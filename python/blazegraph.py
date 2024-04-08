#!/usr/bin/env python-pli

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


from __future__ import print_function, division, absolute_import

import sys
PY2 = sys.version_info[0] == 2
PY3 = sys.version_info[0] >= 3
if PY3:
    unicode = str
    basestring = (bytes, unicode)
    long = int

import os
import os.path
import atexit
import re
import json
import xmltodict

if PY3:
    from io import StringIO
    from functools import lru_cache
else:
    from StringIO import StringIO
    from functools32 import lru_cache

# debugging:
from contexttimer import Timer
import pprint
pp = pprint.PrettyPrinter(indent=4)
"""
pp.pprint(<object>)
"""

import rdflib
import rdflib.namespace as rdfns
from rdflib.plugins.stores.sparqlstore import SPARQLStore
from rdflib.plugins.stores.sparqlstore import SPARQLUpdateStore
from rdflib.graph import DATASET_DEFAULT_GRAPH_ID
import uuid
import requests
import socket

# work around a bug with RDFLib's use of `keepalive' - if we let it
# use it, it keeps leaking TCP file descriptors in CLOSE_WAIT mode
# which eventually breaks with too many open files:
def setUseKeepAlivePatch(self):
    pass
SPARQLStore.setUseKeepAlive = setUseKeepAlivePatch

import misc


### NOTES:

# - See here for examples:
#   https://wiki.blazegraph.com/wiki/index.php/Sesame_API_embedded_mode
# - server invocation:
#   $BLZG_HOME/bin/blazegraph.sh start
# - Execution Timing
#   >>> with Timer() as t:
#   ...     dataframe = pandas.read_sql('select count(*) from opera5.bigmech_events.doc', conn)
#   >>> print t.elapsed
#   0.17404294014
# - we should declare a vocabulary for more efficient storage of ontology predicates and types;
#   this also avoids additional lookups during result materialization; there already is a default
#   RDFSVocabulary with ~300 terms, but we should add stuff we need for AIL, etc.
# - we can define our own SERVICE which can be referenced in SPARQL queries, for example, to
#   specify an initial set of URIs to query over without having to make them into a graph
#   (see Blazegraph SPARQL extensions docs)


### Blazegraph environment and server invocation options:

class ConfigDict(object):
    """Simple config object that remembers insertion order and supports value evaluation."""
    def __init__(self):
        vars(self)['__keys'] = []
    # trying to do this based on OrderedDict proved 'impossible' for Py2:
    def __setattr__(self, name, value):
        if name not in vars(self)['__keys']:
            vars(self)['__keys'].append(name)
        super(ConfigDict, self).__setattr__(name, value)
    def keys(self):
        return vars(self)['__keys']
    def getvalue(self, key):
        val = vars(self)[key]
        if isinstance(val, str) and val.startswith('#!'):
            val = eval(val[2:])
            vars(self)[key] = val
        return val

config = ConfigDict()

config.blazegraphVersion = '2.1.4'
config.blazegraphCodeLocations = '/opt'
config.blazegraphHome = """#!os.environ.get('BLZG_HOME', misc.findFileInPath('blazegraph-tgz-' + config.blazegraphVersion, config.blazegraphCodeLocations, error=False))"""
# TO DO: improve the configuration of this, the value in the config file seems to dominate this:
config.blazegraphDataLocations = """#!os.path.join('/data/blazegraph/', config.blazegraphVersion, 'data') + ':' + os.path.join(config.blazegraphHome, 'data')"""
config.blazegraphDataPath = """#!misc.findFileInPath(os.curdir, config.blazegraphDataLocations, error=True)"""
config.blazegraphConfPath = """#!os.path.join(config.blazegraphHome, 'conf')"""
config.blazegraphLogPath  = """#!os.path.join(config.blazegraphHome, 'log')"""
config.blazegraphWebPath  = """#!os.path.join(config.blazegraphHome, 'war')"""
config.blazegraphPropertiesFile = """#!os.path.join(config.blazegraphConfPath, "RWStore.properties")"""

config.javaClasspath = """#![
    config.blazegraphConfPath,
    os.path.join(config.blazegraphHome, 'lib/*')]"""

config.javaOptions = """#![
     #'-Djava.util.logging.config.class=org.slf4j.bridge.SLF4JBridgeHandler',
     #'-XX:+PrintGCDetails',
     #'-XX:+PrintGCDateStamps',
     #'-Xloggc:' + os.path.join(config.blazegraphLogPath, 'server.gc'),
     #'-Dblazegraph.log.path=' + config.blazegraphLogPath,
     '-Xmx8192m', #'-Xmx16384m', #'-Xmx4096m',
     '-XX:MaxDirectMemorySize=8192m', #'-XX:MaxDirectMemorySize=16384m',
     #'-XX:+HeapDumpOnOutOfMemoryError',
     #'-XX:HeapDumpPath='  + config.blazegraphLogPath
    ]"""

config.javaHomeLocations = '/opt/jdk1.8:/usr/lib/jvm/java-8-oracle:/usr/lib/jvm/java-8-openjdk-amd64'

