//  -*- Mode: C++ -*-

// propagate.cc

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

PropagationEnvironment* newPropagationEnvironment() {
  { PropagationEnvironment* self = NULL;

    self = new PropagationEnvironment();
    self->elaboratedObjects = newHashSet();
    self->deferredDefaultPropositions = list(0);
    self->forwardChainingSet = newHashSet();
    self->forwardChainingQueue = list(0);
    self->evaluationStates = newKeyValueMap();
    self->evaluationQueue = list(0);
    return (self);
  }
}

Surrogate* PropagationEnvironment::primaryType() {
  { PropagationEnvironment* self = this;

    return (SGT_PROPAGATE_LOGIC_PROPAGATION_ENVIRONMENT);
  }
}

Object* accessPropagationEnvironmentSlotValue(PropagationEnvironment* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PROPAGATE_LOGIC_EVALUATION_QUEUE) {
    if (setvalueP) {
      self->evaluationQueue = ((List*)(value));
    }
    else {
      value = self->evaluationQueue;
    }
  }
  else if (slotname == SYM_PROPAGATE_LOGIC_EVALUATION_STATES) {
    if (setvalueP) {
      self->evaluationStates = ((KeyValueMap*)(value));
    }
    else {
      value = self->evaluationStates;
    }
  }
  else if (slotname == SYM_PROPAGATE_LOGIC_FORWARD_CHAINING_QUEUE) {
    if (setvalueP) {
      self->forwardChainingQueue = ((List*)(value));
    }
    else {
      value = self->forwardChainingQueue;
    }
  }
  else if (slotname == SYM_PROPAGATE_LOGIC_FORWARD_CHAINING_SET) {
    if (setvalueP) {
      self->forwardChainingSet = ((HashSet*)(value));
    }
    else {
      value = self->forwardChainingSet;
    }
  }
  else if (slotname == SYM_PROPAGATE_LOGIC_DEFERRED_DEFAULT_PROPOSITIONS) {
    if (setvalueP) {
      self->deferredDefaultPropositions = ((List*)(value));
    }
    else {
      value = self->deferredDefaultPropositions;
    }
  }
  else if (slotname == SYM_PROPAGATE_LOGIC_ELABORATED_OBJECTS) {
    if (setvalueP) {
      self->elaboratedObjects = ((HashSet*)(value));
    }
    else {
      value = self->elaboratedObjects;
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

void printPropagationEnvironmentStats(PropagationEnvironment* self) {
  if (!((boolean)(self))) {
    self = getPropagationEnvironment(oCONTEXTo);
  }
  std::cout << "Propagation environment stats:" << std::endl;
  std::cout << "  " << self->evaluationQueue->length() << " propositions in evaluation-queue" << std::endl;
  std::cout << "  " << self->forwardChainingSet->length() << " propositions in forward-chaining-queue" << std::endl;
  std::cout << "  " << self->elaboratedObjects->length() << " objects elaborated" << std::endl;
}

PropagationEnvironment* getPropagationEnvironment(Context* self) {
  { PropagationEnvironment* environment = ((PropagationEnvironment*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPAGATE_LOGIC_PROPAGATION_ENVIRONMENT, NULL)));

    if (!((boolean)(environment))) {
      environment = newPropagationEnvironment();
      setDynamicSlotValue(self->dynamicSlots, SYM_PROPAGATE_LOGIC_PROPAGATION_ENVIRONMENT, environment, NULL);
    }
    return (environment);
  }
}

void unlinkPropagationEnvironment(Context* self) {
  setDynamicSlotValue(self->dynamicSlots, SYM_PROPAGATE_LOGIC_PROPAGATION_ENVIRONMENT, NULL, NULL);
}

void PropagationEnvironment::deferDefaultProposition(Proposition* proposition) {
  { PropagationEnvironment* self = this;

    self->deferredDefaultPropositions->insert(proposition);
  }
}

void PropagationEnvironment::clearPropagationQueues() {
  { PropagationEnvironment* self = this;

    self->evaluationQueue->clear();
    self->forwardChainingQueue->clear();
  }
}

PropagationEnvironment* PropagationEnvironment::copy() {
  { PropagationEnvironment* self = this;

    { PropagationEnvironment* copy = newPropagationEnvironment();

      copy->evaluationQueue = self->evaluationQueue->copy();
      { Proposition* prop = NULL;
        Keyword* state = NULL;
        DictionaryIterator* iter000 = ((DictionaryIterator*)(self->evaluationStates->allocateIterator()));

        for  (; iter000->nextP(); ) {
          prop = ((Proposition*)(iter000->key));
          state = ((Keyword*)(iter000->value));
          copy->evaluationStates->insertAt(prop, state);
        }
      }
      copy->forwardChainingQueue = self->forwardChainingQueue->copy();
      { Proposition* prop = NULL;
        DictionaryIterator* iter001 = ((DictionaryIterator*)(self->forwardChainingSet->allocateIterator()));

        for (; iter001->nextP(); ) {
          prop = ((Proposition*)(iter001->value));
          copy->forwardChainingSet->insert(prop);
        }
      }
      copy->deferredDefaultPropositions = self->deferredDefaultPropositions->copy();
      { Object* obj = NULL;
        DictionaryIterator* iter002 = ((DictionaryIterator*)(self->elaboratedObjects->allocateIterator()));

        for (; iter002->nextP(); ) {
          obj = iter002->value;
          copy->elaboratedObjects->insert(obj);
        }
      }
      return (copy);
    }
  }
}

// True if we are inside of 'react-to-kb-update'.
DEFINE_STELLA_SPECIAL(oFILLINGCONSTRAINTPROPAGATIONQUEUESpo, boolean , false);

// True if we are propagating strict inferences, and
// posting derived default propositions to temporary queues.
DEFINE_STELLA_SPECIAL(oDEFERINGDEFAULTFORWARDINFERENCESpo, boolean , false);

Keyword* evaluationState(Proposition* proposition) {
  // Return :POSTED if `proposition' is on the evaluation queue
  // for *context*, :EVALUATED if has been evaluated, or NULL if it has never been evaluated.
  if (descriptionModeP()) {
    return (NULL);
  }
  else {
    return (((Keyword*)(getPropagationEnvironment(oCONTEXTo)->evaluationStates->lookup(proposition))));
  }
}

void evaluationStateSetter(Proposition* proposition, Keyword* state) {
  // Record the evaluation `state' of 'proposition'.
  if (!(descriptionModeP())) {
    getPropagationEnvironment(oCONTEXTo)->evaluationStates->insertAt(proposition, state);
  }
}

void postForEvaluation(Proposition* self, Context* world) {
  // Push 'self' onto the evaluation queue (unless it's already there).
  if (!((boolean)(world))) {
    world = oCONTEXTo;
  }
  if (!oFILLINGCONSTRAINTPROPAGATIONQUEUESpo) {
    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, world);
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      evaluateProposition(self);
      return;
    }
  }
  { PropagationEnvironment* environment = getPropagationEnvironment(world);

    if (!(((Keyword*)(environment->evaluationStates->lookup(self))) == KWD_PROPAGATE_POSTED)) {
      environment->evaluationQueue->insert(self);
      environment->evaluationStates->insertAt(self, KWD_PROPAGATE_POSTED);
    }
  }
}

Cons* helpCollectForwardRules(Description* description, KeyValueList* rules, KeyValueList* indices, boolean toucheddefaultP, List* beenthere) {
  if (!((boolean)(rules))) {
    rules = newKeyValueList();
  }
  if (!((boolean)(indices))) {
    indices = newKeyValueList();
  }
  if (!((boolean)(beenthere))) {
    beenthere = newList();
  }
  beenthere->insert(description);
  { ForwardChainingIndex* index = NULL;
    Cons* iter000 = description->forwardChainingIndices_reader()->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      index = ((ForwardChainingIndex*)(iter000->value));
      if ((!index->masterRule->deletedP()) &&
          trueP(index->masterRule)) {
        indices->insertAt(index, (toucheddefaultP ? TRUE_WRAPPER : FALSE_WRAPPER));
      }
    }
  }
  { Proposition* p = NULL;
    Cons* iter001 = applicableRulesOfDescription(description, KWD_PROPAGATE_FORWARD, true);

    for (; !(iter001 == NIL); iter001 = iter001->rest) {
      p = ((Proposition*)(iter001->value));
      if (!((BooleanWrapper*)(dynamicSlotValue(p->dynamicSlots, SYM_PROPAGATE_LOGIC_BACKWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue) {
        { Object* consequent = (p->arguments->theArray)[1];

          { Surrogate* testValue000 = safePrimaryType(consequent);

            if (subtypeOfP(testValue000, SGT_PROPAGATE_LOGIC_NAMED_DESCRIPTION)) {
              { Object* consequent000 = consequent;
                NamedDescription* consequent = ((NamedDescription*)(consequent000));

                { Object* super = valueOf(consequent);

                  if (defaultTrueP(p)) {
                    toucheddefaultP = true;
                  }
                  if (((BooleanWrapper*)(dynamicSlotValue(p->dynamicSlots, SYM_PROPAGATE_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue ||
                      (!(classP(description) == classP(super)))) {
                    rules->insertAt(p, (toucheddefaultP ? TRUE_WRAPPER : FALSE_WRAPPER));
                  }
                  if (!beenthere->memberP(super)) {
                    helpCollectForwardRules(((Description*)(super)), rules, indices, toucheddefaultP, beenthere);
                  }
                }
              }
            }
            else if (subtypeOfP(testValue000, SGT_PROPAGATE_LOGIC_DESCRIPTION)) {
              { Object* consequent001 = consequent;
                Description* consequent = ((Description*)(consequent001));

                rules->insertAt(p, (toucheddefaultP ? TRUE_WRAPPER : FALSE_WRAPPER));
              }
            }
            else {
            }
          }
        }
      }
    }
  }
  return (cons(rules, cons(indices, NIL)));
}

KeyValueList* collectForwardChainingRules(Description* description, KeyValueList*& _Return1) {
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_PROPAGATE_LOGIC_F_COLLECT_FORWARD_CHAINING_RULES_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_PROPAGATE_LOGIC_F_COLLECT_FORWARD_CHAINING_RULES_MEMO_TABLE_000, "(:MAX-VALUES 500 :TIMESTAMPS (:META-KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_PROPAGATE_LOGIC_F_COLLECT_FORWARD_CHAINING_RULES_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), description, oCONTEXTo, MEMOIZED_NULL_VALUE, NULL, -1);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = helpCollectForwardRules(description, NULL, NULL, false, NULL);
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Cons* rules = ((Cons*)(memoizedValue000));

      _Return1 = ((KeyValueList*)(rules->rest->value));
      return (((KeyValueList*)(rules->value)));
    }
  }
}

boolean hasForwardChainingRulesP(Description* description, Proposition* proposition) {
  if (falseP(proposition)) {
    description = getInferableComplementDescription(description);
    if (!((boolean)(description))) {
      return (false);
    }
  }
  { KeyValueList* rules = NULL;
    KeyValueList* indices = NULL;

    rules = collectForwardChainingRules(description, indices);
    return (rules->nonEmptyP() ||
        indices->nonEmptyP());
  }
}

void postToForwardChainingQueue(Proposition* self, World* world) {
  if (unknownP(self) &&
      (!(self->kind == KWD_PROPAGATE_FUNCTION))) {
    return;
  }
  if (!((boolean)(world))) {
    world = ((World*)(oCONTEXTo));
  }
  { PropagationEnvironment* environment = getPropagationEnvironment(world);
    NamedDescription* description = NULL;

    { Keyword* testValue000 = self->kind;

      if ((testValue000 == KWD_PROPAGATE_ISA) ||
          ((testValue000 == KWD_PROPAGATE_PREDICATE) ||
           (testValue000 == KWD_PROPAGATE_FUNCTION))) {
        if (environment->forwardChainingSet->memberP(self)) {
          return;
        }
        description = getDescription(((Surrogate*)(self->operatoR)));
        if (((boolean)(description)) &&
            hasForwardChainingRulesP(description, self)) {
          environment->forwardChainingSet->insert(self);
          environment->forwardChainingQueue->insert(self);
        }
      }
      else {
      }
    }
  }
}

// Collect goes-true propositions produced by forward
// chaining.
DEFINE_STELLA_SPECIAL(oCOLLECTFORWARDPROPOSITIONSo, Cons* , NULL);

int Skolem::skolemGenerationCount_reader() {
  { Skolem* self = this;

    { int answer = ((IntegerWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPAGATE_LOGIC_SKOLEM_GENERATION_COUNT, NULL_INTEGER_WRAPPER)))->wrapperValue;

      if (answer == NULL_INTEGER) {
        return (0);
      }
      else {
        return (answer);
      }
    }
  }
}

int oMAX_SKOLEM_GENERATION_COUNTo = 3;

void applyRuleConsequentToVector(Description* consequent, Vector* arguments, Proposition* rule, Description* triggerdescription, Proposition* triggerproposition, boolean toucheddefaultP, Justification* bcJustification) {
  triggerdescription = triggerdescription;
  { 
    BIND_STELLA_SPECIAL(oCOLLECTFORWARDPROPOSITIONSo, Cons*, NIL);
    { boolean toucheddefaultknowledgeP = defaultTrueP(triggerproposition) ||
          (defaultTrueP(rule) ||
           toucheddefaultP);
      Skolem* skolem = NULL;
      int skolemgenerationcount = 0;

      { Object* arg = NULL;
        Vector* vector000 = arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          arg = (vector000->theArray)[index000];
          if (skolemP(arg) &&
              (((Skolem*)(arg))->skolemGenerationCount_reader() > skolemgenerationcount)) {
            skolemgenerationcount = ((Skolem*)(arg))->skolemGenerationCount_reader();
            if (skolemgenerationcount >= oMAX_SKOLEM_GENERATION_COUNTo) {
              if (((boolean)(oTRACED_KEYWORDSo)) &&
                  oTRACED_KEYWORDSo->membP(KWD_PROPAGATE_PROPAGATE)) {
                std::cout << "*** cutting off forward skolemization on: " << triggerproposition << std::endl;
              }
              return;
            }
          }
        }
      }
      { 
        BIND_STELLA_SPECIAL(oQUERYITERATORo, QueryIterator*, NULL);
        BIND_STELLA_SPECIAL(oDONT_CHECK_FOR_DUPLICATE_PROPOSITIONSpo, boolean, false);
        inheritDescription(arguments, consequent, toucheddefaultknowledgeP);
      }
      if (traceKeywordP(KWD_PROPAGATE_PROPAGATE)) {
        traceForwardRule(rule, triggerproposition, oCOLLECTFORWARDPROPOSITIONSo);
      }
      { Proposition* p = NULL;
        Cons* iter000 = oCOLLECTFORWARDPROPOSITIONSo;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          p = ((Proposition*)(iter000->value));
          { Object* value000 = NULL;

            { Object* arg = NULL;
              Vector* vector001 = p->arguments;
              int index001 = 0;
              int length001 = vector001->length();

              for  (; index001 < length001; 
                    index001 = index001 + 1) {
                arg = (vector001->theArray)[index001];
                if (skolemP(arg)) {
                  value000 = arg;
                  break;
                }
              }
            }
            skolem = ((Skolem*)(value000));
          }
          if (((boolean)(skolem)) &&
              ((!((boolean)(skolem->definingProposition))) &&
               (!((BooleanWrapper*)(dynamicSlotValue(skolem->dynamicSlots, SYM_PROPAGATE_LOGIC_HYPOTHESIZED_INSTANCEp, FALSE_WRAPPER)))->wrapperValue))) {
            setDynamicSlotValue(skolem->dynamicSlots, SYM_PROPAGATE_LOGIC_SKOLEM_GENERATION_COUNT, wrapInteger(stella::integerMax(skolemgenerationcount + 1, skolem->skolemGenerationCount_reader())), NULL_INTEGER_WRAPPER);
          }
          recordForwardGoal(rule, arguments, p);
          recordForwardRuleJustification(consList(1, triggerproposition), rule, arguments, p, bcJustification);
        }
      }
    }
  }
}

