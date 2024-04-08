//  -*- Mode: C++ -*-

// cpp-translate.cc

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

Module* overloadedFunctionNameModule(Symbol* functionName, Surrogate* classType) {
  { Module* symbolModule = functionName->homeModule();
    Module* classModule = classType->homeModule();

    if (symbolModule == classModule) {
      return (symbolModule);
    }
    else if (classModule->parentModules->memberP(symbolModule)) {
      return (classModule);
    }
    else if (symbolModule->parentModules->memberP(classModule)) {
      return (symbolModule);
    }
    else {
      return (classModule);
    }
  }
}

boolean cppUseGarbageCollectorP() {
  return (oCURRENT_STELLA_FEATURESo->membP(KWD_CPP_TRANSLATE_USE_CPP_GARBAGE_COLLECTOR));
}

// Wrapped TRUE string, used to reduce consing.
StringWrapper* oCPP_TRUE_STRING_WRAPPERo = NULL;

// Wrapped FALSE string, used to reduce consing.
StringWrapper* oCPP_FALSE_STRING_WRAPPERo = NULL;

// Temporary List of declarations for unused return parameters
DEFINE_STELLA_SPECIAL(oDUMMYDECLARATIONSo, Cons* , NULL);

// Current index of dummy parameter for unused return value
DEFINE_STELLA_SPECIAL(oCURRENTDUMMYINDEXo, int , NULL_INTEGER);

// Mapping from STELLA operators to C++ operators
KeyValueList* oCPP_OPERATOR_TABLEo = NULL;

Cons* cppLookupOperatorTable(Symbol* operatoR) {
  { Cons* entry = ((Cons*)(oCPP_OPERATOR_TABLEo->lookup(operatoR)));
    Cons* copiedentry = NIL;

    if (((boolean)(entry))) {
      { StringWrapper* wrapper = NULL;
        Cons* iter000 = entry;
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          wrapper = ((StringWrapper*)(iter000->value));
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(wrapString(wrapper->wrapperValue), NIL);
              if (copiedentry == NIL) {
                copiedentry = collect000;
              }
              else {
                addConsToEndOfConsList(copiedentry, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(wrapString(wrapper->wrapperValue), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      return (copiedentry);
    }
    return (NULL);
  }
}

StringWrapper* cppYieldRenamedReservedWord(Symbol* word) {
  { const char* name = word->symbolName;
    int length = strlen(name);

    return (wrapString(stringConcatenate(stringDowncase(stringSubsequence(name, 0, length - 1)), makeString(1, oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) (name[(length - 1)]))]), 0)));
  }
}

StringHashTable* cppCreateReservedWordTable() {
  { StringHashTable* table = newStringHashTable();

    { Object* word = NULL;
      Cons* iter000 = listO(52, SYM_CPP_TRANSLATE_STELLA_ASM, SYM_CPP_TRANSLATE_STELLA_ASSERT, SYM_CPP_TRANSLATE_STELLA_AUTO, SYM_CPP_TRANSLATE_STELLA_BREAK, SYM_CPP_TRANSLATE_STELLA_CASE, SYM_CPP_TRANSLATE_STELLA_CATCH, SYM_CPP_TRANSLATE_STELLA_CHAR, SYM_CPP_TRANSLATE_STELLA_CLASS, SYM_CPP_TRANSLATE_STELLA_CONST, SYM_CPP_TRANSLATE_STELLA_CONTINUE, SYM_CPP_TRANSLATE_STELLA_DEFAULT, SYM_CPP_TRANSLATE_STELLA_DELETE, SYM_CPP_TRANSLATE_STELLA_DO, SYM_CPP_TRANSLATE_STELLA_DOUBLE, SYM_CPP_TRANSLATE_STELLA_ELSE, SYM_CPP_TRANSLATE_STELLA_ENUM, SYM_CPP_TRANSLATE_STELLA_EXTERN, SYM_CPP_TRANSLATE_STELLA_FLOAT, SYM_CPP_TRANSLATE_STELLA_FOR, SYM_CPP_TRANSLATE_STELLA_FRIEND, SYM_CPP_TRANSLATE_STELLA_GOTO, SYM_CPP_TRANSLATE_STELLA_IF, SYM_CPP_TRANSLATE_STELLA_INLINE, SYM_CPP_TRANSLATE_STELLA_INT, SYM_CPP_TRANSLATE_STELLA_LONG, SYM_CPP_TRANSLATE_STELLA_NAMESPACE, SYM_CPP_TRANSLATE_STELLA_NEW, SYM_CPP_TRANSLATE_STELLA_OPERATOR, SYM_CPP_TRANSLATE_STELLA_PRIVATE, SYM_CPP_TRANSLATE_STELLA_PROTECTED, SYM_CPP_TRANSLATE_STELLA_PUBLIC, SYM_CPP_TRANSLATE_STELLA_REGISTER, SYM_CPP_TRANSLATE_STELLA_RETURN, SYM_CPP_TRANSLATE_STELLA_SHORT, SYM_CPP_TRANSLATE_STELLA_SIGNED, SYM_CPP_TRANSLATE_STELLA_SIZEOF, SYM_CPP_TRANSLATE_STELLA_STATIC, SYM_CPP_TRANSLATE_STELLA_STRUCT, SYM_CPP_TRANSLATE_STELLA_SWITCH, SYM_CPP_TRANSLATE_STELLA_TEMPLATE, SYM_CPP_TRANSLATE_STELLA_THROW, SYM_CPP_TRANSLATE_STELLA_TRY, SYM_CPP_TRANSLATE_STELLA_TYPEDEF, SYM_CPP_TRANSLATE_STELLA_TYPEID, SYM_CPP_TRANSLATE_STELLA_UNION, SYM_CPP_TRANSLATE_STELLA_UNSIGNED, SYM_CPP_TRANSLATE_STELLA_VIRTUAL, SYM_CPP_TRANSLATE_STELLA_VOID, SYM_CPP_TRANSLATE_STELLA_VOLATILE, SYM_CPP_TRANSLATE_STELLA_WHILE, SYM_CPP_TRANSLATE_STELLA_TYPENAME, NIL);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        word = iter000->value;
        table->insertAt(((Symbol*)(word))->symbolName, cppYieldRenamedReservedWord(((Symbol*)(word))));
      }
    }
    table->insertAt("++", wrapString("stella_Increment"));
    table->insertAt("--", wrapString("stella_Decrement"));
    return (table);
  }
}

StringHashTable* oCPP_RESERVED_WORD_TABLEo = NULL;

StringWrapper* cppLookupReservedWordTable(Symbol* word) {
  { StringWrapper* entry = ((StringWrapper*)(oCPP_RESERVED_WORD_TABLEo->lookup(word->symbolName)));

    if (((boolean)(entry))) {
      return (wrapString(entry->wrapperValue));
    }
    else {
      return (NULL);
    }
  }
}

// Home module of the currently translated unit.  Needed for
// proper name translation for units whose home module is different than the
// file module (occurs in some PowerLoom files - I thought we had outlawed that).
DEFINE_STELLA_SPECIAL(oCPP_CURRENT_UNIT_MODULEo, Module* , NULL);

