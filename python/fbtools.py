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
# Portions created by the Initial Developer are Copyright (C) 2015-2021      #
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

# Python API to Freebase indices created by FreebaseTools; this primarily facilitates
# querying of indices but not their creation which is already supported by scripts.

# Installation:
# - ensure FreebaseTools (FBT) is properly configured and works from the command line
#   by calling 'fbt-lookup.sh' or 'fbt-search.sh'
# - this packages calls the Java version of FBT via the jnius package, so ensure you
#   have that available on your system or install it via 'sudo pip install jnius'
# - point your PYTHONPATH to the FBT installation directory or where else this file lives
# - either permanently edit 'freebaseToolsHome' and 'freebaseToolsConfig' below or use
#   'configure' immediately after import to configure the package dynamically
# - this package was developed and tested with Python 2.7 only, for Python 3 your
#   milage may vary

# Usage:
# - see the README file or the tail portion of this file for an example session

# TO DO:
# - add minor API extensions to better deal with property access and language-qualified values
# - make some of the FreebaseTools functions and variables public for easier access


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

# default values which can be changed dynamically with 'configure':
freebaseToolsHome   = '/data/nlp/freebase'
freebaseToolsConfig = 'config.dat'

def configure(home=None, config=None):
    """Use this to configure FBT home and config file BEFORE the first use.
       If you need to reconfigure, you need to restart Python."""
    global freebaseToolsHome, freebaseToolsConfig
    if home is not None:
        freebaseToolsHome = home
    if config is not None:
        freebaseToolsConfig = config

def getConfigFile():
    config = freebaseToolsConfig
    if config is not None:
        if os.path.exists(config):
            return config
        config = os.path.join(freebaseToolsHome, config)
        if os.path.exists(config):
            return config
    raise Exception('cannot access config file: ' + str(config))


JavaFreebaseTools = None
JavaLuceneQueryParser = None
JavaLuceneDocument = None
JavaLuceneTerm = None

def initJnius():
    # We package this as a function so we don't require jnius until an index is actually requested.
    import jnius_config
    from string import Template
    env = {'FBT_HOME': freebaseToolsHome}
    classpath = ['$FBT_HOME', '$FBT_HOME/bin', '$FBT_HOME/lib/*']
    classpath = [Template(dir).substitute(env) for dir in classpath]
    if not jnius_config.vm_running:
        jnius_config.set_classpath(*classpath)
    import jnius

    global JavaFreebaseTools, JavaLuceneQueryParser, JavaLuceneDocument, JavaLuceneTerm
    JavaFreebaseTools = jnius.autoclass('edu.isi.kres.FreebaseTools')
    JavaLuceneQueryParser = jnius.autoclass('org.apache.lucene.queryparser.classic.QueryParser')
    JavaLuceneDocument = jnius.autoclass('org.apache.lucene.document.Document')
    JavaLuceneTerm = jnius.autoclass('org.apache.lucene.index.Term')

configKeys = ['LANG',
              'SORT_DIR',
              'IGNORE_LANGS',
              'IGNORE_PREDS',
              'IGNORE_VALUES',
              'LUCENE_DEFAULT_FIELD',
              'LUCENE_INDEX',
              'LUCENE_INDEXED_PREDS',
              'LUCENE_INDEX_ANALYZER_DEFAULT',
              'LUCENE_INDEX_ANALYZER_EN',
              'LUCENE_INDEX_ANALYZER_ES',
              'LUCENE_INDEX_ANALYZER_ZH',
              'LUCENE_INDEX_OPTIONS',
              ]


def toFbtMid(mid):
    "Coerce 'mid' to FBT format."
    if mid.startswith('f_m.'):
        return mid
    elif mid.startswith('/m/'):
        return 'f_m.' + mid[3:]
    elif mid.startswith('m.'):
        return 'f_' + mid
    else:
        raise Exception("don't know how to convert this mid to FBT format: " + str(mid))