void traceForwardRule(Proposition* rule, Proposition* trigger, Cons* consequents) {
  if (((boolean)(consequents)) &&
      (!(consequents == NIL))) {
    { int indent = 11;

      std::cout << "RUNNING FORWARD RULE:" << std::endl << "  TRIGGER: ";
      printFormula(trigger, indent);
      if (falseP(trigger)) {
        std::cout << ")";
      }
      std::cout << std::endl << "  RULE:    ";
      printFormula(rule, indent);
      std::cout << std::endl << "  RESULT:  ";
      if (!(consequents->rest == NIL)) {
        std::cout << "(" << stringifiedSurrogate(SGT_PROPAGATE_PL_KERNEL_KB_AND) << " ";
        indent = indent + 5;
      }
      { Proposition* c = NULL;
        Cons* iter000 = consequents;
        int i = NULL_INTEGER;
        int iter001 = 1;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          c = ((Proposition*)(iter000->value));
          i = iter001;
          if (i > 1) {
            std::cout << std::endl;
            { int i = NULL_INTEGER;
              int iter002 = 1;
              int upperBound000 = indent;
              boolean unboundedP000 = upperBound000 == NULL_INTEGER;

              for  (; unboundedP000 ||
                        (iter002 <= upperBound000); 
                    iter002 = iter002 + 1) {
                i = iter002;
                i = i;
                std::cout << " ";
              }
            }
          }
          printFormula(c, indent);
        }
      }
      if (!(consequents->rest == NIL)) {
        std::cout << ")";
        indent = indent - 5;
      }
      std::cout << std::endl;
    }
  }
}

void applyForwardRulesToVector(Description* triggerdescription, Vector* arguments, Proposition* triggerproposition) {
  { Vector* evaluatedargs = arguments;

    { Object* arg = NULL;
      Vector* vector000 = arguments;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter000 = 0;

      for  (; index000 < length000; 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        arg = (vector000->theArray)[index000];
        i = iter000;
        if (arg->deletedP()) {
          return;
        }
        else if (!eqlP(arg, valueOf(arg))) {
          if (arguments == evaluatedargs) {
            evaluatedargs = arguments->copy();
          }
          (evaluatedargs->theArray)[i] = (valueOf(arg));
        }
      }
    }
    arguments = evaluatedargs;
  }
  { KeyValueList* rules = NULL;
    KeyValueList* indices = NULL;

    rules = collectForwardChainingRules(triggerdescription, indices);
    { Proposition* r = NULL;
      BooleanWrapper* toucheddefaultP = NULL;
      KvCons* iter001 = rules->theKvList;

      for  (; ((boolean)(iter001)); 
            iter001 = iter001->rest) {
        r = ((Proposition*)(iter001->key));
        toucheddefaultP = ((BooleanWrapper*)(iter001->value));
        if (applicableForwardRuleP(r, arguments)) {
          applyRuleConsequentToVector(((Description*)((r->arguments->theArray)[1])), arguments, r, triggerdescription, triggerproposition, coerceWrappedBooleanToBoolean(toucheddefaultP), NULL);
        }
      }
    }
    { ForwardChainingIndex* fwdindex = NULL;
      BooleanWrapper* toucheddefaultP = NULL;
      KvCons* iter002 = indices->theKvList;

      for  (; ((boolean)(iter002)); 
            iter002 = iter002->rest) {
        fwdindex = ((ForwardChainingIndex*)(iter002->key));
        toucheddefaultP = ((BooleanWrapper*)(iter002->value));
        { Cons* inputargs = NIL;

          if (!(arguments->length() == fwdindex->forwardGoal->arguments->length())) {
            continue;
          }
          { Object* arg = NULL;
            Vector* vector001 = arguments;
            int index001 = 0;
            int length001 = vector001->length();
            Object* goalarg = NULL;
            Vector* vector002 = fwdindex->forwardGoal->arguments;
            int index002 = 0;
            int length002 = vector002->length();

            for  (; (index001 < length001) &&
                      (index002 < length002); 
                  index001 = index001 + 1,
                  index002 = index002 + 1) {
              arg = (vector001->theArray)[index001];
              goalarg = (vector002->theArray)[index002];
              if (variableP(goalarg)) {
                inputargs = cons(arg, inputargs);
              }
              else if (!eqlP(arg, valueOf(goalarg))) {
                inputargs = NULL;
                break;
              }
            }
          }
          if (!((boolean)(inputargs))) {
            continue;
          }
          { ConsIterator* it = fwdindex->inputBindings->allocateIterator();
            Object* arg = NULL;
            Cons* iter003 = inputargs->reverse();

            for  (; it->nextP() &&
                      (!(iter003 == NIL)); 
                  iter003 = iter003->rest) {
              arg = iter003->value;
                            it->valueSetter(arg);
            }
          }
        }
        { Cons* outputbindings = NULL;
          Cons* truthvalues = NULL;
          Cons* justifications = NULL;
          boolean traceforwardinferenceP = traceKeywordP(KWD_PROPAGATE_PROPAGATE);
          boolean tracegoaltreeP = traceforwardinferenceP &&
              traceKeywordP(KWD_PROPAGATE_GOAL_TREE);
          List* oldtracekeywords = oTRACED_KEYWORDSo;

          if (traceforwardinferenceP) {
            if (tracegoaltreeP) {
              std::cout << "Proving forward goal: " << fwdindex->queryBody << std::endl;
            }
          }
          else if (traceKeywordP(KWD_PROPAGATE_GOAL_TREE)) {
            oTRACED_KEYWORDSo = ((List*)(oTRACED_KEYWORDSo->copy()->remove(KWD_PROPAGATE_GOAL_TREE)));
          }
          { 
            BIND_STELLA_SPECIAL(oFILLINGCONSTRAINTPROPAGATIONQUEUESpo, boolean, true);
            outputbindings = applyCachedRetrieve(fwdindex->ioVariables, fwdindex->queryBody, fwdindex->inputBindings, consList(4, KWD_PROPAGATE_SINGLETONSp, FALSE_WRAPPER, KWD_PROPAGATE_INFERENCE_LEVEL, KWD_PROPAGATE_SHALLOW), fwdindex->cacheId, truthvalues, justifications);
          }
          if (tracegoaltreeP) {
            std::cout << "Done proving forward goal: " << fwdindex->queryBody << std::endl << std::endl;
          }
          oTRACED_KEYWORDSo = oldtracekeywords;
          { Object* ob = NULL;
            Cons* iter004 = outputbindings;
            Object* tv = NULL;
            Cons* iter005 = truthvalues;

            for  (; (!(iter004 == NIL)) &&
                      (!(iter005 == NIL)); 
                  iter004 = iter004->rest,
                  iter005 = iter005->rest) {
              ob = iter004->value;
              tv = iter005->value;
              { Object* head000 = justifications->value;

                justifications = justifications->rest;
                { Object* justification = head000;

                  applyRuleConsequentToVector(fwdindex->consequent, copyListToArgumentsVector(((Cons*)(ob))->listify()), fwdindex->masterRule, triggerdescription, triggerproposition, coerceWrappedBooleanToBoolean(toucheddefaultP) ||
                      (tv == DEFAULT_TRUE_TRUTH_VALUE), ((Justification*)(justification)));
                }
              }
            }
          }
        }
      }
    }
  }
}

boolean applicableForwardRuleP(Proposition* rule, Vector* arguments) {
  { Description* antecedentdescription = ((Description*)((rule->arguments->theArray)[0]));

    return (trueP(rule) &&
        (arguments->length() == antecedentdescription->ioVariables->length()));
  }
}

void Skolem::reactToInferenceUpdate() {
  { Skolem* self = this;

    { Object* derivedvalue = valueOf(self);
      Object* assertedvalue = NULL;

      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        assertedvalue = valueOf(self);
      }
      if (((boolean)(assertedvalue)) &&
          (!eqlP(assertedvalue, derivedvalue))) {
        equateValues(NULL, valueOf(assertedvalue), derivedvalue);
      }
      { Proposition* prop = NULL;
        Iterator* iter000 = unfilteredDependentPropositions(self, NULL)->allocateIterator();

        for (; iter000->nextP(); ) {
          prop = ((Proposition*)(iter000->value));
          postForEvaluation(prop, oCONTEXTo);
        }
      }
      if (oFILLINGCONSTRAINTPROPAGATIONQUEUESpo) {
        { Proposition* definingproposition = self->definingProposition;

          if (((boolean)(definingproposition))) {
            postToForwardChainingQueue(definingproposition, ((World*)(oCONTEXTo)));
          }
        }
      }
    }
  }
}

void Proposition::reactToInferenceUpdate() {
  { Proposition* self = this;

    postForEvaluation(self, oCONTEXTo);
    { Proposition* prop = NULL;
      Iterator* iter000 = self->dependentPropositions->allocateIterator();

      for (; iter000->nextP(); ) {
        prop = ((Proposition*)(iter000->value));
        postForEvaluation(prop, oCONTEXTo);
      }
    }
    if (oFILLINGCONSTRAINTPROPAGATIONQUEUESpo) {
      postToForwardChainingQueue(self, ((World*)(oCONTEXTo)));
    }
  }
}

void reactToKbUpdate(Context* context, Object* object) {
  { boolean skolemP = false;
    boolean propositionP = false;
    boolean metapropositionP = false;

    { Surrogate* testValue000 = safePrimaryType(object);

      if (subtypeOfP(testValue000, SGT_PROPAGATE_LOGIC_SKOLEM)) {
        { Object* object000 = object;
          Skolem* object = ((Skolem*)(object000));

          skolemP = true;
        }
      }
      else if (subtypeOfP(testValue000, SGT_PROPAGATE_LOGIC_PROPOSITION)) {
        { Object* object001 = object;
          Proposition* object = ((Proposition*)(object001));

          propositionP = true;
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    if (propositionP &&
        metaPropositionP(((Proposition*)(object)))) {
      metapropositionP = true;
    }
    bumpMemoizationTimestamp(KWD_PROPAGATE_KB_UPDATE);
    if (metapropositionP) {
      bumpMemoizationTimestamp(KWD_PROPAGATE_META_KB_UPDATE);
    }
    if (oINVISIBLEASSERTIONpo) {
      return;
    }
    else if (descriptionModeP()) {
      { 
        BIND_STELLA_SPECIAL(oFILLINGCONSTRAINTPROPAGATIONQUEUESpo, boolean, false);
        if (propositionP) {
          ((Proposition*)(object))->reactToInferenceUpdate();
        }
        else if (skolemP) {
          ((Skolem*)(object))->reactToInferenceUpdate();
        }
      }
      return;
    }
    else if (oFILLINGCONSTRAINTPROPAGATIONQUEUESpo) {
      if (propositionP) {
        ((Proposition*)(object))->reactToInferenceUpdate();
      }
      else if (skolemP) {
        ((Skolem*)(object))->reactToInferenceUpdate();
      }
      return;
    }
    { World* world = (metapropositionP ? lookupInferenceCache(context, KWD_PROPAGATE_META) : lookupConstraintPropagationWorld(context));

      if (((boolean)(world))) {
        { 
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, world);
          BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
          { 
            BIND_STELLA_SPECIAL(oFILLINGCONSTRAINTPROPAGATIONQUEUESpo, boolean, true);
            if (propositionP) {
              ((Proposition*)(object))->reactToInferenceUpdate();
            }
            else if (skolemP) {
              ((Skolem*)(object))->reactToInferenceUpdate();
            }
            executeConstraintPropagationQueues();
          }
        }
      }
    }
    if (isaP(context, SGT_PROPAGATE_STELLA_MODULE)) {
      { Context* child = NULL;
        Cons* iter000 = context->childContexts->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          child = ((Context*)(iter000->value));
          if (isaP(child, SGT_PROPAGATE_STELLA_MODULE)) {
            reactToKbUpdate(child, object);
          }
        }
      }
    }
  }
}

void PropagationEnvironment::executePropagationQueues() {
  { PropagationEnvironment* self = this;

    { 
      BIND_STELLA_SPECIAL(oINHIBITOBJECTFINALIZATIONpo, boolean, true);
      for (;;) {
        { List* queue = self->evaluationQueue;

          if (queue->nonEmptyP()) {
            self->evaluationQueue = newList();
            { Proposition* p = NULL;
              Cons* iter000 = queue->theConsList;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                p = ((Proposition*)(iter000->value));
                evaluateProposition(p);
              }
            }
          }
        }
        { List* queue = self->forwardChainingQueue;
          Description* description = NULL;

          if (queue->nonEmptyP()) {
            self->forwardChainingQueue = newList();
            { Proposition* proposition = NULL;
              Cons* iter001 = queue->theConsList;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                proposition = ((Proposition*)(iter001->value));
                                description = getDescription(((Surrogate*)(proposition->operatoR)));
                if (((boolean)(description)) &&
                    falseP(proposition)) {
                  description = getInferableComplementDescription(description);
                }
                if (((boolean)(description))) {
                  applyForwardRulesToVector(description, proposition->arguments, proposition);
                }
              }
            }
          }
        }
        if (self->evaluationQueue->emptyP() &&
            self->forwardChainingQueue->emptyP()) {
          return;
        }
      }
    }
  }
}