config.defaultProperties = """#!{
    Options.BUFFER_MODE: BufferMode.DiskRW,
    # we set this here to something nonsensical to make sure it gets set explicitly:
    BigdataSailOptions.NAMESPACE: "nosuchdataset",
    }"""

def getNanoSparqlServerHost():
    """Mirror com.bigdata.rdf.sail.webapp.NanoSparqlServer.getHost()."""
    return NicUtil.getIpAddress("default.nic", "default", True) or Httpd_Config.DEFAULT_HOST

config.jettyProperties = """#!{
    "jetty.host": getNanoSparqlServerHost(),
    "jetty.port": "9999",
    "jetty.resourceBase": config.blazegraphWebPath,
    "jetty.home": config.blazegraphWebPath,
    "jetty.overrideWebXml": os.path.join(config.blazegraphWebPath, "WEB-INF/override-web.xml"),
    "JETTY_XML": os.path.join(config.blazegraphConfPath, "jetty.xml"),
    "java.util.logging.config.file": os.path.join(config.blazegraphConfPath, "logging.properties"),
    "log4j.configuration": os.path.join(config.blazegraphConfPath, "log4j.properties"),
    }"""

config.temporaryInstancePortRange = (9950, 9998)
config.temporaryInstanceInitialExtent = 104857600
config.temporaryInstanceJournalFile = None
config.temporaryInstanceJettyPort = None


def configure():
    """Configure Blazegraph and relevant Java options and classes.  This also configures the
    Java VM which cannot be reconfigured once jnius has been loaded.  Any deferred #! config
    options will be evaluated in order at this time.  This allows us to import the module,
    change some configuration values, and then configure and run Blazegraph accordingly once a
    connection is opened for the first time.
    """
    module = sys.modules[__name__]
    if getattr(module, 'jnius', None) is not None:
        return
    for key in config.keys():
        value = config.getvalue(key)
        if key == 'blazegraphHome':
            # done with core blazegrap options:
            if config.blazegraphHome is None or not os.path.exists(os.path.join(config.blazegraphHome, 'conf', 'blazegraph')):
                raise Exception('Unable to determine a valid Blazegraph home directory - set BLZG_HOME env variable if necessary')
            os.environ['BLZG_HOME'] = config.blazegraphHome
        elif key == 'javaHomeLocations':
            # done with Java options:
            os.environ['JAVA_HOME'] = os.environ.get('JAVA_HOME', misc.findFileInPath(os.curdir, config.javaHomeLocations))
            import jnius_config
            setattr(module, 'jnius_config', jnius_config)
            # we add to options and classpath in case other Java packages are used as well;
            # if that is a problem, call jnius_config.set_options/classpath() first to clear:
            jnius_config.add_options(*config.javaOptions)
            jnius_config.add_classpath(*config.javaClasspath)
            import jnius
            setattr(module, 'jnius', jnius)
            defineJavaClasses()
            

### Namespaces and RDF Constants

from rdflib.namespace import XSD, RDF, RDFS, OWL

standardNamespaces = {
    'xsd': XSD,
    'rdf': RDF,
    'rdfs': RDFS,
    'owl': OWL,
}

def getNamespacePrefixDeclarations(nsBindings):
    decls = StringIO()
    for key, value in nsBindings.items():
        decls.write("PREFIX %s: <%s>\n" % (key, str(value)))
    return decls.getvalue()

def getNamespaceManager(nsBindings):
    nsm = rdfns.NamespaceManager(rdflib.Graph())
    for key, value in nsBindings.items():
        nsm.bind(key, value, override=True, replace=False)
    return nsm

# TO DO:
# - currently rdflib.namespace.split_uri() doesn't work on URIs like the following,
#   apparently they are valid URIs in general but not for RDF terms - investigate that:
#     "http://en.wikipedia.org/wiki/2014"
#     "http://en.wikipedia.org/wiki/Moire_(fabric)"
#     "http://en.wikipedia.org/wiki/Talbott,_Tennessee"

def uriToQualifiedName(uri, nsm):
    """More robust version of nsm.compute_qname that doesn't break on undefined
    prefixes or bad URI's such as 'http://en.wikipedia.org/wiki/2014'.
    """
    if not isinstance(uri, rdflib.term.URIRef):
        uri = rdflib.term.URIRef(uri)
    try:
        prefix, nsuri, name = nsm.compute_qname(uri, generate=False)
    except:
        # try to work around the invalid URI issues identified above by
        # substituting a name we know is legal and see if that succeeds:
        sp = uri.rfind('#')
        if sp < 0:
            sp = uri.rfind('/')
        if sp > 0:
            origName = uri[sp+1:]
            tempName = 'tEmP0rArY_'
            try:
                # call 'compute_qname' directly to prevent infinite recursion:
                prefix, nsuri, name = nsm.compute_qname(rdflib.term.URIRef(uri[0:sp+1] + tempName), generate=False)
                if prefix is not None:
                    name = name.replace(tempName, origName)
                    return prefix, nsuri, name
            except:
                pass
        # no prefix defined or not splittable, return the bare URI in lieu of the name:
        prefix, nsuri, name = None, None, uri
    return prefix, nsuri, name


