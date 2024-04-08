//  -*- Mode: C++ -*-

// classify.cc

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

void bumpInferableTimestamp() {
  bumpMemoizationTimestamp(KWD_CLASSIFY_IMPLIES_PROPOSITION_UPDATE);
}

void helpCollectIntensionalParents(Description* description, Proposition* proposition, List* collection) {
  { Keyword* testValue000 = proposition->kind;

    if ((testValue000 == KWD_CLASSIFY_PREDICATE) ||
        ((testValue000 == KWD_CLASSIFY_FUNCTION) ||
         (testValue000 == KWD_CLASSIFY_ISA))) {
      { boolean testValue001 = false;

        { boolean alwaysP000 = true;

          { Object* arg1 = NULL;
            Vector* vector000 = proposition->arguments;
            int index000 = 0;
            int length000 = vector000->length();
            PatternVariable* arg2 = NULL;
            Vector* vector001 = description->ioVariables;
            int index001 = 0;
            int length001 = vector001->length();

            for  (; (index000 < length000) &&
                      (index001 < length001); 
                  index000 = index000 + 1,
                  index001 = index001 + 1) {
              arg1 = (vector000->theArray)[index000];
              arg2 = ((PatternVariable*)((vector001->theArray)[index001]));
              if (!(arg1 == arg2)) {
                alwaysP000 = false;
                break;
              }
            }
          }
          testValue001 = alwaysP000;
        }
        if (testValue001) {
          testValue001 = proposition->arguments->length() == description->ioVariables->length();
        }
        if (testValue001) {
          collection->push(getDescription(((Surrogate*)(proposition->operatoR))));
        }
      }
    }
    else if (testValue000 == KWD_CLASSIFY_AND) {
      { Object* arg = NULL;
        Vector* vector002 = proposition->arguments;
        int index002 = 0;
        int length002 = vector002->length();

        for  (; index002 < length002; 
              index002 = index002 + 1) {
          arg = (vector002->theArray)[index002];
          helpCollectIntensionalParents(description, ((Proposition*)(arg)), collection);
        }
      }
    }
    else if (testValue000 == KWD_CLASSIFY_EXISTS) {
      helpCollectIntensionalParents(description, ((Proposition*)((proposition->arguments->theArray)[0])), collection);
    }
    else {
    }
  }
}

List* allIntensionalParents(Description* self) {
  { List* collection = newList();

    helpCollectIntensionalParents(self, self->proposition, collection);
    return (collection);
  }
}

boolean inferableThroughBySomeDescendantP(NamedDescription* self, LogicObject* throughchild, Cons* alreadyvisitedlist) {
  { Surrogate* testValue000 = safePrimaryType(throughchild);

    if (subtypeOfP(testValue000, SGT_CLASSIFY_LOGIC_NAMED_DESCRIPTION)) {
      { LogicObject* throughchild000 = throughchild;
        NamedDescription* throughchild = ((NamedDescription*)(throughchild000));

        if ((lookupSpecialist(throughchild) != NULL) ||
            (lookupComputation(throughchild) != NULL)) {
          return (true);
        }
        else if (!(self->proposition->kind == throughchild->proposition->kind)) {
          return (true);
        }
        else if (!inferableWithCycleCheckP(throughchild, alreadyvisitedlist)) {
          return (false);
        }
        alreadyvisitedlist = cons(throughchild, alreadyvisitedlist);
        { Proposition* p = NULL;
          Cons* iter000 = applicableRulesOfDescription(throughchild, KWD_CLASSIFY_BACKWARD, false);

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            p = ((Proposition*)(iter000->value));
            if ((!((BooleanWrapper*)(dynamicSlotValue(p->dynamicSlots, SYM_CLASSIFY_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue) &&
                trueP(p)) {
              if (inferableThroughBySomeDescendantP(self, ((LogicObject*)((p->arguments->theArray)[0])), alreadyvisitedlist)) {
                return (true);
              }
            }
          }
        }
        return (false);
      }
    }
    else if (subtypeOfP(testValue000, SGT_CLASSIFY_LOGIC_DESCRIPTION)) {
      { LogicObject* throughchild001 = throughchild;
        Description* throughchild = ((Description*)(throughchild001));

        { boolean testValue001 = false;

          { boolean foundP000 = false;

            { Description* parent = NULL;
              Cons* iter001 = allIntensionalParents(throughchild)->theConsList;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                parent = ((Description*)(iter001->value));
                if (collectionImpliesCollectionP(parent, self)) {
                  foundP000 = true;
                  break;
                }
              }
            }
            testValue001 = foundP000;
          }
          testValue001 = !testValue001;
          { boolean value000 = testValue001;

            return (value000);
          }
        }
      }
    }
    else {
      return (false);
    }
  }
}

boolean inferableWithCycleCheckP(Description* self, Cons* alreadyvisitedlist) {
  if (alreadyvisitedlist->membP(self)) {
    return (false);
  }
  { boolean inferableP = false;

    if (subtypeOfP(safePrimaryType(self), SGT_CLASSIFY_LOGIC_NAMED_DESCRIPTION)) {
      { Description* self000 = self;
        NamedDescription* self = ((NamedDescription*)(self000));

        { MemoizationTable* memoTable000 = NULL;
          Cons* memoizedEntry000 = NULL;
          Object* memoizedValue000 = NULL;

          if (oMEMOIZATION_ENABLEDpo) {
            memoTable000 = ((MemoizationTable*)(SGT_CLASSIFY_LOGIC_F_INFERABLE_WITH_CYCLE_CHECKp_MEMO_TABLE_000->surrogateValue));
            if (!((boolean)(memoTable000))) {
              initializeMemoizationTable(SGT_CLASSIFY_LOGIC_F_INFERABLE_WITH_CYCLE_CHECKp_MEMO_TABLE_000, "(:MAX-VALUES 500 :TIMESTAMPS (:IMPLIES-PROPOSITION-UPDATE))");
              memoTable000 = ((MemoizationTable*)(SGT_CLASSIFY_LOGIC_F_INFERABLE_WITH_CYCLE_CHECKp_MEMO_TABLE_000->surrogateValue));
            }
            memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), self, oCONTEXTo, MEMOIZED_NULL_VALUE, NULL, -1);
            memoizedValue000 = memoizedEntry000->value;
          }
          if (((boolean)(memoizedValue000))) {
            if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
              memoizedValue000 = NULL;
            }
          }
          else {
            { boolean testValue001 = false;

              testValue001 = !(self->surrogateValueInverse == SGT_CLASSIFY_STELLA_THING);
              if (testValue001) {
                testValue001 = ((boolean)(alreadyvisitedlist = cons(self, alreadyvisitedlist)));
                if (testValue001) {
                  { boolean foundP001 = false;

                    { Proposition* p = NULL;
                      Cons* iter001 = applicableRulesOfDescription(self, KWD_CLASSIFY_BACKWARD, false);

                      for (; !(iter001 == NIL); iter001 = iter001->rest) {
                        p = ((Proposition*)(iter001->value));
                        if ((!((BooleanWrapper*)(dynamicSlotValue(p->dynamicSlots, SYM_CLASSIFY_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue) &&
                            (trueP(p) &&
                             inferableThroughBySomeDescendantP(self, ((LogicObject*)((p->arguments->theArray)[0])), alreadyvisitedlist))) {
                          foundP001 = true;
                          break;
                        }
                      }
                    }
                    testValue001 = foundP001;
                  }
                }
              }
              memoizedValue000 = (testValue001 ? TRUE_WRAPPER : FALSE_WRAPPER);
            }
            if (oMEMOIZATION_ENABLEDpo) {
              memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
            }
          }
          inferableP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(memoizedValue000)));
        }
      }
    }
    else {
      inferableP = true;
    }
    return (inferableP);
  }
}

boolean inferableP(Description* self) {
  { 
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getInferableTestContext());
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
    return (inferableWithCycleCheckP(self, NIL));
  }
}

boolean nonInferableP(Description* self) {
  return (!inferableP(self));
}

MarkerTable* newMarkerTable() {
  { MarkerTable* self = NULL;

    self = new MarkerTable();
    self->supportsRecallP = false;
    self->recallTable = NULL;
    self->testTable = NULL;
    return (self);
  }
}

Surrogate* MarkerTable::primaryType() {
  { MarkerTable* self = this;

    return (SGT_CLASSIFY_LOGIC_MARKER_TABLE);
  }
}

Object* accessMarkerTableSlotValue(MarkerTable* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_CLASSIFY_LOGIC_TEST_TABLE) {
    if (setvalueP) {
      self->testTable = ((HashTable*)(value));
    }
    else {
      value = self->testTable;
    }
  }
  else if (slotname == SYM_CLASSIFY_LOGIC_RECALL_TABLE) {
    if (setvalueP) {
      self->recallTable = ((List*)(value));
    }
    else {
      value = self->recallTable;
    }
  }
  else if (slotname == SYM_CLASSIFY_LOGIC_SUPPORTS_RECALLp) {
    if (setvalueP) {
      self->supportsRecallP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->supportsRecallP ? TRUE_WRAPPER : FALSE_WRAPPER);
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

MarkerTable* createMarkerStorage(boolean supportrecallP) {
  // Return a new marker storage object, used to
  // remember with objects have been 'marked'.  If 'supportRecall?'
  // is set, then the iterator 'recall-marked-objects' can be invoked
  // on the new marker storage object.
  { MarkerTable* table = newMarkerTable();

    table->testTable = newHashTable();
    if (supportrecallP) {
      table->supportsRecallP = true;
      table->recallTable = newList();
    }
    return (table);
  }
}

void MarkerTable::setMarker(Object* object) {
  // Record membership of 'object' in the marker
  // storage object 'self'.
  { MarkerTable* self = this;

    if (self->supportsRecallP) {
      if (!((boolean)(self->testTable->lookup(object)))) {
        self->testTable->insertAt(object, TRUE_WRAPPER);
        self->recallTable->push(object);
      }
    }
    else {
      self->testTable->insertAt(object, TRUE_WRAPPER);
    }
  }
}

boolean MarkerTable::testMarkerP(Object* object) {
  // Return TRUE if 'object' is stored (marked) in 'self'.
  { MarkerTable* self = this;

    return (((boolean)(self->testTable->lookup(object))));
  }
}

// Special variable that points to the marker table 
// referenced by the function 'test-special-marker-table?'.
DEFINE_STELLA_SPECIAL(oSPECIALMARKERTABLEo, MarkerTable* , NULL);

boolean testSpecialMarkerTableP(Object* self) {
  // Return TRUE if the object 'self' is stored (marked)
  // in the table pointed at by the special variable *specialMarkerTable*.
  // Designed for use by 'remove-if'.
  return (oSPECIALMARKERTABLEo->testMarkerP(self));
}

ListIterator* MarkerTable::recallMarkedObjects() {
  // Return an iterator that generates all marked objects
  // recorded in 'self'.
  { MarkerTable* self = this;

    return (((ListIterator*)(self->recallTable->allocateIterator())));
  }
}

Cons* allNamedDirectSuperdescriptions(Description* self, boolean removeequivalentsP) {
  { Cons* result = NIL;

    { LogicObject* d = NULL;
      Iterator* iter000 = allDirectSupercollections(self, removeequivalentsP);

      for (; iter000->nextP(); ) {
        d = ((LogicObject*)(iter000->value));
        if (isaP(d, SGT_CLASSIFY_LOGIC_NAMED_DESCRIPTION)) {
          result = cons(d, result);
        }
      }
    }
    return (result);
  }
}

Cons* allNamedDirectSubdescriptions(Description* self) {
  { Cons* result = NIL;

    { LogicObject* d = NULL;
      Iterator* iter000 = allDirectSubcollections(self, false);

      for (; iter000->nextP(); ) {
        d = ((LogicObject*)(iter000->value));
        if (isaP(d, SGT_CLASSIFY_LOGIC_NAMED_DESCRIPTION)) {
          result = cons(d, result);
        }
      }
    }
    return (result);
  }
}

void addIsaLink(LogicObject* instance, Description* superdescription) {
  { Proposition* isaprop = assertIsaProposition(instance, superdescription->surrogateValueInverse);

    setDynamicSlotValue(isaprop->dynamicSlots, SYM_CLASSIFY_LOGIC_SUBSUMPTION_LINKp, TRUE_WRAPPER, FALSE_WRAPPER);
    if (traceKeywordP(KWD_CLASSIFY_CLASSIFIER_INFERENCES)) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        if (oEMIT_THINKING_DOTSpo) {
          std::cout << std::endl;
        }
        std::cout << "Recognized type: " << isaprop << std::endl;
      }
    }
  }
}

void addSubsumptionLink(Description* subdescription, Description* superdescription) {
  { Proposition* impliesprop = assertDescriptionImpliesDescription(subdescription, superdescription, false);

    setDynamicSlotValue(impliesprop->dynamicSlots, SYM_CLASSIFY_LOGIC_SUBSUMPTION_LINKp, TRUE_WRAPPER, FALSE_WRAPPER);
    if (traceKeywordP(KWD_CLASSIFY_CLASSIFIER_INFERENCES)) {
      { 
        BIND_STELLA_SPECIAL(oINDENTCOUNTERo, int, 4);
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        if (oEMIT_THINKING_DOTSpo) {
          std::cout << std::endl;
        }
        std::cout << "Recognized subsumption link:" << std::endl << "    " << impliesprop << std::endl;
      }
    }
  }
  allInferableDirectSubcollections(superdescription)->push(subdescription);
  { NamedDescription* p = NULL;
    Cons* iter000 = allNamedDirectSuperdescriptions(superdescription, false);

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      p = ((NamedDescription*)(iter000->value));
      { List* subcollections = allInferableDirectSubcollections(p);

        subcollections->theConsList = ((Cons*)(mostGeneralCollections(subcollections->theConsList)));
      }
    }
  }
}