def toRegularMid(mid):
    "Coerce 'mid' to regular Freebase format."
    if mid.startswith('/m/'):
        return mid
    elif mid.startswith('f_m.'):
        return '/m/' + mid[4:]
    else:
        raise Exception("don't know how to convert this mid to Freebase format: " + str(mid))


class FreebaseIndex(object):
    def __init__(self, config=None, index=None):
        if JavaFreebaseTools is None:
            initJnius()
        self.fbt = JavaFreebaseTools()
        self.config = config
        if self.config is None:
            self.config = getConfigFile()
        if not os.path.exists(self.config):
            raise Exception('cannot access config file: ' + str(self.config))
        self.fbt.configFile = self.config
        self.fbt.readConfig()
        self.index = index or self.fbt.getConfig("LUCENE_INDEX")
        if self.index is None or not os.path.exists(self.index):
            raise Exception('cannot access index directory: ' + str(self.index))
        else:
            self.fbt.indexDirectoryName = self.index

    def __len__(self):
        "Returns the number of documents/subjects indexed in this index."
        return self.fbt.getIndexReader().numDocs()

    def describe(self):
        "Describe content and configuration properties of this index."
        print('Number of indexed documents:', len(self))
        print('Configuration:')
        for key in configKeys:
            value = self.fbt.getConfig(key)
            if value is not None:
                print(' ', key, value)

    def getDocumentFrequency(self, term, field=None):
        """Return the number of documents/subjects containing `term' in 'field'.
           If `field' is None, the currently configured LUCENE_DEFAULT_FIELD is used.
           TO DO: figure out how to make this work, it always returns 0."""
        field = field or self.fbt.getConfig('LUCENE_DEFAULT_FIELD')
        return self.fbt.getIndexReader().docFreq(JavaLuceneTerm(field, term))

    def getDocumentId(self, subject):
        "Return the document ID for 'subject' or -1 if not found."
        subject = toFbtMid(subject)
        return self.fbt.getSubjectDocID(subject)

    def getDocument(self, docSpec):
        """Access or coerce 'docSpec' to a Lucene document instance.  'docSpec' can either
           already be a document, a document ID or a subject URI.  Return None if it doesn't exist."""
        if isinstance(docSpec, JavaLuceneDocument):
            # already a Lucene document:
            return docSpec
        elif isinstance(docSpec, int):
            # a document ID returned by a search:
            if docSpec < 0:
                return None
            else:
                return self.fbt.getIndexReader().document(docSpec)
        elif isinstance(docSpec, basestring):
            docSpec = toFbtMid(docSpec)
            return self.fbt.getSubjectDoc(docSpec)
        else:
            raise Exception('cannot lookup Lucene document for docSpec' + str(docSpec))

    def getFieldValue(self, docSpec, field):
        """Return the value of 'field' on subject 'docSpec'.  If there are muliple values,
           return the first one indexed, if there are none, return None.
           If 'docSpec' is a string, this is specialized to only retrieve 'field' of the subject document.
           If other fields are also needed, convert to a document first via 'getDocument'."""
        if isinstance(docSpec, basestring):
            # special case to only access `field' instead of the whole document:
            docSpec = toFbtMid(docSpec)
            return self.fbt.getSubjectPredicateValue(docSpec, field)
        else:
            doc = self.getDocument(docSpec)
            return doc.get(field)

    def getFieldValues(self, docSpec, field):
        """Return the values of 'field' on subject 'docSpec' as a list.  If there are none, return the empty list.
           If 'docSpec' is a string, this is specialized to only retrieve 'field' of the subject document.
           If other fields are also needed, convert to a document first via 'getDocument'."""
        if isinstance(docSpec, basestring):
            # special case to only access `field' instead of the whole document:
            docSpec = toFbtMid(docSpec)
            return self.fbt.getSubjectPredicateValues(docSpec, field)
        else:
            doc = self.getDocument(docSpec)
            return doc.getValues(field)

    def getDocumentFields(self, docSpec, maxValues=None):
        """Return all fields of 'docSpec' as a dictionary where multi-valued fields become lists.
           Return at most 'maxValues' values or everything if it is None."""
        doc = self.getDocument(docSpec)
        result = {}
        if doc is not None:
            fields = doc.getFields()
            for i in range(min(fields.size(), maxValues or sys.maxsize)):
                field = fields.get(i)
                name = field.name()
                value = field.stringValue()
                values = result.get(name)
                if isinstance(values, list):
                    values.append(value)
                elif values is None:
                    result[name] = value
                else:
                    result[name] = [values, value]
        return result

    def lookup(self, subject):
        "Return the Lucene document for'subject' or None if it doesn't exist."
        return self.getDocument(subject)

    def fetch(self, subject, maxValues=None):
        """Return all document fields for 'subject' as a dictionary (which will be
        empty if 'subject' doesn't exist).  Fetch at most 'maxValues' or all if it is None."""
        return self.getDocumentFields(subject, maxValues=maxValues)

    def count(self, queryExpression, defaultField=None):
        """Search Freebase and count the number of documents matching 'queryExpression'.
           Use 'defaultField' as the search field for unqualified queries which defaults
           to "LUCENE_DEFAULT_FIELD" defined in the configuration."""
        searcher = self.fbt.getIndexSearcher()
        analyzer = self.fbt.getIndexAnalyzer()
        defaultField = defaultField or self.fbt.getConfig("LUCENE_DEFAULT_FIELD")
        query = JavaLuceneQueryParser(defaultField, analyzer).parse(queryExpression)
        results = searcher.search(query, 1)
        return results.totalHits

    def search(self, queryExpression, defaultField=None, maxHits=20):
        """Search Freebase for documents matching 'queryExpression'.
           Use 'defaultField' as the search field for unqualified queries which defaults
           to "LUCENE_DEFAULT_FIELD" defined in the configuration.
           Return at most 'maxHits' results of the form '(docid, score)' sorted by descending score."""
        searcher = self.fbt.getIndexSearcher()
        analyzer = self.fbt.getIndexAnalyzer()
        defaultField = defaultField or self.fbt.getConfig("LUCENE_DEFAULT_FIELD")
        query = JavaLuceneQueryParser(defaultField, analyzer).parse(queryExpression)
        results = searcher.search(query, maxHits)
        results = results.scoreDocs
        for i in range(len(results)):
            hit = results[i]
            docid = hit.doc
            score = hit.score
            results[i] = (docid, score)
        return results

    def retrieve(self, queryExpression, defaultField=None, maxHits=20, maxValues=None):
        """Search Freebase for documents matching 'queryExpression'.
           Just like 'search' but fetch document information for each result.
           The special fields '_docid' and '_score' will be inserted in addition.
           Fetch at most 'maxValues' for each result found or all if it is None."""
        results = []
        for (docid, score) in self.search(queryExpression, defaultField=defaultField, maxHits=maxHits):
            doc = self.fetch(docid, maxValues=maxValues)
            doc['_docid'] = docid
            doc['_score'] = score
            results.append(doc)
        return results

