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
# Portions created by the Initial Developer are Copyright (C) 2021-2023      #
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

### Various utilities to run KGTK Kypher queries directly from PowerLoom
### This mirrors some of the machinery in rdbms.ste for relational DBs,
### but it was easier to recreate it here instead of generalizing there.
### Derived from blazegraph_pli.py

from __future__ import print_function, division, absolute_import

import sys
PY2 = sys.version_info[0] == 2
PY3 = sys.version_info[0] >= 3
if PY3:
    unicode = str
    basestring = (bytes, unicode)
    long = int

if PY3:
    from functools import lru_cache
else:
    from functools32 import lru_cache
import uuid

import misc
import atexit
import rdflib

import stellapi as spi
import ploompi as pli
import blazegraph_pli as blzg         # piggyback on the namespace mapping functionality
import kgtk.kypher.api as kapi
import kgtk.kypher.funclit as litfun  # TO DO: support this from kapi

spi.loadSystem('rdbms')               # needed so the RDBMS module is available


### NOTES, TO DO:

# - constraint substitution parsing needs initial whitespace and is thrown off by single quote
# - need to generalize substitution processing to handle other parameters such as text search strings
# - implement kypher-nsquery that imports objects into RDF namespace similar to query-blazegraph


# Example setup and query:

"""
>>> dwd_api = kapi.KypherApi(graphcache='.../wikidata-20210215-dwd-v2-similarity-main.2021-10-03T12:02.sqlite3.db', loglevel=1)
>>> aida_kb_api = kapi.KypherApi(graphcache='.../output-minikbs.sqlite3.db', loglevel=1)

(rdbms/defdb dwddb
  :documentation "DWD Kypher database instance."
  :Kypher-Database TRUE
  ;; evaluated relative to 'pythonEvalModule' (defaults to main):
  :connection-string "dwd_api"
  ;; assumed for translation of unqualified symbols:
  :default-namespace "wdOnt")

(rdbms/defdb aidakb
  :documentation "AIDA KB Kypher database instance."
  :Kypher-Database TRUE
  ;; this auto-translates bindings and results to/from PowerLoom:
  :auto-translate TRUE
  :connection-string "aida_kb_api")

(retrieve 10 
  (and (= ?node "Q42")
       ;; constraint substitution parsing below is very fragile for now and needs whitespace:
       (rdbms/query-kypher
         dwddb
         "-i claims labels
          --match '(qnode)-[r {label: rl}]->(y)'
          --where ' qnode=?node '
          --opt   'lab: (rl)-[]->(rlab)'
          --opt   'lab: (y)-[]->(ylab)'
          --where: 'not kgtk_lqstring_text(rlab) =~ \".* ID ?.*\"'
          --return 'qnode, rl, rlab, y, ylab'
          --limit 100"
         ?node ?rl ?rlab ?y ?ylab)))
"""


### STELLA API definitions:

#spi.defun('stella/wrap-integer-value', _except=False, _pyin=False) # promote this to PLI
spi.defconstructor('stella/key-value-list')
spi.defmethod('stella/key-value-list.insert-at')
spi.defun('rdbms/sql-query-instantiate-constraints')


### Connection management:

kypherPowerLoomConnections = {}
pythonEvalModule = sys.modules['__main__']

@lru_cache(maxsize=20)
def getCurrentKypherPowerLoomConnection(obj, module):
    "Return the currently cached connection object for `obj' relative to `module'."
    conn = pli.getBinaryProposition('rdbms/db-connection', obj, module=module)
    if conn is not None:
        conn = pli.getNthValue(conn, 2, module=module)
    if conn is not None:
        conn = str(conn)
    if conn is not None:
        conn = kypherPowerLoomConnections.get(conn)
    return conn

def resetKypherPowerLoomConnections():
    "Clear and close all currently cached open connections."
    getCurrentKypherPowerLoomConnection.cache_clear()
    for conn in kypherPowerLoomConnections.values():
        conn = conn['api']
        conn.close()
    kypherPowerLoomConnections.clear()
    print('resetKypherPowerLoomConnections(): done')

atexit.register(resetKypherPowerLoomConnections)
    
