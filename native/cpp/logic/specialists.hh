//  -*- Mode: C++ -*-

// specialists.hh

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
class ComputedProcedure : public Thing {
// Each instance denotes a programming language 
// function that computes some procedure.  The slot 'procedure-name'
// provides the name of the procedure.  The slot 'procedure-function'
// points to the STELLA function object carrying out the computation.
// If neither is supplied, the procedure will be looked up by extracting
// its name from the name of the instance.  Pointing to a function object
// instead of just the code gives us access to argument type information.
// Note that we support external non-STELLA functions by creating a dummy
// STELLA function object during registration of the computation (see
// `register-computation-function' and friends).
public:
  Symbol* procedureName;
  MethodSlot* procedureFunction;
public:
  virtual Surrogate* primaryType();
};

class SubstringPositionIterator : public Iterator {
public:
  const char* superString;
  const char* subString;
  int start;
  int subLength;
public:
  virtual Surrogate* primaryType();
  virtual int length();
  virtual boolean nextP();
};

class ForkProofAdjunct : public ProofAdjunct {
public:
  Justification* conditionJustification;
  ControlFrame* downFrame;
public:
  virtual Surrogate* primaryType();
};

class SavedInferenceLevelProofAdjunct : public ProofAdjunct {
public:
  InferenceLevel* savedInferenceLevel;
  InferenceLevel* inferenceLevel;
  ControlFrame* downFrame;
public:
  virtual Surrogate* primaryType();
};

class SavedContextProofAdjunct : public ProofAdjunct {
public:
  Context* savedContext;
  ControlFrame* downFrame;
public:
  virtual Surrogate* primaryType();
};


// Global declarations:
extern int oPROTOTYPE_ID_COUNTERo;
extern boolean oACCELERATE_FRAME_COMPUTATIONSpo;

