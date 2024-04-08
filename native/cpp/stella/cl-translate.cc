//  -*- Mode: C++ -*-

// cl-translate.cc

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

Symbol* destructureCallTree(Cons* tree, Surrogate*& _Return1, Cons*& _Return2) {
  { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

    if (testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_CALL_FUNCTION) {
      _Return1 = NULL;
      _Return2 = tree->rest->rest;
      return (((Symbol*)(tree->rest->value)));
    }
    else if (testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_CALL_METHOD) {
      _Return1 = ((Surrogate*)(tree->rest->value));
      _Return2 = tree->rest->rest->rest;
      return (((Symbol*)(tree->rest->rest->value)));
    }
    else {
      _Return1 = NULL;
      _Return2 = tree->rest;
      return (((Symbol*)(tree->value)));
    }
  }
}

VerbatimStringWrapper* oCL_TRUE_STRING_WRAPPERo = NULL;

VerbatimStringWrapper* oCL_FALSE_STRING_WRAPPERo = NULL;

// Mapping from STELLA operators to Common-Lisp operators.
KeyValueList* oCL_OPERATOR_TABLEo = NULL;

boolean useClConsesP() {
  return (oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_CONSES));
}

boolean useDefconsmethodP(MethodSlot* method) {
  if ((!method->methodFunctionP) &&
      oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_CONSES)) {
    { Surrogate* testValue000 = method->slotOwner;

      if (testValue000 == SGT_CL_TRANSLATE_STELLA_CONS) {
        return (true);
      }
      else if (testValue000 == SGT_CL_TRANSLATE_STELLA_STANDARD_OBJECT) {
        if (lookupSlot(((Class*)(SGT_CL_TRANSLATE_STELLA_CONS->surrogateValue)), method->slotName)->slotOwner == SGT_CL_TRANSLATE_STELLA_CONS) {
          return (false);
        }
        else {
          return (true);
        }
      }
      else if (testValue000 == SGT_CL_TRANSLATE_STELLA_OBJECT) {
        { Surrogate* testValue001 = lookupSlot(((Class*)(SGT_CL_TRANSLATE_STELLA_CONS->surrogateValue)), method->slotName)->slotOwner;

          if ((testValue001 == SGT_CL_TRANSLATE_STELLA_CONS) ||
              (testValue001 == SGT_CL_TRANSLATE_STELLA_STANDARD_OBJECT)) {
            return (false);
          }
          else {
            return (true);
          }
        }
      }
      else {
      }
    }
  }
  return (false);
}

boolean useClStructsP() {
  return (oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_STRUCTS));
}

boolean useVectorStructsP() {
  return (oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_VECTOR_STRUCTS));
}

DEFINE_STELLA_SPECIAL(oNEEDEXPLICITRETURNpo, boolean , false);

Cons* clTranslateListOfTrees(Cons* trees) {
  { Cons* cursor = trees;

    while (!(cursor == NIL)) {
      { 
        BIND_STELLA_SPECIAL(oNEEDEXPLICITRETURNpo, boolean, oNEEDEXPLICITRETURNpo ||
            (!(cursor->rest == NIL)));
        cursor->value = clTranslateATree(cursor->value);
      }
      cursor = cursor->rest;
    }
    return (trees);
  }
}

Cons* clTranslateVoidSys(Cons* tree) {
  { Object* otree = clTranslateATree(tree->rest->value);

    return (((Cons*)(otree)));
  }
}

Object* clTranslateTypedSys(Cons* tree) {
  { Object* otree = clTranslateATree(tree->rest->value);

    return (otree);
  }
}

Object* clTranslateBadSys(Cons* tree) {
  { Object* returntype = tree->rest->rest->value;

    if (returntype == SGT_CL_TRANSLATE_STELLA_VOID) {
      return (clTranslateATree(yieldIllegalStatementTree()));
    }
    else {
      return (clTranslateATree(yieldIllegalExpressionTree()));
    }
  }
}

Object* clTranslateATree(Object* tree) {
  return (helpClTranslateATree(tree));
}