### Conversion utilities:

def Value_str(self):
    "Treat `str' calls on Java OpenRDF Value objects equivalently to rdflib.term's."
    return self.stringValue()

def Value_unicode(self):
    "Treat `unicode' calls on Java OpenRDF Value objects equivalently to rdflib.term's."
    return unicode(self.stringValue())

# moved into defineJavaClasses():
#Value.__str__ = Value_str
#BigdataValue.__str__ = Value_str          # needed even though it extends Java Value
#Value.__unicode__ = Value_unicode
#BigdataValue.__unicode__ = Value_unicode  # needed even though it extends Java Value


### Server configuration:

def dictToJavaProps(dict, props=None):
    "Convert `dict' into a set of Java Properties.  Add to/modify `props' if supplied."
    if props is None:
        props = Properties()
    for key, val in dict.items():
        props.put(key, val)
    return props

def fileToJavaProps(file, props=None):
    "Read `file' into a set of Java Properties.  Add to/modify `props' if supplied."
    if props is None:
        props = Properties()
    fis = FileReader(file)
    try:
        props.load(fis)
    finally:
        fis.close()
    return props

def setJavaSystemProps(dict):
    "Set Java System properties from properties defined in `dict'."
    system = jnius.autoclass('java.lang.System')
    for key, val in dict.items():
        system.setProperty(key, val)

def getProperties():
    "Return the set of configured Java Properties to contol the Blazegraph server."
    props = fileToJavaProps(config.blazegraphPropertiesFile)
    props = dictToJavaProps(config.defaultProperties, props)
    return props


