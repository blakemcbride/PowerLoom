//  -*- Mode: C++ -*-

// partial-match.hh

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
class PartialMatchFrame : public StandardObject {
// Abstract class acting as placeholder for system and
// user-defined partial match implementations.
public:
  Keyword* kind;
  ControlFrame* controlFrame;
  PartialMatchFrame* parent;
  PartialMatchFrame* child;
  double matchScore;
  double dynamicCutoff;
  Cons* argumentScores;
  Cons* argumentWeights;
  Cons* unboundVars;
  boolean successP;
public:
  virtual double computePartialTruth(QueryIterator* query);
  virtual QueryIterator* retrievePartialSolutions(QueryIterator* query);
  virtual void initializePartialMatchStrategy(QueryIterator* query);
  virtual boolean earlyPartialMatchOrSuccessP();
  virtual boolean earlyPartialMatchAndFailureP();
  virtual void popPartialMatchScore();
  virtual void recordPartialMatchScore(double score, double weight);
  virtual void setBasePartialMatchTruth(Proposition* prop, Keyword* truth);
  virtual Keyword* continuePartialAntecedentsProof(Keyword* lastmove);
  virtual Keyword* continuePartialStrategiesProofs(Keyword* lastmove);
  virtual double computeGoalScore();
  virtual Keyword* continuePartialFailProof(Keyword* lastmove);
  virtual Keyword* continuePartialNotProof(Keyword* lastmove);
  virtual double computeNotScore();
  virtual Keyword* continuePartialOrProof(Keyword* lastmove);
  virtual double computeOrScore();
  virtual Keyword* continuePartialAndProof(ControlFrame* frame, Keyword* lastmove);
  virtual double computeAndScore();
  virtual boolean allowUnboundVariablesP();
  virtual void setJustificationPartialTruth(Justification* justification);
  virtual void setCachePartialTruth(AtomicGoalCache* cache);
  virtual void traceFramePartialTruth(Keyword* lastmove, OutputStream* stream);
  virtual void propagateFramePartialTruth(ControlFrame* target);
  virtual void setFramePartialTruth(TruthValue* truthvalue, double score, boolean ignorepolarityP);
  virtual boolean definedFramePartialTruthP();
  virtual void clearFramePartialTruth();
  virtual double computeAssertionScore(Proposition* proposition, TruthValue* truthvalue);
  virtual double propositionWeight(Proposition* proposition);
  virtual double invertMatchScore(double score);
  virtual double truthValueScore(TruthValue* truthvalue);
  virtual boolean cutoffPartialMatchP(boolean traceP);
  virtual void setDynamicCutoff();
  virtual double computeDynamicCutoff();
  virtual PartialMatchFrame* createPartialMatchFrame(ControlFrame* frame, Keyword* kind);
};

class IncrementalPartialMatch : public PartialMatchFrame {
public:
  double accumulatedScore;
  double accumulatedWeight;
  double totalWeight;
  double maximumScore;
public:
  virtual Surrogate* primaryType();
  virtual double computePartialTruth(QueryIterator* query);
  virtual QueryIterator* retrievePartialSolutions(QueryIterator* query);
  virtual Keyword* continuePartialFailProof(Keyword* lastmove);
  virtual Keyword* continuePartialAntecedentsProof(Keyword* lastmove);
  virtual Keyword* continuePartialStrategiesProofs(Keyword* lastmove);
  virtual double computeGoalScore();
  virtual Keyword* continuePartialNotProof(Keyword* lastmove);
  virtual double computeNotScore();
  virtual Keyword* continuePartialOrProof(Keyword* lastmove);
  virtual double computeOrScore();
  virtual void popOrPartialMatchScore();
  virtual void pushOrPartialMatchScore(double score, double weight);
  virtual Keyword* continuePartialAndProof(ControlFrame* frame, Keyword* lastmove);
  virtual boolean skipAndClauseP(ControlFrame* frame, Cons* forbiddenvars);
  virtual double computeAndScore();
  virtual void popAndPartialMatchScore();
  virtual void pushAndPartialMatchScore(double score, double weight);
  virtual double propositionWeight(Proposition* proposition);
  virtual double invertMatchScore(double score);
  virtual double truthValueScore(TruthValue* truthvalue);
  virtual void clearFramePartialTruth();
  virtual double computeDynamicCutoff();
  virtual PartialMatchFrame* createPartialMatchFrame(ControlFrame* frame, Keyword* kind);
};

