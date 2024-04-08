//  -*- Mode: C++ -*-

// literals.cc

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

IntegerWrapper* ZERO_WRAPPER = NULL;

IntegerWrapper* ONE_WRAPPER = NULL;

BooleanWrapper* TRUE_WRAPPER = NULL;

BooleanWrapper* FALSE_WRAPPER = NULL;

IntegerWrapper* NULL_INTEGER_WRAPPER = NULL;

LongIntegerWrapper* NULL_LONG_INTEGER_WRAPPER = NULL;

FloatWrapper* NULL_FLOAT_WRAPPER = NULL;

StringWrapper* NULL_STRING_WRAPPER = NULL;

MutableStringWrapper* NULL_MUTABLE_STRING_WRAPPER = NULL;

CharacterWrapper* NULL_CHARACTER_WRAPPER = NULL;

FunctionCodeWrapper* NULL_FUNCTION_CODE_WRAPPER = NULL;

MethodCodeWrapper* NULL_METHOD_CODE_WRAPPER = NULL;

boolean Wrapper::terminateWrapperP() {
  { Wrapper* self = this;

    if ((self == NULL_LONG_INTEGER_WRAPPER) ||
        ((self == NULL_FLOAT_WRAPPER) ||
         ((self == NULL_STRING_WRAPPER) ||
          ((self == NULL_MUTABLE_STRING_WRAPPER) ||
           ((self == NULL_CHARACTER_WRAPPER) ||
            ((self == NULL_FUNCTION_CODE_WRAPPER) ||
             (self == NULL_METHOD_CODE_WRAPPER))))))) {
      return (false);
    }
    else {
      return (true);
    }
  }
}

boolean IntegerWrapper::terminateWrapperP() {
  { IntegerWrapper* self = this;

    if ((self == ZERO_WRAPPER) ||
        ((self == ONE_WRAPPER) ||
         (self == NULL_INTEGER_WRAPPER))) {
      return (false);
    }
    else {
      return (true);
    }
  }
}

// Table that holds a variety of information about literal
// types, e.g., the name of their null-wrapper, wrap-function, etc.
HashTable* oLITERAL_TYPE_INFO_TABLEo = NULL;

// List of literal types stored in '*literal-type-info-table*'.
// Maintained for iteration purposes.
List* oLITERAL_TYPESo = NULL;

Object* lookupLiteralTypeInfo(Surrogate* type, Keyword* key) {
  { KeyValueList* entry = ((KeyValueList*)(oLITERAL_TYPE_INFO_TABLEo->lookup(type)));

    if (((boolean)(entry))) {
      return (entry->lookup(key));
    }
    else {
      return (NULL);
    }
  }
}

void setLiteralTypeInfo(Surrogate* type, Keyword* key, Object* value) {
  { KeyValueList* entry = ((KeyValueList*)(oLITERAL_TYPE_INFO_TABLEo->lookup(type)));

    if (!((boolean)(entry))) {
      entry = newKeyValueList();
      oLITERAL_TYPE_INFO_TABLEo->insertAt(type, entry);
      oLITERAL_TYPESo->insertLast(type);
    }
    entry->insertAt(key, value);
  }
}

IntegerWrapper* wrapInteger(int value) {
  // Return a literal object whose value is the INTEGER 'value'.
  if (value == NULL_INTEGER) {
    return (NULL_INTEGER_WRAPPER);
  }
  else {
    switch (value) {
      case 0: 
        return (ZERO_WRAPPER);
      case 1: 
        return (ONE_WRAPPER);
      default:
        return (newIntegerWrapper(value));
    }
  }
}

int unwrapInteger(IntegerWrapper* wrapper) {
  // Unwrap `wrapper' and return the result.
  // Return NULL if `wrapper' is NULL.
  if (!((boolean)(wrapper))) {
    return (NULL_INTEGER);
  }
  else {
    return (wrapper->wrapperValue);
  }
}

LongIntegerWrapper* wrapLongInteger(long long int value) {
  // Return a literal object whose value is the LONG-INTEGER 'value'.
  if (value == NULL_LONG_INTEGER) {
    return (NULL_LONG_INTEGER_WRAPPER);
  }
  else {
    return (newLongIntegerWrapper(value));
  }
}

long long int unwrapLongInteger(LongIntegerWrapper* wrapper) {
  // Unwrap `wrapper' and return the result.
  // Return NULL if `wrapper' is NULL.
  if (!((boolean)(wrapper))) {
    return (NULL_LONG_INTEGER);
  }
  else {
    return (wrapper->wrapperValue);
  }
}

NumberWrapper* wrapIntegerValue(long long int value) {
  // Return a literal object whose value is 'value'.  Choose a regular integer
  // wrapper unless `value' is too large and needs to be stored in a long wrapper.
  if ((value >= NULL_INTEGER) &&
      (value <= MOST_POSITIVE_INTEGER)) {
    { IntegerWrapper* intwrapper = new (PointerFreeGC)IntegerWrapper;

      intwrapper->wrapperValue = ((int)(value));
      return (intwrapper);
    }
  }
  else {
    { LongIntegerWrapper* longwrapper = new (PointerFreeGC)LongIntegerWrapper;

      longwrapper->wrapperValue = value;
      return (longwrapper);
    }
  }
}

FloatWrapper* wrapFloat(double value) {
  // Return a literal object whose value is the FLOAT 'value'.
  if (value == NULL_FLOAT) {
    return (NULL_FLOAT_WRAPPER);
  }
  else {
    return (newFloatWrapper(value));
  }
}

double unwrapFloat(FloatWrapper* wrapper) {
  // Unwrap `wrapper' and return the result.
  // Return NULL if `wrapper' is NULL.
  if (!((boolean)(wrapper))) {
    return (NULL_FLOAT);
  }
  else {
    return (wrapper->wrapperValue);
  }
}

StringWrapper* wrapString(const char* value) {
  // Return a literal object whose value is the STRING 'value'.
  if (value == NULL) {
    return (NULL_STRING_WRAPPER);
  }
  else {
    return (newStringWrapper(value));
  }
}

const char* unwrapString(StringWrapper* wrapper) {
  // Unwrap `wrapper' and return the result.
  // Return NULL if `wrapper' is NULL.
  if (!((boolean)(wrapper))) {
    return (NULL);
  }
  else {
    return (wrapper->wrapperValue);
  }
}

MutableStringWrapper* wrapMutableString(char* value) {
  // Return a literal object whose value is the MUTABLE-STRING 'value'.
  if (value == NULL) {
    return (NULL_MUTABLE_STRING_WRAPPER);
  }
  else {
    return (newMutableStringWrapper(value));
  }
}

char* unwrapMutableString(MutableStringWrapper* wrapper) {
  // Unwrap `wrapper' and return the result.
  // Return NULL if `wrapper' is NULL.
  if (!((boolean)(wrapper))) {
    return (NULL);
  }
  else {
    return (wrapper->wrapperValue);
  }
}

CharacterWrapper* wrapCharacter(char value) {
  // Return a literal object whose value is the CHARACTER 'value'.
  if (value == NULL_CHARACTER) {
    return (NULL_CHARACTER_WRAPPER);
  }
  else {
    return (newCharacterWrapper(value));
  }
}

char unwrapCharacter(CharacterWrapper* wrapper) {
  // Unwrap `wrapper' and return the result.
  // Return NULL if `wrapper' is NULL.
  if (!((boolean)(wrapper))) {
    return (NULL_CHARACTER);
  }
  else {
    return (wrapper->wrapperValue);
  }
}

FunctionCodeWrapper* wrapFunctionCode(cpp_function_code value) {
  // Return a literal object whose value is the FUNCTION-CODE 'value'.
  if (value == NULL) {
    return (NULL_FUNCTION_CODE_WRAPPER);
  }
  else {
    return (newFunctionCodeWrapper(value));
  }
}

cpp_function_code unwrapFunctionCode(FunctionCodeWrapper* wrapper) {
  // Unwrap `wrapper' and return the result.
  // Return NULL if `wrapper' is NULL.
  if (!((boolean)(wrapper))) {
    return (NULL);
  }
  else {
    return (wrapper->wrapperValue);
  }
}

MethodCodeWrapper* wrapMethodCode(cpp_method_code value) {
  // Return a literal object whose value is the METHOD-CODE 'value'.
  if (value == NULL) {
    return (NULL_METHOD_CODE_WRAPPER);
  }
  else {
    return (newMethodCodeWrapper(value));
  }
}

cpp_method_code unwrapMethodCode(MethodCodeWrapper* wrapper) {
  // Unwrap `wrapper' and return the result.
  // Return NULL if `wrapper' is NULL.
  if (!((boolean)(wrapper))) {
    return (((cpp_method_code)(NULL)));
  }
  else {
    return (wrapper->wrapperValue);
  }
}

BooleanWrapper* wrapBoolean(boolean value) {
  // Return a literal object whose value is the BOOLEAN 'value'.
  return ((value ? TRUE_WRAPPER : FALSE_WRAPPER));
}

boolean unwrapBoolean(BooleanWrapper* wrapper) {
  // Unwrap `wrapper' and return its values as a regular BOOLEAN.
  // Map NULL onto FALSE.
  return (wrapper == TRUE_WRAPPER);
}

boolean coerceWrappedBooleanToBoolean(BooleanWrapper* wrapper) {
  if (!((boolean)(wrapper))) {
    *(STANDARD_WARNING->nativeStream) << "Warning: " << "Coercing an undefined BOOLEAN-WRAPPER to FALSE.  Explicitly guard" << std::endl << " with `defined?' or use `unwrap-boolean' to avoid this warning." << std::endl;
  }
  return (wrapper == TRUE_WRAPPER);
}

Object* inlineWrapBoolean(Object* expression) {
  { Object* walkedexp = walkedExpressionExpression(expression);

    if (walkedexp == SYM_LITERALS_STELLA_TRUE) {
      return (SYM_LITERALS_STELLA_TRUE_WRAPPER);
    }
    else if (walkedexp == SYM_LITERALS_STELLA_FALSE) {
      return (SYM_LITERALS_STELLA_FALSE_WRAPPER);
    }
    else {
      return (listO(3, SYM_LITERALS_STELLA_WRAP_BOOLEAN, expression, NIL));
    }
  }
}

