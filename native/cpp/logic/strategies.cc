//  -*- Mode: C++ -*-

// strategies.cc

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

Keyword* continueStrategiesProofs(ControlFrame* frame, Keyword* lastmove) {
  { Keyword* result = NULL;

    if (lastmove == KWD_STRATEGIES_DOWN) {
      unwindToChoicePoint(frame);
      frame->justifications->clear();
      if (((boolean)(frame->down))) {
        return (KWD_STRATEGIES_MOVE_DOWN);
      }
    }
    else if ((lastmove == KWD_STRATEGIES_UP_TRUE) ||
        (lastmove == KWD_STRATEGIES_UP_FAIL)) {
      result = resumeProofStrategyAfterSubgoal(frame, lastmove);
      if (result == KWD_STRATEGIES_FAILURE) {
        result = NULL;
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    for (;;) {
      if (!((boolean)(result))) {
        result = continueCurrentOrNextStrategy(frame);
      }
      if ((result == KWD_STRATEGIES_FINAL_SUCCESS) ||
          (result == KWD_STRATEGIES_CONTINUING_SUCCESS)) {
        if (((boolean)(frame->proposition)) &&
            (((frame->truthValue == DEFAULT_TRUE_TRUTH_VALUE) ||
            (frame->truthValue == DEFAULT_FALSE_TRUTH_VALUE)) &&
             hasShallowDisproofP(frame))) {
          if (traceKeywordP(KWD_STRATEGIES_GOAL_TREE)) {
            { TruthValue* truthvalue = frame->truthValue;
              boolean defaultP = (truthvalue == DEFAULT_TRUE_TRUTH_VALUE) ||
                  (truthvalue == DEFAULT_FALSE_TRUTH_VALUE);

              printVerticalBars(computeFrameDepth(frame) + 1);
              std::cout << "CLSH: truth=" << truthValueToString(truthvalue, true) << std::endl;
            }
          }
          unwindToChoicePoint(frame);
          if ((!((frame->truthValue == DEFAULT_TRUE_TRUTH_VALUE) ||
              (frame->truthValue == DEFAULT_FALSE_TRUTH_VALUE))) &&
              allArgumentsBoundP(frame->proposition)) {
            result = KWD_STRATEGIES_FAILURE;
          }
          else {
            setFrameTruthValue(frame, NULL);
            frame->justifications->clear();
            if (((boolean)(frame->partialMatchFrame))) {
              frame->partialMatchFrame->clearFramePartialTruth();
            }
            if (((boolean)(frame->down))) {
              result = KWD_STRATEGIES_MOVE_DOWN;
            }
            else {
              result = NULL;
              continue;
            }
          }
        }
      }
      else {
      }
      if ((result == KWD_STRATEGIES_CONTINUING_SUCCESS) ||
          (result == KWD_STRATEGIES_FINAL_SUCCESS)) {
        if (!((boolean)(frame->truthValue))) {
          setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
        }
        if ((((boolean)(oQUERYITERATORo)) &&
            ((boolean)(oQUERYITERATORo->partialMatchStrategy))) &&
            (!(((boolean)(frame->partialMatchFrame)) &&
            (frame->partialMatchFrame->matchScore != NULL_FLOAT)))) {
          frame->partialMatchFrame->setFramePartialTruth(TRUE_TRUTH_VALUE, NULL_FLOAT, false);
        }
        if (oRECORD_JUSTIFICATIONSpo &&
            (!((boolean)(((Justification*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_JUSTIFICATION, NULL))))))) {
          recordPrimitiveJustification(frame, KWD_STRATEGIES_UP_TRUE);
        }
      }
      else if ((result == KWD_STRATEGIES_FAILURE) ||
          (result == KWD_STRATEGIES_TERMINAL_FAILURE)) {
        if (((boolean)(oQUERYITERATORo)) &&
            ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
          {
            if (!(((boolean)(frame->partialMatchFrame)) &&
                (frame->partialMatchFrame->matchScore != NULL_FLOAT))) {
              frame->partialMatchFrame->setFramePartialTruth(frame->truthValue, (((boolean)(frame->truthValue)) ? NULL_FLOAT : 0.0), ((boolean)(frame->truthValue)));
            }
            if (oRECORD_JUSTIFICATIONSpo &&
                ((!((boolean)(((Justification*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_JUSTIFICATION, NULL)))))) &&
                 ((boolean)(frame->proposition)))) {
              recordPrimitiveJustification(frame, KWD_STRATEGIES_UP_FAIL);
            }
          }
        }
        else {
          if (((frame->truthValue == UNKNOWN_TRUTH_VALUE) ||
              (!((boolean)(frame->truthValue)))) &&
              ((!((boolean)(((Keyword*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_INFERENCE_CUTOFF_REASON, NULL)))))) &&
               (((boolean)(frame->proposition)) &&
                closedPropositionP(frame->proposition)))) {
            setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
            if (oRECORD_JUSTIFICATIONSpo &&
                (!((boolean)(((Justification*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_JUSTIFICATION, NULL))))))) {
              recordClosedNotJustification(frame, KWD_STRATEGIES_UP_FAIL);
            }
          }
        }
      }
      else {
      }
      return (result);
    }
  }
}

void clearStrategySlots(ControlFrame* frame) {
  if (((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)))))) {
    setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL, NULL);
  }
  if (((boolean)(((Proposition*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_ANTECEDENTS_RULE, NULL)))))) {
    setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_ANTECEDENTS_RULE, NULL, NULL);
  }
  if (((boolean)(((ProofAdjunct*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_PROOF_ADJUNCT, NULL)))))) {
    setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_PROOF_ADJUNCT, NULL, NULL);
  }
}

ControlFrame* selectNextStrategy(ControlFrame* frame) {
  { Keyword* strategy = NULL;

    if (((boolean)(frame->currentStrategy))) {
      strategy = frame->currentStrategy;
    }
    else if (frame->state == KWD_STRATEGIES_PARALLEL_STRATEGIES) {
      strategy = KWD_STRATEGIES_SELECT_PARALLEL_THREAD;
    }
    else {
      for (;;) {
        strategy = ((Keyword*)(frame->nextStrategies->value));
        if (!((boolean)(strategy))) {
          return (frame);
        }
        frame->nextStrategies = frame->nextStrategies->rest;
        if (filterOutStrategyP(strategy, frame)) {
          continue;
        }
        if (parallelStrategyP(strategy)) {
          frame = parallelizeControlFrame(frame);
          frame->nextStrategies = cons(strategy, frame->nextStrategies);
          strategy = KWD_STRATEGIES_SELECT_PARALLEL_THREAD;
        }
        clearStrategySlots(frame);
        break;
      }
    }
    frame->currentStrategy = strategy;
    return (frame);
  }
}

void recordBasePartialMatchTruth(ControlFrame* frame, Keyword* result) {
  { Keyword* pmresult = (((result == KWD_STRATEGIES_FAILURE) ||
        frame->reversePolarityP) ? KWD_STRATEGIES_FAIL : KWD_STRATEGIES_TRUE);

    if (((boolean)(oQUERYITERATORo)) &&
        ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
      oQUERYITERATORo->partialMatchStrategy->setBasePartialMatchTruth(frame->proposition, pmresult);
    }
  }
}

Keyword* continueCurrentOrNextStrategy(ControlFrame* frame) {
  { Keyword* result = NULL;

    for (;;) {
      frame = selectNextStrategy(frame);
      if (!((boolean)(frame->currentStrategy))) {
        if (((boolean)(oTRACED_KEYWORDSo)) &&
            oTRACED_KEYWORDSo->membP(KWD_STRATEGIES_STRATEGIES)) {
          std::cout << std::endl;
        }
        if (frame->justifications->nonEmptyP()) {
          return (KWD_STRATEGIES_FINAL_SUCCESS);
        }
        else {
          return (KWD_STRATEGIES_FAILURE);
        }
      }
      if (((boolean)(oTRACED_KEYWORDSo)) &&
          oTRACED_KEYWORDSo->membP(KWD_STRATEGIES_STRATEGIES)) {
        std::cout << " " << frame->currentStrategy;
        flushOutput(STANDARD_OUTPUT);
      }
      if (traceKeywordP(KWD_STRATEGIES_STRATEGIES)) {
        { Description* description = ((Description*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_DESCRIPTION, NULL)));

          if (((boolean)(description)) &&
              namedDescriptionP(description)) {
            std::cout << "(" << description->surrogateValueInverse->symbolName << ")";
          }
        }
      }
      if (frame->reversePolarityP) {
        { 
          BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, true);
          result = executeProofStrategy(frame);
        }
      }
      else {
        result = executeProofStrategy(frame);
      }
      if (result == KWD_STRATEGIES_TERMINAL_FAILURE) {
        frame->nextStrategies = NIL;
        result = KWD_STRATEGIES_FAILURE;
      }
      else if ((result == KWD_STRATEGIES_MOVE_DOWN) ||
          ((result == KWD_STRATEGIES_MOVE_IN_PLACE) ||
           (result == KWD_STRATEGIES_TIME_OUT))) {
        if (((boolean)(oTRACED_KEYWORDSo)) &&
            oTRACED_KEYWORDSo->membP(KWD_STRATEGIES_STRATEGIES)) {
          std::cout << std::endl;
        }
        return (result);
      }
      else {
      }
      recordBasePartialMatchTruth(frame, result);
      if (traceKeywordP(KWD_STRATEGIES_STRATEGIES)) {
        if (result == KWD_STRATEGIES_FAILURE) {
          std::cout << " ";
        }
        else {
          std::cout << std::endl;
        }
      }
      if (result == KWD_STRATEGIES_FAILURE) {
        frame->currentStrategy = NULL;
      }
      else {
        return (result);
      }
    }
  }
}