void executeConstraintPropagationQueues() {
  getPropagationEnvironment(oCONTEXTo)->executePropagationQueues();
}

void evaluateNewProposition(Proposition* self) {
  if (descriptionModeP() ||
      ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPAGATE_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue) {
    return;
  }
  { World* world = lookupConstraintPropagationWorld(oCONTEXTo);

    if (((boolean)(world))) {
      { 
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, world);
        evaluateProposition(self);
        if (!unknownP(self)) {
          if (((boolean)(oTRACED_KEYWORDSo)) &&
              oTRACED_KEYWORDSo->membP(KWD_PROPAGATE_PROPAGATE)) {
            std::cout << "evaluate-new-proposition:  " << self << std::endl;
          }
          { Proposition* prop = NULL;
            Iterator* iter000 = self->dependentPropositions->allocateIterator();

            for (; iter000->nextP(); ) {
              prop = ((Proposition*)(iter000->value));
              evaluateProposition(prop);
            }
          }
        }
      }
    }
  }
}

void evaluateAndProposition(Proposition* self) {
  { Vector* arguments = self->arguments;

    if (trueP(self)) {
      { Proposition* arg = NULL;
        Vector* vector000 = arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          arg = ((Proposition*)((vector000->theArray)[index000]));
          assignTruthValue(arg, ((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false))));
        }
      }
    }
    else if (falseP(self)) {
      { Proposition* onlyunboundarg = NULL;
        boolean toucheddefaultP = defaultFalseP(self);

        { Proposition* arg = NULL;
          Vector* vector001 = arguments;
          int index001 = 0;
          int length001 = vector001->length();

          for  (; index001 < length001; 
                index001 = index001 + 1) {
            arg = ((Proposition*)((vector001->theArray)[index001]));
            if (falseP(arg)) {
              return;
            }
            else if (unknownP(arg)) {
              if (((boolean)(onlyunboundarg))) {
                return;
              }
              onlyunboundarg = arg;
            }
            else if (defaultTrueP(arg)) {
              toucheddefaultP = true;
            }
          }
        }
        if (((boolean)(onlyunboundarg))) {
          assignTruthValue(onlyunboundarg, defaultifyTruthValue(false, toucheddefaultP));
        }
        else {
          assignTruthValue(self, defaultifyTruthValue(true, toucheddefaultP));
        }
      }
    }
    else {
      { boolean unboundargP = false;
        boolean toucheddefaultP = false;

        { Proposition* arg = NULL;
          Vector* vector002 = arguments;
          int index002 = 0;
          int length002 = vector002->length();

          for  (; index002 < length002; 
                index002 = index002 + 1) {
            arg = ((Proposition*)((vector002->theArray)[index002]));
            if (falseP(arg)) {
              if (defaultFalseP(arg)) {
                assignTruthValue(self, DEFAULT_FALSE_TRUTH_VALUE);
              }
              else {
                {
                  assignTruthValue(self, FALSE_WRAPPER);
                  return;
                }
              }
            }
            else if (unknownP(arg)) {
              unboundargP = true;
            }
            else if (defaultTrueP(arg)) {
              toucheddefaultP = true;
            }
          }
        }
        if ((!unboundargP) &&
            (!defaultFalseP(self))) {
          assignTruthValue(self, defaultifyTruthValue(true, toucheddefaultP));
        }
      }
    }
  }
}

void evaluateOrProposition(Proposition* self) {
  { Vector* arguments = self->arguments;

    if (falseP(self)) {
      { Proposition* arg = NULL;
        Vector* vector000 = arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          arg = ((Proposition*)((vector000->theArray)[index000]));
          assignTruthValue(arg, ((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false))));
        }
      }
    }
    else if (trueP(self)) {
      { Proposition* onlyunboundarg = NULL;
        boolean toucheddefaultP = defaultTrueP(self);

        { Proposition* arg = NULL;
          Vector* vector001 = arguments;
          int index001 = 0;
          int length001 = vector001->length();

          for  (; index001 < length001; 
                index001 = index001 + 1) {
            arg = ((Proposition*)((vector001->theArray)[index001]));
            if (trueP(arg)) {
              return;
            }
            else if (unknownP(arg)) {
              if (((boolean)(onlyunboundarg))) {
                return;
              }
              onlyunboundarg = arg;
            }
            else if (defaultFalseP(arg)) {
              toucheddefaultP = true;
            }
          }
        }
        if (((boolean)(onlyunboundarg))) {
          assignTruthValue(onlyunboundarg, defaultifyTruthValue(true, toucheddefaultP));
        }
        else {
          assignTruthValue(self, defaultifyTruthValue(false, toucheddefaultP));
        }
      }
    }
    else {
      { boolean unboundargP = false;
        boolean toucheddefaultP = false;

        { Proposition* arg = NULL;
          Vector* vector002 = arguments;
          int index002 = 0;
          int length002 = vector002->length();

          for  (; index002 < length002; 
                index002 = index002 + 1) {
            arg = ((Proposition*)((vector002->theArray)[index002]));
            if (trueP(arg)) {
              if (defaultTrueP(arg)) {
                assignTruthValue(self, DEFAULT_TRUE_TRUTH_VALUE);
              }
              else {
                {
                  assignTruthValue(self, TRUE_WRAPPER);
                  return;
                }
              }
            }
            else if (unknownP(arg)) {
              unboundargP = true;
            }
            else if (defaultFalseP(arg)) {
              toucheddefaultP = true;
            }
          }
        }
        if ((!unboundargP) &&
            (!defaultTrueP(self))) {
          assignTruthValue(self, defaultifyTruthValue(false, toucheddefaultP));
        }
      }
    }
  }
}

void evaluateNotProposition(Proposition* self) {
  { Proposition* argument = ((Proposition*)((self->arguments->theArray)[0]));

    if (trueP(argument) ||
        falseP(argument)) {
      assignTruthValue(self, invertTruthValue(((TruthValue*)(accessInContext(argument->truthValue, argument->homeContext, false)))));
    }
    if (trueP(self) ||
        falseP(self)) {
      assignTruthValue(argument, invertTruthValue(((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false)))));
    }
  }
}

void evaluateEquivalentProposition(Proposition* self) {
  { Vector* arguments = self->arguments;
    Object* firstarg = innermostOf((arguments->theArray)[0]);
    Object* secondarg = innermostOf((arguments->theArray)[1]);

    if (trueP(self)) {
      if (defaultTrueP(self)) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "INTERNAL ERROR: DON'T KNOW YET HOW TO EQUATE THINGS BY DEFAULT." << std::endl;
      }
      { Cons* firstargtypes = allAssertedTypes(firstarg);
        Cons* secondargtypes = allAssertedTypes(secondarg);

        { NamedDescription* type1 = NULL;
          Cons* iter000 = firstargtypes;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            type1 = ((NamedDescription*)(iter000->value));
            { boolean foundP000 = false;

              { NamedDescription* type2 = NULL;
                Cons* iter001 = secondargtypes;

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  type2 = ((NamedDescription*)(iter001->value));
                  if (disjointTermsP(type1, type2)) {
                    foundP000 = true;
                    break;
                  }
                }
              }
              if (foundP000) {
                signalUnificationClash(self, firstarg, secondarg);
              }
            }
          }
        }
      }
      equateValues(self, firstarg, secondarg);
    }
    else if (eqlP(firstarg, secondarg)) {
      assignTruthValue(self, TRUE_WRAPPER);
    }
    else if ((!skolemP(firstarg)) &&
        (!skolemP(secondarg))) {
      assignTruthValue(self, FALSE_WRAPPER);
    }
  }
}