Cons* mostSpecificCollections(Cons* descriptions) {
  if (!((boolean)(descriptions->rest))) {
    return (descriptions);
  }
  { Cons* cursor1 = descriptions;
    Cons* cursor2 = NULL;
    Object* value1 = NULL;
    Object* value2 = NULL;

    while (!(cursor1 == NIL)) {
      value1 = ((LogicObject*)(cursor1->value));
      if (((boolean)(value1))) {
        cursor2 = cursor1->rest;
        while (!(cursor2 == NIL)) {
          value2 = cursor2->value;
          if (((boolean)(value2))) {
            if (collectionImpliesCollectionP(((LogicObject*)(value1)), ((LogicObject*)(value2)))) {
              cursor2->value = NULL;
            }
            else {
              if (collectionImpliesCollectionP(((LogicObject*)(value2)), ((LogicObject*)(value1)))) {
                cursor1->value = NULL;
                break;
              }
            }
          }
          cursor2 = cursor2->rest;
        }
      }
      cursor1 = cursor1->rest;
    }
  }
  descriptions = descriptions->remove(NULL);
  return (descriptions);
}

Cons* mostGeneralCollections(Cons* descriptions) {
  if (!((boolean)(descriptions->rest))) {
    return (descriptions);
  }
  { Cons* cursor1 = descriptions;
    Cons* cursor2 = NULL;
    Object* value1 = NULL;
    Object* value2 = NULL;

    while (!(cursor1 == NIL)) {
      value1 = ((LogicObject*)(cursor1->value));
      if (((boolean)(value1))) {
        cursor2 = cursor1->rest;
        while (!(cursor2 == NIL)) {
          value2 = cursor2->value;
          if (((boolean)(value2))) {
            if (collectionImpliesCollectionP(((LogicObject*)(value2)), ((LogicObject*)(value1)))) {
              cursor2->value = NULL;
            }
            else {
              if (collectionImpliesCollectionP(((LogicObject*)(value1)), ((LogicObject*)(value2)))) {
                cursor1->value = NULL;
                break;
              }
            }
          }
          cursor2 = cursor2->rest;
        }
      }
      cursor1 = cursor1->rest;
    }
  }
  descriptions = descriptions->remove(NULL);
  return (descriptions);
}

// Points to a possibly unnamed description being
// temporarily classified.
DEFINE_STELLA_SPECIAL(oFINDSUPERSANDSUBSDESCRIPTIONo, Description* , NULL);

boolean namedCollectionP(LogicObject* self) {
  return (((boolean)(self->surrogateValueInverse)) ||
      (self == oFINDSUPERSANDSUBSDESCRIPTIONo));
}

Cons* mostSpecificNamedCollections(Cons* descriptions) {
  descriptions = mostSpecificCollections(descriptions);
  { boolean recomputeP = false;

    { LogicObject* d = NULL;
      Cons* iter000 = copyConsList(descriptions);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        d = ((LogicObject*)(iter000->value));
        if (!namedCollectionP(d)) {
          descriptions = descriptions->remove(d);
          { LogicObject* super = NULL;
            Iterator* iter001 = allDirectSupercollections(d, false);

            for (; iter001->nextP(); ) {
              super = ((LogicObject*)(iter001->value));
              descriptions = cons(super, descriptions);
            }
          }
          recomputeP = true;
        }
      }
    }
    if (recomputeP) {
      mostSpecificNamedCollections(descriptions);
    }
    return (descriptions);
  }
}

Cons* mostSpecificNamedDescriptions(Cons* descriptions) {
  descriptions = mostSpecificCollections(descriptions);
  { boolean recomputeP = false;

    { LogicObject* d = NULL;
      Cons* iter000 = copyConsList(descriptions);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        d = ((LogicObject*)(iter000->value));
        if (!namedDescriptionP(((Description*)(d)))) {
          descriptions = descriptions->remove(d);
          { LogicObject* super = NULL;
            Iterator* iter001 = allDirectSupercollections(d, false);

            for (; iter001->nextP(); ) {
              super = ((LogicObject*)(iter001->value));
              descriptions = cons(super, descriptions);
            }
          }
          recomputeP = true;
        }
      }
    }
    if (recomputeP) {
      mostSpecificNamedCollections(descriptions);
    }
    return (((Cons*)(descriptions)));
  }
}

ClassificationCache* newClassificationCache() {
  { ClassificationCache* self = NULL;

    self = new ClassificationCache();
    self->introductionTimestamp = 0;
    self->cacheDownclassificationTimestamp = -1;
    self->cacheUpclassificationTimestamp = -1;
    self->inferableDirectSubdescriptions = NULL;
    return (self);
  }
}

Surrogate* ClassificationCache::primaryType() {
  { ClassificationCache* self = this;

    return (SGT_CLASSIFY_LOGIC_CLASSIFICATION_CACHE);
  }
}

Object* accessClassificationCacheSlotValue(ClassificationCache* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_CLASSIFY_LOGIC_INFERABLE_DIRECT_SUBDESCRIPTIONS) {
    if (setvalueP) {
      self->inferableDirectSubdescriptions = ((List*)(value));
    }
    else {
      value = self->inferableDirectSubdescriptions;
    }
  }
  else if (slotname == SYM_CLASSIFY_LOGIC_CACHE_UPCLASSIFICATION_TIMESTAMP) {
    if (setvalueP) {
      self->cacheUpclassificationTimestamp = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->cacheUpclassificationTimestamp);
    }
  }
  else if (slotname == SYM_CLASSIFY_LOGIC_CACHE_DOWNCLASSIFICATION_TIMESTAMP) {
    if (setvalueP) {
      self->cacheDownclassificationTimestamp = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->cacheDownclassificationTimestamp);
    }
  }
  else if (slotname == SYM_CLASSIFY_LOGIC_INTRODUCTION_TIMESTAMP) {
    if (setvalueP) {
      self->introductionTimestamp = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->introductionTimestamp);
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

ClassificationSession* newClassificationSession() {
  { ClassificationSession* self = NULL;

    self = new ClassificationSession();
    self->lastCacheTableValue = NULL;
    self->lastCacheTableKey = NULL;
    self->everythingClassifiedP = false;
    self->introductionTimestampStack = list(1, wrapInteger(0));
    self->classificationTimeclock = 0;
    self->classificationCacheTable = newHashTable();
    self->classificationWorld = NULL;
    return (self);
  }
}

Surrogate* ClassificationSession::primaryType() {
  { ClassificationSession* self = this;

    return (SGT_CLASSIFY_LOGIC_CLASSIFICATION_SESSION);
  }
}

Object* accessClassificationSessionSlotValue(ClassificationSession* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_CLASSIFY_LOGIC_CLASSIFICATION_WORLD) {
    if (setvalueP) {
      self->classificationWorld = ((World*)(value));
    }
    else {
      value = self->classificationWorld;
    }
  }
  else if (slotname == SYM_CLASSIFY_LOGIC_CLASSIFICATION_CACHE_TABLE) {
    if (setvalueP) {
      self->classificationCacheTable = ((HashTable*)(value));
    }
    else {
      value = self->classificationCacheTable;
    }
  }
  else if (slotname == SYM_CLASSIFY_LOGIC_CLASSIFICATION_TIMECLOCK) {
    if (setvalueP) {
      self->classificationTimeclock = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->classificationTimeclock);
    }
  }
  else if (slotname == SYM_CLASSIFY_LOGIC_INTRODUCTION_TIMESTAMP_STACK) {
    if (setvalueP) {
      self->introductionTimestampStack = ((List*)(value));
    }
    else {
      value = self->introductionTimestampStack;
    }
  }
  else if (slotname == SYM_CLASSIFY_LOGIC_EVERYTHING_CLASSIFIEDp) {
    if (setvalueP) {
      self->everythingClassifiedP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->everythingClassifiedP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_CLASSIFY_LOGIC_LAST_CACHE_TABLE_KEY) {
    if (setvalueP) {
      self->lastCacheTableKey = ((LogicObject*)(value));
    }
    else {
      value = self->lastCacheTableKey;
    }
  }
  else if (slotname == SYM_CLASSIFY_LOGIC_LAST_CACHE_TABLE_VALUE) {
    if (setvalueP) {
      self->lastCacheTableValue = ((ClassificationCache*)(value));
    }
    else {
      value = self->lastCacheTableValue;
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

// Points to state of on-going classification session.
DEFINE_STELLA_SPECIAL(oCLASSIFICATIONSESSIONo, ClassificationSession* , NULL);

World* getClassificationWorld() {
  return (oCLASSIFICATIONSESSIONo->classificationWorld);
}

ClassificationSession* getClassificationSession(Keyword* instanceordescription) {
  if (((boolean)(oCLASSIFICATIONSESSIONo))) {
    return (oCLASSIFICATIONSESSIONo);
  }
  { World* world = NULL;
    ClassificationSession* session = NULL;

    if (instanceordescription == KWD_CLASSIFY_DESCRIPTION) {
      world = getInferenceCache(oMODULEo, KWD_CLASSIFY_META);
    }
    else if (instanceordescription == KWD_CLASSIFY_INSTANCE) {
      world = getInferenceCache(oMODULEo, KWD_CLASSIFY_TMS);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << instanceordescription << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    session = ((ClassificationSession*)(dynamicSlotValue(world->dynamicSlots, SYM_CLASSIFY_LOGIC_CLASSIFICATION_SESSION, NULL)));
    if (!((boolean)(session))) {
      session = newClassificationSession();
      setDynamicSlotValue(world->dynamicSlots, SYM_CLASSIFY_LOGIC_CLASSIFICATION_SESSION, session, NULL);
      session->classificationWorld = world;
    }
    return (session);
  }
}

ClassificationCache* getClassificationCache(Object* self) {
  { ClassificationSession* session = oCLASSIFICATIONSESSIONo;
    ClassificationCache* cache = NULL;

    if (session->lastCacheTableKey == self) {
      return (session->lastCacheTableValue);
    }
    cache = ((ClassificationCache*)(session->classificationCacheTable->lookup(self)));
    if (!((boolean)(cache))) {
      cache = newClassificationCache();
      session->classificationCacheTable->insertAt(self, cache);
    }
    session->lastCacheTableKey = ((LogicObject*)(self));
    session->lastCacheTableValue = cache;
    return (cache);
  }
}

// If TRUE, prevents caching of computations of
// all inferable subcollections of a collection.
boolean oCACHE_INFERABLE_SUBCOLLECTIONSpo = true;

const char* toggleInferableDirectSubcollectionsCaching() {
  oCACHE_INFERABLE_SUBCOLLECTIONSpo = !oCACHE_INFERABLE_SUBCOLLECTIONSpo;
  return ((oCACHE_INFERABLE_SUBCOLLECTIONSpo ? "Inferable subcollections caching enabled" : "Inferable subcollections caching disabled"));
}

List* allInferableDirectSubcollections(LogicObject* self) {
  { ClassificationCache* cache = getClassificationCache(self);
    List* list = cache->inferableDirectSubdescriptions;

    if ((!((boolean)(list))) ||
        (!oCACHE_INFERABLE_SUBCOLLECTIONSpo)) {
      list = newList();
      { NamedDescription* sub = NULL;
        Cons* iter000 = allNamedDirectSubdescriptions(((Description*)(self)));

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          sub = ((NamedDescription*)(iter000->value));
          if (inferableP(sub)) {
            list->insert(sub);
          }
        }
      }
      cache->inferableDirectSubdescriptions = list;
    }
    return (list);
  }
}

void flushInferableDirectSubdescriptionsCache(Proposition* impliesproposition) {
  if (!((boolean)(oCLASSIFICATIONSESSIONo))) {
    return;
  }
  { ClassificationCache* cache = getClassificationCache((impliesproposition->arguments->theArray)[1]);

    if (((boolean)(cache))) {
      cache->inferableDirectSubdescriptions = NULL;
    }
  }
}

int currentClassificationTime() {
  return (oCLASSIFICATIONSESSIONo->classificationTimeclock);
}

int bumpClassificationTimeclock() {
  return (oCLASSIFICATIONSESSIONo->classificationTimeclock = oCLASSIFICATIONSESSIONo->classificationTimeclock + 1);
}

int LogicObject::introductionTimestamp() {
  { LogicObject* self = this;

    return (getClassificationCache(self)->introductionTimestamp);
  }
}

void introduceIntoClassificationSession(Description* self) {
  { World* world = ((World*)(dynamicSlotValue(oMODULEo->dynamicSlots, SYM_CLASSIFY_LOGIC_META_INFERENCE_CACHE, NULL)));

    if ((!((boolean)(world))) ||
        (!((boolean)(((ClassificationSession*)(dynamicSlotValue(world->dynamicSlots, SYM_CLASSIFY_LOGIC_CLASSIFICATION_SESSION, NULL))))))) {
      return;
    }
    { int newtimestamp = bumpClassificationTimeclock();

      getClassificationCache(self)->introductionTimestamp = newtimestamp;
      oCLASSIFICATIONSESSIONo->introductionTimestampStack->push(wrapInteger(newtimestamp));
    }
  }
}

int youngestIntroductionTimestamp() {
  return (((IntegerWrapper*)(oCLASSIFICATIONSESSIONo->introductionTimestampStack->first()))->wrapperValue);
}

int upclassificationTimestamp(Object* self) {
  return (getClassificationCache(self)->cacheUpclassificationTimestamp);
}

int downclassificationTimestamp(LogicObject* self) {
  return (getClassificationCache(self)->cacheDownclassificationTimestamp);
}

void refreshUpclassificationTimestamp(Object* self) {
  getClassificationCache(self)->cacheUpclassificationTimestamp = bumpClassificationTimeclock();
}

void refreshDownclassificationTimestamp(LogicObject* self) {
  getClassificationCache(self)->cacheDownclassificationTimestamp = bumpClassificationTimeclock();
}

void flushClassificationSessions() {
  { World* jitworld = lookupInferenceCache(oMODULEo, KWD_CLASSIFY_JUST_IN_TIME);
    World* metaworld = lookupInferenceCache(oMODULEo, KWD_CLASSIFY_META);
    World* tmsworld = lookupInferenceCache(oMODULEo, KWD_CLASSIFY_TMS);

    if (((boolean)(jitworld))) {
      setDynamicSlotValue(jitworld->dynamicSlots, SYM_CLASSIFY_LOGIC_CLASSIFICATION_SESSION, NULL, NULL);
    }
    if (((boolean)(metaworld))) {
      setDynamicSlotValue(metaworld->dynamicSlots, SYM_CLASSIFY_LOGIC_CLASSIFICATION_SESSION, NULL, NULL);
    }
    if (((boolean)(tmsworld))) {
      setDynamicSlotValue(tmsworld->dynamicSlots, SYM_CLASSIFY_LOGIC_CLASSIFICATION_SESSION, NULL, NULL);
    }
  }
}

boolean upclassifiedP(Object* self) {
  return (upclassificationTimestamp(self) > youngestIntroductionTimestamp());
}

boolean upclassifiedLaterThanP(LogicObject* self, LogicObject* other) {
  return (upclassificationTimestamp(self) > other->introductionTimestamp());
}

boolean downclassifiedP(LogicObject* self) {
  return (nonInferableP(((Description*)(self))) ||
      (downclassificationTimestamp(self) > youngestIntroductionTimestamp()));
}

void markUnmarkedSuperrelations(Description* description, MarkerTable* selfisbelowtable) {
  selfisbelowtable->setMarker(description);
  { NamedDescription* super = NULL;
    Cons* iter000 = allNamedDirectSuperdescriptions(description, true);

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      super = ((NamedDescription*)(iter000->value));
      if (!selfisbelowtable->testMarkerP(description)) {
        markUnmarkedSuperrelations(super, selfisbelowtable);
      }
    }
  }
}

boolean applySubsumptionTestP(cpp_function_code subsumptiontest, LogicObject* self, LogicObject* super) {
  { TruthValue* result = ((TruthValue*  (*) (LogicObject*, LogicObject*))subsumptiontest)(self, super);

    if (((boolean)(oTRACED_KEYWORDSo)) &&
        (oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER) ||
         oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER_PROFILE))) {
      std::cout << "   SPECIALIZES?:  " << result << "  self=" << self << " super=" << super << std::endl;
    }
    return ((result == TRUE_TRUTH_VALUE) ||
        (result == DEFAULT_TRUE_TRUTH_VALUE));
  }
}