class Blazegraph(object):
    """
    Captures various connection and API methods necessary to communicate with a Blazegraph KB.
    We have three internal connection types to the SailRepository, the Sail and the associated
    LocalTripleStore database.  Those are for high-speed queries that go directly through the
    Java API to connect to a local server instance.  These are configured for a single dataset
    (or namespace) which must already exist and be provided at store creation time.  All methods
    that do not have a `dataset' parameter either don't care or go to the provided default dataset.

    We also have Rest API calls and an rdflib SparqlStore which all connect to a locally running
    NanoSparqlServer.  The associated methods all do consider a `dataset' parameter.  Due to some
    locking issues, update methods need to temporarily close any Sail connections before they run.
    """
    def __init__(self, dataset, journalFile=None, port=None, props=None, initNs=standardNamespaces):
        configure()
        if not isinstance(dataset, str):
            raise Exception('Illegal dataset or namespace: ' + str(dataset))
        self.dataset = dataset
        if props is None:
            props = getProperties()
        props.setProperty(BigdataSailOptions.NAMESPACE, self.dataset)
        if journalFile is not None:
            props.setProperty('com.bigdata.journal.AbstractJournal.file', journalFile)
        if port is not None:
            config.jettyProperties["jetty.port"] = str(port)
        self.sail = BigdataSail(props)
        self.repository = BigdataSailRepository(self.sail)
        self.repository.initialize()
        self.connection = None
        self.sailConnection = None
        self.tripleStore = None
        self.sparqlServer = None
        self.sparqlServiceBaseUri = None
        self.sparqlStores = {}
        self.nsBindings = initNs or {}
        self.nsManager = None
        self.nsPrefixes = None

    def getDataset(self):
        return self.dataset

    def getSail(self):
        return self.sail

    def getRepository(self):
        return self.repository

    def getConnection(self):
        if self.connection is None:
            self.connection = self.repository.getConnection()
        return self.connection

    def closeConnection(self):
        self.closeSailConnection()
        if self.connection is not None and self.connection.isOpen():
            self.connection.close()
            self.connection = None

    def getSailConnection(self):
        if self.sailConnection is None:
            self.sailConnection = jnius.cast(BigdataSailConnection, self.getConnection().getSailConnection())
        return self.sailConnection

    def closeSailConnection(self):
        if self.sailConnection is not None and self.sailConnection.isOpen():
            self.sailConnection.close()
        self.sailConnection = None
        self.tripleStore = None

    def getTripleStore(self):
        if self.tripleStore is None:
            self.tripleStore = self.getSailConnection().getTripleStore()
        return self.tripleStore

    def getSparqlServer(self):
        if self.sparqlServer is None:
            setJavaSystemProps(config.jettyProperties)
            jettyXml = config.jettyProperties["JETTY_XML"]
            initProps = {
                ConfigParams.PROPERTY_FILE: config.blazegraphPropertiesFile,
                ConfigParams.NAMESPACE: self.dataset, 
                ConfigParams.QUERY_THREAD_POOL_SIZE: str(ConfigParams.DEFAULT_QUERY_THREAD_POOL_SIZE),
                ConfigParams.FORCE_OVERFLOW: 'false',
                #ConfigParams.READ_LOCK: None,
                }
            initProps = dictToJavaProps(initProps)
            self.sparqlServer = NanoSparqlServer.newInstance(jettyXml, self.getSail().indexManager, initProps)
            NanoSparqlServer.awaitServerStart(self.sparqlServer)
            self.sparqlServiceBaseUri = self.sparqlServer.getURI().toString()
        return self.sparqlServer

    # NanoSparqlServer active URIs:
    # - http://HOST:PORT/blazegraph - help page / console (the serviceURL)
    # - http://HOST:PORT/blazegraph/sparql - REST API (the SparqlEndpoint, uses the default namespace)
    # - http://HOST:PORT/blazegraph/namespace/kb/sparql - REST API for specific namespace
    # - http://HOST:PORT/blazegraph/status - Status page
    # - http://HOST:PORT/blazegraph/counters - Performance counters

    def getSparqlServiceBaseUri(self):
        self.getSparqlServer()
        return self.sparqlServiceBaseUri

    def getSparqlServiceRestUri(self, dataset=None):
        serviceUri = self.getSparqlServiceBaseUri()
        if dataset is not None:
            return serviceUri + 'blazegraph/namespace/' + dataset + '/sparql'
        else:
            return serviceUri + 'blazegraph/sparql'

    # ISSUE: queries that use GET must be less than 8192 characters long, which
    # is difficult to check due to namespace prefix injection by rdflib which
    # comes too late in the process and can be quite large.  For this reason we
    # now use POST by default which does't have this limitation.  Further complicating
    # this is that the parameters and API changed between rdflib 4 vs. 6, previously
    # it was store.query_method while now it is store.method; so we now always
    # specify this when we create the store object, using the appropriate parameter.
    # Adaptation can still be done on the fly by updating store.(query_)method.
    DEFAULT_QUERY_METHOD = 'POST'

    def getSparqlStore(self, dataset=None):
        store = self.sparqlStores.get(dataset or self.dataset)
        if store is None:
            sparqlEndpointUri = self.getSparqlServiceRestUri(dataset=dataset)
            if hasattr(SPARQLUpdateStore, 'method'):
                # should work for rdflib 6.0 or later:
                store = SPARQLUpdateStore(sparqlEndpointUri, method=self.DEFAULT_QUERY_METHOD)
            else:
                # should work for rdflib 4.x:
                store = SPARQLUpdateStore(sparqlEndpointUri, default_query_method=self.DEFAULT_QUERY_METHOD)
            self.sparqlStores[dataset] = store
            self.updateNamespaces(store)
        return store

    def close(self):
        for store in self.sparqlStores.values():
            store.close()
        self.sparqlStores = {}
        if self.sparqlServer is not None:
            self.sparqlServer.stop()
        self.closeConnection()
        self.repository.shutDown()

    def isOpen(self):
        return self.repository is not None and self.repository.isInitialized()

    def getNamespaceBindings(self):
        return self.nsBindings

    def getNamespaceManager(self):
        if self.nsManager is None:
            self.nsManager = getNamespaceManager(self.nsBindings)
            for store in self.sparqlStores.values():
                self.updateNamespaces(store)
        return self.nsManager

    def getNamespacePrefixes(self):
        if self.nsPrefixes is None:
            self.nsPrefixes = getNamespacePrefixDeclarations(self.nsBindings)
        return self.nsPrefixes

    def bindNamespace(self, prefix, namespace):
        self.getNamespaceBindings()[prefix] = namespace
        self.nsManager = None
        self.nsPrefixes = None

    def updateNamespaces(self, store):
        #for key, value in self.getNamespaceManager().namespaces():
        #    store.bind(key, value)
        store.nsBindings.update(dict(self.getNamespaceManager().namespaces()))

    DUMMY_INIT_NS = {'dUmmY_314159__': RDF}

    def _patchInitNs(self, initNs):
        # BUG/misfeature in RDFLib 6.0.0: if 'initNs' passed to the query is empty,
        # the internal nsBindings added via _inject_prefixes will not be added,
        # so here we ensure that 'initNs' is not empty:
        return initNs or self.DUMMY_INIT_NS

    def query(self, sparqlQuery, initNs={}, dataset=None):
        "Run a `sparqlQuery' through the RDFLib SPARQLStore REST API."
        store = self.getSparqlStore(dataset=dataset)
        return store.query(sparqlQuery, self._patchInitNs(initNs))

    def rowToVars(self, row):
        "Extract the list of column variables for query result `row'."
        items = list(row.labels.items()) 
        items.sort(key = lambda tup: tup[1])
        for i in range(len(items)):
            items[i] = '?' + items[i][0]
        return items

    def columnToValue(self, value, nsm=None):
        "Convert query result column `value' to a Python value."
        if isinstance(value, rdflib.URIRef):
            # try to abbreviate to a prefixed version if possible:
            nsm = nsm or self.getNamespaceManager()
            prefix, nsUri, name = uriToQualifiedName(value, nsm)
            if prefix is not None:
                return prefix + ':' + name
        if value is not None:
            return value.toPython()
        else:
            return None

    def columnToN3Value(self, value, nsm=None):
        "Convert query result column `value' to an N3 representation."
        if isinstance(value, rdflib.URIRef):
            # try to abbreviate to a prefixed version if possible:
            nsm = nsm or self.getNamespaceManager()
            prefix, nsUri, name = uriToQualifiedName(value, nsm)
            if prefix is not None:
                return prefix + ':' + name
        if value is not None:
            return value.n3()
        else:
            return None

    def rowToValues(self, row, nsm=None):
        "Convert query result `row' to a list of Python values."
        nsm = nsm or self.getNamespaceManager()
        return [self.columnToValue(val, nsm) for val in row]

    def rowToN3Values(self, row, nsm=None):
        "Convert query result `row' to a list of N3 values."
        nsm = nsm or self.getNamespaceManager()
        return [self.columnToN3Value(val, nsm) for val in row]

    limitRegex = re.compile('(limit|LIMIT)\\s+[0-9]+')

    def ppquery(self, sparqlQuery, limit=10, initNs={}, dataset=None, out=sys.stdout):
        "Run a SELECT `sparqlQuery' through the RDFLib SPARQLStore REST API and pretty print the result."
        if limit > 0 and not self.limitRegex.search(sparqlQuery):
            sparqlQuery = sparqlQuery + ' LIMIT ' + str(limit)
        store = self.getSparqlStore(dataset=dataset)
        nsm = None
        variables = None
        indices = None
        for row in store.query(sparqlQuery, self._patchInitNs(initNs)):
            if variables is None:
                nsm = self.getNamespaceManager()
                variables = self.rowToVars(row)
                indices = range(len(variables))
                # with multi-line queries we need a fresh line:
                if sparqlQuery.find('\n') >= 0:
                    out.write('\n')
            values = self.rowToValues(row, nsm)
            for idx in indices:
                out.write('%s=%s\t ' % (variables[idx], values[idx]))
            out.write('\n')
            limit -= 1
            if limit == 0:
                break

    def countTriples(self, dataset=None):
        """Return the total number of triples currently loaded in `dataset'."""
        return list(self.query("SELECT (COUNT(*) AS ?no) { ?s ?p ?o }", dataset=dataset))[0][0].toPython()

    def update(self, command, initNs=None, commit=True, dataset=None):
        # not sure this actually works - we might have to use Rest API instead.
        store = self.getSparqlStore(dataset=dataset)
        self.closeConnection() # close any open connections to avoid hanging
        # this is what we would like to call, but there seems to be a bug in RDFLib 4.2.2, where
        # updates inject namespace prefixes twice, which upsets Blazegraph, so we work around that:
        #store.update(command, initNs=initNs)
        assert store.endpoint
        assert isinstance(command, basestring)
        if initNs is not None:
            store.setNamespaceBindings(initNs)
        store._transaction().append(command)
        if commit:
            store.commit()

    def clearDataset(self, dataset=None):
        restUri = self.getSparqlServiceRestUri(dataset=dataset)
        headers = {}
        params = {'update': 'DROP ALL;'}
        self.closeConnection() # close any open connections to avoid hanging
        resp = requests.post(restUri, headers=headers, params=params)
        resp.raise_for_status()
        return resp

    def createDataset(self, dataset):
        # first retrieve the properties of the configured dataset but for the new one:
        restUri = self.getSparqlServiceBaseUri() + 'blazegraph/namespace/prepareProperties'
        headers = {'Content-Type': 'text/plain'}
        props = BigdataSailOptions.NAMESPACE + '=' + dataset + '\n'
        resp = requests.post(restUri, headers=headers, data=props)
        resp.raise_for_status()
        # then use the retrieved props to create the new dataset:
        restUri = self.getSparqlServiceBaseUri() + 'blazegraph/namespace'
        props = resp.text
        headers = {'Content-Type': 'application/xml'}
        self.closeConnection() # close any open connections to avoid hanging
        resp = requests.post(restUri, headers=headers, data=props)
        resp.raise_for_status()
        return resp

    def getDatasetProperties(self, dataset):
        """Retrieve the properties for the existing `dataset' as a dictionary.
        Raises an error if `dataset' does not yet exist.
        """
        restUri = self.getSparqlServiceBaseUri() + 'blazegraph/namespace/' + dataset + '/properties'
        headers = {'Accept': 'application/xml'}
        self.closeConnection() # close any open connections to avoid hanging
        resp = requests.get(restUri, headers=headers)
        resp.raise_for_status()
        props = {}
        for prop in xmltodict.parse(resp.text).get('properties').get('entry'):
            props[prop['@key']] = prop['#text']
        return props

    def hasDataset(self, dataset):
        "Return True if `self' has `dataset' existing on it."
        # TO DO: this currently shows a Java exception stack trace, figure out if there is a cleaner way
        try:
            return dataset in self.getDatasetNames()
        except:
            return False

    def deleteDataset(self, dataset):
        restUri = self.getSparqlServiceBaseUri() + 'blazegraph/namespace/' + dataset
        self.closeConnection() # close any open connections to avoid hanging
        resp = requests.delete(restUri)
        resp.raise_for_status()
        if dataset == self.dataset:
            self.close()
        return resp

    def getDatasetNames(self):
        """Retrieve a list of dataset names currently configured for `self'."""
        restUri = self.getSparqlServiceBaseUri() + 'blazegraph/namespace'
        headers = {'Accept': 'text/plain'}
        self.closeConnection() # close any open connections to avoid hanging
        resp = requests.get(restUri, headers=headers)
        resp.raise_for_status()
        text = resp.text
        key = '<http://purl.org/dc/terms/title> "'
        datasets = []
        start = 0
        # since this could be a long list, we are parsing like this instead of doing splitlines():
        while start >= 0:
            start = text.find(key, start)
            if start < 0:
                break
            start = start + len(key)
            end = text.find('" .\n', start)
            datasets.append(text[start:end])
            start = end
        return datasets

    def loadFile(self, file, dataset=None):
        file = os.path.abspath(file)
        if not os.path.exists(file):
            raise Exception("file does not exist: " + str(file))
        restUri = self.getSparqlServiceRestUri(dataset=dataset)
        headers = {}
        params = {'update': 'LOAD <file://%s>;' % file}
        self.closeConnection() # close any open connections to avoid hanging
        resp = requests.post(restUri, headers=headers, params=params)
        resp.raise_for_status()
        return resp

    bulkLoadPropertiesTemplate = """
<?xml version="1.0" encoding="UTF-8" standalone="no"?> 
<!DOCTYPE properties SYSTEM "http://java.sun.com/dtd/properties.dtd"> 
<properties>
  <!-- RDF Format (Default is rdf/xml)
    <entry key="format">rdf/xml</entry> -->
  <!-- Base URI (Optional) 
    <entry key="baseURI"></entry> -->
  <entry key="defaultGraph">%s</entry> 
  <entry key="verbose">1</entry>
  <entry key="closure">false</entry> 
  <entry key="durableQueues">false</entry>
  <entry key="com.bigdata.rdf.store.DataLoader.flush">false</entry>
  <entry key="com.bigdata.rdf.store.DataLoader.ignoreInvalidFiles">true</entry>
  <entry key="namespace">%s</entry>
  <entry key="propertyFile">%s</entry> 
  <entry key="fileOrDirs">%s</entry>
</properties>
""".strip()

    def bulkLoadFiles(self, files, dataset=None):
        normalizedFiles = []
        for file in misc.listify(files):
            file = os.path.abspath(file)
            if not os.path.exists(file):
                raise Exception("file does not exist: " + str(file))
            normalizedFiles.append(file)
        loaderProps = self.bulkLoadPropertiesTemplate % (
            'http://systap.com/',
            dataset or self.dataset,
            config.blazegraphPropertiesFile,
            ','.join(normalizedFiles))
        restUri = self.getSparqlServiceBaseUri() + 'blazegraph/dataloader'
        headers = {'Content-Type': 'application/xml'}
        self.closeConnection() # close any open connections to avoid hanging
        resp = requests.post(restUri, headers=headers, data=loaderProps)
        resp.raise_for_status()
        return resp

    def exportKb(self, outDir, format='trig', includeInferred=False, dataset=None):
        if dataset is not None and dataset != self.dataset:
            raise Exception('Can only save KB in default dataset, close and reopen with that')
        # promote this somewhere and make it more robust:
        rdfFormats = {'trig': RDFFormat.TRIG,
                      'trix': RDFFormat.TRIX,
                      'nt':   RDFFormat.NTRIPLES,
                      'rdfxml': RDFFormat.RDFXML,
                      'turtle': RDFFormat.TURTLE,
                      'ttl': RDFFormat.TURTLE,
                      'jsonld': RDFFormat.JSONLD,
                      }
        format = rdfFormats[format]
        sailConn = self.getSailConnection()
        ExportKB(sailConn, JavaFile(outDir), format, includeInferred).export()