void equateEquivalentFunctionPropositions(Proposition* self) {
  { Surrogate* relationref = ((Surrogate*)(self->operatoR));
    int nofargs = self->arguments->length();
    List* candidatepropositions = newList();

    { Object* arg = NULL;
      Vector* vector000 = self->arguments;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter000 = 1;

      for  (; index000 < length000; 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        arg = (vector000->theArray)[index000];
        i = iter000;
        if (!(i == nofargs)) {
          { Surrogate* testValue000 = safePrimaryType(arg);

            if (subtypeOfP(testValue000, SGT_PROPAGATE_LOGIC_SKOLEM)) {
              { Object* arg000 = arg;
                Skolem* arg = ((Skolem*)(arg000));

                if (((boolean)(((Object*)(accessInContext(arg->variableValue, arg->homeContext, false))))) &&
                    isaP(((Object*)(accessInContext(arg->variableValue, arg->homeContext, false))), SGT_PROPAGATE_LOGIC_LOGIC_OBJECT)) {
                  { Proposition* prop = NULL;
                    Iterator* iter001 = unfilteredDependentPropositions(((Object*)(accessInContext(arg->variableValue, arg->homeContext, false))), relationref)->allocateIterator();

                    for (; iter001->nextP(); ) {
                      prop = ((Proposition*)(iter001->value));
                      if ((((Surrogate*)(prop->operatoR)) == relationref) &&
                          (!(prop == self))) {
                        candidatepropositions->insertNew(prop);
                      }
                    }
                  }
                }
                { LogicObject* invarg = NULL;
                  Cons* iter002 = arg->variableValueInverse_reader();

                  for (; !(iter002 == NIL); iter002 = iter002->rest) {
                    invarg = ((LogicObject*)(iter002->value));
                    { Proposition* prop = NULL;
                      Iterator* iter003 = unfilteredDependentPropositions(invarg, relationref)->allocateIterator();

                      for (; iter003->nextP(); ) {
                        prop = ((Proposition*)(iter003->value));
                        if ((((Surrogate*)(prop->operatoR)) == relationref) &&
                            (!(prop == self))) {
                          candidatepropositions->insertNew(prop);
                        }
                      }
                    }
                  }
                }
              }
            }
            else if (subtypeOfP(testValue000, SGT_PROPAGATE_LOGIC_LOGIC_OBJECT)) {
              { Object* arg001 = arg;
                LogicObject* arg = ((LogicObject*)(arg001));

                { LogicObject* invarg = NULL;
                  Cons* iter004 = arg->variableValueInverse_reader();

                  for (; !(iter004 == NIL); iter004 = iter004->rest) {
                    invarg = ((LogicObject*)(iter004->value));
                    { Proposition* prop = NULL;
                      Iterator* iter005 = unfilteredDependentPropositions(invarg, relationref)->allocateIterator();

                      for (; iter005->nextP(); ) {
                        prop = ((Proposition*)(iter005->value));
                        if ((((Surrogate*)(prop->operatoR)) == relationref) &&
                            (!(prop == self))) {
                          candidatepropositions->insertNew(prop);
                        }
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
    { Proposition* prop = NULL;
      Cons* iter006 = candidatepropositions->theConsList;

      for (; !(iter006 == NIL); iter006 = iter006->rest) {
        prop = ((Proposition*)(iter006->value));
        { boolean alwaysP000 = true;

          { Object* arg1 = NULL;
            Vector* vector001 = self->arguments;
            int index001 = 0;
            int length001 = vector001->length();
            Object* arg2 = NULL;
            Vector* vector002 = prop->arguments;
            int index002 = 0;
            int length002 = vector002->length();
            int i = NULL_INTEGER;
            int iter007 = 1;

            for  (; (index001 < length001) &&
                      (index002 < length002); 
                  index001 = index001 + 1,
                  index002 = index002 + 1,
                  iter007 = iter007 + 1) {
              arg1 = (vector001->theArray)[index001];
              arg2 = (vector002->theArray)[index002];
              i = iter007;
              if (!(i == nofargs)) {
                if (!eqlP(innermostOf(arg1), innermostOf(arg2))) {
                  alwaysP000 = false;
                  break;
                }
              }
            }
          }
          if (alwaysP000) {
            equateValues(self, innermostOf(self->arguments->last()), innermostOf(prop->arguments->last()));
          }
        }
      }
    }
    candidatepropositions->free();
  }
}

void evaluateFunctionProposition(Proposition* self) {
  if (isaP(self->operatoR, SGT_PROPAGATE_STELLA_SYMBOL)) {
    return;
  }
  equateEquivalentFunctionPropositions(self);
  { NamedDescription* description = getDescription(((Surrogate*)(self->operatoR)));
    MethodSlot* computation = lookupConstraintFunction(description);
    Object* storedvalue = NULL;
    Object* computedvalue = NULL;
    int missingvalueindex = -1;

    if (((boolean)(computation))) {
      computedvalue = computeSimpleRelationConstraint(self, computation, false, missingvalueindex);
      if (((boolean)(computedvalue))) {
        if (missingvalueindex == -1) {
          assignTruthValue(self, computedvalue);
          return;
        }
        storedvalue = valueOf((self->arguments->theArray)[missingvalueindex]);
        if (!eqlP(computedvalue, storedvalue)) {
          equateValues(self, computedvalue, storedvalue);
        }
      }
      return;
    }
    computation = lookupComputationFunction(description);
    if (((boolean)(computation))) {
      computedvalue = computeRelationValue(self, computation, false);
      if (((boolean)(computedvalue))) {
        computedvalue = evaluateTerm(computedvalue);
      }
      storedvalue = valueOf((self->arguments->theArray)[(self->arguments->length() - 1)]);
      if ((!eqlP(computedvalue, storedvalue)) &&
          ((boolean)(computedvalue))) {
        equateValues(self, computedvalue, storedvalue);
      }
    }
  }
}

void evaluatePredicateProposition(Proposition* self) {
  { int dummy1;

    { NamedDescription* description = getDescription(((Surrogate*)(self->operatoR)));
      MethodSlot* computation = lookupConstraintFunction(description);
      boolean successP = false;

      if (((boolean)(computation))) {
        successP = eqlP(computeSimpleRelationConstraint(self, computation, false, dummy1), TRUE_WRAPPER);
        assignTruthValue(self, (successP ? TRUE_WRAPPER : FALSE_WRAPPER));
        return;
      }
      computation = lookupComputationFunction(description);
      if (((boolean)(computation))) {
        successP = eqlP(computeRelationValue(self, computation, false), TRUE_WRAPPER);
        assignTruthValue(self, (successP ? TRUE_WRAPPER : FALSE_WRAPPER));
      }
    }
  }
}

void evaluateProposition(Proposition* self) {
  // Evaluate 'self' against its arguments, possibly resulting in
  // the setting or changing of its truth value.
  evaluationStateSetter(self, KWD_PROPAGATE_EVALUATED);
  { Keyword* testValue000 = self->kind;

    if (testValue000 == KWD_PROPAGATE_AND) {
      evaluateAndProposition(self);
    }
    else if (testValue000 == KWD_PROPAGATE_OR) {
      evaluateOrProposition(self);
    }
    else if (testValue000 == KWD_PROPAGATE_NOT) {
      evaluateNotProposition(self);
    }
    else if (testValue000 == KWD_PROPAGATE_EQUIVALENT) {
      evaluateEquivalentProposition(self);
    }
    else if (testValue000 == KWD_PROPAGATE_ISA) {
    }
    else if ((testValue000 == KWD_PROPAGATE_FUNCTION) ||
        (testValue000 == KWD_PROPAGATE_PREDICATE)) {
      { NamedDescription* description = getDescription(((Surrogate*)(self->operatoR)));
        cpp_function_code evaluator = lookupEvaluator(description);

        if (evaluator != NULL) {
          ((void  (*) (Proposition*))evaluator)(self);
        }
        else if (self->kind == KWD_PROPAGATE_PREDICATE) {
          evaluatePredicateProposition(self);
        }
        else {
          evaluateFunctionProposition(self);
        }
      }
    }
    else {
    }
  }
}

void LogicObject::markAsIncoherent() {
  { LogicObject* self = this;

  }
}

void Skolem::markAsIncoherent() {
  { Skolem* self = this;

    if (((boolean)(self->definingProposition))) {
      { Object* firstarg = (self->definingProposition->arguments->theArray)[0];

        if (subtypeOfP(safePrimaryType(firstarg), SGT_PROPAGATE_LOGIC_LOGIC_OBJECT)) {
          { Object* firstarg000 = firstarg;
            LogicObject* firstarg = ((LogicObject*)(firstarg000));

            firstarg->markAsIncoherent();
            return;
          }
        }
        else {
        }
      }
    }
  }
}

// If TRUE, ensures that forward propagation has
// been applied to each instance 'touched' during a query.
boolean oJUST_IN_TIME_FORWARD_INFERENCEpo = true;

// Collects clash exceptions that occur during inference.
List* oCLASH_EXCEPTIONSo = NULL;

void resetClashExceptions() {
  // Resets the collection of clash exceptions
  oCLASH_EXCEPTIONSo = newList();
}

boolean exceptionRecordMatchesContextP(ExceptionRecord* record) {
  return (record->context == oCONTEXTo);
}

void cullClashExceptions(Context* self) {
  { 
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, self);
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
    oCLASH_EXCEPTIONSo->removeIf(((cpp_function_code)(&exceptionRecordMatchesContextP)));
  }
}

void recursivelyReactToInferenceUpdate(Proposition* self) {
  self->reactToInferenceUpdate();
  { Object* arg = NULL;
    Vector* vector000 = self->arguments;
    int index000 = 0;
    int length000 = vector000->length();

    for  (; index000 < length000; 
          index000 = index000 + 1) {
      arg = (vector000->theArray)[index000];
      if (isaP(arg, SGT_PROPAGATE_LOGIC_PROPOSITION)) {
        recursivelyReactToInferenceUpdate(((Proposition*)(arg)));
      }
    }
  }
}

void elaborateMetaInstance(Object* self) {
  { Context* worldstate = getWorldState(oCONTEXTo);
    World* metaworld = getInferenceCache(worldstate, KWD_PROPAGATE_META);

    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, metaworld);
      elaborateInstance(self);
    }
  }
}

void elaborateInstance(Object* self) {
  if (oFILLINGCONSTRAINTPROPAGATIONQUEUESpo) {
    return;
  }
  if (oJUST_IN_TIME_FORWARD_INFERENCEpo) {
    if (subtypeOfP(safePrimaryType(self), SGT_PROPAGATE_LOGIC_LOGIC_OBJECT)) {
      { Object* self000 = self;
        LogicObject* self = ((LogicObject*)(self000));

        { PropagationEnvironment* environment = getPropagationEnvironment(oCONTEXTo);

          if (environment->elaboratedObjects->memberP(self)) {
            return;
          }
          if (((boolean)(oTRACED_KEYWORDSo)) &&
              oTRACED_KEYWORDSo->membP(KWD_PROPAGATE_ELABORATE)) {
            std::cout << " ELABORATING:  " << self << " in world " << oCONTEXTo << std::endl;
          }
          { 
            BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_PROPAGATE_EXTENSIONAL_ASSERTION);
            BIND_STELLA_SPECIAL(oINHIBITOBJECTFINALIZATIONpo, boolean, true);
            BIND_STELLA_SPECIAL(oQUERYITERATORo, QueryIterator*, NULL);
            try {
              { 
                BIND_STELLA_SPECIAL(oFILLINGCONSTRAINTPROPAGATIONQUEUESpo, boolean, true);
                postRelatedFacts(self, environment);
                evaluateReachableInequalities(self, list(0));
                { 
                  BIND_STELLA_SPECIAL(oDEFERINGDEFAULTFORWARDINFERENCESpo, boolean, true);
                  executeConstraintPropagationQueues();
                }
                { Proposition* p = NULL;
                  Cons* iter000 = environment->deferredDefaultPropositions->theConsList;

                  for (; !(iter000 == NIL); iter000 = iter000->rest) {
                    p = ((Proposition*)(iter000->value));
                    assignTruthValue(p, DEFAULT_TRUE_TRUTH_VALUE);
                  }
                }
                environment->deferredDefaultPropositions->clear();
                executeConstraintPropagationQueues();
              }
            }
            catch (Clash& _e) {
              Clash* e = &_e;

              { ExceptionRecord* self001 = newExceptionRecord();

                self001->exception = e;
                self001->context = oCONTEXTo;
                self001->module = oMODULEo;
                oCLASH_EXCEPTIONSo->push(self001);
              }
              *(STANDARD_ERROR->nativeStream) << exceptionMessage(e) << std::endl;
            }
          }
        }
      }
    }
    else {
    }
  }
}

void evaluateReachableInequalities(LogicObject* self, List* visitedlist) {
  { Proposition* p = NULL;
    Iterator* iter000 = allTrueDependentPropositions(self, SGT_PROPAGATE_PL_KERNEL_KB_INEQUALITY, true);

    for (; iter000->nextP(); ) {
      p = ((Proposition*)(iter000->value));
      postForEvaluation(p, oCONTEXTo);
      visitedlist->push(self);
      { Object* arg = NULL;
        Vector* vector000 = p->arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          arg = (vector000->theArray)[index000];
          if ((!visitedlist->memberP(arg)) &&
              isaP(arg, SGT_PROPAGATE_LOGIC_LOGIC_OBJECT)) {
            evaluateReachableInequalities(((LogicObject*)(arg)), visitedlist);
          }
        }
      }
    }
  }
}

void elaborateSurrogatesInProposition(Proposition* proposition) {
  if (oJUST_IN_TIME_FORWARD_INFERENCEpo) {
    { Keyword* testValue000 = proposition->kind;

      if ((testValue000 == KWD_PROPAGATE_PREDICATE) ||
          ((testValue000 == KWD_PROPAGATE_FUNCTION) ||
           (testValue000 == KWD_PROPAGATE_ISA))) {
        elaborateMetaInstance(getDescription(((Surrogate*)(proposition->operatoR))));
        { Object* arg = NULL;
          Vector* vector000 = proposition->arguments;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            arg = (vector000->theArray)[index000];
            if (isaP(arg, SGT_PROPAGATE_STELLA_SURROGATE)) {
              { Object* value = valueOf(arg);

                if (((boolean)(value))) {
                  elaborateInstance(value);
                }
              }
            }
          }
        }
      }
      else if ((testValue000 == KWD_PROPAGATE_AND) ||
          ((testValue000 == KWD_PROPAGATE_OR) ||
           ((testValue000 == KWD_PROPAGATE_NOT) ||
            ((testValue000 == KWD_PROPAGATE_EXISTS) ||
             (testValue000 == KWD_PROPAGATE_FORALL))))) {
        { Object* p = NULL;
          Vector* vector001 = proposition->arguments;
          int index001 = 0;
          int length001 = vector001->length();

          for  (; index001 < length001; 
                index001 = index001 + 1) {
            p = (vector001->theArray)[index001];
            elaborateSurrogatesInProposition(((Proposition*)(p)));
          }
        }
      }
      else {
      }
    }
  }
}

boolean followDependentPropositionArgumentP(Proposition* proposition, Object* argument) {
  if (proposition->kind == KWD_PROPAGATE_EQUIVALENT) {
    return (true);
  }
  if (subtypeOfP(safePrimaryType(argument), SGT_PROPAGATE_LOGIC_SKOLEM)) {
    { Object* argument000 = argument;
      Skolem* argument = ((Skolem*)(argument000));

      if (functionOutputSkolemP(argument)) {
        return (true);
      }
      { NamedDescription* relation = getDescription(proposition->operatoR);

        if (((boolean)(relation))) {
          if (computedTermP(relation)) {
            return (true);
          }
        }
      }
      return (!unfilteredDependentPropositions(argument, SGT_PROPAGATE_PL_KERNEL_KB_EQUIVALENT)->emptyP());
    }
  }
  else {
  }
  return (false);
}

boolean doNotElaborateP(Object* self, PropagationEnvironment* environment) {
  environment = environment;
  { Surrogate* donotelaboratesurrogate = lookupSurrogateInModule("DO-NOT-ELABORATE", oPL_KERNEL_MODULEo, false);

    return (((boolean)(donotelaboratesurrogate)) &&
        testIsaP(self, donotelaboratesurrogate));
  }
}

void postRelatedFacts(Object* self, PropagationEnvironment* environment) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPAGATE_LOGIC_LOGIC_OBJECT)) {
      { Object* self000 = self;
        LogicObject* self = ((LogicObject*)(self000));

        if (environment->elaboratedObjects->memberP(self)) {
          return;
        }
        environment->elaboratedObjects->insert(self);
        if (doNotElaborateP(self, environment)) {
          return;
        }
        { Proposition* p = NULL;
          Iterator* iter000 = unfilteredDependentPropositions(self, NULL)->allocateIterator();

          for (; iter000->nextP(); ) {
            p = ((Proposition*)(iter000->value));
            postRelatedFacts(p, environment);
            { Object* arg = NULL;
              Vector* vector000 = p->arguments;
              int index000 = 0;
              int length000 = vector000->length();

              for  (; index000 < length000; 
                    index000 = index000 + 1) {
                arg = (vector000->theArray)[index000];
                if ((!(arg == self)) &&
                    followDependentPropositionArgumentP(p, arg)) {
                  postRelatedFacts(arg, environment);
                }
              }
            }
          }
        }
        { LogicObject* equivalent = NULL;
          Cons* iter001 = self->variableValueInverse_reader();

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            equivalent = ((LogicObject*)(iter001->value));
            postRelatedFacts(equivalent, environment);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPAGATE_LOGIC_PROPOSITION)) {
      { Object* self001 = self;
        Proposition* self = ((Proposition*)(self001));

        if (((boolean)(((Keyword*)(environment->evaluationStates->lookup(self)))))) {
          return;
        }
        { boolean assertedP = !unknownP(self);
          Skolem* outputskolem = NULL;

          if ((!assertedP) &&
              (self->kind == KWD_PROPAGATE_FUNCTION)) {
            assertedP = functionWithDefinedValueP(self);
          }
          if (assertedP) {
            recursivelyReactToInferenceUpdate(self);
          }
          { Proposition* p = NULL;
            Iterator* iter002 = self->dependentPropositions->allocateIterator();

            for (; iter002->nextP(); ) {
              p = ((Proposition*)(iter002->value));
              postRelatedFacts(p, environment);
            }
          }
        }
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* self002 = self;
        Surrogate* self = ((Surrogate*)(self002));

        if (((boolean)(self->surrogateValue))) {
          postRelatedFacts(self->surrogateValue, environment);
        }
      }
    }
    else if (subtypeOfClassP(testValue000)) {
      { Object* self003 = self;
        Class* self = ((Class*)(self003));

        if (((boolean)(((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPAGATE_LOGIC_DESCRIPTION, NULL)))))) {
          postRelatedFacts(((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPAGATE_LOGIC_DESCRIPTION, NULL))), environment);
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPAGATE_STELLA_SLOT)) {
      { Object* self004 = self;
        Slot* self = ((Slot*)(self004));

        if (((boolean)(((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPAGATE_LOGIC_DESCRIPTION, NULL)))))) {
          postRelatedFacts(((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPAGATE_LOGIC_DESCRIPTION, NULL))), environment);
        }
      }
    }
    else {
    }
  }
}