// Function signatures:
ComputedProcedure* newComputedProcedure();
Object* accessComputedProcedureSlotValue(ComputedProcedure* self, Symbol* slotname, Object* value, boolean setvalueP);
MethodSlot* stellaFunctionFromProcedure(ComputedProcedure* procedure);
cpp_function_code functionCodeFromProcedure(ComputedProcedure* procedure);
cpp_function_code lookupSpecialist(NamedDescription* description);
MethodSlot* lookupConstraintFunction(NamedDescription* description);
cpp_function_code lookupConstraint(NamedDescription* description);
MethodSlot* lookupComputationFunction(NamedDescription* description);
cpp_function_code lookupComputation(NamedDescription* description);
MethodSlot* lookupEvaluatorFunction(NamedDescription* description);
cpp_function_code lookupEvaluator(NamedDescription* description);
boolean successResultP(Keyword* result);
boolean failureResultP(Keyword* result);
boolean continuingResultP(Keyword* result);
boolean finalResultP(Keyword* result);
Keyword* selectTestResult(boolean successP, boolean terminalP, ControlFrame* frame);
Keyword* selectProofResult(boolean successP, boolean continuingP, boolean terminalP);
boolean nullWrapperP(Object* self);
Keyword* nativeSlotReaderSpecialist(ControlFrame* frame, Keyword* lastmove);
SubstringPositionIterator* newSubstringPositionIterator(const char* superString, const char* subString);
Object* accessSubstringPositionIteratorSlotValue(SubstringPositionIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
boolean boundComputationInputSkolemP(Skolem* skolem);
Surrogate* argumentTargetType(List* parametertypes, int ninputtypes, int argindex);
Object* computeRelationValue(Proposition* proposition, MethodSlot* computation, boolean errorP);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* computationSpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

Object* computeSimpleRelationConstraint(Proposition* proposition, MethodSlot* computation, boolean errorP, int& _Return1);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* constraintSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* squareRootSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* absoluteValueSpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

List* enumerationsContainingMember(Object* self);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* memberOfSpecialist(ControlFrame* frame, Keyword* lastmove);
void memberOfEvaluator(Proposition* self);
Keyword* instanceOfSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* buggyDirectInstanceOfSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* directInstanceOfSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* assertedInstanceOfSpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

boolean testDisjointTermsP(Object* term1, Object* term2);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* subsetOfSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* holdsSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* totalValueSpecialist(ControlFrame* frame, Keyword* lastmove);
Object* thatComputation(Object* p);
Object* propositionRelationComputation(Object* p);
Object* propositionArgumentComputation(Object* p, IntegerWrapper* i);
Skolem* propositionArgumentsComputation(Object* p);
IntegerWrapper* propositionArityComputation(Object* p);
Keyword* conceivedPropositionTermSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* cutSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* boundVariablesSpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

ForkProofAdjunct* newForkProofAdjunct();
Object* accessForkProofAdjunctSlotValue(ForkProofAdjunct* self, Symbol* slotname, Object* value, boolean setvalueP);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* forkSpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

Proposition* computeSubqueryOptions(ControlFrame* frame, PropertyList*& _Return1);
QueryIterator* createQuerySpecialistIterator(ControlFrame* frame, boolean& _Return1, boolean& _Return2);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* querySpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

SavedInferenceLevelProofAdjunct* newSavedInferenceLevelProofAdjunct();
Object* accessSavedInferenceLevelProofAdjunctSlotValue(SavedInferenceLevelProofAdjunct* self, Symbol* slotname, Object* value, boolean setvalueP);
InferenceLevel* leveledQueryRelationToInferenceLevel(Surrogate* relation);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* leveledQuerySpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* conceptPrototypeSpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

NamedDescription* conceptPrototypeOf(LogicObject* self);
boolean conceptPrototypeP(LogicObject* self);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* closedSpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

boolean closedByAssertionP(Object* self);
boolean closedTermP(Object* self);
boolean helpClosedTermP(Object* self, Cons* activeterms);
boolean closedPropositionP(Proposition* self);
boolean helpClosedPropositionP(Proposition* self, Cons* activeterms);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* singleValuedSpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

boolean singleValuedTermP(Object* self);
boolean nonRecursiveSingleValuedTermP(Object* self);
boolean singleValuedGoalP(Proposition* proposition, Cons* iovariables, Cons* boundvariables);
boolean helpSingleValuedGoalP(Proposition* proposition, Cons* iovariables, Cons* boundvariables, boolean recursiveP);
void helpCollectSinglyBoundVariables(Proposition* proposition, List* boundvariables, boolean recursiveP);
void createCollectDescriptionExtensionFrame(ControlFrame* frame, Description* description);
boolean collectDescriptionExtensionFrameP(ControlFrame* frame);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* collectMembersSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* nthElementSpecialist(ControlFrame* frame, Keyword* lastmove);
Skolem* nthHeadComputation(Skolem* list, IntegerWrapper* narg);
Skolem* nthRestComputation(Skolem* list, IntegerWrapper* narg);
Skolem* insertElementComputation(Skolem* list, IntegerWrapper* narg, Object* element);
Keyword* minimumOfNumbersSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* maximumOfNumbersSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* sumOfNumbersSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* meanOfNumbersSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* medianOfNumbersSpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

Keyword* computeVarianceOrStandardDeviation(ControlFrame* frame, Keyword* lastmove, boolean standardDeviationP);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* standardDeviationSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* varianceSpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

void helpDerivePartitionMemberships(LogicObject* self, LogicObject* super, List* tuples);
boolean derivePartitionMembershipsP(LogicObject* self);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* hasPartitionMembershipSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* refutationDisjointSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* emptySpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

boolean emptyTermP(Object* self);
boolean cheapEmptyTermP(LogicObject* self);
boolean expensiveEmptyTermP(LogicObject* self);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Context* objectContextComputation(Object* instance);
Context* objectNameContextComputation(Object* instance);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

SavedContextProofAdjunct* newSavedContextProofAdjunct();
Object* accessSavedContextProofAdjunctSlotValue(SavedContextProofAdjunct* self, Symbol* slotname, Object* value, boolean setvalueP);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* istSpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

Skolem* getRolesetOf(NamedDescription* relation, Object* instance);
int computeStoredBoundOnRoleset(NamedDescription* relation, Object* instance, Keyword* lowerorupper);
int computeMinimumCardinality(NamedDescription* relation, Object* instance);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* rangeMinCardinalitySpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

int computeMaximumCardinality(NamedDescription* relation, Object* instance);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* rangeMaxCardinalitySpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

boolean testRangeTypeP(NamedDescription* relation, Object* instance, NamedDescription* valuetype);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* rangeTypeSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* reflexiveRelationSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* irreflexiveRelationSpecialist(ControlFrame* frame, Keyword* lastmove);
StringWrapper* objectNameComputation(Object* objectarg);
StringWrapper* objectPrintNameComputation(Object* objectarg);
Object* nameToObjectComputation(Object* namearg);
Object* printNameToObjectComputation(Object* namearg);
IntegerWrapper* arityComputation(Object* descriptionarg);
Keyword* aritySpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* relationHierarchySpecialist(ControlFrame* frame, Keyword* lastmove);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

List* helpProjectNthColumn(int n, List* tuplelist);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* projectColumnSpecialist(ControlFrame* frame, Keyword* lastmove);
void assertSynonymDemon(Proposition* self);
void retractSynonymDemon(Proposition* self);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

Cons* getSynonyms(Object* term);
boolean synonymSurrogateP(Surrogate* name);
void transferSynonyms(Object* oldobject, Object* newobject);

} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* differentSpecialist(ControlFrame* frame, Keyword* lastmove);
Object* equivalentTermsComputation(Object* term);

} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

