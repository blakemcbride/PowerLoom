//  -*- Mode: C++ -*-

// partial-match.cc

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

#include "logic/logic-system.hh"

namespace logic {
  using namespace stella;

Keyword* oPARTIAL_MATCH_MODEo = NULL;

boolean oGREEDY_NETWORK_PRUNINGo = true;

void setPartialMatchMode(Keyword* k) {
  oPARTIAL_MATCH_MODEo = k;
}

Keyword* oRULE_COMBINATIONo = NULL;

boolean oPLANNING_MODEo = false;

Cons* oPLANABLE_PREDICATESo = NULL;

Object* accessPartialMatchFrameSlotValue(PartialMatchFrame* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PARTIAL_MATCH_LOGIC_KIND) {
    if (setvalueP) {
      self->kind = ((Keyword*)(value));
    }
    else {
      value = self->kind;
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_CONTROL_FRAME) {
    if (setvalueP) {
      self->controlFrame = ((ControlFrame*)(value));
    }
    else {
      value = self->controlFrame;
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_PARENT) {
    if (setvalueP) {
      self->parent = ((PartialMatchFrame*)(value));
    }
    else {
      value = self->parent;
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_CHILD) {
    if (setvalueP) {
      self->child = ((PartialMatchFrame*)(value));
    }
    else {
      value = self->child;
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE) {
    if (setvalueP) {
      self->matchScore = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->matchScore);
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_POSITIVE_SCORE) {
    if (setvalueP) {
      self->matchScore = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->matchScore);
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_DYNAMIC_CUTOFF) {
    if (setvalueP) {
      self->dynamicCutoff = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->dynamicCutoff);
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_ARGUMENT_SCORES) {
    if (setvalueP) {
      self->argumentScores = ((Cons*)(value));
    }
    else {
      value = self->argumentScores;
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_ARGUMENT_WEIGHTS) {
    if (setvalueP) {
      self->argumentWeights = ((Cons*)(value));
    }
    else {
      value = self->argumentWeights;
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_UNBOUND_VARS) {
    if (setvalueP) {
      self->unboundVars = ((Cons*)(value));
    }
    else {
      value = self->unboundVars;
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_SUCCESSp) {
    if (setvalueP) {
      self->successP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->successP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

boolean oFAIL_UNBOUND_CLAUSESpo = false;

// Positive scores below *minimum-score-cutoff* get trimmed
// to 0.0 during partial match operations.
double oMINIMUM_SCORE_CUTOFFo = 0.0;

// Positive scores above *maximum-score-cutoff* get trimmed
// to 1.0 during partial match operations.
double oMAXIMUM_SCORE_CUTOFFo = 0.0;

void setRuleCombination(Keyword* k) {
  oRULE_COMBINATIONo = k;
}

void setGreedyNetworkPruning(boolean b) {
  oGREEDY_NETWORK_PRUNINGo = b;
}

void setGreedyNetworkPruningEvaluatorWrapper(Cons* arguments) {
  setGreedyNetworkPruning(((BooleanWrapper*)(arguments->value))->wrapperValue);
}

void setMaximumScoreCutoff(double c) {
  oMAXIMUM_SCORE_CUTOFFo = c;
}

void setMaximumScoreCutoffEvaluatorWrapper(Cons* arguments) {
  setMaximumScoreCutoff(((FloatWrapper*)(arguments->value))->wrapperValue);
}

void setMinimumScoreCutoff(double c) {
  oMAXIMUM_SCORE_CUTOFFo = c;
}

void setMinimumScoreCutoffEvaluatorWrapper(Cons* arguments) {
  setMinimumScoreCutoff(((FloatWrapper*)(arguments->value))->wrapperValue);
}

boolean oAND_MISSED_A_BINDINGo = false;

void linkToParentPartialMatchFrame(PartialMatchFrame* self) {
  { ControlFrame* controlframe = self->controlFrame->up;

    while (((boolean)(controlframe)) &&
        (!((boolean)(controlframe->partialMatchFrame)))) {
      controlframe = controlframe->up;
    }
    if (((boolean)(controlframe))) {
      self->parent = controlframe->partialMatchFrame;
      controlframe->partialMatchFrame->child = self;
    }
  }
}

PartialMatchFrame* PartialMatchFrame::createPartialMatchFrame(ControlFrame* frame, Keyword* kind) {
  { PartialMatchFrame* self = this;

    {
      frame = frame;
      kind = kind;
    }
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Missing concrete method named 'create-partial-match-frame' on the" << std::endl << "   class " << "`" << self->primaryType() << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

double PartialMatchFrame::computeDynamicCutoff() {
  { PartialMatchFrame* self = this;

    return (NULL_FLOAT);
  }
}

void PartialMatchFrame::setDynamicCutoff() {
  { PartialMatchFrame* self = this;

    { double cutoff = self->computeDynamicCutoff();

      if (cutoff != NULL_FLOAT) {
        if ((cutoff < -100) ||
            (cutoff > 100)) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "*** fishy dynamic cutoff=" << "`" << cutoff << "'" << " computed, resetting to 0.0" << std::endl;
          cutoff = 0.0;
        }
        self->dynamicCutoff = cutoff;
      }
    }
  }
}

boolean PartialMatchFrame::cutoffPartialMatchP(boolean traceP) {
  { PartialMatchFrame* self = this;

    { double score = self->matchScore;
      double cutoff = self->dynamicCutoff;
      boolean cutoffP = false;

      if ((score == NULL_FLOAT) ||
          ((cutoff == NULL_FLOAT) ||
           (cutoff == 0.0))) {
        cutoffP = false;
      }
      else if (cutoff < 0.0) {
        cutoffP = score > cutoff;
      }
      else {
        cutoffP = score < cutoff;
      }
      if (cutoffP &&
          traceP) {
        std::cout << "*** Cutting off search, cutoff=" << cutoff << std::endl;
      }
      return (cutoffP);
    }
  }
}

double PartialMatchFrame::truthValueScore(TruthValue* truthvalue) {
  { PartialMatchFrame* self = this;

    return (((truthvalue == TRUE_TRUTH_VALUE) ? 1.0 : 0.0));
  }
}

double PartialMatchFrame::invertMatchScore(double score) {
  { PartialMatchFrame* self = this;

    return (1.0 - score);
  }
}

double PartialMatchFrame::propositionWeight(Proposition* proposition) {
  { PartialMatchFrame* self = this;

    if (((boolean)(proposition))) {
      { double weight = ((FloatWrapper*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_WEIGHT, NULL_FLOAT_WRAPPER)))->wrapperValue;

        if (weight == NULL_FLOAT) {
          return (1.0);
        }
        else {
          return (weight);
        }
      }
    }
    else {
      return (1.0);
    }
  }
}

double PartialMatchFrame::computeAssertionScore(Proposition* proposition, TruthValue* truthvalue) {
  { PartialMatchFrame* self = this;

    if (!((boolean)(truthvalue))) {
      truthvalue = ((TruthValue*)(accessInContext(proposition->truthValue, proposition->homeContext, false)));
    }
    if (!((boolean)(truthvalue))) {
      std::cerr << "Safety violation: " << "INTERNAL ERROR: missing truth value for assertion";
    }
    { FloatWrapper* score = ((FloatWrapper*)(accessInContext(dynamicSlotValue(proposition->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_SCORE, NULL), proposition->homeContext, false)));
      double weight = self->propositionWeight(proposition);

      if (!((boolean)(score))) {
        score = wrapFloat(self->truthValueScore(truthvalue));
      }
      else if ((truthvalue == FALSE_TRUTH_VALUE) ||
          (truthvalue == DEFAULT_FALSE_TRUTH_VALUE)) {
        score = wrapFloat(self->invertMatchScore(score->wrapperValue));
      }
      return (score->wrapperValue * weight);
    }
  }
}

void PartialMatchFrame::clearFramePartialTruth() {
  { PartialMatchFrame* self = this;

    self->matchScore = NULL_FLOAT;
  }
}

boolean ControlFrame::definedFramePartialTruthP() {
  { ControlFrame* self = this;

    return (((boolean)(self->partialMatchFrame)) &&
        (self->partialMatchFrame->matchScore != NULL_FLOAT));
  }
}

boolean PartialMatchFrame::definedFramePartialTruthP() {
  { PartialMatchFrame* self = this;

    return (self->matchScore != NULL_FLOAT);
  }
}

void PartialMatchFrame::setFramePartialTruth(TruthValue* truthvalue, double score, boolean ignorepolarityP) {
  { PartialMatchFrame* self = this;

    { boolean flippolarityP = self->controlFrame->reversePolarityP &&
          (!ignorepolarityP);

      if ((score == NULL_FLOAT) &&
          ((boolean)(truthvalue))) {
        score = self->truthValueScore(truthvalue);
      }
      if (flippolarityP) {
        score = self->invertMatchScore(score);
      }
      self->matchScore = score;
      setDynamicSlotValue(oQUERYITERATORo->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, wrapFloat(score), NULL_FLOAT_WRAPPER);
    }
  }
}

void PartialMatchFrame::propagateFramePartialTruth(ControlFrame* target) {
  { PartialMatchFrame* source = this;

    { PartialMatchFrame* targetpmf = target->partialMatchFrame;
      boolean flippolarityP = !(source->controlFrame->reversePolarityP == target->reversePolarityP);

      if (!((boolean)(targetpmf))) {
        if (flippolarityP) {
          targetpmf = ((PartialMatchFrame*)(createObject(source->primaryType(), 4, KWD_PARTIAL_MATCH_CONTROL_FRAME, target, KWD_PARTIAL_MATCH_KIND, target->state)));
          targetpmf->parent = source->parent;
          targetpmf->child = source;
        }
        else {
          targetpmf = source;
        }
        target->partialMatchFrame = targetpmf;
      }
      targetpmf->matchScore = source->matchScore;
      if (flippolarityP &&
          ((!unknownTruthValueP(source->controlFrame->truthValue)) ||
           (!(source->matchScore == source->truthValueScore(UNKNOWN_TRUTH_VALUE))))) {
        targetpmf->matchScore = source->invertMatchScore(source->matchScore);
      }
      setDynamicSlotValue(oQUERYITERATORo->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, wrapFloat(targetpmf->matchScore), NULL_FLOAT_WRAPPER);
    }
  }
}

void PartialMatchFrame::traceFramePartialTruth(Keyword* lastmove, OutputStream* stream) {
  { PartialMatchFrame* self = this;

    { double weight = self->propositionWeight(self->controlFrame->proposition);

      if (lastmove == KWD_PARTIAL_MATCH_DOWN) {
        { double cutoff = self->computeDynamicCutoff();

          if (cutoff != NULL_FLOAT) {
            *(stream->nativeStream) << "cutoff=" << cutoff;
          }
        }
      }
      else if ((lastmove == KWD_PARTIAL_MATCH_UP_TRUE) ||
          (lastmove == KWD_PARTIAL_MATCH_UP_FAIL)) {
        { double score = self->matchScore;

          *(stream->nativeStream) << "score=" << score;
          if ((weight != NULL_FLOAT) &&
              (!(weight == 1.0))) {
            *(stream->nativeStream) << " weight=" << weight;
          }
        }
      }
      else {
      }
    }
  }
}

void ControlFrame::setCachePartialTruth(AtomicGoalCache* cache) {
  { ControlFrame* self = this;

    { PartialMatchFrame* pmf = self->partialMatchFrame;

      if (((boolean)(pmf))) {
        pmf->setCachePartialTruth(cache);
      }
    }
  }
}

void PartialMatchFrame::setCachePartialTruth(AtomicGoalCache* cache) {
  { PartialMatchFrame* self = this;

    cache->matchScore = self->matchScore;
  }
}

void ControlFrame::setJustificationPartialTruth(Justification* justification) {
  { ControlFrame* self = this;

    { PartialMatchFrame* pmf = self->partialMatchFrame;

      if (((boolean)(pmf))) {
        pmf->setJustificationPartialTruth(justification);
      }
    }
  }
}

void PartialMatchFrame::setJustificationPartialTruth(Justification* justification) {
  { PartialMatchFrame* self = this;

    justification->matchScore = self->matchScore;
  }
}

boolean PartialMatchFrame::allowUnboundVariablesP() {
  { PartialMatchFrame* self = this;

    return (false);
  }
}

double PartialMatchFrame::computeAndScore() {
  { PartialMatchFrame* self = this;

    return (NULL_FLOAT);
  }
}

Keyword* PartialMatchFrame::continuePartialAndProof(ControlFrame* frame, Keyword* lastmove) {
  { PartialMatchFrame* self = this;

    lastmove = oldInterpretAndScores(frame, lastmove);
    return (continueAndProof(frame, lastmove));
  }
}

double PartialMatchFrame::computeOrScore() {
  { PartialMatchFrame* self = this;

    return (NULL_FLOAT);
  }
}

Keyword* PartialMatchFrame::continuePartialOrProof(Keyword* lastmove) {
  { PartialMatchFrame* self = this;

    lastmove = oldInterpretOrScores(self->controlFrame, lastmove);
    return (continueOrProof(self->controlFrame, lastmove));
  }
}

double PartialMatchFrame::computeNotScore() {
  { PartialMatchFrame* self = this;

    return (NULL_FLOAT);
  }
}

Keyword* PartialMatchFrame::continuePartialNotProof(Keyword* lastmove) {
  { PartialMatchFrame* self = this;

    return (continueNotProof(self->controlFrame, lastmove));
  }
}

Keyword* PartialMatchFrame::continuePartialFailProof(Keyword* lastmove) {
  { PartialMatchFrame* self = this;

    lastmove = oldInterpretFailScore(self->controlFrame, lastmove);
    return (continueFailProof(self->controlFrame, lastmove));
  }
}

double PartialMatchFrame::computeGoalScore() {
  { PartialMatchFrame* self = this;

    return (NULL_FLOAT);
  }
}

Keyword* PartialMatchFrame::continuePartialStrategiesProofs(Keyword* lastmove) {
  { PartialMatchFrame* self = this;

    return (oldInterpretGoalScores(self->controlFrame, lastmove));
  }
}

Keyword* PartialMatchFrame::continuePartialAntecedentsProof(Keyword* lastmove) {
  { PartialMatchFrame* self = this;

    return (continueAntecedentsProof(self->controlFrame, lastmove));
  }
}

void PartialMatchFrame::setBasePartialMatchTruth(Proposition* prop, Keyword* truth) {
  { PartialMatchFrame* self = this;

    prop = prop;
    if (truth == KWD_PARTIAL_MATCH_TRUE) {
      setDynamicSlotValue(oQUERYITERATORo->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, wrapFloat(1.0), NULL_FLOAT_WRAPPER);
    }
    else if (truth == KWD_PARTIAL_MATCH_FAIL) {
      setDynamicSlotValue(oQUERYITERATORo->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, wrapFloat(0.0), NULL_FLOAT_WRAPPER);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << truth << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

void PartialMatchFrame::recordPartialMatchScore(double score, double weight) {
  { PartialMatchFrame* self = this;

    {
      score = score;
      weight = weight;
    }
  }
}

void PartialMatchFrame::popPartialMatchScore() {
  { PartialMatchFrame* self = this;

  }
}

boolean PartialMatchFrame::earlyPartialMatchAndFailureP() {
  { PartialMatchFrame* self = this;

    return (false);
  }
}

boolean PartialMatchFrame::earlyPartialMatchOrSuccessP() {
  { PartialMatchFrame* self = this;

    return (false);
  }
}

IncrementalPartialMatch* newIncrementalPartialMatch(Keyword* kind, ControlFrame* controlFrame) {
  { IncrementalPartialMatch* self = NULL;

    self = new IncrementalPartialMatch();
    self->kind = kind;
    self->controlFrame = controlFrame;
    self->successP = false;
    self->unboundVars = NIL;
    self->argumentWeights = NIL;
    self->argumentScores = NIL;
    self->dynamicCutoff = NULL_FLOAT;
    self->matchScore = NULL_FLOAT;
    self->maximumScore = 0.0;
    self->totalWeight = NULL_FLOAT;
    self->accumulatedWeight = 0.0;
    self->accumulatedScore = 0.0;
    self->child = NULL;
    self->parent = NULL;
    initializeIncrementalPartialMatch(self);
    return (self);
  }
}

Surrogate* IncrementalPartialMatch::primaryType() {
  { IncrementalPartialMatch* self = this;

    return (SGT_PARTIAL_MATCH_LOGIC_INCREMENTAL_PARTIAL_MATCH);
  }
}

Object* accessIncrementalPartialMatchSlotValue(IncrementalPartialMatch* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PARTIAL_MATCH_LOGIC_ACCUMULATED_SCORE) {
    if (setvalueP) {
      self->accumulatedScore = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->accumulatedScore);
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_ACCUMULATED_WEIGHT) {
    if (setvalueP) {
      self->accumulatedWeight = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->accumulatedWeight);
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_TOTAL_WEIGHT) {
    if (setvalueP) {
      self->totalWeight = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->totalWeight);
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_MAXIMUM_SCORE) {
    if (setvalueP) {
      self->maximumScore = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->maximumScore);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

void initializeIncrementalPartialMatch(IncrementalPartialMatch* self) {
  { ControlFrame* frame = self->controlFrame;
    Keyword* kind = self->kind;

    if (kind == KWD_PARTIAL_MATCH_AND) {
      { double argumentweight = NULL_FLOAT;
        double totalweight = 0.0;
        int nofweightedargs = 0;

        { Proposition* arg = NULL;
          Vector* vector000 = ((Vector*)(frame->proposition->arguments));
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            arg = ((Proposition*)((vector000->theArray)[index000]));
            if ((arg->kind == KWD_PARTIAL_MATCH_AND) &&
                (((FloatWrapper*)(dynamicSlotValue(arg->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_WEIGHT, NULL_FLOAT_WRAPPER)))->wrapperValue == NULL_FLOAT)) {
              nofweightedargs = 0;
              { Proposition* subarg = NULL;
                Vector* vector001 = ((Vector*)(arg->arguments));
                int index001 = 0;
                int length001 = vector001->length();

                for  (; index001 < length001; 
                      index001 = index001 + 1) {
                  subarg = ((Proposition*)((vector001->theArray)[index001]));
                  if ((self->propositionWeight(subarg) == NULL_FLOAT) ||
                      (self->propositionWeight(subarg) > 0.0)) {
                    nofweightedargs = nofweightedargs + 1;
                  }
                }
              }
              argumentweight = 1.0 * nofweightedargs;
              setDynamicSlotValue(arg->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_WEIGHT, wrapFloat(argumentweight), NULL_FLOAT_WRAPPER);
            }
            else {
              argumentweight = self->propositionWeight(arg);
            }
            totalweight = totalweight + argumentweight;
          }
        }
        if (totalweight > 0.0) {
          self->totalWeight = totalweight;
        }
        else {
          self->totalWeight = ((double)(frame->proposition->arguments->length()));
        }
      }
    }
    else {
    }
    linkToParentPartialMatchFrame(self);
  }
}

PartialMatchFrame* IncrementalPartialMatch::createPartialMatchFrame(ControlFrame* frame, Keyword* kind) {
  { IncrementalPartialMatch* self = this;

    return (newIncrementalPartialMatch(kind, frame));
  }
}

double IncrementalPartialMatch::computeDynamicCutoff() {
  { IncrementalPartialMatch* self = this;

    { IncrementalPartialMatch* parent = ((IncrementalPartialMatch*)(self->parent));
      double cutoff = 0.0;

      if (((boolean)(parent))) {
        if (parent->kind == KWD_PARTIAL_MATCH_AND) {
          { double pcutoff = parent->dynamicCutoff;
            double totweight = parent->totalWeight;
            double propweight = self->propositionWeight(self->controlFrame->proposition);
            double weight = ((propweight == NULL_FLOAT) ? 1.0 : (((propweight < 0.1) ? 0.1 : propweight)));
            double maxother = (totweight - parent->accumulatedWeight) - weight;
            double unscaledcutoff = ((pcutoff * totweight) - parent->accumulatedScore) - maxother;

            cutoff = unscaledcutoff / weight;
          }
        }
        else {
          cutoff = parent->dynamicCutoff;
        }
        if ((cutoff < 0.0) &&
            (!self->controlFrame->reversePolarityP)) {
          cutoff = 0.0;
        }
        else if ((cutoff > 0.0) &&
            self->controlFrame->reversePolarityP) {
          cutoff = 0.0;
        }
        else if (!(self->controlFrame->reversePolarityP == parent->controlFrame->reversePolarityP)) {
          cutoff = 0 - cutoff;
        }
      }
      return (cutoff);
    }
  }
}

void IncrementalPartialMatch::clearFramePartialTruth() {
  { IncrementalPartialMatch* self = this;

    self->matchScore = NULL_FLOAT;
    self->maximumScore = 0.0;
  }
}

double IncrementalPartialMatch::truthValueScore(TruthValue* truthvalue) {
  { IncrementalPartialMatch* self = this;

    return (truthvalue->matchScore);
  }
}

double IncrementalPartialMatch::invertMatchScore(double score) {
  { IncrementalPartialMatch* self = this;

    return (0 - score);
  }
}

double IncrementalPartialMatch::propositionWeight(Proposition* proposition) {
  { IncrementalPartialMatch* self = this;

    if (!((boolean)(proposition))) {
      return (1.0);
    }
    else if (coerceWrappedBooleanToBoolean(proposition->variableTypeP_reader())) {
      return (0.0);
    }
    else if (auxiliaryEquivalencePropositionP(proposition)) {
      return (0.0);
    }
    else if (((FloatWrapper*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_WEIGHT, NULL_FLOAT_WRAPPER)))->wrapperValue != NULL_FLOAT) {
      return (((FloatWrapper*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_WEIGHT, NULL_FLOAT_WRAPPER)))->wrapperValue);
    }
    else {
      return (1.0);
    }
  }
}

void IncrementalPartialMatch::pushAndPartialMatchScore(double score, double weight) {
  { IncrementalPartialMatch* self = this;

    if (weight == NULL_FLOAT) {
      weight = 1.0;
    }
    self->argumentScores = cons(wrapFloat(score), self->argumentScores);
    self->argumentWeights = cons(wrapFloat(weight), self->argumentWeights);
    self->accumulatedScore = self->accumulatedScore + (score * weight);
    self->accumulatedWeight = self->accumulatedWeight + weight;
  }
}

void IncrementalPartialMatch::popAndPartialMatchScore() {
  { IncrementalPartialMatch* self = this;

    self->accumulatedScore = self->accumulatedScore - (((FloatWrapper*)(self->argumentScores->value))->wrapperValue * ((FloatWrapper*)(self->argumentWeights->value))->wrapperValue);
    self->accumulatedWeight = self->accumulatedWeight - ((FloatWrapper*)(self->argumentWeights->value))->wrapperValue;
    self->argumentScores = self->argumentScores->rest;
    self->argumentWeights = self->argumentWeights->rest;
  }
}

double IncrementalPartialMatch::computeAndScore() {
  { IncrementalPartialMatch* self = this;

    return (self->accumulatedScore / self->totalWeight);
  }
}

boolean IncrementalPartialMatch::skipAndClauseP(ControlFrame* frame, Cons* forbiddenvars) {
  { IncrementalPartialMatch* self = this;

    { boolean forbiddenvarsP = !(forbiddenvars == NIL);
      boolean failunconstrainedclausesP = oFAIL_UNBOUND_CLAUSESpo;
      Object* conjunct = (frame->proposition->arguments->theArray)[(frame->argumentCursor)];

      { boolean testValue000 = false;

        testValue000 = forbiddenvarsP;
        if (testValue000) {
          { boolean foundP000 = false;

            { Object* var = NULL;
              Cons* iter000 = getUnboundVariables(((Proposition*)(conjunct)));

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                var = iter000->value;
                if (forbiddenvars->memberP(var)) {
                  foundP000 = true;
                  break;
                }
              }
            }
            testValue000 = foundP000;
          }
        }
        if (!testValue000) {
          testValue000 = failunconstrainedclausesP &&
              allVariablesUnboundP(((Proposition*)(conjunct)));
        }
        if (testValue000) {
          { ControlFrame* result = createDownFrame(frame, ((Proposition*)(conjunct)));

            setFrameTruthValue(result, UNKNOWN_TRUTH_VALUE);
            if (!((boolean)(result->partialMatchFrame))) {
              createAndLinkPartialMatchFrame(result, NULL);
            }
            result->partialMatchFrame->setFramePartialTruth(UNKNOWN_TRUTH_VALUE, 0.0, true);
            { PrimitiveStrategy* self000 = newPrimitiveStrategy();

              self000->inferenceRule = KWD_PARTIAL_MATCH_SKIPPED_CONJUNCT;
              self000->strategy = KWD_PARTIAL_MATCH_FAILURE;
              recordGoalJustification(result, self000);
            }
            result->state = KWD_PARTIAL_MATCH_POPPED;
            (((Vector*)(dynamicSlotValue(frame->dynamicSlots, SYM_PARTIAL_MATCH_STELLA_ARGUMENTS, NULL)))->theArray)[(frame->argumentCursor)] = result;
            frame->result = result;
            if (traceKeywordP(KWD_PARTIAL_MATCH_GOAL_TREE)) {
              std::cout << "*** Skipping clause " << conjunct << std::endl;
            }
            return (true);
          }
        }
      }
      return (false);
    }
  }
}

Keyword* IncrementalPartialMatch::continuePartialAndProof(ControlFrame* frame, Keyword* lastmove) {
  { IncrementalPartialMatch* self = this;

    { Cons* forbiddenvars = NIL;

      if (lastmove == KWD_PARTIAL_MATCH_DOWN) {
        self->setDynamicCutoff();
      }
      else if ((lastmove == KWD_PARTIAL_MATCH_UP_TRUE) ||
          (lastmove == KWD_PARTIAL_MATCH_UP_FAIL)) {
        { boolean successP = lastmove == KWD_PARTIAL_MATCH_UP_TRUE;
          Proposition* andproposition = frame->proposition;
          ControlFrame* conjunctframe = frame->result;
          Proposition* conjunct = conjunctframe->proposition;
          double score = conjunctframe->partialMatchFrame->matchScore;
          double weight = self->propositionWeight(conjunct);

          lastmove = KWD_PARTIAL_MATCH_UP_TRUE;
          self->pushAndPartialMatchScore(score, weight);
          if (conjunctframe->partialMatchFrame->cutoffPartialMatchP(traceKeywordP(KWD_PARTIAL_MATCH_GOAL_TREE))) {
            lastmove = KWD_PARTIAL_MATCH_UP_FAIL;
          }
          else if (((conjunctframe->truthValue == FALSE_TRUTH_VALUE) ||
              (conjunctframe->truthValue == DEFAULT_FALSE_TRUTH_VALUE)) &&
              ((conjunctframe->truthValue == TRUE_TRUTH_VALUE) ||
               (conjunctframe->truthValue == FALSE_TRUTH_VALUE))) {
            lastmove = KWD_PARTIAL_MATCH_UP_FAIL;
          }
          else if (coerceWrappedBooleanToBoolean(conjunct->variableTypeP_reader()) &&
              (!successP)) {
            lastmove = KWD_PARTIAL_MATCH_UP_FAIL;
          }
          else {
            if (frame->argumentCursor == (andproposition->arguments->length() - 1)) {
              score = self->computeAndScore();
              if (((!allArgumentsBoundP(andproposition)) &&
                  (!self->allowUnboundVariablesP())) ||
                  self->cutoffPartialMatchP(traceKeywordP(KWD_PARTIAL_MATCH_GOAL_TREE))) {
                lastmove = KWD_PARTIAL_MATCH_UP_FAIL;
              }
              else {
                self->setFramePartialTruth(NULL, score, false);
              }
            }
          }
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      if (lastmove == KWD_PARTIAL_MATCH_UP_FAIL) {
        frame->down = NULL;
      }
      { Keyword* result = continueAndProof(frame, lastmove);

        if (result == KWD_PARTIAL_MATCH_MOVE_DOWN) {
          { int i = NULL_INTEGER;
            int iter000 = frame->argumentCursor;
            int upperBound000 = self->argumentScores->length() - 1;

            for  (; iter000 <= upperBound000; 
                  iter000 = iter000 + 1) {
              i = iter000;
              i = i;
              self->popAndPartialMatchScore();
            }
          }
          if (self->skipAndClauseP(frame, forbiddenvars)) {
            result = self->continuePartialAndProof(frame, KWD_PARTIAL_MATCH_UP_FAIL);
          }
        }
        else if (result == KWD_PARTIAL_MATCH_FAILURE) {
          self->setFramePartialTruth(frame->truthValue, NULL_FLOAT, false);
        }
        else {
        }
        return (result);
      }
    }
  }
}

void IncrementalPartialMatch::pushOrPartialMatchScore(double score, double weight) {
  { IncrementalPartialMatch* self = this;

    if (weight == NULL_FLOAT) {
      weight = 1.0;
    }
    self->pushAndPartialMatchScore(score, weight);
    score = score * weight;
    if (score > self->maximumScore) {
      self->maximumScore = score;
    }
  }
}

void IncrementalPartialMatch::popOrPartialMatchScore() {
  { IncrementalPartialMatch* self = this;

    { double latestscore = ((FloatWrapper*)(self->argumentScores->value))->wrapperValue * ((FloatWrapper*)(self->argumentWeights->value))->wrapperValue;
      double maximumscore = self->maximumScore;

      self->popAndPartialMatchScore();
      if (latestscore == maximumscore) {
        maximumscore = 0.0;
        { FloatWrapper* score = NULL;
          Cons* iter000 = self->argumentScores;
          FloatWrapper* weight = NULL;
          Cons* iter001 = self->argumentWeights;

          for  (; (!(iter000 == NIL)) &&
                    (!(iter001 == NIL)); 
                iter000 = iter000->rest,
                iter001 = iter001->rest) {
            score = ((FloatWrapper*)(iter000->value));
            weight = ((FloatWrapper*)(iter001->value));
            if ((score->wrapperValue * weight->wrapperValue) > maximumscore) {
              maximumscore = score->wrapperValue * weight->wrapperValue;
            }
          }
        }
        self->maximumScore = maximumscore;
      }
    }
  }
}

double IncrementalPartialMatch::computeOrScore() {
  { IncrementalPartialMatch* self = this;

    return (self->maximumScore);
  }
}

Keyword* IncrementalPartialMatch::continuePartialOrProof(Keyword* lastmove) {
  { IncrementalPartialMatch* self = this;

    { ControlFrame* frame = self->controlFrame;
      Proposition* orproposition = frame->proposition;
      Keyword* result = NULL;

      if (lastmove == KWD_PARTIAL_MATCH_DOWN) {
        self->setDynamicCutoff();
      }
      else if ((lastmove == KWD_PARTIAL_MATCH_UP_TRUE) ||
          (lastmove == KWD_PARTIAL_MATCH_UP_FAIL)) {
        { boolean sucessP = lastmove == KWD_PARTIAL_MATCH_UP_TRUE;
          ControlFrame* result = frame->result;
          Vector* disjuncts = orproposition->arguments;
          Proposition* disjunct = ((Proposition*)((disjuncts->theArray)[(frame->argumentCursor)]));
          double score = NULL_FLOAT;

          score = result->partialMatchFrame->matchScore;
          self->pushOrPartialMatchScore(score, self->propositionWeight(disjunct));
          score = self->computeOrScore();
          self->setFramePartialTruth(NULL, score, false);
          if (((!allArgumentsBoundP(disjunct)) &&
              (!self->allowUnboundVariablesP())) ||
              (self->cutoffPartialMatchP(traceKeywordP(KWD_PARTIAL_MATCH_GOAL_TREE)) ||
               ((!sucessP) &&
                (frame->argumentCursor == (disjuncts->length() - 1))))) {
            self->setFramePartialTruth(UNKNOWN_TRUTH_VALUE, 0.0, true);
            lastmove = KWD_PARTIAL_MATCH_UP_FAIL;
          }
          else {
            lastmove = KWD_PARTIAL_MATCH_UP_TRUE;
          }
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      result = continueOrProof(frame, lastmove);
      if (result == KWD_PARTIAL_MATCH_MOVE_DOWN) {
        { int i = NULL_INTEGER;
          int iter000 = frame->argumentCursor;
          int upperBound000 = self->argumentScores->length() - 1;

          for  (; iter000 <= upperBound000; 
                iter000 = iter000 + 1) {
            i = iter000;
            i = i;
            self->popOrPartialMatchScore();
          }
        }
      }
      else if (result == KWD_PARTIAL_MATCH_FAILURE) {
        self->setFramePartialTruth(NULL, self->computeOrScore(), false);
      }
      else {
      }
      return (result);
    }
  }
}

double IncrementalPartialMatch::computeNotScore() {
  { IncrementalPartialMatch* self = this;

    return (self->invertMatchScore(self->accumulatedScore / self->totalWeight));
  }
}

Keyword* IncrementalPartialMatch::continuePartialNotProof(Keyword* lastmove) {
  { IncrementalPartialMatch* self = this;

    { ControlFrame* frame = self->controlFrame;

      if (lastmove == KWD_PARTIAL_MATCH_DOWN) {
        self->setDynamicCutoff();
      }
      else if ((lastmove == KWD_PARTIAL_MATCH_UP_TRUE) ||
          (lastmove == KWD_PARTIAL_MATCH_UP_FAIL)) {
        { ControlFrame* result = frame->result;
          PartialMatchFrame* resultpmf = result->partialMatchFrame;

          resultpmf->matchScore = resultpmf->matchScore * resultpmf->propositionWeight(result->proposition);
          resultpmf->propagateFramePartialTruth(frame);
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      return (continueNotProof(self->controlFrame, lastmove));
    }
  }
}

double IncrementalPartialMatch::computeGoalScore() {
  { IncrementalPartialMatch* self = this;

    { double score = 0.0;

      if (oRULE_COMBINATIONo == KWD_PARTIAL_MATCH_MAX) {
        score = self->maximumScore;
      }
      else if (oRULE_COMBINATIONo == KWD_PARTIAL_MATCH_NOISY_OR) {
        score = probabilisticSumN(self->argumentScores);
      }
      else {
      }
      return (score);
    }
  }
}

Keyword* IncrementalPartialMatch::continuePartialStrategiesProofs(Keyword* lastmove) {
  { IncrementalPartialMatch* self = this;

    { ControlFrame* frame = self->controlFrame;
      Keyword* result = NULL;

      if (lastmove == KWD_PARTIAL_MATCH_DOWN) {
        self->setDynamicCutoff();
      }
      else if (lastmove == KWD_PARTIAL_MATCH_UP_FAIL) {
        if (((boolean)(frame->down))) {
          frame->down = NULL;
        }
      }
      else {
      }
      for (;;) {
        result = continueStrategiesProofs(frame, lastmove);
        if (result == KWD_PARTIAL_MATCH_CONTINUING_SUCCESS) {
          if (self->cutoffPartialMatchP(traceKeywordP(KWD_PARTIAL_MATCH_GOAL_TREE))) {
            lastmove = KWD_PARTIAL_MATCH_DOWN;
          }
          else {
            break;
          }
        }
        else {
          break;
        }
      }
      return (result);
    }
  }
}

Keyword* IncrementalPartialMatch::continuePartialAntecedentsProof(Keyword* lastmove) {
  { IncrementalPartialMatch* self = this;

    { ControlFrame* frame = self->controlFrame;
      Proposition* goal = extractSubgoalOfFrame(frame);
      double score = NULL_FLOAT;
      Keyword* result = NULL;

      if (lastmove == KWD_PARTIAL_MATCH_DOWN) {
        self->setDynamicCutoff();
      }
      else if ((lastmove == KWD_PARTIAL_MATCH_UP_TRUE) ||
          (lastmove == KWD_PARTIAL_MATCH_UP_FAIL)) {
        score = frame->result->partialMatchFrame->matchScore;
        self->pushOrPartialMatchScore(score, self->propositionWeight(((Proposition*)(dynamicSlotValue(frame->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_ANTECEDENTS_RULE, NULL)))));
        score = self->computeGoalScore();
        self->setFramePartialTruth(NULL, score, false);
        if (((!allArgumentsBoundP(goal)) &&
            (!self->allowUnboundVariablesP())) ||
            self->cutoffPartialMatchP(traceKeywordP(KWD_PARTIAL_MATCH_GOAL_TREE))) {
          self->setFramePartialTruth(UNKNOWN_TRUTH_VALUE, 0.0, true);
          lastmove = KWD_PARTIAL_MATCH_UP_FAIL;
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      if ((lastmove == KWD_PARTIAL_MATCH_UP_FAIL) &&
          ((boolean)(frame->down))) {
        frame->down = NULL;
      }
      result = continueAntecedentsProof(frame, lastmove);
      if ((lastmove == KWD_PARTIAL_MATCH_UP_TRUE) &&
          (!((boolean)(frame->truthValue)))) {
        frame->truthValue = UNKNOWN_TRUTH_VALUE;
      }
      return (result);
    }
  }
}

Keyword* IncrementalPartialMatch::continuePartialFailProof(Keyword* lastmove) {
  { IncrementalPartialMatch* self = this;

    { ControlFrame* frame = self->controlFrame;

      if (lastmove == KWD_PARTIAL_MATCH_DOWN) {
        self->setDynamicCutoff();
      }
      else if ((lastmove == KWD_PARTIAL_MATCH_UP_FAIL) ||
          (lastmove == KWD_PARTIAL_MATCH_UP_TRUE)) {
        { ControlFrame* result = frame->result;
          PartialMatchFrame* resultpmf = result->partialMatchFrame;
          double goalscore = resultpmf->matchScore * resultpmf->propositionWeight(result->proposition);
          double failscore = self->invertMatchScore(goalscore);

          if (((boolean)(((Keyword*)(dynamicSlotValue(frame->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_INFERENCE_CUTOFF_REASON, NULL)))))) {
            failscore = self->truthValueScore(UNKNOWN_TRUTH_VALUE);
          }
          else if (goalscore == self->truthValueScore(UNKNOWN_TRUTH_VALUE)) {
            failscore = self->truthValueScore(TRUE_TRUTH_VALUE);
          }
          resultpmf->matchScore = failscore;
          resultpmf->propagateFramePartialTruth(frame);
          lastmove = KWD_PARTIAL_MATCH_UP_FAIL;
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      return (continueFailProof(self->controlFrame, lastmove));
    }
  }
}

NnPartialMatch* newNnPartialMatch(Keyword* kind, ControlFrame* controlFrame) {
  { NnPartialMatch* self = NULL;

    self = new NnPartialMatch();
    self->kind = kind;
    self->controlFrame = controlFrame;
    self->successP = false;
    self->unboundVars = NIL;
    self->argumentWeights = NIL;
    self->argumentScores = NIL;
    self->dynamicCutoff = NULL_FLOAT;
    self->matchScore = NULL_FLOAT;
    self->arity = NULL_INTEGER;
    self->rules = NIL;
    self->maximumScore = 0.0;
    self->accumulatedScore = 0.0;
    self->child = NULL;
    self->parent = NULL;
    self->initializeNnPartialMatch();
    return (self);
  }
}

Surrogate* NnPartialMatch::primaryType() {
  { NnPartialMatch* self = this;

    return (SGT_PARTIAL_MATCH_LOGIC_NN_PARTIAL_MATCH);
  }
}

Object* accessNnPartialMatchSlotValue(NnPartialMatch* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PARTIAL_MATCH_LOGIC_ACCUMULATED_SCORE) {
    if (setvalueP) {
      self->accumulatedScore = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->accumulatedScore);
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_MAXIMUM_SCORE) {
    if (setvalueP) {
      self->maximumScore = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->maximumScore);
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_LOGIC_RULES) {
    if (setvalueP) {
      self->rules = ((Cons*)(value));
    }
    else {
      value = self->rules;
    }
  }
  else if (slotname == SYM_PARTIAL_MATCH_STELLA_ARITY) {
    if (setvalueP) {
      self->arity = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->arity);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

void NnPartialMatch::initializeNnPartialMatch() {
  { NnPartialMatch* self = this;

    { Proposition* prop = self->controlFrame->proposition;

      self->arity = prop->arguments->length();
      { Keyword* testValue000 = self->kind;

        if ((testValue000 == KWD_PARTIAL_MATCH_AND) ||
            (testValue000 == KWD_PARTIAL_MATCH_OR)) {
          if (!((boolean)(((PropositionNeuralNetwork*)(dynamicSlotValue(prop->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_NEURAL_NET, NULL)))))) {
            setDynamicSlotValue(prop->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_NEURAL_NET, createNeuralNetwork(prop), NULL);
          }
        }
        else {
        }
      }
      linkToParentPartialMatchFrame(self);
      self->setDynamicCutoff();
    }
  }
}

PartialMatchFrame* NnPartialMatch::createPartialMatchFrame(ControlFrame* frame, Keyword* kind) {
  { NnPartialMatch* self = this;

    return (newNnPartialMatch(kind, frame));
  }
}

double NnPartialMatch::computeDynamicCutoff() {
  { NnPartialMatch* self = this;

    if (((boolean)(((NnPartialMatch*)(self->parent))))) {
      { Keyword* testValue000 = self->kind;

        if (testValue000 == KWD_PARTIAL_MATCH_ATOMIC_GOAL) {
          return (((NnPartialMatch*)(self->parent))->dynamicCutoff);
        }
        else if ((testValue000 == KWD_PARTIAL_MATCH_AND) ||
            (testValue000 == KWD_PARTIAL_MATCH_OR)) {
          { NnPartialMatch* parent = ((NnPartialMatch*)(self->parent));
            PropositionNeuralNetwork* net = ((PropositionNeuralNetwork*)(dynamicSlotValue(self->controlFrame->proposition->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_NEURAL_NET, NULL)));
            double active = -1.0;

            if (parent->dynamicCutoff > 0.1) {
              { FloatWrapper* input = NULL;
                Vector* vector000 = net->input;
                int index000 = 0;
                int length000 = vector000->length();

                for  (; index000 < length000; 
                      index000 = index000 + 1) {
                  input = ((FloatWrapper*)((vector000->theArray)[index000]));
                  active = active + input->wrapperValue;
                }
              }
              return (active);
            }
          }
        }
        else {
        }
      }
    }
    return (0.0);
  }
}

double NnPartialMatch::propositionWeight(Proposition* proposition) {
  { NnPartialMatch* self = this;

    if (!((boolean)(proposition))) {
      return (1.0);
    }
    else if (coerceWrappedBooleanToBoolean(proposition->variableTypeP_reader())) {
      return (0.0);
    }
    else if (((FloatWrapper*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_WEIGHT, NULL_FLOAT_WRAPPER)))->wrapperValue != NULL_FLOAT) {
      return (((FloatWrapper*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_WEIGHT, NULL_FLOAT_WRAPPER)))->wrapperValue);
    }
    else {
      return (1.0);
    }
  }
}

void NnPartialMatch::setBasePartialMatchTruth(Proposition* prop, Keyword* truth) {
  { NnPartialMatch* self = this;

    if (truth == KWD_PARTIAL_MATCH_TRUE) {
      if (((boolean)(prop))) {
        {
          if (((FloatWrapper*)(dynamicSlotValue(prop->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_WEIGHT, NULL_FLOAT_WRAPPER)))->wrapperValue != NULL_FLOAT) {
            setDynamicSlotValue(prop->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE, wrapFloat(((FloatWrapper*)(dynamicSlotValue(prop->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_WEIGHT, NULL_FLOAT_WRAPPER)))->wrapperValue), NULL_FLOAT_WRAPPER);
          }
          else {
            setDynamicSlotValue(prop->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE, wrapFloat(1.0), NULL_FLOAT_WRAPPER);
          }
          setDynamicSlotValue(oQUERYITERATORo->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, wrapFloat(((FloatWrapper*)(dynamicSlotValue(prop->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue), NULL_FLOAT_WRAPPER);
        }
      }
      else {
        setDynamicSlotValue(oQUERYITERATORo->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, wrapFloat(1.0), NULL_FLOAT_WRAPPER);
      }
    }
    else if (truth == KWD_PARTIAL_MATCH_FAIL) {
      if (((boolean)(prop))) {
        setDynamicSlotValue(prop->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE, wrapFloat(0.0), NULL_FLOAT_WRAPPER);
      }
      setDynamicSlotValue(oQUERYITERATORo->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, wrapFloat(0.0), NULL_FLOAT_WRAPPER);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << truth << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

void NnPartialMatch::setCachePartialTruth(AtomicGoalCache* cache) {
  { NnPartialMatch* self = this;

    cache->matchScore = ((FloatWrapper*)(dynamicSlotValue(oQUERYITERATORo->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue;
  }
}

void NnPartialMatch::setJustificationPartialTruth(Justification* justification) {
  { NnPartialMatch* self = this;

    justification->matchScore = ((FloatWrapper*)(dynamicSlotValue(oQUERYITERATORo->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue;
  }
}

void NnPartialMatch::recordPartialMatchScore(double score, double weight) {
  { NnPartialMatch* self = this;

    if (weight == NULL_FLOAT) {
      weight = 1.0;
    }
    self->argumentScores = cons(wrapFloat(score), self->argumentScores);
    self->argumentWeights = cons(wrapFloat(weight), self->argumentWeights);
    self->accumulatedScore = self->accumulatedScore + (score * weight);
    if (score > self->maximumScore) {
      self->maximumScore = score;
    }
    { ControlFrame* frame = self->controlFrame;

      if ((self->kind == KWD_PARTIAL_MATCH_ATOMIC_GOAL) &&
          (frame->currentStrategy == KWD_PARTIAL_MATCH_FULL_SUBQUERY)) {
        { Proposition* r = ((Proposition*)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_PARTIAL_MATCH_STELLA_ITERATOR, NULL)))->value));
          Proposition* ante = ((Description*)((r->arguments->theArray)[0]))->proposition;

          self->rules = cons(r, self->rules);
          setDynamicSlotValue(ante->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE, wrapFloat(score), NULL_FLOAT_WRAPPER);
        }
      }
    }
  }
}

void NnPartialMatch::popPartialMatchScore() {
  { NnPartialMatch* self = this;

    self->accumulatedScore = self->accumulatedScore - (((FloatWrapper*)(self->argumentScores->value))->wrapperValue * ((FloatWrapper*)(self->argumentWeights->value))->wrapperValue);
    self->argumentScores = self->argumentScores->rest;
    self->argumentWeights = self->argumentWeights->rest;
  }
}

double NnPartialMatch::computeAndScore() {
  { NnPartialMatch* self = this;

    { PropositionNeuralNetwork* net = ((PropositionNeuralNetwork*)(dynamicSlotValue(self->controlFrame->proposition->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_NEURAL_NET, NULL)));

      { FloatWrapper* score = NULL;
        Cons* iter000 = copyConsList(self->argumentScores)->reverse();
        Object* arg = NULL;
        Vector* vector000 = self->controlFrame->proposition->arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; (!(iter000 == NIL)) &&
                  (index000 < length000); 
              iter000 = iter000->rest,
              index000 = index000 + 1) {
          score = ((FloatWrapper*)(iter000->value));
          arg = (vector000->theArray)[index000];
          setDynamicSlotValue(((Proposition*)(arg))->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE, wrapFloat(score->wrapperValue), NULL_FLOAT_WRAPPER);
        }
      }
      if (((boolean)(net))) {
        return (activatePropositionalNeuralNetwork(net));
      }
      return (0.0);
    }
  }
}

double NnPartialMatch::computeOrScore() {
  { NnPartialMatch* self = this;

    { PropositionNeuralNetwork* net = ((PropositionNeuralNetwork*)(dynamicSlotValue(self->controlFrame->proposition->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_NEURAL_NET, NULL)));

      { FloatWrapper* score = NULL;
        Cons* iter000 = copyConsList(self->argumentScores)->reverse();
        Object* arg = NULL;
        Vector* vector000 = self->controlFrame->proposition->arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; (!(iter000 == NIL)) &&
                  (index000 < length000); 
              iter000 = iter000->rest,
              index000 = index000 + 1) {
          score = ((FloatWrapper*)(iter000->value));
          arg = (vector000->theArray)[index000];
          setDynamicSlotValue(((Proposition*)(arg))->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE, wrapFloat(score->wrapperValue), NULL_FLOAT_WRAPPER);
        }
      }
      if (((boolean)(net))) {
        return (activatePropositionalNeuralNetwork(net));
      }
      return (0.0);
    }
  }
}

double NnPartialMatch::computeNotScore() {
  { NnPartialMatch* self = this;

    return (0.0);
  }
}

double NnPartialMatch::computeGoalScore() {
  { NnPartialMatch* self = this;

    { double score = 0.0;

      if (oRULE_COMBINATIONo == KWD_PARTIAL_MATCH_MAX) {
        score = self->maximumScore;
      }
      else if (oRULE_COMBINATIONo == KWD_PARTIAL_MATCH_NOISY_OR) {
        score = probabilisticSumN(self->argumentScores);
      }
      else {
      }
      return (score);
    }
  }
}

double probabilisticSumN(Cons* form) {
  switch (form->length()) {
    case 0: 
      return (0.0);
    case 1: 
      return (((FloatWrapper*)(form->value))->wrapperValue);
    default:
      { double sum = probabilisticSumN(form->rest);

        return (((FloatWrapper*)(form->value))->wrapperValue + sum + (0 - (((FloatWrapper*)(form->value))->wrapperValue * sum)));
      }
      break;
  }
}

double probabilisticSum(double x, double y) {
  return (x + y + (0 - (x * y)));
}

boolean NnPartialMatch::earlyPartialMatchAndFailureP() {
  { NnPartialMatch* self = this;

    return (pruneNnSearchP(self));
  }
}

boolean NnPartialMatch::earlyPartialMatchOrSuccessP() {
  { NnPartialMatch* self = this;

    return (pruneNnSearchP(self));
  }
}

boolean pruneNnSearchP(NnPartialMatch* self) {
  { double maxPossibleActive = self->accumulatedScore + (self->arity - self->argumentScores->length());

    if (oGREEDY_NETWORK_PRUNINGo &&
        ((!(oRULE_COMBINATIONo == KWD_PARTIAL_MATCH_NOISY_OR)) &&
         (maxPossibleActive < self->dynamicCutoff))) {
      {
        if (traceKeywordP(KWD_PARTIAL_MATCH_GOAL_TREE)) {
          std::cout << "*** Cutting off search, cutoff: " << self->dynamicCutoff << "+, Max possible score: " << maxPossibleActive << std::endl;
        }
        return (true);
      }
    }
    else {
      return (false);
    }
  }
}

PartialMatchFrame* makePartialMatchFrame(QueryIterator* query) {
  { GeneralizedSymbol* matchmode = ((GeneralizedSymbol*)(query->options->lookup(KWD_PARTIAL_MATCH_MATCH_MODE)));
    ControlFrame* frame = query->baseControlFrame;
    Keyword* kind = frame->state;

    if (!((boolean)(matchmode))) {
      matchmode = oPARTIAL_MATCH_MODEo;
    }
    if ((matchmode == KWD_PARTIAL_MATCH_BASIC) ||
        (matchmode == KWD_PARTIAL_MATCH_INCREMENTAL)) {
      return (newIncrementalPartialMatch(kind, frame));
    }
    else if ((matchmode == KWD_PARTIAL_MATCH_NN) ||
        (matchmode == KWD_PARTIAL_MATCH_NEURAL_NETWORK)) {
      return (newNnPartialMatch(kind, frame));
    }
    else {
      { Object* clasS = NULL;
        const char* classname = stringConcatenate(matchmode->symbolName, "-PARTIAL-MATCH", 0);

        { Module* temp000 = matchmode->homeModule();

          { Module* module = (((boolean)(temp000)) ? temp000 : oMODULEo);

            { 
              BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
              BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
              clasS = stringLookupClass(classname);
              if (!((boolean)(clasS))) {
                clasS = stringGetObject(classname, NULL);
              }
            }
            if (((boolean)(clasS)) &&
                isaP(clasS, SGT_PARTIAL_MATCH_STELLA_CLASS)) {
              return (((PartialMatchFrame*)(createObject(((Class*)(clasS))->classType, 4, KWD_PARTIAL_MATCH_CONTROL_FRAME, frame, KWD_PARTIAL_MATCH_KIND, kind))));
            }
            else {
              { OutputStringStream* stream000 = newOutputStringStream();

                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  *(stream000->nativeStream) << "PARSING ERROR: " << "Unknown partial match mode: " << "`" << matchmode << "'" << "." << std::endl;
                  helpSignalPropositionError(stream000, KWD_PARTIAL_MATCH_ERROR);
                }
                throw *newParsingError(stream000->theStringReader());
              }
            }
          }
        }
      }
    }
  }
}

void initializePartialQuery(QueryIterator* query) {
  { PartialMatchFrame* partialmatchframe = query->partialMatchStrategy;

    if (!((boolean)(partialmatchframe))) {
      partialmatchframe = makePartialMatchFrame(query);
      query->partialMatchStrategy = partialmatchframe;
    }
    partialmatchframe->initializePartialMatchStrategy(query);
  }
}

void PartialMatchFrame::initializePartialMatchStrategy(QueryIterator* query) {
  { PartialMatchFrame* self = this;

    { FloatWrapper* minimumscore = ((FloatWrapper*)(query->options->lookup(KWD_PARTIAL_MATCH_MINIMUM_SCORE)));
      double epsilon = 0.001;

      query->partialMatchStrategy = self;
      self->dynamicCutoff = (((boolean)(minimumscore)) ? minimumscore->wrapperValue : epsilon);
      setDynamicSlotValue(query->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, wrapFloat(0.0), NULL_FLOAT_WRAPPER);
    }
  }
}

void createAndLinkPartialMatchFrame(ControlFrame* frame, Keyword* kind) {
  { PartialMatchFrame* strategy = oQUERYITERATORo->partialMatchStrategy;
    PartialMatchFrame* partialmatchframe = strategy->createPartialMatchFrame(frame, kind);

    partialmatchframe->kind = kind;
    frame->partialMatchFrame = partialmatchframe;
    partialmatchframe->controlFrame = frame;
  }
}

Cons* getUnboundVariables(Proposition* prop) {
  { Cons* result = NIL;

    { Object* arg = NULL;
      Vector* vector000 = prop->arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        { Object* bind = argumentBoundTo(arg);

          if (!((boolean)(bind))) {
            result = cons(arg, result);
          }
        }
      }
    }
    return (result);
  }
}

boolean allVariablesUnboundP(Proposition* prop) {
  { boolean foundP000 = false;

    { Object* var = NULL;
      Vector* vector000 = prop->arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        var = (vector000->theArray)[index000];
        if (((boolean)(argumentBoundTo(var)))) {
          foundP000 = true;
          break;
        }
      }
    }
    if (foundP000) {
      return (false);
    }
    else {
      return (true);
    }
  }
}

boolean unboundVariablesInFrameP(ControlFrame* frame) {
  return (!(getUnboundVariables(frame->proposition) == NIL));
}

void recordLatestPartialMatchScore(ControlFrame* frame) {
  { Proposition* prop = NULL;
    double score = ((FloatWrapper*)(dynamicSlotValue(oQUERYITERATORo->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue;
    PartialMatchFrame* pframe = frame->partialMatchFrame;

    { Keyword* testValue000 = frame->state;

      if ((testValue000 == KWD_PARTIAL_MATCH_AND) ||
          (testValue000 == KWD_PARTIAL_MATCH_OR)) {
        prop = ((Proposition*)((frame->proposition->arguments->theArray)[(frame->argumentCursor)]));
      }
      else {
        prop = frame->proposition;
      }
    }
    if ((pframe->kind == KWD_PARTIAL_MATCH_AND) &&
        (coerceWrappedBooleanToBoolean(prop->variableTypeP_reader()) &&
         (!pframe->successP))) {
      oAND_MISSED_A_BINDINGo = true;
    }
    if ((pframe->kind == KWD_PARTIAL_MATCH_AND) &&
        ((score == 0.0) &&
         ((prop->kind == KWD_PARTIAL_MATCH_FUNCTION) &&
          (isaP(prop->arguments->last(), SGT_PARTIAL_MATCH_LOGIC_PATTERN_VARIABLE) &&
           (!((boolean)(argumentBoundTo(prop->arguments->last())))))))) {
      pframe->unboundVars = cons(((PatternVariable*)(prop->arguments->last())), pframe->unboundVars);
    }
    pframe->recordPartialMatchScore(((FloatWrapper*)(dynamicSlotValue(oQUERYITERATORo->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue, pframe->propositionWeight(prop));
  }
}

boolean computePartialMatchAndFailureP(ControlFrame* frame) {
  return (frame->partialMatchFrame->earlyPartialMatchAndFailureP());
}

boolean computePartialMatchOrSuccessP(ControlFrame* frame) {
  return (frame->partialMatchFrame->earlyPartialMatchOrSuccessP());
}

boolean computePartialMatchScoreP(ControlFrame* frame) {
  { PartialMatchFrame* partialmatchframe = frame->partialMatchFrame;
    double score = NULL_FLOAT;

    { Keyword* testValue000 = partialmatchframe->kind;

      if (testValue000 == KWD_PARTIAL_MATCH_AND) {
        score = partialmatchframe->computeAndScore();
      }
      else if (testValue000 == KWD_PARTIAL_MATCH_OR) {
        score = partialmatchframe->computeOrScore();
      }
      else if (testValue000 == KWD_PARTIAL_MATCH_ATOMIC_GOAL) {
        score = partialmatchframe->computeGoalScore();
      }
      else {
      }
    }
    setDynamicSlotValue(oQUERYITERATORo->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, wrapFloat(score), NULL_FLOAT_WRAPPER);
    partialmatchframe->matchScore = score;
    setDynamicSlotValue(frame->proposition->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE, wrapFloat(score), NULL_FLOAT_WRAPPER);
    if (unboundVariablesInFrameP(frame)) {
      return (false);
    }
    else {
      return (score > oMINIMUM_SCORE_CUTOFFo);
    }
  }
}

QueryIterator* retrievePartial(Cons* tree) {
  // Partial-match version of `retrieve' (which see) that generates scored
  // partial solutions based on the current partial match strategy.  By supplying
  // `BEST' instead of `ALL', or by adding the option `:SORT-BY :SCORE', the generated
  // solutions will be sorted so that solutions with higher scores come first.
  // Use the `:MATCH-MODE' option to override the global default setting established
  // by `set-partial-match-mode', e.g., use `:MATCH-MODE :NN' to use the neural
  // net partial match mode.  The `:MINIMUM-SCORE' option can be used to only
  // retrieve solutions that have at least the specified minimum match score.
  // By default, `retrieve-partial' does not maximize the match scores of its returned
  // bindings.  To only get maximal scores use `:MAXIMIZE-SCORE? TRUE' (this is not
  // yet implemented - you can use `ask-partial' to maximize scores for individual
  // solutions by hand).
  try {
    return (oMOST_RECENT_QUERYo = callRetrievePartial(tree));
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    return (oMOST_RECENT_QUERYo = NULL);
  }
}

QueryIterator* retrievePartialEvaluatorWrapper(Cons* arguments) {
  return (retrievePartial(arguments));
}

QueryIterator* callRetrievePartial(Object* query) {
  // Callable version of `retrieve-partial' (which see).  Accepts queries
  // specified by a query iterator, or specified as a CONS-list of arguments as they
  // would be supplied to `retrieve-partial'.  Raises LOGIC-EXCEPTIONs in case of
  // illegal queries and logical expressions.
  { QueryIterator* thequery = createRetrieveQuery(query);

    initializePartialQuery(thequery);
    thequery->partialMatchStrategy->retrievePartialSolutions(thequery);
    if (lookupQueryOption(thequery, KWD_PARTIAL_MATCH_SORT_BY) == KWD_PARTIAL_MATCH_SCORE) {
      sortSolutionsByScore(thequery);
    }
    return (thequery);
  }
}

QueryIterator* PartialMatchFrame::retrievePartialSolutions(QueryIterator* query) {
  { PartialMatchFrame* self = this;

    query = query;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Don't know how to retrieve partial solutions for " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

QueryIterator* IncrementalPartialMatch::retrievePartialSolutions(QueryIterator* query) {
  { IncrementalPartialMatch* self = this;

    { BooleanWrapper* maximizescoreP = ((BooleanWrapper*)(lookupQueryOption(query, KWD_PARTIAL_MATCH_MAXIMIZE_SCOREp)));

      if (maximizescoreP == TRUE_WRAPPER) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << ":MAXIMIZE-SCORE? option not yet implemented for partial " << "retrieval in incremental partial match mode - ignoring it." << std::endl;
      }
      { 
        BIND_STELLA_SPECIAL(oQUERYITERATORo, QueryIterator*, query);
        BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
        BIND_STELLA_SPECIAL(oGENERATE_ALL_PROOFSpo, boolean, false);
        BIND_STELLA_SPECIAL(oINFERENCELEVELo, NormalInferenceLevel*, currentInferenceLevel());
        { int i = NULL_INTEGER;
          int iter000 = 1;
          int upperBound000 = lookupHowManySolutions(query);
          boolean unboundedP000 = upperBound000 == NULL_INTEGER;
          QuerySolution* solution = NULL;
          QueryIterator* iter001 = query;

          for  (; (unboundedP000 ||
                    (iter000 <= upperBound000)) &&
                    iter001->nextP(); 
                iter000 = iter000 + 1) {
            i = iter000;
            solution = ((QuerySolution*)(iter001->value));
            solution = solution;
            i = i;
          }
        }
        return (query);
      }
    }
  }
}

void sortSolutionsByScore(QueryIterator* query) {
  query->solutions->sort(((cpp_function_code)(&solutionScoreGreaterThanP)));
}

boolean solutionScoreGreaterThanP(QuerySolution* s1, QuerySolution* s2) {
  return (s1->matchScore > s2->matchScore);
}

double askPartial(Cons* propositionAoptions) {
  // Similar to `ask' (which see), but return the highest partial match score
  // for the supplied proposition instead of a truth value.  If the option
  // :MAXIMIZE-SCORE? is set to FALSE, return after the first partial match score
  // has been generated.
  oMOST_RECENT_QUERYo = NULL;
  try {
    return (callAskPartial(propositionAoptions));
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    oMOST_RECENT_QUERYo = NULL;
    return (NULL_FLOAT);
  }
}

FloatWrapper* askPartialEvaluatorWrapper(Cons* arguments) {
  { double result = askPartial(arguments);

    if (result != NULL_FLOAT) {
      return (wrapFloat(result));
    }
    else {
      return (NULL);
    }
  }
}

double returnPartialTruth(QueryIterator* query, boolean topP) {
  if (!(topP)) {
    query->options->insertAt(KWD_PARTIAL_MATCH_MAXIMIZE_SCOREp, (topP ? TRUE_WRAPPER : FALSE_WRAPPER));
  }
  return (callAskPartial(query));
}

double callAskPartial(Object* query) {
  { QueryIterator* thequery = createAskQuery(query);

    initializePartialQuery(thequery);
    if (!((boolean)(oMOST_RECENT_QUERYo))) {
      oMOST_RECENT_QUERYo = thequery;
    }
    return (thequery->partialMatchStrategy->computePartialTruth(thequery));
  }
}

double PartialMatchFrame::computePartialTruth(QueryIterator* query) {
  { PartialMatchFrame* self = this;

    query = query;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Don't know how to compute partial truth for " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

double IncrementalPartialMatch::computePartialTruth(QueryIterator* query) {
  { IncrementalPartialMatch* self = this;

    { ControlFrame* baseframe = query->baseControlFrame;
      PartialMatchFrame* partialmatchframe = query->partialMatchStrategy;
      FloatWrapper* minimumscore = ((FloatWrapper*)(query->options->lookup(KWD_PARTIAL_MATCH_MINIMUM_SCORE)));
      boolean maximizescoreP = !eqlP(query->options->lookup(KWD_PARTIAL_MATCH_MAXIMIZE_SCOREp), FALSE_WRAPPER);
      double epsilon = 0.001;
      double latestscore = 0.0;
      double highestscore = self->truthValueScore(FALSE_TRUTH_VALUE);
      Justification* bestjustification = NULL;

      if (!((boolean)(partialmatchframe))) {
        partialmatchframe = self;
        query->partialMatchStrategy = self;
      }
      partialmatchframe->dynamicCutoff = (((boolean)(minimumscore)) ? minimumscore->wrapperValue : epsilon);
      { 
        BIND_STELLA_SPECIAL(oQUERYITERATORo, QueryIterator*, query);
        BIND_STELLA_SPECIAL(oGENERATE_ALL_PROOFSpo, boolean, true);
        BIND_STELLA_SPECIAL(oINFERENCELEVELo, NormalInferenceLevel*, currentInferenceLevel());
        BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
        for (;;) {
          if (!(query->nextP())) {
            if (query->solutions->length() == 0) {
              highestscore = partialmatchframe->matchScore;
            }
            break;
          }
          latestscore = partialmatchframe->matchScore;
          if (latestscore <= highestscore) {
            break;
          }
          bestjustification = ((Justification*)(dynamicSlotValue(baseframe->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_JUSTIFICATION, NULL)));
          highestscore = latestscore;
          partialmatchframe->dynamicCutoff = highestscore + epsilon;
          if ((!maximizescoreP) ||
              knownTruthValueP(baseframe->truthValue)) {
            break;
          }
        }
      }
      setDynamicSlotValue(baseframe->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_JUSTIFICATION, bestjustification, NULL);
      return (highestscore);
    }
  }
}

double NnPartialMatch::computePartialTruth(QueryIterator* query) {
  { NnPartialMatch* self = this;

    if (!(oQUERY_OPTIMIZATION_STRATEGYo == KWD_PARTIAL_MATCH_STATIC)) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Switching to static query optimization required by the NN partial matcher" << std::endl << std::endl;
      oQUERY_OPTIMIZATION_STRATEGYo = KWD_PARTIAL_MATCH_STATIC;
    }
    { Proposition* proposition = query->baseControlFrame->proposition;
      PartialMatchFrame* partialmatchframe = query->partialMatchStrategy;
      FloatWrapper* minimumscore = ((FloatWrapper*)(query->options->lookup(KWD_PARTIAL_MATCH_MINIMUM_SCORE)));
      boolean maximizescoreP = !eqlP(query->options->lookup(KWD_PARTIAL_MATCH_MAXIMIZE_SCOREp), FALSE_WRAPPER);
      double epsilon = 0.001;
      double latestscore = 0.0;
      double highestscore = self->truthValueScore(FALSE_TRUTH_VALUE);
      List* scorelist = newList();
      double weight = 0.0;
      List* netlist = NULL;
      List* activationlist = NULL;
      Cons* support = NULL;

      if (!((boolean)(partialmatchframe))) {
        partialmatchframe = self;
        query->partialMatchStrategy = self;
      }
      partialmatchframe->dynamicCutoff = (((boolean)(minimumscore)) ? minimumscore->wrapperValue : epsilon);
      oACTIVATED_NETWORKSo = newList();
      { 
        BIND_STELLA_SPECIAL(oQUERYITERATORo, QueryIterator*, query);
        for (;;) {
          oACTIVATED_NETWORKSo = newList();
          setDynamicSlotValue(query->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, wrapFloat(0.0), NULL_FLOAT_WRAPPER);
          if (!(query->nextP())) {
            break;
          }
          latestscore = ((FloatWrapper*)(dynamicSlotValue(query->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue;
          if (scorelist->memberP(wrapFloat(latestscore))) {
            break;
          }
          if (latestscore > highestscore) {
            support = proposition->support_reader();
            activationlist = newList();
            netlist = oACTIVATED_NETWORKSo;
            { PropositionNeuralNetwork* net = NULL;
              Cons* iter000 = oACTIVATED_NETWORKSo->theConsList;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                net = ((PropositionNeuralNetwork*)(iter000->value));
                { List* propscores = newList();

                  { Object* prop = NULL;
                    Vector* vector000 = net->proposition->arguments;
                    int index000 = 0;
                    int length000 = vector000->length();
                    Cons* collect000 = NULL;

                    for  (; index000 < length000; 
                          index000 = index000 + 1) {
                      prop = (vector000->theArray)[index000];
                      if (!((boolean)(collect000))) {
                        {
                          collect000 = cons(wrapFloat(((FloatWrapper*)(dynamicSlotValue(((Proposition*)(prop))->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue), NIL);
                          if (propscores->theConsList == NIL) {
                            propscores->theConsList = collect000;
                          }
                          else {
                            addConsToEndOfConsList(propscores->theConsList, collect000);
                          }
                        }
                      }
                      else {
                        {
                          collect000->rest = cons(wrapFloat(((FloatWrapper*)(dynamicSlotValue(((Proposition*)(prop))->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue), NIL);
                          collect000 = collect000->rest;
                        }
                      }
                    }
                  }
                  activationlist->push(propscores);
                }
              }
            }
            activationlist = activationlist->reverse();
          }
          weight = ((FloatWrapper*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_WEIGHT, NULL_FLOAT_WRAPPER)))->wrapperValue;
          if (weight != NULL_FLOAT) {
            latestscore = latestscore * weight;
          }
          if (latestscore > highestscore) {
            highestscore = latestscore;
          }
          partialmatchframe->dynamicCutoff = highestscore + epsilon;
          if ((!maximizescoreP) ||
              (highestscore == 1.0)) {
            break;
          }
          scorelist->push(wrapFloat(latestscore));
        }
      }
      if (((boolean)(support))) {
        setDynamicSlotValue(proposition->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_SUPPORT, support, NULL);
        { PropositionNeuralNetwork* net = NULL;
          Cons* iter001 = netlist->reverse()->theConsList;
          List* scorelist = NULL;
          Cons* iter002 = activationlist->reverse()->theConsList;

          for  (; (!(iter001 == NIL)) &&
                    (!(iter002 == NIL)); 
                iter001 = iter001->rest,
                iter002 = iter002->rest) {
            net = ((PropositionNeuralNetwork*)(iter001->value));
            scorelist = ((List*)(iter002->value));
            { Object* prop = NULL;
              Vector* vector001 = net->proposition->arguments;
              int index001 = 0;
              int length001 = vector001->length();
              FloatWrapper* k = NULL;
              Cons* iter003 = scorelist->theConsList;

              for  (; (index001 < length001) &&
                        (!(iter003 == NIL)); 
                    index001 = index001 + 1,
                    iter003 = iter003->rest) {
                prop = (vector001->theArray)[index001];
                k = ((FloatWrapper*)(iter003->value));
                setDynamicSlotValue(((Proposition*)(prop))->dynamicSlots, SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE, wrapFloat(k->wrapperValue), NULL_FLOAT_WRAPPER);
              }
            }
          }
        }
      }
      return (highestscore);
    }
  }
}

boolean nullInstanceP(Object* x) {
  return (objectSurrogate(x) == SGT_PARTIAL_MATCH_PL_KERNEL_KB_NULL);
}

LogicObject* getNullInstance() {
  return (((LogicObject*)(SGT_PARTIAL_MATCH_PL_KERNEL_KB_NULL->surrogateValue)));
}

boolean nullInstancePropositionsExistP() {
  { BacklinksIndex* index = getBacklinksIndex(getNullInstance());

    return (((boolean)(index->predicatePropositionsTable)) ||
        (!index->dependentPropositionsList->emptyP()));
  }
}

Iterator* allMatchingPartialPropositions(Proposition* self) {
  { Cons* pattern = cons(KWD_PARTIAL_MATCH_RELATION, cons(((!((boolean)(NIL))) ? NIL : NIL), cons(((Surrogate*)(self->operatoR)), cons(getNullInstance(), NIL))));

    { SpecializingPropositionsIterator* self000 = newSpecializingPropositionsIterator();

      self000->selectionPattern = pattern;
      self000->propositionCursor = selectPropositions(pattern)->allocateIterator();
      { SpecializingPropositionsIterator* value000 = self000;

        return (value000);
      }
    }
  }
}

boolean partialArgumentsUnifyWithArgumentsP(Proposition* subproposition, Proposition* referenceproposition) {
  { PatternRecord* patternrecord = oQUERYITERATORo->currentPatternRecord;
    int ubstackoffset = patternrecord->topUnbindingStackOffset;
    boolean successP = false;

    { boolean testValue000 = false;

      { boolean alwaysP000 = true;

        { Object* superarg = NULL;
          Vector* vector000 = referenceproposition->arguments;
          int index000 = 0;
          int length000 = vector000->length();
          Object* subarg = NULL;
          Vector* vector001 = subproposition->arguments;
          int index001 = 0;
          int length001 = vector001->length();

          for  (; (index000 < length000) &&
                    (index001 < length001); 
                index000 = index000 + 1,
                index001 = index001 + 1) {
            superarg = (vector000->theArray)[index000];
            subarg = (vector001->theArray)[index001];
            if (!(nullInstanceP(subarg) ||
                (nullInstanceP(superarg) ||
                 bindArgumentToValueP(superarg, valueOf(subarg), false)))) {
              alwaysP000 = false;
              break;
            }
          }
        }
        testValue000 = alwaysP000;
      }
      if (testValue000) {
        testValue000 = referenceproposition->arguments->length() == subproposition->arguments->length();
      }
      successP = testValue000;
    }
    if (!successP) {
      unbindVariablesBeginningAt(patternrecord, ubstackoffset + 1);
    }
    return (successP);
  }
}

Keyword* tryScanPartialPropositionsProof(ControlFrame* frame) {
  { Proposition* proposition = frame->proposition;
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_PARTIAL_MATCH_STELLA_ITERATOR, NULL)));
    Keyword* result = KWD_PARTIAL_MATCH_FAILURE;

    if (!((boolean)(iterator))) {
      iterator = allMatchingPartialPropositions(proposition);
      setDynamicSlotValue(frame->dynamicSlots, SYM_PARTIAL_MATCH_STELLA_ITERATOR, iterator, NULL);
    }
    if (((boolean)(iterator))) {
      while (iterator->nextP()) {
        if (partialArgumentsUnifyWithArgumentsP(((Proposition*)(iterator->value)), proposition)) {
          result = KWD_PARTIAL_MATCH_CONTINUING_SUCCESS;
          break;
        }
      }
    }
    if (!(result == KWD_PARTIAL_MATCH_FAILURE)) {
      { PartialMatchFrame* pmf = frame->partialMatchFrame;
        TruthValue* truthvalue = propositionsIteratorTruthValue(iterator);
        Proposition* matchingprop = ((Proposition*)(iterator->value));
        double score = pmf->computeAssertionScore(matchingprop, truthvalue);

        frame->truthValue = UNKNOWN_TRUTH_VALUE;
        pmf->setFramePartialTruth(UNKNOWN_TRUTH_VALUE, score, true);
      }
    }
    return (result);
  }
}

void helpStartupPartialMatch1() {
  {
    KWD_PARTIAL_MATCH_BASIC = ((Keyword*)(internRigidSymbolWrtModule("BASIC", NULL, 2)));
    KWD_PARTIAL_MATCH_MAX = ((Keyword*)(internRigidSymbolWrtModule("MAX", NULL, 2)));
    SYM_PARTIAL_MATCH_LOGIC_KIND = ((Symbol*)(internRigidSymbolWrtModule("KIND", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_CONTROL_FRAME = ((Symbol*)(internRigidSymbolWrtModule("CONTROL-FRAME", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_PARENT = ((Symbol*)(internRigidSymbolWrtModule("PARENT", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_CHILD = ((Symbol*)(internRigidSymbolWrtModule("CHILD", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE = ((Symbol*)(internRigidSymbolWrtModule("MATCH-SCORE", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_POSITIVE_SCORE = ((Symbol*)(internRigidSymbolWrtModule("POSITIVE-SCORE", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_DYNAMIC_CUTOFF = ((Symbol*)(internRigidSymbolWrtModule("DYNAMIC-CUTOFF", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_ARGUMENT_SCORES = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENT-SCORES", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_ARGUMENT_WEIGHTS = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENT-WEIGHTS", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_UNBOUND_VARS = ((Symbol*)(internRigidSymbolWrtModule("UNBOUND-VARS", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_SUCCESSp = ((Symbol*)(internRigidSymbolWrtModule("SUCCESS?", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_WEIGHT = ((Symbol*)(internRigidSymbolWrtModule("WEIGHT", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_SCORE = ((Symbol*)(internRigidSymbolWrtModule("SCORE", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE = ((Symbol*)(internRigidSymbolWrtModule("LATEST-POSITIVE-SCORE", NULL, 0)));
    KWD_PARTIAL_MATCH_CONTROL_FRAME = ((Keyword*)(internRigidSymbolWrtModule("CONTROL-FRAME", NULL, 2)));
    KWD_PARTIAL_MATCH_KIND = ((Keyword*)(internRigidSymbolWrtModule("KIND", NULL, 2)));
    KWD_PARTIAL_MATCH_DOWN = ((Keyword*)(internRigidSymbolWrtModule("DOWN", NULL, 2)));
    KWD_PARTIAL_MATCH_UP_TRUE = ((Keyword*)(internRigidSymbolWrtModule("UP-TRUE", NULL, 2)));
    KWD_PARTIAL_MATCH_UP_FAIL = ((Keyword*)(internRigidSymbolWrtModule("UP-FAIL", NULL, 2)));
    KWD_PARTIAL_MATCH_TRUE = ((Keyword*)(internRigidSymbolWrtModule("TRUE", NULL, 2)));
    KWD_PARTIAL_MATCH_FAIL = ((Keyword*)(internRigidSymbolWrtModule("FAIL", NULL, 2)));
    SGT_PARTIAL_MATCH_LOGIC_INCREMENTAL_PARTIAL_MATCH = ((Surrogate*)(internRigidSymbolWrtModule("INCREMENTAL-PARTIAL-MATCH", NULL, 1)));
    SYM_PARTIAL_MATCH_LOGIC_ACCUMULATED_SCORE = ((Symbol*)(internRigidSymbolWrtModule("ACCUMULATED-SCORE", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_ACCUMULATED_WEIGHT = ((Symbol*)(internRigidSymbolWrtModule("ACCUMULATED-WEIGHT", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_TOTAL_WEIGHT = ((Symbol*)(internRigidSymbolWrtModule("TOTAL-WEIGHT", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_MAXIMUM_SCORE = ((Symbol*)(internRigidSymbolWrtModule("MAXIMUM-SCORE", NULL, 0)));
    KWD_PARTIAL_MATCH_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    KWD_PARTIAL_MATCH_SKIPPED_CONJUNCT = ((Keyword*)(internRigidSymbolWrtModule("SKIPPED-CONJUNCT", NULL, 2)));
    KWD_PARTIAL_MATCH_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("FAILURE", NULL, 2)));
    KWD_PARTIAL_MATCH_POPPED = ((Keyword*)(internRigidSymbolWrtModule("POPPED", NULL, 2)));
    SYM_PARTIAL_MATCH_STELLA_ARGUMENTS = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENTS", getStellaModule("/STELLA", true), 0)));
    KWD_PARTIAL_MATCH_GOAL_TREE = ((Keyword*)(internRigidSymbolWrtModule("GOAL-TREE", NULL, 2)));
    KWD_PARTIAL_MATCH_MOVE_DOWN = ((Keyword*)(internRigidSymbolWrtModule("MOVE-DOWN", NULL, 2)));
    KWD_PARTIAL_MATCH_NOISY_OR = ((Keyword*)(internRigidSymbolWrtModule("NOISY-OR", NULL, 2)));
    KWD_PARTIAL_MATCH_CONTINUING_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("CONTINUING-SUCCESS", NULL, 2)));
    SYM_PARTIAL_MATCH_LOGIC_ANTECEDENTS_RULE = ((Symbol*)(internRigidSymbolWrtModule("ANTECEDENTS-RULE", NULL, 0)));
    SYM_PARTIAL_MATCH_LOGIC_INFERENCE_CUTOFF_REASON = ((Symbol*)(internRigidSymbolWrtModule("INFERENCE-CUTOFF-REASON", NULL, 0)));
    SGT_PARTIAL_MATCH_LOGIC_NN_PARTIAL_MATCH = ((Surrogate*)(internRigidSymbolWrtModule("NN-PARTIAL-MATCH", NULL, 1)));
    SYM_PARTIAL_MATCH_LOGIC_RULES = ((Symbol*)(internRigidSymbolWrtModule("RULES", NULL, 0)));
    SYM_PARTIAL_MATCH_STELLA_ARITY = ((Symbol*)(internRigidSymbolWrtModule("ARITY", getStellaModule("/STELLA", true), 0)));
    KWD_PARTIAL_MATCH_OR = ((Keyword*)(internRigidSymbolWrtModule("OR", NULL, 2)));
    SYM_PARTIAL_MATCH_LOGIC_NEURAL_NET = ((Symbol*)(internRigidSymbolWrtModule("NEURAL-NET", NULL, 0)));
    KWD_PARTIAL_MATCH_ATOMIC_GOAL = ((Keyword*)(internRigidSymbolWrtModule("ATOMIC-GOAL", NULL, 2)));
    KWD_PARTIAL_MATCH_FULL_SUBQUERY = ((Keyword*)(internRigidSymbolWrtModule("FULL-SUBQUERY", NULL, 2)));
    SYM_PARTIAL_MATCH_STELLA_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR", getStellaModule("/STELLA", true), 0)));
    KWD_PARTIAL_MATCH_MATCH_MODE = ((Keyword*)(internRigidSymbolWrtModule("MATCH-MODE", NULL, 2)));
    KWD_PARTIAL_MATCH_INCREMENTAL = ((Keyword*)(internRigidSymbolWrtModule("INCREMENTAL", NULL, 2)));
    KWD_PARTIAL_MATCH_NN = ((Keyword*)(internRigidSymbolWrtModule("NN", NULL, 2)));
    KWD_PARTIAL_MATCH_NEURAL_NETWORK = ((Keyword*)(internRigidSymbolWrtModule("NEURAL-NETWORK", NULL, 2)));
    SGT_PARTIAL_MATCH_STELLA_CLASS = ((Surrogate*)(internRigidSymbolWrtModule("CLASS", getStellaModule("/STELLA", true), 1)));
    KWD_PARTIAL_MATCH_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    KWD_PARTIAL_MATCH_MINIMUM_SCORE = ((Keyword*)(internRigidSymbolWrtModule("MINIMUM-SCORE", NULL, 2)));
    KWD_PARTIAL_MATCH_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SGT_PARTIAL_MATCH_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", NULL, 1)));
    KWD_PARTIAL_MATCH_SORT_BY = ((Keyword*)(internRigidSymbolWrtModule("SORT-BY", NULL, 2)));
    KWD_PARTIAL_MATCH_SCORE = ((Keyword*)(internRigidSymbolWrtModule("SCORE", NULL, 2)));
    KWD_PARTIAL_MATCH_MAXIMIZE_SCOREp = ((Keyword*)(internRigidSymbolWrtModule("MAXIMIZE-SCORE?", NULL, 2)));
    SYM_PARTIAL_MATCH_LOGIC_JUSTIFICATION = ((Symbol*)(internRigidSymbolWrtModule("JUSTIFICATION", NULL, 0)));
  }
}

void helpStartupPartialMatch2() {
  {
    defineFunctionObject("SET-PARTIAL-MATCH-MODE", "(DEFUN SET-PARTIAL-MATCH-MODE ((K KEYWORD)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setPartialMatchMode)), NULL);
    defineFunctionObject("SET-RULE-COMBINATION", "(DEFUN SET-RULE-COMBINATION ((K KEYWORD)) :COMMAND? TRUE)", ((cpp_function_code)(&setRuleCombination)), NULL);
    defineFunctionObject("SET-GREEDY-NETWORK-PRUNING", "(DEFUN SET-GREEDY-NETWORK-PRUNING ((B BOOLEAN)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setGreedyNetworkPruning)), ((cpp_function_code)(&setGreedyNetworkPruningEvaluatorWrapper)));
    defineFunctionObject("SET-MAXIMUM-SCORE-CUTOFF", "(DEFUN SET-MAXIMUM-SCORE-CUTOFF ((C FLOAT)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setMaximumScoreCutoff)), ((cpp_function_code)(&setMaximumScoreCutoffEvaluatorWrapper)));
    defineFunctionObject("SET-MINIMUM-SCORE-CUTOFF", "(DEFUN SET-MINIMUM-SCORE-CUTOFF ((C FLOAT)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setMinimumScoreCutoff)), ((cpp_function_code)(&setMinimumScoreCutoffEvaluatorWrapper)));
    defineFunctionObject("LINK-TO-PARENT-PARTIAL-MATCH-FRAME", "(DEFUN LINK-TO-PARENT-PARTIAL-MATCH-FRAME ((SELF PARTIAL-MATCH-FRAME)))", ((cpp_function_code)(&linkToParentPartialMatchFrame)), NULL);
    defineMethodObject("(DEFMETHOD (CREATE-PARTIAL-MATCH-FRAME PARTIAL-MATCH-FRAME) ((SELF PARTIAL-MATCH-FRAME) (FRAME CONTROL-FRAME) (KIND KEYWORD)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::createPartialMatchFrame))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-DYNAMIC-CUTOFF PARTIAL-MATCH-SCORE) ((SELF PARTIAL-MATCH-FRAME)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::computeDynamicCutoff))), NULL);
    defineMethodObject("(DEFMETHOD SET-DYNAMIC-CUTOFF ((SELF PARTIAL-MATCH-FRAME)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::setDynamicCutoff))), NULL);
    defineMethodObject("(DEFMETHOD (CUTOFF-PARTIAL-MATCH? BOOLEAN) ((SELF PARTIAL-MATCH-FRAME) (TRACE? BOOLEAN)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::cutoffPartialMatchP))), NULL);
    defineMethodObject("(DEFMETHOD (TRUTH-VALUE-SCORE PARTIAL-MATCH-SCORE) ((SELF PARTIAL-MATCH-FRAME) (TRUTHVALUE TRUTH-VALUE)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::truthValueScore))), NULL);
    defineMethodObject("(DEFMETHOD (INVERT-MATCH-SCORE PARTIAL-MATCH-SCORE) ((SELF PARTIAL-MATCH-FRAME) (SCORE PARTIAL-MATCH-SCORE)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::invertMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD (PROPOSITION-WEIGHT FLOAT) ((SELF PARTIAL-MATCH-FRAME) (PROPOSITION PROPOSITION)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::propositionWeight))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-ASSERTION-SCORE PARTIAL-MATCH-SCORE) ((SELF PARTIAL-MATCH-FRAME) (PROPOSITION PROPOSITION) (TRUTHVALUE TRUTH-VALUE)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::computeAssertionScore))), NULL);
    defineMethodObject("(DEFMETHOD CLEAR-FRAME-PARTIAL-TRUTH ((SELF PARTIAL-MATCH-FRAME)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::clearFramePartialTruth))), NULL);
    defineMethodObject("(DEFMETHOD (DEFINED-FRAME-PARTIAL-TRUTH? BOOLEAN) ((SELF CONTROL-FRAME)) :GLOBALLY-INLINE? TRUE (RETURN (AND (DEFINED? (PARTIAL-MATCH-FRAME SELF)) (DEFINED-FRAME-PARTIAL-TRUTH? (PARTIAL-MATCH-FRAME SELF)))))", wrapMethodCode(((cpp_method_code)(&ControlFrame::definedFramePartialTruthP))), NULL);
    defineMethodObject("(DEFMETHOD (DEFINED-FRAME-PARTIAL-TRUTH? BOOLEAN) ((SELF PARTIAL-MATCH-FRAME)) :GLOBALLY-INLINE? TRUE (RETURN (DEFINED? (MATCH-SCORE SELF))))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::definedFramePartialTruthP))), NULL);
    defineMethodObject("(DEFMETHOD SET-FRAME-PARTIAL-TRUTH ((SELF PARTIAL-MATCH-FRAME) (TRUTHVALUE TRUTH-VALUE) (SCORE PARTIAL-MATCH-SCORE) (IGNOREPOLARITY? BOOLEAN)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::setFramePartialTruth))), NULL);
    defineMethodObject("(DEFMETHOD PROPAGATE-FRAME-PARTIAL-TRUTH ((SOURCE PARTIAL-MATCH-FRAME) (TARGET CONTROL-FRAME)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::propagateFramePartialTruth))), NULL);
    defineMethodObject("(DEFMETHOD TRACE-FRAME-PARTIAL-TRUTH ((SELF PARTIAL-MATCH-FRAME) (LASTMOVE KEYWORD) (STREAM OUTPUT-STREAM)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::traceFramePartialTruth))), NULL);
    defineMethodObject("(DEFMETHOD SET-CACHE-PARTIAL-TRUTH ((SELF CONTROL-FRAME) (CACHE ATOMIC-GOAL-CACHE)))", wrapMethodCode(((cpp_method_code)(&ControlFrame::setCachePartialTruth))), NULL);
    defineMethodObject("(DEFMETHOD SET-CACHE-PARTIAL-TRUTH ((SELF PARTIAL-MATCH-FRAME) (CACHE ATOMIC-GOAL-CACHE)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::setCachePartialTruth))), NULL);
    defineMethodObject("(DEFMETHOD SET-JUSTIFICATION-PARTIAL-TRUTH ((SELF CONTROL-FRAME) (JUSTIFICATION JUSTIFICATION)))", wrapMethodCode(((cpp_method_code)(&ControlFrame::setJustificationPartialTruth))), NULL);
    defineMethodObject("(DEFMETHOD SET-JUSTIFICATION-PARTIAL-TRUTH ((SELF PARTIAL-MATCH-FRAME) (JUSTIFICATION JUSTIFICATION)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::setJustificationPartialTruth))), NULL);
    defineMethodObject("(DEFMETHOD (ALLOW-UNBOUND-VARIABLES? BOOLEAN) ((SELF PARTIAL-MATCH-FRAME)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::allowUnboundVariablesP))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-AND-SCORE PARTIAL-MATCH-SCORE) ((SELF PARTIAL-MATCH-FRAME)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::computeAndScore))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-AND-PROOF KEYWORD) ((SELF PARTIAL-MATCH-FRAME) (FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::continuePartialAndProof))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-OR-SCORE PARTIAL-MATCH-SCORE) ((SELF PARTIAL-MATCH-FRAME)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::computeOrScore))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-OR-PROOF KEYWORD) ((SELF PARTIAL-MATCH-FRAME) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::continuePartialOrProof))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-NOT-SCORE PARTIAL-MATCH-SCORE) ((SELF PARTIAL-MATCH-FRAME)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::computeNotScore))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-NOT-PROOF KEYWORD) ((SELF PARTIAL-MATCH-FRAME) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::continuePartialNotProof))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-FAIL-PROOF KEYWORD) ((SELF PARTIAL-MATCH-FRAME) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::continuePartialFailProof))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-GOAL-SCORE PARTIAL-MATCH-SCORE) ((SELF PARTIAL-MATCH-FRAME)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::computeGoalScore))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-STRATEGIES-PROOFS KEYWORD) ((SELF PARTIAL-MATCH-FRAME) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::continuePartialStrategiesProofs))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-ANTECEDENTS-PROOF KEYWORD) ((SELF PARTIAL-MATCH-FRAME) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::continuePartialAntecedentsProof))), NULL);
    defineMethodObject("(DEFMETHOD SET-BASE-PARTIAL-MATCH-TRUTH ((SELF PARTIAL-MATCH-FRAME) (PROP PROPOSITION) (TRUTH KEYWORD)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::setBasePartialMatchTruth))), NULL);
    defineMethodObject("(DEFMETHOD RECORD-PARTIAL-MATCH-SCORE ((SELF PARTIAL-MATCH-FRAME) (SCORE PARTIAL-MATCH-SCORE) (WEIGHT FLOAT)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::recordPartialMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD POP-PARTIAL-MATCH-SCORE ((SELF PARTIAL-MATCH-FRAME)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::popPartialMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD (EARLY-PARTIAL-MATCH-AND-FAILURE? BOOLEAN) ((SELF PARTIAL-MATCH-FRAME)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::earlyPartialMatchAndFailureP))), NULL);
    defineMethodObject("(DEFMETHOD (EARLY-PARTIAL-MATCH-OR-SUCCESS? BOOLEAN) ((SELF PARTIAL-MATCH-FRAME)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::earlyPartialMatchOrSuccessP))), NULL);
    defineFunctionObject("INITIALIZE-INCREMENTAL-PARTIAL-MATCH", "(DEFUN INITIALIZE-INCREMENTAL-PARTIAL-MATCH ((SELF INCREMENTAL-PARTIAL-MATCH)))", ((cpp_function_code)(&initializeIncrementalPartialMatch)), NULL);
    defineMethodObject("(DEFMETHOD (CREATE-PARTIAL-MATCH-FRAME PARTIAL-MATCH-FRAME) ((SELF INCREMENTAL-PARTIAL-MATCH) (FRAME CONTROL-FRAME) (KIND KEYWORD)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::createPartialMatchFrame))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-DYNAMIC-CUTOFF PARTIAL-MATCH-SCORE) ((SELF INCREMENTAL-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::computeDynamicCutoff))), NULL);
    defineMethodObject("(DEFMETHOD CLEAR-FRAME-PARTIAL-TRUTH ((SELF INCREMENTAL-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::clearFramePartialTruth))), NULL);
    defineMethodObject("(DEFMETHOD (TRUTH-VALUE-SCORE PARTIAL-MATCH-SCORE) ((SELF INCREMENTAL-PARTIAL-MATCH) (TRUTHVALUE TRUTH-VALUE)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::truthValueScore))), NULL);
    defineMethodObject("(DEFMETHOD (INVERT-MATCH-SCORE PARTIAL-MATCH-SCORE) ((SELF INCREMENTAL-PARTIAL-MATCH) (SCORE PARTIAL-MATCH-SCORE)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::invertMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD (PROPOSITION-WEIGHT FLOAT) ((SELF INCREMENTAL-PARTIAL-MATCH) (PROPOSITION PROPOSITION)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::propositionWeight))), NULL);
    defineMethodObject("(DEFMETHOD PUSH-AND-PARTIAL-MATCH-SCORE ((SELF INCREMENTAL-PARTIAL-MATCH) (SCORE PARTIAL-MATCH-SCORE) (WEIGHT FLOAT)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::pushAndPartialMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD POP-AND-PARTIAL-MATCH-SCORE ((SELF INCREMENTAL-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::popAndPartialMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-AND-SCORE PARTIAL-MATCH-SCORE) ((SELF INCREMENTAL-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::computeAndScore))), NULL);
    defineMethodObject("(DEFMETHOD (SKIP-AND-CLAUSE? BOOLEAN) ((SELF INCREMENTAL-PARTIAL-MATCH) (FRAME CONTROL-FRAME) (FORBIDDENVARS (CONS OF PATTERN-VARIABLE))))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::skipAndClauseP))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-AND-PROOF KEYWORD) ((SELF INCREMENTAL-PARTIAL-MATCH) (FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::continuePartialAndProof))), NULL);
    defineMethodObject("(DEFMETHOD PUSH-OR-PARTIAL-MATCH-SCORE ((SELF INCREMENTAL-PARTIAL-MATCH) (SCORE PARTIAL-MATCH-SCORE) (WEIGHT FLOAT)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::pushOrPartialMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD POP-OR-PARTIAL-MATCH-SCORE ((SELF INCREMENTAL-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::popOrPartialMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-OR-SCORE PARTIAL-MATCH-SCORE) ((SELF INCREMENTAL-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::computeOrScore))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-OR-PROOF KEYWORD) ((SELF INCREMENTAL-PARTIAL-MATCH) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::continuePartialOrProof))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-NOT-SCORE PARTIAL-MATCH-SCORE) ((SELF INCREMENTAL-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::computeNotScore))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-NOT-PROOF KEYWORD) ((SELF INCREMENTAL-PARTIAL-MATCH) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::continuePartialNotProof))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-GOAL-SCORE PARTIAL-MATCH-SCORE) ((SELF INCREMENTAL-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::computeGoalScore))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-STRATEGIES-PROOFS KEYWORD) ((SELF INCREMENTAL-PARTIAL-MATCH) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::continuePartialStrategiesProofs))), NULL);
  }
}

void helpStartupPartialMatch3() {
  {
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-ANTECEDENTS-PROOF KEYWORD) ((SELF INCREMENTAL-PARTIAL-MATCH) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::continuePartialAntecedentsProof))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-FAIL-PROOF KEYWORD) ((SELF INCREMENTAL-PARTIAL-MATCH) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::continuePartialFailProof))), NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-NN-PARTIAL-MATCH ((SELF NN-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::initializeNnPartialMatch))), NULL);
    defineMethodObject("(DEFMETHOD (CREATE-PARTIAL-MATCH-FRAME PARTIAL-MATCH-FRAME) ((SELF NN-PARTIAL-MATCH) (FRAME CONTROL-FRAME) (KIND KEYWORD)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::createPartialMatchFrame))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-DYNAMIC-CUTOFF PARTIAL-MATCH-SCORE) ((SELF NN-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::computeDynamicCutoff))), NULL);
    defineMethodObject("(DEFMETHOD (PROPOSITION-WEIGHT FLOAT) ((SELF NN-PARTIAL-MATCH) (PROPOSITION PROPOSITION)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::propositionWeight))), NULL);
    defineMethodObject("(DEFMETHOD SET-BASE-PARTIAL-MATCH-TRUTH ((SELF NN-PARTIAL-MATCH) (PROP PROPOSITION) (TRUTH KEYWORD)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::setBasePartialMatchTruth))), NULL);
    defineMethodObject("(DEFMETHOD SET-CACHE-PARTIAL-TRUTH ((SELF NN-PARTIAL-MATCH) (CACHE ATOMIC-GOAL-CACHE)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::setCachePartialTruth))), NULL);
    defineMethodObject("(DEFMETHOD SET-JUSTIFICATION-PARTIAL-TRUTH ((SELF NN-PARTIAL-MATCH) (JUSTIFICATION JUSTIFICATION)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::setJustificationPartialTruth))), NULL);
    defineMethodObject("(DEFMETHOD RECORD-PARTIAL-MATCH-SCORE ((SELF NN-PARTIAL-MATCH) (SCORE PARTIAL-MATCH-SCORE) (WEIGHT FLOAT)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::recordPartialMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD POP-PARTIAL-MATCH-SCORE ((SELF NN-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::popPartialMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-AND-SCORE PARTIAL-MATCH-SCORE) ((SELF NN-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::computeAndScore))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-OR-SCORE PARTIAL-MATCH-SCORE) ((SELF NN-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::computeOrScore))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-NOT-SCORE PARTIAL-MATCH-SCORE) ((SELF NN-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::computeNotScore))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-GOAL-SCORE PARTIAL-MATCH-SCORE) ((SELF NN-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::computeGoalScore))), NULL);
    defineFunctionObject("PROBABILISTIC-SUM-N", "(DEFUN (PROBABILISTIC-SUM-N FLOAT) ((FORM (CONS OF FLOAT-WRAPPER))))", ((cpp_function_code)(&probabilisticSumN)), NULL);
    defineFunctionObject("PROBABILISTIC-SUM", "(DEFUN (PROBABILISTIC-SUM FLOAT) ((X FLOAT) (Y FLOAT)))", ((cpp_function_code)(&probabilisticSum)), NULL);
    defineMethodObject("(DEFMETHOD (EARLY-PARTIAL-MATCH-AND-FAILURE? BOOLEAN) ((SELF NN-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::earlyPartialMatchAndFailureP))), NULL);
    defineMethodObject("(DEFMETHOD (EARLY-PARTIAL-MATCH-OR-SUCCESS? BOOLEAN) ((SELF NN-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::earlyPartialMatchOrSuccessP))), NULL);
    defineFunctionObject("PRUNE-NN-SEARCH?", "(DEFUN (PRUNE-NN-SEARCH? BOOLEAN) ((SELF NN-PARTIAL-MATCH)))", ((cpp_function_code)(&pruneNnSearchP)), NULL);
    defineFunctionObject("MAKE-PARTIAL-MATCH-FRAME", "(DEFUN (MAKE-PARTIAL-MATCH-FRAME PARTIAL-MATCH-FRAME) ((QUERY QUERY-ITERATOR)))", ((cpp_function_code)(&makePartialMatchFrame)), NULL);
    defineFunctionObject("INITIALIZE-PARTIAL-QUERY", "(DEFUN INITIALIZE-PARTIAL-QUERY ((QUERY QUERY-ITERATOR)))", ((cpp_function_code)(&initializePartialQuery)), NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-PARTIAL-MATCH-STRATEGY ((SELF PARTIAL-MATCH-FRAME) (QUERY QUERY-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::initializePartialMatchStrategy))), NULL);
    defineFunctionObject("CREATE-AND-LINK-PARTIAL-MATCH-FRAME", "(DEFUN CREATE-AND-LINK-PARTIAL-MATCH-FRAME ((FRAME CONTROL-FRAME) (KIND KEYWORD)))", ((cpp_function_code)(&createAndLinkPartialMatchFrame)), NULL);
    defineFunctionObject("GET-UNBOUND-VARIABLES", "(DEFUN (GET-UNBOUND-VARIABLES CONS) ((PROP PROPOSITION)))", ((cpp_function_code)(&getUnboundVariables)), NULL);
    defineFunctionObject("ALL-VARIABLES-UNBOUND?", "(DEFUN (ALL-VARIABLES-UNBOUND? BOOLEAN) ((PROP PROPOSITION)))", ((cpp_function_code)(&allVariablesUnboundP)), NULL);
    defineFunctionObject("UNBOUND-VARIABLES-IN-FRAME?", "(DEFUN (UNBOUND-VARIABLES-IN-FRAME? BOOLEAN) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&unboundVariablesInFrameP)), NULL);
    defineFunctionObject("RECORD-LATEST-PARTIAL-MATCH-SCORE", "(DEFUN RECORD-LATEST-PARTIAL-MATCH-SCORE ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&recordLatestPartialMatchScore)), NULL);
    defineFunctionObject("COMPUTE-PARTIAL-MATCH-AND-FAILURE?", "(DEFUN (COMPUTE-PARTIAL-MATCH-AND-FAILURE? BOOLEAN) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&computePartialMatchAndFailureP)), NULL);
    defineFunctionObject("COMPUTE-PARTIAL-MATCH-OR-SUCCESS?", "(DEFUN (COMPUTE-PARTIAL-MATCH-OR-SUCCESS? BOOLEAN) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&computePartialMatchOrSuccessP)), NULL);
    defineFunctionObject("COMPUTE-PARTIAL-MATCH-SCORE?", "(DEFUN (COMPUTE-PARTIAL-MATCH-SCORE? BOOLEAN) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&computePartialMatchScoreP)), NULL);
    defineFunctionObject("RETRIEVE-PARTIAL", "(DEFUN (RETRIEVE-PARTIAL QUERY-ITERATOR) (|&REST| (TREE PARSE-TREE)) :DOCUMENTATION \"Partial-match version of `retrieve' (which see) that generates scored\npartial solutions based on the current partial match strategy.  By supplying\n`BEST' instead of `ALL', or by adding the option `:SORT-BY :SCORE', the generated\nsolutions will be sorted so that solutions with higher scores come first.\nUse the `:MATCH-MODE' option to override the global default setting established\nby `set-partial-match-mode', e.g., use `:MATCH-MODE :NN' to use the neural\nnet partial match mode.  The `:MINIMUM-SCORE' option can be used to only\nretrieve solutions that have at least the specified minimum match score.\nBy default, `retrieve-partial' does not maximize the match scores of its returned\nbindings.  To only get maximal scores use `:MAXIMIZE-SCORE? TRUE' (this is not\nyet implemented - you can use `ask-partial' to maximize scores for individual\nsolutions by hand).\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&retrievePartial)), ((cpp_function_code)(&retrievePartialEvaluatorWrapper)));
    defineFunctionObject("CALL-RETRIEVE-PARTIAL", "(DEFUN (CALL-RETRIEVE-PARTIAL QUERY-ITERATOR) ((QUERY OBJECT)) :DOCUMENTATION \"Callable version of `retrieve-partial' (which see).  Accepts queries\nspecified by a query iterator, or specified as a CONS-list of arguments as they\nwould be supplied to `retrieve-partial'.  Raises LOGIC-EXCEPTIONs in case of\nillegal queries and logical expressions.\" :PUBLIC? TRUE)", ((cpp_function_code)(&callRetrievePartial)), NULL);
    defineMethodObject("(DEFMETHOD (RETRIEVE-PARTIAL-SOLUTIONS QUERY-ITERATOR) ((SELF PARTIAL-MATCH-FRAME) (QUERY QUERY-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::retrievePartialSolutions))), NULL);
    defineMethodObject("(DEFMETHOD (RETRIEVE-PARTIAL-SOLUTIONS QUERY-ITERATOR) ((SELF INCREMENTAL-PARTIAL-MATCH) (QUERY QUERY-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::retrievePartialSolutions))), NULL);
    defineFunctionObject("SORT-SOLUTIONS-BY-SCORE", "(DEFUN SORT-SOLUTIONS-BY-SCORE ((QUERY QUERY-ITERATOR)))", ((cpp_function_code)(&sortSolutionsByScore)), NULL);
    defineFunctionObject("SOLUTION-SCORE-GREATER-THAN?", "(DEFUN (SOLUTION-SCORE-GREATER-THAN? BOOLEAN) ((S1 QUERY-SOLUTION) (S2 QUERY-SOLUTION)))", ((cpp_function_code)(&solutionScoreGreaterThanP)), NULL);
    defineFunctionObject("ASK-PARTIAL", "(DEFUN (ASK-PARTIAL FLOAT) (|&REST| (|PROPOSITION&OPTIONS| PARSE-TREE)) :DOCUMENTATION \"Similar to `ask' (which see), but return the highest partial match score\nfor the supplied proposition instead of a truth value.  If the option\n:MAXIMIZE-SCORE? is set to FALSE, return after the first partial match score\nhas been generated.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&askPartial)), ((cpp_function_code)(&askPartialEvaluatorWrapper)));
    defineFunctionObject("RETURN-PARTIAL-TRUTH", "(DEFUN (RETURN-PARTIAL-TRUTH FLOAT) ((QUERY QUERY-ITERATOR) (TOP? BOOLEAN)))", ((cpp_function_code)(&returnPartialTruth)), NULL);
    defineFunctionObject("CALL-ASK-PARTIAL", "(DEFUN (CALL-ASK-PARTIAL FLOAT) ((QUERY OBJECT)))", ((cpp_function_code)(&callAskPartial)), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-PARTIAL-TRUTH FLOAT) ((SELF PARTIAL-MATCH-FRAME) (QUERY QUERY-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&PartialMatchFrame::computePartialTruth))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-PARTIAL-TRUTH FLOAT) ((SELF INCREMENTAL-PARTIAL-MATCH) (QUERY QUERY-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&IncrementalPartialMatch::computePartialTruth))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-PARTIAL-TRUTH FLOAT) ((SELF NN-PARTIAL-MATCH) (QUERY QUERY-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&NnPartialMatch::computePartialTruth))), NULL);
    defineFunctionObject("NULL-INSTANCE?", "(DEFUN (NULL-INSTANCE? BOOLEAN) ((X OBJECT)))", ((cpp_function_code)(&nullInstanceP)), NULL);
    defineFunctionObject("GET-NULL-INSTANCE", "(DEFUN (GET-NULL-INSTANCE LOGIC-OBJECT) ())", ((cpp_function_code)(&getNullInstance)), NULL);
    defineFunctionObject("NULL-INSTANCE-PROPOSITIONS-EXIST?", "(DEFUN (NULL-INSTANCE-PROPOSITIONS-EXIST? BOOLEAN) ())", ((cpp_function_code)(&nullInstancePropositionsExistP)), NULL);
    defineFunctionObject("ALL-MATCHING-PARTIAL-PROPOSITIONS", "(DEFUN (ALL-MATCHING-PARTIAL-PROPOSITIONS (ITERATOR OF PROPOSITION)) ((SELF PROPOSITION)))", ((cpp_function_code)(&allMatchingPartialPropositions)), NULL);
    defineFunctionObject("PARTIAL-ARGUMENTS-UNIFY-WITH-ARGUMENTS?", "(DEFUN (PARTIAL-ARGUMENTS-UNIFY-WITH-ARGUMENTS? BOOLEAN) ((SUBPROPOSITION PROPOSITION) (REFERENCEPROPOSITION PROPOSITION)))", ((cpp_function_code)(&partialArgumentsUnifyWithArgumentsP)), NULL);
    defineFunctionObject("TRY-SCAN-PARTIAL-PROPOSITIONS-PROOF", "(DEFUN (TRY-SCAN-PARTIAL-PROPOSITIONS-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryScanPartialPropositionsProof)), NULL);
    defineFunctionObject("STARTUP-PARTIAL-MATCH", "(DEFUN STARTUP-PARTIAL-MATCH () :PUBLIC? TRUE)", ((cpp_function_code)(&startupPartialMatch)), NULL);
    { MethodSlot* function = lookupFunction(SYM_PARTIAL_MATCH_LOGIC_STARTUP_PARTIAL_MATCH);

      setDynamicSlotValue(function->dynamicSlots, SYM_PARTIAL_MATCH_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupPartialMatch"), NULL_STRING_WRAPPER);
    }
  }
}

void startupPartialMatch() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupPartialMatch1();
      KWD_PARTIAL_MATCH_STATIC = ((Keyword*)(internRigidSymbolWrtModule("STATIC", NULL, 2)));
      SYM_PARTIAL_MATCH_LOGIC_SUPPORT = ((Symbol*)(internRigidSymbolWrtModule("SUPPORT", NULL, 0)));
      SGT_PARTIAL_MATCH_PL_KERNEL_KB_NULL = ((Surrogate*)(internRigidSymbolWrtModule("NULL", getStellaModule("/PL-KERNEL-KB", true), 1)));
      KWD_PARTIAL_MATCH_RELATION = ((Keyword*)(internRigidSymbolWrtModule("RELATION", NULL, 2)));
      SYM_PARTIAL_MATCH_LOGIC_STARTUP_PARTIAL_MATCH = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-PARTIAL-MATCH", NULL, 0)));
      SYM_PARTIAL_MATCH_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(4)) {
      oPARTIAL_MATCH_MODEo = KWD_PARTIAL_MATCH_BASIC;
      oRULE_COMBINATIONo = KWD_PARTIAL_MATCH_MAX;
      oPLANABLE_PREDICATESo = NIL;
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("PARTIAL-MATCH-FRAME", "(DEFCLASS PARTIAL-MATCH-FRAME (STANDARD-OBJECT) :DOCUMENTATION \"Abstract class acting as placeholder for system and\nuser-defined partial match implementations.\" :ABSTRACT? TRUE :SLOTS ((KIND :TYPE KEYWORD :REQUIRED? TRUE) (CONTROL-FRAME :TYPE CONTROL-FRAME :REQUIRED? TRUE) (PARENT :TYPE PARTIAL-MATCH-FRAME) (CHILD :TYPE PARTIAL-MATCH-FRAME) (MATCH-SCORE :TYPE PARTIAL-MATCH-SCORE :INITIALLY NULL) (POSITIVE-SCORE :RENAMES MATCH-SCORE :DOCUMENTATION \"For backwards compatibility\") (DYNAMIC-CUTOFF :TYPE FLOAT) (ARGUMENT-SCORES :TYPE (CONS OF FLOAT-WRAPPER) :INITIALLY NIL) (ARGUMENT-WEIGHTS :TYPE (CONS OF FLOAT-WRAPPER) :INITIALLY NIL) (UNBOUND-VARS :TYPE CONS :INITIALLY NIL) (SUCCESS? :TYPE BOOLEAN :INITIALLY FALSE)))");

        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessPartialMatchFrameSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("INCREMENTAL-PARTIAL-MATCH", "(DEFCLASS INCREMENTAL-PARTIAL-MATCH (PARTIAL-MATCH-FRAME) :SLOTS ((PARENT :TYPE INCREMENTAL-PARTIAL-MATCH) (CHILD :TYPE INCREMENTAL-PARTIAL-MATCH) (ACCUMULATED-SCORE :TYPE PARTIAL-MATCH-SCORE :INITIALLY 0.0) (ACCUMULATED-WEIGHT :TYPE FLOAT :INITIALLY 0.0) (TOTAL-WEIGHT :TYPE FLOAT) (MAXIMUM-SCORE :TYPE PARTIAL-MATCH-SCORE :INITIALLY 0.0)) :INITIALIZER INITIALIZE-INCREMENTAL-PARTIAL-MATCH)");

        clasS->classConstructorCode = ((cpp_function_code)(&newIncrementalPartialMatch));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessIncrementalPartialMatchSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("NN-PARTIAL-MATCH", "(DEFCLASS NN-PARTIAL-MATCH (PARTIAL-MATCH-FRAME) :SLOTS ((PARENT :TYPE NN-PARTIAL-MATCH) (CHILD :TYPE NN-PARTIAL-MATCH) (ACCUMULATED-SCORE :TYPE PARTIAL-MATCH-SCORE :INITIALLY 0.0) (MAXIMUM-SCORE :TYPE PARTIAL-MATCH-SCORE :INITIALLY 0.0) (RULES :TYPE (CONS OF PROPOSITION) :INITIALLY NIL) (ARITY :TYPE INTEGER)) :INITIALIZER INITIALIZE-NN-PARTIAL-MATCH)");

        clasS->classConstructorCode = ((cpp_function_code)(&newNnPartialMatch));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessNnPartialMatchSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupPartialMatch2();
      helpStartupPartialMatch3();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFGLOBAL *PARTIAL-MATCH-MODE* KEYWORD :BASIC)", &oPARTIAL_MATCH_MODEo);
      defineGlobalVariableObject("(DEFGLOBAL *GREEDY-NETWORK-PRUNING* BOOLEAN TRUE)", &oGREEDY_NETWORK_PRUNINGo);
      defineGlobalVariableObject("(DEFGLOBAL *RULE-COMBINATION* KEYWORD :MAX)", &oRULE_COMBINATIONo);
      defineGlobalVariableObject("(DEFGLOBAL *PLANNING-MODE* BOOLEAN FALSE)", &oPLANNING_MODEo);
      defineGlobalVariableObject("(DEFGLOBAL *PLANABLE-PREDICATES* CONS NIL)", &oPLANABLE_PREDICATESo);
      defineGlobalVariableObject("(DEFGLOBAL *FAIL-UNBOUND-CLAUSES?* BOOLEAN FALSE)", &oFAIL_UNBOUND_CLAUSESpo);
      defineGlobalVariableObject("(DEFGLOBAL *MINIMUM-SCORE-CUTOFF* PARTIAL-MATCH-SCORE 0.0 :DOCUMENTATION \"Positive scores below *minimum-score-cutoff* get trimmed\nto 0.0 during partial match operations.\")", &oMINIMUM_SCORE_CUTOFFo);
      defineGlobalVariableObject("(DEFGLOBAL *MAXIMUM-SCORE-CUTOFF* PARTIAL-MATCH-SCORE 0.0 :DOCUMENTATION \"Positive scores above *maximum-score-cutoff* get trimmed\nto 1.0 during partial match operations.\")", &oMAXIMUM_SCORE_CUTOFFo);
      defineGlobalVariableObject("(DEFGLOBAL *AND-MISSED-A-BINDING* BOOLEAN FALSE)", &oAND_MISSED_A_BINDINGo);
      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, oPL_KERNEL_MODULEo);
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        createLogicInstance(SGT_PARTIAL_MATCH_PL_KERNEL_KB_NULL, NULL);
      }
    }
  }
}

Keyword* KWD_PARTIAL_MATCH_BASIC = NULL;

Keyword* KWD_PARTIAL_MATCH_MAX = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_KIND = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_CONTROL_FRAME = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_PARENT = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_CHILD = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_MATCH_SCORE = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_POSITIVE_SCORE = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_DYNAMIC_CUTOFF = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_ARGUMENT_SCORES = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_ARGUMENT_WEIGHTS = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_UNBOUND_VARS = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_SUCCESSp = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_WEIGHT = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_SCORE = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_LATEST_POSITIVE_SCORE = NULL;

Keyword* KWD_PARTIAL_MATCH_CONTROL_FRAME = NULL;

Keyword* KWD_PARTIAL_MATCH_KIND = NULL;

Keyword* KWD_PARTIAL_MATCH_DOWN = NULL;

Keyword* KWD_PARTIAL_MATCH_UP_TRUE = NULL;

Keyword* KWD_PARTIAL_MATCH_UP_FAIL = NULL;

Keyword* KWD_PARTIAL_MATCH_TRUE = NULL;

Keyword* KWD_PARTIAL_MATCH_FAIL = NULL;

Surrogate* SGT_PARTIAL_MATCH_LOGIC_INCREMENTAL_PARTIAL_MATCH = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_ACCUMULATED_SCORE = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_ACCUMULATED_WEIGHT = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_TOTAL_WEIGHT = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_MAXIMUM_SCORE = NULL;

Keyword* KWD_PARTIAL_MATCH_AND = NULL;

Keyword* KWD_PARTIAL_MATCH_SKIPPED_CONJUNCT = NULL;

Keyword* KWD_PARTIAL_MATCH_FAILURE = NULL;

Keyword* KWD_PARTIAL_MATCH_POPPED = NULL;

Symbol* SYM_PARTIAL_MATCH_STELLA_ARGUMENTS = NULL;

Keyword* KWD_PARTIAL_MATCH_GOAL_TREE = NULL;

Keyword* KWD_PARTIAL_MATCH_MOVE_DOWN = NULL;

Keyword* KWD_PARTIAL_MATCH_NOISY_OR = NULL;

Keyword* KWD_PARTIAL_MATCH_CONTINUING_SUCCESS = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_ANTECEDENTS_RULE = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_INFERENCE_CUTOFF_REASON = NULL;

Surrogate* SGT_PARTIAL_MATCH_LOGIC_NN_PARTIAL_MATCH = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_RULES = NULL;

Symbol* SYM_PARTIAL_MATCH_STELLA_ARITY = NULL;

Keyword* KWD_PARTIAL_MATCH_OR = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_NEURAL_NET = NULL;

Keyword* KWD_PARTIAL_MATCH_ATOMIC_GOAL = NULL;

Keyword* KWD_PARTIAL_MATCH_FULL_SUBQUERY = NULL;

Symbol* SYM_PARTIAL_MATCH_STELLA_ITERATOR = NULL;

Keyword* KWD_PARTIAL_MATCH_MATCH_MODE = NULL;

Keyword* KWD_PARTIAL_MATCH_INCREMENTAL = NULL;

Keyword* KWD_PARTIAL_MATCH_NN = NULL;

Keyword* KWD_PARTIAL_MATCH_NEURAL_NETWORK = NULL;

Surrogate* SGT_PARTIAL_MATCH_STELLA_CLASS = NULL;

Keyword* KWD_PARTIAL_MATCH_ERROR = NULL;

Keyword* KWD_PARTIAL_MATCH_MINIMUM_SCORE = NULL;

Keyword* KWD_PARTIAL_MATCH_FUNCTION = NULL;

Surrogate* SGT_PARTIAL_MATCH_LOGIC_PATTERN_VARIABLE = NULL;

Keyword* KWD_PARTIAL_MATCH_SORT_BY = NULL;

Keyword* KWD_PARTIAL_MATCH_SCORE = NULL;

Keyword* KWD_PARTIAL_MATCH_MAXIMIZE_SCOREp = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_JUSTIFICATION = NULL;

Keyword* KWD_PARTIAL_MATCH_STATIC = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_SUPPORT = NULL;

Surrogate* SGT_PARTIAL_MATCH_PL_KERNEL_KB_NULL = NULL;

Keyword* KWD_PARTIAL_MATCH_RELATION = NULL;

Symbol* SYM_PARTIAL_MATCH_LOGIC_STARTUP_PARTIAL_MATCH = NULL;

Symbol* SYM_PARTIAL_MATCH_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
