//  -*- Mode: C++ -*-

// dynamic-slots.cc

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

Object* dynamicSlotValue(KeyValueList* dynamicslots, Symbol* slotname, Object* nullvalue) {
  { Object* key = NULL;
    Object* value = NULL;
    KvCons* iter000 = dynamicslots->theKvList;

    for  (; ((boolean)(iter000)); 
          iter000 = iter000->rest) {
      key = iter000->key;
      value = iter000->value;
      if (key == slotname) {
        if (!((boolean)(value))) {
          return (nullvalue);
        }
        else {
          return (value);
        }
      }
    }
  }
  return (nullvalue);
}

Object* setDynamicSlotValue(KeyValueList* dynamicslots, Symbol* slotname, Object* value, Wrapper* nullwrapper) {
  { boolean deletevalueP = (value == nullwrapper) &&
        (!(nullwrapper == FALSE_WRAPPER));
    KvCons* cursor = dynamicslots->theKvList;

    while (((boolean)(cursor))) {
      if (cursor->key == slotname) {
        if (deletevalueP) {
          dynamicslots->removeAt(slotname);
        }
        else {
          cursor->value = value;
        }
        return (value);
      }
      cursor = cursor->rest;
    }
    if (!deletevalueP) {
      dynamicslots->theKvList = kvCons(slotname, value, dynamicslots->theKvList);
    }
    return (value);
  }
}

boolean standardDynamicSlotAccessP(StorageSlot* slot) {
  return ((!slot->activeP()) &&
      ((slot->allocation() == KWD_DYNAMIC_SLOTS_DYNAMIC) &&
       ((!slotValueIsBareLiteralP(slot)) ||
        ((boolean)(lookupLiteralTypeInfo(slot->slotBaseType, KWD_DYNAMIC_SLOTS_NULL_WRAPPER))))));
}

Cons* yieldDownCastTree(Cons* tree, StandardObject* returntype) {
  { StandardObject* dummy1;
    StandardObject* dummy2;

    { Cons* otree = sysTree(tree, returntype, dummy1);

      if (!(oTRANSLATOROUTPUTLANGUAGEo == KWD_DYNAMIC_SLOTS_COMMON_LISP)) {
        setTargetLanguageType(otree, SGT_DYNAMIC_SLOTS_STELLA_OBJECT, dummy2);
      }
      return (otree);
    }
  }
}

Cons* yieldStandardDynamicSlotValueTree(StorageSlot* slot, Object* objectref, StandardObject* returntype) {
  { StandardObject* dummy1;

    { Symbol* slotname = canonicalSlot(slot)->slotName;

      if (slotValueIsBareLiteralP(slot)) {
        return (listO(3, SYM_DYNAMIC_SLOTS_STELLA_WRAPPER_VALUE, listO(4, SYM_DYNAMIC_SLOTS_STELLA_SAFE_CAST, listO(5, SYM_DYNAMIC_SLOTS_STELLA_DYNAMIC_SLOT_VALUE, listO(3, SYM_DYNAMIC_SLOTS_STELLA_DYNAMIC_SLOTS, objectref, NIL), listO(3, SYM_DYNAMIC_SLOTS_STELLA_QUOTE, slotname, NIL), lookupLiteralTypeInfo(slot->type(), KWD_DYNAMIC_SLOTS_NULL_WRAPPER), NIL), typeToSymbol(slot->type()->typeToWrappedType()), NIL), NIL));
      }
      else {
        return (yieldDownCastTree(walkAConsTree(listO(5, SYM_DYNAMIC_SLOTS_STELLA_DYNAMIC_SLOT_VALUE, listO(3, SYM_DYNAMIC_SLOTS_STELLA_DYNAMIC_SLOTS, objectref, NIL), listO(3, SYM_DYNAMIC_SLOTS_STELLA_QUOTE, slotname, NIL), SYM_DYNAMIC_SLOTS_STELLA_NULL, NIL), dummy1), returntype));
      }
    }
  }
}