cpp_function_code lookupNativeSpecialist(const char* nativeName);
void registerSpecialistFunction(const char* name, cpp_function_code code);
void registerSpecialistFunctionName(const char* stellaName, const char* nativeName);
void registerSpecialistFunctionNameEvaluatorWrapper(Cons* arguments);
cpp_function_code lookupNativeComputation(const char* nativeName, int arity);
void registerComputationFunction(const char* name, cpp_function_code code, int arity);
void registerComputationFunctionName(const char* stellaName, const char* nativeName, int arity);
void registerComputationFunctionNameEvaluatorWrapper(Cons* arguments);
void helpStartupSpecialists1();
void helpStartupSpecialists2();
void helpStartupSpecialists3();
void helpStartupSpecialists4();
void helpStartupSpecialists5();
void startupSpecialists();

// Auxiliary global declarations:
extern Surrogate* SGT_SPECIALISTS_LOGIC_COMPUTED_PROCEDURE;
extern Symbol* SYM_SPECIALISTS_LOGIC_PROCEDURE_NAME;
extern Symbol* SYM_SPECIALISTS_LOGIC_PROCEDURE_FUNCTION;
extern Keyword* KWD_SPECIALISTS_ERROR;
extern Keyword* KWD_SPECIALISTS_RELEASE;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_SPECIALIST;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_HANDLES_REVERSE_POLARITY;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_CONSTRAINT;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_COMPUTATION;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_EVALUATOR;
extern Keyword* KWD_SPECIALISTS_CONTINUING_SUCCESS;
extern Keyword* KWD_SPECIALISTS_FINAL_SUCCESS;
extern Keyword* KWD_SPECIALISTS_FAILURE;
extern Keyword* KWD_SPECIALISTS_TERMINAL_FAILURE;
extern Keyword* KWD_SPECIALISTS_FAIL;
extern Keyword* KWD_SPECIALISTS_TRUE;
extern Surrogate* SGT_SPECIALISTS_STELLA_THING;
extern Surrogate* SGT_SPECIALISTS_STELLA_FUNCTION_CODE_WRAPPER;
extern Surrogate* SGT_SPECIALISTS_STELLA_METHOD_CODE_WRAPPER;
extern Surrogate* SGT_SPECIALISTS_LOGIC_SUBSTRING_POSITION_ITERATOR;
extern Symbol* SYM_SPECIALISTS_LOGIC_SUPER_STRING;
extern Symbol* SYM_SPECIALISTS_LOGIC_SUB_STRING;
extern Symbol* SYM_SPECIALISTS_STELLA_START;
extern Symbol* SYM_SPECIALISTS_LOGIC_SUB_LENGTH;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_TOTAL;
extern Surrogate* SGT_SPECIALISTS_STELLA_CONS;
extern Surrogate* SGT_SPECIALISTS_STELLA_OBJECT;
extern Symbol* SYM_SPECIALISTS_STELLA_ITERATOR;
extern Surrogate* SGT_SPECIALISTS_STELLA_NUMBER_WRAPPER;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_COLLECTIONOF;
extern Keyword* KWD_SPECIALISTS_UP_TRUE;
extern Keyword* KWD_SPECIALISTS_UP_FAIL;
extern Surrogate* SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION;
extern Symbol* SYM_SPECIALISTS_STELLA_ISA;
extern Keyword* KWD_SPECIALISTS_MOVE_DOWN;
extern Surrogate* SGT_SPECIALISTS_LOGIC_DESCRIPTION;
extern Symbol* SYM_SPECIALISTS_LOGIC_EXTERNAL_VARIABLES;
extern Surrogate* SGT_SPECIALISTS_STELLA_COLLECTION;
extern Surrogate* SGT_SPECIALISTS_LOGIC_LOGIC_OBJECT;
extern Keyword* KWD_SPECIALISTS_SCAN_COLLECTION;
extern Surrogate* SGT_SPECIALISTS_LOGIC_PROPOSITION;
extern Keyword* KWD_SPECIALISTS_DOWN;
extern Symbol* SYM_SPECIALISTS_STELLA_PREDICATE;
extern Symbol* SYM_SPECIALISTS_STELLA_FUNCTION;
extern Symbol* SYM_SPECIALISTS_STELLA_DUMMY;
extern Keyword* KWD_SPECIALISTS_FULL_SUBQUERY;
extern Symbol* SYM_SPECIALISTS_LOGIC_DESCRIPTION;
extern Keyword* KWD_SPECIALISTS_FUNCTION;
extern Keyword* KWD_SPECIALISTS_PREDICATE;
extern Keyword* KWD_SPECIALISTS_ISA;
extern Surrogate* SGT_SPECIALISTS_LOGIC_SKOLEM;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_HOLDS;
extern Keyword* KWD_SPECIALISTS_AND;
extern Symbol* SYM_SPECIALISTS_STELLA_ARGUMENTS;
extern Surrogate* SGT_SPECIALISTS_LOGIC_FORK_PROOF_ADJUNCT;
extern Symbol* SYM_SPECIALISTS_LOGIC_CONDITION_JUSTIFICATION;
extern Symbol* SYM_SPECIALISTS_LOGIC_DOWN_FRAME;
extern Symbol* SYM_SPECIALISTS_LOGIC_PROOF_ADJUNCT;
extern Keyword* KWD_SPECIALISTS_FAIL_INTRODUCTION;
extern Keyword* KWD_SPECIALISTS_FORK_ELSE;
extern Keyword* KWD_SPECIALISTS_FORK_THEN;
extern Symbol* SYM_SPECIALISTS_LOGIC_JUSTIFICATION;
extern Keyword* KWD_SPECIALISTS_TECHNICAL;
extern Keyword* KWD_SPECIALISTS_LAY;
extern Keyword* KWD_SPECIALISTS_HOW_MANY;
extern Keyword* KWD_SPECIALISTS_INHERIT;
extern Keyword* KWD_SPECIALISTS_ALL;
extern Keyword* KWD_SPECIALISTS_CURRENT;
extern Symbol* SYM_SPECIALISTS_LOGIC_QUERY_SPECIALIST_IO_VARIABLES;
extern Keyword* KWD_SPECIALISTS_MATCH_MODE;
extern Keyword* KWD_SPECIALISTS_DESCRIPTION;
extern Keyword* KWD_SPECIALISTS_SORT_BY;
extern Keyword* KWD_SPECIALISTS_GOAL_TREE;
extern Surrogate* SGT_SPECIALISTS_LOGIC_SAVED_INFERENCE_LEVEL_PROOF_ADJUNCT;
extern Symbol* SYM_SPECIALISTS_LOGIC_SAVED_INFERENCE_LEVEL;
extern Symbol* SYM_SPECIALISTS_LOGIC_INFERENCE_LEVEL;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_ASSERTION_QUERY;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_SHALLOW_QUERY;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_SUBSUMPTION_QUERY;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_BACKTRACKING_QUERY;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_NORMAL_QUERY;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_REFUTATION_QUERY;
extern Keyword* KWD_SPECIALISTS_LEVELED_QUERY;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_CONCEPT_PROTOTYPE;
extern Symbol* SYM_SPECIALISTS_LOGIC_HYPOTHESIZED_INSTANCEp;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_CLOSED;
extern Surrogate* SGT_SPECIALISTS_LOGIC_F_CLOSED_TERMp_MEMO_TABLE_000;
extern Symbol* SYM_SPECIALISTS_LOGIC_EQUIVALENT_VALUE;
extern Surrogate* SGT_SPECIALISTS_LOGIC_PATTERN_VARIABLE;
extern Surrogate* SGT_SPECIALISTS_LOGIC_F_CLOSED_PROPOSITIONp_MEMO_TABLE_000;
extern Keyword* KWD_SPECIALISTS_OR;
extern Keyword* KWD_SPECIALISTS_NOT;
extern Keyword* KWD_SPECIALISTS_FORALL;
extern Keyword* KWD_SPECIALISTS_EXISTS;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_MEMBER_OF;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_SINGLE_VALUED;
extern Surrogate* SGT_SPECIALISTS_LOGIC_F_SINGLE_VALUED_TERMp_MEMO_TABLE_000;
extern Keyword* KWD_SPECIALISTS_EQUIVALENT;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_COLLECT_INTO_LIST;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_COLLECT_INTO_ORDERED_SET;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_COUNT_MEMBERS;
extern Symbol* SYM_SPECIALISTS_LOGIC_INFERENCE_CUTOFF_REASON;
extern Keyword* KWD_SPECIALISTS_COLLECT_MEMBERS;
extern Symbol* SYM_SPECIALISTS_LOGIC_pSUPER;
extern Symbol* SYM_SPECIALISTS_LOGIC_pMDC;
extern Symbol* SYM_SPECIALISTS_STELLA_AND;
extern Symbol* SYM_SPECIALISTS_LOGIC_MEMBER_OF;
extern Symbol* SYM_SPECIALISTS_LOGIC_MUTUALLY_DISJOINT_COLLECTION;
extern Symbol* SYM_SPECIALISTS_LOGIC_F_HELP_DERIVE_PARTITION_MEMBERSHIPS_QUERY_000;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_PARTITION_MEMBERSHIP;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_DISJOINT;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_HAS_PARTITION_MEMBERSHIP;
extern Keyword* KWD_SPECIALISTS_ASSERT_TRUE;
extern Keyword* KWD_SPECIALISTS_ASSERT_FALSE;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_EMPTY;
extern Surrogate* SGT_SPECIALISTS_LOGIC_SAVED_CONTEXT_PROOF_ADJUNCT;
extern Symbol* SYM_SPECIALISTS_LOGIC_SAVED_CONTEXT;
extern Surrogate* SGT_SPECIALISTS_STELLA_CONTEXT;
extern Keyword* KWD_SPECIALISTS_JUST_IN_TIME;
extern Keyword* KWD_SPECIALISTS_IST_INTRODUCTION;
extern Keyword* KWD_SPECIALISTS_PARTIAL;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_THE_ROLESET;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_CARDINALITY;
extern Keyword* KWD_SPECIALISTS_LOWER;
extern Keyword* KWD_SPECIALISTS_UPPER;
extern Surrogate* SGT_SPECIALISTS_STELLA_INTEGER_WRAPPER;
extern Surrogate* SGT_SPECIALISTS_STELLA_SURROGATE;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_DIRECT_SUBRELATION;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_DIRECT_SUPERRELATION;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_SUBRELATION;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_SUPERRELATION;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_PROPER_SUBRELATION;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_PROPER_SUPERRELATION;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_EQUIVALENT_RELATION;
extern Surrogate* SGT_SPECIALISTS_STELLA_LIST;
extern Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_SYNONYM;
extern Surrogate* SGT_SPECIALISTS_STELLA_CS_VALUE;
extern Symbol* SYM_SPECIALISTS_LOGIC_STARTUP_SPECIALISTS;
extern Symbol* SYM_SPECIALISTS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
