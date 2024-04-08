//  -*- Mode: C++ -*-

// describe.cc

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

Object* get(Object* name, Cons* type) {
  { Cons* typespec = type;

    return (searchForObject(name, typespec->value));
  }
}

Object* getEvaluatorWrapper(Cons* arguments) {
  return (get(arguments->value, arguments->rest));
}

Object* Object::getObject(Object* type) {
  { Object* self = this;

    return (searchForObject(self, type));
  }
}

Object* stringGetObject(const char* self, Object* type) {
  { StringWrapper* wrappedstring = wrapString(self);
    Object* object = searchForObject(wrappedstring, type);

    wrappedstring->free();
    return (object);
  }
}

Object* integerGetObject(int self, Object* type) {
  { IntegerWrapper* wrappedinteger = wrapInteger(self);
    Object* object = searchForObject(wrappedinteger, type);

    wrappedinteger->free();
    return (object);
  }
}

// Table of functions (keyed by type of object returned) that can
// be called to search for an object identified by a string.
KeyValueList* oSTRING_TO_OBJECT_FUNCTIONSo = NULL;

// List of functions that can be called to search for
// an object identified by an integer.
List* oINTEGER_TO_OBJECT_FUNCTIONSo = NULL;

Object* stringSearchForObject(const char* string, Surrogate* classtype) {
  { Object* object = NULL;

    { Surrogate* type = NULL;
      CodeWrapper* fn = NULL;
      KvCons* iter000 = oSTRING_TO_OBJECT_FUNCTIONSo->theKvList;

      for  (; ((boolean)(iter000)); 
            iter000 = iter000->rest) {
        type = ((Surrogate*)(iter000->key));
        fn = ((CodeWrapper*)(iter000->value));
        if ((!((boolean)(classtype))) ||
            subtypeOfP(type, classtype)) {
          if (subtypeOfP(safePrimaryType(fn), SGT_DESCRIBE_STELLA_FUNCTION_CODE_WRAPPER)) {
            { CodeWrapper* fn000 = fn;
              FunctionCodeWrapper* fn = ((FunctionCodeWrapper*)(fn000));

              object = ((Object*  (*) (const char*))fn->wrapperValue)(string);
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << safePrimaryType(fn) << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
          if (((boolean)(object))) {
            return (object);
          }
        }
      }
    }
    return (NULL);
  }
}

Object* searchForObject(Object* self, Object* typeref) {
  // If `self' is a string or a symbol, search for an object named
  // `self' of type `type'.  Otherwise, if `self' is an object, return it.
  { Surrogate* classtype = NULL;

    if (((boolean)(typeref))) {
      { Surrogate* testValue000 = safePrimaryType(typeref);

        if (subtypeOfSymbolP(testValue000)) {
          { Object* typeref000 = typeref;
            Symbol* typeref = ((Symbol*)(typeref000));

            classtype = lookupSurrogateInModule(typeref->symbolName, ((Module*)(typeref->homeContext)), false);
          }
        }
        else if (subtypeOfSurrogateP(testValue000)) {
          { Object* typeref001 = typeref;
            Surrogate* typeref = ((Surrogate*)(typeref001));

            classtype = typeref;
          }
        }
        else if (subtypeOfStringP(testValue000)) {
          { Object* typeref002 = typeref;
            StringWrapper* typeref = ((StringWrapper*)(typeref002));

            classtype = lookupSurrogate(typeref->wrapperValue);
          }
        }
        else if (subtypeOfClassP(testValue000)) {
          { Object* typeref003 = typeref;
            Class* typeref = ((Class*)(typeref003));

            classtype = typeref->classType;
          }
        }
        else {
          std::cout << "Invalid type reference: " << "`" << typeref << "'" << std::endl;
        }
      }
      if (((boolean)(classtype)) &&
          ((!((boolean)(classtype->surrogateValue))) ||
           (!isaP(classtype->surrogateValue, SGT_DESCRIBE_STELLA_CLASS)))) {
        std::cout << "No class exists with name: " << "`" << classtype->symbolName << "'" << std::endl;
        classtype = NULL;
      }
    }
    { Surrogate* testValue001 = safePrimaryType(self);

      if (subtypeOfStringP(testValue001)) {
        { Object* self000 = self;
          StringWrapper* self = ((StringWrapper*)(self000));

          { const char* string = self->wrapperValue;
            Object* object = stringSearchForObject(string, classtype);
            Module* module = NULL;

            if ((!((boolean)(object))) &&
                qualifiedStellaNameP(string)) {
              module = computeModuleAndBareName(string, string);
              object = stringSearchForObject(string, classtype);
            }
            if (!((boolean)(object))) {
              string = stringUpcase(string);
              object = stringSearchForObject(string, classtype);
            }
            return (object);
          }
        }
      }
      else if (subtypeOfSymbolP(testValue001)) {
        { Object* self001 = self;
          Symbol* self = ((Symbol*)(self001));

          return (searchForObject(wrapString(self->symbolName), classtype));
        }
      }
      else if (subtypeOfIntegerP(testValue001)) {
        { Object* self002 = self;
          IntegerWrapper* self = ((IntegerWrapper*)(self002));

          { int integer = self->wrapperValue;
            Object* object = NULL;

            { CodeWrapper* fn = NULL;
              Cons* iter000 = oINTEGER_TO_OBJECT_FUNCTIONSo->theConsList;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                fn = ((CodeWrapper*)(iter000->value));
                if (subtypeOfP(safePrimaryType(fn), SGT_DESCRIBE_STELLA_FUNCTION_CODE_WRAPPER)) {
                  { CodeWrapper* fn000 = fn;
                    FunctionCodeWrapper* fn = ((FunctionCodeWrapper*)(fn000));

                    object = ((Object*  (*) (int))fn->wrapperValue)(integer);
                  }
                }
                else {
                  { OutputStringStream* stream000 = newOutputStringStream();

                    *(stream000->nativeStream) << "`" << safePrimaryType(fn) << "'" << " is not a valid case option";
                    throw *newStellaException(stream000->theStringReader());
                  }
                }
                if (((boolean)(object))) {
                  return (object);
                }
              }
            }
            return (NULL);
          }
        }
      }
      else if (subtypeOfP(testValue001, SGT_DESCRIBE_STELLA_OBJECT)) {
        { Object* self003 = self;
          Object* self = self003;

          return (self);
        }
      }
      else {
        return (NULL);
      }
    }
  }
}

boolean filterStringToClassP(Class* self, AllPurposeIterator* iterator) {
  if (iterator->iteratorInteger == 1) {
    return (stringEqlP(className(self), ((StringWrapper*)(iterator->iteratorObject))->wrapperValue));
  }
  else {
    return (stringSearch(className(self), ((StringWrapper*)(iterator->iteratorObject))->wrapperValue, 0) != NULL_INTEGER);
  }
}

Iterator* stringToClasses(const char* string, boolean exactP) {
  { AllPurposeIterator* iterator = newAllPurposeIterator();

    iterator->iteratorNestedIterator = allClasses(NULL, false);
    iterator->iteratorFilterCode = ((cpp_function_code)(&filterStringToClassP));
    iterator->iteratorNextCode = ((cpp_function_code)(&filteredNestedIteratorNextP));
    iterator->iteratorObject = wrapString(string);
    iterator->iteratorInteger = (exactP ? 1 : 0);
    return (iterator);
  }
}

Object* stringToClass(const char* string) {
  return (stringGetStellaClass(string, false));
}

Object* stringToContext(const char* string) {
  try {
    return (stringGetStellaContextSlowly(string));
  }
  catch (NoSuchContextException ) {
    return (NULL);
  }
}

Object* stringToFunction(const char* string) {
  return (lookupFunctionByName(string));
}

boolean dottedStringP(const char* string) {
  return (stringPosition(string, '.', 0) != NULL_INTEGER);
}

const char* yieldExplodedMethodName(const char* dottedstring, const char*& _Return1) {
  { int dotposition = stringPosition(dottedstring, '.', 0);
    const char* firststring = NULL;
    const char* secondstring = NULL;

    if (dotposition != NULL_INTEGER) {
      firststring = stringSubsequence(dottedstring, 0, dotposition);
      secondstring = stringSubsequence(dottedstring, dotposition + 1, NULL_INTEGER);
    }
    _Return1 = secondstring;
    return (firststring);
  }
}

Object* stringToSlot(const char* string) {
  if (dottedStringP(string)) {
    { const char* classstring = NULL;
      const char* slotstring = NULL;

      classstring = yieldExplodedMethodName(string, slotstring);
      { Class* clasS = stringGetStellaClass(classstring, false);
        Symbol* slotname = NULL;

        if (((boolean)(clasS))) {
          slotname = lookupSymbol(slotstring);
          if (((boolean)(slotname))) {
            return (lookupSlot(clasS, slotname));
          }
        }
      }
    }
  }
  else {
    { Symbol* symbol = lookupSymbol(string);

      if (((boolean)(symbol))) {
        return (lookupFunction(symbol));
      }
    }
  }
  return (NULL);
}

Object* stringToSurrogateValue(const char* string) {
  { Surrogate* sgt = NULL;
    Iterator* iter000 = allSurrogates(NULL, false);

    for (; iter000->nextP(); ) {
      sgt = ((Surrogate*)(iter000->value));
      if (stringEqlP(sgt->symbolName, string)) {
        return (sgt->surrogateValue);
      }
    }
  }
  return (NULL);
}

Object* stringToDemon(const char* string) {
  return (lookupDemon(string));
}

Object* integerToContext(int integer) {
  return (integerGetStellaContextSlowly(integer));
}

// Specifies the print mode for `describe' when no second
// argument is given.
Keyword* oDEFAULT_DESCRIBE_MODEo = NULL;

void describe(Object* name, Cons* mode) {
  // Print a description of an object in :verbose, :terse,
  // or :source modes.
  { Object* object = ((!((boolean)(name))) ? ((Object*)(NULL)) : name->getObject(NULL));
    Object* modespec = mode->value;
    Keyword* validmode = NULL;

    if (!((boolean)(modespec))) {
      modespec = oDEFAULT_DESCRIBE_MODEo;
    }
    if (subtypeOfP(safePrimaryType(modespec), SGT_DESCRIBE_STELLA_GENERALIZED_SYMBOL)) {
      { Object* modespec000 = modespec;
        GeneralizedSymbol* modespec = ((GeneralizedSymbol*)(modespec000));

        { const char* testValue000 = modespec->symbolName;

          if (stringEqlP(testValue000, "VERBOSE") ||
              (stringEqlP(testValue000, "TERSE") ||
               stringEqlP(testValue000, "SOURCE"))) {
            validmode = internKeyword(modespec->symbolName);
          }
          else {
          }
        }
      }
    }
    else {
    }
    if (!((boolean)(validmode))) {
      std::cout << "Valid modes (the second argument to 'describe') are " << std::endl << "   :VERBOSE, :TERSE, and :SOURCE" << std::endl;
      validmode = oDEFAULT_DESCRIBE_MODEo;
    }
    if (!((boolean)(object))) {
      std::cout << "NULL";
    }
    else {
      object->describeObject(STANDARD_OUTPUT, validmode);
    }
  }
}

void describeEvaluatorWrapper(Cons* arguments) {
  describe(arguments->value, arguments->rest);
}

void describeTersely(Object* self, OutputStream* stream) {
  *(stream->nativeStream) << self;
}

void prettyPrintStellaTree(Cons* tree, OutputStream* stream) {
  tree = ((Cons*)(consifyListsAndIterators(tree)));
  { 
    BIND_STELLA_SPECIAL(oPRINTPRETTYCODEpo, boolean, true);
    printStellaCode(tree, stream->nativeStream);
  }
}

void prettyPrintDefinitionTree(Cons* tree, OutputStream* stream) {
  tree = ((Cons*)(consifyListsAndIterators(tree)));
  { 
    BIND_STELLA_SPECIAL(oPRINTPRETTYCODEpo, boolean, true);
    printStellaDefinition(tree, stream->nativeStream);
  }
}

// Lists longer than the cutoff are truncated during
// pretty printing.
int oPRETTY_PRINT_LIST_CUTOFFo = 5;

Object* consifyListsAndIterators(Object* tree) {
  if (!((boolean)(tree))) {
    return (tree);
  }
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (testValue000 == SGT_DESCRIBE_STELLA_CONS) {
      { Object* tree000 = tree;
        Cons* tree = ((Cons*)(tree000));

        { ConsIterator* cons = tree->allocateIterator();

          for (; cons->nextP(); ) {
            cons->valueSetter(consifyListsAndIterators(cons->value));
          }
        }
        return (tree);
      }
    }
    else if (subtypeOfP(testValue000, SGT_DESCRIBE_STELLA_LIST)) {
      { Object* tree001 = tree;
        List* tree = ((List*)(tree001));

        { Cons* conslist = NIL;

          { Object* item = NULL;
            Cons* iter000 = tree->theConsList;
            int i = NULL_INTEGER;
            int iter001 = 0;
            int upperBound000 = oPRETTY_PRINT_LIST_CUTOFFo;
            boolean unboundedP000 = upperBound000 == NULL_INTEGER;
            Cons* collect000 = NULL;

            for  (; (!(iter000 == NIL)) &&
                      (unboundedP000 ||
                       (iter001 <= upperBound000)); 
                  iter000 = iter000->rest,
                  iter001 = iter001 + 1) {
              item = iter000->value;
              i = iter001;
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(((i == oPRETTY_PRINT_LIST_CUTOFFo) ? ELLIPSIS : item), NIL);
                  if (conslist == NIL) {
                    conslist = collect000;
                  }
                  else {
                    addConsToEndOfConsList(conslist, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(((i == oPRETTY_PRINT_LIST_CUTOFFo) ? ELLIPSIS : item), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
          return (conslist);
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_DESCRIBE_STELLA_ITERATOR)) {
      { Object* tree002 = tree;
        Iterator* tree = ((Iterator*)(tree002));

        { Cons* conslist = NIL;

          { Object* item = NULL;
            Iterator* iter002 = tree;
            int i = NULL_INTEGER;
            int iter003 = 0;
            int upperBound001 = oPRETTY_PRINT_LIST_CUTOFFo;
            boolean unboundedP001 = upperBound001 == NULL_INTEGER;
            Cons* collect001 = NULL;

            for  (; iter002->nextP() &&
                      (unboundedP001 ||
                       (iter003 <= upperBound001)); 
                  iter003 = iter003 + 1) {
              item = iter002->value;
              i = iter003;
              if (!((boolean)(collect001))) {
                {
                  collect001 = cons(((i == oPRETTY_PRINT_LIST_CUTOFFo) ? ELLIPSIS : item), NIL);
                  if (conslist == NIL) {
                    conslist = collect001;
                  }
                  else {
                    addConsToEndOfConsList(conslist, collect001);
                  }
                }
              }
              else {
                {
                  collect001->rest = cons(((i == oPRETTY_PRINT_LIST_CUTOFFo) ? ELLIPSIS : item), NIL);
                  collect001 = collect001->rest;
                }
              }
            }
          }
          return (conslist);
        }
      }
    }
    else {
      return (tree);
    }
  }
}

void Module::printDefinition(OutputStream* stream) {
  { Module* self = this;

    { Cons* options = ((Cons*)(readSExpressionFromString(self->stringifiedOptions)));

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream->nativeStream) << "(DEFMODULE \"" << self->moduleFullName << "\"";
        while (!(options == NIL)) {
          *(stream->nativeStream) << std::endl << "  " << options->value << " " << options->rest->value;
          options = options->nthRest(2);
        }
        *(stream->nativeStream) << ")" << std::endl;
      }
    }
  }
}

void printClassList(Iterator* self, OutputStream* stream) {
  *(stream->nativeStream) << "(";
  if (self->nextP()) {
    *(stream->nativeStream) << ((Class*)(self->value))->classType->symbolName;
  }
  while (self->nextP()) {
    *(stream->nativeStream) << " " << ((Class*)(self->value))->classType->symbolName;
  }
  *(stream->nativeStream) << ")";
}

void Slot::prettyPrintObject(OutputStream* stream) {
  { Slot* self = this;

    stream = stream;
  }
}

// List of slots containing storage-slot options
DEFINE_STELLA_SPECIAL(oSLOTOPTIONSLOTSo, Cons* , NULL);

// List of slots containing class options
DEFINE_STELLA_SPECIAL(oCLASSOPTIONSLOTSo, Cons* , NULL);

// Plist of unstringifed class options
DEFINE_STELLA_SPECIAL(oCLASSUNSTRINGIFIEDOPTIONSo, PropertyList* , NULL);

Cons* getClassOptions() {
  { Cons* result = NIL;

    { StorageSlot* slot = NULL;
      Iterator* iter000 = privateClassStorageSlots(((Class*)(SGT_DESCRIBE_STELLA_CLASS->surrogateValue)));
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        slot = ((StorageSlot*)(iter000->value));
        if (((boolean)(((Keyword*)(dynamicSlotValue(slot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD, NULL)))))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(slot, NIL);
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
              collect000->rest = cons(slot, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    { StorageSlot* slot = NULL;
      Iterator* iter001 = publicClassStorageSlots(((Class*)(SGT_DESCRIBE_STELLA_CLASS->surrogateValue)));
      Cons* collect001 = NULL;

      for  (; iter001->nextP(); ) {
        slot = ((StorageSlot*)(iter001->value));
        if (((boolean)(((Keyword*)(dynamicSlotValue(slot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD, NULL)))))) {
          if (!((boolean)(collect001))) {
            {
              collect001 = cons(slot, NIL);
              if (result == NIL) {
                result = collect001;
              }
              else {
                addConsToEndOfConsList(result, collect001);
              }
            }
          }
          else {
            {
              collect001->rest = cons(slot, NIL);
              collect001 = collect001->rest;
            }
          }
        }
      }
    }
    { StorageSlot* slot = NULL;
      Iterator* iter002 = privateClassStorageSlots(((Class*)(SGT_DESCRIBE_STELLA_RELATION->surrogateValue)));
      Cons* collect002 = NULL;

      for  (; iter002->nextP(); ) {
        slot = ((StorageSlot*)(iter002->value));
        if (((boolean)(((Keyword*)(dynamicSlotValue(slot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD, NULL)))))) {
          if (!((boolean)(collect002))) {
            {
              collect002 = cons(slot, NIL);
              if (result == NIL) {
                result = collect002;
              }
              else {
                addConsToEndOfConsList(result, collect002);
              }
            }
          }
          else {
            {
              collect002->rest = cons(slot, NIL);
              collect002 = collect002->rest;
            }
          }
        }
      }
    }
    { StorageSlot* slot = NULL;
      Iterator* iter003 = publicClassStorageSlots(((Class*)(SGT_DESCRIBE_STELLA_RELATION->surrogateValue)));
      Cons* collect003 = NULL;

      for  (; iter003->nextP(); ) {
        slot = ((StorageSlot*)(iter003->value));
        if (((boolean)(((Keyword*)(dynamicSlotValue(slot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD, NULL)))))) {
          if (!((boolean)(collect003))) {
            {
              collect003 = cons(slot, NIL);
              if (result == NIL) {
                result = collect003;
              }
              else {
                addConsToEndOfConsList(result, collect003);
              }
            }
          }
          else {
            {
              collect003->rest = cons(slot, NIL);
              collect003 = collect003->rest;
            }
          }
        }
      }
    }
    return (result);
  }
}

PropertyList* getUnstringifiedClassOptions(Class* clasS) {
  { PropertyList* theoptions = newPropertyList();

    theoptions->thePlist = ((Cons*)(readSExpressionFromString(clasS->classStringifiedSource)))->rest->rest->rest;
    return (theoptions);
  }
}

Cons* getSlotOptions() {
  { Cons* result = NIL;

    { StorageSlot* slot = NULL;
      Iterator* iter000 = privateClassStorageSlots(((Class*)(SGT_DESCRIBE_STELLA_STORAGE_SLOT->surrogateValue)));
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        slot = ((StorageSlot*)(iter000->value));
        if (((boolean)(((Keyword*)(dynamicSlotValue(slot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD, NULL)))))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(slot, NIL);
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
              collect000->rest = cons(slot, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (result);
  }
}

void prettyPrintLiteral(Object* literal, OutputStream* stream) {
  if (subtypeOfBooleanP(safePrimaryType(literal))) {
    { Object* literal000 = literal;
      BooleanWrapper* literal = ((BooleanWrapper*)(literal000));

      if (literal == TRUE_WRAPPER) {
        *(stream->nativeStream) << "TRUE";
      }
      else {
        *(stream->nativeStream) << "FALSE";
      }
    }
  }
  else {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      *(stream->nativeStream) << literal;
    }
  }
}

boolean literalEqlP(Object* x, Object* y) {
  if ((((boolean)(x)) &&
      isaP(x, SGT_DESCRIBE_STELLA_BOOLEAN_WRAPPER)) ||
      (((boolean)(y)) &&
       isaP(y, SGT_DESCRIBE_STELLA_BOOLEAN_WRAPPER))) {
    return (((!((boolean)(((BooleanWrapper*)(x))))) &&
        (!coerceWrappedBooleanToBoolean(((BooleanWrapper*)(y))))) ||
        (((!((boolean)(((BooleanWrapper*)(y))))) &&
        (!coerceWrappedBooleanToBoolean(((BooleanWrapper*)(x))))) ||
         eqlP(x, y)));
  }
  return (eqlP(x, y));
}

Object* convertToLiteral(Object* object) {
  if (!((boolean)(object))) {
    return (object);
  }
  { Surrogate* testValue000 = safePrimaryType(object);

    if (subtypeOfP(testValue000, SGT_DESCRIBE_STELLA_LITERAL_WRAPPER)) {
      { Object* object000 = object;
        LiteralWrapper* object = ((LiteralWrapper*)(object000));

        return (object);
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* object001 = object;
        Symbol* object = ((Symbol*)(object001));

        if (object == SYM_DESCRIBE_STELLA_TRUE) {
          return (TRUE_WRAPPER);
        }
        if (object == SYM_DESCRIBE_STELLA_FALSE) {
          return (FALSE_WRAPPER);
        }
        return (object);
      }
    }
    else if (subtypeOfKeywordP(testValue000)) {
      { Object* object002 = object;
        Keyword* object = ((Keyword*)(object002));

        return (object);
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* object003 = object;
        Surrogate* object = ((Surrogate*)(object003));

        return (object);
      }
    }
    else {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "`convert-to-literal': Can't handle non-boolean literals" << std::endl;
      return (NULL);
    }
  }
}

void prettyPrintClassOptions(Class* clasS, OutputStream* stream) {
  { Object* optionvalue = NULL;

    { StorageSlot* optionslot = NULL;
      Cons* iter000 = oCLASSOPTIONSLOTSo;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        optionslot = ((StorageSlot*)(iter000->value));
        optionvalue = readSlotValue(clasS, optionslot);
        if (!((boolean)(optionvalue))) {
          continue;
        }
        { Surrogate* testValue000 = safePrimaryType(optionvalue);

          if (subtypeOfP(testValue000, SGT_DESCRIBE_STELLA_LITERAL_WRAPPER)) {
            { Object* optionvalue000 = optionvalue;
              LiteralWrapper* optionvalue = ((LiteralWrapper*)(optionvalue000));

              if (!(literalEqlP(convertToLiteral(dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_INITIAL_VALUE, NULL)), optionvalue) ||
                  literalEqlP(convertToLiteral(optionslot->defaultForm()), optionvalue))) {
                *(stream->nativeStream) << std::endl << "  :" << stringDowncase(((Keyword*)(dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD, NULL)))->symbolName) << " ";
                prettyPrintLiteral(optionvalue, stream);
              }
            }
          }
          else if (subtypeOfSymbolP(testValue000)) {
            { Object* optionvalue001 = optionvalue;
              Symbol* optionvalue = ((Symbol*)(optionvalue001));

              if (!(literalEqlP(convertToLiteral(dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_INITIAL_VALUE, NULL)), optionvalue) ||
                  literalEqlP(convertToLiteral(optionslot->defaultForm()), optionvalue))) {
                *(stream->nativeStream) << std::endl << "  :" << stringDowncase(((Keyword*)(dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD, NULL)))->symbolName) << " ";
                prettyPrintLiteral(optionvalue, stream);
              }
            }
          }
          else if (subtypeOfKeywordP(testValue000)) {
            { Object* optionvalue002 = optionvalue;
              Keyword* optionvalue = ((Keyword*)(optionvalue002));

              if (!(literalEqlP(convertToLiteral(dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_INITIAL_VALUE, NULL)), optionvalue) ||
                  literalEqlP(convertToLiteral(optionslot->defaultForm()), optionvalue))) {
                *(stream->nativeStream) << std::endl << "  :" << stringDowncase(((Keyword*)(dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD, NULL)))->symbolName) << " ";
                prettyPrintLiteral(optionvalue, stream);
              }
            }
          }
          else if (subtypeOfSurrogateP(testValue000)) {
            { Object* optionvalue003 = optionvalue;
              Surrogate* optionvalue = ((Surrogate*)(optionvalue003));

              if (!(literalEqlP(convertToLiteral(dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_INITIAL_VALUE, NULL)), optionvalue) ||
                  literalEqlP(convertToLiteral(optionslot->defaultForm()), optionvalue))) {
                *(stream->nativeStream) << std::endl << "  :" << stringDowncase(((Keyword*)(dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD, NULL)))->symbolName) << " ";
                prettyPrintLiteral(optionvalue, stream);
              }
            }
          }
          else if (subtypeOfP(testValue000, SGT_DESCRIBE_STELLA_LIST)) {
            { Object* optionvalue004 = optionvalue;
              List* optionvalue = ((List*)(optionvalue004));

              if (!(optionvalue->emptyP() ||
                  ((dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_INITIAL_VALUE, NULL) == optionvalue) ||
                   (optionslot->defaultForm() == optionvalue)))) {
                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  BIND_STELLA_SPECIAL(oPRINTPRETTYpo, boolean, true);
                  *(stream->nativeStream) << std::endl << "  :" << stringDowncase(((Keyword*)(dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD, NULL)))->symbolName) << " ";
                  *(stream->nativeStream) << oCLASSUNSTRINGIFIEDOPTIONSo->lookup(((Keyword*)(dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD, NULL))));
                }
              }
            }
          }
          else if (testValue000 == SGT_DESCRIBE_STELLA_CONS) {
            { Object* optionvalue005 = optionvalue;
              Cons* optionvalue = ((Cons*)(optionvalue005));

              if (!((optionvalue == NIL) ||
                  ((dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_INITIAL_VALUE, NULL) == optionvalue) ||
                   (optionslot->defaultForm() == optionvalue)))) {
                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  BIND_STELLA_SPECIAL(oPRINTPRETTYpo, boolean, true);
                  *(stream->nativeStream) << std::endl << "  :" << stringDowncase(((Keyword*)(dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD, NULL)))->symbolName) << " ";
                  *(stream->nativeStream) << optionvalue;
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
}

void prettyPrintSlotOptions(StorageSlot* slot, OutputStream* stream) {
  { Object* slotvalue = NULL;

    { StorageSlot* optionslot = NULL;
      Cons* iter000 = oSLOTOPTIONSLOTSo;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        optionslot = ((StorageSlot*)(iter000->value));
        slotvalue = readSlotValue(slot, optionslot);
        if (!((boolean)(slotvalue))) {
          continue;
        }
        if (subtypeOfP(safePrimaryType(slotvalue), SGT_DESCRIBE_STELLA_LITERAL_WRAPPER)) {
          { Object* slotvalue000 = slotvalue;
            LiteralWrapper* slotvalue = ((LiteralWrapper*)(slotvalue000));

            if (!literalEqlP(dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_INITIAL_VALUE, NULL), slotvalue)) {
              *(stream->nativeStream) << " :" << stringDowncase(((Keyword*)(dynamicSlotValue(optionslot->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD, NULL)))->symbolName) << " ";
              prettyPrintLiteral(slotvalue, stream);
            }
          }
        }
        else {
        }
      }
    }
  }
}