Object* inlineUnwrapBoolean(Object* expression) {
  { Object* walkedexp = walkedExpressionExpression(expression);

    if (walkedexp == SYM_LITERALS_STELLA_TRUE_WRAPPER) {
      return (SYM_LITERALS_STELLA_TRUE);
    }
    else if (walkedexp == SYM_LITERALS_STELLA_FALSE_WRAPPER) {
      return (SYM_LITERALS_STELLA_FALSE);
    }
    else {
      return (listO(3, SYM_LITERALS_STELLA_COERCE_WRAPPED_BOOLEAN_TO_BOOLEAN, expression, NIL));
    }
  }
}

IntegerWrapper* integerWrapLiteral(int value) {
  return (wrapInteger(value));
}

LongIntegerWrapper* longIntegerWrapLiteral(long long int value) {
  return (wrapLongInteger(value));
}

FloatWrapper* floatWrapLiteral(double value) {
  return (wrapFloat(value));
}

MutableStringWrapper* mutableStringWrapLiteral(char* value) {
  return (wrapMutableString(value));
}

StringWrapper* stringWrapLiteral(const char* value) {
  return (wrapString(value));
}

CharacterWrapper* characterWrapLiteral(char value) {
  return (wrapCharacter(value));
}

FunctionCodeWrapper* functionCodeWrapLiteral(cpp_function_code value) {
  return (wrapFunctionCode(value));
}

MethodCodeWrapper* methodCodeWrapLiteral(cpp_method_code value) {
  return (wrapMethodCode(value));
}

Object* StandardObject::copyWrappedLiteral() {
  { StandardObject* self = this;

    return (self);
  }
}

Object* LiteralWrapper::copyWrappedLiteral() {
  { LiteralWrapper* self = this;

    return (self);
  }
}

Object* IntegerWrapper::copyWrappedLiteral() {
  { IntegerWrapper* self = this;

    return (wrapInteger(self->wrapperValue));
  }
}

Object* LongIntegerWrapper::copyWrappedLiteral() {
  { LongIntegerWrapper* self = this;

    return (wrapLongInteger(self->wrapperValue));
  }
}

Object* FloatWrapper::copyWrappedLiteral() {
  { FloatWrapper* self = this;

    return (wrapFloat(self->wrapperValue));
  }
}

Object* StringWrapper::copyWrappedLiteral() {
  { StringWrapper* self = this;

    return (wrapString(self->wrapperValue));
  }
}

Object* MutableStringWrapper::copyWrappedLiteral() {
  { MutableStringWrapper* self = this;

    return (wrapMutableString(self->wrapperValue));
  }
}

Object* CharacterWrapper::copyWrappedLiteral() {
  { CharacterWrapper* self = this;

    return (wrapCharacter(self->wrapperValue));
  }
}

Object* FunctionCodeWrapper::copyWrappedLiteral() {
  { FunctionCodeWrapper* self = this;

    return (wrapFunctionCode(self->wrapperValue));
  }
}

Object* MethodCodeWrapper::copyWrappedLiteral() {
  { MethodCodeWrapper* self = this;

    return (wrapMethodCode(self->wrapperValue));
  }
}