boolean helpCollectParentsBelowP(LogicObject* self, Description* super, List* newparentdescriptions, MarkerTable* alreadyvisitedtable, MarkerTable* selfisbelowtable, cpp_function_code subsumptiontest) {
  if (((boolean)(oTRACED_KEYWORDSo)) &&
      oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER)) {
    std::cout << "HELP-COLLECT-PARENTS-BELOW  self= " << self << "    super= " << super << std::endl;
  }
  if (((boolean)(oTRACED_KEYWORDSo)) &&
      oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER)) {
    std::cout << "   TEST-MARKER of 'super': " << selfisbelowtable->testMarkerP(super) << std::endl;
  }
  { boolean foundsubsumingsubP = false;

    alreadyvisitedtable->setMarker(super);
    if (selfisbelowtable->testMarkerP(super)) {
      foundsubsumingsubP = true;
      { Description* sub = NULL;
        Cons* iter000 = allInferableDirectSubcollections(super)->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          sub = ((Description*)(iter000->value));
          if (!alreadyvisitedtable->testMarkerP(sub)) {
            helpCollectParentsBelowP(self, sub, newparentdescriptions, alreadyvisitedtable, selfisbelowtable, subsumptiontest);
          }
        }
      }
    }
    else if ((!upclassifiedLaterThanP(self, super)) &&
        applySubsumptionTestP(subsumptiontest, self, super)) {
      foundsubsumingsubP = true;
      markUnmarkedSuperrelations(super, selfisbelowtable);
      { boolean foundP000 = false;

        { Description* sub = NULL;
          Cons* iter001 = allInferableDirectSubcollections(super)->theConsList;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            sub = ((Description*)(iter001->value));
            if ((!alreadyvisitedtable->testMarkerP(sub)) &&
                helpCollectParentsBelowP(self, sub, newparentdescriptions, alreadyvisitedtable, selfisbelowtable, subsumptiontest)) {
              foundP000 = true;
              break;
            }
          }
        }
        { boolean existsmorespecificsubP = foundP000;

          if (!existsmorespecificsubP) {
            if (((boolean)(oTRACED_KEYWORDSo)) &&
                (oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER) ||
                 oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER_PROFILE))) {
              std::cout << std::endl << "XXXXXXX PUSHING NEW PARENT: " << super << "  of " << self << std::endl << std::endl;
            }
            newparentdescriptions->push(super);
          }
        }
      }
    }
    else {
    }
    return (foundsubsumingsubP);
  }
}

void collectSubsumingParentsBelow(LogicObject* self, Description* super, List* newparentdescriptions, MarkerTable* alreadyvisitedtable, MarkerTable* selfisbelowtable, cpp_function_code subsumptiontest) {
  if (((boolean)(oTRACED_KEYWORDSo)) &&
      oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER)) {
    std::cout << "COLLECT-SUBSUMING  self= " << self << "    super= " << super << std::endl;
  }
  if (((boolean)(oTRACED_KEYWORDSo)) &&
      oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER)) {
    std::cout << "   ALL-INFERABLE-SUBS:  " << consList(1, allInferableDirectSubcollections(super)->listify()) << std::endl;
  }
  { 
    BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
    { Description* sub = NULL;
      Cons* iter000 = allInferableDirectSubcollections(super)->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        sub = ((Description*)(iter000->value));
        if (!alreadyvisitedtable->testMarkerP(sub)) {
          helpCollectParentsBelowP(self, sub, newparentdescriptions, alreadyvisitedtable, selfisbelowtable, subsumptiontest);
        }
      }
    }
  }
}

Iterator* allAncestorsOfParents(Cons* supers) {
  { Cons* collection = copyConsList(supers);

    { LogicObject* s = NULL;
      Cons* iter000 = supers;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        s = ((LogicObject*)(iter000->value));
        { LogicObject* a = NULL;
          Iterator* iter001 = allSupercollections(s);

          for (; iter001->nextP(); ) {
            a = ((LogicObject*)(iter001->value));
            if (!supers->memberP(a)) {
              collection = cons(a, collection);
            }
          }
        }
      }
    }
    return (collection->allocateIterator());
  }
}

Iterator* allAncestorCollections(Object* self, Keyword* instanceordescription) {
  if (instanceordescription == KWD_CLASSIFY_INSTANCE) {
    return (allAncestorsOfParents(allIsaCollections(self)));
  }
  else if (instanceordescription == KWD_CLASSIFY_DESCRIPTION) {
    return (allSupercollections(((LogicObject*)(self))));
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << instanceordescription << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

// If true (the default) only consider those relations (or instances) for
// classification that have at least one non-inferable parent (or type).  This
// can greatly reduce the classification effort.  To find entities that were
// left unclassified due to this optimization use `list-unclassified-relations'
// or `list-unclassified-instances'.
DEFINE_STELLA_SPECIAL(oCLASSIFY_FROM_NON_INFERABLE_PARENTS_ONLYpo, boolean , true);

void helpUpclassifyOneEntity(LogicObject* self, Keyword* instanceordescription) {
  if (upclassifiedP(self)) {
    return;
  }
  { MarkerTable* alreadyvisitedtable = createMarkerStorage(false);
    MarkerTable* instanceisbelowtable = createMarkerStorage(false);
    List* newparentdescriptions = newList();

    instanceisbelowtable->setMarker(self);
    { LogicObject* super = NULL;
      Iterator* iter000 = allAncestorCollections(self, instanceordescription);

      for (; iter000->nextP(); ) {
        super = ((LogicObject*)(iter000->value));
        instanceisbelowtable->setMarker(super);
      }
    }
    if (((boolean)(oTRACED_KEYWORDSo)) &&
        oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER)) {
      std::cout << "   WORLD: " << oCONTEXTo << "  self: " << self << std::endl << "   ANCESTORS: " << allAncestorCollections(self, instanceordescription)->consify() << std::endl;
    }
    { LogicObject* super = NULL;
      Iterator* iter001 = allAncestorCollections(self, instanceordescription);

      for (; iter001->nextP(); ) {
        super = ((LogicObject*)(iter001->value));
        if (isaP(super, SGT_CLASSIFY_LOGIC_DESCRIPTION) &&
            (((!oCLASSIFY_FROM_NON_INFERABLE_PARENTS_ONLYpo) ||
            nonInferableP(((Description*)(super)))) &&
             (!alreadyvisitedtable->testMarkerP(super)))) {
          alreadyvisitedtable->setMarker(super);
          collectSubsumingParentsBelow(self, ((Description*)(super)), newparentdescriptions, alreadyvisitedtable, instanceisbelowtable, ((instanceordescription == KWD_CLASSIFY_INSTANCE) ? ((cpp_function_code)(&instanceSatisfiesDescriptionP)) : ((cpp_function_code)(&descriptionSpecializesDescriptionP))));
        }
      }
    }
    { LogicObject* pd = NULL;
      Cons* iter002 = mostSpecificNamedCollections(newparentdescriptions->theConsList);

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        pd = ((LogicObject*)(iter002->value));
        if (instanceordescription == KWD_CLASSIFY_INSTANCE) {
          addIsaLink(self, ((Description*)(pd)));
        }
        else if (instanceordescription == KWD_CLASSIFY_DESCRIPTION) {
          addSubsumptionLink(((Description*)(self)), ((Description*)(pd)));
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << instanceordescription << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
    refreshUpclassificationTimestamp(self);
  }
}

void upclassifyOneInstance(LogicObject* self) {
  if (upclassifiedP(self)) {
    return;
  }
  if (((boolean)(oTRACED_KEYWORDSo)) &&
      (oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER) ||
       oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER_PROFILE))) {
    std::cout << "UPCLASSIFY:  " << self << std::endl;
  }
  emitThinkingDot(KWD_CLASSIFY_UPCLASSIFY);
  helpUpclassifyOneEntity(self, KWD_CLASSIFY_INSTANCE);
}

void upclassifyOneDescription(LogicObject* self) {
  if (upclassifiedP(self) ||
      (!isaP(self, SGT_CLASSIFY_LOGIC_DESCRIPTION))) {
    return;
  }
  if (((boolean)(oTRACED_KEYWORDSo)) &&
      (oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER) ||
       oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER_PROFILE))) {
    std::cout << "UPCLASSIFY: " << self << std::endl;
  }
  emitThinkingDot(KWD_CLASSIFY_UPCLASSIFY);
  { Cons* equivalents = allEquivalentCollections(self, true);

    { LogicObject* e = NULL;
      Cons* iter000 = equivalents;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        e = ((LogicObject*)(iter000->value));
        if (!namedDescriptionP(((Description*)(e)))) {
          { Description* pd = NULL;
            Cons* iter001 = allIntensionalParents(((Description*)(e)))->theConsList;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              pd = ((Description*)(iter001->value));
              addSubsumptionLink(((Description*)(self)), pd);
            }
          }
        }
      }
    }
  }
  { NamedDescription* super = NULL;
    Cons* iter002 = allNamedDirectSuperdescriptions(((Description*)(self)), true);

    for (; !(iter002 == NIL); iter002 = iter002->rest) {
      super = ((NamedDescription*)(iter002->value));
      upclassifyOneDescription(super);
    }
  }
  helpUpclassifyOneEntity(self, KWD_CLASSIFY_DESCRIPTION);
}

void helpDownclassifyOneDescription(LogicObject* node, LogicObject* self, Cons* necessaryancestors, MarkerTable* alreadyvisitedtable) {
  if (alreadyvisitedtable->testMarkerP(node) ||
      collectionImpliesCollectionP(((Description*)(node)), ((Description*)(self)))) {
    return;
  }
  alreadyvisitedtable->setMarker(node);
  { boolean nodecouldbetheoneP = true;

    if (upclassificationTimestamp(node) == -1) {
      upclassifyOneDescription(node);
    }
    else if (!upclassifiedLaterThanP(node, self)) {
      { boolean foundP000 = false;

        { LogicObject* ancestor = NULL;
          Cons* iter000 = necessaryancestors;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            ancestor = ((LogicObject*)(iter000->value));
            if (upclassifiedLaterThanP(node, ancestor) &&
                (!collectionImpliesCollectionP(((Description*)(node)), ((Description*)(ancestor))))) {
              foundP000 = true;
              break;
            }
          }
        }
        if (foundP000) {
          nodecouldbetheoneP = false;
        }
        else {
          upclassifyOneDescription(node);
        }
      }
    }
    if (nodecouldbetheoneP &&
        collectionImpliesCollectionP(((Description*)(node)), ((Description*)(self)))) {
      return;
    }
    { NamedDescription* subnode = NULL;
      Cons* iter001 = allNamedDirectSubdescriptions(((Description*)(node)));

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        subnode = ((NamedDescription*)(iter001->value));
        helpDownclassifyOneDescription(subnode, self, necessaryancestors, alreadyvisitedtable);
      }
    }
  }
}