class NnPartialMatch : public PartialMatchFrame {
public:
  double accumulatedScore;
  double maximumScore;
  Cons* rules;
  int arity;
public:
  virtual Surrogate* primaryType();
  virtual double computePartialTruth(QueryIterator* query);
  virtual boolean earlyPartialMatchOrSuccessP();
  virtual boolean earlyPartialMatchAndFailureP();
  virtual double computeGoalScore();
  virtual double computeNotScore();
  virtual double computeOrScore();
  virtual double computeAndScore();
  virtual void popPartialMatchScore();
  virtual void recordPartialMatchScore(double score, double weight);
  virtual void setJustificationPartialTruth(Justification* justification);
  virtual void setCachePartialTruth(AtomicGoalCache* cache);
  virtual void setBasePartialMatchTruth(Proposition* prop, Keyword* truth);
  virtual double propositionWeight(Proposition* proposition);
  virtual double computeDynamicCutoff();
  virtual PartialMatchFrame* createPartialMatchFrame(ControlFrame* frame, Keyword* kind);
  virtual void initializeNnPartialMatch();
};


// Global declarations:
extern Keyword* oPARTIAL_MATCH_MODEo;
extern boolean oGREEDY_NETWORK_PRUNINGo;
extern Keyword* oRULE_COMBINATIONo;
extern boolean oPLANNING_MODEo;
extern Cons* oPLANABLE_PREDICATESo;
extern boolean oFAIL_UNBOUND_CLAUSESpo;
extern double oMINIMUM_SCORE_CUTOFFo;
extern double oMAXIMUM_SCORE_CUTOFFo;
extern boolean oAND_MISSED_A_BINDINGo;

// Function signatures:
void setPartialMatchMode(Keyword* k);
Object* accessPartialMatchFrameSlotValue(PartialMatchFrame* self, Symbol* slotname, Object* value, boolean setvalueP);
void setRuleCombination(Keyword* k);
void setGreedyNetworkPruning(boolean b);
void setGreedyNetworkPruningEvaluatorWrapper(Cons* arguments);
void setMaximumScoreCutoff(double c);
void setMaximumScoreCutoffEvaluatorWrapper(Cons* arguments);
void setMinimumScoreCutoff(double c);
void setMinimumScoreCutoffEvaluatorWrapper(Cons* arguments);
void linkToParentPartialMatchFrame(PartialMatchFrame* self);
IncrementalPartialMatch* newIncrementalPartialMatch(Keyword* kind, ControlFrame* controlFrame);
Object* accessIncrementalPartialMatchSlotValue(IncrementalPartialMatch* self, Symbol* slotname, Object* value, boolean setvalueP);
void initializeIncrementalPartialMatch(IncrementalPartialMatch* self);
NnPartialMatch* newNnPartialMatch(Keyword* kind, ControlFrame* controlFrame);
Object* accessNnPartialMatchSlotValue(NnPartialMatch* self, Symbol* slotname, Object* value, boolean setvalueP);
double probabilisticSumN(Cons* form);
double probabilisticSum(double x, double y);
boolean pruneNnSearchP(NnPartialMatch* self);
PartialMatchFrame* makePartialMatchFrame(QueryIterator* query);
void initializePartialQuery(QueryIterator* query);
void createAndLinkPartialMatchFrame(ControlFrame* frame, Keyword* kind);
Cons* getUnboundVariables(Proposition* prop);
boolean allVariablesUnboundP(Proposition* prop);
boolean unboundVariablesInFrameP(ControlFrame* frame);
void recordLatestPartialMatchScore(ControlFrame* frame);
boolean computePartialMatchAndFailureP(ControlFrame* frame);
boolean computePartialMatchOrSuccessP(ControlFrame* frame);
boolean computePartialMatchScoreP(ControlFrame* frame);
QueryIterator* retrievePartial(Cons* tree);
QueryIterator* retrievePartialEvaluatorWrapper(Cons* arguments);
QueryIterator* callRetrievePartial(Object* query);
void sortSolutionsByScore(QueryIterator* query);
boolean solutionScoreGreaterThanP(QuerySolution* s1, QuerySolution* s2);
double askPartial(Cons* propositionAoptions);
FloatWrapper* askPartialEvaluatorWrapper(Cons* arguments);
double returnPartialTruth(QueryIterator* query, boolean topP);
double callAskPartial(Object* query);
boolean nullInstanceP(Object* x);
LogicObject* getNullInstance();
boolean nullInstancePropositionsExistP();
Iterator* allMatchingPartialPropositions(Proposition* self);
boolean partialArgumentsUnifyWithArgumentsP(Proposition* subproposition, Proposition* referenceproposition);
Keyword* tryScanPartialPropositionsProof(ControlFrame* frame);
void helpStartupPartialMatch1();
void helpStartupPartialMatch2();
void helpStartupPartialMatch3();
void startupPartialMatch();

