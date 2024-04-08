//  -*- Mode: C++ -*-

// pli.cc

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

namespace pli {
  using namespace stella;
  using namespace logic;

boolean oPOWERLOOM_INITIALIZEDpo = false;

void initialize() {
  // Initialize the PowerLoom logic system.  This function
  // needs to be called by all applications before using PowerLoom.  If it
  // is called more than once, every call after the first one is a no-op.
  // Should be synchronized on process lock oBOOTSTRAP_LOCKo
  {
    if (!oPOWERLOOM_INITIALIZEDpo) {
      startupLogicSystem();
    }
  }
}

extern "C" void pli_initialize() {
  // C-callable wrapper for `initialize'.
  try {
    initialize();
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

void resetPowerloom() {
  // Reset PowerLoom to its initial state.
  // CAUTION: This will destroy all loaded knowledge bases and might break other
  // loaded STELLA systems if they do reference PowerLoom symbols in their code.
  // Should be synchronized on process lock oPOWERLOOM_LOCKo
  {
    logic::resetPowerloom();
  }
}

extern "C" void pli_resetPowerloom() {
  // C-callable wrapper for `resetPowerloom'.
  try {
    resetPowerloom();
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

void clearCaches() {
  // Clear all query and memoization caches.
  // Should be synchronized on process lock oPOWERLOOM_LOCKo
  {
    logic::clearCaches();
  }
}

extern "C" void pli_clearCaches() {
  // C-callable wrapper for `clearCaches'.
  clearCaches();
}

Environment* newEnvironment() {
  { Environment* self = NULL;

    self = new Environment();
    self->level = NULL;
    return (self);
  }
}

Surrogate* Environment::primaryType() {
  { Environment* self = this;

    return (SGT_PLI_PLI_ENVIRONMENT);
  }
}

Object* accessEnvironmentSlotValue(Environment* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PLI_LOGIC_LEVEL) {
    if (setvalueP) {
      self->level = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->level);
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

void Environment::printObject(std::ostream* stream) {
  { Environment* self = this;

    *(stream) << "|ENV|" << self->level;
  }
}

Environment* ASSERTION_ENV = NULL;

Environment* TAXONOMIC_ENV = NULL;

Environment* INFERENCE_ENV = NULL;

boolean testEnvironmentLevelP(Environment* env, const char* level) {
  // Test if `env' has level set to `level'
  return (((boolean)(env)) &&
      stringEqlP(env->level, level));
}

PlIterator* newPlIterator() {
  { PlIterator* self = NULL;

    self = new PlIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->cursor = NULL;
    return (self);
  }
}

Surrogate* PlIterator::primaryType() {
  { PlIterator* self = this;

    return (SGT_PLI_PLI_PL_ITERATOR);
  }
}

Object* accessPlIteratorSlotValue(PlIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PLI_STELLA_CURSOR) {
    if (setvalueP) {
      self->cursor = ((Cons*)(value));
    }
    else {
      value = self->cursor;
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

boolean PlIterator::nextP() {
  // Advance the PL-Iterator `self' and return `true' if more
  // elements are available, `false' otherwise.
  { PlIterator* self = this;

    { Cons* cursor = self->cursor;

      if (cursor == NIL) {
        self->value = NULL;
        return (false);
      }
      self->value = cursor->value;
      self->cursor = cursor->rest;
      return (true);
    }
  }
}

extern "C" int pli_plIteratorNextP(PlIterator* self) {
  // C-callable wrapper for `PlIterator::nextP'.
  return (self->nextP());
}

Object* plIteratorValue(PlIterator* self) {
  // C-callable iterator `value'-slot accessor.
  return (self->value);
}

extern "C" Object* pli_plIteratorValue(PlIterator* self) {
  // C-callable wrapper for `plIteratorValue'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(plIteratorValue(self)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
}

boolean PlIterator::emptyP() {
  // Return TRUE if the iterator `self' has no more elements.
  { PlIterator* self = this;

    return (self->cursor == NIL);
  }
}

extern "C" int pli_plIteratorEmptyP(PlIterator* self) {
  // C-callable wrapper for `PlIterator::emptyP'.
  return (self->emptyP());
}

boolean plIteratorIsEmpty(PlIterator* self) {
  // Return TRUE if the iterator `self' has no more elements.
  // This is here primarily to support the `is-...' naming convention for tests.
  return (self->cursor == NIL);
}

extern "C" int pli_plIteratorIsEmpty(PlIterator* self) {
  // C-callable wrapper for `plIteratorIsEmpty'.
  return (plIteratorIsEmpty(self));
}

int PlIterator::length() {
  // Number of items remaining in `self'.  Non destructive.
  { PlIterator* self = this;

    return (self->cursor->length());
  }
}

extern "C" int pli_plIteratorLength(PlIterator* self) {
  // C-callable wrapper for `PlIterator::length'.
  return (self->length());
}

// Iterator that generates no values.
PlIterator* EMPTY_PL_ITERATOR = NULL;

PlIterator* consToPlIterator(Cons* self) {
  // Convert a STELLA cons list into an API iterator.
  if (self == NIL) {
    return (EMPTY_PL_ITERATOR);
  }
  else {
    { PlIterator* self000 = newPlIterator();

      self000->cursor = self;
      { PlIterator* value000 = self000;

        return (value000);
      }
    }
  }
}

extern "C" PlIterator* pli_consToPlIterator(Cons* self) {
  // C-callable wrapper for `consToPlIterator'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(consToPlIterator(self)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

PlIterator* listToPlIterator(List* self) {
  // Convert a STELLA list into an API iterator.
  if (self->emptyP()) {
    return (EMPTY_PL_ITERATOR);
  }
  else {
    return (consToPlIterator(self->theConsList));
  }
}

extern "C" PlIterator* pli_listToPlIterator(List* self) {
  // C-callable wrapper for `listToPlIterator'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(listToPlIterator(self)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

PlIterator* iteratorToPlIterator(Iterator* self) {
  // Convert an arbitrary STELLA iterator into an API iterator.
  // This will first exhaust `self' and then create an API iterator that will
  // iterate over the previously generated values.
  return (consToPlIterator(self->consify()));
}

extern "C" PlIterator* pli_iteratorToPlIterator(Iterator* self) {
  // C-callable wrapper for `iteratorToPlIterator'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(iteratorToPlIterator(self)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

List* PlIterator::listify() {
  // Convert `self' into a Stella LIST.
  { PlIterator* self = this;

    { List* self000 = newList();

      { Cons* value001 = NIL;

        { Object* x = NULL;
          PlIterator* iter000 = self;
          Cons* collect000 = NULL;

          for  (; iter000->nextP(); ) {
            x = iter000->value;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(x, NIL);
                if (value001 == NIL) {
                  value001 = collect000;
                }
                else {
                  addConsToEndOfConsList(value001, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(x, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        self000->theConsList = value001;
      }
      { List* value000 = self000;

        return (value000);
      }
    }
  }
}

extern "C" List* pli_plIteratorListify(PlIterator* self) {
  // C-callable wrapper for `PlIterator::listify'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(self->listify()));
    return (((List*)(oC_API_RESULT_BUFFERo)));
  }
}

Cons* PlIterator::consify() {
  // Convert `self' into a Stella CONS.
  { PlIterator* self = this;

    { Cons* value000 = NIL;

      { Object* x = NULL;
        PlIterator* iter000 = self;
        Cons* collect000 = NULL;

        for  (; iter000->nextP(); ) {
          x = iter000->value;
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(x, NIL);
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
              collect000->rest = cons(x, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      { Cons* value001 = value000;

        return (value001);
      }
    }
  }
}

extern "C" Cons* pli_plIteratorConsify(PlIterator* self) {
  // C-callable wrapper for `PlIterator::consify'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(self->consify()));
    return (((Cons*)(oC_API_RESULT_BUFFERo)));
  }
}

Cons* createCons(Object* first, Cons* rest) {
  // Create a STELLA CONS-cell whose value points to `first' and tail points to `rest'.
  // If `rest' is NULL, it will point to the empty list (available as a constructor in C).
  if (!((boolean)(rest))) {
    rest = NIL;
  }
  return (cons(first, rest));
}

extern "C" Cons* pli_createCons(Object* first, Cons* rest) {
  // C-callable wrapper for `createCons'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(createCons(first, rest)));
    return (((Cons*)(oC_API_RESULT_BUFFERo)));
  }
}

Cons* createConsList(int length) {
  // Create a STELLA CONS-list of `length' with elements initialized to NULL (available as a constructor in C).
  { Cons* list = NIL;

    while (length > 0) {
      list = cons(NULL, list);
      length = length - 1;
    }
    return (list);
  }
}

extern "C" Cons* pli_createConsList(int length) {
  // C-callable wrapper for `createConsList'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(createConsList(length)));
    return (((Cons*)(oC_API_RESULT_BUFFERo)));
  }
}

int consLength(Cons* self) {
  // Return the length of the CONS-list `self' (available to support access in C).
  return (self->length());
}

extern "C" int pli_consLength(Cons* self) {
  // C-callable wrapper for `consLength'.
  return (consLength(self));
}

boolean consIsEmpty(Cons* self) {
  // Return TRUE if the CONS-list `self' is empty (available to support access in C).
  return (self == NIL);
}

extern "C" int pli_consIsEmpty(Cons* self) {
  // C-callable wrapper for `consIsEmpty'.
  return (consIsEmpty(self));
}

Object* consFirst(Cons* self) {
  // Access the first element of the CONS-list `self' (available to support access in C).
  return (self->value);
}

extern "C" Object* pli_consFirst(Cons* self) {
  // C-callable wrapper for `consFirst'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(consFirst(self)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
}

Cons* consRest(Cons* self) {
  // Access the rest (tail) of the CONS-list `self' (available to support access in C).
  return (self->rest);
}

extern "C" Cons* pli_consRest(Cons* self) {
  // C-callable wrapper for `consRest'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(consRest(self)));
    return (((Cons*)(oC_API_RESULT_BUFFERo)));
  }
}

Object* consNth(Cons* self, int n) {
  // Access the `n'-th element of the CONS-list `self' (available to support access in C).
  return (self->nth(n));
}

extern "C" Object* pli_consNth(Cons* self, int n) {
  // C-callable wrapper for `consNth'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(consNth(self, n)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
}

Cons* consNthRest(Cons* self, int n) {
  // Access the `n'-th rest (tail) of the CONS-list `self' (available to support access in C).
  return (self->nthRest(n));
}

extern "C" Cons* pli_consNthRest(Cons* self, int n) {
  // C-callable wrapper for `consNthRest'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(consNthRest(self, n)));
    return (((Cons*)(oC_API_RESULT_BUFFERo)));
  }
}

void consSetFirst(Cons* self, Object* value) {
  // Set the first element of the CONS-list `self' to `value' (available to support access in C).
  self->value = value;
}

extern "C" void pli_consSetFirst(Cons* self, Object* value) {
  // C-callable wrapper for `consSetFirst'.
  consSetFirst(self, value);
}

void consSetRest(Cons* self, Cons* rest) {
  // Set the rest (tail) of the CONS-list `self' to `rest' (available to support access in C).
  // If `rest' is NULL, it will point to the empty list.
  if (!((boolean)(rest))) {
    rest = NIL;
  }
  self->rest = rest;
}

extern "C" void pli_consSetRest(Cons* self, Cons* rest) {
  // C-callable wrapper for `consSetRest'.
  consSetRest(self, rest);
}

void consSetNth(Cons* self, int n, Object* value) {
  // Set the `n'-th element of the CONS-list `self' to `value' (available to support access in C).
  // The run-time complexity of this operation is O(n).
  self->nthSetter(value, n);
}

extern "C" void pli_consSetNth(Cons* self, int n, Object* value) {
  // C-callable wrapper for `consSetNth'.
  consSetNth(self, n, value);
}

void consSetNthRest(Cons* self, int n, Cons* rest) {
  // Set the `n'-th rest (tail) of the CONS-list `self' to `rest' (available to support access in C).
  // If `rest' is NULL, it will point to the empty list.  The run-time complexity of this operation is O(n).
  if (!((boolean)(rest))) {
    rest = NIL;
  }
  self->nthRestSetter(rest, n);
}

extern "C" void pli_consSetNthRest(Cons* self, int n, Cons* rest) {
  // C-callable wrapper for `consSetNthRest'.
  consSetNthRest(self, n, rest);
}

Object* listFirst(List* self) {
  // Access the first element of the list `self' (available to support access in C).
  return (self->first());
}

extern "C" Object* pli_listFirst(List* self) {
  // C-callable wrapper for `listFirst'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(listFirst(self)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
}

Cons* listRest(List* self) {
  // Access the rest (tail) of the list `self' (available to support access in C).
  // NOTE: the rest of a STELLA list is a CONS-list not a LIST.
  return (self->rest());
}

extern "C" Cons* pli_listRest(List* self) {
  // C-callable wrapper for `listRest'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(listRest(self)));
    return (((Cons*)(oC_API_RESULT_BUFFERo)));
  }
}

Object* listNth(List* self, int n) {
  // Access the `n'-th element of the list `self' (available to support access in C).
  return (self->nth(n));
}

extern "C" Object* pli_listNth(List* self, int n) {
  // C-callable wrapper for `listNth'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(listNth(self, n)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* createString(const char* content) {
  // Create a PowerLoom copy of the string `content' which uses PowerLoom memory
  // management and garbage collection.  This is primarily necessary in C environments when a string
  // is passed to a PowerLoom PLI function which might then be pointed to by a PowerLoom result
  // object such as a string wrapper.  If such an argument string is later explicitly freed or
  // overwritten, the result object would have a dangling reference or its content destroyed.
  return (stringCopy(content));
}

extern "C" const char* pli_createString(const char* content) {
  // C-callable wrapper for `createString'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(createString(content)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

StringWrapper* createStringWrapper(const char* self) {
  // Create a STELLA string wrapper for `self'.  This automatically copies `self'
  // before the wrapper is allocated to avoid garbage collection issues in case `self' is freed.
  return (wrapString(stringCopy(self)));
}

extern "C" StringWrapper* pli_createStringWrapper(const char* self) {
  // C-callable wrapper for `createStringWrapper'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(createStringWrapper(self)));
    return (((StringWrapper*)(oC_API_RESULT_BUFFERo)));
  }
}

StringWrapper* createDirectStringWrapper(const char* self) {
  // Create a STELLA string wrapper for `self'.  This wraps `self' directly
  // and does not allocate a PowerLoom copy first, hence, memory management of `self' needs to
  // be carefully handled by the caller.
  return (wrapString(self));
}

extern "C" StringWrapper* pli_createDirectStringWrapper(const char* self) {
  // C-callable wrapper for `createDirectStringWrapper'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(createDirectStringWrapper(self)));
    return (((StringWrapper*)(oC_API_RESULT_BUFFERo)));
  }
}

IntegerWrapper* createIntegerWrapper(int self) {
  // Create a STELLA integer wrapper for `self'.
  return (wrapInteger(self));
}

extern "C" IntegerWrapper* pli_createIntegerWrapper(int self) {
  // C-callable wrapper for `createIntegerWrapper'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(createIntegerWrapper(self)));
    return (((IntegerWrapper*)(oC_API_RESULT_BUFFERo)));
  }
}

LongIntegerWrapper* createLongIntegerWrapper(long long int self) {
  // Create a STELLA long-integer wrapper for `self'.
  return (wrapLongInteger(self));
}

extern "C" LongIntegerWrapper* pli_createLongIntegerWrapper(long long int self) {
  // C-callable wrapper for `createLongIntegerWrapper'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(createLongIntegerWrapper(self)));
    return (((LongIntegerWrapper*)(oC_API_RESULT_BUFFERo)));
  }
}

FloatWrapper* createFloatWrapper(double self) {
  // Create a STELLA float wrapper for `self'.
  return (wrapFloat(self));
}

extern "C" FloatWrapper* pli_createFloatWrapper(double self) {
  // C-callable wrapper for `createFloatWrapper'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(createFloatWrapper(self)));
    return (((FloatWrapper*)(oC_API_RESULT_BUFFERo)));
  }
}

BooleanWrapper* createBooleanWrapper(boolean self) {
  // Create a STELLA boolean wrapper for `self'.
  return ((self ? TRUE_WRAPPER : FALSE_WRAPPER));
}

extern "C" BooleanWrapper* pli_createBooleanWrapper(int self) {
  // C-callable wrapper for `createBooleanWrapper'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(createBooleanWrapper(self)));
    return (((BooleanWrapper*)(oC_API_RESULT_BUFFERo)));
  }
}

Object* safelyGetObject(const char* name, Module* module, Environment* environment) {
  if (name == NULL) {
    return (NULL);
  }
  { Object* object = getObject(name, module, environment);

    if (!((boolean)(object))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't find an object named " << "`" << name << "'";
        throw *newNoSuchObjectException(stream000->theStringReader());
      }
    }
    else {
      return (object);
    }
  }
}

Object* safelyGetConcept(const char* name, Module* module, Environment* environment) {
  if (name == NULL) {
    return (NULL);
  }
  { LogicObject* object = getConcept(name, module, environment);

    if (!((boolean)(object))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't find a concept named " << "`" << name << "'";
        throw *newNoSuchObjectException(stream000->theStringReader());
      }
    }
    else {
      return (object);
    }
  }
}

Object* safelyGetRelation(const char* name, Module* module, Environment* environment) {
  if (name == NULL) {
    return (NULL);
  }
  { LogicObject* object = getRelation(name, module, environment);

    if (!((boolean)(object))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't find a relation named " << "`" << name << "'";
        throw *newNoSuchObjectException(stream000->theStringReader());
      }
    }
    else {
      return (object);
    }
  }
}

Context* safelyGetModule(const char* name, Environment* environment) {
  environment = environment;
  if ((name == NULL) ||
      stringEqlP(name, "")) {
    return (oMODULEo);
  }
  return (getStellaModule(name, true));
}

Object* safelyGetObjectOrNull(const char* name, Module* module, Environment* environment) {
  if ((!((boolean)(module))) ||
      ((name == NULL) ||
       (stringEqlP(name, "") ||
        stringEqualP(name, "null")))) {
    return (NULL);
  }
  try {
    return (getObject(name, module, environment));
  }
  catch (NoSuchObjectException ) {
    return (NULL);
  }
}

Cons* sequenceToConsList(Object* sequence) {
  { Surrogate* testValue000 = safePrimaryType(sequence);

    if (testValue000 == SGT_PLI_STELLA_CONS) {
      { Object* sequence000 = sequence;
        Cons* sequence = ((Cons*)(sequence000));

        return (sequence);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PLI_STELLA_LIST)) {
      { Object* sequence001 = sequence;
        List* sequence = ((List*)(sequence001));

        return (sequence->theConsList);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PLI_STELLA_VECTOR)) {
      { Object* sequence002 = sequence;
        Vector* sequence = ((Vector*)(sequence002));

        { Cons* result = NIL;

          { int i = NULL_INTEGER;
            int iter000 = 0;
            int upperBound000 = sequence->length();
            Cons* collect000 = NULL;

            for  (; iter000 <= upperBound000; 
                  iter000 = iter000 + 1) {
              i = iter000;
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons((sequence->theArray)[i], NIL);
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
                  collect000->rest = cons((sequence->theArray)[i], NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
          return (result);
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Don't know how to convert object of type " << "`" << sequence->primaryType() << "'" << " into a cons list.";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Cons* explodeStringList(const char* stringlist, Module* module) {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    { Cons* expression = ((Cons*)(readSExpressionFromString(stringlist)));
      Object* term = NULL;
      Cons* result = NIL;

      { Object* ref = NULL;
        Cons* iter000 = expression;
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          ref = iter000->value;
          term = ((ref == SYM_PLI_STELLA_NULL) ? NULL : evaluateTerm(ref));
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(term, NIL);
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
              collect000->rest = cons(term, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      return (result);
    }
  }
}

boolean legalOperatorP(Symbol* operatoR) {
  return (oKIF_SENTENCE_OPERATORSo->memberP(operatoR) ||
      (oKIF_TERM_OPERATORSo->memberP(operatoR) ||
       getQuotedTree("((<=>> <<=> <<=>> <~> <~>> <<~> <<~>> ABOUT <<= =>> <~ ~> <<~ ~>>) \"/PLI\")", "/PLI")->memberP(operatoR)));
}

Keyword* getKeyword(const char* name) {
  // Returns the Stella KEYWORD `name' if it exists.  Case sensitive.
  return (lookupKeyword(name));
}

extern "C" Keyword* pli_getKeyword(const char* name) {
  // C-callable wrapper for `getKeyword'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getKeyword(name)));
    return (((Keyword*)(oC_API_RESULT_BUFFERo)));
  }
}

Symbol* getSymbol(const char* name, Module* module, Environment* environment) {
  // Returns the Stella SYMBOL `name' visible in `module' if it
  // exists.  `name' is ALWAYS treated literally and case sensitively.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (lookupSymbol(name));
    }
  }
}

extern "C" Symbol* pli_getSymbol(const char* name, Module* module, Environment* environment) {
  // C-callable wrapper for `getSymbol'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getSymbol(name, module, environment)));
    return (((Symbol*)(oC_API_RESULT_BUFFERo)));
  }
}

Symbol* getOperator(const char* name) {
  // Returns the logical operator object (a Stella SYMBOL) for `name'.
  // If no such operator exists then a `no-such-object' exception is thrown.
  if (!(allUpperCaseStringP(name))) {
    name = stringUpcase(name);
  }
  { Symbol* operatoR = lookupSymbolInModule(name, oLOGIC_MODULEo, false);

    if (((boolean)(operatoR)) &&
        legalOperatorP(operatoR)) {
      return (operatoR);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "No operator named " << "`" << name << "'";
        throw *newNoSuchObjectException(stream000->theStringReader());
      }
    }
  }
}

extern "C" Symbol* pli_getOperator(const char* name) {
  // C-callable wrapper for `getOperator'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getOperator(name)));
    return (((Symbol*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Object* getObject(const char* name, Module* module, Environment* environment) {
  // Look for an object named `name' that is local to
  // or visible from the module `module'.  `name' is not taken literally
  // but will be parsed first with the PowerLoom symbol reader and, hence,
  // can contain escape characters, module prefixes, etc.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (getInstance(lookupStellaName(name)));
    }
  }
}

extern "C" Object* pli_getObject(const char* name, Module* module, Environment* environment) {
  // C-callable wrapper for `getObject'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getObject(name, module, environment)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Object* sGetObject(const char* name, const char* moduleName, Environment* environment) {
  // Look for an object named `name' that is local to
  // or visible from the module `module-name'.  A module name of `null' or the
  // empty string refers to the current module.  If no module can be found
  // with the name `module-name', then a STELLA `no-such-context-exception' is thrown.
  // `name' is not taken literally but will be parsed first (see `get-object').
  return (getObject(name, ((Module*)(safelyGetModule(moduleName, environment))), environment));
}

extern "C" Object* pli_sGetObject(const char* name, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetObject'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sGetObject(name, moduleName, environment)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

LogicObject* getConcept(const char* name, Module* module, Environment* environment) {
  // Return a class/concept named `name' that is local to
  // or visible from the module `module'.  `name' is not taken literally but
  // will be parsed first (see `get-object').
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (getClass(lookupStellaName(name)));
    }
  }
}

extern "C" LogicObject* pli_getConcept(const char* name, Module* module, Environment* environment) {
  // C-callable wrapper for `getConcept'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getConcept(name, module, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

LogicObject* sGetConcept(const char* name, const char* moduleName, Environment* environment) {
  // Return a class/concept named `name' that is local to
  // or visible from the module `module-name'.  A module name of `null' or the
  // empty string refers to the current module.  If no module can be found
  // with the name `module-name', then a Stella `no-such-context-exception' is thrown.
  // `name' is not taken literally but will be parsed first (see `get-object').
  return (getConcept(name, ((Module*)(safelyGetModule(moduleName, environment))), environment));
}

extern "C" LogicObject* pli_sGetConcept(const char* name, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetConcept'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sGetConcept(name, moduleName, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

LogicObject* getRelation(const char* name, Module* module, Environment* environment) {
  // Return a concept or relation named `name' that is local to
  // or visible from the module `module'.  `name' is not taken literally but will
  // be parsed first (see `get-object').
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (logic::getRelation(lookupStellaName(name)));
    }
  }
}

extern "C" LogicObject* pli_getRelation(const char* name, Module* module, Environment* environment) {
  // C-callable wrapper for `getRelation'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getRelation(name, module, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

LogicObject* sGetRelation(const char* name, const char* moduleName, Environment* environment) {
  // Return a concept or relation named `name' that is local to
  // or visible from the module `module-name'.  A module name of `null' or the
  // empty string refers to the current module.  If no module can be found
  // with the name `module-name', then a Stella `no-such-context-exception' is thrown.
  // `name' is not taken literally but will be parsed first (see `get-object').
  return (getRelation(name, ((Module*)(safelyGetModule(moduleName, environment))), environment));
}

extern "C" LogicObject* pli_sGetRelation(const char* name, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetRelation'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sGetRelation(name, moduleName, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* getUndefinedRelations(Module* module, Environment* environment) {
  // Return relations that have been referenced but not defined in `module'.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      module = oMODULEo;
      return (consToPlIterator(callListUndefinedRelations(module, false)));
    }
  }
}

extern "C" PlIterator* pli_getUndefinedRelations(Module* module, Environment* environment) {
  // C-callable wrapper for `getUndefinedRelations'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getUndefinedRelations(module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

const char* getNameInModule(Object* obj, Module* module, Environment* environment) {
  // Return the name, qualified as necessary, so that `obj' can be found from
  // `module'.  If there is no name for the object return `null'.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      { Surrogate* testValue000 = safePrimaryType(obj);

        if (subtypeOfP(testValue000, SGT_PLI_LOGIC_SKOLEM)) {
          { Object* obj000 = obj;
            Skolem* obj = ((Skolem*)(obj000));

            return (NULL);
          }
        }
        else if (subtypeOfP(testValue000, SGT_PLI_LOGIC_LOGIC_OBJECT)) {
          { Object* obj001 = obj;
            LogicObject* obj = ((LogicObject*)(obj001));

            return (stringify(objectName(obj)));
          }
        }
        else if (subtypeOfP(testValue000, SGT_PLI_STELLA_GENERALIZED_SYMBOL)) {
          { Object* obj002 = obj;
            GeneralizedSymbol* obj = ((GeneralizedSymbol*)(obj002));

            return (stringify(obj));
          }
        }
        else if (subtypeOfP(testValue000, SGT_PLI_STELLA_MODULE)) {
          { Object* obj003 = obj;
            Module* obj = ((Module*)(obj003));

            return (obj->moduleFullName);
          }
        }
        else if (subtypeOfP(testValue000, SGT_PLI_STELLA_CONTEXT)) {
          { Object* obj004 = obj;
            Context* obj = ((Context*)(obj004));

            return (obj->contextName());
          }
        }
        else if (subtypeOfP(testValue000, SGT_PLI_LOGIC_COMPUTED_PROCEDURE)) {
          { Object* obj005 = obj;
            ComputedProcedure* obj = ((ComputedProcedure*)(obj005));

            return (stringify(obj->surrogateValueInverse));
          }
        }
        else {
          return (NULL);
        }
      }
    }
  }
}

extern "C" const char* pli_getNameInModule(Object* obj, Module* module, Environment* environment) {
  // C-callable wrapper for `getNameInModule'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getNameInModule(obj, module, environment)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* getName(Object* obj) {
  // Return the fully qualified name of `obj', if it has one.  Otherwise return `null'.
  return (getNameInModule(obj, oROOT_MODULEo, NULL));
}

extern "C" const char* pli_getName(Object* obj) {
  // C-callable wrapper for `getName'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getName(obj)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* getShortName(Object* obj) {
  // Return the short name of `obj', if it has one.  Otherwise return `null'.
  { Surrogate* testValue000 = safePrimaryType(obj);

    if (subtypeOfP(testValue000, SGT_PLI_LOGIC_SKOLEM)) {
      { Object* obj000 = obj;
        Skolem* obj = ((Skolem*)(obj000));

        return (NULL);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PLI_LOGIC_LOGIC_OBJECT)) {
      { Object* obj001 = obj;
        LogicObject* obj = ((LogicObject*)(obj001));

        return (objectNameString(obj));
      }
    }
    else if (subtypeOfKeywordP(testValue000)) {
      { Object* obj002 = obj;
        Keyword* obj = ((Keyword*)(obj002));

        return (stringConcatenate(":", obj->symbolName, 0));
      }
    }
    else if (subtypeOfP(testValue000, SGT_PLI_STELLA_GENERALIZED_SYMBOL)) {
      { Object* obj003 = obj;
        GeneralizedSymbol* obj = ((GeneralizedSymbol*)(obj003));

        return (obj->symbolName);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PLI_STELLA_CONTEXT)) {
      { Object* obj004 = obj;
        Context* obj = ((Context*)(obj004));

        return (obj->contextName());
      }
    }
    else if (subtypeOfP(testValue000, SGT_PLI_LOGIC_COMPUTED_PROCEDURE)) {
      { Object* obj005 = obj;
        ComputedProcedure* obj = ((ComputedProcedure*)(obj005));

        return (obj->surrogateValueInverse->symbolName);
      }
    }
    else {
      return (NULL);
    }
  }
}

extern "C" const char* pli_getShortName(Object* obj) {
  // C-callable wrapper for `getShortName'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getShortName(obj)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* getSkolemName(Skolem* skolem) {
  // Return the fully qualified name of `skolem'.  Note that skolems are anonymous objects
  // which cannot be referenced by their name in logic expressions, so this function is only useful in special
  // circumstances such as inside specialist computations, etc.
  return (getNameInModule(skolem->skolemName, oROOT_MODULEo, NULL));
}

extern "C" const char* pli_getSkolemName(Skolem* skolem) {
  // C-callable wrapper for `getSkolemName'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getSkolemName(skolem)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* getSkolemShortName(Skolem* skolem) {
  // Return the unqualified name of `skolem'.  Note that skolems are anonymous objects which
  // cannot be referenced by their name in logic expressions, so this function is only useful in special
  // circumstances such as inside specialist computations, etc.
  return (skolem->skolemName->symbolName);
}

extern "C" const char* pli_getSkolemShortName(Skolem* skolem) {
  // C-callable wrapper for `getSkolemShortName'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getSkolemShortName(skolem)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* getVariableName(PatternVariable* variable) {
  // Return the fully qualified name of `variable'.
  return (getNameInModule(variable->skolemName, oROOT_MODULEo, NULL));
}

extern "C" const char* pli_getVariableName(PatternVariable* variable) {
  // C-callable wrapper for `getVariableName'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getVariableName(variable)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* getVariableShortName(PatternVariable* variable) {
  // Return the unqualified name of `variable'.
  return (variable->skolemName->symbolName);
}

extern "C" const char* pli_getVariableShortName(PatternVariable* variable) {
  // C-callable wrapper for `getVariableShortName'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getVariableShortName(variable)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* objectToString(Object* self) {
  // Return a printed representation of the term `self' as a string.
  if (!((boolean)(self))) {
    return (NULL);
  }
  else {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      { Surrogate* testValue000 = safePrimaryType(self);

        if (subtypeOfStringP(testValue000)) {
          { Object* self000 = self;
            StringWrapper* self = ((StringWrapper*)(self000));

            return (self->wrapperValue);
          }
        }
        else if (subtypeOfP(testValue000, SGT_PLI_LOGIC_SKOLEM)) {
          { Object* self001 = self;
            Skolem* self = ((Skolem*)(self001));

            { Object* value = valueOf(self);

              if (value == self) {
                return (stringify(self));
              }
              else {
                return (objectToString(value));
              }
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_PLI_PLI_PL_ITERATOR)) {
          { Object* self002 = self;
            PlIterator* self = ((PlIterator*)(self002));

            return (stringify(self->consify()));
          }
        }
        else {
          return (stringify(self));
        }
      }
    }
  }
}

extern "C" const char* pli_objectToString(Object* self) {
  // C-callable wrapper for `objectToString'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(objectToString(self)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

int objectToInteger(Object* self) {
  // Coerce `self' to an integer, or throw a Stella Exception if the coersion is not feasible.
  // Floating point values will be coerced by rounding.
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PLI_LOGIC_SKOLEM)) {
      { Object* self000 = self;
        Skolem* self = ((Skolem*)(self000));

        { Object* value = valueOf(self);

          if (value == self) {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "Can't coerce " << "`" << self << "'" << " to an integer.";
              throw *newStellaException(stream000->theStringReader());
            }
          }
          else {
            return (objectToInteger(value));
          }
        }
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { Object* self001 = self;
        IntegerWrapper* self = ((IntegerWrapper*)(self001));

        return (self->wrapperValue);
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* self002 = self;
        FloatWrapper* self = ((FloatWrapper*)(self002));

        return (stella::round(self->wrapperValue));
      }
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "Can't coerce " << "`" << self << "'" << " to an integer.";
        throw *newStellaException(stream001->theStringReader());
      }
    }
  }
}

extern "C" int pli_objectToInteger(Object* self) {
  // C-callable wrapper for `objectToInteger'.
  try {
    return (objectToInteger(self));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL_INTEGER);
  }
}

double objectToFloat(Object* self) {
  // Coerce `self' to a float, or throw a Stella Exception if the coersion is not feasible.
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PLI_LOGIC_SKOLEM)) {
      { Object* self000 = self;
        Skolem* self = ((Skolem*)(self000));

        { Object* value = valueOf(self);

          if (value == self) {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "Can't coerce " << "`" << self << "'" << " to a float.";
              throw *newStellaException(stream000->theStringReader());
            }
          }
          else {
            return (objectToFloat(value));
          }
        }
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { Object* self001 = self;
        IntegerWrapper* self = ((IntegerWrapper*)(self001));

        return (self->numberWrapperToFloat());
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* self002 = self;
        FloatWrapper* self = ((FloatWrapper*)(self002));

        return (self->wrapperValue);
      }
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "Can't coerce " << "`" << self << "'" << " to a float.";
        throw *newStellaException(stream001->theStringReader());
      }
    }
  }
}

extern "C" double pli_objectToFloat(Object* self) {
  // C-callable wrapper for `objectToFloat'.
  try {
    return (objectToFloat(self));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL_FLOAT);
  }
}

const char* objectToParsableString(Object* self) {
  // Return a string representing a printed
  // representation of the object `self'.  Like `object-to-string', but puts
  // escaped double quotes around strings.
  if (subtypeOfStringP(safePrimaryType(self))) {
    { Object* self000 = self;
      StringWrapper* self = ((StringWrapper*)(self000));

      return (stringConcatenate("\"", self->wrapperValue, 1, "\""));
    }
  }
  else {
    return (objectToString(self));
  }
}

extern "C" const char* pli_objectToParsableString(Object* self) {
  // C-callable wrapper for `objectToParsableString'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(objectToParsableString(self)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

Symbol* getStellaType(Object* self) {
  // Return the name symbol of the STELLA class of which `self' is a direct instance.
  return (typeToSymbol(self->primaryType()));
}

extern "C" Symbol* pli_getStellaType(Object* self) {
  // C-callable wrapper for `getStellaType'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getStellaType(self)));
    return (((Symbol*)(oC_API_RESULT_BUFFERo)));
  }
}

Symbol* getLogicType(Object* self) {
  // Return the name symbol of the logic object type of `self'.  This type describes the basic
  // role this object plays in the logic system such as 'PROPOSITION', 'CONCEPT', 'THING', etc., as indicated by
  // its native object type, it does not have anything to do with type propositions asserted about `self'.
  return (typeToSymbol(logicalType(self)));
}

