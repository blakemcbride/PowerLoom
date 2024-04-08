//  -*- Mode: C++ -*-

// java-translate.cc

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

// Wrapped true string, used to reduce consing.
StringWrapper* oJAVA_TRUE_STRING_WRAPPERo = NULL;

// Wrapped false string, used to reduce consing.
StringWrapper* oJAVA_FALSE_STRING_WRAPPERo = NULL;

const char* javaYieldFlotsamClassName(Module* mod) {
  { const char* flotsamclassname = ((StringWrapper*)(dynamicSlotValue(mod->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_JAVA_FLOTSAM_CLASS, NULL_STRING_WRAPPER)))->wrapperValue;

    if ((flotsamclassname != NULL) &&
        (!(flotsamclassname == ""))) {
      return (flotsamclassname);
    }
    else {
      {
        flotsamclassname = javaTranslateClassNamestring(wrapString(mod->name()))->wrapperValue;
        setDynamicSlotValue(mod->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_JAVA_FLOTSAM_CLASS, wrapString(flotsamclassname), NULL_STRING_WRAPPER);
        return (flotsamclassname);
      }
    }
  }
}

const char* javaYieldNativeClassName() {
  if (((boolean)(stringGetStellaClass("NATIVE", false))) ||
      inheritedClassNameConflictsP("NATIVE")) {
    return (javaYieldFullNativeClassName());
  }
  else {
    return ("Native");
  }
}

const char* javaYieldSpecialVariableClassName() {
  if (((boolean)(stringGetStellaClass("STELLA-SPECIAL-VARIABLE", false))) ||
      inheritedClassNameConflictsP("STELLA-SPECIAL-VARIABLE")) {
    return (stringConcatenate(javaStellaPackage(), ".javalib.StellaSpecialVariable", 0));
  }
  else {
    return ("StellaSpecialVariable");
  }
}

const char* javaYieldFullNativeClassName() {
  return (stringConcatenate(javaStellaPackage(), ".javalib.Native", 0));
}

Cons* javaTranslateUnit(TranslationUnit* unit) {
  { Symbol* testValue000 = unit->category;

    if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_GLOBAL_VARIABLE) {
      return (javaTranslateDefineGlobalVariableUnit(unit));
    }
    else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_CLASS) {
      return (javaTranslateDefineNativeClassUnit(unit));
    }
    else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_TYPE) {
      return (NIL);
    }
    else if ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_METHOD) ||
        (testValue000 == SYM_JAVA_TRANSLATE_STELLA_MACRO)) {
      return (javaTranslateDefineMethodUnit(unit));
    }
    else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_PRINT_METHOD) {
      return (javaTranslateDefprintUnit(unit));
    }
    else if ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_STARTUP_TIME_PROGN) ||
        (testValue000 == SYM_JAVA_TRANSLATE_STELLA_VERBATIM)) {
      return (((Cons*)(javaTranslateATree(unit->theObject))));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Cons* javaTranslateDefineGlobalVariableUnit(TranslationUnit* unit) {
  { GlobalVariable* global = ((GlobalVariable*)(unit->theObject));

    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, global->homeModule());
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      { StringWrapper* variabletype = (global->variableSpecialP ? wrapString(javaYieldSpecialVariableClassName()) : javaTranslateTypeSpec(globalVariableTypeSpec(global)));
        Cons* typelist = cons(variabletype, NIL);
        Object* initialvaluetree = javaTranslateATree(unit->codeRegister);
        StringWrapper* variablename = javaTranslateGlobalName(global->variableName, true);

        typelist = cons(wrapString("static"), typelist);
        if (global->variableConstantP ||
            global->variableSpecialP) {
          typelist = cons(wrapString("final"), typelist);
        }
        if (global->variablePublicP) {
          typelist = cons(wrapString("public"), typelist);
        }
        if ((unit->codeRegister == KWD_JAVA_TRANSLATE_UNBOUND_SPECIAL_VARIABLE) ||
            global->variableSpecialP) {
          return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_GLOBAL, wrapString(global->documentation), listO(3, cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_TYPE, typelist->concatenate(NIL, 0)), variablename, cons(listO(4, SYM_JAVA_TRANSLATE_STELLA_JAVA_MAKE, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, variabletype, NIL), cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, NIL), NIL), NIL))));
        }
        else {
          return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_GLOBAL, wrapString(global->documentation), listO(3, cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_TYPE, typelist->concatenate(NIL, 0)), variablename, cons(initialvaluetree, NIL))));
        }
      }
    }
  }
}

Cons* wrapMethodBodyWithJavaAuxiliaryDeclarations(Cons* methodbody, Cons* declarations) {
  { Cons* odeclarations = NIL;
    Cons* otree = NULL;

    declarations = declarations->reverse();
    { Object* declaration = NULL;
      Cons* iter000 = declarations;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        declaration = iter000->value;
        { Cons* d = ((Cons*)(declaration));

          odeclarations = cons(cons(javaTranslateTypeSpec(((StandardObject*)(d->rest->value))), cons(javaTranslateATree(d->value), ((((boolean)(d->rest->rest->value)) ? consList(1, javaTranslateATree(d->rest->rest->value)) : NIL))->concatenate(NIL, 0))), odeclarations);
        }
      }
    }
    otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_BLOCK, odeclarations->reverse(), cons(methodbody, NIL)), NIL);
    return (otree);
  }
}

boolean javaSynchronizedMethodP(MethodSlot* method) {
  method = method;
  return (false);
}

Cons* javaTranslateMethodSignature(MethodSlot* method) {
  { Cons* modifiers = NIL;
    Cons* returntype = NULL;

    if (javaSynchronizedMethodP(method)) {
      modifiers = cons(wrapString("synchronized"), modifiers);
    }
    if (javaMethodObjectIsFunctionP(method)) {
      modifiers = cons(wrapString("static"), modifiers);
    }
    if (method->abstractP) {
      modifiers = cons(wrapString("abstract"), modifiers);
    }
    if (method->publicP()) {
      modifiers = cons(wrapString("public"), modifiers);
    }
    returntype = cons(javaTranslateTypeSpec(computeMostGeneralReturnType(method, method->computeReturnTypeSpec(method->slotOwner))), NIL);
    return (cons(modifiers, cons(returntype, cons(method->javaTranslateMethodName(), cons(javaTranslateMethodParameters(method), NIL)))));
  }
}

Cons* javaTranslateDefineMethodUnit(TranslationUnit* unit) {
  { 
    BIND_STELLA_SPECIAL(oLOCALGENSYMTABLEo, KeyValueList*, newKeyValueList());
    BIND_STELLA_SPECIAL(oMETHODBEINGWALKEDo, MethodSlot*, NULL);
    BIND_STELLA_SPECIAL(oCURRENTDUMMYINDEXo, int, 0);
    BIND_STELLA_SPECIAL(oDUMMYDECLARATIONSo, Cons*, NIL);
    { MethodSlot* method = ((MethodSlot*)(unit->theObject));
      boolean unitisfunction = javaMethodObjectIsFunctionP(method);
      Cons* bodytree = ((Cons*)(unit->codeRegister));
      Cons* otree = NIL;
      Cons* translatedmethodbody = NULL;

      if (((boolean)(unit->translation)) &&
          (!(!((boolean)(unit->translation))))) {
        otree = ((Cons*)(unit->translation));
        unit->translation = NIL;
        return (otree);
      }
      oMETHODBEINGWALKEDo = method;
      bodytree = deleteQuotedNullStatements(bodytree);
      if (!unitisfunction) {
        oDUMMYDECLARATIONSo = cons(cons(((Symbol*)(method->methodParameterNames_reader()->first())), cons(method->slotOwner, cons(SYM_JAVA_TRANSLATE_STELLA_THIS, NIL))), oDUMMYDECLARATIONSo);
      }
      if (method->abstractP) {
        translatedmethodbody = NIL;
      }
      else {
        {
          translatedmethodbody = cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, javaTranslateListOfTrees(bodytree)->concatenate(NIL, 0));
          if (!(oDUMMYDECLARATIONSo == NIL)) {
            translatedmethodbody = wrapMethodBodyWithJavaAuxiliaryDeclarations(translatedmethodbody, oDUMMYDECLARATIONSo);
          }
        }
      }
      if (((StringWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue != NULL) {
        if (translatedmethodbody == NIL) {
          translatedmethodbody = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_COMMENT, wrapString(((StringWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue), NIL), NIL);
        }
        else {
          translatedmethodbody->rest = cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_COMMENT, wrapString(((StringWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue), NIL), translatedmethodbody->rest->concatenate(NIL, 0));
        }
      }
      otree = cons((unitisfunction ? SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION : SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD), javaTranslateMethodSignature(method)->concatenate(cons(translatedmethodbody, NIL), 0));
      unit->translation = NIL;
      return (otree);
    }
  }
}

Cons* javaTranslateDefprintUnit(TranslationUnit* unit) {
  { 
    BIND_STELLA_SPECIAL(oMETHODBEINGWALKEDo, MethodSlot*, newMethodSlot());
    BIND_STELLA_SPECIAL(oLOCALGENSYMTABLEo, KeyValueList*, newKeyValueList());
    BIND_STELLA_SPECIAL(oCURRENTDUMMYINDEXo, int, 0);
    BIND_STELLA_SPECIAL(oDUMMYDECLARATIONSo, Cons*, NIL);
    { Class* clasS = ((Class*)(unit->theObject));
      Cons* bodytree = ((Cons*)(unit->codeRegister));
      Cons* otree = NIL;
      Cons* translatedmethodbody = NULL;

      { 
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, clasS->homeModule());
        BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
        bodytree = deleteQuotedNullStatements(bodytree);
        oDUMMYDECLARATIONSo = cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_SELF, canonicalType(clasS->classType), cons(SYM_JAVA_TRANSLATE_STELLA_THIS, NIL)), oDUMMYDECLARATIONSo);
        translatedmethodbody = wrapMethodBodyWithJavaAuxiliaryDeclarations(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, javaTranslateATree(bodytree), NIL), oDUMMYDECLARATIONSo);
        otree = listO(5, SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD, cons(wrapString("public"), NIL), cons(wrapString("String"), NIL), wrapString("toString"), listO(3, NIL, translatedmethodbody, NIL));
        unit->translation = NIL;
        return (otree);
      }
    }
  }
}

Cons* javaTranslateListOfTrees(Cons* trees) {
  { Cons* cursor = trees;

    while (!(cursor == NIL)) {
      cursor->value = javaTranslateATree(cursor->value);
      cursor = cursor->rest;
    }
    return (trees);
  }
}

