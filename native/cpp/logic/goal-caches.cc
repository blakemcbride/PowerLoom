//  -*- Mode: C++ -*-

// goal-caches.cc

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

GoalCache* newGoalCache() {
  { GoalCache* self = NULL;

    self = new GoalCache();
    self->cacheContext = NULL;
    self->reversePolarityP = false;
    self->proposition = NULL;
    self->timestamp = NULL_INTEGER;
    self->cachedBindings = newList();
    return (self);
  }
}

Surrogate* GoalCache::primaryType() {
  { GoalCache* self = this;

    return (SGT_GOAL_CACHES_LOGIC_GOAL_CACHE);
  }
}

Object* accessGoalCacheSlotValue(GoalCache* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_GOAL_CACHES_LOGIC_CACHED_BINDINGS) {
    if (setvalueP) {
      self->cachedBindings = ((List*)(value));
    }
    else {
      value = self->cachedBindings;
    }
  }
  else if (slotname == SYM_GOAL_CACHES_LOGIC_TIMESTAMP) {
    if (setvalueP) {
      self->timestamp = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->timestamp);
    }
  }
  else if (slotname == SYM_GOAL_CACHES_LOGIC_PROPOSITION) {
    if (setvalueP) {
      self->proposition = ((Proposition*)(value));
    }
    else {
      value = self->proposition;
    }
  }
  else if (slotname == SYM_GOAL_CACHES_LOGIC_REVERSE_POLARITYp) {
    if (setvalueP) {
      self->reversePolarityP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->reversePolarityP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_GOAL_CACHES_LOGIC_CACHE_CONTEXT) {
    if (setvalueP) {
      self->cacheContext = ((Context*)(value));
    }
    else {
      value = self->cacheContext;
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

void traceGoalCache(const char* string, ControlFrame* frame) {
  { Proposition* goal = frame->proposition;

    if (traceKeywordP(KWD_GOAL_CACHES_GOAL_CACHES)) {
      { 
        BIND_STELLA_SPECIAL(oPRINTINFRAMEo, ControlFrame*, frame);
        std::cout << string;
        if (oREVERSEPOLARITYpo) {
          std::cout << "not~";
        }
        std::cout << goal << std::endl;
      }
    }
  }
}

void removeObsoleteGoalCaches(KeyValueList* table) {
  { Context* k = NULL;
    GoalCache* v = NULL;
    KvCons* iter000 = table->theKvList;

    for  (; ((boolean)(iter000)); 
          iter000 = iter000->rest) {
      k = ((Context*)(iter000->key));
      v = ((GoalCache*)(iter000->value));
      if (k->deletedP()) {
        v = v;
        table->removeAt(k);
        removeObsoleteGoalCaches(table);
        break;
      }
    }
  }
}

Cons* yieldGoalBindings(Proposition* goal) {
  { Cons* result = NIL;

    { Object* arg = NULL;
      Vector* vector000 = goal->arguments;
      int index000 = 0;
      int length000 = vector000->length();
      Cons* collect000 = NULL;

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(argumentBoundTo(arg), NIL);
            if (result == NIL) {
              result = collect000;
            }
            else {
              addConsToEndOfConsList(result, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(argumentBoundTo(arg), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (result);
  }
}

KeyValueList* findGoalCacheTable(Proposition* goal) {
  { Keyword* testValue000 = goal->kind;

    if ((testValue000 == KWD_GOAL_CACHES_ISA) ||
        ((testValue000 == KWD_GOAL_CACHES_PREDICATE) ||
         (testValue000 == KWD_GOAL_CACHES_FUNCTION))) {
      { NamedDescription* description = getDescription(((Surrogate*)(goal->operatoR)));

        if (oREVERSEPOLARITYpo) {
          return (((KeyValueList*)(dynamicSlotValue(description->dynamicSlots, SYM_GOAL_CACHES_LOGIC_NEGATED_GOAL_CACHE_TABLE, NULL))));
        }
        else {
          return (((KeyValueList*)(dynamicSlotValue(description->dynamicSlots, SYM_GOAL_CACHES_LOGIC_GOAL_CACHE_TABLE, NULL))));
        }
      }
    }
    else {
      return (NULL);
    }
  }
}

boolean createGoalCacheP(ControlFrame* frame) {
  { Proposition* goal = frame->proposition;
    KeyValueList* table = findGoalCacheTable(goal);

    if (!((boolean)(table))) {
      table = newKeyValueList();
      { Keyword* testValue000 = goal->kind;

        if ((testValue000 == KWD_GOAL_CACHES_ISA) ||
            ((testValue000 == KWD_GOAL_CACHES_PREDICATE) ||
             (testValue000 == KWD_GOAL_CACHES_FUNCTION))) {
          if (goal->operatoR->primaryType() == SGT_GOAL_CACHES_STELLA_SURROGATE) {
            { NamedDescription* goaldescription = getDescription(((Surrogate*)(goal->operatoR)));

              if (oREVERSEPOLARITYpo) {
                setDynamicSlotValue(goaldescription->dynamicSlots, SYM_GOAL_CACHES_LOGIC_NEGATED_GOAL_CACHE_TABLE, table, NULL);
              }
              else {
                setDynamicSlotValue(goaldescription->dynamicSlots, SYM_GOAL_CACHES_LOGIC_GOAL_CACHE_TABLE, table, NULL);
              }
            }
          }
          else {
            return (false);
          }
        }
        else {
          return (false);
        }
      }
    }
    { GoalCache* goalcache = lookupGoalCache(table);

      if (!((boolean)(goalcache))) {
        traceGoalCache("CREATING GOAL CACHE: ", frame);
        goalcache = newGoalCache();
        removeObsoleteGoalCaches(table);
        table->insertAt(oCONTEXTo, goalcache);
        setDynamicSlotValue(frame->dynamicSlots, SYM_GOAL_CACHES_LOGIC_GOAL_CACHE, goalcache, NULL);
        goalcache->timestamp = getNowTimestamp();
        goalcache->proposition = goal;
        goalcache->reversePolarityP = oREVERSEPOLARITYpo;
        goalcache->cacheContext = oCONTEXTo;
        oQUERYITERATORo->activeGoalCaches->insert(goalcache);
        if (topLevelQueryContextP(oCONTEXTo)) {
          oQUERYITERATORo->augmentedGoalCacheP = true;
        }
      }
      return (true);
    }
  }
}

GoalCache* lookupGoalCache(KeyValueList* table) {
  return (((GoalCache*)(table->lookup(oCONTEXTo))));
}

GoalCache* findGoalCache(ControlFrame* frame) {
  { Proposition* goal = frame->proposition;
    KeyValueList* table = findGoalCacheTable(goal);
    GoalCache* goalcache = NULL;

    if (!((boolean)(table))) {
      return (NULL);
    }
    goalcache = lookupGoalCache(table);
    if (((boolean)(goalcache)) &&
        (goalcache->timestamp < getNowTimestamp())) {
      goalcache->cachedBindings->clear();
      goalcache->timestamp = getNowTimestamp();
    }
    return (goalcache);
  }
}

void updateGoalCache(ControlFrame* frame, boolean successP) {
  if ((!(oDUPLICATE_SUBGOAL_STRATEGYo == KWD_GOAL_CACHES_DUPLICATE_GOALS_WITH_CACHING)) ||
      (!successP)) {
    return;
  }
  { GoalCache* goalcache = findGoalCache(frame);

    if (((boolean)(goalcache))) {
      { List* cachedbindings = goalcache->cachedBindings;
        Cons* bindings = yieldRelativeGoalBindings(frame);

        { boolean foundP000 = false;

          { Cons* oldbindings = NULL;
            Cons* iter000 = cachedbindings->theConsList;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              oldbindings = ((Cons*)(iter000->value));
              { boolean alwaysP000 = true;

                { Object* v1 = NULL;
                  Cons* iter001 = bindings;
                  Object* v2 = NULL;
                  Cons* iter002 = oldbindings;

                  for  (; (!(iter001 == NIL)) &&
                            (!(iter002 == NIL)); 
                        iter001 = iter001->rest,
                        iter002 = iter002->rest) {
                    v1 = iter001->value;
                    v2 = iter002->value;
                    if (!eqlP(v1, v2)) {
                      alwaysP000 = false;
                      break;
                    }
                  }
                }
                if (alwaysP000) {
                  foundP000 = true;
                  break;
                }
              }
            }
          }
          if (foundP000) {
            return;
          }
        }
        if (((boolean)(oTRACED_KEYWORDSo)) &&
            oTRACED_KEYWORDSo->membP(KWD_GOAL_CACHES_GOAL_CACHES)) {
          std::cout << "AUGMENT CACHE: " << bindings << "  " << frame << std::endl;
        }
        cachedbindings->push(bindings);
        oQUERYITERATORo->augmentedGoalCacheP = true;
      }
    }
  }
}

Cons* yieldRelativeGoalBindings(ControlFrame* frame) {
  { Proposition* goal = frame->proposition;
    Cons* result = NIL;
    PatternRecord* savecurrentpr = oQUERYITERATORo->currentPatternRecord;

    oQUERYITERATORo->currentPatternRecord = operativePatternRecord(frame);
    { Object* arg = NULL;
      Vector* vector000 = goal->arguments;
      int index000 = 0;
      int length000 = vector000->length();
      Cons* collect000 = NULL;

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(argumentBoundTo(arg), NIL);
            if (result == NIL) {
              result = collect000;
            }
            else {
              addConsToEndOfConsList(result, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(argumentBoundTo(arg), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    oQUERYITERATORo->currentPatternRecord = savecurrentpr;
    return (result);
  }
}

Keyword* continueCachedBindingsProof(ControlFrame* frame, Keyword* lastmove) {
  lastmove = lastmove;
  { Proposition* goal = frame->proposition;
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_GOAL_CACHES_LOGIC_CACHED_BINDINGS_ITERATOR, NULL)));

    if (!((boolean)(iterator))) {
      { GoalCache* goalcache = findGoalCache(frame);
        List* cachedbindings = NULL;

        if (!((boolean)(goalcache))) {
          createGoalCacheP(frame);
          return (KWD_GOAL_CACHES_FAILURE);
        }
        cachedbindings = goalcache->cachedBindings;
        switch (cachedbindings->length()) {
          case 0: 
            traceGoalCache("EMPTY CACHE: ", frame);
            return (KWD_GOAL_CACHES_FAILURE);
          case 1: 
            traceGoalCache("USED CACHED BINDING: ", frame);
            if (bindVectorOfArgumentsToValuesP(goal->arguments, ((Cons*)(cachedbindings->first())))) {
              return (KWD_GOAL_CACHES_FINAL_SUCCESS);
            }
            else {
              return (KWD_GOAL_CACHES_FAILURE);
            }
            break;
          default:
            traceGoalCache("USED MANY CACHED BINDINGS: ", frame);
            iterator = ((ListIterator*)(goalcache->cachedBindings->allocateIterator()));
            setDynamicSlotValue(frame->dynamicSlots, SYM_GOAL_CACHES_LOGIC_CACHED_BINDINGS_ITERATOR, iterator, NULL);
            break;
        }
      }
    }
    createChoicePoint(frame);
    while (iterator->nextP()) {
      if (bindVectorOfArgumentsToValuesP(frame->proposition->arguments, ((Cons*)(iterator->value)))) {
        if (iterator->emptyP()) {
          return (KWD_GOAL_CACHES_FINAL_SUCCESS);
        }
        else {
          return (KWD_GOAL_CACHES_CONTINUING_SUCCESS);
        }
      }
    }
    return (KWD_GOAL_CACHES_FAILURE);
  }
}

boolean topLevelQueryContextP(Context* self) {
  { Context* querycontext = oQUERYITERATORo->queryContext;

    return ((self == querycontext) ||
        (worldStateP(self) ||
         (((Context*)(dynamicSlotValue(((World*)(self))->dynamicSlots, SYM_GOAL_CACHES_LOGIC_INFERENCE_CACHE_OF, NULL))) == querycontext)));
  }
}

boolean cacheQueryResultsP() {
  return ((oCACHE_SUCCEEDED_GOALSpo ||
      oCACHE_FAILED_GOALSpo) &&
      ((oDUPLICATE_SUBGOAL_STRATEGYo == KWD_GOAL_CACHES_DUPLICATE_GOALS) &&
       (!(((boolean)(oQUERYITERATORo)) &&
      ((boolean)(oQUERYITERATORo->partialMatchStrategy))))));
}

boolean oCACHE_SUCCEEDED_GOALSpo = true;

boolean oCACHE_FAILED_GOALSpo = true;

// Only goals whose success or failure took at least this
// number of query clock ticks will be cached.
int oCACHE_GOAL_QUANTUMo = 5;

const char* toggleGoalCaching() {
  if (oCACHE_SUCCEEDED_GOALSpo) {
    {
      oCACHE_SUCCEEDED_GOALSpo = false;
      oCACHE_FAILED_GOALSpo = false;
      incrementNowTimestamp();
      return ("Disabled goal caching.");
    }
  }
  else {
    {
      oCACHE_SUCCEEDED_GOALSpo = true;
      oCACHE_FAILED_GOALSpo = true;
      return ("Enabled goal caching.");
    }
  }
}

StringWrapper* toggleGoalCachingEvaluatorWrapper(Cons* arguments) {
  arguments = arguments;
  { const char* result = toggleGoalCaching();

    if (result != NULL) {
      return (wrapString(result));
    }
    else {
      return (NULL);
    }
  }
}

AtomicGoalCache* newAtomicGoalCache() {
  { AtomicGoalCache* self = NULL;

    self = new AtomicGoalCache();
    self->next = NULL;
    self->previous = NULL;
    self->matchScore = NULL_FLOAT;
    self->justification = NULL;
    self->bindings = NULL;
    self->proposition = NULL;
    self->reversePolarityP = false;
    self->truthValue = NULL;
    self->timestamp = NULL_INTEGER;
    self->goalContext = NULL;
    return (self);
  }
}

Surrogate* AtomicGoalCache::primaryType() {
  { AtomicGoalCache* self = this;

    return (SGT_GOAL_CACHES_LOGIC_ATOMIC_GOAL_CACHE);
  }
}

Object* accessAtomicGoalCacheSlotValue(AtomicGoalCache* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_GOAL_CACHES_LOGIC_GOAL_CONTEXT) {
    if (setvalueP) {
      self->goalContext = ((Context*)(value));
    }
    else {
      value = self->goalContext;
    }
  }
  else if (slotname == SYM_GOAL_CACHES_LOGIC_TIMESTAMP) {
    if (setvalueP) {
      self->timestamp = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->timestamp);
    }
  }
  else if (slotname == SYM_GOAL_CACHES_LOGIC_TRUTH_VALUE) {
    if (setvalueP) {
      self->truthValue = ((TruthValue*)(value));
    }
    else {
      value = self->truthValue;
    }
  }
  else if (slotname == SYM_GOAL_CACHES_LOGIC_REVERSE_POLARITYp) {
    if (setvalueP) {
      self->reversePolarityP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->reversePolarityP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_GOAL_CACHES_LOGIC_PROPOSITION) {
    if (setvalueP) {
      self->proposition = ((Proposition*)(value));
    }
    else {
      value = self->proposition;
    }
  }
  else if (slotname == SYM_GOAL_CACHES_LOGIC_BINDINGS) {
    if (setvalueP) {
      self->bindings = ((Cons*)(value));
    }
    else {
      value = self->bindings;
    }
  }
  else if (slotname == SYM_GOAL_CACHES_LOGIC_JUSTIFICATION) {
    if (setvalueP) {
      self->justification = ((Justification*)(value));
    }
    else {
      value = self->justification;
    }
  }
  else if (slotname == SYM_GOAL_CACHES_LOGIC_MATCH_SCORE) {
    if (setvalueP) {
      self->matchScore = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->matchScore);
    }
  }
  else if (slotname == SYM_GOAL_CACHES_LOGIC_PREVIOUS) {
    if (setvalueP) {
      self->previous = ((AtomicGoalCache*)(value));
    }
    else {
      value = self->previous;
    }
  }
  else if (slotname == SYM_GOAL_CACHES_STELLA_NEXT) {
    if (setvalueP) {
      self->next = ((AtomicGoalCache*)(value));
    }
    else {
      value = self->next;
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

void AtomicGoalCache::printObject(std::ostream* stream) {
  { AtomicGoalCache* self = this;

    printAtomicGoalCache(self, stream);
  }
}

void printAtomicGoalCache(AtomicGoalCache* self, std::ostream* stream) {
  if (!((boolean)(self->proposition))) {
    *(stream) << "|GC|[NULL]";
    return;
  }
  *(stream) << "|GC|[" << ((self->reversePolarityP ? "~" : "")) << "(" << stringifiedKifOperator(self->proposition);
  { 
    BIND_STELLA_SPECIAL(oPRINTMODEo, Keyword*, KWD_GOAL_CACHES_REALISTIC);
    BIND_STELLA_SPECIAL(oPRINTLOGICALFORMSTREAMo, OutputStream*, wrapNativeOutputStream(stream));
    { Object* arg = NULL;
      Vector* vector000 = self->proposition->arguments;
      int index000 = 0;
      int length000 = vector000->length();
      Object* argvalue = NULL;
      Cons* iter000 = self->bindings;

      for  (; (index000 < length000) &&
                (!(iter000 == NIL)); 
            index000 = index000 + 1,
            iter000 = iter000->rest) {
        arg = (vector000->theArray)[index000];
        argvalue = iter000->value;
        *(stream) << " ";
        printAsKifInternal(((!((boolean)(argvalue))) ? arg : argvalue));
      }
    }
  }
  *(stream) << ") time: " << self->timestamp << " ctxt: " << self->goalContext->contextNumber << "]";
}

Vector* oSUCCEEDED_GOALS_CACHEo = NULL;

Vector* oFAILED_GOALS_CACHEo = NULL;

void clearQueryResultsCache() {
  { AtomicGoalCache* cache = NULL;
    Vector* vector000 = oSUCCEEDED_GOALS_CACHEo;
    int index000 = 0;
    int length000 = vector000->length();

    for  (; index000 < length000; 
          index000 = index000 + 1) {
      cache = ((AtomicGoalCache*)((vector000->theArray)[index000]));
      if (((boolean)(cache))) {
        setGoalCacheList(cache->proposition, NULL);
      }
    }
  }
  oSUCCEEDED_GOALS_CACHEo->clear();
  oFAILED_GOALS_CACHEo->clear();
  oFAILED_GOAL_CUTOFFSo = 0;
  oSUCCEEDED_GOAL_CUTOFFSo = 0;
}

void printQueryResultsCache(int limit) {
  if (limit == NULL_INTEGER) {
    limit = 100;
  }
  { int count = limit;

    std::cout << "Failed goal cutoffs:    " << oFAILED_GOAL_CUTOFFSo << std::endl;
    std::cout << "Succeeded goal cutoffs: " << oSUCCEEDED_GOAL_CUTOFFSo << std::endl << std::endl;
    std::cout << "Cached failed goals:" << std::endl;
    { AtomicGoalCache* cache = NULL;
      Vector* vector000 = oFAILED_GOALS_CACHEo;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter000 = 0;

      for  (; index000 < length000; 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        cache = ((AtomicGoalCache*)((vector000->theArray)[index000]));
        i = iter000;
        { boolean testValue000 = false;

          testValue000 = ((boolean)(cache));
          if (testValue000) {
            testValue000 = !cache->proposition->deletedP();
            if (testValue000) {
              testValue000 = !(cache->proposition->operatoR->symbolId == -1);
              if (testValue000) {
                { boolean foundP000 = false;

                  { Object* arg = NULL;
                    Vector* vector001 = cache->proposition->arguments;
                    int index001 = 0;
                    int length001 = vector001->length();
                    Object* binding = NULL;
                    Cons* iter001 = cache->bindings;

                    for  (; (index001 < length001) &&
                              (!(iter001 == NIL)); 
                          index001 = index001 + 1,
                          iter001 = iter001->rest) {
                      arg = (vector001->theArray)[index001];
                      binding = iter001->value;
                      if (arg->deletedP() ||
                          (((boolean)(binding)) &&
                           binding->deletedP())) {
                        foundP000 = true;
                        break;
                      }
                    }
                  }
                  testValue000 = foundP000;
                }
                testValue000 = !testValue000;
              }
            }
          }
          if (testValue000) {
            if (count <= 0) {
              break;
            }
            std::cout << i << ": " << cache << std::endl;
            count = count - 1;
          }
        }
      }
    }
    count = limit;
    std::cout << std::endl << "Cached succeeded goals:" << std::endl;
    { AtomicGoalCache* cache = NULL;
      Vector* vector002 = oSUCCEEDED_GOALS_CACHEo;
      int index002 = 0;
      int length002 = vector002->length();
      int i = NULL_INTEGER;
      int iter002 = 0;

      for  (; index002 < length002; 
            index002 = index002 + 1,
            iter002 = iter002 + 1) {
        cache = ((AtomicGoalCache*)((vector002->theArray)[index002]));
        i = iter002;
        { boolean testValue001 = false;

          testValue001 = ((boolean)(cache));
          if (testValue001) {
            testValue001 = !cache->proposition->deletedP();
            if (testValue001) {
              testValue001 = !(cache->proposition->operatoR->symbolId == -1);
              if (testValue001) {
                { boolean foundP001 = false;

                  { Object* arg = NULL;
                    Vector* vector003 = cache->proposition->arguments;
                    int index003 = 0;
                    int length003 = vector003->length();
                    Object* binding = NULL;
                    Cons* iter003 = cache->bindings;

                    for  (; (index003 < length003) &&
                              (!(iter003 == NIL)); 
                          index003 = index003 + 1,
                          iter003 = iter003->rest) {
                      arg = (vector003->theArray)[index003];
                      binding = iter003->value;
                      if (arg->deletedP() ||
                          (((boolean)(binding)) &&
                           binding->deletedP())) {
                        foundP001 = true;
                        break;
                      }
                    }
                  }
                  testValue001 = foundP001;
                }
                testValue001 = !testValue001;
              }
            }
          }
          if (testValue001) {
            if (count <= 0) {
              break;
            }
            std::cout << i << ": " << cache << std::endl;
            count = count - 1;
          }
        }
      }
    }
  }
}

int succeededGoalIndex(ControlFrame* frame) {
  return ((((unsigned int) (goalHashCode(frame))) % 1541));
}

int failedGoalIndex(ControlFrame* frame) {
  return ((((unsigned int) (goalHashCode(frame))) % 1541));
}

int goalHashCode(ControlFrame* frame) {
  { Proposition* proposition = frame->proposition;
    Surrogate* operatoR = cachedGoalOperator(proposition);
    Vector* arguments = proposition->arguments;
    int code = 0;

    code = oCONTEXTo->hashCode();
    if (frame->reversePolarityP) {
      code = (((((code & 1) == 0) ? ((unsigned int)code >> 1) : (((code >> 1)) | oINTEGER_MSB_MASKo))) ^ 8312004);
    }
    code = (((((code & 1) == 0) ? ((unsigned int)code >> 1) : (((code >> 1)) | oINTEGER_MSB_MASKo))) ^ (safeHashCode(operatoR)));
    { Object* arg = NULL;
      Vector* vector000 = arguments;
      int index000 = 0;
      int length000 = vector000->length();
      Object* argvalue = NULL;
      Cons* iter000 = frame->goalBindings;

      for  (; (index000 < length000) &&
                (!(iter000 == NIL)); 
            index000 = index000 + 1,
            iter000 = iter000->rest) {
        arg = (vector000->theArray)[index000];
        argvalue = iter000->value;
        if (!((boolean)(argvalue))) {
          argvalue = (oQUERYITERATORo->currentPatternRecord->variableBindings->theArray)[(((PatternVariable*)(arg))->boundToOffset)];
          if (!((boolean)(argvalue))) {
            code = hashUnboundGoalVariable(((PatternVariable*)(arg)), arguments, code);
            continue;
          }
        }
        code = hashGoalArgument(argvalue, code);
      }
    }
    return (code);
  }
}

int hashUnboundGoalVariable(PatternVariable* var, Vector* arguments, int code) {
  { int varindex = 1;

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
        if (var == arg) {
          return (hashString("#v", code + varindex));
        }
        else if (isaP(arg, SGT_GOAL_CACHES_LOGIC_PATTERN_VARIABLE) &&
            (arguments->position(arg, 0) == i)) {
          varindex = varindex + 1;
        }
      }
    }
    throw *newStellaException("Shouldn't get here!");
  }
}

int hashGoalArgument(Object* arg, int code) {
  { Object* hashedarg = arg;

    { Surrogate* testValue000 = safePrimaryType(arg);

      if (subtypeOfP(testValue000, SGT_GOAL_CACHES_LOGIC_SKOLEM)) {
        { Object* arg000 = arg;
          Skolem* arg = ((Skolem*)(arg000));

        }
      }
      else if (subtypeOfP(testValue000, SGT_GOAL_CACHES_LOGIC_LOGIC_OBJECT)) {
        { Object* arg001 = arg;
          LogicObject* arg = ((LogicObject*)(arg001));

          if (!((boolean)(arg->surrogateValueInverse))) {
            hashedarg = wrapString(stringify(arg));
          }
        }
      }
      else {
      }
    }
    return ((((((code & 1) == 0) ? ((unsigned int)code >> 1) : (((code >> 1)) | oINTEGER_MSB_MASKo))) ^ (safeEqualHashCode(hashedarg))));
  }
}

Surrogate* cachedGoalOperator(Proposition* goal) {
  { Keyword* testValue000 = goal->kind;

    if ((testValue000 == KWD_GOAL_CACHES_ISA) ||
        ((testValue000 == KWD_GOAL_CACHES_PREDICATE) ||
         (testValue000 == KWD_GOAL_CACHES_FUNCTION))) {
      { GeneralizedSymbol* operatoR = goal->operatoR;

        if (((boolean)(operatoR)) &&
            (isaP(operatoR, SGT_GOAL_CACHES_STELLA_SURROGATE) &&
             (!(operatoR->symbolId == -1)))) {
          return (((Surrogate*)(operatoR)));
        }
      }
    }
    else {
    }
  }
  return (NULL);
}

AtomicGoalCache* getGoalCacheList(Proposition* goal) {
  { Surrogate* operatoR = cachedGoalOperator(goal);
    NamedDescription* description = (((boolean)(operatoR)) ? getDescription(operatoR) : NULL);

    if (((boolean)(description)) &&
        (!description->deletedP())) {
      return (((AtomicGoalCache*)(dynamicSlotValue(description->dynamicSlots, SYM_GOAL_CACHES_LOGIC_GOAL_CACHE_LIST, NULL))));
    }
    else {
      return (NULL);
    }
  }
}

AtomicGoalCache* setGoalCacheList(Proposition* goal, AtomicGoalCache* firstcache) {
  { Surrogate* operatoR = cachedGoalOperator(goal);
    NamedDescription* description = (((boolean)(operatoR)) ? getDescription(operatoR) : NULL);

    if (((boolean)(description)) &&
        (!description->deletedP())) {
      return (((AtomicGoalCache*)(setDynamicSlotValue(description->dynamicSlots, SYM_GOAL_CACHES_LOGIC_GOAL_CACHE_LIST, firstcache, NULL))));
    }
    else {
      return (NULL);
    }
  }
}

AtomicGoalCache* createAtomicGoalCache(ControlFrame* frame, AtomicGoalCache* cache, boolean successP) {
  { boolean collisionP = ((boolean)(cache));
    Proposition* proposition = frame->proposition;

    if (!collisionP) {
      cache = newAtomicGoalCache();
    }
    if (successP) {
      if (collisionP) {
        if (((boolean)(cache->next))) {
          cache->next->previous = cache->previous;
        }
        if (!((boolean)(cache->previous))) {
          setGoalCacheList(cache->proposition, cache->next);
        }
        else {
          cache->previous->next = cache->next;
        }
        cache->previous = NULL;
        cache->next = NULL;
      }
      { AtomicGoalCache* previousstart = getGoalCacheList(proposition);

        if (!(cache == previousstart)) {
          if (((boolean)(previousstart))) {
            previousstart->previous = cache;
            cache->next = previousstart;
          }
        }
      }
      setGoalCacheList(proposition, cache);
    }
    cache->goalContext = oCONTEXTo;
    cache->timestamp = getNowTimestamp();
    cache->reversePolarityP = frame->reversePolarityP;
    cache->proposition = proposition;
    cache->bindings = yieldGoalBindings(proposition);
    cache->justification = (successP ? ((Justification*)(dynamicSlotValue(frame->dynamicSlots, SYM_GOAL_CACHES_LOGIC_JUSTIFICATION, NULL))) : NULL);
    cache->truthValue = frame->truthValue;
    if (((boolean)(oQUERYITERATORo)) &&
        ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
      frame->setCachePartialTruth(cache);
    }
    frame->cachedGoalResultP = true;
    return (cache);
  }
}

DEFINE_STELLA_SPECIAL(oUNIFICATION_VECTOR_1o, Vector* , NULL);

DEFINE_STELLA_SPECIAL(oUNIFICATION_VECTOR_2o, Vector* , NULL);

boolean cacheMatchesGoalP(AtomicGoalCache* cache, ControlFrame* goal, boolean successP, Keyword* mode) {
  successP = successP;
  if ((getNowTimestamp() == cache->timestamp) &&
      ((oCONTEXTo == cache->goalContext) &&
       (goal->reversePolarityP == cache->reversePolarityP))) {
    { Proposition* goalproposition = goal->proposition;
      Vector* goalarguments = goalproposition->arguments;
      Proposition* cacheproposition = cache->proposition;
      Vector* cachearguments = cacheproposition->arguments;
      int nofgoalarguments = goalarguments->length();
      Object** uvector1 = oUNIFICATION_VECTOR_1o->theArray;
      Object** uvector2 = oUNIFICATION_VECTOR_2o->theArray;

      if ((goalproposition->operatoR == cacheproposition->operatoR) &&
          (nofgoalarguments == cachearguments->length())) {
        if (nofgoalarguments > oUNIFICATION_VECTOR_1o->arraySize) {
          resizeVector(oUNIFICATION_VECTOR_1o, 2 * nofgoalarguments);
          resizeVector(oUNIFICATION_VECTOR_2o, 2 * nofgoalarguments);
          uvector1 = oUNIFICATION_VECTOR_1o->theArray;
          uvector2 = oUNIFICATION_VECTOR_2o->theArray;
        }
        { Object* goalarg = NULL;
          Vector* vector000 = goalarguments;
          int index000 = 0;
          int length000 = vector000->length();
          Object* goalbinding = NULL;
          Cons* iter000 = goal->goalBindings;
          Object* cachebinding = NULL;
          Cons* iter001 = cache->bindings;
          int i = NULL_INTEGER;
          int iter002 = 0;

          for  (; (index000 < length000) &&
                    ((!(iter000 == NIL)) &&
                     (!(iter001 == NIL))); 
                index000 = index000 + 1,
                iter000 = iter000->rest,
                iter001 = iter001->rest,
                iter002 = iter002 + 1) {
            goalarg = (vector000->theArray)[index000];
            goalbinding = iter000->value;
            cachebinding = iter001->value;
            i = iter002;
            if (!((boolean)(goalbinding))) {
              goalbinding = (oQUERYITERATORo->currentPatternRecord->variableBindings->theArray)[(((PatternVariable*)(goalarg))->boundToOffset)];
            }
            uvector1[i] = goalbinding;
            uvector2[i] = cachebinding;
          }
        }
        { Vector* subarguments = goalarguments;
          Object** subbindings = uvector1;
          Object* subargbinding = NULL;
          Vector* superarguments = cachearguments;
          Object** superbindings = uvector2;
          Object* unifiedarg = NULL;

          if (mode == KWD_GOAL_CACHES_GOAL_INSTANTIATES_CACHE) {
          }
          else if (mode == KWD_GOAL_CACHES_CACHE_INSTANTIATES_GOAL) {
            subarguments = cachearguments;
            subbindings = uvector2;
            superarguments = goalarguments;
            superbindings = uvector1;
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << mode << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
          { Object* subarg = NULL;
            Vector* vector001 = subarguments;
            int index001 = 0;
            int length001 = vector001->length();
            Object* superarg = NULL;
            Vector* vector002 = superarguments;
            int index002 = 0;
            int length002 = vector002->length();
            int i = NULL_INTEGER;
            int iter003 = 0;

            for  (; (index001 < length001) &&
                      (index002 < length002); 
                  index001 = index001 + 1,
                  index002 = index002 + 1,
                  iter003 = iter003 + 1) {
              subarg = (vector001->theArray)[index001];
              superarg = (vector002->theArray)[index002];
              i = iter003;
              subargbinding = subbindings[i];
              unifiedarg = superbindings[i];
              if (((boolean)(unifiedarg))) {
                if (!eqlP(subargbinding, unifiedarg)) {
                  return (false);
                }
                else {
                  continue;
                }
              }
              if (!((boolean)(subargbinding))) {
                subargbinding = subarg;
              }
              { Object* suparg = NULL;
                Vector* vector003 = superarguments;
                int index003 = 0;
                int length003 = vector003->length();
                int i = NULL_INTEGER;
                int iter004 = 0;

                for  (; index003 < length003; 
                      index003 = index003 + 1,
                      iter004 = iter004 + 1) {
                  suparg = (vector003->theArray)[index003];
                  i = iter004;
                  if (eqlP(suparg, superarg)) {
                    superbindings[i] = subargbinding;
                  }
                }
              }
            }
          }
          return (true);
        }
      }
    }
  }
  return (false);
}

boolean goalInstantiatesCacheP(ControlFrame* goal, AtomicGoalCache* cache, boolean successP) {
  return (cacheMatchesGoalP(cache, goal, successP, KWD_GOAL_CACHES_GOAL_INSTANTIATES_CACHE));
}

boolean cacheInstantiatesGoalP(AtomicGoalCache* cache, ControlFrame* goal, boolean successP) {
  return (cacheMatchesGoalP(cache, goal, successP, KWD_GOAL_CACHES_CACHE_INSTANTIATES_GOAL));
}

void dontCacheGoalFailureBetweenFrames(ControlFrame* topframe, ControlFrame* bottomframe) {
  for (;;) {
    topframe->dontCacheGoalFailureP = true;
    if (topframe == bottomframe) {
      return;
    }
    topframe = topframe->up;
  }
}

void cacheGoal(ControlFrame* frame, boolean successP, boolean keepframeP, int clockticks) {
  keepframeP = keepframeP;
  if (frame->state == KWD_GOAL_CACHES_ATOMIC_GOAL) {
    if (!((boolean)(frame->goalBindings))) {
      return;
    }
    { Object* binding = NULL;
      Cons* iter000 = frame->goalBindings;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        binding = iter000->value;
        if (((boolean)(binding))) {
          { Surrogate* testValue000 = safePrimaryType(binding);

            if (subtypeOfP(testValue000, SGT_GOAL_CACHES_LOGIC_DESCRIPTION)) {
              { Object* binding000 = binding;
                Description* binding = ((Description*)(binding000));

                if (((boolean)(((Vector*)(dynamicSlotValue(binding->dynamicSlots, SYM_GOAL_CACHES_LOGIC_EXTERNAL_VARIABLES, NULL)))))) {
                  return;
                }
              }
            }
            else if (subtypeOfP(testValue000, SGT_GOAL_CACHES_LOGIC_PROPOSITION)) {
              { Object* binding001 = binding;
                Proposition* binding = ((Proposition*)(binding001));

                return;
              }
            }
            else {
            }
          }
        }
      }
    }
    if (successP) {
      frame->dontCacheGoalFailureP = true;
    }
    if (frame->cachedGoalResultP) {
      return;
    }
    if (((clockticks - frame->startingClockTicks) >= oCACHE_GOAL_QUANTUMo) ||
        (false &&
         testPropertyP(surrogateToDescription(((Surrogate*)(frame->proposition->operatoR))), SGT_GOAL_CACHES_PL_KERNEL_KB_FRAME_PREDICATE))) {
      { Keyword* testValue001 = frame->proposition->kind;

        if ((testValue001 == KWD_GOAL_CACHES_ISA) ||
            ((testValue001 == KWD_GOAL_CACHES_PREDICATE) ||
             (testValue001 == KWD_GOAL_CACHES_FUNCTION))) {
          if (getQuotedTree("((/PL-KERNEL-KB/@FORK /PL-KERNEL-KB/@COLLECT-INTO-SET) \"/LOGIC\")", "/LOGIC")->memberP(frame->proposition->operatoR)) {
            return;
          }
          if (traceKeywordP(KWD_GOAL_CACHES_GOAL_CACHES)) {
            std::cout << "=========> CACHED " << ((successP ? "SUCCESS" : "FAILURE")) << " AT " << (((unsigned int) (goalHashCode(frame))) % 1541) << ": " << frame->proposition << std::endl;
          }
          updateNowTimestamp(KWD_GOAL_CACHES_EXECUTE_QUERY);
          setDynamicSlotValue(surrogateToDescription(((Surrogate*)(frame->proposition->operatoR)))->dynamicSlots, SYM_GOAL_CACHES_LOGIC_CHECK_FOR_CACHED_GOALSp, TRUE_WRAPPER, FALSE_WRAPPER);
          { int index = NULL_INTEGER;
            AtomicGoalCache* cachedgoal = NULL;

            if (successP) {
              if (!oCACHE_SUCCEEDED_GOALSpo) {
                return;
              }
              index = (((unsigned int) (goalHashCode(frame))) % 1541);
              cachedgoal = ((AtomicGoalCache*)((oSUCCEEDED_GOALS_CACHEo->theArray)[index]));
              if ((!((boolean)(cachedgoal))) ||
                  ((!cacheMatchesGoalP(cachedgoal, frame, true, KWD_GOAL_CACHES_GOAL_INSTANTIATES_CACHE)) ||
                   (oRECORD_JUSTIFICATIONSpo &&
                    (!((boolean)(cachedgoal->justification)))))) {
                (oSUCCEEDED_GOALS_CACHEo->theArray)[index] = (createAtomicGoalCache(frame, cachedgoal, true));
              }
              else if (((boolean)(cachedgoal))) {
                cachedgoal->truthValue = strengthenTruthValue(cachedgoal->truthValue, frame->truthValue);
              }
            }
            else {
              if ((!oCACHE_FAILED_GOALSpo) ||
                  frame->dontCacheGoalFailureP) {
                return;
              }
              index = (((unsigned int) (goalHashCode(frame))) % 1541);
              cachedgoal = ((AtomicGoalCache*)((oFAILED_GOALS_CACHEo->theArray)[index]));
              if ((!((boolean)(cachedgoal))) ||
                  (!cacheMatchesGoalP(cachedgoal, frame, false, KWD_GOAL_CACHES_GOAL_INSTANTIATES_CACHE))) {
                (oFAILED_GOALS_CACHEo->theArray)[index] = (createAtomicGoalCache(frame, cachedgoal, false));
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

AtomicGoalCache* findCachedGoal(ControlFrame* frame, Keyword* successorfailure) {
  if (frame->state == KWD_GOAL_CACHES_ATOMIC_GOAL) {
    { Keyword* testValue000 = frame->proposition->kind;

      if ((testValue000 == KWD_GOAL_CACHES_ISA) ||
          ((testValue000 == KWD_GOAL_CACHES_PREDICATE) ||
           (testValue000 == KWD_GOAL_CACHES_FUNCTION))) {
        { AtomicGoalCache* cachedgoal = NULL;

          if (successorfailure == KWD_GOAL_CACHES_SUCCESS) {
            if (!oCACHE_SUCCEEDED_GOALSpo) {
              return (NULL);
            }
            cachedgoal = ((AtomicGoalCache*)((oSUCCEEDED_GOALS_CACHEo->theArray)[((((unsigned int) (goalHashCode(frame))) % 1541))]));
            if (((boolean)(cachedgoal)) &&
                (cacheMatchesGoalP(cachedgoal, frame, true, KWD_GOAL_CACHES_GOAL_INSTANTIATES_CACHE) &&
                 ((!oRECORD_JUSTIFICATIONSpo) ||
                  ((boolean)(cachedgoal->justification))))) {
              return (cachedgoal);
            }
          }
          else if (successorfailure == KWD_GOAL_CACHES_FAILURE) {
            if ((!oCACHE_FAILED_GOALSpo) ||
                frame->dontCacheGoalFailureP) {
              return (NULL);
            }
            cachedgoal = ((AtomicGoalCache*)((oFAILED_GOALS_CACHEo->theArray)[((((unsigned int) (goalHashCode(frame))) % 1541))]));
            if (((boolean)(cachedgoal)) &&
                cacheMatchesGoalP(cachedgoal, frame, false, KWD_GOAL_CACHES_GOAL_INSTANTIATES_CACHE)) {
              return (cachedgoal);
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << successorfailure << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
      }
      else {
      }
    }
  }
  return (NULL);
}

AtomicGoalCacheIterator* newAtomicGoalCacheIterator() {
  { AtomicGoalCacheIterator* self = NULL;

    self = new AtomicGoalCacheIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->cacheList = NULL;
    self->goal = NULL;
    return (self);
  }
}

Surrogate* AtomicGoalCacheIterator::primaryType() {
  { AtomicGoalCacheIterator* self = this;

    return (SGT_GOAL_CACHES_LOGIC_ATOMIC_GOAL_CACHE_ITERATOR);
  }
}

Object* accessAtomicGoalCacheIteratorSlotValue(AtomicGoalCacheIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_GOAL_CACHES_LOGIC_GOAL) {
    if (setvalueP) {
      self->goal = ((ControlFrame*)(value));
    }
    else {
      value = self->goal;
    }
  }
  else if (slotname == SYM_GOAL_CACHES_LOGIC_CACHE_LIST) {
    if (setvalueP) {
      self->cacheList = ((AtomicGoalCache*)(value));
    }
    else {
      value = self->cacheList;
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

AtomicGoalCacheIterator* allCachedPropositions(ControlFrame* goal) {
  { Proposition* proposition = goal->proposition;
    GeneralizedSymbol* operatoR = proposition->operatoR;
    AtomicGoalCache* cachelist = getGoalCacheList(proposition);

    while (((boolean)(cachelist)) &&
        (!(cachelist->proposition->operatoR == operatoR))) {
      cachelist = cachelist->next;
    }
    setGoalCacheList(proposition, cachelist);
    { AtomicGoalCacheIterator* self000 = newAtomicGoalCacheIterator();

      self000->goal = goal;
      self000->cacheList = cachelist;
      { AtomicGoalCacheIterator* value000 = self000;

        return (value000);
      }
    }
  }
}

boolean AtomicGoalCacheIterator::nextP() {
  { AtomicGoalCacheIterator* self = this;

    { ControlFrame* goal = self->goal;
      AtomicGoalCache* cachelist = self->cacheList;

      if (((boolean)(cachelist)) &&
          (!(goal->proposition->operatoR == cachelist->proposition->operatoR))) {
        self->cacheList = NULL;
        return (false);
      }
      while (((boolean)(cachelist)) &&
          ((!cacheMatchesGoalP(cachelist, goal, true, KWD_GOAL_CACHES_CACHE_INSTANTIATES_GOAL)) ||
           (((!(!oDONTUSEDEFAULTKNOWLEDGEpo)) &&
          ((goal->truthValue == DEFAULT_TRUE_TRUTH_VALUE) ||
           (goal->truthValue == DEFAULT_FALSE_TRUTH_VALUE))) ||
            (oRECORD_JUSTIFICATIONSpo &&
             (!((boolean)(cachelist->justification))))))) {
        cachelist = cachelist->next;
      }
      if (((boolean)(cachelist))) {
        self->value = cachelist;
        self->cacheList = cachelist->next;
        return (true);
      }
      else {
        return (false);
      }
    }
  }
}

void helpStartupGoalCaches1() {
  {
    SGT_GOAL_CACHES_LOGIC_GOAL_CACHE = ((Surrogate*)(internRigidSymbolWrtModule("GOAL-CACHE", NULL, 1)));
    SYM_GOAL_CACHES_LOGIC_CACHED_BINDINGS = ((Symbol*)(internRigidSymbolWrtModule("CACHED-BINDINGS", NULL, 0)));
    SYM_GOAL_CACHES_LOGIC_TIMESTAMP = ((Symbol*)(internRigidSymbolWrtModule("TIMESTAMP", NULL, 0)));
    SYM_GOAL_CACHES_LOGIC_PROPOSITION = ((Symbol*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 0)));
    SYM_GOAL_CACHES_LOGIC_REVERSE_POLARITYp = ((Symbol*)(internRigidSymbolWrtModule("REVERSE-POLARITY?", NULL, 0)));
    SYM_GOAL_CACHES_LOGIC_CACHE_CONTEXT = ((Symbol*)(internRigidSymbolWrtModule("CACHE-CONTEXT", NULL, 0)));
    KWD_GOAL_CACHES_GOAL_CACHES = ((Keyword*)(internRigidSymbolWrtModule("GOAL-CACHES", NULL, 2)));
    SYM_GOAL_CACHES_LOGIC_GOAL_CACHE_TABLE = ((Symbol*)(internRigidSymbolWrtModule("GOAL-CACHE-TABLE", NULL, 0)));
    KWD_GOAL_CACHES_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    KWD_GOAL_CACHES_PREDICATE = ((Keyword*)(internRigidSymbolWrtModule("PREDICATE", NULL, 2)));
    KWD_GOAL_CACHES_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SYM_GOAL_CACHES_LOGIC_NEGATED_GOAL_CACHE_TABLE = ((Symbol*)(internRigidSymbolWrtModule("NEGATED-GOAL-CACHE-TABLE", NULL, 0)));
    SGT_GOAL_CACHES_STELLA_SURROGATE = ((Surrogate*)(internRigidSymbolWrtModule("SURROGATE", getStellaModule("/STELLA", true), 1)));
    SYM_GOAL_CACHES_LOGIC_GOAL_CACHE = ((Symbol*)(internRigidSymbolWrtModule("GOAL-CACHE", NULL, 0)));
    KWD_GOAL_CACHES_DUPLICATE_GOALS_WITH_CACHING = ((Keyword*)(internRigidSymbolWrtModule("DUPLICATE-GOALS-WITH-CACHING", NULL, 2)));
    SYM_GOAL_CACHES_LOGIC_CACHED_BINDINGS_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("CACHED-BINDINGS-ITERATOR", NULL, 0)));
    KWD_GOAL_CACHES_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("FAILURE", NULL, 2)));
    KWD_GOAL_CACHES_FINAL_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("FINAL-SUCCESS", NULL, 2)));
    KWD_GOAL_CACHES_CONTINUING_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("CONTINUING-SUCCESS", NULL, 2)));
    SYM_GOAL_CACHES_LOGIC_INFERENCE_CACHE_OF = ((Symbol*)(internRigidSymbolWrtModule("INFERENCE-CACHE-OF", NULL, 0)));
    KWD_GOAL_CACHES_DUPLICATE_GOALS = ((Keyword*)(internRigidSymbolWrtModule("DUPLICATE-GOALS", NULL, 2)));
    SGT_GOAL_CACHES_LOGIC_ATOMIC_GOAL_CACHE = ((Surrogate*)(internRigidSymbolWrtModule("ATOMIC-GOAL-CACHE", NULL, 1)));
    SYM_GOAL_CACHES_LOGIC_GOAL_CONTEXT = ((Symbol*)(internRigidSymbolWrtModule("GOAL-CONTEXT", NULL, 0)));
    SYM_GOAL_CACHES_LOGIC_TRUTH_VALUE = ((Symbol*)(internRigidSymbolWrtModule("TRUTH-VALUE", NULL, 0)));
    SYM_GOAL_CACHES_LOGIC_BINDINGS = ((Symbol*)(internRigidSymbolWrtModule("BINDINGS", NULL, 0)));
    SYM_GOAL_CACHES_LOGIC_JUSTIFICATION = ((Symbol*)(internRigidSymbolWrtModule("JUSTIFICATION", NULL, 0)));
    SYM_GOAL_CACHES_LOGIC_MATCH_SCORE = ((Symbol*)(internRigidSymbolWrtModule("MATCH-SCORE", NULL, 0)));
    SYM_GOAL_CACHES_LOGIC_PREVIOUS = ((Symbol*)(internRigidSymbolWrtModule("PREVIOUS", NULL, 0)));
    SYM_GOAL_CACHES_STELLA_NEXT = ((Symbol*)(internRigidSymbolWrtModule("NEXT", getStellaModule("/STELLA", true), 0)));
    KWD_GOAL_CACHES_REALISTIC = ((Keyword*)(internRigidSymbolWrtModule("REALISTIC", NULL, 2)));
    SGT_GOAL_CACHES_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", NULL, 1)));
    SGT_GOAL_CACHES_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", NULL, 1)));
    SGT_GOAL_CACHES_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
    SYM_GOAL_CACHES_LOGIC_GOAL_CACHE_LIST = ((Symbol*)(internRigidSymbolWrtModule("GOAL-CACHE-LIST", NULL, 0)));
    KWD_GOAL_CACHES_GOAL_INSTANTIATES_CACHE = ((Keyword*)(internRigidSymbolWrtModule("GOAL-INSTANTIATES-CACHE", NULL, 2)));
    KWD_GOAL_CACHES_CACHE_INSTANTIATES_GOAL = ((Keyword*)(internRigidSymbolWrtModule("CACHE-INSTANTIATES-GOAL", NULL, 2)));
    KWD_GOAL_CACHES_ATOMIC_GOAL = ((Keyword*)(internRigidSymbolWrtModule("ATOMIC-GOAL", NULL, 2)));
    SGT_GOAL_CACHES_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
    SYM_GOAL_CACHES_LOGIC_EXTERNAL_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("EXTERNAL-VARIABLES", NULL, 0)));
    SGT_GOAL_CACHES_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    SGT_GOAL_CACHES_PL_KERNEL_KB_FRAME_PREDICATE = ((Surrogate*)(internRigidSymbolWrtModule("FRAME-PREDICATE", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_GOAL_CACHES_EXECUTE_QUERY = ((Keyword*)(internRigidSymbolWrtModule("EXECUTE-QUERY", NULL, 2)));
    SYM_GOAL_CACHES_LOGIC_CHECK_FOR_CACHED_GOALSp = ((Symbol*)(internRigidSymbolWrtModule("CHECK-FOR-CACHED-GOALS?", NULL, 0)));
    KWD_GOAL_CACHES_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("SUCCESS", NULL, 2)));
    SGT_GOAL_CACHES_LOGIC_ATOMIC_GOAL_CACHE_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("ATOMIC-GOAL-CACHE-ITERATOR", NULL, 1)));
    SYM_GOAL_CACHES_LOGIC_GOAL = ((Symbol*)(internRigidSymbolWrtModule("GOAL", NULL, 0)));
    SYM_GOAL_CACHES_LOGIC_CACHE_LIST = ((Symbol*)(internRigidSymbolWrtModule("CACHE-LIST", NULL, 0)));
    SYM_GOAL_CACHES_LOGIC_STARTUP_GOAL_CACHES = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-GOAL-CACHES", NULL, 0)));
    SYM_GOAL_CACHES_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void startupGoalCaches() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupGoalCaches1();
    }
    if (currentStartupTimePhaseP(4)) {
      oSUCCEEDED_GOALS_CACHEo = stella::newVector(1541);
      oFAILED_GOALS_CACHEo = stella::newVector(1541);
      oUNIFICATION_VECTOR_1o = stella::newVector(10);
      oUNIFICATION_VECTOR_2o = stella::newVector(10);
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("GOAL-CACHE", "(DEFCLASS GOAL-CACHE (STANDARD-OBJECT) :DOCUMENTATION \"Cache of output bindings derived for a particular goal\nand set of input bindings.\" :SLOTS ((CACHED-BINDINGS :TYPE (LIST OF GOAL-BINDINGS) :ALLOCATION :EMBEDDED) (TIMESTAMP :TYPE TIMESTAMP) (PROPOSITION :TYPE PROPOSITION) (REVERSE-POLARITY? :TYPE BOOLEAN) (CACHE-CONTEXT :TYPE CONTEXT)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newGoalCache));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessGoalCacheSlotValue));
      }
      defineStellaTypeFromStringifiedSource("(DEFTYPE GOAL-CACHE-TABLE (KEY-VALUE-LIST OF CONTEXT GOAL-CACHE))");
      { Class* clasS = defineClassFromStringifiedSource("ATOMIC-GOAL-CACHE", "(DEFCLASS ATOMIC-GOAL-CACHE (STANDARD-OBJECT) :DOCUMENTATION \"Cache data structure to store the result of proving an atomic\nand possibly open `proposition' relative to a set of variable `bindings'.\" :SLOTS ((GOAL-CONTEXT :TYPE CONTEXT) (TIMESTAMP :TYPE TIMESTAMP) (TRUTH-VALUE :TYPE TRUTH-VALUE) (REVERSE-POLARITY? :TYPE BOOLEAN) (PROPOSITION :TYPE PROPOSITION) (BINDINGS :TYPE GOAL-BINDINGS) (JUSTIFICATION :TYPE JUSTIFICATION) (MATCH-SCORE :TYPE PARTIAL-MATCH-SCORE) (PREVIOUS :TYPE ATOMIC-GOAL-CACHE) (NEXT :TYPE ATOMIC-GOAL-CACHE)) :PRINT-FORM (PRINT-ATOMIC-GOAL-CACHE SELF STREAM))");

        clasS->classConstructorCode = ((cpp_function_code)(&newAtomicGoalCache));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessAtomicGoalCacheSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("ATOMIC-GOAL-CACHE-ITERATOR", "(DEFCLASS ATOMIC-GOAL-CACHE-ITERATOR (ITERATOR) :PARAMETERS ((ANY-VALUE :TYPE ATOMIC-GOAL-CACHE)) :SLOTS ((GOAL :TYPE CONTROL-FRAME) (CACHE-LIST :TYPE ATOMIC-GOAL-CACHE)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newAtomicGoalCacheIterator));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessAtomicGoalCacheIteratorSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("TRACE-GOAL-CACHE", "(DEFUN TRACE-GOAL-CACHE ((STRING STRING) (FRAME CONTROL-FRAME)))", ((cpp_function_code)(&traceGoalCache)), NULL);
      defineFunctionObject("REMOVE-OBSOLETE-GOAL-CACHES", "(DEFUN REMOVE-OBSOLETE-GOAL-CACHES ((TABLE (KEY-VALUE-LIST OF CONTEXT GOAL-CACHE))))", ((cpp_function_code)(&removeObsoleteGoalCaches)), NULL);
      defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION GOAL-CACHE-TABLE :TYPE GOAL-CACHE-TABLE :DOCUMENTATION \"Allows attachment of goal caches to classes or slots.\" :ALLOCATION :DYNAMIC)");
      defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION NEGATED-GOAL-CACHE-TABLE :TYPE GOAL-CACHE-TABLE :DOCUMENTATION \"Allows attachment of goal caches to classes or slots.\" :ALLOCATION :DYNAMIC)");
      defineFunctionObject("YIELD-GOAL-BINDINGS", "(DEFUN (YIELD-GOAL-BINDINGS GOAL-BINDINGS) ((GOAL PROPOSITION)))", ((cpp_function_code)(&yieldGoalBindings)), NULL);
      defineFunctionObject("FIND-GOAL-CACHE-TABLE", "(DEFUN (FIND-GOAL-CACHE-TABLE GOAL-CACHE-TABLE) ((GOAL PROPOSITION)))", ((cpp_function_code)(&findGoalCacheTable)), NULL);
      defineFunctionObject("CREATE-GOAL-CACHE?", "(DEFUN (CREATE-GOAL-CACHE? BOOLEAN) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&createGoalCacheP)), NULL);
      defineFunctionObject("LOOKUP-GOAL-CACHE", "(DEFUN (LOOKUP-GOAL-CACHE GOAL-CACHE) ((TABLE GOAL-CACHE-TABLE)))", ((cpp_function_code)(&lookupGoalCache)), NULL);
      defineFunctionObject("FIND-GOAL-CACHE", "(DEFUN (FIND-GOAL-CACHE GOAL-CACHE) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&findGoalCache)), NULL);
      defineFunctionObject("UPDATE-GOAL-CACHE", "(DEFUN UPDATE-GOAL-CACHE ((FRAME CONTROL-FRAME) (SUCCESS? BOOLEAN)))", ((cpp_function_code)(&updateGoalCache)), NULL);
      defineFunctionObject("YIELD-RELATIVE-GOAL-BINDINGS", "(DEFUN (YIELD-RELATIVE-GOAL-BINDINGS GOAL-BINDINGS) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&yieldRelativeGoalBindings)), NULL);
      defineFunctionObject("CONTINUE-CACHED-BINDINGS-PROOF", "(DEFUN (CONTINUE-CACHED-BINDINGS-PROOF KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&continueCachedBindingsProof)), NULL);
      defineFunctionObject("TOP-LEVEL-QUERY-CONTEXT?", "(DEFUN (TOP-LEVEL-QUERY-CONTEXT? BOOLEAN) ((SELF CONTEXT)))", ((cpp_function_code)(&topLevelQueryContextP)), NULL);
      defineFunctionObject("CACHE-QUERY-RESULTS?", "(DEFUN (CACHE-QUERY-RESULTS? BOOLEAN) () :GLOBALLY-INLINE? TRUE (RETURN (AND (OR *CACHE-SUCCEEDED-GOALS?* *CACHE-FAILED-GOALS?*) (EQL? *DUPLICATE-SUBGOAL-STRATEGY* :DUPLICATE-GOALS) (NOT (PARTIAL-MATCH-MODE?)))))", ((cpp_function_code)(&cacheQueryResultsP)), NULL);
      defineFunctionObject("TOGGLE-GOAL-CACHING", "(DEFUN (TOGGLE-GOAL-CACHING STRING) () :COMMAND? TRUE)", ((cpp_function_code)(&toggleGoalCaching)), ((cpp_function_code)(&toggleGoalCachingEvaluatorWrapper)));
      defineFunctionObject("PRINT-ATOMIC-GOAL-CACHE", "(DEFUN PRINT-ATOMIC-GOAL-CACHE ((SELF ATOMIC-GOAL-CACHE) (STREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&printAtomicGoalCache)), NULL);
      defineFunctionObject("CLEAR-QUERY-RESULTS-CACHE", "(DEFUN CLEAR-QUERY-RESULTS-CACHE ())", ((cpp_function_code)(&clearQueryResultsCache)), NULL);
      defineFunctionObject("PRINT-QUERY-RESULTS-CACHE", "(DEFUN PRINT-QUERY-RESULTS-CACHE ((LIMIT INTEGER)))", ((cpp_function_code)(&printQueryResultsCache)), NULL);
      defineFunctionObject("SUCCEEDED-GOAL-INDEX", "(DEFUN (SUCCEEDED-GOAL-INDEX INTEGER) ((FRAME CONTROL-FRAME)) :GLOBALLY-INLINE? TRUE (RETURN (HASHMOD (GOAL-HASH-CODE FRAME) 1541)))", ((cpp_function_code)(&succeededGoalIndex)), NULL);
      defineFunctionObject("FAILED-GOAL-INDEX", "(DEFUN (FAILED-GOAL-INDEX INTEGER) ((FRAME CONTROL-FRAME)) :GLOBALLY-INLINE? TRUE (RETURN (HASHMOD (GOAL-HASH-CODE FRAME) 1541)))", ((cpp_function_code)(&failedGoalIndex)), NULL);
      defineFunctionObject("GOAL-HASH-CODE", "(DEFUN (GOAL-HASH-CODE INTEGER) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&goalHashCode)), NULL);
      defineFunctionObject("HASH-UNBOUND-GOAL-VARIABLE", "(DEFUN (HASH-UNBOUND-GOAL-VARIABLE INTEGER) ((VAR PATTERN-VARIABLE) (ARGUMENTS VECTOR) (CODE INTEGER)))", ((cpp_function_code)(&hashUnboundGoalVariable)), NULL);
      defineFunctionObject("HASH-GOAL-ARGUMENT", "(DEFUN (HASH-GOAL-ARGUMENT INTEGER) ((ARG OBJECT) (CODE INTEGER)))", ((cpp_function_code)(&hashGoalArgument)), NULL);
      defineExternalSlotFromStringifiedSource("(DEFSLOT NAMED-DESCRIPTION GOAL-CACHE-LIST :TYPE ATOMIC-GOAL-CACHE :DOCUMENTATION \"Points at the beginning of a chain of cached values\nfor some named description\" :ALLOCATION :DYNAMIC)");
      defineFunctionObject("CACHED-GOAL-OPERATOR", "(DEFUN (CACHED-GOAL-OPERATOR SURROGATE) ((GOAL PROPOSITION)))", ((cpp_function_code)(&cachedGoalOperator)), NULL);
      defineFunctionObject("GET-GOAL-CACHE-LIST", "(DEFUN (GET-GOAL-CACHE-LIST ATOMIC-GOAL-CACHE) ((GOAL PROPOSITION)))", ((cpp_function_code)(&getGoalCacheList)), NULL);
      defineFunctionObject("SET-GOAL-CACHE-LIST", "(DEFUN (SET-GOAL-CACHE-LIST ATOMIC-GOAL-CACHE) ((GOAL PROPOSITION) (FIRSTCACHE ATOMIC-GOAL-CACHE)))", ((cpp_function_code)(&setGoalCacheList)), NULL);
      defineFunctionObject("CREATE-ATOMIC-GOAL-CACHE", "(DEFUN (CREATE-ATOMIC-GOAL-CACHE ATOMIC-GOAL-CACHE) ((FRAME CONTROL-FRAME) (CACHE ATOMIC-GOAL-CACHE) (SUCCESS? BOOLEAN)))", ((cpp_function_code)(&createAtomicGoalCache)), NULL);
      defineFunctionObject("CACHE-MATCHES-GOAL?", "(DEFUN (CACHE-MATCHES-GOAL? BOOLEAN) ((CACHE ATOMIC-GOAL-CACHE) (GOAL CONTROL-FRAME) (SUCCESS? BOOLEAN) (MODE KEYWORD)))", ((cpp_function_code)(&cacheMatchesGoalP)), NULL);
      defineFunctionObject("GOAL-INSTANTIATES-CACHE?", "(DEFUN (GOAL-INSTANTIATES-CACHE? BOOLEAN) ((GOAL CONTROL-FRAME) (CACHE ATOMIC-GOAL-CACHE) (SUCCESS? BOOLEAN)) :GLOBALLY-INLINE? TRUE (RETURN (CACHE-MATCHES-GOAL? CACHE GOAL SUCCESS? :GOAL-INSTANTIATES-CACHE)))", ((cpp_function_code)(&goalInstantiatesCacheP)), NULL);
      defineFunctionObject("CACHE-INSTANTIATES-GOAL?", "(DEFUN (CACHE-INSTANTIATES-GOAL? BOOLEAN) ((CACHE ATOMIC-GOAL-CACHE) (GOAL CONTROL-FRAME) (SUCCESS? BOOLEAN)) :GLOBALLY-INLINE? TRUE (RETURN (CACHE-MATCHES-GOAL? CACHE GOAL SUCCESS? :CACHE-INSTANTIATES-GOAL)))", ((cpp_function_code)(&cacheInstantiatesGoalP)), NULL);
      defineFunctionObject("DONT-CACHE-GOAL-FAILURE-BETWEEN-FRAMES", "(DEFUN DONT-CACHE-GOAL-FAILURE-BETWEEN-FRAMES ((TOPFRAME CONTROL-FRAME) (BOTTOMFRAME CONTROL-FRAME)))", ((cpp_function_code)(&dontCacheGoalFailureBetweenFrames)), NULL);
      defineFunctionObject("CACHE-GOAL", "(DEFUN CACHE-GOAL ((FRAME CONTROL-FRAME) (SUCCESS? BOOLEAN) (KEEPFRAME? BOOLEAN) (CLOCKTICKS INTEGER)))", ((cpp_function_code)(&cacheGoal)), NULL);
      defineFunctionObject("FIND-CACHED-GOAL", "(DEFUN (FIND-CACHED-GOAL ATOMIC-GOAL-CACHE) ((FRAME CONTROL-FRAME) (SUCCESSORFAILURE KEYWORD)))", ((cpp_function_code)(&findCachedGoal)), NULL);
      defineFunctionObject("ALL-CACHED-PROPOSITIONS", "(DEFUN (ALL-CACHED-PROPOSITIONS ATOMIC-GOAL-CACHE-ITERATOR) ((GOAL CONTROL-FRAME)))", ((cpp_function_code)(&allCachedPropositions)), NULL);
      defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF ATOMIC-GOAL-CACHE-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&AtomicGoalCacheIterator::nextP))), NULL);
      defineFunctionObject("STARTUP-GOAL-CACHES", "(DEFUN STARTUP-GOAL-CACHES () :PUBLIC? TRUE)", ((cpp_function_code)(&startupGoalCaches)), NULL);
      { MethodSlot* function = lookupFunction(SYM_GOAL_CACHES_LOGIC_STARTUP_GOAL_CACHES);

        setDynamicSlotValue(function->dynamicSlots, SYM_GOAL_CACHES_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupGoalCaches"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFGLOBAL *CACHE-SUCCEEDED-GOALS?* BOOLEAN TRUE)", &oCACHE_SUCCEEDED_GOALSpo);
      defineGlobalVariableObject("(DEFGLOBAL *CACHE-FAILED-GOALS?* BOOLEAN TRUE)", &oCACHE_FAILED_GOALSpo);
      defineGlobalVariableObject("(DEFGLOBAL *CACHE-GOAL-QUANTUM* INTEGER 5 :DOCUMENTATION \"Only goals whose success or failure took at least this\nnumber of query clock ticks will be cached.\")", &oCACHE_GOAL_QUANTUMo);
      defineGlobalVariableObject("(DEFGLOBAL *SUCCEEDED-GOALS-CACHE* (VECTOR OF ATOMIC-GOAL-CACHE) (NEW VECTOR :ARRAY-SIZE 1541))", &oSUCCEEDED_GOALS_CACHEo);
      defineGlobalVariableObject("(DEFGLOBAL *FAILED-GOALS-CACHE* (VECTOR OF ATOMIC-GOAL-CACHE) (NEW VECTOR :ARRAY-SIZE 1541))", &oFAILED_GOALS_CACHEo);
      defineGlobalVariableObject("(DEFSPECIAL *UNIFICATION-VECTOR-1* VECTOR (NEW VECTOR :ARRAY-SIZE 10))", &oUNIFICATION_VECTOR_1o);
      defineGlobalVariableObject("(DEFSPECIAL *UNIFICATION-VECTOR-2* VECTOR (NEW VECTOR :ARRAY-SIZE 10))", &oUNIFICATION_VECTOR_2o);
    }
  }
}

Surrogate* SGT_GOAL_CACHES_LOGIC_GOAL_CACHE = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_CACHED_BINDINGS = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_TIMESTAMP = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_PROPOSITION = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_REVERSE_POLARITYp = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_CACHE_CONTEXT = NULL;

Keyword* KWD_GOAL_CACHES_GOAL_CACHES = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_GOAL_CACHE_TABLE = NULL;

Keyword* KWD_GOAL_CACHES_ISA = NULL;

Keyword* KWD_GOAL_CACHES_PREDICATE = NULL;

Keyword* KWD_GOAL_CACHES_FUNCTION = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_NEGATED_GOAL_CACHE_TABLE = NULL;

Surrogate* SGT_GOAL_CACHES_STELLA_SURROGATE = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_GOAL_CACHE = NULL;

Keyword* KWD_GOAL_CACHES_DUPLICATE_GOALS_WITH_CACHING = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_CACHED_BINDINGS_ITERATOR = NULL;

Keyword* KWD_GOAL_CACHES_FAILURE = NULL;

Keyword* KWD_GOAL_CACHES_FINAL_SUCCESS = NULL;

Keyword* KWD_GOAL_CACHES_CONTINUING_SUCCESS = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_INFERENCE_CACHE_OF = NULL;

Keyword* KWD_GOAL_CACHES_DUPLICATE_GOALS = NULL;

Surrogate* SGT_GOAL_CACHES_LOGIC_ATOMIC_GOAL_CACHE = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_GOAL_CONTEXT = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_TRUTH_VALUE = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_BINDINGS = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_JUSTIFICATION = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_MATCH_SCORE = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_PREVIOUS = NULL;

Symbol* SYM_GOAL_CACHES_STELLA_NEXT = NULL;

Keyword* KWD_GOAL_CACHES_REALISTIC = NULL;

Surrogate* SGT_GOAL_CACHES_LOGIC_PATTERN_VARIABLE = NULL;

Surrogate* SGT_GOAL_CACHES_LOGIC_SKOLEM = NULL;

Surrogate* SGT_GOAL_CACHES_LOGIC_LOGIC_OBJECT = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_GOAL_CACHE_LIST = NULL;

Keyword* KWD_GOAL_CACHES_GOAL_INSTANTIATES_CACHE = NULL;

Keyword* KWD_GOAL_CACHES_CACHE_INSTANTIATES_GOAL = NULL;

Keyword* KWD_GOAL_CACHES_ATOMIC_GOAL = NULL;

Surrogate* SGT_GOAL_CACHES_LOGIC_DESCRIPTION = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_EXTERNAL_VARIABLES = NULL;

Surrogate* SGT_GOAL_CACHES_LOGIC_PROPOSITION = NULL;

Surrogate* SGT_GOAL_CACHES_PL_KERNEL_KB_FRAME_PREDICATE = NULL;

Keyword* KWD_GOAL_CACHES_EXECUTE_QUERY = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_CHECK_FOR_CACHED_GOALSp = NULL;

Keyword* KWD_GOAL_CACHES_SUCCESS = NULL;

Surrogate* SGT_GOAL_CACHES_LOGIC_ATOMIC_GOAL_CACHE_ITERATOR = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_GOAL = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_CACHE_LIST = NULL;

Symbol* SYM_GOAL_CACHES_LOGIC_STARTUP_GOAL_CACHES = NULL;

Symbol* SYM_GOAL_CACHES_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
