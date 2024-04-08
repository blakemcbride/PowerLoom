//  -*- Mode: C++ -*-

// strategies.hh

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
class ConditionalAntecedentProofAdjunct : public ProofAdjunct {
public:
  Proposition* provableRule;
  Proposition* goal;
  Keyword* phase;
public:
  virtual Surrogate* primaryType();
};

class ClusteredConjunctionProofAdjunct : public ProofAdjunct {
public:
  Vector* clusterFrames;
public:
  virtual Surrogate* primaryType();
};


// Global declarations:
extern List* oPARALLEL_STRATEGIESo;
extern int oFAILED_GOAL_CUTOFFSo;
extern int oSUCCEEDED_GOAL_CUTOFFSo;
extern Module* oPL_ANONYMOUS_MODULEo;

// Function signatures:
Keyword* continueStrategiesProofs(ControlFrame* frame, Keyword* lastmove);
void clearStrategySlots(ControlFrame* frame);
ControlFrame* selectNextStrategy(ControlFrame* frame);
void recordBasePartialMatchTruth(ControlFrame* frame, Keyword* result);
Keyword* continueCurrentOrNextStrategy(ControlFrame* frame);
Keyword* resumeProofStrategyAfterSubgoal(ControlFrame* frame, Keyword* lastmove);
boolean filterOutStrategyP(Keyword* strategy, ControlFrame* frame);
Keyword* executeProofStrategy(ControlFrame* frame);
Keyword* continueParallelStrategiesProofs(ParallelControlFrame* pframe, Keyword* lastmove);
boolean parallelStrategyP(Keyword* strategy);
ParallelThread* selectNextChildThread(ParallelControlFrame* pframe);
ParallelThread* createChildThread(ParallelControlFrame* pframe);
Keyword* tryParallelThreadProof(ControlFrame* frame);
void pushNextStrategy(ControlFrame* frame, Keyword* strategy);
ControlFrame* createSubgoalFrame(ControlFrame* upframe, Proposition* goal, Keyword* strategy);
boolean specialistApplicableP(NamedDescription* description, Proposition* proposition);
Keyword* continueSpecialistProof(ControlFrame* frame, Keyword* lastmove);
Keyword* lookupCachedProof(ControlFrame* frame);
Keyword* scanCachedGoals(ControlFrame* frame);
Keyword* finishCachedGoalProcessing(AtomicGoalCache* cachedgoal, ControlFrame* frame, Keyword* successorfailure, boolean continuingP);
Keyword* tryGoalCachesProof(ControlFrame* frame);
Keyword* tryLookupGroundAssertionsProof(ControlFrame* frame);
Iterator* tsppDinitializeStrategy(ControlFrame* frame);
void tsppDspawnDerivedStrategies(ControlFrame* frame, Keyword* state);
boolean tsppDsingleValuedStrategyP(ControlFrame* frame);
void tsppDhandleDefaultResult(ControlFrame* frame);
void tsppDrecordResultJustification(ControlFrame* frame);
void tsppDpropagateResultTruthValue(ControlFrame* frame);
Keyword* tryScanPropositionsProof(ControlFrame* frame);
boolean hasShallowDisproofP(ControlFrame* frame);
boolean hasDisjointnessDisproofP(ControlFrame* frame);
Keyword* tryShallowDisproof(ControlFrame* frame);
Keyword* tryScanForValueClashProof(ControlFrame* frame);
Keyword* tryManufactureSkolemProof(ControlFrame* frame);
Proposition* extractSubgoalOfFrame(ControlFrame* frame);
Description* extractSubgoalDescriptionOfFrame(ControlFrame* frame);
Vector* findExternalArgumentsForSubgoal(ControlFrame* frame);
Keyword* trySubgoalStrategiesProof(ControlFrame* frame);
void establishGoalCache(ControlFrame* frame);
boolean checkForDuplicateRuleP(ControlFrame* frame, Proposition* impliesproposition);
Keyword* continueAntecedentsProof(ControlFrame* frame, Keyword* lastmove);
Iterator* allocateAntecedentsIterator(Description* goaldescription, Vector* externalarguments, boolean reversepolarityP);
Cons* optimizeOrderOfApplicableRules(Cons* rules, boolean tailP);
boolean hasMoreAntecedentsP(ControlFrame* frame);
Keyword* tryGoalComplementProof(ControlFrame* frame);
Keyword* tryForwardGoalsProof(ControlFrame* frame);
ConditionalAntecedentProofAdjunct* newConditionalAntecedentProofAdjunct();
Object* accessConditionalAntecedentProofAdjunctSlotValue(ConditionalAntecedentProofAdjunct* self, Symbol* slotname, Object* value, boolean setvalueP);
ControlFrame* createConditionalAntecedentSubframe(ControlFrame* frame, Proposition* goal, Proposition* provablerule);
Keyword* continueConditionalAntecedentProof(ControlFrame* frame, Keyword* lastmove);
Keyword* tryFullSubqueryProof(ControlFrame* frame);
Description* extractCollectionArgument(Proposition* proposition);
Keyword* tryIsaPropositionProof(ControlFrame* frame);
Keyword* tryScanCollectionProof(ControlFrame* frame);
boolean inferableDescriptionP(Object* self);
Keyword* tryImpliesProof(ControlFrame* frame);
Keyword* trySimpleContainedByProof(Object* subcollection, Object* supercollection, boolean reversepolarityP);
Keyword* tryContainedByProof(ControlFrame* upframe);
Proposition* createContainedByArgument(Object* collection, List* bridgeargs);
Keyword* continueContainedByProof(ControlFrame* frame, Keyword* lastmove);
Keyword* trySubsumptionTest(ControlFrame* frame);
Keyword* tryEquivalenceProof(ControlFrame* frame);
ClusteredConjunctionProofAdjunct* newClusteredConjunctionProofAdjunct();
Object* accessClusteredConjunctionProofAdjunctSlotValue(ClusteredConjunctionProofAdjunct* self, Symbol* slotname, Object* value, boolean setvalueP);
Keyword* continueClusteredConjunctionProof(ControlFrame* andframe, Keyword* lastmove);
World* pushMonotonicWorld();
Keyword* tryDisjunctiveImplicationProof(ControlFrame* frame);
Keyword* resumeDisjunctiveImplicationProof(ControlFrame* frame, Keyword* lastmove);
LogicObject* createAnonymousInstance(const char* prefix, boolean skolemP);
LogicObject* createHypothesizedInstance(const char* prefix);
Keyword* tryUniversalIntroductionProof(ControlFrame* frame);
Keyword* tryRefutationProof(ControlFrame* frame);
Keyword* continueForallProof(ControlFrame* frame, Keyword* lastmove);
Keyword* continueExistsProof(ControlFrame* frame, Keyword* lastmove);
Keyword* continueConstantProof(ControlFrame* frame, Keyword* lastmove);
void registerInferenceCutoff(ControlFrame* frame, Keyword* reason);
Keyword* continueFailProof(ControlFrame* frame, Keyword* lastmove);
void helpStartupStrategies1();
void helpStartupStrategies2();
void helpStartupStrategies3();
void startupStrategies();