Object* javaTranslateATree(Object* tree) {
  if (safePrimaryType(tree) == SGT_JAVA_TRANSLATE_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if (tree == NIL) {
        return (tree->javaTranslateAtomicTree());
      }
      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SPECIAL) {
          return (javaTranslateSpecialTree(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_VERBATIM) {
          return (javaTranslateVerbatimTree(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_UNWIND_PROTECT) {
          return (javaTranslateUnwindProtect(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_SIGNAL) {
          return (javaTranslateSignal(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_HANDLER_CASE) {
          return (javaTranslateHandlerCase(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_HANDLE_EXCEPTION) {
          return (javaTranslateHandleException(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_VOID_SYS) {
          return (javaTranslateVoidSys(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_TYPED_SYS) {
          return (javaTranslateTypedSys(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_BAD_SYS) {
          return (javaTranslateBadSys(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SETQ) {
          return (javaTranslateSetqTree(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_SET_DEFAULT) {
          return (javaTranslateSysSetDefault(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_SLOT_VALUE) {
          return (javaTranslateSysSlotValue(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_SLOT_VALUE_SETTER) {
          return (javaTranslateSysSlotValueSetter(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_METHOD) {
          return (javaTranslateMethodCall(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_FUNCTION) {
          return (javaTranslateFunctionCall(tree, NULL));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_SUPER_METHOD) {
          return (javaTranslateSuperMethodCall(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_PROGN) {
          return (javaTranslateProgn(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_WITH_PROCESS_LOCK) {
          return (javaTranslateWithProcessLock(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_LOOP) {
          return (javaTranslateLoop(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_FOREACH) {
          return (javaTranslateForeachTree(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_LET) {
          return (javaTranslateLetTree(tree));
        }
        else if ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_CAST) ||
            (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SAFE_CAST)) {
          return (javaTranslateCast(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_RETURN) {
          return (javaTranslateReturnTree(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_BREAK) {
          return (javaTranslateBreak(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_CONTINUE) {
          return (javaTranslateContinue(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_WHILE) {
          return (javaTranslateWhile(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_IF) {
          return (javaTranslateIfTree(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_CHOOSE) {
          return (javaTranslateChooseTree(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_WHEN) {
          return (javaTranslateWhenTree(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_UNLESS) {
          return (javaTranslateUnlessTree(tree));
        }
        else if ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_AND) ||
            ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_OR) ||
             ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_NOT) ||
              ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_EQp) ||
               ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_g) ||
                ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_ge) ||
                 ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_l) ||
                  ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_le) ||
                   ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_ii) ||
                    (testValue000 == SYM_JAVA_TRANSLATE_STELLA___)))))))))) {
          return (javaTranslateOperatorTree(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_COND) {
          return (javaTranslateCondTree(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_CASE) {
          return (javaTranslateCaseTree(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_MAKE) {
          return (javaTranslateMakeTree(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_NEW) {
          return (javaTranslateSysNew(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_MV_SETQ) {
          return (javaTranslateMvSetq(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_FUNCTION_CODE) {
          return (javaTranslateCallFunctionCode(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_METHOD_CODE) {
          return (javaTranslateCallMethodCode(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_SYS_INLINE_CALL) {
          return (javaTranslateInlineCallTree(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_THE_CODE) {
          return (javaTranslateTheCode(tree));
        }
        else if ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_INLINE) ||
            (testValue000 == SYM_JAVA_TRANSLATE_STELLA_IGNORE)) {
          return (javaTranslateIgnoreTree(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_PRINT_STREAM) {
          return (javaTranslatePrintStream(tree));
        }
        else if (testValue000 == SYM_JAVA_TRANSLATE_STELLA_PRINT_NATIVE_STREAM) {
          return (javaTranslatePrintNativeStream(tree));
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
      return (javaTranslateNull());
    }
    return (tree->javaTranslateAtomicTree());
  }
}

// A list of new vectors generated for variable-length argument 
//              lists
DEFINE_STELLA_SPECIAL(oVARARGSTATEMENTSo, Cons* , NULL);

// A list of vector-pushes generated for variable-length argument 
//              lists
DEFINE_STELLA_SPECIAL(oVARARGDECLSo, Cons* , NULL);

// The current index of the variable length arguments
DEFINE_STELLA_SPECIAL(oCURRENTVARARGINDEXo, int , 1);

// Mapping from STELLA operators to Java operators
KeyValueList* oJAVA_OPERATOR_TABLEo = NULL;

Cons* javaLookupOperatorTable(Symbol* operatoR) {
  { Cons* entry = ((Cons*)(oJAVA_OPERATOR_TABLEo->lookup(operatoR)));
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

const char* javaCreateCharacterSubstitutionTable() {
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
    table[((int)(unsigned char) '*')] = '$';
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

const char* oJAVA_CHARACTER_SUBSTITUTION_TABLEo = NULL;

const char* javaSubstituteForbiddenCharacters(const char* name, Keyword* caseconvention) {
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
        substitution = oJAVA_CHARACTER_SUBSTITUTION_TABLEo[((int)(unsigned char) (result[i]))];
        if (!(substitution == '=')) {
          if (caseconvention == KWD_JAVA_TRANSLATE_UPPERCASE) {
            result[i] = (oCHARACTER_DOWNCASE_TABLEo[((int)(unsigned char) substitution)]);
          }
          else if (caseconvention == KWD_JAVA_TRANSLATE_LOWERCASE) {
            result[i] = (oCHARACTER_UPCASE_TABLEo[((int)(unsigned char) substitution)]);
          }
          else if (caseconvention == KWD_JAVA_TRANSLATE_CAPITALIZED) {
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

const char* javaChangeCase(GeneralizedSymbol* symbol, Keyword* caseconvention) {
  { Module* module = ((Module*)(symbol->homeContext));
    const char* name = symbol->symbolName;
    boolean allUpperP = allUpperCaseStringP(name);
    Keyword* capsBreakKeyword = (allUpperP ? KWD_JAVA_TRANSLATE_CLEVER : KWD_JAVA_TRANSLATE_YES);

    if (!((boolean)(module))) {
      module = oMODULEo;
    }
    if (module->caseSensitiveP ||
        (!allUpperP)) {
      return (makeMatchingNameFull(name, KWD_JAVA_TRANSLATE_NO, KWD_JAVA_TRANSLATE_NO, "- ", "", "", "", "", KWD_JAVA_TRANSLATE_PRESERVE, "_"));
    }
    if (caseconvention == KWD_JAVA_TRANSLATE_UPPERCASE) {
      return (makeMatchingNameFull(name, KWD_JAVA_TRANSLATE_NO, KWD_JAVA_TRANSLATE_NO, "- ", "", "", "", "", KWD_JAVA_TRANSLATE_UPCASE, "_"));
    }
    else if (caseconvention == KWD_JAVA_TRANSLATE_LOWERCASE) {
      return (makeMatchingNameFull(name, capsBreakKeyword, KWD_JAVA_TRANSLATE_CLEVER, "- ", "", "", "", "", KWD_JAVA_TRANSLATE_TITLECASEX, ""));
    }
    else if (caseconvention == KWD_JAVA_TRANSLATE_CAPITALIZED) {
      return (makeMatchingNameFull(name, capsBreakKeyword, KWD_JAVA_TRANSLATE_CLEVER, "- ", "", "", "", "", KWD_JAVA_TRANSLATE_TITLECASE, ""));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << caseconvention << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

boolean javaLiteralP(StandardObject* typespec) {
  return (subTypeSpecOfP(typespec, SGT_JAVA_TRANSLATE_STELLA_LITERAL) &&
      ((!subTypeSpecOfP(typespec, SGT_JAVA_TRANSLATE_STELLA_STRING)) &&
       ((!subTypeSpecOfP(typespec, SGT_JAVA_TRANSLATE_STELLA_MUTABLE_STRING)) &&
        (!subTypeSpecOfP(typespec, SGT_JAVA_TRANSLATE_STELLA_CODE)))));
}

StringWrapper* javaNativeLiteralWrapperNames(StandardObject* typespec, StringWrapper*& _Return1) {
  { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(typespec));

    if (testValue000 == SGT_JAVA_TRANSLATE_STELLA_BOOLEAN) {
      { StringWrapper* _Return0 = wrapString("Boolean");

        _Return1 = wrapString("booleanValue");
        return (_Return0);
      }
    }
    else if ((testValue000 == SGT_JAVA_TRANSLATE_STELLA_INTEGER) ||
        ((testValue000 == SGT_JAVA_TRANSLATE_STELLA_SHORT_INTEGER) ||
         ((testValue000 == SGT_JAVA_TRANSLATE_STELLA_UNSIGNED_SHORT_INTEGER) ||
          ((testValue000 == SGT_JAVA_TRANSLATE_STELLA_BYTE) ||
           ((testValue000 == SGT_JAVA_TRANSLATE_STELLA_OCTET) ||
            (testValue000 == SGT_JAVA_TRANSLATE_STELLA_THIRY_TWO_BIT_VECTOR)))))) {
      { StringWrapper* _Return0 = wrapString("Integer");

        _Return1 = wrapString("intValue");
        return (_Return0);
      }
    }
    else if ((testValue000 == SGT_JAVA_TRANSLATE_STELLA_FLOAT) ||
        (testValue000 == SGT_JAVA_TRANSLATE_STELLA_DOUBLE)) {
      { StringWrapper* _Return0 = wrapString("Double");

        _Return1 = wrapString("doubleValue");
        return (_Return0);
      }
    }
    else if (testValue000 == SGT_JAVA_TRANSLATE_STELLA_CHARACTER) {
      { StringWrapper* _Return0 = wrapString("Character");

        _Return1 = wrapString("charValue");
        return (_Return0);
      }
    }
    else if (testValue000 == SGT_JAVA_TRANSLATE_STELLA_LONG_INTEGER) {
      { StringWrapper* _Return0 = wrapString("Long");

        _Return1 = wrapString("longValue");
        return (_Return0);
      }
    }
    else if (testValue000 == SGT_JAVA_TRANSLATE_STELLA_SINGLE_FLOAT) {
      { StringWrapper* _Return0 = wrapString("Float");

        _Return1 = wrapString("floatValue");
        return (_Return0);
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

StringWrapper* javaSpecialSetterName(StandardObject* typespec) {
  { Surrogate* testValue000 = typeSpecToBaseType(typespec);

    if (testValue000 == SGT_JAVA_TRANSLATE_STELLA_BOOLEAN) {
      return (wrapString("setBooleanSpecial"));
    }
    else if ((testValue000 == SGT_JAVA_TRANSLATE_STELLA_INTEGER) ||
        ((testValue000 == SGT_JAVA_TRANSLATE_STELLA_SHORT_INTEGER) ||
         ((testValue000 == SGT_JAVA_TRANSLATE_STELLA_UNSIGNED_SHORT_INTEGER) ||
          ((testValue000 == SGT_JAVA_TRANSLATE_STELLA_BYTE) ||
           ((testValue000 == SGT_JAVA_TRANSLATE_STELLA_OCTET) ||
            (testValue000 == SGT_JAVA_TRANSLATE_STELLA_THIRY_TWO_BIT_VECTOR)))))) {
      return (wrapString("setIntSpecial"));
    }
    else if ((testValue000 == SGT_JAVA_TRANSLATE_STELLA_FLOAT) ||
        (testValue000 == SGT_JAVA_TRANSLATE_STELLA_DOUBLE)) {
      return (wrapString("setDoubleSpecial"));
    }
    else if (testValue000 == SGT_JAVA_TRANSLATE_STELLA_CHARACTER) {
      return (wrapString("setCharSpecial"));
    }
    else if (testValue000 == SGT_JAVA_TRANSLATE_STELLA_LONG_INTEGER) {
      return (wrapString("setLongSpecial"));
    }
    else if (testValue000 == SGT_JAVA_TRANSLATE_STELLA_SINGLE_FLOAT) {
      return (wrapString("setFloatSpecial"));
    }
    else {
      return (wrapString("setSpecial"));
    }
  }
}

const char* javaYieldFlotsamTypeName(const char* flotsamClassName) {
  { int lastPeriod = NULL_INTEGER;
    int nextPeriod = stringPosition(flotsamClassName, '.', 0);
    const char* bareClassName = NULL;

    while (nextPeriod != NULL_INTEGER) {
      lastPeriod = nextPeriod;
      nextPeriod = stringPosition(flotsamClassName, '.', nextPeriod);
    }
    if (lastPeriod != NULL_INTEGER) {
      bareClassName = stringSubsequence(flotsamClassName, lastPeriod, NULL_INTEGER);
    }
    else {
      bareClassName = flotsamClassName;
    }
    return (makeMatchingNameFull(bareClassName, KWD_JAVA_TRANSLATE_YES, KWD_JAVA_TRANSLATE_NO, "_", "", "", "", "", KWD_JAVA_TRANSLATE_UPCASE, "-"));
  }
}

StringWrapper* javaTranslateSymbolConstantName(GeneralizedSymbol* symbol) {
  { GeneralizedSymbol* globalsymbol = ((GeneralizedSymbol*)(oSYMBOL_REGISTRYo->lookup(symbol)));
    const char* translatedname = "";
    const char* flotsamClassName = "";

    if (!(((boolean)(globalsymbol)))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Couldn't lookup symbol name for " << "`" << symbol << "'" << std::endl << "     in java-translate-symbol-constant-name" << std::endl;
    }
    flotsamClassName = javaYieldFlotsamClassName(globalsymbol->homeModule());
    translatedname = stringConcatenate(flotsamClassName, ".", 1, javaSubstituteForbiddenCharacters(globalsymbol->symbolName, KWD_JAVA_TRANSLATE_UPPERCASE));
    if (!(omitJavaPackagePrefixP(globalsymbol->homeModule(), javaYieldFlotsamTypeName(flotsamClassName)))) {
      translatedname = stringConcatenate(javaPackagePrefix(globalsymbol->homeModule(), "."), translatedname, 0);
    }
    return (wrapString(translatedname));
  }
}

StringWrapper* javaTranslateSymbolConstantId(GeneralizedSymbol* symbol) {
  { StringWrapper* translatedsymbol = javaTranslateSymbolConstantName(symbol);

    translatedsymbol->wrapperValue = stringConcatenate(translatedsymbol->wrapperValue, "_id", 0);
    return (translatedsymbol);
  }
}

StringWrapper* javaTranslateSymbolName(Symbol* symbol) {
  return (javaTranslateSymbolConstantName(symbol));
}

StringWrapper* javaTranslateSymbolId(Symbol* symbol) {
  return (javaTranslateSymbolConstantId(symbol));
}

StringWrapper* javaTranslateSurrogateName(Surrogate* surrogate) {
  return (javaTranslateSymbolConstantName(surrogate));
}

StringWrapper* javaTranslateSurrogateId(Surrogate* surrogate) {
  return (javaTranslateSymbolConstantId(surrogate));
}

StringWrapper* javaTranslateKeywordName(Keyword* keyword) {
  return (javaTranslateSymbolConstantName(keyword));
}

StringWrapper* javaTranslateKeywordId(Keyword* keyword) {
  return (javaTranslateSymbolConstantId(keyword));
}

StringWrapper* javaTranslateClassNamestring(StringWrapper* namestring) {
  { const char* translatedname = NULL;

    if (allUpperCaseStringP(namestring->wrapperValue)) {
      translatedname = makeMatchingNameFull(namestring->wrapperValue, KWD_JAVA_TRANSLATE_CLEVER, KWD_JAVA_TRANSLATE_CLEVER, "- ", "", "", "", "", KWD_JAVA_TRANSLATE_TITLECASE, "");
    }
    else {
      translatedname = makeMatchingNameFull(namestring->wrapperValue, KWD_JAVA_TRANSLATE_CLEVER, KWD_JAVA_TRANSLATE_CLEVER, "- ", "", "", "", "", KWD_JAVA_TRANSLATE_PRESERVE, "");
    }
    translatedname = javaSubstituteForbiddenCharacters(translatedname, KWD_JAVA_TRANSLATE_CAPITALIZE);
    if (javaLookupReservedWordTable(translatedname) != NULL) {
      return (wrapString(stringConcatenate("Stella_", translatedname, 0)));
    }
    else {
      return (wrapString(translatedname));
    }
  }
}

StringWrapper* javaTranslateClassName(GeneralizedSymbol* namesymbol) {
  return (javaTranslateTypeSpec(namesymbol->surrogatify()));
}

boolean inCurrentJavaPackageP(Module* module) {
  return ((module == oMODULEo) ||
      stringEqlP(javaPackagePrefix(module, "."), javaPackagePrefix(oMODULEo, ".")));
}

boolean inheritedClassNameConflictsP(const char* stellaClassName) {
  { Class* stellaClass = stringGetStellaClass(stellaClassName, false);
    Class* testClass = NULL;
    const char* javaClassName = "";
    Module* catchallModule = NULL;

    { Module* module = NULL;
      Cons* iter000 = oMODULEo->uses->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        module = ((Module*)(iter000->value));
        { 
          BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
          testClass = stringGetStellaClass(stellaClassName, false);
          if (!((boolean)(stellaClass))) {
            stellaClass = testClass;
          }
          if (((boolean)(testClass)) &&
              (!(testClass == stellaClass))) {
            return (true);
          }
        }
      }
    }
    { Context* module = NULL;
      Cons* iter001 = oMODULEo->allSuperContexts;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        module = ((Context*)(iter001->value));
        if (isaP(module, SGT_JAVA_TRANSLATE_STELLA_MODULE)) {
          { 
            BIND_STELLA_SPECIAL(oMODULEo, Module*, ((Module*)(module)));
            testClass = stringGetStellaClass(stellaClassName, false);
            if (!((boolean)(stellaClass))) {
              stellaClass = testClass;
            }
            if (((boolean)(testClass)) &&
                (!(testClass == stellaClass))) {
              return (true);
            }
          }
        }
      }
    }
    javaClassName = javaTranslateClassNamestring(wrapString(stellaClassName))->wrapperValue;
    { Module* module = NULL;
      Cons* iter002 = oMODULEo->uses->theConsList;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        module = ((Module*)(iter002->value));
        if (stringEqlP(javaClassName, javaYieldFlotsamClassName(module))) {
          if (((boolean)(stellaClass)) ||
              ((boolean)(catchallModule))) {
            return (true);
          }
          catchallModule = module;
        }
      }
    }
    { Context* module = NULL;
      Cons* iter003 = oMODULEo->allSuperContexts;

      for (; !(iter003 == NIL); iter003 = iter003->rest) {
        module = ((Context*)(iter003->value));
        if (isaP(module, SGT_JAVA_TRANSLATE_STELLA_MODULE) &&
            stringEqlP(javaClassName, javaYieldFlotsamClassName(((Module*)(module))))) {
          if (((boolean)(stellaClass)) ||
              ((boolean)(catchallModule))) {
            return (true);
          }
          catchallModule = ((Module*)(module));
        }
      }
    }
    return (false);
  }
}

boolean classNameConflictsWithSlotNameP(Class* definingClass, const char* javaClassName) {
  if (((boolean)(definingClass))) {
    { Slot* slot = NULL;
      Iterator* iter000 = definingClass->classSlots();

      for (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if (storageSlotP(slot) &&
            equalP(wrapString(javaClassName), javaTranslateName(slot->slotName))) {
          return (true);
        }
      }
    }
  }
  return (false);
}

boolean omitJavaPackagePrefixP(Module* module, const char* stellaClassName) {
  if (oCURRENT_STELLA_FEATURESo->membP(KWD_JAVA_TRANSLATE_MINIMIZE_JAVA_PREFIXES)) {
    return (inCurrentJavaPackageP(module) ||
        ((oMODULEo->uses->membP(module) ||
        oMODULEo->allSuperContexts->membP(module)) &&
         (!inheritedClassNameConflictsP(stellaClassName))));
  }
  else {
    return (inCurrentJavaPackageP(module));
  }
}

StringWrapper* javaTranslateTypeSpec(StandardObject* typeSpec) {
  return (javaTranslateTypeSpecHelper(typeSpec, false));
}

StringWrapper* javaTranslateTypeSpecForFunction(StandardObject* typeSpec) {
  return (javaTranslateTypeSpecHelper(typeSpec, true));
}

StringWrapper* javaTranslateTypeSpecHelper(StandardObject* typeSpec, boolean functionP) {
  { Surrogate* finalType = NULL;
    const char* typeName = "";

    { Surrogate* testValue000 = safePrimaryType(typeSpec);

      if (subtypeOfParametricTypeSpecifierP(testValue000)) {
        { StandardObject* typeSpec000 = typeSpec;
          ParametricTypeSpecifier* typeSpec = ((ParametricTypeSpecifier*)(typeSpec000));

          if (arrayTypeSpecifierP(typeSpec)) {
            return (javaTranslateArrayType(typeSpec));
          }
          else {
            return (javaTranslateTypeSpec(typeSpec->specifierBaseType));
          }
        }
      }
      else if (subtypeOfSurrogateP(testValue000)) {
        { StandardObject* typeSpec001 = typeSpec;
          Surrogate* typeSpec = ((Surrogate*)(typeSpec001));

          if (((StringWrapper*)(dynamicSlotValue(((Class*)(typeSpec->surrogateValue))->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_CLASS_JAVA_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue != NULL) {
            return (wrapString(((Class*)(typeSpec->surrogateValue))->javaNativeType()));
          }
          else {
            finalType = ((Class*)(typeSpec->surrogateValue))->classType;
            typeName = javaTranslateClassNamestring(wrapString(finalType->symbolName))->wrapperValue;
            if (!omitJavaPackagePrefixP(finalType->homeModule(), finalType->symbolName)) {
              return (wrapString(stringConcatenate(javaPackagePrefix(finalType->homeModule(), "."), typeName, 0)));
            }
            else if (functionP &&
                classNameConflictsWithSlotNameP(oCURRENT_JAVA_OUTPUT_CLASSo, typeName)) {
              return (wrapString(stringConcatenate(javaPackagePrefix(finalType->homeModule(), "."), typeName, 0)));
            }
            else {
              return (wrapString(typeName));
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

StringWrapper* javaTranslateArrayType(ParametricTypeSpecifier* arraytype) {
  { boolean dummy1;

    { List* dimensions = arrayTypeDimensions(arraytype);
      StandardObject* elementtype = extractParameterType(arraytype, SYM_JAVA_TRANSLATE_STELLA_ANY_VALUE, dummy1);
      const char* translatedtype = javaTranslateTypeSpec(elementtype)->wrapperValue;

      switch (dimensions->length()) {
        case 1: 
          return (wrapString(stringConcatenate(translatedtype, "[]", 0)));
        case 2: 
          return (wrapString(stringConcatenate(translatedtype, "[][]", 0)));
        case 3: 
          return (wrapString(stringConcatenate(translatedtype, "[][][]", 0)));
        default:
          { IntegerWrapper* unusedDim = NULL;
            Cons* iter000 = dimensions->theConsList;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              unusedDim = ((IntegerWrapper*)(iter000->value));
              unusedDim = unusedDim;
              translatedtype = stringConcatenate(translatedtype, "[]", 0);
            }
          }
          return (wrapString(translatedtype));
      }
    }
  }
}

StringWrapper* javaTranslateArrayOfTypeSpec(StandardObject* typespec, boolean fullyqualifiedP) {
  { const char* basetypestring = (fullyqualifiedP ? javaYieldFullyQualifiedTypeName(typespec)->wrapperValue : javaTranslateTypeSpec(typespec)->wrapperValue);

    return (wrapString(stringConcatenate(basetypestring, " []", 0)));
  }
}

StringWrapper* javaYieldRenamedReservedWord(Symbol* word) {
  return (wrapString(stringConcatenate("renamed_", stringCapitalize(word->symbolName), 0)));
}

StringHashTable* javaCreateReservedWordTable() {
  { StringHashTable* table = newStringHashTable();

    { Object* word = NULL;
      Cons* iter000 = listO(50, SYM_JAVA_TRANSLATE_STELLA_OBJECT, SYM_JAVA_TRANSLATE_STELLA_ABSTRACT, SYM_JAVA_TRANSLATE_STELLA_BOOLEAN, SYM_JAVA_TRANSLATE_STELLA_BREAK, SYM_JAVA_TRANSLATE_STELLA_BYTE, SYM_JAVA_TRANSLATE_STELLA_CASE, SYM_JAVA_TRANSLATE_STELLA_CATCH, SYM_JAVA_TRANSLATE_STELLA_CHAR, SYM_JAVA_TRANSLATE_STELLA_CLASS, SYM_JAVA_TRANSLATE_STELLA_CONST, SYM_JAVA_TRANSLATE_STELLA_CONTINUE, SYM_JAVA_TRANSLATE_STELLA_DEFAULT, SYM_JAVA_TRANSLATE_STELLA_DO, SYM_JAVA_TRANSLATE_STELLA_DOUBLE, SYM_JAVA_TRANSLATE_STELLA_ELSE, SYM_JAVA_TRANSLATE_STELLA_EXTENDS, SYM_JAVA_TRANSLATE_STELLA_FINAL, SYM_JAVA_TRANSLATE_STELLA_FINALLY, SYM_JAVA_TRANSLATE_STELLA_FLOAT, SYM_JAVA_TRANSLATE_STELLA_FOR, SYM_JAVA_TRANSLATE_STELLA_GOTO, SYM_JAVA_TRANSLATE_STELLA_IF, SYM_JAVA_TRANSLATE_STELLA_IMPLEMENTS, SYM_JAVA_TRANSLATE_STELLA_IMPORT, SYM_JAVA_TRANSLATE_STELLA_INSTANCEOF, SYM_JAVA_TRANSLATE_STELLA_INT, SYM_JAVA_TRANSLATE_STELLA_INTERFACE, SYM_JAVA_TRANSLATE_STELLA_LONG, SYM_JAVA_TRANSLATE_STELLA_NATIVE, SYM_JAVA_TRANSLATE_STELLA_NEW, SYM_JAVA_TRANSLATE_STELLA_PACKAGE, SYM_JAVA_TRANSLATE_STELLA_PRIVATE, SYM_JAVA_TRANSLATE_STELLA_PROTECTED, SYM_JAVA_TRANSLATE_STELLA_PUBLIC, SYM_JAVA_TRANSLATE_STELLA_RETURN, SYM_JAVA_TRANSLATE_STELLA_SHORT, SYM_JAVA_TRANSLATE_STELLA_STATIC, SYM_JAVA_TRANSLATE_STELLA_SUPER, SYM_JAVA_TRANSLATE_STELLA_SWITCH, SYM_JAVA_TRANSLATE_STELLA_SYNCHRONIZED, SYM_JAVA_TRANSLATE_STELLA_THROW, SYM_JAVA_TRANSLATE_STELLA_THROWS, SYM_JAVA_TRANSLATE_STELLA_TRANSIENT, SYM_JAVA_TRANSLATE_STELLA_TRY, SYM_JAVA_TRANSLATE_STELLA_VOID, SYM_JAVA_TRANSLATE_STELLA_VOLATILE, SYM_JAVA_TRANSLATE_STELLA_WHILE, SYM_JAVA_TRANSLATE_STELLA_ASSERT, SYM_JAVA_TRANSLATE_STELLA_ENUM, NIL);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        word = iter000->value;
        table->insertAt(stringDowncase(((Symbol*)(word))->symbolName), javaYieldRenamedReservedWord(((Symbol*)(word))));
        table->insertAt(stringCapitalize(((Symbol*)(word))->symbolName), javaYieldRenamedReservedWord(((Symbol*)(word))));
      }
    }
    table->insertAt("++", wrapString("stella_Increment"));
    table->insertAt("--", wrapString("stella_Decrement"));
    return (table);
  }
}

StringHashTable* oJAVA_RESERVED_WORD_TABLEo = NULL;

const char* javaLookupReservedWordTable(const char* word) {
  { StringWrapper* entry = ((StringWrapper*)(oJAVA_RESERVED_WORD_TABLEo->lookup(word)));

    if (((boolean)(entry))) {
      return (entry->wrapperValue);
    }
    else {
      return (NULL);
    }
  }
}

const char* javaTranslateNamestring(const char* namestring) {
  { const char* reservedname = javaLookupReservedWordTable(namestring);

    if (namestring == NULL) {
      return ("NULL");
    }
    if (reservedname != NULL) {
      return (reservedname);
    }
    return (javaSubstituteForbiddenCharacters(namestring, KWD_JAVA_TRANSLATE_LOWERCASE));
  }
}

StringWrapper* javaTranslateName(Symbol* namesymbol) {
  return (wrapString(javaTranslateNamestring(javaChangeCase(namesymbol, KWD_JAVA_TRANSLATE_LOWERCASE))));
}

Cons* javaTranslateSpecialTree(Cons* tree) {
  { Cons* savedeclarations = NIL;
    Cons* setforms = NIL;
    Cons* restoreforms = NIL;
    Cons* otree = NULL;

    { Object* declaration = NULL;
      Cons* iter000 = ((Cons*)(tree->rest->value));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        declaration = iter000->value;
        { Cons* d = ((Cons*)(declaration));
          Symbol* specialvariablename = ((Symbol*)(d->value));
          Object* oldvaluevariable = javaTranslateATree(localGensym(stringConcatenate("OLD-", specialvariablename->symbolName, 0)));

          savedeclarations = cons(cons(wrapString("Object"), cons(oldvaluevariable, cons(listO(6, SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CALL, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString(""), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("get"), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, javaTranslateGlobalName(specialvariablename, false), NIL), cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, NIL), NIL), NIL))), savedeclarations);
          setforms = cons(javaTranslateATree(listO(3, SYM_JAVA_TRANSLATE_STELLA_SETQ, d->value, cons(d->rest->rest->value, NIL))), setforms);
          restoreforms = cons(listO(6, SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CALL, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString(""), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("set"), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, javaTranslateGlobalName(specialvariablename, false), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, oldvaluevariable, NIL), NIL), restoreforms);
        }
      }
    }
    otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_BLOCK, savedeclarations->reverse(), cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_UNWIND_PROTECT, cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, setforms->reverse()->concatenate(javaTranslateListOfTrees(tree->rest->rest)->concatenate(NIL, 0), 0)), restoreforms->concatenate(NIL, 0)), NIL), NIL));
    return (otree);
  }
}

Cons* javaTranslateVerbatimTree(Cons* tree) {
  { Cons* cursor = tree->rest;
    Object* verbatimcode = NULL;

    while (!(cursor == NIL)) {
      if (cursor->value == KWD_JAVA_TRANSLATE_JAVA) {
        verbatimcode = cursor->rest->value;
        return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM, verbatimcode, NIL));
      }
      cursor = cursor->rest->rest;
    }
    throw *newStellaException("Verbatim has no :java option");
  }
}

Object* javaTranslateInlineCallTree(Cons* tree) {
  { Cons* calltree = ((Cons*)(tree->rest->value));
    Cons* arguments = ((calltree->value == SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_FUNCTION) ? calltree->nthRest(2) : calltree->nthRest(3));
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
                else if (testValue000 == SGT_JAVA_TRANSLATE_STELLA_CONS) {
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
                      javaOutputStatement(javaTranslateATree(copyConsTree(argument)));
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
            return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM, newVerbatimStringWrapper(inlinedbody), NIL));
          }
        }
      }
    }
    return (javaTranslateATree(calltree));
  }
}

Cons* javaTranslateUnwindProtect(Cons* tree) {
  tree->firstSetter(SYM_JAVA_TRANSLATE_STELLA_JAVA_UNWIND_PROTECT);
  tree->rest = javaTranslateListOfTrees(tree->rest);
  return (tree);
}

Cons* javaTranslateSignal(Cons* tree) {
  tree->firstSetter(SYM_JAVA_TRANSLATE_STELLA_JAVA_SIGNAL);
  tree->secondSetter(javaTranslateATree(listO(4, SYM_JAVA_TRANSLATE_STELLA_CAST, listO(3, SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_METHOD, tree->rest->rest->value, listO(3, SYM_JAVA_TRANSLATE_STELLA_FILL_IN_STACK_TRACE, tree->rest->value, NIL)), tree->rest->rest->value, NIL)));
  tree->rest->rest = NIL;
  return (tree);
}

Cons* javaTranslateHandlerCase(Cons* tree) {
  tree->firstSetter(SYM_JAVA_TRANSLATE_STELLA_JAVA_HANDLER_CASE);
  tree->rest = javaTranslateListOfTrees(tree->rest);
  return (tree);
}

Cons* javaTranslateHandleException(Cons* tree) {
  tree->firstSetter(SYM_JAVA_TRANSLATE_STELLA_JAVA_CATCH);
  tree->secondSetter(cons(javaTranslateTypeSpec(((StandardObject*)(((Cons*)(tree->rest->value))->rest->value))), cons(javaTranslateName(((Symbol*)(((Cons*)(tree->rest->value))->value))), NIL)));
  tree->rest->rest = javaTranslateListOfTrees(tree->rest->rest);
  return (tree);
}

Cons* javaTranslateVoidSys(Cons* tree) {
  return (((Cons*)(javaTranslateATree(tree->rest->value))));
}

Cons* javaTranslateTypedSys(Cons* tree) {
  return (((Cons*)(javaTranslateATree(tree->rest->value))));
}

Object* javaTranslateBadSys(Cons* tree) {
  return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM, wrapString(stringConcatenate("*** TRANSLATION FAILURE FROM ", stringify(tree->rest->value), 0)), NIL));
}

Object* javaTranslateSetqTree(Cons* tree) {
  { Symbol* variablename = ((Symbol*)(tree->rest->value));
    GlobalVariable* globalvar = variablename->softPermanentify()->lookupGlobalVariable();

    if (((boolean)(globalvar)) &&
        globalvar->variableSpecialP) {
      return (listO(5, SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION_CALL, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString(javaYieldNativeClassName()), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, javaSpecialSetterName(globalVariableTypeSpec(globalvar)), NIL), listO(4, SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, javaTranslateGlobalName(variablename, false), NIL), javaTranslateATree(tree->rest->rest->value), NIL), NIL));
    }
    else {
      return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_ASSIGN, javaTranslateATree(tree->rest->value), cons(javaTranslateATree(tree->rest->rest->value), NIL)));
    }
  }
}

Object* javaTranslateSysSetDefault(Cons* tree) {
  { Symbol* variablename = ((Symbol*)(tree->rest->value));
    GlobalVariable* globalvar = variablename->softPermanentify()->lookupGlobalVariable();

    return (listO(6, SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CALL, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString(""), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("setDefaultValue"), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, javaTranslateGlobalName(variablename, false), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, javaTranslateWithNativeWrapper(tree->rest->rest->value, (((boolean)(((StandardObject*)(dynamicSlotValue(globalvar->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_VARIABLE_TYPE_SPECIFIER, NULL))))) ? ((StandardObject*)(((StandardObject*)(dynamicSlotValue(globalvar->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_VARIABLE_TYPE_SPECIFIER, NULL))))) : globalvar->variableType)), NIL), NIL));
  }
}

Cons* javaTranslateSysSlotValueSetter(Cons* tree) {
  { Object* objectref = tree->fourth();
    Surrogate* objecttype = ((Surrogate*)(tree->rest->value));
    Symbol* slotname = trueSlotName(((Symbol*)(tree->rest->rest->value)), objecttype);
    Object* valueref = javaTranslateATree(tree->fifth());
    Cons* otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_SLOT_VALUE_SETTER, javaTranslateATree(objectref), cons(javaTranslateName(slotname), cons(valueref, NIL)));

    tree->thirdSetter(NULL);
    tree->fourthSetter(NULL);
    tree->fifthSetter(NULL);
    return (otree);
  }
}

Cons* javaTranslateSysSlotValue(Cons* tree) {
  { Surrogate* objecttype = ((Surrogate*)(tree->rest->value));
    Object* objectref = tree->fourth();
    Symbol* slotname = trueSlotName(((Symbol*)(tree->rest->rest->value)), objecttype);
    Cons* otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_SLOT_VALUE, javaTranslateATree(objectref), cons(javaTranslateName(slotname), NIL));

    return (otree);
  }
}

Cons* javaTranslateProgn(Cons* tree) {
  return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_PROGN, cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, javaTranslateListOfTrees(tree->rest)->concatenate(NIL, 0)), NIL));
}

Cons* javaTranslateWithProcessLock(Cons* tree) {
  return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_WITH_PROCESS_LOCK, javaTranslateATree(tree->rest->value), cons(cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, javaTranslateListOfTrees(tree->rest->rest)->concatenate(NIL, 0)), NIL)));
}

DEFINE_STELLA_SPECIAL(oJAVA_LOOP_NAMEo, Symbol* , NULL);

DEFINE_STELLA_SPECIAL(oJAVA_LOOP_NAME_USEDpo, boolean , false);

Cons* javaTranslateLoop(Cons* tree) {
  { 
    BIND_STELLA_SPECIAL(oJAVA_LOOP_NAMEo, Symbol*, localGensym("LOOP"));
    BIND_STELLA_SPECIAL(oJAVA_LOOP_NAME_USEDpo, boolean, false);
    { Cons* body = javaTranslateListOfTrees(tree->rest);

      if (oJAVA_LOOP_NAME_USEDpo) {
        return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_NAMED_STATEMENT, javaTranslateATree(oJAVA_LOOP_NAMEo), cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_LOOP, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_PROGN, cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, body->concatenate(NIL, 0)), NIL), NIL), NIL)));
      }
      else {
        return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_LOOP, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_PROGN, cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, body->concatenate(NIL, 0)), NIL), NIL));
      }
    }
  }
}

Cons* javaTranslateForeachTree(Cons* tree) {
  { 
    BIND_STELLA_SPECIAL(oJAVA_LOOP_NAMEo, Symbol*, localGensym("LOOP"));
    BIND_STELLA_SPECIAL(oJAVA_LOOP_NAME_USEDpo, boolean, false);
    { Cons* iteratorbindings = ((Cons*)(tree->rest->value));
      Cons* valuetrees = ((Cons*)(tree->rest->rest->value));
      Cons* nexttrees = ((Cons*)(tree->fourth()));
      Object* continuationtest = javaTranslateATree(tree->fifth());
      Cons* body = javaTranslateListOfTrees(tree->nthRest(5));
      Cons* declarations = NIL;
      Cons* valueassignments = NIL;
      Cons* nextassignments = NIL;
      Cons* variables = NIL;

      { Cons* binding = NULL;
        Cons* iter000 = iteratorbindings;
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          binding = ((Cons*)(iter000->value));
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(consList(3, javaTranslateTypeSpec(((StandardObject*)(binding->rest->value))), javaTranslateATree(binding->value), javaTranslateATree(binding->rest->rest->value)), NIL);
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
              collect000->rest = cons(consList(3, javaTranslateTypeSpec(((StandardObject*)(binding->rest->value))), javaTranslateATree(binding->value), javaTranslateATree(binding->rest->rest->value)), NIL);
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
              collect001 = cons(javaTranslateATree(tree), NIL);
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
              collect001->rest = cons(javaTranslateATree(tree), NIL);
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
              collect002 = cons(javaTranslateATree(tree), NIL);
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
              collect002->rest = cons(javaTranslateATree(tree), NIL);
              collect002 = collect002->rest;
            }
          }
        }
      }
      { Cons* decl = NULL;
        Cons* iter003 = declarations;
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
      if (oJAVA_LOOP_NAME_USEDpo) {
        return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_BLOCK, declarations, cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_NAMED_STATEMENT, javaTranslateATree(oJAVA_LOOP_NAMEo), cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_FOREACH, variables, cons(continuationtest, cons(valueassignments, cons(nextassignments, cons(body, NIL))))), NIL)), NIL), NIL)));
      }
      else {
        return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_BLOCK, declarations, cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_FOREACH, variables, cons(continuationtest, cons(valueassignments, cons(nextassignments, cons(body, NIL))))), NIL), NIL)));
      }
    }
  }
}

Cons* javaTranslateLetTree(Cons* tree) {
  { Cons* odeclarations = NIL;
    Cons* otree = NULL;

    { Object* declaration = NULL;
      Cons* iter000 = ((Cons*)(tree->rest->value));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        declaration = iter000->value;
        { Cons* d = ((Cons*)(declaration));

          odeclarations = cons(cons(javaTranslateTypeSpec(((StandardObject*)(d->rest->value))), cons(javaTranslateATree(d->value), cons(javaTranslateATree(d->rest->rest->value), NIL))), odeclarations);
        }
      }
    }
    otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_BLOCK, odeclarations->reverse(), cons(cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, javaTranslateListOfTrees(tree->rest->rest)->concatenate(NIL, 0)), NIL));
    return (otree);
  }
}

Cons* javaTranslateCast(Cons* tree) {
  { Object* expression = tree->rest->value;
    Surrogate* type = typeSpecToBaseType(((StandardObject*)(tree->rest->rest->value)));

    if (subtypeOfP(type, SGT_JAVA_TRANSLATE_STELLA_NUMBER) &&
        isaP(expression, SGT_JAVA_TRANSLATE_STELLA_NUMBER_WRAPPER)) {
      return (((Cons*)(javaTranslateATree(coerceNumericConstant(((NumberWrapper*)(expression)), type)))));
    }
    tree->firstSetter(SYM_JAVA_TRANSLATE_STELLA_JAVA_CAST);
    tree->secondSetter(javaTranslateATree(tree->rest->value));
    tree->thirdSetter(javaTranslateTypeSpec(((StandardObject*)(tree->rest->rest->value))));
    return (tree);
  }
}

Cons* javaTranslateReturnTree(Cons* tree) {
  { Cons* otree = NULL;
    Cons* returnassignments = NIL;
    Cons* methodotherreturntypes = oMETHODBEINGWALKEDo->methodReturnTypeSpecifiers_reader()->rest();
    Object* returnexpression = NULL;
    Cons* translatedreturnexpression = NIL;
    Cons* mvreturnparametertranslation = NIL;

    { Object* exp = NULL;
      Cons* iter000 = tree->rest->rest;
      int parameterindex = NULL_INTEGER;
      int iter001 = 0;
      StandardObject* parametertype = NULL;
      Cons* iter002 = methodotherreturntypes;

      for  (; (!(iter000 == NIL)) &&
                (!(iter002 == NIL)); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1,
            iter002 = iter002->rest) {
        exp = iter000->value;
        parameterindex = iter001;
        parametertype = ((StandardObject*)(iter002->value));
        if (subtypeOfP(typeSpecToBaseType(parametertype), SGT_JAVA_TRANSLATE_STELLA_LITERAL)) {
          mvreturnparametertranslation = ((Cons*)(javaTranslateATree(listO(3, SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_FUNCTION, lookupLiteralTypeInfo(typeSpecToBaseType(parametertype), KWD_JAVA_TRANSLATE_WRAP_FUNCTION), cons(exp, NIL)))));
        }
        else {
          mvreturnparametertranslation = ((Cons*)(javaTranslateATree(exp)));
        }
        returnassignments = cons(listO(4, SYM_JAVA_TRANSLATE_STELLA_JAVA_ASSIGN, listO(4, SYM_JAVA_TRANSLATE_STELLA_JAVA_AREF, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("MV_returnarray"), NIL), wrapInteger(parameterindex), NIL), mvreturnparametertranslation, NIL), returnassignments);
      }
    }
    returnassignments = returnassignments->reverse();
    returnexpression = tree->rest->value;
    if ((methodotherreturntypes->length() > 0) &&
        ((tree->rest->rest == NIL) &&
         (consP(returnexpression) &&
          (((boolean)(((Cons*)(returnexpression))->value)) &&
           ((((Cons*)(returnexpression))->value == SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_FUNCTION) ||
            (((Cons*)(returnexpression))->value == SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_METHOD)))))) {
      translatedreturnexpression = javaTranslateMvFunctionCall(((Cons*)(returnexpression)), SYM_JAVA_TRANSLATE_STELLA_MV_returnarray);
    }
    else {
      translatedreturnexpression = ((Cons*)(javaTranslateATree(returnexpression)));
    }
    if (returnassignments == NIL) {
      if (tree->rest == NIL) {
        otree = cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_RETURN, NIL);
      }
      else {
        otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_RETURN, translatedreturnexpression, NIL);
      }
    }
    else {
      { const char* tempvarname = "_return_temp";

        otree = listO(4, SYM_JAVA_TRANSLATE_STELLA_JAVA_BLOCK, cons(cons(javaTranslateTypeSpec(oMETHODBEINGWALKEDo->computeReturnTypeSpec(oMETHODBEINGWALKEDo->slotOwner)), listO(3, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString(tempvarname), NIL), translatedreturnexpression, NIL)), NIL), cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, returnassignments->concatenate(cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_RETURN, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString(tempvarname), NIL), NIL), NIL), 0)), NIL);
      }
    }
    return (otree);
  }
}

Cons* javaTranslateBreak(Cons* tree) {
  if (!((boolean)(oJAVA_LOOP_NAMEo))) {
    breakProgram("No loop name in (BREAK)");
  }
  oJAVA_LOOP_NAME_USEDpo = true;
  tree->firstSetter(SYM_JAVA_TRANSLATE_STELLA_JAVA_BREAK);
  tree->rest = cons(javaTranslateATree(oJAVA_LOOP_NAMEo), NIL);
  return (tree);
}

Cons* javaTranslateContinue(Cons* tree) {
  if (!((boolean)(oJAVA_LOOP_NAMEo))) {
    breakProgram("No loop name in (CONTINUE)");
  }
  oJAVA_LOOP_NAME_USEDpo = true;
  tree->firstSetter(SYM_JAVA_TRANSLATE_STELLA_JAVA_CONTINUE);
  tree->rest = cons(javaTranslateATree(oJAVA_LOOP_NAMEo), NIL);
  return (tree);
}

Cons* javaTranslateIfTree(Cons* tree) {
  { Object* test = javaTranslateATree(tree->rest->value);
    Cons* truebody = ((Cons*)(javaTranslateATree(tree->rest->rest->value)));
    Cons* falsebody = ((Cons*)(javaTranslateATree(tree->rest->rest->rest->value)));

    tree->rest->rest = NIL;
    if (consP(truebody->value) &&
        (!(truebody->rest == NIL))) {
      truebody = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_PROGN, cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, truebody->concatenate(NIL, 0)), NIL);
    }
    else {
      truebody = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_PROGN, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, truebody, NIL), NIL);
    }
    if (consP(falsebody->value) &&
        (!(falsebody->rest == NIL))) {
      falsebody = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_PROGN, cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, falsebody->concatenate(NIL, 0)), NIL);
    }
    else {
      falsebody = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_PROGN, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, falsebody, NIL), NIL);
    }
    return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IF, test, cons(truebody, cons(falsebody, NIL))));
  }
}

