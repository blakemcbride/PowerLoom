#!/usr/bin/env python

############################# BEGIN LICENSE BLOCK ############################
#                                                                            #
# Version: MPL 1.1/GPL 2.0/LGPL 2.1                                          #
#                                                                            #
# The contents of this file are subject to the Mozilla Public License        #
# Version 1.1 (the "License"); you may not use this file except in           #
# compliance with the License. You may obtain a copy of the License at       #
# http://www.mozilla.org/MPL/                                                #
#                                                                            #
# Software distributed under the License is distributed on an "AS IS" basis, #
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License   #
# for the specific language governing rights and limitations under the       #
# License.                                                                   #
#                                                                            #
# The Original Code is the PowerLoom KR&R System.                            #
#                                                                            #
# The Initial Developer of the Original Code is                              #
# UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          #
# 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               #
#                                                                            #
# Portions created by the Initial Developer are Copyright (C) 2015-2023      #
# the Initial Developer. All Rights Reserved.                                #
#                                                                            #
# Contributor(s):                                                            #
#                                                                            #
# Alternatively, the contents of this file may be used under the terms of    #
# either the GNU General Public License Version 2 or later (the "GPL"), or   #
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),   #
# in which case the provisions of the GPL or the LGPL are applicable instead #
# of those above. If you wish to allow use of your version of this file only #
# under the terms of either the GPL or the LGPL, and not to allow others to  #
# use your version of this file under the terms of the MPL, indicate your    #
# decision by deleting the provisions above and replace them with the notice #
# and other provisions required by the GPL or the LGPL. If you do not delete #
# the provisions above, a recipient may use your version of this file under  #
# the terms of any one of the MPL, the GPL or the LGPL.                      #
#                                                                            #
############################# END LICENSE BLOCK ##############################

### Various utilities to run Blazegraph queries directly from PowerLoom
### This mirrors some of the machinery in rdbms.ste for relational DBs,
### but it was easier to recreate it here instead of generalizing there.

from __future__ import print_function, division, absolute_import

import sys
PY2 = sys.version_info[0] == 2
PY3 = sys.version_info[0] >= 3
if PY3:
    unicode = str
    basestring = (bytes, unicode)
    long = int

import misc
import atexit

# we want all blazegraph fns available here, so we only have to import once:
from blazegraph import *

import stellapi as spi
import ploompi as pli

spi.loadSystem('rdbms')    # needed so the RDBMS module is available


### NOTES, TO DO:
# - implement a db-update demon so cached connections can be wiped out if a db object gets modified
# - add query cache cleanup machinery once we also have updates that might change the triple store
# - figure out how to handle large result sets without materializing them completely
# - figure out whether the SAIL Repository query machinery would be faster instead of going through the HTTP server
# - PLI:
#   - implement a more convenient binary relation value accessor (a la access-binary-value)
#   - support easy implementation of demons similar to what we do for specialists and computations
#   - provide accessor for a named object's name module so we can easily get namespace prefixes such as RDF/... etc.
#   - figure out whether there is a generic way to store Python objects as values of STELLA slots


### STELLA API definitions:

spi.defglobal('logic/*evaluationMode*')
spi.defglobal('logic/*invisibleAssertion?*')
spi.defglobal('logic/*queryIterator*')


### Connection management:

blazegraphPowerLoomConnections = {}

@lru_cache(maxsize=20)
def getCurrentBlazegraphPowerLoomConnection(obj, module):
    "Return the currently cached connection object for `obj' relative to `module'."
    conn = pli.getBinaryProposition('rdbms/db-connection', obj, module=module)
    if conn is not None:
        conn = pli.getNthValue(conn, 2, module=module)
    if conn is not None:
        conn = str(conn)
    if conn is not None:
        conn = blazegraphPowerLoomConnections.get(conn)
    return conn

def resetBlazegraphPowerLoomConnections():
    "Clear and close all currently cached open connections."
    getCurrentBlazegraphPowerLoomConnection.cache_clear()
    for conn in blazegraphPowerLoomConnections.values():
        conn = conn['blazegraph']
        if conn.isOpen():
            conn.close()
    blazegraphPowerLoomConnections.clear()
    print('resetBlazegraphPowerLoomConnections(): done')