Cons* cppTranslateUnit(TranslationUnit* unit) {
  { 
    BIND_STELLA_SPECIAL(oCPP_CURRENT_UNIT_MODULEo, Module*, oMODULEo);
    if (((boolean)(unit->theObject))) {
      oCPP_CURRENT_UNIT_MODULEo = unit->theObject->homeModule();
    }
    { Symbol* testValue000 = unit->category;

      if (testValue000 == SYM_CPP_TRANSLATE_STELLA_GLOBAL_VARIABLE) {
        return (cppTranslateDefineGlobalVariableUnit(unit));
      }
      else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_CLASS) {
        return (cppTranslateDefineNativeClassUnit(unit));
      }
      else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_TYPE) {
        return (NIL);
      }
      else if ((testValue000 == SYM_CPP_TRANSLATE_STELLA_METHOD) ||
          (testValue000 == SYM_CPP_TRANSLATE_STELLA_MACRO)) {
        return (cppTranslateDefineMethodUnit(unit));
      }
      else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_PRINT_METHOD) {
        return (cppTranslateDefprintUnit(unit));
      }
      else if ((testValue000 == SYM_CPP_TRANSLATE_STELLA_STARTUP_TIME_PROGN) ||
          (testValue000 == SYM_CPP_TRANSLATE_STELLA_VERBATIM)) {
        return (((Cons*)(cppTranslateATree(unit->theObject))));
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

Cons* cppTranslateListOfTrees(Cons* trees) {
  { Cons* cursor = trees;

    while (!(cursor == NIL)) {
      cursor->value = cppTranslateATree(cursor->value);
      cursor = cursor->rest;
    }
    return (trees);
  }
}

Object* cppTranslateATree(Object* tree) {
  if (safePrimaryType(tree) == SGT_CPP_TRANSLATE_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if (tree == NIL) {
        return (tree->cppTranslateAtomicTree());
      }
      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SPECIAL) {
          return (cppTranslateSpecialTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_VERBATIM) {
          return (cppTranslateVerbatimTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_UNWIND_PROTECT) {
          return (cppTranslateUnwindProtect(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_SIGNAL) {
          return (cppTranslateSignal(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_HANDLER_CASE) {
          return (cppTranslateHandlerCase(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_HANDLE_EXCEPTION) {
          return (cppTranslateHandleException(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_VOID_SYS) {
          return (cppTranslateVoidSys(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_BAD_SYS) {
          return (cppTranslateBadSys(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_TYPED_SYS) {
          return (cppTranslateTypedSys(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SETQ) {
          return (cppTranslateSetqTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_SET_DEFAULT) {
          return (cppTranslateSysSetDefault(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_SLOT_VALUE) {
          return (cppTranslateSysSlotValue(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_REFERENCED_SLOT_VALUE) {
          return (cppTranslateSysReferencedSlotValue(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_SLOT_VALUE_SETTER) {
          return (cppTranslateSysSlotValueSetter(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_CALL_METHOD) {
          return (cppTranslateMethodCall(tree->rest, false));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_REFERENCED_CALL_METHOD) {
          return (cppTranslateMethodCall(tree->rest, true));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_CALL_SUPER_METHOD) {
          return (cppTranslateSuperMethodCall(tree->rest));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_CALL_FUNCTION) {
          return (cppTranslateFunctionCall(tree->rest, NULL));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_PROGN) {
          return (cppTranslateProgn(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_WITH_PROCESS_LOCK) {
          return (cppTranslateWithProcessLock(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_LOOP) {
          return (cppTranslateLoop(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_FOREACH) {
          return (cppTranslateForeachTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_LET) {
          return (cppTranslateLetTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_STARTUP_TIME_PROGN) {
          return (cppTranslateStartupTimeProgn(tree));
        }
        else if ((testValue000 == SYM_CPP_TRANSLATE_STELLA_CAST) ||
            (testValue000 == SYM_CPP_TRANSLATE_STELLA_SAFE_CAST)) {
          return (cppTranslateCast(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_RETURN) {
          return (cppTranslateReturnTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_BREAK) {
          return (cppTranslateBreak(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_CONTINUE) {
          return (cppTranslateContinue(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_WHILE) {
          return (cppTranslateWhile(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_IF) {
          return (cppTranslateIfTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_CHOOSE) {
          return (cppTranslateChooseTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_WHEN) {
          return (cppTranslateWhenTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_UNLESS) {
          return (cppTranslateUnlessTree(tree));
        }
        else if ((testValue000 == SYM_CPP_TRANSLATE_STELLA_AND) ||
            ((testValue000 == SYM_CPP_TRANSLATE_STELLA_OR) ||
             ((testValue000 == SYM_CPP_TRANSLATE_STELLA_NOT) ||
              ((testValue000 == SYM_CPP_TRANSLATE_STELLA_EQp) ||
               ((testValue000 == SYM_CPP_TRANSLATE_STELLA_g) ||
                ((testValue000 == SYM_CPP_TRANSLATE_STELLA_ge) ||
                 ((testValue000 == SYM_CPP_TRANSLATE_STELLA_l) ||
                  ((testValue000 == SYM_CPP_TRANSLATE_STELLA_le) ||
                   ((testValue000 == SYM_CPP_TRANSLATE_STELLA_ii) ||
                    (testValue000 == SYM_CPP_TRANSLATE_STELLA___)))))))))) {
          return (cppTranslateOperatorTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_COND) {
          return (cppTranslateCondTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_CASE) {
          return (cppTranslateCaseTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_MAKE) {
          return (cppTranslateMakeTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_NEW) {
          return (cppTranslateSysNew(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_MV_SETQ) {
          return (cppTranslateMvSetq(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_CALL_FUNCTION_CODE) {
          return (cppTranslateCallFunctionCode(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_CALL_METHOD_CODE) {
          return (cppTranslateCallMethodCode(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_INLINE_CALL) {
          return (cppTranslateInlineCallTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_THE_CODE) {
          return (cppTranslateTheCode(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_SYS_POINTER_TO_FUNCTION) {
          return (cppTranslateSysPointerToFunction(tree));
        }
        else if ((testValue000 == SYM_CPP_TRANSLATE_STELLA_INLINE) ||
            (testValue000 == SYM_CPP_TRANSLATE_STELLA_IGNORE)) {
          return (cppTranslateInlineTree(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_PRINT_STREAM) {
          return (cppTranslatePrintStream(tree));
        }
        else if (testValue000 == SYM_CPP_TRANSLATE_STELLA_PRINT_NATIVE_STREAM) {
          return (cppTranslatePrintNativeStream(tree));
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
  else {
    if (!((boolean)(tree))) {
      return (cppTranslateNull());
    }
    return (tree->cppTranslateAtomicTree());
  }
}

Cons* cppTranslateVerbatimTree(Cons* tree) {
  { Cons* cursor = tree->rest;
    Object* verbatimcode = NULL;

    while (!(cursor == NIL)) {
      if (cursor->value == KWD_CPP_TRANSLATE_CPP) {
        verbatimcode = cursor->rest->value;
        return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_VERBATIM, verbatimcode, NIL));
      }
      cursor = cursor->rest->rest;
    }
    throw *newStellaException("Verbatim has no :cpp option");
  }
}

Cons* cppTranslateSpecialTree(Cons* tree) {
  if (!(specialImplementationStyle() == KWD_CPP_TRANSLATE_UNBIND_WITH_DESTRUCTORS)) {
    std::cerr << "Safety violation: " << "INTERNAL ERROR: Unexpected special implementation style";
  }
  { Cons* odeclarations = NIL;
    GlobalVariable* variable = NULL;
    Symbol* variablename = NULL;
    StandardObject* type = NULL;
    Object* initialvaluetree = NULL;

    { Cons* declaration = NULL;
      Cons* iter000 = ((Cons*)(tree->rest->value));
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        declaration = ((Cons*)(iter000->value));
        variablename = ((Symbol*)(declaration->value));
        type = ((StandardObject*)(declaration->rest->value));
        initialvaluetree = declaration->rest->rest->value;
        variable = variablename->lookupGlobalVariable();
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, wrapString("BIND_STELLA_SPECIAL"), NIL), listO(5, SYM_CPP_TRANSLATE_STELLA_CPP_ACTUALS, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateGlobalVariableName(variable), NIL), listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateAndPointerizeTypeSpec(type), NIL), cppTranslateATree(initialvaluetree), NIL), NIL), NIL);
            if (odeclarations == NIL) {
              odeclarations = collect000;
            }
            else {
              addConsToEndOfConsList(odeclarations, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, wrapString("BIND_STELLA_SPECIAL"), NIL), listO(5, SYM_CPP_TRANSLATE_STELLA_CPP_ACTUALS, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateGlobalVariableName(variable), NIL), listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateAndPointerizeTypeSpec(type), NIL), cppTranslateATree(initialvaluetree), NIL), NIL), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_BLOCK, NIL, cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, odeclarations->concatenate(cppTranslateListOfTrees(tree->rest->rest)->concatenate(NIL, 0), 0)), NIL));
  }
}

Cons* cppTranslateInlineTree(Cons* tree) {
  tree = tree;
  return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_COMMENT, wrapString("inline method"), NIL));
}

Cons* tokenizeVerbatimMethodBody(Cons* tree) {
  { StandardObject* dummy1;

    { MethodSlot* method = ((MethodSlot*)(slotFromExpressionTree(tree)));
      const char* body = ((VerbatimStringWrapper*)(lookupVerbatimTree(((Cons*)(walkVerbatimTree(((Cons*)(inlinableMethodBody(method))), dummy1))), NULL)))->wrapperValue;
      int bodystart = 0;
      int bodylength = strlen(body);
      List* parameters = newList();
      int parameterposition = 0;
      const char* identifierchars = "_ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789$";
      Cons* result = NIL;
      char ch = NULL_CHARACTER;
      int cursor = 0;
      int end = 0;

      { Symbol* par = NULL;
        Cons* iter000 = method->methodParameterNames_reader()->theConsList;
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          par = ((Symbol*)(iter000->value));
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(((oTRANSLATOROUTPUTLANGUAGEo == KWD_CPP_TRANSLATE_CPP) ? cppTranslateName(par) : javaTranslateName(par)), NIL);
              if (parameters->theConsList == NIL) {
                parameters->theConsList = collect000;
              }
              else {
                addConsToEndOfConsList(parameters->theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(((oTRANSLATOROUTPUTLANGUAGEo == KWD_CPP_TRANSLATE_CPP) ? cppTranslateName(par) : javaTranslateName(par)), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      for (;;) {
        if (cursor >= bodylength) {
          break;
        }
        ch = body[cursor];
        if (ch == '/') {
          cursor = cursor + 1;
          if (cursor < bodylength) {
            switch (body[cursor]) {
              case '/': 
                { InputStringStream* comment = newInputStringStream(stringSubsequence(body, cursor, NULL_INTEGER));

                  cursor = cursor + strlen((readLine(comment)));
                }
                break;
              case '*': 
                cursor = stringSearch(body, "*/", cursor);
                if (cursor == NULL_INTEGER) {
                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    signalTranslationError();
                    if (!(suppressWarningsP())) {
                      printErrorContext(">> ERROR: ", STANDARD_ERROR);
                      *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal " << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " verbatim code in " << "`" << deUglifyParseTree(method) << "'" << "." << std::endl;
                    }
                  }
                  return (NULL);
                }
                else {
                  cursor = cursor + 2;
                }
                break;
              default:
                break;
            }
          }
        }
        else if (stringMemberP(identifierchars, ch) &&
            (!(oCHARACTER_TYPE_TABLEo[(int)(unsigned char) ch] == KWD_CPP_TRANSLATE_DIGIT))) {
          end = cursor + 1;
          { int i = NULL_INTEGER;
            int iter001 = end;
            int upperBound000 = bodylength - 1;

            for  (; iter001 <= upperBound000; 
                  iter001 = iter001 + 1) {
              i = iter001;
              if (stringMemberP(identifierchars, body[i])) {
                end = end + 1;
              }
              else {
                break;
              }
            }
          }
          parameterposition = parameters->position(wrapString(stringSubsequence(body, cursor, end)), NULL_INTEGER);
          if (parameterposition != NULL_INTEGER) {
            result = cons(wrapString(stringSubsequence(body, bodystart, cursor)), result);
            result = cons(cons(parameters->nth(parameterposition), cons(wrapInteger(parameterposition), NIL)), result);
            bodystart = end;
          }
          cursor = end;
        }
        else {
          cursor = cursor + 1;
        }
      }
      if (bodystart < bodylength) {
        result = cons(wrapString(stringSubsequence(body, bodystart, bodylength)), result);
      }
      return (result->reverse());
    }
  }
}

Object* cppTranslateInlineCallTree(Cons* tree) {
  { Cons* calltree = ((Cons*)(tree->rest->value));
    Cons* arguments = ((calltree->value == SYM_CPP_TRANSLATE_STELLA_SYS_CALL_FUNCTION) ? calltree->nthRest(2) : calltree->nthRest(3));
    Cons* tokenizedbody = tokenizeVerbatimMethodBody(calltree);

    if (((boolean)(tokenizedbody))) {
      { List* inlinedparameters = newList();
        const char* inlinedbody = NULL;
        boolean successP = true;

        { 
          BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, newOutputStringStream());
          { Object* token = NULL;
            Cons* iter000 = tokenizedbody;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              token = iter000->value;
              { Surrogate* testValue000 = safePrimaryType(token);

                if (subtypeOfStringP(testValue000)) {
                  { Object* token000 = token;
                    StringWrapper* token = ((StringWrapper*)(token000));

                    *(oCURRENT_STREAMo->nativeStream) << token->wrapperValue;
                  }
                }
                else if (testValue000 == SGT_CPP_TRANSLATE_STELLA_CONS) {
                  { Object* token001 = token;
                    Cons* token = ((Cons*)(token001));

                    { StringWrapper* parameter = ((StringWrapper*)(token->value));
                      IntegerWrapper* position = ((IntegerWrapper*)(token->rest->value));
                      Object* argument = arguments->nth(position->wrapperValue);

                      if (!sideEffectFreeExpressionP(argument)) {
                        if (inlinedparameters->memberP(parameter)) {
                          {
                            successP = false;
                            break;
                          }
                        }
                        else {
                          inlinedparameters->insert(parameter);
                        }
                      }
                      if (!(atomicExpressionP(argument))) {
                        *(oCURRENT_STREAMo->nativeStream) << "(";
                      }
                      cppOutputStatement(cppTranslateATree(copyConsTree(argument)));
                      if (!(atomicExpressionP(argument))) {
                        *(oCURRENT_STREAMo->nativeStream) << ")";
                      }
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
          }
          inlinedbody = ((OutputStringStream*)(oCURRENT_STREAMo))->theStringReader();
          if (successP) {
            return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_VERBATIM, newVerbatimStringWrapper(inlinedbody), NIL));
          }
        }
      }
    }
    return (cppTranslateATree(calltree));
  }
}

Cons* cppTranslatePrintNativeStream(Cons* tree) {
  { Cons* otree = cppTranslatePrintStream(tree);

    otree->firstSetter(SYM_CPP_TRANSLATE_STELLA_CPP_PRINT_NATIVE_STREAM);
    return (otree);
  }
}

Cons* cppTranslateDefprintUnit(TranslationUnit* unit) {
  { Object* printform = unit->codeRegister;
    Class* clasS = ((Class*)(unit->theObject));
    StringWrapper* classname = NULL;

    classname = cppTranslateAndPointerizeTypeSpec(clasS->classType);
    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_DEFPRINT, classname, cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, cppTranslateATree(printform), cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_RETURN, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateName(SYM_CPP_TRANSLATE_STELLA_STREAM), NIL), NIL), NIL)), NIL)));
  }
}

Cons* cppTranslateSignal(Cons* tree) {
  tree->firstSetter(SYM_CPP_TRANSLATE_STELLA_CPP_SIGNAL);
  tree->secondSetter(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_DEREFERENCE, cppTranslateATree(tree->rest->value), NIL));
  tree->rest->rest = NIL;
  return (tree);
}

Cons* cppTranslateHandlerCase(Cons* tree) {
  tree->firstSetter(SYM_CPP_TRANSLATE_STELLA_CPP_HANDLER_CASE);
  tree->rest = cppTranslateListOfTrees(tree->rest);
  return (tree);
}

Cons* cppTranslateHandleException(Cons* tree) {
  { Cons* variabledecl = ((Cons*)(tree->rest->value));
    Object* variable = variabledecl->value;
    Object* exceptiontype = variabledecl->rest->value;
    StringWrapper* helpervariable = NULL;
    StringWrapper* helpervariabletype = NULL;

    tree->firstSetter(SYM_CPP_TRANSLATE_STELLA_CPP_CATCH);
    if (((boolean)(variable))) {
      helpervariable = wrapString(stringConcatenate("_", cppTranslateName(((Symbol*)(variable)))->wrapperValue, 0));
      helpervariabletype = wrapString(stringConcatenate(cppTranslateTypeSpec(((StandardObject*)(exceptiontype)))->wrapperValue, "&"));
    }
    tree->secondSetter(cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_TYPE, (((boolean)(variable)) ? helpervariabletype : cppTranslateTypeSpec(((StandardObject*)(exceptiontype)))), NIL), ((((boolean)(variable)) ? cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, helpervariable, NIL), NIL) : NIL))->concatenate(NIL, 0)));
    tree->rest->rest = cppTranslateListOfTrees(tree->rest->rest);
    if (((boolean)(variable))) {
      tree->rest->rest = cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_LOCAL, NULL, cons(cppTranslateAndPointerizeTypeSpec(((StandardObject*)(exceptiontype))), listO(3, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateName(((Symbol*)(variable))), NIL), listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, wrapString(stringConcatenate("&", helpervariable->wrapperValue)), NIL), NIL))), tree->rest->rest->concatenate(NIL, 0));
    }
    return (tree);
  }
}

Cons* cppTranslateUnwindProtect(Cons* tree) {
  tree->firstSetter(SYM_CPP_TRANSLATE_STELLA_CPP_UNWIND_PROTECT);
  tree->rest = cppTranslateListOfTrees(tree->rest);
  return (tree);
}

Cons* cppTranslateCast(Cons* tree) {
  { Object* expression = tree->rest->value;
    Surrogate* type = typeSpecToBaseType(((StandardObject*)(tree->rest->rest->value)));

    if (subtypeOfP(type, SGT_CPP_TRANSLATE_STELLA_NUMBER) &&
        isaP(expression, SGT_CPP_TRANSLATE_STELLA_NUMBER_WRAPPER)) {
      return (((Cons*)(cppTranslateATree(coerceNumericConstant(((NumberWrapper*)(expression)), type)))));
    }
    tree->firstSetter(SYM_CPP_TRANSLATE_STELLA_CPP_CAST);
    tree->secondSetter(cppTranslateATree(tree->rest->value));
    tree->thirdSetter(cppTranslateAndPointerizeTypeSpec(((StandardObject*)(tree->rest->rest->value))));
    return (tree);
  }
}

Cons* cppTranslateMvSetq(Cons* tree) {
  { Cons* variables = ((Cons*)(tree->rest->value));
    Object* functioncall = tree->rest->rest->value;
    Cons* otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_ASSIGN, cppTranslateATree(variables->value), cons(cppTranslateMvFunctionCall(((Cons*)(functioncall)), variables->rest), NIL));

    return (otree);
  }
}

Cons* cppTranslateMvFunctionCall(Cons* functioncall, Cons* variables) {
  return (((Cons*)(cppTranslateATree(functioncall->concatenate(variables->concatenate(NIL, 0), 0)))));
}

Cons* cppTranslateDefineGlobalVariableUnit(TranslationUnit* unit) {
  { GlobalVariable* global = ((GlobalVariable*)(unit->theObject));
    StandardObject* type = globalVariableTypeSpec(global);
    Object* initialvaluetree = ((unit->codeRegister == KWD_CPP_TRANSLATE_UNBOUND_SPECIAL_VARIABLE) ? ((Object*)(NULL)) : cppTranslateATree(unit->codeRegister));
    StringWrapper* variablename = cppTranslateGlobalVariableName(global);

    if (global->variableSpecialP) {
      if ((!((boolean)(initialvaluetree))) &&
          (specialImplementationStyle() == KWD_CPP_TRANSLATE_UNBIND_WITH_DESTRUCTORS)) {
        initialvaluetree = cppTranslateATree(typeToWalkedNullValueTree(type, typeSpecToBaseType(type)));
      }
      return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_SPECIAL, wrapString(global->documentation), listO(3, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_TYPE, cppTranslateAndPointerizeTypeSpec(type), NIL), variablename, ((((boolean)(initialvaluetree)) ? cons(initialvaluetree, NIL) : NIL))->concatenate(NIL, 0))));
    }
    else {
      return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_GLOBAL, wrapString(global->documentation), listO(3, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_TYPE, cppTranslateAndPointerizeTypeSpec(type), NIL), variablename, cons(initialvaluetree, NIL))));
    }
  }
}

StringWrapper* cppTranslateGlobalVariableName(GlobalVariable* global) {
  return (cppTranslateGlobalName(cppFixupNameSymbol(global->variableName, global->homeModule())));
}

StringWrapper* cppTranslateGlobalVariableAddress(GlobalVariable* global) {
  return (wrapString(stringConcatenate("&", cppTranslateGlobalVariableName(global)->wrapperValue, 0)));
}

boolean symbolCaseP(Object* keyform) {
  if (safePrimaryType(keyform) == SGT_CPP_TRANSLATE_STELLA_CONS) {
    { Object* keyform000 = keyform;
      Cons* keyform = ((Cons*)(keyform000));

      return ((keyform->value == SYM_CPP_TRANSLATE_STELLA_SYS_SLOT_VALUE) &&
          (keyform->rest->rest->value == SYM_CPP_TRANSLATE_STELLA_SYMBOL_ID));
    }
  }
  else {
    return (false);
  }
}

Cons* cppYieldSymbolIdForm(int symbolid) {
  { Symbol* symbol = getSymFromOffset(symbolid);

    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateSymbolId(symbol), NIL));
  }
}

Cons* cppTranslateCondition(Cons* condition, boolean symbolcasep) {
  { Cons* translatedactions = cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, cppTranslateListOfTrees(condition->rest)->concatenate(NIL, 0));
    Object* keys = condition->value;
    Object* translatedkeys = NULL;
    Cons* translatedkeyslist = NIL;

    if (symbolcasep) {
      if (consP(keys)) {
        {
          { Object* key = NULL;
            Cons* iter000 = ((Cons*)(keys));
            Cons* collect000 = NULL;

            for  (; !(iter000 == NIL); 
                  iter000 = iter000->rest) {
              key = iter000->value;
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(cppYieldSymbolIdForm(((IntegerWrapper*)(key))->wrapperValue), NIL);
                  if (translatedkeyslist == NIL) {
                    translatedkeyslist = collect000;
                  }
                  else {
                    addConsToEndOfConsList(translatedkeyslist, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(cppYieldSymbolIdForm(((IntegerWrapper*)(key))->wrapperValue), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
          translatedkeys = translatedkeyslist;
        }
      }
      else {
        translatedkeys = cppYieldSymbolIdForm(((IntegerWrapper*)(keys))->wrapperValue);
      }
    }
    else {
      translatedkeys = (consP(keys) ? cppTranslateListOfTrees(((Cons*)(keys))) : cppTranslateATree(keys));
    }
    return (cons(translatedkeys, cons(translatedactions, NIL)));
  }
}

Cons* cppTranslateCaseTree(Cons* tree) {
  { Cons* otherwisecondition = NULL;
    Cons* conditions = NIL;
    Object* keyform = NULL;
    boolean symbolcasep = false;

    symbolcasep = symbolCaseP(tree->rest->value);
    keyform = cppTranslateATree(tree->rest->value);
    { 
      BIND_STELLA_SPECIAL(oCPPLOOPEXITACTIVEpo, boolean, true);
      { Object* condition = NULL;
        Cons* iter000 = tree->rest->rest;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          condition = iter000->value;
          if (safePrimaryType(condition) == SGT_CPP_TRANSLATE_STELLA_CONS) {
            { Object* condition000 = condition;
              Cons* condition = ((Cons*)(condition000));

              if (condition->value == SYM_CPP_TRANSLATE_STELLA_OTHERWISE) {
                otherwisecondition = cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, cppTranslateListOfTrees(condition->rest)->concatenate(NIL, 0));
              }
              else {
                conditions = cons(cppTranslateCondition(condition, symbolcasep), conditions);
              }
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << safePrimaryType(condition) << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
      }
      return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_CASE, keyform, cons(otherwisecondition, cons(conditions->reverse(), NIL))));
    }
  }
}

Cons* cppTranslateCondTree(Cons* tree) {
  { Cons* otherwisecondition = NULL;
    Cons* conditions = NIL;

    { Object* condition = NULL;
      Cons* iter000 = tree->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        condition = iter000->value;
        if (safePrimaryType(condition) == SGT_CPP_TRANSLATE_STELLA_CONS) {
          { Object* condition000 = condition;
            Cons* condition = ((Cons*)(condition000));

            if (condition->value == SYM_CPP_TRANSLATE_STELLA_OTHERWISE) {
              otherwisecondition = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_PROGN, cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, cppTranslateListOfTrees(condition->rest)->concatenate(NIL, 0)), NIL);
            }
            else {
              conditions = cons(cons(cppTranslateATree(condition->value), cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_PROGN, cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, cppTranslateListOfTrees(condition->rest)->concatenate(NIL, 0)), NIL), NIL)), conditions);
            }
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << safePrimaryType(condition) << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_COND, otherwisecondition, cons(conditions->reverse(), NIL)));
  }
}

DEFINE_STELLA_SPECIAL(oCPPLOOPEXITo, Symbol* , NULL);

DEFINE_STELLA_SPECIAL(oCPPLOOPEXITACTIVEpo, boolean , false);

Cons* cppTranslateLoop(Cons* tree) {
  { 
    BIND_STELLA_SPECIAL(oCPPLOOPEXITo, Symbol*, NULL);
    { Cons* otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_LOOP, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_PROGN, cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, cppTranslateListOfTrees(tree->rest)->concatenate(NIL, 0)), NIL), NIL);

      if (((boolean)(oCPPLOOPEXITo))) {
        otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, otree, cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_GOTO_LABEL, cppTranslateATree(oCPPLOOPEXITo), NIL), NIL));
      }
      return (otree);
    }
  }
}

Cons* cppTranslateWhile(Cons* tree) {
  { 
    BIND_STELLA_SPECIAL(oCPPLOOPEXITo, Symbol*, NULL);
    { Object* test = cppTranslateATree(tree->rest->value);
      Cons* otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_WHILE, test, cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_PROGN, cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, cppTranslateListOfTrees(tree->rest->rest)->concatenate(NIL, 0)), NIL), NIL));

      if (((boolean)(oCPPLOOPEXITo))) {
        otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, otree, cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_GOTO_LABEL, cppTranslateATree(oCPPLOOPEXITo), NIL), NIL));
      }
      return (otree);
    }
  }
}

Cons* cppTranslateProgn(Cons* tree) {
  return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_PROGN, cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, cppTranslateListOfTrees(tree->rest)->concatenate(NIL, 0)), NIL));
}

Cons* cppTranslateWithProcessLock(Cons* tree) {
  return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_WITH_PROCESS_LOCK, cppTranslateATree(tree->rest->value), cons(cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, cppTranslateListOfTrees(tree->rest->rest)->concatenate(NIL, 0)), NIL)));
}

Cons* cppTranslateBreak(Cons* tree) {
  if ((!(oCPPLOOPEXITo == SYM_CPP_TRANSLATE_STELLA_CPP_BREAK)) &&
      oCPPLOOPEXITACTIVEpo) {
    if (!((boolean)(oCPPLOOPEXITo))) {
      oCPPLOOPEXITo = localGensym("LOOP-EXIT");
    }
    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_GOTO, cppTranslateATree(oCPPLOOPEXITo), NIL));
  }
  else {
    tree->firstSetter(SYM_CPP_TRANSLATE_STELLA_CPP_BREAK);
    return (tree);
  }
}

Cons* cppTranslateContinue(Cons* tree) {
  tree->firstSetter(SYM_CPP_TRANSLATE_STELLA_CPP_CONTINUE);
  return (tree);
}

Cons* cppTranslateIfTree(Cons* tree) {
  { Object* test = cppTranslateATree(tree->rest->value);
    Cons* truebody = ((Cons*)(cppTranslateATree(tree->rest->rest->value)));
    Cons* falsebody = ((Cons*)(cppTranslateATree(tree->fourth())));

    if (consP(truebody->value) &&
        (!(truebody->rest == NIL))) {
      truebody = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_PROGN, cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, truebody->concatenate(NIL, 0)), NIL);
    }
    else {
      truebody = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_PROGN, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, truebody, NIL), NIL);
    }
    if (consP(falsebody->value) &&
        (!(falsebody->rest == NIL))) {
      falsebody = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_PROGN, cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, falsebody->concatenate(NIL, 0)), NIL);
    }
    else {
      falsebody = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_PROGN, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, falsebody, NIL), NIL);
    }
    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IF, test, cons(truebody, cons(falsebody, NIL))));
  }
}

Cons* cppTranslateChooseTree(Cons* tree) {
  return (cppTranslateOperatorCall(cons(wrapString("?"), cons(wrapString(":"), NIL)), tree->rest, 3));
}

Cons* cppTranslateWhenTree(Cons* tree) {
  { Object* test = cppTranslateATree(tree->rest->value);
    Cons* body = cppTranslateListOfTrees(tree->rest->rest);

    tree->rest->rest = NIL;
    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_WHEN, test, cons(cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, body->concatenate(NIL, 0)), NIL)));
  }
}

Cons* cppTranslateUnlessTree(Cons* tree) {
  { Object* test = cppTranslateATree(tree->rest->value);
    Cons* body = cppTranslateListOfTrees(tree->rest->rest);

    tree->rest->rest = NIL;
    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_UNLESS, test, cons(cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, body->concatenate(NIL, 0)), NIL)));
  }
}

Cons* cppTranslateForeachTree(Cons* tree) {
  { 
    BIND_STELLA_SPECIAL(oCPPLOOPEXITo, Symbol*, NULL);
    { Cons* iteratorbindings = ((Cons*)(tree->rest->value));
      Cons* valuetrees = ((Cons*)(tree->rest->rest->value));
      Cons* nexttrees = ((Cons*)(tree->fourth()));
      Object* continuationtest = cppTranslateATree(tree->fifth());
      Cons* body = cppTranslateListOfTrees(tree->nthRest(5));
      Cons* declaration = NIL;
      Cons* declarations = NIL;
      Cons* vadeclarations = NIL;
      Cons* valueassignments = NIL;
      Cons* nextassignments = NIL;
      Symbol* varargsiterator = NULL;
      Cons* variables = NIL;
      Cons* otree = NIL;

      { Cons* binding = NULL;
        Cons* iter000 = iteratorbindings;
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          binding = ((Cons*)(iter000->value));
          if (subTypeSpecOfP(((StandardObject*)(binding->rest->value)), SGT_CPP_TRANSLATE_STELLA_ARGUMENT_LIST_ITERATOR)) {
            varargsiterator = ((Symbol*)(binding->value));
            vadeclarations = vadeclarations->concatenate(cppYieldVaIteratorDeclarations(varargsiterator), 0);
            continue;
          }
          else {
            declaration = cons(cppTranslateAndPointerizeTypeSpec(((StandardObject*)(binding->rest->value))), cons(cppTranslateATree(binding->value), cons(cppTranslateATree(binding->rest->rest->value), NIL)));
          }
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(declaration, NIL);
              if (declarations == NIL) {
                declarations = collect000;
              }
              else {
                addConsToEndOfConsList(declarations, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(declaration, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      { Cons* tree = NULL;
        Cons* iter001 = valuetrees;
        Cons* collect001 = NULL;

        for  (; !(iter001 == NIL); 
              iter001 = iter001->rest) {
          tree = ((Cons*)(iter001->value));
          if (!((boolean)(collect001))) {
            {
              collect001 = cons(cppTranslateATree(tree), NIL);
              if (valueassignments == NIL) {
                valueassignments = collect001;
              }
              else {
                addConsToEndOfConsList(valueassignments, collect001);
              }
            }
          }
          else {
            {
              collect001->rest = cons(cppTranslateATree(tree), NIL);
              collect001 = collect001->rest;
            }
          }
        }
      }
      { Cons* tree = NULL;
        Cons* iter002 = nexttrees;
        Cons* collect002 = NULL;

        for  (; !(iter002 == NIL); 
              iter002 = iter002->rest) {
          tree = ((Cons*)(iter002->value));
          if (!((boolean)(collect002))) {
            {
              collect002 = cons(cppTranslateATree(tree), NIL);
              if (nextassignments == NIL) {
                nextassignments = collect002;
              }
              else {
                addConsToEndOfConsList(nextassignments, collect002);
              }
            }
          }
          else {
            {
              collect002->rest = cons(cppTranslateATree(tree), NIL);
              collect002 = collect002->rest;
            }
          }
        }
      }
      { Cons* decl = NULL;
        Cons* iter003 = vadeclarations;
        Cons* collect003 = NULL;

        for  (; !(iter003 == NIL); 
              iter003 = iter003->rest) {
          decl = ((Cons*)(iter003->value));
          if (!((boolean)(collect003))) {
            {
              collect003 = cons(decl->rest->value, NIL);
              if (variables == NIL) {
                variables = collect003;
              }
              else {
                addConsToEndOfConsList(variables, collect003);
              }
            }
          }
          else {
            {
              collect003->rest = cons(decl->rest->value, NIL);
              collect003 = collect003->rest;
            }
          }
        }
      }
      { Cons* decl = NULL;
        Cons* iter004 = declarations;
        Cons* collect004 = NULL;

        for  (; !(iter004 == NIL); 
              iter004 = iter004->rest) {
          decl = ((Cons*)(iter004->value));
          if (!((boolean)(collect004))) {
            {
              collect004 = cons(decl->rest->value, NIL);
              if (variables == NIL) {
                variables = collect004;
              }
              else {
                addConsToEndOfConsList(variables, collect004);
              }
            }
          }
          else {
            {
              collect004->rest = cons(decl->rest->value, NIL);
              collect004 = collect004->rest;
            }
          }
        }
      }
      if (!(vadeclarations == NIL)) {
        otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_BLOCK, vadeclarations->concatenate(declarations, 0), cons(cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, cppYieldVaStartTree(varargsiterator)->concatenate(cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_FOREACH, variables, cons(continuationtest, cons(valueassignments, cons(nextassignments, cons(body, NIL))))), cppYieldVaEndTree(varargsiterator)->concatenate(NIL, 0)), 0)), NIL));
      }
      else {
        otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_BLOCK, declarations, cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_FOREACH, variables, cons(continuationtest, cons(valueassignments, cons(nextassignments, cons(body, NIL))))), NIL));
      }
      if (((boolean)(oCPPLOOPEXITo))) {
        otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, otree, cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_GOTO_LABEL, cppTranslateATree(oCPPLOOPEXITo), NIL), NIL));
      }
      return (otree);
    }
  }
}

Cons* cppYieldVaStartTree(Symbol* iteratorvar) {
  return (cons(listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateName(SYM_CPP_TRANSLATE_STELLA_VA_START), NIL), listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_ACTUALS, cppTranslateATree(iteratorvar), cons(cppTranslateATree(variableArgumentsName(oMETHODBEINGWALKEDo)), NIL)), NIL), NIL));
}

Cons* cppYieldVaEndTree(Symbol* iteratorvar) {
  return (cons(listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateName(SYM_CPP_TRANSLATE_STELLA_VA_END), NIL), listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_ACTUALS, cppTranslateATree(iteratorvar), NIL), NIL), NIL));
}

Symbol* cppYieldVaIteratorHelperVariable(Symbol* iteratorvar) {
  return (internSymbol(stringConcatenate(iteratorvar->symbolName, "-COUNT", 0)));
}

Cons* cppYieldVaIteratorDeclarations(Symbol* iteratorvar) {
  return (listO(3, cons(cppTranslateAndPointerizeTypeSpec(SGT_CPP_TRANSLATE_STELLA_ARGUMENT_LIST_ITERATOR), cons(cppTranslateATree(iteratorvar), NIL)), cons(cppTranslateAndPointerizeTypeSpec(SGT_CPP_TRANSLATE_STELLA_INTEGER), cons(cppTranslateATree(cppYieldVaIteratorHelperVariable(iteratorvar)), cons(cppTranslateATree(variableArgumentsName(oMETHODBEINGWALKEDo)), NIL))), NIL));
}

Cons* cppTranslateArgumentListTree(Symbol* operatoR, Surrogate* owner, Object* argument) {
  owner = owner;
  if (operatoR == SYM_CPP_TRANSLATE_STELLA_ALLOCATE_ITERATOR) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Cannot handle explicit calls to " << "`ARGUMENT-LIST.ALLOCATE-ITERATOR' in C++" << "." << std::endl;
      }
    }
    return (((Cons*)(cppTranslateATree(argument))));
  }
  else if (operatoR == SYM_CPP_TRANSLATE_STELLA_LENGTH) {
    return (((Cons*)(cppTranslateATree(variableArgumentsName(oMETHODBEINGWALKEDo)))));
  }
  else if (operatoR == SYM_CPP_TRANSLATE_STELLA_NEXTp) {
    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_BINARY_OP, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_UNARY_OP, cppTranslateATree(cppYieldVaIteratorHelperVariable(((Symbol*)(argument)))), cppLookupOperatorTable(SYM_CPP_TRANSLATE_STELLA___)->concatenate(NIL, 0)), cppLookupOperatorTable(SYM_CPP_TRANSLATE_STELLA_g)->concatenate(cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_LITERAL, wrapInteger(0), NIL), NIL), 0)));
  }
  else if (operatoR == SYM_CPP_TRANSLATE_STELLA_ARGUMENT) {
    return (listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateName(SYM_CPP_TRANSLATE_STELLA_VA_ARG), NIL), listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_ACTUALS, cppTranslateATree(argument), cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateAndPointerizeTypeSpec(variableArgumentsType(oMETHODBEINGWALKEDo)), NIL), NIL)), NIL));
  }
  else {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Cannot translate call to " << "`" << deUglifyParseTree(operatoR) << "'" << " on an `ARGUMENT-LIST'" << "." << std::endl;
      }
    }
    return (listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateName(operatoR), NIL), listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_ACTUALS, cppTranslateATree(argument), NIL), NIL));
  }
}

Cons* cppTranslateTheCode(Cons* tree) {
  { Cons* otree = NULL;

    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->rest->value));

      if (testValue000 == KWD_CPP_TRANSLATE_FUNCTION) {
        { Object* methodspec = tree->rest->rest->value;
          boolean overloadedP = (symbolP(methodspec) &&
              cppPossiblyOverloadedFunctionNameP(((Symbol*)(methodspec)))) ||
              (methodSlotP(methodspec) &&
               cppMethodObjectIsOverloadedFunctionP(((MethodSlot*)(methodspec))));

          otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_POINTER, (methodSlotP(methodspec) ? cppTranslateFunctionName(((MethodSlot*)(methodspec)), true) : cppTranslateFunctionNameFromName(((Symbol*)(methodspec)))), NIL);
          if (overloadedP) {
            if (symbolP(methodspec)) {
              methodspec = lookupFunction(((Symbol*)(methodspec)));
            }
            otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_CAST, otree, cons(cppTranslateFunctionSignature(((MethodSlot*)(methodspec))), NIL));
          }
          otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_CAST, otree, cons(wrapString("cpp_function_code"), NIL));
        }
      }
      else if (testValue000 == KWD_CPP_TRANSLATE_METHOD) {
        { Object* methodspec = tree->fourth();
          Object* ownerspec = tree->rest->rest->value;

          otree = listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_CAST, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_POINTER, (methodSlotP(methodspec) ? cppTranslateMethodName(((MethodSlot*)(methodspec)), true) : cppTranslateMethodNameFromName(((Symbol*)(methodspec)), ((StandardObject*)(ownerspec)))), NIL), wrapString("cpp_method_code"), NIL);
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    return (otree);
  }
}

Cons* cppTranslateSysPointerToFunction(Cons* tree) {
  { const char* functionname = cppTranslateName(((Symbol*)(tree->rest->value)))->wrapperValue;
    Cons* otree = NULL;

    if (tree->rest->rest->value == SYM_CPP_TRANSLATE_STELLA_TRUE) {
      functionname = stringConcatenate(functionname, "_setter", 0);
    }
    otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_POINTER, wrapString(functionname), NIL);
    return (otree);
  }
}

Cons* cppTranslateSysNew(Cons* tree) {
  { StandardObject* typespec = ((StandardObject*)(tree->rest->value));
    Class* clasS = typeSpecToClass(typespec);

    if (arrayTypeSpecifierP(typespec)) {
      return (cppTranslateNewArray(tree));
    }
    else {
      return (listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, wrapString(cppYieldQualifiedName(cppTranslateName(yieldConstructorName(clasS))->wrapperValue, classSymbol(clasS))), NIL), cppTranslateActualParameters(tree->rest->rest), NIL));
    }
  }
}

boolean cppNonPointerTypeP(StandardObject* typespec) {
  { Surrogate* basetype = typeSpecToBaseType(typespec);

    if ((basetype == SGT_CPP_TRANSLATE_STELLA_INTEGER) ||
        ((basetype == SGT_CPP_TRANSLATE_STELLA_SHORT_INTEGER) ||
         ((basetype == SGT_CPP_TRANSLATE_STELLA_LONG_INTEGER) ||
          ((basetype == SGT_CPP_TRANSLATE_STELLA_UNSIGNED_LONG_INTEGER) ||
           ((basetype == SGT_CPP_TRANSLATE_STELLA_FLOAT) ||
            ((basetype == SGT_CPP_TRANSLATE_STELLA_SINGLE_FLOAT) ||
             ((basetype == SGT_CPP_TRANSLATE_STELLA_DOUBLE_FLOAT) ||
              ((basetype == SGT_CPP_TRANSLATE_STELLA_CHARACTER) ||
               ((basetype == SGT_CPP_TRANSLATE_STELLA_BYTE) ||
                (basetype == SGT_CPP_TRANSLATE_STELLA_OCTET)))))))))) {
      return (true);
    }
    else {
      return (false);
    }
  }
}

boolean cppTypeWithoutInteriorPointersP(StandardObject* typespec) {
  { boolean dummy1;

    { Surrogate* basetype = typeSpecToBaseType(typespec);
      Class* clasS = ((Class*)(basetype->surrogateValue));

      if (arrayTypeSpecifierP(typespec)) {
        return (cppNonPointerTypeP(extractParameterType(typespec, SYM_CPP_TRANSLATE_STELLA_ANY_VALUE, dummy1)));
      }
      if (createNativeClassP(clasS) &&
          (!subtypeOfP(basetype, SGT_CPP_TRANSLATE_STELLA_NATIVE_EXCEPTION))) {
        { boolean alwaysP000 = true;

          { Slot* slot = NULL;
            Iterator* iter000 = clasS->classSlots();

            for (; iter000->nextP(); ) {
              slot = ((Slot*)(iter000->value));
              if (storageSlotP(slot) &&
                  (nativeSlotP(((StorageSlot*)(slot))) &&
                   (!slotHasUnknownTypeP(((StorageSlot*)(slot)), clasS)))) {
                if (!cppNonPointerTypeP(slot->slotBaseType)) {
                  alwaysP000 = false;
                  break;
                }
              }
            }
          }
          { boolean value000 = alwaysP000;

            return (value000);
          }
        }
      }
      return (false);
    }
  }
}

Cons* cppTranslateNewArray(Cons* tree) {
  { boolean dummy1;

    { ParametricTypeSpecifier* arraytype = ((ParametricTypeSpecifier*)(tree->rest->value));
      Object* initialelement = tree->rest->rest->value;
      Cons* dimensions = cppTranslateListOfTrees(tree->rest->rest->rest);
      StandardObject* elementtype = extractParameterType(arraytype, SYM_CPP_TRANSLATE_STELLA_ANY_VALUE, dummy1);

      initialelement = initialelement;
      return (listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, (cppUseGarbageCollectorP() ? ((cppNonPointerTypeP(elementtype) ? wrapString("new (PointerFreeGC)") : wrapString("new (GC)"))) : wrapString("new")), NIL), listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_ARRAY_REFERENCE, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateAndPointerizeTypeSpec(elementtype), NIL), dimensions->concatenate(NIL, 0)), NIL));
    }
  }
}

Cons* cppTranslateVoidSys(Cons* tree) {
  return (((Cons*)(cppTranslateATree(tree->rest->value))));
}

Cons* cppTranslateTypedSys(Cons* tree) {
  return (((Cons*)(cppTranslateATree(tree->rest->value))));
}

Object* cppTranslateBadSys(Cons* tree) {
  { Object* returntype = tree->rest->rest->value;

    if (returntype == SGT_CPP_TRANSLATE_STELLA_VOID) {
      return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, wrapString("illegal_stella_statement_flagged_by_the_translator"), NIL), NIL));
    }
    else {
      return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, wrapString("illegal_stella_expression_flagged_by_the_translator"), NIL));
    }
  }
}

Cons* cppTranslateSysReferencedSlotValue(Cons* tree) {
  { Object* objectref = tree->fourth();
    Object* slotname = tree->rest->rest->value;

    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_REFERENCED_SLOT_VALUE, cppTranslateATree(objectref), cons(cppTranslateName(((Symbol*)(slotname))), NIL)));
  }
}

Cons* cppTranslateSysSlotValue(Cons* tree) {
  { Surrogate* objecttype = ((Surrogate*)(tree->rest->value));
    Object* objectref = tree->fourth();
    Symbol* slotname = trueSlotName(((Symbol*)(tree->rest->rest->value)), objecttype);

    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_SLOT_VALUE, cppTranslateATree(objectref), cons(cppTranslateName(slotname), NIL)));
  }
}

Cons* cppTranslateSysSlotValueSetter(Cons* tree) {
  { Object* objectref = tree->fourth();
    Surrogate* objecttype = ((Surrogate*)(tree->rest->value));
    Symbol* slotname = trueSlotName(((Symbol*)(tree->rest->rest->value)), objecttype);
    Object* valueref = cppTranslateATree(tree->fifth());
    Cons* otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_SLOT_VALUE_SETTER, cppTranslateATree(objectref), cons(cppTranslateName(slotname), cons(valueref, NIL)));

    tree->thirdSetter(NULL);
    tree->fourthSetter(NULL);
    tree->fifthSetter(NULL);
    return (otree);
  }
}

Cons* cppTranslateMakeTree(Cons* tree) {
  { Symbol* classname = ((Symbol*)(tree->rest->value));
    Class* clasS = classname->lookupClass();
    const char* nativetype = ((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_CPP_TRANSLATE_STELLA_CLASS_CPP_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue;
    Cons* arguments = cppTranslateActualParameters(tree->rest->rest);

    if (nativetype == NULL) {
      if (cppTypeWithoutInteriorPointersP(clasS->classType)) {
        return (listO(5, SYM_CPP_TRANSLATE_STELLA_CPP_MAKE, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_ACTUALS, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, wrapString("PointerFreeGC"), NIL), NIL), listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateClassName(classname), NIL), arguments, NIL));
      }
      else {
        return (listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_MAKE, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateClassName(classname), NIL), arguments, NIL));
      }
    }
    else if (cppNativePointerTypeP(nativetype)) {
      return (listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_MAKE, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, wrapString(cppUnpointerizeNativeType(nativetype)), NIL), arguments, NIL));
    }
    else {
      return (listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, wrapString(nativetype), NIL), arguments, NIL));
    }
  }
}

Cons* cppTranslateStartupTimeProgn(Cons* tree) {
  { Object* otree = cppTranslateATree(tree->rest->value);

    tree->rest = NIL;
    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_STARTUP_TIME_PROGN, otree, NIL));
  }
}

boolean cppStreamIsStandardOutputP(Object* tree) {
  if (safePrimaryType(tree) == SGT_CPP_TRANSLATE_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      return (equalConsTreesP(tree, getQuotedTree("((SYS-SLOT-VALUE @OUTPUT-STREAM NATIVE-STREAM STANDARD-OUTPUT) \"/STELLA\")", "/STELLA")));
    }
  }
  else {
    return (false);
  }
}

Cons* cppTranslatePrintStream(Cons* tree) {
  tree->firstSetter(SYM_CPP_TRANSLATE_STELLA_CPP_PRINT_STREAM);
  if (subtypeOfKeywordP(safePrimaryType(tree->rest->value))) {
    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->rest->value));

      if ((testValue000 == KWD_CPP_TRANSLATE_WARN) ||
          ((testValue000 == KWD_CPP_TRANSLATE_ERROR) ||
           (testValue000 == KWD_CPP_TRANSLATE_CONTINUABLE_ERROR))) {
        tree->secondSetter(SYM_CPP_TRANSLATE_STELLA_CPP_STANDARD_ERROR);
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
  else {
    if (cppStreamIsStandardOutputP(tree->rest->value)) {
      tree->secondSetter(SYM_CPP_TRANSLATE_STELLA_CPP_STANDARD_OUT);
    }
    else {
      tree->secondSetter(cppTranslateATree(tree->rest->value));
    }
  }
  { ConsIterator* it = tree->rest->rest->allocateIterator();

    for (; it->nextP(); ) {
      if (it->value == SYM_CPP_TRANSLATE_STELLA_EOL) {
        it->valueSetter(getQuotedTree("((CPP_IDENT \"std::endl\") \"/STELLA\")", "/STELLA"));
      }
      else {
        it->valueSetter(cppTranslateATree(it->value));
      }
    }
  }
  return (tree);
}

Cons* cppTranslateSetqTree(Cons* tree) {
  return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_ASSIGN, cppTranslateATree(tree->rest->value), cons(cppTranslateATree(tree->rest->rest->value), NIL)));
}

Object* cppTranslateSysSetDefault(Cons* tree) {
  return (cppTranslateSetqTree(tree));
}

Cons* cppTranslateNull() {
  return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, wrapString("NULL"), NIL));
}

Cons* Object::cppTranslateAtomicTree() {
  { Object* tree = this;

    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_LITERAL, tree, NIL));
  }
}

Cons* Keyword::cppTranslateAtomicTree() {
  { Keyword* tree = this;

    if (useHardcodedSymbolsP()) {
      return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_SYMBOL, tree, NIL));
    }
    else {
      return (yieldSymbolConstantName(tree)->cppTranslateAtomicTree());
    }
  }
}

Cons* Surrogate::cppTranslateAtomicTree() {
  { Surrogate* tree = this;

    if (useHardcodedSymbolsP()) {
      return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_SYMBOL, tree, NIL));
    }
    else {
      return (yieldSymbolConstantName(tree)->cppTranslateAtomicTree());
    }
  }
}

Cons* Symbol::cppTranslateAtomicTree() {
  { Symbol* tree = this;

    { GlobalVariable* globalvar = tree->softPermanentify()->lookupGlobalVariable();

      if (((boolean)(globalvar))) {
        return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateGlobalVariableName(globalvar), NIL));
      }
      else {
        return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateName(tree), NIL));
      }
    }
  }
}