void StorageSlot::prettyPrintObject(OutputStream* stream) {
  { StorageSlot* self = this;

    *(stream->nativeStream) << "(" << stringDowncase(self->slotName->symbolName) << " :type ";
    *(stream->nativeStream) << ((((boolean)(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_TYPE_SPECIFIER, NULL))))) ? stringify(yieldTypeSpecTree(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_TYPE_SPECIFIER, NULL))))) : stringify(yieldTypeSpecTree(self->slotBaseType))));
    prettyPrintSlotOptions(self, stream);
    *(stream->nativeStream) << ")";
  }
}

void prettyPrintMethodParameters(OutputStream* stream, MethodSlot* method) {
  { int lastargindex = (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_DESCRIBE_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue ? method->methodParameterNames_reader()->length() : -1);

    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      *(stream->nativeStream) << "(";
      { Symbol* parameter = NULL;
        Cons* iter000 = method->methodParameterNames_reader()->theConsList;
        StandardObject* tspec = NULL;
        Cons* iter001 = method->methodParameterTypeSpecifiers_reader()->theConsList;
        int i = NULL_INTEGER;
        int iter002 = 1;

        for  (; (!(iter000 == NIL)) &&
                  (!(iter001 == NIL)); 
              iter000 = iter000->rest,
              iter001 = iter001->rest,
              iter002 = iter002 + 1) {
          parameter = ((Symbol*)(iter000->value));
          tspec = ((StandardObject*)(iter001->value));
          i = iter002;
          if (i > 1) {
            *(stream->nativeStream) << " ";
          }
          if (i == lastargindex) {
            *(stream->nativeStream) << "&rest ";
            tspec = variableArgumentsType(method);
          }
          *(stream->nativeStream) << "(" << stringDowncase(parameter->symbolName) << " " << yieldTypeSpecTree(tspec) << ")";
        }
      }
      *(stream->nativeStream) << ")";
    }
  }
}