atexit.register(resetBlazegraphPowerLoomConnections)
    
def getBlazegraphPowerLoomConnection(dbobj):
    """Create or access a Blazegraph connection object for `dbobj' and cache it in `blazegraphPowerLoomConnections'.
    The key to each cached connection is a UUID which gets asserted as the value of (rdbms/db-connection dbobj "uuid").
    We also rely on an additional memoized lookup via `getCurrentBlazegraphPowerLoomConnection' for fast connection
    access once the connection has been created and cached."""
    module = pli.getCurrentModule()
    conn = getCurrentBlazegraphPowerLoomConnection(dbobj, module)
    if conn is None:
        getCurrentBlazegraphPowerLoomConnection.cache_clear()
        if not pli.isInstance(dbobj, 'rdbms/blazegraph-database'):
            return None, None

        # TO DO: we need a better way to bind STELLA specials, also this is not thread-safe:
        oldctxt = spi.stella.pdef.oCONTEXTo
        oldevmode = spi.logic.pdef.oEVALUATIONMODEo
        oldinvass = spi.logic.pdef.oINVISIBLEASSERTIONpo
        oldqiter = spi.logic.pdef.oQUERYITERATORo
        try:
            datasetName = pli.getBinaryProposition('rdbms/dataset-name', dbobj)
            if datasetName is None:
                return None, None
            # ensure we have a logic object at this point:
            dbobj = pli.getNthValue(datasetName, 1)
            datasetName = pli.getNthValue(datasetName, 2)
            dataset = str(datasetName)
            # if we have a dataset object, access its parent database:
            database = pli.getBinaryProposition('rdbms/dataset-db', dbobj)
            database = database and pli.getNthValue(database, 2) or dbobj
            connString = pli.getBinaryProposition('rdbms/connection-string', dbobj)
            if connString is None:
                connString = pli.getBinaryProposition('rdbms/connection-string', database)
            connString = connString and pli.getNthValue(connString, 2)
            # can only handle embedded connections for now:
            if connString is None or str(connString) != 'embedded':
                return None, None
            blzg = getBlazegraph(dataset=dataset)
            connid = str(uuid.uuid1())
            conn = {'blazegraph': blzg, 'dataset': dataset}
            blazegraphPowerLoomConnections[connid] = conn

            # set up assertion environment, so we can safely do this within a query:
            # TO DO: support this better in PLI, since this is really obscure and messy
            spi.stella.pdef.oCONTEXTo = dbobj.homeModule()
            spi.logic.pdef.oEVALUATIONMODEo = pli.createKeyword('EXTENSIONAL-ASSERTION')
            # make sure we don't destroy the current inference cache - even though 'db-connection'
            # is a hidden relation, that doesn't help us with top-level assertions like these:
            spi.logic.pdef.oINVISIBLEASSERTIONpo = True
            # this isn't strictly necessary, but just to be safe:
            spi.logic.pdef.oQUERYITERATORo = None
            
            pli.assertBinaryProposition('rdbms/db-connection', dbobj, connid, module=module)
        except:
            return None, None
        finally:
            # restore STELLA specials:
            spi.stella.pdef.oCONTEXTo = oldctxt
            spi.logic.pdef.oEVALUATIONMODEo = oldevmode
            spi.logic.pdef.oINVISIBLEASSERTIONpo = oldinvass
            spi.logic.pdef.oQUERYITERATORo = oldqiter
            
    return conn['blazegraph'], conn['dataset']


### Namespace to module mapping:

# To define a bidirectional mapping between PowerLoom modules and RDF namespace URIs, we do the following:
# - we piggyback off the rdflib NamespaceManager machinery to define and access the mapping
# - given a prefix-to-URI mapping such as 'owl' -> 'http://www.w3.org/2002/07/owl#' we map the corresponding
#   PowerLoom OWL module as       'owl_plmmod_' -> 'plmmod:///XMLNS/OWL', that is, we use a derived parallel
#   prefix which is mapped onto the module pathname.  This way we can go from the module path to the derived
#   prefix and therefore the prefix, and from a prefix to the derived prefix to the pathname.  We memoize
#   the mapping functions to negate the extra indirect access overhead and cost of the prefix lookup (since
#   the NamespaceManager searches the dictionary's values to map from a URI back to the prefix).