boolean Object::objectEqlP(Object* y) {
  { Object* x = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "object-eql?: Don't know how to compare " << "`" << x << "'" << " with " << "`" << y << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

boolean StandardObject::objectEqlP(Object* y) {
  { StandardObject* x = this;

    return (x == y);
  }
}

boolean IntegerWrapper::objectEqlP(Object* y) {
  { IntegerWrapper* x = this;

    return (((boolean)(y)) &&
        (((y->primaryType() == SGT_LITERALS_STELLA_INTEGER_WRAPPER) ||
        isaP(y, SGT_LITERALS_STELLA_INTEGER_WRAPPER)) &&
         (x->wrapperValue == ((IntegerWrapper*)(y))->wrapperValue)));
  }
}

boolean LongIntegerWrapper::objectEqlP(Object* y) {
  { LongIntegerWrapper* x = this;

    return (((boolean)(y)) &&
        (((y->primaryType() == SGT_LITERALS_STELLA_LONG_INTEGER_WRAPPER) ||
        isaP(y, SGT_LITERALS_STELLA_LONG_INTEGER_WRAPPER)) &&
         (x->wrapperValue == ((LongIntegerWrapper*)(y))->wrapperValue)));
  }
}

boolean FloatWrapper::objectEqlP(Object* y) {
  { FloatWrapper* x = this;

    return (((boolean)(y)) &&
        (((y->primaryType() == SGT_LITERALS_STELLA_FLOAT_WRAPPER) ||
        isaP(y, SGT_LITERALS_STELLA_FLOAT_WRAPPER)) &&
         (x->wrapperValue == ((FloatWrapper*)(y))->wrapperValue)));
  }
}

boolean BooleanWrapper::objectEqlP(Object* y) {
  { BooleanWrapper* x = this;

    return ((x == y) ||
        (((boolean)(y)) &&
         (((y->primaryType() == SGT_LITERALS_STELLA_BOOLEAN_WRAPPER) ||
        isaP(y, SGT_LITERALS_STELLA_BOOLEAN_WRAPPER)) &&
          (x->wrapperValue == ((BooleanWrapper*)(y))->wrapperValue))));
  }
}

boolean StringWrapper::objectEqlP(Object* y) {
  { StringWrapper* x = this;

    if (((boolean)(y))) {
      { Surrogate* ytype = y->primaryType();

        if ((ytype == SGT_LITERALS_STELLA_STRING_WRAPPER) ||
            ((ytype == SGT_LITERALS_STELLA_VERBATIM_STRING_WRAPPER) ||
             (((!oCLASS_HIERARCHY_BOOTEDpo) &&
            ((!((boolean)(ytype))) ||
             ((!((boolean)(SGT_LITERALS_STELLA_STRING_WRAPPER))) ||
              (!((boolean)(SGT_LITERALS_STELLA_VERBATIM_STRING_WRAPPER)))))) ||
              isaP(y, SGT_LITERALS_STELLA_STRING_WRAPPER)))) {
          return (stringEqlP(x->wrapperValue, ((StringWrapper*)(y))->wrapperValue));
        }
      }
    }
    return (false);
  }
}

boolean MutableStringWrapper::objectEqlP(Object* y) {
  { MutableStringWrapper* x = this;

    return (x == y);
  }
}

boolean CharacterWrapper::objectEqlP(Object* y) {
  { CharacterWrapper* x = this;

    return (((boolean)(y)) &&
        (((y->primaryType() == SGT_LITERALS_STELLA_CHARACTER_WRAPPER) ||
        isaP(y, SGT_LITERALS_STELLA_CHARACTER_WRAPPER)) &&
         (x->wrapperValue == ((CharacterWrapper*)(y))->wrapperValue)));
  }
}

boolean eqlToBooleanP(Object* y, boolean x) {
  return (booleanP(y) &&
      (((BooleanWrapper*)(y))->wrapperValue == x));
}

boolean eqlToIntegerP(Object* y, int x) {
  return (integerP(y) &&
      (((IntegerWrapper*)(y))->wrapperValue == x));
}

boolean eqlToLongIntegerP(Object* y, long long int x) {
  return (longIntegerP(y) &&
      (((LongIntegerWrapper*)(y))->wrapperValue == x));
}

boolean eqlToFloatP(Object* y, double x) {
  return (floatP(y) &&
      (((FloatWrapper*)(y))->wrapperValue == x));
}

boolean eqlToStringP(Object* y, const char* x) {
  return (stringP(y) &&
      stringEqlP(((StringWrapper*)(y))->wrapperValue, x));
}

boolean eqlToCharacterP(Object* y, char x) {
  return (characterP(y) &&
      (((CharacterWrapper*)(y))->wrapperValue == x));
}

Object* helpBquotify(Object* tree) {
  if (!((boolean)(tree))) {
    return (SYM_LITERALS_STELLA_NULL);
  }
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (testValue000 == SGT_LITERALS_STELLA_CONS) {
      { Object* tree000 = tree;
        Cons* tree = ((Cons*)(tree000));

        if (tree == NIL) {
          return (SYM_LITERALS_STELLA_NIL);
        }
        else {
          return (consList(3, SYM_LITERALS_STELLA_CONS, helpBquotify(tree->value), helpBquotify(tree->rest)));
        }
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { Object* tree001 = tree;
        IntegerWrapper* tree = ((IntegerWrapper*)(tree001));

        return (consList(2, SYM_LITERALS_STELLA_WRAP_LITERAL, tree));
      }
    }
    else if (subtypeOfLongIntegerP(testValue000)) {
      { Object* tree002 = tree;
        LongIntegerWrapper* tree = ((LongIntegerWrapper*)(tree002));

        return (consList(2, SYM_LITERALS_STELLA_WRAP_LITERAL, tree));
      }
    }
    else if (subtypeOfStringP(testValue000)) {
      { Object* tree003 = tree;
        StringWrapper* tree = ((StringWrapper*)(tree003));

        return (consList(2, SYM_LITERALS_STELLA_WRAP_LITERAL, tree));
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* tree004 = tree;
        FloatWrapper* tree = ((FloatWrapper*)(tree004));

        return (consList(2, SYM_LITERALS_STELLA_WRAP_LITERAL, tree));
      }
    }
    else if (subtypeOfCharacterP(testValue000)) {
      { Object* tree005 = tree;
        CharacterWrapper* tree = ((CharacterWrapper*)(tree005));

        return (consList(2, SYM_LITERALS_STELLA_WRAP_LITERAL, tree));
      }
    }
    else if (subtypeOfKeywordP(testValue000)) {
      { Object* tree006 = tree;
        Keyword* tree = ((Keyword*)(tree006));

        if (useHardcodedSymbolsP()) {
          return (consList(2, SYM_LITERALS_STELLA_GET_KWD, wrapInteger(tree->symbolId)));
        }
        else {
          return (consList(3, SYM_LITERALS_STELLA_TYPED_SYS, registerSymbol(tree), SGT_LITERALS_STELLA_SYMBOL));
        }
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* tree007 = tree;
        Surrogate* tree = ((Surrogate*)(tree007));

        if (useHardcodedSymbolsP()) {
          return (consList(2, SYM_LITERALS_STELLA_GET_SGT, wrapInteger(tree->symbolId)));
        }
        else {
          return (consList(3, SYM_LITERALS_STELLA_TYPED_SYS, registerSymbol(tree), SGT_LITERALS_STELLA_SYMBOL));
        }
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* tree008 = tree;
        Symbol* tree = ((Symbol*)(tree008));

        if (symbolCommonLispP(tree)) {
          return (consList(2, SYM_LITERALS_STELLA_INTERN_COMMON_LISP_SYMBOL, wrapString(tree->symbolName)));
        }
        else {
          if (useHardcodedSymbolsP()) {
            return (consList(2, SYM_LITERALS_STELLA_GET_SYM, wrapInteger(((Symbol*)(tree->permanentify()))->symbolId)));
          }
          else {
            return (consList(3, SYM_LITERALS_STELLA_TYPED_SYS, registerSymbol(tree), SGT_LITERALS_STELLA_SYMBOL));
          }
        }
      }
    }
    else {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal argument to quote: " << "`" << deUglifyParseTree(tree) << "'" << "." << std::endl;
        }
      }
      return (NULL);
    }
  }
}

Object* bquotify(Object* tree) {
  return (helpBquotify(tree));
}

Object* expandBquoteTree(Object* tree) {
  if (safePrimaryType(tree) == SGT_LITERALS_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { Cons* expandedtree = cons(SYM_LITERALS_STELLA_LISTo, NIL);
        Cons* cursor = tree;
        Object* term = cursor->value;

        while ((!(cursor == NIL)) &&
            (!((term == SYM_LITERALS_STELLA_a) ||
            (term == SYM_LITERALS_STELLA_aa)))) {
          expandedtree = cons(expandBquoteTree(term), expandedtree);
          cursor = cursor->rest;
          term = cursor->value;
        }
        if (cursor == NIL) {
          return (cons(SYM_LITERALS_STELLA_NIL, expandedtree)->reverse());
        }
        else if (term == SYM_LITERALS_STELLA_a) {
          cursor = cursor->rest;
          if (cursor == NIL) {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal bquote tree -- missing term after '&'." << "." << std::endl;
              }
            }
          }
          return (cons(expandBquoteTree(cursor->rest), cons(cursor->value, expandedtree))->reverse());
        }
        else {
          cursor = cursor->rest;
          if (cursor == NIL) {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationError();
              if (!(suppressWarningsP())) {
                printErrorContext(">> ERROR: ", STANDARD_ERROR);
                *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal bquote tree -- missing term after '&&'" << "." << std::endl;
              }
            }
          }
          return (cons(consList(3, SYM_LITERALS_STELLA_CONCATENATE, cursor->value, expandBquoteTree(cursor->rest)), expandedtree)->reverse());
        }
      }
    }
  }
  else {
    return (bquotify(tree));
  }
}

Object* simplifyBquoteTree(Object* tree) {
  if (safePrimaryType(tree) == SGT_LITERALS_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { Cons* cursor = tree->rest;

        while (!(cursor == NIL)) {
          cursor->value = simplifyBquoteTree(cursor->value);
          cursor = cursor->rest;
        }
        if (!(tree->value == SYM_LITERALS_STELLA_LISTo)) {
          return (tree);
        }
        switch (tree->rest->length()) {
          case 1: 
            return (tree->rest->value);
          case 2: 
            tree->value = SYM_LITERALS_STELLA_CONS;
            return (tree);
          default:
            return (tree);
        }
      }
    }
  }
  else {
    return (tree);
  }
}

Object* Object::permanentify() {
  { Object* self = this;

    return (self);
  }
}

Object* Symbol::permanentify() {
  { Symbol* self = this;

    return (self);
  }
}

Object* TransientSymbol::permanentify() {
  { TransientSymbol* self = this;

    return (internPermanentSymbol(self->symbolName));
  }
}

Object* LiteralWrapper::permanentify() {
  { LiteralWrapper* self = this;

    return (((LiteralWrapper*)(self->copyWrappedLiteral())));
  }
}

Object* permanentCopy(Object* tree) {
  if (safePrimaryType(tree) == SGT_LITERALS_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if (tree == NIL) {
        return (tree);
      }
      else {
        return (cons(permanentCopy(tree->value), ((Cons*)(permanentCopy(tree->rest)))));
      }
    }
  }
  else {
    return (tree->permanentify());
  }
}

Symbol* Symbol::softPermanentify() {
  { Symbol* symbol = this;

    return (symbol);
  }
}

Symbol* TransientSymbol::softPermanentify() {
  { TransientSymbol* symbol = this;

    { GeneralizedSymbol* permanentsymbol = lookupRigidSymbolWrtModule(symbol->symbolName, (((boolean)(((Module*)(symbol->homeContext)))) ? ((Module*)(symbol->homeContext)) : oMODULEo), SYMBOL_SYM);

      if (((boolean)(permanentsymbol))) {
        return (((Symbol*)(permanentsymbol)));
      }
      else {
        return (symbol);
      }
    }
  }
}

void printCharacter(char chaR, std::ostream* stream) {
  *(stream) << "#\\";
  switch (chaR) {
    case '\n': 
      *(stream) << "Linefeed";
      break;
    case '\b': 
      *(stream) << "Backspace";
      break;
    case '\t': 
      *(stream) << "Tab";
      break;
    case '\r': 
      *(stream) << "Return";
      break;
    case '\f': 
      *(stream) << "Page";
      break;
    default:
      *(stream) << chaR;
      break;
  }
}

Keyword** createCharacterTypeTable() {
  { Keyword** table = new (GC)Keyword*[256];

    { int code = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = 255;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        code = iter000;
        table[code] = KWD_LITERALS_OTHER;
      }
    }
    { int code = NULL_INTEGER;
      int iter001 = (int)(unsigned char) '0';
      int upperBound001 = (int)(unsigned char) '9';
      boolean unboundedP000 = upperBound001 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter001 <= upperBound001); 
            iter001 = iter001 + 1) {
        code = iter001;
        table[code] = KWD_LITERALS_DIGIT;
      }
    }
    { int code = NULL_INTEGER;
      int iter002 = (int)(unsigned char) 'A';
      int upperBound002 = (int)(unsigned char) 'Z';
      boolean unboundedP001 = upperBound002 == NULL_INTEGER;

      for  (; unboundedP001 ||
                (iter002 <= upperBound002); 
            iter002 = iter002 + 1) {
        code = iter002;
        table[code] = KWD_LITERALS_LETTER;
      }
    }
    { int code = NULL_INTEGER;
      int iter003 = (int)(unsigned char) 'a';
      int upperBound003 = (int)(unsigned char) 'z';
      boolean unboundedP002 = upperBound003 == NULL_INTEGER;

      for  (; unboundedP002 ||
                (iter003 <= upperBound003); 
            iter003 = iter003 + 1) {
        code = iter003;
        table[code] = KWD_LITERALS_LETTER;
      }
    }
    table[(int)(unsigned char) '!'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '$'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '%'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '<'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '>'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '='] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '?'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '['] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) ']'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '^'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '_'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '{'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '}'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '~'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '*'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '.'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '+'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) '-'] = KWD_LITERALS_SYMBOL_CONSTITUENT;
    table[(int)(unsigned char) ':'] = KWD_LITERALS_SYMBOL_QUALIFIER;
    table[(int)(unsigned char) '/'] = KWD_LITERALS_SYMBOL_QUALIFIER;
    table[(int)(unsigned char) '@'] = KWD_LITERALS_SYMBOL_QUALIFIER;
    table[(int)(unsigned char) '\\'] = KWD_LITERALS_ESCAPE;
    table[(int)(unsigned char) '('] = KWD_LITERALS_DELIMITER;
    table[(int)(unsigned char) ')'] = KWD_LITERALS_DELIMITER;
    table[(int)(unsigned char) '"'] = KWD_LITERALS_DELIMITER;
    table[(int)(unsigned char) '|'] = KWD_LITERALS_DELIMITER;
    table[(int)(unsigned char) '\''] = KWD_LITERALS_DELIMITER;
    table[(int)(unsigned char) '`'] = KWD_LITERALS_DELIMITER;
    table[(int)(unsigned char) ','] = KWD_LITERALS_DELIMITER;
    table[(int)(unsigned char) ' '] = KWD_LITERALS_WHITE_SPACE;
    table[(int)(unsigned char) '\t'] = KWD_LITERALS_WHITE_SPACE;
    table[(int)(unsigned char) '\n'] = KWD_LITERALS_WHITE_SPACE;
    table[(int)(unsigned char) '\r'] = KWD_LITERALS_WHITE_SPACE;
    table[(int)(unsigned char) '\n'] = KWD_LITERALS_WHITE_SPACE;
    table[(int)(unsigned char) '\f'] = KWD_LITERALS_WHITE_SPACE;
    return (table);
  }
}

// Table of character types.  Entry 'i' represents the type
// of the character whose 'char-code' equals 'i'.  Each character is classified 
// by one of the following keywords: :DIGIT, :LETTER, :SYMBOL-CONSTITUENT, 
// :SYMBOL-QUALIFIER, :ESCAPE, :DELIMITER, :WHITE-SPACE, or :OTHER.
Keyword** oCHARACTER_TYPE_TABLEo = NULL;

boolean digitCharacterP(char ch) {
  // Return TRUE if `ch' represents a digit.
  return (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) ch] == KWD_LITERALS_DIGIT);
}

boolean letterCharacterP(char ch) {
  // Return TRUE if `ch' represents a letter.
  return (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) ch] == KWD_LITERALS_LETTER);
}

boolean upperCaseCharacterP(char ch) {
  // Return TRUE if `ch' represents an upper-case character.
  { int charcode = (int)(unsigned char) ch;

    return ((charcode >= (int)(unsigned char) 'A') &&
        (charcode <= (int)(unsigned char) 'Z'));
  }
}

boolean lowerCaseCharacterP(char ch) {
  // Return TRUE if `ch' represents a lower-case character.
  { int charcode = (int)(unsigned char) ch;

    return ((charcode >= (int)(unsigned char) 'a') &&
        (charcode <= (int)(unsigned char) 'z'));
  }
}

boolean whiteSpaceCharacterP(char ch) {
  // Return TRUE if `ch' is a white space character.
  return (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) ch] == KWD_LITERALS_WHITE_SPACE);
}

boolean eightBitCharacterP(char ch) {
  // Return TRUE if `ch' is in the upper half of the byte set such as UTF-8 codes, etc.
  return ((int)(unsigned char) ch >= 128);
}

boolean allUpperCaseStringP(const char* s) {
  // Return TRUE if all letters in `s' are upper case.
  { int code = 0;
    int codea = (int)(unsigned char) 'a';
    int codez = (int)(unsigned char) 'z';

    { char ch = NULL_CHARACTER;
      const char* vector000 = s;
      int index000 = 0;
      int length000 = strlen(vector000);

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        ch = vector000[index000];
        code = (int)(unsigned char) ch;
        if ((code >= codea) &&
            (code <= codez)) {
          return (false);
        }
      }
    }
    return (true);
  }
}

