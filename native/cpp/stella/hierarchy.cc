//  -*- Mode: C++ -*-

// hierarchy.cc

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
| The Original Code is the STELLA Programming Language.                      |
|                                                                            |
| The Initial Developer of the Original Code is                              |
| UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
| 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
|                                                                            |
| Portions created by the Initial Developer are Copyright (C) 1996-2023      |
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
+---------------------------- END LICENSE BLOCK -----------------------------+
*/

#include "stella/stella-system.hh"

namespace stella {

Surrogate* Object::primaryType() {
  // Returns the primary type of `self'.
  // Gets defined automatically for every non-abstract subclass of OBJECT.
  { Object* self = this;

    return (NULL);
  }
}

Module* Object::homeModule() {
  // Return the home module of `self'.
  { Object* self = this;

    return (NULL);
  }
}

boolean Object::deletedP() {
  // Default `deleted?' method which always returns FALSE.  Objects
  // that inherit DYNAMIC-SLOTS-MIXIN also inherit the dynamically-allocated slot
  // `deleted-object?' which is read/writable with specializations of this method.
  { Object* self = this;

    return (false);
  }
}

void Object::incrementReferenceCount() {
  { Object* self = this;

  }
}

void Object::decrementReferenceCount() {
  { Object* self = this;

  }
}

void Object::printObject(std::ostream* stream) {
  { Object* self = this;

    *(stream) << "|i|" << self->primaryType();
  }
}

std::ostream& operator << (std::ostream& stream, Object* self) {
  if (!((boolean)(self))) {
    stream << "!NULL!";
  }
  else {
    self->printObject(&stream);
  }
  return (stream);
}

void ReferenceCountObject::incrementReferenceCount() {
  { ReferenceCountObject* self = this;

    self->referenceCount = self->referenceCount + 1;
  }
}

void ReferenceCountObject::decrementReferenceCount() {
  { ReferenceCountObject* self = this;

    self->referenceCount = self->referenceCount - 1;
  }
}

Object* accessReferenceCountObjectSlotValue(ReferenceCountObject* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_REFERENCE_COUNT) {
    if (setvalueP) {
      self->referenceCount = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->referenceCount);
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

Module* ContextSensitiveObject::homeModule() {
  { ContextSensitiveObject* self = this;

    { Context* context = self->homeContext;

      if (((boolean)(context))) {
        return (context->baseModule);
      }
      else {
        return (NULL);
      }
    }
  }
}

BooleanWrapper* ActiveObject::badP_reader() {
  { ActiveObject* self = this;

    { BooleanWrapper* answer = ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_BADp, NULL)));

      if (!((boolean)(answer))) {
        return (FALSE_WRAPPER);
      }
      else {
        return (answer);
      }
    }
  }
}

Object* accessActiveObjectSlotValue(ActiveObject* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (TRUE) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

boolean ActiveObject::deletedP() {
  { ActiveObject* self = this;

    { BooleanWrapper* deletedP = ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_DELETED_OBJECTp, NULL)));

      if (((boolean)(deletedP))) {
        return (coerceWrappedBooleanToBoolean(deletedP));
      }
      else {
        return (false);
      }
    }
  }
}

boolean ActiveObject::deletedPSetter(boolean value) {
  { ActiveObject* self = this;

    setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_DELETED_OBJECTp, (value ? TRUE_WRAPPER : FALSE_WRAPPER), NULL);
    return (value);
  }
}

boolean AbstractIterator::nextP() {
  { AbstractIterator* self = this;

    return (false);
  }
}

Object* accessAbstractIteratorSlotValue(AbstractIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_FIRST_ITERATIONp) {
    if (setvalueP) {
      self->firstIterationP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->firstIterationP ? TRUE_WRAPPER : FALSE_WRAPPER);
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

Object* accessIteratorSlotValue(Iterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_VALUE) {
    if (setvalueP) {
      self->value = value;
    }
    else {
      value = self->value;
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

ConsIterator* newConsIterator() {
  { ConsIterator* self = NULL;

    self = new ConsIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->consIteratorCursor = NULL;
    return (self);
  }
}

void ConsIterator::free() {
  { ConsIterator* self = this;

    if (terminateConsIteratorP(self)) {
      unmake(self);
    }
  }
}

Surrogate* ConsIterator::primaryType() {
  { ConsIterator* self = this;

    return (SGT_HIERARCHY_STELLA_CONS_ITERATOR);
  }
}

Object* accessConsIteratorSlotValue(ConsIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_CONS_ITERATOR_CURSOR) {
    if (setvalueP) {
      self->consIteratorCursor = ((Cons*)(value));
    }
    else {
      value = self->consIteratorCursor;
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

ListIterator* newListIterator() {
  { ListIterator* self = NULL;

    self = new ListIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->listIteratorCollection = NULL;
    self->listIteratorCursor = NULL;
    return (self);
  }
}

void ListIterator::free() {
  { ListIterator* self = this;

    if (terminateListIteratorP(self)) {
      unmake(self);
    }
  }
}

Surrogate* ListIterator::primaryType() {
  { ListIterator* self = this;

    return (SGT_HIERARCHY_STELLA_LIST_ITERATOR);
  }
}

Object* accessListIteratorSlotValue(ListIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_LIST_ITERATOR_CURSOR) {
    if (setvalueP) {
      self->listIteratorCursor = ((Cons*)(value));
    }
    else {
      value = self->listIteratorCursor;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_LIST_ITERATOR_COLLECTION) {
    if (setvalueP) {
      self->listIteratorCollection = ((List*)(value));
    }
    else {
      value = self->listIteratorCollection;
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

DestructiveListIterator* newDestructiveListIterator() {
  { DestructiveListIterator* self = NULL;

    self = new DestructiveListIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->listIteratorCursor = NULL;
    self->theConsList = NIL;
    return (self);
  }
}

void DestructiveListIterator::free() {
  { DestructiveListIterator* self = this;

    if (terminateDestructiveListIteratorP(self)) {
      unmake(self);
    }
  }
}

Surrogate* DestructiveListIterator::primaryType() {
  { DestructiveListIterator* self = this;

    return (SGT_HIERARCHY_STELLA_DESTRUCTIVE_LIST_ITERATOR);
  }
}

Object* accessDestructiveListIteratorSlotValue(DestructiveListIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_THE_CONS_LIST) {
    if (setvalueP) {
      self->theConsList = ((Cons*)(value));
    }
    else {
      value = self->theConsList;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_LIST_ITERATOR_CURSOR) {
    if (setvalueP) {
      self->listIteratorCursor = ((Cons*)(value));
    }
    else {
      value = self->listIteratorCursor;
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

AllPurposeIterator* newAllPurposeIterator() {
  { AllPurposeIterator* self = NULL;

    self = new AllPurposeIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->iteratorSecondInteger = NULL_INTEGER;
    self->iteratorInteger = NULL_INTEGER;
    self->iteratorSecondObject = NULL;
    self->iteratorObject = NULL;
    self->iteratorConsList = NULL;
    self->iteratorNestedIterator = NULL;
    self->iteratorEmptyCode = NULL;
    self->iteratorFilterCode = NULL;
    self->iteratorNextCode = NULL;
    self->key = NULL;
    return (self);
  }
}

void AllPurposeIterator::free() {
  { AllPurposeIterator* self = this;

    if (self->terminateAllPurposeIteratorP()) {
      unmake(self);
    }
  }
}

Surrogate* AllPurposeIterator::primaryType() {
  { AllPurposeIterator* self = this;

    return (SGT_HIERARCHY_STELLA_ALL_PURPOSE_ITERATOR);
  }
}

Object* accessAllPurposeIteratorSlotValue(AllPurposeIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_KEY) {
    if (setvalueP) {
      self->key = value;
    }
    else {
      value = self->key;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_ITERATOR_NEXT_CODE) {
    if (setvalueP) {
      self->iteratorNextCode = ((FunctionCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFunctionCode(self->iteratorNextCode);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_ITERATOR_FILTER_CODE) {
    if (setvalueP) {
      self->iteratorFilterCode = ((FunctionCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFunctionCode(self->iteratorFilterCode);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_ITERATOR_EMPTY_CODE) {
    if (setvalueP) {
      self->iteratorEmptyCode = ((FunctionCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFunctionCode(self->iteratorEmptyCode);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_ITERATOR_NESTED_ITERATOR) {
    if (setvalueP) {
      self->iteratorNestedIterator = ((Iterator*)(value));
    }
    else {
      value = self->iteratorNestedIterator;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_ITERATOR_CONS_LIST) {
    if (setvalueP) {
      self->iteratorConsList = ((Cons*)(value));
    }
    else {
      value = self->iteratorConsList;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_ITERATOR_OBJECT) {
    if (setvalueP) {
      self->iteratorObject = value;
    }
    else {
      value = self->iteratorObject;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_ITERATOR_SECOND_OBJECT) {
    if (setvalueP) {
      self->iteratorSecondObject = value;
    }
    else {
      value = self->iteratorSecondObject;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_ITERATOR_INTEGER) {
    if (setvalueP) {
      self->iteratorInteger = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->iteratorInteger);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_ITERATOR_SECOND_INTEGER) {
    if (setvalueP) {
      self->iteratorSecondInteger = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->iteratorSecondInteger);
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

TypesToClassesIterator* newTypesToClassesIterator(Cons* iteratorCursor) {
  { TypesToClassesIterator* self = NULL;

    self = new TypesToClassesIterator();
    self->iteratorCursor = iteratorCursor;
    self->firstIterationP = true;
    self->value = NULL;
    return (self);
  }
}

Surrogate* TypesToClassesIterator::primaryType() {
  { TypesToClassesIterator* self = this;

    return (SGT_HIERARCHY_STELLA_TYPES_TO_CLASSES_ITERATOR);
  }
}

boolean TypesToClassesIterator::nextP() {
  { TypesToClassesIterator* self = this;

    if (self->firstIterationP) {
      self->firstIterationP = false;
    }
    else {
      self->iteratorCursor = self->iteratorCursor->rest;
    }
    if (!(self->iteratorCursor == NIL)) {
      self->value = ((Class*)(((Surrogate*)(self->iteratorCursor->value))->surrogateValue));
      return (true);
    }
    else {
      return (false);
    }
  }
}

Object* accessTypesToClassesIteratorSlotValue(TypesToClassesIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_ITERATOR_CURSOR) {
    if (setvalueP) {
      self->iteratorCursor = ((Cons*)(value));
    }
    else {
      value = self->iteratorCursor;
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

Object* DictionaryIterator::valueSetter(Object* value) {
  { DictionaryIterator* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "DICTIONARY-ITERATOR.value-setter not implemented on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Object* DictionaryIterator::keySetter(Object* key) {
  { DictionaryIterator* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "DICTIONARY-ITERATOR.key-setter not implemented on " << "`" << self << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Object* accessDictionaryIteratorSlotValue(DictionaryIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_KEY) {
    if (setvalueP) {
      self->keySetter(value);
    }
    else {
      value = self->key;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_VALUE) {
    if (setvalueP) {
      self->valueSetter(value);
    }
    else {
      value = self->value;
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

PropertyListIterator* newPropertyListIterator() {
  { PropertyListIterator* self = NULL;

    self = new PropertyListIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->key = NULL;
    self->plistIteratorCollection = NULL;
    self->plistIteratorCursor = NULL;
    return (self);
  }
}

Surrogate* PropertyListIterator::primaryType() {
  { PropertyListIterator* self = this;

    return (SGT_HIERARCHY_STELLA_PROPERTY_LIST_ITERATOR);
  }
}

Object* accessPropertyListIteratorSlotValue(PropertyListIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_PLIST_ITERATOR_CURSOR) {
    if (setvalueP) {
      self->plistIteratorCursor = ((Cons*)(value));
    }
    else {
      value = self->plistIteratorCursor;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_PLIST_ITERATOR_COLLECTION) {
    if (setvalueP) {
      self->plistIteratorCollection = ((PropertyList*)(value));
    }
    else {
      value = self->plistIteratorCollection;
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

KvListIterator* newKvListIterator() {
  { KvListIterator* self = NULL;

    self = new KvListIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->key = NULL;
    self->kvListIteratorCursor = NULL;
    self->theKvList = NULL;
    return (self);
  }
}

Surrogate* KvListIterator::primaryType() {
  { KvListIterator* self = this;

    return (SGT_HIERARCHY_STELLA_KV_LIST_ITERATOR);
  }
}

Object* accessKvListIteratorSlotValue(KvListIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_THE_KV_LIST) {
    if (setvalueP) {
      self->theKvList = ((KeyValueList*)(value));
    }
    else {
      value = self->theKvList;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_KV_LIST_ITERATOR_CURSOR) {
    if (setvalueP) {
      self->kvListIteratorCursor = ((KvCons*)(value));
    }
    else {
      value = self->kvListIteratorCursor;
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

IntegerIntervalIterator* newIntegerIntervalIterator(int lowerBound, int upperBound) {
  { IntegerIntervalIterator* self = NULL;

    self = new IntegerIntervalIterator();
    self->lowerBound = lowerBound;
    self->upperBound = upperBound;
    self->firstIterationP = true;
    self->value = NULL_INTEGER;
    self->intervalCursor = NULL_INTEGER;
    self->initializeIntegerIntervalIterator();
    return (self);
  }
}

Surrogate* IntegerIntervalIterator::primaryType() {
  { IntegerIntervalIterator* self = this;

    return (SGT_HIERARCHY_STELLA_INTEGER_INTERVAL_ITERATOR);
  }
}

Object* accessIntegerIntervalIteratorSlotValue(IntegerIntervalIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_INTERVAL_CURSOR) {
    if (setvalueP) {
      self->intervalCursor = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->intervalCursor);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_LOWER_BOUND) {
    if (setvalueP) {
      self->lowerBound = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->lowerBound);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_UPPER_BOUND) {
    if (setvalueP) {
      self->upperBound = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->upperBound);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_VALUE) {
    if (setvalueP) {
      self->value = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->value);
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

ReverseIntegerIntervalIterator* newReverseIntegerIntervalIterator(int lowerBound, int upperBound) {
  { ReverseIntegerIntervalIterator* self = NULL;

    self = new ReverseIntegerIntervalIterator();
    self->lowerBound = lowerBound;
    self->upperBound = upperBound;
    self->firstIterationP = true;
    self->value = NULL_INTEGER;
    self->intervalCursor = NULL_INTEGER;
    initializeReverseIntegerIntervalIterator(self);
    return (self);
  }
}

Surrogate* ReverseIntegerIntervalIterator::primaryType() {
  { ReverseIntegerIntervalIterator* self = this;

    return (SGT_HIERARCHY_STELLA_REVERSE_INTEGER_INTERVAL_ITERATOR);
  }
}

Object* accessReverseIntegerIntervalIteratorSlotValue(ReverseIntegerIntervalIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_INTERVAL_CURSOR) {
    if (setvalueP) {
      self->intervalCursor = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->intervalCursor);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_LOWER_BOUND) {
    if (setvalueP) {
      self->lowerBound = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->lowerBound);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_UPPER_BOUND) {
    if (setvalueP) {
      self->upperBound = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->upperBound);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_VALUE) {
    if (setvalueP) {
      self->value = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->value);
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

StringIterator* newStringIterator() {
  { StringIterator* self = NULL;

    self = new StringIterator();
    self->firstIterationP = true;
    self->value = NULL_CHARACTER;
    self->end = NULL_INTEGER;
    self->cursor = NULL_INTEGER;
    self->theString = NULL;
    return (self);
  }
}

Surrogate* StringIterator::primaryType() {
  { StringIterator* self = this;

    return (SGT_HIERARCHY_STELLA_STRING_ITERATOR);
  }
}

Object* accessStringIteratorSlotValue(StringIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_THE_STRING) {
    if (setvalueP) {
      self->theString = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->theString);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CURSOR) {
    if (setvalueP) {
      self->cursor = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->cursor);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_END) {
    if (setvalueP) {
      self->end = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->end);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_VALUE) {
    if (setvalueP) {
      self->value = ((CharacterWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapCharacter(self->value);
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

AbstractIterator* AbstractCollection::allocateIterator() {
  { AbstractCollection* self = this;

    return (NULL);
  }
}

int AbstractCollection::length() {
  { AbstractCollection* self = this;

    return (NULL_INTEGER);
  }
}

AbstractIterator* Collection::allocateIterator() {
  { Collection* self = this;

    return (NULL);
  }
}

int Collection::length() {
  { Collection* self = this;

    return (NULL_INTEGER);
  }
}

void Collection::insert(Object* value) {
  { Collection* self = this;

    value = value;
    return;
  }
}

AbstractCollection* Collection::remove(Object* value) {
  { Collection* self = this;

    value = value;
    return (NULL);
  }
}

AbstractIterator* Sequence::allocateIterator() {
  { Sequence* self = this;

    return (NULL);
  }
}

int Sequence::length() {
  { Sequence* sequence = this;

    return (NULL_INTEGER);
  }
}

List* newList() {
  { List* self = NULL;

    self = new List();
    self->theConsList = NIL;
    return (self);
  }
}

Surrogate* List::primaryType() {
  { List* self = this;

    return (SGT_HIERARCHY_STELLA_LIST);
  }
}

Object* accessListSlotValue(List* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_THE_CONS_LIST) {
    if (setvalueP) {
      self->theConsList = ((Cons*)(value));
    }
    else {
      value = self->theConsList;
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

void List::printObject(std::ostream* stream) {
  { List* self = this;

    {
      *(stream) << "|l|";
      printCons(self->theConsList, stream, "(", ")");
    }
  }
}

Set* newSet() {
  { Set* self = NULL;

    self = new Set();
    self->theConsList = NIL;
    return (self);
  }
}

Surrogate* Set::primaryType() {
  { Set* self = this;

    return (SGT_HIERARCHY_STELLA_SET);
  }
}

void Set::printObject(std::ostream* stream) {
  { Set* self = this;

    {
      *(stream) << "|s|";
      printCons(self->theConsList, stream, "(", ")");
    }
  }
}

ClassExtension* newClassExtension() {
  { ClassExtension* self = NULL;

    self = new ClassExtension();
    self->theConsList = NIL;
    return (self);
  }
}

Surrogate* ClassExtension::primaryType() {
  { ClassExtension* self = this;

    return (SGT_HIERARCHY_STELLA_CLASS_EXTENSION);
  }
}

Cons* newCons() {
  { Cons* self = NULL;

    self = new Cons();
    self->rest = NIL;
    self->value = NULL;
    return (self);
  }
}

Surrogate* Cons::primaryType() {
  { Cons* self = this;

    return (SGT_HIERARCHY_STELLA_CONS);
  }
}

Object* accessConsSlotValue(Cons* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_VALUE) {
    if (setvalueP) {
      self->value = value;
    }
    else {
      value = self->value;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_REST) {
    if (setvalueP) {
      self->rest = ((Cons*)(value));
    }
    else {
      value = self->rest;
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

void Cons::printObject(std::ostream* stream) {
  { Cons* self = this;

    printCons(self, stream, "(", ")");
  }
}

AbstractIterator* AbstractDictionary::allocateIterator() {
  { AbstractDictionary* self = this;

    return (NULL);
  }
}

AbstractIterator* Dictionary::allocateIterator() {
  { Dictionary* self = this;

    return (NULL);
  }
}

Object* Dictionary::lookup(Object* key) {
  { Dictionary* self = this;

    key = key;
    return (NULL);
  }
}

void Dictionary::insertAt(Object* key, Object* value) {
  { Dictionary* self = this;

    {
      key = key;
      value = value;
    }
    return;
  }
}

PropertyList* newPropertyList() {
  { PropertyList* self = NULL;

    self = new PropertyList();
    self->thePlist = NIL;
    return (self);
  }
}

Surrogate* PropertyList::primaryType() {
  { PropertyList* self = this;

    return (SGT_HIERARCHY_STELLA_PROPERTY_LIST);
  }
}

Object* accessPropertyListSlotValue(PropertyList* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_THE_PLIST) {
    if (setvalueP) {
      self->thePlist = ((Cons*)(value));
    }
    else {
      value = self->thePlist;
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

void PropertyList::printObject(std::ostream* stream) {
  { PropertyList* self = this;

    {
      *(stream) << "|pl|";
      printCons(self->thePlist, stream, "(", ")");
    }
  }
}

KvCons* newKvCons() {
  { KvCons* self = NULL;

    self = new KvCons();
    self->rest = NULL;
    self->value = NULL;
    self->key = NULL;
    return (self);
  }
}

Surrogate* KvCons::primaryType() {
  { KvCons* self = this;

    return (SGT_HIERARCHY_STELLA_KV_CONS);
  }
}

Object* accessKvConsSlotValue(KvCons* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_KEY) {
    if (setvalueP) {
      self->key = value;
    }
    else {
      value = self->key;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_VALUE) {
    if (setvalueP) {
      self->value = value;
    }
    else {
      value = self->value;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_REST) {
    if (setvalueP) {
      self->rest = ((KvCons*)(value));
    }
    else {
      value = self->rest;
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

void KvCons::printObject(std::ostream* stream) {
  { KvCons* self = this;

    *(stream) << "<" << self->key << "," << self->value << ">";
  }
}

KeyValueList* newKeyValueList() {
  { KeyValueList* self = NULL;

    self = new KeyValueList();
    self->theKvList = NULL;
    return (self);
  }
}

Surrogate* KeyValueList::primaryType() {
  { KeyValueList* self = this;

    return (SGT_HIERARCHY_STELLA_KEY_VALUE_LIST);
  }
}

Object* accessKeyValueListSlotValue(KeyValueList* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_THE_KV_LIST) {
    if (setvalueP) {
      self->theKvList = ((KvCons*)(value));
    }
    else {
      value = self->theKvList;
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

void KeyValueList::printObject(std::ostream* stream) {
  { KeyValueList* self = this;

    printKeyValueList(self, stream);
  }
}

RecycleList* newRecycleList() {
  { RecycleList* self = NULL;

    self = new RecycleList();
    self->itemSize = NULL_INTEGER;
    self->currentLength = 0;
    self->unusedItems = NULL;
    self->allItems = NULL;
    self->listOfRecycledItems = makeNonRecycledList();
    self->recycledItems = NULL;
    self->recycleListOf = NULL;
    return (self);
  }
}

Surrogate* RecycleList::primaryType() {
  { RecycleList* self = this;

    return (SGT_HIERARCHY_STELLA_RECYCLE_LIST);
  }
}

Object* accessRecycleListSlotValue(RecycleList* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_RECYCLE_LIST_OF) {
    if (setvalueP) {
      self->recycleListOf = ((Surrogate*)(value));
    }
    else {
      value = self->recycleListOf;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_RECYCLED_ITEMS) {
    if (setvalueP) {
      self->recycledItems = value;
    }
    else {
      value = self->recycledItems;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_LIST_OF_RECYCLED_ITEMS) {
    if (setvalueP) {
      self->listOfRecycledItems = ((List*)(value));
    }
    else {
      value = self->listOfRecycledItems;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_ALL_ITEMS) {
    if (setvalueP) {
      self->allItems = value;
    }
    else {
      value = self->allItems;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_UNUSED_ITEMS) {
    if (setvalueP) {
      self->unusedItems = value;
    }
    else {
      value = self->unusedItems;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CURRENT_LENGTH) {
    if (setvalueP) {
      self->currentLength = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->currentLength);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_ITEM_SIZE) {
    if (setvalueP) {
      self->itemSize = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->itemSize);
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

void RecycleList::printObject(std::ostream* stream) {
  { RecycleList* self = this;

    if (((boolean)(self->recycleListOf))) {
      *(stream) << "|i|[RECYCLE-LIST OF " << self->currentLength << " " << self->recycleListOf << "'s]";
    }
    else {
      *(stream) << "|i|@RECYCLE-LIST";
    }
  }
}

Object* accessAbstractHashTableSlotValue(AbstractHashTable* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_THE_STELLA_HASH_TABLE) {
    if (setvalueP) {
      self->theStellaHashTable = ((StellaHashTable*)(value));
    }
    else {
      value = self->theStellaHashTable;
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

HashTable* newHashTable() {
  { HashTable* self = NULL;

    self = new HashTable();
    self->theStellaHashTable = NULL;
    self->theHashTable = NULL;
    self->initializeHashTable();
    return (self);
  }
}

Surrogate* HashTable::primaryType() {
  { HashTable* self = this;

    return (SGT_HIERARCHY_STELLA_HASH_TABLE);
  }
}

IntegerHashTable* newIntegerHashTable() {
  { IntegerHashTable* self = NULL;

    self = new IntegerHashTable();
    self->theStellaHashTable = NULL;
    self->theHashTable = NULL;
    self->initializeHashTable();
    return (self);
  }
}

Surrogate* IntegerHashTable::primaryType() {
  { IntegerHashTable* self = this;

    return (SGT_HIERARCHY_STELLA_INTEGER_HASH_TABLE);
  }
}

FloatHashTable* newFloatHashTable() {
  { FloatHashTable* self = NULL;

    self = new FloatHashTable();
    self->theStellaHashTable = NULL;
    self->theHashTable = NULL;
    self->initializeHashTable();
    return (self);
  }
}

Surrogate* FloatHashTable::primaryType() {
  { FloatHashTable* self = this;

    return (SGT_HIERARCHY_STELLA_FLOAT_HASH_TABLE);
  }
}

StringHashTable* newStringHashTable() {
  { StringHashTable* self = NULL;

    self = new StringHashTable();
    self->theStellaHashTable = NULL;
    self->theHashTable = NULL;
    self->initializeHashTable();
    return (self);
  }
}

Surrogate* StringHashTable::primaryType() {
  { StringHashTable* self = this;

    return (SGT_HIERARCHY_STELLA_STRING_HASH_TABLE);
  }
}

StringToIntegerHashTable* newStringToIntegerHashTable() {
  { StringToIntegerHashTable* self = NULL;

    self = new StringToIntegerHashTable();
    self->theStellaHashTable = NULL;
    self->theHashTable = NULL;
    self->initializeHashTable();
    return (self);
  }
}

Surrogate* StringToIntegerHashTable::primaryType() {
  { StringToIntegerHashTable* self = this;

    return (SGT_HIERARCHY_STELLA_STRING_TO_INTEGER_HASH_TABLE);
  }
}

Vector* newVector(int arraySize) {
  { Vector* self = NULL;

    self = new Vector();
    self->arraySize = arraySize;
    self->theArray = NULL;
    self->initializeVector();
    return (self);
  }
}

Surrogate* Vector::primaryType() {
  { Vector* self = this;

    return (SGT_HIERARCHY_STELLA_VECTOR);
  }
}

Object* accessVectorSlotValue(Vector* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_ARRAY_SIZE) {
    if (setvalueP) {
      self->arraySize = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->arraySize);
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

void Vector::printObject(std::ostream* stream) {
  { Vector* self = this;

    self->printVector(stream);
  }
}

ExtensibleVector* newExtensibleVector(int arraySize) {
  { ExtensibleVector* self = NULL;

    self = new ExtensibleVector();
    self->arraySize = arraySize;
    self->theArray = NULL;
    self->initializeVector();
    return (self);
  }
}

Surrogate* ExtensibleVector::primaryType() {
  { ExtensibleVector* self = this;

    return (SGT_HIERARCHY_STELLA_EXTENSIBLE_VECTOR);
  }
}

ExtensibleSymbolArray* newExtensibleSymbolArray(int arraySize) {
  { ExtensibleSymbolArray* self = NULL;

    self = new ExtensibleSymbolArray();
    self->arraySize = arraySize;
    self->theArray = NULL;
    self->potentialFreeSymbolOffset = 0;
    self->topSymbolOffset = -1;
    self->initializeVector();
    return (self);
  }
}

Surrogate* ExtensibleSymbolArray::primaryType() {
  { ExtensibleSymbolArray* self = this;

    return (SGT_HIERARCHY_STELLA_EXTENSIBLE_SYMBOL_ARRAY);
  }
}

Object* accessExtensibleSymbolArraySlotValue(ExtensibleSymbolArray* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_TOP_SYMBOL_OFFSET) {
    if (setvalueP) {
      self->topSymbolOffset = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->topSymbolOffset);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_POTENTIAL_FREE_SYMBOL_OFFSET) {
    if (setvalueP) {
      self->potentialFreeSymbolOffset = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->potentialFreeSymbolOffset);
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

VectorSequence* newVectorSequence(int arraySize) {
  { VectorSequence* self = NULL;

    self = new VectorSequence();
    self->arraySize = arraySize;
    self->theArray = NULL;
    self->sequenceLength = 0;
    self->initializeVector();
    return (self);
  }
}

Surrogate* VectorSequence::primaryType() {
  { VectorSequence* self = this;

    return (SGT_HIERARCHY_STELLA_VECTOR_SEQUENCE);
  }
}

Object* accessVectorSequenceSlotValue(VectorSequence* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_SEQUENCE_LENGTH) {
    if (setvalueP) {
      self->sequenceLength = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->sequenceLength);
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

CustomVectorSequence* newCustomVectorSequence(int arraySize) {
  { CustomVectorSequence* self = NULL;

    self = new CustomVectorSequence();
    self->arraySize = arraySize;
    self->theArray = NULL;
    self->sequenceLength = 0;
    self->resizeFactor = 2.0;
    self->initializeVector();
    return (self);
  }
}

Surrogate* CustomVectorSequence::primaryType() {
  { CustomVectorSequence* self = this;

    return (SGT_HIERARCHY_STELLA_CUSTOM_VECTOR_SEQUENCE);
  }
}

Object* accessCustomVectorSequenceSlotValue(CustomVectorSequence* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_RESIZE_FACTOR) {
    if (setvalueP) {
      self->resizeFactor = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->resizeFactor);
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

BooleanVector* newBooleanVector(int arraySize) {
  { BooleanVector* self = NULL;

    self = new BooleanVector();
    self->arraySize = arraySize;
    self->theArray = NULL;
    self->initializeVector();
    return (self);
  }
}

Surrogate* BooleanVector::primaryType() {
  { BooleanVector* self = this;

    return (SGT_HIERARCHY_STELLA_BOOLEAN_VECTOR);
  }
}

IntegerVector* newIntegerVector(int arraySize) {
  { IntegerVector* self = NULL;

    self = new IntegerVector();
    self->arraySize = arraySize;
    self->theArray = NULL;
    self->initializeVector();
    return (self);
  }
}

Surrogate* IntegerVector::primaryType() {
  { IntegerVector* self = this;

    return (SGT_HIERARCHY_STELLA_INTEGER_VECTOR);
  }
}

ActiveList* newActiveList() {
  { ActiveList* self = NULL;

    self = new ActiveList();
    self->ownerInstance = NULL;
    self->activeSlot = NULL;
    self->theConsList = NIL;
    return (self);
  }
}

Surrogate* ActiveList::primaryType() {
  { ActiveList* self = this;

    return (SGT_HIERARCHY_STELLA_ACTIVE_LIST);
  }
}

ActiveSet* newActiveSet() {
  { ActiveSet* self = NULL;

    self = new ActiveSet();
    self->ownerInstance = NULL;
    self->activeSlot = NULL;
    self->theConsList = NIL;
    return (self);
  }
}

Surrogate* ActiveSet::primaryType() {
  { ActiveSet* self = this;

    return (SGT_HIERARCHY_STELLA_ACTIVE_SET);
  }
}

Demon* newDemon() {
  { Demon* self = NULL;

    self = new Demon();
    self->demonInheritP = false;
    self->demonAllP = false;
    self->demonGuardP = false;
    self->demonDocumentation = NULL;
    self->demonMethod = NULL;
    self->demonCode = NULL;
    self->demonSlotRefs = newList();
    self->demonClassRefs = newList();
    self->demonAction = NULL;
    self->demonName = NULL;
    return (self);
  }
}

Surrogate* Demon::primaryType() {
  { Demon* self = this;

    return (SGT_HIERARCHY_STELLA_DEMON);
  }
}

Object* accessDemonSlotValue(Demon* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_DEMON_NAME) {
    if (setvalueP) {
      self->demonName = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->demonName);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DEMON_ACTION) {
    if (setvalueP) {
      self->demonAction = ((Keyword*)(value));
    }
    else {
      value = self->demonAction;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DEMON_CLASS_REFS) {
    if (setvalueP) {
      self->demonClassRefs = ((List*)(value));
    }
    else {
      value = self->demonClassRefs;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DEMON_SLOT_REFS) {
    if (setvalueP) {
      self->demonSlotRefs = ((List*)(value));
    }
    else {
      value = self->demonSlotRefs;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DEMON_CODE) {
    if (setvalueP) {
      self->demonCode = ((FunctionCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFunctionCode(self->demonCode);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DEMON_METHOD) {
    if (setvalueP) {
      self->demonMethod = ((MethodSlot*)(value));
    }
    else {
      value = self->demonMethod;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DEMON_DOCUMENTATION) {
    if (setvalueP) {
      self->demonDocumentation = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->demonDocumentation);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DEMON_GUARDp) {
    if (setvalueP) {
      self->demonGuardP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->demonGuardP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DEMON_ALLp) {
    if (setvalueP) {
      self->demonAllP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->demonAllP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DEMON_INHERITp) {
    if (setvalueP) {
      self->demonInheritP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->demonInheritP ? TRUE_WRAPPER : FALSE_WRAPPER);
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

KeywordKeyValueList* newKeywordKeyValueList() {
  { KeywordKeyValueList* self = NULL;

    self = new KeywordKeyValueList();
    self->theKvList = NULL;
    return (self);
  }
}

Surrogate* KeywordKeyValueList::primaryType() {
  { KeywordKeyValueList* self = this;

    return (SGT_HIERARCHY_STELLA_KEYWORD_KEY_VALUE_LIST);
  }
}

Object* accessGeneralizedSymbolSlotValue(GeneralizedSymbol* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_SYMBOL_NAME) {
    if (setvalueP) {
      self->symbolName = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->symbolName);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SYMBOL_ID) {
    if (setvalueP) {
      self->symbolId = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->symbolId);
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

Symbol* newSymbol(const char* symbolName) {
  { Symbol* self = NULL;

    self = new Symbol();
    self->symbolName = symbolName;
    self->homeContext = oCONTEXTo;
    self->symbolId = NULL_INTEGER;
    self->symbolValueAndPlist = NIL;
    self->symbolSlotOffset = NULL_INTEGER;
    return (self);
  }
}

Surrogate* Symbol::primaryType() {
  { Symbol* self = this;

    return (SGT_HIERARCHY_STELLA_SYMBOL);
  }
}

Object* accessSymbolSlotValue(Symbol* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_SYMBOL_SLOT_OFFSET) {
    if (setvalueP) {
      self->symbolSlotOffset = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->symbolSlotOffset);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SYMBOL_VALUE_AND_PLIST) {
    if (setvalueP) {
      self->symbolValueAndPlist = ((Cons*)(value));
    }
    else {
      value = self->symbolValueAndPlist;
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

void Symbol::printObject(std::ostream* stream) {
  { Symbol* self = this;

    printSymbol(self, stream);
  }
}

Surrogate* newSurrogate(const char* symbolName) {
  { Surrogate* self = NULL;

    self = new Surrogate();
    self->symbolName = symbolName;
    self->homeContext = oCONTEXTo;
    self->symbolId = NULL_INTEGER;
    self->surrogateValue = NULL;
    return (self);
  }
}

Surrogate* Surrogate::primaryType() {
  { Surrogate* self = this;

    return (SGT_HIERARCHY_STELLA_SURROGATE);
  }
}

Object* accessSurrogateSlotValue(Surrogate* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_SURROGATE_VALUE) {
    if (setvalueP) {
      self->surrogateValue = value;
    }
    else {
      value = self->surrogateValue;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_TYPE_CLASS) {
    if (setvalueP) {
      self->surrogateValue = ((Class*)(value));
    }
    else {
      value = ((Class*)(self->surrogateValue));
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOTREF_SLOT) {
    if (setvalueP) {
      self->surrogateValue = ((Slot*)(value));
    }
    else {
      value = ((Slot*)(self->surrogateValue));
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

void Surrogate::printObject(std::ostream* stream) {
  { Surrogate* self = this;

    printSurrogate(self, stream);
  }
}

Keyword* newKeyword(const char* symbolName) {
  { Keyword* self = NULL;

    self = new Keyword();
    self->symbolName = symbolName;
    self->homeContext = oCONTEXTo;
    self->symbolId = NULL_INTEGER;
    return (self);
  }
}

Surrogate* Keyword::primaryType() {
  { Keyword* self = this;

    return (SGT_HIERARCHY_STELLA_KEYWORD);
  }
}

void Keyword::printObject(std::ostream* stream) {
  { Keyword* self = this;

    printKeyword(self, stream);
  }
}

TransientSymbol* newTransientSymbol(const char* symbolName) {
  { TransientSymbol* self = NULL;

    self = new TransientSymbol();
    self->symbolName = symbolName;
    self->homeContext = oCONTEXTo;
    self->symbolId = NULL_INTEGER;
    self->symbolValueAndPlist = NIL;
    self->symbolSlotOffset = NULL_INTEGER;
    return (self);
  }
}

Surrogate* TransientSymbol::primaryType() {
  { TransientSymbol* self = this;

    return (SGT_HIERARCHY_STELLA_TRANSIENT_SYMBOL);
  }
}

boolean TransientSymbol::transientP_reader() {
  { TransientSymbol* self = this;

    return (oHARDWIRED_TRANSIENTp_ON_TRANSIENT_MIXINo);
  }
}

List* MappableObject::projectsOnto_reader() {
  { MappableObject* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_PROJECTS_ONTO, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

List* MappableObject::projectedFrom_reader() {
  { MappableObject* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_PROJECTED_FROM, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

BooleanWrapper* MappableObject::badP_reader() {
  { MappableObject* self = this;

    { BooleanWrapper* answer = ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_BADp, NULL)));

      if (!((boolean)(answer))) {
        return (FALSE_WRAPPER);
      }
      else {
        return (answer);
      }
    }
  }
}

Object* accessMappableObjectSlotValue(MappableObject* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_PROJECTS_ONTO) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_PROJECTS_ONTO, ((List*)(value)), NULL);
    }
    else {
      value = self->projectsOnto_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_PROJECTED_FROM) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_PROJECTED_FROM, ((List*)(value)), NULL);
    }
    else {
      value = self->projectedFrom_reader();
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

boolean MappableObject::deletedP() {
  { MappableObject* self = this;

    { BooleanWrapper* deletedP = ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_DELETED_OBJECTp, NULL)));

      if (((boolean)(deletedP))) {
        return (coerceWrappedBooleanToBoolean(deletedP));
      }
      else {
        return (false);
      }
    }
  }
}

boolean MappableObject::deletedPSetter(boolean value) {
  { MappableObject* self = this;

    setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_DELETED_OBJECTp, (value ? TRUE_WRAPPER : FALSE_WRAPPER), NULL);
    return (value);
  }
}

const char* Relation::name() {
  { Relation* self = this;

    return (NULL);
  }
}

Module* Relation::homeModule() {
  { Relation* self = this;

    return (NULL);
  }
}

int Relation::arity() {
  { Relation* self = this;

    return (NULL_INTEGER);
  }
}

boolean Relation::publicP() {
  { Relation* self = this;

    return (false);
  }
}

List* Relation::directSupers() {
  { Relation* self = this;

    return (NULL);
  }
}

List* Relation::allSupers() {
  { Relation* self = this;

    return (NULL);
  }
}

Iterator* Relation::slots() {
  { Relation* self = this;

    return (NULL);
  }
}

List* Relation::properties_reader() {
  { Relation* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_PROPERTIES, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

Object* accessRelationSlotValue(Relation* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_ABSTRACTp) {
    if (setvalueP) {
      self->abstractP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->abstractP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_PROPERTIES) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_PROPERTIES, ((List*)(value)), NULL);
    }
    else {
      value = self->properties_reader();
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

Class* newClass() {
  { Class* self = NULL;

    self = new Class();
    self->dynamicSlots = newKeyValueList();
    self->classTaxonomyNode = NULL;
    self->classMarkedP = false;
    self->classSlotAccessorCode = NULL;
    self->classConstructorCode = NULL;
    self->classStringifiedSource = NULL;
    self->classSlotsFinalizedP = false;
    self->classFinalizedP = false;
    self->classPublicP = true;
    self->clStructP = false;
    self->classCollectionP = false;
    self->mixinP = false;
    self->abstractP = false;
    self->classSlotAndMethodCache = NULL;
    self->classLocalSlots = NULL;
    self->classAllSlots = NULL;
    self->classAllSuperClasses = NIL;
    self->classDirectSubs = newList();
    self->classDirectSupers = newList();
    self->classType = NULL;
    return (self);
  }
}

Surrogate* Class::primaryType() {
  { Class* self = this;

    return (SGT_HIERARCHY_STELLA_CLASS);
  }
}

const char* Class::name() {
  { Class* self = this;

    return (self->classType->symbolName);
  }
}

Module* Class::homeModule() {
  { Class* self = this;

    return (((Module*)(self->classType->homeContext)));
  }
}

int Class::arity() {
  { Class* self = this;

    return (1);
  }
}

boolean Class::publicP() {
  { Class* self = this;

    return (self->classPublicP);
  }
}

boolean Class::activeP() {
  { Class* self = this;

    return ((((boolean)(((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_STORED_ACTIVEp, NULL))))) &&
        coerceWrappedBooleanToBoolean(((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_STORED_ACTIVEp, NULL))))) ||
        subtypeOfP(self->classType, SGT_HIERARCHY_STELLA_ACTIVE_OBJECT));
  }
}

Symbol* Class::creator() {
  { Class* self = this;

    return (((Symbol*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_CREATOR, NULL))));
  }
}

Symbol* Class::initializer() {
  { Class* self = this;

    { Class* cursor = self;
      Symbol* value = ((Symbol*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_INITIALIZER, NULL)));

      for (;;) {
        if (((boolean)(value))) {
          return (value);
        }
        cursor = ((Class*)(cursor->classAllSuperClasses->value));
        if (((boolean)(cursor))) {
          value = ((Symbol*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_INITIALIZER, NULL)));
        }
        else {
          return (NULL);
        }
      }
    }
  }
}

Symbol* Class::terminator() {
  { Class* self = this;

    { Class* cursor = self;
      Symbol* value = ((Symbol*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_TERMINATOR, NULL)));

      for (;;) {
        if (((boolean)(value))) {
          return (value);
        }
        cursor = ((Class*)(cursor->classAllSuperClasses->value));
        if (((boolean)(cursor))) {
          value = ((Symbol*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_TERMINATOR, NULL)));
        }
        else {
          return (NULL);
        }
      }
    }
  }
}

Symbol* Class::destructor() {
  { Class* self = this;

    return (((Symbol*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_DESTRUCTOR, NULL))));
  }
}

List* Class::requiredSlots() {
  // Returns a list of names of required slots for `self'.
  { Class* self = this;

    return (self->classRequiredSlotNames_reader());
  }
}

List* Class::parameters() {
  // Returns the list of parameters names of `self'.
  { Class* self = this;

    { Class* cursor = self;
      List* value = ((List*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_PARAMETERS, NULL)));

      for (;;) {
        if (((boolean)(value))) {
          return (value);
        }
        cursor = ((Class*)(cursor->classAllSuperClasses->value));
        if (((boolean)(cursor))) {
          value = ((List*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_PARAMETERS, NULL)));
        }
        else {
          return (NIL_LIST);
        }
      }
    }
  }
}

Object* Class::initialValue() {
  // Return an initial value for the class `self'.
  { Class* self = this;

    { Class* cursor = self;
      Object* value = dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_INITIAL_VALUE, NULL);

      for (;;) {
        if (((boolean)(value))) {
          return (value);
        }
        cursor = ((Class*)(cursor->classAllSuperClasses->value));
        if (((boolean)(cursor))) {
          value = dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_INITIAL_VALUE, NULL);
        }
        else {
          return (NULL);
        }
      }
    }
  }
}

ClassExtension* Class::extension() {
  // Return the nearest class extension that records instances
  // of the class `self'.
  { Class* self = this;

    { Class* cursor = self;
      ClassExtension* value = ((ClassExtension*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_EXTENSION, NULL)));

      for (;;) {
        if (((boolean)(value))) {
          return (value);
        }
        cursor = ((Class*)(cursor->classAllSuperClasses->value));
        if (((boolean)(cursor))) {
          value = ((ClassExtension*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_EXTENSION, NULL)));
        }
        else {
          return (NULL);
        }
      }
    }
  }
}

const char* Class::clNativeType() {
  { Class* self = this;

    return (((StringWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_CL_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue);
  }
}

const char* Class::cppNativeType() {
  { Class* self = this;

    return (((StringWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_CPP_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue);
  }
}

const char* Class::idlNativeType() {
  { Class* self = this;

    return (((StringWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_CPP_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue);
  }
}

const char* Class::javaNativeType() {
  { Class* self = this;

    { const char* nativetype = ((StringWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_JAVA_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue;

      if (nativetype != NULL) {
        return (substituteTemplateVariablesInString(nativetype, oJAVA_STELLA_PACKAGE_MAPPINGo));
      }
      else {
        return (NULL);
      }
    }
  }
}

int Class::classArity_reader() {
  { Class* self = this;

    return (oHARDWIRED_CLASS_ARITY_ON_CLASSo);
  }
}

List* Class::classClStructSlots_reader() {
  { Class* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_CL_STRUCT_SLOTS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

Keyword* Class::classRecycleMethod_reader() {
  { Class* self = this;

    { Keyword* answer = ((Keyword*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_RECYCLE_METHOD, NULL)));

      if (!((boolean)(answer))) {
        return (KWD_HIERARCHY_NONE);
      }
      else {
        return (answer);
      }
    }
  }
}

List* Class::classParameters_reader() {
  { Class* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_PARAMETERS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

List* Class::classRequiredSlotNames_reader() {
  { Class* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_REQUIRED_SLOT_NAMES, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

List* Class::classGuardConstructorDemons_reader() {
  { Class* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

List* Class::classConstructorDemons_reader() {
  { Class* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_CONSTRUCTOR_DEMONS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

List* Class::classGuardDestructorDemons_reader() {
  { Class* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

List* Class::classDestructorDemons_reader() {
  { Class* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_DESTRUCTOR_DEMONS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

List* Class::classKey_reader() {
  { Class* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_KEY, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

List* Class::classSynonyms_reader() {
  { Class* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_SYNONYMS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

Object* accessClassSlotValue(Class* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_CL_STRUCTp) {
    if (setvalueP) {
      self->clStructP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->clStructP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_MIXINp) {
    if (setvalueP) {
      self->mixinP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->mixinP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_TYPE) {
    if (setvalueP) {
      self->classType = ((Surrogate*)(value));
    }
    else {
      value = self->classType;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_ARITY) {
    value = wrapInteger(self->classArity_reader());
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_DIRECT_SUPERS) {
    if (setvalueP) {
      self->classDirectSupers = ((List*)(value));
    }
    else {
      value = self->classDirectSupers;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_DIRECT_SUBS) {
    if (setvalueP) {
      self->classDirectSubs = ((List*)(value));
    }
    else {
      value = self->classDirectSubs;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_ALL_SUPER_CLASSES) {
    if (setvalueP) {
      self->classAllSuperClasses = ((Cons*)(value));
    }
    else {
      value = self->classAllSuperClasses;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_ALL_SLOTS) {
    if (setvalueP) {
      self->classAllSlots = ((Cons*)(value));
    }
    else {
      value = self->classAllSlots;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_LOCAL_SLOTS) {
    if (setvalueP) {
      self->classLocalSlots = ((List*)(value));
    }
    else {
      value = self->classLocalSlots;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_SLOT_AND_METHOD_CACHE) {
    if (setvalueP) {
      self->classSlotAndMethodCache = ((Vector*)(value));
    }
    else {
      value = self->classSlotAndMethodCache;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_MIXINp) {
    if (setvalueP) {
      self->mixinP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->mixinP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_COLLECTIONp) {
    if (setvalueP) {
      self->classCollectionP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->classCollectionP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_CL_STRUCTp) {
    if (setvalueP) {
      self->clStructP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->clStructP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_CL_STRUCT_SLOTS) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_CL_STRUCT_SLOTS, ((List*)(value)), NULL);
    }
    else {
      value = self->classClStructSlots_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_PUBLICp) {
    if (setvalueP) {
      self->classPublicP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->classPublicP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_RECYCLE_METHOD) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_RECYCLE_METHOD, ((Keyword*)(value)), NULL);
    }
    else {
      value = self->classRecycleMethod_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_FINALIZEDp) {
    if (setvalueP) {
      self->classFinalizedP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->classFinalizedP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_SLOTS_FINALIZEDp) {
    if (setvalueP) {
      self->classSlotsFinalizedP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->classSlotsFinalizedP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_STRINGIFIED_SOURCE) {
    if (setvalueP) {
      self->classStringifiedSource = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->classStringifiedSource);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_PARAMETERS) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_PARAMETERS, ((List*)(value)), NULL);
    }
    else {
      value = self->classParameters_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_CONSTRUCTOR_CODE) {
    if (setvalueP) {
      self->classConstructorCode = ((FunctionCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFunctionCode(self->classConstructorCode);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_SLOT_ACCESSOR_CODE) {
    if (setvalueP) {
      self->classSlotAccessorCode = ((FunctionCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFunctionCode(self->classSlotAccessorCode);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_REQUIRED_SLOT_NAMES) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_REQUIRED_SLOT_NAMES, ((List*)(value)), NULL);
    }
    else {
      value = self->classRequiredSlotNames_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS, ((List*)(value)), NULL);
    }
    else {
      value = self->classGuardConstructorDemons_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_CONSTRUCTOR_DEMONS) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_CONSTRUCTOR_DEMONS, ((List*)(value)), NULL);
    }
    else {
      value = self->classConstructorDemons_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS, ((List*)(value)), NULL);
    }
    else {
      value = self->classGuardDestructorDemons_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_DESTRUCTOR_DEMONS) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_DESTRUCTOR_DEMONS, ((List*)(value)), NULL);
    }
    else {
      value = self->classDestructorDemons_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_KEY) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_KEY, ((List*)(value)), NULL);
    }
    else {
      value = self->classKey_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_SYNONYMS) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLASS_SYNONYMS, ((List*)(value)), NULL);
    }
    else {
      value = self->classSynonyms_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_MARKEDp) {
    if (setvalueP) {
      self->classMarkedP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->classMarkedP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLASS_TAXONOMY_NODE) {
    if (setvalueP) {
      self->classTaxonomyNode = ((TaxonomyNode*)(value));
    }
    else {
      value = self->classTaxonomyNode;
    }
  }
  else {
    if (slotname == SYM_HIERARCHY_STELLA_CLASS_DOCUMENTATION) {
      slotname = SYM_HIERARCHY_STELLA_DOCUMENTATION;
    }
    else if (slotname == SYM_HIERARCHY_STELLA_CLASS_PRINT_FORM) {
      slotname = SYM_HIERARCHY_STELLA_PRINT_FORM;
    }
    else {
    }
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

void Class::printObject(std::ostream* stream) {
  { Class* self = this;

    *(stream) << "|C|" << ((((boolean)(self->classType)) ? classSymbol(self)->relativeName(false) : "??"));
  }
}

Surrogate* PolymorphicRelation::owner() {
  { PolymorphicRelation* self = this;

    return (NULL);
  }
}

Symbol* PolymorphicRelation::renames() {
  { PolymorphicRelation* self = this;

    return (NULL);
  }
}

boolean PolymorphicRelation::activeP() {
  // True if `self' or a superslot of `self' is marked active.
  { PolymorphicRelation* self = this;

    { PolymorphicRelation* cursor = self;
      BooleanWrapper* value = ((BooleanWrapper*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_STORED_ACTIVEp, NULL)));

      for (;;) {
        if (((boolean)(value))) {
          return (coerceWrappedBooleanToBoolean(value));
        }
        cursor = cursor->slotDirectEquivalent;
        if (((boolean)(cursor))) {
          value = ((BooleanWrapper*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_STORED_ACTIVEp, NULL)));
        }
        else {
          return (false);
        }
      }
    }
  }
}

Object* accessPolymorphicRelationSlotValue(PolymorphicRelation* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_SLOT_DIRECT_EQUIVALENT) {
    if (setvalueP) {
      self->slotDirectEquivalent = ((Slot*)(value));
    }
    else {
      value = self->slotDirectEquivalent;
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

const char* Slot::name() {
  { Slot* self = this;

    return (self->slotName->symbolName);
  }
}

Surrogate* Slot::type() {
  // The type of a storage slot is its base type.
  { Slot* self = this;

    { Slot* cursor = self;
      Surrogate* value = cursor->slotBaseType;

      for (;;) {
        if (((boolean)(value))) {
          return (value);
        }
        cursor = cursor->slotDirectEquivalent;
        if (((boolean)(cursor))) {
          value = cursor->slotBaseType;
        }
        else {
          return (NULL);
        }
      }
    }
  }
}

StandardObject* Slot::typeSpecifier() {
  // If `self' has a complex type return its
  // type specifier, otherwise, return `type' of `self'.
  { Slot* self = this;

    { CompoundTypeSpecifier* tspec = ((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_TYPE_SPECIFIER, NULL)));

      return ((((boolean)(tspec)) ? ((StandardObject*)(tspec)) : ((StandardObject*)(self->type()))));
    }
  }
}

Surrogate* Slot::owner() {
  { Slot* self = this;

    return (self->slotOwner);
  }
}

Module* Slot::homeModule() {
  { Slot* self = this;

    { Module* module = ((Module*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_HOME_MODULE, NULL)));

      if (((boolean)(module))) {
        return (module);
      }
      else {
        return (((Module*)(self->slotName->homeContext)));
      }
    }
  }
}

Symbol* Slot::renames() {
  { Slot* self = this;

    return (((Symbol*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_RENAMES, NULL))));
  }
}

boolean Slot::collectionValuedP() {
  // True if slot values are collections.
  { Slot* self = this;

    return (subtypeOfP(self->slotBaseType, SGT_HIERARCHY_STELLA_COLLECTION));
  }
}

Keyword* Slot::closureAssumption() {
  { Slot* self = this;

    { Slot* cursor = self;
      Keyword* value = ((Keyword*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_CLOSURE_ASSUMPTION, NULL)));

      for (;;) {
        if (((boolean)(value))) {
          return (value);
        }
        cursor = cursor->slotDirectEquivalent;
        if (((boolean)(cursor))) {
          value = ((Keyword*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_CLOSURE_ASSUMPTION, NULL)));
        }
        else {
          return (NULL);
        }
      }
    }
  }
}

List* Slot::slotDirectSupers_reader() {
  { Slot* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_DIRECT_SUPERS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

List* Slot::slotDirectSubs_reader() {
  { Slot* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_DIRECT_SUBS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

Object* accessSlotSlotValue(Slot* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_SLOT_NAME) {
    if (setvalueP) {
      self->slotName = ((Symbol*)(value));
    }
    else {
      value = self->slotName;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_OWNER) {
    if (setvalueP) {
      self->slotOwner = ((Surrogate*)(value));
    }
    else {
      value = self->slotOwner;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_BASE_TYPE) {
    if (setvalueP) {
      self->slotBaseType = ((Surrogate*)(value));
    }
    else {
      value = self->slotBaseType;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_SLOTREF) {
    if (setvalueP) {
      self->slotSlotref = ((Surrogate*)(value));
    }
    else {
      value = self->slotSlotref;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_DIRECT_SUPERS) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_DIRECT_SUPERS, ((List*)(value)), NULL);
    }
    else {
      value = self->slotDirectSupers_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_DIRECT_SUBS) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_DIRECT_SUBS, ((List*)(value)), NULL);
    }
    else {
      value = self->slotDirectSubs_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_PUBLICp) {
    if (setvalueP) {
      self->slotPublicP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->slotPublicP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_RENAMEDp) {
    if (setvalueP) {
      self->slotRenamedP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->slotRenamedP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_EXTERNALp) {
    if (setvalueP) {
      self->slotExternalP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->slotExternalP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_MARKEDp) {
    if (setvalueP) {
      self->slotMarkedP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->slotMarkedP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else {
    if (slotname == SYM_HIERARCHY_STELLA_SLOT_DOCUMENTATION) {
      slotname = SYM_HIERARCHY_STELLA_DOCUMENTATION;
    }
    else {
    }
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

void Slot::printObject(std::ostream* stream) {
  { Slot* self = this;

    *(stream) << "|S|" << self->slotOwner->symbolName << "." << self->slotName->symbolName;
  }
}

StorageSlot* newStorageSlot() {
  { StorageSlot* self = NULL;

    self = new StorageSlot();
    self->dynamicSlots = newKeyValueList();
    self->abstractP = false;
    self->slotDirectEquivalent = NULL;
    self->slotMarkedP = false;
    self->slotExternalP = false;
    self->slotRenamedP = false;
    self->slotPublicP = true;
    self->slotSlotref = NULL;
    self->slotBaseType = NULL;
    self->slotOwner = NULL;
    self->slotName = NULL;
    self->slotContextSensitiveP = false;
    self->slotHardwiredP = false;
    self->slotReadOnlyP = false;
    self->slotComponentP = false;
    self->slotRequiredP = false;
    return (self);
  }
}

Surrogate* StorageSlot::primaryType() {
  { StorageSlot* self = this;

    return (SGT_HIERARCHY_STELLA_STORAGE_SLOT);
  }
}

Keyword* StorageSlot::allocation() {
  // Return the most specific :allocation facet, or
  // :instance if all inherited values are NULL.
  { StorageSlot* self = this;

    { StorageSlot* cursor = self;
      Keyword* value = ((Keyword*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_ALLOCATION, NULL)));

      for (;;) {
        if (((boolean)(value))) {
          return (value);
        }
        cursor = ((StorageSlot*)(cursor->slotDirectEquivalent));
        if (((boolean)(cursor))) {
          value = ((Keyword*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_ALLOCATION, NULL)));
        }
        else {
          return (KWD_HIERARCHY_INSTANCE);
        }
      }
    }
  }
}

Object* StorageSlot::defaultForm() {
  // Returns the current value of default expression when the
  // slot has not been assigned a value.
  { StorageSlot* self = this;

    { StorageSlot* cursor = self;
      Object* value = dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_DEFAULT_EXPRESSION, NULL);

      for (;;) {
        if (((boolean)(value))) {
          return (value);
        }
        cursor = ((StorageSlot*)(cursor->slotDirectEquivalent));
        if (((boolean)(cursor))) {
          value = dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_DEFAULT_EXPRESSION, NULL);
        }
        else {
          return (NULL);
        }
      }
    }
  }
}

boolean StorageSlot::requiredP() {
  // True if a value must be assigned to this slot at
  // creation time.
  { StorageSlot* self = this;

    { StorageSlot* cursor = self;
      boolean value = cursor->slotRequiredP;

      for (;;) {
        if (value) {
          return (value);
        }
        cursor = ((StorageSlot*)(cursor->slotDirectEquivalent));
        if (((boolean)(cursor))) {
          value = cursor->slotRequiredP;
        }
        else {
          return (false);
        }
      }
    }
  }
}

boolean StorageSlot::componentP() {
  // True if fillers of this slot are components of the
  // owner slot, and therefore should be deleted if the owner is deleted.
  { StorageSlot* self = this;

    { StorageSlot* cursor = self;
      boolean value = cursor->slotComponentP;

      for (;;) {
        if (value) {
          return (value);
        }
        cursor = ((StorageSlot*)(cursor->slotDirectEquivalent));
        if (((boolean)(cursor))) {
          value = cursor->slotComponentP;
        }
        else {
          return (false);
        }
      }
    }
  }
}

Symbol* StorageSlot::reader() {
  // Name of a method called to read the value of the slot
  // `self'.
  { StorageSlot* self = this;

    { StorageSlot* cursor = self;
      Symbol* value = ((Symbol*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_READER, NULL)));

      for (;;) {
        if (((boolean)(value))) {
          return (value);
        }
        cursor = ((StorageSlot*)(cursor->slotDirectEquivalent));
        if (((boolean)(cursor))) {
          value = ((Symbol*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_READER, NULL)));
        }
        else {
          return (NULL);
        }
      }
    }
  }
}

Symbol* StorageSlot::writer() {
  // Name of a method called to write the value of the slot
  // `self'.
  { StorageSlot* self = this;

    { StorageSlot* cursor = self;
      Symbol* value = ((Symbol*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_WRITER, NULL)));

      for (;;) {
        if (((boolean)(value))) {
          return (value);
        }
        cursor = ((StorageSlot*)(cursor->slotDirectEquivalent));
        if (((boolean)(cursor))) {
          value = ((Symbol*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_WRITER, NULL)));
        }
        else {
          return (NULL);
        }
      }
    }
  }
}

Keyword* StorageSlot::slotAllocation_reader() {
  { StorageSlot* self = this;

    { Keyword* answer = ((Keyword*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_ALLOCATION, NULL)));

      if (!((boolean)(answer))) {
        return (KWD_HIERARCHY_INSTANCE);
      }
      else {
        return (answer);
      }
    }
  }
}

List* StorageSlot::slotGuardDemons_reader() {
  { StorageSlot* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_GUARD_DEMONS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

List* StorageSlot::slotDemons_reader() {
  { StorageSlot* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_DEMONS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

Object* accessStorageSlotSlotValue(StorageSlot* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_SLOT_ALLOCATION) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_ALLOCATION, ((Keyword*)(value)), NULL);
    }
    else {
      value = self->slotAllocation_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_GUARD_DEMONS) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_GUARD_DEMONS, ((List*)(value)), NULL);
    }
    else {
      value = self->slotGuardDemons_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_DEMONS) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SLOT_DEMONS, ((List*)(value)), NULL);
    }
    else {
      value = self->slotDemons_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_REQUIREDp) {
    if (setvalueP) {
      self->slotRequiredP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->slotRequiredP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_COMPONENTp) {
    if (setvalueP) {
      self->slotComponentP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->slotComponentP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_READ_ONLYp) {
    if (setvalueP) {
      self->slotReadOnlyP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->slotReadOnlyP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_HARDWIREDp) {
    if (setvalueP) {
      self->slotHardwiredP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->slotHardwiredP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SLOT_CONTEXT_SENSITIVEp) {
    if (setvalueP) {
      self->slotContextSensitiveP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->slotContextSensitiveP ? TRUE_WRAPPER : FALSE_WRAPPER);
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

MethodSlot* newMethodSlot() {
  { MethodSlot* self = NULL;

    self = new MethodSlot();
    self->dynamicSlots = newKeyValueList();
    self->abstractP = false;
    self->slotDirectEquivalent = NULL;
    self->slotMarkedP = false;
    self->slotExternalP = false;
    self->slotRenamedP = false;
    self->slotPublicP = true;
    self->slotSlotref = NULL;
    self->slotBaseType = NULL;
    self->slotOwner = NULL;
    self->slotName = NULL;
    self->methodFunctionP = false;
    self->functionCode = NULL;
    self->methodCode = NULL;
    self->methodStringifiedSource = NULL;
    self->methodReturnTypeSpecifiers = NULL;
    self->methodParameterTypeSpecifiers = NULL;
    self->methodParameterNames = NULL;
    self->methodSetterP = false;
    return (self);
  }
}

Surrogate* MethodSlot::primaryType() {
  { MethodSlot* self = this;

    return (SGT_HIERARCHY_STELLA_METHOD_SLOT);
  }
}

boolean MethodSlot::setterP() {
  { MethodSlot* self = this;

    return (self->methodSetterP);
  }
}

List* MethodSlot::methodParameterNames_reader() {
  { MethodSlot* self = this;

    { List* answer = self->methodParameterNames;

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

List* MethodSlot::methodParameterTypeSpecifiers_reader() {
  { MethodSlot* self = this;

    { List* answer = self->methodParameterTypeSpecifiers;

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

List* MethodSlot::methodParameterDirections_reader() {
  { MethodSlot* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_METHOD_PARAMETER_DIRECTIONS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

List* MethodSlot::methodReturnTypeSpecifiers_reader() {
  { MethodSlot* self = this;

    { List* answer = self->methodReturnTypeSpecifiers;

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

List* MethodSlot::methodInlinedFunctions_reader() {
  { MethodSlot* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_METHOD_INLINED_FUNCTIONS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

boolean MethodSlot::methodEvaluateArgumentsP_reader() {
  { MethodSlot* self = this;

    return (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_METHOD_EVALUATE_ARGUMENTSp, TRUE_WRAPPER)))->wrapperValue);
  }
}

Object* accessMethodSlotSlotValue(MethodSlot* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_METHOD_SETTERp) {
    if (setvalueP) {
      self->methodSetterP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->methodSetterP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_METHOD_PARAMETER_NAMES) {
    if (setvalueP) {
      self->methodParameterNames = ((List*)(value));
    }
    else {
      value = self->methodParameterNames_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_METHOD_PARAMETER_TYPE_SPECIFIERS) {
    if (setvalueP) {
      self->methodParameterTypeSpecifiers = ((List*)(value));
    }
    else {
      value = self->methodParameterTypeSpecifiers_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_METHOD_PARAMETER_DIRECTIONS) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_METHOD_PARAMETER_DIRECTIONS, ((List*)(value)), NULL);
    }
    else {
      value = self->methodParameterDirections_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_METHOD_RETURN_TYPE_SPECIFIERS) {
    if (setvalueP) {
      self->methodReturnTypeSpecifiers = ((List*)(value));
    }
    else {
      value = self->methodReturnTypeSpecifiers_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_METHOD_STRINGIFIED_SOURCE) {
    if (setvalueP) {
      self->methodStringifiedSource = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->methodStringifiedSource);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_METHOD_CODE) {
    if (setvalueP) {
      self->methodCode = ((CodeWrapper*)(value));
    }
    else {
      value = self->methodCode;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_FUNCTION_CODE) {
    if (setvalueP) {
      self->functionCode = ((FunctionCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFunctionCode(self->functionCode);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_METHOD_FUNCTIONp) {
    if (setvalueP) {
      self->methodFunctionP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->methodFunctionP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_METHOD_INLINED_FUNCTIONS) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_METHOD_INLINED_FUNCTIONS, ((List*)(value)), NULL);
    }
    else {
      value = self->methodInlinedFunctions_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_METHOD_EVALUATE_ARGUMENTSp) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_METHOD_EVALUATE_ARGUMENTSp, (coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value))) ? TRUE_WRAPPER : FALSE_WRAPPER), FALSE_WRAPPER);
    }
    else {
      value = (self->methodEvaluateArgumentsP_reader() ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else {
    if (slotname == SYM_HIERARCHY_STELLA_METHOD_DOCUMENTATION) {
      slotname = SYM_HIERARCHY_STELLA_DOCUMENTATION;
    }
    else if (slotname == SYM_HIERARCHY_STELLA_METHOD_AUXILIARYp) {
      slotname = SYM_HIERARCHY_STELLA_SLOT_AUXILIARYp;
    }
    else if (slotname == SYM_HIERARCHY_STELLA_METHOD_STORAGE_SLOT) {
      slotname = SYM_HIERARCHY_STELLA_STORAGE_SLOT;
    }
    else {
    }
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

void MethodSlot::printObject(std::ostream* stream) {
  { MethodSlot* self = this;

    if (self->methodFunctionP) {
      *(stream) << "|F|" << self->slotName->symbolName;
    }
    else {
      *(stream) << "|M|" << self->slotOwner->symbolName << "." << self->slotName->symbolName;
    }
  }
}

void CompoundTypeSpecifier::printObject(std::ostream* stream) {
  { CompoundTypeSpecifier* self = this;

    *(stream) << "|TS|" << yieldTypeSpecTree(self);
  }
}

ParametricTypeSpecifier* newParametricTypeSpecifier() {
  { ParametricTypeSpecifier* self = NULL;

    self = new ParametricTypeSpecifier();
    self->specifierDimensions = NULL;
    self->specifierParameterTypes = newList();
    self->specifierBaseType = NULL;
    return (self);
  }
}

Surrogate* ParametricTypeSpecifier::primaryType() {
  { ParametricTypeSpecifier* self = this;

    return (SGT_HIERARCHY_STELLA_PARAMETRIC_TYPE_SPECIFIER);
  }
}

Object* accessParametricTypeSpecifierSlotValue(ParametricTypeSpecifier* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_SPECIFIER_BASE_TYPE) {
    if (setvalueP) {
      self->specifierBaseType = ((Surrogate*)(value));
    }
    else {
      value = self->specifierBaseType;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SPECIFIER_PARAMETER_TYPES) {
    if (setvalueP) {
      self->specifierParameterTypes = ((List*)(value));
    }
    else {
      value = self->specifierParameterTypes;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SPECIFIER_DIMENSIONS) {
    if (setvalueP) {
      self->specifierDimensions = ((List*)(value));
    }
    else {
      value = self->specifierDimensions;
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

AnchoredTypeSpecifier* newAnchoredTypeSpecifier() {
  { AnchoredTypeSpecifier* self = NULL;

    self = new AnchoredTypeSpecifier();
    self->specifierParameterName = NULL;
    return (self);
  }
}

Surrogate* AnchoredTypeSpecifier::primaryType() {
  { AnchoredTypeSpecifier* self = this;

    return (SGT_HIERARCHY_STELLA_ANCHORED_TYPE_SPECIFIER);
  }
}

Object* accessAnchoredTypeSpecifierSlotValue(AnchoredTypeSpecifier* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_SPECIFIER_PARAMETER_NAME) {
    if (setvalueP) {
      self->specifierParameterName = ((Symbol*)(value));
    }
    else {
      value = self->specifierParameterName;
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

Table* newTable() {
  { Table* self = NULL;

    self = new Table();
    self->dynamicSlots = newKeyValueList();
    self->abstractP = false;
    self->slotDirectEquivalent = NULL;
    self->slotMarkedP = false;
    self->slotExternalP = false;
    self->slotRenamedP = false;
    self->slotPublicP = true;
    self->slotSlotref = NULL;
    self->slotBaseType = NULL;
    self->slotOwner = NULL;
    self->slotName = NULL;
    self->tupleDomains = NULL;
    return (self);
  }
}

Surrogate* Table::primaryType() {
  { Table* self = this;

    return (SGT_HIERARCHY_STELLA_TABLE);
  }
}

Object* accessTableSlotValue(Table* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_TUPLE_DOMAINS) {
    if (setvalueP) {
      self->tupleDomains = ((List*)(value));
    }
    else {
      value = self->tupleDomains;
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

void Table::printObject(std::ostream* stream) {
  { Table* self = this;

    *(stream) << "|T|" << self->slotName->symbolName;
  }
}

GlobalVariable* newGlobalVariable() {
  { GlobalVariable* self = NULL;

    self = new GlobalVariable();
    self->dynamicSlots = newKeyValueList();
    self->variableStringifiedSource = NULL;
    self->documentation = NULL;
    self->variableNativeObject = NULL;
    self->variableAuxiliaryP = false;
    self->variablePublicP = true;
    self->variableConstantP = false;
    self->variableSpecialP = false;
    self->variableType = NULL;
    self->variableName = NULL;
    return (self);
  }
}

Surrogate* GlobalVariable::primaryType() {
  { GlobalVariable* self = this;

    return (SGT_HIERARCHY_STELLA_GLOBAL_VARIABLE);
  }
}

const char* GlobalVariable::name() {
  { GlobalVariable* self = this;

    return (self->variableName->symbolName);
  }
}

Surrogate* GlobalVariable::type() {
  { GlobalVariable* self = this;

    return (self->variableType);
  }
}

Module* GlobalVariable::homeModule() {
  { GlobalVariable* self = this;

    { Module* module = ((Module*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_VARIABLE_HOME_MODULE, NULL)));

      if (((boolean)(module))) {
        return (module);
      }
      else {
        return (((Module*)(self->variableName->homeContext)));
      }
    }
  }
}

Object* accessGlobalVariableSlotValue(GlobalVariable* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_DOCUMENTATION) {
    if (setvalueP) {
      self->documentation = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->documentation);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_VARIABLE_NAME) {
    if (setvalueP) {
      self->variableName = ((Symbol*)(value));
    }
    else {
      value = self->variableName;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_VARIABLE_TYPE) {
    if (setvalueP) {
      self->variableType = ((Surrogate*)(value));
    }
    else {
      value = self->variableType;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_VARIABLE_SPECIALp) {
    if (setvalueP) {
      self->variableSpecialP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->variableSpecialP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_VARIABLE_CONSTANTp) {
    if (setvalueP) {
      self->variableConstantP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->variableConstantP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_VARIABLE_PUBLICp) {
    if (setvalueP) {
      self->variablePublicP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->variablePublicP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_VARIABLE_AUXILIARYp) {
    if (setvalueP) {
      self->variableAuxiliaryP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->variableAuxiliaryP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_VARIABLE_DOCUMENTATION) {
    if (setvalueP) {
      self->documentation = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->documentation);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_VARIABLE_STRINGIFIED_SOURCE) {
    if (setvalueP) {
      self->variableStringifiedSource = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->variableStringifiedSource);
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

QuotedExpression* newQuotedExpression() {
  { QuotedExpression* self = NULL;

    self = new (PointerFreeGC)QuotedExpression;
    self->quotationTableOffset = NULL_INTEGER;
    return (self);
  }
}

Surrogate* QuotedExpression::primaryType() {
  { QuotedExpression* self = this;

    return (SGT_HIERARCHY_STELLA_QUOTED_EXPRESSION);
  }
}

Object* accessQuotedExpressionSlotValue(QuotedExpression* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_QUOTATION_TABLE_OFFSET) {
    if (setvalueP) {
      self->quotationTableOffset = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->quotationTableOffset);
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

BooleanWrapper* Thing::badP_reader() {
  { Thing* self = this;

    { BooleanWrapper* answer = ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_BADp, NULL)));

      if (!((boolean)(answer))) {
        return (FALSE_WRAPPER);
      }
      else {
        return (answer);
      }
    }
  }
}

Object* accessThingSlotValue(Thing* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_SURROGATE_VALUE_INVERSE) {
    if (setvalueP) {
      self->surrogateValueInverse = ((Surrogate*)(value));
    }
    else {
      value = self->surrogateValueInverse;
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

boolean Thing::deletedP() {
  { Thing* self = this;

    { BooleanWrapper* deletedP = ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_DELETED_OBJECTp, NULL)));

      if (((boolean)(deletedP))) {
        return (coerceWrappedBooleanToBoolean(deletedP));
      }
      else {
        return (false);
      }
    }
  }
}

boolean Thing::deletedPSetter(boolean value) {
  { Thing* self = this;

    setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_DELETED_OBJECTp, (value ? TRUE_WRAPPER : FALSE_WRAPPER), NULL);
    return (value);
  }
}

void Thing::printObject(std::ostream* stream) {
  { Thing* self = this;

    if (((boolean)(self->surrogateValueInverse))) {
      *(stream) << "|i|" << self->surrogateValueInverse->symbolName;
    }
    else {
      *(stream) << "|i|" << self->primaryType();
    }
  }
}

const char* Context::contextName() {
  { Context* self = this;

    { Context* aux = self;

      { Surrogate* testValue000 = safePrimaryType(aux);

        if (subtypeOfP(testValue000, SGT_HIERARCHY_STELLA_MODULE)) {
          { Context* aux000 = aux;
            Module* aux = ((Module*)(aux000));

            return (aux->moduleName);
          }
        }
        else if (subtypeOfP(testValue000, SGT_HIERARCHY_STELLA_WORLD)) {
          { Context* aux001 = aux;
            World* aux = ((World*)(aux001));

            return (((StringWrapper*)(dynamicSlotValue(aux->dynamicSlots, SYM_HIERARCHY_STELLA_WORLD_NAME, NULL_STRING_WRAPPER)))->wrapperValue);
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

Module* Context::homeModule() {
  { Context* self = this;

    return (self->baseModule);
  }
}

Object* accessContextSlotValue(Context* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_CHILD_CONTEXTS) {
    if (setvalueP) {
      self->childContexts = ((List*)(value));
    }
    else {
      value = self->childContexts;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_BASE_MODULE) {
    if (setvalueP) {
      self->baseModule = ((Module*)(value));
    }
    else {
      value = self->baseModule;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_ALL_SUPER_CONTEXTS) {
    if (setvalueP) {
      self->allSuperContexts = ((Cons*)(value));
    }
    else {
      value = self->allSuperContexts;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CONTEXT_NUMBER) {
    if (setvalueP) {
      self->contextNumber = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->contextNumber);
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

void Context::printObject(std::ostream* stream) {
  { Context* self = this;

    printContext(self, stream);
  }
}

Module* newModule() {
  { Module* self = NULL;

    self = new Module();
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->contextNumber = NULL_INTEGER;
    self->allSuperContexts = NULL;
    self->baseModule = NULL;
    self->childContexts = newList();
    self->prototypeInferenceCache = NULL;
    self->defaultInferenceCache = NULL;
    self->strictInferenceCache = NULL;
    self->surrogateOffsetTable = NULL;
    self->symbolOffsetTable = NULL;
    self->cardinalModule = NULL;
    self->stringifiedOptions = NULL;
    self->moduleStringifiedSource = NULL;
    self->moduleName = NULL;
    self->moduleFullName = NULL;
    self->caseSensitiveP = false;
    self->requires = NULL;
    self->usedBy = newList();
    self->uses = newList();
    self->nicknames = NULL;
    self->documentation = NULL;
    self->parentModules = newList();
    return (self);
  }
}

Surrogate* Module::primaryType() {
  { Module* self = this;

    return (SGT_HIERARCHY_STELLA_MODULE);
  }
}

const char* Module::name() {
  { Module* self = this;

    return (self->moduleName);
  }
}

Module* Module::parentModule() {
  { Module* self = this;

    return (((Module*)(((Context*)(self->parentContexts()->pop())))));
  }
}

const char* Module::lispPackage() {
  { Module* self = this;

    { Module* cursor = self;
      const char* value = ((StringWrapper*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_MODULE_LISP_PACKAGE, NULL_STRING_WRAPPER)))->wrapperValue;

      for (;;) {
        if (value != NULL) {
          return (value);
        }
        cursor = ((Module*)(cursor->parentModules->first()));
        if (((boolean)(cursor))) {
          value = ((StringWrapper*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_MODULE_LISP_PACKAGE, NULL_STRING_WRAPPER)))->wrapperValue;
        }
        else {
          return ("STELLA");
        }
      }
    }
  }
}

const char* Module::cppPackage() {
  { Module* self = this;

    { Module* cursor = self;
      const char* value = ((StringWrapper*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_MODULE_CPP_PACKAGE, NULL_STRING_WRAPPER)))->wrapperValue;

      for (;;) {
        if (value != NULL) {
          return (value);
        }
        cursor = ((Module*)(cursor->parentModules->first()));
        if (((boolean)(cursor))) {
          value = ((StringWrapper*)(dynamicSlotValue(cursor->dynamicSlots, SYM_HIERARCHY_STELLA_MODULE_CPP_PACKAGE, NULL_STRING_WRAPPER)))->wrapperValue;
        }
        else {
          return ("stella");
        }
      }
    }
  }
}

List* Module::shadowedSurrogates_reader() {
  { Module* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SHADOWED_SURROGATES, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

const char* Module::moduleLispPackage_reader() {
  { Module* self = this;

    { const char* answer = ((StringWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_MODULE_LISP_PACKAGE, NULL_STRING_WRAPPER)))->wrapperValue;

      if (answer == NULL) {
        return ("STELLA");
      }
      else {
        return (answer);
      }
    }
  }
}

const char* Module::moduleCppPackage_reader() {
  { Module* self = this;

    { const char* answer = ((StringWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_MODULE_CPP_PACKAGE, NULL_STRING_WRAPPER)))->wrapperValue;

      if (answer == NULL) {
        return ("stella");
      }
      else {
        return (answer);
      }
    }
  }
}

const char* Module::javaPackage_reader() {
  { Module* self = this;

    { const char* answer = ((StringWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_JAVA_PACKAGE, NULL_STRING_WRAPPER)))->wrapperValue;

      if (answer == NULL) {
        return (NULL);
      }
      else {
        return (answer);
      }
    }
  }
}

boolean Module::clearableP_reader() {
  { Module* self = this;

    return (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLEARABLEp, TRUE_WRAPPER)))->wrapperValue);
  }
}

boolean Module::protectSurrogatesP_reader() {
  { Module* self = this;

    return (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_PROTECT_SURROGATESp, TRUE_WRAPPER)))->wrapperValue);
  }
}

Object* accessModuleSlotValue(Module* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_PARENT_MODULES) {
    if (setvalueP) {
      self->parentModules = ((List*)(value));
    }
    else {
      value = self->parentModules;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DOCUMENTATION) {
    if (setvalueP) {
      self->documentation = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->documentation);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_NICKNAMES) {
    if (setvalueP) {
      self->nicknames = ((List*)(value));
    }
    else {
      value = self->nicknames;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_USES) {
    if (setvalueP) {
      self->uses = ((List*)(value));
    }
    else {
      value = self->uses;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_USED_BY) {
    if (setvalueP) {
      self->usedBy = ((List*)(value));
    }
    else {
      value = self->usedBy;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SHADOWED_SURROGATES) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_SHADOWED_SURROGATES, ((List*)(value)), NULL);
    }
    else {
      value = self->shadowedSurrogates_reader();
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_REQUIRES) {
    if (setvalueP) {
      self->requires = ((List*)(value));
    }
    else {
      value = self->requires;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_MODULE_LISP_PACKAGE) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_MODULE_LISP_PACKAGE, wrapString(((StringWrapper*)(value))->wrapperValue), NULL_STRING_WRAPPER);
    }
    else {
      value = wrapString(self->moduleLispPackage_reader());
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_MODULE_CPP_PACKAGE) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_MODULE_CPP_PACKAGE, wrapString(((StringWrapper*)(value))->wrapperValue), NULL_STRING_WRAPPER);
    }
    else {
      value = wrapString(self->moduleCppPackage_reader());
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_JAVA_PACKAGE) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_JAVA_PACKAGE, wrapString(((StringWrapper*)(value))->wrapperValue), NULL_STRING_WRAPPER);
    }
    else {
      value = wrapString(self->javaPackage_reader());
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CASE_SENSITIVEp) {
    if (setvalueP) {
      self->caseSensitiveP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->caseSensitiveP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CLEARABLEp) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_CLEARABLEp, (coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value))) ? TRUE_WRAPPER : FALSE_WRAPPER), FALSE_WRAPPER);
    }
    else {
      value = (self->clearableP_reader() ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_PROTECT_SURROGATESp) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_PROTECT_SURROGATESp, (coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value))) ? TRUE_WRAPPER : FALSE_WRAPPER), FALSE_WRAPPER);
    }
    else {
      value = (self->protectSurrogatesP_reader() ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_MODULE_FULL_NAME) {
    if (setvalueP) {
      self->moduleFullName = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->moduleFullName);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_MODULE_NAME) {
    if (setvalueP) {
      self->moduleName = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->moduleName);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_MODULE_STRINGIFIED_SOURCE) {
    if (setvalueP) {
      self->moduleStringifiedSource = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->moduleStringifiedSource);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_STRINGIFIED_OPTIONS) {
    if (setvalueP) {
      self->stringifiedOptions = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->stringifiedOptions);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CARDINAL_MODULE) {
    if (setvalueP) {
      self->cardinalModule = ((Module*)(value));
    }
    else {
      value = self->cardinalModule;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SYMBOL_OFFSET_TABLE) {
    if (setvalueP) {
      self->symbolOffsetTable = ((StringToIntegerHashTable*)(value));
    }
    else {
      value = self->symbolOffsetTable;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SURROGATE_OFFSET_TABLE) {
    if (setvalueP) {
      self->surrogateOffsetTable = ((StringToIntegerHashTable*)(value));
    }
    else {
      value = self->surrogateOffsetTable;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_STRICT_INFERENCE_CACHE) {
    if (setvalueP) {
      self->strictInferenceCache = ((World*)(value));
    }
    else {
      value = self->strictInferenceCache;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DEFAULT_INFERENCE_CACHE) {
    if (setvalueP) {
      self->defaultInferenceCache = ((World*)(value));
    }
    else {
      value = self->defaultInferenceCache;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_PROTOTYPE_INFERENCE_CACHE) {
    if (setvalueP) {
      self->prototypeInferenceCache = ((World*)(value));
    }
    else {
      value = self->prototypeInferenceCache;
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

World* newWorld() {
  { World* self = NULL;

    self = new World();
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->contextNumber = NULL_INTEGER;
    self->allSuperContexts = NULL;
    self->baseModule = NULL;
    self->childContexts = newList();
    self->parentContext = NULL;
    return (self);
  }
}

Surrogate* World::primaryType() {
  { World* self = this;

    return (SGT_HIERARCHY_STELLA_WORLD);
  }
}

Object* accessWorldSlotValue(World* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_PARENT_CONTEXT) {
    if (setvalueP) {
      self->parentContext = ((Context*)(value));
    }
    else {
      value = self->parentContext;
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

CsValue* newCsValue() {
  { CsValue* self = NULL;

    self = new CsValue();
    self->theKvList = NULL;
    return (self);
  }
}

Surrogate* CsValue::primaryType() {
  { CsValue* self = this;

    return (SGT_HIERARCHY_STELLA_CS_VALUE);
  }
}

Interval* newInterval() {
  { Interval* self = NULL;

    self = new (PointerFreeGC)Interval;
    self->upperBound = NULL_INTEGER;
    self->lowerBound = NULL_INTEGER;
    return (self);
  }
}

Surrogate* Interval::primaryType() {
  { Interval* self = this;

    return (SGT_HIERARCHY_STELLA_INTERVAL);
  }
}

Object* accessIntervalSlotValue(Interval* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_LOWER_BOUND) {
    if (setvalueP) {
      self->lowerBound = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->lowerBound);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_UPPER_BOUND) {
    if (setvalueP) {
      self->upperBound = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->upperBound);
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

void Interval::printObject(std::ostream* stream) {
  { Interval* self = this;

    *(stream) << "[" << self->lowerBound << "," << self->upperBound << "]";
  }
}

TaxonomyNode* newTaxonomyNode() {
  { TaxonomyNode* self = NULL;

    self = new TaxonomyNode();
    self->marker = NULL;
    self->treeChildren = NIL;
    self->totalAncestors = 1;
    self->children = NIL;
    self->parents = NIL;
    self->firstIntervalUpperBound = -1;
    self->firstIntervalLowerBound = -1;
    self->initialInterval = NULL;
    self->intervals = NIL;
    self->label = NULL_INTEGER;
    self->nativeObject = NULL;
    return (self);
  }
}

Surrogate* TaxonomyNode::primaryType() {
  { TaxonomyNode* self = this;

    return (SGT_HIERARCHY_STELLA_TAXONOMY_NODE);
  }
}

Object* accessTaxonomyNodeSlotValue(TaxonomyNode* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_NATIVE_OBJECT) {
    if (setvalueP) {
      self->nativeObject = value;
    }
    else {
      value = self->nativeObject;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_LABEL) {
    if (setvalueP) {
      self->label = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->label);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_INTERVALS) {
    if (setvalueP) {
      self->intervals = ((Cons*)(value));
    }
    else {
      value = self->intervals;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_INITIAL_INTERVAL) {
    if (setvalueP) {
      self->initialInterval = ((Interval*)(value));
    }
    else {
      value = self->initialInterval;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_FIRST_INTERVAL_LOWER_BOUND) {
    if (setvalueP) {
      self->firstIntervalLowerBound = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->firstIntervalLowerBound);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_FIRST_INTERVAL_UPPER_BOUND) {
    if (setvalueP) {
      self->firstIntervalUpperBound = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->firstIntervalUpperBound);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_PARENTS) {
    if (setvalueP) {
      self->parents = ((Cons*)(value));
    }
    else {
      value = self->parents;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CHILDREN) {
    if (setvalueP) {
      self->children = ((Cons*)(value));
    }
    else {
      value = self->children;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_TOTAL_ANCESTORS) {
    if (setvalueP) {
      self->totalAncestors = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->totalAncestors);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_TREE_CHILDREN) {
    if (setvalueP) {
      self->treeChildren = ((Cons*)(value));
    }
    else {
      value = self->treeChildren;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_MARKER) {
    if (setvalueP) {
      self->marker = value;
    }
    else {
      value = self->marker;
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

void TaxonomyNode::printObject(std::ostream* stream) {
  { TaxonomyNode* self = this;

    *(stream) << "|TN|" << self->label << " " << self->intervals << " " << self->nativeObject;
  }
}

TaxonomyGraph* newTaxonomyGraph() {
  { TaxonomyGraph* self = NULL;

    self = new TaxonomyGraph();
    self->removedLinks = NULL;
    self->addedLinks = NULL;
    self->brokenLinks = NULL;
    self->roots = NULL;
    self->numberOfForeignIntervalNodes = NULL_INTEGER;
    self->numberOfNodes = NULL_INTEGER;
    self->largestPostorderNumber = NULL_INTEGER;
    self->incrementalModeP = false;
    self->renumberRatio = 0.1;
    self->renumberIfOutOfNumbersP = false;
    initializeTaxonomyGraph(self);
    return (self);
  }
}

Surrogate* TaxonomyGraph::primaryType() {
  { TaxonomyGraph* self = this;

    return (SGT_HIERARCHY_STELLA_TAXONOMY_GRAPH);
  }
}

Object* accessTaxonomyGraphSlotValue(TaxonomyGraph* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_RENUMBER_IF_OUT_OF_NUMBERSp) {
    if (setvalueP) {
      self->renumberIfOutOfNumbersP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->renumberIfOutOfNumbersP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_RENUMBER_RATIO) {
    if (setvalueP) {
      self->renumberRatio = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->renumberRatio);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_INCREMENTAL_MODEp) {
    if (setvalueP) {
      self->incrementalModeP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->incrementalModeP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_LARGEST_POSTORDER_NUMBER) {
    if (setvalueP) {
      self->largestPostorderNumber = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->largestPostorderNumber);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_NUMBER_OF_NODES) {
    if (setvalueP) {
      self->numberOfNodes = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->numberOfNodes);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_NUMBER_OF_FOREIGN_INTERVAL_NODES) {
    if (setvalueP) {
      self->numberOfForeignIntervalNodes = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->numberOfForeignIntervalNodes);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_ROOTS) {
    if (setvalueP) {
      self->roots = ((List*)(value));
    }
    else {
      value = self->roots;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_BROKEN_LINKS) {
    if (setvalueP) {
      self->brokenLinks = ((List*)(value));
    }
    else {
      value = self->brokenLinks;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_ADDED_LINKS) {
    if (setvalueP) {
      self->addedLinks = ((List*)(value));
    }
    else {
      value = self->addedLinks;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_REMOVED_LINKS) {
    if (setvalueP) {
      self->removedLinks = ((List*)(value));
    }
    else {
      value = self->removedLinks;
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

void TaxonomyGraph::printObject(std::ostream* stream) {
  { TaxonomyGraph* self = this;

    *(stream) << "|TG|" << self->roots;
  }
}

StellaException* newStellaException(const char* message) {
  { StellaException* self = NULL;

    self = new StellaException(message);
    return (self);
  }
}

InputOutputException* newInputOutputException(const char* message) {
  { InputOutputException* self = NULL;

    self = new InputOutputException(message);
    return (self);
  }
}

ReadException* newReadException(const char* message) {
  { ReadException* self = NULL;

    self = new ReadException(message);
    return (self);
  }
}

EndOfFileException* newEndOfFileException(const char* message) {
  { EndOfFileException* self = NULL;

    self = new EndOfFileException(message);
    return (self);
  }
}

NoSuchFileException* newNoSuchFileException(const char* message) {
  { NoSuchFileException* self = NULL;

    self = new NoSuchFileException(message);
    self->filename = NULL;
    return (self);
  }
}

FileAlreadyExistsException* newFileAlreadyExistsException(const char* message) {
  { FileAlreadyExistsException* self = NULL;

    self = new FileAlreadyExistsException(message);
    self->filename = NULL;
    return (self);
  }
}

UnhandledException* newUnhandledException(const char* message) {
  { UnhandledException* self = NULL;

    self = new UnhandledException(message);
    return (self);
  }
}

EvaluationException* newEvaluationException(const char* message) {
  { EvaluationException* self = NULL;

    self = new EvaluationException(message);
    return (self);
  }
}

NoSuchObjectException* newNoSuchObjectException(const char* message) {
  { NoSuchObjectException* self = NULL;

    self = new NoSuchObjectException(message);
    return (self);
  }
}

NoSuchContextException* newNoSuchContextException(const char* message) {
  { NoSuchContextException* self = NULL;

    self = new NoSuchContextException(message);
    return (self);
  }
}

UndefinedClassException* newUndefinedClassException(const char* message) {
  { UndefinedClassException* self = NULL;

    self = new UndefinedClassException(message);
    return (self);
  }
}

BadArgumentException* newBadArgumentException(const char* message) {
  { BadArgumentException* self = NULL;

    self = new BadArgumentException(message);
    return (self);
  }
}

ObjectNotClassException* newObjectNotClassException(const char* message) {
  { ObjectNotClassException* self = NULL;

    self = new ObjectNotClassException(message);
    return (self);
  }
}

IncompatibleQuantityException* newIncompatibleQuantityException(const char* message) {
  { IncompatibleQuantityException* self = NULL;

    self = new IncompatibleQuantityException(message);
    return (self);
  }
}

TimeoutException* newTimeoutException(const char* message) {
  { TimeoutException* self = NULL;

    self = new TimeoutException(message);
    return (self);
  }
}

Quantity* Quantity::coerceTo(Object* other) {
  { Quantity* self = this;

    if (isaP(other, self->primaryType())) {
      return (((Quantity*)(other)));
    }
    else {
      return (NULL);
    }
  }
}

boolean Quantity::lessP(Object* other) {
  { Quantity* self = this;

    other = other;
    return (false);
  }
}

boolean Quantity::lessEqualP(Object* other) {
  { Quantity* self = this;

    return (self->objectEqlP(other) ||
        self->lessP(other));
  }
}

boolean Quantity::greaterEqualP(Object* other) {
  { Quantity* self = this;

    return (self->objectEqlP(other) ||
        self->greaterP(other));
  }
}

boolean Quantity::greaterP(Object* other) {
  { Quantity* self = this;

    other = other;
    return (false);
  }
}

IntegerWrapper* newIntegerWrapper(int wrapperValue) {
  { IntegerWrapper* self = NULL;

    self = new (PointerFreeGC)IntegerWrapper;
    self->wrapperValue = wrapperValue;
    return (self);
  }
}

Surrogate* IntegerWrapper::primaryType() {
  { IntegerWrapper* self = this;

    return (SGT_HIERARCHY_STELLA_INTEGER_WRAPPER);
  }
}

Object* accessIntegerWrapperSlotValue(IntegerWrapper* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_WRAPPER_VALUE) {
    if (setvalueP) {
      self->wrapperValue = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->wrapperValue);
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

void IntegerWrapper::printObject(std::ostream* stream) {
  { IntegerWrapper* self = this;

    { int value = self->wrapperValue;

      if (value == NULL_INTEGER) {
        if (oPRINTREADABLYpo) {
          *(stream) << SYM_HIERARCHY_STELLA_NULL_INTEGER;
        }
        else {
          *(stream) << "|L|NULL-INTEGER";
        }
      }
      else {
        if (oPRINTREADABLYpo) {
          *(stream) << value;
        }
        else {
          *(stream) << "|L|" << value;
        }
      }
    }
  }
}

LongIntegerWrapper* newLongIntegerWrapper(long long int wrapperValue) {
  { LongIntegerWrapper* self = NULL;

    self = new (PointerFreeGC)LongIntegerWrapper;
    self->wrapperValue = wrapperValue;
    return (self);
  }
}

Surrogate* LongIntegerWrapper::primaryType() {
  { LongIntegerWrapper* self = this;

    return (SGT_HIERARCHY_STELLA_LONG_INTEGER_WRAPPER);
  }
}

Object* accessLongIntegerWrapperSlotValue(LongIntegerWrapper* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_WRAPPER_VALUE) {
    if (setvalueP) {
      self->wrapperValue = ((LongIntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapLongInteger(self->wrapperValue);
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

void LongIntegerWrapper::printObject(std::ostream* stream) {
  { LongIntegerWrapper* self = this;

    { long long int value = self->wrapperValue;

      if (value == NULL_LONG_INTEGER) {
        if (oPRINTREADABLYpo) {
          *(stream) << SYM_HIERARCHY_STELLA_NULL_LONG_INTEGER;
        }
        else {
          *(stream) << "|L|NULL-LONG-INTEGER";
        }
      }
      else {
        if (oPRINTREADABLYpo) {
          *(stream) << value;
        }
        else {
          *(stream) << "|L|" << value;
        }
      }
    }
  }
}

FloatWrapper* newFloatWrapper(double wrapperValue) {
  { FloatWrapper* self = NULL;

    self = new (PointerFreeGC)FloatWrapper;
    self->wrapperValue = wrapperValue;
    return (self);
  }
}

Surrogate* FloatWrapper::primaryType() {
  { FloatWrapper* self = this;

    return (SGT_HIERARCHY_STELLA_FLOAT_WRAPPER);
  }
}

Object* accessFloatWrapperSlotValue(FloatWrapper* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_WRAPPER_VALUE) {
    if (setvalueP) {
      self->wrapperValue = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->wrapperValue);
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

void FloatWrapper::printObject(std::ostream* stream) {
  { FloatWrapper* self = this;

    { double value = self->wrapperValue;

      if (value == NULL_FLOAT) {
        if (oPRINTREADABLYpo) {
          *(stream) << SYM_HIERARCHY_STELLA_NULL_FLOAT;
        }
        else {
          *(stream) << "|L|NULL-FLOAT";
        }
      }
      else {
        if (oPRINTREADABLYpo) {
          *(stream) << value;
        }
        else {
          *(stream) << "|L|" << value;
        }
      }
    }
  }
}

StringWrapper* newStringWrapper(const char* wrapperValue) {
  { StringWrapper* self = NULL;

    self = new StringWrapper();
    self->wrapperValue = wrapperValue;
    return (self);
  }
}

Surrogate* StringWrapper::primaryType() {
  { StringWrapper* self = this;

    return (SGT_HIERARCHY_STELLA_STRING_WRAPPER);
  }
}

Object* accessStringWrapperSlotValue(StringWrapper* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_WRAPPER_VALUE) {
    if (setvalueP) {
      self->wrapperValue = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->wrapperValue);
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

void StringWrapper::printObject(std::ostream* stream) {
  { StringWrapper* self = this;

    { const char* value = self->wrapperValue;

      if (value == NULL) {
        if (oPRINTREADABLYpo) {
          *(stream) << SYM_HIERARCHY_STELLA_NULL_STRING;
        }
        else {
          *(stream) << "|L|NULL-STRING";
        }
      }
      else {
        if (oPRINTREADABLYpo) {
          printStringReadably(value, stream);
        }
        else {
          *(stream) << "|L|" << "\"" << value << "\"";
        }
      }
    }
  }
}

MutableStringWrapper* newMutableStringWrapper(char* wrapperValue) {
  { MutableStringWrapper* self = NULL;

    self = new MutableStringWrapper();
    self->wrapperValue = wrapperValue;
    return (self);
  }
}

Surrogate* MutableStringWrapper::primaryType() {
  { MutableStringWrapper* self = this;

    return (SGT_HIERARCHY_STELLA_MUTABLE_STRING_WRAPPER);
  }
}

Object* accessMutableStringWrapperSlotValue(MutableStringWrapper* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_WRAPPER_VALUE) {
    if (setvalueP) {
      self->wrapperValue = ((MutableStringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapMutableString(self->wrapperValue);
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

void MutableStringWrapper::printObject(std::ostream* stream) {
  { MutableStringWrapper* self = this;

    { char* value = self->wrapperValue;

      if (value == NULL) {
        if (oPRINTREADABLYpo) {
          *(stream) << SYM_HIERARCHY_STELLA_NULL_MUTABLE_STRING;
        }
        else {
          *(stream) << "|L|NULL-MUTABLE-STRING";
        }
      }
      else {
        if (oPRINTREADABLYpo) {
          printStringReadably(value, stream);
        }
        else {
          *(stream) << "|L|" << "\"" << value << "\"";
        }
      }
    }
  }
}

CharacterWrapper* newCharacterWrapper(char wrapperValue) {
  { CharacterWrapper* self = NULL;

    self = new (PointerFreeGC)CharacterWrapper;
    self->wrapperValue = wrapperValue;
    return (self);
  }
}

Surrogate* CharacterWrapper::primaryType() {
  { CharacterWrapper* self = this;

    return (SGT_HIERARCHY_STELLA_CHARACTER_WRAPPER);
  }
}

Object* accessCharacterWrapperSlotValue(CharacterWrapper* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_WRAPPER_VALUE) {
    if (setvalueP) {
      self->wrapperValue = ((CharacterWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapCharacter(self->wrapperValue);
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

void CharacterWrapper::printObject(std::ostream* stream) {
  { CharacterWrapper* self = this;

    { char value = self->wrapperValue;

      if (value == NULL_CHARACTER) {
        if (oPRINTREADABLYpo) {
          *(stream) << SYM_HIERARCHY_STELLA_NULL_CHARACTER;
        }
        else {
          *(stream) << "|L|NULL-CHARACTER";
        }
      }
      else {
        {
          if (!(oPRINTREADABLYpo)) {
            *(stream) << "|L|";
          }
          printCharacter(value, stream);
        }
      }
    }
  }
}

BooleanWrapper* newBooleanWrapper(boolean wrapperValue) {
  { BooleanWrapper* self = NULL;

    self = new BooleanWrapper();
    self->wrapperValue = wrapperValue;
    return (self);
  }
}

Surrogate* BooleanWrapper::primaryType() {
  { BooleanWrapper* self = this;

    return (SGT_HIERARCHY_STELLA_BOOLEAN_WRAPPER);
  }
}

Object* accessBooleanWrapperSlotValue(BooleanWrapper* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_WRAPPER_VALUE) {
    if (setvalueP) {
      self->wrapperValue = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->wrapperValue ? TRUE_WRAPPER : FALSE_WRAPPER);
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

void BooleanWrapper::printObject(std::ostream* stream) {
  { BooleanWrapper* self = this;

    {
      if (!(oPRINTREADABLYpo)) {
        *(stream) << "|L|";
      }
      if (self->wrapperValue) {
        *(stream) << SYM_HIERARCHY_STELLA_TRUE;
      }
      else {
        *(stream) << SYM_HIERARCHY_STELLA_FALSE;
      }
    }
  }
}

Object* accessCodeWrapperSlotValue(CodeWrapper* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_METHOD_CODEp) {
    if (setvalueP) {
      self->methodCodeP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->methodCodeP ? TRUE_WRAPPER : FALSE_WRAPPER);
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

FunctionCodeWrapper* newFunctionCodeWrapper(cpp_function_code wrapperValue) {
  { FunctionCodeWrapper* self = NULL;

    self = new FunctionCodeWrapper();
    self->wrapperValue = wrapperValue;
    self->methodCodeP = false;
    return (self);
  }
}

Surrogate* FunctionCodeWrapper::primaryType() {
  { FunctionCodeWrapper* self = this;

    return (SGT_HIERARCHY_STELLA_FUNCTION_CODE_WRAPPER);
  }
}

Object* accessFunctionCodeWrapperSlotValue(FunctionCodeWrapper* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_WRAPPER_VALUE) {
    if (setvalueP) {
      self->wrapperValue = ((FunctionCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFunctionCode(self->wrapperValue);
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

MethodCodeWrapper* newMethodCodeWrapper(cpp_method_code wrapperValue) {
  { MethodCodeWrapper* self = NULL;

    self = new MethodCodeWrapper();
    self->wrapperValue = wrapperValue;
    self->methodCodeP = true;
    return (self);
  }
}

Surrogate* MethodCodeWrapper::primaryType() {
  { MethodCodeWrapper* self = this;

    return (SGT_HIERARCHY_STELLA_METHOD_CODE_WRAPPER);
  }
}

Object* accessMethodCodeWrapperSlotValue(MethodCodeWrapper* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_WRAPPER_VALUE) {
    if (setvalueP) {
      self->wrapperValue = ((MethodCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapMethodCode(self->wrapperValue);
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

VerbatimStringWrapper* newVerbatimStringWrapper(const char* wrapperValue) {
  { VerbatimStringWrapper* self = NULL;

    self = new VerbatimStringWrapper();
    self->wrapperValue = wrapperValue;
    return (self);
  }
}

Surrogate* VerbatimStringWrapper::primaryType() {
  { VerbatimStringWrapper* self = this;

    return (SGT_HIERARCHY_STELLA_VERBATIM_STRING_WRAPPER);
  }
}

void VerbatimStringWrapper::printObject(std::ostream* stream) {
  { VerbatimStringWrapper* self = this;

    *(stream) << ((oPRINTREADABLYpo ? "" : "|V|")) << self->wrapperValue;
  }
}

NativeObjectPointerWrapper* newNativeObjectPointerWrapper(void* wrapperValue) {
  { NativeObjectPointerWrapper* self = NULL;

    self = new NativeObjectPointerWrapper();
    self->wrapperValue = wrapperValue;
    return (self);
  }
}

Surrogate* NativeObjectPointerWrapper::primaryType() {
  { NativeObjectPointerWrapper* self = this;

    return (SGT_HIERARCHY_STELLA_NATIVE_OBJECT_POINTER_WRAPPER);
  }
}

ExceptionWrapper* newExceptionWrapper(std::exception* wrapperValue) {
  { ExceptionWrapper* self = NULL;

    self = new ExceptionWrapper();
    self->wrapperValue = wrapperValue;
    return (self);
  }
}

Surrogate* ExceptionWrapper::primaryType() {
  { ExceptionWrapper* self = this;

    return (SGT_HIERARCHY_STELLA_EXCEPTION_WRAPPER);
  }
}

SystemDefinition* newSystemDefinition() {
  { SystemDefinition* self = NULL;

    self = new SystemDefinition();
    self->dynamicSlots = newKeyValueList();
    self->finalizationFunction = NULL;
    self->developmentSettings = NULL;
    self->productionSettings = NULL;
    self->banner = NULL;
    self->binaryRootDirectory = NULL;
    self->nativeRootDirectory = NULL;
    self->sourceRootDirectory = NULL;
    self->cardinalModule = NULL;
    self->upToDateP = false;
    self->loadedP = false;
    self->requiredSystems = NULL;
    self->preprocessedFiles = NULL;
    self->dataFiles = NULL;
    self->javaOnlyFiles = NULL;
    self->cppOnlyFiles = NULL;
    self->lispOnlyFiles = NULL;
    self->files = NULL;
    self->directory = NULL;
    self->definitionFile = NULL;
    self->name = NULL;
    return (self);
  }
}

Surrogate* SystemDefinition::primaryType() {
  { SystemDefinition* self = this;

    return (SGT_HIERARCHY_STELLA_SYSTEM_DEFINITION);
  }
}

BooleanWrapper* SystemDefinition::badP_reader() {
  { SystemDefinition* self = this;

    { BooleanWrapper* answer = ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_BADp, NULL)));

      if (!((boolean)(answer))) {
        return (FALSE_WRAPPER);
      }
      else {
        return (answer);
      }
    }
  }
}

Object* accessSystemDefinitionSlotValue(SystemDefinition* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_NAME) {
    if (setvalueP) {
      self->name = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->name);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DEFINITION_FILE) {
    if (setvalueP) {
      self->definitionFile = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->definitionFile);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DIRECTORY) {
    if (setvalueP) {
      self->directory = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->directory);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_FILES) {
    if (setvalueP) {
      self->files = ((Cons*)(value));
    }
    else {
      value = self->files;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_LISP_ONLY_FILES) {
    if (setvalueP) {
      self->lispOnlyFiles = ((Cons*)(value));
    }
    else {
      value = self->lispOnlyFiles;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CPP_ONLY_FILES) {
    if (setvalueP) {
      self->cppOnlyFiles = ((Cons*)(value));
    }
    else {
      value = self->cppOnlyFiles;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_JAVA_ONLY_FILES) {
    if (setvalueP) {
      self->javaOnlyFiles = ((Cons*)(value));
    }
    else {
      value = self->javaOnlyFiles;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DATA_FILES) {
    if (setvalueP) {
      self->dataFiles = ((Cons*)(value));
    }
    else {
      value = self->dataFiles;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_PREPROCESSED_FILES) {
    if (setvalueP) {
      self->preprocessedFiles = ((Cons*)(value));
    }
    else {
      value = self->preprocessedFiles;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_REQUIRED_SYSTEMS) {
    if (setvalueP) {
      self->requiredSystems = ((Cons*)(value));
    }
    else {
      value = self->requiredSystems;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_LOADEDp) {
    if (setvalueP) {
      self->loadedP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->loadedP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_UP_TO_DATEp) {
    if (setvalueP) {
      self->upToDateP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->upToDateP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_CARDINAL_MODULE) {
    if (setvalueP) {
      self->cardinalModule = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->cardinalModule);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_SOURCE_ROOT_DIRECTORY) {
    if (setvalueP) {
      self->sourceRootDirectory = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->sourceRootDirectory);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_NATIVE_ROOT_DIRECTORY) {
    if (setvalueP) {
      self->nativeRootDirectory = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->nativeRootDirectory);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_BINARY_ROOT_DIRECTORY) {
    if (setvalueP) {
      self->binaryRootDirectory = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->binaryRootDirectory);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_BANNER) {
    if (setvalueP) {
      self->banner = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->banner);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_COPYRIGHT_HEADER) {
    if (setvalueP) {
      self->banner = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->banner);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_PRODUCTION_SETTINGS) {
    if (setvalueP) {
      self->productionSettings = ((Cons*)(value));
    }
    else {
      value = self->productionSettings;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_DEVELOPMENT_SETTINGS) {
    if (setvalueP) {
      self->developmentSettings = ((Cons*)(value));
    }
    else {
      value = self->developmentSettings;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_FINALIZATION_FUNCTION) {
    if (setvalueP) {
      self->finalizationFunction = ((Symbol*)(value));
    }
    else {
      value = self->finalizationFunction;
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

boolean SystemDefinition::deletedP() {
  { SystemDefinition* self = this;

    { BooleanWrapper* deletedP = ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_DELETED_OBJECTp, NULL)));

      if (((boolean)(deletedP))) {
        return (coerceWrappedBooleanToBoolean(deletedP));
      }
      else {
        return (false);
      }
    }
  }
}

boolean SystemDefinition::deletedPSetter(boolean value) {
  { SystemDefinition* self = this;

    setDynamicSlotValue(self->dynamicSlots, SYM_HIERARCHY_STELLA_DELETED_OBJECTp, (value ? TRUE_WRAPPER : FALSE_WRAPPER), NULL);
    return (value);
  }
}

void SystemDefinition::printObject(std::ostream* stream) {
  { SystemDefinition* self = this;

    *(stream) << "|SYSTEM|" << self->name;
  }
}

Object* accessStreamSlotValue(Stream* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_STATE) {
    if (setvalueP) {
      self->state = ((Keyword*)(value));
    }
    else {
      value = self->state;
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

OutputStream* newOutputStream() {
  { OutputStream* self = NULL;

    self = new OutputStream();
    self->state = NULL;
    self->nativeStream = NULL;
    return (self);
  }
}

void OutputStream::free() {
  { OutputStream* self = this;

    if (terminateOutputStreamP(self)) {
      unmake(self);
    }
  }
}

Surrogate* OutputStream::primaryType() {
  { OutputStream* self = this;

    return (SGT_HIERARCHY_STELLA_OUTPUT_STREAM);
  }
}

InputStream* newInputStream() {
  { InputStream* self = NULL;

    self = new InputStream();
    self->state = NULL;
    self->bufferingScheme = KWD_HIERARCHY_LINE;
    self->tokenizerState = NULL;
    self->echoStream = NULL;
    self->nativeStream = NULL;
    return (self);
  }
}

void InputStream::free() {
  { InputStream* self = this;

    if (terminateInputStreamP(self)) {
      unmake(self);
    }
  }
}

Surrogate* InputStream::primaryType() {
  { InputStream* self = this;

    return (SGT_HIERARCHY_STELLA_INPUT_STREAM);
  }
}

Object* accessInputStreamSlotValue(InputStream* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_ECHO_STREAM) {
    if (setvalueP) {
      self->echoStream = ((OutputStream*)(value));
    }
    else {
      value = self->echoStream;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_TOKENIZER_STATE) {
    if (setvalueP) {
      self->tokenizerState = ((TokenizerStreamState*)(value));
    }
    else {
      value = self->tokenizerState;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_BUFFERING_SCHEME) {
    if (setvalueP) {
      self->bufferingScheme = ((Keyword*)(value));
    }
    else {
      value = self->bufferingScheme;
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

OutputFileStream* newOutputFileStream(const char* filename) {
  { OutputFileStream* self = NULL;

    self = new OutputFileStream();
    self->filename = filename;
    self->state = NULL;
    self->nativeStream = NULL;
    self->ifNotExistsAction = KWD_HIERARCHY_CREATE;
    self->ifExistsAction = KWD_HIERARCHY_SUPERSEDE;
    initializeFileOutputStream(self);
    return (self);
  }
}

void OutputFileStream::free() {
  { OutputFileStream* self = this;

    if (terminateFileOutputStreamP(self)) {
      unmake(self);
    }
  }
}

Surrogate* OutputFileStream::primaryType() {
  { OutputFileStream* self = this;

    return (SGT_HIERARCHY_STELLA_OUTPUT_FILE_STREAM);
  }
}

Object* accessOutputFileStreamSlotValue(OutputFileStream* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_FILENAME) {
    if (setvalueP) {
      self->filename = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->filename);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_IF_EXISTS_ACTION) {
    if (setvalueP) {
      self->ifExistsAction = ((Keyword*)(value));
    }
    else {
      value = self->ifExistsAction;
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_IF_NOT_EXISTS_ACTION) {
    if (setvalueP) {
      self->ifNotExistsAction = ((Keyword*)(value));
    }
    else {
      value = self->ifNotExistsAction;
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

void OutputFileStream::printObject(std::ostream* stream) {
  { OutputFileStream* self = this;

    *(stream) << "|FOS|'" << self->filename << "'";
  }
}

InputFileStream* newInputFileStream(const char* filename) {
  { InputFileStream* self = NULL;

    self = new InputFileStream();
    self->filename = filename;
    self->state = NULL;
    self->tokenizerState = NULL;
    self->echoStream = NULL;
    self->nativeStream = NULL;
    self->bufferingScheme = KWD_HIERARCHY_BLOCK;
    self->ifNotExistsAction = KWD_HIERARCHY_ERROR;
    initializeFileInputStream(self);
    return (self);
  }
}

void InputFileStream::free() {
  { InputFileStream* self = this;

    if (terminateFileInputStreamP(self)) {
      unmake(self);
    }
  }
}

Surrogate* InputFileStream::primaryType() {
  { InputFileStream* self = this;

    return (SGT_HIERARCHY_STELLA_INPUT_FILE_STREAM);
  }
}

Object* accessInputFileStreamSlotValue(InputFileStream* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_FILENAME) {
    if (setvalueP) {
      self->filename = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->filename);
    }
  }
  else if (slotname == SYM_HIERARCHY_STELLA_IF_NOT_EXISTS_ACTION) {
    if (setvalueP) {
      self->ifNotExistsAction = ((Keyword*)(value));
    }
    else {
      value = self->ifNotExistsAction;
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

void InputFileStream::printObject(std::ostream* stream) {
  { InputFileStream* self = this;

    *(stream) << "|FIS|'" << self->filename << "'";
  }
}

OutputStringStream* newOutputStringStream() {
  { OutputStringStream* self = NULL;

    self = new OutputStringStream();
    self->state = NULL;
    self->nativeStream = NULL;
    self->theString = NULL;
    initializeStringOutputStream(self);
    return (self);
  }
}

void OutputStringStream::free() {
  { OutputStringStream* self = this;

    if (terminateStringOutputStreamP(self)) {
      unmake(self);
    }
  }
}

Surrogate* OutputStringStream::primaryType() {
  { OutputStringStream* self = this;

    return (SGT_HIERARCHY_STELLA_OUTPUT_STRING_STREAM);
  }
}

Object* accessOutputStringStreamSlotValue(OutputStringStream* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_THE_STRING) {
    if (setvalueP) {
      self->theString = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->theStringReader());
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

InputStringStream* newInputStringStream(const char* theString) {
  { InputStringStream* self = NULL;

    self = new InputStringStream();
    self->theString = theString;
    self->state = NULL;
    self->tokenizerState = NULL;
    self->echoStream = NULL;
    self->nativeStream = NULL;
    self->bufferingScheme = KWD_HIERARCHY_BLOCK;
    initializeStringInputStream(self);
    return (self);
  }
}

void InputStringStream::free() {
  { InputStringStream* self = this;

    if (terminateStringInputStreamP(self)) {
      unmake(self);
    }
  }
}

Surrogate* InputStringStream::primaryType() {
  { InputStringStream* self = this;

    return (SGT_HIERARCHY_STELLA_INPUT_STRING_STREAM);
  }
}

Object* accessInputStringStreamSlotValue(InputStringStream* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_HIERARCHY_STELLA_THE_STRING) {
    if (setvalueP) {
      self->theString = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->theString);
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

void helpStartupHierarchy1() {
  {
    SGT_HIERARCHY_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
    SYM_HIERARCHY_STELLA_PRIMARY_TYPE = ((Symbol*)(internRigidSymbolWrtModule("PRIMARY-TYPE", NULL, 0)));
    SYM_HIERARCHY_STELLA_HOME_MODULE = ((Symbol*)(internRigidSymbolWrtModule("HOME-MODULE", NULL, 0)));
    SYM_HIERARCHY_STELLA_DELETEDp = ((Symbol*)(internRigidSymbolWrtModule("DELETED?", NULL, 0)));
    SYM_HIERARCHY_STELLA_INCREMENT_REFERENCE_COUNT = ((Symbol*)(internRigidSymbolWrtModule("INCREMENT-REFERENCE-COUNT", NULL, 0)));
    SYM_HIERARCHY_STELLA_DECREMENT_REFERENCE_COUNT = ((Symbol*)(internRigidSymbolWrtModule("DECREMENT-REFERENCE-COUNT", NULL, 0)));
    SYM_HIERARCHY_STELLA_TYPE_SPEC = ((Symbol*)(internRigidSymbolWrtModule("TYPE-SPEC", NULL, 0)));
    SGT_HIERARCHY_STELLA_REFERENCE_COUNT_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("REFERENCE-COUNT-OBJECT", NULL, 1)));
    SYM_HIERARCHY_STELLA_REFERENCE_COUNT = ((Symbol*)(internRigidSymbolWrtModule("REFERENCE-COUNT", NULL, 0)));
    SYM_HIERARCHY_STELLA_BADp = ((Symbol*)(internRigidSymbolWrtModule("BAD?", NULL, 0)));
    SYM_HIERARCHY_STELLA_DELETED_OBJECTp = ((Symbol*)(internRigidSymbolWrtModule("DELETED-OBJECT?", NULL, 0)));
    SGT_HIERARCHY_STELLA_ABSTRACT_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("ABSTRACT-ITERATOR", NULL, 1)));
    SYM_HIERARCHY_STELLA_NEXTp = ((Symbol*)(internRigidSymbolWrtModule("NEXT?", NULL, 0)));
    SYM_HIERARCHY_STELLA_FIRST_ITERATIONp = ((Symbol*)(internRigidSymbolWrtModule("FIRST-ITERATION?", NULL, 0)));
    SYM_HIERARCHY_STELLA_VALUE = ((Symbol*)(internRigidSymbolWrtModule("VALUE", NULL, 0)));
    SYM_HIERARCHY_STELLA_OBJECT_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-ITERATOR", NULL, 0)));
    SGT_HIERARCHY_STELLA_CONS_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("CONS-ITERATOR", NULL, 1)));
    SYM_HIERARCHY_STELLA_CONS_ITERATOR_CURSOR = ((Symbol*)(internRigidSymbolWrtModule("CONS-ITERATOR-CURSOR", NULL, 0)));
    SGT_HIERARCHY_STELLA_LIST_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("LIST-ITERATOR", NULL, 1)));
    SYM_HIERARCHY_STELLA_LIST_ITERATOR_CURSOR = ((Symbol*)(internRigidSymbolWrtModule("LIST-ITERATOR-CURSOR", NULL, 0)));
    SYM_HIERARCHY_STELLA_LIST_ITERATOR_COLLECTION = ((Symbol*)(internRigidSymbolWrtModule("LIST-ITERATOR-COLLECTION", NULL, 0)));
    SGT_HIERARCHY_STELLA_DESTRUCTIVE_LIST_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("DESTRUCTIVE-LIST-ITERATOR", NULL, 1)));
    SYM_HIERARCHY_STELLA_THE_CONS_LIST = ((Symbol*)(internRigidSymbolWrtModule("THE-CONS-LIST", NULL, 0)));
    SGT_HIERARCHY_STELLA_ALL_PURPOSE_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("ALL-PURPOSE-ITERATOR", NULL, 1)));
    SYM_HIERARCHY_STELLA_KEY = ((Symbol*)(internRigidSymbolWrtModule("KEY", NULL, 0)));
    SYM_HIERARCHY_STELLA_ITERATOR_NEXT_CODE = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR-NEXT-CODE", NULL, 0)));
    SYM_HIERARCHY_STELLA_ITERATOR_FILTER_CODE = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR-FILTER-CODE", NULL, 0)));
    SYM_HIERARCHY_STELLA_ITERATOR_EMPTY_CODE = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR-EMPTY-CODE", NULL, 0)));
    SYM_HIERARCHY_STELLA_ITERATOR_NESTED_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR-NESTED-ITERATOR", NULL, 0)));
    SYM_HIERARCHY_STELLA_ITERATOR_CONS_LIST = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR-CONS-LIST", NULL, 0)));
    SYM_HIERARCHY_STELLA_ITERATOR_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR-OBJECT", NULL, 0)));
    SYM_HIERARCHY_STELLA_ITERATOR_SECOND_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR-SECOND-OBJECT", NULL, 0)));
    SYM_HIERARCHY_STELLA_ITERATOR_INTEGER = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR-INTEGER", NULL, 0)));
    SYM_HIERARCHY_STELLA_ITERATOR_SECOND_INTEGER = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR-SECOND-INTEGER", NULL, 0)));
    SGT_HIERARCHY_STELLA_TYPES_TO_CLASSES_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("TYPES-TO-CLASSES-ITERATOR", NULL, 1)));
    SYM_HIERARCHY_STELLA_ITERATOR_CURSOR = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR-CURSOR", NULL, 0)));
    SGT_HIERARCHY_STELLA_DICTIONARY_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("DICTIONARY-ITERATOR", NULL, 1)));
    SYM_HIERARCHY_STELLA_VALUE_SETTER = ((Symbol*)(internRigidSymbolWrtModule("VALUE-SETTER", NULL, 0)));
    SYM_HIERARCHY_STELLA_KEY_SETTER = ((Symbol*)(internRigidSymbolWrtModule("KEY-SETTER", NULL, 0)));
    SYM_HIERARCHY_STELLA_OBJECT_DICTIONARY_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-DICTIONARY-ITERATOR", NULL, 0)));
    SGT_HIERARCHY_STELLA_PROPERTY_LIST_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("PROPERTY-LIST-ITERATOR", NULL, 1)));
    SYM_HIERARCHY_STELLA_PLIST_ITERATOR_CURSOR = ((Symbol*)(internRigidSymbolWrtModule("PLIST-ITERATOR-CURSOR", NULL, 0)));
    SYM_HIERARCHY_STELLA_PLIST_ITERATOR_COLLECTION = ((Symbol*)(internRigidSymbolWrtModule("PLIST-ITERATOR-COLLECTION", NULL, 0)));
    SGT_HIERARCHY_STELLA_KV_LIST_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("KV-LIST-ITERATOR", NULL, 1)));
    SYM_HIERARCHY_STELLA_THE_KV_LIST = ((Symbol*)(internRigidSymbolWrtModule("THE-KV-LIST", NULL, 0)));
    SYM_HIERARCHY_STELLA_KV_LIST_ITERATOR_CURSOR = ((Symbol*)(internRigidSymbolWrtModule("KV-LIST-ITERATOR-CURSOR", NULL, 0)));
    SGT_HIERARCHY_STELLA_INTEGER_INTERVAL_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-INTERVAL-ITERATOR", NULL, 1)));
    SYM_HIERARCHY_STELLA_INTERVAL_CURSOR = ((Symbol*)(internRigidSymbolWrtModule("INTERVAL-CURSOR", NULL, 0)));
    SYM_HIERARCHY_STELLA_LOWER_BOUND = ((Symbol*)(internRigidSymbolWrtModule("LOWER-BOUND", NULL, 0)));
    SYM_HIERARCHY_STELLA_UPPER_BOUND = ((Symbol*)(internRigidSymbolWrtModule("UPPER-BOUND", NULL, 0)));
    SGT_HIERARCHY_STELLA_REVERSE_INTEGER_INTERVAL_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("REVERSE-INTEGER-INTERVAL-ITERATOR", NULL, 1)));
    SGT_HIERARCHY_STELLA_STRING_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("STRING-ITERATOR", NULL, 1)));
    SYM_HIERARCHY_STELLA_THE_STRING = ((Symbol*)(internRigidSymbolWrtModule("THE-STRING", NULL, 0)));
    SYM_HIERARCHY_STELLA_CURSOR = ((Symbol*)(internRigidSymbolWrtModule("CURSOR", NULL, 0)));
    SYM_HIERARCHY_STELLA_END = ((Symbol*)(internRigidSymbolWrtModule("END", NULL, 0)));
    SGT_HIERARCHY_STELLA_ABSTRACT_COLLECTION = ((Surrogate*)(internRigidSymbolWrtModule("ABSTRACT-COLLECTION", NULL, 1)));
    SYM_HIERARCHY_STELLA_ALLOCATE_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("ALLOCATE-ITERATOR", NULL, 0)));
    SYM_HIERARCHY_STELLA_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("LENGTH", NULL, 0)));
    SGT_HIERARCHY_STELLA_COLLECTION = ((Surrogate*)(internRigidSymbolWrtModule("COLLECTION", NULL, 1)));
    SYM_HIERARCHY_STELLA_INSERT = ((Symbol*)(internRigidSymbolWrtModule("INSERT", NULL, 0)));
  }
}

void helpStartupHierarchy2() {
  {
    SYM_HIERARCHY_STELLA_REMOVE = ((Symbol*)(internRigidSymbolWrtModule("REMOVE", NULL, 0)));
    SYM_HIERARCHY_STELLA_OBJECT_COLLECTION = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-COLLECTION", NULL, 0)));
    SGT_HIERARCHY_STELLA_SEQUENCE = ((Surrogate*)(internRigidSymbolWrtModule("SEQUENCE", NULL, 1)));
    SYM_HIERARCHY_STELLA_OBJECT_SEQUENCE = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-SEQUENCE", NULL, 0)));
    SGT_HIERARCHY_STELLA_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", NULL, 1)));
    SGT_HIERARCHY_STELLA_SET = ((Surrogate*)(internRigidSymbolWrtModule("SET", NULL, 1)));
    SGT_HIERARCHY_STELLA_CLASS_EXTENSION = ((Surrogate*)(internRigidSymbolWrtModule("CLASS-EXTENSION", NULL, 1)));
    SGT_HIERARCHY_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SYM_HIERARCHY_STELLA_REST = ((Symbol*)(internRigidSymbolWrtModule("REST", NULL, 0)));
    SGT_HIERARCHY_STELLA_ABSTRACT_DICTIONARY = ((Surrogate*)(internRigidSymbolWrtModule("ABSTRACT-DICTIONARY", NULL, 1)));
    SGT_HIERARCHY_STELLA_DICTIONARY = ((Surrogate*)(internRigidSymbolWrtModule("DICTIONARY", NULL, 1)));
    SYM_HIERARCHY_STELLA_LOOKUP = ((Symbol*)(internRigidSymbolWrtModule("LOOKUP", NULL, 0)));
    SYM_HIERARCHY_STELLA_INSERT_AT = ((Symbol*)(internRigidSymbolWrtModule("INSERT-AT", NULL, 0)));
    SYM_HIERARCHY_STELLA_OBJECT_TO_OBJECT_DICTIONARY = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-TO-OBJECT-DICTIONARY", NULL, 0)));
    SGT_HIERARCHY_STELLA_PROPERTY_LIST = ((Surrogate*)(internRigidSymbolWrtModule("PROPERTY-LIST", NULL, 1)));
    SYM_HIERARCHY_STELLA_THE_PLIST = ((Symbol*)(internRigidSymbolWrtModule("THE-PLIST", NULL, 0)));
    SGT_HIERARCHY_STELLA_KV_CONS = ((Surrogate*)(internRigidSymbolWrtModule("KV-CONS", NULL, 1)));
    SGT_HIERARCHY_STELLA_KEY_VALUE_LIST = ((Surrogate*)(internRigidSymbolWrtModule("KEY-VALUE-LIST", NULL, 1)));
    SGT_HIERARCHY_STELLA_RECYCLE_LIST = ((Surrogate*)(internRigidSymbolWrtModule("RECYCLE-LIST", NULL, 1)));
    SYM_HIERARCHY_STELLA_RECYCLE_LIST_OF = ((Symbol*)(internRigidSymbolWrtModule("RECYCLE-LIST-OF", NULL, 0)));
    SYM_HIERARCHY_STELLA_RECYCLED_ITEMS = ((Symbol*)(internRigidSymbolWrtModule("RECYCLED-ITEMS", NULL, 0)));
    SYM_HIERARCHY_STELLA_LIST_OF_RECYCLED_ITEMS = ((Symbol*)(internRigidSymbolWrtModule("LIST-OF-RECYCLED-ITEMS", NULL, 0)));
    SYM_HIERARCHY_STELLA_ALL_ITEMS = ((Symbol*)(internRigidSymbolWrtModule("ALL-ITEMS", NULL, 0)));
    SYM_HIERARCHY_STELLA_UNUSED_ITEMS = ((Symbol*)(internRigidSymbolWrtModule("UNUSED-ITEMS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CURRENT_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("CURRENT-LENGTH", NULL, 0)));
    SYM_HIERARCHY_STELLA_ITEM_SIZE = ((Symbol*)(internRigidSymbolWrtModule("ITEM-SIZE", NULL, 0)));
    SYM_HIERARCHY_STELLA_THE_STELLA_HASH_TABLE = ((Symbol*)(internRigidSymbolWrtModule("THE-STELLA-HASH-TABLE", NULL, 0)));
    SGT_HIERARCHY_STELLA_HASH_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("HASH-TABLE", NULL, 1)));
    SYM_HIERARCHY_STELLA_OBJECT_TO_OBJECT_HASH_TABLE = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-TO-OBJECT-HASH-TABLE", NULL, 0)));
    SGT_HIERARCHY_STELLA_INTEGER_HASH_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-HASH-TABLE", NULL, 1)));
    SGT_HIERARCHY_STELLA_FLOAT_HASH_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT-HASH-TABLE", NULL, 1)));
    SGT_HIERARCHY_STELLA_STRING_HASH_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("STRING-HASH-TABLE", NULL, 1)));
    SGT_HIERARCHY_STELLA_STRING_TO_INTEGER_HASH_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("STRING-TO-INTEGER-HASH-TABLE", NULL, 1)));
    SGT_HIERARCHY_STELLA_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("VECTOR", NULL, 1)));
    SYM_HIERARCHY_STELLA_ARRAY_SIZE = ((Symbol*)(internRigidSymbolWrtModule("ARRAY-SIZE", NULL, 0)));
    SGT_HIERARCHY_STELLA_EXTENSIBLE_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("EXTENSIBLE-VECTOR", NULL, 1)));
    SGT_HIERARCHY_STELLA_EXTENSIBLE_SYMBOL_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("EXTENSIBLE-SYMBOL-ARRAY", NULL, 1)));
    SYM_HIERARCHY_STELLA_TOP_SYMBOL_OFFSET = ((Symbol*)(internRigidSymbolWrtModule("TOP-SYMBOL-OFFSET", NULL, 0)));
    SYM_HIERARCHY_STELLA_POTENTIAL_FREE_SYMBOL_OFFSET = ((Symbol*)(internRigidSymbolWrtModule("POTENTIAL-FREE-SYMBOL-OFFSET", NULL, 0)));
    SGT_HIERARCHY_STELLA_VECTOR_SEQUENCE = ((Surrogate*)(internRigidSymbolWrtModule("VECTOR-SEQUENCE", NULL, 1)));
    SYM_HIERARCHY_STELLA_SEQUENCE_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("SEQUENCE-LENGTH", NULL, 0)));
    SGT_HIERARCHY_STELLA_CUSTOM_VECTOR_SEQUENCE = ((Surrogate*)(internRigidSymbolWrtModule("CUSTOM-VECTOR-SEQUENCE", NULL, 1)));
    SYM_HIERARCHY_STELLA_RESIZE_FACTOR = ((Symbol*)(internRigidSymbolWrtModule("RESIZE-FACTOR", NULL, 0)));
    SGT_HIERARCHY_STELLA_BOOLEAN_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN-VECTOR", NULL, 1)));
    SGT_HIERARCHY_STELLA_INTEGER_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-VECTOR", NULL, 1)));
    SGT_HIERARCHY_STELLA_ACTIVE_LIST = ((Surrogate*)(internRigidSymbolWrtModule("ACTIVE-LIST", NULL, 1)));
    SGT_HIERARCHY_STELLA_ACTIVE_SET = ((Surrogate*)(internRigidSymbolWrtModule("ACTIVE-SET", NULL, 1)));
    SGT_HIERARCHY_STELLA_DEMON = ((Surrogate*)(internRigidSymbolWrtModule("DEMON", NULL, 1)));
    SYM_HIERARCHY_STELLA_DEMON_NAME = ((Symbol*)(internRigidSymbolWrtModule("DEMON-NAME", NULL, 0)));
    SYM_HIERARCHY_STELLA_DEMON_ACTION = ((Symbol*)(internRigidSymbolWrtModule("DEMON-ACTION", NULL, 0)));
    SYM_HIERARCHY_STELLA_DEMON_CLASS_REFS = ((Symbol*)(internRigidSymbolWrtModule("DEMON-CLASS-REFS", NULL, 0)));
    SYM_HIERARCHY_STELLA_DEMON_SLOT_REFS = ((Symbol*)(internRigidSymbolWrtModule("DEMON-SLOT-REFS", NULL, 0)));
    SYM_HIERARCHY_STELLA_DEMON_CODE = ((Symbol*)(internRigidSymbolWrtModule("DEMON-CODE", NULL, 0)));
    SYM_HIERARCHY_STELLA_DEMON_METHOD = ((Symbol*)(internRigidSymbolWrtModule("DEMON-METHOD", NULL, 0)));
    SYM_HIERARCHY_STELLA_DEMON_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DEMON-DOCUMENTATION", NULL, 0)));
    SYM_HIERARCHY_STELLA_DEMON_GUARDp = ((Symbol*)(internRigidSymbolWrtModule("DEMON-GUARD?", NULL, 0)));
    SYM_HIERARCHY_STELLA_DEMON_ALLp = ((Symbol*)(internRigidSymbolWrtModule("DEMON-ALL?", NULL, 0)));
    SYM_HIERARCHY_STELLA_DEMON_INHERITp = ((Symbol*)(internRigidSymbolWrtModule("DEMON-INHERIT?", NULL, 0)));
    SGT_HIERARCHY_STELLA_KEYWORD_KEY_VALUE_LIST = ((Surrogate*)(internRigidSymbolWrtModule("KEYWORD-KEY-VALUE-LIST", NULL, 1)));
    SYM_HIERARCHY_STELLA_SYMBOL_NAME = ((Symbol*)(internRigidSymbolWrtModule("SYMBOL-NAME", NULL, 0)));
  }
}

void helpStartupHierarchy3() {
  {
    SYM_HIERARCHY_STELLA_SYMBOL_ID = ((Symbol*)(internRigidSymbolWrtModule("SYMBOL-ID", NULL, 0)));
    SGT_HIERARCHY_STELLA_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("SYMBOL", NULL, 1)));
    SYM_HIERARCHY_STELLA_SYMBOL_SLOT_OFFSET = ((Symbol*)(internRigidSymbolWrtModule("SYMBOL-SLOT-OFFSET", NULL, 0)));
    SYM_HIERARCHY_STELLA_SYMBOL_VALUE_AND_PLIST = ((Symbol*)(internRigidSymbolWrtModule("SYMBOL-VALUE-AND-PLIST", NULL, 0)));
    SGT_HIERARCHY_STELLA_SURROGATE = ((Surrogate*)(internRigidSymbolWrtModule("SURROGATE", NULL, 1)));
    SYM_HIERARCHY_STELLA_SURROGATE_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SURROGATE-VALUE", NULL, 0)));
    SYM_HIERARCHY_STELLA_TYPE_CLASS = ((Symbol*)(internRigidSymbolWrtModule("TYPE-CLASS", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOTREF_SLOT = ((Symbol*)(internRigidSymbolWrtModule("SLOTREF-SLOT", NULL, 0)));
    SYM_HIERARCHY_STELLA_TYPE = ((Symbol*)(internRigidSymbolWrtModule("TYPE", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOTREF = ((Symbol*)(internRigidSymbolWrtModule("SLOTREF", NULL, 0)));
    SGT_HIERARCHY_STELLA_KEYWORD = ((Surrogate*)(internRigidSymbolWrtModule("KEYWORD", NULL, 1)));
    SGT_HIERARCHY_STELLA_TRANSIENT_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("TRANSIENT-SYMBOL", NULL, 1)));
    SYM_HIERARCHY_STELLA_PROJECTS_ONTO = ((Symbol*)(internRigidSymbolWrtModule("PROJECTS-ONTO", NULL, 0)));
    SYM_HIERARCHY_STELLA_PROJECTED_FROM = ((Symbol*)(internRigidSymbolWrtModule("PROJECTED-FROM", NULL, 0)));
    SGT_HIERARCHY_STELLA_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("RELATION", NULL, 1)));
    SYM_HIERARCHY_STELLA_NAME = ((Symbol*)(internRigidSymbolWrtModule("NAME", NULL, 0)));
    SYM_HIERARCHY_STELLA_ARITY = ((Symbol*)(internRigidSymbolWrtModule("ARITY", NULL, 0)));
    SYM_HIERARCHY_STELLA_PUBLICp = ((Symbol*)(internRigidSymbolWrtModule("PUBLIC?", NULL, 0)));
    SYM_HIERARCHY_STELLA_DIRECT_SUPERS = ((Symbol*)(internRigidSymbolWrtModule("DIRECT-SUPERS", NULL, 0)));
    SYM_HIERARCHY_STELLA_ALL_SUPERS = ((Symbol*)(internRigidSymbolWrtModule("ALL-SUPERS", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOTS = ((Symbol*)(internRigidSymbolWrtModule("SLOTS", NULL, 0)));
    SYM_HIERARCHY_STELLA_PROPERTIES = ((Symbol*)(internRigidSymbolWrtModule("PROPERTIES", NULL, 0)));
    SYM_HIERARCHY_STELLA_ABSTRACTp = ((Symbol*)(internRigidSymbolWrtModule("ABSTRACT?", NULL, 0)));
    SGT_HIERARCHY_STELLA_CLASS = ((Surrogate*)(internRigidSymbolWrtModule("CLASS", NULL, 1)));
    SYM_HIERARCHY_STELLA_STORED_ACTIVEp = ((Symbol*)(internRigidSymbolWrtModule("STORED-ACTIVE?", NULL, 0)));
    SGT_HIERARCHY_STELLA_ACTIVE_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("ACTIVE-OBJECT", NULL, 1)));
    SYM_HIERARCHY_STELLA_ACTIVEp = ((Symbol*)(internRigidSymbolWrtModule("ACTIVE?", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_CREATOR = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CREATOR", NULL, 0)));
    SYM_HIERARCHY_STELLA_CREATOR = ((Symbol*)(internRigidSymbolWrtModule("CREATOR", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_INITIALIZER = ((Symbol*)(internRigidSymbolWrtModule("CLASS-INITIALIZER", NULL, 0)));
    SYM_HIERARCHY_STELLA_INITIALIZER = ((Symbol*)(internRigidSymbolWrtModule("INITIALIZER", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_TERMINATOR = ((Symbol*)(internRigidSymbolWrtModule("CLASS-TERMINATOR", NULL, 0)));
    SYM_HIERARCHY_STELLA_TERMINATOR = ((Symbol*)(internRigidSymbolWrtModule("TERMINATOR", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_DESTRUCTOR = ((Symbol*)(internRigidSymbolWrtModule("CLASS-DESTRUCTOR", NULL, 0)));
    SYM_HIERARCHY_STELLA_DESTRUCTOR = ((Symbol*)(internRigidSymbolWrtModule("DESTRUCTOR", NULL, 0)));
    SYM_HIERARCHY_STELLA_REQUIRED_SLOTS = ((Symbol*)(internRigidSymbolWrtModule("REQUIRED-SLOTS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_PARAMETERS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-PARAMETERS", NULL, 0)));
    SYM_HIERARCHY_STELLA_PARAMETERS = ((Symbol*)(internRigidSymbolWrtModule("PARAMETERS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_INITIAL_VALUE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-INITIAL-VALUE", NULL, 0)));
    SYM_HIERARCHY_STELLA_INITIAL_VALUE = ((Symbol*)(internRigidSymbolWrtModule("INITIAL-VALUE", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_EXTENSION = ((Symbol*)(internRigidSymbolWrtModule("CLASS-EXTENSION", NULL, 0)));
    SYM_HIERARCHY_STELLA_EXTENSION = ((Symbol*)(internRigidSymbolWrtModule("EXTENSION", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_CL_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CL-NATIVE-TYPE", NULL, 0)));
    SYM_HIERARCHY_STELLA_CL_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CL-NATIVE-TYPE", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_CPP_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CPP-NATIVE-TYPE", NULL, 0)));
    SYM_HIERARCHY_STELLA_CPP_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CPP-NATIVE-TYPE", NULL, 0)));
    SYM_HIERARCHY_STELLA_IDL_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("IDL-NATIVE-TYPE", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_JAVA_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-JAVA-NATIVE-TYPE", NULL, 0)));
    SYM_HIERARCHY_STELLA_JAVA_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("JAVA-NATIVE-TYPE", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_CL_STRUCT_SLOTS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CL-STRUCT-SLOTS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_RECYCLE_METHOD = ((Symbol*)(internRigidSymbolWrtModule("CLASS-RECYCLE-METHOD", NULL, 0)));
    KWD_HIERARCHY_NONE = ((Keyword*)(internRigidSymbolWrtModule("NONE", NULL, 2)));
    SYM_HIERARCHY_STELLA_CLASS_REQUIRED_SLOT_NAMES = ((Symbol*)(internRigidSymbolWrtModule("CLASS-REQUIRED-SLOT-NAMES", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-GUARD-CONSTRUCTOR-DEMONS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_CONSTRUCTOR_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CONSTRUCTOR-DEMONS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-GUARD-DESTRUCTOR-DEMONS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_DESTRUCTOR_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-DESTRUCTOR-DEMONS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_KEY = ((Symbol*)(internRigidSymbolWrtModule("CLASS-KEY", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_SYNONYMS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-SYNONYMS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CL_STRUCTp = ((Symbol*)(internRigidSymbolWrtModule("CL-STRUCT?", NULL, 0)));
  }
}

void helpStartupHierarchy4() {
  {
    SYM_HIERARCHY_STELLA_MIXINp = ((Symbol*)(internRigidSymbolWrtModule("MIXIN?", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-TYPE", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_ARITY = ((Symbol*)(internRigidSymbolWrtModule("CLASS-ARITY", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_DIRECT_SUPERS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-DIRECT-SUPERS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_DIRECT_SUBS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-DIRECT-SUBS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_ALL_SUPER_CLASSES = ((Symbol*)(internRigidSymbolWrtModule("CLASS-ALL-SUPER-CLASSES", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_ALL_SLOTS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-ALL-SLOTS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_LOCAL_SLOTS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-LOCAL-SLOTS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_SLOT_AND_METHOD_CACHE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-SLOT-AND-METHOD-CACHE", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_MIXINp = ((Symbol*)(internRigidSymbolWrtModule("CLASS-MIXIN?", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_COLLECTIONp = ((Symbol*)(internRigidSymbolWrtModule("CLASS-COLLECTION?", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_CL_STRUCTp = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CL-STRUCT?", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_PUBLICp = ((Symbol*)(internRigidSymbolWrtModule("CLASS-PUBLIC?", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_FINALIZEDp = ((Symbol*)(internRigidSymbolWrtModule("CLASS-FINALIZED?", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_SLOTS_FINALIZEDp = ((Symbol*)(internRigidSymbolWrtModule("CLASS-SLOTS-FINALIZED?", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_STRINGIFIED_SOURCE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-STRINGIFIED-SOURCE", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_CONSTRUCTOR_CODE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CONSTRUCTOR-CODE", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_SLOT_ACCESSOR_CODE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-SLOT-ACCESSOR-CODE", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_MARKEDp = ((Symbol*)(internRigidSymbolWrtModule("CLASS-MARKED?", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_TAXONOMY_NODE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-TAXONOMY-NODE", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("CLASS-DOCUMENTATION", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLASS_PRINT_FORM = ((Symbol*)(internRigidSymbolWrtModule("CLASS-PRINT-FORM", NULL, 0)));
    SYM_HIERARCHY_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 0)));
    SYM_HIERARCHY_STELLA_PRINT_FORM = ((Symbol*)(internRigidSymbolWrtModule("PRINT-FORM", NULL, 0)));
    SGT_HIERARCHY_STELLA_POLYMORPHIC_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("POLYMORPHIC-RELATION", NULL, 1)));
    SYM_HIERARCHY_STELLA_OWNER = ((Symbol*)(internRigidSymbolWrtModule("OWNER", NULL, 0)));
    SYM_HIERARCHY_STELLA_RENAMES = ((Symbol*)(internRigidSymbolWrtModule("RENAMES", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_DIRECT_EQUIVALENT = ((Symbol*)(internRigidSymbolWrtModule("SLOT-DIRECT-EQUIVALENT", NULL, 0)));
    SGT_HIERARCHY_STELLA_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("SLOT", NULL, 1)));
    SYM_HIERARCHY_STELLA_SLOT_TYPE_SPECIFIER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-TYPE-SPECIFIER", NULL, 0)));
    SYM_HIERARCHY_STELLA_TYPE_SPECIFIER = ((Symbol*)(internRigidSymbolWrtModule("TYPE-SPECIFIER", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_HOME_MODULE = ((Symbol*)(internRigidSymbolWrtModule("SLOT-HOME-MODULE", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_RENAMES = ((Symbol*)(internRigidSymbolWrtModule("SLOT-RENAMES", NULL, 0)));
    SYM_HIERARCHY_STELLA_COLLECTION_VALUEDp = ((Symbol*)(internRigidSymbolWrtModule("COLLECTION-VALUED?", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_CLOSURE_ASSUMPTION = ((Symbol*)(internRigidSymbolWrtModule("SLOT-CLOSURE-ASSUMPTION", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLOSURE_ASSUMPTION = ((Symbol*)(internRigidSymbolWrtModule("CLOSURE-ASSUMPTION", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_DIRECT_SUPERS = ((Symbol*)(internRigidSymbolWrtModule("SLOT-DIRECT-SUPERS", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_DIRECT_SUBS = ((Symbol*)(internRigidSymbolWrtModule("SLOT-DIRECT-SUBS", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_NAME = ((Symbol*)(internRigidSymbolWrtModule("SLOT-NAME", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_OWNER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-OWNER", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_BASE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("SLOT-BASE-TYPE", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_SLOTREF = ((Symbol*)(internRigidSymbolWrtModule("SLOT-SLOTREF", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_PUBLICp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-PUBLIC?", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_RENAMEDp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-RENAMED?", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_EXTERNALp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-EXTERNAL?", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_MARKEDp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-MARKED?", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("SLOT-DOCUMENTATION", NULL, 0)));
    SGT_HIERARCHY_STELLA_STORAGE_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("STORAGE-SLOT", NULL, 1)));
    SYM_HIERARCHY_STELLA_SLOT_ALLOCATION = ((Symbol*)(internRigidSymbolWrtModule("SLOT-ALLOCATION", NULL, 0)));
    KWD_HIERARCHY_INSTANCE = ((Keyword*)(internRigidSymbolWrtModule("INSTANCE", NULL, 2)));
    SYM_HIERARCHY_STELLA_ALLOCATION = ((Symbol*)(internRigidSymbolWrtModule("ALLOCATION", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_DEFAULT_EXPRESSION = ((Symbol*)(internRigidSymbolWrtModule("SLOT-DEFAULT-EXPRESSION", NULL, 0)));
    SYM_HIERARCHY_STELLA_DEFAULT_FORM = ((Symbol*)(internRigidSymbolWrtModule("DEFAULT-FORM", NULL, 0)));
    SYM_HIERARCHY_STELLA_REQUIREDp = ((Symbol*)(internRigidSymbolWrtModule("REQUIRED?", NULL, 0)));
    SYM_HIERARCHY_STELLA_COMPONENTp = ((Symbol*)(internRigidSymbolWrtModule("COMPONENT?", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_READER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-READER", NULL, 0)));
    SYM_HIERARCHY_STELLA_READER = ((Symbol*)(internRigidSymbolWrtModule("READER", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_WRITER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-WRITER", NULL, 0)));
    SYM_HIERARCHY_STELLA_WRITER = ((Symbol*)(internRigidSymbolWrtModule("WRITER", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_GUARD_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("SLOT-GUARD-DEMONS", NULL, 0)));
  }
}

void helpStartupHierarchy5() {
  {
    SYM_HIERARCHY_STELLA_SLOT_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("SLOT-DEMONS", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_REQUIREDp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-REQUIRED?", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_COMPONENTp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-COMPONENT?", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_READ_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-READ-ONLY?", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_HARDWIREDp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-HARDWIRED?", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_CONTEXT_SENSITIVEp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-CONTEXT-SENSITIVE?", NULL, 0)));
    SGT_HIERARCHY_STELLA_METHOD_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-SLOT", NULL, 1)));
    SYM_HIERARCHY_STELLA_SETTERp = ((Symbol*)(internRigidSymbolWrtModule("SETTER?", NULL, 0)));
    SYM_HIERARCHY_STELLA_METHOD_PARAMETER_DIRECTIONS = ((Symbol*)(internRigidSymbolWrtModule("METHOD-PARAMETER-DIRECTIONS", NULL, 0)));
    SYM_HIERARCHY_STELLA_METHOD_INLINED_FUNCTIONS = ((Symbol*)(internRigidSymbolWrtModule("METHOD-INLINED-FUNCTIONS", NULL, 0)));
    SYM_HIERARCHY_STELLA_METHOD_EVALUATE_ARGUMENTSp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-EVALUATE-ARGUMENTS?", NULL, 0)));
    SYM_HIERARCHY_STELLA_METHOD_SETTERp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-SETTER?", NULL, 0)));
    SYM_HIERARCHY_STELLA_METHOD_PARAMETER_NAMES = ((Symbol*)(internRigidSymbolWrtModule("METHOD-PARAMETER-NAMES", NULL, 0)));
    SYM_HIERARCHY_STELLA_METHOD_PARAMETER_TYPE_SPECIFIERS = ((Symbol*)(internRigidSymbolWrtModule("METHOD-PARAMETER-TYPE-SPECIFIERS", NULL, 0)));
    SYM_HIERARCHY_STELLA_METHOD_RETURN_TYPE_SPECIFIERS = ((Symbol*)(internRigidSymbolWrtModule("METHOD-RETURN-TYPE-SPECIFIERS", NULL, 0)));
    SYM_HIERARCHY_STELLA_METHOD_STRINGIFIED_SOURCE = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STRINGIFIED-SOURCE", NULL, 0)));
    SYM_HIERARCHY_STELLA_METHOD_CODE = ((Symbol*)(internRigidSymbolWrtModule("METHOD-CODE", NULL, 0)));
    SYM_HIERARCHY_STELLA_FUNCTION_CODE = ((Symbol*)(internRigidSymbolWrtModule("FUNCTION-CODE", NULL, 0)));
    SYM_HIERARCHY_STELLA_METHOD_FUNCTIONp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-FUNCTION?", NULL, 0)));
    SYM_HIERARCHY_STELLA_METHOD_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("METHOD-DOCUMENTATION", NULL, 0)));
    SYM_HIERARCHY_STELLA_METHOD_AUXILIARYp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-AUXILIARY?", NULL, 0)));
    SYM_HIERARCHY_STELLA_METHOD_STORAGE_SLOT = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STORAGE-SLOT", NULL, 0)));
    SYM_HIERARCHY_STELLA_SLOT_AUXILIARYp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-AUXILIARY?", NULL, 0)));
    SYM_HIERARCHY_STELLA_STORAGE_SLOT = ((Symbol*)(internRigidSymbolWrtModule("STORAGE-SLOT", NULL, 0)));
    SYM_HIERARCHY_STELLA_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("FUNCTION", NULL, 0)));
    SGT_HIERARCHY_STELLA_PARAMETRIC_TYPE_SPECIFIER = ((Surrogate*)(internRigidSymbolWrtModule("PARAMETRIC-TYPE-SPECIFIER", NULL, 1)));
    SYM_HIERARCHY_STELLA_SPECIFIER_BASE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("SPECIFIER-BASE-TYPE", NULL, 0)));
    SYM_HIERARCHY_STELLA_SPECIFIER_PARAMETER_TYPES = ((Symbol*)(internRigidSymbolWrtModule("SPECIFIER-PARAMETER-TYPES", NULL, 0)));
    SYM_HIERARCHY_STELLA_SPECIFIER_DIMENSIONS = ((Symbol*)(internRigidSymbolWrtModule("SPECIFIER-DIMENSIONS", NULL, 0)));
    SGT_HIERARCHY_STELLA_ANCHORED_TYPE_SPECIFIER = ((Surrogate*)(internRigidSymbolWrtModule("ANCHORED-TYPE-SPECIFIER", NULL, 1)));
    SYM_HIERARCHY_STELLA_SPECIFIER_PARAMETER_NAME = ((Symbol*)(internRigidSymbolWrtModule("SPECIFIER-PARAMETER-NAME", NULL, 0)));
    SGT_HIERARCHY_STELLA_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("TABLE", NULL, 1)));
    SYM_HIERARCHY_STELLA_TUPLE_DOMAINS = ((Symbol*)(internRigidSymbolWrtModule("TUPLE-DOMAINS", NULL, 0)));
    SGT_HIERARCHY_STELLA_GLOBAL_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("GLOBAL-VARIABLE", NULL, 1)));
    SYM_HIERARCHY_STELLA_VARIABLE_HOME_MODULE = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-HOME-MODULE", NULL, 0)));
    SYM_HIERARCHY_STELLA_VARIABLE_NAME = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-NAME", NULL, 0)));
    SYM_HIERARCHY_STELLA_VARIABLE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-TYPE", NULL, 0)));
    SYM_HIERARCHY_STELLA_VARIABLE_SPECIALp = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-SPECIAL?", NULL, 0)));
    SYM_HIERARCHY_STELLA_VARIABLE_CONSTANTp = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-CONSTANT?", NULL, 0)));
    SYM_HIERARCHY_STELLA_VARIABLE_PUBLICp = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-PUBLIC?", NULL, 0)));
    SYM_HIERARCHY_STELLA_VARIABLE_AUXILIARYp = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-AUXILIARY?", NULL, 0)));
    SYM_HIERARCHY_STELLA_VARIABLE_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-DOCUMENTATION", NULL, 0)));
    SYM_HIERARCHY_STELLA_VARIABLE_STRINGIFIED_SOURCE = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-STRINGIFIED-SOURCE", NULL, 0)));
    SGT_HIERARCHY_STELLA_QUOTED_EXPRESSION = ((Surrogate*)(internRigidSymbolWrtModule("QUOTED-EXPRESSION", NULL, 1)));
    SYM_HIERARCHY_STELLA_QUOTATION_TABLE_OFFSET = ((Symbol*)(internRigidSymbolWrtModule("QUOTATION-TABLE-OFFSET", NULL, 0)));
    SYM_HIERARCHY_STELLA_SURROGATE_VALUE_INVERSE = ((Symbol*)(internRigidSymbolWrtModule("SURROGATE-VALUE-INVERSE", NULL, 0)));
    SGT_HIERARCHY_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", NULL, 1)));
    SGT_HIERARCHY_STELLA_WORLD = ((Surrogate*)(internRigidSymbolWrtModule("WORLD", NULL, 1)));
    SYM_HIERARCHY_STELLA_WORLD_NAME = ((Symbol*)(internRigidSymbolWrtModule("WORLD-NAME", NULL, 0)));
    SGT_HIERARCHY_STELLA_CONTEXT = ((Surrogate*)(internRigidSymbolWrtModule("CONTEXT", NULL, 1)));
    SYM_HIERARCHY_STELLA_CONTEXT_NAME = ((Symbol*)(internRigidSymbolWrtModule("CONTEXT-NAME", NULL, 0)));
    SYM_HIERARCHY_STELLA_CHILD_CONTEXTS = ((Symbol*)(internRigidSymbolWrtModule("CHILD-CONTEXTS", NULL, 0)));
    SYM_HIERARCHY_STELLA_BASE_MODULE = ((Symbol*)(internRigidSymbolWrtModule("BASE-MODULE", NULL, 0)));
    SYM_HIERARCHY_STELLA_ALL_SUPER_CONTEXTS = ((Symbol*)(internRigidSymbolWrtModule("ALL-SUPER-CONTEXTS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CONTEXT_NUMBER = ((Symbol*)(internRigidSymbolWrtModule("CONTEXT-NUMBER", NULL, 0)));
    SYM_HIERARCHY_STELLA_PARENT_MODULE = ((Symbol*)(internRigidSymbolWrtModule("PARENT-MODULE", NULL, 0)));
    SYM_HIERARCHY_STELLA_MODULE_LISP_PACKAGE = ((Symbol*)(internRigidSymbolWrtModule("MODULE-LISP-PACKAGE", NULL, 0)));
    SYM_HIERARCHY_STELLA_LISP_PACKAGE = ((Symbol*)(internRigidSymbolWrtModule("LISP-PACKAGE", NULL, 0)));
    SYM_HIERARCHY_STELLA_MODULE_CPP_PACKAGE = ((Symbol*)(internRigidSymbolWrtModule("MODULE-CPP-PACKAGE", NULL, 0)));
    SYM_HIERARCHY_STELLA_CPP_PACKAGE = ((Symbol*)(internRigidSymbolWrtModule("CPP-PACKAGE", NULL, 0)));
  }
}

void helpStartupHierarchy6() {
  {
    SYM_HIERARCHY_STELLA_SHADOWED_SURROGATES = ((Symbol*)(internRigidSymbolWrtModule("SHADOWED-SURROGATES", NULL, 0)));
    SYM_HIERARCHY_STELLA_JAVA_PACKAGE = ((Symbol*)(internRigidSymbolWrtModule("JAVA-PACKAGE", NULL, 0)));
    SYM_HIERARCHY_STELLA_CLEARABLEp = ((Symbol*)(internRigidSymbolWrtModule("CLEARABLE?", NULL, 0)));
    SYM_HIERARCHY_STELLA_PROTECT_SURROGATESp = ((Symbol*)(internRigidSymbolWrtModule("PROTECT-SURROGATES?", NULL, 0)));
    SYM_HIERARCHY_STELLA_PARENT_MODULES = ((Symbol*)(internRigidSymbolWrtModule("PARENT-MODULES", NULL, 0)));
    SYM_HIERARCHY_STELLA_NICKNAMES = ((Symbol*)(internRigidSymbolWrtModule("NICKNAMES", NULL, 0)));
    SYM_HIERARCHY_STELLA_USES = ((Symbol*)(internRigidSymbolWrtModule("USES", NULL, 0)));
    SYM_HIERARCHY_STELLA_USED_BY = ((Symbol*)(internRigidSymbolWrtModule("USED-BY", NULL, 0)));
    SYM_HIERARCHY_STELLA_REQUIRES = ((Symbol*)(internRigidSymbolWrtModule("REQUIRES", NULL, 0)));
    SYM_HIERARCHY_STELLA_CASE_SENSITIVEp = ((Symbol*)(internRigidSymbolWrtModule("CASE-SENSITIVE?", NULL, 0)));
    SYM_HIERARCHY_STELLA_MODULE_FULL_NAME = ((Symbol*)(internRigidSymbolWrtModule("MODULE-FULL-NAME", NULL, 0)));
    SYM_HIERARCHY_STELLA_MODULE_NAME = ((Symbol*)(internRigidSymbolWrtModule("MODULE-NAME", NULL, 0)));
    SYM_HIERARCHY_STELLA_MODULE_STRINGIFIED_SOURCE = ((Symbol*)(internRigidSymbolWrtModule("MODULE-STRINGIFIED-SOURCE", NULL, 0)));
    SYM_HIERARCHY_STELLA_STRINGIFIED_OPTIONS = ((Symbol*)(internRigidSymbolWrtModule("STRINGIFIED-OPTIONS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CARDINAL_MODULE = ((Symbol*)(internRigidSymbolWrtModule("CARDINAL-MODULE", NULL, 0)));
    SYM_HIERARCHY_STELLA_SYMBOL_OFFSET_TABLE = ((Symbol*)(internRigidSymbolWrtModule("SYMBOL-OFFSET-TABLE", NULL, 0)));
    SYM_HIERARCHY_STELLA_SURROGATE_OFFSET_TABLE = ((Symbol*)(internRigidSymbolWrtModule("SURROGATE-OFFSET-TABLE", NULL, 0)));
    SYM_HIERARCHY_STELLA_STRICT_INFERENCE_CACHE = ((Symbol*)(internRigidSymbolWrtModule("STRICT-INFERENCE-CACHE", NULL, 0)));
    SYM_HIERARCHY_STELLA_DEFAULT_INFERENCE_CACHE = ((Symbol*)(internRigidSymbolWrtModule("DEFAULT-INFERENCE-CACHE", NULL, 0)));
    SYM_HIERARCHY_STELLA_PROTOTYPE_INFERENCE_CACHE = ((Symbol*)(internRigidSymbolWrtModule("PROTOTYPE-INFERENCE-CACHE", NULL, 0)));
    SYM_HIERARCHY_STELLA_PARENT_CONTEXT = ((Symbol*)(internRigidSymbolWrtModule("PARENT-CONTEXT", NULL, 0)));
    SGT_HIERARCHY_STELLA_CS_VALUE = ((Surrogate*)(internRigidSymbolWrtModule("CS-VALUE", NULL, 1)));
    SGT_HIERARCHY_STELLA_INTERVAL = ((Surrogate*)(internRigidSymbolWrtModule("INTERVAL", NULL, 1)));
    SGT_HIERARCHY_STELLA_TAXONOMY_NODE = ((Surrogate*)(internRigidSymbolWrtModule("TAXONOMY-NODE", NULL, 1)));
    SYM_HIERARCHY_STELLA_NATIVE_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("NATIVE-OBJECT", NULL, 0)));
    SYM_HIERARCHY_STELLA_LABEL = ((Symbol*)(internRigidSymbolWrtModule("LABEL", NULL, 0)));
    SYM_HIERARCHY_STELLA_INTERVALS = ((Symbol*)(internRigidSymbolWrtModule("INTERVALS", NULL, 0)));
    SYM_HIERARCHY_STELLA_INITIAL_INTERVAL = ((Symbol*)(internRigidSymbolWrtModule("INITIAL-INTERVAL", NULL, 0)));
    SYM_HIERARCHY_STELLA_FIRST_INTERVAL_LOWER_BOUND = ((Symbol*)(internRigidSymbolWrtModule("FIRST-INTERVAL-LOWER-BOUND", NULL, 0)));
    SYM_HIERARCHY_STELLA_FIRST_INTERVAL_UPPER_BOUND = ((Symbol*)(internRigidSymbolWrtModule("FIRST-INTERVAL-UPPER-BOUND", NULL, 0)));
    SYM_HIERARCHY_STELLA_PARENTS = ((Symbol*)(internRigidSymbolWrtModule("PARENTS", NULL, 0)));
    SYM_HIERARCHY_STELLA_CHILDREN = ((Symbol*)(internRigidSymbolWrtModule("CHILDREN", NULL, 0)));
    SYM_HIERARCHY_STELLA_TOTAL_ANCESTORS = ((Symbol*)(internRigidSymbolWrtModule("TOTAL-ANCESTORS", NULL, 0)));
    SYM_HIERARCHY_STELLA_TREE_CHILDREN = ((Symbol*)(internRigidSymbolWrtModule("TREE-CHILDREN", NULL, 0)));
    SYM_HIERARCHY_STELLA_MARKER = ((Symbol*)(internRigidSymbolWrtModule("MARKER", NULL, 0)));
    SGT_HIERARCHY_STELLA_TAXONOMY_GRAPH = ((Surrogate*)(internRigidSymbolWrtModule("TAXONOMY-GRAPH", NULL, 1)));
    SYM_HIERARCHY_STELLA_RENUMBER_IF_OUT_OF_NUMBERSp = ((Symbol*)(internRigidSymbolWrtModule("RENUMBER-IF-OUT-OF-NUMBERS?", NULL, 0)));
    SYM_HIERARCHY_STELLA_RENUMBER_RATIO = ((Symbol*)(internRigidSymbolWrtModule("RENUMBER-RATIO", NULL, 0)));
    SYM_HIERARCHY_STELLA_INCREMENTAL_MODEp = ((Symbol*)(internRigidSymbolWrtModule("INCREMENTAL-MODE?", NULL, 0)));
    SYM_HIERARCHY_STELLA_LARGEST_POSTORDER_NUMBER = ((Symbol*)(internRigidSymbolWrtModule("LARGEST-POSTORDER-NUMBER", NULL, 0)));
    SYM_HIERARCHY_STELLA_NUMBER_OF_NODES = ((Symbol*)(internRigidSymbolWrtModule("NUMBER-OF-NODES", NULL, 0)));
    SYM_HIERARCHY_STELLA_NUMBER_OF_FOREIGN_INTERVAL_NODES = ((Symbol*)(internRigidSymbolWrtModule("NUMBER-OF-FOREIGN-INTERVAL-NODES", NULL, 0)));
    SYM_HIERARCHY_STELLA_ROOTS = ((Symbol*)(internRigidSymbolWrtModule("ROOTS", NULL, 0)));
    SYM_HIERARCHY_STELLA_BROKEN_LINKS = ((Symbol*)(internRigidSymbolWrtModule("BROKEN-LINKS", NULL, 0)));
    SYM_HIERARCHY_STELLA_ADDED_LINKS = ((Symbol*)(internRigidSymbolWrtModule("ADDED-LINKS", NULL, 0)));
    SYM_HIERARCHY_STELLA_REMOVED_LINKS = ((Symbol*)(internRigidSymbolWrtModule("REMOVED-LINKS", NULL, 0)));
    SGT_HIERARCHY_STELLA_QUANTITY = ((Surrogate*)(internRigidSymbolWrtModule("QUANTITY", NULL, 1)));
    SYM_HIERARCHY_STELLA_COERCE_TO = ((Symbol*)(internRigidSymbolWrtModule("COERCE-TO", NULL, 0)));
    SYM_HIERARCHY_STELLA_LESSp = ((Symbol*)(internRigidSymbolWrtModule("LESS?", NULL, 0)));
    SYM_HIERARCHY_STELLA_LESS_EQUALp = ((Symbol*)(internRigidSymbolWrtModule("LESS-EQUAL?", NULL, 0)));
    SYM_HIERARCHY_STELLA_GREATER_EQUALp = ((Symbol*)(internRigidSymbolWrtModule("GREATER-EQUAL?", NULL, 0)));
    SYM_HIERARCHY_STELLA_GREATERp = ((Symbol*)(internRigidSymbolWrtModule("GREATER?", NULL, 0)));
    SYM_HIERARCHY_STELLA_FILE_NAME = ((Symbol*)(internRigidSymbolWrtModule("FILE-NAME", NULL, 0)));
    SGT_HIERARCHY_STELLA_INTEGER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-WRAPPER", NULL, 1)));
    SYM_HIERARCHY_STELLA_WRAPPER_VALUE = ((Symbol*)(internRigidSymbolWrtModule("WRAPPER-VALUE", NULL, 0)));
    SYM_HIERARCHY_STELLA_NULL_INTEGER = ((Symbol*)(internRigidSymbolWrtModule("NULL-INTEGER", NULL, 0)));
    SGT_HIERARCHY_STELLA_LONG_INTEGER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("LONG-INTEGER-WRAPPER", NULL, 1)));
    SYM_HIERARCHY_STELLA_NULL_LONG_INTEGER = ((Symbol*)(internRigidSymbolWrtModule("NULL-LONG-INTEGER", NULL, 0)));
    SGT_HIERARCHY_STELLA_FLOAT_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT-WRAPPER", NULL, 1)));
    SYM_HIERARCHY_STELLA_NULL_FLOAT = ((Symbol*)(internRigidSymbolWrtModule("NULL-FLOAT", NULL, 0)));
  }
}

void helpStartupHierarchy7() {
  {
    SGT_HIERARCHY_STELLA_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("STRING-WRAPPER", NULL, 1)));
    SYM_HIERARCHY_STELLA_NULL_STRING = ((Symbol*)(internRigidSymbolWrtModule("NULL-STRING", NULL, 0)));
    SGT_HIERARCHY_STELLA_MUTABLE_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("MUTABLE-STRING-WRAPPER", NULL, 1)));
    SYM_HIERARCHY_STELLA_NULL_MUTABLE_STRING = ((Symbol*)(internRigidSymbolWrtModule("NULL-MUTABLE-STRING", NULL, 0)));
    SGT_HIERARCHY_STELLA_CHARACTER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("CHARACTER-WRAPPER", NULL, 1)));
    SYM_HIERARCHY_STELLA_NULL_CHARACTER = ((Symbol*)(internRigidSymbolWrtModule("NULL-CHARACTER", NULL, 0)));
    SGT_HIERARCHY_STELLA_BOOLEAN_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN-WRAPPER", NULL, 1)));
    SYM_HIERARCHY_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    SYM_HIERARCHY_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    SYM_HIERARCHY_STELLA_METHOD_CODEp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-CODE?", NULL, 0)));
    SGT_HIERARCHY_STELLA_FUNCTION_CODE_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("FUNCTION-CODE-WRAPPER", NULL, 1)));
    SGT_HIERARCHY_STELLA_METHOD_CODE_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-CODE-WRAPPER", NULL, 1)));
    SGT_HIERARCHY_STELLA_VERBATIM_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("VERBATIM-STRING-WRAPPER", NULL, 1)));
    SGT_HIERARCHY_STELLA_NATIVE_OBJECT_POINTER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NATIVE-OBJECT-POINTER-WRAPPER", NULL, 1)));
    SGT_HIERARCHY_STELLA_EXCEPTION_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("EXCEPTION-WRAPPER", NULL, 1)));
    SYM_HIERARCHY_STELLA_THREE_VALUED_BOOLEAN = ((Symbol*)(internRigidSymbolWrtModule("THREE-VALUED-BOOLEAN", NULL, 0)));
    SYM_HIERARCHY_STELLA_PYTHON_OBJECT_POINTER = ((Symbol*)(internRigidSymbolWrtModule("PYTHON-OBJECT-POINTER", NULL, 0)));
    SGT_HIERARCHY_STELLA_SYSTEM_DEFINITION = ((Surrogate*)(internRigidSymbolWrtModule("SYSTEM-DEFINITION", NULL, 1)));
    SYM_HIERARCHY_STELLA_DEFINITION_FILE = ((Symbol*)(internRigidSymbolWrtModule("DEFINITION-FILE", NULL, 0)));
    SYM_HIERARCHY_STELLA_DIRECTORY = ((Symbol*)(internRigidSymbolWrtModule("DIRECTORY", NULL, 0)));
    SYM_HIERARCHY_STELLA_FILES = ((Symbol*)(internRigidSymbolWrtModule("FILES", NULL, 0)));
    SYM_HIERARCHY_STELLA_LISP_ONLY_FILES = ((Symbol*)(internRigidSymbolWrtModule("LISP-ONLY-FILES", NULL, 0)));
    SYM_HIERARCHY_STELLA_CPP_ONLY_FILES = ((Symbol*)(internRigidSymbolWrtModule("CPP-ONLY-FILES", NULL, 0)));
    SYM_HIERARCHY_STELLA_JAVA_ONLY_FILES = ((Symbol*)(internRigidSymbolWrtModule("JAVA-ONLY-FILES", NULL, 0)));
    SYM_HIERARCHY_STELLA_DATA_FILES = ((Symbol*)(internRigidSymbolWrtModule("DATA-FILES", NULL, 0)));
    SYM_HIERARCHY_STELLA_PREPROCESSED_FILES = ((Symbol*)(internRigidSymbolWrtModule("PREPROCESSED-FILES", NULL, 0)));
    SYM_HIERARCHY_STELLA_REQUIRED_SYSTEMS = ((Symbol*)(internRigidSymbolWrtModule("REQUIRED-SYSTEMS", NULL, 0)));
    SYM_HIERARCHY_STELLA_LOADEDp = ((Symbol*)(internRigidSymbolWrtModule("LOADED?", NULL, 0)));
    SYM_HIERARCHY_STELLA_UP_TO_DATEp = ((Symbol*)(internRigidSymbolWrtModule("UP-TO-DATE?", NULL, 0)));
    SYM_HIERARCHY_STELLA_SOURCE_ROOT_DIRECTORY = ((Symbol*)(internRigidSymbolWrtModule("SOURCE-ROOT-DIRECTORY", NULL, 0)));
    SYM_HIERARCHY_STELLA_NATIVE_ROOT_DIRECTORY = ((Symbol*)(internRigidSymbolWrtModule("NATIVE-ROOT-DIRECTORY", NULL, 0)));
    SYM_HIERARCHY_STELLA_BINARY_ROOT_DIRECTORY = ((Symbol*)(internRigidSymbolWrtModule("BINARY-ROOT-DIRECTORY", NULL, 0)));
    SYM_HIERARCHY_STELLA_BANNER = ((Symbol*)(internRigidSymbolWrtModule("BANNER", NULL, 0)));
    SYM_HIERARCHY_STELLA_COPYRIGHT_HEADER = ((Symbol*)(internRigidSymbolWrtModule("COPYRIGHT-HEADER", NULL, 0)));
    SYM_HIERARCHY_STELLA_PRODUCTION_SETTINGS = ((Symbol*)(internRigidSymbolWrtModule("PRODUCTION-SETTINGS", NULL, 0)));
    SYM_HIERARCHY_STELLA_DEVELOPMENT_SETTINGS = ((Symbol*)(internRigidSymbolWrtModule("DEVELOPMENT-SETTINGS", NULL, 0)));
    SYM_HIERARCHY_STELLA_FINALIZATION_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("FINALIZATION-FUNCTION", NULL, 0)));
    SYM_HIERARCHY_STELLA_STATE = ((Symbol*)(internRigidSymbolWrtModule("STATE", NULL, 0)));
    SGT_HIERARCHY_STELLA_OUTPUT_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("OUTPUT-STREAM", NULL, 1)));
    KWD_HIERARCHY_LINE = ((Keyword*)(internRigidSymbolWrtModule("LINE", NULL, 2)));
    SGT_HIERARCHY_STELLA_INPUT_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("INPUT-STREAM", NULL, 1)));
    SYM_HIERARCHY_STELLA_ECHO_STREAM = ((Symbol*)(internRigidSymbolWrtModule("ECHO-STREAM", NULL, 0)));
    SYM_HIERARCHY_STELLA_TOKENIZER_STATE = ((Symbol*)(internRigidSymbolWrtModule("TOKENIZER-STATE", NULL, 0)));
    SYM_HIERARCHY_STELLA_BUFFERING_SCHEME = ((Symbol*)(internRigidSymbolWrtModule("BUFFERING-SCHEME", NULL, 0)));
    KWD_HIERARCHY_CREATE = ((Keyword*)(internRigidSymbolWrtModule("CREATE", NULL, 2)));
    KWD_HIERARCHY_SUPERSEDE = ((Keyword*)(internRigidSymbolWrtModule("SUPERSEDE", NULL, 2)));
    SGT_HIERARCHY_STELLA_OUTPUT_FILE_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("OUTPUT-FILE-STREAM", NULL, 1)));
    SYM_HIERARCHY_STELLA_FILENAME = ((Symbol*)(internRigidSymbolWrtModule("FILENAME", NULL, 0)));
    SYM_HIERARCHY_STELLA_IF_EXISTS_ACTION = ((Symbol*)(internRigidSymbolWrtModule("IF-EXISTS-ACTION", NULL, 0)));
    SYM_HIERARCHY_STELLA_IF_NOT_EXISTS_ACTION = ((Symbol*)(internRigidSymbolWrtModule("IF-NOT-EXISTS-ACTION", NULL, 0)));
    SYM_HIERARCHY_STELLA_FILE_OUTPUT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("FILE-OUTPUT-STREAM", NULL, 0)));
    KWD_HIERARCHY_BLOCK = ((Keyword*)(internRigidSymbolWrtModule("BLOCK", NULL, 2)));
    KWD_HIERARCHY_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    SGT_HIERARCHY_STELLA_INPUT_FILE_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("INPUT-FILE-STREAM", NULL, 1)));
    SYM_HIERARCHY_STELLA_FILE_INPUT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("FILE-INPUT-STREAM", NULL, 0)));
    SGT_HIERARCHY_STELLA_OUTPUT_STRING_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("OUTPUT-STRING-STREAM", NULL, 1)));
    SYM_HIERARCHY_STELLA_STRING_OUTPUT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("STRING-OUTPUT-STREAM", NULL, 0)));
    SGT_HIERARCHY_STELLA_INPUT_STRING_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("INPUT-STRING-STREAM", NULL, 1)));
    SYM_HIERARCHY_STELLA_STRING_INPUT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("STRING-INPUT-STREAM", NULL, 0)));
    SYM_HIERARCHY_STELLA_STARTUP_HIERARCHY = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-HIERARCHY", NULL, 0)));
  }
}

void helpStartupHierarchy8() {
  {
    defineClassFromStringifiedSource("OBJECT", "(DEFCLASS OBJECT () :DOCUMENTATION \"A reflective object that can participate in dynamically-typed\ncontexts.  Either a STANDARD-OBJECT or a WRAPPER or a GENERIC-OBJECT.\nAlso, either an OBJECT-WITH-INHERITED-TYPE or an OBJECT-WITH-OWN-TYPE.\" :PUBLIC-METHODS ((PRIMARY-TYPE ((SELF OBJECT)) :TYPE TYPE :DOCUMENTATION \"Returns the primary type of `self'.\nGets defined automatically for every non-abstract subclass of OBJECT.\" (RETURN NULL)) (HOME-MODULE ((SELF OBJECT)) :TYPE MODULE :DOCUMENTATION \"Return the home module of `self'.\" (RETURN NULL)) (DELETED? ((SELF OBJECT)) :TYPE BOOLEAN :DOCUMENTATION \"Default `deleted?' method which always returns FALSE.  Objects\nthat inherit DYNAMIC-SLOTS-MIXIN also inherit the dynamically-allocated slot\n`deleted-object?' which is read/writable with specializations of this method.\" (RETURN FALSE))) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"|i|\" (PRIMARY-TYPE SELF)) :METHODS ((INCREMENT-REFERENCE-COUNT ((SELF OBJECT)) NULL) (DECREMENT-REFERENCE-COUNT ((SELF OBJECT)) NUL" "L)) :ABSTRACT? TRUE)");
    defineClassFromStringifiedSource("SECOND-CLASS-OBJECT", "(DEFCLASS SECOND-CLASS-OBJECT () :DOCUMENTATION \"A native reference-type object pretending to be second class,\ni.e., it can't/won't participate in dynamically-typed contexts such as (real)\nmethod dispatch.  Since it is a reference-type object, it is always passed via\na pointer reference similar to a real object.\" :ABSTRACT? TRUE)");
    defineClassFromStringifiedSource("NON-OBJECT", "(DEFCLASS NON-OBJECT () :DOCUMENTATION \"A data structure that cannot be a dispatch argument to\na (real) method, because its type is not accessible at run-time.\" :ABSTRACT? TRUE)");
    defineClassFromStringifiedSource("STANDARD-OBJECT", "(DEFCLASS STANDARD-OBJECT (OBJECT) :DOCUMENTATION \"Object that used to find its type stored in a :class slot.\nBy reimplementing `primary-type' as a method, the justification for this\nclass went away, but we'll keep it for now to keep things working.\" :ABSTRACT? TRUE :SYNONYMS (TYPE-SPEC))");
    { Class* clasS = defineClassFromStringifiedSource("TRANSIENT-MIXIN", "(DEFCLASS TRANSIENT-MIXIN () :DOCUMENTATION \"Transient objects are periodically swept back into a pool\nof free objects.  A transient object should never be pointed at by a\npermanent object.\" :MIXIN? TRUE :PUBLIC-SLOTS ((TRANSIENT? :TYPE BOOLEAN :INITIALLY TRUE :HARDWIRED? TRUE)))");

      oHARDWIRED_TRANSIENTp_ON_TRANSIENT_MIXINo = true;
    }
    { Class* clasS = defineClassFromStringifiedSource("REFERENCE-COUNT-OBJECT", "(DEFCLASS REFERENCE-COUNT-OBJECT (OBJECT) :DOCUMENTATION \"A reference count objects contains a slot `reference-count' \nthat is incremented whenever the object is assigned to a slot, and decremented\nwhenever it is deassigned from a slot.\" :ABSTRACT? TRUE :PUBLIC-SLOTS ((REFERENCE-COUNT :TYPE INTEGER :INITIALLY 0)) :METHODS ((INCREMENT-REFERENCE-COUNT ((SELF REFERENCE-COUNT-OBJECT)) (SETF (REFERENCE-COUNT SELF) (+ (REFERENCE-COUNT SELF) 1))) (DECREMENT-REFERENCE-COUNT ((SELF REFERENCE-COUNT-OBJECT)) (SETF (REFERENCE-COUNT SELF) (- (REFERENCE-COUNT SELF) 1)))))");

      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessReferenceCountObjectSlotValue));
    }
    defineClassFromStringifiedSource("DYNAMIC-SLOTS-MIXIN", "(DEFCLASS DYNAMIC-SLOTS-MIXIN () :DOCUMENTATION \"Enables objects to store slot values in non-preallocated storage.\" :MIXIN? TRUE :PUBLIC-SLOTS ((DYNAMIC-SLOTS :TYPE KEY-VALUE-LIST :ALLOCATION :EMBEDDED :PUBLIC? TRUE) (BAD? :TYPE BOOLEAN-WRAPPER :ALLOCATION :DYNAMIC :DEFAULT FALSE :DOCUMENTATION \"Indicates that an object is in need of repair.\") (DELETED-OBJECT? :TYPE BOOLEAN-WRAPPER :ALLOCATION :DYNAMIC :READER DELETED? :WRITER DELETED?-SETTER :DOCUMENTATION \"Indicates that an object has been \ndestroyed/deleted.  A deleted object is visible only if something broke\nbefore it was fully excised from the network).\")) :PUBLIC-METHODS ((DELETED? ((SELF DYNAMIC-SLOTS-MIXIN)) :TYPE BOOLEAN (LET ((DELETED? (SLOT-VALUE SELF DELETED-OBJECT?))) (IF (DEFINED? DELETED?) (RETURN DELETED?) (RETURN FALSE)))) (DELETED?-SETTER ((SELF DYNAMIC-SLOTS-MIXIN) (VALUE BOOLEAN)) :TYPE BOOLEAN (SETF (SLOT-VALUE SELF DELETED-OBJECT?) VALUE) (RETURN VALUE))))");
    defineClassFromStringifiedSource("CONTEXT-SENSITIVE-OBJECT", "(DEFCLASS CONTEXT-SENSITIVE-OBJECT (STANDARD-OBJECT CONTEXT-SENSITIVE-MIXIN) :DOCUMENTATION \"Context sensitive objects inherit a slot `home-context'\nthat enables context-dependent access machinery to determine the\nvisibility of objects from modules.\" :ABSTRACT? TRUE)");
    defineClassFromStringifiedSource("CONTEXT-SENSITIVE-MIXIN", "(DEFCLASS CONTEXT-SENSITIVE-MIXIN () :DOCUMENTATION \"Mixin class that enables the class to support \ncontext sensitive slots.  The mixin allocates and initializes the\nslot `home-context'.\" :MIXIN? TRUE :PUBLIC-SLOTS ((HOME-CONTEXT :TYPE CONTEXT :INITIALLY *CONTEXT*)) :PUBLIC-METHODS ((HOME-MODULE ((SELF CONTEXT-SENSITIVE-MIXIN)) :TYPE MODULE (LET ((CONTEXT (HOME-CONTEXT SELF))) (IF (DEFINED? CONTEXT) (RETURN (BASE-MODULE CONTEXT)) (RETURN NULL))))))");
    defineClassFromStringifiedSource("ACTIVE-OBJECT", "(DEFCLASS ACTIVE-OBJECT (CONTEXT-SENSITIVE-OBJECT DYNAMIC-SLOTS-MIXIN) :DOCUMENTATION \"Active objects call class and slot triggers in response\nto instance creation/destruction and slot updates.  They include internal\nstorage slots needed for class extensions, dynamic storage, and home context.\" :ABSTRACT? TRUE)");
    { Class* clasS = defineClassFromStringifiedSource("ABSTRACT-ITERATOR", "(DEFCLASS ABSTRACT-ITERATOR (STANDARD-OBJECT) :ABSTRACT? TRUE :DOCUMENTATION \"Instances of ABSTRACT-ITERATOR support iteration over collections.\" :PARAMETERS ((ANY-VALUE :TYPE UNKNOWN)) :PUBLIC-SLOTS ((VALUE :TYPE (LIKE (ANY-VALUE SELF)) :DOCUMENTATION \"The current value of this iterator\") (FIRST-ITERATION? :TYPE BOOLEAN :INITIALLY TRUE)) :PUBLIC-METHODS ((NEXT? ((SELF ABSTRACT-ITERATOR)) :TYPE BOOLEAN (RETURN NULL)) (LENGTH ((SELF ABSTRACT-ITERATOR)) :TYPE INTEGER)))");

      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessAbstractIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("ITERATOR", "(DEFCLASS ITERATOR (ABSTRACT-ITERATOR) :ABSTRACT? TRUE :DOCUMENTATION \"Instances of ITERATOR support iteration over \ncollections of OBJECTs.\" :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :SYNONYMS (OBJECT-ITERATOR))");

      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("CONS-ITERATOR", "(DEFCLASS CONS-ITERATOR (ITERATOR) :DOCUMENTATION \"Iterator class for the class CONS.\" :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :PUBLIC-SLOTS ((CONS-ITERATOR-CURSOR :TYPE CONS)) :TERMINATOR TERMINATE-CONS-ITERATOR?)");

      clasS->classConstructorCode = ((cpp_function_code)(&newConsIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessConsIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("LIST-ITERATOR", "(DEFCLASS LIST-ITERATOR (ITERATOR) :DOCUMENTATION \"Iterator class for the collection LIST.\" :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :PUBLIC-SLOTS ((LIST-ITERATOR-CURSOR :TYPE CONS) (LIST-ITERATOR-COLLECTION :TYPE LIST)) :TERMINATOR TERMINATE-LIST-ITERATOR?)");

      clasS->classConstructorCode = ((cpp_function_code)(&newListIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessListIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("DESTRUCTIVE-LIST-ITERATOR", "(DEFCLASS DESTRUCTIVE-LIST-ITERATOR (ITERATOR) :DOCUMENTATION \"An iterator that contains a cons list.  Iterates over\nthe stored list, and destroys it when the iterator is free'd.\" :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :PUBLIC-SLOTS ((THE-CONS-LIST :TYPE CONS :INITIALLY NIL) (LIST-ITERATOR-CURSOR :TYPE CONS)) :TERMINATOR TERMINATE-DESTRUCTIVE-LIST-ITERATOR?)");

      clasS->classConstructorCode = ((cpp_function_code)(&newDestructiveListIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessDestructiveListIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("ALL-PURPOSE-ITERATOR", "(DEFCLASS ALL-PURPOSE-ITERATOR (ITERATOR) :DOCUMENTATION \"The all-purpose iterator works by storing a `next?'\nfunction within itself during iterator allocation.  The method\n`ALL-PURPOSE-ITERAOR.next?' funcalls the stored `next?' function.\nAn assortment of storage slots are provided for constructing different\nkinds of iterators.\" :PUBLIC-SLOTS ((KEY :TYPE OBJECT) (ITERATOR-NEXT-CODE :TYPE FUNCTION-CODE) (ITERATOR-FILTER-CODE :TYPE FUNCTION-CODE) (ITERATOR-EMPTY-CODE :TYPE FUNCTION-CODE) (ITERATOR-NESTED-ITERATOR :TYPE ITERATOR) (ITERATOR-CONS-LIST :TYPE CONS) (ITERATOR-OBJECT :TYPE OBJECT) (ITERATOR-SECOND-OBJECT :TYPE OBJECT) (ITERATOR-INTEGER :TYPE INTEGER) (ITERATOR-SECOND-INTEGER :TYPE INTEGER)) :TERMINATOR TERMINATE-ALL-PURPOSE-ITERATOR?)");

      clasS->classConstructorCode = ((cpp_function_code)(&newAllPurposeIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessAllPurposeIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("TYPES-TO-CLASSES-ITERATOR", "(DEFCLASS TYPES-TO-CLASSES-ITERATOR (ITERATOR) :DOCUMENTATION \"Iterator that returns a class for each type\nin a cons list of types.\" :PARAMETERS ((ANY-VALUE :TYPE CLASS)) :PUBLIC-SLOTS ((ITERATOR-CURSOR :TYPE (CONS OF TYPE) :REQUIRED? TRUE)) :METHODS ((NEXT? ((SELF TYPES-TO-CLASSES-ITERATOR)) :TYPE BOOLEAN (IF (FIRST-ITERATION? SELF) (SETF (FIRST-ITERATION? SELF) FALSE) (SETF (ITERATOR-CURSOR SELF) (REST (ITERATOR-CURSOR SELF)))) (COND ((NON-EMPTY? (ITERATOR-CURSOR SELF)) (SETF (SLOT-VALUE SELF VALUE) (TYPE-CLASS (FIRST (ITERATOR-CURSOR SELF)))) (RETURN TRUE)) (OTHERWISE (RETURN FALSE))))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newTypesToClassesIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTypesToClassesIteratorSlotValue));
    }
    defineClassFromStringifiedSource("ABSTRACT-DICTIONARY-ITERATOR", "(DEFCLASS ABSTRACT-DICTIONARY-ITERATOR (ABSTRACT-ITERATOR) :ABSTRACT? TRUE :DOCUMENTATION \"Instances of ABSTRACT-DICTIONARY-ITERATOR support iteration\nover dictionaries.\" :PARAMETERS ((ANY-KEY :TYPE UNKNOWN) (ANY-VALUE :TYPE UNKNOWN)) :PUBLIC-SLOTS ((KEY :TYPE (LIKE (ANY-KEY SELF)))) :PUBLIC-METHODS ((VALUE-SETTER ((SELF ABSTRACT-DICTIONARY-ITERATOR) (VALUE (LIKE (ANY-VALUE SELF)))) :TYPE (LIKE (ANY-VALUE SELF)) :DOCUMENTATION \"Abstract method needed to allow application of this\nmethod on abstract iterator classes that do not implement it.  By having\nthis here all `next?' methods of dictionary iterators MUST use the `slot-value'\nparadigm to set the iterator value.\") (KEY-SETTER ((SELF ABSTRACT-DICTIONARY-ITERATOR) (KEY (LIKE (ANY-KEY SELF)))) :TYPE (LIKE (ANY-KEY SELF)))))");
    { Class* clasS = defineClassFromStringifiedSource("DICTIONARY-ITERATOR", "(DEFCLASS DICTIONARY-ITERATOR (ABSTRACT-DICTIONARY-ITERATOR) :ABSTRACT? TRUE :DOCUMENTATION \"Instances of DICTIONARY-ITERATOR support iteration\nover dictionaries with keys and values of type OBJECT.\" :PARAMETERS ((ANY-KEY :TYPE OBJECT) (ANY-VALUE :TYPE OBJECT)) :SYNONYMS (OBJECT-DICTIONARY-ITERATOR) :PUBLIC-METHODS ((VALUE-SETTER ((SELF DICTIONARY-ITERATOR) (VALUE (LIKE (ANY-VALUE SELF)))) :TYPE (LIKE (ANY-VALUE SELF)) (ERROR \"DICTIONARY-ITERATOR.value-setter not implemented on \" SELF)) (KEY-SETTER ((SELF DICTIONARY-ITERATOR) (KEY (LIKE (ANY-KEY SELF)))) :TYPE (LIKE (ANY-KEY SELF)) (ERROR \"DICTIONARY-ITERATOR.key-setter not implemented on \" SELF))))");

      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessDictionaryIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("PROPERTY-LIST-ITERATOR", "(DEFCLASS PROPERTY-LIST-ITERATOR (DICTIONARY-ITERATOR) :DOCUMENTATION \"Iterator class for the collection PROPERTY-LIST.\" :PUBLIC-SLOTS ((PLIST-ITERATOR-CURSOR :TYPE CONS) (PLIST-ITERATOR-COLLECTION :TYPE PROPERTY-LIST)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newPropertyListIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessPropertyListIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("KV-LIST-ITERATOR", "(DEFCLASS KV-LIST-ITERATOR (DICTIONARY-ITERATOR) :PUBLIC-SLOTS ((THE-KV-LIST :TYPE KEY-VALUE-LIST :PUBLIC? TRUE) (KV-LIST-ITERATOR-CURSOR :TYPE KV-CONS)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newKvListIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessKvListIteratorSlotValue));
    }
    defineClassFromStringifiedSource("INTERVAL-ITERATOR", "(DEFCLASS INTERVAL-ITERATOR (ABSTRACT-ITERATOR) :ABSTRACT? TRUE :DOCUMENTATION \"An iterator that specifies a (possibly infinite) range of\nvalues.  Supports `member?' test as well as iteration methods.\" :PUBLIC-SLOTS ((LOWER-BOUND :TYPE UNKNOWN :REQUIRED? TRUE) (UPPER-BOUND :TYPE UNKNOWN :REQUIRED? TRUE)))");
    { Class* clasS = defineClassFromStringifiedSource("INTEGER-INTERVAL-ITERATOR", "(DEFCLASS INTEGER-INTERVAL-ITERATOR (INTERVAL-ITERATOR) :PARAMETERS ((ANY-VALUE :TYPE INTEGER)) :PUBLIC-SLOTS ((INTERVAL-CURSOR :TYPE INTEGER) (LOWER-BOUND :TYPE INTEGER :REQUIRED? TRUE) (UPPER-BOUND :TYPE INTEGER :REQUIRED? TRUE)) :INITIALIZER INITIALIZE-INTEGER-INTERVAL-ITERATOR)");

      clasS->classConstructorCode = ((cpp_function_code)(&newIntegerIntervalIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessIntegerIntervalIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("REVERSE-INTEGER-INTERVAL-ITERATOR", "(DEFCLASS REVERSE-INTEGER-INTERVAL-ITERATOR (INTERVAL-ITERATOR) :PARAMETERS ((ANY-VALUE :TYPE INTEGER)) :PUBLIC-SLOTS ((INTERVAL-CURSOR :TYPE INTEGER) (LOWER-BOUND :TYPE INTEGER :REQUIRED? TRUE) (UPPER-BOUND :TYPE INTEGER :REQUIRED? TRUE)) :INITIALIZER INITIALIZE-REVERSE-INTEGER-INTERVAL-ITERATOR)");

      clasS->classConstructorCode = ((cpp_function_code)(&newReverseIntegerIntervalIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessReverseIntegerIntervalIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("STRING-ITERATOR", "(DEFCLASS STRING-ITERATOR (ABSTRACT-ITERATOR) :DOCUMENTATION \"Iterator that yields characters from a string.\" :PARAMETERS ((ANY-VALUE :TYPE CHARACTER)) :PUBLIC-SLOTS ((THE-STRING :TYPE STRING) (CURSOR :TYPE INTEGER) (END :TYPE INTEGER)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newStringIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessStringIteratorSlotValue));
    }
    defineClassFromStringifiedSource("ABSTRACT-COLLECTION", "(DEFCLASS ABSTRACT-COLLECTION (STANDARD-OBJECT) :PARAMETERS ((ANY-VALUE :TYPE UNKNOWN)) :PUBLIC-METHODS ((ALLOCATE-ITERATOR ((SELF ABSTRACT-COLLECTION)) :TYPE (ABSTRACT-ITERATOR OF (LIKE (ANY-VALUE SELF))) (RETURN NULL)) (LENGTH ((SELF ABSTRACT-COLLECTION)) :TYPE INTEGER (RETURN NULL)) (INSERT ((SELF ABSTRACT-COLLECTION) (VALUE (LIKE (ANY-VALUE SELF))))) (REMOVE ((SELF ABSTRACT-COLLECTION) (VALUE (LIKE (ANY-VALUE SELF)))) :TYPE ABSTRACT-COLLECTION)) :ABSTRACT? TRUE)");
    defineClassFromStringifiedSource("COLLECTION", "(DEFCLASS COLLECTION (ABSTRACT-COLLECTION) :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :PUBLIC-METHODS ((ALLOCATE-ITERATOR ((SELF COLLECTION)) :TYPE (ITERATOR OF (LIKE (ANY-VALUE SELF))) (RETURN NULL)) (LENGTH ((SELF COLLECTION)) :TYPE INTEGER (RETURN NULL)) (INSERT ((SELF COLLECTION) (VALUE (LIKE (ANY-VALUE SELF)))) (IGNORE VALUE) (RETURN)) (REMOVE ((SELF COLLECTION) (VALUE (LIKE (ANY-VALUE SELF)))) :TYPE COLLECTION (IGNORE VALUE) (RETURN NULL))) :ABSTRACT? TRUE :SYNONYMS (OBJECT-COLLECTION))");
    defineClassFromStringifiedSource("SET-MIXIN", "(DEFCLASS SET-MIXIN () :DOCUMENTATION \"Users of this mixin check for duplicates inside of \nthe method `insert'.\" :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :MIXIN? TRUE)");
    defineClassFromStringifiedSource("SEQUENCE-MIXIN", "(DEFCLASS SEQUENCE-MIXIN () :PARAMETERS ((ANY-VALUE :TYPE UNKNOWN)) :PUBLIC-METHODS ((FIRST ((SEQUENCE SEQUENCE-MIXIN)) :TYPE (LIKE (ANY-VALUE SELF))) (NTH ((SEQUENCE SEQUENCE-MIXIN) (POSITION INTEGER)) :TYPE (LIKE (ANY-VALUE SELF)))) :MIXIN? TRUE)");
    defineClassFromStringifiedSource("SEQUENCE", "(DEFCLASS SEQUENCE (COLLECTION SEQUENCE-MIXIN) :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :PUBLIC-METHODS ((ALLOCATE-ITERATOR ((SELF SEQUENCE)) :TYPE (ITERATOR OF (LIKE (ANY-VALUE SELF))) (RETURN NULL)) (LENGTH ((SEQUENCE SEQUENCE)) :TYPE INTEGER (RETURN NULL))) :ABSTRACT? TRUE :SYNONYMS (OBJECT-SEQUENCE))");
    { Class* clasS = defineClassFromStringifiedSource("LIST", "(DEFCLASS LIST (SEQUENCE) :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :PUBLIC-SLOTS ((THE-CONS-LIST :TYPE (CONS OF (LIKE (ANY-VALUE SELF))) :INITIALLY NIL :PUBLIC? TRUE)) :INITIAL-VALUE NIL-LIST :PRINT-FORM (PROGN (PRINT-STREAM STREAM \"|l|\") (PRINT-CONS (THE-CONS-LIST SELF) STREAM \"(\" \")\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newList));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessListSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("SET", "(DEFCLASS SET (LIST SET-MIXIN) :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :INITIAL-VALUE NULL :PRINT-FORM (PROGN (PRINT-STREAM STREAM \"|s|\") (PRINT-CONS (THE-CONS-LIST SELF) STREAM \"(\" \")\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newSet));
    }
    { Class* clasS = defineClassFromStringifiedSource("CLASS-EXTENSION", "(DEFCLASS CLASS-EXTENSION (LIST) :PARAMETERS ((ANY-VALUE :TYPE ACTIVE-OBJECT)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newClassExtension));
    }
    { Class* clasS = defineClassFromStringifiedSource("CONS", "(DEFCLASS CONS (STANDARD-OBJECT) :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :METHODS ((ALLOCATE-ITERATOR ((SELF CONS)) :TYPE (ITERATOR OF (LIKE (ANY-VALUE SELF))))) :PUBLIC-SLOTS ((VALUE :TYPE (LIKE (ANY-VALUE SELF)) :PUBLIC? TRUE) (REST :TYPE (CONS OF (LIKE (ANY-VALUE SELF))) :PUBLIC? TRUE :INITIALLY NIL)) :INITIAL-VALUE NIL :PRINT-FORM (PRINT-CONS SELF STREAM \"(\" \")\"))");

      clasS->classConstructorCode = ((cpp_function_code)(&newCons));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessConsSlotValue));
    }
    defineClassFromStringifiedSource("ABSTRACT-DICTIONARY", "(DEFCLASS ABSTRACT-DICTIONARY (ABSTRACT-COLLECTION) :PARAMETERS ((ANY-KEY :TYPE UNKNOWN) (ANY-VALUE :TYPE UNKNOWN)) :PUBLIC-METHODS ((LOOKUP ((SELF ABSTRACT-DICTIONARY) (KEY (LIKE (ANY-KEY SELF)))) :TYPE (LIKE (ANY-VALUE SELF))) (INSERT-AT ((SELF ABSTRACT-DICTIONARY) (KEY (LIKE (ANY-KEY SELF))) (VALUE (LIKE (ANY-VALUE SELF)))))) :METHODS ((ALLOCATE-ITERATOR ((SELF ABSTRACT-DICTIONARY)) :TYPE (ABSTRACT-DICTIONARY-ITERATOR OF (LIKE (ANY-KEY SELF)) (LIKE (ANY-VALUE SELF))) (RETURN NULL))) :ABSTRACT? TRUE)");
    defineClassFromStringifiedSource("DICTIONARY", "(DEFCLASS DICTIONARY (ABSTRACT-DICTIONARY) :PARAMETERS ((ANY-KEY :TYPE OBJECT) (ANY-VALUE :TYPE OBJECT)) :METHODS ((ALLOCATE-ITERATOR ((SELF DICTIONARY)) :TYPE (DICTIONARY-ITERATOR OF (LIKE (ANY-KEY SELF)) (LIKE (ANY-VALUE SELF))) (RETURN NULL)) (LOOKUP ((SELF DICTIONARY) (KEY (LIKE (ANY-KEY SELF)))) :TYPE (LIKE (ANY-VALUE SELF)) (IGNORE KEY) (RETURN NULL)) (INSERT-AT ((SELF DICTIONARY) (KEY (LIKE (ANY-KEY SELF))) (VALUE (LIKE (ANY-VALUE SELF)))) (IGNORE KEY VALUE) (RETURN))) :ABSTRACT? TRUE :SYNONYMS (OBJECT-TO-OBJECT-DICTIONARY))");
    { Class* clasS = defineClassFromStringifiedSource("PROPERTY-LIST", "(DEFCLASS PROPERTY-LIST (DICTIONARY) :PARAMETERS ((ANY-KEY :TYPE OBJECT) (ANY-VALUE :TYPE OBJECT)) :PUBLIC-SLOTS ((THE-PLIST :TYPE CONS :INITIALLY NIL)) :PRINT-FORM (PROGN (PRINT-STREAM STREAM \"|pl|\") (PRINT-CONS (THE-PLIST SELF) STREAM \"(\" \")\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newPropertyList));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessPropertyListSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("KV-CONS", "(DEFCLASS KV-CONS (STANDARD-OBJECT) :PARAMETERS ((ANY-KEY :TYPE OBJECT) (ANY-VALUE :TYPE OBJECT)) :PUBLIC-SLOTS ((KEY :TYPE OBJECT) (VALUE :TYPE OBJECT) (REST :TYPE KV-CONS)) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"<\" (KEY SELF) \",\" (VALUE SELF) \">\"))");

      clasS->classConstructorCode = ((cpp_function_code)(&newKvCons));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessKvConsSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("KEY-VALUE-LIST", "(DEFCLASS KEY-VALUE-LIST (DICTIONARY) :PARAMETERS ((ANY-KEY :TYPE OBJECT) (ANY-VALUE :TYPE OBJECT)) :PUBLIC-SLOTS ((THE-KV-LIST :TYPE KV-CONS)) :PRINT-FORM (PRINT-KEY-VALUE-LIST SELF STREAM))");

      clasS->classConstructorCode = ((cpp_function_code)(&newKeyValueList));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessKeyValueListSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("RECYCLE-LIST", "(DEFCLASS RECYCLE-LIST (SEQUENCE) :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :PUBLIC-SLOTS ((RECYCLE-LIST-OF :TYPE TYPE) (RECYCLED-ITEMS :TYPE (LIKE (ANY-VALUE SELF))) (LIST-OF-RECYCLED-ITEMS :TYPE (LIST OF (LIKE (ANY-VALUE SELF))) :INITIALLY (MAKE-NON-RECYCLED-LIST)) (ALL-ITEMS :TYPE (LIKE (ANY-VALUE SELF))) (UNUSED-ITEMS :TYPE (LIKE (ANY-VALUE SELF))) (CURRENT-LENGTH :TYPE INTEGER :INITIALLY 0) (ITEM-SIZE :TYPE INTEGER)) :PRINT-FORM (IF (DEFINED? (RECYCLE-LIST-OF SELF)) (PRINT-NATIVE-STREAM STREAM \"|i|[RECYCLE-LIST OF \" (CURRENT-LENGTH SELF) \" \" (RECYCLE-LIST-OF SELF) \"'s]\") (PRINT-NATIVE-STREAM STREAM \"|i|@RECYCLE-LIST\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newRecycleList));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessRecycleListSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("ABSTRACT-HASH-TABLE", "(DEFCLASS ABSTRACT-HASH-TABLE (ABSTRACT-DICTIONARY) :PARAMETERS ((ANY-KEY :TYPE UNKNOWN) (ANY-VALUE :TYPE UNKNOWN)) :PUBLIC-SLOTS ((THE-HASH-TABLE :TYPE NATIVE-HASH-TABLE) (THE-STELLA-HASH-TABLE :TYPE STELLA-HASH-TABLE)) :INITIALIZER INITIALIZE-HASH-TABLE :ABSTRACT? TRUE)");

      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessAbstractHashTableSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("HASH-TABLE", "(DEFCLASS HASH-TABLE (ABSTRACT-HASH-TABLE) :PARAMETERS ((ANY-KEY :TYPE OBJECT) (ANY-VALUE :TYPE OBJECT)) :INITIALIZER INITIALIZE-HASH-TABLE :SYNONYMS (OBJECT-TO-OBJECT-HASH-TABLE))");

      clasS->classConstructorCode = ((cpp_function_code)(&newHashTable));
    }
    { Class* clasS = defineClassFromStringifiedSource("INTEGER-HASH-TABLE", "(DEFCLASS INTEGER-HASH-TABLE (ABSTRACT-HASH-TABLE) :PARAMETERS ((ANY-KEY :TYPE INTEGER) (ANY-VALUE :TYPE OBJECT)) :INITIALIZER INITIALIZE-HASH-TABLE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newIntegerHashTable));
    }
    { Class* clasS = defineClassFromStringifiedSource("FLOAT-HASH-TABLE", "(DEFCLASS FLOAT-HASH-TABLE (ABSTRACT-HASH-TABLE) :PARAMETERS ((ANY-KEY :TYPE FLOAT) (ANY-VALUE :TYPE OBJECT)) :INITIALIZER INITIALIZE-HASH-TABLE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newFloatHashTable));
    }
    { Class* clasS = defineClassFromStringifiedSource("STRING-HASH-TABLE", "(DEFCLASS STRING-HASH-TABLE (ABSTRACT-HASH-TABLE) :PARAMETERS ((ANY-KEY :TYPE STRING) (ANY-VALUE :TYPE OBJECT)) :INITIALIZER INITIALIZE-HASH-TABLE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newStringHashTable));
    }
    { Class* clasS = defineClassFromStringifiedSource("STRING-TO-INTEGER-HASH-TABLE", "(DEFCLASS STRING-TO-INTEGER-HASH-TABLE (ABSTRACT-HASH-TABLE) :PARAMETERS ((ANY-KEY :TYPE STRING) (ANY-VALUE :TYPE INTEGER)) :INITIALIZER INITIALIZE-HASH-TABLE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newStringToIntegerHashTable));
    }
    { Class* clasS = defineClassFromStringifiedSource("VECTOR", "(DEFCLASS VECTOR (SEQUENCE) :PUBLIC-SLOTS ((ARRAY-SIZE :TYPE INTEGER :REQUIRED? TRUE) (THE-ARRAY :TYPE (NATIVE-VECTOR OF (LIKE (ANY-VALUE SELF))))) :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :PRINT-FORM (PRINT-VECTOR SELF STREAM) :INITIALIZER INITIALIZE-VECTOR)");

      clasS->classConstructorCode = ((cpp_function_code)(&newVector));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessVectorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("EXTENSIBLE-VECTOR", "(DEFCLASS EXTENSIBLE-VECTOR (VECTOR) :INITIALIZER INITIALIZE-VECTOR)");

      clasS->classConstructorCode = ((cpp_function_code)(&newExtensibleVector));
    }
    { Class* clasS = defineClassFromStringifiedSource("EXTENSIBLE-SYMBOL-ARRAY", "(DEFCLASS EXTENSIBLE-SYMBOL-ARRAY (EXTENSIBLE-VECTOR) :DOCUMENTATION \"Self-extending array with methods for storing and\naccessing symbols within it.\" :PUBLIC-SLOTS ((TOP-SYMBOL-OFFSET :TYPE INTEGER :INITIALLY -1) (POTENTIAL-FREE-SYMBOL-OFFSET :TYPE INTEGER :INITIALLY 0)) :INITIALIZER INITIALIZE-VECTOR)");

      clasS->classConstructorCode = ((cpp_function_code)(&newExtensibleSymbolArray));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessExtensibleSymbolArraySlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("VECTOR-SEQUENCE", "(DEFCLASS VECTOR-SEQUENCE (VECTOR) :DOCUMENTATION \"Extensible sequence implemented by a vector.  Whenever we run\nout of room, we grow the sequence by a factor of two.  Note that this keeps the\naverage insertion cost per element constant.  This is generally preferable over\nlinked lists unless we need within-list insertions or removals, since it uses\nless space and has better cache locality.\" :PUBLIC-SLOTS ((SEQUENCE-LENGTH :TYPE INTEGER :INITIALLY 0)) :INITIALIZER INITIALIZE-VECTOR)");

      clasS->classConstructorCode = ((cpp_function_code)(&newVectorSequence));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessVectorSequenceSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("CUSTOM-VECTOR-SEQUENCE", "(DEFCLASS CUSTOM-VECTOR-SEQUENCE (VECTOR-SEQUENCE) :DOCUMENTATION \"VECTOR-SEQUENCE (which see) with a customizable resize factor.\nThe resize factor needs to be > 1.\" :PUBLIC-SLOTS ((RESIZE-FACTOR :TYPE FLOAT :INITIALLY 2.0)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newCustomVectorSequence));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessCustomVectorSequenceSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("BOOLEAN-VECTOR", "(DEFCLASS BOOLEAN-VECTOR (VECTOR) :PARAMETERS ((ANY-VALUE :TYPE BOOLEAN-WRAPPER)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newBooleanVector));
    }
    { Class* clasS = defineClassFromStringifiedSource("INTEGER-VECTOR", "(DEFCLASS INTEGER-VECTOR (VECTOR) :PARAMETERS ((ANY-VALUE :TYPE INTEGER-WRAPPER)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newIntegerVector));
    }
    defineClassFromStringifiedSource("ARRAY", "(DEFCLASS ARRAY (SECOND-CLASS-OBJECT) :PARAMETERS ((ANY-VALUE :TYPE UNKNOWN)) :SLOTS ((INITIAL-ELEMENT :TYPE (LIKE (ANY-VALUE SELF)) :REQUIRED? TRUE :ABSTRACT? TRUE :DOCUMENTATION \"Initializer pseudo-slot special-cased by the STELLA translator.\") (SIZE :TYPE (LIST OF INTEGER-WRAPPER) :REQUIRED? TRUE :ABSTRACT? TRUE :DOCUMENTATION \"Size pseudo-slot special-cased by the STELLA translator.\")) :METHODS ((AREF ((SELF ARRAY) (DIM0 INTEGER) |&REST| (DIMS INTEGER)) :TYPE (LIKE (ANY-VALUE SELF)) :PUBLIC? TRUE :NATIVE? TRUE) (AREF-SETTER ((SELF ARRAY) (VALUE (LIKE (ANY-VALUE SELF))) (DIM0 INTEGER) |&REST| (DIMS INTEGER)) :TYPE (LIKE (ANY-VALUE SELF)) :PUBLIC? TRUE :NATIVE? TRUE)) :CL-NATIVE-TYPE \"ARRAY\" :CPP-NATIVE-TYPE \"void*\" :JAVA-NATIVE-TYPE \"Object\")");
    defineClassFromStringifiedSource("NATIVE-HASH-TABLE", "(DEFCLASS NATIVE-HASH-TABLE (SECOND-CLASS-OBJECT) :CPP-NATIVE-TYPE \"cpp_hash_table*\" :CL-NATIVE-TYPE \"HASH-TABLE\" :JAVA-NATIVE-TYPE \"java.util.HashMap\")");
    defineClassFromStringifiedSource("NATIVE-VECTOR", "(DEFCLASS NATIVE-VECTOR (SECOND-CLASS-OBJECT) :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :CPP-NATIVE-TYPE \"Object**\" :CL-NATIVE-TYPE \"VECTOR\" :JAVA-NATIVE-TYPE \"#$(STELLAROOT).Stella_Object[]\" :INITIAL-VALUE (VERBATIM :COMMON-LISP \"STELLA::NULL-NATIVE-VECTOR\" :JAVA \"null\" :CPP \"NULL\"))");
    defineClassFromStringifiedSource("ACTIVE-COLLECTION-MIXIN", "(DEFCLASS ACTIVE-COLLECTION-MIXIN () :DOCUMENTATION \"Mixin class that provides collection instances with a\nbackpointer to the instance slot they belong to.\" :MIXIN? TRUE :PUBLIC-SLOTS ((ACTIVE-SLOT :TYPE STORAGE-SLOT) (OWNER-INSTANCE :TYPE STANDARD-OBJECT)))");
    { Class* clasS = defineClassFromStringifiedSource("ACTIVE-LIST", "(DEFCLASS ACTIVE-LIST (LIST ACTIVE-COLLECTION-MIXIN))");

      clasS->classConstructorCode = ((cpp_function_code)(&newActiveList));
    }
    { Class* clasS = defineClassFromStringifiedSource("ACTIVE-SET", "(DEFCLASS ACTIVE-SET (LIST SET-MIXIN ACTIVE-COLLECTION-MIXIN))");

      clasS->classConstructorCode = ((cpp_function_code)(&newActiveSet));
    }
    { Class* clasS = defineClassFromStringifiedSource("DEMON", "(DEFCLASS DEMON (STANDARD-OBJECT) :PUBLIC-SLOTS ((DEMON-NAME :TYPE STRING) (DEMON-ACTION :TYPE KEYWORD) (DEMON-CLASS-REFS :TYPE (LIST OF TYPE) :ALLOCATION :EMBEDDED) (DEMON-SLOT-REFS :TYPE (LIST OF SYMBOL) :ALLOCATION :EMBEDDED) (DEMON-CODE :TYPE FUNCTION-CODE) (DEMON-METHOD :TYPE METHOD-SLOT) (DEMON-DOCUMENTATION :TYPE STRING) (DEMON-GUARD? :TYPE BOOLEAN) (DEMON-ALL? :TYPE BOOLEAN) (DEMON-INHERIT? :TYPE BOOLEAN)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newDemon));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessDemonSlotValue));
    }
  }
}

void helpStartupHierarchy9() {
  {
    { Class* clasS = defineClassFromStringifiedSource("KEYWORD-KEY-VALUE-LIST", "(DEFCLASS KEYWORD-KEY-VALUE-LIST (KEY-VALUE-LIST) :PARAMETERS ((ANY-KEY :TYPE KEYWORD) (ANY-VALUE :TYPE OBJECT)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newKeywordKeyValueList));
    }
    { Class* clasS = defineClassFromStringifiedSource("GENERALIZED-SYMBOL", "(DEFCLASS GENERALIZED-SYMBOL (CONTEXT-SENSITIVE-OBJECT) :PUBLIC-SLOTS ((SYMBOL-NAME :TYPE STRING :REQUIRED? TRUE) (SYMBOL-ID :TYPE INTEGER) (INTERNED-IN :RENAMES HOME-CONTEXT :TYPE MODULE)) :ABSTRACT? TRUE)");

      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessGeneralizedSymbolSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("SYMBOL", "(DEFCLASS SYMBOL (GENERALIZED-SYMBOL) :PUBLIC-SLOTS ((SYMBOL-SLOT-OFFSET :TYPE INTEGER) (SYMBOL-VALUE-AND-PLIST :TYPE CONS :INITIALLY NIL)) :PRINT-FORM (PRINT-SYMBOL SELF STREAM))");

      clasS->classConstructorCode = ((cpp_function_code)(&newSymbol));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessSymbolSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("SURROGATE", "(DEFCLASS SURROGATE (GENERALIZED-SYMBOL) :DOCUMENTATION \"Rigid surrogate.\" :PUBLIC-SLOTS ((SURROGATE-VALUE :TYPE OBJECT) (SURROGATE-NAME :RENAMES SYMBOL-NAME) (TYPE-CLASS :RENAMES SURROGATE-VALUE :TYPE CLASS) (TYPE-NAME :RENAMES SYMBOL-NAME)) :PUBLIC-SLOTS ((SLOTREF-SLOT :RENAMES SURROGATE-VALUE :TYPE SLOT)) :SYNONYMS (TYPE SLOTREF) :PRINT-FORM (PRINT-SURROGATE SELF STREAM))");

      clasS->classConstructorCode = ((cpp_function_code)(&newSurrogate));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessSurrogateSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("KEYWORD", "(DEFCLASS KEYWORD (GENERALIZED-SYMBOL) :PUBLIC-SLOTS ((KEYWORD-NAME :RENAMES SYMBOL-NAME)) :PRINT-FORM (PRINT-KEYWORD SELF STREAM))");

      clasS->classConstructorCode = ((cpp_function_code)(&newKeyword));
    }
    { Class* clasS = defineClassFromStringifiedSource("TRANSIENT-SYMBOL", "(DEFCLASS TRANSIENT-SYMBOL (SYMBOL TRANSIENT-MIXIN))");

      oHARDWIRED_TRANSIENTp_ON_TRANSIENT_MIXINo = true;
      clasS->classConstructorCode = ((cpp_function_code)(&newTransientSymbol));
    }
    { Class* clasS = defineClassFromStringifiedSource("MAPPABLE-OBJECT", "(DEFCLASS MAPPABLE-OBJECT (STANDARD-OBJECT DYNAMIC-SLOTS-MIXIN) :DOCUMENTATION \"The class MAPPABLE-OBJECT enables the definition of projections\nfrom a Stella class, slot, global variable, etc. onto a corresponding native\nentity.\" :ABSTRACT? TRUE :PUBLIC-SLOTS ((PROJECTS-ONTO :TYPE (LIST OF SYMBOL) :ALLOCATION :DYNAMIC) (PROJECTED-FROM :TYPE (LIST OF SYMBOL) :ALLOCATION :DYNAMIC) (PROJECTION-TRANSFORM :TYPE SYMBOL :ALLOCATION :DYNAMIC :DOCUMENTATION \"Names a coersion function that translates\nvalues retrieved from the `from' entity to the `projecting' entity.\")) :PUBLIC-SLOTS ((NATIVE-NAME :TYPE STRING :ALLOCATION :DYNAMIC :DOCUMENTATION \"Used in cases when the native name cannot be\ncast as a symbol (e.g., because it contains illegal characters).\")))");

      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessMappableObjectSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("RELATION", "(DEFCLASS RELATION (MAPPABLE-OBJECT) :ABSTRACT? TRUE :PUBLIC-SLOTS ((DOCUMENTATION :TYPE STRING :ALLOCATION :DYNAMIC) (ABSTRACT? :TYPE BOOLEAN :OPTION-KEYWORD :ABSTRACT?) (META-ATTRIBUTES :TYPE (KEY-VALUE-LIST OF GENERALIZED-SYMBOL OBJECT) :ALLOCATION :DYNAMIC :OPTION-KEYWORD :META-ATTRIBUTES) (PROPERTIES :TYPE (LIST OF GENERALIZED-SYMBOL) :ALLOCATION :DYNAMIC :OPTION-KEYWORD :PROPERTIES)) :PUBLIC-METHODS ((NAME ((SELF RELATION)) :TYPE STRING (RETURN NULL)) (HOME-MODULE ((SELF RELATION)) :TYPE MODULE (RETURN NULL)) (ARITY ((SELF RELATION)) :TYPE INTEGER (RETURN NULL)) (PUBLIC? ((SELF RELATION)) :TYPE BOOLEAN (RETURN NULL)) (DIRECT-SUPERS ((SELF RELATION)) :TYPE (LIST OF RELATION) (RETURN NULL)) (ALL-SUPERS ((SELF RELATION)) :TYPE (LIST OF RELATION) (RETURN NULL)) (SLOTS ((SELF RELATION)) :TYPE (ITERATOR OF SLOT) (RETURN NULL))) :SLOTS ((STORED-ACTIVE? :TYPE BOOLEAN-WRAPPER :ALLOCATION :DYNAMIC :OPTION-KEYWORD :ACTIVE?)))");

      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessRelationSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("CLASS", stringConcatenate("(DEFCLASS CLASS (RELATION) :PUBLIC-SLOTS ((CL-STRUCT? :TYPE BOOLEAN :INITIALLY FALSE) (MIXIN? :TYPE BOOLEAN :INITIALLY FALSE) (PRINT-FORM :TYPE OBJECT :ALLOCATION :DYNAMIC :OPTION-KEYWORD :PRINT-FORM) (CLASS-TYPE :TYPE TYPE :PUBLIC? TRUE) (CLASS-ARITY :TYPE INTEGER :INITIALLY 1 :HARDWIRED? TRUE) (CLASS-DIRECT-SUPERS :TYPE (LIST OF TYPE) :ALLOCATION :EMBEDDED) (CLASS-DIRECT-SUBS :TYPE (LIST OF TYPE) :ALLOCATION :EMBEDDED) (CLASS-ALL-SUPER-CLASSES :TYPE (CONS OF CLASS) :INITIALLY NIL :PUBLIC? TRUE) (CLASS-ALL-SLOTS :TYPE (CONS OF SLOT)) (CLASS-LOCAL-SLOTS :TYPE (LIST OF SLOT)) (CLASS-SLOT-AND-METHOD-CACHE :TYPE (VECTOR OF SLOT)) (CLASS-ABSTRACT? :TYPE BOOLEAN :INITIALLY FALSE :RENAMES ABSTRACT?) (CLASS-MIXIN? :TYPE BOOLEAN :INITIALLY FALSE :RENAMES MIXIN?) (CLASS-COLLECTION? :TYPE BOOLEAN :INITIALLY FALSE) (CLASS-CL-STRUCT? :TYPE BOOLEAN :INITIALLY FALSE :RENAMES CL-STRUCT?) (CLASS-CL-STRUCT-SLOTS :TYPE (LIST OF STORAGE-SLOT) :ALLOCATION :DYNAMIC) (CLASS-PUBLIC? :TYPE BOOLEAN :INITIALLY TRUE :OPTION-KEYWORD :P" "UBLIC?) (CLASS-RECYCLE-METHOD :TYPE KEYWORD :ALLOCATION :DYNAMIC :DEFAULT :NONE :OPTION-KEYWORD :RECYCLE-METHOD) (CLASS-FINALIZED? :TYPE BOOLEAN :INITIALLY FALSE :PUBLIC? TRUE) (CLASS-SLOTS-FINALIZED? :TYPE BOOLEAN :INITIALLY FALSE) (CLASS-STRINGIFIED-SOURCE :TYPE STRING) (CLASS-PARAMETERS :TYPE (LIST OF SYMBOL) :ALLOCATION :DYNAMIC :DEFAULT NIL-LIST :OPTION-KEYWORD :PARAMETERS) (CLASS-CONSTRUCTOR-CODE :TYPE FUNCTION-CODE) (CLASS-SLOT-ACCESSOR-CODE :TYPE FUNCTION-CODE) (CLASS-CREATOR :TYPE SYMBOL :ALLOCATION :DYNAMIC :OPTION-KEYWORD :CREATOR) (CLASS-INITIALIZER :TYPE SYMBOL :ALLOCATION :DYNAMIC :OPTION-KEYWORD :INITIALIZER) (CLASS-TERMINATOR :TYPE SYMBOL :ALLOCATION :DYNAMIC :OPTION-KEYWORD :TERMINATOR) (CLASS-DESTRUCTOR :TYPE SYMBOL :ALLOCATION :DYNAMIC :OPTION-KEYWORD :DESTRUCTOR) (CLASS-DOCUMENTATION :ALLOCATION :DYNAMIC :RENAMES DOCUMENTATION :OPTION-KEYWORD :DOCUMENTATION) (CLASS-EXTENSION-NAME :TYPE SYMBOL :ALLOCATION :DYNAMIC :OPTION-KEYWORD :EXTENSION) (CLASS-EXTENSION :TYPE CLASS-EXTENSION :ALLOCATI" "ON :DYNAMIC) (CLASS-REQUIRED-SLOT-NAMES :TYPE (LIST OF SYMBOL) :ALLOCATION :DYNAMIC :DEFAULT NIL-LIST) (CLASS-GUARD-CONSTRUCTOR-DEMONS :TYPE (LIST OF DEMON) :ALLOCATION :DYNAMIC) (CLASS-CONSTRUCTOR-DEMONS :TYPE (LIST OF DEMON) :ALLOCATION :DYNAMIC) (CLASS-GUARD-DESTRUCTOR-DEMONS :TYPE (LIST OF DEMON) :ALLOCATION :DYNAMIC) (CLASS-DESTRUCTOR-DEMONS :TYPE (LIST OF DEMON) :ALLOCATION :DYNAMIC) (CLASS-INITIAL-VALUE :TYPE OBJECT :ALLOCATION :DYNAMIC :OPTION-KEYWORD :INITIAL-VALUE) (CLASS-PRINT-FORM :TYPE OBJECT :RENAMES PRINT-FORM :OPTION-KEYWORD :PRINT-FORM) (CLASS-KEY :TYPE (LIST OF SLOT) :ALLOCATION :DYNAMIC :DEFAULT NIL-LIST) (CLASS-SYNONYMS :TYPE (LIST OF TYPE) :ALLOCATION :DYNAMIC :DEFAULT NIL-LIST :OPTION-KEYWORD :SYNONYMS) (CLASS-IS-LINK :TYPE TYPE :ALLOCATION :DYNAMIC) (CLASS-INVERSE-IS-LINK :TYPE CLASS :ALLOCATION :DYNAMIC) (CLASS-CL-NATIVE-TYPE :TYPE STRING :ALLOCATION :DYNAMIC :OPTION-KEYWORD :CL-NATIVE-TYPE) (CLASS-CPP-NATIVE-TYPE :TYPE STRING :ALLOCATION :DYNAMIC :OPTION-KEYWORD :CPP-NATIVE-TYPE) (CL" "ASS-JAVA-NATIVE-TYPE :TYPE STRING :ALLOCATION :DYNAMIC :OPTION-KEYWORD :JAVA-NATIVE-TYPE) (CLASS-IDL-NATIVE-TYPE :TYPE STRING :ALLOCATION :DYNAMIC :OPTION-KEYWORD :IDL-NATIVE-TYPE) (CLASS-MARKED? :TYPE BOOLEAN) (CLASS-PROTOTYPE :TYPE OBJECT :ALLOCATION :DYNAMIC) (CLASS-TAXONOMY-NODE :TYPE TAXONOMY-NODE)) :PUBLIC-METHODS ((NAME ((SELF CLASS)) :TYPE STRING (RETURN (SYMBOL-NAME (CLASS-TYPE SELF)))) (HOME-MODULE ((SELF CLASS)) :TYPE MODULE (RETURN (INTERNED-IN (CLASS-TYPE SELF)))) (ARITY ((SELF CLASS)) :TYPE INTEGER (RETURN 1)) (PUBLIC? ((SELF CLASS)) :TYPE BOOLEAN :STORAGE-SLOT CLASS-PUBLIC? (RETURN (CLASS-PUBLIC? SELF))) (ACTIVE? ((SELF CLASS)) :TYPE BOOLEAN :STORAGE-SLOT STORED-ACTIVE? (RETURN (OR (AND (DEFINED? (STORED-ACTIVE? SELF)) (STORED-ACTIVE? SELF)) (SUBTYPE-OF? (CLASS-TYPE SELF) @ACTIVE-OBJECT)))) (CREATOR ((SELF CLASS)) :TYPE SYMBOL :STORAGE-SLOT CLASS-CREATOR (RETURN (CLASS-CREATOR SELF))) (INITIALIZER ((SEL", "F CLASS)) :TYPE SYMBOL :STORAGE-SLOT CLASS-INITIALIZER :INHERITS-THROUGH SUPER-CLASSES) (TERMINATOR ((SELF CLASS)) :TYPE SYMBOL :STORAGE-SLOT CLASS-TERMINATOR :INHERITS-THROUGH SUPER-CLASSES) (DESTRUCTOR ((SELF CLASS)) :TYPE SYMBOL :STORAGE-SLOT CLASS-DESTRUCTOR (RETURN (CLASS-DESTRUCTOR SELF))) (REQUIRED-SLOTS ((SELF CLASS)) :TYPE (LIST OF SYMBOL) :DOCUMENTATION \"Returns a list of names of required slots for `self'.\" (RETURN (CLASS-REQUIRED-SLOT-NAMES SELF))) (PARAMETERS ((SELF CLASS)) :TYPE (LIST OF SYMBOL) :DOCUMENTATION \"Returns the list of parameters names of `self'.\" :STORAGE-SLOT CLASS-PARAMETERS :INHERITS-THROUGH SUPER-CLASSES) (INITIAL-VALUE ((SELF CLASS)) :TYPE OBJECT :DOCUMENTATION \"Return an initial value for the class `self'.\" :STORAGE-SLOT CLASS-INITIAL-VALUE :INHERITS-THROUGH SUPER-CLASSES) (EXTENSION ((SELF CLASS)) :TYPE CLASS-EXTENSION :DOCUMENTATION \"Return the nearest class extension that records instances\nof the class `self'.\" :STORAGE-SLOT CLASS-EXTENSION :INHERITS-THROUGH SUPER" "-CLASSES) (CL-NATIVE-TYPE ((SELF CLASS)) :TYPE STRING :STORAGE-SLOT CLASS-CL-NATIVE-TYPE (RETURN (CLASS-CL-NATIVE-TYPE SELF))) (CPP-NATIVE-TYPE ((SELF CLASS)) :TYPE STRING :STORAGE-SLOT CLASS-CPP-NATIVE-TYPE (RETURN (CLASS-CPP-NATIVE-TYPE SELF))) (IDL-NATIVE-TYPE ((SELF CLASS)) :TYPE STRING :STORAGE-SLOT CLASS-IDL-NATIVE-TYPE (RETURN (CLASS-CPP-NATIVE-TYPE SELF))) (JAVA-NATIVE-TYPE ((SELF CLASS)) :TYPE STRING :STORAGE-SLOT CLASS-JAVA-NATIVE-TYPE (LET ((NATIVETYPE (CLASS-JAVA-NATIVE-TYPE SELF))) (IF (DEFINED? NATIVETYPE) (RETURN (SUBSTITUTE-TEMPLATE-VARIABLES-IN-STRING NATIVETYPE *JAVA-STELLA-PACKAGE-MAPPING*)) (RETURN NULL))))) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"|C|\" (CHOOSE (DEFINED? (CLASS-TYPE SELF)) (RELATIVE-NAME (CLASS-SYMBOL SELF) FALSE) \"??\")))", 0));

      oHARDWIRED_CLASS_ARITY_ON_CLASSo = 1;
      clasS->classConstructorCode = ((cpp_function_code)(&newClass));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessClassSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("POLYMORPHIC-RELATION", "(DEFCLASS POLYMORPHIC-RELATION (RELATION) :ABSTRACT? TRUE :PUBLIC-SLOTS ((SLOT-DIRECT-EQUIVALENT :TYPE SLOT)) :PUBLIC-METHODS ((OWNER ((SELF POLYMORPHIC-RELATION)) :TYPE TYPE (RETURN NULL)) (RENAMES ((SELF POLYMORPHIC-RELATION)) :TYPE SYMBOL (RETURN NULL)) (ACTIVE? ((SELF POLYMORPHIC-RELATION)) :TYPE BOOLEAN :STORAGE-SLOT STORED-ACTIVE? :INHERITS-THROUGH EQUIVALENT-SLOT :DOCUMENTATION \"True if `self' or a superslot of `self' is marked active.\")))");

      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessPolymorphicRelationSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("SLOT", "(DEFCLASS SLOT (POLYMORPHIC-RELATION) :ABSTRACT? TRUE :PUBLIC-METHODS ((NAME ((SELF SLOT)) :TYPE STRING (RETURN (SYMBOL-NAME (SLOT-NAME SELF)))) (TYPE ((SELF SLOT)) :TYPE TYPE :STORAGE-SLOT SLOT-BASE-TYPE :INHERITS-THROUGH EQUIVALENT-SLOT :DOCUMENTATION \"The type of a storage slot is its base type.\") (TYPE-SPECIFIER ((SELF SLOT)) :TYPE TYPE-SPEC :DOCUMENTATION \"If `self' has a complex type return its\ntype specifier, otherwise, return `type' of `self'.\" (LET ((TSPEC (SLOT-TYPE-SPECIFIER SELF))) (RETURN (CHOOSE (DEFINED? TSPEC) TSPEC (TYPE SELF))))) (OWNER ((SELF SLOT)) :TYPE TYPE :STORAGE-SLOT SLOT-OWNER (RETURN (SLOT-OWNER SELF))) (HOME-MODULE ((SELF SLOT)) :TYPE MODULE (LET ((MODULE (SLOT-HOME-MODULE SELF))) (IF (DEFINED? MODULE) (RETURN MODULE) (RETURN (INTERNED-IN (SLOT-NAME SELF)))))) (RENAMES ((SELF SLOT)) :TYPE SYMBOL :STORAGE-SLOT SLOT-RENAMES (RETURN (SLOT-RENAMES SELF))) (COLLECTION-VALUED? ((SELF SLOT)) :TYPE BOOLEAN :DOCUMENTATION \"True if slot values are collections.\" (RETURN (SUBTYPE-OF? " "(SLOT-BASE-TYPE SELF) @COLLECTION))) (CLOSURE-ASSUMPTION ((SELF SLOT)) :TYPE KEYWORD :STORAGE-SLOT SLOT-CLOSURE-ASSUMPTION :INHERITS-THROUGH EQUIVALENT-SLOT)) :PUBLIC-SLOTS ((INVERSE :TYPE SLOT :ALLOCATION :DYNAMIC) (SLOT-NAME :TYPE SYMBOL) (SLOT-OWNER :TYPE TYPE) (SLOT-BASE-TYPE :TYPE TYPE) (SLOT-SLOTREF :TYPE SLOTREF) (SLOT-DIRECT-SUPERS :TYPE (LIST OF SLOT) :ALLOCATION :DYNAMIC) (SLOT-DIRECT-SUBS :TYPE (LIST OF SLOT) :ALLOCATION :DYNAMIC) (SLOT-HOME-MODULE :TYPE MODULE :ALLOCATION :DYNAMIC) (SLOT-TYPE-SPECIFIER :TYPE COMPOUND-TYPE-SPECIFIER :ALLOCATION :DYNAMIC) (SLOT-PUBLIC? :TYPE BOOLEAN :INITIALLY TRUE :OPTION-KEYWORD :PUBLIC?) (SLOT-INVERSE :TYPE SYMBOL :ALLOCATION :DYNAMIC :OPTION-KEYWORD :INVERSE) (SLOT-RENAMES :TYPE SYMBOL :ALLOCATION :DYNAMIC :OPTION-KEYWORD :RENAMES) (SLOT-RENAMED? :TYPE BOOLEAN :INITIALLY FALSE) (SLOT-DOCUMENTATION :TYPE STRING :ALLOCATION :DYNAMIC :RENAMES DOCUMENTATION :OPTION-KEYWORD :DOCUMENTATION) (SLOT-EXTERNAL? :TYPE BOOLEAN :INITIALLY FALSE) (SLOT-MARKED? :TYPE BOOLEAN) " "(SLOT-AUXILIARY? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :OPTION-KEYWORD :AUXILIARY?) (SLOT-CLOSURE-ASSUMPTION :TYPE KEYWORD :ALLOCATION :DYNAMIC)) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"|S|\" (SYMBOL-NAME (SLOT-OWNER SELF)) \".\" (SYMBOL-NAME (SLOT-NAME SELF))))");

      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessSlotSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("STORAGE-SLOT", "(DEFCLASS STORAGE-SLOT (SLOT) :PUBLIC-METHODS ((INITIALLY ((SELF STORAGE-SLOT)) :TYPE OBJECT) (ALLOCATION ((SELF STORAGE-SLOT)) :TYPE KEYWORD :STORAGE-SLOT SLOT-ALLOCATION :INHERITS-THROUGH EQUIVALENT-SLOT :DOCUMENTATION \"Return the most specific :allocation facet, or\n:instance if all inherited values are NULL.\") (DEFAULT-FORM ((SELF STORAGE-SLOT)) :TYPE OBJECT :STORAGE-SLOT SLOT-DEFAULT-EXPRESSION :INHERITS-THROUGH EQUIVALENT-SLOT :DOCUMENTATION \"Returns the current value of default expression when the\nslot has not been assigned a value.\") (REQUIRED? ((SELF STORAGE-SLOT)) :TYPE BOOLEAN :STORAGE-SLOT SLOT-REQUIRED? :INHERITS-THROUGH EQUIVALENT-SLOT :DOCUMENTATION \"True if a value must be assigned to this slot at\ncreation time.\") (COMPONENT? ((SELF STORAGE-SLOT)) :TYPE BOOLEAN :STORAGE-SLOT SLOT-COMPONENT? :INHERITS-THROUGH EQUIVALENT-SLOT :DOCUMENTATION \"True if fillers of this slot are components of the\nowner slot, and therefore should be deleted if the owner is deleted.\") (READER ((SELF STORAGE" "-SLOT)) :TYPE SYMBOL :STORAGE-SLOT SLOT-READER :INHERITS-THROUGH EQUIVALENT-SLOT :DOCUMENTATION \"Name of a method called to read the value of the slot\n`self'.\") (WRITER ((SELF STORAGE-SLOT)) :TYPE SYMBOL :STORAGE-SLOT SLOT-WRITER :INHERITS-THROUGH EQUIVALENT-SLOT :DOCUMENTATION \"Name of a method called to write the value of the slot\n`self'.\")) :PUBLIC-SLOTS ((SLOT-INITIAL-VALUE :TYPE OBJECT :ALLOCATION :DYNAMIC :OPTION-KEYWORD :INITIALLY) (SLOT-ALLOCATION :TYPE KEYWORD :ALLOCATION :DYNAMIC :DEFAULT :INSTANCE :OPTION-KEYWORD :ALLOCATION) (SLOT-DEFAULT-EXPRESSION :TYPE OBJECT :ALLOCATION :DYNAMIC :OPTION-KEYWORD :DEFAULT) (SLOT-GUARD-DEMONS :TYPE (LIST OF DEMON) :ALLOCATION :DYNAMIC) (SLOT-DEMONS :TYPE (LIST OF DEMON) :ALLOCATION :DYNAMIC) (SLOT-REQUIRED? :TYPE BOOLEAN :OPTION-KEYWORD :REQUIRED?) (SLOT-COMPONENT? :TYPE BOOLEAN :OPTION-KEYWORD :COMPONENT?) (SLOT-READ-ONLY? :TYPE BOOLEAN :OPTION-KEYWORD :READ-ONLY?) (SLOT-HARDWIRED? :TYPE BOOLEAN :OPTION-KEYWORD :HARDWIRED?) (SLOT-CONTEXT-SENSITIVE? :TYPE " "BOOLEAN :OPTION-KEYWORD :CONTEXT-SENSITIVE?) (SLOT-READER :TYPE SYMBOL :ALLOCATION :DYNAMIC :OPTION-KEYWORD :READER) (SLOT-WRITER :TYPE SYMBOL :ALLOCATION :DYNAMIC :OPTION-KEYWORD :WRITER) (SLOT-OPTION-KEYWORD :TYPE KEYWORD :ALLOCATION :DYNAMIC :OPTION-KEYWORD :OPTION-KEYWORD) (SLOT-OPTION-HANDLER :TYPE SYMBOL :ALLOCATION :DYNAMIC :OPTION-KEYWORD :OPTION-HANDLER)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newStorageSlot));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessStorageSlotSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("METHOD-SLOT", "(DEFCLASS METHOD-SLOT (SLOT) :SYNONYMS (FUNCTION) :PUBLIC-SLOTS ((STORAGE-SLOT :TYPE SYMBOL :ALLOCATION :DYNAMIC) (SLOT-REQUIRED? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :DEFAULT FALSE) (METHOD-SETTER? :TYPE BOOLEAN) (METHOD-DOCUMENTATION :TYPE STRING :ALLOCATION :DYNAMIC :RENAMES DOCUMENTATION) (METHOD-PARAMETER-NAMES :TYPE (LIST OF SYMBOL) :DEFAULT NIL-LIST :COMPONENT? TRUE) (METHOD-PARAMETER-TYPE-SPECIFIERS :TYPE (LIST OF TYPE-SPEC) :DEFAULT NIL-LIST :COMPONENT? TRUE) (METHOD-PARAMETER-DIRECTIONS :TYPE (LIST OF SYMBOL) :DEFAULT NIL-LIST :COMPONENT? TRUE :ALLOCATION :DYNAMIC) (METHOD-RETURN-TYPE-SPECIFIERS :TYPE (LIST OF TYPE-SPEC) :DEFAULT NIL-LIST :COMPONENT? TRUE) (METHOD-STRINGIFIED-SOURCE :TYPE STRING) (METHOD-CODE :TYPE CODE-WRAPPER) (FUNCTION-CODE :TYPE FUNCTION-CODE) (METHOD-FUNCTION? :TYPE BOOLEAN) (METHOD-VARIABLE-ARGUMENTS? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :DEFAULT FALSE) (METHOD-BODY-ARGUMENT? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :DEFAULT FALSE) (METHOD-AUXILIARY? :RENAMES SLOT-AUXILIARY?) (METHOD-N" "ATIVE? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :DEFAULT FALSE) (METHOD-CONSTRUCTOR? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :DEFAULT FALSE) (METHOD-GLOBALLY-INLINE? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :DEFAULT FALSE) (METHOD-INLINED-FUNCTIONS :TYPE (LIST OF SYMBOL) :ALLOCATION :DYNAMIC :DEFAULT NIL-LIST) (METHOD-STORAGE-SLOT :TYPE SYMBOL :ALLOCATION :DYNAMIC :RENAMES STORAGE-SLOT) (METHOD-INHERITS-THROUGH :TYPE SYMBOL :ALLOCATION :DYNAMIC) (METHOD-COMMAND? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :DEFAULT FALSE) (METHOD-EVALUATE-ARGUMENTS? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :DEFAULT TRUE) (METHOD-LISP-MACRO? :TYPE BOOLEAN-WRAPPER :ALLOCATION :DYNAMIC) (EVALUATOR-WRAPPER-CODE :TYPE FUNCTION-CODE :ALLOCATION :DYNAMIC) (METHOD-C-CALLABLE? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :DEFAULT FALSE :OPTION-KEYWORD :C-CALLABLE?) (C-CALLABLE-WRAPPER-CODE :TYPE FUNCTION-CODE :ALLOCATION :DYNAMIC)) :PUBLIC-METHODS ((SETTER? ((SELF METHOD-SLOT)) :TYPE BOOLEAN :STORAGE-SLOT METHOD-SETTER? (RETURN (METHOD-SETTER? SELF)))) :PRINT-FORM (IF (METHOD" "-FUNCTION? SELF) (PRINT-NATIVE-STREAM STREAM \"|F|\" (SYMBOL-NAME (SLOT-NAME SELF))) (PRINT-NATIVE-STREAM STREAM \"|M|\" (SYMBOL-NAME (SLOT-OWNER SELF)) \".\" (SYMBOL-NAME (SLOT-NAME SELF)))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newMethodSlot));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessMethodSlotSlotValue));
    }
    defineClassFromStringifiedSource("COMPOUND-TYPE-SPECIFIER", "(DEFCLASS COMPOUND-TYPE-SPECIFIER (STANDARD-OBJECT) :ABSTRACT? TRUE :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"|TS|\" (YIELD-TYPE-SPEC-TREE SELF)))");
    { Class* clasS = defineClassFromStringifiedSource("PARAMETRIC-TYPE-SPECIFIER", "(DEFCLASS PARAMETRIC-TYPE-SPECIFIER (COMPOUND-TYPE-SPECIFIER) :PUBLIC-SLOTS ((SPECIFIER-BASE-TYPE :TYPE TYPE) (SPECIFIER-PARAMETER-TYPES :TYPE (LIST OF TYPE-SPEC) :ALLOCATION :EMBEDDED) (SPECIFIER-DIMENSIONS :TYPE (LIST OF OBJECT))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newParametricTypeSpecifier));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessParametricTypeSpecifierSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("ANCHORED-TYPE-SPECIFIER", "(DEFCLASS ANCHORED-TYPE-SPECIFIER (COMPOUND-TYPE-SPECIFIER) :PUBLIC-SLOTS ((SPECIFIER-PARAMETER-NAME :TYPE SYMBOL)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newAnchoredTypeSpecifier));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessAnchoredTypeSpecifierSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("TABLE", "(DEFCLASS TABLE (SLOT) :PARAMETERS ((ANY-VALUE :TYPE BOOLEAN)) :PUBLIC-SLOTS ((TUPLE-DOMAINS :TYPE (LIST OF TYPE-SPEC)) (VARIABLE-ARITY-TABLE? :TYPE BOOLEAN :ALLOCATION :DYNAMIC)) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"|T|\" (SYMBOL-NAME (SLOT-NAME SELF))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newTable));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTableSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("GLOBAL-VARIABLE", "(DEFCLASS GLOBAL-VARIABLE (MAPPABLE-OBJECT) :PUBLIC-SLOTS ((DOCUMENTATION :TYPE STRING)) :PUBLIC-METHODS ((NAME ((SELF GLOBAL-VARIABLE)) :TYPE STRING (RETURN (SYMBOL-NAME (VARIABLE-NAME SELF)))) (TYPE ((SELF GLOBAL-VARIABLE)) :TYPE TYPE :STORAGE-SLOT VARIABLE-TYPE (RETURN (VARIABLE-TYPE SELF))) (HOME-MODULE ((SELF GLOBAL-VARIABLE)) :TYPE MODULE (LET ((MODULE (VARIABLE-HOME-MODULE SELF))) (IF (DEFINED? MODULE) (RETURN MODULE) (RETURN (INTERNED-IN (VARIABLE-NAME SELF))))))) :PUBLIC-SLOTS ((VARIABLE-NAME :TYPE SYMBOL) (VARIABLE-TYPE :TYPE TYPE) (VARIABLE-TYPE-SPECIFIER :TYPE TYPE-SPEC :ALLOCATION :DYNAMIC) (VARIABLE-HOME-MODULE :TYPE MODULE :ALLOCATION :DYNAMIC) (VARIABLE-SPECIAL? :TYPE BOOLEAN) (VARIABLE-CONSTANT? :TYPE BOOLEAN) (VARIABLE-PUBLIC? :TYPE BOOLEAN :INITIALLY TRUE) (VARIABLE-AUXILIARY? :TYPE BOOLEAN) (VARIABLE-THREAD-LOCAL? :TYPE BOOLEAN :OPTION-KEYWORD :THREAD-LOCAL? :ALLOCATION :DYNAMIC :DOCUMENTATION \"If true, the variable will be allocated on a per-thread\nbasis similar to specials for which t" "his is always true.  CAUTION: this is\nonly a documentation place holder so far and not yet used by the translators.\") (VARIABLE-NATIVE-OBJECT :TYPE NATIVE-OBJECT-POINTER :INITIALLY NULL :DOCUMENTATION \"Points to a handle that can be used to access the native value.\") (VARIABLE-DOCUMENTATION :TYPE STRING :RENAMES DOCUMENTATION) (VARIABLE-STRINGIFIED-SOURCE :TYPE STRING)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newGlobalVariable));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessGlobalVariableSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("QUOTED-EXPRESSION", "(DEFCLASS QUOTED-EXPRESSION (STANDARD-OBJECT) :PUBLIC-SLOTS ((QUOTATION-TABLE-OFFSET :TYPE INTEGER)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newQuotedExpression));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessQuotedExpressionSlotValue));
    }
    defineClassFromStringifiedSource("VOID", "(DEFCLASS VOID () :ABSTRACT? TRUE :JAVA-NATIVE-TYPE \"void\" :IDL-NATIVE-TYPE \"void\" :CPP-NATIVE-TYPE \"void\")");
    defineClassFromStringifiedSource("UNKNOWN", "(DEFCLASS UNKNOWN () :ABSTRACT? TRUE :CPP-NATIVE-TYPE \"unknown\" :IDL-NATIVE-TYPE \"unknown\" :JAVA-NATIVE-TYPE \"unknown\" :SLOTS ((UNKNOWN-SLOT :TYPE UNKNOWN)))");
    { Class* clasS = defineClassFromStringifiedSource("THING", "(DEFCLASS THING (STANDARD-OBJECT DYNAMIC-SLOTS-MIXIN) :ABSTRACT? TRUE :DOCUMENTATION \"Defines a class that must be inherited by any\nclass that participates in the PowerLoom side of things.\" :PUBLIC-SLOTS ((SURROGATE-VALUE-INVERSE :TYPE SURROGATE)) :PRINT-FORM (IF (DEFINED? (SURROGATE-VALUE-INVERSE SELF)) (PRINT-NATIVE-STREAM STREAM \"|i|\" (SYMBOL-NAME (SURROGATE-VALUE-INVERSE SELF))) (PRINT-NATIVE-STREAM STREAM \"|i|\" (PRIMARY-TYPE SELF))))");

      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessThingSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("CONTEXT", "(DEFCLASS CONTEXT (THING) :ABSTRACT? TRUE :PUBLIC-SLOTS ((CHILD-CONTEXTS :TYPE (LIST OF CONTEXT) :ALLOCATION :EMBEDDED) (BASE-MODULE :TYPE MODULE) (ALL-SUPER-CONTEXTS :TYPE (CONS OF CONTEXT)) (CONTEXT-NUMBER :TYPE INTEGER)) :METHODS ((CONTEXT-NAME ((SELF CONTEXT)) :TYPE STRING (LET ((AUX SELF)) (TYPECASE AUX (MODULE (RETURN (MODULE-NAME AUX))) (WORLD (RETURN (WORLD-NAME AUX)))))) (PARENT-CONTEXTS ((SELF CONTEXT)) :TYPE (ITERATOR OF CONTEXT)) (HOME-MODULE ((SELF CONTEXT)) :TYPE MODULE :PUBLIC? TRUE (RETURN (BASE-MODULE SELF)))) :PRINT-FORM (PRINT-CONTEXT SELF STREAM))");

      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessContextSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("MODULE", "(DEFCLASS MODULE (CONTEXT) :PUBLIC-SLOTS ((PARENT-MODULES :TYPE (LIST OF MODULE) :ALLOCATION :EMBEDDED) (DOCUMENTATION :TYPE STRING :OPTION-KEYWORD :DOCUMENTATION) (NICKNAMES :TYPE (LIST OF STRING-WRAPPER) :OPTION-KEYWORD :NICKNAMES) (USES :TYPE (LIST OF MODULE) :ALLOCATION :EMBEDDED :OPTION-KEYWORD :USES) (USED-BY :TYPE (LIST OF MODULE) :ALLOCATION :EMBEDDED) (SHADOWED-SURROGATES :TYPE (LIST OF SURROGATE) :ALLOCATION :DYNAMIC) (REQUIRES :TYPE (LIST OF MODULE) :OPTION-KEYWORD :REQUIRES) (MODULE-LISP-PACKAGE :TYPE STRING :DEFAULT \"STELLA\" :ALLOCATION :DYNAMIC :OPTION-KEYWORD :MODULE-LISP-PACKAGE) (MODULE-CPP-PACKAGE :TYPE STRING :DEFAULT \"stella\" :ALLOCATION :DYNAMIC :OPTION-KEYWORD :MODULE-CPP-PACKAGE) (JAVA-PACKAGE :TYPE STRING :DEFAULT NULL :ALLOCATION :DYNAMIC :OPTION-KEYWORD :JAVA-PACKAGE) (CASE-SENSITIVE? :TYPE BOOLEAN :INITIALLY FALSE :OPTION-KEYWORD :CASE-SENSITIVE?) (CLEARABLE? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :DEFAULT TRUE :OPTION-KEYWORD :CLEARABLE?) (CODE-ONLY? :TYPE BOOLEAN :ALLOCATION :DYN" "AMIC :OPTION-KEYWORD :CODE-ONLY?) (NAMESPACE? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :OPTION-KEYWORD :NAMESPACE?) (API? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :OPTION-KEYWORD :API?) (PROTECT-SURROGATES? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :OPTION-KEYWORD :PROTECT-SURROGATES? :DEFAULT TRUE) (JAVA-FLOTSAM-CLASS :TYPE STRING :ALLOCATION :DYNAMIC :OPTION-KEYWORD :JAVA-CATCHALL-CLASS) (MODULE-FULL-NAME :TYPE STRING) (MODULE-NAME :TYPE STRING :ALLOCATION :INSTANCE) (MODULE-STRINGIFIED-SOURCE :TYPE STRING) (STRINGIFIED-OPTIONS :TYPE STRING) (CARDINAL-MODULE :TYPE MODULE) (SYMBOL-OFFSET-TABLE :TYPE STRING-TO-INTEGER-HASH-TABLE) (SURROGATE-OFFSET-TABLE :TYPE STRING-TO-INTEGER-HASH-TABLE) (STRICT-INFERENCE-CACHE :TYPE WORLD) (DEFAULT-INFERENCE-CACHE :TYPE WORLD) (PROTOTYPE-INFERENCE-CACHE :TYPE WORLD)) :PUBLIC-METHODS ((NAME ((SELF MODULE)) :TYPE STRING (RETURN (MODULE-NAME SELF))) (PARENT-MODULE ((SELF MODULE)) :TYPE MODULE (RETURN (POP (PARENT-CONTEXTS SELF)))) (LISP-PACKAGE ((SELF MODULE)) :TYPE STRING :STORAGE-SLOT MODULE-" "LISP-PACKAGE :INHERITS-THROUGH PARENT-MODULES) (CPP-PACKAGE ((SELF MODULE)) :TYPE STRING :STORAGE-SLOT MODULE-CPP-PACKAGE :INHERITS-THROUGH PARENT-MODULES)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newModule));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessModuleSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("WORLD", "(DEFCLASS WORLD (CONTEXT) :PUBLIC-SLOTS ((PARENT-CONTEXT :TYPE CONTEXT) (CHILD-CONTEXTS :TYPE (LIST OF WORLD) :ALLOCATION :EMBEDDED) (WORLD-NAME :TYPE STRING :ALLOCATION :DYNAMIC)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newWorld));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessWorldSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("CS-VALUE", "(DEFCLASS CS-VALUE (KEY-VALUE-LIST) :DOCUMENTATION \"Contextualized value.  Contains a sorted kv-cons list indexed\nby context. The kv-cons list is never null.  Newer (higher numbered) contexts\nappear first.\" :PARAMETERS ((ANY-KEY :TYPE CONTEXT) (ANY-VALUE :TYPE OBJECT)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newCsValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("INTERVAL", "(DEFCLASS INTERVAL (STANDARD-OBJECT) :PUBLIC-SLOTS ((LOWER-BOUND :TYPE INTEGER) (UPPER-BOUND :TYPE INTEGER)) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"[\" (LOWER-BOUND SELF) \",\" (UPPER-BOUND SELF) \"]\"))");

      clasS->classConstructorCode = ((cpp_function_code)(&newInterval));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessIntervalSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("TAXONOMY-NODE", "(DEFCLASS TAXONOMY-NODE (STANDARD-OBJECT) :PUBLIC-SLOTS ((NATIVE-OBJECT :TYPE OBJECT) (LABEL :TYPE INTEGER) (INTERVALS :TYPE (CONS OF INTERVAL) :INITIALLY NIL) (INITIAL-INTERVAL :TYPE INTERVAL) (FIRST-INTERVAL-LOWER-BOUND :TYPE INTEGER :INITIALLY -1) (FIRST-INTERVAL-UPPER-BOUND :TYPE INTEGER :INITIALLY -1) (PARENTS :TYPE (CONS OF TAXONOMY-NODE) :INITIALLY NIL) (CHILDREN :TYPE (CONS OF TAXONOMY-NODE) :INITIALLY NIL) (TOTAL-ANCESTORS :TYPE INTEGER :INITIALLY 1) (TREE-CHILDREN :TYPE (CONS OF TAXONOMY-NODE) :INITIALLY NIL) (MARKER :TYPE OBJECT)) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"|TN|\" (LABEL SELF) \" \" (INTERVALS SELF) \" \" (NATIVE-OBJECT SELF)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newTaxonomyNode));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTaxonomyNodeSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("TAXONOMY-GRAPH", "(DEFCLASS TAXONOMY-GRAPH (STANDARD-OBJECT) :PUBLIC-SLOTS ((RENUMBER-IF-OUT-OF-NUMBERS? :DOCUMENTATION \"If TRUE, relabel the entire graph when a new interval\nfor an incrementally inserted node can't be allocated due to lack of\nsplittable interval space.  Otherwise, create a `foreign' interval and\npropagate it.\" :TYPE BOOLEAN :INITIALLY FALSE) (RENUMBER-RATIO :DOCUMENTATION \"Whenever the ratio between foreign intervals and\nnon-foreign intervals becomes greater than `renumber-ratio', relabel\nthe whole graph non-incrementally.\" :TYPE FLOAT :INITIALLY 0.1)) :SLOTS ((INCREMENTAL-MODE? :TYPE BOOLEAN) (LARGEST-POSTORDER-NUMBER :TYPE INTEGER) (NUMBER-OF-NODES :TYPE INTEGER) (NUMBER-OF-FOREIGN-INTERVAL-NODES :TYPE INTEGER) (ROOTS :TYPE (LIST OF TAXONOMY-NODE)) (BROKEN-LINKS :TYPE (LIST OF (CONS OF TAXONOMY-NODE))) (ADDED-LINKS :TYPE (LIST OF (CONS OF TAXONOMY-NODE))) (REMOVED-LINKS :TYPE (LIST OF (CONS OF TAXONOMY-NODE)))) :INITIALIZER INITIALIZE-TAXONOMY-GRAPH :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"|TG|\"" " (ROOTS SELF)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newTaxonomyGraph));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTaxonomyGraphSlotValue));
    }
    defineClassFromStringifiedSource("NATIVE-EXCEPTION", "(DEFCLASS NATIVE-EXCEPTION () :JAVA-NATIVE-TYPE \"java.lang.Exception\" :CL-NATIVE-TYPE \"CONDITION\" :CPP-NATIVE-TYPE \"std::exception\")");
    defineClassFromStringifiedSource("STELLA-ROOT-EXCEPTION", "(DEFCLASS STELLA-ROOT-EXCEPTION (NATIVE-EXCEPTION) :PUBLIC-SLOTS ((MESSAGE :TYPE STRING :READER EXCEPTION-MESSAGE :REQUIRED? TRUE :ABSTRACT? TRUE)) :ABSTRACT? TRUE :JAVA-NATIVE-TYPE \"java.lang.RuntimeException\" :CL-NATIVE-TYPE \"SIMPLE-ERROR\" :CPP-NATIVE-TYPE \"std::runtime_error\")");
    { Class* clasS = defineClassFromStringifiedSource("STELLA-EXCEPTION", "(DEFCLASS STELLA-EXCEPTION (STELLA-ROOT-EXCEPTION) :PUBLIC? TRUE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newStellaException));
    }
    { Class* clasS = defineClassFromStringifiedSource("INPUT-OUTPUT-EXCEPTION", "(DEFCLASS INPUT-OUTPUT-EXCEPTION (STELLA-EXCEPTION) :PUBLIC? TRUE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newInputOutputException));
    }
    { Class* clasS = defineClassFromStringifiedSource("READ-EXCEPTION", "(DEFCLASS READ-EXCEPTION (INPUT-OUTPUT-EXCEPTION) :PUBLIC? TRUE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newReadException));
    }
    { Class* clasS = defineClassFromStringifiedSource("END-OF-FILE-EXCEPTION", "(DEFCLASS END-OF-FILE-EXCEPTION (INPUT-OUTPUT-EXCEPTION) :PUBLIC? TRUE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newEndOfFileException));
    }
    { Class* clasS = defineClassFromStringifiedSource("NO-SUCH-FILE-EXCEPTION", "(DEFCLASS NO-SUCH-FILE-EXCEPTION (INPUT-OUTPUT-EXCEPTION) :PUBLIC? TRUE :PUBLIC-SLOTS ((FILENAME :TYPE STRING)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newNoSuchFileException));
    }
    { Class* clasS = defineClassFromStringifiedSource("FILE-ALREADY-EXISTS-EXCEPTION", "(DEFCLASS FILE-ALREADY-EXISTS-EXCEPTION (INPUT-OUTPUT-EXCEPTION) :PUBLIC? TRUE :PUBLIC-SLOTS ((FILENAME :TYPE STRING)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newFileAlreadyExistsException));
    }
    { Class* clasS = defineClassFromStringifiedSource("UNHANDLED-EXCEPTION", "(DEFCLASS UNHANDLED-EXCEPTION (STELLA-EXCEPTION) :PUBLIC? TRUE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newUnhandledException));
    }
    { Class* clasS = defineClassFromStringifiedSource("EVALUATION-EXCEPTION", "(DEFCLASS EVALUATION-EXCEPTION (STELLA-EXCEPTION) :PUBLIC? TRUE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newEvaluationException));
    }
    { Class* clasS = defineClassFromStringifiedSource("NO-SUCH-OBJECT-EXCEPTION", "(DEFCLASS NO-SUCH-OBJECT-EXCEPTION (STELLA-EXCEPTION) :PUBLIC? TRUE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newNoSuchObjectException));
    }
    { Class* clasS = defineClassFromStringifiedSource("NO-SUCH-CONTEXT-EXCEPTION", "(DEFCLASS NO-SUCH-CONTEXT-EXCEPTION (NO-SUCH-OBJECT-EXCEPTION) :PUBLIC? TRUE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newNoSuchContextException));
    }
    { Class* clasS = defineClassFromStringifiedSource("UNDEFINED-CLASS-EXCEPTION", "(DEFCLASS UNDEFINED-CLASS-EXCEPTION (NO-SUCH-OBJECT-EXCEPTION) :PUBLIC? TRUE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newUndefinedClassException));
    }
    { Class* clasS = defineClassFromStringifiedSource("BAD-ARGUMENT-EXCEPTION", "(DEFCLASS BAD-ARGUMENT-EXCEPTION (STELLA-EXCEPTION) :PUBLIC? TRUE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newBadArgumentException));
    }
    { Class* clasS = defineClassFromStringifiedSource("OBJECT-NOT-CLASS-EXCEPTION", "(DEFCLASS OBJECT-NOT-CLASS-EXCEPTION (BAD-ARGUMENT-EXCEPTION) :PUBLIC? TRUE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newObjectNotClassException));
    }
    { Class* clasS = defineClassFromStringifiedSource("INCOMPATIBLE-QUANTITY-EXCEPTION", "(DEFCLASS INCOMPATIBLE-QUANTITY-EXCEPTION (STELLA-EXCEPTION) :PUBLIC? TRUE :DOCUMENTATION \"Exception thrown when an operation is attempted on quantities\nthat are not compatible with the requested operation.  For example,\ncomparing dates and time durations.\")");

      clasS->classConstructorCode = ((cpp_function_code)(&newIncompatibleQuantityException));
    }
    { Class* clasS = defineClassFromStringifiedSource("TIMEOUT-EXCEPTION", "(DEFCLASS TIMEOUT-EXCEPTION (STELLA-EXCEPTION) :PUBLIC? TRUE)");

      clasS->classConstructorCode = ((cpp_function_code)(&newTimeoutException));
    }
    defineClassFromStringifiedSource("QUANTITY", "(DEFCLASS QUANTITY (OBJECT) :PUBLIC? TRUE :ABSTRACT? TRUE :DOCUMENTATION \"General superclass for extensible quantity objects\" :PUBLIC-METHODS ((COERCE-TO ((SELF QUANTITY) (OTHER OBJECT)) :TYPE QUANTITY (IF (ISA? OTHER (PRIMARY-TYPE SELF)) (RETURN OTHER) (RETURN NULL))) (LESS? ((SELF QUANTITY) (OTHER OBJECT)) :TYPE BOOLEAN (IGNORE OTHER) (RETURN FALSE)) (LESS-EQUAL? ((SELF QUANTITY) (OTHER OBJECT)) :TYPE BOOLEAN (RETURN (OR (OBJECT-EQL? SELF OTHER) (LESS? SELF OTHER)))) (GREATER-EQUAL? ((SELF QUANTITY) (OTHER OBJECT)) :TYPE BOOLEAN (RETURN (OR (OBJECT-EQL? SELF OTHER) (GREATER? SELF OTHER)))) (GREATER? ((SELF QUANTITY) (OTHER OBJECT)) :TYPE BOOLEAN (IGNORE OTHER) (RETURN FALSE))))");
    defineClassFromStringifiedSource("LITERAL", "(DEFCLASS LITERAL (NON-OBJECT) :ABSTRACT? TRUE)");
    defineClassFromStringifiedSource("NUMBER", "(DEFCLASS NUMBER (LITERAL) :ABSTRACT? TRUE)");
    defineClassFromStringifiedSource("INTEGER", "(DEFCLASS INTEGER (NUMBER) :CL-NATIVE-TYPE \"FIXNUM\" :CPP-NATIVE-TYPE \"int\" :IDL-NATIVE-TYPE \"long\" :JAVA-NATIVE-TYPE \"int\" :INITIAL-VALUE NULL-INTEGER :EQUALITY-TEST EQL?)");
    defineClassFromStringifiedSource("FLOAT", "(DEFCLASS FLOAT (NUMBER) :CL-NATIVE-TYPE \"FLOAT\" :CPP-NATIVE-TYPE \"double\" :IDL-NATIVE-TYPE \"double\" :JAVA-NATIVE-TYPE \"double\" :INITIAL-VALUE NULL-FLOAT :EQUALITY-TEST EQL?)");
    defineClassFromStringifiedSource("MUTABLE-STRING", "(DEFCLASS MUTABLE-STRING (LITERAL) :CL-NATIVE-TYPE \"STRING\" :IDL-NATIVE-TYPE \"string\" :JAVA-NATIVE-TYPE \"StringBuffer\" :CPP-NATIVE-TYPE \"char*\" :EQUALITY-TEST STRING-EQL? :INITIAL-VALUE (VERBATIM :COMMON-LISP \"STELLA::NULL-STRING\" :JAVA \"null\" :CPP \"NULL\"))");
    defineClassFromStringifiedSource("STRING", "(DEFCLASS STRING (LITERAL) :SYNONYMS (FILE-NAME) :CL-NATIVE-TYPE \"STRING\" :IDL-NATIVE-TYPE \"string\" :JAVA-NATIVE-TYPE \"String\" :CPP-NATIVE-TYPE \"const char*\" :EQUALITY-TEST STRING-EQL? :INITIAL-VALUE (VERBATIM :COMMON-LISP \"STELLA::NULL-STRING\" :JAVA \"null\" :CPP \"NULL\"))");
    defineClassFromStringifiedSource("CHARACTER", "(DEFCLASS CHARACTER (LITERAL) :CL-NATIVE-TYPE \"CHARACTER\" :CPP-NATIVE-TYPE \"char\" :IDL-NATIVE-TYPE \"char\" :JAVA-NATIVE-TYPE \"char\" :INITIAL-VALUE NULL-CHARACTER)");
    defineClassFromStringifiedSource("SHORT-INTEGER", "(DEFCLASS SHORT-INTEGER (NUMBER) :CL-NATIVE-TYPE \"FIXNUM\" :CPP-NATIVE-TYPE \"short int\" :IDL-NATIVE-TYPE \"short int\" :JAVA-NATIVE-TYPE \"short\" :INITIAL-VALUE NULL-SHORT-INTEGER :EQUALITY-TEST EQL?)");
    defineClassFromStringifiedSource("LONG-INTEGER", "(DEFCLASS LONG-INTEGER (NUMBER) :CL-NATIVE-TYPE \"INTEGER\" :CPP-NATIVE-TYPE \"long long int\" :IDL-NATIVE-TYPE \"long int\" :JAVA-NATIVE-TYPE \"long\" :INITIAL-VALUE NULL-LONG-INTEGER :EQUALITY-TEST EQL?)");
    defineClassFromStringifiedSource("UNSIGNED-SHORT-INTEGER", "(DEFCLASS UNSIGNED-SHORT-INTEGER (NUMBER) :CL-NATIVE-TYPE \"INTEGER\" :CPP-NATIVE-TYPE \"unsigned short int\" :IDL-NATIVE-TYPE \"unsigned short int\" :JAVA-NATIVE-TYPE \"short\" :INITIAL-VALUE NULL-UNSIGNED-SHORT-INTEGER :EQUALITY-TEST EQL?)");
    defineClassFromStringifiedSource("UNSIGNED-LONG-INTEGER", "(DEFCLASS UNSIGNED-LONG-INTEGER (NUMBER) :CL-NATIVE-TYPE \"INTEGER\" :IDL-NATIVE-TYPE \"unsigned long int\" :CPP-NATIVE-TYPE \"unsigned long int\" :JAVA-NATIVE-TYPE \"long\" :INITIAL-VALUE NULL-UNSIGNED-LONG-INTEGER :EQUALITY-TEST EQL?)");
    defineClassFromStringifiedSource("SINGLE-FLOAT", "(DEFCLASS SINGLE-FLOAT (NUMBER) :CL-NATIVE-TYPE \"FLOAT\" :JAVA-NATIVE-TYPE \"float\" :IDL-NATIVE-TYPE \"float\" :CPP-NATIVE-TYPE \"float\" :INITIAL-VALUE NULL-SINGLE-FLOAT :EQUALITY-TEST EQL?)");
    defineClassFromStringifiedSource("DOUBLE-FLOAT", "(DEFCLASS DOUBLE-FLOAT (NUMBER) :CL-NATIVE-TYPE \"FLOAT\" :CPP-NATIVE-TYPE \"double\" :JAVA-NATIVE-TYPE \"double\" :IDL-NATIVE-TYPE \"double\" :INITIAL-VALUE NULL-DOUBLE-FLOAT :EQUALITY-TEST EQL?)");
  }
}

void helpStartupHierarchy10() {
  {
    defineClassFromStringifiedSource("BYTE", "(DEFCLASS BYTE (LITERAL) :CL-NATIVE-TYPE \"FIXNUM\" :CPP-NATIVE-TYPE \"char\" :IDL-NATIVE-TYPE \"char\" :JAVA-NATIVE-TYPE \"byte\" :INITIAL-VALUE NULL-BYTE :EQUALITY-TEST EQL?)");
    defineClassFromStringifiedSource("OCTET", "(DEFCLASS OCTET (BYTE) :CL-NATIVE-TYPE \"FIXNUM\" :CPP-NATIVE-TYPE \"char\" :IDL-NATIVE-TYPE \"octet\" :JAVA-NATIVE-TYPE \"byte\" :INITIAL-VALUE NULL-OCTET :EQUALITY-TEST EQL?)");
    defineClassFromStringifiedSource("WRAPPER", "(DEFCLASS WRAPPER (OBJECT) :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE UNKNOWN :REQUIRED? TRUE)) :KEY (WRAPPER-VALUE) :PUBLIC? TRUE :ABSTRACT? TRUE)");
    defineClassFromStringifiedSource("LITERAL-WRAPPER", "(DEFCLASS LITERAL-WRAPPER (WRAPPER) :ABSTRACT? TRUE)");
    defineClassFromStringifiedSource("NUMBER-WRAPPER", "(DEFCLASS NUMBER-WRAPPER (LITERAL-WRAPPER) :ABSTRACT? TRUE)");
    { Class* clasS = defineClassFromStringifiedSource("INTEGER-WRAPPER", "(DEFCLASS INTEGER-WRAPPER (NUMBER-WRAPPER) :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE INTEGER)) :PRINT-FORM (LET ((VALUE (WRAPPER-VALUE SELF))) (IF (NULL? VALUE) (IF *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM (QUOTE NULL-INTEGER)) (PRINT-NATIVE-STREAM STREAM \"|L|NULL-INTEGER\")) (IF *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM VALUE) (PRINT-NATIVE-STREAM STREAM \"|L|\" VALUE)))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newIntegerWrapper));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessIntegerWrapperSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("LONG-INTEGER-WRAPPER", "(DEFCLASS LONG-INTEGER-WRAPPER (NUMBER-WRAPPER) :SLOTS ((WRAPPER-VALUE :TYPE LONG-INTEGER)) :PRINT-FORM (LET ((VALUE (WRAPPER-VALUE SELF))) (IF (NULL? VALUE) (IF *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM (QUOTE NULL-LONG-INTEGER)) (PRINT-NATIVE-STREAM STREAM \"|L|NULL-LONG-INTEGER\")) (IF *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM VALUE) (PRINT-NATIVE-STREAM STREAM \"|L|\" VALUE)))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newLongIntegerWrapper));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessLongIntegerWrapperSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("FLOAT-WRAPPER", "(DEFCLASS FLOAT-WRAPPER (NUMBER-WRAPPER) :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE FLOAT)) :PRINT-FORM (LET ((VALUE (WRAPPER-VALUE SELF))) (IF (NULL? VALUE) (IF *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM (QUOTE NULL-FLOAT)) (PRINT-NATIVE-STREAM STREAM \"|L|NULL-FLOAT\")) (IF *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM VALUE) (PRINT-NATIVE-STREAM STREAM \"|L|\" VALUE)))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newFloatWrapper));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessFloatWrapperSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("STRING-WRAPPER", "(DEFCLASS STRING-WRAPPER (LITERAL-WRAPPER) :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE STRING)) :PRINT-FORM (LET ((VALUE (WRAPPER-VALUE SELF))) (IF (NULL? VALUE) (IF *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM (QUOTE NULL-STRING)) (PRINT-NATIVE-STREAM STREAM \"|L|NULL-STRING\")) (IF *PRINTREADABLY?* (PRINT-STRING-READABLY VALUE STREAM) (PRINT-NATIVE-STREAM STREAM \"|L|\" #\\\" VALUE #\\\")))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newStringWrapper));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessStringWrapperSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("MUTABLE-STRING-WRAPPER", "(DEFCLASS MUTABLE-STRING-WRAPPER (LITERAL-WRAPPER) :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE MUTABLE-STRING)) :PRINT-FORM (LET ((VALUE (WRAPPER-VALUE SELF))) (IF (NULL? VALUE) (IF *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM (QUOTE NULL-MUTABLE-STRING)) (PRINT-NATIVE-STREAM STREAM \"|L|NULL-MUTABLE-STRING\")) (IF *PRINTREADABLY?* (PRINT-STRING-READABLY VALUE STREAM) (PRINT-NATIVE-STREAM STREAM \"|L|\" #\\\" (MUTABLE-STRING-TO-STRING VALUE) #\\\")))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newMutableStringWrapper));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessMutableStringWrapperSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("CHARACTER-WRAPPER", "(DEFCLASS CHARACTER-WRAPPER (LITERAL-WRAPPER) :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE CHARACTER)) :PRINT-FORM (LET ((VALUE (WRAPPER-VALUE SELF))) (IF (NULL? VALUE) (IF *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM (QUOTE NULL-CHARACTER)) (PRINT-NATIVE-STREAM STREAM \"|L|NULL-CHARACTER\")) (PROGN (UNLESS *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM \"|L|\")) (PRINT-CHARACTER VALUE STREAM)))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newCharacterWrapper));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessCharacterWrapperSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("BOOLEAN-WRAPPER", "(DEFCLASS BOOLEAN-WRAPPER (LITERAL-WRAPPER) :DOCUMENTATION \"Objectified version of the BOOLEAN data type.  The NULL\nvalue can be used for a 3-valued semantics (see THREE-VALUED-BOOLEAN).\" :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE BOOLEAN :ALLOCATION :INSTANCE)) :PRINT-FORM (PROGN (UNLESS *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM \"|L|\")) (IF (WRAPPER-VALUE SELF) (PRINT-NATIVE-STREAM STREAM (QUOTE TRUE)) (PRINT-NATIVE-STREAM STREAM (QUOTE FALSE)))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newBooleanWrapper));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessBooleanWrapperSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("CODE-WRAPPER", "(DEFCLASS CODE-WRAPPER (WRAPPER) :ABSTRACT? TRUE :PUBLIC-SLOTS ((METHOD-CODE? :TYPE BOOLEAN :INITIALLY FALSE :DOCUMENTATION \"Redundant slot that supports a fast type test.\")))");

      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessCodeWrapperSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("FUNCTION-CODE-WRAPPER", "(DEFCLASS FUNCTION-CODE-WRAPPER (CODE-WRAPPER) :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE FUNCTION-CODE)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newFunctionCodeWrapper));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessFunctionCodeWrapperSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("METHOD-CODE-WRAPPER", "(DEFCLASS METHOD-CODE-WRAPPER (CODE-WRAPPER) :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE METHOD-CODE) (METHOD-CODE? :INITIALLY TRUE)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newMethodCodeWrapper));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessMethodCodeWrapperSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("VERBATIM-STRING-WRAPPER", "(DEFCLASS VERBATIM-STRING-WRAPPER (STRING-WRAPPER) :DOCUMENTATION \"Wrapper class used to hold verbatim native code strings.\" :PRINT-FORM (PRINT-NATIVE-STREAM STREAM (CHOOSE *PRINTREADABLY?* \"\" \"|V|\") (WRAPPER-VALUE SELF)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newVerbatimStringWrapper));
    }
    { Class* clasS = defineClassFromStringifiedSource("NATIVE-OBJECT-POINTER-WRAPPER", "(DEFCLASS NATIVE-OBJECT-POINTER-WRAPPER (WRAPPER) :DOCUMENTATION \"Wrapper class for native object pointers so that they can be\nstored in standard collection classes as well as in dynamic slots.\" :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE NATIVE-OBJECT-POINTER)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newNativeObjectPointerWrapper));
    }
    { Class* clasS = defineClassFromStringifiedSource("EXCEPTION-WRAPPER", "(DEFCLASS EXCEPTION-WRAPPER (WRAPPER) :DOCUMENTATION \"Wrapper class for exceptions so they can be stored in standard\ncollection classes as well as in dynamic slots.  NOTE: in order to determine the\nexact type of the wrapped native exception, it has to be signaled and caught in\nan `exception-case' statement, a normal `type-case' will not work here.\" :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE NATIVE-EXCEPTION)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newExceptionWrapper));
    }
    defineClassFromStringifiedSource("BOOLEAN", "(DEFCLASS BOOLEAN (LITERAL) :DOCUMENTATION \"Boolean type with values TRUE and FALSE.\" :INITIAL-VALUE FALSE :CL-NATIVE-TYPE \"FIXNUM\" :CPP-NATIVE-TYPE \"boolean\" :IDL-NATIVE-TYPE \"boolean\" :JAVA-NATIVE-TYPE \"boolean\")");
    defineClassFromStringifiedSource("ONE-BIT-BOOLEAN", "(DEFCLASS ONE-BIT-BOOLEAN (BOOLEAN) :DOCUMENTATION \"Space-saving representation of BOOLEAN which takes longer\nto read and write than BOOLEAN.  Not yet implemented.\" :CPP-NATIVE-TYPE \"one_bit_boolean\")");
    defineStellaTypeFromStringifiedSource("(DEFTYPE THREE-VALUED-BOOLEAN BOOLEAN-WRAPPER)");
    defineClassFromStringifiedSource("CODE", "(DEFCLASS CODE (LITERAL) :ABSTRACT? TRUE)");
    defineClassFromStringifiedSource("FUNCTION-CODE", "(DEFCLASS FUNCTION-CODE (CODE) :CL-NATIVE-TYPE \"FUNCTION\" :JAVA-NATIVE-TYPE \"java.lang.reflect.Method\" :CPP-NATIVE-TYPE \"cpp_function_code\")");
    defineClassFromStringifiedSource("METHOD-CODE", "(DEFCLASS METHOD-CODE (CODE) :CL-NATIVE-TYPE \"STANDARD-GENERIC-FUNCTION\" :JAVA-NATIVE-TYPE \"java.lang.reflect.Method\" :CPP-NATIVE-TYPE \"cpp_method_code\" :INITIAL-VALUE (SAFE-CAST NULL @METHOD-CODE))");
    defineClassFromStringifiedSource("LISP-CODE", "(DEFCLASS LISP-CODE () :ABSTRACT? TRUE :DOCUMENTATION \"Used to indicate variables that input or output Common Lisp~\n      structures.\")");
    defineClassFromStringifiedSource("THIRTY-TWO-BIT-VECTOR", "(DEFCLASS THIRTY-TWO-BIT-VECTOR (INTEGER) :CL-NATIVE-TYPE \"FIXNUM\" :CPP-NATIVE-TYPE \"long\" :JAVA-NATIVE-TYPE \"int\" :DOCUMENTATION \"Bit vector used to implement BOOLEAN slots.\" :INITIAL-VALUE NULL-INTEGER)");
    defineClassFromStringifiedSource("TICKTOCK", "(DEFCLASS TICKTOCK () :DOCUMENTATION \"A data type that is used to hold information for computing\ntiming of code.  It is intentionally opaque to the user.\nIt should only be used as an argument to the TICKTOCK-DIFFERENCE\nfunction.  Values are obtained with the GET-TICKTOCK function.\" :CPP-NATIVE-TYPE \"clock_t\" :CL-NATIVE-TYPE \"FIXNUM\" :JAVA-NATIVE-TYPE \"long\")");
    defineClassFromStringifiedSource("NATIVE-OBJECT-POINTER", "(DEFCLASS NATIVE-OBJECT-POINTER (SECOND-CLASS-OBJECT) :DOCUMENTATION \"A pointer type that can point at an arbitrary native\nnon-literal object.  Usable to store native objects that fall outside the\nSTELLA OBJECT hierarchy (e.g., native arrays) without having to use their\nexact type.\" :CL-NATIVE-TYPE \"T\" :CPP-NATIVE-TYPE \"void*\" :JAVA-NATIVE-TYPE \"Object\")");
    defineStellaTypeFromStringifiedSource("(DEFTYPE PYTHON-OBJECT-POINTER LONG-INTEGER-WRAPPER)");
    defineClassFromStringifiedSource("PROCESS-LOCK-OBJECT", "(DEFCLASS PROCESS-LOCK-OBJECT () :DOCUMENTATION \"A process lock object for synchronizing in a multi-threaded environment.\nFully supported in Java; supported in some Common Lisp systems; not supported\nin C++.\" :CL-NATIVE-TYPE \"T\" :CPP-NATIVE-TYPE \"void*\" :JAVA-NATIVE-TYPE \"Object\")");
    { Class* clasS = defineClassFromStringifiedSource("SYSTEM-DEFINITION", "(DEFCLASS SYSTEM-DEFINITION (STANDARD-OBJECT DYNAMIC-SLOTS-MIXIN) :DOCUMENTATION \"The System-Definition class is used to define systems of files\nthat constitute STELLA applications.\" :SLOTS ((NAME :TYPE STRING) (DEFINITION-FILE :TYPE FILE-NAME) (DIRECTORY :TYPE FILE-NAME) (FILES :TYPE (CONS OF STRING-WRAPPER)) (LISP-ONLY-FILES :TYPE (CONS OF STRING-WRAPPER)) (CPP-ONLY-FILES :TYPE (CONS OF STRING-WRAPPER)) (JAVA-ONLY-FILES :TYPE (CONS OF STRING-WRAPPER)) (DATA-FILES :TYPE (CONS OF STRING-WRAPPER)) (PREPROCESSED-FILES :TYPE (CONS OF STRING-WRAPPER)) (REQUIRED-SYSTEMS :TYPE (CONS OF STRING-WRAPPER)) (LOADED? :TYPE BOOLEAN) (UP-TO-DATE? :TYPE BOOLEAN) (CARDINAL-MODULE :TYPE STRING) (SOURCE-ROOT-DIRECTORY :TYPE FILE-NAME) (NATIVE-ROOT-DIRECTORY :TYPE FILE-NAME) (BINARY-ROOT-DIRECTORY :TYPE FILE-NAME) (BANNER :TYPE STRING) (COPYRIGHT-HEADER :RENAMES BANNER) (PRODUCTION-SETTINGS :TYPE (CONS OF INTEGER-WRAPPER)) (DEVELOPMENT-SETTINGS :TYPE (CONS OF INTEGER-WRAPPER)) (FINALIZATION-FUNCTION :TYPE SYMBOL)) :PRINT-FO" "RM (PRINT-NATIVE-STREAM STREAM \"|SYSTEM|\" (NAME SELF)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newSystemDefinition));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessSystemDefinitionSlotValue));
    }
    defineClassFromStringifiedSource("ARGUMENT-LIST", "(DEFCLASS ARGUMENT-LIST () :PARAMETERS ((ANY-VALUE :TYPE UNKNOWN)) :PUBLIC-METHODS ((LENGTH ((SELF ARGUMENT-LIST)) :TYPE INTEGER :NATIVE? TRUE)) :METHODS ((ALLOCATE-ITERATOR ((SELF ARGUMENT-LIST)) :TYPE (ARGUMENT-LIST-ITERATOR OF (LIKE (ANY-VALUE SELF))) :NATIVE? TRUE)) :CL-NATIVE-TYPE \"CONS\" :CPP-NATIVE-TYPE \"void\" :JAVA-NATIVE-TYPE \"void\")");
    defineClassFromStringifiedSource("ARGUMENT-LIST-ITERATOR", "(DEFCLASS ARGUMENT-LIST-ITERATOR (ABSTRACT-ITERATOR) :PUBLIC-SLOTS ((VALUE :READER ARGUMENT)) :METHODS ((ARGUMENT ((SELF ARGUMENT-LIST-ITERATOR)) :TYPE (LIKE (ANY-VALUE SELF)) :NATIVE? TRUE) (NEXT? ((SELF ARGUMENT-LIST-ITERATOR)) :TYPE BOOLEAN :NATIVE? TRUE)) :CL-NATIVE-TYPE \"CONS\" :CPP-NATIVE-TYPE \"va_list\" :JAVA-NATIVE-TYPE \"void\")");
    defineClassFromStringifiedSource("NATIVE-STREAM", "(DEFCLASS NATIVE-STREAM () :ABSTRACT? TRUE :CPP-NATIVE-TYPE \"std::ios*\" :JAVA-NATIVE-TYPE \"Object\" :CL-NATIVE-TYPE \"STREAM\")");
    defineClassFromStringifiedSource("NATIVE-OUTPUT-STREAM", "(DEFCLASS NATIVE-OUTPUT-STREAM (NATIVE-STREAM) :ABSTRACT? TRUE :CPP-NATIVE-TYPE \"std::ostream*\" :JAVA-NATIVE-TYPE \"edu.isi.stella.javalib.NativeOutputStream\" :CL-NATIVE-TYPE \"STREAM\")");
    defineClassFromStringifiedSource("NATIVE-INPUT-STREAM", "(DEFCLASS NATIVE-INPUT-STREAM (NATIVE-STREAM) :ABSTRACT? TRUE :CPP-NATIVE-TYPE \"std::istream*\" :JAVA-NATIVE-TYPE \"edu.isi.stella.javalib.NativeInputStream\" :CL-NATIVE-TYPE \"STREAM\")");
    defineClassFromStringifiedSource("NATIVE-CHARSET-ENCODING", "(DEFCLASS NATIVE-CHARSET-ENCODING () :DOCUMENTATION \"Specifies a native character set encoding for proper byte-to-char translation\nfor implementations where we need that.  See also STELLA-CHARSET in streams.ste.\" :CPP-NATIVE-TYPE \"void*\" :JAVA-NATIVE-TYPE \"java.nio.charset.Charset\" :CL-NATIVE-TYPE \"T\")");
    { Class* clasS = defineClassFromStringifiedSource("STREAM", "(DEFCLASS STREAM (STANDARD-OBJECT) :ABSTRACT? TRUE :PUBLIC-SLOTS ((STATE :TYPE KEYWORD)))");

      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessStreamSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("OUTPUT-STREAM", "(DEFCLASS OUTPUT-STREAM (STREAM) :PUBLIC-SLOTS ((NATIVE-STREAM :TYPE NATIVE-OUTPUT-STREAM :PUBLIC? TRUE) (NATIVE-OUTPUT-STREAM :RENAMES NATIVE-STREAM)) :TERMINATOR TERMINATE-OUTPUT-STREAM?)");

      clasS->classConstructorCode = ((cpp_function_code)(&newOutputStream));
    }
    { Class* clasS = defineClassFromStringifiedSource("INPUT-STREAM", "(DEFCLASS INPUT-STREAM (STREAM) :PUBLIC-SLOTS ((NATIVE-STREAM :TYPE NATIVE-INPUT-STREAM :PUBLIC? TRUE) (NATIVE-INPUT-STREAM :RENAMES NATIVE-STREAM) (ECHO-STREAM :TYPE OUTPUT-STREAM) (TOKENIZER-STATE :TYPE TOKENIZER-STREAM-STATE) (BUFFERING-SCHEME :TYPE KEYWORD :INITIALLY :LINE :DOCUMENTATION \"One of :CHARACTER, :LINE or :BLOCK indicating what kind of\ninput buffer we are reading from.  This determines what read function to use\nfor tokenization.\")) :TERMINATOR TERMINATE-INPUT-STREAM?)");

      clasS->classConstructorCode = ((cpp_function_code)(&newInputStream));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessInputStreamSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("OUTPUT-FILE-STREAM", "(DEFCLASS OUTPUT-FILE-STREAM (OUTPUT-STREAM) :SYNONYMS (FILE-OUTPUT-STREAM) :PUBLIC-SLOTS ((FILENAME :TYPE STRING :REQUIRED? TRUE :PUBLIC? TRUE) (IF-EXISTS-ACTION :TYPE KEYWORD :INITIALLY :SUPERSEDE :PUBLIC? TRUE) (IF-NOT-EXISTS-ACTION :TYPE KEYWORD :INITIALLY :CREATE :PUBLIC? TRUE)) :INITIALIZER INITIALIZE-FILE-OUTPUT-STREAM :TERMINATOR TERMINATE-FILE-OUTPUT-STREAM? :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"|FOS|'\" (FILENAME SELF) \"'\"))");

      clasS->classConstructorCode = ((cpp_function_code)(&newOutputFileStream));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessOutputFileStreamSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("INPUT-FILE-STREAM", "(DEFCLASS INPUT-FILE-STREAM (INPUT-STREAM) :SYNONYMS (FILE-INPUT-STREAM) :PUBLIC-SLOTS ((FILENAME :TYPE STRING :REQUIRED? TRUE :PUBLIC? TRUE) (IF-NOT-EXISTS-ACTION :TYPE KEYWORD :INITIALLY :ERROR :PUBLIC? TRUE) (BUFFERING-SCHEME :INITIALLY :BLOCK)) :INITIALIZER INITIALIZE-FILE-INPUT-STREAM :TERMINATOR TERMINATE-FILE-INPUT-STREAM? :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"|FIS|'\" (FILENAME SELF) \"'\"))");

      clasS->classConstructorCode = ((cpp_function_code)(&newInputFileStream));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessInputFileStreamSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("OUTPUT-STRING-STREAM", "(DEFCLASS OUTPUT-STRING-STREAM (OUTPUT-STREAM) :SYNONYMS (STRING-OUTPUT-STREAM) :PUBLIC-SLOTS ((THE-STRING :TYPE STRING :PUBLIC? TRUE :READER THE-STRING-READER)) :TERMINATOR TERMINATE-STRING-OUTPUT-STREAM? :INITIALIZER INITIALIZE-STRING-OUTPUT-STREAM)");

      clasS->classConstructorCode = ((cpp_function_code)(&newOutputStringStream));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessOutputStringStreamSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("INPUT-STRING-STREAM", "(DEFCLASS INPUT-STRING-STREAM (INPUT-STREAM) :SYNONYMS (STRING-INPUT-STREAM) :PUBLIC-SLOTS ((THE-STRING :TYPE STRING :REQUIRED? TRUE :PUBLIC? TRUE) (BUFFERING-SCHEME :INITIALLY :BLOCK)) :TERMINATOR TERMINATE-STRING-INPUT-STREAM? :INITIALIZER INITIALIZE-STRING-INPUT-STREAM)");

      clasS->classConstructorCode = ((cpp_function_code)(&newInputStringStream));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessInputStringStreamSlotValue));
    }
  }
}

void helpStartupHierarchy11() {
  {
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_OBJECT, SYM_HIERARCHY_STELLA_PRIMARY_TYPE, wrapMethodCode(((cpp_method_code)(&Object::primaryType))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_OBJECT, SYM_HIERARCHY_STELLA_HOME_MODULE, wrapMethodCode(((cpp_method_code)(&Object::homeModule))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_OBJECT, SYM_HIERARCHY_STELLA_DELETEDp, wrapMethodCode(((cpp_method_code)(&Object::deletedP))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_OBJECT, SYM_HIERARCHY_STELLA_INCREMENT_REFERENCE_COUNT, wrapMethodCode(((cpp_method_code)(&Object::incrementReferenceCount))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_OBJECT, SYM_HIERARCHY_STELLA_DECREMENT_REFERENCE_COUNT, wrapMethodCode(((cpp_method_code)(&Object::decrementReferenceCount))), NULL);
    defineMethodObject("(DEFMETHOD (TRANSIENT? BOOLEAN) ((SELF TRANSIENT-MIXIN)) :AUXILIARY? TRUE (RETURN *HARDWIRED-TRANSIENT?-ON-TRANSIENT-MIXIN*))", NULL, NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_REFERENCE_COUNT_OBJECT, SYM_HIERARCHY_STELLA_INCREMENT_REFERENCE_COUNT, wrapMethodCode(((cpp_method_code)(&ReferenceCountObject::incrementReferenceCount))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_REFERENCE_COUNT_OBJECT, SYM_HIERARCHY_STELLA_DECREMENT_REFERENCE_COUNT, wrapMethodCode(((cpp_method_code)(&ReferenceCountObject::decrementReferenceCount))), NULL);
    defineMethodObject("(DEFMETHOD (BAD? BOOLEAN-WRAPPER) ((SELF DYNAMIC-SLOTS-MIXIN)) :AUXILIARY? TRUE (LET ((ANSWER (SLOT-VALUE SELF BAD?))) (IF (NULL? ANSWER) (RETURN FALSE) (RETURN ANSWER))))", NULL, NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_ABSTRACT_ITERATOR, SYM_HIERARCHY_STELLA_NEXTp, wrapMethodCode(((cpp_method_code)(&AbstractIterator::nextP))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_TYPES_TO_CLASSES_ITERATOR, SYM_HIERARCHY_STELLA_NEXTp, wrapMethodCode(((cpp_method_code)(&TypesToClassesIterator::nextP))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_DICTIONARY_ITERATOR, SYM_HIERARCHY_STELLA_VALUE_SETTER, wrapMethodCode(((cpp_method_code)(&DictionaryIterator::valueSetter))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_DICTIONARY_ITERATOR, SYM_HIERARCHY_STELLA_KEY_SETTER, wrapMethodCode(((cpp_method_code)(&DictionaryIterator::keySetter))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_ABSTRACT_COLLECTION, SYM_HIERARCHY_STELLA_ALLOCATE_ITERATOR, wrapMethodCode(((cpp_method_code)(&AbstractCollection::allocateIterator))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_ABSTRACT_COLLECTION, SYM_HIERARCHY_STELLA_LENGTH, wrapMethodCode(((cpp_method_code)(&AbstractCollection::length))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_COLLECTION, SYM_HIERARCHY_STELLA_ALLOCATE_ITERATOR, wrapMethodCode(((cpp_method_code)(&Collection::allocateIterator))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_COLLECTION, SYM_HIERARCHY_STELLA_LENGTH, wrapMethodCode(((cpp_method_code)(&Collection::length))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_COLLECTION, SYM_HIERARCHY_STELLA_INSERT, wrapMethodCode(((cpp_method_code)(&Collection::insert))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_COLLECTION, SYM_HIERARCHY_STELLA_REMOVE, wrapMethodCode(((cpp_method_code)(&Collection::remove))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_SEQUENCE, SYM_HIERARCHY_STELLA_ALLOCATE_ITERATOR, wrapMethodCode(((cpp_method_code)(&Sequence::allocateIterator))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_SEQUENCE, SYM_HIERARCHY_STELLA_LENGTH, wrapMethodCode(((cpp_method_code)(&Sequence::length))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_ABSTRACT_DICTIONARY, SYM_HIERARCHY_STELLA_ALLOCATE_ITERATOR, wrapMethodCode(((cpp_method_code)(&AbstractDictionary::allocateIterator))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_DICTIONARY, SYM_HIERARCHY_STELLA_ALLOCATE_ITERATOR, wrapMethodCode(((cpp_method_code)(&Dictionary::allocateIterator))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_DICTIONARY, SYM_HIERARCHY_STELLA_LOOKUP, wrapMethodCode(((cpp_method_code)(&Dictionary::lookup))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_DICTIONARY, SYM_HIERARCHY_STELLA_INSERT_AT, wrapMethodCode(((cpp_method_code)(&Dictionary::insertAt))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_RELATION, SYM_HIERARCHY_STELLA_NAME, wrapMethodCode(((cpp_method_code)(&Relation::name))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_RELATION, SYM_HIERARCHY_STELLA_HOME_MODULE, wrapMethodCode(((cpp_method_code)(&Relation::homeModule))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_RELATION, SYM_HIERARCHY_STELLA_ARITY, wrapMethodCode(((cpp_method_code)(&Relation::arity))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_RELATION, SYM_HIERARCHY_STELLA_PUBLICp, wrapMethodCode(((cpp_method_code)(&Relation::publicP))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_RELATION, SYM_HIERARCHY_STELLA_DIRECT_SUPERS, wrapMethodCode(((cpp_method_code)(&Relation::directSupers))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_RELATION, SYM_HIERARCHY_STELLA_ALL_SUPERS, wrapMethodCode(((cpp_method_code)(&Relation::allSupers))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_RELATION, SYM_HIERARCHY_STELLA_SLOTS, wrapMethodCode(((cpp_method_code)(&Relation::slots))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_NAME, wrapMethodCode(((cpp_method_code)(&Class::name))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_HOME_MODULE, wrapMethodCode(((cpp_method_code)(&Class::homeModule))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_ARITY, wrapMethodCode(((cpp_method_code)(&Class::arity))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_PUBLICp, wrapMethodCode(((cpp_method_code)(&Class::publicP))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_ACTIVEp, wrapMethodCode(((cpp_method_code)(&Class::activeP))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_CREATOR, wrapMethodCode(((cpp_method_code)(&Class::creator))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_INITIALIZER, wrapMethodCode(((cpp_method_code)(&Class::initializer))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_TERMINATOR, wrapMethodCode(((cpp_method_code)(&Class::terminator))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_DESTRUCTOR, wrapMethodCode(((cpp_method_code)(&Class::destructor))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_REQUIRED_SLOTS, wrapMethodCode(((cpp_method_code)(&Class::requiredSlots))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_PARAMETERS, wrapMethodCode(((cpp_method_code)(&Class::parameters))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_INITIAL_VALUE, wrapMethodCode(((cpp_method_code)(&Class::initialValue))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_EXTENSION, wrapMethodCode(((cpp_method_code)(&Class::extension))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_CL_NATIVE_TYPE, wrapMethodCode(((cpp_method_code)(&Class::clNativeType))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_CPP_NATIVE_TYPE, wrapMethodCode(((cpp_method_code)(&Class::cppNativeType))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_IDL_NATIVE_TYPE, wrapMethodCode(((cpp_method_code)(&Class::idlNativeType))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_CLASS, SYM_HIERARCHY_STELLA_JAVA_NATIVE_TYPE, wrapMethodCode(((cpp_method_code)(&Class::javaNativeType))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_POLYMORPHIC_RELATION, SYM_HIERARCHY_STELLA_OWNER, wrapMethodCode(((cpp_method_code)(&PolymorphicRelation::owner))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_POLYMORPHIC_RELATION, SYM_HIERARCHY_STELLA_RENAMES, wrapMethodCode(((cpp_method_code)(&PolymorphicRelation::renames))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_POLYMORPHIC_RELATION, SYM_HIERARCHY_STELLA_ACTIVEp, wrapMethodCode(((cpp_method_code)(&PolymorphicRelation::activeP))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_SLOT, SYM_HIERARCHY_STELLA_NAME, wrapMethodCode(((cpp_method_code)(&Slot::name))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_SLOT, SYM_HIERARCHY_STELLA_TYPE, wrapMethodCode(((cpp_method_code)(&Slot::type))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_SLOT, SYM_HIERARCHY_STELLA_TYPE_SPECIFIER, wrapMethodCode(((cpp_method_code)(&Slot::typeSpecifier))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_SLOT, SYM_HIERARCHY_STELLA_OWNER, wrapMethodCode(((cpp_method_code)(&Slot::owner))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_SLOT, SYM_HIERARCHY_STELLA_HOME_MODULE, wrapMethodCode(((cpp_method_code)(&Slot::homeModule))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_SLOT, SYM_HIERARCHY_STELLA_RENAMES, wrapMethodCode(((cpp_method_code)(&Slot::renames))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_SLOT, SYM_HIERARCHY_STELLA_COLLECTION_VALUEDp, wrapMethodCode(((cpp_method_code)(&Slot::collectionValuedP))), NULL);
    defineInlineMethodCode(SGT_HIERARCHY_STELLA_SLOT, SYM_HIERARCHY_STELLA_CLOSURE_ASSUMPTION, wrapMethodCode(((cpp_method_code)(&Slot::closureAssumption))), NULL);
  }
}

void startupHierarchy() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupHierarchy1();
      helpStartupHierarchy2();
      helpStartupHierarchy3();
      helpStartupHierarchy4();
      helpStartupHierarchy5();
      helpStartupHierarchy6();
      helpStartupHierarchy7();
      SYM_HIERARCHY_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(4)) {
      oHARDWIRED_TRANSIENTp_ON_TRANSIENT_MIXINo = false;
      oHARDWIRED_CLASS_ARITY_ON_CLASSo = NULL_INTEGER;
    }
    if (currentStartupTimePhaseP(5)) {
      helpStartupHierarchy8();
      helpStartupHierarchy9();
      helpStartupHierarchy10();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupHierarchy11();
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_STORAGE_SLOT, SYM_HIERARCHY_STELLA_ALLOCATION, wrapMethodCode(((cpp_method_code)(&StorageSlot::allocation))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_STORAGE_SLOT, SYM_HIERARCHY_STELLA_DEFAULT_FORM, wrapMethodCode(((cpp_method_code)(&StorageSlot::defaultForm))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_STORAGE_SLOT, SYM_HIERARCHY_STELLA_REQUIREDp, wrapMethodCode(((cpp_method_code)(&StorageSlot::requiredP))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_STORAGE_SLOT, SYM_HIERARCHY_STELLA_COMPONENTp, wrapMethodCode(((cpp_method_code)(&StorageSlot::componentP))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_STORAGE_SLOT, SYM_HIERARCHY_STELLA_READER, wrapMethodCode(((cpp_method_code)(&StorageSlot::reader))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_STORAGE_SLOT, SYM_HIERARCHY_STELLA_WRITER, wrapMethodCode(((cpp_method_code)(&StorageSlot::writer))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_METHOD_SLOT, SYM_HIERARCHY_STELLA_SETTERp, wrapMethodCode(((cpp_method_code)(&MethodSlot::setterP))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_GLOBAL_VARIABLE, SYM_HIERARCHY_STELLA_NAME, wrapMethodCode(((cpp_method_code)(&GlobalVariable::name))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_GLOBAL_VARIABLE, SYM_HIERARCHY_STELLA_TYPE, wrapMethodCode(((cpp_method_code)(&GlobalVariable::type))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_GLOBAL_VARIABLE, SYM_HIERARCHY_STELLA_HOME_MODULE, wrapMethodCode(((cpp_method_code)(&GlobalVariable::homeModule))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_CONTEXT, SYM_HIERARCHY_STELLA_CONTEXT_NAME, wrapMethodCode(((cpp_method_code)(&Context::contextName))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_CONTEXT, SYM_HIERARCHY_STELLA_HOME_MODULE, wrapMethodCode(((cpp_method_code)(&Context::homeModule))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_MODULE, SYM_HIERARCHY_STELLA_NAME, wrapMethodCode(((cpp_method_code)(&Module::name))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_MODULE, SYM_HIERARCHY_STELLA_PARENT_MODULE, wrapMethodCode(((cpp_method_code)(&Module::parentModule))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_MODULE, SYM_HIERARCHY_STELLA_LISP_PACKAGE, wrapMethodCode(((cpp_method_code)(&Module::lispPackage))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_MODULE, SYM_HIERARCHY_STELLA_CPP_PACKAGE, wrapMethodCode(((cpp_method_code)(&Module::cppPackage))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_QUANTITY, SYM_HIERARCHY_STELLA_COERCE_TO, wrapMethodCode(((cpp_method_code)(&Quantity::coerceTo))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_QUANTITY, SYM_HIERARCHY_STELLA_LESSp, wrapMethodCode(((cpp_method_code)(&Quantity::lessP))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_QUANTITY, SYM_HIERARCHY_STELLA_LESS_EQUALp, wrapMethodCode(((cpp_method_code)(&Quantity::lessEqualP))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_QUANTITY, SYM_HIERARCHY_STELLA_GREATER_EQUALp, wrapMethodCode(((cpp_method_code)(&Quantity::greaterEqualP))), NULL);
      defineInlineMethodCode(SGT_HIERARCHY_STELLA_QUANTITY, SYM_HIERARCHY_STELLA_GREATERp, wrapMethodCode(((cpp_method_code)(&Quantity::greaterP))), NULL);
      defineFunctionObject("STARTUP-HIERARCHY", "(DEFUN STARTUP-HIERARCHY () :PUBLIC? TRUE)", ((cpp_function_code)(&startupHierarchy)), NULL);
      { MethodSlot* function = lookupFunction(SYM_HIERARCHY_STELLA_STARTUP_HIERARCHY);

        setDynamicSlotValue(function->dynamicSlots, SYM_HIERARCHY_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupHierarchy"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
    }
  }
}

Surrogate* SGT_HIERARCHY_STELLA_OBJECT = NULL;

Symbol* SYM_HIERARCHY_STELLA_PRIMARY_TYPE = NULL;

Symbol* SYM_HIERARCHY_STELLA_HOME_MODULE = NULL;

Symbol* SYM_HIERARCHY_STELLA_DELETEDp = NULL;

Symbol* SYM_HIERARCHY_STELLA_INCREMENT_REFERENCE_COUNT = NULL;

Symbol* SYM_HIERARCHY_STELLA_DECREMENT_REFERENCE_COUNT = NULL;

Symbol* SYM_HIERARCHY_STELLA_TYPE_SPEC = NULL;

boolean oHARDWIRED_TRANSIENTp_ON_TRANSIENT_MIXINo = false;

Surrogate* SGT_HIERARCHY_STELLA_REFERENCE_COUNT_OBJECT = NULL;

Symbol* SYM_HIERARCHY_STELLA_REFERENCE_COUNT = NULL;

Symbol* SYM_HIERARCHY_STELLA_BADp = NULL;

Symbol* SYM_HIERARCHY_STELLA_DELETED_OBJECTp = NULL;

Surrogate* SGT_HIERARCHY_STELLA_ABSTRACT_ITERATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_NEXTp = NULL;

Symbol* SYM_HIERARCHY_STELLA_FIRST_ITERATIONp = NULL;

Symbol* SYM_HIERARCHY_STELLA_VALUE = NULL;

Symbol* SYM_HIERARCHY_STELLA_OBJECT_ITERATOR = NULL;

Surrogate* SGT_HIERARCHY_STELLA_CONS_ITERATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_CONS_ITERATOR_CURSOR = NULL;

Surrogate* SGT_HIERARCHY_STELLA_LIST_ITERATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_LIST_ITERATOR_CURSOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_LIST_ITERATOR_COLLECTION = NULL;

Surrogate* SGT_HIERARCHY_STELLA_DESTRUCTIVE_LIST_ITERATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_THE_CONS_LIST = NULL;

Surrogate* SGT_HIERARCHY_STELLA_ALL_PURPOSE_ITERATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_KEY = NULL;

Symbol* SYM_HIERARCHY_STELLA_ITERATOR_NEXT_CODE = NULL;

Symbol* SYM_HIERARCHY_STELLA_ITERATOR_FILTER_CODE = NULL;

Symbol* SYM_HIERARCHY_STELLA_ITERATOR_EMPTY_CODE = NULL;

Symbol* SYM_HIERARCHY_STELLA_ITERATOR_NESTED_ITERATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_ITERATOR_CONS_LIST = NULL;

Symbol* SYM_HIERARCHY_STELLA_ITERATOR_OBJECT = NULL;

Symbol* SYM_HIERARCHY_STELLA_ITERATOR_SECOND_OBJECT = NULL;

Symbol* SYM_HIERARCHY_STELLA_ITERATOR_INTEGER = NULL;

Symbol* SYM_HIERARCHY_STELLA_ITERATOR_SECOND_INTEGER = NULL;

Surrogate* SGT_HIERARCHY_STELLA_TYPES_TO_CLASSES_ITERATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_ITERATOR_CURSOR = NULL;

Surrogate* SGT_HIERARCHY_STELLA_DICTIONARY_ITERATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_VALUE_SETTER = NULL;

Symbol* SYM_HIERARCHY_STELLA_KEY_SETTER = NULL;

Symbol* SYM_HIERARCHY_STELLA_OBJECT_DICTIONARY_ITERATOR = NULL;

Surrogate* SGT_HIERARCHY_STELLA_PROPERTY_LIST_ITERATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_PLIST_ITERATOR_CURSOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_PLIST_ITERATOR_COLLECTION = NULL;

Surrogate* SGT_HIERARCHY_STELLA_KV_LIST_ITERATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_THE_KV_LIST = NULL;

Symbol* SYM_HIERARCHY_STELLA_KV_LIST_ITERATOR_CURSOR = NULL;

Surrogate* SGT_HIERARCHY_STELLA_INTEGER_INTERVAL_ITERATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_INTERVAL_CURSOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_LOWER_BOUND = NULL;

Symbol* SYM_HIERARCHY_STELLA_UPPER_BOUND = NULL;

Surrogate* SGT_HIERARCHY_STELLA_REVERSE_INTEGER_INTERVAL_ITERATOR = NULL;

Surrogate* SGT_HIERARCHY_STELLA_STRING_ITERATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_THE_STRING = NULL;

Symbol* SYM_HIERARCHY_STELLA_CURSOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_END = NULL;

Surrogate* SGT_HIERARCHY_STELLA_ABSTRACT_COLLECTION = NULL;

Symbol* SYM_HIERARCHY_STELLA_ALLOCATE_ITERATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_LENGTH = NULL;

Surrogate* SGT_HIERARCHY_STELLA_COLLECTION = NULL;

Symbol* SYM_HIERARCHY_STELLA_INSERT = NULL;

Symbol* SYM_HIERARCHY_STELLA_REMOVE = NULL;

Symbol* SYM_HIERARCHY_STELLA_OBJECT_COLLECTION = NULL;

Surrogate* SGT_HIERARCHY_STELLA_SEQUENCE = NULL;

Symbol* SYM_HIERARCHY_STELLA_OBJECT_SEQUENCE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_LIST = NULL;

Surrogate* SGT_HIERARCHY_STELLA_SET = NULL;

Surrogate* SGT_HIERARCHY_STELLA_CLASS_EXTENSION = NULL;

Surrogate* SGT_HIERARCHY_STELLA_CONS = NULL;

Symbol* SYM_HIERARCHY_STELLA_REST = NULL;

Surrogate* SGT_HIERARCHY_STELLA_ABSTRACT_DICTIONARY = NULL;

Surrogate* SGT_HIERARCHY_STELLA_DICTIONARY = NULL;

Symbol* SYM_HIERARCHY_STELLA_LOOKUP = NULL;

Symbol* SYM_HIERARCHY_STELLA_INSERT_AT = NULL;

Symbol* SYM_HIERARCHY_STELLA_OBJECT_TO_OBJECT_DICTIONARY = NULL;

Surrogate* SGT_HIERARCHY_STELLA_PROPERTY_LIST = NULL;

Symbol* SYM_HIERARCHY_STELLA_THE_PLIST = NULL;

Surrogate* SGT_HIERARCHY_STELLA_KV_CONS = NULL;

Surrogate* SGT_HIERARCHY_STELLA_KEY_VALUE_LIST = NULL;

Surrogate* SGT_HIERARCHY_STELLA_RECYCLE_LIST = NULL;

Symbol* SYM_HIERARCHY_STELLA_RECYCLE_LIST_OF = NULL;

Symbol* SYM_HIERARCHY_STELLA_RECYCLED_ITEMS = NULL;

Symbol* SYM_HIERARCHY_STELLA_LIST_OF_RECYCLED_ITEMS = NULL;

Symbol* SYM_HIERARCHY_STELLA_ALL_ITEMS = NULL;

Symbol* SYM_HIERARCHY_STELLA_UNUSED_ITEMS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CURRENT_LENGTH = NULL;

Symbol* SYM_HIERARCHY_STELLA_ITEM_SIZE = NULL;

Symbol* SYM_HIERARCHY_STELLA_THE_STELLA_HASH_TABLE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_HASH_TABLE = NULL;

Symbol* SYM_HIERARCHY_STELLA_OBJECT_TO_OBJECT_HASH_TABLE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_INTEGER_HASH_TABLE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_FLOAT_HASH_TABLE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_STRING_HASH_TABLE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_STRING_TO_INTEGER_HASH_TABLE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_VECTOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_ARRAY_SIZE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_EXTENSIBLE_VECTOR = NULL;

Surrogate* SGT_HIERARCHY_STELLA_EXTENSIBLE_SYMBOL_ARRAY = NULL;

Symbol* SYM_HIERARCHY_STELLA_TOP_SYMBOL_OFFSET = NULL;

Symbol* SYM_HIERARCHY_STELLA_POTENTIAL_FREE_SYMBOL_OFFSET = NULL;

Surrogate* SGT_HIERARCHY_STELLA_VECTOR_SEQUENCE = NULL;

Symbol* SYM_HIERARCHY_STELLA_SEQUENCE_LENGTH = NULL;

Surrogate* SGT_HIERARCHY_STELLA_CUSTOM_VECTOR_SEQUENCE = NULL;

Symbol* SYM_HIERARCHY_STELLA_RESIZE_FACTOR = NULL;

Surrogate* SGT_HIERARCHY_STELLA_BOOLEAN_VECTOR = NULL;

Surrogate* SGT_HIERARCHY_STELLA_INTEGER_VECTOR = NULL;

Surrogate* SGT_HIERARCHY_STELLA_ACTIVE_LIST = NULL;

Surrogate* SGT_HIERARCHY_STELLA_ACTIVE_SET = NULL;

Surrogate* SGT_HIERARCHY_STELLA_DEMON = NULL;

Symbol* SYM_HIERARCHY_STELLA_DEMON_NAME = NULL;

Symbol* SYM_HIERARCHY_STELLA_DEMON_ACTION = NULL;

Symbol* SYM_HIERARCHY_STELLA_DEMON_CLASS_REFS = NULL;

Symbol* SYM_HIERARCHY_STELLA_DEMON_SLOT_REFS = NULL;

Symbol* SYM_HIERARCHY_STELLA_DEMON_CODE = NULL;

Symbol* SYM_HIERARCHY_STELLA_DEMON_METHOD = NULL;

Symbol* SYM_HIERARCHY_STELLA_DEMON_DOCUMENTATION = NULL;

Symbol* SYM_HIERARCHY_STELLA_DEMON_GUARDp = NULL;

Symbol* SYM_HIERARCHY_STELLA_DEMON_ALLp = NULL;

Symbol* SYM_HIERARCHY_STELLA_DEMON_INHERITp = NULL;

Surrogate* SGT_HIERARCHY_STELLA_KEYWORD_KEY_VALUE_LIST = NULL;

Symbol* SYM_HIERARCHY_STELLA_SYMBOL_NAME = NULL;

Symbol* SYM_HIERARCHY_STELLA_SYMBOL_ID = NULL;

Surrogate* SGT_HIERARCHY_STELLA_SYMBOL = NULL;

Symbol* SYM_HIERARCHY_STELLA_SYMBOL_SLOT_OFFSET = NULL;

Symbol* SYM_HIERARCHY_STELLA_SYMBOL_VALUE_AND_PLIST = NULL;

Surrogate* SGT_HIERARCHY_STELLA_SURROGATE = NULL;

Symbol* SYM_HIERARCHY_STELLA_SURROGATE_VALUE = NULL;

Symbol* SYM_HIERARCHY_STELLA_TYPE_CLASS = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOTREF_SLOT = NULL;

Symbol* SYM_HIERARCHY_STELLA_TYPE = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOTREF = NULL;

Surrogate* SGT_HIERARCHY_STELLA_KEYWORD = NULL;

Surrogate* SGT_HIERARCHY_STELLA_TRANSIENT_SYMBOL = NULL;

Symbol* SYM_HIERARCHY_STELLA_PROJECTS_ONTO = NULL;

Symbol* SYM_HIERARCHY_STELLA_PROJECTED_FROM = NULL;

Surrogate* SGT_HIERARCHY_STELLA_RELATION = NULL;

Symbol* SYM_HIERARCHY_STELLA_NAME = NULL;

Symbol* SYM_HIERARCHY_STELLA_ARITY = NULL;

Symbol* SYM_HIERARCHY_STELLA_PUBLICp = NULL;

Symbol* SYM_HIERARCHY_STELLA_DIRECT_SUPERS = NULL;

Symbol* SYM_HIERARCHY_STELLA_ALL_SUPERS = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOTS = NULL;

Symbol* SYM_HIERARCHY_STELLA_PROPERTIES = NULL;

Symbol* SYM_HIERARCHY_STELLA_ABSTRACTp = NULL;

Surrogate* SGT_HIERARCHY_STELLA_CLASS = NULL;

Symbol* SYM_HIERARCHY_STELLA_STORED_ACTIVEp = NULL;

Surrogate* SGT_HIERARCHY_STELLA_ACTIVE_OBJECT = NULL;

Symbol* SYM_HIERARCHY_STELLA_ACTIVEp = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_CREATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_CREATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_INITIALIZER = NULL;

Symbol* SYM_HIERARCHY_STELLA_INITIALIZER = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_TERMINATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_TERMINATOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_DESTRUCTOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_DESTRUCTOR = NULL;

Symbol* SYM_HIERARCHY_STELLA_REQUIRED_SLOTS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_PARAMETERS = NULL;

Symbol* SYM_HIERARCHY_STELLA_PARAMETERS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_INITIAL_VALUE = NULL;

Symbol* SYM_HIERARCHY_STELLA_INITIAL_VALUE = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_EXTENSION = NULL;

Symbol* SYM_HIERARCHY_STELLA_EXTENSION = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_CL_NATIVE_TYPE = NULL;

Symbol* SYM_HIERARCHY_STELLA_CL_NATIVE_TYPE = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_CPP_NATIVE_TYPE = NULL;

Symbol* SYM_HIERARCHY_STELLA_CPP_NATIVE_TYPE = NULL;

Symbol* SYM_HIERARCHY_STELLA_IDL_NATIVE_TYPE = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_JAVA_NATIVE_TYPE = NULL;

Symbol* SYM_HIERARCHY_STELLA_JAVA_NATIVE_TYPE = NULL;

int oHARDWIRED_CLASS_ARITY_ON_CLASSo = NULL_INTEGER;

Symbol* SYM_HIERARCHY_STELLA_CLASS_CL_STRUCT_SLOTS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_RECYCLE_METHOD = NULL;

Keyword* KWD_HIERARCHY_NONE = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_REQUIRED_SLOT_NAMES = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_CONSTRUCTOR_DEMONS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_DESTRUCTOR_DEMONS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_KEY = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_SYNONYMS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CL_STRUCTp = NULL;

Symbol* SYM_HIERARCHY_STELLA_MIXINp = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_TYPE = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_ARITY = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_DIRECT_SUPERS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_DIRECT_SUBS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_ALL_SUPER_CLASSES = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_ALL_SLOTS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_LOCAL_SLOTS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_SLOT_AND_METHOD_CACHE = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_MIXINp = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_COLLECTIONp = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_CL_STRUCTp = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_PUBLICp = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_FINALIZEDp = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_SLOTS_FINALIZEDp = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_STRINGIFIED_SOURCE = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_CONSTRUCTOR_CODE = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_SLOT_ACCESSOR_CODE = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_MARKEDp = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_TAXONOMY_NODE = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_DOCUMENTATION = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLASS_PRINT_FORM = NULL;

Symbol* SYM_HIERARCHY_STELLA_DOCUMENTATION = NULL;

Symbol* SYM_HIERARCHY_STELLA_PRINT_FORM = NULL;

Surrogate* SGT_HIERARCHY_STELLA_POLYMORPHIC_RELATION = NULL;

Symbol* SYM_HIERARCHY_STELLA_OWNER = NULL;

Symbol* SYM_HIERARCHY_STELLA_RENAMES = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_DIRECT_EQUIVALENT = NULL;

Surrogate* SGT_HIERARCHY_STELLA_SLOT = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_TYPE_SPECIFIER = NULL;

Symbol* SYM_HIERARCHY_STELLA_TYPE_SPECIFIER = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_HOME_MODULE = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_RENAMES = NULL;

Symbol* SYM_HIERARCHY_STELLA_COLLECTION_VALUEDp = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_CLOSURE_ASSUMPTION = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLOSURE_ASSUMPTION = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_DIRECT_SUPERS = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_DIRECT_SUBS = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_NAME = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_OWNER = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_BASE_TYPE = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_SLOTREF = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_PUBLICp = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_RENAMEDp = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_EXTERNALp = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_MARKEDp = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_DOCUMENTATION = NULL;

Surrogate* SGT_HIERARCHY_STELLA_STORAGE_SLOT = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_ALLOCATION = NULL;

Keyword* KWD_HIERARCHY_INSTANCE = NULL;

Symbol* SYM_HIERARCHY_STELLA_ALLOCATION = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_DEFAULT_EXPRESSION = NULL;

Symbol* SYM_HIERARCHY_STELLA_DEFAULT_FORM = NULL;

Symbol* SYM_HIERARCHY_STELLA_REQUIREDp = NULL;

Symbol* SYM_HIERARCHY_STELLA_COMPONENTp = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_READER = NULL;

Symbol* SYM_HIERARCHY_STELLA_READER = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_WRITER = NULL;

Symbol* SYM_HIERARCHY_STELLA_WRITER = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_GUARD_DEMONS = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_DEMONS = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_REQUIREDp = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_COMPONENTp = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_READ_ONLYp = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_HARDWIREDp = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_CONTEXT_SENSITIVEp = NULL;

Surrogate* SGT_HIERARCHY_STELLA_METHOD_SLOT = NULL;

Symbol* SYM_HIERARCHY_STELLA_SETTERp = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_PARAMETER_DIRECTIONS = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_INLINED_FUNCTIONS = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_EVALUATE_ARGUMENTSp = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_SETTERp = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_PARAMETER_NAMES = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_PARAMETER_TYPE_SPECIFIERS = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_RETURN_TYPE_SPECIFIERS = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_STRINGIFIED_SOURCE = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_CODE = NULL;

Symbol* SYM_HIERARCHY_STELLA_FUNCTION_CODE = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_FUNCTIONp = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_DOCUMENTATION = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_AUXILIARYp = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_STORAGE_SLOT = NULL;

Symbol* SYM_HIERARCHY_STELLA_SLOT_AUXILIARYp = NULL;

Symbol* SYM_HIERARCHY_STELLA_STORAGE_SLOT = NULL;

Symbol* SYM_HIERARCHY_STELLA_FUNCTION = NULL;

Surrogate* SGT_HIERARCHY_STELLA_PARAMETRIC_TYPE_SPECIFIER = NULL;

Symbol* SYM_HIERARCHY_STELLA_SPECIFIER_BASE_TYPE = NULL;

Symbol* SYM_HIERARCHY_STELLA_SPECIFIER_PARAMETER_TYPES = NULL;

Symbol* SYM_HIERARCHY_STELLA_SPECIFIER_DIMENSIONS = NULL;

Surrogate* SGT_HIERARCHY_STELLA_ANCHORED_TYPE_SPECIFIER = NULL;

Symbol* SYM_HIERARCHY_STELLA_SPECIFIER_PARAMETER_NAME = NULL;

Surrogate* SGT_HIERARCHY_STELLA_TABLE = NULL;

Symbol* SYM_HIERARCHY_STELLA_TUPLE_DOMAINS = NULL;

Surrogate* SGT_HIERARCHY_STELLA_GLOBAL_VARIABLE = NULL;

Symbol* SYM_HIERARCHY_STELLA_VARIABLE_HOME_MODULE = NULL;

Symbol* SYM_HIERARCHY_STELLA_VARIABLE_NAME = NULL;

Symbol* SYM_HIERARCHY_STELLA_VARIABLE_TYPE = NULL;

Symbol* SYM_HIERARCHY_STELLA_VARIABLE_SPECIALp = NULL;

Symbol* SYM_HIERARCHY_STELLA_VARIABLE_CONSTANTp = NULL;

Symbol* SYM_HIERARCHY_STELLA_VARIABLE_PUBLICp = NULL;

Symbol* SYM_HIERARCHY_STELLA_VARIABLE_AUXILIARYp = NULL;

Symbol* SYM_HIERARCHY_STELLA_VARIABLE_DOCUMENTATION = NULL;

Symbol* SYM_HIERARCHY_STELLA_VARIABLE_STRINGIFIED_SOURCE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_QUOTED_EXPRESSION = NULL;

Symbol* SYM_HIERARCHY_STELLA_QUOTATION_TABLE_OFFSET = NULL;

Symbol* SYM_HIERARCHY_STELLA_SURROGATE_VALUE_INVERSE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_MODULE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_WORLD = NULL;

Symbol* SYM_HIERARCHY_STELLA_WORLD_NAME = NULL;

Surrogate* SGT_HIERARCHY_STELLA_CONTEXT = NULL;

Symbol* SYM_HIERARCHY_STELLA_CONTEXT_NAME = NULL;

Symbol* SYM_HIERARCHY_STELLA_CHILD_CONTEXTS = NULL;

Symbol* SYM_HIERARCHY_STELLA_BASE_MODULE = NULL;

Symbol* SYM_HIERARCHY_STELLA_ALL_SUPER_CONTEXTS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CONTEXT_NUMBER = NULL;

Symbol* SYM_HIERARCHY_STELLA_PARENT_MODULE = NULL;

Symbol* SYM_HIERARCHY_STELLA_MODULE_LISP_PACKAGE = NULL;

Symbol* SYM_HIERARCHY_STELLA_LISP_PACKAGE = NULL;

Symbol* SYM_HIERARCHY_STELLA_MODULE_CPP_PACKAGE = NULL;

Symbol* SYM_HIERARCHY_STELLA_CPP_PACKAGE = NULL;

Symbol* SYM_HIERARCHY_STELLA_SHADOWED_SURROGATES = NULL;

Symbol* SYM_HIERARCHY_STELLA_JAVA_PACKAGE = NULL;

Symbol* SYM_HIERARCHY_STELLA_CLEARABLEp = NULL;

Symbol* SYM_HIERARCHY_STELLA_PROTECT_SURROGATESp = NULL;

Symbol* SYM_HIERARCHY_STELLA_PARENT_MODULES = NULL;

Symbol* SYM_HIERARCHY_STELLA_NICKNAMES = NULL;

Symbol* SYM_HIERARCHY_STELLA_USES = NULL;

Symbol* SYM_HIERARCHY_STELLA_USED_BY = NULL;

Symbol* SYM_HIERARCHY_STELLA_REQUIRES = NULL;

Symbol* SYM_HIERARCHY_STELLA_CASE_SENSITIVEp = NULL;

Symbol* SYM_HIERARCHY_STELLA_MODULE_FULL_NAME = NULL;

Symbol* SYM_HIERARCHY_STELLA_MODULE_NAME = NULL;

Symbol* SYM_HIERARCHY_STELLA_MODULE_STRINGIFIED_SOURCE = NULL;

Symbol* SYM_HIERARCHY_STELLA_STRINGIFIED_OPTIONS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CARDINAL_MODULE = NULL;

Symbol* SYM_HIERARCHY_STELLA_SYMBOL_OFFSET_TABLE = NULL;

Symbol* SYM_HIERARCHY_STELLA_SURROGATE_OFFSET_TABLE = NULL;

Symbol* SYM_HIERARCHY_STELLA_STRICT_INFERENCE_CACHE = NULL;

Symbol* SYM_HIERARCHY_STELLA_DEFAULT_INFERENCE_CACHE = NULL;

Symbol* SYM_HIERARCHY_STELLA_PROTOTYPE_INFERENCE_CACHE = NULL;

Symbol* SYM_HIERARCHY_STELLA_PARENT_CONTEXT = NULL;

Surrogate* SGT_HIERARCHY_STELLA_CS_VALUE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_INTERVAL = NULL;

Surrogate* SGT_HIERARCHY_STELLA_TAXONOMY_NODE = NULL;

Symbol* SYM_HIERARCHY_STELLA_NATIVE_OBJECT = NULL;

Symbol* SYM_HIERARCHY_STELLA_LABEL = NULL;

Symbol* SYM_HIERARCHY_STELLA_INTERVALS = NULL;

Symbol* SYM_HIERARCHY_STELLA_INITIAL_INTERVAL = NULL;

Symbol* SYM_HIERARCHY_STELLA_FIRST_INTERVAL_LOWER_BOUND = NULL;

Symbol* SYM_HIERARCHY_STELLA_FIRST_INTERVAL_UPPER_BOUND = NULL;

Symbol* SYM_HIERARCHY_STELLA_PARENTS = NULL;

Symbol* SYM_HIERARCHY_STELLA_CHILDREN = NULL;

Symbol* SYM_HIERARCHY_STELLA_TOTAL_ANCESTORS = NULL;

Symbol* SYM_HIERARCHY_STELLA_TREE_CHILDREN = NULL;

Symbol* SYM_HIERARCHY_STELLA_MARKER = NULL;

Surrogate* SGT_HIERARCHY_STELLA_TAXONOMY_GRAPH = NULL;

Symbol* SYM_HIERARCHY_STELLA_RENUMBER_IF_OUT_OF_NUMBERSp = NULL;

Symbol* SYM_HIERARCHY_STELLA_RENUMBER_RATIO = NULL;

Symbol* SYM_HIERARCHY_STELLA_INCREMENTAL_MODEp = NULL;

Symbol* SYM_HIERARCHY_STELLA_LARGEST_POSTORDER_NUMBER = NULL;

Symbol* SYM_HIERARCHY_STELLA_NUMBER_OF_NODES = NULL;

Symbol* SYM_HIERARCHY_STELLA_NUMBER_OF_FOREIGN_INTERVAL_NODES = NULL;

Symbol* SYM_HIERARCHY_STELLA_ROOTS = NULL;

Symbol* SYM_HIERARCHY_STELLA_BROKEN_LINKS = NULL;

Symbol* SYM_HIERARCHY_STELLA_ADDED_LINKS = NULL;

Symbol* SYM_HIERARCHY_STELLA_REMOVED_LINKS = NULL;

Surrogate* SGT_HIERARCHY_STELLA_QUANTITY = NULL;

Symbol* SYM_HIERARCHY_STELLA_COERCE_TO = NULL;

Symbol* SYM_HIERARCHY_STELLA_LESSp = NULL;

Symbol* SYM_HIERARCHY_STELLA_LESS_EQUALp = NULL;

Symbol* SYM_HIERARCHY_STELLA_GREATER_EQUALp = NULL;

Symbol* SYM_HIERARCHY_STELLA_GREATERp = NULL;

Symbol* SYM_HIERARCHY_STELLA_FILE_NAME = NULL;

Surrogate* SGT_HIERARCHY_STELLA_INTEGER_WRAPPER = NULL;

Symbol* SYM_HIERARCHY_STELLA_WRAPPER_VALUE = NULL;

Symbol* SYM_HIERARCHY_STELLA_NULL_INTEGER = NULL;

Surrogate* SGT_HIERARCHY_STELLA_LONG_INTEGER_WRAPPER = NULL;

Symbol* SYM_HIERARCHY_STELLA_NULL_LONG_INTEGER = NULL;

Surrogate* SGT_HIERARCHY_STELLA_FLOAT_WRAPPER = NULL;

Symbol* SYM_HIERARCHY_STELLA_NULL_FLOAT = NULL;

Surrogate* SGT_HIERARCHY_STELLA_STRING_WRAPPER = NULL;

Symbol* SYM_HIERARCHY_STELLA_NULL_STRING = NULL;

Surrogate* SGT_HIERARCHY_STELLA_MUTABLE_STRING_WRAPPER = NULL;

Symbol* SYM_HIERARCHY_STELLA_NULL_MUTABLE_STRING = NULL;

Surrogate* SGT_HIERARCHY_STELLA_CHARACTER_WRAPPER = NULL;

Symbol* SYM_HIERARCHY_STELLA_NULL_CHARACTER = NULL;

Surrogate* SGT_HIERARCHY_STELLA_BOOLEAN_WRAPPER = NULL;

Symbol* SYM_HIERARCHY_STELLA_TRUE = NULL;

Symbol* SYM_HIERARCHY_STELLA_FALSE = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_CODEp = NULL;

Surrogate* SGT_HIERARCHY_STELLA_FUNCTION_CODE_WRAPPER = NULL;

Surrogate* SGT_HIERARCHY_STELLA_METHOD_CODE_WRAPPER = NULL;

Surrogate* SGT_HIERARCHY_STELLA_VERBATIM_STRING_WRAPPER = NULL;

Surrogate* SGT_HIERARCHY_STELLA_NATIVE_OBJECT_POINTER_WRAPPER = NULL;

Surrogate* SGT_HIERARCHY_STELLA_EXCEPTION_WRAPPER = NULL;

Symbol* SYM_HIERARCHY_STELLA_THREE_VALUED_BOOLEAN = NULL;

Symbol* SYM_HIERARCHY_STELLA_PYTHON_OBJECT_POINTER = NULL;

Surrogate* SGT_HIERARCHY_STELLA_SYSTEM_DEFINITION = NULL;

Symbol* SYM_HIERARCHY_STELLA_DEFINITION_FILE = NULL;

Symbol* SYM_HIERARCHY_STELLA_DIRECTORY = NULL;

Symbol* SYM_HIERARCHY_STELLA_FILES = NULL;

Symbol* SYM_HIERARCHY_STELLA_LISP_ONLY_FILES = NULL;

Symbol* SYM_HIERARCHY_STELLA_CPP_ONLY_FILES = NULL;

Symbol* SYM_HIERARCHY_STELLA_JAVA_ONLY_FILES = NULL;

Symbol* SYM_HIERARCHY_STELLA_DATA_FILES = NULL;

Symbol* SYM_HIERARCHY_STELLA_PREPROCESSED_FILES = NULL;

Symbol* SYM_HIERARCHY_STELLA_REQUIRED_SYSTEMS = NULL;

Symbol* SYM_HIERARCHY_STELLA_LOADEDp = NULL;

Symbol* SYM_HIERARCHY_STELLA_UP_TO_DATEp = NULL;

Symbol* SYM_HIERARCHY_STELLA_SOURCE_ROOT_DIRECTORY = NULL;

Symbol* SYM_HIERARCHY_STELLA_NATIVE_ROOT_DIRECTORY = NULL;

Symbol* SYM_HIERARCHY_STELLA_BINARY_ROOT_DIRECTORY = NULL;

Symbol* SYM_HIERARCHY_STELLA_BANNER = NULL;

Symbol* SYM_HIERARCHY_STELLA_COPYRIGHT_HEADER = NULL;

Symbol* SYM_HIERARCHY_STELLA_PRODUCTION_SETTINGS = NULL;

Symbol* SYM_HIERARCHY_STELLA_DEVELOPMENT_SETTINGS = NULL;

Symbol* SYM_HIERARCHY_STELLA_FINALIZATION_FUNCTION = NULL;

Symbol* SYM_HIERARCHY_STELLA_STATE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_OUTPUT_STREAM = NULL;

Keyword* KWD_HIERARCHY_LINE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_INPUT_STREAM = NULL;

Symbol* SYM_HIERARCHY_STELLA_ECHO_STREAM = NULL;

Symbol* SYM_HIERARCHY_STELLA_TOKENIZER_STATE = NULL;

Symbol* SYM_HIERARCHY_STELLA_BUFFERING_SCHEME = NULL;

Keyword* KWD_HIERARCHY_CREATE = NULL;

Keyword* KWD_HIERARCHY_SUPERSEDE = NULL;

Surrogate* SGT_HIERARCHY_STELLA_OUTPUT_FILE_STREAM = NULL;

Symbol* SYM_HIERARCHY_STELLA_FILENAME = NULL;

Symbol* SYM_HIERARCHY_STELLA_IF_EXISTS_ACTION = NULL;

Symbol* SYM_HIERARCHY_STELLA_IF_NOT_EXISTS_ACTION = NULL;

Symbol* SYM_HIERARCHY_STELLA_FILE_OUTPUT_STREAM = NULL;

Keyword* KWD_HIERARCHY_BLOCK = NULL;

Keyword* KWD_HIERARCHY_ERROR = NULL;

Surrogate* SGT_HIERARCHY_STELLA_INPUT_FILE_STREAM = NULL;

Symbol* SYM_HIERARCHY_STELLA_FILE_INPUT_STREAM = NULL;

Surrogate* SGT_HIERARCHY_STELLA_OUTPUT_STRING_STREAM = NULL;

Symbol* SYM_HIERARCHY_STELLA_STRING_OUTPUT_STREAM = NULL;

Surrogate* SGT_HIERARCHY_STELLA_INPUT_STRING_STREAM = NULL;

Symbol* SYM_HIERARCHY_STELLA_STRING_INPUT_STREAM = NULL;

Symbol* SYM_HIERARCHY_STELLA_STARTUP_HIERARCHY = NULL;

Symbol* SYM_HIERARCHY_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
