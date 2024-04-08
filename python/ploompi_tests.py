#!/bin/python

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
# Portions created by the Initial Developer are Copyright (C) 1997-2020      #
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
############################## END LICENSE BLOCK #############################

"""
Test suite for Python PowerLoom PLI interface v2.
"""

from __future__ import print_function, division, absolute_import

import sys
PY2 = sys.version_info[0] == 2
PY3 = sys.version_info[0] >= 3
if PY3:
    basestring = str
    unicode = str
    long = int

import unittest
import ploompi as pli


### NOTES
# - see https://docs.python.org/2/library/unittest.html#unittest.TestCase.assertEqual
#   for documentation on assertion operators


class TestWrapper(unittest.TestCase):
    """For interactive testing, so we can create a test case to run asserts on."""
    def runTest(self):
        pass


### STELLA lists and literals:

class Test_Lists_Literals(unittest.TestCase):

    def test_lists(self):
        # TO DO: these still need value assertions, so far they just call the various functions
        value = pli.createCons(pli.createIntegerWrapper(42), pli.NIL)
        value = pli.createConsList(5)
        value = pli.consLength(value)
        pli.consIsEmpty(pli.NIL)
        pli.consIsEmpty(pli.createConsList(5))
        list = pli.createCons(pli.createIntegerWrapper(1), pli.createCons(pli.createIntegerWrapper(2), pli.NIL))
        value = pli.consFirst(list)
        value = pli.consRest(list)
        value = pli.consNth(list, 0)
        value = pli.consNth(list, 1)
        value = pli.consNth(list, 2)
        value = pli.consNthRest(list, 0)
        value = pli.consNthRest(list, 1)
        value = pli.consNthRest(list, 2)
        value = pli.consNthRest(list, 10)
        pli.consSetFirst(list, pli.createIntegerWrapper(10))
        list
        pli.consSetRest(list, pli.NIL)
        list
        pli.consSetNth(list, 0, pli.createIntegerWrapper(100))
        list
        pli.consSetNthRest(list, 1, pli.createCons(pli.createIntegerWrapper(200), pli.NIL))
        list
        list = pli.plIteratorListify(pli.getPropositionsInModule('PL-KERNEL'))
        value = len(list)
        value = pli.listFirst(list)
        value = pli.listNth(list, 100)
        consRest = pli.listRest(list)
        value = pli.consFirst(consRest)
        value = len(consRest)
        self.assertTrue(value >= 1500)

    def test_literals(self):
        # TO DO: these still need value assertions, so far they just call the various functions
        value = pli.createString('Hans')
        value = pli.createStringWrapper('Franz')
        value = pli.createDirectStringWrapper('Susi')
        value = pli.createIntegerWrapper(42)
        value = pli.createLongIntegerWrapper(long(1000000))
        value = pli.createFloatWrapper(1.99)
        value = pli.createBooleanWrapper(True)
        self.assertTrue(value)
        value = pli.createBooleanWrapper(False)
        self.assertFalse(value)


### Names to instances and back:

class Test_Names_To_Instances(unittest.TestCase):

    def test_get_symbols(self):
        pli.cc('STELLA')
        value = pli.getKeyword('documentation')
        self.assertIsNone(value)
        value = pli.getKeyword('DOCUMENTATION')
        self.assertIsNotNone(value)
        value = pli.getSymbol('cons')
        self.assertIsNone(value)
        value = pli.getSymbol('CONS')
        self.assertEqual(value.symbolName, 'CONS')
        value = pli.getSymbol('NTH-DOMAIN')
        self.assertIsNone(value)
        value = pli.getSymbol('NTH-DOMAIN', 'PL-KERNEL')
        self.assertEqual(value.symbolName, 'NTH-DOMAIN')
        value = pli.getSymbol('NTH-DOMAIN', 'PL-USER')
        self.assertEqual(value.symbolName, 'NTH-DOMAIN')
        value = pli.getSymbol('NTH-DOMAIN', module=pli.oPL_KERNEL_MODULEo)
        self.assertEqual(value.symbolName, 'NTH-DOMAIN')
        pli.cc('PL-USER')
        value = pli.getSymbol('NTH-DOMAIN')
        self.assertEqual(value.symbolName, 'NTH-DOMAIN')
        pli.cc('STELLA')
        value = pli.getOperator('and')
        self.assertEqual(value.symbolName, 'AND')
        value = pli.getOperator('OR')
        self.assertEqual(value.symbolName, 'OR')
        with self.assertRaises(pli.spi.StellaException):
            value = pli.getOperator('NORT')

    def test_get_objects(self):
        pli.cc('STELLA')
        value = pli.getObject('NTH-DOMAIN')
        self.assertIsNone(value)
        value = pli.getObject('nth-domain')
        self.assertIsNone(value)
        value = pli.getObject('NTH-DOMAIN', 'PL-KERNEL')
        self.assertEqual(pli.getShortName(value), 'NTH-DOMAIN')
        value = pli.getObject('nth-domain', 'PL-KERNEL')
        self.assertEqual(pli.getShortName(value), 'NTH-DOMAIN')
        value = pli.getObject('NTH-DOMAIN', module=pli.oPL_KERNEL_MODULEo)
        self.assertEqual(pli.getShortName(value), 'NTH-DOMAIN')
        value = pli.getObject('nth-domain', module=pli.oPL_KERNEL_MODULEo)
        self.assertEqual(pli.getShortName(value), 'NTH-DOMAIN')
        pli.cc('PL-USER')
        value = pli.getObject('NTH-DOMAIN')
        self.assertEqual(pli.getShortName(value), 'NTH-DOMAIN')
        value = pli.getObject('nth-domain')
        self.assertEqual(pli.getShortName(value), 'NTH-DOMAIN')

        pli.cc('STELLA')
        value = pli.getConcept('aggregate')
        self.assertIsNone(value)
        value = pli.getConcept('aggregate', 'PL-KERNEL')
        self.assertEqual(pli.getShortName(value), 'AGGREGATE')
        value = pli.getConcept('aggregate', module=pli.oPL_KERNEL_MODULEo)
        self.assertEqual(pli.getShortName(value), 'AGGREGATE')
        pli.cc('PL-USER')
        value = pli.getConcept('aggregate')
        self.assertEqual(pli.getShortName(value), 'AGGREGATE')

        pli.cc('STELLA')
        value = pli.getRelation('nth-domain')
        self.assertIsNone(value)
        value = pli.getRelation('nth-domain', 'PL-KERNEL')
        self.assertEqual(pli.getShortName(value), 'NTH-DOMAIN')
        value = pli.getRelation('nth-domain', module=pli.oPL_KERNEL_MODULEo)
        self.assertEqual(pli.getShortName(value), 'NTH-DOMAIN')
        pli.cc('PL-USER')
        value = pli.getRelation('nth-domain')
        self.assertEqual(pli.getShortName(value), 'NTH-DOMAIN')

        pli.cc('STELLA')
        value = pli.getUndefinedRelations()
        self.assertTrue(len(value) == 0)
        value = pli.getUndefinedRelations('PL-KERNEL')
        self.assertTrue(len(value) > 0)
        value = pli.getUndefinedRelations(module=pli.oPL_KERNEL_MODULEo)
        self.assertTrue(len(value) > 0)
        pli.cc('PL-KERNEL')
        value = pli.getUndefinedRelations()
        self.assertTrue(len(value) > 0)

"""
pli.getNameInModule, module=None, environment=None, _pre=_coerceToModuleStmt, ...

pli.getName
pli.getShortName
pli.getSkolemName
pli.getSkolemShortName
pli.getVariableName
pli.getVariableShortName
pli.objectToString
pli.objectToInteger
pli.objectToFloat
pli.objectToParsableString
pli.getStellaType
pli.getLogicType
pli.getStellaTypeName
pli.getStellaTypeShortName
pli.getLogicTypeName
pli.getLogicTypeShortName

LITERAL_CONCEPT
STRING_CONCEPT
INTEGER_CONCEPT
FLOAT_CONCEPT
CONCEPT_CONCEPT
FUNCTION_CONCEPT
RELATION_CONCEPT

pli.stringToObject, module=None, environment=None, _pre=[_coerceToModuleStmt, 'type = pli.pdef.coerceToConcept(type, module)'], ...
pli.stringToStellaExpression, module=None, environment=None
"""