NS_MODULE_PREFIX  = 'plmmod://'
NS_MODULE_POSTFIX = '_plmmod_'

standardModuleBindings = {
    'xsd':  '/XMLNS/XMLS',
    'rdf':  '/XMLNS/RDF',
    'rdfs': '/XMLNS/RDFS',
    'owl':  '/XMLNS/OWL',
}

def _blazegraphBindModule(self, prefix, moduleSpec):
    """Map the namespace `prefix' (really its associated URI) onto the module `moduleSpec'
    which has to be either an actual module or an absolute module path.  This requires
    that `prefix' has already been defined by the time a module is mapped to it."""
    if self.getNamespaceBindings().get(prefix) is None:
        raise Exception('namespace prefix is not yet defined: ' + str(prefix))
    if isinstance(moduleSpec, pli.Module):
        path = pli.getName(moduleSpec)
    elif isinstance(moduleSpec, str):
        path = moduleSpec
    else:
        path = pli.getName(pli.getExistingModule(moduleSpec))
    if not path.startswith('/'):
        raise Exception('module spec is not an absolute pathname: ' + str(moduleSpec))
    prefix = prefix + NS_MODULE_POSTFIX
    namespace = NS_MODULE_PREFIX + path
    self.bindNamespace(prefix, rdflib.URIRef(namespace))
    # clear memoized mappings:
    moduleToNamespacePrefix.cache_clear()
    moduleToNamespaceUri.cache_clear()
    namespaceUriToModule.cache_clear()
Blazegraph.bindModule = _blazegraphBindModule

def ensureModuleBindings(blzg):
    "Ensures that all module bindings in `standardModuleBindings' have been added to `blzg'."
    if not getattr(blzg, '_processedModuleBindings', False):
        for prefix, modpath in standardModuleBindings.items():
            blzg.bindModule(prefix, modpath)
        setattr(blzg, '_processedModuleBindings', True)

@lru_cache(maxsize=100)
def moduleToNamespacePrefix(blzg, module):
    "Lookup the namespace URI prefix for the PowerLoom `module'.  Return None if it is undefined."
    # We memoize, since reverse namespace-to-prefix lookup is expensive.
    if not isinstance(module, pli.Module):
        module = pli.getExistingModule(module)
    # make sure bindings are defined and new bindings have been propagated:
    ensureModuleBindings(blzg)
    blzg.getNamespaceManager()
    sstore = blzg.getSparqlStore()
    path = rdflib.URIRef(NS_MODULE_PREFIX + pli.getName(module))
    prefix = sstore.prefix(path)
    return prefix[:-len(NS_MODULE_POSTFIX)] if prefix is not None else None

@lru_cache(maxsize=100)
def moduleToNamespaceUri(blzg, module):
    "Lookup the namespace URI for the PowerLoom `module'.  Return None if it is undefined."
    # We memoize, since reverse namespace-to-prefix lookup is expensive.
    prefix = moduleToNamespacePrefix(blzg, module)
    sstore = blzg.getSparqlStore()
    if prefix is not None:
        return sstore.namespace(prefix)
    else:
        return None

@lru_cache(maxsize=100)
def namespaceUriToModule(blzg, namespace):
    "Lookup the PowerLoom module mapped to the given `namespace' URI.  Return None if it is undefined."
    # We memoize, since reverse namespace-to-prefix lookup is expensive.
    if not isinstance(namespace, rdflib.URIRef):
        namespace = rdflib.URIRef(namespace)
    # make sure bindings are defined and new bindings have been propagated:
    ensureModuleBindings(blzg)
    blzg.getNamespaceManager()
    sstore = blzg.getSparqlStore()
    prefix = sstore.prefix(namespace)
    if prefix is not None:
        prefix = prefix + NS_MODULE_POSTFIX
        path = sstore.namespace(prefix)
        if path is not None:
            path = str(path)[len(NS_MODULE_PREFIX):]
            return pli.getModule(path)
    return None