void helpCollectFacts(Object* self, List* facts, HashSet* beenthere, boolean includeunknownP) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPAGATE_LOGIC_LOGIC_OBJECT)) {
      { Object* self000 = self;
        LogicObject* self = ((LogicObject*)(self000));

        if (beenthere->memberP(self)) {
          return;
        }
        else {
          beenthere->insert(self);
        }
        { Proposition* p = NULL;
          Iterator* iter000 = unfilteredDependentPropositions(self, NULL)->allocateIterator();

          for (; iter000->nextP(); ) {
            p = ((Proposition*)(iter000->value));
            helpCollectFacts(p, facts, beenthere, includeunknownP);
          }
        }
        { LogicObject* equivalent = NULL;
          Cons* iter001 = self->variableValueInverse_reader();

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            equivalent = ((LogicObject*)(iter001->value));
            helpCollectFacts(equivalent, facts, beenthere, includeunknownP);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPAGATE_LOGIC_PROPOSITION)) {
      { Object* self001 = self;
        Proposition* self = ((Proposition*)(self001));

        if (beenthere->memberP(self)) {
          return;
        }
        else {
          beenthere->insert(self);
        }
        { boolean assertedP = includeunknownP ||
              (!unknownP(self));
          Skolem* outputskolem = NULL;

          if ((!assertedP) &&
              (self->kind == KWD_PROPAGATE_FUNCTION)) {
            outputskolem = ((Skolem*)((self->arguments->theArray)[(self->arguments->length() - 1)]));
            assertedP = !(outputskolem == valueOf(outputskolem));
          }
          if (assertedP) {
            facts->insert(self);
          }
          { Proposition* p = NULL;
            Iterator* iter002 = self->dependentPropositions->allocateIterator();

            for (; iter002->nextP(); ) {
              p = ((Proposition*)(iter002->value));
              helpCollectFacts(p, facts, beenthere, includeunknownP);
            }
          }
        }
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* self002 = self;
        Surrogate* self = ((Surrogate*)(self002));

        if (((boolean)(self->surrogateValue))) {
          helpCollectFacts(self->surrogateValue, facts, beenthere, includeunknownP);
        }
      }
    }
    else if (subtypeOfClassP(testValue000)) {
      { Object* self003 = self;
        Class* self = ((Class*)(self003));

        if (((boolean)(((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPAGATE_LOGIC_DESCRIPTION, NULL)))))) {
          helpCollectFacts(((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPAGATE_LOGIC_DESCRIPTION, NULL))), facts, beenthere, includeunknownP);
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPAGATE_STELLA_SLOT)) {
      { Object* self004 = self;
        Slot* self = ((Slot*)(self004));

        if (((boolean)(((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPAGATE_LOGIC_DESCRIPTION, NULL)))))) {
          helpCollectFacts(((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPAGATE_LOGIC_DESCRIPTION, NULL))), facts, beenthere, includeunknownP);
        }
      }
    }
    else {
    }
  }
}

List* allFactsOfInstance(Object* self, boolean includeunknownfactsP, boolean elaborateP) {
  // Return a list of all definite (TRUE or FALSE) propositions
  // attached to `self'.
  { List* facts = newList();

    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getQueryContext());
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      if (elaborateP) {
        elaborateInstance(self);
      }
      helpCollectFacts(self, facts, newHashSet(), includeunknownfactsP);
    }
    return (facts);
  }
}

Cons* allFactsOf(Object* instanceref) {
  // Return a cons list of all definite (TRUE or FALSE) propositions
  // that reference the instance `instanceRef'.  This includes propositions
  // asserted to be true by default, but it does not include propositions
  // that are found to be TRUE only by running the query engine.  Facts
  // inferred to be TRUE by the forward chainer will be included.
  // Hence, the returned list of facts may be longer in a context where the
  // forward chainer has been run then in one where it has not (see
  // `run-forward-rules').  `instanceRef' can be a regular name such as
  // `fred' as well as a function term such as `(father fred)'.
  { LogicObject* instance = coerceToInstance(instanceref, NULL);

    if (((boolean)(instance))) {
      return (allFactsOfInstance(instance, false, true)->theConsList);
    }
    else {
      return (NULL);
    }
  }
}

void printFacts(Object* instanceref) {
  // Like `all-facts-of', but sorts and prints each fact
  // on a separate line on the standard output stream.
  { LogicObject* instance = coerceToInstance(instanceref, NULL);

    { Proposition* fact = NULL;
      Cons* iter000 = allFactsOfInstance(instance, false, false)->sort(((cpp_function_code)(&propositionLessThanP)))->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        fact = ((Proposition*)(iter000->value));
        prettyPrintLogicalForm(fact, STANDARD_OUTPUT);
        std::cout << std::endl;
      }
    }
  }
}

List* callAllFactsOf(Object* instanceref) {
  // Return a list of all definite (TRUE or FALSE) propositions
  // that reference the instance `instanceRef'.
  { LogicObject* instance = coerceToInstance(instanceref, NULL);

    if (((boolean)(instance))) {
      return (allFactsOfInstance(instance, false, true));
    }
    else {
      return (NULL);
    }
  }
}

void retractFactsOfInstance(LogicObject* self) {
  // Retract all definite (TRUE or FALSE) propositions attached to `self'.
  if (!((boolean)(self))) {
    return;
  }
  { Proposition* p = NULL;
    Cons* iter000 = allFactsOfInstance(self, false, true)->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      p = ((Proposition*)(iter000->value));
      if (p->kind == KWD_PROPAGATE_FUNCTION) {
        { Skolem* skolem = ((Skolem*)(p->arguments->last()));

          if (skolem == self) {
            continue;
          }
          if (((boolean)(skolem)) &&
              ((boolean)(((Object*)(accessInContext(skolem->variableValue, skolem->homeContext, false)))))) {
            unassertProposition(p);
          }
          retractFactsOfInstance(skolem);
        }
      }
      else {
        unassertProposition(p);
      }
    }
  }
}

void retractFactsOf(Object* instanceref) {
  // Retract all definite (TRUE or FALSE) propositions
  // that reference the instance `instanceRef'.
  { LogicObject* instance = coerceToInstance(instanceref, NULL);

    if (((boolean)(instance))) {
      retractFactsOfInstance(instance);
    }
  }
}

List* explodeVariablizedString(const char* string) {
  { List* list = newList();
    int endofstring = strlen(string);
    int begin = 0;
    int end = NULL_INTEGER;
    const char* substring = NULL;
    Symbol* symbol = NULL;

    for (;;) {
      if (begin >= endofstring) {
        return (list);
      }
      end = stringPosition(string, '?', begin);
      if (end == NULL_INTEGER) {
        substring = stringSubsequence(string, begin, endofstring);
        list->insertLast(wrapString(substring));
        return (list);
      }
      else if (end > begin) {
        substring = stringSubsequence(string, begin, end);
        list->insertLast(wrapString(substring));
      }
      begin = end;
      end = stringPosition(string, ' ', begin);
      if (end == NULL_INTEGER) {
        end = endofstring;
      }
      substring = stringSubsequence(string, begin, end);
      symbol = internSymbol(stringUpcase(substring));
      list->insertLast(symbol);
      begin = end;
    }
  }
}

const char* factToSentence(Proposition* self, boolean periodP) {
  { Keyword* testValue000 = self->kind;

    if ((testValue000 == KWD_PROPAGATE_PREDICATE) ||
        ((testValue000 == KWD_PROPAGATE_FUNCTION) ||
         (testValue000 == KWD_PROPAGATE_ISA))) {
      { NamedDescription* relation = ((NamedDescription*)(((Surrogate*)(self->operatoR))->surrogateValue));
        Object* phrase = accessBinaryValue(relation, SGT_PROPAGATE_PL_KERNEL_KB_PHRASE);
        List* explodedstring = (((boolean)(phrase)) ? explodeVariablizedString(((StringWrapper*)(phrase))->wrapperValue) : ((List*)(NULL)));

        if (((boolean)(explodedstring))) {
          { KeyValueList* table = newKeyValueList();
            const char* sentence = "";

            { Symbol* vbl = NULL;
              Cons* iter000 = relation->ioVariableNames->theConsList;
              Object* arg = NULL;
              Vector* vector000 = self->arguments;
              int index000 = 0;
              int length000 = vector000->length();

              for  (; (!(iter000 == NIL)) &&
                        (index000 < length000); 
                    iter000 = iter000->rest,
                    index000 = index000 + 1) {
                vbl = ((Symbol*)(iter000->value));
                arg = (vector000->theArray)[index000];
                table->insertAt(vbl, arg);
              }
            }
            { Object* item = NULL;
              Cons* iter001 = explodedstring->theConsList;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                item = iter001->value;
                { Object* value = NULL;
                  const char* stringvalue = NULL;

                  { Surrogate* testValue001 = safePrimaryType(item);

                    if (subtypeOfSymbolP(testValue001)) {
                      { Object* item000 = item;
                        Symbol* item = ((Symbol*)(item000));

                        value = table->lookup(item);
                        if (((boolean)(value))) {
                          { Surrogate* testValue002 = safePrimaryType(value);

                            if (subtypeOfP(testValue002, SGT_PROPAGATE_LOGIC_SKOLEM)) {
                              { Object* value000 = value;
                                Skolem* value = ((Skolem*)(value000));

                                { Surrogate* surrogate = ((LogicObject*)(value))->surrogateValueInverse;
                                  Proposition* definingproposition = value->definingProposition;

                                  if (((boolean)(definingproposition))) {
                                    stringvalue = factToSentence(definingproposition, false);
                                  }
                                  else if (((boolean)(surrogate))) {
                                    stringvalue = surrogate->symbolName;
                                  }
                                  else {
                                    stringvalue = ((Skolem*)(value))->skolemName->symbolName;
                                  }
                                }
                              }
                            }
                            else if (subtypeOfP(testValue002, SGT_PROPAGATE_LOGIC_LOGIC_OBJECT)) {
                              { Object* value001 = value;
                                LogicObject* value = ((LogicObject*)(value001));

                                { Surrogate* surrogate = ((LogicObject*)(value))->surrogateValueInverse;

                                  if (((boolean)(surrogate))) {
                                    stringvalue = surrogate->symbolName;
                                  }
                                }
                              }
                            }
                            else if (subtypeOfStringP(testValue002)) {
                              { Object* value002 = value;
                                StringWrapper* value = ((StringWrapper*)(value002));

                                stringvalue = stringConcatenate("'", value->wrapperValue, 1, "'");
                              }
                            }
                            else if (subtypeOfIntegerP(testValue002)) {
                              { Object* value003 = value;
                                IntegerWrapper* value = ((IntegerWrapper*)(value003));

                                stringvalue = integerToString(((long long int)(value->wrapperValue)));
                              }
                            }
                            else if (subtypeOfFloatP(testValue002)) {
                              { Object* value004 = value;
                                FloatWrapper* value = ((FloatWrapper*)(value004));

                                stringvalue = floatToString(value->wrapperValue);
                              }
                            }
                            else {
                            }
                          }
                        }
                        if (stringvalue != NULL) {
                          sentence = stringConcatenate(sentence, stringvalue, 0);
                        }
                        else {
                          sentence = stringConcatenate(sentence, item->symbolName, 0);
                        }
                      }
                    }
                    else if (subtypeOfStringP(testValue001)) {
                      { Object* item001 = item;
                        StringWrapper* item = ((StringWrapper*)(item001));

                        sentence = stringConcatenate(sentence, item->wrapperValue, 0);
                      }
                    }
                    else {
                      { OutputStringStream* stream000 = newOutputStringStream();

                        *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                        throw *newStellaException(stream000->theStringReader());
                      }
                    }
                  }
                }
              }
            }
            if (periodP) {
              sentence = stringConcatenate(sentence, ".", 0);
            }
            return (sentence);
          }
        }
        return (NULL);
      }
    }
    else if (testValue000 == KWD_PROPAGATE_IMPLIES) {
      return ("rules not yet implemented");
    }
    else {
      return ("???");
    }
  }
}