### Proposition retrieval:

class Test_Proposition_Retrieval(unittest.TestCase):

    def test_getProposition(self):
        pli.changeModule(pli.getModule('STELLA'))
        plUser = pli.getModule('PL-USER')
        propCons = pli.createConsList(2)
        pli.consSetNth(propCons, 0, pli.getObject('RELATION', plUser, None))
        pli.consSetNth(propCons, 1, pli.getObject('RELATION', plUser))
        self.assertEqual(repr(propCons), """<proxy.Cons (/PL-KERNEL-KB/RELATION /PL-KERNEL-KB/RELATION)>""")
        prop = pli.getProposition(propCons, plUser)
        self.assertEqual(repr(prop), """<proxy.Proposition (/PL-KERNEL-KB/CONCEPT /PL-KERNEL-KB/RELATION)>""")
        prop = pli.getProposition(propCons, 'PL-USER')
        self.assertEqual(repr(prop), """<proxy.Proposition (/PL-KERNEL-KB/CONCEPT /PL-KERNEL-KB/RELATION)>""")
        prop = pli.getProposition(['relation', 'relation'], 'PL-USER')
        self.assertEqual(repr(prop), """<proxy.Proposition (/PL-KERNEL-KB/CONCEPT /PL-KERNEL-KB/RELATION)>""")
        pli.changeModule('PL-USER')
        prop = pli.getProposition([pli.gob("RELATION"), pli.gob("RELATION")])
        self.assertEqual(repr(prop), """<proxy.Proposition (CONCEPT RELATION)>""")

    def test_getPropositions(self):
        pli.cc('PL-USER')
        value = list(pli.getPropositions("(concept null)", 'PL-USER'))
        ref = """[<proxy.Proposition (CONCEPT CONCEPT)>, <proxy.Proposition (CONCEPT RELATION)>, ...]"""
        self.assertEqual(repr(value)[0:80], ref[0:80])
        value = list(pli.getPropositions([pli.gob("concept"), None], 'PL-USER'))
        ref = """[<proxy.Proposition (CONCEPT CONCEPT)>, <proxy.Proposition (CONCEPT RELATION)>, ...]"""
        self.assertEqual(repr(value)[0:80], ref[0:80])

    def test_getUnaryPropositions(self):
        pli.cc('PL-USER')
        value = list(pli.getUnaryPropositions('variable-arity'))
        ref = """[<proxy.Proposition (VARIABLE-ARITY SKOLEM-FN)>, <proxy.Proposition (VARIABLE-ARITY COLLECTIONOF)>, ...]"""
        self.assertEqual(repr(value)[0:100], ref[0:100])
        value = list(pli.getUnaryPropositions('variable-arity', 'collectionof'))
        ref = """[<proxy.Proposition (VARIABLE-ARITY COLLECTIONOF)>]"""
        self.assertEqual(repr(value), ref)

    def test_getBinaryProposition(self):
        pli.cc('PL-USER')
        value = pli.getBinaryProposition('documentation', None, None)
        ref = """<proxy.Proposition (DOCUMENTATION ...)>"""
        self.assertEqual(repr(value)[0:34], ref[0:34])
        value = pli.getBinaryProposition('documentation')
        self.assertEqual(repr(value)[0:34], ref[0:34])
        value = pli.getBinaryProposition('documentation', 'aggregate', None)
        ref = """<proxy.Proposition (DOCUMENTATION AGGREGATE "?a is an aggregate")>"""
        self.assertEqual(repr(value), ref)
        value = pli.getBinaryProposition('documentation', pli.getObject('aggregate'), None)
        self.assertEqual(repr(value), ref)
        value = pli.getBinaryProposition('documentation', 'aggregate')
        self.assertEqual(repr(value), ref)
        # DWIM keys in on an initial `?' as a sign of a variable and creates a symbol for this, thus None as the result:
        value = pli.getBinaryProposition('documentation', None, "?a is an aggregate")
        self.assertEqual(value, None)
        # we can force it to create a string wrapper like this:
        value = pli.getBinaryProposition('documentation', None, "\\?a is an aggregate")
        ref = """<proxy.Proposition (DOCUMENTATION AGGREGATE "?a is an aggregate")>"""
        self.assertEqual(repr(value), ref)
        # for a regular string we don't have an issue:
        value = pli.getBinaryProposition('documentation', None, "The class of scalar quantities.")
        ref = """<proxy.Proposition (DOCUMENTATION SCALAR "The class of scalar quantities.")>"""
        self.assertEqual(repr(value), ref)

    def test_getBinaryPropositions(self):
        pli.cc('PL-USER')
        value = list(pli.getBinaryPropositions('documentation', 'aggregate', None, 'PL-KERNEL'))
        ref = """[<proxy.Proposition (DOCUMENTATION AGGREGATE "?a is an aggregate")>]"""
        self.assertEqual(repr(value), ref)
        value = list(pli.getBinaryPropositions('documentation', 'aggregate'))
        self.assertEqual(repr(value), ref)
        # `help-get-propositions' allows a NULL relation but returns NIL in that case:
        value = list(pli.getBinaryPropositions(None, 'aggregate', None, 'PL-KERNEL'))
        self.assertEqual(value, [])
        value = list(pli.getBinaryPropositions('relation-specialist', None, None))[0:5]
        ref = ("""[<proxy.Proposition (RELATION-SPECIALIST + |i|CONSTRAINT-SPECIALIST)>, """ +
              """<proxy.Proposition (RELATION-SPECIALIST - |i|CONSTRAINT-SPECIALIST)>, """ +
              """<proxy.Proposition (RELATION-SPECIALIST * |i|CONSTRAINT-SPECIALIST)>, """ +
              """<proxy.Proposition (RELATION-SPECIALIST / |i|CONSTRAINT-SPECIALIST)>, """ +
              """<proxy.Proposition (RELATION-SPECIALIST < |i|INEQUALITY-SPECIALIST)>]""")
        self.assertEqual(repr(value), ref)

    def test_getInferredBinaryPropositionValues(self):
        pli.cc('PL-USER')
        value = list(pli.getInferredBinaryPropositionValues('documentation', 'aggregate'))
        ref = """[<proxy.StringWrapper ?a is an aggregate>]"""
        self.assertEqual(repr(value), ref)
        value = list(pli.getInferredBinaryPropositionValues('documentation', None))
        self.assertEqual(value, [])

    def test_getPropositionsOf(self):
        pli.cc('PL-USER')
        value = list(pli.getPropositionsOf('aggregate'))
        ref = """[<proxy.Proposition (CONCEPT AGGREGATE)>, <proxy.Proposition (DOCUMENTATION AGGREGATE "?a is an aggregate")>, ...]"""
        self.assertEqual(repr(value)[0:100], ref[0:100])
        value = list(pli.getPropositionsOf(pli.getObject('aggregate')))
        self.assertEqual(repr(value)[0:100], ref[0:100])
        with self.assertRaises(pli.spi.ApiException):
            # stellapi.ApiException: Object ?a is an aggregate is not of type <class 'LogicObject'>
            value = list(pli.getPropositionsOf("\\?a is an aggregate"))

    def test_getPropositionsInModule(self):
        pli.cc('STELLA')
        value = pli.getPropositionsInModule()
        self.assertEqual(value.length(), 0)
        value = pli.getPropositionsInModule('PL-KERNEL')
        self.assertTrue(value.length() >= 1500)
        value = pli.getPropositionsInModule('PL-USER')
        self.assertTrue(value.length() >= 1 and value.length() <= 10)
        pli.cc('PL-USER')
        value = pli.getPropositionsInModule()
        self.assertTrue(value.length() >= 1 and value.length() <= 10)