Keyword* resumeProofStrategyAfterSubgoal(ControlFrame* frame, Keyword* lastmove) {
  { Keyword* result = NULL;

    { Keyword* testValue000 = frame->currentStrategy;

      if (testValue000 == KWD_STRATEGIES_SPECIALIST) {
        result = continueSpecialistProof(frame, lastmove);
      }
      else if (testValue000 == KWD_STRATEGIES_ANTECEDENTS) {
        if (((boolean)(frame->partialMatchFrame))) {
          result = frame->partialMatchFrame->continuePartialAntecedentsProof(lastmove);
        }
        else {
          result = continueAntecedentsProof(frame, lastmove);
        }
      }
      else if (testValue000 == KWD_STRATEGIES_CLUSTERED_CONJUNCTION) {
        result = continueClusteredConjunctionProof(frame, lastmove);
      }
      else if (testValue000 == KWD_STRATEGIES_CONDITIONAL_ANTECEDENT) {
        result = continueConditionalAntecedentProof(frame, lastmove);
      }
      else if (testValue000 == KWD_STRATEGIES_DISJUNCTIVE_IMPLICATION_INTRODUCTION) {
        result = resumeDisjunctiveImplicationProof(frame, lastmove);
      }
      else {
        propagateFrameTruthValue(frame->result, frame);
        if (((boolean)(frame->result->partialMatchFrame))) {
          frame->result->partialMatchFrame->propagateFramePartialTruth(frame);
        }
        if (lastmove == KWD_STRATEGIES_UP_TRUE) {
          if (((boolean)(frame->down))) {
            result = KWD_STRATEGIES_CONTINUING_SUCCESS;
          }
          else {
            result = KWD_STRATEGIES_FINAL_SUCCESS;
          }
        }
        else if (lastmove == KWD_STRATEGIES_UP_FAIL) {
          if ((frame->truthValue == FALSE_TRUTH_VALUE) ||
              (frame->truthValue == DEFAULT_FALSE_TRUTH_VALUE)) {
            result = KWD_STRATEGIES_TERMINAL_FAILURE;
          }
          else {
            result = KWD_STRATEGIES_FAILURE;
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
    if (result == KWD_STRATEGIES_CONTINUING_SUCCESS) {
      if (oGENERATE_ALL_PROOFSpo &&
          ((frame->state == KWD_STRATEGIES_ATOMIC_GOAL) &&
           ((!(((boolean)(oQUERYITERATORo)) &&
          ((boolean)(oQUERYITERATORo->partialMatchStrategy)))) &&
            (!newBindingsSinceLastChoicePointP(frame))))) {
        frame->justifications->push(KWD_STRATEGIES_DUMMY_JUSTIFICATION);
        result = KWD_STRATEGIES_MOVE_DOWN;
      }
    }
    else if ((result == KWD_STRATEGIES_FINAL_SUCCESS) ||
        (result == KWD_STRATEGIES_TERMINAL_FAILURE)) {
      frame->nextStrategies = NIL;
      frame->currentStrategy = NULL;
      if (result == KWD_STRATEGIES_TERMINAL_FAILURE) {
        result = KWD_STRATEGIES_FAILURE;
      }
    }
    else if (result == KWD_STRATEGIES_FAILURE) {
      frame->currentStrategy = NULL;
    }
    else if ((result == KWD_STRATEGIES_MOVE_DOWN) ||
        (result == KWD_STRATEGIES_MOVE_IN_PLACE)) {
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "`" << result << "'" << " is not a valid case option";
        throw *newStellaException(stream001->theStringReader());
      }
    }
    return (result);
  }
}

boolean filterOutStrategyP(Keyword* strategy, ControlFrame* frame) {
  if (strategy == KWD_STRATEGIES_LOOKUP_GOAL_CACHES) {
    return ((!((BooleanWrapper*)(dynamicSlotValue(surrogateToDescription(((Surrogate*)(frame->proposition->operatoR)))->dynamicSlots, SYM_STRATEGIES_LOGIC_CHECK_FOR_CACHED_GOALSp, FALSE_WRAPPER)))->wrapperValue) ||
        (!((oCACHE_SUCCEEDED_GOALSpo ||
        oCACHE_FAILED_GOALSpo) &&
        ((oDUPLICATE_SUBGOAL_STRATEGYo == KWD_STRATEGIES_DUPLICATE_GOALS) &&
         (!(((boolean)(oQUERYITERATORo)) &&
        ((boolean)(oQUERYITERATORo->partialMatchStrategy))))))));
  }
  else if (strategy == KWD_STRATEGIES_SPECIALIST) {
    { Proposition* proposition = frame->proposition;
      NamedDescription* description = getDescription(((Surrogate*)(proposition->operatoR)));

      return (lookupSpecialist(description) == NULL);
    }
  }
  else if (strategy == KWD_STRATEGIES_MANUFACTURE_SKOLEM) {
    { NamedDescription* description = getDescription(((Surrogate*)(frame->proposition->operatoR)));

      return ((!testPropertyP(description, SGT_STRATEGIES_PL_KERNEL_KB_TOTAL)) ||
          frame->reversePolarityP);
    }
  }
  else {
    return (false);
  }
}

Keyword* executeProofStrategy(ControlFrame* frame) {
  { Keyword* testValue000 = frame->currentStrategy;

    if (testValue000 == KWD_STRATEGIES_SPECIALIST) {
      return (continueSpecialistProof(frame, KWD_STRATEGIES_DOWN));
    }
    else if (testValue000 == KWD_STRATEGIES_LOOKUP_GOAL_CACHES) {
      return (tryGoalCachesProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_LOOKUP_ASSERTIONS) {
      return (tryLookupGroundAssertionsProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_SCAN_PROPOSITIONS) {
      return (tryScanPropositionsProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_SCAN_PARTIAL_PROPOSITIONS) {
      return (tryScanPartialPropositionsProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_SCAN_COLLECTION) {
      return (tryScanCollectionProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_SHALLOW_DISPROOF) {
      return (tryShallowDisproof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_SCAN_FOR_VALUE_CLASH) {
      return (tryScanForValueClashProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_MANUFACTURE_SKOLEM) {
      return (tryManufactureSkolemProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_ALL_SUBGOAL_STRATEGIES) {
      return (trySubgoalStrategiesProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_ANTECEDENTS) {
      if (((boolean)(frame->partialMatchFrame))) {
        return (frame->partialMatchFrame->continuePartialAntecedentsProof(KWD_STRATEGIES_DOWN));
      }
      else {
        return (continueAntecedentsProof(frame, KWD_STRATEGIES_DOWN));
      }
    }
    else if (testValue000 == KWD_STRATEGIES_FULL_SUBQUERY) {
      return (tryFullSubqueryProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_GOAL_COMPLEMENT) {
      return (tryGoalComplementProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_CONDITIONAL_ANTECEDENT) {
      return (continueConditionalAntecedentProof(frame, KWD_STRATEGIES_DOWN));
    }
    else if (testValue000 == KWD_STRATEGIES_FORWARD_GOALS) {
      return (tryForwardGoalsProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_IMPLIES) {
      return (tryImpliesProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_CONTAINED_BY) {
      return (tryContainedByProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_EQUIVALENCE) {
      return (tryEquivalenceProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_CLUSTERED_CONJUNCTION) {
      return (continueClusteredConjunctionProof(frame, KWD_STRATEGIES_DOWN));
    }
    else if (testValue000 == KWD_STRATEGIES_DISJUNCTIVE_IMPLICATION_INTRODUCTION) {
      return (tryDisjunctiveImplicationProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_UNIVERSAL_INTRODUCTION) {
      return (tryUniversalIntroductionProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_SUBSUMPTION_TEST) {
      return (trySubsumptionTest(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_REFUTATION) {
      return (tryRefutationProof(frame));
    }
    else if (testValue000 == KWD_STRATEGIES_SELECT_PARALLEL_THREAD) {
      return (tryParallelThreadProof(frame));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Keyword* continueParallelStrategiesProofs(ParallelControlFrame* pframe, Keyword* lastmove) {
  if (lastmove == KWD_STRATEGIES_DOWN) {
    if (((boolean)(pframe->down))) {
      enterParallelThread(pframe, NULL);
      return (KWD_STRATEGIES_MOVE_DOWN);
    }
    return (continueCurrentOrNextStrategy(pframe));
  }
  else if (lastmove == KWD_STRATEGIES_UP_TRUE) {
    exitParallelThread(pframe);
    if (pframe->unboundVariablesP) {
    }
    propagateFrameTruthValue(pframe->result, pframe);
    if (((boolean)(pframe->down))) {
      return (KWD_STRATEGIES_CONTINUING_SUCCESS);
    }
    else {
      return (KWD_STRATEGIES_FINAL_SUCCESS);
    }
  }
  else if (lastmove == KWD_STRATEGIES_UP_FAIL) {
    exitParallelThread(pframe);
    if (!(pframe->nextStrategies == NIL)) {
      pframe->state = KWD_STRATEGIES_STRATEGY;
      pframe->currentStrategy = NULL;
      return (continueCurrentOrNextStrategy(pframe));
    }
    propagateFrameTruthValue(pframe->result, pframe);
    return (KWD_STRATEGIES_FAILURE);
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

// List of strategies (keywords) that fork a parallel
// control stack before executing.
List* oPARALLEL_STRATEGIESo = NULL;

boolean parallelStrategyP(Keyword* strategy) {
  return (oPARALLEL_STRATEGIESo->memberP(strategy));
}

ParallelThread* selectNextChildThread(ParallelControlFrame* pframe) {
  return (((ParallelThread*)(pframe->childThreads->first())));
}

ParallelThread* createChildThread(ParallelControlFrame* pframe) {
  { Cons* strategies = pframe->nextStrategies;
    ParallelThread* childthread = newParallelThread();
    ControlFrame* downframe = createDownFrame(pframe, pframe->proposition);

    downframe->state = KWD_STRATEGIES_STRATEGY;
    downframe->currentStrategy = ((Keyword*)(strategies->value));
    pframe->nextStrategies = strategies->rest;
    if (((boolean)(oQUERYITERATORo)) &&
        ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
      createAndLinkPartialMatchFrame(downframe, KWD_STRATEGIES_STRATEGY);
    }
    childthread->topControlFrame = downframe;
    pframe->childThreads->insert(childthread);
    return (childthread);
  }
}

Keyword* tryParallelThreadProof(ControlFrame* frame) {
  { ParallelThread* childthread = createChildThread(((ParallelControlFrame*)(frame)));

    enterParallelThread(((ParallelControlFrame*)(frame)), childthread);
    return (KWD_STRATEGIES_MOVE_DOWN);
  }
}

void pushNextStrategy(ControlFrame* frame, Keyword* strategy) {
  frame->nextStrategies = cons(strategy, frame->nextStrategies);
}

ControlFrame* createSubgoalFrame(ControlFrame* upframe, Proposition* goal, Keyword* strategy) {
  { ControlFrame* downframe = createDownFrame(upframe, goal);

    if (((boolean)(strategy))) {
      if (((boolean)(goal)) &&
          (!(goal == upframe->proposition))) {
        downframe->state = KWD_STRATEGIES_ATOMIC_GOAL;
      }
      else {
        downframe->state = KWD_STRATEGIES_STRATEGY;
      }
      downframe->currentStrategy = strategy;
    }
    downframe->reversePolarityP = upframe->reversePolarityP;
    return (downframe);
  }
}

boolean specialistApplicableP(NamedDescription* description, Proposition* proposition) {
  { int dArity = description->arity();
    int pArity = proposition->arguments->length();

    if (dArity < 0) {
      return (true);
    }
    else {
      return (dArity == pArity);
    }
  }
}

Keyword* continueSpecialistProof(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    NamedDescription* description = getDescription(((Surrogate*)(proposition->operatoR)));
    cpp_function_code specialistcode = lookupSpecialist(description);
    Keyword* result = KWD_STRATEGIES_FAILURE;

    if ((specialistcode != NULL) &&
        specialistApplicableP(description, proposition)) {
      if (oPOWERLOOM_EXECUTION_MODEo == KWD_STRATEGIES_DEBUG) {
        result = ((Keyword*  (*) (ControlFrame*, Keyword*))specialistcode)(frame, lastmove);
      }
      else {
        try {
          result = ((Keyword*  (*) (ControlFrame*, Keyword*))specialistcode)(frame, lastmove);
        }
        catch (std::exception& _ne) {
          std::exception* ne = &_ne;

          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Exception executing specialist for " << "`" << description << "'" << ": " << std::endl << "`" << ne << "'" << std::endl;
        }
      }
      if (!((boolean)(frame->truthValue))) {
        if ((result == KWD_STRATEGIES_FINAL_SUCCESS) ||
            (result == KWD_STRATEGIES_CONTINUING_SUCCESS)) {
          setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
        }
        else {
        }
      }
    }
    return (result);
  }
}

int oFAILED_GOAL_CUTOFFSo = 0;

int oSUCCEEDED_GOAL_CUTOFFSo = 0;

Keyword* lookupCachedProof(ControlFrame* frame) {
  if ((!((BooleanWrapper*)(dynamicSlotValue(surrogateToDescription(((Surrogate*)(frame->proposition->operatoR)))->dynamicSlots, SYM_STRATEGIES_LOGIC_CHECK_FOR_CACHED_GOALSp, FALSE_WRAPPER)))->wrapperValue) ||
      (!((oCACHE_SUCCEEDED_GOALSpo ||
      oCACHE_FAILED_GOALSpo) &&
      ((oDUPLICATE_SUBGOAL_STRATEGYo == KWD_STRATEGIES_DUPLICATE_GOALS) &&
       (!(((boolean)(oQUERYITERATORo)) &&
      ((boolean)(oQUERYITERATORo->partialMatchStrategy)))))))) {
    return (KWD_STRATEGIES_FAILURE);
  }
  { Keyword* successorfailure = KWD_STRATEGIES_FAILURE;
    AtomicGoalCache* cachedgoal = findCachedGoal(frame, successorfailure);

    if (!((boolean)(cachedgoal))) {
      successorfailure = KWD_STRATEGIES_SUCCESS;
      cachedgoal = findCachedGoal(frame, successorfailure);
    }
    if (((boolean)(cachedgoal)) &&
        ((!oDONTUSEDEFAULTKNOWLEDGEpo) ||
         ((cachedgoal->truthValue == TRUE_TRUTH_VALUE) ||
          (cachedgoal->truthValue == FALSE_TRUTH_VALUE)))) {
      return (finishCachedGoalProcessing(cachedgoal, frame, successorfailure, false));
    }
    else {
      return (KWD_STRATEGIES_FAILURE);
    }
  }
}

Keyword* scanCachedGoals(ControlFrame* frame) {
  { Proposition* proposition = frame->proposition;
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)));
    AtomicGoalCache* cachedgoal = NULL;
    PatternRecord* patternrecord = oQUERYITERATORo->currentPatternRecord;
    int ubstackoffset = patternrecord->topUnbindingStackOffset;

    if (!((BooleanWrapper*)(dynamicSlotValue(surrogateToDescription(((Surrogate*)(proposition->operatoR)))->dynamicSlots, SYM_STRATEGIES_LOGIC_CHECK_FOR_CACHED_GOALSp, FALSE_WRAPPER)))->wrapperValue) {
      return (KWD_STRATEGIES_FAILURE);
    }
    if (!((boolean)(iterator))) {
      iterator = ((Iterator*)(setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, allCachedPropositions(frame), NULL)));
    }
    while (iterator->nextP()) {
      cachedgoal = ((AtomicGoalCache*)(iterator->value));
      { boolean alwaysP000 = true;

        { Object* arg = NULL;
          Vector* vector000 = proposition->arguments;
          int index000 = 0;
          int length000 = vector000->length();
          Object* cachedbinding = NULL;
          Cons* iter000 = cachedgoal->bindings;

          for  (; (index000 < length000) &&
                    (!(iter000 == NIL)); 
                index000 = index000 + 1,
                iter000 = iter000->rest) {
            arg = (vector000->theArray)[index000];
            cachedbinding = iter000->value;
            if (!bindArgumentToValueP(arg, cachedbinding, true)) {
              alwaysP000 = false;
              break;
            }
          }
        }
        if (alwaysP000) {
          return (finishCachedGoalProcessing(cachedgoal, frame, KWD_STRATEGIES_SUCCESS, true));
        }
      }
      unbindVariablesBeginningAt(patternrecord, ubstackoffset + 1);
    }
    return (KWD_STRATEGIES_FAILURE);
  }
}

Keyword* finishCachedGoalProcessing(AtomicGoalCache* cachedgoal, ControlFrame* frame, Keyword* successorfailure, boolean continuingP) {
  setDynamicSlotValue(oQUERYITERATORo->dynamicSlots, SYM_STRATEGIES_LOGIC_LATEST_POSITIVE_SCORE, wrapFloat(cachedgoal->matchScore), NULL_FLOAT_WRAPPER);
  frame->truthValue = cachedgoal->truthValue;
  if (((boolean)(frame->partialMatchFrame))) {
    frame->partialMatchFrame->setFramePartialTruth(cachedgoal->truthValue, cachedgoal->matchScore, true);
  }
  if (oRECORD_JUSTIFICATIONSpo &&
      ((boolean)(cachedgoal->justification))) {
    setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_JUSTIFICATION, cachedgoal->justification->copy(), NULL);
  }
  if (traceKeywordP(KWD_STRATEGIES_GOAL_CACHES) &&
      true) {
    { 
      BIND_STELLA_SPECIAL(oPRINTINFRAMEo, ControlFrame*, frame);
      BIND_STELLA_SPECIAL(oPRETTYPRINTLOGICALFORMSpo, boolean, false);
      if (successorfailure == KWD_STRATEGIES_SUCCESS) {
        std::cout << "USED CACHED SUCCESS+: ";
      }
      else if (successorfailure == KWD_STRATEGIES_FAILURE) {
        std::cout << "USED CACHED FAILURE-: ";
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << successorfailure << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      if ((frame->truthValue == DEFAULT_TRUE_TRUTH_VALUE) ||
          (frame->truthValue == DEFAULT_FALSE_TRUTH_VALUE)) {
        std::cout << "dflt";
      }
      std::cout << ((cachedgoal->reversePolarityP ? "~" : " ")) << frame->proposition << std::endl;
    }
  }
  if (successorfailure == KWD_STRATEGIES_SUCCESS) {
    oSUCCEEDED_GOAL_CUTOFFSo = oSUCCEEDED_GOAL_CUTOFFSo + 1;
    return ((continuingP ? KWD_STRATEGIES_CONTINUING_SUCCESS : KWD_STRATEGIES_FINAL_SUCCESS));
  }
  else if (successorfailure == KWD_STRATEGIES_FAILURE) {
    oFAILED_GOAL_CUTOFFSo = oFAILED_GOAL_CUTOFFSo + 1;
    if (((boolean)(frame->down))) {
      popFramesUpTo(frame->down);
    }
    return (KWD_STRATEGIES_TERMINAL_FAILURE);
  }
  else {
    { OutputStringStream* stream001 = newOutputStringStream();

      *(stream001->nativeStream) << "`" << successorfailure << "'" << " is not a valid case option";
      throw *newStellaException(stream001->theStringReader());
    }
  }
}

Keyword* tryGoalCachesProof(ControlFrame* frame) {
  if (!((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)))))) {
    { Proposition* proposition = frame->proposition;
      Keyword* cachedresult = lookupCachedProof(frame);

      if (!(cachedresult == KWD_STRATEGIES_FAILURE)) {
        return (cachedresult);
      }
      if (allArgumentsBoundP(proposition) ||
          ((!((oCACHE_SUCCEEDED_GOALSpo ||
          oCACHE_FAILED_GOALSpo) &&
          ((oDUPLICATE_SUBGOAL_STRATEGYo == KWD_STRATEGIES_DUPLICATE_GOALS) &&
           (!(((boolean)(oQUERYITERATORo)) &&
          ((boolean)(oQUERYITERATORo->partialMatchStrategy))))))) ||
           (!((boolean)(getGoalCacheList(proposition)))))) {
        return (KWD_STRATEGIES_FAILURE);
      }
    }
  }
  if (allKeyArgumentsBoundP(frame->proposition)) {
    if (scanCachedGoals(frame) == KWD_STRATEGIES_FAILURE) {
      return (KWD_STRATEGIES_FAILURE);
    }
    else {
      return (KWD_STRATEGIES_FINAL_SUCCESS);
    }
  }
  return (KWD_STRATEGIES_FAILURE);
}

Keyword* tryLookupGroundAssertionsProof(ControlFrame* frame) {
  if (frame->proposition->kind == KWD_STRATEGIES_ISA) {
    if (oREVERSEPOLARITYpo) {
      return (tryScanPropositionsProof(frame));
    }
    return (tryIsaPropositionProof(frame));
  }
  else {
    return (tryScanPropositionsProof(frame));
  }
}

Iterator* tsppDinitializeStrategy(ControlFrame* frame) {
  { Proposition* proposition = frame->proposition;
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)));

    if (!((boolean)(iterator))) {
      iterator = allMatchingPropositions(proposition);
      if (iterator == EMPTY_PROPOSITIONS_ITERATOR) {
        iterator = NULL;
      }
      else {
        setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, iterator, NULL);
      }
    }
    return (iterator);
  }
}

void tsppDspawnDerivedStrategies(ControlFrame* frame, Keyword* state) {
  { Proposition* proposition = frame->proposition;

    if ((state == KWD_STRATEGIES_INITIALIZE) &&
        ((((boolean)(oQUERYITERATORo)) &&
        ((boolean)(oQUERYITERATORo->partialMatchStrategy))) &&
         ((frame->currentStrategy == KWD_STRATEGIES_LOOKUP_ASSERTIONS) &&
          ((proposition->arguments->length() > 1) &&
           nullInstancePropositionsExistP())))) {
      pushNextStrategy(frame, KWD_STRATEGIES_SCAN_PARTIAL_PROPOSITIONS);
    }
    if ((state == KWD_STRATEGIES_FAILURE) &&
        (frame->reversePolarityP &&
         ((!(frame->currentStrategy == KWD_STRATEGIES_SHALLOW_DISPROOF)) &&
          (((proposition->kind == KWD_STRATEGIES_FUNCTION) ||
        singleValuedPredicateP(proposition)) &&
           allArgumentsBoundP(proposition))))) {
      pushNextStrategy(frame, KWD_STRATEGIES_SCAN_FOR_VALUE_CLASH);
    }
  }
}

boolean tsppDsingleValuedStrategyP(ControlFrame* frame) {
  { Proposition* proposition = frame->proposition;

    return ((allArgumentsBoundP(proposition) ||
        allKeyArgumentsBoundP(proposition)) &&
        ((!oGENERATE_ALL_PROOFSpo) ||
         ((((boolean)(oQUERYITERATORo)) &&
        ((boolean)(oQUERYITERATORo->partialMatchStrategy))) &&
          isaP(oQUERYITERATORo->partialMatchStrategy, SGT_STRATEGIES_LOGIC_WHYNOT_PARTIAL_MATCH))));
  }
}

void tsppDhandleDefaultResult(ControlFrame* frame) {
  if ((frame->truthValue == DEFAULT_TRUE_TRUTH_VALUE) ||
      (frame->truthValue == DEFAULT_FALSE_TRUTH_VALUE)) {
    { Proposition* proposition = frame->proposition;
      Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)));
      Proposition* matchingprop = ((Proposition*)(iterator->value));

      { 
        BIND_STELLA_SPECIAL(oDONTUSEDEFAULTKNOWLEDGEpo, boolean, true);
        iterator = allMatchingPropositions(proposition);
        if (iterator->nextP()) {
          frame->truthValue = propositionsIteratorTruthValue(iterator);
          matchingprop = ((Proposition*)(iterator->value));
          ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)))->value = matchingprop;
        }
      }
    }
  }
}

void tsppDrecordResultJustification(ControlFrame* frame) {
  if (oRECORD_JUSTIFICATIONSpo) {
    { Proposition* proposition = frame->proposition;
      Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)));
      Proposition* matchingprop = ((Proposition*)(iterator->value));
      ForwardJustification* forwardjust = getOneSupportedForwardJustification(matchingprop);

      if (((boolean)(forwardjust))) {
        frame->justifications->push(forwardjust);
      }
      { Justification* implicitjust = createImplicitInferenceJustification(proposition, matchingprop);

        if (((boolean)(implicitjust))) {
          frame->justifications->push(implicitjust);
        }
      }
    }
  }
}

void tsppDpropagateResultTruthValue(ControlFrame* frame) {
  { Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)));
    TruthValue* truthvalue = frame->truthValue;
    Proposition* matchingprop = ((Proposition*)(iterator->value));
    PartialMatchFrame* pmf = frame->partialMatchFrame;

    if (((boolean)(pmf))) {
      { double score = pmf->computeAssertionScore(matchingprop, truthvalue);

        pmf->setFramePartialTruth(truthvalue, score, true);
      }
    }
  }
}

Keyword* tryScanPropositionsProof(ControlFrame* frame) {
  { Proposition* proposition = frame->proposition;
    boolean singlevaluedP = false;
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)));
    Keyword* result = KWD_STRATEGIES_FAILURE;

    if (!((boolean)(iterator))) {
      iterator = tsppDinitializeStrategy(frame);
      singlevaluedP = tsppDsingleValuedStrategyP(frame);
      tsppDspawnDerivedStrategies(frame, KWD_STRATEGIES_INITIALIZE);
    }
    if (((boolean)(iterator))) {
      while (iterator->nextP()) {
        if (relationAndArgumentsUnifyP(((Proposition*)(iterator->value)), proposition, true)) {
          if (singlevaluedP) {
            result = KWD_STRATEGIES_FINAL_SUCCESS;
            break;
          }
          else {
            result = KWD_STRATEGIES_CONTINUING_SUCCESS;
            break;
          }
        }
      }
    }
    if (result == KWD_STRATEGIES_FAILURE) {
      tsppDspawnDerivedStrategies(frame, KWD_STRATEGIES_FAILURE);
    }
    else if (!(result == KWD_STRATEGIES_FAILURE)) {
      frame->truthValue = propositionsIteratorTruthValue(iterator);
      if ((frame->truthValue == DEFAULT_TRUE_TRUTH_VALUE) ||
          (frame->truthValue == DEFAULT_FALSE_TRUTH_VALUE)) {
        tsppDhandleDefaultResult(frame);
      }
      if (oRECORD_JUSTIFICATIONSpo) {
        tsppDrecordResultJustification(frame);
      }
      tsppDpropagateResultTruthValue(frame);
    }
    return (result);
  }
}

