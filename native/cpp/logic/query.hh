//  -*- Mode: C++ -*-

// query.hh

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
class InferenceLevel : public StandardObject {
// This class hierarchy is used to choose the
// level of inference applied when dispatching queries (canned
// or ad hoc).
public:
  Keyword* keyword;
public:
  virtual Surrogate* primaryType();
};

class NormalInferenceLevel : public InferenceLevel {
// The normal inference level employs all proof strategies
// except disjunctive implication introduction and refutation.
public:
  virtual Surrogate* primaryType();
  virtual Cons* levellizedAllSlotValueTypes(LogicObject* self, Surrogate* relation);
  virtual int levellizedGetSlotMaximumCardinality(LogicObject* self, Surrogate* relation);
  virtual int levellizedGetSlotMinimumCardinality(LogicObject* self, Surrogate* relation);
  virtual boolean levellizedTestRelationOnArgumentsP(Surrogate* relation, Cons* arguments);
  virtual Cons* levellizedAllRelationValues(Surrogate* relation, Cons* nminusonearguments);
  virtual Cons* levellizedAllClassInstances(Surrogate* type);
  virtual boolean levellizedTestTypeOnInstanceP(Object* self, Surrogate* type);
};

class BacktrackingInferenceLevel : public NormalInferenceLevel {
// Specifies subsumption level inference plus backtracking.
public:
  virtual Surrogate* primaryType();
};

class SubsumptionInferenceLevel : public BacktrackingInferenceLevel {
// Specifies lookup augmented with cached
// subsumption links and equality reasoning.
public:
  virtual Surrogate* primaryType();
  virtual Cons* levellizedAllSlotValueTypes(LogicObject* self, Surrogate* relation);
  virtual int levellizedGetSlotMaximumCardinality(LogicObject* self, Surrogate* relation);
  virtual int levellizedGetSlotMinimumCardinality(LogicObject* self, Surrogate* relation);
  virtual boolean levellizedTestRelationOnArgumentsP(Surrogate* relation, Cons* arguments);
  virtual Cons* levellizedAllRelationValues(Surrogate* relation, Cons* nminusonearguments);
  virtual Cons* levellizedAllClassInstances(Surrogate* type);
  virtual boolean levellizedTestTypeOnInstanceP(Object* self, Surrogate* type);
};

class ShallowInferenceLevel : public SubsumptionInferenceLevel {
// Specifies lookup of assertions plus simple frame computations.
public:
  virtual Surrogate* primaryType();
  virtual Cons* levellizedAllSlotValueTypes(LogicObject* self, Surrogate* relation);
  virtual int levellizedGetSlotMaximumCardinality(LogicObject* self, Surrogate* relation);
  virtual int levellizedGetSlotMinimumCardinality(LogicObject* self, Surrogate* relation);
  virtual boolean levellizedTestTypeOnInstanceP(Object* self, Surrogate* type);
};

class AssertionInferenceLevel : public SubsumptionInferenceLevel {
// Specifies lookup of assertions only.
public:
  virtual Surrogate* primaryType();
  virtual Cons* levellizedAllClassInstances(Surrogate* type);
};

class RefutationInferenceLevel : public NormalInferenceLevel {
// Normal inference augmented by refutation proof strategy.
public:
  virtual Surrogate* primaryType();
};

class QueryIterator : public Iterator {
// A query iterator points to a query environment
// representing the initial or intermediate state of a query.  The iterator's
// 'value' is a vector representing a satisfying set bindings of the query's
// output variables.  Each call to the iterator writes a new set of bindings
// into the vector.
public:
  Vector* externalVariables;
  boolean exhaustedP;
  PropertyList* options;
  // Each element holds a solution record with a
  // vector of bindings of the free external variables of the query plus all
  // the appropriate truth-value and justification support.
  QuerySolutionTable* solutions;
  Context* queryContext;
  ControlFrame* baseControlFrame;
  ControlFrame* currentControlFrame;
  PatternRecord* currentPatternRecord;
  ParallelThread* currentParallelThread;
  ControlFramePriorityQueue* controlFramePriorityQueue;
  boolean augmentedGoalCacheP;
  List* activeGoalCaches;
  boolean triggeredDepthCutoffP;
  boolean failedToFindDuplicateSubgoalP;
  boolean foundAtLeastOneSolutionP;
  int timestamp;
  PartialMatchFrame* partialMatchStrategy;
  InferenceLevel* inferenceLevel;
  int currentDepthCutoff;
  int maximumDepth;
  // If defined, timeout after that many seconds.
  double allottedTime;
  // If defined, timeout after that many :DOWN moves.
  int allottedClockTicks;
  int currentClockTicks;
  // Set to TRUE if query times out.
  boolean timeoutP;
  // Set to TRUE if one or more depth cutoffs occurred.
  boolean depthCutoffsP;
  KeyValueList* dynamicSlots;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
  virtual List* listify();
  virtual Cons* consify();
  virtual Cons* consifyCurrentSolutions();
  virtual void reset();
  virtual boolean nextP();
  virtual boolean querySucceededP();
  virtual boolean queryIsPartialP();
  virtual boolean queryIsTrueFalseP();
  virtual Description* queryDescription();
  virtual Proposition* queryProposition();
  virtual void free();
  virtual void debugIdSetter(const char* id);
  virtual boolean deletedPSetter(boolean value);
  virtual boolean deletedP();
  virtual BooleanWrapper* badP_reader();
  virtual List* bestGoalSequence_reader();
  virtual List* residueGoals_reader();
};

class ControlFrame : public StandardObject {
public:
  Keyword* state;
  Proposition* proposition;
  TruthValue* truthValue;
  boolean reversePolarityP;
  // Clock ticks at last :DOWN move.
  int startingClockTicks;
  // Total clock ticks allotted to prove this goal.
  int allottedClockTicks;
  ControlFrame* up;
  ControlFrame* down;
  ControlFrame* result;
  int argumentCursor;
  PatternRecord* patternRecord;
  PatternRecord* inheritedPatternRecord;
  int choicePointUnbindingOffset;
  Keyword* currentStrategy;
  Cons* nextStrategies;
  PartialMatchFrame* partialMatchFrame;
  List* justifications;
  Cons* goalBindings;
  boolean cachedGoalResultP;
  boolean dontCacheGoalFailureP;
  KeyValueList* dynamicSlots;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
  virtual Keyword* continuePartialFailProof(Keyword* lastmove);
  virtual void setJustificationPartialTruth(Justification* justification);
  virtual void setCachePartialTruth(AtomicGoalCache* cache);
  virtual boolean definedFramePartialTruthP();
  virtual Keyword* continuePartialStrategiesProofs(Keyword* lastmove);
  virtual Keyword* continuePartialNotProof(Keyword* lastmove);
  virtual Keyword* continuePartialOrProof(Keyword* lastmove);
  virtual Keyword* continuePartialAndProof(ControlFrame* frame, Keyword* lastmove);
  virtual boolean holdsByDefaultP();
  virtual List* querySpecialistIoVariables_reader();
  virtual List* allJustifications_reader();
  virtual boolean deletedPSetter(boolean value);
  virtual boolean deletedP();
  virtual BooleanWrapper* badP_reader();
};