"""
>>> bs.createDataset('operabig')
<Response [201]>
>>> resp=bs.bulkLoadFiles(['/data/tmp/bellingcat-multiplied'], dataset='operabig')
>>> print resp.text
<?xml version="1.0"?><data modified="0" milliseconds="126271"/>DATALOADER-SERVLET: Loaded operabig with properties: /opt/blazegraph-tgz-2.1.4/conf/RWStore.properties
>>> bs.ppquery("SELECT (COUNT(*) AS ?no) { ?s ?p ?o }", dataset='operabig')
?no=7353177	 
"""

currentBlazegraph = None

def getCurrentBlazegraph():
    """Accessor to facilitate variable access from other modules."""
    global currentBlazegraph
    return currentBlazegraph

def setCurrentBlazegraph(blzg):
    """Accessor to facilitate variable access from other modules."""
    global currentBlazegraph
    currentBlazegraph = blzg

def getBlazegraph(blzg=None, dataset=None, journalFile=None, port=None, initNs=standardNamespaces):
    """Get the currently running Blazegraph instance or re/open a new one according to `dataset' and `initNs'.
    This assumes that at all times we have at most one embedded Blazegraph database instance running."""
    global currentBlazegraph
    if blzg is not None:
        return blzg
    if dataset is None and currentBlazegraph is not None:
        dataset = currentBlazegraph.getDataset()
    if currentBlazegraph is None or not currentBlazegraph.isOpen():
        currentBlazegraph = Blazegraph(dataset=dataset, journalFile=journalFile, port=port, initNs=initNs)
    return currentBlazegraph