boolean javaSymbolCaseP(Object* keyform) {
  if (safePrimaryType(keyform) == SGT_JAVA_TRANSLATE_STELLA_CONS) {
    { Object* keyform000 = keyform;
      Cons* keyform = ((Cons*)(keyform000));

      return ((keyform->value == SYM_JAVA_TRANSLATE_STELLA_SYS_SLOT_VALUE) &&
          (keyform->rest->rest->value == SYM_JAVA_TRANSLATE_STELLA_SYMBOL_ID));
    }
  }
  else {
    return (false);
  }
}

Cons* javaYieldSymbolIdForm(int symbolid) {
  { Symbol* symbol = getSym(symbolid);

    return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, javaTranslateSymbolId(symbol), NIL));
  }
}

Cons* javaTranslateCondition(Cons* condition, boolean symbolcasep) {
  { Cons* translatedactions = cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, javaTranslateListOfTrees(condition->rest)->concatenate(NIL, 0));
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
                  collect000 = cons(javaYieldSymbolIdForm(((IntegerWrapper*)(key))->wrapperValue), NIL);
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
                  collect000->rest = cons(javaYieldSymbolIdForm(((IntegerWrapper*)(key))->wrapperValue), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
          translatedkeys = translatedkeyslist;
        }
      }
      else {
        translatedkeys = javaYieldSymbolIdForm(((IntegerWrapper*)(keys))->wrapperValue);
      }
    }
    else {
      translatedkeys = (consP(keys) ? javaTranslateListOfTrees(((Cons*)(keys))) : javaTranslateATree(keys));
    }
    return (cons(translatedkeys, cons(translatedactions, NIL)));
  }
}

Cons* javaTranslateCaseTree(Cons* tree) {
  { Cons* otherwisecondition = NULL;
    Cons* conditions = NIL;
    Object* keyform = NULL;
    boolean symbolcasep = false;

    symbolcasep = javaSymbolCaseP(tree->rest->value);
    keyform = javaTranslateATree(tree->rest->value);
    { Object* condition = NULL;
      Cons* iter000 = tree->rest->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        condition = iter000->value;
        if (safePrimaryType(condition) == SGT_JAVA_TRANSLATE_STELLA_CONS) {
          { Object* condition000 = condition;
            Cons* condition = ((Cons*)(condition000));

            if (condition->value == SYM_JAVA_TRANSLATE_STELLA_OTHERWISE) {
              otherwisecondition = cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, javaTranslateListOfTrees(condition->rest)->concatenate(NIL, 0));
            }
            else {
              conditions = cons(javaTranslateCondition(condition, symbolcasep), conditions);
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
    tree->rest->rest = NIL;
    return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_CASE, keyform, cons(otherwisecondition, cons(conditions->reverse(), NIL))));
  }
}

Cons* javaTranslateCondTree(Cons* tree) {
  { Cons* otherwisecondition = NULL;
    Cons* conditions = NIL;

    { Object* condition = NULL;
      Cons* iter000 = tree->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        condition = iter000->value;
        if (safePrimaryType(condition) == SGT_JAVA_TRANSLATE_STELLA_CONS) {
          { Object* condition000 = condition;
            Cons* condition = ((Cons*)(condition000));

            if (condition->value == SYM_JAVA_TRANSLATE_STELLA_OTHERWISE) {
              otherwisecondition = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_PROGN, cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, javaTranslateListOfTrees(condition->rest)->concatenate(NIL, 0)), NIL);
            }
            else {
              conditions = cons(cons(javaTranslateATree(condition->value), cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_PROGN, cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, javaTranslateListOfTrees(condition->rest)->concatenate(NIL, 0)), NIL), NIL)), conditions);
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
    return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_COND, otherwisecondition, cons(conditions->reverse(), NIL)));
  }
}

Cons* javaTranslateWhile(Cons* tree) {
  { 
    BIND_STELLA_SPECIAL(oJAVA_LOOP_NAMEo, Symbol*, localGensym("LOOP"));
    BIND_STELLA_SPECIAL(oJAVA_LOOP_NAME_USEDpo, boolean, false);
    { Object* test = javaTranslateATree(tree->rest->value);
      Cons* body = javaTranslateListOfTrees(tree->rest->rest);

      tree->rest->rest = NIL;
      if (oJAVA_LOOP_NAME_USEDpo) {
        return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_NAMED_STATEMENT, javaTranslateATree(oJAVA_LOOP_NAMEo), cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_WHILE, test, cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_PROGN, cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, body->concatenate(NIL, 0)), NIL), NIL)), NIL)));
      }
      else {
        return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_WHILE, test, cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_PROGN, cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, body->concatenate(NIL, 0)), NIL), NIL)));
      }
    }
  }
}

Cons* javaTranslateChooseTree(Cons* tree) {
  { Object* test = tree->rest->value;
    Object* truebody = tree->rest->rest->value;
    Object* falsebody = tree->rest->rest->rest->value;

    tree->rest->rest = NIL;
    return (javaTranslateOperatorCall(cons(wrapString("?"), cons(wrapString(":"), NIL)), cons(test, cons(truebody, cons(falsebody, NIL))), 3));
  }
}

Cons* javaTranslateWhenTree(Cons* tree) {
  { Object* test = javaTranslateATree(tree->rest->value);
    Cons* body = javaTranslateListOfTrees(tree->rest->rest);

    tree->rest->rest = NIL;
    return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_WHEN, test, cons(cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, body->concatenate(NIL, 0)), NIL)));
  }
}

Cons* javaTranslateUnlessTree(Cons* tree) {
  { Object* test = javaTranslateATree(tree->rest->value);
    Cons* body = javaTranslateListOfTrees(tree->rest->rest);

    tree->rest->rest = NIL;
    return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_UNLESS, test, cons(cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, body->concatenate(NIL, 0)), NIL)));
  }
}

Cons* javaTranslateMakeTree(Cons* tree) {
  { Class* clasS = ((Symbol*)(tree->rest->value))->getStellaClass(true);
    StringWrapper* classname = ((((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_CLASS_JAVA_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue != NULL) ? wrapString(clasS->javaNativeType()) : javaTranslateClassName(((GeneralizedSymbol*)(tree->rest->value))));
    Cons* otree = listO(4, SYM_JAVA_TRANSLATE_STELLA_JAVA_MAKE, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, classname, NIL), javaTranslateActualParameters(tree->rest->rest), NIL);

    return (otree);
  }
}

Cons* javaTranslateSysNew(Cons* tree) {
  { StandardObject* typespec = ((StandardObject*)(tree->rest->value));

    if (arrayTypeSpecifierP(typespec)) {
      return (javaTranslateNewArray(tree));
    }
    else {
      return (listO(5, SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION_CALL, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, javaTranslateTypeSpecForFunction(typespec), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, javaTranslateName(yieldConstructorName(typeSpecToClass(typespec))), NIL), javaTranslateActualParameters(tree->rest->rest), NIL));
    }
  }
}

Cons* javaTranslateNewArray(Cons* tree) {
  { boolean dummy1;

    { ParametricTypeSpecifier* arraytype = ((ParametricTypeSpecifier*)(tree->rest->value));
      Object* initialelement = tree->rest->rest->value;
      Cons* dimensions = javaTranslateListOfTrees(tree->rest->rest->rest);
      StandardObject* elementtype = extractParameterType(arraytype, SYM_JAVA_TRANSLATE_STELLA_ANY_VALUE, dummy1);

      initialelement = initialelement;
      return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_MAKE_ARRAY, javaTranslateTypeSpec(elementtype), dimensions->concatenate(NIL, 0)));
    }
  }
}

Cons* javaTranslateMvSetq(Cons* tree) {
  { Cons* variables = ((Cons*)(tree->rest->value));
    Cons* functioncall = ((Cons*)(tree->rest->rest->value));
    Cons* mvassignments = NIL;
    Cons* otree = NULL;
    Cons* otherreturntypes = NIL;
    Cons* mvreturnedvalue = NIL;

    if (functioncall->value == SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_FUNCTION) {
      otherreturntypes = lookupFunction(((Symbol*)(functioncall->rest->value)))->methodReturnTypeSpecifiers_reader()->rest();
    }
    else {
      otherreturntypes = ((MethodSlot*)(lookupSlot(((Class*)(((Surrogate*)(functioncall->rest->value))->surrogateValue)), ((Symbol*)(functioncall->rest->rest->value)))))->methodReturnTypeSpecifiers_reader()->rest();
    }
    { Object* variable = NULL;
      Cons* iter000 = variables->rest;
      int currentindex = NULL_INTEGER;
      int iter001 = 0;
      Object* returntype = NULL;
      Cons* iter002 = otherreturntypes;

      for  (; (!(iter000 == NIL)) &&
                (!(iter002 == NIL)); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1,
            iter002 = iter002->rest) {
        variable = iter000->value;
        currentindex = iter001;
        returntype = iter002->value;
        mvreturnedvalue = listO(4, SYM_JAVA_TRANSLATE_STELLA_JAVA_AREF, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("caller_MV_returnarray"), NIL), wrapInteger(currentindex), NIL);
        if (subtypeOfP(typeSpecToBaseType(((StandardObject*)(returntype))), SGT_JAVA_TRANSLATE_STELLA_LITERAL)) {
          mvreturnedvalue = listO(4, SYM_JAVA_TRANSLATE_STELLA_JAVA_SLOT_VALUE, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_CAST, mvreturnedvalue, cons(javaTranslateTypeSpec(typeSpecToBaseType(((StandardObject*)(returntype)))->typeToWrappedType()->yieldTypeSpecifier()), NIL)), wrapString("wrapperValue"), NIL);
        }
        mvassignments = cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_ASSIGN, javaTranslateATree(variable), cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_CAST, mvreturnedvalue, cons(javaTranslateTypeSpec(((StandardObject*)(returntype))), NIL)), NIL)), mvassignments);
      }
    }
    otree = listO(4, SYM_JAVA_TRANSLATE_STELLA_JAVA_BLOCK, cons(cons(javaTranslateArrayOfTypeSpec(SGT_JAVA_TRANSLATE_STELLA_NATIVE_OBJECT_POINTER, false), listO(3, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("caller_MV_returnarray"), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_MAKE_ARRAY, javaTranslateTypeSpec(SGT_JAVA_TRANSLATE_STELLA_NATIVE_OBJECT_POINTER), cons(wrapInteger(otherreturntypes->length()), NIL)), NIL)), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_ASSIGN, javaTranslateATree(variables->value), cons(javaTranslateMvFunctionCall(functioncall, SYM_JAVA_TRANSLATE_STELLA_caller_MV_returnarray), NIL)), mvassignments->reverse()->concatenate(NIL, 0)), NIL);
    return (otree);
  }
}

Cons* javaTranslateMvFunctionCall(Cons* functioncall, Symbol* mvvectorname) {
  return (((Cons*)(javaTranslateATree(functioncall->concatenate(cons(mvvectorname, NIL), 0)))));
}

Cons* javaTranslateCodeSignature(Cons* signature) {
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
            collect000 = cons(javaTranslateTypeSpec(((StandardObject*)(returntype))), NIL);
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
            collect000->rest = cons(javaTranslateTypeSpec(((StandardObject*)(returntype))), NIL);
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
            collect001 = cons(javaTranslateTypeSpec(((StandardObject*)(parametertype))), NIL);
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
            collect001->rest = cons(javaTranslateTypeSpec(((StandardObject*)(parametertype))), NIL);
            collect001 = collect001->rest;
          }
        }
      }
    }
    return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION_SIGNATURE, translatedreturntypes, cons(translatedparametertypes, NIL)));
  }
}

Cons* javaTranslateWithNativeWrapper(Object* tree, StandardObject* type) {
  { StringWrapper* dummy1;

    if (javaLiteralP(type)) {
      return (listO(4, SYM_JAVA_TRANSLATE_STELLA_JAVA_MAKE, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, javaNativeLiteralWrapperNames(type, dummy1), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, javaTranslateATree(tree), NIL), NIL));
    }
    else {
      return (((Cons*)(javaTranslateATree(tree))));
    }
  }
}