"""
>>> bs.bindModule('rdf', '/XMLNS/RDF')
>>> bs.bindModule('owl', pli.getModule('OWL'))
>>> moduleToNamespaceUri(bs, 'RDF')
rdflib.term.URIRef(u'http://www.w3.org/1999/02/22-rdf-syntax-ns#')
>>> moduleToNamespaceUri(bs, pli.getModule('RDF'))
rdflib.term.URIRef(u'http://www.w3.org/1999/02/22-rdf-syntax-ns#')
>>> namespaceUriToModule(bs, 'http://www.w3.org/2002/07/owl#')
<pli.Module /XMLNS/OWL>
"""


### RDF to PowerLoom object conversion:

# Conversion to and from RDF is based on the object types of the PowerLoom and RDF values
# and availability of corresponding prefix->namespace->module mapping definitions.
# - default conversion is overridable for some cases, e.g., when bringing results back into
#   PowerLoom based on a variable type such as STRING, we create strings instead of logic objects
# - how initial bindings are communicated and thus how they need to be encoded might depend on the
#   specific SPARQL query interface we are using (e.g., there might be different possibilities if
#   we use the Blazegraph RDF/SAIL connection instead of the NanoSparqlServer via rdflib).

modulePathRegex = re.compile('/?[a-zA-Z][a-zA-Z0-9/_.-]*/')

# this datatype needs to match the datatype used to encode strings in the triple store
# (set this to None to encode PowerLoom strings as old-style plain literals):
#stringLiteralDataType = XSD.string
stringLiteralDataType = None

def coercePowerLoomValueToRdf(blzg, value, targetType):
    "Return an RDF translation of the PowerLoom `value' as an rdflib term."
    if isinstance(value, pli.LogicObject):
        name = pli.getName(value)
        # this test automatically excludes skolems:
        if name is not None and name.startswith('/'):
            moduleName = name[0:modulePathRegex.match(name).end()]
            moduleUri = moduleToNamespaceUri(blzg, moduleName)
            if moduleUri is not None:
                return rdflib.URIRef(moduleUri + pli.getShortName(value))
        return str(value)
    if isinstance(value, pli.StringWrapper):
        value = str(value)
        colpos = value.find(':')
        if colpos > 0:
            # namespaces are assumed to be of type rdflib.Namespace:
            ns = blzg.getNamespaceBindings().get(value[0:colpos])
            if ns is not None:
                # the string looks like a prefixed URI, treat it as such (e.g., 'rdf:type'):
                return rdflib.URIRef(ns[value[colpos+1:]])
        return rdflib.Literal(misc.coerceToUnicode(value), datatype=stringLiteralDataType)
    # see here for numeric XSD type info: https://docstore.mik.ua/orelly/xml/schema/ch04_04.htm
    elif isinstance(value, pli.IntegerWrapper):
        return rdflib.Literal(misc.coerceToUnicode(str(value)), datatype=XSD.integer)
    elif isinstance(value, pli.FloatWrapper):
        return rdflib.Literal(misc.coerceToUnicode(str(value)), datatype=XSD.double)
    elif isinstance(value, pli.LongIntegerWrapper):
        return rdflib.Literal(misc.coerceToUnicode(str(value)), datatype=XSD.long)
    else:
        # don't know what it is, treat it as a string:
        return rdflib.Literal(str(value))

