//  -*- Mode: C++ -*-

// optimize.hh

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
class GoalRecord : public StandardObject {
public:
  List* generatorGoals;
  List* otherGoals;
public:
  virtual Surrogate* primaryType();
};


// Global declarations:
extern DECLARE_STELLA_SPECIAL(oDISTRIBUTEDOPENGOALpo, boolean );
extern BooleanVector* V_0_0;
extern BooleanVector* V_1_0;
extern BooleanVector* V_0_1;
extern BooleanVector* V_1_1;
extern List* V_1_0_AND_V_0_1;
extern List* V_1_0_SINGLETON;
extern List* V_0_1_SINGLETON;
extern double ESTIMATED_SLOT_VALUE_COLLECTION_SIZE;
extern double ESTIMATED_NUMBER_OF_PREDICATE_BINDINGS;
extern double ESTIMATED_SIZE_OF_CLASS_EXTENSION;
extern double ESTIMATED_CARDINALITY_OF_DESCRIPTION;
extern double ESTIMATED_CARDINALITY_OF_MEMBER_OF;
extern double ESTIMATED_CARDINALITY_OF_SUBSET_OF;
extern double INFERABLE_PENALTY_COST;
extern double SUBSET_OF_PENALTY_COST;
extern DECLARE_STELLA_SPECIAL(oOPTIMALGOALORDERINGRECURSIONSo, int );
extern int oOPTIMAL_GOAL_ORDERING_CUTOFFo;
extern DECLARE_STELLA_SPECIAL(oQUERYOPTIMIZERCONTROLFRAMEo, ControlFrame* );
extern DECLARE_STELLA_SPECIAL(oBOUNDTOOFFSETCOUNTERo, int );
extern Keyword* oQUERY_OPTIMIZATION_STRATEGYo;
extern DECLARE_STELLA_SPECIAL(oPOSTOPTIMIZATIONpo, boolean );