boolean hasShallowDisproofP(ControlFrame* frame) {
  { Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)));
    Proposition* proposition = frame->proposition;
    TruthValue* truthvalue = frame->truthValue;
    boolean hasdisproofP = false;

    setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL, NULL);
    { 
      BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, !frame->reversePolarityP);
      frame->reversePolarityP = oREVERSEPOLARITYpo;
      setFrameTruthValue(frame, NULL);
      if ((((boolean)(oQUERYITERATORo)) &&
          ((boolean)(oQUERYITERATORo->partialMatchStrategy))) &&
          isaP(oQUERYITERATORo->partialMatchStrategy, SGT_STRATEGIES_LOGIC_WHYNOT_PARTIAL_MATCH)) {
        hasdisproofP = hasDisjointnessDisproofP(frame);
      }
      if (!hasdisproofP) {
        hasdisproofP = successResultP(tryScanPropositionsProof(frame));
      }
      if ((!hasdisproofP) &&
          (oREVERSEPOLARITYpo &&
           ((proposition->kind == KWD_STRATEGIES_FUNCTION) ||
            singleValuedPredicateP(proposition)))) {
        hasdisproofP = successResultP(tryScanForValueClashProof(frame));
      }
      frame->reversePolarityP = !frame->reversePolarityP;
      if (hasdisproofP &&
          (frame->reversePolarityP &&
           (!(frame->up->state == KWD_STRATEGIES_NOT)))) {
        frame->truthValue = invertTruthValue(frame->truthValue);
        { PartialMatchFrame* pmf = frame->partialMatchFrame;

          if (((boolean)(pmf))) {
            pmf->setFramePartialTruth(NULL, pmf->invertMatchScore(pmf->matchScore), true);
          }
        }
      }
    }
    if (!(hasdisproofP)) {
      frame->truthValue = truthvalue;
    }
    setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, iterator, NULL);
    return (hasdisproofP);
  }
}

boolean hasDisjointnessDisproofP(ControlFrame* frame) {
  { Proposition* proposition = frame->proposition;
    boolean hasdisproofP = false;

    if (proposition->kind == KWD_STRATEGIES_ISA) {
      if (!oREVERSEPOLARITYpo) {
        hasdisproofP = successResultP(tryIsaPropositionProof(frame));
      }
      else {
        { NamedDescription* queriedtype = getDescription(proposition->operatoR);
          Object* instance = argumentBoundTo((proposition->arguments->theArray)[0]);
          Cons* assertedtypes = NIL;

          if (((boolean)(instance))) {
            { 
              BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
              assertedtypes = allAssertedTypes(instance);
            }
            { Object* type = NULL;
              Cons* iter000 = assertedtypes;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                type = iter000->value;
                if (disjointTermsP(((Description*)(type)), queriedtype)) {
                  hasdisproofP = true;
                  setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
                  break;
                }
              }
            }
          }
        }
      }
    }
    return (hasdisproofP);
  }
}

Keyword* tryShallowDisproof(ControlFrame* frame) {
  { Proposition* proposition = frame->proposition;

    if (!allArgumentsBoundP(proposition)) {
      return (KWD_STRATEGIES_FAILURE);
    }
    else if (hasShallowDisproofP(frame)) {
      { boolean hasdefaultdisproofP = (frame->truthValue == DEFAULT_TRUE_TRUTH_VALUE) ||
            (frame->truthValue == DEFAULT_FALSE_TRUTH_VALUE);

        if (hasdefaultdisproofP) {
          setFrameTruthValue(frame, NULL);
        }
        return ((hasdefaultdisproofP ? KWD_STRATEGIES_FAILURE : KWD_STRATEGIES_TERMINAL_FAILURE));
      }
    }
    return (KWD_STRATEGIES_FAILURE);
  }
}

Keyword* tryScanForValueClashProof(ControlFrame* frame) {
  { 
    BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
    BIND_STELLA_SPECIAL(oDONTUSEDEFAULTKNOWLEDGEpo, boolean, oDONTUSEDEFAULTKNOWLEDGEpo);
    { Proposition* proposition = frame->proposition;
      Iterator* clashiterator = allClashingPropositions(proposition);
      TruthValue* truthvalue = (clashiterator->nextP() ? propositionsIteratorTruthValue(clashiterator) : ((TruthValue*)(NULL)));

      if ((truthvalue == DEFAULT_TRUE_TRUTH_VALUE) ||
          (truthvalue == DEFAULT_FALSE_TRUTH_VALUE)) {
        oDONTUSEDEFAULTKNOWLEDGEpo = true;
        clashiterator = allClashingPropositions(proposition);
        if (clashiterator->nextP()) {
          truthvalue = propositionsIteratorTruthValue(clashiterator);
        }
      }
      frame->truthValue = invertTruthValue(truthvalue);
      return ((((boolean)(truthvalue)) ? KWD_STRATEGIES_FINAL_SUCCESS : KWD_STRATEGIES_FAILURE));
    }
  }
}

Keyword* tryManufactureSkolemProof(ControlFrame* frame) {
  { Proposition* proposition = frame->proposition;
    NamedDescription* description = getDescription(((Surrogate*)(proposition->operatoR)));
    Cons* argumentvalues = NIL;

    if ((!testPropertyP(description, SGT_STRATEGIES_PL_KERNEL_KB_TOTAL)) ||
        frame->reversePolarityP) {
      return (KWD_STRATEGIES_FAILURE);
    }
    { Object* arg = NULL;
      Vector* vector000 = proposition->arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        argumentvalues = cons(argumentBoundTo(arg), argumentvalues);
      }
    }
    { boolean testValue000 = false;

      if (((boolean)(argumentvalues->value))) {
        testValue000 = true;
      }
      else {
        { boolean foundP000 = false;

          { Object* value = NULL;
            Cons* iter000 = argumentvalues->rest;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              value = iter000->value;
              if (!((boolean)(value))) {
                foundP000 = true;
                break;
              }
            }
          }
          testValue000 = foundP000;
        }
      }
      if (testValue000) {
        return (KWD_STRATEGIES_FAILURE);
      }
    }
    { Cons* inputvalues = argumentvalues->rest->reverse();
      Proposition* definingproposition = findOrCreateFunctionProposition(((Surrogate*)(proposition->operatoR)), inputvalues);

      bindVariableToValueP(((PatternVariable*)((proposition->arguments->theArray)[(proposition->arguments->length() - 1)])), (definingproposition->arguments->theArray)[(definingproposition->arguments->length() - 1)], true);
      return (KWD_STRATEGIES_FINAL_SUCCESS);
    }
  }
}

Proposition* extractSubgoalOfFrame(ControlFrame* frame) {
  while (!(frame->state == KWD_STRATEGIES_ATOMIC_GOAL)) {
    frame = frame->up;
  }
  return (frame->proposition);
}

Description* extractSubgoalDescriptionOfFrame(ControlFrame* frame) {
  if (((boolean)(((Description*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_DESCRIPTION, NULL)))))) {
    return (((Description*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_DESCRIPTION, NULL))));
  }
  while (!(frame->state == KWD_STRATEGIES_ATOMIC_GOAL)) {
    frame = frame->up;
  }
  return (getDescription(((Surrogate*)(frame->proposition->operatoR))));
}

Vector* findExternalArgumentsForSubgoal(ControlFrame* frame) {
  while (!(frame->state == KWD_STRATEGIES_ATOMIC_GOAL)) {
    frame = frame->up;
  }
  { Proposition* proposition = frame->proposition;
    Vector* externalarguments = frame->proposition->arguments;

    if ((proposition->operatoR == SGT_STRATEGIES_PL_KERNEL_KB_MEMBER_OF) &&
        (((boolean)(((Description*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_DESCRIPTION, NULL))))) &&
         ((((Description*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_DESCRIPTION, NULL)))->arity() > 1) &&
          isaP((proposition->arguments->theArray)[0], SGT_STRATEGIES_STELLA_LIST)))) {
      externalarguments = copyListToArgumentsVector(((List*)((proposition->arguments->theArray)[0])));
    }
    return (externalarguments);
  }
}

Keyword* trySubgoalStrategiesProof(ControlFrame* frame) {
  { Description* description = extractSubgoalDescriptionOfFrame(frame);
    boolean reversepolarityP = frame->reversePolarityP;
    Cons* strategies = NIL;

    { boolean chooseValue000 = false;

      if (reversepolarityP) {
        { boolean foundP000 = false;

          { ConsIterator* p = applicableRulesOfDescription(description, KWD_STRATEGIES_FORWARD, true)->allocateIterator();

            for (; p->nextP(); ) {
              foundP000 = true;
              break;
            }
          }
          chooseValue000 = foundP000;
        }
      }
      else {
        chooseValue000 = inferableP(description);
      }
      if (chooseValue000) {
        strategies = cons(KWD_STRATEGIES_ANTECEDENTS, strategies);
      }
    }
    if (reversepolarityP &&
        ((boolean)(getInferableComplementDescription(description)))) {
      strategies = cons(KWD_STRATEGIES_GOAL_COMPLEMENT, strategies);
    }
    { Proposition* proposition = frame->proposition;

      if (((boolean)(proposition)) &&
          (allArgumentsBoundP(proposition) &&
           ((boolean)(findMatchingConceivedProposition(proposition))))) {
        strategies = cons(KWD_STRATEGIES_FORWARD_GOALS, strategies);
      }
    }
    { Object* s = NULL;
      Cons* iter000 = strategies->reverse();

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        s = iter000->value;
        pushNextStrategy(frame, ((Keyword*)(s)));
      }
    }
    return (KWD_STRATEGIES_FAILURE);
  }
}

void establishGoalCache(ControlFrame* frame) {
  { ControlFrame* goalframe = NULL;
    ControlFrame* restartframe = NULL;
    int restartdepth = NULL_INTEGER;

    goalframe = findDuplicatedGoal(frame, restartframe, restartdepth);
    {
      restartframe = restartframe;
      restartdepth = restartdepth;
    }
    if (((boolean)(goalframe)) &&
        (!((boolean)(findGoalCache(goalframe))))) {
      createGoalCacheP(goalframe);
    }
  }
}

boolean checkForDuplicateRuleP(ControlFrame* frame, Proposition* impliesproposition) {
  if (!(oDUPLICATE_SUBGOAL_STRATEGYo == KWD_STRATEGIES_DUPLICATE_)) {
    return (false);
  }
  { ControlFrame* previousframe = frame->up;
    Cons* goalbindings = yieldGoalBindings(frame->proposition);

    { int i = NULL_INTEGER;
      int iter000 = 1;
      int upperBound000 = oDUPLICATE_RULE_SEARCH_DEPTHo;
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter000 <= upperBound000); 
            iter000 = iter000 + 1) {
        i = iter000;
        i = i;
        if (!((boolean)(previousframe))) {
          return (false);
        }
        { boolean testValue000 = false;

          testValue000 = ((Proposition*)(dynamicSlotValue(previousframe->dynamicSlots, SYM_STRATEGIES_LOGIC_ANTECEDENTS_RULE, NULL))) == impliesproposition;
          if (testValue000) {
            { boolean alwaysP000 = true;

              { Object* b1 = NULL;
                Cons* iter001 = goalbindings;
                Object* b2 = NULL;
                Cons* iter002 = yieldGoalBindings(previousframe->proposition);

                for  (; (!(iter001 == NIL)) &&
                          (!(iter002 == NIL)); 
                      iter001 = iter001->rest,
                      iter002 = iter002->rest) {
                  b1 = iter001->value;
                  b2 = iter002->value;
                  if (!eqlP(b1, b2)) {
                    alwaysP000 = false;
                    break;
                  }
                }
              }
              testValue000 = alwaysP000;
            }
            if (testValue000) {
              testValue000 = frame->reversePolarityP == previousframe->reversePolarityP;
            }
          }
          if (testValue000) {
            if (((boolean)(oTRACED_KEYWORDSo)) &&
                oTRACED_KEYWORDSo->membP(KWD_STRATEGIES_GOAL_CACHES)) {
              std::cout << "DUPLICATE RULE.  BINDINGS: " << goalbindings << std::endl;
            }
            if (false) {
              establishGoalCache(frame);
            }
            return (true);
          }
        }
        previousframe = previousframe->up;
      }
    }
  }
  return (false);
}

Keyword* continueAntecedentsProof(ControlFrame* frame, Keyword* lastmove) {
  { Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)));
    boolean firsttimeP = !((boolean)(iterator));
    boolean reversepolarityP = frame->reversePolarityP;

    if (lastmove == KWD_STRATEGIES_UP_TRUE) {
      { Proposition* object000 = ((Proposition*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_ANTECEDENTS_RULE, NULL)));
        Object* oldValue000 = object000->truthValue;

        frame->truthValue = weakenTruthValue(propagateFrameTruthValue(frame->result, frame), ((TruthValue*)(accessInContext(oldValue000, object000->homeContext, false))));
      }
      if (oRECORD_JUSTIFICATIONSpo) {
        recordModusPonensJustification(frame, lastmove);
      }
      return (KWD_STRATEGIES_CONTINUING_SUCCESS);
    }
    else {
    }
    if (firsttimeP) {
      iterator = allocateAntecedentsIterator(extractSubgoalDescriptionOfFrame(frame), findExternalArgumentsForSubgoal(frame), reversepolarityP);
      if (!((boolean)(iterator))) {
        return (KWD_STRATEGIES_FAILURE);
      }
      setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, iterator, NULL);
    }
    while (iterator->nextP()) {
      { Proposition* impliesproposition = ((Proposition*)(iterator->value));
        Description* antecedentdescription = (reversepolarityP ? ((Description*)((impliesproposition->arguments->theArray)[1])) : ((Description*)((impliesproposition->arguments->theArray)[0])));

        if (checkForDuplicateRuleP(frame, impliesproposition)) {
          continue;
        }
        setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_ANTECEDENTS_RULE, impliesproposition, NULL);
        if (!trueP(impliesproposition)) {
          if (getForwardGoals(impliesproposition)->emptyP()) {
            continue;
          }
          else {
            {
              createConditionalAntecedentSubframe(frame, frame->proposition, impliesproposition);
              return (KWD_STRATEGIES_MOVE_DOWN);
            }
          }
        }
        { ControlFrame* downframe = createSubgoalFrame(frame, NULL, KWD_STRATEGIES_FULL_SUBQUERY);

          setDynamicSlotValue(downframe->dynamicSlots, SYM_STRATEGIES_LOGIC_DESCRIPTION, antecedentdescription, NULL);
          return (KWD_STRATEGIES_MOVE_DOWN);
        }
      }
    }
    return (KWD_STRATEGIES_FAILURE);
  }
}

Iterator* allocateAntecedentsIterator(Description* goaldescription, Vector* externalarguments, boolean reversepolarityP) {
  { Cons* antecedents = NIL;
    LogicObject* antecedent = NULL;
    boolean incompatibleargumentsP = false;

    { Proposition* prop = NULL;
      Cons* iter000 = applicableRulesOfDescription(goaldescription, (reversepolarityP ? KWD_STRATEGIES_FORWARD : KWD_STRATEGIES_BACKWARD), false);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        prop = ((Proposition*)(iter000->value));
        if (((reversepolarityP ? (!((BooleanWrapper*)(dynamicSlotValue(prop->dynamicSlots, SYM_STRATEGIES_LOGIC_BACKWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue) : (!((BooleanWrapper*)(dynamicSlotValue(prop->dynamicSlots, SYM_STRATEGIES_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue))) &&
            ((!reversepolarityP) ||
             (atomicGoalDescriptionP(((Description*)((prop->arguments->theArray)[1]))) ||
              closedTermP((prop->arguments->theArray)[1])))) {
          antecedent = (reversepolarityP ? ((LogicObject*)((prop->arguments->theArray)[1])) : ((LogicObject*)((prop->arguments->theArray)[0])));
          if ((!isaP(antecedent, SGT_STRATEGIES_LOGIC_DESCRIPTION)) ||
              (!(externalarguments->length() == ((Description*)(antecedent))->ioVariables->length()))) {
            continue;
          }
          incompatibleargumentsP = false;
          { PatternVariable* v = NULL;
            Vector* vector000 = ((Description*)(antecedent))->ioVariables;
            int index000 = 0;
            int length000 = vector000->length();
            Object* arg = NULL;
            Vector* vector001 = externalarguments;
            int index001 = 0;
            int length001 = vector001->length();

            for  (; (index000 < length000) &&
                      (index001 < length001); 
                  index000 = index000 + 1,
                  index001 = index001 + 1) {
              v = ((PatternVariable*)((vector000->theArray)[index000]));
              arg = (vector001->theArray)[index001];
              { Object* argvalue = argumentBoundTo(arg);
                Object* varvalue = groundValueOf(v);

                if (((boolean)(argvalue)) &&
                    ((((boolean)(varvalue)) &&
                    (!eqlP(argvalue, varvalue))) ||
                     ((!((boolean)(varvalue))) &&
                      failsAntecedentTypeCheckP(v, argvalue)))) {
                  incompatibleargumentsP = true;
                  break;
                }
              }
            }
          }
          if (!incompatibleargumentsP) {
            antecedents = cons(prop, antecedents);
          }
        }
      }
    }
    if (antecedents == NIL) {
      return (NULL);
    }
    else {
      return (optimizeOrderOfApplicableRules(antecedents, !reversepolarityP)->allocateIterator());
    }
  }
}

Cons* optimizeOrderOfApplicableRules(Cons* rules, boolean tailP) {
  { Cons* cursor = rules;
    Cons* result = NIL;
    Description* antecedent = NULL;
    int antecedentindex = (tailP ? 0 : 1);

    if (rules->rest == NIL) {
      return (rules);
    }
    { int i = NULL_INTEGER;
      int iter000 = 0;

      for (; true; iter000 = iter000 + 1) {
        i = iter000;
        while (!(cursor == NIL)) {
          antecedent = ((Description*)((((Proposition*)(cursor->value))->arguments->theArray)[antecedentindex]));
          if (antecedent->internalVariables->length() == i) {
            result = cons(((Proposition*)(cursor->value)), result);
            cursor->value = NULL;
          }
          cursor = cursor->rest;
        }
        cursor = rules->remove(NULL);
        if (cursor == NIL) {
          break;
        }
      }
    }
    return (result->reverse());
  }
}

boolean hasMoreAntecedentsP(ControlFrame* frame) {
  { Keyword* strategy = frame->currentStrategy;
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)));

    return (((boolean)(iterator)) &&
        (((strategy == KWD_STRATEGIES_ANTECEDENTS) ||
        (strategy == KWD_STRATEGIES_FULL_SUBQUERY)) &&
         (isaP(iterator, SGT_STRATEGIES_STELLA_CONS_ITERATOR) &&
          (!iterator->emptyP()))));
  }
}

Keyword* tryGoalComplementProof(ControlFrame* frame) {
  { Description* description = extractSubgoalDescriptionOfFrame(frame);
    Description* complement = getInferableComplementDescription(description);
    ControlFrame* downframe = createSubgoalFrame(frame, NULL, KWD_STRATEGIES_ALL_SUBGOAL_STRATEGIES);

    setDynamicSlotValue(downframe->dynamicSlots, SYM_STRATEGIES_LOGIC_DESCRIPTION, complement, NULL);
    downframe->reversePolarityP = false;
    return (KWD_STRATEGIES_MOVE_DOWN);
  }
}

Keyword* tryForwardGoalsProof(ControlFrame* frame) {
  { Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)));

    if (!((boolean)(iterator))) {
      { Proposition* baseproposition = findMatchingConceivedProposition(frame->proposition);
        List* forwardgoals = NULL;

        if (!((boolean)(baseproposition))) {
          return (KWD_STRATEGIES_FAILURE);
        }
        forwardgoals = getForwardGoals(baseproposition);
        if (forwardgoals->emptyP()) {
          return (KWD_STRATEGIES_FAILURE);
        }
        else if ((forwardgoals->rest() == NIL) &&
            trueP(((ForwardGoalRecord*)(forwardgoals->first()))->forwardRule)) {
          createSubgoalFrame(frame, ((ForwardGoalRecord*)(forwardgoals->first()))->forwardGoal, NULL);
          return (KWD_STRATEGIES_MOVE_DOWN);
        }
        else {
          iterator = ((ListIterator*)(forwardgoals->allocateIterator()));
          setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, iterator, NULL);
        }
      }
    }
    else {
      iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)));
    }
    if (iterator->nextP()) {
      { ForwardGoalRecord* fwdgoalrec = ((ForwardGoalRecord*)(iterator->value));

        if (trueP(fwdgoalrec->forwardRule)) {
          createSubgoalFrame(frame, fwdgoalrec->forwardGoal, NULL);
        }
        else {
          createConditionalAntecedentSubframe(frame, fwdgoalrec->forwardGoal, fwdgoalrec->forwardRule);
        }
        return (KWD_STRATEGIES_MOVE_DOWN);
      }
    }
    return (KWD_STRATEGIES_FAILURE);
  }
}