Cons* javaTranslateActualParametersWithNativeWrappers(Cons* trees, Cons* parametertypes) {
  { Cons* cursor = trees;
    Cons* typecursor = parametertypes;

    while (!(cursor == NIL)) {
      cursor->value = javaTranslateWithNativeWrapper(cursor->value, ((StandardObject*)(typecursor->value)));
      cursor = cursor->rest;
      typecursor = typecursor->rest;
    }
    return (trees);
  }
}

Cons* javaWrapWithNativeValueExtraction(Cons* tree, StandardObject* primaryreturntype) {
  { StringWrapper* wrappertype = NULL;
    StringWrapper* extractorname = NULL;

    wrappertype = javaNativeLiteralWrapperNames(primaryreturntype, extractorname);
    return (listO(6, SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CALL, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString(""), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, extractorname, NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_CAST, tree, cons(wrappertype, NIL)), cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, NIL), NIL));
  }
}

Cons* javaTranslateObjectToReturnType(Cons* tree, StandardObject* returntype) {
  if (javaLiteralP(returntype)) {
    return (javaWrapWithNativeValueExtraction(tree, returntype));
  }
  else if ((returntype == SGT_JAVA_TRANSLATE_STELLA_STRING) ||
      (returntype == SGT_JAVA_TRANSLATE_STELLA_MUTABLE_STRING)) {
    return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_CAST, tree, cons(javaTranslateTypeSpec(returntype), NIL)));
  }
  else if (returntype == SGT_JAVA_TRANSLATE_STELLA_VOID) {
    return (tree);
  }
  else {
    return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_CAST, tree, cons(javaTranslateTypeSpec(returntype), NIL)));
  }
}

Cons* javaTranslateCallFunctionCode(Cons* tree) {
  { Cons* signature = javaTranslateCodeSignature(((Cons*)(tree->rest->value)));
    Object* functionnameexpr = javaTranslateATree(tree->rest->rest->value);
    Cons* functionargs = tree->rest->rest->rest;
    StandardObject* primaryreturntype = ((StandardObject*)(((Cons*)(((Cons*)(tree->rest->value))->value))->value));
    Cons* otree = NULL;

    otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCALL, signature, cons(functionnameexpr, cons(cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, javaTranslateActualParametersWithNativeWrappers(functionargs, ((Cons*)(tree->rest->value))->rest)->concatenate(NIL, 0)), NIL)));
    return (javaTranslateObjectToReturnType(otree, primaryreturntype));
  }
}

Cons* javaTranslateCallMethodCode(Cons* tree) {
  { Cons* signature = javaTranslateCodeSignature(((Cons*)(tree->rest->value)));
    Object* methodnameexpr = javaTranslateATree(tree->rest->rest->value);
    StandardObject* primaryreturntype = ((StandardObject*)(((Cons*)(((Cons*)(tree->rest->value))->value))->value));
    Object* theobject = tree->rest->rest->rest->value;
    Cons* methodargs = tree->rest->rest->rest->rest;
    Cons* otree = NULL;

    otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CODE_CALL, signature, cons(methodnameexpr, cons(javaTranslateATree(theobject), cons(cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, javaTranslateActualParametersWithNativeWrappers(methodargs, ((Cons*)(tree->rest->value))->rest->rest)->concatenate(NIL, 0)), NIL))));
    return (javaTranslateObjectToReturnType(otree, primaryreturntype));
  }
}

const char* javaPackagePrefix(Module* module, const char* separator) {
  { const char* result = "";
    char separatorChar = separator[0];
    const char* packagePrefix = module->javaPackage_reader();

    if (packagePrefix != NULL) {
      if (separatorChar == '.') {
        result = packagePrefix;
      }
      else {
        result = stringSubstitute(packagePrefix, separatorChar, '.');
      }
      return (stringConcatenate(result, separator, 0));
    }
    result = stringConcatenate(javaTranslateNamestring(stringDowncase(module->name())), separator, 0);
    { Context* mod = NULL;
      Iterator* iter000 = module->parentContexts();

      for (; iter000->nextP(); ) {
        mod = ((Context*)(iter000->value));
        if (isaP(mod, SGT_JAVA_TRANSLATE_STELLA_MODULE) &&
            (!(mod == oROOT_MODULEo))) {
          result = stringConcatenate(javaPackagePrefix(((Module*)(mod)), separator), result, 0);
          break;
        }
      }
    }
    if (separatorChar == '.') {
      setDynamicSlotValue(module->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_JAVA_PACKAGE, wrapString(stringSubsequence(result, 0, strlen(result) - 1)), NULL_STRING_WRAPPER);
    }
    return (result);
  }
}

StringWrapper* javaYieldFullyQualifiedTypeName(StandardObject* typespec) {
  { Surrogate* basetypespec = typeSpecToBaseType(typespec);
    StringWrapper* translatedtype = NULL;
    const char* nativetype = ((Class*)(basetypespec->surrogateValue))->javaNativeType();

    if (basetypespec == SGT_JAVA_TRANSLATE_STELLA_ARGUMENT_LIST) {
      basetypespec = SGT_JAVA_TRANSLATE_STELLA_CONS;
      nativetype = NULL;
    }
    if (nativetype != NULL) {
      if (stringMemberP(nativetype, '.') ||
          javaLiteralP(typespec)) {
        return (wrapString(nativetype));
      }
      else {
        return (wrapString(stringConcatenate("java.lang.", nativetype, 0)));
      }
    }
    translatedtype = javaTranslateTypeSpec(basetypespec);
    if (stringMemberP(translatedtype->wrapperValue, '.')) {
      return (translatedtype);
    }
    else {
      return (wrapString(stringConcatenate(javaPackagePrefix(basetypespec->homeModule(), "."), translatedtype->wrapperValue, 0)));
    }
  }
}

StringWrapper* javaYieldTranslatedClassAndFunctionNames(MethodSlot* f, StringWrapper*& _Return1) {
  if (javaFlotsamFunctionP(f)) {
    { StringWrapper* _Return0 = wrapString(stringConcatenate(javaPackagePrefix(f->homeModule(), "."), javaYieldFlotsamClassName(f->homeModule()), 0));

      _Return1 = javaTranslateFunctionName(f);
      return (_Return0);
    }
  }
  else if (((BooleanWrapper*)(dynamicSlotValue(f->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_METHOD_NATIVEp, FALSE_WRAPPER)))->wrapperValue) {
    { StringWrapper* _Return0 = wrapString(javaYieldFullNativeClassName());

      _Return1 = javaTranslateFunctionName(f);
      return (_Return0);
    }
  }
  else if (f->methodStartupFunctionP()) {
    { StringWrapper* _Return0 = wrapString(stringConcatenate(javaPackagePrefix(f->homeModule(), "."), javaTranslateClassNamestring(wrapString(((StringWrapper*)(dynamicSlotValue(f->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME, NULL_STRING_WRAPPER)))->wrapperValue))->wrapperValue, 0));

      _Return1 = javaTranslateFunctionName(f);
      return (_Return0);
    }
  }
  else if (((BooleanWrapper*)(dynamicSlotValue(f->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_METHOD_CONSTRUCTORp, FALSE_WRAPPER)))->wrapperValue) {
    { StringWrapper* _Return0 = javaYieldFullyQualifiedTypeName(((StandardObject*)(f->methodReturnTypeSpecifiers_reader()->first())));

      _Return1 = javaTranslateFunctionName(f);
      return (_Return0);
    }
  }
  else {
    { StringWrapper* _Return0 = javaYieldFullyQualifiedTypeName(((StandardObject*)(f->methodParameterTypeSpecifiers_reader()->first())));

      _Return1 = javaTranslateFunctionName(f);
      return (_Return0);
    }
  }
}

const char* javaYieldTranslatedClassAndMethodNames(StandardObject* owner, MethodSlot* f, const char*& _Return1) {
  if (((BooleanWrapper*)(dynamicSlotValue(f->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_METHOD_NATIVEp, FALSE_WRAPPER)))->wrapperValue) {
    { const char* _Return0 = javaYieldFullNativeClassName();

      _Return1 = javaTranslateFunctionName(f)->wrapperValue;
      return (_Return0);
    }
  }
  else if (javaFlotsamFunctionP(f)) {
    { const char* _Return0 = stringConcatenate(javaPackagePrefix(f->homeModule(), "."), javaYieldFlotsamClassName(f->homeModule()), 0);

      _Return1 = javaTranslateFunctionName(f)->wrapperValue;
      return (_Return0);
    }
  }
  else if (((BooleanWrapper*)(dynamicSlotValue(f->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_METHOD_CONSTRUCTORp, FALSE_WRAPPER)))->wrapperValue) {
    { const char* _Return0 = javaYieldFullyQualifiedTypeName(((StandardObject*)(f->methodReturnTypeSpecifiers_reader()->first())))->wrapperValue;

      _Return1 = javaTranslateFunctionName(f)->wrapperValue;
      return (_Return0);
    }
  }
  else {
    { const char* _Return0 = javaYieldFullyQualifiedTypeName(owner)->wrapperValue;

      _Return1 = javaTranslateFunctionName(f)->wrapperValue;
      return (_Return0);
    }
  }
}

Cons* javaTranslateClassObjectLookup(const char* classname) {
  return (listO(5, SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION_CALL, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString(javaYieldNativeClassName()), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("find_java_class"), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, wrapString(classname), NIL), NIL));
}

Cons* javaYieldClassObjectArrayExpression(StandardObject* typespec, int ndimensions) {
  { const char* prefix = makeString(ndimensions, '[');
    Surrogate* classtype = NULL;
    const char* classid = NULL;

    { Surrogate* testValue000 = safePrimaryType(typespec);

      if (subtypeOfParametricTypeSpecifierP(testValue000)) {
        { StandardObject* typespec000 = typespec;
          ParametricTypeSpecifier* typespec = ((ParametricTypeSpecifier*)(typespec000));

          classtype = typespec->specifierBaseType;
        }
      }
      else if (subtypeOfSurrogateP(testValue000)) {
        { StandardObject* typespec001 = typespec;
          Surrogate* typespec = ((Surrogate*)(typespec001));

          classtype = ((Class*)(typespec->surrogateValue))->classType;
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    if (classtype == SGT_JAVA_TRANSLATE_STELLA_VOID) {
      throw *newStellaException("VOID is an invalid array base type.");
    }
    else if (classtype == SGT_JAVA_TRANSLATE_STELLA_BOOLEAN) {
      classid = "Z";
    }
    else if (classtype == SGT_JAVA_TRANSLATE_STELLA_INTEGER) {
      classid = "I";
    }
    else if (classtype == SGT_JAVA_TRANSLATE_STELLA_CHARACTER) {
      classid = "C";
    }
    else if ((classtype == SGT_JAVA_TRANSLATE_STELLA_BYTE) ||
        (classtype == SGT_JAVA_TRANSLATE_STELLA_OCTET)) {
      classid = "B";
    }
    else if ((classtype == SGT_JAVA_TRANSLATE_STELLA_FLOAT) ||
        (classtype == SGT_JAVA_TRANSLATE_STELLA_DOUBLE_FLOAT)) {
      classid = "D";
    }
    else if ((classtype == SGT_JAVA_TRANSLATE_STELLA_SHORT_INTEGER) ||
        (classtype == SGT_JAVA_TRANSLATE_STELLA_UNSIGNED_SHORT_INTEGER)) {
      classid = "S";
    }
    else if ((classtype == SGT_JAVA_TRANSLATE_STELLA_LONG_INTEGER) ||
        (classtype == SGT_JAVA_TRANSLATE_STELLA_UNSIGNED_LONG_INTEGER)) {
      classid = "J";
    }
    else if (classtype == SGT_JAVA_TRANSLATE_STELLA_SINGLE_FLOAT) {
      classid = "F";
    }
    else if (classtype == SGT_JAVA_TRANSLATE_STELLA_STRING) {
      classid = "Ljava.lang.String;";
    }
    else if (classtype == SGT_JAVA_TRANSLATE_STELLA_MUTABLE_STRING) {
      classid = "Ljava.lang.StringBuffer;";
    }
    else {
      classid = stringConcatenate("L", javaYieldFullyQualifiedTypeName(typespec)->wrapperValue, 1, ";");
    }
    return (javaTranslateClassObjectLookup(stringConcatenate(prefix, classid, 0)));
  }
}

Cons* javaYieldClassObjectExpression(StandardObject* typespec) {
  { boolean dummy1;

    { Cons* otree = NULL;
      Surrogate* classtype = NULL;

      { Surrogate* testValue000 = safePrimaryType(typespec);

        if (subtypeOfParametricTypeSpecifierP(testValue000)) {
          { StandardObject* typespec000 = typespec;
            ParametricTypeSpecifier* typespec = ((ParametricTypeSpecifier*)(typespec000));

            if (arrayTypeSpecifierP(typespec)) {
              return (javaYieldClassObjectArrayExpression(extractParameterType(typespec, SYM_JAVA_TRANSLATE_STELLA_ANY_VALUE, dummy1), arrayTypeDimensions(typespec)->length()));
            }
            else {
              classtype = typespec->specifierBaseType;
            }
          }
        }
        else if (subtypeOfSurrogateP(testValue000)) {
          { StandardObject* typespec001 = typespec;
            Surrogate* typespec = ((Surrogate*)(typespec001));

            classtype = ((Class*)(typespec->surrogateValue))->classType;
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      if (classtype == SGT_JAVA_TRANSLATE_STELLA_VOID) {
        otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM, wrapString("java.lang.Void.TYPE"), NIL);
      }
      else if (classtype == SGT_JAVA_TRANSLATE_STELLA_BOOLEAN) {
        otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM, wrapString("java.lang.Boolean.TYPE"), NIL);
      }
      else if ((classtype == SGT_JAVA_TRANSLATE_STELLA_INTEGER) ||
          (classtype == SGT_JAVA_TRANSLATE_STELLA_THIRTY_TWO_BIT_VECTOR)) {
        otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM, wrapString("java.lang.Integer.TYPE"), NIL);
      }
      else if (classtype == SGT_JAVA_TRANSLATE_STELLA_CHARACTER) {
        otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM, wrapString("java.lang.Character.TYPE"), NIL);
      }
      else if ((classtype == SGT_JAVA_TRANSLATE_STELLA_BYTE) ||
          (classtype == SGT_JAVA_TRANSLATE_STELLA_OCTET)) {
        otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM, wrapString("java.lang.Byte.TYPE"), NIL);
      }
      else if ((classtype == SGT_JAVA_TRANSLATE_STELLA_FLOAT) ||
          (classtype == SGT_JAVA_TRANSLATE_STELLA_DOUBLE_FLOAT)) {
        otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM, wrapString("java.lang.Double.TYPE"), NIL);
      }
      else if ((classtype == SGT_JAVA_TRANSLATE_STELLA_SHORT_INTEGER) ||
          (classtype == SGT_JAVA_TRANSLATE_STELLA_UNSIGNED_SHORT_INTEGER)) {
        otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM, wrapString("java.lang.Short.TYPE"), NIL);
      }
      else if ((classtype == SGT_JAVA_TRANSLATE_STELLA_LONG_INTEGER) ||
          ((classtype == SGT_JAVA_TRANSLATE_STELLA_UNSIGNED_LONG_INTEGER) ||
           ((classtype == SGT_JAVA_TRANSLATE_STELLA_TICKTOCK) ||
            (classtype == SGT_JAVA_TRANSLATE_STELLA_NATIVE_DATE_TIME)))) {
        otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM, wrapString("java.lang.Long.TYPE"), NIL);
      }
      else if (classtype == SGT_JAVA_TRANSLATE_STELLA_SINGLE_FLOAT) {
        otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM, wrapString("java.lang.Float.TYPE"), NIL);
      }
      else if (classtype == SGT_JAVA_TRANSLATE_STELLA_STRING) {
        otree = javaTranslateClassObjectLookup("java.lang.String");
      }
      else if (classtype == SGT_JAVA_TRANSLATE_STELLA_MUTABLE_STRING) {
        otree = javaTranslateClassObjectLookup("java.lang.StringBuffer");
      }
      else {
        if ((!(classtype == SGT_JAVA_TRANSLATE_STELLA_ARGUMENT_LIST)) &&
            (((StringWrapper*)(dynamicSlotValue(((Class*)(classtype->surrogateValue))->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_CLASS_JAVA_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue != NULL)) {
          otree = javaTranslateClassObjectLookup(yieldClassObjectLookupNameForNativeType(((Class*)(classtype->surrogateValue))->javaNativeType()));
        }
        else {
          otree = javaTranslateClassObjectLookup(javaYieldFullyQualifiedTypeName(typespec)->wrapperValue);
        }
      }
      return (otree);
    }
  }
}

KeyValueList* oJAVA_PRIMITIVE_ARRAY_TYPE_NAMESo = NULL;

const char* yieldClassObjectLookupNameForNativeType(const char* nativetype) {
  { const char* basetype = nativetype;
    const char* package = "java.lang.";
    int arraydimensions = 0;
    int index = -1;
    int arraymarkerindex = NULL_INTEGER;

    { char ch = NULL_CHARACTER;
      const char* vector000 = nativetype;
      int index000 = 0;
      int length000 = strlen(vector000);
      int i = NULL_INTEGER;
      int iter000 = 0;

      for  (; index000 < length000; 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        ch = vector000[index000];
        i = iter000;
        if (ch == '.') {
          index = i;
        }
        if (ch == '[') {
          if (arraymarkerindex == NULL_INTEGER) {
            arraymarkerindex = i;
          }
          arraydimensions = arraydimensions + 1;
        }
      }
    }
    if (index >= 0) {
      package = stringSubsequence(nativetype, 0, index + 1);
    }
    basetype = stringSubsequence(nativetype, index + 1, arraymarkerindex);
    if (((boolean)(oJAVA_PRIMITIVE_ARRAY_TYPE_NAMESo->lookup(wrapString(basetype))))) {
      basetype = ((StringWrapper*)(oJAVA_PRIMITIVE_ARRAY_TYPE_NAMESo->lookup(wrapString(basetype))))->wrapperValue;
    }
    else if (arraydimensions > 0) {
      basetype = stringConcatenate("L", package, 2, basetype, ";");
    }
    else {
      basetype = stringConcatenate(package, basetype, 0);
    }
    switch (arraydimensions) {
      case 0: 
        return (basetype);
      case 1: 
        return (stringConcatenate("[", basetype, 0));
      case 2: 
        return (stringConcatenate("[[", basetype, 0));
      default:
        return (stringConcatenate(makeString(arraydimensions, '['), basetype, 0));
    }
  }
}

Cons* javaTranslateParamTypeSpecifications(MethodSlot* fn, StandardObject* owner) {
  { Cons* paramclasses = NIL;
    boolean skipparameterP = (!fn->methodFunctionP) &&
        (!javaMethodObjectDefinedOnNativeTypeP(fn));

    { StandardObject* ts = NULL;
      Cons* iter000 = fn->methodParameterTypeSpecifiers_reader()->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        ts = ((StandardObject*)(iter000->value));
        if (skipparameterP) {
          skipparameterP = false;
        }
        else if (anchoredTypeSpecifierP(ts)) {
          paramclasses = cons(javaYieldClassObjectExpression(computeAnchoredTypeSpec(owner, ((AnchoredTypeSpecifier*)(ts)))), paramclasses);
        }
        else {
          paramclasses = cons(javaYieldClassObjectExpression(ts), paramclasses);
        }
      }
    }
    if (!(fn->methodReturnTypeSpecifiers_reader()->rest() == NIL)) {
      paramclasses = cons(javaYieldClassObjectArrayExpression(SGT_JAVA_TRANSLATE_STELLA_NATIVE_OBJECT_POINTER, 1), paramclasses);
    }
    return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_ANONYMOUS_ARRAY, wrapString("java.lang.Class"), paramclasses->reverse()->concatenate(NIL, 0)));
  }
}

Object* javaTranslateTheCode(Cons* tree) {
  { Cons* otree = NULL;
    MethodSlot* fn = NULL;
    const char* classname = "";
    const char* functionname = "";

    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->rest->value));

      if (testValue000 == KWD_JAVA_TRANSLATE_FUNCTION) {
        fn = lookupFunction(((Symbol*)(tree->rest->rest->value)));
        if (!(((boolean)(fn)))) {
          fn = ((MethodSlot*)(tree->fourth()));
        }
        if (!(((boolean)(fn)))) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't translate the-code form for function " << "`" << tree->rest->rest->value << "'" << std::endl << " because it there is no corresponding function object" << std::endl;
          return (javaTranslateNull());
        }
        { StringWrapper* value000 = NULL;
          StringWrapper* value001 = NULL;

          value000 = javaYieldTranslatedClassAndFunctionNames(fn, value001);
          {
            classname = value000->wrapperValue;
            functionname = value001->wrapperValue;
          }
        }
        otree = listO(5, SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION_CALL, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString(javaYieldNativeClassName()), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("find_java_method"), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, wrapString(classname), cons(wrapString(functionname), cons(javaTranslateParamTypeSpecifications(fn, fn->slotOwner), NIL))), NIL);
      }
      else if (testValue000 == KWD_JAVA_TRANSLATE_METHOD) {
        fn = ((MethodSlot*)(lookupSlot(((Class*)(((Surrogate*)(tree->rest->rest->value))->surrogateValue)), ((Symbol*)(tree->fourth())))));
        if (!(((boolean)(fn)))) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't translate the-code form for method " << "`" << tree->fourth() << "'" << std::endl << " because it there is no corresponding function object" << std::endl;
          return (javaTranslateNull());
        }
        classname = javaYieldTranslatedClassAndMethodNames(((StandardObject*)(tree->rest->rest->value)), fn, functionname);
        otree = listO(5, SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION_CALL, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString(javaYieldNativeClassName()), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("find_java_method"), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, wrapString(classname), cons(wrapString(functionname), cons(javaTranslateParamTypeSpecifications(fn, ((StandardObject*)(tree->rest->rest->value))), NIL))), NIL);
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

StringWrapper* javaTranslateFunctionName(MethodSlot* function) {
  { Symbol* functionname = yieldRenamedNameIfNative(function->slotName, KWD_JAVA_TRANSLATE_JAVA, KWD_JAVA_TRANSLATE_FUNCTION);
    const char* translatedname = NULL;

    if (javaMethodObjectIsOverloadedFunctionP(function)) {
      functionname = javaCreateOverloadedFunctionName(functionname, function->slotOwner);
    }
    translatedname = javaTranslateName(functionname)->wrapperValue;
    if (function->methodSetterP) {
      translatedname = stringConcatenate(translatedname, "_setter", 0);
    }
    if (slotReaderP(function)) {
      translatedname = stringConcatenate(translatedname, "_reader", 0);
    }
    return (wrapString(translatedname));
  }
}

Object* javaTranslateIgnoreTree(Cons* tree) {
  tree = tree;
  return (javaTranslateNull());
}

boolean javaStreamIsStandardOutputP(Object* tree) {
  if (safePrimaryType(tree) == SGT_JAVA_TRANSLATE_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      return (equalConsTreesP(tree, getQuotedTree("((SYS-SLOT-VALUE @OUTPUT-STREAM NATIVE-STREAM STANDARD-OUTPUT) \"/STELLA\")", "/STELLA")));
    }
  }
  else {
    return (false);
  }
}

