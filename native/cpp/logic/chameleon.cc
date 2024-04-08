//  -*- Mode: C++ -*-

// chameleon.cc

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

// Namespace module for Chameleon relations
Module* oCHAMELEON_MODULEo = NULL;

void ensureChameleonOntology() {
  // Ensure the chameleon.plm ontology file has been loaded (assumes it exists in the current load path).
  if (!((boolean)(oCHAMELEON_MODULEo))) {
    if (!(((boolean)(SGT_CHAMELEON_CHAMELEON_TRUTH_VALUE_RELATION->surrogateValue)))) {
      load("chameleon.plm", NIL);
    }
    oCHAMELEON_MODULEo = getStellaModule("/CHAMELEON", true);
  }
}

Module* getChameleonModule() {
  // Return the namespace module for Chameleon relations
  if (!((boolean)(oCHAMELEON_MODULEo))) {
    ensureChameleonOntology();
  }
  return (oCHAMELEON_MODULEo);
}

boolean chameleonVectorRelationP(Object* x) {
  // Return TRUE if `x' is an explicitly marked vector relation.
  return (testPropertyP(x, SGT_CHAMELEON_CHAMELEON_VECTOR_RELATION));
}

boolean chameleonIgnoredValueRelationP(Object* x) {
  // Return TRUE if `x' is an explicitly marked as ignored or a vector relation
  // that is not also marked as a truth value relation.
  return (testPropertyP(x, SGT_CHAMELEON_CHAMELEON_IGNORED_VALUE_RELATION) ||
      (testPropertyP(x, SGT_CHAMELEON_CHAMELEON_VECTOR_RELATION) &&
       (!testPropertyP(x, SGT_CHAMELEON_CHAMELEON_TRUTH_VALUE_RELATION))));
}

boolean chameleonTruthValueRelationP(Object* x) {
  // Return TRUE if `x' is an explicitly marked truth value relation or
  // otherwise not known to be ignored.
  return (testPropertyP(x, SGT_CHAMELEON_CHAMELEON_TRUTH_VALUE_RELATION) ||
      (!(testPropertyP(x, SGT_CHAMELEON_CHAMELEON_IGNORED_VALUE_RELATION) ||
      (testPropertyP(x, SGT_CHAMELEON_CHAMELEON_VECTOR_RELATION) &&
       (!testPropertyP(x, SGT_CHAMELEON_CHAMELEON_TRUTH_VALUE_RELATION))))));
}

boolean chameleonPrimitiveValueRelationP(Object* x) {
  // Return TRUE if `x' is an explicitly marked primitive value relation.
  return (testPropertyP(x, SGT_CHAMELEON_CHAMELEON_PRIMITIVE_VALUE_RELATION));
}

ChameleonPartialMatch* newChameleonPartialMatch(Keyword* kind, ControlFrame* controlFrame) {
  { ChameleonPartialMatch* self = NULL;

    self = new ChameleonPartialMatch();
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
    self->argumentPropositions = NIL;
    self->argumentJustifications = NIL;
    initializeIncrementalPartialMatch(self);
    return (self);
  }
}

Surrogate* ChameleonPartialMatch::primaryType() {
  { ChameleonPartialMatch* self = this;

    return (SGT_CHAMELEON_LOGIC_CHAMELEON_PARTIAL_MATCH);
  }
}