extern "C" Symbol* pli_getLogicType(Object* self) {
  // C-callable wrapper for `getLogicType'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getLogicType(self)));
    return (((Symbol*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* getStellaTypeName(Object* self) {
  // Return the qualified name of the STELLA class of which `self' is a direct instance.
  { Surrogate* type = self->primaryType();

    return (computeFullName(type->symbolName, ((Module*)(type->homeContext))));
  }
}

extern "C" const char* pli_getStellaTypeName(Object* self) {
  // C-callable wrapper for `getStellaTypeName'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getStellaTypeName(self)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* getStellaTypeShortName(Object* self) {
  // Return the unqualified name of the STELLA class of which `self' is a direct instance.
  return (self->primaryType()->symbolName);
}

extern "C" const char* pli_getStellaTypeShortName(Object* self) {
  // C-callable wrapper for `getStellaTypeShortName'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getStellaTypeShortName(self)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* getLogicTypeName(Object* self) {
  // Return the qualified name of the logic type of `self'.
  { Surrogate* type = logicalType(self);

    return (computeFullName(type->symbolName, ((Module*)(type->homeContext))));
  }
}

extern "C" const char* pli_getLogicTypeName(Object* self) {
  // C-callable wrapper for `getLogicTypeName'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getLogicTypeName(self)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* getLogicTypeShortName(Object* self) {
  // Return the unqualified name of the logic type of `self'.
  return (logicalType(self)->symbolName);
}

extern "C" const char* pli_getLogicTypeShortName(Object* self) {
  // C-callable wrapper for `getLogicTypeShortName'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getLogicTypeShortName(self)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

NamedDescription* oLITERAL_CONCEPTo = NULL;

NamedDescription* oSTRING_CONCEPTo = NULL;

NamedDescription* oINTEGER_CONCEPTo = NULL;

NamedDescription* oFLOAT_CONCEPTo = NULL;

Object* stringToObject(const char* string, LogicObject* type, Module* module, Environment* environment) {
  // Evaluate `string' with respect to `module' and `environment'
  // and return the corresponding logical term.  `type' is a concept used to assist the
  // correct interpretation of `string'.
  // 
  // Currently `type' only has an effect on the interpretation of literal types.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      module = oMODULEo;
      { Object* obj = readSExpressionFromString(string);

        if (subtypeOfP(safePrimaryType(obj), SGT_PLI_STELLA_LITERAL_WRAPPER)) {
          { Object* obj000 = obj;
            LiteralWrapper* obj = ((LiteralWrapper*)(obj000));

            if (!((boolean)(type))) {
              return (obj);
            }
            { Surrogate* testValue000 = safePrimaryType(obj);

              if (subtypeOfStringP(testValue000)) {
                { LiteralWrapper* obj001 = obj;
                  StringWrapper* obj = ((StringWrapper*)(obj001));

                  if (subrelationOfP(((NamedDescription*)(type)), oSTRING_CONCEPTo)) {
                    return (obj);
                  }
                  else {
                    { OutputStringStream* stream000 = newOutputStringStream();

                      *(stream000->nativeStream) << "String argument found, but " << "`" << type << "'" << " is not a subconcept of " << "`" << oSTRING_CONCEPTo << "'";
                      throw *newParsingError(stream000->theStringReader());
                    }
                  }
                }
              }
              else if (subtypeOfIntegerP(testValue000)) {
                { LiteralWrapper* obj002 = obj;
                  IntegerWrapper* obj = ((IntegerWrapper*)(obj002));

                  if (subrelationOfP(((NamedDescription*)(type)), oINTEGER_CONCEPTo)) {
                    return (obj);
                  }
                  else if (subrelationOfP(((NamedDescription*)(type)), oFLOAT_CONCEPTo)) {
                    return (wrapFloat(((double)(obj->wrapperValue))));
                  }
                  else {
                    return (getObject(string, module, environment));
                  }
                }
              }
              else if (subtypeOfFloatP(testValue000)) {
                { LiteralWrapper* obj003 = obj;
                  FloatWrapper* obj = ((FloatWrapper*)(obj003));

                  if (subrelationOfP(((NamedDescription*)(type)), oFLOAT_CONCEPTo)) {
                    return (obj);
                  }
                  else {
                    return (getObject(string, module, environment));
                  }
                }
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
        else {
          if (!((boolean)(type))) {
            return (getObject(string, module, environment));
          }
          else if (subrelationOfP(((NamedDescription*)(type)), oSTRING_CONCEPTo)) {
            return (wrapString(stringCopy(string)));
          }
          else if (subrelationOfP(((NamedDescription*)(type)), oLITERAL_CONCEPTo)) {
            { OutputStringStream* stream002 = newOutputStringStream();

              *(stream002->nativeStream) << "`" << string << "'" << " is a non-literal, but " << "`" << type << "'" << " is a subconcept of " << "`" << oLITERAL_CONCEPTo << "'";
              throw *newParsingError(stream002->theStringReader());
            }
          }
          else {
            return (getObject(string, module, environment));
          }
        }
      }
    }
  }
}

extern "C" Object* pli_stringToObject(const char* string, LogicObject* type, Module* module, Environment* environment) {
  // C-callable wrapper for `stringToObject'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(stringToObject(string, type, module, environment)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Object* stringToStellaExpression(const char* expression, Module* module, Environment* environment) {
  // Read the STELLA `expression' in `module' and return the result.
  // Raises a reader exception in case of incorrect STELLA syntax.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (readSExpressionFromString(expression));
    }
  }
}

extern "C" Object* pli_stringToStellaExpression(const char* expression, Module* module, Environment* environment) {
  // C-callable wrapper for `stringToStellaExpression'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(stringToStellaExpression(expression, module, environment)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Cons* helpGetTrueExtensionMembers(NamedDescription* relation, boolean specializeP) {
  { Cons* value000 = NIL;

    { Object* p = NULL;
      Iterator* iter000 = allExtensionMembers(relation);
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        p = iter000->value;
        if ((!((Proposition*)(p))->deletedP()) &&
            ((oREVERSEPOLARITYpo ? falseP(((Proposition*)(p))) : (trueP(((Proposition*)(p))) ||
            functionWithDefinedValueP(((Proposition*)(p))))))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(p, NIL);
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
              collect000->rest = cons(p, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    { Cons* result = value000;

      if (specializeP) {
        { LogicObject* sub = NULL;
          Iterator* iter001 = allSubcollections(relation);

          for (; iter001->nextP(); ) {
            sub = ((LogicObject*)(iter001->value));
            if (isaP(sub, SGT_PLI_LOGIC_NAMED_DESCRIPTION)) {
              { Object* p = NULL;
                Iterator* iter002 = allExtensionMembers(((NamedDescription*)(sub)));

                for (; iter002->nextP(); ) {
                  p = iter002->value;
                  if ((!((Proposition*)(p))->deletedP()) &&
                      ((oREVERSEPOLARITYpo ? falseP(((Proposition*)(p))) : (trueP(((Proposition*)(p))) ||
                      functionWithDefinedValueP(((Proposition*)(p))))))) {
                    result = cons(p, result);
                  }
                }
              }
            }
          }
        }
        return (result->removeDuplicates());
      }
      return (result);
    }
  }
}

Cons* helpGetPropositions(LogicObject* relation, Cons* arguments, int limit, Module* module, Environment* environment) {
  if (!((boolean)(relation))) {
    return (NIL);
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      { boolean assertionsonlyP = ((boolean)(environment)) &&
            stringEqlP(environment->level, "ASSERTION");
        boolean specializeP = !assertionsonlyP;

        { Object* value000 = NULL;

          { Object* arg = NULL;
            Cons* iter000 = arguments;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              arg = iter000->value;
              if (((boolean)(arg)) &&
                  isaP(arg, SGT_PLI_LOGIC_LOGIC_OBJECT)) {
                value000 = arg;
                break;
              }
            }
          }
          { Object* argumentwithbacklinks = value000;
            Iterator* iterator = (((boolean)(argumentwithbacklinks)) ? ((Iterator*)(allTrueDependentPropositions(argumentwithbacklinks, relation->surrogateValueInverse, specializeP))) : helpGetTrueExtensionMembers(((NamedDescription*)(relation)), specializeP)->allocateIterator());
            Cons* results = NIL;

            if (!(assertionsonlyP)) {
              oCONTEXTo = getPropertyTestContext();
            }
            { Proposition* p = NULL;
              Iterator* iter001 = iterator;

              for (; iter001->nextP(); ) {
                p = ((Proposition*)(iter001->value));
                { boolean testValue000 = false;

                  { boolean alwaysP000 = true;

                    { Object* inputarg = NULL;
                      Cons* iter002 = arguments;
                      Object* arg2 = NULL;
                      Vector* vector000 = p->arguments;
                      int index000 = 0;
                      int length000 = vector000->length();

                      for  (; (!(iter002 == NIL)) &&
                                (index000 < length000); 
                            iter002 = iter002->rest,
                            index000 = index000 + 1) {
                        inputarg = iter002->value;
                        arg2 = (vector000->theArray)[index000];
                        if (!((!((boolean)(inputarg))) ||
                            eqlP(inputarg, valueOf(arg2)))) {
                          alwaysP000 = false;
                          break;
                        }
                      }
                    }
                    testValue000 = alwaysP000;
                  }
                  if (testValue000) {
                    testValue000 = arguments->length() == p->arguments->length();
                  }
                  if (testValue000) {
                    results = cons(p, results);
                    limit = limit - 1;
                    if (limit == 0) {
                      break;
                    }
                  }
                }
              }
            }
            return (results);
          }
        }
      }
    }
  }
}

Proposition* getProposition(Object* relationAndArguments, Module* module, Environment* environment) {
  // Return a proposition matching `relation-and-arguments' that
  // has been asserted (or inferred by forward chaining).  `relation-and-arguments'
  // is a sequence containing objects and nulls.  The first argument must be the
  // name of a relation.  A null value acts like a wild card.  If more than one 
  // proposition matches the input criteria, the selection among satisficing
  // propositions is arbitrary.  This procedure is normally applied to single-valued
  // relations or functions.
  { Cons* list = sequenceToConsList(relationAndArguments);
    Object* relation = list->value;
    Cons* arguments = list->rest;

    return (((Proposition*)(helpGetPropositions(((LogicObject*)(relation)), arguments, 1, module, environment)->value)));
  }
}

extern "C" Proposition* pli_getProposition(Object* relationAndArguments, Module* module, Environment* environment) {
  // C-callable wrapper for `getProposition'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getProposition(relationAndArguments, module, environment)));
    return (((Proposition*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Proposition* sGetProposition(const char* relationAndArguments, const char* moduleName, Environment* environment) {
  // Return a proposition matching `relation-and-arguments' that
  // has been asserted (or inferred by forward chaining).  `relation-and-arguments'
  // is a string that begins with a left parenthesis, followed by a relation name, 
  // one or more argument identifiers, and terminated by a right parenthesis.  Each
  // argument identifier can be the name of a logical constant, a literal reference
  // such as a number, or the null identifier which acts like a wild card.
  // If more than one proposition matches the input criteria, the selection among
  // satisficing propositions is arbitrary.  This procedure is normally applied to
  // single-valued relations or functions.
  // 
  // A module name of `null' or the empty string refers to the current module.  If no module
  // with name `module-name' can be found, a STELLA `no-such-context-exception' is thrown.
  { Context* module = safelyGetModule(moduleName, environment);
    Cons* elements = explodeStringList(relationAndArguments, ((Module*)(module)));
    Object* relation = elements->value;
    Cons* arguments = elements->rest;

    return (((Proposition*)(helpGetPropositions(((LogicObject*)(relation)), arguments, 1, ((Module*)(module)), environment)->value)));
  }
}

extern "C" Proposition* pli_sGetProposition(const char* relationAndArguments, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetProposition'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sGetProposition(relationAndArguments, moduleName, environment)));
    return (((Proposition*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* getPropositions(Object* relationAndArguments, Module* module, Environment* environment) {
  // Return propositions matching `relation-and-arguments' that
  // have been asserted (or inferred by forward chaining).  `relation-and-arguments'
  // is a sequence containing objects and nulls.  The first argument must be the
  // name of a relation.  A null value acts like a wild card.
  { Cons* list = sequenceToConsList(relationAndArguments);
    Object* relation = list->value;
    Cons* arguments = list->rest;

    return (consToPlIterator(helpGetPropositions(((LogicObject*)(relation)), arguments, 0, module, environment)));
  }
}

extern "C" PlIterator* pli_getPropositions(Object* relationAndArguments, Module* module, Environment* environment) {
  // C-callable wrapper for `getPropositions'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getPropositions(relationAndArguments, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* sGetPropositions(const char* relationAndArguments, const char* moduleName, Environment* environment) {
  // Return propositions matching `relation-and-arguments' that
  // have been asserted (or inferred by forward chaining).  `relation-and-arguments'
  // is a string that begins with a left parenthesis, followed by a relation name, 
  // one or more argument identifiers, and terminated by a right parenthesis.  Each
  // argument identifier can be the name of a logical constant, a literal 
  // reference (e.g., a number), or the null identifier which acts like a wild card.
  // 
  // A module name of `null' or the empty string refers to the current module.  If no module
  // with name `module-name' can be found, a STELLA `no-such-context-exception' is thrown.
  { Context* module = safelyGetModule(moduleName, environment);
    Cons* elements = explodeStringList(relationAndArguments, ((Module*)(module)));
    Object* relation = elements->value;
    Cons* arguments = elements->rest;

    return (consToPlIterator(helpGetPropositions(((LogicObject*)(relation)), arguments, 0, ((Module*)(module)), environment)));
  }
}

extern "C" PlIterator* pli_sGetPropositions(const char* relationAndArguments, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetPropositions'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sGetPropositions(relationAndArguments, moduleName, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* getInconsistentPropositions(Module* module, Environment* environment) {
  // Return inconsistent propositions visible in `module'.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      module = oMODULEo;
      return (iteratorToPlIterator(allInconsistentPropositions(module, false)));
    }
  }
}

extern "C" PlIterator* pli_getInconsistentPropositions(Module* module, Environment* environment) {
  // C-callable wrapper for `getInconsistentPropositions'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getInconsistentPropositions(module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* getUnaryPropositions(LogicObject* relation, Object* arg, Module* module, Environment* environment) {
  // Return propositions such that (`relation' `arg')
  // is true.  The `relation' argument must be bound to a relation.  `arg' may be
  // set to NULL, which is interpreted as a wildcard.
  return (consToPlIterator(helpGetPropositions(relation, consList(1, arg), 0, module, environment)));
}

extern "C" PlIterator* pli_getUnaryPropositions(LogicObject* relation, Object* arg, Module* module, Environment* environment) {
  // C-callable wrapper for `getUnaryPropositions'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getUnaryPropositions(relation, arg, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Proposition* getBinaryProposition(LogicObject* relation, Object* arg1, Object* arg2, Module* module, Environment* environment) {
  // Return a proposition such that (`relation' `arg1' `arg2')
  // is true.  The `relation' argument must be bound to a relation.  One or both
  // of the `arg1' and `arg2' arguments may be set to NULL, which is interpreted
  // as a wildcard. If more than one proposition matches the input criteria,
  // the selection is arbitrary.  This procedure is normally applied to single-valued
  // relations or functions.
  return (((Proposition*)(helpGetPropositions(relation, consList(2, arg1, arg2), 1, module, environment)->value)));
}

extern "C" Proposition* pli_getBinaryProposition(LogicObject* relation, Object* arg1, Object* arg2, Module* module, Environment* environment) {
  // C-callable wrapper for `getBinaryProposition'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getBinaryProposition(relation, arg1, arg2, module, environment)));
    return (((Proposition*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* getBinaryPropositions(LogicObject* relation, Object* arg1, Object* arg2, Module* module, Environment* environment) {
  // Return propositions such that (`relation' `arg1' `arg2')
  // is true.  The `relation' argument must be bound to a relation.  One or both
  // of the `arg1' and `arg2' arguments may be set to NULL, which is interpreted
  // as a wildcard.
  return (consToPlIterator(helpGetPropositions(relation, consList(2, arg1, arg2), 0, module, environment)));
}

extern "C" PlIterator* pli_getBinaryPropositions(LogicObject* relation, Object* arg1, Object* arg2, Module* module, Environment* environment) {
  // C-callable wrapper for `getBinaryPropositions'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getBinaryPropositions(relation, arg1, arg2, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* getInferredBinaryPropositionValues(LogicObject* relation, Object* arg, Module* module, Environment* environment) {
  // Return all values `v' such that (`relation' `arg' `v')
  // has been asserted or can be inferred via a general PowerLoom `retrieve'.
  // Both `relation' and `arg' have to be non-NULL.
  { Cons* dummy1;
    Cons* dummy2;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        if (((boolean)(relation)) &&
            ((boolean)(arg))) {
          return (consToPlIterator(applyCachedRetrieve(listO(4, SYM_PLI_PLI_pR, SYM_PLI_PLI_pI, SYM_PLI_PLI_pV, NIL), listO(4, SYM_PLI_PLI_pR, SYM_PLI_PLI_pI, SYM_PLI_PLI_pV, NIL), consList(3, relation, arg, NULL), consList(0), SYM_PLI_PLI_F_GET_INFERRED_BINARY_PROPOSITION_VALUES_QUERY_000, dummy1, dummy2)));
        }
        else {
          return (EMPTY_PL_ITERATOR);
        }
      }
    }
  }
}

extern "C" PlIterator* pli_getInferredBinaryPropositionValues(LogicObject* relation, Object* arg, Module* module, Environment* environment) {
  // C-callable wrapper for `getInferredBinaryPropositionValues'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getInferredBinaryPropositionValues(relation, arg, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* sGetInferredBinaryPropositionValues(const char* relationName, const char* argName, const char* moduleName, Environment* environment) {
  // Return all values `v' such that (`relation-name' `arg-name' `v')
  // has been asserted or can be inferred via a general PowerLoom `retrieve'.
  // 
  // A module name of `null' or the empty string refers to the current module. 
  // If no module can be found with the name `module-name', then a STELLA
  // `no-such-context-exception' is thrown.
  { Context* module = safelyGetModule(moduleName, environment);
    Object* relation = safelyGetRelation(relationName, ((Module*)(module)), environment);
    Object* object = safelyGetObject(argName, ((Module*)(module)), environment);

    return (getInferredBinaryPropositionValues(((LogicObject*)(relation)), object, ((Module*)(module)), environment));
  }
}

extern "C" PlIterator* pli_sGetInferredBinaryPropositionValues(const char* relationName, const char* argName, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetInferredBinaryPropositionValues'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sGetInferredBinaryPropositionValues(relationName, argName, moduleName, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* getPropositionsOf(LogicObject* object, Module* module, Environment* environment) {
  // Return all propositions that have `object' among their arguments,
  // and that are TRUE in the scope of the module `module'.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      if (((boolean)(object))) {
        return (listToPlIterator(allFactsOfInstance(object, false, false)));
      }
      else {
        return (EMPTY_PL_ITERATOR);
      }
    }
  }
}

extern "C" PlIterator* pli_getPropositionsOf(LogicObject* object, Module* module, Environment* environment) {
  // C-callable wrapper for `getPropositionsOf'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getPropositionsOf(object, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* sGetPropositionsOf(const char* objectName, const char* moduleName, Environment* environment) {
  // Return all propositions that have the object named `object-name' among
  // their arguments, and that are TRUE in the scope of the module `module-name'.
  // A module name of `null' or the empty string refers to the current module. 
  // If no module can be found with the name `module-name', then a Stella 
  // `no-such-context-exception' is thrown.
  { Context* module = safelyGetModule(moduleName, environment);
    Object* object = safelyGetObject(objectName, ((Module*)(module)), environment);

    return (getPropositionsOf(((LogicObject*)(object)), ((Module*)(module)), environment));
  }
}

extern "C" PlIterator* pli_sGetPropositionsOf(const char* objectName, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetPropositionsOf'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sGetPropositionsOf(objectName, moduleName, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* getPropositionsInModule(Module* module, Environment* environment) {
  // Return propositions that have been locally conceived in
  // the module `module' (but are not necessarily true).
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      module = oMODULEo;
      return (consToPlIterator(allPropositions(module, true)->consify()));
    }
  }
}

extern "C" PlIterator* pli_getPropositionsInModule(Module* module, Environment* environment) {
  // C-callable wrapper for `getPropositionsInModule'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getPropositionsInModule(module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

boolean isTrueUnaryProposition(LogicObject* relation, Object* arg, Module* module, Environment* environment) {
  // Return TRUE if the proposition (`relation' `arg') has
  // been asserted (or inferred by forward chaining).
  return (!(helpGetPropositions(relation, consList(1, arg), 1, module, environment) == NIL));
}

extern "C" int pli_isTrueUnaryProposition(LogicObject* relation, Object* arg, Module* module, Environment* environment) {
  // C-callable wrapper for `isTrueUnaryProposition'.
  try {
    return (isTrueUnaryProposition(relation, arg, module, environment));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (false);
  }
}

boolean isTrueBinaryProposition(LogicObject* relation, Object* arg, Object* value, Module* module, Environment* environment) {
  // Return TRUE if the proposition (`relation' `arg' `value') has
  // been asserted (or inferred by forward chaining).
  return (((boolean)(getBinaryProposition(relation, arg, value, module, environment))));
}

extern "C" int pli_isTrueBinaryProposition(LogicObject* relation, Object* arg, Object* value, Module* module, Environment* environment) {
  // C-callable wrapper for `isTrueBinaryProposition'.
  return (isTrueBinaryProposition(relation, arg, value, module, environment));
}

boolean isTrueNaryProposition(Object* relationAndArguments, Module* module, Environment* environment) {
  // Return TRUE if a proposition (`relation' `args') has
  // been asserted (or inferred by forward chaining).
  return (((boolean)(getProposition(relationAndArguments, module, environment))));
}

extern "C" int pli_isTrueNaryProposition(Object* relationAndArguments, Module* module, Environment* environment) {
  // C-callable wrapper for `isTrueNaryProposition'.
  return (isTrueNaryProposition(relationAndArguments, module, environment));
}

boolean sIsTrueNaryProposition(const char* relationAndArguments, const char* moduleName, Environment* environment) {
  // Return TRUE if a proposition that prints as the string
  // `relation-and-arguments' is true in the module named `module-name'.
  // A module name of `null' or the empty string refers to the current module. 
  // If no module can be found with the name `module-name', then a Stella 
  // `no-such-context-exception' is thrown.
  return (((boolean)(sGetProposition(relationAndArguments, moduleName, environment))));
}

extern "C" int pli_sIsTrueNaryProposition(const char* relationAndArguments, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sIsTrueNaryProposition'.
  return (sIsTrueNaryProposition(relationAndArguments, moduleName, environment));
}

boolean isTrueProposition(Proposition* proposition, Module* module, Environment* environment) {
  // Return TRUE if `proposition' is TRUE in the module `module'.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return ((!proposition->deletedP()) &&
          ((oREVERSEPOLARITYpo ? falseP(proposition) : (trueP(proposition) ||
          functionWithDefinedValueP(proposition)))));
    }
  }
}

extern "C" int pli_isTrueProposition(Proposition* proposition, Module* module, Environment* environment) {
  // C-callable wrapper for `isTrueProposition'.
  return (isTrueProposition(proposition, module, environment));
}

boolean isSubrelation(LogicObject* sub, LogicObject* super, Module* module, Environment* environment) {
  // Return TRUE if `sub' is a subconcept/subrelation of `super'.
  if ((!((boolean)(sub))) ||
      (!((boolean)(super)))) {
    return (false);
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (trueTruthValueP(descriptionSpecializesDescriptionP(((Description*)(sub)), ((Description*)(super)))));
    }
  }
}

extern "C" int pli_isSubrelation(LogicObject* sub, LogicObject* super, Module* module, Environment* environment) {
  // C-callable wrapper for `isSubrelation'.
  return (isSubrelation(sub, super, module, environment));
}

PlIterator* getProperSubrelations(LogicObject* relation, Module* module, Environment* environment) {
  // Return relations that specialize `relation'.
  // Non-reflexive.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (consToPlIterator(allSubrelations(((NamedDescription*)(relation)), true)));
    }
  }
}

extern "C" PlIterator* pli_getProperSubrelations(LogicObject* relation, Module* module, Environment* environment) {
  // C-callable wrapper for `getProperSubrelations'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getProperSubrelations(relation, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

PlIterator* getDirectSubrelations(LogicObject* relation, Module* module, Environment* environment) {
  // Return relations that directly specialize `relation'.
  // Non-reflexive.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (consToPlIterator(allDirectSubrelations(((NamedDescription*)(relation)), true)));
    }
  }
}

extern "C" PlIterator* pli_getDirectSubrelations(LogicObject* relation, Module* module, Environment* environment) {
  // C-callable wrapper for `getDirectSubrelations'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getDirectSubrelations(relation, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

PlIterator* getProperSuperrelations(LogicObject* relation, Module* module, Environment* environment) {
  // Return relations that generalize `relation'.
  // Non-reflexive.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (consToPlIterator(allSuperrelations(((NamedDescription*)(relation)), true)));
    }
  }
}

extern "C" PlIterator* pli_getProperSuperrelations(LogicObject* relation, Module* module, Environment* environment) {
  // C-callable wrapper for `getProperSuperrelations'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getProperSuperrelations(relation, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

PlIterator* getDirectSuperrelations(LogicObject* relation, Module* module, Environment* environment) {
  // Return relations that directly generalize `relation'.
  // Non-reflexive.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (consToPlIterator(allDirectSuperrelations(((NamedDescription*)(relation)), true)));
    }
  }
}

extern "C" PlIterator* pli_getDirectSuperrelations(LogicObject* relation, Module* module, Environment* environment) {
  // C-callable wrapper for `getDirectSuperrelations'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getDirectSuperrelations(relation, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

boolean isInstance(Object* object, LogicObject* concept, Module* module, Environment* environment) {
  // Return TRUE if `object' is an instance of the concept `concept'.  This uses subsumption inference only.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (testIsaP(object, concept->surrogateValueInverse));
    }
  }
}

extern "C" int pli_isInstance(Object* object, LogicObject* concept, Module* module, Environment* environment) {
  // C-callable wrapper for `isInstance'.
  try {
    return (isInstance(object, concept, module, environment));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (false);
  }
}

boolean isA(Object* object, LogicObject* concept, Module* module, Environment* environment) {
  // Deprecated - use `is-instance' instead.
  return (isInstance(object, concept, module, environment));
}

PlIterator* getConceptInstances(LogicObject* concept, Module* module, Environment* environment) {
  // Return instances of the concept `concept'.
  // Include instances of subconcepts of `concept'.  Depending on `concept',
  // the return values could be (wrapped) literals.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      module = oMODULEo;
      if (((boolean)(environment)) &&
          stringEqlP(environment->level, "ASSERTION")) {
        return (listToPlIterator(assertedCollectionMembers(concept, false)->removeDeletedMembers()));
      }
      else {
        return (retrieve(listO(4, SYM_PLI_LOGIC_ALL, SYM_PLI_LOGIC_pX, cons(objectName(concept), cons(SYM_PLI_LOGIC_pX, NIL)), NIL), module, environment));
      }
    }
  }
}

extern "C" PlIterator* pli_getConceptInstances(LogicObject* concept, Module* module, Environment* environment) {
  // C-callable wrapper for `getConceptInstances'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getConceptInstances(concept, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* sGetConceptInstances(const char* conceptName, const char* moduleName, Environment* environment) {
  // Return instances of concept `concept-name'.
  // Include instances of subconcepts of `concept-name'.  Depending on `concept-name',
  // the return values could be (wrapped) literals.
  // 
  // A module name of `null' or the empty string refers to the current module. 
  // If no module can be found with the name `module-name', then a Stella 
  // `no-such-context-exception' is thrown.
  { Context* module = safelyGetModule(moduleName, environment);
    Object* concept = safelyGetConcept(conceptName, ((Module*)(module)), environment);

    if (((boolean)(module)) &&
        ((boolean)(concept))) {
      return (getConceptInstances(((LogicObject*)(concept)), ((Module*)(module)), environment));
    }
    else {
      return (EMPTY_PL_ITERATOR);
    }
  }
}

extern "C" PlIterator* pli_sGetConceptInstances(const char* conceptName, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetConceptInstances'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sGetConceptInstances(conceptName, moduleName, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* getDirectConceptInstances(LogicObject* concept, Module* module, Environment* environment) {
  // Return instances of concept `concept'.
  // Exclude instances of subconcepts of `concept'.  Depending on `concept',
  // the return values could be (wrapped) literals.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      module = oMODULEo;
      if (((boolean)(environment)) &&
          stringEqlP(environment->level, "ASSERTION")) {
        return (listToPlIterator(assertedCollectionMembers(concept, true)->removeDeletedMembers()));
      }
      else {
        return (retrieve(listO(4, SYM_PLI_LOGIC_ALL, SYM_PLI_LOGIC_pX, listO(4, SYM_PLI_STELLA_AND, cons(objectName(concept), cons(SYM_PLI_LOGIC_pX, NIL)), listO(3, SYM_PLI_LOGIC_FAIL, listO(4, SYM_PLI_STELLA_EXISTS, cons(SYM_PLI_LOGIC_pY, NIL), listO(4, SYM_PLI_STELLA_AND, listO(3, SYM_PLI_PLI_PROPER_SUBRELATION, objectName(concept), cons(SYM_PLI_LOGIC_pY, NIL)), listO(3, SYM_PLI_LOGIC_pY, SYM_PLI_LOGIC_pX, NIL), NIL), NIL), NIL), NIL), NIL), module, environment));
      }
    }
  }
}

extern "C" PlIterator* pli_getDirectConceptInstances(LogicObject* concept, Module* module, Environment* environment) {
  // C-callable wrapper for `getDirectConceptInstances'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getDirectConceptInstances(concept, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* sGetDirectConceptInstances(const char* conceptName, const char* moduleName, Environment* environment) {
  // Return instances of concept `concept-name'.
  // Exclude instances of subconcepts of `concept-name'.  Depending on `concept-name',
  // the return values could be (wrapped) literals.
  // 
  // A module name of `null' or the empty string refers to the current module. 
  // If no module can be found with the name `module-name', then a Stella 
  // `no-such-context-exception' is thrown.
  { Context* module = safelyGetModule(moduleName, environment);
    Object* concept = safelyGetConcept(conceptName, ((Module*)(module)), environment);

    if (((boolean)(concept))) {
      return (getDirectConceptInstances(((LogicObject*)(concept)), ((Module*)(module)), environment));
    }
    else {
      return (EMPTY_PL_ITERATOR);
    }
  }
}

extern "C" PlIterator* pli_sGetDirectConceptInstances(const char* conceptName, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetDirectConceptInstances'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(sGetDirectConceptInstances(conceptName, moduleName, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

PlIterator* getConceptInstancesMatchingValue(LogicObject* concept, LogicObject* relation, Object* value, Module* module, Environment* environment) {
  // Return members of concept `concept' that
  // have an attribute matching `value' for the binary relation `relation', i.e.,
  // `(relation <result> value)' holds.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      module = oMODULEo;
      { PlIterator* instances = getConceptInstances(concept, module, environment);
        Cons* answers = NIL;

        { Object* i = NULL;
          PlIterator* iter000 = instances;

          for (; iter000->nextP(); ) {
            i = iter000->value;
            if (isTrueBinaryProposition(relation, i, value, module, environment)) {
              answers = cons(i, answers);
            }
          }
        }
        return (consToPlIterator(answers));
      }
    }
  }
}

extern "C" PlIterator* pli_getConceptInstancesMatchingValue(LogicObject* concept, LogicObject* relation, Object* value, Module* module, Environment* environment) {
  // C-callable wrapper for `getConceptInstancesMatchingValue'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getConceptInstancesMatchingValue(concept, relation, value, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

Object* getConceptInstanceMatchingValue(LogicObject* concept, LogicObject* relation, Object* value, Module* module, Environment* environment) {
  // Return a member of concept `concept' that
  // has an attribute matching `value' for the binary relation `relation', i.e.,
  // `(relation <result> value)' holds.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      module = oMODULEo;
      { PlIterator* instances = getConceptInstances(concept, module, environment);

        { Object* i = NULL;
          PlIterator* iter000 = instances;

          for (; iter000->nextP(); ) {
            i = iter000->value;
            if (isTrueBinaryProposition(relation, i, value, module, environment)) {
              return (i);
            }
          }
        }
        return (NULL);
      }
    }
  }
}

extern "C" Object* pli_getConceptInstanceMatchingValue(LogicObject* concept, LogicObject* relation, Object* value, Module* module, Environment* environment) {
  // C-callable wrapper for `getConceptInstanceMatchingValue'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getConceptInstanceMatchingValue(concept, relation, value, module, environment)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
}

Cons* helpGetTypes(LogicObject* object, Module* module, Environment* environment) {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      { Cons* derivabletypes = NIL;

        if ((!((boolean)(environment))) ||
            (((boolean)(environment)) &&
             stringEqlP(environment->level, "INFERENCE"))) {
          derivabletypes = allTypes(object);
        }
        else if (((boolean)(environment)) &&
            stringEqlP(environment->level, "ASSERTION")) {
          derivabletypes = allAssertedTypes(object);
        }
        else if (((boolean)(environment)) &&
            stringEqlP(environment->level, "TAXONOMIC")) {
          derivabletypes = allTaxonomicTypes(object);
        }
        return (derivabletypes);
      }
    }
  }
}

PlIterator* getTypes(LogicObject* object, Module* module, Environment* environment) {
  // Return all named concepts that `object' belongs to.
  return (consToPlIterator(helpGetTypes(object, module, environment)));
}

extern "C" PlIterator* pli_getTypes(LogicObject* object, Module* module, Environment* environment) {
  // C-callable wrapper for `getTypes'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getTypes(object, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* getDirectTypes(LogicObject* object, Module* module, Environment* environment) {
  // Return most specific concepts that `object' belongs to.
  return (consToPlIterator(mostSpecificNamedDescriptions(copyConsList(helpGetTypes(object, module, environment)))));
}

extern "C" PlIterator* pli_getDirectTypes(LogicObject* object, Module* module, Environment* environment) {
  // C-callable wrapper for `getDirectTypes'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getDirectTypes(object, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* getRelationExtension(LogicObject* relation, Module* module, Environment* environment) {
  // Return propositions that satisfy `relation'.
  // Include propositions that satisfy subrelations of `relation'.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (consToPlIterator(helpGetTrueExtensionMembers(((NamedDescription*)(relation)), !(((boolean)(environment)) &&
          stringEqlP(environment->level, "ASSERTION")))));
    }
  }
}

