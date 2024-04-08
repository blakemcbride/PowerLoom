//  -*- Mode: C++ -*-

// unit-kb.cc

/*
 +---------------------------- BEGIN LICENSE BLOCK ---------------------------+
 |                                                                            |
 | Version: MPL 1.1/GPL 2.0/LGPL 2.1                                          |
 |                                                                            |
 | The contents of this file are subject to the Mozilla Public License        |
 | Version 1.1 (the "License"); you may not use this file except in           |
 | compliance with the License. You may obtain a copy of the License at       |
 | http://www.mozilla.org/MPL/                                                |
 |                                                                            |
 | Software distributed under the License is distributed on an "AS IS" basis, |
 | WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License   |
 | for the specific language governing rights and limitations under the       |
 | License.                                                                   |
 |                                                                            |
 | The Original Code is the PowerLoom KR&R System.                            |
 |                                                                            |
 | The Initial Developer of the Original Code is                              |
 | UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
 | 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
 |                                                                            |
 | Portions created by the Initial Developer are Copyright (C) 1997-2023      |
 | the Initial Developer. All Rights Reserved.                                |
 |                                                                            |
 | Contributor(s):                                                            |
 |                                                                            |
 | Alternatively, the contents of this file may be used under the terms of    |
 | either the GNU General Public License Version 2 or later (the "GPL"), or   |
 | the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),   |
 | in which case the provisions of the GPL or the LGPL are applicable instead |
 | of those above. If you wish to allow use of your version of this file only |
 | under the terms of either the GPL or the LGPL, and not to allow others to  |
 | use your version of this file under the terms of the MPL, indicate your    |
 | decision by deleting the provisions above and replace them with the notice |
 | and other provisions required by the GPL or the LGPL. If you do not delete |
 | the provisions above, a recipient may use your version of this file under  |
 | the terms of any one of the MPL, the GPL or the LGPL.                      |
 |                                                                            |
 +----------------------------- END LICENSE BLOCK ----------------------------+
*/

#include "logic/extensions/powerloom-extensions-system.hh"