def coerceRdfValueToPowerLoom(blzg, value, targetType):
    "Return a PowerLoom representation of the rdflib term `value'."
    if isinstance(value, rdflib.term.URIRef):
        nsm = blzg.getNamespaceManager()
        prefix, nsuri, name = uriToQualifiedName(value, nsm)
        name = misc.coerceToBytes(unicode(name))
        if pli.getShortName(targetType) == 'STRING':
            return pli.createStringWrapper(prefix + ':' + name)
        module = nsuri and namespaceUriToModule(blzg, nsuri)
        if module is not None:
            obj = None
            createObj = False
            nameSymbol = pli.getSymbol(name, module)
            if nameSymbol is None:
                # no matching symbol found, we have to create one plus a matching object:
                nameSymbol = pli.createSymbol(name, module)
                createObj = True
            qualName = pli.getName(nameSymbol)
            if not createObj:
                # try to find an existing object - PowerLoom's get-instance is too flexible
                # and will find an object in the current module with matching name if necessary,
                # for that reason we always create one if we had to create a symbol above
                # (handles the problem where /XMLNS/CONLL/NUMBER picked up PL-KERNEL/NUMBER):
                obj = pli.getObject(qualName)
            if obj is None:
                # no suitable object found, we have to create one:
                obj = pli.createObject(qualName)
            return obj
        # otherwise, fall through and create a string representation:
        if prefix is not None:
            value = prefix + ':' + name
        else:
            value = name
        return pli.createStringWrapper(value)
    elif isinstance(value, rdflib.term.Literal):
        dtype = value.datatype
        if dtype == XSD.string:
            return pli.createStringWrapper(misc.coerceToBytes(unicode(value)))
        # see here for numeric XSD type info: https://docstore.mik.ua/orelly/xml/schema/ch04_04.htm
        elif dtype == XSD.integer:
            return pli.createIntegerWrapper(int(value))
        elif dtype == XSD.float or dtype == XSD.double:
            return pli.createFloatWrapper(float(value))
        elif dtype == XSD.long:
            return pli.createLongIntegerWrapper(long(value))
        else:
            return pli.createStringWrapper(misc.coerceToBytes(unicode(value)))
    else:
        # don't know what it is (maybe a blank node), treat it as a string:
        return pli.createStringWrapper(str(value))


### Query translation, specialist and ontology:

def getCanonicalVariableName(var):
    """Given a PowerLoom or SPARQL result variable `var', canonicalize it onto
    a lower-case string that starts with a `?'.  This will do the right thing
    to propagate output values even if variable cases differ, however, for binding
    constraints to work, the SPARQL query variable has to be in lower-case.
    """
    if isinstance(var, pli.PatternVariable):
        var = pli.getVariableShortName(var)
    else:
        var = str(var)
    qpos = var.find('?')
    if qpos < 0:
        var = '?' + var
    elif qpos > 0:
        var = var[qpos:]
    var = var.lower()
    return var

def collectQueryBindingInfos(blzg, frame):
    """For each output variable following the query argument in this `query-blazegraph'
    `frame', collect various name, position, type and binding info, and pre-compute a
    binding constraint in case the variable had a single or set-valued binding.
    """
    infos = {}
    nsm = blzg.getNamespaceManager()
    for i in range(2, pli.getFrameArity(frame)):
        arg = pli.getNthFrameArgument(frame, i)
        value = pli.getNthFrameBinding(frame, i)
        if isinstance(arg, pli.PatternVariable):
            # TO DO: enable access to the variable's type via logical-type:
            varName = getCanonicalVariableName(arg)
            info = {'variable': arg, 
                    'variableName': varName, 
                    'index': i, 
                    'type': pli.getLogicType(arg), 
                    'value': value}
            infos[varName] = info
            if value is not None:
                sparqlValues = []
                if pli.isEnumeratedCollection(value):
                    for val in pli.getEnumeratedCollectionMembers(value):
                        sparqlValues.append(coercePowerLoomValueToRdf(blzg, val, info['type']).n3(nsm))
                else:
                    sparqlValues.append(coercePowerLoomValueToRdf(blzg, value, info['type']).n3(nsm))
                if len(sparqlValues) == 1:
                    constraint = "BIND ( %s AS %s )" % (sparqlValues[0], varName)
                else:
                    constraint = "VALUES %s { %s }" % (varName, ' '.join(sparqlValues))
                info['constraint'] = constraint
    return infos