Cons* javaTranslatePrintStream(Cons* tree) {
  tree->firstSetter(SYM_JAVA_TRANSLATE_STELLA_JAVA_PRINT_STREAM);
  if (subtypeOfKeywordP(safePrimaryType(tree->rest->value))) {
    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->rest->value));

      if ((testValue000 == KWD_JAVA_TRANSLATE_WARN) ||
          ((testValue000 == KWD_JAVA_TRANSLATE_ERROR) ||
           (testValue000 == KWD_JAVA_TRANSLATE_CONTINUABLE_ERROR))) {
        tree->secondSetter(SYM_JAVA_TRANSLATE_STELLA_JAVA_STANDARD_ERROR);
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
    if (javaStreamIsStandardOutputP(tree->rest->value) &&
        false) {
      tree->secondSetter(SYM_JAVA_TRANSLATE_STELLA_JAVA_STANDARD_OUT);
    }
    else {
      tree->secondSetter(javaTranslateATree(tree->rest->value));
    }
  }
  { Cons* args = tree->rest->rest;
    StandardObject* arg1Type = walkedExpressionType(args->value);
    StandardObject* arg2Type = walkedExpressionType(args->rest->value);

    javaTranslateListOfTrees(args);
    if ((!(args->rest == NIL)) &&
        ((!(arg1Type == SGT_JAVA_TRANSLATE_STELLA_STRING)) &&
         (!(arg2Type == SGT_JAVA_TRANSLATE_STELLA_STRING)))) {
      if (subTypeSpecOfP(arg1Type, SGT_JAVA_TRANSLATE_STELLA_OBJECT)) {
        args->firstSetter(listO(5, SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CALL, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("Object"), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("toString"), NIL), args->value, cons(cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, NIL), NIL)));
      }
      else if (subTypeSpecOfP(arg2Type, SGT_JAVA_TRANSLATE_STELLA_OBJECT)) {
        args->secondSetter(listO(5, SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CALL, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("Object"), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("toString"), NIL), args->rest->value, cons(cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, NIL), NIL)));
      }
      else {
        args->rest = cons(args->value, args->rest);
        args->firstSetter(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_LITERAL, wrapString(""), NIL));
      }
    }
    return (tree);
  }
}

Cons* javaTranslatePrintNativeStream(Cons* tree) {
  { Cons* otree = javaTranslatePrintStream(tree);

    otree->firstSetter(SYM_JAVA_TRANSLATE_STELLA_JAVA_PRINT_NATIVE_STREAM);
    return (otree);
  }
}

Cons* javaTranslateNull() {
  return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("null"), NIL));
}

Cons* javaTranslateEol() {
  return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_EOL, javaTranslateGlobalName(SYM_JAVA_TRANSLATE_STELLA_EOL, false), NIL));
}

Cons* Object::javaTranslateAtomicTree() {
  { Object* tree = this;

    return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_LITERAL, tree, NIL));
  }
}

const char* javaPrependGlobalClassName(const char* namestring, Module* module) {
  return (stringConcatenate(javaYieldFlotsamClassName(module), ".", 1, namestring));
}

StringWrapper* javaTranslateGlobalName(Symbol* namesymbol, boolean definitionP) {
  if (!((boolean)(namesymbol))) {
    return (wrapString("NULL"));
  }
  if (!(definitionP)) {
    if (namesymbol == SYM_JAVA_TRANSLATE_STELLA_TRUE) {
      return (oJAVA_TRUE_STRING_WRAPPERo);
    }
    if (namesymbol == SYM_JAVA_TRANSLATE_STELLA_FALSE) {
      return (oJAVA_FALSE_STRING_WRAPPERo);
    }
  }
  { const char* rawname = javaSubstituteForbiddenCharacters(javaChangeCase(namesymbol, KWD_JAVA_TRANSLATE_UPPERCASE), KWD_JAVA_TRANSLATE_UPPERCASE);
    Module* module = namesymbol->homeModule();

    if (definitionP) {
      return (wrapString(rawname));
    }
    else if (omitJavaPackagePrefixP(module, javaYieldFlotsamTypeName(javaYieldFlotsamClassName(module)))) {
      return (wrapString(javaPrependGlobalClassName(rawname, module)));
    }
    else {
      return (wrapString(stringConcatenate(javaPackagePrefix(module, "."), javaPrependGlobalClassName(rawname, module), 0)));
    }
  }
}

Cons* javaTranslateGeneralSymbol(Symbol* tree) {
  { GlobalVariable* globalvar = tree->softPermanentify()->lookupGlobalVariable();

    if (!((boolean)(globalvar))) {
      return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, javaTranslateName(tree), NIL));
    }
    else if (globalvar->variableSpecialP) {
      return (javaTranslateObjectToReturnType(listO(6, SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CALL, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString(""), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("get"), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, javaTranslateGlobalName(tree, false), NIL), cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, NIL), NIL), globalVariableTypeSpec(globalvar)));
    }
    else {
      return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, javaTranslateGlobalName(tree, false), NIL));
    }
  }
}

Cons* Symbol::javaTranslateAtomicTree() {
  { Symbol* tree = this;

    if (tree == SYM_JAVA_TRANSLATE_STELLA_NULL) {
      return (javaTranslateNull());
    }
    else if (tree == SYM_JAVA_TRANSLATE_STELLA_EOL) {
      return (javaTranslateEol());
    }
    else {
      return (javaTranslateGeneralSymbol(tree));
    }
  }
}

Object* javaTranslateMethodParameter(Symbol* name, StandardObject* type, MethodSlot* method) {
  type = computeRelativeTypeSpec(type, method->slotOwner);
  if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue &&
      ((variableArgumentsName(method) == name) &&
       (passVariableArgumentsAsListP(method) ||
        stringConcatenateMethodP(method)))) {
    type = yieldListifiedVariableArgumentsType(method);
  }
  return (cons(javaTranslateTypeSpec(type), cons(javaTranslateName(name), NIL)));
}

Cons* javaTranslateReturnParameter() {
  return (listO(3, wrapString("Object []"), wrapString("MV_returnarray"), NIL));
}

Cons* javaTranslateMethodParameters(MethodSlot* method) {
  { boolean skipfirstparameterP = !javaMethodObjectIsFunctionP(method);
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
        if ((!skipfirstparameterP) ||
            (i > 1)) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(javaTranslateMethodParameter(pname, ptype, method), NIL);
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
              collect000->rest = cons(javaTranslateMethodParameter(pname, ptype, method), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    if (!(method->methodReturnTypeSpecifiers_reader()->rest() == NIL)) {
      translatedparameters = translatedparameters->concatenate(cons(javaTranslateReturnParameter(), NIL), 0);
    }
    return (translatedparameters);
  }
}

boolean zeroArgumentFunctionP(MethodSlot* method) {
  return (method->methodFunctionP &&
      method->methodParameterNames_reader()->emptyP());
}

boolean javaMethodObjectDefinedOnNativeTypeP(MethodSlot* method) {
  { StandardObject* firstparametertype = ((StandardObject*)(method->methodParameterTypeSpecifiers_reader()->first()));

    return (((boolean)(firstparametertype)) &&
        (((StringWrapper*)(dynamicSlotValue(typeSpecToClass(firstparametertype)->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_CLASS_JAVA_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue != NULL));
  }
}

boolean javaMethodObjectIsOverloadedFunctionP(MethodSlot* method) {
  return ((!method->methodFunctionP) &&
      (javaMethodObjectDefinedOnNativeTypeP(method) &&
       ((!((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_METHOD_NATIVEp, FALSE_WRAPPER)))->wrapperValue) ||
        subtypeOfP(method->slotOwner, SGT_JAVA_TRANSLATE_STELLA_LITERAL))));
}

boolean javaMethodObjectIsFunctionP(MethodSlot* method) {
  return (method->methodFunctionP ||
      javaMethodObjectIsOverloadedFunctionP(method));
}

boolean javaFunctionInDifferentModuleP(MethodSlot* method) {
  { StandardObject* firstparametertype = ((StandardObject*)(method->methodParameterTypeSpecifiers_reader()->first()));

    if ((!((boolean)(firstparametertype))) ||
        (method->homeModule() == typeSpecToClass(firstparametertype)->homeModule())) {
      return (false);
    }
    else {
      {
        if (!(javaMethodObjectIsFunctionP(method))) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Method " << "`" << method << "'" << " being defined on type " << "`" << firstparametertype << "'" << ", but they are not in the same module!" << std::endl;
        }
        return (true);
      }
    }
  }
}

Symbol* javaCreateOverloadedFunctionName(Symbol* functionname, Surrogate* classtype) {
  return (internSymbolInModule(stringConcatenate(classtype->symbolName, "_", 1, functionname->symbolName), overloadedFunctionNameModule(functionname, classtype), true));
}

StringWrapper* MethodSlot::javaTranslateMethodName() {
  { MethodSlot* method = this;

    { Symbol* methodname = yieldRenamedNameIfNative(method->slotName, KWD_JAVA_TRANSLATE_JAVA, KWD_JAVA_TRANSLATE_FUNCTION);
      const char* translatedname = NULL;

      if (javaMethodObjectIsOverloadedFunctionP(method)) {
        methodname = javaCreateOverloadedFunctionName(methodname, method->slotOwner);
      }
      translatedname = javaTranslateName(methodname)->wrapperValue;
      return (wrapString(translatedname));
    }
  }
}

Cons* javaDeleteQuotedNullStatements(Cons* trees) {
  return (trees->remove(SYM_JAVA_TRANSLATE_STELLA_NULL));
}

Cons* javaWrapMethodBodyWithVarargDeclarations(Cons* methodbody) {
  return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_BLOCK, oVARARGDECLSo->reverse(), cons(methodbody, NIL)));
}

Cons* javaWrapMethodBodyWithVarargValueSetup(Cons* methodbody) {
  return (cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS, oVARARGSTATEMENTSo->reverse()->concatenate(cons(methodbody, NIL), 0)));
}

StringWrapper* javaTranslateVariableLengthArgName(Symbol* namesymbol, int parameternumber) {
  { Symbol* returnsymbol = internSymbol(stringConcatenate(namesymbol->symbolName, integerToString(((long long int)(parameternumber))), 0));
    StringWrapper* translatedname = javaTranslateName(returnsymbol);

    return (translatedname);
  }
}

Cons* javaTranslateVariableLengthActuals(Cons* actuals, MethodSlot* unusedMethod) {
  unusedMethod = unusedMethod;
  return (javaTranslateActualParameters(actuals));
}

Cons* javaTranslateActualParameters(Cons* tree) {
  return (cons(SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS, javaTranslateListOfTrees(tree)->concatenate(NIL, 0)));
}

const char* javaYieldClassNameForFunction(MethodSlot* function) {
  { const char* rawClassName = "";

    if (javaFlotsamFunctionP(function)) {
      rawClassName = javaYieldFlotsamClassName(function->homeModule());
      if (omitJavaPackagePrefixP(function->homeModule(), javaYieldFlotsamTypeName(rawClassName))) {
        return (rawClassName);
      }
      else {
        return (stringConcatenate(javaPackagePrefix(function->homeModule(), "."), rawClassName, 0));
      }
    }
    else if (((BooleanWrapper*)(dynamicSlotValue(function->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_METHOD_NATIVEp, FALSE_WRAPPER)))->wrapperValue) {
      return (javaYieldNativeClassName());
    }
    else if (function->methodStartupFunctionP()) {
      rawClassName = javaTranslateClassNamestring(wrapString(((StringWrapper*)(dynamicSlotValue(function->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME, NULL_STRING_WRAPPER)))->wrapperValue))->wrapperValue;
      if (omitJavaPackagePrefixP(function->homeModule(), javaYieldFlotsamTypeName(rawClassName))) {
        return (rawClassName);
      }
      else {
        return (stringConcatenate(javaPackagePrefix(function->homeModule(), "."), rawClassName, 0));
      }
    }
    else if (((BooleanWrapper*)(dynamicSlotValue(function->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_METHOD_CONSTRUCTORp, FALSE_WRAPPER)))->wrapperValue) {
      return (javaTranslateTypeSpecForFunction(((StandardObject*)(function->methodReturnTypeSpecifiers_reader()->first())))->wrapperValue);
    }
    else {
      return (javaTranslateTypeSpecForFunction(((StandardObject*)(function->methodParameterTypeSpecifiers_reader()->first())))->wrapperValue);
    }
  }
}

Cons* javaTranslateFunctionCall(Cons* tree, MethodSlot* method) {
  tree = tree->rest;
  { Symbol* functionname = ((Symbol*)(tree->value));
    Cons* functionargs = copyConsList(tree->rest);
    Object* firstarg = functionargs->value;
    MethodSlot* function = (((boolean)(method)) ? method : lookupFunction(functionname));
    Cons* operatoR = javaLookupOperatorTable(functionname->softPermanentify());
    Cons* otree = NULL;

    if ((functionname == SYM_JAVA_TRANSLATE_STELLA_GET_SYM) &&
        isaP(firstarg, SGT_JAVA_TRANSLATE_STELLA_INTEGER_WRAPPER)) {
      return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_SYMBOL, getSym(((IntegerWrapper*)(firstarg))->wrapperValue), NIL));
    }
    else if ((functionname == SYM_JAVA_TRANSLATE_STELLA_GET_KWD) &&
        isaP(firstarg, SGT_JAVA_TRANSLATE_STELLA_INTEGER_WRAPPER)) {
      return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_SYMBOL, getKwd(((IntegerWrapper*)(firstarg))->wrapperValue), NIL));
    }
    else if ((functionname == SYM_JAVA_TRANSLATE_STELLA_GET_SGT) &&
        isaP(firstarg, SGT_JAVA_TRANSLATE_STELLA_INTEGER_WRAPPER)) {
      return (listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_SYMBOL, getSgt(((IntegerWrapper*)(firstarg))->wrapperValue), NIL));
    }
    if (((boolean)(operatoR))) {
      otree = javaTranslateOperatorCall(operatoR, functionargs, functionargs->length());
    }
    else if (!((boolean)(function))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't translate function call: Undefined function or method " << "`" << functionname << "'" << std::endl;
      otree = NIL;
    }
    else {
      { 
        BIND_STELLA_SPECIAL(oVARARGSTATEMENTSo, Cons*, NIL);
        { Cons* actuals = (((BooleanWrapper*)(dynamicSlotValue(function->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp, FALSE_WRAPPER)))->wrapperValue ? javaTranslateVariableLengthActuals(functionargs, function) : javaTranslateActualParameters(functionargs));

          if (!((function->methodReturnTypeSpecifiers_reader()->rest() == NIL) ||
              ((actuals->length() - 1) > function->methodParameterNames_reader()->length()))) {
            actuals = actuals->concatenate(cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_MAKE_ARRAY, javaTranslateTypeSpec(SGT_JAVA_TRANSLATE_STELLA_NATIVE_OBJECT_POINTER), cons(wrapInteger(function->methodReturnTypeSpecifiers_reader()->length() - 1), NIL)), NIL), 0);
          }
          otree = listO(5, SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION_CALL, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString(javaYieldClassNameForFunction(function)), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, javaTranslateFunctionName(function), NIL), actuals, NIL);
          if (!(oVARARGSTATEMENTSo == NIL)) {
            otree = javaWrapMethodBodyWithVarargValueSetup(otree);
          }
        }
      }
    }
    return (otree);
  }
}

Cons* javaTranslateDefinedOrNull(Surrogate* classtype, Object* object, boolean nullP) {
  { const char* operatoR = (nullP ? "==" : "!=");
    Object* nullvalue = (subtypeOfP(classtype, SGT_JAVA_TRANSLATE_STELLA_LITERAL) ? typeToWalkedNullValueTree(classtype, classtype) : SYM_JAVA_TRANSLATE_STELLA_NULL);

    return (javaTranslateOperatorCall(cons(wrapString(operatoR), NIL), cons(object, cons(nullvalue, NIL)), 2));
  }
}

Cons* javaTranslateMethodCall(Cons* tree) {
  { Symbol* methodname = ((Symbol*)(tree->rest->rest->value));
    Surrogate* classtype = ((Surrogate*)(tree->rest->value));
    Cons* allargs = tree->rest->rest->rest;
    Object* object = tree->fourth();

    if (methodname == SYM_JAVA_TRANSLATE_STELLA_DEFINEDp) {
      return (javaTranslateDefinedOrNull(classtype, object, false));
    }
    else if (methodname == SYM_JAVA_TRANSLATE_STELLA_NULLp) {
      return (javaTranslateDefinedOrNull(classtype, object, true));
    }
    else if (methodname == SYM_JAVA_TRANSLATE_STELLA_CONCATENATE) {
      if (classtype == SGT_JAVA_TRANSLATE_STELLA_STRING) {
        return (javaTranslateOperatorCall(getQuotedTree("((\"+\") \"/STELLA\")", "/STELLA"), allargs, 2));
      }
    }
    else if ((methodname == SYM_JAVA_TRANSLATE_STELLA_NTH) ||
        (methodname == SYM_JAVA_TRANSLATE_STELLA_NTH_SETTER)) {
      return (javaTranslateNthMethodCall(methodname, classtype, allargs));
    }
    else if ((methodname == SYM_JAVA_TRANSLATE_STELLA_AREF) ||
        (methodname == SYM_JAVA_TRANSLATE_STELLA_AREF_SETTER)) {
      return (javaTranslateArefMethodCall(methodname, classtype, allargs));
    }
    else {
    }
    return (javaTranslateNormalMethodCall(methodname, classtype, allargs));
  }
}

Object* javaTranslateSuperMethodCall(Cons* tree) {
  { Cons* otree = javaTranslateNormalMethodCall(((Symbol*)(tree->rest->rest->value)), ((Surrogate*)(tree->rest->value)), tree->rest->rest->rest);

    otree->fourthSetter(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, wrapString("super"), NIL));
    return (otree);
  }
}

Cons* javaTranslateNormalMethodCall(Symbol* methodname, Surrogate* classtype, Cons* allargs) {
  { Slot* slot = lookupSlot(((Class*)(classtype->surrogateValue)), methodname);
    MethodSlot* methodslot = ((((boolean)(slot)) &&
        isaP(slot, SGT_JAVA_TRANSLATE_STELLA_METHOD_SLOT)) ? ((MethodSlot*)(slot)) : NULL);
    Object* object = allargs->value;
    Cons* operatoR = javaLookupOperatorTable(methodname->softPermanentify());

    if (((boolean)(methodslot)) &&
        javaMethodObjectIsOverloadedFunctionP(methodslot)) {
      return (javaTranslateFunctionCall(listO(3, SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_FUNCTION, javaCreateOverloadedFunctionName(methodname, classtype), allargs->concatenate(NIL, 0)), methodslot));
    }
    if (((boolean)(operatoR))) {
      return (javaTranslateOperatorCall(operatoR, allargs, allargs->length()));
    }
    else {
      return (listO(5, SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CALL, listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, javaTranslateClassName(internSymbolInModule(classtype->symbolName, ((Module*)(classtype->homeContext)), false)), NIL), listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT, (((boolean)(methodslot)) ? methodslot->javaTranslateMethodName() : javaTranslateName(methodname)), NIL), javaTranslateATree(object), cons(((((boolean)(methodslot)) &&
          ((!(methodslot->methodReturnTypeSpecifiers_reader()->rest() == NIL)) &&
           (allargs->length() <= methodslot->methodParameterNames_reader()->length()))) ? javaTranslateActualParameters(allargs->rest)->concatenate(cons(listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_MAKE_ARRAY, javaTranslateTypeSpec(SGT_JAVA_TRANSLATE_STELLA_NATIVE_OBJECT_POINTER), cons(wrapInteger(methodslot->methodReturnTypeSpecifiers_reader()->length() - 1), NIL)), NIL), 0) : javaTranslateActualParameters(allargs->rest)), NIL)));
    }
  }
}

Cons* javaTranslateOperatorTree(Cons* tree) {
  { Cons* operatoR = javaLookupOperatorTable(((Symbol*)(tree->value)));
    Cons* args = tree->rest;
    int arity = NULL_INTEGER;

    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

      if ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_AND) ||
          ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_OR) ||
           ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_EQp) ||
            ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_g) ||
             ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_ge) ||
              ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_l) ||
               (testValue000 == SYM_JAVA_TRANSLATE_STELLA_le))))))) {
        arity = 2;
      }
      else if ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_NOT) ||
          ((testValue000 == SYM_JAVA_TRANSLATE_STELLA_ii) ||
           (testValue000 == SYM_JAVA_TRANSLATE_STELLA___))) {
        arity = 1;
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    return (javaTranslateOperatorCall(operatoR, args, arity));
  }
}

Cons* javaTranslateOperatorCall(Cons* operatornames, Cons* arguments, int arity) {
  { Cons* otree = NULL;

    switch (arity) {
      case 1: 
        otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_UNARY_OP, operatornames->value, cons(javaTranslateATree(arguments->value), NIL));
        break;
      case 2: 
        if (arguments->length() > 2) {
          otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_BINARY_OP, javaTranslateATree(arguments->value), cons(operatornames->value, cons(javaTranslateOperatorCall(operatornames, arguments->rest, 2), NIL)));
        }
        else {
          otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_BINARY_OP, javaTranslateATree(arguments->value), cons(operatornames->value, cons(javaTranslateATree(arguments->rest->value), NIL)));
        }
        break;
      case 3: 
        otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_TERNARY_OP, javaTranslateATree(arguments->value), cons(operatornames->value, cons(javaTranslateATree(arguments->rest->value), cons(operatornames->rest->value, cons(javaTranslateATree(arguments->rest->rest->value), NIL)))));
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

Cons* javaTranslateArefMethodCall(Symbol* operatoR, Surrogate* owner, Cons* arguments) {
  if (owner == SGT_JAVA_TRANSLATE_STELLA_ARRAY) {
    { boolean setterP = operatoR == SYM_JAVA_TRANSLATE_STELLA_AREF_SETTER;
      Cons* otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_AREF, javaTranslateATree(arguments->value), javaTranslateListOfTrees((setterP ? arguments->rest->rest : arguments->rest))->concatenate(NIL, 0));

      if (setterP) {
        otree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_ASSIGN, otree, cons(javaTranslateATree(arguments->rest->value), NIL));
      }
      return (otree);
    }
  }
  else {
    return (javaTranslateNormalMethodCall(operatoR, owner, arguments));
  }
}

Cons* javaTranslateNthMethodCall(Symbol* operatoR, Surrogate* owner, Cons* arguments) {
  { boolean setterP = operatoR == SYM_JAVA_TRANSLATE_STELLA_NTH_SETTER;
    Object* collection = arguments->value;
    Object* position = arguments->last();
    Object* value = (setterP ? arguments->rest->value : ((Object*)(NULL)));
    Cons* tree = NULL;

    if (owner == SGT_JAVA_TRANSLATE_STELLA_NATIVE_VECTOR) {
      tree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_AREF, javaTranslateATree(collection), cons(javaTranslateATree(position), NIL));
      if (setterP) {
        tree = listO(3, SYM_JAVA_TRANSLATE_STELLA_JAVA_ASSIGN, tree, cons(javaTranslateATree(value), NIL));
      }
      return (tree);
    }
    else {
    }
    return (javaTranslateNormalMethodCall(operatoR, owner, arguments));
  }
}