namespace units {
  using namespace stella_utilities;
  using namespace stella;
  using namespace logic;

void startupUnitKb() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/UNIT-SUPPORT", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SYM_UNIT_KB_UNIT_KB_MEASURE = ((Symbol*)(internRigidSymbolWrtModule("MEASURE", getStellaModule("/UNIT-KB", true), 0)));
      KWD_UNIT_KB_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
      SYM_UNIT_KB_UNIT_KB_BASE_MEASURE = ((Symbol*)(internRigidSymbolWrtModule("BASE-MEASURE", getStellaModule("/UNIT-KB", true), 0)));
      KWD_UNIT_KB_AXIOMS = ((Keyword*)(internRigidSymbolWrtModule("AXIOMS", NULL, 2)));
      SYM_UNIT_KB_UNIT_KB_MEASURE_UNIT = ((Symbol*)(internRigidSymbolWrtModule("MEASURE-UNIT", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_UNIT_KB_VALUE_MEASURE = ((Symbol*)(internRigidSymbolWrtModule("VALUE-MEASURE", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_UNIT_KB_NUMERATOR_MEASURES = ((Symbol*)(internRigidSymbolWrtModule("NUMERATOR-MEASURES", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_UNIT_KB_DENOMINATOR_MEASURES = ((Symbol*)(internRigidSymbolWrtModule("DENOMINATOR-MEASURES", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_UNIT_KB_COMENSURATE_UNITS = ((Symbol*)(internRigidSymbolWrtModule("COMENSURATE-UNITS", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_UNIT_KB_UNITS = ((Symbol*)(internRigidSymbolWrtModule("UNITS", getStellaModule("/UNIT-KB", true), 0)));
      KWD_UNIT_KB__g = ((Keyword*)(internRigidSymbolWrtModule("->", NULL, 2)));
      SYM_UNIT_KB_UNIT_SUPPORT_pDIM = ((Symbol*)(internRigidSymbolWrtModule("?DIM", NULL, 0)));
      SYM_UNIT_KB_UNIT_KB_Ui = ((Symbol*)(internRigidSymbolWrtModule("U+", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_LOGIC_pZ = ((Symbol*)(internRigidSymbolWrtModule("?Z", getStellaModule("/LOGIC", true), 0)));
      SYM_UNIT_KB_UNIT_KB_U_ = ((Symbol*)(internRigidSymbolWrtModule("U-", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_UNIT_KB_Uo = ((Symbol*)(internRigidSymbolWrtModule("U*", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_UNIT_KB_U_DIV = ((Symbol*)(internRigidSymbolWrtModule("U-DIV", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_UNIT_KB_U_ABS = ((Symbol*)(internRigidSymbolWrtModule("U-ABS", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_UNIT_KB_U_SIGNUM = ((Symbol*)(internRigidSymbolWrtModule("U-SIGNUM", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_UNIT_KB_U_WITHIN_DELTA = ((Symbol*)(internRigidSymbolWrtModule("U-WITHIN-DELTA", getStellaModule("/UNIT-KB", true), 0)));
      KWD_UNIT_KB_eg = ((Keyword*)(internRigidSymbolWrtModule("=>", NULL, 2)));
      KWD_UNIT_KB_le = ((Keyword*)(internRigidSymbolWrtModule("<=", NULL, 2)));
      SYM_UNIT_KB_UNIT_KB_U_WITHIN_FACTOR = ((Symbol*)(internRigidSymbolWrtModule("U-WITHIN-FACTOR", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_UNIT_KB_U_MINIMUM_VALUE = ((Symbol*)(internRigidSymbolWrtModule("U-MINIMUM-VALUE", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_UNIT_KB_U_MAXIMUM_VALUE = ((Symbol*)(internRigidSymbolWrtModule("U-MAXIMUM-VALUE", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_UNIT_KB_U_SUM = ((Symbol*)(internRigidSymbolWrtModule("U-SUM", getStellaModule("/UNIT-KB", true), 0)));
      SYM_UNIT_KB_UNIT_SUPPORT_STARTUP_UNIT_KB = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-UNIT-KB", NULL, 0)));
      SYM_UNIT_KB_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("STARTUP-UNIT-KB", "(DEFUN STARTUP-UNIT-KB () :PUBLIC? TRUE)", ((cpp_function_code)(&startupUnitKb)), NULL);
      { MethodSlot* function = lookupFunction(SYM_UNIT_KB_UNIT_SUPPORT_STARTUP_UNIT_KB);

        setDynamicSlotValue(function->dynamicSlots, SYM_UNIT_KB_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupUnitKb"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("UNIT-SUPPORT")))));
      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("PL-KERNEL-KB", true));
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        defconcept(consList(4, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_MEASURE))), ((Cons*)(copyConsTree(NIL))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("A (pre-defined) measure of some physical quantity."))))));
        defconcept(consList(6, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_BASE_MEASURE))), ((Cons*)(copyConsTree(getQuotedTree("((?M /UNIT-KB/MEASURE) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("A base measure.  One that defines fundamental units which\nare not composed of any other units.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((CLOSED /UNIT-KB/BASE-MEASURE) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        defrelation(consList(6, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_MEASURE_UNIT))), ((Cons*)(copyConsTree(getQuotedTree("(((?M /UNIT-KB/MEASURE) (?U STRING)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("A mapping between a Measure and the unit names that belong\nto that measure.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((CLOSED /UNIT-KB/MEASURE-UNIT) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        deffunction(consList(6, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_VALUE_MEASURE))), ((Cons*)(copyConsTree(getQuotedTree("((?DIM (?M /UNIT-KB/MEASURE)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("A mapping from a dimensioned value to the corresponding measure.\nIt may not, in fact, exist for dimensions that are formed by ad hoc\ncombinations of units or by arithmetic manipulations of dimensions.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (COMPUTED /UNIT-KB/VALUE-MEASURE) (CLOSED /UNIT-KB/VALUE-MEASURE) (RELATION-SPECIALIST /UNIT-KB/VALUE-MEASURE U-VALUE-MEASURE-SPECIALIST)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        deffunction(consList(6, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_NUMERATOR_MEASURES))), ((Cons*)(copyConsTree(getQuotedTree("((?DIM (?M /PL-KERNEL-KB/LIST)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("A mapping from a dimensioned value or a measure to\na list of the base measures in the numerator of the expression.\nThe measures will be in a canonical order.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (COMPUTED /UNIT-KB/NUMERATOR-MEASURES) (RELATION-SPECIALIST /UNIT-KB/NUMERATOR-MEASURES U-BASE-MEASURES-SPECIALIST)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        deffunction(consList(6, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_DENOMINATOR_MEASURES))), ((Cons*)(copyConsTree(getQuotedTree("((?DIM (?M /PL-KERNEL-KB/LIST)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("A mapping from a dimensioned value or a measure to\na list of the base measures in the denominator of the expression.\nThe measures will be in a canonical order.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (COMPUTED /UNIT-KB/DENOMINATOR-MEASURES) (RELATION-SPECIALIST /UNIT-KB/DENOMINATOR-MEASURES U-BASE-MEASURES-SPECIALIST)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        defrelation(consList(6, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_COMENSURATE_UNITS))), ((Cons*)(copyConsTree(getQuotedTree("((?X ?Y) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("A (computed) relation between units expressions that are\ncomensurate.  That means they can be compared with one another,\nadded or subtracted.  Works with either dimensioned quantities or\nunit expressions (strings)")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (COMPUTED /UNIT-KB/COMENSURATE-UNITS) (RELATION-SPECIALIST /UNIT-KB/COMENSURATE-UNITS COMENSURATE-UNITS-SPECIALIST) (HANDLES-REVERSE-POLARITY COMENSURATE-UNITS-SPECIALIST)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        deffunction(consList(8, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_UNITS))), ((Cons*)(copyConsTree(getQuotedTree("(((?M NUMBER) (?U STRING)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB__g, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_SUPPORT_pDIM))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Connects a MAGNITUDE STRING representation of a dimensioned number\n to the actual\ninternal representation.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (COMPUTED /UNIT-KB/UNITS) (RELATION-EVALUATOR /UNIT-KB/UNITS UNITS-EVALUATOR) (RELATION-SPECIALIST /UNIT-KB/UNITS UNITS-SPECIALIST) (GOES-TRUE-DEMON /UNIT-KB/UNITS UNITS-EVALUATOR)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        deffunction(consList(8, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_Ui))), ((Cons*)(copyConsTree(getQuotedTree("((?X ?Y) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB__g, ((Symbol*)(copyConsTree(SYM_UNIT_KB_LOGIC_pZ))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Function that adds two dim numbers.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (COMPUTED /UNIT-KB/U+) (RELATION-CONSTRAINT /UNIT-KB/U+ U-PLUS-CONSTRAINT) (RELATION-SPECIALIST /UNIT-KB/U+ /PL-KERNEL-KB/CONSTRAINT-SPECIALIST)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        deffunction(consList(8, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_U_))), ((Cons*)(copyConsTree(getQuotedTree("((?X ?Y) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB__g, ((Symbol*)(copyConsTree(SYM_UNIT_KB_LOGIC_pZ))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Function that subtracts two dim numbers.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (COMPUTED /UNIT-KB/U-) (RELATION-CONSTRAINT /UNIT-KB/U- U-MINUS-CONSTRAINT) (RELATION-SPECIALIST /UNIT-KB/U- /PL-KERNEL-KB/CONSTRAINT-SPECIALIST)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        deffunction(consList(8, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_Uo))), ((Cons*)(copyConsTree(getQuotedTree("((?X ?Y) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB__g, ((Symbol*)(copyConsTree(SYM_UNIT_KB_LOGIC_pZ))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Function that multiplies two dim numbers.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (COMPUTED /UNIT-KB/U*) (RELATION-CONSTRAINT /UNIT-KB/U* U-TIMES-CONSTRAINT) (RELATION-SPECIALIST /UNIT-KB/U* /PL-KERNEL-KB/CONSTRAINT-SPECIALIST)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        deffunction(consList(8, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_U_DIV))), ((Cons*)(copyConsTree(getQuotedTree("((?X ?Y) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB__g, ((Symbol*)(copyConsTree(SYM_UNIT_KB_LOGIC_pZ))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Function that divides two dim numbers.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (COMPUTED /UNIT-KB/U-DIV) (RELATION-CONSTRAINT /UNIT-KB/U-DIV U-DIVIDE-CONSTRAINT) (RELATION-SPECIALIST /UNIT-KB/U-DIV /PL-KERNEL-KB/CONSTRAINT-SPECIALIST)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        deffunction(consList(8, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_U_ABS))), ((Cons*)(copyConsTree(getQuotedTree("((?X) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB__g, ((Symbol*)(copyConsTree(SYM_UNIT_KB_LOGIC_pZ))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Absolute value of dim number.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (COMPUTED /UNIT-KB/U-ABS) (RELATION-SPECIALIST /UNIT-KB/U-ABS U-ABS-SPECIALIST)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        deffunction(consList(8, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_U_SIGNUM))), ((Cons*)(copyConsTree(getQuotedTree("((?X) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB__g, ((Cons*)(copyConsTree(getQuotedTree("((?Z INTEGER) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Signum function of dim number.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (COMPUTED /UNIT-KB/U-SIGNUM) (RELATION-SPECIALIST /UNIT-KB/U-SIGNUM U-SIGNUM-SPECIALIST)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        defrelation(consList(8, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_U_WITHIN_DELTA))), ((Cons*)(copyConsTree(getQuotedTree("((?X ?Y ?Z) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("?X and ?Y do not differ in value by more than ?Z.\n?Z must be positive.\n\nFor example (/unit-kb/u-within-delta (units 10.0 \"ft\") (units 3.0 \"m\") (units 2 \"in\"))\nis true.  This relation is useful for numeric comparisons where floating point\ncomputations (or other rounding errors) introduce minor inaccuracies\nthat prevent a straight equality test from succeeding.")))), KWD_UNIT_KB_eg, ((Cons*)(copyConsTree(getQuotedTree("((>= (/UNIT-KB/U-SIGNUM ?Z) 0) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB_le, ((Cons*)(copyConsTree(getQuotedTree("((=< (/UNIT-KB/U-ABS (/UNIT-KB/U- ?X ?Y)) ?Z) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        defrelation(consList(8, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_U_WITHIN_FACTOR))), ((Cons*)(copyConsTree(getQuotedTree("((?X ?Y ?Z) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("?X and ?Y are with factor ?Z of each other.  The\nfactor is applied relative to ?X.  ?Z must be positive.\n\nThat means (/unit-kb/u-within-factor (units 100 \"km\") (units 60 \"km\") (units 0.5 \"\"))\nis true (60km is in the range 50km-150km), but the converse\n  (/unit-kb/u-within-factor (units 60 \"km\") (units 100 \"km\") (units 50 \"%\"))\nis not (100km is not in the range 30km-90km).")))), KWD_UNIT_KB_eg, ((Cons*)(copyConsTree(getQuotedTree("((>= (/UNIT-KB/U-SIGNUM ?Z) 0) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB_le, ((Cons*)(copyConsTree(getQuotedTree("((=< (/UNIT-KB/U-ABS (/UNIT-KB/U- ?X ?Y)) (/UNIT-KB/U* ?Z (/UNIT-KB/U-ABS ?X))) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        defrelation(consList(6, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_U_MINIMUM_VALUE))), ((Cons*)(copyConsTree(getQuotedTree("(((?L /PL-KERNEL-KB/COLLECTION) ?MIN) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Binds ?min to the minimum of the dimensioned numbers in the list ?l.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (RELATION-SPECIALIST /UNIT-KB/U-MINIMUM-VALUE MINIMUM-OF-UNITS-SPECIALIST) (SINGLE-VALUED /UNIT-KB/U-MINIMUM-VALUE)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        defrelation(consList(6, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_U_MAXIMUM_VALUE))), ((Cons*)(copyConsTree(getQuotedTree("(((?L /PL-KERNEL-KB/COLLECTION) ?MAX) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Binds ?max to the maximum of the dimensioned numbers in the list ?l.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (RELATION-SPECIALIST /UNIT-KB/U-MAXIMUM-VALUE MAXIMUM-OF-UNITS-SPECIALIST) (SINGLE-VALUED /UNIT-KB/U-MAXIMUM-VALUE)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        defrelation(consList(6, ((Symbol*)(copyConsTree(SYM_UNIT_KB_UNIT_KB_U_SUM))), ((Cons*)(copyConsTree(getQuotedTree("(((?L /PL-KERNEL-KB/COLLECTION) ?SUM) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))), KWD_UNIT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Binds ?sum to the sum of the dimensioned numbers in the list ?l.")))), KWD_UNIT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (RELATION-SPECIALIST /UNIT-KB/U-SUM SUM-OF-UNITS-SPECIALIST) (SINGLE-VALUED /UNIT-KB/U-SUM)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT"))))));
        asserT(((Cons*)(copyConsTree(getQuotedTree("((AND (COMPUTED-PROCEDURE UNITS-EVALUATOR) (COMPUTED-PROCEDURE UNITS-SPECIALIST) (COMPUTED-PROCEDURE U-ABS-SPECIALIST) (COMPUTED-PROCEDURE U-SIGNUM-SPECIALIST) (COMPUTED-PROCEDURE MINIMUM-OF-UNITS-SPECIALIST) (COMPUTED-PROCEDURE MAXIMUM-OF-UNITS-SPECIALIST) (COMPUTED-PROCEDURE SUM-OF-UNITS-SPECIALIST) (COMPUTED-PROCEDURE U-VALUE-MEASURE-SPECIALIST) (COMPUTED-PROCEDURE U-BASE-MEASURES-SPECIALIST) (COMPUTED-PROCEDURE COMENSURATE-UNITS-SPECIALIST)) \"/UNIT-SUPPORT\")", "/UNIT-SUPPORT")))));
        initializeMeasureConcepts();
        processDefinitions();
      }
    }
  }
}

Symbol* SYM_UNIT_KB_UNIT_KB_MEASURE = NULL;

Keyword* KWD_UNIT_KB_DOCUMENTATION = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_BASE_MEASURE = NULL;

Keyword* KWD_UNIT_KB_AXIOMS = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_MEASURE_UNIT = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_VALUE_MEASURE = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_NUMERATOR_MEASURES = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_DENOMINATOR_MEASURES = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_COMENSURATE_UNITS = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_UNITS = NULL;

Keyword* KWD_UNIT_KB__g = NULL;

Symbol* SYM_UNIT_KB_UNIT_SUPPORT_pDIM = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_Ui = NULL;

Symbol* SYM_UNIT_KB_LOGIC_pZ = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_U_ = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_Uo = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_U_DIV = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_U_ABS = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_U_SIGNUM = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_U_WITHIN_DELTA = NULL;

Keyword* KWD_UNIT_KB_eg = NULL;

Keyword* KWD_UNIT_KB_le = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_U_WITHIN_FACTOR = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_U_MINIMUM_VALUE = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_U_MAXIMUM_VALUE = NULL;

Symbol* SYM_UNIT_KB_UNIT_KB_U_SUM = NULL;

Symbol* SYM_UNIT_KB_UNIT_SUPPORT_STARTUP_UNIT_KB = NULL;

Symbol* SYM_UNIT_KB_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace units
