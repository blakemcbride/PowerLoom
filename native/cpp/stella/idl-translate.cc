//  -*- Mode: C++ -*-

// idl-translate.cc

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

Object* idlTranslateATree(Object* tree) {
  if (safePrimaryType(tree) == SGT_IDL_TRANSLATE_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if (tree == NIL) {
        return (tree->idlTranslateAtomicTree());
      }
      else {
        return (idlTranslateNull());
      }
    }
  }
  else {
    if (!((boolean)(tree))) {
      return (idlTranslateNull());
    }
    return (tree->idlTranslateAtomicTree());
  }
}

Cons* idlTranslateUnit(TranslationUnit* unit) {
  { Symbol* testValue000 = unit->category;

    if (testValue000 == SYM_IDL_TRANSLATE_STELLA_GLOBAL_VARIABLE) {
      return (NULL);
    }
    else if (testValue000 == SYM_IDL_TRANSLATE_STELLA_TYPE) {
      return (idlTranslateDeftypeUnit(unit));
    }
    else if (testValue000 == SYM_IDL_TRANSLATE_STELLA_CLASS) {
      return (idlTranslateDefineNativeClassUnit(unit));
    }
    else if ((testValue000 == SYM_IDL_TRANSLATE_STELLA_METHOD) ||
        (testValue000 == SYM_IDL_TRANSLATE_STELLA_MACRO)) {
      return (NULL);
    }
    else if (testValue000 == SYM_IDL_TRANSLATE_STELLA_PRINT_METHOD) {
      return (NULL);
    }
    else if ((testValue000 == SYM_IDL_TRANSLATE_STELLA_STARTUP_TIME_PROGN) ||
        (testValue000 == SYM_IDL_TRANSLATE_STELLA_VERBATIM)) {
      return (NULL);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Cons* idlTranslateDeftypeUnit(TranslationUnit* unit) {
  return (listO(3, SYM_IDL_TRANSLATE_STELLA_IDL_TYPEDEF, idlTranslateName(((Symbol*)(((Cons*)(unit->codeRegister))->rest->value))), cons(idlTranslateTypeSpec(((StandardObject*)(((Surrogate*)(unit->theObject))->surrogateValue))), NIL)));
}

Cons* idlTranslateNull() {
  return (listO(3, SYM_IDL_TRANSLATE_STELLA_IDL_IDENT, wrapString("NULL"), NIL));
}

Cons* Object::idlTranslateAtomicTree() {
  { Object* tree = this;

    return (listO(3, SYM_IDL_TRANSLATE_STELLA_IDL_LITERAL, tree, NIL));
  }
}

Cons* Symbol::idlTranslateAtomicTree() {
  { Symbol* tree = this;

    return (listO(3, SYM_IDL_TRANSLATE_STELLA_IDL_IDENT, idlTranslateName(tree), NIL));
  }
}

StringWrapper* idlTranslateTypeSpec(StandardObject* typespec) {
  { Surrogate* testValue000 = safePrimaryType(typespec);

    if (subtypeOfParametricTypeSpecifierP(testValue000)) {
      { StandardObject* typespec000 = typespec;
        ParametricTypeSpecifier* typespec = ((ParametricTypeSpecifier*)(typespec000));

        return (wrapString(stringConcatenate(idlTranslateTypeSpec(typespec->specifierBaseType)->wrapperValue, stringConcatenate("<", stringConcatenate(idlTranslateTypeSpec(((StandardObject*)(typespec->specifierParameterTypes->first())))->wrapperValue, ">", 0), 0), 0)));
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { StandardObject* typespec001 = typespec;
        Surrogate* typespec = ((Surrogate*)(typespec001));

        if (((StringWrapper*)(dynamicSlotValue(((Class*)(typespec->surrogateValue))->dynamicSlots, SYM_IDL_TRANSLATE_STELLA_CLASS_IDL_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue != NULL) {
          return (wrapString(((StringWrapper*)(dynamicSlotValue(((Class*)(typespec->surrogateValue))->dynamicSlots, SYM_IDL_TRANSLATE_STELLA_CLASS_IDL_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue));
        }
        else {
          return (idlTranslateClassName(symbolize(((Class*)(typespec->surrogateValue))->classType)));
        }
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

StringWrapper* idlTranslateClassName(GeneralizedSymbol* namesymbol) {
  return (wrapString(idlSubstituteForbiddenCharacters(idlChangeCase(((Class*)(namesymbol->surrogatify()->surrogateValue))->classType, KWD_IDL_TRANSLATE_CAPITALIZED), KWD_IDL_TRANSLATE_CAPITALIZED)));
}

const char* idlCreateCharacterSubstitutionTable() {
  { char* table = native_make_mutable_string(256, '_');

    { int code = NULL_INTEGER;
      int iter000 = (int)(unsigned char) '0';
      int upperBound000 = (int)(unsigned char) '9';
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter000 <= upperBound000); 
            iter000 = iter000 + 1) {
        code = iter000;
        table[code] = '=';
      }
    }
    { int code = NULL_INTEGER;
      int iter001 = (int)(unsigned char) 'A';
      int upperBound001 = (int)(unsigned char) 'Z';
      boolean unboundedP001 = upperBound001 == NULL_INTEGER;

      for  (; unboundedP001 ||
                (iter001 <= upperBound001); 
            iter001 = iter001 + 1) {
        code = iter001;
        table[code] = '=';
      }
    }
    { int code = NULL_INTEGER;
      int iter002 = (int)(unsigned char) 'a';
      int upperBound002 = (int)(unsigned char) 'z';
      boolean unboundedP002 = upperBound002 == NULL_INTEGER;

      for  (; unboundedP002 ||
                (iter002 <= upperBound002); 
            iter002 = iter002 + 1) {
        code = iter002;
        table[code] = '=';
      }
    }
    table[((int)(unsigned char) '_')] = '=';
    table[((int)(unsigned char) ' ')] = '_';
    table[((int)(unsigned char) '!')] = 'X';
    table[((int)(unsigned char) '"')] = '_';
    table[((int)(unsigned char) '#')] = 'H';
    table[((int)(unsigned char) '$')] = 'B';
    table[((int)(unsigned char) '%')] = 'R';
    table[((int)(unsigned char) '&')] = 'A';
    table[((int)(unsigned char) '\'')] = 'Q';
    table[((int)(unsigned char) '(')] = '_';
    table[((int)(unsigned char) ')')] = '_';
    table[((int)(unsigned char) '*')] = 'O';
    table[((int)(unsigned char) '+')] = 'I';
    table[((int)(unsigned char) ',')] = '_';
    table[((int)(unsigned char) '-')] = '_';
    table[((int)(unsigned char) '.')] = 'D';
    table[((int)(unsigned char) '/')] = 'S';
    table[((int)(unsigned char) ':')] = 'C';
    table[((int)(unsigned char) ';')] = '_';
    table[((int)(unsigned char) '<')] = 'L';
    table[((int)(unsigned char) '=')] = 'E';
    table[((int)(unsigned char) '>')] = 'G';
    table[((int)(unsigned char) '?')] = 'P';
    table[((int)(unsigned char) '@')] = 'M';
    table[((int)(unsigned char) '[')] = '_';
    table[((int)(unsigned char) '\\')] = '_';
    table[((int)(unsigned char) ']')] = '_';
    table[((int)(unsigned char) '^')] = 'U';
    table[((int)(unsigned char) '`')] = '_';
    table[((int)(unsigned char) '{')] = '_';
    table[((int)(unsigned char) '|')] = 'V';
    table[((int)(unsigned char) '}')] = '_';
    table[((int)(unsigned char) '~')] = 'T';
    return (table);
  }
}

const char* oIDL_CHARACTER_SUBSTITUTION_TABLEo = NULL;

const char* idlSubstituteForbiddenCharacters(const char* name, Keyword* caseconvention) {
  { char* result = NULL;
    char substitution = NULL_CHARACTER;

    switch (name[0]) {
      case '0': 
        result = stringToMutableString(replaceFirstCharacterWithString(name, "zero"));
        break;
      case '1': 
        result = stringToMutableString(replaceFirstCharacterWithString(name, "one"));
        break;
      case '2': 
        result = stringToMutableString(replaceFirstCharacterWithString(name, "two"));
        break;
      case '3': 
        result = stringToMutableString(replaceFirstCharacterWithString(name, "three"));
        break;
      case '4': 
        result = stringToMutableString(replaceFirstCharacterWithString(name, "four"));
        break;
      case '5': 
        result = stringToMutableString(replaceFirstCharacterWithString(name, "five"));
        break;
      case '6': 
        result = stringToMutableString(replaceFirstCharacterWithString(name, "six"));
        break;
      case '7': 
        result = stringToMutableString(replaceFirstCharacterWithString(name, "seven"));
        break;
      case '8': 
        result = stringToMutableString(replaceFirstCharacterWithString(name, "eight"));
        break;
      case '9': 
        result = stringToMutableString(replaceFirstCharacterWithString(name, "nine"));
        break;
      default:
        result = strcpy(new (GC) char[strlen(name)+1], name);
        break;
    }
    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = strlen(result) - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        substitution = oIDL_CHARACTER_SUBSTITUTION_TABLEo[((int)(unsigned char) (result[i]))];
        if (!(substitution == '=')) {
          if (caseconvention == KWD_IDL_TRANSLATE_UPPERCASE) {
            result[i] = (oCHARACTER_DOWNCASE_TABLEo[((int)(unsigned char) substitution)]);
          }
          else if (caseconvention == KWD_IDL_TRANSLATE_LOWERCASE) {
            result[i] = (oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) substitution)]);
          }
          else if (caseconvention == KWD_IDL_TRANSLATE_CAPITALIZED) {
            result[i] = (oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) substitution)]);
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << caseconvention << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
      }
    }
    return (result);
  }
}

const char* idlChangeCase(GeneralizedSymbol* symbol, Keyword* caseconvention) {
  { Module* module = ((Module*)(symbol->homeContext));
    const char* name = symbol->symbolName;

    if (!((boolean)(module))) {
      module = oMODULEo;
    }
    if (module->caseSensitiveP) {
      return (stringCopy(name));
    }
    if (caseconvention == KWD_IDL_TRANSLATE_UPPERCASE) {
      return (stringUpcase(name));
    }
    else if (caseconvention == KWD_IDL_TRANSLATE_LOWERCASE) {
      return (stringDowncase(name));
    }
    else if (caseconvention == KWD_IDL_TRANSLATE_CAPITALIZED) {
      return (stringCapitalize(name));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << caseconvention << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

StringWrapper* idlYieldRenamedReservedWord(Symbol* word) {
  return (wrapString(stringConcatenate("renamed_", stringCapitalize(word->symbolName), 0)));
}

StringHashTable* idlCreateReservedWordTable() {
  { StringHashTable* table = newStringHashTable();

    { Object* word = NULL;
      Cons* iter000 = listO(49, SYM_IDL_TRANSLATE_STELLA_ASM, SYM_IDL_TRANSLATE_STELLA_AUTO, SYM_IDL_TRANSLATE_STELLA_BREAK, SYM_IDL_TRANSLATE_STELLA_CASE, SYM_IDL_TRANSLATE_STELLA_CATCH, SYM_IDL_TRANSLATE_STELLA_CHAR, SYM_IDL_TRANSLATE_STELLA_CLASS, SYM_IDL_TRANSLATE_STELLA_CONST, SYM_IDL_TRANSLATE_STELLA_CONTINUE, SYM_IDL_TRANSLATE_STELLA_DEFAULT, SYM_IDL_TRANSLATE_STELLA_DELETE, SYM_IDL_TRANSLATE_STELLA_DO, SYM_IDL_TRANSLATE_STELLA_DOUBLE, SYM_IDL_TRANSLATE_STELLA_ELSE, SYM_IDL_TRANSLATE_STELLA_ENUM, SYM_IDL_TRANSLATE_STELLA_EXTERN, SYM_IDL_TRANSLATE_STELLA_FLOAT, SYM_IDL_TRANSLATE_STELLA_FOR, SYM_IDL_TRANSLATE_STELLA_FRIEND, SYM_IDL_TRANSLATE_STELLA_GOTO, SYM_IDL_TRANSLATE_STELLA_IF, SYM_IDL_TRANSLATE_STELLA_INLINE, SYM_IDL_TRANSLATE_STELLA_INT, SYM_IDL_TRANSLATE_STELLA_LONG, SYM_IDL_TRANSLATE_STELLA_NEW, SYM_IDL_TRANSLATE_STELLA_OPERATOR, SYM_IDL_TRANSLATE_STELLA_PRIVATE, SYM_IDL_TRANSLATE_STELLA_PROTECTED, SYM_IDL_TRANSLATE_STELLA_PUBLIC, SYM_IDL_TRANSLATE_STELLA_REGISTER, SYM_IDL_TRANSLATE_STELLA_RETURN, SYM_IDL_TRANSLATE_STELLA_SHORT, SYM_IDL_TRANSLATE_STELLA_SIGNED, SYM_IDL_TRANSLATE_STELLA_SIZEOF, SYM_IDL_TRANSLATE_STELLA_STATIC, SYM_IDL_TRANSLATE_STELLA_STRUCT, SYM_IDL_TRANSLATE_STELLA_SWITCH, SYM_IDL_TRANSLATE_STELLA_TEMPLATE, SYM_IDL_TRANSLATE_STELLA_THROW, SYM_IDL_TRANSLATE_STELLA_TRY, SYM_IDL_TRANSLATE_STELLA_TYPEDEF, SYM_IDL_TRANSLATE_STELLA_UNION, SYM_IDL_TRANSLATE_STELLA_UNSIGNED, SYM_IDL_TRANSLATE_STELLA_VIRTUAL, SYM_IDL_TRANSLATE_STELLA_VOID, SYM_IDL_TRANSLATE_STELLA_VOLATILE, SYM_IDL_TRANSLATE_STELLA_WHILE, SYM_IDL_TRANSLATE_STELLA_TYPENAME, NIL);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        word = iter000->value;
        table->insertAt(((Symbol*)(word))->symbolName, idlYieldRenamedReservedWord(((Symbol*)(word))));
      }
    }
    table->insertAt("++", wrapString("stella_Increment"));
    table->insertAt("--", wrapString("stella_Decrement"));
    return (table);
  }
}

StringHashTable* oIDL_RESERVED_WORD_TABLEo = NULL;

StringWrapper* idlLookupReservedWordTable(Symbol* word) {
  { StringWrapper* entry = ((StringWrapper*)(oIDL_RESERVED_WORD_TABLEo->lookup(word->symbolName)));

    if (((boolean)(entry))) {
      return (wrapString(entry->wrapperValue));
    }
    else {
      return (NULL);
    }
  }
}

StringWrapper* idlTranslateName(Symbol* namesymbol) {
  { StringWrapper* reservedname = idlLookupReservedWordTable(namesymbol);

    if (!((boolean)(namesymbol))) {
      return (wrapString("NULL"));
    }
    if (((boolean)(reservedname))) {
      return (reservedname);
    }
    return (wrapString(idlSubstituteForbiddenCharacters(idlChangeCase(namesymbol, KWD_IDL_TRANSLATE_LOWERCASE), KWD_IDL_TRANSLATE_LOWERCASE)));
  }
}

StringWrapper* idlTranslateSymbolConstantName(GeneralizedSymbol* symbol) {
  { const char* prefix = NULL;

    { Surrogate* testValue000 = safePrimaryType(symbol);

      if (subtypeOfSymbolP(testValue000)) {
        { GeneralizedSymbol* symbol000 = symbol;
          Symbol* symbol = ((Symbol*)(symbol000));

          prefix = stringConcatenate("SYM_", ((Module*)(symbol->homeContext))->contextName(), 0);
        }
      }
      else if (subtypeOfSurrogateP(testValue000)) {
        { GeneralizedSymbol* symbol001 = symbol;
          Surrogate* symbol = ((Surrogate*)(symbol001));

          prefix = stringConcatenate("SGT_", ((Module*)(symbol->homeContext))->contextName(), 0);
        }
      }
      else if (subtypeOfKeywordP(testValue000)) {
        { GeneralizedSymbol* symbol002 = symbol;
          Keyword* symbol = ((Keyword*)(symbol002));

          prefix = "KWD";
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    return (wrapString(idlSubstituteForbiddenCharacters(stringConcatenate(prefix, stringConcatenate("_", symbol->symbolName, 0), 0), KWD_IDL_TRANSLATE_UPPERCASE)));
  }
}

StringWrapper* idlTranslateSymbolConstantId(GeneralizedSymbol* symbol) {
  { StringWrapper* translatedsymbol = idlTranslateSymbolConstantName(symbol);

    translatedsymbol->wrapperValue = stringConcatenate(translatedsymbol->wrapperValue, "_id", 0);
    return (translatedsymbol);
  }
}

StringWrapper* idlTranslateSymbolName(Symbol* symbol) {
  return (idlTranslateSymbolConstantName(symbol));
}

StringWrapper* idlTranslateSymbolId(Symbol* symbol) {
  return (idlTranslateSymbolConstantId(symbol));
}

StringWrapper* idlTranslateSurrogateName(Surrogate* surrogate) {
  return (idlTranslateSymbolConstantName(surrogate));
}

StringWrapper* idlTranslateSurrogateId(Surrogate* surrogate) {
  return (idlTranslateSymbolConstantId(surrogate));
}

StringWrapper* idlTranslateKeywordName(Keyword* keyword) {
  return (idlTranslateSymbolConstantName(keyword));
}

StringWrapper* idlTranslateKeywordId(Keyword* keyword) {
  return (idlTranslateSymbolConstantId(keyword));
}

StringWrapper* idlTranslateClassParameterName(Symbol* namesymbol) {
  return (wrapString(idlSubstituteForbiddenCharacters(idlChangeCase(namesymbol, KWD_IDL_TRANSLATE_UPPERCASE), KWD_IDL_TRANSLATE_UPPERCASE)));
}

Symbol* idlCreateOverloadedFunctionName(Symbol* functionname, Surrogate* classtype) {
  return (internSymbol(stringConcatenate(classtype->symbolName, stringConcatenate("-", functionname->symbolName, 0), 0)));
}

boolean idlMethodObjectIsOverloadedFunctionP(MethodSlot* method) {
  return ((!method->methodFunctionP) &&
      (((StringWrapper*)(dynamicSlotValue(((Class*)(method->slotOwner->surrogateValue))->dynamicSlots, SYM_IDL_TRANSLATE_STELLA_CLASS_IDL_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue != NULL));
}

StringWrapper* idlTranslateFunctionName(MethodSlot* function) {
  { Symbol* functionname = function->slotName;
    const char* translatedname = NULL;

    if (idlMethodObjectIsOverloadedFunctionP(function)) {
      functionname = idlCreateOverloadedFunctionName(functionname, function->slotOwner);
    }
    translatedname = idlTranslateName(functionname)->wrapperValue;
    if (function->methodSetterP) {
      translatedname = stringConcatenate(translatedname, "_setter", 0);
    }
    if (slotReaderP(function)) {
      translatedname = stringConcatenate(translatedname, "_reader", 0);
    }
    return (wrapString(translatedname));
  }
}

Object* idlTranslateMethodParameter(Symbol* name, StandardObject* type, Symbol* direction) {
  return (cons(idlTranslateName(direction), cons(idlTranslateTypeSpec(type), cons(idlTranslateName(name), NIL))));
}

Cons* idlTranslateMethodParameters(MethodSlot* method) {
  { Cons* result = NIL;
    Cons* directions = NIL;

    if (method->methodParameterDirections_reader()->emptyP()) {
      { Symbol* name = NULL;
        Cons* iter000 = method->methodParameterNames_reader()->rest();
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          name = ((Symbol*)(iter000->value));
          name = name;
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(SYM_IDL_TRANSLATE_STELLA_IN, NIL);
              if (directions == NIL) {
                directions = collect000;
              }
              else {
                addConsToEndOfConsList(directions, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(SYM_IDL_TRANSLATE_STELLA_IN, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    else {
      directions = method->methodParameterDirections_reader()->rest();
    }
    { Symbol* name = NULL;
      Cons* iter001 = method->methodParameterNames_reader()->rest();
      StandardObject* type = NULL;
      Cons* iter002 = method->methodParameterTypeSpecifiers_reader()->rest();
      Object* direction = NULL;
      Cons* iter003 = directions;
      Cons* collect001 = NULL;

      for  (; (!(iter001 == NIL)) &&
                ((!(iter002 == NIL)) &&
                 (!(iter003 == NIL))); 
            iter001 = iter001->rest,
            iter002 = iter002->rest,
            iter003 = iter003->rest) {
        name = ((Symbol*)(iter001->value));
        type = ((StandardObject*)(iter002->value));
        direction = iter003->value;
        if (!((boolean)(collect001))) {
          {
            collect001 = cons(idlTranslateMethodParameter(name, type, ((Symbol*)(direction))), NIL);
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
            collect001->rest = cons(idlTranslateMethodParameter(name, type, ((Symbol*)(direction))), NIL);
            collect001 = collect001->rest;
          }
        }
      }
    }
    return (result);
  }
}

StringWrapper* idlTranslateConstructorName(MethodSlot* constructor) {
  return (idlTranslateClassName(constructor->slotName));
}

void helpStartupIdlTranslate1() {
  {
    SGT_IDL_TRANSLATE_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SYM_IDL_TRANSLATE_STELLA_GLOBAL_VARIABLE = ((Symbol*)(internRigidSymbolWrtModule("GLOBAL-VARIABLE", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_TYPE = ((Symbol*)(internRigidSymbolWrtModule("TYPE", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_CLASS = ((Symbol*)(internRigidSymbolWrtModule("CLASS", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_METHOD = ((Symbol*)(internRigidSymbolWrtModule("METHOD", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_MACRO = ((Symbol*)(internRigidSymbolWrtModule("MACRO", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_PRINT_METHOD = ((Symbol*)(internRigidSymbolWrtModule("PRINT-METHOD", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_STARTUP_TIME_PROGN = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-TIME-PROGN", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_VERBATIM = ((Symbol*)(internRigidSymbolWrtModule("VERBATIM", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_IDL_TYPEDEF = ((Symbol*)(internRigidSymbolWrtModule("IDL_TYPEDEF", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_IDL_IDENT = ((Symbol*)(internRigidSymbolWrtModule("IDL_IDENT", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_IDL_LITERAL = ((Symbol*)(internRigidSymbolWrtModule("IDL_LITERAL", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_CLASS_IDL_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-IDL-NATIVE-TYPE", NULL, 0)));
    KWD_IDL_TRANSLATE_CAPITALIZED = ((Keyword*)(internRigidSymbolWrtModule("CAPITALIZED", NULL, 2)));
    KWD_IDL_TRANSLATE_UPPERCASE = ((Keyword*)(internRigidSymbolWrtModule("UPPERCASE", NULL, 2)));
    KWD_IDL_TRANSLATE_LOWERCASE = ((Keyword*)(internRigidSymbolWrtModule("LOWERCASE", NULL, 2)));
    SYM_IDL_TRANSLATE_STELLA_ASM = ((Symbol*)(internRigidSymbolWrtModule("ASM", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_AUTO = ((Symbol*)(internRigidSymbolWrtModule("AUTO", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_BREAK = ((Symbol*)(internRigidSymbolWrtModule("BREAK", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_CASE = ((Symbol*)(internRigidSymbolWrtModule("CASE", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_CATCH = ((Symbol*)(internRigidSymbolWrtModule("CATCH", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_CHAR = ((Symbol*)(internRigidSymbolWrtModule("CHAR", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_CONST = ((Symbol*)(internRigidSymbolWrtModule("CONST", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_CONTINUE = ((Symbol*)(internRigidSymbolWrtModule("CONTINUE", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_DEFAULT = ((Symbol*)(internRigidSymbolWrtModule("DEFAULT", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_DELETE = ((Symbol*)(internRigidSymbolWrtModule("DELETE", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_DO = ((Symbol*)(internRigidSymbolWrtModule("DO", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_DOUBLE = ((Symbol*)(internRigidSymbolWrtModule("DOUBLE", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_ELSE = ((Symbol*)(internRigidSymbolWrtModule("ELSE", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_ENUM = ((Symbol*)(internRigidSymbolWrtModule("ENUM", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_EXTERN = ((Symbol*)(internRigidSymbolWrtModule("EXTERN", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_FLOAT = ((Symbol*)(internRigidSymbolWrtModule("FLOAT", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_FOR = ((Symbol*)(internRigidSymbolWrtModule("FOR", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_FRIEND = ((Symbol*)(internRigidSymbolWrtModule("FRIEND", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_GOTO = ((Symbol*)(internRigidSymbolWrtModule("GOTO", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_IF = ((Symbol*)(internRigidSymbolWrtModule("IF", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_INLINE = ((Symbol*)(internRigidSymbolWrtModule("INLINE", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_INT = ((Symbol*)(internRigidSymbolWrtModule("INT", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_LONG = ((Symbol*)(internRigidSymbolWrtModule("LONG", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_NEW = ((Symbol*)(internRigidSymbolWrtModule("NEW", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_OPERATOR = ((Symbol*)(internRigidSymbolWrtModule("OPERATOR", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_PRIVATE = ((Symbol*)(internRigidSymbolWrtModule("PRIVATE", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_PROTECTED = ((Symbol*)(internRigidSymbolWrtModule("PROTECTED", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_PUBLIC = ((Symbol*)(internRigidSymbolWrtModule("PUBLIC", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_REGISTER = ((Symbol*)(internRigidSymbolWrtModule("REGISTER", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_RETURN = ((Symbol*)(internRigidSymbolWrtModule("RETURN", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_SHORT = ((Symbol*)(internRigidSymbolWrtModule("SHORT", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_SIGNED = ((Symbol*)(internRigidSymbolWrtModule("SIGNED", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_SIZEOF = ((Symbol*)(internRigidSymbolWrtModule("SIZEOF", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_STATIC = ((Symbol*)(internRigidSymbolWrtModule("STATIC", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_STRUCT = ((Symbol*)(internRigidSymbolWrtModule("STRUCT", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_SWITCH = ((Symbol*)(internRigidSymbolWrtModule("SWITCH", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_TEMPLATE = ((Symbol*)(internRigidSymbolWrtModule("TEMPLATE", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_THROW = ((Symbol*)(internRigidSymbolWrtModule("THROW", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_TRY = ((Symbol*)(internRigidSymbolWrtModule("TRY", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_TYPEDEF = ((Symbol*)(internRigidSymbolWrtModule("TYPEDEF", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_UNION = ((Symbol*)(internRigidSymbolWrtModule("UNION", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_UNSIGNED = ((Symbol*)(internRigidSymbolWrtModule("UNSIGNED", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_VIRTUAL = ((Symbol*)(internRigidSymbolWrtModule("VIRTUAL", NULL, 0)));
    SYM_IDL_TRANSLATE_STELLA_VOID = ((Symbol*)(internRigidSymbolWrtModule("VOID", NULL, 0)));
  }
}

void startupIdlTranslate() {
  if (currentStartupTimePhaseP(1)) {
    defineModuleFromStringifiedSource("/IDL-THEORY", "(:CASE-SENSITIVE? TRUE :USES () :LISP-PACKAGE \"IDL\")");
    defineModuleFromStringifiedSource("/IDL-THEORY/IDL-USER-THEORY", "(:CASE-SENSITIVE? TRUE :USES () :LISP-PACKAGE \"IDL-USER\")");
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupIdlTranslate1();
      SYM_IDL_TRANSLATE_STELLA_VOLATILE = ((Symbol*)(internRigidSymbolWrtModule("VOLATILE", NULL, 0)));
      SYM_IDL_TRANSLATE_STELLA_WHILE = ((Symbol*)(internRigidSymbolWrtModule("WHILE", NULL, 0)));
      SYM_IDL_TRANSLATE_STELLA_TYPENAME = ((Symbol*)(internRigidSymbolWrtModule("TYPENAME", NULL, 0)));
      SYM_IDL_TRANSLATE_STELLA_IN = ((Symbol*)(internRigidSymbolWrtModule("IN", NULL, 0)));
      SYM_IDL_TRANSLATE_STELLA_STARTUP_IDL_TRANSLATE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-IDL-TRANSLATE", NULL, 0)));
      SYM_IDL_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(4)) {
      oIDL_CHARACTER_SUBSTITUTION_TABLEo = idlCreateCharacterSubstitutionTable();
      oIDL_RESERVED_WORD_TABLEo = idlCreateReservedWordTable();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("IDL-TRANSLATE-A-TREE", "(DEFUN (IDL-TRANSLATE-A-TREE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&idlTranslateATree)), NULL);
      defineFunctionObject("IDL-TRANSLATE-UNIT", "(DEFUN (IDL-TRANSLATE-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&idlTranslateUnit)), NULL);
      defineFunctionObject("IDL-TRANSLATE-DEFTYPE-UNIT", "(DEFUN (IDL-TRANSLATE-DEFTYPE-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&idlTranslateDeftypeUnit)), NULL);
      defineFunctionObject("IDL-TRANSLATE-NULL", "(DEFUN (IDL-TRANSLATE-NULL CONS) ())", ((cpp_function_code)(&idlTranslateNull)), NULL);
      defineMethodObject("(DEFMETHOD (IDL-TRANSLATE-ATOMIC-TREE CONS) ((TREE OBJECT)))", wrapMethodCode(((cpp_method_code)(&Object::idlTranslateAtomicTree))), NULL);
      defineMethodObject("(DEFMETHOD (IDL-TRANSLATE-ATOMIC-TREE CONS) ((TREE SYMBOL)))", wrapMethodCode(((cpp_method_code)(&Symbol::idlTranslateAtomicTree))), NULL);
      defineFunctionObject("IDL-TRANSLATE-TYPE-SPEC", "(DEFUN (IDL-TRANSLATE-TYPE-SPEC STRING-WRAPPER) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&idlTranslateTypeSpec)), NULL);
      defineFunctionObject("IDL-TRANSLATE-CLASS-NAME", "(DEFUN (IDL-TRANSLATE-CLASS-NAME STRING-WRAPPER) ((NAMESYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&idlTranslateClassName)), NULL);
      defineFunctionObject("IDL-CREATE-CHARACTER-SUBSTITUTION-TABLE", "(DEFUN (IDL-CREATE-CHARACTER-SUBSTITUTION-TABLE STRING) ())", ((cpp_function_code)(&idlCreateCharacterSubstitutionTable)), NULL);
      defineFunctionObject("IDL-SUBSTITUTE-FORBIDDEN-CHARACTERS", "(DEFUN (IDL-SUBSTITUTE-FORBIDDEN-CHARACTERS STRING) ((NAME STRING) (CASECONVENTION KEYWORD)))", ((cpp_function_code)(&idlSubstituteForbiddenCharacters)), NULL);
      defineFunctionObject("IDL-CHANGE-CASE", "(DEFUN (IDL-CHANGE-CASE STRING) ((SYMBOL GENERALIZED-SYMBOL) (CASECONVENTION KEYWORD)))", ((cpp_function_code)(&idlChangeCase)), NULL);
      defineFunctionObject("IDL-YIELD-RENAMED-RESERVED-WORD", "(DEFUN (IDL-YIELD-RENAMED-RESERVED-WORD STRING-WRAPPER) ((WORD SYMBOL)))", ((cpp_function_code)(&idlYieldRenamedReservedWord)), NULL);
      defineFunctionObject("IDL-CREATE-RESERVED-WORD-TABLE", "(DEFUN (IDL-CREATE-RESERVED-WORD-TABLE STRING-HASH-TABLE) ())", ((cpp_function_code)(&idlCreateReservedWordTable)), NULL);
      defineFunctionObject("IDL-LOOKUP-RESERVED-WORD-TABLE", "(DEFUN (IDL-LOOKUP-RESERVED-WORD-TABLE STRING-WRAPPER) ((WORD SYMBOL)))", ((cpp_function_code)(&idlLookupReservedWordTable)), NULL);
      defineFunctionObject("IDL-TRANSLATE-NAME", "(DEFUN (IDL-TRANSLATE-NAME STRING-WRAPPER) ((NAMESYMBOL SYMBOL)))", ((cpp_function_code)(&idlTranslateName)), NULL);
      defineFunctionObject("IDL-TRANSLATE-SYMBOL-CONSTANT-NAME", "(DEFUN (IDL-TRANSLATE-SYMBOL-CONSTANT-NAME STRING-WRAPPER) ((SYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&idlTranslateSymbolConstantName)), NULL);
      defineFunctionObject("IDL-TRANSLATE-SYMBOL-CONSTANT-ID", "(DEFUN (IDL-TRANSLATE-SYMBOL-CONSTANT-ID STRING-WRAPPER) ((SYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&idlTranslateSymbolConstantId)), NULL);
      defineFunctionObject("IDL-TRANSLATE-SYMBOL-NAME", "(DEFUN (IDL-TRANSLATE-SYMBOL-NAME STRING-WRAPPER) ((SYMBOL SYMBOL)))", ((cpp_function_code)(&idlTranslateSymbolName)), NULL);
      defineFunctionObject("IDL-TRANSLATE-SYMBOL-ID", "(DEFUN (IDL-TRANSLATE-SYMBOL-ID STRING-WRAPPER) ((SYMBOL SYMBOL)))", ((cpp_function_code)(&idlTranslateSymbolId)), NULL);
      defineFunctionObject("IDL-TRANSLATE-SURROGATE-NAME", "(DEFUN (IDL-TRANSLATE-SURROGATE-NAME STRING-WRAPPER) ((SURROGATE SURROGATE)))", ((cpp_function_code)(&idlTranslateSurrogateName)), NULL);
      defineFunctionObject("IDL-TRANSLATE-SURROGATE-ID", "(DEFUN (IDL-TRANSLATE-SURROGATE-ID STRING-WRAPPER) ((SURROGATE SURROGATE)))", ((cpp_function_code)(&idlTranslateSurrogateId)), NULL);
      defineFunctionObject("IDL-TRANSLATE-KEYWORD-NAME", "(DEFUN (IDL-TRANSLATE-KEYWORD-NAME STRING-WRAPPER) ((KEYWORD KEYWORD)))", ((cpp_function_code)(&idlTranslateKeywordName)), NULL);
      defineFunctionObject("IDL-TRANSLATE-KEYWORD-ID", "(DEFUN (IDL-TRANSLATE-KEYWORD-ID STRING-WRAPPER) ((KEYWORD KEYWORD)))", ((cpp_function_code)(&idlTranslateKeywordId)), NULL);
      defineFunctionObject("IDL-TRANSLATE-CLASS-PARAMETER-NAME", "(DEFUN (IDL-TRANSLATE-CLASS-PARAMETER-NAME STRING-WRAPPER) ((NAMESYMBOL SYMBOL)))", ((cpp_function_code)(&idlTranslateClassParameterName)), NULL);
      defineFunctionObject("IDL-CREATE-OVERLOADED-FUNCTION-NAME", "(DEFUN (IDL-CREATE-OVERLOADED-FUNCTION-NAME SYMBOL) ((FUNCTIONNAME SYMBOL) (CLASSTYPE TYPE)))", ((cpp_function_code)(&idlCreateOverloadedFunctionName)), NULL);
      defineFunctionObject("IDL-METHOD-OBJECT-IS-OVERLOADED-FUNCTION?", "(DEFUN (IDL-METHOD-OBJECT-IS-OVERLOADED-FUNCTION? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&idlMethodObjectIsOverloadedFunctionP)), NULL);
      defineFunctionObject("IDL-TRANSLATE-FUNCTION-NAME", "(DEFUN (IDL-TRANSLATE-FUNCTION-NAME STRING-WRAPPER) ((FUNCTION METHOD-SLOT)))", ((cpp_function_code)(&idlTranslateFunctionName)), NULL);
      defineFunctionObject("IDL-TRANSLATE-METHOD-PARAMETER", "(DEFUN (IDL-TRANSLATE-METHOD-PARAMETER OBJECT) ((NAME SYMBOL) (TYPE TYPE-SPEC) (DIRECTION SYMBOL)))", ((cpp_function_code)(&idlTranslateMethodParameter)), NULL);
      defineFunctionObject("IDL-TRANSLATE-METHOD-PARAMETERS", "(DEFUN (IDL-TRANSLATE-METHOD-PARAMETERS CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&idlTranslateMethodParameters)), NULL);
      defineFunctionObject("IDL-TRANSLATE-CONSTRUCTOR-NAME", "(DEFUN (IDL-TRANSLATE-CONSTRUCTOR-NAME STRING-WRAPPER) ((CONSTRUCTOR METHOD-SLOT)))", ((cpp_function_code)(&idlTranslateConstructorName)), NULL);
      defineFunctionObject("STARTUP-IDL-TRANSLATE", "(DEFUN STARTUP-IDL-TRANSLATE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupIdlTranslate)), NULL);
      { MethodSlot* function = lookupFunction(SYM_IDL_TRANSLATE_STELLA_STARTUP_IDL_TRANSLATE);

        setDynamicSlotValue(function->dynamicSlots, SYM_IDL_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupIdlTranslate"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *IDL-CHARACTER-SUBSTITUTION-TABLE* STRING (IDL-CREATE-CHARACTER-SUBSTITUTION-TABLE))", &oIDL_CHARACTER_SUBSTITUTION_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *IDL-RESERVED-WORD-TABLE* (STRING-HASH-TABLE OF STRING STRING-WRAPPER) (IDL-CREATE-RESERVED-WORD-TABLE))", &oIDL_RESERVED_WORD_TABLEo);
    }
  }
}

Surrogate* SGT_IDL_TRANSLATE_STELLA_CONS = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_GLOBAL_VARIABLE = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_TYPE = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_CLASS = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_METHOD = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_MACRO = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_PRINT_METHOD = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_STARTUP_TIME_PROGN = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_VERBATIM = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_IDL_TYPEDEF = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_IDL_IDENT = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_IDL_LITERAL = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_CLASS_IDL_NATIVE_TYPE = NULL;

Keyword* KWD_IDL_TRANSLATE_CAPITALIZED = NULL;

Keyword* KWD_IDL_TRANSLATE_UPPERCASE = NULL;

Keyword* KWD_IDL_TRANSLATE_LOWERCASE = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_ASM = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_AUTO = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_BREAK = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_CASE = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_CATCH = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_CHAR = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_CONST = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_CONTINUE = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_DEFAULT = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_DELETE = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_DO = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_DOUBLE = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_ELSE = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_ENUM = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_EXTERN = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_FLOAT = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_FOR = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_FRIEND = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_GOTO = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_IF = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_INLINE = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_INT = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_LONG = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_NEW = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_OPERATOR = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_PRIVATE = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_PROTECTED = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_PUBLIC = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_REGISTER = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_RETURN = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_SHORT = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_SIGNED = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_SIZEOF = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_STATIC = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_STRUCT = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_SWITCH = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_TEMPLATE = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_THROW = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_TRY = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_TYPEDEF = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_UNION = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_UNSIGNED = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_VIRTUAL = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_VOID = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_VOLATILE = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_WHILE = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_TYPENAME = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_IN = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_STARTUP_IDL_TRANSLATE = NULL;

Symbol* SYM_IDL_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
