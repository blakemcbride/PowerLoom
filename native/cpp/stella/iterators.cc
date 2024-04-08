//  -*- Mode: C++ -*-

// iterators.cc

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

AbstractIterator* AbstractIterator::allocateIterator() {
  // Iterator objects return themselves when asked
  // for an iterator (they occupy the same position as a collection
  // within a 'foreach' statement).
  { AbstractIterator* self = this;

    return (self);
  }
}

int AbstractIterator::length() {
  // Iterate over 'self', and count how many
  // items there are.  Bad idea if 'self' iterates over an infinite
  // collection, since in that case it will run forever.'
  { AbstractIterator* self = this;

    { int count = 0;

      { AbstractIterator* i = self;

        for (; i->nextP(); ) {
          count = count + 1;
        }
      }
      return (count);
    }
  }
}

Object* Iterator::pop() {
  // Return the first item of the sequence represented by 'self',
  // or NULL if it is empty.  Destructively uses up the first iteration element.
  { Iterator* self = this;

    if (self->nextP()) {
      return (self->value);
    }
    else {
      return (NULL);
    }
  }
}

Iterator* Iterator::advance(int n) {
  // Return 'self' after skipping over the first
  // 'n' elements in the (remainder of the) iteration.
  { Iterator* self = this;

    while ((n > 0) &&
        self->nextP()) {
      n = n - 1;
    }
    return (self);
  }
}

boolean Iterator::emptyP() {
  // Return TRUE if the sequence represented by 'self'
  // has no elements.  Side-effect free.
  { Iterator* self = this;

    throw *newStellaException("Missing 'empty?' method");
  }
}

boolean Iterator::memberP(Object* value) {
  // Iterate over values of 'self', returning TRUE
  // if one of them is 'eql' to 'value.
  { Iterator* self = this;

    if ((!((boolean)(value))) ||
        value->standardObjectP()) {
      { Object* m = NULL;
        Iterator* iter000 = self;

        for (; iter000->nextP(); ) {
          m = iter000->value;
          if (m == value) {
            return (true);
          }
        }
      }
    }
    else {
      { Object* m = NULL;
        Iterator* iter001 = self;

        for (; iter001->nextP(); ) {
          m = iter001->value;
          if (eqlP(m, value)) {
            return (true);
          }
        }
      }
    }
    return (false);
  }
}

boolean DestructiveListIterator::nextP() {
  { DestructiveListIterator* self = this;

    { Cons* cursor = self->listIteratorCursor;

      if (cursor == NIL) {
        return (false);
      }
      self->value = cursor->value;
      self->listIteratorCursor = cursor->rest;
      return (true);
    }
  }
}

boolean DestructiveListIterator::emptyP() {
  { DestructiveListIterator* self = this;

    return (self->listIteratorCursor == NIL);
  }
}

boolean terminateDestructiveListIteratorP(DestructiveListIterator* self) {
  self->theConsList = NIL;
  self->listIteratorCursor = NIL;
  return (true);
}

void DestructiveListIterator::insert(Object* value) {
  // Add 'value' to the front of the list 'self'.
  { DestructiveListIterator* self = this;

    self->listIteratorCursor = self->theConsList = cons(value, self->theConsList);
  }
}

Iterator* Cons::allocateDestructiveListIterator() {
  { Cons* self = this;

    { DestructiveListIterator* iterator = newDestructiveListIterator();

      iterator->theConsList = self;
      iterator->listIteratorCursor = self;
      return (iterator);
    }
  }
}

Iterator* List::allocateDestructiveListIterator() {
  { List* self = this;

    { Iterator* iterator = self->theConsList->allocateDestructiveListIterator();

      self->theConsList = NIL;
      self->free();
      return (iterator);
    }
  }
}

boolean AllPurposeIterator::nextP() {
  // Apply the stored 'next?' function to 'self'.
  { AllPurposeIterator* self = this;

    return (((boolean  (*) (AllPurposeIterator*))self->iteratorNextCode)(self));
  }
}

boolean AllPurposeIterator::emptyP() {
  { AllPurposeIterator* self = this;

    if (self->iteratorEmptyCode == NULL) {
      throw *newStellaException("Missing 'empty?' method");
    }
    return (((boolean  (*) ())self->iteratorEmptyCode)());
  }
}

boolean AllPurposeIterator::terminateAllPurposeIteratorP() {
  { AllPurposeIterator* self = this;

    if (((boolean)(self->iteratorNestedIterator))) {
      self->iteratorNestedIterator->free();
    }
    return (true);
  }
}

boolean filteredNestedIteratorNextP(AllPurposeIterator* self) {
  { Iterator* nestediterator = self->iteratorNestedIterator;
    Object* value = NULL;

    while (nestediterator->nextP()) {
      value = nestediterator->value;
      if (((boolean  (*) (Object*, AllPurposeIterator*))self->iteratorFilterCode)(value, self)) {
        self->value = value;
        return (true);
      }
    }
    return (false);
  }
}

boolean iteratorConsListNextP(AllPurposeIterator* self) {
  { Cons* cursor = self->iteratorConsList;

    if (cursor == NIL) {
      return (false);
    }
    self->value = cursor->value;
    self->iteratorConsList = cursor->rest;
    return (true);
  }
}

boolean iteratorConsListEmptyP(AllPurposeIterator* self) {
  return (self->iteratorConsList == NIL);
}

boolean filteredConcatenatedIteratorNextP(AllPurposeIterator* self) {
  { Iterator* nestediterator = self->iteratorNestedIterator;
    cpp_function_code filtercode = self->iteratorFilterCode;
    Object* value = NULL;

    for (;;) {
      while (nestediterator->nextP()) {
        value = nestediterator->value;
        if (((filtercode != NULL) ? ((boolean  (*) (Object*, AllPurposeIterator*))filtercode)(value, self) : true)) {
          self->value = value;
          return (true);
        }
      }
      nestediterator = ((Iterator*)(self->iteratorConsList->value));
      self->iteratorConsList = self->iteratorConsList->rest;
      if (!((boolean)(nestediterator))) {
        break;
      }
      else {
        self->iteratorNestedIterator = nestediterator;
      }
    }
    return (false);
  }
}