def getSailConn():
    # For backwards compatibility with some of the early experiments below.
    blzg = getBlazegraph()
    return blzg.getSail(), blzg.getSailConnection(), blzg.getTripleStore()

def getRepoConn():
    # For backwards compatibility with some of the early experiments below.
    blzg = getBlazegraph()
    return blzg.getRepository(), blzg.getConnection()


### Temporary triple store instance

# The current implementation opens a BigdataSail instance which is tied to a single triple store DB.
# If we want to run a BG from a different Python process, we cannot open that again since the DB is locked.
# There are two possibilities to get multiple tenants running:
# (1) have a central server running and then have everybody else connect to it via REST API - that would be
#     the traditional way to go
# (2) allow temporary DB instances that have their private journal file defined in RWStore.properties
#     and that run a Jetty server on a private port to not intefere with other processes; the way to do this is to
#     - bind an open port in a range
#     - once port is bound ensure that /data/blazegraph/2.1.4/data/blazegraph-<port>.jnl does not yet exist
#       (if it exists find the next open port)
#     - now create the file - initialize it so it is usable by Blazegraph - touching it seems to work
#     - close the port, change the properties to use that file and the open port we found
#     - now open the temporary DB instance relative to the new properties
#     - atexit ensure the port is closed and the DB file is deleted