def getKypherPowerLoomConnection(dbobj):
    """Create or access a Kypher connection object for `dbobj' and cache it in `kypherPowerLoomConnections'.
    The key to each cached connection is a UUID which gets asserted as the value of (rdbms/db-connection dbobj "uuid").
    We also rely on an additional memoized lookup via `getCurrentKypherPowerLoomConnection' for fast connection
    access once the connection has been created and cached.
    """
    module = pli.getCurrentModule()
    conn = getCurrentKypherPowerLoomConnection(dbobj, module)
    if conn is None:
        getCurrentKypherPowerLoomConnection.cache_clear()
        if not pli.isInstance(dbobj, 'rdbms/kypher-database'):
            return None

        # TO DO: we need a better way to bind STELLA specials, also this is not thread-safe:
        oldctxt = spi.stella.pdef.oCONTEXTo
        oldevmode = spi.logic.pdef.oEVALUATIONMODEo
        oldinvass = spi.logic.pdef.oINVISIBLEASSERTIONpo
        oldqiter = spi.logic.pdef.oQUERYITERATORo
        try:
            connString = pli.getBinaryProposition('rdbms/connection-string', dbobj)
            if connString is None:
                return None
            dbobj = pli.getNthValue(connString, 1)
            connString = str(pli.getNthValue(connString, 2))
            
            api = eval(connString, pythonEvalModule.__dict__)
            defaultNs = pli.getBinaryProposition('rdbms/default-namespace', dbobj)
            defaultNs = defaultNs and str(pli.getNthValue(defaultNs, 2))
            autoTrans = pli.isTrueUnaryProposition('rdbms/auto-translate', dbobj)
            # FIXME: these options are currently linked directly to an API object, which means
            # if the API is shared among different DB instances, their options cannot differ;
            # but, for example, we might want a raw and an autotrans version of the same DB.
            api._kypherPliStore = KypherPliStore(defaultNs=defaultNs, autoTrans=autoTrans)

            connid = str(uuid.uuid1())
            conn = {'api': api}
            kypherPowerLoomConnections[connid] = conn

            # set up assertion environment, so we can safely do this within a query:
            # TO DO: support this better in PLI, since this is really obscure and messy
            spi.stella.pdef.oCONTEXTo = dbobj.homeModule()
            spi.logic.pdef.oEVALUATIONMODEo = pli.createKeyword('EXTENSIONAL-ASSERTION')
            # make sure we don't destroy the current inference cache - even though 'db-connection'
            # is a hidden relation, that doesn't help us with top-level assertions like these:
            spi.logic.pdef.oINVISIBLEASSERTIONpo = True
            # this isn't strictly necessary, but just to be safe:
            spi.logic.pdef.oQUERYITERATORo = None

            # not needed anymore due to relaxation of 'db-connection' value constraint:
            #pli.assertUnaryProposition('rdbms/connection-wrapper', connid, module=module)
            pli.assertBinaryProposition('rdbms/db-connection', dbobj, connid, module=module)
        except:
            return None
        finally:
            # restore STELLA specials:
            spi.stella.pdef.oCONTEXTo = oldctxt
            spi.logic.pdef.oEVALUATIONMODEo = oldevmode
            spi.logic.pdef.oINVISIBLEASSERTIONpo = oldinvass
            spi.logic.pdef.oQUERYITERATORo = oldqiter
            
    return conn['api']


### Namespace to module mapping:

# we piggyback off blazegraph_pli (which see for the full story)

class KypherPliStore(object):
    """Shell class which provides the necessary functionality normally provided by blzg.Blazegraph
    to support namespace mappings and namespace to module translation.
    """

    def __init__(self, initNs=blzg.standardNamespaces, defaultNs=None, autoTrans=False):
        self.nsBindings = initNs
        self.defaultNsPrefix = defaultNs
        self.autoTranslate = autoTrans
        self.nsManager = None
        self.sparqlStore = rdflib.plugins.stores.sparqlstore.SPARQLUpdateStore('dummy')

    def getNamespaceBindings(self):
        return self.nsBindings

    def getNamespaceManager(self):
        if self.nsManager is None:
            self.nsManager = blzg.getNamespaceManager(self.nsBindings)
            self.updateNamespaces(self.sparqlStore)
        return self.nsManager

    def bindNamespace(self, prefix, namespace):
        self.getNamespaceBindings()[prefix] = namespace
        self.nsManager = None

    def updateNamespaces(self, store):
        store.nsBindings.update(dict(self.getNamespaceManager().namespaces()))

    def getSparqlStore(self):
        return self.sparqlStore