Cons* allSentencesOf(Object* instanceref) {
  // Return a list of sentences describing facts about 'instanceRef'.
  { LogicObject* instance = coerceToInstance(instanceref, NULL);
    const char* sentence = NULL;

    if (((boolean)(instance))) {
      { Cons* list = NIL;

        { Proposition* fact = NULL;
          Cons* iter000 = allFactsOfInstance(instance, false, true)->theConsList;
          Cons* collect000 = NULL;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest) {
            fact = ((Proposition*)(iter000->value));
            sentence = factToSentence(fact, true);
            if (sentence == NULL) {
              continue;
            }
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(wrapString(sentence), NIL);
                if (list == NIL) {
                  list = collect000;
                }
                else {
                  addConsToEndOfConsList(list, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(wrapString(sentence), NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        return (list);
      }
    }
    else {
      return (NULL);
    }
  }
}

List* callAllFactsOfN(int n, Cons* seedrefs) {
  { HashTable* visited = newHashTable();
    HashTable* facts = newHashTable();
    List* factlist = newList();
    List* seeds = newList();
    List* newseeds = newList();
    Object* instance = NULL;

    { Object* seedref = NULL;
      Cons* iter000 = seedrefs;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        seedref = iter000->value;
        instance = coerceToInstance(seedref, NULL);
        if (((boolean)(instance))) {
          seeds->insertNew(instance);
        }
      }
    }
    { int i = NULL_INTEGER;
      int iter001 = 0;
      int upperBound000 = ((n != NULL_INTEGER) ? n : 0);
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter001 <= upperBound000); 
            iter001 = iter001 + 1) {
        i = iter001;
        i = i;
        { Object* seed = NULL;
          Cons* iter002 = seeds->theConsList;

          for (; !(iter002 == NIL); iter002 = iter002->rest) {
            seed = iter002->value;
            visited->insertAt(seed, seed);
          }
        }
        { Object* seed = NULL;
          Cons* iter003 = seeds->theConsList;

          for (; !(iter003 == NIL); iter003 = iter003->rest) {
            seed = iter003->value;
            { Proposition* prop = NULL;
              Cons* iter004 = allFactsOfInstance(seed, false, true)->theConsList;

              for (; !(iter004 == NIL); iter004 = iter004->rest) {
                prop = ((Proposition*)(iter004->value));
                if (((boolean)(((Proposition*)(facts->lookup(prop)))))) {
                  continue;
                }
                facts->insertAt(prop, prop);
                factlist->insert(prop);
                { Object* arg = NULL;
                  Vector* vector000 = prop->arguments;
                  int index000 = 0;
                  int length000 = vector000->length();

                  for  (; index000 < length000; 
                        index000 = index000 + 1) {
                    arg = (vector000->theArray)[index000];
                    if (!((boolean)(visited->lookup(arg)))) {
                      newseeds->insertNew(arg);
                    }
                  }
                }
              }
            }
          }
        }
        seeds = newseeds;
        newseeds = newList();
      }
    }
    return (factlist->reverse());
  }
}

List* filteredAllFactsOfN(int n, Cons* seedrefs, cpp_function_code filter) {
  { HashTable* visited = newHashTable();
    HashTable* facts = newHashTable();
    List* factlist = newList();
    List* seeds = newList();
    List* newseeds = newList();
    Object* instance = NULL;

    { Object* seedref = NULL;
      Cons* iter000 = seedrefs;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        seedref = iter000->value;
        instance = coerceToInstance(seedref, NULL);
        if (((boolean)(instance))) {
          seeds->insertNew(instance);
        }
      }
    }
    { int i = NULL_INTEGER;
      int iter001 = 0;
      int upperBound000 = ((n != NULL_INTEGER) ? n : 0);
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter001 <= upperBound000); 
            iter001 = iter001 + 1) {
        i = iter001;
        i = i;
        { Object* seed = NULL;
          Cons* iter002 = seeds->theConsList;

          for (; !(iter002 == NIL); iter002 = iter002->rest) {
            seed = iter002->value;
            visited->insertAt(seed, seed);
          }
        }
        { Object* seed = NULL;
          Cons* iter003 = seeds->theConsList;

          for (; !(iter003 == NIL); iter003 = iter003->rest) {
            seed = iter003->value;
            { Proposition* prop = NULL;
              Cons* iter004 = allFactsOfInstance(seed, false, true)->theConsList;

              for (; !(iter004 == NIL); iter004 = iter004->rest) {
                prop = ((Proposition*)(iter004->value));
                if (((boolean)(((Proposition*)(facts->lookup(prop)))))) {
                  continue;
                }
                { Cons* filteroutput = ((Cons*  (*) (Proposition*))filter)(prop);
                  Cons* factprops = ((Cons*)(filteroutput->value));
                  Cons* propseeds = ((Cons*)(filteroutput->rest->value));

                  { Proposition* factprop = NULL;
                    Cons* iter005 = factprops;

                    for (; !(iter005 == NIL); iter005 = iter005->rest) {
                      factprop = ((Proposition*)(iter005->value));
                      facts->insertAt(factprop, factprop);
                      factlist->insert(factprop);
                    }
                  }
                  { Object* arg = NULL;
                    Cons* iter006 = propseeds;

                    for (; !(iter006 == NIL); iter006 = iter006->rest) {
                      arg = iter006->value;
                      if (!((boolean)(visited->lookup(arg)))) {
                        newseeds->insertNew(arg);
                      }
                    }
                  }
                }
              }
            }
          }
        }
        seeds = newseeds;
        newseeds = newList();
      }
    }
    return (factlist->reverse());
  }
}

Cons* allFactsOfN(int n, Cons* instancerefs) {
  // This is a generalization of `all-facts-of' (which see).  With `n' = 0
  // and only one instance this command behaves just like `all-facts-of'.
  // Otherwise, returns a cons list of all definite (TRUE or FALSE) propositions
  // that reference any of the instances listed in `instanceRefs', plus if `n' >= 1
  // all propositions that reference any instances that are arguments of
  // propositions collected in the previous step, plus if `n' >= 2... and so on.
  // That is, if we only consider binary propositions, this can be viewed as
  // growing a graph with instances as its nodes and predicates as its arcs
  // starting from the set of seed `instanceRefs' to depth `n'-1.
  // Caution: with a fully connected KB and large enough `n' this could return
  // the whole knowledge base.
  // 
  // The returned propositions include those asserted to be true or false by
  // default, but it does not include propositions that are found to be
  // true only by running the query engine.  Facts inferred to be true by
  // the forward chainer will be included.  Hence, the returned list of
  // facts may be longer in a context where the forward chainer has been
  // run then in one where it has not (see `run-forward-rules').
  return (callAllFactsOfN(n, instancerefs)->theConsList);
}

Cons* allFactsOfNEvaluatorWrapper(Cons* arguments) {
  return (allFactsOfN(((IntegerWrapper*)(arguments->value))->wrapperValue, arguments->rest));
}