AllPurposeIterator* Iterator::concatenate(Iterator* iterator2, int otheriterators, ...) {
  // Return an iterator that first generates all values of
  // `iterator1', then those of `iterator2', and then those of all `otherIterators'.
  // The generated values can be filtered by supplying a filter function to the
  // resulting iterator.
  { Iterator* iterator1 = this;

    { Cons* iteratorlist = cons(iterator2, NIL);

      { va_list iter000;
        int iter000Count = otheriterators;
        Iterator* iterator = NULL;
        Cons* collect000 = NULL;

        va_start(iter000, otheriterators);
                for  (; (iter000Count--) > 0; ) {
          iterator = va_arg(iter000, Iterator*);
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(iterator, NIL);
              if (iteratorlist == NIL) {
                iteratorlist = collect000;
              }
              else {
                addConsToEndOfConsList(iteratorlist, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(iterator, NIL);
              collect000 = collect000->rest;
            }
          }
        }
        va_end(iter000);
      }
      { AllPurposeIterator* self000 = newAllPurposeIterator();

        self000->iteratorNestedIterator = iterator1;
        self000->iteratorConsList = iteratorlist;
        self000->iteratorNextCode = ((cpp_function_code)(&filteredConcatenatedIteratorNextP));
        { AllPurposeIterator* value000 = self000;

          return (value000);
        }
      }
    }
  }
}

void IntegerIntervalIterator::initializeIntegerIntervalIterator() {
  { IntegerIntervalIterator* self = this;

    self->intervalCursor = self->lowerBound;
    self->firstIterationP = true;
  }
}

boolean IntegerIntervalIterator::nextP() {
  { IntegerIntervalIterator* self = this;

    if (self->firstIterationP) {
      self->firstIterationP = false;
    }
    else {
      self->intervalCursor = self->intervalCursor + 1;
    }
    { int upperbound = self->upperBound;

      self->value = self->intervalCursor;
      return ((upperbound == NULL_INTEGER) ||
          (self->intervalCursor <= upperbound));
    }
  }
}

IntegerIntervalIterator* interval(int lowerbound, int upperbound) {
  return (newIntegerIntervalIterator(lowerbound, upperbound));
}

ReverseIntegerIntervalIterator* IntegerIntervalIterator::reverse() {
  { IntegerIntervalIterator* self = this;

    return (reverseInterval(self->lowerBound, self->upperBound));
  }
}

void initializeReverseIntegerIntervalIterator(ReverseIntegerIntervalIterator* self) {
  self->intervalCursor = self->upperBound;
  self->firstIterationP = true;
}

boolean ReverseIntegerIntervalIterator::nextP() {
  { ReverseIntegerIntervalIterator* self = this;

    if (self->firstIterationP) {
      self->firstIterationP = false;
    }
    else {
      self->intervalCursor = self->intervalCursor - 1;
    }
    { int lowerbound = self->lowerBound;

      self->value = self->intervalCursor;
      return ((lowerbound == NULL_INTEGER) ||
          (self->intervalCursor >= lowerbound));
    }
  }
}

ReverseIntegerIntervalIterator* reverseInterval(int lowerbound, int upperbound) {
  // Create a reverse interval object.
  return (newReverseIntegerIntervalIterator(lowerbound, upperbound));
}

StringIterator* stringAllocateIterator(const char* self) {
  { StringIterator* self000 = newStringIterator();

    self000->theString = self;
    { StringIterator* iterator = self000;

      iterator->cursor = 0;
      iterator->end = strlen(self);
      return (iterator);
    }
  }
}

boolean StringIterator::nextP() {
  { StringIterator* self = this;

    { int pos = self->cursor;

      if (pos < self->end) {
        self->value = (self->theString)[pos];
        self->cursor = pos + 1;
        return (true);
      }
      return (false);
    }
  }
}