Cons* QuotedExpression::cppTranslateAtomicTree() {
  { QuotedExpression* tree = this;

    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_LITERAL, tree, NIL));
  }
}

Cons* cppTranslateLetTree(Cons* tree) {
  { Cons* odeclarations = NIL;

    { Object* declaration = NULL;
      Cons* iter000 = ((Cons*)(tree->rest->value));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        declaration = iter000->value;
        { Cons* d = ((Cons*)(declaration));

          odeclarations = cons(cons(cppTranslateAndPointerizeTypeSpec(((StandardObject*)(d->rest->value))), cons(cppTranslateATree(d->value), cons(cppTranslateATree(d->rest->rest->value), NIL))), odeclarations);
        }
      }
    }
    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_BLOCK, odeclarations->reverse(), cons(cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, cppTranslateListOfTrees(tree->rest->rest)->concatenate(NIL, 0)), NIL)));
  }
}

StringWrapper* cppTranslateTypeSpec(StandardObject* typespec) {
  { Surrogate* testValue000 = safePrimaryType(typespec);

    if (subtypeOfParametricTypeSpecifierP(testValue000)) {
      { StandardObject* typespec000 = typespec;
        ParametricTypeSpecifier* typespec = ((ParametricTypeSpecifier*)(typespec000));

        if (arrayTypeSpecifierP(typespec)) {
          return (cppTranslateArrayType(typespec));
        }
        if (oTRANSLATOROUTPUTLANGUAGEo == KWD_CPP_TRANSLATE_CPP_STANDALONE) {
          return (wrapString(stringConcatenate(cppTranslateTypeSpec(typespec->specifierBaseType)->wrapperValue, "<", 2, cppTranslateAndPointerizeTypeSpec(((StandardObject*)(typespec->specifierParameterTypes->first())))->wrapperValue, ">")));
        }
        else {
          return (cppTranslateTypeSpec(typespec->specifierBaseType));
        }
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { StandardObject* typespec001 = typespec;
        Surrogate* typespec = ((Surrogate*)(typespec001));

        if (((StringWrapper*)(dynamicSlotValue(((Class*)(typespec->surrogateValue))->dynamicSlots, SYM_CPP_TRANSLATE_STELLA_CLASS_CPP_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue != NULL) {
          return (wrapString(((StringWrapper*)(dynamicSlotValue(((Class*)(typespec->surrogateValue))->dynamicSlots, SYM_CPP_TRANSLATE_STELLA_CLASS_CPP_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue));
        }
        else {
          return (cppTranslateClassTypename(symbolize(((Class*)(typespec->surrogateValue))->classType)));
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

StringWrapper* cppTranslateAndPointerizeTypeSpec(StandardObject* typespec) {
  { Surrogate* basetype = typeSpecToBaseType(typespec);
    StringWrapper* translatedtype = cppTranslateTypeSpec(typespec);

    if (createNativeClassP(((Class*)(basetype->surrogateValue))) ||
        exceptionClassP(((Class*)(basetype->surrogateValue)))) {
      translatedtype->wrapperValue = stringConcatenate(translatedtype->wrapperValue, "*", 0);
    }
    return (translatedtype);
  }
}

StringWrapper* cppTranslateAndReferencizeTypeSpec(StandardObject* typespec) {
  { Surrogate* basetype = typeSpecToBaseType(typespec);
    StringWrapper* translatedtype = cppTranslateTypeSpec(typespec);

    translatedtype->wrapperValue = (cppTranslatedArrayTypeP(translatedtype) ? cppGenerateArrayTypedEntity("&", translatedtype->wrapperValue) : stringConcatenate(translatedtype->wrapperValue, (createNativeClassP(((Class*)(basetype->surrogateValue))) ? "*&" : "&"), 0));
    return (translatedtype);
  }
}

StringWrapper* cppTranslateArrayType(ParametricTypeSpecifier* arraytype) {
  { boolean dummy1;

    { List* dimensions = arrayTypeDimensions(arraytype);
      StandardObject* elementtype = extractParameterType(arraytype, SYM_CPP_TRANSLATE_STELLA_ANY_VALUE, dummy1);
      const char* translatedtype = "";
      const char* temp = NULL;

      if (dimensions->length() == 1) {
        return (wrapString(stringConcatenate(cppTranslateAndPointerizeTypeSpec(elementtype)->wrapperValue, "*", 0)));
      }
      { IntegerWrapper* dim = NULL;
        Cons* iter000 = dimensions->theConsList;
        int i = NULL_INTEGER;
        int iter001 = 0;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          dim = ((IntegerWrapper*)(iter000->value));
          i = iter001;
          if (i == 0) {
            temp = "(*)";
          }
          else if (!((boolean)(dim))) {
            temp = "[]";
          }
          else {
            temp = stringConcatenate("[", stringify(dim), 1, "]");
          }
          translatedtype = stringConcatenate(translatedtype, temp, 0);
        }
      }
      if (arrayTypeSpecifierP(elementtype)) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          signalTranslationError();
          if (!(suppressWarningsP())) {
            printErrorContext(">> ERROR: ", STANDARD_ERROR);
            *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Can't yet handle nested arrays in C++: " << "`" << deUglifyParseTree(arraytype) << "'" << "." << std::endl;
          }
        }
        elementtype = SGT_CPP_TRANSLATE_STELLA_UNKNOWN;
      }
      temp = cppTranslateAndPointerizeTypeSpec(elementtype)->wrapperValue;
      translatedtype = stringConcatenate(temp, " ", 1, translatedtype);
      return (wrapString(translatedtype));
    }
  }
}

boolean cppTranslatedArrayTypeP(Object* translatedtype) {
  { Surrogate* testValue000 = safePrimaryType(translatedtype);

    if (testValue000 == SGT_CPP_TRANSLATE_STELLA_CONS) {
      { Object* translatedtype000 = translatedtype;
        Cons* translatedtype = ((Cons*)(translatedtype000));

        return (cppTranslatedArrayTypeP(translatedtype->last()));
      }
    }
    else if (subtypeOfStringP(testValue000)) {
      { Object* translatedtype001 = translatedtype;
        StringWrapper* translatedtype = ((StringWrapper*)(translatedtype001));

        { const char* transtype = translatedtype->wrapperValue;

          return ((transtype[(strlen(transtype) - 1)] == ']') &&
              ((stringSearch(transtype, "(*)", 0) != NULL_INTEGER) ||
               (stringSearch(transtype, "(*&)", 0) != NULL_INTEGER)));
        }
      }
    }
    else {
    }
  }
  return (false);
}

const char* cppGenerateArrayTypedEntity(const char* entity, const char* translatedarraytype) {
  { boolean referencetypeP = stringSearch(translatedarraytype, "(*&)", 0) != NULL_INTEGER;

    if (referencetypeP) {
      return (replaceSubstrings(translatedarraytype, stringConcatenate("(*&", entity, 1, ")"), "(*&)"));
    }
    else {
      return (replaceSubstrings(translatedarraytype, stringConcatenate("(*", entity, 1, ")"), "(*)"));
    }
  }
}

boolean cppNativePointerTypeP(const char* nativetype) {
  { int length = strlen(nativetype);

    { int i = NULL_INTEGER;
      int iter000 = 1;
      int upperBound000 = length;
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter000 <= upperBound000); 
            iter000 = iter000 + 1) {
        i = iter000;
        switch (nativetype[(length - i)]) {
          case ' ': 
          case '\t': 
          case '\n': 
          case '\r': 
            continue;
            break;
          case '*': 
            return (true);
          default:
            goto loopExit093;
            break;
        }
      }
    }
    loopExit093:;
    return (false);
  }
}

const char* cppUnpointerizeNativeType(const char* nativetype) {
  { int length = strlen(nativetype);

    { int i = NULL_INTEGER;
      int iter000 = 1;
      int upperBound000 = length;
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter000 <= upperBound000); 
            iter000 = iter000 + 1) {
        i = iter000;
        switch (nativetype[(length - i)]) {
          case ' ': 
          case '\t': 
          case '\n': 
          case '\r': 
            continue;
            break;
          case '*': 
            return (stringSubsequence(nativetype, 0, length - i));
          default:
            goto loopExit094;
            break;
        }
      }
    }
    loopExit094:;
    return (nativetype);
  }
}

const char* cppCreateCharacterSubstitutionTable() {
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
    table[((int)(unsigned char) '[')] = 'J';
    table[((int)(unsigned char) '\\')] = '_';
    table[((int)(unsigned char) ']')] = 'K';
    table[((int)(unsigned char) '^')] = 'U';
    table[((int)(unsigned char) '`')] = '_';
    table[((int)(unsigned char) '{')] = 'Y';
    table[((int)(unsigned char) '|')] = 'V';
    table[((int)(unsigned char) '}')] = 'Z';
    table[((int)(unsigned char) '~')] = 'T';
    return (table);
  }
}

const char* oCPP_CHARACTER_SUBSTITUTION_TABLEo = NULL;

const char* replaceFirstCharacterWithString(const char* string, const char* newprefix) {
  return (stringConcatenate(newprefix, stringSubsequence(string, 1, NULL_INTEGER)));
}

const char* cppSubstituteForbiddenCharacters(const char* name, Keyword* caseconvention) {
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
        substitution = oCPP_CHARACTER_SUBSTITUTION_TABLEo[((int)(unsigned char) (result[i]))];
        if (!(substitution == '=')) {
          if (caseconvention == KWD_CPP_TRANSLATE_UPPERCASE) {
            result[i] = (oCHARACTER_DOWNCASE_TABLEo[((int)(unsigned char) substitution)]);
          }
          else if (caseconvention == KWD_CPP_TRANSLATE_LOWERCASE) {
            result[i] = (oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) substitution)]);
          }
          else if (caseconvention == KWD_CPP_TRANSLATE_CAPITALIZED) {
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

const char* cppChangeCase(GeneralizedSymbol* symbol, Keyword* caseconvention) {
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_CPP_TRANSLATE_STELLA_F_CPP_CHANGE_CASE_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_CPP_TRANSLATE_STELLA_F_CPP_CHANGE_CASE_MEMO_TABLE_000, "(:MAX-VALUES 2000)");
        memoTable000 = ((MemoizationTable*)(SGT_CPP_TRANSLATE_STELLA_F_CPP_CHANGE_CASE_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), symbol, caseconvention, oMODULEo, MEMOIZED_NULL_VALUE, -1);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = wrapString(helpCppChangeCase(symbol, caseconvention));
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { StringWrapper* value000 = ((StringWrapper*)(memoizedValue000));

      return (value000->wrapperValue);
    }
  }
}

const char* helpCppChangeCase(GeneralizedSymbol* symbol, Keyword* caseconvention) {
  { Module* module = ((Module*)(symbol->homeContext));
    const char* name = symbol->symbolName;
    boolean allUpperP = allUpperCaseStringP(name);
    Keyword* capsBreakKeyword = (allUpperP ? KWD_CPP_TRANSLATE_CLEVER : KWD_CPP_TRANSLATE_YES);

    if (!((boolean)(module))) {
      module = oMODULEo;
    }
    if (module->caseSensitiveP ||
        (!allUpperP)) {
      return (makeMatchingNameFull(name, KWD_CPP_TRANSLATE_NO, KWD_CPP_TRANSLATE_NO, "- ", "", "", "", "", KWD_CPP_TRANSLATE_PRESERVE, "_"));
    }
    if (caseconvention == KWD_CPP_TRANSLATE_UPPERCASE) {
      return (makeMatchingNameFull(name, KWD_CPP_TRANSLATE_NO, KWD_CPP_TRANSLATE_NO, "- ", "", "", "", "", KWD_CPP_TRANSLATE_UPCASE, "_"));
    }
    else if (caseconvention == KWD_CPP_TRANSLATE_LOWERCASE) {
      return (makeMatchingNameFull(name, capsBreakKeyword, KWD_CPP_TRANSLATE_CLEVER, "- ", "", "", "", "", KWD_CPP_TRANSLATE_TITLECASEX, ""));
    }
    else if (caseconvention == KWD_CPP_TRANSLATE_CAPITALIZED) {
      return (makeMatchingNameFull(name, capsBreakKeyword, KWD_CPP_TRANSLATE_CLEVER, "- ", "", "", "", "", KWD_CPP_TRANSLATE_TITLECASE, ""));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << caseconvention << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

const char* cppYieldNamespacePrefixFromModule(Module* module) {
  if (!((boolean)(module))) {
    module = oMODULEo;
  }
  { const char* packageprefix = module->cppPackage();
    boolean packageprefixinheritedP = ((StringWrapper*)(dynamicSlotValue(module->dynamicSlots, SYM_CPP_TRANSLATE_STELLA_MODULE_CPP_PACKAGE, NULL_STRING_WRAPPER)))->wrapperValue == NULL;

    if (packageprefixinheritedP) {
      { const char* relativemodulepath = module->moduleFullName;

        return (stringConcatenate(packageprefix, cppSubstituteForbiddenCharacters(stringSubstitute(stringDowncase(relativemodulepath), '_', '/'), KWD_CPP_TRANSLATE_LOWERCASE), 0));
      }
    }
    else {
      return (packageprefix);
    }
  }
}

const char* cppYieldNamespacePrefix(GeneralizedSymbol* symbol) {
  return (cppYieldNamespacePrefixFromModule(((Module*)(symbol->homeContext))));
}

DEFINE_STELLA_SPECIAL(oCPP_NAME_QUALIFICATION_MODEo, Keyword* , NULL);

Keyword* cppNameQualificationMode() {
  return (oCPP_NAME_QUALIFICATION_MODEo);
}

boolean cppQualifyNameP(GeneralizedSymbol* namesymbol) {
  { Module* symbolmodule = ((Module*)(namesymbol->homeContext));
    Module* namespacemodule = (((boolean)(oCPP_CURRENT_UNIT_MODULEo)) ? oCPP_CURRENT_UNIT_MODULEo : oMODULEo);

    if ((!((boolean)(symbolmodule))) ||
        (namesymbol == SYM_CPP_TRANSLATE_STELLA_NULL)) {
      return (false);
    }
    if (symbolP(namesymbol) &&
        nativeNameP(((Symbol*)(namesymbol)), KWD_CPP_TRANSLATE_CPP, NULL)) {
      return (true);
    }
    if (oCPP_NAME_QUALIFICATION_MODEo == KWD_CPP_TRANSLATE_FULL) {
      return (true);
    }
    else if (oCPP_NAME_QUALIFICATION_MODEo == KWD_CPP_TRANSLATE_NEVER) {
      return (false);
    }
    else if (oCPP_NAME_QUALIFICATION_MODEo == KWD_CPP_TRANSLATE_CLEVER) {
      if (symbolmodule == namespacemodule) {
        return (false);
      }
      else if (!visibleFromP(symbolmodule, namespacemodule)) {
        return (true);
      }
      else {
        { Surrogate* testValue000 = safePrimaryType(namesymbol);

          if (subtypeOfSymbolP(testValue000)) {
            { GeneralizedSymbol* namesymbol000 = namesymbol;
              Symbol* namesymbol = ((Symbol*)(namesymbol000));

              return (!(lookupVisibleSymbolsInModule(namesymbol->symbolName, namespacemodule, false)->rest == NIL));
            }
          }
          else if (subtypeOfSurrogateP(testValue000)) {
            { GeneralizedSymbol* namesymbol001 = namesymbol;
              Surrogate* namesymbol = ((Surrogate*)(namesymbol001));

              return (!(lookupVisibleSurrogatesInModule(namesymbol->symbolName, namespacemodule, false)->rest == NIL));
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
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "`" << oCPP_NAME_QUALIFICATION_MODEo << "'" << " is not a valid case option";
        throw *newStellaException(stream001->theStringReader());
      }
    }
  }
}

const char* oCPP_NAMESPACE_SEPARATORo = "::";

const char* cppYieldQualifiedName(const char* translatedname, GeneralizedSymbol* sourcesymbol) {
  if (!(cppQualifyNameP(sourcesymbol))) {
    return (translatedname);
  }
  { const char* prefix = cppYieldNamespacePrefix(sourcesymbol);

    if (stringEqlP(prefix, "")) {
      return (translatedname);
    }
    else {
      return (stringConcatenate(prefix, oCPP_NAMESPACE_SEPARATORo, 1, translatedname));
    }
  }
}

Symbol* cppFixupNameSymbol(Symbol* namesymbol, Module* homemodule) {
  if (((Module*)(namesymbol->homeContext)) == homemodule) {
    return (namesymbol);
  }
  else {
    { Symbol* self000 = newSymbol(namesymbol->symbolName);

      self000->homeContext = homemodule;
      { Symbol* value000 = self000;

        return (value000);
      }
    }
  }
}

StringWrapper* cppTranslateName(Symbol* namesymbol) {
  { StringWrapper* reservedname = cppLookupReservedWordTable(namesymbol);

    if (!((boolean)(namesymbol))) {
      return (wrapString("NULL"));
    }
    if (((boolean)(reservedname))) {
      return (reservedname);
    }
    return (wrapString(cppSubstituteForbiddenCharacters(cppChangeCase(namesymbol, KWD_CPP_TRANSLATE_LOWERCASE), KWD_CPP_TRANSLATE_LOWERCASE)));
  }
}

StringWrapper* cppTranslateGlobalName(Symbol* namesymbol) {
  if (!((boolean)(namesymbol))) {
    return (wrapString("NULL"));
  }
  if (namesymbol == SYM_CPP_TRANSLATE_STELLA_TRUE) {
    return (oCPP_TRUE_STRING_WRAPPERo);
  }
  if (namesymbol == SYM_CPP_TRANSLATE_STELLA_FALSE) {
    return (oCPP_FALSE_STRING_WRAPPERo);
  }
  return (wrapString(cppYieldQualifiedName(cppSubstituteForbiddenCharacters(cppChangeCase(namesymbol, KWD_CPP_TRANSLATE_UPPERCASE), KWD_CPP_TRANSLATE_UPPERCASE), namesymbol)));
}

StringWrapper* cppTranslateClassParameterName(Symbol* namesymbol) {
  return (wrapString(cppSubstituteForbiddenCharacters(cppChangeCase(namesymbol, KWD_CPP_TRANSLATE_UPPERCASE), KWD_CPP_TRANSLATE_UPPERCASE)));
}

StringWrapper* cppTranslateReturnParameterName(Symbol* namesymbol, int parameternumber) {
  { Symbol* returnsymbol = internSymbol(stringConcatenate(namesymbol->symbolName, integerToString(((long long int)(parameternumber))), 0));
    StringWrapper* translatedname = cppTranslateName(returnsymbol);

    return (translatedname);
  }
}

StringWrapper* cppTranslateSymbolConstantName(GeneralizedSymbol* symbol) {
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
    return (wrapString(cppSubstituteForbiddenCharacters(stringConcatenate(prefix, stringConcatenate("_", symbol->symbolName, 0), 0), KWD_CPP_TRANSLATE_UPPERCASE)));
  }
}

StringWrapper* cppTranslateSymbolConstantId(GeneralizedSymbol* symbol) {
  { StringWrapper* translatedsymbol = cppTranslateSymbolConstantName(symbol);

    translatedsymbol->wrapperValue = stringConcatenate(translatedsymbol->wrapperValue, "_id", 0);
    return (translatedsymbol);
  }
}

StringWrapper* cppTranslateSymbolName(Symbol* symbol) {
  return (cppTranslateSymbolConstantName(symbol));
}

StringWrapper* cppTranslateSymbolId(Symbol* symbol) {
  return (cppTranslateSymbolConstantId(symbol));
}

StringWrapper* cppTranslateSurrogateName(Surrogate* surrogate) {
  return (cppTranslateSymbolConstantName(surrogate));
}

StringWrapper* cppTranslateSurrogateId(Surrogate* surrogate) {
  return (cppTranslateSymbolConstantId(surrogate));
}

StringWrapper* cppTranslateKeywordName(Keyword* keyword) {
  return (cppTranslateSymbolConstantName(keyword));
}

StringWrapper* cppTranslateKeywordId(Keyword* keyword) {
  return (cppTranslateSymbolConstantId(keyword));
}

StringWrapper* cppTranslateClassTypename(GeneralizedSymbol* namesymbol) {
  { Surrogate* realnamesymbol = ((Class*)(namesymbol->surrogatify()->surrogateValue))->classType;

    return (wrapString(cppYieldQualifiedName(cppSubstituteForbiddenCharacters(cppChangeCase(realnamesymbol, KWD_CPP_TRANSLATE_CAPITALIZED), KWD_CPP_TRANSLATE_CAPITALIZED), realnamesymbol)));
  }
}

StringWrapper* cppTranslateClassName(GeneralizedSymbol* namesymbol) {
  return (cppTranslateTypeSpec(namesymbol->surrogatify()));
}

boolean cppReferenceTypeP(StandardObject* typespec) {
  typespec = typespec;
  return (false);
}

StringWrapper* cppReferencizeType(StandardObject* typespec) {
  return (wrapString(stringSubstitute(cppTranslateTypeSpec(typespec)->wrapperValue, '&', '*')));
}

Object* cppTranslateFunctionParameter(Symbol* name, StandardObject* type, MethodSlot* method) {
  type = computeRelativeTypeSpec(type, method->slotOwner);
  if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_CPP_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue &&
      ((variableArgumentsName(method) == name) &&
       passVariableArgumentsAsListP(method))) {
    type = yieldListifiedVariableArgumentsType(method);
  }
  return (cons((cppReferenceTypeP(type) ? cppReferencizeType(type) : cppTranslateAndPointerizeTypeSpec(type)), cons(cppTranslateName(name), NIL)));
}

Cons* cppTranslateReturnParameter(int parameternumber, StandardObject* parametertype) {
  return (cons(cppTranslateAndReferencizeTypeSpec(parametertype), cons(cppTranslateReturnParameterName(SYM_CPP_TRANSLATE_STELLA__RETURN, parameternumber), NIL)));
}

Cons* cppTranslateFunctionParameters(MethodSlot* method) {
  { boolean skipfirstparameterP = !cppMethodObjectIsFunctionP(method);
    boolean variableargumentsP = ((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_CPP_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue &&
        (!passVariableArgumentsAsListP(method));
    Cons* translatedparameters = NIL;

    { Symbol* pname = NULL;
      Cons* iter000 = method->methodParameterNames_reader()->theConsList;
      StandardObject* ptype = NULL;
      Cons* iter001 = method->methodParameterTypeSpecifiers_reader()->theConsList;
      int i = NULL_INTEGER;
      int iter002 = 1;
      Cons* collect000 = NULL;

      for  (; (!(iter000 == NIL)) &&
                (!(iter001 == NIL)); 
            iter000 = iter000->rest,
            iter001 = iter001->rest,
            iter002 = iter002 + 1) {
        pname = ((Symbol*)(iter000->value));
        ptype = ((StandardObject*)(iter001->value));
        i = iter002;
        if (((!skipfirstparameterP) ||
            (i > 1)) &&
            ((!variableargumentsP) ||
             (!(pname == variableArgumentsName(method))))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(cppTranslateFunctionParameter(pname, ptype, method), NIL);
              if (translatedparameters == NIL) {
                translatedparameters = collect000;
              }
              else {
                addConsToEndOfConsList(translatedparameters, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(cppTranslateFunctionParameter(pname, ptype, method), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    { StandardObject* rtype = NULL;
      Cons* iter003 = method->methodReturnTypeSpecifiers_reader()->rest();
      int rtypeindex = NULL_INTEGER;
      int iter004 = 1;
      Cons* collect001 = NULL;

      for  (; !(iter003 == NIL); 
            iter003 = iter003->rest,
            iter004 = iter004 + 1) {
        rtype = ((StandardObject*)(iter003->value));
        rtypeindex = iter004;
        if (!((boolean)(collect001))) {
          {
            collect001 = cons(cppTranslateReturnParameter(rtypeindex, rtype), NIL);
            if (translatedparameters == NIL) {
              translatedparameters = collect001;
            }
            else {
              addConsToEndOfConsList(translatedparameters, collect001);
            }
          }
        }
        else {
          {
            collect001->rest = cons(cppTranslateReturnParameter(rtypeindex, rtype), NIL);
            collect001 = collect001->rest;
          }
        }
      }
    }
    return (translatedparameters->concatenate(((variableargumentsP ? cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_VAR_ARGS, cppTranslateName(variableArgumentsName(method)), NIL), NIL) : NIL))->concatenate(NIL, 0), 0));
  }
}

boolean slotReaderFromNameP(Symbol* methodname, StandardObject* methodowner) {
  { Class* ownerclass = ((Class*)(((Surrogate*)(methodowner))->surrogateValue));
    Slot* slot = lookupSlot(ownerclass, methodname);

    return (((boolean)(slot)) &&
        isaP(slot, SGT_CPP_TRANSLATE_STELLA_STORAGE_SLOT));
  }
}

boolean slotReaderP(MethodSlot* method) {
  { Slot* lookedupslot = NULL;

    if (!(method->methodFunctionP)) {
      lookedupslot = lookupSlot(((Class*)(method->slotOwner->surrogateValue)), method->slotName);
    }
    return (((boolean)(lookedupslot)) &&
        isaP(lookedupslot, SGT_CPP_TRANSLATE_STELLA_STORAGE_SLOT));
  }
}

StringWrapper* cppTranslateConstructorName(MethodSlot* constructor) {
  return (cppTranslateClassName(constructor->slotName));
}

StringWrapper* cppTranslateFunctionNameFromName(Symbol* functionname) {
  { MethodSlot* function = lookupFunction(functionname);

    if (((boolean)(function))) {
      return (cppTranslateFunctionName(function, true));
    }
    else {
      return (cppTranslateName(functionname));
    }
  }
}

StringWrapper* cppTranslateFunctionName(MethodSlot* function, boolean qualifyP) {
  { Symbol* functionname = yieldRenamedNameIfNative(function->slotName, KWD_CPP_TRANSLATE_CPP, KWD_CPP_TRANSLATE_FUNCTION);
    const char* translatedname = NULL;

    if (cppMethodObjectIsOverloadedFunctionP(function)) {
      functionname = cppCreateOverloadedFunctionName(functionname, function->slotOwner);
    }
    translatedname = cppTranslateName(functionname)->wrapperValue;
    if (function->methodSetterP) {
      translatedname = stringConcatenate(translatedname, "_setter", 0);
    }
    if (slotReaderP(function)) {
      translatedname = stringConcatenate(translatedname, "_reader", 0);
    }
    if (qualifyP) {
      return (wrapString(cppYieldQualifiedName(translatedname, cppFixupNameSymbol(function->slotName, function->homeModule()))));
    }
    else {
      return (wrapString(translatedname));
    }
  }
}

StringWrapper* cppTranslateMethodNameFromName(Symbol* methodname, StandardObject* methodowner) {
  { const char* translatedname = cppTranslateName(yieldRenamedNameIfNative(methodname, KWD_CPP_TRANSLATE_CPP, KWD_CPP_TRANSLATE_FUNCTION))->wrapperValue;

    if (slotReaderFromNameP(methodname, methodowner)) {
      translatedname = stringConcatenate(translatedname, "_reader", 0);
    }
    return (wrapString(stringConcatenate(cppTranslateClassName(((GeneralizedSymbol*)(methodowner)))->wrapperValue, "::", 1, translatedname)));
  }
}

StringWrapper* cppTranslateMethodName(MethodSlot* method, boolean qualifyP) {
  { Surrogate* methodtype = method->slotOwner;

    if (cppMethodObjectIsFunctionP(method)) {
      return (cppTranslateFunctionName(method, qualifyP));
    }
    else {
      return (wrapString(stringConcatenate(cppTranslateClassName(internSymbolInModule(methodtype->symbolName, ((Module*)(methodtype->homeContext)), false))->wrapperValue, "::", 1, cppTranslateFunctionName(method, false)->wrapperValue)));
    }
  }
}

Cons* deleteQuotedNullStatements(Cons* trees) {
  return (trees->remove(SYM_CPP_TRANSLATE_STELLA_NULL));
}

boolean cppMethodObjectIsFunctionP(MethodSlot* method) {
  return (method->methodFunctionP ||
      cppMethodObjectIsOverloadedFunctionP(method));
}

boolean cppMethodObjectIsOverloadedFunctionP(MethodSlot* method) {
  return ((!method->methodFunctionP) &&
      ((((StringWrapper*)(dynamicSlotValue(((Class*)(method->slotOwner->surrogateValue))->dynamicSlots, SYM_CPP_TRANSLATE_STELLA_CLASS_CPP_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue != NULL) &&
       ((!((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_CPP_TRANSLATE_STELLA_METHOD_NATIVEp, FALSE_WRAPPER)))->wrapperValue) ||
        subtypeOfP(method->slotOwner, SGT_CPP_TRANSLATE_STELLA_LITERAL))));
}

Cons* wrapMethodBodyWithCppAuxiliaryDeclarations(Cons* methodbody, Cons* declarations) {
  { Cons* odeclarations = NIL;
    Cons* otree = NULL;

    declarations = declarations->reverse();
    { Object* declaration = NULL;
      Cons* iter000 = declarations;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        declaration = iter000->value;
        { Cons* d = ((Cons*)(declaration));

          odeclarations = cons(cons(cppTranslateAndPointerizeTypeSpec(((StandardObject*)(d->rest->value))), cons(cppTranslateATree(d->value), ((((boolean)(d->rest->rest->value)) ? consList(1, cppTranslateATree(d->rest->rest->value)) : NIL))->concatenate(NIL, 0))), odeclarations);
        }
      }
    }
    otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_BLOCK, odeclarations->reverse(), cons(methodbody, NIL)), NIL);
    return (otree);
  }
}

Cons* cppTranslateDefineMethodUnit(TranslationUnit* unit) {
  { 
    BIND_STELLA_SPECIAL(oMETHODBEINGWALKEDo, MethodSlot*, NULL);
    BIND_STELLA_SPECIAL(oCURRENTDUMMYINDEXo, int, 0);
    BIND_STELLA_SPECIAL(oDUMMYDECLARATIONSo, Cons*, NIL);
    { MethodSlot* method = ((MethodSlot*)(unit->theObject));
      boolean unitisfunction = cppMethodObjectIsFunctionP(method);
      Cons* bodytree = ((Cons*)(unit->codeRegister));
      Cons* returntype = NULL;
      Cons* otree = NIL;
      Cons* translatedmethodbody = NULL;

      oMETHODBEINGWALKEDo = method;
      bodytree = deleteQuotedNullStatements(bodytree);
      if (!unitisfunction) {
        oDUMMYDECLARATIONSo = cons(cons(((Symbol*)(method->methodParameterNames_reader()->first())), cons(method->slotOwner, cons(SYM_CPP_TRANSLATE_STELLA_THIS, NIL))), oDUMMYDECLARATIONSo);
      }
      translatedmethodbody = cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, cppTranslateListOfTrees(bodytree)->concatenate(NIL, 0));
      if (!(oDUMMYDECLARATIONSo == NIL)) {
        translatedmethodbody = wrapMethodBodyWithCppAuxiliaryDeclarations(translatedmethodbody, oDUMMYDECLARATIONSo);
      }
      if (((StringWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_CPP_TRANSLATE_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue != NULL) {
        translatedmethodbody->rest = cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_COMMENT, wrapString(((StringWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_CPP_TRANSLATE_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue), NIL), translatedmethodbody->rest->concatenate(NIL, 0));
      }
      returntype = (cppConstructorP(method) ? NIL : cons(cppTranslateAndPointerizeTypeSpec(computeMostGeneralReturnType(method, method->computeReturnTypeSpec(method->slotOwner))), NIL));
      otree = cons((unitisfunction ? SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION : SYM_CPP_TRANSLATE_STELLA_CPP_METHOD), cons(returntype, cons(cppTranslateMethodName(method, false), cons(cppTranslateFunctionParameters(method), cons(translatedmethodbody, NIL)))));
      if (cCallableWrapperMethodP(method)) {
        otree = cons(SYM_CPP_TRANSLATE_STELLA_CPP_EXTERN_C, otree);
        otree->thirdSetter(substituteConsTree(otree->rest->rest->value, wrapString("int"), wrapString("boolean")));
        { Object* vardecl = NULL;
          Cons* iter000 = ((Cons*)(otree->fifth()));

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            vardecl = iter000->value;
            if (consP(vardecl) &&
                eqlToStringP(((Cons*)(vardecl))->value, "boolean")) {
              ((Cons*)(vardecl))->firstSetter(wrapString("int"));
            }
          }
        }
      }
      return (otree);
    }
  }
}

Cons* cppTranslateReturnTree(Cons* tree) {
  { Cons* otree = NULL;
    Cons* returnassignments = NIL;
    Cons* returnvariables = NIL;
    Cons* methodotherreturntypes = oMETHODBEINGWALKEDo->methodReturnTypeSpecifiers_reader()->rest();
    Object* returnexpression = NULL;
    Cons* translatedreturnexpression = NIL;
    boolean needtemporaryreturnvariableP = (!(tree->rest->rest == NIL)) &&
        (!sideEffectFreeExpressionP(tree->rest->value));

    { Object* exp = NULL;
      Cons* iter000 = tree->rest->rest;
      int parameternum = NULL_INTEGER;
      int iter001 = 1;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        exp = iter000->value;
        parameternum = iter001;
        if (!sideEffectFreeExpressionP(exp)) {
          needtemporaryreturnvariableP = true;
        }
        returnassignments = cons(listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_ASSIGN, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateReturnParameterName(SYM_CPP_TRANSLATE_STELLA__RETURN, parameternum), NIL), cppTranslateATree(exp), NIL), returnassignments);
      }
    }
    returnassignments = returnassignments->reverse();
    returnexpression = tree->rest->value;
    if ((methodotherreturntypes->length() > 0) &&
        ((tree->rest->rest == NIL) &&
         (consP(returnexpression) &&
          (((boolean)(((Cons*)(returnexpression))->value)) &&
           ((((Cons*)(returnexpression))->value == SYM_CPP_TRANSLATE_STELLA_SYS_CALL_FUNCTION) ||
            (((Cons*)(returnexpression))->value == SYM_CPP_TRANSLATE_STELLA_SYS_CALL_METHOD)))))) {
      {
        { StandardObject* type = NULL;
          Cons* iter002 = methodotherreturntypes;
          int parameternum = NULL_INTEGER;
          int iter003 = 1;
          Cons* collect000 = NULL;

          for  (; !(iter002 == NIL); 
                iter002 = iter002->rest,
                iter003 = iter003 + 1) {
            type = ((StandardObject*)(iter002->value));
            parameternum = iter003;
            type = type;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(internSymbol(cppTranslateReturnParameterName(SYM_CPP_TRANSLATE_STELLA__RETURN, parameternum)->wrapperValue), NIL);
                if (returnvariables == NIL) {
                  returnvariables = collect000;
                }
                else {
                  addConsToEndOfConsList(returnvariables, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(internSymbol(cppTranslateReturnParameterName(SYM_CPP_TRANSLATE_STELLA__RETURN, parameternum)->wrapperValue), NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        translatedreturnexpression = cppTranslateMvFunctionCall(((Cons*)(returnexpression)), returnvariables);
      }
    }
    else {
      translatedreturnexpression = ((Cons*)(cppTranslateATree(returnexpression)));
    }
    if (returnassignments == NIL) {
      if (tree->rest == NIL) {
        otree = cons(SYM_CPP_TRANSLATE_STELLA_CPP_RETURN, NIL);
      }
      else {
        otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_RETURN, translatedreturnexpression, NIL);
      }
    }
    else {
      if (needtemporaryreturnvariableP) {
        { StringWrapper* tempvar = cppTranslateReturnParameterName(SYM_CPP_TRANSLATE_STELLA__RETURN, 0);

          otree = listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_BLOCK, cons(cons(cppTranslateAndPointerizeTypeSpec(oMETHODBEINGWALKEDo->computeReturnTypeSpec(oMETHODBEINGWALKEDo->slotOwner)), listO(3, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, tempvar, NIL), translatedreturnexpression, NIL)), NIL), cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, returnassignments->concatenate(cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_RETURN, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, tempvar, NIL), NIL), NIL), 0)), NIL);
        }
      }
      else {
        otree = cons(SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS, returnassignments->concatenate(cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_RETURN, translatedreturnexpression, NIL), NIL), 0));
      }
    }
    return (otree);
  }
}

Cons* cppTranslateActualParameters(Cons* tree) {
  return (cons(SYM_CPP_TRANSLATE_STELLA_CPP_ACTUALS, cppTranslateListOfTrees(tree)->concatenate(NIL, 0)));
}

Cons* cppTranslateVariableLengthActuals(Cons* actuals, MethodSlot* method) {
  { int nofparameters = method->methodParameterNames_reader()->length();
    int restargumentstart = (cppMethodObjectIsFunctionP(method) ? (nofparameters - 1) : (nofparameters - 2));
    Cons* otree = NIL;
    boolean pusheddummy = false;

    { Object* actual = NULL;
      Cons* iter000 = actuals;
      int i = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        actual = iter000->value;
        i = iter001;
        if (i == restargumentstart) {
          pusheddummy = true;
          { int result = actuals->length() - restargumentstart;

            otree = cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_LITERAL, wrapInteger(result), NIL), otree);
          }
        }
        otree = cons(cppTranslateATree(actual), otree);
      }
    }
    if (!(pusheddummy)) {
      otree = cons(listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_LITERAL, wrapInteger(0), NIL), otree);
    }
    return (cons(SYM_CPP_TRANSLATE_STELLA_CPP_ACTUALS, otree->reverse()->concatenate(NIL, 0)));
  }
}

