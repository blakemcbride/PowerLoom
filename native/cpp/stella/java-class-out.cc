//  -*- Mode: C++ -*-

// java-class-out.cc

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

Cons* javaYieldInstanceVarTree(StorageSlot* slot, Class* clasS) {
  { Symbol* slotname = trueSlotName(slot->slotName, clasS->classType);
    StandardObject* slottype = (slot->slotContextSensitiveP ? SGT_JAVA_CLASS_OUT_STELLA_OBJECT : ((StandardObject*)(slot->computeReturnTypeSpec(clasS->classType))));
    Keyword* allocation = slot->allocation();
    Cons* allocationform = NULL;
    Cons* accessform = NULL;
    const char* documentation = ((StringWrapper*)(dynamicSlotValue(slot->dynamicSlots, SYM_JAVA_CLASS_OUT_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue;
    Cons* documentationform = NIL;

    if (slot->slotPublicP) {
      accessform = cons(wrapString("public"), NIL);
    }
    else {
      accessform = cons(wrapString("protected"), NIL);
    }
    if (allocation == KWD_JAVA_CLASS_OUT_EMBEDDED) {
      allocationform = NIL;
    }
    else if (allocation == KWD_JAVA_CLASS_OUT_INSTANCE) {
      allocationform = NIL;
    }
    else if (allocation == KWD_JAVA_CLASS_OUT_CLASS) {
      allocationform = cons(wrapString("static"), NIL);
    }
    else {
      allocationform = NIL;
    }
    if (documentation != NULL) {
      documentationform = cons(wrapString(documentation), NIL);
    }
    return (listO(3, accessform->concatenate(allocationform->concatenate(cons(javaTranslateTypeSpec(slottype), NIL), 0), 0), javaTranslateName(slotname), documentationform->concatenate(NIL, 0)));
  }
}

Cons* javaGetInstanceVariableDefinitions(Class* clasS) {
  if (clasS->mixinP) {
    return (NIL);
  }
  { Cons* instancevardefs = NIL;
    Class* superclass = NULL;

    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if (storageSlotP(slot) &&
            (nativeSlotP(((StorageSlot*)(slot))) &&
             (nativeSlotHome(slot, clasS) == clasS))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(javaYieldInstanceVarTree(((StorageSlot*)(slot)), clasS), NIL);
              if (instancevardefs == NIL) {
                instancevardefs = collect000;
              }
              else {
                addConsToEndOfConsList(instancevardefs, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(javaYieldInstanceVarTree(((StorageSlot*)(slot)), clasS), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    { Surrogate* super = NULL;
      Cons* iter001 = clasS->classDirectSupers->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        super = ((Surrogate*)(iter001->value));
        superclass = super->getStellaClass(true);
        if (superclass->mixinP) {
          { Slot* slot = NULL;
            Iterator* iter002 = superclass->classSlots();
            Cons* collect001 = NULL;

            for  (; iter002->nextP(); ) {
              slot = ((Slot*)(iter002->value));
              if (storageSlotP(slot) &&
                  (nativeSlotP(((StorageSlot*)(slot))) &&
                   (nativeSlotHome(slot, superclass) == superclass))) {
                if (!((boolean)(collect001))) {
                  {
                    collect001 = cons(javaYieldInstanceVarTree(((StorageSlot*)(slot)), superclass), NIL);
                    if (instancevardefs == NIL) {
                      instancevardefs = collect001;
                    }
                    else {
                      addConsToEndOfConsList(instancevardefs, collect001);
                    }
                  }
                }
                else {
                  {
                    collect001->rest = cons(javaYieldInstanceVarTree(((StorageSlot*)(slot)), superclass), NIL);
                    collect001 = collect001->rest;
                  }
                }
              }
            }
          }
        }
      }
    }
    return (instancevardefs);
  }
}

Cons* javaGetConstructorAndMethodDefinitions(Class* clasS, Cons*& _Return1) {
  { Cons* constructordefinitions = NIL;
    Cons* methoddefinitions = NIL;
    MethodSlot* method = NULL;

    { TranslationUnit* tu = NULL;
      Cons* iter000 = oTRANSLATIONUNITSo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        tu = ((TranslationUnit*)(iter000->value));
        if ((tu->category == SYM_JAVA_CLASS_OUT_STELLA_METHOD) ||
            ((tu->category == SYM_JAVA_CLASS_OUT_STELLA_MACRO) ||
             (tu->category == SYM_JAVA_CLASS_OUT_STELLA_PRINT_METHOD))) {
          if (tu->category == SYM_JAVA_CLASS_OUT_STELLA_PRINT_METHOD) {
            if (canonicalType(((Class*)(tu->theObject))->classType) == clasS->classType) {
              methoddefinitions = cons(tu, methoddefinitions);
            }
          }
          else {
            {
              method = ((MethodSlot*)(tu->theObject));
              if (javaFlotsamFunctionP(method) ||
                  method->methodStartupFunctionP()) {
              }
              else if (((BooleanWrapper*)(dynamicSlotValue(method->dynamicSlots, SYM_JAVA_CLASS_OUT_STELLA_METHOD_CONSTRUCTORp, FALSE_WRAPPER)))->wrapperValue) {
                if (canonicalType(method->slotBaseType) == clasS->classType) {
                  constructordefinitions = cons(tu, constructordefinitions);
                }
              }
              else if (canonicalType(method->slotOwner) == clasS->classType) {
                methoddefinitions = cons(tu, methoddefinitions);
              }
            }
          }
        }
      }
    }
    { Cons* _Return0 = constructordefinitions->reverse();

      _Return1 = methoddefinitions->reverse();
      return (_Return0);
    }
  }
}

Cons* javaTranslateDefineNativeClassUnit(TranslationUnit* unit) {
  return (javaTranslateDefineNativeClass(((Class*)(unit->theObject))));
}

Cons* javaTranslateDefineNativeClass(Class* clasS) {
  { Object* parentclass = NULL;
    Cons* interfaceclasses = NIL;
    Cons* instancevardefs = NIL;
    Cons* constructordefs = NIL;
    Cons* modifiers = NIL;
    Cons* methoddefs = NIL;

    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, clasS->homeModule());
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      if (clasS->mixinP) {
        return (NIL);
      }
      if (clasS->abstractP) {
        modifiers = cons(wrapString("abstract"), modifiers);
      }
      if (clasS->publicP()) {
        modifiers = cons(wrapString("public"), modifiers);
      }
      if (((boolean)(((Surrogate*)(clasS->classDirectSupers->first()))))) {
        parentclass = javaTranslateClassName(symbolize(((Surrogate*)(clasS->classDirectSupers->first()))));
      }
      instancevardefs = javaGetInstanceVariableDefinitions(clasS);
      constructordefs = javaGetConstructorAndMethodDefinitions(clasS, methoddefs);
      return (cons((exceptionClassP(clasS) ? SYM_JAVA_CLASS_OUT_STELLA_JAVA_EXCEPTION_CLASS : SYM_JAVA_CLASS_OUT_STELLA_JAVA_CLASS), cons(((((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_JAVA_CLASS_OUT_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue != NULL) ? wrapString(((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_JAVA_CLASS_OUT_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue) : NULL), cons(modifiers, cons((clasS->mixinP ? wrapString("interface") : wrapString("class")), cons(javaTranslateClassName(internSymbolInModule(clasS->classType->symbolName, ((Module*)(clasS->classType->homeContext)), false)), cons(parentclass, cons(interfaceclasses, cons(((!(instancevardefs == NIL)) ? cons(cons(SYM_JAVA_CLASS_OUT_STELLA_JAVA_DECLARATIONS, instancevardefs->concatenate(NIL, 0)), NIL) : NIL), cons(constructordefs, cons(methoddefs, NIL)))))))))));
    }
  }
}

void startupJavaClassOut() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SGT_JAVA_CLASS_OUT_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
      SYM_JAVA_CLASS_OUT_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 0)));
      KWD_JAVA_CLASS_OUT_EMBEDDED = ((Keyword*)(internRigidSymbolWrtModule("EMBEDDED", NULL, 2)));
      KWD_JAVA_CLASS_OUT_INSTANCE = ((Keyword*)(internRigidSymbolWrtModule("INSTANCE", NULL, 2)));
      KWD_JAVA_CLASS_OUT_CLASS = ((Keyword*)(internRigidSymbolWrtModule("CLASS", NULL, 2)));
      SYM_JAVA_CLASS_OUT_STELLA_METHOD = ((Symbol*)(internRigidSymbolWrtModule("METHOD", NULL, 0)));
      SYM_JAVA_CLASS_OUT_STELLA_MACRO = ((Symbol*)(internRigidSymbolWrtModule("MACRO", NULL, 0)));
      SYM_JAVA_CLASS_OUT_STELLA_PRINT_METHOD = ((Symbol*)(internRigidSymbolWrtModule("PRINT-METHOD", NULL, 0)));
      SYM_JAVA_CLASS_OUT_STELLA_METHOD_CONSTRUCTORp = ((Symbol*)(internRigidSymbolWrtModule("METHOD-CONSTRUCTOR?", NULL, 0)));
      SYM_JAVA_CLASS_OUT_STELLA_JAVA_EXCEPTION_CLASS = ((Symbol*)(internRigidSymbolWrtModule("JAVA_EXCEPTION_CLASS", NULL, 0)));
      SYM_JAVA_CLASS_OUT_STELLA_JAVA_CLASS = ((Symbol*)(internRigidSymbolWrtModule("JAVA_CLASS", NULL, 0)));
      SYM_JAVA_CLASS_OUT_STELLA_JAVA_DECLARATIONS = ((Symbol*)(internRigidSymbolWrtModule("JAVA_DECLARATIONS", NULL, 0)));
      SYM_JAVA_CLASS_OUT_STELLA_STARTUP_JAVA_CLASS_OUT = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-JAVA-CLASS-OUT", NULL, 0)));
      SYM_JAVA_CLASS_OUT_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("JAVA-YIELD-INSTANCE-VAR-TREE", "(DEFUN (JAVA-YIELD-INSTANCE-VAR-TREE CONS) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&javaYieldInstanceVarTree)), NULL);
      defineFunctionObject("JAVA-GET-INSTANCE-VARIABLE-DEFINITIONS", "(DEFUN (JAVA-GET-INSTANCE-VARIABLE-DEFINITIONS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&javaGetInstanceVariableDefinitions)), NULL);
      defineFunctionObject("JAVA-GET-CONSTRUCTOR-AND-METHOD-DEFINITIONS", "(DEFUN (JAVA-GET-CONSTRUCTOR-AND-METHOD-DEFINITIONS CONS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&javaGetConstructorAndMethodDefinitions)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-DEFINE-NATIVE-CLASS-UNIT", "(DEFUN (JAVA-TRANSLATE-DEFINE-NATIVE-CLASS-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&javaTranslateDefineNativeClassUnit)), NULL);
      defineFunctionObject("JAVA-TRANSLATE-DEFINE-NATIVE-CLASS", "(DEFUN (JAVA-TRANSLATE-DEFINE-NATIVE-CLASS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&javaTranslateDefineNativeClass)), NULL);
      defineFunctionObject("STARTUP-JAVA-CLASS-OUT", "(DEFUN STARTUP-JAVA-CLASS-OUT () :PUBLIC? TRUE)", ((cpp_function_code)(&startupJavaClassOut)), NULL);
      { MethodSlot* function = lookupFunction(SYM_JAVA_CLASS_OUT_STELLA_STARTUP_JAVA_CLASS_OUT);

        setDynamicSlotValue(function->dynamicSlots, SYM_JAVA_CLASS_OUT_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupJavaClassOut"), NULL_STRING_WRAPPER);
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

Surrogate* SGT_JAVA_CLASS_OUT_STELLA_OBJECT = NULL;

Symbol* SYM_JAVA_CLASS_OUT_STELLA_DOCUMENTATION = NULL;

Keyword* KWD_JAVA_CLASS_OUT_EMBEDDED = NULL;

Keyword* KWD_JAVA_CLASS_OUT_INSTANCE = NULL;

Keyword* KWD_JAVA_CLASS_OUT_CLASS = NULL;

Symbol* SYM_JAVA_CLASS_OUT_STELLA_METHOD = NULL;

Symbol* SYM_JAVA_CLASS_OUT_STELLA_MACRO = NULL;

Symbol* SYM_JAVA_CLASS_OUT_STELLA_PRINT_METHOD = NULL;

Symbol* SYM_JAVA_CLASS_OUT_STELLA_METHOD_CONSTRUCTORp = NULL;

Symbol* SYM_JAVA_CLASS_OUT_STELLA_JAVA_EXCEPTION_CLASS = NULL;

Symbol* SYM_JAVA_CLASS_OUT_STELLA_JAVA_CLASS = NULL;

Symbol* SYM_JAVA_CLASS_OUT_STELLA_JAVA_DECLARATIONS = NULL;

Symbol* SYM_JAVA_CLASS_OUT_STELLA_STARTUP_JAVA_CLASS_OUT = NULL;

Symbol* SYM_JAVA_CLASS_OUT_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