// Function signatures:
GoalRecord* newGoalRecord();
Object* accessGoalRecordSlotValue(GoalRecord* self, Symbol* slotname, Object* value, boolean setvalueP);
boolean variableBoundP(PatternVariable* variable);
boolean argumentBoundP(Object* argument);
boolean quantifiedArgumentBoundP(Object* argument, List* quantifiedvars);
boolean unboundVariableP(Object* argument);
boolean hasDisjunctionP(Proposition* goal);
boolean modalGoalP(Proposition* goal);
boolean hasInversionsP(Proposition* goal);
boolean computedTermP(Description* self);
boolean computedConstraintP(Description* self);
boolean computedPredicateP(Proposition* goal);
int simulateCreateChoicePoint();
boolean relationSupportsExtensionP(NamedDescription* self);
boolean generatorCollectionP(Object* collection);
void initializeOptimizerGoalRecords(int size);
GoalRecord* goalRecord(PatternVariable* variable);
void helpDistributeGoal(Object* argument, Proposition* parentgoal, boolean generatorP);
void distributeOpenGoal(Proposition* goal);
List* getBinaryUniquenessVectors(NamedDescription* self);
List* getUniquenessVectors(NamedDescription* self);
BooleanVector* getBinaryIndexingVector(NamedDescription* self);
BooleanVector* getIndexingVector(NamedDescription* self);
void updateObservedCardinality(NamedDescription* self, int cardinality);
int accessObservedCardinality(Description* self);
double estimateCardinalityOfExtension(NamedDescription* description);
double estimateMemberOfGoalFanout(Proposition* goal);
double estimatePredicateGoalFanout(Proposition* goal);
double estimateGoalCost(Proposition* goal);
double estimateGoalFanout(Proposition* goal);
Proposition* cheapestGeneratorGoal(PatternVariable* variable, double& _Return1, double& _Return2);
void propagateSingleValuedConstraints(Proposition* goal, List* goalsequence);
void collectClosedGoals(List* goals, List* goalsequence);
void simulateBindVariableAndPropagateConstraints(PatternVariable* variable, List* goalsequence);
void bindAllVariablesInGeneratorGoal(Proposition* goal, List* goalsequence);
void computeOptimalOpenGoalOrdering(List* optimizervariables, int numberofopengoals, List* goalsequence, double priorcost, double priorfanout);
void computeGreedyOpenGoalOrdering(List* optimizervariables, int numberofopengoals, List* goalsequence, double priorcost, double priorfanout);
void computeBackupOpenGoalOrdering(List* goalsequence);
void collectUnboundGoalVariables(Proposition* goal, List* unboundvariables);
void extractOpenGoalClusters(List* opengoals, List* opengoalclusters);
void collectOptimizerVariables(Proposition* proposition, List* collection);
boolean biggerConjunctionP(Proposition* prop1, Proposition* prop2);
void computeOpenGoalOrdering(Proposition* andproposition, List* opengoals, List* goalsequence);
void optimizeOrderingOfConjuncts(Proposition* andproposition);
void reorderGoals(Proposition* andproposition, List* initiallyclosedgoals, List* goalsequence, List* residuegoals);
void simulateBindVariableToValue(Object* formula);
void warnOfUnboundVariableArgument(Proposition* proposition);
void simulateGoalEvaluation(Proposition* goal);
void simulateAndOptimizeArgument(Object* formula);
void simulateAndOptimizeQuery(Proposition* proposition);
void initializeOptimizerMemory(int stacksize);
void optimizeQuery(Description* description, BooleanVector* booleanvector, ControlFrame* parentframe);
boolean useDynamicQueryOptimizationP();
boolean dynamicallyOptimizePropositionP(Proposition* self);
boolean useStaticQueryOptimizationP();
boolean staticallyOptimizePropositionP(Proposition* self);
boolean tryToClusterConjunctionsP();
Description* selectOptimalQueryPattern(Description* description, BooleanVector* booleanvector, ControlFrame* parentframe);
double dynamicallyEstimateInferenceCost(NamedDescription* self);
double dynamicallyEstimateGoalCost(Proposition* goal);
double dynamicallyEstimateGoalFanout(Proposition* goal);
double dynamicallyEstimatePredicateGoalFanout(Proposition* goal);
double dynamicallyEstimateInstanceOfGoalFanout(Proposition* goal);
double dynamicallyEstimateExtensionSize(NamedDescription* description);
int countBoundArguments(Proposition* goal);
double dynamicallyEstimateUnboundVariablePenalty(Proposition* goal);
void dynamicallyReoptimizeArguments(Vector* arguments, int cursor);
void simplifyDescription(Description* description, boolean postoptimizationP);
Vector* copyListToArgumentsVector(List* arguments);
boolean conjunctCancelsIsaPropositionP(Proposition* isaconjunct, Proposition* otherconjunct);
void simplifyConjunction(Proposition* andproposition);
void simplifyProposition(Proposition* proposition);
Description* copyDescription(Description* self, KeyValueMap* parentmapping, boolean addbacklinksP);
PatternVariable* copyVariable(PatternVariable* self, KeyValueMap* mapping);
Vector* copyVariablesVector(Vector* self, KeyValueMap* mapping);
Proposition* copyProposition(Proposition* self, KeyValueMap* mapping);
Object* copyPropositionArgument(Object* self, KeyValueMap* mapping);
Object* mappedValueOf(Object* self, KeyValueMap* mapping, boolean createskolemP);
boolean singleValuedPredicateP(Proposition* proposition);
boolean binaryPropositionP(Proposition* proposition);
Proposition* inheritEquivalentProposition(Skolem* skolem, Object* value);
Proposition* inheritFunctionProposition(Proposition* self, KeyValueMap* mapping, boolean createskolemP);
boolean equalUpToSkolemIdentityP(Object* inheritedarg, Object* basearg, KeyValueMap* mapping);
Proposition* oldFindSimilarProposition(Proposition* proposition, KeyValueMap* mapping);
Proposition* newFindSimilarProposition(Proposition* proposition, KeyValueMap* mapping);
Proposition* findSimilarProposition(Proposition* proposition, KeyValueMap* mapping);
Object* inheritPropositionArgument(Object* argument, Proposition* parent, KeyValueMap* mapping);
Proposition* eradicateHoldsProposition(Proposition* self);
Proposition* inheritProposition(Proposition* self, KeyValueMap* mapping);
Skolem* createSkolemForUnmappedVariable(PatternVariable* variable, KeyValueMap* mapping);
Cons* inheritAsTopLevelProposition(Proposition* proposition, KeyValueMap* mapping);
boolean propositionReferencesTermsP(Proposition* self, HashSet* terms);
Cons* createSkolemPropositionsQuery(Cons* inheritedprops, Description* description, KeyValueMap* mapping);
Cons* filterImpliedSkolemPropositions(Cons* inheritedprops, Description* description, Vector* arguments, KeyValueMap* mapping);
boolean mapAndEnqueueVariableP(Object* variable, Object* localvalue, KeyValueMap* mapping);
void collectStructuralFunctions(Proposition* proposition, List* structuralfunctions);
List* computeStructuralFunctionEvaluationOrder(Description* self);
List* getStructuralFunctionEvaluationOrder(Description* self);
boolean mapFunctionalValueP(Proposition* proposition, KeyValueMap* mapping);
Cons* inheritDescriptionPropositions(Vector* arguments, Description* description, KeyValueMap*& _Return1);
void inheritUnnamedDescription(Object* self, Description* description, boolean defaulttrueP);
void vectorDinheritUnnamedDescription(Vector* arguments, Description* description, boolean defaulttrueP);
void logicObjectDinheritUnnamedDescription(LogicObject* instance, Description* description, boolean defaulttrueP);
void inheritDescription(Vector* arguments, Description* description, boolean defaulttrueP);
void helpStartupOptimize1();
void helpStartupOptimize2();
void helpStartupOptimize3();
void helpStartupOptimize4();
void helpStartupOptimize5();
void startupOptimize();