Object* helpClTranslateATree(Object* tree) {
  if (!((boolean)(tree))) {
    return (tree);
  }
  if (safePrimaryType(tree) == SGT_CL_TRANSLATE_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if (tree == NIL) {
        return (tree);
      }
      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if (testValue000 == SYM_CL_TRANSLATE_STELLA_VOID_SYS) {
          return (clTranslateVoidSys(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_TYPED_SYS) {
          return (clTranslateTypedSys(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_BAD_SYS) {
          return (clTranslateBadSys(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_SETQ) {
          return (clTranslateSetqTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_SLOT_VALUE) {
          return (clTranslateFixedSlotValueTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_SLOT_VALUE_SETTER) {
          return (clTranslateFixedSlotValueSetterTree(tree));
        }
        else if ((testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_CALL_METHOD) ||
            (testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_CALL_FUNCTION)) {
          return (clTranslateCallMethodTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_CALL_SUPER_METHOD) {
          return (clTranslateCallSuperMethodTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_PROGN) {
          tree->value = internCommonLispSymbol("PROGN");
          tree->rest = clTranslateListOfTrees(tree->rest);
          return (tree);
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_WITH_PROCESS_LOCK) {
          tree->value = clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_WITH_PROCESS_LOCK);
          tree->secondSetter(clTranslateATree(tree->rest->value));
          tree->rest->rest = clTranslateListOfTrees(tree->rest->rest);
          return (tree);
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_LOOP) {
          { 
            BIND_STELLA_SPECIAL(oNEEDEXPLICITRETURNpo, boolean, true);
            tree->value = internCommonLispSymbol("LOOP");
            tree->rest = maybeWrapWithContinueLabel(clTranslateListOfTrees(tree->rest));
            return (tree);
          }
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_FOREACH) {
          { 
            BIND_STELLA_SPECIAL(oNEEDEXPLICITRETURNpo, boolean, true);
            return (clTranslateForeachTree(tree));
          }
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_LET) {
          return (clTranslateLetTree(tree, false));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_STARTUP_TIME_PROGN) {
          { 
            BIND_STELLA_SPECIAL(oNEEDEXPLICITRETURNpo, boolean, true);
            return (clTranslateStartupTimePrognTree(tree));
          }
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_SPECIAL) {
          return (clTranslateSpecialTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_UNWIND_PROTECT) {
          return (clTranslateUnwindProtectTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_HANDLER_CASE) {
          return (clTranslateHandlerCaseTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_HANDLE_EXCEPTION) {
          return (clTranslateHandleExceptionTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_SIGNAL) {
          return (clTranslateSignalTree(tree));
        }
        else if ((testValue000 == SYM_CL_TRANSLATE_STELLA_CAST) ||
            (testValue000 == SYM_CL_TRANSLATE_STELLA_SAFE_CAST)) {
          return (clTranslateCastTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_RETURN) {
          return (clTranslateReturnTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_BREAK) {
          tree->firstSetter(internCommonLispSymbol("RETURN"));
          return (tree);
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_CONTINUE) {
          return (listO(3, internCommonLispSymbol("GO"), KWD_CL_TRANSLATE_CONTINUE, NIL));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_WHILE) {
          { 
            BIND_STELLA_SPECIAL(oNEEDEXPLICITRETURNpo, boolean, true);
            return (clTranslateWhileTree(tree));
          }
        }
        else if ((testValue000 == SYM_CL_TRANSLATE_STELLA_IF) ||
            ((testValue000 == SYM_CL_TRANSLATE_STELLA_CHOOSE) ||
             ((testValue000 == SYM_CL_TRANSLATE_STELLA_WHEN) ||
              (testValue000 == SYM_CL_TRANSLATE_STELLA_UNLESS)))) {
          return (clTranslateConditionalTree(tree));
        }
        else if ((testValue000 == SYM_CL_TRANSLATE_STELLA_AND) ||
            ((testValue000 == SYM_CL_TRANSLATE_STELLA_OR) ||
             (testValue000 == SYM_CL_TRANSLATE_STELLA_NOT))) {
          return (clTranslateBooleanTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_COND) {
          return (clTranslateCondTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_CASE) {
          return (clTranslateCaseTree(tree));
        }
        else if ((testValue000 == SYM_CL_TRANSLATE_STELLA_EQp) ||
            ((testValue000 == SYM_CL_TRANSLATE_STELLA_g) ||
             ((testValue000 == SYM_CL_TRANSLATE_STELLA_ge) ||
              ((testValue000 == SYM_CL_TRANSLATE_STELLA_l) ||
               (testValue000 == SYM_CL_TRANSLATE_STELLA_le))))) {
          return (clTranslateOperatorTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_MAKE) {
          return (clTranslateMakeTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_NEW) {
          return (clTranslateNewTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_MV_SETQ) {
          tree->firstSetter(internCommonLispSymbol("MULTIPLE-VALUE-SETQ"));
          tree->secondSetter(clTranslateListOfTrees(((Cons*)(tree->rest->value))));
          tree->thirdSetter(clTranslateATree(tree->rest->rest->value));
          return (tree);
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_QUOTE) {
          tree->firstSetter(internCommonLispSymbol("QUOTE"));
          return (tree);
        }
        else if ((testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_CALL_FUNCTION_CODE) ||
            (testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_CALL_METHOD_CODE)) {
          return (clTranslateCallFunctionCodeTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_SYS_INLINE_CALL) {
          return (clTranslateInlineCallTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_THE_CODE) {
          return (clTranslateTheCodeTree(tree));
        }
        else if ((testValue000 == SYM_CL_TRANSLATE_STELLA_PRINT_STREAM) ||
            (testValue000 == SYM_CL_TRANSLATE_STELLA_PRINT_NATIVE_STREAM)) {
          return (clTranslatePrintStreamTree(tree));
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_VERBATIM) {
          return (clTranslateVerbatimTree(tree));
        }
        else if ((testValue000 == SYM_CL_TRANSLATE_STELLA_INLINE) ||
            (testValue000 == SYM_CL_TRANSLATE_STELLA_IGNORE)) {
          return (clTranslateInlineTree(tree));
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
    return (tree->clTranslateAtomicTree());
  }
}

Object* Object::clTranslateAtomicTree() {
  { Object* tree = this;

    return (tree);
  }
}

Object* FloatWrapper::clTranslateAtomicTree() {
  { FloatWrapper* tree = this;

    { const char* floatString = stringify(tree);

      if (stringMemberP(floatString, 'e')) {
        floatString = stringSubstitute(floatString, 'd', 'e');
      }
      else if (stringMemberP(floatString, 'E')) {
        floatString = stringSubstitute(floatString, 'd', 'E');
      }
      else {
        floatString = stringConcatenate(floatString, "d0", 0);
      }
      return (newVerbatimStringWrapper(floatString));
    }
  }
}

Object* Symbol::clTranslateAtomicTree() {
  { Symbol* tree = this;

    if (tree == SYM_CL_TRANSLATE_STELLA_TRUE) {
      return (oCL_TRUE_STRING_WRAPPERo);
    }
    else if (tree == SYM_CL_TRANSLATE_STELLA_FALSE) {
      return (oCL_FALSE_STRING_WRAPPERo);
    }
    else if (((boolean)(tree->lookupGlobalVariable()))) {
      return (clTranslateGlobalSymbol(tree));
    }
    else {
      return (clTranslateLocalSymbol(tree));
    }
  }
}

Object* Keyword::clTranslateAtomicTree() {
  { Keyword* tree = this;

    if (useHardcodedSymbolsP()) {
      { IntegerWrapper* offset = wrapInteger(tree->keywordify()->symbolId);

        return (listO(3, SYM_CL_TRANSLATE_STELLA_GET_KWD, offset, NIL));
      }
    }
    else {
      return (clTranslateGlobalSymbol(yieldSymbolConstantName(tree)));
    }
  }
}

Object* Surrogate::clTranslateAtomicTree() {
  { Surrogate* tree = this;

    if (useHardcodedSymbolsP()) {
      { IntegerWrapper* offset = wrapInteger(tree->symbolId);

        return (listO(3, SYM_CL_TRANSLATE_STELLA_GET_SGT, offset, NIL));
      }
    }
    else {
      return (clTranslateGlobalSymbol(yieldSymbolConstantName(tree)));
    }
  }
}

Object* clTranslateGlobalSymbol(Symbol* symbol) {
  { Module* symbolmodule = ((Module*)(symbol->homeContext));

    if (symbolmodule == oCOMMON_LISP_MODULEo) {
      return (symbol);
    }
    if (!((boolean)(symbolmodule))) {
      symbolmodule = oMODULEo;
    }
    return (yieldGlobalLispSymbol(symbolmodule, symbol->symbolName));
  }
}

const char* yieldReadableSymbolName(Module* symbolmodule, const char* symbolname, boolean localP) {
  { const char* lispsymbolname = ((localP ||
        (((StringWrapper*)(dynamicSlotValue(symbolmodule->dynamicSlots, SYM_CL_TRANSLATE_STELLA_MODULE_LISP_PACKAGE, NULL_STRING_WRAPPER)))->wrapperValue != NULL)) ? symbolname : computeFullName(symbolname, symbolmodule));

    { Keyword* testValue000 = computeSymbolEscapeCode(lispsymbolname, false);

      if (testValue000 == KWD_CL_TRANSLATE_UNESCAPED) {
      }
      else if (testValue000 == KWD_CL_TRANSLATE_ESCAPED) {
        lispsymbolname = stringConcatenate("|", stringConcatenate(lispsymbolname, "|", 0), 0);
      }
      else if (testValue000 == KWD_CL_TRANSLATE_COMPLEX_ESCAPED) {
        { OutputStringStream* s = newOutputStringStream();

          printSymbolNameReadably(lispsymbolname, s->nativeStream, false);
          lispsymbolname = s->theStringReader();
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    return (lispsymbolname);
  }
}

Object* yieldGlobalLispSymbol(Module* symbolmodule, const char* symbolname) {
  { const char* lispsymbolpackage = (((!((boolean)(symbolmodule))) ||
        ((symbolmodule == oMODULEo) ||
         stringEqlP(symbolmodule->lispPackage(), oMODULEo->lispPackage()))) ? ((const char*)(NULL)) : symbolmodule->lispPackage());
    const char* lispsymbolname = yieldReadableSymbolName(symbolmodule, symbolname, false);

    if (lispsymbolpackage == NULL) {
      return (newVerbatimStringWrapper(lispsymbolname));
    }
    else {
      return (newVerbatimStringWrapper(stringConcatenate(lispsymbolpackage, stringConcatenate("::", lispsymbolname, 0), 0)));
    }
  }
}

Object* clTranslateLocalSymbol(Symbol* symbol) {
  return (newVerbatimStringWrapper(yieldReadableSymbolName(((Module*)(symbol->homeContext)), symbol->symbolName, true)));
}

Cons* clTranslateSetqTree(Cons* tree) {
  tree->firstSetter(internCommonLispSymbol("SETQ"));
  tree->secondSetter(clTranslateATree(tree->rest->value));
  tree->thirdSetter(clTranslateATree(tree->rest->rest->value));
  return (tree);
}

Object* yieldStructSlotAccessorName(Surrogate* classtype, Symbol* slotname) {
  return (yieldGlobalLispSymbol(((Module*)(classtype->homeContext)), stringConcatenate("%", stringConcatenate(classtype->symbolName, stringConcatenate(".", slotname->symbolName, 0), 0), 0)));
}

Object* yieldClosSlotAccessorName(Symbol* slotname) {
  return (yieldGlobalLispSymbol(((Module*)(slotname->homeContext)), stringConcatenate("%", slotname->symbolName, 0)));
}

Cons* yieldSlotValueReaderTree(Symbol* slotname, Object* objectref, Surrogate* objecttype) {
  if ((objecttype == SGT_CL_TRANSLATE_STELLA_CONS) &&
      oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_CONSES)) {
    if (slotname == SYM_CL_TRANSLATE_STELLA_VALUE) {
      return (cons(clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_rrVALUE), cons(objectref, NIL)));
    }
    else if (slotname == SYM_CL_TRANSLATE_STELLA_REST) {
      return (cons(clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_rrREST), cons(objectref, NIL)));
    }
    else {
    }
  }
  { Class* clasS = ((Class*)(objecttype->surrogateValue));

    if ((!oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_STRUCTS)) ||
        (exceptionClassP(clasS) ||
         clAlwaysTranslateToClosClassP(clasS))) {
      return (cons(yieldClosSlotAccessorName(slotname), cons(objectref, NIL)));
    }
    else if (oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_VECTOR_STRUCTS)) {
      return (cons(clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_CLSYS_SVAL), cons(wrapInteger(clStructSlotOffset(slotname, objecttype)), cons(clTranslateGlobalSymbol(internSymbolInModule(objecttype->symbolName, ((Module*)(objecttype->homeContext)), true)), cons(clTranslateGlobalSymbol(slotname), cons(objectref, NIL))))));
    }
    else {
      return (cons(yieldStructSlotAccessorName(objecttype, slotname), cons(objectref, NIL)));
    }
  }
}

Cons* yieldSlotValueWriterTree(Symbol* slotname, Object* objectref, Surrogate* objecttype, Object* valueref) {
  return (listO(3, internCommonLispSymbol("SETF"), yieldSlotValueReaderTree(slotname, objectref, objecttype), cons(valueref, NIL)));
}

Symbol* trueSlotName(Symbol* slotname, Surrogate* type) {
  return (canonicalSlotName(((StorageSlot*)(lookupSlot(((Class*)(type->surrogateValue)), slotname)))));
}

Cons* clTranslateFixedSlotValueTree(Cons* tree) {
  { Surrogate* objtype = ((Surrogate*)(tree->rest->value));
    Symbol* slotname = trueSlotName(((Symbol*)(tree->rest->rest->value)), objtype);
    Object* objref = clTranslateATree(tree->fourth());
    Cons* otree = yieldSlotValueReaderTree(slotname, objref, objtype);

    return (otree);
  }
}

Cons* clTranslateFixedSlotValueSetterTree(Cons* tree) {
  { Surrogate* objtype = ((Surrogate*)(tree->rest->value));
    Symbol* slotname = trueSlotName(((Symbol*)(tree->rest->rest->value)), objtype);
    Object* objref = clTranslateATree(tree->fourth());
    Object* valueref = clTranslateATree(tree->fifth());
    Cons* otree = yieldSlotValueWriterTree(slotname, objref, objtype, valueref);

    return (otree);
  }
}

Object* clTranslateCallMethodTree(Cons* tree) {
  { Symbol* operatoR = NULL;
    Surrogate* owner = NULL;
    Cons* arguments = NULL;

    operatoR = destructureCallTree(tree, owner, arguments);
    if ((operatoR == SYM_CL_TRANSLATE_STELLA_NTH) ||
        (operatoR == SYM_CL_TRANSLATE_STELLA_NTH_SETTER)) {
      return (clTranslateNthTree(tree));
    }
    else if ((operatoR == SYM_CL_TRANSLATE_STELLA_AREF) ||
        (operatoR == SYM_CL_TRANSLATE_STELLA_AREF_SETTER)) {
      return (clTranslateArefTree(tree));
    }
    else if ((operatoR == SYM_CL_TRANSLATE_STELLA_NULLp) ||
        (operatoR == SYM_CL_TRANSLATE_STELLA_DEFINEDp)) {
      return (clTranslatePlainBooleanTest(tree, false));
    }
    else {
    }
    if ((owner == SGT_CL_TRANSLATE_STELLA_ARGUMENT_LIST) ||
        (owner == SGT_CL_TRANSLATE_STELLA_ARGUMENT_LIST_ITERATOR)) {
      return (clTranslateArgumentListTree(tree));
    }
    if (((boolean)(oCL_OPERATOR_TABLEo->lookup(operatoR)))) {
      return (clTranslateOperatorTree(tree));
    }
    return (clTranslateNormalCallMethodTree(operatoR, owner, arguments));
  }
}

Object* clTranslateCallSuperMethodTree(Cons* tree) {
  tree->firstSetter(SYM_CL_TRANSLATE_STELLA_SYS_CALL_METHOD);
  { Symbol* operatoR = NULL;
    Surrogate* owner = NULL;
    Cons* arguments = NULL;

    operatoR = destructureCallTree(tree, owner, arguments);
    operatoR = internCommonLispSymbol("CALL-NEXT-METHOD");
    return (clTranslateNormalCallMethodTree(operatoR, owner, arguments));
  }
}

Symbol* methodCallTypeForVectorStructs(Symbol* slotname, Surrogate* owner, boolean functionP) {
  if (functionP ||
      ((!((boolean)(owner))) ||
       ((slotname == SYM_CL_TRANSLATE_STELLA_NULLp) ||
        ((slotname == SYM_CL_TRANSLATE_STELLA_DEFINEDp) ||
         (symbolCommonLispP(slotname) ||
          ((!oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_STRUCTS)) ||
           (!oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_VECTOR_STRUCTS)))))))) {
    return (SYM_CL_TRANSLATE_STELLA_NORMAL_CALL);
  }
  if (((!subtypeOfP(owner, SGT_CL_TRANSLATE_STELLA_OBJECT)) &&
      (!((Class*)(owner->surrogateValue))->mixinP)) ||
      ((owner == SGT_CL_TRANSLATE_STELLA_CONS) &&
       oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_CONSES))) {
    return (SYM_CL_TRANSLATE_STELLA_NON_OBJECT_METHOD);
  }
  else {
    if (slotname == SYM_CL_TRANSLATE_STELLA_PRINT_OBJECT) {
      return (SYM_CL_TRANSLATE_STELLA_PRINT_OBJECT);
    }
    else {
      return (SYM_CL_TRANSLATE_STELLA_OBJECT_METHOD);
    }
  }
}

Cons* clTranslateNormalCallMethodTree(Symbol* operatoR, Surrogate* owner, Cons* arguments) {
  { Object* translatedoperator = clTranslateGlobalSymbol(yieldRenamedNameIfNative(operatoR, KWD_CL_TRANSLATE_COMMON_LISP, KWD_CL_TRANSLATE_FUNCTION));

    { Symbol* testValue000 = methodCallTypeForVectorStructs(operatoR, owner, !((boolean)(owner)));

      if ((testValue000 == SYM_CL_TRANSLATE_STELLA_OBJECT_METHOD) ||
          (testValue000 == SYM_CL_TRANSLATE_STELLA_PRINT_OBJECT)) {
        return (cons(clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_CLSYS_CALL), cons(translatedoperator, clTranslateListOfTrees(arguments)->concatenate(NIL, 0))));
      }
      else if (testValue000 == SYM_CL_TRANSLATE_STELLA_NON_OBJECT_METHOD) {
        return (cons(translatedoperator, cons(clTranslateATree(arguments->value), cons(SYM_CL_TRANSLATE_STELLA_NULL, clTranslateListOfTrees(arguments->rest)->concatenate(NIL, 0)))));
      }
      else {
        return (cons(translatedoperator, clTranslateListOfTrees(arguments)->concatenate(NIL, 0)));
      }
    }
  }
}

Cons* clTranslateNthTree(Cons* tree) {
  { Symbol* operatoR = NULL;
    Surrogate* owner = NULL;
    Cons* arguments = NULL;

    operatoR = destructureCallTree(tree, owner, arguments);
    { boolean setterP = operatoR == SYM_CL_TRANSLATE_STELLA_NTH_SETTER;
      Object* collection = arguments->value;
      Object* position = arguments->last();
      Object* value = (setterP ? arguments->rest->value : ((Object*)(NULL)));

      if ((owner == SGT_CL_TRANSLATE_STELLA_STRING) ||
          ((owner == SGT_CL_TRANSLATE_STELLA_MUTABLE_STRING) ||
           (owner == SGT_CL_TRANSLATE_STELLA_NATIVE_VECTOR))) {
        if ((owner == SGT_CL_TRANSLATE_STELLA_NATIVE_VECTOR) ||
            methodCallInliningEnabledP()) {
          operatoR = internCommonLispSymbol("AREF");
          tree = cons(operatoR, cons(clTranslateATree(collection), cons(clTranslateATree(position), NIL)));
          if (setterP) {
            tree = listO(3, internCommonLispSymbol("SETF"), tree, cons(clTranslateATree(value), NIL));
          }
          return (tree);
        }
      }
      else {
      }
      return (clTranslateNormalCallMethodTree(operatoR, owner, arguments));
    }
  }
}

Cons* clTranslateArefTree(Cons* tree) {
  { Symbol* operatoR = NULL;
    Surrogate* owner = NULL;
    Cons* arguments = NULL;

    operatoR = destructureCallTree(tree, owner, arguments);
    if (owner == SGT_CL_TRANSLATE_STELLA_ARRAY) {
      { boolean setterP = operatoR == SYM_CL_TRANSLATE_STELLA_AREF_SETTER;
        Object* array = arguments->value;
        StandardObject* arraytype = walkedExpressionType(array);
        Cons* indices = (setterP ? arguments->rest->rest : arguments->rest);
        Object* value = (setterP ? arguments->rest->value : ((Object*)(NULL)));

        operatoR = internCommonLispSymbol("AREF");
        array = clTranslateATree(array);
        indices = clTranslateListOfTrees(indices);
        if (generateClTypeDeclarationsP()) {
          if (consP(array)) {
            array = clYieldTypedExpressionTree(array, arraytype);
          }
          { ConsIterator* it = indices->allocateIterator();

            for (; it->nextP(); ) {
              if (consP(it->value)) {
                it->valueSetter(clYieldTypedExpressionTree(it->value, SGT_CL_TRANSLATE_STELLA_INTEGER));
              }
            }
          }
        }
        tree = cons(operatoR, cons(array, indices->concatenate(NIL, 0)));
        if (setterP) {
          tree = listO(3, internCommonLispSymbol("SETF"), tree, cons(clTranslateATree(value), NIL));
        }
        return (tree);
      }
    }
    else {
      return (clTranslateNormalCallMethodTree(operatoR, owner, arguments));
    }
  }
}

Object* clTranslateArgumentListTree(Cons* tree) {
  { Symbol* operatoR = NULL;
    Surrogate* owner = NULL;
    Cons* arguments = NULL;

    operatoR = destructureCallTree(tree, owner, arguments);
    owner = owner;
    if (operatoR == SYM_CL_TRANSLATE_STELLA_ALLOCATE_ITERATOR) {
      return (clTranslateATree(arguments->value));
    }
    else if (operatoR == SYM_CL_TRANSLATE_STELLA_LENGTH) {
      return (listO(3, internCommonLispSymbol("LENGTH"), clTranslateATree(arguments->value), NIL));
    }
    else if (operatoR == SYM_CL_TRANSLATE_STELLA_NEXTp) {
      return (clTranslateATree(arguments->value));
    }
    else if (operatoR == SYM_CL_TRANSLATE_STELLA_ARGUMENT) {
      return (listO(3, internCommonLispSymbol("POP"), clTranslateATree(arguments->value), NIL));
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
      return (cons(operatoR, cons(clTranslateATree(arguments->value), NIL)));
    }
  }
}

boolean duplicateCursorVariableP(Symbol* variable, Cons* iteratorbindings) {
  { boolean foundP000 = false;

    { Cons* ib = NULL;
      Cons* iter000 = ((Cons*)(iteratorbindings));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        ib = ((Cons*)(iter000->value));
        if (ib->value == variable) {
          foundP000 = true;
          break;
        }
      }
    }
    { boolean value000 = foundP000;

      return (value000);
    }
  }
}

Cons* clTranslateForeachTree(Cons* tree) {
  { Cons* iteratorbindings = ((Cons*)(tree->rest->value));
    Cons* valuetrees = ((Cons*)(tree->rest->rest->value));
    Cons* nexttrees = ((Cons*)(tree->fourth()));
    Object* continuationtest = clTranslateBooleanTest(tree->fifth(), false);
    Cons* body = clTranslateListOfTrees(tree->nthRest(5));
    Cons* declarations = NIL;
    Cons* valueassignments = NIL;
    Cons* nextassignments = NIL;
    Cons* typedeclarations = NIL;
    Object* iteratorconstructor = NULL;

    if (generateClTypeDeclarationsP()) {
      typedeclarations = clYieldLetVariableTypeDeclarationTrees(iteratorbindings);
    }
    { Cons* binding = NULL;
      Cons* iter000 = iteratorbindings;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        binding = ((Cons*)(iter000->value));
        iteratorconstructor = clTranslateATree(binding->rest->rest->value);
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(cons(clTranslateLocalSymbol(((Symbol*)(binding->value))), cons(iteratorconstructor, NIL)), NIL);
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
            collect000->rest = cons(cons(clTranslateLocalSymbol(((Symbol*)(binding->value))), cons(iteratorconstructor, NIL)), NIL);
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
            collect001 = cons(clTranslateATree(tree), NIL);
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
            collect001->rest = cons(clTranslateATree(tree), NIL);
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
            collect002 = cons(clTranslateATree(tree), NIL);
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
            collect002->rest = cons(clTranslateATree(tree), NIL);
            collect002 = collect002->rest;
          }
        }
      }
    }
    return (listO(3, internCommonLispSymbol("LET*"), declarations, clYieldDeclareTree(typedeclarations, false)->concatenate(cons(listO(4, internCommonLispSymbol("LOOP"), SYM_CL_TRANSLATE_STELLA_WHILE, continuationtest, cons(SYM_CL_TRANSLATE_STELLA_DO, valueassignments->concatenate(maybeWrapWithContinueLabel(body)->concatenate(nextassignments->concatenate(NIL, 0), 0), 0))), NIL), 0)));
  }
}

Cons* maybeWrapWithContinueLabel(Cons* translatedloopbody) {
  if (searchConsTreeWithFilterP(translatedloopbody, KWD_CL_TRANSLATE_CONTINUE, getQuotedTree("((CL:LOOP QUOTE) \"/STELLA\")", "/STELLA"))) {
    return (cons(cons(internCommonLispSymbol("TAGBODY"), translatedloopbody->concatenate(cons(KWD_CL_TRANSLATE_CONTINUE, NIL), 0)), NIL));
  }
  else {
    return (translatedloopbody);
  }
}

Cons* clTranslateLetTree(Cons* tree, boolean specialP) {
  { Cons* odeclarations = NIL;
    Cons* typedeclarations = (generateClTypeDeclarationsP() ? clYieldLetVariableTypeDeclarationTrees(((Cons*)(tree->rest->value))) : NIL);

    { Cons* d = NULL;
      Cons* iter000 = ((Cons*)(tree->rest->value));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        d = ((Cons*)(iter000->value));
        odeclarations = cons(cons((specialP ? clTranslateGlobalSymbol(((Symbol*)(d->value))) : clTranslateLocalSymbol(((Symbol*)(d->value)))), cons(clTranslateATree(d->rest->rest->value), NIL)), odeclarations);
      }
    }
    tree->firstSetter(internCommonLispSymbol("LET*"));
    tree->secondSetter(odeclarations->reverse());
    tree->rest->rest = clYieldDeclareTree(typedeclarations, false)->concatenate(clTranslateListOfTrees(tree->rest->rest), 0);
    return (tree);
  }
}

Cons* clTranslateSpecialTree(Cons* tree) {
  { Cons* translatedtree = clTranslateLetTree(tree, true);
    Cons* specialvars = NIL;

    { Cons* decl = NULL;
      Cons* iter000 = ((Cons*)(tree->rest->value));
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        decl = ((Cons*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(decl->value, NIL);
            if (specialvars == NIL) {
              specialvars = collect000;
            }
            else {
              addConsToEndOfConsList(specialvars, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(decl->value, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    translatedtree->rest->rest = cons(listO(3, internCommonLispSymbol("DECLARE"), cons(internCommonLispSymbol("SPECIAL"), specialvars->concatenate(NIL, 0)), NIL), translatedtree->rest->rest);
    return (translatedtree);
  }
}

Cons* clTranslateStartupTimePrognTree(Cons* tree) {
  tree->value = internCommonLispSymbol("PROGN");
  tree->rest = clTranslateListOfTrees(tree->rest);
  return (listO(4, internCommonLispSymbol("EVAL-WHEN"), cons(newVerbatimStringWrapper(":LOAD-TOPLEVEL"), cons(newVerbatimStringWrapper(":EXECUTE"), NIL)), tree, NIL));
}

Cons* clTranslateUnwindProtectTree(Cons* tree) {
  tree->value = internCommonLispSymbol("UNWIND-PROTECT");
  tree->rest = clTranslateListOfTrees(tree->rest);
  return (tree);
}

Cons* clTranslateSignalTree(Cons* tree) {
  tree->value = internCommonLispSymbol("ERROR");
  tree->secondSetter(clTranslateATree(tree->rest->value));
  tree->rest->rest = NIL;
  return (tree);
}

Cons* clTranslateHandlerCaseTree(Cons* tree) {
  tree->value = internCommonLispSymbol("HANDLER-CASE");
  tree->rest = clTranslateListOfTrees(tree->rest);
  return (tree);
}

Cons* clTranslateHandleExceptionTree(Cons* tree) {
  { Symbol* var = ((Symbol*)(((Cons*)(tree->rest->value))->value));
    StandardObject* type = ((StandardObject*)(((Cons*)(tree->rest->value))->rest->value));

    tree->value = clTranslateClassName(typeToClass(typeSpecToBaseType(type)));
    if (((boolean)(var))) {
      tree->secondSetter(cons(clTranslateLocalSymbol(var), NIL));
    }
    else {
      tree->secondSetter(NIL);
    }
    tree->rest->rest = clTranslateListOfTrees(tree->rest->rest);
    return (tree);
  }
}

Object* cast(Object* value, Surrogate* type) {
  // Perform a run-time type check, and then return `value'.
  if ((oSAFETYo >= 2) &&
      ((oSTARTUP_TIME_PHASEo == 999) &&
       oUNFINALIZED_CLASSESo->emptyP())) {
    if (((boolean)(value)) &&
        (!isaP(value, type))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Run-time casting violation.  The value: " << std::endl << "`" << value << "'" << std::endl << " is not of type " << "`" << type << "'" << ".";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
  return (value);
}

NumberWrapper* coerceNumericConstant(NumberWrapper* constant, Surrogate* type) {
  { Surrogate* testValue000 = safePrimaryType(constant);

    if (subtypeOfIntegerP(testValue000)) {
      { NumberWrapper* constant000 = constant;
        IntegerWrapper* constant = ((IntegerWrapper*)(constant000));

        if (subtypeOfP(type, SGT_CL_TRANSLATE_STELLA_FLOAT)) {
          return (wrapFloat(coerceToFloat(constant)));
        }
        else if (subtypeOfP(type, SGT_CL_TRANSLATE_STELLA_INTEGER)) {
          return (constant);
        }
        else if (subtypeOfP(type, SGT_CL_TRANSLATE_STELLA_LONG_INTEGER)) {
          return (wrapLongInteger(((long long int)(constant->wrapperValue))));
        }
      }
    }
    else if (subtypeOfLongIntegerP(testValue000)) {
      { NumberWrapper* constant001 = constant;
        LongIntegerWrapper* constant = ((LongIntegerWrapper*)(constant001));

        if (subtypeOfP(type, SGT_CL_TRANSLATE_STELLA_FLOAT)) {
          return (wrapFloat(coerceToFloat(constant)));
        }
        else if (subtypeOfP(type, SGT_CL_TRANSLATE_STELLA_INTEGER)) {
          return (wrapInteger(((int)(constant->wrapperValue))));
        }
        else if (subtypeOfP(type, SGT_CL_TRANSLATE_STELLA_LONG_INTEGER)) {
          return (constant);
        }
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { NumberWrapper* constant002 = constant;
        FloatWrapper* constant = ((FloatWrapper*)(constant002));

        if (subtypeOfP(type, SGT_CL_TRANSLATE_STELLA_FLOAT)) {
          return (constant);
        }
        else if (subtypeOfP(type, SGT_CL_TRANSLATE_STELLA_INTEGER)) {
          return (wrapInteger(((int)(constant->wrapperValue))));
        }
        else if (subtypeOfP(type, SGT_CL_TRANSLATE_STELLA_LONG_INTEGER)) {
          return (wrapLongInteger(((long long int)(constant->wrapperValue))));
        }
      }
    }
    else {
    }
  }
  return (constant);
}

Object* clTranslateCastTree(Cons* tree) {
  { Object* expression = tree->rest->value;
    Surrogate* type = typeSpecToBaseType(((StandardObject*)(tree->rest->rest->value)));

    tree->secondSetter(clTranslateATree(expression));
    tree->thirdSetter(clTranslateATree(type));
    if (subtypeOfP(type, SGT_CL_TRANSLATE_STELLA_NUMBER) &&
        isaP(expression, SGT_CL_TRANSLATE_STELLA_NUMBER_WRAPPER)) {
      return (coerceNumericConstant(((NumberWrapper*)(expression)), type)->clTranslateAtomicTree());
    }
    else if (subtypeOfP(type, SGT_CL_TRANSLATE_STELLA_FLOAT)) {
      return (listO(3, internCommonLispSymbol("FLOAT"), tree->rest->value, cons(newVerbatimStringWrapper("0.0d0"), NIL)));
    }
    else if (subtypeOfP(type, SGT_CL_TRANSLATE_STELLA_INTEGER) ||
        subtypeOfP(type, SGT_CL_TRANSLATE_STELLA_LONG_INTEGER)) {
      return (listO(3, internCommonLispSymbol("TRUNCATE"), tree->rest->value, NIL));
    }
    if ((oSAFETYo < 2) ||
        ((tree->value == SYM_CL_TRANSLATE_STELLA_SAFE_CAST) ||
         (!((boolean)(lookupSlot(typeToClass(type), SYM_CL_TRANSLATE_STELLA_PRIMARY_TYPE)))))) {
      expression = tree->rest->value;
      tree->secondSetter(NIL);
      return (expression);
    }
    tree->firstSetter(clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_CAST));
    return (tree);
  }
}

Object* clTranslateReturnTree(Cons* tree) {
  { Cons* returnvalues = clTranslateListOfTrees(tree->rest);

    if (!(returnvalues->rest == NIL)) {
      returnvalues = cons(cons(internCommonLispSymbol("VALUES"), returnvalues->concatenate(NIL, 0)), NIL);
    }
    return ((((!oNEEDEXPLICITRETURNpo) &&
        preserveTailMergeOptimizabilityP()) ? returnvalues->value : listO(3, internCommonLispSymbol("RETURN-FROM"), clTranslateGlobalSymbol(yieldRenamedNameIfNative(((MethodSlot*)(oCURRENTTRANSLATIONUNITo->theObject))->slotName, KWD_CL_TRANSLATE_COMMON_LISP, KWD_CL_TRANSLATE_FUNCTION)), returnvalues->concatenate(NIL, 0))));
  }
}

Object* clTranslateBooleanTest(Object* tree, boolean invertP) {
  if (safePrimaryType(tree) == SGT_CL_TRANSLATE_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if (testValue000 == SYM_CL_TRANSLATE_STELLA_NOT) {
          { Object* postree = tree->rest->value;

            return (clTranslateBooleanTest(postree, !invertP));
          }
        }
        else if ((testValue000 == SYM_CL_TRANSLATE_STELLA_AND) ||
            (testValue000 == SYM_CL_TRANSLATE_STELLA_OR)) {
          { Cons* cursor = tree->rest;

            while (!(cursor == NIL)) {
              cursor->value = clTranslateBooleanTest(cursor->value, false);
              cursor = cursor->rest;
            }
          }
          if (tree->value == SYM_CL_TRANSLATE_STELLA_AND) {
            tree->firstSetter(internCommonLispSymbol("AND"));
          }
          else {
            tree->firstSetter(internCommonLispSymbol("OR"));
          }
          if (invertP) {
            tree = listO(3, internCommonLispSymbol("NOT"), tree, NIL);
          }
          return (tree);
        }
        else if (testValue000 == SYM_CL_TRANSLATE_STELLA_TYPED_SYS) {
          return (clTranslateBooleanTest(tree->rest->value, invertP));
        }
        else {
        }
      }
    }
  }
  else {
  }
  return (clTranslatePlainBooleanTest(tree, invertP));
}

Object* clTranslatePlainBooleanTest(Object* tree, boolean invertP) {
  if (safePrimaryType(tree) == SGT_CL_TRANSLATE_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { Symbol* operatoR = NULL;
        Surrogate* owner = NULL;
        Cons* arguments = NULL;

        operatoR = destructureCallTree(tree, owner, arguments);
        if ((operatoR == SYM_CL_TRANSLATE_STELLA_l) ||
            ((operatoR == SYM_CL_TRANSLATE_STELLA_le) ||
             ((operatoR == SYM_CL_TRANSLATE_STELLA_e) ||
              ((operatoR == SYM_CL_TRANSLATE_STELLA_ge) ||
               (operatoR == SYM_CL_TRANSLATE_STELLA_g))))) {
          if (optimizeBooleanTestsP()) {
            if (invertP) {
              if (operatoR == SYM_CL_TRANSLATE_STELLA_l) {
                operatoR = SYM_CL_TRANSLATE_STELLA_ge;
              }
              else if (operatoR == SYM_CL_TRANSLATE_STELLA_le) {
                operatoR = SYM_CL_TRANSLATE_STELLA_g;
              }
              else if (operatoR == SYM_CL_TRANSLATE_STELLA_e) {
                operatoR = SYM_CL_TRANSLATE_STELLA_xe;
              }
              else if (operatoR == SYM_CL_TRANSLATE_STELLA_ge) {
                operatoR = SYM_CL_TRANSLATE_STELLA_l;
              }
              else if (operatoR == SYM_CL_TRANSLATE_STELLA_g) {
                operatoR = SYM_CL_TRANSLATE_STELLA_le;
              }
              else {
                { OutputStringStream* stream000 = newOutputStringStream();

                  *(stream000->nativeStream) << "`" << operatoR << "'" << " is not a valid case option";
                  throw *newStellaException(stream000->theStringReader());
                }
              }
              invertP = false;
            }
          }
          tree = cons(oCL_OPERATOR_TABLEo->lookup(operatoR), clTranslateListOfTrees(arguments)->concatenate(NIL, 0));
          if (invertP) {
            return (listO(3, internCommonLispSymbol("NOT"), tree, NIL));
          }
          else {
            return (tree);
          }
        }
        else if (operatoR == SYM_CL_TRANSLATE_STELLA_EQp) {
          if (optimizeBooleanTestsP()) {
            { StandardObject* argtype1 = walkedExpressionType(arguments->value);
              StandardObject* argtype2 = walkedExpressionType(arguments->rest->value);

              if (subTypeSpecOfP(argtype1, SGT_CL_TRANSLATE_STELLA_LITERAL) &&
                  subTypeSpecOfP(argtype2, SGT_CL_TRANSLATE_STELLA_LITERAL)) {
                if ((argtype1 == SGT_CL_TRANSLATE_STELLA_STRING) ||
                    subTypeSpecOfP(argtype1, SGT_CL_TRANSLATE_STELLA_BOOLEAN)) {
                  operatoR = internCommonLispSymbol("EQ");
                }
                else if (subTypeSpecOfP(argtype1, SGT_CL_TRANSLATE_STELLA_NUMBER)) {
                  operatoR = internCommonLispSymbol("=");
                }
                else {
                  operatoR = internCommonLispSymbol("EQL");
                }
              }
              else {
                operatoR = internCommonLispSymbol("EQ");
              }
              tree->firstSetter(operatoR);
            }
          }
          tree->rest = clTranslateListOfTrees(tree->rest);
          if (invertP) {
            return (listO(3, internCommonLispSymbol("NOT"), tree, NIL));
          }
          else {
            return (tree);
          }
        }
        else if ((operatoR == SYM_CL_TRANSLATE_STELLA_NULLp) ||
            (operatoR == SYM_CL_TRANSLATE_STELLA_DEFINEDp)) {
          if (methodCallInliningEnabledP()) {
            if ((owner == SGT_CL_TRANSLATE_STELLA_OBJECT) ||
                ((owner == SGT_CL_TRANSLATE_STELLA_SECOND_CLASS_OBJECT) ||
                 ((owner == SGT_CL_TRANSLATE_STELLA_STRING) ||
                  ((owner == SGT_CL_TRANSLATE_STELLA_NATIVE_VECTOR) ||
                   ((owner == SGT_CL_TRANSLATE_STELLA_ARRAY) ||
                    ((owner == SGT_CL_TRANSLATE_STELLA_INTEGER) ||
                     ((owner == SGT_CL_TRANSLATE_STELLA_LONG_INTEGER) ||
                      ((owner == SGT_CL_TRANSLATE_STELLA_FLOAT) ||
                       (owner == SGT_CL_TRANSLATE_STELLA_CODE))))))))) {
              if (owner == SGT_CL_TRANSLATE_STELLA_ARRAY) {
                tree = cons(clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_NULL_ARRAYp), cons(clTranslateATree(arguments->value), NIL));
              }
              else {
                tree = cons((subtypeOfP(owner, SGT_CL_TRANSLATE_STELLA_NUMBER) ? internCommonLispSymbol("=") : internCommonLispSymbol("EQ")), cons(clTranslateATree(arguments->value), cons(clTranslateATree(typeToWalkedNullValueTree(owner, owner)), NIL)));
              }
              if (owner == SGT_CL_TRANSLATE_STELLA_FLOAT) {
                tree->firstSetter(internCommonLispSymbol("="));
              }
              else {
              }
              if ((invertP &&
                  (operatoR == SYM_CL_TRANSLATE_STELLA_NULLp)) ||
                  ((!invertP) &&
                   (operatoR == SYM_CL_TRANSLATE_STELLA_DEFINEDp))) {
                return (listO(3, internCommonLispSymbol("NOT"), tree, NIL));
              }
              else {
                return (tree);
              }
            }
            else {
            }
          }
          tree = cons(clTranslateGlobalSymbol(operatoR), cons(clTranslateATree(arguments->value), NIL));
          if (invertP) {
            return (listO(3, internCommonLispSymbol("NOT"), tree, NIL));
          }
          else {
            return (tree);
          }
        }
        else {
        }
      }
    }
  }
  else {
  }
  tree = clTranslateATree(tree);
  if (invertP) {
    return (listO(3, internCommonLispSymbol("NOT"), tree, NIL));
  }
  else {
    return (tree);
  }
}

Cons* clTranslateWhileTree(Cons* tree) {
  { Object* test = clTranslateBooleanTest(tree->rest->value, false);
    Cons* body = clTranslateListOfTrees(tree->rest->rest);

    tree->rest->rest = NIL;
    return (((body == NIL) ? listO(4, internCommonLispSymbol("LOOP"), SYM_CL_TRANSLATE_STELLA_WHILE, test, NIL) : listO(4, internCommonLispSymbol("LOOP"), SYM_CL_TRANSLATE_STELLA_WHILE, test, cons(SYM_CL_TRANSLATE_STELLA_DO, maybeWrapWithContinueLabel(body)->concatenate(NIL, 0)))));
  }
}

Cons* clTranslateConditionalTree(Cons* tree) {
  { Object* operatoR = tree->value;
    Object* test = tree->rest->value;
    Cons* body = tree->rest->rest;

    tree->rest->rest = NIL;
    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(operatoR));

      if ((testValue000 == SYM_CL_TRANSLATE_STELLA_IF) ||
          (testValue000 == SYM_CL_TRANSLATE_STELLA_CHOOSE)) {
        return (listO(3, internCommonLispSymbol("IF"), clTranslateBooleanTest(test, false), cons(clTranslateATree(body->value), cons(clTranslateATree(body->rest->value), NIL))));
      }
      else if (testValue000 == SYM_CL_TRANSLATE_STELLA_WHEN) {
        return (listO(3, internCommonLispSymbol("WHEN"), clTranslateBooleanTest(test, false), clTranslateListOfTrees(body)->concatenate(NIL, 0)));
      }
      else if (testValue000 == SYM_CL_TRANSLATE_STELLA_UNLESS) {
        return (listO(3, internCommonLispSymbol("WHEN"), clTranslateBooleanTest(test, true), clTranslateListOfTrees(body)->concatenate(NIL, 0)));
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

Cons* clTranslateCondTree(Cons* tree) {
  { Cons* condition = NULL;
    Cons* iter000 = ((Cons*)(tree->rest));

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      condition = ((Cons*)(iter000->value));
      if (condition->value == SYM_CL_TRANSLATE_STELLA_OTHERWISE) {
        condition->value = internCommonLispSymbol("T");
      }
      else {
        condition->value = clTranslateBooleanTest(condition->value, false);
      }
      condition->rest = clTranslateListOfTrees(condition->rest);
    }
  }
  tree->value = internCommonLispSymbol("COND");
  return (tree);
}

Cons* clTranslateCaseTree(Cons* tree) {
  { boolean otherwiseP = false;

    tree->secondSetter(clTranslateATree(tree->rest->value));
    { Cons* cond = NULL;
      Cons* iter000 = ((Cons*)(tree->rest->rest));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        cond = ((Cons*)(iter000->value));
        if (cond->value == SYM_CL_TRANSLATE_STELLA_OTHERWISE) {
          otherwiseP = true;
          cond->firstSetter(internCommonLispSymbol("OTHERWISE"));
        }
        else if (consP(cond->value)) {
          cond->firstSetter(clTranslateListOfTrees(((Cons*)(cond->value))));
        }
        else {
          cond->firstSetter(clTranslateATree(cond->value));
        }
        cond->rest = clTranslateListOfTrees(cond->rest);
      }
    }
    tree->firstSetter((otherwiseP ? internCommonLispSymbol("CASE") : internCommonLispSymbol("ECASE")));
    return (tree);
  }
}

Cons* clTranslateBooleanTree(Cons* tree) {
  return (((Cons*)(clTranslateBooleanTest(tree, false))));
}

Object* clTranslateClassName(Class* clasS) {
  if (oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_CONSES)) {
    if (clasS->classType == SGT_CL_TRANSLATE_STELLA_CONS) {
      return (internCommonLispSymbol("CONS"));
    }
    else {
    }
  }
  if (((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_CL_TRANSLATE_STELLA_CLASS_CL_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue != NULL) {
    { const char* nativetype = ((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_CL_TRANSLATE_STELLA_CLASS_CL_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue;

      if (!(stringPosition(nativetype, ':', 0) != NULL_INTEGER)) {
        nativetype = stringConcatenate("CL:", nativetype, 0);
      }
      return (newVerbatimStringWrapper(nativetype));
    }
  }
  else {
    return (clTranslateGlobalSymbol(classSymbol(clasS)));
  }
}

Object* yieldStructConstructorName(Class* clasS) {
  return (yieldGlobalLispSymbol(((Module*)(clasS->classType->homeContext)), stringConcatenate("%MAKE-", clasS->classType->symbolName, 0)));
}

Cons* clTranslateMakeTree(Cons* tree) {
  { Class* clasS = ((Class*)(typify(tree->rest->value)->surrogateValue));
    Object* classsymbol = clTranslateClassName(clasS);
    Cons* otree = NULL;

    if ((classsymbol == internCommonLispSymbol("CONS")) &&
        oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_CONSES)) {
      return (listO(4, internCommonLispSymbol("CONS"), internCommonLispSymbol("NIL"), internCommonLispSymbol("NIL"), NIL));
    }
    if (exceptionClassP(clasS)) {
      otree = listO(4, internCommonLispSymbol("MAKE-CONDITION"), listO(3, internCommonLispSymbol("QUOTE"), classsymbol, NIL), clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_oCONDITION_MESSAGE_KEYWORDo), cons(cons(clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_REPLACE_SUBSTRINGS), cons(clTranslateATree(tree->rest->rest->value), listO(3, wrapString("~~"), wrapString("~"), NIL))), NIL));
    }
    else if ((!oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_STRUCTS)) ||
        clAlwaysTranslateToClosClassP(clasS)) {
      otree = listO(3, internCommonLispSymbol("MAKE-INSTANCE"), listO(3, internCommonLispSymbol("QUOTE"), classsymbol, NIL), NIL);
    }
    else if (oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_VECTOR_STRUCTS)) {
      otree = cons(clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_CLSYS_MAKE), cons(classsymbol, cons(wrapInteger(clStructSlots(clasS)->length() + 1), NIL)));
    }
    else {
      otree = cons(yieldStructConstructorName(clasS), NIL);
    }
    return (otree);
  }
}

Cons* clTranslateNewTree(Cons* tree) {
  if (arrayTypeSpecifierP(((StandardObject*)(tree->rest->value)))) {
    return (clTranslateNewArrayTree(tree));
  }
  { Object* typespec = tree->rest->value;
    Object* constructorname = clTranslateGlobalSymbol(yieldConstructorName(((typeP(typespec) ? ((Surrogate*)(typespec)) : ((ParametricTypeSpecifier*)(typespec))->specifierBaseType))->getStellaClass(true)));
    Cons* requiredargrefs = clTranslateListOfTrees(tree->rest->rest);

    return (cons(constructorname, requiredargrefs->concatenate(NIL, 0)));
  }
}

Cons* clTranslateNewArrayTree(Cons* tree) {
  { Object* initialelement = tree->rest->rest->value;
    Cons* dimensions = clTranslateListOfTrees(tree->rest->rest->rest);

    initialelement = NULL;
    return (listO(3, internCommonLispSymbol("MAKE-ARRAY"), ((dimensions->length() == 1) ? dimensions->value : cons(internCommonLispSymbol("LIST"), dimensions->concatenate(NIL, 0))), ((((boolean)(initialelement)) ? listO(3, KWD_CL_TRANSLATE_INITIAL_ELEMENT, clTranslateATree(initialelement), NIL) : NIL))->concatenate(NIL, 0)));
  }
}

Cons* clTranslateOperatorTree(Cons* tree) {
  { Symbol* operatoR = NULL;
    Surrogate* owner = NULL;
    Cons* arguments = NULL;

    operatoR = destructureCallTree(tree, owner, arguments);
    owner = owner;
    if (operatoR == SYM_CL_TRANSLATE_STELLA_i) {
      if ((arguments->length() == 2) &&
          arguments->memberP(ONE_WRAPPER)) {
        if (eqlP(arguments->value, ONE_WRAPPER)) {
          arguments = arguments->rest;
        }
        else {
          arguments->rest = NIL;
        }
        operatoR = internCommonLispSymbol("1+");
      }
    }
    else if (operatoR == SYM_CL_TRANSLATE_STELLA__) {
      if ((arguments->length() == 2) &&
          eqlP(arguments->rest->value, ONE_WRAPPER)) {
        arguments->rest = NIL;
        operatoR = internCommonLispSymbol("1-");
      }
    }
    else if (operatoR == SYM_CL_TRANSLATE_STELLA_EQp) {
      return (((Cons*)(clTranslatePlainBooleanTest(tree, false))));
    }
    else {
    }
    if ((operatoR == SYM_CL_TRANSLATE_STELLA_i) ||
        ((operatoR == SYM_CL_TRANSLATE_STELLA__) ||
         ((operatoR == SYM_CL_TRANSLATE_STELLA_o) ||
          (operatoR == SYM_CL_TRANSLATE_STELLA_s)))) {
      operatoR = ((Symbol*)(oCL_OPERATOR_TABLEo->lookup(operatoR)));
    }
    else {
    }
    return (cons(clTranslateGlobalSymbol(operatoR), clTranslateListOfTrees(arguments)->concatenate(NIL, 0)));
  }
}

Cons* yieldFormatArguments(Cons* tree) {
  { const char* formatstring = "";
    Cons* formatarguments = NIL;

    tree->rest->rest = tree->rest->rest->reverse();
    { Object* arg = NULL;
      Cons* iter000 = tree->rest->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        arg = iter000->value;
        if (stringP(arg)) {
          formatstring = stringConcatenate(((StringWrapper*)(arg))->wrapperValue, formatstring, 0);
        }
        else if (arg == EOL) {
          formatstring = stringConcatenate("~%", formatstring, 0);
        }
        else {
          formatstring = stringConcatenate("~A", formatstring, 0);
          formatarguments = cons(clTranslateATree(arg), formatarguments);
        }
      }
    }
    formatarguments = cons(wrapString(formatstring), formatarguments);
    return (formatarguments);
  }
}

Cons* yieldPrintTree(Cons* tree) {
  { Object* stream = tree->rest->value;
    Cons* arguments = tree->rest->rest;
    Surrogate* argumenttype = NULL;
    Symbol* printoperator = NULL;
    const char* compoundedstring = NULL;
    Cons* printforms = NIL;

    stream = clTranslateATree(stream);
    { Object* arg = NULL;
      Cons* iter000 = arguments;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        arg = iter000->value;
        if (arg == EOL) {
          printforms = cons(arg, printforms);
          compoundedstring = NULL;
        }
        else {
          argumenttype = typeSpecToBaseType(walkedExpressionType(arg));
          if (argumenttype == SGT_CL_TRANSLATE_STELLA_STRING) {
            printoperator = internCommonLispSymbol("WRITE-STRING");
          }
          else {
            if (subtypeOfP(argumenttype, SGT_CL_TRANSLATE_STELLA_OBJECT)) {
              printoperator = SYM_CL_TRANSLATE_STELLA_PRINT_OBJECT;
            }
            else {
              printoperator = internCommonLispSymbol("PRINC");
            }
          }
          if (subtypeOfStringP(safePrimaryType(arg))) {
            { Object* arg000 = arg;
              StringWrapper* arg = ((StringWrapper*)(arg000));

              if (compoundedstring != NULL) {
                compoundedstring = stringConcatenate(compoundedstring, arg->wrapperValue, 0);
                printforms->firstSetter(wrapString(compoundedstring));
                continue;
              }
              compoundedstring = arg->wrapperValue;
            }
          }
          else {
            compoundedstring = NULL;
          }
          if (methodCallTypeForVectorStructs(printoperator, argumenttype, !(printoperator == SYM_CL_TRANSLATE_STELLA_PRINT_OBJECT)) == SYM_CL_TRANSLATE_STELLA_PRINT_OBJECT) {
            printforms = cons(clTranslateATree(arg), printforms);
          }
          else {
            printforms = cons(clTranslateATree(arg), printforms);
          }
        }
      }
    }
    printforms = printforms->reverse();
    return (cons(clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_rrPRINT_STREAM), cons(stream, printforms->concatenate(NIL, 0))));
  }
}

Cons* clTranslatePrintStreamTree(Cons* tree) {
  { Object* stream = tree->rest->value;

    if (stream == KWD_CL_TRANSLATE_WARN) {
      return (cons(internCommonLispSymbol("WARN"), yieldFormatArguments(tree)->concatenate(NIL, 0)));
    }
    else if (stream == KWD_CL_TRANSLATE_ERROR) {
      return (cons(internCommonLispSymbol("ERROR"), yieldFormatArguments(tree)->concatenate(NIL, 0)));
    }
    else if (stream == KWD_CL_TRANSLATE_CONTINUABLE_ERROR) {
      return (listO(3, internCommonLispSymbol("CERROR"), wrapString("Continue anyway? "), yieldFormatArguments(tree)->concatenate(NIL, 0)));
    }
    else {
      return (yieldPrintTree(tree));
    }
  }
}

Cons* clTranslateCallFunctionCodeTree(Cons* tree) {
  { boolean methodcodeP = tree->value == SYM_CL_TRANSLATE_STELLA_SYS_CALL_METHOD_CODE;
    Cons* otree = tree->rest;

    otree->rest = clTranslateListOfTrees(otree->rest);
    otree->firstSetter(((methodcodeP &&
        oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_VECTOR_STRUCTS)) ? SYM_CL_TRANSLATE_STELLA_CLSYS_METHOD_CODE_CALL : internCommonLispSymbol("FUNCALL")));
    return (otree);
  }
}

Object* clTranslateInlineCallTree(Cons* tree) {
  { StandardObject* dummy1;

    { Cons* calltree = ((Cons*)(tree->rest->value));
      MethodSlot* method = ((MethodSlot*)(slotFromExpressionTree(calltree)));
      Cons* args = ((calltree->value == SYM_CL_TRANSLATE_STELLA_SYS_CALL_FUNCTION) ? calltree->nthRest(2) : calltree->nthRest(3));
      Cons* translatedargs = clTranslateListOfTrees(args);
      Cons* usedcomplexargs = NIL;
      Object* argument = NULL;
      Object* body = lookupVerbatimTree(((Cons*)(walkVerbatimTree(((Cons*)(inlinableMethodBody(method))), dummy1))), NULL);
      List* parameters = method->methodParameterNames_reader();
      List* parametertypes = method->methodParameterTypeSpecifiers_reader();
      int parindex = 0;
      Cons* otree = NIL;

      if (safePrimaryType(body) == SGT_CL_TRANSLATE_STELLA_CONS) {
        { Object* body000 = body;
          Cons* body = ((Cons*)(body000));

          { boolean alwaysP000 = true;

            { Object* elt = NULL;
              Cons* iter000 = body;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                elt = iter000->value;
                if (!(!consP(elt))) {
                  alwaysP000 = false;
                  break;
                }
              }
            }
            if (alwaysP000) {
              otree = cons(clTranslateVerbatimBodySymbols(body->value, NIL_LIST), NIL);
              { Object* barg = NULL;
                Cons* iter001 = body->rest;

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  barg = iter001->value;
                  if (parameters->memberP(barg)) {
                    parindex = parameters->position(barg, 0);
                    argument = translatedargs->nth(parindex);
                    if (usedcomplexargs->memberP(argument)) {
                      otree = NIL;
                      break;
                    }
                    if (consP(argument)) {
                      usedcomplexargs = cons(argument, usedcomplexargs);
                      argument = clYieldTypedExpressionTree(argument, ((StandardObject*)(parametertypes->nth(parindex))));
                    }
                    otree = cons(argument, otree);
                  }
                  else {
                    otree = cons(clTranslateVerbatimBodySymbols(barg, NIL_LIST), otree);
                  }
                }
              }
              if (!(otree == NIL)) {
                return (clYieldTypedExpressionTree(otree->reverse(), method->type()));
              }
            }
          }
        }
      }
      else {
      }
      { Symbol* par = NULL;
        Cons* iter002 = parameters->theConsList;
        Object* arg = NULL;
        Cons* iter003 = translatedargs;
        Cons* collect000 = NULL;

        for  (; (!(iter002 == NIL)) &&
                  (!(iter003 == NIL)); 
              iter002 = iter002->rest,
              iter003 = iter003->rest) {
          par = ((Symbol*)(iter002->value));
          arg = iter003->value;
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(cons(clTranslateLocalSymbol(par), cons(arg, NIL)), NIL);
              if (otree == NIL) {
                otree = collect000;
              }
              else {
                addConsToEndOfConsList(otree, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(cons(clTranslateLocalSymbol(par), cons(arg, NIL)), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      return (listO(3, internCommonLispSymbol("LET"), otree, clYieldDeclareTree(clYieldMethodParameterTypeDeclarationTrees(method), false)->concatenate(cons(clYieldTypedExpressionTree(clTranslateVerbatimBodySymbols(copyConsTree(body), parameters), method->type()), NIL), 0)));
    }
  }
}

Object* clTranslateVerbatimBodySymbols(Object* body, List* parameters) {
  { Surrogate* testValue000 = safePrimaryType(body);

    if (testValue000 == SGT_CL_TRANSLATE_STELLA_CONS) {
      { Object* body000 = body;
        Cons* body = ((Cons*)(body000));

        if (!(body == NIL)) {
          return (cons(clTranslateVerbatimBodySymbols(body->value, parameters), ((Cons*)(clTranslateVerbatimBodySymbols(body->rest, parameters)))));
        }
        else {
          return (NIL);
        }
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* body001 = body;
        Symbol* body = ((Symbol*)(body001));

        if (parameters->memberP(body)) {
          return (clTranslateLocalSymbol(body));
        }
        else {
          return (clTranslateGlobalSymbol(body));
        }
      }
    }
    else {
      return (body);
    }
  }
}

Cons* clTranslateTheCodeTree(Cons* tree) {
  { Symbol* name = ((tree->rest->value == KWD_CL_TRANSLATE_FUNCTION) ? ((Symbol*)(tree->rest->rest->value)) : ((Symbol*)(tree->fourth())));

    return (listO(3, internCommonLispSymbol("FUNCTION"), clTranslateGlobalSymbol(yieldRenamedNameIfNative(name, KWD_CL_TRANSLATE_COMMON_LISP, KWD_CL_TRANSLATE_FUNCTION)), NIL));
  }
}

Object* clTranslateVerbatimTree(Cons* tree) {
  { Cons* cursor = tree->rest;
    Object* verbatimcode = NULL;

    while (!(cursor == NIL)) {
      if (cursor->value == KWD_CL_TRANSLATE_COMMON_LISP) {
        verbatimcode = cursor->rest->value;
        cursor->rest->value = NULL;
        break;
      }
      cursor = cursor->rest->rest;
    }
    return (verbatimcode);
  }
}

Cons* clTranslateInlineTree(Cons* tree) {
  { Object* operatoR = tree->value;
    Cons* body = clTranslateListOfTrees(tree->rest);

    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(operatoR));

      if (testValue000 == SYM_CL_TRANSLATE_STELLA_INLINE) {
        operatoR = internCommonLispSymbol("INLINE");
      }
      else if (testValue000 == SYM_CL_TRANSLATE_STELLA_IGNORE) {
        operatoR = internCommonLispSymbol("IGNORE");
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    return (listO(3, internCommonLispSymbol("DECLARE"), cons(operatoR, body->concatenate(NIL, 0)), NIL));
  }
}

boolean generateClTypeDeclarationsP() {
  return (methodCallInliningEnabledP());
}

Object* lookupClTypeFromStellaType(StandardObject* type) {
  if ((!((boolean)(type))) ||
      anchoredTypeSpecifierP(type)) {
    return (NULL);
  }
  { Surrogate* basetype = typeSpecToBaseType(type);

    if (basetype == SGT_CL_TRANSLATE_STELLA_INTEGER) {
      return (internCommonLispSymbol("FIXNUM"));
    }
    else if (basetype == SGT_CL_TRANSLATE_STELLA_SHORT_INTEGER) {
      return (internCommonLispSymbol("FIXNUM"));
    }
    else if (basetype == SGT_CL_TRANSLATE_STELLA_FLOAT) {
      return (internCommonLispSymbol("DOUBLE-FLOAT"));
    }
    else if (basetype == SGT_CL_TRANSLATE_STELLA_STRING) {
      return (internCommonLispSymbol("SIMPLE-STRING"));
    }
    else if (basetype == SGT_CL_TRANSLATE_STELLA_MUTABLE_STRING) {
      return (internCommonLispSymbol("SIMPLE-STRING"));
    }
    else if (basetype == SGT_CL_TRANSLATE_STELLA_NATIVE_VECTOR) {
      return (internCommonLispSymbol("SIMPLE-VECTOR"));
    }
    else if (basetype == SGT_CL_TRANSLATE_STELLA_ARRAY) {
      if (arrayTypeSpecifierP(type)) {
        switch (arrayTypeRank(((ParametricTypeSpecifier*)(type)))) {
          case 1: 
            return (internCommonLispSymbol("SIMPLE-VECTOR"));
          default:
            { int rank = arrayTypeRank(((ParametricTypeSpecifier*)(type)));
              Cons* dimensions = NIL;

              if (rank <= 5) {
                { IntegerWrapper* dim = NULL;
                  Cons* iter000 = arrayTypeDimensions(((ParametricTypeSpecifier*)(type)))->theConsList;
                  Cons* collect000 = NULL;

                  for  (; !(iter000 == NIL); 
                        iter000 = iter000->rest) {
                    dim = ((IntegerWrapper*)(iter000->value));
                    if (!((boolean)(collect000))) {
                      {
                        collect000 = cons(((!((boolean)(dim))) ? ((Object*)(internCommonLispSymbol("*"))) : ((Object*)(dim))), NIL);
                        if (dimensions == NIL) {
                          dimensions = collect000;
                        }
                        else {
                          addConsToEndOfConsList(dimensions, collect000);
                        }
                      }
                    }
                    else {
                      {
                        collect000->rest = cons(((!((boolean)(dim))) ? ((Object*)(internCommonLispSymbol("*"))) : ((Object*)(dim))), NIL);
                        collect000 = collect000->rest;
                      }
                    }
                  }
                }
                return (listO(4, internCommonLispSymbol("ARRAY"), internCommonLispSymbol("T"), dimensions, NIL));
              }
            }
            break;
        }
      }
    }
    else {
    }
    return (NULL);
  }
}

Object* clYieldTypedExpressionTree(Object* tree, StandardObject* type) {
  { Object* cltype = lookupClTypeFromStellaType(type);

    if (((boolean)(cltype))) {
      if (safePrimaryType(tree) == SGT_CL_TRANSLATE_STELLA_CONS) {
        { Object* tree000 = tree;
          Cons* tree = ((Cons*)(tree000));

          if ((tree->value == internCommonLispSymbol("THE")) &&
              eqlP(tree->rest->value, cltype)) {
            return (tree);
          }
        }
      }
      else {
      }
      return (listO(3, internCommonLispSymbol("THE"), cltype, cons(tree, NIL)));
    }
    else {
      return (tree);
    }
  }
}

Cons* clYieldMethodParameterTypeDeclarationTrees(MethodSlot* method) {
  { Cons* types = NIL;
    Symbol* cltype = NULL;

    { StandardObject* tspec = NULL;
      Cons* iter000 = method->methodParameterTypeSpecifiers_reader()->theConsList;
      Symbol* pname = NULL;
      Cons* iter001 = method->methodParameterNames_reader()->theConsList;

      for  (; (!(iter000 == NIL)) &&
                (!(iter001 == NIL)); 
            iter000 = iter000->rest,
            iter001 = iter001->rest) {
        tspec = ((StandardObject*)(iter000->value));
        pname = ((Symbol*)(iter001->value));
        cltype = ((Symbol*)(lookupClTypeFromStellaType(computeRelativeTypeSpec(tspec, method->slotOwner))));
        if (((boolean)(cltype))) {
          types = cons(listO(3, internCommonLispSymbol("TYPE"), cltype, cons(clTranslateLocalSymbol(pname), NIL)), types);
        }
      }
    }
    return (types->reverse());
  }
}

Cons* clYieldLetVariableTypeDeclarationTrees(Cons* bindingstree) {
  { Cons* types = NIL;
    Symbol* cltype = NULL;

    { Cons* binding = NULL;
      Cons* iter000 = bindingstree;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        binding = ((Cons*)(iter000->value));
        { Object* type = binding->rest->value;

          if (((boolean)(type))) {
            cltype = ((Symbol*)(lookupClTypeFromStellaType(((StandardObject*)(binding->rest->value)))));
          }
          if (((boolean)(cltype))) {
            types = cons(listO(3, internCommonLispSymbol("TYPE"), cltype, cons(clTranslateLocalSymbol(((Symbol*)(binding->value))), NIL)), types);
          }
        }
      }
    }
    return (types->reverse());
  }
}

Cons* clYieldGlobalVariableTypeDeclarationTree(GlobalVariable* global) {
  { Object* cltype = lookupClTypeFromStellaType(globalVariableTypeSpec(global));

    if (((boolean)(cltype))) {
      return (((Cons*)(clConditionalizeTypeDeclarationTree(listO(3, internCommonLispSymbol("TYPE"), cltype, cons(clTranslateGlobalSymbol(global->variableName), NIL))))));
    }
    else {
      return (NULL);
    }
  }
}

Cons* clYieldMethodArglistTypeDeclarations(MethodSlot* method) {
  { Cons* types = NIL;
    Symbol* cltype = NULL;

    { StandardObject* tspec = NULL;
      Cons* iter000 = method->methodParameterTypeSpecifiers_reader()->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        tspec = ((StandardObject*)(iter000->value));
        cltype = ((Symbol*)(lookupClTypeFromStellaType(computeRelativeTypeSpec(tspec, method->slotOwner))));
        if (subTypeSpecOfP(tspec, SGT_CL_TRANSLATE_STELLA_ARGUMENT_LIST)) {
          types = cons(internCommonLispSymbol("&REST"), types);
        }
        if (((boolean)(cltype))) {
          types = cons(cltype, types);
        }
        else {
          types = cons(internCommonLispSymbol("T"), types);
        }
      }
    }
    return (types->reverse());
  }
}

Object* clYieldMethodReturnTypeDeclaration(MethodSlot* method) {
  { Cons* types = NIL;
    Symbol* cltype = NULL;

    { StandardObject* tspec = NULL;
      Cons* iter000 = method->methodReturnTypeSpecifiers_reader()->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        tspec = ((StandardObject*)(iter000->value));
        cltype = ((Symbol*)(lookupClTypeFromStellaType(computeRelativeTypeSpec(tspec, method->slotOwner))));
        if (((boolean)(cltype))) {
          types = cons(cltype, types);
        }
        else {
          types = cons(internCommonLispSymbol("T"), types);
        }
      }
    }
    if (types->rest == NIL) {
      return (types->value);
    }
    else {
      return (cons(internCommonLispSymbol("VALUES"), types->reverse()->concatenate(NIL, 0)));
    }
  }
}

Cons* clYieldMethodTypeDeclarationTree(MethodSlot* method) {
  if (!(method->methodFunctionP)) {
    return (NULL);
  }
  { Object* cltype = lookupClTypeFromStellaType(method->slotBaseType);

    if (((boolean)(cltype))) {
      return (((Cons*)(clConditionalizeTypeDeclarationTree(listO(4, internCommonLispSymbol("FTYPE"), listO(3, internCommonLispSymbol("FUNCTION"), clYieldMethodArglistTypeDeclarations(method), cons(clYieldMethodReturnTypeDeclaration(method), NIL)), clTranslateGlobalSymbol(yieldRenamedNameIfNative(method->slotName, KWD_CL_TRANSLATE_COMMON_LISP, KWD_CL_TRANSLATE_FUNCTION)), NIL)))));
    }
    else {
      return (NULL);
    }
  }
}

Cons* clYieldDeclareTree(Cons* declarations, boolean includeTypeChecksP) {
  if (declarations == NIL) {
    return (NIL);
  }
  { Cons* otherdeclarations = declarations->rest;
    Cons* typechecks = NIL;

    if (includeTypeChecksP &&
        (oSAFETYo >= 1)) {
      { Cons* decl = NULL;
        Cons* iter000 = declarations;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          decl = ((Cons*)(iter000->value));
          if (oSAFETYo <= 2) {
            typechecks = cons(newVerbatimStringWrapper("#+MCL"), typechecks);
          }
          typechecks = cons(listO(3, internCommonLispSymbol("CHECK-TYPE"), decl->rest->rest->value, cons(decl->rest->value, NIL)), typechecks);
        }
      }
      typechecks = typechecks->reverse();
    }
    { Cons* decl = NULL;
      Cons* iter001 = declarations;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        decl = ((Cons*)(iter001->value));
        if (((boolean)(decl)) &&
            (decl->value == internCommonLispSymbol("TYPE"))) {
          { Cons* otherdecl = NULL;
            Cons* iter002 = otherdeclarations;

            for (; !(iter002 == NIL); iter002 = iter002->rest) {
              otherdecl = ((Cons*)(iter002->value));
              if (((boolean)(otherdecl)) &&
                  ((otherdecl->value == internCommonLispSymbol("TYPE")) &&
                   eqlP(otherdecl->rest->value, decl->rest->value))) {
                decl->concatenate(otherdecl->rest->rest, 0);
                otherdeclarations->substitute(NULL, otherdecl);
              }
            }
          }
        }
        otherdeclarations = otherdeclarations->rest;
      }
    }
    return (cons(clConditionalizeTypeDeclarationTree(cons(internCommonLispSymbol("DECLARE"), declarations->remove(NULL)->concatenate(NIL, 0))), typechecks->concatenate(NIL, 0)));
  }
}

Object* clConditionalizeTypeDeclarationTree(Object* declaration) {
  return (declaration);
}

Object* clTranslateUnit(TranslationUnit* unit) {
  { Symbol* testValue000 = unit->category;

    if (testValue000 == SYM_CL_TRANSLATE_STELLA_GLOBAL_VARIABLE) {
      return (clTranslateDefineGlobalVariableUnit(unit));
    }
    else if (testValue000 == SYM_CL_TRANSLATE_STELLA_CLASS) {
      return (clTranslateDefineNativeClassUnit(unit));
    }
    else if ((testValue000 == SYM_CL_TRANSLATE_STELLA_METHOD) ||
        (testValue000 == SYM_CL_TRANSLATE_STELLA_MACRO)) {
      return (clTranslateDefineMethodUnit(unit));
    }
    else if (testValue000 == SYM_CL_TRANSLATE_STELLA_PRINT_METHOD) {
      return (clTranslateDefprintUnit(unit));
    }
    else if ((testValue000 == SYM_CL_TRANSLATE_STELLA_STARTUP_TIME_PROGN) ||
        (testValue000 == SYM_CL_TRANSLATE_STELLA_VERBATIM)) {
      return (clTranslateATree(unit->theObject));
    }
    else if (testValue000 == SYM_CL_TRANSLATE_STELLA_TYPE) {
      unit->category = NULL;
      return (NIL);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Cons* clTranslateMethodParameters(MethodSlot* method) {
  { boolean functionP = method->methodFunctionP;
    boolean abstractP = method->abstractP;
    Cons* otree = NIL;
    Object* oparameter = NULL;
    Object* firstparametertype = NULL;

    { Symbol* parameter = NULL;
      Cons* iter000 = method->methodParameterNames_reader()->theConsList;
      StandardObject* ptype = NULL;
      Cons* iter001 = method->methodParameterTypeSpecifiers_reader()->theConsList;
      int i = NULL_INTEGER;
      int iter002 = 1;

      for  (; (!(iter000 == NIL)) &&
                (!(iter001 == NIL)); 
            iter000 = iter000->rest,
            iter001 = iter001->rest,
            iter002 = iter002 + 1) {
        parameter = ((Symbol*)(iter000->value));
        ptype = ((StandardObject*)(iter001->value));
        i = iter002;
        oparameter = clTranslateLocalSymbol(parameter);
        if ((!functionP) &&
            ((!abstractP) &&
             (i == 1))) {
          firstparametertype = clTranslateClassName(typeToClass(typeSpecToBaseType(ptype)));
          { Symbol* testValue000 = methodCallTypeForVectorStructs(method->slotName, method->slotOwner, functionP);

            if (testValue000 == SYM_CL_TRANSLATE_STELLA_OBJECT_METHOD) {
              otree = cons(listO(3, SYM_CL_TRANSLATE_STELLA_CLSYS_SELF, firstparametertype, NIL), otree);
              otree = cons(oparameter, otree);
            }
            else if (testValue000 == SYM_CL_TRANSLATE_STELLA_NON_OBJECT_METHOD) {
              otree = cons(cons(oparameter, cons(firstparametertype, NIL)), otree);
              otree = cons(SYM_CL_TRANSLATE_STELLA_CLSYS_DUMMY, otree);
            }
            else {
              otree = cons(cons(oparameter, cons(firstparametertype, NIL)), otree);
            }
          }
        }
        else {
          otree = cons(oparameter, otree);
        }
      }
    }
    if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_CL_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue &&
        (!passVariableArgumentsAsListP(method))) {
      otree->rest = cons(internCommonLispSymbol("&REST"), otree->rest->concatenate(NIL, 0));
    }
    return (otree->reverse());
  }
}

Symbol* clMethodDefinitionOperator(MethodSlot* method) {
  if (method->methodFunctionP) {
    return (internCommonLispSymbol("DEFUN"));
  }
  else if (method->abstractP) {
    return (internCommonLispSymbol("DEFGENERIC"));
  }
  else if (useDefconsmethodP(method)) {
    return (SYM_CL_TRANSLATE_STELLA_rrDEFCONSMETHOD);
  }
  else if ((method->slotOwner == SGT_CL_TRANSLATE_STELLA_INTEGER) ||
      (method->slotOwner == SGT_CL_TRANSLATE_STELLA_LONG_INTEGER)) {
    return (SYM_CL_TRANSLATE_STELLA_rrDEFINTEGERMETHOD);
  }
  else {
    return (internCommonLispSymbol("DEFMETHOD"));
  }
}

Cons* clTranslateDefineMethodUnit(TranslationUnit* unit) {
  { MethodSlot* method = ((MethodSlot*)(unit->theObject));
    Symbol* methodname = method->slotName;
    const char* documentation = ((StringWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_CL_TRANSLATE_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue;
    boolean functionP = method->methodFunctionP;
    Cons* bodytree = ((Cons*)(unit->codeRegister));
    Cons* declarations = NIL;
    Cons* methoddeclaration = NULL;
    Cons* otree = NIL;

    if ((methodname == SYM_CL_TRANSLATE_STELLA_PRINT_OBJECT) &&
        ((method->slotOwner == SGT_CL_TRANSLATE_STELLA_CONS) &&
         oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_CONSES))) {
      return (NULL);
    }
    { Symbol* testValue000 = methodCallTypeForVectorStructs(methodname, method->slotOwner, functionP);

      if (testValue000 == SYM_CL_TRANSLATE_STELLA_PRINT_OBJECT) {
        bodytree = cons(listO(4, SYM_CL_TRANSLATE_STELLA_SETQ, SYM_CL_TRANSLATE_STELLA_SELF, clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_oCLSYS_SELFo), NIL), bodytree);
      }
      else if (testValue000 == SYM_CL_TRANSLATE_STELLA_NON_OBJECT_METHOD) {
        declarations = cons(listO(3, internCommonLispSymbol("IGNORE"), SYM_CL_TRANSLATE_STELLA_CLSYS_DUMMY, NIL), NIL);
      }
      else {
      }
    }
    if (generateClTypeDeclarationsP()) {
      declarations = declarations->concatenate(clYieldMethodParameterTypeDeclarationTrees(method), 0);
      methoddeclaration = clYieldMethodTypeDeclarationTree(method);
    }
    if ((!functionP) &&
        method->abstractP) {
      otree = cons(clMethodDefinitionOperator(method), cons(clTranslateGlobalSymbol(yieldRenamedNameIfNative(methodname, KWD_CL_TRANSLATE_COMMON_LISP, KWD_CL_TRANSLATE_FUNCTION)), cons(clTranslateMethodParameters(method), NIL)));
    }
    else {
      otree = cons(clMethodDefinitionOperator(method), cons(clTranslateGlobalSymbol(yieldRenamedNameIfNative(methodname, KWD_CL_TRANSLATE_COMMON_LISP, KWD_CL_TRANSLATE_FUNCTION)), cons(clTranslateMethodParameters(method), (((documentation != NULL) ? cons(wrapString(documentation), NIL) : NIL))->concatenate(clYieldDeclareTree(declarations, true)->concatenate(clTranslateListOfTrees(bodytree)->concatenate((((voidP(method->type()) &&
          (!preserveTailMergeOptimizabilityP())) ? cons(KWD_CL_TRANSLATE_VOID, NIL) : NIL))->concatenate(NIL, 0), 0), 0), 0))));
    }
    if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_CL_TRANSLATE_STELLA_SLOT_AUXILIARYp, FALSE_WRAPPER)))->wrapperValue) {
      method->free();
    }
    if (((boolean)(methoddeclaration))) {
      otree = listO(4, internCommonLispSymbol("PROGN"), listO(3, internCommonLispSymbol("DECLAIM"), methoddeclaration, NIL), otree, NIL);
    }
    return (otree);
  }
}

Cons* yieldClosSlotTypeTree(StorageSlot* slot) {
  { Object* cltype = lookupClTypeFromStellaType(slot->slotBaseType);

    if (((boolean)(cltype))) {
      return (cons(clConditionalizeTypeDeclarationTree(KWD_CL_TRANSLATE_TYPE), cons(clConditionalizeTypeDeclarationTree(cltype), listO(3, KWD_CL_TRANSLATE_INITFORM, clTranslateATree(typeToWalkedNullValueTree(slot->typeSpecifier(), slot->slotBaseType)), NIL))));
    }
    else {
      return (NIL);
    }
  }
}

Cons* yieldClosSlotTree(StorageSlot* slot) {
  { Symbol* slotname = trueSlotName(slot->slotName, slot->slotOwner);
    Keyword* allocation = slot->allocation();
    Cons* allocationform = NIL;
    const char* documentation = ((StringWrapper*)(dynamicSlotValue(slot->dynamicSlots, SYM_CL_TRANSLATE_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue;
    Cons* documentationform = NIL;

    if (allocation == KWD_CL_TRANSLATE_EMBEDDED) {
      allocation = KWD_CL_TRANSLATE_INSTANCE;
    }
    else {
    }
    if (((boolean)(allocation))) {
      allocationform = listO(3, KWD_CL_TRANSLATE_ALLOCATION, allocation, NIL);
    }
    if (documentation != NULL) {
      documentationform = listO(3, KWD_CL_TRANSLATE_DOCUMENTATION, wrapString(documentation), NIL);
    }
    return (cons(clTranslateGlobalSymbol(slotname), yieldClosSlotTypeTree(slot)->concatenate(documentationform->concatenate(allocationform->concatenate(listO(3, KWD_CL_TRANSLATE_ACCESSOR, yieldClosSlotAccessorName(slotname), NIL), 0), 0), 0)));
  }
}

Cons* yieldClosClassTree(Class* clasS) {
  { Cons* directsupers = NIL;
    Cons* closslotdefs = NIL;
    const char* documentation = ((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_CL_TRANSLATE_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue;

    { Surrogate* super = NULL;
      Cons* iter000 = classNativeSupers(clasS)->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        super = ((Surrogate*)(iter000->value));
        if ((!((Class*)(super->surrogateValue))->mixinP) ||
            (!translateToSingleInheritanceLanguageP())) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(clTranslateClassName(typeToClass(super)), NIL);
              if (directsupers == NIL) {
                directsupers = collect000;
              }
              else {
                addConsToEndOfConsList(directsupers, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(clTranslateClassName(typeToClass(super)), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    if (directsupers == NIL) {
      directsupers = cons(clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_CLSYS_ROOT_OBJECT), directsupers);
    }
    { Slot* slot = NULL;
      Iterator* iter001 = clasS->classSlots();
      Cons* collect001 = NULL;

      for  (; iter001->nextP(); ) {
        slot = ((Slot*)(iter001->value));
        if (storageSlotP(slot) &&
            nativeSlotP(((StorageSlot*)(slot)))) {
          if (!(nativeSlotHome(slot, clasS) == clasS)) {
            if (((boolean)(slot->slotBaseType)) &&
                (!((boolean)(((Class*)(slot->slotBaseType->surrogateValue)))))) {
              *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't generate a native slot named " << "`" << slot->slotName << "'" << " for the class " << "`" << className(clasS) << "'" << std::endl << " because the slot's :type " << "`" << slot->slotBaseType << "'" << " is undefined." << std::endl;
            }
            continue;
          }
          if (!((boolean)(collect001))) {
            {
              collect001 = cons(yieldClosSlotTree(((StorageSlot*)(slot))), NIL);
              if (closslotdefs == NIL) {
                closslotdefs = collect001;
              }
              else {
                addConsToEndOfConsList(closslotdefs, collect001);
              }
            }
          }
          else {
            {
              collect001->rest = cons(yieldClosSlotTree(((StorageSlot*)(slot))), NIL);
              collect001 = collect001->rest;
            }
          }
        }
      }
    }
    return (listO(3, internCommonLispSymbol("DEFCLASS"), clTranslateGlobalSymbol(classSymbol(clasS)), cons(directsupers, cons(closslotdefs, (((documentation != NULL) ? cons(listO(3, KWD_CL_TRANSLATE_DOCUMENTATION, wrapString(documentation), NIL), NIL) : NIL))->concatenate(NIL, 0)))));
  }
}

List* computeClStructSlots(Class* clasS) {
  { Surrogate* value000 = NULL;

    { Surrogate* super = NULL;
      Cons* iter000 = classNativeSupers(clasS)->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        super = ((Surrogate*)(iter000->value));
        if (!((Class*)(super->surrogateValue))->mixinP) {
          value000 = super;
          break;
        }
      }
    }
    { Surrogate* realsuper = value000;
      List* result = (((boolean)(realsuper)) ? computeClStructSlots(((Class*)(realsuper->surrogateValue))) : ((List*)(NULL)));

      if (!(((boolean)(result)))) {
        result = newList();
      }
      { Surrogate* super = NULL;
        Cons* iter001 = classNativeSupers(clasS)->theConsList;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          super = ((Surrogate*)(iter001->value));
          if (!(super == realsuper)) {
            { Slot* slot = NULL;
              Iterator* iter002 = ((Class*)(super->surrogateValue))->classSlots();
              Cons* collect000 = NULL;

              for  (; iter002->nextP(); ) {
                slot = ((Slot*)(iter002->value));
                if (storageSlotP(slot) &&
                    nativeSlotP(((StorageSlot*)(slot)))) {
                  if (!((boolean)(collect000))) {
                    {
                      collect000 = cons(slot, NIL);
                      if (result->theConsList == NIL) {
                        result->theConsList = collect000;
                      }
                      else {
                        addConsToEndOfConsList(result->theConsList, collect000);
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
          }
        }
      }
      { Slot* slot = NULL;
        Cons* iter003 = clasS->classLocalSlots->theConsList;
        Cons* collect001 = NULL;

        for  (; !(iter003 == NIL); 
              iter003 = iter003->rest) {
          slot = ((Slot*)(iter003->value));
          if (storageSlotP(slot) &&
              nativeSlotP(((StorageSlot*)(slot)))) {
            if (!((boolean)(collect001))) {
              {
                collect001 = cons(slot, NIL);
                if (result->theConsList == NIL) {
                  result->theConsList = collect001;
                }
                else {
                  addConsToEndOfConsList(result->theConsList, collect001);
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
      return (result);
    }
  }
}

List* clStructSlots(Class* clasS) {
  { List* slots = clasS->classClStructSlots_reader();

    if (definedListP(slots)) {
      return (slots);
    }
    else {
      return (((List*)(setDynamicSlotValue(clasS->dynamicSlots, SYM_CL_TRANSLATE_STELLA_CLASS_CL_STRUCT_SLOTS, computeClStructSlots(clasS), NULL))));
    }
  }
}

int clStructSlotOffset(Symbol* slotname, Surrogate* classtype) {
  { List* slots = clStructSlots(((Class*)(classtype->surrogateValue)));
    int offset = 1;

    { StorageSlot* slot = NULL;
      Cons* iter000 = slots->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        slot = ((StorageSlot*)(iter000->value));
        if (slot->slotName == slotname) {
          return (offset);
        }
        else {
          offset = offset + 1;
        }
      }
    }
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      signalTranslationError();
      if (!(suppressWarningsP())) {
        printErrorContext(">> ERROR: ", STANDARD_ERROR);
        *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Can't find slot " << "`" << deUglifyParseTree(slotname) << "'" << " on CL-struct class " << "`" << deUglifyParseTree(classtype) << "'" << "." << std::endl;
      }
    }
    return (NULL_INTEGER);
  }
}

Cons* yieldStructSlotTree(StorageSlot* slot) {
  { Object* cltype = lookupClTypeFromStellaType(slot->slotBaseType);

    if (((boolean)(cltype))) {
      return (cons(clTranslateLocalSymbol(slot->slotName), cons(clTranslateATree(typeToWalkedNullValueTree(slot->typeSpecifier(), slot->slotBaseType)), cons(clConditionalizeTypeDeclarationTree(KWD_CL_TRANSLATE_TYPE), cons(clConditionalizeTypeDeclarationTree(cltype), NIL)))));
    }
    else {
      return (cons(clTranslateLocalSymbol(slot->slotName), cons(clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_NULL), NIL)));
    }
  }
}

Cons* yieldStructSlotTrees(Class* clasS) {
  { Cons* structslotdefs = NIL;

    { StorageSlot* slot = NULL;
      Cons* iter000 = clStructSlots(clasS)->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        slot = ((StorageSlot*)(iter000->value));
        if (!(nativeSlotHome(slot, clasS) == clasS)) {
          if (((boolean)(slot->slotBaseType)) &&
              (!((boolean)(((Class*)(slot->slotBaseType->surrogateValue)))))) {
            *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't generate a native slot named " << "`" << slot->slotName << "'" << " for the class " << "`" << className(clasS) << "'" << std::endl << " because the slot's :type " << "`" << slot->slotBaseType << "'" << " is undefined." << std::endl;
          }
          continue;
        }
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(yieldStructSlotTree(slot), NIL);
            if (structslotdefs == NIL) {
              structslotdefs = collect000;
            }
            else {
              addConsToEndOfConsList(structslotdefs, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(yieldStructSlotTree(slot), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (structslotdefs);
  }
}

Cons* yieldStructTree(Class* clasS) {
  { Surrogate* value000 = NULL;

    { Surrogate* super = NULL;
      Cons* iter000 = classNativeSupers(clasS)->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        super = ((Surrogate*)(iter000->value));
        if (!((Class*)(super->surrogateValue))->mixinP) {
          value000 = super;
          break;
        }
      }
    }
    { Surrogate* super = value000;
      Object* translatedsuper = NULL;
      const char* documentation = ((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_CL_TRANSLATE_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue;

      if (((boolean)(super))) {
        translatedsuper = clTranslateGlobalSymbol(internSymbolInModule(super->symbolName, ((Module*)(super->homeContext)), true));
      }
      else {
        translatedsuper = clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_CLSYS_ROOT_STRUCT);
      }
      return (listO(3, internCommonLispSymbol("DEFSTRUCT"), cons(clTranslateGlobalSymbol(classSymbol(clasS)), cons(listO(3, KWD_CL_TRANSLATE_CONC_NAME, yieldStructSlotAccessorName(clasS->classType, SYM_CL_TRANSLATE_STELLA_), NIL), ((((boolean)(translatedsuper)) ? cons(listO(3, KWD_CL_TRANSLATE_INCLUDE, translatedsuper, NIL), NIL) : NIL))->concatenate(listO(4, listO(3, KWD_CL_TRANSLATE_CONSTRUCTOR, yieldStructConstructorName(clasS), cons(NIL, NIL)), listO(3, KWD_CL_TRANSLATE_COPIER, NIL, NIL), listO(3, KWD_CL_TRANSLATE_PREDICATE, NIL, NIL), NIL), 0))), (((documentation != NULL) ? cons(wrapString(documentation), NIL) : NIL))->concatenate(yieldStructSlotTrees(clasS)->concatenate(NIL, 0), 0)));
    }
  }
}

Object* yieldVectorStructName(Class* clasS) {
  return (yieldGlobalLispSymbol(((Module*)(clasS->classType->homeContext)), stringConcatenate("%", className(clasS), 0)));
}

Cons* yieldVectorStructTree(Class* clasS) {
  { Surrogate* value000 = NULL;

    { Surrogate* super = NULL;
      Cons* iter000 = classNativeSupers(clasS)->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        super = ((Surrogate*)(iter000->value));
        if (!((Class*)(super->surrogateValue))->mixinP) {
          value000 = super;
          break;
        }
      }
    }
    { Surrogate* super = value000;
      const char* documentation = ((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_CL_TRANSLATE_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue;

      return (listO(3, internCommonLispSymbol("DEFCLASS"), clTranslateGlobalSymbol(classSymbol(clasS)), cons((((boolean)(super)) ? cons(clTranslateGlobalSymbol(internSymbolInModule(super->symbolName, ((Module*)(super->homeContext)), true)), NIL) : NIL), cons(NIL, (((documentation != NULL) ? cons(listO(3, KWD_CL_TRANSLATE_DOCUMENTATION, wrapString(documentation), NIL), NIL) : NIL))->concatenate(NIL, 0)))));
    }
  }
}

Cons* yieldConditionTree(Class* clasS) {
  { Cons* defn = yieldClosClassTree(clasS);

    defn->firstSetter(internCommonLispSymbol("DEFINE-CONDITION"));
    if (((boolean)(defn->rest->rest->rest->rest))) {
      defn->rest->rest->rest->rest = NIL;
    }
    return (defn);
  }
}

boolean clAlwaysTranslateToClosClassP(Class* clasS) {
  { boolean testValue000 = false;

    testValue000 = !subtypeOfP(clasS->classType, SGT_CL_TRANSLATE_STELLA_OBJECT);
    if (testValue000) {
      testValue000 = createNativeClassP(clasS);
      if (testValue000) {
        { boolean foundP000 = false;

          { Class* super = NULL;
            Cons* iter000 = clasS->classAllSuperClasses;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              super = ((Class*)(iter000->value));
              if (!createNativeClassP(super)) {
                foundP000 = true;
                break;
              }
            }
          }
          testValue000 = foundP000;
        }
      }
    }
    { boolean value000 = testValue000;

      return (value000);
    }
  }
}

Cons* clTranslateDefineNativeClassUnit(TranslationUnit* unit) {
  { Class* clasS = ((Class*)(unit->theObject));

    if (exceptionClassP(clasS)) {
      return (yieldConditionTree(clasS));
    }
    else if ((!oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_STRUCTS)) ||
        clAlwaysTranslateToClosClassP(clasS)) {
      return (yieldClosClassTree(clasS));
    }
    else if (oCURRENT_STELLA_FEATURESo->membP(KWD_CL_TRANSLATE_USE_COMMON_LISP_VECTOR_STRUCTS)) {
      return (yieldVectorStructTree(clasS));
    }
    else {
      return (yieldStructTree(clasS));
    }
  }
}

Cons* clTranslateDefineGlobalVariableUnit(TranslationUnit* unit) {
  { GlobalVariable* global = ((GlobalVariable*)(unit->theObject));
    Object* name = clTranslateGlobalSymbol(global->variableName);
    const char* documentation = global->documentation;
    boolean unboundspecialP = global->variableSpecialP &&
        (unit->codeRegister == KWD_CL_TRANSLATE_UNBOUND_SPECIAL_VARIABLE);
    Object* initialvaluetree = clTranslateATree(unit->codeRegister);
    Cons* typedeclarationtree = (generateClTypeDeclarationsP() ? clYieldGlobalVariableTypeDeclarationTree(global) : ((Cons*)(NULL)));
    Symbol* operatoR = internCommonLispSymbol("DEFVAR");
    Cons* otree = NIL;

    otree = (unboundspecialP ? listO(3, internCommonLispSymbol("DEFVAR"), name, NIL) : cons(operatoR, cons(name, cons(initialvaluetree, (((documentation != NULL) ? cons(wrapString(documentation), NIL) : NIL))->concatenate(NIL, 0)))));
    if (((boolean)(typedeclarationtree))) {
      otree = listO(3, internCommonLispSymbol("PROGN"), otree, cons(listO(3, internCommonLispSymbol("DECLAIM"), typedeclarationtree, NIL), NIL));
    }
    return (otree);
  }
}

Cons* clTranslateDefprintUnit(TranslationUnit* unit) {
  { Class* clasS = ((Class*)(unit->theObject));
    Object* body = unit->codeRegister;
    Cons* extratrees = NIL;

    if (methodCallTypeForVectorStructs(SYM_CL_TRANSLATE_STELLA_PRINT_OBJECT, clasS->classType, false) == SYM_CL_TRANSLATE_STELLA_PRINT_OBJECT) {
      extratrees = cons(listO(4, SYM_CL_TRANSLATE_STELLA_SETQ, SYM_CL_TRANSLATE_STELLA_SELF, clTranslateGlobalSymbol(SYM_CL_TRANSLATE_STELLA_oCLSYS_SELFo), NIL), NIL);
    }
    else {
    }
    return (listO(4, internCommonLispSymbol("DEFMETHOD"), internCommonLispSymbol("PRINT-OBJECT"), listO(3, listO(3, SYM_CL_TRANSLATE_STELLA_SELF, classSymbol(clasS), NIL), SYM_CL_TRANSLATE_STELLA_STREAM, NIL), extratrees->concatenate(cons(clTranslateATree(body), NIL), 0)));
  }
}

void helpStartupClTranslate1() {
  {
    SYM_CL_TRANSLATE_STELLA_SYS_CALL_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-FUNCTION", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SYS_CALL_METHOD = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-METHOD", NULL, 0)));
    SGT_CL_TRANSLATE_STELLA_KEY_VALUE_LIST = ((Surrogate*)(internRigidSymbolWrtModule("KEY-VALUE-LIST", NULL, 1)));
    SYM_CL_TRANSLATE_STELLA_i = ((Symbol*)(internRigidSymbolWrtModule("+", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA__ = ((Symbol*)(internRigidSymbolWrtModule("-", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_o = ((Symbol*)(internRigidSymbolWrtModule("*", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_s = ((Symbol*)(internRigidSymbolWrtModule("/", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_EQp = ((Symbol*)(internRigidSymbolWrtModule("EQ?", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_l = ((Symbol*)(internRigidSymbolWrtModule("<", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_le = ((Symbol*)(internRigidSymbolWrtModule("<=", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_ge = ((Symbol*)(internRigidSymbolWrtModule(">=", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_g = ((Symbol*)(internRigidSymbolWrtModule(">", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_e = ((Symbol*)(internRigidSymbolWrtModule("=", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_xe = ((Symbol*)(internRigidSymbolWrtModule("!=", NULL, 0)));
    KWD_CL_TRANSLATE_USE_COMMON_LISP_CONSES = ((Keyword*)(internRigidSymbolWrtModule("USE-COMMON-LISP-CONSES", NULL, 2)));
    SGT_CL_TRANSLATE_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SGT_CL_TRANSLATE_STELLA_STANDARD_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("STANDARD-OBJECT", NULL, 1)));
    SGT_CL_TRANSLATE_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
    KWD_CL_TRANSLATE_USE_COMMON_LISP_STRUCTS = ((Keyword*)(internRigidSymbolWrtModule("USE-COMMON-LISP-STRUCTS", NULL, 2)));
    KWD_CL_TRANSLATE_USE_COMMON_LISP_VECTOR_STRUCTS = ((Keyword*)(internRigidSymbolWrtModule("USE-COMMON-LISP-VECTOR-STRUCTS", NULL, 2)));
    SGT_CL_TRANSLATE_STELLA_VOID = ((Surrogate*)(internRigidSymbolWrtModule("VOID", NULL, 1)));
    SYM_CL_TRANSLATE_STELLA_VOID_SYS = ((Symbol*)(internRigidSymbolWrtModule("VOID-SYS", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_TYPED_SYS = ((Symbol*)(internRigidSymbolWrtModule("TYPED-SYS", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_BAD_SYS = ((Symbol*)(internRigidSymbolWrtModule("BAD-SYS", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SYS_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SYS-SLOT-VALUE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SYS_SLOT_VALUE_SETTER = ((Symbol*)(internRigidSymbolWrtModule("SYS-SLOT-VALUE-SETTER", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SYS_CALL_SUPER_METHOD = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-SUPER-METHOD", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("PROGN", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_WITH_PROCESS_LOCK = ((Symbol*)(internRigidSymbolWrtModule("WITH-PROCESS-LOCK", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_LOOP = ((Symbol*)(internRigidSymbolWrtModule("LOOP", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SYS_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("SYS-FOREACH", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_LET = ((Symbol*)(internRigidSymbolWrtModule("LET", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_STARTUP_TIME_PROGN = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-TIME-PROGN", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SPECIAL = ((Symbol*)(internRigidSymbolWrtModule("SPECIAL", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SYS_UNWIND_PROTECT = ((Symbol*)(internRigidSymbolWrtModule("SYS-UNWIND-PROTECT", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SYS_HANDLER_CASE = ((Symbol*)(internRigidSymbolWrtModule("SYS-HANDLER-CASE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SYS_HANDLE_EXCEPTION = ((Symbol*)(internRigidSymbolWrtModule("SYS-HANDLE-EXCEPTION", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SYS_SIGNAL = ((Symbol*)(internRigidSymbolWrtModule("SYS-SIGNAL", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_CAST = ((Symbol*)(internRigidSymbolWrtModule("CAST", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SAFE_CAST = ((Symbol*)(internRigidSymbolWrtModule("SAFE-CAST", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_RETURN = ((Symbol*)(internRigidSymbolWrtModule("RETURN", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_BREAK = ((Symbol*)(internRigidSymbolWrtModule("BREAK", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_CONTINUE = ((Symbol*)(internRigidSymbolWrtModule("CONTINUE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_WHILE = ((Symbol*)(internRigidSymbolWrtModule("WHILE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_IF = ((Symbol*)(internRigidSymbolWrtModule("IF", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_CHOOSE = ((Symbol*)(internRigidSymbolWrtModule("CHOOSE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_WHEN = ((Symbol*)(internRigidSymbolWrtModule("WHEN", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_UNLESS = ((Symbol*)(internRigidSymbolWrtModule("UNLESS", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_OR = ((Symbol*)(internRigidSymbolWrtModule("OR", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_COND = ((Symbol*)(internRigidSymbolWrtModule("COND", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_CASE = ((Symbol*)(internRigidSymbolWrtModule("CASE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_MAKE = ((Symbol*)(internRigidSymbolWrtModule("MAKE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SYS_NEW = ((Symbol*)(internRigidSymbolWrtModule("SYS-NEW", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_MV_SETQ = ((Symbol*)(internRigidSymbolWrtModule("MV-SETQ", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_QUOTE = ((Symbol*)(internRigidSymbolWrtModule("QUOTE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SYS_CALL_FUNCTION_CODE = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-FUNCTION-CODE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SYS_CALL_METHOD_CODE = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-METHOD-CODE", NULL, 0)));
  }
}

void helpStartupClTranslate2() {
  {
    SYM_CL_TRANSLATE_STELLA_SYS_INLINE_CALL = ((Symbol*)(internRigidSymbolWrtModule("SYS-INLINE-CALL", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_THE_CODE = ((Symbol*)(internRigidSymbolWrtModule("THE-CODE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_PRINT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("PRINT-STREAM", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_PRINT_NATIVE_STREAM = ((Symbol*)(internRigidSymbolWrtModule("PRINT-NATIVE-STREAM", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_VERBATIM = ((Symbol*)(internRigidSymbolWrtModule("VERBATIM", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_INLINE = ((Symbol*)(internRigidSymbolWrtModule("INLINE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_IGNORE = ((Symbol*)(internRigidSymbolWrtModule("IGNORE", NULL, 0)));
    KWD_CL_TRANSLATE_CONTINUE = ((Keyword*)(internRigidSymbolWrtModule("CONTINUE", NULL, 2)));
    SYM_CL_TRANSLATE_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_GET_KWD = ((Symbol*)(internRigidSymbolWrtModule("GET-KWD", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_GET_SGT = ((Symbol*)(internRigidSymbolWrtModule("GET-SGT", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_MODULE_LISP_PACKAGE = ((Symbol*)(internRigidSymbolWrtModule("MODULE-LISP-PACKAGE", NULL, 0)));
    KWD_CL_TRANSLATE_UNESCAPED = ((Keyword*)(internRigidSymbolWrtModule("UNESCAPED", NULL, 2)));
    KWD_CL_TRANSLATE_ESCAPED = ((Keyword*)(internRigidSymbolWrtModule("ESCAPED", NULL, 2)));
    KWD_CL_TRANSLATE_COMPLEX_ESCAPED = ((Keyword*)(internRigidSymbolWrtModule("COMPLEX-ESCAPED", NULL, 2)));
    SYM_CL_TRANSLATE_STELLA_VALUE = ((Symbol*)(internRigidSymbolWrtModule("VALUE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_REST = ((Symbol*)(internRigidSymbolWrtModule("REST", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_rrVALUE = ((Symbol*)(internRigidSymbolWrtModule("%%VALUE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_rrREST = ((Symbol*)(internRigidSymbolWrtModule("%%REST", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_CLSYS_SVAL = ((Symbol*)(internRigidSymbolWrtModule("CLSYS-SVAL", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_NTH = ((Symbol*)(internRigidSymbolWrtModule("NTH", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_NTH_SETTER = ((Symbol*)(internRigidSymbolWrtModule("NTH-SETTER", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_AREF = ((Symbol*)(internRigidSymbolWrtModule("AREF", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_AREF_SETTER = ((Symbol*)(internRigidSymbolWrtModule("AREF-SETTER", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_NULLp = ((Symbol*)(internRigidSymbolWrtModule("NULL?", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_DEFINEDp = ((Symbol*)(internRigidSymbolWrtModule("DEFINED?", NULL, 0)));
    SGT_CL_TRANSLATE_STELLA_ARGUMENT_LIST = ((Surrogate*)(internRigidSymbolWrtModule("ARGUMENT-LIST", NULL, 1)));
    SGT_CL_TRANSLATE_STELLA_ARGUMENT_LIST_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("ARGUMENT-LIST-ITERATOR", NULL, 1)));
    SYM_CL_TRANSLATE_STELLA_NORMAL_CALL = ((Symbol*)(internRigidSymbolWrtModule("NORMAL-CALL", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_NON_OBJECT_METHOD = ((Symbol*)(internRigidSymbolWrtModule("NON-OBJECT-METHOD", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_PRINT_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("PRINT-OBJECT", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_OBJECT_METHOD = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-METHOD", NULL, 0)));
    KWD_CL_TRANSLATE_COMMON_LISP = ((Keyword*)(internRigidSymbolWrtModule("COMMON-LISP", NULL, 2)));
    KWD_CL_TRANSLATE_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SYM_CL_TRANSLATE_STELLA_CLSYS_CALL = ((Symbol*)(internRigidSymbolWrtModule("CLSYS-CALL", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    SGT_CL_TRANSLATE_STELLA_STRING = ((Surrogate*)(internRigidSymbolWrtModule("STRING", NULL, 1)));
    SGT_CL_TRANSLATE_STELLA_MUTABLE_STRING = ((Surrogate*)(internRigidSymbolWrtModule("MUTABLE-STRING", NULL, 1)));
    SGT_CL_TRANSLATE_STELLA_NATIVE_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("NATIVE-VECTOR", NULL, 1)));
    SGT_CL_TRANSLATE_STELLA_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("ARRAY", NULL, 1)));
    SGT_CL_TRANSLATE_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", NULL, 1)));
    SYM_CL_TRANSLATE_STELLA_ALLOCATE_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("ALLOCATE-ITERATOR", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("LENGTH", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_NEXTp = ((Symbol*)(internRigidSymbolWrtModule("NEXT?", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_ARGUMENT = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENT", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_DO = ((Symbol*)(internRigidSymbolWrtModule("DO", NULL, 0)));
    SGT_CL_TRANSLATE_STELLA_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT", NULL, 1)));
    SGT_CL_TRANSLATE_STELLA_LONG_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("LONG-INTEGER", NULL, 1)));
    SGT_CL_TRANSLATE_STELLA_NUMBER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER", NULL, 1)));
    SGT_CL_TRANSLATE_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", NULL, 1)));
    SYM_CL_TRANSLATE_STELLA_PRIMARY_TYPE = ((Symbol*)(internRigidSymbolWrtModule("PRIMARY-TYPE", NULL, 0)));
    SGT_CL_TRANSLATE_STELLA_LITERAL = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL", NULL, 1)));
    SGT_CL_TRANSLATE_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 1)));
    SGT_CL_TRANSLATE_STELLA_SECOND_CLASS_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("SECOND-CLASS-OBJECT", NULL, 1)));
    SGT_CL_TRANSLATE_STELLA_CODE = ((Surrogate*)(internRigidSymbolWrtModule("CODE", NULL, 1)));
    SYM_CL_TRANSLATE_STELLA_NULL_ARRAYp = ((Symbol*)(internRigidSymbolWrtModule("NULL-ARRAY?", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_OTHERWISE = ((Symbol*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_CLASS_CL_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CL-NATIVE-TYPE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_oCONDITION_MESSAGE_KEYWORDo = ((Symbol*)(internRigidSymbolWrtModule("*CONDITION-MESSAGE-KEYWORD*", NULL, 0)));
  }
}

void helpStartupClTranslate3() {
  {
    SYM_CL_TRANSLATE_STELLA_REPLACE_SUBSTRINGS = ((Symbol*)(internRigidSymbolWrtModule("REPLACE-SUBSTRINGS", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_CLSYS_MAKE = ((Symbol*)(internRigidSymbolWrtModule("CLSYS-MAKE", NULL, 0)));
    KWD_CL_TRANSLATE_INITIAL_ELEMENT = ((Keyword*)(internRigidSymbolWrtModule("INITIAL-ELEMENT", NULL, 2)));
    SYM_CL_TRANSLATE_STELLA_rrPRINT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("%%PRINT-STREAM", NULL, 0)));
    KWD_CL_TRANSLATE_WARN = ((Keyword*)(internRigidSymbolWrtModule("WARN", NULL, 2)));
    KWD_CL_TRANSLATE_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    KWD_CL_TRANSLATE_CONTINUABLE_ERROR = ((Keyword*)(internRigidSymbolWrtModule("CONTINUABLE-ERROR", NULL, 2)));
    SYM_CL_TRANSLATE_STELLA_CLSYS_METHOD_CODE_CALL = ((Symbol*)(internRigidSymbolWrtModule("CLSYS-METHOD-CODE-CALL", NULL, 0)));
    SGT_CL_TRANSLATE_STELLA_SHORT_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("SHORT-INTEGER", NULL, 1)));
    SYM_CL_TRANSLATE_STELLA_GLOBAL_VARIABLE = ((Symbol*)(internRigidSymbolWrtModule("GLOBAL-VARIABLE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_CLASS = ((Symbol*)(internRigidSymbolWrtModule("CLASS", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_METHOD = ((Symbol*)(internRigidSymbolWrtModule("METHOD", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_MACRO = ((Symbol*)(internRigidSymbolWrtModule("MACRO", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_PRINT_METHOD = ((Symbol*)(internRigidSymbolWrtModule("PRINT-METHOD", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_TYPE = ((Symbol*)(internRigidSymbolWrtModule("TYPE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_CLSYS_SELF = ((Symbol*)(internRigidSymbolWrtModule("CLSYS-SELF", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_CLSYS_DUMMY = ((Symbol*)(internRigidSymbolWrtModule("CLSYS-DUMMY", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-VARIABLE-ARGUMENTS?", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_rrDEFCONSMETHOD = ((Symbol*)(internRigidSymbolWrtModule("%%DEFCONSMETHOD", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_rrDEFINTEGERMETHOD = ((Symbol*)(internRigidSymbolWrtModule("%%DEFINTEGERMETHOD", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_SELF = ((Symbol*)(internRigidSymbolWrtModule("SELF", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_oCLSYS_SELFo = ((Symbol*)(internRigidSymbolWrtModule("*CLSYS-SELF*", NULL, 0)));
    KWD_CL_TRANSLATE_VOID = ((Keyword*)(internRigidSymbolWrtModule("VOID", NULL, 2)));
    SYM_CL_TRANSLATE_STELLA_SLOT_AUXILIARYp = ((Symbol*)(internRigidSymbolWrtModule("SLOT-AUXILIARY?", NULL, 0)));
    KWD_CL_TRANSLATE_INITFORM = ((Keyword*)(internRigidSymbolWrtModule("INITFORM", NULL, 2)));
    KWD_CL_TRANSLATE_TYPE = ((Keyword*)(internRigidSymbolWrtModule("TYPE", NULL, 2)));
    KWD_CL_TRANSLATE_EMBEDDED = ((Keyword*)(internRigidSymbolWrtModule("EMBEDDED", NULL, 2)));
    KWD_CL_TRANSLATE_INSTANCE = ((Keyword*)(internRigidSymbolWrtModule("INSTANCE", NULL, 2)));
    KWD_CL_TRANSLATE_ALLOCATION = ((Keyword*)(internRigidSymbolWrtModule("ALLOCATION", NULL, 2)));
    KWD_CL_TRANSLATE_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
    KWD_CL_TRANSLATE_ACCESSOR = ((Keyword*)(internRigidSymbolWrtModule("ACCESSOR", NULL, 2)));
    SYM_CL_TRANSLATE_STELLA_CLSYS_ROOT_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("CLSYS-ROOT-OBJECT", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_CLASS_CL_STRUCT_SLOTS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CL-STRUCT-SLOTS", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_CLSYS_ROOT_STRUCT = ((Symbol*)(internRigidSymbolWrtModule("CLSYS-ROOT-STRUCT", NULL, 0)));
    KWD_CL_TRANSLATE_CONC_NAME = ((Keyword*)(internRigidSymbolWrtModule("CONC-NAME", NULL, 2)));
    KWD_CL_TRANSLATE_CONSTRUCTOR = ((Keyword*)(internRigidSymbolWrtModule("CONSTRUCTOR", NULL, 2)));
    KWD_CL_TRANSLATE_COPIER = ((Keyword*)(internRigidSymbolWrtModule("COPIER", NULL, 2)));
    KWD_CL_TRANSLATE_PREDICATE = ((Keyword*)(internRigidSymbolWrtModule("PREDICATE", NULL, 2)));
    SYM_CL_TRANSLATE_STELLA_ = ((Symbol*)(internRigidSymbolWrtModule("", NULL, 0)));
    KWD_CL_TRANSLATE_INCLUDE = ((Keyword*)(internRigidSymbolWrtModule("INCLUDE", NULL, 2)));
    KWD_CL_TRANSLATE_UNBOUND_SPECIAL_VARIABLE = ((Keyword*)(internRigidSymbolWrtModule("UNBOUND-SPECIAL-VARIABLE", NULL, 2)));
    SYM_CL_TRANSLATE_STELLA_STREAM = ((Symbol*)(internRigidSymbolWrtModule("STREAM", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_STARTUP_CL_TRANSLATE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-CL-TRANSLATE", NULL, 0)));
    SYM_CL_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupClTranslate4() {
  {
    defineFunctionObject("DESTRUCTURE-CALL-TREE", "(DEFUN (DESTRUCTURE-CALL-TREE SYMBOL TYPE CONS) ((TREE CONS)))", ((cpp_function_code)(&destructureCallTree)), NULL);
    defineFunctionObject("USE-CL-CONSES?", "(DEFUN (USE-CL-CONSES? BOOLEAN) () :GLOBALLY-INLINE? TRUE (RETURN (ENABLED-STELLA-FEATURE? :USE-COMMON-LISP-CONSES)))", ((cpp_function_code)(&useClConsesP)), NULL);
    defineFunctionObject("USE-DEFCONSMETHOD?", "(DEFUN (USE-DEFCONSMETHOD? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&useDefconsmethodP)), NULL);
    defineFunctionObject("USE-CL-STRUCTS?", "(DEFUN (USE-CL-STRUCTS? BOOLEAN) () :GLOBALLY-INLINE? TRUE (RETURN (ENABLED-STELLA-FEATURE? :USE-COMMON-LISP-STRUCTS)))", ((cpp_function_code)(&useClStructsP)), NULL);
    defineFunctionObject("USE-VECTOR-STRUCTS?", "(DEFUN (USE-VECTOR-STRUCTS? BOOLEAN) () :GLOBALLY-INLINE? TRUE (RETURN (ENABLED-STELLA-FEATURE? :USE-COMMON-LISP-VECTOR-STRUCTS)))", ((cpp_function_code)(&useVectorStructsP)), NULL);
    defineFunctionObject("CL-TRANSLATE-LIST-OF-TREES", "(DEFUN (CL-TRANSLATE-LIST-OF-TREES CONS) ((TREES CONS)))", ((cpp_function_code)(&clTranslateListOfTrees)), NULL);
    defineFunctionObject("CL-TRANSLATE-VOID-SYS", "(DEFUN (CL-TRANSLATE-VOID-SYS CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateVoidSys)), NULL);
    defineFunctionObject("CL-TRANSLATE-TYPED-SYS", "(DEFUN (CL-TRANSLATE-TYPED-SYS OBJECT) ((TREE CONS)))", ((cpp_function_code)(&clTranslateTypedSys)), NULL);
    defineFunctionObject("CL-TRANSLATE-BAD-SYS", "(DEFUN (CL-TRANSLATE-BAD-SYS OBJECT) ((TREE CONS)))", ((cpp_function_code)(&clTranslateBadSys)), NULL);
    defineFunctionObject("CL-TRANSLATE-A-TREE", "(DEFUN (CL-TRANSLATE-A-TREE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&clTranslateATree)), NULL);
    defineFunctionObject("HELP-CL-TRANSLATE-A-TREE", "(DEFUN (HELP-CL-TRANSLATE-A-TREE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&helpClTranslateATree)), NULL);
    defineMethodObject("(DEFMETHOD (CL-TRANSLATE-ATOMIC-TREE OBJECT) ((TREE OBJECT)))", wrapMethodCode(((cpp_method_code)(&Object::clTranslateAtomicTree))), NULL);
    defineMethodObject("(DEFMETHOD (CL-TRANSLATE-ATOMIC-TREE OBJECT) ((TREE FLOAT-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&FloatWrapper::clTranslateAtomicTree))), NULL);
    defineMethodObject("(DEFMETHOD (CL-TRANSLATE-ATOMIC-TREE OBJECT) ((TREE SYMBOL)))", wrapMethodCode(((cpp_method_code)(&Symbol::clTranslateAtomicTree))), NULL);
    defineMethodObject("(DEFMETHOD (CL-TRANSLATE-ATOMIC-TREE OBJECT) ((TREE KEYWORD)))", wrapMethodCode(((cpp_method_code)(&Keyword::clTranslateAtomicTree))), NULL);
    defineMethodObject("(DEFMETHOD (CL-TRANSLATE-ATOMIC-TREE OBJECT) ((TREE SURROGATE)))", wrapMethodCode(((cpp_method_code)(&Surrogate::clTranslateAtomicTree))), NULL);
    defineFunctionObject("CL-TRANSLATE-GLOBAL-SYMBOL", "(DEFUN (CL-TRANSLATE-GLOBAL-SYMBOL OBJECT) ((SYMBOL SYMBOL)))", ((cpp_function_code)(&clTranslateGlobalSymbol)), NULL);
    defineFunctionObject("YIELD-READABLE-SYMBOL-NAME", "(DEFUN (YIELD-READABLE-SYMBOL-NAME STRING) ((SYMBOLMODULE MODULE) (SYMBOLNAME STRING) (LOCAL? BOOLEAN)))", ((cpp_function_code)(&yieldReadableSymbolName)), NULL);
    defineFunctionObject("YIELD-GLOBAL-LISP-SYMBOL", "(DEFUN (YIELD-GLOBAL-LISP-SYMBOL OBJECT) ((SYMBOLMODULE MODULE) (SYMBOLNAME STRING)))", ((cpp_function_code)(&yieldGlobalLispSymbol)), NULL);
    defineFunctionObject("CL-TRANSLATE-LOCAL-SYMBOL", "(DEFUN (CL-TRANSLATE-LOCAL-SYMBOL OBJECT) ((SYMBOL SYMBOL)))", ((cpp_function_code)(&clTranslateLocalSymbol)), NULL);
    defineFunctionObject("CL-TRANSLATE-SETQ-TREE", "(DEFUN (CL-TRANSLATE-SETQ-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateSetqTree)), NULL);
    defineFunctionObject("YIELD-STRUCT-SLOT-ACCESSOR-NAME", "(DEFUN (YIELD-STRUCT-SLOT-ACCESSOR-NAME OBJECT) ((CLASSTYPE TYPE) (SLOTNAME SYMBOL)))", ((cpp_function_code)(&yieldStructSlotAccessorName)), NULL);
    defineFunctionObject("YIELD-CLOS-SLOT-ACCESSOR-NAME", "(DEFUN (YIELD-CLOS-SLOT-ACCESSOR-NAME OBJECT) ((SLOTNAME SYMBOL)))", ((cpp_function_code)(&yieldClosSlotAccessorName)), NULL);
    defineFunctionObject("YIELD-SLOT-VALUE-READER-TREE", "(DEFUN (YIELD-SLOT-VALUE-READER-TREE CONS) ((SLOTNAME SYMBOL) (OBJECTREF OBJECT) (OBJECTTYPE TYPE)))", ((cpp_function_code)(&yieldSlotValueReaderTree)), NULL);
    defineFunctionObject("YIELD-SLOT-VALUE-WRITER-TREE", "(DEFUN (YIELD-SLOT-VALUE-WRITER-TREE CONS) ((SLOTNAME SYMBOL) (OBJECTREF OBJECT) (OBJECTTYPE TYPE) (VALUEREF OBJECT)))", ((cpp_function_code)(&yieldSlotValueWriterTree)), NULL);
    defineFunctionObject("TRUE-SLOT-NAME", "(DEFUN (TRUE-SLOT-NAME SYMBOL) ((SLOTNAME SYMBOL) (TYPE TYPE)))", ((cpp_function_code)(&trueSlotName)), NULL);
    defineFunctionObject("CL-TRANSLATE-FIXED-SLOT-VALUE-TREE", "(DEFUN (CL-TRANSLATE-FIXED-SLOT-VALUE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateFixedSlotValueTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-FIXED-SLOT-VALUE-SETTER-TREE", "(DEFUN (CL-TRANSLATE-FIXED-SLOT-VALUE-SETTER-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateFixedSlotValueSetterTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-CALL-METHOD-TREE", "(DEFUN (CL-TRANSLATE-CALL-METHOD-TREE OBJECT) ((TREE CONS)))", ((cpp_function_code)(&clTranslateCallMethodTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-CALL-SUPER-METHOD-TREE", "(DEFUN (CL-TRANSLATE-CALL-SUPER-METHOD-TREE OBJECT) ((TREE CONS)))", ((cpp_function_code)(&clTranslateCallSuperMethodTree)), NULL);
    defineFunctionObject("METHOD-CALL-TYPE-FOR-VECTOR-STRUCTS", "(DEFUN (METHOD-CALL-TYPE-FOR-VECTOR-STRUCTS SYMBOL) ((SLOTNAME SYMBOL) (OWNER TYPE) (FUNCTION? BOOLEAN)))", ((cpp_function_code)(&methodCallTypeForVectorStructs)), NULL);
    defineFunctionObject("CL-TRANSLATE-NORMAL-CALL-METHOD-TREE", "(DEFUN (CL-TRANSLATE-NORMAL-CALL-METHOD-TREE CONS) ((OPERATOR SYMBOL) (OWNER TYPE) (ARGUMENTS CONS)))", ((cpp_function_code)(&clTranslateNormalCallMethodTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-NTH-TREE", "(DEFUN (CL-TRANSLATE-NTH-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateNthTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-AREF-TREE", "(DEFUN (CL-TRANSLATE-AREF-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateArefTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-ARGUMENT-LIST-TREE", "(DEFUN (CL-TRANSLATE-ARGUMENT-LIST-TREE OBJECT) ((TREE CONS)))", ((cpp_function_code)(&clTranslateArgumentListTree)), NULL);
    defineFunctionObject("DUPLICATE-CURSOR-VARIABLE?", "(DEFUN (DUPLICATE-CURSOR-VARIABLE? BOOLEAN) ((VARIABLE SYMBOL) (ITERATORBINDINGS CONS)))", ((cpp_function_code)(&duplicateCursorVariableP)), NULL);
    defineFunctionObject("CL-TRANSLATE-FOREACH-TREE", "(DEFUN (CL-TRANSLATE-FOREACH-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateForeachTree)), NULL);
    defineFunctionObject("MAYBE-WRAP-WITH-CONTINUE-LABEL", "(DEFUN (MAYBE-WRAP-WITH-CONTINUE-LABEL CONS) ((TRANSLATEDLOOPBODY CONS)))", ((cpp_function_code)(&maybeWrapWithContinueLabel)), NULL);
    defineFunctionObject("CL-TRANSLATE-LET-TREE", "(DEFUN (CL-TRANSLATE-LET-TREE CONS) ((TREE CONS) (SPECIAL? BOOLEAN)))", ((cpp_function_code)(&clTranslateLetTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-SPECIAL-TREE", "(DEFUN (CL-TRANSLATE-SPECIAL-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateSpecialTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-STARTUP-TIME-PROGN-TREE", "(DEFUN (CL-TRANSLATE-STARTUP-TIME-PROGN-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateStartupTimePrognTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-UNWIND-PROTECT-TREE", "(DEFUN (CL-TRANSLATE-UNWIND-PROTECT-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateUnwindProtectTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-SIGNAL-TREE", "(DEFUN (CL-TRANSLATE-SIGNAL-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateSignalTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-HANDLER-CASE-TREE", "(DEFUN (CL-TRANSLATE-HANDLER-CASE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateHandlerCaseTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-HANDLE-EXCEPTION-TREE", "(DEFUN (CL-TRANSLATE-HANDLE-EXCEPTION-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateHandleExceptionTree)), NULL);
    defineFunctionObject("CAST", "(DEFUN (CAST OBJECT) ((VALUE OBJECT) (TYPE TYPE)) :DOCUMENTATION \"Perform a run-time type check, and then return `value'.\")", ((cpp_function_code)(&cast)), NULL);
    defineFunctionObject("COERCE-NUMERIC-CONSTANT", "(DEFUN (COERCE-NUMERIC-CONSTANT NUMBER-WRAPPER) ((CONSTANT NUMBER-WRAPPER) (TYPE TYPE)))", ((cpp_function_code)(&coerceNumericConstant)), NULL);
    defineFunctionObject("CL-TRANSLATE-CAST-TREE", "(DEFUN (CL-TRANSLATE-CAST-TREE OBJECT) ((TREE CONS)))", ((cpp_function_code)(&clTranslateCastTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-RETURN-TREE", "(DEFUN (CL-TRANSLATE-RETURN-TREE OBJECT) ((TREE CONS)))", ((cpp_function_code)(&clTranslateReturnTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-BOOLEAN-TEST", "(DEFUN (CL-TRANSLATE-BOOLEAN-TEST OBJECT) ((TREE OBJECT) (INVERT? BOOLEAN)))", ((cpp_function_code)(&clTranslateBooleanTest)), NULL);
    defineFunctionObject("CL-TRANSLATE-PLAIN-BOOLEAN-TEST", "(DEFUN (CL-TRANSLATE-PLAIN-BOOLEAN-TEST OBJECT) ((TREE OBJECT) (INVERT? BOOLEAN)))", ((cpp_function_code)(&clTranslatePlainBooleanTest)), NULL);
    defineFunctionObject("CL-TRANSLATE-WHILE-TREE", "(DEFUN (CL-TRANSLATE-WHILE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateWhileTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-CONDITIONAL-TREE", "(DEFUN (CL-TRANSLATE-CONDITIONAL-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateConditionalTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-COND-TREE", "(DEFUN (CL-TRANSLATE-COND-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateCondTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-CASE-TREE", "(DEFUN (CL-TRANSLATE-CASE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateCaseTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-BOOLEAN-TREE", "(DEFUN (CL-TRANSLATE-BOOLEAN-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateBooleanTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-CLASS-NAME", "(DEFUN (CL-TRANSLATE-CLASS-NAME OBJECT) ((CLASS CLASS)))", ((cpp_function_code)(&clTranslateClassName)), NULL);
    defineFunctionObject("YIELD-STRUCT-CONSTRUCTOR-NAME", "(DEFUN (YIELD-STRUCT-CONSTRUCTOR-NAME OBJECT) ((CLASS CLASS)))", ((cpp_function_code)(&yieldStructConstructorName)), NULL);
    defineFunctionObject("CL-TRANSLATE-MAKE-TREE", "(DEFUN (CL-TRANSLATE-MAKE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateMakeTree)), NULL);
    defineFunctionObject("CL-TRANSLATE-NEW-TREE", "(DEFUN (CL-TRANSLATE-NEW-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateNewTree)), NULL);
  }
}

void startupClTranslate() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupClTranslate1();
      helpStartupClTranslate2();
      helpStartupClTranslate3();
    }
    if (currentStartupTimePhaseP(4)) {
      oCL_TRUE_STRING_WRAPPERo = newVerbatimStringWrapper("CL:T");
      oCL_FALSE_STRING_WRAPPERo = newVerbatimStringWrapper("CL:NIL");
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupClTranslate4();
      defineFunctionObject("CL-TRANSLATE-NEW-ARRAY-TREE", "(DEFUN (CL-TRANSLATE-NEW-ARRAY-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateNewArrayTree)), NULL);
      defineFunctionObject("CL-TRANSLATE-OPERATOR-TREE", "(DEFUN (CL-TRANSLATE-OPERATOR-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateOperatorTree)), NULL);
      defineFunctionObject("YIELD-FORMAT-ARGUMENTS", "(DEFUN (YIELD-FORMAT-ARGUMENTS CONS) ((TREE CONS)))", ((cpp_function_code)(&yieldFormatArguments)), NULL);
      defineFunctionObject("YIELD-PRINT-TREE", "(DEFUN (YIELD-PRINT-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&yieldPrintTree)), NULL);
      defineFunctionObject("CL-TRANSLATE-PRINT-STREAM-TREE", "(DEFUN (CL-TRANSLATE-PRINT-STREAM-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslatePrintStreamTree)), NULL);
      defineFunctionObject("CL-TRANSLATE-CALL-FUNCTION-CODE-TREE", "(DEFUN (CL-TRANSLATE-CALL-FUNCTION-CODE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateCallFunctionCodeTree)), NULL);
      defineFunctionObject("CL-TRANSLATE-INLINE-CALL-TREE", "(DEFUN (CL-TRANSLATE-INLINE-CALL-TREE OBJECT) ((TREE CONS)))", ((cpp_function_code)(&clTranslateInlineCallTree)), NULL);
      defineFunctionObject("CL-TRANSLATE-VERBATIM-BODY-SYMBOLS", "(DEFUN (CL-TRANSLATE-VERBATIM-BODY-SYMBOLS OBJECT) ((BODY OBJECT) (PARAMETERS (LIST OF SYMBOL))))", ((cpp_function_code)(&clTranslateVerbatimBodySymbols)), NULL);
      defineFunctionObject("CL-TRANSLATE-THE-CODE-TREE", "(DEFUN (CL-TRANSLATE-THE-CODE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateTheCodeTree)), NULL);
      defineFunctionObject("CL-TRANSLATE-VERBATIM-TREE", "(DEFUN (CL-TRANSLATE-VERBATIM-TREE OBJECT) ((TREE CONS)))", ((cpp_function_code)(&clTranslateVerbatimTree)), NULL);
      defineFunctionObject("CL-TRANSLATE-INLINE-TREE", "(DEFUN (CL-TRANSLATE-INLINE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&clTranslateInlineTree)), NULL);
      defineFunctionObject("GENERATE-CL-TYPE-DECLARATIONS?", "(DEFUN (GENERATE-CL-TYPE-DECLARATIONS? BOOLEAN) ())", ((cpp_function_code)(&generateClTypeDeclarationsP)), NULL);
      defineFunctionObject("LOOKUP-CL-TYPE-FROM-STELLA-TYPE", "(DEFUN (LOOKUP-CL-TYPE-FROM-STELLA-TYPE OBJECT) ((TYPE TYPE-SPEC)))", ((cpp_function_code)(&lookupClTypeFromStellaType)), NULL);
      defineFunctionObject("CL-YIELD-TYPED-EXPRESSION-TREE", "(DEFUN (CL-YIELD-TYPED-EXPRESSION-TREE OBJECT) ((TREE OBJECT) (TYPE TYPE-SPEC)))", ((cpp_function_code)(&clYieldTypedExpressionTree)), NULL);
      defineFunctionObject("CL-YIELD-METHOD-PARAMETER-TYPE-DECLARATION-TREES", "(DEFUN (CL-YIELD-METHOD-PARAMETER-TYPE-DECLARATION-TREES CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&clYieldMethodParameterTypeDeclarationTrees)), NULL);
      defineFunctionObject("CL-YIELD-LET-VARIABLE-TYPE-DECLARATION-TREES", "(DEFUN (CL-YIELD-LET-VARIABLE-TYPE-DECLARATION-TREES CONS) ((BINDINGSTREE (CONS OF CONS))))", ((cpp_function_code)(&clYieldLetVariableTypeDeclarationTrees)), NULL);
      defineFunctionObject("CL-YIELD-GLOBAL-VARIABLE-TYPE-DECLARATION-TREE", "(DEFUN (CL-YIELD-GLOBAL-VARIABLE-TYPE-DECLARATION-TREE CONS) ((GLOBAL GLOBAL-VARIABLE)))", ((cpp_function_code)(&clYieldGlobalVariableTypeDeclarationTree)), NULL);
      defineFunctionObject("CL-YIELD-METHOD-ARGLIST-TYPE-DECLARATIONS", "(DEFUN (CL-YIELD-METHOD-ARGLIST-TYPE-DECLARATIONS CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&clYieldMethodArglistTypeDeclarations)), NULL);
      defineFunctionObject("CL-YIELD-METHOD-RETURN-TYPE-DECLARATION", "(DEFUN (CL-YIELD-METHOD-RETURN-TYPE-DECLARATION OBJECT) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&clYieldMethodReturnTypeDeclaration)), NULL);
      defineFunctionObject("CL-YIELD-METHOD-TYPE-DECLARATION-TREE", "(DEFUN (CL-YIELD-METHOD-TYPE-DECLARATION-TREE CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&clYieldMethodTypeDeclarationTree)), NULL);
      defineFunctionObject("CL-YIELD-DECLARE-TREE", "(DEFUN (CL-YIELD-DECLARE-TREE CONS) ((DECLARATIONS (CONS OF CONS)) (INCLUDE-TYPE-CHECKS? BOOLEAN)))", ((cpp_function_code)(&clYieldDeclareTree)), NULL);
      defineFunctionObject("CL-CONDITIONALIZE-TYPE-DECLARATION-TREE", "(DEFUN (CL-CONDITIONALIZE-TYPE-DECLARATION-TREE OBJECT) ((DECLARATION OBJECT)))", ((cpp_function_code)(&clConditionalizeTypeDeclarationTree)), NULL);
      defineFunctionObject("CL-TRANSLATE-UNIT", "(DEFUN (CL-TRANSLATE-UNIT OBJECT) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&clTranslateUnit)), NULL);
      defineFunctionObject("CL-TRANSLATE-METHOD-PARAMETERS", "(DEFUN (CL-TRANSLATE-METHOD-PARAMETERS CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&clTranslateMethodParameters)), NULL);
      defineFunctionObject("CL-METHOD-DEFINITION-OPERATOR", "(DEFUN (CL-METHOD-DEFINITION-OPERATOR SYMBOL) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&clMethodDefinitionOperator)), NULL);
      defineFunctionObject("CL-TRANSLATE-DEFINE-METHOD-UNIT", "(DEFUN (CL-TRANSLATE-DEFINE-METHOD-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&clTranslateDefineMethodUnit)), NULL);
      defineFunctionObject("YIELD-CLOS-SLOT-TYPE-TREE", "(DEFUN (YIELD-CLOS-SLOT-TYPE-TREE CONS) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&yieldClosSlotTypeTree)), NULL);
      defineFunctionObject("YIELD-CLOS-SLOT-TREE", "(DEFUN (YIELD-CLOS-SLOT-TREE CONS) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&yieldClosSlotTree)), NULL);
      defineFunctionObject("YIELD-CLOS-CLASS-TREE", "(DEFUN (YIELD-CLOS-CLASS-TREE CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldClosClassTree)), NULL);
      defineFunctionObject("COMPUTE-CL-STRUCT-SLOTS", "(DEFUN (COMPUTE-CL-STRUCT-SLOTS (LIST OF STORAGE-SLOT)) ((CLASS CLASS)))", ((cpp_function_code)(&computeClStructSlots)), NULL);
      defineFunctionObject("CL-STRUCT-SLOTS", "(DEFUN (CL-STRUCT-SLOTS (LIST OF STORAGE-SLOT)) ((CLASS CLASS)))", ((cpp_function_code)(&clStructSlots)), NULL);
      defineFunctionObject("CL-STRUCT-SLOT-OFFSET", "(DEFUN (CL-STRUCT-SLOT-OFFSET INTEGER) ((SLOTNAME SYMBOL) (CLASSTYPE TYPE)))", ((cpp_function_code)(&clStructSlotOffset)), NULL);
      defineFunctionObject("YIELD-STRUCT-SLOT-TREE", "(DEFUN (YIELD-STRUCT-SLOT-TREE CONS) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&yieldStructSlotTree)), NULL);
      defineFunctionObject("YIELD-STRUCT-SLOT-TREES", "(DEFUN (YIELD-STRUCT-SLOT-TREES CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldStructSlotTrees)), NULL);
      defineFunctionObject("YIELD-STRUCT-TREE", "(DEFUN (YIELD-STRUCT-TREE CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldStructTree)), NULL);
      defineFunctionObject("YIELD-VECTOR-STRUCT-NAME", "(DEFUN (YIELD-VECTOR-STRUCT-NAME OBJECT) ((CLASS CLASS)))", ((cpp_function_code)(&yieldVectorStructName)), NULL);
      defineFunctionObject("YIELD-VECTOR-STRUCT-TREE", "(DEFUN (YIELD-VECTOR-STRUCT-TREE CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldVectorStructTree)), NULL);
      defineFunctionObject("YIELD-CONDITION-TREE", "(DEFUN (YIELD-CONDITION-TREE CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldConditionTree)), NULL);
      defineFunctionObject("CL-ALWAYS-TRANSLATE-TO-CLOS-CLASS?", "(DEFUN (CL-ALWAYS-TRANSLATE-TO-CLOS-CLASS? BOOLEAN) ((CLASS CLASS)))", ((cpp_function_code)(&clAlwaysTranslateToClosClassP)), NULL);
      defineFunctionObject("CL-TRANSLATE-DEFINE-NATIVE-CLASS-UNIT", "(DEFUN (CL-TRANSLATE-DEFINE-NATIVE-CLASS-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&clTranslateDefineNativeClassUnit)), NULL);
      defineFunctionObject("CL-TRANSLATE-DEFINE-GLOBAL-VARIABLE-UNIT", "(DEFUN (CL-TRANSLATE-DEFINE-GLOBAL-VARIABLE-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&clTranslateDefineGlobalVariableUnit)), NULL);
      defineFunctionObject("CL-TRANSLATE-DEFPRINT-UNIT", "(DEFUN (CL-TRANSLATE-DEFPRINT-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&clTranslateDefprintUnit)), NULL);
      defineFunctionObject("STARTUP-CL-TRANSLATE", "(DEFUN STARTUP-CL-TRANSLATE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupClTranslate)), NULL);
      { MethodSlot* function = lookupFunction(SYM_CL_TRANSLATE_STELLA_STARTUP_CL_TRANSLATE);

        setDynamicSlotValue(function->dynamicSlots, SYM_CL_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupClTranslate"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *CL-TRUE-STRING-WRAPPER* VERBATIM-STRING-WRAPPER (NEW VERBATIM-STRING-WRAPPER :WRAPPER-VALUE \"CL:T\"))", &oCL_TRUE_STRING_WRAPPERo);
      defineGlobalVariableObject("(DEFGLOBAL *CL-FALSE-STRING-WRAPPER* VERBATIM-STRING-WRAPPER (NEW VERBATIM-STRING-WRAPPER :WRAPPER-VALUE \"CL:NIL\"))", &oCL_FALSE_STRING_WRAPPERo);
      defineGlobalVariableObject("(DEFGLOBAL *CL-OPERATOR-TABLE* KEY-VALUE-LIST NULL :DOCUMENTATION \"Mapping from STELLA operators to Common-Lisp operators.\")", &oCL_OPERATOR_TABLEo);
      oCL_OPERATOR_TABLEo = ((KeyValueList*)(dictionary(SGT_CL_TRANSLATE_STELLA_KEY_VALUE_LIST, 22, SYM_CL_TRANSLATE_STELLA_i, internCommonLispSymbol("+"), SYM_CL_TRANSLATE_STELLA__, internCommonLispSymbol("-"), SYM_CL_TRANSLATE_STELLA_o, internCommonLispSymbol("*"), SYM_CL_TRANSLATE_STELLA_s, internCommonLispSymbol("/"), SYM_CL_TRANSLATE_STELLA_EQp, internCommonLispSymbol("EQL"), SYM_CL_TRANSLATE_STELLA_l, internCommonLispSymbol("<"), SYM_CL_TRANSLATE_STELLA_le, internCommonLispSymbol("<="), SYM_CL_TRANSLATE_STELLA_ge, internCommonLispSymbol(">="), SYM_CL_TRANSLATE_STELLA_g, internCommonLispSymbol(">"), SYM_CL_TRANSLATE_STELLA_e, internCommonLispSymbol("="), SYM_CL_TRANSLATE_STELLA_xe, internCommonLispSymbol("/="))));
      { boolean usestructsP = false;
        boolean usevectorstructsP = false;
        boolean useclconsesP = false;

        if (usestructsP) {
          setStellaFeature(consList(1, KWD_CL_TRANSLATE_USE_COMMON_LISP_STRUCTS));
        }
        if (usevectorstructsP) {
          setStellaFeature(consList(1, KWD_CL_TRANSLATE_USE_COMMON_LISP_VECTOR_STRUCTS));
        }
        if (useclconsesP) {
          setStellaFeature(consList(1, KWD_CL_TRANSLATE_USE_COMMON_LISP_CONSES));
        }
      }
      defineGlobalVariableObject("(DEFSPECIAL *NEEDEXPLICITRETURN?* BOOLEAN FALSE)", &oNEEDEXPLICITRETURNpo);
    }
  }
}

Symbol* SYM_CL_TRANSLATE_STELLA_SYS_CALL_FUNCTION = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SYS_CALL_METHOD = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_KEY_VALUE_LIST = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_i = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA__ = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_o = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_s = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_EQp = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_l = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_le = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_ge = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_g = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_e = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_xe = NULL;

Keyword* KWD_CL_TRANSLATE_USE_COMMON_LISP_CONSES = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_CONS = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_STANDARD_OBJECT = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_OBJECT = NULL;

Keyword* KWD_CL_TRANSLATE_USE_COMMON_LISP_STRUCTS = NULL;

Keyword* KWD_CL_TRANSLATE_USE_COMMON_LISP_VECTOR_STRUCTS = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_VOID = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_VOID_SYS = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_TYPED_SYS = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_BAD_SYS = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SETQ = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SYS_SLOT_VALUE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SYS_SLOT_VALUE_SETTER = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SYS_CALL_SUPER_METHOD = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_PROGN = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_WITH_PROCESS_LOCK = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_LOOP = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SYS_FOREACH = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_LET = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_STARTUP_TIME_PROGN = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SPECIAL = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SYS_UNWIND_PROTECT = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SYS_HANDLER_CASE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SYS_HANDLE_EXCEPTION = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SYS_SIGNAL = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CAST = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SAFE_CAST = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_RETURN = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_BREAK = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CONTINUE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_WHILE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_IF = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CHOOSE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_WHEN = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_UNLESS = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_AND = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_OR = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_NOT = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_COND = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CASE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_MAKE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SYS_NEW = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_MV_SETQ = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_QUOTE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SYS_CALL_FUNCTION_CODE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SYS_CALL_METHOD_CODE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SYS_INLINE_CALL = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_THE_CODE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_PRINT_STREAM = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_PRINT_NATIVE_STREAM = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_VERBATIM = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_INLINE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_IGNORE = NULL;

Keyword* KWD_CL_TRANSLATE_CONTINUE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_TRUE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_FALSE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_GET_KWD = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_GET_SGT = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_MODULE_LISP_PACKAGE = NULL;

Keyword* KWD_CL_TRANSLATE_UNESCAPED = NULL;

Keyword* KWD_CL_TRANSLATE_ESCAPED = NULL;

Keyword* KWD_CL_TRANSLATE_COMPLEX_ESCAPED = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_VALUE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_REST = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_rrVALUE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_rrREST = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_SVAL = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_NTH = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_NTH_SETTER = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_AREF = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_AREF_SETTER = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_NULLp = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_DEFINEDp = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_ARGUMENT_LIST = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_ARGUMENT_LIST_ITERATOR = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_NORMAL_CALL = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_NON_OBJECT_METHOD = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_PRINT_OBJECT = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_OBJECT_METHOD = NULL;

Keyword* KWD_CL_TRANSLATE_COMMON_LISP = NULL;

Keyword* KWD_CL_TRANSLATE_FUNCTION = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_CALL = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_NULL = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_STRING = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_MUTABLE_STRING = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_NATIVE_VECTOR = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_ARRAY = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_INTEGER = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_ALLOCATE_ITERATOR = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_LENGTH = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_NEXTp = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_ARGUMENT = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_DO = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_FLOAT = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_LONG_INTEGER = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_NUMBER = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_NUMBER_WRAPPER = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_PRIMARY_TYPE = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_LITERAL = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_BOOLEAN = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_SECOND_CLASS_OBJECT = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_CODE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_NULL_ARRAYp = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_OTHERWISE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CLASS_CL_NATIVE_TYPE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_oCONDITION_MESSAGE_KEYWORDo = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_REPLACE_SUBSTRINGS = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_MAKE = NULL;

Keyword* KWD_CL_TRANSLATE_INITIAL_ELEMENT = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_rrPRINT_STREAM = NULL;

Keyword* KWD_CL_TRANSLATE_WARN = NULL;

Keyword* KWD_CL_TRANSLATE_ERROR = NULL;

Keyword* KWD_CL_TRANSLATE_CONTINUABLE_ERROR = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_METHOD_CODE_CALL = NULL;

Surrogate* SGT_CL_TRANSLATE_STELLA_SHORT_INTEGER = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_GLOBAL_VARIABLE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CLASS = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_METHOD = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_MACRO = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_PRINT_METHOD = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_TYPE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_SELF = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_DUMMY = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_rrDEFCONSMETHOD = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_rrDEFINTEGERMETHOD = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_DOCUMENTATION = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SELF = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_oCLSYS_SELFo = NULL;

Keyword* KWD_CL_TRANSLATE_VOID = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_SLOT_AUXILIARYp = NULL;

Keyword* KWD_CL_TRANSLATE_INITFORM = NULL;

Keyword* KWD_CL_TRANSLATE_TYPE = NULL;

Keyword* KWD_CL_TRANSLATE_EMBEDDED = NULL;

Keyword* KWD_CL_TRANSLATE_INSTANCE = NULL;

Keyword* KWD_CL_TRANSLATE_ALLOCATION = NULL;

Keyword* KWD_CL_TRANSLATE_DOCUMENTATION = NULL;

Keyword* KWD_CL_TRANSLATE_ACCESSOR = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_ROOT_OBJECT = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CLASS_CL_STRUCT_SLOTS = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_ROOT_STRUCT = NULL;

Keyword* KWD_CL_TRANSLATE_CONC_NAME = NULL;

Keyword* KWD_CL_TRANSLATE_CONSTRUCTOR = NULL;

Keyword* KWD_CL_TRANSLATE_COPIER = NULL;

Keyword* KWD_CL_TRANSLATE_PREDICATE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_ = NULL;

Keyword* KWD_CL_TRANSLATE_INCLUDE = NULL;

Keyword* KWD_CL_TRANSLATE_UNBOUND_SPECIAL_VARIABLE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_STREAM = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_STARTUP_CL_TRANSLATE = NULL;

Symbol* SYM_CL_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