class ParallelThread : public StandardObject {
public:
  ControlFrame* topControlFrame;
  World* hypotheticalWorld;
  Vector* variableBindings;
  IntegerVector* unbindingStack;
  int topUnbindingStackOffset;
  int priority;
  Keyword* status;
public:
  virtual Surrogate* primaryType();
};

class ParallelControlFrame : public ControlFrame {
public:
  List* childThreads;
  boolean unboundVariablesP;
  ParallelThread* currentChildThread;
  Context* savedParentContext;
  ParallelThread* savedParentParallelThread;
public:
  virtual Surrogate* primaryType();
};

class ControlFramePriorityQueue : public StandardObject {
public:
  List* queue;
public:
  virtual Surrogate* primaryType();
};

class ProofAdjunct : public StandardObject {
// Subclasses of 'PROOF-ADJUNCT' provide for specialized
// slots (specialized for a particular strategy) to hold a record of
// an ongoing proof thread.
public:
  virtual Surrogate* primaryType();
};

class PatternRecord : public StandardObject {
// A pattern record records bookkeeping data used during
// the processing of a description.
public:
  ControlFrame* controlFrame;
  Vector* variableBindings;
  IntegerVector* unbindingStack;
  int topUnbindingStackOffset;
  Description* description;
  Vector* externalArguments;
  BooleanVector* booleanVector;
  Description* optimalPattern;
  List* collectionList;
public:
  virtual void free();
  virtual Surrogate* primaryType();
};

class BooleanVectorIndexNode : public StandardObject {
public:
  BooleanVectorIndexNode* trueLink;
  BooleanVectorIndexNode* falseLink;
  BooleanVector* theVector;
public:
  virtual Surrogate* primaryType();
};

class AssertedCollectionMembersIterator : public Iterator {
// Iterator reimplementation of `asserted-collection-members'.
// Generates asserted members of a collection as well as the supporting propositions
// with their truth values and justifications (if applicable).
public:
  Object* collection;
  boolean specializeP;
  Keyword* kind;
  Iterator* baseIterator;
  Iterator* nestedBaseIterator;
  Proposition* proposition;
  int observedCardinality;
public:
  virtual Surrogate* primaryType();
  virtual boolean nextP();
};

class AssertedMemberOfCollectionSupportsIterator : public AssertedCollectionMembersIterator {
// Iterator reimplementation of `member-of-collection?'.
// Generates proposition supports that prove that the bound self.member is or is not
// an asserted member of the specified collection (handles reverse polarity).
public:
  Object* member;
public:
  virtual Surrogate* primaryType();
  virtual boolean nextP();
};

class DescriptionExtensionIterator : public Iterator {
// Iterates over the extension of a description and
// its subdescriptions, returning those propositions that are currently true.
public:
  NamedDescription* rootDescription;
  Cons* subcollections;
  Iterator* extensionIterator;
  Proposition* referenceProposition;
  List* alreadyGeneratedList;
  HashTable* alreadyGeneratedTable;
  boolean removingDuplicatesP;
  TruthValue* truthValue;
public:
  virtual Surrogate* primaryType();
  virtual boolean nextP();
};

class QuerySolutionTable : public Dictionary {
// Special key/value map for query solutions indexed by output
// variable binding vectors that also preserves the order of solution generation.
public:
  KeyValueMap* theMap;
  QueryIterator* query;
  QuerySolution* first;
  QuerySolution* last;
public:
  virtual Surrogate* primaryType();
  virtual AbstractIterator* allocateIterator();
  virtual QuerySolutionTable* sort(cpp_function_code predicate);
  virtual Cons* consify();
  virtual void clear();
  virtual QuerySolution* nth(int position);
  virtual boolean nonEmptyP();
  virtual boolean emptyP();
  virtual int length();
  virtual QuerySolution* pop();
  virtual void removeAt(Vector* key);
  virtual void insertAt(Vector* key, QuerySolution* value);
  virtual Object* lookup(Vector* key);
};

class QuerySolution : public StandardObject {
public:
  Vector* bindings;
  TruthValue* truthValue;
  double matchScore;
  Justification* justification;
  // All recorded justifications for
  // this solution in case we have multiple ones from a partial match operation.
  List* allJustifications;
  QuerySolution* next;
public:
  virtual Surrogate* primaryType();
  virtual boolean deletedPSetter(boolean value);
  virtual boolean deletedP();
};

class QuerySolutionTableIterator : public DictionaryIterator {
public:
  QuerySolutionTable* theTable;
  QuerySolution* cursor;
public:
  virtual Surrogate* primaryType();
  virtual boolean nextP();
};


// Global declarations:
extern NormalInferenceLevel* NORMAL_INFERENCE;
extern BacktrackingInferenceLevel* BACKTRACKING_INFERENCE;
extern SubsumptionInferenceLevel* SUBSUMPTION_INFERENCE;
extern ShallowInferenceLevel* SHALLOW_INFERENCE;
extern AssertionInferenceLevel* ASSERTION_INFERENCE;
extern RefutationInferenceLevel* REFUTATION_INFERENCE;
extern DECLARE_STELLA_SPECIAL(oINFERENCELEVELo, NormalInferenceLevel* );
extern DECLARE_STELLA_SPECIAL(oDONTUSEDEFAULTKNOWLEDGEpo, boolean );
extern int oMAXIMUM_BACKTRACKING_DEPTHo;
extern DECLARE_STELLA_SPECIAL(oTYPE_CHECK_STRATEGYo, Keyword* );
extern Keyword* oDUPLICATE_SUBGOAL_STRATEGYo;
extern int oDUPLICATE_GOAL_SEARCH_DEPTHo;
extern int oDUPLICATE_RULE_SEARCH_DEPTHo;
extern boolean oGLOBALLY_CLOSED_COLLECTIONSpo;
extern DECLARE_STELLA_SPECIAL(oGENERATE_ALL_PROOFSpo, boolean );
extern DECLARE_STELLA_SPECIAL(oQUERYITERATORo, QueryIterator* );
extern int oDEFAULT_MAXIMUM_DEPTHo;
extern int oINITIAL_BACKTRACKING_DEPTHo;
extern boolean oITERATIVE_DEEPENING_MODEpo;
extern boolean oEMIT_THINKING_DOTSpo;
extern int oTHINKING_DOT_COUNTERo;
extern PropertyList* oTHINKING_DOT_TABLEo;
extern BooleanVectorIndexNode* oBOOLEAN_VECTOR_INDEXo;
extern DECLARE_STELLA_SPECIAL(oPRINTINFRAMEo, ControlFrame* );
extern HashSet* oTRACED_GOALSo;
extern int oCONTROL_FRAME_ID_COUNTERo;
extern DECLARE_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean );
extern boolean oTRACE_DISJOINTNESS_SUBGOALSpo;
extern int oDUPLICATEINSTANCESCACHECROSSOVERPOINTo;
extern int oQUERY_ITERATOR_DEBUG_ID_COUNTERo;
extern QueryIterator* oMOST_RECENT_QUERYo;
extern KeyValueMap* oINLINE_QUERY_CACHEo;
extern int oMAX_CACHED_QUERIES_PER_IDo;