kapi.KypherApi.getNamespaceBindings = lambda self: self._kypherPliStore.getNamespaceBindings()
kapi.KypherApi.getNamespaceManager = lambda self: self._kypherPliStore.getNamespaceManager()
kapi.KypherApi.bindNamespace = lambda self, prefix, namespace: self._kypherPliStore.bindNamespace(prefix, namespace)
kapi.KypherApi.getSparqlStore = lambda self: self._kypherPliStore.getSparqlStore()
kapi.KypherApi.getDefaultNamespacePrefix = lambda self: self._kypherPliStore.defaultNsPrefix
kapi.KypherApi.autoTranslate = lambda self: self._kypherPliStore.autoTranslate
kapi.KypherApi.bindModule = blzg._blazegraphBindModule


### KGTK to PowerLoom object conversion:

# Blank nodes: we assume an RDF-ish blank node prefix to detect them and translate them onto
# logic objects in the current module with the prefix includes, as in <proxy.LogicObject |_:xyz12345|>.
# We could translate into strings, but then we couldn't distinguish between blank nodes and
# strings that look like blank nodes when translating back to KGTK.

BLANK_NODE_PREFIX = '_:'

def coerceKgtkValueToPowerLoom(db, value, targetType=None):
    """Return a PowerLoom representation of the KGTK term `value'.
    """
    if litfun.kgtk_literal(value):
        # KGTK Literal:
        if litfun.kgtk_string(value):
            value = litfun.kgtk_unstringify(value)
            return pli.createStringWrapper(misc.coerceToBytes(unicode(value)))
        elif litfun.kgtk_number(value):
            number = litfun.kgtk_quantity_number(value)
            if isinstance(number, (int, long)):
                # TO DO: promote this into PLI
                return spi.stella.pdef.wrapIntegerValue(number)
            else:
                return pli.createFloatWrapper(number)
        else:
            return pli.createStringWrapper(misc.coerceToBytes(unicode(value)))

    elif isinstance(value, str):
        # KGTK Symbol:
        nsm = db.getNamespaceManager()
        if ':' in value:
            prefix, name = value.split(':', 1)
        else:
            prefix, name = db.getDefaultNamespacePrefix(), value
        nsuri = db.getNamespaceBindings().get(prefix)
        prefix = misc.coerceToBytes(unicode(prefix)) if prefix is not None else None
        name = misc.coerceToBytes(unicode(name))
        if pli.getShortName(targetType) == 'STRING':
            name = prefix + b':' + name if prefix is not None else name
            return pli.createStringWrapper(name)
        if nsuri is not None:
            module = blzg.namespaceUriToModule(db, nsuri)
        elif value.startswith(BLANK_NODE_PREFIX):
            # for now we intern in the current module and rely on the name prefix only:
            name = misc.coerceToBytes(unicode(value))
            module = pli.getCurrentModule()
        else:
            module = None
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
            value = prefix + b':' + name
        else:
            value = name
        return pli.createStringWrapper(value)

    elif isinstance(value, (int, long)):
        return spi.stella.pdef.wrapIntegerValue(value)
    
    elif isinstance(value, float):
        return pli.createFloatWrapper(value)

    elif value is None:
        # is this right?
        return pli.createStringWrapper(str(value))

    else:
        # don't know what it is, treat it as a string:
        return pli.createStringWrapper(misc.coerceToBytes(unicode(value)))