extern "C" PlIterator* pli_getRelationExtension(LogicObject* relation, Module* module, Environment* environment) {
  // C-callable wrapper for `getRelationExtension'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getRelationExtension(relation, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

PlIterator* sGetRelationExtension(const char* relationName, const char* moduleName, Environment* environment) {
  // Return propositions that satisfy the relation named
  // `relation-name'.  Include propositions that satisfy subrelations of the relation.
  { Context* module = safelyGetModule(moduleName, environment);
    Object* relation = safelyGetRelation(relationName, ((Module*)(module)), environment);

    if (((boolean)(relation))) {
      return (getRelationExtension(((LogicObject*)(relation)), ((Module*)(module)), environment));
    }
    else {
      return (EMPTY_PL_ITERATOR);
    }
  }
}

extern "C" PlIterator* pli_sGetRelationExtension(const char* relationName, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetRelationExtension'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(sGetRelationExtension(relationName, moduleName, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

Module* getModule(const char* name, Environment* environment) {
  // Return a module named `name' or NULL if no such module exists.
  environment = environment;
  return (getStellaModule(name, false));
}

extern "C" Module* pli_getModule(const char* name, Environment* environment) {
  // C-callable wrapper for `getModule'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getModule(name, environment)));
    return (((Module*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Module* getExistingModule(const char* name, Environment* environment) {
  // Return the module named `name' or raise a STELLA `no-such-context-exception' if it doesn't exist.
  environment = environment;
  return (getStellaModule(name, true));
}

extern "C" Module* pli_getExistingModule(const char* name, Environment* environment) {
  // C-callable wrapper for `getExistingModule'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getExistingModule(name, environment)));
    return (((Module*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Module* getCurrentModule(Environment* environment) {
  // Return the currently set module
  environment = environment;
  return (oMODULEo);
}

extern "C" Module* pli_getCurrentModule(Environment* environment) {
  // C-callable wrapper for `getCurrentModule'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getCurrentModule(environment)));
    return (((Module*)(oC_API_RESULT_BUFFERo)));
  }
}

Module* getHomeModule(LogicObject* object) {
  // Return the module in which `object' was created.
  return (object->homeModule());
}

extern "C" Module* pli_getHomeModule(LogicObject* object) {
  // C-callable wrapper for `getHomeModule'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getHomeModule(object)));
    return (((Module*)(oC_API_RESULT_BUFFERo)));
  }
}

PlIterator* getModules(boolean kbModulesOnlyP) {
  // Return all modules currently loaded into PowerLoom.  If `kb-modules-only?'
  // is `true', then Stella modules that are used only for program code are
  // not included in the list.
  return (consToPlIterator(listModules(kbModulesOnlyP)));
}

extern "C" PlIterator* pli_getModules(int kbModulesOnlyP) {
  // C-callable wrapper for `getModules'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getModules(kbModulesOnlyP)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

Module* createModule(const char* name, Module* parent, boolean caseSensitiveP) {
  // Creates a new module `name' as a child of `parent'.  The flag
  // `case-sensitive?' controls whether names read in this module will be
  // case sensitive or not.
  { const char* fullName = (((boolean)(parent)) ? stringConcatenate(parent->moduleFullName, "/", 1, name) : name);
    Symbol* caseSensitiveSymbol = (caseSensitiveP ? SYM_PLI_STELLA_TRUE : SYM_PLI_STELLA_FALSE);

    return (defineModule(fullName, listO(3, KWD_PLI_CASE_SENSITIVEp, caseSensitiveSymbol, NIL)));
  }
}

extern "C" Module* pli_createModule(const char* name, Module* parent, int caseSensitiveP) {
  // C-callable wrapper for `createModule'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(createModule(name, parent, caseSensitiveP)));
    return (((Module*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Module* sCreateModule(const char* name, const char* parentName, boolean caseSensitiveP, Environment* environment) {
  // Creates a new module `name' as a child of `parent-name'.  The flag
  // `case-sensitive?' controls whether names read in this module will be
  // case sensitive or not.
  return (createModule(name, ((Module*)(safelyGetModule(parentName, environment))), caseSensitiveP));
}

extern "C" Module* pli_sCreateModule(const char* name, const char* parentName, int caseSensitiveP, Environment* environment) {
  // C-callable wrapper for `sCreateModule'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sCreateModule(name, parentName, caseSensitiveP, environment)));
    return (((Module*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Module* changeModule(Module* module) {
  // Set the current module to `module' and return it.
  // If `module' is `null', then no switch is performed and the current
  // module is returned.
  if (!((boolean)(module))) {
    return (oMODULEo);
  }
  return (module->changeModule());
}

extern "C" Module* pli_changeModule(Module* module) {
  // C-callable wrapper for `changeModule'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(changeModule(module)));
    return (((Module*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Module* sChangeModule(const char* name, Environment* environment) {
  // Set the current module to the module named `name'.
  // The return value is the module named `name' unless `name' is null or
  // the empty string.  In that case, the current module is returned.
  // If no module named `name' exists, a Stella `no-such-context-exception'
  // is thrown.
  return (changeModule(((Module*)(safelyGetModule(name, environment)))));
}

extern "C" Module* pli_sChangeModule(const char* name, Environment* environment) {
  // C-callable wrapper for `sChangeModule'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sChangeModule(name, environment)));
    return (((Module*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Module* clearModule(Module* module) {
  // Destroy the contents of the module `module' as well as
  // the contents of all of its children, recursively.
  callClearModule(consList(1, module));
  return (module);
}

extern "C" Module* pli_clearModule(Module* module) {
  // C-callable wrapper for `clearModule'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(clearModule(module)));
    return (((Module*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Module* sClearModule(const char* name, Environment* environment) {
  // Destroy the contents of the module named `name', as
  // well as the contents of all of its children, recursively.  If no module
  // named `name' exists, a Stella `no-such-context-exception' is thrown.
  { Context* module = safelyGetModule(name, environment);

    callClearModule(consList(1, module));
    return (((Module*)(module)));
  }
}

extern "C" Module* pli_sClearModule(const char* name, Environment* environment) {
  // C-callable wrapper for `sClearModule'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sClearModule(name, environment)));
    return (((Module*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* getChildModules(Module* module) {
  // Return the modules that are immediate children of `module'.
  { Cons* directsubmodules = NIL;

    { Context* child = NULL;
      Cons* iter000 = module->childContexts->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        child = ((Context*)(iter000->value));
        if (isaP(child, SGT_PLI_STELLA_MODULE)) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(child, NIL);
              if (directsubmodules == NIL) {
                directsubmodules = collect000;
              }
              else {
                addConsToEndOfConsList(directsubmodules, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(child, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (consToPlIterator(directsubmodules));
  }
}

extern "C" PlIterator* pli_getChildModules(Module* module) {
  // C-callable wrapper for `getChildModules'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getChildModules(module)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

PlIterator* sGetChildModules(const char* name, Environment* environment) {
  // Return the modules that are immediate children of module `name'.
  // If no module named `name' exists, a Stella `no-such-context-exception'
  // is thrown.
  return (getChildModules(((Module*)(safelyGetModule(name, environment)))));
}

extern "C" PlIterator* pli_sGetChildModules(const char* name, Environment* environment) {
  // C-callable wrapper for `sGetChildModules'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(sGetChildModules(name, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

PlIterator* getParentModules(Module* module) {
  // Return the modules that are immediate parents of `module'.
  return (listToPlIterator(module->parentModules));
}

extern "C" PlIterator* pli_getParentModules(Module* module) {
  // C-callable wrapper for `getParentModules'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getParentModules(module)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

PlIterator* sGetParentModules(const char* name, Environment* environment) {
  // Return the modules that are immediate parents of module `name'.
  // If no module named `name' exists, a Stella `no-such-context-exception'
  // is thrown.
  return (getParentModules(((Module*)(safelyGetModule(name, environment)))));
}

extern "C" PlIterator* pli_sGetParentModules(const char* name, Environment* environment) {
  // C-callable wrapper for `sGetParentModules'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(sGetParentModules(name, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* generateUniqueName(const char* prefix, Module* module, Environment* environment) {
  // Generates a name based on `prefix' with a number appended that
  // is not currently in use in `module.'  In a non-case-sensitive module, the returned
  // name will be all upper case (This latter feature may change!)
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      module = oMODULEo;
      if (!(module->caseSensitiveP ||
          allUpperCaseStringP(prefix))) {
        prefix = stringUpcase(prefix);
      }
      return (yieldUniqueGensymName(prefix, module));
    }
  }
}

extern "C" const char* pli_generateUniqueName(const char* prefix, Module* module, Environment* environment) {
  // C-callable wrapper for `generateUniqueName'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(generateUniqueName(prefix, module, environment)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

Keyword* createKeyword(const char* name) {
  // Returns the Stella keyword `name', creating it if
  // necessary.  `name' is treated literally and case-sensitively.
  // This should generally not be necessary to do.
  return (((Keyword*)(internRigidSymbolWrtModule(name, oMODULEo, KEYWORD_SYM))));
}

extern "C" Keyword* pli_createKeyword(const char* name) {
  // C-callable wrapper for `createKeyword'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(createKeyword(name)));
    return (((Keyword*)(oC_API_RESULT_BUFFERo)));
  }
}

Symbol* createSymbol(const char* name, Module* module, Environment* environment) {
  // Returns the Stella symbol `name' visible in `module',
  // creating it if necessary.  `name' is treated literally and ALWAYS case-sensitively,
  // even if `module' is case insensitive. This should generally not be necessary to do.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      module = oMODULEo;
      return (internSymbolInModule(name, module, false));
    }
  }
}

extern "C" Symbol* pli_createSymbol(const char* name, Module* module, Environment* environment) {
  // C-callable wrapper for `createSymbol'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(createSymbol(name, module, environment)));
    return (((Symbol*)(oC_API_RESULT_BUFFERo)));
  }
}

LogicObject* createObject(const char* name, LogicObject* concept, Module* module, Environment* environment) {
  // Create an object named `name' of type `concept' in the designated
  // module.  Both `name' and `concept' can be `null'.  If `name' is `null' then an
  // object will be created with a new, non-conflicting name based on the name of
  // `concept', or system-generated if no concept is specified.  If `concept' is
  // `null', then the object will be of type THING.  It is an error to create an
  // object with the same name as an existing object.
  // 
  // Note that the string can be a qualified name, in which case the object
  // will be created in the module specified, but with a name as determined
  // by the qualified name.  Vertical bars in the name string are interpreted
  // as Stella escape characters.
  // 
  // Note that because names in modules that are not case-sensitive are
  // canonicalized, the name of the returned object may not match `name'
  // exactly.
  // 
  // Return the object.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      module = oMODULEo;
      { LogicObject* object = NULL;
        Symbol* nameSymbol = NULL;
        Surrogate* objectSurrogate = NULL;

        if (name != NULL) {
          nameSymbol = ((Symbol*)(internStellaName(name)));
        }
        else if (((boolean)(concept))) {
          nameSymbol = internSymbol(getShortName(concept));
          nameSymbol = internSymbolInModule(generateUniqueName(nameSymbol->symbolName, ((Module*)(nameSymbol->homeContext)), NULL), ((Module*)(nameSymbol->homeContext)), true);
        }
        else {
          nameSymbol = internSymbolInModule(generateUniqueName("I", NULL, NULL), module, true);
        }
        objectSurrogate = lookupSurrogateInModule(nameSymbol->symbolName, ((Module*)(nameSymbol->homeContext)), false);
        if (!((boolean)(objectSurrogate))) {
          objectSurrogate = internSurrogateInModule(nameSymbol->symbolName, ((Module*)(nameSymbol->homeContext)), false);
        }
        object = ((LogicObject*)(helpCreateLogicInstance(objectSurrogate, NULL)));
        if (((boolean)(concept))) {
          if (((boolean)(assertUnaryProposition(concept, object, module, environment)))) {
            return (object);
          }
          else {
            return (NULL);
          }
        }
        return (object);
      }
    }
  }
}

extern "C" LogicObject* pli_createObject(const char* name, LogicObject* concept, Module* module, Environment* environment) {
  // C-callable wrapper for `createObject'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(createObject(name, concept, module, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

LogicObject* sCreateObject(const char* name, const char* conceptName, const char* moduleName, Environment* environment) {
  // Create an object named `name' of type `concept-name' in the designated
  // module.  Both `name' and `concept-name' can be null strings.  If `name' is a null string
  // then an object will be created with a new, non-conflicting name based on `concept-name', or
  // system-generated if no concept nameis specified.  If `concept-name' is the null string, then
  // the object will be of type THING.
  // 
  // A module name of `null' or the empty string refers to the current module. 
  // If no module can be found with the name `module-name', then a Stella 
  // `no-such-context-exception' is thrown.
  // 
  // Note that because names in modules that are not case-sensitive are canonicalized,
  // the name of the returned object may not match `name' exactly.
  // 
  // Return the object.
  { Context* module = safelyGetModule(moduleName, environment);

    return (createObject(name, ((LogicObject*)(safelyGetConcept(conceptName, ((Module*)(module)), environment))), ((Module*)(module)), environment));
  }
}

extern "C" LogicObject* pli_sCreateObject(const char* name, const char* conceptName, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sCreateObject'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sCreateObject(name, conceptName, moduleName, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

LogicObject* createConcept(const char* name, LogicObject* parent, Module* module, Environment* environment) {
  // Create a concept named `name' in the designated `module', with the
  // designated `parent' superconcept (which can be left undefined).  Additional
  // superconcepts can be added via assertions of the `subset-of' relation.  Note
  // that a specified `parent' concept needs to be created separately.
  // 
  // Note that because names in modules that are not case-sensitive are canonicalized,
  // the name of the returned object may not match `name' exactly.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (callDefconcept(cons(internStellaName(name), ((((boolean)(parent)) ? listO(3, KWD_PLI_SUBSET_OF, objectName(parent), NIL) : NIL))->concatenate(NIL, 0))));
    }
  }
}

extern "C" LogicObject* pli_createConcept(const char* name, LogicObject* parent, Module* module, Environment* environment) {
  // C-callable wrapper for `createConcept'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(createConcept(name, parent, module, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

LogicObject* sCreateConcept(const char* name, const char* parentName, const char* moduleName, Environment* environment) {
  // Create a concept named `name' in the designated module, with
  // with the concept named `parent-name' as superconcept (which can be left
  // undefined).  Additional superconcepts can be added via assertions of the
  // `subset-of' relation.  Note that a specified parent concept needs to be
  // created separately.
  // 
  // A module name of `null' or the empty string refers to the current module. 
  // If no module can be found with the name `module-name', then a Stella 
  // `no-such-context-exception' is thrown.
  // 
  // Note that because names in modules that are not case-sensitive are canonicalized,
  // the name of the returned object may not match `name' exactly.
  { Context* module = safelyGetModule(moduleName, environment);

    return (createConcept(name, ((LogicObject*)(safelyGetConcept(parentName, ((Module*)(module)), environment))), ((Module*)(module)), environment));
  }
}

extern "C" LogicObject* pli_sCreateConcept(const char* name, const char* parentName, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sCreateConcept'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sCreateConcept(name, parentName, moduleName, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

LogicObject* createRelation(const char* name, int arity, Module* module, Environment* environment) {
  // Create a relation named `name' with arity `arity' in the
  // designated module.  Domain and range information can be added via assertions
  // of `nth-domain' (or `domain' and `range') relations.
  // 
  // Note that because names in modules that are not case-sensitive are canonicalized,
  // the name of the returned object may not match `name' exactly.
  if (!(arity > 0)) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "PARSING ERROR: " << "Relations must have arity of at least 1" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_PLI_ERROR);
      }
      throw *newParsingError(stream000->theStringReader());
    }
  }
  { Cons* args = NIL;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        module = oMODULEo;
        { int i = NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = arity - 1;
          Cons* collect000 = NULL;

          for  (; iter000 <= upperBound000; 
                iter000 = iter000 + 1) {
            i = iter000;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(yieldSystemDefinedParameterName(i, module), NIL);
                if (args == NIL) {
                  args = collect000;
                }
                else {
                  addConsToEndOfConsList(args, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(yieldSystemDefinedParameterName(i, module), NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        return (callDefrelation(cons(internStellaName(name), cons(args, NIL))));
      }
    }
  }
}

extern "C" LogicObject* pli_createRelation(const char* name, int arity, Module* module, Environment* environment) {
  // C-callable wrapper for `createRelation'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(createRelation(name, arity, module, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

LogicObject* sCreateRelation(const char* name, int arity, const char* moduleName, Environment* environment) {
  // Create a relation named `name' with arity `arity' in the
  // designated module.  Domain and range information can be added via assertions
  // of `nth-domain' (or `domain' and `range') relations.
  // 
  // A module name of `null' or the empty string refers to the current module. 
  // If no module can be found with the name `module-name', then a Stella 
  // `no-such-context-exception' is thrown.
  // 
  // Note that because names in modules that are not case-sensitive are canonicalized,
  // the name of the returned object may not match `name' exactly.
  return (createRelation(name, arity, ((Module*)(safelyGetModule(moduleName, environment))), environment));
}

extern "C" LogicObject* pli_sCreateRelation(const char* name, int arity, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sCreateRelation'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sCreateRelation(name, arity, moduleName, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

LogicObject* createFunction(const char* name, int arity, Module* module, Environment* environment) {
  // Create a function named `name' with arity `arity'  in the designated 
  // `module'.  Domain and range information can be added via assertions of
  // `nth-domain' (or `domain' and `range') relations.
  // 
  // Note that because names in modules that are not case-sensitive are canonicalized,
  // the name of the returned object may not match `name' exactly.
  if (!(arity > 0)) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "PARSING ERROR: " << "Functions must have arity of at least 1" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_PLI_ERROR);
      }
      throw *newParsingError(stream000->theStringReader());
    }
  }
  { Cons* args = NIL;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        module = oMODULEo;
        { int i = NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = arity - 1;
          Cons* collect000 = NULL;

          for  (; iter000 <= upperBound000; 
                iter000 = iter000 + 1) {
            i = iter000;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(yieldSystemDefinedParameterName(i, module), NIL);
                if (args == NIL) {
                  args = collect000;
                }
                else {
                  addConsToEndOfConsList(args, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(yieldSystemDefinedParameterName(i, module), NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        return (callDeffunction(cons(internStellaName(name), cons(args, NIL))));
      }
    }
  }
}

extern "C" LogicObject* pli_createFunction(const char* name, int arity, Module* module, Environment* environment) {
  // C-callable wrapper for `createFunction'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(createFunction(name, arity, module, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

LogicObject* sCreateFunction(const char* name, int arity, const char* moduleName, Environment* environment) {
  // Create a function named `name' with arity `arity' in the designated 
  // module.  Domain and range information can be added via assertions of
  // `domain', `nth-domain' and `range' relations.
  // 
  // A module name of `null' or the empty string refers to the current module. 
  // If no module can be found with the name `module-name', then a Stella 
  // `no-such-context-exception' is thrown.
  // 
  // Note that because names in modules that are not case-sensitive are canonicalized,
  // the name of the returned object may not match `name' exactly.
  return (createFunction(name, arity, ((Module*)(safelyGetModule(moduleName, environment))), environment));
}

extern "C" LogicObject* pli_sCreateFunction(const char* name, int arity, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sCreateFunction'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sCreateFunction(name, arity, moduleName, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

void registerSpecialistFunction(const char* name, cpp_function_code functionReference, Module* module, Environment* environment) {
  // Register `name' as a function name in `module' which will invoke the
  // native code procedure described by `function-reference.'  The `name'
  // is a fully-qualified name which will be interpreted by the normal
  // rules for reading names in PowerLoom.  The function must conform
  // to the signature for specialist functions.
  // 
  // The exact form of `function-reference' depends on the underlying
  // programming language.  The following type mappings are used:
  //           C++:  
  //   Common Lisp:  FUNCTION   (result of #' or (FUNCTION ...))
  //          Java:  java.lang.reflect.Method
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      logic::registerSpecialistFunction(name, functionReference);
    }
  }
}

extern "C" void pli_registerSpecialistFunction(const char* name, cpp_function_code functionReference, Module* module, Environment* environment) {
  // C-callable wrapper for `registerSpecialistFunction'.
  registerSpecialistFunction(name, functionReference, module, environment);
}

void sRegisterSpecialistFunction(const char* name, const char* nativeName, const char* moduleName, Environment* environment) {
  // Register `name' as a function name in the module named `module-name'.
  // This function will the native code named `native-name'.  The `name'
  // is a fully-qualified name which will be interpreted by the normal
  // rules for reading names in PowerLoom.  The `native-name' will be
  // processed in a manner that depends on the underlying programming
  // language.  The following type mappings are used:
  //           C++:  Not available.  Error signaled.
  //   Common Lisp:  The native-name is read by READ-FROM-STRING and then
  //                 the SYMBOL-FUNCTION is taken.
  //          Java:  A fully package-qualified name is required.  It is
  //                 looked up using the Reflection tools.
  // The function found must conform to the signature for specialist functions.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, NULL);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, NULL);
    { Context* temp000 = safelyGetModule(moduleName, environment);

      oMODULEo = (((boolean)(temp000)) ? ((Module*)(temp000)) : oMODULEo);
    }
    oCONTEXTo = oMODULEo;
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      registerSpecialistFunctionName(name, nativeName);
    }
  }
}

extern "C" void pli_sRegisterSpecialistFunction(const char* name, const char* nativeName, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sRegisterSpecialistFunction'.
  sRegisterSpecialistFunction(name, nativeName, moduleName, environment);
}

void registerComputationFunction(const char* name, cpp_function_code functionReference, int arity, Module* module, Environment* environment) {
  // Register `name' as a function name in `module' which will invoke the
  // native code procedure described by `function-reference.'  The `name'
  // is a fully-qualified name which will be interpreted by the normal
  // rules for reading names in PowerLoom.  The function must conform
  // to the signature for computation functions used by the computation
  // specialist.  Arity specifies the number of arguments the computation
  // accepts.
  // 
  // The exact form of `function-reference' depends on the underlying
  // programming language.  The following type mappings are used:
  //           C++:  cpp_function_code (a pointer to the function code)
  //   Common Lisp:  FUNCTION   (result of #' or (FUNCTION ...))
  //          Java:  java.lang.reflect.Method
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      logic::registerComputationFunction(name, functionReference, arity);
    }
  }
}

extern "C" void pli_registerComputationFunction(const char* name, cpp_function_code functionReference, int arity, Module* module, Environment* environment) {
  // C-callable wrapper for `registerComputationFunction'.
  registerComputationFunction(name, functionReference, arity, module, environment);
}

void sRegisterComputationFunction(const char* name, const char* nativeName, int arity, const char* moduleName, Environment* environment) {
  // Register `name' as a function name in the module named `module-name'.
  // This function will the native code named `native-name'.  The `name'
  // is a fully-qualified name which will be interpreted by the normal
  // rules for reading names in PowerLoom.  The `native-name' will be
  // processed in a manner that depends on the underlying programming
  // language.  The following type mappings are used:
  //           C++:  Not available.  Error signaled.
  //   Common Lisp:  The native-name is read by READ-FROM-STRING and then
  //                 the SYMBOL-FUNCTION is taken.
  //          Java:  A fully package-qualified name is required.  It is
  //                 looked up using the Reflection tools.
  // The function found must conform to the signature for computation functions.
  // Arity specifies the number of arguments the computation accepts.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, NULL);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, NULL);
    { Context* temp000 = safelyGetModule(moduleName, environment);

      oMODULEo = (((boolean)(temp000)) ? ((Module*)(temp000)) : oMODULEo);
    }
    oCONTEXTo = oMODULEo;
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      registerComputationFunctionName(name, nativeName, arity);
    }
  }
}

extern "C" void pli_sRegisterComputationFunction(const char* name, const char* nativeName, int arity, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sRegisterComputationFunction'.
  sRegisterComputationFunction(name, nativeName, arity, moduleName, environment);
}

LogicObject* createEnumeratedList(Cons* members, Module* module, Environment* environment) {
  // Create a logical term that denotes a list containing `members' in
  // `module' using `environment'.  Useful for passing lists as arguments
  // to parameterized queries.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      { List* self000 = newList();

        self000->theConsList = members;
        { Skolem* value000 = createLogicalList(self000);

          return (value000);
        }
      }
    }
  }
}

extern "C" LogicObject* pli_createEnumeratedList(Cons* members, Module* module, Environment* environment) {
  // C-callable wrapper for `createEnumeratedList'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(createEnumeratedList(members, module, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
}

LogicObject* createEnumeratedSet(Cons* members, Module* module, Environment* environment) {
  // Create a logical term that denotes the enumerated set containing `members'
  // in `module' using `environment'.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      { List* self000 = newList();

        self000->theConsList = members;
        { Skolem* value000 = logic::createEnumeratedSet(self000);

          return (value000);
        }
      }
    }
  }
}

extern "C" LogicObject* pli_createEnumeratedSet(Cons* members, Module* module, Environment* environment) {
  // C-callable wrapper for `createEnumeratedSet'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(createEnumeratedSet(members, module, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

void destroyObject(Object* object) {
  // Delete the object `object', retracting all facts attached to it.
  // Should be synchronized on process lock oPOWERLOOM_LOCKo
  {
    logic::destroyObject(object);
  }
}

extern "C" void pli_destroyObject(Object* object) {
  // C-callable wrapper for `destroyObject'.
  try {
    destroyObject(object);
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

void sDestroyObject(const char* objectName, const char* moduleName, Environment* environment) {
  // Delete the object named `object-name', retracting all facts
  // attached to it.
  // 
  // A module name of `null' or the empty string refers to the current module. 
  // If no module can be found with the name `module-name', then a Stella 
  // `no-such-context-exception' is thrown.
  { Context* module = safelyGetModule(moduleName, environment);
    Object* object = safelyGetObject(objectName, ((Module*)(module)), environment);

    if (((boolean)(object))) {
      destroyObject(object);
    }
  }
}

extern "C" void pli_sDestroyObject(const char* objectName, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sDestroyObject'.
  try {
    sDestroyObject(objectName, moduleName, environment);
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

Proposition* assertUnaryProposition(LogicObject* relation, Object* arg, Module* module, Environment* environment) {
  // Assert that the proposition (`relation' `arg') is TRUE in `module'.  Return the asserted proposition.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      if (classP(relation)) {
        return (assertIsaProposition(arg, relation->surrogateValueInverse));
      }
      else {
        return (assertProperty(((LogicObject*)(arg)), relation->surrogateValueInverse));
      }
    }
  }
}

extern "C" Proposition* pli_assertUnaryProposition(LogicObject* relation, Object* arg, Module* module, Environment* environment) {
  // C-callable wrapper for `assertUnaryProposition'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(assertUnaryProposition(relation, arg, module, environment)));
    return (((Proposition*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Proposition* assertBinaryProposition(LogicObject* relation, Object* arg, Object* value, Module* module, Environment* environment) {
  // Assert that the proposition (`relation' `arg' `value') is TRUE
  // in `module'.  Return the asserted proposition.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (assertBinaryValue(relation->surrogateValueInverse, arg, value));
    }
  }
}

extern "C" Proposition* pli_assertBinaryProposition(LogicObject* relation, Object* arg, Object* value, Module* module, Environment* environment) {
  // C-callable wrapper for `assertBinaryProposition'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(assertBinaryProposition(relation, arg, value, module, environment)));
    return (((Proposition*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Proposition* assertNaryProposition(Object* relationAndArguments, Module* module, Environment* environment) {
  // Assert that the proposition represented by the list ` relation-and-arguments' satisfies
  // the relation `relation'.
  { Cons* list = sequenceToConsList(relationAndArguments);
    NamedDescription* relation = ((NamedDescription*)(list->value));
    Surrogate* relationsurrogate = relation->surrogateValueInverse;
    Cons* arguments = list->rest;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        return (assertTuple(relationsurrogate, arguments));
      }
    }
  }
}

extern "C" Proposition* pli_assertNaryProposition(Object* relationAndArguments, Module* module, Environment* environment) {
  // C-callable wrapper for `assertNaryProposition'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(assertNaryProposition(relationAndArguments, module, environment)));
    return (((Proposition*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Proposition* retractUnaryProposition(LogicObject* relation, Object* arg, Module* module, Environment* environment) {
  // Retract that the proposition (`relation' `arg') is TRUE in `module'.  Return the asserted proposition.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      if (classP(relation)) {
        return (retractIsaProposition(arg, relation->surrogateValueInverse));
      }
      else {
        return (retractProperty(((LogicObject*)(arg)), relation->surrogateValueInverse));
      }
    }
  }
}

extern "C" Proposition* pli_retractUnaryProposition(LogicObject* relation, Object* arg, Module* module, Environment* environment) {
  // C-callable wrapper for `retractUnaryProposition'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(retractUnaryProposition(relation, arg, module, environment)));
    return (((Proposition*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Proposition* retractBinaryProposition(LogicObject* relation, Object* arg, Object* value, Module* module, Environment* environment) {
  // Retract that the proposition (`relation' `arg' `value') is TRUE
  // in `module'.  Return the asserted proposition.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      return (retractBinaryValue(relation->surrogateValueInverse, arg, value));
    }
  }
}

extern "C" Proposition* pli_retractBinaryProposition(LogicObject* relation, Object* arg, Object* value, Module* module, Environment* environment) {
  // C-callable wrapper for `retractBinaryProposition'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(retractBinaryProposition(relation, arg, value, module, environment)));
    return (((Proposition*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Proposition* retractNaryProposition(Object* relationAndArguments, Module* module, Environment* environment) {
  // Retract the proposition that `arguments' satisfies
  // the relation `relation'.
  { Cons* list = sequenceToConsList(relationAndArguments);
    NamedDescription* relation = ((NamedDescription*)(list->value));
    Surrogate* relationsurrogate = relation->surrogateValueInverse;
    Cons* arguments = list->rest;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        return (updateTuple(relationsurrogate, arguments, KWD_PLI_RETRACT_TRUE));
      }
    }
  }
}

extern "C" Proposition* pli_retractNaryProposition(Object* relationAndArguments, Module* module, Environment* environment) {
  // C-callable wrapper for `retractNaryProposition'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(retractNaryProposition(relationAndArguments, module, environment)));
    return (((Proposition*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Proposition* assertProposition(Proposition* proposition, Module* module, Environment* environment) {
  // Assert that the proposition `proposition' is true in `module'.
  // Return the asserted proposition.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      helpUpdateTopLevelProposition(proposition, KWD_PLI_ASSERT_TRUE);
      return (proposition);
    }
  }
}

extern "C" Proposition* pli_assertProposition(Proposition* proposition, Module* module, Environment* environment) {
  // C-callable wrapper for `assertProposition'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(assertProposition(proposition, module, environment)));
    return (((Proposition*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* sAssertProposition(const char* sentence, const char* moduleName, Environment* environment) {
  // Assert that the logical sentence `sentence' is true in the module
  // named `module-name'.  A module name of `null' or the empty string refers to the
  // current module.  If no module can be found with the name `module-name',
  // then a Stella `no-such-context-exception' is thrown.
  // 
  // Return an iterator of the propositions resulting from sentence.
  { Context* module = safelyGetModule(moduleName, environment);
    PlIterator* propositions = NULL;
    PlIterator* returnValue = NULL;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? ((Module*)(module)) : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        propositions = sConceive(sentence, moduleName, environment);
        returnValue = consToPlIterator(propositions->cursor);
        { Proposition* proposition = NULL;
          PlIterator* iter000 = propositions;

          for (; iter000->nextP(); ) {
            proposition = ((Proposition*)(iter000->value));
            helpUpdateTopLevelProposition(proposition, KWD_PLI_ASSERT_TRUE);
          }
        }
        return (returnValue);
      }
    }
  }
}

extern "C" PlIterator* pli_sAssertProposition(const char* sentence, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sAssertProposition'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sAssertProposition(sentence, moduleName, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Proposition* retractProposition(Proposition* proposition, Module* module, Environment* environment) {
  // Retract the truth of the proposition `proposition' in `module'.
  // Return the retracted proposition.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      helpUpdateTopLevelProposition(proposition, KWD_PLI_RETRACT_TRUE);
      return (proposition);
    }
  }
}

extern "C" Proposition* pli_retractProposition(Proposition* proposition, Module* module, Environment* environment) {
  // C-callable wrapper for `retractProposition'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(retractProposition(proposition, module, environment)));
    return (((Proposition*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* sRetractProposition(const char* sentence, const char* moduleName, Environment* environment) {
  // Retract the truth of the logical sentence `sentence' in the module named
  // `module-name'.  A module name of `null' or the empty string refers to the
  // current module.  If no module can be found with the name `module-name',
  // then a Stella `no-such-context-exception' is thrown.
  // 
  // Return an iterator of the retracted propositions resulting from sentence.
  { Context* module = safelyGetModule(moduleName, environment);
    PlIterator* propositions = NULL;
    PlIterator* returnValue = NULL;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? ((Module*)(module)) : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        propositions = sConceive(sentence, moduleName, environment);
        returnValue = consToPlIterator(propositions->cursor);
        { Proposition* proposition = NULL;
          PlIterator* iter000 = propositions;

          for (; iter000->nextP(); ) {
            proposition = ((Proposition*)(iter000->value));
            helpUpdateTopLevelProposition(proposition, KWD_PLI_RETRACT_TRUE);
          }
        }
        return (returnValue);
      }
    }
  }
}

extern "C" PlIterator* pli_sRetractProposition(const char* sentence, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sRetractProposition'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sRetractProposition(sentence, moduleName, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* conceive(Object* sentence, Module* module, Environment* environment) {
  // Create one or more proposition objects from the sentence `sentence'
  // in the  module `module'.  Return an iterator of the propositions.
  // If any of the new propositions has the same structure as an already existing
  // proposition, an automatic check for duplicates will return the pre-existing
  // proposition.  Multiple propositions may be returned for a single sentence
  // because of normalization of equivalences, conjunctions, etc.
  // 
  // Signals a `Proposition-Error' if PowerLoom could not conceive `sentence'.
  if (!((boolean)(sentence))) {
    return (NULL);
  }
  else {
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        { Object* propositions = conceiveFormula(sentence);

          if (!((boolean)(propositions))) {
            { OutputStringStream* stream000 = newOutputStringStream();

              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                *(stream000->nativeStream) << "ERROR: " << "Failed to conceive " << "`" << sentence << "'" << "." << std::endl;
                helpSignalPropositionError(stream000, KWD_PLI_ERROR);
              }
              throw *newPropositionError(stream000->theStringReader());
            }
          }
          { Surrogate* testValue000 = safePrimaryType(propositions);

            if (subtypeOfP(testValue000, SGT_PLI_LOGIC_PROPOSITION)) {
              { Object* propositions000 = propositions;
                Proposition* propositions = ((Proposition*)(propositions000));

                return (consToPlIterator(cons(propositions, NIL)));
              }
            }
            else if (testValue000 == SGT_PLI_STELLA_CONS) {
              { Object* propositions001 = propositions;
                Cons* propositions = ((Cons*)(propositions001));

                return (consToPlIterator(propositions));
              }
            }
            else {
              { OutputStringStream* stream001 = newOutputStringStream();

                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  *(stream001->nativeStream) << "ERROR: " << "Formula is not a sentence: " << "`" << sentence << "'" << "." << std::endl;
                  helpSignalPropositionError(stream001, KWD_PLI_ERROR);
                }
                throw *newPropositionError(stream001->theStringReader());
              }
            }
          }
        }
      }
    }
  }
}

extern "C" PlIterator* pli_conceive(Object* sentence, Module* module, Environment* environment) {
  // C-callable wrapper for `conceive'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(conceive(sentence, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* sConceive(const char* sentence, const char* moduleName, Environment* environment) {
  // Create one or more proposition objects from the sentence `sentence'
  // in the  module named `module-name'.  Return an iterator of the propositions.
  // If any of the new propositions has the same structure as an already existing
  // proposition, an automatic check for duplicates will return the pre-existing
  // proposition.  Multiple propositions may be returned for a single sentence
  // because of normalization of equivalences, conjunctions, etc.
  // 
  // A module name of `null' or the empty string refers to the current module.
  // If no module can be found with the name `module-name', then a Stella
  // `No-Such-Context-Exception' is thrown.
  // 
  // Signals a `Proposition-Error' if PowerLoom could not conceive `sentence'.
  { Context* module = safelyGetModule(moduleName, environment);

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? ((Module*)(module)) : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        module = oMODULEo;
        return (conceive(readSExpressionFromString(sentence), ((Module*)(module)), environment));
      }
    }
  }
}

extern "C" PlIterator* pli_sConceive(const char* sentence, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sConceive'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sConceive(sentence, moduleName, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* getRules(LogicObject* relation, Module* module, Environment* environment) {
  // Return rules attached to the concept/relation `relation'
  // in either antecedent or consequent position.
  if (!((boolean)(relation))) {
    return (EMPTY_PL_ITERATOR);
  }
  else {
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        return (consToPlIterator(callGetRules(relation)));
      }
    }
  }
}

extern "C" PlIterator* pli_getRules(LogicObject* relation, Module* module, Environment* environment) {
  // C-callable wrapper for `getRules'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getRules(relation, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

PlIterator* sGetRules(const char* relationName, const char* moduleName, Environment* environment) {
  // Return rules attached to the concept/relation named
  // `relation-name' found in the module named `module-name'.
  // A module name of `null' or the empty string refers to the current module.
  // If no module can be found with the name `module-name', then a Stella
  // `No-Such-Context-Exception' is thrown.
  { Context* module = safelyGetModule(moduleName, environment);
    Object* relation = safelyGetRelation(relationName, ((Module*)(module)), environment);

    return (getRules(((LogicObject*)(relation)), ((Module*)(module)), environment));
  }
}

extern "C" PlIterator* pli_sGetRules(const char* relationName, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetRules'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sGetRules(relationName, moduleName, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

void sPrintRules(const char* name, OutputStream* stream, const char* moduleName, Environment* environment) {
  // Print rules attached to the concept/relation named `name'.
  // A module name of `null' or the empty string refers to the
  // current module.  If no module can be found with the name `module-name',
  // then a Stella `no-such-context-exception' is thrown.
  if (!((boolean)(stream))) {
    stream = STANDARD_OUTPUT;
  }
  { Proposition* rule = NULL;
    PlIterator* iter000 = sGetRules(name, moduleName, environment);

    for (; iter000->nextP(); ) {
      rule = ((Proposition*)(iter000->value));
      printLogicalForm(rule, stream);
      *(stream->nativeStream) << std::endl << std::endl;
    }
  }
}

extern "C" void pli_sPrintRules(const char* name, OutputStream* stream, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sPrintRules'.
  try {
    sPrintRules(name, stream, moduleName, environment);
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

void runForwardRules(Object* module, boolean localP, boolean forceP) {
  // Run forward inference rules in module `module' which defaults
  // to the current module.  See `run-forward-rules' command for more information.
  if (!((boolean)(module))) {
    module = oMODULEo;
  }
  if (((boolean)(module))) {
    callRunForwardRules(((Context*)(module)), localP, forceP);
  }
}

extern "C" void pli_runForwardRules(Object* module, int localP, int forceP) {
  // C-callable wrapper for `runForwardRules'.
  try {
    runForwardRules(module, localP, forceP);
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

int getArity(LogicObject* relation) {
  // Return the arity of the relation `relation'.
  if (subtypeOfP(safePrimaryType(relation), SGT_PLI_LOGIC_DESCRIPTION)) {
    { LogicObject* relation000 = relation;
      Description* relation = ((Description*)(relation000));

      return (relation->arity());
    }
  }
  else {
    return (0);
  }
}

extern "C" int pli_getArity(LogicObject* relation) {
  // C-callable wrapper for `getArity'.
  return (getArity(relation));
}

int sGetArity(const char* relationName, const char* moduleName, Environment* environment) {
  // Return the arity of the relation named `relation-name'.
  // 
  //  A module name of `null' or the empty string refers to the
  // current module.  If no module can be found with the name `module-name',
  // then a Stella `no-such-context-exception' is thrown.
  { Context* module = safelyGetModule(moduleName, environment);
    Object* relation = safelyGetRelation(relationName, ((Module*)(module)), environment);

    if (((boolean)(relation))) {
      return (getArity(((LogicObject*)(relation))));
    }
    else {
      return (NULL_INTEGER);
    }
  }
}

extern "C" int pli_sGetArity(const char* relationName, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetArity'.
  return (sGetArity(relationName, moduleName, environment));
}

LogicObject* getDomain(LogicObject* relation) {
  // Return the type (a concept) for the first argument to the binary
  // relation `relation'.
  if (subtypeOfP(safePrimaryType(relation), SGT_PLI_LOGIC_NAMED_DESCRIPTION)) {
    { LogicObject* relation000 = relation;
      NamedDescription* relation = ((NamedDescription*)(relation000));

      return (getNthDomain(relation, 0));
    }
  }
  else {
    return (NULL);
  }
}

extern "C" LogicObject* pli_getDomain(LogicObject* relation) {
  // C-callable wrapper for `getDomain'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getDomain(relation)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
}

LogicObject* sGetDomain(const char* relationName, const char* moduleName, Environment* environment) {
  // Return the type (concept) for the first argument to the binary
  // relation `relation-name'.
  // 
  // A module name of `null' or the empty string refers to the
  // current module.  If no module can be found with the name `module-name',
  // then a Stella `no-such-context-exception' is thrown.
  { Context* module = safelyGetModule(moduleName, environment);
    Object* relation = safelyGetRelation(relationName, ((Module*)(module)), environment);

    if (((boolean)(relation))) {
      return (getDomain(((LogicObject*)(relation))));
    }
    else {
      return (NULL);
    }
  }
}

extern "C" LogicObject* pli_sGetDomain(const char* relationName, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetDomain'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(sGetDomain(relationName, moduleName, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
}

LogicObject* getRange(LogicObject* relation) {
  // Return the type (a concept) for fillers of the binary relation
  // `relation'.
  if (subtypeOfP(safePrimaryType(relation), SGT_PLI_LOGIC_NAMED_DESCRIPTION)) {
    { LogicObject* relation000 = relation;
      NamedDescription* relation = ((NamedDescription*)(relation000));

      return (getNthDomain(relation, 1));
    }
  }
  else {
    return (NULL);
  }
}

extern "C" LogicObject* pli_getRange(LogicObject* relation) {
  // C-callable wrapper for `getRange'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getRange(relation)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
}

LogicObject* sGetRange(const char* relationName, const char* moduleName, Environment* environment) {
  // Return the type (a concept) for fillers of the binary relation
  // `relation-name'.
  // 
  // A module name of `null' or the empty string refers to the
  // current module.  If no module can be found with the name `module-name',
  // then a Stella `no-such-context-exception' is thrown.
  { Context* module = safelyGetModule(moduleName, environment);
    Object* relation = safelyGetRelation(relationName, ((Module*)(module)), environment);

    if (((boolean)(relation))) {
      return (getRange(((LogicObject*)(relation))));
    }
    else {
      return (NULL);
    }
  }
}

extern "C" LogicObject* pli_sGetRange(const char* relationName, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetRange'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(sGetRange(relationName, moduleName, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
}

LogicObject* getNthDomain(LogicObject* relation, int n) {
  // Return the type (a concept) for the the nth argument of the
  // relation `relation'.  Counting starts at zero.  NOTE: if there are multiple
  // `nth-domain' propositions for `relation', this arbitrarily returns one of them;
  // it does not look for the most specific one (which might have to be created).
  if (classP(relation)) {
    return (((n == 0) ? relation : NULL));
  }
  if (subtypeOfP(safePrimaryType(relation), SGT_PLI_LOGIC_NAMED_DESCRIPTION)) {
    { LogicObject* relation000 = relation;
      NamedDescription* relation = ((NamedDescription*)(relation000));

      if ((n >= 0) &&
          (n < relation->ioVariableTypes->length())) {
        { Proposition* domainprop = ((Proposition*)(helpGetPropositions(((LogicObject*)(SGT_PLI_PL_KERNEL_KB_NTH_DOMAIN->surrogateValue)), cons(relation, cons(wrapInteger(n), cons(NULL, NIL))), 1, NULL, NULL)->value));

          if (((boolean)(domainprop))) {
            return (((LogicObject*)((domainprop->arguments->theArray)[(domainprop->arguments->length() - 1)])));
          }
        }
      }
    }
  }
  else {
  }
  return (NULL);
}

extern "C" LogicObject* pli_getNthDomain(LogicObject* relation, int n) {
  // C-callable wrapper for `getNthDomain'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getNthDomain(relation, n)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
}

LogicObject* sGetNthDomain(const char* relationName, int n, const char* moduleName, Environment* environment) {
  // Return the type (a concept) for the nth argument of the relation
  // named `relation-name'.  Counting starts at zero.
  // 
  // A module name of `null' or the empty string refers to the
  // current module.  If no module can be found with the name `module-name',
  // then a Stella `no-such-context-exception' is thrown.
  { Context* module = safelyGetModule(moduleName, environment);
    Object* relation = safelyGetRelation(relationName, ((Module*)(module)), environment);

    if (((boolean)(relation))) {
      return (getNthDomain(((LogicObject*)(relation)), n));
    }
    else {
      return (NULL);
    }
  }
}

extern "C" LogicObject* pli_sGetNthDomain(const char* relationName, int n, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sGetNthDomain'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(sGetNthDomain(relationName, n, moduleName, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
}

void load(const char* filename, Environment* environment) {
  // Read logic commands from the file named `filename' and evaluate them.
  // See `load' command help for more information.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(oMODULEo)) ? oMODULEo : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      logic::load(filename, NIL);
    }
  }
}

extern "C" void pli_load(const char* filename, Environment* environment) {
  // C-callable wrapper for `load'.
  try {
    load(filename, environment);
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

void loadInModule(const char* filename, Module* module, Environment* environment) {
  // Read logic commands from the file named `filename' and evaluate them.
  // Binds the `load' command's :module option to `module'.  See `load' command help for more information.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      module = oMODULEo;
      logic::load(filename, consList(2, KWD_PLI_MODULE, module));
    }
  }
}

extern "C" void pli_loadInModule(const char* filename, Module* module, Environment* environment) {
  // C-callable wrapper for `loadInModule'.
  try {
    loadInModule(filename, module, environment);
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

void loadStream(InputStream* stream, Environment* environment) {
  // Read logic commands from the STELLA stream `stream' and evaluate them.
  // See `load' command help for more information.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(oMODULEo)) ? oMODULEo : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      logic::loadStream(stream, 0);
    }
  }
}

extern "C" void pli_loadStream(InputStream* stream, Environment* environment) {
  // C-callable wrapper for `loadStream'.
  try {
    loadStream(stream, environment);
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

void loadStreamInModule(InputStream* stream, Module* module, Environment* environment) {
  // Read logic commands from the STELLA stream `stream' and evaluate them.
  // Binds the `load' command's :module option to `module'.  See `load' command help for more information.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      module = oMODULEo;
      logic::loadStream(stream, 2, KWD_PLI_MODULE, module);
    }
  }
}

extern "C" void pli_loadStreamInModule(InputStream* stream, Module* module, Environment* environment) {
  // C-callable wrapper for `loadStreamInModule'.
  try {
    loadStreamInModule(stream, module, environment);
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

void loadNativeStream(std::istream* stream, Environment* environment) {
  // Read logic commands from the native input stream `stream' and evaluate them.
  // Assumes `stream' is a line-buffered stream which is a safe compromise but does
  // not generate the best efficiency for block-buffered streams such as files.
  // See `load' command help for more information.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(oMODULEo)) ? oMODULEo : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      { InputStream* self000 = newInputStream();

        self000->nativeStream = stream;
        logic::loadStream(self000, 0);
      }
    }
  }
}

extern "C" void pli_loadNativeStream(std::istream* stream, Environment* environment) {
  // C-callable wrapper for `loadNativeStream'.
  try {
    loadNativeStream(stream, environment);
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

void loadNativeStreamInModule(std::istream* stream, Module* module, Environment* environment) {
  // Read logic commands from the native input stream `stream' and evaluate them.
  // Assumes `stream' is a line-buffered stream which is a safe compromise but does
  // not generate the best efficiency for block-buffered streams such as files.
  // Binds the `load' command's :module option to `module'.  See `load' command help for more information.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      module = oMODULEo;
      { InputStream* self000 = newInputStream();

        self000->nativeStream = stream;
        logic::loadStream(self000, 2, KWD_PLI_MODULE, module);
      }
    }
  }
}

extern "C" void pli_loadNativeStreamInModule(std::istream* stream, Module* module, Environment* environment) {
  // C-callable wrapper for `loadNativeStreamInModule'.
  try {
    loadNativeStreamInModule(stream, module, environment);
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

void saveModule(Module* module, const char* filename, const char* ifexists, Environment* environment) {
  // Save the contents of the module `mod' into a file named `filename'.
  // If a file named `filename' already exists, then the action taken depends on the
  // value of `ifexists'.  Possible values are "ASK", "REPLACE", "WARN" and "ERROR":
  // 
  //   REPLACE => Means overwrite without warning.
  //   WARN    => Means overwrite with a warning.
  //   ERROR   => Means don't overwrite, signal an error instead.
  //   ASK     => Ask the user whether to overwrite or not.  If not overwritten, an 
  //              exception is thrown.
  { boolean existsP = probeFileP(filename);

    if ((!existsP) ||
        stringEqualP(ifexists, "REPLACE")) {
    }
    else if (stringEqualP(ifexists, "ASK")) {
      if (!(yesOrNoP(stringConcatenate("File `", filename, 1, "' already exists.  Overwrite it? (yes or no) ")))) {
        ensureFileDoesNotExist(filename, "save-module");
      }
    }
    else if (stringEqualP(ifexists, "WARN")) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "File " << "`" << filename << "'" << " already exists, overwriting." << std::endl;
    }
    else if (stringEqualP(ifexists, "ERROR")) {
      ensureFileDoesNotExist(filename, "save-module");
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Unrecognized ifexists option " << "`" << ifexists << "'";
        throw *newBadArgumentException(stream000->theStringReader());
      }
    }
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        module = oMODULEo;
        { OutputFileStream* stream = NULL;

          try {
            stream = openOutputFile(filename, 0);
            doSaveModule(module, stream);
          }
catch (...) {
            if (((boolean)(stream))) {
              stream->free();
            }
            throw;
          }
          if (((boolean)(stream))) {
            stream->free();
          }
        }
      }
    }
  }
}

extern "C" void pli_saveModule(Module* module, const char* filename, const char* ifexists, Environment* environment) {
  // C-callable wrapper for `saveModule'.
  try {
    saveModule(module, filename, ifexists, environment);
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

void sSaveModule(const char* moduleName, const char* filename, const char* ifexists, Environment* environment) {
  // Save the contents of the module `module-name' into a file named `filename'.
  // If a file named `filename' already exists, then the action taken depends on the
  // value of `ifexists'.  Possible values are "ASK", "REPLACE", "WARN" and "ERROR":
  // 
  //   REPLACE => Means overwrite without warning.
  //   WARN    => Means overwrite with a warning.
  //   ERROR   => Means don't overwrite, signal an error instead.
  //   ASK     => Ask the user whether to overwrite or not.  If not overwritten, an
  //              exception is thrown.
  // 
  // A module name of `null' or the empty string refers to the
  // current module.  If no module can be found with the name `module-name',
  // then a Stella `no-such-context-exception' is thrown.
  saveModule(((Module*)(safelyGetModule(moduleName, environment))), filename, ifexists, environment);
}

extern "C" void pli_sSaveModule(const char* moduleName, const char* filename, const char* ifexists, Environment* environment) {
  // C-callable wrapper for `sSaveModule'.
  try {
    sSaveModule(moduleName, filename, ifexists, environment);
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

LogicObject* getPredicate(Proposition* prop) {
  // Return the concept or relation predicate for
  // the proposition `prop'.
  { LogicObject* relation = getDescription(((Surrogate*)(prop->operatoR)));

    if (!((boolean)(relation))) {
      relation = ((LogicObject*)(((Surrogate*)(prop->operatoR))->surrogateValue));
    }
    return (relation);
  }
}

extern "C" LogicObject* pli_getPredicate(Proposition* prop) {
  // C-callable wrapper for `getPredicate'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getPredicate(prop)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
}

int getColumnCount(Object* obj) {
  // Return the number of columns in `obj', which must
  // be of type proposition, skolem, cons, vector or PL-iterator.  For a proposition,
  // the number includes both the predicate and arguments. For the PL-iterator
  // case,the number of columns is for the current value of the iterator. For the
  // skolem case, if the skolem is a function term, the column count of its defining
  // proposition will be returned, otherwise it is treated as a non-sequence object.
  // 
  // For a null item, the column count is zero.
  // For non sequence objects, the column count is one.
  if (!((boolean)(obj))) {
    return (0);
  }
  { Surrogate* testValue000 = safePrimaryType(obj);

    if (subtypeOfP(testValue000, SGT_PLI_LOGIC_PROPOSITION)) {
      { Object* obj000 = obj;
        Proposition* obj = ((Proposition*)(obj000));

        return (obj->arguments->length() + 1);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PLI_PLI_PL_ITERATOR)) {
      { Object* obj001 = obj;
        PlIterator* obj = ((PlIterator*)(obj001));

        return (getColumnCount(obj->value));
      }
    }
    else if (testValue000 == SGT_PLI_STELLA_CONS) {
      { Object* obj002 = obj;
        Cons* obj = ((Cons*)(obj002));

        return (obj->length());
      }
    }
    else if (subtypeOfP(testValue000, SGT_PLI_STELLA_VECTOR)) {
      { Object* obj003 = obj;
        Vector* obj = ((Vector*)(obj003));

        return (obj->length());
      }
    }
    else if (subtypeOfP(testValue000, SGT_PLI_LOGIC_SKOLEM)) {
      { Object* obj004 = obj;
        Skolem* obj = ((Skolem*)(obj004));

        if (functionOutputSkolemP(obj)) {
          return (getColumnCount(obj->definingProposition));
        }
        else {
          return (1);
        }
      }
    }
    else {
      return (1);
    }
  }
}

extern "C" int pli_getColumnCount(Object* obj) {
  // C-callable wrapper for `getColumnCount'.
  return (getColumnCount(obj));
}

Object* getNthValue(Object* sequence, int n, Module* module, Environment* environment) {
  // Return the value in the `nth' column of `sequence'.
  // Counting starts at zero.  Unless `n' is zero, `sequence' must be of type
  // proposition, skolem, cons, vector or PL-iterator.  A zero column number returns
  // a proposition's relational predicate.  For the PL-iterator case, the number
  // of columns is for the current value of the iterator.   For the skolem case,
  // if the skolem is a function term, the nth value of its defining proposition
  // will be returned, otherwise it is treated as a non-sequence object.
  // 
  // As a special case, a column number of zero will also return `sequence' itself
  // if it is not one of the types enumerated above.  This is done to allow the
  // use of `get-nth-value' on PL-iterators with only a single return variable.
  if ((n >= getColumnCount(sequence)) ||
      (n < 0)) {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Column index " << "`" << n << "'" << " is out of range for " << "`" << sequence << "'";
      throw *newLogicException(stream000->theStringReader());
    }
  }
  { Surrogate* testValue000 = safePrimaryType(sequence);

    if (subtypeOfP(testValue000, SGT_PLI_LOGIC_PROPOSITION)) {
      { Object* sequence000 = sequence;
        Proposition* sequence = ((Proposition*)(sequence000));

        if (n == 0) {
          return (getPredicate(sequence));
        }
        else {
          { Object* value = (sequence->arguments->theArray)[(n - 1)];

            if (subtypeOfP(safePrimaryType(value), SGT_PLI_LOGIC_SKOLEM)) {
              { Object* value000 = value;
                Skolem* value = ((Skolem*)(value000));

                { 
                  BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
                  BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
                  environment = environment;
                  // Should be synchronized on process lock oPOWERLOOM_LOCKo
                  {
                    return (valueOf(value));
                  }
                }
              }
            }
            else {
              return (value);
            }
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PLI_PLI_PL_ITERATOR)) {
      { Object* sequence001 = sequence;
        PlIterator* sequence = ((PlIterator*)(sequence001));

        return (getNthValue(sequence->value, n, module, environment));
      }
    }
    else if (testValue000 == SGT_PLI_STELLA_CONS) {
      { Object* sequence002 = sequence;
        Cons* sequence = ((Cons*)(sequence002));

        return (sequence->nth(n));
      }
    }
    else if (subtypeOfP(testValue000, SGT_PLI_STELLA_VECTOR)) {
      { Object* sequence003 = sequence;
        Vector* sequence = ((Vector*)(sequence003));

        return ((sequence->theArray)[n]);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PLI_LOGIC_SKOLEM)) {
      { Object* sequence004 = sequence;
        Skolem* sequence = ((Skolem*)(sequence004));

        if (functionOutputSkolemP(sequence)) {
          return (getNthValue(sequence->definingProposition, n, module, environment));
        }
        else {
          return (sequence);
        }
      }
    }
    else {
      return (sequence);
    }
  }
}

extern "C" Object* pli_getNthValue(Object* sequence, int n, Module* module, Environment* environment) {
  // C-callable wrapper for `getNthValue'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getNthValue(sequence, n, module, environment)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

const char* getNthString(Object* sequence, int n, Module* module, Environment* environment) {
  // Return a string representation of the value in the `nth' column of
  // `sequence'. Counting starts at zero.   Unless `n' is zero, `sequence' must be of type
  // proposition, cons, vector or PL-iterator.  A zero column number returns
  // a proposition's relational predicate.  For the PL-iterator case, the
  // the current value pointed to by the iterator is used.  This will always
  // succeed, even if the `nth' value is not a string object.  In that case, a
  // string reprensentation will be returned.
  // 
  // As a special case, a column number of zero will also return `sequence' itself
  // as a string if it is not one of the types enumerated above.  This is done to 
  // allow the use of `get-nth-string' on PL-iterators with only a single return variable.
  return (objectToString(getNthValue(sequence, n, module, environment)));
}

extern "C" const char* pli_getNthString(Object* sequence, int n, Module* module, Environment* environment) {
  // C-callable wrapper for `getNthString'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getNthString(sequence, n, module, environment)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

int getNthInteger(Object* sequence, int n, Module* module, Environment* environment) {
  // Return an integer representation of the value in the `nth' column of
  // `sequence'. Counting starts at zero.   Unless `n' is zero, `sequence' must be of type
  // proposition, cons, vector or PL-iterator.  A zero column number returns
  // a proposition's relational predicate.  For the PL-iterator case, the
  // the current value pointed to by the iterator is used.  If this is not
  // an integer value, then an exception will be thrown.
  // 
  // As a special case, a column number of zero will also return the integer
  // value of `sequence' itself if it is not one of the types enumerated
  // above.   This allows the use of `get-nth-integer' on PL-iterators with
  // only a single return variable.  If  `sequence' cannot be turned into an
  // integer, an exception will be thrown.
  return (objectToInteger(getNthValue(sequence, n, module, environment)));
}

extern "C" int pli_getNthInteger(Object* sequence, int n, Module* module, Environment* environment) {
  // C-callable wrapper for `getNthInteger'.
  try {
    return (getNthInteger(sequence, n, module, environment));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL_INTEGER);
  }
}

double getNthFloat(Object* sequence, int n, Module* module, Environment* environment) {
  // Return the floating point value in the `nth' column of
  // `sequence'. Counting starts at zero.  `sequence' must be of type
  // proposition, cons, vector or PL-iterator.  A zero column number returns
  // a proposition's relational predicate.  For the PL-iterator case, the
  // the current value pointed to by the iterator is used.  If this is not
  // a floating point value, then an exception will be thrown.
  // 
  // As a special case, a column number of zero will also return the floating
  // point value of `sequence' itself if it is not one of the types enumerated
  // above.  This allows the use of `get-nth-float' on PL-iterators with only
  // a single return variable.    If  `sequence' cannot be turned into a floating
  // point value, an exception will be thrown.
  return (objectToFloat(getNthValue(sequence, n, module, environment)));
}

extern "C" double pli_getNthFloat(Object* sequence, int n, Module* module, Environment* environment) {
  // C-callable wrapper for `getNthFloat'.
  try {
    return (getNthFloat(sequence, n, module, environment));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL_FLOAT);
  }
}

LogicObject* getNthLogicObject(Object* sequence, int n, Module* module, Environment* environment) {
  // Return a logic object representation of the value in the `nth' column
  // of `sequence'.  Counting starts at zero.   Unless `n' is zero, `sequence' must be of type
  // proposition, cons, vector or PL-iterator.  A zero column number returns
  // a proposition's relational predicate.  For the PL-iterator case, the
  // the current value pointed to by the iterator is used.  A zero column number
  // returns the proposition's relational predicate.  If the return value is
  // not a LOGIC-OBJECT, an exception is thrown.
  // 
  // As a special case, a column number of zero will also return `sequence' itself
  // if it is not one of the types enumerated above.  This is done to allow the
  // use of `get-nth-value' on PL-iterators with only a single return variable.
  // If `sequence' is not a LOGIC-OBJECT, an exception is thrown.
  { Object* value = getNthValue(sequence, n, module, environment);

    if (isaP(value, SGT_PLI_LOGIC_LOGIC_OBJECT)) {
      return (((LogicObject*)(value)));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't coerce " << "`" << value << "'" << " to a LOGIC-OBJECT.";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

extern "C" LogicObject* pli_getNthLogicObject(Object* sequence, int n, Module* module, Environment* environment) {
  // C-callable wrapper for `getNthLogicObject'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getNthLogicObject(sequence, n, module, environment)));
    return (((LogicObject*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Cons* getEnumeratedCollectionMembers(Object* collection, Module* module, Environment* environment) {
  // Returns the members of an enumerated collection.  This works on all types
  // of collection, i.e., sets and lists
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      { List* members = assertedCollectionMembers(collection, true);

        if (((boolean)(members))) {
          return (members->theConsList);
        }
        else {
          return (NULL);
        }
      }
    }
  }
}

extern "C" Cons* pli_getEnumeratedCollectionMembers(Object* collection, Module* module, Environment* environment) {
  // C-callable wrapper for `getEnumeratedCollectionMembers'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getEnumeratedCollectionMembers(collection, module, environment)));
    return (((Cons*)(oC_API_RESULT_BUFFERo)));
  }
}

Object* evaluate(Object* command, Module* module, Environment* environment) {
  // Evaluate the command `command' within `module' and return
  // the result. Currently, only the evaluation of (possibly nested) commands and
  // global variables is supported.  Commands are simple to program in Common Lisp,
  // since they are built into the language, and relatively awkward in Java and C++.
  // Users of either of those languages are more likely to want to call `s-evaluate'.
  if (((boolean)(command))) {
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        return (stella::evaluate(command));
      }
    }
  }
  return (NULL);
}

extern "C" Object* pli_evaluate(Object* command, Module* module, Environment* environment) {
  // C-callable wrapper for `evaluate'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(evaluate(command, module, environment)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Object* sEvaluate(const char* command, const char* moduleName, Environment* environment) {
  // Evaluate the command represented by the string `command' within `module' and
  // return the result.  Currently, only the evaluation of (possibly nested) commands and
  // global variables is supported.
  // 
  //  A module name of `null' or the empty string refers to the
  // current module.  If no module can be found with the name `module-name',
  // then a Stella `no-such-context-exception' is thrown.
  { Context* module = safelyGetModule(moduleName, environment);

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? ((Module*)(module)) : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        module = oMODULEo;
        return (evaluate(readSExpressionFromString(command), ((Module*)(module)), environment));
      }
    }
  }
}

extern "C" Object* pli_sEvaluate(const char* command, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sEvaluate'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sEvaluate(command, moduleName, environment)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

void powerloom(Module* module, Environment* environment) {
  // Run the PowerLoom read/eval/print loop.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      logic::powerloom();
    }
  }
}

extern "C" void pli_powerloom(Module* module, Environment* environment) {
  // C-callable wrapper for `powerloom'.
  try {
    powerloom(module, environment);
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

boolean isLogicObject(Object* obj) {
  // Test whether `obj' is of type LOGIC-OBJECT
  return (isaP(obj, SGT_PLI_LOGIC_LOGIC_OBJECT));
}

extern "C" int pli_isLogicObject(Object* obj) {
  // C-callable wrapper for `isLogicObject'.
  return (isLogicObject(obj));
}

boolean isSkolem(Object* obj) {
  // Test whether `obj' is of type SKOLEM (which subsumes pattern variables).
  return (isaP(obj, SGT_PLI_LOGIC_SKOLEM));
}

extern "C" int pli_isSkolem(Object* obj) {
  // C-callable wrapper for `isSkolem'.
  return (isSkolem(obj));
}

boolean isVariable(Object* obj) {
  // Test whether `obj' is of type PATTERN-VARIABLE.
  return (isaP(obj, SGT_PLI_LOGIC_PATTERN_VARIABLE));
}

extern "C" int pli_isVariable(Object* obj) {
  // C-callable wrapper for `isVariable'.
  return (isVariable(obj));
}

boolean isInteger(Object* obj) {
  // Test whether `obj' is of type INTEGER
  return (isaP(obj, SGT_PLI_STELLA_INTEGER_WRAPPER));
}

extern "C" int pli_isInteger(Object* obj) {
  // C-callable wrapper for `isInteger'.
  return (isInteger(obj));
}

boolean isFloat(Object* obj) {
  // Test whether `obj' is of type FLOAT (double)
  return (isaP(obj, SGT_PLI_STELLA_FLOAT_WRAPPER));
}

extern "C" int pli_isFloat(Object* obj) {
  // C-callable wrapper for `isFloat'.
  return (isFloat(obj));
}

boolean isNumber(Object* obj) {
  // Test whether `obj' is of type NUMBER.  This can
  // be either an integer or a floating point number.  One key characteristic
  // is that 'object-to-integer' and `object-to-float' will both work on it.
  return (isaP(obj, SGT_PLI_STELLA_NUMBER_WRAPPER));
}

extern "C" int pli_isNumber(Object* obj) {
  // C-callable wrapper for `isNumber'.
  return (isNumber(obj));
}

boolean isString(Object* obj) {
  // Test whether `obj' is of type STRING
  return (isaP(obj, SGT_PLI_STELLA_STRING_WRAPPER));
}

extern "C" int pli_isString(Object* obj) {
  // C-callable wrapper for `isString'.
  return (isString(obj));
}

boolean isEnumeratedCollection(Object* obj) {
  // Test whether `obj' is an enumerated collection.  This
  // subsumes both sets and lists.
  return (logicalCollectionP(obj));
}

extern "C" int pli_isEnumeratedCollection(Object* obj) {
  // C-callable wrapper for `isEnumeratedCollection'.
  return (isEnumeratedCollection(obj));
}

boolean isEnumeratedSet(Object* obj) {
  // Test whether `obj' is an enumerated set.
  return (enumeratedSetP(obj));
}

extern "C" int pli_isEnumeratedSet(Object* obj) {
  // C-callable wrapper for `isEnumeratedSet'.
  return (isEnumeratedSet(obj));
}

boolean isEnumeratedList(Object* obj) {
  // Test whether `obj' is an enumerated list
  return (enumeratedListP(obj));
}

extern "C" int pli_isEnumeratedList(Object* obj) {
  // C-callable wrapper for `isEnumeratedList'.
  return (isEnumeratedList(obj));
}

boolean isTrue(TruthValue* tv) {
  // Tests whether `tv' is a true truth value.  It can be true
  // either absolutely or by default.
  return ((tv == TRUE_TRUTH_VALUE) ||
      (tv == DEFAULT_TRUE_TRUTH_VALUE));
}

extern "C" int pli_isTrue(TruthValue* tv) {
  // C-callable wrapper for `isTrue'.
  return (isTrue(tv));
}

boolean isFalse(TruthValue* tv) {
  // Tests whether `tv' is a false truth value.  It can be false
  // either absolutely or by default.
  return ((tv == FALSE_TRUTH_VALUE) ||
      (tv == DEFAULT_FALSE_TRUTH_VALUE));
}

extern "C" int pli_isFalse(TruthValue* tv) {
  // C-callable wrapper for `isFalse'.
  return (isFalse(tv));
}

boolean isUnknown(TruthValue* tv) {
  // Tests whether `tv' is an unknown truth value.
  return ((tv == UNKNOWN_TRUTH_VALUE) ||
      (!((boolean)(tv))));
}

extern "C" int pli_isUnknown(TruthValue* tv) {
  // C-callable wrapper for `isUnknown'.
  return (isUnknown(tv));
}

boolean isKnown(TruthValue* tv) {
  // Tests whether `tv' is a known truth value (i.e., true or false).
  return (knownTruthValueP(tv));
}

extern "C" int pli_isKnown(TruthValue* tv) {
  // C-callable wrapper for `isKnown'.
  return (isKnown(tv));
}

boolean isInconsistent(TruthValue* tv) {
  // Tests whether `tv' is an inconsistent truth value.
  return (tv == INCONSISTENT_TRUTH_VALUE);
}

extern "C" int pli_isInconsistent(TruthValue* tv) {
  // C-callable wrapper for `isInconsistent'.
  return (isInconsistent(tv));
}

boolean isStrict(TruthValue* tv) {
  // Tests whether `tv' is a strict (non-default) truth value.
  return ((tv == TRUE_TRUTH_VALUE) ||
      (tv == FALSE_TRUTH_VALUE));
}

extern "C" int pli_isStrict(TruthValue* tv) {
  // C-callable wrapper for `isStrict'.
  return (isStrict(tv));
}

boolean isDefault(TruthValue* tv) {
  // Tests whether `tv' is a default truth value.
  return ((tv == DEFAULT_TRUE_TRUTH_VALUE) ||
      (tv == DEFAULT_FALSE_TRUTH_VALUE));
}

extern "C" int pli_isDefault(TruthValue* tv) {
  // C-callable wrapper for `isDefault'.
  return (isDefault(tv));
}

TruthValue* ask(Cons* query, Module* module, Environment* environment) {
  // Returns a truth value for `query' in `module' and `environment'.
  // `query' has the same syntax as the PowerLoom `ask' command (which see)
  // but with the `ask' operator omitted.  For example, here are some legal
  // `query' arguments:
  // 	 
  //     ((happy Fred))
  //     ((happy Fred) :inference-level :assertion)
  //     ((happy Fred) :inference-level :assertion :timeout 1.0)
  // 	
  // As a convenience, a `query' argument whose first element is a symbol is
  // interpreted as a sentence that is queried without any options.  For example:
  // 	 
  //     (happy Fred)
  // 	
  // is a legal `query' argument.  Note that for a sentence whose relation is a list
  // itself, e.g., `((FruitFn BananaTree) MyBanana)' this shortcut is not available,
  // that is, in that case an extra level of list nesting is always necessary.
  // The returned truth value represents the logical truth of the queried sentence
  // as determined by PowerLoom.  It can be be tested via the functions `is-true',
  // `is-false' and `is-unknown' (which see).
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      query = ((Cons*)(deobjectifyTree(query)));
      if (symbolP(query->value)) {
        query = cons(query, NIL);
      }
      return (callAsk(query));
    }
  }
}

extern "C" TruthValue* pli_ask(Cons* query, Module* module, Environment* environment) {
  // C-callable wrapper for `ask'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(ask(query, module, environment)));
    return (((TruthValue*)(oC_API_RESULT_BUFFERo)));
  }
}

TruthValue* sAsk(const char* query, const char* moduleName, Environment* environment) {
  // Returns a truth value for `query' in module `module-name' and `environment'.
  // `query' has the same syntax as the PowerLoom `ask' command (which see) but
  // with the `ask' operator omitted.  Different from the PLI `ask' function, `s-ask'
  // does not expect a top-level pair of parentheses.  For example, here are some legal
  // `query' arguments:
  // 	 
  //     "(happy Fred)"
  //     "(happy Fred) :inference-level :assertion"
  //     "(happy Fred) :inference-level :assertion :timeout 1.0"
  // 	
  // Names in `query' will be interpreted relative to module `module-name'.
  // A null `module-name' or the empty string refers to the current module.
  // If no module can be found with the name `module-name', then a STELLA
  // `no-such-context-exception' is thrown.
  // The returned truth value represents the logical truth of the queried sentence
  // as determined by PowerLoom.  It can be be tested via the functions `is-true',
  // `is-false' and `is-unknown' (which see).
  { Cons* queryform = NIL;
    Context* module = safelyGetModule(moduleName, environment);

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? ((Module*)(module)) : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        { Object* sexp = NULL;
          SExpressionIterator* iter000 = sExpressions(newInputStringStream(query));
          Cons* collect000 = NULL;

          for  (; iter000->nextP(); ) {
            sexp = iter000->value;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(sexp, NIL);
                if (queryform == NIL) {
                  queryform = collect000;
                }
                else {
                  addConsToEndOfConsList(queryform, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(sexp, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
      }
    }
    return (ask(queryform, ((Module*)(safelyGetModule(moduleName, environment))), environment));
  }
}

extern "C" TruthValue* pli_sAsk(const char* query, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sAsk'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(sAsk(query, moduleName, environment)));
    return (((TruthValue*)(oC_API_RESULT_BUFFERo)));
  }
}

PlIterator* retrieve(Cons* query, Module* module, Environment* environment) {
  // Returns an iterator of variable bindings that when substituted for the
  // open variables in `query' satisfy the query proposition.  The query is
  // run in `module' and relative to `environment'.  `query' has the same syntax
  // as the PowerLoom `retrieve' command (which see) but with the `retrieve'
  // operator omitted.    For example, here are some legal `query' arguments:
  // 	 
  //     ((happy ?x))
  //     (10 (happy ?x))
  //     (all (happy ?x))
  //     (all ?x (happy ?x))
  //     (10 (happy ?x) :inference-level :assertion)
  //     (10 (happy ?x) :inference-level :assertion :timeout 1.0)
  // 	
  // If there is only a single output variable (as in all the examples above)
  // each element generated by the returned iterator will be a binding for
  // that variable - unless, the output variable was declared with a surrounding
  // pair of parentheses.  For example:
  // 	 
  //     (all (?x) (happy ?x))
  // 	
  // In that case, the generated elements will be one-element lists.  If there
  // are multiple output variables, each element generated by the returned
  // iterator will be a list of variable bindings that can be accessed using
  // the various `get-nth-...' functions.  The list of output variables does
  // not need to be declared in which case they are taken to be the open variables
  // in the query proposition in the order in which they were encountered.  If
  // order does matter or should be different from its default, it can be forced
  // by declaring the set of output variables.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? module : oMODULEo));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    environment = environment;
    // Should be synchronized on process lock oPOWERLOOM_LOCKo
    {
      query = ((Cons*)(deobjectifyTree(query)));
      return (consToPlIterator(callRetrieve(query)->consifyCurrentSolutions()));
    }
  }
}

extern "C" PlIterator* pli_retrieve(Cons* query, Module* module, Environment* environment) {
  // C-callable wrapper for `retrieve'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(retrieve(query, module, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

PlIterator* sRetrieve(const char* query, const char* moduleName, Environment* environment) {
  // Returns an iterator of variable bindings that when substituted for the
  // open variables in `query' satisfy the query proposition.  The query is
  // run in `module' and relative to `environment'.  `query' has the same syntax
  // as the PowerLoom `retrieve' command (which see) but with the `retrieve'
  // operator omitted.  Different from the PLI `retrieve' function, `s-retrieve'
  // does not expect a top-level pair of parentheses.  For example, here are some
  // legal `query' arguments:
  // 	 
  //     "(happy ?x)"
  //     "10 (happy ?x)"
  //     "all (happy ?x)"
  //     "all ?x (happy ?x)"
  //     "10 (happy ?x) :inference-level :assertion"
  //     "10 (happy ?x) :inference-level :assertion :timeout 1.0"
  // 	
  // If there is only a single output variable (as in all the examples above)
  // each element generated by the returned iterator will be a binding for
  // that variable - unless, the output variable was declared with a surrounding
  // pair of parentheses.  For example:
  // 	 
  //     "all (?x) (happy ?x)"
  // 	
  // In that case, the generated elements will be one-element lists.  If there
  // are multiple output variables, each element generated by the returned
  // iterator will be a list of variable bindings that can be accessed using
  // the various `get-nth-...' functions.  The list of output variables does
  // not need to be declared in which case they are taken to be the open variables
  // in the query proposition in the order in which they were encountered.  If
  // order does matter or should be different from its default, it can be forced
  // by declaring the set of output variables.
  // 
  // Names in `query' will be interpreted relative to module `module-name'.
  // A null `module-name' or the empty string refers to the current module.
  // If no module can be found with the name `module-name', then a STELLA
  // `no-such-context-exception' is thrown.
  { Cons* queryform = NIL;
    Context* module = safelyGetModule(moduleName, environment);

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, (((boolean)(module)) ? ((Module*)(module)) : oMODULEo));
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      environment = environment;
      // Should be synchronized on process lock oPOWERLOOM_LOCKo
      {
        { Object* sexp = NULL;
          SExpressionIterator* iter000 = sExpressions(newInputStringStream(query));
          Cons* collect000 = NULL;

          for  (; iter000->nextP(); ) {
            sexp = iter000->value;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(sexp, NIL);
                if (queryform == NIL) {
                  queryform = collect000;
                }
                else {
                  addConsToEndOfConsList(queryform, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(sexp, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
      }
    }
    return (retrieve(queryform, ((Module*)(module)), environment));
  }
}

extern "C" PlIterator* pli_sRetrieve(const char* query, const char* moduleName, Environment* environment) {
  // C-callable wrapper for `sRetrieve'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(sRetrieve(query, moduleName, environment)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Proposition* getFrameProposition(ControlFrame* frame) {
  // Return the proposition currently being inferred by this control `frame'.
  // This proposition will generally have bound and/or unbound pattern variables as its arguments.
  return (frame->proposition);
}

extern "C" Proposition* pli_getFrameProposition(ControlFrame* frame) {
  // C-callable wrapper for `getFrameProposition'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getFrameProposition(frame)));
    return (((Proposition*)(oC_API_RESULT_BUFFERo)));
  }
}

int getFrameArity(ControlFrame* frame) {
  // Return the arity of the proposition currently being inferred by `frame'.
  // This will be the actual number of arguments, even if the proposition is of variable arity.
  return (frame->proposition->arguments->length());
}

extern "C" int pli_getFrameArity(ControlFrame* frame) {
  // C-callable wrapper for `getFrameArity'.
  return (getFrameArity(frame));
}

PlIterator* getFrameIterator(ControlFrame* frame) {
  // Return the iterator generating successive bindings for the proposition
  // that is currently being inferred by `frame'.
  return (((PlIterator*)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_PLI_STELLA_ITERATOR, NULL))))));
}

extern "C" PlIterator* pli_getFrameIterator(ControlFrame* frame) {
  // C-callable wrapper for `getFrameIterator'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getFrameIterator(frame)));
    return (((PlIterator*)(oC_API_RESULT_BUFFERo)));
  }
}

void setFrameIterator(ControlFrame* frame, PlIterator* iterator) {
  // Set the iterator for generating successive bindings for the proposition
  // that is currently being inferred by `frame' to `iterator'.
  setDynamicSlotValue(frame->dynamicSlots, SYM_PLI_STELLA_ITERATOR, iterator, NULL);
}

extern "C" void pli_setFrameIterator(ControlFrame* frame, PlIterator* iterator) {
  // C-callable wrapper for `setFrameIterator'.
  setFrameIterator(frame, iterator);
}

Object* getNthFrameArgument(ControlFrame* frame, int n) {
  // Return the `n'-th argument of the proposition that is currently being inferred
  // by `frame'.  This will generally be a pattern variable that might be unbound or bound.
  { Vector* args = frame->proposition->arguments;

    if ((n >= 0) &&
        (n < args->length())) {
      return ((args->theArray)[n]);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Argument index " << "`" << n << "'" << " is out of range for " << "`" << frame->proposition << "'";
        throw *newLogicException(stream000->theStringReader());
      }
    }
  }
}

extern "C" Object* pli_getNthFrameArgument(ControlFrame* frame, int n) {
  // C-callable wrapper for `getNthFrameArgument'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getNthFrameArgument(frame, n)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Object* getNthFrameBinding(ControlFrame* frame, int n) {
  // Return the binding of the `n'-th argument of the proposition that is currently
  // being inferred by `frame'.  This will be NULL if the argument is unbound, otherwise, the object
  // bound to the variable.
  { Vector* args = frame->proposition->arguments;

    if ((n >= 0) &&
        (n < args->length())) {
      return (safeArgumentBoundTo((args->theArray)[n]));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Argument index " << "`" << n << "'" << " is out of range for " << "`" << frame->proposition << "'";
        throw *newLogicException(stream000->theStringReader());
      }
    }
  }
}

extern "C" Object* pli_getNthFrameBinding(ControlFrame* frame, int n) {
  // C-callable wrapper for `getNthFrameBinding'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getNthFrameBinding(frame, n)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

boolean setNthFrameBinding(ControlFrame* frame, int n, Object* value) {
  // Set the binding of the `n'-th argument of the proposition that is currently
  // being inferred by `frame' to `value'.  If the binding was successful, that is if the argument
  // was unbound or is already bound to `binding', the function returns TRUE.  Otherwise, the
  // argument will keep its current binding and FALSE will be returned.
  { Vector* args = frame->proposition->arguments;

    if ((n >= 0) &&
        (n < args->length())) {
      return (bindArgumentToValueP((args->theArray)[n], value, true));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Argument index " << "`" << n << "'" << " is out of range for " << "`" << frame->proposition << "'";
        throw *newLogicException(stream000->theStringReader());
      }
    }
  }
}

extern "C" int pli_setNthFrameBinding(ControlFrame* frame, int n, Object* value) {
  // C-callable wrapper for `setNthFrameBinding'.
  try {
    return (setNthFrameBinding(frame, n, value));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (false);
  }
}

boolean isFrameBindingPattern(ControlFrame* frame, const char* pattern) {
  // Return TRUE if the arguments of `frame' are bound according to `pattern'.
  // Each character in pattern corresponds to an argument at the particular position and  must be
  // either `B' (for bound) or `_' for unbound.  The function returns TRUE if `frame' has at least
  // as many arguments as `pattern' has characters and their bindings match `pattern'.  If `frame'
  // has additional arguments, they will be ignored.  If `pattern' has more positions than `frame'
  // has arguments, the function returns FALSE.
  { Vector* args = frame->proposition->arguments;

    if (strlen(pattern) <= args->length()) {
      { char ch = NULL_CHARACTER;
        const char* vector000 = pattern;
        int index000 = 0;
        int length000 = strlen(vector000);
        Object* arg = NULL;
        Vector* vector001 = args;
        int index001 = 0;
        int length001 = vector001->length();

        for  (; (index000 < length000) &&
                  (index001 < length001); 
              index000 = index000 + 1,
              index001 = index001 + 1) {
          ch = vector000[index000];
          arg = (vector001->theArray)[index001];
          switch (ch) {
            case 'B': 
              if (!((boolean)(safeArgumentBoundTo(arg)))) {
                return (false);
              }
              break;
            case '_': 
              if (((boolean)(safeArgumentBoundTo(arg)))) {
                return (false);
              }
              break;
            default:
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "Illegal binding pattern: " << "`" << pattern << "'";
                throw *newLogicException(stream000->theStringReader());
              }
              break;
          }
        }
      }
      return (true);
    }
    else {
      return (false);
    }
  }
}

extern "C" int pli_isFrameBindingPattern(ControlFrame* frame, const char* pattern) {
  // C-callable wrapper for `isFrameBindingPattern'.
  try {
    return (isFrameBindingPattern(frame, pattern));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (false);
  }
}

const char* getFrameBindingPattern(ControlFrame* frame) {
  // Return a string representation of the argument binding pattern of `frame'.
  // The syntax of the pattern is the same as used for `is-frame-binding-pattern' (which see).
  { Vector* args = frame->proposition->arguments;
    char* pattern = makeRawMutableString(args->length());

    { Object* arg = NULL;
      Vector* vector000 = args;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter000 = 0;

      for  (; index000 < length000; 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        arg = (vector000->theArray)[index000];
        i = iter000;
        if (((boolean)(safeArgumentBoundTo(arg)))) {
          pattern[i] = 'B';
        }
        else {
          pattern[i] = '_';
        }
      }
    }
    return (pattern);
  }
}

extern "C" const char* pli_getFrameBindingPattern(ControlFrame* frame) {
  // C-callable wrapper for `getFrameBindingPattern'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getFrameBindingPattern(frame)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

Cons* getFrameBindingState(ControlFrame* frame) {
  // Return a frame variable binding stack state that can be used to unbind
  // all frame variables to the state they were in when the binding stack state was recorded.
  { PatternRecord* patternrecord = oQUERYITERATORo->currentPatternRecord;
    int ubstackoffset = patternrecord->topUnbindingStackOffset;

    return (cons(patternrecord, cons(wrapInteger(ubstackoffset), NIL)));
  }
}

extern "C" Cons* pli_getFrameBindingState(ControlFrame* frame) {
  // C-callable wrapper for `getFrameBindingState'.
  try {
    oC_API_RESULT_BUFFERo = ((void*)(getFrameBindingState(frame)));
    return (((Cons*)(oC_API_RESULT_BUFFERo)));
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
    return (NULL);
  }
}

void setFrameBindingState(ControlFrame* frame, Cons* state) {
  // Reset the frame variable binding stack state to `state'.  This will set
  // all frame variables to the state they were in when the binding stack state was recorded.
  unbindVariablesBeginningAt(((PatternRecord*)(state->value)), ((int)(((NumberWrapper*)(state->rest->value))->numberWrapperToFloat() + 1)));
}

extern "C" void pli_setFrameBindingState(ControlFrame* frame, Cons* state) {
  // C-callable wrapper for `setFrameBindingState'.
  try {
    setFrameBindingState(frame, state);
  }
  catch (std::exception& _e) {
    std::exception* e = &_e;

    callGlobalExceptionHandler(e);
  }
}

Object* getPropertyObject(const char* property, Object* defaultvalue) {
  // Return the value of the global STELLA configuration `property'
  // or `defaultValue' if it is undefined.
  return (stella::getProperty(wrapString(property), consList(1, defaultvalue)));
}

extern "C" Object* pli_getPropertyObject(const char* property, Object* defaultvalue) {
  // C-callable wrapper for `getPropertyObject'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getPropertyObject(property, defaultvalue)));
    return (((Object*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* getPropertyString(const char* property, const char* defaultvalue) {
  // Return the value of the global STELLA configuration `property'
  // as a string or `defaultValue' if it is undefined.
  return (objectToString(stella::getProperty(wrapString(property), consList(1, wrapString(defaultvalue)))));
}

extern "C" const char* pli_getPropertyString(const char* property, const char* defaultvalue) {
  // C-callable wrapper for `getPropertyString'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getPropertyString(property, defaultvalue)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

const char* getProperty(const char* property, const char* defaultvalue) {
  // Synonym for `get-property-string' (which see).
  return (getPropertyString(property, defaultvalue));
}

extern "C" const char* pli_getProperty(const char* property, const char* defaultvalue) {
  // C-callable wrapper for `getProperty'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(getProperty(property, defaultvalue)));
    return (((const char*)(oC_API_RESULT_BUFFERo)));
  }
}

int getPropertyInteger(const char* property, int defaultvalue) {
  // Return the value of the global STELLA configuration `property'
  // as an integer or `defaultValue' if it is undefined.  Raises an error if the defined
  // value is not an integer.
  return (objectToInteger(stella::getProperty(wrapString(property), consList(1, wrapInteger(defaultvalue)))));
}

extern "C" int pli_getPropertyInteger(const char* property, int defaultvalue) {
  // C-callable wrapper for `getPropertyInteger'.
  return (getPropertyInteger(property, defaultvalue));
}

double getPropertyFloat(const char* property, double defaultvalue) {
  // Return the value of the global STELLA configuration `property'
  // as a float or `defaultValue' if it is undefined.  Raises an error if the defined
  // value is not a float.
  return (objectToFloat(stella::getProperty(wrapString(property), consList(1, wrapFloat(defaultvalue)))));
}

extern "C" double pli_getPropertyFloat(const char* property, double defaultvalue) {
  // C-callable wrapper for `getPropertyFloat'.
  return (getPropertyFloat(property, defaultvalue));
}

boolean getPropertyBoolean(const char* property, boolean defaultvalue) {
  // Return the value of the global STELLA configuration `property'
  // as a boolean or `defaultValue' if it is undefined.  Raises an error if the defined
  // value is not a boolean.
  return (coerceWrappedBooleanToBoolean(coerceToBoolean(stella::getProperty(wrapString(property), consList(1, (defaultvalue ? TRUE_WRAPPER : FALSE_WRAPPER))))));
}

extern "C" int pli_getPropertyBoolean(const char* property, int defaultvalue) {
  // C-callable wrapper for `getPropertyBoolean'.
  return (getPropertyBoolean(property, defaultvalue));
}

void setPropertyObject(const char* property, Object* value) {
  // Set the global STELLA configuration `property' to `value'.
  stella::setProperty(wrapString(stringCopy(property)), value);
}

extern "C" void pli_setPropertyObject(const char* property, Object* value) {
  // C-callable wrapper for `setPropertyObject'.
  setPropertyObject(property, value);
}

void setPropertyString(const char* property, const char* value) {
  // Set the global STELLA configuration `property' to a string `value'.
  stella::setProperty(wrapString(stringCopy(property)), wrapString(stringCopy(value)));
}

extern "C" void pli_setPropertyString(const char* property, const char* value) {
  // C-callable wrapper for `setPropertyString'.
  setPropertyString(property, value);
}

void setProperty(const char* property, const char* value) {
  // Synonym for `set-property-string' (which see).
  setPropertyString(property, value);
}

extern "C" void pli_setProperty(const char* property, const char* value) {
  // C-callable wrapper for `setProperty'.
  setProperty(property, value);
}

void setPropertyInteger(const char* property, int value) {
  // Set the global STELLA configuration `property' to an integer `value'.
  stella::setProperty(wrapString(stringCopy(property)), wrapInteger(value));
}

extern "C" void pli_setPropertyInteger(const char* property, int value) {
  // C-callable wrapper for `setPropertyInteger'.
  setPropertyInteger(property, value);
}

void setPropertyFloat(const char* property, double value) {
  // Set the global STELLA configuration `property' to a float `value'.
  stella::setProperty(wrapString(stringCopy(property)), wrapFloat(value));
}

extern "C" void pli_setPropertyFloat(const char* property, double value) {
  // C-callable wrapper for `setPropertyFloat'.
  setPropertyFloat(property, value);
}

void setPropertyBoolean(const char* property, boolean value) {
  // Set the global STELLA configuration `property' to a boolean `value'.
  stella::setProperty(wrapString(stringCopy(property)), (value ? TRUE_WRAPPER : FALSE_WRAPPER));
}

extern "C" void pli_setPropertyBoolean(const char* property, int value) {
  // C-callable wrapper for `setPropertyBoolean'.
  setPropertyBoolean(property, value);
}

boolean isDefinedProperty(const char* property) {
  // Return TRUE if `property' has a defined value.
  { Object* value = stella::getProperty(wrapString(property), NIL);

    return (((boolean)(value)) &&
        (!nullWrapperP(value)));
  }
}

extern "C" int pli_isDefinedProperty(const char* property) {
  // C-callable wrapper for `isDefinedProperty'.
  return (isDefinedProperty(property));
}

void printProperties() {
  // Print all currently defined STELLA configuration properties and values.
  stella::printProperties();
}

extern "C" void pli_printProperties() {
  // C-callable wrapper for `printProperties'.
  printProperties();
}

cpp_function_code getExceptionHandler() {
  return (getGlobalExceptionHandler());
}

extern "C" cpp_function_code pli_getExceptionHandler() {
  // C-callable wrapper for `getExceptionHandler'.
  return (getExceptionHandler());
}

void setExceptionHandler(cpp_function_code handler) {
  setGlobalExceptionHandler(handler);
}

extern "C" void pli_setExceptionHandler(cpp_function_code handler) {
  // C-callable wrapper for `setExceptionHandler'.
  setExceptionHandler(handler);
}

ObjectRegistryList* newObjectRegistryList() {
  { ObjectRegistryList* self = NULL;

    self = new ObjectRegistryList();
    self->theConsList = NIL;
    self->nFreeCells = 0;
    self->registryLength = 0;
    return (self);
  }
}

Surrogate* ObjectRegistryList::primaryType() {
  { ObjectRegistryList* self = this;

    return (SGT_PLI_PLI_OBJECT_REGISTRY_LIST);
  }
}

Object* accessObjectRegistryListSlotValue(ObjectRegistryList* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PLI_PLI_REGISTRY_LENGTH) {
    if (setvalueP) {
      self->registryLength = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->registryLength);
    }
  }
  else if (slotname == SYM_PLI_PLI_N_FREE_CELLS) {
    if (setvalueP) {
      self->nFreeCells = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->nFreeCells);
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

ObjectRegistryList* oOBJECT_REGISTRYo = NULL;

Cons* registerObject(Object* object) {
  // Register `object' to prevent it from being garbage-collected by the PowerLoom GC.
  // The result of registration is a handle for `object' which can later be used to unregister it.
  // Currently it is assumed that calling this immediately after an object was returned by a PLI function
  // is safe; however, we might have to handle registration in PLI functions before objects are returned.
  // This is not thread safe and needs to be explicitly synchronized in a threaded environment.
  { ObjectRegistryList* registry = oOBJECT_REGISTRYo;

    registry->push(object);
    registry->registryLength = registry->registryLength + 1;
    return (registry->theConsList);
  }
}

extern "C" Cons* pli_registerObject(Object* object) {
  // C-callable wrapper for `registerObject'.
  {
    oC_API_RESULT_BUFFERo = ((void*)(registerObject(object)));
    return (((Cons*)(oC_API_RESULT_BUFFERo)));
  }
}

void unregisterObject(Cons* objecthandle) {
  // Unregister the object whose registered handle is `objectHandle' to make it available
  // for PowerLoom garbage collection.  This also is not thread safe and needs to be explicitly synchronized
  // in a threaded environment.
  { ObjectRegistryList* registry = oOBJECT_REGISTRYo;
    int nfree = registry->nFreeCells;

    objecthandle->value = NULL;
    nfree = nfree + 1;
    if ((nfree > 1000) &&
        (nfree >= ((registry->registryLength) >> 1))) {
      registry->remove(NULL);
      registry->registryLength = registry->registryLength - nfree;
      nfree = 0;
    }
    registry->nFreeCells = nfree;
  }
}

extern "C" void pli_unregisterObject(Cons* objecthandle) {
  // C-callable wrapper for `unregisterObject'.
  unregisterObject(objecthandle);
}

int main() {
  std::cout << "Initializing STELLA..." << std::endl;
  startupStellaSystem();
  std::cout << "Initializing PowerLoom..." << std::endl;
  startupLogicSystem();
  stella::stringChangeModule("PL-USER");
  logic::powerloom();
  return (1);
}

void helpStartupPli1() {
  {
    SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE = ((Symbol*)(internRigidSymbolWrtModule("C-CALLABLE-WRAPPER-CODE", getStellaModule("/STELLA", true), 0)));
    SGT_PLI_PLI_ENVIRONMENT = ((Surrogate*)(internRigidSymbolWrtModule("ENVIRONMENT", NULL, 1)));
    SYM_PLI_LOGIC_LEVEL = ((Symbol*)(internRigidSymbolWrtModule("LEVEL", getStellaModule("/LOGIC", true), 0)));
    SGT_PLI_PLI_PL_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("PL-ITERATOR", NULL, 1)));
    SYM_PLI_STELLA_CURSOR = ((Symbol*)(internRigidSymbolWrtModule("CURSOR", getStellaModule("/STELLA", true), 0)));
    SGT_PLI_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    SGT_PLI_STELLA_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", getStellaModule("/STELLA", true), 1)));
    SGT_PLI_STELLA_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("VECTOR", getStellaModule("/STELLA", true), 1)));
    SYM_PLI_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", getStellaModule("/STELLA", true), 0)));
    SGT_PLI_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", getStellaModule("/LOGIC", true), 1)));
    SGT_PLI_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", getStellaModule("/LOGIC", true), 1)));
    SGT_PLI_STELLA_GENERALIZED_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("GENERALIZED-SYMBOL", getStellaModule("/STELLA", true), 1)));
    SGT_PLI_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 1)));
    SGT_PLI_STELLA_CONTEXT = ((Surrogate*)(internRigidSymbolWrtModule("CONTEXT", getStellaModule("/STELLA", true), 1)));
    SGT_PLI_LOGIC_COMPUTED_PROCEDURE = ((Surrogate*)(internRigidSymbolWrtModule("COMPUTED-PROCEDURE", getStellaModule("/LOGIC", true), 1)));
    SGT_PLI_STELLA_LITERAL_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_PLI_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", getStellaModule("/LOGIC", true), 1)));
    SYM_PLI_PLI_pR = ((Symbol*)(internRigidSymbolWrtModule("?R", NULL, 0)));
    SYM_PLI_PLI_pI = ((Symbol*)(internRigidSymbolWrtModule("?I", NULL, 0)));
    SYM_PLI_PLI_pV = ((Symbol*)(internRigidSymbolWrtModule("?V", NULL, 0)));
    SYM_PLI_PLI_F_GET_INFERRED_BINARY_PROPOSITION_VALUES_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("F-GET-INFERRED-BINARY-PROPOSITION-VALUES-QUERY-000", NULL, 0)));
    SYM_PLI_LOGIC_ALL = ((Symbol*)(internRigidSymbolWrtModule("ALL", getStellaModule("/LOGIC", true), 0)));
    SYM_PLI_LOGIC_pX = ((Symbol*)(internRigidSymbolWrtModule("?X", getStellaModule("/LOGIC", true), 0)));
    SYM_PLI_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    SYM_PLI_LOGIC_FAIL = ((Symbol*)(internRigidSymbolWrtModule("FAIL", getStellaModule("/LOGIC", true), 0)));
    SYM_PLI_STELLA_EXISTS = ((Symbol*)(internRigidSymbolWrtModule("EXISTS", getStellaModule("/STELLA", true), 0)));
    SYM_PLI_LOGIC_pY = ((Symbol*)(internRigidSymbolWrtModule("?Y", getStellaModule("/LOGIC", true), 0)));
    SYM_PLI_PLI_PROPER_SUBRELATION = ((Symbol*)(internRigidSymbolWrtModule("PROPER-SUBRELATION", NULL, 0)));
    SYM_PLI_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", getStellaModule("/STELLA", true), 0)));
    SYM_PLI_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", getStellaModule("/STELLA", true), 0)));
    KWD_PLI_CASE_SENSITIVEp = ((Keyword*)(internRigidSymbolWrtModule("CASE-SENSITIVE?", NULL, 2)));
    KWD_PLI_SUBSET_OF = ((Keyword*)(internRigidSymbolWrtModule("SUBSET-OF", NULL, 2)));
    KWD_PLI_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    KWD_PLI_RETRACT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("RETRACT-TRUE", NULL, 2)));
    KWD_PLI_ASSERT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("ASSERT-TRUE", NULL, 2)));
    SGT_PLI_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", getStellaModule("/LOGIC", true), 1)));
    SGT_PLI_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", getStellaModule("/LOGIC", true), 1)));
    SGT_PLI_PL_KERNEL_KB_NTH_DOMAIN = ((Surrogate*)(internRigidSymbolWrtModule("NTH-DOMAIN", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_PLI_MODULE = ((Keyword*)(internRigidSymbolWrtModule("MODULE", NULL, 2)));
    SGT_PLI_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", getStellaModule("/LOGIC", true), 1)));
    SGT_PLI_STELLA_INTEGER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_PLI_STELLA_FLOAT_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_PLI_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_PLI_STELLA_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("STRING-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SYM_PLI_STELLA_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR", getStellaModule("/STELLA", true), 0)));
    SGT_PLI_PLI_OBJECT_REGISTRY_LIST = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT-REGISTRY-LIST", NULL, 1)));
    SYM_PLI_PLI_REGISTRY_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("REGISTRY-LENGTH", NULL, 0)));
    SYM_PLI_PLI_N_FREE_CELLS = ((Symbol*)(internRigidSymbolWrtModule("N-FREE-CELLS", NULL, 0)));
    KWD_PLI_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
    SYM_PLI_PLI_STARTUP_PLI = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-PLI", NULL, 0)));
    SYM_PLI_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupPli2() {
  {
    defineFunctionObject("INITIALIZE", "(DEFUN INITIALIZE () :DOCUMENTATION \"Initialize the PowerLoom logic system.  This function\nneeds to be called by all applications before using PowerLoom.  If it\nis called more than once, every call after the first one is a no-op.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&initialize)), NULL);
    defineFunctionObject("RESET-POWERLOOM", "(DEFUN RESET-POWERLOOM () :DOCUMENTATION \"Reset PowerLoom to its initial state.\nCAUTION: This will destroy all loaded knowledge bases and might break other\nloaded STELLA systems if they do reference PowerLoom symbols in their code.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&resetPowerloom)), NULL);
    defineFunctionObject("CLEAR-CACHES", "(DEFUN CLEAR-CACHES () :DOCUMENTATION \"Clear all query and memoization caches.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&clearCaches)), NULL);
    defineFunctionObject("TEST-ENVIRONMENT-LEVEL?", "(DEFUN (TEST-ENVIRONMENT-LEVEL? BOOLEAN) ((ENV ENVIRONMENT) (LEVEL STRING)) :PUBLIC? FALSE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Test if `env' has level set to `level'\" (RETURN (AND (DEFINED? ENV) (STRING-EQL? (LEVEL ENV) LEVEL))))", ((cpp_function_code)(&testEnvironmentLevelP)), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF PL-ITERATOR)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Advance the PL-Iterator `self' and return `true' if more\nelements are available, `false' otherwise.\")", wrapMethodCode(((cpp_method_code)(&PlIterator::nextP))), NULL);
    defineFunctionObject("PL-ITERATOR-VALUE", "(DEFUN (PL-ITERATOR-VALUE OBJECT) ((SELF PL-ITERATOR)) :DOCUMENTATION \"C-callable iterator `value'-slot accessor.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&plIteratorValue)), NULL);
    defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF PL-ITERATOR)) :DOCUMENTATION \"Return TRUE if the iterator `self' has no more elements.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", wrapMethodCode(((cpp_method_code)(&PlIterator::emptyP))), NULL);
    defineFunctionObject("PL-ITERATOR-IS-EMPTY", "(DEFUN (PL-ITERATOR-IS-EMPTY BOOLEAN) ((SELF PL-ITERATOR)) :DOCUMENTATION \"Return TRUE if the iterator `self' has no more elements.\nThis is here primarily to support the `is-...' naming convention for tests.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&plIteratorIsEmpty)), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF PL-ITERATOR)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Number of items remaining in `self'.  Non destructive.\")", wrapMethodCode(((cpp_method_code)(&PlIterator::length))), NULL);
    defineFunctionObject("CONS-TO-PL-ITERATOR", "(DEFUN (CONS-TO-PL-ITERATOR PL-ITERATOR) ((SELF CONS)) :DOCUMENTATION \"Convert a STELLA cons list into an API iterator.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&consToPlIterator)), NULL);
    defineFunctionObject("LIST-TO-PL-ITERATOR", "(DEFUN (LIST-TO-PL-ITERATOR PL-ITERATOR) ((SELF LIST)) :DOCUMENTATION \"Convert a STELLA list into an API iterator.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&listToPlIterator)), NULL);
    defineFunctionObject("ITERATOR-TO-PL-ITERATOR", "(DEFUN (ITERATOR-TO-PL-ITERATOR PL-ITERATOR) ((SELF ITERATOR)) :DOCUMENTATION \"Convert an arbitrary STELLA iterator into an API iterator.\nThis will first exhaust `self' and then create an API iterator that will\niterate over the previously generated values.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&iteratorToPlIterator)), NULL);
    defineMethodObject("(DEFMETHOD (LISTIFY LIST) ((SELF PL-ITERATOR)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Convert `self' into a Stella LIST.\")", wrapMethodCode(((cpp_method_code)(&PlIterator::listify))), NULL);
    defineMethodObject("(DEFMETHOD (CONSIFY CONS) ((SELF PL-ITERATOR)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Convert `self' into a Stella CONS.\")", wrapMethodCode(((cpp_method_code)(&PlIterator::consify))), NULL);
    defineFunctionObject("CREATE-CONS", "(DEFUN (CREATE-CONS CONS) ((FIRST OBJECT) (REST CONS)) :DOCUMENTATION \"Create a STELLA CONS-cell whose value points to `first' and tail points to `rest'.\nIf `rest' is NULL, it will point to the empty list (available as a constructor in C).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&createCons)), NULL);
    defineFunctionObject("CREATE-CONS-LIST", "(DEFUN (CREATE-CONS-LIST CONS) ((LENGTH INTEGER)) :DOCUMENTATION \"Create a STELLA CONS-list of `length' with elements initialized to NULL (available as a constructor in C).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&createConsList)), NULL);
    defineFunctionObject("CONS-LENGTH", "(DEFUN (CONS-LENGTH INTEGER) ((SELF CONS)) :DOCUMENTATION \"Return the length of the CONS-list `self' (available to support access in C).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&consLength)), NULL);
    defineFunctionObject("CONS-IS-EMPTY", "(DEFUN (CONS-IS-EMPTY BOOLEAN) ((SELF CONS)) :DOCUMENTATION \"Return TRUE if the CONS-list `self' is empty (available to support access in C).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&consIsEmpty)), NULL);
    defineFunctionObject("CONS-FIRST", "(DEFUN (CONS-FIRST (LIKE (ANY-VALUE SELF))) ((SELF CONS)) :DOCUMENTATION \"Access the first element of the CONS-list `self' (available to support access in C).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&consFirst)), NULL);
    defineFunctionObject("CONS-REST", "(DEFUN (CONS-REST (LIKE SELF)) ((SELF CONS)) :DOCUMENTATION \"Access the rest (tail) of the CONS-list `self' (available to support access in C).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&consRest)), NULL);
    defineFunctionObject("CONS-NTH", "(DEFUN (CONS-NTH (LIKE (ANY-VALUE SELF))) ((SELF CONS) (N INTEGER)) :DOCUMENTATION \"Access the `n'-th element of the CONS-list `self' (available to support access in C).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&consNth)), NULL);
    defineFunctionObject("CONS-NTH-REST", "(DEFUN (CONS-NTH-REST (LIKE SELF)) ((SELF CONS) (N INTEGER)) :DOCUMENTATION \"Access the `n'-th rest (tail) of the CONS-list `self' (available to support access in C).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&consNthRest)), NULL);
    defineFunctionObject("CONS-SET-FIRST", "(DEFUN CONS-SET-FIRST ((SELF CONS) (VALUE OBJECT)) :DOCUMENTATION \"Set the first element of the CONS-list `self' to `value' (available to support access in C).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&consSetFirst)), NULL);
    defineFunctionObject("CONS-SET-REST", "(DEFUN CONS-SET-REST ((SELF CONS) (REST CONS)) :DOCUMENTATION \"Set the rest (tail) of the CONS-list `self' to `rest' (available to support access in C).\nIf `rest' is NULL, it will point to the empty list.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&consSetRest)), NULL);
    defineFunctionObject("CONS-SET-NTH", "(DEFUN CONS-SET-NTH ((SELF CONS) (N INTEGER) (VALUE OBJECT)) :DOCUMENTATION \"Set the `n'-th element of the CONS-list `self' to `value' (available to support access in C).\nThe run-time complexity of this operation is O(n).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&consSetNth)), NULL);
    defineFunctionObject("CONS-SET-NTH-REST", "(DEFUN CONS-SET-NTH-REST ((SELF CONS) (N INTEGER) (REST CONS)) :DOCUMENTATION \"Set the `n'-th rest (tail) of the CONS-list `self' to `rest' (available to support access in C).\nIf `rest' is NULL, it will point to the empty list.  The run-time complexity of this operation is O(n).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&consSetNthRest)), NULL);
    defineFunctionObject("LIST-FIRST", "(DEFUN (LIST-FIRST (LIKE (ANY-VALUE SELF))) ((SELF LIST)) :DOCUMENTATION \"Access the first element of the list `self' (available to support access in C).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&listFirst)), NULL);
    defineFunctionObject("LIST-REST", "(DEFUN (LIST-REST (CONS OF (LIKE (ANY-VALUE SELF)))) ((SELF LIST)) :DOCUMENTATION \"Access the rest (tail) of the list `self' (available to support access in C).\nNOTE: the rest of a STELLA list is a CONS-list not a LIST.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&listRest)), NULL);
    defineFunctionObject("LIST-NTH", "(DEFUN (LIST-NTH (LIKE (ANY-VALUE SELF))) ((SELF LIST) (N INTEGER)) :DOCUMENTATION \"Access the `n'-th element of the list `self' (available to support access in C).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&listNth)), NULL);
    defineFunctionObject("CREATE-STRING", "(DEFUN (CREATE-STRING STRING) ((CONTENT STRING)) :DOCUMENTATION \"Create a PowerLoom copy of the string `content' which uses PowerLoom memory\nmanagement and garbage collection.  This is primarily necessary in C environments when a string\nis passed to a PowerLoom PLI function which might then be pointed to by a PowerLoom result\nobject such as a string wrapper.  If such an argument string is later explicitly freed or\noverwritten, the result object would have a dangling reference or its content destroyed.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&createString)), NULL);
    defineFunctionObject("CREATE-STRING-WRAPPER", "(DEFUN (CREATE-STRING-WRAPPER STRING-WRAPPER) ((SELF STRING)) :DOCUMENTATION \"Create a STELLA string wrapper for `self'.  This automatically copies `self'\nbefore the wrapper is allocated to avoid garbage collection issues in case `self' is freed.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&createStringWrapper)), NULL);
    defineFunctionObject("CREATE-DIRECT-STRING-WRAPPER", "(DEFUN (CREATE-DIRECT-STRING-WRAPPER STRING-WRAPPER) ((SELF STRING)) :DOCUMENTATION \"Create a STELLA string wrapper for `self'.  This wraps `self' directly\nand does not allocate a PowerLoom copy first, hence, memory management of `self' needs to\nbe carefully handled by the caller.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&createDirectStringWrapper)), NULL);
    defineFunctionObject("CREATE-INTEGER-WRAPPER", "(DEFUN (CREATE-INTEGER-WRAPPER INTEGER-WRAPPER) ((SELF INTEGER)) :DOCUMENTATION \"Create a STELLA integer wrapper for `self'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&createIntegerWrapper)), NULL);
    defineFunctionObject("CREATE-LONG-INTEGER-WRAPPER", "(DEFUN (CREATE-LONG-INTEGER-WRAPPER LONG-INTEGER-WRAPPER) ((SELF LONG-INTEGER)) :DOCUMENTATION \"Create a STELLA long-integer wrapper for `self'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&createLongIntegerWrapper)), NULL);
    defineFunctionObject("CREATE-FLOAT-WRAPPER", "(DEFUN (CREATE-FLOAT-WRAPPER FLOAT-WRAPPER) ((SELF FLOAT)) :DOCUMENTATION \"Create a STELLA float wrapper for `self'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&createFloatWrapper)), NULL);
    defineFunctionObject("CREATE-BOOLEAN-WRAPPER", "(DEFUN (CREATE-BOOLEAN-WRAPPER BOOLEAN-WRAPPER) ((SELF BOOLEAN)) :DOCUMENTATION \"Create a STELLA boolean wrapper for `self'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&createBooleanWrapper)), NULL);
    defineFunctionObject("SAFELY-GET-OBJECT", "(DEFUN (SAFELY-GET-OBJECT OBJECT) ((NAME STRING) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? FALSE)", ((cpp_function_code)(&safelyGetObject)), NULL);
    defineFunctionObject("SAFELY-GET-CONCEPT", "(DEFUN (SAFELY-GET-CONCEPT OBJECT) ((NAME STRING) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? FALSE)", ((cpp_function_code)(&safelyGetConcept)), NULL);
    defineFunctionObject("SAFELY-GET-RELATION", "(DEFUN (SAFELY-GET-RELATION OBJECT) ((NAME STRING) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? FALSE)", ((cpp_function_code)(&safelyGetRelation)), NULL);
    defineFunctionObject("SAFELY-GET-MODULE", "(DEFUN (SAFELY-GET-MODULE CONTEXT) ((NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? FALSE)", ((cpp_function_code)(&safelyGetModule)), NULL);
    defineFunctionObject("SAFELY-GET-OBJECT-OR-NULL", "(DEFUN (SAFELY-GET-OBJECT-OR-NULL OBJECT) ((NAME STRING) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? FALSE)", ((cpp_function_code)(&safelyGetObjectOrNull)), NULL);
    defineFunctionObject("SEQUENCE-TO-CONS-LIST", "(DEFUN (SEQUENCE-TO-CONS-LIST CONS) ((SEQUENCE OBJECT)) :PUBLIC? FALSE)", ((cpp_function_code)(&sequenceToConsList)), NULL);
    defineFunctionObject("EXPLODE-STRING-LIST", "(DEFUN (EXPLODE-STRING-LIST CONS) ((STRINGLIST STRING) (MODULE MODULE)) :PUBLIC? FALSE)", ((cpp_function_code)(&explodeStringList)), NULL);
    defineFunctionObject("LEGAL-OPERATOR?", "(DEFUN (LEGAL-OPERATOR? BOOLEAN) ((OPERATOR SYMBOL)) :PUBLIC? FALSE)", ((cpp_function_code)(&legalOperatorP)), NULL);
    defineFunctionObject("GET-KEYWORD", "(DEFUN (GET-KEYWORD KEYWORD) ((NAME STRING)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Returns the Stella KEYWORD `name' if it exists.  Case sensitive.\")", ((cpp_function_code)(&getKeyword)), NULL);
    defineFunctionObject("GET-SYMBOL", "(DEFUN (GET-SYMBOL SYMBOL) ((NAME STRING) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Returns the Stella SYMBOL `name' visible in `module' if it\nexists.  `name' is ALWAYS treated literally and case sensitively.\")", ((cpp_function_code)(&getSymbol)), NULL);
    defineFunctionObject("GET-OPERATOR", "(DEFUN (GET-OPERATOR SYMBOL) ((NAME STRING)) :DOCUMENTATION \"Returns the logical operator object (a Stella SYMBOL) for `name'.\nIf no such operator exists then a `no-such-object' exception is thrown.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&getOperator)), NULL);
    defineFunctionObject("GET-OBJECT", "(DEFUN (GET-OBJECT OBJECT) ((NAME STRING) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Look for an object named `name' that is local to\nor visible from the module `module'.  `name' is not taken literally\nbut will be parsed first with the PowerLoom symbol reader and, hence,\ncan contain escape characters, module prefixes, etc.\")", ((cpp_function_code)(&getObject)), NULL);
    defineFunctionObject("S-GET-OBJECT", "(DEFUN (S-GET-OBJECT OBJECT) ((NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Look for an object named `name' that is local to\nor visible from the module `module-name'.  A module name of `null' or the\nempty string refers to the current module.  If no module can be found\nwith the name `module-name', then a STELLA `no-such-context-exception' is thrown.\n`name' is not taken literally but will be parsed first (see `get-object').\")", ((cpp_function_code)(&sGetObject)), NULL);
    defineFunctionObject("GET-CONCEPT", "(DEFUN (GET-CONCEPT LOGIC-OBJECT) ((NAME STRING) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return a class/concept named `name' that is local to\nor visible from the module `module'.  `name' is not taken literally but\nwill be parsed first (see `get-object').\")", ((cpp_function_code)(&getConcept)), NULL);
    defineFunctionObject("S-GET-CONCEPT", "(DEFUN (S-GET-CONCEPT LOGIC-OBJECT) ((NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return a class/concept named `name' that is local to\nor visible from the module `module-name'.  A module name of `null' or the\nempty string refers to the current module.  If no module can be found\nwith the name `module-name', then a Stella `no-such-context-exception' is thrown.\n`name' is not taken literally but will be parsed first (see `get-object').\")", ((cpp_function_code)(&sGetConcept)), NULL);
    defineFunctionObject("GET-RELATION", "(DEFUN (GET-RELATION LOGIC-OBJECT) ((NAME STRING) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return a concept or relation named `name' that is local to\nor visible from the module `module'.  `name' is not taken literally but will\nbe parsed first (see `get-object').\")", ((cpp_function_code)(&getRelation)), NULL);
    defineFunctionObject("S-GET-RELATION", "(DEFUN (S-GET-RELATION LOGIC-OBJECT) ((NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return a concept or relation named `name' that is local to\nor visible from the module `module-name'.  A module name of `null' or the\nempty string refers to the current module.  If no module can be found\nwith the name `module-name', then a Stella `no-such-context-exception' is thrown.\n`name' is not taken literally but will be parsed first (see `get-object').\")", ((cpp_function_code)(&sGetRelation)), NULL);
    defineFunctionObject("GET-UNDEFINED-RELATIONS", "(DEFUN (GET-UNDEFINED-RELATIONS (PL-ITERATOR OF LOGIC-OBJECT)) ((MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return relations that have been referenced but not defined in `module'.\")", ((cpp_function_code)(&getUndefinedRelations)), NULL);
    defineFunctionObject("GET-NAME-IN-MODULE", "(DEFUN (GET-NAME-IN-MODULE STRING) ((OBJ OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the name, qualified as necessary, so that `obj' can be found from\n`module'.  If there is no name for the object return `null'.\")", ((cpp_function_code)(&getNameInModule)), NULL);
    defineFunctionObject("GET-NAME", "(DEFUN (GET-NAME STRING) ((OBJ OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the fully qualified name of `obj', if it has one.  Otherwise return `null'.\")", ((cpp_function_code)(&getName)), NULL);
    defineFunctionObject("GET-SHORT-NAME", "(DEFUN (GET-SHORT-NAME STRING) ((OBJ OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the short name of `obj', if it has one.  Otherwise return `null'.\")", ((cpp_function_code)(&getShortName)), NULL);
    defineFunctionObject("GET-SKOLEM-NAME", "(DEFUN (GET-SKOLEM-NAME STRING) ((SKOLEM SKOLEM)) :DOCUMENTATION \"Return the fully qualified name of `skolem'.  Note that skolems are anonymous objects\nwhich cannot be referenced by their name in logic expressions, so this function is only useful in special\ncircumstances such as inside specialist computations, etc.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getSkolemName)), NULL);
    defineFunctionObject("GET-SKOLEM-SHORT-NAME", "(DEFUN (GET-SKOLEM-SHORT-NAME STRING) ((SKOLEM SKOLEM)) :DOCUMENTATION \"Return the unqualified name of `skolem'.  Note that skolems are anonymous objects which\ncannot be referenced by their name in logic expressions, so this function is only useful in special\ncircumstances such as inside specialist computations, etc.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getSkolemShortName)), NULL);
    defineFunctionObject("GET-VARIABLE-NAME", "(DEFUN (GET-VARIABLE-NAME STRING) ((VARIABLE PATTERN-VARIABLE)) :DOCUMENTATION \"Return the fully qualified name of `variable'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getVariableName)), NULL);
  }
}

void helpStartupPli3() {
  {
    defineFunctionObject("GET-VARIABLE-SHORT-NAME", "(DEFUN (GET-VARIABLE-SHORT-NAME STRING) ((VARIABLE PATTERN-VARIABLE)) :DOCUMENTATION \"Return the unqualified name of `variable'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getVariableShortName)), NULL);
    defineFunctionObject("OBJECT-TO-STRING", "(DEFUN (OBJECT-TO-STRING STRING) ((SELF OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return a printed representation of the term `self' as a string.\")", ((cpp_function_code)(&objectToString)), NULL);
    defineFunctionObject("OBJECT-TO-INTEGER", "(DEFUN (OBJECT-TO-INTEGER INTEGER) ((SELF OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Coerce `self' to an integer, or throw a Stella Exception if the coersion is not feasible.\nFloating point values will be coerced by rounding.\")", ((cpp_function_code)(&objectToInteger)), NULL);
    defineFunctionObject("OBJECT-TO-FLOAT", "(DEFUN (OBJECT-TO-FLOAT FLOAT) ((SELF OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Coerce `self' to a float, or throw a Stella Exception if the coersion is not feasible.\")", ((cpp_function_code)(&objectToFloat)), NULL);
    defineFunctionObject("OBJECT-TO-PARSABLE-STRING", "(DEFUN (OBJECT-TO-PARSABLE-STRING STRING) ((SELF OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return a string representing a printed\nrepresentation of the object `self'.  Like `object-to-string', but puts\nescaped double quotes around strings.\")", ((cpp_function_code)(&objectToParsableString)), NULL);
    defineFunctionObject("GET-STELLA-TYPE", "(DEFUN (GET-STELLA-TYPE SYMBOL) ((SELF OBJECT)) :DOCUMENTATION \"Return the name symbol of the STELLA class of which `self' is a direct instance.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getStellaType)), NULL);
    defineFunctionObject("GET-LOGIC-TYPE", "(DEFUN (GET-LOGIC-TYPE SYMBOL) ((SELF OBJECT)) :DOCUMENTATION \"Return the name symbol of the logic object type of `self'.  This type describes the basic\nrole this object plays in the logic system such as 'PROPOSITION', 'CONCEPT', 'THING', etc., as indicated by\nits native object type, it does not have anything to do with type propositions asserted about `self'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getLogicType)), NULL);
    defineFunctionObject("GET-STELLA-TYPE-NAME", "(DEFUN (GET-STELLA-TYPE-NAME STRING) ((SELF OBJECT)) :DOCUMENTATION \"Return the qualified name of the STELLA class of which `self' is a direct instance.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getStellaTypeName)), NULL);
    defineFunctionObject("GET-STELLA-TYPE-SHORT-NAME", "(DEFUN (GET-STELLA-TYPE-SHORT-NAME STRING) ((SELF OBJECT)) :DOCUMENTATION \"Return the unqualified name of the STELLA class of which `self' is a direct instance.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getStellaTypeShortName)), NULL);
    defineFunctionObject("GET-LOGIC-TYPE-NAME", "(DEFUN (GET-LOGIC-TYPE-NAME STRING) ((SELF OBJECT)) :DOCUMENTATION \"Return the qualified name of the logic type of `self'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getLogicTypeName)), NULL);
    defineFunctionObject("GET-LOGIC-TYPE-SHORT-NAME", "(DEFUN (GET-LOGIC-TYPE-SHORT-NAME STRING) ((SELF OBJECT)) :DOCUMENTATION \"Return the unqualified name of the logic type of `self'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getLogicTypeShortName)), NULL);
    defineFunctionObject("STRING-TO-OBJECT", "(DEFUN (STRING-TO-OBJECT OBJECT) ((STRING STRING) (TYPE LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Evaluate `string' with respect to `module' and `environment'\nand return the corresponding logical term.  `type' is a concept used to assist the\ncorrect interpretation of `string'.\n\nCurrently `type' only has an effect on the interpretation of literal types.\")", ((cpp_function_code)(((Object*  (*) (const char*, LogicObject*, Module*, Environment*))(&stringToObject)))), NULL);
    defineFunctionObject("STRING-TO-STELLA-EXPRESSION", "(DEFUN (STRING-TO-STELLA-EXPRESSION OBJECT) ((EXPRESSION STRING) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :DOCUMENTATION \"Read the STELLA `expression' in `module' and return the result.\nRaises a reader exception in case of incorrect STELLA syntax.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(((Object*  (*) (const char*, Module*, Environment*))(&stringToStellaExpression)))), NULL);
    defineFunctionObject("HELP-GET-TRUE-EXTENSION-MEMBERS", "(DEFUN (HELP-GET-TRUE-EXTENSION-MEMBERS (CONS OF PROPOSITION)) ((RELATION NAMED-DESCRIPTION) (SPECIALIZE? BOOLEAN)) :PUBLIC? FALSE)", ((cpp_function_code)(&helpGetTrueExtensionMembers)), NULL);
    defineFunctionObject("HELP-GET-PROPOSITIONS", "(DEFUN (HELP-GET-PROPOSITIONS (CONS OF PROPOSITION)) ((RELATION LOGIC-OBJECT) (ARGUMENTS CONS) (LIMIT INTEGER) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? FALSE)", ((cpp_function_code)(&helpGetPropositions)), NULL);
    defineFunctionObject("GET-PROPOSITION", "(DEFUN (GET-PROPOSITION PROPOSITION) ((RELATION-AND-ARGUMENTS OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return a proposition matching `relation-and-arguments' that\nhas been asserted (or inferred by forward chaining).  `relation-and-arguments'\nis a sequence containing objects and nulls.  The first argument must be the\nname of a relation.  A null value acts like a wild card.  If more than one \nproposition matches the input criteria, the selection among satisficing\npropositions is arbitrary.  This procedure is normally applied to single-valued\nrelations or functions.\")", ((cpp_function_code)(&getProposition)), NULL);
    defineFunctionObject("S-GET-PROPOSITION", "(DEFUN (S-GET-PROPOSITION PROPOSITION) ((RELATION-AND-ARGUMENTS STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return a proposition matching `relation-and-arguments' that\nhas been asserted (or inferred by forward chaining).  `relation-and-arguments'\nis a string that begins with a left parenthesis, followed by a relation name, \none or more argument identifiers, and terminated by a right parenthesis.  Each\nargument identifier can be the name of a logical constant, a literal reference\nsuch as a number, or the null identifier which acts like a wild card.\nIf more than one proposition matches the input criteria, the selection among\nsatisficing propositions is arbitrary.  This procedure is normally applied to\nsingle-valued relations or functions.\n\nA module name of `null' or the empty string refers to the current module.  If no module\nwith name `module-name' can be found, a STELLA `no-such-context-exception' is thrown.\")", ((cpp_function_code)(&sGetProposition)), NULL);
    defineFunctionObject("GET-PROPOSITIONS", "(DEFUN (GET-PROPOSITIONS (PL-ITERATOR OF PROPOSITION)) ((RELATION-AND-ARGUMENTS OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return propositions matching `relation-and-arguments' that\nhave been asserted (or inferred by forward chaining).  `relation-and-arguments'\nis a sequence containing objects and nulls.  The first argument must be the\nname of a relation.  A null value acts like a wild card.\")", ((cpp_function_code)(&getPropositions)), NULL);
    defineFunctionObject("S-GET-PROPOSITIONS", "(DEFUN (S-GET-PROPOSITIONS (PL-ITERATOR OF PROPOSITION)) ((RELATION-AND-ARGUMENTS STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return propositions matching `relation-and-arguments' that\nhave been asserted (or inferred by forward chaining).  `relation-and-arguments'\nis a string that begins with a left parenthesis, followed by a relation name, \none or more argument identifiers, and terminated by a right parenthesis.  Each\nargument identifier can be the name of a logical constant, a literal \nreference (e.g., a number), or the null identifier which acts like a wild card.\n\nA module name of `null' or the empty string refers to the current module.  If no module\nwith name `module-name' can be found, a STELLA `no-such-context-exception' is thrown.\")", ((cpp_function_code)(&sGetPropositions)), NULL);
    defineFunctionObject("GET-INCONSISTENT-PROPOSITIONS", "(DEFUN (GET-INCONSISTENT-PROPOSITIONS (PL-ITERATOR OF PROPOSITION)) ((MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return inconsistent propositions visible in `module'.\")", ((cpp_function_code)(&getInconsistentPropositions)), NULL);
    defineFunctionObject("GET-UNARY-PROPOSITIONS", "(DEFUN (GET-UNARY-PROPOSITIONS (PL-ITERATOR OF PROPOSITION)) ((RELATION LOGIC-OBJECT) (ARG OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return propositions such that (`relation' `arg')\nis true.  The `relation' argument must be bound to a relation.  `arg' may be\nset to NULL, which is interpreted as a wildcard.\")", ((cpp_function_code)(&getUnaryPropositions)), NULL);
    defineFunctionObject("GET-BINARY-PROPOSITION", "(DEFUN (GET-BINARY-PROPOSITION PROPOSITION) ((RELATION LOGIC-OBJECT) (ARG1 OBJECT) (ARG2 OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return a proposition such that (`relation' `arg1' `arg2')\nis true.  The `relation' argument must be bound to a relation.  One or both\nof the `arg1' and `arg2' arguments may be set to NULL, which is interpreted\nas a wildcard. If more than one proposition matches the input criteria,\nthe selection is arbitrary.  This procedure is normally applied to single-valued\nrelations or functions.\")", ((cpp_function_code)(&getBinaryProposition)), NULL);
    defineFunctionObject("GET-BINARY-PROPOSITIONS", "(DEFUN (GET-BINARY-PROPOSITIONS (PL-ITERATOR OF PROPOSITION)) ((RELATION LOGIC-OBJECT) (ARG1 OBJECT) (ARG2 OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return propositions such that (`relation' `arg1' `arg2')\nis true.  The `relation' argument must be bound to a relation.  One or both\nof the `arg1' and `arg2' arguments may be set to NULL, which is interpreted\nas a wildcard.\")", ((cpp_function_code)(&getBinaryPropositions)), NULL);
    defineFunctionObject("GET-INFERRED-BINARY-PROPOSITION-VALUES", "(DEFUN (GET-INFERRED-BINARY-PROPOSITION-VALUES PL-ITERATOR) ((RELATION LOGIC-OBJECT) (ARG OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return all values `v' such that (`relation' `arg' `v')\nhas been asserted or can be inferred via a general PowerLoom `retrieve'.\nBoth `relation' and `arg' have to be non-NULL.\")", ((cpp_function_code)(&getInferredBinaryPropositionValues)), NULL);
    defineFunctionObject("S-GET-INFERRED-BINARY-PROPOSITION-VALUES", "(DEFUN (S-GET-INFERRED-BINARY-PROPOSITION-VALUES PL-ITERATOR) ((RELATION-NAME STRING) (ARG-NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return all values `v' such that (`relation-name' `arg-name' `v')\nhas been asserted or can be inferred via a general PowerLoom `retrieve'.\n\nA module name of `null' or the empty string refers to the current module. \nIf no module can be found with the name `module-name', then a STELLA\n`no-such-context-exception' is thrown.\")", ((cpp_function_code)(&sGetInferredBinaryPropositionValues)), NULL);
    defineFunctionObject("GET-PROPOSITIONS-OF", "(DEFUN (GET-PROPOSITIONS-OF (PL-ITERATOR OF PROPOSITION)) ((OBJECT LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return all propositions that have `object' among their arguments,\nand that are TRUE in the scope of the module `module'.\")", ((cpp_function_code)(&getPropositionsOf)), NULL);
    defineFunctionObject("S-GET-PROPOSITIONS-OF", "(DEFUN (S-GET-PROPOSITIONS-OF (PL-ITERATOR OF PROPOSITION)) ((OBJECT-NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return all propositions that have the object named `object-name' among\ntheir arguments, and that are TRUE in the scope of the module `module-name'.\nA module name of `null' or the empty string refers to the current module. \nIf no module can be found with the name `module-name', then a Stella \n`no-such-context-exception' is thrown.\")", ((cpp_function_code)(&sGetPropositionsOf)), NULL);
    defineFunctionObject("GET-PROPOSITIONS-IN-MODULE", "(DEFUN (GET-PROPOSITIONS-IN-MODULE (PL-ITERATOR OF PROPOSITION)) ((MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return propositions that have been locally conceived in\nthe module `module' (but are not necessarily true).\")", ((cpp_function_code)(&getPropositionsInModule)), NULL);
    defineFunctionObject("IS-TRUE-UNARY-PROPOSITION", "(DEFUN (IS-TRUE-UNARY-PROPOSITION BOOLEAN) ((RELATION LOGIC-OBJECT) (ARG OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :DOCUMENTATION \"Return TRUE if the proposition (`relation' `arg') has\nbeen asserted (or inferred by forward chaining).\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&isTrueUnaryProposition)), NULL);
    defineFunctionObject("IS-TRUE-BINARY-PROPOSITION", "(DEFUN (IS-TRUE-BINARY-PROPOSITION BOOLEAN) ((RELATION LOGIC-OBJECT) (ARG OBJECT) (VALUE OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :DOCUMENTATION \"Return TRUE if the proposition (`relation' `arg' `value') has\nbeen asserted (or inferred by forward chaining).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&isTrueBinaryProposition)), NULL);
    defineFunctionObject("IS-TRUE-NARY-PROPOSITION", "(DEFUN (IS-TRUE-NARY-PROPOSITION BOOLEAN) ((RELATION-AND-ARGUMENTS OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :DOCUMENTATION \"Return TRUE if a proposition (`relation' `args') has\nbeen asserted (or inferred by forward chaining).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&isTrueNaryProposition)), NULL);
    defineFunctionObject("S-IS-TRUE-NARY-PROPOSITION", "(DEFUN (S-IS-TRUE-NARY-PROPOSITION BOOLEAN) ((RELATION-AND-ARGUMENTS STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :DOCUMENTATION \"Return TRUE if a proposition that prints as the string\n`relation-and-arguments' is true in the module named `module-name'.\nA module name of `null' or the empty string refers to the current module. \nIf no module can be found with the name `module-name', then a Stella \n`no-such-context-exception' is thrown.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&sIsTrueNaryProposition)), NULL);
    defineFunctionObject("IS-TRUE-PROPOSITION", "(DEFUN (IS-TRUE-PROPOSITION BOOLEAN) ((PROPOSITION PROPOSITION) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :DOCUMENTATION \"Return TRUE if `proposition' is TRUE in the module `module'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&isTrueProposition)), NULL);
    defineFunctionObject("IS-SUBRELATION", "(DEFUN (IS-SUBRELATION BOOLEAN) ((SUB LOGIC-OBJECT) (SUPER LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return TRUE if `sub' is a subconcept/subrelation of `super'.\")", ((cpp_function_code)(&isSubrelation)), NULL);
    defineFunctionObject("GET-PROPER-SUBRELATIONS", "(DEFUN (GET-PROPER-SUBRELATIONS (PL-ITERATOR OF LOGIC-OBJECT)) ((RELATION LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return relations that specialize `relation'.\nNon-reflexive.\")", ((cpp_function_code)(&getProperSubrelations)), NULL);
    defineFunctionObject("GET-DIRECT-SUBRELATIONS", "(DEFUN (GET-DIRECT-SUBRELATIONS (PL-ITERATOR OF LOGIC-OBJECT)) ((RELATION LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return relations that directly specialize `relation'.\nNon-reflexive.\")", ((cpp_function_code)(&getDirectSubrelations)), NULL);
    defineFunctionObject("GET-PROPER-SUPERRELATIONS", "(DEFUN (GET-PROPER-SUPERRELATIONS (PL-ITERATOR OF LOGIC-OBJECT)) ((RELATION LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return relations that generalize `relation'.\nNon-reflexive.\")", ((cpp_function_code)(&getProperSuperrelations)), NULL);
    defineFunctionObject("GET-DIRECT-SUPERRELATIONS", "(DEFUN (GET-DIRECT-SUPERRELATIONS (PL-ITERATOR OF LOGIC-OBJECT)) ((RELATION LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return relations that directly generalize `relation'.\nNon-reflexive.\")", ((cpp_function_code)(&getDirectSuperrelations)), NULL);
    defineFunctionObject("IS-INSTANCE", "(DEFUN (IS-INSTANCE BOOLEAN) ((OBJECT OBJECT) (CONCEPT LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :DOCUMENTATION \"Return TRUE if `object' is an instance of the concept `concept'.  This uses subsumption inference only.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&isInstance)), NULL);
    defineFunctionObject("IS-A", "(DEFUN (IS-A BOOLEAN) ((OBJECT OBJECT) (CONCEPT LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :DOCUMENTATION \"Deprecated - use `is-instance' instead.\" :PUBLIC? TRUE)", ((cpp_function_code)(&isA)), NULL);
    defineFunctionObject("GET-CONCEPT-INSTANCES", "(DEFUN (GET-CONCEPT-INSTANCES PL-ITERATOR) ((CONCEPT LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return instances of the concept `concept'.\nInclude instances of subconcepts of `concept'.  Depending on `concept',\nthe return values could be (wrapped) literals.\")", ((cpp_function_code)(&getConceptInstances)), NULL);
    defineFunctionObject("S-GET-CONCEPT-INSTANCES", "(DEFUN (S-GET-CONCEPT-INSTANCES PL-ITERATOR) ((CONCEPT-NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return instances of concept `concept-name'.\nInclude instances of subconcepts of `concept-name'.  Depending on `concept-name',\nthe return values could be (wrapped) literals.\n\nA module name of `null' or the empty string refers to the current module. \nIf no module can be found with the name `module-name', then a Stella \n`no-such-context-exception' is thrown.\")", ((cpp_function_code)(&sGetConceptInstances)), NULL);
    defineFunctionObject("GET-DIRECT-CONCEPT-INSTANCES", "(DEFUN (GET-DIRECT-CONCEPT-INSTANCES PL-ITERATOR) ((CONCEPT LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return instances of concept `concept'.\nExclude instances of subconcepts of `concept'.  Depending on `concept',\nthe return values could be (wrapped) literals.\")", ((cpp_function_code)(&getDirectConceptInstances)), NULL);
    defineFunctionObject("S-GET-DIRECT-CONCEPT-INSTANCES", "(DEFUN (S-GET-DIRECT-CONCEPT-INSTANCES PL-ITERATOR) ((CONCEPT-NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return instances of concept `concept-name'.\nExclude instances of subconcepts of `concept-name'.  Depending on `concept-name',\nthe return values could be (wrapped) literals.\n\nA module name of `null' or the empty string refers to the current module. \nIf no module can be found with the name `module-name', then a Stella \n`no-such-context-exception' is thrown.\")", ((cpp_function_code)(&sGetDirectConceptInstances)), NULL);
    defineFunctionObject("GET-CONCEPT-INSTANCES-MATCHING-VALUE", "(DEFUN (GET-CONCEPT-INSTANCES-MATCHING-VALUE PL-ITERATOR) ((CONCEPT LOGIC-OBJECT) (RELATION LOGIC-OBJECT) (VALUE OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return members of concept `concept' that\nhave an attribute matching `value' for the binary relation `relation', i.e.,\n`(relation <result> value)' holds.\")", ((cpp_function_code)(&getConceptInstancesMatchingValue)), NULL);
    defineFunctionObject("GET-CONCEPT-INSTANCE-MATCHING-VALUE", "(DEFUN (GET-CONCEPT-INSTANCE-MATCHING-VALUE OBJECT) ((CONCEPT LOGIC-OBJECT) (RELATION LOGIC-OBJECT) (VALUE OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return a member of concept `concept' that\nhas an attribute matching `value' for the binary relation `relation', i.e.,\n`(relation <result> value)' holds.\")", ((cpp_function_code)(&getConceptInstanceMatchingValue)), NULL);
    defineFunctionObject("HELP-GET-TYPES", "(DEFUN (HELP-GET-TYPES (CONS OF LOGIC-OBJECT)) ((OBJECT LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? FALSE)", ((cpp_function_code)(&helpGetTypes)), NULL);
    defineFunctionObject("GET-TYPES", "(DEFUN (GET-TYPES (PL-ITERATOR OF LOGIC-OBJECT)) ((OBJECT LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return all named concepts that `object' belongs to.\")", ((cpp_function_code)(&getTypes)), NULL);
    defineFunctionObject("GET-DIRECT-TYPES", "(DEFUN (GET-DIRECT-TYPES (PL-ITERATOR OF LOGIC-OBJECT)) ((OBJECT LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return most specific concepts that `object' belongs to.\")", ((cpp_function_code)(&getDirectTypes)), NULL);
    defineFunctionObject("GET-RELATION-EXTENSION", "(DEFUN (GET-RELATION-EXTENSION (PL-ITERATOR OF PROPOSITION)) ((RELATION LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :DOCUMENTATION \"Return propositions that satisfy `relation'.\nInclude propositions that satisfy subrelations of `relation'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getRelationExtension)), NULL);
    defineFunctionObject("S-GET-RELATION-EXTENSION", "(DEFUN (S-GET-RELATION-EXTENSION (PL-ITERATOR OF PROPOSITION)) ((RELATION-NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return propositions that satisfy the relation named\n`relation-name'.  Include propositions that satisfy subrelations of the relation.\")", ((cpp_function_code)(&sGetRelationExtension)), NULL);
    defineFunctionObject("GET-MODULE", "(DEFUN (GET-MODULE MODULE) ((NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return a module named `name' or NULL if no such module exists.\")", ((cpp_function_code)(&getModule)), NULL);
    defineFunctionObject("GET-EXISTING-MODULE", "(DEFUN (GET-EXISTING-MODULE MODULE) ((NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return the module named `name' or raise a STELLA `no-such-context-exception' if it doesn't exist.\")", ((cpp_function_code)(&getExistingModule)), NULL);
    defineFunctionObject("GET-CURRENT-MODULE", "(DEFUN (GET-CURRENT-MODULE MODULE) ((ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the currently set module\")", ((cpp_function_code)(&getCurrentModule)), NULL);
    defineFunctionObject("GET-HOME-MODULE", "(DEFUN (GET-HOME-MODULE MODULE) ((OBJECT LOGIC-OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the module in which `object' was created.\")", ((cpp_function_code)(&getHomeModule)), NULL);
    defineFunctionObject("GET-MODULES", "(DEFUN (GET-MODULES (PL-ITERATOR OF MODULE)) ((KB-MODULES-ONLY? BOOLEAN)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return all modules currently loaded into PowerLoom.  If `kb-modules-only?'\nis `true', then Stella modules that are used only for program code are\nnot included in the list.\")", ((cpp_function_code)(&getModules)), NULL);
    defineFunctionObject("CREATE-MODULE", "(DEFUN (CREATE-MODULE MODULE) ((NAME STRING) (PARENT MODULE) (CASE-SENSITIVE? BOOLEAN)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Creates a new module `name' as a child of `parent'.  The flag\n`case-sensitive?' controls whether names read in this module will be\ncase sensitive or not.\")", ((cpp_function_code)(&createModule)), NULL);
    defineFunctionObject("S-CREATE-MODULE", "(DEFUN (S-CREATE-MODULE MODULE) ((NAME STRING) (PARENT-NAME STRING) (CASE-SENSITIVE? BOOLEAN) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Creates a new module `name' as a child of `parent-name'.  The flag\n`case-sensitive?' controls whether names read in this module will be\ncase sensitive or not.\")", ((cpp_function_code)(&sCreateModule)), NULL);
    defineFunctionObject("CHANGE-MODULE", "(DEFUN (CHANGE-MODULE MODULE) ((MODULE MODULE)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Set the current module to `module' and return it.\nIf `module' is `null', then no switch is performed and the current\nmodule is returned.\")", ((cpp_function_code)(&changeModule)), NULL);
    defineFunctionObject("S-CHANGE-MODULE", "(DEFUN (S-CHANGE-MODULE MODULE) ((NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Set the current module to the module named `name'.\nThe return value is the module named `name' unless `name' is null or\nthe empty string.  In that case, the current module is returned.\nIf no module named `name' exists, a Stella `no-such-context-exception'\nis thrown.\")", ((cpp_function_code)(&sChangeModule)), NULL);
  }
}

void helpStartupPli4() {
  {
    defineFunctionObject("CLEAR-MODULE", "(DEFUN (CLEAR-MODULE MODULE) ((MODULE MODULE)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Destroy the contents of the module `module' as well as\nthe contents of all of its children, recursively.\")", ((cpp_function_code)(&clearModule)), NULL);
    defineFunctionObject("S-CLEAR-MODULE", "(DEFUN (S-CLEAR-MODULE MODULE) ((NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Destroy the contents of the module named `name', as\nwell as the contents of all of its children, recursively.  If no module\nnamed `name' exists, a Stella `no-such-context-exception' is thrown.\")", ((cpp_function_code)(&sClearModule)), NULL);
    defineFunctionObject("GET-CHILD-MODULES", "(DEFUN (GET-CHILD-MODULES (PL-ITERATOR OF MODULE)) ((MODULE MODULE)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the modules that are immediate children of `module'.\")", ((cpp_function_code)(&getChildModules)), NULL);
    defineFunctionObject("S-GET-CHILD-MODULES", "(DEFUN (S-GET-CHILD-MODULES (PL-ITERATOR OF MODULE)) ((NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the modules that are immediate children of module `name'.\nIf no module named `name' exists, a Stella `no-such-context-exception'\nis thrown.\")", ((cpp_function_code)(&sGetChildModules)), NULL);
    defineFunctionObject("GET-PARENT-MODULES", "(DEFUN (GET-PARENT-MODULES (PL-ITERATOR OF MODULE)) ((MODULE MODULE)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the modules that are immediate parents of `module'.\")", ((cpp_function_code)(&getParentModules)), NULL);
    defineFunctionObject("S-GET-PARENT-MODULES", "(DEFUN (S-GET-PARENT-MODULES (PL-ITERATOR OF MODULE)) ((NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the modules that are immediate parents of module `name'.\nIf no module named `name' exists, a Stella `no-such-context-exception'\nis thrown.\")", ((cpp_function_code)(&sGetParentModules)), NULL);
    defineFunctionObject("GENERATE-UNIQUE-NAME", "(DEFUN (GENERATE-UNIQUE-NAME STRING) ((PREFIX STRING) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Generates a name based on `prefix' with a number appended that\nis not currently in use in `module.'  In a non-case-sensitive module, the returned\nname will be all upper case (This latter feature may change!)\")", ((cpp_function_code)(&generateUniqueName)), NULL);
    defineFunctionObject("CREATE-KEYWORD", "(DEFUN (CREATE-KEYWORD KEYWORD) ((NAME STRING)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Returns the Stella keyword `name', creating it if\nnecessary.  `name' is treated literally and case-sensitively.\nThis should generally not be necessary to do.\")", ((cpp_function_code)(&createKeyword)), NULL);
    defineFunctionObject("CREATE-SYMBOL", "(DEFUN (CREATE-SYMBOL SYMBOL) ((NAME STRING) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Returns the Stella symbol `name' visible in `module',\ncreating it if necessary.  `name' is treated literally and ALWAYS case-sensitively,\neven if `module' is case insensitive. This should generally not be necessary to do.\")", ((cpp_function_code)(&createSymbol)), NULL);
    defineFunctionObject("CREATE-OBJECT", "(DEFUN (CREATE-OBJECT LOGIC-OBJECT) ((NAME STRING) (CONCEPT LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Create an object named `name' of type `concept' in the designated\nmodule.  Both `name' and `concept' can be `null'.  If `name' is `null' then an\nobject will be created with a new, non-conflicting name based on the name of\n`concept', or system-generated if no concept is specified.  If `concept' is\n`null', then the object will be of type THING.  It is an error to create an\nobject with the same name as an existing object.\n\nNote that the string can be a qualified name, in which case the object\nwill be created in the module specified, but with a name as determined\nby the qualified name.  Vertical bars in the name string are interpreted\nas Stella escape characters.\n\nNote that because names in modules that are not case-sensitive are\ncanonicalized, the name of the returned object may not match `name'\nexactly.\n\nRe" "turn the object.\")", ((cpp_function_code)(&createObject)), NULL);
    defineFunctionObject("S-CREATE-OBJECT", "(DEFUN (S-CREATE-OBJECT LOGIC-OBJECT) ((NAME STRING) (CONCEPT-NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Create an object named `name' of type `concept-name' in the designated\nmodule.  Both `name' and `concept-name' can be null strings.  If `name' is a null string\nthen an object will be created with a new, non-conflicting name based on `concept-name', or\nsystem-generated if no concept nameis specified.  If `concept-name' is the null string, then\nthe object will be of type THING.\n\nA module name of `null' or the empty string refers to the current module. \nIf no module can be found with the name `module-name', then a Stella \n`no-such-context-exception' is thrown.\n\nNote that because names in modules that are not case-sensitive are canonicalized,\nthe name of the returned object may not match `name' exactly.\n\nReturn the object.\")", ((cpp_function_code)(&sCreateObject)), NULL);
    defineFunctionObject("CREATE-CONCEPT", "(DEFUN (CREATE-CONCEPT LOGIC-OBJECT) ((NAME STRING) (PARENT LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Create a concept named `name' in the designated `module', with the\ndesignated `parent' superconcept (which can be left undefined).  Additional\nsuperconcepts can be added via assertions of the `subset-of' relation.  Note\nthat a specified `parent' concept needs to be created separately.\n\nNote that because names in modules that are not case-sensitive are canonicalized,\nthe name of the returned object may not match `name' exactly.\")", ((cpp_function_code)(&createConcept)), NULL);
    defineFunctionObject("S-CREATE-CONCEPT", "(DEFUN (S-CREATE-CONCEPT LOGIC-OBJECT) ((NAME STRING) (PARENT-NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Create a concept named `name' in the designated module, with\nwith the concept named `parent-name' as superconcept (which can be left\nundefined).  Additional superconcepts can be added via assertions of the\n`subset-of' relation.  Note that a specified parent concept needs to be\ncreated separately.\n\nA module name of `null' or the empty string refers to the current module. \nIf no module can be found with the name `module-name', then a Stella \n`no-such-context-exception' is thrown.\n\nNote that because names in modules that are not case-sensitive are canonicalized,\nthe name of the returned object may not match `name' exactly.\")", ((cpp_function_code)(&sCreateConcept)), NULL);
    defineFunctionObject("CREATE-RELATION", "(DEFUN (CREATE-RELATION LOGIC-OBJECT) ((NAME STRING) (ARITY INTEGER) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Create a relation named `name' with arity `arity' in the\ndesignated module.  Domain and range information can be added via assertions\nof `nth-domain' (or `domain' and `range') relations.\n\nNote that because names in modules that are not case-sensitive are canonicalized,\nthe name of the returned object may not match `name' exactly.\")", ((cpp_function_code)(&createRelation)), NULL);
    defineFunctionObject("S-CREATE-RELATION", "(DEFUN (S-CREATE-RELATION LOGIC-OBJECT) ((NAME STRING) (ARITY INTEGER) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Create a relation named `name' with arity `arity' in the\ndesignated module.  Domain and range information can be added via assertions\nof `nth-domain' (or `domain' and `range') relations.\n\nA module name of `null' or the empty string refers to the current module. \nIf no module can be found with the name `module-name', then a Stella \n`no-such-context-exception' is thrown.\n\nNote that because names in modules that are not case-sensitive are canonicalized,\nthe name of the returned object may not match `name' exactly.\")", ((cpp_function_code)(&sCreateRelation)), NULL);
    defineFunctionObject("CREATE-FUNCTION", "(DEFUN (CREATE-FUNCTION LOGIC-OBJECT) ((NAME STRING) (ARITY INTEGER) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Create a function named `name' with arity `arity'  in the designated \n`module'.  Domain and range information can be added via assertions of\n`nth-domain' (or `domain' and `range') relations.\n\nNote that because names in modules that are not case-sensitive are canonicalized,\nthe name of the returned object may not match `name' exactly.\")", ((cpp_function_code)(&createFunction)), NULL);
    defineFunctionObject("S-CREATE-FUNCTION", "(DEFUN (S-CREATE-FUNCTION LOGIC-OBJECT) ((NAME STRING) (ARITY INTEGER) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Create a function named `name' with arity `arity' in the designated \nmodule.  Domain and range information can be added via assertions of\n`domain', `nth-domain' and `range' relations.\n\nA module name of `null' or the empty string refers to the current module. \nIf no module can be found with the name `module-name', then a Stella \n`no-such-context-exception' is thrown.\n\nNote that because names in modules that are not case-sensitive are canonicalized,\nthe name of the returned object may not match `name' exactly.\")", ((cpp_function_code)(&sCreateFunction)), NULL);
    defineFunctionObject("REGISTER-SPECIALIST-FUNCTION", "(DEFUN REGISTER-SPECIALIST-FUNCTION ((NAME STRING) (FUNCTION-REFERENCE FUNCTION-CODE) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Register `name' as a function name in `module' which will invoke the\nnative code procedure described by `function-reference.'  The `name'\nis a fully-qualified name which will be interpreted by the normal\nrules for reading names in PowerLoom.  The function must conform\nto the signature for specialist functions.\n\nThe exact form of `function-reference' depends on the underlying\nprogramming language.  The following type mappings are used:\n          C++:  \n  Common Lisp:  FUNCTION   (result of #' or (FUNCTION ...))\n         Java:  java.lang.reflect.Method\")", ((cpp_function_code)(&registerSpecialistFunction)), NULL);
    defineFunctionObject("S-REGISTER-SPECIALIST-FUNCTION", "(DEFUN S-REGISTER-SPECIALIST-FUNCTION ((NAME STRING) (NATIVE-NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Register `name' as a function name in the module named `module-name'.\nThis function will the native code named `native-name'.  The `name'\nis a fully-qualified name which will be interpreted by the normal\nrules for reading names in PowerLoom.  The `native-name' will be\nprocessed in a manner that depends on the underlying programming\nlanguage.  The following type mappings are used:\n          C++:  Not available.  Error signaled.\n  Common Lisp:  The native-name is read by READ-FROM-STRING and then\n                the SYMBOL-FUNCTION is taken.\n         Java:  A fully package-qualified name is required.  It is\n                looked up using the Reflection tools.\nThe function found must conform to the signature for specialist functions.\")", ((cpp_function_code)(&sRegisterSpecialistFunction)), NULL);
    defineFunctionObject("REGISTER-COMPUTATION-FUNCTION", "(DEFUN REGISTER-COMPUTATION-FUNCTION ((NAME STRING) (FUNCTION-REFERENCE FUNCTION-CODE) (ARITY INTEGER) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Register `name' as a function name in `module' which will invoke the\nnative code procedure described by `function-reference.'  The `name'\nis a fully-qualified name which will be interpreted by the normal\nrules for reading names in PowerLoom.  The function must conform\nto the signature for computation functions used by the computation\nspecialist.  Arity specifies the number of arguments the computation\naccepts.\n\nThe exact form of `function-reference' depends on the underlying\nprogramming language.  The following type mappings are used:\n          C++:  cpp_function_code (a pointer to the function code)\n  Common Lisp:  FUNCTION   (result of #' or (FUNCTION ...))\n         Java:  java.lang.reflect.Method\")", ((cpp_function_code)(&registerComputationFunction)), NULL);
    defineFunctionObject("S-REGISTER-COMPUTATION-FUNCTION", "(DEFUN S-REGISTER-COMPUTATION-FUNCTION ((NAME STRING) (NATIVE-NAME STRING) (ARITY INTEGER) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Register `name' as a function name in the module named `module-name'.\nThis function will the native code named `native-name'.  The `name'\nis a fully-qualified name which will be interpreted by the normal\nrules for reading names in PowerLoom.  The `native-name' will be\nprocessed in a manner that depends on the underlying programming\nlanguage.  The following type mappings are used:\n          C++:  Not available.  Error signaled.\n  Common Lisp:  The native-name is read by READ-FROM-STRING and then\n                the SYMBOL-FUNCTION is taken.\n         Java:  A fully package-qualified name is required.  It is\n                looked up using the Reflection tools.\nThe function found must conform to the signature for computation functions.\nArity specifies the number of arguments the computation accepts.\")", ((cpp_function_code)(&sRegisterComputationFunction)), NULL);
    defineFunctionObject("CREATE-ENUMERATED-LIST", "(DEFUN (CREATE-ENUMERATED-LIST LOGIC-OBJECT) ((MEMBERS CONS) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Create a logical term that denotes a list containing `members' in\n`module' using `environment'.  Useful for passing lists as arguments\nto parameterized queries.\")", ((cpp_function_code)(&createEnumeratedList)), NULL);
    defineFunctionObject("CREATE-ENUMERATED-SET", "(DEFUN (CREATE-ENUMERATED-SET LOGIC-OBJECT) ((MEMBERS CONS) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Create a logical term that denotes the enumerated set containing `members'\nin `module' using `environment'.\")", ((cpp_function_code)(&createEnumeratedSet)), NULL);
    defineFunctionObject("DESTROY-OBJECT", "(DEFUN DESTROY-OBJECT ((OBJECT OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Delete the object `object', retracting all facts attached to it.\")", ((cpp_function_code)(&destroyObject)), NULL);
    defineFunctionObject("S-DESTROY-OBJECT", "(DEFUN S-DESTROY-OBJECT ((OBJECT-NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Delete the object named `object-name', retracting all facts\nattached to it.\n\nA module name of `null' or the empty string refers to the current module. \nIf no module can be found with the name `module-name', then a Stella \n`no-such-context-exception' is thrown.\")", ((cpp_function_code)(&sDestroyObject)), NULL);
    defineFunctionObject("ASSERT-UNARY-PROPOSITION", "(DEFUN (ASSERT-UNARY-PROPOSITION PROPOSITION) ((RELATION LOGIC-OBJECT) (ARG OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Assert that the proposition (`relation' `arg') is TRUE in `module'.  Return the asserted proposition.\")", ((cpp_function_code)(&assertUnaryProposition)), NULL);
    defineFunctionObject("ASSERT-BINARY-PROPOSITION", "(DEFUN (ASSERT-BINARY-PROPOSITION PROPOSITION) ((RELATION LOGIC-OBJECT) (ARG OBJECT) (VALUE OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Assert that the proposition (`relation' `arg' `value') is TRUE\nin `module'.  Return the asserted proposition.\")", ((cpp_function_code)(&assertBinaryProposition)), NULL);
    defineFunctionObject("ASSERT-NARY-PROPOSITION", "(DEFUN (ASSERT-NARY-PROPOSITION PROPOSITION) ((RELATION-AND-ARGUMENTS OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Assert that the proposition represented by the list ` relation-and-arguments' satisfies\nthe relation `relation'.\")", ((cpp_function_code)(&assertNaryProposition)), NULL);
    defineFunctionObject("RETRACT-UNARY-PROPOSITION", "(DEFUN (RETRACT-UNARY-PROPOSITION PROPOSITION) ((RELATION LOGIC-OBJECT) (ARG OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Retract that the proposition (`relation' `arg') is TRUE in `module'.  Return the asserted proposition.\")", ((cpp_function_code)(&retractUnaryProposition)), NULL);
    defineFunctionObject("RETRACT-BINARY-PROPOSITION", "(DEFUN (RETRACT-BINARY-PROPOSITION PROPOSITION) ((RELATION LOGIC-OBJECT) (ARG OBJECT) (VALUE OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Retract that the proposition (`relation' `arg' `value') is TRUE\nin `module'.  Return the asserted proposition.\")", ((cpp_function_code)(&retractBinaryProposition)), NULL);
    defineFunctionObject("RETRACT-NARY-PROPOSITION", "(DEFUN (RETRACT-NARY-PROPOSITION PROPOSITION) ((RELATION-AND-ARGUMENTS OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Retract the proposition that `arguments' satisfies\nthe relation `relation'.\")", ((cpp_function_code)(&retractNaryProposition)), NULL);
    defineFunctionObject("ASSERT-PROPOSITION", "(DEFUN (ASSERT-PROPOSITION PROPOSITION) ((PROPOSITION PROPOSITION) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Assert that the proposition `proposition' is true in `module'.\nReturn the asserted proposition.\")", ((cpp_function_code)(&assertProposition)), NULL);
    defineFunctionObject("S-ASSERT-PROPOSITION", "(DEFUN (S-ASSERT-PROPOSITION (PL-ITERATOR OF PROPOSITION)) ((SENTENCE STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Assert that the logical sentence `sentence' is true in the module\nnamed `module-name'.  A module name of `null' or the empty string refers to the\ncurrent module.  If no module can be found with the name `module-name',\nthen a Stella `no-such-context-exception' is thrown.\n\nReturn an iterator of the propositions resulting from sentence.\")", ((cpp_function_code)(&sAssertProposition)), NULL);
    defineFunctionObject("RETRACT-PROPOSITION", "(DEFUN (RETRACT-PROPOSITION PROPOSITION) ((PROPOSITION PROPOSITION) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Retract the truth of the proposition `proposition' in `module'.\nReturn the retracted proposition.\")", ((cpp_function_code)(&retractProposition)), NULL);
    defineFunctionObject("S-RETRACT-PROPOSITION", "(DEFUN (S-RETRACT-PROPOSITION (PL-ITERATOR OF PROPOSITION)) ((SENTENCE STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Retract the truth of the logical sentence `sentence' in the module named\n`module-name'.  A module name of `null' or the empty string refers to the\ncurrent module.  If no module can be found with the name `module-name',\nthen a Stella `no-such-context-exception' is thrown.\n\nReturn an iterator of the retracted propositions resulting from sentence.\")", ((cpp_function_code)(&sRetractProposition)), NULL);
    defineFunctionObject("CONCEIVE", "(DEFUN (CONCEIVE (PL-ITERATOR OF PROPOSITION)) ((SENTENCE OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Create one or more proposition objects from the sentence `sentence'\nin the  module `module'.  Return an iterator of the propositions.\nIf any of the new propositions has the same structure as an already existing\nproposition, an automatic check for duplicates will return the pre-existing\nproposition.  Multiple propositions may be returned for a single sentence\nbecause of normalization of equivalences, conjunctions, etc.\n\nSignals a `Proposition-Error' if PowerLoom could not conceive `sentence'.\")", ((cpp_function_code)(&conceive)), NULL);
    defineFunctionObject("S-CONCEIVE", "(DEFUN (S-CONCEIVE (PL-ITERATOR OF PROPOSITION)) ((SENTENCE STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Create one or more proposition objects from the sentence `sentence'\nin the  module named `module-name'.  Return an iterator of the propositions.\nIf any of the new propositions has the same structure as an already existing\nproposition, an automatic check for duplicates will return the pre-existing\nproposition.  Multiple propositions may be returned for a single sentence\nbecause of normalization of equivalences, conjunctions, etc.\n\nA module name of `null' or the empty string refers to the current module.\nIf no module can be found with the name `module-name', then a Stella\n`No-Such-Context-Exception' is thrown.\n\nSignals a `Proposition-Error' if PowerLoom could not conceive `sentence'.\")", ((cpp_function_code)(&sConceive)), NULL);
    defineFunctionObject("GET-RULES", "(DEFUN (GET-RULES (PL-ITERATOR OF PROPOSITION)) ((RELATION LOGIC-OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return rules attached to the concept/relation `relation'\nin either antecedent or consequent position.\")", ((cpp_function_code)(&getRules)), NULL);
    defineFunctionObject("S-GET-RULES", "(DEFUN (S-GET-RULES (PL-ITERATOR OF PROPOSITION)) ((RELATION-NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return rules attached to the concept/relation named\n`relation-name' found in the module named `module-name'.\nA module name of `null' or the empty string refers to the current module.\nIf no module can be found with the name `module-name', then a Stella\n`No-Such-Context-Exception' is thrown.\")", ((cpp_function_code)(&sGetRules)), NULL);
    defineFunctionObject("S-PRINT-RULES", "(DEFUN S-PRINT-RULES ((NAME STRING) (STREAM OUTPUT-STREAM) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :DOCUMENTATION \"Print rules attached to the concept/relation named `name'.\nA module name of `null' or the empty string refers to the\ncurrent module.  If no module can be found with the name `module-name',\nthen a Stella `no-such-context-exception' is thrown.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&sPrintRules)), NULL);
    defineFunctionObject("RUN-FORWARD-RULES", "(DEFUN RUN-FORWARD-RULES ((MODULE OBJECT) (LOCAL? BOOLEAN) (FORCE? BOOLEAN)) :DOCUMENTATION \"Run forward inference rules in module `module' which defaults\nto the current module.  See `run-forward-rules' command for more information.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&runForwardRules)), NULL);
    defineFunctionObject("GET-ARITY", "(DEFUN (GET-ARITY INTEGER) ((RELATION LOGIC-OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the arity of the relation `relation'.\")", ((cpp_function_code)(&getArity)), NULL);
    defineFunctionObject("S-GET-ARITY", "(DEFUN (S-GET-ARITY INTEGER) ((RELATION-NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the arity of the relation named `relation-name'.\n\n A module name of `null' or the empty string refers to the\ncurrent module.  If no module can be found with the name `module-name',\nthen a Stella `no-such-context-exception' is thrown.\")", ((cpp_function_code)(&sGetArity)), NULL);
    defineFunctionObject("GET-DOMAIN", "(DEFUN (GET-DOMAIN LOGIC-OBJECT) ((RELATION LOGIC-OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the type (a concept) for the first argument to the binary\nrelation `relation'.\")", ((cpp_function_code)(&getDomain)), NULL);
    defineFunctionObject("S-GET-DOMAIN", "(DEFUN (S-GET-DOMAIN LOGIC-OBJECT) ((RELATION-NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the type (concept) for the first argument to the binary\nrelation `relation-name'.\n\nA module name of `null' or the empty string refers to the\ncurrent module.  If no module can be found with the name `module-name',\nthen a Stella `no-such-context-exception' is thrown.\")", ((cpp_function_code)(&sGetDomain)), NULL);
    defineFunctionObject("GET-RANGE", "(DEFUN (GET-RANGE LOGIC-OBJECT) ((RELATION LOGIC-OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the type (a concept) for fillers of the binary relation\n`relation'.\")", ((cpp_function_code)(&getRange)), NULL);
    defineFunctionObject("S-GET-RANGE", "(DEFUN (S-GET-RANGE LOGIC-OBJECT) ((RELATION-NAME STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the type (a concept) for fillers of the binary relation\n`relation-name'.\n\nA module name of `null' or the empty string refers to the\ncurrent module.  If no module can be found with the name `module-name',\nthen a Stella `no-such-context-exception' is thrown.\")", ((cpp_function_code)(&sGetRange)), NULL);
    defineFunctionObject("GET-NTH-DOMAIN", "(DEFUN (GET-NTH-DOMAIN LOGIC-OBJECT) ((RELATION LOGIC-OBJECT) (N INTEGER)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the type (a concept) for the the nth argument of the\nrelation `relation'.  Counting starts at zero.  NOTE: if there are multiple\n`nth-domain' propositions for `relation', this arbitrarily returns one of them;\nit does not look for the most specific one (which might have to be created).\")", ((cpp_function_code)(&getNthDomain)), NULL);
    defineFunctionObject("S-GET-NTH-DOMAIN", "(DEFUN (S-GET-NTH-DOMAIN LOGIC-OBJECT) ((RELATION-NAME STRING) (N INTEGER) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the type (a concept) for the nth argument of the relation\nnamed `relation-name'.  Counting starts at zero.\n\nA module name of `null' or the empty string refers to the\ncurrent module.  If no module can be found with the name `module-name',\nthen a Stella `no-such-context-exception' is thrown.\")", ((cpp_function_code)(&sGetNthDomain)), NULL);
    defineFunctionObject("LOAD", "(DEFUN LOAD ((FILENAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Read logic commands from the file named `filename' and evaluate them.\nSee `load' command help for more information.\")", ((cpp_function_code)(&load)), NULL);
    defineFunctionObject("LOAD-IN-MODULE", "(DEFUN LOAD-IN-MODULE ((FILENAME STRING) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Read logic commands from the file named `filename' and evaluate them.\nBinds the `load' command's :module option to `module'.  See `load' command help for more information.\")", ((cpp_function_code)(&loadInModule)), NULL);
    defineFunctionObject("LOAD-STREAM", "(DEFUN LOAD-STREAM ((STREAM INPUT-STREAM) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Read logic commands from the STELLA stream `stream' and evaluate them.\nSee `load' command help for more information.\")", ((cpp_function_code)(&loadStream)), NULL);
    defineFunctionObject("LOAD-STREAM-IN-MODULE", "(DEFUN LOAD-STREAM-IN-MODULE ((STREAM INPUT-STREAM) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Read logic commands from the STELLA stream `stream' and evaluate them.\nBinds the `load' command's :module option to `module'.  See `load' command help for more information.\")", ((cpp_function_code)(&loadStreamInModule)), NULL);
    defineFunctionObject("LOAD-NATIVE-STREAM", "(DEFUN LOAD-NATIVE-STREAM ((STREAM NATIVE-INPUT-STREAM) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Read logic commands from the native input stream `stream' and evaluate them.\nAssumes `stream' is a line-buffered stream which is a safe compromise but does\nnot generate the best efficiency for block-buffered streams such as files.\nSee `load' command help for more information.\")", ((cpp_function_code)(&loadNativeStream)), NULL);
    defineFunctionObject("LOAD-NATIVE-STREAM-IN-MODULE", "(DEFUN LOAD-NATIVE-STREAM-IN-MODULE ((STREAM NATIVE-INPUT-STREAM) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Read logic commands from the native input stream `stream' and evaluate them.\nAssumes `stream' is a line-buffered stream which is a safe compromise but does\nnot generate the best efficiency for block-buffered streams such as files.\nBinds the `load' command's :module option to `module'.  See `load' command help for more information.\")", ((cpp_function_code)(&loadNativeStreamInModule)), NULL);
    defineFunctionObject("SAVE-MODULE", "(DEFUN SAVE-MODULE ((MODULE MODULE) (FILENAME STRING) (IFEXISTS STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Save the contents of the module `mod' into a file named `filename'.\nIf a file named `filename' already exists, then the action taken depends on the\nvalue of `ifexists'.  Possible values are \\\"ASK\\\", \\\"REPLACE\\\", \\\"WARN\\\" and \\\"ERROR\\\":\n\n  REPLACE => Means overwrite without warning.\n  WARN    => Means overwrite with a warning.\n  ERROR   => Means don't overwrite, signal an error instead.\n  ASK     => Ask the user whether to overwrite or not.  If not overwritten, an \n             exception is thrown.\")", ((cpp_function_code)(&saveModule)), NULL);
    defineFunctionObject("S-SAVE-MODULE", "(DEFUN S-SAVE-MODULE ((MODULE-NAME STRING) (FILENAME STRING) (IFEXISTS STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Save the contents of the module `module-name' into a file named `filename'.\nIf a file named `filename' already exists, then the action taken depends on the\nvalue of `ifexists'.  Possible values are \\\"ASK\\\", \\\"REPLACE\\\", \\\"WARN\\\" and \\\"ERROR\\\":\n\n  REPLACE => Means overwrite without warning.\n  WARN    => Means overwrite with a warning.\n  ERROR   => Means don't overwrite, signal an error instead.\n  ASK     => Ask the user whether to overwrite or not.  If not overwritten, an\n             exception is thrown.\n\nA module name of `null' or the empty string refers to the\ncurrent module.  If no module can be found with the name `module-name',\nthen a Stella `no-such-context-exception' is thrown.\")", ((cpp_function_code)(&sSaveModule)), NULL);
    defineFunctionObject("GET-PREDICATE", "(DEFUN (GET-PREDICATE LOGIC-OBJECT) ((PROP PROPOSITION)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the concept or relation predicate for\nthe proposition `prop'.\")", ((cpp_function_code)(&getPredicate)), NULL);
    defineFunctionObject("GET-COLUMN-COUNT", "(DEFUN (GET-COLUMN-COUNT INTEGER) ((OBJ OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Return the number of columns in `obj', which must\nbe of type proposition, skolem, cons, vector or PL-iterator.  For a proposition,\nthe number includes both the predicate and arguments. For the PL-iterator\ncase,the number of columns is for the current value of the iterator. For the\nskolem case, if the skolem is a function term, the column count of its defining\nproposition will be returned, otherwise it is treated as a non-sequence object.\n\nFor a null item, the column count is zero.\nFor non sequence objects, the column count is one.\")", ((cpp_function_code)(&getColumnCount)), NULL);
    defineFunctionObject("GET-NTH-VALUE", "(DEFUN (GET-NTH-VALUE OBJECT) ((SEQUENCE OBJECT) (N INTEGER) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return the value in the `nth' column of `sequence'.\nCounting starts at zero.  Unless `n' is zero, `sequence' must be of type\nproposition, skolem, cons, vector or PL-iterator.  A zero column number returns\na proposition's relational predicate.  For the PL-iterator case, the number\nof columns is for the current value of the iterator.   For the skolem case,\nif the skolem is a function term, the nth value of its defining proposition\nwill be returned, otherwise it is treated as a non-sequence object.\n\nAs a special case, a column number of zero will also return `sequence' itself\nif it is not one of the types enumerated above.  This is done to allow the\nuse of `get-nth-value' on PL-iterators with only a single return variable.\")", ((cpp_function_code)(&getNthValue)), NULL);
  }
}

void helpStartupPli5() {
  {
    defineFunctionObject("GET-NTH-STRING", "(DEFUN (GET-NTH-STRING STRING) ((SEQUENCE OBJECT) (N INTEGER) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return a string representation of the value in the `nth' column of\n`sequence'. Counting starts at zero.   Unless `n' is zero, `sequence' must be of type\nproposition, cons, vector or PL-iterator.  A zero column number returns\na proposition's relational predicate.  For the PL-iterator case, the\nthe current value pointed to by the iterator is used.  This will always\nsucceed, even if the `nth' value is not a string object.  In that case, a\nstring reprensentation will be returned.\n\nAs a special case, a column number of zero will also return `sequence' itself\nas a string if it is not one of the types enumerated above.  This is done to \nallow the use of `get-nth-string' on PL-iterators with only a single return variable.\")", ((cpp_function_code)(&getNthString)), NULL);
    defineFunctionObject("GET-NTH-INTEGER", "(DEFUN (GET-NTH-INTEGER INTEGER) ((SEQUENCE OBJECT) (N INTEGER) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return an integer representation of the value in the `nth' column of\n`sequence'. Counting starts at zero.   Unless `n' is zero, `sequence' must be of type\nproposition, cons, vector or PL-iterator.  A zero column number returns\na proposition's relational predicate.  For the PL-iterator case, the\nthe current value pointed to by the iterator is used.  If this is not\nan integer value, then an exception will be thrown.\n\nAs a special case, a column number of zero will also return the integer\nvalue of `sequence' itself if it is not one of the types enumerated\nabove.   This allows the use of `get-nth-integer' on PL-iterators with\nonly a single return variable.  If  `sequence' cannot be turned into an\ninteger, an exception will be thrown.\")", ((cpp_function_code)(&getNthInteger)), NULL);
    defineFunctionObject("GET-NTH-FLOAT", "(DEFUN (GET-NTH-FLOAT FLOAT) ((SEQUENCE OBJECT) (N INTEGER) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return the floating point value in the `nth' column of\n`sequence'. Counting starts at zero.  `sequence' must be of type\nproposition, cons, vector or PL-iterator.  A zero column number returns\na proposition's relational predicate.  For the PL-iterator case, the\nthe current value pointed to by the iterator is used.  If this is not\na floating point value, then an exception will be thrown.\n\nAs a special case, a column number of zero will also return the floating\npoint value of `sequence' itself if it is not one of the types enumerated\nabove.  This allows the use of `get-nth-float' on PL-iterators with only\na single return variable.    If  `sequence' cannot be turned into a floating\npoint value, an exception will be thrown.\")", ((cpp_function_code)(&getNthFloat)), NULL);
    defineFunctionObject("GET-NTH-LOGIC-OBJECT", "(DEFUN (GET-NTH-LOGIC-OBJECT LOGIC-OBJECT) ((SEQUENCE OBJECT) (N INTEGER) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Return a logic object representation of the value in the `nth' column\nof `sequence'.  Counting starts at zero.   Unless `n' is zero, `sequence' must be of type\nproposition, cons, vector or PL-iterator.  A zero column number returns\na proposition's relational predicate.  For the PL-iterator case, the\nthe current value pointed to by the iterator is used.  A zero column number\nreturns the proposition's relational predicate.  If the return value is\nnot a LOGIC-OBJECT, an exception is thrown.\n\nAs a special case, a column number of zero will also return `sequence' itself\nif it is not one of the types enumerated above.  This is done to allow the\nuse of `get-nth-value' on PL-iterators with only a single return variable.\nIf `sequence' is not a LOGIC-OBJECT, an exception is thrown.\")", ((cpp_function_code)(&getNthLogicObject)), NULL);
    defineFunctionObject("GET-ENUMERATED-COLLECTION-MEMBERS", "(DEFUN (GET-ENUMERATED-COLLECTION-MEMBERS CONS) ((COLLECTION OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Returns the members of an enumerated collection.  This works on all types\nof collection, i.e., sets and lists\")", ((cpp_function_code)(&getEnumeratedCollectionMembers)), NULL);
    defineFunctionObject("EVALUATE", "(DEFUN (EVALUATE OBJECT) ((COMMAND OBJECT) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Evaluate the command `command' within `module' and return\nthe result. Currently, only the evaluation of (possibly nested) commands and\nglobal variables is supported.  Commands are simple to program in Common Lisp,\nsince they are built into the language, and relatively awkward in Java and C++.\nUsers of either of those languages are more likely to want to call `s-evaluate'.\")", ((cpp_function_code)(&evaluate)), NULL);
    defineFunctionObject("S-EVALUATE", "(DEFUN (S-EVALUATE OBJECT) ((COMMAND STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Evaluate the command represented by the string `command' within `module' and\nreturn the result.  Currently, only the evaluation of (possibly nested) commands and\nglobal variables is supported.\n\n A module name of `null' or the empty string refers to the\ncurrent module.  If no module can be found with the name `module-name',\nthen a Stella `no-such-context-exception' is thrown.\")", ((cpp_function_code)(&sEvaluate)), NULL);
    defineFunctionObject("POWERLOOM", "(DEFUN POWERLOOM ((MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :DOCUMENTATION \"Run the PowerLoom read/eval/print loop.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&powerloom)), NULL);
    defineFunctionObject("IS-LOGIC-OBJECT", "(DEFUN (IS-LOGIC-OBJECT BOOLEAN) ((OBJ OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Test whether `obj' is of type LOGIC-OBJECT\")", ((cpp_function_code)(&isLogicObject)), NULL);
    defineFunctionObject("IS-SKOLEM", "(DEFUN (IS-SKOLEM BOOLEAN) ((OBJ OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Test whether `obj' is of type SKOLEM (which subsumes pattern variables).\")", ((cpp_function_code)(&isSkolem)), NULL);
    defineFunctionObject("IS-VARIABLE", "(DEFUN (IS-VARIABLE BOOLEAN) ((OBJ OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Test whether `obj' is of type PATTERN-VARIABLE.\")", ((cpp_function_code)(&isVariable)), NULL);
    defineFunctionObject("IS-INTEGER", "(DEFUN (IS-INTEGER BOOLEAN) ((OBJ OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Test whether `obj' is of type INTEGER\")", ((cpp_function_code)(&isInteger)), NULL);
    defineFunctionObject("IS-FLOAT", "(DEFUN (IS-FLOAT BOOLEAN) ((OBJ OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Test whether `obj' is of type FLOAT (double)\")", ((cpp_function_code)(&isFloat)), NULL);
    defineFunctionObject("IS-NUMBER", "(DEFUN (IS-NUMBER BOOLEAN) ((OBJ OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Test whether `obj' is of type NUMBER.  This can\nbe either an integer or a floating point number.  One key characteristic\nis that 'object-to-integer' and `object-to-float' will both work on it.\")", ((cpp_function_code)(&isNumber)), NULL);
    defineFunctionObject("IS-STRING", "(DEFUN (IS-STRING BOOLEAN) ((OBJ OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Test whether `obj' is of type STRING\")", ((cpp_function_code)(&isString)), NULL);
    defineFunctionObject("IS-ENUMERATED-COLLECTION", "(DEFUN (IS-ENUMERATED-COLLECTION BOOLEAN) ((OBJ OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Test whether `obj' is an enumerated collection.  This\nsubsumes both sets and lists.\")", ((cpp_function_code)(&isEnumeratedCollection)), NULL);
    defineFunctionObject("IS-ENUMERATED-SET", "(DEFUN (IS-ENUMERATED-SET BOOLEAN) ((OBJ OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Test whether `obj' is an enumerated set.\")", ((cpp_function_code)(&isEnumeratedSet)), NULL);
    defineFunctionObject("IS-ENUMERATED-LIST", "(DEFUN (IS-ENUMERATED-LIST BOOLEAN) ((OBJ OBJECT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Test whether `obj' is an enumerated list\")", ((cpp_function_code)(&isEnumeratedList)), NULL);
    defineFunctionObject("IS-TRUE", "(DEFUN (IS-TRUE BOOLEAN) ((TV TRUTH-VALUE)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Tests whether `tv' is a true truth value.  It can be true\neither absolutely or by default.\")", ((cpp_function_code)(&isTrue)), NULL);
    defineFunctionObject("IS-FALSE", "(DEFUN (IS-FALSE BOOLEAN) ((TV TRUTH-VALUE)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Tests whether `tv' is a false truth value.  It can be false\neither absolutely or by default.\")", ((cpp_function_code)(&isFalse)), NULL);
    defineFunctionObject("IS-UNKNOWN", "(DEFUN (IS-UNKNOWN BOOLEAN) ((TV TRUTH-VALUE)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Tests whether `tv' is an unknown truth value.\")", ((cpp_function_code)(&isUnknown)), NULL);
    defineFunctionObject("IS-KNOWN", "(DEFUN (IS-KNOWN BOOLEAN) ((TV TRUTH-VALUE)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Tests whether `tv' is a known truth value (i.e., true or false).\")", ((cpp_function_code)(&isKnown)), NULL);
    defineFunctionObject("IS-INCONSISTENT", "(DEFUN (IS-INCONSISTENT BOOLEAN) ((TV TRUTH-VALUE)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Tests whether `tv' is an inconsistent truth value.\")", ((cpp_function_code)(&isInconsistent)), NULL);
    defineFunctionObject("IS-STRICT", "(DEFUN (IS-STRICT BOOLEAN) ((TV TRUTH-VALUE)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Tests whether `tv' is a strict (non-default) truth value.\")", ((cpp_function_code)(&isStrict)), NULL);
    defineFunctionObject("IS-DEFAULT", "(DEFUN (IS-DEFAULT BOOLEAN) ((TV TRUTH-VALUE)) :PUBLIC? TRUE :C-CALLABLE? TRUE :DOCUMENTATION \"Tests whether `tv' is a default truth value.\")", ((cpp_function_code)(&isDefault)), NULL);
    defineFunctionObject("ASK", "(DEFUN (ASK TRUTH-VALUE) ((QUERY CONS) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :DOCUMENTATION \"Returns a truth value for `query' in `module' and `environment'.\n`query' has the same syntax as the PowerLoom `ask' command (which see)\nbut with the `ask' operator omitted.  For example, here are some legal\n`query' arguments:\n	 \n    ((happy Fred))\n    ((happy Fred) :inference-level :assertion)\n    ((happy Fred) :inference-level :assertion :timeout 1.0)\n	\nAs a convenience, a `query' argument whose first element is a symbol is\ninterpreted as a sentence that is queried without any options.  For example:\n	 \n    (happy Fred)\n	\nis a legal `query' argument.  Note that for a sentence whose relation is a list\nitself, e.g., `((FruitFn BananaTree) MyBanana)' this shortcut is not available,\nthat is, in that case an extra level of list nesting is always necessary.\nThe returned truth value represents the logical truth of the queried sentence\nas determined by PowerLoom.  It can be be tested via the functions" " `is-true',\n`is-false' and `is-unknown' (which see).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&ask)), NULL);
    defineFunctionObject("S-ASK", "(DEFUN (S-ASK TRUTH-VALUE) ((QUERY STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :DOCUMENTATION \"Returns a truth value for `query' in module `module-name' and `environment'.\n`query' has the same syntax as the PowerLoom `ask' command (which see) but\nwith the `ask' operator omitted.  Different from the PLI `ask' function, `s-ask'\ndoes not expect a top-level pair of parentheses.  For example, here are some legal\n`query' arguments:\n	 \n    \\\"(happy Fred)\\\"\n    \\\"(happy Fred) :inference-level :assertion\\\"\n    \\\"(happy Fred) :inference-level :assertion :timeout 1.0\\\"\n	\nNames in `query' will be interpreted relative to module `module-name'.\nA null `module-name' or the empty string refers to the current module.\nIf no module can be found with the name `module-name', then a STELLA\n`no-such-context-exception' is thrown.\nThe returned truth value represents the logical truth of the queried sentence\nas determined by PowerLoom.  It can be be tested via the functions `is-true',\n`is-false" "' and `is-unknown' (which see).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&sAsk)), NULL);
    defineFunctionObject("RETRIEVE", "(DEFUN (RETRIEVE PL-ITERATOR) ((QUERY CONS) (MODULE MODULE) (ENVIRONMENT ENVIRONMENT)) :DOCUMENTATION \"Returns an iterator of variable bindings that when substituted for the\nopen variables in `query' satisfy the query proposition.  The query is\nrun in `module' and relative to `environment'.  `query' has the same syntax\nas the PowerLoom `retrieve' command (which see) but with the `retrieve'\noperator omitted.    For example, here are some legal `query' arguments:\n	 \n    ((happy ?x))\n    (10 (happy ?x))\n    (all (happy ?x))\n    (all ?x (happy ?x))\n    (10 (happy ?x) :inference-level :assertion)\n    (10 (happy ?x) :inference-level :assertion :timeout 1.0)\n	\nIf there is only a single output variable (as in all the examples above)\neach element generated by the returned iterator will be a binding for\nthat variable - unless, the output variable was declared with a surrounding\npair of parentheses.  For example:\n	 \n    (all (?x) (happy ?x))\n	\nIn that case, the generated elements will be one-elemen" "t lists.  If there\nare multiple output variables, each element generated by the returned\niterator will be a list of variable bindings that can be accessed using\nthe various `get-nth-...' functions.  The list of output variables does\nnot need to be declared in which case they are taken to be the open variables\nin the query proposition in the order in which they were encountered.  If\norder does matter or should be different from its default, it can be forced\nby declaring the set of output variables.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&retrieve)), NULL);
    defineFunctionObject("S-RETRIEVE", "(DEFUN (S-RETRIEVE PL-ITERATOR) ((QUERY STRING) (MODULE-NAME STRING) (ENVIRONMENT ENVIRONMENT)) :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE :DOCUMENTATION \"Returns an iterator of variable bindings that when substituted for the\nopen variables in `query' satisfy the query proposition.  The query is\nrun in `module' and relative to `environment'.  `query' has the same syntax\nas the PowerLoom `retrieve' command (which see) but with the `retrieve'\noperator omitted.  Different from the PLI `retrieve' function, `s-retrieve'\ndoes not expect a top-level pair of parentheses.  For example, here are some\nlegal `query' arguments:\n	 \n    \\\"(happy ?x)\\\"\n    \\\"10 (happy ?x)\\\"\n    \\\"all (happy ?x)\\\"\n    \\\"all ?x (happy ?x)\\\"\n    \\\"10 (happy ?x) :inference-level :assertion\\\"\n    \\\"10 (happy ?x) :inference-level :assertion :timeout 1.0\\\"\n	\nIf there is only a single output variable (as in all the examples above)\neach element generated by the returned iterator will be a bindin" "g for\nthat variable - unless, the output variable was declared with a surrounding\npair of parentheses.  For example:\n	 \n    \\\"all (?x) (happy ?x)\\\"\n	\nIn that case, the generated elements will be one-element lists.  If there\nare multiple output variables, each element generated by the returned\niterator will be a list of variable bindings that can be accessed using\nthe various `get-nth-...' functions.  The list of output variables does\nnot need to be declared in which case they are taken to be the open variables\nin the query proposition in the order in which they were encountered.  If\norder does matter or should be different from its default, it can be forced\nby declaring the set of output variables.\n\nNames in `query' will be interpreted relative to module `module-name'.\nA null `module-name' or the empty string refers to the current module.\nIf no module can be found with the name `module-name', then a STELLA\n`no-such-context-exception' is thrown.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-" "EXCEPTIONS? TRUE)", ((cpp_function_code)(&sRetrieve)), NULL);
    defineFunctionObject("GET-FRAME-PROPOSITION", "(DEFUN (GET-FRAME-PROPOSITION PROPOSITION) ((FRAME CONTROL-FRAME)) :DOCUMENTATION \"Return the proposition currently being inferred by this control `frame'.\nThis proposition will generally have bound and/or unbound pattern variables as its arguments.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getFrameProposition)), NULL);
    defineFunctionObject("GET-FRAME-ARITY", "(DEFUN (GET-FRAME-ARITY INTEGER) ((FRAME CONTROL-FRAME)) :DOCUMENTATION \"Return the arity of the proposition currently being inferred by `frame'.\nThis will be the actual number of arguments, even if the proposition is of variable arity.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getFrameArity)), NULL);
    defineFunctionObject("GET-FRAME-ITERATOR", "(DEFUN (GET-FRAME-ITERATOR PL-ITERATOR) ((FRAME CONTROL-FRAME)) :DOCUMENTATION \"Return the iterator generating successive bindings for the proposition\nthat is currently being inferred by `frame'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getFrameIterator)), NULL);
    defineFunctionObject("SET-FRAME-ITERATOR", "(DEFUN SET-FRAME-ITERATOR ((FRAME CONTROL-FRAME) (ITERATOR PL-ITERATOR)) :DOCUMENTATION \"Set the iterator for generating successive bindings for the proposition\nthat is currently being inferred by `frame' to `iterator'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&setFrameIterator)), NULL);
    defineFunctionObject("GET-NTH-FRAME-ARGUMENT", "(DEFUN (GET-NTH-FRAME-ARGUMENT OBJECT) ((FRAME CONTROL-FRAME) (N INTEGER)) :DOCUMENTATION \"Return the `n'-th argument of the proposition that is currently being inferred\nby `frame'.  This will generally be a pattern variable that might be unbound or bound.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&getNthFrameArgument)), NULL);
    defineFunctionObject("GET-NTH-FRAME-BINDING", "(DEFUN (GET-NTH-FRAME-BINDING OBJECT) ((FRAME CONTROL-FRAME) (N INTEGER)) :DOCUMENTATION \"Return the binding of the `n'-th argument of the proposition that is currently\nbeing inferred by `frame'.  This will be NULL if the argument is unbound, otherwise, the object\nbound to the variable.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&getNthFrameBinding)), NULL);
    defineFunctionObject("SET-NTH-FRAME-BINDING", "(DEFUN (SET-NTH-FRAME-BINDING BOOLEAN) ((FRAME CONTROL-FRAME) (N INTEGER) (VALUE OBJECT)) :DOCUMENTATION \"Set the binding of the `n'-th argument of the proposition that is currently\nbeing inferred by `frame' to `value'.  If the binding was successful, that is if the argument\nwas unbound or is already bound to `binding', the function returns TRUE.  Otherwise, the\nargument will keep its current binding and FALSE will be returned.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&setNthFrameBinding)), NULL);
    defineFunctionObject("IS-FRAME-BINDING-PATTERN", "(DEFUN (IS-FRAME-BINDING-PATTERN BOOLEAN) ((FRAME CONTROL-FRAME) (PATTERN STRING)) :DOCUMENTATION \"Return TRUE if the arguments of `frame' are bound according to `pattern'.\nEach character in pattern corresponds to an argument at the particular position and  must be\neither `B' (for bound) or `_' for unbound.  The function returns TRUE if `frame' has at least\nas many arguments as `pattern' has characters and their bindings match `pattern'.  If `frame'\nhas additional arguments, they will be ignored.  If `pattern' has more positions than `frame'\nhas arguments, the function returns FALSE.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&isFrameBindingPattern)), NULL);
    defineFunctionObject("GET-FRAME-BINDING-PATTERN", "(DEFUN (GET-FRAME-BINDING-PATTERN STRING) ((FRAME CONTROL-FRAME)) :DOCUMENTATION \"Return a string representation of the argument binding pattern of `frame'.\nThe syntax of the pattern is the same as used for `is-frame-binding-pattern' (which see).\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&getFrameBindingPattern)), NULL);
    defineFunctionObject("GET-FRAME-BINDING-STATE", "(DEFUN (GET-FRAME-BINDING-STATE CONS) ((FRAME CONTROL-FRAME)) :DOCUMENTATION \"Return a frame variable binding stack state that can be used to unbind\nall frame variables to the state they were in when the binding stack state was recorded.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&getFrameBindingState)), NULL);
    defineFunctionObject("SET-FRAME-BINDING-STATE", "(DEFUN SET-FRAME-BINDING-STATE ((FRAME CONTROL-FRAME) (STATE CONS)) :DOCUMENTATION \"Reset the frame variable binding stack state to `state'.  This will set\nall frame variables to the state they were in when the binding stack state was recorded.\" :PUBLIC? TRUE :C-CALLABLE? TRUE :THROWS-EXCEPTIONS? TRUE)", ((cpp_function_code)(&setFrameBindingState)), NULL);
    defineFunctionObject("GET-PROPERTY-OBJECT", "(DEFUN (GET-PROPERTY-OBJECT OBJECT) ((PROPERTY STRING) (DEFAULTVALUE OBJECT)) :DOCUMENTATION \"Return the value of the global STELLA configuration `property'\nor `defaultValue' if it is undefined.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getPropertyObject)), NULL);
    defineFunctionObject("GET-PROPERTY-STRING", "(DEFUN (GET-PROPERTY-STRING STRING) ((PROPERTY STRING) (DEFAULTVALUE STRING)) :DOCUMENTATION \"Return the value of the global STELLA configuration `property'\nas a string or `defaultValue' if it is undefined.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getPropertyString)), NULL);
    defineFunctionObject("GET-PROPERTY", "(DEFUN (GET-PROPERTY STRING) ((PROPERTY STRING) (DEFAULTVALUE STRING)) :DOCUMENTATION \"Synonym for `get-property-string' (which see).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getProperty)), NULL);
    defineFunctionObject("GET-PROPERTY-INTEGER", "(DEFUN (GET-PROPERTY-INTEGER INTEGER) ((PROPERTY STRING) (DEFAULTVALUE INTEGER)) :DOCUMENTATION \"Return the value of the global STELLA configuration `property'\nas an integer or `defaultValue' if it is undefined.  Raises an error if the defined\nvalue is not an integer.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getPropertyInteger)), NULL);
    defineFunctionObject("GET-PROPERTY-FLOAT", "(DEFUN (GET-PROPERTY-FLOAT FLOAT) ((PROPERTY STRING) (DEFAULTVALUE FLOAT)) :DOCUMENTATION \"Return the value of the global STELLA configuration `property'\nas a float or `defaultValue' if it is undefined.  Raises an error if the defined\nvalue is not a float.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getPropertyFloat)), NULL);
    defineFunctionObject("GET-PROPERTY-BOOLEAN", "(DEFUN (GET-PROPERTY-BOOLEAN BOOLEAN) ((PROPERTY STRING) (DEFAULTVALUE BOOLEAN)) :DOCUMENTATION \"Return the value of the global STELLA configuration `property'\nas a boolean or `defaultValue' if it is undefined.  Raises an error if the defined\nvalue is not a boolean.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getPropertyBoolean)), NULL);
    defineFunctionObject("SET-PROPERTY-OBJECT", "(DEFUN SET-PROPERTY-OBJECT ((PROPERTY STRING) (VALUE OBJECT)) :DOCUMENTATION \"Set the global STELLA configuration `property' to `value'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&setPropertyObject)), NULL);
    defineFunctionObject("SET-PROPERTY-STRING", "(DEFUN SET-PROPERTY-STRING ((PROPERTY STRING) (VALUE STRING)) :DOCUMENTATION \"Set the global STELLA configuration `property' to a string `value'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&setPropertyString)), NULL);
    defineFunctionObject("SET-PROPERTY", "(DEFUN SET-PROPERTY ((PROPERTY STRING) (VALUE STRING)) :DOCUMENTATION \"Synonym for `set-property-string' (which see).\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&setProperty)), NULL);
    defineFunctionObject("SET-PROPERTY-INTEGER", "(DEFUN SET-PROPERTY-INTEGER ((PROPERTY STRING) (VALUE INTEGER)) :DOCUMENTATION \"Set the global STELLA configuration `property' to an integer `value'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&setPropertyInteger)), NULL);
    defineFunctionObject("SET-PROPERTY-FLOAT", "(DEFUN SET-PROPERTY-FLOAT ((PROPERTY STRING) (VALUE FLOAT)) :DOCUMENTATION \"Set the global STELLA configuration `property' to a float `value'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&setPropertyFloat)), NULL);
    defineFunctionObject("SET-PROPERTY-BOOLEAN", "(DEFUN SET-PROPERTY-BOOLEAN ((PROPERTY STRING) (VALUE BOOLEAN)) :DOCUMENTATION \"Set the global STELLA configuration `property' to a boolean `value'.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&setPropertyBoolean)), NULL);
    defineFunctionObject("IS-DEFINED-PROPERTY", "(DEFUN (IS-DEFINED-PROPERTY BOOLEAN) ((PROPERTY STRING)) :DOCUMENTATION \"Return TRUE if `property' has a defined value.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&isDefinedProperty)), NULL);
    defineFunctionObject("PRINT-PROPERTIES", "(DEFUN PRINT-PROPERTIES () :DOCUMENTATION \"Print all currently defined STELLA configuration properties and values.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&printProperties)), NULL);
    defineFunctionObject("GET-EXCEPTION-HANDLER", "(DEFUN (GET-EXCEPTION-HANDLER FUNCTION-CODE) () :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&getExceptionHandler)), NULL);
    defineFunctionObject("SET-EXCEPTION-HANDLER", "(DEFUN SET-EXCEPTION-HANDLER ((HANDLER FUNCTION-CODE)) :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&setExceptionHandler)), NULL);
    defineFunctionObject("REGISTER-OBJECT", "(DEFUN (REGISTER-OBJECT CONS) ((OBJECT OBJECT)) :DOCUMENTATION \"Register `object' to prevent it from being garbage-collected by the PowerLoom GC.\nThe result of registration is a handle for `object' which can later be used to unregister it.\nCurrently it is assumed that calling this immediately after an object was returned by a PLI function\nis safe; however, we might have to handle registration in PLI functions before objects are returned.\nThis is not thread safe and needs to be explicitly synchronized in a threaded environment.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&registerObject)), NULL);
    defineFunctionObject("UNREGISTER-OBJECT", "(DEFUN UNREGISTER-OBJECT ((OBJECTHANDLE CONS)) :DOCUMENTATION \"Unregister the object whose registered handle is `objectHandle' to make it available\nfor PowerLoom garbage collection.  This also is not thread safe and needs to be explicitly synchronized\nin a threaded environment.\" :PUBLIC? TRUE :C-CALLABLE? TRUE)", ((cpp_function_code)(&unregisterObject)), NULL);
    defineFunctionObject("MAIN", "(DEFUN (MAIN INTEGER) () :PUBLIC? TRUE)", ((cpp_function_code)(&main)), NULL);
    defineFunctionObject("STARTUP-PLI", "(DEFUN STARTUP-PLI () :PUBLIC? TRUE)", ((cpp_function_code)(&startupPli)), NULL);
    { MethodSlot* function = lookupFunction(SYM_PLI_PLI_STARTUP_PLI);

      setDynamicSlotValue(function->dynamicSlots, SYM_PLI_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupPli"), NULL_STRING_WRAPPER);
    }
  }
}

void helpStartupPli6() {
  {
    inModule(((StringWrapper*)(copyConsTree(wrapString("PLI")))));
    defineGlobalVariableObject("(DEFGLOBAL *POWERLOOM-INITIALIZED?* BOOLEAN FALSE)", &oPOWERLOOM_INITIALIZEDpo);
    oPOWERLOOM_INITIALIZEDpo = true;
    setDynamicSlotValue(lookupFunctionByName("INITIALIZE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_initialize))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("RESET-POWERLOOM")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_resetPowerloom))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CLEAR-CACHES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_clearCaches))), NULL_FUNCTION_CODE_WRAPPER);
    defineGlobalVariableObject("(DEFCONSTANT ASSERTION-ENV ENVIRONMENT (NEW ENVIRONMENT :LEVEL \"ASSERTION\") :PUBLIC? TRUE)", &ASSERTION_ENV);
    defineGlobalVariableObject("(DEFCONSTANT TAXONOMIC-ENV ENVIRONMENT (NEW ENVIRONMENT :LEVEL \"TAXONOMIC\") :PUBLIC? TRUE)", &TAXONOMIC_ENV);
    defineGlobalVariableObject("(DEFCONSTANT INFERENCE-ENV ENVIRONMENT (NEW ENVIRONMENT :LEVEL \"INFERENCE\") :PUBLIC? TRUE)", &INFERENCE_ENV);
    setDynamicSlotValue(lookupFunctionByName("PL-ITERATOR-VALUE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_plIteratorValue))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("PL-ITERATOR-IS-EMPTY")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_plIteratorIsEmpty))), NULL_FUNCTION_CODE_WRAPPER);
    defineGlobalVariableObject("(DEFGLOBAL EMPTY-PL-ITERATOR PL-ITERATOR (NEW PL-ITERATOR :CURSOR NIL) :PUBLIC? FALSE :DOCUMENTATION \"Iterator that generates no values.\")", &EMPTY_PL_ITERATOR);
    setDynamicSlotValue(lookupFunctionByName("CONS-TO-PL-ITERATOR")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_consToPlIterator))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LIST-TO-PL-ITERATOR")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_listToPlIterator))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("ITERATOR-TO-PL-ITERATOR")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_iteratorToPlIterator))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-CONS")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createCons))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-CONS-LIST")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createConsList))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CONS-LENGTH")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_consLength))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CONS-IS-EMPTY")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_consIsEmpty))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CONS-FIRST")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_consFirst))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CONS-REST")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_consRest))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CONS-NTH")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_consNth))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CONS-NTH-REST")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_consNthRest))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CONS-SET-FIRST")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_consSetFirst))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CONS-SET-REST")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_consSetRest))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CONS-SET-NTH")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_consSetNth))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CONS-SET-NTH-REST")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_consSetNthRest))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LIST-FIRST")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_listFirst))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LIST-REST")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_listRest))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LIST-NTH")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_listNth))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-STRING")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createString))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-STRING-WRAPPER")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createStringWrapper))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-DIRECT-STRING-WRAPPER")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createDirectStringWrapper))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-INTEGER-WRAPPER")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createIntegerWrapper))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-LONG-INTEGER-WRAPPER")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createLongIntegerWrapper))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-FLOAT-WRAPPER")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createFloatWrapper))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-BOOLEAN-WRAPPER")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createBooleanWrapper))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-KEYWORD")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getKeyword))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-SYMBOL")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getSymbol))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-OPERATOR")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getOperator))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-OBJECT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getObject))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-OBJECT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetObject))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-CONCEPT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getConcept))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-CONCEPT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetConcept))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-RELATION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getRelation))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-RELATION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetRelation))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-UNDEFINED-RELATIONS")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getUndefinedRelations))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-NAME-IN-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getNameInModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-NAME")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-SHORT-NAME")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getShortName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-SKOLEM-NAME")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getSkolemName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-SKOLEM-SHORT-NAME")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getSkolemShortName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-VARIABLE-NAME")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getVariableName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-VARIABLE-SHORT-NAME")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getVariableShortName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("OBJECT-TO-STRING")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_objectToString))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("OBJECT-TO-INTEGER")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_objectToInteger))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("OBJECT-TO-FLOAT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_objectToFloat))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("OBJECT-TO-PARSABLE-STRING")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_objectToParsableString))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-STELLA-TYPE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getStellaType))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-LOGIC-TYPE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getLogicType))), NULL_FUNCTION_CODE_WRAPPER);
  }
}

void helpStartupPli7() {
  {
    setDynamicSlotValue(lookupFunctionByName("GET-STELLA-TYPE-NAME")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getStellaTypeName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-STELLA-TYPE-SHORT-NAME")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getStellaTypeShortName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-LOGIC-TYPE-NAME")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getLogicTypeName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-LOGIC-TYPE-SHORT-NAME")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getLogicTypeShortName))), NULL_FUNCTION_CODE_WRAPPER);
    defineGlobalVariableObject("(DEFGLOBAL *LITERAL-CONCEPT* NAMED-DESCRIPTION NULL :PUBLIC? FALSE)", &oLITERAL_CONCEPTo);
    defineGlobalVariableObject("(DEFGLOBAL *STRING-CONCEPT* NAMED-DESCRIPTION NULL :PUBLIC? FALSE)", &oSTRING_CONCEPTo);
    defineGlobalVariableObject("(DEFGLOBAL *INTEGER-CONCEPT* NAMED-DESCRIPTION NULL :PUBLIC? FALSE)", &oINTEGER_CONCEPTo);
    defineGlobalVariableObject("(DEFGLOBAL *FLOAT-CONCEPT* NAMED-DESCRIPTION NULL :PUBLIC? FALSE)", &oFLOAT_CONCEPTo);
    oLITERAL_CONCEPTo = ((NamedDescription*)(sGetConcept("LITERAL", "PL-USER", NULL)));
    oSTRING_CONCEPTo = ((NamedDescription*)(sGetConcept("STRING", "PL-USER", NULL)));
    oINTEGER_CONCEPTo = ((NamedDescription*)(sGetConcept("INTEGER", "PL-USER", NULL)));
    oFLOAT_CONCEPTo = ((NamedDescription*)(sGetConcept("FLOAT", "PL-USER", NULL)));
    setDynamicSlotValue(lookupFunctionByName("STRING-TO-OBJECT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_stringToObject))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("STRING-TO-STELLA-EXPRESSION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_stringToStellaExpression))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-PROPOSITIONS")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getPropositions))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-PROPOSITIONS")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetPropositions))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-INCONSISTENT-PROPOSITIONS")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getInconsistentPropositions))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-UNARY-PROPOSITIONS")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getUnaryPropositions))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-BINARY-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getBinaryProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-BINARY-PROPOSITIONS")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getBinaryPropositions))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-INFERRED-BINARY-PROPOSITION-VALUES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getInferredBinaryPropositionValues))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-INFERRED-BINARY-PROPOSITION-VALUES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetInferredBinaryPropositionValues))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-PROPOSITIONS-OF")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getPropositionsOf))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-PROPOSITIONS-OF")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetPropositionsOf))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-PROPOSITIONS-IN-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getPropositionsInModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("IS-TRUE-UNARY-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isTrueUnaryProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("IS-TRUE-BINARY-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isTrueBinaryProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("IS-TRUE-NARY-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isTrueNaryProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-IS-TRUE-NARY-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sIsTrueNaryProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("IS-TRUE-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isTrueProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("IS-SUBRELATION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isSubrelation))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-PROPER-SUBRELATIONS")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getProperSubrelations))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-DIRECT-SUBRELATIONS")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getDirectSubrelations))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-PROPER-SUPERRELATIONS")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getProperSuperrelations))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-DIRECT-SUPERRELATIONS")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getDirectSuperrelations))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("IS-INSTANCE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isInstance))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-CONCEPT-INSTANCES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getConceptInstances))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-CONCEPT-INSTANCES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetConceptInstances))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-DIRECT-CONCEPT-INSTANCES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getDirectConceptInstances))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-DIRECT-CONCEPT-INSTANCES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetDirectConceptInstances))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-CONCEPT-INSTANCES-MATCHING-VALUE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getConceptInstancesMatchingValue))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-CONCEPT-INSTANCE-MATCHING-VALUE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getConceptInstanceMatchingValue))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-TYPES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getTypes))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-DIRECT-TYPES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getDirectTypes))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-RELATION-EXTENSION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getRelationExtension))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-RELATION-EXTENSION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetRelationExtension))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-EXISTING-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getExistingModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-CURRENT-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getCurrentModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-HOME-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getHomeModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-MODULES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getModules))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-CREATE-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sCreateModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CHANGE-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_changeModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-CHANGE-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sChangeModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CLEAR-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_clearModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-CLEAR-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sClearModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-CHILD-MODULES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getChildModules))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-CHILD-MODULES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetChildModules))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-PARENT-MODULES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getParentModules))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-PARENT-MODULES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetParentModules))), NULL_FUNCTION_CODE_WRAPPER);
  }
}

void helpStartupPli8() {
  {
    setDynamicSlotValue(lookupFunctionByName("GENERATE-UNIQUE-NAME")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_generateUniqueName))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-KEYWORD")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createKeyword))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-SYMBOL")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createSymbol))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-OBJECT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createObject))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-CREATE-OBJECT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sCreateObject))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-CONCEPT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createConcept))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-CREATE-CONCEPT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sCreateConcept))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-RELATION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createRelation))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-CREATE-RELATION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sCreateRelation))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-FUNCTION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createFunction))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-CREATE-FUNCTION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sCreateFunction))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("REGISTER-SPECIALIST-FUNCTION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_registerSpecialistFunction))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-REGISTER-SPECIALIST-FUNCTION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sRegisterSpecialistFunction))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("REGISTER-COMPUTATION-FUNCTION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_registerComputationFunction))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-REGISTER-COMPUTATION-FUNCTION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sRegisterComputationFunction))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-ENUMERATED-LIST")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createEnumeratedList))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CREATE-ENUMERATED-SET")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_createEnumeratedSet))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("DESTROY-OBJECT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_destroyObject))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-DESTROY-OBJECT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sDestroyObject))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("ASSERT-UNARY-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_assertUnaryProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("ASSERT-BINARY-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_assertBinaryProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("ASSERT-NARY-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_assertNaryProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("RETRACT-UNARY-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_retractUnaryProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("RETRACT-BINARY-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_retractBinaryProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("RETRACT-NARY-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_retractNaryProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("ASSERT-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_assertProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-ASSERT-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sAssertProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("RETRACT-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_retractProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-RETRACT-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sRetractProposition))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("CONCEIVE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_conceive))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-CONCEIVE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sConceive))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-RULES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getRules))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-RULES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetRules))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-PRINT-RULES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sPrintRules))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("RUN-FORWARD-RULES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_runForwardRules))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-ARITY")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getArity))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-ARITY")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetArity))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-DOMAIN")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getDomain))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-DOMAIN")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetDomain))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-RANGE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getRange))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-RANGE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetRange))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-NTH-DOMAIN")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getNthDomain))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-GET-NTH-DOMAIN")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sGetNthDomain))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOAD")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_load))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOAD-IN-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_loadInModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOAD-STREAM")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_loadStream))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOAD-STREAM-IN-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_loadStreamInModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOAD-NATIVE-STREAM")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_loadNativeStream))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("LOAD-NATIVE-STREAM-IN-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_loadNativeStreamInModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("SAVE-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_saveModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("S-SAVE-MODULE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sSaveModule))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-PREDICATE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getPredicate))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-COLUMN-COUNT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getColumnCount))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-NTH-VALUE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getNthValue))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-NTH-STRING")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getNthString))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-NTH-INTEGER")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getNthInteger))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-NTH-FLOAT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getNthFloat))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-NTH-LOGIC-OBJECT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getNthLogicObject))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("GET-ENUMERATED-COLLECTION-MEMBERS")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getEnumeratedCollectionMembers))), NULL_FUNCTION_CODE_WRAPPER);
    setDynamicSlotValue(lookupFunctionByName("EVALUATE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_evaluate))), NULL_FUNCTION_CODE_WRAPPER);
  }
}