def configureTemporaryInstance():
    """Configure a temporary Blazegraph instance that will run with its own temporary journal file
    and use a private port for its NanoSparqlServer service.  At exit the most recently configured
    temporary instance will be deleted.  Configuration will not do anything by itself, it only sets
    up properties which will come into effect once the Blazegraph instance is started.
    """
    configure()
    if config.temporaryInstanceJournalFile is not None:
        raise Exception('Temporary instance is already configured, delete it first before creating a new one')
    host = getNanoSparqlServerHost()
    portMin = config.temporaryInstancePortRange[0]
    portMax = config.temporaryInstancePortRange[1]
    sock = None
    journalFile = None
    jettyPort = None
    for port in range(portMin, portMax + 1):
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            # we use binding the socket to a port as a lock which will prevent others from using the same:
            sock.bind((host, port))
            jnlFile = os.path.join(config.blazegraphDataPath, 'blazegraph-' + str(port) + '.jnl')
            if not os.path.exists(jnlFile):
                open(jnlFile, 'w').close()
                # once the temporary instance file has been successfully created, we can close the socket:
                # TO DO: there is a possibility that another, unrelated service starts using the port we
                # just reserved before we reopen it, keeping it open would prevent that - should we?
                sock.close()
                journalFile = jnlFile
                jettyPort = port
                break
            sock.close()
        except:
            if sock is not None:
                sock.close
    if journalFile is None:
        raise Exception('Unable to configure temporary triple store instance in port range')
    config.defaultProperties['com.bigdata.journal.AbstractJournal.file'] = journalFile
    config.defaultProperties['com.bigdata.journal.AbstractJournal.initialExtent'] = str(config.temporaryInstanceInitialExtent)
    config.defaultProperties['com.bigdata.journal.AbstractJournal.maximumExtent'] = str(config.temporaryInstanceInitialExtent)
    config.jettyProperties["jetty.port"] = str(jettyPort)
    config.temporaryInstanceJournalFile = journalFile
    config.temporaryInstanceJettyPort = jettyPort
    return journalFile, jettyPort

def cleanupTemporaryInstance():
    if currentBlazegraph is not None and currentBlazegraph.isOpen():
        try:
            currentBlazegraph.close()
        except:
            pass
    if config.temporaryInstanceJournalFile is not None:
        try:
            os.remove(config.temporaryInstanceJournalFile)
        except:
            pass
    config.temporaryInstanceJournalFile = None
    config.temporaryInstanceJettyPort = None

atexit.register(cleanupTemporaryInstance)


### Jnius support

def defineJavaClass(name, javaClass, module=None):
    """Define `javaClass' using jnius.autoclass and bind module.name to its result.
    """
    if module is None:
        module = sys.modules[__name__]
    setattr(module, name, jnius.autoclass(javaClass))

