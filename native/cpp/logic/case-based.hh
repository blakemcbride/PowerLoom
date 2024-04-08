//  -*- Mode: C++ -*-

// case-based.hh

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



namespace logic {
  using namespace stella;

// Global declarations:
extern boolean oLOG_MATCH_RULESo;
extern boolean oLOG_ANTECEDENT_CONSTRUCTIONo;
extern int oNUM_NEIGHBORSo;
extern Keyword* oCASE_SOLUTION_COMBINATIONo;
extern List* oCASE_RULE_NAMESo;
extern int oNUM_CASESo;
extern int oNUM_TRAINING_PER_CASEo;
extern int oCASE_VARIABLE_COUNTERo;
extern int oBASE_COUNTERo;
extern List* oVISITED_INSTANCESo;
extern boolean oONLY_VARIABLIZE_VISITED_INSTANCESo;
extern List* oVISITED_PROPOSITIONSo;
extern List* oSEEN_INSTANCESo;
extern List* oDELETED_CASE_VARIABLESo;
extern HashTable* oSYMBOL_VARIABLE_HASH_TABLEo;
extern StringHashTable* oCASE_ANTECEDENT_TABLEo;
extern StringHashTable* oCASE_TYPES_TABLEo;
extern HashTable* oCASE_NAME_TABLEo;
extern boolean oPRINT_CASE_DISTANCESo;

// Function signatures:
void setNumNeighbors(int d);
void setNumNeighborsEvaluatorWrapper(Cons* arguments);
void setCaseSolutionCombination(Keyword* k);
void setNumTrainingPerCase(int d);
void setNumTrainingPerCaseEvaluatorWrapper(Cons* arguments);
void clearCases();
void addAllClassInstancesToCaseRule(Surrogate* kind);
void finalizeCases(Symbol* kind);
void buildCaseRule(Surrogate* kind);
void addCase(Symbol* inst, Symbol* kind);
void buildCaseFromInstance(LogicObject* inst, Surrogate* kind);
Vector* createCaseInstanceVector(Surrogate* clasS);
FloatWrapper* matchInstances(LogicObject* x, LogicObject* y);
Vector* createCaseValueVector(List* instances, Surrogate* slot);
Object* guess(Symbol* instName, Symbol* slotName);
Object* generateCaseBasedAnswer(LogicObject* probe, Surrogate* slot, List* cases);
Object* combineCaseAnswers(Vector* closest, Vector* scores, Vector* slots);
void trainCaseMatcher(Symbol* className, Symbol* slotName, int cycles);
void trainCaseMatcherEvaluatorWrapper(Cons* arguments);
void generateCaseRuleWoSlot(Vector* cases, Symbol* className, Symbol* slotName);
double trainAndTestCaseMatcher(Symbol* className, Symbol* slotName, int numTrain, int numTest, int cycles);
FloatWrapper* trainAndTestCaseMatcherEvaluatorWrapper(Cons* arguments);
double testCaseBasedReasoner(Symbol* className, Symbol* slotName, int numTrain, int numTest);
FloatWrapper* testCaseBasedReasonerEvaluatorWrapper(Cons* arguments);
double testCaseMatcher(Symbol* className, Symbol* slotName);
FloatWrapper* testCaseMatcherEvaluatorWrapper(Cons* arguments);
int generateCaseTrainingExamples(Vector* instances, Surrogate* slot);
void normalizeNumbers(Vector* vect);
void clearSlotFromClass(Symbol* className, Symbol* slotName);
Object* logicSymbol(Object* obj);
double calculateCaseMatch(Object* x, Object* y);
Cons* getMostSpecificClasses(LogicObject* instance);
List* findUniqueVariableNames(Cons* tree, List* names);
List* variablizeConsPropositions(List* antecedent);
List* variablizeInstances(List* form, List* instances);
boolean stringArgumentP(Cons* clause);
void filterAntecedent(List* antecedent, const char* ruleName);
Cons* findMatchingCaseVars(Cons* clause, List* antecedent, List* generatedVariables);
boolean parametersAlignedP(Cons* clause1, Cons* clause2, List* vars);
boolean variableArgP(Object* arg);
Cons* buildVariableConstraints(List* instances);
List* buildTypeDefs(List* instances);
void setPrintCaseDistances(boolean b);
void setPrintCaseDistancesEvaluatorWrapper(Cons* arguments);
List* getNearestNeighbors(TrainingExample* probe, List* cases, int k);
double euclideanDistance(Vector* vec1, Vector* vec2);
int hammingDistance(Vector* vec1, Vector* vec2);
Symbol* internLogicSymbol(const char* name);
void helpStartupCaseBased1();
void helpStartupCaseBased2();
void helpStartupCaseBased3();
void startupCaseBased();

// Auxiliary global declarations:
extern Keyword* KWD_CASE_BASED_WEIGHTED_VOTE;
extern Keyword* KWD_CASE_BASED_RETRACT_TRUE;
extern Symbol* SYM_CASE_BASED_LOGIC_DEFRULE;
extern Symbol* SYM_CASE_BASED_STELLA_FORALL;
extern Symbol* SYM_CASE_BASED_STELLA_eg;
extern Symbol* SYM_CASE_BASED_STELLA_AND;
extern Symbol* SYM_CASE_BASED_LOGIC_CASE_MATCH;
extern Symbol* SYM_CASE_BASED_LOGIC_pX;
extern Symbol* SYM_CASE_BASED_LOGIC_pY;
extern Symbol* SYM_CASE_BASED_PL_KERNEL_KB_CASE_MATCH;
extern Keyword* KWD_CASE_BASED_WEIGHTED_AVERAGE;
extern Surrogate* SGT_CASE_BASED_STELLA_FLOAT_WRAPPER;
extern Surrogate* SGT_CASE_BASED_STELLA_INTEGER_WRAPPER;
extern Keyword* KWD_CASE_BASED_AVERAGE;
extern Keyword* KWD_CASE_BASED_ASSERT_TRUE;
extern Symbol* SYM_CASE_BASED_LOGIC_OBJECT_NAME;
extern Symbol* SYM_CASE_BASED_STELLA_SECOND;
extern Symbol* SYM_CASE_BASED_LOGIC_CASES;
extern Surrogate* SGT_CASE_BASED_LOGIC_DESCRIPTION;
extern Surrogate* SGT_CASE_BASED_LOGIC_PATTERN_VARIABLE;
extern Surrogate* SGT_CASE_BASED_LOGIC_SKOLEM;
extern Surrogate* SGT_CASE_BASED_LOGIC_LOGIC_OBJECT;
extern Surrogate* SGT_CASE_BASED_STELLA_CONS;
extern Symbol* SYM_CASE_BASED_LOGIC_SOFT_EQ;
extern Symbol* SYM_CASE_BASED_LOGIC_STARTUP_CASE_BASED;
extern Symbol* SYM_CASE_BASED_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