void startupPli() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/PLI", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupPli1();
    }
    if (currentStartupTimePhaseP(4)) {
      { Environment* self062 = newEnvironment();

        self062->level = "ASSERTION";
        ASSERTION_ENV = self062;
      }
      { Environment* self063 = newEnvironment();

        self063->level = "TAXONOMIC";
        TAXONOMIC_ENV = self063;
      }
      { Environment* self064 = newEnvironment();

        self064->level = "INFERENCE";
        INFERENCE_ENV = self064;
      }
      { PlIterator* self065 = newPlIterator();

        self065->cursor = NIL;
        EMPTY_PL_ITERATOR = self065;
      }
      oOBJECT_REGISTRYo = newObjectRegistryList();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("ENVIRONMENT", "(DEFCLASS ENVIRONMENT (STANDARD-OBJECT) :PUBLIC? TRUE :SLOTS ((LEVEL :TYPE STRING)) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"|ENV|\" (LEVEL SELF)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newEnvironment));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessEnvironmentSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("PL-ITERATOR", "(DEFCLASS PL-ITERATOR (ITERATOR) :PUBLIC? TRUE :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :SLOTS ((CURSOR :TYPE CONS)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newPlIterator));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessPlIteratorSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("OBJECT-REGISTRY-LIST", "(DEFCLASS OBJECT-REGISTRY-LIST (LIST) :SLOTS ((REGISTRY-LENGTH :TYPE INTEGER :INITIALLY 0) (N-FREE-CELLS :TYPE INTEGER :INITIALLY 0)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newObjectRegistryList));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessObjectRegistryListSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupPli2();
      helpStartupPli3();
      helpStartupPli4();
      helpStartupPli5();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      helpStartupPli6();
      helpStartupPli7();
      helpStartupPli8();
      setDynamicSlotValue(lookupFunctionByName("S-EVALUATE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sEvaluate))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("POWERLOOM")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_powerloom))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-LOGIC-OBJECT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isLogicObject))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-SKOLEM")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isSkolem))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-VARIABLE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isVariable))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-INTEGER")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isInteger))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-FLOAT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isFloat))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-NUMBER")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isNumber))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-STRING")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isString))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-ENUMERATED-COLLECTION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isEnumeratedCollection))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-ENUMERATED-SET")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isEnumeratedSet))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-ENUMERATED-LIST")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isEnumeratedList))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-TRUE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isTrue))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-FALSE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isFalse))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-UNKNOWN")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isUnknown))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-KNOWN")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isKnown))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-INCONSISTENT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isInconsistent))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-STRICT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isStrict))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-DEFAULT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isDefault))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("ASK")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_ask))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("S-ASK")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sAsk))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("RETRIEVE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_retrieve))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("S-RETRIEVE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_sRetrieve))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("GET-FRAME-PROPOSITION")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getFrameProposition))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("GET-FRAME-ARITY")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getFrameArity))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("GET-FRAME-ITERATOR")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getFrameIterator))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("SET-FRAME-ITERATOR")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_setFrameIterator))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("GET-NTH-FRAME-ARGUMENT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getNthFrameArgument))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("GET-NTH-FRAME-BINDING")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getNthFrameBinding))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("SET-NTH-FRAME-BINDING")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_setNthFrameBinding))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-FRAME-BINDING-PATTERN")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isFrameBindingPattern))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("GET-FRAME-BINDING-PATTERN")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getFrameBindingPattern))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("GET-FRAME-BINDING-STATE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getFrameBindingState))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("SET-FRAME-BINDING-STATE")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_setFrameBindingState))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("GET-PROPERTY-OBJECT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getPropertyObject))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("GET-PROPERTY-STRING")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getPropertyString))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("GET-PROPERTY")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getProperty))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("GET-PROPERTY-INTEGER")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getPropertyInteger))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("GET-PROPERTY-FLOAT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getPropertyFloat))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("GET-PROPERTY-BOOLEAN")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getPropertyBoolean))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("SET-PROPERTY-OBJECT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_setPropertyObject))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("SET-PROPERTY-STRING")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_setPropertyString))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("SET-PROPERTY")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_setProperty))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("SET-PROPERTY-INTEGER")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_setPropertyInteger))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("SET-PROPERTY-FLOAT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_setPropertyFloat))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("SET-PROPERTY-BOOLEAN")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_setPropertyBoolean))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("IS-DEFINED-PROPERTY")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_isDefinedProperty))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("PRINT-PROPERTIES")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_printProperties))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("GET-EXCEPTION-HANDLER")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_getExceptionHandler))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("SET-EXCEPTION-HANDLER")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_setExceptionHandler))), NULL_FUNCTION_CODE_WRAPPER);
      defineGlobalVariableObject("(DEFGLOBAL *OBJECT-REGISTRY* OBJECT-REGISTRY-LIST (NEW OBJECT-REGISTRY-LIST))", &oOBJECT_REGISTRYo);
      setDynamicSlotValue(lookupFunctionByName("REGISTER-OBJECT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_registerObject))), NULL_FUNCTION_CODE_WRAPPER);
      setDynamicSlotValue(lookupFunctionByName("UNREGISTER-OBJECT")->dynamicSlots, SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE, wrapFunctionCode(((cpp_function_code)(&pli_unregisterObject))), NULL_FUNCTION_CODE_WRAPPER);
    }
  }
}