def defineJavaClasses():
    """Import often-used Java classes and make them available as module variables.
    """
    mod = sys.modules[__name__]
    defineJavaClass('JavaObject', 'java.lang.Object', module=mod)
    defineJavaClass('JavaFile', 'java.io.File', module=mod)
    defineJavaClass('FileReader', 'java.io.FileReader', module=mod)
    defineJavaClass('StringBuilder', 'java.lang.StringBuilder', module=mod)
    defineJavaClass('Collections', 'java.util.Collections', module=mod)
    defineJavaClass('Properties', 'java.util.Properties', module=mod)

    defineJavaClass('OpenRDFException', 'org.openrdf.OpenRDFException', module=mod)
    defineJavaClass('BNode', 'org.openrdf.model.BNode', module=mod)
    defineJavaClass('Literal', 'org.openrdf.model.Literal', module=mod)
    defineJavaClass('Resource', 'org.openrdf.model.Resource', module=mod)
    defineJavaClass('Statement', 'org.openrdf.model.Statement', module=mod)
    defineJavaClass('URI', 'org.openrdf.model.URI', module=mod)
    defineJavaClass('Value', 'org.openrdf.model.Value', module=mod)
    Value.__str__ = Value_str
    Value.__unicode__ = Value_unicode
    defineJavaClass('LiteralImpl', 'org.openrdf.model.impl.LiteralImpl', module=mod)
    defineJavaClass('StatementImpl', 'org.openrdf.model.impl.StatementImpl', module=mod)
    defineJavaClass('URIImpl', 'org.openrdf.model.impl.URIImpl', module=mod)
    defineJavaClass('BindingSet', 'org.openrdf.query.BindingSet', module=mod)
    defineJavaClass('QueryLanguage', 'org.openrdf.query.QueryLanguage', module=mod)
    defineJavaClass('TupleQuery', 'org.openrdf.query.TupleQuery', module=mod)
    defineJavaClass('TupleQueryResult', 'org.openrdf.query.TupleQueryResult', module=mod)
    defineJavaClass('Repository', 'org.openrdf.repository.Repository', module=mod)
    defineJavaClass('RepositoryConnection', 'org.openrdf.repository.RepositoryConnection', module=mod)
    defineJavaClass('RDFFormat', 'org.openrdf.rio.RDFFormat', module=mod)

    defineJavaClass('BigdataBNode', 'com.bigdata.rdf.model.BigdataBNode', module=mod)
    defineJavaClass('BigdataLiteral', 'com.bigdata.rdf.model.BigdataLiteral', module=mod)
    defineJavaClass('BigdataResource', 'com.bigdata.rdf.model.BigdataResource', module=mod)
    defineJavaClass('BigdataStatement', 'com.bigdata.rdf.model.BigdataStatement', module=mod)
    defineJavaClass('BigdataURI', 'com.bigdata.rdf.model.BigdataURI', module=mod)
    defineJavaClass('BigdataValue', 'com.bigdata.rdf.model.BigdataValue', module=mod)
    BigdataValue.__str__ = Value_str          # needed even though it extends Java Value
    BigdataValue.__unicode__ = Value_unicode  # needed even though it extends Java Value

    defineJavaClass('BigdataSail', 'com.bigdata.rdf.sail.BigdataSail', module=mod)
    defineJavaClass('BigdataSailRepository', 'com.bigdata.rdf.sail.BigdataSailRepository', module=mod)
    defineJavaClass('BigdataSailConnection', 'com.bigdata.rdf.sail.BigdataSail$BigdataSailConnection', module=mod)
    defineJavaClass('BigdataSailOptions', 'com.bigdata.rdf.sail.BigdataSail$Options', module=mod)
    defineJavaClass('ExportKB', 'com.bigdata.rdf.sail.ExportKB', module=mod)
    defineJavaClass('ConfigParams', 'com.bigdata.rdf.sail.webapp.ConfigParams', module=mod)
    defineJavaClass('NanoSparqlServer', 'com.bigdata.rdf.sail.webapp.NanoSparqlServer', module=mod)
    defineJavaClass('RemoteRepositoryManager', 'com.bigdata.rdf.sail.webapp.client.RemoteRepositoryManager', module=mod)

    defineJavaClass('TermId', 'com.bigdata.rdf.internal.impl.TermId', module=mod)
    defineJavaClass('IVUtility', 'com.bigdata.rdf.internal.IVUtility', module=mod)

    defineJavaClass('ResultBufferHandler', 'com.bigdata.btree.proc.AbstractKeyArrayIndexProcedure$ResultBufferHandler', module=mod)
    defineJavaClass('BatchLookup', 'com.bigdata.btree.proc.BatchLookup', module=mod)
    defineJavaClass('BatchLookupConstructor', 'com.bigdata.btree.proc.BatchLookup$BatchLookupConstructor', module=mod)
    defineJavaClass('BufferMode', 'com.bigdata.journal.BufferMode', module=mod)
    defineJavaClass('Options', 'com.bigdata.journal.Options', module=mod)
    defineJavaClass('BytesUtil', 'com.bigdata.util.BytesUtil', module=mod)
    defineJavaClass('NicUtil', 'com.bigdata.util.config.NicUtil', module=mod)
    defineJavaClass('Httpd_Config', 'com.bigdata.util.httpd.Config', module=mod)