Cons* cppTranslateCallMethodSetter(Cons* tree) {
  { Object* methodname = tree->rest->rest->value;
    Object* objectref = cppTranslateATree(tree->fourth());
    Object* valueref = cppTranslateATree(tree->fifth());

    return (listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_SETTER_CALL, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateName(((Symbol*)(methodname))), NIL), objectref, cons(valueref, NIL)));
  }
}

Symbol* cppCreateOverloadedFunctionName(Symbol* functionname, Surrogate* classtype) {
  return (internSymbolInModule(stringConcatenate(classtype->symbolName, "-", 1, functionname->symbolName), overloadedFunctionNameModule(functionname, classtype), true));
}

boolean cppPossiblyOverloadedFunctionNameP(Symbol* functionname) {
  { const char* fname = functionname->symbolName;
    int dashpos = stringPosition(fname, '-', 0);
    Class* clasS = NULL;

    while (dashpos != NULL_INTEGER) {
      clasS = stringLookupClass(stringSubsequence(fname, 0, dashpos));
      if (((boolean)(clasS)) &&
          (!subtypeOfP(clasS->classType, SGT_CPP_TRANSLATE_STELLA_OBJECT))) {
        return (true);
      }
      dashpos = stringPosition(fname, '-', dashpos + 1);
    }
    return (false);
  }
}

