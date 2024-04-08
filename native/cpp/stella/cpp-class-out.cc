//  -*- Mode: C++ -*-

// cpp-class-out.cc

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

Cons* cppYieldInitialNullValue() {
  return (((Cons*)(cppTranslateATree(NULL))));
}

Cons* cppYieldMemberVarTree(StorageSlot* slot, Class* clasS) {
  { Symbol* slotname = trueSlotName(slot->slotName, clasS->classType);
    StandardObject* slottype = (slot->slotContextSensitiveP ? SGT_CPP_CLASS_OUT_STELLA_OBJECT : ((StandardObject*)(slot->computeReturnTypeSpec(clasS->classType))));
    Keyword* allocation = slot->allocation();
    Cons* allocationform = NIL;
    const char* documentation = ((StringWrapper*)(dynamicSlotValue(slot->dynamicSlots, SYM_CPP_CLASS_OUT_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue;
    Cons* documentationform = NIL;

    if (allocation == KWD_CPP_CLASS_OUT_EMBEDDED) {
      allocationform = NIL;
    }
    else if (allocation == KWD_CPP_CLASS_OUT_INSTANCE) {
      allocationform = NIL;
    }
    else if (allocation == KWD_CPP_CLASS_OUT_CLASS) {
      allocationform = consList(1, wrapString("static"));
    }
    else {
      allocationform = NIL;
    }
    if (documentation != NULL) {
      documentationform = cons(wrapString(documentation), NIL);
    }
    return (listO(3, allocationform->concatenate(cons(cppTranslateAndPointerizeTypeSpec(slottype), NIL), 0), cppTranslateName(slotname), documentationform->concatenate(NIL, 0)));
  }
}

Cons* cppYieldParameterizedMemberVarTree(StorageSlot* slot, Class* clasS) {
  { Symbol* slotname = trueSlotName(slot->slotName, clasS->classType);
    Keyword* allocation = slot->allocation();
    Cons* allocationform = NIL;

    if (allocation == KWD_CPP_CLASS_OUT_EMBEDDED) {
      allocationform = NIL;
    }
    else if (allocation == KWD_CPP_CLASS_OUT_INSTANCE) {
      allocationform = NIL;
    }
    else if (allocation == KWD_CPP_CLASS_OUT_CLASS) {
      allocationform = consList(1, wrapString("static"));
    }
    else {
      allocationform = NIL;
    }
    return (listO(3, allocationform->concatenate(cons(cppTranslateClassParameterName(getSlotClassParameterName(slot)), NIL), 0), cppTranslateName(slotname), cons(SYM_CPP_CLASS_OUT_STELLA_NULL, NIL)));
  }
}

Cons* cppYieldStaticMemberAllocationTree(StorageSlot* slot, Class* clasS) {
  { Symbol* slotname = slot->slotName;
    Cons* allocationform = NIL;
    Slot* mostgeneralslot = NULL;

    mostgeneralslot = slot;
    for (;;) {
      if (((boolean)(mostgeneralslot->slotDirectEquivalent))) {
        mostgeneralslot = mostgeneralslot->slotDirectEquivalent;
      }
      else {
        break;
      }
    }
    return (listO(3, allocationform->concatenate(cons(cppTranslateAndPointerizeTypeSpec(mostgeneralslot->computeReturnTypeSpec(clasS->classType)), NIL), 0), cppTranslateName(slotname), cons(SYM_CPP_CLASS_OUT_STELLA_NULL, NIL)));
  }
}

Cons* cppYieldMemberFuncSignatureTree(MethodSlot* method) {
  oMETHODBEINGWALKEDo = method;
  return (cons((method->methodFunctionP ? NULL : cppTranslateClassName(internSymbolInModule(method->slotOwner->symbolName, ((Module*)(method->slotOwner->homeContext)), false))), listO(3, cons(wrapString("virtual"), cons(cppTranslateAndPointerizeTypeSpec(computeMostGeneralReturnType(method, method->computeReturnTypeSpec(method->slotOwner))), NIL)), cppTranslateFunctionName(method, false), cons(cppTranslateFunctionParameters(method), NIL))));
}

Cons* cppYieldConstructorSignatureTree(MethodSlot* method) {
  oMETHODBEINGWALKEDo = method;
  return (cons(cppTranslateClassName(internSymbolInModule(method->slotOwner->symbolName, ((Module*)(method->slotOwner->homeContext)), false)), listO(3, NIL, cppTranslateConstructorName(method), cons(cppTranslateFunctionParameters(method), NIL))));
}

Cons* cppYieldExceptionConstructorDefinition(Class* clasS) {
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

      return (listO(4, SYM_CPP_CLASS_OUT_STELLA_CPP_FUNCTION, NIL, cppTranslateClassName(clasS->classType), listO(4, cons(listO(3, wrapString("const std::string&"), wrapString("msg"), NIL), NIL), NIL, cons(listO(4, SYM_CPP_CLASS_OUT_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_CLASS_OUT_STELLA_CPP_IDENT, cppTranslateClassName(super), NIL), listO(3, SYM_CPP_CLASS_OUT_STELLA_CPP_ACTUALS, listO(3, SYM_CPP_CLASS_OUT_STELLA_CPP_IDENT, wrapString("msg"), NIL), NIL), NIL), NIL), NIL)));
    }
  }
}

