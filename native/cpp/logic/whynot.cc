//  -*- Mode: C++ -*-

// whynot.cc

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

WhynotPartialMatch* newWhynotPartialMatch(Keyword* kind, ControlFrame* controlFrame) {
  { WhynotPartialMatch* self = NULL;

    self = new WhynotPartialMatch();
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
    self->unknownGoalCutoff = NULL_INTEGER;
    initializeIncrementalPartialMatch(self);
    return (self);
  }
}

Surrogate* WhynotPartialMatch::primaryType() {
  { WhynotPartialMatch* self = this;

    return (SGT_WHYNOT_LOGIC_WHYNOT_PARTIAL_MATCH);
  }
}

Object* accessWhynotPartialMatchSlotValue(WhynotPartialMatch* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_WHYNOT_LOGIC_UNKNOWN_GOAL_CUTOFF) {
    if (setvalueP) {
      self->unknownGoalCutoff = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->unknownGoalCutoff);
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

WhynotDeepPartialMatch* newWhynotDeepPartialMatch(Keyword* kind, ControlFrame* controlFrame) {
  { WhynotDeepPartialMatch* self = NULL;

    self = new WhynotDeepPartialMatch();
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
    self->unknownGoalCutoff = NULL_INTEGER;
    initializeIncrementalPartialMatch(self);
    return (self);
  }
}

Surrogate* WhynotDeepPartialMatch::primaryType() {
  { WhynotDeepPartialMatch* self = this;

    return (SGT_WHYNOT_LOGIC_WHYNOT_DEEP_PARTIAL_MATCH);
  }
}

boolean whynotPartialMatchModeP() {
  return ((((boolean)(oQUERYITERATORo)) &&
      ((boolean)(oQUERYITERATORo->partialMatchStrategy))) &&
      isaP(oQUERYITERATORo->partialMatchStrategy, SGT_WHYNOT_LOGIC_WHYNOT_PARTIAL_MATCH));
}

PartialMatchFrame* WhynotPartialMatch::createPartialMatchFrame(ControlFrame* frame, Keyword* kind) {
  { WhynotPartialMatch* self = this;

    return (newWhynotPartialMatch(kind, frame));
  }
}

PartialMatchFrame* WhynotDeepPartialMatch::createPartialMatchFrame(ControlFrame* frame, Keyword* kind) {
  { WhynotDeepPartialMatch* self = this;

    return (newWhynotDeepPartialMatch(kind, frame));
  }
}

void WhynotPartialMatch::setDynamicCutoff() {
  { WhynotPartialMatch* self = this;

    { double cutoff = self->computeDynamicCutoff();

      if (cutoff != NULL_FLOAT) {
        if ((cutoff < -100) ||
            (cutoff > 100)) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "*** fishy dynamic cutoff=" << "`" << cutoff << "'" << " computed, resetting to 0.0" << std::endl;
          cutoff = 0.0;
        }
        self->dynamicCutoff = cutoff;
      }
      self->unknownGoalCutoff = self->computeUnknownGoalCutoff();
    }
  }
}

int WhynotPartialMatch::computeUnknownGoalCutoff() {
  { WhynotPartialMatch* self = this;

    { WhynotPartialMatch* parent = ((WhynotPartialMatch*)(((IncrementalPartialMatch*)(self->parent))));
      int parentcutoff = NULL_INTEGER;
      int cutoff = NULL_INTEGER;

      if (((boolean)(parent))) {
        parentcutoff = parent->unknownGoalCutoff;
        if (parentcutoff == NULL_INTEGER) {
          return (NULL_INTEGER);
        }
        if (parent->kind == KWD_WHYNOT_AND) {
          { ControlFrame* parentframe = parent->controlFrame;
            int siblingunknowns = 0;

            { int i = NULL_INTEGER;
              int iter000 = 0;
              int upperBound000 = parentframe->argumentCursor - 1;

              for  (; iter000 <= upperBound000; 
                    iter000 = iter000 + 1) {
                i = iter000;
                siblingunknowns = siblingunknowns + ((WhynotPartialMatch*)(((ControlFrame*)((((Vector*)(dynamicSlotValue(parentframe->dynamicSlots, SYM_WHYNOT_STELLA_ARGUMENTS, NULL)))->theArray)[i]))->partialMatchFrame))->numberOfFailedSubgoals();
              }
            }
            cutoff = stella::integerMax(parentcutoff - siblingunknowns, 0);
          }
        }
        else {
          cutoff = parentcutoff;
        }
      }
      return (cutoff);
    }
  }
}

int WhynotPartialMatch::numberOfFailedSubgoals() {
  { WhynotPartialMatch* self = this;

    { Justification* proof = ((Justification*)(dynamicSlotValue(self->controlFrame->dynamicSlots, SYM_WHYNOT_LOGIC_JUSTIFICATION, NULL)));

      { MemoizationTable* memoTable000 = NULL;
        Cons* memoizedEntry000 = NULL;
        Object* memoizedValue000 = NULL;

        if (oMEMOIZATION_ENABLEDpo) {
          memoTable000 = ((MemoizationTable*)(SGT_WHYNOT_LOGIC_M_WHYNOT_PARTIAL_MATCHdNUMBER_OF_FAILED_SUBGOALS_MEMO_TABLE_000->surrogateValue));
          if (!((boolean)(memoTable000))) {
            initializeMemoizationTable(SGT_WHYNOT_LOGIC_M_WHYNOT_PARTIAL_MATCHdNUMBER_OF_FAILED_SUBGOALS_MEMO_TABLE_000, "(:MAX-VALUES 500)");
            memoTable000 = ((MemoizationTable*)(SGT_WHYNOT_LOGIC_M_WHYNOT_PARTIAL_MATCHdNUMBER_OF_FAILED_SUBGOALS_MEMO_TABLE_000->surrogateValue));
          }
          memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), proof, MEMOIZED_NULL_VALUE, NULL, NULL, -1);
          memoizedValue000 = memoizedEntry000->value;
        }
        if (((boolean)(memoizedValue000))) {
          if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
            memoizedValue000 = NULL;
          }
        }
        else {
          memoizedValue000 = wrapInteger(computeNumberOfFailedSubgoals(proof));
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
}

int computeNumberOfFailedSubgoals(Justification* proof) {
  { List* list = NULL;

    if (((boolean)(proof))) {
      list = newList();
      collectFailedGoals(proof, list);
      return (list->length());
    }
    return (0);
  }
}

boolean WhynotPartialMatch::cutoffPartialMatchP(boolean traceP) {
  { WhynotPartialMatch* self = this;

    { double score = self->matchScore;
      double scorecutoff = self->dynamicCutoff;
      int unknowngoalcutoff = self->unknownGoalCutoff;
      boolean cutoffP = false;

      if ((score == NULL_FLOAT) ||
          ((scorecutoff == NULL_FLOAT) ||
           (scorecutoff == 0.0))) {
        cutoffP = false;
      }
      else if (scorecutoff < 0.0) {
        cutoffP = score > scorecutoff;
      }
      else {
        cutoffP = score < scorecutoff;
      }
      if ((!cutoffP) &&
          (unknowngoalcutoff != NULL_INTEGER)) {
        cutoffP = self->numberOfFailedSubgoals() > unknowngoalcutoff;
        if (cutoffP &&
            traceP) {
          std::cout << "*** Cutting off search, more than " << unknowngoalcutoff << " failed subgoal(s)" << std::endl;
        }
      }
      return (cutoffP);
    }
  }
}

boolean auxiliaryEquivalencePropositionP(Proposition* proposition) {
  { boolean testValue000 = false;

    testValue000 = proposition->kind == KWD_WHYNOT_EQUIVALENT;
    if (testValue000) {
      { boolean foundP000 = false;

        { Object* arg = NULL;
          Vector* vector000 = proposition->arguments;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            arg = (vector000->theArray)[index000];
            if (variableP(arg) &&
                ((boolean)(((Object*)(accessInContext(((PatternVariable*)(arg))->variableValue, ((PatternVariable*)(arg))->homeContext, false)))))) {
              foundP000 = true;
              break;
            }
          }
        }
        testValue000 = foundP000;
      }
    }
    { boolean value000 = testValue000;

      return (value000);
    }
  }
}

double WhynotPartialMatch::propositionWeight(Proposition* proposition) {
  { WhynotPartialMatch* self = this;

    if (!((boolean)(proposition))) {
      return (1.0);
    }
    else if (proposition->kind == KWD_WHYNOT_ISA) {
      return (0.25);
    }
    else if ((proposition->kind == KWD_WHYNOT_NOT) &&
        (((Proposition*)((proposition->arguments->theArray)[0]))->kind == KWD_WHYNOT_EQUIVALENT)) {
      return (0.1);
    }
    else if (auxiliaryEquivalencePropositionP(proposition)) {
      return (0.0);
    }
    else if (((FloatWrapper*)(dynamicSlotValue(proposition->dynamicSlots, SYM_WHYNOT_LOGIC_WEIGHT, NULL_FLOAT_WRAPPER)))->wrapperValue != NULL_FLOAT) {
      return (((FloatWrapper*)(dynamicSlotValue(proposition->dynamicSlots, SYM_WHYNOT_LOGIC_WEIGHT, NULL_FLOAT_WRAPPER)))->wrapperValue);
    }
    else {
      return (1.0);
    }
  }
}

int oMIN_CLOCK_TICKS_PER_WHYNOT_ANTECEDENTo = 5;