def coercePowerLoomValueToKgtk(db, value, targetType=None):
    """Return a KGTK term translation of the PowerLoom object `value'.
    """
    if isinstance(value, pli.LogicObject):
        name = pli.getName(value)
        # this test automatically excludes skolems:
        if name is not None and name.startswith('/'):
            moduleName = name[0:blzg.modulePathRegex.match(name).end()]
            modulePrefix = blzg.moduleToNamespacePrefix(db, moduleName)
            shortName = pli.getShortName(value)
            # since we are interning blank nodes in the current module, we could
            # have a module prefix, so we are checking the object name first:
            if shortName.startswith(BLANK_NODE_PREFIX):
                return shortName
            if modulePrefix is not None:
                if modulePrefix == db.getDefaultNamespacePrefix():
                    return shortName
                else:
                    return modulePrefix + ':' + shortName
        return str(value)
    if isinstance(value, pli.StringWrapper):
        value = str(value)
        if litfun.kgtk_literal(value):
            return value
        else:
            return litfun.kgtk_stringify(value)
    elif isinstance(value, (pli.IntegerWrapper, pli.FloatWrapper, pli.LongIntegerWrapper)):
        value = str(value)
        if litfun.kgtk_number(value):
            return value
        else:
            return '+' + value
    else:
        # don't know what it is, treat it as a string:
        return str(value)

def autoTranslateKgtkValueToPowerLoom(db, value, targetType=None):
    """Return a PowerLoom representation of the KGTK term `value'
    depending on the translation policy of 'db'.
    """
    if not db._kypherPliStore.autoTranslate:
        if isinstance(value, (int, float)):
            # keep numbers as is:
            return spi.pythonToStellaTree(value)
        else:
            return pli.createStringWrapper(misc.coerceToBytes(unicode(value)))
    else:
        return coerceKgtkValueToPowerLoom(db, value, targetType=targetType)

def autoTranslatePowerLoomValueToKgtk(db, value, targetType=None):
    """Return a KGTK term translation of the PowerLoom object `value'
    depending on the translation policy of 'db'.
    """
    if not db._kypherPliStore.autoTranslate:
        return str(value)
    else:
        return coercePowerLoomValueToKgtk(db, value, targetType=targetType)


### Specialist computations and ontology:

debugSpecialist = None # or 'trace', 'step'

@lru_cache(maxsize=1000)
def getQueryKypherCache(conn, query, bindings):
    """LRU cache for a query-kypher frame with specific query and binding values.
    This serves primarily as an API-entry point to lru_cache which only supports
    memoization of functions.  The arguments here are all hashable which is not the
    case for some of the query functions used to populate this cache."""
    return []