def instantiateQueryConstraints(blzg, query, bindingInfos):
    """Splice any binding constraints defined in `bindingInfos' into `query'.
    NOTE/TO DO: due to variable name normalization, this will currently only do
    the right thing if the corresponding SPARQL query variable is in lower-case.
    """
    io = None
    for var, info in bindingInfos.items():
        constraint = info.get('constraint')
        if constraint is not None:
            if io is None:
                whereStart = query.find('{')
                if whereStart <= 0:
                    return query
                whereStart += 1
                io = StringIO()
                io.write(query[:whereStart])
            io.write(constraint)
            io.write('\n')
    if io is not None:
        io.write(query[whereStart:])
        query = io.getvalue()
    return query

def getResultSetViaNss(blzg, query, bindingInfos, dataset=None):
    """Run a SPARQL `query' against this Blazegraph `blzg' relative to `dataset' and return
    an iterator of result tuples that can be used to bind the unbound output variables in the
    invoking specialist's frame which are captured in `bindingInfos'.  Any variable binding
    constraints communicated in `bindingInfos' are first spliced into `query' before it is run.
    The order of output values in the resulting iterator match the order of unbound variables
    in the invoking specialist's frame.  Since binding constraints are provided at the level
    of the SPARQL `query', we do not have to check whether result bindings are unifiable with
    the variable bindings on the frame; thus, we only return bindings of unbound variables.
    Input and output values are properly converted to and from PowerLoom based on their object
    or RDF types, however, it is possible to override that by providing variable types.
    """
    query = instantiateQueryConstraints(blzg, query, bindingInfos)
    if debugSpecialist == 'trace':
        print(query)
    try:
        results = blzg.query(query, dataset=dataset)
    except:
        return None
    outputInfos = None
    outputRows = []
    for row in results:
        if outputInfos is None:
            outputInfos = []
            for var, idx in row.labels.items():
                var = getCanonicalVariableName(var)
                varInfo = bindingInfos.get(var)
                if varInfo is not None and varInfo.get('value') is None:
                    varInfo['columnIndex'] = idx
            for info in bindingInfos.values():
                if info.get('value') is None:
                    if info.get('columnIndex') is None:
                        return None
                    outputInfos.append(info)
            outputInfos.sort(key=lambda i: i['index'])
        values = []
        for info in outputInfos:
            value = row[info['columnIndex']]
            values.append(coerceRdfValueToPowerLoom(blzg, value, info['type']))
        outputRows.append(values)
    iterator = pli.consToPlIterator(spi.pythonToStellaTree(outputRows))
    return iterator


debugSpecialist = None # or 'trace', 'step'

@lru_cache(maxsize=1000)
def getQueryBlazegraphCache(blzg, dataset, query, bindings):
    """LRU cache for a query-blazegraph frame with specific query and binding values.
    This serves primarily as an API-entry point to lru_cache which only supports
    memoization of functions.  The arguments here are all hashable which is not the
    case for some of the query functions used to populate this cache."""
    return []

@pli.specialist(relation='rdbms/query-blazegraph', module='rdbms/database', create=True, arity=3, varargs=True, defer=True)
def queryBlazegraphSpecialist(frame, lastMove):
    """Specialist for the PowerLoom `rdbms/query-blazegraph(?db ?query ?x ...)' relation
       which provides a PowerLoom API for the blazegraph.Blazegraph.query method.
    """
    if debugSpecialist == 'step':
        import pdb
        pdb.set_trace()
    iterator = pli.getFrameIterator(frame)
    if iterator is None:
        # first time around, at least the db and query args need to be bound:
        if pli.isFrameBindingPattern(frame, 'BB'):
            db = pli.getNthFrameBinding(frame, 0)
            query = pli.getNthFrameBinding(frame, 1)
            if isinstance(db, pli.LogicObject) and isinstance(query, pli.StringWrapper):
                blzg, dataset = getBlazegraphPowerLoomConnection(db)
                if blzg is None:
                    return pli.TERMINAL_FAILURE
                query = str(query)
                # create a hashable bindings key:
                bindings = tuple([str(pli.getNthFrameBinding(frame, i)) for i in range(2, pli.getFrameArity(frame))])
                cache = getQueryBlazegraphCache(blzg, dataset, query, bindings)
                if len(cache) == 0:
                    # in case there were any foreign-language strings in the query, make sure to convert to Unicode:
                    query = misc.coerceToUnicode(query)
                    bindingInfos = collectQueryBindingInfos(blzg, frame)
                    iterator = getResultSetViaNss(blzg, query, bindingInfos, dataset=dataset)
                    if iterator is not None:
                        # this wastes one full iteration over the list which we could avoid by changing `getResultSetViaNss':
                        solutions = pli.plIteratorConsify(iterator)
                    else:
                        solutions = pli.NIL
                    cache.append(solutions)
                iterator = pli.consToPlIterator(cache[0])
                pli.setFrameIterator(frame, iterator)
    if iterator is None:
        return pli.TERMINAL_FAILURE
    # generate solutions:
    bindingState = pli.getFrameBindingState(frame)
    arity = pli.getFrameArity(frame)
    for row in iterator:
        row = list(row)
        ci = 0
        for i in range(2, arity):
            value = pli.getNthFrameBinding(frame, i)
            if value is None:
                if pli.setNthFrameBinding(frame, i, row[ci]):
                    ci += 1
        if ci == len(row):
            # we successfully consumed the whole output row:
            return pli.CONTINUING_SUCCESS
        else:
            pli.setFrameBindingState(frame, bindingState)
    return pli.TERMINAL_FAILURE