ConditionalAntecedentProofAdjunct* newConditionalAntecedentProofAdjunct() {
  { ConditionalAntecedentProofAdjunct* self = NULL;

    self = new ConditionalAntecedentProofAdjunct();
    self->phase = KWD_STRATEGIES_FORWARD_RULE;
    self->goal = NULL;
    self->provableRule = NULL;
    return (self);
  }
}

Surrogate* ConditionalAntecedentProofAdjunct::primaryType() {
  { ConditionalAntecedentProofAdjunct* self = this;

    return (SGT_STRATEGIES_LOGIC_CONDITIONAL_ANTECEDENT_PROOF_ADJUNCT);
  }
}

Object* accessConditionalAntecedentProofAdjunctSlotValue(ConditionalAntecedentProofAdjunct* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_STRATEGIES_LOGIC_PROVABLE_RULE) {
    if (setvalueP) {
      self->provableRule = ((Proposition*)(value));
    }
    else {
      value = self->provableRule;
    }
  }
  else if (slotname == SYM_STRATEGIES_LOGIC_GOAL) {
    if (setvalueP) {
      self->goal = ((Proposition*)(value));
    }
    else {
      value = self->goal;
    }
  }
  else if (slotname == SYM_STRATEGIES_STELLA_PHASE) {
    if (setvalueP) {
      self->phase = ((Keyword*)(value));
    }
    else {
      value = self->phase;
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

ControlFrame* createConditionalAntecedentSubframe(ControlFrame* frame, Proposition* goal, Proposition* provablerule) {
  { ControlFrame* downframe = createSubgoalFrame(frame, goal, KWD_STRATEGIES_CONDITIONAL_ANTECEDENT);
    ConditionalAntecedentProofAdjunct* proofadjunct = newConditionalAntecedentProofAdjunct();

    setDynamicSlotValue(downframe->dynamicSlots, SYM_STRATEGIES_LOGIC_PROOF_ADJUNCT, proofadjunct, NULL);
    proofadjunct->provableRule = provablerule;
    proofadjunct->goal = goal;
    return (downframe);
  }
}

Keyword* continueConditionalAntecedentProof(ControlFrame* frame, Keyword* lastmove) {
  { ConditionalAntecedentProofAdjunct* proofadjunct = ((ConditionalAntecedentProofAdjunct*)(((ProofAdjunct*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_PROOF_ADJUNCT, NULL)))));
    Proposition* provablerule = proofadjunct->provableRule;

    if (lastmove == KWD_STRATEGIES_DOWN) {
      createSubgoalFrame(frame, provablerule, KWD_STRATEGIES_FORWARD_GOALS);
      return (KWD_STRATEGIES_MOVE_DOWN);
    }
    else if (lastmove == KWD_STRATEGIES_UP_TRUE) {
      if (proofadjunct->phase == KWD_STRATEGIES_ORIGINAL_GOAL) {
        frame->truthValue = weakenTruthValue(propagateFrameTruthValue(frame->result, frame), ((TruthValue*)(accessInContext(provablerule->truthValue, provablerule->homeContext, false))));
        return (selectProofResult(true, ((boolean)(frame->down)), false));
      }
      assignTruthValue(provablerule, frame->result->truthValue);
      { ControlFrame* downframe = createSubgoalFrame(frame, frame->proposition, KWD_STRATEGIES_ANTECEDENTS);

        setDynamicSlotValue(downframe->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, consList(1, provablerule)->allocateIterator(), NULL);
        proofadjunct->phase = KWD_STRATEGIES_ORIGINAL_GOAL;
        return (KWD_STRATEGIES_MOVE_DOWN);
      }
    }
    else if (lastmove == KWD_STRATEGIES_UP_FAIL) {
      propagateFrameTruthValue(frame->result, frame);
      return (KWD_STRATEGIES_FAILURE);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Keyword* tryFullSubqueryProof(ControlFrame* frame) {
  { Description* description = ((Description*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_DESCRIPTION, NULL)));
    Vector* externalarguments = findExternalArgumentsForSubgoal(frame);

    if (overlayWithPatternFrameP(frame, description, externalarguments)) {
      return (KWD_STRATEGIES_MOVE_IN_PLACE);
    }
    if ((!((boolean)(frame->partialMatchFrame))) &&
        (((boolean)(oQUERYITERATORo)) &&
         ((boolean)(oQUERYITERATORo->partialMatchStrategy)))) {
      createAndLinkPartialMatchFrame(frame, KWD_STRATEGIES_ATOMIC_GOAL);
    }
    return (KWD_STRATEGIES_FAILURE);
  }
}

Description* extractCollectionArgument(Proposition* proposition) {
  if (proposition->kind == KWD_STRATEGIES_ISA) {
    return (getDescription(((Surrogate*)(proposition->operatoR))));
  }
  else {
    return (((Description*)(argumentBoundTo((proposition->arguments->theArray)[1]))));
  }
}

Keyword* tryIsaPropositionProof(ControlFrame* frame) {
  { Proposition* proposition = frame->proposition;
    Surrogate* surrogate = ((Surrogate*)(proposition->operatoR));
    Vector* arguments = proposition->arguments;
    Object* memberarg = (arguments->theArray)[0];
    Object* member = argumentBoundTo(memberarg);
    boolean scanisapropositionsP = (oGENERATE_ALL_PROOFSpo ||
        (oREVERSEPOLARITYpo ||
         oRECORD_JUSTIFICATIONSpo)) &&
        (!(surrogate == SGT_STRATEGIES_STELLA_THING));

    if (oCYC_KLUDGES_ENABLEDpo) {
      if (!(oREVERSEPOLARITYpo)) {
        scanisapropositionsP = false;
      }
    }
    if (!((boolean)(member))) {
      return (tryScanCollectionProof(frame));
    }
    if (isaP(member, SGT_STRATEGIES_STELLA_LITERAL_WRAPPER) ||
        ((surrogate == SGT_STRATEGIES_LOGIC_PROPOSITION) ||
         descriptionP(member))) {
      { boolean successP = logicalSubtypeOfP(logicalType(member), surrogate);

        if (oREVERSEPOLARITYpo) {
          successP = !successP;
        }
        if (successP) {
          return (KWD_STRATEGIES_FINAL_SUCCESS);
        }
        if (!(instanceHasBacklinksP(member))) {
          return (KWD_STRATEGIES_FAILURE);
        }
      }
    }
    if (scanisapropositionsP) {
      return (tryScanPropositionsProof(frame));
    }
    { Description* collection = extractCollectionArgument(proposition);

      if (testIsaP(member, collection->surrogateValueInverse)) {
        return (KWD_STRATEGIES_FINAL_SUCCESS);
      }
      else {
        return (KWD_STRATEGIES_FAILURE);
      }
    }
  }
}

Keyword* tryScanCollectionProof(ControlFrame* frame) {
  { Proposition* proposition = frame->proposition;
    Vector* arguments = proposition->arguments;
    Object* memberarg = (arguments->theArray)[0];
    AssertedCollectionMembersIterator* iterator = ((AssertedCollectionMembersIterator*)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, NULL)))));

    if (!((boolean)(iterator))) {
      { Description* collection = extractCollectionArgument(proposition);

        iterator = allAssertedCollectionMembers(collection, inferableP(collection));
        setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_STELLA_ITERATOR, iterator, NULL);
      }
    }
    while (iterator->nextP()) {
      if (bindVariableToValueP(((PatternVariable*)(memberarg)), valueOf(iterator->value), true)) {
        if (oRECORD_JUSTIFICATIONSpo) {
          { Proposition* matchingprop = iterator->proposition;
            ForwardJustification* forwardjust = getOneSupportedForwardJustification(matchingprop);
            Justification* implicitjust = createImplicitInferenceJustification(proposition, matchingprop);

            if (((boolean)(forwardjust))) {
              frame->justifications->push(forwardjust);
            }
            if (((boolean)(implicitjust))) {
              frame->justifications->push(implicitjust);
            }
          }
        }
        return (KWD_STRATEGIES_CONTINUING_SUCCESS);
      }
    }
    return (KWD_STRATEGIES_FAILURE);
  }
}

boolean inferableDescriptionP(Object* self) {
  if (!((boolean)(self))) {
    return (false);
  }
  if (subtypeOfP(safePrimaryType(self), SGT_STRATEGIES_LOGIC_DESCRIPTION)) {
    { Object* self000 = self;
      Description* self = ((Description*)(self000));

      if (oREVERSEPOLARITYpo &&
          ((boolean)(getInferableComplementDescription(self)))) {
        self = ((Description*)(dynamicSlotValue(self->dynamicSlots, SYM_STRATEGIES_LOGIC_COMPLEMENT_DESCRIPTION, NULL)));
      }
      return (inferableP(self));
    }
  }
  else {
    return (false);
  }
}

Keyword* tryImpliesProof(ControlFrame* frame) {
  { Proposition* proposition = frame->proposition;
    Object* subcollectionarg = (proposition->arguments->theArray)[0];
    Object* supercollectionarg = (proposition->arguments->theArray)[1];
    Object* subcollection = argumentBoundTo(subcollectionarg);
    Object* supercollection = argumentBoundTo(supercollectionarg);

    if ((!((boolean)(subcollection))) ||
        (!((boolean)(supercollection)))) {
      return (KWD_STRATEGIES_FAILURE);
    }
    if ((!inferableDescriptionP(subcollection)) &&
        ((!inferableDescriptionP(supercollection)) &&
         (closedTermP(subcollection) ||
          frame->reversePolarityP))) {
      { Keyword* testValue000 = trySimpleContainedByProof(subcollection, supercollection, frame->reversePolarityP);

        if (testValue000 == KWD_STRATEGIES_FINAL_SUCCESS) {
          setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
          return (KWD_STRATEGIES_FINAL_SUCCESS);
        }
        else if (testValue000 == KWD_STRATEGIES_TERMINAL_FAILURE) {
          setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
          return (KWD_STRATEGIES_TERMINAL_FAILURE);
        }
        else {
        }
      }
    }
    if (isaP(subcollection, SGT_STRATEGIES_LOGIC_DESCRIPTION) &&
        isaP(supercollection, SGT_STRATEGIES_LOGIC_DESCRIPTION)) {
      pushNextStrategy(frame, KWD_STRATEGIES_SUBSUMPTION_TEST);
    }
    if (closedTermP(subcollection)) {
      pushNextStrategy(frame, KWD_STRATEGIES_CONTAINED_BY);
    }
    return (KWD_STRATEGIES_FAILURE);
  }
}

Keyword* trySimpleContainedByProof(Object* subcollection, Object* supercollection, boolean reversepolarityP) {
  { 
    BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
    { List* members = assertedCollectionMembers(subcollection, false);

      oREVERSEPOLARITYpo = reversepolarityP;
      if (((boolean)(members))) {
        if (reversepolarityP) {
          { boolean foundP000 = false;

            { Object* m = NULL;
              Cons* iter000 = members->theConsList;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                m = iter000->value;
                if (memberOfCollectionP(valueOf(m), supercollection)) {
                  foundP000 = true;
                  break;
                }
              }
            }
            if (foundP000) {
              return (KWD_STRATEGIES_FINAL_SUCCESS);
            }
            else {
              if (closedTermP(supercollection)) {
                return (KWD_STRATEGIES_TERMINAL_FAILURE);
              }
            }
          }
        }
        else {
          { boolean alwaysP000 = true;

            { Object* m = NULL;
              Cons* iter001 = members->theConsList;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                m = iter001->value;
                if (!memberOfCollectionP(valueOf(m), supercollection)) {
                  alwaysP000 = false;
                  break;
                }
              }
            }
            if (alwaysP000) {
              return (KWD_STRATEGIES_FINAL_SUCCESS);
            }
            else {
              if (closedTermP(supercollection)) {
                return (KWD_STRATEGIES_TERMINAL_FAILURE);
              }
            }
          }
        }
      }
      return (KWD_STRATEGIES_FAILURE);
    }
  }
}

Keyword* tryContainedByProof(ControlFrame* upframe) {
  { Proposition* upproposition = upframe->proposition;
    Object* subcollection = argumentBoundTo((upproposition->arguments->theArray)[0]);
    Object* supercollection = argumentBoundTo((upproposition->arguments->theArray)[1]);
    Proposition* containedbyprop = createProposition(SYM_STRATEGIES_LOGIC_CONTAINED_BY, 2);
    Description* description = (isaP(subcollection, SGT_STRATEGIES_LOGIC_DESCRIPTION) ? ((Description*)(subcollection)) : ((Description*)(supercollection)));
    int arity = description->arity();
    List* bridgearguments = newList();
    ControlFrame* containedbyframe = createDownFrame(upframe, containedbyprop);

    if (upframe->reversePolarityP) {
      return (KWD_STRATEGIES_FAILURE);
    }
    { int i = NULL_INTEGER;
      int iter000 = 0;
      PatternVariable* vbl = NULL;
      Vector* vector000 = description->ioVariables;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            iter000 = iter000 + 1,
            index000 = index000 + 1) {
        i = iter000;
        vbl = ((PatternVariable*)((vector000->theArray)[index000]));
        { PatternVariable* bridgevbl = newPatternVariable();

          bridgevbl->boundToOffset = i;
          bridgevbl->skolemName = vbl->skolemName;
          bridgevbl->skolemType = vbl->skolemType;
          bridgearguments->insertLast(bridgevbl);
        }
      }
    }
    containedbyframe->state = KWD_STRATEGIES_CONTAINED_BY;
    containedbyframe->proposition = containedbyprop;
    (containedbyprop->arguments->theArray)[0] = (createContainedByArgument(subcollection, bridgearguments));
    (containedbyprop->arguments->theArray)[1] = (createContainedByArgument(supercollection, bridgearguments));
    createPatternRecord(containedbyframe, NULL, NULL);
    activatePatternRecord(containedbyframe->patternRecord, arity);
    return (KWD_STRATEGIES_MOVE_DOWN);
  }
}

Proposition* createContainedByArgument(Object* collection, List* bridgeargs) {
  { Proposition* proposition = NULL;
    Object* thecollection = collection;
    int arity = 1;

    { Surrogate* testValue000 = safePrimaryType(collection);

      if (subtypeOfP(testValue000, SGT_STRATEGIES_LOGIC_NAMED_DESCRIPTION)) {
        { Object* collection000 = collection;
          NamedDescription* collection = ((NamedDescription*)(collection000));

          if (classP(collection)) {
            proposition = createProposition(SYM_STRATEGIES_STELLA_ISA, 1);
            proposition->operatoR = collection->surrogateValueInverse;
            (proposition->arguments->theArray)[0] = (bridgeargs->first());
            return (proposition);
          }
          else {
            proposition = createProposition(SYM_STRATEGIES_STELLA_PREDICATE, collection->arity());
            proposition->operatoR = collection->surrogateValueInverse;
            { Object* arg = NULL;
              Cons* iter000 = bridgeargs->theConsList;
              int i = NULL_INTEGER;
              int iter001 = 0;

              for  (; !(iter000 == NIL); 
                    iter000 = iter000->rest,
                    iter001 = iter001 + 1) {
                arg = iter000->value;
                i = iter001;
                (proposition->arguments->theArray)[i] = arg;
              }
            }
            return (proposition);
          }
        }
      }
      else if (subtypeOfP(testValue000, SGT_STRATEGIES_LOGIC_DESCRIPTION)) {
        { Object* collection001 = collection;
          Description* collection = ((Description*)(collection001));

          arity = collection->arity();
          thecollection = instantiateExternalBindings(collection);
        }
      }
      else {
      }
    }
    proposition = createProposition(SYM_STRATEGIES_STELLA_PREDICATE, 2);
    proposition->operatoR = SGT_STRATEGIES_PL_KERNEL_KB_MEMBER_OF;
    (proposition->arguments->theArray)[0] = (((arity > 1) ? bridgeargs : bridgeargs->first()));
    (proposition->arguments->theArray)[1] = thecollection;
    return (proposition);
  }
}