"""
>>> import fbtools as fbt

# point to your own FBT installation directory (and config file if it differs from the default):
>>> fbt.configure(home='/data/nlp/freebase', config='config.dat.dist')

# ignore the warning:
>>> fbi = fbt.FreebaseIndex()
WARN: problem reading config file `/data/nlp/freebase/config.dat.dist': null

>>> fbi.describe()
Number of indexed documents: 107692853
Configuration:
  SORT_DIR /data/nlp/freebase/sort
  IGNORE_LANGS /data/nlp/freebase/ignore-langs.lst
  IGNORE_PREDS /data/nlp/freebase/ignore-preds.lst
  IGNORE_VALUES /data/nlp/freebase/ignore-values.lst
  LUCENE_DEFAULT_FIELD rs_label
  LUCENE_INDEX /data/nlp/freebase/data/basekb-gold-jan-2015.shrink.sort.index
  LUCENE_INDEXED_PREDS /data/nlp/freebase/indexed-preds.lst
  LUCENE_INDEX_ANALYZER_DEFAULT org.apache.lucene.analysis.standard.StandardAnalyzer
  LUCENE_INDEX_OPTIONS "-nn -v"

>>> fbi.lookup('f_m.0h54qv8')
<org.apache.lucene.document.Document at 0x7f87e8d74a70 jclass=org/apache/lucene/document/Document jself=<LocalRef obj=0x1c95cc8 at 0x7f87ea42c350>>

>>> fbi.getFieldValue('f_m.0h54qv8', 'rs_label')
'"Henry Higgins"@en'

>>> fbi.getFieldValues('f_m.0h54qv8', 'r_type')
['f_common.topic', 'f_people.deceased_person', 'f_people.person']

>>> fbi.getFieldValues('/m/0h54qv8', 'r_type')
['f_common.topic', 'f_people.deceased_person', 'f_people.person']

>>> fbi.getDocumentId('f_m.0h54qv8')
69442668

>>> fbi.getDocument(69442668)
<org.apache.lucene.document.Document at 0x7f87e8d74a70 jclass=org/apache/lucene/document/Document jself=<LocalRef obj=0x1c95cb8 at 0x7f87ea42c370>>

>>> import pprint
>>> pp = pprint.PrettyPrinter(indent=4)

>>> pp.pprint(fbi.fetch('f_m.0h54qv8'))
{   'f_common.topic.article': 'f_m.0h54qvd',
    'f_common.topic.description': '"Henry Hugh Higgins was an English botanist, bryologist, geologist, curator and clergyman. He is cited as an authority in scientific classification, as Higgins.\\nHe was inspector of the National Schools in Liverpool from 1842 to 1848 and chaplain to the Rainhill Asylum, also in Liverpool. He was also president of the Liverpool Field Naturalists\' Club from 1861 to 1881.\\nHe especially worked on the Ravenhead collections, almost wholly made up of Upper Carboniferous flora, fish, bivalves and insect remains. Higgins had suggested that Ravenhead donate his collections to the Liverpool Museum and the donation gained a home with the construction of the railway in 1870, which exposed two Carboniferous seams known as the Upper and Lower Ravenhead. Most of Liverpool Museum\'s collections survived the Liverpool Blitz of May 1941 which practically destroyed the Museum itself, but the entire Ravenhead collection was lost in the fire."@en',
    'f_common.topic.notable_for': 'f_g.125crzjzl',
    'f_common.topic.notable_types': 'f_m.022tfrk',
    'f_common.topic.topic_equivalent_webpage': [   'we_Henry_Higgins_(botanist)',
                                                   'we_index.html?curid=32997517'],
    'f_people.deceased_person.date_of_death': '"1893"^^<http://www.w3.org/2001/XMLSchema#gYear>',
    'f_people.person.date_of_birth': '"1814"^^<http://www.w3.org/2001/XMLSchema#gYear>',
    'f_people.person.gender': 'f_m.05zppz',
    'f_people.person.profession': 'f_m.036n1',
    'f_type.object.name': '"Henry Higgins"@en',
    'fk_key.wikipedia.en': [   '"Henry_Higgins_$0028botanist$0029"',
                               '"Henry_Hugh_Higgins"'],
    'fk_key.wikipedia.en_id': '"32997517"',
    'fk_key.wikipedia.en_title': '"Henry_Higgins_$0028botanist$0029"',
    'r_type': [   'f_common.topic',
                  'f_people.deceased_person',
                  'f_people.person'],
    'rs_label': '"Henry Higgins"@en',
    'subject': 'f_m.0h54qv8'}

>>> fbi.search('Henry Higgins AND r_type:f_people.person', maxHits=5)
[(69442668, 8.640470504760742), (93746332, 8.640470504760742), (3290194, 4.759587287902832), (15812, 4.0124993324279785), (63493, 4.0124993324279785)]

>>> pp.pprint(fbi.fetch(69442668))
{   'f_common.topic.article': 'f_m.0h54qvd',
    'f_common.topic.description': '"Henry Hugh Higgins was an English botanist, bryologist, geologist, curator and clergyman. He is cited as an authority in scientific classification, as Higgins.\\nHe was inspector of the National Schools in Liverpool from 1842 to 1848 and chaplain to the Rainhill Asylum, also in Liverpool. He was also president of the Liverpool Field Naturalists\' Club from 1861 to 1881.\\nHe especially worked on the Ravenhead collections, almost wholly made up of Upper Carboniferous flora, fish, bivalves and insect remains. Higgins had suggested that Ravenhead donate his collections to the Liverpool Museum and the donation gained a home with the construction of the railway in 1870, which exposed two Carboniferous seams known as the Upper and Lower Ravenhead. Most of Liverpool Museum\'s collections survived the Liverpool Blitz of May 1941 which practically destroyed the Museum itself, but the entire Ravenhead collection was lost in the fire."@en',
    'f_common.topic.notable_for': 'f_g.125crzjzl',
    'f_common.topic.notable_types': 'f_m.022tfrk',
    'f_common.topic.topic_equivalent_webpage': [   'we_Henry_Higgins_(botanist)',
                                                   'we_index.html?curid=32997517'],
    'f_people.deceased_person.date_of_death': '"1893"^^<http://www.w3.org/2001/XMLSchema#gYear>',
    'f_people.person.date_of_birth': '"1814"^^<http://www.w3.org/2001/XMLSchema#gYear>',
    'f_people.person.gender': 'f_m.05zppz',
    'f_people.person.profession': 'f_m.036n1',
    'f_type.object.name': '"Henry Higgins"@en',
    'fk_key.wikipedia.en': [   '"Henry_Higgins_$0028botanist$0029"',
                               '"Henry_Hugh_Higgins"'],
    'fk_key.wikipedia.en_id': '"32997517"',
    'fk_key.wikipedia.en_title': '"Henry_Higgins_$0028botanist$0029"',
    'r_type': [   'f_common.topic',
                  'f_people.deceased_person',
                  'f_people.person'],
    'rs_label': '"Henry Higgins"@en',
    'subject': 'f_m.0h54qv8'}

>>> pp.pprint(fbi.retrieve('Henry Higgins AND r_type:f_people.person', maxHits=5))
[   {   '_docid': 69442668,
        '_score': 8.640470504760742,
        'f_common.topic.article': 'f_m.0h54qvd',
        'f_common.topic.description': '"Henry Hugh Higgins was an English botanist, bryologist, geologist, curator and clergyman. He is cited as an authority in scientific classification, as Higgins.\\nHe was inspector of the National Schools in Liverpool from 1842 to 1848 and chaplain to the Rainhill Asylum, also in Liverpool. He was also president of the Liverpool Field Naturalists\' Club from 1861 to 1881.\\nHe especially worked on the Ravenhead collections, almost wholly made up of Upper Carboniferous flora, fish, bivalves and insect remains. Higgins had suggested that Ravenhead donate his collections to the Liverpool Museum and the donation gained a home with the construction of the railway in 1870, which exposed two Carboniferous seams known as the Upper and Lower Ravenhead. Most of Liverpool Museum\'s collections survived the Liverpool Blitz of May 1941 which practically destroyed the Museum itself, but the entire Ravenhead collection was lost in the fire."@en',
        'f_common.topic.notable_for': 'f_g.125crzjzl',
        'f_common.topic.notable_types': 'f_m.022tfrk',
        'f_common.topic.topic_equivalent_webpage': [   'we_Henry_Higgins_(botanist)',
                                                       'we_index.html?curid=32997517'],
        'f_people.deceased_person.date_of_death': '"1893"^^<http://www.w3.org/2001/XMLSchema#gYear>',
        'f_people.person.date_of_birth': '"1814"^^<http://www.w3.org/2001/XMLSchema#gYear>',
        'f_people.person.gender': 'f_m.05zppz',
        'f_people.person.profession': 'f_m.036n1',
        'f_type.object.name': '"Henry Higgins"@en',
        'fk_key.wikipedia.en': [   '"Henry_Higgins_$0028botanist$0029"',
                                   '"Henry_Hugh_Higgins"'],
        'fk_key.wikipedia.en_id': '"32997517"',
        'fk_key.wikipedia.en_title': '"Henry_Higgins_$0028botanist$0029"',
        'r_type': [   'f_common.topic',
                      'f_people.deceased_person',
                      'f_people.person'],
        'rs_label': '"Henry Higgins"@en',
        'subject': 'f_m.0h54qv8'},
    {   '_docid': 93746332,
        '_score': 8.640470504760742,
        'f_common.topic.article': 'f_m.0ll1ywd',
        'f_common.topic.description': '"Henry Higgins was an English bullfighter, who was born in Bogot\\u00E1, Colombia in 1944. He died as a result of a hang-gliding accident, while demonstrating it by jumping off a 200 ft high hill in 1978. He was educated at King Williams College in the Isle of Man."@en',
        'f_common.topic.notable_for': 'f_g.12q4p343t',
        'f_common.topic.notable_types': 'f_m.04kr',
        'f_common.topic.topic_equivalent_webpage': [   'we_Henry_Higgins_(bullfighter)',
                                                       'we_index.html?curid=36799328'],
        'f_people.person.profession': 'f_m.01kr58',
        'f_type.object.name': '"Henry Higgins"@en',
        'fk_key.wikipedia.en': '"Henry_Higgins_$0028bullfighter$0029"',
        'fk_key.wikipedia.en_id': '"36799328"',
        'fk_key.wikipedia.en_title': '"Henry_Higgins_$0028bullfighter$0029"',
        'r_type': ['f_common.topic', 'f_people.person'],
        'rs_label': '"Henry Higgins"@en',
        'subject': 'f_m.0ll1yw8'},
    {   '_docid': 3290194,
        '_score': 4.759587287902832,
        'f_common.topic.article': 'f_m.04j19m',
        'f_common.topic.description': '"Terence Langley Higgins, Baron Higgins KBE DL PC is a retired British Conservative politician and Commonwealth Games silver medalist winner for England.\\nHiggins was Member of Parliament for Worthing from 1964 to 1997, and Financial Secretary to the Treasury between 1972 and 1974.\\nHe served in the RAF from 1946 to 1948, and was a member of British Olympic Team in 1948 and 1952. He was created a life peer as Baron Higgins, of Worthing in the County of West Sussex on 28 October 1997. While in opposition, he served as the Conservative shadow minister for work and pensions in the House of Lords. He was appointed a Knight Commander of the Order of the British Empire in the 1993 New Years Honours List."@en',
        'f_common.topic.notable_for': 'f_g.1257q_vsp',
        'f_common.topic.notable_types': 'f_m.02xlh55',
        'f_common.topic.topic_equivalent_webpage': [   'we_Terence_Higgins,_Baron_Higgins',
                                                       'we_index.html?curid=1215819'],
        'f_government.politician.government_positions_held': 'f_m.04ntzv0',
        'f_government.politician.party': 'f_m.04htc0_',
        'f_people.person.date_of_birth': '"1928-01-18"^^<http://www.w3.org/2001/XMLSchema#date>',
        'f_people.person.gender': 'f_m.05zppz',
        'f_people.person.nationality': 'f_m.07ssc',
        'f_type.object.name': '"Terence Higgins, Baron Higgins"@en',
        'fk_key.en': '"terence_higgins_baron_higgins"',
        'fk_key.wikipedia.en': [   '"Baron_Higgins"',
                                   '"Lord_Higgins"',
                                   '"Terence_Higgins$002C_Baron_Higgins"',
                                   '"Terence_Langley_Higgins"'],
        'fk_key.wikipedia.en_id': '"1215819"',
        'fk_key.wikipedia.en_title': '"Terence_Higgins$002C_Baron_Higgins"',
        'r_type': [   'f_common.topic',
                      'f_government.politician',
                      'f_people.person',
                      'f_royalty.chivalric_order_member',
                      'f_royalty.noble_person'],
        'rs_label': '"Terence Higgins, Baron Higgins"@en',
        'subject': 'f_m.04j19g'},
    {   '_docid': 15812,
        '_score': 4.0124993324279785,
        'f_common.topic.article': 'f_m.03chhdq',
        'f_common.topic.description': '"Debra Elaine Higgins is a Canadian provincial politician, who was the Saskatchewan New Democratic Party member of the Legislative Assembly of Saskatchewan for the constituency of Moose Jaw Wakamow from 1999 to 2011. She is currently the mayor of Moose Jaw, Saskatchewan, having been elected as the city\'s first female mayor in the Saskatchewan municipal elections, 2012.\\nShe was first elected in the 1999 election and was re-elected in the 2003 and 2007 elections. Higgins served in the cabinet of Lorne Calvert as the Minister of Labour and later as the Minister of Learning.\\nAfter the defeat of the NDP government in the 2007 election, Higgins has served as the NDP critic for municipal affairs, liquor and gaming, and women\'s issues.\\nOn January 30, 2009, she announced her bid to succeed Calvert as Saskatchewan NDP leader at the party\'s June 2009 leadership convention. Higgins ran on the theme of renewal and defeating Premier Brad Wall. In the end she finished last of four candidates with Dwain Lingenfelter being the victor.\\nIn the 2011 election Higgins was defeated in her riding by Greg Lawrence of the Saskatchewan Party.\\nHiggins got her start in politics when she became involved with the UFCW union in 1982 while working at a Safeway grocery store. She later served as the President of the UFCW Council from 1993 to 1999, during which period she also served as a table officer for the Moose Jaw & District Labour Council."@en',
        'f_common.topic.notable_for': 'f_g.12556xmf4',
        'f_common.topic.notable_types': 'f_m.04kr',
        'f_common.topic.topic_equivalent_webpage': [   'we_Deb_Higgins',
                                                       'we_index.html?curid=13762292'],
        'f_government.politician.party': 'f_m.0lr0_qy',
        'f_people.person.date_of_birth': '"1954"^^<http://www.w3.org/2001/XMLSchema#gYear>',
        'f_people.person.gender': 'f_m.02zsn',
        'f_people.person.places_lived': 'f_m.0wllybw',
        'f_type.object.name': '"Deb Higgins"@en',
        'fk_key.en': '"deb_higgins"',
        'fk_key.source.videosurf': '"125328"',
        'fk_key.wikipedia.en': '"Deb_Higgins"',
        'fk_key.wikipedia.en_id': '"13762292"',
        'fk_key.wikipedia.en_title': '"Deb_Higgins"',
        'r_type': ['f_common.topic', 'f_people.person'],
        'rs_label': '"Deb Higgins"@en',
        'subject': 'f_m.03chhdl'},
    {   '_docid': 63493,
        '_score': 4.0124993324279785,
        'f_common.topic.article': 'f_m.03d0fnj',
        'f_common.topic.description': '"Terence John Higgins is Chief Justice of the Australian Capital Territory, a territory of Australia."@en',
        'f_common.topic.notable_for': 'f_g.125dtp53k',
        'f_common.topic.notable_types': 'f_m.04kr',
        'f_common.topic.topic_equivalent_webpage': [   'we_Terence_Higgins_(judge)',
                                                       'we_index.html?curid=14320511'],
        'f_people.person.date_of_birth': '"1943"^^<http://www.w3.org/2001/XMLSchema#gYear>',
        'f_people.person.education': 'f_m.0sw2b_6',
        'f_people.person.gender': 'f_m.05zppz',
        'f_people.person.place_of_birth': 'f_m.0chghy',
        'f_type.object.name': '"Terence Higgins"@en',
        'fk_key.en': '"terence_john_higgins"',
        'fk_key.wikipedia.en': [   '"Terence_Higgins_$0028judge$0029"',
                                   '"Terence_John_Higgins"',
                                   '"Terrence_John_Higgins"'],
        'fk_key.wikipedia.en_id': '"14320511"',
        'fk_key.wikipedia.en_title': '"Terence_Higgins_$0028judge$0029"',
        'r_type': ['f_common.topic', 'f_people.person'],
        'rs_label': '"Terence Higgins"@en',
        'subject': 'f_m.03d0fnd'}]
"""