### Probes:

class Test_Probes(unittest.TestCase):

    def test_isTrueUnaryProposition(self):
        pli.cc('PL-USER')
        value = pli.isTrueUnaryProposition("concept", "concept")
        self.assertEqual(value, True)
        value = pli.isTrueUnaryProposition("variable-arity", "holds")
        self.assertEqual(value, True)

    def test_isTrueBinaryProposition(self):
        pli.cc('PL-USER')
        value = pli.isTrueBinaryProposition("subset-of", "NUMBER", "SCALAR")
        self.assertEqual(value, True)
        value = pli.isTrueBinaryProposition("subset-of", "SCALAR", "NUMBER")
        self.assertEqual(value, False)
        # BUT - since these are not explicitly asserted:
        value = pli.isTrueBinaryProposition("arity", "range", 2)
        self.assertEqual(value, False)
        value = pli.isTrueUnaryProposition("single-valued", "arity")
        self.assertEqual(value, False)

    def test_isTrueNaryProposition(self):
        pli.cc('PL-USER')
        value = pli.isTrueNaryProposition(["subset-of", "LIST", "COLLECTION"])
        self.assertEqual(value, True)
        value = pli.isTrueNaryProposition(["subset-of", "COLLECTION", "LIST"])
        self.assertEqual(value, False)
        value = pli.isTrueNaryProposition("(subset-of LIST COLLECTION)")
        self.assertEqual(value, True)
        value = pli.isTrueNaryProposition("(subset-of COLLECTION LIST)")
        self.assertEqual(value, False)
        value = pli.isTrueNaryProposition([pli.getRelation("subset-of"), "LIST", "COLLECTION"])
        self.assertEqual(value, True)
        value = pli.isTrueNaryProposition([pli.getRelation("subset-of"), pli.getConcept("LIST"), "COLLECTION"])
        self.assertEqual(value, True)

    def test_isTrueProposition(self):
        pli.cc('PL-USER')
        value = pli.getBinaryProposition("subset-of", "LIST", "COLLECTION")
        ref = """<proxy.Proposition (forall (?l)\n   (<= (COLLECTION ?l)\n       (LIST ?l)))>"""
        value = pli.isTrueProposition(pli.getBinaryProposition("subset-of", "LIST", "COLLECTION"))
        self.assertEqual(value, True)


