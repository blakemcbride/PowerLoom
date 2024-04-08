//  -*- Mode: C++ -*-

// rule-induction.hh

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

// Class definitions:
class DecisionTree : public StandardObject {
public:
  Symbol* feature;
  int featureIndex;
  Proposition* proposition;
  boolean truthValue;
  Symbol* concept;
  DecisionTree* trueBranch;
  DecisionTree* falseBranch;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
};


// Global declarations:
extern Keyword* oRULE_INDUCTION_STRATEGYo;
extern Keyword* oSIGNATURE_STRATEGYo;
extern boolean oENABLE_USER_THINGo;
extern boolean oOPTIMIZE_INDUCED_QUERIESo;
extern boolean oSIMPLIFY_RULE_ANTECEDENTpo;
extern boolean oTRACE_ID3o;
extern boolean oTRACE_FOILo;
extern boolean oINDUCE_RULES_FROM_SIGNATURESo;
extern int oNUM_LGGSo;
extern boolean oENFORCE_LINKED_VARIABLESo;
extern boolean oLOG_INDUCED_RULESo;
extern boolean oALLOW_RECURSIVE_DECISION_NODESo;
extern boolean oLOG_DECISION_RULE_CONSTRUCTIONo;
extern double LOG_2;
extern List* oINDUCED_DECISION_RULESo;
extern int oINDUCED_RULE_COUNTERo;
extern Vector* oCANDIDATE_CLAUSESo;
extern DECLARE_STELLA_SPECIAL(oBOTTOM_UP_VARIABLE_COUNTERo, int );

// Function signatures:
void setSignatureStrategy(Keyword* k);
void setSignatureRules(boolean b);
void setSignatureRulesEvaluatorWrapper(Cons* arguments);
void setRuleInductionStrategy(Keyword* k);
void setRecursiveDecisionNodes(boolean b);
void setRecursiveDecisionNodesEvaluatorWrapper(Cons* arguments);
DecisionTree* newDecisionTree();
Object* accessDecisionTreeSlotValue(DecisionTree* self, Symbol* slotname, Object* value, boolean setvalueP);
void induceInferenceRules(Symbol* relationName, Symbol* className);
void modularInduceInferenceRules(Symbol* relationName, Symbol* className, List* modules);
void bottomUpRuleInduction(List* examples, boolean simplifyRuleP);
void bottomUpRuleInductionEvaluatorWrapper(Cons* arguments);
Cons* learnOneRuleBottomUp(List* positive, List* negative);
boolean containsOutputVariableP(Cons* clause, Cons* outputVariables);
Cons* simplifyAntecedent(Cons* antecedent, Cons* outputVariables, List* positive, List* negative);
Cons* leastGeneralGeneralization(Cons* clause1, Cons* clause2);
Cons* generalizeInequality(Cons* probe, Cons* match, List* bindings);
boolean bothNumbersP(Object* t1, Object* t2);
boolean eitherNumbersP(Object* t1, Object* t2);
Cons* removeRedundantClauses(Cons* clauses);
Object* lookupVariableInBindings(Object* obj1, Object* obj2, List* bindings);
Cons* learnOneRuleBottomUpFromSignatures(List* positive, List* negative, List* covered, Vector* consProps);
List* intersectSignatures(Vector* sig1, Vector* sig2);
List* removeSignatureCoveredExamples(List* indices, List* examples);
int numSignatureIndicesCovered(List* indices, List* examples);
boolean signatureIndicesCoverAnyExampleP(List* indices, List* examples);
boolean signatureIndicesCoverExampleP(List* indices, TrainingExample* example);
void topDownRuleInduction(List* examples);
Cons* buildAntecedentFromRuleIndex(Vector* props, List* ruleIndex);
Cons* learnOneRuleTopDownFromSignatures(List* positive, List* negative, List* covered_pos, Vector* consProps);
void updateExampleMatches(List* examples, int index, IntegerWrapper* matchValue);
void updateCoveredExamples(int feature_index, List* covered_pos, List* covered_neg);
int countExampleMatches(List* examples, int index, IntegerWrapper* matchValue);
double foilGain(int featureIndex, double utility, List* coveredPos, List* coveredNeg);
double foilUtility(int p, int n);
Cons* learnOneRuleTopDown(Vector* propositions, List* positive, List* negative);
Cons* specializeRule(Cons* rule, Vector* propositions, List* positive, List* negative);
void removeExcludedExamples(Cons* rule, List* coveredPos, List* coveredNeg);
double queryFoilGain(Cons* rule, double utility, List* coveredPos, List* coveredNeg);
void queryAndUpdateCoveredExamples(Cons* rule, List* uncovered, List* covered);
void removeCoveredExamples(Cons* rule, List* uncovered);
int numExamplesCovered(Cons* rule, List* examples);
List* getCoveredExamples(Cons* rule, List* uncovered);
boolean ruleCoversAnyExampleP(Cons* rule, List* examples);
boolean ruleCoversExampleP(Cons* reverseRule, TrainingExample* example);
List* linkVariablesInInducedRule(Cons* rule, List* examples, Vector* consProps);
Vector* evaluateRuleInduction(Symbol* relationName, Symbol* className, int numTrials, int curveSplits);
Vector* evaluateRuleInductionEvaluatorWrapper(Cons* arguments);
double trainAndTestRuleInduction(List* trainSet, List* testSet);
void induceDecisionRules(Symbol* relationName, Symbol* className);
void modularInduceDecisionRules(Symbol* relationName, Symbol* className, List* modules);
boolean askDecisionTree(DecisionTree* tree, Cons* query);
boolean traverseDecisionTree(DecisionTree* tree, Vector* features);
DecisionTree* induceDecisionTree(List* examples);
void addPropositionsToDecisionTree(DecisionTree* tree, HashTable* table);
Object* buildDecisionTree(List* examples, List* features, Cons* featureStack);
double expectedEntropy(int featureIndex, List* examples);
double entropy(int p, int n);
void printDecisionTree(DecisionTree* tree, std::ostream* stream);
void helpPrintDecisionTree(DecisionTree* tree, int level, std::ostream* stream);
List* getRulesFromTree(Cons* query, DecisionTree* tree);
List* buildRulesFromTree(DecisionTree* tree, List* props);
void extractPathsFromTree(DecisionTree* tree, Cons* antecedentStack, List* antecedent);
void sortExamplesByTree(DecisionTree* tree, List* examples, List* sortedExamples);
void assertInducedRules();
void setCandidateClauses(Symbol* className);
List* getVariablesFromPropositionList(List* props);
List* getVariablesFromConsPropositions(Cons* props);
List* helpGetVariablesFromConsPropositions(Object* ele, List* theList);
List* getPropositionsFromDecisionTree(DecisionTree* tree);
void helpStartupRuleInduction1();
void helpStartupRuleInduction2();
void startupRuleInduction();