Cons* yieldStandardDynamicSlotValueSetterTree(StorageSlot* slot, Object* objectref, Object* valueref, StandardObject* returntype) {
  { StandardObject* dummy1;

    { Symbol* slotname = canonicalSlot(slot)->slotName;
      boolean literalslotP = slotValueIsBareLiteralP(slot);
      Cons* settertree = NULL;

      if (literalslotP) {
        settertree = listO(5, SYM_DYNAMIC_SLOTS_STELLA_SET_DYNAMIC_SLOT_VALUE, listO(3, SYM_DYNAMIC_SLOTS_STELLA_DYNAMIC_SLOTS, objectref, NIL), listO(3, SYM_DYNAMIC_SLOTS_STELLA_BQUOTE, slotname, NIL), valueref, cons(lookupLiteralTypeInfo(slot->type(), KWD_DYNAMIC_SLOTS_NULL_WRAPPER), NIL));
      }
      else {
        settertree = listO(5, SYM_DYNAMIC_SLOTS_STELLA_SET_DYNAMIC_SLOT_VALUE, listO(3, SYM_DYNAMIC_SLOTS_STELLA_DYNAMIC_SLOTS, objectref, NIL), listO(3, SYM_DYNAMIC_SLOTS_STELLA_BQUOTE, slotname, NIL), valueref, cons(SYM_DYNAMIC_SLOTS_STELLA_NULL, NIL));
      }
      if (walkingExpressionP()) {
        if (literalslotP) {
          settertree = listO(3, SYM_DYNAMIC_SLOTS_STELLA_WRAPPER_VALUE, listO(3, SYM_DYNAMIC_SLOTS_STELLA_SAFE_CAST, settertree, cons(typeToSymbol(slot->type()->typeToWrappedType()), NIL)), NIL);
        }
        else {
          settertree = yieldDownCastTree(walkAConsTree(settertree, dummy1), returntype);
        }
      }
      return (settertree);
    }
  }
}