### Isa and Subsumption Hierarchies:

class Test_Subsumption_Hierarchies(unittest.TestCase):

    def test_isSubrelation(self):
        pli.cc('PL-USER')
        value = pli.isSubrelation('concept', 'relation')
        self.assertEqual(value, True)
        value = pli.isSubrelation('relation', 'relation')
        self.assertEqual(value, True)
        value = pli.isSubrelation('relation', 'concept')
        self.assertEqual(value, False)
        pli.cc('STELLA')
        value = pli.isSubrelation('concept', 'relation', 'PL-USER')
        self.assertEqual(value, True)

    def test_getProperSubrelations(self):
        pli.cc('PL-USER')
        value = list(pli.getProperSubrelations('relation'))[0:5]
        ref = ("""[<proxy.NamedDescription FUNCTION>, <proxy.NamedDescription SKOLEM-FUNCTION>, """ +
               """<proxy.NamedDescription CONCEPT>, <proxy.NamedDescription FRAME-PREDICATE>, <proxy.NamedDescription BINARY-RELATION>]""")
        self.assertEqual(repr(value), ref)

    def test_getDirectSubrelations(self):
        pli.cc('PL-USER')
        value = list(pli.getDirectSubrelations('relation'))
        ref = ("""[<proxy.NamedDescription FUNCTION>, <proxy.NamedDescription CONCEPT>, """ +
               """<proxy.NamedDescription FRAME-PREDICATE>, <proxy.NamedDescription BINARY-RELATION>]""")
        self.assertEqual(repr(value), ref)

    def test_getProperSuperrelations(self):
        pli.cc('PL-USER')
        value = list(pli.getProperSuperrelations('concept'))
        ref = ("""[<proxy.NamedDescription RELATION>, <proxy.NamedDescription SET>, <proxy.NamedDescription DUPLICATE-FREE-COLLECTION>, """+
               """<proxy.NamedDescription COLLECTION>, <proxy.NamedDescription AGGREGATE>, <proxy.NamedDescription DUPLICATE-FREE>]""")
        self.assertEqual(repr(value), ref)

    def test_getDirectSuperrelations(self):
        pli.cc('PL-USER')
        value = list(pli.getDirectSuperrelations('concept'))
        ref = """[<proxy.NamedDescription RELATION>]"""
        self.assertEqual(repr(value), ref)