LogicObject* collectionWithFewestChildren(Cons* collections) {
  if (!((boolean)(collections->rest))) {
    return (((LogicObject*)(collections->value)));
  }
  { LogicObject* bestcollection = ((LogicObject*)(collections->value));
    int lowestchildcount = 100;

    { LogicObject* c = NULL;
      Cons* iter000 = collections;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        c = ((LogicObject*)(iter000->value));
        { int childcount = 0;

          { ConsIterator* p = applicableRulesOfDescription(c, KWD_CLASSIFY_BACKWARD, true)->allocateIterator();

            for (; p->nextP(); ) {
              childcount = childcount + 1;
            }
          }
          if (childcount < lowestchildcount) {
            bestcollection = c;
            lowestchildcount = childcount;
          }
        }
      }
    }
    return (bestcollection);
  }
}

LogicObject* chooseBestDownclassifiedParent(Cons* parents) {
  if (parents == NIL) {
    return (NULL);
  }
  { Cons* downclassifiedparents = NIL;
    LogicObject* bestparent = NULL;

    { LogicObject* p = NULL;
      Cons* iter000 = parents;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        p = ((LogicObject*)(iter000->value));
        if (downclassifiedP(p)) {
          {
          }
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(p, NIL);
              if (downclassifiedparents == NIL) {
                downclassifiedparents = collect000;
              }
              else {
                addConsToEndOfConsList(downclassifiedparents, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(p, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    switch (downclassifiedparents->length()) {
      case 0: 
        { Cons* namedparents = NIL;

          { LogicObject* p = NULL;
            Cons* iter001 = parents;
            Cons* collect001 = NULL;

            for  (; !(iter001 == NIL); 
                  iter001 = iter001->rest) {
              p = ((LogicObject*)(iter001->value));
              if (namedDescriptionP(((Description*)(p)))) {
                if (!((boolean)(collect001))) {
                  {
                    collect001 = cons(p, NIL);
                    if (namedparents == NIL) {
                      namedparents = collect001;
                    }
                    else {
                      addConsToEndOfConsList(namedparents, collect001);
                    }
                  }
                }
                else {
                  {
                    collect001->rest = cons(p, NIL);
                    collect001 = collect001->rest;
                  }
                }
              }
            }
          }
          if (!(namedparents == NIL)) {
            bestparent = collectionWithFewestChildren(namedparents);
          }
          if (!((boolean)(bestparent))) {
            bestparent = collectionWithFewestChildren(parents);
          }
          downclassifyOneDescription(bestparent);
        }
        break;
      case 1: 
        bestparent = ((LogicObject*)(downclassifiedparents->value));
        break;
      default:
        bestparent = collectionWithFewestChildren(downclassifiedparents);
        break;
    }
    if (((boolean)(oTRACED_KEYWORDSo)) &&
        oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER)) {
      std::cout << "   BEST PARENT:   " << bestparent << "   ALL-PARENTS: " << parents << std::endl;
    }
    return (bestparent);
  }
}

void downclassifyOneDescription(LogicObject* self) {
  { 
    BIND_STELLA_SPECIAL(oCLASSIFICATIONSESSIONo, ClassificationSession*, getClassificationSession(KWD_CLASSIFY_DESCRIPTION));
    if (!downclassifiedP(self)) {
      if (nonInferableP(((Description*)(self)))) {
        refreshDownclassificationTimestamp(self);
        return;
      }
      if (((boolean)(oTRACED_KEYWORDSo)) &&
          (oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER) ||
           oTRACED_KEYWORDSo->membP(KWD_CLASSIFY_CLASSIFIER_PROFILE))) {
        std::cout << "DOWNCLASSIFY-ONE-DESCRIPTION:  " << self << std::endl;
      }
      emitThinkingDot(KWD_CLASSIFY_DOWNCLASSIFY);
      { MarkerTable* alreadyvisitedtable = createMarkerStorage(false);
        Cons* parents = allNamedDirectSuperdescriptions(((Description*)(self)), false);
        LogicObject* bestparent = chooseBestDownclassifiedParent(parents);
        Cons* otherparents = parents->remove(bestparent);

        alreadyvisitedtable->setMarker(self);
        if (((boolean)(bestparent))) {
          { NamedDescription* child = NULL;
            Cons* iter000 = allNamedDirectSubdescriptions(((Description*)(bestparent)));

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              child = ((NamedDescription*)(iter000->value));
              helpDownclassifyOneDescription(child, self, otherparents, alreadyvisitedtable);
            }
          }
        }
      }
      refreshDownclassificationTimestamp(self);
    }
  }
}

boolean Description::virginP() {
  { Description* self = this;

    return (unfilteredDependentPropositions(self, NULL)->emptyP() &&
        (!namedCollectionP(self)));
  }
}

void evaporateVirgin(Description* self) {
  { List* parentimplies = newList();
    List* childimplies = newList();
    Description* parent = NULL;
    Description* child = NULL;
    Proposition* bridgeprop = NULL;

    { Proposition* p = NULL;
      Iterator* iter000 = unfilteredDependentPropositions(self, NULL)->allocateIterator();

      for (; iter000->nextP(); ) {
        p = ((Proposition*)(iter000->value));
        if ((p->arguments->theArray)[0] == self) {
          parentimplies->push(p);
        }
        else {
          childimplies->push(p);
        }
      }
    }
    { Proposition* cp = NULL;
      Cons* iter001 = childimplies->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        cp = ((Proposition*)(iter001->value));
        child = ((Description*)((cp->arguments->theArray)[0]));
        { Proposition* pp = NULL;
          Cons* iter002 = parentimplies->theConsList;

          for (; !(iter002 == NIL); iter002 = iter002->rest) {
            pp = ((Proposition*)(iter002->value));
            parent = ((Description*)((pp->arguments->theArray)[1]));
            bridgeprop = assertDescriptionImpliesDescription(child, parent, true);
            if (((BooleanWrapper*)(dynamicSlotValue(cp->dynamicSlots, SYM_CLASSIFY_LOGIC_SUBRELATION_LINKp, FALSE_WRAPPER)))->wrapperValue &&
                ((BooleanWrapper*)(dynamicSlotValue(pp->dynamicSlots, SYM_CLASSIFY_LOGIC_SUBRELATION_LINKp, FALSE_WRAPPER)))->wrapperValue) {
              setDynamicSlotValue(bridgeprop->dynamicSlots, SYM_CLASSIFY_LOGIC_SUBRELATION_LINKp, TRUE_WRAPPER, FALSE_WRAPPER);
            }
            updatePropositionTruthValue(bridgeprop, KWD_CLASSIFY_ASSERT_TRUE);
          }
        }
      }
    }
    { Proposition* p = NULL;
      Iterator* iter003 = unfilteredDependentPropositions(self, NULL)->allocateIterator();

      for (; iter003->nextP(); ) {
        p = ((Proposition*)(iter003->value));
        destroyProposition(p);
      }
    }
  }
}

Cons* findDirectSupersAndSubs(Description* self, boolean onlysupersP, Cons*& _Return1, Cons*& _Return2) {
  // Classify 'self' and return three values, its direct
  // supers, direct subs, and a list of equivalent descriptions.
  // Setting 'supersOnly?' may speed up the computation (perhaps by a lot).
  // If 'description' is nameless and has no dependent propositions, then
  // it is automatically removed from the hierarchy after classification.
  finalizeObjects();
  if (!((boolean)(self))) {
    _Return1 = NIL;
    _Return2 = NIL;
    return (NIL);
  }
  { 
    BIND_STELLA_SPECIAL(oFINDSUPERSANDSUBSDESCRIPTIONo, Description*, self);
    { 
      BIND_STELLA_SPECIAL(oCLASSIFICATIONSESSIONo, ClassificationSession*, getClassificationSession(KWD_CLASSIFY_DESCRIPTION));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oCLASSIFICATIONSESSIONo->classificationWorld);
      { boolean virginP = self->virginP();
        int oldcurrenttime = currentClassificationTime();
        Cons* supers = NIL;
        Cons* subs = NIL;
        Cons* equivalents = NIL;

        if (virginP) {
          introduceIntoClassificationSession(self);
        }
        upclassifyOneDescription(self);
        { NamedDescription* super = NULL;
          Cons* iter000 = allNamedDirectSuperdescriptions(self, false);

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            super = ((NamedDescription*)(iter000->value));
            upclassifyOneDescription(super);
          }
        }
        supers = allNamedDirectSuperdescriptions(self, true);
        if (!onlysupersP) {
          downclassifyOneDescription(self);
          subs = allDirectSubcollections(self, true)->consify();
        }
        { LogicObject* e = NULL;
          Cons* iter001 = allEquivalentCollections(self, false);
          Cons* collect000 = NULL;

          for  (; !(iter001 == NIL); 
                iter001 = iter001->rest) {
            e = ((LogicObject*)(iter001->value));
            if (namedDescriptionP(((Description*)(e)))) {
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(e, NIL);
                  if (equivalents == NIL) {
                    equivalents = collect000;
                  }
                  else {
                    addConsToEndOfConsList(equivalents, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(e, NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
        }
        if (virginP) {
          evaporateVirgin(self);
          oCLASSIFICATIONSESSIONo->introductionTimestampStack->pop();
        }
        _Return1 = subs;
        _Return2 = equivalents;
        return (supers);
      }
    }
  }
}

Cons* findDirectSupersOfInstance(Object* self) {
  // Classify 'self' and return a list of most specific 
  // named descriptions among all descriptions that it satisfies.
  finalizeObjects();
  if (!((boolean)(self))) {
    return (NIL);
  }
  { 
    BIND_STELLA_SPECIAL(oCLASSIFICATIONSESSIONo, ClassificationSession*, getClassificationSession(KWD_CLASSIFY_INSTANCE));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oCLASSIFICATIONSESSIONo->classificationWorld);
    upclassifyOneInstance(((LogicObject*)(self)));
    return (mostSpecificNamedCollections(allIsaCollections(self)));
  }
}

void upclassifyNamedDescriptions(Module* module, boolean localP) {
  // Classify named descriptions local to 'module' and inherited
  // by 'module'.  If 'local?', don't classify inherited descriptions.  If
  // 'module' is NULL, classify descriptions in all modules.
  { 
    BIND_STELLA_SPECIAL(oCLASSIFICATIONSESSIONo, ClassificationSession*, getClassificationSession(KWD_CLASSIFY_DESCRIPTION));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oCLASSIFICATIONSESSIONo->classificationWorld);
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, ((!((boolean)(module))) ? oMODULEo : module));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      if (!((boolean)(module))) {
        upclassifyAllDescriptions();
      }
      else if (localP) {
        { NamedDescription* d = NULL;
          Iterator* iter000 = allNamedDescriptions(module, true);

          for (; iter000->nextP(); ) {
            d = ((NamedDescription*)(iter000->value));
            upclassifyOneDescription(d);
          }
        }
      }
      else {
        { ClassificationSession* session = oCLASSIFICATIONSESSIONo;

          if (!session->everythingClassifiedP) {
            { Module* m = NULL;
              Iterator* iter001 = allIncludedModules(module);

              for (; iter001->nextP(); ) {
                m = ((Module*)(iter001->value));
                { NamedDescription* d = NULL;
                  Iterator* iter002 = allNamedDescriptions(m, true);

                  for (; iter002->nextP(); ) {
                    d = ((NamedDescription*)(iter002->value));
                    upclassifyOneDescription(d);
                  }
                }
              }
            }
            session->everythingClassifiedP = true;
          }
        }
      }
    }
  }
}

void classifyRelations(Cons* options) {
  // Classify relations visible in the module defined by the :module option (which
  // defaults to the current module).  If :module was explicitly specified as NULL,
  // classify relations in all modules.  If `:local?' is specified as TRUE only classify
  // relations that belong to the specified module but not any modules it inherits.  For
  // backwards compatibility, this command also supports the old <module> <local?>
  // arguments specified without keywords.
  // 
  // Conceptually, the classifier operates by comparing each concept or relation
  // with all other concepts/relations, searching for a proof that a
  // subsumption relation exists between each pair. Whenever a new subsumption
  // relation is discovered, the classifier adds an `implication' link between
  // members of the pair, thereby augmenting the structure of the
  // concept or relation hierarchy. The implemented classification algorithm is
  // relatively efficient -- it works hard at limiting the number of concepts
  // or relations that need to be checked for possible subsumption
  // relationships.
  // 
  finalizeObjects();
  { Cons* optionslist = options;
    PropertyList* theoptions = parseOptions((keywordP(optionslist->value) ? optionslist : consList(4, KWD_CLASSIFY_MODULE, optionslist->value, KWD_CLASSIFY_LOCALp, optionslist->rest->value)), listO(5, KWD_CLASSIFY_MODULE, SGT_CLASSIFY_STELLA_MODULE, KWD_CLASSIFY_LOCALp, SGT_CLASSIFY_STELLA_BOOLEAN, NIL), true, false);
    Module* themodule = ((Module*)(theoptions->lookupWithDefault(KWD_CLASSIFY_MODULE, NULL)));
    boolean localP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_CLASSIFY_LOCALp, FALSE_WRAPPER))));

    if ((!((boolean)(themodule))) &&
        (!optionslist->memberP(KWD_CLASSIFY_MODULE))) {
      themodule = oMODULEo;
    }
    upclassifyNamedDescriptions(themodule, localP);
  }
}