void helpStartupJavaTranslate1() {
  {
    SYM_JAVA_TRANSLATE_STELLA_JAVA_FLOTSAM_CLASS = ((Symbol*)(internRigidSymbolWrtModule("JAVA-FLOTSAM-CLASS", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_GLOBAL_VARIABLE = ((Symbol*)(internRigidSymbolWrtModule("GLOBAL-VARIABLE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_CLASS = ((Symbol*)(internRigidSymbolWrtModule("CLASS", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_TYPE = ((Symbol*)(internRigidSymbolWrtModule("TYPE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_METHOD = ((Symbol*)(internRigidSymbolWrtModule("METHOD", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_MACRO = ((Symbol*)(internRigidSymbolWrtModule("MACRO", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_PRINT_METHOD = ((Symbol*)(internRigidSymbolWrtModule("PRINT-METHOD", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_STARTUP_TIME_PROGN = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-TIME-PROGN", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_VERBATIM = ((Symbol*)(internRigidSymbolWrtModule("VERBATIM", NULL, 0)));
    KWD_JAVA_TRANSLATE_UNBOUND_SPECIAL_VARIABLE = ((Keyword*)(internRigidSymbolWrtModule("UNBOUND-SPECIAL-VARIABLE", NULL, 2)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_GLOBAL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_GLOBAL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_TYPE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_TYPE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_MAKE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_MAKE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT = ((Symbol*)(internRigidSymbolWrtModule("JAVA_IDENT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS = ((Symbol*)(internRigidSymbolWrtModule("JAVA_ACTUALS", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS = ((Symbol*)(internRigidSymbolWrtModule("JAVA_STATEMENTS", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_BLOCK = ((Symbol*)(internRigidSymbolWrtModule("JAVA_BLOCK", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_THIS = ((Symbol*)(internRigidSymbolWrtModule("THIS", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_COMMENT = ((Symbol*)(internRigidSymbolWrtModule("JAVA_COMMENT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("JAVA_FUNCTION", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD = ((Symbol*)(internRigidSymbolWrtModule("JAVA_METHOD", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SELF = ((Symbol*)(internRigidSymbolWrtModule("SELF", NULL, 0)));
    SGT_JAVA_TRANSLATE_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SYM_JAVA_TRANSLATE_STELLA_SPECIAL = ((Symbol*)(internRigidSymbolWrtModule("SPECIAL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_UNWIND_PROTECT = ((Symbol*)(internRigidSymbolWrtModule("SYS-UNWIND-PROTECT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_SIGNAL = ((Symbol*)(internRigidSymbolWrtModule("SYS-SIGNAL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_HANDLER_CASE = ((Symbol*)(internRigidSymbolWrtModule("SYS-HANDLER-CASE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_HANDLE_EXCEPTION = ((Symbol*)(internRigidSymbolWrtModule("SYS-HANDLE-EXCEPTION", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_VOID_SYS = ((Symbol*)(internRigidSymbolWrtModule("VOID-SYS", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_TYPED_SYS = ((Symbol*)(internRigidSymbolWrtModule("TYPED-SYS", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_BAD_SYS = ((Symbol*)(internRigidSymbolWrtModule("BAD-SYS", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_SET_DEFAULT = ((Symbol*)(internRigidSymbolWrtModule("SYS-SET-DEFAULT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SYS-SLOT-VALUE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_SLOT_VALUE_SETTER = ((Symbol*)(internRigidSymbolWrtModule("SYS-SLOT-VALUE-SETTER", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_METHOD = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-METHOD", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-FUNCTION", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_SUPER_METHOD = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-SUPER-METHOD", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("PROGN", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_WITH_PROCESS_LOCK = ((Symbol*)(internRigidSymbolWrtModule("WITH-PROCESS-LOCK", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_LOOP = ((Symbol*)(internRigidSymbolWrtModule("LOOP", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("SYS-FOREACH", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_LET = ((Symbol*)(internRigidSymbolWrtModule("LET", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_CAST = ((Symbol*)(internRigidSymbolWrtModule("CAST", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SAFE_CAST = ((Symbol*)(internRigidSymbolWrtModule("SAFE-CAST", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_RETURN = ((Symbol*)(internRigidSymbolWrtModule("RETURN", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_BREAK = ((Symbol*)(internRigidSymbolWrtModule("BREAK", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_CONTINUE = ((Symbol*)(internRigidSymbolWrtModule("CONTINUE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_WHILE = ((Symbol*)(internRigidSymbolWrtModule("WHILE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_IF = ((Symbol*)(internRigidSymbolWrtModule("IF", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_CHOOSE = ((Symbol*)(internRigidSymbolWrtModule("CHOOSE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_WHEN = ((Symbol*)(internRigidSymbolWrtModule("WHEN", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_UNLESS = ((Symbol*)(internRigidSymbolWrtModule("UNLESS", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_OR = ((Symbol*)(internRigidSymbolWrtModule("OR", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_EQp = ((Symbol*)(internRigidSymbolWrtModule("EQ?", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_g = ((Symbol*)(internRigidSymbolWrtModule(">", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_ge = ((Symbol*)(internRigidSymbolWrtModule(">=", NULL, 0)));
  }
}

void helpStartupJavaTranslate2() {
  {
    SYM_JAVA_TRANSLATE_STELLA_l = ((Symbol*)(internRigidSymbolWrtModule("<", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_le = ((Symbol*)(internRigidSymbolWrtModule("<=", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_ii = ((Symbol*)(internRigidSymbolWrtModule("++", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA___ = ((Symbol*)(internRigidSymbolWrtModule("--", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_COND = ((Symbol*)(internRigidSymbolWrtModule("COND", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_CASE = ((Symbol*)(internRigidSymbolWrtModule("CASE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_MAKE = ((Symbol*)(internRigidSymbolWrtModule("MAKE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_NEW = ((Symbol*)(internRigidSymbolWrtModule("SYS-NEW", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_MV_SETQ = ((Symbol*)(internRigidSymbolWrtModule("MV-SETQ", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_FUNCTION_CODE = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-FUNCTION-CODE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_METHOD_CODE = ((Symbol*)(internRigidSymbolWrtModule("SYS-CALL-METHOD-CODE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYS_INLINE_CALL = ((Symbol*)(internRigidSymbolWrtModule("SYS-INLINE-CALL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_THE_CODE = ((Symbol*)(internRigidSymbolWrtModule("THE-CODE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_INLINE = ((Symbol*)(internRigidSymbolWrtModule("INLINE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_IGNORE = ((Symbol*)(internRigidSymbolWrtModule("IGNORE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_PRINT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("PRINT-STREAM", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_PRINT_NATIVE_STREAM = ((Symbol*)(internRigidSymbolWrtModule("PRINT-NATIVE-STREAM", NULL, 0)));
    SGT_JAVA_TRANSLATE_STELLA_KEY_VALUE_LIST = ((Surrogate*)(internRigidSymbolWrtModule("KEY-VALUE-LIST", NULL, 1)));
    SYM_JAVA_TRANSLATE_STELLA_i = ((Symbol*)(internRigidSymbolWrtModule("+", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA__ = ((Symbol*)(internRigidSymbolWrtModule("-", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_o = ((Symbol*)(internRigidSymbolWrtModule("*", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_s = ((Symbol*)(internRigidSymbolWrtModule("/", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_eg = ((Symbol*)(internRigidSymbolWrtModule("=>", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_el = ((Symbol*)(internRigidSymbolWrtModule("=<", NULL, 0)));
    KWD_JAVA_TRANSLATE_UPPERCASE = ((Keyword*)(internRigidSymbolWrtModule("UPPERCASE", NULL, 2)));
    KWD_JAVA_TRANSLATE_LOWERCASE = ((Keyword*)(internRigidSymbolWrtModule("LOWERCASE", NULL, 2)));
    KWD_JAVA_TRANSLATE_CAPITALIZED = ((Keyword*)(internRigidSymbolWrtModule("CAPITALIZED", NULL, 2)));
    KWD_JAVA_TRANSLATE_CLEVER = ((Keyword*)(internRigidSymbolWrtModule("CLEVER", NULL, 2)));
    KWD_JAVA_TRANSLATE_YES = ((Keyword*)(internRigidSymbolWrtModule("YES", NULL, 2)));
    KWD_JAVA_TRANSLATE_NO = ((Keyword*)(internRigidSymbolWrtModule("NO", NULL, 2)));
    KWD_JAVA_TRANSLATE_PRESERVE = ((Keyword*)(internRigidSymbolWrtModule("PRESERVE", NULL, 2)));
    KWD_JAVA_TRANSLATE_UPCASE = ((Keyword*)(internRigidSymbolWrtModule("UPCASE", NULL, 2)));
    KWD_JAVA_TRANSLATE_TITLECASEX = ((Keyword*)(internRigidSymbolWrtModule("TITLECASEX", NULL, 2)));
    KWD_JAVA_TRANSLATE_TITLECASE = ((Keyword*)(internRigidSymbolWrtModule("TITLECASE", NULL, 2)));
    SGT_JAVA_TRANSLATE_STELLA_LITERAL = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_STRING = ((Surrogate*)(internRigidSymbolWrtModule("STRING", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_MUTABLE_STRING = ((Surrogate*)(internRigidSymbolWrtModule("MUTABLE-STRING", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_CODE = ((Surrogate*)(internRigidSymbolWrtModule("CODE", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_SHORT_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("SHORT-INTEGER", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_UNSIGNED_SHORT_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("UNSIGNED-SHORT-INTEGER", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_BYTE = ((Surrogate*)(internRigidSymbolWrtModule("BYTE", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_OCTET = ((Surrogate*)(internRigidSymbolWrtModule("OCTET", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_THIRY_TWO_BIT_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("THIRY-TWO-BIT-VECTOR", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_DOUBLE = ((Surrogate*)(internRigidSymbolWrtModule("DOUBLE", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_CHARACTER = ((Surrogate*)(internRigidSymbolWrtModule("CHARACTER", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_LONG_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("LONG-INTEGER", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_SINGLE_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("SINGLE-FLOAT", NULL, 1)));
    KWD_JAVA_TRANSLATE_CAPITALIZE = ((Keyword*)(internRigidSymbolWrtModule("CAPITALIZE", NULL, 2)));
    SGT_JAVA_TRANSLATE_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", NULL, 1)));
    KWD_JAVA_TRANSLATE_MINIMIZE_JAVA_PREFIXES = ((Keyword*)(internRigidSymbolWrtModule("MINIMIZE-JAVA-PREFIXES", NULL, 2)));
    SYM_JAVA_TRANSLATE_STELLA_CLASS_JAVA_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-JAVA-NATIVE-TYPE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_ANY_VALUE = ((Symbol*)(internRigidSymbolWrtModule("ANY-VALUE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("OBJECT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_ABSTRACT = ((Symbol*)(internRigidSymbolWrtModule("ABSTRACT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_BOOLEAN = ((Symbol*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_BYTE = ((Symbol*)(internRigidSymbolWrtModule("BYTE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_CATCH = ((Symbol*)(internRigidSymbolWrtModule("CATCH", NULL, 0)));
  }
}

void helpStartupJavaTranslate3() {
  {
    SYM_JAVA_TRANSLATE_STELLA_CHAR = ((Symbol*)(internRigidSymbolWrtModule("CHAR", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_CONST = ((Symbol*)(internRigidSymbolWrtModule("CONST", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_DEFAULT = ((Symbol*)(internRigidSymbolWrtModule("DEFAULT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_DO = ((Symbol*)(internRigidSymbolWrtModule("DO", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_DOUBLE = ((Symbol*)(internRigidSymbolWrtModule("DOUBLE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_ELSE = ((Symbol*)(internRigidSymbolWrtModule("ELSE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_EXTENDS = ((Symbol*)(internRigidSymbolWrtModule("EXTENDS", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_FINAL = ((Symbol*)(internRigidSymbolWrtModule("FINAL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_FINALLY = ((Symbol*)(internRigidSymbolWrtModule("FINALLY", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_FLOAT = ((Symbol*)(internRigidSymbolWrtModule("FLOAT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_FOR = ((Symbol*)(internRigidSymbolWrtModule("FOR", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_GOTO = ((Symbol*)(internRigidSymbolWrtModule("GOTO", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_IMPLEMENTS = ((Symbol*)(internRigidSymbolWrtModule("IMPLEMENTS", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_IMPORT = ((Symbol*)(internRigidSymbolWrtModule("IMPORT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_INSTANCEOF = ((Symbol*)(internRigidSymbolWrtModule("INSTANCEOF", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_INT = ((Symbol*)(internRigidSymbolWrtModule("INT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_INTERFACE = ((Symbol*)(internRigidSymbolWrtModule("INTERFACE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_LONG = ((Symbol*)(internRigidSymbolWrtModule("LONG", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_NATIVE = ((Symbol*)(internRigidSymbolWrtModule("NATIVE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_NEW = ((Symbol*)(internRigidSymbolWrtModule("NEW", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_PACKAGE = ((Symbol*)(internRigidSymbolWrtModule("PACKAGE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_PRIVATE = ((Symbol*)(internRigidSymbolWrtModule("PRIVATE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_PROTECTED = ((Symbol*)(internRigidSymbolWrtModule("PROTECTED", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_PUBLIC = ((Symbol*)(internRigidSymbolWrtModule("PUBLIC", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SHORT = ((Symbol*)(internRigidSymbolWrtModule("SHORT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_STATIC = ((Symbol*)(internRigidSymbolWrtModule("STATIC", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SUPER = ((Symbol*)(internRigidSymbolWrtModule("SUPER", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SWITCH = ((Symbol*)(internRigidSymbolWrtModule("SWITCH", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYNCHRONIZED = ((Symbol*)(internRigidSymbolWrtModule("SYNCHRONIZED", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_THROW = ((Symbol*)(internRigidSymbolWrtModule("THROW", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_THROWS = ((Symbol*)(internRigidSymbolWrtModule("THROWS", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_TRANSIENT = ((Symbol*)(internRigidSymbolWrtModule("TRANSIENT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_TRY = ((Symbol*)(internRigidSymbolWrtModule("TRY", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_VOID = ((Symbol*)(internRigidSymbolWrtModule("VOID", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_VOLATILE = ((Symbol*)(internRigidSymbolWrtModule("VOLATILE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_ASSERT = ((Symbol*)(internRigidSymbolWrtModule("ASSERT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_ENUM = ((Symbol*)(internRigidSymbolWrtModule("ENUM", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CALL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_METHOD_CALL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_UNWIND_PROTECT = ((Symbol*)(internRigidSymbolWrtModule("JAVA_UNWIND_PROTECT", NULL, 0)));
    KWD_JAVA_TRANSLATE_JAVA = ((Keyword*)(internRigidSymbolWrtModule("JAVA", NULL, 2)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM = ((Symbol*)(internRigidSymbolWrtModule("JAVA_VERBATIM", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_SIGNAL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_SIGNAL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_FILL_IN_STACK_TRACE = ((Symbol*)(internRigidSymbolWrtModule("FILL-IN-STACK-TRACE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_HANDLER_CASE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_HANDLER_CASE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_CATCH = ((Symbol*)(internRigidSymbolWrtModule("JAVA_CATCH", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION_CALL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_FUNCTION_CALL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_ASSIGN = ((Symbol*)(internRigidSymbolWrtModule("JAVA_ASSIGN", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_VARIABLE_TYPE_SPECIFIER = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-TYPE-SPECIFIER", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_SLOT_VALUE_SETTER = ((Symbol*)(internRigidSymbolWrtModule("JAVA_SLOT_VALUE_SETTER", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_SLOT_VALUE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("JAVA_PROGN", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_WITH_PROCESS_LOCK = ((Symbol*)(internRigidSymbolWrtModule("JAVA_WITH_PROCESS_LOCK", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_NAMED_STATEMENT = ((Symbol*)(internRigidSymbolWrtModule("JAVA_NAMED_STATEMENT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_LOOP = ((Symbol*)(internRigidSymbolWrtModule("JAVA_LOOP", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("JAVA_FOREACH", NULL, 0)));
    SGT_JAVA_TRANSLATE_STELLA_NUMBER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", NULL, 1)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_CAST = ((Symbol*)(internRigidSymbolWrtModule("JAVA_CAST", NULL, 0)));
    KWD_JAVA_TRANSLATE_WRAP_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("WRAP-FUNCTION", NULL, 2)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_AREF = ((Symbol*)(internRigidSymbolWrtModule("JAVA_AREF", NULL, 0)));
  }
}

void helpStartupJavaTranslate4() {
  {
    SYM_JAVA_TRANSLATE_STELLA_MV_returnarray = ((Symbol*)(internRigidSymbolWrtModule("MV_returnarray", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_RETURN = ((Symbol*)(internRigidSymbolWrtModule("JAVA_RETURN", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_BREAK = ((Symbol*)(internRigidSymbolWrtModule("JAVA_BREAK", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_CONTINUE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_CONTINUE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_IF = ((Symbol*)(internRigidSymbolWrtModule("JAVA_IF", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_SYMBOL_ID = ((Symbol*)(internRigidSymbolWrtModule("SYMBOL-ID", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_OTHERWISE = ((Symbol*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_CASE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_CASE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_COND = ((Symbol*)(internRigidSymbolWrtModule("JAVA_COND", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_WHILE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_WHILE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_WHEN = ((Symbol*)(internRigidSymbolWrtModule("JAVA_WHEN", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_UNLESS = ((Symbol*)(internRigidSymbolWrtModule("JAVA_UNLESS", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_MAKE_ARRAY = ((Symbol*)(internRigidSymbolWrtModule("JAVA_MAKE_ARRAY", NULL, 0)));
    SGT_JAVA_TRANSLATE_STELLA_NATIVE_OBJECT_POINTER = ((Surrogate*)(internRigidSymbolWrtModule("NATIVE-OBJECT-POINTER", NULL, 1)));
    SYM_JAVA_TRANSLATE_STELLA_caller_MV_returnarray = ((Symbol*)(internRigidSymbolWrtModule("caller_MV_returnarray", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION_SIGNATURE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_FUNCTION_SIGNATURE", NULL, 0)));
    SGT_JAVA_TRANSLATE_STELLA_VOID = ((Surrogate*)(internRigidSymbolWrtModule("VOID", NULL, 1)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCALL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_FUNCALL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CODE_CALL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_METHOD_CODE_CALL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_PACKAGE = ((Symbol*)(internRigidSymbolWrtModule("JAVA-PACKAGE", NULL, 0)));
    SGT_JAVA_TRANSLATE_STELLA_ARGUMENT_LIST = ((Surrogate*)(internRigidSymbolWrtModule("ARGUMENT-LIST", NULL, 1)));
    SYM_JAVA_TRANSLATE_STELLA_METHOD_NATIVEp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-NATIVE?", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_METHOD_CONSTRUCTORp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-CONSTRUCTOR?", NULL, 0)));
    SGT_JAVA_TRANSLATE_STELLA_DOUBLE_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("DOUBLE-FLOAT", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_UNSIGNED_LONG_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("UNSIGNED-LONG-INTEGER", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_THIRTY_TWO_BIT_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("THIRTY-TWO-BIT-VECTOR", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_TICKTOCK = ((Surrogate*)(internRigidSymbolWrtModule("TICKTOCK", NULL, 1)));
    SGT_JAVA_TRANSLATE_STELLA_NATIVE_DATE_TIME = ((Surrogate*)(internRigidSymbolWrtModule("NATIVE-DATE-TIME", NULL, 1)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_ANONYMOUS_ARRAY = ((Symbol*)(internRigidSymbolWrtModule("JAVA_ANONYMOUS_ARRAY", NULL, 0)));
    KWD_JAVA_TRANSLATE_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    KWD_JAVA_TRANSLATE_METHOD = ((Keyword*)(internRigidSymbolWrtModule("METHOD", NULL, 2)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_PRINT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("JAVA_PRINT_STREAM", NULL, 0)));
    KWD_JAVA_TRANSLATE_WARN = ((Keyword*)(internRigidSymbolWrtModule("WARN", NULL, 2)));
    KWD_JAVA_TRANSLATE_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    KWD_JAVA_TRANSLATE_CONTINUABLE_ERROR = ((Keyword*)(internRigidSymbolWrtModule("CONTINUABLE-ERROR", NULL, 2)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_STANDARD_ERROR = ((Symbol*)(internRigidSymbolWrtModule("JAVA_STANDARD_ERROR", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_STANDARD_OUT = ((Symbol*)(internRigidSymbolWrtModule("JAVA_STANDARD_OUT", NULL, 0)));
    SGT_JAVA_TRANSLATE_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_LITERAL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_LITERAL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_PRINT_NATIVE_STREAM = ((Symbol*)(internRigidSymbolWrtModule("JAVA_PRINT_NATIVE_STREAM", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_EOL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_EOL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_EOL = ((Symbol*)(internRigidSymbolWrtModule("EOL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-VARIABLE-ARGUMENTS?", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_GET_SYM = ((Symbol*)(internRigidSymbolWrtModule("GET-SYM", NULL, 0)));
    SGT_JAVA_TRANSLATE_STELLA_INTEGER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-WRAPPER", NULL, 1)));
    SYM_JAVA_TRANSLATE_STELLA_JAVA_SYMBOL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_SYMBOL", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_GET_KWD = ((Symbol*)(internRigidSymbolWrtModule("GET-KWD", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_GET_SGT = ((Symbol*)(internRigidSymbolWrtModule("GET-SGT", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_DEFINEDp = ((Symbol*)(internRigidSymbolWrtModule("DEFINED?", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_NULLp = ((Symbol*)(internRigidSymbolWrtModule("NULL?", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_CONCATENATE = ((Symbol*)(internRigidSymbolWrtModule("CONCATENATE", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_NTH = ((Symbol*)(internRigidSymbolWrtModule("NTH", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_NTH_SETTER = ((Symbol*)(internRigidSymbolWrtModule("NTH-SETTER", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_AREF = ((Symbol*)(internRigidSymbolWrtModule("AREF", NULL, 0)));
    SYM_JAVA_TRANSLATE_STELLA_AREF_SETTER = ((Symbol*)(internRigidSymbolWrtModule("AREF-SETTER", NULL, 0)));
    SGT_JAVA_TRANSLATE_STELLA_METHOD_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-SLOT", NULL, 1)));
  }
}

void helpStartupJavaTranslate5() {
  {
    oJAVA_TRUE_STRING_WRAPPERo = wrapString("true");
    oJAVA_FALSE_STRING_WRAPPERo = wrapString("false");
    oVARARGSTATEMENTSo = NIL;
    oVARARGDECLSo = NIL;
    oJAVA_OPERATOR_TABLEo = ((KeyValueList*)(dictionary(SGT_JAVA_TRANSLATE_STELLA_KEY_VALUE_LIST, 34, SYM_JAVA_TRANSLATE_STELLA_ii, cons(wrapString("++"), NIL), SYM_JAVA_TRANSLATE_STELLA___, cons(wrapString("--"), NIL), SYM_JAVA_TRANSLATE_STELLA_i, cons(wrapString("+"), NIL), SYM_JAVA_TRANSLATE_STELLA__, cons(wrapString("-"), NIL), SYM_JAVA_TRANSLATE_STELLA_o, cons(wrapString("*"), NIL), SYM_JAVA_TRANSLATE_STELLA_s, cons(wrapString("/"), NIL), SYM_JAVA_TRANSLATE_STELLA_EQp, cons(wrapString("=="), NIL), SYM_JAVA_TRANSLATE_STELLA_g, cons(wrapString(">"), NIL), SYM_JAVA_TRANSLATE_STELLA_ge, cons(wrapString(">="), NIL), SYM_JAVA_TRANSLATE_STELLA_eg, cons(wrapString(">="), NIL), SYM_JAVA_TRANSLATE_STELLA_l, cons(wrapString("<"), NIL), SYM_JAVA_TRANSLATE_STELLA_el, cons(wrapString("<="), NIL), SYM_JAVA_TRANSLATE_STELLA_le, cons(wrapString("<="), NIL), SYM_JAVA_TRANSLATE_STELLA_AND, cons(wrapString("&&"), NIL), SYM_JAVA_TRANSLATE_STELLA_OR, cons(wrapString("||"), NIL), SYM_JAVA_TRANSLATE_STELLA_NOT, cons(wrapString("!"), NIL), SYM_JAVA_TRANSLATE_STELLA_CHOOSE, cons(wrapString("?"), cons(wrapString(":"), NIL)))));
    oJAVA_CHARACTER_SUBSTITUTION_TABLEo = javaCreateCharacterSubstitutionTable();
    oJAVA_RESERVED_WORD_TABLEo = javaCreateReservedWordTable();
    oJAVA_PRIMITIVE_ARRAY_TYPE_NAMESo = ((KeyValueList*)(dictionary(SGT_JAVA_TRANSLATE_STELLA_KEY_VALUE_LIST, 16, wrapString("byte"), wrapString("B"), wrapString("char"), wrapString("C"), wrapString("double"), wrapString("D"), wrapString("float"), wrapString("F"), wrapString("int"), wrapString("I"), wrapString("long"), wrapString("J"), wrapString("short"), wrapString("S"), wrapString("boolean"), wrapString("Z"))));
  }
}

void helpStartupJavaTranslate6() {
  {
    defineFunctionObject("JAVA-YIELD-FLOTSAM-CLASS-NAME", "(DEFUN (JAVA-YIELD-FLOTSAM-CLASS-NAME STRING) ((MOD MODULE)))", ((cpp_function_code)(&javaYieldFlotsamClassName)), NULL);
    defineFunctionObject("JAVA-YIELD-NATIVE-CLASS-NAME", "(DEFUN (JAVA-YIELD-NATIVE-CLASS-NAME STRING) ())", ((cpp_function_code)(&javaYieldNativeClassName)), NULL);
    defineFunctionObject("JAVA-YIELD-SPECIAL-VARIABLE-CLASS-NAME", "(DEFUN (JAVA-YIELD-SPECIAL-VARIABLE-CLASS-NAME STRING) ())", ((cpp_function_code)(&javaYieldSpecialVariableClassName)), NULL);
    defineFunctionObject("JAVA-YIELD-FULL-NATIVE-CLASS-NAME", "(DEFUN (JAVA-YIELD-FULL-NATIVE-CLASS-NAME STRING) ())", ((cpp_function_code)(&javaYieldFullNativeClassName)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-UNIT", "(DEFUN (JAVA-TRANSLATE-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&javaTranslateUnit)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-DEFINE-GLOBAL-VARIABLE-UNIT", "(DEFUN (JAVA-TRANSLATE-DEFINE-GLOBAL-VARIABLE-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&javaTranslateDefineGlobalVariableUnit)), NULL);
    defineFunctionObject("WRAP-METHOD-BODY-WITH-JAVA-AUXILIARY-DECLARATIONS", "(DEFUN (WRAP-METHOD-BODY-WITH-JAVA-AUXILIARY-DECLARATIONS CONS) ((METHODBODY CONS) (DECLARATIONS CONS)))", ((cpp_function_code)(&wrapMethodBodyWithJavaAuxiliaryDeclarations)), NULL);
    defineFunctionObject("JAVA-SYNCHRONIZED-METHOD?", "(DEFUN (JAVA-SYNCHRONIZED-METHOD? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&javaSynchronizedMethodP)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-METHOD-SIGNATURE", "(DEFUN (JAVA-TRANSLATE-METHOD-SIGNATURE CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&javaTranslateMethodSignature)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-DEFINE-METHOD-UNIT", "(DEFUN (JAVA-TRANSLATE-DEFINE-METHOD-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&javaTranslateDefineMethodUnit)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-DEFPRINT-UNIT", "(DEFUN (JAVA-TRANSLATE-DEFPRINT-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&javaTranslateDefprintUnit)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-LIST-OF-TREES", "(DEFUN (JAVA-TRANSLATE-LIST-OF-TREES CONS) ((TREES CONS)))", ((cpp_function_code)(&javaTranslateListOfTrees)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-A-TREE", "(DEFUN (JAVA-TRANSLATE-A-TREE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&javaTranslateATree)), NULL);
    defineFunctionObject("JAVA-LOOKUP-OPERATOR-TABLE", "(DEFUN (JAVA-LOOKUP-OPERATOR-TABLE CONS) ((OPERATOR SYMBOL)))", ((cpp_function_code)(&javaLookupOperatorTable)), NULL);
    defineFunctionObject("JAVA-CREATE-CHARACTER-SUBSTITUTION-TABLE", "(DEFUN (JAVA-CREATE-CHARACTER-SUBSTITUTION-TABLE STRING) ())", ((cpp_function_code)(&javaCreateCharacterSubstitutionTable)), NULL);
    defineFunctionObject("JAVA-SUBSTITUTE-FORBIDDEN-CHARACTERS", "(DEFUN (JAVA-SUBSTITUTE-FORBIDDEN-CHARACTERS STRING) ((NAME STRING) (CASECONVENTION KEYWORD)))", ((cpp_function_code)(&javaSubstituteForbiddenCharacters)), NULL);
    defineFunctionObject("JAVA-CHANGE-CASE", "(DEFUN (JAVA-CHANGE-CASE STRING) ((SYMBOL GENERALIZED-SYMBOL) (CASECONVENTION KEYWORD)))", ((cpp_function_code)(&javaChangeCase)), NULL);
    defineFunctionObject("JAVA-LITERAL?", "(DEFUN (JAVA-LITERAL? BOOLEAN) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&javaLiteralP)), NULL);
    defineFunctionObject("JAVA-NATIVE-LITERAL-WRAPPER-NAMES", "(DEFUN (JAVA-NATIVE-LITERAL-WRAPPER-NAMES STRING-WRAPPER STRING-WRAPPER) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&javaNativeLiteralWrapperNames)), NULL);
    defineFunctionObject("JAVA-SPECIAL-SETTER-NAME", "(DEFUN (JAVA-SPECIAL-SETTER-NAME STRING-WRAPPER) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&javaSpecialSetterName)), NULL);
    defineFunctionObject("JAVA-YIELD-FLOTSAM-TYPE-NAME", "(DEFUN (JAVA-YIELD-FLOTSAM-TYPE-NAME STRING) ((FLOTSAM-CLASS-NAME STRING)))", ((cpp_function_code)(&javaYieldFlotsamTypeName)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-SYMBOL-CONSTANT-NAME", "(DEFUN (JAVA-TRANSLATE-SYMBOL-CONSTANT-NAME STRING-WRAPPER) ((SYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&javaTranslateSymbolConstantName)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-SYMBOL-CONSTANT-ID", "(DEFUN (JAVA-TRANSLATE-SYMBOL-CONSTANT-ID STRING-WRAPPER) ((SYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&javaTranslateSymbolConstantId)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-SYMBOL-NAME", "(DEFUN (JAVA-TRANSLATE-SYMBOL-NAME STRING-WRAPPER) ((SYMBOL SYMBOL)))", ((cpp_function_code)(&javaTranslateSymbolName)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-SYMBOL-ID", "(DEFUN (JAVA-TRANSLATE-SYMBOL-ID STRING-WRAPPER) ((SYMBOL SYMBOL)))", ((cpp_function_code)(&javaTranslateSymbolId)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-SURROGATE-NAME", "(DEFUN (JAVA-TRANSLATE-SURROGATE-NAME STRING-WRAPPER) ((SURROGATE SURROGATE)))", ((cpp_function_code)(&javaTranslateSurrogateName)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-SURROGATE-ID", "(DEFUN (JAVA-TRANSLATE-SURROGATE-ID STRING-WRAPPER) ((SURROGATE SURROGATE)))", ((cpp_function_code)(&javaTranslateSurrogateId)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-KEYWORD-NAME", "(DEFUN (JAVA-TRANSLATE-KEYWORD-NAME STRING-WRAPPER) ((KEYWORD KEYWORD)))", ((cpp_function_code)(&javaTranslateKeywordName)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-KEYWORD-ID", "(DEFUN (JAVA-TRANSLATE-KEYWORD-ID STRING-WRAPPER) ((KEYWORD KEYWORD)))", ((cpp_function_code)(&javaTranslateKeywordId)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-CLASS-NAMESTRING", "(DEFUN (JAVA-TRANSLATE-CLASS-NAMESTRING STRING-WRAPPER) ((NAMESTRING STRING-WRAPPER)))", ((cpp_function_code)(&javaTranslateClassNamestring)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-CLASS-NAME", "(DEFUN (JAVA-TRANSLATE-CLASS-NAME STRING-WRAPPER) ((NAMESYMBOL GENERALIZED-SYMBOL)))", ((cpp_function_code)(&javaTranslateClassName)), NULL);
    defineFunctionObject("IN-CURRENT-JAVA-PACKAGE?", "(DEFUN (IN-CURRENT-JAVA-PACKAGE? BOOLEAN) ((MODULE MODULE)))", ((cpp_function_code)(&inCurrentJavaPackageP)), NULL);
    defineFunctionObject("INHERITED-CLASS-NAME-CONFLICTS?", "(DEFUN (INHERITED-CLASS-NAME-CONFLICTS? BOOLEAN) ((STELLA-CLASS-NAME STRING)))", ((cpp_function_code)(&inheritedClassNameConflictsP)), NULL);
    defineFunctionObject("CLASS-NAME-CONFLICTS-WITH-SLOT-NAME?", "(DEFUN (CLASS-NAME-CONFLICTS-WITH-SLOT-NAME? BOOLEAN) ((DEFINING-CLASS CLASS) (JAVA-CLASS-NAME STRING)))", ((cpp_function_code)(&classNameConflictsWithSlotNameP)), NULL);
    defineFunctionObject("OMIT-JAVA-PACKAGE-PREFIX?", "(DEFUN (OMIT-JAVA-PACKAGE-PREFIX? BOOLEAN) ((MODULE MODULE) (STELLA-CLASS-NAME STRING)))", ((cpp_function_code)(&omitJavaPackagePrefixP)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-TYPE-SPEC", "(DEFUN (JAVA-TRANSLATE-TYPE-SPEC STRING-WRAPPER) ((TYPE-SPEC TYPE-SPEC)))", ((cpp_function_code)(&javaTranslateTypeSpec)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-TYPE-SPEC-FOR-FUNCTION", "(DEFUN (JAVA-TRANSLATE-TYPE-SPEC-FOR-FUNCTION STRING-WRAPPER) ((TYPE-SPEC TYPE-SPEC)))", ((cpp_function_code)(&javaTranslateTypeSpecForFunction)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-TYPE-SPEC-HELPER", "(DEFUN (JAVA-TRANSLATE-TYPE-SPEC-HELPER STRING-WRAPPER) ((TYPE-SPEC TYPE-SPEC) (FUNCTION? BOOLEAN)))", ((cpp_function_code)(&javaTranslateTypeSpecHelper)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-ARRAY-TYPE", "(DEFUN (JAVA-TRANSLATE-ARRAY-TYPE STRING-WRAPPER) ((ARRAYTYPE PARAMETRIC-TYPE-SPECIFIER)))", ((cpp_function_code)(&javaTranslateArrayType)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-ARRAY-OF-TYPE-SPEC", "(DEFUN (JAVA-TRANSLATE-ARRAY-OF-TYPE-SPEC STRING-WRAPPER) ((TYPESPEC TYPE-SPEC) (FULLYQUALIFIED? BOOLEAN)))", ((cpp_function_code)(&javaTranslateArrayOfTypeSpec)), NULL);
    defineFunctionObject("JAVA-YIELD-RENAMED-RESERVED-WORD", "(DEFUN (JAVA-YIELD-RENAMED-RESERVED-WORD STRING-WRAPPER) ((WORD SYMBOL)))", ((cpp_function_code)(&javaYieldRenamedReservedWord)), NULL);
    defineFunctionObject("JAVA-CREATE-RESERVED-WORD-TABLE", "(DEFUN (JAVA-CREATE-RESERVED-WORD-TABLE STRING-HASH-TABLE) ())", ((cpp_function_code)(&javaCreateReservedWordTable)), NULL);
    defineFunctionObject("JAVA-LOOKUP-RESERVED-WORD-TABLE", "(DEFUN (JAVA-LOOKUP-RESERVED-WORD-TABLE STRING) ((WORD STRING)))", ((cpp_function_code)(&javaLookupReservedWordTable)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-NAMESTRING", "(DEFUN (JAVA-TRANSLATE-NAMESTRING STRING) ((NAMESTRING STRING)))", ((cpp_function_code)(&javaTranslateNamestring)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-NAME", "(DEFUN (JAVA-TRANSLATE-NAME STRING-WRAPPER) ((NAMESYMBOL SYMBOL)))", ((cpp_function_code)(&javaTranslateName)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-SPECIAL-TREE", "(DEFUN (JAVA-TRANSLATE-SPECIAL-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateSpecialTree)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-VERBATIM-TREE", "(DEFUN (JAVA-TRANSLATE-VERBATIM-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateVerbatimTree)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-INLINE-CALL-TREE", "(DEFUN (JAVA-TRANSLATE-INLINE-CALL-TREE OBJECT) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateInlineCallTree)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-UNWIND-PROTECT", "(DEFUN (JAVA-TRANSLATE-UNWIND-PROTECT CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateUnwindProtect)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-SIGNAL", "(DEFUN (JAVA-TRANSLATE-SIGNAL CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateSignal)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-HANDLER-CASE", "(DEFUN (JAVA-TRANSLATE-HANDLER-CASE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateHandlerCase)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-HANDLE-EXCEPTION", "(DEFUN (JAVA-TRANSLATE-HANDLE-EXCEPTION CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateHandleException)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-VOID-SYS", "(DEFUN (JAVA-TRANSLATE-VOID-SYS CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateVoidSys)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-TYPED-SYS", "(DEFUN (JAVA-TRANSLATE-TYPED-SYS CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateTypedSys)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-BAD-SYS", "(DEFUN (JAVA-TRANSLATE-BAD-SYS OBJECT) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateBadSys)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-SETQ-TREE", "(DEFUN (JAVA-TRANSLATE-SETQ-TREE OBJECT) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateSetqTree)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-SYS-SET-DEFAULT", "(DEFUN (JAVA-TRANSLATE-SYS-SET-DEFAULT OBJECT) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateSysSetDefault)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-SYS-SLOT-VALUE-SETTER", "(DEFUN (JAVA-TRANSLATE-SYS-SLOT-VALUE-SETTER CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateSysSlotValueSetter)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-SYS-SLOT-VALUE", "(DEFUN (JAVA-TRANSLATE-SYS-SLOT-VALUE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateSysSlotValue)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-PROGN", "(DEFUN (JAVA-TRANSLATE-PROGN CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateProgn)), NULL);
  }
}

void helpStartupJavaTranslate7() {
  {
    defineFunctionObject("JAVA-TRANSLATE-WITH-PROCESS-LOCK", "(DEFUN (JAVA-TRANSLATE-WITH-PROCESS-LOCK CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateWithProcessLock)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-LOOP", "(DEFUN (JAVA-TRANSLATE-LOOP CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateLoop)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-FOREACH-TREE", "(DEFUN (JAVA-TRANSLATE-FOREACH-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateForeachTree)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-LET-TREE", "(DEFUN (JAVA-TRANSLATE-LET-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateLetTree)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-CAST", "(DEFUN (JAVA-TRANSLATE-CAST CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateCast)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-RETURN-TREE", "(DEFUN (JAVA-TRANSLATE-RETURN-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateReturnTree)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-BREAK", "(DEFUN (JAVA-TRANSLATE-BREAK CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateBreak)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-CONTINUE", "(DEFUN (JAVA-TRANSLATE-CONTINUE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateContinue)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-IF-TREE", "(DEFUN (JAVA-TRANSLATE-IF-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateIfTree)), NULL);
    defineFunctionObject("JAVA-SYMBOL-CASE?", "(DEFUN (JAVA-SYMBOL-CASE? BOOLEAN) ((KEYFORM OBJECT)))", ((cpp_function_code)(&javaSymbolCaseP)), NULL);
    defineFunctionObject("JAVA-YIELD-SYMBOL-ID-FORM", "(DEFUN (JAVA-YIELD-SYMBOL-ID-FORM CONS) ((SYMBOLID INTEGER)))", ((cpp_function_code)(&javaYieldSymbolIdForm)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-CONDITION", "(DEFUN (JAVA-TRANSLATE-CONDITION CONS) ((CONDITION CONS) (SYMBOLCASEP BOOLEAN)))", ((cpp_function_code)(&javaTranslateCondition)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-CASE-TREE", "(DEFUN (JAVA-TRANSLATE-CASE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateCaseTree)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-COND-TREE", "(DEFUN (JAVA-TRANSLATE-COND-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateCondTree)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-WHILE", "(DEFUN (JAVA-TRANSLATE-WHILE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateWhile)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-CHOOSE-TREE", "(DEFUN (JAVA-TRANSLATE-CHOOSE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateChooseTree)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-WHEN-TREE", "(DEFUN (JAVA-TRANSLATE-WHEN-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateWhenTree)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-UNLESS-TREE", "(DEFUN (JAVA-TRANSLATE-UNLESS-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateUnlessTree)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-MAKE-TREE", "(DEFUN (JAVA-TRANSLATE-MAKE-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateMakeTree)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-SYS-NEW", "(DEFUN (JAVA-TRANSLATE-SYS-NEW CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateSysNew)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-NEW-ARRAY", "(DEFUN (JAVA-TRANSLATE-NEW-ARRAY CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateNewArray)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-MV-SETQ", "(DEFUN (JAVA-TRANSLATE-MV-SETQ CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateMvSetq)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-MV-FUNCTION-CALL", "(DEFUN (JAVA-TRANSLATE-MV-FUNCTION-CALL CONS) ((FUNCTIONCALL CONS) (MVVECTORNAME SYMBOL)))", ((cpp_function_code)(&javaTranslateMvFunctionCall)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-CODE-SIGNATURE", "(DEFUN (JAVA-TRANSLATE-CODE-SIGNATURE CONS) ((SIGNATURE CONS)))", ((cpp_function_code)(&javaTranslateCodeSignature)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-WITH-NATIVE-WRAPPER", "(DEFUN (JAVA-TRANSLATE-WITH-NATIVE-WRAPPER CONS) ((TREE OBJECT) (TYPE TYPE-SPEC)))", ((cpp_function_code)(&javaTranslateWithNativeWrapper)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-ACTUAL-PARAMETERS-WITH-NATIVE-WRAPPERS", "(DEFUN (JAVA-TRANSLATE-ACTUAL-PARAMETERS-WITH-NATIVE-WRAPPERS CONS) ((TREES CONS) (PARAMETERTYPES (CONS OF TYPE-SPEC))))", ((cpp_function_code)(&javaTranslateActualParametersWithNativeWrappers)), NULL);
    defineFunctionObject("JAVA-WRAP-WITH-NATIVE-VALUE-EXTRACTION", "(DEFUN (JAVA-WRAP-WITH-NATIVE-VALUE-EXTRACTION CONS) ((TREE CONS) (PRIMARYRETURNTYPE TYPE-SPEC)))", ((cpp_function_code)(&javaWrapWithNativeValueExtraction)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-OBJECT-TO-RETURN-TYPE", "(DEFUN (JAVA-TRANSLATE-OBJECT-TO-RETURN-TYPE CONS) ((TREE CONS) (RETURNTYPE TYPE-SPEC)))", ((cpp_function_code)(&javaTranslateObjectToReturnType)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-CALL-FUNCTION-CODE", "(DEFUN (JAVA-TRANSLATE-CALL-FUNCTION-CODE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateCallFunctionCode)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-CALL-METHOD-CODE", "(DEFUN (JAVA-TRANSLATE-CALL-METHOD-CODE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateCallMethodCode)), NULL);
    defineFunctionObject("JAVA-PACKAGE-PREFIX", "(DEFUN (JAVA-PACKAGE-PREFIX STRING) ((MODULE MODULE) (SEPARATOR STRING)))", ((cpp_function_code)(&javaPackagePrefix)), NULL);
    defineFunctionObject("JAVA-YIELD-FULLY-QUALIFIED-TYPE-NAME", "(DEFUN (JAVA-YIELD-FULLY-QUALIFIED-TYPE-NAME STRING-WRAPPER) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&javaYieldFullyQualifiedTypeName)), NULL);
    defineFunctionObject("JAVA-YIELD-TRANSLATED-CLASS-AND-FUNCTION-NAMES", "(DEFUN (JAVA-YIELD-TRANSLATED-CLASS-AND-FUNCTION-NAMES STRING-WRAPPER STRING-WRAPPER) ((F FUNCTION)))", ((cpp_function_code)(&javaYieldTranslatedClassAndFunctionNames)), NULL);
    defineFunctionObject("JAVA-YIELD-TRANSLATED-CLASS-AND-METHOD-NAMES", "(DEFUN (JAVA-YIELD-TRANSLATED-CLASS-AND-METHOD-NAMES STRING STRING) ((OWNER TYPE-SPEC) (F FUNCTION)))", ((cpp_function_code)(&javaYieldTranslatedClassAndMethodNames)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-CLASS-OBJECT-LOOKUP", "(DEFUN (JAVA-TRANSLATE-CLASS-OBJECT-LOOKUP CONS) ((CLASSNAME STRING)))", ((cpp_function_code)(&javaTranslateClassObjectLookup)), NULL);
    defineFunctionObject("JAVA-YIELD-CLASS-OBJECT-ARRAY-EXPRESSION", "(DEFUN (JAVA-YIELD-CLASS-OBJECT-ARRAY-EXPRESSION CONS) ((TYPESPEC TYPE-SPEC) (NDIMENSIONS INTEGER)))", ((cpp_function_code)(&javaYieldClassObjectArrayExpression)), NULL);
    defineFunctionObject("JAVA-YIELD-CLASS-OBJECT-EXPRESSION", "(DEFUN (JAVA-YIELD-CLASS-OBJECT-EXPRESSION CONS) ((TYPESPEC TYPE-SPEC)))", ((cpp_function_code)(&javaYieldClassObjectExpression)), NULL);
    defineFunctionObject("YIELD-CLASS-OBJECT-LOOKUP-NAME-FOR-NATIVE-TYPE", "(DEFUN (YIELD-CLASS-OBJECT-LOOKUP-NAME-FOR-NATIVE-TYPE STRING) ((NATIVETYPE STRING)))", ((cpp_function_code)(&yieldClassObjectLookupNameForNativeType)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-PARAM-TYPE-SPECIFICATIONS", "(DEFUN (JAVA-TRANSLATE-PARAM-TYPE-SPECIFICATIONS CONS) ((FN METHOD-SLOT) (OWNER TYPE-SPEC)))", ((cpp_function_code)(&javaTranslateParamTypeSpecifications)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-THE-CODE", "(DEFUN (JAVA-TRANSLATE-THE-CODE OBJECT) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateTheCode)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-FUNCTION-NAME", "(DEFUN (JAVA-TRANSLATE-FUNCTION-NAME STRING-WRAPPER) ((FUNCTION METHOD-SLOT)))", ((cpp_function_code)(&javaTranslateFunctionName)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-IGNORE-TREE", "(DEFUN (JAVA-TRANSLATE-IGNORE-TREE OBJECT) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateIgnoreTree)), NULL);
    defineFunctionObject("JAVA-STREAM-IS-STANDARD-OUTPUT?", "(DEFUN (JAVA-STREAM-IS-STANDARD-OUTPUT? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&javaStreamIsStandardOutputP)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-PRINT-STREAM", "(DEFUN (JAVA-TRANSLATE-PRINT-STREAM CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslatePrintStream)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-PRINT-NATIVE-STREAM", "(DEFUN (JAVA-TRANSLATE-PRINT-NATIVE-STREAM CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslatePrintNativeStream)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-NULL", "(DEFUN (JAVA-TRANSLATE-NULL CONS) ())", ((cpp_function_code)(&javaTranslateNull)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-EOL", "(DEFUN (JAVA-TRANSLATE-EOL CONS) ())", ((cpp_function_code)(&javaTranslateEol)), NULL);
    defineMethodObject("(DEFMETHOD (JAVA-TRANSLATE-ATOMIC-TREE CONS) ((TREE OBJECT)))", wrapMethodCode(((cpp_method_code)(&Object::javaTranslateAtomicTree))), NULL);
    defineFunctionObject("JAVA-PREPEND-GLOBAL-CLASS-NAME", "(DEFUN (JAVA-PREPEND-GLOBAL-CLASS-NAME STRING) ((NAMESTRING STRING) (MODULE MODULE)))", ((cpp_function_code)(&javaPrependGlobalClassName)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-GLOBAL-NAME", "(DEFUN (JAVA-TRANSLATE-GLOBAL-NAME STRING-WRAPPER) ((NAMESYMBOL SYMBOL) (DEFINITION? BOOLEAN)))", ((cpp_function_code)(&javaTranslateGlobalName)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-GENERAL-SYMBOL", "(DEFUN (JAVA-TRANSLATE-GENERAL-SYMBOL CONS) ((TREE SYMBOL)))", ((cpp_function_code)(&javaTranslateGeneralSymbol)), NULL);
    defineMethodObject("(DEFMETHOD (JAVA-TRANSLATE-ATOMIC-TREE CONS) ((TREE SYMBOL)))", wrapMethodCode(((cpp_method_code)(&Symbol::javaTranslateAtomicTree))), NULL);
    defineFunctionObject("JAVA-TRANSLATE-METHOD-PARAMETER", "(DEFUN (JAVA-TRANSLATE-METHOD-PARAMETER OBJECT) ((NAME SYMBOL) (TYPE TYPE-SPEC) (METHOD METHOD-SLOT)))", ((cpp_function_code)(&javaTranslateMethodParameter)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-RETURN-PARAMETER", "(DEFUN (JAVA-TRANSLATE-RETURN-PARAMETER CONS) ())", ((cpp_function_code)(&javaTranslateReturnParameter)), NULL);
    defineFunctionObject("JAVA-TRANSLATE-METHOD-PARAMETERS", "(DEFUN (JAVA-TRANSLATE-METHOD-PARAMETERS CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&javaTranslateMethodParameters)), NULL);
    defineFunctionObject("ZERO-ARGUMENT-FUNCTION?", "(DEFUN (ZERO-ARGUMENT-FUNCTION? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&zeroArgumentFunctionP)), NULL);
    defineFunctionObject("JAVA-METHOD-OBJECT-DEFINED-ON-NATIVE-TYPE?", "(DEFUN (JAVA-METHOD-OBJECT-DEFINED-ON-NATIVE-TYPE? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&javaMethodObjectDefinedOnNativeTypeP)), NULL);
    defineFunctionObject("JAVA-METHOD-OBJECT-IS-OVERLOADED-FUNCTION?", "(DEFUN (JAVA-METHOD-OBJECT-IS-OVERLOADED-FUNCTION? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&javaMethodObjectIsOverloadedFunctionP)), NULL);
    defineFunctionObject("JAVA-METHOD-OBJECT-IS-FUNCTION?", "(DEFUN (JAVA-METHOD-OBJECT-IS-FUNCTION? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&javaMethodObjectIsFunctionP)), NULL);
    defineFunctionObject("JAVA-FUNCTION-IN-DIFFERENT-MODULE?", "(DEFUN (JAVA-FUNCTION-IN-DIFFERENT-MODULE? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&javaFunctionInDifferentModuleP)), NULL);
  }
}

void startupJavaTranslate() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupJavaTranslate1();
      helpStartupJavaTranslate2();
      helpStartupJavaTranslate3();
      helpStartupJavaTranslate4();
      SYM_JAVA_TRANSLATE_STELLA_JAVA_UNARY_OP = ((Symbol*)(internRigidSymbolWrtModule("JAVA_UNARY_OP", NULL, 0)));
      SYM_JAVA_TRANSLATE_STELLA_JAVA_BINARY_OP = ((Symbol*)(internRigidSymbolWrtModule("JAVA_BINARY_OP", NULL, 0)));
      SYM_JAVA_TRANSLATE_STELLA_JAVA_TERNARY_OP = ((Symbol*)(internRigidSymbolWrtModule("JAVA_TERNARY_OP", NULL, 0)));
      SGT_JAVA_TRANSLATE_STELLA_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("ARRAY", NULL, 1)));
      SGT_JAVA_TRANSLATE_STELLA_NATIVE_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("NATIVE-VECTOR", NULL, 1)));
      SYM_JAVA_TRANSLATE_STELLA_STARTUP_JAVA_TRANSLATE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-JAVA-TRANSLATE", NULL, 0)));
    }
    if (currentStartupTimePhaseP(4)) {
      helpStartupJavaTranslate5();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupJavaTranslate6();
      helpStartupJavaTranslate7();
      defineFunctionObject("JAVA-CREATE-OVERLOADED-FUNCTION-NAME", "(DEFUN (JAVA-CREATE-OVERLOADED-FUNCTION-NAME SYMBOL) ((FUNCTIONNAME SYMBOL) (CLASSTYPE TYPE)))", ((cpp_function_code)(&javaCreateOverloadedFunctionName)), NULL);
      defineMethodObject("(DEFMETHOD (JAVA-TRANSLATE-METHOD-NAME STRING-WRAPPER) ((METHOD METHOD-SLOT)))", wrapMethodCode(((cpp_method_code)(&MethodSlot::javaTranslateMethodName))), NULL);
      defineFunctionObject("JAVA-DELETE-QUOTED-NULL-STATEMENTS", "(DEFUN (JAVA-DELETE-QUOTED-NULL-STATEMENTS CONS) ((TREES CONS)))", ((cpp_function_code)(&javaDeleteQuotedNullStatements)), NULL);
      defineFunctionObject("JAVA-WRAP-METHOD-BODY-WITH-VARARG-DECLARATIONS", "(DEFUN (JAVA-WRAP-METHOD-BODY-WITH-VARARG-DECLARATIONS CONS) ((METHODBODY CONS)))", ((cpp_function_code)(&javaWrapMethodBodyWithVarargDeclarations)), NULL);
      defineFunctionObject("JAVA-WRAP-METHOD-BODY-WITH-VARARG-VALUE-SETUP", "(DEFUN (JAVA-WRAP-METHOD-BODY-WITH-VARARG-VALUE-SETUP CONS) ((METHODBODY CONS)))", ((cpp_function_code)(&javaWrapMethodBodyWithVarargValueSetup)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-VARIABLE-LENGTH-ARG-NAME", "(DEFUN (JAVA-TRANSLATE-VARIABLE-LENGTH-ARG-NAME STRING-WRAPPER) ((NAMESYMBOL SYMBOL) (PARAMETERNUMBER INTEGER)))", ((cpp_function_code)(&javaTranslateVariableLengthArgName)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-VARIABLE-LENGTH-ACTUALS", "(DEFUN (JAVA-TRANSLATE-VARIABLE-LENGTH-ACTUALS CONS) ((ACTUALS CONS) (UNUSED-METHOD METHOD-SLOT)))", ((cpp_function_code)(&javaTranslateVariableLengthActuals)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-ACTUAL-PARAMETERS", "(DEFUN (JAVA-TRANSLATE-ACTUAL-PARAMETERS CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateActualParameters)), NULL);
      defineFunctionObject("JAVA-YIELD-CLASS-NAME-FOR-FUNCTION", "(DEFUN (JAVA-YIELD-CLASS-NAME-FOR-FUNCTION STRING) ((FUNCTION METHOD-SLOT)))", ((cpp_function_code)(&javaYieldClassNameForFunction)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-FUNCTION-CALL", "(DEFUN (JAVA-TRANSLATE-FUNCTION-CALL CONS) ((TREE CONS) (METHOD METHOD-SLOT)))", ((cpp_function_code)(&javaTranslateFunctionCall)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-DEFINED-OR-NULL", "(DEFUN (JAVA-TRANSLATE-DEFINED-OR-NULL CONS) ((CLASSTYPE TYPE) (OBJECT OBJECT) (NULL? BOOLEAN)))", ((cpp_function_code)(&javaTranslateDefinedOrNull)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-METHOD-CALL", "(DEFUN (JAVA-TRANSLATE-METHOD-CALL CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateMethodCall)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-SUPER-METHOD-CALL", "(DEFUN (JAVA-TRANSLATE-SUPER-METHOD-CALL OBJECT) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateSuperMethodCall)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-NORMAL-METHOD-CALL", "(DEFUN (JAVA-TRANSLATE-NORMAL-METHOD-CALL CONS) ((METHODNAME SYMBOL) (CLASSTYPE TYPE) (ALLARGS CONS)))", ((cpp_function_code)(&javaTranslateNormalMethodCall)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-OPERATOR-TREE", "(DEFUN (JAVA-TRANSLATE-OPERATOR-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&javaTranslateOperatorTree)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-OPERATOR-CALL", "(DEFUN (JAVA-TRANSLATE-OPERATOR-CALL CONS) ((OPERATORNAMES CONS) (ARGUMENTS CONS) (ARITY INTEGER)))", ((cpp_function_code)(&javaTranslateOperatorCall)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-AREF-METHOD-CALL", "(DEFUN (JAVA-TRANSLATE-AREF-METHOD-CALL CONS) ((OPERATOR SYMBOL) (OWNER TYPE) (ARGUMENTS CONS)))", ((cpp_function_code)(&javaTranslateArefMethodCall)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-NTH-METHOD-CALL", "(DEFUN (JAVA-TRANSLATE-NTH-METHOD-CALL CONS) ((OPERATOR SYMBOL) (OWNER TYPE) (ARGUMENTS CONS)))", ((cpp_function_code)(&javaTranslateNthMethodCall)), NULL);
      defineFunctionObject("STARTUP-JAVA-TRANSLATE", "(DEFUN STARTUP-JAVA-TRANSLATE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupJavaTranslate)), NULL);
      { MethodSlot* function = lookupFunction(SYM_JAVA_TRANSLATE_STELLA_STARTUP_JAVA_TRANSLATE);

        setDynamicSlotValue(function->dynamicSlots, SYM_JAVA_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupJavaTranslate"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *JAVA-TRUE-STRING-WRAPPER* STRING-WRAPPER (WRAP-LITERAL \"true\") :PUBLIC? FALSE :DOCUMENTATION \"Wrapped true string, used to reduce consing.\")", &oJAVA_TRUE_STRING_WRAPPERo);
      defineGlobalVariableObject("(DEFGLOBAL *JAVA-FALSE-STRING-WRAPPER* STRING-WRAPPER (WRAP-LITERAL \"false\") :PUBLIC? FALSE :DOCUMENTATION \"Wrapped false string, used to reduce consing.\")", &oJAVA_FALSE_STRING_WRAPPERo);
      defineGlobalVariableObject("(DEFSPECIAL *VARARGSTATEMENTS* (CONS OF CONS) NIL :DOCUMENTATION \"A list of new vectors generated for variable-length argument \n             lists\")", &oVARARGSTATEMENTSo);
      defineGlobalVariableObject("(DEFSPECIAL *VARARGDECLS* (CONS OF CONS) NIL :DOCUMENTATION \"A list of vector-pushes generated for variable-length argument \n             lists\")", &oVARARGDECLSo);
      defineGlobalVariableObject("(DEFSPECIAL *CURRENTVARARGINDEX* INTEGER 1 :DOCUMENTATION \"The current index of the variable length arguments\")", &oCURRENTVARARGINDEXo);
      defineGlobalVariableObject("(DEFGLOBAL *JAVA-OPERATOR-TABLE* KEY-VALUE-LIST (DICTIONARY @KEY-VALUE-LIST (QUOTE ++) (CONS (WRAP-LITERAL \"++\") NIL) (QUOTE --) (CONS (WRAP-LITERAL \"--\") NIL) (QUOTE +) (CONS (WRAP-LITERAL \"+\") NIL) (QUOTE -) (CONS (WRAP-LITERAL \"-\") NIL) (QUOTE *) (CONS (WRAP-LITERAL \"*\") NIL) (QUOTE /) (CONS (WRAP-LITERAL \"/\") NIL) (QUOTE EQ?) (CONS (WRAP-LITERAL \"==\") NIL) (QUOTE >) (CONS (WRAP-LITERAL \">\") NIL) (QUOTE >=) (CONS (WRAP-LITERAL \">=\") NIL) (QUOTE =>) (CONS (WRAP-LITERAL \">=\") NIL) (QUOTE <) (CONS (WRAP-LITERAL \"<\") NIL) (QUOTE =<) (CONS (WRAP-LITERAL \"<=\") NIL) (QUOTE <=) (CONS (WRAP-LITERAL \"<=\") NIL) (QUOTE AND) (CONS (WRAP-LITERAL \"&&\") NIL) (QUOTE OR) (CONS (WRAP-LITERAL \"||\") NIL) (QUOTE NOT) (CONS (WRAP-LITERAL \"!\") NIL) (QUOTE CHOOSE) (CONS (WRAP-LITERAL \"?\") (CONS (WRAP-LITERAL \":\") NIL))) :DOCUMENTATION \"Mapping from STELLA operators to Java operators\")", &oJAVA_OPERATOR_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *JAVA-CHARACTER-SUBSTITUTION-TABLE* STRING (JAVA-CREATE-CHARACTER-SUBSTITUTION-TABLE))", &oJAVA_CHARACTER_SUBSTITUTION_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *JAVA-RESERVED-WORD-TABLE* (STRING-HASH-TABLE OF STRING STRING-WRAPPER) (JAVA-CREATE-RESERVED-WORD-TABLE))", &oJAVA_RESERVED_WORD_TABLEo);
      defineGlobalVariableObject("(DEFSPECIAL *JAVA-LOOP-NAME* SYMBOL NULL)", &oJAVA_LOOP_NAMEo);
      defineGlobalVariableObject("(DEFSPECIAL *JAVA-LOOP-NAME-USED?* BOOLEAN FALSE)", &oJAVA_LOOP_NAME_USEDpo);
      defineGlobalVariableObject("(DEFGLOBAL *JAVA-PRIMITIVE-ARRAY-TYPE-NAMES* KEY-VALUE-LIST (DICTIONARY @KEY-VALUE-LIST \"byte\" \"B\" \"char\" \"C\" \"double\" \"D\" \"float\" \"F\" \"int\" \"I\" \"long\" \"J\" \"short\" \"S\" \"boolean\" \"Z\"))", &oJAVA_PRIMITIVE_ARRAY_TYPE_NAMESo);
    }
  }
}

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_FLOTSAM_CLASS = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_GLOBAL_VARIABLE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_CLASS = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_TYPE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_METHOD = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_MACRO = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_PRINT_METHOD = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_STARTUP_TIME_PROGN = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_VERBATIM = NULL;

Keyword* KWD_JAVA_TRANSLATE_UNBOUND_SPECIAL_VARIABLE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_GLOBAL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_TYPE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_MAKE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_BLOCK = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_THIS = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_DOCUMENTATION = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_COMMENT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SELF = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_CONS = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SPECIAL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_UNWIND_PROTECT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_SIGNAL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_HANDLER_CASE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_HANDLE_EXCEPTION = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_VOID_SYS = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_TYPED_SYS = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_BAD_SYS = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SETQ = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_SET_DEFAULT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_SLOT_VALUE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_SLOT_VALUE_SETTER = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_METHOD = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_FUNCTION = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_SUPER_METHOD = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_PROGN = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_WITH_PROCESS_LOCK = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_LOOP = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_FOREACH = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_LET = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_CAST = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SAFE_CAST = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_RETURN = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_BREAK = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_CONTINUE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_WHILE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_IF = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_CHOOSE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_WHEN = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_UNLESS = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_AND = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_OR = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_NOT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_EQp = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_g = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_ge = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_l = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_le = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_ii = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA___ = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_COND = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_CASE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_MAKE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_NEW = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_MV_SETQ = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_FUNCTION_CODE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_METHOD_CODE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_INLINE_CALL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_THE_CODE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_INLINE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_IGNORE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_PRINT_STREAM = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_PRINT_NATIVE_STREAM = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_KEY_VALUE_LIST = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_i = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA__ = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_o = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_s = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_eg = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_el = NULL;

Keyword* KWD_JAVA_TRANSLATE_UPPERCASE = NULL;

Keyword* KWD_JAVA_TRANSLATE_LOWERCASE = NULL;

Keyword* KWD_JAVA_TRANSLATE_CAPITALIZED = NULL;

Keyword* KWD_JAVA_TRANSLATE_CLEVER = NULL;

Keyword* KWD_JAVA_TRANSLATE_YES = NULL;

Keyword* KWD_JAVA_TRANSLATE_NO = NULL;

Keyword* KWD_JAVA_TRANSLATE_PRESERVE = NULL;

Keyword* KWD_JAVA_TRANSLATE_UPCASE = NULL;

Keyword* KWD_JAVA_TRANSLATE_TITLECASEX = NULL;

Keyword* KWD_JAVA_TRANSLATE_TITLECASE = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_LITERAL = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_STRING = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_MUTABLE_STRING = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_CODE = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_BOOLEAN = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_INTEGER = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_SHORT_INTEGER = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_UNSIGNED_SHORT_INTEGER = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_BYTE = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_OCTET = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_THIRY_TWO_BIT_VECTOR = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_FLOAT = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_DOUBLE = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_CHARACTER = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_LONG_INTEGER = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_SINGLE_FLOAT = NULL;

Keyword* KWD_JAVA_TRANSLATE_CAPITALIZE = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_MODULE = NULL;

Keyword* KWD_JAVA_TRANSLATE_MINIMIZE_JAVA_PREFIXES = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_CLASS_JAVA_NATIVE_TYPE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_ANY_VALUE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_OBJECT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_ABSTRACT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_BOOLEAN = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_BYTE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_CATCH = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_CHAR = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_CONST = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_DEFAULT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_DO = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_DOUBLE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_ELSE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_EXTENDS = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_FINAL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_FINALLY = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_FLOAT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_FOR = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_GOTO = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_IMPLEMENTS = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_IMPORT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_INSTANCEOF = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_INT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_INTERFACE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_LONG = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_NATIVE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_NEW = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_PACKAGE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_PRIVATE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_PROTECTED = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_PUBLIC = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SHORT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_STATIC = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SUPER = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SWITCH = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYNCHRONIZED = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_THROW = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_THROWS = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_TRANSIENT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_TRY = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_VOID = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_VOLATILE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_ASSERT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_ENUM = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CALL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_UNWIND_PROTECT = NULL;

Keyword* KWD_JAVA_TRANSLATE_JAVA = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_SIGNAL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_FILL_IN_STACK_TRACE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_HANDLER_CASE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_CATCH = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION_CALL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_ASSIGN = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_VARIABLE_TYPE_SPECIFIER = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_SLOT_VALUE_SETTER = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_SLOT_VALUE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_PROGN = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_WITH_PROCESS_LOCK = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_NAMED_STATEMENT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_LOOP = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_FOREACH = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_NUMBER = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_NUMBER_WRAPPER = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_CAST = NULL;

Keyword* KWD_JAVA_TRANSLATE_WRAP_FUNCTION = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_AREF = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_MV_returnarray = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_RETURN = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_BREAK = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_CONTINUE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_IF = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_SYMBOL_ID = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_OTHERWISE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_CASE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_COND = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_WHILE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_WHEN = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_UNLESS = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_MAKE_ARRAY = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_NATIVE_OBJECT_POINTER = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_caller_MV_returnarray = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION_SIGNATURE = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_VOID = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCALL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CODE_CALL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_PACKAGE = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_ARGUMENT_LIST = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_METHOD_NATIVEp = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_METHOD_CONSTRUCTORp = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_DOUBLE_FLOAT = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_UNSIGNED_LONG_INTEGER = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_THIRTY_TWO_BIT_VECTOR = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_TICKTOCK = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_NATIVE_DATE_TIME = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_ANONYMOUS_ARRAY = NULL;

Keyword* KWD_JAVA_TRANSLATE_FUNCTION = NULL;

Keyword* KWD_JAVA_TRANSLATE_METHOD = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_PRINT_STREAM = NULL;

Keyword* KWD_JAVA_TRANSLATE_WARN = NULL;

Keyword* KWD_JAVA_TRANSLATE_ERROR = NULL;

Keyword* KWD_JAVA_TRANSLATE_CONTINUABLE_ERROR = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_STANDARD_ERROR = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_STANDARD_OUT = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_OBJECT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_LITERAL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_PRINT_NATIVE_STREAM = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_EOL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_EOL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_TRUE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_FALSE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_NULL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_GET_SYM = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_INTEGER_WRAPPER = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_SYMBOL = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_GET_KWD = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_GET_SGT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_DEFINEDp = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_NULLp = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_CONCATENATE = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_NTH = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_NTH_SETTER = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_AREF = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_AREF_SETTER = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_METHOD_SLOT = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_UNARY_OP = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_BINARY_OP = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_TERNARY_OP = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_ARRAY = NULL;

Surrogate* SGT_JAVA_TRANSLATE_STELLA_NATIVE_VECTOR = NULL;

Symbol* SYM_JAVA_TRANSLATE_STELLA_STARTUP_JAVA_TRANSLATE = NULL;

} // end of namespace stella