boolean allLowerCaseStringP(const char* s) {
  // Return TRUE if all letters in `s' are lower case.
  { int code = 0;
    int codea = (int)(unsigned char) 'A';
    int codez = (int)(unsigned char) 'Z';

    { char ch = NULL_CHARACTER;
      const char* vector000 = s;
      int index000 = 0;
      int length000 = strlen(vector000);

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        ch = vector000[index000];
        code = (int)(unsigned char) ch;
        if ((code <= codez) &&
            (code >= codea)) {
          return (false);
        }
      }
    }
    return (true);
  }
}

const char* oCHARACTER_UPCASE_TABLEo = NULL;

const char* initializeCharacterUpcaseTable() {
  { char* buffer = native_make_mutable_string(256, NULL_CHARACTER);

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = 255;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        buffer[i] = ((char) i);
        if ((i >= (int)(unsigned char) 'a') &&
            (i <= (int)(unsigned char) 'z')) {
          buffer[i] = ((char) ((int)(unsigned char) 'A' + (i - (int)(unsigned char) 'a')));
        }
      }
    }
    return (buffer);
  }
}

const char* oCHARACTER_DOWNCASE_TABLEo = NULL;

const char* initializeCharacterDowncaseTable() {
  { char* buffer = native_make_mutable_string(256, NULL_CHARACTER);

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = 255;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        buffer[i] = ((char) i);
        if ((i >= (int)(unsigned char) 'A') &&
            (i <= (int)(unsigned char) 'Z')) {
          buffer[i] = ((char) ((int)(unsigned char) 'a' + (i - (int)(unsigned char) 'A')));
        }
      }
    }
    return (buffer);
  }
}

char upcaseCharacter(char chaR) {
  // If `char' is lowercase, return its uppercase version,
  // otherwise, return 'char' unmodified.
  return (oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) chaR)]);
}

char downcaseCharacter(char chaR) {
  // If `char' is uppercase, return its lowercase version,
  // otherwise, return 'char' unmodified.
  return (oCHARACTER_DOWNCASE_TABLEo[((int)(unsigned char) chaR)]);
}

void printStringReadably(const char* string, std::ostream* stream) {
  if (string == NULL) {
    *(stream) << SYM_LITERALS_STELLA_NULL_STRING;
  }
  else {
    {
      *(stream) << "\"";
      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = strlen(string) - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          { char chaR = string[i];

            if ((chaR == '"') ||
                (chaR == '\\')) {
              *(stream) << "\\" << chaR;
            }
            else {
              *(stream) << chaR;
            }
          }
        }
      }
      *(stream) << "\"";
    }
  }
}

char* stringToMutableString(const char* s) {
  // Copy `s' into a mutable string with the same content.
  // In Lisp and C++ this simply copies `s'.
  return (strcpy(new (GC) char[strlen(s)+1], s));
}

const char* mutableStringToString(char* s) {
  // Convert `s' into a regular string with the same content.
  // In Lisp and C++ this is a no-op.
  return (s);
}

double Object::numberWrapperToFloat() {
  { Object* self = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << self << "'" << " is not a number wrapper";
      throw *newBadArgumentException(stream000->theStringReader());
    }
  }
}

double IntegerWrapper::numberWrapperToFloat() {
  { IntegerWrapper* self = this;

    return (((double)(self->wrapperValue)));
  }
}

double LongIntegerWrapper::numberWrapperToFloat() {
  { LongIntegerWrapper* self = this;

    return (((double)(self->wrapperValue)));
  }
}

double FloatWrapper::numberWrapperToFloat() {
  { FloatWrapper* self = this;

    return (self->wrapperValue);
  }
}

void helpStartupLiterals1() {
  {
    SGT_LITERALS_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 1)));
    KWD_LITERALS_NULL_WRAPPER = ((Keyword*)(internRigidSymbolWrtModule("NULL-WRAPPER", NULL, 2)));
    SYM_LITERALS_STELLA_FALSE_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("FALSE-WRAPPER", NULL, 0)));
    SGT_LITERALS_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", NULL, 1)));
    SYM_LITERALS_STELLA_NULL_INTEGER_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("NULL-INTEGER-WRAPPER", NULL, 0)));
    SGT_LITERALS_STELLA_LONG_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("LONG-INTEGER", NULL, 1)));
    SYM_LITERALS_STELLA_NULL_LONG_INTEGER_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("NULL-LONG-INTEGER-WRAPPER", NULL, 0)));
    SGT_LITERALS_STELLA_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT", NULL, 1)));
    SYM_LITERALS_STELLA_NULL_FLOAT_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("NULL-FLOAT-WRAPPER", NULL, 0)));
    SGT_LITERALS_STELLA_STRING = ((Surrogate*)(internRigidSymbolWrtModule("STRING", NULL, 1)));
    SYM_LITERALS_STELLA_NULL_STRING_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("NULL-STRING-WRAPPER", NULL, 0)));
    SGT_LITERALS_STELLA_MUTABLE_STRING = ((Surrogate*)(internRigidSymbolWrtModule("MUTABLE-STRING", NULL, 1)));
    SYM_LITERALS_STELLA_NULL_MUTABLE_STRING_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("NULL-MUTABLE-STRING-WRAPPER", NULL, 0)));
    SGT_LITERALS_STELLA_CHARACTER = ((Surrogate*)(internRigidSymbolWrtModule("CHARACTER", NULL, 1)));
    SYM_LITERALS_STELLA_NULL_CHARACTER_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("NULL-CHARACTER-WRAPPER", NULL, 0)));
    SGT_LITERALS_STELLA_FUNCTION_CODE = ((Surrogate*)(internRigidSymbolWrtModule("FUNCTION-CODE", NULL, 1)));
    SYM_LITERALS_STELLA_NULL_FUNCTION_CODE_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("NULL-FUNCTION-CODE-WRAPPER", NULL, 0)));
    SGT_LITERALS_STELLA_METHOD_CODE = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-CODE", NULL, 1)));
    SYM_LITERALS_STELLA_NULL_METHOD_CODE_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("NULL-METHOD-CODE-WRAPPER", NULL, 0)));
    SYM_LITERALS_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    SYM_LITERALS_STELLA_TRUE_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("TRUE-WRAPPER", NULL, 0)));
    SYM_LITERALS_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    SYM_LITERALS_STELLA_WRAP_BOOLEAN = ((Symbol*)(internRigidSymbolWrtModule("WRAP-BOOLEAN", NULL, 0)));
    SYM_LITERALS_STELLA_COERCE_WRAPPED_BOOLEAN_TO_BOOLEAN = ((Symbol*)(internRigidSymbolWrtModule("COERCE-WRAPPED-BOOLEAN-TO-BOOLEAN", NULL, 0)));
    KWD_LITERALS_WRAP_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("WRAP-FUNCTION", NULL, 2)));
    SYM_LITERALS_STELLA_WRAP_INTEGER = ((Symbol*)(internRigidSymbolWrtModule("WRAP-INTEGER", NULL, 0)));
    SYM_LITERALS_STELLA_WRAP_LONG_INTEGER = ((Symbol*)(internRigidSymbolWrtModule("WRAP-LONG-INTEGER", NULL, 0)));
    SYM_LITERALS_STELLA_WRAP_FLOAT = ((Symbol*)(internRigidSymbolWrtModule("WRAP-FLOAT", NULL, 0)));
    SYM_LITERALS_STELLA_WRAP_STRING = ((Symbol*)(internRigidSymbolWrtModule("WRAP-STRING", NULL, 0)));
    SYM_LITERALS_STELLA_WRAP_MUTABLE_STRING = ((Symbol*)(internRigidSymbolWrtModule("WRAP-MUTABLE-STRING", NULL, 0)));
    SYM_LITERALS_STELLA_WRAP_CHARACTER = ((Symbol*)(internRigidSymbolWrtModule("WRAP-CHARACTER", NULL, 0)));
    SYM_LITERALS_STELLA_WRAP_FUNCTION_CODE = ((Symbol*)(internRigidSymbolWrtModule("WRAP-FUNCTION-CODE", NULL, 0)));
    SYM_LITERALS_STELLA_WRAP_METHOD_CODE = ((Symbol*)(internRigidSymbolWrtModule("WRAP-METHOD-CODE", NULL, 0)));
    SGT_LITERALS_STELLA_INTEGER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-WRAPPER", NULL, 1)));
    SGT_LITERALS_STELLA_LONG_INTEGER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("LONG-INTEGER-WRAPPER", NULL, 1)));
    SGT_LITERALS_STELLA_FLOAT_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT-WRAPPER", NULL, 1)));
    SGT_LITERALS_STELLA_BOOLEAN_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN-WRAPPER", NULL, 1)));
    SGT_LITERALS_STELLA_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("STRING-WRAPPER", NULL, 1)));
    SGT_LITERALS_STELLA_VERBATIM_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("VERBATIM-STRING-WRAPPER", NULL, 1)));
    SGT_LITERALS_STELLA_CHARACTER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("CHARACTER-WRAPPER", NULL, 1)));
    SYM_LITERALS_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    SGT_LITERALS_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SYM_LITERALS_STELLA_NIL = ((Symbol*)(internRigidSymbolWrtModule("NIL", NULL, 0)));
    SYM_LITERALS_STELLA_CONS = ((Symbol*)(internRigidSymbolWrtModule("CONS", NULL, 0)));
    SYM_LITERALS_STELLA_WRAP_LITERAL = ((Symbol*)(internRigidSymbolWrtModule("WRAP-LITERAL", NULL, 0)));
    SYM_LITERALS_STELLA_GET_KWD = ((Symbol*)(internRigidSymbolWrtModule("GET-KWD", NULL, 0)));
    SYM_LITERALS_STELLA_TYPED_SYS = ((Symbol*)(internRigidSymbolWrtModule("TYPED-SYS", NULL, 0)));
    SGT_LITERALS_STELLA_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("SYMBOL", NULL, 1)));
    SYM_LITERALS_STELLA_GET_SGT = ((Symbol*)(internRigidSymbolWrtModule("GET-SGT", NULL, 0)));
    SYM_LITERALS_STELLA_INTERN_COMMON_LISP_SYMBOL = ((Symbol*)(internRigidSymbolWrtModule("INTERN-COMMON-LISP-SYMBOL", NULL, 0)));
    SYM_LITERALS_STELLA_GET_SYM = ((Symbol*)(internRigidSymbolWrtModule("GET-SYM", NULL, 0)));
    SYM_LITERALS_STELLA_LISTo = ((Symbol*)(internRigidSymbolWrtModule("LIST*", NULL, 0)));
    SYM_LITERALS_STELLA_a = ((Symbol*)(internRigidSymbolWrtModule("&", NULL, 0)));
    SYM_LITERALS_STELLA_aa = ((Symbol*)(internRigidSymbolWrtModule("&&", NULL, 0)));
    SYM_LITERALS_STELLA_CONCATENATE = ((Symbol*)(internRigidSymbolWrtModule("CONCATENATE", NULL, 0)));
    KWD_LITERALS_OTHER = ((Keyword*)(internRigidSymbolWrtModule("OTHER", NULL, 2)));
    KWD_LITERALS_DIGIT = ((Keyword*)(internRigidSymbolWrtModule("DIGIT", NULL, 2)));
    KWD_LITERALS_LETTER = ((Keyword*)(internRigidSymbolWrtModule("LETTER", NULL, 2)));
    KWD_LITERALS_SYMBOL_CONSTITUENT = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL-CONSTITUENT", NULL, 2)));
    KWD_LITERALS_SYMBOL_QUALIFIER = ((Keyword*)(internRigidSymbolWrtModule("SYMBOL-QUALIFIER", NULL, 2)));
  }
}