Symbol* SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE = NULL;

Surrogate* SGT_PLI_PLI_ENVIRONMENT = NULL;

Symbol* SYM_PLI_LOGIC_LEVEL = NULL;

Surrogate* SGT_PLI_PLI_PL_ITERATOR = NULL;

Symbol* SYM_PLI_STELLA_CURSOR = NULL;

Surrogate* SGT_PLI_STELLA_CONS = NULL;

Surrogate* SGT_PLI_STELLA_LIST = NULL;

Surrogate* SGT_PLI_STELLA_VECTOR = NULL;

Symbol* SYM_PLI_STELLA_NULL = NULL;

Surrogate* SGT_PLI_LOGIC_SKOLEM = NULL;

Surrogate* SGT_PLI_LOGIC_LOGIC_OBJECT = NULL;

Surrogate* SGT_PLI_STELLA_GENERALIZED_SYMBOL = NULL;

Surrogate* SGT_PLI_STELLA_MODULE = NULL;

Surrogate* SGT_PLI_STELLA_CONTEXT = NULL;

Surrogate* SGT_PLI_LOGIC_COMPUTED_PROCEDURE = NULL;

Surrogate* SGT_PLI_STELLA_LITERAL_WRAPPER = NULL;

Surrogate* SGT_PLI_LOGIC_NAMED_DESCRIPTION = NULL;