void MethodSlot::prettyPrintObject(OutputStream* stream) {
  { MethodSlot* self = this;

    *(stream->nativeStream) << "(" << stringDowncase(self->slotName->symbolName) << " ";
    prettyPrintMethodParameters(stream, self);
    *(stream->nativeStream) << " :type ";
    *(stream->nativeStream) << ((((boolean)(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_TYPE_SPECIFIER, NULL))))) ? stringify(yieldTypeSpecTree(((CompoundTypeSpecifier*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_TYPE_SPECIFIER, NULL))))) : stringify(yieldTypeSpecTree(self->slotBaseType))));
    *(stream->nativeStream) << ")";
  }
}

void prettyPrintSlotBlock(OutputStream* stream, Iterator* iterator, const char* slotgroup) {
  if (iterator->nextP()) {
    { Slot* slot = ((Slot*)(iterator->value));

      *(stream->nativeStream) << std::endl << "  " << slotgroup << std::endl << "  (";
      slot->prettyPrintObject(stream);
    }
  }
  else {
    return;
  }
  { Slot* slot = NULL;
    Iterator* iter000 = iterator;

    for (; iter000->nextP(); ) {
      slot = ((Slot*)(iter000->value));
      *(stream->nativeStream) << std::endl << "   ";
      slot->prettyPrintObject(stream);
    }
  }
  *(stream->nativeStream) << ")";
}