void classifyRelationsEvaluatorWrapper(Cons* arguments) {
  classifyRelations(arguments);
}

Cons* listUnclassifiedRelations(Cons* options) {
  // Collect all named description in the module defined by the :module option (which defaults
  // to the current module) that were not (or will not be) classified due to their lack of
  // non-inferable/primitive ancestor relations.  If :module was explicitly specified as NULL,
  // look in all currently defined modules.  If `:local?' is specified as TRUE only look
  // in the specified module but not any modules it inherits.  For backwards compatibility,
  // this command also supports the old <module> <local?> arguments specified without keywords.
  if (!oCLASSIFY_FROM_NON_INFERABLE_PARENTS_ONLYpo) {
    return (NIL);
  }
  finalizeObjects();
  { Cons* optionslist = options;
    PropertyList* theoptions = parseOptions((keywordP(optionslist->value) ? optionslist : consList(4, KWD_CLASSIFY_MODULE, optionslist->value, KWD_CLASSIFY_LOCALp, optionslist->rest->value)), listO(5, KWD_CLASSIFY_MODULE, SGT_CLASSIFY_STELLA_MODULE, KWD_CLASSIFY_LOCALp, SGT_CLASSIFY_STELLA_BOOLEAN, NIL), true, false);
    Module* themodule = ((Module*)(theoptions->lookupWithDefault(KWD_CLASSIFY_MODULE, NULL)));
    boolean localP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_CLASSIFY_LOCALp, FALSE_WRAPPER))));
    Cons* unclassified = NIL;

    if ((!((boolean)(themodule))) &&
        (!optionslist->memberP(KWD_CLASSIFY_MODULE))) {
      themodule = oMODULEo;
    }
    { 
      BIND_STELLA_SPECIAL(oCLASSIFICATIONSESSIONo, ClassificationSession*, getClassificationSession(KWD_CLASSIFY_DESCRIPTION));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oCLASSIFICATIONSESSIONo->classificationWorld);
      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, ((!((boolean)(themodule))) ? oMODULEo : themodule));
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        { NamedDescription* d = NULL;
          Iterator* iter000 = allNamedDescriptions(themodule, localP);
          Cons* collect000 = NULL;

          for  (; iter000->nextP(); ) {
            d = ((NamedDescription*)(iter000->value));
            { boolean testValue000 = false;

              testValue000 = inferableP(d);
              if (testValue000) {
                { boolean foundP000 = false;

                  { LogicObject* super = NULL;
                    Iterator* iter001 = allAncestorCollections(d, KWD_CLASSIFY_DESCRIPTION);

                    for (; iter001->nextP(); ) {
                      super = ((LogicObject*)(iter001->value));
                      if (nonInferableP(((Description*)(super)))) {
                        foundP000 = true;
                        break;
                      }
                    }
                  }
                  testValue000 = foundP000;
                }
                testValue000 = !testValue000;
              }
              if (testValue000) {
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(d, NIL);
                    if (unclassified == NIL) {
                      unclassified = collect000;
                    }
                    else {
                      addConsToEndOfConsList(unclassified, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(d, NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
          }
        }
      }
    }
    return (unclassified);
  }
}

Cons* listUnclassifiedRelationsEvaluatorWrapper(Cons* arguments) {
  return (listUnclassifiedRelations(arguments));
}

void upclassifyInstances(Module* module, boolean localP) {
  // Classify instances local to 'module' and inherited
  // by 'module'.  If 'local?', don't classify inherited descriptions.  If
  // 'module' is NULL, classify descriptions in all modules.
  { 
    BIND_STELLA_SPECIAL(oCLASSIFICATIONSESSIONo, ClassificationSession*, getClassificationSession(KWD_CLASSIFY_INSTANCE));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oCLASSIFICATIONSESSIONo->classificationWorld);
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, ((!((boolean)(module))) ? oMODULEo : module));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      if (!((boolean)(module))) {
        upclassifyAllInstances();
      }
      else if (localP) {
        { LogicObject* i = NULL;
          Iterator* iter000 = allInstances(module, true);

          for (; iter000->nextP(); ) {
            i = ((LogicObject*)(iter000->value));
            upclassifyOneInstance(i);
          }
        }
      }
      else {
        { Module* m = NULL;
          Iterator* iter001 = allIncludedModules(module);

          for (; iter001->nextP(); ) {
            m = ((Module*)(iter001->value));
            { LogicObject* i = NULL;
              Iterator* iter002 = allInstances(m, true);

              for (; iter002->nextP(); ) {
                i = ((LogicObject*)(iter002->value));
                upclassifyOneInstance(i);
              }
            }
          }
        }
      }
    }
  }
}

void classifyInstances(Cons* options) {
  // Classify instances visible in the module defined by the :module option (which
  // defaults to the current module).  If :module was explicitly specified as NULL,
  // classify instances in all modules.  If `:local?' is specified as TRUE only classify
  // instances that belong to the specified module but not any modules it inherits.  For
  // backwards compatibility, this command also supports the old <module> <local?>
  // arguments specified without keywords.
  // 
  // Conceptually, the classifier operates by comparing each instance with all
  // concepts in the hierarchy, searching for a proof for each pairing indicating
  // that the instance belongs to the concept.  Whenever a new `is-a' relation is
  // discovered, the classifier adds an `is-a' link between the instance and the
  // concept, thereby recording an additional fact about the instance.  The
  // implemented classification algorithm is relatively efficient -- it works hard at
  // limiting the number of concepts or relations that need to be checked for
  // possible is-a relationships.
  // 
  finalizeObjects();
  { Cons* optionslist = options;
    PropertyList* theoptions = parseOptions((keywordP(optionslist->value) ? optionslist : consList(4, KWD_CLASSIFY_MODULE, optionslist->value, KWD_CLASSIFY_LOCALp, optionslist->rest->value)), listO(5, KWD_CLASSIFY_MODULE, SGT_CLASSIFY_STELLA_MODULE, KWD_CLASSIFY_LOCALp, SGT_CLASSIFY_STELLA_BOOLEAN, NIL), true, false);
    Module* themodule = ((Module*)(theoptions->lookupWithDefault(KWD_CLASSIFY_MODULE, NULL)));
    boolean localP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_CLASSIFY_LOCALp, FALSE_WRAPPER))));

    if ((!((boolean)(themodule))) &&
        (!optionslist->memberP(KWD_CLASSIFY_MODULE))) {
      themodule = oMODULEo;
    }
    upclassifyInstances(themodule, localP);
  }
}

void classifyInstancesEvaluatorWrapper(Cons* arguments) {
  classifyInstances(arguments);
}

Cons* listUnclassifiedInstances(Cons* options) {
  // Collect all instances in the module defined by the :module option (which defaults
  // to the current module) that were not (or will not be) classified due to their lack of
  // non-inferable/primitive type assertions.  If :module was explicitly specified as NULL,
  // look in all currently defined modules.  If `:local?' is specified as TRUE only look
  // in the specified module but not any modules it inherits.  For backwards compatibility,
  // this command also supports the old <module> <local?> arguments specified without keywords.
  if (!oCLASSIFY_FROM_NON_INFERABLE_PARENTS_ONLYpo) {
    return (NIL);
  }
  finalizeObjects();
  { Cons* optionslist = options;
    PropertyList* theoptions = parseOptions((keywordP(optionslist->value) ? optionslist : consList(4, KWD_CLASSIFY_MODULE, optionslist->value, KWD_CLASSIFY_LOCALp, optionslist->rest->value)), listO(5, KWD_CLASSIFY_MODULE, SGT_CLASSIFY_STELLA_MODULE, KWD_CLASSIFY_LOCALp, SGT_CLASSIFY_STELLA_BOOLEAN, NIL), true, false);
    Module* themodule = ((Module*)(theoptions->lookupWithDefault(KWD_CLASSIFY_MODULE, NULL)));
    boolean localP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_CLASSIFY_LOCALp, FALSE_WRAPPER))));
    Cons* unclassified = NIL;

    if ((!((boolean)(themodule))) &&
        (!optionslist->memberP(KWD_CLASSIFY_MODULE))) {
      themodule = oMODULEo;
    }
    { 
      BIND_STELLA_SPECIAL(oCLASSIFICATIONSESSIONo, ClassificationSession*, getClassificationSession(KWD_CLASSIFY_INSTANCE));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oCLASSIFICATIONSESSIONo->classificationWorld);
      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, ((!((boolean)(themodule))) ? oMODULEo : themodule));
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        { LogicObject* i = NULL;
          Iterator* iter000 = allInstances(themodule, localP);
          Cons* collect000 = NULL;

          for  (; iter000->nextP(); ) {
            i = ((LogicObject*)(iter000->value));
            { boolean testValue000 = false;

              testValue000 = !functionOutputSkolemP(i);
              if (testValue000) {
                { boolean foundP000 = false;

                  { LogicObject* type = NULL;
                    Iterator* iter001 = allAncestorCollections(i, KWD_CLASSIFY_INSTANCE);

                    for (; iter001->nextP(); ) {
                      type = ((LogicObject*)(iter001->value));
                      if (nonInferableP(((Description*)(type)))) {
                        foundP000 = true;
                        break;
                      }
                    }
                  }
                  testValue000 = foundP000;
                }
                testValue000 = !testValue000;
              }
              if (testValue000) {
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(i, NIL);
                    if (unclassified == NIL) {
                      unclassified = collect000;
                    }
                    else {
                      addConsToEndOfConsList(unclassified, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(i, NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
          }
        }
      }
    }
    return (unclassified);
  }
}

Cons* listUnclassifiedInstancesEvaluatorWrapper(Cons* arguments) {
  return (listUnclassifiedInstances(arguments));
}

void upclassifyAllDescriptions() {
  // Classify all named descriptions.
  finalizeObjects();
  { 
    BIND_STELLA_SPECIAL(oCLASSIFICATIONSESSIONo, ClassificationSession*, getClassificationSession(KWD_CLASSIFY_DESCRIPTION));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oCLASSIFICATIONSESSIONo->classificationWorld);
    { NamedDescription* d = NULL;
      Iterator* iter000 = allNamedDescriptions(NULL, false);

      for (; iter000->nextP(); ) {
        d = ((NamedDescription*)(iter000->value));
        upclassifyOneDescription(d);
      }
    }
  }
}

void upclassifyAllInstances() {
  // Classify all named instances.
  finalizeObjects();
  { 
    BIND_STELLA_SPECIAL(oCLASSIFICATIONSESSIONo, ClassificationSession*, getClassificationSession(KWD_CLASSIFY_INSTANCE));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oCLASSIFICATIONSESSIONo->classificationWorld);
    { LogicObject* i = NULL;
      Iterator* iter000 = allInstances(NULL, false);

      for (; iter000->nextP(); ) {
        i = ((LogicObject*)(iter000->value));
        upclassifyOneInstance(i);
      }
    }
  }
}

Cons* allEquivalentCollections(LogicObject* self, boolean reflexiveP) {
  { Cons* equivalents = consList(1, self);
    List* unscannedequivalents = list(1, self);
    LogicObject* u = NULL;

    if (allSupercollections(self)->memberP(self)) {
      for (;;) {
        u = ((LogicObject*)(unscannedequivalents->pop()));
        { LogicObject* parent = NULL;
          Iterator* iter000 = allDirectSupercollections(u, false);

          for (; iter000->nextP(); ) {
            parent = ((LogicObject*)(iter000->value));
            if ((!equivalents->memberP(parent)) &&
                allSupercollections(parent)->memberP(u)) {
              equivalents = cons(parent, equivalents);
              unscannedequivalents->push(parent);
            }
          }
        }
        if (unscannedequivalents->emptyP()) {
          break;
        }
      }
    }
    if (reflexiveP) {
      return (equivalents);
    }
    else {
      return (equivalents->remove(self));
    }
  }
}

Cons* allCycles(Module* module, boolean localP) {
  // Return a list of lists of descriptions that are
  // provably co-extensional.
  return (NULL);
}