ontology = """(progn

(defconcept RDBMS/Graph-Database (RDBMS/Database)
  :documentation "Information defining a graph database.")

(defconcept RDBMS/Blazegraph-Database (RDBMS/Graph-Database)
  :documentation "Information defining a Blazegraph database supporting SPARQL queries.")

(defconcept RDBMS/Blazegraph-Dataset (RDBMS/Blazegraph-Database)
  :documentation "A derived Blazegraph database for a specific dataset.")

(deffunction RDBMS/dataset-name ((?db RDBMS/Blazegraph-Database)) :-> (?dataset STRING)
  :documentation "The name of a specific dataset (database) on a Blazegraph server."
  ;; we might need some equivalent that can handle Blazegraph connections:
  ;:goes-true-demon RDBMS/db-update-demon
  ;:goes-unknown-demon RDBMS/db-update-demon
  )

(deffunction RDBMS/dataset-db ((?db RDBMS/Blazegraph-Dataset)) :-> (?server RDBMS/Blazegraph-Database)
  :documentation "The Blazegraph database server hosting this dataset.  This allows us to define
dataset-specific derived databases using the same connection information as the main server."
  ;; we might need some equivalent that can handle Blazegraph connections:
  ;:goes-true-demon RDBMS/db-update-demon
  ;:goes-unknown-demon RDBMS/db-update-demon
  )

(defrelation RDBMS/blazegraph-triple (?subj ?pred ?obj)
  :documentation "Convenience accessor for `blazegraph' DB.  Limited to at most 1000 results for safety."
  :<<= (rdbms/query-blazegraph blazegraph "SELECT * { ?subj ?pred ?obj } LIMIT 1000" ?subj ?pred ?obj))

(defrelation RDBMS/bind-as (?value ?var)
  :documentation "Utility that binds ?var to ?value and fails if ?var was already bound.
This is useful to generate initial bindings without bound variables being optimized out
by the query normalizer which could happen with the `(= ?var VALUE)' idiom."
  :<<= (and (bound-variables ?value)
            (fork (bound-variables ?var)
                  (fail (bound-variables ?var))
                  (= ?var ?value))
            (cut))
  :single-valued TRUE
  :computed TRUE)
)
"""

dbDefinitions = """(progn

(defdb blazegraph
  :documentation "Blazegraph database instance; connection and dataset info can be asserted in an application context."
  :Blazegraph-Database TRUE
  :connection-string "embedded")

(defdb blazegraph-kb
  :Blazegraph-Dataset TRUE
  :dataset-name "kb"
  :dataset-db blazegraph)
)
"""

pli.evalDeferred(pli.eval, 'RDBMS', ontology, module='PL-KERNEL')
pli.evalDeferred(pli.eval, 'RDBMS', dbDefinitions, module='PL-KERNEL')

