//  -*- Mode: C++ -*-

// idl-class-out.cc

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

Cons* idlYieldInitialNullValue() {
  return (((Cons*)(idlTranslateATree(NULL))));
}

Cons* idlYieldAttributeTree(StorageSlot* slot, Class* clasS) {
  { Symbol* slotname = trueSlotName(slot->slotName, clasS->classType);
    Object* initialvalueform = slot->initially();
    Cons* facetform = NIL;
    Slot* mostgeneralslot = NULL;

    if (idlClassCategory(clasS) == SYM_IDL_CLASS_OUT_STELLA_IDL_INTERFACE) {
      if (slot->slotReadOnlyP) {
        facetform = listO(3, wrapString("readonly"), wrapString("attribute"), NIL);
      }
      else {
        facetform = cons(wrapString("attribute"), NIL);
      }
    }
    if (!(((boolean)(initialvalueform)))) {
      initialvalueform = idlYieldInitialNullValue();
    }
    mostgeneralslot = slot;
    return (listO(3, facetform->concatenate(cons(idlTranslateTypeSpec(mostgeneralslot->computeReturnTypeSpec(clasS->classType)), NIL), 0), idlTranslateName(slotname), cons(initialvalueform, NIL)));
  }
}

Cons* idlYieldParameterizedAttributeTree(StorageSlot* slot, Class* clasS) {
  { Symbol* slotname = trueSlotName(slot->slotName, clasS->classType);
    Object* initialvalueform = slot->initially();
    Keyword* allocation = slot->allocation();
    Cons* allocationform = NIL;

    if (!(((boolean)(initialvalueform)))) {
      initialvalueform = idlYieldInitialNullValue();
    }
    if (allocation == KWD_IDL_CLASS_OUT_EMBEDDED) {
      allocationform = NIL;
    }
    else if (allocation == KWD_IDL_CLASS_OUT_INSTANCE) {
      allocationform = NIL;
    }
    else if (allocation == KWD_IDL_CLASS_OUT_CLASS) {
      allocationform = consList(1, wrapString("static"));
    }
    else {
      allocationform = NIL;
    }
    return (listO(3, allocationform->concatenate(cons(idlTranslateClassParameterName(getSlotClassParameterName(slot)), NIL), 0), idlTranslateName(slotname), cons(initialvalueform, NIL)));
  }
}

Cons* idlYieldStaticMemberAllocationTree(StorageSlot* slot, Class* clasS) {
  { Symbol* slotname = slot->slotName;
    Object* initialvalueform = slot->initially();
    Cons* allocationform = NIL;
    Slot* mostgeneralslot = NULL;

    if (!(((boolean)(initialvalueform)))) {
      initialvalueform = idlYieldInitialNullValue();
    }
    mostgeneralslot = slot;
    for (;;) {
      if (((boolean)(mostgeneralslot->slotDirectEquivalent))) {
        mostgeneralslot = mostgeneralslot->slotDirectEquivalent;
      }
      else {
        break;
      }
    }
    return (listO(3, allocationform->concatenate(cons(idlTranslateTypeSpec(mostgeneralslot->computeReturnTypeSpec(clasS->classType)), NIL), 0), idlTranslateName(slotname), cons(initialvalueform, NIL)));
  }
}

Cons* idlYieldOperationSignatureTree(MethodSlot* method) {
  { MethodSlot* mostgeneralmethod = method;
    StandardObject* returntype = NULL;

    oMETHODBEINGWALKEDo = method;
    while (((boolean)(mostgeneralmethod->slotDirectEquivalent)) &&
        (isaP(mostgeneralmethod->slotDirectEquivalent, SGT_IDL_CLASS_OUT_STELLA_METHOD_SLOT) &&
         (!methodContainsUnknownTypeP(((MethodSlot*)(mostgeneralmethod->slotDirectEquivalent)))))) {
      mostgeneralmethod = ((MethodSlot*)(mostgeneralmethod->slotDirectEquivalent));
    }
    returntype = mostgeneralmethod->slotBaseType;
    return (cons((method->methodFunctionP ? NULL : idlTranslateClassName(internSymbolInModule(method->slotOwner->symbolName, ((Module*)(method->slotOwner->homeContext)), false))), listO(3, cons(idlTranslateTypeSpec(returntype), NIL), idlTranslateFunctionName(method), cons(idlTranslateMethodParameters(method), NIL))));
  }
}