void startupDynamicSlots() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      KWD_DYNAMIC_SLOTS_DYNAMIC = ((Keyword*)(internRigidSymbolWrtModule("DYNAMIC", NULL, 2)));
      KWD_DYNAMIC_SLOTS_NULL_WRAPPER = ((Keyword*)(internRigidSymbolWrtModule("NULL-WRAPPER", NULL, 2)));
      KWD_DYNAMIC_SLOTS_COMMON_LISP = ((Keyword*)(internRigidSymbolWrtModule("COMMON-LISP", NULL, 2)));
      SGT_DYNAMIC_SLOTS_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
      SYM_DYNAMIC_SLOTS_STELLA_WRAPPER_VALUE = ((Symbol*)(internRigidSymbolWrtModule("WRAPPER-VALUE", NULL, 0)));
      SYM_DYNAMIC_SLOTS_STELLA_SAFE_CAST = ((Symbol*)(internRigidSymbolWrtModule("SAFE-CAST", NULL, 0)));
      SYM_DYNAMIC_SLOTS_STELLA_DYNAMIC_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("DYNAMIC-SLOT-VALUE", NULL, 0)));
      SYM_DYNAMIC_SLOTS_STELLA_DYNAMIC_SLOTS = ((Symbol*)(internRigidSymbolWrtModule("DYNAMIC-SLOTS", NULL, 0)));
      SYM_DYNAMIC_SLOTS_STELLA_QUOTE = ((Symbol*)(internRigidSymbolWrtModule("QUOTE", NULL, 0)));
      SYM_DYNAMIC_SLOTS_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
      SYM_DYNAMIC_SLOTS_STELLA_SET_DYNAMIC_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SET-DYNAMIC-SLOT-VALUE", NULL, 0)));
      SYM_DYNAMIC_SLOTS_STELLA_BQUOTE = ((Symbol*)(internRigidSymbolWrtModule("BQUOTE", NULL, 0)));
      SYM_DYNAMIC_SLOTS_STELLA_STARTUP_DYNAMIC_SLOTS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-DYNAMIC-SLOTS", NULL, 0)));
      SYM_DYNAMIC_SLOTS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("DYNAMIC-SLOT-VALUE", "(DEFUN (DYNAMIC-SLOT-VALUE OBJECT) ((DYNAMICSLOTS KEY-VALUE-LIST) (SLOTNAME SYMBOL) (NULLVALUE OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&dynamicSlotValue)), NULL);
      defineFunctionObject("SET-DYNAMIC-SLOT-VALUE", "(DEFUN (SET-DYNAMIC-SLOT-VALUE OBJECT) ((DYNAMICSLOTS KEY-VALUE-LIST) (SLOTNAME SYMBOL) (VALUE OBJECT) (NULLWRAPPER WRAPPER)) :PUBLIC? TRUE)", ((cpp_function_code)(&setDynamicSlotValue)), NULL);
      defineFunctionObject("STANDARD-DYNAMIC-SLOT-ACCESS?", "(DEFUN (STANDARD-DYNAMIC-SLOT-ACCESS? BOOLEAN) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&standardDynamicSlotAccessP)), NULL);
      defineFunctionObject("YIELD-DOWN-CAST-TREE", "(DEFUN (YIELD-DOWN-CAST-TREE CONS) ((TREE CONS) (RETURNTYPE TYPE-SPEC)))", ((cpp_function_code)(&yieldDownCastTree)), NULL);
      defineFunctionObject("YIELD-STANDARD-DYNAMIC-SLOT-VALUE-TREE", "(DEFUN (YIELD-STANDARD-DYNAMIC-SLOT-VALUE-TREE CONS) ((SLOT STORAGE-SLOT) (OBJECTREF OBJECT) (RETURNTYPE TYPE-SPEC)))", ((cpp_function_code)(&yieldStandardDynamicSlotValueTree)), NULL);
      defineFunctionObject("YIELD-STANDARD-DYNAMIC-SLOT-VALUE-SETTER-TREE", "(DEFUN (YIELD-STANDARD-DYNAMIC-SLOT-VALUE-SETTER-TREE CONS) ((SLOT STORAGE-SLOT) (OBJECTREF OBJECT) (VALUEREF OBJECT) (RETURNTYPE TYPE-SPEC)))", ((cpp_function_code)(&yieldStandardDynamicSlotValueSetterTree)), NULL);
      defineFunctionObject("STARTUP-DYNAMIC-SLOTS", "(DEFUN STARTUP-DYNAMIC-SLOTS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupDynamicSlots)), NULL);
      { MethodSlot* function = lookupFunction(SYM_DYNAMIC_SLOTS_STELLA_STARTUP_DYNAMIC_SLOTS);

        setDynamicSlotValue(function->dynamicSlots, SYM_DYNAMIC_SLOTS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupDynamicSlots"), NULL_STRING_WRAPPER);
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

Keyword* KWD_DYNAMIC_SLOTS_DYNAMIC = NULL;

Keyword* KWD_DYNAMIC_SLOTS_NULL_WRAPPER = NULL;

Keyword* KWD_DYNAMIC_SLOTS_COMMON_LISP = NULL;

Surrogate* SGT_DYNAMIC_SLOTS_STELLA_OBJECT = NULL;

Symbol* SYM_DYNAMIC_SLOTS_STELLA_WRAPPER_VALUE = NULL;

Symbol* SYM_DYNAMIC_SLOTS_STELLA_SAFE_CAST = NULL;

Symbol* SYM_DYNAMIC_SLOTS_STELLA_DYNAMIC_SLOT_VALUE = NULL;

Symbol* SYM_DYNAMIC_SLOTS_STELLA_DYNAMIC_SLOTS = NULL;

Symbol* SYM_DYNAMIC_SLOTS_STELLA_QUOTE = NULL;

Symbol* SYM_DYNAMIC_SLOTS_STELLA_NULL = NULL;

Symbol* SYM_DYNAMIC_SLOTS_STELLA_SET_DYNAMIC_SLOT_VALUE = NULL;

Symbol* SYM_DYNAMIC_SLOTS_STELLA_BQUOTE = NULL;

Symbol* SYM_DYNAMIC_SLOTS_STELLA_STARTUP_DYNAMIC_SLOTS = NULL;

Symbol* SYM_DYNAMIC_SLOTS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