Symbol* SYM_PLI_PLI_pR = NULL;

Symbol* SYM_PLI_PLI_pI = NULL;

Symbol* SYM_PLI_PLI_pV = NULL;

Symbol* SYM_PLI_PLI_F_GET_INFERRED_BINARY_PROPOSITION_VALUES_QUERY_000 = NULL;

Symbol* SYM_PLI_LOGIC_ALL = NULL;

Symbol* SYM_PLI_LOGIC_pX = NULL;

Symbol* SYM_PLI_STELLA_AND = NULL;

Symbol* SYM_PLI_LOGIC_FAIL = NULL;

Symbol* SYM_PLI_STELLA_EXISTS = NULL;

Symbol* SYM_PLI_LOGIC_pY = NULL;

Symbol* SYM_PLI_PLI_PROPER_SUBRELATION = NULL;

Symbol* SYM_PLI_STELLA_TRUE = NULL;

Symbol* SYM_PLI_STELLA_FALSE = NULL;

Keyword* KWD_PLI_CASE_SENSITIVEp = NULL;

Keyword* KWD_PLI_SUBSET_OF = NULL;

Keyword* KWD_PLI_ERROR = NULL;

Keyword* KWD_PLI_RETRACT_TRUE = NULL;

Keyword* KWD_PLI_ASSERT_TRUE = NULL;

Surrogate* SGT_PLI_LOGIC_PROPOSITION = NULL;

Surrogate* SGT_PLI_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_PLI_PL_KERNEL_KB_NTH_DOMAIN = NULL;

Keyword* KWD_PLI_MODULE = NULL;

Surrogate* SGT_PLI_LOGIC_PATTERN_VARIABLE = NULL;

Surrogate* SGT_PLI_STELLA_INTEGER_WRAPPER = NULL;

Surrogate* SGT_PLI_STELLA_FLOAT_WRAPPER = NULL;

Surrogate* SGT_PLI_STELLA_NUMBER_WRAPPER = NULL;

Surrogate* SGT_PLI_STELLA_STRING_WRAPPER = NULL;

Symbol* SYM_PLI_STELLA_ITERATOR = NULL;

Surrogate* SGT_PLI_PLI_OBJECT_REGISTRY_LIST = NULL;

Symbol* SYM_PLI_PLI_REGISTRY_LENGTH = NULL;

Symbol* SYM_PLI_PLI_N_FREE_CELLS = NULL;

Keyword* KWD_PLI_DOCUMENTATION = NULL;

Symbol* SYM_PLI_PLI_STARTUP_PLI = NULL;

Symbol* SYM_PLI_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace pli