// Auxiliary global declarations:
extern Keyword* KWD_RULE_INDUCTION_TOP_DOWN;
extern Surrogate* SGT_RULE_INDUCTION_LOGIC_DECISION_TREE;
extern Symbol* SYM_RULE_INDUCTION_LOGIC_FEATURE;
extern Symbol* SYM_RULE_INDUCTION_LOGIC_FEATURE_INDEX;
extern Symbol* SYM_RULE_INDUCTION_LOGIC_PROPOSITION;
extern Symbol* SYM_RULE_INDUCTION_LOGIC_TRUTH_VALUE;
extern Symbol* SYM_RULE_INDUCTION_LOGIC_CONCEPT;
extern Symbol* SYM_RULE_INDUCTION_LOGIC_TRUE_BRANCH;
extern Symbol* SYM_RULE_INDUCTION_LOGIC_FALSE_BRANCH;
extern Keyword* KWD_RULE_INDUCTION_BOTTOM_UP;
extern Symbol* SYM_RULE_INDUCTION_LOGIC_pY;
extern Symbol* SYM_RULE_INDUCTION_STELLA_eg;
extern Symbol* SYM_RULE_INDUCTION_STELLA_AND;
extern Surrogate* SGT_RULE_INDUCTION_STELLA_CONS;
extern Symbol* SYM_RULE_INDUCTION_STELLA_NOT;
extern Symbol* SYM_RULE_INDUCTION_STELLA_g;
extern Symbol* SYM_RULE_INDUCTION_STELLA_l;
extern Symbol* SYM_RULE_INDUCTION_STELLA_ge;
extern Symbol* SYM_RULE_INDUCTION_STELLA_el;
extern Surrogate* SGT_RULE_INDUCTION_STELLA_NUMBER_WRAPPER;
extern Symbol* SYM_RULE_INDUCTION_LOGIC_FAIL;
extern Keyword* KWD_RULE_INDUCTION_DECISION_TREE;
extern Symbol* SYM_RULE_INDUCTION_LOGIC_USER_THING;
extern Symbol* SYM_RULE_INDUCTION_STELLA_EXISTS;
extern Keyword* KWD_RULE_INDUCTION_TIMEOUT;
extern Keyword* KWD_RULE_INDUCTION_DONT_OPTIMIZEp;
extern Symbol* SYM_RULE_INDUCTION_STELLA_TRUE;
extern Symbol* SYM_RULE_INDUCTION_LOGIC_DEFRULE;
extern Symbol* SYM_RULE_INDUCTION_STELLA_FORALL;
extern Keyword* KWD_RULE_INDUCTION_OR;
extern Keyword* KWD_RULE_INDUCTION_NOT;
extern Keyword* KWD_RULE_INDUCTION_AND;
extern Surrogate* SGT_RULE_INDUCTION_LOGIC_PATTERN_VARIABLE;
extern Surrogate* SGT_RULE_INDUCTION_LOGIC_PROPOSITION;
extern Surrogate* SGT_RULE_INDUCTION_LOGIC_LOGIC_OBJECT;
extern Symbol* SYM_RULE_INDUCTION_LOGIC_STARTUP_RULE_INDUCTION;
extern Symbol* SYM_RULE_INDUCTION_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