# If possible, execute PowerLoom definitions in the current environment, otherwise this has to be called again later:
pli.processDeferredCommands()


"""
>>> pli.powerloom()

PL-USER |= (defdb opera-csr
             :Blazegraph-Dataset TRUE
             :dataset-name "operademo"
             :dataset-db blazegraph)

PL-USER |= (time-command
             (retrieve all (?s1 ?p ?o)
                (and (setof "data:sent-HC0000318-text-cmu-r1-21" "data:sent-HC0000318-text-cmu-r1-22" ?s)
                     (rdbms/query-blazegraph opera-csr "SELECT * { BIND (?s AS ?s1) ?s1 ?p ?o } limit 200" ?s ?s1 ?p ?o))))

CPU Time:     0.08817999999999999 secs
Elapsed Time: 0 secs
There are 6 solutions:
#1: ?S1="data:sent-HC0000318-text-cmu-r1-21", ?P="ail:extent", ?O="t155"
#2: ?S1="data:sent-HC0000318-text-cmu-r1-21", ?P="ail:meta", ?O="t249"
#3: ?S1="data:sent-HC0000318-text-cmu-r1-21", ?P="rdf:type", ?O="ail:sentence"
#4: ?S1="data:sent-HC0000318-text-cmu-r1-22", ?P="ail:extent", ?O="t287"
#5: ?S1="data:sent-HC0000318-text-cmu-r1-22", ?P="ail:meta", ?O="t252"
#6: ?S1="data:sent-HC0000318-text-cmu-r1-22", ?P="rdf:type", ?O="ail:sentence"


PL-USER |= (assert (rdbms/dataset-name blazegraph "operademo"))

|P|(= (/RDBMS/DATASET-NAME BLAZEGRAPH) "operademo")

PL-USER |= (retrieve (rdbms/query-blazegraph blazegraph "SELECT (COUNT(*) AS ?no) { ?s rdf:type ?o }" ?no))

There is 1 solution so far:
#1: ?NO=19352

PL-USER |= (retrieve 10 (rdbms/blazegraph-triple ?subj ?pred ?obj))

There are 10 solutions so far:
 #1: ?SUBJ="data:HC0000318-text", ?PRED="ail:language", ?OBJ="en"
 #2: ?SUBJ="data:HC0000318-text", ?PRED="ail:media_type", ?OBJ="text"
 #3: ?SUBJ="data:HC0000318-text", ?PRED="ail:meta", ?OBJ="t49812"
 #4: ?SUBJ="data:HC0000318-text", ?PRED="rdf:type", ?OBJ="ail:document"
 #5: ?SUBJ="data:sent-HC0000318-text-cmu-r1-0", ?PRED="ail:extent", ?OBJ="t49919"
 #6: ?SUBJ="data:sent-HC0000318-text-cmu-r1-0", ?PRED="ail:meta", ?OBJ="t49826"
 #7: ?SUBJ="data:sent-HC0000318-text-cmu-r1-0", ?PRED="rdf:type", ?OBJ="ail:sentence"
 #8: ?SUBJ="data:sent-HC0000318-text-cmu-r1-1", ?PRED="ail:extent", ?OBJ="t49879"
 #9: ?SUBJ="data:sent-HC0000318-text-cmu-r1-1", ?PRED="ail:meta", ?OBJ="t49854"
#10: ?SUBJ="data:sent-HC0000318-text-cmu-r1-1", ?PRED="rdf:type", ?OBJ="ail:sentence"

PL-USER |= (retrieve 10 (rdbms/blazegraph-triple ?subj "ail:language" ?obj))

There are 3 solutions:
#1: ?SUBJ="data:HC0000318-text", ?OBJ="en"
#2: ?SUBJ="data:HC000Q7X1-text", ?OBJ="uk"
#3: ?SUBJ="data:HC000T6IZ-text", ?OBJ="ru"

PL-USER |= (retrieve 10 (RDBMS/blazegraph-triple "data:HC000T6IZ-text" "rdf:type" ?o ))

There is 1 solution:
#1: ?O="ail:document"
"""