Object* accessChameleonPartialMatchSlotValue(ChameleonPartialMatch* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_CHAMELEON_LOGIC_ARGUMENT_JUSTIFICATIONS) {
    if (setvalueP) {
      self->argumentJustifications = ((Cons*)(value));
    }
    else {
      value = self->argumentJustifications;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_ARGUMENT_PROPOSITIONS) {
    if (setvalueP) {
      self->argumentPropositions = ((Cons*)(value));
    }
    else {
      value = self->argumentPropositions;
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

// Default weight to use for unknown propositions that don't have a relation-specific value specified.
double oCHAMELEON_DEFAULT_DEFAULT_SCOREo = 0.01;

boolean chameleonPartialMatchModeP() {
  // Return TRUE if a query is computing Chameleon partial matches.
  return ((((boolean)(oQUERYITERATORo)) &&
      ((boolean)(oQUERYITERATORo->partialMatchStrategy))) &&
      isaP(oQUERYITERATORo->partialMatchStrategy, SGT_CHAMELEON_LOGIC_CHAMELEON_PARTIAL_MATCH));
}

PartialMatchFrame* ChameleonPartialMatch::createPartialMatchFrame(ControlFrame* frame, Keyword* kind) {
  { ChameleonPartialMatch* self = this;

    { ChameleonPartialMatch* pmf = newChameleonPartialMatch(kind, frame);
      Proposition* prop = frame->proposition;

      if ((kind == KWD_CHAMELEON_AND) ||
          (kind == KWD_CHAMELEON_OR)) {
        if (!((boolean)(getPropositionNeuralNetwork(prop, false)))) {
          createAndLinkNeuralNetwork(prop);
        }
      }
      else {
      }
      linkToParentPartialMatchFrame(pmf);
      return (pmf);
    }
  }
}

double ChameleonPartialMatch::computeDynamicCutoff() {
  { ChameleonPartialMatch* self = this;

    if (((boolean)(((IncrementalPartialMatch*)(self->parent))))) {
      { Keyword* testValue000 = self->kind;

        if (testValue000 == KWD_CHAMELEON_ATOMIC_GOAL) {
          return (((IncrementalPartialMatch*)(self->parent))->dynamicCutoff);
        }
        else if ((testValue000 == KWD_CHAMELEON_AND) ||
            (testValue000 == KWD_CHAMELEON_OR)) {
        }
        else {
        }
      }
    }
    return (0.0);
  }
}

boolean ChameleonPartialMatch::cutoffPartialMatchP(boolean traceP) {
  { ChameleonPartialMatch* self = this;

    return (PartialMatchFrame::cutoffPartialMatchP(traceP));
  }
}

double ChameleonPartialMatch::truthValueScore(TruthValue* truthvalue) {
  { ChameleonPartialMatch* self = this;

    { double score = truthvalue->matchScore;

      if (score < 0.0) {
        score = score + 1.0;
      }
      return (score);
    }
  }
}

double invertChameleonMatchScore(double score) {
  return (1.0 - score);
}

double ChameleonPartialMatch::invertMatchScore(double score) {
  { ChameleonPartialMatch* self = this;

    return (invertChameleonMatchScore(score));
  }
}

double ChameleonPartialMatch::propositionWeight(Proposition* proposition) {
  { ChameleonPartialMatch* self = this;

    return (IncrementalPartialMatch::propositionWeight(proposition));
  }
}

void ChameleonPartialMatch::pushAndPartialMatchScore(double score, double weight) {
  { ChameleonPartialMatch* self = this;

    { Proposition* argprop = self->controlFrame->result->proposition;

      IncrementalPartialMatch::pushAndPartialMatchScore(score, weight);
      self->argumentPropositions = cons(argprop, self->argumentPropositions);
    }
  }
}

void ChameleonPartialMatch::popAndPartialMatchScore() {
  { ChameleonPartialMatch* self = this;

    IncrementalPartialMatch::popAndPartialMatchScore();
    self->argumentPropositions = self->argumentPropositions->rest;
  }
}

void ChameleonPartialMatch::pushOrPartialMatchScore(double score, double weight) {
  { ChameleonPartialMatch* self = this;

    IncrementalPartialMatch::pushOrPartialMatchScore(score, weight);
  }
}

void ChameleonPartialMatch::popOrPartialMatchScore() {
  { ChameleonPartialMatch* self = this;

    IncrementalPartialMatch::popOrPartialMatchScore();
  }
}

boolean ChameleonPartialMatch::allowUnboundVariablesP() {
  { ChameleonPartialMatch* self = this;

    return (false);
  }
}

double ChameleonPartialMatch::computeAndScore() {
  { ChameleonPartialMatch* self = this;

    { NeuralNetwork* net = getPropositionNeuralNetwork(self->controlFrame->proposition, true);
      Vector* inputs = stella::newVector(net->numberOfInputs());
      Vector* vectorargs = (net->hasVectorArgumentsP() ? stella::newVector(net->numberOfVectorArguments(NULL)) : ((Vector*)(NULL)));
      int index = -1;

      { Proposition* arg = NULL;
        Cons* iter000 = self->argumentPropositions;
        FloatWrapper* score = NULL;
        Cons* iter001 = self->argumentScores;

        for  (; (!(iter000 == NIL)) &&
                  (!(iter001 == NIL)); 
              iter000 = iter000->rest,
              iter001 = iter001->rest) {
          arg = ((Proposition*)(iter000->value));
          score = ((FloatWrapper*)(iter001->value));
          index = net->truthValueArgumentIndex(arg);
          if (index >= 0) {
            (inputs->theArray)[index] = score;
          }
          if (((boolean)(vectorargs))) {
            index = net->vectorArgumentIndex(arg);
            if (index >= 0) {
              (vectorargs->theArray)[index] = (net->getVectorArgumentSpec(arg));
            }
          }
        }
      }
      net->setInputValues(inputs);
      if (((boolean)(vectorargs))) {
        net->setVectorInputValues(vectorargs);
      }
      return (net->forwardPropagateInputs());
    }
  }
}

Keyword* ChameleonPartialMatch::continuePartialAndProof(ControlFrame* frame, Keyword* lastmove) {
  { ChameleonPartialMatch* self = this;

    if ((lastmove == KWD_CHAMELEON_UP_TRUE) ||
        (lastmove == KWD_CHAMELEON_UP_FAIL)) {
      if (falseTruthValueP(frame->result->truthValue) &&
          strictTruthValueP(frame->result->truthValue)) {
        frame->result->truthValue = UNKNOWN_TRUTH_VALUE;
      }
    }
    else {
    }
    return (IncrementalPartialMatch::continuePartialAndProof(frame, lastmove));
  }
}

double ChameleonPartialMatch::computeOrScore() {
  { ChameleonPartialMatch* self = this;

    return (self->computeAndScore());
  }
}

Keyword* ChameleonPartialMatch::continuePartialOrProof(Keyword* lastmove) {
  { ChameleonPartialMatch* self = this;

    { ControlFrame* frame = self->controlFrame;
      Proposition* orproposition = frame->proposition;
      int argcursor = frame->argumentCursor;
      Keyword* result = NULL;

      if (lastmove == KWD_CHAMELEON_DOWN) {
        { int i = NULL_INTEGER;
          int iter000 = argcursor;
          int upperBound000 = self->argumentScores->length() - 1;

          for  (; iter000 <= upperBound000; 
                iter000 = iter000 + 1) {
            i = iter000;
            i = i;
            self->popOrPartialMatchScore();
            if (oRECORD_JUSTIFICATIONSpo) {
              self->argumentJustifications = self->argumentJustifications->rest;
            }
          }
        }
        self->setDynamicCutoff();
      }
      else if ((lastmove == KWD_CHAMELEON_UP_TRUE) ||
          (lastmove == KWD_CHAMELEON_UP_FAIL)) {
        { boolean sucessP = lastmove == KWD_CHAMELEON_UP_TRUE;
          ControlFrame* result = frame->result;
          Vector* disjuncts = orproposition->arguments;
          Proposition* disjunct = ((Proposition*)((disjuncts->theArray)[argcursor]));
          double score = result->partialMatchFrame->matchScore;

          self->pushOrPartialMatchScore(score, self->propositionWeight(disjunct));
          score = self->computeOrScore();
          self->setFramePartialTruth(NULL, score, false);
          if (oRECORD_JUSTIFICATIONSpo) {
            self->argumentJustifications = cons(((Justification*)(dynamicSlotValue(result->dynamicSlots, SYM_CHAMELEON_LOGIC_JUSTIFICATION, NULL))), self->argumentJustifications);
          }
          if ((!allArgumentsBoundP(disjunct)) ||
              self->cutoffPartialMatchP(traceKeywordP(KWD_CHAMELEON_GOAL_TREE))) {
            self->popOrPartialMatchScore();
            if (oRECORD_JUSTIFICATIONSpo) {
              self->argumentJustifications = self->argumentJustifications->rest;
            }
            self->setFramePartialTruth(UNKNOWN_TRUTH_VALUE, 0.0, true);
            lastmove = KWD_CHAMELEON_UP_FAIL;
          }
          else if (sucessP &&
              ((argcursor == (disjuncts->length() - 1)) &&
               allArgumentsBoundP(disjunct))) {
            lastmove = KWD_CHAMELEON_UP_TRUE;
          }
          else {
            lastmove = KWD_CHAMELEON_UP_FAIL;
          }
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      frame->down = NULL;
      result = continueOrProof(frame, lastmove);
      if (self->argumentJustifications->length() >= 2) {
        { Justification* self002 = newJustification();

          self002->inferenceRule = KWD_CHAMELEON_OR_INTRODUCTION;
          self002->antecedents = self->argumentJustifications->reverse();
          recordGoalJustification(frame, self002);
        }
      }
      return (result);
    }
  }
}

double ChameleonPartialMatch::computeNotScore() {
  { ChameleonPartialMatch* self = this;

    return (0.0);
  }
}

Keyword* ChameleonPartialMatch::continuePartialNotProof(Keyword* lastmove) {
  { ChameleonPartialMatch* self = this;

    return (IncrementalPartialMatch::continuePartialNotProof(lastmove));
  }
}

Keyword* ChameleonPartialMatch::continuePartialFailProof(Keyword* lastmove) {
  { ChameleonPartialMatch* self = this;

    return (IncrementalPartialMatch::continuePartialFailProof(lastmove));
  }
}

double ChameleonPartialMatch::computeGoalScore() {
  { ChameleonPartialMatch* self = this;

    return (IncrementalPartialMatch::computeGoalScore());
  }
}

Keyword* ChameleonPartialMatch::continuePartialStrategiesProofs(Keyword* lastmove) {
  { ChameleonPartialMatch* self = this;

    { ControlFrame* frame = self->controlFrame;
      Keyword* result = IncrementalPartialMatch::continuePartialStrategiesProofs(lastmove);

      if ((result == KWD_CHAMELEON_FAILURE) &&
          ((!((frame->truthValue == UNKNOWN_TRUTH_VALUE) ||
          (!((boolean)(frame->truthValue))))) &&
           (!(frame->reversePolarityP == ((frame->truthValue == FALSE_TRUTH_VALUE) ||
           (frame->truthValue == DEFAULT_FALSE_TRUTH_VALUE)))))) {
        if (KWD_CHAMELEON_OTHER == KWD_CHAMELEON_VARIANT1) {
          setFrameTruthValue(frame, UNKNOWN_TRUTH_VALUE);
          if (!((self->matchScore == 0.0) ||
              (self->matchScore == 1.0))) {
            result = KWD_CHAMELEON_FINAL_SUCCESS;
          }
          if (oRECORD_JUSTIFICATIONSpo &&
              ((result == KWD_CHAMELEON_FINAL_SUCCESS) &&
               (!((boolean)(((Justification*)(dynamicSlotValue(frame->dynamicSlots, SYM_CHAMELEON_LOGIC_JUSTIFICATION, NULL)))))))) {
            recordPrimitiveJustification(frame, KWD_CHAMELEON_UP_TRUE);
          }
        }
        else if (KWD_CHAMELEON_OTHER == KWD_CHAMELEON_VARIANT2) {
          setFrameTruthValue(frame, UNKNOWN_TRUTH_VALUE);
          self->setFramePartialTruth(UNKNOWN_TRUTH_VALUE, NULL_FLOAT, true);
        }
        else {
        }
      }
      return (result);
    }
  }
}

Keyword* ChameleonPartialMatch::continuePartialAntecedentsProof(Keyword* lastmove) {
  { ChameleonPartialMatch* self = this;

    { ControlFrame* frame = self->controlFrame;
      Proposition* goal = extractSubgoalOfFrame(frame);
      double score = NULL_FLOAT;
      Keyword* result = NULL;

      if (lastmove == KWD_CHAMELEON_DOWN) {
        self->setDynamicCutoff();
      }
      else if ((lastmove == KWD_CHAMELEON_UP_TRUE) ||
          (lastmove == KWD_CHAMELEON_UP_FAIL)) {
        { ControlFrame* goalframe = frame->result;

          score = goalframe->partialMatchFrame->matchScore;
          self->pushOrPartialMatchScore(score, self->propositionWeight(((Proposition*)(dynamicSlotValue(frame->dynamicSlots, SYM_CHAMELEON_LOGIC_ANTECEDENTS_RULE, NULL)))));
          score = self->computeGoalScore();
          self->setFramePartialTruth(NULL, score, false);
          if (oRECORD_JUSTIFICATIONSpo &&
              ((boolean)(((Justification*)(dynamicSlotValue(goalframe->dynamicSlots, SYM_CHAMELEON_LOGIC_JUSTIFICATION, NULL)))))) {
            recordModusPonensJustification(frame, KWD_CHAMELEON_UP_TRUE);
            self->argumentJustifications = cons(((Justification*)(dynamicSlotValue(frame->dynamicSlots, SYM_CHAMELEON_LOGIC_JUSTIFICATION, NULL))), self->argumentJustifications);
          }
          if ((!allArgumentsBoundP(goal)) ||
              self->cutoffPartialMatchP(traceKeywordP(KWD_CHAMELEON_GOAL_TREE))) {
            self->popOrPartialMatchScore();
            if (oRECORD_JUSTIFICATIONSpo) {
              self->argumentJustifications = self->argumentJustifications->rest;
            }
            self->setFramePartialTruth(UNKNOWN_TRUTH_VALUE, 0.0, true);
            lastmove = KWD_CHAMELEON_UP_FAIL;
          }
          else if ((!hasMoreAntecedentsP(frame)) &&
              (allArgumentsBoundP(goal) &&
               (self->argumentJustifications->length() > 0))) {
            lastmove = KWD_CHAMELEON_UP_TRUE;
          }
          else {
            lastmove = KWD_CHAMELEON_UP_FAIL;
          }
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      frame->down = NULL;
      result = continueAntecedentsProof(frame, lastmove);
      if (lastmove == KWD_CHAMELEON_UP_TRUE) {
        if (!((boolean)(frame->truthValue))) {
          frame->truthValue = UNKNOWN_TRUTH_VALUE;
        }
        switch (self->argumentJustifications->length()) {
          case 0: 
            break;
          case 1: 
            setDynamicSlotValue(frame->dynamicSlots, SYM_CHAMELEON_LOGIC_JUSTIFICATION, ((Justification*)(self->argumentJustifications->value)), NULL);
            break;
          default:
            { Justification* self002 = newJustification();

              self002->inferenceRule = KWD_CHAMELEON_MULTIPLE_PROOFS;
              self002->antecedents = self->argumentJustifications->reverse();
              recordGoalJustification(frame, self002);
            }
            break;
        }
      }
      return (result);
    }
  }
}

double ChameleonPartialMatch::computePartialTruth(QueryIterator* query) {
  { ChameleonPartialMatch* self = this;

    { ControlFrame* baseframe = query->baseControlFrame;
      PartialMatchFrame* partialmatchframe = query->partialMatchStrategy;
      FloatWrapper* minimumscore = ((FloatWrapper*)(query->options->lookup(KWD_CHAMELEON_MINIMUM_SCORE)));
      boolean maximizescoreP = !eqlP(query->options->lookup(KWD_CHAMELEON_MAXIMIZE_SCOREp), FALSE_WRAPPER);
      Object* recordjustificationsP = lookupDeferredQueryOption(query, KWD_CHAMELEON_RECORD_JUSTIFICATIONSp, SGT_CHAMELEON_STELLA_BOOLEAN);
      double epsilon = 0.001;
      NormalInferenceLevel* initialinferencelevel = currentInferenceLevel();
      double latestscore = 0.0;
      double bestscore = 0.0;
      Justification* bestproof = NULL;

      if (!((boolean)(partialmatchframe))) {
        partialmatchframe = self;
        query->partialMatchStrategy = self;
      }
      partialmatchframe->dynamicCutoff = (((boolean)(minimumscore)) ? minimumscore->wrapperValue : epsilon);
      { 
        BIND_STELLA_SPECIAL(oQUERYITERATORo, QueryIterator*, query);
        BIND_STELLA_SPECIAL(oGENERATE_ALL_PROOFSpo, boolean, true);
        BIND_STELLA_SPECIAL(oRECORD_JUSTIFICATIONSpo, boolean, oRECORD_JUSTIFICATIONSpo);
        BIND_STELLA_SPECIAL(oINFERENCELEVELo, NormalInferenceLevel*, initialinferencelevel);
        BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
        if (eqlP(recordjustificationsP, TRUE_WRAPPER)) {
          oRECORD_JUSTIFICATIONSpo = true;
        }
        oRULE_COMBINATIONo = KWD_CHAMELEON_NOISY_OR;
        for (;;) {
          if (!(query->nextP())) {
            if (query->solutions->length() == 0) {
              bestscore = partialmatchframe->matchScore;
            }
            break;
          }
          if (partialmatchframe->cutoffPartialMatchP(false)) {
            break;
          }
          latestscore = partialmatchframe->matchScore;
          if (latestscore > bestscore) {
            bestscore = latestscore;
            bestproof = ((Justification*)(dynamicSlotValue(baseframe->dynamicSlots, SYM_CHAMELEON_LOGIC_JUSTIFICATION, NULL)));
            partialmatchframe->dynamicCutoff = bestscore + epsilon;
          }
          if (!maximizescoreP) {
            break;
          }
          oINFERENCELEVELo = initialinferencelevel;
        }
        setDynamicSlotValue(baseframe->dynamicSlots, SYM_CHAMELEON_LOGIC_JUSTIFICATION, bestproof, NULL);
        partialmatchframe->matchScore = bestscore;
        return (bestscore);
      }
    }
  }
}

KeyValueMap* oALL_NEURAL_NETWORKSo = NULL;

void registerNeuralNetwork(NeuralNetwork* self) {
  // Register the network `self' on the global networks list (assumes `self' has been linked).
  { IntegerWrapper* hashcode = wrapInteger(propositionHashIndex(self->getNeuralNetworkProposition(), NULL, true));
    Cons* bucket = ((Cons*)(oALL_NEURAL_NETWORKSo->lookup(hashcode)));

    if (!((boolean)(bucket))) {
      oALL_NEURAL_NETWORKSo->insertAt(hashcode, cons(self, NIL));
    }
    else {
      bucket->rest = cons(((NeuralNetwork*)(bucket->value)), bucket->rest);
      bucket->firstSetter(self);
    }
  }
}

void unregisterNeuralNetwork(NeuralNetwork* self) {
  // Unregister the network `self' on the global networks list.
  { IntegerWrapper* hashcode = wrapInteger(propositionHashIndex(self->getNeuralNetworkProposition(), NULL, true));
    Cons* bucket = ((Cons*)(oALL_NEURAL_NETWORKSo->lookup(hashcode)));

    if (!((boolean)(bucket))) {
    }
    else if (bucket->rest == NIL) {
      oALL_NEURAL_NETWORKSo->removeAt(hashcode);
    }
    else {
      bucket->remove(self);
    }
  }
}

NeuralNetwork* lookupPropositionNeuralNetwork(Proposition* prop) {
  // Lookup the neural network for `prop' in the global networks list.
  { IntegerWrapper* hashcode = wrapInteger(propositionHashIndex(prop, NULL, true));
    Cons* bucket = ((Cons*)(oALL_NEURAL_NETWORKSo->lookup(hashcode)));

    if (((boolean)(bucket))) {
      { NeuralNetwork* net = NULL;
        Cons* iter000 = bucket;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          net = ((NeuralNetwork*)(iter000->value));
          if (equivalentPropositionsP(prop, net->getNeuralNetworkProposition(), NULL) &&
              visibleFromP(net->getNeuralNetworkProposition()->homeContext, oMODULEo)) {
            return (net);
          }
        }
      }
    }
    return (NULL);
  }
}

void deleteNeuralNetworks() {
  // Eliminate all neural networks and remove any connections
  // to propositions and training examples.
  { Cons* bucket = NULL;
    DictionaryIterator* iter000 = ((DictionaryIterator*)(oALL_NEURAL_NETWORKSo->allocateIterator()));

    for (; iter000->nextP(); ) {
      bucket = ((Cons*)(iter000->value));
      { NeuralNetwork* net = NULL;
        Cons* iter001 = bucket;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          net = ((NeuralNetwork*)(iter001->value));
          net->deleteNeuralNetwork();
        }
      }
    }
  }
  incrementNowTimestamp();
  oALL_NEURAL_NETWORKSo->clear();
  { PropositionNeuralNetwork* net = NULL;
    Cons* iter002 = oMASTER_NEURAL_NETWORK_LISTo->theConsList;

    for (; !(iter002 == NIL); iter002 = iter002->rest) {
      net = ((PropositionNeuralNetwork*)(iter002->value));
      net->deleteNeuralNetwork();
    }
  }
  deleteAllNeuralNetworks();
}

void randomizeNeuralNetworks() {
  // Undo all training and randomize weights in all neural networks.
  { Cons* bucket = NULL;
    DictionaryIterator* iter000 = ((DictionaryIterator*)(oALL_NEURAL_NETWORKSo->allocateIterator()));

    for (; iter000->nextP(); ) {
      bucket = ((Cons*)(iter000->value));
      { NeuralNetwork* net = NULL;
        Cons* iter001 = bucket;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          net = ((NeuralNetwork*)(iter001->value));
          net->randomizeNetworkWeights();
        }
      }
    }
  }
}

Keyword* oCHAMELEON_NEURAL_NETWORK_IMPLEMENTATIONo = NULL;

void createAndLinkNeuralNetwork(Proposition* prop) {
  { NeuralNetwork* net = NULL;

    if (oCHAMELEON_NEURAL_NETWORK_IMPLEMENTATIONo == KWD_CHAMELEON_ORIGINAL) {
      setDynamicSlotValue(prop->dynamicSlots, SYM_CHAMELEON_LOGIC_NEURAL_NET, createNeuralNetwork(prop), NULL);
      return;
    }
    else if (oCHAMELEON_NEURAL_NETWORK_IMPLEMENTATIONo == KWD_CHAMELEON_PROPOSITION) {
      net = newPropositionNeuralNetwork();
    }
    else if (oCHAMELEON_NEURAL_NETWORK_IMPLEMENTATIONo == KWD_CHAMELEON_CHAMELEON) {
      ensureChameleonOntology();
      net = newChameleonNeuralNetwork();
    }
    else if (oCHAMELEON_NEURAL_NETWORK_IMPLEMENTATIONo == KWD_CHAMELEON_CHAMELEON_BATCH) {
      ensureChameleonOntology();
      net = newChameleonBatchNeuralNetwork();
    }
    else if (oCHAMELEON_NEURAL_NETWORK_IMPLEMENTATIONo == KWD_CHAMELEON_TENSORFLOW) {
      ensureChameleonOntology();
      if (!(tensorflowBackendAvailableP())) {
        throw *newStellaException("create-and-link-neural-network: TensorFlow backend is not available");
      }
      net = newTensorflowNeuralNetwork();
    }
    else if (oCHAMELEON_NEURAL_NETWORK_IMPLEMENTATIONo == KWD_CHAMELEON_TENSORFLOW_BATCH) {
      ensureChameleonOntology();
      if (!(tensorflowBackendAvailableP())) {
        throw *newStellaException("create-and-link-neural-network: TensorFlow backend is not available");
      }
      net = newTensorflowBatchNeuralNetwork();
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oCHAMELEON_NEURAL_NETWORK_IMPLEMENTATIONo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    net->buildPropositionNetwork(prop);
    registerNeuralNetwork(net);
  }
}

NeuralNetwork* getPropositionNeuralNetwork(Proposition* prop, boolean errorP) {
  // Return the neural network associated with `prop'.  If `error?', raise an
  // exception if it cannot be found, otherwise, simply return NULL.
  { NeuralNetwork* net = ((NeuralNetwork*)(dynamicSlotValue(prop->dynamicSlots, SYM_CHAMELEON_LOGIC_NEURAL_NET, NULL)));

    if (!((boolean)(net))) {
      net = lookupPropositionNeuralNetwork(prop);
      if (((boolean)(net))) {
        setDynamicSlotValue(prop->dynamicSlots, SYM_CHAMELEON_LOGIC_NEURAL_NET, net, NULL);
      }
      else if (errorP) {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Missing neural network for proposition: " << "`" << prop << "'";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    return (net);
  }
}

NeuralNetwork* getJustificationNeuralNetwork(Justification* just) {
  // Return the neural network associated with an :AND or :OR justification.
  // Raise an error if the associated proposition is not linked to a neural network.
  return (getPropositionNeuralNetwork(just->proposition, true));
}

void NeuralNetwork::linkNeuralNetwork(Proposition* prop) {
  // Link the network `self' to its associated proposition `prop'.
  { NeuralNetwork* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "link-neural-network: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NeuralNetwork::unlinkNeuralNetwork() {
  // Unlink the network `self' from its associated proposition.
  { NeuralNetwork* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "unlink-neural-network: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Proposition* NeuralNetwork::getNeuralNetworkProposition() {
  // Return the proposition linked to `self'.
  { NeuralNetwork* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "get-proposition: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NeuralNetwork::deleteNeuralNetwork() {
  // Unlink the network `self' from its associated proposition and mark it as deleted.
  { NeuralNetwork* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "delete-neural-network: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

boolean NeuralNetwork::deletedP() {
  // Return trun if `self' has been deleted.
  { NeuralNetwork* self = this;

    return (false);
  }
}

void NeuralNetwork::allocateNetworkArrays(int numIn, int numHidden, int numOut) {
  // Allocates array space for a neural network with given number of input, hidden and output units.
  { NeuralNetwork* self = this;

    {
      numIn = numIn;
      numHidden = numHidden;
      numOut = numOut;
    }
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "allocate-arrays: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NeuralNetwork::randomizeNetworkWeights() {
  // Randomize the weights of the neural network `self'.
  { NeuralNetwork* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "randomize-network-weights: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NeuralNetwork::buildPropositionNetwork(Proposition* prop) {
  // Build a neural network for the proposition `prop' and link them.  This builds
  // a two-layer perceptron network whose input nodes are activated by the truth of `prop's arguments
  // and whose output node computes the truth of `prop'.
  { NeuralNetwork* self = this;

    prop = prop;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "build-proposition-network: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

int NeuralNetwork::numberOfInputs() {
  // Return the number of input values expected by `self' (ignores bias unit).
  { NeuralNetwork* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "number-of-inputs: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

int helpComputeArgumentIndex(NeuralNetwork* self, Proposition* arg, Keyword* kind) {
  // Memoizable helper function for `truth-value-argument-index' and friends.
  { Proposition* proposition = self->getNeuralNetworkProposition();
    int pos = -1;
    boolean matchP = false;
    KeyValueMap* mapping = NULL;

    if ((arg->kind == KWD_CHAMELEON_NOT) ||
        (arg->kind == KWD_CHAMELEON_FAIL)) {
      arg = ((Proposition*)((arg->arguments->theArray)[0]));
    }
    { Object* proparg = NULL;
      Vector* vector000 = proposition->arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        proparg = (vector000->theArray)[index000];
        if (subtypeOfP(safePrimaryType(proparg), SGT_CHAMELEON_LOGIC_PROPOSITION)) {
          { Object* proparg000 = proparg;
            Proposition* proparg = ((Proposition*)(proparg000));

            if ((proparg->kind == KWD_CHAMELEON_NOT) ||
                (proparg->kind == KWD_CHAMELEON_FAIL)) {
              proparg = ((Proposition*)((proparg->arguments->theArray)[0]));
            }
            if (((kind == KWD_CHAMELEON_TRUTH_VALUE) &&
                self->truthValueArgumentP(proparg)) ||
                (((kind == KWD_CHAMELEON_IGNORED_VALUE) &&
                self->ignoredValueArgumentP(proparg)) ||
                 ((kind == KWD_CHAMELEON_VECTOR) &&
                  self->vectorArgumentP(proparg)))) {
              pos = pos + 1;
              matchP = true;
            }
            else {
              matchP = false;
            }
            if (proparg == arg) {
              return ((matchP ? pos : -1));
            }
            else if (proparg->operatoR == arg->operatoR) {
              { 
                BIND_STELLA_SPECIAL(oUNIFY_PROPOSITIONSpo, boolean, true);
                BIND_STELLA_SPECIAL(oQUERYITERATORo, QueryIterator*, NULL);
                if (!((boolean)(mapping))) {
                  mapping = newKeyValueMap();
                }
                else {
                  mapping->clear();
                }
                if (equivalentPropositionsP(proparg, arg, mapping)) {
                  return ((matchP ? pos : -1));
                }
              }
            }
          }
        }
        else {
        }
      }
    }
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "INTERNAL ERROR: failed to map neural net input argument: " << "`" << arg << "'" << "`" << proposition << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

boolean NeuralNetwork::truthValueArgumentP(Proposition* arg) {
  // Return TRUE if the partial truth value of `arg' will be considered for `self's inputs.
  // This top-level method only looks at `arg' and ignores `self'.
  { NeuralNetwork* self = this;

    { Object* argrel = ((Surrogate*)(arg->operatoR))->surrogateValue;

      return (((boolean)(argrel)) &&
          (testPropertyP(argrel, SGT_CHAMELEON_CHAMELEON_TRUTH_VALUE_RELATION) ||
           (!(testPropertyP(argrel, SGT_CHAMELEON_CHAMELEON_IGNORED_VALUE_RELATION) ||
          (testPropertyP(argrel, SGT_CHAMELEON_CHAMELEON_VECTOR_RELATION) &&
           (!testPropertyP(argrel, SGT_CHAMELEON_CHAMELEON_TRUTH_VALUE_RELATION)))))));
    }
  }
}

int NeuralNetwork::numberOfTruthValueArguments(Proposition* prop) {
  // Return the number of arguments of `prop' whose partial truth value will be considered
  // for `self's inputs.  This top-level method only looks at `prop' and ignores `self'.
  { NeuralNetwork* self = this;

    { int ntruth = 0;

      { Object* arg = NULL;
        Vector* vector000 = prop->arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          arg = (vector000->theArray)[index000];
          if (self->truthValueArgumentP(((Proposition*)(arg)))) {
            ntruth = ntruth + 1;
          }
        }
      }
      return (ntruth);
    }
  }
}

int NeuralNetwork::truthValueArgumentIndex(Proposition* arg) {
  // Return the 0-based input position of truth value argument `arg'.  Ignores bias unit which
  // is a network-implementation-specific detail.  Generates indices in the order expected by `set-input-values'.
  // If `arg' is not a truth value argument, returns -1.
  { NeuralNetwork* self = this;

    { MemoizationTable* memoTable000 = NULL;
      Cons* memoizedEntry000 = NULL;
      Object* memoizedValue000 = NULL;

      if (oMEMOIZATION_ENABLEDpo) {
        memoTable000 = ((MemoizationTable*)(SGT_CHAMELEON_LOGIC_M_NEURAL_NETWORKdTRUTH_VALUE_ARGUMENT_INDEX_MEMO_TABLE_000->surrogateValue));
        if (!((boolean)(memoTable000))) {
          initializeMemoizationTable(SGT_CHAMELEON_LOGIC_M_NEURAL_NETWORKdTRUTH_VALUE_ARGUMENT_INDEX_MEMO_TABLE_000, "(:MAX-VALUES 1000 :TIMESTAMPS (:KB-UPDATE))");
          memoTable000 = ((MemoizationTable*)(SGT_CHAMELEON_LOGIC_M_NEURAL_NETWORKdTRUTH_VALUE_ARGUMENT_INDEX_MEMO_TABLE_000->surrogateValue));
        }
        memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), self, arg, MEMOIZED_NULL_VALUE, NULL, -1);
        memoizedValue000 = memoizedEntry000->value;
      }
      if (((boolean)(memoizedValue000))) {
        if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
          memoizedValue000 = NULL;
        }
      }
      else {
        memoizedValue000 = wrapInteger(helpComputeArgumentIndex(self, arg, KWD_CHAMELEON_TRUTH_VALUE));
        if (oMEMOIZATION_ENABLEDpo) {
          memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
        }
      }
      { IntegerWrapper* value000 = ((IntegerWrapper*)(memoizedValue000));

        return (value000->wrapperValue);
      }
    }
  }
}

boolean NeuralNetwork::ignoredValueArgumentP(Proposition* arg) {
  // Return TRUE if the partial truth value of `arg' will be ignored for `self's inputs.
  // This top-level method only looks at `arg' and ignores `self'.
  { NeuralNetwork* self = this;

    { Object* argrel = ((Surrogate*)(arg->operatoR))->surrogateValue;

      return (((boolean)(argrel)) &&
          (testPropertyP(argrel, SGT_CHAMELEON_CHAMELEON_IGNORED_VALUE_RELATION) ||
           (testPropertyP(argrel, SGT_CHAMELEON_CHAMELEON_VECTOR_RELATION) &&
            (!testPropertyP(argrel, SGT_CHAMELEON_CHAMELEON_TRUTH_VALUE_RELATION)))));
    }
  }
}

int NeuralNetwork::numberOfIgnoredValueArguments(Proposition* prop) {
  // Return the number of arguments of `prop' whose partial truth value will be ignored
  // for `self's inputs.  This top-level method only looks at `prop' and ignores `self'.
  { NeuralNetwork* self = this;

    { int nignored = 0;

      { Object* arg = NULL;
        Vector* vector000 = prop->arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          arg = (vector000->theArray)[index000];
          if (self->ignoredValueArgumentP(((Proposition*)(arg)))) {
            nignored = nignored + 1;
          }
        }
      }
      return (nignored);
    }
  }
}

boolean NeuralNetwork::vectorArgumentP(Proposition* arg) {
  // Return TRUE if `arg' yields one or more vectors for `self's inputs.
  { NeuralNetwork* self = this;

    arg = arg;
    return (false);
  }
}

boolean NeuralNetwork::hasVectorArgumentsP() {
  // Return TRUE if `self' has at least one vector input argument.
  { NeuralNetwork* self = this;

    return (false);
  }
}

int NeuralNetwork::numberOfVectorArguments(Proposition* prop) {
  // Return the number of arguments of `prop' that yield one or more vectors
  // for `self's inputs.  `prop' can be NULL in which case the linked proposition will be used.
  { NeuralNetwork* self = this;

    prop = prop;
    return (0);
  }
}

int NeuralNetwork::vectorArgumentIndex(Proposition* arg) {
  // Return the 0-based input position of vector argument `arg'.  Ignores bias unit which
  // is a network-implementation-specific detail.  If `arg' is not a vector argument, returns -1.
  { NeuralNetwork* self = this;

    arg = arg;
    return (-1);
  }
}

double NeuralNetwork::nthInput(int n) {
  // Return the 0-based `n'-th proposition input of `self' (ignores bias unit).
  { NeuralNetwork* self = this;

    n = n;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "nth-input: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

double NeuralNetwork::nthInputError(int n) {
  // Return the 0-based `n'-th proposition input error of `self' (ignores bias unit).
  { NeuralNetwork* self = this;

    n = n;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "nth-input-error: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

double oCHAMELEON_DEFAULT_INPUT_VALUEo = 0.0;

FloatWrapper* oWRAPPED_CHAMELEON_DEFAULT_INPUT_VALUEo = NULL;

void NeuralNetwork::setInputValues(Object* values) {
  // Set the current truth-value inputs of the network `self' to float `values' in sequence.
  // Missing inputs will be set to 0.0, extra values will be ignored.
  { NeuralNetwork* self = this;

    values = values;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "set-input-values: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NeuralNetwork::setVectorInputValues(Object* vectorspecs) {
  // Set the current vector inputs of the network `self' to the vectors described by `vectorSpecs'.
  // Each vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs
  // are translated into actual numeric vectors such as embeddings is specific to the particular neural network type.
  { NeuralNetwork* self = this;

    vectorspecs = vectorspecs;
  }
}

Object* NeuralNetwork::getVectorArgumentSpec(Object* arg) {
  // Generate a single argument spec for `arg' that can be used for `set-vector-input-values'.
  // `arg' can either be a proposition or justification.
  { NeuralNetwork* self = this;

    arg = arg;
    return (NULL);
  }
}

double NeuralNetwork::forwardPropagateInputs() {
  // Activates the current inputs of the network `self' to compute its output.
  // Sets `self's `output' slot and returns the computed value.  Reads input activations and
  // weights and updates hidden and output activations.
  { NeuralNetwork* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "forward-propagate-inputs: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NeuralNetwork::backwardPropagateError(double error) {
  // Given a properly forward activated network `self' for the current set of inputs,
  // and a training `error' between the current output and the goal value, backpropagate the error and
  // update `self's vector of input errors.  Reads output, hidden activations and weights and updates
  // hidden errors and input errors.
  { NeuralNetwork* self = this;

    error = error;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "backward-propagate-error: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NeuralNetwork::updateNetworkWeights(double error) {
  // Given a properly forward activated and backpropagated network `self' for the current
  // inputs and training `error', update the network's weights according to current gradients, learning rate
  // and momentum terms to reduce the error for the given inputs.  Reads output, hidden and input activations,
  // hidden error, weights and weight deltas, and updates weights and weight deltas.
  { NeuralNetwork* self = this;

    error = error;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "update-network-weights: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void PropositionNeuralNetwork::linkNeuralNetwork(Proposition* prop) {
  // Link the network `self' to its associated proposition `prop'.
  { PropositionNeuralNetwork* self = this;

    self->proposition = prop;
    setDynamicSlotValue(prop->dynamicSlots, SYM_CHAMELEON_LOGIC_NEURAL_NET, self, NULL);
  }
}

void PropositionNeuralNetwork::unlinkNeuralNetwork() {
  // Unlink the network `self' from its associated proposition.
  { PropositionNeuralNetwork* self = this;

    { Proposition* prop = self->proposition;

      self->proposition = NULL;
      if (((boolean)(prop))) {
        setDynamicSlotValue(prop->dynamicSlots, SYM_CHAMELEON_LOGIC_NEURAL_NET, NULL, NULL);
      }
    }
  }
}

Proposition* PropositionNeuralNetwork::getNeuralNetworkProposition() {
  // Return the proposition linked to `self'.
  { PropositionNeuralNetwork* self = this;

    return (self->proposition);
  }
}

void PropositionNeuralNetwork::deleteNeuralNetwork() {
  // Unlink the network `self' from its associated proposition and mark it as deleted.
  { PropositionNeuralNetwork* self = this;

    self->unlinkNeuralNetwork();
    self->output = MOST_NEGATIVE_FLOAT;
  }
}

boolean PropositionNeuralNetwork::deletedP() {
  // Return trun if `self' has been deleted.
  { PropositionNeuralNetwork* self = this;

    return (self->output == MOST_NEGATIVE_FLOAT);
  }
}

void PropositionNeuralNetwork::allocateNetworkArrays(int numIn, int numHidden, int numOut) {
  // Allocates array space for a neural network with given number of input, hidden and output units.
  { PropositionNeuralNetwork* self = this;

    numOut = numOut;
    self->input = stella::newVector(numIn);
    self->hidden = stella::newVector(numHidden);
    self->ih = new2_D_array(numIn, numHidden);
    self->ihDelta = new2_D_array(numIn, numHidden);
    self->inputError = stella::newVector(numIn);
    self->hiddenError = stella::newVector(numHidden);
    self->ho = stella::newVector(numHidden);
    self->hoDelta = stella::newVector(numHidden);
    if (oNEURAL_NETWORK_TRAINING_METHODo == KWD_CHAMELEON_QUICKPROP) {
      self->ihSlope = new2_D_array(numIn, numHidden);
      self->ihPrevSlope = new2_D_array(numIn, numHidden);
      self->hoSlope = stella::newVector(numHidden);
      self->hoPrevSlope = stella::newVector(numHidden);
    }
  }
}

void PropositionNeuralNetwork::randomizeNetworkWeights() {
  // Randomize the weights of the neural network `self'.
  { PropositionNeuralNetwork* self = this;

    { int numIn = self->input->length();
      int numHidden = self->hidden->length();

      { int h = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = numHidden - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          h = iter000;
          (self->hoDelta->theArray)[h] = (wrapFloat(0.0));
          { int i = NULL_INTEGER;
            int iter001 = 0;
            int upperBound001 = numIn - 1;

            for  (; iter001 <= upperBound001; 
                  iter001 = iter001 + 1) {
              i = iter001;
              (self->ihDelta->theArray)[((i * self->ihDelta->nofColumns) + h)] = (wrapFloat(0.0));
            }
          }
        }
      }
      { int i = NULL_INTEGER;
        int iter002 = 0;
        int upperBound002 = numHidden - 1;

        for  (; iter002 <= upperBound002; 
              iter002 = iter002 + 1) {
          i = iter002;
          { int j = NULL_INTEGER;
            int iter003 = 0;
            int upperBound003 = numIn - 1;

            for  (; iter003 <= upperBound003; 
                  iter003 = iter003 + 1) {
              j = iter003;
              (self->ih->theArray)[((j * self->ih->nofColumns) + i)] = (wrapFloat(randomWeight(oWEIGHT_RANGEo)));
            }
          }
          (self->ho->theArray)[i] = (wrapFloat(randomWeight(oWEIGHT_RANGEo)));
        }
      }
    }
  }
}

void PropositionNeuralNetwork::buildPropositionNetwork(Proposition* prop) {
  // Build a neural network for the proposition `prop'.  This builds a two-layer
  // perceptron network whose input nodes are activated by the truth of `prop's arguments and whose
  // output node computes the truth of `prop'.
  { PropositionNeuralNetwork* self = this;

    { int numIn = (prop->arguments->length() - self->numberOfIgnoredValueArguments(prop)) + 1;
      int numHidden = stella::integerMin(numIn + 0, 20);

      if (numIn > 100) {
        numHidden = stella::floor(numIn / 10.0) + 10;
      }
      self->allocateNetworkArrays(numIn, numHidden, 1);
      { Keyword* testValue000 = prop->kind;

        if ((testValue000 == KWD_CHAMELEON_AND) ||
            (testValue000 == KWD_CHAMELEON_OR)) {
          self->randomizeNetworkWeights();
        }
        else {
          self->randomizeNetworkWeights();
        }
      }
      self->linkNeuralNetwork(prop);
    }
  }
}

int PropositionNeuralNetwork::numberOfInputs() {
  // Return the number of input values expected by `self' (ignores bias unit).
  { PropositionNeuralNetwork* self = this;

    return (self->input->length() - 1);
  }
}

double PropositionNeuralNetwork::nthInput(int n) {
  // Return the 0-based `n'-th proposition input of `self' (ignores bias unit).
  { PropositionNeuralNetwork* self = this;

    return (((FloatWrapper*)((self->input->theArray)[(n + 1)]))->wrapperValue);
  }
}

double PropositionNeuralNetwork::nthInputError(int n) {
  // Return the 0-based `n'-th proposition input error of `self' (ignores bias unit).
  { PropositionNeuralNetwork* self = this;

    return (((FloatWrapper*)((self->inputError->theArray)[(n + 1)]))->wrapperValue);
  }
}

void PropositionNeuralNetwork::setInputValues(Object* values) {
  // Set the current truth-value inputs of the network `self' to float `values' in sequence.
  // Missing inputs will be set to 0.0, extra values will be ignored.
  { PropositionNeuralNetwork* self = this;

    { Vector* input = self->input;
      int numIn = input->length();
      int cursor = 1;

      (input->theArray)[0] = (wrapFloat(1.0));
      { Surrogate* testValue000 = safePrimaryType(values);

        if (testValue000 == SGT_CHAMELEON_STELLA_CONS) {
          { Object* values000 = values;
            Cons* values = ((Cons*)(values000));

            { Object* val = NULL;
              Cons* iter000 = values;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                val = iter000->value;
                if (cursor < numIn) {
                  if (!((boolean)(val))) {
                    val = oWRAPPED_CHAMELEON_DEFAULT_INPUT_VALUEo;
                  }
                  (input->theArray)[cursor] = (((FloatWrapper*)(val)));
                  cursor = cursor + 1;
                }
              }
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_CHAMELEON_STELLA_LIST)) {
          { Object* values001 = values;
            List* values = ((List*)(values001));

            { Object* val = NULL;
              Cons* iter001 = values->theConsList;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                val = iter001->value;
                if (cursor < numIn) {
                  if (!((boolean)(val))) {
                    val = oWRAPPED_CHAMELEON_DEFAULT_INPUT_VALUEo;
                  }
                  (input->theArray)[cursor] = (((FloatWrapper*)(val)));
                  cursor = cursor + 1;
                }
              }
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_CHAMELEON_STELLA_VECTOR)) {
          { Object* values002 = values;
            Vector* values = ((Vector*)(values002));

            { Object* val = NULL;
              Vector* vector000 = values;
              int index000 = 0;
              int length000 = vector000->length();

              for  (; index000 < length000; 
                    index000 = index000 + 1) {
                val = (vector000->theArray)[index000];
                if (cursor < numIn) {
                  if (!((boolean)(val))) {
                    val = oWRAPPED_CHAMELEON_DEFAULT_INPUT_VALUEo;
                  }
                  (input->theArray)[cursor] = (((FloatWrapper*)(val)));
                  cursor = cursor + 1;
                }
              }
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_CHAMELEON_STELLA_SEQUENCE)) {
          { Object* values003 = values;
            Sequence* values = ((Sequence*)(values003));

            { Object* val = NULL;
              Iterator* iter002 = ((Iterator*)(values->allocateIterator()));

              for (; iter002->nextP(); ) {
                val = iter002->value;
                if (cursor < numIn) {
                  if (!((boolean)(val))) {
                    val = oWRAPPED_CHAMELEON_DEFAULT_INPUT_VALUEo;
                  }
                  (input->theArray)[cursor] = (((FloatWrapper*)(val)));
                  cursor = cursor + 1;
                }
              }
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_CHAMELEON_STELLA_ITERATOR)) {
          { Object* values004 = values;
            Iterator* values = ((Iterator*)(values004));

            { Object* val = NULL;
              Iterator* iter003 = values;

              for (; iter003->nextP(); ) {
                val = iter003->value;
                if (cursor < numIn) {
                  if (!((boolean)(val))) {
                    val = oWRAPPED_CHAMELEON_DEFAULT_INPUT_VALUEo;
                  }
                  (input->theArray)[cursor] = (((FloatWrapper*)(val)));
                  cursor = cursor + 1;
                }
              }
            }
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      while (cursor < numIn) {
        (input->theArray)[cursor] = (wrapFloat(0.0));
        cursor = cursor + 1;
      }
    }
  }
}

double PropositionNeuralNetwork::forwardPropagateInputs() {
  // Activates the current inputs of the network `self' to compute its output.
  // Sets `self's `output' slot and returns the computed value.  Reads input activations and
  // weights and updates hidden and output activations.
  { PropositionNeuralNetwork* self = this;

    { Vector* input = self->input;
      Vector* hidden = self->hidden;
      int numIn = input->length();
      int numHidden = hidden->length();
      two_D_array* ih = self->ih;
      Vector* ho = self->ho;
      double score = 0.0;
      double sum = 0.0;

      (input->theArray)[0] = (wrapFloat(1.0));
      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = numHidden - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          { int j = NULL_INTEGER;
            int iter001 = 0;
            int upperBound001 = numIn - 1;

            for  (; iter001 <= upperBound001; 
                  iter001 = iter001 + 1) {
              j = iter001;
              sum = sum + (((FloatWrapper*)((input->theArray)[j]))->wrapperValue * ((FloatWrapper*)((ih->theArray)[((j * ih->nofColumns) + i)]))->wrapperValue);
            }
          }
          (hidden->theArray)[i] = (wrapFloat(1.0 / (1.0 + ::exp((0 - sum)))));
          score = score + (((FloatWrapper*)((hidden->theArray)[i]))->wrapperValue * ((FloatWrapper*)((ho->theArray)[i]))->wrapperValue);
        }
      }
      self->output = 1.0 / (1.0 + ::exp((0 - score)));
      return (self->output);
    }
  }
}

void PropositionNeuralNetwork::backwardPropagateError(double error) {
  // Given a properly forward activated network `self' for the current set of inputs,
  // and a training `error' between the current output and the goal value, backpropagate the error and
  // update `self's vector of input errors.  Reads output, hidden activations and weights and updates
  // hidden errors and input errors.
  { PropositionNeuralNetwork* self = this;

    { int lastInput = self->input->length() - 1;
      Vector* inputError = self->inputError;
      two_D_array* ih = self->ih;
      Vector* hidden = self->hidden;
      int lastHidden = hidden->length() - 1;
      Vector* hiddenError = self->hiddenError;
      Vector* ho = self->ho;
      double output = self->output;

      error = error * output * (1.0 - output);
      { int h = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = lastHidden;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter000 <= upperBound000); 
              iter000 = iter000 + 1) {
          h = iter000;
          (hiddenError->theArray)[h] = (wrapFloat(error * ((FloatWrapper*)((ho->theArray)[h]))->wrapperValue));
          (hiddenError->theArray)[h] = (wrapFloat(((FloatWrapper*)((hiddenError->theArray)[h]))->wrapperValue * ((FloatWrapper*)((hidden->theArray)[h]))->wrapperValue * (1.0 - ((FloatWrapper*)((hidden->theArray)[h]))->wrapperValue)));
        }
      }
      { int i = NULL_INTEGER;
        int iter001 = 0;
        int upperBound001 = lastInput;
        boolean unboundedP001 = upperBound001 == NULL_INTEGER;

        for  (; unboundedP001 ||
                  (iter001 <= upperBound001); 
              iter001 = iter001 + 1) {
          i = iter001;
          (inputError->theArray)[i] = (wrapFloat(0.0));
          { int h = NULL_INTEGER;
            int iter002 = 0;
            int upperBound002 = lastHidden;
            boolean unboundedP002 = upperBound002 == NULL_INTEGER;

            for  (; unboundedP002 ||
                      (iter002 <= upperBound002); 
                  iter002 = iter002 + 1) {
              h = iter002;
              (inputError->theArray)[i] = (wrapFloat(((FloatWrapper*)((inputError->theArray)[i]))->wrapperValue + (((FloatWrapper*)((hiddenError->theArray)[h]))->wrapperValue * ((FloatWrapper*)((ih->theArray)[((i * ih->nofColumns) + h)]))->wrapperValue)));
            }
          }
        }
      }
    }
  }
}

void PropositionNeuralNetwork::updateNetworkWeights(double error) {
  // Given a properly forward activated and backpropagated network `self' for the current
  // inputs and training `error', update the network's weights according to current gradients, learning rate
  // and momentum terms to reduce the error for the given inputs.  Reads output, hidden and input activations,
  // hidden error, weights and weight deltas, and updates weights and weight deltas.
  { PropositionNeuralNetwork* self = this;

    { Vector* input = self->input;
      int lastInput = input->length() - 1;
      two_D_array* ih = self->ih;
      two_D_array* ihDelta = self->ihDelta;
      Vector* hidden = self->hidden;
      int lastHidden = hidden->length() - 1;
      Vector* hiddenError = self->hiddenError;
      Vector* ho = self->ho;
      Vector* hoDelta = self->hoDelta;
      double output = self->output;
      double delta = 0.0;

      error = error * output * (1.0 - output);
      { int h = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = lastHidden;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter000 <= upperBound000); 
              iter000 = iter000 + 1) {
          h = iter000;
          delta = (oMOMENTUM_TERMo * ((FloatWrapper*)((hoDelta->theArray)[h]))->wrapperValue) + (oLEARNING_RATEo * error * ((FloatWrapper*)((hidden->theArray)[h]))->wrapperValue);
          (ho->theArray)[h] = (wrapFloat(((FloatWrapper*)((ho->theArray)[h]))->wrapperValue + delta));
          (hoDelta->theArray)[h] = (wrapFloat(delta));
          { int i = NULL_INTEGER;
            int iter001 = 0;
            int upperBound001 = lastInput;
            boolean unboundedP001 = upperBound001 == NULL_INTEGER;

            for  (; unboundedP001 ||
                      (iter001 <= upperBound001); 
                  iter001 = iter001 + 1) {
              i = iter001;
              delta = (oMOMENTUM_TERMo * ((FloatWrapper*)((ihDelta->theArray)[((i * ihDelta->nofColumns) + h)]))->wrapperValue) + (oLEARNING_RATEo * ((FloatWrapper*)((hiddenError->theArray)[h]))->wrapperValue * ((FloatWrapper*)((input->theArray)[i]))->wrapperValue);
              (ih->theArray)[((i * ih->nofColumns) + h)] = (wrapFloat(((FloatWrapper*)((ih->theArray)[((i * ih->nofColumns) + h)]))->wrapperValue + delta));
              (ihDelta->theArray)[((i * ihDelta->nofColumns) + h)] = (wrapFloat(delta));
            }
          }
        }
      }
    }
  }
}

ChameleonNeuralNetwork* newChameleonNeuralNetwork() {
  { ChameleonNeuralNetwork* self = NULL;

    self = new ChameleonNeuralNetwork();
    self->hoDelta = NULL;
    self->ihDelta = NULL;
    self->outputError = NULL_FLOAT;
    self->hiddenError = NULL;
    self->inputError = NULL;
    self->ho = NULL;
    self->ih = NULL;
    self->output = NULL_FLOAT;
    self->hidden = NULL;
    self->input = NULL;
    self->proposition = NULL;
    return (self);
  }
}

Surrogate* ChameleonNeuralNetwork::primaryType() {
  { ChameleonNeuralNetwork* self = this;

    return (SGT_CHAMELEON_LOGIC_CHAMELEON_NEURAL_NETWORK);
  }
}

Object* accessChameleonNeuralNetworkSlotValue(ChameleonNeuralNetwork* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_CHAMELEON_LOGIC_PROPOSITION) {
    if (setvalueP) {
      self->proposition = ((Proposition*)(value));
    }
    else {
      value = self->proposition;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_INPUT) {
    if (setvalueP) {
      self->input = ((oneDFloatArray*)(value));
    }
    else {
      value = self->input;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_HIDDEN) {
    if (setvalueP) {
      self->hidden = ((oneDFloatArray*)(value));
    }
    else {
      value = self->hidden;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_OUTPUT) {
    if (setvalueP) {
      self->output = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->output);
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_IH) {
    if (setvalueP) {
      self->ih = ((twoDFloatArray*)(value));
    }
    else {
      value = self->ih;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_HO) {
    if (setvalueP) {
      self->ho = ((oneDFloatArray*)(value));
    }
    else {
      value = self->ho;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_INPUT_ERROR) {
    if (setvalueP) {
      self->inputError = ((oneDFloatArray*)(value));
    }
    else {
      value = self->inputError;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_HIDDEN_ERROR) {
    if (setvalueP) {
      self->hiddenError = ((oneDFloatArray*)(value));
    }
    else {
      value = self->hiddenError;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_OUTPUT_ERROR) {
    if (setvalueP) {
      self->outputError = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->outputError);
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_IH_DELTA) {
    if (setvalueP) {
      self->ihDelta = ((twoDFloatArray*)(value));
    }
    else {
      value = self->ihDelta;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_HO_DELTA) {
    if (setvalueP) {
      self->hoDelta = ((oneDFloatArray*)(value));
    }
    else {
      value = self->hoDelta;
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

void ChameleonNeuralNetwork::linkNeuralNetwork(Proposition* prop) {
  // Link the network `self' to its associated proposition `prop'.
  { ChameleonNeuralNetwork* self = this;

    self->proposition = prop;
    setDynamicSlotValue(prop->dynamicSlots, SYM_CHAMELEON_LOGIC_NEURAL_NET, self, NULL);
  }
}

void ChameleonNeuralNetwork::unlinkNeuralNetwork() {
  // Unlink the network `self' from its associated proposition.
  { ChameleonNeuralNetwork* self = this;

    { Proposition* prop = self->proposition;

      self->proposition = NULL;
      if (((boolean)(prop))) {
        setDynamicSlotValue(prop->dynamicSlots, SYM_CHAMELEON_LOGIC_NEURAL_NET, NULL, NULL);
      }
    }
  }
}

Proposition* ChameleonNeuralNetwork::getNeuralNetworkProposition() {
  // Return the proposition linked to `self'.
  { ChameleonNeuralNetwork* self = this;

    return (self->proposition);
  }
}

void ChameleonNeuralNetwork::deleteNeuralNetwork() {
  // Unlink the network `self' from its associated proposition and mark it as deleted.
  { ChameleonNeuralNetwork* self = this;

    self->unlinkNeuralNetwork();
    self->output = MOST_NEGATIVE_FLOAT;
  }
}

boolean ChameleonNeuralNetwork::deletedP() {
  // Return trun if `self' has been deleted.
  { ChameleonNeuralNetwork* self = this;

    return (self->output == MOST_NEGATIVE_FLOAT);
  }
}

void ChameleonNeuralNetwork::allocateNetworkArrays(int numIn, int numHidden, int numOut) {
  // Allocates array space for a neural network with given number of input, hidden and output units.
  { ChameleonNeuralNetwork* self = this;

    numOut = numOut;
    self->input = new1DFloatArray(numIn);
    self->hidden = new1DFloatArray(numHidden);
    self->ih = new2DFloatArray(numHidden, numIn);
    self->ihDelta = new2DFloatArray(numHidden, numIn);
    self->inputError = new1DFloatArray(numIn);
    self->hiddenError = new1DFloatArray(numHidden);
    self->ho = new1DFloatArray(numHidden);
    self->hoDelta = new1DFloatArray(numHidden);
  }
}

void ChameleonNeuralNetwork::randomizeNetworkWeights() {
  // Randomize the weights of the neural network `self'.
  { ChameleonNeuralNetwork* self = this;

    { int numIn = self->input->dim1;
      int numHidden = self->hidden->dim1;
      double* hoDeltaArray = self->hoDelta->theArray;
      twoDFloatArray* ihDelta = self->ihDelta;
      twoDFloatArray* ih = self->ih;
      double* hoArray = self->ho->theArray;

      { int h = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = numHidden - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          h = iter000;
          hoDeltaArray[h] = 0.0;
          { int i = NULL_INTEGER;
            int iter001 = 0;
            int upperBound001 = numIn - 1;

            for  (; iter001 <= upperBound001; 
                  iter001 = iter001 + 1) {
              i = iter001;
              ihDelta->theArray[(i * ihDelta->dim2) + h] = 0.0;
            }
          }
        }
      }
      { int i = NULL_INTEGER;
        int iter002 = 0;
        int upperBound002 = numHidden - 1;

        for  (; iter002 <= upperBound002; 
              iter002 = iter002 + 1) {
          i = iter002;
          { int j = NULL_INTEGER;
            int iter003 = 0;
            int upperBound003 = numIn - 1;

            for  (; iter003 <= upperBound003; 
                  iter003 = iter003 + 1) {
              j = iter003;
              ih->theArray[(j * ih->dim2) + i] = randomWeight(oWEIGHT_RANGEo);
            }
          }
          hoArray[i] = randomWeight(oWEIGHT_RANGEo);
        }
      }
    }
  }
}

void ChameleonNeuralNetwork::buildPropositionNetwork(Proposition* prop) {
  // Build a neural network for the proposition `prop'.  This builds a two-layer
  // perceptron network whose input nodes are activated by the truth of `prop's arguments and whose
  // output node computes the truth of `prop'.
  { ChameleonNeuralNetwork* self = this;

    { int numIn = (prop->arguments->length() - self->numberOfIgnoredValueArguments(prop)) + 1;
      int numHidden = stella::integerMin(numIn + 0, 20);

      if (numIn > 100) {
        numHidden = stella::floor(numIn / 10.0) + 10;
      }
      self->allocateNetworkArrays(numIn, numHidden, 1);
      { Keyword* testValue000 = prop->kind;

        if ((testValue000 == KWD_CHAMELEON_AND) ||
            (testValue000 == KWD_CHAMELEON_OR)) {
          self->randomizeNetworkWeights();
        }
        else {
          self->randomizeNetworkWeights();
        }
      }
      self->linkNeuralNetwork(prop);
    }
  }
}

int ChameleonNeuralNetwork::numberOfInputs() {
  // Return the number of input values expected by `self' (ignores bias unit).
  { ChameleonNeuralNetwork* self = this;

    return (self->input->dim1 - 1);
  }
}

double ChameleonNeuralNetwork::nthInput(int n) {
  // Return the 0-based `n'-th proposition input of `self' (ignores bias unit).
  { ChameleonNeuralNetwork* self = this;

    return (self->input->theArray[n + 1]);
  }
}

double ChameleonNeuralNetwork::nthInputError(int n) {
  // Return the 0-based `n'-th proposition input error of `self' (ignores bias unit).
  { ChameleonNeuralNetwork* self = this;

    return (self->inputError->theArray[n + 1]);
  }
}

void copyFloatValuesToBuffer(Object* values, double* buffer, int start, int end) {
  // Copy the float `values' in sequence to `buffer' between `start' and `end'.
  // Missing values will be set to 0.0, extra values will be ignored.
  { int cursor = start;

    { Surrogate* testValue000 = safePrimaryType(values);

      if (subtypeOfP(testValue000, SGT_CHAMELEON_STELLA_VECTOR)) {
        { Object* values000 = values;
          Vector* values = ((Vector*)(values000));

          { Object* val = NULL;
            Vector* vector000 = values;
            int index000 = 0;
            int length000 = vector000->length();

            for  (; index000 < length000; 
                  index000 = index000 + 1) {
              val = (vector000->theArray)[index000];
              if (cursor < end) {
                if (!((boolean)(val))) {
                  val = oWRAPPED_CHAMELEON_DEFAULT_INPUT_VALUEo;
                }
                buffer[cursor] = ((FloatWrapper*)(val))->wrapperValue;
                cursor = cursor + 1;
              }
            }
          }
        }
      }
      else if (testValue000 == SGT_CHAMELEON_STELLA_CONS) {
        { Object* values001 = values;
          Cons* values = ((Cons*)(values001));

          { Object* val = NULL;
            Cons* iter000 = values;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              val = iter000->value;
              if (cursor < end) {
                if (!((boolean)(val))) {
                  val = oWRAPPED_CHAMELEON_DEFAULT_INPUT_VALUEo;
                }
                buffer[cursor] = ((FloatWrapper*)(val))->wrapperValue;
                cursor = cursor + 1;
              }
            }
          }
        }
      }
      else if (subtypeOfP(testValue000, SGT_CHAMELEON_STELLA_LIST)) {
        { Object* values002 = values;
          List* values = ((List*)(values002));

          { Object* val = NULL;
            Cons* iter001 = values->theConsList;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              val = iter001->value;
              if (cursor < end) {
                if (!((boolean)(val))) {
                  val = oWRAPPED_CHAMELEON_DEFAULT_INPUT_VALUEo;
                }
                buffer[cursor] = ((FloatWrapper*)(val))->wrapperValue;
                cursor = cursor + 1;
              }
            }
          }
        }
      }
      else if (subtypeOfP(testValue000, SGT_CHAMELEON_STELLA_SEQUENCE)) {
        { Object* values003 = values;
          Sequence* values = ((Sequence*)(values003));

          { Object* val = NULL;
            Iterator* iter002 = ((Iterator*)(values->allocateIterator()));

            for (; iter002->nextP(); ) {
              val = iter002->value;
              if (cursor < end) {
                if (!((boolean)(val))) {
                  val = oWRAPPED_CHAMELEON_DEFAULT_INPUT_VALUEo;
                }
                buffer[cursor] = ((FloatWrapper*)(val))->wrapperValue;
                cursor = cursor + 1;
              }
            }
          }
        }
      }
      else if (subtypeOfP(testValue000, SGT_CHAMELEON_STELLA_ITERATOR)) {
        { Object* values004 = values;
          Iterator* values = ((Iterator*)(values004));

          { Object* val = NULL;
            Iterator* iter003 = values;

            for (; iter003->nextP(); ) {
              val = iter003->value;
              if (cursor < end) {
                if (!((boolean)(val))) {
                  val = oWRAPPED_CHAMELEON_DEFAULT_INPUT_VALUEo;
                }
                buffer[cursor] = ((FloatWrapper*)(val))->wrapperValue;
                cursor = cursor + 1;
              }
            }
          }
        }
      }
      else if (subtypeOfP(testValue000, SGT_CHAMELEON_STELLA_FLOAT_ARRAY)) {
        { Object* values005 = values;
          oneDFloatArray* values = ((oneDFloatArray*)(values005));

          { double* valuesarray = values->theArray;

            { int i = NULL_INTEGER;
              int iter004 = 0;
              int upperBound000 = values->dim1 - 1;

              for  (; iter004 <= upperBound000; 
                    iter004 = iter004 + 1) {
                i = iter004;
                if (cursor < end) {
                  buffer[cursor] = valuesarray[i];
                  cursor = cursor + 1;
                }
              }
            }
          }
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    while (cursor < end) {
      buffer[cursor] = 0.0;
      cursor = cursor + 1;
    }
  }
}

void ChameleonNeuralNetwork::setInputValues(Object* values) {
  // Set the current truth-value inputs of the network `self' to float `values' in sequence.
  // Missing inputs will be set to 0.0, extra values will be ignored.
  { ChameleonNeuralNetwork* self = this;

    { oneDFloatArray* input = self->input;
      double* inputarray = input->theArray;

      inputarray[0] = 1.0;
      copyFloatValuesToBuffer(values, inputarray, 1, input->dim1);
    }
  }
}

void ChameleonNeuralNetwork::setVectorInputValues(Object* vectorspecs) {
  // Set the current vector inputs of the network `self' to the vectors described by `vectorSpecs'.
  // Each vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs
  // are translated into actual numeric vectors such as embeddings is specific to the particular neural network type.
  { ChameleonNeuralNetwork* self = this;

    vectorspecs = vectorspecs;
    if (!(isaP(self, SGT_CHAMELEON_LOGIC_VECTOR_NEURAL_NETWORK))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "set-vector-input-values: Not defined on " << "`" << self << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

double ChameleonNeuralNetwork::forwardPropagateInputs() {
  // Activates the current inputs of the network `self' to compute its output.
  // Sets `self's `output' slot and returns the computed value.  Reads input activations and
  // weights and updates hidden and output activations.
  { ChameleonNeuralNetwork* self = this;

    { oneDFloatArray* input = self->input;
      oneDFloatArray* hidden = self->hidden;
      int numIn = input->dim1;
      int numHidden = hidden->dim1;
      double* inputArray = input->theArray;
      double* hiddenArray = hidden->theArray;
      twoDFloatArray* ih = self->ih;
      oneDFloatArray* ho = self->ho;
      double* hoArray = ho->theArray;
      double score = 0.0;
      double sum = 0.0;

      inputArray[0] = 1.0;
      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = numHidden - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          sum = 0.0;
          { int j = NULL_INTEGER;
            int iter001 = 0;
            int upperBound001 = numIn - 1;

            for  (; iter001 <= upperBound001; 
                  iter001 = iter001 + 1) {
              j = iter001;
              sum = sum + (inputArray[j] * ih->theArray[(j * ih->dim2) + i]);
            }
          }
          hiddenArray[i] = 1.0 / (1.0 + ::exp((0 - sum)));
          score = score + (hiddenArray[i] * hoArray[i]);
        }
      }
      self->output = 1.0 / (1.0 + ::exp((0 - score)));
      return (self->output);
    }
  }
}

void ChameleonNeuralNetwork::backwardPropagateError(double error) {
  // Given a properly forward activated network `self' for the current set of inputs,
  // and a training `error' between the current output and the goal value, backpropagate the error and
  // update `self's vector of input errors.  Reads output, hidden activations and weights and updates
  // hidden errors and input errors.
  { ChameleonNeuralNetwork* self = this;

    { int lastInput = self->input->dim1 - 1;
      oneDFloatArray* inputError = self->inputError;
      double* inputErrorArray = inputError->theArray;
      twoDFloatArray* ih = self->ih;
      oneDFloatArray* hidden = self->hidden;
      double* hiddenArray = hidden->theArray;
      int lastHidden = hidden->dim1 - 1;
      oneDFloatArray* hiddenError = self->hiddenError;
      double* hiddenErrorArray = hiddenError->theArray;
      oneDFloatArray* ho = self->ho;
      double* hoArray = ho->theArray;
      double output = self->output;

      error = error * output * (1.0 - output);
      { int h = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = lastHidden;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter000 <= upperBound000); 
              iter000 = iter000 + 1) {
          h = iter000;
          hiddenErrorArray[h] = error * hoArray[h];
          hiddenErrorArray[h] = hiddenErrorArray[h] * hiddenArray[h] * (1.0 - hiddenArray[h]);
        }
      }
      { int i = NULL_INTEGER;
        int iter001 = 0;
        int upperBound001 = lastInput;
        boolean unboundedP001 = upperBound001 == NULL_INTEGER;

        for  (; unboundedP001 ||
                  (iter001 <= upperBound001); 
              iter001 = iter001 + 1) {
          i = iter001;
          inputErrorArray[i] = 0.0;
          { int h = NULL_INTEGER;
            int iter002 = 0;
            int upperBound002 = lastHidden;
            boolean unboundedP002 = upperBound002 == NULL_INTEGER;

            for  (; unboundedP002 ||
                      (iter002 <= upperBound002); 
                  iter002 = iter002 + 1) {
              h = iter002;
              inputErrorArray[i] = inputErrorArray[i] + (hiddenErrorArray[h] * ih->theArray[(i * ih->dim2) + h]);
            }
          }
        }
      }
    }
  }
}

void ChameleonNeuralNetwork::updateNetworkWeights(double error) {
  // Given a properly forward activated and backpropagated network `self' for the current
  // inputs and training `error', update the network's weights according to current gradients, learning rate
  // and momentum terms to reduce the error for the given inputs.  Reads output, hidden and input activations,
  // hidden error, weights and weight deltas, and updates weights and weight deltas.
  { ChameleonNeuralNetwork* self = this;

    { oneDFloatArray* input = self->input;
      int lastInput = input->dim1 - 1;
      double* inputArray = input->theArray;
      twoDFloatArray* ih = self->ih;
      twoDFloatArray* ihDelta = self->ihDelta;
      oneDFloatArray* hidden = self->hidden;
      int lastHidden = hidden->dim1 - 1;
      double* hiddenArray = hidden->theArray;
      oneDFloatArray* hiddenError = self->hiddenError;
      double* hiddenErrorArray = hiddenError->theArray;
      oneDFloatArray* ho = self->ho;
      double* hoArray = ho->theArray;
      oneDFloatArray* hoDelta = self->hoDelta;
      double* hoDeltaArray = hoDelta->theArray;
      double output = self->output;
      double delta = 0.0;

      error = error * output * (1.0 - output);
      { int h = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = lastHidden;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter000 <= upperBound000); 
              iter000 = iter000 + 1) {
          h = iter000;
          delta = (oMOMENTUM_TERMo * hoDeltaArray[h]) + (oLEARNING_RATEo * error * hiddenArray[h]);
          hoArray[h] = hoArray[h] + delta;
          hoDeltaArray[h] = delta;
          { int i = NULL_INTEGER;
            int iter001 = 0;
            int upperBound001 = lastInput;
            boolean unboundedP001 = upperBound001 == NULL_INTEGER;

            for  (; unboundedP001 ||
                      (iter001 <= upperBound001); 
                  iter001 = iter001 + 1) {
              i = iter001;
              delta = (oMOMENTUM_TERMo * ihDelta->theArray[(i * ihDelta->dim2) + h]) + (oLEARNING_RATEo * hiddenErrorArray[h] * inputArray[i]);
              ih->theArray[(i * ih->dim2) + h] = ih->theArray[(i * ih->dim2) + h] + delta;
              ihDelta->theArray[(i * ihDelta->dim2) + h] = delta;
            }
          }
        }
      }
    }
  }
}

VectorNeuralNetwork* newVectorNeuralNetwork() {
  { VectorNeuralNetwork* self = NULL;

    self = new (PointerFreeGC)VectorNeuralNetwork;
    self->nVectorArgumentInputs = -1;
    self->nVectorArgumentSpecs = -1;
    self->nVectorArguments = -1;
    return (self);
  }
}

Surrogate* VectorNeuralNetwork::primaryType() {
  { VectorNeuralNetwork* self = this;

    return (SGT_CHAMELEON_LOGIC_VECTOR_NEURAL_NETWORK);
  }
}

Object* accessVectorNeuralNetworkSlotValue(VectorNeuralNetwork* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_CHAMELEON_LOGIC_N_VECTOR_ARGUMENTS) {
    if (setvalueP) {
      self->nVectorArguments = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->nVectorArguments);
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_N_VECTOR_ARGUMENT_SPECS) {
    if (setvalueP) {
      self->nVectorArgumentSpecs = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->nVectorArgumentSpecs);
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_N_VECTOR_ARGUMENT_INPUTS) {
    if (setvalueP) {
      self->nVectorArgumentInputs = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->nVectorArgumentInputs);
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

boolean VectorNeuralNetwork::vectorArgumentP(Proposition* arg) {
  // Return TRUE if `arg' yields one or more vectors for `self's inputs.
  { VectorNeuralNetwork* self = this;

    { Object* argrel = ((Surrogate*)(arg->operatoR))->surrogateValue;

      return (((boolean)(argrel)) &&
          testPropertyP(argrel, SGT_CHAMELEON_CHAMELEON_VECTOR_RELATION));
    }
  }
}

boolean VectorNeuralNetwork::hasVectorArgumentsP() {
  // Return TRUE if `self' has at least one vector input argument.
  { VectorNeuralNetwork* self = this;

    { int nargs = self->nVectorArguments;

      if (nargs < 0) {
        nargs = self->numberOfVectorArguments(NULL);
      }
      return (nargs > 0);
    }
  }
}

int VectorNeuralNetwork::numberOfVectorArguments(Proposition* prop) {
  // Return the number of arguments of `prop' that yield one or more vectors
  // for `self's inputs.  `prop' can be NULL in which case the linked proposition will be used.
  { VectorNeuralNetwork* self = this;

    { int nargs = self->nVectorArguments;

      if (nargs < 0) {
        if (!((boolean)(prop))) {
          prop = self->getNeuralNetworkProposition();
        }
        nargs = 0;
        { Object* arg = NULL;
          Vector* vector000 = prop->arguments;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            arg = (vector000->theArray)[index000];
            if (self->vectorArgumentP(((Proposition*)(arg)))) {
              nargs = nargs + 1;
            }
          }
        }
        self->nVectorArguments = nargs;
      }
      return (nargs);
    }
  }
}

int VectorNeuralNetwork::vectorArgumentIndex(Proposition* arg) {
  // Return the 0-based input position of vector argument `arg'.  Ignores bias unit which
  // is a network-implementation-specific detail.  If `arg' is not a vector argument, returns -1.
  { VectorNeuralNetwork* self = this;

    { MemoizationTable* memoTable000 = NULL;
      Cons* memoizedEntry000 = NULL;
      Object* memoizedValue000 = NULL;

      if (oMEMOIZATION_ENABLEDpo) {
        memoTable000 = ((MemoizationTable*)(SGT_CHAMELEON_LOGIC_M_VECTOR_NEURAL_NETWORKdVECTOR_ARGUMENT_INDEX_MEMO_TABLE_000->surrogateValue));
        if (!((boolean)(memoTable000))) {
          initializeMemoizationTable(SGT_CHAMELEON_LOGIC_M_VECTOR_NEURAL_NETWORKdVECTOR_ARGUMENT_INDEX_MEMO_TABLE_000, "(:MAX-VALUES 1000 :TIMESTAMPS (:KB-UPDATE))");
          memoTable000 = ((MemoizationTable*)(SGT_CHAMELEON_LOGIC_M_VECTOR_NEURAL_NETWORKdVECTOR_ARGUMENT_INDEX_MEMO_TABLE_000->surrogateValue));
        }
        memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), self, arg, MEMOIZED_NULL_VALUE, NULL, -1);
        memoizedValue000 = memoizedEntry000->value;
      }
      if (((boolean)(memoizedValue000))) {
        if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
          memoizedValue000 = NULL;
        }
      }
      else {
        memoizedValue000 = wrapInteger(helpComputeArgumentIndex(self, arg, KWD_CHAMELEON_VECTOR));
        if (oMEMOIZATION_ENABLEDpo) {
          memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
        }
      }
      { IntegerWrapper* value000 = ((IntegerWrapper*)(memoizedValue000));

        return (value000->wrapperValue);
      }
    }
  }
}

int VectorNeuralNetwork::numberOfVectorArgumentSpecs(Proposition* prop) {
  // Return the total number of argument specs generated by vector arguments of `prop'.
  // This is only different than `number-of-vector-arguments' if at least one of `prop's vector argument
  // relations has arity > 1.  `prop' can be NULL in which case the linked proposition will be used.
  { VectorNeuralNetwork* self = this;

    { int ninps = self->nVectorArgumentSpecs;

      if (ninps < 0) {
        if (!((boolean)(prop))) {
          prop = self->getNeuralNetworkProposition();
        }
        ninps = 0;
        { Object* arg = NULL;
          Vector* vector000 = prop->arguments;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            arg = (vector000->theArray)[index000];
            if (self->vectorArgumentP(((Proposition*)(arg)))) {
              { Object* rel = ((Surrogate*)(((Proposition*)(arg))->operatoR))->surrogateValue;
                Object* arity = accessBinaryValue(rel, SGT_CHAMELEON_CHAMELEON_VECTOR_ARITY);

                if (!(integerP(arity))) {
                  { OutputStringStream* stream000 = newOutputStringStream();

                    *(stream000->nativeStream) << "number-of-vector-argument-specs: Missing or incorrect arity specifications for " << "`" << rel << "'";
                    throw *newStellaException(stream000->theStringReader());
                  }
                }
                ninps = ((int)(ninps + ((NumberWrapper*)(arity))->numberWrapperToFloat()));
              }
            }
          }
        }
        self->nVectorArgumentSpecs = ninps;
      }
      return (ninps);
    }
  }
}

int VectorNeuralNetwork::numberOfVectorArgumentInputs(Proposition* prop) {
  // Return the total number of input positions to store all elements of all vector
  // arguments of `prop'.  `prop' can be NULL in which case the linked proposition will be used.
  { VectorNeuralNetwork* self = this;

    { int ninps = self->nVectorArgumentInputs;

      if (ninps < 0) {
        if (!((boolean)(prop))) {
          prop = self->getNeuralNetworkProposition();
        }
        ninps = 0;
        { Object* arg = NULL;
          Vector* vector000 = prop->arguments;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            arg = (vector000->theArray)[index000];
            if (self->vectorArgumentP(((Proposition*)(arg)))) {
              { Object* rel = ((Surrogate*)(((Proposition*)(arg))->operatoR))->surrogateValue;
                Object* arity = accessBinaryValue(rel, SGT_CHAMELEON_CHAMELEON_VECTOR_ARITY);
                Object* dims = accessBinaryValue(rel, SGT_CHAMELEON_CHAMELEON_VECTOR_DIMENSIONS);

                if (!(integerP(arity) &&
                    integerP(dims))) {
                  { OutputStringStream* stream000 = newOutputStringStream();

                    *(stream000->nativeStream) << "number-of-vector-argument-inputs: Missing or incorrect arity/dimension specifications for " << "`" << rel << "'";
                    throw *newStellaException(stream000->theStringReader());
                  }
                }
                ninps = ((int)(ninps + (((NumberWrapper*)(arity))->numberWrapperToFloat() * ((NumberWrapper*)(dims))->numberWrapperToFloat())));
              }
            }
          }
        }
        self->nVectorArgumentInputs = ninps;
      }
      return (ninps);
    }
  }
}

void VectorNeuralNetwork::setVectorInputValues(Object* vectorspecs) {
  // Set the current vector inputs of the network `self' to the vectors described by `vectorSpecs'.
  // Each vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs
  // are translated into actual numeric vectors such as embeddings is specific to the particular neural network type.
  { VectorNeuralNetwork* self = this;

    vectorspecs = vectorspecs;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "set-vector-input-values: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Object* VectorNeuralNetwork::getVectorArgumentSpec(Object* arg) {
  // Generate a single argument spec for `arg' that can be used for `set-vector-input-values'.
  // `arg' can either be a proposition or justification.
  { VectorNeuralNetwork* self = this;

    { Surrogate* testValue000 = safePrimaryType(arg);

      if (subtypeOfP(testValue000, SGT_CHAMELEON_LOGIC_JUSTIFICATION)) {
        { Object* arg000 = arg;
          Justification* arg = ((Justification*)(arg000));

          { 
            BIND_STELLA_SPECIAL(oCURRENTJUSTIFICATIONo, Justification*, arg);
            return (generateProposition(arg->proposition));
          }
        }
      }
      else if (subtypeOfP(testValue000, SGT_CHAMELEON_LOGIC_PROPOSITION)) {
        { Object* arg001 = arg;
          Proposition* arg = ((Proposition*)(arg001));

          return (generateProposition(arg));
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

TensorflowNeuralNetwork* newTensorflowNeuralNetwork() {
  { TensorflowNeuralNetwork* self = NULL;

    self = new TensorflowNeuralNetwork();
    self->nVectorArgumentInputs = -1;
    self->nVectorArgumentSpecs = -1;
    self->nVectorArguments = -1;
    self->model = NULL;
    self->proposition = NULL;
    return (self);
  }
}

Surrogate* TensorflowNeuralNetwork::primaryType() {
  { TensorflowNeuralNetwork* self = this;

    return (SGT_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORK);
  }
}

Object* accessTensorflowNeuralNetworkSlotValue(TensorflowNeuralNetwork* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_CHAMELEON_LOGIC_PROPOSITION) {
    if (setvalueP) {
      self->proposition = ((Proposition*)(value));
    }
    else {
      value = self->proposition;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_MODEL) {
    if (setvalueP) {
      self->model = ((LongIntegerWrapper*)(value));
    }
    else {
      value = self->model;
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

void registerTensorflowCallback(const char* name, cpp_function_code code) {
  // Special-purpose callback support that registers `code' under the logic symbol with `name',
  // which by convention we make the qualified method name of the method we are using this for.  This is a
  // special-purpose hack which eventually we might want to generalize so others can use it too.
  symbolValueSetter(internSymbolInModule(stringUpcase(name), oLOGIC_MODULEo, false), wrapFunctionCode(code));
}

cpp_function_code getTensorflowCallback(Symbol* name) {
  // Access the TensorFlow callback code registered under `name'.
  return (((FunctionCodeWrapper*)(name->symbolValueAndPlist->value))->wrapperValue);
}

boolean tensorflowBackendAvailableP() {
  // Return TRUE if TensorFlow callbacks have been properly registered.
  return (((boolean)(SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdBUILD_PROPOSITION_NETWORK->symbolValueAndPlist->value)));
}

void TensorflowNeuralNetwork::linkNeuralNetwork(Proposition* prop) {
  // Link the network `self' to its associated proposition `prop'.
  { TensorflowNeuralNetwork* self = this;

    self->proposition = prop;
    setDynamicSlotValue(prop->dynamicSlots, SYM_CHAMELEON_LOGIC_NEURAL_NET, self, NULL);
  }
}

void TensorflowNeuralNetwork::unlinkNeuralNetwork() {
  // Unlink the network `self' from its associated proposition.
  { TensorflowNeuralNetwork* self = this;

    { Proposition* prop = self->proposition;

      self->proposition = NULL;
      if (((boolean)(prop))) {
        setDynamicSlotValue(prop->dynamicSlots, SYM_CHAMELEON_LOGIC_NEURAL_NET, NULL, NULL);
      }
    }
  }
}

Proposition* TensorflowNeuralNetwork::getNeuralNetworkProposition() {
  // Return the proposition linked to `self'.
  { TensorflowNeuralNetwork* self = this;

    return (self->proposition);
  }
}

void TensorflowNeuralNetwork::deleteNeuralNetwork() {
  // Unlink the network `self' from its associated proposition and mark it as deleted.
  { TensorflowNeuralNetwork* self = this;

    self->unlinkNeuralNetwork();
    self->model = wrapLongInteger(MOST_NEGATIVE_LONG_INTEGER);
  }
}

boolean TensorflowNeuralNetwork::deletedP() {
  // Return trun if `self' has been deleted.
  { TensorflowNeuralNetwork* self = this;

    return (eqlToLongIntegerP(self->model, MOST_NEGATIVE_LONG_INTEGER));
  }
}

void TensorflowNeuralNetwork::allocateNetworkArrays(int numIn, int numHidden, int numOut) {
  // Allocates array space for a neural network with given number of input, hidden and output units.
  { TensorflowNeuralNetwork* self = this;

    ((void  (*) (TensorflowNeuralNetwork*, int, int, int))((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdALLOCATE_NETWORK_ARRAYS->symbolValueAndPlist->value))->wrapperValue)(self, numIn, numHidden, numOut);
  }
}

void TensorflowNeuralNetwork::randomizeNetworkWeights() {
  // Randomize the weights of the neural network `self'.
  { TensorflowNeuralNetwork* self = this;

    ((void  (*) (TensorflowNeuralNetwork*))((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdRANDOMIZE_NETWORK_WEIGHTS->symbolValueAndPlist->value))->wrapperValue)(self);
  }
}

void TensorflowNeuralNetwork::initializeNetworkWeights() {
  // Initialize the weights of the neural network `self' - eiher randomly or from a saved state.
  { TensorflowNeuralNetwork* self = this;

    ((void  (*) (TensorflowNeuralNetwork*))((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdINITIALIZE_NETWORK_WEIGHTS->symbolValueAndPlist->value))->wrapperValue)(self);
  }
}

void TensorflowNeuralNetwork::buildPropositionNetwork(Proposition* prop) {
  // Build a neural network for the proposition `prop'.  This builds a two-layer
  // perceptron network whose input nodes are activated by the truth of `prop's arguments and whose
  // output node computes the truth of `prop'.
  { TensorflowNeuralNetwork* self = this;

    ((void  (*) (TensorflowNeuralNetwork*, Proposition*))((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdBUILD_PROPOSITION_NETWORK->symbolValueAndPlist->value))->wrapperValue)(self, prop);
    self->linkNeuralNetwork(prop);
  }
}

int TensorflowNeuralNetwork::numberOfInputs() {
  // Return the number of input values expected by `self' (ignores bias unit).
  { TensorflowNeuralNetwork* self = this;

    return (((int  (*) (TensorflowNeuralNetwork*))((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdNUMBER_OF_INPUTS->symbolValueAndPlist->value))->wrapperValue)(self));
  }
}

double TensorflowNeuralNetwork::nthInput(int n) {
  // Return the 0-based `n'-th proposition input of `self' (ignores bias unit).
  { TensorflowNeuralNetwork* self = this;

    return (((double  (*) (TensorflowNeuralNetwork*, int))((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdNTH_INPUT->symbolValueAndPlist->value))->wrapperValue)(self, n));
  }
}

double TensorflowNeuralNetwork::nthInputError(int n) {
  // Return the 0-based `n'-th proposition input error of `self' (ignores bias unit).
  { TensorflowNeuralNetwork* self = this;

    return (((double  (*) (TensorflowNeuralNetwork*, int))((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdNTH_INPUT_ERROR->symbolValueAndPlist->value))->wrapperValue)(self, n));
  }
}

void TensorflowNeuralNetwork::setInputValues(Object* values) {
  // Set the current truth-value inputs of the network `self' to float `values' in sequence.
  // Missing inputs will be set to 0.0, extra values will be ignored.
  { TensorflowNeuralNetwork* self = this;

    ((void  (*) (TensorflowNeuralNetwork*, Cons*))((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdSET_INPUT_VALUES->symbolValueAndPlist->value))->wrapperValue)(self, values->consify());
  }
}

Object* TensorflowNeuralNetwork::getVectorArgumentSpec(Object* arg) {
  // Generate a single argument spec for `arg' that can be used for `set-vector-input-values'.
  // `arg' can either be a proposition or justification.
  { TensorflowNeuralNetwork* self = this;

    { Object* spec = VectorNeuralNetwork::getVectorArgumentSpec(arg);
      Cons* evalargs = NIL;

      if (safePrimaryType(spec) == SGT_CHAMELEON_STELLA_CONS) {
        { Object* spec000 = spec;
          Cons* spec = ((Cons*)(spec000));

          { Object* elt = NULL;
            Cons* iter000 = spec;
            Cons* collect000 = NULL;

            for  (; !(iter000 == NIL); 
                  iter000 = iter000->rest) {
              elt = iter000->value;
              if (longIntegerP(elt) ||
                  stringP(elt)) {
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(elt, NIL);
                    if (evalargs == NIL) {
                      evalargs = collect000;
                    }
                    else {
                      addConsToEndOfConsList(evalargs, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(elt, NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
          }
        }
      }
      else {
      }
      if (!(evalargs == NIL)) {
        return (evalargs);
      }
      else {
        return (spec);
      }
    }
  }
}

void TensorflowNeuralNetwork::setVectorInputValues(Object* vectorspecs) {
  // Set the current vector inputs of the network `self' to the vectors described by `vectorSpecs'.
  // Each vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs
  // are translated into actual numeric vectors such as embeddings is specific to the particular neural network type.
  { TensorflowNeuralNetwork* self = this;

    ((void  (*) (TensorflowNeuralNetwork*, Cons*))((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdSET_VECTOR_INPUT_VALUES->symbolValueAndPlist->value))->wrapperValue)(self, vectorspecs->consify());
  }
}

double TensorflowNeuralNetwork::forwardPropagateInputs() {
  // Activates the current inputs of the network `self' to compute its output.
  // Sets `self's `output' slot and returns the computed value.  Reads input activations and
  // weights and updates hidden and output activations.
  { TensorflowNeuralNetwork* self = this;

    return (((double  (*) (TensorflowNeuralNetwork*))((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdFORWARD_PROPAGATE_INPUTS->symbolValueAndPlist->value))->wrapperValue)(self));
  }
}

void TensorflowNeuralNetwork::backwardPropagateError(double error) {
  // Given a properly forward activated network `self' for the current set of inputs,
  // and a training `error' between the current output and the goal value, backpropagate the error and
  // update `self's vector of input errors.  Reads output, hidden activations and weights and updates
  // hidden errors and input errors.
  { TensorflowNeuralNetwork* self = this;

    ((void  (*) (TensorflowNeuralNetwork*, double))((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdBACKWARD_PROPAGATE_ERROR->symbolValueAndPlist->value))->wrapperValue)(self, error);
  }
}

void TensorflowNeuralNetwork::updateNetworkWeights(double error) {
  // Given a properly forward activated and backpropagated network `self' for the current
  // inputs and training `error', update the network's weights according to current gradients, learning rate
  // and momentum terms to reduce the error for the given inputs.  Reads output, hidden and input activations,
  // hidden error, weights and weight deltas, and updates weights and weight deltas.
  { TensorflowNeuralNetwork* self = this;

    ((void  (*) (TensorflowNeuralNetwork*, double))((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdUPDATE_NETWORK_WEIGHTS->symbolValueAndPlist->value))->wrapperValue)(self, error);
  }
}

Justification* getCachedNetworkProof(TrainingExample* example) {
  // Variant of `create-cached-network' that takes a training `example',
  // runs its cons query, and stores a compacted version of the associated proof tree
  // as the `example's cached solution which will also be returned.  If a cached and
  // up-to-date solution already exists, it will be returned instead.
  if (((boolean)(example->cachedSolution)) &&
      (example->timestamp == getNowTimestamp())) {
    return (((Justification*)(example->cachedSolution)));
  }
  else {
    { Module* temp000 = example->module;

      { Module* module = (((boolean)(temp000)) ? temp000 : oMODULEo);

        { 
          BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
          { QueryIterator* queryiter = createAskQuery(consList(5, example->query, KWD_CHAMELEON_RECORD_JUSTIFICATIONSp, TRUE_WRAPPER, KWD_CHAMELEON_MATCH_MODE, KWD_CHAMELEON_CHAMELEON));

            callAskPartial(queryiter);
            example->cachedSolution = ((Justification*)(dynamicSlotValue(queryiter->baseControlFrame->dynamicSlots, SYM_CHAMELEON_LOGIC_JUSTIFICATION, NULL)));
            if (!((boolean)(example->cachedSolution))) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                *(STANDARD_WARNING->nativeStream) << "WARNING: " << "get-cached-network-proof: training example query failed: " << example->query << std::endl;
                helpSignalPropositionError(STANDARD_WARNING, KWD_CHAMELEON_WARNING);
              }
              recordFailJustification(queryiter->baseControlFrame, KWD_CHAMELEON_UP_FAIL);
              example->cachedSolution = ((Justification*)(dynamicSlotValue(queryiter->baseControlFrame->dynamicSlots, SYM_CHAMELEON_LOGIC_JUSTIFICATION, NULL)));
            }
            example->cachedSolution = compactPartialProofToNetworkProof(((Justification*)(example->cachedSolution)));
            example->timestamp = getNowTimestamp();
            return (((Justification*)(example->cachedSolution)));
          }
        }
      }
    }
  }
}

Justification* compactPartialProofToNetworkProof(Justification* proof) {
  // Convert `proof' into a compacted network tree form that only contains
  // :AND, :OR, :MULTI and :PRIMITIVE nodes (some of which such as `instance-of' might contain
  // further antecedents if they were computed by specialists, for example).
  { Keyword* testValue000 = proof->inferenceRule;

    if (testValue000 == KWD_CHAMELEON_PRIMITIVE_STRATEGY) {
      if (((PrimitiveStrategy*)(proof))->strategy == KWD_CHAMELEON_GOAL_COMPLEMENT) {
        proof = proof->shallowCopy();
        proof->inferenceRule = KWD_CHAMELEON_GOAL_COMPLEMENT;
        return (compactPartialProofToNetworkProof(proof));
      }
      else if (proof->antecedents == NIL) {
        return (proof);
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "INTERNAL ERROR: unexpected primitive justifications with antecedents for: " << "`" << proof->proposition << "'";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    else if ((testValue000 == KWD_CHAMELEON_AND_INTRODUCTION) ||
        ((testValue000 == KWD_CHAMELEON_OR_INTRODUCTION) ||
         ((testValue000 == KWD_CHAMELEON_MULTIPLE_PROOFS) ||
          ((testValue000 == KWD_CHAMELEON_DISPROOF) ||
           (testValue000 == KWD_CHAMELEON_GOAL_COMPLEMENT))))) {
      proof = proof->shallowCopy();
      { Cons* value000 = NIL;

        { Justification* ant = NULL;
          Cons* iter000 = proof->antecedents;
          Cons* collect000 = NULL;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest) {
            ant = ((Justification*)(iter000->value));
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(compactPartialProofToNetworkProof(ant), NIL);
                if (value000 == NIL) {
                  value000 = collect000;
                }
                else {
                  addConsToEndOfConsList(value000, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(compactPartialProofToNetworkProof(ant), NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        proof->antecedents = value000;
      }
      return (proof);
    }
    else if ((testValue000 == KWD_CHAMELEON_MODUS_PONENS) ||
        (testValue000 == KWD_CHAMELEON_MODUS_TOLLENS)) {
      { Object* relation = ((Surrogate*)(proof->proposition->operatoR))->surrogateValue;

        if (((boolean)(relation)) &&
            (testPropertyP(relation, SGT_CHAMELEON_CHAMELEON_TRUTH_VALUE_RELATION) ||
             (!(testPropertyP(relation, SGT_CHAMELEON_CHAMELEON_IGNORED_VALUE_RELATION) ||
            (testPropertyP(relation, SGT_CHAMELEON_CHAMELEON_VECTOR_RELATION) &&
             (!testPropertyP(relation, SGT_CHAMELEON_CHAMELEON_TRUTH_VALUE_RELATION))))))) {
          proof = proof->shallowCopy();
          proof->inferenceRule = KWD_CHAMELEON_MULTIPLE_PROOFS;
          proof->antecedents = cons(compactPartialProofToNetworkProof(((Justification*)(proof->antecedents->rest->value))), NIL);
          return (proof);
        }
        else {
          proof = proof->shallowCopy();
          proof->inferenceRule = KWD_CHAMELEON_PRIMITIVE_STRATEGY;
          proof->antecedents = NIL;
          return (proof);
        }
      }
    }
    else if (testValue000 == KWD_CHAMELEON_SUBSUMPTION_REASONING) {
      proof = proof->shallowCopy();
      proof->inferenceRule = KWD_CHAMELEON_PRIMITIVE_STRATEGY;
      proof->antecedents = NIL;
      return (proof);
    }
    else if (testValue000 == KWD_CHAMELEON_FAIL_INTRODUCTION) {
      proof = proof->shallowCopy();
      proof->inferenceRule = KWD_CHAMELEON_PRIMITIVE_STRATEGY;
      proof->antecedents = NIL;
      return (proof);
    }
    else {
      { Object* relation = ((Surrogate*)(proof->proposition->operatoR))->surrogateValue;

        if (((boolean)(relation)) &&
            testPropertyP(relation, SGT_CHAMELEON_CHAMELEON_PRIMITIVE_VALUE_RELATION)) {
          proof = proof->shallowCopy();
          proof->inferenceRule = KWD_CHAMELEON_PRIMITIVE_STRATEGY;
          proof->antecedents = NIL;
          return (proof);
        }
        else {
          switch (proof->antecedents->length()) {
            case 0: 
              return (proof);
            case 1: 
              return (compactPartialProofToNetworkProof(((Justification*)(proof->antecedents->value))));
            default:
              { OutputStringStream* stream001 = newOutputStringStream();

                *(stream001->nativeStream) << "Unhandled network proof justification with multiple antecedents: " << "`" << proof->inferenceRule << "'";
                throw *newStellaException(stream001->theStringReader());
              }
              break;
          }
        }
      }
    }
  }
}

double combineMultipleMatchScores(Cons* scores) {
  // Combine partial match scores from alternative :multiple-proofs `scores'
  // according to the current `*rule-combination*' strategy.
  if (oRULE_COMBINATIONo == KWD_CHAMELEON_MAX) {
    { double max = 0.0;

      { FloatWrapper* score = NULL;
        Cons* iter000 = scores;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          score = ((FloatWrapper*)(iter000->value));
          if (score->wrapperValue > max) {
            max = score->wrapperValue;
          }
        }
      }
      return (max);
    }
  }
  else if (oRULE_COMBINATIONo == KWD_CHAMELEON_NOISY_OR) {
    switch (scores->length()) {
      case 0: 
        return (0.0);
      case 1: 
        return (((FloatWrapper*)(scores->value))->wrapperValue);
      case 2: 
        return (probabilisticSum(((FloatWrapper*)(scores->value))->wrapperValue, ((FloatWrapper*)(scores->rest->value))->wrapperValue));
      default:
        return (probabilisticSumN(scores));
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << oRULE_COMBINATIONo << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

double forwardPropagateCachedNetworkProof(Justification* proof) {
  // Compute the same partial match score as the call to `compute-partial-truth'
  // that generated `proof' (which is assumed to have been compacted with a call to
  // `compact-partial-proof-to-network-proof'.  The score will only be identical of course, if
  // the various networks and their weights have not yet been updated during learning.
  { double score = 0.0;

    { Keyword* testValue000 = proof->inferenceRule;

      if (testValue000 == KWD_CHAMELEON_PRIMITIVE_STRATEGY) {
        return (proof->matchScore);
      }
      else if ((testValue000 == KWD_CHAMELEON_AND_INTRODUCTION) ||
          (testValue000 == KWD_CHAMELEON_OR_INTRODUCTION)) {
        { NeuralNetwork* net = getJustificationNeuralNetwork(proof);
          Vector* inputs = stella::newVector(net->numberOfInputs());
          Vector* vectorargs = (net->hasVectorArgumentsP() ? stella::newVector(net->numberOfVectorArguments(NULL)) : ((Vector*)(NULL)));
          int index = -1;

          { Justification* ant = NULL;
            Cons* iter000 = proof->antecedents;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              ant = ((Justification*)(iter000->value));
              index = net->truthValueArgumentIndex(ant->proposition);
              if (index >= 0) {
                score = forwardPropagateCachedNetworkProof(ant);
                (inputs->theArray)[index] = (wrapFloat(score));
              }
              if (((boolean)(vectorargs))) {
                index = net->vectorArgumentIndex(ant->proposition);
                if (index >= 0) {
                  (vectorargs->theArray)[index] = (net->getVectorArgumentSpec(ant));
                }
              }
            }
          }
          net->setInputValues(inputs);
          if (((boolean)(vectorargs))) {
            net->setVectorInputValues(vectorargs);
          }
          score = net->forwardPropagateInputs();
          proof->matchScore = score;
          return (score);
        }
      }
      else if (testValue000 == KWD_CHAMELEON_MULTIPLE_PROOFS) {
        { Cons* value000 = NIL;

          { Justification* ant = NULL;
            Cons* iter001 = proof->antecedents;
            Cons* collect000 = NULL;

            for  (; !(iter001 == NIL); 
                  iter001 = iter001->rest) {
              ant = ((Justification*)(iter001->value));
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(wrapFloat(forwardPropagateCachedNetworkProof(ant)), NIL);
                  if (value000 == NIL) {
                    value000 = collect000;
                  }
                  else {
                    addConsToEndOfConsList(value000, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(wrapFloat(forwardPropagateCachedNetworkProof(ant)), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
          score = combineMultipleMatchScores(value000);
        }
        proof->matchScore = score;
        return (score);
      }
      else if ((testValue000 == KWD_CHAMELEON_DISPROOF) ||
          (testValue000 == KWD_CHAMELEON_GOAL_COMPLEMENT)) {
        score = invertChameleonMatchScore(((Justification*)(proof->antecedents->value))->matchScore);
        proof->matchScore = score;
        return (score);
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

double forwardPropagateCachedNetworkFromJustification(Justification* just) {
  // Locally forward-propagate the network associated with `just' based on
  // previously cached `positive-score's of antecedents.
  { double score = 0.0;

    { Keyword* testValue000 = just->inferenceRule;

      if ((testValue000 == KWD_CHAMELEON_AND_INTRODUCTION) ||
          (testValue000 == KWD_CHAMELEON_OR_INTRODUCTION)) {
        { NeuralNetwork* net = getJustificationNeuralNetwork(just);
          Vector* inputs = stella::newVector(net->numberOfInputs());
          Vector* vectorargs = (net->hasVectorArgumentsP() ? stella::newVector(net->numberOfVectorArguments(NULL)) : ((Vector*)(NULL)));
          int index = -1;

          { Justification* ant = NULL;
            Cons* iter000 = just->antecedents;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              ant = ((Justification*)(iter000->value));
              index = net->truthValueArgumentIndex(ant->proposition);
              if (index >= 0) {
                score = ant->matchScore;
                (inputs->theArray)[index] = (wrapFloat(score));
              }
              if (((boolean)(vectorargs))) {
                index = net->vectorArgumentIndex(ant->proposition);
                if (index >= 0) {
                  (vectorargs->theArray)[index] = (net->getVectorArgumentSpec(ant));
                }
              }
            }
          }
          net->setInputValues(inputs);
          if (((boolean)(vectorargs))) {
            net->setVectorInputValues(vectorargs);
          }
          score = net->forwardPropagateInputs();
          return (score);
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

void backwardPropagateCachedNetworkProof(Justification* proof, double error) {
  // Propagate the `error' between `proof's conclusion and the desired target value
  // through `proof's network and its antecedents, and adjust weights to decrease the error.  Multiple
  // iterations through `forward/backward-propagate-cached-network-proof' with updated top-level
  // errors will train the involved networks to minimize the error as much as possible.
  { Keyword* testValue000 = proof->inferenceRule;

    if (testValue000 == KWD_CHAMELEON_MULTIPLE_PROOFS) {
      backwardPropagateCachedNetworkMultiProof(proof, error);
    }
    else if ((testValue000 == KWD_CHAMELEON_DISPROOF) ||
        (testValue000 == KWD_CHAMELEON_GOAL_COMPLEMENT)) {
      backwardPropagateCachedNetworkProof(((Justification*)(proof->antecedents->value)), error);
    }
    else if ((testValue000 == KWD_CHAMELEON_AND_INTRODUCTION) ||
        (testValue000 == KWD_CHAMELEON_OR_INTRODUCTION)) {
      { NeuralNetwork* net = getJustificationNeuralNetwork(proof);
        boolean reactivateP = false;

        forwardPropagateCachedNetworkFromJustification(proof);
        net->backwardPropagateError(error);
        { Justification* ant = NULL;
          Cons* iter000 = proof->antecedents;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            ant = ((Justification*)(iter000->value));
            if (!(ant->inferenceRule == KWD_CHAMELEON_PRIMITIVE_STRATEGY)) {
              { int index = net->truthValueArgumentIndex(ant->proposition);

                if (index >= 0) {
                  backwardPropagateCachedNetworkProof(ant, net->nthInputError(index));
                  reactivateP = true;
                }
              }
            }
          }
        }
        if (reactivateP) {
          forwardPropagateCachedNetworkFromJustification(proof);
          net->backwardPropagateError(error);
        }
        net->updateNetworkWeights(error);
      }
    }
    else if (testValue000 == KWD_CHAMELEON_PRIMITIVE_STRATEGY) {
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

void backwardPropagateCachedNetworkMultiProof(Justification* proof, double error) {
  // Recurse through :multiple-proofs antecedents guided by the current rule combination scheme.
  if (oRULE_COMBINATIONo == KWD_CHAMELEON_MAX) {
    { double max = MOST_NEGATIVE_FLOAT;

      { Justification* ant = NULL;
        Cons* iter000 = proof->antecedents;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          ant = ((Justification*)(iter000->value));
          if (ant->matchScore > max) {
            max = ant->matchScore;
            proof = ant;
          }
        }
      }
      backwardPropagateCachedNetworkProof(proof, error);
    }
  }
  else if (oRULE_COMBINATIONo == KWD_CHAMELEON_NOISY_OR) {
    { Justification* ant = NULL;
      Cons* iter001 = proof->antecedents;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        ant = ((Justification*)(iter001->value));
        backwardPropagateCachedNetworkProof(ant, error * ant->matchScore);
      }
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << oRULE_COMBINATIONo << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NeuralNetwork::clearBatchArrays() {
  // Clear all currently batched inputs (with keys) and associated target values.
  { NeuralNetwork* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "clear-batch-arrays: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

int NeuralNetwork::currentBatchSize() {
  // Return the number of currently batched inputs.
  { NeuralNetwork* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "current-batch-size: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

boolean NeuralNetwork::batchIsFullP() {
  // Return true if input batch arrays have been filled to capacity.
  { NeuralNetwork* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "batch-is-full?: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NeuralNetwork::pushInputValues(Object* key, Object* values) {
  // Push input `values' onto the input batch array and associate them with `key' (which can be NULL).
  // Associating a key lets us easily map inputs/outputs to some processing object of interest (e.g., a justification).
  { NeuralNetwork* self = this;

    {
      key = key;
      values = values;
    }
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "push-input-values: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NeuralNetwork::pushVectorInputValues(Object* vectorspecs) {
  // Push `vectorSpecs' onto the vector argument batch array which is assumed to correspond to the input
  // values at the same respective position in the batch.  Truth-valued and vector-valued inputs are associated by position
  // in the batch, they can be pushed independently, as long as they are fully synchronized when processing of the batch starts.
  // If `self' has no vector-valued argument, the associated batch array can be left undefined.
  { NeuralNetwork* self = this;

    vectorspecs = vectorspecs;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "push-vector-input-values: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NeuralNetwork::pushTargetValue(double value) {
  // Push a target `value' onto the target batch array which is assumed to correspond to the input
  // values at the same respective position in the batch.  Inputs and targets are associated by position in the batch,
  // they can be pushed independently, as long as they are fully synchronized when processing of the batch starts.
  { NeuralNetwork* self = this;

    value = value;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "push-target-value: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Object* NeuralNetwork::nthBatchKey(int n) {
  // Return the key associated with the `n'-th set of inputs in the input batch.
  { NeuralNetwork* self = this;

    n = n;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "nth-batch-key: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

double NeuralNetwork::nthKthBatchInputError(int n, int k) {
  // Return error of the `k'-th input in the `n'-th set of inputs in the input batch.
  // `k' ignores the bias unit.
  { NeuralNetwork* self = this;

    {
      n = n;
      k = k;
    }
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "nth-kth-batch-input-error: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

double NeuralNetwork::nthBatchOutput(int n) {
  // Return the output value for the `n'-th set of inputs in the input batch.
  { NeuralNetwork* self = this;

    n = n;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "nth-batch-output: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

oneDFloatArray* NeuralNetwork::batchForwardPropagateInputs() {
  // Run forward propagation on the current input batch and store outputs in the output batch.
  { NeuralNetwork* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "batch-forward-propagate-inputs: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NeuralNetwork::batchBackwardPropagateError() {
  // Run backward propagation on the current input and target batch and store back-propagated
  // errors in the input error batch.
  { NeuralNetwork* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "batch-backward-propagate-error: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NeuralNetwork::batchUpdateNetworkWeights() {
  // Run weight updates for the current input and target batches.
  { NeuralNetwork* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "batch-update-network-weights: Not defined on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

int oNEURAL_NETWORK_BATCH_SIZEo = 128;

ChameleonBatchNeuralNetwork* newChameleonBatchNeuralNetwork() {
  { ChameleonBatchNeuralNetwork* self = NULL;

    self = new ChameleonBatchNeuralNetwork();
    self->hoDelta = NULL;
    self->ihDelta = NULL;
    self->outputError = NULL_FLOAT;
    self->hiddenError = NULL;
    self->inputError = NULL;
    self->ho = NULL;
    self->ih = NULL;
    self->output = NULL_FLOAT;
    self->hidden = NULL;
    self->input = NULL;
    self->proposition = NULL;
    self->inputErrorBatch = NULL;
    self->outputBatch = NULL;
    self->targetBatch = NULL;
    self->keyBatch = NULL;
    self->inputBatch = NULL;
    return (self);
  }
}

Surrogate* ChameleonBatchNeuralNetwork::primaryType() {
  { ChameleonBatchNeuralNetwork* self = this;

    return (SGT_CHAMELEON_LOGIC_CHAMELEON_BATCH_NEURAL_NETWORK);
  }
}

Object* accessChameleonBatchNeuralNetworkSlotValue(ChameleonBatchNeuralNetwork* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_CHAMELEON_LOGIC_INPUT_BATCH) {
    if (setvalueP) {
      self->inputBatch = ((VectorSequence*)(value));
    }
    else {
      value = self->inputBatch;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_KEY_BATCH) {
    if (setvalueP) {
      self->keyBatch = ((VectorSequence*)(value));
    }
    else {
      value = self->keyBatch;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_TARGET_BATCH) {
    if (setvalueP) {
      self->targetBatch = ((VectorSequence*)(value));
    }
    else {
      value = self->targetBatch;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_OUTPUT_BATCH) {
    if (setvalueP) {
      self->outputBatch = ((oneDFloatArray*)(value));
    }
    else {
      value = self->outputBatch;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_INPUT_ERROR_BATCH) {
    if (setvalueP) {
      self->inputErrorBatch = ((VectorSequence*)(value));
    }
    else {
      value = self->inputErrorBatch;
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

void ChameleonBatchNeuralNetwork::allocateNetworkArrays(int numIn, int numHidden, int numOut) {
  { ChameleonBatchNeuralNetwork* self = this;

    ChameleonNeuralNetwork::allocateNetworkArrays(numIn, numHidden, numOut);
    self->inputBatch = newVectorSequence(oNEURAL_NETWORK_BATCH_SIZEo);
    self->keyBatch = newVectorSequence(oNEURAL_NETWORK_BATCH_SIZEo);
    self->outputBatch = new1DFloatArray(oNEURAL_NETWORK_BATCH_SIZEo);
    self->targetBatch = newVectorSequence(oNEURAL_NETWORK_BATCH_SIZEo);
    self->inputErrorBatch = newVectorSequence(oNEURAL_NETWORK_BATCH_SIZEo);
  }
}

void ChameleonBatchNeuralNetwork::clearBatchArrays() {
  { ChameleonBatchNeuralNetwork* self = this;

    self->inputBatch->clear();
    self->keyBatch->clear();
    self->targetBatch->clear();
    self->inputErrorBatch->clear();
  }
}

int ChameleonBatchNeuralNetwork::currentBatchSize() {
  { ChameleonBatchNeuralNetwork* self = this;

    return (self->inputBatch->sequenceLength);
  }
}

boolean ChameleonBatchNeuralNetwork::batchIsFullP() {
  { ChameleonBatchNeuralNetwork* self = this;

    return (self->inputBatch->sequenceLength >= self->outputBatch->length());
  }
}

void ChameleonBatchNeuralNetwork::pushInputValues(Object* key, Object* values) {
  { ChameleonBatchNeuralNetwork* self = this;

    self->keyBatch->insert(key);
    self->inputBatch->insert(values);
  }
}

void ChameleonBatchNeuralNetwork::pushTargetValue(double value) {
  { ChameleonBatchNeuralNetwork* self = this;

    self->targetBatch->insert(wrapFloat(value));
  }
}

Object* ChameleonBatchNeuralNetwork::nthBatchKey(int n) {
  { ChameleonBatchNeuralNetwork* self = this;

    return ((self->keyBatch->theArray)[n]);
  }
}

double ChameleonBatchNeuralNetwork::nthKthBatchInputError(int n, int k) {
  { ChameleonBatchNeuralNetwork* self = this;

    return (((oneDFloatArray*)((self->inputErrorBatch->theArray)[n]))->theArray[k + 1]);
  }
}

double ChameleonBatchNeuralNetwork::nthBatchOutput(int n) {
  { ChameleonBatchNeuralNetwork* self = this;

    return (self->outputBatch->theArray[n]);
  }
}

int oBATCH_OPERATION_COUNTo = 0;

int oBATCH_TOTAL_COUNTo = 0;

oneDFloatArray* ChameleonBatchNeuralNetwork::batchForwardPropagateInputs() {
  { ChameleonBatchNeuralNetwork* self = this;

    { double* outputs = self->outputBatch->theArray;

      { Object* input = NULL;
        VectorSequence* vector000 = self->inputBatch;
        int index000 = 0;
        int length000 = vector000->sequenceLength;
        int i = NULL_INTEGER;
        int iter000 = 0;

        for  (; index000 < length000; 
              index000 = index000 + 1,
              iter000 = iter000 + 1) {
          input = (vector000->theArray)[index000];
          i = iter000;
          self->setInputValues(input);
          outputs[i] = self->forwardPropagateInputs();
        }
      }
      return (self->outputBatch);
    }
  }
}

oneDFloatArray* ChameleonBatchNeuralNetwork::copyInputError() {
  { ChameleonBatchNeuralNetwork* self = this;

    { oneDFloatArray* inputerror = self->inputError;
      oneDFloatArray* copyerror = new1DFloatArray(inputerror->dim1);

      copyFloatValuesToBuffer(inputerror, copyerror->theArray, 0, inputerror->dim1);
      return (copyerror);
    }
  }
}

void ChameleonBatchNeuralNetwork::batchBackwardPropagateError() {
  { ChameleonBatchNeuralNetwork* self = this;

    { Object** targets = self->targetBatch->theArray;
      VectorSequence* errors = self->inputErrorBatch;
      double output = 0.0;
      double error = 0.0;

      errors->clear();
      { Object* input = NULL;
        VectorSequence* vector000 = self->inputBatch;
        int index000 = 0;
        int length000 = vector000->sequenceLength;
        int i = NULL_INTEGER;
        int iter000 = 0;

        for  (; index000 < length000; 
              index000 = index000 + 1,
              iter000 = iter000 + 1) {
          input = (vector000->theArray)[index000];
          i = iter000;
          self->setInputValues(input);
          output = self->forwardPropagateInputs();
          error = ((FloatWrapper*)(targets[i]))->wrapperValue - output;
          self->backwardPropagateError(error);
          errors->insert(self->copyInputError());
        }
      }
    }
  }
}

void ChameleonBatchNeuralNetwork::batchUpdateNetworkWeights() {
  { ChameleonBatchNeuralNetwork* self = this;

    { Object** targets = self->targetBatch->theArray;
      double output = 0.0;
      double error = 0.0;

      { Object* input = NULL;
        VectorSequence* vector000 = self->inputBatch;
        int index000 = 0;
        int length000 = vector000->sequenceLength;
        int i = NULL_INTEGER;
        int iter000 = 0;

        for  (; index000 < length000; 
              index000 = index000 + 1,
              iter000 = iter000 + 1) {
          input = (vector000->theArray)[index000];
          i = iter000;
          self->setInputValues(input);
          output = self->forwardPropagateInputs();
          error = ((FloatWrapper*)(targets[i]))->wrapperValue - output;
          self->backwardPropagateError(error);
          self->updateNetworkWeights(error);
        }
      }
    }
  }
}

twoDLongArray* new2DLongArray(int dim2, int dim1) {
  { twoDLongArray* self = NULL;

    self = new twoDLongArray();
    self->dim2 = dim2;
    self->dim1 = dim1;
    self->theArray = NULL;
    self->initializeDimensionalArray();
    return (self);
  }
}

Surrogate* twoDLongArray::primaryType() {
  { twoDLongArray* self = this;

    return (SGT_CHAMELEON_LOGIC_2D_LONG_ARRAY);
  }
}

int twoDLongArray::twoDArefAddress(int i, int j) {
  // Return the 1D address of the element at position `[i, j]'.
  // This is useful for fast element-wise iteration that doesn't need arithmetic.
  { twoDLongArray* self = this;

    return ((i * self->dim2) + j);
  }
}

long long int twoDLongArray::twoDArefSetter(long long int value, int i, int j) {
  // Set the element of `self' at position `[i, j]' to `value'
  // and return the result.
  { twoDLongArray* self = this;

    return (self->theArray[(i * self->dim2) + j] = value);
  }
}

long long int twoDLongArray::twoDAref(int i, int j) {
  // Return the element of `self' at position `[i, j]'.
  { twoDLongArray* self = this;

    return (self->theArray[(i * self->dim2) + j]);
  }
}

int twoDLongArray::length() {
  // Return the total number of elements in `self'.
  { twoDLongArray* self = this;

    return (self->dim1 * self->dim2);
  }
}

int twoDLongArray::oneDArefAddress(int i) {
  // Return the 1D address of the element at position `[i]'.
  // This is useful for fast element-wise iteration that doesn't need arithmetic.
  { twoDLongArray* self = this;

    return (i);
  }
}

long long int twoDLongArray::oneDArefSetter(long long int value, int i) {
  // Set the element of `self' at position `[i]' to `value'
  // and return the result.
  { twoDLongArray* self = this;

    return (self->theArray[i] = value);
  }
}

long long int twoDLongArray::oneDAref(int i) {
  // Return the element of `self' at position `[i]'.
  { twoDLongArray* self = this;

    return (self->theArray[i]);
  }
}

void twoDLongArray::initializeArray(long long int initialvalue) {
  // Initialize the elements of `self' with `initialValue'.
  { twoDLongArray* self = this;

    { long long int* array = self->theArray;

      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = self->length() - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          array[i] = initialvalue;
        }
      }
    }
  }
}

void twoDLongArray::initializeDimensionalArray() {
  { twoDLongArray* self = this;

    self->theArray = new (PointerFreeGC)long long int[self->length()];
  }
}

long long int* twoDLongArray::theArrayReader() {
  { twoDLongArray* self = this;

    return (self->theArray);
  }
}

TensorflowBatchNeuralNetwork* newTensorflowBatchNeuralNetwork() {
  { TensorflowBatchNeuralNetwork* self = NULL;

    self = new TensorflowBatchNeuralNetwork();
    self->nVectorArgumentInputs = -1;
    self->nVectorArgumentSpecs = -1;
    self->nVectorArguments = -1;
    self->model = NULL;
    self->proposition = NULL;
    self->inputErrorBatch = NULL;
    self->outputBatch = NULL;
    self->targetBatchLength = 0;
    self->targetBatch = NULL;
    self->vectorBatchLength = 0;
    self->vectorBatch = NULL;
    self->keyBatch = NULL;
    self->inputBatchLength = 0;
    self->inputBatch = NULL;
    self->inputModifiedP = true;
    return (self);
  }
}

Surrogate* TensorflowBatchNeuralNetwork::primaryType() {
  { TensorflowBatchNeuralNetwork* self = this;

    return (SGT_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORK);
  }
}

Object* accessTensorflowBatchNeuralNetworkSlotValue(TensorflowBatchNeuralNetwork* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_CHAMELEON_LOGIC_INPUT_MODIFIEDp) {
    if (setvalueP) {
      self->inputModifiedP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->inputModifiedP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_INPUT_BATCH) {
    if (setvalueP) {
      self->inputBatch = ((twoDFloatArray*)(value));
    }
    else {
      value = self->inputBatch;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_INPUT_BATCH_LENGTH) {
    if (setvalueP) {
      self->inputBatchLength = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->inputBatchLength);
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_KEY_BATCH) {
    if (setvalueP) {
      self->keyBatch = ((VectorSequence*)(value));
    }
    else {
      value = self->keyBatch;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_VECTOR_BATCH) {
    if (setvalueP) {
      self->vectorBatch = ((twoDLongArray*)(value));
    }
    else {
      value = self->vectorBatch;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_VECTOR_BATCH_LENGTH) {
    if (setvalueP) {
      self->vectorBatchLength = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->vectorBatchLength);
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_TARGET_BATCH) {
    if (setvalueP) {
      self->targetBatch = ((oneDFloatArray*)(value));
    }
    else {
      value = self->targetBatch;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_TARGET_BATCH_LENGTH) {
    if (setvalueP) {
      self->targetBatchLength = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->targetBatchLength);
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_OUTPUT_BATCH) {
    if (setvalueP) {
      self->outputBatch = ((oneDFloatArray*)(value));
    }
    else {
      value = self->outputBatch;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_INPUT_ERROR_BATCH) {
    if (setvalueP) {
      self->inputErrorBatch = ((twoDFloatArray*)(value));
    }
    else {
      value = self->inputErrorBatch;
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

void TensorflowBatchNeuralNetwork::printNetworkArrays() {
  { TensorflowBatchNeuralNetwork* self = this;

    { int batchlength = self->inputBatchLength;

      std::cout << "input batch (" << batchlength << "):" << std::endl;
      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = batchlength - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          { int j = NULL_INTEGER;
            int iter001 = 0;
            int upperBound001 = self->inputBatch->dim2 - 1;

            for  (; iter001 <= upperBound001; 
                  iter001 = iter001 + 1) {
              j = iter001;
              std::cout << self->inputBatch->theArray[(i * self->inputBatch->dim2) + j] << " ";
            }
          }
          std::cout << std::endl;
        }
      }
      batchlength = self->targetBatchLength;
      std::cout << "target batch (" << batchlength << "):" << std::endl;
      { int i = NULL_INTEGER;
        int iter002 = 0;
        int upperBound002 = batchlength - 1;

        for  (; iter002 <= upperBound002; 
              iter002 = iter002 + 1) {
          i = iter002;
          std::cout << self->targetBatch->theArray[i] << " ";
        }
      }
      std::cout << std::endl;
      batchlength = self->inputBatchLength;
      std::cout << "output batch (" << batchlength << "):" << std::endl;
      { int i = NULL_INTEGER;
        int iter003 = 0;
        int upperBound003 = batchlength - 1;

        for  (; iter003 <= upperBound003; 
              iter003 = iter003 + 1) {
          i = iter003;
          std::cout << self->outputBatch->theArray[i] << " ";
        }
      }
      std::cout << std::endl;
      std::cout << "input error batch (" << batchlength << "):" << std::endl;
      { int i = NULL_INTEGER;
        int iter004 = 0;
        int upperBound004 = batchlength - 1;

        for  (; iter004 <= upperBound004; 
              iter004 = iter004 + 1) {
          i = iter004;
          { int j = NULL_INTEGER;
            int iter005 = 0;
            int upperBound005 = self->inputErrorBatch->dim2 - 1;

            for  (; iter005 <= upperBound005; 
                  iter005 = iter005 + 1) {
              j = iter005;
              std::cout << self->inputErrorBatch->theArray[(i * self->inputErrorBatch->dim2) + j] << " ";
            }
          }
          std::cout << std::endl;
        }
      }
    }
  }
}

void TensorflowBatchNeuralNetwork::allocateNetworkArrays(int numIn, int numHidden, int numOut) {
  { TensorflowBatchNeuralNetwork* self = this;

    TensorflowNeuralNetwork::allocateNetworkArrays(numIn, numHidden, numOut);
    { int tvnumin = self->numberOfTruthValueArguments(self->proposition) + 1;

      self->inputBatch = new2DFloatArray(tvnumin, oNEURAL_NETWORK_BATCH_SIZEo);
      self->keyBatch = newVectorSequence(oNEURAL_NETWORK_BATCH_SIZEo);
      if (self->numberOfVectorArgumentSpecs(NULL) > 0) {
        self->vectorBatch = new2DLongArray(self->numberOfVectorArgumentSpecs(NULL), oNEURAL_NETWORK_BATCH_SIZEo);
      }
      self->targetBatch = new1DFloatArray(oNEURAL_NETWORK_BATCH_SIZEo);
      self->outputBatch = new1DFloatArray(oNEURAL_NETWORK_BATCH_SIZEo);
      self->inputErrorBatch = new2DFloatArray(tvnumin, oNEURAL_NETWORK_BATCH_SIZEo);
      self->inputModifiedP = true;
    }
  }
}

void TensorflowBatchNeuralNetwork::buildPropositionNetwork(Proposition* prop) {
  // Build a neural network for the proposition `prop'.  This builds a two-layer
  // perceptron network whose input nodes are activated by the truth of `prop's arguments and whose
  // output node computes the truth of `prop'.
  { TensorflowBatchNeuralNetwork* self = this;

    { int numIn = self->numberOfTruthValueArguments(prop) + self->numberOfVectorArgumentInputs(prop) + 1;
      int numHidden = stella::integerMin(numIn + 0, 20);

      if (numIn > 100) {
        numHidden = stella::floor(numIn / 10.0) + 10;
      }
      self->proposition = prop;
      self->allocateNetworkArrays(numIn, numHidden, 1);
      { Keyword* testValue000 = prop->kind;

        if ((testValue000 == KWD_CHAMELEON_AND) ||
            (testValue000 == KWD_CHAMELEON_OR)) {
          self->initializeNetworkWeights();
        }
        else {
          self->initializeNetworkWeights();
        }
      }
      self->linkNeuralNetwork(prop);
    }
  }
}

int TensorflowBatchNeuralNetwork::numberOfInputs() {
  // Return the number of input values expected by `self' (ignores bias unit).
  { TensorflowBatchNeuralNetwork* self = this;

    return (self->inputBatch->dim2 - 1);
  }
}

double TensorflowBatchNeuralNetwork::nthInput(int n) {
  // Return the 0-based `n'-th proposition input of `self' (ignores bias unit).
  { TensorflowBatchNeuralNetwork* self = this;

    n = n;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "nth-input: not supported on: " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

double TensorflowBatchNeuralNetwork::nthInputError(int n) {
  // Return the 0-based `n'-th proposition input error of `self' (ignores bias unit).
  { TensorflowBatchNeuralNetwork* self = this;

    n = n;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "nth-input-error: not supported on: " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void TensorflowBatchNeuralNetwork::setInputValues(Object* values) {
  // Set the current truth-value inputs of the network `self' to float `values' in sequence.
  // Missing inputs will be set to 0.0, extra values will be ignored.
  { TensorflowBatchNeuralNetwork* self = this;

    TensorflowNeuralNetwork::setInputValues(values);
  }
}

Object* TensorflowBatchNeuralNetwork::getVectorArgumentSpec(Object* arg) {
  // Generate a single argument spec for `arg' that can be used for `set-vector-input-values'.
  // `arg' can either be a proposition or justification.
  { TensorflowBatchNeuralNetwork* self = this;

    { Object* spec = TensorflowNeuralNetwork::getVectorArgumentSpec(arg);
      Cons* evalargs = NIL;

      if (safePrimaryType(spec) == SGT_CHAMELEON_STELLA_CONS) {
        { Object* spec000 = spec;
          Cons* spec = ((Cons*)(spec000));

          { Object* elt = NULL;
            Cons* iter000 = spec;
            Cons* collect000 = NULL;

            for  (; !(iter000 == NIL); 
                  iter000 = iter000->rest) {
              elt = iter000->value;
              if (longIntegerP(elt)) {
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(elt, NIL);
                    if (evalargs == NIL) {
                      evalargs = collect000;
                    }
                    else {
                      addConsToEndOfConsList(evalargs, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(elt, NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
          }
        }
      }
      else {
      }
      if (!(evalargs == NIL)) {
        return (evalargs);
      }
      else {
        return (spec);
      }
    }
  }
}

void TensorflowBatchNeuralNetwork::setVectorInputValues(Object* vectorspecs) {
  // Set the current vector inputs of the network `self' to the vectors described by `vectorSpecs'.
  // Each vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs
  // are translated into actual numeric vectors such as embeddings is specific to the particular neural network type.
  { TensorflowBatchNeuralNetwork* self = this;

    TensorflowNeuralNetwork::setVectorInputValues(vectorspecs);
  }
}

double TensorflowBatchNeuralNetwork::forwardPropagateInputs() {
  // Activates the current inputs of the network `self' to compute its output.
  // Sets `self's `output' slot and returns the computed value.  Reads input activations and
  // weights and updates hidden and output activations.
  { TensorflowBatchNeuralNetwork* self = this;

    return (TensorflowNeuralNetwork::forwardPropagateInputs());
  }
}

void TensorflowBatchNeuralNetwork::clearBatchArrays() {
  { TensorflowBatchNeuralNetwork* self = this;

    self->inputBatchLength = 0;
    self->keyBatch->clear();
    self->vectorBatchLength = 0;
    self->targetBatchLength = 0;
    self->inputModifiedP = true;
  }
}

int TensorflowBatchNeuralNetwork::currentBatchSize() {
  { TensorflowBatchNeuralNetwork* self = this;

    return (self->inputBatchLength);
  }
}

boolean TensorflowBatchNeuralNetwork::batchIsFullP() {
  { TensorflowBatchNeuralNetwork* self = this;

    return (self->inputBatchLength >= oNEURAL_NETWORK_BATCH_SIZEo);
  }
}

void TensorflowBatchNeuralNetwork::pushInputValues(Object* key, Object* values) {
  { TensorflowBatchNeuralNetwork* self = this;

    { twoDFloatArray* inputbatch = self->inputBatch;
      double* inputarray = inputbatch->theArray;
      int start = (self->inputBatchLength * inputbatch->dim2) + 0;

      inputarray[start] = 1.0;
      copyFloatValuesToBuffer(values, inputarray, start + 1, start + inputbatch->dim2);
      self->inputBatchLength = self->inputBatchLength + 1;
      self->keyBatch->insert(key);
      self->inputModifiedP = true;
    }
  }
}

void TensorflowBatchNeuralNetwork::pushVectorInputValues(Object* vectorspecs) {
  { TensorflowBatchNeuralNetwork* self = this;

    if (((boolean)(self->vectorBatch))) {
      { twoDLongArray* vectorbatch = self->vectorBatch;
        long long int* vectorarray = vectorbatch->theArray;
        int start = (self->vectorBatchLength * vectorbatch->dim2) + 0;
        int i = start;

        { Surrogate* testValue000 = safePrimaryType(vectorspecs);

          if (subtypeOfP(testValue000, SGT_CHAMELEON_STELLA_VECTOR)) {
            { Object* vectorspecs000 = vectorspecs;
              Vector* vectorspecs = ((Vector*)(vectorspecs000));

              { Object* spec = NULL;
                Vector* vector000 = vectorspecs;
                int index000 = 0;
                int length000 = vector000->length();

                for  (; index000 < length000; 
                      index000 = index000 + 1) {
                  spec = (vector000->theArray)[index000];
                  if (safePrimaryType(spec) == SGT_CHAMELEON_STELLA_CONS) {
                    { Object* spec000 = spec;
                      Cons* spec = ((Cons*)(spec000));

                      { Object* elt = NULL;
                        Cons* iter000 = spec;

                        for (; !(iter000 == NIL); iter000 = iter000->rest) {
                          elt = iter000->value;
                          if (subtypeOfLongIntegerP(safePrimaryType(elt))) {
                            { Object* elt000 = elt;
                              LongIntegerWrapper* elt = ((LongIntegerWrapper*)(elt000));

                              vectorarray[i] = elt->wrapperValue;
                              i = i + 1;
                            }
                          }
                          else {
                            { OutputStringStream* stream000 = newOutputStringStream();

                              *(stream000->nativeStream) << "push-vector-input-values: unexpected vector argument spec: " << "`" << elt << "'";
                              throw *newStellaException(stream000->theStringReader());
                            }
                          }
                        }
                      }
                    }
                  }
                  else {
                  }
                }
              }
            }
          }
          else if (testValue000 == SGT_CHAMELEON_STELLA_CONS) {
            { Object* vectorspecs001 = vectorspecs;
              Cons* vectorspecs = ((Cons*)(vectorspecs001));

              { Object* spec = NULL;
                Cons* iter001 = vectorspecs;

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  spec = iter001->value;
                  if (safePrimaryType(spec) == SGT_CHAMELEON_STELLA_CONS) {
                    { Object* spec001 = spec;
                      Cons* spec = ((Cons*)(spec001));

                      { Object* elt = NULL;
                        Cons* iter002 = spec;

                        for (; !(iter002 == NIL); iter002 = iter002->rest) {
                          elt = iter002->value;
                          if (subtypeOfLongIntegerP(safePrimaryType(elt))) {
                            { Object* elt001 = elt;
                              LongIntegerWrapper* elt = ((LongIntegerWrapper*)(elt001));

                              vectorarray[i] = elt->wrapperValue;
                              i = i + 1;
                            }
                          }
                          else {
                            { OutputStringStream* stream001 = newOutputStringStream();

                              *(stream001->nativeStream) << "push-vector-input-values: unexpected vector argument spec: " << "`" << elt << "'";
                              throw *newStellaException(stream001->theStringReader());
                            }
                          }
                        }
                      }
                    }
                  }
                  else {
                  }
                }
              }
            }
          }
          else {
            { OutputStringStream* stream002 = newOutputStringStream();

              *(stream002->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
              throw *newStellaException(stream002->theStringReader());
            }
          }
        }
        if (i > start) {
          self->vectorBatchLength = self->vectorBatchLength + 1;
          self->inputModifiedP = true;
        }
      }
    }
  }
}

void TensorflowBatchNeuralNetwork::pushTargetValue(double value) {
  { TensorflowBatchNeuralNetwork* self = this;

    { int cursor = self->targetBatchLength;

      self->targetBatch->theArray[cursor] = value;
      self->targetBatchLength = cursor + 1;
      self->inputModifiedP = true;
    }
  }
}

Object* TensorflowBatchNeuralNetwork::nthBatchKey(int n) {
  { TensorflowBatchNeuralNetwork* self = this;

    return ((self->keyBatch->theArray)[n]);
  }
}

double TensorflowBatchNeuralNetwork::nthKthBatchInputError(int n, int k) {
  { TensorflowBatchNeuralNetwork* self = this;

    return (self->inputErrorBatch->theArray[(n * self->inputErrorBatch->dim2) + k + 1]);
  }
}

double TensorflowBatchNeuralNetwork::nthBatchOutput(int n) {
  { TensorflowBatchNeuralNetwork* self = this;

    return (self->outputBatch->theArray[n]);
  }
}

oneDFloatArray* TensorflowBatchNeuralNetwork::batchForwardPropagateInputs() {
  { TensorflowBatchNeuralNetwork* self = this;

    ((void  (*) ())((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_FORWARD_PROPAGATE_INPUTS->symbolValueAndPlist->value))->wrapperValue)();
    return (self->outputBatch);
  }
}

void TensorflowBatchNeuralNetwork::batchBackwardPropagateError() {
  { TensorflowBatchNeuralNetwork* self = this;

    ((void  (*) ())((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_BACKWARD_PROPAGATE_ERROR->symbolValueAndPlist->value))->wrapperValue)();
  }
}

void TensorflowBatchNeuralNetwork::batchUpdateNetworkWeights() {
  { TensorflowBatchNeuralNetwork* self = this;

    ((void  (*) ())((FunctionCodeWrapper*)(SYM_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_UPDATE_NETWORK_WEIGHTS->symbolValueAndPlist->value))->wrapperValue)();
  }
}

NetworkProofQueue* newNetworkProofQueue() {
  { NetworkProofQueue* self = NULL;

    self = new NetworkProofQueue();
    self->nQueued = 0;
    self->minBatchSize = stella::floor(oNEURAL_NETWORK_BATCH_SIZEo * 0.8);
    self->activeNetworks = newHashSet();
    self->prerequisites = newKeyValueMap();
    self->dependents = newKeyValueMap();
    return (self);
  }
}

Surrogate* NetworkProofQueue::primaryType() {
  { NetworkProofQueue* self = this;

    return (SGT_CHAMELEON_LOGIC_NETWORK_PROOF_QUEUE);
  }
}

Object* accessNetworkProofQueueSlotValue(NetworkProofQueue* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_CHAMELEON_LOGIC_DEPENDENTS) {
    if (setvalueP) {
      self->dependents = ((KeyValueMap*)(value));
    }
    else {
      value = self->dependents;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_PREREQUISITES) {
    if (setvalueP) {
      self->prerequisites = ((KeyValueMap*)(value));
    }
    else {
      value = self->prerequisites;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_ACTIVE_NETWORKS) {
    if (setvalueP) {
      self->activeNetworks = ((HashSet*)(value));
    }
    else {
      value = self->activeNetworks;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_MIN_BATCH_SIZE) {
    if (setvalueP) {
      self->minBatchSize = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->minBatchSize);
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_N_QUEUED) {
    if (setvalueP) {
      self->nQueued = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->nQueued);
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

NetworkProofForwardQueue* newNetworkProofForwardQueue() {
  { NetworkProofForwardQueue* self = NULL;

    self = new NetworkProofForwardQueue();
    self->nQueued = 0;
    self->minBatchSize = stella::floor(oNEURAL_NETWORK_BATCH_SIZEo * 0.8);
    self->activeNetworks = newHashSet();
    self->prerequisites = newKeyValueMap();
    self->dependents = newKeyValueMap();
    return (self);
  }
}

Surrogate* NetworkProofForwardQueue::primaryType() {
  { NetworkProofForwardQueue* self = this;

    return (SGT_CHAMELEON_LOGIC_NETWORK_PROOF_FORWARD_QUEUE);
  }
}

NetworkProofBackwardQueue* newNetworkProofBackwardQueue() {
  { NetworkProofBackwardQueue* self = NULL;

    self = new NetworkProofBackwardQueue();
    self->nQueued = 0;
    self->minBatchSize = stella::floor(oNEURAL_NETWORK_BATCH_SIZEo * 0.8);
    self->activeNetworks = newHashSet();
    self->prerequisites = newKeyValueMap();
    self->dependents = newKeyValueMap();
    return (self);
  }
}

Surrogate* NetworkProofBackwardQueue::primaryType() {
  { NetworkProofBackwardQueue* self = this;

    return (SGT_CHAMELEON_LOGIC_NETWORK_PROOF_BACKWARD_QUEUE);
  }
}

NetworkProofUpdateQueue* newNetworkProofUpdateQueue() {
  { NetworkProofUpdateQueue* self = NULL;

    self = new NetworkProofUpdateQueue();
    self->nQueued = 0;
    self->minBatchSize = stella::floor(oNEURAL_NETWORK_BATCH_SIZEo * 0.8);
    self->activeNetworks = newHashSet();
    self->prerequisites = newKeyValueMap();
    self->dependents = newKeyValueMap();
    return (self);
  }
}

Surrogate* NetworkProofUpdateQueue::primaryType() {
  { NetworkProofUpdateQueue* self = this;

    return (SGT_CHAMELEON_LOGIC_NETWORK_PROOF_UPDATE_QUEUE);
  }
}

void addNetworkProofDependencyLink(KeyValueMap* table, Justification* subject, Justification* object) {
  { Cons* links = ((Cons*)(table->lookup(subject)));

    if (!((boolean)(links))) {
      table->insertAt(subject, cons(object, NIL));
    }
    else if (links == NIL) {
      table->insertAt(subject, cons(object, NIL));
    }
    else if (!links->membP(object)) {
      links->concatenate(cons(object, NIL), 0);
    }
  }
}

void removeNetworkProofDependencyLink(KeyValueMap* table, Justification* subject, Justification* object) {
  { Cons* links = ((Cons*)(table->lookup(subject)));

    if (((boolean)(links)) &&
        (!(links == NIL))) {
      links = links->remove(object);
      if (links == NIL) {
        table->removeAt(subject);
      }
    }
  }
}

void NetworkProofQueue::addDependent(Justification* prerequisite, Justification* dependent) {
  { NetworkProofQueue* queue = this;

    addNetworkProofDependencyLink(queue->dependents, prerequisite, dependent);
    addNetworkProofDependencyLink(queue->prerequisites, dependent, prerequisite);
  }
}

void NetworkProofQueue::removeDependent(Justification* prerequisite, Justification* dependent) {
  { NetworkProofQueue* queue = this;

    removeNetworkProofDependencyLink(queue->dependents, prerequisite, dependent);
    removeNetworkProofDependencyLink(queue->prerequisites, dependent, prerequisite);
  }
}

Cons* NetworkProofQueue::getDependents(Justification* prerequisite) {
  { NetworkProofQueue* queue = this;

    { Cons* temp000 = ((Cons*)(queue->dependents->lookup(prerequisite)));

      { Cons* value000 = (((boolean)(temp000)) ? temp000 : NIL);

        return (((Cons*)(value000)));
      }
    }
  }
}

boolean NetworkProofQueue::hasDependentP(Justification* prerequisite, Justification* dependent) {
  { NetworkProofQueue* queue = this;

    return (queue->getDependents(prerequisite)->membP(dependent));
  }
}

Cons* NetworkProofQueue::getPrerequisites(Justification* dependent) {
  { NetworkProofQueue* queue = this;

    { Cons* temp000 = ((Cons*)(queue->prerequisites->lookup(dependent)));

      { Cons* value000 = (((boolean)(temp000)) ? temp000 : NIL);

        return (((Cons*)(value000)));
      }
    }
  }
}

boolean NetworkProofQueue::hasPrerequisiteP(Justification* dependent, Justification* prerequisite) {
  { NetworkProofQueue* queue = this;

    return (queue->getPrerequisites(dependent)->membP(prerequisite));
  }
}

void NetworkProofQueue::batchProcessCachedNetworkProof(Justification* proof) {
  { NetworkProofQueue* queue = this;

    proof = proof;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "batch-process-cached-network-proof: not implemented on: " << "`" << queue << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NetworkProofQueue::queueNetworkOperation(Justification* proof) {
  { NetworkProofQueue* queue = this;

    proof = proof;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "queue-network-operation: not implemented on: " << "`" << queue << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NetworkProofQueue::executeNetworkOperation(NeuralNetwork* net, boolean forceP) {
  { NetworkProofQueue* queue = this;

    {
      net = net;
      forceP = forceP;
    }
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "execute-network-operation: not implemented on: " << "`" << queue << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void NetworkProofForwardQueue::batchProcessCachedNetworkProof(Justification* proof) {
  // Compute the same partial match score as the call to `compute-partial-truth'
  // that generated `proof' (which is assumed to have been compacted with a call to
  // `compact-partial-proof-to-network-proof'.  The score will only be identical of course, if
  // the various networks and their weights have not yet been updated during learning.
  { NetworkProofForwardQueue* queue = this;

    { Keyword* testValue000 = proof->inferenceRule;

      if (testValue000 == KWD_CHAMELEON_PRIMITIVE_STRATEGY) {
        { Justification* dep = NULL;
          Cons* iter000 = queue->getDependents(proof);

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            dep = ((Justification*)(iter000->value));
            queue->notifyOfCompletion(dep, proof);
          }
        }
      }
      else if ((testValue000 == KWD_CHAMELEON_AND_INTRODUCTION) ||
          (testValue000 == KWD_CHAMELEON_OR_INTRODUCTION)) {
        { NeuralNetwork* net = getJustificationNeuralNetwork(proof);

          { Justification* ant = NULL;
            Cons* iter001 = proof->antecedents;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              ant = ((Justification*)(iter001->value));
              if (!net->ignoredValueArgumentP(ant->proposition)) {
                queue->addDependent(ant, proof);
              }
            }
          }
          { Justification* ant = NULL;
            Cons* iter002 = proof->antecedents;

            for (; !(iter002 == NIL); iter002 = iter002->rest) {
              ant = ((Justification*)(iter002->value));
              if (!net->ignoredValueArgumentP(ant->proposition)) {
                queue->batchProcessCachedNetworkProof(ant);
              }
            }
          }
        }
      }
      else if ((testValue000 == KWD_CHAMELEON_MULTIPLE_PROOFS) ||
          ((testValue000 == KWD_CHAMELEON_DISPROOF) ||
           (testValue000 == KWD_CHAMELEON_GOAL_COMPLEMENT))) {
        { Justification* ant = NULL;
          Cons* iter003 = proof->antecedents;

          for (; !(iter003 == NIL); iter003 = iter003->rest) {
            ant = ((Justification*)(iter003->value));
            queue->addDependent(ant, proof);
          }
        }
        { Justification* ant = NULL;
          Cons* iter004 = proof->antecedents;

          for (; !(iter004 == NIL); iter004 = iter004->rest) {
            ant = ((Justification*)(iter004->value));
            queue->batchProcessCachedNetworkProof(ant);
          }
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

void NetworkProofQueue::notifyOfCompletion(Justification* proof, Justification* prerequisite) {
  // Notify `proof' that one of its `prerequisite's had its computation completed.
  { NetworkProofQueue* queue = this;

    queue->removeDependent(prerequisite, proof);
    if (queue->getPrerequisites(proof) == NIL) {
      queue->queueNetworkOperation(proof);
    }
  }
}

void NetworkProofQueue::queueInputValues(NeuralNetwork* net, Justification* proof, Object* inputs, Object* vectorspecs) {
  // Queue `inputs' in `net's input batch.  Execute the current batch if we are full.
  { NetworkProofQueue* queue = this;

    queue->activeNetworks->insert(net);
    while (net->batchIsFullP()) {
      queue->executeNetworkOperation(net, true);
    }
    net->pushInputValues(proof, inputs);
    if (((boolean)(vectorspecs))) {
      net->pushVectorInputValues(vectorspecs);
    }
    queue->nQueued = queue->nQueued + 1;
  }
}

void NetworkProofForwardQueue::queueNetworkOperation(Justification* proof) {
  { NetworkProofForwardQueue* queue = this;

    { double score = 0.0;

      { Keyword* testValue000 = proof->inferenceRule;

        if (testValue000 == KWD_CHAMELEON_PRIMITIVE_STRATEGY) {
          throw *newStellaException("INTERNAL ERROR: unexpected justification type in batch forward computation");
        }
        else if ((testValue000 == KWD_CHAMELEON_AND_INTRODUCTION) ||
            (testValue000 == KWD_CHAMELEON_OR_INTRODUCTION)) {
          { NeuralNetwork* net = getJustificationNeuralNetwork(proof);
            Vector* inputs = stella::newVector(net->numberOfInputs());
            Vector* vectorargs = (net->hasVectorArgumentsP() ? stella::newVector(net->numberOfVectorArguments(NULL)) : ((Vector*)(NULL)));
            int index = -1;

            { Justification* ant = NULL;
              Cons* iter000 = proof->antecedents;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                ant = ((Justification*)(iter000->value));
                index = net->truthValueArgumentIndex(ant->proposition);
                if (index >= 0) {
                  score = ant->matchScore;
                  (inputs->theArray)[index] = (wrapFloat(score));
                }
                if (((boolean)(vectorargs))) {
                  index = net->vectorArgumentIndex(ant->proposition);
                  if (index >= 0) {
                    (vectorargs->theArray)[index] = (net->getVectorArgumentSpec(ant));
                  }
                }
              }
            }
            queue->queueInputValues(net, proof, inputs, vectorargs);
          }
        }
        else if (testValue000 == KWD_CHAMELEON_MULTIPLE_PROOFS) {
          { Cons* value000 = NIL;

            { Justification* ant = NULL;
              Cons* iter001 = proof->antecedents;
              Cons* collect000 = NULL;

              for  (; !(iter001 == NIL); 
                    iter001 = iter001->rest) {
                ant = ((Justification*)(iter001->value));
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(wrapFloat(ant->matchScore), NIL);
                    if (value000 == NIL) {
                      value000 = collect000;
                    }
                    else {
                      addConsToEndOfConsList(value000, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(wrapFloat(ant->matchScore), NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
            score = combineMultipleMatchScores(value000);
          }
          proof->matchScore = score;
          { Justification* dep = NULL;
            Cons* iter002 = queue->getDependents(proof);

            for (; !(iter002 == NIL); iter002 = iter002->rest) {
              dep = ((Justification*)(iter002->value));
              queue->notifyOfCompletion(dep, proof);
            }
          }
        }
        else if ((testValue000 == KWD_CHAMELEON_DISPROOF) ||
            (testValue000 == KWD_CHAMELEON_GOAL_COMPLEMENT)) {
          score = invertChameleonMatchScore(((Justification*)(proof->antecedents->value))->matchScore);
          proof->matchScore = score;
          { Justification* dep = NULL;
            Cons* iter003 = queue->getDependents(proof);

            for (; !(iter003 == NIL); iter003 = iter003->rest) {
              dep = ((Justification*)(iter003->value));
              queue->notifyOfCompletion(dep, proof);
            }
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
  }
}

void NetworkProofForwardQueue::executeNetworkOperation(NeuralNetwork* net, boolean forceP) {
  { NetworkProofForwardQueue* queue = this;

    { int batchsize = net->currentBatchSize();

      if ((batchsize > 0) &&
          (forceP ||
           (batchsize >= queue->minBatchSize))) {
        { double output = 0.0;
          Justification* proof = NULL;
          VectorSequence* scoredproofs = newVectorSequence(batchsize);

          net->batchForwardPropagateInputs();
          { int i = NULL_INTEGER;
            int iter000 = 0;
            int upperBound000 = batchsize - 1;

            for  (; iter000 <= upperBound000; 
                  iter000 = iter000 + 1) {
              i = iter000;
              output = net->nthBatchOutput(i);
              proof = ((Justification*)(net->nthBatchKey(i)));
              proof->matchScore = output;
              scoredproofs->insert(proof);
            }
          }
          queue->nQueued = queue->nQueued - batchsize;
          net->clearBatchArrays();
          { Justification* proof = NULL;
            VectorSequence* vector000 = scoredproofs;
            int index000 = 0;
            int length000 = vector000->sequenceLength;

            for  (; index000 < length000; 
                  index000 = index000 + 1) {
              proof = ((Justification*)((vector000->theArray)[index000]));
              { Justification* dep = NULL;
                Cons* iter001 = queue->getDependents(proof);

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  dep = ((Justification*)(iter001->value));
                  queue->notifyOfCompletion(dep, proof);
                }
              }
            }
          }
        }
      }
    }
  }
}

void NetworkProofQueue::executeAll() {
  // Execute queued ops in `queue' until there is nothing more to do.
  { NetworkProofQueue* queue = this;

    { int lowwatermark = queue->activeNetworks->length() * queue->minBatchSize;

      while (queue->nQueued > 0) {
        { NeuralNetwork* net = NULL;
          DictionaryIterator* iter000 = ((DictionaryIterator*)(queue->activeNetworks->allocateIterator()));

          for (; iter000->nextP(); ) {
            net = ((NeuralNetwork*)(iter000->value));
            queue->executeNetworkOperation(net, queue->nQueued <= lowwatermark);
          }
        }
      }
    }
  }
}

void NetworkProofBackwardQueue::batchProcessCachedNetworkProof(Justification* proof) {
  // Queue and process operations for `update-network-weights' for `proof'.
  { NetworkProofBackwardQueue* queue = this;

    { Keyword* testValue000 = proof->inferenceRule;

      if ((testValue000 == KWD_CHAMELEON_AND_INTRODUCTION) ||
          (testValue000 == KWD_CHAMELEON_OR_INTRODUCTION)) {
        { NeuralNetwork* net = getJustificationNeuralNetwork(proof);

          { Justification* ant = NULL;
            Cons* iter000 = proof->antecedents;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              ant = ((Justification*)(iter000->value));
              if ((!(ant->inferenceRule == KWD_CHAMELEON_PRIMITIVE_STRATEGY)) &&
                  (!net->ignoredValueArgumentP(ant->proposition))) {
                queue->addDependent(proof, ant);
              }
            }
          }
          if (queue->getPrerequisites(proof) == NIL) {
            queue->queueNetworkOperation(proof);
          }
          { Justification* ant = NULL;
            Cons* iter001 = proof->antecedents;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              ant = ((Justification*)(iter001->value));
              if ((!(ant->inferenceRule == KWD_CHAMELEON_PRIMITIVE_STRATEGY)) &&
                  (!net->ignoredValueArgumentP(ant->proposition))) {
                queue->batchProcessCachedNetworkProof(ant);
              }
            }
          }
        }
      }
      else if ((testValue000 == KWD_CHAMELEON_MULTIPLE_PROOFS) ||
          ((testValue000 == KWD_CHAMELEON_DISPROOF) ||
           (testValue000 == KWD_CHAMELEON_GOAL_COMPLEMENT))) {
        { Justification* ant = NULL;
          Cons* iter002 = proof->antecedents;

          for (; !(iter002 == NIL); iter002 = iter002->rest) {
            ant = ((Justification*)(iter002->value));
            if (!(ant->inferenceRule == KWD_CHAMELEON_PRIMITIVE_STRATEGY)) {
              queue->addDependent(proof, ant);
            }
          }
        }
        if (queue->getPrerequisites(proof) == NIL) {
          queue->queueNetworkOperation(proof);
        }
        { Justification* ant = NULL;
          Cons* iter003 = proof->antecedents;

          for (; !(iter003 == NIL); iter003 = iter003->rest) {
            ant = ((Justification*)(iter003->value));
            if (!(ant->inferenceRule == KWD_CHAMELEON_PRIMITIVE_STRATEGY)) {
              queue->batchProcessCachedNetworkProof(ant);
            }
          }
        }
      }
      else if (testValue000 == KWD_CHAMELEON_PRIMITIVE_STRATEGY) {
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

void NetworkProofBackwardQueue::queueNetworkOperation(Justification* proof) {
  { NetworkProofBackwardQueue* queue = this;

    { double score = 0.0;
      double error = proof->errorScore;

      { Keyword* testValue000 = proof->inferenceRule;

        if (testValue000 == KWD_CHAMELEON_PRIMITIVE_STRATEGY) {
          throw *newStellaException("INTERNAL ERROR: unexpected justification type in batch backward computation");
        }
        else if ((testValue000 == KWD_CHAMELEON_AND_INTRODUCTION) ||
            (testValue000 == KWD_CHAMELEON_OR_INTRODUCTION)) {
          { NeuralNetwork* net = getJustificationNeuralNetwork(proof);
            Vector* inputs = stella::newVector(net->numberOfInputs());
            Vector* vectorargs = (net->hasVectorArgumentsP() ? stella::newVector(net->numberOfVectorArguments(NULL)) : ((Vector*)(NULL)));
            int index = -1;

            { Justification* ant = NULL;
              Cons* iter000 = proof->antecedents;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                ant = ((Justification*)(iter000->value));
                index = net->truthValueArgumentIndex(ant->proposition);
                if (index >= 0) {
                  score = ant->matchScore;
                  (inputs->theArray)[index] = (wrapFloat(score));
                }
                if (((boolean)(vectorargs))) {
                  index = net->vectorArgumentIndex(ant->proposition);
                  if (index >= 0) {
                    (vectorargs->theArray)[index] = (net->getVectorArgumentSpec(ant));
                  }
                }
              }
            }
            score = proof->matchScore;
            queue->queueInputValues(net, proof, inputs, vectorargs);
            net->pushTargetValue(score + error);
          }
        }
        else if (testValue000 == KWD_CHAMELEON_MULTIPLE_PROOFS) {
          { Justification* ant = NULL;
            Cons* iter001 = proof->antecedents;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              ant = ((Justification*)(iter001->value));
              if (oRULE_COMBINATIONo == KWD_CHAMELEON_MAX) {
                ant->errorScore = error;
              }
              else if (oRULE_COMBINATIONo == KWD_CHAMELEON_NOISY_OR) {
                ant->errorScore = error * ant->matchScore;
              }
              else {
                { OutputStringStream* stream000 = newOutputStringStream();

                  *(stream000->nativeStream) << "`" << oRULE_COMBINATIONo << "'" << " is not a valid case option";
                  throw *newStellaException(stream000->theStringReader());
                }
              }
              queue->removeDependent(proof, ant);
            }
          }
        }
        else if ((testValue000 == KWD_CHAMELEON_DISPROOF) ||
            (testValue000 == KWD_CHAMELEON_GOAL_COMPLEMENT)) {
          ((Justification*)(proof->antecedents->value))->errorScore = error;
          queue->removeDependent(proof, ((Justification*)(proof->antecedents->value)));
        }
        else {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream001->theStringReader());
          }
        }
      }
    }
  }
}

void NetworkProofBackwardQueue::executeNetworkOperation(NeuralNetwork* net, boolean forceP) {
  { NetworkProofBackwardQueue* queue = this;

    { int batchsize = net->currentBatchSize();

      if ((batchsize > 0) &&
          (forceP ||
           (batchsize >= queue->minBatchSize))) {
        { double error = 0.0;
          int index = -1;
          Justification* proof = NULL;
          VectorSequence* processedproofs = newVectorSequence(batchsize);

          net->batchBackwardPropagateError();
          { int i = NULL_INTEGER;
            int iter000 = 0;
            int upperBound000 = batchsize - 1;

            for  (; iter000 <= upperBound000; 
                  iter000 = iter000 + 1) {
              i = iter000;
              proof = ((Justification*)(net->nthBatchKey(i)));
              processedproofs->insert(proof);
              { Justification* ant = NULL;
                Cons* iter001 = proof->antecedents;

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  ant = ((Justification*)(iter001->value));
                  if (!(ant->inferenceRule == KWD_CHAMELEON_PRIMITIVE_STRATEGY)) {
                    index = net->truthValueArgumentIndex(ant->proposition);
                    if (index >= 0) {
                      error = net->nthKthBatchInputError(i, index);
                      ant->errorScore = error;
                    }
                  }
                }
              }
            }
          }
          queue->nQueued = queue->nQueued - batchsize;
          net->clearBatchArrays();
          { Justification* proof = NULL;
            VectorSequence* vector000 = processedproofs;
            int index000 = 0;
            int length000 = vector000->sequenceLength;

            for  (; index000 < length000; 
                  index000 = index000 + 1) {
              proof = ((Justification*)((vector000->theArray)[index000]));
              { Justification* dep = NULL;
                Cons* iter002 = queue->getDependents(proof);

                for (; !(iter002 == NIL); iter002 = iter002->rest) {
                  dep = ((Justification*)(iter002->value));
                  queue->notifyOfCompletion(dep, proof);
                }
              }
            }
          }
        }
      }
    }
  }
}

void NetworkProofUpdateQueue::batchProcessCachedNetworkProof(Justification* proof) {
  // Queue and process operations for `update-network-weights' for `proof'.
  { NetworkProofUpdateQueue* queue = this;

    { Keyword* testValue000 = proof->inferenceRule;

      if ((testValue000 == KWD_CHAMELEON_AND_INTRODUCTION) ||
          (testValue000 == KWD_CHAMELEON_OR_INTRODUCTION)) {
        { NeuralNetwork* net = getJustificationNeuralNetwork(proof);

          queue->queueNetworkOperation(proof);
          { Justification* ant = NULL;
            Cons* iter000 = proof->antecedents;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              ant = ((Justification*)(iter000->value));
              if ((!(ant->inferenceRule == KWD_CHAMELEON_PRIMITIVE_STRATEGY)) &&
                  (!net->ignoredValueArgumentP(ant->proposition))) {
                queue->batchProcessCachedNetworkProof(ant);
              }
            }
          }
        }
      }
      else if ((testValue000 == KWD_CHAMELEON_MULTIPLE_PROOFS) ||
          ((testValue000 == KWD_CHAMELEON_DISPROOF) ||
           (testValue000 == KWD_CHAMELEON_GOAL_COMPLEMENT))) {
        { Justification* ant = NULL;
          Cons* iter001 = proof->antecedents;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            ant = ((Justification*)(iter001->value));
            if (!(ant->inferenceRule == KWD_CHAMELEON_PRIMITIVE_STRATEGY)) {
              queue->batchProcessCachedNetworkProof(ant);
            }
          }
        }
      }
      else if (testValue000 == KWD_CHAMELEON_PRIMITIVE_STRATEGY) {
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

void NetworkProofUpdateQueue::queueNetworkOperation(Justification* proof) {
  { NetworkProofUpdateQueue* queue = this;

    { double score = 0.0;
      double error = proof->errorScore;

      { Keyword* testValue000 = proof->inferenceRule;

        if ((testValue000 == KWD_CHAMELEON_PRIMITIVE_STRATEGY) ||
            ((testValue000 == KWD_CHAMELEON_MULTIPLE_PROOFS) ||
             ((testValue000 == KWD_CHAMELEON_DISPROOF) ||
              (testValue000 == KWD_CHAMELEON_GOAL_COMPLEMENT)))) {
          throw *newStellaException("INTERNAL ERROR: unexpected justification type in batch update computation");
        }
        else if ((testValue000 == KWD_CHAMELEON_AND_INTRODUCTION) ||
            (testValue000 == KWD_CHAMELEON_OR_INTRODUCTION)) {
          { NeuralNetwork* net = getJustificationNeuralNetwork(proof);
            Vector* inputs = stella::newVector(net->numberOfInputs());
            Vector* vectorargs = (net->hasVectorArgumentsP() ? stella::newVector(net->numberOfVectorArguments(NULL)) : ((Vector*)(NULL)));
            int index = -1;

            { Justification* ant = NULL;
              Cons* iter000 = proof->antecedents;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                ant = ((Justification*)(iter000->value));
                index = net->truthValueArgumentIndex(ant->proposition);
                if (index >= 0) {
                  score = ant->matchScore;
                  (inputs->theArray)[index] = (wrapFloat(score));
                }
                if (((boolean)(vectorargs))) {
                  index = net->vectorArgumentIndex(ant->proposition);
                  if (index >= 0) {
                    (vectorargs->theArray)[index] = (net->getVectorArgumentSpec(ant));
                  }
                }
              }
            }
            score = proof->matchScore;
            queue->queueInputValues(net, proof, inputs, vectorargs);
            net->pushTargetValue(score + error);
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
  }
}

void NetworkProofUpdateQueue::executeNetworkOperation(NeuralNetwork* net, boolean forceP) {
  { NetworkProofUpdateQueue* queue = this;

    { int batchsize = net->currentBatchSize();

      if ((batchsize > 0) &&
          (forceP ||
           (batchsize >= queue->minBatchSize))) {
        net->batchUpdateNetworkWeights();
        queue->nQueued = queue->nQueued - batchsize;
        net->clearBatchArrays();
      }
    }
  }
}

List* retrieveTrainingExamples(Cons* options) {
  // Retrieve a subset of current training examples defined via `cham/training-example'.
  { PropertyList* theoptions = parseOptions(options, listO(7, KWD_CHAMELEON_MODULE, SGT_CHAMELEON_STELLA_MODULE, KWD_CHAMELEON_LOCALp, SGT_CHAMELEON_STELLA_BOOLEAN, KWD_CHAMELEON_N_TRAIN, SGT_CHAMELEON_STELLA_INTEGER, NIL), true, true);
    Module* themodule = ((Module*)(theoptions->lookupWithDefault(KWD_CHAMELEON_MODULE, oMODULEo)));
    int numtraining = ((IntegerWrapper*)(theoptions->lookupWithDefault(KWD_CHAMELEON_N_TRAIN, wrapInteger(MOST_POSITIVE_INTEGER))))->wrapperValue;
    TrainingExample* example = NULL;
    List* examples = newList();

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, themodule);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      { QuerySolution* solution = NULL;
        DictionaryIterator* iter000 = ((DictionaryIterator*)(callRetrieve(cons(wrapInteger(numtraining), cons(listO(4, SYM_CHAMELEON_CHAMELEON_TRAINING_EXAMPLE, SYM_CHAMELEON_LOGIC_pP, SYM_CHAMELEON_LOGIC_pS, NIL), NIL)))->solutions->allocateIterator()));
        Cons* collect000 = NULL;

        for  (; iter000->nextP(); ) {
          solution = ((QuerySolution*)(iter000->value));
          { TrainingExample* self001 = newTrainingExample();

            self001->query = ((Cons*)(generateProposition(((Proposition*)((solution->bindings->theArray)[0])))));
            self001->score = coerceToFloat((solution->bindings->theArray)[1]);
            self001->module = themodule;
            example = self001;
          }
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(example, NIL);
              if (examples->theConsList == NIL) {
                examples->theConsList = collect000;
              }
              else {
                addConsToEndOfConsList(examples->theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(example, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      return (examples);
    }
  }
}

List* retrieveTrainingExamplesEvaluatorWrapper(Cons* arguments) {
  return (retrieveTrainingExamples(arguments));
}

Vector* selectTrainingExamples(Cons* options) {
  // Select a subset of currently defined training examples.  Currently the selection
  // is purely based on module and/or number.  Results will be shuffled if :shuffle? is TRUE (default).
  { PropertyList* theoptions = parseOptions(options, listO(9, KWD_CHAMELEON_MODULE, SGT_CHAMELEON_STELLA_MODULE, KWD_CHAMELEON_LOCALp, SGT_CHAMELEON_STELLA_BOOLEAN, KWD_CHAMELEON_N_TRAIN, SGT_CHAMELEON_STELLA_INTEGER, KWD_CHAMELEON_SHUFFLEp, SGT_CHAMELEON_STELLA_BOOLEAN, NIL), true, false);
    List* trainingexamples = retrieveTrainingExamples(consList(2, KWD_CHAMELEON_OPTIONS, theoptions))->concatenate(oTRAINING_EXAMPLESo, 0);
    Module* themodule = ((Module*)(theoptions->lookupWithDefault(KWD_CHAMELEON_MODULE, oMODULEo)));
    boolean localP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_CHAMELEON_LOCALp, FALSE_WRAPPER))));
    int numtraining = ((IntegerWrapper*)(theoptions->lookupWithDefault(KWD_CHAMELEON_N_TRAIN, wrapInteger(MOST_POSITIVE_INTEGER))))->wrapperValue;
    boolean shuffleP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_CHAMELEON_SHUFFLEp, TRUE_WRAPPER))));
    VectorSequence* examples = newVectorSequence(100);

    { TrainingExample* exp = NULL;
      Cons* iter000 = trainingexamples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        exp = ((TrainingExample*)(iter000->value));
        if (numtraining > 0) {
          if ((!((boolean)(exp->module))) ||
              ((exp->module == themodule) ||
               ((!localP) &&
                visibleFromP(exp->module, themodule)))) {
            examples->insert(exp);
            numtraining = numtraining - 1;
          }
        }
      }
    }
    examples->arraySize = examples->sequenceLength;
    if (shuffleP) {
      shuffleVector(examples);
    }
    return (examples);
  }
}

Vector* selectTrainingExamplesEvaluatorWrapper(Cons* arguments) {
  return (selectTrainingExamples(arguments));
}

PropertyList* normalizeChameleonTrainingOptions(Object* options) {
  // Normalize and provide defaults for `options' supplied
  // to `train-chameleon-neural-networks'.
  { PropertyList* theoptions = parseOptions(options, listO(19, KWD_CHAMELEON_MODULE, SGT_CHAMELEON_STELLA_MODULE, KWD_CHAMELEON_LOCALp, SGT_CHAMELEON_STELLA_BOOLEAN, KWD_CHAMELEON_EPOCHS, SGT_CHAMELEON_STELLA_INTEGER, KWD_CHAMELEON_N_TRAIN, SGT_CHAMELEON_STELLA_INTEGER, KWD_CHAMELEON_PRINT_CYCLE, SGT_CHAMELEON_STELLA_INTEGER, KWD_CHAMELEON_ERROR_CUTOFF, SGT_CHAMELEON_STELLA_FLOAT, KWD_CHAMELEON_SHUFFLEp, SGT_CHAMELEON_STELLA_BOOLEAN, KWD_CHAMELEON_BATCHp, SGT_CHAMELEON_STELLA_BOOLEAN, KWD_CHAMELEON_EXAMPLES, SGT_CHAMELEON_STELLA_OBJECT, NIL), true, false);
    boolean batchdefaultP = stringSearchIgnoreCase(oCHAMELEON_NEURAL_NETWORK_IMPLEMENTATIONo->symbolName, "-batch", 0) != NULL_INTEGER;

    theoptions->insertAt(KWD_CHAMELEON_MODULE, theoptions->lookupWithDefault(KWD_CHAMELEON_MODULE, oMODULEo));
    theoptions->insertAt(KWD_CHAMELEON_LOCALp, theoptions->lookupWithDefault(KWD_CHAMELEON_LOCALp, FALSE_WRAPPER));
    theoptions->insertAt(KWD_CHAMELEON_EPOCHS, theoptions->lookupWithDefault(KWD_CHAMELEON_EPOCHS, wrapInteger(20)));
    theoptions->insertAt(KWD_CHAMELEON_PRINT_CYCLE, theoptions->lookupWithDefault(KWD_CHAMELEON_PRINT_CYCLE, wrapInteger(-1)));
    theoptions->insertAt(KWD_CHAMELEON_ERROR_CUTOFF, theoptions->lookupWithDefault(KWD_CHAMELEON_ERROR_CUTOFF, wrapFloat(oERROR_CUTOFFo)));
    theoptions->insertAt(KWD_CHAMELEON_SHUFFLEp, theoptions->lookupWithDefault(KWD_CHAMELEON_SHUFFLEp, TRUE_WRAPPER));
    theoptions->insertAt(KWD_CHAMELEON_BATCHp, theoptions->lookupWithDefault(KWD_CHAMELEON_BATCHp, (batchdefaultP ? TRUE_WRAPPER : FALSE_WRAPPER)));
    theoptions->insertAt(KWD_CHAMELEON_EXAMPLES, selectTrainingExamples(consList(8, KWD_CHAMELEON_MODULE, theoptions->lookup(KWD_CHAMELEON_MODULE), KWD_CHAMELEON_LOCALp, theoptions->lookup(KWD_CHAMELEON_LOCALp), KWD_CHAMELEON_N_TRAIN, theoptions->lookup(KWD_CHAMELEON_N_TRAIN), KWD_CHAMELEON_SHUFFLEp, theoptions->lookup(KWD_CHAMELEON_SHUFFLEp))));
    theoptions->insertAt(KWD_CHAMELEON_N_TRAIN, theoptions->lookupWithDefault(KWD_CHAMELEON_N_TRAIN, wrapInteger(((Sequence*)(theoptions->lookup(KWD_CHAMELEON_EXAMPLES)))->length())));
    return (theoptions);
  }
}

void trainChameleonNeuralNetworks(Cons* options) {
  // Train rule neural networks based on :n-train (or all) training examples looked
  // up in :module/:local?.  Train for :epochs (defaults to 20) or until :error-cutoff is reached.
  // Print every :print-cycle epochs or not at all.  If :shuffle? (the default) randomly shuffle the
  // selected training examples before every epoch.  If :batch?, use batch training mechanism (which
  // will fail if the current network implementation does not support it).
  { PropertyList* theoptions = normalizeChameleonTrainingOptions(options);
    int epochs = ((IntegerWrapper*)(theoptions->lookup(KWD_CHAMELEON_EPOCHS)))->wrapperValue;
    int numtraining = ((IntegerWrapper*)(theoptions->lookup(KWD_CHAMELEON_N_TRAIN)))->wrapperValue;
    int printcycle = ((IntegerWrapper*)(theoptions->lookup(KWD_CHAMELEON_PRINT_CYCLE)))->wrapperValue;
    double errorcutoff = ((FloatWrapper*)(theoptions->lookup(KWD_CHAMELEON_ERROR_CUTOFF)))->wrapperValue;
    boolean shuffleP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookup(KWD_CHAMELEON_SHUFFLEp))));
    boolean batchP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookup(KWD_CHAMELEON_BATCHp))));
    Vector* examples = ((Vector*)(theoptions->lookup(KWD_CHAMELEON_EXAMPLES)));
    Justification* cachedproof = NULL;
    NetworkProofQueue* batchqueue = NULL;
    double target = 0.0;
    double output = 0.0;
    double error = 0.0;
    double totalabserror = 0.0;
    OutputStream* log = STANDARD_OUTPUT;

    { TrainingExample* exp = NULL;
      Vector* vector000 = examples;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        exp = ((TrainingExample*)((vector000->theArray)[index000]));
        getCachedNetworkProof(exp);
      }
    }
    if (printcycle > 0) {
      *(log->nativeStream) << "Training networks..." << std::endl;
    }
    { int cycle = NULL_INTEGER;
      int iter000 = 1;
      int upperBound000 = epochs;
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter000 <= upperBound000); 
            iter000 = iter000 + 1) {
        cycle = iter000;
        totalabserror = 0.0;
        if (shuffleP) {
          shuffleVector(examples);
        }
        if (batchP) {
          batchqueue = newNetworkProofForwardQueue();
          { TrainingExample* exp = NULL;
            Vector* vector001 = examples;
            int index001 = 0;
            int length001 = vector001->length();

            for  (; index001 < length001; 
                  index001 = index001 + 1) {
              exp = ((TrainingExample*)((vector001->theArray)[index001]));
              cachedproof = getCachedNetworkProof(exp);
              batchqueue->batchProcessCachedNetworkProof(cachedproof);
            }
          }
          batchqueue->executeAll();
          batchqueue = newNetworkProofBackwardQueue();
          { TrainingExample* exp = NULL;
            Vector* vector002 = examples;
            int index002 = 0;
            int length002 = vector002->length();

            for  (; index002 < length002; 
                  index002 = index002 + 1) {
              exp = ((TrainingExample*)((vector002->theArray)[index002]));
              target = exp->score;
              cachedproof = getCachedNetworkProof(exp);
              output = cachedproof->matchScore;
              error = target - output;
              cachedproof->errorScore = error;
              totalabserror = totalabserror + (((error < 0.0) ? (0.0 - error) : error));
              batchqueue->batchProcessCachedNetworkProof(cachedproof);
            }
          }
          batchqueue->executeAll();
          batchqueue = newNetworkProofUpdateQueue();
          { TrainingExample* exp = NULL;
            Vector* vector003 = examples;
            int index003 = 0;
            int length003 = vector003->length();

            for  (; index003 < length003; 
                  index003 = index003 + 1) {
              exp = ((TrainingExample*)((vector003->theArray)[index003]));
              cachedproof = getCachedNetworkProof(exp);
              batchqueue->batchProcessCachedNetworkProof(cachedproof);
            }
          }
          batchqueue->executeAll();
        }
        else {
          { TrainingExample* exp = NULL;
            Vector* vector004 = examples;
            int index004 = 0;
            int length004 = vector004->length();

            for  (; index004 < length004; 
                  index004 = index004 + 1) {
              exp = ((TrainingExample*)((vector004->theArray)[index004]));
              target = exp->score;
              cachedproof = getCachedNetworkProof(exp);
              output = forwardPropagateCachedNetworkProof(cachedproof);
              error = target - output;
              totalabserror = totalabserror + (((error < 0.0) ? (0.0 - error) : error));
              backwardPropagateCachedNetworkProof(cachedproof, error);
            }
          }
        }
        if ((printcycle > 0) &&
            ((cycle % printcycle) == 0)) {
          *(log->nativeStream) << "Cycle " << cycle << " Error: " << (totalabserror / numtraining) << std::endl;
        }
        if ((totalabserror / numtraining) <= errorcutoff) {
          break;
        }
      }
    }
    if (printcycle > 0) {
      *(log->nativeStream) << "Final error: " << (totalabserror / numtraining) << std::endl;
    }
  }
}

void trainChameleonNeuralNetworksEvaluatorWrapper(Cons* arguments) {
  trainChameleonNeuralNetworks(arguments);
}

ScoredQueryProofAdjunct* newScoredQueryProofAdjunct() {
  { ScoredQueryProofAdjunct* self = NULL;

    self = new ScoredQueryProofAdjunct();
    self->downFrame = NULL;
    self->partialMatchStrategy = NULL;
    return (self);
  }
}

Surrogate* ScoredQueryProofAdjunct::primaryType() {
  { ScoredQueryProofAdjunct* self = this;

    return (SGT_CHAMELEON_LOGIC_SCORED_QUERY_PROOF_ADJUNCT);
  }
}

Object* accessScoredQueryProofAdjunctSlotValue(ScoredQueryProofAdjunct* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_CHAMELEON_LOGIC_PARTIAL_MATCH_STRATEGY) {
    if (setvalueP) {
      self->partialMatchStrategy = ((PartialMatchFrame*)(value));
    }
    else {
      value = self->partialMatchStrategy;
    }
  }
  else if (slotname == SYM_CHAMELEON_LOGIC_DOWN_FRAME) {
    if (setvalueP) {
      self->downFrame = ((ControlFrame*)(value));
    }
    else {
      value = self->downFrame;
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

Keyword* scoredQuerySpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* argpropvalue = argumentBoundTo((proposition->arguments->theArray)[0]);
    Object* argscorevalue = argumentBoundTo((proposition->arguments->theArray)[1]);
    ScoredQueryProofAdjunct* adjunct = ((ScoredQueryProofAdjunct*)(((ProofAdjunct*)(dynamicSlotValue(frame->dynamicSlots, SYM_CHAMELEON_LOGIC_PROOF_ADJUNCT, NULL)))));

    if (lastmove == KWD_CHAMELEON_DOWN) {
      if (!((boolean)(adjunct))) {
        if ((!((boolean)(argpropvalue))) ||
            (!isaP(argpropvalue, SGT_CHAMELEON_LOGIC_PROPOSITION))) {
          return (KWD_CHAMELEON_TERMINAL_FAILURE);
        }
        frame->choicePointUnbindingOffset = NULL_INTEGER;
        { ScoredQueryProofAdjunct* self000 = newScoredQueryProofAdjunct();

          self000->downFrame = createDownFrame(frame, ((Proposition*)(argpropvalue)));
          adjunct = self000;
        }
        setDynamicSlotValue(frame->dynamicSlots, SYM_CHAMELEON_LOGIC_PROOF_ADJUNCT, adjunct, NULL);
      }
      frame->down = adjunct->downFrame;
      frame->down->partialMatchFrame = NULL;
      adjunct->partialMatchStrategy = oQUERYITERATORo->partialMatchStrategy;
      oQUERYITERATORo->partialMatchStrategy = NULL;
      return (KWD_CHAMELEON_MOVE_DOWN);
    }
    else if (lastmove == KWD_CHAMELEON_UP_TRUE) {
      if ((!((boolean)(argscorevalue))) ||
          (!isaP(argscorevalue, SGT_CHAMELEON_STELLA_NUMBER_WRAPPER))) {
        return (scoredQuerySpecialist(frame, KWD_CHAMELEON_UP_FAIL));
      }
      oQUERYITERATORo->partialMatchStrategy = adjunct->partialMatchStrategy;
      propagateFrameTruthValue(frame->result, frame);
      if (((boolean)(oQUERYITERATORo)) &&
          ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
        frame->partialMatchFrame->setFramePartialTruth(frame->result->truthValue, coerceToFloat(argscorevalue), true);
      }
      if (oRECORD_JUSTIFICATIONSpo) {
        { Justification* self001 = newJustification();

          self001->inferenceRule = KWD_CHAMELEON_SCORED_QUERY;
          self001->antecedents = cons(((Justification*)(dynamicSlotValue(frame->result->dynamicSlots, SYM_CHAMELEON_LOGIC_JUSTIFICATION, NULL))), NIL);
          recordGoalJustification(frame, self001);
        }
      }
      if (((boolean)(frame->down))) {
        adjunct->downFrame = frame->down;
        frame->down = NULL;
        return (KWD_CHAMELEON_CONTINUING_SUCCESS);
      }
      else {
        return (KWD_CHAMELEON_FINAL_SUCCESS);
      }
    }
    else if (lastmove == KWD_CHAMELEON_UP_FAIL) {
      oQUERYITERATORo->partialMatchStrategy = adjunct->partialMatchStrategy;
      propagateFrameTruthValue(frame->result, frame);
      if (((boolean)(oQUERYITERATORo)) &&
          ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
        frame->partialMatchFrame->setFramePartialTruth(UNKNOWN_TRUTH_VALUE, NULL_FLOAT, true);
      }
      if (oRECORD_JUSTIFICATIONSpo) {
        recordPrimitiveJustification(frame, KWD_CHAMELEON_UP_FAIL);
      }
      return (KWD_CHAMELEON_TERMINAL_FAILURE);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Keyword* matchScoreSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* argpropvalue = argumentBoundTo((proposition->arguments->theArray)[0]);
    Object* argscore = (proposition->arguments->theArray)[1];
    ScoredQueryProofAdjunct* adjunct = ((ScoredQueryProofAdjunct*)(((ProofAdjunct*)(dynamicSlotValue(frame->dynamicSlots, SYM_CHAMELEON_LOGIC_PROOF_ADJUNCT, NULL)))));

    if (lastmove == KWD_CHAMELEON_DOWN) {
      if (!((boolean)(adjunct))) {
        if ((!((boolean)(argpropvalue))) ||
            (!isaP(argpropvalue, SGT_CHAMELEON_LOGIC_PROPOSITION))) {
          return (KWD_CHAMELEON_TERMINAL_FAILURE);
        }
        frame->choicePointUnbindingOffset = NULL_INTEGER;
        { ScoredQueryProofAdjunct* self000 = newScoredQueryProofAdjunct();

          self000->downFrame = createDownFrame(frame, ((Proposition*)(argpropvalue)));
          adjunct = self000;
        }
        setDynamicSlotValue(frame->dynamicSlots, SYM_CHAMELEON_LOGIC_PROOF_ADJUNCT, adjunct, NULL);
      }
      frame->down = adjunct->downFrame;
      if (!((boolean)(frame->down->partialMatchFrame))) {
        frame->down->partialMatchFrame = newChameleonPartialMatch(NULL, frame->down);
      }
      adjunct->partialMatchStrategy = oQUERYITERATORo->partialMatchStrategy;
      oQUERYITERATORo->partialMatchStrategy = frame->down->partialMatchFrame;
      return (KWD_CHAMELEON_MOVE_DOWN);
    }
    else if (lastmove == KWD_CHAMELEON_UP_TRUE) {
      oQUERYITERATORo->partialMatchStrategy = adjunct->partialMatchStrategy;
      { double score = frame->result->partialMatchFrame->matchScore;

        if (bindArgumentToValueP(argscore, wrapFloat(score), true)) {
          propagateFrameTruthValue(frame->result, frame);
          if (((boolean)(oQUERYITERATORo)) &&
              ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
            frame->result->partialMatchFrame->propagateFramePartialTruth(frame);
          }
          if (oRECORD_JUSTIFICATIONSpo) {
            { Justification* self002 = newJustification();

              self002->inferenceRule = KWD_CHAMELEON_MATCH_SCORE;
              self002->antecedents = cons(((Justification*)(dynamicSlotValue(frame->result->dynamicSlots, SYM_CHAMELEON_LOGIC_JUSTIFICATION, NULL))), NIL);
              recordGoalJustification(frame, self002);
            }
          }
          if (((boolean)(frame->down))) {
            adjunct->downFrame = frame->down;
            frame->down = NULL;
            return (KWD_CHAMELEON_CONTINUING_SUCCESS);
          }
          else {
            return (KWD_CHAMELEON_FINAL_SUCCESS);
          }
        }
        else {
          return (matchScoreSpecialist(frame, KWD_CHAMELEON_UP_FAIL));
        }
      }
    }
    else if (lastmove == KWD_CHAMELEON_UP_FAIL) {
      oQUERYITERATORo->partialMatchStrategy = adjunct->partialMatchStrategy;
      propagateFrameTruthValue(frame->result, frame);
      if (((boolean)(oQUERYITERATORo)) &&
          ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
        frame->partialMatchFrame->setFramePartialTruth(UNKNOWN_TRUTH_VALUE, NULL_FLOAT, true);
      }
      if (oRECORD_JUSTIFICATIONSpo) {
        recordPrimitiveJustification(frame, KWD_CHAMELEON_UP_FAIL);
      }
      return (KWD_CHAMELEON_TERMINAL_FAILURE);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

void helpStartupChameleon1() {
  {
    SGT_CHAMELEON_CHAMELEON_TRUTH_VALUE_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("TRUTH-VALUE-RELATION", getStellaModule("/CHAMELEON", true), 1)));
    SGT_CHAMELEON_CHAMELEON_VECTOR_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("VECTOR-RELATION", getStellaModule("/CHAMELEON", true), 1)));
    SGT_CHAMELEON_CHAMELEON_IGNORED_VALUE_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("IGNORED-VALUE-RELATION", getStellaModule("/CHAMELEON", true), 1)));
    SGT_CHAMELEON_CHAMELEON_PRIMITIVE_VALUE_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("PRIMITIVE-VALUE-RELATION", getStellaModule("/CHAMELEON", true), 1)));
    SGT_CHAMELEON_LOGIC_CHAMELEON_PARTIAL_MATCH = ((Surrogate*)(internRigidSymbolWrtModule("CHAMELEON-PARTIAL-MATCH", NULL, 1)));
    SYM_CHAMELEON_LOGIC_ARGUMENT_JUSTIFICATIONS = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENT-JUSTIFICATIONS", NULL, 0)));
    SYM_CHAMELEON_LOGIC_ARGUMENT_PROPOSITIONS = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENT-PROPOSITIONS", NULL, 0)));
    KWD_CHAMELEON_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    KWD_CHAMELEON_OR = ((Keyword*)(internRigidSymbolWrtModule("OR", NULL, 2)));
    KWD_CHAMELEON_ATOMIC_GOAL = ((Keyword*)(internRigidSymbolWrtModule("ATOMIC-GOAL", NULL, 2)));
    KWD_CHAMELEON_UP_TRUE = ((Keyword*)(internRigidSymbolWrtModule("UP-TRUE", NULL, 2)));
    KWD_CHAMELEON_UP_FAIL = ((Keyword*)(internRigidSymbolWrtModule("UP-FAIL", NULL, 2)));
    KWD_CHAMELEON_DOWN = ((Keyword*)(internRigidSymbolWrtModule("DOWN", NULL, 2)));
    SYM_CHAMELEON_LOGIC_JUSTIFICATION = ((Symbol*)(internRigidSymbolWrtModule("JUSTIFICATION", NULL, 0)));
    KWD_CHAMELEON_GOAL_TREE = ((Keyword*)(internRigidSymbolWrtModule("GOAL-TREE", NULL, 2)));
    KWD_CHAMELEON_OR_INTRODUCTION = ((Keyword*)(internRigidSymbolWrtModule("OR-INTRODUCTION", NULL, 2)));
    KWD_CHAMELEON_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("FAILURE", NULL, 2)));
    KWD_CHAMELEON_OTHER = ((Keyword*)(internRigidSymbolWrtModule("OTHER", NULL, 2)));
    KWD_CHAMELEON_VARIANT1 = ((Keyword*)(internRigidSymbolWrtModule("VARIANT1", NULL, 2)));
    KWD_CHAMELEON_FINAL_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("FINAL-SUCCESS", NULL, 2)));
    KWD_CHAMELEON_VARIANT2 = ((Keyword*)(internRigidSymbolWrtModule("VARIANT2", NULL, 2)));
    SYM_CHAMELEON_LOGIC_ANTECEDENTS_RULE = ((Symbol*)(internRigidSymbolWrtModule("ANTECEDENTS-RULE", NULL, 0)));
    KWD_CHAMELEON_MULTIPLE_PROOFS = ((Keyword*)(internRigidSymbolWrtModule("MULTIPLE-PROOFS", NULL, 2)));
    KWD_CHAMELEON_TECHNICAL = ((Keyword*)(internRigidSymbolWrtModule("TECHNICAL", NULL, 2)));
    KWD_CHAMELEON_LAY = ((Keyword*)(internRigidSymbolWrtModule("LAY", NULL, 2)));
    KWD_CHAMELEON_MINIMUM_SCORE = ((Keyword*)(internRigidSymbolWrtModule("MINIMUM-SCORE", NULL, 2)));
    KWD_CHAMELEON_MAXIMIZE_SCOREp = ((Keyword*)(internRigidSymbolWrtModule("MAXIMIZE-SCORE?", NULL, 2)));
    KWD_CHAMELEON_RECORD_JUSTIFICATIONSp = ((Keyword*)(internRigidSymbolWrtModule("RECORD-JUSTIFICATIONS?", NULL, 2)));
    SGT_CHAMELEON_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", getStellaModule("/STELLA", true), 1)));
    KWD_CHAMELEON_NOISY_OR = ((Keyword*)(internRigidSymbolWrtModule("NOISY-OR", NULL, 2)));
    KWD_CHAMELEON_ORIGINAL = ((Keyword*)(internRigidSymbolWrtModule("ORIGINAL", NULL, 2)));
    SYM_CHAMELEON_LOGIC_NEURAL_NET = ((Symbol*)(internRigidSymbolWrtModule("NEURAL-NET", NULL, 0)));
    KWD_CHAMELEON_PROPOSITION = ((Keyword*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 2)));
    KWD_CHAMELEON_CHAMELEON = ((Keyword*)(internRigidSymbolWrtModule("CHAMELEON", NULL, 2)));
    KWD_CHAMELEON_CHAMELEON_BATCH = ((Keyword*)(internRigidSymbolWrtModule("CHAMELEON-BATCH", NULL, 2)));
    KWD_CHAMELEON_TENSORFLOW = ((Keyword*)(internRigidSymbolWrtModule("TENSORFLOW", NULL, 2)));
    KWD_CHAMELEON_TENSORFLOW_BATCH = ((Keyword*)(internRigidSymbolWrtModule("TENSORFLOW-BATCH", NULL, 2)));
    KWD_CHAMELEON_NOT = ((Keyword*)(internRigidSymbolWrtModule("NOT", NULL, 2)));
    KWD_CHAMELEON_FAIL = ((Keyword*)(internRigidSymbolWrtModule("FAIL", NULL, 2)));
    SGT_CHAMELEON_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    KWD_CHAMELEON_TRUTH_VALUE = ((Keyword*)(internRigidSymbolWrtModule("TRUTH-VALUE", NULL, 2)));
    KWD_CHAMELEON_IGNORED_VALUE = ((Keyword*)(internRigidSymbolWrtModule("IGNORED-VALUE", NULL, 2)));
    KWD_CHAMELEON_VECTOR = ((Keyword*)(internRigidSymbolWrtModule("VECTOR", NULL, 2)));
    SGT_CHAMELEON_LOGIC_M_NEURAL_NETWORKdTRUTH_VALUE_ARGUMENT_INDEX_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("M-NEURAL-NETWORK.TRUTH-VALUE-ARGUMENT-INDEX-MEMO-TABLE-000", NULL, 1)));
    KWD_CHAMELEON_QUICKPROP = ((Keyword*)(internRigidSymbolWrtModule("QUICKPROP", NULL, 2)));
    SGT_CHAMELEON_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    SGT_CHAMELEON_STELLA_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", getStellaModule("/STELLA", true), 1)));
    SGT_CHAMELEON_STELLA_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("VECTOR", getStellaModule("/STELLA", true), 1)));
    SGT_CHAMELEON_STELLA_SEQUENCE = ((Surrogate*)(internRigidSymbolWrtModule("SEQUENCE", getStellaModule("/STELLA", true), 1)));
    SGT_CHAMELEON_STELLA_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("ITERATOR", getStellaModule("/STELLA", true), 1)));
    SGT_CHAMELEON_LOGIC_CHAMELEON_NEURAL_NETWORK = ((Surrogate*)(internRigidSymbolWrtModule("CHAMELEON-NEURAL-NETWORK", NULL, 1)));
    SYM_CHAMELEON_LOGIC_PROPOSITION = ((Symbol*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 0)));
    SYM_CHAMELEON_LOGIC_INPUT = ((Symbol*)(internRigidSymbolWrtModule("INPUT", NULL, 0)));
    SYM_CHAMELEON_LOGIC_HIDDEN = ((Symbol*)(internRigidSymbolWrtModule("HIDDEN", NULL, 0)));
    SYM_CHAMELEON_LOGIC_OUTPUT = ((Symbol*)(internRigidSymbolWrtModule("OUTPUT", NULL, 0)));
    SYM_CHAMELEON_LOGIC_IH = ((Symbol*)(internRigidSymbolWrtModule("IH", NULL, 0)));
    SYM_CHAMELEON_LOGIC_HO = ((Symbol*)(internRigidSymbolWrtModule("HO", NULL, 0)));
    SYM_CHAMELEON_LOGIC_INPUT_ERROR = ((Symbol*)(internRigidSymbolWrtModule("INPUT-ERROR", NULL, 0)));
    SYM_CHAMELEON_LOGIC_HIDDEN_ERROR = ((Symbol*)(internRigidSymbolWrtModule("HIDDEN-ERROR", NULL, 0)));
    SYM_CHAMELEON_LOGIC_OUTPUT_ERROR = ((Symbol*)(internRigidSymbolWrtModule("OUTPUT-ERROR", NULL, 0)));
  }
}

void helpStartupChameleon2() {
  {
    SYM_CHAMELEON_LOGIC_IH_DELTA = ((Symbol*)(internRigidSymbolWrtModule("IH-DELTA", NULL, 0)));
    SYM_CHAMELEON_LOGIC_HO_DELTA = ((Symbol*)(internRigidSymbolWrtModule("HO-DELTA", NULL, 0)));
    SGT_CHAMELEON_STELLA_FLOAT_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT-ARRAY", getStellaModule("/STELLA", true), 1)));
    SGT_CHAMELEON_LOGIC_VECTOR_NEURAL_NETWORK = ((Surrogate*)(internRigidSymbolWrtModule("VECTOR-NEURAL-NETWORK", NULL, 1)));
    SYM_CHAMELEON_LOGIC_N_VECTOR_ARGUMENTS = ((Symbol*)(internRigidSymbolWrtModule("N-VECTOR-ARGUMENTS", NULL, 0)));
    SYM_CHAMELEON_LOGIC_N_VECTOR_ARGUMENT_SPECS = ((Symbol*)(internRigidSymbolWrtModule("N-VECTOR-ARGUMENT-SPECS", NULL, 0)));
    SYM_CHAMELEON_LOGIC_N_VECTOR_ARGUMENT_INPUTS = ((Symbol*)(internRigidSymbolWrtModule("N-VECTOR-ARGUMENT-INPUTS", NULL, 0)));
    SGT_CHAMELEON_LOGIC_M_VECTOR_NEURAL_NETWORKdVECTOR_ARGUMENT_INDEX_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("M-VECTOR-NEURAL-NETWORK.VECTOR-ARGUMENT-INDEX-MEMO-TABLE-000", NULL, 1)));
    SGT_CHAMELEON_CHAMELEON_VECTOR_ARITY = ((Surrogate*)(internRigidSymbolWrtModule("VECTOR-ARITY", getStellaModule("/CHAMELEON", true), 1)));
    SGT_CHAMELEON_CHAMELEON_VECTOR_DIMENSIONS = ((Surrogate*)(internRigidSymbolWrtModule("VECTOR-DIMENSIONS", getStellaModule("/CHAMELEON", true), 1)));
    SGT_CHAMELEON_LOGIC_JUSTIFICATION = ((Surrogate*)(internRigidSymbolWrtModule("JUSTIFICATION", NULL, 1)));
    SGT_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORK = ((Surrogate*)(internRigidSymbolWrtModule("TENSORFLOW-NEURAL-NETWORK", NULL, 1)));
    SYM_CHAMELEON_LOGIC_MODEL = ((Symbol*)(internRigidSymbolWrtModule("MODEL", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdBUILD_PROPOSITION_NETWORK = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-NEURAL-NETWORK.BUILD-PROPOSITION-NETWORK", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdALLOCATE_NETWORK_ARRAYS = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-NEURAL-NETWORK.ALLOCATE-NETWORK-ARRAYS", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdRANDOMIZE_NETWORK_WEIGHTS = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-NEURAL-NETWORK.RANDOMIZE-NETWORK-WEIGHTS", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdINITIALIZE_NETWORK_WEIGHTS = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-NEURAL-NETWORK.INITIALIZE-NETWORK-WEIGHTS", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdNUMBER_OF_INPUTS = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-NEURAL-NETWORK.NUMBER-OF-INPUTS", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdNTH_INPUT = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-NEURAL-NETWORK.NTH-INPUT", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdNTH_INPUT_ERROR = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-NEURAL-NETWORK.NTH-INPUT-ERROR", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdSET_INPUT_VALUES = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-NEURAL-NETWORK.SET-INPUT-VALUES", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdSET_VECTOR_INPUT_VALUES = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-NEURAL-NETWORK.SET-VECTOR-INPUT-VALUES", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdFORWARD_PROPAGATE_INPUTS = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-NEURAL-NETWORK.FORWARD-PROPAGATE-INPUTS", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdBACKWARD_PROPAGATE_ERROR = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-NEURAL-NETWORK.BACKWARD-PROPAGATE-ERROR", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdUPDATE_NETWORK_WEIGHTS = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-NEURAL-NETWORK.UPDATE-NETWORK-WEIGHTS", NULL, 0)));
    KWD_CHAMELEON_MATCH_MODE = ((Keyword*)(internRigidSymbolWrtModule("MATCH-MODE", NULL, 2)));
    KWD_CHAMELEON_WARNING = ((Keyword*)(internRigidSymbolWrtModule("WARNING", NULL, 2)));
    KWD_CHAMELEON_PRIMITIVE_STRATEGY = ((Keyword*)(internRigidSymbolWrtModule("PRIMITIVE-STRATEGY", NULL, 2)));
    KWD_CHAMELEON_GOAL_COMPLEMENT = ((Keyword*)(internRigidSymbolWrtModule("GOAL-COMPLEMENT", NULL, 2)));
    KWD_CHAMELEON_AND_INTRODUCTION = ((Keyword*)(internRigidSymbolWrtModule("AND-INTRODUCTION", NULL, 2)));
    KWD_CHAMELEON_DISPROOF = ((Keyword*)(internRigidSymbolWrtModule("DISPROOF", NULL, 2)));
    KWD_CHAMELEON_MODUS_PONENS = ((Keyword*)(internRigidSymbolWrtModule("MODUS-PONENS", NULL, 2)));
    KWD_CHAMELEON_MODUS_TOLLENS = ((Keyword*)(internRigidSymbolWrtModule("MODUS-TOLLENS", NULL, 2)));
    KWD_CHAMELEON_SUBSUMPTION_REASONING = ((Keyword*)(internRigidSymbolWrtModule("SUBSUMPTION-REASONING", NULL, 2)));
    KWD_CHAMELEON_FAIL_INTRODUCTION = ((Keyword*)(internRigidSymbolWrtModule("FAIL-INTRODUCTION", NULL, 2)));
    KWD_CHAMELEON_MAX = ((Keyword*)(internRigidSymbolWrtModule("MAX", NULL, 2)));
    SGT_CHAMELEON_LOGIC_CHAMELEON_BATCH_NEURAL_NETWORK = ((Surrogate*)(internRigidSymbolWrtModule("CHAMELEON-BATCH-NEURAL-NETWORK", NULL, 1)));
    SYM_CHAMELEON_LOGIC_INPUT_BATCH = ((Symbol*)(internRigidSymbolWrtModule("INPUT-BATCH", NULL, 0)));
    SYM_CHAMELEON_LOGIC_KEY_BATCH = ((Symbol*)(internRigidSymbolWrtModule("KEY-BATCH", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TARGET_BATCH = ((Symbol*)(internRigidSymbolWrtModule("TARGET-BATCH", NULL, 0)));
    SYM_CHAMELEON_LOGIC_OUTPUT_BATCH = ((Symbol*)(internRigidSymbolWrtModule("OUTPUT-BATCH", NULL, 0)));
    SYM_CHAMELEON_LOGIC_INPUT_ERROR_BATCH = ((Symbol*)(internRigidSymbolWrtModule("INPUT-ERROR-BATCH", NULL, 0)));
    SGT_CHAMELEON_LOGIC_2D_LONG_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("2D-LONG-ARRAY", NULL, 1)));
    SGT_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORK = ((Surrogate*)(internRigidSymbolWrtModule("TENSORFLOW-BATCH-NEURAL-NETWORK", NULL, 1)));
    SYM_CHAMELEON_LOGIC_INPUT_MODIFIEDp = ((Symbol*)(internRigidSymbolWrtModule("INPUT-MODIFIED?", NULL, 0)));
    SYM_CHAMELEON_LOGIC_INPUT_BATCH_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("INPUT-BATCH-LENGTH", NULL, 0)));
    SYM_CHAMELEON_LOGIC_VECTOR_BATCH = ((Symbol*)(internRigidSymbolWrtModule("VECTOR-BATCH", NULL, 0)));
    SYM_CHAMELEON_LOGIC_VECTOR_BATCH_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("VECTOR-BATCH-LENGTH", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TARGET_BATCH_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("TARGET-BATCH-LENGTH", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_FORWARD_PROPAGATE_INPUTS = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-BATCH-NEURAL-NETWORK.BATCH-FORWARD-PROPAGATE-INPUTS", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_BACKWARD_PROPAGATE_ERROR = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-BATCH-NEURAL-NETWORK.BATCH-BACKWARD-PROPAGATE-ERROR", NULL, 0)));
    SYM_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_UPDATE_NETWORK_WEIGHTS = ((Symbol*)(internRigidSymbolWrtModule("TENSORFLOW-BATCH-NEURAL-NETWORK.BATCH-UPDATE-NETWORK-WEIGHTS", NULL, 0)));
    SGT_CHAMELEON_LOGIC_NETWORK_PROOF_QUEUE = ((Surrogate*)(internRigidSymbolWrtModule("NETWORK-PROOF-QUEUE", NULL, 1)));
    SYM_CHAMELEON_LOGIC_DEPENDENTS = ((Symbol*)(internRigidSymbolWrtModule("DEPENDENTS", NULL, 0)));
    SYM_CHAMELEON_LOGIC_PREREQUISITES = ((Symbol*)(internRigidSymbolWrtModule("PREREQUISITES", NULL, 0)));
    SYM_CHAMELEON_LOGIC_ACTIVE_NETWORKS = ((Symbol*)(internRigidSymbolWrtModule("ACTIVE-NETWORKS", NULL, 0)));
    SYM_CHAMELEON_LOGIC_MIN_BATCH_SIZE = ((Symbol*)(internRigidSymbolWrtModule("MIN-BATCH-SIZE", NULL, 0)));
    SYM_CHAMELEON_LOGIC_N_QUEUED = ((Symbol*)(internRigidSymbolWrtModule("N-QUEUED", NULL, 0)));
    SGT_CHAMELEON_LOGIC_NETWORK_PROOF_FORWARD_QUEUE = ((Surrogate*)(internRigidSymbolWrtModule("NETWORK-PROOF-FORWARD-QUEUE", NULL, 1)));
    SGT_CHAMELEON_LOGIC_NETWORK_PROOF_BACKWARD_QUEUE = ((Surrogate*)(internRigidSymbolWrtModule("NETWORK-PROOF-BACKWARD-QUEUE", NULL, 1)));
  }
}

void helpStartupChameleon3() {
  {
    SGT_CHAMELEON_LOGIC_NETWORK_PROOF_UPDATE_QUEUE = ((Surrogate*)(internRigidSymbolWrtModule("NETWORK-PROOF-UPDATE-QUEUE", NULL, 1)));
    KWD_CHAMELEON_MODULE = ((Keyword*)(internRigidSymbolWrtModule("MODULE", NULL, 2)));
    SGT_CHAMELEON_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 1)));
    KWD_CHAMELEON_LOCALp = ((Keyword*)(internRigidSymbolWrtModule("LOCAL?", NULL, 2)));
    KWD_CHAMELEON_N_TRAIN = ((Keyword*)(internRigidSymbolWrtModule("N-TRAIN", NULL, 2)));
    SGT_CHAMELEON_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", getStellaModule("/STELLA", true), 1)));
    SYM_CHAMELEON_CHAMELEON_TRAINING_EXAMPLE = ((Symbol*)(internRigidSymbolWrtModule("TRAINING-EXAMPLE", getStellaModule("/CHAMELEON", true), 0)));
    SYM_CHAMELEON_LOGIC_pP = ((Symbol*)(internRigidSymbolWrtModule("?P", NULL, 0)));
    SYM_CHAMELEON_LOGIC_pS = ((Symbol*)(internRigidSymbolWrtModule("?S", NULL, 0)));
    KWD_CHAMELEON_SHUFFLEp = ((Keyword*)(internRigidSymbolWrtModule("SHUFFLE?", NULL, 2)));
    KWD_CHAMELEON_OPTIONS = ((Keyword*)(internRigidSymbolWrtModule("OPTIONS", NULL, 2)));
    KWD_CHAMELEON_EPOCHS = ((Keyword*)(internRigidSymbolWrtModule("EPOCHS", NULL, 2)));
    KWD_CHAMELEON_PRINT_CYCLE = ((Keyword*)(internRigidSymbolWrtModule("PRINT-CYCLE", NULL, 2)));
    KWD_CHAMELEON_ERROR_CUTOFF = ((Keyword*)(internRigidSymbolWrtModule("ERROR-CUTOFF", NULL, 2)));
    SGT_CHAMELEON_STELLA_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT", getStellaModule("/STELLA", true), 1)));
    KWD_CHAMELEON_BATCHp = ((Keyword*)(internRigidSymbolWrtModule("BATCH?", NULL, 2)));
    KWD_CHAMELEON_EXAMPLES = ((Keyword*)(internRigidSymbolWrtModule("EXAMPLES", NULL, 2)));
    SGT_CHAMELEON_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", getStellaModule("/STELLA", true), 1)));
    SGT_CHAMELEON_LOGIC_SCORED_QUERY_PROOF_ADJUNCT = ((Surrogate*)(internRigidSymbolWrtModule("SCORED-QUERY-PROOF-ADJUNCT", NULL, 1)));
    SYM_CHAMELEON_LOGIC_PARTIAL_MATCH_STRATEGY = ((Symbol*)(internRigidSymbolWrtModule("PARTIAL-MATCH-STRATEGY", NULL, 0)));
    SYM_CHAMELEON_LOGIC_DOWN_FRAME = ((Symbol*)(internRigidSymbolWrtModule("DOWN-FRAME", NULL, 0)));
    SYM_CHAMELEON_LOGIC_PROOF_ADJUNCT = ((Symbol*)(internRigidSymbolWrtModule("PROOF-ADJUNCT", NULL, 0)));
    KWD_CHAMELEON_TERMINAL_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("TERMINAL-FAILURE", NULL, 2)));
    KWD_CHAMELEON_MOVE_DOWN = ((Keyword*)(internRigidSymbolWrtModule("MOVE-DOWN", NULL, 2)));
    SGT_CHAMELEON_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", getStellaModule("/STELLA", true), 1)));
    KWD_CHAMELEON_SCORED_QUERY = ((Keyword*)(internRigidSymbolWrtModule("SCORED-QUERY", NULL, 2)));
    KWD_CHAMELEON_CONTINUING_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("CONTINUING-SUCCESS", NULL, 2)));
    KWD_CHAMELEON_MATCH_SCORE = ((Keyword*)(internRigidSymbolWrtModule("MATCH-SCORE", NULL, 2)));
    SYM_CHAMELEON_LOGIC_STARTUP_CHAMELEON = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-CHAMELEON", NULL, 0)));
    SYM_CHAMELEON_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupChameleon4() {
  {
    { Class* clasS = defineClassFromStringifiedSource("CHAMELEON-PARTIAL-MATCH", "(DEFCLASS CHAMELEON-PARTIAL-MATCH (INCREMENTAL-PARTIAL-MATCH) :DOCUMENTATION \"Variant of :BASIC partial match strategy to support CHAMELEON queries.\" :SLOTS ((ARGUMENT-JUSTIFICATIONS :TYPE (CONS OF JUSTIFICATION) :INITIALLY NIL :DOCUMENTATION \"Holds justifications for OR arguments and alternative rules.\") (ARGUMENT-PROPOSITIONS :TYPE (CONS OF PROPOSITION) :INITIALLY NIL :DOCUMENTATION \"Holds argument propositions in the order they are associated with scores\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newChameleonPartialMatch));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessChameleonPartialMatchSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("CHAMELEON-NEURAL-NETWORK", "(DEFCLASS CHAMELEON-NEURAL-NETWORK (NEURAL-NETWORK) :DOCUMENTATION \"Stream-lined neural network structure that doesn't require float wrapping.\" :SLOTS ((PROPOSITION :TYPE PROPOSITION) (INPUT :TYPE FLOAT-ARRAY) (HIDDEN :TYPE FLOAT-ARRAY) (OUTPUT :TYPE FLOAT) (IH :TYPE 2D-FLOAT-ARRAY) (HO :TYPE FLOAT-ARRAY) (INPUT-ERROR :TYPE FLOAT-ARRAY) (HIDDEN-ERROR :TYPE FLOAT-ARRAY) (OUTPUT-ERROR :TYPE FLOAT) (IH-DELTA :TYPE 2D-FLOAT-ARRAY) (HO-DELTA :TYPE FLOAT-ARRAY)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newChameleonNeuralNetwork));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessChameleonNeuralNetworkSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("VECTOR-NEURAL-NETWORK", "(DEFCLASS VECTOR-NEURAL-NETWORK (NEURAL-NETWORK) :DOCUMENTATION \"Neural network that supports vector input arguments.\" :SLOTS ((N-VECTOR-ARGUMENTS :TYPE INTEGER :INITIALLY -1) (N-VECTOR-ARGUMENT-SPECS :TYPE INTEGER :INITIALLY -1) (N-VECTOR-ARGUMENT-INPUTS :TYPE INTEGER :INITIALLY -1)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newVectorNeuralNetwork));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessVectorNeuralNetworkSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("TENSORFLOW-NEURAL-NETWORK", "(DEFCLASS TENSORFLOW-NEURAL-NETWORK (VECTOR-NEURAL-NETWORK) :DOCUMENTATION \"Neural network that is implemented by callbacks to TensorFlow.\" :SLOTS ((PROPOSITION :TYPE PROPOSITION) (MODEL :TYPE PYTHON-OBJECT-POINTER)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newTensorflowNeuralNetwork));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTensorflowNeuralNetworkSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("CHAMELEON-BATCH-NEURAL-NETWORK", "(DEFCLASS CHAMELEON-BATCH-NEURAL-NETWORK (CHAMELEON-NEURAL-NETWORK) :DOCUMENTATION \"Chameleon neural network that supports batch operations via emulation.\" :SLOTS ((INPUT-BATCH :TYPE (VECTOR-SEQUENCE OF OBJECT) :DOCUMENTATION \"Each element is a set of values that may be legally passed to `set-input-values'.\") (KEY-BATCH :TYPE (VECTOR-SEQUENCE OF OBJECT) :DOCUMENTATION \"Each element is a key to identify a specific set of input values.\") (TARGET-BATCH :TYPE (VECTOR-SEQUENCE OF FLOAT-WRAPPER) :DOCUMENTATION \"Each element is a target output value for the respective set of input values.\") (OUTPUT-BATCH :TYPE FLOAT-ARRAY) (INPUT-ERROR-BATCH :TYPE (VECTOR-SEQUENCE OF FLOAT-ARRAY) :DOCUMENTATION \"Copies of `input-error' but without the bias unit, thus shifted by 1.\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newChameleonBatchNeuralNetwork));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessChameleonBatchNeuralNetworkSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("2D-LONG-ARRAY", "(DEFCLASS 2D-LONG-ARRAY (ABSTRACT-DIMENSIONAL-ARRAY 2-DIMENSIONAL-ARRAY-MIXIN) :DOCUMENTATION \"2-dimensional array with long integer values.\" :PUBLIC? TRUE :PARAMETERS ((ANY-VALUE :TYPE LONG-INTEGER)))");

      clasS->classConstructorCode = ((cpp_function_code)(&new2DLongArray));
    }
    { Class* clasS = defineClassFromStringifiedSource("TENSORFLOW-BATCH-NEURAL-NETWORK", "(DEFCLASS TENSORFLOW-BATCH-NEURAL-NETWORK (TENSORFLOW-NEURAL-NETWORK) :DOCUMENTATION \"Tensorflow neural network that supports batch operations.  We implement input and result\nbatches as 1-D and 2-D float arrays to enable fast back-and-forth copying in a single shot instead of having\nmultiple method calls.  For this reason, we maintain the input and target sequences manually.\" :SLOTS ((INPUT-MODIFIED? :TYPE BOOLEAN :INITIALLY TRUE :DOCUMENTATION \"Cleared by Python/Tensorflow side, used to avoid unnecessary copying.\") (INPUT-BATCH :TYPE 2D-FLOAT-ARRAY :DOCUMENTATION \"Each row is a set of inputs for the input units of the network, including the bias.\") (INPUT-BATCH-LENGTH :TYPE INTEGER :INITIALLY 0) (KEY-BATCH :TYPE (VECTOR-SEQUENCE OF OBJECT) :DOCUMENTATION \"Each element is a key to identify a specific set of input values.\") (VECTOR-BATCH :TYPE 2D-LONG-ARRAY :DOCUMENTATION \"Each row is a set of vector argument specs for the inputs of the network.\") (VECTOR-BATCH-LENGTH :TYPE INTEGER :INITIALLY 0) (" "TARGET-BATCH :TYPE FLOAT-ARRAY :DOCUMENTATION \"Each element is a target output value for the respective set of input values.\") (TARGET-BATCH-LENGTH :TYPE INTEGER :INITIALLY 0) (OUTPUT-BATCH :TYPE FLOAT-ARRAY) (INPUT-ERROR-BATCH :TYPE 2D-FLOAT-ARRAY :DOCUMENTATION \"Each row is a set of errors the respective inputs including the bias.\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newTensorflowBatchNeuralNetwork));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTensorflowBatchNeuralNetworkSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("NETWORK-PROOF-QUEUE", "(DEFCLASS NETWORK-PROOF-QUEUE (STANDARD-OBJECT) :SLOTS ((DEPENDENTS :TYPE (KEY-VALUE-MAP OF JUSTIFICATION (CONS OF JUSTIFICATION)) :INITIALLY (NEW KEY-VALUE-MAP) :DOCUMENTATION \"Map from computation prerequisites to their dependents.\") (PREREQUISITES :TYPE (KEY-VALUE-MAP OF JUSTIFICATION (CONS OF JUSTIFICATION)) :INITIALLY (NEW KEY-VALUE-MAP) :DOCUMENTATION \"Map from dependents to their computation prerequisites.\") (ACTIVE-NETWORKS :TYPE (HASH-SET OF NEURAL-NETWORK NEURAL-NETWORK) :INITIALLY (NEW HASH-SET)) (MIN-BATCH-SIZE :TYPE INTEGER :INITIALLY (FLOOR (* *NEURAL-NETWORK-BATCH-SIZE* 0.8))) (N-QUEUED :TYPE INTEGER :INITIALLY 0)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newNetworkProofQueue));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessNetworkProofQueueSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("NETWORK-PROOF-FORWARD-QUEUE", "(DEFCLASS NETWORK-PROOF-FORWARD-QUEUE (NETWORK-PROOF-QUEUE))");

      clasS->classConstructorCode = ((cpp_function_code)(&newNetworkProofForwardQueue));
    }
    { Class* clasS = defineClassFromStringifiedSource("NETWORK-PROOF-BACKWARD-QUEUE", "(DEFCLASS NETWORK-PROOF-BACKWARD-QUEUE (NETWORK-PROOF-QUEUE))");

      clasS->classConstructorCode = ((cpp_function_code)(&newNetworkProofBackwardQueue));
    }
    { Class* clasS = defineClassFromStringifiedSource("NETWORK-PROOF-UPDATE-QUEUE", "(DEFCLASS NETWORK-PROOF-UPDATE-QUEUE (NETWORK-PROOF-QUEUE))");

      clasS->classConstructorCode = ((cpp_function_code)(&newNetworkProofUpdateQueue));
    }
    { Class* clasS = defineClassFromStringifiedSource("SCORED-QUERY-PROOF-ADJUNCT", "(DEFCLASS SCORED-QUERY-PROOF-ADJUNCT (PROOF-ADJUNCT) :SLOTS ((PARTIAL-MATCH-STRATEGY :TYPE PARTIAL-MATCH-FRAME) (DOWN-FRAME :TYPE CONTROL-FRAME)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newScoredQueryProofAdjunct));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessScoredQueryProofAdjunctSlotValue));
    }
  }
}

void helpStartupChameleon5() {
  {
    defineFunctionObject("ENSURE-CHAMELEON-ONTOLOGY", "(DEFUN ENSURE-CHAMELEON-ONTOLOGY () :DOCUMENTATION \"Ensure the chameleon.plm ontology file has been loaded (assumes it exists in the current load path).\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&ensureChameleonOntology)), NULL);
    defineFunctionObject("GET-CHAMELEON-MODULE", "(DEFUN (GET-CHAMELEON-MODULE MODULE) () :DOCUMENTATION \"Return the namespace module for Chameleon relations\" :PUBLIC? TRUE)", ((cpp_function_code)(&getChameleonModule)), NULL);
    defineFunctionObject("CHAMELEON-VECTOR-RELATION?", "(DEFUN (CHAMELEON-VECTOR-RELATION? BOOLEAN) ((X OBJECT)) :DOCUMENTATION \"Return TRUE if `x' is an explicitly marked vector relation.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (TEST-PROPERTY? X /CHAMELEON/@VECTOR-RELATION)))", ((cpp_function_code)(&chameleonVectorRelationP)), NULL);
    defineFunctionObject("CHAMELEON-IGNORED-VALUE-RELATION?", "(DEFUN (CHAMELEON-IGNORED-VALUE-RELATION? BOOLEAN) ((X OBJECT)) :DOCUMENTATION \"Return TRUE if `x' is an explicitly marked as ignored or a vector relation\nthat is not also marked as a truth value relation.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (OR (TEST-PROPERTY? X /CHAMELEON/@IGNORED-VALUE-RELATION) (AND (TEST-PROPERTY? X /CHAMELEON/@VECTOR-RELATION) (NOT (TEST-PROPERTY? X /CHAMELEON/@TRUTH-VALUE-RELATION))))))", ((cpp_function_code)(&chameleonIgnoredValueRelationP)), NULL);
    defineFunctionObject("CHAMELEON-TRUTH-VALUE-RELATION?", "(DEFUN (CHAMELEON-TRUTH-VALUE-RELATION? BOOLEAN) ((X OBJECT)) :DOCUMENTATION \"Return TRUE if `x' is an explicitly marked truth value relation or\notherwise not known to be ignored.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (OR (TEST-PROPERTY? X /CHAMELEON/@TRUTH-VALUE-RELATION) (NOT (CHAMELEON-IGNORED-VALUE-RELATION? X)))))", ((cpp_function_code)(&chameleonTruthValueRelationP)), NULL);
    defineFunctionObject("CHAMELEON-PRIMITIVE-VALUE-RELATION?", "(DEFUN (CHAMELEON-PRIMITIVE-VALUE-RELATION? BOOLEAN) ((X OBJECT)) :DOCUMENTATION \"Return TRUE if `x' is an explicitly marked primitive value relation.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (TEST-PROPERTY? X /CHAMELEON/@PRIMITIVE-VALUE-RELATION)))", ((cpp_function_code)(&chameleonPrimitiveValueRelationP)), NULL);
    defineFunctionObject("CHAMELEON-PARTIAL-MATCH-MODE?", "(DEFUN (CHAMELEON-PARTIAL-MATCH-MODE? BOOLEAN) () :DOCUMENTATION \"Return TRUE if a query is computing Chameleon partial matches.\" :GLOBALLY-INLINE? TRUE (RETURN (AND (PARTIAL-MATCH-MODE?) (ISA? (PARTIAL-MATCH-STRATEGY *QUERYITERATOR*) @CHAMELEON-PARTIAL-MATCH))))", ((cpp_function_code)(&chameleonPartialMatchModeP)), NULL);
    defineMethodObject("(DEFMETHOD (CREATE-PARTIAL-MATCH-FRAME CHAMELEON-PARTIAL-MATCH) ((SELF CHAMELEON-PARTIAL-MATCH) (FRAME CONTROL-FRAME) (KIND KEYWORD)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::createPartialMatchFrame))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-DYNAMIC-CUTOFF PARTIAL-MATCH-SCORE) ((SELF CHAMELEON-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::computeDynamicCutoff))), NULL);
    defineMethodObject("(DEFMETHOD (CUTOFF-PARTIAL-MATCH? BOOLEAN) ((SELF CHAMELEON-PARTIAL-MATCH) (TRACE? BOOLEAN)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::cutoffPartialMatchP))), NULL);
    defineMethodObject("(DEFMETHOD (TRUTH-VALUE-SCORE PARTIAL-MATCH-SCORE) ((SELF CHAMELEON-PARTIAL-MATCH) (TRUTHVALUE TRUTH-VALUE)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::truthValueScore))), NULL);
    defineFunctionObject("INVERT-CHAMELEON-MATCH-SCORE", "(DEFUN (INVERT-CHAMELEON-MATCH-SCORE PARTIAL-MATCH-SCORE) ((SCORE PARTIAL-MATCH-SCORE)))", ((cpp_function_code)(&invertChameleonMatchScore)), NULL);
    defineMethodObject("(DEFMETHOD (INVERT-MATCH-SCORE PARTIAL-MATCH-SCORE) ((SELF CHAMELEON-PARTIAL-MATCH) (SCORE PARTIAL-MATCH-SCORE)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::invertMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD (PROPOSITION-WEIGHT FLOAT) ((SELF CHAMELEON-PARTIAL-MATCH) (PROPOSITION PROPOSITION)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::propositionWeight))), NULL);
    defineMethodObject("(DEFMETHOD PUSH-AND-PARTIAL-MATCH-SCORE ((SELF CHAMELEON-PARTIAL-MATCH) (SCORE PARTIAL-MATCH-SCORE) (WEIGHT FLOAT)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::pushAndPartialMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD POP-AND-PARTIAL-MATCH-SCORE ((SELF CHAMELEON-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::popAndPartialMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD PUSH-OR-PARTIAL-MATCH-SCORE ((SELF CHAMELEON-PARTIAL-MATCH) (SCORE PARTIAL-MATCH-SCORE) (WEIGHT FLOAT)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::pushOrPartialMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD POP-OR-PARTIAL-MATCH-SCORE ((SELF CHAMELEON-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::popOrPartialMatchScore))), NULL);
    defineMethodObject("(DEFMETHOD (ALLOW-UNBOUND-VARIABLES? BOOLEAN) ((SELF CHAMELEON-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::allowUnboundVariablesP))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-AND-SCORE PARTIAL-MATCH-SCORE) ((SELF CHAMELEON-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::computeAndScore))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-AND-PROOF KEYWORD) ((SELF CHAMELEON-PARTIAL-MATCH) (FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::continuePartialAndProof))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-OR-SCORE PARTIAL-MATCH-SCORE) ((SELF CHAMELEON-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::computeOrScore))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-OR-PROOF KEYWORD) ((SELF CHAMELEON-PARTIAL-MATCH) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::continuePartialOrProof))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-NOT-SCORE PARTIAL-MATCH-SCORE) ((SELF CHAMELEON-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::computeNotScore))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-NOT-PROOF KEYWORD) ((SELF CHAMELEON-PARTIAL-MATCH) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::continuePartialNotProof))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-FAIL-PROOF KEYWORD) ((SELF CHAMELEON-PARTIAL-MATCH) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::continuePartialFailProof))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-GOAL-SCORE PARTIAL-MATCH-SCORE) ((SELF CHAMELEON-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::computeGoalScore))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-STRATEGIES-PROOFS KEYWORD) ((SELF CHAMELEON-PARTIAL-MATCH) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::continuePartialStrategiesProofs))), NULL);
    defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-ANTECEDENTS-PROOF KEYWORD) ((SELF CHAMELEON-PARTIAL-MATCH) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::continuePartialAntecedentsProof))), NULL);
    defineMethodObject("(DEFMETHOD (COMPUTE-PARTIAL-TRUTH FLOAT) ((SELF CHAMELEON-PARTIAL-MATCH) (QUERY QUERY-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&ChameleonPartialMatch::computePartialTruth))), NULL);
    defineFunctionObject("REGISTER-NEURAL-NETWORK", "(DEFUN REGISTER-NEURAL-NETWORK ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Register the network `self' on the global networks list (assumes `self' has been linked).\" :PUBLIC? TRUE)", ((cpp_function_code)(&registerNeuralNetwork)), NULL);
    defineFunctionObject("UNREGISTER-NEURAL-NETWORK", "(DEFUN UNREGISTER-NEURAL-NETWORK ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Unregister the network `self' on the global networks list.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unregisterNeuralNetwork)), NULL);
    defineFunctionObject("LOOKUP-PROPOSITION-NEURAL-NETWORK", "(DEFUN (LOOKUP-PROPOSITION-NEURAL-NETWORK NEURAL-NETWORK) ((PROP PROPOSITION)) :DOCUMENTATION \"Lookup the neural network for `prop' in the global networks list.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupPropositionNeuralNetwork)), NULL);
    defineFunctionObject("DELETE-NEURAL-NETWORKS", "(DEFUN DELETE-NEURAL-NETWORKS () :DOCUMENTATION \"Eliminate all neural networks and remove any connections\nto propositions and training examples.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&deleteNeuralNetworks)), NULL);
    defineFunctionObject("RANDOMIZE-NEURAL-NETWORKS", "(DEFUN RANDOMIZE-NEURAL-NETWORKS () :DOCUMENTATION \"Undo all training and randomize weights in all neural networks.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&randomizeNeuralNetworks)), NULL);
    defineFunctionObject("CREATE-AND-LINK-NEURAL-NETWORK", "(DEFUN CREATE-AND-LINK-NEURAL-NETWORK ((PROP PROPOSITION)))", ((cpp_function_code)(&createAndLinkNeuralNetwork)), NULL);
    defineFunctionObject("GET-PROPOSITION-NEURAL-NETWORK", "(DEFUN (GET-PROPOSITION-NEURAL-NETWORK NEURAL-NETWORK) ((PROP PROPOSITION) (ERROR? BOOLEAN)) :DOCUMENTATION \"Return the neural network associated with `prop'.  If `error?', raise an\nexception if it cannot be found, otherwise, simply return NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getPropositionNeuralNetwork)), NULL);
    defineFunctionObject("GET-JUSTIFICATION-NEURAL-NETWORK", "(DEFUN (GET-JUSTIFICATION-NEURAL-NETWORK NEURAL-NETWORK) ((JUST JUSTIFICATION)) :DOCUMENTATION \"Return the neural network associated with an :AND or :OR justification.\nRaise an error if the associated proposition is not linked to a neural network.\")", ((cpp_function_code)(&getJustificationNeuralNetwork)), NULL);
    defineMethodObject("(DEFMETHOD LINK-NEURAL-NETWORK ((SELF NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Link the network `self' to its associated proposition `prop'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::linkNeuralNetwork))), NULL);
    defineMethodObject("(DEFMETHOD UNLINK-NEURAL-NETWORK ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Unlink the network `self' from its associated proposition.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::unlinkNeuralNetwork))), NULL);
    defineMethodObject("(DEFMETHOD (GET-NEURAL-NETWORK-PROPOSITION PROPOSITION) ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Return the proposition linked to `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::getNeuralNetworkProposition))), NULL);
    defineMethodObject("(DEFMETHOD DELETE-NEURAL-NETWORK ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Unlink the network `self' from its associated proposition and mark it as deleted.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::deleteNeuralNetwork))), NULL);
    defineMethodObject("(DEFMETHOD (DELETED? BOOLEAN) ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Return trun if `self' has been deleted.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::deletedP))), NULL);
    defineMethodObject("(DEFMETHOD ALLOCATE-NETWORK-ARRAYS ((SELF NEURAL-NETWORK) (NUM-IN INTEGER) (NUM-HIDDEN INTEGER) (NUM-OUT INTEGER)) :DOCUMENTATION \"Allocates array space for a neural network with given number of input, hidden and output units.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::allocateNetworkArrays))), NULL);
    defineMethodObject("(DEFMETHOD RANDOMIZE-NETWORK-WEIGHTS ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Randomize the weights of the neural network `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::randomizeNetworkWeights))), NULL);
    defineMethodObject("(DEFMETHOD BUILD-PROPOSITION-NETWORK ((SELF NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Build a neural network for the proposition `prop' and link them.  This builds\na two-layer perceptron network whose input nodes are activated by the truth of `prop's arguments\nand whose output node computes the truth of `prop'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::buildPropositionNetwork))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-OF-INPUTS INTEGER) ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Return the number of input values expected by `self' (ignores bias unit).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::numberOfInputs))), NULL);
    defineFunctionObject("HELP-COMPUTE-ARGUMENT-INDEX", "(DEFUN (HELP-COMPUTE-ARGUMENT-INDEX INTEGER) ((SELF NEURAL-NETWORK) (ARG PROPOSITION) (KIND KEYWORD)) :DOCUMENTATION \"Memoizable helper function for `truth-value-argument-index' and friends.\" :PUBLIC? TRUE)", ((cpp_function_code)(&helpComputeArgumentIndex)), NULL);
    defineMethodObject("(DEFMETHOD (TRUTH-VALUE-ARGUMENT? BOOLEAN) ((SELF NEURAL-NETWORK) (ARG PROPOSITION)) :DOCUMENTATION \"Return TRUE if the partial truth value of `arg' will be considered for `self's inputs.\nThis top-level method only looks at `arg' and ignores `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::truthValueArgumentP))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-OF-TRUTH-VALUE-ARGUMENTS INTEGER) ((SELF NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Return the number of arguments of `prop' whose partial truth value will be considered\nfor `self's inputs.  This top-level method only looks at `prop' and ignores `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::numberOfTruthValueArguments))), NULL);
    defineMethodObject("(DEFMETHOD (TRUTH-VALUE-ARGUMENT-INDEX INTEGER) ((SELF NEURAL-NETWORK) (ARG PROPOSITION)) :DOCUMENTATION \"Return the 0-based input position of truth value argument `arg'.  Ignores bias unit which\nis a network-implementation-specific detail.  Generates indices in the order expected by `set-input-values'.\nIf `arg' is not a truth value argument, returns -1.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::truthValueArgumentIndex))), NULL);
    defineMethodObject("(DEFMETHOD (IGNORED-VALUE-ARGUMENT? BOOLEAN) ((SELF NEURAL-NETWORK) (ARG PROPOSITION)) :DOCUMENTATION \"Return TRUE if the partial truth value of `arg' will be ignored for `self's inputs.\nThis top-level method only looks at `arg' and ignores `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::ignoredValueArgumentP))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-OF-IGNORED-VALUE-ARGUMENTS INTEGER) ((SELF NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Return the number of arguments of `prop' whose partial truth value will be ignored\nfor `self's inputs.  This top-level method only looks at `prop' and ignores `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::numberOfIgnoredValueArguments))), NULL);
    defineMethodObject("(DEFMETHOD (VECTOR-ARGUMENT? BOOLEAN) ((SELF NEURAL-NETWORK) (ARG PROPOSITION)) :DOCUMENTATION \"Return TRUE if `arg' yields one or more vectors for `self's inputs.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::vectorArgumentP))), NULL);
    defineMethodObject("(DEFMETHOD (HAS-VECTOR-ARGUMENTS? BOOLEAN) ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Return TRUE if `self' has at least one vector input argument.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::hasVectorArgumentsP))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-OF-VECTOR-ARGUMENTS INTEGER) ((SELF NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Return the number of arguments of `prop' that yield one or more vectors\nfor `self's inputs.  `prop' can be NULL in which case the linked proposition will be used.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::numberOfVectorArguments))), NULL);
    defineMethodObject("(DEFMETHOD (VECTOR-ARGUMENT-INDEX INTEGER) ((SELF NEURAL-NETWORK) (ARG PROPOSITION)) :DOCUMENTATION \"Return the 0-based input position of vector argument `arg'.  Ignores bias unit which\nis a network-implementation-specific detail.  If `arg' is not a vector argument, returns -1.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::vectorArgumentIndex))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-INPUT FLOAT) ((SELF NEURAL-NETWORK) (N INTEGER)) :DOCUMENTATION \"Return the 0-based `n'-th proposition input of `self' (ignores bias unit).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::nthInput))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-INPUT-ERROR FLOAT) ((SELF NEURAL-NETWORK) (N INTEGER)) :DOCUMENTATION \"Return the 0-based `n'-th proposition input error of `self' (ignores bias unit).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::nthInputError))), NULL);
    defineMethodObject("(DEFMETHOD SET-INPUT-VALUES ((SELF NEURAL-NETWORK) (VALUES OBJECT)) :DOCUMENTATION \"Set the current truth-value inputs of the network `self' to float `values' in sequence.\nMissing inputs will be set to 0.0, extra values will be ignored.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::setInputValues))), NULL);
  }
}

void helpStartupChameleon6() {
  {
    defineMethodObject("(DEFMETHOD SET-VECTOR-INPUT-VALUES ((SELF NEURAL-NETWORK) (VECTORSPECS OBJECT)) :DOCUMENTATION \"Set the current vector inputs of the network `self' to the vectors described by `vectorSpecs'.\nEach vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs\nare translated into actual numeric vectors such as embeddings is specific to the particular neural network type.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::setVectorInputValues))), NULL);
    defineMethodObject("(DEFMETHOD (GET-VECTOR-ARGUMENT-SPEC OBJECT) ((SELF NEURAL-NETWORK) (ARG OBJECT)) :DOCUMENTATION \"Generate a single argument spec for `arg' that can be used for `set-vector-input-values'.\n`arg' can either be a proposition or justification.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::getVectorArgumentSpec))), NULL);
    defineMethodObject("(DEFMETHOD (FORWARD-PROPAGATE-INPUTS FLOAT) ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Activates the current inputs of the network `self' to compute its output.\nSets `self's `output' slot and returns the computed value.  Reads input activations and\nweights and updates hidden and output activations.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::forwardPropagateInputs))), NULL);
    defineMethodObject("(DEFMETHOD BACKWARD-PROPAGATE-ERROR ((SELF NEURAL-NETWORK) (ERROR FLOAT)) :DOCUMENTATION \"Given a properly forward activated network `self' for the current set of inputs,\nand a training `error' between the current output and the goal value, backpropagate the error and\nupdate `self's vector of input errors.  Reads output, hidden activations and weights and updates\nhidden errors and input errors.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::backwardPropagateError))), NULL);
    defineMethodObject("(DEFMETHOD UPDATE-NETWORK-WEIGHTS ((SELF NEURAL-NETWORK) (ERROR FLOAT)) :DOCUMENTATION \"Given a properly forward activated and backpropagated network `self' for the current\ninputs and training `error', update the network's weights according to current gradients, learning rate\nand momentum terms to reduce the error for the given inputs.  Reads output, hidden and input activations,\nhidden error, weights and weight deltas, and updates weights and weight deltas.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::updateNetworkWeights))), NULL);
    defineMethodObject("(DEFMETHOD LINK-NEURAL-NETWORK ((SELF PROPOSITION-NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Link the network `self' to its associated proposition `prop'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::linkNeuralNetwork))), NULL);
    defineMethodObject("(DEFMETHOD UNLINK-NEURAL-NETWORK ((SELF PROPOSITION-NEURAL-NETWORK)) :DOCUMENTATION \"Unlink the network `self' from its associated proposition.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::unlinkNeuralNetwork))), NULL);
    defineMethodObject("(DEFMETHOD (GET-NEURAL-NETWORK-PROPOSITION PROPOSITION) ((SELF PROPOSITION-NEURAL-NETWORK)) :DOCUMENTATION \"Return the proposition linked to `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::getNeuralNetworkProposition))), NULL);
    defineMethodObject("(DEFMETHOD DELETE-NEURAL-NETWORK ((SELF PROPOSITION-NEURAL-NETWORK)) :DOCUMENTATION \"Unlink the network `self' from its associated proposition and mark it as deleted.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::deleteNeuralNetwork))), NULL);
    defineMethodObject("(DEFMETHOD (DELETED? BOOLEAN) ((SELF PROPOSITION-NEURAL-NETWORK)) :DOCUMENTATION \"Return trun if `self' has been deleted.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::deletedP))), NULL);
    defineMethodObject("(DEFMETHOD ALLOCATE-NETWORK-ARRAYS ((SELF PROPOSITION-NEURAL-NETWORK) (NUM-IN INTEGER) (NUM-HIDDEN INTEGER) (NUM-OUT INTEGER)) :DOCUMENTATION \"Allocates array space for a neural network with given number of input, hidden and output units.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::allocateNetworkArrays))), NULL);
    defineMethodObject("(DEFMETHOD RANDOMIZE-NETWORK-WEIGHTS ((SELF PROPOSITION-NEURAL-NETWORK)) :DOCUMENTATION \"Randomize the weights of the neural network `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::randomizeNetworkWeights))), NULL);
    defineMethodObject("(DEFMETHOD BUILD-PROPOSITION-NETWORK ((SELF PROPOSITION-NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Build a neural network for the proposition `prop'.  This builds a two-layer\nperceptron network whose input nodes are activated by the truth of `prop's arguments and whose\noutput node computes the truth of `prop'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::buildPropositionNetwork))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-OF-INPUTS INTEGER) ((SELF PROPOSITION-NEURAL-NETWORK)) :DOCUMENTATION \"Return the number of input values expected by `self' (ignores bias unit).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::numberOfInputs))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-INPUT FLOAT) ((SELF PROPOSITION-NEURAL-NETWORK) (N INTEGER)) :DOCUMENTATION \"Return the 0-based `n'-th proposition input of `self' (ignores bias unit).\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NTH (INPUT SELF) (1+ N))))", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::nthInput))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-INPUT-ERROR FLOAT) ((SELF PROPOSITION-NEURAL-NETWORK) (N INTEGER)) :DOCUMENTATION \"Return the 0-based `n'-th proposition input error of `self' (ignores bias unit).\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NTH (INPUT-ERROR SELF) (1+ N))))", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::nthInputError))), NULL);
    defineMethodObject("(DEFMETHOD SET-INPUT-VALUES ((SELF PROPOSITION-NEURAL-NETWORK) (VALUES OBJECT)) :DOCUMENTATION \"Set the current truth-value inputs of the network `self' to float `values' in sequence.\nMissing inputs will be set to 0.0, extra values will be ignored.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::setInputValues))), NULL);
    defineMethodObject("(DEFMETHOD (FORWARD-PROPAGATE-INPUTS FLOAT) ((SELF PROPOSITION-NEURAL-NETWORK)) :DOCUMENTATION \"Activates the current inputs of the network `self' to compute its output.\nSets `self's `output' slot and returns the computed value.  Reads input activations and\nweights and updates hidden and output activations.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::forwardPropagateInputs))), NULL);
    defineMethodObject("(DEFMETHOD BACKWARD-PROPAGATE-ERROR ((SELF PROPOSITION-NEURAL-NETWORK) (ERROR FLOAT)) :DOCUMENTATION \"Given a properly forward activated network `self' for the current set of inputs,\nand a training `error' between the current output and the goal value, backpropagate the error and\nupdate `self's vector of input errors.  Reads output, hidden activations and weights and updates\nhidden errors and input errors.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::backwardPropagateError))), NULL);
    defineMethodObject("(DEFMETHOD UPDATE-NETWORK-WEIGHTS ((SELF PROPOSITION-NEURAL-NETWORK) (ERROR FLOAT)) :DOCUMENTATION \"Given a properly forward activated and backpropagated network `self' for the current\ninputs and training `error', update the network's weights according to current gradients, learning rate\nand momentum terms to reduce the error for the given inputs.  Reads output, hidden and input activations,\nhidden error, weights and weight deltas, and updates weights and weight deltas.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&PropositionNeuralNetwork::updateNetworkWeights))), NULL);
    defineMethodObject("(DEFMETHOD LINK-NEURAL-NETWORK ((SELF CHAMELEON-NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Link the network `self' to its associated proposition `prop'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::linkNeuralNetwork))), NULL);
    defineMethodObject("(DEFMETHOD UNLINK-NEURAL-NETWORK ((SELF CHAMELEON-NEURAL-NETWORK)) :DOCUMENTATION \"Unlink the network `self' from its associated proposition.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::unlinkNeuralNetwork))), NULL);
    defineMethodObject("(DEFMETHOD (GET-NEURAL-NETWORK-PROPOSITION PROPOSITION) ((SELF CHAMELEON-NEURAL-NETWORK)) :DOCUMENTATION \"Return the proposition linked to `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::getNeuralNetworkProposition))), NULL);
    defineMethodObject("(DEFMETHOD DELETE-NEURAL-NETWORK ((SELF CHAMELEON-NEURAL-NETWORK)) :DOCUMENTATION \"Unlink the network `self' from its associated proposition and mark it as deleted.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::deleteNeuralNetwork))), NULL);
    defineMethodObject("(DEFMETHOD (DELETED? BOOLEAN) ((SELF CHAMELEON-NEURAL-NETWORK)) :DOCUMENTATION \"Return trun if `self' has been deleted.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::deletedP))), NULL);
    defineMethodObject("(DEFMETHOD ALLOCATE-NETWORK-ARRAYS ((SELF CHAMELEON-NEURAL-NETWORK) (NUM-IN INTEGER) (NUM-HIDDEN INTEGER) (NUM-OUT INTEGER)) :DOCUMENTATION \"Allocates array space for a neural network with given number of input, hidden and output units.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::allocateNetworkArrays))), NULL);
    defineMethodObject("(DEFMETHOD RANDOMIZE-NETWORK-WEIGHTS ((SELF CHAMELEON-NEURAL-NETWORK)) :DOCUMENTATION \"Randomize the weights of the neural network `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::randomizeNetworkWeights))), NULL);
    defineMethodObject("(DEFMETHOD BUILD-PROPOSITION-NETWORK ((SELF CHAMELEON-NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Build a neural network for the proposition `prop'.  This builds a two-layer\nperceptron network whose input nodes are activated by the truth of `prop's arguments and whose\noutput node computes the truth of `prop'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::buildPropositionNetwork))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-OF-INPUTS INTEGER) ((SELF CHAMELEON-NEURAL-NETWORK)) :DOCUMENTATION \"Return the number of input values expected by `self' (ignores bias unit).\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (1- (DIM1 (INPUT SELF)))))", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::numberOfInputs))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-INPUT FLOAT) ((SELF CHAMELEON-NEURAL-NETWORK) (N INTEGER)) :DOCUMENTATION \"Return the 0-based `n'-th proposition input of `self' (ignores bias unit).\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (1D-AREF (INPUT SELF) (1+ N))))", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::nthInput))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-INPUT-ERROR FLOAT) ((SELF CHAMELEON-NEURAL-NETWORK) (N INTEGER)) :DOCUMENTATION \"Return the 0-based `n'-th proposition input error of `self' (ignores bias unit).\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (1D-AREF (INPUT-ERROR SELF) (1+ N))))", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::nthInputError))), NULL);
    defineFunctionObject("COPY-FLOAT-VALUES-TO-BUFFER", "(DEFUN COPY-FLOAT-VALUES-TO-BUFFER ((VALUES OBJECT) (BUFFER (ARRAY () OF FLOAT)) (START INTEGER) (END INTEGER)) :DOCUMENTATION \"Copy the float `values' in sequence to `buffer' between `start' and `end'.\nMissing values will be set to 0.0, extra values will be ignored.\" :PUBLIC? TRUE)", ((cpp_function_code)(&copyFloatValuesToBuffer)), NULL);
    defineMethodObject("(DEFMETHOD SET-INPUT-VALUES ((SELF CHAMELEON-NEURAL-NETWORK) (VALUES OBJECT)) :DOCUMENTATION \"Set the current truth-value inputs of the network `self' to float `values' in sequence.\nMissing inputs will be set to 0.0, extra values will be ignored.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::setInputValues))), NULL);
    defineMethodObject("(DEFMETHOD SET-VECTOR-INPUT-VALUES ((SELF CHAMELEON-NEURAL-NETWORK) (VECTORSPECS OBJECT)) :DOCUMENTATION \"Set the current vector inputs of the network `self' to the vectors described by `vectorSpecs'.\nEach vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs\nare translated into actual numeric vectors such as embeddings is specific to the particular neural network type.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::setVectorInputValues))), NULL);
    defineMethodObject("(DEFMETHOD (FORWARD-PROPAGATE-INPUTS FLOAT) ((SELF CHAMELEON-NEURAL-NETWORK)) :DOCUMENTATION \"Activates the current inputs of the network `self' to compute its output.\nSets `self's `output' slot and returns the computed value.  Reads input activations and\nweights and updates hidden and output activations.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::forwardPropagateInputs))), NULL);
    defineMethodObject("(DEFMETHOD BACKWARD-PROPAGATE-ERROR ((SELF CHAMELEON-NEURAL-NETWORK) (ERROR FLOAT)) :DOCUMENTATION \"Given a properly forward activated network `self' for the current set of inputs,\nand a training `error' between the current output and the goal value, backpropagate the error and\nupdate `self's vector of input errors.  Reads output, hidden activations and weights and updates\nhidden errors and input errors.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::backwardPropagateError))), NULL);
    defineMethodObject("(DEFMETHOD UPDATE-NETWORK-WEIGHTS ((SELF CHAMELEON-NEURAL-NETWORK) (ERROR FLOAT)) :DOCUMENTATION \"Given a properly forward activated and backpropagated network `self' for the current\ninputs and training `error', update the network's weights according to current gradients, learning rate\nand momentum terms to reduce the error for the given inputs.  Reads output, hidden and input activations,\nhidden error, weights and weight deltas, and updates weights and weight deltas.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonNeuralNetwork::updateNetworkWeights))), NULL);
    defineMethodObject("(DEFMETHOD (VECTOR-ARGUMENT? BOOLEAN) ((SELF VECTOR-NEURAL-NETWORK) (ARG PROPOSITION)) :DOCUMENTATION \"Return TRUE if `arg' yields one or more vectors for `self's inputs.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorNeuralNetwork::vectorArgumentP))), NULL);
    defineMethodObject("(DEFMETHOD (HAS-VECTOR-ARGUMENTS? BOOLEAN) ((SELF VECTOR-NEURAL-NETWORK)) :DOCUMENTATION \"Return TRUE if `self' has at least one vector input argument.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorNeuralNetwork::hasVectorArgumentsP))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-OF-VECTOR-ARGUMENTS INTEGER) ((SELF VECTOR-NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Return the number of arguments of `prop' that yield one or more vectors\nfor `self's inputs.  `prop' can be NULL in which case the linked proposition will be used.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorNeuralNetwork::numberOfVectorArguments))), NULL);
    defineMethodObject("(DEFMETHOD (VECTOR-ARGUMENT-INDEX INTEGER) ((SELF VECTOR-NEURAL-NETWORK) (ARG PROPOSITION)) :DOCUMENTATION \"Return the 0-based input position of vector argument `arg'.  Ignores bias unit which\nis a network-implementation-specific detail.  If `arg' is not a vector argument, returns -1.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorNeuralNetwork::vectorArgumentIndex))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-OF-VECTOR-ARGUMENT-SPECS INTEGER) ((SELF VECTOR-NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Return the total number of argument specs generated by vector arguments of `prop'.\nThis is only different than `number-of-vector-arguments' if at least one of `prop's vector argument\nrelations has arity > 1.  `prop' can be NULL in which case the linked proposition will be used.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorNeuralNetwork::numberOfVectorArgumentSpecs))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-OF-VECTOR-ARGUMENT-INPUTS INTEGER) ((SELF VECTOR-NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Return the total number of input positions to store all elements of all vector\narguments of `prop'.  `prop' can be NULL in which case the linked proposition will be used.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorNeuralNetwork::numberOfVectorArgumentInputs))), NULL);
    defineMethodObject("(DEFMETHOD SET-VECTOR-INPUT-VALUES ((SELF VECTOR-NEURAL-NETWORK) (VECTORSPECS OBJECT)) :DOCUMENTATION \"Set the current vector inputs of the network `self' to the vectors described by `vectorSpecs'.\nEach vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs\nare translated into actual numeric vectors such as embeddings is specific to the particular neural network type.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorNeuralNetwork::setVectorInputValues))), NULL);
    defineMethodObject("(DEFMETHOD (GET-VECTOR-ARGUMENT-SPEC OBJECT) ((SELF VECTOR-NEURAL-NETWORK) (ARG OBJECT)) :DOCUMENTATION \"Generate a single argument spec for `arg' that can be used for `set-vector-input-values'.\n`arg' can either be a proposition or justification.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&VectorNeuralNetwork::getVectorArgumentSpec))), NULL);
    defineFunctionObject("REGISTER-TENSORFLOW-CALLBACK", "(DEFUN REGISTER-TENSORFLOW-CALLBACK ((NAME STRING) (CODE FUNCTION-CODE)) :DOCUMENTATION \"Special-purpose callback support that registers `code' under the logic symbol with `name',\nwhich by convention we make the qualified method name of the method we are using this for.  This is a\nspecial-purpose hack which eventually we might want to generalize so others can use it too.\" :PUBLIC? TRUE)", ((cpp_function_code)(&registerTensorflowCallback)), NULL);
    defineFunctionObject("GET-TENSORFLOW-CALLBACK", "(DEFUN (GET-TENSORFLOW-CALLBACK FUNCTION-CODE) ((NAME SYMBOL)) :DOCUMENTATION \"Access the TensorFlow callback code registered under `name'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (SYMBOL-VALUE NAME)))", ((cpp_function_code)(&getTensorflowCallback)), NULL);
    defineFunctionObject("TENSORFLOW-BACKEND-AVAILABLE?", "(DEFUN (TENSORFLOW-BACKEND-AVAILABLE? BOOLEAN) () :DOCUMENTATION \"Return TRUE if TensorFlow callbacks have been properly registered.\" :PUBLIC? TRUE)", ((cpp_function_code)(&tensorflowBackendAvailableP)), NULL);
    defineMethodObject("(DEFMETHOD LINK-NEURAL-NETWORK ((SELF TENSORFLOW-NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Link the network `self' to its associated proposition `prop'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::linkNeuralNetwork))), NULL);
    defineMethodObject("(DEFMETHOD UNLINK-NEURAL-NETWORK ((SELF TENSORFLOW-NEURAL-NETWORK)) :DOCUMENTATION \"Unlink the network `self' from its associated proposition.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::unlinkNeuralNetwork))), NULL);
    defineMethodObject("(DEFMETHOD (GET-NEURAL-NETWORK-PROPOSITION PROPOSITION) ((SELF TENSORFLOW-NEURAL-NETWORK)) :DOCUMENTATION \"Return the proposition linked to `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::getNeuralNetworkProposition))), NULL);
    defineMethodObject("(DEFMETHOD DELETE-NEURAL-NETWORK ((SELF TENSORFLOW-NEURAL-NETWORK)) :DOCUMENTATION \"Unlink the network `self' from its associated proposition and mark it as deleted.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::deleteNeuralNetwork))), NULL);
    defineMethodObject("(DEFMETHOD (DELETED? BOOLEAN) ((SELF TENSORFLOW-NEURAL-NETWORK)) :DOCUMENTATION \"Return trun if `self' has been deleted.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::deletedP))), NULL);
    defineMethodObject("(DEFMETHOD ALLOCATE-NETWORK-ARRAYS ((SELF TENSORFLOW-NEURAL-NETWORK) (NUM-IN INTEGER) (NUM-HIDDEN INTEGER) (NUM-OUT INTEGER)) :DOCUMENTATION \"Allocates array space for a neural network with given number of input, hidden and output units.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::allocateNetworkArrays))), NULL);
    defineMethodObject("(DEFMETHOD RANDOMIZE-NETWORK-WEIGHTS ((SELF TENSORFLOW-NEURAL-NETWORK)) :DOCUMENTATION \"Randomize the weights of the neural network `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::randomizeNetworkWeights))), NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-NETWORK-WEIGHTS ((SELF TENSORFLOW-NEURAL-NETWORK)) :DOCUMENTATION \"Initialize the weights of the neural network `self' - eiher randomly or from a saved state.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::initializeNetworkWeights))), NULL);
    defineMethodObject("(DEFMETHOD BUILD-PROPOSITION-NETWORK ((SELF TENSORFLOW-NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Build a neural network for the proposition `prop'.  This builds a two-layer\nperceptron network whose input nodes are activated by the truth of `prop's arguments and whose\noutput node computes the truth of `prop'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::buildPropositionNetwork))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-OF-INPUTS INTEGER) ((SELF TENSORFLOW-NEURAL-NETWORK)) :DOCUMENTATION \"Return the number of input values expected by `self' (ignores bias unit).\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (FUNCALL (GET-TENSORFLOW-CALLBACK (QUOTE TENSORFLOW-NEURAL-NETWORK.NUMBER-OF-INPUTS)) SELF)))", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::numberOfInputs))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-INPUT FLOAT) ((SELF TENSORFLOW-NEURAL-NETWORK) (N INTEGER)) :DOCUMENTATION \"Return the 0-based `n'-th proposition input of `self' (ignores bias unit).\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (FUNCALL (GET-TENSORFLOW-CALLBACK (QUOTE TENSORFLOW-NEURAL-NETWORK.NTH-INPUT)) SELF N)))", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::nthInput))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-INPUT-ERROR FLOAT) ((SELF TENSORFLOW-NEURAL-NETWORK) (N INTEGER)) :DOCUMENTATION \"Return the 0-based `n'-th proposition input error of `self' (ignores bias unit).\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (FUNCALL (GET-TENSORFLOW-CALLBACK (QUOTE TENSORFLOW-NEURAL-NETWORK.NTH-INPUT-ERROR)) SELF N)))", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::nthInputError))), NULL);
  }
}

void helpStartupChameleon7() {
  {
    defineMethodObject("(DEFMETHOD SET-INPUT-VALUES ((SELF TENSORFLOW-NEURAL-NETWORK) (VALUES OBJECT)) :DOCUMENTATION \"Set the current truth-value inputs of the network `self' to float `values' in sequence.\nMissing inputs will be set to 0.0, extra values will be ignored.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::setInputValues))), NULL);
    defineMethodObject("(DEFMETHOD (GET-VECTOR-ARGUMENT-SPEC OBJECT) ((SELF TENSORFLOW-NEURAL-NETWORK) (ARG OBJECT)) :DOCUMENTATION \"Generate a single argument spec for `arg' that can be used for `set-vector-input-values'.\n`arg' can either be a proposition or justification.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::getVectorArgumentSpec))), NULL);
    defineMethodObject("(DEFMETHOD SET-VECTOR-INPUT-VALUES ((SELF TENSORFLOW-NEURAL-NETWORK) (VECTORSPECS OBJECT)) :DOCUMENTATION \"Set the current vector inputs of the network `self' to the vectors described by `vectorSpecs'.\nEach vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs\nare translated into actual numeric vectors such as embeddings is specific to the particular neural network type.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::setVectorInputValues))), NULL);
    defineMethodObject("(DEFMETHOD (FORWARD-PROPAGATE-INPUTS FLOAT) ((SELF TENSORFLOW-NEURAL-NETWORK)) :DOCUMENTATION \"Activates the current inputs of the network `self' to compute its output.\nSets `self's `output' slot and returns the computed value.  Reads input activations and\nweights and updates hidden and output activations.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::forwardPropagateInputs))), NULL);
    defineMethodObject("(DEFMETHOD BACKWARD-PROPAGATE-ERROR ((SELF TENSORFLOW-NEURAL-NETWORK) (ERROR FLOAT)) :DOCUMENTATION \"Given a properly forward activated network `self' for the current set of inputs,\nand a training `error' between the current output and the goal value, backpropagate the error and\nupdate `self's vector of input errors.  Reads output, hidden activations and weights and updates\nhidden errors and input errors.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::backwardPropagateError))), NULL);
    defineMethodObject("(DEFMETHOD UPDATE-NETWORK-WEIGHTS ((SELF TENSORFLOW-NEURAL-NETWORK) (ERROR FLOAT)) :DOCUMENTATION \"Given a properly forward activated and backpropagated network `self' for the current\ninputs and training `error', update the network's weights according to current gradients, learning rate\nand momentum terms to reduce the error for the given inputs.  Reads output, hidden and input activations,\nhidden error, weights and weight deltas, and updates weights and weight deltas.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowNeuralNetwork::updateNetworkWeights))), NULL);
    defineFunctionObject("GET-CACHED-NETWORK-PROOF", "(DEFUN (GET-CACHED-NETWORK-PROOF JUSTIFICATION) ((EXAMPLE TRAINING-EXAMPLE)) :DOCUMENTATION \"Variant of `create-cached-network' that takes a training `example',\nruns its cons query, and stores a compacted version of the associated proof tree\nas the `example's cached solution which will also be returned.  If a cached and\nup-to-date solution already exists, it will be returned instead.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getCachedNetworkProof)), NULL);
    defineFunctionObject("COMPACT-PARTIAL-PROOF-TO-NETWORK-PROOF", "(DEFUN (COMPACT-PARTIAL-PROOF-TO-NETWORK-PROOF JUSTIFICATION) ((PROOF JUSTIFICATION)) :DOCUMENTATION \"Convert `proof' into a compacted network tree form that only contains\n:AND, :OR, :MULTI and :PRIMITIVE nodes (some of which such as `instance-of' might contain\nfurther antecedents if they were computed by specialists, for example).\" :PUBLIC? TRUE)", ((cpp_function_code)(&compactPartialProofToNetworkProof)), NULL);
    defineFunctionObject("COMBINE-MULTIPLE-MATCH-SCORES", "(DEFUN (COMBINE-MULTIPLE-MATCH-SCORES FLOAT) ((SCORES (CONS OF FLOAT-WRAPPER))) :DOCUMENTATION \"Combine partial match scores from alternative :multiple-proofs `scores'\naccording to the current `*rule-combination*' strategy.\" :PUBLIC? TRUE)", ((cpp_function_code)(&combineMultipleMatchScores)), NULL);
    defineFunctionObject("FORWARD-PROPAGATE-CACHED-NETWORK-PROOF", "(DEFUN (FORWARD-PROPAGATE-CACHED-NETWORK-PROOF FLOAT) ((PROOF JUSTIFICATION)) :DOCUMENTATION \"Compute the same partial match score as the call to `compute-partial-truth'\nthat generated `proof' (which is assumed to have been compacted with a call to\n`compact-partial-proof-to-network-proof'.  The score will only be identical of course, if\nthe various networks and their weights have not yet been updated during learning.\" :PUBLIC? TRUE)", ((cpp_function_code)(&forwardPropagateCachedNetworkProof)), NULL);
    defineFunctionObject("FORWARD-PROPAGATE-CACHED-NETWORK-FROM-JUSTIFICATION", "(DEFUN (FORWARD-PROPAGATE-CACHED-NETWORK-FROM-JUSTIFICATION FLOAT) ((JUST JUSTIFICATION)) :DOCUMENTATION \"Locally forward-propagate the network associated with `just' based on\npreviously cached `positive-score's of antecedents.\" :PUBLIC? TRUE)", ((cpp_function_code)(&forwardPropagateCachedNetworkFromJustification)), NULL);
    defineFunctionObject("BACKWARD-PROPAGATE-CACHED-NETWORK-PROOF", "(DEFUN BACKWARD-PROPAGATE-CACHED-NETWORK-PROOF ((PROOF JUSTIFICATION) (ERROR FLOAT)) :DOCUMENTATION \"Propagate the `error' between `proof's conclusion and the desired target value\nthrough `proof's network and its antecedents, and adjust weights to decrease the error.  Multiple\niterations through `forward/backward-propagate-cached-network-proof' with updated top-level\nerrors will train the involved networks to minimize the error as much as possible.\" :PUBLIC? TRUE)", ((cpp_function_code)(&backwardPropagateCachedNetworkProof)), NULL);
    defineFunctionObject("BACKWARD-PROPAGATE-CACHED-NETWORK-MULTI-PROOF", "(DEFUN BACKWARD-PROPAGATE-CACHED-NETWORK-MULTI-PROOF ((PROOF JUSTIFICATION) (ERROR FLOAT)) :DOCUMENTATION \"Recurse through :multiple-proofs antecedents guided by the current rule combination scheme.\" :PUBLIC? TRUE)", ((cpp_function_code)(&backwardPropagateCachedNetworkMultiProof)), NULL);
    defineMethodObject("(DEFMETHOD CLEAR-BATCH-ARRAYS ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Clear all currently batched inputs (with keys) and associated target values.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::clearBatchArrays))), NULL);
    defineMethodObject("(DEFMETHOD (CURRENT-BATCH-SIZE INTEGER) ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Return the number of currently batched inputs.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::currentBatchSize))), NULL);
    defineMethodObject("(DEFMETHOD (BATCH-IS-FULL? BOOLEAN) ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Return true if input batch arrays have been filled to capacity.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::batchIsFullP))), NULL);
    defineMethodObject("(DEFMETHOD PUSH-INPUT-VALUES ((SELF NEURAL-NETWORK) (KEY OBJECT) (VALUES OBJECT)) :DOCUMENTATION \"Push input `values' onto the input batch array and associate them with `key' (which can be NULL).\nAssociating a key lets us easily map inputs/outputs to some processing object of interest (e.g., a justification).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::pushInputValues))), NULL);
    defineMethodObject("(DEFMETHOD PUSH-VECTOR-INPUT-VALUES ((SELF NEURAL-NETWORK) (VECTORSPECS OBJECT)) :DOCUMENTATION \"Push `vectorSpecs' onto the vector argument batch array which is assumed to correspond to the input\nvalues at the same respective position in the batch.  Truth-valued and vector-valued inputs are associated by position\nin the batch, they can be pushed independently, as long as they are fully synchronized when processing of the batch starts.\nIf `self' has no vector-valued argument, the associated batch array can be left undefined.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::pushVectorInputValues))), NULL);
    defineMethodObject("(DEFMETHOD PUSH-TARGET-VALUE ((SELF NEURAL-NETWORK) (VALUE FLOAT)) :DOCUMENTATION \"Push a target `value' onto the target batch array which is assumed to correspond to the input\nvalues at the same respective position in the batch.  Inputs and targets are associated by position in the batch,\nthey can be pushed independently, as long as they are fully synchronized when processing of the batch starts.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::pushTargetValue))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-BATCH-KEY OBJECT) ((SELF NEURAL-NETWORK) (N INTEGER)) :DOCUMENTATION \"Return the key associated with the `n'-th set of inputs in the input batch.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::nthBatchKey))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-KTH-BATCH-INPUT-ERROR FLOAT) ((SELF NEURAL-NETWORK) (N INTEGER) (K INTEGER)) :DOCUMENTATION \"Return error of the `k'-th input in the `n'-th set of inputs in the input batch.\n`k' ignores the bias unit.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::nthKthBatchInputError))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-BATCH-OUTPUT FLOAT) ((SELF NEURAL-NETWORK) (N INTEGER)) :DOCUMENTATION \"Return the output value for the `n'-th set of inputs in the input batch.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::nthBatchOutput))), NULL);
    defineMethodObject("(DEFMETHOD (BATCH-FORWARD-PROPAGATE-INPUTS FLOAT-ARRAY) ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Run forward propagation on the current input batch and store outputs in the output batch.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::batchForwardPropagateInputs))), NULL);
    defineMethodObject("(DEFMETHOD BATCH-BACKWARD-PROPAGATE-ERROR ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Run backward propagation on the current input and target batch and store back-propagated\nerrors in the input error batch.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::batchBackwardPropagateError))), NULL);
    defineMethodObject("(DEFMETHOD BATCH-UPDATE-NETWORK-WEIGHTS ((SELF NEURAL-NETWORK)) :DOCUMENTATION \"Run weight updates for the current input and target batches.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NeuralNetwork::batchUpdateNetworkWeights))), NULL);
    defineMethodObject("(DEFMETHOD ALLOCATE-NETWORK-ARRAYS ((SELF CHAMELEON-BATCH-NEURAL-NETWORK) (NUM-IN INTEGER) (NUM-HIDDEN INTEGER) (NUM-OUT INTEGER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonBatchNeuralNetwork::allocateNetworkArrays))), NULL);
    defineMethodObject("(DEFMETHOD CLEAR-BATCH-ARRAYS ((SELF CHAMELEON-BATCH-NEURAL-NETWORK)))", wrapMethodCode(((cpp_method_code)(&ChameleonBatchNeuralNetwork::clearBatchArrays))), NULL);
    defineMethodObject("(DEFMETHOD (CURRENT-BATCH-SIZE INTEGER) ((SELF CHAMELEON-BATCH-NEURAL-NETWORK)))", wrapMethodCode(((cpp_method_code)(&ChameleonBatchNeuralNetwork::currentBatchSize))), NULL);
    defineMethodObject("(DEFMETHOD (BATCH-IS-FULL? BOOLEAN) ((SELF CHAMELEON-BATCH-NEURAL-NETWORK)))", wrapMethodCode(((cpp_method_code)(&ChameleonBatchNeuralNetwork::batchIsFullP))), NULL);
    defineMethodObject("(DEFMETHOD PUSH-INPUT-VALUES ((SELF CHAMELEON-BATCH-NEURAL-NETWORK) (KEY OBJECT) (VALUES OBJECT)))", wrapMethodCode(((cpp_method_code)(&ChameleonBatchNeuralNetwork::pushInputValues))), NULL);
    defineMethodObject("(DEFMETHOD PUSH-TARGET-VALUE ((SELF CHAMELEON-BATCH-NEURAL-NETWORK) (VALUE FLOAT)))", wrapMethodCode(((cpp_method_code)(&ChameleonBatchNeuralNetwork::pushTargetValue))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-BATCH-KEY OBJECT) ((SELF CHAMELEON-BATCH-NEURAL-NETWORK) (N INTEGER)))", wrapMethodCode(((cpp_method_code)(&ChameleonBatchNeuralNetwork::nthBatchKey))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-KTH-BATCH-INPUT-ERROR FLOAT) ((SELF CHAMELEON-BATCH-NEURAL-NETWORK) (N INTEGER) (K INTEGER)))", wrapMethodCode(((cpp_method_code)(&ChameleonBatchNeuralNetwork::nthKthBatchInputError))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-BATCH-OUTPUT FLOAT) ((SELF CHAMELEON-BATCH-NEURAL-NETWORK) (N INTEGER)))", wrapMethodCode(((cpp_method_code)(&ChameleonBatchNeuralNetwork::nthBatchOutput))), NULL);
    defineMethodObject("(DEFMETHOD (BATCH-FORWARD-PROPAGATE-INPUTS FLOAT-ARRAY) ((SELF CHAMELEON-BATCH-NEURAL-NETWORK)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonBatchNeuralNetwork::batchForwardPropagateInputs))), NULL);
    defineMethodObject("(DEFMETHOD (COPY-INPUT-ERROR FLOAT-ARRAY) ((SELF CHAMELEON-BATCH-NEURAL-NETWORK)))", wrapMethodCode(((cpp_method_code)(&ChameleonBatchNeuralNetwork::copyInputError))), NULL);
    defineMethodObject("(DEFMETHOD BATCH-BACKWARD-PROPAGATE-ERROR ((SELF CHAMELEON-BATCH-NEURAL-NETWORK)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonBatchNeuralNetwork::batchBackwardPropagateError))), NULL);
    defineMethodObject("(DEFMETHOD BATCH-UPDATE-NETWORK-WEIGHTS ((SELF CHAMELEON-BATCH-NEURAL-NETWORK)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ChameleonBatchNeuralNetwork::batchUpdateNetworkWeights))), NULL);
    defineMethodObject("(DEFMETHOD (THE-ARRAY-READER (ARRAY () OF (LIKE (ANY-VALUE SELF)))) ((SELF 2D-LONG-ARRAY)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&twoDLongArray::theArrayReader))), NULL);
    defineMethodObject("(DEFMETHOD PRINT-NETWORK-ARRAYS ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK)))", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::printNetworkArrays))), NULL);
    defineMethodObject("(DEFMETHOD ALLOCATE-NETWORK-ARRAYS ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK) (NUM-IN INTEGER) (NUM-HIDDEN INTEGER) (NUM-OUT INTEGER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::allocateNetworkArrays))), NULL);
    defineMethodObject("(DEFMETHOD BUILD-PROPOSITION-NETWORK ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK) (PROP PROPOSITION)) :DOCUMENTATION \"Build a neural network for the proposition `prop'.  This builds a two-layer\nperceptron network whose input nodes are activated by the truth of `prop's arguments and whose\noutput node computes the truth of `prop'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::buildPropositionNetwork))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-OF-INPUTS INTEGER) ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK)) :DOCUMENTATION \"Return the number of input values expected by `self' (ignores bias unit).\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (1- (DIM2 (INPUT-BATCH SELF)))))", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::numberOfInputs))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-INPUT FLOAT) ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK) (N INTEGER)) :DOCUMENTATION \"Return the 0-based `n'-th proposition input of `self' (ignores bias unit).\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (IGNORE N) (ERROR \"nth-input: not supported on: \" SELF))", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::nthInput))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-INPUT-ERROR FLOAT) ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK) (N INTEGER)) :DOCUMENTATION \"Return the 0-based `n'-th proposition input error of `self' (ignores bias unit).\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (IGNORE N) (ERROR \"nth-input-error: not supported on: \" SELF))", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::nthInputError))), NULL);
    defineMethodObject("(DEFMETHOD SET-INPUT-VALUES ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK) (VALUES OBJECT)) :DOCUMENTATION \"Set the current truth-value inputs of the network `self' to float `values' in sequence.\nMissing inputs will be set to 0.0, extra values will be ignored.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::setInputValues))), NULL);
    defineMethodObject("(DEFMETHOD (GET-VECTOR-ARGUMENT-SPEC OBJECT) ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK) (ARG OBJECT)) :DOCUMENTATION \"Generate a single argument spec for `arg' that can be used for `set-vector-input-values'.\n`arg' can either be a proposition or justification.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::getVectorArgumentSpec))), NULL);
    defineMethodObject("(DEFMETHOD SET-VECTOR-INPUT-VALUES ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK) (VECTORSPECS OBJECT)) :DOCUMENTATION \"Set the current vector inputs of the network `self' to the vectors described by `vectorSpecs'.\nEach vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs\nare translated into actual numeric vectors such as embeddings is specific to the particular neural network type.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::setVectorInputValues))), NULL);
    defineMethodObject("(DEFMETHOD (FORWARD-PROPAGATE-INPUTS FLOAT) ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK)) :DOCUMENTATION \"Activates the current inputs of the network `self' to compute its output.\nSets `self's `output' slot and returns the computed value.  Reads input activations and\nweights and updates hidden and output activations.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::forwardPropagateInputs))), NULL);
    defineMethodObject("(DEFMETHOD CLEAR-BATCH-ARRAYS ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK)))", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::clearBatchArrays))), NULL);
    defineMethodObject("(DEFMETHOD (CURRENT-BATCH-SIZE INTEGER) ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK)))", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::currentBatchSize))), NULL);
    defineMethodObject("(DEFMETHOD (BATCH-IS-FULL? BOOLEAN) ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK)))", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::batchIsFullP))), NULL);
    defineMethodObject("(DEFMETHOD PUSH-INPUT-VALUES ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK) (KEY OBJECT) (VALUES OBJECT)))", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::pushInputValues))), NULL);
    defineMethodObject("(DEFMETHOD PUSH-VECTOR-INPUT-VALUES ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK) (VECTORSPECS OBJECT)))", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::pushVectorInputValues))), NULL);
    defineMethodObject("(DEFMETHOD PUSH-TARGET-VALUE ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK) (VALUE FLOAT)))", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::pushTargetValue))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-BATCH-KEY OBJECT) ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK) (N INTEGER)))", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::nthBatchKey))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-KTH-BATCH-INPUT-ERROR FLOAT) ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK) (N INTEGER) (K INTEGER)))", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::nthKthBatchInputError))), NULL);
    defineMethodObject("(DEFMETHOD (NTH-BATCH-OUTPUT FLOAT) ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK) (N INTEGER)))", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::nthBatchOutput))), NULL);
    defineMethodObject("(DEFMETHOD (BATCH-FORWARD-PROPAGATE-INPUTS FLOAT-ARRAY) ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::batchForwardPropagateInputs))), NULL);
    defineMethodObject("(DEFMETHOD BATCH-BACKWARD-PROPAGATE-ERROR ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::batchBackwardPropagateError))), NULL);
  }
}

void startupChameleon() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupChameleon1();
      helpStartupChameleon2();
      helpStartupChameleon3();
    }
    if (currentStartupTimePhaseP(4)) {
      oALL_NEURAL_NETWORKSo = newKeyValueMap();
      oCHAMELEON_NEURAL_NETWORK_IMPLEMENTATIONo = KWD_CHAMELEON_ORIGINAL;
      oWRAPPED_CHAMELEON_DEFAULT_INPUT_VALUEo = wrapFloat(oCHAMELEON_DEFAULT_INPUT_VALUEo);
    }
    if (currentStartupTimePhaseP(5)) {
      helpStartupChameleon4();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupChameleon5();
      helpStartupChameleon6();
      helpStartupChameleon7();
      defineMethodObject("(DEFMETHOD BATCH-UPDATE-NETWORK-WEIGHTS ((SELF TENSORFLOW-BATCH-NEURAL-NETWORK)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TensorflowBatchNeuralNetwork::batchUpdateNetworkWeights))), NULL);
      defineFunctionObject("ADD-NETWORK-PROOF-DEPENDENCY-LINK", "(DEFUN ADD-NETWORK-PROOF-DEPENDENCY-LINK ((TABLE KEY-VALUE-MAP) (SUBJECT JUSTIFICATION) (OBJECT JUSTIFICATION)))", ((cpp_function_code)(&addNetworkProofDependencyLink)), NULL);
      defineFunctionObject("REMOVE-NETWORK-PROOF-DEPENDENCY-LINK", "(DEFUN REMOVE-NETWORK-PROOF-DEPENDENCY-LINK ((TABLE KEY-VALUE-MAP) (SUBJECT JUSTIFICATION) (OBJECT JUSTIFICATION)))", ((cpp_function_code)(&removeNetworkProofDependencyLink)), NULL);
      defineMethodObject("(DEFMETHOD ADD-DEPENDENT ((QUEUE NETWORK-PROOF-QUEUE) (PREREQUISITE JUSTIFICATION) (DEPENDENT JUSTIFICATION)))", wrapMethodCode(((cpp_method_code)(&NetworkProofQueue::addDependent))), NULL);
      defineMethodObject("(DEFMETHOD REMOVE-DEPENDENT ((QUEUE NETWORK-PROOF-QUEUE) (PREREQUISITE JUSTIFICATION) (DEPENDENT JUSTIFICATION)))", wrapMethodCode(((cpp_method_code)(&NetworkProofQueue::removeDependent))), NULL);
      defineMethodObject("(DEFMETHOD (GET-DEPENDENTS (CONS OF JUSTIFICATION)) ((QUEUE NETWORK-PROOF-QUEUE) (PREREQUISITE JUSTIFICATION)))", wrapMethodCode(((cpp_method_code)(&NetworkProofQueue::getDependents))), NULL);
      defineMethodObject("(DEFMETHOD (HAS-DEPENDENT? BOOLEAN) ((QUEUE NETWORK-PROOF-QUEUE) (PREREQUISITE JUSTIFICATION) (DEPENDENT JUSTIFICATION)))", wrapMethodCode(((cpp_method_code)(&NetworkProofQueue::hasDependentP))), NULL);
      defineMethodObject("(DEFMETHOD (GET-PREREQUISITES (CONS OF JUSTIFICATION)) ((QUEUE NETWORK-PROOF-QUEUE) (DEPENDENT JUSTIFICATION)))", wrapMethodCode(((cpp_method_code)(&NetworkProofQueue::getPrerequisites))), NULL);
      defineMethodObject("(DEFMETHOD (HAS-PREREQUISITE? BOOLEAN) ((QUEUE NETWORK-PROOF-QUEUE) (DEPENDENT JUSTIFICATION) (PREREQUISITE JUSTIFICATION)))", wrapMethodCode(((cpp_method_code)(&NetworkProofQueue::hasPrerequisiteP))), NULL);
      defineMethodObject("(DEFMETHOD BATCH-PROCESS-CACHED-NETWORK-PROOF ((QUEUE NETWORK-PROOF-QUEUE) (PROOF JUSTIFICATION)))", wrapMethodCode(((cpp_method_code)(&NetworkProofQueue::batchProcessCachedNetworkProof))), NULL);
      defineMethodObject("(DEFMETHOD QUEUE-NETWORK-OPERATION ((QUEUE NETWORK-PROOF-QUEUE) (PROOF JUSTIFICATION)))", wrapMethodCode(((cpp_method_code)(&NetworkProofQueue::queueNetworkOperation))), NULL);
      defineMethodObject("(DEFMETHOD EXECUTE-NETWORK-OPERATION ((QUEUE NETWORK-PROOF-QUEUE) (NET NEURAL-NETWORK) (FORCE? BOOLEAN)))", wrapMethodCode(((cpp_method_code)(&NetworkProofQueue::executeNetworkOperation))), NULL);
      defineMethodObject("(DEFMETHOD BATCH-PROCESS-CACHED-NETWORK-PROOF ((QUEUE NETWORK-PROOF-FORWARD-QUEUE) (PROOF JUSTIFICATION)) :DOCUMENTATION \"Compute the same partial match score as the call to `compute-partial-truth'\nthat generated `proof' (which is assumed to have been compacted with a call to\n`compact-partial-proof-to-network-proof'.  The score will only be identical of course, if\nthe various networks and their weights have not yet been updated during learning.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NetworkProofForwardQueue::batchProcessCachedNetworkProof))), NULL);
      defineMethodObject("(DEFMETHOD NOTIFY-OF-COMPLETION ((QUEUE NETWORK-PROOF-QUEUE) (PROOF JUSTIFICATION) (PREREQUISITE JUSTIFICATION)) :DOCUMENTATION \"Notify `proof' that one of its `prerequisite's had its computation completed.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NetworkProofQueue::notifyOfCompletion))), NULL);
      defineMethodObject("(DEFMETHOD QUEUE-INPUT-VALUES ((QUEUE NETWORK-PROOF-QUEUE) (NET NEURAL-NETWORK) (PROOF JUSTIFICATION) (INPUTS OBJECT) (VECTORSPECS OBJECT)) :DOCUMENTATION \"Queue `inputs' in `net's input batch.  Execute the current batch if we are full.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NetworkProofQueue::queueInputValues))), NULL);
      defineMethodObject("(DEFMETHOD QUEUE-NETWORK-OPERATION ((QUEUE NETWORK-PROOF-FORWARD-QUEUE) (PROOF JUSTIFICATION)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NetworkProofForwardQueue::queueNetworkOperation))), NULL);
      defineMethodObject("(DEFMETHOD EXECUTE-NETWORK-OPERATION ((QUEUE NETWORK-PROOF-FORWARD-QUEUE) (NET NEURAL-NETWORK) (FORCE? BOOLEAN)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NetworkProofForwardQueue::executeNetworkOperation))), NULL);
      defineMethodObject("(DEFMETHOD EXECUTE-ALL ((QUEUE NETWORK-PROOF-QUEUE)) :DOCUMENTATION \"Execute queued ops in `queue' until there is nothing more to do.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NetworkProofQueue::executeAll))), NULL);
      defineExternalSlotFromStringifiedSource("(DEFSLOT JUSTIFICATION TRAINING-ERROR :RENAMES ERROR-SCORE :DOCUMENTATION \"More suggestive name for this slot which is used to store and propagate errors during training.\")");
      defineMethodObject("(DEFMETHOD BATCH-PROCESS-CACHED-NETWORK-PROOF ((QUEUE NETWORK-PROOF-BACKWARD-QUEUE) (PROOF JUSTIFICATION)) :DOCUMENTATION \"Queue and process operations for `update-network-weights' for `proof'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NetworkProofBackwardQueue::batchProcessCachedNetworkProof))), NULL);
      defineMethodObject("(DEFMETHOD QUEUE-NETWORK-OPERATION ((QUEUE NETWORK-PROOF-BACKWARD-QUEUE) (PROOF JUSTIFICATION)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NetworkProofBackwardQueue::queueNetworkOperation))), NULL);
      defineMethodObject("(DEFMETHOD EXECUTE-NETWORK-OPERATION ((QUEUE NETWORK-PROOF-BACKWARD-QUEUE) (NET NEURAL-NETWORK) (FORCE? BOOLEAN)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NetworkProofBackwardQueue::executeNetworkOperation))), NULL);
      defineMethodObject("(DEFMETHOD BATCH-PROCESS-CACHED-NETWORK-PROOF ((QUEUE NETWORK-PROOF-UPDATE-QUEUE) (PROOF JUSTIFICATION)) :DOCUMENTATION \"Queue and process operations for `update-network-weights' for `proof'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NetworkProofUpdateQueue::batchProcessCachedNetworkProof))), NULL);
      defineMethodObject("(DEFMETHOD QUEUE-NETWORK-OPERATION ((QUEUE NETWORK-PROOF-UPDATE-QUEUE) (PROOF JUSTIFICATION)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NetworkProofUpdateQueue::queueNetworkOperation))), NULL);
      defineMethodObject("(DEFMETHOD EXECUTE-NETWORK-OPERATION ((QUEUE NETWORK-PROOF-UPDATE-QUEUE) (NET NEURAL-NETWORK) (FORCE? BOOLEAN)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NetworkProofUpdateQueue::executeNetworkOperation))), NULL);
      defineFunctionObject("RETRIEVE-TRAINING-EXAMPLES", "(DEFUN (RETRIEVE-TRAINING-EXAMPLES (LIST OF TRAINING-EXAMPLE)) (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Retrieve a subset of current training examples defined via `cham/training-example'.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&retrieveTrainingExamples)), ((cpp_function_code)(&retrieveTrainingExamplesEvaluatorWrapper)));
      defineFunctionObject("SELECT-TRAINING-EXAMPLES", "(DEFUN (SELECT-TRAINING-EXAMPLES (VECTOR OF TRAINING-EXAMPLE)) (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Select a subset of currently defined training examples.  Currently the selection\nis purely based on module and/or number.  Results will be shuffled if :shuffle? is TRUE (default).\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&selectTrainingExamples)), ((cpp_function_code)(&selectTrainingExamplesEvaluatorWrapper)));
      defineFunctionObject("NORMALIZE-CHAMELEON-TRAINING-OPTIONS", "(DEFUN (NORMALIZE-CHAMELEON-TRAINING-OPTIONS PROPERTY-LIST) ((OPTIONS OBJECT)) :DOCUMENTATION \"Normalize and provide defaults for `options' supplied\nto `train-chameleon-neural-networks'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&normalizeChameleonTrainingOptions)), NULL);
      defineFunctionObject("TRAIN-CHAMELEON-NEURAL-NETWORKS", "(DEFUN TRAIN-CHAMELEON-NEURAL-NETWORKS (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Train rule neural networks based on :n-train (or all) training examples looked\nup in :module/:local?.  Train for :epochs (defaults to 20) or until :error-cutoff is reached.\nPrint every :print-cycle epochs or not at all.  If :shuffle? (the default) randomly shuffle the\nselected training examples before every epoch.  If :batch?, use batch training mechanism (which\nwill fail if the current network implementation does not support it).\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&trainChameleonNeuralNetworks)), ((cpp_function_code)(&trainChameleonNeuralNetworksEvaluatorWrapper)));
      defineFunctionObject("SCORED-QUERY-SPECIALIST", "(DEFUN (SCORED-QUERY-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&scoredQuerySpecialist)), NULL);
      defineFunctionObject("MATCH-SCORE-SPECIALIST", "(DEFUN (MATCH-SCORE-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&matchScoreSpecialist)), NULL);
      defineFunctionObject("STARTUP-CHAMELEON", "(DEFUN STARTUP-CHAMELEON () :PUBLIC? TRUE)", ((cpp_function_code)(&startupChameleon)), NULL);
      { MethodSlot* function = lookupFunction(SYM_CHAMELEON_LOGIC_STARTUP_CHAMELEON);

        setDynamicSlotValue(function->dynamicSlots, SYM_CHAMELEON_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupChameleon"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFGLOBAL *CHAMELEON-MODULE* MODULE NULL :DOCUMENTATION \"Namespace module for Chameleon relations\")", &oCHAMELEON_MODULEo);
      defineGlobalVariableObject("(DEFGLOBAL *CHAMELEON-DEFAULT-DEFAULT-SCORE* FLOAT 0.01 :DOCUMENTATION \"Default weight to use for unknown propositions that don't have a relation-specific value specified.\" :DEMON-PROPERTY \"powerloom.chameleon.defaultDefaultScore\" :PUBLIC? TRUE)", &oCHAMELEON_DEFAULT_DEFAULT_SCOREo);
      defineExplanationPhrase(KWD_CHAMELEON_MULTIPLE_PROOFS, KWD_CHAMELEON_TECHNICAL, "from multiple proofs", 0);
      defineExplanationPhrase(KWD_CHAMELEON_MULTIPLE_PROOFS, KWD_CHAMELEON_LAY, "from multiple proofs", 0);
      defineGlobalVariableObject("(DEFGLOBAL *ALL-NEURAL-NETWORKS* (KEY-VALUE-MAP OF INTEGER-WRAPPER (CONS OF NEURAL-NETWORK)) (NEW KEY-VALUE-MAP))", &oALL_NEURAL_NETWORKSo);
      defineGlobalVariableObject("(DEFGLOBAL *CHAMELEON-NEURAL-NETWORK-IMPLEMENTATION* KEYWORD :ORIGINAL :DEMON-PROPERTY \"powerloom.chameleon.neuralNetworkImplementation\" :PUBLIC? TRUE)", &oCHAMELEON_NEURAL_NETWORK_IMPLEMENTATIONo);
      defineGlobalVariableObject("(DEFGLOBAL *CHAMELEON-DEFAULT-INPUT-VALUE* FLOAT 0.0)", &oCHAMELEON_DEFAULT_INPUT_VALUEo);
      defineGlobalVariableObject("(DEFGLOBAL *WRAPPED-CHAMELEON-DEFAULT-INPUT-VALUE* FLOAT-WRAPPER (WRAP-FLOAT *CHAMELEON-DEFAULT-INPUT-VALUE*))", &oWRAPPED_CHAMELEON_DEFAULT_INPUT_VALUEo);
      defineGlobalVariableObject("(DEFGLOBAL *NEURAL-NETWORK-BATCH-SIZE* INTEGER 128 :DEMON-PROPERTY \"powerloom.chameleon.neuralNetworkBatchSize\" :PUBLIC? TRUE)", &oNEURAL_NETWORK_BATCH_SIZEo);
      defineGlobalVariableObject("(DEFGLOBAL *BATCH-OPERATION-COUNT* INTEGER 0)", &oBATCH_OPERATION_COUNTo);
      defineGlobalVariableObject("(DEFGLOBAL *BATCH-TOTAL-COUNT* INTEGER 0)", &oBATCH_TOTAL_COUNTo);
    }
  }
}

Surrogate* SGT_CHAMELEON_CHAMELEON_TRUTH_VALUE_RELATION = NULL;

Surrogate* SGT_CHAMELEON_CHAMELEON_VECTOR_RELATION = NULL;

Surrogate* SGT_CHAMELEON_CHAMELEON_IGNORED_VALUE_RELATION = NULL;

Surrogate* SGT_CHAMELEON_CHAMELEON_PRIMITIVE_VALUE_RELATION = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_CHAMELEON_PARTIAL_MATCH = NULL;

Symbol* SYM_CHAMELEON_LOGIC_ARGUMENT_JUSTIFICATIONS = NULL;

Symbol* SYM_CHAMELEON_LOGIC_ARGUMENT_PROPOSITIONS = NULL;

Keyword* KWD_CHAMELEON_AND = NULL;

Keyword* KWD_CHAMELEON_OR = NULL;

Keyword* KWD_CHAMELEON_ATOMIC_GOAL = NULL;

Keyword* KWD_CHAMELEON_UP_TRUE = NULL;

Keyword* KWD_CHAMELEON_UP_FAIL = NULL;

Keyword* KWD_CHAMELEON_DOWN = NULL;

Symbol* SYM_CHAMELEON_LOGIC_JUSTIFICATION = NULL;

Keyword* KWD_CHAMELEON_GOAL_TREE = NULL;

Keyword* KWD_CHAMELEON_OR_INTRODUCTION = NULL;

Keyword* KWD_CHAMELEON_FAILURE = NULL;

Keyword* KWD_CHAMELEON_OTHER = NULL;

Keyword* KWD_CHAMELEON_VARIANT1 = NULL;

Keyword* KWD_CHAMELEON_FINAL_SUCCESS = NULL;

Keyword* KWD_CHAMELEON_VARIANT2 = NULL;

Symbol* SYM_CHAMELEON_LOGIC_ANTECEDENTS_RULE = NULL;

Keyword* KWD_CHAMELEON_MULTIPLE_PROOFS = NULL;

Keyword* KWD_CHAMELEON_TECHNICAL = NULL;

Keyword* KWD_CHAMELEON_LAY = NULL;

Keyword* KWD_CHAMELEON_MINIMUM_SCORE = NULL;

Keyword* KWD_CHAMELEON_MAXIMIZE_SCOREp = NULL;

Keyword* KWD_CHAMELEON_RECORD_JUSTIFICATIONSp = NULL;

Surrogate* SGT_CHAMELEON_STELLA_BOOLEAN = NULL;

Keyword* KWD_CHAMELEON_NOISY_OR = NULL;

Keyword* KWD_CHAMELEON_ORIGINAL = NULL;

Symbol* SYM_CHAMELEON_LOGIC_NEURAL_NET = NULL;

Keyword* KWD_CHAMELEON_PROPOSITION = NULL;

Keyword* KWD_CHAMELEON_CHAMELEON = NULL;

Keyword* KWD_CHAMELEON_CHAMELEON_BATCH = NULL;

Keyword* KWD_CHAMELEON_TENSORFLOW = NULL;

Keyword* KWD_CHAMELEON_TENSORFLOW_BATCH = NULL;

Keyword* KWD_CHAMELEON_NOT = NULL;

Keyword* KWD_CHAMELEON_FAIL = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_PROPOSITION = NULL;

Keyword* KWD_CHAMELEON_TRUTH_VALUE = NULL;

Keyword* KWD_CHAMELEON_IGNORED_VALUE = NULL;

Keyword* KWD_CHAMELEON_VECTOR = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_M_NEURAL_NETWORKdTRUTH_VALUE_ARGUMENT_INDEX_MEMO_TABLE_000 = NULL;

Keyword* KWD_CHAMELEON_QUICKPROP = NULL;

Surrogate* SGT_CHAMELEON_STELLA_CONS = NULL;

Surrogate* SGT_CHAMELEON_STELLA_LIST = NULL;

Surrogate* SGT_CHAMELEON_STELLA_VECTOR = NULL;

Surrogate* SGT_CHAMELEON_STELLA_SEQUENCE = NULL;

Surrogate* SGT_CHAMELEON_STELLA_ITERATOR = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_CHAMELEON_NEURAL_NETWORK = NULL;

Symbol* SYM_CHAMELEON_LOGIC_PROPOSITION = NULL;

Symbol* SYM_CHAMELEON_LOGIC_INPUT = NULL;

Symbol* SYM_CHAMELEON_LOGIC_HIDDEN = NULL;

Symbol* SYM_CHAMELEON_LOGIC_OUTPUT = NULL;

Symbol* SYM_CHAMELEON_LOGIC_IH = NULL;

Symbol* SYM_CHAMELEON_LOGIC_HO = NULL;

Symbol* SYM_CHAMELEON_LOGIC_INPUT_ERROR = NULL;

Symbol* SYM_CHAMELEON_LOGIC_HIDDEN_ERROR = NULL;

Symbol* SYM_CHAMELEON_LOGIC_OUTPUT_ERROR = NULL;

Symbol* SYM_CHAMELEON_LOGIC_IH_DELTA = NULL;

Symbol* SYM_CHAMELEON_LOGIC_HO_DELTA = NULL;

Surrogate* SGT_CHAMELEON_STELLA_FLOAT_ARRAY = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_VECTOR_NEURAL_NETWORK = NULL;

Symbol* SYM_CHAMELEON_LOGIC_N_VECTOR_ARGUMENTS = NULL;

Symbol* SYM_CHAMELEON_LOGIC_N_VECTOR_ARGUMENT_SPECS = NULL;

Symbol* SYM_CHAMELEON_LOGIC_N_VECTOR_ARGUMENT_INPUTS = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_M_VECTOR_NEURAL_NETWORKdVECTOR_ARGUMENT_INDEX_MEMO_TABLE_000 = NULL;

Surrogate* SGT_CHAMELEON_CHAMELEON_VECTOR_ARITY = NULL;

Surrogate* SGT_CHAMELEON_CHAMELEON_VECTOR_DIMENSIONS = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_JUSTIFICATION = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORK = NULL;

Symbol* SYM_CHAMELEON_LOGIC_MODEL = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdBUILD_PROPOSITION_NETWORK = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdALLOCATE_NETWORK_ARRAYS = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdRANDOMIZE_NETWORK_WEIGHTS = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdINITIALIZE_NETWORK_WEIGHTS = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdNUMBER_OF_INPUTS = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdNTH_INPUT = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdNTH_INPUT_ERROR = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdSET_INPUT_VALUES = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdSET_VECTOR_INPUT_VALUES = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdFORWARD_PROPAGATE_INPUTS = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdBACKWARD_PROPAGATE_ERROR = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdUPDATE_NETWORK_WEIGHTS = NULL;

Keyword* KWD_CHAMELEON_MATCH_MODE = NULL;

Keyword* KWD_CHAMELEON_WARNING = NULL;

Keyword* KWD_CHAMELEON_PRIMITIVE_STRATEGY = NULL;

Keyword* KWD_CHAMELEON_GOAL_COMPLEMENT = NULL;

Keyword* KWD_CHAMELEON_AND_INTRODUCTION = NULL;

Keyword* KWD_CHAMELEON_DISPROOF = NULL;

Keyword* KWD_CHAMELEON_MODUS_PONENS = NULL;

Keyword* KWD_CHAMELEON_MODUS_TOLLENS = NULL;

Keyword* KWD_CHAMELEON_SUBSUMPTION_REASONING = NULL;

Keyword* KWD_CHAMELEON_FAIL_INTRODUCTION = NULL;

Keyword* KWD_CHAMELEON_MAX = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_CHAMELEON_BATCH_NEURAL_NETWORK = NULL;

Symbol* SYM_CHAMELEON_LOGIC_INPUT_BATCH = NULL;

Symbol* SYM_CHAMELEON_LOGIC_KEY_BATCH = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TARGET_BATCH = NULL;

Symbol* SYM_CHAMELEON_LOGIC_OUTPUT_BATCH = NULL;

Symbol* SYM_CHAMELEON_LOGIC_INPUT_ERROR_BATCH = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_2D_LONG_ARRAY = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORK = NULL;

Symbol* SYM_CHAMELEON_LOGIC_INPUT_MODIFIEDp = NULL;

Symbol* SYM_CHAMELEON_LOGIC_INPUT_BATCH_LENGTH = NULL;

Symbol* SYM_CHAMELEON_LOGIC_VECTOR_BATCH = NULL;

Symbol* SYM_CHAMELEON_LOGIC_VECTOR_BATCH_LENGTH = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TARGET_BATCH_LENGTH = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_FORWARD_PROPAGATE_INPUTS = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_BACKWARD_PROPAGATE_ERROR = NULL;

Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_UPDATE_NETWORK_WEIGHTS = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_NETWORK_PROOF_QUEUE = NULL;

Symbol* SYM_CHAMELEON_LOGIC_DEPENDENTS = NULL;

Symbol* SYM_CHAMELEON_LOGIC_PREREQUISITES = NULL;

Symbol* SYM_CHAMELEON_LOGIC_ACTIVE_NETWORKS = NULL;

Symbol* SYM_CHAMELEON_LOGIC_MIN_BATCH_SIZE = NULL;

Symbol* SYM_CHAMELEON_LOGIC_N_QUEUED = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_NETWORK_PROOF_FORWARD_QUEUE = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_NETWORK_PROOF_BACKWARD_QUEUE = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_NETWORK_PROOF_UPDATE_QUEUE = NULL;

Keyword* KWD_CHAMELEON_MODULE = NULL;

Surrogate* SGT_CHAMELEON_STELLA_MODULE = NULL;

Keyword* KWD_CHAMELEON_LOCALp = NULL;

Keyword* KWD_CHAMELEON_N_TRAIN = NULL;

Surrogate* SGT_CHAMELEON_STELLA_INTEGER = NULL;

Symbol* SYM_CHAMELEON_CHAMELEON_TRAINING_EXAMPLE = NULL;

Symbol* SYM_CHAMELEON_LOGIC_pP = NULL;

Symbol* SYM_CHAMELEON_LOGIC_pS = NULL;

Keyword* KWD_CHAMELEON_SHUFFLEp = NULL;

Keyword* KWD_CHAMELEON_OPTIONS = NULL;

Keyword* KWD_CHAMELEON_EPOCHS = NULL;

Keyword* KWD_CHAMELEON_PRINT_CYCLE = NULL;

Keyword* KWD_CHAMELEON_ERROR_CUTOFF = NULL;

Surrogate* SGT_CHAMELEON_STELLA_FLOAT = NULL;

Keyword* KWD_CHAMELEON_BATCHp = NULL;

Keyword* KWD_CHAMELEON_EXAMPLES = NULL;

Surrogate* SGT_CHAMELEON_STELLA_OBJECT = NULL;

Surrogate* SGT_CHAMELEON_LOGIC_SCORED_QUERY_PROOF_ADJUNCT = NULL;

Symbol* SYM_CHAMELEON_LOGIC_PARTIAL_MATCH_STRATEGY = NULL;

Symbol* SYM_CHAMELEON_LOGIC_DOWN_FRAME = NULL;

Symbol* SYM_CHAMELEON_LOGIC_PROOF_ADJUNCT = NULL;

Keyword* KWD_CHAMELEON_TERMINAL_FAILURE = NULL;

Keyword* KWD_CHAMELEON_MOVE_DOWN = NULL;

Surrogate* SGT_CHAMELEON_STELLA_NUMBER_WRAPPER = NULL;

Keyword* KWD_CHAMELEON_SCORED_QUERY = NULL;

Keyword* KWD_CHAMELEON_CONTINUING_SUCCESS = NULL;

Keyword* KWD_CHAMELEON_MATCH_SCORE = NULL;

Symbol* SYM_CHAMELEON_LOGIC_STARTUP_CHAMELEON = NULL;

Symbol* SYM_CHAMELEON_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