// Function signatures:
InferenceLevel* newInferenceLevel();
Object* accessInferenceLevelSlotValue(InferenceLevel* self, Symbol* slotname, Object* value, boolean setvalueP);
NormalInferenceLevel* newNormalInferenceLevel();
BacktrackingInferenceLevel* newBacktrackingInferenceLevel();
SubsumptionInferenceLevel* newSubsumptionInferenceLevel();
ShallowInferenceLevel* newShallowInferenceLevel();
AssertionInferenceLevel* newAssertionInferenceLevel();
RefutationInferenceLevel* newRefutationInferenceLevel();
NormalInferenceLevel* currentInferenceLevel();
InferenceLevel* getInferenceLevel(Keyword* levelkeyword);
Keyword* setInferenceLevel(Object* level, Object* module);
Keyword* callSetInferenceLevel(Keyword* levelkeyword, Module* module);
boolean usingDefaultKnowledgeP();
void traceSubgoals();
void untraceSubgoals();
void traceRules();
void untraceRules();
const char* toggleTraceSubgoals();
const char* toggleTraceRules();
QueryIterator* newQueryIterator();
Object* accessQueryIteratorSlotValue(QueryIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
ControlFrame* newControlFrame();
Object* accessControlFrameSlotValue(ControlFrame* self, Symbol* slotname, Object* value, boolean setvalueP);
ParallelThread* newParallelThread();
Object* accessParallelThreadSlotValue(ParallelThread* self, Symbol* slotname, Object* value, boolean setvalueP);
ParallelControlFrame* newParallelControlFrame();
Object* accessParallelControlFrameSlotValue(ParallelControlFrame* self, Symbol* slotname, Object* value, boolean setvalueP);
ControlFramePriorityQueue* newControlFramePriorityQueue();
Object* accessControlFramePriorityQueueSlotValue(ControlFramePriorityQueue* self, Symbol* slotname, Object* value, boolean setvalueP);
void emitThinkingDot(Keyword* kindofthinking);
ProofAdjunct* newProofAdjunct();
PatternRecord* newPatternRecord();
Object* accessPatternRecordSlotValue(PatternRecord* self, Symbol* slotname, Object* value, boolean setvalueP);
BooleanVectorIndexNode* newBooleanVectorIndexNode();
Object* accessBooleanVectorIndexNodeSlotValue(BooleanVectorIndexNode* self, Symbol* slotname, Object* value, boolean setvalueP);
BooleanVectorIndexNode* createBooleanVectorIndexNode(BooleanVectorIndexNode* parentnode, boolean lastvalue);
BooleanVector* argumentsVectorToBooleanVector(Vector* argumentsvector);
BooleanVector* zeroOneListToBooleanVector(List* zeroonelist);
void popControlFrame(ControlFrame* frame);
void popFramesUpTo(ControlFrame* frame);
void popDownFrame(ControlFrame* frame);
void activatePatternRecord(PatternRecord* patternrecord, int variablecount);
void resetCurrentPatternRecord(ControlFrame* frame, Keyword* localorparent);
void printEnvironmentStacks();
void setPatternVariableBinding(PatternVariable* variable, Object* value);
void changePatternVariableBinding(PatternVariable* variable, Object* newvalue);
void unbindVariablesBeginningAt(PatternRecord* patternrecord, int ubstackoffset);
void createChoicePoint(ControlFrame* frame);
void unwindToChoicePoint(ControlFrame* frame);
boolean newBindingsSinceLastChoicePointP(ControlFrame* frame);
Object* boundTo(PatternVariable* self);
Object* safeBoundTo(PatternVariable* self);
Object* boundToInFrame(PatternVariable* self, ControlFrame* frame);
Object* boundToInRecord(PatternVariable* self, PatternRecord* record);
boolean containsOperatorP(Proposition* proposition, Surrogate* operatoR);
Object* argumentBoundTo(Object* self);
Object* safeArgumentBoundTo(Object* self);
boolean helpUnifyAttributesP(Object* value1, Object* value2);
boolean failsUnificationTypeCheckP(PatternVariable* v1, Object* i2);
boolean failsAntecedentTypeCheckP(PatternVariable* v1, Object* i2);
boolean helpBindVariableToValueP(PatternVariable* variable, Object* value);
boolean bindVariableToValueP(PatternVariable* variable, Object* value, boolean autocleanupP);
boolean bindArgumentToValueP(Object* argument, Object* value, boolean autocleanupP);
boolean bindVectorOfArgumentsToValuesP(Vector* arguments, Cons* values);
void printControlFrameStack(ControlFrame* frame);
void pcs();
PatternVariable* variableFromUnbindingOffset(Description* description, int uboffset);
void printOneVariableBinding(PatternVariable* variable);
void printVariableBindings(ControlFrame* frame);
void printRuleInGoalTree(ControlFrame* frame, Proposition* impliesprop, int depth);
void printGoalInGoalTree(ControlFrame* frame, int depth);
int computeFrameDepth(ControlFrame* frame);
void printVerticalBars(int depth);
void unwindToChoicePointsBelowFrame(ControlFrame* frame);
void traceGoal(Object* name);
void untraceGoal(Object* name);
void clearTracedGoals();
boolean restrictedGoalTracingP();
boolean traceThisGoalP(ControlFrame* frame, Keyword* lastmove);
void traceGoalTree(ControlFrame* frame, int depth, Keyword* lastmove);
void traceGoalStack(ControlFrame* frame);
Keyword* oldInterpretAndScores(ControlFrame* frame, Keyword* lastmove);
Keyword* interpretIterativeForallScores(ControlFrame* frame, Keyword* lastmove);
Keyword* oldInterpretOrScores(ControlFrame* frame, Keyword* lastmove);
Keyword* oldInterpretFailScore(ControlFrame* frame, Keyword* lastmove);
Keyword* oldInterpretGoalScores(ControlFrame* frame, Keyword* lastmove);
void attachSupport(ControlFrame* frame, Keyword* lastmove);
PatternRecord* operativePatternRecord(ControlFrame* frame);
ControlFrame* createDownFrame(ControlFrame* upframe, Proposition* downproposition);
TruthValue* setFrameTruthValue(ControlFrame* frame, TruthValue* truthvalue);
TruthValue* propagateFrameTruthValue(ControlFrame* source, ControlFrame* target);
int debugFrameId(ControlFrame* frame);
void copyFrameState(ControlFrame* fromframe, ControlFrame* toframe);
ParallelControlFrame* parallelizeControlFrame(ControlFrame* frame);
void enterParallelThread(ParallelControlFrame* pframe, ParallelThread* childthread);
void exitParallelThread(ParallelControlFrame* pframe);
World* enterHypotheticalWorld(ParallelControlFrame* pframe);
boolean partialMatchModeP();
boolean executeBackwardChainingProofP(QueryIterator* query);
Keyword* evaluateNextMove(ControlFrame* frame, Keyword* lastmove, int clockticks);
Keyword* continueAndProof(ControlFrame* frame, Keyword* lastmove);
Keyword* continueOrProof(ControlFrame* frame, Keyword* lastmove);
Keyword* continueNotProof(ControlFrame* frame, Keyword* lastmove);
Keyword* overlayWithFailFrame(ControlFrame* frame, Proposition* proposition);
Keyword* overlayWithStrategyFrame(ControlFrame* frame, Keyword* strategy);
boolean checkForDuplicateGoalP(ControlFrame* frame);
Keyword* initiateAtomicGoalProofs(ControlFrame* frame);
boolean allArgumentsBoundP(Proposition* goal);
boolean allKeyArgumentsBoundP(Proposition* goal);
PatternRecord* createPatternRecord(ControlFrame* frame, Description* description, Vector* externalarguments);
boolean terminatePatternRecordP(PatternRecord* self);
Vector* copyPatternArguments(Vector* arguments, Description* description);
Cons* computeExternalBindings(Vector* externalarguments);
Object* instantiateExternalBindings(Object* self);
Description* instantiateExternalVariables(Description* self, KeyValueMap* bindings);
boolean checkForSingleValuedGoalP(Description* pattern, Cons* iobindings);
boolean overlayWithPatternFrameP(ControlFrame* frame, Description* description, Vector* ioarguments);
boolean transferPatternQueryBindingsP(ControlFrame* frame, boolean futurebindingsP);
void collectPatternQueryBindings(ControlFrame* frame);
Proposition* getRuleOfAntecedentFrame(ControlFrame* frame);
Keyword* continuePatternProof(ControlFrame* frame, Keyword* lastmove);
boolean disjointClassesP(NamedDescription* desc1, NamedDescription* desc2);
boolean disjointTermsP(Description* d1, Description* d2);
boolean expensiveDisjointTermsP(Description* d1, Description* d2);
AssertedCollectionMembersIterator* newAssertedCollectionMembersIterator();
Object* accessAssertedCollectionMembersIteratorSlotValue(AssertedCollectionMembersIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
AssertedMemberOfCollectionSupportsIterator* newAssertedMemberOfCollectionSupportsIterator();
Object* accessAssertedMemberOfCollectionSupportsIteratorSlotValue(AssertedMemberOfCollectionSupportsIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
boolean collectionofPropositionP(Proposition* definingproposition);
AssertedMemberOfCollectionSupportsIterator* allAssertedMemberOfCollectionSupports(Object* member, Object* collection);
boolean allAssertedMemberOfCollectionSupportsDnextP(AssertedMemberOfCollectionSupportsIterator* self);
boolean memberOfCollectionP(Object* member, Object* collection);
AssertedCollectionMembersIterator* allAssertedCollectionMembers(Object* self, boolean directP);
boolean allAssertedCollectionMembersDnextP(AssertedCollectionMembersIterator* self);
List* assertedCollectionMembers(Object* self, boolean directP);
DescriptionExtensionIterator* newDescriptionExtensionIterator();
Object* accessDescriptionExtensionIteratorSlotValue(DescriptionExtensionIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
DescriptionExtensionIterator* allTrueExtensionMembers(NamedDescription* self, boolean specializeP);
Iterator* allMatchingExtensionMembers(Proposition* self, boolean specializeP);
ControlFrame* helpFindDuplicatedGoal(ControlFrame* goalframe, ControlFrame*& _Return1, int& _Return2);
ControlFrame* findDuplicatedGoal(ControlFrame* frame, ControlFrame*& _Return1, int& _Return2);
ControlFrame* handleDepthViolation(ControlFrame* frame, int depth, int& _Return1);
ControlFrame* handleTimeout(ControlFrame* frame, int depth, int& _Return1);
QuerySolutionTable* newQuerySolutionTable();
Object* accessQuerySolutionTableSlotValue(QuerySolutionTable* self, Symbol* slotname, Object* value, boolean setvalueP);
QuerySolution* newQuerySolution();
Object* accessQuerySolutionSlotValue(QuerySolution* self, Symbol* slotname, Object* value, boolean setvalueP);
boolean querySolutionLessThanP(QuerySolution* x, QuerySolution* y);
boolean querySolutionGreaterThanP(QuerySolution* x, QuerySolution* y);
QuerySolutionTableIterator* newQuerySolutionTableIterator();
Object* accessQuerySolutionTableIteratorSlotValue(QuerySolutionTableIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
void printControlFrame(ControlFrame* self, std::ostream* stream);
void printGoalStack(ControlFrame* frame, boolean verboseP);
void pgs();
void vpgs();
void printQueryIterator(QueryIterator* self, std::ostream* stream);
void printQueryIteratorOrnately(QueryIterator* self, std::ostream* stream);
void printQueryIteratorSolutionOrnately(QueryIterator* self, QuerySolution* solution, int solutionnumber, std::ostream* stream);
void traceSolution(QueryIterator* self, QuerySolution* solution, int solutionnumber);
void printQueryIteratorReadably(QueryIterator* self, std::ostream* stream);
void printQueryIteratorTabSeparated(QueryIterator* self, std::ostream* stream);
Cons* parseQueryIteratorStringTemplate(QueryIterator* self, const char* templatE);
void printQueryIteratorViaTemplate(QueryIterator* self, std::ostream* stream);
QueryIterator* allocateQueryIterator();
void freeQueryIterator(QueryIterator* self);
Vector* allocateCollectionVariables(ControlFrame* frame, Description* description);
QueryIterator* createQueryIterator(Description* description, Vector* outsidebindings);
QueryIterator* initializeQueryIterator(QueryIterator* queryiterator, Description* description, Vector* outsidebindings);
boolean tryToDefeatLastAnswerP(QueryIterator* self, Justification*& _Return1);
Cons* standardizeQueryTree(Object* iovariables, Object* querybody, Cons* externalvariables);
QueryIterator* makeQuery(Object* iovariables, Object* querytree, Cons* externalbindings, Object* options);
Object* parseQueryAndOptions(Cons* queryAoptions, Object*& _Return1, PropertyList*& _Return2);
void processQueryOptions(QueryIterator* query, Object* options);
Object* lookupQueryOption(Object* queryoroptions, Keyword* key);
Object* lookupQueryOptionWithDefault(Object* queryoroptions, Keyword* key, Object* defaulT);
boolean testQueryOptionP(Object* queryoroptions, Keyword* key);
boolean testQueryOptionValueP(Object* queryoroptions, Keyword* key, Object* value);
Object* lookupDeferredQueryOption(Object* queryoroptions, Keyword* key, Surrogate* coercetotype);
int lookupHowManySolutions(Object* queryoroptions);
BooleanWrapper* runYesOrNoQueryP(QueryIterator* query);
Object* coerceToTree(Object* self);
QueryIterator* createAskQuery(Object* query);
TruthValue* callAsk(Object* query);
TruthValue* ask(Cons* propositionAoptions);
TruthValue* askEvaluatorWrapper(Cons* arguments);
QueryIterator* retrieveBindings(Object* query, int nofbindings);
QueryIterator* createRetrieveQuery(Object* query);
QueryIterator* callRetrieve(Object* query);
QueryIterator* retrieve(Cons* query);
QueryIterator* retrieveEvaluatorWrapper(Cons* arguments);
Cons* consifyQuery(QueryIterator* self);
void clearInlineQueryCaches();
QueryIterator* findCachedQuery(Symbol* queryid);
void freeCachedQuery(QueryIterator* query, Symbol* queryid);
QueryIterator* makeCachedQuery(Cons* variables, Object* query, Cons* inputbindings, Object* options, Symbol* cacheid);
Cons* consifyCachedQuerySolutions(QueryIterator* queryiterator, boolean truthvaluesP, boolean justificationsP, Cons*& _Return1, Cons*& _Return2);
Cons* applyCachedRetrieve(Cons* variables, Cons* querybody, Cons* inputbindings, Object* options, Symbol* cacheid, Cons*& _Return1, Cons*& _Return2);
boolean applyCachedAsk(Cons* inputvariables, Cons* querybody, Cons* inputbindings, Object* options, Symbol* cacheid, TruthValue*& _Return1);
LogicObject* getPrototype(Description* description);
TruthValue* unaryDescriptionSpecializesDescriptionP(Description* sub, Description* super);
TruthValue* descriptionSpecializesDescriptionP(Description* sub, Description* super);
TruthValue* vectorSatisfiesDescriptionP(Vector* vector, Description* description);
TruthValue* instanceSatisfiesDescriptionP(Object* instance, Description* description);
Description* coerceToDescription(Object* self, Object* original);
TruthValue* specializesP(Object* subobject, Object* superobject);
LogicObject* coerceToInstance(Object* self, Object* original);
Object* coerceToInstanceOrLiteral(Object* self, Object* original);
Vector* coerceToVector(Object* self);
TruthValue* satisfiesP(Object* instanceortuple, Object* relationref);
boolean applyKappaP(Description* description, Vector* vector);
Cons* updatePropositionsFromQuery(QueryIterator* query, Description* description, Module* module, Keyword* updatemode, boolean recordjustificationsP);
QueryIterator* getQueryIteratorFromCommand(Cons* query);
Cons* handleUpdatePropositionsResult(Cons* result, Keyword* resultmode, Keyword* updatemode, QueryIterator* query, Module* module);
Cons* assertFromQuery(Cons* query, Cons* options);
Cons* assertFromQueryEvaluatorWrapper(Cons* arguments);
Cons* retractFromQuery(Cons* query, Cons* options);
Cons* retractFromQueryEvaluatorWrapper(Cons* arguments);
const char* displaySettings();
void helpStartupQuery1();
void helpStartupQuery2();
void helpStartupQuery3();
void helpStartupQuery4();
void helpStartupQuery5();
void helpStartupQuery6();
void helpStartupQuery7();
void helpStartupQuery8();
void helpStartupQuery9();
void helpStartupQuery10();
void helpStartupQuery11();
void helpStartupQuery12();
void startupQuery();

// Auxiliary global declarations:
extern Surrogate* SGT_QUERY_LOGIC_INFERENCE_LEVEL;
extern Symbol* SYM_QUERY_STELLA_KEYWORD;
extern Surrogate* SGT_QUERY_LOGIC_NORMAL_INFERENCE_LEVEL;
extern Surrogate* SGT_QUERY_LOGIC_BACKTRACKING_INFERENCE_LEVEL;
extern Surrogate* SGT_QUERY_LOGIC_SUBSUMPTION_INFERENCE_LEVEL;
extern Surrogate* SGT_QUERY_LOGIC_SHALLOW_INFERENCE_LEVEL;
extern Surrogate* SGT_QUERY_LOGIC_ASSERTION_INFERENCE_LEVEL;
extern Surrogate* SGT_QUERY_LOGIC_REFUTATION_INFERENCE_LEVEL;
extern Keyword* KWD_QUERY_NORMAL;
extern Keyword* KWD_QUERY_BACKTRACKING;
extern Keyword* KWD_QUERY_SUBSUMPTION;
extern Keyword* KWD_QUERY_SHALLOW;
extern Keyword* KWD_QUERY_ASSERTION;
extern Keyword* KWD_QUERY_REFUTATION;
extern Symbol* SYM_QUERY_LOGIC_INFERENCE_LEVEL;
extern Keyword* KWD_QUERY_LOOKUP;
extern Keyword* KWD_QUERY_DUPLICATE_GOALS;
extern Keyword* KWD_QUERY_TRACE_SUBGOALS;
extern Keyword* KWD_QUERY_PROPAGATE;
extern Keyword* KWD_QUERY_STRATEGIES;
extern Symbol* SYM_QUERY_LOGIC_COST_ESTIMATE;
extern Surrogate* SGT_QUERY_LOGIC_QUERY_ITERATOR;
extern Symbol* SYM_QUERY_LOGIC_RESIDUE_GOALS;
extern Symbol* SYM_QUERY_LOGIC_BEST_GOAL_SEQUENCE;
extern Symbol* SYM_QUERY_STELLA_BADp;
extern Symbol* SYM_QUERY_LOGIC_EXTERNAL_VARIABLES;
extern Symbol* SYM_QUERY_LOGIC_EXHAUSTEDp;
extern Symbol* SYM_QUERY_STELLA_OPTIONS;
extern Symbol* SYM_QUERY_LOGIC_SOLUTIONS;
extern Symbol* SYM_QUERY_LOGIC_QUERY_CONTEXT;
extern Symbol* SYM_QUERY_LOGIC_BASE_CONTROL_FRAME;
extern Symbol* SYM_QUERY_LOGIC_CURRENT_CONTROL_FRAME;
extern Symbol* SYM_QUERY_LOGIC_CURRENT_PATTERN_RECORD;
extern Symbol* SYM_QUERY_LOGIC_CURRENT_PARALLEL_THREAD;
extern Symbol* SYM_QUERY_LOGIC_CONTROL_FRAME_PRIORITY_QUEUE;
extern Symbol* SYM_QUERY_LOGIC_AUGMENTED_GOAL_CACHEp;
extern Symbol* SYM_QUERY_LOGIC_ACTIVE_GOAL_CACHES;
extern Symbol* SYM_QUERY_LOGIC_TRIGGERED_DEPTH_CUTOFFp;
extern Symbol* SYM_QUERY_LOGIC_FAILED_TO_FIND_DUPLICATE_SUBGOALp;
extern Symbol* SYM_QUERY_LOGIC_FOUND_AT_LEAST_ONE_SOLUTIONp;
extern Symbol* SYM_QUERY_LOGIC_TIMESTAMP;
extern Symbol* SYM_QUERY_LOGIC_PARTIAL_MATCH_STRATEGY;
extern Symbol* SYM_QUERY_LOGIC_CURRENT_DEPTH_CUTOFF;
extern Symbol* SYM_QUERY_LOGIC_MAXIMUM_DEPTH;
extern Symbol* SYM_QUERY_LOGIC_ALLOTTED_TIME;
extern Symbol* SYM_QUERY_LOGIC_ALLOTTED_CLOCK_TICKS;
extern Symbol* SYM_QUERY_LOGIC_CURRENT_CLOCK_TICKS;
extern Symbol* SYM_QUERY_LOGIC_TIMEOUTp;
extern Symbol* SYM_QUERY_LOGIC_DEPTH_CUTOFFSp;
extern Symbol* SYM_QUERY_LOGIC_NEGATED_QUERY;
extern Symbol* SYM_QUERY_LOGIC_LATEST_PARTIAL_SCORE;
extern Symbol* SYM_QUERY_LOGIC_AUXILIARY_QUERY;
extern Symbol* SYM_QUERY_LOGIC_LATEST_POSITIVE_SCORE;
extern Symbol* SYM_QUERY_STELLA_DELETED_OBJECTp;
extern Symbol* SYM_QUERY_LOGIC_GOAL_BINDINGS;
extern Surrogate* SGT_QUERY_LOGIC_CONTROL_FRAME;
extern Symbol* SYM_QUERY_LOGIC_HOLDS_BY_DEFAULTp;
extern Symbol* SYM_QUERY_STELLA_STATE;
extern Symbol* SYM_QUERY_LOGIC_PROPOSITION;
extern Symbol* SYM_QUERY_LOGIC_TRUTH_VALUE;
extern Symbol* SYM_QUERY_LOGIC_REVERSE_POLARITYp;
extern Symbol* SYM_QUERY_LOGIC_STARTING_CLOCK_TICKS;
extern Symbol* SYM_QUERY_LOGIC_UP;
extern Symbol* SYM_QUERY_LOGIC_DOWN;
extern Symbol* SYM_QUERY_STELLA_RESULT;
extern Symbol* SYM_QUERY_LOGIC_ARGUMENT_CURSOR;
extern Symbol* SYM_QUERY_LOGIC_PATTERN_RECORD;
extern Symbol* SYM_QUERY_LOGIC_INHERITED_PATTERN_RECORD;
extern Symbol* SYM_QUERY_LOGIC_CHOICE_POINT_UNBINDING_OFFSET;
extern Symbol* SYM_QUERY_LOGIC_CURRENT_STRATEGY;
extern Symbol* SYM_QUERY_LOGIC_NEXT_STRATEGIES;
extern Symbol* SYM_QUERY_LOGIC_PARTIAL_MATCH_FRAME;
extern Symbol* SYM_QUERY_LOGIC_JUSTIFICATIONS;
extern Symbol* SYM_QUERY_LOGIC_CACHED_GOAL_RESULTp;
extern Symbol* SYM_QUERY_LOGIC_DONT_CACHE_GOAL_FAILUREp;
extern Surrogate* SGT_QUERY_LOGIC_PARALLEL_THREAD;
extern Symbol* SYM_QUERY_LOGIC_TOP_CONTROL_FRAME;
extern Symbol* SYM_QUERY_LOGIC_HYPOTHETICAL_WORLD;
extern Symbol* SYM_QUERY_LOGIC_VARIABLE_BINDINGS;
extern Symbol* SYM_QUERY_LOGIC_UNBINDING_STACK;
extern Symbol* SYM_QUERY_LOGIC_TOP_UNBINDING_STACK_OFFSET;
extern Symbol* SYM_QUERY_LOGIC_PRIORITY;
extern Symbol* SYM_QUERY_LOGIC_STATUS;
extern Surrogate* SGT_QUERY_LOGIC_PARALLEL_CONTROL_FRAME;
extern Symbol* SYM_QUERY_LOGIC_CHILD_THREADS;
extern Symbol* SYM_QUERY_LOGIC_UNBOUND_VARIABLESp;
extern Symbol* SYM_QUERY_LOGIC_CURRENT_CHILD_THREAD;
extern Symbol* SYM_QUERY_LOGIC_SAVED_PARENT_CONTEXT;
extern Symbol* SYM_QUERY_LOGIC_SAVED_PARENT_PARALLEL_THREAD;
extern Surrogate* SGT_QUERY_LOGIC_CONTROL_FRAME_PRIORITY_QUEUE;
extern Symbol* SYM_QUERY_LOGIC_QUEUE;
extern Keyword* KWD_QUERY_UPCLASSIFY;
extern Keyword* KWD_QUERY_DOWNCLASSIFY;
extern Keyword* KWD_QUERY_PARTIAL_MATCH;
extern Surrogate* SGT_QUERY_LOGIC_PROOF_ADJUNCT;
extern Surrogate* SGT_QUERY_LOGIC_PATTERN_RECORD;
extern Symbol* SYM_QUERY_LOGIC_CONTROL_FRAME;
extern Symbol* SYM_QUERY_LOGIC_DESCRIPTION;
extern Symbol* SYM_QUERY_LOGIC_EXTERNAL_ARGUMENTS;
extern Symbol* SYM_QUERY_STELLA_BOOLEAN_VECTOR;
extern Symbol* SYM_QUERY_LOGIC_OPTIMAL_PATTERN;
extern Symbol* SYM_QUERY_LOGIC_COLLECTION_LIST;
extern Surrogate* SGT_QUERY_LOGIC_BOOLEAN_VECTOR_INDEX_NODE;
extern Symbol* SYM_QUERY_LOGIC_TRUE_LINK;
extern Symbol* SYM_QUERY_LOGIC_FALSE_LINK;
extern Symbol* SYM_QUERY_LOGIC_THE_VECTOR;
extern Surrogate* SGT_QUERY_LOGIC_PATTERN_VARIABLE;
extern Keyword* KWD_QUERY_PATTERN;
extern Keyword* KWD_QUERY_CONTAINED_BY;
extern Keyword* KWD_QUERY_PARENT;
extern Symbol* SYM_QUERY_LOGIC_CACHED_BINDINGS_ITERATOR;
extern Keyword* KWD_QUERY_POPPED;
extern Keyword* KWD_QUERY_LOCAL;
extern Keyword* KWD_QUERY_QUERY_STACKS;
extern Surrogate* SGT_QUERY_LOGIC_PROPOSITION;
extern Surrogate* SGT_QUERY_LOGIC_DESCRIPTION;
extern Surrogate* SGT_QUERY_PL_KERNEL_KB_HOLDS;
extern Keyword* KWD_QUERY_NONE;
extern Keyword* KWD_QUERY_SHALLOW_DISJOINT;
extern Keyword* KWD_QUERY_DISJOINT;
extern Keyword* KWD_QUERY_ISA;
extern Surrogate* SGT_QUERY_LOGIC_LOGIC_OBJECT;
extern Keyword* KWD_QUERY_GOAL_TREE;
extern Keyword* KWD_QUERY_WARNING;
extern Symbol* SYM_QUERY_STELLA_NULL;
extern Surrogate* SGT_QUERY_STELLA_LIST;
extern Symbol* SYM_QUERY_STELLA_SURROGATE_VALUE_INVERSE;
extern Symbol* SYM_QUERY_LOGIC_MASTER_PROPOSITION;
extern Keyword* KWD_QUERY_FLAT;
extern Keyword* KWD_QUERY_REALISTIC;
extern Keyword* KWD_QUERY_ATOMIC_GOAL;
extern Keyword* KWD_QUERY_DOWN;
extern Keyword* KWD_QUERY_ITERATIVE_FORALL;
extern Keyword* KWD_QUERY_STATE_MACHINE;
extern Keyword* KWD_QUERY_PARALLEL_STRATEGIES;
extern Keyword* KWD_QUERY_STRATEGY;
extern Keyword* KWD_QUERY_SPECIALIST;
extern Symbol* SYM_QUERY_LOGIC_ANTECEDENTS_RULE;
extern Keyword* KWD_QUERY_UP_TRUE;
extern Keyword* KWD_QUERY_UP_FAIL;
extern Keyword* KWD_QUERY_AND;
extern Keyword* KWD_QUERY_OR;
extern Keyword* KWD_QUERY_NOT;
extern Keyword* KWD_QUERY_FULL_SUBQUERY;
extern Keyword* KWD_QUERY_ANTECEDENTS;
extern Symbol* SYM_QUERY_STELLA_ITERATOR;
extern Keyword* KWD_QUERY_FAILURE;
extern Keyword* KWD_QUERY_FINAL_SUCCESS;
extern Surrogate* SGT_QUERY_LOGIC_NN_PARTIAL_MATCH;
extern Symbol* SYM_QUERY_LOGIC_MATCH_SCORE;
extern Symbol* SYM_QUERY_LOGIC_SUPPORT;
extern Symbol* SYM_QUERY_LOGIC_BACK;
extern Symbol* SYM_QUERY_LOGIC_JUSTIFICATION;
extern Symbol* SYM_QUERY_LOGIC_GOAL_CACHE;
extern Symbol* SYM_QUERY_LOGIC_DEBUG_FRAME_ID_INTERNAL;
extern Keyword* KWD_QUERY_MOVE_DOWN;
extern Keyword* KWD_QUERY_CONTINUING_SUCCESS;
extern Keyword* KWD_QUERY_MOVE_IN_PLACE;
extern Keyword* KWD_QUERY_TIMEOUT;
extern Keyword* KWD_QUERY_FUNCTION;
extern Keyword* KWD_QUERY_PREDICATE;
extern Keyword* KWD_QUERY_EQUIVALENT;
extern Keyword* KWD_QUERY_IMPLIES;
extern Keyword* KWD_QUERY_SCAN_CACHED_BINDINGS;
extern Keyword* KWD_QUERY_FORALL;
extern Keyword* KWD_QUERY_EXISTS;
extern Keyword* KWD_QUERY_CONSTANT;
extern Keyword* KWD_QUERY_FAIL;
extern Keyword* KWD_QUERY_CLUSTERED_CONJUNCTION;
extern Symbol* SYM_QUERY_STELLA_ARGUMENTS;
extern Keyword* KWD_QUERY_DISJUNCTIVE_IMPLICATION_INTRODUCTION;
extern Symbol* SYM_QUERY_LOGIC_FAIL;
extern Keyword* KWD_QUERY_DUPLICATE_GOALS_WITH_CACHING;
extern Keyword* KWD_QUERY_MANUFACTURE_SKOLEM;
extern Symbol* SYM_QUERY_LOGIC_IO_VARIABLES;
extern Surrogate* SGT_QUERY_LOGIC_NAMED_DESCRIPTION;
extern Keyword* KWD_QUERY_DESCRIPTION;
extern Keyword* KWD_QUERY_TOP_LEVEL;
extern Symbol* SYM_QUERY_LOGIC_CACHED_SINGLE_VALUEDp;
extern Keyword* KWD_QUERY_FAILED_OVERLAY;
extern Surrogate* SGT_QUERY_PL_KERNEL_KB_PARTITION_MEMBERSHIP;
extern Surrogate* SGT_QUERY_PL_KERNEL_KB_DISJOINT;
extern Keyword* KWD_QUERY_EXTENSIONAL_ASSERTION;
extern Symbol* SYM_QUERY_LOGIC_pD1;
extern Symbol* SYM_QUERY_LOGIC_pD2;
extern Symbol* SYM_QUERY_LOGIC_DISJOINT;
extern Symbol* SYM_QUERY_LOGIC_F_DISJOINT_TERMSp_QUERY_000;
extern Surrogate* SGT_QUERY_LOGIC_F_DISJOINT_TERMSp_MEMO_TABLE_000;
extern Symbol* SYM_QUERY_LOGIC_F_DISJOINT_TERMSp_QUERY_001;
extern Symbol* SYM_QUERY_STELLA_OR;
extern Symbol* SYM_QUERY_STELLA_AND;
extern Symbol* SYM_QUERY_PL_KERNEL_KB_CLASS;
extern Symbol* SYM_QUERY_LOGIC_REFUTATION_DISJOINT;
extern Symbol* SYM_QUERY_LOGIC_F_EXPENSIVE_DISJOINT_TERMSp_QUERY_000;
extern Surrogate* SGT_QUERY_LOGIC_ASSERTED_COLLECTION_MEMBERS_ITERATOR;
extern Symbol* SYM_QUERY_STELLA_COLLECTION;
extern Symbol* SYM_QUERY_LOGIC_SPECIALIZEp;
extern Symbol* SYM_QUERY_LOGIC_KIND;
extern Symbol* SYM_QUERY_STELLA_BASE_ITERATOR;
extern Symbol* SYM_QUERY_LOGIC_NESTED_BASE_ITERATOR;
extern Symbol* SYM_QUERY_LOGIC_OBSERVED_CARDINALITY;
extern Surrogate* SGT_QUERY_LOGIC_ASSERTED_MEMBER_OF_COLLECTION_SUPPORTS_ITERATOR;
extern Symbol* SYM_QUERY_LOGIC_MEMBER;
extern Surrogate* SGT_QUERY_PL_KERNEL_KB_COLLECTIONOF;
extern Surrogate* SGT_QUERY_STELLA_COLLECTION;
extern Keyword* KWD_QUERY_COLLECTION;
extern Keyword* KWD_QUERY_NAMED_DESCRIPTION;
extern Surrogate* SGT_QUERY_LOGIC_SKOLEM;
extern Keyword* KWD_QUERY_ENUMERATION;
extern Keyword* KWD_QUERY_SKOLEM;
extern Surrogate* SGT_QUERY_PL_KERNEL_KB_MEMBER_OF;
extern Keyword* KWD_QUERY_LOGIC_OBJECT;
extern Keyword* KWD_QUERY_UNDEFINED;
extern Surrogate* SGT_QUERY_LOGIC_F_ALL_ASSERTED_COLLECTION_MEMBERSdNEXTp_MEMO_TABLE_000;
extern Surrogate* SGT_QUERY_LOGIC_DESCRIPTION_EXTENSION_ITERATOR;
extern Symbol* SYM_QUERY_LOGIC_ROOT_DESCRIPTION;
extern Symbol* SYM_QUERY_LOGIC_SUBCOLLECTIONS;
extern Symbol* SYM_QUERY_LOGIC_EXTENSION_ITERATOR;
extern Symbol* SYM_QUERY_LOGIC_REFERENCE_PROPOSITION;
extern Symbol* SYM_QUERY_LOGIC_ALREADY_GENERATED_LIST;
extern Symbol* SYM_QUERY_LOGIC_ALREADY_GENERATED_TABLE;
extern Symbol* SYM_QUERY_LOGIC_REMOVING_DUPLICATESp;
extern Keyword* KWD_QUERY_GOAL_CACHES;
extern Keyword* KWD_QUERY_GOAL_CUTOFFS;
extern Keyword* KWD_QUERY_DEPTH_VIOLATION;
extern Keyword* KWD_QUERY_DEPTH_CUTOFF;
extern Keyword* KWD_QUERY_TECHNICAL;
extern Keyword* KWD_QUERY_LAY;
extern Surrogate* SGT_QUERY_LOGIC_QUERY_SOLUTION_TABLE;
extern Symbol* SYM_QUERY_STELLA_THE_MAP;
extern Symbol* SYM_QUERY_LOGIC_QUERY;
extern Symbol* SYM_QUERY_STELLA_FIRST;
extern Symbol* SYM_QUERY_STELLA_LAST;
extern Surrogate* SGT_QUERY_LOGIC_QUERY_SOLUTION;
extern Symbol* SYM_QUERY_LOGIC_BINDINGS;
extern Symbol* SYM_QUERY_LOGIC_BEST_JUSTIFICATION;
extern Symbol* SYM_QUERY_LOGIC_ALL_JUSTIFICATIONS;
extern Symbol* SYM_QUERY_STELLA_NEXT;
extern Surrogate* SGT_QUERY_LOGIC_QUERY_SOLUTION_TABLE_ITERATOR;
extern Symbol* SYM_QUERY_STELLA_THE_TABLE;
extern Symbol* SYM_QUERY_STELLA_CURSOR;
extern Symbol* SYM_QUERY_LOGIC_DEBUG_ID;
extern Keyword* KWD_QUERY_FORMAT;
extern Keyword* KWD_QUERY_OUTPUT_FILE;
extern Keyword* KWD_QUERY_IF_EXISTS;
extern Keyword* KWD_QUERY_SUPERSEDE;
extern Keyword* KWD_QUERY_APPEND;
extern Keyword* KWD_QUERY_VERTICAL;
extern Keyword* KWD_QUERY_LIST;
extern Keyword* KWD_QUERY_TSV;
extern Keyword* KWD_QUERY_HORIZONTAL;
extern Keyword* KWD_QUERY_TRACE_SOLUTIONS;
extern Symbol* SYM_QUERY_LOGIC_ATOMIC_SINGLETONSp;
extern Keyword* KWD_QUERY_VALUE_FORMAT;
extern Keyword* KWD_QUERY_READABLE;
extern Keyword* KWD_QUERY_BARE;
extern Surrogate* SGT_QUERY_STELLA_CONS;
extern Symbol* SYM_QUERY_PL_KERNEL_KB_pMATCH_SCORE;
extern Keyword* KWD_QUERY_EXECUTE_QUERY;
extern Keyword* KWD_QUERY_DONT_OPTIMIZEp;
extern Symbol* SYM_QUERY_LOGIC_DONT_OPTIMIZEp;
extern Symbol* SYM_QUERY_LOGIC_INITIAL_BINDINGS;
extern Keyword* KWD_QUERY_ITERATIVE_DEEPENINGp;
extern Symbol* SYM_QUERY_LOGIC_ITERATIVE_DEEPENINGp;
extern Keyword* KWD_QUERY_MATCH_MODE;
extern Keyword* KWD_QUERY_STRICT;
extern Keyword* KWD_QUERY_DEFERRED_OPTIONS;
extern Keyword* KWD_QUERY_ERROR;
extern Keyword* KWD_QUERY_FOUR_VALUEDp;
extern Keyword* KWD_QUERY_BACKWARD;
extern Symbol* SYM_QUERY_STELLA_TRUE;
extern Symbol* SYM_QUERY_LOGIC_KAPPA;
extern Symbol* SYM_QUERY_STELLA_EXISTS;
extern Keyword* KWD_QUERY_HOW_MANY;
extern Keyword* KWD_QUERY_SORT_BY;
extern Keyword* KWD_QUERY_SCORE;
extern Keyword* KWD_QUERY_CHECK_VARIABLESp;
extern Keyword* KWD_QUERY_MOVEOUT;
extern Keyword* KWD_QUERY_MAXIMUM_DEPTH;
extern Keyword* KWD_QUERY_INFERENCE_LEVEL;
extern Surrogate* SGT_QUERY_STELLA_GENERALIZED_SYMBOL;
extern Keyword* KWD_QUERY_THREE_VALUEDp;
extern Keyword* KWD_QUERY_SINGLETONSp;
extern Keyword* KWD_QUERY_ATOMIC_SINGLETONSp;
extern Keyword* KWD_QUERY_ALL_PROOFSp;
extern Keyword* KWD_QUERY_VALUES;
extern Keyword* KWD_QUERY_VALUES_DESCENDING;
extern Keyword* KWD_QUERY_VALUES_ASCENDING;
extern Keyword* KWD_QUERY_MINIMUM_SCORE;
extern Keyword* KWD_QUERY_MAXIMIZE_SCOREp;
extern Keyword* KWD_QUERY_MAXIMUM_UNKNOWNS;
extern Surrogate* SGT_QUERY_STELLA_PROPERTY_LIST;
extern Keyword* KWD_QUERY_HIGH;
extern Surrogate* SGT_QUERY_PL_KERNEL_KB_CONCEPT_PROTOTYPE;
extern Symbol* SYM_QUERY_LOGIC_pC;
extern Symbol* SYM_QUERY_LOGIC_pP;
extern Symbol* SYM_QUERY_PL_KERNEL_KB_CONCEPT_PROTOTYPE;
extern Symbol* SYM_QUERY_LOGIC_F_GET_PROTOTYPE_QUERY_000;
extern Keyword* KWD_QUERY_META;
extern Surrogate* SGT_QUERY_STELLA_RELATION;
extern Surrogate* SGT_QUERY_STELLA_VECTOR;
extern Keyword* KWD_QUERY_RETRACT_TRUE;
extern Keyword* KWD_QUERY_UPDATE_FROM_QUERY;
extern Symbol* SYM_QUERY_LOGIC_DESCRIPTIVEp;
extern Symbol* SYM_QUERY_LOGIC_WEIGHT;
extern Keyword* KWD_QUERY_ASSERT_FROM_QUERY;
extern Keyword* KWD_QUERY_PRINT;
extern Keyword* KWD_QUERY_SUMMARY;
extern Keyword* KWD_QUERY_ASSERT_TRUE;
extern Keyword* KWD_QUERY_STATISTICS;
extern Keyword* KWD_QUERY_STATS;
extern Keyword* KWD_QUERY_MODULE;
extern Surrogate* SGT_QUERY_STELLA_MODULE;
extern Keyword* KWD_QUERY_RELATION;
extern Surrogate* SGT_QUERY_STELLA_SYMBOL;
extern Keyword* KWD_QUERY_RECORD_JUSTIFICATIONSp;
extern Surrogate* SGT_QUERY_STELLA_BOOLEAN;
extern Keyword* KWD_QUERY_RESULT;
extern Surrogate* SGT_QUERY_STELLA_KEYWORD;
extern Symbol* SYM_QUERY_LOGIC_STARTUP_QUERY;
extern Symbol* SYM_QUERY_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