### Modules:


### Object creation, destruction:

# This uncovered a premature GC-bug before, where string arguments passed to plic functions
# were eventually garbage collected by Python and created memory corruption on the STELLA side.
# Now we explicitly allocate STELLA strings for such arguments which solves the problem.
# >>> s = pli.createSymbol(pli.generateUniqueName('blah', 'PL-USER'))
# >>> s
# <pli.Symbol BLAH-025>
# >>> n = pli.generateUniqueName('blah', 'PL-USER')
# >>> n
# 'BLAH-026'
# >>> s2 =  pli.createSymbol(n)
# >>> s2
# <pli.Symbol BLAH-026>


### Specialists and computations:

@pli.specialist(relation='test-subconcept', module='PL-KERNEL', create=True, arity=2)
def testSubconceptSpecialist(frame, lastMove):
    """Example Python specialist implementation to test and demonstrate the inference engine API.
    """
    iterator = pli.getFrameIterator(frame)
    #concept = pli.getConcept('CONCEPT', 'PL-KERNEL')
    if iterator is None:
        # first time around:
        if pli.isFrameBindingPattern(frame, 'BB'):
            sub = pli.getNthFrameBinding(frame, 0)
            sup = pli.getNthFrameBinding(frame, 1)
            if pli.isInstance(sub, pli.CONCEPT_CONCEPT) and pli.isInstance(sup, pli.CONCEPT_CONCEPT) and pli.isSubrelation(sub, sup):
                return pli.FINAL_SUCCESS
            else:
                return pli.FAILURE
        elif pli.isFrameBindingPattern(frame, '_B'):
            sup = pli.getNthFrameBinding(frame, 1)
            if not pli.isInstance(sup, pli.CONCEPT_CONCEPT):
                return pli.FAILURE
            iterator = pli.getProperSubrelations(sup)
            pli.setFrameIterator(frame, iterator)
            if pli.setNthFrameBinding(frame, 0, sup):
                # handle the reflexive case first:
                return pli.CONTINUING_SUCCESS
        elif pli.isFrameBindingPattern(frame, 'B_'):
            sub = pli.getNthFrameBinding(frame, 0)
            if not pli.isInstance(sub, pli.CONCEPT_CONCEPT):
                return pli.FAILURE
            iterator = pli.getProperSuperrelations(sub)
            pli.setFrameIterator(frame, iterator)
            if pli.setNthFrameBinding(frame, 1, sub):
                # handle the reflexive case first:
                return pli.CONTINUING_SUCCESS
        elif pli.isFrameBindingPattern(frame, '__'):
            return pli.FAILURE
    # generate additional solutions:
    for conc in iterator:
        if pli.isInstance(conc, pli.CONCEPT_CONCEPT):
            if pli.isFrameBindingPattern(frame, '_B'):
                if pli.setNthFrameBinding(frame, 0, conc):
                    return pli.CONTINUING_SUCCESS
            else: # must be the other way around:
                if pli.setNthFrameBinding(frame, 1, conc):
                    return pli.CONTINUING_SUCCESS
    return pli.FAILURE