boolean slotHasClassParameterTypeP(StorageSlot* slot, Class* clasS) {
  return (((boolean)(((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_CPP_CLASS_OUT_STELLA_SLOT_TYPE_SPECIFIER, NULL))))) &&
      (isaP(((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_CPP_CLASS_OUT_STELLA_SLOT_TYPE_SPECIFIER, NULL))), SGT_CPP_CLASS_OUT_STELLA_ANCHORED_TYPE_SPECIFIER) &&
       (slot->computeReturnTypeSpec(clasS->classType) == SGT_CPP_CLASS_OUT_STELLA_UNKNOWN)));
}

Symbol* getSlotClassParameterName(StorageSlot* slot) {
  return (((AnchoredTypeSpecifier*)(((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_CPP_CLASS_OUT_STELLA_SLOT_TYPE_SPECIFIER, NULL)))))->specifierParameterName);
}

boolean cppNativeMethodP(MethodSlot* methodslot) {
  { Symbol* testValue000 = methodslot->slotName;

    if ((testValue000 == SYM_CPP_CLASS_OUT_STELLA_DEFINEDp) ||
        (testValue000 == SYM_CPP_CLASS_OUT_STELLA_NULLp)) {
      return (true);
    }
    else {
      return (false);
    }
  }
}

Cons* cppGetParameterizedMemberVariableDefinitions(Class* clasS) {
  { Cons* membervardefs = NIL;

    { Slot* slot = NULL;
      Cons* iter000 = clasS->classLocalSlots->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        slot = ((Slot*)(iter000->value));
        if (storageSlotP(slot) &&
            (nativeSlotP(((StorageSlot*)(slot))) &&
             slotHasClassParameterTypeP(((StorageSlot*)(slot)), clasS))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(cppYieldParameterizedMemberVarTree(((StorageSlot*)(slot)), clasS), NIL);
              if (membervardefs == NIL) {
                membervardefs = collect000;
              }
              else {
                addConsToEndOfConsList(membervardefs, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(cppYieldParameterizedMemberVarTree(((StorageSlot*)(slot)), clasS), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (membervardefs);
  }
}

Cons* cppGetMemberVariableDefinitions(Class* clasS, Cons*& _Return1) {
  { Cons* publicmembervardefs = NIL;
    Cons* protectedmembervardefs = NIL;

    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();

      for (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if (storageSlotP(slot) &&
            (nativeSlotP(((StorageSlot*)(slot))) &&
             (nativeSlotHome(slot, clasS) == clasS))) {
          if (slot->slotPublicP) {
            publicmembervardefs = cons(cppYieldMemberVarTree(((StorageSlot*)(slot)), clasS), publicmembervardefs);
          }
          else {
            protectedmembervardefs = cons(cppYieldMemberVarTree(((StorageSlot*)(slot)), clasS), protectedmembervardefs);
          }
        }
      }
    }
    { Cons* _Return0 = publicmembervardefs->reverse();

      _Return1 = protectedmembervardefs->reverse();
      return (_Return0);
    }
  }
}

Cons* cppGetStaticVariableDefinitions(Class* clasS) {
  { Cons* staticmembervardefs = NIL;

    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();

      for (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if (storageSlotP(slot) &&
            (nativeSlotP(((StorageSlot*)(slot))) &&
             ((((StorageSlot*)(slot))->allocation() == KWD_CPP_CLASS_OUT_CLASS) &&
              ((!((StorageSlot*)(slot))->slotHardwiredP) &&
               ((!slot->slotMarkedP) &&
                (nativeSlotHome(slot, clasS) == clasS)))))) {
          staticmembervardefs = cons(cppYieldStaticMemberAllocationTree(((StorageSlot*)(slot)), clasS), staticmembervardefs);
        }
      }
    }
    return (staticmembervardefs);
  }
}

Cons* cppGetConstructorDefinitions(Class* clasS) {
  { Cons* constructordefs = NIL;

    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if ((!slot->slotMarkedP) &&
            ((slot->primaryType() == SGT_CPP_CLASS_OUT_STELLA_METHOD_SLOT) &&
             (localSlotP(slot, clasS) &&
              cppConstructorP(((MethodSlot*)(slot)))))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(cppYieldConstructorSignatureTree(((MethodSlot*)(slot))), NIL);
              if (constructordefs == NIL) {
                constructordefs = collect000;
              }
              else {
                addConsToEndOfConsList(constructordefs, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(cppYieldConstructorSignatureTree(((MethodSlot*)(slot))), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (constructordefs);
  }
}

Cons* cppGetMethodDefinitions(Class* clasS, Cons*& _Return1) {
  { Cons* publicmemberfuncdefs = NIL;
    Cons* protectedmemberfuncdefs = NIL;

    { Slot* slot = NULL;
      Cons* iter000 = clasS->classLocalSlots->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        slot = ((Slot*)(iter000->value));
        if (subtypeOfMethodSlotP(safePrimaryType(slot))) {
          { Slot* slot000 = slot;
            MethodSlot* slot = ((MethodSlot*)(slot000));

            if ((!slot->slotMarkedP) &&
                (nativeMethodP(slot) &&
                 ((!cppConstructorP(slot)) &&
                  (!cppNativeMethodP(slot))))) {
              if (slot->slotPublicP) {
                publicmemberfuncdefs = cons(cppYieldMemberFuncSignatureTree(slot), publicmemberfuncdefs);
              }
              else {
                protectedmemberfuncdefs = cons(cppYieldMemberFuncSignatureTree(slot), protectedmemberfuncdefs);
              }
            }
          }
        }
        else {
        }
      }
    }
    { MethodSlot* method = NULL;
      Cons* iter001 = clasS->classAuxiliaryMethods_reader()->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        method = ((MethodSlot*)(iter001->value));
        if (method->slotPublicP) {
          publicmemberfuncdefs = cons(cppYieldMemberFuncSignatureTree(method), publicmemberfuncdefs);
        }
        else {
          protectedmemberfuncdefs = cons(cppYieldMemberFuncSignatureTree(method), protectedmemberfuncdefs);
        }
      }
    }
    { Cons* _Return0 = publicmemberfuncdefs->reverse();

      _Return1 = protectedmemberfuncdefs->reverse();
      return (_Return0);
    }
  }
}

void markRenamingSlots(Class* clasS) {
  { Slot* slot = NULL;
    Iterator* iter000 = clasS->classSlots();

    for (; iter000->nextP(); ) {
      slot = ((Slot*)(iter000->value));
      slot->slotMarkedP = false;
    }
  }
  { Slot* slot = NULL;
    Iterator* iter001 = clasS->classSlots();

    for (; iter001->nextP(); ) {
      slot = ((Slot*)(iter001->value));
      if (!slot->slotMarkedP) {
        if (((boolean)(slot->slotDirectEquivalent)) &&
            (!slot->slotDirectEquivalent->slotRenamedP)) {
          markDirectEquivalentSlot(slot);
          slot->slotMarkedP = false;
        }
      }
    }
  }
}

boolean cppClassHasOnlyNativeParentsP(Class* clasS) {
  { Class* super = NULL;
    Cons* iter000 = clasS->classAllSuperClasses;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      super = ((Class*)(iter000->value));
      if (!(super->mixinP)) {
        if (createNativeClassP(super) &&
            (((StringWrapper*)(dynamicSlotValue(super->dynamicSlots, SYM_CPP_CLASS_OUT_STELLA_CLASS_CPP_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue == NULL)) {
          return (false);
        }
      }
    }
  }
  return (true);
}

Cons* cppTranslateDefineNativeClassUnit(TranslationUnit* unit) {
  { Class* clasS = ((Class*)(unit->theObject));
    Cons* baseclasses = NIL;
    Cons* parameterizedmembervardefs = NIL;
    Cons* publicmembervardefs = NIL;
    Cons* protectedmembervardefs = NIL;
    Cons* publicmemberfuncdefs = NIL;
    Cons* protectedmemberfuncdefs = NIL;
    Cons* constructordefs = NIL;
    Cons* parameters = NIL;
    Cons* staticmembervardefs = NIL;

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
              collect000 = cons(cppTranslateClassName(super), NIL);
              if (baseclasses == NIL) {
                baseclasses = collect000;
              }
              else {
                addConsToEndOfConsList(baseclasses, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(cppTranslateClassName(super), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    if (((baseclasses == NIL) ||
        cppClassHasOnlyNativeParentsP(clasS)) &&
        ((!clasS->mixinP) &&
         ((oTRANSLATOROUTPUTLANGUAGEo == KWD_CPP_CLASS_OUT_CPP) &&
          cppUseGarbageCollectorP()))) {
      baseclasses = cons(cppTranslateName(SYM_CPP_CLASS_OUT_STELLA_GC), baseclasses);
    }
    { Symbol* parameter = NULL;
      Cons* iter001 = clasS->classParameters_reader()->theConsList;
      Cons* collect001 = NULL;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest) {
        parameter = ((Symbol*)(iter001->value));
        if (!((boolean)(collect001))) {
          {
            collect001 = cons(cppTranslateClassParameterName(parameter), NIL);
            if (parameters == NIL) {
              parameters = collect001;
            }
            else {
              addConsToEndOfConsList(parameters, collect001);
            }
          }
        }
        else {
          {
            collect001->rest = cons(cppTranslateClassParameterName(parameter), NIL);
            collect001 = collect001->rest;
          }
        }
      }
    }
    markRenamingSlots(clasS);
    if (oTRANSLATOROUTPUTLANGUAGEo == KWD_CPP_CLASS_OUT_CPP_STANDALONE) {
      constructordefs = cppGetConstructorDefinitions(clasS);
    }
    if (cppOutputTemplateClassesP()) {
      parameterizedmembervardefs = cppGetParameterizedMemberVariableDefinitions(clasS);
    }
    publicmembervardefs = cppGetMemberVariableDefinitions(clasS, protectedmembervardefs);
    publicmemberfuncdefs = cppGetMethodDefinitions(clasS, protectedmemberfuncdefs);
    staticmembervardefs = cppGetStaticVariableDefinitions(clasS);
    return (listO(3, SYM_CPP_CLASS_OUT_STELLA_CPP_CLASS, cppTranslateClassName(internSymbolInModule(clasS->classType->symbolName, ((Module*)(clasS->classType->homeContext)), false)), cons(parameters, cons(baseclasses, cons(staticmembervardefs, (((((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_CPP_CLASS_OUT_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue != NULL) ? cons(listO(3, SYM_CPP_CLASS_OUT_STELLA_CPP_COMMENT, wrapString(((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_CPP_CLASS_OUT_STELLA_DOCUMENTATION, NULL_STRING_WRAPPER)))->wrapperValue), NIL), NIL) : NIL))->concatenate((((!(parameterizedmembervardefs == NIL)) ? cons(listO(4, SYM_CPP_CLASS_OUT_STELLA_CPP_DECLARATIONS, KWD_CPP_CLASS_OUT_PUBLIC, parameterizedmembervardefs, NIL), NIL) : NIL))->concatenate((((!(publicmembervardefs == NIL)) ? cons(listO(4, SYM_CPP_CLASS_OUT_STELLA_CPP_DECLARATIONS, KWD_CPP_CLASS_OUT_PUBLIC, publicmembervardefs, NIL), NIL) : NIL))->concatenate((((!(protectedmembervardefs == NIL)) ? cons(listO(4, SYM_CPP_CLASS_OUT_STELLA_CPP_DECLARATIONS, KWD_CPP_CLASS_OUT_PUBLIC, protectedmembervardefs, NIL), NIL) : NIL))->concatenate((((!(constructordefs == NIL)) ? cons(listO(4, SYM_CPP_CLASS_OUT_STELLA_CPP_SIGNATURES, KWD_CPP_CLASS_OUT_PUBLIC, constructordefs, NIL), NIL) : NIL))->concatenate(((exceptionClassP(clasS) ? cons(listO(4, SYM_CPP_CLASS_OUT_STELLA_CPP_DEFINITIONS, KWD_CPP_CLASS_OUT_PUBLIC, cons(cppYieldExceptionConstructorDefinition(clasS), NIL), NIL), NIL) : NIL))->concatenate((((!(publicmemberfuncdefs == NIL)) ? cons(listO(4, SYM_CPP_CLASS_OUT_STELLA_CPP_SIGNATURES, KWD_CPP_CLASS_OUT_PUBLIC, publicmemberfuncdefs, NIL), NIL) : NIL))->concatenate((((!(protectedmemberfuncdefs == NIL)) ? cons(listO(4, SYM_CPP_CLASS_OUT_STELLA_CPP_SIGNATURES, KWD_CPP_CLASS_OUT_PUBLIC, protectedmemberfuncdefs, NIL), NIL) : NIL))->concatenate(NIL, 0), 0), 0), 0), 0), 0), 0), 0))))));
  }
}

void startupCppClassOut() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SGT_CPP_CLASS_OUT_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
      SYM_CPP_CLASS_OUT_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 0)));
      KWD_CPP_CLASS_OUT_EMBEDDED = ((Keyword*)(internRigidSymbolWrtModule("EMBEDDED", NULL, 2)));
      KWD_CPP_CLASS_OUT_INSTANCE = ((Keyword*)(internRigidSymbolWrtModule("INSTANCE", NULL, 2)));
      KWD_CPP_CLASS_OUT_CLASS = ((Keyword*)(internRigidSymbolWrtModule("CLASS", NULL, 2)));
      SYM_CPP_CLASS_OUT_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
      SYM_CPP_CLASS_OUT_STELLA_CPP_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("CPP_FUNCTION", NULL, 0)));
      SYM_CPP_CLASS_OUT_STELLA_CPP_FUNCTION_CALL = ((Symbol*)(internRigidSymbolWrtModule("CPP_FUNCTION_CALL", NULL, 0)));
      SYM_CPP_CLASS_OUT_STELLA_CPP_IDENT = ((Symbol*)(internRigidSymbolWrtModule("CPP_IDENT", NULL, 0)));
      SYM_CPP_CLASS_OUT_STELLA_CPP_ACTUALS = ((Symbol*)(internRigidSymbolWrtModule("CPP_ACTUALS", NULL, 0)));
      SYM_CPP_CLASS_OUT_STELLA_SLOT_TYPE_SPECIFIER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-TYPE-SPECIFIER", NULL, 0)));
      SGT_CPP_CLASS_OUT_STELLA_ANCHORED_TYPE_SPECIFIER = ((Surrogate*)(internRigidSymbolWrtModule("ANCHORED-TYPE-SPECIFIER", NULL, 1)));
      SGT_CPP_CLASS_OUT_STELLA_UNKNOWN = ((Surrogate*)(internRigidSymbolWrtModule("UNKNOWN", NULL, 1)));
      SYM_CPP_CLASS_OUT_STELLA_DEFINEDp = ((Symbol*)(internRigidSymbolWrtModule("DEFINED?", NULL, 0)));
      SYM_CPP_CLASS_OUT_STELLA_NULLp = ((Symbol*)(internRigidSymbolWrtModule("NULL?", NULL, 0)));
      SGT_CPP_CLASS_OUT_STELLA_METHOD_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-SLOT", NULL, 1)));
      SYM_CPP_CLASS_OUT_STELLA_CLASS_CPP_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CPP-NATIVE-TYPE", NULL, 0)));
      KWD_CPP_CLASS_OUT_CPP = ((Keyword*)(internRigidSymbolWrtModule("CPP", NULL, 2)));
      SYM_CPP_CLASS_OUT_STELLA_GC = ((Symbol*)(internRigidSymbolWrtModule("GC", NULL, 0)));
      KWD_CPP_CLASS_OUT_CPP_STANDALONE = ((Keyword*)(internRigidSymbolWrtModule("CPP-STANDALONE", NULL, 2)));
      SYM_CPP_CLASS_OUT_STELLA_CPP_CLASS = ((Symbol*)(internRigidSymbolWrtModule("CPP_CLASS", NULL, 0)));
      SYM_CPP_CLASS_OUT_STELLA_CPP_COMMENT = ((Symbol*)(internRigidSymbolWrtModule("CPP_COMMENT", NULL, 0)));
      SYM_CPP_CLASS_OUT_STELLA_CPP_DECLARATIONS = ((Symbol*)(internRigidSymbolWrtModule("CPP_DECLARATIONS", NULL, 0)));
      KWD_CPP_CLASS_OUT_PUBLIC = ((Keyword*)(internRigidSymbolWrtModule("PUBLIC", NULL, 2)));
      SYM_CPP_CLASS_OUT_STELLA_CPP_SIGNATURES = ((Symbol*)(internRigidSymbolWrtModule("CPP_SIGNATURES", NULL, 0)));
      SYM_CPP_CLASS_OUT_STELLA_CPP_DEFINITIONS = ((Symbol*)(internRigidSymbolWrtModule("CPP_DEFINITIONS", NULL, 0)));
      SYM_CPP_CLASS_OUT_STELLA_STARTUP_CPP_CLASS_OUT = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-CPP-CLASS-OUT", NULL, 0)));
      SYM_CPP_CLASS_OUT_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("CPP-YIELD-INITIAL-NULL-VALUE", "(DEFUN (CPP-YIELD-INITIAL-NULL-VALUE CONS) ())", ((cpp_function_code)(&cppYieldInitialNullValue)), NULL);
      defineFunctionObject("CPP-YIELD-MEMBER-VAR-TREE", "(DEFUN (CPP-YIELD-MEMBER-VAR-TREE CONS) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&cppYieldMemberVarTree)), NULL);
      defineFunctionObject("CPP-YIELD-PARAMETERIZED-MEMBER-VAR-TREE", "(DEFUN (CPP-YIELD-PARAMETERIZED-MEMBER-VAR-TREE CONS) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&cppYieldParameterizedMemberVarTree)), NULL);
      defineFunctionObject("CPP-YIELD-STATIC-MEMBER-ALLOCATION-TREE", "(DEFUN (CPP-YIELD-STATIC-MEMBER-ALLOCATION-TREE CONS) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&cppYieldStaticMemberAllocationTree)), NULL);
      defineFunctionObject("CPP-YIELD-MEMBER-FUNC-SIGNATURE-TREE", "(DEFUN (CPP-YIELD-MEMBER-FUNC-SIGNATURE-TREE CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&cppYieldMemberFuncSignatureTree)), NULL);
      defineFunctionObject("CPP-YIELD-CONSTRUCTOR-SIGNATURE-TREE", "(DEFUN (CPP-YIELD-CONSTRUCTOR-SIGNATURE-TREE CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&cppYieldConstructorSignatureTree)), NULL);
      defineFunctionObject("CPP-YIELD-EXCEPTION-CONSTRUCTOR-DEFINITION", "(DEFUN (CPP-YIELD-EXCEPTION-CONSTRUCTOR-DEFINITION CONS) ((CLASS CLASS)))", ((cpp_function_code)(&cppYieldExceptionConstructorDefinition)), NULL);
      defineFunctionObject("SLOT-HAS-CLASS-PARAMETER-TYPE?", "(DEFUN (SLOT-HAS-CLASS-PARAMETER-TYPE? BOOLEAN) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&slotHasClassParameterTypeP)), NULL);
      defineFunctionObject("GET-SLOT-CLASS-PARAMETER-NAME", "(DEFUN (GET-SLOT-CLASS-PARAMETER-NAME SYMBOL) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&getSlotClassParameterName)), NULL);
      defineFunctionObject("CPP-NATIVE-METHOD?", "(DEFUN (CPP-NATIVE-METHOD? BOOLEAN) ((METHODSLOT METHOD-SLOT)))", ((cpp_function_code)(&cppNativeMethodP)), NULL);
      defineFunctionObject("CPP-GET-PARAMETERIZED-MEMBER-VARIABLE-DEFINITIONS", "(DEFUN (CPP-GET-PARAMETERIZED-MEMBER-VARIABLE-DEFINITIONS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&cppGetParameterizedMemberVariableDefinitions)), NULL);
      defineFunctionObject("CPP-GET-MEMBER-VARIABLE-DEFINITIONS", "(DEFUN (CPP-GET-MEMBER-VARIABLE-DEFINITIONS CONS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&cppGetMemberVariableDefinitions)), NULL);
      defineFunctionObject("CPP-GET-STATIC-VARIABLE-DEFINITIONS", "(DEFUN (CPP-GET-STATIC-VARIABLE-DEFINITIONS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&cppGetStaticVariableDefinitions)), NULL);
      defineFunctionObject("CPP-GET-CONSTRUCTOR-DEFINITIONS", "(DEFUN (CPP-GET-CONSTRUCTOR-DEFINITIONS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&cppGetConstructorDefinitions)), NULL);
      defineFunctionObject("CPP-GET-METHOD-DEFINITIONS", "(DEFUN (CPP-GET-METHOD-DEFINITIONS CONS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&cppGetMethodDefinitions)), NULL);
      defineFunctionObject("MARK-RENAMING-SLOTS", "(DEFUN (MARK-RENAMING-SLOTS VOID) ((CLASS CLASS)))", ((cpp_function_code)(&markRenamingSlots)), NULL);
      defineFunctionObject("CPP-CLASS-HAS-ONLY-NATIVE-PARENTS?", "(DEFUN (CPP-CLASS-HAS-ONLY-NATIVE-PARENTS? BOOLEAN) ((CLASS CLASS)))", ((cpp_function_code)(&cppClassHasOnlyNativeParentsP)), NULL);
      defineFunctionObject("CPP-TRANSLATE-DEFINE-NATIVE-CLASS-UNIT", "(DEFUN (CPP-TRANSLATE-DEFINE-NATIVE-CLASS-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&cppTranslateDefineNativeClassUnit)), NULL);
      defineFunctionObject("STARTUP-CPP-CLASS-OUT", "(DEFUN STARTUP-CPP-CLASS-OUT () :PUBLIC? TRUE)", ((cpp_function_code)(&startupCppClassOut)), NULL);
      { MethodSlot* function = lookupFunction(SYM_CPP_CLASS_OUT_STELLA_STARTUP_CPP_CLASS_OUT);

        setDynamicSlotValue(function->dynamicSlots, SYM_CPP_CLASS_OUT_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupCppClassOut"), NULL_STRING_WRAPPER);
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

Surrogate* SGT_CPP_CLASS_OUT_STELLA_OBJECT = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_DOCUMENTATION = NULL;

Keyword* KWD_CPP_CLASS_OUT_EMBEDDED = NULL;

Keyword* KWD_CPP_CLASS_OUT_INSTANCE = NULL;

Keyword* KWD_CPP_CLASS_OUT_CLASS = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_NULL = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_FUNCTION = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_FUNCTION_CALL = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_IDENT = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_ACTUALS = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_SLOT_TYPE_SPECIFIER = NULL;

Surrogate* SGT_CPP_CLASS_OUT_STELLA_ANCHORED_TYPE_SPECIFIER = NULL;

Surrogate* SGT_CPP_CLASS_OUT_STELLA_UNKNOWN = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_DEFINEDp = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_NULLp = NULL;

Surrogate* SGT_CPP_CLASS_OUT_STELLA_METHOD_SLOT = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_CLASS_CPP_NATIVE_TYPE = NULL;

Keyword* KWD_CPP_CLASS_OUT_CPP = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_GC = NULL;

Keyword* KWD_CPP_CLASS_OUT_CPP_STANDALONE = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_CLASS = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_COMMENT = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_DECLARATIONS = NULL;

Keyword* KWD_CPP_CLASS_OUT_PUBLIC = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_SIGNATURES = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_DEFINITIONS = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_STARTUP_CPP_CLASS_OUT = NULL;

Symbol* SYM_CPP_CLASS_OUT_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