Keyword* continueContainedByProof(ControlFrame* frame, Keyword* lastmove) {
  if (lastmove == KWD_STRATEGIES_DOWN) {
    if (frame->state == KWD_STRATEGIES_CONTAINED_BY) {
      resetCurrentPatternRecord(frame, KWD_STRATEGIES_LOCAL);
    }
    createDownFrame(frame, ((Proposition*)((frame->proposition->arguments->theArray)[0])));
    setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_BACK, frame->down, NULL);
    return (KWD_STRATEGIES_MOVE_DOWN);
  }
  else if (lastmove == KWD_STRATEGIES_UP_TRUE) {
    switch (frame->argumentCursor) {
      case 0: 
        frame->down = NULL;
        frame->argumentCursor = 1;
        return (KWD_STRATEGIES_MOVE_DOWN);
      case 1: 
        if (((boolean)(frame->down))) {
          popFramesUpTo(frame->down);
        }
        if (((ControlFrame*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_BACK, NULL)))->state == KWD_STRATEGIES_POPPED) {
          {
            setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
            return (KWD_STRATEGIES_FINAL_SUCCESS);
          }
        }
        else {
          {
            frame->down = ((ControlFrame*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_BACK, NULL)));
            frame->argumentCursor = 0;
            return (KWD_STRATEGIES_MOVE_DOWN);
          }
        }
        break;
      default:
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << frame->argumentCursor << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
        break;
    }
  }
  else if (lastmove == KWD_STRATEGIES_UP_FAIL) {
    switch (frame->argumentCursor) {
      case 0: 
        setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
        return (KWD_STRATEGIES_FINAL_SUCCESS);
      case 1: 
        { ControlFrame* parent = frame->up;
          Proposition* parentgoal = parent->proposition;

          if ((parentgoal->kind == KWD_STRATEGIES_IMPLIES) &&
              closedTermP((parentgoal->arguments->theArray)[1])) {
            setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
            parent->nextStrategies = NIL;
          }
          if (!(((ControlFrame*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_BACK, NULL)))->state == KWD_STRATEGIES_POPPED)) {
            popFramesUpTo(((ControlFrame*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_BACK, NULL))));
          }
          return (KWD_STRATEGIES_FAILURE);
        }
        break;
      default:
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "`" << frame->argumentCursor << "'" << " is not a valid case option";
          throw *newStellaException(stream001->theStringReader());
        }
        break;
    }
  }
  else {
    { OutputStringStream* stream002 = newOutputStringStream();

      *(stream002->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
      throw *newStellaException(stream002->theStringReader());
    }
  }
}

Keyword* trySubsumptionTest(ControlFrame* frame) {
  { Proposition* proposition = frame->proposition;
    Object* subcollectionarg = (proposition->arguments->theArray)[0];
    Object* supercollectionarg = (proposition->arguments->theArray)[1];
    Description* subcollection = ((Description*)(argumentBoundTo(subcollectionarg)));
    Description* supercollection = ((Description*)(argumentBoundTo(supercollectionarg)));

    if (frame->reversePolarityP) {
      return (KWD_STRATEGIES_FAILURE);
    }
    if (((boolean)(subcollection)) &&
        ((boolean)(((Vector*)(dynamicSlotValue(subcollection->dynamicSlots, SYM_STRATEGIES_LOGIC_EXTERNAL_VARIABLES, NULL)))))) {
      { boolean foundP000 = false;

        { PatternVariable* var = NULL;
          Vector* vector000 = ((Vector*)(dynamicSlotValue(subcollection->dynamicSlots, SYM_STRATEGIES_LOGIC_EXTERNAL_VARIABLES, NULL)));
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            var = ((PatternVariable*)((vector000->theArray)[index000]));
            if (!argumentBoundP(var)) {
              foundP000 = true;
              break;
            }
          }
        }
        if (foundP000) {
          return (KWD_STRATEGIES_FAILURE);
        }
        else {
          subcollection = ((Description*)(instantiateExternalBindings(subcollection)));
        }
      }
    }
    if (((boolean)(supercollection)) &&
        ((boolean)(((Vector*)(dynamicSlotValue(supercollection->dynamicSlots, SYM_STRATEGIES_LOGIC_EXTERNAL_VARIABLES, NULL)))))) {
      { boolean foundP001 = false;

        { PatternVariable* var = NULL;
          Vector* vector001 = ((Vector*)(dynamicSlotValue(supercollection->dynamicSlots, SYM_STRATEGIES_LOGIC_EXTERNAL_VARIABLES, NULL)));
          int index001 = 0;
          int length001 = vector001->length();

          for  (; index001 < length001; 
                index001 = index001 + 1) {
            var = ((PatternVariable*)((vector001->theArray)[index001]));
            if (!argumentBoundP(var)) {
              foundP001 = true;
              break;
            }
          }
        }
        if (foundP001) {
          return (KWD_STRATEGIES_FAILURE);
        }
        else {
          supercollection = ((Description*)(instantiateExternalBindings(supercollection)));
        }
      }
    }
    { TruthValue* truthvalue = descriptionSpecializesDescriptionP(subcollection, supercollection);

      setFrameTruthValue(frame, truthvalue);
      if ((truthvalue == TRUE_TRUTH_VALUE) ||
          (truthvalue == DEFAULT_TRUE_TRUTH_VALUE)) {
        return (KWD_STRATEGIES_FINAL_SUCCESS);
      }
      else {
        return (KWD_STRATEGIES_FAILURE);
      }
    }
  }
}

Keyword* tryEquivalenceProof(ControlFrame* frame) {
  { Vector* arguments = frame->proposition->arguments;
    Object* firstarg = (arguments->theArray)[0];
    Object* firstvalue = argumentBoundTo(firstarg);
    Object* secondarg = (arguments->theArray)[1];
    Object* secondvalue = argumentBoundTo(secondarg);
    boolean successP = false;

    if (frame->reversePolarityP) {
      if ((!((boolean)(firstvalue))) ||
          (!((boolean)(secondvalue)))) {
        return (KWD_STRATEGIES_FAILURE);
      }
      else if (skolemP(firstvalue) ||
          skolemP(secondvalue)) {
        return (KWD_STRATEGIES_FAILURE);
      }
      else if (eqlP(firstvalue, secondvalue)) {
        setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
        return (KWD_STRATEGIES_TERMINAL_FAILURE);
      }
      else {
        setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
        return (KWD_STRATEGIES_FINAL_SUCCESS);
      }
    }
    if (((boolean)(firstvalue))) {
      if (((boolean)(secondvalue))) {
        successP = eqlP(firstvalue, secondvalue);
      }
      else {
        successP = bindVariableToValueP(((PatternVariable*)(secondarg)), firstvalue, true);
      }
    }
    else {
      if (((boolean)(secondvalue))) {
        successP = bindVariableToValueP(((PatternVariable*)(firstarg)), secondvalue, true);
      }
      else {
        successP = false;
      }
    }
    return ((successP ? KWD_STRATEGIES_FINAL_SUCCESS : KWD_STRATEGIES_FAILURE));
  }
}

ClusteredConjunctionProofAdjunct* newClusteredConjunctionProofAdjunct() {
  { ClusteredConjunctionProofAdjunct* self = NULL;

    self = new ClusteredConjunctionProofAdjunct();
    self->clusterFrames = NULL;
    return (self);
  }
}

Surrogate* ClusteredConjunctionProofAdjunct::primaryType() {
  { ClusteredConjunctionProofAdjunct* self = this;

    return (SGT_STRATEGIES_LOGIC_CLUSTERED_CONJUNCTION_PROOF_ADJUNCT);
  }
}