@pli.specialist(relation='test-subconcept2', module='PL-KERNEL', create=True, arity=2)
def testSubconcept2Specialist(frame, lastMove):
    """Example Python specialist implementation to test and demonstrate the inference engine API.
    Variant of the above that uses `getFrameBindingPattern'.
    """
    iterator = pli.getFrameIterator(frame)
    #concept = pli.getConcept('CONCEPT', 'PL-KERNEL')
    bindingPattern = pli.getFrameBindingPattern(frame)
    if iterator is None:
        # first time around:
        if bindingPattern == 'BB':
            sub = pli.getNthFrameBinding(frame, 0)
            sup = pli.getNthFrameBinding(frame, 1)
            if pli.isInstance(sub, pli.CONCEPT_CONCEPT) and pli.isInstance(sup, pli.CONCEPT_CONCEPT) and pli.isSubrelation(sub, sup):
                return pli.FINAL_SUCCESS
            else:
                return pli.FAILURE
        elif bindingPattern == '_B':
            sup = pli.getNthFrameBinding(frame, 1)
            if not pli.isInstance(sup, pli.CONCEPT_CONCEPT):
                return pli.FAILURE
            iterator = pli.getProperSubrelations(sup)
            pli.setFrameIterator(frame, iterator)
            if pli.setNthFrameBinding(frame, 0, sup):
                # handle the reflexive case first:
                return pli.CONTINUING_SUCCESS
        elif bindingPattern == 'B_':
            sub = pli.getNthFrameBinding(frame, 0)
            if not pli.isInstance(sub, pli.CONCEPT_CONCEPT):
                return pli.FAILURE
            iterator = pli.getProperSuperrelations(sub)
            pli.setFrameIterator(frame, iterator)
            if pli.setNthFrameBinding(frame, 1, sub):
                # handle the reflexive case first:
                return pli.CONTINUING_SUCCESS
        elif bindingPattern == '__':
            return pli.FAILURE
    # generate additional solutions:
    for conc in iterator:
        if pli.isInstance(conc, pli.CONCEPT_CONCEPT):
            if bindingPattern == '_B':
                if pli.setNthFrameBinding(frame, 0, conc):
                    return pli.CONTINUING_SUCCESS
            else: # must be the other way around:
                if pli.setNthFrameBinding(frame, 1, conc):
                    return pli.CONTINUING_SUCCESS
    return pli.FAILURE


@pli.computation(function='test-plus', module='PL-KERNEL', create=True)
def testPlus(x, y):
    return pli.createIntegerWrapper(int(x) + int(y))

@pli.computation(relation='test-equal', module='PL-KERNEL', create=True)
def testEqual(x, y):
    return pli.createBooleanWrapper(x == y)


class Test_Specialists_Computations(unittest.TestCase):

    def testUserDefinedSpecialists(self):
        pli.cc('PL-USER')
        value = list(pli.retrieve('all (test-subconcept ?x collection)'))
        ref = """[<proxy.NamedDescription COLLECTION>, <proxy.NamedDescription LIST>, <proxy.NamedDescription NUMERIC-SET>, ...]"""
        self.assertEqual(repr(value)[0:100], ref[0:100])
        value = list(pli.retrieve('all (test-subconcept2 ?x collection)'))
        self.assertEqual(repr(value)[0:100], ref[0:100])

    def testUserDefinedComputations(self):
        pli.cc('PL-USER')
        value = list(pli.retrieve('all (test-plus 2 3 ?x)'))
        self.assertTrue(int(value[0]) == 5)
        value = pli.ask('(test-plus 2 3 5)')
        self.assertTrue(pli.isTrue(value))
        value = pli.ask('(test-equal 1 1)')
        self.assertTrue(pli.isTrue(value))
        value = pli.ask('(test-equal 1 2)')
        self.assertTrue(pli.isFalse(value))
        value = pli.ask('(test-equal "a" "a")')
        self.assertTrue(pli.isTrue(value))
        value = pli.ask('(test-equal "a" "b")')
        self.assertTrue(pli.isFalse(value))


### Assert, retract:

### Rules:

### Frame queries:

### File operations:

### Extracting column values from propositions and iterators:

### Evaluation:

### Queries and support functions

### Inference Engine API:
# already partially exercised by specialist tests

### Properties:


### Running the tests:

if __name__ == '__main__':
    unittest.main()