void helpStartupPropagate1() {
  {
    SGT_PROPAGATE_LOGIC_PROPAGATION_ENVIRONMENT = ((Surrogate*)(internRigidSymbolWrtModule("PROPAGATION-ENVIRONMENT", NULL, 1)));
    SYM_PROPAGATE_LOGIC_EVALUATION_QUEUE = ((Symbol*)(internRigidSymbolWrtModule("EVALUATION-QUEUE", NULL, 0)));
    SYM_PROPAGATE_LOGIC_EVALUATION_STATES = ((Symbol*)(internRigidSymbolWrtModule("EVALUATION-STATES", NULL, 0)));
    SYM_PROPAGATE_LOGIC_FORWARD_CHAINING_QUEUE = ((Symbol*)(internRigidSymbolWrtModule("FORWARD-CHAINING-QUEUE", NULL, 0)));
    SYM_PROPAGATE_LOGIC_FORWARD_CHAINING_SET = ((Symbol*)(internRigidSymbolWrtModule("FORWARD-CHAINING-SET", NULL, 0)));
    SYM_PROPAGATE_LOGIC_DEFERRED_DEFAULT_PROPOSITIONS = ((Symbol*)(internRigidSymbolWrtModule("DEFERRED-DEFAULT-PROPOSITIONS", NULL, 0)));
    SYM_PROPAGATE_LOGIC_ELABORATED_OBJECTS = ((Symbol*)(internRigidSymbolWrtModule("ELABORATED-OBJECTS", NULL, 0)));
    SYM_PROPAGATE_LOGIC_PROPAGATION_ENVIRONMENT = ((Symbol*)(internRigidSymbolWrtModule("PROPAGATION-ENVIRONMENT", NULL, 0)));
    KWD_PROPAGATE_POSTED = ((Keyword*)(internRigidSymbolWrtModule("POSTED", NULL, 2)));
    KWD_PROPAGATE_FORWARD = ((Keyword*)(internRigidSymbolWrtModule("FORWARD", NULL, 2)));
    SYM_PROPAGATE_LOGIC_BACKWARD_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("BACKWARD-ONLY?", NULL, 0)));
    SGT_PROPAGATE_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
    SYM_PROPAGATE_LOGIC_FORWARD_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("FORWARD-ONLY?", NULL, 0)));
    SGT_PROPAGATE_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
    SGT_PROPAGATE_LOGIC_F_COLLECT_FORWARD_CHAINING_RULES_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-COLLECT-FORWARD-CHAINING-RULES-MEMO-TABLE-000", NULL, 1)));
    KWD_PROPAGATE_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    KWD_PROPAGATE_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    KWD_PROPAGATE_PREDICATE = ((Keyword*)(internRigidSymbolWrtModule("PREDICATE", NULL, 2)));
    SYM_PROPAGATE_LOGIC_SKOLEM_GENERATION_COUNT = ((Symbol*)(internRigidSymbolWrtModule("SKOLEM-GENERATION-COUNT", NULL, 0)));
    KWD_PROPAGATE_PROPAGATE = ((Keyword*)(internRigidSymbolWrtModule("PROPAGATE", NULL, 2)));
    SYM_PROPAGATE_LOGIC_HYPOTHESIZED_INSTANCEp = ((Symbol*)(internRigidSymbolWrtModule("HYPOTHESIZED-INSTANCE?", NULL, 0)));
    SGT_PROPAGATE_PL_KERNEL_KB_AND = ((Surrogate*)(internRigidSymbolWrtModule("AND", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_PROPAGATE_GOAL_TREE = ((Keyword*)(internRigidSymbolWrtModule("GOAL-TREE", NULL, 2)));
    KWD_PROPAGATE_SINGLETONSp = ((Keyword*)(internRigidSymbolWrtModule("SINGLETONS?", NULL, 2)));
    KWD_PROPAGATE_INFERENCE_LEVEL = ((Keyword*)(internRigidSymbolWrtModule("INFERENCE-LEVEL", NULL, 2)));
    KWD_PROPAGATE_SHALLOW = ((Keyword*)(internRigidSymbolWrtModule("SHALLOW", NULL, 2)));
    SGT_PROPAGATE_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", NULL, 1)));
    SGT_PROPAGATE_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    KWD_PROPAGATE_KB_UPDATE = ((Keyword*)(internRigidSymbolWrtModule("KB-UPDATE", NULL, 2)));
    KWD_PROPAGATE_META_KB_UPDATE = ((Keyword*)(internRigidSymbolWrtModule("META-KB-UPDATE", NULL, 2)));
    KWD_PROPAGATE_META = ((Keyword*)(internRigidSymbolWrtModule("META", NULL, 2)));
    SGT_PROPAGATE_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 1)));
    SYM_PROPAGATE_LOGIC_DESCRIPTIVEp = ((Symbol*)(internRigidSymbolWrtModule("DESCRIPTIVE?", NULL, 0)));
    SGT_PROPAGATE_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
    SGT_PROPAGATE_STELLA_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("SYMBOL", getStellaModule("/STELLA", true), 1)));
    KWD_PROPAGATE_EVALUATED = ((Keyword*)(internRigidSymbolWrtModule("EVALUATED", NULL, 2)));
    KWD_PROPAGATE_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    KWD_PROPAGATE_OR = ((Keyword*)(internRigidSymbolWrtModule("OR", NULL, 2)));
    KWD_PROPAGATE_NOT = ((Keyword*)(internRigidSymbolWrtModule("NOT", NULL, 2)));
    KWD_PROPAGATE_EQUIVALENT = ((Keyword*)(internRigidSymbolWrtModule("EQUIVALENT", NULL, 2)));
    SYM_PROPAGATE_LOGIC_CULL_CLASH_EXCEPTIONS = ((Symbol*)(internRigidSymbolWrtModule("CULL-CLASH-EXCEPTIONS", NULL, 0)));
    KWD_PROPAGATE_ELABORATE = ((Keyword*)(internRigidSymbolWrtModule("ELABORATE", NULL, 2)));
    KWD_PROPAGATE_EXTENSIONAL_ASSERTION = ((Keyword*)(internRigidSymbolWrtModule("EXTENSIONAL-ASSERTION", NULL, 2)));
    SGT_PROPAGATE_PL_KERNEL_KB_INEQUALITY = ((Surrogate*)(internRigidSymbolWrtModule("INEQUALITY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_PROPAGATE_STELLA_SURROGATE = ((Surrogate*)(internRigidSymbolWrtModule("SURROGATE", getStellaModule("/STELLA", true), 1)));
    KWD_PROPAGATE_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("EXISTS", NULL, 2)));
    KWD_PROPAGATE_FORALL = ((Keyword*)(internRigidSymbolWrtModule("FORALL", NULL, 2)));
    SGT_PROPAGATE_PL_KERNEL_KB_EQUIVALENT = ((Surrogate*)(internRigidSymbolWrtModule("EQUIVALENT", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_PROPAGATE_LOGIC_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 0)));
    SGT_PROPAGATE_STELLA_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("SLOT", getStellaModule("/STELLA", true), 1)));
    SGT_PROPAGATE_PL_KERNEL_KB_PHRASE = ((Surrogate*)(internRigidSymbolWrtModule("PHRASE", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_PROPAGATE_IMPLIES = ((Keyword*)(internRigidSymbolWrtModule("IMPLIES", NULL, 2)));
    SYM_PROPAGATE_LOGIC_STARTUP_PROPAGATE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-PROPAGATE", NULL, 0)));
    SYM_PROPAGATE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupPropagate2() {
  {
    defineFunctionObject("PRINT-PROPAGATION-ENVIRONMENT-STATS", "(DEFUN PRINT-PROPAGATION-ENVIRONMENT-STATS ((SELF PROPAGATION-ENVIRONMENT)))", ((cpp_function_code)(&printPropagationEnvironmentStats)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT CONTEXT PROPAGATION-ENVIRONMENT :TYPE PROPAGATION-ENVIRONMENT :PUBLIC? TRUE :DOCUMENTATION \"Holds propositions posted for evaluation and\nforward chaining as well as various other propagation control information.\" :ALLOCATION :DYNAMIC)");
    defineFunctionObject("GET-PROPAGATION-ENVIRONMENT", "(DEFUN (GET-PROPAGATION-ENVIRONMENT PROPAGATION-ENVIRONMENT) ((SELF CONTEXT)))", ((cpp_function_code)(&getPropagationEnvironment)), NULL);
    defineFunctionObject("UNLINK-PROPAGATION-ENVIRONMENT", "(DEFUN UNLINK-PROPAGATION-ENVIRONMENT ((SELF CONTEXT)))", ((cpp_function_code)(&unlinkPropagationEnvironment)), NULL);
    defineMethodObject("(DEFMETHOD DEFER-DEFAULT-PROPOSITION ((SELF PROPAGATION-ENVIRONMENT) (PROPOSITION PROPOSITION)))", wrapMethodCode(((cpp_method_code)(&PropagationEnvironment::deferDefaultProposition))), NULL);
    defineMethodObject("(DEFMETHOD CLEAR-PROPAGATION-QUEUES ((SELF PROPAGATION-ENVIRONMENT)))", wrapMethodCode(((cpp_method_code)(&PropagationEnvironment::clearPropagationQueues))), NULL);
    defineMethodObject("(DEFMETHOD (COPY (LIKE SELF)) ((SELF PROPAGATION-ENVIRONMENT)))", wrapMethodCode(((cpp_method_code)(&PropagationEnvironment::copy))), NULL);
    defineFunctionObject("EVALUATION-STATE", "(DEFUN (EVALUATION-STATE KEYWORD) ((PROPOSITION PROPOSITION)) :DOCUMENTATION \"Return :POSTED if `proposition' is on the evaluation queue\nfor *context*, :EVALUATED if has been evaluated, or NULL if it has never been evaluated.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (IF (DESCRIPTION-MODE?) (RETURN NULL) (RETURN (LOOKUP (EVALUATION-STATES (GET-PROPAGATION-ENVIRONMENT *CONTEXT*)) PROPOSITION))))", ((cpp_function_code)(&evaluationState)), NULL);
    defineFunctionObject("EVALUATION-STATE-SETTER", "(DEFUN EVALUATION-STATE-SETTER ((PROPOSITION PROPOSITION) (STATE KEYWORD)) :DOCUMENTATION \"Record the evaluation `state' of 'proposition'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&evaluationStateSetter)), NULL);
    defineFunctionObject("POST-FOR-EVALUATION", "(DEFUN POST-FOR-EVALUATION ((SELF PROPOSITION) (WORLD CONTEXT)) :DOCUMENTATION \"Push 'self' onto the evaluation queue (unless it's already there).\" :PUBLIC? TRUE)", ((cpp_function_code)(&postForEvaluation)), NULL);
    defineFunctionObject("HELP-COLLECT-FORWARD-RULES", "(DEFUN (HELP-COLLECT-FORWARD-RULES (CONS OF KEY-VALUE-LIST)) ((DESCRIPTION DESCRIPTION) (RULES KEY-VALUE-LIST) (INDICES KEY-VALUE-LIST) (TOUCHEDDEFAULT? BOOLEAN) (BEENTHERE LIST)))", ((cpp_function_code)(&helpCollectForwardRules)), NULL);
    defineFunctionObject("COLLECT-FORWARD-CHAINING-RULES", "(DEFUN (COLLECT-FORWARD-CHAINING-RULES (KEY-VALUE-LIST OF PROPOSITION BOOLEAN-WRAPPER) (KEY-VALUE-LIST OF FORWARD-CHAINING-INDEX BOOLEAN-WRAPPER)) ((DESCRIPTION DESCRIPTION)))", ((cpp_function_code)(&collectForwardChainingRules)), NULL);
    defineFunctionObject("HAS-FORWARD-CHAINING-RULES?", "(DEFUN (HAS-FORWARD-CHAINING-RULES? BOOLEAN) ((DESCRIPTION DESCRIPTION) (PROPOSITION PROPOSITION)))", ((cpp_function_code)(&hasForwardChainingRulesP)), NULL);
    defineFunctionObject("POST-TO-FORWARD-CHAINING-QUEUE", "(DEFUN POST-TO-FORWARD-CHAINING-QUEUE ((SELF PROPOSITION) (WORLD WORLD)))", ((cpp_function_code)(&postToForwardChainingQueue)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT SKOLEM SKOLEM-GENERATION-COUNT :TYPE INTEGER :DEFAULT 0 :ALLOCATION :DYNAMIC)");
    defineFunctionObject("APPLY-RULE-CONSEQUENT-TO-VECTOR", "(DEFUN APPLY-RULE-CONSEQUENT-TO-VECTOR ((CONSEQUENT DESCRIPTION) (ARGUMENTS ARGUMENTS-VECTOR) (RULE PROPOSITION) (TRIGGERDESCRIPTION DESCRIPTION) (TRIGGERPROPOSITION PROPOSITION) (TOUCHEDDEFAULT? BOOLEAN) (BC-JUSTIFICATION JUSTIFICATION)))", ((cpp_function_code)(&applyRuleConsequentToVector)), NULL);
    defineFunctionObject("TRACE-FORWARD-RULE", "(DEFUN TRACE-FORWARD-RULE ((RULE PROPOSITION) (TRIGGER PROPOSITION) (CONSEQUENTS (CONS OF PROPOSITION))))", ((cpp_function_code)(&traceForwardRule)), NULL);
    defineFunctionObject("APPLY-FORWARD-RULES-TO-VECTOR", "(DEFUN APPLY-FORWARD-RULES-TO-VECTOR ((TRIGGERDESCRIPTION DESCRIPTION) (ARGUMENTS ARGUMENTS-VECTOR) (TRIGGERPROPOSITION PROPOSITION)))", ((cpp_function_code)(&applyForwardRulesToVector)), NULL);
    defineFunctionObject("APPLICABLE-FORWARD-RULE?", "(DEFUN (APPLICABLE-FORWARD-RULE? BOOLEAN) ((RULE PROPOSITION) (ARGUMENTS ARGUMENTS-VECTOR)))", ((cpp_function_code)(&applicableForwardRuleP)), NULL);
    defineMethodObject("(DEFMETHOD REACT-TO-INFERENCE-UPDATE ((SELF SKOLEM)))", wrapMethodCode(((cpp_method_code)(&Skolem::reactToInferenceUpdate))), NULL);
    defineMethodObject("(DEFMETHOD REACT-TO-INFERENCE-UPDATE ((SELF PROPOSITION)))", wrapMethodCode(((cpp_method_code)(&Proposition::reactToInferenceUpdate))), NULL);
    defineFunctionObject("REACT-TO-KB-UPDATE", "(DEFUN REACT-TO-KB-UPDATE ((CONTEXT CONTEXT) (OBJECT OBJECT)))", ((cpp_function_code)(&reactToKbUpdate)), NULL);
    defineMethodObject("(DEFMETHOD EXECUTE-PROPAGATION-QUEUES ((SELF PROPAGATION-ENVIRONMENT)))", wrapMethodCode(((cpp_method_code)(&PropagationEnvironment::executePropagationQueues))), NULL);
    defineFunctionObject("EXECUTE-CONSTRAINT-PROPAGATION-QUEUES", "(DEFUN EXECUTE-CONSTRAINT-PROPAGATION-QUEUES ())", ((cpp_function_code)(&executeConstraintPropagationQueues)), NULL);
    defineFunctionObject("EVALUATE-NEW-PROPOSITION", "(DEFUN EVALUATE-NEW-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&evaluateNewProposition)), NULL);
    defineFunctionObject("EVALUATE-AND-PROPOSITION", "(DEFUN EVALUATE-AND-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&evaluateAndProposition)), NULL);
    defineFunctionObject("EVALUATE-OR-PROPOSITION", "(DEFUN EVALUATE-OR-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&evaluateOrProposition)), NULL);
    defineFunctionObject("EVALUATE-NOT-PROPOSITION", "(DEFUN EVALUATE-NOT-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&evaluateNotProposition)), NULL);
    defineFunctionObject("EVALUATE-EQUIVALENT-PROPOSITION", "(DEFUN EVALUATE-EQUIVALENT-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&evaluateEquivalentProposition)), NULL);
    defineFunctionObject("EQUATE-EQUIVALENT-FUNCTION-PROPOSITIONS", "(DEFUN EQUATE-EQUIVALENT-FUNCTION-PROPOSITIONS ((SELF PROPOSITION)))", ((cpp_function_code)(&equateEquivalentFunctionPropositions)), NULL);
    defineFunctionObject("EVALUATE-FUNCTION-PROPOSITION", "(DEFUN EVALUATE-FUNCTION-PROPOSITION ((SELF PROPOSITION)) :PUBLIC? TRUE)", ((cpp_function_code)(&evaluateFunctionProposition)), NULL);
    defineFunctionObject("EVALUATE-PREDICATE-PROPOSITION", "(DEFUN EVALUATE-PREDICATE-PROPOSITION ((SELF PROPOSITION)) :PUBLIC? TRUE)", ((cpp_function_code)(&evaluatePredicateProposition)), NULL);
    defineFunctionObject("EVALUATE-PROPOSITION", "(DEFUN EVALUATE-PROPOSITION ((SELF PROPOSITION)) :DOCUMENTATION \"Evaluate 'self' against its arguments, possibly resulting in\nthe setting or changing of its truth value.\" :PUBLIC? TRUE)", ((cpp_function_code)(&evaluateProposition)), NULL);
    defineMethodObject("(DEFMETHOD MARK-AS-INCOHERENT ((SELF LOGIC-OBJECT)))", wrapMethodCode(((cpp_method_code)(&LogicObject::markAsIncoherent))), NULL);
    defineMethodObject("(DEFMETHOD MARK-AS-INCOHERENT ((SELF SKOLEM)))", wrapMethodCode(((cpp_method_code)(&Skolem::markAsIncoherent))), NULL);
    defineFunctionObject("RESET-CLASH-EXCEPTIONS", "(DEFUN RESET-CLASH-EXCEPTIONS () :PUBLIC? TRUE :DOCUMENTATION \"Resets the collection of clash exceptions\")", ((cpp_function_code)(&resetClashExceptions)), NULL);
    defineFunctionObject("EXCEPTION-RECORD-MATCHES-CONTEXT?", "(DEFUN (EXCEPTION-RECORD-MATCHES-CONTEXT? BOOLEAN) ((RECORD EXCEPTION-RECORD)))", ((cpp_function_code)(&exceptionRecordMatchesContextP)), NULL);
    defineFunctionObject("CULL-CLASH-EXCEPTIONS", "(DEFUN CULL-CLASH-EXCEPTIONS ((SELF CONTEXT)))", ((cpp_function_code)(&cullClashExceptions)), NULL);
    defineFunctionObject("RECURSIVELY-REACT-TO-INFERENCE-UPDATE", "(DEFUN RECURSIVELY-REACT-TO-INFERENCE-UPDATE ((SELF PROPOSITION)))", ((cpp_function_code)(&recursivelyReactToInferenceUpdate)), NULL);
    defineFunctionObject("ELABORATE-META-INSTANCE", "(DEFUN ELABORATE-META-INSTANCE ((SELF OBJECT)))", ((cpp_function_code)(&elaborateMetaInstance)), NULL);
    defineFunctionObject("ELABORATE-INSTANCE", "(DEFUN ELABORATE-INSTANCE ((SELF OBJECT)))", ((cpp_function_code)(&elaborateInstance)), NULL);
    defineFunctionObject("EVALUATE-REACHABLE-INEQUALITIES", "(DEFUN EVALUATE-REACHABLE-INEQUALITIES ((SELF LOGIC-OBJECT) (VISITEDLIST LIST)))", ((cpp_function_code)(&evaluateReachableInequalities)), NULL);
    defineFunctionObject("ELABORATE-SURROGATES-IN-PROPOSITION", "(DEFUN ELABORATE-SURROGATES-IN-PROPOSITION ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&elaborateSurrogatesInProposition)), NULL);
    defineFunctionObject("FOLLOW-DEPENDENT-PROPOSITION-ARGUMENT?", "(DEFUN (FOLLOW-DEPENDENT-PROPOSITION-ARGUMENT? BOOLEAN) ((PROPOSITION PROPOSITION) (ARGUMENT OBJECT)))", ((cpp_function_code)(&followDependentPropositionArgumentP)), NULL);
    defineFunctionObject("DO-NOT-ELABORATE?", "(DEFUN (DO-NOT-ELABORATE? BOOLEAN) ((SELF OBJECT) (ENVIRONMENT PROPAGATION-ENVIRONMENT)))", ((cpp_function_code)(&doNotElaborateP)), NULL);
    defineFunctionObject("POST-RELATED-FACTS", "(DEFUN POST-RELATED-FACTS ((SELF OBJECT) (ENVIRONMENT PROPAGATION-ENVIRONMENT)))", ((cpp_function_code)(&postRelatedFacts)), NULL);
    defineFunctionObject("HELP-COLLECT-FACTS", "(DEFUN HELP-COLLECT-FACTS ((SELF OBJECT) (FACTS (LIST OF PROPOSITION)) (BEENTHERE HASH-SET) (INCLUDEUNKNOWN? BOOLEAN)))", ((cpp_function_code)(&helpCollectFacts)), NULL);
    defineFunctionObject("ALL-FACTS-OF-INSTANCE", "(DEFUN (ALL-FACTS-OF-INSTANCE (LIST OF PROPOSITION)) ((SELF OBJECT) (INCLUDEUNKNOWNFACTS? BOOLEAN) (ELABORATE? BOOLEAN)) :DOCUMENTATION \"Return a list of all definite (TRUE or FALSE) propositions\nattached to `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allFactsOfInstance)), NULL);
    defineFunctionObject("ALL-FACTS-OF", "(DEFUN (ALL-FACTS-OF (CONS OF PROPOSITION)) ((INSTANCEREF OBJECT)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Return a cons list of all definite (TRUE or FALSE) propositions\nthat reference the instance `instanceRef'.  This includes propositions\nasserted to be true by default, but it does not include propositions\nthat are found to be TRUE only by running the query engine.  Facts\ninferred to be TRUE by the forward chainer will be included.\nHence, the returned list of facts may be longer in a context where the\nforward chainer has been run then in one where it has not (see\n`run-forward-rules').  `instanceRef' can be a regular name such as\n`fred' as well as a function term such as `(father fred)'.\")", ((cpp_function_code)(&allFactsOf)), NULL);
    defineFunctionObject("PRINT-FACTS", "(DEFUN PRINT-FACTS ((INSTANCEREF OBJECT)) :DOCUMENTATION \"Like `all-facts-of', but sorts and prints each fact\non a separate line on the standard output stream.\" :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&printFacts)), NULL);
    defineFunctionObject("CALL-ALL-FACTS-OF", "(DEFUN (CALL-ALL-FACTS-OF (LIST OF PROPOSITION)) ((INSTANCEREF OBJECT)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? TRUE :DOCUMENTATION \"Return a list of all definite (TRUE or FALSE) propositions\nthat reference the instance `instanceRef'.\")", ((cpp_function_code)(&callAllFactsOf)), NULL);
    defineFunctionObject("RETRACT-FACTS-OF-INSTANCE", "(DEFUN RETRACT-FACTS-OF-INSTANCE ((SELF LOGIC-OBJECT)) :DOCUMENTATION \"Retract all definite (TRUE or FALSE) propositions attached to `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&retractFactsOfInstance)), NULL);
    defineFunctionObject("RETRACT-FACTS-OF", "(DEFUN RETRACT-FACTS-OF ((INSTANCEREF OBJECT)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Retract all definite (TRUE or FALSE) propositions\nthat reference the instance `instanceRef'.\")", ((cpp_function_code)(&retractFactsOf)), NULL);
    defineFunctionObject("EXPLODE-VARIABLIZED-STRING", "(DEFUN (EXPLODE-VARIABLIZED-STRING LIST) ((STRING STRING)))", ((cpp_function_code)(&explodeVariablizedString)), NULL);
    defineFunctionObject("FACT-TO-SENTENCE", "(DEFUN (FACT-TO-SENTENCE STRING) ((SELF PROPOSITION) (PERIOD? BOOLEAN)))", ((cpp_function_code)(&factToSentence)), NULL);
    defineFunctionObject("ALL-SENTENCES-OF", "(DEFUN (ALL-SENTENCES-OF (CONS OF STRING-WRAPPER)) ((INSTANCEREF OBJECT)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? TRUE :DOCUMENTATION \"Return a list of sentences describing facts about 'instanceRef'.\")", ((cpp_function_code)(&allSentencesOf)), NULL);
    defineFunctionObject("CALL-ALL-FACTS-OF-N", "(DEFUN (CALL-ALL-FACTS-OF-N (LIST OF PROPOSITION)) ((N INTEGER) (SEEDREFS CONS)))", ((cpp_function_code)(&callAllFactsOfN)), NULL);
    defineFunctionObject("FILTERED-ALL-FACTS-OF-N", "(DEFUN (FILTERED-ALL-FACTS-OF-N (LIST OF PROPOSITION)) ((N INTEGER) (SEEDREFS CONS) (FILTER FUNCTION-CODE)))", ((cpp_function_code)(&filteredAllFactsOfN)), NULL);
    defineFunctionObject("ALL-FACTS-OF-N", "(DEFUN (ALL-FACTS-OF-N (CONS OF PROPOSITION)) ((N INTEGER) |&REST| (INSTANCEREFS NAME)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"This is a generalization of `all-facts-of' (which see).  With `n' = 0\nand only one instance this command behaves just like `all-facts-of'.\nOtherwise, returns a cons list of all definite (TRUE or FALSE) propositions\nthat reference any of the instances listed in `instanceRefs', plus if `n' >= 1\nall propositions that reference any instances that are arguments of\npropositions collected in the previous step, plus if `n' >= 2... and so on.\nThat is, if we only consider binary propositions, this can be viewed as\ngrowing a graph with instances as its nodes and predicates as its arcs\nstarting from the set of seed `instanceRefs' to depth `n'-1.\nCaution: with a fully connected KB and large enough `n' this could return\nthe whole knowledge base.\n\nThe returned propositions include those asserted to be true or false by\ndefault, but it does not include p" "ropositions that are found to be\ntrue only by running the query engine.  Facts inferred to be true by\nthe forward chainer will be included.  Hence, the returned list of\nfacts may be longer in a context where the forward chainer has been\nrun then in one where it has not (see `run-forward-rules').\")", ((cpp_function_code)(&allFactsOfN)), ((cpp_function_code)(&allFactsOfNEvaluatorWrapper)));
    defineFunctionObject("STARTUP-PROPAGATE", "(DEFUN STARTUP-PROPAGATE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupPropagate)), NULL);
    { MethodSlot* function = lookupFunction(SYM_PROPAGATE_LOGIC_STARTUP_PROPAGATE);

      setDynamicSlotValue(function->dynamicSlots, SYM_PROPAGATE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupPropagate"), NULL_STRING_WRAPPER);
    }
  }
}

void startupPropagate() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupPropagate1();
    }
    if (currentStartupTimePhaseP(4)) {
      oCLASH_EXCEPTIONSo = newList();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("PROPAGATION-ENVIRONMENT", "(DEFCLASS PROPAGATION-ENVIRONMENT (STANDARD-OBJECT) :SLOTS ((EVALUATION-QUEUE :TYPE (LIST OF PROPOSITION) :INITIALLY (LIST)) (EVALUATION-STATES :TYPE (KEY-VALUE-MAP OF PROPOSITION KEYWORD) :INITIALLY (NEW KEY-VALUE-MAP)) (FORWARD-CHAINING-QUEUE :TYPE (LIST OF PROPOSITION) :INITIALLY (LIST)) (FORWARD-CHAINING-SET :TYPE (HASH-SET OF PROPOSITION PROPOSITION) :INITIALLY (NEW HASH-SET)) (DEFERRED-DEFAULT-PROPOSITIONS :TYPE (LIST OF PROPOSITION) :INITIALLY (LIST)) (ELABORATED-OBJECTS :TYPE HASH-SET :INITIALLY (NEW HASH-SET))))");

        clasS->classConstructorCode = ((cpp_function_code)(&newPropagationEnvironment));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessPropagationEnvironmentSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupPropagate2();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFSPECIAL *FILLINGCONSTRAINTPROPAGATIONQUEUES?* BOOLEAN FALSE :DOCUMENTATION \"True if we are inside of 'react-to-kb-update'.\")", &oFILLINGCONSTRAINTPROPAGATIONQUEUESpo);
      defineGlobalVariableObject("(DEFSPECIAL *DEFERINGDEFAULTFORWARDINFERENCES?* BOOLEAN FALSE :DOCUMENTATION \"True if we are propagating strict inferences, and\nposting derived default propositions to temporary queues.\")", &oDEFERINGDEFAULTFORWARDINFERENCESpo);
      defineGlobalVariableObject("(DEFSPECIAL *COLLECTFORWARDPROPOSITIONS* (CONS OF PROPOSITION) NULL :DOCUMENTATION \"Collect goes-true propositions produced by forward\nchaining.\")", &oCOLLECTFORWARDPROPOSITIONSo);
      defineGlobalVariableObject("(DEFGLOBAL *MAX-SKOLEM-GENERATION-COUNT* INTEGER 3)", &oMAX_SKOLEM_GENERATION_COUNTo);
      defineGlobalVariableObject("(DEFGLOBAL *JUST-IN-TIME-FORWARD-INFERENCE?* BOOLEAN TRUE :PUBLIC? TRUE :DOCUMENTATION \"If TRUE, ensures that forward propagation has\nbeen applied to each instance 'touched' during a query.\")", &oJUST_IN_TIME_FORWARD_INFERENCEpo);
      defineGlobalVariableObject("(DEFGLOBAL *CLASH-EXCEPTIONS* (LIST OF EXCEPTION-RECORD) (NEW LIST) :PUBLIC? TRUE :DOCUMENTATION \"Collects clash exceptions that occur during inference.\")", &oCLASH_EXCEPTIONSo);
      addHook(oDESTROY_CONTEXT_HOOKSo, SYM_PROPAGATE_LOGIC_CULL_CLASH_EXCEPTIONS);
    }
  }
}

Surrogate* SGT_PROPAGATE_LOGIC_PROPAGATION_ENVIRONMENT = NULL;

Symbol* SYM_PROPAGATE_LOGIC_EVALUATION_QUEUE = NULL;

Symbol* SYM_PROPAGATE_LOGIC_EVALUATION_STATES = NULL;

Symbol* SYM_PROPAGATE_LOGIC_FORWARD_CHAINING_QUEUE = NULL;

Symbol* SYM_PROPAGATE_LOGIC_FORWARD_CHAINING_SET = NULL;

Symbol* SYM_PROPAGATE_LOGIC_DEFERRED_DEFAULT_PROPOSITIONS = NULL;

Symbol* SYM_PROPAGATE_LOGIC_ELABORATED_OBJECTS = NULL;

Symbol* SYM_PROPAGATE_LOGIC_PROPAGATION_ENVIRONMENT = NULL;

Keyword* KWD_PROPAGATE_POSTED = NULL;

Keyword* KWD_PROPAGATE_FORWARD = NULL;

Symbol* SYM_PROPAGATE_LOGIC_BACKWARD_ONLYp = NULL;

Surrogate* SGT_PROPAGATE_LOGIC_NAMED_DESCRIPTION = NULL;

Symbol* SYM_PROPAGATE_LOGIC_FORWARD_ONLYp = NULL;

Surrogate* SGT_PROPAGATE_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_PROPAGATE_LOGIC_F_COLLECT_FORWARD_CHAINING_RULES_MEMO_TABLE_000 = NULL;

Keyword* KWD_PROPAGATE_FUNCTION = NULL;

Keyword* KWD_PROPAGATE_ISA = NULL;

Keyword* KWD_PROPAGATE_PREDICATE = NULL;

Symbol* SYM_PROPAGATE_LOGIC_SKOLEM_GENERATION_COUNT = NULL;

Keyword* KWD_PROPAGATE_PROPAGATE = NULL;

Symbol* SYM_PROPAGATE_LOGIC_HYPOTHESIZED_INSTANCEp = NULL;

Surrogate* SGT_PROPAGATE_PL_KERNEL_KB_AND = NULL;

Keyword* KWD_PROPAGATE_GOAL_TREE = NULL;

Keyword* KWD_PROPAGATE_SINGLETONSp = NULL;

Keyword* KWD_PROPAGATE_INFERENCE_LEVEL = NULL;

Keyword* KWD_PROPAGATE_SHALLOW = NULL;

Surrogate* SGT_PROPAGATE_LOGIC_SKOLEM = NULL;

Surrogate* SGT_PROPAGATE_LOGIC_PROPOSITION = NULL;

Keyword* KWD_PROPAGATE_KB_UPDATE = NULL;

Keyword* KWD_PROPAGATE_META_KB_UPDATE = NULL;

Keyword* KWD_PROPAGATE_META = NULL;

Surrogate* SGT_PROPAGATE_STELLA_MODULE = NULL;

Symbol* SYM_PROPAGATE_LOGIC_DESCRIPTIVEp = NULL;

Surrogate* SGT_PROPAGATE_LOGIC_LOGIC_OBJECT = NULL;

Surrogate* SGT_PROPAGATE_STELLA_SYMBOL = NULL;

Keyword* KWD_PROPAGATE_EVALUATED = NULL;

Keyword* KWD_PROPAGATE_AND = NULL;

Keyword* KWD_PROPAGATE_OR = NULL;

Keyword* KWD_PROPAGATE_NOT = NULL;

Keyword* KWD_PROPAGATE_EQUIVALENT = NULL;

Symbol* SYM_PROPAGATE_LOGIC_CULL_CLASH_EXCEPTIONS = NULL;

Keyword* KWD_PROPAGATE_ELABORATE = NULL;

Keyword* KWD_PROPAGATE_EXTENSIONAL_ASSERTION = NULL;

Surrogate* SGT_PROPAGATE_PL_KERNEL_KB_INEQUALITY = NULL;

Surrogate* SGT_PROPAGATE_STELLA_SURROGATE = NULL;

Keyword* KWD_PROPAGATE_EXISTS = NULL;

Keyword* KWD_PROPAGATE_FORALL = NULL;

Surrogate* SGT_PROPAGATE_PL_KERNEL_KB_EQUIVALENT = NULL;

Symbol* SYM_PROPAGATE_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_PROPAGATE_STELLA_SLOT = NULL;

Surrogate* SGT_PROPAGATE_PL_KERNEL_KB_PHRASE = NULL;

Keyword* KWD_PROPAGATE_IMPLIES = NULL;

Symbol* SYM_PROPAGATE_LOGIC_STARTUP_PROPAGATE = NULL;

Symbol* SYM_PROPAGATE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