Object* accessClusteredConjunctionProofAdjunctSlotValue(ClusteredConjunctionProofAdjunct* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_STRATEGIES_LOGIC_CLUSTER_FRAMES) {
    if (setvalueP) {
      self->clusterFrames = ((Vector*)(value));
    }
    else {
      value = self->clusterFrames;
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

Keyword* continueClusteredConjunctionProof(ControlFrame* andframe, Keyword* lastmove) {
  { Keyword* state = andframe->state;
    ClusteredConjunctionProofAdjunct* adjunct = ((ClusteredConjunctionProofAdjunct*)(((ProofAdjunct*)(dynamicSlotValue(andframe->dynamicSlots, SYM_STRATEGIES_LOGIC_PROOF_ADJUNCT, NULL)))));
    Proposition* proposition = andframe->proposition;
    Vector* arguments = proposition->arguments;
    int nofarguments = arguments->length();
    ControlFrame* downframe = NULL;

    if (((boolean)(oQUERYITERATORo)) &&
        ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
      andframe->state = KWD_STRATEGIES_AND;
      lastmove = oldInterpretAndScores(andframe, lastmove);
      andframe->state = state;
    }
    if (lastmove == KWD_STRATEGIES_DOWN) {
      if (!((boolean)(adjunct))) {
        { ClusteredConjunctionProofAdjunct* self000 = newClusteredConjunctionProofAdjunct();

          self000->clusterFrames = stella::newVector(nofarguments);
          adjunct = self000;
        }
        setDynamicSlotValue(andframe->dynamicSlots, SYM_STRATEGIES_LOGIC_PROOF_ADJUNCT, adjunct, NULL);
      }
      downframe = ((ControlFrame*)((adjunct->clusterFrames->theArray)[(andframe->argumentCursor)]));
      if (!((boolean)(downframe))) {
        createSubgoalFrame(andframe, ((Proposition*)((arguments->theArray)[(andframe->argumentCursor)])), NULL);
      }
      else {
        andframe->down = downframe;
      }
      return (KWD_STRATEGIES_MOVE_DOWN);
    }
    else if (lastmove == KWD_STRATEGIES_UP_TRUE) {
      andframe->truthValue = ((!((boolean)(andframe->truthValue))) ? andframe->result->truthValue : conjoinTruthValues(andframe->truthValue, andframe->result->truthValue));
      if (oRECORD_JUSTIFICATIONSpo) {
        recordAndIntroductionJustification(andframe, lastmove);
      }
      (adjunct->clusterFrames->theArray)[(andframe->argumentCursor)] = (andframe->down);
      if ((andframe->argumentCursor + 1) == nofarguments) {
        { int i = NULL_INTEGER;
          int iter000 = 1;
          int upperBound000 = nofarguments;
          boolean unboundedP000 = upperBound000 == NULL_INTEGER;

          for  (; unboundedP000 ||
                    (iter000 <= upperBound000); 
                iter000 = iter000 + 1) {
            i = iter000;
            if (((boolean)(((ControlFrame*)((adjunct->clusterFrames->theArray)[(nofarguments - i)]))))) {
              andframe->argumentCursor = nofarguments - i;
              andframe->down = ((ControlFrame*)((adjunct->clusterFrames->theArray)[(andframe->argumentCursor)]));
              return (KWD_STRATEGIES_CONTINUING_SUCCESS);
            }
          }
        }
        andframe->down = NULL;
        return (KWD_STRATEGIES_FINAL_SUCCESS);
      }
      else {
        andframe->argumentCursor = andframe->argumentCursor + 1;
        downframe = ((ControlFrame*)((adjunct->clusterFrames->theArray)[(andframe->argumentCursor)]));
        if (!((boolean)(downframe))) {
          createSubgoalFrame(andframe, ((Proposition*)((arguments->theArray)[(andframe->argumentCursor)])), NULL);
        }
        else {
          andframe->down = downframe;
        }
        return (KWD_STRATEGIES_MOVE_DOWN);
      }
    }
    else if (lastmove == KWD_STRATEGIES_UP_FAIL) {
      if (((boolean)(oQUERYITERATORo)) &&
          ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
        andframe->down = NULL;
        setFrameTruthValue(andframe, NULL);
        return (KWD_STRATEGIES_TERMINAL_FAILURE);
      }
      if (!((boolean)(((ControlFrame*)((adjunct->clusterFrames->theArray)[(andframe->argumentCursor)]))))) {
        { Keyword* testValue000 = ((Proposition*)((arguments->theArray)[(andframe->argumentCursor)]))->kind;

          if ((testValue000 == KWD_STRATEGIES_AND) ||
              ((testValue000 == KWD_STRATEGIES_FUNCTION) ||
               ((testValue000 == KWD_STRATEGIES_PREDICATE) ||
                (testValue000 == KWD_STRATEGIES_IMPLIES)))) {
            andframe->down = NULL;
            setFrameTruthValue(andframe, NULL);
            return (KWD_STRATEGIES_TERMINAL_FAILURE);
          }
          else {
          }
        }
      }
      (adjunct->clusterFrames->theArray)[(andframe->argumentCursor)] = NULL;
      { int i = NULL_INTEGER;
        int iter001 = 1;
        int upperBound001 = andframe->argumentCursor;
        boolean unboundedP001 = upperBound001 == NULL_INTEGER;

        for  (; unboundedP001 ||
                  (iter001 <= upperBound001); 
              iter001 = iter001 + 1) {
          i = iter001;
          if (((boolean)(((ControlFrame*)((adjunct->clusterFrames->theArray)[(andframe->argumentCursor - i)]))))) {
            andframe->argumentCursor = andframe->argumentCursor - i;
            andframe->down = ((ControlFrame*)((adjunct->clusterFrames->theArray)[(andframe->argumentCursor)]));
            return (KWD_STRATEGIES_MOVE_DOWN);
          }
        }
      }
      andframe->down = NULL;
      setFrameTruthValue(andframe, NULL);
      return (KWD_STRATEGIES_TERMINAL_FAILURE);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

World* pushMonotonicWorld() {
  { World* world = pushWorld();

    setDynamicSlotValue(world->dynamicSlots, SYM_STRATEGIES_LOGIC_MONOTONICp, TRUE_WRAPPER, FALSE_WRAPPER);
    return (world);
  }
}

Keyword* tryDisjunctiveImplicationProof(ControlFrame* frame) {
  { ParallelThread* parallelthread = oQUERYITERATORo->currentParallelThread;
    ParallelControlFrame* parallelframe = ((ParallelControlFrame*)(parallelthread->topControlFrame->up));

    { Proposition* disjunctiveprop = frame->proposition;
      Vector* disjuncts = disjunctiveprop->arguments;
      Proposition* subgoaldisjunct = ((Proposition*)((disjuncts->theArray)[0]));

      if (parallelframe->unboundVariablesP) {
        {
          subgoaldisjunct = NULL;
          { Proposition* d = NULL;
            Vector* vector000 = disjuncts;
            int index000 = 0;
            int length000 = vector000->length();

            for  (; index000 < length000; 
                  index000 = index000 + 1) {
              d = ((Proposition*)((vector000->theArray)[index000]));
              if (!allArgumentsBoundP(d)) {
                if (((boolean)(subgoaldisjunct))) {
                  return (KWD_STRATEGIES_FAILURE);
                }
                subgoaldisjunct = d;
              }
            }
          }
        }
      }
      else {
        { Proposition* d = NULL;
          Vector* vector001 = disjuncts;
          int index001 = 0;
          int length001 = vector001->length();

          for  (; index001 < length001; 
                index001 = index001 + 1) {
            d = ((Proposition*)((vector001->theArray)[index001]));
            if (!(d->kind == KWD_STRATEGIES_NOT)) {
              subgoaldisjunct = d;
              break;
            }
          }
        }
      }
      enterHypotheticalWorld(parallelframe);
      try {
        { boolean negatedtruthvalueP = frame->reversePolarityP;
          Proposition* assumption = NULL;

          { Proposition* disj = NULL;
            Vector* vector002 = disjuncts;
            int index002 = 0;
            int length002 = vector002->length();

            for  (; index002 < length002; 
                  index002 = index002 + 1) {
              disj = ((Proposition*)((vector002->theArray)[index002]));
              if (!(disj == subgoaldisjunct)) {
                assumption = recursivelyFastenDownPropositions((negatedtruthvalueP ? conjoinPropositions(inheritAsTopLevelProposition(disj, newKeyValueMap())) : inheritProposition(disj, newKeyValueMap())), false);
                if (((boolean)(oTRACED_KEYWORDSo)) &&
                    oTRACED_KEYWORDSo->membP(KWD_STRATEGIES_GOAL_TREE)) {
                  std::cout << std::endl << "  Assume that " << assumption << " is " << ((negatedtruthvalueP ? "true" : "false")) << "." << std::endl << std::endl;
                }
                assignTruthValue(assumption, (negatedtruthvalueP ? TRUE_WRAPPER : FALSE_WRAPPER));
              }
            }
          }
        }
      }
      catch (Clash ) {
        return (KWD_STRATEGIES_FINAL_SUCCESS);
      }
      { Proposition* d = NULL;
        Vector* vector003 = disjuncts;
        int index003 = 0;
        int length003 = vector003->length();
        int i = NULL_INTEGER;
        int iter000 = 0;

        for  (; index003 < length003; 
              index003 = index003 + 1,
              iter000 = iter000 + 1) {
          d = ((Proposition*)((vector003->theArray)[index003]));
          i = iter000;
          if (d == subgoaldisjunct) {
            frame->argumentCursor = i;
            break;
          }
        }
      }
      return (KWD_STRATEGIES_MOVE_DOWN);
    }
  }
}

Keyword* resumeDisjunctiveImplicationProof(ControlFrame* frame, Keyword* lastmove) {
  if (lastmove == KWD_STRATEGIES_UP_TRUE) {
    propagateFrameTruthValue(frame->result, frame);
    if (((boolean)(frame->result->partialMatchFrame))) {
      frame->result->partialMatchFrame->propagateFramePartialTruth(frame);
    }
    if (((boolean)(frame->down))) {
      return (KWD_STRATEGIES_CONTINUING_SUCCESS);
    }
    else {
      return (KWD_STRATEGIES_FINAL_SUCCESS);
    }
  }
  else if (lastmove == KWD_STRATEGIES_UP_FAIL) {
    return (KWD_STRATEGIES_FAILURE);
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Module* oPL_ANONYMOUS_MODULEo = NULL;

LogicObject* createAnonymousInstance(const char* prefix, boolean skolemP) {
  { Symbol* instancename = internSymbolInModule(yieldUniqueGensymName(prefix, oPL_ANONYMOUS_MODULEo), oPL_ANONYMOUS_MODULEo, true);
    LogicObject* instance = (skolemP ? createSkolem(NULL, instancename) : ((LogicObject*)(createLogicInstance(internSurrogateInModule(instancename->symbolName, ((Module*)(instancename->homeContext)), true), NULL))));

    setDynamicSlotValue(instance->dynamicSlots, SYM_STRATEGIES_LOGIC_HYPOTHESIZED_INSTANCEp, TRUE_WRAPPER, FALSE_WRAPPER);
    return (instance);
  }
}

LogicObject* createHypothesizedInstance(const char* prefix) {
  { LogicObject* instance = createAnonymousInstance(prefix, true);

    setDynamicSlotValue(instance->dynamicSlots, SYM_STRATEGIES_LOGIC_HYPOTHESIZED_INSTANCEp, TRUE_WRAPPER, FALSE_WRAPPER);
    return (instance);
  }
}

Keyword* tryUniversalIntroductionProof(ControlFrame* frame) {
  { ParallelThread* parallelthread = oQUERYITERATORo->currentParallelThread;
    ParallelControlFrame* parallelframe = ((ParallelControlFrame*)(parallelthread->topControlFrame->up));

    enterHypotheticalWorld(parallelframe);
    { Proposition* forallprop = frame->proposition;
      Object* antecedent = (forallprop->arguments->theArray)[0];
      Object* consequent = (forallprop->arguments->theArray)[1];

      { PatternVariable* v = NULL;
        Vector* vector000 = ((Vector*)(dynamicSlotValue(forallprop->dynamicSlots, SYM_STRATEGIES_LOGIC_IO_VARIABLES, NULL)));
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          v = ((PatternVariable*)((vector000->theArray)[index000]));
          { LogicObject* skolem = createHypothesizedInstance("anonymous");

            if (((boolean)(v->skolemType))) {
              assertMemberOfProposition(skolem, getDescription(v->skolemType));
            }
            bindVariableToValueP(v, skolem, false);
          }
        }
      }
      try {
        { Proposition* prop = NULL;
          Cons* iter000 = inheritAsTopLevelProposition(((Proposition*)(antecedent)), NULL);

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            prop = ((Proposition*)(iter000->value));
            recursivelyFastenDownPropositions(prop, false);
            assignTruthValue(prop, TRUE_WRAPPER);
          }
        }
      }
      catch (Clash ) {
        return (KWD_STRATEGIES_FINAL_SUCCESS);
      }
      createDownFrame(frame, ((Proposition*)(consequent)));
      return (KWD_STRATEGIES_MOVE_DOWN);
    }
  }
}

Keyword* tryRefutationProof(ControlFrame* frame) {
  { ParallelThread* parallelthread = oQUERYITERATORo->currentParallelThread;
    ParallelControlFrame* parallelframe = ((ParallelControlFrame*)(parallelthread->topControlFrame->up));

    if (parallelframe->unboundVariablesP) {
      return (KWD_STRATEGIES_FAILURE);
    }
    enterHypotheticalWorld(parallelframe);
    try {
      { boolean negatedtruthvalueP = frame->reversePolarityP;

        { Proposition* prop = NULL;
          Cons* iter000 = inheritAsTopLevelProposition(frame->proposition, NULL);

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            prop = ((Proposition*)(iter000->value));
            if (((boolean)(oTRACED_KEYWORDSo)) &&
                oTRACED_KEYWORDSo->membP(KWD_STRATEGIES_GOAL_TREE)) {
              std::cout << std::endl << "  Assume that " << prop << " is " << ((negatedtruthvalueP ? "true" : "false")) << "." << std::endl;
            }
            recursivelyFastenDownPropositions(prop, false);
            assignTruthValue(prop, (negatedtruthvalueP ? TRUE_WRAPPER : FALSE_WRAPPER));
          }
        }
      }
    }
    catch (Clash ) {
      return (KWD_STRATEGIES_FINAL_SUCCESS);
    }
    return (KWD_STRATEGIES_FAILURE);
  }
}

Keyword* continueForallProof(ControlFrame* frame, Keyword* lastmove) {
  lastmove = lastmove;
  { boolean testValue000 = false;

    if (frame->reversePolarityP) {
      testValue000 = true;
    }
    else {
      {
        { boolean alwaysP000 = true;

          { PatternVariable* var = NULL;
            Vector* vector000 = ((Vector*)(dynamicSlotValue(frame->proposition->dynamicSlots, SYM_STRATEGIES_LOGIC_IO_VARIABLES, NULL)));
            int index000 = 0;
            int length000 = vector000->length();

            for  (; index000 < length000; 
                  index000 = index000 + 1) {
              var = ((PatternVariable*)((vector000->theArray)[index000]));
              if (!closedTermP(getDescription(logicalType(var)))) {
                alwaysP000 = false;
                break;
              }
            }
          }
          testValue000 = alwaysP000;
        }
        if (!testValue000) {
          testValue000 = closedPropositionP(((Proposition*)((frame->proposition->arguments->theArray)[0])));
        }
      }
    }
    if (testValue000) {
      {
        frame->state = KWD_STRATEGIES_ITERATIVE_FORALL;
        return (KWD_STRATEGIES_MOVE_IN_PLACE);
      }
    }
    else {
      {
        { Keyword* testValue001 = currentInferenceLevel()->keyword;

          if ((testValue001 == KWD_STRATEGIES_NORMAL) ||
              (testValue001 == KWD_STRATEGIES_REFUTATION)) {
            overlayWithStrategyFrame(frame, KWD_STRATEGIES_UNIVERSAL_INTRODUCTION);
            return (KWD_STRATEGIES_MOVE_IN_PLACE);
          }
          else {
            return (KWD_STRATEGIES_FAILURE);
          }
        }
      }
    }
  }
}

Keyword* continueExistsProof(ControlFrame* frame, Keyword* lastmove) {
  if (lastmove == KWD_STRATEGIES_DOWN) {
    return (KWD_STRATEGIES_MOVE_DOWN);
  }
  else if (lastmove == KWD_STRATEGIES_UP_TRUE) {
    { ControlFrame* result = frame->result;

      if (((boolean)(result->partialMatchFrame))) {
        result->partialMatchFrame->propagateFramePartialTruth(frame);
      }
      propagateFrameTruthValue(result, frame);
      if (oRECORD_JUSTIFICATIONSpo) {
        recordExistentialIntroductionJustification(frame, lastmove);
      }
      if (!((boolean)(frame->down))) {
        return (KWD_STRATEGIES_FINAL_SUCCESS);
      }
      else {
        return (KWD_STRATEGIES_CONTINUING_SUCCESS);
      }
    }
  }
  else if (lastmove == KWD_STRATEGIES_UP_FAIL) {
    { ControlFrame* result = frame->result;

      if (((boolean)(result->partialMatchFrame))) {
        result->partialMatchFrame->propagateFramePartialTruth(frame);
      }
      propagateFrameTruthValue(result, frame);
      if (!((boolean)(frame->down))) {
        return (KWD_STRATEGIES_FAILURE);
      }
      else {
        throw *newStellaException("Failed subgoal of 'exists' didn't remove itself from stack.");
      }
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Keyword* continueConstantProof(ControlFrame* frame, Keyword* lastmove) {
  lastmove = lastmove;
  { Proposition* proposition = frame->proposition;

    frame->truthValue = ((TruthValue*)(accessInContext(proposition->truthValue, proposition->homeContext, false)));
    if (oRECORD_JUSTIFICATIONSpo &&
        (!((boolean)(((Justification*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_JUSTIFICATION, NULL))))))) {
      { PrimitiveStrategy* self000 = newPrimitiveStrategy();

        self000->strategy = KWD_STRATEGIES_CONSTANT_PROPOSITION;
        recordGoalJustification(frame, self000);
      }
    }
    if (frame->reversePolarityP) {
      if (falseP(proposition)) {
        return (KWD_STRATEGIES_FINAL_SUCCESS);
      }
      else {
        return (KWD_STRATEGIES_FAILURE);
      }
    }
    else {
      if (trueP(proposition)) {
        return (KWD_STRATEGIES_FINAL_SUCCESS);
      }
      else {
        return (KWD_STRATEGIES_FAILURE);
      }
    }
  }
}

void registerInferenceCutoff(ControlFrame* frame, Keyword* reason) {
  while (((boolean)(frame))) {
    if ((frame->state == KWD_STRATEGIES_FAIL) ||
        collectDescriptionExtensionFrameP(frame)) {
      setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_INFERENCE_CUTOFF_REASON, reason, NULL);
    }
    frame = frame->up;
  }
}

Keyword* continueFailProof(ControlFrame* frame, Keyword* lastmove) {
  if (lastmove == KWD_STRATEGIES_DOWN) {
    createChoicePoint(frame);
    setDynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_INFERENCE_CUTOFF_REASON, NULL, NULL);
    return (KWD_STRATEGIES_MOVE_DOWN);
  }
  else if (lastmove == KWD_STRATEGIES_UP_TRUE) {
    { Keyword* result = (frame->reversePolarityP ? KWD_STRATEGIES_FINAL_SUCCESS : KWD_STRATEGIES_FAILURE);

      if (frame->reversePolarityP) {
        setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
        if (oRECORD_JUSTIFICATIONSpo) {
          recordNegatedFailJustification(frame, lastmove);
        }
      }
      else {
        setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
      }
      unbindVariablesBeginningAt(oQUERYITERATORo->currentPatternRecord, frame->choicePointUnbindingOffset);
      if (((boolean)(frame->down))) {
        popFramesUpTo(frame->down);
      }
      return (result);
    }
  }
  else if (lastmove == KWD_STRATEGIES_UP_FAIL) {
    { Keyword* result = (frame->reversePolarityP ? KWD_STRATEGIES_FAILURE : KWD_STRATEGIES_FINAL_SUCCESS);

      if (((boolean)(((Keyword*)(dynamicSlotValue(frame->dynamicSlots, SYM_STRATEGIES_LOGIC_INFERENCE_CUTOFF_REASON, NULL)))))) {
        setFrameTruthValue(frame, UNKNOWN_TRUTH_VALUE);
        result = KWD_STRATEGIES_FAILURE;
      }
      else if (frame->result->truthValue == INCONSISTENT_TRUTH_VALUE) {
        setFrameTruthValue(frame, INCONSISTENT_TRUTH_VALUE);
        result = KWD_STRATEGIES_TERMINAL_FAILURE;
      }
      else if (frame->reversePolarityP) {
        setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
      }
      else {
        setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
        if (oRECORD_JUSTIFICATIONSpo) {
          if (frame->up->proposition->kind == KWD_STRATEGIES_NOT) {
            recordClosedNotJustification(frame, lastmove);
          }
          else {
            recordFailJustification(frame, lastmove);
          }
        }
      }
      unbindVariablesBeginningAt(oQUERYITERATORo->currentPatternRecord, frame->choicePointUnbindingOffset);
      return (result);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Keyword* ControlFrame::continuePartialFailProof(Keyword* lastmove) {
  { ControlFrame* self = this;

    { PartialMatchFrame* pmf = self->partialMatchFrame;

      if (!((boolean)(pmf))) {
        createAndLinkPartialMatchFrame(self, KWD_STRATEGIES_FAIL);
      }
      return (self->partialMatchFrame->continuePartialFailProof(lastmove));
    }
  }
}

void helpStartupStrategies1() {
  {
    KWD_STRATEGIES_DOWN = ((Keyword*)(internRigidSymbolWrtModule("DOWN", NULL, 2)));
    KWD_STRATEGIES_MOVE_DOWN = ((Keyword*)(internRigidSymbolWrtModule("MOVE-DOWN", NULL, 2)));
    KWD_STRATEGIES_UP_TRUE = ((Keyword*)(internRigidSymbolWrtModule("UP-TRUE", NULL, 2)));
    KWD_STRATEGIES_UP_FAIL = ((Keyword*)(internRigidSymbolWrtModule("UP-FAIL", NULL, 2)));
    KWD_STRATEGIES_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("FAILURE", NULL, 2)));
    KWD_STRATEGIES_FINAL_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("FINAL-SUCCESS", NULL, 2)));
    KWD_STRATEGIES_CONTINUING_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("CONTINUING-SUCCESS", NULL, 2)));
    KWD_STRATEGIES_GOAL_TREE = ((Keyword*)(internRigidSymbolWrtModule("GOAL-TREE", NULL, 2)));
    SYM_STRATEGIES_LOGIC_JUSTIFICATION = ((Symbol*)(internRigidSymbolWrtModule("JUSTIFICATION", NULL, 0)));
    KWD_STRATEGIES_TERMINAL_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("TERMINAL-FAILURE", NULL, 2)));
    SYM_STRATEGIES_LOGIC_INFERENCE_CUTOFF_REASON = ((Symbol*)(internRigidSymbolWrtModule("INFERENCE-CUTOFF-REASON", NULL, 0)));
    SYM_STRATEGIES_STELLA_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR", getStellaModule("/STELLA", true), 0)));
    SYM_STRATEGIES_LOGIC_ANTECEDENTS_RULE = ((Symbol*)(internRigidSymbolWrtModule("ANTECEDENTS-RULE", NULL, 0)));
    SYM_STRATEGIES_LOGIC_PROOF_ADJUNCT = ((Symbol*)(internRigidSymbolWrtModule("PROOF-ADJUNCT", NULL, 0)));
    KWD_STRATEGIES_PARALLEL_STRATEGIES = ((Keyword*)(internRigidSymbolWrtModule("PARALLEL-STRATEGIES", NULL, 2)));
    KWD_STRATEGIES_SELECT_PARALLEL_THREAD = ((Keyword*)(internRigidSymbolWrtModule("SELECT-PARALLEL-THREAD", NULL, 2)));
    KWD_STRATEGIES_FAIL = ((Keyword*)(internRigidSymbolWrtModule("FAIL", NULL, 2)));
    KWD_STRATEGIES_TRUE = ((Keyword*)(internRigidSymbolWrtModule("TRUE", NULL, 2)));
    KWD_STRATEGIES_STRATEGIES = ((Keyword*)(internRigidSymbolWrtModule("STRATEGIES", NULL, 2)));
    SYM_STRATEGIES_LOGIC_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 0)));
    KWD_STRATEGIES_MOVE_IN_PLACE = ((Keyword*)(internRigidSymbolWrtModule("MOVE-IN-PLACE", NULL, 2)));
    KWD_STRATEGIES_TIME_OUT = ((Keyword*)(internRigidSymbolWrtModule("TIME-OUT", NULL, 2)));
    KWD_STRATEGIES_SPECIALIST = ((Keyword*)(internRigidSymbolWrtModule("SPECIALIST", NULL, 2)));
    KWD_STRATEGIES_ANTECEDENTS = ((Keyword*)(internRigidSymbolWrtModule("ANTECEDENTS", NULL, 2)));
    KWD_STRATEGIES_CLUSTERED_CONJUNCTION = ((Keyword*)(internRigidSymbolWrtModule("CLUSTERED-CONJUNCTION", NULL, 2)));
    KWD_STRATEGIES_CONDITIONAL_ANTECEDENT = ((Keyword*)(internRigidSymbolWrtModule("CONDITIONAL-ANTECEDENT", NULL, 2)));
    KWD_STRATEGIES_DISJUNCTIVE_IMPLICATION_INTRODUCTION = ((Keyword*)(internRigidSymbolWrtModule("DISJUNCTIVE-IMPLICATION-INTRODUCTION", NULL, 2)));
    KWD_STRATEGIES_ATOMIC_GOAL = ((Keyword*)(internRigidSymbolWrtModule("ATOMIC-GOAL", NULL, 2)));
    KWD_STRATEGIES_DUMMY_JUSTIFICATION = ((Keyword*)(internRigidSymbolWrtModule("DUMMY-JUSTIFICATION", NULL, 2)));
    KWD_STRATEGIES_LOOKUP_GOAL_CACHES = ((Keyword*)(internRigidSymbolWrtModule("LOOKUP-GOAL-CACHES", NULL, 2)));
    SYM_STRATEGIES_LOGIC_CHECK_FOR_CACHED_GOALSp = ((Symbol*)(internRigidSymbolWrtModule("CHECK-FOR-CACHED-GOALS?", NULL, 0)));
    KWD_STRATEGIES_DUPLICATE_GOALS = ((Keyword*)(internRigidSymbolWrtModule("DUPLICATE-GOALS", NULL, 2)));
    KWD_STRATEGIES_MANUFACTURE_SKOLEM = ((Keyword*)(internRigidSymbolWrtModule("MANUFACTURE-SKOLEM", NULL, 2)));
    SGT_STRATEGIES_PL_KERNEL_KB_TOTAL = ((Surrogate*)(internRigidSymbolWrtModule("TOTAL", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_STRATEGIES_LOOKUP_ASSERTIONS = ((Keyword*)(internRigidSymbolWrtModule("LOOKUP-ASSERTIONS", NULL, 2)));
    KWD_STRATEGIES_SCAN_PROPOSITIONS = ((Keyword*)(internRigidSymbolWrtModule("SCAN-PROPOSITIONS", NULL, 2)));
    KWD_STRATEGIES_SCAN_PARTIAL_PROPOSITIONS = ((Keyword*)(internRigidSymbolWrtModule("SCAN-PARTIAL-PROPOSITIONS", NULL, 2)));
    KWD_STRATEGIES_SCAN_COLLECTION = ((Keyword*)(internRigidSymbolWrtModule("SCAN-COLLECTION", NULL, 2)));
    KWD_STRATEGIES_SHALLOW_DISPROOF = ((Keyword*)(internRigidSymbolWrtModule("SHALLOW-DISPROOF", NULL, 2)));
    KWD_STRATEGIES_SCAN_FOR_VALUE_CLASH = ((Keyword*)(internRigidSymbolWrtModule("SCAN-FOR-VALUE-CLASH", NULL, 2)));
    KWD_STRATEGIES_ALL_SUBGOAL_STRATEGIES = ((Keyword*)(internRigidSymbolWrtModule("ALL-SUBGOAL-STRATEGIES", NULL, 2)));
    KWD_STRATEGIES_FULL_SUBQUERY = ((Keyword*)(internRigidSymbolWrtModule("FULL-SUBQUERY", NULL, 2)));
    KWD_STRATEGIES_GOAL_COMPLEMENT = ((Keyword*)(internRigidSymbolWrtModule("GOAL-COMPLEMENT", NULL, 2)));
    KWD_STRATEGIES_FORWARD_GOALS = ((Keyword*)(internRigidSymbolWrtModule("FORWARD-GOALS", NULL, 2)));
    KWD_STRATEGIES_IMPLIES = ((Keyword*)(internRigidSymbolWrtModule("IMPLIES", NULL, 2)));
    KWD_STRATEGIES_CONTAINED_BY = ((Keyword*)(internRigidSymbolWrtModule("CONTAINED-BY", NULL, 2)));
    KWD_STRATEGIES_EQUIVALENCE = ((Keyword*)(internRigidSymbolWrtModule("EQUIVALENCE", NULL, 2)));
    KWD_STRATEGIES_UNIVERSAL_INTRODUCTION = ((Keyword*)(internRigidSymbolWrtModule("UNIVERSAL-INTRODUCTION", NULL, 2)));
    KWD_STRATEGIES_SUBSUMPTION_TEST = ((Keyword*)(internRigidSymbolWrtModule("SUBSUMPTION-TEST", NULL, 2)));
    KWD_STRATEGIES_REFUTATION = ((Keyword*)(internRigidSymbolWrtModule("REFUTATION", NULL, 2)));
    KWD_STRATEGIES_STRATEGY = ((Keyword*)(internRigidSymbolWrtModule("STRATEGY", NULL, 2)));
    KWD_STRATEGIES_DEBUG = ((Keyword*)(internRigidSymbolWrtModule("DEBUG", NULL, 2)));
    KWD_STRATEGIES_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("SUCCESS", NULL, 2)));
    SYM_STRATEGIES_LOGIC_LATEST_POSITIVE_SCORE = ((Symbol*)(internRigidSymbolWrtModule("LATEST-POSITIVE-SCORE", NULL, 0)));
    KWD_STRATEGIES_GOAL_CACHES = ((Keyword*)(internRigidSymbolWrtModule("GOAL-CACHES", NULL, 2)));
    KWD_STRATEGIES_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    KWD_STRATEGIES_INITIALIZE = ((Keyword*)(internRigidSymbolWrtModule("INITIALIZE", NULL, 2)));
    KWD_STRATEGIES_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SGT_STRATEGIES_LOGIC_WHYNOT_PARTIAL_MATCH = ((Surrogate*)(internRigidSymbolWrtModule("WHYNOT-PARTIAL-MATCH", NULL, 1)));
    KWD_STRATEGIES_NOT = ((Keyword*)(internRigidSymbolWrtModule("NOT", NULL, 2)));
  }
}