Cons* cppTranslateMethodCall(Cons* tree, boolean referencedP) {
  { Symbol* methodname = ((Symbol*)(tree->rest->value));
    Surrogate* owner = ((Surrogate*)(tree->value));
    Cons* arguments = tree->rest->rest;

    if ((methodname == SYM_CPP_TRANSLATE_STELLA_DEFINEDp) ||
        (methodname == SYM_CPP_TRANSLATE_STELLA_NULLp)) {
      return (cppTranslateDefinedPMethodCall(owner, arguments->value, methodname == SYM_CPP_TRANSLATE_STELLA_NULLp));
    }
    else if ((methodname == SYM_CPP_TRANSLATE_STELLA_NTH) ||
        (methodname == SYM_CPP_TRANSLATE_STELLA_NTH_SETTER)) {
      return (cppTranslateNthMethodCall(methodname, owner, arguments));
    }
    else if ((methodname == SYM_CPP_TRANSLATE_STELLA_AREF) ||
        (methodname == SYM_CPP_TRANSLATE_STELLA_AREF_SETTER)) {
      return (cppTranslateArefMethodCall(methodname, owner, arguments));
    }
    else {
      if ((owner == SGT_CPP_TRANSLATE_STELLA_ARGUMENT_LIST) ||
          (owner == SGT_CPP_TRANSLATE_STELLA_ARGUMENT_LIST_ITERATOR)) {
        return (cppTranslateArgumentListTree(methodname, owner, arguments->value));
      }
    }
    return (cppTranslateNormalMethodCall(methodname, owner, arguments, referencedP));
  }
}

Cons* cppTranslateSuperMethodCall(Cons* tree) {
  { Symbol* methodname = ((Symbol*)(tree->rest->value));
    Surrogate* owner = ((Surrogate*)(tree->value));
    Cons* arguments = tree->rest->rest;
    Slot* slot = lookupSlot(((Class*)(owner->surrogateValue)), methodname)->slotDirectEquivalent;
    Cons* otree = cppTranslateNormalMethodCall(methodname, slot->slotOwner, arguments, false);
    const char* qualmethodname = stringConcatenate(unwrapString(((StringWrapper*)(consTreeNth(otree, 2, 1, 1)))), "::", 1, ((StringWrapper*)(consTreeNth(otree, 2, 2, 1)))->wrapperValue);

    otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, wrapString(qualmethodname), NIL), otree->nthRest(4)->concatenate(NIL, 0));
    return (otree);
  }
}

Cons* cppTranslateNormalMethodCall(Symbol* methodname, Surrogate* owner, Cons* arguments, boolean referencedP) {
  { Slot* slot = lookupSlot(((Class*)(owner->surrogateValue)), methodname);
    MethodSlot* method = (methodSlotP(slot) ? ((MethodSlot*)(slot)) : NULL);
    Object* firstarg = arguments->value;
    Cons* otherargs = arguments->rest;

    { Cons* operatoR = cppLookupOperatorTable(methodname->softPermanentify());

      if (((boolean)(operatoR))) {
        return (cppTranslateOperatorCall(operatoR, arguments, arguments->length()));
      }
    }
    if (((boolean)(method)) &&
        cppMethodObjectIsOverloadedFunctionP(method)) {
      return (cppTranslateFunctionCall(cons(cppCreateOverloadedFunctionName(methodname, owner), arguments->concatenate(NIL, 0)), method));
    }
    { StringWrapper* translatedname = cppTranslateName(yieldRenamedNameIfNative(methodname, KWD_CPP_TRANSLATE_CPP, KWD_CPP_TRANSLATE_FUNCTION));

      if ((!((boolean)(method))) &&
          slotReaderFromNameP(methodname, owner)) {
        translatedname->wrapperValue = stringConcatenate(translatedname->wrapperValue, "_reader", 0);
      }
      otherargs = otherargs->concatenate(cppYieldUnusedDummyArgs(method, arguments), 0);
      return (cons((referencedP ? SYM_CPP_TRANSLATE_STELLA_CPP_REFERENCED_METHOD_CALL : SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_CALL), listO(4, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateClassName(internSymbolInModule(owner->symbolName, ((Module*)(owner->homeContext)), false)), NIL), listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, translatedname, NIL), cppTranslateATree(firstarg), cons(((((boolean)(method)) &&
          (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_CPP_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue &&
           (!passVariableArgumentsAsListP(method)))) ? cppTranslateVariableLengthActuals(otherargs, method) : cppTranslateActualParameters(otherargs)), NIL))));
    }
  }
}

Cons* cppTranslateDefinedPMethodCall(Surrogate* argumenttype, Object* argument, boolean nullP) {
  { Object* nullvalue = typeToWalkedNullValueTree(argumenttype, argumenttype);

    if (optimizeBooleanTestsP() &&
        subtypeOfP(argumenttype, SGT_CPP_TRANSLATE_STELLA_OBJECT)) {
      argument = listO(3, SYM_CPP_TRANSLATE_STELLA_CAST, argument, cons(SGT_CPP_TRANSLATE_STELLA_BOOLEAN, NIL));
      if (nullP) {
        return (cppTranslateOperatorCall(cppLookupOperatorTable(SYM_CPP_TRANSLATE_STELLA_NOT), cons(argument, NIL), 1));
      }
      else {
        return (((Cons*)(cppTranslateATree(argument))));
      }
    }
    else {
      return (cppTranslateOperatorCall(cppLookupOperatorTable((nullP ? SYM_CPP_TRANSLATE_STELLA_EQp : SYM_CPP_TRANSLATE_STELLA_xe)), cons(argument, cons(nullvalue, NIL)), 2));
    }
  }
}

Cons* cppTranslateNthMethodCall(Symbol* operatoR, Surrogate* owner, Cons* arguments) {
  { boolean setterP = operatoR == SYM_CPP_TRANSLATE_STELLA_NTH_SETTER;
    Object* collection = arguments->value;
    Object* position = arguments->last();
    Object* value = (setterP ? arguments->rest->value : ((Object*)(NULL)));
    Cons* tree = NULL;

    if ((owner == SGT_CPP_TRANSLATE_STELLA_STRING) ||
        ((owner == SGT_CPP_TRANSLATE_STELLA_MUTABLE_STRING) ||
         (owner == SGT_CPP_TRANSLATE_STELLA_NATIVE_VECTOR))) {
      if ((owner == SGT_CPP_TRANSLATE_STELLA_NATIVE_VECTOR) ||
          methodCallInliningEnabledP()) {
        collection = cppTranslateATree(collection);
        tree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_ARRAY_REFERENCE, collection, cons(cppTranslateATree(position), NIL));
        if (setterP) {
          tree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_ASSIGN, tree, cons(cppTranslateATree(value), NIL));
        }
        return (tree);
      }
    }
    else {
    }
    return (cppTranslateNormalMethodCall(operatoR, owner, arguments, false));
  }
}

