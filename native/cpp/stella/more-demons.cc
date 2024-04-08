//  -*- Mode: C++ -*-

// more-demons.cc

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

void inverseSlotDemon(StandardObject* self, StorageSlot* slot, StandardObject* oldvalue, StandardObject* newvalue) {
  { Slot* inverseslot = ((Slot*)(dynamicSlotValue(slot->dynamicSlots, SYM_MORE_DEMONS_STELLA_INVERSE, NULL)));

    if (((boolean)(oldvalue))) {
      dropSlotValue(oldvalue, ((StorageSlot*)(inverseslot)), self);
    }
    if (((boolean)(newvalue))) {
      putSlotValue(newvalue, ((StorageSlot*)(inverseslot)), self);
    }
  }
}

void attachInverseSlotDemon(Slot* slot) {
  if (subtypeOfStorageSlotP(safePrimaryType(slot))) {
    { Slot* slot000 = slot;
      StorageSlot* slot = ((StorageSlot*)(slot000));

      { Demon* inversedemon = lookupDemon("inverse-slot-demon");

        inversedemon->demonClassRefs->push(slot->slotOwner);
        inversedemon->demonSlotRefs->push(slot->slotName);
        setDynamicSlotValue(slot->dynamicSlots, SYM_MORE_DEMONS_STELLA_SLOT_DEMONS, injectDemon(slot->slotDemons_reader(), inversedemon), NULL);
      }
    }
  }
  else {
    return;
  }
}

void classExtensionConstructorDemon(ActiveObject* self, Class* clasS) {
  { ClassExtension* extension = clasS->extension();

    if (((boolean)(extension))) {
      extension->insert(self);
    }
  }
}

void classExtensionDestructorDemon(ActiveObject* self, Class* clasS) {
  { ClassExtension* extension = clasS->extension();

    if (((boolean)(extension))) {
      extension->remove(self);
    }
  }
}

void startupMoreDemons() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SYM_MORE_DEMONS_STELLA_INVERSE = ((Symbol*)(internRigidSymbolWrtModule("INVERSE", NULL, 0)));
      KWD_MORE_DEMONS_CODE = ((Keyword*)(internRigidSymbolWrtModule("CODE", NULL, 2)));
      SYM_MORE_DEMONS_STELLA_SLOT_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("SLOT-DEMONS", NULL, 0)));
      KWD_MORE_DEMONS_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
      KWD_MORE_DEMONS_CREATE = ((Keyword*)(internRigidSymbolWrtModule("CREATE", NULL, 2)));
      KWD_MORE_DEMONS_ALL = ((Keyword*)(internRigidSymbolWrtModule("ALL", NULL, 2)));
      KWD_MORE_DEMONS_DESTROY = ((Keyword*)(internRigidSymbolWrtModule("DESTROY", NULL, 2)));
      SYM_MORE_DEMONS_STELLA_STARTUP_MORE_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-MORE-DEMONS", NULL, 0)));
      SYM_MORE_DEMONS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("INVERSE-SLOT-DEMON", "(DEFUN INVERSE-SLOT-DEMON ((SELF STANDARD-OBJECT) (SLOT STORAGE-SLOT) (OLDVALUE STANDARD-OBJECT) (NEWVALUE STANDARD-OBJECT)))", ((cpp_function_code)(&inverseSlotDemon)), NULL);
      defineFunctionObject("ATTACH-INVERSE-SLOT-DEMON", "(DEFUN ATTACH-INVERSE-SLOT-DEMON ((SLOT SLOT)))", ((cpp_function_code)(&attachInverseSlotDemon)), NULL);
      defineFunctionObject("CLASS-EXTENSION-CONSTRUCTOR-DEMON", "(DEFUN CLASS-EXTENSION-CONSTRUCTOR-DEMON ((SELF ACTIVE-OBJECT) (CLASS CLASS)))", ((cpp_function_code)(&classExtensionConstructorDemon)), NULL);
      defineFunctionObject("CLASS-EXTENSION-DESTRUCTOR-DEMON", "(DEFUN CLASS-EXTENSION-DESTRUCTOR-DEMON ((SELF ACTIVE-OBJECT) (CLASS CLASS)))", ((cpp_function_code)(&classExtensionDestructorDemon)), NULL);
      defineFunctionObject("STARTUP-MORE-DEMONS", "(DEFUN STARTUP-MORE-DEMONS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupMoreDemons)), NULL);
      { MethodSlot* function = lookupFunction(SYM_MORE_DEMONS_STELLA_STARTUP_MORE_DEMONS);

        setDynamicSlotValue(function->dynamicSlots, SYM_MORE_DEMONS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupMoreDemons"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineDemon("inverse-slot-demon", 2, KWD_MORE_DEMONS_CODE, wrapFunctionCode(((cpp_function_code)(&inverseSlotDemon))));
      defineDemon("class-extension-constructor-demon", 6, KWD_MORE_DEMONS_DOCUMENTATION, wrapString("Demon that inserts the instance 'self' into the extension of\nthe class 'class'."), KWD_MORE_DEMONS_CREATE, KWD_MORE_DEMONS_ALL, KWD_MORE_DEMONS_CODE, wrapFunctionCode(((cpp_function_code)(&classExtensionConstructorDemon))));
      defineDemon("class-extension-destructor-demon", 6, KWD_MORE_DEMONS_DOCUMENTATION, wrapString("Demon that removes the instance 'self' from the extension of\nthe class 'class'.  Removal removes the instance forever.  Deletion without\nremoval can be achieved in constant time by setting 'deleted?' on 'self'."), KWD_MORE_DEMONS_DESTROY, KWD_MORE_DEMONS_ALL, KWD_MORE_DEMONS_CODE, wrapFunctionCode(((cpp_function_code)(&classExtensionDestructorDemon))));
      { Demon* createdemon = lookupDemon("class-extension-constructor-demon");
        Demon* destroydemon = lookupDemon("class-extension-destructor-demon");

        activateDemon(createdemon);
        activateDemon(destroydemon);
      }
    }
  }
}

Symbol* SYM_MORE_DEMONS_STELLA_INVERSE = NULL;

Keyword* KWD_MORE_DEMONS_CODE = NULL;

Symbol* SYM_MORE_DEMONS_STELLA_SLOT_DEMONS = NULL;

Keyword* KWD_MORE_DEMONS_DOCUMENTATION = NULL;

Keyword* KWD_MORE_DEMONS_CREATE = NULL;

Keyword* KWD_MORE_DEMONS_ALL = NULL;

Keyword* KWD_MORE_DEMONS_DESTROY = NULL;

Symbol* SYM_MORE_DEMONS_STELLA_STARTUP_MORE_DEMONS = NULL;

Symbol* SYM_MORE_DEMONS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