Keyword* WhynotPartialMatch::continuePartialAndProof(ControlFrame* frame, Keyword* lastmove) {
  { WhynotPartialMatch* self = this;

    { Cons* forbiddenvars = NIL;

      if (lastmove == KWD_WHYNOT_DOWN) {
        self->setDynamicCutoff();
        if (frame->allottedClockTicks != NULL_INTEGER) {
          setDynamicSlotValue(frame->dynamicSlots, SYM_WHYNOT_LOGIC_REAL_ALLOTTED_CLOCK_TICKS, wrapInteger(frame->allottedClockTicks), NULL_INTEGER_WRAPPER);
        }
      }
      else if ((lastmove == KWD_WHYNOT_UP_TRUE) ||
          (lastmove == KWD_WHYNOT_UP_FAIL)) {
        { boolean successP = lastmove == KWD_WHYNOT_UP_TRUE;
          Proposition* andproposition = frame->proposition;
          ControlFrame* conjunctframe = frame->result;
          Proposition* conjunct = conjunctframe->proposition;
          double score = conjunctframe->partialMatchFrame->matchScore;
          double weight = self->propositionWeight(conjunct);

          lastmove = KWD_WHYNOT_UP_TRUE;
          self->pushAndPartialMatchScore(score, weight);
          if (conjunctframe->partialMatchFrame->cutoffPartialMatchP(traceKeywordP(KWD_WHYNOT_GOAL_TREE))) {
            lastmove = KWD_WHYNOT_UP_FAIL;
          }
          else if (((conjunctframe->truthValue == FALSE_TRUTH_VALUE) ||
              (conjunctframe->truthValue == DEFAULT_FALSE_TRUTH_VALUE)) &&
              ((conjunctframe->truthValue == TRUE_TRUTH_VALUE) ||
               (conjunctframe->truthValue == FALSE_TRUTH_VALUE))) {
            lastmove = KWD_WHYNOT_UP_FAIL;
          }
          else if (coerceWrappedBooleanToBoolean(conjunct->variableTypeP_reader()) &&
              (!successP)) {
            lastmove = KWD_WHYNOT_UP_FAIL;
          }
          else {
            if (frame->argumentCursor == (andproposition->arguments->length() - 1)) {
              score = self->computeAndScore();
              if (((!allArgumentsBoundP(andproposition)) &&
                  (!self->allowUnboundVariablesP())) ||
                  self->cutoffPartialMatchP(traceKeywordP(KWD_WHYNOT_GOAL_TREE))) {
                lastmove = KWD_WHYNOT_UP_FAIL;
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
      if (lastmove == KWD_WHYNOT_UP_FAIL) {
        frame->down = NULL;
      }
      { Keyword* result = continueAndProof(frame, lastmove);

        if (result == KWD_WHYNOT_MOVE_DOWN) {
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
            result = self->continuePartialAndProof(frame, KWD_WHYNOT_UP_FAIL);
          }
          if ((frame->allottedClockTicks != NULL_INTEGER) &&
              (result == KWD_WHYNOT_MOVE_DOWN)) {
            frame->allottedClockTicks = ((int)(((double)(((IntegerWrapper*)(dynamicSlotValue(frame->dynamicSlots, SYM_WHYNOT_LOGIC_REAL_ALLOTTED_CLOCK_TICKS, NULL_INTEGER_WRAPPER)))->wrapperValue - (oQUERYITERATORo->currentClockTicks - frame->startingClockTicks))) / ((Vector*)(dynamicSlotValue(frame->dynamicSlots, SYM_WHYNOT_STELLA_ARGUMENTS, NULL)))->length()));
          }
        }
        else if (result == KWD_WHYNOT_FAILURE) {
          self->setFramePartialTruth(frame->truthValue, NULL_FLOAT, false);
        }
        else {
        }
        return (result);
      }
    }
  }
}

int numberOfRemainingAntecedents(Iterator* iterator) {
  if (subtypeOfP(safePrimaryType(iterator), SGT_WHYNOT_STELLA_CONS_ITERATOR)) {
    { Iterator* iterator000 = iterator;
      ConsIterator* iterator = ((ConsIterator*)(iterator000));

      if (iterator->firstIterationP) {
        return (iterator->consIteratorCursor->length());
      }
      else {
        return (iterator->consIteratorCursor->length() - 1);
      }
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Don't know how to handle antecedents iterator of type " << "`" << iterator->primaryType() << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

double WhynotPartialMatch::chainingDepthDegradation() {
  { WhynotPartialMatch* self = this;

    { ControlFrame* frame = self->controlFrame;
      double degradationfactor = 0.75;
      double degradation = 1.0;

      frame = frame->up;
      while (((boolean)(frame))) {
        if (((boolean)(((Proposition*)(dynamicSlotValue(frame->dynamicSlots, SYM_WHYNOT_LOGIC_ANTECEDENTS_RULE, NULL)))))) {
          degradation = degradation * degradationfactor;
        }
        frame = frame->up;
      }
      return (degradation);
    }
  }
}

double WhynotDeepPartialMatch::chainingDepthDegradation() {
  { WhynotDeepPartialMatch* self = this;

    return (1.0);
  }
}

Keyword* WhynotPartialMatch::continuePartialAntecedentsProof(Keyword* lastmove) {
  { WhynotPartialMatch* self = this;

    { ControlFrame* frame = self->controlFrame;
      Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_WHYNOT_STELLA_ITERATOR, NULL)));
      Proposition* goal = extractSubgoalOfFrame(frame);
      double score = NULL_FLOAT;
      Keyword* result = NULL;
      int allottedclockticks = frame->allottedClockTicks;
      int currentclockticks = oQUERYITERATORo->currentClockTicks;

      if (lastmove == KWD_WHYNOT_DOWN) {
        self->setDynamicCutoff();
        if (!((boolean)(iterator))) {
          iterator = allocateAntecedentsIterator(extractSubgoalDescriptionOfFrame(frame), findExternalArgumentsForSubgoal(frame), frame->reversePolarityP);
          if (!((boolean)(iterator))) {
            iterator = NIL->allocateIterator();
          }
          setDynamicSlotValue(frame->dynamicSlots, SYM_WHYNOT_STELLA_ITERATOR, iterator, NULL);
        }
        if (allottedclockticks != NULL_INTEGER) {
          setDynamicSlotValue(frame->dynamicSlots, SYM_WHYNOT_LOGIC_REAL_ALLOTTED_CLOCK_TICKS, wrapInteger(allottedclockticks), NULL_INTEGER_WRAPPER);
        }
      }
      else if ((lastmove == KWD_WHYNOT_UP_TRUE) ||
          (lastmove == KWD_WHYNOT_UP_FAIL)) {
        score = frame->result->partialMatchFrame->matchScore;
        if ((frame->reversePolarityP &&
            (score > 0.0)) ||
            ((!frame->reversePolarityP) &&
             (score < 0.0))) {
          score = 0.0;
          lastmove = KWD_WHYNOT_UP_FAIL;
        }
        if ((((score < 0.0) ? (0.0 - score) : score)) < 1.0) {
          score = score * self->chainingDepthDegradation();
        }
        score = score * self->propositionWeight(((Proposition*)(dynamicSlotValue(frame->dynamicSlots, SYM_WHYNOT_LOGIC_ANTECEDENTS_RULE, NULL))));
        self->setFramePartialTruth(NULL, score, false);
        if ((lastmove == KWD_WHYNOT_UP_FAIL) ||
            (((!allArgumentsBoundP(goal)) &&
            (!self->allowUnboundVariablesP())) ||
             self->cutoffPartialMatchP(traceKeywordP(KWD_WHYNOT_GOAL_TREE)))) {
          self->setFramePartialTruth(UNKNOWN_TRUTH_VALUE, 0.0, true);
          lastmove = KWD_WHYNOT_UP_FAIL;
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      if ((lastmove == KWD_WHYNOT_UP_FAIL) &&
          ((boolean)(frame->down))) {
        frame->down = NULL;
      }
      if (!((lastmove == KWD_WHYNOT_UP_TRUE) ||
          (allottedclockticks == NULL_INTEGER))) {
        frame->allottedClockTicks = ((int)(((double)(((IntegerWrapper*)(dynamicSlotValue(frame->dynamicSlots, SYM_WHYNOT_LOGIC_REAL_ALLOTTED_CLOCK_TICKS, NULL_INTEGER_WRAPPER)))->wrapperValue - (currentclockticks - frame->startingClockTicks))) / stella::integerMax(numberOfRemainingAntecedents(iterator), 1)));
        if ((frame->allottedClockTicks < oMIN_CLOCK_TICKS_PER_WHYNOT_ANTECEDENTo) &&
            (numberOfRemainingAntecedents(iterator) > 0)) {
          if (((boolean)(oTRACED_KEYWORDSo)) &&
              oTRACED_KEYWORDSo->membP(KWD_WHYNOT_GOAL_TREE)) {
            std::cout << "*** Timeout - not enough time to subgoal" << std::endl;
          }
          setDynamicSlotValue(frame->dynamicSlots, SYM_WHYNOT_STELLA_ITERATOR, NIL->allocateIterator(), NULL);
        }
      }
      result = continueAntecedentsProof(frame, lastmove);
      if ((lastmove == KWD_WHYNOT_UP_TRUE) &&
          (!((boolean)(frame->truthValue)))) {
        frame->truthValue = UNKNOWN_TRUTH_VALUE;
      }
      return (result);
    }
  }
}

double WhynotPartialMatch::maxUnconstrainedFanout() {
  { WhynotPartialMatch* self = this;

    return (25.0);
  }
}

double WhynotDeepPartialMatch::maxUnconstrainedFanout() {
  { WhynotDeepPartialMatch* self = this;

    return (1000000.0);
  }
}

boolean WhynotPartialMatch::skipAndClauseP(ControlFrame* frame, Cons* forbiddenvars) {
  { WhynotPartialMatch* self = this;

    { boolean forbiddenvarsP = !(forbiddenvars == NIL);
      Proposition* conjunct = ((Proposition*)((frame->proposition->arguments->theArray)[(frame->argumentCursor)]));

      { boolean testValue000 = false;

        testValue000 = forbiddenvarsP;
        if (testValue000) {
          { boolean foundP000 = false;

            { Object* var = NULL;
              Cons* iter000 = getUnboundVariables(conjunct);

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
          testValue000 = dynamicallyEstimateGoalFanout(conjunct) > self->maxUnconstrainedFanout();
        }
        if (testValue000) {
          { ControlFrame* result = createDownFrame(frame, conjunct);

            setFrameTruthValue(result, UNKNOWN_TRUTH_VALUE);
            if (!((boolean)(result->partialMatchFrame))) {
              createAndLinkPartialMatchFrame(result, NULL);
            }
            result->partialMatchFrame->setFramePartialTruth(UNKNOWN_TRUTH_VALUE, 0.0, true);
            { PrimitiveStrategy* self000 = newPrimitiveStrategy();

              self000->inferenceRule = KWD_WHYNOT_SKIPPED_CONJUNCT;
              self000->strategy = KWD_WHYNOT_FAILURE;
              recordGoalJustification(result, self000);
            }
            result->state = KWD_WHYNOT_POPPED;
            (((Vector*)(dynamicSlotValue(frame->dynamicSlots, SYM_WHYNOT_STELLA_ARGUMENTS, NULL)))->theArray)[(frame->argumentCursor)] = result;
            frame->result = result;
            if (traceKeywordP(KWD_WHYNOT_GOAL_TREE)) {
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

void WhynotPartialMatch::initializePartialMatchStrategy(QueryIterator* query) {
  { WhynotPartialMatch* self = this;

    { FloatWrapper* minimumscore = ((FloatWrapper*)(query->options->lookup(KWD_WHYNOT_MINIMUM_SCORE)));
      IntegerWrapper* maxunknowns = ((IntegerWrapper*)(query->options->lookup(KWD_WHYNOT_MAXIMUM_UNKNOWNS)));
      double epsilon = 0.001;

      query->partialMatchStrategy = self;
      self->dynamicCutoff = (((boolean)(minimumscore)) ? minimumscore->wrapperValue : epsilon);
      setDynamicSlotValue(query->dynamicSlots, SYM_WHYNOT_LOGIC_LATEST_POSITIVE_SCORE, wrapFloat(0.0), NULL_FLOAT_WRAPPER);
      if (((boolean)(maxunknowns))) {
        self->unknownGoalCutoff = maxunknowns->wrapperValue;
      }
    }
  }
}

List* ControlFrame::allJustifications_reader() {
  { ControlFrame* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_WHYNOT_LOGIC_ALL_JUSTIFICATIONS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

double WhynotPartialMatch::computePartialTruth(QueryIterator* query) {
  { WhynotPartialMatch* self = this;

    { ControlFrame* baseframe = query->baseControlFrame;
      PartialMatchFrame* partialmatchframe = query->partialMatchStrategy;
      FloatWrapper* minimumscore = ((FloatWrapper*)(query->options->lookup(KWD_WHYNOT_MINIMUM_SCORE)));
      boolean maximizescoreP = !eqlP(query->options->lookup(KWD_WHYNOT_MAXIMIZE_SCOREp), FALSE_WRAPPER);
      int topnproofs = 10;
      List* proofclasses = newList();
      NormalInferenceLevel* initialinferencelevel = currentInferenceLevel();

      if (!((boolean)(partialmatchframe))) {
        partialmatchframe = self;
        query->partialMatchStrategy = self;
      }
      partialmatchframe->dynamicCutoff = (((boolean)(minimumscore)) ? minimumscore->wrapperValue : 0.3);
      { 
        BIND_STELLA_SPECIAL(oQUERYITERATORo, QueryIterator*, query);
        BIND_STELLA_SPECIAL(oGENERATE_ALL_PROOFSpo, boolean, true);
        BIND_STELLA_SPECIAL(oRECORD_JUSTIFICATIONSpo, boolean, true);
        BIND_STELLA_SPECIAL(oINFERENCELEVELo, NormalInferenceLevel*, initialinferencelevel);
        BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
        for (;;) {
          if (!(query->nextP())) {
            break;
          }
          oINFERENCELEVELo = initialinferencelevel;
          if (partialmatchframe->cutoffPartialMatchP(false)) {
            break;
          }
          if (insertWhynotProof(proofclasses, ((Justification*)(dynamicSlotValue(baseframe->dynamicSlots, SYM_WHYNOT_LOGIC_JUSTIFICATION, NULL))))->length() == oSIMILAR_WHYNOT_PROOF_CUTOFFo) {
            cutoffSimilarWhynotProofs(query);
          }
          if (proofclasses->length() >= topnproofs) {
            proofclasses->sort(((cpp_function_code)(&betterWhynotProofClassP)));
            partialmatchframe->dynamicCutoff = ((WhynotProofClass*)(proofclasses->nth(topnproofs - 1)))->representative->matchScore + 0.01;
          }
          if ((!maximizescoreP) ||
              knownTruthValueP(baseframe->truthValue)) {
            break;
          }
        }
      }
      postProcessWhynotProofClasses(proofclasses);
      setDynamicSlotValue(baseframe->dynamicSlots, SYM_WHYNOT_LOGIC_ALL_JUSTIFICATIONS, newList(), NULL);
      { WhynotProofClass* clasS = NULL;
        Cons* iter000 = proofclasses->theConsList;
        List* into000 = baseframe->allJustifications_reader();
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          clasS = ((WhynotProofClass*)(iter000->value));
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(clasS->representative, NIL);
              if (into000->theConsList == NIL) {
                into000->theConsList = collect000;
              }
              else {
                addConsToEndOfConsList(into000->theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(clasS->representative, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      setDynamicSlotValue(baseframe->dynamicSlots, SYM_WHYNOT_LOGIC_JUSTIFICATION, ((Justification*)(baseframe->allJustifications_reader()->first())), NULL);
      return ((((boolean)(((Justification*)(dynamicSlotValue(baseframe->dynamicSlots, SYM_WHYNOT_LOGIC_JUSTIFICATION, NULL))))) ? ((Justification*)(dynamicSlotValue(baseframe->dynamicSlots, SYM_WHYNOT_LOGIC_JUSTIFICATION, NULL)))->matchScore : 0.0));
    }
  }
}

boolean betterWhynotProofP(Justification* proof1, Justification* proof2) {
  return (proof1->matchScore > proof2->matchScore);
}

int computeProofDeviation(Justification* proof1, Justification* proof2, int maxdeviations, KeyValueList* deviations) {
  if (!((boolean)(deviations))) {
    deviations = newKeyValueList();
  }
  { int founddeviations = 0;
    int subdeviations = 0;

    if ((proof1->inferenceRule == proof2->inferenceRule) &&
        ((proof1->inferenceStrategy() == proof2->inferenceStrategy()) &&
         ((proof1->truthValue == proof2->truthValue) &&
          ((proof1->reversePolarityP == proof2->reversePolarityP) &&
           ((proof1->matchScore == proof2->matchScore) &&
            equivalentPropositionsP(proof1->proposition, proof2->proposition, NULL)))))) {
      if (proof1->inferenceRule == KWD_WHYNOT_PATTERN) {
        { PatternVariable* var1 = NULL;
          Object* value1 = NULL;
          DictionaryIterator* iter000 = ((DictionaryIterator*)(proof1->substitution->allocateIterator()));
          PatternVariable* var2 = NULL;
          Object* value2 = NULL;
          DictionaryIterator* iter001 = ((DictionaryIterator*)(proof2->substitution->allocateIterator()));

          for  (; iter000->nextP() &&
                    iter001->nextP(); ) {
            var1 = ((PatternVariable*)(iter000->key));
            value1 = iter000->value;
            var2 = ((PatternVariable*)(iter001->key));
            value2 = iter001->value;
            if (!(var1 == var2)) {
              deviations->clear();
              return (NULL_INTEGER);
            }
            if (!(eqlP(value1, value2))) {
              founddeviations = founddeviations + 1;
            }
            if (founddeviations > maxdeviations) {
              deviations->clear();
              return (NULL_INTEGER);
            }
          }
        }
        if (founddeviations > 0) {
          deviations->insertAt(proof1, proof2);
        }
      }
      { Justification* ant1 = NULL;
        Cons* iter002 = proof1->antecedents;
        Justification* ant2 = NULL;
        Cons* iter003 = proof2->antecedents;

        for  (; (!(iter002 == NIL)) &&
                  (!(iter003 == NIL)); 
              iter002 = iter002->rest,
              iter003 = iter003->rest) {
          ant1 = ((Justification*)(iter002->value));
          ant2 = ((Justification*)(iter003->value));
          subdeviations = computeProofDeviation(ant1, ant2, maxdeviations - founddeviations, deviations);
          if (subdeviations == NULL_INTEGER) {
            deviations->clear();
            return (NULL_INTEGER);
          }
          founddeviations = founddeviations + subdeviations;
        }
      }
      return (founddeviations);
    }
    return (NULL_INTEGER);
  }
}

WhynotProofClass* newWhynotProofClass() {
  { WhynotProofClass* self = NULL;

    self = new WhynotProofClass();
    self->theConsList = NIL;
    self->deviatingInstances = newList();
    self->deviatingVariable = NULL;
    self->deviatingPattern = NULL;
    self->representative = NULL;
    return (self);
  }
}

Surrogate* WhynotProofClass::primaryType() {
  { WhynotProofClass* self = this;

    return (SGT_WHYNOT_LOGIC_WHYNOT_PROOF_CLASS);
  }
}

Object* accessWhynotProofClassSlotValue(WhynotProofClass* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_WHYNOT_LOGIC_REPRESENTATIVE) {
    if (setvalueP) {
      self->representative = ((Justification*)(value));
    }
    else {
      value = self->representative;
    }
  }
  else if (slotname == SYM_WHYNOT_LOGIC_DEVIATING_PATTERN) {
    if (setvalueP) {
      self->deviatingPattern = ((Justification*)(value));
    }
    else {
      value = self->deviatingPattern;
    }
  }
  else if (slotname == SYM_WHYNOT_LOGIC_DEVIATING_VARIABLE) {
    if (setvalueP) {
      self->deviatingVariable = ((PatternVariable*)(value));
    }
    else {
      value = self->deviatingVariable;
    }
  }
  else if (slotname == SYM_WHYNOT_LOGIC_DEVIATING_INSTANCES) {
    if (setvalueP) {
      self->deviatingInstances = ((List*)(value));
    }
    else {
      value = self->deviatingInstances;
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

DEFINE_STELLA_SPECIAL(oMAX_WHYNOT_PROOF_CLASS_DEVIATIONSo, int , 1);

boolean insertWhynotProofToClassP(WhynotProofClass* clasS, Justification* proof) {
  if (clasS->emptyP()) {
    clasS->theConsList = cons(proof, clasS->theConsList);
    clasS->representative = proof;
    return (true);
  }
  { KeyValueList* deviations = newKeyValueList();
    int founddeviations = computeProofDeviation(proof, clasS->representative, oMAX_WHYNOT_PROOF_CLASS_DEVIATIONSo, deviations);

    if (founddeviations != NULL_INTEGER) {
      { Justification* newdev = NULL;
        Justification* repdev = NULL;
        KvCons* iter000 = deviations->theKvList;

        for  (; ((boolean)(iter000)); 
              iter000 = iter000->rest) {
          newdev = ((Justification*)(iter000->key));
          repdev = ((Justification*)(iter000->value));
          if (founddeviations == 0) {
            return (true);
          }
          if (!((boolean)(clasS->deviatingPattern))) {
            clasS->deviatingPattern = repdev;
          }
          { PatternVariable* newvar = NULL;
            Object* newvalue = NULL;
            DictionaryIterator* iter001 = ((DictionaryIterator*)(newdev->substitution->allocateIterator()));
            PatternVariable* repvar = NULL;
            Object* repvalue = NULL;
            DictionaryIterator* iter002 = ((DictionaryIterator*)(clasS->deviatingPattern->substitution->allocateIterator()));

            for  (; iter001->nextP() &&
                      iter002->nextP(); ) {
              newvar = ((PatternVariable*)(iter001->key));
              newvalue = iter001->value;
              repvar = ((PatternVariable*)(iter002->key));
              repvalue = iter002->value;
              if (!eqlP(newvalue, repvalue)) {
                repvar = repvar;
                if (!((boolean)(clasS->deviatingVariable))) {
                  clasS->deviatingVariable = newvar;
                  clasS->deviatingInstances->insert(repvalue);
                }
                else if (!(newvar == clasS->deviatingVariable)) {
                  return (false);
                }
                else if (clasS->deviatingInstances->memberP(newvalue)) {
                  return (true);
                }
                clasS->deviatingInstances->insert(newvalue);
              }
            }
          }
          clasS->theConsList = cons(proof, clasS->theConsList);
          return (true);
        }
      }
    }
    return (false);
  }
}

WhynotProofClass* insertWhynotProof(List* classes, Justification* proof) {
  { WhynotProofClass* clasS = NULL;
    Cons* iter000 = classes->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      clasS = ((WhynotProofClass*)(iter000->value));
      if (insertWhynotProofToClassP(clasS, proof)) {
        return (clasS);
      }
    }
  }
  classes->push(newWhynotProofClass());
  insertWhynotProofToClassP(((WhynotProofClass*)(classes->first())), proof);
  return (((WhynotProofClass*)(classes->first())));
}

boolean betterWhynotProofClassP(WhynotProofClass* class1, WhynotProofClass* class2) {
  return (betterWhynotProofP(class1->representative, class2->representative));
}

AlternativeBindingsSet* newAlternativeBindingsSet() {
  { AlternativeBindingsSet* self = NULL;

    self = new AlternativeBindingsSet();
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = SGT_WHYNOT_LOGIC_ALTERNATIVE_BINDINGS_SET;
    self->bindings = newSet();
    self->theVariable = NULL;
    return (self);
  }
}

Surrogate* AlternativeBindingsSet::primaryType() {
  { AlternativeBindingsSet* self = this;

    return (SGT_WHYNOT_LOGIC_ALTERNATIVE_BINDINGS_SET);
  }
}

Object* accessAlternativeBindingsSetSlotValue(AlternativeBindingsSet* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_WHYNOT_LOGIC_THE_VARIABLE) {
    if (setvalueP) {
      self->theVariable = ((PatternVariable*)(value));
    }
    else {
      value = self->theVariable;
    }
  }
  else if (slotname == SYM_WHYNOT_LOGIC_BINDINGS) {
    if (setvalueP) {
      self->bindings = ((Set*)(value));
    }
    else {
      value = self->bindings;
    }
  }
  else {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

void AlternativeBindingsSet::printObject(std::ostream* stream) {
  { AlternativeBindingsSet* self = this;

    *(stream) << stringDowncase(getSkolemPrintName(self->theVariable));
  }
}

boolean alternativeBindingsSetP(Object* thing) {
  return (((boolean)(thing)) &&
      isaP(thing, SGT_WHYNOT_LOGIC_ALTERNATIVE_BINDINGS_SET));
}

Set* alternativeBindings(AlternativeBindingsSet* bindingsset) {
  return (bindingsset->bindings);
}

void postProcessWhynotProofClasses(List* classes) {
  classes->sort(((cpp_function_code)(&betterWhynotProofClassP)));
  { WhynotProofClass* clasS = NULL;
    Cons* iter000 = classes->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      clasS = ((WhynotProofClass*)(iter000->value));
      if (clasS->length() > 1) {
        { KeyValueMap* substitution = clasS->deviatingPattern->substitution;
          PatternVariable* variable = clasS->deviatingVariable;

          { AlternativeBindingsSet* self000 = newAlternativeBindingsSet();

            self000->theVariable = variable;
            { AlternativeBindingsSet* bindings = self000;

              { Object* instance = NULL;
                Cons* iter001 = clasS->deviatingInstances->theConsList;

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  instance = iter001->value;
                  bindings->bindings->insert(instance);
                }
              }
              substitution->insertAt(variable, bindings);
            }
          }
        }
      }
    }
  }
}

int oSIMILAR_WHYNOT_PROOF_CUTOFFo = 3;

void cutoffSimilarWhynotProofs(QueryIterator* query) {
  { ControlFrame* continuationframe = query->baseControlFrame;

    while (((boolean)(continuationframe->down))) {
      continuationframe = continuationframe->down;
    }
    if (((boolean)(((Iterator*)(dynamicSlotValue(continuationframe->dynamicSlots, SYM_WHYNOT_STELLA_ITERATOR, NULL)))))) {
      setDynamicSlotValue(continuationframe->dynamicSlots, SYM_WHYNOT_STELLA_ITERATOR, NIL->allocateIterator(), NULL);
      if (traceKeywordP(KWD_WHYNOT_GOAL_TREE)) {
        { 
          BIND_STELLA_SPECIAL(oPRINTINFRAMEo, ControlFrame*, continuationframe);
          BIND_STELLA_SPECIAL(oPRINTMODEo, Keyword*, KWD_WHYNOT_REALISTIC);
          BIND_STELLA_SPECIAL(oPRINTLOGICALFORMSTREAMo, OutputStream*, STANDARD_OUTPUT);
          BIND_STELLA_SPECIAL(oQUERYITERATORo, QueryIterator*, query);
          std::cout << "*** cutting off similar WhyNot proofs at goal=";
          printUnformattedLogicalForm(continuationframe->proposition, STANDARD_OUTPUT);
          std::cout << std::endl;
        }
      }
    }
  }
}

QueryIterator* WhynotPartialMatch::retrievePartialSolutions(QueryIterator* query) {
  { WhynotPartialMatch* self = this;

    { ControlFrame* baseframe = query->baseControlFrame;
      PartialMatchFrame* partialmatchframe = query->partialMatchStrategy;
      FloatWrapper* minimumscore = ((FloatWrapper*)(lookupQueryOption(query, KWD_WHYNOT_MINIMUM_SCORE)));
      boolean maximizescoreP = !eqlP(lookupQueryOption(query, KWD_WHYNOT_MAXIMIZE_SCOREp), FALSE_WRAPPER);
      int howmany = lookupHowManySolutions(query);
      int topn = 10;
      int topnpartialproofs = topn;
      boolean haveenoughpartialproofsP = false;
      Cons* currentsolution = NIL;
      Justification* currentproof = NULL;
      List* strictproofs = newList();
      List* partialproofclasses = newList();
      NormalInferenceLevel* initialinferencelevel = currentInferenceLevel();

      if (!((boolean)(partialmatchframe))) {
        partialmatchframe = self;
        query->partialMatchStrategy = self;
      }
      partialmatchframe->dynamicCutoff = (((boolean)(minimumscore)) ? minimumscore->wrapperValue : 0.3);
      { 
        BIND_STELLA_SPECIAL(oQUERYITERATORo, QueryIterator*, query);
        BIND_STELLA_SPECIAL(oGENERATE_ALL_PROOFSpo, boolean, true);
        BIND_STELLA_SPECIAL(oRECORD_JUSTIFICATIONSpo, boolean, true);
        BIND_STELLA_SPECIAL(oINFERENCELEVELo, NormalInferenceLevel*, initialinferencelevel);
        BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
        for (;;) {
          query->solutions->clear();
          if ((strictproofs->length() == howmany) ||
              (!query->nextP())) {
            break;
          }
          oINFERENCELEVELo = initialinferencelevel;
          if (partialmatchframe->cutoffPartialMatchP(false)) {
            break;
          }
          currentsolution = ((QuerySolution*)(query->value))->consify();
          currentproof = ((Justification*)(dynamicSlotValue(baseframe->dynamicSlots, SYM_WHYNOT_LOGIC_JUSTIFICATION, NULL)));
          { boolean testValue000 = false;

            { boolean foundP000 = false;

              { Justification* proof = NULL;
                Cons* iter000 = strictproofs->theConsList;

                for (; !(iter000 == NIL); iter000 = iter000->rest) {
                  proof = ((Justification*)(iter000->value));
                  if (equalP(retrievalProofSolution(proof, query), currentsolution)) {
                    foundP000 = true;
                    break;
                  }
                }
              }
              testValue000 = foundP000;
            }
            testValue000 = !testValue000;
            if (testValue000) {
              {
                if (knownTruthValueP(baseframe->truthValue)) {
                  strictproofs->push(currentproof);
                  continue;
                }
              }
            }
            else {
              {
                continue;
              }
            }
          }
          if (insertWhynotProof(partialproofclasses, currentproof)->length() == oSIMILAR_WHYNOT_PROOF_CUTOFFo) {
            cutoffSimilarWhynotProofs(query);
          }
          topnpartialproofs = ((howmany == NULL_INTEGER) ? topn : stella::integerMax(topn, howmany - strictproofs->length()));
          if (haveenoughpartialproofsP ||
              (partialproofclasses->length() >= topnpartialproofs)) {
            haveenoughpartialproofsP = true;
            partialproofclasses->sort(((cpp_function_code)(&betterWhynotProofClassP)));
            partialmatchframe->dynamicCutoff = ((WhynotProofClass*)(partialproofclasses->nth(topnpartialproofs - 1)))->representative->matchScore + 0.01;
          }
          if (!maximizescoreP) {
            break;
          }
        }
      }
      setDynamicSlotValue(baseframe->dynamicSlots, SYM_WHYNOT_LOGIC_ALL_JUSTIFICATIONS, strictproofs->reverse(), NULL);
      if (!(strictproofs->length() == howmany)) {
        postProcessWhynotProofClasses(partialproofclasses);
        { WhynotProofClass* clasS = NULL;
          Cons* iter001 = partialproofclasses->theConsList;
          int i = NULL_INTEGER;
          int iter002 = 1;
          int upperBound000 = topnpartialproofs;
          boolean unboundedP000 = upperBound000 == NULL_INTEGER;
          List* into000 = baseframe->allJustifications_reader();
          Cons* collect000 = NULL;

          for  (; (!(iter001 == NIL)) &&
                    (unboundedP000 ||
                     (iter002 <= upperBound000)); 
                iter001 = iter001->rest,
                iter002 = iter002 + 1) {
            clasS = ((WhynotProofClass*)(iter001->value));
            i = iter002;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(clasS->representative, NIL);
                if (into000->theConsList == NIL) {
                  into000->theConsList = collect000;
                }
                else {
                  addConsToEndOfConsList(into000->theConsList, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(clasS->representative, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
      }
      setDynamicSlotValue(baseframe->dynamicSlots, SYM_WHYNOT_LOGIC_JUSTIFICATION, ((Justification*)(baseframe->allJustifications_reader()->first())), NULL);
      query->solutions->clear();
      { Justification* proof = NULL;
        Cons* iter003 = baseframe->allJustifications_reader()->theConsList;

        for (; !(iter003 == NIL); iter003 = iter003->rest) {
          proof = ((Justification*)(iter003->value));
          { QuerySolution* self002 = newQuerySolution();

            self002->bindings = coerceToVector(retrievalProofSolution(proof, query));
            self002->matchScore = proof->matchScore;
            self002->justification = proof;
            { QuerySolution* solution = self002;

              query->solutions->insertAt(solution->bindings, solution);
            }
          }
        }
      }
      return (query);
    }
  }
}

Cons* retrievalProofSolution(Justification* proof, QueryIterator* query) {
  { Cons* solution = NIL;
    KeyValueMap* substitution = proof->substitution;

    { PatternVariable* extvar = NULL;
      Vector* vector000 = query->externalVariables;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        extvar = ((PatternVariable*)((vector000->theArray)[index000]));
        { PatternVariable* var = NULL;
          Object* value = NULL;
          DictionaryIterator* iter000 = ((DictionaryIterator*)(substitution->allocateIterator()));

          for  (; iter000->nextP(); ) {
            var = ((PatternVariable*)(iter000->key));
            value = iter000->value;
            if (var->skolemName == extvar->skolemName) {
              solution = cons(value, solution);
              break;
            }
          }
        }
      }
    }
    return (solution->reverse());
  }
}

void collectFailedGoals(Justification* proof, List* failures) {
  if (proof->inferenceRule == KWD_WHYNOT_AND_INTRODUCTION) {
    { List* variables = newList();

      { Justification* antecedent = NULL;
        Cons* iter000 = proof->antecedents;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          antecedent = ((Justification*)(iter000->value));
          if (failedGoalJustificationP(antecedent)) {
            { Object* arg = NULL;
              Vector* vector000 = antecedent->proposition->arguments;
              int index000 = 0;
              int length000 = vector000->length();

              for  (; index000 < length000; 
                    index000 = index000 + 1) {
                arg = (vector000->theArray)[index000];
                if (alternativeBindingsSetP(justificationArgumentBoundTo(arg, antecedent))) {
                  variables->insertNew(((PatternVariable*)(arg)));
                }
              }
            }
          }
        }
      }
      if (variables->nonEmptyP()) {
        { Justification* antecedent = NULL;
          Cons* iter001 = proof->antecedents;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            antecedent = ((Justification*)(iter001->value));
            { boolean testValue000 = false;

              if (failedGoalJustificationP(antecedent)) {
                testValue000 = true;
              }
              else {
                { boolean foundP000 = false;

                  { Object* arg = NULL;
                    Vector* vector001 = antecedent->proposition->arguments;
                    int index001 = 0;
                    int length001 = vector001->length();

                    for  (; index001 < length001; 
                          index001 = index001 + 1) {
                      arg = (vector001->theArray)[index001];
                      if (variables->memberP(arg)) {
                        foundP000 = true;
                        break;
                      }
                    }
                  }
                  testValue000 = foundP000;
                }
              }
              if (testValue000) {
                failures->insert(antecedent);
              }
              else {
                collectFailedGoals(antecedent, failures);
              }
            }
          }
        }
        return;
      }
    }
  }
  if (failedGoalJustificationP(proof)) {
    failures->insertNew(proof);
  }
  else {
    { Justification* antecedent = NULL;
      Cons* iter002 = proof->antecedents;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        antecedent = ((Justification*)(iter002->value));
        collectFailedGoals(antecedent, failures);
      }
    }
  }
}

QueryIterator* deriveJustifiedPartialQuery(QueryIterator* query) {
  if (((boolean)(query->partialMatchStrategy)) &&
      ((boolean)(((Justification*)(dynamicSlotValue(query->baseControlFrame->dynamicSlots, SYM_WHYNOT_LOGIC_JUSTIFICATION, NULL)))))) {
    return (query);
  }
  { QueryIterator* partialquery = createQueryIterator(query->baseControlFrame->patternRecord->description, ((QuerySolution*)(query->value))->bindings);
    boolean recordjustificationsP = oRECORD_JUSTIFICATIONSpo;

    partialquery->options->insertAt(KWD_WHYNOT_MATCH_MODE, KWD_WHYNOT_WHYNOT);
    setPowerloomFeature(KWD_WHYNOT_JUSTIFICATIONS);
    callAskPartial(partialquery);
    if (!(recordjustificationsP)) {
      unsetPowerloomFeature(KWD_WHYNOT_JUSTIFICATIONS);
    }
    return (partialquery);
  }
}

void whynot(Cons* args) {
  { const char* label = NULL;
    Keyword* style = NULL;
    int maxdepth = NULL_INTEGER;
    boolean summaryP = false;

    label = parseWhyArguments(args, style, maxdepth, summaryP);
    explainWhynot(label, style, maxdepth, summaryP, STANDARD_OUTPUT);
  }
}

void whynotEvaluatorWrapper(Cons* arguments) {
  whynot(arguments);
}

void explainWhynot(const char* label, Keyword* style, int maxdepth, boolean summaryP, OutputStream* stream) {
  // Programmer's interface to the WHYNOT function.
  if (label == NULL) {
    oMOST_RECENT_EXPLANATION_MAPPINGo = newKeyValueList();
  }
  try {
    { Cons* mappings = NIL;

      { Justification* justification = NULL;
        Cons* iter000 = getWhynotJustifications(oMOST_RECENT_QUERYo, label, oMOST_RECENT_EXPLANATION_MAPPINGo)->theConsList;
        int i = NULL_INTEGER;
        int iter001 = 1;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          justification = ((Justification*)(iter000->value));
          i = iter001;
          if (label == NULL) {
            { ExplanationInfo* info = registerJustification(visibleJustification(justification), oMOST_RECENT_EXPLANATION_MAPPINGo);

              info->label = integerToString(((long long int)(i)));
              info->depth = 1;
            }
          }
          *(stream->nativeStream) << std::endl << "Explanation #" << i << " score=" << justification->matchScore << ":" << std::endl << std::endl;
          printWhynotJustification(justification, stream, maxdepth, style, summaryP);
          if (label == NULL) {
            mappings = cons(oMOST_RECENT_EXPLANATION_MAPPINGo, mappings);
            oMOST_RECENT_EXPLANATION_MAPPINGo = newKeyValueList();
          }
        }
      }
      if (!(mappings == NIL)) {
        oMOST_RECENT_EXPLANATION_MAPPINGo = newKeyValueList();
        { KeyValueList* mapping = NULL;
          Cons* iter002 = mappings;

          for (; !(iter002 == NIL); iter002 = iter002->rest) {
            mapping = ((KeyValueList*)(iter002->value));
            { Justification* k = NULL;
              ExplanationInfo* v = NULL;
              KvCons* iter003 = mapping->theKvList;

              for  (; ((boolean)(iter003)); 
                    iter003 = iter003->rest) {
                k = ((Justification*)(iter003->key));
                v = ((ExplanationInfo*)(iter003->value));
                oMOST_RECENT_EXPLANATION_MAPPINGo->insertAt(k, v);
              }
            }
          }
        }
      }
    }
  }
  catch (ExplainException& _ee) {
    ExplainException* ee = &_ee;

    std::cout << exceptionMessage(ee);
  }
}

void printWhynotJustification(Justification* justification, OutputStream* stream, int maxdepth, Keyword* style, boolean summaryP) {
  // Print a WHYNOT `justification' to `stream' according to
  // `maxDepth' and `style'.  Print a summary only if `summary?' is TRUE.
  { 
    BIND_STELLA_SPECIAL(oEXPLANATION_STYLEo, Keyword*, (((boolean)(style)) ? style : KWD_WHYNOT_BRIEF));
    if (!((boolean)(justification))) {
      if (((boolean)(oMOST_RECENT_QUERYo))) {
        prettyPrintLogicalForm(oMOST_RECENT_QUERYo->currentPatternRecord->description->proposition, stream);
        *(stream->nativeStream) << std::endl << "  " << lookupExplanationPhrase(KWD_WHYNOT_NOT_ASSERTED, NIL, NULL) << " and " << std::endl << "  " << lookupExplanationPhrase(KWD_WHYNOT_NO_RULES, NIL, NULL) << "." << std::endl;
      }
    }
    else if (summaryP) {
      { List* failures = newList();

        collectFailedGoals(justification, failures);
        *(stream->nativeStream) << "The query failed, because" << std::endl;
        { Justification* failure = NULL;
          Cons* iter000 = failures->theConsList;
          int i = NULL_INTEGER;
          int iter001 = 1;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest,
                iter001 = iter001 + 1) {
            failure = ((Justification*)(iter000->value));
            i = iter001;
            if (i == 1) {
              *(stream->nativeStream) << "    ";
            }
            else {
              *(stream->nativeStream) << "and ";
            }
            printJustificationProposition(failure, stream, 4);
            *(stream->nativeStream) << std::endl;
          }
        }
        *(stream->nativeStream) << "failed." << std::endl << std::endl;
      }
    }
    else {
      printExplanation(justification, stream, oMOST_RECENT_EXPLANATION_MAPPINGo, maxdepth, oEXPLANATION_AUDIENCEo);
    }
  }
}

List* getWhynotJustifications(QueryIterator* query, const char* label, KeyValueList* mapping) {
  // Programmer's interface to WHYNOT function.  Derive
  // justifications why `query' failed, or, if `label' was supplied as non-NULL,
  // lookup its justification relative to `mapping' and return the result.
  { List* justifications = NULL;

    if (!((boolean)(query))) {
      query = oMOST_RECENT_QUERYo;
    }
    if (!((boolean)(mapping))) {
      mapping = oMOST_RECENT_EXPLANATION_MAPPINGo;
    }
    if (!((boolean)(query))) {
      throw *newExplainNoQueryException("There is nothing to explain.");
    }
    if ((!((boolean)(query->partialMatchStrategy))) &&
        (!query->exhaustedP)) {
      throw *newExplainQueryTrueException("The query did not fail.");
    }
    query = deriveJustifiedPartialQuery(query);
    justifications = query->baseControlFrame->allJustifications_reader();
    if (label != NULL) {
      if (((boolean)(mapping))) {
        justifications = list(1, lookupJustification(mapping, label));
      }
      if (!((boolean)(justifications->first()))) {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Label " << "`" << label << "'" << " does not exists in the current explanation";
          throw *newExplainNoSuchLabelException(stream000->theStringReader());
        }
      }
    }
    return (justifications);
  }
}

void helpStartupWhynot1() {
  {
    SGT_WHYNOT_LOGIC_WHYNOT_PARTIAL_MATCH = ((Surrogate*)(internRigidSymbolWrtModule("WHYNOT-PARTIAL-MATCH", NULL, 1)));
    SYM_WHYNOT_LOGIC_UNKNOWN_GOAL_CUTOFF = ((Symbol*)(internRigidSymbolWrtModule("UNKNOWN-GOAL-CUTOFF", NULL, 0)));
    SGT_WHYNOT_LOGIC_WHYNOT_DEEP_PARTIAL_MATCH = ((Surrogate*)(internRigidSymbolWrtModule("WHYNOT-DEEP-PARTIAL-MATCH", NULL, 1)));
    KWD_WHYNOT_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    SYM_WHYNOT_STELLA_ARGUMENTS = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENTS", getStellaModule("/STELLA", true), 0)));
    SYM_WHYNOT_LOGIC_JUSTIFICATION = ((Symbol*)(internRigidSymbolWrtModule("JUSTIFICATION", NULL, 0)));
    SGT_WHYNOT_LOGIC_M_WHYNOT_PARTIAL_MATCHdNUMBER_OF_FAILED_SUBGOALS_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("M-WHYNOT-PARTIAL-MATCH.NUMBER-OF-FAILED-SUBGOALS-MEMO-TABLE-000", NULL, 1)));
    KWD_WHYNOT_EQUIVALENT = ((Keyword*)(internRigidSymbolWrtModule("EQUIVALENT", NULL, 2)));
    KWD_WHYNOT_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    KWD_WHYNOT_NOT = ((Keyword*)(internRigidSymbolWrtModule("NOT", NULL, 2)));
    SYM_WHYNOT_LOGIC_WEIGHT = ((Symbol*)(internRigidSymbolWrtModule("WEIGHT", NULL, 0)));
    KWD_WHYNOT_DOWN = ((Keyword*)(internRigidSymbolWrtModule("DOWN", NULL, 2)));
    SYM_WHYNOT_LOGIC_REAL_ALLOTTED_CLOCK_TICKS = ((Symbol*)(internRigidSymbolWrtModule("REAL-ALLOTTED-CLOCK-TICKS", NULL, 0)));
    KWD_WHYNOT_UP_TRUE = ((Keyword*)(internRigidSymbolWrtModule("UP-TRUE", NULL, 2)));
    KWD_WHYNOT_UP_FAIL = ((Keyword*)(internRigidSymbolWrtModule("UP-FAIL", NULL, 2)));
    KWD_WHYNOT_GOAL_TREE = ((Keyword*)(internRigidSymbolWrtModule("GOAL-TREE", NULL, 2)));
    KWD_WHYNOT_MOVE_DOWN = ((Keyword*)(internRigidSymbolWrtModule("MOVE-DOWN", NULL, 2)));
    KWD_WHYNOT_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("FAILURE", NULL, 2)));
    SGT_WHYNOT_STELLA_CONS_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("CONS-ITERATOR", getStellaModule("/STELLA", true), 1)));
    SYM_WHYNOT_LOGIC_ANTECEDENTS_RULE = ((Symbol*)(internRigidSymbolWrtModule("ANTECEDENTS-RULE", NULL, 0)));
    SYM_WHYNOT_STELLA_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR", getStellaModule("/STELLA", true), 0)));
    KWD_WHYNOT_SKIPPED_CONJUNCT = ((Keyword*)(internRigidSymbolWrtModule("SKIPPED-CONJUNCT", NULL, 2)));
    KWD_WHYNOT_POPPED = ((Keyword*)(internRigidSymbolWrtModule("POPPED", NULL, 2)));
    KWD_WHYNOT_MINIMUM_SCORE = ((Keyword*)(internRigidSymbolWrtModule("MINIMUM-SCORE", NULL, 2)));
    KWD_WHYNOT_MAXIMUM_UNKNOWNS = ((Keyword*)(internRigidSymbolWrtModule("MAXIMUM-UNKNOWNS", NULL, 2)));
    SYM_WHYNOT_LOGIC_LATEST_POSITIVE_SCORE = ((Symbol*)(internRigidSymbolWrtModule("LATEST-POSITIVE-SCORE", NULL, 0)));
    SYM_WHYNOT_LOGIC_ALL_JUSTIFICATIONS = ((Symbol*)(internRigidSymbolWrtModule("ALL-JUSTIFICATIONS", NULL, 0)));
    KWD_WHYNOT_MAXIMIZE_SCOREp = ((Keyword*)(internRigidSymbolWrtModule("MAXIMIZE-SCORE?", NULL, 2)));
    KWD_WHYNOT_PATTERN = ((Keyword*)(internRigidSymbolWrtModule("PATTERN", NULL, 2)));
    SGT_WHYNOT_LOGIC_WHYNOT_PROOF_CLASS = ((Surrogate*)(internRigidSymbolWrtModule("WHYNOT-PROOF-CLASS", NULL, 1)));
    SYM_WHYNOT_LOGIC_REPRESENTATIVE = ((Symbol*)(internRigidSymbolWrtModule("REPRESENTATIVE", NULL, 0)));
    SYM_WHYNOT_LOGIC_DEVIATING_PATTERN = ((Symbol*)(internRigidSymbolWrtModule("DEVIATING-PATTERN", NULL, 0)));
    SYM_WHYNOT_LOGIC_DEVIATING_VARIABLE = ((Symbol*)(internRigidSymbolWrtModule("DEVIATING-VARIABLE", NULL, 0)));
    SYM_WHYNOT_LOGIC_DEVIATING_INSTANCES = ((Symbol*)(internRigidSymbolWrtModule("DEVIATING-INSTANCES", NULL, 0)));
    SGT_WHYNOT_LOGIC_ALTERNATIVE_BINDINGS_SET = ((Surrogate*)(internRigidSymbolWrtModule("ALTERNATIVE-BINDINGS-SET", NULL, 1)));
    SYM_WHYNOT_LOGIC_THE_VARIABLE = ((Symbol*)(internRigidSymbolWrtModule("THE-VARIABLE", NULL, 0)));
    SYM_WHYNOT_LOGIC_BINDINGS = ((Symbol*)(internRigidSymbolWrtModule("BINDINGS", NULL, 0)));
    KWD_WHYNOT_REALISTIC = ((Keyword*)(internRigidSymbolWrtModule("REALISTIC", NULL, 2)));
    KWD_WHYNOT_AND_INTRODUCTION = ((Keyword*)(internRigidSymbolWrtModule("AND-INTRODUCTION", NULL, 2)));
    KWD_WHYNOT_MATCH_MODE = ((Keyword*)(internRigidSymbolWrtModule("MATCH-MODE", NULL, 2)));
    KWD_WHYNOT_WHYNOT = ((Keyword*)(internRigidSymbolWrtModule("WHYNOT", NULL, 2)));
    KWD_WHYNOT_JUSTIFICATIONS = ((Keyword*)(internRigidSymbolWrtModule("JUSTIFICATIONS", NULL, 2)));
    KWD_WHYNOT_BRIEF = ((Keyword*)(internRigidSymbolWrtModule("BRIEF", NULL, 2)));
    KWD_WHYNOT_NOT_ASSERTED = ((Keyword*)(internRigidSymbolWrtModule("NOT-ASSERTED", NULL, 2)));
    KWD_WHYNOT_NO_RULES = ((Keyword*)(internRigidSymbolWrtModule("NO-RULES", NULL, 2)));
    SYM_WHYNOT_LOGIC_STARTUP_WHYNOT = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-WHYNOT", NULL, 0)));
    SYM_WHYNOT_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void startupWhynot() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupWhynot1();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("WHYNOT-PARTIAL-MATCH", "(DEFCLASS WHYNOT-PARTIAL-MATCH (INCREMENTAL-PARTIAL-MATCH) :DOCUMENTATION \"Variant of :BASIC partial match strategy to support WHYNOT queries.\" :SLOTS ((UNKNOWN-GOAL-CUTOFF :TYPE INTEGER :INITIALLY NULL)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newWhynotPartialMatch));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessWhynotPartialMatchSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("WHYNOT-DEEP-PARTIAL-MATCH", "(DEFCLASS WHYNOT-DEEP-PARTIAL-MATCH (WHYNOT-PARTIAL-MATCH) :DOCUMENTATION \"Variant of WhyNot partial match geared towards deep proofs.\")");

        clasS->classConstructorCode = ((cpp_function_code)(&newWhynotDeepPartialMatch));
      }
      { Class* clasS = defineClassFromStringifiedSource("WHYNOT-PROOF-CLASS", "(DEFCLASS WHYNOT-PROOF-CLASS (SET) :DOCUMENTATION \"Set of equivalent WhyNot proofs that differ in at most one\nvariable binding all on the same `deviating-variable'.\" :PARAMETERS ((ANY-VALUE :TYPE JUSTIFICATION)) :SLOTS ((REPRESENTATIVE :TYPE JUSTIFICATION) (DEVIATING-PATTERN :TYPE JUSTIFICATION) (DEVIATING-VARIABLE :TYPE PATTERN-VARIABLE) (DEVIATING-INSTANCES :TYPE LIST :INITIALLY (NEW LIST))))");

        clasS->classConstructorCode = ((cpp_function_code)(&newWhynotProofClass));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessWhynotProofClassSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("ALTERNATIVE-BINDINGS-SET", "(DEFCLASS ALTERNATIVE-BINDINGS-SET (THING) :DOCUMENTATION \"Represents a set of alternative bindings collected for the pattern\nvariable `(the-variable self)'.\" :SLOTS ((THE-VARIABLE :TYPE PATTERN-VARIABLE) (BINDINGS :TYPE SET :INITIALLY (NEW SET)) (SURROGATE-VALUE-INVERSE :INITIALLY @ALTERNATIVE-BINDINGS-SET)) :PRINT-FORM (PRINT-STREAM STREAM (STRING-DOWNCASE (GET-SKOLEM-PRINT-NAME (THE-VARIABLE SELF)))))");

        clasS->classConstructorCode = ((cpp_function_code)(&newAlternativeBindingsSet));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessAlternativeBindingsSetSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("WHYNOT-PARTIAL-MATCH-MODE?", "(DEFUN (WHYNOT-PARTIAL-MATCH-MODE? BOOLEAN) () :GLOBALLY-INLINE? TRUE (RETURN (AND (PARTIAL-MATCH-MODE?) (ISA? (PARTIAL-MATCH-STRATEGY *QUERYITERATOR*) @WHYNOT-PARTIAL-MATCH))))", ((cpp_function_code)(&whynotPartialMatchModeP)), NULL);
      defineMethodObject("(DEFMETHOD (CREATE-PARTIAL-MATCH-FRAME WHYNOT-PARTIAL-MATCH) ((SELF WHYNOT-PARTIAL-MATCH) (FRAME CONTROL-FRAME) (KIND KEYWORD)))", wrapMethodCode(((cpp_method_code)(&WhynotPartialMatch::createPartialMatchFrame))), NULL);
      defineMethodObject("(DEFMETHOD (CREATE-PARTIAL-MATCH-FRAME WHYNOT-DEEP-PARTIAL-MATCH) ((SELF WHYNOT-DEEP-PARTIAL-MATCH) (FRAME CONTROL-FRAME) (KIND KEYWORD)))", wrapMethodCode(((cpp_method_code)(&WhynotDeepPartialMatch::createPartialMatchFrame))), NULL);
      defineMethodObject("(DEFMETHOD SET-DYNAMIC-CUTOFF ((SELF WHYNOT-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&WhynotPartialMatch::setDynamicCutoff))), NULL);
      defineMethodObject("(DEFMETHOD (COMPUTE-UNKNOWN-GOAL-CUTOFF INTEGER) ((SELF WHYNOT-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&WhynotPartialMatch::computeUnknownGoalCutoff))), NULL);
      defineMethodObject("(DEFMETHOD (NUMBER-OF-FAILED-SUBGOALS INTEGER) ((SELF WHYNOT-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&WhynotPartialMatch::numberOfFailedSubgoals))), NULL);
      defineFunctionObject("COMPUTE-NUMBER-OF-FAILED-SUBGOALS", "(DEFUN (COMPUTE-NUMBER-OF-FAILED-SUBGOALS INTEGER) ((PROOF JUSTIFICATION)))", ((cpp_function_code)(&computeNumberOfFailedSubgoals)), NULL);
      defineMethodObject("(DEFMETHOD (CUTOFF-PARTIAL-MATCH? BOOLEAN) ((SELF WHYNOT-PARTIAL-MATCH) (TRACE? BOOLEAN)))", wrapMethodCode(((cpp_method_code)(&WhynotPartialMatch::cutoffPartialMatchP))), NULL);
      defineFunctionObject("AUXILIARY-EQUIVALENCE-PROPOSITION?", "(DEFUN (AUXILIARY-EQUIVALENCE-PROPOSITION? BOOLEAN) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&auxiliaryEquivalencePropositionP)), NULL);
      defineMethodObject("(DEFMETHOD (PROPOSITION-WEIGHT FLOAT) ((SELF WHYNOT-PARTIAL-MATCH) (PROPOSITION PROPOSITION)))", wrapMethodCode(((cpp_method_code)(&WhynotPartialMatch::propositionWeight))), NULL);
      defineExternalSlotFromStringifiedSource("(DEFSLOT CONTROL-FRAME REAL-ALLOTTED-CLOCK-TICKS :TYPE INTEGER :ALLOCATION :DYNAMIC)");
      defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-AND-PROOF KEYWORD) ((SELF WHYNOT-PARTIAL-MATCH) (FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&WhynotPartialMatch::continuePartialAndProof))), NULL);
      defineFunctionObject("NUMBER-OF-REMAINING-ANTECEDENTS", "(DEFUN (NUMBER-OF-REMAINING-ANTECEDENTS INTEGER) ((ITERATOR ITERATOR)))", ((cpp_function_code)(((int  (*) (Iterator*))(&numberOfRemainingAntecedents)))), NULL);
      defineMethodObject("(DEFMETHOD (CHAINING-DEPTH-DEGRADATION FLOAT) ((SELF WHYNOT-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&WhynotPartialMatch::chainingDepthDegradation))), NULL);
      defineMethodObject("(DEFMETHOD (CHAINING-DEPTH-DEGRADATION FLOAT) ((SELF WHYNOT-DEEP-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&WhynotDeepPartialMatch::chainingDepthDegradation))), NULL);
      defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-ANTECEDENTS-PROOF KEYWORD) ((SELF WHYNOT-PARTIAL-MATCH) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&WhynotPartialMatch::continuePartialAntecedentsProof))), NULL);
      defineMethodObject("(DEFMETHOD (MAX-UNCONSTRAINED-FANOUT FLOAT) ((SELF WHYNOT-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&WhynotPartialMatch::maxUnconstrainedFanout))), NULL);
      defineMethodObject("(DEFMETHOD (MAX-UNCONSTRAINED-FANOUT FLOAT) ((SELF WHYNOT-DEEP-PARTIAL-MATCH)))", wrapMethodCode(((cpp_method_code)(&WhynotDeepPartialMatch::maxUnconstrainedFanout))), NULL);
      defineMethodObject("(DEFMETHOD (SKIP-AND-CLAUSE? BOOLEAN) ((SELF WHYNOT-PARTIAL-MATCH) (FRAME CONTROL-FRAME) (FORBIDDENVARS (CONS OF PATTERN-VARIABLE))))", wrapMethodCode(((cpp_method_code)(&WhynotPartialMatch::skipAndClauseP))), NULL);
      defineMethodObject("(DEFMETHOD INITIALIZE-PARTIAL-MATCH-STRATEGY ((SELF WHYNOT-PARTIAL-MATCH) (QUERY QUERY-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&WhynotPartialMatch::initializePartialMatchStrategy))), NULL);
      defineExternalSlotFromStringifiedSource("(DEFSLOT CONTROL-FRAME ALL-JUSTIFICATIONS :TYPE (LIST OF JUSTIFICATION) :ALLOCATION :DYNAMIC)");
      defineMethodObject("(DEFMETHOD (COMPUTE-PARTIAL-TRUTH FLOAT) ((SELF WHYNOT-PARTIAL-MATCH) (QUERY QUERY-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&WhynotPartialMatch::computePartialTruth))), NULL);
      defineFunctionObject("BETTER-WHYNOT-PROOF?", "(DEFUN (BETTER-WHYNOT-PROOF? BOOLEAN) ((PROOF1 JUSTIFICATION) (PROOF2 JUSTIFICATION)))", ((cpp_function_code)(&betterWhynotProofP)), NULL);
      defineFunctionObject("COMPUTE-PROOF-DEVIATION", "(DEFUN (COMPUTE-PROOF-DEVIATION INTEGER) ((PROOF1 JUSTIFICATION) (PROOF2 JUSTIFICATION) (MAXDEVIATIONS INTEGER) (DEVIATIONS (KEY-VALUE-LIST OF JUSTIFICATION JUSTIFICATION))))", ((cpp_function_code)(&computeProofDeviation)), NULL);
      defineFunctionObject("INSERT-WHYNOT-PROOF-TO-CLASS?", "(DEFUN (INSERT-WHYNOT-PROOF-TO-CLASS? BOOLEAN) ((CLASS WHYNOT-PROOF-CLASS) (PROOF JUSTIFICATION)))", ((cpp_function_code)(&insertWhynotProofToClassP)), NULL);
      defineFunctionObject("INSERT-WHYNOT-PROOF", "(DEFUN (INSERT-WHYNOT-PROOF WHYNOT-PROOF-CLASS) ((CLASSES (LIST OF WHYNOT-PROOF-CLASS)) (PROOF JUSTIFICATION)))", ((cpp_function_code)(&insertWhynotProof)), NULL);
      defineFunctionObject("BETTER-WHYNOT-PROOF-CLASS?", "(DEFUN (BETTER-WHYNOT-PROOF-CLASS? BOOLEAN) ((CLASS1 WHYNOT-PROOF-CLASS) (CLASS2 WHYNOT-PROOF-CLASS)))", ((cpp_function_code)(&betterWhynotProofClassP)), NULL);
      defineFunctionObject("ALTERNATIVE-BINDINGS-SET?", "(DEFUN (ALTERNATIVE-BINDINGS-SET? BOOLEAN) ((THING OBJECT)) :GLOBALLY-INLINE? TRUE (RETURN (AND (DEFINED? THING) (ISA? THING @ALTERNATIVE-BINDINGS-SET))))", ((cpp_function_code)(&alternativeBindingsSetP)), NULL);
      defineFunctionObject("ALTERNATIVE-BINDINGS", "(DEFUN (ALTERNATIVE-BINDINGS SET) ((BINDINGSSET ALTERNATIVE-BINDINGS-SET)) :GLOBALLY-INLINE? TRUE (RETURN (BINDINGS BINDINGSSET)))", ((cpp_function_code)(&alternativeBindings)), NULL);
      defineFunctionObject("POST-PROCESS-WHYNOT-PROOF-CLASSES", "(DEFUN POST-PROCESS-WHYNOT-PROOF-CLASSES ((CLASSES (LIST OF WHYNOT-PROOF-CLASS))))", ((cpp_function_code)(&postProcessWhynotProofClasses)), NULL);
      defineFunctionObject("CUTOFF-SIMILAR-WHYNOT-PROOFS", "(DEFUN CUTOFF-SIMILAR-WHYNOT-PROOFS ((QUERY QUERY-ITERATOR)))", ((cpp_function_code)(&cutoffSimilarWhynotProofs)), NULL);
      defineMethodObject("(DEFMETHOD (RETRIEVE-PARTIAL-SOLUTIONS QUERY-ITERATOR) ((SELF WHYNOT-PARTIAL-MATCH) (QUERY QUERY-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&WhynotPartialMatch::retrievePartialSolutions))), NULL);
      defineFunctionObject("RETRIEVAL-PROOF-SOLUTION", "(DEFUN (RETRIEVAL-PROOF-SOLUTION CONS) ((PROOF JUSTIFICATION) (QUERY QUERY-ITERATOR)))", ((cpp_function_code)(&retrievalProofSolution)), NULL);
      defineFunctionObject("COLLECT-FAILED-GOALS", "(DEFUN COLLECT-FAILED-GOALS ((PROOF JUSTIFICATION) (FAILURES (LIST OF JUSTIFICATION))))", ((cpp_function_code)(&collectFailedGoals)), NULL);
      defineFunctionObject("DERIVE-JUSTIFIED-PARTIAL-QUERY", "(DEFUN (DERIVE-JUSTIFIED-PARTIAL-QUERY QUERY-ITERATOR) ((QUERY QUERY-ITERATOR)))", ((cpp_function_code)(&deriveJustifiedPartialQuery)), NULL);
      defineFunctionObject("WHYNOT", "(DEFUN WHYNOT (|&REST| (ARGS OBJECT)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&whynot)), ((cpp_function_code)(&whynotEvaluatorWrapper)));
      defineFunctionObject("EXPLAIN-WHYNOT", "(DEFUN EXPLAIN-WHYNOT ((LABEL STRING) (STYLE KEYWORD) (MAXDEPTH INTEGER) (SUMMARY? BOOLEAN) (STREAM OUTPUT-STREAM)) :DOCUMENTATION \"Programmer's interface to the WHYNOT function.\" :PUBLIC? TRUE)", ((cpp_function_code)(&explainWhynot)), NULL);
      defineFunctionObject("PRINT-WHYNOT-JUSTIFICATION", "(DEFUN PRINT-WHYNOT-JUSTIFICATION ((JUSTIFICATION JUSTIFICATION) (STREAM OUTPUT-STREAM) (MAXDEPTH INTEGER) (STYLE KEYWORD) (SUMMARY? BOOLEAN)) :DOCUMENTATION \"Print a WHYNOT `justification' to `stream' according to\n`maxDepth' and `style'.  Print a summary only if `summary?' is TRUE.\" :PUBLIC? TRUE)", ((cpp_function_code)(&printWhynotJustification)), NULL);
      defineFunctionObject("GET-WHYNOT-JUSTIFICATIONS", "(DEFUN (GET-WHYNOT-JUSTIFICATIONS (LIST OF JUSTIFICATION)) ((QUERY QUERY-ITERATOR) (LABEL STRING) (MAPPING EXPLANATION-MAPPING)) :DOCUMENTATION \"Programmer's interface to WHYNOT function.  Derive\njustifications why `query' failed, or, if `label' was supplied as non-NULL,\nlookup its justification relative to `mapping' and return the result.\")", ((cpp_function_code)(&getWhynotJustifications)), NULL);
      defineFunctionObject("STARTUP-WHYNOT", "(DEFUN STARTUP-WHYNOT () :PUBLIC? TRUE)", ((cpp_function_code)(&startupWhynot)), NULL);
      { MethodSlot* function = lookupFunction(SYM_WHYNOT_LOGIC_STARTUP_WHYNOT);

        setDynamicSlotValue(function->dynamicSlots, SYM_WHYNOT_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupWhynot"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFGLOBAL *MIN-CLOCK-TICKS-PER-WHYNOT-ANTECEDENT* INTEGER 5)", &oMIN_CLOCK_TICKS_PER_WHYNOT_ANTECEDENTo);
      defineGlobalVariableObject("(DEFSPECIAL *MAX-WHYNOT-PROOF-CLASS-DEVIATIONS* INTEGER 1)", &oMAX_WHYNOT_PROOF_CLASS_DEVIATIONSo);
      defineGlobalVariableObject("(DEFGLOBAL *SIMILAR-WHYNOT-PROOF-CUTOFF* INTEGER 3)", &oSIMILAR_WHYNOT_PROOF_CUTOFFo);
    }
  }
}

Surrogate* SGT_WHYNOT_LOGIC_WHYNOT_PARTIAL_MATCH = NULL;

Symbol* SYM_WHYNOT_LOGIC_UNKNOWN_GOAL_CUTOFF = NULL;

Surrogate* SGT_WHYNOT_LOGIC_WHYNOT_DEEP_PARTIAL_MATCH = NULL;

Keyword* KWD_WHYNOT_AND = NULL;

Symbol* SYM_WHYNOT_STELLA_ARGUMENTS = NULL;

Symbol* SYM_WHYNOT_LOGIC_JUSTIFICATION = NULL;

Surrogate* SGT_WHYNOT_LOGIC_M_WHYNOT_PARTIAL_MATCHdNUMBER_OF_FAILED_SUBGOALS_MEMO_TABLE_000 = NULL;

Keyword* KWD_WHYNOT_EQUIVALENT = NULL;

Keyword* KWD_WHYNOT_ISA = NULL;

Keyword* KWD_WHYNOT_NOT = NULL;

Symbol* SYM_WHYNOT_LOGIC_WEIGHT = NULL;

Keyword* KWD_WHYNOT_DOWN = NULL;

Symbol* SYM_WHYNOT_LOGIC_REAL_ALLOTTED_CLOCK_TICKS = NULL;

Keyword* KWD_WHYNOT_UP_TRUE = NULL;

Keyword* KWD_WHYNOT_UP_FAIL = NULL;

Keyword* KWD_WHYNOT_GOAL_TREE = NULL;

Keyword* KWD_WHYNOT_MOVE_DOWN = NULL;

Keyword* KWD_WHYNOT_FAILURE = NULL;

Surrogate* SGT_WHYNOT_STELLA_CONS_ITERATOR = NULL;

Symbol* SYM_WHYNOT_LOGIC_ANTECEDENTS_RULE = NULL;

Symbol* SYM_WHYNOT_STELLA_ITERATOR = NULL;

Keyword* KWD_WHYNOT_SKIPPED_CONJUNCT = NULL;

Keyword* KWD_WHYNOT_POPPED = NULL;

Keyword* KWD_WHYNOT_MINIMUM_SCORE = NULL;

Keyword* KWD_WHYNOT_MAXIMUM_UNKNOWNS = NULL;

Symbol* SYM_WHYNOT_LOGIC_LATEST_POSITIVE_SCORE = NULL;

Symbol* SYM_WHYNOT_LOGIC_ALL_JUSTIFICATIONS = NULL;

Keyword* KWD_WHYNOT_MAXIMIZE_SCOREp = NULL;

Keyword* KWD_WHYNOT_PATTERN = NULL;

Surrogate* SGT_WHYNOT_LOGIC_WHYNOT_PROOF_CLASS = NULL;

Symbol* SYM_WHYNOT_LOGIC_REPRESENTATIVE = NULL;

Symbol* SYM_WHYNOT_LOGIC_DEVIATING_PATTERN = NULL;

Symbol* SYM_WHYNOT_LOGIC_DEVIATING_VARIABLE = NULL;

Symbol* SYM_WHYNOT_LOGIC_DEVIATING_INSTANCES = NULL;

Surrogate* SGT_WHYNOT_LOGIC_ALTERNATIVE_BINDINGS_SET = NULL;

Symbol* SYM_WHYNOT_LOGIC_THE_VARIABLE = NULL;

Symbol* SYM_WHYNOT_LOGIC_BINDINGS = NULL;

Keyword* KWD_WHYNOT_REALISTIC = NULL;

Keyword* KWD_WHYNOT_AND_INTRODUCTION = NULL;

Keyword* KWD_WHYNOT_MATCH_MODE = NULL;

Keyword* KWD_WHYNOT_WHYNOT = NULL;

Keyword* KWD_WHYNOT_JUSTIFICATIONS = NULL;

Keyword* KWD_WHYNOT_BRIEF = NULL;

Keyword* KWD_WHYNOT_NOT_ASSERTED = NULL;

Keyword* KWD_WHYNOT_NO_RULES = NULL;

Symbol* SYM_WHYNOT_LOGIC_STARTUP_WHYNOT = NULL;

Symbol* SYM_WHYNOT_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