Cons* cppTranslateArefMethodCall(Symbol* operatoR, Surrogate* owner, Cons* arguments) {
  if (owner == SGT_CPP_TRANSLATE_STELLA_ARRAY) {
    { boolean setterP = operatoR == SYM_CPP_TRANSLATE_STELLA_AREF_SETTER;
      Cons* otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_ARRAY_REFERENCE, cppTranslateATree(arguments->value), cppTranslateListOfTrees((setterP ? arguments->rest->rest : arguments->rest))->concatenate(NIL, 0));

      if (setterP) {
        otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_ASSIGN, otree, cons(cppTranslateATree(arguments->rest->value), NIL));
      }
      return (otree);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << owner << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Cons* cppTranslateFunctionSignature(MethodSlot* function) {
  { Cons* cppsig = yieldFunctionCppSignature(function, NULL, true);
    Cons* returns = cons(((StringWrapper*)(((Cons*)(cppsig->value))->rest->value)), NIL);
    Cons* params = NIL;

    { Cons* spec = NULL;
      Cons* iter000 = cppsig->rest;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        spec = ((Cons*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons((eqlToStringP(((StringWrapper*)(spec->value)), "...") ? ((StringWrapper*)(spec->value)) : ((StringWrapper*)(spec->rest->value))), NIL);
            if (params == NIL) {
              params = collect000;
            }
            else {
              addConsToEndOfConsList(params, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons((eqlToStringP(((StringWrapper*)(spec->value)), "...") ? ((StringWrapper*)(spec->value)) : ((StringWrapper*)(spec->rest->value))), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_SIGNATURE, returns, cons(params, NIL)));
  }
}

Cons* cppTranslateCodeSignature(Cons* signature) {
  { Cons* translatedreturntypes = NIL;
    Cons* translatedparametertypes = NIL;

    { Object* returntype = NULL;
      Cons* iter000 = ((Cons*)(signature->value));
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        returntype = iter000->value;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(cppTranslateAndPointerizeTypeSpec(((StandardObject*)(returntype))), NIL);
            if (translatedreturntypes == NIL) {
              translatedreturntypes = collect000;
            }
            else {
              addConsToEndOfConsList(translatedreturntypes, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(cppTranslateAndPointerizeTypeSpec(((StandardObject*)(returntype))), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { Object* parametertype = NULL;
      Cons* iter001 = signature->rest;
      Cons* collect001 = NULL;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest) {
        parametertype = iter001->value;
        if (!((boolean)(collect001))) {
          {
            collect001 = cons(cppTranslateAndPointerizeTypeSpec(((StandardObject*)(parametertype))), NIL);
            if (translatedparametertypes == NIL) {
              translatedparametertypes = collect001;
            }
            else {
              addConsToEndOfConsList(translatedparametertypes, collect001);
            }
          }
        }
        else {
          {
            collect001->rest = cons(cppTranslateAndPointerizeTypeSpec(((StandardObject*)(parametertype))), NIL);
            collect001 = collect001->rest;
          }
        }
      }
    }
    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_SIGNATURE, translatedreturntypes, cons(translatedparametertypes, NIL)));
  }
}

Cons* cppTranslateMethodCodeSignature(Cons* signature) {
  { Cons* translatedreturntypes = NIL;
    Cons* translatedparametertypes = NIL;
    StringWrapper* translatedobjecttype = cppTranslateTypeSpec(((StandardObject*)(signature->rest->value)));

    { Object* returntype = NULL;
      Cons* iter000 = ((Cons*)(signature->value));
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        returntype = iter000->value;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(cppTranslateAndPointerizeTypeSpec(((StandardObject*)(returntype))), NIL);
            if (translatedreturntypes == NIL) {
              translatedreturntypes = collect000;
            }
            else {
              addConsToEndOfConsList(translatedreturntypes, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(cppTranslateAndPointerizeTypeSpec(((StandardObject*)(returntype))), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { Object* parametertype = NULL;
      Cons* iter001 = signature->rest->rest;
      Cons* collect001 = NULL;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest) {
        parametertype = iter001->value;
        if (!((boolean)(collect001))) {
          {
            collect001 = cons(cppTranslateAndPointerizeTypeSpec(((StandardObject*)(parametertype))), NIL);
            if (translatedparametertypes == NIL) {
              translatedparametertypes = collect001;
            }
            else {
              addConsToEndOfConsList(translatedparametertypes, collect001);
            }
          }
        }
        else {
          {
            collect001->rest = cons(cppTranslateAndPointerizeTypeSpec(((StandardObject*)(parametertype))), NIL);
            collect001 = collect001->rest;
          }
        }
      }
    }
    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_SIGNATURE, translatedreturntypes, cons(translatedobjecttype, cons(translatedparametertypes, NIL))));
  }
}

Cons* cppTranslateCallFunctionCode(Cons* tree) {
  { Cons* signature = cppTranslateCodeSignature(((Cons*)(tree->rest->value)));
    Object* functionnameexpr = cppTranslateATree(tree->rest->rest->value);
    Cons* functionargs = tree->rest->rest->rest;

    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCALL, signature, cons(functionnameexpr, cons(cppTranslateActualParameters(functionargs), NIL))));
  }
}

Cons* cppTranslateCallMethodCode(Cons* tree) {
  { Cons* signature = cppTranslateMethodCodeSignature(((Cons*)(tree->rest->value)));
    Object* methodnameexpr = cppTranslateATree(tree->rest->rest->value);
    Object* theobject = tree->rest->rest->rest->value;
    Cons* methodargs = tree->rest->rest->rest->rest;

    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_CODE_CALL, signature, cons(methodnameexpr, cons(cppTranslateATree(theobject), cons(cppTranslateActualParameters(methodargs), NIL)))));
  }
}

Cons* getLastNElements(Cons* list, int n) {
  n = list->length() - n;
  if (n < 0) {
    n = 0;
  }
  return (list->nthRest(n));
}

Cons* cppYieldUnusedDummyArgs(MethodSlot* method, Cons* args) {
  if (!((boolean)(method))) {
    return (NIL);
  }
  { int numberofunusedreturnparameters = (method->methodParameterNames_reader()->length() + (method->methodReturnTypeSpecifiers_reader()->length() - 1)) - args->length();
    Cons* unusedreturntypes = NIL;
    Symbol* dummyname = NULL;
    Cons* dummyargs = NIL;

    if (numberofunusedreturnparameters > 0) {
      unusedreturntypes = getLastNElements(method->methodReturnTypeSpecifiers_reader()->rest(), numberofunusedreturnparameters);
      { Object* unusedparametertype = NULL;
        Cons* iter000 = unusedreturntypes;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          unusedparametertype = iter000->value;
          oCURRENTDUMMYINDEXo = oCURRENTDUMMYINDEXo + 1;
          dummyname = internSymbol(cppTranslateReturnParameterName(SYM_CPP_TRANSLATE_STELLA_DUMMY, oCURRENTDUMMYINDEXo)->wrapperValue);
          oDUMMYDECLARATIONSo = cons(cons(dummyname, cons(unusedparametertype, NIL)), oDUMMYDECLARATIONSo);
          dummyargs = cons(dummyname, dummyargs);
        }
      }
    }
    return (dummyargs->reverse());
  }
}

Cons* cppTranslateFunctionCall(Cons* tree, MethodSlot* method) {
  { Symbol* functionname = ((Symbol*)(tree->value));
    Cons* functionargs = copyConsList(tree->rest);
    Object* firstarg = functionargs->value;
    MethodSlot* function = (((boolean)(method)) ? method : lookupFunction(functionname));
    Cons* operatoR = cppLookupOperatorTable(functionname->softPermanentify());
    Cons* otree = NULL;

    if ((functionname == SYM_CPP_TRANSLATE_STELLA_GET_SYM) ||
        ((functionname == SYM_CPP_TRANSLATE_STELLA_GET_KWD) ||
         (functionname == SYM_CPP_TRANSLATE_STELLA_GET_SGT))) {
      if (subtypeOfIntegerP(safePrimaryType(firstarg))) {
        { Object* firstarg000 = firstarg;
          IntegerWrapper* firstarg = ((IntegerWrapper*)(firstarg000));

          return (cppTranslateHardcodedSymbolReference(functionname, firstarg->wrapperValue));
        }
      }
      else {
      }
    }
    else {
    }
    functionargs = functionargs->concatenate(cppYieldUnusedDummyArgs(function, functionargs), 0);
    if (((boolean)(operatoR))) {
      otree = cppTranslateOperatorCall(operatoR, functionargs, functionargs->length());
    }
    else {
      otree = listO(4, SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_IDENT, cppTranslateFunctionName(function, true), NIL), ((((BooleanWrapper*)(dynamicSlotValue(function->dynamicSlots, SYM_CPP_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue &&
          (!passVariableArgumentsAsListP(function))) ? cppTranslateVariableLengthActuals(functionargs, function) : cppTranslateActualParameters(functionargs)), NIL);
    }
    return (otree);
  }
}

Cons* cppTranslateOperatorTree(Cons* tree) {
  { Cons* operatoR = cppLookupOperatorTable(((Symbol*)(tree->value)));
    Cons* args = tree->rest;
    int arity = NULL_INTEGER;

    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

      if ((testValue000 == SYM_CPP_TRANSLATE_STELLA_AND) ||
          ((testValue000 == SYM_CPP_TRANSLATE_STELLA_OR) ||
           ((testValue000 == SYM_CPP_TRANSLATE_STELLA_EQp) ||
            ((testValue000 == SYM_CPP_TRANSLATE_STELLA_g) ||
             ((testValue000 == SYM_CPP_TRANSLATE_STELLA_ge) ||
              ((testValue000 == SYM_CPP_TRANSLATE_STELLA_l) ||
               (testValue000 == SYM_CPP_TRANSLATE_STELLA_le))))))) {
        arity = 2;
      }
      else if ((testValue000 == SYM_CPP_TRANSLATE_STELLA_NOT) ||
          ((testValue000 == SYM_CPP_TRANSLATE_STELLA_ii) ||
           (testValue000 == SYM_CPP_TRANSLATE_STELLA___))) {
        arity = 1;
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    return (cppTranslateOperatorCall(operatoR, args, arity));
  }
}

Cons* cppTranslateOperatorCall(Cons* operatornames, Cons* arguments, int arity) {
  { Cons* otree = NULL;

    switch (arity) {
      case 1: 
        otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_UNARY_OP, operatornames->value, cons(cppTranslateATree(arguments->value), NIL));
        break;
      case 2: 
        if (arguments->length() > 2) {
          otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_BINARY_OP, cppTranslateATree(arguments->value), cons(operatornames->value, cons(cppTranslateOperatorCall(((Cons*)(copyConsTree(operatornames))), arguments->rest, 2), NIL)));
        }
        else {
          otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_BINARY_OP, cppTranslateATree(arguments->value), cons(operatornames->value, cons(cppTranslateATree(arguments->rest->value), NIL)));
        }
        break;
      case 3: 
        otree = listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_TERNARY_OP, cppTranslateATree(arguments->value), cons(operatornames->value, cons(cppTranslateATree(arguments->rest->value), cons(operatornames->rest->value, cons(cppTranslateATree(arguments->rest->rest->value), NIL)))));
        break;
      default:
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << arity << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
        break;
    }
    return (otree);
  }
}

Cons* cppTranslateHardcodedSymbolReference(Symbol* operatoR, int offset) {
  { GeneralizedSymbol* symbol = NULL;

    if (operatoR == SYM_CPP_TRANSLATE_STELLA_GET_SYM) {
      symbol = getSymFromOffset(offset);
    }
    else if (operatoR == SYM_CPP_TRANSLATE_STELLA_GET_KWD) {
      symbol = getKwdFromOffset(offset);
    }
    else if (operatoR == SYM_CPP_TRANSLATE_STELLA_GET_SGT) {
      symbol = getSgtFromOffset(offset);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << operatoR << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    return (listO(3, SYM_CPP_TRANSLATE_STELLA_CPP_SYMBOL, symbol, NIL));
  }
}

void helpStartupCppTranslate1() {
  {
    KWD_CPP_TRANSLATE_USE_CPP_GARBAGE_COLLECTOR = ((Keyword*)(internRigidSymbolWrtModule("USE-CPP-GARBAGE-COLLECTOR", NULL, 2)));
    SGT_CPP_TRANSLATE_STELLA_KEY_VALUE_LIST = ((Surrogate*)(internRigidSymbolWrtModule("KEY-VALUE-LIST", NULL, 1)));
    SYM_CPP_TRANSLATE_STELLA_ii = ((Symbol*)(internRigidSymbolWrtModule("++", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA___ = ((Symbol*)(internRigidSymbolWrtModule("--", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_i = ((Symbol*)(internRigidSymbolWrtModule("+", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA__ = ((Symbol*)(internRigidSymbolWrtModule("-", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_o = ((Symbol*)(internRigidSymbolWrtModule("*", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_s = ((Symbol*)(internRigidSymbolWrtModule("/", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_EQp = ((Symbol*)(internRigidSymbolWrtModule("EQ?", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_xe = ((Symbol*)(internRigidSymbolWrtModule("!=", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_g = ((Symbol*)(internRigidSymbolWrtModule(">", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_ge = ((Symbol*)(internRigidSymbolWrtModule(">=", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_eg = ((Symbol*)(internRigidSymbolWrtModule("=>", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_l = ((Symbol*)(internRigidSymbolWrtModule("<", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_el = ((Symbol*)(internRigidSymbolWrtModule("=<", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_le = ((Symbol*)(internRigidSymbolWrtModule("<=", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_OR = ((Symbol*)(internRigidSymbolWrtModule("OR", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CHOOSE = ((Symbol*)(internRigidSymbolWrtModule("CHOOSE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_ASM = ((Symbol*)(internRigidSymbolWrtModule("ASM", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_ASSERT = ((Symbol*)(internRigidSymbolWrtModule("ASSERT", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_AUTO = ((Symbol*)(internRigidSymbolWrtModule("AUTO", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_BREAK = ((Symbol*)(internRigidSymbolWrtModule("BREAK", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CASE = ((Symbol*)(internRigidSymbolWrtModule("CASE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CATCH = ((Symbol*)(internRigidSymbolWrtModule("CATCH", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CHAR = ((Symbol*)(internRigidSymbolWrtModule("CHAR", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CLASS = ((Symbol*)(internRigidSymbolWrtModule("CLASS", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CONST = ((Symbol*)(internRigidSymbolWrtModule("CONST", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CONTINUE = ((Symbol*)(internRigidSymbolWrtModule("CONTINUE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_DEFAULT = ((Symbol*)(internRigidSymbolWrtModule("DEFAULT", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_DELETE = ((Symbol*)(internRigidSymbolWrtModule("DELETE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_DO = ((Symbol*)(internRigidSymbolWrtModule("DO", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_DOUBLE = ((Symbol*)(internRigidSymbolWrtModule("DOUBLE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_ELSE = ((Symbol*)(internRigidSymbolWrtModule("ELSE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_ENUM = ((Symbol*)(internRigidSymbolWrtModule("ENUM", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_EXTERN = ((Symbol*)(internRigidSymbolWrtModule("EXTERN", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_FLOAT = ((Symbol*)(internRigidSymbolWrtModule("FLOAT", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_FOR = ((Symbol*)(internRigidSymbolWrtModule("FOR", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_FRIEND = ((Symbol*)(internRigidSymbolWrtModule("FRIEND", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_GOTO = ((Symbol*)(internRigidSymbolWrtModule("GOTO", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_IF = ((Symbol*)(internRigidSymbolWrtModule("IF", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_INLINE = ((Symbol*)(internRigidSymbolWrtModule("INLINE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_INT = ((Symbol*)(internRigidSymbolWrtModule("INT", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_LONG = ((Symbol*)(internRigidSymbolWrtModule("LONG", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_NAMESPACE = ((Symbol*)(internRigidSymbolWrtModule("NAMESPACE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_NEW = ((Symbol*)(internRigidSymbolWrtModule("NEW", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_OPERATOR = ((Symbol*)(internRigidSymbolWrtModule("OPERATOR", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_PRIVATE = ((Symbol*)(internRigidSymbolWrtModule("PRIVATE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_PROTECTED = ((Symbol*)(internRigidSymbolWrtModule("PROTECTED", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_PUBLIC = ((Symbol*)(internRigidSymbolWrtModule("PUBLIC", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_REGISTER = ((Symbol*)(internRigidSymbolWrtModule("REGISTER", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_RETURN = ((Symbol*)(internRigidSymbolWrtModule("RETURN", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SHORT = ((Symbol*)(internRigidSymbolWrtModule("SHORT", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SIGNED = ((Symbol*)(internRigidSymbolWrtModule("SIGNED", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SIZEOF = ((Symbol*)(internRigidSymbolWrtModule("SIZEOF", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_STATIC = ((Symbol*)(internRigidSymbolWrtModule("STATIC", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_STRUCT = ((Symbol*)(internRigidSymbolWrtModule("STRUCT", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SWITCH = ((Symbol*)(internRigidSymbolWrtModule("SWITCH", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_TEMPLATE = ((Symbol*)(internRigidSymbolWrtModule("TEMPLATE", NULL, 0)));
  }
}

void helpStartupCppTranslate2() {
  {
    SYM_CPP_TRANSLATE_STELLA_THROW = ((Symbol*)(internRigidSymbolWrtModule("THROW", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_TRY = ((Symbol*)(internRigidSymbolWrtModule("TRY", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_TYPEDEF = ((Symbol*)(internRigidSymbolWrtModule("TYPEDEF", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_TYPEID = ((Symbol*)(internRigidSymbolWrtModule("TYPEID", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_UNION = ((Symbol*)(internRigidSymbolWrtModule("UNION", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_UNSIGNED = ((Symbol*)(internRigidSymbolWrtModule("UNSIGNED", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_VIRTUAL = ((Symbol*)(internRigidSymbolWrtModule("VIRTUAL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_VOID = ((Symbol*)(internRigidSymbolWrtModule("VOID", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_VOLATILE = ((Symbol*)(internRigidSymbolWrtModule("VOLATILE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_WHILE = ((Symbol*)(internRigidSymbolWrtModule("WHILE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_TYPENAME = ((Symbol*)(internRigidSymbolWrtModule("TYPENAME", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_GLOBAL_VARIABLE = ((Symbol*)(internRigidSymbolWrtModule("GLOBAL-VARIABLE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_TYPE = ((Symbol*)(internRigidSymbolWrtModule("TYPE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_METHOD = ((Symbol*)(internRigidSymbolWrtModule("METHOD", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_MACRO = ((Symbol*)(internRigidSymbolWrtModule("MACRO", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_PRINT_METHOD = ((Symbol*)(internRigidSymbolWrtModule("PRINT-METHOD", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_STARTUP_TIME_PROGN = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-TIME-PROGN", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_VERBATIM = ((Symbol*)(internRigidSymbolWrtModule("VERBATIM", NULL, 0)));
    SGT_CPP_TRANSLATE_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SYM_CPP_TRANSLATE_STELLA_SPECIAL = ((Symbol*)(internRigidSymbolWrtModule("SPECIAL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_UNWIND_PROTECT = ((Symbol*)(internRigidSymbolWrtModule("SYS-UNWIND-PROTECT", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_SIGNAL = ((Symbol*)(internRigidSymbolWrtModule("SYS-SIGNAL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_HANDLER_CASE = ((Symbol*)(internRigidSymbolWrtModule("SYS-HANDLER-CASE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_HANDLE_EXCEPTION = ((Symbol*)(internRigidSymbolWrtModule("SYS-HANDLE-EXCEPTION", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_VOID_SYS = ((Symbol*)(internRigidSymbolWrtModule("VOID-SYS", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_BAD_SYS = ((Symbol*)(internRigidSymbolWrtModule("BAD-SYS", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_TYPED_SYS = ((Symbol*)(internRigidSymbolWrtModule("TYPED-SYS", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_SET_DEFAULT = ((Symbol*)(internRigidSymbolWrtModule("SYS-SET-DEFAULT", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SYS-SLOT-VALUE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_REFERENCED_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SYS-REFERENCED-SLOT-VALUE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_SLOT_VALUE_SETTER = ((Symbol*)(internRigidSymbolWrtModule("SYS-SLOT-VALUE-SETTER", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_CALL_METHOD = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-METHOD", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_REFERENCED_CALL_METHOD = ((Symbol*)(internRigidSymbolWrtModule("SYS-REFERENCED-CALL-METHOD", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_CALL_SUPER_METHOD = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-SUPER-METHOD", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_CALL_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-FUNCTION", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("PROGN", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_WITH_PROCESS_LOCK = ((Symbol*)(internRigidSymbolWrtModule("WITH-PROCESS-LOCK", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_LOOP = ((Symbol*)(internRigidSymbolWrtModule("LOOP", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("SYS-FOREACH", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_LET = ((Symbol*)(internRigidSymbolWrtModule("LET", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CAST = ((Symbol*)(internRigidSymbolWrtModule("CAST", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SAFE_CAST = ((Symbol*)(internRigidSymbolWrtModule("SAFE-CAST", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_WHEN = ((Symbol*)(internRigidSymbolWrtModule("WHEN", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_UNLESS = ((Symbol*)(internRigidSymbolWrtModule("UNLESS", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_COND = ((Symbol*)(internRigidSymbolWrtModule("COND", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_MAKE = ((Symbol*)(internRigidSymbolWrtModule("MAKE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_NEW = ((Symbol*)(internRigidSymbolWrtModule("SYS-NEW", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_MV_SETQ = ((Symbol*)(internRigidSymbolWrtModule("MV-SETQ", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_CALL_FUNCTION_CODE = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-FUNCTION-CODE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_CALL_METHOD_CODE = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-METHOD-CODE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_INLINE_CALL = ((Symbol*)(internRigidSymbolWrtModule("SYS-INLINE-CALL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_THE_CODE = ((Symbol*)(internRigidSymbolWrtModule("THE-CODE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYS_POINTER_TO_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("SYS-POINTER-TO-FUNCTION", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_IGNORE = ((Symbol*)(internRigidSymbolWrtModule("IGNORE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_PRINT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("PRINT-STREAM", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_PRINT_NATIVE_STREAM = ((Symbol*)(internRigidSymbolWrtModule("PRINT-NATIVE-STREAM", NULL, 0)));
    KWD_CPP_TRANSLATE_CPP = ((Keyword*)(internRigidSymbolWrtModule("CPP", NULL, 2)));
    SYM_CPP_TRANSLATE_STELLA_CPP_VERBATIM = ((Symbol*)(internRigidSymbolWrtModule("CPP_VERBATIM", NULL, 0)));
    KWD_CPP_TRANSLATE_UNBIND_WITH_DESTRUCTORS = ((Keyword*)(internRigidSymbolWrtModule("UNBIND-WITH-DESTRUCTORS", NULL, 2)));
  }
}

void helpStartupCppTranslate3() {
  {
    SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL = ((Symbol*)(internRigidSymbolWrtModule("CPP_FUNCTION_CALL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_IDENT = ((Symbol*)(internRigidSymbolWrtModule("CPP_IDENT", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_ACTUALS = ((Symbol*)(internRigidSymbolWrtModule("CPP_ACTUALS", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_BLOCK = ((Symbol*)(internRigidSymbolWrtModule("CPP_BLOCK", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS = ((Symbol*)(internRigidSymbolWrtModule("CPP_STATEMENTS", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_COMMENT = ((Symbol*)(internRigidSymbolWrtModule("CPP_COMMENT", NULL, 0)));
    KWD_CPP_TRANSLATE_DIGIT = ((Keyword*)(internRigidSymbolWrtModule("DIGIT", NULL, 2)));
    SYM_CPP_TRANSLATE_STELLA_CPP_PRINT_NATIVE_STREAM = ((Symbol*)(internRigidSymbolWrtModule("CPP_PRINT_NATIVE_STREAM", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_DEFPRINT = ((Symbol*)(internRigidSymbolWrtModule("CPP_DEFPRINT", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_RETURN = ((Symbol*)(internRigidSymbolWrtModule("CPP_RETURN", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_STREAM = ((Symbol*)(internRigidSymbolWrtModule("STREAM", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_SIGNAL = ((Symbol*)(internRigidSymbolWrtModule("CPP_SIGNAL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_DEREFERENCE = ((Symbol*)(internRigidSymbolWrtModule("CPP_DEREFERENCE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_HANDLER_CASE = ((Symbol*)(internRigidSymbolWrtModule("CPP_HANDLER_CASE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_CATCH = ((Symbol*)(internRigidSymbolWrtModule("CPP_CATCH", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CPP_TYPE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_LOCAL = ((Symbol*)(internRigidSymbolWrtModule("CPP_LOCAL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_UNWIND_PROTECT = ((Symbol*)(internRigidSymbolWrtModule("CPP_UNWIND_PROTECT", NULL, 0)));
    SGT_CPP_TRANSLATE_STELLA_NUMBER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER", NULL, 1)));
    SGT_CPP_TRANSLATE_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", NULL, 1)));
    SYM_CPP_TRANSLATE_STELLA_CPP_CAST = ((Symbol*)(internRigidSymbolWrtModule("CPP_CAST", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_ASSIGN = ((Symbol*)(internRigidSymbolWrtModule("CPP_ASSIGN", NULL, 0)));
    KWD_CPP_TRANSLATE_UNBOUND_SPECIAL_VARIABLE = ((Keyword*)(internRigidSymbolWrtModule("UNBOUND-SPECIAL-VARIABLE", NULL, 2)));
    SYM_CPP_TRANSLATE_STELLA_CPP_SPECIAL = ((Symbol*)(internRigidSymbolWrtModule("CPP_SPECIAL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_GLOBAL = ((Symbol*)(internRigidSymbolWrtModule("CPP_GLOBAL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_SYMBOL_ID = ((Symbol*)(internRigidSymbolWrtModule("SYMBOL-ID", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_OTHERWISE = ((Symbol*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_CASE = ((Symbol*)(internRigidSymbolWrtModule("CPP_CASE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_PROGN = ((Symbol*)(internRigidSymbolWrtModule("CPP_PROGN", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_COND = ((Symbol*)(internRigidSymbolWrtModule("CPP_COND", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_BREAK = ((Symbol*)(internRigidSymbolWrtModule("CPP_BREAK", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_LOOP = ((Symbol*)(internRigidSymbolWrtModule("CPP_LOOP", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_GOTO_LABEL = ((Symbol*)(internRigidSymbolWrtModule("CPP_GOTO_LABEL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_WHILE = ((Symbol*)(internRigidSymbolWrtModule("CPP_WHILE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_WITH_PROCESS_LOCK = ((Symbol*)(internRigidSymbolWrtModule("CPP_WITH_PROCESS_LOCK", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_GOTO = ((Symbol*)(internRigidSymbolWrtModule("CPP_GOTO", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_CONTINUE = ((Symbol*)(internRigidSymbolWrtModule("CPP_CONTINUE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_IF = ((Symbol*)(internRigidSymbolWrtModule("CPP_IF", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_WHEN = ((Symbol*)(internRigidSymbolWrtModule("CPP_WHEN", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_UNLESS = ((Symbol*)(internRigidSymbolWrtModule("CPP_UNLESS", NULL, 0)));
    SGT_CPP_TRANSLATE_STELLA_ARGUMENT_LIST_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("ARGUMENT-LIST-ITERATOR", NULL, 1)));
    SYM_CPP_TRANSLATE_STELLA_CPP_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("CPP_FOREACH", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_VA_START = ((Symbol*)(internRigidSymbolWrtModule("VA_START", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_VA_END = ((Symbol*)(internRigidSymbolWrtModule("VA_END", NULL, 0)));
    SGT_CPP_TRANSLATE_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", NULL, 1)));
    SYM_CPP_TRANSLATE_STELLA_ALLOCATE_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("ALLOCATE-ITERATOR", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("LENGTH", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_NEXTp = ((Symbol*)(internRigidSymbolWrtModule("NEXT?", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_ARGUMENT = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENT", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_BINARY_OP = ((Symbol*)(internRigidSymbolWrtModule("CPP_BINARY_OP", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_UNARY_OP = ((Symbol*)(internRigidSymbolWrtModule("CPP_UNARY_OP", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_LITERAL = ((Symbol*)(internRigidSymbolWrtModule("CPP_LITERAL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_VA_ARG = ((Symbol*)(internRigidSymbolWrtModule("VA_ARG", NULL, 0)));
    KWD_CPP_TRANSLATE_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_POINTER = ((Symbol*)(internRigidSymbolWrtModule("CPP_FUNCTION_POINTER", NULL, 0)));
    KWD_CPP_TRANSLATE_METHOD = ((Keyword*)(internRigidSymbolWrtModule("METHOD", NULL, 2)));
    SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_POINTER = ((Symbol*)(internRigidSymbolWrtModule("CPP_METHOD_POINTER", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    SGT_CPP_TRANSLATE_STELLA_SHORT_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("SHORT-INTEGER", NULL, 1)));
    SGT_CPP_TRANSLATE_STELLA_LONG_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("LONG-INTEGER", NULL, 1)));
  }
}

void helpStartupCppTranslate4() {
  {
    SGT_CPP_TRANSLATE_STELLA_UNSIGNED_LONG_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("UNSIGNED-LONG-INTEGER", NULL, 1)));
    SGT_CPP_TRANSLATE_STELLA_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT", NULL, 1)));
    SGT_CPP_TRANSLATE_STELLA_SINGLE_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("SINGLE-FLOAT", NULL, 1)));
    SGT_CPP_TRANSLATE_STELLA_DOUBLE_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("DOUBLE-FLOAT", NULL, 1)));
    SGT_CPP_TRANSLATE_STELLA_CHARACTER = ((Surrogate*)(internRigidSymbolWrtModule("CHARACTER", NULL, 1)));
    SGT_CPP_TRANSLATE_STELLA_BYTE = ((Surrogate*)(internRigidSymbolWrtModule("BYTE", NULL, 1)));
    SGT_CPP_TRANSLATE_STELLA_OCTET = ((Surrogate*)(internRigidSymbolWrtModule("OCTET", NULL, 1)));
    SYM_CPP_TRANSLATE_STELLA_ANY_VALUE = ((Symbol*)(internRigidSymbolWrtModule("ANY-VALUE", NULL, 0)));
    SGT_CPP_TRANSLATE_STELLA_NATIVE_EXCEPTION = ((Surrogate*)(internRigidSymbolWrtModule("NATIVE-EXCEPTION", NULL, 1)));
    SYM_CPP_TRANSLATE_STELLA_CPP_ARRAY_REFERENCE = ((Symbol*)(internRigidSymbolWrtModule("CPP_ARRAY_REFERENCE", NULL, 0)));
    SGT_CPP_TRANSLATE_STELLA_VOID = ((Surrogate*)(internRigidSymbolWrtModule("VOID", NULL, 1)));
    SYM_CPP_TRANSLATE_STELLA_CPP_REFERENCED_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("CPP_REFERENCED_SLOT_VALUE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("CPP_SLOT_VALUE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_SLOT_VALUE_SETTER = ((Symbol*)(internRigidSymbolWrtModule("CPP_SLOT_VALUE_SETTER", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CLASS_CPP_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CPP-NATIVE-TYPE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_MAKE = ((Symbol*)(internRigidSymbolWrtModule("CPP_MAKE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_STARTUP_TIME_PROGN = ((Symbol*)(internRigidSymbolWrtModule("CPP_STARTUP_TIME_PROGN", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_PRINT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("CPP_PRINT_STREAM", NULL, 0)));
    KWD_CPP_TRANSLATE_WARN = ((Keyword*)(internRigidSymbolWrtModule("WARN", NULL, 2)));
    KWD_CPP_TRANSLATE_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    KWD_CPP_TRANSLATE_CONTINUABLE_ERROR = ((Keyword*)(internRigidSymbolWrtModule("CONTINUABLE-ERROR", NULL, 2)));
    SYM_CPP_TRANSLATE_STELLA_CPP_STANDARD_ERROR = ((Symbol*)(internRigidSymbolWrtModule("CPP_STANDARD_ERROR", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_STANDARD_OUT = ((Symbol*)(internRigidSymbolWrtModule("CPP_STANDARD_OUT", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_EOL = ((Symbol*)(internRigidSymbolWrtModule("EOL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_SYMBOL = ((Symbol*)(internRigidSymbolWrtModule("CPP_SYMBOL", NULL, 0)));
    KWD_CPP_TRANSLATE_CPP_STANDALONE = ((Keyword*)(internRigidSymbolWrtModule("CPP-STANDALONE", NULL, 2)));
    SGT_CPP_TRANSLATE_STELLA_UNKNOWN = ((Surrogate*)(internRigidSymbolWrtModule("UNKNOWN", NULL, 1)));
    KWD_CPP_TRANSLATE_UPPERCASE = ((Keyword*)(internRigidSymbolWrtModule("UPPERCASE", NULL, 2)));
    KWD_CPP_TRANSLATE_LOWERCASE = ((Keyword*)(internRigidSymbolWrtModule("LOWERCASE", NULL, 2)));
    KWD_CPP_TRANSLATE_CAPITALIZED = ((Keyword*)(internRigidSymbolWrtModule("CAPITALIZED", NULL, 2)));
    SGT_CPP_TRANSLATE_STELLA_F_CPP_CHANGE_CASE_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-CPP-CHANGE-CASE-MEMO-TABLE-000", NULL, 1)));
    KWD_CPP_TRANSLATE_CLEVER = ((Keyword*)(internRigidSymbolWrtModule("CLEVER", NULL, 2)));
    KWD_CPP_TRANSLATE_YES = ((Keyword*)(internRigidSymbolWrtModule("YES", NULL, 2)));
    KWD_CPP_TRANSLATE_NO = ((Keyword*)(internRigidSymbolWrtModule("NO", NULL, 2)));
    KWD_CPP_TRANSLATE_PRESERVE = ((Keyword*)(internRigidSymbolWrtModule("PRESERVE", NULL, 2)));
    KWD_CPP_TRANSLATE_UPCASE = ((Keyword*)(internRigidSymbolWrtModule("UPCASE", NULL, 2)));
    KWD_CPP_TRANSLATE_TITLECASEX = ((Keyword*)(internRigidSymbolWrtModule("TITLECASEX", NULL, 2)));
    KWD_CPP_TRANSLATE_TITLECASE = ((Keyword*)(internRigidSymbolWrtModule("TITLECASE", NULL, 2)));
    SYM_CPP_TRANSLATE_STELLA_MODULE_CPP_PACKAGE = ((Symbol*)(internRigidSymbolWrtModule("MODULE-CPP-PACKAGE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    KWD_CPP_TRANSLATE_FULL = ((Keyword*)(internRigidSymbolWrtModule("FULL", NULL, 2)));
    KWD_CPP_TRANSLATE_NEVER = ((Keyword*)(internRigidSymbolWrtModule("NEVER", NULL, 2)));
    SYM_CPP_TRANSLATE_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-VARIABLE-ARGUMENTS?", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA__RETURN = ((Symbol*)(internRigidSymbolWrtModule("_RETURN", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_VAR_ARGS = ((Symbol*)(internRigidSymbolWrtModule("CPP_VAR_ARGS", NULL, 0)));
    SGT_CPP_TRANSLATE_STELLA_STORAGE_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("STORAGE-SLOT", NULL, 1)));
    SYM_CPP_TRANSLATE_STELLA_METHOD_NATIVEp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-NATIVE?", NULL, 0)));
    SGT_CPP_TRANSLATE_STELLA_LITERAL = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL", NULL, 1)));
    SYM_CPP_TRANSLATE_STELLA_THIS = ((Symbol*)(internRigidSymbolWrtModule("THIS", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("CPP_FUNCTION", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_METHOD = ((Symbol*)(internRigidSymbolWrtModule("CPP_METHOD", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_EXTERN_C = ((Symbol*)(internRigidSymbolWrtModule("CPP_EXTERN_C", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_SETTER_CALL = ((Symbol*)(internRigidSymbolWrtModule("CPP_METHOD_SETTER_CALL", NULL, 0)));
    SGT_CPP_TRANSLATE_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
    SYM_CPP_TRANSLATE_STELLA_DEFINEDp = ((Symbol*)(internRigidSymbolWrtModule("DEFINED?", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_NULLp = ((Symbol*)(internRigidSymbolWrtModule("NULL?", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_NTH = ((Symbol*)(internRigidSymbolWrtModule("NTH", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_NTH_SETTER = ((Symbol*)(internRigidSymbolWrtModule("NTH-SETTER", NULL, 0)));
  }
}

void helpStartupCppTranslate5() {
  {
    SYM_CPP_TRANSLATE_STELLA_AREF = ((Symbol*)(internRigidSymbolWrtModule("AREF", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_AREF_SETTER = ((Symbol*)(internRigidSymbolWrtModule("AREF-SETTER", NULL, 0)));
    SGT_CPP_TRANSLATE_STELLA_ARGUMENT_LIST = ((Surrogate*)(internRigidSymbolWrtModule("ARGUMENT-LIST", NULL, 1)));
    SYM_CPP_TRANSLATE_STELLA_CPP_REFERENCED_METHOD_CALL = ((Symbol*)(internRigidSymbolWrtModule("CPP_REFERENCED_METHOD_CALL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_CALL = ((Symbol*)(internRigidSymbolWrtModule("CPP_METHOD_CALL", NULL, 0)));
    SGT_CPP_TRANSLATE_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 1)));
    SGT_CPP_TRANSLATE_STELLA_STRING = ((Surrogate*)(internRigidSymbolWrtModule("STRING", NULL, 1)));
    SGT_CPP_TRANSLATE_STELLA_MUTABLE_STRING = ((Surrogate*)(internRigidSymbolWrtModule("MUTABLE-STRING", NULL, 1)));
    SGT_CPP_TRANSLATE_STELLA_NATIVE_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("NATIVE-VECTOR", NULL, 1)));
    SGT_CPP_TRANSLATE_STELLA_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("ARRAY", NULL, 1)));
    SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_SIGNATURE = ((Symbol*)(internRigidSymbolWrtModule("CPP_FUNCTION_SIGNATURE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_SIGNATURE = ((Symbol*)(internRigidSymbolWrtModule("CPP_METHOD_SIGNATURE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_FUNCALL = ((Symbol*)(internRigidSymbolWrtModule("CPP_FUNCALL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_CODE_CALL = ((Symbol*)(internRigidSymbolWrtModule("CPP_METHOD_CODE_CALL", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_DUMMY = ((Symbol*)(internRigidSymbolWrtModule("DUMMY", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_GET_SYM = ((Symbol*)(internRigidSymbolWrtModule("GET-SYM", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_GET_KWD = ((Symbol*)(internRigidSymbolWrtModule("GET-KWD", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_GET_SGT = ((Symbol*)(internRigidSymbolWrtModule("GET-SGT", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_CPP_TERNARY_OP = ((Symbol*)(internRigidSymbolWrtModule("CPP_TERNARY_OP", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_STARTUP_CPP_TRANSLATE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-CPP-TRANSLATE", NULL, 0)));
    SYM_CPP_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupCppTranslate6() {
  {
    oCPP_TRUE_STRING_WRAPPERo = wrapString("TRUE");
    oCPP_FALSE_STRING_WRAPPERo = wrapString("FALSE");
    oCURRENTDUMMYINDEXo = NULL_INTEGER;
    oCPP_OPERATOR_TABLEo = ((KeyValueList*)(dictionary(SGT_CPP_TRANSLATE_STELLA_KEY_VALUE_LIST, 36, SYM_CPP_TRANSLATE_STELLA_ii, cons(wrapString("++"), NIL), SYM_CPP_TRANSLATE_STELLA___, cons(wrapString("--"), NIL), SYM_CPP_TRANSLATE_STELLA_i, cons(wrapString("+"), NIL), SYM_CPP_TRANSLATE_STELLA__, cons(wrapString("-"), NIL), SYM_CPP_TRANSLATE_STELLA_o, cons(wrapString("*"), NIL), SYM_CPP_TRANSLATE_STELLA_s, cons(wrapString("/"), NIL), SYM_CPP_TRANSLATE_STELLA_EQp, cons(wrapString("=="), NIL), SYM_CPP_TRANSLATE_STELLA_xe, cons(wrapString("!="), NIL), SYM_CPP_TRANSLATE_STELLA_g, cons(wrapString(">"), NIL), SYM_CPP_TRANSLATE_STELLA_ge, cons(wrapString(">="), NIL), SYM_CPP_TRANSLATE_STELLA_eg, cons(wrapString(">="), NIL), SYM_CPP_TRANSLATE_STELLA_l, cons(wrapString("<"), NIL), SYM_CPP_TRANSLATE_STELLA_el, cons(wrapString("<="), NIL), SYM_CPP_TRANSLATE_STELLA_le, cons(wrapString("<="), NIL), SYM_CPP_TRANSLATE_STELLA_AND, cons(wrapString("&&"), NIL), SYM_CPP_TRANSLATE_STELLA_OR, cons(wrapString("||"), NIL), SYM_CPP_TRANSLATE_STELLA_NOT, cons(wrapString("!"), NIL), SYM_CPP_TRANSLATE_STELLA_CHOOSE, cons(wrapString("?"), cons(wrapString(":"), NIL)))));
    oCPP_RESERVED_WORD_TABLEo = cppCreateReservedWordTable();
    oCPPLOOPEXITo = SYM_CPP_TRANSLATE_STELLA_CPP_BREAK;
    oCPP_CHARACTER_SUBSTITUTION_TABLEo = cppCreateCharacterSubstitutionTable();
    oCPP_NAME_QUALIFICATION_MODEo = KWD_CPP_TRANSLATE_CLEVER;
  }
}

void helpStartupCppTranslate7() {
  {
    defineFunctionObject("OVERLOADED-FUNCTION-NAME-MODULE", "(DEFUN (OVERLOADED-FUNCTION-NAME-MODULE MODULE) ((FUNCTION-NAME SYMBOL) (CLASS-TYPE TYPE)))", ((cpp_function_code)(&overloadedFunctionNameModule)), NULL);
    defineFunctionObject("CPP-USE-GARBAGE-COLLECTOR?", "(DEFUN (CPP-USE-GARBAGE-COLLECTOR? BOOLEAN) ())", ((cpp_function_code)(&cppUseGarbageCollectorP)), NULL);
    defineFunctionObject("CPP-LOOKUP-OPERATOR-TABLE", "(DEFUN (CPP-LOOKUP-OPERATOR-TABLE CONS) ((OPERATOR SYMBOL)))", ((cpp_function_code)(&cppLookupOperatorTable)), NULL);
    defineFunctionObject("CPP-YIELD-RENAMED-RESERVED-WORD", "(DEFUN (CPP-YIELD-RENAMED-RESERVED-WORD STRING-WRAPPER) ((WORD SYMBOL)))", ((cpp_function_code)(&cppYieldRenamedReservedWord)), NULL);
    defineFunctionObject("CPP-CREATE-RESERVED-WORD-TABLE", "(DEFUN (CPP-CREATE-RESERVED-WORD-TABLE STRING-HASH-TABLE) ())", ((cpp_function_code)(&cppCreateReservedWordTable)), NULL);
    defineFunctionObject("CPP-LOOKUP-RESERVED-WORD-TABLE", "(DEFUN (CPP-LOOKUP-RESERVED-WORD-TABLE STRING-WRAPPER) ((WORD SYMBOL)))", ((cpp_function_code)(&cppLookupReservedWordTable)), NULL);
    defineFunctionObject("CPP-TRANSLATE-UNIT", "(DEFUN (CPP-TRANSLATE-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&cppTranslateUnit)), NULL);
    defineFunctionObject("CPP-TRANSLATE-LIST-OF-TREES", "(DEFUN (CPP-TRANSLATE-LIST-OF-TREES CONS) ((TREES CONS)))", ((cpp_function_code)(&cppTranslateListOfTrees)), NULL);
    defineFunctionObject("CPP-TRANSLATE-A-TREE", "(DEFUN (CPP-TRANSLATE-A-TREE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&cppTranslateATree)), NULL);
    defineFunctionObject("CPP-TRANSLATE-VERBATIM-TREE", "(DEFUN (CPP-TRANSLATE-VERBATIM-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateVerbatimTree)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SPECIAL-TREE", "(DEFUN (CPP-TRANSLATE-SPECIAL-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateSpecialTree)), NULL);
    defineFunctionObject("CPP-TRANSLATE-INLINE-TREE", "(DEFUN (CPP-TRANSLATE-INLINE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateInlineTree)), NULL);
    defineFunctionObject("TOKENIZE-VERBATIM-METHOD-BODY", "(DEFUN (TOKENIZE-VERBATIM-METHOD-BODY CONS) ((TREE CONS)))", ((cpp_function_code)(&tokenizeVerbatimMethodBody)), NULL);
    defineFunctionObject("CPP-TRANSLATE-INLINE-CALL-TREE", "(DEFUN (CPP-TRANSLATE-INLINE-CALL-TREE OBJECT) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateInlineCallTree)), NULL);
    defineFunctionObject("CPP-TRANSLATE-PRINT-NATIVE-STREAM", "(DEFUN (CPP-TRANSLATE-PRINT-NATIVE-STREAM CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslatePrintNativeStream)), NULL);
    defineFunctionObject("CPP-TRANSLATE-DEFPRINT-UNIT", "(DEFUN (CPP-TRANSLATE-DEFPRINT-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&cppTranslateDefprintUnit)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SIGNAL", "(DEFUN (CPP-TRANSLATE-SIGNAL CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateSignal)), NULL);
    defineFunctionObject("CPP-TRANSLATE-HANDLER-CASE", "(DEFUN (CPP-TRANSLATE-HANDLER-CASE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateHandlerCase)), NULL);
    defineFunctionObject("CPP-TRANSLATE-HANDLE-EXCEPTION", "(DEFUN (CPP-TRANSLATE-HANDLE-EXCEPTION CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateHandleException)), NULL);
    defineFunctionObject("CPP-TRANSLATE-UNWIND-PROTECT", "(DEFUN (CPP-TRANSLATE-UNWIND-PROTECT CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateUnwindProtect)), NULL);
    defineFunctionObject("CPP-TRANSLATE-CAST", "(DEFUN (CPP-TRANSLATE-CAST CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateCast)), NULL);
    defineFunctionObject("CPP-TRANSLATE-MV-SETQ", "(DEFUN (CPP-TRANSLATE-MV-SETQ CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateMvSetq)), NULL);
    defineFunctionObject("CPP-TRANSLATE-MV-FUNCTION-CALL", "(DEFUN (CPP-TRANSLATE-MV-FUNCTION-CALL CONS) ((FUNCTIONCALL CONS) (VARIABLES CONS)))", ((cpp_function_code)(&cppTranslateMvFunctionCall)), NULL);
    defineFunctionObject("CPP-TRANSLATE-DEFINE-GLOBAL-VARIABLE-UNIT", "(DEFUN (CPP-TRANSLATE-DEFINE-GLOBAL-VARIABLE-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&cppTranslateDefineGlobalVariableUnit)), NULL);
    defineFunctionObject("CPP-TRANSLATE-GLOBAL-VARIABLE-NAME", "(DEFUN (CPP-TRANSLATE-GLOBAL-VARIABLE-NAME STRING-WRAPPER) ((GLOBAL GLOBAL-VARIABLE)))", ((cpp_function_code)(&cppTranslateGlobalVariableName)), NULL);
    defineFunctionObject("CPP-TRANSLATE-GLOBAL-VARIABLE-ADDRESS", "(DEFUN (CPP-TRANSLATE-GLOBAL-VARIABLE-ADDRESS STRING-WRAPPER) ((GLOBAL GLOBAL-VARIABLE)))", ((cpp_function_code)(&cppTranslateGlobalVariableAddress)), NULL);
    defineFunctionObject("SYMBOL-CASE?", "(DEFUN (SYMBOL-CASE? BOOLEAN) ((KEYFORM OBJECT)))", ((cpp_function_code)(&symbolCaseP)), NULL);
    defineFunctionObject("CPP-YIELD-SYMBOL-ID-FORM", "(DEFUN (CPP-YIELD-SYMBOL-ID-FORM CONS) ((SYMBOLID INTEGER)))", ((cpp_function_code)(&cppYieldSymbolIdForm)), NULL);
    defineFunctionObject("CPP-TRANSLATE-CONDITION", "(DEFUN (CPP-TRANSLATE-CONDITION CONS) ((CONDITION CONS) (SYMBOLCASEP BOOLEAN)))", ((cpp_function_code)(&cppTranslateCondition)), NULL);
    defineFunctionObject("CPP-TRANSLATE-CASE-TREE", "(DEFUN (CPP-TRANSLATE-CASE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateCaseTree)), NULL);
    defineFunctionObject("CPP-TRANSLATE-COND-TREE", "(DEFUN (CPP-TRANSLATE-COND-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateCondTree)), NULL);
    defineFunctionObject("CPP-TRANSLATE-LOOP", "(DEFUN (CPP-TRANSLATE-LOOP CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateLoop)), NULL);
    defineFunctionObject("CPP-TRANSLATE-WHILE", "(DEFUN (CPP-TRANSLATE-WHILE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateWhile)), NULL);
    defineFunctionObject("CPP-TRANSLATE-PROGN", "(DEFUN (CPP-TRANSLATE-PROGN CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateProgn)), NULL);
    defineFunctionObject("CPP-TRANSLATE-WITH-PROCESS-LOCK", "(DEFUN (CPP-TRANSLATE-WITH-PROCESS-LOCK CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateWithProcessLock)), NULL);
    defineFunctionObject("CPP-TRANSLATE-BREAK", "(DEFUN (CPP-TRANSLATE-BREAK CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateBreak)), NULL);
    defineFunctionObject("CPP-TRANSLATE-CONTINUE", "(DEFUN (CPP-TRANSLATE-CONTINUE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateContinue)), NULL);
    defineFunctionObject("CPP-TRANSLATE-IF-TREE", "(DEFUN (CPP-TRANSLATE-IF-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateIfTree)), NULL);
    defineFunctionObject("CPP-TRANSLATE-CHOOSE-TREE", "(DEFUN (CPP-TRANSLATE-CHOOSE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateChooseTree)), NULL);
    defineFunctionObject("CPP-TRANSLATE-WHEN-TREE", "(DEFUN (CPP-TRANSLATE-WHEN-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateWhenTree)), NULL);
    defineFunctionObject("CPP-TRANSLATE-UNLESS-TREE", "(DEFUN (CPP-TRANSLATE-UNLESS-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateUnlessTree)), NULL);
    defineFunctionObject("CPP-TRANSLATE-FOREACH-TREE", "(DEFUN (CPP-TRANSLATE-FOREACH-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateForeachTree)), NULL);
    defineFunctionObject("CPP-YIELD-VA-START-TREE", "(DEFUN (CPP-YIELD-VA-START-TREE CONS) ((ITERATORVAR SYMBOL)))", ((cpp_function_code)(&cppYieldVaStartTree)), NULL);
    defineFunctionObject("CPP-YIELD-VA-END-TREE", "(DEFUN (CPP-YIELD-VA-END-TREE CONS) ((ITERATORVAR SYMBOL)))", ((cpp_function_code)(&cppYieldVaEndTree)), NULL);
    defineFunctionObject("CPP-YIELD-VA-ITERATOR-HELPER-VARIABLE", "(DEFUN (CPP-YIELD-VA-ITERATOR-HELPER-VARIABLE SYMBOL) ((ITERATORVAR SYMBOL)))", ((cpp_function_code)(&cppYieldVaIteratorHelperVariable)), NULL);
    defineFunctionObject("CPP-YIELD-VA-ITERATOR-DECLARATIONS", "(DEFUN (CPP-YIELD-VA-ITERATOR-DECLARATIONS CONS) ((ITERATORVAR SYMBOL)))", ((cpp_function_code)(&cppYieldVaIteratorDeclarations)), NULL);
    defineFunctionObject("CPP-TRANSLATE-ARGUMENT-LIST-TREE", "(DEFUN (CPP-TRANSLATE-ARGUMENT-LIST-TREE CONS) ((OPERATOR SYMBOL) (OWNER TYPE) (ARGUMENT OBJECT)))", ((cpp_function_code)(&cppTranslateArgumentListTree)), NULL);
    defineFunctionObject("CPP-TRANSLATE-THE-CODE", "(DEFUN (CPP-TRANSLATE-THE-CODE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateTheCode)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SYS-POINTER-TO-FUNCTION", "(DEFUN (CPP-TRANSLATE-SYS-POINTER-TO-FUNCTION CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateSysPointerToFunction)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SYS-NEW", "(DEFUN (CPP-TRANSLATE-SYS-NEW CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateSysNew)), NULL);
    defineFunctionObject("CPP-NON-POINTER-TYPE?", "(DEFUN (CPP-NON-POINTER-TYPE? BOOLEAN) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&cppNonPointerTypeP)), NULL);
    defineFunctionObject("CPP-TYPE-WITHOUT-INTERIOR-POINTERS?", "(DEFUN (CPP-TYPE-WITHOUT-INTERIOR-POINTERS? BOOLEAN) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&cppTypeWithoutInteriorPointersP)), NULL);
    defineFunctionObject("CPP-TRANSLATE-NEW-ARRAY", "(DEFUN (CPP-TRANSLATE-NEW-ARRAY CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateNewArray)), NULL);
    defineFunctionObject("CPP-TRANSLATE-VOID-SYS", "(DEFUN (CPP-TRANSLATE-VOID-SYS CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateVoidSys)), NULL);
    defineFunctionObject("CPP-TRANSLATE-TYPED-SYS", "(DEFUN (CPP-TRANSLATE-TYPED-SYS CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateTypedSys)), NULL);
    defineFunctionObject("CPP-TRANSLATE-BAD-SYS", "(DEFUN (CPP-TRANSLATE-BAD-SYS OBJECT) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateBadSys)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SYS-REFERENCED-SLOT-VALUE", "(DEFUN (CPP-TRANSLATE-SYS-REFERENCED-SLOT-VALUE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateSysReferencedSlotValue)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SYS-SLOT-VALUE", "(DEFUN (CPP-TRANSLATE-SYS-SLOT-VALUE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateSysSlotValue)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SYS-SLOT-VALUE-SETTER", "(DEFUN (CPP-TRANSLATE-SYS-SLOT-VALUE-SETTER CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateSysSlotValueSetter)), NULL);
    defineFunctionObject("CPP-TRANSLATE-MAKE-TREE", "(DEFUN (CPP-TRANSLATE-MAKE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateMakeTree)), NULL);
  }
}

void helpStartupCppTranslate8() {
  {
    defineFunctionObject("CPP-TRANSLATE-STARTUP-TIME-PROGN", "(DEFUN (CPP-TRANSLATE-STARTUP-TIME-PROGN CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateStartupTimeProgn)), NULL);
    defineFunctionObject("CPP-STREAM-IS-STANDARD-OUTPUT?", "(DEFUN (CPP-STREAM-IS-STANDARD-OUTPUT? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&cppStreamIsStandardOutputP)), NULL);
    defineFunctionObject("CPP-TRANSLATE-PRINT-STREAM", "(DEFUN (CPP-TRANSLATE-PRINT-STREAM CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslatePrintStream)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SETQ-TREE", "(DEFUN (CPP-TRANSLATE-SETQ-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateSetqTree)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SYS-SET-DEFAULT", "(DEFUN (CPP-TRANSLATE-SYS-SET-DEFAULT OBJECT) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateSysSetDefault)), NULL);
    defineFunctionObject("CPP-TRANSLATE-NULL", "(DEFUN (CPP-TRANSLATE-NULL CONS) ())", ((cpp_function_code)(&cppTranslateNull)), NULL);
    defineMethodObject("(DEFMETHOD (CPP-TRANSLATE-ATOMIC-TREE CONS) ((TREE OBJECT)))", wrapMethodCode(((cpp_method_code)(&Object::cppTranslateAtomicTree))), NULL);
    defineMethodObject("(DEFMETHOD (CPP-TRANSLATE-ATOMIC-TREE CONS) ((TREE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&Keyword::cppTranslateAtomicTree))), NULL);
    defineMethodObject("(DEFMETHOD (CPP-TRANSLATE-ATOMIC-TREE CONS) ((TREE SURROGATE)))", wrapMethodCode(((cpp_method_code)(&Surrogate::cppTranslateAtomicTree))), NULL);
    defineMethodObject("(DEFMETHOD (CPP-TRANSLATE-ATOMIC-TREE CONS) ((TREE SYMBOL)))", wrapMethodCode(((cpp_method_code)(&Symbol::cppTranslateAtomicTree))), NULL);
    defineMethodObject("(DEFMETHOD (CPP-TRANSLATE-ATOMIC-TREE CONS) ((TREE QUOTED-EXPRESSION)))", wrapMethodCode(((cpp_method_code)(&QuotedExpression::cppTranslateAtomicTree))), NULL);
    defineFunctionObject("CPP-TRANSLATE-LET-TREE", "(DEFUN (CPP-TRANSLATE-LET-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateLetTree)), NULL);
    defineFunctionObject("CPP-TRANSLATE-TYPE-SPEC", "(DEFUN (CPP-TRANSLATE-TYPE-SPEC STRING-WRAPPER) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&cppTranslateTypeSpec)), NULL);
    defineFunctionObject("CPP-TRANSLATE-AND-POINTERIZE-TYPE-SPEC", "(DEFUN (CPP-TRANSLATE-AND-POINTERIZE-TYPE-SPEC STRING-WRAPPER) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&cppTranslateAndPointerizeTypeSpec)), NULL);
    defineFunctionObject("CPP-TRANSLATE-AND-REFERENCIZE-TYPE-SPEC", "(DEFUN (CPP-TRANSLATE-AND-REFERENCIZE-TYPE-SPEC STRING-WRAPPER) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&cppTranslateAndReferencizeTypeSpec)), NULL);
    defineFunctionObject("CPP-TRANSLATE-ARRAY-TYPE", "(DEFUN (CPP-TRANSLATE-ARRAY-TYPE STRING-WRAPPER) ((ARRAYTYPE PARAMETRIC-TYPE-SPECIFIER)))", ((cpp_function_code)(&cppTranslateArrayType)), NULL);
    defineFunctionObject("CPP-TRANSLATED-ARRAY-TYPE?", "(DEFUN (CPP-TRANSLATED-ARRAY-TYPE? BOOLEAN) ((TRANSLATEDTYPE OBJECT)))", ((cpp_function_code)(&cppTranslatedArrayTypeP)), NULL);
    defineFunctionObject("CPP-GENERATE-ARRAY-TYPED-ENTITY", "(DEFUN (CPP-GENERATE-ARRAY-TYPED-ENTITY STRING) ((ENTITY STRING) (TRANSLATEDARRAYTYPE STRING)))", ((cpp_function_code)(&cppGenerateArrayTypedEntity)), NULL);
    defineFunctionObject("CPP-NATIVE-POINTER-TYPE?", "(DEFUN (CPP-NATIVE-POINTER-TYPE? BOOLEAN) ((NATIVETYPE STRING)))", ((cpp_function_code)(&cppNativePointerTypeP)), NULL);
    defineFunctionObject("CPP-UNPOINTERIZE-NATIVE-TYPE", "(DEFUN (CPP-UNPOINTERIZE-NATIVE-TYPE STRING) ((NATIVETYPE STRING)))", ((cpp_function_code)(&cppUnpointerizeNativeType)), NULL);
    defineFunctionObject("CPP-CREATE-CHARACTER-SUBSTITUTION-TABLE", "(DEFUN (CPP-CREATE-CHARACTER-SUBSTITUTION-TABLE STRING) ())", ((cpp_function_code)(&cppCreateCharacterSubstitutionTable)), NULL);
    defineFunctionObject("REPLACE-FIRST-CHARACTER-WITH-STRING", "(DEFUN (REPLACE-FIRST-CHARACTER-WITH-STRING STRING) ((STRING STRING) (NEWPREFIX STRING)))", ((cpp_function_code)(&replaceFirstCharacterWithString)), NULL);
    defineFunctionObject("CPP-SUBSTITUTE-FORBIDDEN-CHARACTERS", "(DEFUN (CPP-SUBSTITUTE-FORBIDDEN-CHARACTERS STRING) ((NAME STRING) (CASECONVENTION KEYWORD)))", ((cpp_function_code)(&cppSubstituteForbiddenCharacters)), NULL);
    defineFunctionObject("CPP-CHANGE-CASE", "(DEFUN (CPP-CHANGE-CASE STRING) ((SYMBOL GENERALIZED-SYMBOL) (CASECONVENTION KEYWORD)))", ((cpp_function_code)(&cppChangeCase)), NULL);
    defineFunctionObject("HELP-CPP-CHANGE-CASE", "(DEFUN (HELP-CPP-CHANGE-CASE STRING) ((SYMBOL GENERALIZED-SYMBOL) (CASECONVENTION KEYWORD)))", ((cpp_function_code)(&helpCppChangeCase)), NULL);
    defineFunctionObject("CPP-YIELD-NAMESPACE-PREFIX-FROM-MODULE", "(DEFUN (CPP-YIELD-NAMESPACE-PREFIX-FROM-MODULE STRING) ((MODULE MODULE)))", ((cpp_function_code)(&cppYieldNamespacePrefixFromModule)), NULL);
    defineFunctionObject("CPP-YIELD-NAMESPACE-PREFIX", "(DEFUN (CPP-YIELD-NAMESPACE-PREFIX STRING) ((SYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&cppYieldNamespacePrefix)), NULL);
    defineFunctionObject("CPP-NAME-QUALIFICATION-MODE", "(DEFUN (CPP-NAME-QUALIFICATION-MODE KEYWORD) () :GLOBALLY-INLINE? TRUE (RETURN *CPP-NAME-QUALIFICATION-MODE*))", ((cpp_function_code)(&cppNameQualificationMode)), NULL);
    defineFunctionObject("CPP-QUALIFY-NAME?", "(DEFUN (CPP-QUALIFY-NAME? BOOLEAN) ((NAMESYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&cppQualifyNameP)), NULL);
    defineFunctionObject("CPP-YIELD-QUALIFIED-NAME", "(DEFUN (CPP-YIELD-QUALIFIED-NAME STRING) ((TRANSLATEDNAME STRING) (SOURCESYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&cppYieldQualifiedName)), NULL);
    defineFunctionObject("CPP-FIXUP-NAME-SYMBOL", "(DEFUN (CPP-FIXUP-NAME-SYMBOL SYMBOL) ((NAMESYMBOL SYMBOL) (HOMEMODULE MODULE)))", ((cpp_function_code)(&cppFixupNameSymbol)), NULL);
    defineFunctionObject("CPP-TRANSLATE-NAME", "(DEFUN (CPP-TRANSLATE-NAME STRING-WRAPPER) ((NAMESYMBOL SYMBOL)))", ((cpp_function_code)(&cppTranslateName)), NULL);
    defineFunctionObject("CPP-TRANSLATE-GLOBAL-NAME", "(DEFUN (CPP-TRANSLATE-GLOBAL-NAME STRING-WRAPPER) ((NAMESYMBOL SYMBOL)))", ((cpp_function_code)(&cppTranslateGlobalName)), NULL);
    defineFunctionObject("CPP-TRANSLATE-CLASS-PARAMETER-NAME", "(DEFUN (CPP-TRANSLATE-CLASS-PARAMETER-NAME STRING-WRAPPER) ((NAMESYMBOL SYMBOL)))", ((cpp_function_code)(&cppTranslateClassParameterName)), NULL);
    defineFunctionObject("CPP-TRANSLATE-RETURN-PARAMETER-NAME", "(DEFUN (CPP-TRANSLATE-RETURN-PARAMETER-NAME STRING-WRAPPER) ((NAMESYMBOL SYMBOL) (PARAMETERNUMBER INTEGER)))", ((cpp_function_code)(&cppTranslateReturnParameterName)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SYMBOL-CONSTANT-NAME", "(DEFUN (CPP-TRANSLATE-SYMBOL-CONSTANT-NAME STRING-WRAPPER) ((SYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&cppTranslateSymbolConstantName)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SYMBOL-CONSTANT-ID", "(DEFUN (CPP-TRANSLATE-SYMBOL-CONSTANT-ID STRING-WRAPPER) ((SYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&cppTranslateSymbolConstantId)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SYMBOL-NAME", "(DEFUN (CPP-TRANSLATE-SYMBOL-NAME STRING-WRAPPER) ((SYMBOL SYMBOL)))", ((cpp_function_code)(&cppTranslateSymbolName)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SYMBOL-ID", "(DEFUN (CPP-TRANSLATE-SYMBOL-ID STRING-WRAPPER) ((SYMBOL SYMBOL)))", ((cpp_function_code)(&cppTranslateSymbolId)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SURROGATE-NAME", "(DEFUN (CPP-TRANSLATE-SURROGATE-NAME STRING-WRAPPER) ((SURROGATE SURROGATE)))", ((cpp_function_code)(&cppTranslateSurrogateName)), NULL);
    defineFunctionObject("CPP-TRANSLATE-SURROGATE-ID", "(DEFUN (CPP-TRANSLATE-SURROGATE-ID STRING-WRAPPER) ((SURROGATE SURROGATE)))", ((cpp_function_code)(&cppTranslateSurrogateId)), NULL);
    defineFunctionObject("CPP-TRANSLATE-KEYWORD-NAME", "(DEFUN (CPP-TRANSLATE-KEYWORD-NAME STRING-WRAPPER) ((KEYWORD KEYWORD)))", ((cpp_function_code)(&cppTranslateKeywordName)), NULL);
    defineFunctionObject("CPP-TRANSLATE-KEYWORD-ID", "(DEFUN (CPP-TRANSLATE-KEYWORD-ID STRING-WRAPPER) ((KEYWORD KEYWORD)))", ((cpp_function_code)(&cppTranslateKeywordId)), NULL);
    defineFunctionObject("CPP-TRANSLATE-CLASS-TYPENAME", "(DEFUN (CPP-TRANSLATE-CLASS-TYPENAME STRING-WRAPPER) ((NAMESYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&cppTranslateClassTypename)), NULL);
    defineFunctionObject("CPP-TRANSLATE-CLASS-NAME", "(DEFUN (CPP-TRANSLATE-CLASS-NAME STRING-WRAPPER) ((NAMESYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&cppTranslateClassName)), NULL);
    defineFunctionObject("CPP-REFERENCE-TYPE?", "(DEFUN (CPP-REFERENCE-TYPE? BOOLEAN) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&cppReferenceTypeP)), NULL);
    defineFunctionObject("CPP-REFERENCIZE-TYPE", "(DEFUN (CPP-REFERENCIZE-TYPE STRING-WRAPPER) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&cppReferencizeType)), NULL);
    defineFunctionObject("CPP-TRANSLATE-FUNCTION-PARAMETER", "(DEFUN (CPP-TRANSLATE-FUNCTION-PARAMETER OBJECT) ((NAME SYMBOL) (TYPE TYPE-SPEC) (METHOD METHOD-SLOT)))", ((cpp_function_code)(&cppTranslateFunctionParameter)), NULL);
    defineFunctionObject("CPP-TRANSLATE-RETURN-PARAMETER", "(DEFUN (CPP-TRANSLATE-RETURN-PARAMETER CONS) ((PARAMETERNUMBER INTEGER) (PARAMETERTYPE TYPE-SPEC)))", ((cpp_function_code)(&cppTranslateReturnParameter)), NULL);
    defineFunctionObject("CPP-TRANSLATE-FUNCTION-PARAMETERS", "(DEFUN (CPP-TRANSLATE-FUNCTION-PARAMETERS CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&cppTranslateFunctionParameters)), NULL);
    defineFunctionObject("SLOT-READER-FROM-NAME?", "(DEFUN (SLOT-READER-FROM-NAME? BOOLEAN) ((METHODNAME SYMBOL) (METHODOWNER TYPE-SPEC)))", ((cpp_function_code)(&slotReaderFromNameP)), NULL);
    defineFunctionObject("SLOT-READER?", "(DEFUN (SLOT-READER? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&slotReaderP)), NULL);
    defineFunctionObject("CPP-TRANSLATE-CONSTRUCTOR-NAME", "(DEFUN (CPP-TRANSLATE-CONSTRUCTOR-NAME STRING-WRAPPER) ((CONSTRUCTOR METHOD-SLOT)))", ((cpp_function_code)(&cppTranslateConstructorName)), NULL);
    defineFunctionObject("CPP-TRANSLATE-FUNCTION-NAME-FROM-NAME", "(DEFUN (CPP-TRANSLATE-FUNCTION-NAME-FROM-NAME STRING-WRAPPER) ((FUNCTIONNAME SYMBOL)))", ((cpp_function_code)(&cppTranslateFunctionNameFromName)), NULL);
    defineFunctionObject("CPP-TRANSLATE-FUNCTION-NAME", "(DEFUN (CPP-TRANSLATE-FUNCTION-NAME STRING-WRAPPER) ((FUNCTION METHOD-SLOT) (QUALIFY? BOOLEAN)))", ((cpp_function_code)(&cppTranslateFunctionName)), NULL);
    defineFunctionObject("CPP-TRANSLATE-METHOD-NAME-FROM-NAME", "(DEFUN (CPP-TRANSLATE-METHOD-NAME-FROM-NAME STRING-WRAPPER) ((METHODNAME SYMBOL) (METHODOWNER TYPE-SPEC)))", ((cpp_function_code)(&cppTranslateMethodNameFromName)), NULL);
    defineFunctionObject("CPP-TRANSLATE-METHOD-NAME", "(DEFUN (CPP-TRANSLATE-METHOD-NAME STRING-WRAPPER) ((METHOD METHOD-SLOT) (QUALIFY? BOOLEAN)))", ((cpp_function_code)(&cppTranslateMethodName)), NULL);
    defineFunctionObject("DELETE-QUOTED-NULL-STATEMENTS", "(DEFUN (DELETE-QUOTED-NULL-STATEMENTS CONS) ((TREES CONS)))", ((cpp_function_code)(&deleteQuotedNullStatements)), NULL);
    defineFunctionObject("CPP-METHOD-OBJECT-IS-FUNCTION?", "(DEFUN (CPP-METHOD-OBJECT-IS-FUNCTION? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&cppMethodObjectIsFunctionP)), NULL);
    defineFunctionObject("CPP-METHOD-OBJECT-IS-OVERLOADED-FUNCTION?", "(DEFUN (CPP-METHOD-OBJECT-IS-OVERLOADED-FUNCTION? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&cppMethodObjectIsOverloadedFunctionP)), NULL);
  }
}

void startupCppTranslate() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupCppTranslate1();
      helpStartupCppTranslate2();
      helpStartupCppTranslate3();
      helpStartupCppTranslate4();
      helpStartupCppTranslate5();
    }
    if (currentStartupTimePhaseP(4)) {
      helpStartupCppTranslate6();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupCppTranslate7();
      helpStartupCppTranslate8();
      defineFunctionObject("WRAP-METHOD-BODY-WITH-CPP-AUXILIARY-DECLARATIONS", "(DEFUN (WRAP-METHOD-BODY-WITH-CPP-AUXILIARY-DECLARATIONS CONS) ((METHODBODY CONS) (DECLARATIONS CONS)))", ((cpp_function_code)(&wrapMethodBodyWithCppAuxiliaryDeclarations)), NULL);
      defineFunctionObject("CPP-TRANSLATE-DEFINE-METHOD-UNIT", "(DEFUN (CPP-TRANSLATE-DEFINE-METHOD-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&cppTranslateDefineMethodUnit)), NULL);
      defineFunctionObject("CPP-TRANSLATE-RETURN-TREE", "(DEFUN (CPP-TRANSLATE-RETURN-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateReturnTree)), NULL);
      defineFunctionObject("CPP-TRANSLATE-ACTUAL-PARAMETERS", "(DEFUN (CPP-TRANSLATE-ACTUAL-PARAMETERS CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateActualParameters)), NULL);
      defineFunctionObject("CPP-TRANSLATE-VARIABLE-LENGTH-ACTUALS", "(DEFUN (CPP-TRANSLATE-VARIABLE-LENGTH-ACTUALS CONS) ((ACTUALS CONS) (METHOD METHOD-SLOT)))", ((cpp_function_code)(&cppTranslateVariableLengthActuals)), NULL);
      defineFunctionObject("CPP-TRANSLATE-CALL-METHOD-SETTER", "(DEFUN (CPP-TRANSLATE-CALL-METHOD-SETTER CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateCallMethodSetter)), NULL);
      defineFunctionObject("CPP-CREATE-OVERLOADED-FUNCTION-NAME", "(DEFUN (CPP-CREATE-OVERLOADED-FUNCTION-NAME SYMBOL) ((FUNCTIONNAME SYMBOL) (CLASSTYPE TYPE)))", ((cpp_function_code)(&cppCreateOverloadedFunctionName)), NULL);
      defineFunctionObject("CPP-POSSIBLY-OVERLOADED-FUNCTION-NAME?", "(DEFUN (CPP-POSSIBLY-OVERLOADED-FUNCTION-NAME? BOOLEAN) ((FUNCTIONNAME SYMBOL)))", ((cpp_function_code)(&cppPossiblyOverloadedFunctionNameP)), NULL);
      defineFunctionObject("CPP-TRANSLATE-METHOD-CALL", "(DEFUN (CPP-TRANSLATE-METHOD-CALL CONS) ((TREE CONS) (REFERENCED? BOOLEAN)))", ((cpp_function_code)(&cppTranslateMethodCall)), NULL);
      defineFunctionObject("CPP-TRANSLATE-SUPER-METHOD-CALL", "(DEFUN (CPP-TRANSLATE-SUPER-METHOD-CALL CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateSuperMethodCall)), NULL);
      defineFunctionObject("CPP-TRANSLATE-NORMAL-METHOD-CALL", "(DEFUN (CPP-TRANSLATE-NORMAL-METHOD-CALL CONS) ((METHODNAME SYMBOL) (OWNER TYPE) (ARGUMENTS CONS) (REFERENCED? BOOLEAN)))", ((cpp_function_code)(&cppTranslateNormalMethodCall)), NULL);
      defineFunctionObject("CPP-TRANSLATE-DEFINED?-METHOD-CALL", "(DEFUN (CPP-TRANSLATE-DEFINED?-METHOD-CALL CONS) ((ARGUMENTTYPE TYPE) (ARGUMENT OBJECT) (NULL? BOOLEAN)))", ((cpp_function_code)(&cppTranslateDefinedPMethodCall)), NULL);
      defineFunctionObject("CPP-TRANSLATE-NTH-METHOD-CALL", "(DEFUN (CPP-TRANSLATE-NTH-METHOD-CALL CONS) ((OPERATOR SYMBOL) (OWNER TYPE) (ARGUMENTS CONS)))", ((cpp_function_code)(&cppTranslateNthMethodCall)), NULL);
      defineFunctionObject("CPP-TRANSLATE-AREF-METHOD-CALL", "(DEFUN (CPP-TRANSLATE-AREF-METHOD-CALL CONS) ((OPERATOR SYMBOL) (OWNER TYPE) (ARGUMENTS CONS)))", ((cpp_function_code)(&cppTranslateArefMethodCall)), NULL);
      defineFunctionObject("CPP-TRANSLATE-FUNCTION-SIGNATURE", "(DEFUN (CPP-TRANSLATE-FUNCTION-SIGNATURE CONS) ((FUNCTION METHOD-SLOT)))", ((cpp_function_code)(&cppTranslateFunctionSignature)), NULL);
      defineFunctionObject("CPP-TRANSLATE-CODE-SIGNATURE", "(DEFUN (CPP-TRANSLATE-CODE-SIGNATURE CONS) ((SIGNATURE CONS)))", ((cpp_function_code)(&cppTranslateCodeSignature)), NULL);
      defineFunctionObject("CPP-TRANSLATE-METHOD-CODE-SIGNATURE", "(DEFUN (CPP-TRANSLATE-METHOD-CODE-SIGNATURE CONS) ((SIGNATURE CONS)))", ((cpp_function_code)(&cppTranslateMethodCodeSignature)), NULL);
      defineFunctionObject("CPP-TRANSLATE-CALL-FUNCTION-CODE", "(DEFUN (CPP-TRANSLATE-CALL-FUNCTION-CODE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateCallFunctionCode)), NULL);
      defineFunctionObject("CPP-TRANSLATE-CALL-METHOD-CODE", "(DEFUN (CPP-TRANSLATE-CALL-METHOD-CODE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateCallMethodCode)), NULL);
      defineFunctionObject("GET-LAST-N-ELEMENTS", "(DEFUN (GET-LAST-N-ELEMENTS CONS) ((LIST CONS) (N INTEGER)))", ((cpp_function_code)(&getLastNElements)), NULL);
      defineFunctionObject("CPP-YIELD-UNUSED-DUMMY-ARGS", "(DEFUN (CPP-YIELD-UNUSED-DUMMY-ARGS CONS) ((METHOD METHOD-SLOT) (ARGS CONS)))", ((cpp_function_code)(&cppYieldUnusedDummyArgs)), NULL);
      defineFunctionObject("CPP-TRANSLATE-FUNCTION-CALL", "(DEFUN (CPP-TRANSLATE-FUNCTION-CALL CONS) ((TREE CONS) (METHOD METHOD-SLOT)))", ((cpp_function_code)(&cppTranslateFunctionCall)), NULL);
      defineFunctionObject("CPP-TRANSLATE-OPERATOR-TREE", "(DEFUN (CPP-TRANSLATE-OPERATOR-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&cppTranslateOperatorTree)), NULL);
      defineFunctionObject("CPP-TRANSLATE-OPERATOR-CALL", "(DEFUN (CPP-TRANSLATE-OPERATOR-CALL CONS) ((OPERATORNAMES CONS) (ARGUMENTS CONS) (ARITY INTEGER)))", ((cpp_function_code)(&cppTranslateOperatorCall)), NULL);
      defineFunctionObject("CPP-TRANSLATE-HARDCODED-SYMBOL-REFERENCE", "(DEFUN (CPP-TRANSLATE-HARDCODED-SYMBOL-REFERENCE CONS) ((OPERATOR SYMBOL) (OFFSET INTEGER)))", ((cpp_function_code)(&cppTranslateHardcodedSymbolReference)), NULL);
      defineFunctionObject("STARTUP-CPP-TRANSLATE", "(DEFUN STARTUP-CPP-TRANSLATE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupCppTranslate)), NULL);
      { MethodSlot* function = lookupFunction(SYM_CPP_TRANSLATE_STELLA_STARTUP_CPP_TRANSLATE);

        setDynamicSlotValue(function->dynamicSlots, SYM_CPP_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupCppTranslate"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *CPP-TRUE-STRING-WRAPPER* STRING-WRAPPER (WRAP-LITERAL \"TRUE\") :PUBLIC? FALSE :DOCUMENTATION \"Wrapped TRUE string, used to reduce consing.\")", &oCPP_TRUE_STRING_WRAPPERo);
      defineGlobalVariableObject("(DEFGLOBAL *CPP-FALSE-STRING-WRAPPER* STRING-WRAPPER (WRAP-LITERAL \"FALSE\") :PUBLIC? FALSE :DOCUMENTATION \"Wrapped FALSE string, used to reduce consing.\")", &oCPP_FALSE_STRING_WRAPPERo);
      defineGlobalVariableObject("(DEFSPECIAL *DUMMYDECLARATIONS* CONS NULL :DOCUMENTATION \"Temporary List of declarations for unused return parameters\")", &oDUMMYDECLARATIONSo);
      defineGlobalVariableObject("(DEFSPECIAL *CURRENTDUMMYINDEX* INTEGER NULL-INTEGER :DOCUMENTATION \"Current index of dummy parameter for unused return value\")", &oCURRENTDUMMYINDEXo);
      defineGlobalVariableObject("(DEFGLOBAL *CPP-OPERATOR-TABLE* KEY-VALUE-LIST (DICTIONARY @KEY-VALUE-LIST (QUOTE ++) (CONS (WRAP-LITERAL \"++\") NIL) (QUOTE --) (CONS (WRAP-LITERAL \"--\") NIL) (QUOTE +) (CONS (WRAP-LITERAL \"+\") NIL) (QUOTE -) (CONS (WRAP-LITERAL \"-\") NIL) (QUOTE *) (CONS (WRAP-LITERAL \"*\") NIL) (QUOTE /) (CONS (WRAP-LITERAL \"/\") NIL) (QUOTE EQ?) (CONS (WRAP-LITERAL \"==\") NIL) (QUOTE !=) (CONS (WRAP-LITERAL \"!=\") NIL) (QUOTE >) (CONS (WRAP-LITERAL \">\") NIL) (QUOTE >=) (CONS (WRAP-LITERAL \">=\") NIL) (QUOTE =>) (CONS (WRAP-LITERAL \">=\") NIL) (QUOTE <) (CONS (WRAP-LITERAL \"<\") NIL) (QUOTE =<) (CONS (WRAP-LITERAL \"<=\") NIL) (QUOTE <=) (CONS (WRAP-LITERAL \"<=\") NIL) (QUOTE AND) (CONS (WRAP-LITERAL \"&&\") NIL) (QUOTE OR) (CONS (WRAP-LITERAL \"||\") NIL) (QUOTE NOT) (CONS (WRAP-LITERAL \"!\") NIL) (QUOTE CHOOSE) (CONS (WRAP-LITERAL \"?\") (CONS (WRAP-LITERAL \":\") NIL))) :DOCUMENTATION \"Mapping from STELLA operators to C++ operators\")", &oCPP_OPERATOR_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *CPP-RESERVED-WORD-TABLE* (STRING-HASH-TABLE OF STRING STRING-WRAPPER) (CPP-CREATE-RESERVED-WORD-TABLE))", &oCPP_RESERVED_WORD_TABLEo);
      defineGlobalVariableObject("(DEFSPECIAL *CPP-CURRENT-UNIT-MODULE* MODULE NULL :DOCUMENTATION \"Home module of the currently translated unit.  Needed for\nproper name translation for units whose home module is different than the\nfile module (occurs in some PowerLoom files - I thought we had outlawed that).\")", &oCPP_CURRENT_UNIT_MODULEo);
      defineGlobalVariableObject("(DEFSPECIAL *CPPLOOPEXIT* SYMBOL (QUOTE CPP_BREAK))", &oCPPLOOPEXITo);
      defineGlobalVariableObject("(DEFSPECIAL *CPPLOOPEXITACTIVE?* BOOLEAN FALSE)", &oCPPLOOPEXITACTIVEpo);
      defineGlobalVariableObject("(DEFGLOBAL *CPP-CHARACTER-SUBSTITUTION-TABLE* STRING (CPP-CREATE-CHARACTER-SUBSTITUTION-TABLE))", &oCPP_CHARACTER_SUBSTITUTION_TABLEo);
      defineGlobalVariableObject("(DEFSPECIAL *CPP-NAME-QUALIFICATION-MODE* KEYWORD :CLEVER)", &oCPP_NAME_QUALIFICATION_MODEo);
      defineGlobalVariableObject("(DEFGLOBAL *CPP-NAMESPACE-SEPARATOR* STRING \"::\")", &oCPP_NAMESPACE_SEPARATORo);
    }
  }
}

Keyword* KWD_CPP_TRANSLATE_USE_CPP_GARBAGE_COLLECTOR = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_KEY_VALUE_LIST = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_ii = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA___ = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_i = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA__ = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_o = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_s = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_EQp = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_xe = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_g = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_ge = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_eg = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_l = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_el = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_le = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_AND = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_OR = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_NOT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CHOOSE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_ASM = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_ASSERT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_AUTO = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_BREAK = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CASE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CATCH = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CHAR = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CLASS = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CONST = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CONTINUE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_DEFAULT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_DELETE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_DO = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_DOUBLE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_ELSE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_ENUM = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_EXTERN = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_FLOAT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_FOR = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_FRIEND = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_GOTO = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_IF = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_INLINE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_INT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_LONG = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_NAMESPACE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_NEW = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_OPERATOR = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_PRIVATE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_PROTECTED = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_PUBLIC = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_REGISTER = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_RETURN = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SHORT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SIGNED = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SIZEOF = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_STATIC = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_STRUCT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SWITCH = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_TEMPLATE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_THROW = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_TRY = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_TYPEDEF = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_TYPEID = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_UNION = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_UNSIGNED = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_VIRTUAL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_VOID = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_VOLATILE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_WHILE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_TYPENAME = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_GLOBAL_VARIABLE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_TYPE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_METHOD = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_MACRO = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_PRINT_METHOD = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_STARTUP_TIME_PROGN = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_VERBATIM = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_CONS = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SPECIAL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_UNWIND_PROTECT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_SIGNAL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_HANDLER_CASE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_HANDLE_EXCEPTION = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_VOID_SYS = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_BAD_SYS = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_TYPED_SYS = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SETQ = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_SET_DEFAULT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_SLOT_VALUE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_REFERENCED_SLOT_VALUE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_SLOT_VALUE_SETTER = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_CALL_METHOD = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_REFERENCED_CALL_METHOD = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_CALL_SUPER_METHOD = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_CALL_FUNCTION = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_PROGN = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_WITH_PROCESS_LOCK = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_LOOP = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_FOREACH = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_LET = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CAST = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SAFE_CAST = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_WHEN = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_UNLESS = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_COND = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_MAKE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_NEW = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_MV_SETQ = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_CALL_FUNCTION_CODE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_CALL_METHOD_CODE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_INLINE_CALL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_THE_CODE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_POINTER_TO_FUNCTION = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_IGNORE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_PRINT_STREAM = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_PRINT_NATIVE_STREAM = NULL;

Keyword* KWD_CPP_TRANSLATE_CPP = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_VERBATIM = NULL;

Keyword* KWD_CPP_TRANSLATE_UNBIND_WITH_DESTRUCTORS = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_IDENT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_ACTUALS = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_BLOCK = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_COMMENT = NULL;

Keyword* KWD_CPP_TRANSLATE_DIGIT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_PRINT_NATIVE_STREAM = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_DEFPRINT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_RETURN = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_STREAM = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_SIGNAL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_DEREFERENCE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_HANDLER_CASE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_CATCH = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_TYPE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_LOCAL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_UNWIND_PROTECT = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_NUMBER = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_NUMBER_WRAPPER = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_CAST = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_ASSIGN = NULL;

Keyword* KWD_CPP_TRANSLATE_UNBOUND_SPECIAL_VARIABLE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_SPECIAL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_GLOBAL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_SYMBOL_ID = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_OTHERWISE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_CASE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_PROGN = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_COND = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_BREAK = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_LOOP = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_GOTO_LABEL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_WHILE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_WITH_PROCESS_LOCK = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_GOTO = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_CONTINUE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_IF = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_WHEN = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_UNLESS = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_ARGUMENT_LIST_ITERATOR = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_FOREACH = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_VA_START = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_VA_END = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_INTEGER = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_ALLOCATE_ITERATOR = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_LENGTH = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_NEXTp = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_ARGUMENT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_BINARY_OP = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_UNARY_OP = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_LITERAL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_VA_ARG = NULL;

Keyword* KWD_CPP_TRANSLATE_FUNCTION = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_POINTER = NULL;

Keyword* KWD_CPP_TRANSLATE_METHOD = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_POINTER = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_TRUE = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_SHORT_INTEGER = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_LONG_INTEGER = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_UNSIGNED_LONG_INTEGER = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_FLOAT = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_SINGLE_FLOAT = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_DOUBLE_FLOAT = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_CHARACTER = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_BYTE = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_OCTET = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_ANY_VALUE = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_NATIVE_EXCEPTION = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_ARRAY_REFERENCE = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_VOID = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_REFERENCED_SLOT_VALUE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_SLOT_VALUE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_SLOT_VALUE_SETTER = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CLASS_CPP_NATIVE_TYPE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_MAKE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_STARTUP_TIME_PROGN = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_PRINT_STREAM = NULL;

Keyword* KWD_CPP_TRANSLATE_WARN = NULL;

Keyword* KWD_CPP_TRANSLATE_ERROR = NULL;

Keyword* KWD_CPP_TRANSLATE_CONTINUABLE_ERROR = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_STANDARD_ERROR = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_STANDARD_OUT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_EOL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_SYMBOL = NULL;

Keyword* KWD_CPP_TRANSLATE_CPP_STANDALONE = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_UNKNOWN = NULL;

Keyword* KWD_CPP_TRANSLATE_UPPERCASE = NULL;

Keyword* KWD_CPP_TRANSLATE_LOWERCASE = NULL;

Keyword* KWD_CPP_TRANSLATE_CAPITALIZED = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_F_CPP_CHANGE_CASE_MEMO_TABLE_000 = NULL;

Keyword* KWD_CPP_TRANSLATE_CLEVER = NULL;

Keyword* KWD_CPP_TRANSLATE_YES = NULL;

Keyword* KWD_CPP_TRANSLATE_NO = NULL;

Keyword* KWD_CPP_TRANSLATE_PRESERVE = NULL;

Keyword* KWD_CPP_TRANSLATE_UPCASE = NULL;

Keyword* KWD_CPP_TRANSLATE_TITLECASEX = NULL;

Keyword* KWD_CPP_TRANSLATE_TITLECASE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_MODULE_CPP_PACKAGE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_NULL = NULL;

Keyword* KWD_CPP_TRANSLATE_FULL = NULL;

Keyword* KWD_CPP_TRANSLATE_NEVER = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_FALSE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA__RETURN = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_VAR_ARGS = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_STORAGE_SLOT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_METHOD_NATIVEp = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_LITERAL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_THIS = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_DOCUMENTATION = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_METHOD = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_EXTERN_C = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_SETTER_CALL = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_OBJECT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_DEFINEDp = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_NULLp = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_NTH = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_NTH_SETTER = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_AREF = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_AREF_SETTER = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_ARGUMENT_LIST = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_REFERENCED_METHOD_CALL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_CALL = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_BOOLEAN = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_STRING = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_MUTABLE_STRING = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_NATIVE_VECTOR = NULL;

Surrogate* SGT_CPP_TRANSLATE_STELLA_ARRAY = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_SIGNATURE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_SIGNATURE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_FUNCALL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_CODE_CALL = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_DUMMY = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_GET_SYM = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_GET_KWD = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_GET_SGT = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_TERNARY_OP = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_STARTUP_CPP_TRANSLATE = NULL;

Symbol* SYM_CPP_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