void helpStartupClassify1() {
  {
    KWD_CLASSIFY_IMPLIES_PROPOSITION_UPDATE = ((Keyword*)(internRigidSymbolWrtModule("IMPLIES-PROPOSITION-UPDATE", NULL, 2)));
    KWD_CLASSIFY_PREDICATE = ((Keyword*)(internRigidSymbolWrtModule("PREDICATE", NULL, 2)));
    KWD_CLASSIFY_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    KWD_CLASSIFY_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    KWD_CLASSIFY_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    KWD_CLASSIFY_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("EXISTS", NULL, 2)));
    SGT_CLASSIFY_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
    KWD_CLASSIFY_BACKWARD = ((Keyword*)(internRigidSymbolWrtModule("BACKWARD", NULL, 2)));
    SYM_CLASSIFY_LOGIC_FORWARD_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("FORWARD-ONLY?", NULL, 0)));
    SGT_CLASSIFY_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
    SGT_CLASSIFY_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
    SGT_CLASSIFY_LOGIC_F_INFERABLE_WITH_CYCLE_CHECKp_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-INFERABLE-WITH-CYCLE-CHECK?-MEMO-TABLE-000", NULL, 1)));
    SGT_CLASSIFY_LOGIC_MARKER_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("MARKER-TABLE", NULL, 1)));
    SYM_CLASSIFY_LOGIC_TEST_TABLE = ((Symbol*)(internRigidSymbolWrtModule("TEST-TABLE", NULL, 0)));
    SYM_CLASSIFY_LOGIC_RECALL_TABLE = ((Symbol*)(internRigidSymbolWrtModule("RECALL-TABLE", NULL, 0)));
    SYM_CLASSIFY_LOGIC_SUPPORTS_RECALLp = ((Symbol*)(internRigidSymbolWrtModule("SUPPORTS-RECALL?", NULL, 0)));
    SYM_CLASSIFY_LOGIC_SUBSUMPTION_LINKp = ((Symbol*)(internRigidSymbolWrtModule("SUBSUMPTION-LINK?", NULL, 0)));
    KWD_CLASSIFY_CLASSIFIER_INFERENCES = ((Keyword*)(internRigidSymbolWrtModule("CLASSIFIER-INFERENCES", NULL, 2)));
    SGT_CLASSIFY_LOGIC_CLASSIFICATION_CACHE = ((Surrogate*)(internRigidSymbolWrtModule("CLASSIFICATION-CACHE", NULL, 1)));
    SYM_CLASSIFY_LOGIC_INFERABLE_DIRECT_SUBDESCRIPTIONS = ((Symbol*)(internRigidSymbolWrtModule("INFERABLE-DIRECT-SUBDESCRIPTIONS", NULL, 0)));
    SYM_CLASSIFY_LOGIC_CACHE_UPCLASSIFICATION_TIMESTAMP = ((Symbol*)(internRigidSymbolWrtModule("CACHE-UPCLASSIFICATION-TIMESTAMP", NULL, 0)));
    SYM_CLASSIFY_LOGIC_CACHE_DOWNCLASSIFICATION_TIMESTAMP = ((Symbol*)(internRigidSymbolWrtModule("CACHE-DOWNCLASSIFICATION-TIMESTAMP", NULL, 0)));
    SYM_CLASSIFY_LOGIC_INTRODUCTION_TIMESTAMP = ((Symbol*)(internRigidSymbolWrtModule("INTRODUCTION-TIMESTAMP", NULL, 0)));
    SGT_CLASSIFY_LOGIC_CLASSIFICATION_SESSION = ((Surrogate*)(internRigidSymbolWrtModule("CLASSIFICATION-SESSION", NULL, 1)));
    SYM_CLASSIFY_LOGIC_CLASSIFICATION_WORLD = ((Symbol*)(internRigidSymbolWrtModule("CLASSIFICATION-WORLD", NULL, 0)));
    SYM_CLASSIFY_LOGIC_CLASSIFICATION_CACHE_TABLE = ((Symbol*)(internRigidSymbolWrtModule("CLASSIFICATION-CACHE-TABLE", NULL, 0)));
    SYM_CLASSIFY_LOGIC_CLASSIFICATION_TIMECLOCK = ((Symbol*)(internRigidSymbolWrtModule("CLASSIFICATION-TIMECLOCK", NULL, 0)));
    SYM_CLASSIFY_LOGIC_INTRODUCTION_TIMESTAMP_STACK = ((Symbol*)(internRigidSymbolWrtModule("INTRODUCTION-TIMESTAMP-STACK", NULL, 0)));
    SYM_CLASSIFY_LOGIC_EVERYTHING_CLASSIFIEDp = ((Symbol*)(internRigidSymbolWrtModule("EVERYTHING-CLASSIFIED?", NULL, 0)));
    SYM_CLASSIFY_LOGIC_LAST_CACHE_TABLE_KEY = ((Symbol*)(internRigidSymbolWrtModule("LAST-CACHE-TABLE-KEY", NULL, 0)));
    SYM_CLASSIFY_LOGIC_LAST_CACHE_TABLE_VALUE = ((Symbol*)(internRigidSymbolWrtModule("LAST-CACHE-TABLE-VALUE", NULL, 0)));
    KWD_CLASSIFY_DESCRIPTION = ((Keyword*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 2)));
    KWD_CLASSIFY_META = ((Keyword*)(internRigidSymbolWrtModule("META", NULL, 2)));
    KWD_CLASSIFY_INSTANCE = ((Keyword*)(internRigidSymbolWrtModule("INSTANCE", NULL, 2)));
    KWD_CLASSIFY_TMS = ((Keyword*)(internRigidSymbolWrtModule("TMS", NULL, 2)));
    SYM_CLASSIFY_LOGIC_CLASSIFICATION_SESSION = ((Symbol*)(internRigidSymbolWrtModule("CLASSIFICATION-SESSION", NULL, 0)));
    SYM_CLASSIFY_LOGIC_META_INFERENCE_CACHE = ((Symbol*)(internRigidSymbolWrtModule("META-INFERENCE-CACHE", NULL, 0)));
    KWD_CLASSIFY_JUST_IN_TIME = ((Keyword*)(internRigidSymbolWrtModule("JUST-IN-TIME", NULL, 2)));
    KWD_CLASSIFY_CLASSIFIER = ((Keyword*)(internRigidSymbolWrtModule("CLASSIFIER", NULL, 2)));
    KWD_CLASSIFY_CLASSIFIER_PROFILE = ((Keyword*)(internRigidSymbolWrtModule("CLASSIFIER-PROFILE", NULL, 2)));
    KWD_CLASSIFY_UPCLASSIFY = ((Keyword*)(internRigidSymbolWrtModule("UPCLASSIFY", NULL, 2)));
    KWD_CLASSIFY_DOWNCLASSIFY = ((Keyword*)(internRigidSymbolWrtModule("DOWNCLASSIFY", NULL, 2)));
    SYM_CLASSIFY_LOGIC_SUBRELATION_LINKp = ((Symbol*)(internRigidSymbolWrtModule("SUBRELATION-LINK?", NULL, 0)));
    KWD_CLASSIFY_ASSERT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("ASSERT-TRUE", NULL, 2)));
    KWD_CLASSIFY_MODULE = ((Keyword*)(internRigidSymbolWrtModule("MODULE", NULL, 2)));
    KWD_CLASSIFY_LOCALp = ((Keyword*)(internRigidSymbolWrtModule("LOCAL?", NULL, 2)));
    SGT_CLASSIFY_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 1)));
    SGT_CLASSIFY_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", getStellaModule("/STELLA", true), 1)));
    SYM_CLASSIFY_LOGIC_STARTUP_CLASSIFY = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-CLASSIFY", NULL, 0)));
    SYM_CLASSIFY_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupClassify2() {
  {
    defineFunctionObject("BUMP-INFERABLE-TIMESTAMP", "(DEFUN BUMP-INFERABLE-TIMESTAMP () :GLOBALLY-INLINE? TRUE (BUMP-MEMOIZATION-TIMESTAMP :IMPLIES-PROPOSITION-UPDATE))", ((cpp_function_code)(&bumpInferableTimestamp)), NULL);
    defineFunctionObject("HELP-COLLECT-INTENSIONAL-PARENTS", "(DEFUN HELP-COLLECT-INTENSIONAL-PARENTS ((DESCRIPTION DESCRIPTION) (PROPOSITION PROPOSITION) (COLLECTION LIST)))", ((cpp_function_code)(&helpCollectIntensionalParents)), NULL);
    defineFunctionObject("ALL-INTENSIONAL-PARENTS", "(DEFUN (ALL-INTENSIONAL-PARENTS (LIST OF DESCRIPTION)) ((SELF DESCRIPTION)))", ((cpp_function_code)(&allIntensionalParents)), NULL);
    defineFunctionObject("INFERABLE-THROUGH-BY-SOME-DESCENDANT?", "(DEFUN (INFERABLE-THROUGH-BY-SOME-DESCENDANT? BOOLEAN) ((SELF NAMED-DESCRIPTION) (THROUGHCHILD LOGIC-OBJECT) (ALREADYVISITEDLIST CONS)))", ((cpp_function_code)(&inferableThroughBySomeDescendantP)), NULL);
    defineFunctionObject("INFERABLE-WITH-CYCLE-CHECK?", "(DEFUN (INFERABLE-WITH-CYCLE-CHECK? BOOLEAN) ((SELF DESCRIPTION) (ALREADYVISITEDLIST CONS)))", ((cpp_function_code)(&inferableWithCycleCheckP)), NULL);
    defineFunctionObject("INFERABLE?", "(DEFUN (INFERABLE? BOOLEAN) ((SELF DESCRIPTION)) :INLINE INFERABLE-WITH-CYCLE-CHECK?)", ((cpp_function_code)(&inferableP)), NULL);
    defineFunctionObject("NON-INFERABLE?", "(DEFUN (NON-INFERABLE? BOOLEAN) ((SELF DESCRIPTION)) :INLINE INFERABLE?)", ((cpp_function_code)(&nonInferableP)), NULL);
    defineFunctionObject("CREATE-MARKER-STORAGE", "(DEFUN (CREATE-MARKER-STORAGE MARKER-TABLE) ((SUPPORTRECALL? BOOLEAN)) :DOCUMENTATION \"Return a new marker storage object, used to\nremember with objects have been 'marked'.  If 'supportRecall?'\nis set, then the iterator 'recall-marked-objects' can be invoked\non the new marker storage object.\")", ((cpp_function_code)(&createMarkerStorage)), NULL);
    defineMethodObject("(DEFMETHOD SET-MARKER ((SELF MARKER-TABLE) (OBJECT OBJECT)) :DOCUMENTATION \"Record membership of 'object' in the marker\nstorage object 'self'.\")", wrapMethodCode(((cpp_method_code)(&MarkerTable::setMarker))), NULL);
    defineMethodObject("(DEFMETHOD (TEST-MARKER? BOOLEAN) ((SELF MARKER-TABLE) (OBJECT OBJECT)) :DOCUMENTATION \"Return TRUE if 'object' is stored (marked) in 'self'.\")", wrapMethodCode(((cpp_method_code)(&MarkerTable::testMarkerP))), NULL);
    defineFunctionObject("TEST-SPECIAL-MARKER-TABLE?", "(DEFUN (TEST-SPECIAL-MARKER-TABLE? BOOLEAN) ((SELF OBJECT)) :DOCUMENTATION \"Return TRUE if the object 'self' is stored (marked)\nin the table pointed at by the special variable *specialMarkerTable*.\nDesigned for use by 'remove-if'.\")", ((cpp_function_code)(&testSpecialMarkerTableP)), NULL);
    defineMethodObject("(DEFMETHOD (RECALL-MARKED-OBJECTS LIST-ITERATOR) ((SELF MARKER-TABLE)) :DOCUMENTATION \"Return an iterator that generates all marked objects\nrecorded in 'self'.\")", wrapMethodCode(((cpp_method_code)(&MarkerTable::recallMarkedObjects))), NULL);
    defineFunctionObject("ALL-NAMED-DIRECT-SUPERDESCRIPTIONS", "(DEFUN (ALL-NAMED-DIRECT-SUPERDESCRIPTIONS (CONS OF NAMED-DESCRIPTION)) ((SELF DESCRIPTION) (REMOVEEQUIVALENTS? BOOLEAN)))", ((cpp_function_code)(&allNamedDirectSuperdescriptions)), NULL);
    defineFunctionObject("ALL-NAMED-DIRECT-SUBDESCRIPTIONS", "(DEFUN (ALL-NAMED-DIRECT-SUBDESCRIPTIONS (CONS OF NAMED-DESCRIPTION)) ((SELF DESCRIPTION)))", ((cpp_function_code)(&allNamedDirectSubdescriptions)), NULL);
    defineFunctionObject("ADD-ISA-LINK", "(DEFUN ADD-ISA-LINK ((INSTANCE LOGIC-OBJECT) (SUPERDESCRIPTION DESCRIPTION)))", ((cpp_function_code)(&addIsaLink)), NULL);
    defineFunctionObject("ADD-SUBSUMPTION-LINK", "(DEFUN ADD-SUBSUMPTION-LINK ((SUBDESCRIPTION DESCRIPTION) (SUPERDESCRIPTION DESCRIPTION)))", ((cpp_function_code)(&addSubsumptionLink)), NULL);
    defineFunctionObject("MOST-SPECIFIC-COLLECTIONS", "(DEFUN (MOST-SPECIFIC-COLLECTIONS (CONS OF LOGIC-OBJECT)) ((DESCRIPTIONS (CONS OF LOGIC-OBJECT))))", ((cpp_function_code)(&mostSpecificCollections)), NULL);
    defineFunctionObject("MOST-GENERAL-COLLECTIONS", "(DEFUN (MOST-GENERAL-COLLECTIONS (CONS OF LOGIC-OBJECT)) ((DESCRIPTIONS (CONS OF LOGIC-OBJECT))))", ((cpp_function_code)(&mostGeneralCollections)), NULL);
    defineFunctionObject("NAMED-COLLECTION?", "(DEFUN (NAMED-COLLECTION? BOOLEAN) ((SELF LOGIC-OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&namedCollectionP)), NULL);
    defineFunctionObject("MOST-SPECIFIC-NAMED-COLLECTIONS", "(DEFUN (MOST-SPECIFIC-NAMED-COLLECTIONS (CONS OF LOGIC-OBJECT)) ((DESCRIPTIONS (CONS OF LOGIC-OBJECT))) :PUBLIC? TRUE)", ((cpp_function_code)(&mostSpecificNamedCollections)), NULL);
    defineFunctionObject("MOST-SPECIFIC-NAMED-DESCRIPTIONS", "(DEFUN (MOST-SPECIFIC-NAMED-DESCRIPTIONS (CONS OF NAMED-DESCRIPTION)) ((DESCRIPTIONS (CONS OF LOGIC-OBJECT))))", ((cpp_function_code)(&mostSpecificNamedDescriptions)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT WORLD CLASSIFICATION-SESSION :PUBLIC? TRUE :DOCUMENTATION \"Points to a record that caches the distributed\nstate of descriptions participating in a classification session.\" :TYPE CLASSIFICATION-SESSION :ALLOCATION :DYNAMIC)");
    defineFunctionObject("GET-CLASSIFICATION-WORLD", "(DEFUN (GET-CLASSIFICATION-WORLD WORLD) () :PUBLIC? TRUE)", ((cpp_function_code)(&getClassificationWorld)), NULL);
    defineFunctionObject("GET-CLASSIFICATION-SESSION", "(DEFUN (GET-CLASSIFICATION-SESSION CLASSIFICATION-SESSION) ((INSTANCEORDESCRIPTION KEYWORD)) :PUBLIC? TRUE)", ((cpp_function_code)(&getClassificationSession)), NULL);
    defineFunctionObject("GET-CLASSIFICATION-CACHE", "(DEFUN (GET-CLASSIFICATION-CACHE CLASSIFICATION-CACHE) ((SELF OBJECT)))", ((cpp_function_code)(&getClassificationCache)), NULL);
    defineFunctionObject("TOGGLE-INFERABLE-DIRECT-SUBCOLLECTIONS-CACHING", "(DEFUN (TOGGLE-INFERABLE-DIRECT-SUBCOLLECTIONS-CACHING STRING) ())", ((cpp_function_code)(&toggleInferableDirectSubcollectionsCaching)), NULL);
    defineFunctionObject("ALL-INFERABLE-DIRECT-SUBCOLLECTIONS", "(DEFUN (ALL-INFERABLE-DIRECT-SUBCOLLECTIONS (LIST OF DESCRIPTION)) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&allInferableDirectSubcollections)), NULL);
    defineFunctionObject("FLUSH-INFERABLE-DIRECT-SUBDESCRIPTIONS-CACHE", "(DEFUN FLUSH-INFERABLE-DIRECT-SUBDESCRIPTIONS-CACHE ((IMPLIESPROPOSITION PROPOSITION)))", ((cpp_function_code)(&flushInferableDirectSubdescriptionsCache)), NULL);
    defineFunctionObject("CURRENT-CLASSIFICATION-TIME", "(DEFUN (CURRENT-CLASSIFICATION-TIME TIMESTAMP) ())", ((cpp_function_code)(&currentClassificationTime)), NULL);
    defineFunctionObject("BUMP-CLASSIFICATION-TIMECLOCK", "(DEFUN (BUMP-CLASSIFICATION-TIMECLOCK TIMESTAMP) ())", ((cpp_function_code)(&bumpClassificationTimeclock)), NULL);
    defineMethodObject("(DEFMETHOD (INTRODUCTION-TIMESTAMP TIMESTAMP) ((SELF LOGIC-OBJECT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&LogicObject::introductionTimestamp))), NULL);
    defineFunctionObject("INTRODUCE-INTO-CLASSIFICATION-SESSION", "(DEFUN INTRODUCE-INTO-CLASSIFICATION-SESSION ((SELF DESCRIPTION)))", ((cpp_function_code)(&introduceIntoClassificationSession)), NULL);
    defineFunctionObject("YOUNGEST-INTRODUCTION-TIMESTAMP", "(DEFUN (YOUNGEST-INTRODUCTION-TIMESTAMP INTEGER) ())", ((cpp_function_code)(&youngestIntroductionTimestamp)), NULL);
    defineFunctionObject("UPCLASSIFICATION-TIMESTAMP", "(DEFUN (UPCLASSIFICATION-TIMESTAMP INTEGER) ((SELF OBJECT)))", ((cpp_function_code)(&upclassificationTimestamp)), NULL);
    defineFunctionObject("DOWNCLASSIFICATION-TIMESTAMP", "(DEFUN (DOWNCLASSIFICATION-TIMESTAMP INTEGER) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&downclassificationTimestamp)), NULL);
    defineFunctionObject("REFRESH-UPCLASSIFICATION-TIMESTAMP", "(DEFUN REFRESH-UPCLASSIFICATION-TIMESTAMP ((SELF OBJECT)))", ((cpp_function_code)(&refreshUpclassificationTimestamp)), NULL);
    defineFunctionObject("REFRESH-DOWNCLASSIFICATION-TIMESTAMP", "(DEFUN REFRESH-DOWNCLASSIFICATION-TIMESTAMP ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&refreshDownclassificationTimestamp)), NULL);
    defineFunctionObject("FLUSH-CLASSIFICATION-SESSIONS", "(DEFUN FLUSH-CLASSIFICATION-SESSIONS ())", ((cpp_function_code)(&flushClassificationSessions)), NULL);
    defineFunctionObject("UPCLASSIFIED?", "(DEFUN (UPCLASSIFIED? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&upclassifiedP)), NULL);
    defineFunctionObject("UPCLASSIFIED-LATER-THAN?", "(DEFUN (UPCLASSIFIED-LATER-THAN? BOOLEAN) ((SELF LOGIC-OBJECT) (OTHER LOGIC-OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&upclassifiedLaterThanP)), NULL);
    defineFunctionObject("DOWNCLASSIFIED?", "(DEFUN (DOWNCLASSIFIED? BOOLEAN) ((SELF LOGIC-OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&downclassifiedP)), NULL);
    defineFunctionObject("MARK-UNMARKED-SUPERRELATIONS", "(DEFUN MARK-UNMARKED-SUPERRELATIONS ((DESCRIPTION DESCRIPTION) (SELFISBELOWTABLE MARKER-TABLE)))", ((cpp_function_code)(&markUnmarkedSuperrelations)), NULL);
    defineFunctionObject("APPLY-SUBSUMPTION-TEST?", "(DEFUN (APPLY-SUBSUMPTION-TEST? BOOLEAN) ((SUBSUMPTIONTEST FUNCTION-CODE) (SELF LOGIC-OBJECT) (SUPER LOGIC-OBJECT)))", ((cpp_function_code)(&applySubsumptionTestP)), NULL);
    defineFunctionObject("HELP-COLLECT-PARENTS-BELOW?", "(DEFUN (HELP-COLLECT-PARENTS-BELOW? BOOLEAN) ((SELF LOGIC-OBJECT) (SUPER DESCRIPTION) (NEWPARENTDESCRIPTIONS (LIST OF DESCRIPTION)) (ALREADYVISITEDTABLE MARKER-TABLE) (SELFISBELOWTABLE MARKER-TABLE) (SUBSUMPTIONTEST FUNCTION-CODE)))", ((cpp_function_code)(&helpCollectParentsBelowP)), NULL);
    defineFunctionObject("COLLECT-SUBSUMING-PARENTS-BELOW", "(DEFUN COLLECT-SUBSUMING-PARENTS-BELOW ((SELF LOGIC-OBJECT) (SUPER DESCRIPTION) (NEWPARENTDESCRIPTIONS (LIST OF DESCRIPTION)) (ALREADYVISITEDTABLE MARKER-TABLE) (SELFISBELOWTABLE MARKER-TABLE) (SUBSUMPTIONTEST FUNCTION-CODE)))", ((cpp_function_code)(&collectSubsumingParentsBelow)), NULL);
    defineFunctionObject("ALL-ANCESTORS-OF-PARENTS", "(DEFUN (ALL-ANCESTORS-OF-PARENTS (ITERATOR OF LOGIC-OBJECT)) ((SUPERS (CONS OF LOGIC-OBJECT))))", ((cpp_function_code)(&allAncestorsOfParents)), NULL);
    defineFunctionObject("ALL-ANCESTOR-COLLECTIONS", "(DEFUN (ALL-ANCESTOR-COLLECTIONS (ITERATOR OF LOGIC-OBJECT)) ((SELF OBJECT) (INSTANCEORDESCRIPTION KEYWORD)))", ((cpp_function_code)(&allAncestorCollections)), NULL);
    defineFunctionObject("HELP-UPCLASSIFY-ONE-ENTITY", "(DEFUN HELP-UPCLASSIFY-ONE-ENTITY ((SELF LOGIC-OBJECT) (INSTANCEORDESCRIPTION KEYWORD)))", ((cpp_function_code)(&helpUpclassifyOneEntity)), NULL);
    defineFunctionObject("UPCLASSIFY-ONE-INSTANCE", "(DEFUN UPCLASSIFY-ONE-INSTANCE ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&upclassifyOneInstance)), NULL);
    defineFunctionObject("UPCLASSIFY-ONE-DESCRIPTION", "(DEFUN UPCLASSIFY-ONE-DESCRIPTION ((SELF LOGIC-OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&upclassifyOneDescription)), NULL);
    defineFunctionObject("HELP-DOWNCLASSIFY-ONE-DESCRIPTION", "(DEFUN HELP-DOWNCLASSIFY-ONE-DESCRIPTION ((NODE LOGIC-OBJECT) (SELF LOGIC-OBJECT) (NECESSARYANCESTORS (CONS OF LOGIC-OBJECT)) (ALREADYVISITEDTABLE MARKER-TABLE)))", ((cpp_function_code)(&helpDownclassifyOneDescription)), NULL);
    defineFunctionObject("COLLECTION-WITH-FEWEST-CHILDREN", "(DEFUN (COLLECTION-WITH-FEWEST-CHILDREN LOGIC-OBJECT) ((COLLECTIONS (CONS OF LOGIC-OBJECT))))", ((cpp_function_code)(&collectionWithFewestChildren)), NULL);
    defineFunctionObject("CHOOSE-BEST-DOWNCLASSIFIED-PARENT", "(DEFUN (CHOOSE-BEST-DOWNCLASSIFIED-PARENT LOGIC-OBJECT) ((PARENTS (CONS OF LOGIC-OBJECT))))", ((cpp_function_code)(&chooseBestDownclassifiedParent)), NULL);
    defineFunctionObject("DOWNCLASSIFY-ONE-DESCRIPTION", "(DEFUN DOWNCLASSIFY-ONE-DESCRIPTION ((SELF LOGIC-OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&downclassifyOneDescription)), NULL);
    defineMethodObject("(DEFMETHOD (VIRGIN? BOOLEAN) ((SELF DESCRIPTION)))", wrapMethodCode(((cpp_method_code)(&Description::virginP))), NULL);
    defineFunctionObject("EVAPORATE-VIRGIN", "(DEFUN EVAPORATE-VIRGIN ((SELF DESCRIPTION)))", ((cpp_function_code)(&evaporateVirgin)), NULL);
    defineFunctionObject("FIND-DIRECT-SUPERS-AND-SUBS", "(DEFUN (FIND-DIRECT-SUPERS-AND-SUBS (CONS OF DESCRIPTION) (CONS OF DESCRIPTION) (CONS OF DESCRIPTION)) ((SELF DESCRIPTION) (ONLYSUPERS? BOOLEAN)) :DOCUMENTATION \"Classify 'self' and return three values, its direct\nsupers, direct subs, and a list of equivalent descriptions.\nSetting 'supersOnly?' may speed up the computation (perhaps by a lot).\nIf 'description' is nameless and has no dependent propositions, then\nit is automatically removed from the hierarchy after classification.\" :PUBLIC? TRUE)", ((cpp_function_code)(&findDirectSupersAndSubs)), NULL);
    defineFunctionObject("FIND-DIRECT-SUPERS-OF-INSTANCE", "(DEFUN (FIND-DIRECT-SUPERS-OF-INSTANCE (CONS OF LOGIC-OBJECT)) ((SELF OBJECT)) :DOCUMENTATION \"Classify 'self' and return a list of most specific \nnamed descriptions among all descriptions that it satisfies.\" :PUBLIC? TRUE)", ((cpp_function_code)(&findDirectSupersOfInstance)), NULL);
    defineFunctionObject("UPCLASSIFY-NAMED-DESCRIPTIONS", "(DEFUN UPCLASSIFY-NAMED-DESCRIPTIONS ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Classify named descriptions local to 'module' and inherited\nby 'module'.  If 'local?', don't classify inherited descriptions.  If\n'module' is NULL, classify descriptions in all modules.\")", ((cpp_function_code)(&upclassifyNamedDescriptions)), NULL);
    defineFunctionObject("CLASSIFY-RELATIONS", "(DEFUN CLASSIFY-RELATIONS (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Classify relations visible in the module defined by the :module option (which\ndefaults to the current module).  If :module was explicitly specified as NULL,\nclassify relations in all modules.  If `:local?' is specified as TRUE only classify\nrelations that belong to the specified module but not any modules it inherits.  For\nbackwards compatibility, this command also supports the old <module> <local?>\narguments specified without keywords.\n\nConceptually, the classifier operates by comparing each concept or relation\nwith all other concepts/relations, searching for a proof that a\nsubsumption relation exists between each pair. Whenever a new subsumption\nrelation is discovered, the classifier adds an `implication' link between\nmembers of the pair, thereby augmenting the structure of the\nconcept or relation hierarchy. The implemented classification algorithm is\nrelatively efficient -- it works hard at limiting the number of concepts\n" "or relations that need to be checked for possible subsumption\nrelationships.\n\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&classifyRelations)), ((cpp_function_code)(&classifyRelationsEvaluatorWrapper)));
  }
}

void startupClassify() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupClassify1();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("MARKER-TABLE", "(DEFCLASS MARKER-TABLE (STANDARD-OBJECT) :DOCUMENTATION \"Used to record (mark) a set of objects.\nCan be optimized for testing only, or also for recall.\" :SLOTS ((TEST-TABLE :TYPE HASH-TABLE) (RECALL-TABLE :TYPE LIST) (SUPPORTS-RECALL? :TYPE BOOLEAN)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newMarkerTable));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessMarkerTableSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("CLASSIFICATION-CACHE", "(DEFCLASS CLASSIFICATION-CACHE (STANDARD-OBJECT) :DOCUMENTATION \"Records various kinds of data about a description\nduring a classification session.\" :SLOTS ((INFERABLE-DIRECT-SUBDESCRIPTIONS :TYPE (LIST OF DESCRIPTION)) (CACHE-UPCLASSIFICATION-TIMESTAMP :TYPE INTEGER :INITIALLY -1) (CACHE-DOWNCLASSIFICATION-TIMESTAMP :TYPE INTEGER :INITIALLY -1) (INTRODUCTION-TIMESTAMP :TYPE INTEGER :INITIALLY 0)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newClassificationCache));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessClassificationCacheSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("CLASSIFICATION-SESSION", "(DEFCLASS CLASSIFICATION-SESSION (STANDARD-OBJECT) :SLOTS ((CLASSIFICATION-WORLD :TYPE WORLD) (CLASSIFICATION-CACHE-TABLE :TYPE (HASH-TABLE OF OBJECT CLASSIFICATION-CACHE) :ALLOCATION :EMBEDDED) (CLASSIFICATION-TIMECLOCK :TYPE INTEGER :INITIALLY 0) (INTRODUCTION-TIMESTAMP-STACK :TYPE (LIST OF INTEGER-WRAPPER) :INITIALLY (LIST 0)) (EVERYTHING-CLASSIFIED? :TYPE BOOLEAN) (LAST-CACHE-TABLE-KEY :TYPE LOGIC-OBJECT) (LAST-CACHE-TABLE-VALUE :TYPE CLASSIFICATION-CACHE)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newClassificationSession));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessClassificationSessionSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupClassify2();
      defineFunctionObject("LIST-UNCLASSIFIED-RELATIONS", "(DEFUN (LIST-UNCLASSIFIED-RELATIONS (CONS OF NAMED-DESCRIPTION)) (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Collect all named description in the module defined by the :module option (which defaults\nto the current module) that were not (or will not be) classified due to their lack of\nnon-inferable/primitive ancestor relations.  If :module was explicitly specified as NULL,\nlook in all currently defined modules.  If `:local?' is specified as TRUE only look\nin the specified module but not any modules it inherits.  For backwards compatibility,\nthis command also supports the old <module> <local?> arguments specified without keywords.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&listUnclassifiedRelations)), ((cpp_function_code)(&listUnclassifiedRelationsEvaluatorWrapper)));
      defineFunctionObject("UPCLASSIFY-INSTANCES", "(DEFUN UPCLASSIFY-INSTANCES ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Classify instances local to 'module' and inherited\nby 'module'.  If 'local?', don't classify inherited descriptions.  If\n'module' is NULL, classify descriptions in all modules.\")", ((cpp_function_code)(&upclassifyInstances)), NULL);
      defineFunctionObject("CLASSIFY-INSTANCES", "(DEFUN CLASSIFY-INSTANCES (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Classify instances visible in the module defined by the :module option (which\ndefaults to the current module).  If :module was explicitly specified as NULL,\nclassify instances in all modules.  If `:local?' is specified as TRUE only classify\ninstances that belong to the specified module but not any modules it inherits.  For\nbackwards compatibility, this command also supports the old <module> <local?>\narguments specified without keywords.\n\nConceptually, the classifier operates by comparing each instance with all\nconcepts in the hierarchy, searching for a proof for each pairing indicating\nthat the instance belongs to the concept.  Whenever a new `is-a' relation is\ndiscovered, the classifier adds an `is-a' link between the instance and the\nconcept, thereby recording an additional fact about the instance.  The\nimplemented classification algorithm is relatively efficient -- it works hard at\nlimiting the number of concepts or relatio" "ns that need to be checked for\npossible is-a relationships.\n\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&classifyInstances)), ((cpp_function_code)(&classifyInstancesEvaluatorWrapper)));
      defineFunctionObject("LIST-UNCLASSIFIED-INSTANCES", "(DEFUN (LIST-UNCLASSIFIED-INSTANCES (CONS OF LOGIC-OBJECT)) (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Collect all instances in the module defined by the :module option (which defaults\nto the current module) that were not (or will not be) classified due to their lack of\nnon-inferable/primitive type assertions.  If :module was explicitly specified as NULL,\nlook in all currently defined modules.  If `:local?' is specified as TRUE only look\nin the specified module but not any modules it inherits.  For backwards compatibility,\nthis command also supports the old <module> <local?> arguments specified without keywords.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&listUnclassifiedInstances)), ((cpp_function_code)(&listUnclassifiedInstancesEvaluatorWrapper)));
      defineFunctionObject("UPCLASSIFY-ALL-DESCRIPTIONS", "(DEFUN UPCLASSIFY-ALL-DESCRIPTIONS () :DOCUMENTATION \"Classify all named descriptions.\")", ((cpp_function_code)(&upclassifyAllDescriptions)), NULL);
      defineFunctionObject("UPCLASSIFY-ALL-INSTANCES", "(DEFUN UPCLASSIFY-ALL-INSTANCES () :DOCUMENTATION \"Classify all named instances.\")", ((cpp_function_code)(&upclassifyAllInstances)), NULL);
      defineFunctionObject("ALL-EQUIVALENT-COLLECTIONS", "(DEFUN (ALL-EQUIVALENT-COLLECTIONS (CONS OF LOGIC-OBJECT)) ((SELF LOGIC-OBJECT) (REFLEXIVE? BOOLEAN)) :PUBLIC? TRUE)", ((cpp_function_code)(&allEquivalentCollections)), NULL);
      defineFunctionObject("ALL-CYCLES", "(DEFUN (ALL-CYCLES (CONS OF CONS)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Return a list of lists of descriptions that are\nprovably co-extensional.\")", ((cpp_function_code)(&allCycles)), NULL);
      defineFunctionObject("STARTUP-CLASSIFY", "(DEFUN STARTUP-CLASSIFY () :PUBLIC? TRUE)", ((cpp_function_code)(&startupClassify)), NULL);
      { MethodSlot* function = lookupFunction(SYM_CLASSIFY_LOGIC_STARTUP_CLASSIFY);

        setDynamicSlotValue(function->dynamicSlots, SYM_CLASSIFY_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupClassify"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFSPECIAL *SPECIALMARKERTABLE* MARKER-TABLE :DOCUMENTATION \"Special variable that points to the marker table \nreferenced by the function 'test-special-marker-table?'.\")", &oSPECIALMARKERTABLEo);
      defineGlobalVariableObject("(DEFSPECIAL *FINDSUPERSANDSUBSDESCRIPTION* DESCRIPTION NULL :DOCUMENTATION \"Points to a possibly unnamed description being\ntemporarily classified.\")", &oFINDSUPERSANDSUBSDESCRIPTIONo);
      defineGlobalVariableObject("(DEFSPECIAL *CLASSIFICATIONSESSION* CLASSIFICATION-SESSION NULL :PUBLIC? TRUE :DOCUMENTATION \"Points to state of on-going classification session.\")", &oCLASSIFICATIONSESSIONo);
      defineGlobalVariableObject("(DEFGLOBAL *CACHE-INFERABLE-SUBCOLLECTIONS?* BOOLEAN TRUE :DOCUMENTATION \"If TRUE, prevents caching of computations of\nall inferable subcollections of a collection.\")", &oCACHE_INFERABLE_SUBCOLLECTIONSpo);
      defineGlobalVariableObject("(DEFSPECIAL *CLASSIFY-FROM-NON-INFERABLE-PARENTS-ONLY?* BOOLEAN TRUE :DOCUMENTATION \"If true (the default) only consider those relations (or instances) for\nclassification that have at least one non-inferable parent (or type).  This\ncan greatly reduce the classification effort.  To find entities that were\nleft unclassified due to this optimization use `list-unclassified-relations'\nor `list-unclassified-instances'.\" :PUBLIC? TRUE)", &oCLASSIFY_FROM_NON_INFERABLE_PARENTS_ONLYpo);
    }
  }
}

Keyword* KWD_CLASSIFY_IMPLIES_PROPOSITION_UPDATE = NULL;

Keyword* KWD_CLASSIFY_PREDICATE = NULL;

Keyword* KWD_CLASSIFY_FUNCTION = NULL;

Keyword* KWD_CLASSIFY_ISA = NULL;

Keyword* KWD_CLASSIFY_AND = NULL;

Keyword* KWD_CLASSIFY_EXISTS = NULL;

Surrogate* SGT_CLASSIFY_LOGIC_NAMED_DESCRIPTION = NULL;

Keyword* KWD_CLASSIFY_BACKWARD = NULL;

Symbol* SYM_CLASSIFY_LOGIC_FORWARD_ONLYp = NULL;

Surrogate* SGT_CLASSIFY_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_CLASSIFY_STELLA_THING = NULL;

Surrogate* SGT_CLASSIFY_LOGIC_F_INFERABLE_WITH_CYCLE_CHECKp_MEMO_TABLE_000 = NULL;

Surrogate* SGT_CLASSIFY_LOGIC_MARKER_TABLE = NULL;

Symbol* SYM_CLASSIFY_LOGIC_TEST_TABLE = NULL;

Symbol* SYM_CLASSIFY_LOGIC_RECALL_TABLE = NULL;

Symbol* SYM_CLASSIFY_LOGIC_SUPPORTS_RECALLp = NULL;

Symbol* SYM_CLASSIFY_LOGIC_SUBSUMPTION_LINKp = NULL;

Keyword* KWD_CLASSIFY_CLASSIFIER_INFERENCES = NULL;

Surrogate* SGT_CLASSIFY_LOGIC_CLASSIFICATION_CACHE = NULL;

Symbol* SYM_CLASSIFY_LOGIC_INFERABLE_DIRECT_SUBDESCRIPTIONS = NULL;

Symbol* SYM_CLASSIFY_LOGIC_CACHE_UPCLASSIFICATION_TIMESTAMP = NULL;

Symbol* SYM_CLASSIFY_LOGIC_CACHE_DOWNCLASSIFICATION_TIMESTAMP = NULL;

Symbol* SYM_CLASSIFY_LOGIC_INTRODUCTION_TIMESTAMP = NULL;

Surrogate* SGT_CLASSIFY_LOGIC_CLASSIFICATION_SESSION = NULL;

Symbol* SYM_CLASSIFY_LOGIC_CLASSIFICATION_WORLD = NULL;

Symbol* SYM_CLASSIFY_LOGIC_CLASSIFICATION_CACHE_TABLE = NULL;

Symbol* SYM_CLASSIFY_LOGIC_CLASSIFICATION_TIMECLOCK = NULL;

Symbol* SYM_CLASSIFY_LOGIC_INTRODUCTION_TIMESTAMP_STACK = NULL;

Symbol* SYM_CLASSIFY_LOGIC_EVERYTHING_CLASSIFIEDp = NULL;

Symbol* SYM_CLASSIFY_LOGIC_LAST_CACHE_TABLE_KEY = NULL;

Symbol* SYM_CLASSIFY_LOGIC_LAST_CACHE_TABLE_VALUE = NULL;

Keyword* KWD_CLASSIFY_DESCRIPTION = NULL;

Keyword* KWD_CLASSIFY_META = NULL;

Keyword* KWD_CLASSIFY_INSTANCE = NULL;

Keyword* KWD_CLASSIFY_TMS = NULL;

Symbol* SYM_CLASSIFY_LOGIC_CLASSIFICATION_SESSION = NULL;

Symbol* SYM_CLASSIFY_LOGIC_META_INFERENCE_CACHE = NULL;

Keyword* KWD_CLASSIFY_JUST_IN_TIME = NULL;

Keyword* KWD_CLASSIFY_CLASSIFIER = NULL;

Keyword* KWD_CLASSIFY_CLASSIFIER_PROFILE = NULL;

Keyword* KWD_CLASSIFY_UPCLASSIFY = NULL;

Keyword* KWD_CLASSIFY_DOWNCLASSIFY = NULL;

Symbol* SYM_CLASSIFY_LOGIC_SUBRELATION_LINKp = NULL;

Keyword* KWD_CLASSIFY_ASSERT_TRUE = NULL;

Keyword* KWD_CLASSIFY_MODULE = NULL;

Keyword* KWD_CLASSIFY_LOCALp = NULL;

Surrogate* SGT_CLASSIFY_STELLA_MODULE = NULL;

Surrogate* SGT_CLASSIFY_STELLA_BOOLEAN = NULL;

Symbol* SYM_CLASSIFY_LOGIC_STARTUP_CLASSIFY = NULL;

Symbol* SYM_CLASSIFY_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