// Auxiliary global declarations:
extern Surrogate* SGT_OPTIMIZE_LOGIC_GOAL_RECORD;
extern Symbol* SYM_OPTIMIZE_LOGIC_GENERATOR_GOALS;
extern Symbol* SYM_OPTIMIZE_LOGIC_OTHER_GOALS;
extern Surrogate* SGT_OPTIMIZE_LOGIC_PATTERN_VARIABLE;
extern Surrogate* SGT_OPTIMIZE_LOGIC_PROPOSITION;
extern Symbol* SYM_OPTIMIZE_LOGIC_IO_VARIABLES;
extern Surrogate* SGT_OPTIMIZE_LOGIC_DESCRIPTION;
extern Symbol* SYM_OPTIMIZE_LOGIC_EXTERNAL_VARIABLES;
extern Keyword* KWD_OPTIMIZE_OR;
extern Symbol* SYM_OPTIMIZE_LOGIC_PERMUTATION_TABLE;
extern Surrogate* SGT_OPTIMIZE_PL_KERNEL_KB_COMPUTED;
extern Surrogate* SGT_OPTIMIZE_PL_KERNEL_KB_RELATION_CONSTRAINT;
extern Surrogate* SGT_OPTIMIZE_PL_KERNEL_KB_HOLDS;
extern Surrogate* SGT_OPTIMIZE_PL_KERNEL_KB_SETOF;
extern Surrogate* SGT_OPTIMIZE_PL_KERNEL_KB_LISTOF;
extern Surrogate* SGT_OPTIMIZE_PL_KERNEL_KB_ABSTRACT;
extern Surrogate* SGT_OPTIMIZE_LOGIC_NAMED_DESCRIPTION;
extern Symbol* SYM_OPTIMIZE_LOGIC_OPTIMIZER_GOAL_RECORDS;
extern Keyword* KWD_OPTIMIZE_FUNCTION;
extern Keyword* KWD_OPTIMIZE_EQUIVALENT;
extern Keyword* KWD_OPTIMIZE_ISA;
extern Keyword* KWD_OPTIMIZE_PREDICATE;
extern Keyword* KWD_OPTIMIZE_NOT;
extern Keyword* KWD_OPTIMIZE_FAIL;
extern Keyword* KWD_OPTIMIZE_IMPLIES;
extern Symbol* SYM_OPTIMIZE_LOGIC_UNIQUENESSVECTORS;
extern Symbol* SYM_OPTIMIZE_LOGIC_INVERSE_DESCRIPTION;
extern Symbol* SYM_OPTIMIZE_LOGIC_INDEXING_VECTOR;
extern Surrogate* SGT_OPTIMIZE_PL_KERNEL_KB_OBSERVED_CARDINALITY_OF;
extern Surrogate* SGT_OPTIMIZE_STELLA_INTEGER_WRAPPER;
extern Surrogate* SGT_OPTIMIZE_STELLA_COLLECTION;
extern Surrogate* SGT_OPTIMIZE_PL_KERNEL_KB_MEMBER_OF;
extern Keyword* KWD_OPTIMIZE_OPTIMIZER;
extern Symbol* SYM_OPTIMIZE_LOGIC_BEST_GOAL_SEQUENCE;
extern Symbol* SYM_OPTIMIZE_LOGIC_BEST_COST;
extern Keyword* KWD_OPTIMIZE_FORALL;
extern Keyword* KWD_OPTIMIZE_EXISTS;
extern Keyword* KWD_OPTIMIZE_STATIC_WITH_CLUSTERING;
extern Keyword* KWD_OPTIMIZE_DESCRIPTION;
extern Keyword* KWD_OPTIMIZE_AND;
extern Keyword* KWD_OPTIMIZE_BOUND;
extern Symbol* SYM_OPTIMIZE_LOGIC_RESIDUE_GOALS;
extern Keyword* KWD_OPTIMIZE_PATTERN;
extern Keyword* KWD_OPTIMIZE_DYNAMIC;
extern Keyword* KWD_OPTIMIZE_DYNAMIC_WITH_CLUSTERING;
extern Symbol* SYM_OPTIMIZE_LOGIC_DONT_OPTIMIZEp;
extern Keyword* KWD_OPTIMIZE_NONE;
extern Surrogate* SGT_OPTIMIZE_PL_KERNEL_KB_CUT;
extern Surrogate* SGT_OPTIMIZE_PL_KERNEL_KB_BOUND_VARIABLES;
extern Keyword* KWD_OPTIMIZE_BACKWARD;
extern Surrogate* SGT_OPTIMIZE_LOGIC_F_DYNAMICALLY_ESTIMATE_INFERENCE_COST_MEMO_TABLE_000;
extern Surrogate* SGT_OPTIMIZE_PL_KERNEL_KB_INSTANCE_OF;
extern Surrogate* SGT_OPTIMIZE_PL_KERNEL_KB_TOTAL;
extern Keyword* KWD_OPTIMIZE_RELATION;
extern Surrogate* SGT_OPTIMIZE_STELLA_THING;
extern Keyword* KWD_OPTIMIZE_REALISTIC;
extern Keyword* KWD_OPTIMIZE_FLAT;
extern Surrogate* SGT_OPTIMIZE_STELLA_CS_VALUE;
extern Keyword* KWD_OPTIMIZE_CONSTANT;
extern Symbol* SYM_OPTIMIZE_STELLA_PREDICATE;
extern Symbol* SYM_OPTIMIZE_LOGIC_WEIGHT;
extern Symbol* SYM_OPTIMIZE_LOGIC_VARIABLE_TYPEp;
extern Symbol* SYM_OPTIMIZE_LOGIC_DESCRIPTIVEp;
extern Symbol* SYM_OPTIMIZE_LOGIC_ANNOTATIONS;
extern Surrogate* SGT_OPTIMIZE_LOGIC_LOGIC_OBJECT;
extern Surrogate* SGT_OPTIMIZE_PL_KERNEL_KB_EQUIVALENT;
extern Symbol* SYM_OPTIMIZE_LOGIC_EQUIVALENT;
extern Symbol* SYM_OPTIMIZE_LOGIC_CONSTANT;
extern Keyword* KWD_OPTIMIZE_CREATED_SKOLEMS;
extern Surrogate* SGT_OPTIMIZE_LOGIC_SKOLEM;
extern Surrogate* SGT_OPTIMIZE_LOGIC_F_FILTER_IMPLIED_SKOLEM_PROPOSITIONS_MEMO_TABLE_000;
extern Symbol* SYM_OPTIMIZE_LOGIC_INITIAL_BINDINGS;
extern Symbol* SYM_OPTIMIZE_LOGIC_STRUCTURAL_FUNCTION_EVALUATION_ORDER;
extern Surrogate* SGT_OPTIMIZE_STELLA_VECTOR;
extern Keyword* KWD_OPTIMIZE_CONCEIVE;
extern Symbol* SYM_OPTIMIZE_LOGIC_STARTUP_OPTIMIZE;
extern Symbol* SYM_OPTIMIZE_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