void helpStartupLiterals2() {
  {
    oLITERAL_TYPE_INFO_TABLEo = newHashTable();
    oLITERAL_TYPESo = newList();
    setLiteralTypeInfo(SGT_LITERALS_STELLA_BOOLEAN, KWD_LITERALS_NULL_WRAPPER, SYM_LITERALS_STELLA_FALSE_WRAPPER);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_INTEGER, KWD_LITERALS_NULL_WRAPPER, SYM_LITERALS_STELLA_NULL_INTEGER_WRAPPER);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_LONG_INTEGER, KWD_LITERALS_NULL_WRAPPER, SYM_LITERALS_STELLA_NULL_LONG_INTEGER_WRAPPER);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_FLOAT, KWD_LITERALS_NULL_WRAPPER, SYM_LITERALS_STELLA_NULL_FLOAT_WRAPPER);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_STRING, KWD_LITERALS_NULL_WRAPPER, SYM_LITERALS_STELLA_NULL_STRING_WRAPPER);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_MUTABLE_STRING, KWD_LITERALS_NULL_WRAPPER, SYM_LITERALS_STELLA_NULL_MUTABLE_STRING_WRAPPER);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_CHARACTER, KWD_LITERALS_NULL_WRAPPER, SYM_LITERALS_STELLA_NULL_CHARACTER_WRAPPER);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_FUNCTION_CODE, KWD_LITERALS_NULL_WRAPPER, SYM_LITERALS_STELLA_NULL_FUNCTION_CODE_WRAPPER);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_METHOD_CODE, KWD_LITERALS_NULL_WRAPPER, SYM_LITERALS_STELLA_NULL_METHOD_CODE_WRAPPER);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_BOOLEAN, KWD_LITERALS_WRAP_FUNCTION, SYM_LITERALS_STELLA_WRAP_BOOLEAN);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_INTEGER, KWD_LITERALS_WRAP_FUNCTION, SYM_LITERALS_STELLA_WRAP_INTEGER);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_LONG_INTEGER, KWD_LITERALS_WRAP_FUNCTION, SYM_LITERALS_STELLA_WRAP_LONG_INTEGER);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_FLOAT, KWD_LITERALS_WRAP_FUNCTION, SYM_LITERALS_STELLA_WRAP_FLOAT);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_STRING, KWD_LITERALS_WRAP_FUNCTION, SYM_LITERALS_STELLA_WRAP_STRING);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_MUTABLE_STRING, KWD_LITERALS_WRAP_FUNCTION, SYM_LITERALS_STELLA_WRAP_MUTABLE_STRING);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_CHARACTER, KWD_LITERALS_WRAP_FUNCTION, SYM_LITERALS_STELLA_WRAP_CHARACTER);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_FUNCTION_CODE, KWD_LITERALS_WRAP_FUNCTION, SYM_LITERALS_STELLA_WRAP_FUNCTION_CODE);
    setLiteralTypeInfo(SGT_LITERALS_STELLA_METHOD_CODE, KWD_LITERALS_WRAP_FUNCTION, SYM_LITERALS_STELLA_WRAP_METHOD_CODE);
    oCHARACTER_TYPE_TABLEo = createCharacterTypeTable();
    oCHARACTER_UPCASE_TABLEo = initializeCharacterUpcaseTable();
    oCHARACTER_DOWNCASE_TABLEo = initializeCharacterDowncaseTable();
  }
}