// Auxiliary global declarations:
extern Keyword* KWD_STRATEGIES_DOWN;
extern Keyword* KWD_STRATEGIES_MOVE_DOWN;
extern Keyword* KWD_STRATEGIES_UP_TRUE;
extern Keyword* KWD_STRATEGIES_UP_FAIL;
extern Keyword* KWD_STRATEGIES_FAILURE;
extern Keyword* KWD_STRATEGIES_FINAL_SUCCESS;
extern Keyword* KWD_STRATEGIES_CONTINUING_SUCCESS;
extern Keyword* KWD_STRATEGIES_GOAL_TREE;
extern Symbol* SYM_STRATEGIES_LOGIC_JUSTIFICATION;
extern Keyword* KWD_STRATEGIES_TERMINAL_FAILURE;
extern Symbol* SYM_STRATEGIES_LOGIC_INFERENCE_CUTOFF_REASON;
extern Symbol* SYM_STRATEGIES_STELLA_ITERATOR;
extern Symbol* SYM_STRATEGIES_LOGIC_ANTECEDENTS_RULE;
extern Symbol* SYM_STRATEGIES_LOGIC_PROOF_ADJUNCT;
extern Keyword* KWD_STRATEGIES_PARALLEL_STRATEGIES;
extern Keyword* KWD_STRATEGIES_SELECT_PARALLEL_THREAD;
extern Keyword* KWD_STRATEGIES_FAIL;
extern Keyword* KWD_STRATEGIES_TRUE;
extern Keyword* KWD_STRATEGIES_STRATEGIES;
extern Symbol* SYM_STRATEGIES_LOGIC_DESCRIPTION;
extern Keyword* KWD_STRATEGIES_MOVE_IN_PLACE;
extern Keyword* KWD_STRATEGIES_TIME_OUT;
extern Keyword* KWD_STRATEGIES_SPECIALIST;
extern Keyword* KWD_STRATEGIES_ANTECEDENTS;
extern Keyword* KWD_STRATEGIES_CLUSTERED_CONJUNCTION;
extern Keyword* KWD_STRATEGIES_CONDITIONAL_ANTECEDENT;
extern Keyword* KWD_STRATEGIES_DISJUNCTIVE_IMPLICATION_INTRODUCTION;
extern Keyword* KWD_STRATEGIES_ATOMIC_GOAL;
extern Keyword* KWD_STRATEGIES_DUMMY_JUSTIFICATION;
extern Keyword* KWD_STRATEGIES_LOOKUP_GOAL_CACHES;
extern Symbol* SYM_STRATEGIES_LOGIC_CHECK_FOR_CACHED_GOALSp;
extern Keyword* KWD_STRATEGIES_DUPLICATE_GOALS;
extern Keyword* KWD_STRATEGIES_MANUFACTURE_SKOLEM;
extern Surrogate* SGT_STRATEGIES_PL_KERNEL_KB_TOTAL;
extern Keyword* KWD_STRATEGIES_LOOKUP_ASSERTIONS;
extern Keyword* KWD_STRATEGIES_SCAN_PROPOSITIONS;
extern Keyword* KWD_STRATEGIES_SCAN_PARTIAL_PROPOSITIONS;
extern Keyword* KWD_STRATEGIES_SCAN_COLLECTION;
extern Keyword* KWD_STRATEGIES_SHALLOW_DISPROOF;
extern Keyword* KWD_STRATEGIES_SCAN_FOR_VALUE_CLASH;
extern Keyword* KWD_STRATEGIES_ALL_SUBGOAL_STRATEGIES;
extern Keyword* KWD_STRATEGIES_FULL_SUBQUERY;
extern Keyword* KWD_STRATEGIES_GOAL_COMPLEMENT;
extern Keyword* KWD_STRATEGIES_FORWARD_GOALS;
extern Keyword* KWD_STRATEGIES_IMPLIES;
extern Keyword* KWD_STRATEGIES_CONTAINED_BY;
extern Keyword* KWD_STRATEGIES_EQUIVALENCE;
extern Keyword* KWD_STRATEGIES_UNIVERSAL_INTRODUCTION;
extern Keyword* KWD_STRATEGIES_SUBSUMPTION_TEST;
extern Keyword* KWD_STRATEGIES_REFUTATION;
extern Keyword* KWD_STRATEGIES_STRATEGY;
extern Keyword* KWD_STRATEGIES_DEBUG;
extern Keyword* KWD_STRATEGIES_SUCCESS;
extern Symbol* SYM_STRATEGIES_LOGIC_LATEST_POSITIVE_SCORE;
extern Keyword* KWD_STRATEGIES_GOAL_CACHES;
extern Keyword* KWD_STRATEGIES_ISA;
extern Keyword* KWD_STRATEGIES_INITIALIZE;
extern Keyword* KWD_STRATEGIES_FUNCTION;
extern Surrogate* SGT_STRATEGIES_LOGIC_WHYNOT_PARTIAL_MATCH;
extern Keyword* KWD_STRATEGIES_NOT;
extern Surrogate* SGT_STRATEGIES_PL_KERNEL_KB_MEMBER_OF;
extern Surrogate* SGT_STRATEGIES_STELLA_LIST;
extern Keyword* KWD_STRATEGIES_FORWARD;
extern Keyword* KWD_STRATEGIES_DUPLICATE_;
extern Keyword* KWD_STRATEGIES_BACKWARD;
extern Symbol* SYM_STRATEGIES_LOGIC_BACKWARD_ONLYp;
extern Symbol* SYM_STRATEGIES_LOGIC_FORWARD_ONLYp;
extern Surrogate* SGT_STRATEGIES_LOGIC_DESCRIPTION;
extern Surrogate* SGT_STRATEGIES_STELLA_CONS_ITERATOR;
extern Keyword* KWD_STRATEGIES_FORWARD_RULE;
extern Surrogate* SGT_STRATEGIES_LOGIC_CONDITIONAL_ANTECEDENT_PROOF_ADJUNCT;
extern Symbol* SYM_STRATEGIES_LOGIC_PROVABLE_RULE;
extern Symbol* SYM_STRATEGIES_LOGIC_GOAL;
extern Symbol* SYM_STRATEGIES_STELLA_PHASE;
extern Keyword* KWD_STRATEGIES_ORIGINAL_GOAL;
extern Surrogate* SGT_STRATEGIES_STELLA_THING;
extern Surrogate* SGT_STRATEGIES_STELLA_LITERAL_WRAPPER;
extern Surrogate* SGT_STRATEGIES_LOGIC_PROPOSITION;
extern Symbol* SYM_STRATEGIES_LOGIC_COMPLEMENT_DESCRIPTION;
extern Symbol* SYM_STRATEGIES_LOGIC_CONTAINED_BY;
extern Surrogate* SGT_STRATEGIES_LOGIC_NAMED_DESCRIPTION;
extern Symbol* SYM_STRATEGIES_STELLA_ISA;
extern Symbol* SYM_STRATEGIES_STELLA_PREDICATE;
extern Keyword* KWD_STRATEGIES_LOCAL;
extern Symbol* SYM_STRATEGIES_LOGIC_BACK;
extern Keyword* KWD_STRATEGIES_POPPED;
extern Symbol* SYM_STRATEGIES_LOGIC_EXTERNAL_VARIABLES;
extern Surrogate* SGT_STRATEGIES_LOGIC_CLUSTERED_CONJUNCTION_PROOF_ADJUNCT;
extern Symbol* SYM_STRATEGIES_LOGIC_CLUSTER_FRAMES;
extern Keyword* KWD_STRATEGIES_AND;
extern Keyword* KWD_STRATEGIES_PREDICATE;
extern Symbol* SYM_STRATEGIES_LOGIC_MONOTONICp;
extern Symbol* SYM_STRATEGIES_LOGIC_HYPOTHESIZED_INSTANCEp;
extern Symbol* SYM_STRATEGIES_LOGIC_IO_VARIABLES;
extern Keyword* KWD_STRATEGIES_ITERATIVE_FORALL;
extern Keyword* KWD_STRATEGIES_NORMAL;
extern Keyword* KWD_STRATEGIES_CONSTANT_PROPOSITION;
extern Keyword* KWD_STRATEGIES_TECHNICAL;
extern Keyword* KWD_STRATEGIES_LAY;
extern Symbol* SYM_STRATEGIES_LOGIC_STARTUP_STRATEGIES;
extern Symbol* SYM_STRATEGIES_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