Cons* idlYieldConstructorSignatureTree(MethodSlot* method) {
  oMETHODBEINGWALKEDo = method;
  return (cons(idlTranslateClassName(internSymbolInModule(method->slotOwner->symbolName, ((Module*)(method->slotOwner->homeContext)), false)), listO(3, NIL, idlTranslateConstructorName(method), cons(idlTranslateMethodParameters(method), NIL))));
}

boolean illegalIdlMethodP(MethodSlot* methodslot) {
  return (getQuotedTree("((DEFINED? NULL?) \"/STELLA\")", "/STELLA")->memberP(methodslot->slotName));
}

Cons* idlGetParameterizedAttributeDefinitions(Class* clasS) {
  { Cons* attributedefs = NIL;

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
              collect000 = cons(idlYieldParameterizedAttributeTree(((StorageSlot*)(slot)), clasS), NIL);
              if (attributedefs == NIL) {
                attributedefs = collect000;
              }
              else {
                addConsToEndOfConsList(attributedefs, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(idlYieldParameterizedAttributeTree(((StorageSlot*)(slot)), clasS), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (attributedefs);
  }
}

Cons* idlGetAttributeDefinitions(Class* clasS) {
  { Cons* attributedefs = NIL;

    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();

      for (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if (storageSlotP(slot) &&
            (nativeSlotP(((StorageSlot*)(slot))) &&
             (nativeSlotHome(slot, clasS) == clasS))) {
          attributedefs = cons(idlYieldAttributeTree(((StorageSlot*)(slot)), clasS), attributedefs);
        }
      }
    }
    return (attributedefs->reverse());
  }
}

Cons* idlGetStaticVariableDefinitions(Class* clasS) {
  { Cons* staticattributedefs = NIL;

    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();

      for (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if (storageSlotP(slot) &&
            (nativeSlotP(((StorageSlot*)(slot))) &&
             ((((StorageSlot*)(slot))->slotAllocation_reader() == KWD_IDL_CLASS_OUT_CLASS) &&
              ((!slotHasUnknownTypeP(((StorageSlot*)(slot)), clasS)) &&
               ((!((StorageSlot*)(slot))->slotHardwiredP) &&
                (!slot->slotMarkedP)))))) {
          staticattributedefs = cons(idlYieldStaticMemberAllocationTree(((StorageSlot*)(slot)), clasS), staticattributedefs);
        }
      }
    }
    return (staticattributedefs);
  }
}

boolean idlConstructorP(MethodSlot* method) {
  return ((method->type() == SGT_IDL_CLASS_OUT_STELLA_VOID) &&
      ((method->methodParameterNames_reader()->length() == 1) &&
       (stringEqlP(method->slotOwner->symbolName, method->slotName->symbolName) &&
        (((Module*)(method->slotOwner->homeContext)) == ((Module*)(method->slotName->homeContext))))));
}

Cons* idlGetConstructorDefinitions(Class* clasS) {
  { Cons* constructordefs = NIL;

    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if ((!slot->slotMarkedP) &&
            ((slot->primaryType() == SGT_IDL_CLASS_OUT_STELLA_METHOD_SLOT) &&
             (localSlotP(slot, clasS) &&
              idlConstructorP(((MethodSlot*)(slot)))))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(idlYieldConstructorSignatureTree(((MethodSlot*)(slot))), NIL);
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
              collect000->rest = cons(idlYieldConstructorSignatureTree(((MethodSlot*)(slot))), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (constructordefs);
  }
}

Cons* idlGetOperationDefinitions(Class* clasS) {
  { Cons* operationdefs = NIL;

    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if ((!slot->slotMarkedP) &&
            ((slot->primaryType() == SGT_IDL_CLASS_OUT_STELLA_METHOD_SLOT) &&
             (localSlotP(slot, clasS) &&
              ((!idlConstructorP(((MethodSlot*)(slot)))) &&
               ((!((MethodSlot*)(slot))->methodFunctionP) &&
                ((!illegalIdlMethodP(((MethodSlot*)(slot)))) &&
                 (!methodContainsUnknownTypeP(((MethodSlot*)(slot)))))))))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(idlYieldOperationSignatureTree(((MethodSlot*)(slot))), NIL);
              if (operationdefs == NIL) {
                operationdefs = collect000;
              }
              else {
                addConsToEndOfConsList(operationdefs, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(idlYieldOperationSignatureTree(((MethodSlot*)(slot))), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    { MethodSlot* auxiliary = NULL;
      Cons* iter001 = clasS->classAuxiliaryMethods_reader()->theConsList;
      Cons* collect001 = NULL;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest) {
        auxiliary = ((MethodSlot*)(iter001->value));
        if (!((boolean)(collect001))) {
          {
            collect001 = cons(idlYieldOperationSignatureTree(auxiliary), NIL);
            if (operationdefs == NIL) {
              operationdefs = collect001;
            }
            else {
              addConsToEndOfConsList(operationdefs, collect001);
            }
          }
        }
        else {
          {
            collect001->rest = cons(idlYieldOperationSignatureTree(auxiliary), NIL);
            collect001 = collect001->rest;
          }
        }
      }
    }
    return (operationdefs);
  }
}

Symbol* idlClassCategory(Class* clasS) {
  if (!(((boolean)(clasS->properties_reader())))) {
    return (SYM_IDL_CLASS_OUT_STELLA_IDL_INTERFACE);
  }
  { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(clasS->properties_reader()->first()));

    if (testValue000 == SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYsinterface) {
      return (SYM_IDL_CLASS_OUT_STELLA_IDL_INTERFACE);
    }
    else if (testValue000 == SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYsstruct) {
      return (SYM_IDL_CLASS_OUT_STELLA_IDL_STRUCT);
    }
    else if (testValue000 == SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYsenum) {
      return (SYM_IDL_CLASS_OUT_STELLA_IDL_ENUM);
    }
    else if (testValue000 == SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYstypedef) {
      return (SYM_IDL_CLASS_OUT_STELLA_IDL_TYPEDEF);
    }
    else {
      return (SYM_IDL_CLASS_OUT_STELLA_IDL_INTERFACE);
    }
  }
}

Cons* idlTranslateDefineNativeClassUnit(TranslationUnit* unit) {
  { Class* clasS = ((Class*)(unit->theObject));
    Cons* derivedclasses = NIL;
    Cons* parameterizedattributedefs = NIL;
    Cons* attributedefs = NIL;
    Cons* operationdefs = NIL;
    Cons* constructordefs = NIL;
    Cons* parameters = NIL;
    Cons* staticattributedefs = NIL;

    { Surrogate* super = NULL;
      Cons* iter000 = clasS->classDirectSupers->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        super = ((Surrogate*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(idlTranslateClassName(internSymbolInModule(super->symbolName, ((Module*)(super->homeContext)), false)), NIL);
            if (derivedclasses == NIL) {
              derivedclasses = collect000;
            }
            else {
              addConsToEndOfConsList(derivedclasses, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(idlTranslateClassName(internSymbolInModule(super->symbolName, ((Module*)(super->homeContext)), false)), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { Symbol* parameter = NULL;
      Cons* iter001 = clasS->classParameters_reader()->theConsList;
      Cons* collect001 = NULL;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest) {
        parameter = ((Symbol*)(iter001->value));
        if (!((boolean)(collect001))) {
          {
            collect001 = cons(idlTranslateClassParameterName(parameter), NIL);
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
            collect001->rest = cons(idlTranslateClassParameterName(parameter), NIL);
            collect001 = collect001->rest;
          }
        }
      }
    }
    { Slot* slot = NULL;
      Iterator* iter002 = clasS->classSlots();

      for (; iter002->nextP(); ) {
        slot = ((Slot*)(iter002->value));
        slot->slotMarkedP = false;
      }
    }
    { Slot* slot = NULL;
      Iterator* iter003 = clasS->classSlots();

      for (; iter003->nextP(); ) {
        slot = ((Slot*)(iter003->value));
        if (!slot->slotMarkedP) {
          if (((boolean)(slot->slotDirectEquivalent)) &&
              (!slot->slotDirectEquivalent->slotRenamedP)) {
            markDirectEquivalentSlot(slot);
            slot->slotMarkedP = false;
          }
        }
      }
    }
    constructordefs = idlGetConstructorDefinitions(clasS);
    parameterizedattributedefs = idlGetParameterizedAttributeDefinitions(clasS);
    attributedefs = idlGetAttributeDefinitions(clasS);
    operationdefs = idlGetOperationDefinitions(clasS);
    staticattributedefs = idlGetStaticVariableDefinitions(clasS);
    return (cons(idlClassCategory(clasS), cons(idlTranslateClassName(internSymbolInModule(clasS->classType->symbolName, ((Module*)(clasS->classType->homeContext)), false)), cons(parameters, cons(derivedclasses, cons(staticattributedefs, (((!(parameterizedattributedefs == NIL)) ? cons(listO(3, SYM_IDL_CLASS_OUT_STELLA_IDL_DECLARATIONS, parameterizedattributedefs, NIL), NIL) : NIL))->concatenate((((!(attributedefs == NIL)) ? cons(listO(3, SYM_IDL_CLASS_OUT_STELLA_IDL_DECLARATIONS, attributedefs, NIL), NIL) : NIL))->concatenate((((!(constructordefs == NIL)) ? cons(listO(3, SYM_IDL_CLASS_OUT_STELLA_IDL_SIGNATURES, constructordefs, NIL), NIL) : NIL))->concatenate((((!(operationdefs == NIL)) ? cons(listO(3, SYM_IDL_CLASS_OUT_STELLA_IDL_SIGNATURES, operationdefs, NIL), NIL) : NIL))->concatenate(NIL, 0), 0), 0), 0)))))));
  }
}

void startupIdlClassOut() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SYM_IDL_CLASS_OUT_STELLA_IDL_INTERFACE = ((Symbol*)(internRigidSymbolWrtModule("IDL_INTERFACE", NULL, 0)));
      KWD_IDL_CLASS_OUT_EMBEDDED = ((Keyword*)(internRigidSymbolWrtModule("EMBEDDED", NULL, 2)));
      KWD_IDL_CLASS_OUT_INSTANCE = ((Keyword*)(internRigidSymbolWrtModule("INSTANCE", NULL, 2)));
      KWD_IDL_CLASS_OUT_CLASS = ((Keyword*)(internRigidSymbolWrtModule("CLASS", NULL, 2)));
      SGT_IDL_CLASS_OUT_STELLA_METHOD_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-SLOT", NULL, 1)));
      SGT_IDL_CLASS_OUT_STELLA_VOID = ((Surrogate*)(internRigidSymbolWrtModule("VOID", NULL, 1)));
      SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYsinterface = ((Symbol*)(internRigidSymbolWrtModule("/IDL-THEORY/interface", NULL, 0)));
      SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYsstruct = ((Symbol*)(internRigidSymbolWrtModule("/IDL-THEORY/struct", NULL, 0)));
      SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYsenum = ((Symbol*)(internRigidSymbolWrtModule("/IDL-THEORY/enum", NULL, 0)));
      SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYstypedef = ((Symbol*)(internRigidSymbolWrtModule("/IDL-THEORY/typedef", NULL, 0)));
      SYM_IDL_CLASS_OUT_STELLA_IDL_STRUCT = ((Symbol*)(internRigidSymbolWrtModule("IDL_STRUCT", NULL, 0)));
      SYM_IDL_CLASS_OUT_STELLA_IDL_ENUM = ((Symbol*)(internRigidSymbolWrtModule("IDL_ENUM", NULL, 0)));
      SYM_IDL_CLASS_OUT_STELLA_IDL_TYPEDEF = ((Symbol*)(internRigidSymbolWrtModule("IDL_TYPEDEF", NULL, 0)));
      SYM_IDL_CLASS_OUT_STELLA_IDL_DECLARATIONS = ((Symbol*)(internRigidSymbolWrtModule("IDL_DECLARATIONS", NULL, 0)));
      SYM_IDL_CLASS_OUT_STELLA_IDL_SIGNATURES = ((Symbol*)(internRigidSymbolWrtModule("IDL_SIGNATURES", NULL, 0)));
      SYM_IDL_CLASS_OUT_STELLA_STARTUP_IDL_CLASS_OUT = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-IDL-CLASS-OUT", NULL, 0)));
      SYM_IDL_CLASS_OUT_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("IDL-YIELD-INITIAL-NULL-VALUE", "(DEFUN (IDL-YIELD-INITIAL-NULL-VALUE CONS) ())", ((cpp_function_code)(&idlYieldInitialNullValue)), NULL);
      defineFunctionObject("IDL-YIELD-ATTRIBUTE-TREE", "(DEFUN (IDL-YIELD-ATTRIBUTE-TREE CONS) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&idlYieldAttributeTree)), NULL);
      defineFunctionObject("IDL-YIELD-PARAMETERIZED-ATTRIBUTE-TREE", "(DEFUN (IDL-YIELD-PARAMETERIZED-ATTRIBUTE-TREE CONS) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&idlYieldParameterizedAttributeTree)), NULL);
      defineFunctionObject("IDL-YIELD-STATIC-MEMBER-ALLOCATION-TREE", "(DEFUN (IDL-YIELD-STATIC-MEMBER-ALLOCATION-TREE CONS) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&idlYieldStaticMemberAllocationTree)), NULL);
      defineFunctionObject("IDL-YIELD-OPERATION-SIGNATURE-TREE", "(DEFUN (IDL-YIELD-OPERATION-SIGNATURE-TREE CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&idlYieldOperationSignatureTree)), NULL);
      defineFunctionObject("IDL-YIELD-CONSTRUCTOR-SIGNATURE-TREE", "(DEFUN (IDL-YIELD-CONSTRUCTOR-SIGNATURE-TREE CONS) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&idlYieldConstructorSignatureTree)), NULL);
      defineFunctionObject("ILLEGAL-IDL-METHOD?", "(DEFUN (ILLEGAL-IDL-METHOD? BOOLEAN) ((METHODSLOT METHOD-SLOT)))", ((cpp_function_code)(&illegalIdlMethodP)), NULL);
      defineFunctionObject("IDL-GET-PARAMETERIZED-ATTRIBUTE-DEFINITIONS", "(DEFUN (IDL-GET-PARAMETERIZED-ATTRIBUTE-DEFINITIONS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&idlGetParameterizedAttributeDefinitions)), NULL);
      defineFunctionObject("IDL-GET-ATTRIBUTE-DEFINITIONS", "(DEFUN (IDL-GET-ATTRIBUTE-DEFINITIONS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&idlGetAttributeDefinitions)), NULL);
      defineFunctionObject("IDL-GET-STATIC-VARIABLE-DEFINITIONS", "(DEFUN (IDL-GET-STATIC-VARIABLE-DEFINITIONS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&idlGetStaticVariableDefinitions)), NULL);
      defineFunctionObject("IDL-CONSTRUCTOR?", "(DEFUN (IDL-CONSTRUCTOR? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&idlConstructorP)), NULL);
      defineFunctionObject("IDL-GET-CONSTRUCTOR-DEFINITIONS", "(DEFUN (IDL-GET-CONSTRUCTOR-DEFINITIONS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&idlGetConstructorDefinitions)), NULL);
      defineFunctionObject("IDL-GET-OPERATION-DEFINITIONS", "(DEFUN (IDL-GET-OPERATION-DEFINITIONS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&idlGetOperationDefinitions)), NULL);
      defineFunctionObject("IDL-CLASS-CATEGORY", "(DEFUN (IDL-CLASS-CATEGORY SYMBOL) ((CLASS CLASS)))", ((cpp_function_code)(&idlClassCategory)), NULL);
      defineFunctionObject("IDL-TRANSLATE-DEFINE-NATIVE-CLASS-UNIT", "(DEFUN (IDL-TRANSLATE-DEFINE-NATIVE-CLASS-UNIT CONS) ((UNIT TRANSLATION-UNIT)))", ((cpp_function_code)(&idlTranslateDefineNativeClassUnit)), NULL);
      defineFunctionObject("STARTUP-IDL-CLASS-OUT", "(DEFUN STARTUP-IDL-CLASS-OUT () :PUBLIC? TRUE)", ((cpp_function_code)(&startupIdlClassOut)), NULL);
      { MethodSlot* function = lookupFunction(SYM_IDL_CLASS_OUT_STELLA_STARTUP_IDL_CLASS_OUT);

        setDynamicSlotValue(function->dynamicSlots, SYM_IDL_CLASS_OUT_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupIdlClassOut"), NULL_STRING_WRAPPER);
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

Symbol* SYM_IDL_CLASS_OUT_STELLA_IDL_INTERFACE = NULL;

Keyword* KWD_IDL_CLASS_OUT_EMBEDDED = NULL;

Keyword* KWD_IDL_CLASS_OUT_INSTANCE = NULL;

Keyword* KWD_IDL_CLASS_OUT_CLASS = NULL;

Surrogate* SGT_IDL_CLASS_OUT_STELLA_METHOD_SLOT = NULL;

Surrogate* SGT_IDL_CLASS_OUT_STELLA_VOID = NULL;

Symbol* SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYsinterface = NULL;

Symbol* SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYsstruct = NULL;

Symbol* SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYsenum = NULL;

Symbol* SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYstypedef = NULL;

Symbol* SYM_IDL_CLASS_OUT_STELLA_IDL_STRUCT = NULL;

Symbol* SYM_IDL_CLASS_OUT_STELLA_IDL_ENUM = NULL;

Symbol* SYM_IDL_CLASS_OUT_STELLA_IDL_TYPEDEF = NULL;

Symbol* SYM_IDL_CLASS_OUT_STELLA_IDL_DECLARATIONS = NULL;

Symbol* SYM_IDL_CLASS_OUT_STELLA_IDL_SIGNATURES = NULL;

Symbol* SYM_IDL_CLASS_OUT_STELLA_STARTUP_IDL_CLASS_OUT = NULL;

Symbol* SYM_IDL_CLASS_OUT_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