void helpStartupLiterals3() {
  {
    defineMethodObject("(DEFMETHOD (TERMINATE-WRAPPER? BOOLEAN) ((SELF WRAPPER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Wrapper::terminateWrapperP))), NULL);
    defineMethodObject("(DEFMETHOD (TERMINATE-WRAPPER? BOOLEAN) ((SELF INTEGER-WRAPPER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&IntegerWrapper::terminateWrapperP))), NULL);
    defineFunctionObject("LOOKUP-LITERAL-TYPE-INFO", "(DEFUN (LOOKUP-LITERAL-TYPE-INFO OBJECT) ((TYPE TYPE) (KEY KEYWORD)))", ((cpp_function_code)(&lookupLiteralTypeInfo)), NULL);
    defineFunctionObject("SET-LITERAL-TYPE-INFO", "(DEFUN SET-LITERAL-TYPE-INFO ((TYPE TYPE) (KEY KEYWORD) (VALUE OBJECT)))", ((cpp_function_code)(&setLiteralTypeInfo)), NULL);
    defineFunctionObject("WRAP-INTEGER", "(DEFUN (WRAP-INTEGER INTEGER-WRAPPER) ((VALUE INTEGER)) :DOCUMENTATION \"Return a literal object whose value is the INTEGER 'value'.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&wrapInteger)), NULL);
    defineFunctionObject("UNWRAP-INTEGER", "(DEFUN (UNWRAP-INTEGER INTEGER) ((WRAPPER INTEGER-WRAPPER)) :DOCUMENTATION \"Unwrap `wrapper' and return the result.\nReturn NULL if `wrapper' is NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unwrapInteger)), NULL);
    defineFunctionObject("WRAP-LONG-INTEGER", "(DEFUN (WRAP-LONG-INTEGER LONG-INTEGER-WRAPPER) ((VALUE LONG-INTEGER)) :DOCUMENTATION \"Return a literal object whose value is the LONG-INTEGER 'value'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&wrapLongInteger)), NULL);
    defineFunctionObject("UNWRAP-LONG-INTEGER", "(DEFUN (UNWRAP-LONG-INTEGER LONG-INTEGER) ((WRAPPER LONG-INTEGER-WRAPPER)) :DOCUMENTATION \"Unwrap `wrapper' and return the result.\nReturn NULL if `wrapper' is NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unwrapLongInteger)), NULL);
    defineFunctionObject("WRAP-INTEGER-VALUE", "(DEFUN (WRAP-INTEGER-VALUE NUMBER-WRAPPER) ((VALUE LONG-INTEGER)) :DOCUMENTATION \"Return a literal object whose value is 'value'.  Choose a regular integer\nwrapper unless `value' is too large and needs to be stored in a long wrapper.\" :PUBLIC? TRUE)", ((cpp_function_code)(&wrapIntegerValue)), NULL);
    defineFunctionObject("WRAP-FLOAT", "(DEFUN (WRAP-FLOAT FLOAT-WRAPPER) ((VALUE FLOAT)) :DOCUMENTATION \"Return a literal object whose value is the FLOAT 'value'.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&wrapFloat)), NULL);
    defineFunctionObject("UNWRAP-FLOAT", "(DEFUN (UNWRAP-FLOAT FLOAT) ((WRAPPER FLOAT-WRAPPER)) :DOCUMENTATION \"Unwrap `wrapper' and return the result.\nReturn NULL if `wrapper' is NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unwrapFloat)), NULL);
    defineFunctionObject("WRAP-STRING", "(DEFUN (WRAP-STRING STRING-WRAPPER) ((VALUE STRING)) :DOCUMENTATION \"Return a literal object whose value is the STRING 'value'.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&wrapString)), NULL);
    defineFunctionObject("UNWRAP-STRING", "(DEFUN (UNWRAP-STRING STRING) ((WRAPPER STRING-WRAPPER)) :DOCUMENTATION \"Unwrap `wrapper' and return the result.\nReturn NULL if `wrapper' is NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unwrapString)), NULL);
    defineFunctionObject("WRAP-MUTABLE-STRING", "(DEFUN (WRAP-MUTABLE-STRING MUTABLE-STRING-WRAPPER) ((VALUE MUTABLE-STRING)) :DOCUMENTATION \"Return a literal object whose value is the MUTABLE-STRING 'value'.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&wrapMutableString)), NULL);
    defineFunctionObject("UNWRAP-MUTABLE-STRING", "(DEFUN (UNWRAP-MUTABLE-STRING MUTABLE-STRING) ((WRAPPER MUTABLE-STRING-WRAPPER)) :DOCUMENTATION \"Unwrap `wrapper' and return the result.\nReturn NULL if `wrapper' is NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unwrapMutableString)), NULL);
    defineFunctionObject("WRAP-CHARACTER", "(DEFUN (WRAP-CHARACTER CHARACTER-WRAPPER) ((VALUE CHARACTER)) :DOCUMENTATION \"Return a literal object whose value is the CHARACTER 'value'.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&wrapCharacter)), NULL);
    defineFunctionObject("UNWRAP-CHARACTER", "(DEFUN (UNWRAP-CHARACTER CHARACTER) ((WRAPPER CHARACTER-WRAPPER)) :DOCUMENTATION \"Unwrap `wrapper' and return the result.\nReturn NULL if `wrapper' is NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unwrapCharacter)), NULL);
    defineFunctionObject("WRAP-FUNCTION-CODE", "(DEFUN (WRAP-FUNCTION-CODE FUNCTION-CODE-WRAPPER) ((VALUE FUNCTION-CODE)) :DOCUMENTATION \"Return a literal object whose value is the FUNCTION-CODE 'value'.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&wrapFunctionCode)), NULL);
    defineFunctionObject("UNWRAP-FUNCTION-CODE", "(DEFUN (UNWRAP-FUNCTION-CODE FUNCTION-CODE) ((WRAPPER FUNCTION-CODE-WRAPPER)) :DOCUMENTATION \"Unwrap `wrapper' and return the result.\nReturn NULL if `wrapper' is NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unwrapFunctionCode)), NULL);
    defineFunctionObject("WRAP-METHOD-CODE", "(DEFUN (WRAP-METHOD-CODE METHOD-CODE-WRAPPER) ((VALUE METHOD-CODE)) :DOCUMENTATION \"Return a literal object whose value is the METHOD-CODE 'value'.\" :PUBLIC? TRUE :CONSTRUCTOR? TRUE)", ((cpp_function_code)(&wrapMethodCode)), NULL);
    defineFunctionObject("UNWRAP-METHOD-CODE", "(DEFUN (UNWRAP-METHOD-CODE METHOD-CODE) ((WRAPPER METHOD-CODE-WRAPPER)) :DOCUMENTATION \"Unwrap `wrapper' and return the result.\nReturn NULL if `wrapper' is NULL.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unwrapMethodCode)), NULL);
    defineFunctionObject("WRAP-BOOLEAN", "(DEFUN (WRAP-BOOLEAN BOOLEAN-WRAPPER) ((VALUE BOOLEAN)) :DOCUMENTATION \"Return a literal object whose value is the BOOLEAN 'value'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :CONSTRUCTOR? TRUE (RETURN (CHOOSE VALUE TRUE-WRAPPER FALSE-WRAPPER)))", ((cpp_function_code)(&wrapBoolean)), NULL);
    defineFunctionObject("UNWRAP-BOOLEAN", "(DEFUN (UNWRAP-BOOLEAN BOOLEAN) ((WRAPPER BOOLEAN-WRAPPER)) :DOCUMENTATION \"Unwrap `wrapper' and return its values as a regular BOOLEAN.\nMap NULL onto FALSE.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (EQ? WRAPPER TRUE-WRAPPER)))", ((cpp_function_code)(&unwrapBoolean)), NULL);
    defineFunctionObject("COERCE-WRAPPED-BOOLEAN-TO-BOOLEAN", "(DEFUN (COERCE-WRAPPED-BOOLEAN-TO-BOOLEAN BOOLEAN) ((WRAPPER BOOLEAN-WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&coerceWrappedBooleanToBoolean)), NULL);
    defineFunctionObject("INLINE-WRAP-BOOLEAN", "(DEFUN INLINE-WRAP-BOOLEAN ((EXPRESSION OBJECT)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&inlineWrapBoolean)), NULL);
    defineFunctionObject("INLINE-UNWRAP-BOOLEAN", "(DEFUN INLINE-UNWRAP-BOOLEAN ((EXPRESSION OBJECT)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&inlineUnwrapBoolean)), NULL);
    defineMethodObject("(DEFMETHOD (WRAP-LITERAL INTEGER-WRAPPER) ((VALUE INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (WRAP-INTEGER VALUE)))", wrapFunctionCode(((cpp_function_code)(((IntegerWrapper*  (*) (int))(&integerWrapLiteral))))), NULL);
    defineMethodObject("(DEFMETHOD (WRAP-LITERAL LONG-INTEGER-WRAPPER) ((VALUE LONG-INTEGER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (WRAP-LONG-INTEGER VALUE)))", wrapFunctionCode(((cpp_function_code)(((LongIntegerWrapper*  (*) (long long int))(&longIntegerWrapLiteral))))), NULL);
    defineMethodObject("(DEFMETHOD (WRAP-LITERAL FLOAT-WRAPPER) ((VALUE FLOAT)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (WRAP-FLOAT VALUE)))", wrapFunctionCode(((cpp_function_code)(((FloatWrapper*  (*) (double))(&floatWrapLiteral))))), NULL);
    defineMethodObject("(DEFMETHOD (WRAP-LITERAL MUTABLE-STRING-WRAPPER) ((VALUE MUTABLE-STRING)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (WRAP-MUTABLE-STRING VALUE)))", wrapFunctionCode(((cpp_function_code)(((MutableStringWrapper*  (*) (char*))(&mutableStringWrapLiteral))))), NULL);
    defineMethodObject("(DEFMETHOD (WRAP-LITERAL STRING-WRAPPER) ((VALUE STRING)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (WRAP-STRING VALUE)))", wrapFunctionCode(((cpp_function_code)(((StringWrapper*  (*) (const char*))(&stringWrapLiteral))))), NULL);
    defineMethodObject("(DEFMETHOD (WRAP-LITERAL CHARACTER-WRAPPER) ((VALUE CHARACTER)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (WRAP-CHARACTER VALUE)))", wrapFunctionCode(((cpp_function_code)(((CharacterWrapper*  (*) (char))(&characterWrapLiteral))))), NULL);
    defineMethodObject("(DEFMETHOD (WRAP-LITERAL FUNCTION-CODE-WRAPPER) ((VALUE FUNCTION-CODE)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (WRAP-FUNCTION-CODE VALUE)))", wrapFunctionCode(((cpp_function_code)(((FunctionCodeWrapper*  (*) (cpp_function_code))(&functionCodeWrapLiteral))))), NULL);
    defineMethodObject("(DEFMETHOD (WRAP-LITERAL METHOD-CODE-WRAPPER) ((VALUE METHOD-CODE)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (WRAP-METHOD-CODE VALUE)))", wrapFunctionCode(((cpp_function_code)(((MethodCodeWrapper*  (*) (cpp_method_code))(&methodCodeWrapLiteral))))), NULL);
    defineMethodObject("(DEFMETHOD (COPY-WRAPPED-LITERAL OBJECT) ((SELF STANDARD-OBJECT)))", wrapMethodCode(((cpp_method_code)(&StandardObject::copyWrappedLiteral))), NULL);
    defineMethodObject("(DEFMETHOD (COPY-WRAPPED-LITERAL OBJECT) ((SELF LITERAL-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&LiteralWrapper::copyWrappedLiteral))), NULL);
    defineMethodObject("(DEFMETHOD (COPY-WRAPPED-LITERAL OBJECT) ((SELF INTEGER-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&IntegerWrapper::copyWrappedLiteral))), NULL);
    defineMethodObject("(DEFMETHOD (COPY-WRAPPED-LITERAL OBJECT) ((SELF LONG-INTEGER-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&LongIntegerWrapper::copyWrappedLiteral))), NULL);
    defineMethodObject("(DEFMETHOD (COPY-WRAPPED-LITERAL OBJECT) ((SELF FLOAT-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&FloatWrapper::copyWrappedLiteral))), NULL);
    defineMethodObject("(DEFMETHOD (COPY-WRAPPED-LITERAL OBJECT) ((SELF STRING-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&StringWrapper::copyWrappedLiteral))), NULL);
    defineMethodObject("(DEFMETHOD (COPY-WRAPPED-LITERAL OBJECT) ((SELF MUTABLE-STRING-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&MutableStringWrapper::copyWrappedLiteral))), NULL);
    defineMethodObject("(DEFMETHOD (COPY-WRAPPED-LITERAL OBJECT) ((SELF CHARACTER-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&CharacterWrapper::copyWrappedLiteral))), NULL);
    defineMethodObject("(DEFMETHOD (COPY-WRAPPED-LITERAL OBJECT) ((SELF FUNCTION-CODE-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&FunctionCodeWrapper::copyWrappedLiteral))), NULL);
    defineMethodObject("(DEFMETHOD (COPY-WRAPPED-LITERAL OBJECT) ((SELF METHOD-CODE-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&MethodCodeWrapper::copyWrappedLiteral))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X OBJECT) (Y OBJECT)))", wrapMethodCode(((cpp_method_code)(&Object::objectEqlP))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X STANDARD-OBJECT) (Y OBJECT)))", wrapMethodCode(((cpp_method_code)(&StandardObject::objectEqlP))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X INTEGER-WRAPPER) (Y OBJECT)))", wrapMethodCode(((cpp_method_code)(&IntegerWrapper::objectEqlP))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X LONG-INTEGER-WRAPPER) (Y OBJECT)))", wrapMethodCode(((cpp_method_code)(&LongIntegerWrapper::objectEqlP))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X FLOAT-WRAPPER) (Y OBJECT)))", wrapMethodCode(((cpp_method_code)(&FloatWrapper::objectEqlP))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X BOOLEAN-WRAPPER) (Y OBJECT)))", wrapMethodCode(((cpp_method_code)(&BooleanWrapper::objectEqlP))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X STRING-WRAPPER) (Y OBJECT)))", wrapMethodCode(((cpp_method_code)(&StringWrapper::objectEqlP))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X MUTABLE-STRING-WRAPPER) (Y OBJECT)))", wrapMethodCode(((cpp_method_code)(&MutableStringWrapper::objectEqlP))), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQL? BOOLEAN) ((X CHARACTER-WRAPPER) (Y OBJECT)))", wrapMethodCode(((cpp_method_code)(&CharacterWrapper::objectEqlP))), NULL);
    defineFunctionObject("EQL-TO-BOOLEAN?", "(DEFUN (EQL-TO-BOOLEAN? BOOLEAN) ((Y OBJECT) (X BOOLEAN)))", ((cpp_function_code)(&eqlToBooleanP)), NULL);
    defineFunctionObject("EQL-TO-INTEGER?", "(DEFUN (EQL-TO-INTEGER? BOOLEAN) ((Y OBJECT) (X INTEGER)))", ((cpp_function_code)(&eqlToIntegerP)), NULL);
    defineFunctionObject("EQL-TO-LONG-INTEGER?", "(DEFUN (EQL-TO-LONG-INTEGER? BOOLEAN) ((Y OBJECT) (X LONG-INTEGER)))", ((cpp_function_code)(&eqlToLongIntegerP)), NULL);
    defineFunctionObject("EQL-TO-FLOAT?", "(DEFUN (EQL-TO-FLOAT? BOOLEAN) ((Y OBJECT) (X FLOAT)))", ((cpp_function_code)(&eqlToFloatP)), NULL);
    defineFunctionObject("EQL-TO-STRING?", "(DEFUN (EQL-TO-STRING? BOOLEAN) ((Y OBJECT) (X STRING)))", ((cpp_function_code)(&eqlToStringP)), NULL);
    defineFunctionObject("EQL-TO-CHARACTER?", "(DEFUN (EQL-TO-CHARACTER? BOOLEAN) ((Y OBJECT) (X CHARACTER)))", ((cpp_function_code)(&eqlToCharacterP)), NULL);
    defineFunctionObject("HELP-BQUOTIFY", "(DEFUN (HELP-BQUOTIFY OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&helpBquotify)), NULL);
  }
}

void helpStartupLiterals4() {
  {
    defineFunctionObject("BQUOTIFY", "(DEFUN (BQUOTIFY OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&bquotify)), NULL);
    defineFunctionObject("EXPAND-BQUOTE-TREE", "(DEFUN (EXPAND-BQUOTE-TREE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&expandBquoteTree)), NULL);
    defineFunctionObject("SIMPLIFY-BQUOTE-TREE", "(DEFUN (SIMPLIFY-BQUOTE-TREE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&simplifyBquoteTree)), NULL);
    defineMethodObject("(DEFMETHOD (PERMANENTIFY OBJECT) ((SELF OBJECT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Object::permanentify))), NULL);
    defineMethodObject("(DEFMETHOD (PERMANENTIFY SYMBOL) ((SELF SYMBOL)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Symbol::permanentify))), NULL);
    defineMethodObject("(DEFMETHOD (PERMANENTIFY SYMBOL) ((SELF TRANSIENT-SYMBOL)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&TransientSymbol::permanentify))), NULL);
    defineMethodObject("(DEFMETHOD (PERMANENTIFY LITERAL-WRAPPER) ((SELF LITERAL-WRAPPER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&LiteralWrapper::permanentify))), NULL);
    defineFunctionObject("PERMANENT-COPY", "(DEFUN (PERMANENT-COPY OBJECT) ((TREE OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&permanentCopy)), NULL);
    defineMethodObject("(DEFMETHOD (SOFT-PERMANENTIFY SYMBOL) ((SYMBOL SYMBOL)))", wrapMethodCode(((cpp_method_code)(&Symbol::softPermanentify))), NULL);
    defineMethodObject("(DEFMETHOD (SOFT-PERMANENTIFY SYMBOL) ((SYMBOL TRANSIENT-SYMBOL)))", wrapMethodCode(((cpp_method_code)(&TransientSymbol::softPermanentify))), NULL);
    defineFunctionObject("PRINT-CHARACTER", "(DEFUN PRINT-CHARACTER ((CHAR CHARACTER) (STREAM NATIVE-OUTPUT-STREAM)) :PUBLIC? TRUE)", ((cpp_function_code)(&printCharacter)), NULL);
    defineFunctionObject("CREATE-CHARACTER-TYPE-TABLE", "(DEFUN (CREATE-CHARACTER-TYPE-TABLE (ARRAY (256) OF KEYWORD)) ())", ((cpp_function_code)(&createCharacterTypeTable)), NULL);
    defineFunctionObject("DIGIT-CHARACTER?", "(DEFUN (DIGIT-CHARACTER? BOOLEAN) ((CH CHARACTER)) :DOCUMENTATION \"Return TRUE if `ch' represents a digit.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (EQL? (AREF *CHARACTER-TYPE-TABLE* (CHARACTER-CODE CH)) :DIGIT)))", ((cpp_function_code)(&digitCharacterP)), NULL);
    defineFunctionObject("LETTER-CHARACTER?", "(DEFUN (LETTER-CHARACTER? BOOLEAN) ((CH CHARACTER)) :DOCUMENTATION \"Return TRUE if `ch' represents a letter.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (EQL? (AREF *CHARACTER-TYPE-TABLE* (CHARACTER-CODE CH)) :LETTER)))", ((cpp_function_code)(&letterCharacterP)), NULL);
    defineFunctionObject("UPPER-CASE-CHARACTER?", "(DEFUN (UPPER-CASE-CHARACTER? BOOLEAN) ((CH CHARACTER)) :PUBLIC? TRUE :DOCUMENTATION \"Return TRUE if `ch' represents an upper-case character.\")", ((cpp_function_code)(&upperCaseCharacterP)), NULL);
    defineFunctionObject("LOWER-CASE-CHARACTER?", "(DEFUN (LOWER-CASE-CHARACTER? BOOLEAN) ((CH CHARACTER)) :PUBLIC? TRUE :DOCUMENTATION \"Return TRUE if `ch' represents a lower-case character.\")", ((cpp_function_code)(&lowerCaseCharacterP)), NULL);
    defineFunctionObject("WHITE-SPACE-CHARACTER?", "(DEFUN (WHITE-SPACE-CHARACTER? BOOLEAN) ((CH CHARACTER)) :DOCUMENTATION \"Return TRUE if `ch' is a white space character.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (EQL? (AREF *CHARACTER-TYPE-TABLE* (CHARACTER-CODE CH)) :WHITE-SPACE)))", ((cpp_function_code)(&whiteSpaceCharacterP)), NULL);
    defineFunctionObject("EIGHT-BIT-CHARACTER?", "(DEFUN (EIGHT-BIT-CHARACTER? BOOLEAN) ((CH CHARACTER)) :DOCUMENTATION \"Return TRUE if `ch' is in the upper half of the byte set such as UTF-8 codes, etc.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (>= (CHARACTER-CODE CH) 128)))", ((cpp_function_code)(&eightBitCharacterP)), NULL);
    defineFunctionObject("ALL-UPPER-CASE-STRING?", "(DEFUN (ALL-UPPER-CASE-STRING? BOOLEAN) ((S STRING)) :DOCUMENTATION \"Return TRUE if all letters in `s' are upper case.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allUpperCaseStringP)), NULL);
    defineFunctionObject("ALL-LOWER-CASE-STRING?", "(DEFUN (ALL-LOWER-CASE-STRING? BOOLEAN) ((S STRING)) :DOCUMENTATION \"Return TRUE if all letters in `s' are lower case.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allLowerCaseStringP)), NULL);
    defineFunctionObject("INITIALIZE-CHARACTER-UPCASE-TABLE", "(DEFUN (INITIALIZE-CHARACTER-UPCASE-TABLE STRING) ())", ((cpp_function_code)(&initializeCharacterUpcaseTable)), NULL);
    defineFunctionObject("INITIALIZE-CHARACTER-DOWNCASE-TABLE", "(DEFUN (INITIALIZE-CHARACTER-DOWNCASE-TABLE STRING) ())", ((cpp_function_code)(&initializeCharacterDowncaseTable)), NULL);
    defineFunctionObject("UPCASE-CHARACTER", "(DEFUN (UPCASE-CHARACTER CHARACTER) ((CHAR CHARACTER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"If `char' is lowercase, return its uppercase version,\notherwise, return 'char' unmodified.\" (RETURN (NTH *CHARACTER-UPCASE-TABLE* (CHARACTER-CODE CHAR))))", ((cpp_function_code)(&upcaseCharacter)), NULL);
    defineFunctionObject("DOWNCASE-CHARACTER", "(DEFUN (DOWNCASE-CHARACTER CHARACTER) ((CHAR CHARACTER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"If `char' is uppercase, return its lowercase version,\notherwise, return 'char' unmodified.\" (RETURN (NTH *CHARACTER-DOWNCASE-TABLE* (CHARACTER-CODE CHAR))))", ((cpp_function_code)(&downcaseCharacter)), NULL);
    defineFunctionObject("PRINT-STRING-READABLY", "(DEFUN PRINT-STRING-READABLY ((STRING STRING) (STREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&printStringReadably)), NULL);
    defineFunctionObject("STRING-TO-MUTABLE-STRING", "(DEFUN (STRING-TO-MUTABLE-STRING MUTABLE-STRING) ((S STRING)) :DOCUMENTATION \"Copy `s' into a mutable string with the same content.\nIn Lisp and C++ this simply copies `s'.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP (CL:COPY-SEQ S) :CPP \"strcpy(new (GC) char[strlen(s)+1], s)\" :JAVA \"new StringBuffer(s)\")))", ((cpp_function_code)(((char*  (*) (const char*))(&stringToMutableString)))), NULL);
    defineFunctionObject("MUTABLE-STRING-TO-STRING", "(DEFUN (MUTABLE-STRING-TO-STRING STRING) ((S MUTABLE-STRING)) :DOCUMENTATION \"Convert `s' into a regular string with the same content.\nIn Lisp and C++ this is a no-op.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP S :CPP \"s\" :JAVA \"s.toString()\")))", ((cpp_function_code)(((const char*  (*) (char*))(&mutableStringToString)))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-WRAPPER-TO-FLOAT FLOAT) ((SELF OBJECT)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Object::numberWrapperToFloat))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-WRAPPER-TO-FLOAT FLOAT) ((SELF INTEGER-WRAPPER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&IntegerWrapper::numberWrapperToFloat))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-WRAPPER-TO-FLOAT FLOAT) ((SELF LONG-INTEGER-WRAPPER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&LongIntegerWrapper::numberWrapperToFloat))), NULL);
    defineMethodObject("(DEFMETHOD (NUMBER-WRAPPER-TO-FLOAT FLOAT) ((SELF FLOAT-WRAPPER)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&FloatWrapper::numberWrapperToFloat))), NULL);
    defineFunctionObject("STARTUP-LITERALS", "(DEFUN STARTUP-LITERALS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupLiterals)), NULL);
    { MethodSlot* function = lookupFunction(SYM_LITERALS_STELLA_STARTUP_LITERALS);

      setDynamicSlotValue(function->dynamicSlots, SYM_LITERALS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupLiterals"), NULL_STRING_WRAPPER);
    }
  }
}

void startupLiterals() {
  if (currentStartupTimePhaseP(0)) {
    ZERO_WRAPPER = newIntegerWrapper(0);
    ONE_WRAPPER = newIntegerWrapper(1);
    FALSE_WRAPPER = newBooleanWrapper(false);
    TRUE_WRAPPER = newBooleanWrapper(true);
    NULL_INTEGER_WRAPPER = newIntegerWrapper(NULL_INTEGER);
    NULL_LONG_INTEGER_WRAPPER = newLongIntegerWrapper(NULL_LONG_INTEGER);
    NULL_FLOAT_WRAPPER = newFloatWrapper(NULL_FLOAT);
    NULL_STRING_WRAPPER = newStringWrapper(NULL);
    NULL_MUTABLE_STRING_WRAPPER = newMutableStringWrapper(NULL);
    NULL_CHARACTER_WRAPPER = newCharacterWrapper(NULL_CHARACTER);
    NULL_FUNCTION_CODE_WRAPPER = newFunctionCodeWrapper(NULL);
    NULL_METHOD_CODE_WRAPPER = newMethodCodeWrapper(((cpp_method_code)(NULL)));
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupLiterals1();
      KWD_LITERALS_ESCAPE = ((Keyword*)(internRigidSymbolWrtModule("ESCAPE", NULL, 2)));
      KWD_LITERALS_DELIMITER = ((Keyword*)(internRigidSymbolWrtModule("DELIMITER", NULL, 2)));
      KWD_LITERALS_WHITE_SPACE = ((Keyword*)(internRigidSymbolWrtModule("WHITE-SPACE", NULL, 2)));
      SYM_LITERALS_STELLA_NULL_STRING = ((Symbol*)(internRigidSymbolWrtModule("NULL-STRING", NULL, 0)));
      SYM_LITERALS_STELLA_STARTUP_LITERALS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-LITERALS", NULL, 0)));
      SYM_LITERALS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(4)) {
      helpStartupLiterals2();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupLiterals3();
      helpStartupLiterals4();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL ZERO-WRAPPER INTEGER-WRAPPER NULL :PUBLIC? TRUE)", &ZERO_WRAPPER);
      defineGlobalVariableObject("(DEFGLOBAL ONE-WRAPPER INTEGER-WRAPPER NULL :PUBLIC? TRUE)", &ONE_WRAPPER);
      defineGlobalVariableObject("(DEFGLOBAL TRUE-WRAPPER BOOLEAN-WRAPPER NULL :PUBLIC? TRUE)", &TRUE_WRAPPER);
      defineGlobalVariableObject("(DEFGLOBAL FALSE-WRAPPER BOOLEAN-WRAPPER NULL :PUBLIC? TRUE)", &FALSE_WRAPPER);
      defineGlobalVariableObject("(DEFGLOBAL NULL-INTEGER-WRAPPER INTEGER-WRAPPER NULL :PUBLIC? TRUE)", &NULL_INTEGER_WRAPPER);
      defineGlobalVariableObject("(DEFGLOBAL NULL-LONG-INTEGER-WRAPPER LONG-INTEGER-WRAPPER NULL :PUBLIC? TRUE)", &NULL_LONG_INTEGER_WRAPPER);
      defineGlobalVariableObject("(DEFGLOBAL NULL-FLOAT-WRAPPER FLOAT-WRAPPER NULL :PUBLIC? TRUE)", &NULL_FLOAT_WRAPPER);
      defineGlobalVariableObject("(DEFGLOBAL NULL-STRING-WRAPPER STRING-WRAPPER NULL :PUBLIC? TRUE)", &NULL_STRING_WRAPPER);
      defineGlobalVariableObject("(DEFGLOBAL NULL-MUTABLE-STRING-WRAPPER MUTABLE-STRING-WRAPPER NULL :PUBLIC? TRUE)", &NULL_MUTABLE_STRING_WRAPPER);
      defineGlobalVariableObject("(DEFGLOBAL NULL-CHARACTER-WRAPPER CHARACTER-WRAPPER NULL :PUBLIC? TRUE)", &NULL_CHARACTER_WRAPPER);
      defineGlobalVariableObject("(DEFGLOBAL NULL-FUNCTION-CODE-WRAPPER FUNCTION-CODE-WRAPPER NULL :PUBLIC? TRUE)", &NULL_FUNCTION_CODE_WRAPPER);
      defineGlobalVariableObject("(DEFGLOBAL NULL-METHOD-CODE-WRAPPER METHOD-CODE-WRAPPER NULL :PUBLIC? TRUE)", &NULL_METHOD_CODE_WRAPPER);
      defineGlobalVariableObject("(DEFGLOBAL *LITERAL-TYPE-INFO-TABLE* (HASH-TABLE OF TYPE (KEY-VALUE-LIST OF KEYWORD OBJECT)) (NEW HASH-TABLE) :DOCUMENTATION \"Table that holds a variety of information about literal\ntypes, e.g., the name of their null-wrapper, wrap-function, etc.\")", &oLITERAL_TYPE_INFO_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *LITERAL-TYPES* (LIST OF TYPE) (NEW LIST) :DOCUMENTATION \"List of literal types stored in '*literal-type-info-table*'.\nMaintained for iteration purposes.\")", &oLITERAL_TYPESo);
      defineGlobalVariableObject("(DEFGLOBAL *CHARACTER-TYPE-TABLE* (ARRAY (256) OF KEYWORD) (CREATE-CHARACTER-TYPE-TABLE) :DOCUMENTATION \"Table of character types.  Entry 'i' represents the type\nof the character whose 'char-code' equals 'i'.  Each character is classified \nby one of the following keywords: :DIGIT, :LETTER, :SYMBOL-CONSTITUENT, \n:SYMBOL-QUALIFIER, :ESCAPE, :DELIMITER, :WHITE-SPACE, or :OTHER.\" :PUBLIC? TRUE)", &oCHARACTER_TYPE_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *CHARACTER-UPCASE-TABLE* STRING (INITIALIZE-CHARACTER-UPCASE-TABLE))", &oCHARACTER_UPCASE_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *CHARACTER-DOWNCASE-TABLE* STRING (INITIALIZE-CHARACTER-DOWNCASE-TABLE))", &oCHARACTER_DOWNCASE_TABLEo);
    }
  }
}

Surrogate* SGT_LITERALS_STELLA_BOOLEAN = NULL;

Keyword* KWD_LITERALS_NULL_WRAPPER = NULL;

Symbol* SYM_LITERALS_STELLA_FALSE_WRAPPER = NULL;

Surrogate* SGT_LITERALS_STELLA_INTEGER = NULL;

Symbol* SYM_LITERALS_STELLA_NULL_INTEGER_WRAPPER = NULL;

Surrogate* SGT_LITERALS_STELLA_LONG_INTEGER = NULL;

Symbol* SYM_LITERALS_STELLA_NULL_LONG_INTEGER_WRAPPER = NULL;

Surrogate* SGT_LITERALS_STELLA_FLOAT = NULL;

Symbol* SYM_LITERALS_STELLA_NULL_FLOAT_WRAPPER = NULL;

Surrogate* SGT_LITERALS_STELLA_STRING = NULL;

Symbol* SYM_LITERALS_STELLA_NULL_STRING_WRAPPER = NULL;

Surrogate* SGT_LITERALS_STELLA_MUTABLE_STRING = NULL;

Symbol* SYM_LITERALS_STELLA_NULL_MUTABLE_STRING_WRAPPER = NULL;

Surrogate* SGT_LITERALS_STELLA_CHARACTER = NULL;

Symbol* SYM_LITERALS_STELLA_NULL_CHARACTER_WRAPPER = NULL;

Surrogate* SGT_LITERALS_STELLA_FUNCTION_CODE = NULL;

Symbol* SYM_LITERALS_STELLA_NULL_FUNCTION_CODE_WRAPPER = NULL;

Surrogate* SGT_LITERALS_STELLA_METHOD_CODE = NULL;

Symbol* SYM_LITERALS_STELLA_NULL_METHOD_CODE_WRAPPER = NULL;

Symbol* SYM_LITERALS_STELLA_TRUE = NULL;

Symbol* SYM_LITERALS_STELLA_TRUE_WRAPPER = NULL;

Symbol* SYM_LITERALS_STELLA_FALSE = NULL;

Symbol* SYM_LITERALS_STELLA_WRAP_BOOLEAN = NULL;

Symbol* SYM_LITERALS_STELLA_COERCE_WRAPPED_BOOLEAN_TO_BOOLEAN = NULL;

Keyword* KWD_LITERALS_WRAP_FUNCTION = NULL;

Symbol* SYM_LITERALS_STELLA_WRAP_INTEGER = NULL;

Symbol* SYM_LITERALS_STELLA_WRAP_LONG_INTEGER = NULL;

Symbol* SYM_LITERALS_STELLA_WRAP_FLOAT = NULL;

Symbol* SYM_LITERALS_STELLA_WRAP_STRING = NULL;

Symbol* SYM_LITERALS_STELLA_WRAP_MUTABLE_STRING = NULL;

Symbol* SYM_LITERALS_STELLA_WRAP_CHARACTER = NULL;

Symbol* SYM_LITERALS_STELLA_WRAP_FUNCTION_CODE = NULL;

Symbol* SYM_LITERALS_STELLA_WRAP_METHOD_CODE = NULL;

Surrogate* SGT_LITERALS_STELLA_INTEGER_WRAPPER = NULL;

Surrogate* SGT_LITERALS_STELLA_LONG_INTEGER_WRAPPER = NULL;

Surrogate* SGT_LITERALS_STELLA_FLOAT_WRAPPER = NULL;

Surrogate* SGT_LITERALS_STELLA_BOOLEAN_WRAPPER = NULL;

Surrogate* SGT_LITERALS_STELLA_STRING_WRAPPER = NULL;

Surrogate* SGT_LITERALS_STELLA_VERBATIM_STRING_WRAPPER = NULL;

Surrogate* SGT_LITERALS_STELLA_CHARACTER_WRAPPER = NULL;

Symbol* SYM_LITERALS_STELLA_NULL = NULL;

Surrogate* SGT_LITERALS_STELLA_CONS = NULL;

Symbol* SYM_LITERALS_STELLA_NIL = NULL;

Symbol* SYM_LITERALS_STELLA_CONS = NULL;

Symbol* SYM_LITERALS_STELLA_WRAP_LITERAL = NULL;

Symbol* SYM_LITERALS_STELLA_GET_KWD = NULL;

Symbol* SYM_LITERALS_STELLA_TYPED_SYS = NULL;

Surrogate* SGT_LITERALS_STELLA_SYMBOL = NULL;

Symbol* SYM_LITERALS_STELLA_GET_SGT = NULL;

Symbol* SYM_LITERALS_STELLA_INTERN_COMMON_LISP_SYMBOL = NULL;

Symbol* SYM_LITERALS_STELLA_GET_SYM = NULL;

Symbol* SYM_LITERALS_STELLA_LISTo = NULL;

Symbol* SYM_LITERALS_STELLA_a = NULL;

Symbol* SYM_LITERALS_STELLA_aa = NULL;

Symbol* SYM_LITERALS_STELLA_CONCATENATE = NULL;

Keyword* KWD_LITERALS_OTHER = NULL;

Keyword* KWD_LITERALS_DIGIT = NULL;

Keyword* KWD_LITERALS_LETTER = NULL;

Keyword* KWD_LITERALS_SYMBOL_CONSTITUENT = NULL;

Keyword* KWD_LITERALS_SYMBOL_QUALIFIER = NULL;

Keyword* KWD_LITERALS_ESCAPE = NULL;

Keyword* KWD_LITERALS_DELIMITER = NULL;

Keyword* KWD_LITERALS_WHITE_SPACE = NULL;

Symbol* SYM_LITERALS_STELLA_NULL_STRING = NULL;

Symbol* SYM_LITERALS_STELLA_STARTUP_LITERALS = NULL;

Symbol* SYM_LITERALS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