Iterator* allocateAllMetaObjectsIterator(int arraysize, cpp_function_code nextcode, Module* module, boolean localP) {
  { AllPurposeIterator* iterator = newAllPurposeIterator();
    Cons* moduleslist = NIL;

    iterator->iteratorInteger = 0;
    iterator->iteratorSecondInteger = arraysize;
    if (((boolean)(module))) {
      if (localP) {
        moduleslist = cons(module, moduleslist);
      }
      else {
        { Module* mod = NULL;
          Cons* iter000 = visibleModules(module);
          Cons* collect000 = NULL;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest) {
            mod = ((Module*)(iter000->value));
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(mod, NIL);
                if (moduleslist == NIL) {
                  moduleslist = collect000;
                }
                else {
                  addConsToEndOfConsList(moduleslist, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(mod, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
      }
    }
    iterator->iteratorConsList = moduleslist;
    iterator->iteratorNextCode = nextcode;
    return (iterator);
  }
}

boolean selectedMetaObjectP(AllPurposeIterator* self, Module* objectmodule) {
  { Cons* modules = self->iteratorConsList;

    if (modules == NIL) {
      return (true);
    }
    else {
      if (modules->rest == NIL) {
        if (objectmodule == modules->value) {
          return (true);
        }
        else {
          return (false);
        }
      }
      else {
        return (modules->membP(objectmodule));
      }
    }
  }
}

boolean allSymbolsNextP(AllPurposeIterator* self) {
  { int cursor = self->iteratorInteger;
    Symbol* symbol = NULL;

    while (cursor < self->iteratorSecondInteger) {
      symbol = ((Symbol*)((oSYMBOL_ARRAYo->theArray)[cursor]));
      if (((boolean)(symbol)) &&
          selectedMetaObjectP(self, ((Module*)(symbol->homeContext)))) {
        self->value = symbol;
        self->iteratorInteger = cursor + 1;
        return (true);
      }
      cursor = cursor + 1;
    }
    return (false);
  }
}

Iterator* allSymbols(Module* module, boolean localP) {
  // Iterate over all symbols visible from 'module'.
  // If 'local?', return only symbols interned in 'module'.
  // If 'module' is null, return all symbols interned everywhere.
  return (allocateAllMetaObjectsIterator(oSYMBOL_ARRAYo->topSymbolOffset + 1, ((cpp_function_code)(&allSymbolsNextP)), module, localP));
}

boolean filterPublicSlotP(Slot* self, AllPurposeIterator* iterator) {
  iterator = iterator;
  return (self->slotPublicP);
}

boolean filterPrivateSlotP(Slot* self, AllPurposeIterator* iterator) {
  iterator = iterator;
  return (!self->slotPublicP);
}

boolean filterMethodSlotP(Slot* self, AllPurposeIterator* iterator) {
  iterator = iterator;
  return (methodSlotP(self));
}

boolean filterPublicMethodSlotP(Slot* self, AllPurposeIterator* iterator) {
  iterator = iterator;
  return (self->slotPublicP &&
      methodSlotP(self));
}

boolean filterNonExternalSlotP(Slot* self, AllPurposeIterator* iterator) {
  iterator = iterator;
  return (!self->slotExternalP);
}

boolean filterNonParameterSlotP(Slot* self, AllPurposeIterator* iterator) {
  iterator = iterator;
  return (!((Class*)(self->slotOwner->surrogateValue))->classParameters_reader()->memberP(self->slotName));
}

boolean filterNonAuxiliarySlotP(Slot* self, AllPurposeIterator* iterator) {
  iterator = iterator;
  return (!((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_ITERATORS_STELLA_SLOT_AUXILIARYp, FALSE_WRAPPER)))->wrapperValue);
}

boolean filterSlotP(Slot* self, AllPurposeIterator* iterator) {
  { boolean alwaysP000 = true;

    { FunctionCodeWrapper* filter = NULL;
      Cons* iter000 = ((Cons*)(iterator->iteratorObject));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        filter = ((FunctionCodeWrapper*)(iter000->value));
        if (!((boolean  (*) (Slot*, AllPurposeIterator*))filter->wrapperValue)(self, iterator)) {
          alwaysP000 = false;
          break;
        }
      }
    }
    { boolean value000 = alwaysP000;

      return (value000);
    }
  }
}

boolean allFunctionsNextP(AllPurposeIterator* self) {
  { int cursor = self->iteratorInteger;
    Symbol* symbol = NULL;
    MethodSlot* function = NULL;

    while (cursor < self->iteratorSecondInteger) {
      symbol = ((Symbol*)((oSYMBOL_ARRAYo->theArray)[cursor]));
      if (((boolean)(symbol)) &&
          selectedMetaObjectP(self, lookupFunctionHomeModule(symbol))) {
        function = lookupFunction(symbol);
        if (((boolean)(function)) &&
            ((self->iteratorFilterCode == NULL) ||
             ((boolean  (*) (MethodSlot*, AllPurposeIterator*))self->iteratorFilterCode)(function, self))) {
          self->value = function;
          self->iteratorInteger = cursor + 1;
          return (true);
        }
      }
      cursor = cursor + 1;
    }
    return (false);
  }
}

Iterator* allFunctions(Module* module, boolean localP) {
  // Iterate over all functions visible from 'module'.
  // If 'local?', return only functions bound to symbols interned in 'module'.
  // If 'module' is null, return all functions defined everywhere.
  return (allocateAllMetaObjectsIterator(oSYMBOL_ARRAYo->topSymbolOffset + 1, ((cpp_function_code)(&allFunctionsNextP)), module, localP));
}

Iterator* allPublicFunctions(Module* module, boolean localP) {
  // Iterate over all functions visible from 'module'.
  // If 'local?', return only functions bound to symbols interned in 'module'.
  // If 'module' is null, return all functions defined everywhere.
  { AllPurposeIterator* iterator = ((AllPurposeIterator*)(allFunctions(module, localP)));

    iterator->iteratorFilterCode = ((cpp_function_code)(&filterPublicSlotP));
    return (iterator);
  }
}

boolean allVariablesNextP(AllPurposeIterator* self) {
  { int cursor = self->iteratorInteger;
    Symbol* symbol = NULL;
    GlobalVariable* variable = NULL;

    while (cursor < self->iteratorSecondInteger) {
      symbol = ((Symbol*)((oSYMBOL_ARRAYo->theArray)[cursor]));
      if (((boolean)(symbol)) &&
          selectedMetaObjectP(self, ((Module*)(symbol->homeContext)))) {
        variable = ((GlobalVariable*)(oGLOBAL_VARIABLE_LOOKUP_TABLEo->lookup(symbol)));
        if (((boolean)(variable)) &&
            (selectedMetaObjectP(self, variable->homeModule()) &&
             ((self->iteratorFilterCode == NULL) ||
              ((boolean  (*) (GlobalVariable*, AllPurposeIterator*))self->iteratorFilterCode)(variable, self)))) {
          self->value = variable;
          self->iteratorInteger = cursor + 1;
          return (true);
        }
      }
      cursor = cursor + 1;
    }
    return (false);
  }
}

Iterator* allVariables(Module* module, boolean localP) {
  // Iterate over all variables visible from 'module'.
  // If 'local?', return only variables bound to symbols interned in 'module'.
  // If 'module' is null, return all variables defined everywhere.
  return (allocateAllMetaObjectsIterator(oSYMBOL_ARRAYo->topSymbolOffset + 1, ((cpp_function_code)(&allVariablesNextP)), module, localP));
}

boolean allSurrogatesNextP(AllPurposeIterator* self) {
  { int cursor = self->iteratorInteger;
    Surrogate* surrogate = NULL;

    while (cursor < self->iteratorSecondInteger) {
      surrogate = ((Surrogate*)((oSURROGATE_ARRAYo->theArray)[cursor]));
      if (((boolean)(surrogate)) &&
          selectedMetaObjectP(self, ((Module*)(surrogate->homeContext)))) {
        self->value = surrogate;
        self->iteratorInteger = cursor + 1;
        return (true);
      }
      cursor = cursor + 1;
    }
    return (false);
  }
}

Iterator* allSurrogates(Module* module, boolean localP) {
  // Iterate over all surrogates visible from 'module'.
  // If 'local?', return only surrogates interned in 'module'.
  // If 'module' is null, return all surrogates interned everywhere.
  return (allocateAllMetaObjectsIterator(oSURROGATE_ARRAYo->topSymbolOffset + 1, ((cpp_function_code)(&allSurrogatesNextP)), module, localP));
}

boolean allClassesNextP(AllPurposeIterator* self) {
  { int cursor = self->iteratorInteger;
    Surrogate* surrogate = NULL;
    Object* value = NULL;

    while (cursor < self->iteratorSecondInteger) {
      surrogate = ((Surrogate*)((oSURROGATE_ARRAYo->theArray)[cursor]));
      if (((boolean)(surrogate)) &&
          selectedMetaObjectP(self, ((Module*)(surrogate->homeContext)))) {
        value = surrogate->surrogateValue;
        if (((boolean)(value)) &&
            (stellaClassP(value) &&
             (((Class*)(value))->classType == surrogate))) {
          self->value = value;
          self->iteratorInteger = cursor + 1;
          return (true);
        }
      }
      cursor = cursor + 1;
    }
    return (false);
  }
}

Iterator* allClasses(Module* module, boolean localP) {
  // Iterate over all classes visible from 'module'.
  // If 'local?', return only classes interned in 'module'.
  // If 'module' is null, return all classes interned everywhere.
  return (allocateAllMetaObjectsIterator(oSURROGATE_ARRAYo->topSymbolOffset + 1, ((cpp_function_code)(&allClassesNextP)), module, localP));
}

boolean slotsNextP(AllPurposeIterator* self) {
  { Slot* slot = NULL;

    for (;;) {
      for (;;) {
        { 
          slot = ((Slot*)(self->iteratorConsList->value));
          if (!(((boolean)(slot)))) {
            break;
          }
        }
        self->iteratorConsList = self->iteratorConsList->rest;
        if ((self->iteratorFilterCode == NULL) ||
            ((boolean  (*) (Slot*, AllPurposeIterator*))self->iteratorFilterCode)(slot, self)) {
          self->value = slot;
          return (true);
        }
      }
      if (!self->iteratorNestedIterator->nextP()) {
        return (false);
      }
      self->iteratorConsList = ((Class*)(self->iteratorNestedIterator->value))->classLocalSlots->theConsList;
    }
  }
}

Iterator* allSlots(Module* module, boolean localP) {
  // Iterate over all slots visible from 'module'.
  // If 'local?', return only methods interned in 'module'.
  // If 'module' is null, return all methods interned everywhere.
  { AllPurposeIterator* iterator = newAllPurposeIterator();

    iterator->iteratorNextCode = ((cpp_function_code)(&slotsNextP));
    iterator->iteratorNestedIterator = allClasses(module, localP);
    iterator->iteratorConsList = NIL;
    return (iterator);
  }
}

Iterator* allMethods(Module* module, boolean localP) {
  // Iterate over all methods visible from 'module'.
  // If 'local?', return only methods interned in 'module'.
  // If 'module' is null, return all methods interned everywhere.
  { AllPurposeIterator* iterator = newAllPurposeIterator();

    iterator->iteratorNextCode = ((cpp_function_code)(&slotsNextP));
    iterator->iteratorNestedIterator = allClasses(module, localP);
    iterator->iteratorFilterCode = ((cpp_function_code)(&filterMethodSlotP));
    iterator->iteratorConsList = NIL;
    return (iterator);
  }
}

Iterator* allPublicMethods(Module* module, boolean localP) {
  // Iterate over all public methods visible from 'module'.
  // If 'local?', return only methods interned in 'module'.
  // If 'module' is null, return all methods interned everywhere.
  { AllPurposeIterator* iterator = ((AllPurposeIterator*)(allSlots(module, localP)));

    iterator->iteratorFilterCode = ((cpp_function_code)(&filterPublicMethodSlotP));
    return (iterator);
  }
}

boolean classMethodsNextP(AllPurposeIterator* self) {
  { Slot* slot = NULL;

    for (;;) {
      { 
        slot = ((Slot*)(self->iteratorConsList->value));
        if (!(((boolean)(slot)))) {
          break;
        }
      }
      self->iteratorConsList = self->iteratorConsList->rest;
      if (methodSlotP(slot) &&
          ((self->iteratorFilterCode == NULL) ||
           ((boolean  (*) (Slot*, AllPurposeIterator*))self->iteratorFilterCode)(slot, self))) {
        self->value = slot;
        return (true);
      }
    }
    return (false);
  }
}

Iterator* classMethods(Class* clasS, Cons* filters) {
  { AllPurposeIterator* iterator = newAllPurposeIterator();

    iterator->iteratorNextCode = ((cpp_function_code)(&classMethodsNextP));
    iterator->iteratorConsList = clasS->classLocalSlots->theConsList;
    iterator->iteratorObject = filters;
    iterator->iteratorFilterCode = ((cpp_function_code)(&filterSlotP));
    return (iterator);
  }
}

Iterator* publicClassMethods(Class* clasS) {
  // Iterate over all private methods attached to 'class'.
  return (classMethods(clasS, cons(wrapFunctionCode(((cpp_function_code)(&filterPublicSlotP))), cons(wrapFunctionCode(((cpp_function_code)(&filterNonExternalSlotP))), cons(wrapFunctionCode(((cpp_function_code)(&filterNonAuxiliarySlotP))), NIL)))));
}

Iterator* privateClassMethods(Class* clasS) {
  // Iterate over all private methods attached to 'class'.
  return (classMethods(clasS, cons(wrapFunctionCode(((cpp_function_code)(&filterPrivateSlotP))), cons(wrapFunctionCode(((cpp_function_code)(&filterNonExternalSlotP))), cons(wrapFunctionCode(((cpp_function_code)(&filterNonAuxiliarySlotP))), NIL)))));
}

boolean classStorageSlotsNextP(AllPurposeIterator* self) {
  { Slot* slot = NULL;

    for (;;) {
      { 
        slot = ((Slot*)(self->iteratorConsList->value));
        if (!(((boolean)(slot)))) {
          break;
        }
      }
      self->iteratorConsList = self->iteratorConsList->rest;
      if (storageSlotP(slot) &&
          ((self->iteratorFilterCode == NULL) ||
           ((boolean  (*) (Slot*, AllPurposeIterator*))self->iteratorFilterCode)(slot, self))) {
        self->value = slot;
        return (true);
      }
    }
    return (false);
  }
}

Iterator* classStorageSlots(Class* clasS, Cons* filters) {
  { AllPurposeIterator* iterator = newAllPurposeIterator();

    iterator->iteratorNextCode = ((cpp_function_code)(&classStorageSlotsNextP));
    iterator->iteratorConsList = clasS->classLocalSlots->theConsList;
    iterator->iteratorObject = filters;
    iterator->iteratorFilterCode = ((cpp_function_code)(&filterSlotP));
    return (iterator);
  }
}

boolean classTablesNextP(AllPurposeIterator* self) {
  { Slot* slot = NULL;

    for (;;) {
      { 
        slot = ((Slot*)(self->iteratorConsList->value));
        if (!(((boolean)(slot)))) {
          break;
        }
      }
      self->iteratorConsList = self->iteratorConsList->rest;
      if (isaP(slot, SGT_ITERATORS_STELLA_TABLE) &&
          ((self->iteratorFilterCode == NULL) ||
           ((boolean  (*) (Slot*, AllPurposeIterator*))self->iteratorFilterCode)(slot, self))) {
        self->value = slot;
        return (true);
      }
    }
    return (false);
  }
}

Iterator* classTables(Class* clasS, Cons* filters) {
  { AllPurposeIterator* iterator = newAllPurposeIterator();

    iterator->iteratorNextCode = ((cpp_function_code)(&classTablesNextP));
    iterator->iteratorConsList = clasS->classLocalSlots->theConsList;
    iterator->iteratorObject = filters;
    iterator->iteratorFilterCode = ((cpp_function_code)(&filterSlotP));
    return (iterator);
  }
}

Iterator* publicClassStorageSlots(Class* clasS) {
  // Iterate over all public storage-slots attached to 'class'.
  return (classStorageSlots(clasS, cons(wrapFunctionCode(((cpp_function_code)(&filterPublicSlotP))), cons(wrapFunctionCode(((cpp_function_code)(&filterNonParameterSlotP))), cons(wrapFunctionCode(((cpp_function_code)(&filterNonExternalSlotP))), cons(wrapFunctionCode(((cpp_function_code)(&filterNonAuxiliarySlotP))), NIL))))));
}

Iterator* privateClassStorageSlots(Class* clasS) {
  // Iterate over all private storage-slots attached to 'class'.
  return (classStorageSlots(clasS, cons(wrapFunctionCode(((cpp_function_code)(&filterPrivateSlotP))), cons(wrapFunctionCode(((cpp_function_code)(&filterNonParameterSlotP))), cons(wrapFunctionCode(((cpp_function_code)(&filterNonExternalSlotP))), cons(wrapFunctionCode(((cpp_function_code)(&filterNonAuxiliarySlotP))), NIL))))));
}

CrossProductIterator* newCrossProductIterator() {
  { CrossProductIterator* self = NULL;

    self = new CrossProductIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->cursors = NIL;
    self->domains = NIL;
    return (self);
  }
}

Surrogate* CrossProductIterator::primaryType() {
  { CrossProductIterator* self = this;

    return (SGT_ITERATORS_STELLA_CROSS_PRODUCT_ITERATOR);
  }
}

Object* accessCrossProductIteratorSlotValue(CrossProductIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_ITERATORS_STELLA_DOMAINS) {
    if (setvalueP) {
      self->domains = ((Cons*)(value));
    }
    else {
      value = self->domains;
    }
  }
  else if (slotname == SYM_ITERATORS_STELLA_CURSORS) {
    if (setvalueP) {
      self->cursors = ((Cons*)(value));
    }
    else {
      value = self->cursors;
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

CrossProductIterator* allocateCrossProductIterator(Cons* domains) {
  // Allocate a cross product iterator for a list of `domains'.
  { CrossProductIterator* self000 = newCrossProductIterator();

    self000->domains = domains;
    { CrossProductIterator* iterator = self000;
      Cons* cursors = NIL;
      Cons* values = NIL;

      { Cons* domain = NULL;
        Cons* iter000 = domains;
        int i = NULL_INTEGER;
        int iter001 = 0;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          domain = ((Cons*)(iter000->value));
          i = iter001;
          if ((!((boolean)(domain))) ||
              (domain == NIL)) {
            return (iterator);
          }
          cursors = cons(((i == 0) ? domain : domain->rest), cursors);
          values = cons(domain->value, values);
        }
      }
      iterator->cursors = cursors->reverse();
      iterator->value = values->reverse();
      return (iterator);
    }
  }
}

void CrossProductIterator::reset() {
  // Reset `self' to its initially allocated state.  Note, that
  // this is somewhat expensive, costing almost as much as allocating the iterator.
  { CrossProductIterator* self = this;

    { Cons* domains = self->domains;
      Cons* cursors = NIL;
      Cons* values = NIL;

      { Cons* domain = NULL;
        Cons* iter000 = domains;
        int i = NULL_INTEGER;
        int iter001 = 0;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          domain = ((Cons*)(iter000->value));
          i = iter001;
          if ((!((boolean)(domain))) ||
              (domain == NIL)) {
            return;
          }
          cursors = cons(((i == 0) ? domain : domain->rest), cursors);
          values = cons(domain->value, values);
        }
      }
      self->cursors = cursors->reverse();
      self->value = values->reverse();
    }
  }
}

boolean CrossProductIterator::nextP() {
  { CrossProductIterator* self = this;

    { Cons* domains = self->domains;
      Cons* cursors = self->cursors;
      Cons* cursor = NIL;
      Cons* values = ((Cons*)(self->value));

      if (!((boolean)(values))) {
        return (false);
      }
      while (!(cursors == NIL)) {
        cursor = ((Cons*)(cursors->value));
        if (!(cursor == NIL)) {
          values->firstSetter(cursor->value);
          cursors->firstSetter(cursor->rest);
          return (true);
        }
        else {
          cursor = ((Cons*)(domains->value));
          values->firstSetter(cursor->value);
          cursors->firstSetter(cursor->rest);
        }
        cursors = cursors->rest;
        domains = domains->rest;
        values = values->rest;
      }
      self->value = NULL;
      return (false);
    }
  }
}

void helpStartupIterators1() {
  {
    SYM_ITERATORS_STELLA_SLOT_AUXILIARYp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-AUXILIARY?", NULL, 0)));
    SGT_ITERATORS_STELLA_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("TABLE", NULL, 1)));
    SGT_ITERATORS_STELLA_CROSS_PRODUCT_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("CROSS-PRODUCT-ITERATOR", NULL, 1)));
    SYM_ITERATORS_STELLA_DOMAINS = ((Symbol*)(internRigidSymbolWrtModule("DOMAINS", NULL, 0)));
    SYM_ITERATORS_STELLA_CURSORS = ((Symbol*)(internRigidSymbolWrtModule("CURSORS", NULL, 0)));
    SYM_ITERATORS_STELLA_STARTUP_ITERATORS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-ITERATORS", NULL, 0)));
    SYM_ITERATORS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupIterators2() {
  {
    defineMethodObject("(DEFMETHOD (ALLOCATE-ITERATOR (LIKE SELF)) ((SELF ABSTRACT-ITERATOR)) :DOCUMENTATION \"Iterator objects return themselves when asked\nfor an iterator (they occupy the same position as a collection\nwithin a 'foreach' statement).\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&AbstractIterator::allocateIterator))), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF ABSTRACT-ITERATOR)) :DOCUMENTATION \"Iterate over 'self', and count how many\nitems there are.  Bad idea if 'self' iterates over an infinite\ncollection, since in that case it will run forever.'\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&AbstractIterator::length))), NULL);
    defineMethodObject("(DEFMETHOD (POP (LIKE (ANY-VALUE SELF))) ((SELF ITERATOR)) :PUBLIC? TRUE :DOCUMENTATION \"Return the first item of the sequence represented by 'self',\nor NULL if it is empty.  Destructively uses up the first iteration element.\")", wrapMethodCode(((cpp_method_code)(&Iterator::pop))), NULL);
    defineMethodObject("(DEFMETHOD (ADVANCE (LIKE SELF)) ((SELF ITERATOR) (N INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Return 'self' after skipping over the first\n'n' elements in the (remainder of the) iteration.\")", wrapMethodCode(((cpp_method_code)(&Iterator::advance))), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF ITERATOR)) :PUBLIC? TRUE :DOCUMENTATION \"Return TRUE if the sequence represented by 'self'\nhas no elements.  Side-effect free.\")", wrapMethodCode(((cpp_method_code)(&Iterator::emptyP))), NULL);
    defineMethodObject("(DEFMETHOD (MEMBER? BOOLEAN) ((SELF ITERATOR) (VALUE OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Iterate over values of 'self', returning TRUE\nif one of them is 'eql' to 'value.\")", wrapMethodCode(((cpp_method_code)(&Iterator::memberP))), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF DESTRUCTIVE-LIST-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&DestructiveListIterator::nextP))), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF DESTRUCTIVE-LIST-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&DestructiveListIterator::emptyP))), NULL);
    defineFunctionObject("TERMINATE-DESTRUCTIVE-LIST-ITERATOR?", "(DEFUN (TERMINATE-DESTRUCTIVE-LIST-ITERATOR? BOOLEAN) ((SELF DESTRUCTIVE-LIST-ITERATOR)))", ((cpp_function_code)(&terminateDestructiveListIteratorP)), NULL);
    defineMethodObject("(DEFMETHOD INSERT ((SELF DESTRUCTIVE-LIST-ITERATOR) (VALUE (LIKE (ANY-VALUE SELF)))) :DOCUMENTATION \"Add 'value' to the front of the list 'self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&DestructiveListIterator::insert))), NULL);
    defineMethodObject("(DEFMETHOD (ALLOCATE-DESTRUCTIVE-LIST-ITERATOR (ITERATOR OF (LIKE (ANY-VALUE SELF)))) ((SELF CONS)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Cons::allocateDestructiveListIterator))), NULL);
    defineMethodObject("(DEFMETHOD (ALLOCATE-DESTRUCTIVE-LIST-ITERATOR (ITERATOR OF (LIKE (ANY-VALUE SELF)))) ((SELF LIST)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&List::allocateDestructiveListIterator))), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)) :DOCUMENTATION \"Apply the stored 'next?' function to 'self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&AllPurposeIterator::nextP))), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&AllPurposeIterator::emptyP))), NULL);
    defineMethodObject("(DEFMETHOD (TERMINATE-ALL-PURPOSE-ITERATOR? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&AllPurposeIterator::terminateAllPurposeIteratorP))), NULL);
    defineFunctionObject("FILTERED-NESTED-ITERATOR-NEXT?", "(DEFUN (FILTERED-NESTED-ITERATOR-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filteredNestedIteratorNextP)), NULL);
    defineFunctionObject("ITERATOR-CONS-LIST-NEXT?", "(DEFUN (ITERATOR-CONS-LIST-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&iteratorConsListNextP)), NULL);
    defineFunctionObject("ITERATOR-CONS-LIST-EMPTY?", "(DEFUN (ITERATOR-CONS-LIST-EMPTY? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&iteratorConsListEmptyP)), NULL);
    defineFunctionObject("FILTERED-CONCATENATED-ITERATOR-NEXT?", "(DEFUN (FILTERED-CONCATENATED-ITERATOR-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filteredConcatenatedIteratorNextP)), NULL);
    defineMethodObject("(DEFMETHOD (CONCATENATE ALL-PURPOSE-ITERATOR) ((ITERATOR1 ITERATOR) (ITERATOR2 ITERATOR) |&REST| (OTHERITERATORS ITERATOR)) :DOCUMENTATION \"Return an iterator that first generates all values of\n`iterator1', then those of `iterator2', and then those of all `otherIterators'.\nThe generated values can be filtered by supplying a filter function to the\nresulting iterator.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Iterator::concatenate))), NULL);
    defineMethodObject("(DEFMETHOD INITIALIZE-INTEGER-INTERVAL-ITERATOR ((SELF INTEGER-INTERVAL-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&IntegerIntervalIterator::initializeIntegerIntervalIterator))), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF INTEGER-INTERVAL-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&IntegerIntervalIterator::nextP))), NULL);
    defineFunctionObject("INTERVAL", "(DEFUN (INTERVAL INTEGER-INTERVAL-ITERATOR) ((LOWERBOUND INTEGER) (UPPERBOUND INTEGER)) :PUBLIC? TRUE)", ((cpp_function_code)(&interval)), NULL);
    defineMethodObject("(DEFMETHOD (REVERSE REVERSE-INTEGER-INTERVAL-ITERATOR) ((SELF INTEGER-INTERVAL-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&IntegerIntervalIterator::reverse))), NULL);
    defineFunctionObject("INITIALIZE-REVERSE-INTEGER-INTERVAL-ITERATOR", "(DEFUN INITIALIZE-REVERSE-INTEGER-INTERVAL-ITERATOR ((SELF REVERSE-INTEGER-INTERVAL-ITERATOR)))", ((cpp_function_code)(&initializeReverseIntegerIntervalIterator)), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF REVERSE-INTEGER-INTERVAL-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&ReverseIntegerIntervalIterator::nextP))), NULL);
    defineFunctionObject("REVERSE-INTERVAL", "(DEFUN (REVERSE-INTERVAL REVERSE-INTEGER-INTERVAL-ITERATOR) ((LOWERBOUND INTEGER) (UPPERBOUND INTEGER)) :DOCUMENTATION \"Create a reverse interval object.\")", ((cpp_function_code)(&reverseInterval)), NULL);
    defineMethodObject("(DEFMETHOD (ALLOCATE-ITERATOR STRING-ITERATOR) ((SELF STRING)) :PUBLIC? TRUE)", wrapFunctionCode(((cpp_function_code)(((StringIterator*  (*) (const char*))(&stringAllocateIterator))))), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF STRING-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StringIterator::nextP))), NULL);
    defineFunctionObject("ALLOCATE-ALL-META-OBJECTS-ITERATOR", "(DEFUN (ALLOCATE-ALL-META-OBJECTS-ITERATOR ITERATOR) ((ARRAYSIZE INTEGER) (NEXTCODE FUNCTION-CODE) (MODULE MODULE) (LOCAL? BOOLEAN)) :PUBLIC? TRUE)", ((cpp_function_code)(&allocateAllMetaObjectsIterator)), NULL);
    defineFunctionObject("SELECTED-META-OBJECT?", "(DEFUN (SELECTED-META-OBJECT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR) (OBJECTMODULE MODULE)) :PUBLIC? TRUE)", ((cpp_function_code)(&selectedMetaObjectP)), NULL);
    defineFunctionObject("ALL-SYMBOLS-NEXT?", "(DEFUN (ALL-SYMBOLS-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)) :PUBLIC? TRUE)", ((cpp_function_code)(&allSymbolsNextP)), NULL);
    defineFunctionObject("ALL-SYMBOLS", "(DEFUN (ALL-SYMBOLS (ITERATOR OF SYMBOL)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all symbols visible from 'module'.\nIf 'local?', return only symbols interned in 'module'.\nIf 'module' is null, return all symbols interned everywhere.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allSymbols)), NULL);
    defineFunctionObject("FILTER-PUBLIC-SLOT?", "(DEFUN (FILTER-PUBLIC-SLOT? BOOLEAN) ((SELF SLOT) (ITERATOR ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filterPublicSlotP)), NULL);
    defineFunctionObject("FILTER-PRIVATE-SLOT?", "(DEFUN (FILTER-PRIVATE-SLOT? BOOLEAN) ((SELF SLOT) (ITERATOR ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filterPrivateSlotP)), NULL);
    defineFunctionObject("FILTER-METHOD-SLOT?", "(DEFUN (FILTER-METHOD-SLOT? BOOLEAN) ((SELF SLOT) (ITERATOR ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filterMethodSlotP)), NULL);
    defineFunctionObject("FILTER-PUBLIC-METHOD-SLOT?", "(DEFUN (FILTER-PUBLIC-METHOD-SLOT? BOOLEAN) ((SELF SLOT) (ITERATOR ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filterPublicMethodSlotP)), NULL);
    defineFunctionObject("FILTER-NON-EXTERNAL-SLOT?", "(DEFUN (FILTER-NON-EXTERNAL-SLOT? BOOLEAN) ((SELF SLOT) (ITERATOR ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filterNonExternalSlotP)), NULL);
    defineFunctionObject("FILTER-NON-PARAMETER-SLOT?", "(DEFUN (FILTER-NON-PARAMETER-SLOT? BOOLEAN) ((SELF SLOT) (ITERATOR ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filterNonParameterSlotP)), NULL);
    defineFunctionObject("FILTER-NON-AUXILIARY-SLOT?", "(DEFUN (FILTER-NON-AUXILIARY-SLOT? BOOLEAN) ((SELF SLOT) (ITERATOR ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filterNonAuxiliarySlotP)), NULL);
    defineFunctionObject("FILTER-SLOT?", "(DEFUN (FILTER-SLOT? BOOLEAN) ((SELF SLOT) (ITERATOR ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filterSlotP)), NULL);
    defineFunctionObject("ALL-FUNCTIONS-NEXT?", "(DEFUN (ALL-FUNCTIONS-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&allFunctionsNextP)), NULL);
    defineFunctionObject("ALL-FUNCTIONS", "(DEFUN (ALL-FUNCTIONS (ITERATOR OF FUNCTION)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all functions visible from 'module'.\nIf 'local?', return only functions bound to symbols interned in 'module'.\nIf 'module' is null, return all functions defined everywhere.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allFunctions)), NULL);
    defineFunctionObject("ALL-PUBLIC-FUNCTIONS", "(DEFUN (ALL-PUBLIC-FUNCTIONS (ITERATOR OF FUNCTION)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all functions visible from 'module'.\nIf 'local?', return only functions bound to symbols interned in 'module'.\nIf 'module' is null, return all functions defined everywhere.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allPublicFunctions)), NULL);
    defineFunctionObject("ALL-VARIABLES-NEXT?", "(DEFUN (ALL-VARIABLES-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&allVariablesNextP)), NULL);
    defineFunctionObject("ALL-VARIABLES", "(DEFUN (ALL-VARIABLES (ITERATOR OF GLOBAL-VARIABLE)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all variables visible from 'module'.\nIf 'local?', return only variables bound to symbols interned in 'module'.\nIf 'module' is null, return all variables defined everywhere.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allVariables)), NULL);
    defineFunctionObject("ALL-SURROGATES-NEXT?", "(DEFUN (ALL-SURROGATES-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&allSurrogatesNextP)), NULL);
    defineFunctionObject("ALL-SURROGATES", "(DEFUN (ALL-SURROGATES (ITERATOR OF SURROGATE)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all surrogates visible from 'module'.\nIf 'local?', return only surrogates interned in 'module'.\nIf 'module' is null, return all surrogates interned everywhere.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allSurrogates)), NULL);
    defineFunctionObject("ALL-CLASSES-NEXT?", "(DEFUN (ALL-CLASSES-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&allClassesNextP)), NULL);
    defineFunctionObject("ALL-CLASSES", "(DEFUN (ALL-CLASSES (ITERATOR OF CLASS)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all classes visible from 'module'.\nIf 'local?', return only classes interned in 'module'.\nIf 'module' is null, return all classes interned everywhere.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allClasses)), NULL);
    defineFunctionObject("SLOTS-NEXT?", "(DEFUN (SLOTS-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&slotsNextP)), NULL);
    defineFunctionObject("ALL-SLOTS", "(DEFUN (ALL-SLOTS (ITERATOR OF SLOT)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all slots visible from 'module'.\nIf 'local?', return only methods interned in 'module'.\nIf 'module' is null, return all methods interned everywhere.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allSlots)), NULL);
    defineFunctionObject("ALL-METHODS", "(DEFUN (ALL-METHODS (ITERATOR OF METHOD-SLOT)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all methods visible from 'module'.\nIf 'local?', return only methods interned in 'module'.\nIf 'module' is null, return all methods interned everywhere.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allMethods)), NULL);
    defineFunctionObject("ALL-PUBLIC-METHODS", "(DEFUN (ALL-PUBLIC-METHODS (ITERATOR OF METHOD-SLOT)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all public methods visible from 'module'.\nIf 'local?', return only methods interned in 'module'.\nIf 'module' is null, return all methods interned everywhere.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allPublicMethods)), NULL);
    defineFunctionObject("CLASS-METHODS-NEXT?", "(DEFUN (CLASS-METHODS-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&classMethodsNextP)), NULL);
    defineFunctionObject("CLASS-METHODS", "(DEFUN (CLASS-METHODS (ITERATOR OF METHOD-SLOT)) ((CLASS CLASS) (FILTERS (CONS OF FUNCTION-CODE-WRAPPER))))", ((cpp_function_code)(&classMethods)), NULL);
    defineFunctionObject("PUBLIC-CLASS-METHODS", "(DEFUN (PUBLIC-CLASS-METHODS (ITERATOR OF METHOD-SLOT)) ((CLASS CLASS)) :DOCUMENTATION \"Iterate over all private methods attached to 'class'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&publicClassMethods)), NULL);
    defineFunctionObject("PRIVATE-CLASS-METHODS", "(DEFUN (PRIVATE-CLASS-METHODS (ITERATOR OF METHOD-SLOT)) ((CLASS CLASS)) :DOCUMENTATION \"Iterate over all private methods attached to 'class'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&privateClassMethods)), NULL);
    defineFunctionObject("CLASS-STORAGE-SLOTS-NEXT?", "(DEFUN (CLASS-STORAGE-SLOTS-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&classStorageSlotsNextP)), NULL);
    defineFunctionObject("CLASS-STORAGE-SLOTS", "(DEFUN (CLASS-STORAGE-SLOTS (ITERATOR OF STORAGE-SLOT)) ((CLASS CLASS) (FILTERS (CONS OF FUNCTION-CODE-WRAPPER))))", ((cpp_function_code)(&classStorageSlots)), NULL);
  }
}

void startupIterators() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupIterators1();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("CROSS-PRODUCT-ITERATOR", "(DEFCLASS CROSS-PRODUCT-ITERATOR (ITERATOR) :DOCUMENTATION \"Iterator class that generates the cross product of a list of domains.\nEach value tuple is represented as a CONS.  CAUTION: the value tuple will be modified\ndestructively, hence, it needs to be copied in case it needs to persist beyond a single\niteration.\" :PUBLIC? TRUE :PARAMETERS ((ANY-VALUE :TYPE CONS)) :SLOTS ((DOMAINS :TYPE (CONS OF CONS) :INITIALLY NIL) (CURSORS :TYPE (CONS OF CONS) :INITIALLY NIL)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newCrossProductIterator));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessCrossProductIteratorSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupIterators2();
      defineFunctionObject("CLASS-TABLES-NEXT?", "(DEFUN (CLASS-TABLES-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&classTablesNextP)), NULL);
      defineFunctionObject("CLASS-TABLES", "(DEFUN (CLASS-TABLES (ITERATOR OF TABLE)) ((CLASS CLASS) (FILTERS (CONS OF FUNCTION-CODE-WRAPPER))))", ((cpp_function_code)(&classTables)), NULL);
      defineFunctionObject("PUBLIC-CLASS-STORAGE-SLOTS", "(DEFUN (PUBLIC-CLASS-STORAGE-SLOTS (ITERATOR OF STORAGE-SLOT)) ((CLASS CLASS)) :DOCUMENTATION \"Iterate over all public storage-slots attached to 'class'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&publicClassStorageSlots)), NULL);
      defineFunctionObject("PRIVATE-CLASS-STORAGE-SLOTS", "(DEFUN (PRIVATE-CLASS-STORAGE-SLOTS (ITERATOR OF STORAGE-SLOT)) ((CLASS CLASS)) :DOCUMENTATION \"Iterate over all private storage-slots attached to 'class'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&privateClassStorageSlots)), NULL);
      defineFunctionObject("ALLOCATE-CROSS-PRODUCT-ITERATOR", "(DEFUN (ALLOCATE-CROSS-PRODUCT-ITERATOR CROSS-PRODUCT-ITERATOR) ((DOMAINS (CONS OF CONS))) :DOCUMENTATION \"Allocate a cross product iterator for a list of `domains'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allocateCrossProductIterator)), NULL);
      defineMethodObject("(DEFMETHOD RESET ((SELF CROSS-PRODUCT-ITERATOR)) :DOCUMENTATION \"Reset `self' to its initially allocated state.  Note, that\nthis is somewhat expensive, costing almost as much as allocating the iterator.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&CrossProductIterator::reset))), NULL);
      defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF CROSS-PRODUCT-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&CrossProductIterator::nextP))), NULL);
      defineFunctionObject("STARTUP-ITERATORS", "(DEFUN STARTUP-ITERATORS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupIterators)), NULL);
      { MethodSlot* function = lookupFunction(SYM_ITERATORS_STELLA_STARTUP_ITERATORS);

        setDynamicSlotValue(function->dynamicSlots, SYM_ITERATORS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupIterators"), NULL_STRING_WRAPPER);
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

Symbol* SYM_ITERATORS_STELLA_SLOT_AUXILIARYp = NULL;

Surrogate* SGT_ITERATORS_STELLA_TABLE = NULL;

Surrogate* SGT_ITERATORS_STELLA_CROSS_PRODUCT_ITERATOR = NULL;

Symbol* SYM_ITERATORS_STELLA_DOMAINS = NULL;

Symbol* SYM_ITERATORS_STELLA_CURSORS = NULL;

Symbol* SYM_ITERATORS_STELLA_STARTUP_ITERATORS = NULL;

Symbol* SYM_ITERATORS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