void prettyPrintSlots(Class* self, OutputStream* stream) {
  prettyPrintSlotBlock(stream, publicClassStorageSlots(self), ":public-slots");
  prettyPrintSlotBlock(stream, privateClassStorageSlots(self), ":slots");
  prettyPrintSlotBlock(stream, publicClassMethods(self), ":public-methods");
  prettyPrintSlotBlock(stream, privateClassMethods(self), ":methods");
}

void Class::prettyPrintObject(OutputStream* stream) {
  { Class* self = this;

    { 
      BIND_STELLA_SPECIAL(oSLOTOPTIONSLOTSo, Cons*, getSlotOptions());
      BIND_STELLA_SPECIAL(oCLASSOPTIONSLOTSo, Cons*, getClassOptions());
      BIND_STELLA_SPECIAL(oCLASSUNSTRINGIFIEDOPTIONSo, PropertyList*, getUnstringifiedClassOptions(self));
      *(stream->nativeStream) << "(defclass " << self->classType->symbolName << " ";
      printClassList(newTypesToClassesIterator(self->classDirectSupers->theConsList), stream);
      prettyPrintClassOptions(self, stream);
      prettyPrintSlots(self, stream);
      *(stream->nativeStream) << ")" << std::endl;
      if (classTables(self, NIL)->nextP()) {
        *(stream->nativeStream) << std::endl;
        { Table* table = NULL;
          Iterator* iter000 = classTables(self, NIL);

          for (; iter000->nextP(); ) {
            table = ((Table*)(iter000->value));
            table->prettyPrintObject(stream);
            *(stream->nativeStream) << std::endl;
          }
        }
        *(stream->nativeStream) << std::endl;
      }
    }
  }
}