void helpStartupStrategies2() {
  {
    SGT_STRATEGIES_PL_KERNEL_KB_MEMBER_OF = ((Surrogate*)(internRigidSymbolWrtModule("MEMBER-OF", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_STRATEGIES_STELLA_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", getStellaModule("/STELLA", true), 1)));
    KWD_STRATEGIES_FORWARD = ((Keyword*)(internRigidSymbolWrtModule("FORWARD", NULL, 2)));
    KWD_STRATEGIES_DUPLICATE_ = ((Keyword*)(internRigidSymbolWrtModule("DUPLICATE-", NULL, 2)));
    KWD_STRATEGIES_BACKWARD = ((Keyword*)(internRigidSymbolWrtModule("BACKWARD", NULL, 2)));
    SYM_STRATEGIES_LOGIC_BACKWARD_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("BACKWARD-ONLY?", NULL, 0)));
    SYM_STRATEGIES_LOGIC_FORWARD_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("FORWARD-ONLY?", NULL, 0)));
    SGT_STRATEGIES_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
    SGT_STRATEGIES_STELLA_CONS_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("CONS-ITERATOR", getStellaModule("/STELLA", true), 1)));
    KWD_STRATEGIES_FORWARD_RULE = ((Keyword*)(internRigidSymbolWrtModule("FORWARD-RULE", NULL, 2)));
    SGT_STRATEGIES_LOGIC_CONDITIONAL_ANTECEDENT_PROOF_ADJUNCT = ((Surrogate*)(internRigidSymbolWrtModule("CONDITIONAL-ANTECEDENT-PROOF-ADJUNCT", NULL, 1)));
    SYM_STRATEGIES_LOGIC_PROVABLE_RULE = ((Symbol*)(internRigidSymbolWrtModule("PROVABLE-RULE", NULL, 0)));
    SYM_STRATEGIES_LOGIC_GOAL = ((Symbol*)(internRigidSymbolWrtModule("GOAL", NULL, 0)));
    SYM_STRATEGIES_STELLA_PHASE = ((Symbol*)(internRigidSymbolWrtModule("PHASE", getStellaModule("/STELLA", true), 0)));
    KWD_STRATEGIES_ORIGINAL_GOAL = ((Keyword*)(internRigidSymbolWrtModule("ORIGINAL-GOAL", NULL, 2)));
    SGT_STRATEGIES_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
    SGT_STRATEGIES_STELLA_LITERAL_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_STRATEGIES_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    SYM_STRATEGIES_LOGIC_COMPLEMENT_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("COMPLEMENT-DESCRIPTION", NULL, 0)));
    SYM_STRATEGIES_LOGIC_CONTAINED_BY = ((Symbol*)(internRigidSymbolWrtModule("CONTAINED-BY", NULL, 0)));
    SGT_STRATEGIES_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
    SYM_STRATEGIES_STELLA_ISA = ((Symbol*)(internRigidSymbolWrtModule("ISA", getStellaModule("/STELLA", true), 0)));
    SYM_STRATEGIES_STELLA_PREDICATE = ((Symbol*)(internRigidSymbolWrtModule("PREDICATE", getStellaModule("/STELLA", true), 0)));
    KWD_STRATEGIES_LOCAL = ((Keyword*)(internRigidSymbolWrtModule("LOCAL", NULL, 2)));
    SYM_STRATEGIES_LOGIC_BACK = ((Symbol*)(internRigidSymbolWrtModule("BACK", NULL, 0)));
    KWD_STRATEGIES_POPPED = ((Keyword*)(internRigidSymbolWrtModule("POPPED", NULL, 2)));
    SYM_STRATEGIES_LOGIC_EXTERNAL_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("EXTERNAL-VARIABLES", NULL, 0)));
    SGT_STRATEGIES_LOGIC_CLUSTERED_CONJUNCTION_PROOF_ADJUNCT = ((Surrogate*)(internRigidSymbolWrtModule("CLUSTERED-CONJUNCTION-PROOF-ADJUNCT", NULL, 1)));
    SYM_STRATEGIES_LOGIC_CLUSTER_FRAMES = ((Symbol*)(internRigidSymbolWrtModule("CLUSTER-FRAMES", NULL, 0)));
    KWD_STRATEGIES_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    KWD_STRATEGIES_PREDICATE = ((Keyword*)(internRigidSymbolWrtModule("PREDICATE", NULL, 2)));
    SYM_STRATEGIES_LOGIC_MONOTONICp = ((Symbol*)(internRigidSymbolWrtModule("MONOTONIC?", NULL, 0)));
    SYM_STRATEGIES_LOGIC_HYPOTHESIZED_INSTANCEp = ((Symbol*)(internRigidSymbolWrtModule("HYPOTHESIZED-INSTANCE?", NULL, 0)));
    SYM_STRATEGIES_LOGIC_IO_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("IO-VARIABLES", NULL, 0)));
    KWD_STRATEGIES_ITERATIVE_FORALL = ((Keyword*)(internRigidSymbolWrtModule("ITERATIVE-FORALL", NULL, 2)));
    KWD_STRATEGIES_NORMAL = ((Keyword*)(internRigidSymbolWrtModule("NORMAL", NULL, 2)));
    KWD_STRATEGIES_CONSTANT_PROPOSITION = ((Keyword*)(internRigidSymbolWrtModule("CONSTANT-PROPOSITION", NULL, 2)));
    KWD_STRATEGIES_TECHNICAL = ((Keyword*)(internRigidSymbolWrtModule("TECHNICAL", NULL, 2)));
    KWD_STRATEGIES_LAY = ((Keyword*)(internRigidSymbolWrtModule("LAY", NULL, 2)));
    SYM_STRATEGIES_LOGIC_STARTUP_STRATEGIES = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-STRATEGIES", NULL, 0)));
    SYM_STRATEGIES_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupStrategies3() {
  {
    defineFunctionObject("CONTINUE-STRATEGIES-PROOFS", "(DEFUN (CONTINUE-STRATEGIES-PROOFS KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&continueStrategiesProofs)), NULL);
    defineFunctionObject("CLEAR-STRATEGY-SLOTS", "(DEFUN CLEAR-STRATEGY-SLOTS ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&clearStrategySlots)), NULL);
    defineFunctionObject("SELECT-NEXT-STRATEGY", "(DEFUN (SELECT-NEXT-STRATEGY CONTROL-FRAME) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&selectNextStrategy)), NULL);
    defineFunctionObject("RECORD-BASE-PARTIAL-MATCH-TRUTH", "(DEFUN RECORD-BASE-PARTIAL-MATCH-TRUTH ((FRAME CONTROL-FRAME) (RESULT KEYWORD)))", ((cpp_function_code)(&recordBasePartialMatchTruth)), NULL);
    defineFunctionObject("CONTINUE-CURRENT-OR-NEXT-STRATEGY", "(DEFUN (CONTINUE-CURRENT-OR-NEXT-STRATEGY KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&continueCurrentOrNextStrategy)), NULL);
    defineFunctionObject("RESUME-PROOF-STRATEGY-AFTER-SUBGOAL", "(DEFUN (RESUME-PROOF-STRATEGY-AFTER-SUBGOAL KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&resumeProofStrategyAfterSubgoal)), NULL);
    defineFunctionObject("FILTER-OUT-STRATEGY?", "(DEFUN (FILTER-OUT-STRATEGY? BOOLEAN) ((STRATEGY KEYWORD) (FRAME CONTROL-FRAME)))", ((cpp_function_code)(&filterOutStrategyP)), NULL);
    defineFunctionObject("EXECUTE-PROOF-STRATEGY", "(DEFUN (EXECUTE-PROOF-STRATEGY KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&executeProofStrategy)), NULL);
    defineFunctionObject("CONTINUE-PARALLEL-STRATEGIES-PROOFS", "(DEFUN (CONTINUE-PARALLEL-STRATEGIES-PROOFS KEYWORD) ((PFRAME PARALLEL-CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&continueParallelStrategiesProofs)), NULL);
    defineFunctionObject("PARALLEL-STRATEGY?", "(DEFUN (PARALLEL-STRATEGY? BOOLEAN) ((STRATEGY KEYWORD)))", ((cpp_function_code)(&parallelStrategyP)), NULL);
    defineFunctionObject("SELECT-NEXT-CHILD-THREAD", "(DEFUN (SELECT-NEXT-CHILD-THREAD PARALLEL-THREAD) ((PFRAME PARALLEL-CONTROL-FRAME)))", ((cpp_function_code)(&selectNextChildThread)), NULL);
    defineFunctionObject("CREATE-CHILD-THREAD", "(DEFUN (CREATE-CHILD-THREAD PARALLEL-THREAD) ((PFRAME PARALLEL-CONTROL-FRAME)))", ((cpp_function_code)(&createChildThread)), NULL);
    defineFunctionObject("TRY-PARALLEL-THREAD-PROOF", "(DEFUN (TRY-PARALLEL-THREAD-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryParallelThreadProof)), NULL);
    defineFunctionObject("PUSH-NEXT-STRATEGY", "(DEFUN PUSH-NEXT-STRATEGY ((FRAME CONTROL-FRAME) (STRATEGY KEYWORD)))", ((cpp_function_code)(&pushNextStrategy)), NULL);
    defineFunctionObject("CREATE-SUBGOAL-FRAME", "(DEFUN (CREATE-SUBGOAL-FRAME CONTROL-FRAME) ((UPFRAME CONTROL-FRAME) (GOAL PROPOSITION) (STRATEGY KEYWORD)))", ((cpp_function_code)(&createSubgoalFrame)), NULL);
    defineFunctionObject("SPECIALIST-APPLICABLE?", "(DEFUN (SPECIALIST-APPLICABLE? BOOLEAN) ((DESCRIPTION NAMED-DESCRIPTION) (PROPOSITION PROPOSITION)))", ((cpp_function_code)(&specialistApplicableP)), NULL);
    defineFunctionObject("CONTINUE-SPECIALIST-PROOF", "(DEFUN (CONTINUE-SPECIALIST-PROOF KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&continueSpecialistProof)), NULL);
    defineFunctionObject("LOOKUP-CACHED-PROOF", "(DEFUN (LOOKUP-CACHED-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&lookupCachedProof)), NULL);
    defineFunctionObject("SCAN-CACHED-GOALS", "(DEFUN (SCAN-CACHED-GOALS KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&scanCachedGoals)), NULL);
    defineFunctionObject("FINISH-CACHED-GOAL-PROCESSING", "(DEFUN (FINISH-CACHED-GOAL-PROCESSING KEYWORD) ((CACHEDGOAL ATOMIC-GOAL-CACHE) (FRAME CONTROL-FRAME) (SUCCESSORFAILURE KEYWORD) (CONTINUING? BOOLEAN)))", ((cpp_function_code)(&finishCachedGoalProcessing)), NULL);
    defineFunctionObject("TRY-GOAL-CACHES-PROOF", "(DEFUN (TRY-GOAL-CACHES-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryGoalCachesProof)), NULL);
    defineFunctionObject("TRY-LOOKUP-GROUND-ASSERTIONS-PROOF", "(DEFUN (TRY-LOOKUP-GROUND-ASSERTIONS-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryLookupGroundAssertionsProof)), NULL);
    defineFunctionObject("TSPP.INITIALIZE-STRATEGY", "(DEFUN (TSPP.INITIALIZE-STRATEGY ITERATOR) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tsppDinitializeStrategy)), NULL);
    defineFunctionObject("TSPP.SPAWN-DERIVED-STRATEGIES", "(DEFUN TSPP.SPAWN-DERIVED-STRATEGIES ((FRAME CONTROL-FRAME) (STATE KEYWORD)))", ((cpp_function_code)(&tsppDspawnDerivedStrategies)), NULL);
    defineFunctionObject("TSPP.SINGLE-VALUED-STRATEGY?", "(DEFUN (TSPP.SINGLE-VALUED-STRATEGY? BOOLEAN) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tsppDsingleValuedStrategyP)), NULL);
    defineFunctionObject("TSPP.HANDLE-DEFAULT-RESULT", "(DEFUN TSPP.HANDLE-DEFAULT-RESULT ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tsppDhandleDefaultResult)), NULL);
    defineFunctionObject("TSPP.RECORD-RESULT-JUSTIFICATION", "(DEFUN TSPP.RECORD-RESULT-JUSTIFICATION ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tsppDrecordResultJustification)), NULL);
    defineFunctionObject("TSPP.PROPAGATE-RESULT-TRUTH-VALUE", "(DEFUN TSPP.PROPAGATE-RESULT-TRUTH-VALUE ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tsppDpropagateResultTruthValue)), NULL);
    defineFunctionObject("TRY-SCAN-PROPOSITIONS-PROOF", "(DEFUN (TRY-SCAN-PROPOSITIONS-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryScanPropositionsProof)), NULL);
    defineFunctionObject("HAS-SHALLOW-DISPROOF?", "(DEFUN (HAS-SHALLOW-DISPROOF? BOOLEAN) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&hasShallowDisproofP)), NULL);
    defineFunctionObject("HAS-DISJOINTNESS-DISPROOF?", "(DEFUN (HAS-DISJOINTNESS-DISPROOF? BOOLEAN) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&hasDisjointnessDisproofP)), NULL);
    defineFunctionObject("TRY-SHALLOW-DISPROOF", "(DEFUN (TRY-SHALLOW-DISPROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryShallowDisproof)), NULL);
    defineFunctionObject("TRY-SCAN-FOR-VALUE-CLASH-PROOF", "(DEFUN (TRY-SCAN-FOR-VALUE-CLASH-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryScanForValueClashProof)), NULL);
    defineFunctionObject("TRY-MANUFACTURE-SKOLEM-PROOF", "(DEFUN (TRY-MANUFACTURE-SKOLEM-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryManufactureSkolemProof)), NULL);
    defineFunctionObject("EXTRACT-SUBGOAL-OF-FRAME", "(DEFUN (EXTRACT-SUBGOAL-OF-FRAME PROPOSITION) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&extractSubgoalOfFrame)), NULL);
    defineFunctionObject("EXTRACT-SUBGOAL-DESCRIPTION-OF-FRAME", "(DEFUN (EXTRACT-SUBGOAL-DESCRIPTION-OF-FRAME DESCRIPTION) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&extractSubgoalDescriptionOfFrame)), NULL);
    defineFunctionObject("FIND-EXTERNAL-ARGUMENTS-FOR-SUBGOAL", "(DEFUN (FIND-EXTERNAL-ARGUMENTS-FOR-SUBGOAL ARGUMENTS-VECTOR) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&findExternalArgumentsForSubgoal)), NULL);
    defineFunctionObject("TRY-SUBGOAL-STRATEGIES-PROOF", "(DEFUN (TRY-SUBGOAL-STRATEGIES-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&trySubgoalStrategiesProof)), NULL);
    defineFunctionObject("ESTABLISH-GOAL-CACHE", "(DEFUN ESTABLISH-GOAL-CACHE ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&establishGoalCache)), NULL);
    defineFunctionObject("CHECK-FOR-DUPLICATE-RULE?", "(DEFUN (CHECK-FOR-DUPLICATE-RULE? BOOLEAN) ((FRAME CONTROL-FRAME) (IMPLIESPROPOSITION PROPOSITION)))", ((cpp_function_code)(&checkForDuplicateRuleP)), NULL);
    defineFunctionObject("CONTINUE-ANTECEDENTS-PROOF", "(DEFUN (CONTINUE-ANTECEDENTS-PROOF KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&continueAntecedentsProof)), NULL);
    defineFunctionObject("ALLOCATE-ANTECEDENTS-ITERATOR", "(DEFUN (ALLOCATE-ANTECEDENTS-ITERATOR (ITERATOR OF PROPOSITION)) ((GOALDESCRIPTION DESCRIPTION) (EXTERNALARGUMENTS ARGUMENTS-VECTOR) (REVERSEPOLARITY? BOOLEAN)))", ((cpp_function_code)(&allocateAntecedentsIterator)), NULL);
    defineFunctionObject("OPTIMIZE-ORDER-OF-APPLICABLE-RULES", "(DEFUN (OPTIMIZE-ORDER-OF-APPLICABLE-RULES (CONS OF PROPOSITION)) ((RULES (CONS OF PROPOSITION)) (TAIL? BOOLEAN)))", ((cpp_function_code)(&optimizeOrderOfApplicableRules)), NULL);
    defineFunctionObject("HAS-MORE-ANTECEDENTS?", "(DEFUN (HAS-MORE-ANTECEDENTS? BOOLEAN) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&hasMoreAntecedentsP)), NULL);
    defineFunctionObject("TRY-GOAL-COMPLEMENT-PROOF", "(DEFUN (TRY-GOAL-COMPLEMENT-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryGoalComplementProof)), NULL);
    defineFunctionObject("TRY-FORWARD-GOALS-PROOF", "(DEFUN (TRY-FORWARD-GOALS-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryForwardGoalsProof)), NULL);
    defineFunctionObject("CREATE-CONDITIONAL-ANTECEDENT-SUBFRAME", "(DEFUN (CREATE-CONDITIONAL-ANTECEDENT-SUBFRAME CONTROL-FRAME) ((FRAME CONTROL-FRAME) (GOAL PROPOSITION) (PROVABLERULE PROPOSITION)))", ((cpp_function_code)(&createConditionalAntecedentSubframe)), NULL);
    defineFunctionObject("CONTINUE-CONDITIONAL-ANTECEDENT-PROOF", "(DEFUN (CONTINUE-CONDITIONAL-ANTECEDENT-PROOF KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&continueConditionalAntecedentProof)), NULL);
    defineFunctionObject("TRY-FULL-SUBQUERY-PROOF", "(DEFUN (TRY-FULL-SUBQUERY-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryFullSubqueryProof)), NULL);
    defineFunctionObject("EXTRACT-COLLECTION-ARGUMENT", "(DEFUN (EXTRACT-COLLECTION-ARGUMENT DESCRIPTION) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&extractCollectionArgument)), NULL);
    defineFunctionObject("TRY-ISA-PROPOSITION-PROOF", "(DEFUN (TRY-ISA-PROPOSITION-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryIsaPropositionProof)), NULL);
    defineFunctionObject("TRY-SCAN-COLLECTION-PROOF", "(DEFUN (TRY-SCAN-COLLECTION-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryScanCollectionProof)), NULL);
    defineFunctionObject("INFERABLE-DESCRIPTION?", "(DEFUN (INFERABLE-DESCRIPTION? BOOLEAN) ((SELF OBJECT)))", ((cpp_function_code)(&inferableDescriptionP)), NULL);
    defineFunctionObject("TRY-IMPLIES-PROOF", "(DEFUN (TRY-IMPLIES-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryImpliesProof)), NULL);
    defineFunctionObject("TRY-SIMPLE-CONTAINED-BY-PROOF", "(DEFUN (TRY-SIMPLE-CONTAINED-BY-PROOF KEYWORD) ((SUBCOLLECTION OBJECT) (SUPERCOLLECTION OBJECT) (REVERSEPOLARITY? BOOLEAN)))", ((cpp_function_code)(&trySimpleContainedByProof)), NULL);
    defineFunctionObject("TRY-CONTAINED-BY-PROOF", "(DEFUN (TRY-CONTAINED-BY-PROOF KEYWORD) ((UPFRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryContainedByProof)), NULL);
    defineFunctionObject("CREATE-CONTAINED-BY-ARGUMENT", "(DEFUN (CREATE-CONTAINED-BY-ARGUMENT PROPOSITION) ((COLLECTION OBJECT) (BRIDGEARGS LIST)))", ((cpp_function_code)(&createContainedByArgument)), NULL);
    defineFunctionObject("CONTINUE-CONTAINED-BY-PROOF", "(DEFUN (CONTINUE-CONTAINED-BY-PROOF KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&continueContainedByProof)), NULL);
    defineFunctionObject("TRY-SUBSUMPTION-TEST", "(DEFUN (TRY-SUBSUMPTION-TEST KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&trySubsumptionTest)), NULL);
    defineFunctionObject("TRY-EQUIVALENCE-PROOF", "(DEFUN (TRY-EQUIVALENCE-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryEquivalenceProof)), NULL);
  }
}

void startupStrategies() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupStrategies1();
      helpStartupStrategies2();
    }
    if (currentStartupTimePhaseP(4)) {
      oPARALLEL_STRATEGIESo = list(3, KWD_STRATEGIES_DISJUNCTIVE_IMPLICATION_INTRODUCTION, KWD_STRATEGIES_UNIVERSAL_INTRODUCTION, KWD_STRATEGIES_REFUTATION);
      oPL_ANONYMOUS_MODULEo = getStellaModule("PL-ANONYMOUS", true);
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("CONDITIONAL-ANTECEDENT-PROOF-ADJUNCT", "(DEFCLASS CONDITIONAL-ANTECEDENT-PROOF-ADJUNCT (PROOF-ADJUNCT) :SLOTS ((PROVABLE-RULE :TYPE PROPOSITION) (GOAL :TYPE PROPOSITION) (PHASE :TYPE KEYWORD :INITIALLY :FORWARD-RULE)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newConditionalAntecedentProofAdjunct));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessConditionalAntecedentProofAdjunctSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("CLUSTERED-CONJUNCTION-PROOF-ADJUNCT", "(DEFCLASS CLUSTERED-CONJUNCTION-PROOF-ADJUNCT (PROOF-ADJUNCT) :SLOTS ((CLUSTER-FRAMES :TYPE (VECTOR OF CONTROL-FRAME))))");

        clasS->classConstructorCode = ((cpp_function_code)(&newClusteredConjunctionProofAdjunct));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessClusteredConjunctionProofAdjunctSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupStrategies3();
      defineFunctionObject("CONTINUE-CLUSTERED-CONJUNCTION-PROOF", "(DEFUN (CONTINUE-CLUSTERED-CONJUNCTION-PROOF KEYWORD) ((ANDFRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&continueClusteredConjunctionProof)), NULL);
      defineFunctionObject("PUSH-MONOTONIC-WORLD", "(DEFUN (PUSH-MONOTONIC-WORLD WORLD) ())", ((cpp_function_code)(&pushMonotonicWorld)), NULL);
      defineFunctionObject("TRY-DISJUNCTIVE-IMPLICATION-PROOF", "(DEFUN (TRY-DISJUNCTIVE-IMPLICATION-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryDisjunctiveImplicationProof)), NULL);
      defineFunctionObject("RESUME-DISJUNCTIVE-IMPLICATION-PROOF", "(DEFUN (RESUME-DISJUNCTIVE-IMPLICATION-PROOF KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&resumeDisjunctiveImplicationProof)), NULL);
      defineFunctionObject("CREATE-ANONYMOUS-INSTANCE", "(DEFUN (CREATE-ANONYMOUS-INSTANCE LOGIC-OBJECT) ((PREFIX STRING) (SKOLEM? BOOLEAN)))", ((cpp_function_code)(&createAnonymousInstance)), NULL);
      defineFunctionObject("CREATE-HYPOTHESIZED-INSTANCE", "(DEFUN (CREATE-HYPOTHESIZED-INSTANCE LOGIC-OBJECT) ((PREFIX STRING)))", ((cpp_function_code)(&createHypothesizedInstance)), NULL);
      defineFunctionObject("TRY-UNIVERSAL-INTRODUCTION-PROOF", "(DEFUN (TRY-UNIVERSAL-INTRODUCTION-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryUniversalIntroductionProof)), NULL);
      defineFunctionObject("TRY-REFUTATION-PROOF", "(DEFUN (TRY-REFUTATION-PROOF KEYWORD) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&tryRefutationProof)), NULL);
      defineFunctionObject("CONTINUE-FORALL-PROOF", "(DEFUN (CONTINUE-FORALL-PROOF KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&continueForallProof)), NULL);
      defineFunctionObject("CONTINUE-EXISTS-PROOF", "(DEFUN (CONTINUE-EXISTS-PROOF KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&continueExistsProof)), NULL);
      defineFunctionObject("CONTINUE-CONSTANT-PROOF", "(DEFUN (CONTINUE-CONSTANT-PROOF KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&continueConstantProof)), NULL);
      defineExternalSlotFromStringifiedSource("(DEFSLOT CONTROL-FRAME INFERENCE-CUTOFF-REASON :TYPE KEYWORD :ALLOCATION :DYNAMIC)");
      defineFunctionObject("REGISTER-INFERENCE-CUTOFF", "(DEFUN REGISTER-INFERENCE-CUTOFF ((FRAME CONTROL-FRAME) (REASON KEYWORD)))", ((cpp_function_code)(&registerInferenceCutoff)), NULL);
      defineFunctionObject("CONTINUE-FAIL-PROOF", "(DEFUN (CONTINUE-FAIL-PROOF KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&continueFailProof)), NULL);
      defineMethodObject("(DEFMETHOD (CONTINUE-PARTIAL-FAIL-PROOF KEYWORD) ((SELF CONTROL-FRAME) (LASTMOVE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&ControlFrame::continuePartialFailProof))), NULL);
      defineFunctionObject("STARTUP-STRATEGIES", "(DEFUN STARTUP-STRATEGIES () :PUBLIC? TRUE)", ((cpp_function_code)(&startupStrategies)), NULL);
      { MethodSlot* function = lookupFunction(SYM_STRATEGIES_LOGIC_STARTUP_STRATEGIES);

        setDynamicSlotValue(function->dynamicSlots, SYM_STRATEGIES_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupStrategies"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFGLOBAL *PARALLEL-STRATEGIES* (LIST OF KEYWORD) (LIST :DISJUNCTIVE-IMPLICATION-INTRODUCTION :UNIVERSAL-INTRODUCTION :REFUTATION) :DOCUMENTATION \"List of strategies (keywords) that fork a parallel\ncontrol stack before executing.\")", &oPARALLEL_STRATEGIESo);
      defineGlobalVariableObject("(DEFGLOBAL *FAILED-GOAL-CUTOFFS* INTEGER 0)", &oFAILED_GOAL_CUTOFFSo);
      defineGlobalVariableObject("(DEFGLOBAL *SUCCEEDED-GOAL-CUTOFFS* INTEGER 0)", &oSUCCEEDED_GOAL_CUTOFFSo);
      defineGlobalVariableObject("(DEFGLOBAL *PL-ANONYMOUS-MODULE* MODULE (GET-STELLA-MODULE \"PL-ANONYMOUS\" TRUE))", &oPL_ANONYMOUS_MODULEo);
      defineExplanationPhrase(KWD_STRATEGIES_CONSTANT_PROPOSITION, KWD_STRATEGIES_TECHNICAL, "trivially", 0);
      defineExplanationPhrase(KWD_STRATEGIES_CONSTANT_PROPOSITION, KWD_STRATEGIES_LAY, "trivially", 0);
    }
  }
}

Keyword* KWD_STRATEGIES_DOWN = NULL;

Keyword* KWD_STRATEGIES_MOVE_DOWN = NULL;

Keyword* KWD_STRATEGIES_UP_TRUE = NULL;

Keyword* KWD_STRATEGIES_UP_FAIL = NULL;

Keyword* KWD_STRATEGIES_FAILURE = NULL;

Keyword* KWD_STRATEGIES_FINAL_SUCCESS = NULL;

Keyword* KWD_STRATEGIES_CONTINUING_SUCCESS = NULL;

Keyword* KWD_STRATEGIES_GOAL_TREE = NULL;

Symbol* SYM_STRATEGIES_LOGIC_JUSTIFICATION = NULL;

Keyword* KWD_STRATEGIES_TERMINAL_FAILURE = NULL;

Symbol* SYM_STRATEGIES_LOGIC_INFERENCE_CUTOFF_REASON = NULL;

Symbol* SYM_STRATEGIES_STELLA_ITERATOR = NULL;

Symbol* SYM_STRATEGIES_LOGIC_ANTECEDENTS_RULE = NULL;

Symbol* SYM_STRATEGIES_LOGIC_PROOF_ADJUNCT = NULL;

Keyword* KWD_STRATEGIES_PARALLEL_STRATEGIES = NULL;

Keyword* KWD_STRATEGIES_SELECT_PARALLEL_THREAD = NULL;

Keyword* KWD_STRATEGIES_FAIL = NULL;

Keyword* KWD_STRATEGIES_TRUE = NULL;

Keyword* KWD_STRATEGIES_STRATEGIES = NULL;

Symbol* SYM_STRATEGIES_LOGIC_DESCRIPTION = NULL;

Keyword* KWD_STRATEGIES_MOVE_IN_PLACE = NULL;

Keyword* KWD_STRATEGIES_TIME_OUT = NULL;

Keyword* KWD_STRATEGIES_SPECIALIST = NULL;

Keyword* KWD_STRATEGIES_ANTECEDENTS = NULL;

Keyword* KWD_STRATEGIES_CLUSTERED_CONJUNCTION = NULL;

Keyword* KWD_STRATEGIES_CONDITIONAL_ANTECEDENT = NULL;

Keyword* KWD_STRATEGIES_DISJUNCTIVE_IMPLICATION_INTRODUCTION = NULL;

Keyword* KWD_STRATEGIES_ATOMIC_GOAL = NULL;

Keyword* KWD_STRATEGIES_DUMMY_JUSTIFICATION = NULL;

Keyword* KWD_STRATEGIES_LOOKUP_GOAL_CACHES = NULL;

Symbol* SYM_STRATEGIES_LOGIC_CHECK_FOR_CACHED_GOALSp = NULL;

Keyword* KWD_STRATEGIES_DUPLICATE_GOALS = NULL;

Keyword* KWD_STRATEGIES_MANUFACTURE_SKOLEM = NULL;

Surrogate* SGT_STRATEGIES_PL_KERNEL_KB_TOTAL = NULL;

Keyword* KWD_STRATEGIES_LOOKUP_ASSERTIONS = NULL;

Keyword* KWD_STRATEGIES_SCAN_PROPOSITIONS = NULL;

Keyword* KWD_STRATEGIES_SCAN_PARTIAL_PROPOSITIONS = NULL;

Keyword* KWD_STRATEGIES_SCAN_COLLECTION = NULL;

Keyword* KWD_STRATEGIES_SHALLOW_DISPROOF = NULL;

Keyword* KWD_STRATEGIES_SCAN_FOR_VALUE_CLASH = NULL;

Keyword* KWD_STRATEGIES_ALL_SUBGOAL_STRATEGIES = NULL;

Keyword* KWD_STRATEGIES_FULL_SUBQUERY = NULL;

Keyword* KWD_STRATEGIES_GOAL_COMPLEMENT = NULL;

Keyword* KWD_STRATEGIES_FORWARD_GOALS = NULL;

Keyword* KWD_STRATEGIES_IMPLIES = NULL;

Keyword* KWD_STRATEGIES_CONTAINED_BY = NULL;

Keyword* KWD_STRATEGIES_EQUIVALENCE = NULL;

Keyword* KWD_STRATEGIES_UNIVERSAL_INTRODUCTION = NULL;

Keyword* KWD_STRATEGIES_SUBSUMPTION_TEST = NULL;

Keyword* KWD_STRATEGIES_REFUTATION = NULL;

Keyword* KWD_STRATEGIES_STRATEGY = NULL;

Keyword* KWD_STRATEGIES_DEBUG = NULL;

Keyword* KWD_STRATEGIES_SUCCESS = NULL;

Symbol* SYM_STRATEGIES_LOGIC_LATEST_POSITIVE_SCORE = NULL;

Keyword* KWD_STRATEGIES_GOAL_CACHES = NULL;

Keyword* KWD_STRATEGIES_ISA = NULL;

Keyword* KWD_STRATEGIES_INITIALIZE = NULL;

Keyword* KWD_STRATEGIES_FUNCTION = NULL;

Surrogate* SGT_STRATEGIES_LOGIC_WHYNOT_PARTIAL_MATCH = NULL;

Keyword* KWD_STRATEGIES_NOT = NULL;

Surrogate* SGT_STRATEGIES_PL_KERNEL_KB_MEMBER_OF = NULL;

Surrogate* SGT_STRATEGIES_STELLA_LIST = NULL;

Keyword* KWD_STRATEGIES_FORWARD = NULL;

Keyword* KWD_STRATEGIES_DUPLICATE_ = NULL;

Keyword* KWD_STRATEGIES_BACKWARD = NULL;

Symbol* SYM_STRATEGIES_LOGIC_BACKWARD_ONLYp = NULL;

Symbol* SYM_STRATEGIES_LOGIC_FORWARD_ONLYp = NULL;

Surrogate* SGT_STRATEGIES_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_STRATEGIES_STELLA_CONS_ITERATOR = NULL;

Keyword* KWD_STRATEGIES_FORWARD_RULE = NULL;

Surrogate* SGT_STRATEGIES_LOGIC_CONDITIONAL_ANTECEDENT_PROOF_ADJUNCT = NULL;

Symbol* SYM_STRATEGIES_LOGIC_PROVABLE_RULE = NULL;

Symbol* SYM_STRATEGIES_LOGIC_GOAL = NULL;

Symbol* SYM_STRATEGIES_STELLA_PHASE = NULL;

Keyword* KWD_STRATEGIES_ORIGINAL_GOAL = NULL;

Surrogate* SGT_STRATEGIES_STELLA_THING = NULL;

Surrogate* SGT_STRATEGIES_STELLA_LITERAL_WRAPPER = NULL;

Surrogate* SGT_STRATEGIES_LOGIC_PROPOSITION = NULL;

Symbol* SYM_STRATEGIES_LOGIC_COMPLEMENT_DESCRIPTION = NULL;

Symbol* SYM_STRATEGIES_LOGIC_CONTAINED_BY = NULL;

Surrogate* SGT_STRATEGIES_LOGIC_NAMED_DESCRIPTION = NULL;

Symbol* SYM_STRATEGIES_STELLA_ISA = NULL;

Symbol* SYM_STRATEGIES_STELLA_PREDICATE = NULL;

Keyword* KWD_STRATEGIES_LOCAL = NULL;

Symbol* SYM_STRATEGIES_LOGIC_BACK = NULL;

Keyword* KWD_STRATEGIES_POPPED = NULL;

Symbol* SYM_STRATEGIES_LOGIC_EXTERNAL_VARIABLES = NULL;

Surrogate* SGT_STRATEGIES_LOGIC_CLUSTERED_CONJUNCTION_PROOF_ADJUNCT = NULL;

Symbol* SYM_STRATEGIES_LOGIC_CLUSTER_FRAMES = NULL;

Keyword* KWD_STRATEGIES_AND = NULL;

Keyword* KWD_STRATEGIES_PREDICATE = NULL;

Symbol* SYM_STRATEGIES_LOGIC_MONOTONICp = NULL;

Symbol* SYM_STRATEGIES_LOGIC_HYPOTHESIZED_INSTANCEp = NULL;

Symbol* SYM_STRATEGIES_LOGIC_IO_VARIABLES = NULL;

Keyword* KWD_STRATEGIES_ITERATIVE_FORALL = NULL;

Keyword* KWD_STRATEGIES_NORMAL = NULL;

Keyword* KWD_STRATEGIES_CONSTANT_PROPOSITION = NULL;

Keyword* KWD_STRATEGIES_TECHNICAL = NULL;

Keyword* KWD_STRATEGIES_LAY = NULL;

Symbol* SYM_STRATEGIES_LOGIC_STARTUP_STRATEGIES = NULL;

Symbol* SYM_STRATEGIES_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