@pli.specialist(relation='rdbms/query-kypher', module='rdbms/database', create=True, arity=3, varargs=True, defer=True)
def queryKypherSpecialist(frame, lastMove):
    """Specialist for the PowerLoom `rdbms/query-kypher(?db ?query ?x ...)' relation
       which provides a PowerLoom API for the kgtk.kypher.api.execute_query method.
    """
    if debugSpecialist == 'step':
        import pdb
        pdb.set_trace()
    firstArgIndex = 2
    arity = pli.getFrameArity(frame)
    iterator = pli.getFrameIterator(frame)
    
    if iterator is None:
        # first time around, at least the db and query args need to be bound:
        if pli.isFrameBindingPattern(frame, 'BB'):
            db = pli.getNthFrameBinding(frame, 0)
            query = pli.getNthFrameBinding(frame, 1)
            if isinstance(db, pli.LogicObject) and isinstance(query, pli.StringWrapper):
                conn = getKypherPowerLoomConnection(db)
                if conn is None:
                    return pli.TERMINAL_FAILURE
                query = str(query)
                # create a hashable bindings key:
                bindings = tuple([pli.getNthFrameBinding(frame, i) for i in range(firstArgIndex, arity)])
                cache = getQueryKypherCache(conn, query, bindings)
                
                if len(cache) == 0:
                    # in case there were any foreign-language strings in the query, make sure to convert to Unicode:
                    query = misc.coerceToUnicode(query)
                    queryName = query + pli.getFrameBindingPattern(frame)
                    apiQuery = conn.lookup_query(queryName)
                    if apiQuery is None:
                        parameters = spi.stella.pdef.KeyValueList()
                        for i in range(firstArgIndex, arity):
                            arg = pli.getNthFrameArgument(frame, i)
                            if isinstance(arg, pli.PatternVariable):
                                varname = spi.stella.pdef.wrapString(pli.getVariableShortName(arg).lower())
                                value = pli.getNthFrameBinding(frame, i)
                                if value is not None:
                                    value = spi.stella.pdef.wrapString(f'$`_{i}_`')
                                parameters.insertAt(varname, value)
                        query = spi.rdbms.pdef.sqlQueryInstantiateConstraints(query, parameters)
                        # since we are caching here, we don't have to do it in the API:
                        apiQuery = conn.get_query(name=queryName, cmd=query, maxcache=0)
                        
                    bindingDict = {f'_{i+firstArgIndex}_': autoTranslatePowerLoomValueToKgtk(conn, v)
                                   for i, v in enumerate(bindings) if v is not None}
                    result = apiQuery.execute(fmt='list', **bindingDict)
                    solutions = spi.pythonToStellaTree(result)
                    cache.append(solutions)
                iterator = pli.consToPlIterator(cache[0])
                pli.setFrameIterator(frame, iterator)
                
    if iterator is None:
        return pli.TERMINAL_FAILURE
    db = pli.getNthFrameBinding(frame, 0)
    conn = getKypherPowerLoomConnection(db)
    
    # generate solutions:
    bindingState = pli.getFrameBindingState(frame)
    for row in iterator:
        row = list(row)
        bindingFailure = False
        for ci, i in enumerate(range(firstArgIndex, arity)):
            # TO DO: get the proper target type supplied here to force mapping to strings:
            value = autoTranslateKgtkValueToPowerLoom(conn, row[ci].unwrapLiteral())
            if not pli.setNthFrameBinding(frame, i, value):
                bindingFailure = True
                break
        if not bindingFailure:
            # we successfully consumed a whole output row:
            return pli.CONTINUING_SUCCESS
        else:
            pli.setFrameBindingState(frame, bindingState)
    return pli.TERMINAL_FAILURE


@pli.computation(function='RDBMS/kgtk-to-powerloom', module='PL-KERNEL', create=True, defer=True)
def kgtkToPowerLoomComputation(db, value):
    """Computation function for PowerLoom function `RDBMS/kgtk-to-powerloom (?db (?value string) ?pl-value)'.
    """
    try:
        if isinstance(db, pli.LogicObject) and isinstance(value, (pli.StringWrapper, pli.NumberWrapper)):
            conn = getKypherPowerLoomConnection(db)
            if conn is not None:
                return coerceKgtkValueToPowerLoom(conn, value.unwrapLiteral())
    except:
        pass
    return None

@pli.computation(function='RDBMS/powerloom-to-kgtk', module='PL-KERNEL', create=True, defer=True)
def powerLoomToKgtkComputation(db, value):
    """Computation function for PowerLoom function `RDBMS/powerloom-to-kgtk (?db ?value (?kgtk-value STRING))'.
    """
    try:
        if isinstance(db, pli.LogicObject):
            conn = getKypherPowerLoomConnection(db)
            if conn is not None:
                return pli.createStringWrapper(coercePowerLoomValueToKgtk(conn, value))
    except:
        pass
    return None


ontology = """(progn

(defconcept RDBMS/Graph-Database (RDBMS/Database)
  :documentation "Information defining a graph database.")

(defconcept RDBMS/Kypher-Database (RDBMS/Graph-Database)
  :documentation "Information defining a KGTK database supporting Kypher queries.")

(deffunction RDBMS/default-namespace ((?db RDBMS/Kypher-Database)) :-> (?namespace STRING)
  :documentation "Default namespace prefix to assume for translation of unqualified KGTK symbols.
This can be used for both regular and XMLNS databases, since translation could be explicitly
invoked via the two conversion computations.")

(defrelation RDBMS/auto-translate ((?db RDBMS/Database))
  :documentation "Automatically translate database values to and from PowerLoom")
)
"""

pli.evalDeferred(pli.eval, 'RDBMS', ontology, module='PL-KERNEL')

# If possible, execute PowerLoom definitions in the current environment, otherwise this has to be called again later:
pli.processDeferredCommands()