// Auxiliary global declarations:
extern Keyword* KWD_PARTIAL_MATCH_BASIC;
extern Keyword* KWD_PARTIAL_MATCH_MAX;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_KIND;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_CONTROL_FRAME;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_PARENT;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_CHILD;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_POSITIVE_SCORE;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_DYNAMIC_CUTOFF;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_ARGUMENT_SCORES;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_ARGUMENT_WEIGHTS;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_UNBOUND_VARS;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_SUCCESSp;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_WEIGHT;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_SCORE;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE;
extern Keyword* KWD_PARTIAL_MATCH_CONTROL_FRAME;
extern Keyword* KWD_PARTIAL_MATCH_KIND;
extern Keyword* KWD_PARTIAL_MATCH_DOWN;
extern Keyword* KWD_PARTIAL_MATCH_UP_TRUE;
extern Keyword* KWD_PARTIAL_MATCH_UP_FAIL;
extern Keyword* KWD_PARTIAL_MATCH_TRUE;
extern Keyword* KWD_PARTIAL_MATCH_FAIL;
extern Surrogate* SGT_PARTIAL_MATCH_LOGIC_INCREMENTAL_PARTIAL_MATCH;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_ACCUMULATED_SCORE;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_ACCUMULATED_WEIGHT;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_TOTAL_WEIGHT;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_MAXIMUM_SCORE;
extern Keyword* KWD_PARTIAL_MATCH_AND;
extern Keyword* KWD_PARTIAL_MATCH_SKIPPED_CONJUNCT;
extern Keyword* KWD_PARTIAL_MATCH_FAILURE;
extern Keyword* KWD_PARTIAL_MATCH_POPPED;
extern Symbol* SYM_PARTIAL_MATCH_STELLA_ARGUMENTS;
extern Keyword* KWD_PARTIAL_MATCH_GOAL_TREE;
extern Keyword* KWD_PARTIAL_MATCH_MOVE_DOWN;
extern Keyword* KWD_PARTIAL_MATCH_NOISY_OR;
extern Keyword* KWD_PARTIAL_MATCH_CONTINUING_SUCCESS;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_ANTECEDENTS_RULE;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_INFERENCE_CUTOFF_REASON;
extern Surrogate* SGT_PARTIAL_MATCH_LOGIC_NN_PARTIAL_MATCH;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_RULES;
extern Symbol* SYM_PARTIAL_MATCH_STELLA_ARITY;
extern Keyword* KWD_PARTIAL_MATCH_OR;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_NEURAL_NET;
extern Keyword* KWD_PARTIAL_MATCH_ATOMIC_GOAL;
extern Keyword* KWD_PARTIAL_MATCH_FULL_SUBQUERY;
extern Symbol* SYM_PARTIAL_MATCH_STELLA_ITERATOR;
extern Keyword* KWD_PARTIAL_MATCH_MATCH_MODE;
extern Keyword* KWD_PARTIAL_MATCH_INCREMENTAL;
extern Keyword* KWD_PARTIAL_MATCH_NN;
extern Keyword* KWD_PARTIAL_MATCH_NEURAL_NETWORK;
extern Surrogate* SGT_PARTIAL_MATCH_STELLA_CLASS;
extern Keyword* KWD_PARTIAL_MATCH_ERROR;
extern Keyword* KWD_PARTIAL_MATCH_MINIMUM_SCORE;
extern Keyword* KWD_PARTIAL_MATCH_FUNCTION;
extern Surrogate* SGT_PARTIAL_MATCH_LOGIC_PATTERN_VARIABLE;
extern Keyword* KWD_PARTIAL_MATCH_SORT_BY;
extern Keyword* KWD_PARTIAL_MATCH_SCORE;
extern Keyword* KWD_PARTIAL_MATCH_MAXIMIZE_SCOREp;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_JUSTIFICATION;
extern Keyword* KWD_PARTIAL_MATCH_STATIC;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_SUPPORT;
extern Surrogate* SGT_PARTIAL_MATCH_PL_KERNEL_KB_NULL;
extern Keyword* KWD_PARTIAL_MATCH_RELATION;
extern Symbol* SYM_PARTIAL_MATCH_LOGIC_STARTUP_PARTIAL_MATCH;
extern Symbol* SYM_PARTIAL_MATCH_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