void Object::describeObject(OutputStream* stream, Keyword* mode) {
  // Prints a description of 'self' to stream 'stream'.  'mode'
  // can be :terse, :verbose, or :source.  The :terse mode is often equivalent
  // to the standard print function.
  { Object* self = this;

    mode = mode;
    describeTersely(self, stream);
  }
}

void Class::describeObject(OutputStream* stream, Keyword* mode) {
  { Class* self = this;

    if (mode == KWD_DESCRIBE_SOURCE) {
      prettyPrintDefinitionTree(((Cons*)(readSExpressionFromString(self->classStringifiedSource))), stream);
    }
    else if (mode == KWD_DESCRIBE_TERSE) {
      describeTersely(self, stream);
    }
    else if (mode == KWD_DESCRIBE_VERBOSE) {
      *(stream->nativeStream) << "SOURCE mode:" << std::endl;
      self->describeObject(stream, KWD_DESCRIBE_SOURCE);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << mode << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

void StorageSlot::describeObject(OutputStream* stream, Keyword* mode) {
  { StorageSlot* self = this;

    if (mode == KWD_DESCRIBE_SOURCE) {
      *(stream->nativeStream) << "TERSE mode:" << std::endl;
      self->describeObject(stream, KWD_DESCRIBE_TERSE);
    }
    else if (mode == KWD_DESCRIBE_TERSE) {
      describeTersely(self, stream);
    }
    else if (mode == KWD_DESCRIBE_VERBOSE) {
      prettyPrintDefinitionTree(listO(3, SYM_DESCRIBE_STELLA_SLOT, self->slotName, listO(3, KWD_DESCRIBE_OWNER, wrapString(self->slotOwner->symbolName), listO(3, KWD_DESCRIBE_TYPE, self->slotBaseType, listO(3, KWD_DESCRIBE_INITIALLY, dynamicSlotValue(self->dynamicSlots, SYM_DESCRIBE_STELLA_SLOT_INITIAL_VALUE, NULL), NIL)))), stream);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << mode << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

void Module::describeObject(OutputStream* stream, Keyword* mode) {
  { Module* self = this;

    if (mode == KWD_DESCRIBE_SOURCE) {
      prettyPrintStellaTree(((Cons*)(readSExpressionFromString(xmoduleStringifiedSource(self)))), stream);
    }
    else if (mode == KWD_DESCRIBE_TERSE) {
      describeTersely(self, stream);
    }
    else if (mode == KWD_DESCRIBE_VERBOSE) {
      prettyPrintDefinitionTree(listO(3, SYM_DESCRIBE_STELLA_DEFMODULE, wrapString(self->moduleName), listO(3, KWD_DESCRIBE_INCLUDES, self->parentModules, listO(3, KWD_DESCRIBE_USES, self->uses, listO(3, KWD_DESCRIBE_SHADOWS, self->shadowedSurrogates_reader(), listO(4, SYM_DESCRIBE_STELLA_gg_INFERRED_SLOTS, KWD_DESCRIBE_CHILDREN, self->childContexts, listO(3, KWD_DESCRIBE_USED_BY, self->usedBy, listO(3, KWD_DESCRIBE_CARDINAL_MODULE, self->cardinalModule, NIL))))))), stream);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << mode << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

const char* xmoduleStringifiedSource(Module* self) {
  return (stringConcatenate("(defmodule ", stringConcatenate(self->moduleName, stringConcatenate(" ", stringConcatenate(self->stringifiedOptions, ")", 0), 0), 0), 0));
}

const char* shortDocumentation(const char* documentation) {
  { int lineend = NULL_INTEGER;
    int sentenceend = NULL_INTEGER;

    if (documentation == NULL) {
      documentation = "Not documented.";
    }
    lineend = stringPosition(documentation, '\r', 0);
    if (lineend == NULL_INTEGER) {
      lineend = stringPosition(documentation, '\n', 0);
    }
    if (lineend == NULL_INTEGER) {
      return (documentation);
    }
    if (stringMemberP(".!", documentation[(lineend - 1)])) {
      return (stringSubsequence(documentation, 0, lineend));
    }
    sentenceend = stringPosition(documentation, '.', 0);
    if ((sentenceend != NULL_INTEGER) &&
        (sentenceend <= 155)) {
      return (stringSubsequence(documentation, 0, sentenceend + 1));
    }
    else {
      return (stringSubsequence(documentation, 0, lineend));
    }
  }
}

void printDocumentationString(const char* string, int indent, OutputStream* stream) {
  if (indent == NULL_INTEGER) {
    indent = 0;
  }
  { const char* line = NULL;
    LineIterator* iter000 = lines(makeTokenizerStringStream(string));

    for (; iter000->nextP(); ) {
      line = iter000->value;
      { int i = NULL_INTEGER;
        int iter001 = 1;
        int upperBound000 = indent;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter001 <= upperBound000); 
              iter001 = iter001 + 1) {
          i = iter001;
          i = i;
          *(stream->nativeStream) << " ";
        }
      }
      *(stream->nativeStream) << line << std::endl;
    }
  }
}

void MethodSlot::printDocumentation(OutputStream* stream, boolean shortP) {
  { MethodSlot* self = this;

    if (!((boolean)(stream))) {
      stream = STANDARD_OUTPUT;
    }
    { const char* documentation = ((StringWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIBE_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue;

      *(stream->nativeStream) << self->slotName;
      if (!(shortP)) {
        *(stream->nativeStream) << " ";
        prettyPrintMethodParameters(stream, self);
      }
      *(stream->nativeStream) << ":" << std::endl;
      printDocumentationString((shortP ? shortDocumentation(documentation) : documentation), 2, stream);
    }
  }
}

void helpStartupDescribe1() {
  {
    SGT_DESCRIBE_STELLA_FUNCTION_CODE_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("FUNCTION-CODE-WRAPPER", NULL, 1)));
    SGT_DESCRIBE_STELLA_CLASS = ((Surrogate*)(internRigidSymbolWrtModule("CLASS", NULL, 1)));
    SGT_DESCRIBE_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
    SGT_DESCRIBE_STELLA_CONTEXT = ((Surrogate*)(internRigidSymbolWrtModule("CONTEXT", NULL, 1)));
    SGT_DESCRIBE_STELLA_METHOD_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-SLOT", NULL, 1)));
    SGT_DESCRIBE_STELLA_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("SLOT", NULL, 1)));
    SGT_DESCRIBE_STELLA_DEMON = ((Surrogate*)(internRigidSymbolWrtModule("DEMON", NULL, 1)));
    KWD_DESCRIBE_VERBOSE = ((Keyword*)(internRigidSymbolWrtModule("VERBOSE", NULL, 2)));
    SGT_DESCRIBE_STELLA_GENERALIZED_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("GENERALIZED-SYMBOL", NULL, 1)));
    SGT_DESCRIBE_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SGT_DESCRIBE_STELLA_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", NULL, 1)));
    SGT_DESCRIBE_STELLA_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("ITERATOR", NULL, 1)));
    SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD = ((Symbol*)(internRigidSymbolWrtModule("SLOT-OPTION-KEYWORD", NULL, 0)));
    SGT_DESCRIBE_STELLA_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("RELATION", NULL, 1)));
    SGT_DESCRIBE_STELLA_STORAGE_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("STORAGE-SLOT", NULL, 1)));
    SGT_DESCRIBE_STELLA_BOOLEAN_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN-WRAPPER", NULL, 1)));
    SGT_DESCRIBE_STELLA_LITERAL_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL-WRAPPER", NULL, 1)));
    SYM_DESCRIBE_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    SYM_DESCRIBE_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    SYM_DESCRIBE_STELLA_SLOT_INITIAL_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SLOT-INITIAL-VALUE", NULL, 0)));
    SYM_DESCRIBE_STELLA_SLOT_TYPE_SPECIFIER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-TYPE-SPECIFIER", NULL, 0)));
    SYM_DESCRIBE_STELLA_METHOD_VARIABLE_ARGUMENTSp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-VARIABLE-ARGUMENTS?", NULL, 0)));
    KWD_DESCRIBE_SOURCE = ((Keyword*)(internRigidSymbolWrtModule("SOURCE", NULL, 2)));
    KWD_DESCRIBE_TERSE = ((Keyword*)(internRigidSymbolWrtModule("TERSE", NULL, 2)));
    SYM_DESCRIBE_STELLA_SLOT = ((Symbol*)(internRigidSymbolWrtModule("SLOT", NULL, 0)));
    KWD_DESCRIBE_OWNER = ((Keyword*)(internRigidSymbolWrtModule("OWNER", NULL, 2)));
    KWD_DESCRIBE_TYPE = ((Keyword*)(internRigidSymbolWrtModule("TYPE", NULL, 2)));
    KWD_DESCRIBE_INITIALLY = ((Keyword*)(internRigidSymbolWrtModule("INITIALLY", NULL, 2)));
    SYM_DESCRIBE_STELLA_DEFMODULE = ((Symbol*)(internRigidSymbolWrtModule("DEFMODULE", NULL, 0)));
    KWD_DESCRIBE_INCLUDES = ((Keyword*)(internRigidSymbolWrtModule("INCLUDES", NULL, 2)));
    KWD_DESCRIBE_USES = ((Keyword*)(internRigidSymbolWrtModule("USES", NULL, 2)));
    KWD_DESCRIBE_SHADOWS = ((Keyword*)(internRigidSymbolWrtModule("SHADOWS", NULL, 2)));
    SYM_DESCRIBE_STELLA_gg_INFERRED_SLOTS = ((Symbol*)(internRigidSymbolWrtModule(">>_INFERRED_SLOTS", NULL, 0)));
    KWD_DESCRIBE_CHILDREN = ((Keyword*)(internRigidSymbolWrtModule("CHILDREN", NULL, 2)));
    KWD_DESCRIBE_USED_BY = ((Keyword*)(internRigidSymbolWrtModule("USED-BY", NULL, 2)));
    KWD_DESCRIBE_CARDINAL_MODULE = ((Keyword*)(internRigidSymbolWrtModule("CARDINAL-MODULE", NULL, 2)));
    SYM_DESCRIBE_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 0)));
    SYM_DESCRIBE_STELLA_STARTUP_DESCRIBE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-DESCRIBE", NULL, 0)));
    SYM_DESCRIBE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupDescribe2() {
  {
    defineFunctionObject("GET", "(DEFUN (GET OBJECT) ((NAME NAME) |&REST| (TYPE NAME)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&get)), ((cpp_function_code)(&getEvaluatorWrapper)));
    defineMethodObject("(DEFMETHOD (GET-OBJECT OBJECT) ((SELF OBJECT) (TYPE OBJECT)))", wrapMethodCode(((cpp_method_code)(&Object::getObject))), NULL);
    defineMethodObject("(DEFMETHOD (GET-OBJECT OBJECT) ((SELF STRING) (TYPE OBJECT)))", wrapFunctionCode(((cpp_function_code)(((Object*  (*) (const char*, Object*))(&stringGetObject))))), NULL);
    defineMethodObject("(DEFMETHOD (GET-OBJECT OBJECT) ((SELF INTEGER) (TYPE OBJECT)))", wrapFunctionCode(((cpp_function_code)(((Object*  (*) (int, Object*))(&integerGetObject))))), NULL);
    defineFunctionObject("STRING-SEARCH-FOR-OBJECT", "(DEFUN (STRING-SEARCH-FOR-OBJECT OBJECT) ((STRING STRING) (CLASSTYPE TYPE)))", ((cpp_function_code)(((Object*  (*) (const char*, Surrogate*))(&stringSearchForObject)))), NULL);
    defineFunctionObject("SEARCH-FOR-OBJECT", "(DEFUN (SEARCH-FOR-OBJECT OBJECT) ((SELF OBJECT) (TYPEREF OBJECT)) :DOCUMENTATION \"If `self' is a string or a symbol, search for an object named\n`self' of type `type'.  Otherwise, if `self' is an object, return it.\")", ((cpp_function_code)(&searchForObject)), NULL);
    defineFunctionObject("FILTER-STRING-TO-CLASS?", "(DEFUN (FILTER-STRING-TO-CLASS? BOOLEAN) ((SELF CLASS) (ITERATOR ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&filterStringToClassP)), NULL);
    defineFunctionObject("STRING-TO-CLASSES", "(DEFUN (STRING-TO-CLASSES (ITERATOR OF CLASS)) ((STRING STRING) (EXACT? BOOLEAN)))", ((cpp_function_code)(((Iterator*  (*) (const char*, boolean))(&stringToClasses)))), NULL);
    defineFunctionObject("STRING-TO-CLASS", "(DEFUN (STRING-TO-CLASS OBJECT) ((STRING STRING)))", ((cpp_function_code)(((Object*  (*) (const char*))(&stringToClass)))), NULL);
    defineFunctionObject("STRING-TO-CONTEXT", "(DEFUN (STRING-TO-CONTEXT OBJECT) ((STRING STRING)))", ((cpp_function_code)(((Object*  (*) (const char*))(&stringToContext)))), NULL);
    defineFunctionObject("STRING-TO-FUNCTION", "(DEFUN (STRING-TO-FUNCTION OBJECT) ((STRING STRING)))", ((cpp_function_code)(((Object*  (*) (const char*))(&stringToFunction)))), NULL);
    defineFunctionObject("DOTTED-STRING?", "(DEFUN (DOTTED-STRING? BOOLEAN) ((STRING STRING)) :PUBLIC? TRUE)", ((cpp_function_code)(&dottedStringP)), NULL);
    defineFunctionObject("YIELD-EXPLODED-METHOD-NAME", "(DEFUN (YIELD-EXPLODED-METHOD-NAME STRING STRING) ((DOTTEDSTRING STRING)))", ((cpp_function_code)(&yieldExplodedMethodName)), NULL);
    defineFunctionObject("STRING-TO-SLOT", "(DEFUN (STRING-TO-SLOT OBJECT) ((STRING STRING)) :PUBLIC? TRUE)", ((cpp_function_code)(((Object*  (*) (const char*))(&stringToSlot)))), NULL);
    defineFunctionObject("STRING-TO-SURROGATE-VALUE", "(DEFUN (STRING-TO-SURROGATE-VALUE OBJECT) ((STRING STRING)))", ((cpp_function_code)(((Object*  (*) (const char*))(&stringToSurrogateValue)))), NULL);
    defineFunctionObject("STRING-TO-DEMON", "(DEFUN (STRING-TO-DEMON OBJECT) ((STRING STRING)))", ((cpp_function_code)(((Object*  (*) (const char*))(&stringToDemon)))), NULL);
    defineFunctionObject("INTEGER-TO-CONTEXT", "(DEFUN (INTEGER-TO-CONTEXT OBJECT) ((INTEGER INTEGER)))", ((cpp_function_code)(((Object*  (*) (int))(&integerToContext)))), NULL);
    defineFunctionObject("DESCRIBE", "(DEFUN DESCRIBE ((NAME OBJECT) |&REST| (MODE OBJECT)) :DOCUMENTATION \"Print a description of an object in :verbose, :terse,\nor :source modes.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&describe)), ((cpp_function_code)(&describeEvaluatorWrapper)));
    defineFunctionObject("DESCRIBE-TERSELY", "(DEFUN DESCRIBE-TERSELY ((SELF OBJECT) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&describeTersely)), NULL);
    defineFunctionObject("PRETTY-PRINT-STELLA-TREE", "(DEFUN PRETTY-PRINT-STELLA-TREE ((TREE CONS) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&prettyPrintStellaTree)), NULL);
    defineFunctionObject("PRETTY-PRINT-DEFINITION-TREE", "(DEFUN PRETTY-PRINT-DEFINITION-TREE ((TREE CONS) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&prettyPrintDefinitionTree)), NULL);
    defineFunctionObject("CONSIFY-LISTS-AND-ITERATORS", "(DEFUN (CONSIFY-LISTS-AND-ITERATORS OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&consifyListsAndIterators)), NULL);
    defineMethodObject("(DEFMETHOD PRINT-DEFINITION ((SELF MODULE) (STREAM OUTPUT-STREAM)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Module::printDefinition))), NULL);
    defineFunctionObject("PRINT-CLASS-LIST", "(DEFUN PRINT-CLASS-LIST ((SELF (ITERATOR OF CLASS)) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printClassList)), NULL);
    defineMethodObject("(DEFMETHOD PRETTY-PRINT-OBJECT ((SELF SLOT) (STREAM OUTPUT-STREAM)))", wrapMethodCode(((cpp_method_code)(&Slot::prettyPrintObject))), NULL);
    defineFunctionObject("GET-CLASS-OPTIONS", "(DEFUN (GET-CLASS-OPTIONS (CONS OF STORAGE-SLOT)) ())", ((cpp_function_code)(&getClassOptions)), NULL);
    defineFunctionObject("GET-UNSTRINGIFIED-CLASS-OPTIONS", "(DEFUN (GET-UNSTRINGIFIED-CLASS-OPTIONS PROPERTY-LIST) ((CLASS CLASS)))", ((cpp_function_code)(&getUnstringifiedClassOptions)), NULL);
    defineFunctionObject("GET-SLOT-OPTIONS", "(DEFUN (GET-SLOT-OPTIONS (CONS OF STORAGE-SLOT)) ())", ((cpp_function_code)(&getSlotOptions)), NULL);
    defineFunctionObject("PRETTY-PRINT-LITERAL", "(DEFUN PRETTY-PRINT-LITERAL ((LITERAL OBJECT) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&prettyPrintLiteral)), NULL);
    defineFunctionObject("LITERAL-EQL?", "(DEFUN (LITERAL-EQL? BOOLEAN) ((X OBJECT) (Y OBJECT)))", ((cpp_function_code)(((boolean  (*) (Object*, Object*))(&literalEqlP)))), NULL);
    defineFunctionObject("CONVERT-TO-LITERAL", "(DEFUN (CONVERT-TO-LITERAL OBJECT) ((OBJECT OBJECT)))", ((cpp_function_code)(&convertToLiteral)), NULL);
    defineFunctionObject("PRETTY-PRINT-CLASS-OPTIONS", "(DEFUN PRETTY-PRINT-CLASS-OPTIONS ((CLASS CLASS) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&prettyPrintClassOptions)), NULL);
    defineFunctionObject("PRETTY-PRINT-SLOT-OPTIONS", "(DEFUN PRETTY-PRINT-SLOT-OPTIONS ((SLOT STORAGE-SLOT) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&prettyPrintSlotOptions)), NULL);
    defineMethodObject("(DEFMETHOD PRETTY-PRINT-OBJECT ((SELF STORAGE-SLOT) (STREAM OUTPUT-STREAM)))", wrapMethodCode(((cpp_method_code)(&StorageSlot::prettyPrintObject))), NULL);
    defineFunctionObject("PRETTY-PRINT-METHOD-PARAMETERS", "(DEFUN PRETTY-PRINT-METHOD-PARAMETERS ((STREAM OUTPUT-STREAM) (METHOD METHOD-SLOT)))", ((cpp_function_code)(&prettyPrintMethodParameters)), NULL);
    defineMethodObject("(DEFMETHOD PRETTY-PRINT-OBJECT ((SELF METHOD-SLOT) (STREAM OUTPUT-STREAM)))", wrapMethodCode(((cpp_method_code)(&MethodSlot::prettyPrintObject))), NULL);
    defineFunctionObject("PRETTY-PRINT-SLOT-BLOCK", "(DEFUN PRETTY-PRINT-SLOT-BLOCK ((STREAM OUTPUT-STREAM) (ITERATOR (ITERATOR OF SLOT)) (SLOTGROUP STRING)))", ((cpp_function_code)(&prettyPrintSlotBlock)), NULL);
    defineFunctionObject("PRETTY-PRINT-SLOTS", "(DEFUN PRETTY-PRINT-SLOTS ((SELF CLASS) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&prettyPrintSlots)), NULL);
    defineMethodObject("(DEFMETHOD PRETTY-PRINT-OBJECT ((SELF CLASS) (STREAM OUTPUT-STREAM)))", wrapMethodCode(((cpp_method_code)(&Class::prettyPrintObject))), NULL);
    defineMethodObject("(DEFMETHOD DESCRIBE-OBJECT ((SELF OBJECT) (STREAM OUTPUT-STREAM) (MODE KEYWORD)) :PUBLIC? TRUE :DOCUMENTATION \"Prints a description of 'self' to stream 'stream'.  'mode'\ncan be :terse, :verbose, or :source.  The :terse mode is often equivalent\nto the standard print function.\")", wrapMethodCode(((cpp_method_code)(&Object::describeObject))), NULL);
    defineMethodObject("(DEFMETHOD DESCRIBE-OBJECT ((SELF CLASS) (STREAM OUTPUT-STREAM) (MODE KEYWORD)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Class::describeObject))), NULL);
    defineMethodObject("(DEFMETHOD DESCRIBE-OBJECT ((SELF STORAGE-SLOT) (STREAM OUTPUT-STREAM) (MODE KEYWORD)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&StorageSlot::describeObject))), NULL);
    defineMethodObject("(DEFMETHOD DESCRIBE-OBJECT ((SELF MODULE) (STREAM OUTPUT-STREAM) (MODE KEYWORD)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Module::describeObject))), NULL);
    defineFunctionObject("XMODULE-STRINGIFIED-SOURCE", "(DEFUN (XMODULE-STRINGIFIED-SOURCE STRING) ((SELF MODULE)))", ((cpp_function_code)(&xmoduleStringifiedSource)), NULL);
    defineFunctionObject("SHORT-DOCUMENTATION", "(DEFUN (SHORT-DOCUMENTATION STRING) ((DOCUMENTATION STRING)) :PUBLIC? TRUE)", ((cpp_function_code)(&shortDocumentation)), NULL);
    defineFunctionObject("PRINT-DOCUMENTATION-STRING", "(DEFUN PRINT-DOCUMENTATION-STRING ((STRING STRING) (INDENT INTEGER) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printDocumentationString)), NULL);
    defineMethodObject("(DEFMETHOD PRINT-DOCUMENTATION ((SELF METHOD-SLOT) (STREAM OUTPUT-STREAM) (SHORT? BOOLEAN)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&MethodSlot::printDocumentation))), NULL);
    defineFunctionObject("STARTUP-DESCRIBE", "(DEFUN STARTUP-DESCRIBE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupDescribe)), NULL);
    { MethodSlot* function = lookupFunction(SYM_DESCRIBE_STELLA_STARTUP_DESCRIBE);

      setDynamicSlotValue(function->dynamicSlots, SYM_DESCRIBE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupDescribe"), NULL_STRING_WRAPPER);
    }
  }
}

void startupDescribe() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupDescribe1();
    }
    if (currentStartupTimePhaseP(4)) {
      oSTRING_TO_OBJECT_FUNCTIONSo = newKeyValueList();
      oINTEGER_TO_OBJECT_FUNCTIONSo = list(0);
      oDEFAULT_DESCRIBE_MODEo = KWD_DESCRIBE_VERBOSE;
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupDescribe2();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *STRING-TO-OBJECT-FUNCTIONS* (KEY-VALUE-LIST OF TYPE CODE-WRAPPER) (NEW KEY-VALUE-LIST) :DOCUMENTATION \"Table of functions (keyed by type of object returned) that can\nbe called to search for an object identified by a string.\")", &oSTRING_TO_OBJECT_FUNCTIONSo);
      defineGlobalVariableObject("(DEFGLOBAL *INTEGER-TO-OBJECT-FUNCTIONS* (LIST OF CODE-WRAPPER) (LIST) :DOCUMENTATION \"List of functions that can be called to search for\nan object identified by an integer.\")", &oINTEGER_TO_OBJECT_FUNCTIONSo);
      oSTRING_TO_OBJECT_FUNCTIONSo->clear();
      oSTRING_TO_OBJECT_FUNCTIONSo->insertAt(SGT_DESCRIBE_STELLA_CLASS, wrapFunctionCode(((cpp_function_code)(((Object*  (*) (const char*))(&stringToClass))))));
      oSTRING_TO_OBJECT_FUNCTIONSo->insertAt(SGT_DESCRIBE_STELLA_CONTEXT, wrapFunctionCode(((cpp_function_code)(((Object*  (*) (const char*))(&stringToContext))))));
      oSTRING_TO_OBJECT_FUNCTIONSo->insertAt(SGT_DESCRIBE_STELLA_METHOD_SLOT, wrapFunctionCode(((cpp_function_code)(((Object*  (*) (const char*))(&stringToFunction))))));
      oSTRING_TO_OBJECT_FUNCTIONSo->insertAt(SGT_DESCRIBE_STELLA_SLOT, wrapFunctionCode(((cpp_function_code)(((Object*  (*) (const char*))(&stringToSlot))))));
      oSTRING_TO_OBJECT_FUNCTIONSo->insertAt(SGT_DESCRIBE_STELLA_OBJECT, wrapFunctionCode(((cpp_function_code)(((Object*  (*) (const char*))(&stringToSurrogateValue))))));
      oSTRING_TO_OBJECT_FUNCTIONSo->insertAt(SGT_DESCRIBE_STELLA_DEMON, wrapFunctionCode(((cpp_function_code)(((Object*  (*) (const char*))(&stringToDemon))))));
      oINTEGER_TO_OBJECT_FUNCTIONSo->insert(wrapFunctionCode(((cpp_function_code)(((Object*  (*) (int))(&integerToContext))))));
      defineGlobalVariableObject("(DEFGLOBAL *DEFAULT-DESCRIBE-MODE* KEYWORD :VERBOSE :PUBLIC? TRUE :DOCUMENTATION \"Specifies the print mode for `describe' when no second\nargument is given.\")", &oDEFAULT_DESCRIBE_MODEo);
      defineGlobalVariableObject("(DEFGLOBAL *PRETTY-PRINT-LIST-CUTOFF* INTEGER 5 :PUBLIC? TRUE :DOCUMENTATION \"Lists longer than the cutoff are truncated during\npretty printing.\")", &oPRETTY_PRINT_LIST_CUTOFFo);
      defineGlobalVariableObject("(DEFSPECIAL *SLOTOPTIONSLOTS* (CONS OF STORAGE-SLOT) NULL :DOCUMENTATION \"List of slots containing storage-slot options\")", &oSLOTOPTIONSLOTSo);
      defineGlobalVariableObject("(DEFSPECIAL *CLASSOPTIONSLOTS* (CONS OF STORAGE-SLOT) NULL :DOCUMENTATION \"List of slots containing class options\")", &oCLASSOPTIONSLOTSo);
      defineGlobalVariableObject("(DEFSPECIAL *CLASSUNSTRINGIFIEDOPTIONS* PROPERTY-LIST NULL :DOCUMENTATION \"Plist of unstringifed class options\")", &oCLASSUNSTRINGIFIEDOPTIONSo);
    }
  }
}

Surrogate* SGT_DESCRIBE_STELLA_FUNCTION_CODE_WRAPPER = NULL;

Surrogate* SGT_DESCRIBE_STELLA_CLASS = NULL;

Surrogate* SGT_DESCRIBE_STELLA_OBJECT = NULL;

Surrogate* SGT_DESCRIBE_STELLA_CONTEXT = NULL;

Surrogate* SGT_DESCRIBE_STELLA_METHOD_SLOT = NULL;

Surrogate* SGT_DESCRIBE_STELLA_SLOT = NULL;

Surrogate* SGT_DESCRIBE_STELLA_DEMON = NULL;

Keyword* KWD_DESCRIBE_VERBOSE = NULL;

Surrogate* SGT_DESCRIBE_STELLA_GENERALIZED_SYMBOL = NULL;

Surrogate* SGT_DESCRIBE_STELLA_CONS = NULL;

Surrogate* SGT_DESCRIBE_STELLA_LIST = NULL;

Surrogate* SGT_DESCRIBE_STELLA_ITERATOR = NULL;

Symbol* SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD = NULL;

Surrogate* SGT_DESCRIBE_STELLA_RELATION = NULL;

Surrogate* SGT_DESCRIBE_STELLA_STORAGE_SLOT = NULL;

Surrogate* SGT_DESCRIBE_STELLA_BOOLEAN_WRAPPER = NULL;

Surrogate* SGT_DESCRIBE_STELLA_LITERAL_WRAPPER = NULL;

Symbol* SYM_DESCRIBE_STELLA_TRUE = NULL;

Symbol* SYM_DESCRIBE_STELLA_FALSE = NULL;

Symbol* SYM_DESCRIBE_STELLA_SLOT_INITIAL_VALUE = NULL;

Symbol* SYM_DESCRIBE_STELLA_SLOT_TYPE_SPECIFIER = NULL;

Symbol* SYM_DESCRIBE_STELLA_METHOD_VARIABLE_ARGUMENTSp = NULL;

Keyword* KWD_DESCRIBE_SOURCE = NULL;

Keyword* KWD_DESCRIBE_TERSE = NULL;

Symbol* SYM_DESCRIBE_STELLA_SLOT = NULL;

Keyword* KWD_DESCRIBE_OWNER = NULL;

Keyword* KWD_DESCRIBE_TYPE = NULL;

Keyword* KWD_DESCRIBE_INITIALLY = NULL;

Symbol* SYM_DESCRIBE_STELLA_DEFMODULE = NULL;

Keyword* KWD_DESCRIBE_INCLUDES = NULL;

Keyword* KWD_DESCRIBE_USES = NULL;

Keyword* KWD_DESCRIBE_SHADOWS = NULL;

Symbol* SYM_DESCRIBE_STELLA_gg_INFERRED_SLOTS = NULL;

Keyword* KWD_DESCRIBE_CHILDREN = NULL;

Keyword* KWD_DESCRIBE_USED_BY = NULL;

Keyword* KWD_DESCRIBE_CARDINAL_MODULE = NULL;

Symbol* SYM_DESCRIBE_STELLA_DOCUMENTATION = NULL;

Symbol* SYM_DESCRIBE_STELLA_STARTUP_DESCRIBE = NULL;

Symbol* SYM_DESCRIBE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
