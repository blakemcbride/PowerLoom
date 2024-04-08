//  -*- Mode: C++ -*-

// demons.cc

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

// Table containing all active and inactive demons, indexed
// on their names.
StringHashTable* oDEMONS_TABLEo = NULL;

// These demons trigger every time an active instance is created.
List* oCONSTRUCTOR_DEMONSo = NULL;

// These demons trigger every time an active instance is destroyed.
List* oDESTRUCTOR_DEMONSo = NULL;

// These demons trigger every time a slot value is modified.
List* oALL_SLOTS_DEMONSo = NULL;

// These demons trigger every time a slot value is modified, and
// cancel slot update when they return `false'.
List* oALL_SLOTS_GUARD_DEMONSo = NULL;

boolean validateDemonReferencesP(Demon* demon) {
  { Surrogate* classref = (((boolean)(demon->demonClassRefs)) ? ((Surrogate*)(demon->demonClassRefs->first())) : ((Surrogate*)(NULL)));
    Symbol* slotref = (((boolean)(demon->demonSlotRefs)) ? ((Symbol*)(demon->demonSlotRefs->first())) : ((Symbol*)(NULL)));
    Slot* slot = NULL;

    if ((!((boolean)(classref))) &&
        (!((boolean)(slotref)))) {
      return (true);
    }
    if (!((boolean)(classref))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Missing :class option in demon " << "`" << demon << "'" << std::endl;
      return (false);
    }
    if (!((boolean)(((Class*)(classref->surrogateValue))))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Class " << "`" << classref << "'" << " not yet defined." << std::endl;
      return (false);
    }
    if (demon->demonAction == KWD_DEMONS_MODIFY) {
      if (!((boolean)(slotref))) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Missing :slot option in demon " << "`" << demon << "'" << std::endl;
        return (false);
      }
      { boolean testValue000 = false;

        { 
          slot = lookupSlot(((Class*)(classref->surrogateValue)), slotref);
          testValue000 = ((boolean)(slot));
        }
        testValue000 = !testValue000;
        if (testValue000) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "No slot named " << "`" << slotref << "'" << " exists on class " << "`" << ((Class*)(classref->surrogateValue)) << "'" << "." << std::endl << "Can't create demon " << "`" << demon << "'" << std::endl;
          return (false);
        }
      }
      if (!storageSlotP(slot)) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't install a demon on the method." << "`" << slot << "'" << std::endl;
        return (false);
      }
    }
    return (true);
  }
}

boolean incorporateDemonOptionsP(Demon* demon, PropertyList* options) {
  if (((boolean)(options->lookup(KWD_DEMONS_CREATE)))) {
    demon->demonAction = KWD_DEMONS_CREATE;
  }
  else if (((boolean)(options->lookup(KWD_DEMONS_DESTROY)))) {
    demon->demonAction = KWD_DEMONS_DESTROY;
  }
  else {
    demon->demonAction = KWD_DEMONS_MODIFY;
  }
  { Object* k = NULL;
    Object* v = NULL;
    Cons* iter000 = options->thePlist;

    for  (; !(iter000 == NIL); 
          iter000 = iter000->rest->rest) {
      k = iter000->value;
      v = iter000->rest->value;
      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(k));

        if ((testValue000 == KWD_DEMONS_CREATE) ||
            (testValue000 == KWD_DEMONS_DESTROY)) {
          demon->demonAction = ((Keyword*)(k));
          if (v == KWD_DEMONS_ALL) {
            demon->demonAllP = true;
          }
          else {
            demon->demonClassRefs->insert(v->surrogatify());
          }
        }
        else if (testValue000 == KWD_DEMONS_CLASS) {
          demon->demonClassRefs->insert(v->surrogatify());
        }
        else if (testValue000 == KWD_DEMONS_SLOT) {
          if (v == KWD_DEMONS_ALL) {
            demon->demonAllP = true;
          }
          else {
            demon->demonSlotRefs->insert(((Symbol*)(v->permanentify())));
          }
        }
        else if (testValue000 == KWD_DEMONS_CODE) {
          demon->demonCode = ((FunctionCodeWrapper*)(v))->wrapperValue;
        }
        else if (testValue000 == KWD_DEMONS_METHOD) {
          demon->demonMethod = ((MethodSlot*)(v));
        }
        else if (testValue000 == KWD_DEMONS_GUARDp) {
          demon->demonGuardP = true;
        }
        else if (testValue000 == KWD_DEMONS_INHERITEDp) {
          demon->demonInheritP = true;
          std::cout << "Inherit? not yet implemented for demons" << std::endl;
        }
        else if (testValue000 == KWD_DEMONS_DOCUMENTATION) {
          demon->demonDocumentation = ((StringWrapper*)(v))->wrapperValue;
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
  if (((boolean)(demon->demonMethod))) {
    demon->demonCode = demon->demonMethod->functionCode;
  }
  options->free();
  return (validateDemonReferencesP(demon));
}

Demon* lookupDemon(const char* name) {
  // Return the demon named `name'.
  return (((Demon*)(oDEMONS_TABLEo->lookup(name))));
}

Demon* defineDemon(const char* name, int options, ...) {
  // Define a class or slot demon.  Options are :create,
  // :destroy, :class, :slot, :guard?, :code, :method, :inherit?, and :documentation.
  { Demon* demon = newDemon();
    PropertyList* plist = newPropertyList();
    Cons* conslist = NIL;
    Demon* olddemon = NULL;
    boolean activateP = false;

    { va_list iter000;
      int iter000Count = options;
      Object* item = NULL;
      Cons* collect000 = NULL;

      va_start(iter000, options);
            for  (; (iter000Count--) > 0; ) {
        item = va_arg(iter000, Object*);
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(item, NIL);
            if (conslist == NIL) {
              conslist = collect000;
            }
            else {
              addConsToEndOfConsList(conslist, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(item, NIL);
            collect000 = collect000->rest;
          }
        }
      }
      va_end(iter000);
    }
    plist->thePlist = conslist;
    demon->demonName = name;
    activateP = plist->removeAt(KWD_DEMONS_ACTIVATEp) == TRUE_WRAPPER;
    if (incorporateDemonOptionsP(demon, plist)) {
      { 
        olddemon = lookupDemon(name);
        if (((boolean)(olddemon))) {
          deactivateDemon(olddemon);
          olddemon->free();
        }
      }
      oDEMONS_TABLEo->insertAt(demon->demonName, demon);
      if (activateP) {
        activateDemon(demon);
      }
      return (demon);
    }
    demon->free();
    return (NULL);
  }
}

List* injectDemon(List* demonlist, Demon* demon) {
  if (nullListP(demonlist)) {
    demonlist = newList();
  }
  { ListIterator* it = ((ListIterator*)(demonlist->allocateIterator()));

    for (; it->nextP(); ) {
      if (stringEqlP(((Demon*)(it->value))->demonName, demon->demonName)) {
        it->valueSetter(demon);
        return (demonlist);
      }
    }
  }
  demonlist->insert(demon);
  return (demonlist);
}

List* ejectDemon(List* demonlist, Demon* demon) {
  if (!((boolean)(demonlist))) {
    return (NULL);
  }
  demonlist->remove(demon);
  if (demonlist->emptyP()) {
    demonlist->free();
    demonlist = NULL;
  }
  return (demonlist);
}

void activateDemon(Demon* demon) {
  // Install `demon' in the location(s) specified by its internal
  // structure.
  if (!((boolean)(demon))) {
    return;
  }
  { Keyword* testValue000 = demon->demonAction;

    if (testValue000 == KWD_DEMONS_MODIFY) {
      if (demon->demonAllP) {
        if (demon->demonGuardP) {
          oALL_SLOTS_GUARD_DEMONSo = injectDemon(oALL_SLOTS_GUARD_DEMONSo, demon);
        }
        else {
          oALL_SLOTS_DEMONSo = injectDemon(oALL_SLOTS_DEMONSo, demon);
        }
      }
      else {
        { Surrogate* type = NULL;
          Cons* iter000 = demon->demonClassRefs->theConsList;
          Symbol* slotname = NULL;
          Cons* iter001 = demon->demonSlotRefs->theConsList;

          for  (; (!(iter000 == NIL)) &&
                    (!(iter001 == NIL)); 
                iter000 = iter000->rest,
                iter001 = iter001->rest) {
            type = ((Surrogate*)(iter000->value));
            slotname = ((Symbol*)(iter001->value));
            { StorageSlot* slot = ((StorageSlot*)(lookupSlot(((Class*)(type->surrogateValue)), slotname)));

              if (!((boolean)(slot))) {
                *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't install demon on non-existant slot " << "`" << ((Class*)(type->surrogateValue)) << "'" << "." << "`" << slotname << "'" << std::endl;
                continue;
              }
              if (demon->demonGuardP) {
                setDynamicSlotValue(slot->dynamicSlots, SYM_DEMONS_STELLA_SLOT_GUARD_DEMONS, injectDemon(slot->slotGuardDemons_reader(), demon), NULL);
              }
              else {
                setDynamicSlotValue(slot->dynamicSlots, SYM_DEMONS_STELLA_SLOT_DEMONS, injectDemon(slot->slotDemons_reader(), demon), NULL);
              }
            }
          }
        }
      }
    }
    else if (testValue000 == KWD_DEMONS_CREATE) {
      if (demon->demonAllP) {
        oCONSTRUCTOR_DEMONSo = injectDemon(oCONSTRUCTOR_DEMONSo, demon);
      }
      else {
        { Surrogate* classref = NULL;
          Cons* iter002 = demon->demonClassRefs->theConsList;

          for (; !(iter002 == NIL); iter002 = iter002->rest) {
            classref = ((Surrogate*)(iter002->value));
            { Class* clasS = ((Class*)(classref->surrogateValue));

              if (!((boolean)(clasS))) {
                *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't install demon on non-existant class " << "`" << classref << "'" << std::endl;
                continue;
              }
              if (demon->demonGuardP) {
                setDynamicSlotValue(clasS->dynamicSlots, SYM_DEMONS_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS, injectDemon(clasS->classGuardConstructorDemons_reader(), demon), NULL);
              }
              else {
                setDynamicSlotValue(clasS->dynamicSlots, SYM_DEMONS_STELLA_CLASS_CONSTRUCTOR_DEMONS, injectDemon(clasS->classConstructorDemons_reader(), demon), NULL);
              }
            }
          }
        }
      }
    }
    else if (testValue000 == KWD_DEMONS_DESTROY) {
      if (demon->demonAllP) {
        oDESTRUCTOR_DEMONSo = injectDemon(oDESTRUCTOR_DEMONSo, demon);
      }
      else {
        { Surrogate* classref = NULL;
          Cons* iter003 = demon->demonClassRefs->theConsList;

          for (; !(iter003 == NIL); iter003 = iter003->rest) {
            classref = ((Surrogate*)(iter003->value));
            { Class* clasS = ((Class*)(classref->surrogateValue));

              if (!((boolean)(clasS))) {
                *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't install demon on non-existant class " << "`" << classref << "'" << std::endl;
                continue;
              }
              if (demon->demonGuardP) {
                setDynamicSlotValue(clasS->dynamicSlots, SYM_DEMONS_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS, injectDemon(clasS->classGuardDestructorDemons_reader(), demon), NULL);
              }
              else {
                setDynamicSlotValue(clasS->dynamicSlots, SYM_DEMONS_STELLA_CLASS_DESTRUCTOR_DEMONS, injectDemon(clasS->classDestructorDemons_reader(), demon), NULL);
              }
            }
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

void deactivateDemon(Demon* demon) {
  // Detach `demon' from the location(s) specified by its internal
  // structure.
  if (!((boolean)(demon))) {
    return;
  }
  { Keyword* testValue000 = demon->demonAction;

    if (testValue000 == KWD_DEMONS_MODIFY) {
      if (demon->demonAllP) {
        if (demon->demonGuardP) {
          oALL_SLOTS_GUARD_DEMONSo = ejectDemon(oALL_SLOTS_GUARD_DEMONSo, demon);
        }
        else {
          oALL_SLOTS_DEMONSo = ejectDemon(oALL_SLOTS_DEMONSo, demon);
        }
      }
      else {
        { Surrogate* type = NULL;
          Cons* iter000 = demon->demonClassRefs->theConsList;
          Symbol* slotname = NULL;
          Cons* iter001 = demon->demonSlotRefs->theConsList;

          for  (; (!(iter000 == NIL)) &&
                    (!(iter001 == NIL)); 
                iter000 = iter000->rest,
                iter001 = iter001->rest) {
            type = ((Surrogate*)(iter000->value));
            slotname = ((Symbol*)(iter001->value));
            { StorageSlot* slot = ((StorageSlot*)(lookupSlot(((Class*)(type->surrogateValue)), slotname)));

              if (!((boolean)(slot))) {
                *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't remove demon from non-existant slot " << "`" << ((Class*)(type->surrogateValue)) << "'" << "." << "`" << slotname << "'" << std::endl;
                continue;
              }
              if (demon->demonGuardP) {
                setDynamicSlotValue(slot->dynamicSlots, SYM_DEMONS_STELLA_SLOT_GUARD_DEMONS, ejectDemon(slot->slotGuardDemons_reader(), demon), NULL);
              }
              else {
                setDynamicSlotValue(slot->dynamicSlots, SYM_DEMONS_STELLA_SLOT_DEMONS, ejectDemon(slot->slotDemons_reader(), demon), NULL);
              }
            }
          }
        }
      }
    }
    else if (testValue000 == KWD_DEMONS_CREATE) {
      if (demon->demonAllP) {
        oCONSTRUCTOR_DEMONSo = ejectDemon(oCONSTRUCTOR_DEMONSo, demon);
      }
      else {
        { Surrogate* classref = NULL;
          Cons* iter002 = demon->demonClassRefs->theConsList;

          for (; !(iter002 == NIL); iter002 = iter002->rest) {
            classref = ((Surrogate*)(iter002->value));
            { Class* clasS = ((Class*)(classref->surrogateValue));

              if (!((boolean)(clasS))) {
                *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't install demon on non-existant class " << "`" << classref << "'" << std::endl;
                continue;
              }
              if (demon->demonGuardP) {
                setDynamicSlotValue(clasS->dynamicSlots, SYM_DEMONS_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS, ejectDemon(clasS->classGuardConstructorDemons_reader(), demon), NULL);
              }
              else {
                setDynamicSlotValue(clasS->dynamicSlots, SYM_DEMONS_STELLA_CLASS_CONSTRUCTOR_DEMONS, ejectDemon(clasS->classConstructorDemons_reader(), demon), NULL);
              }
            }
          }
        }
      }
    }
    else if (testValue000 == KWD_DEMONS_DESTROY) {
      if (demon->demonAllP) {
        oDESTRUCTOR_DEMONSo = ejectDemon(oDESTRUCTOR_DEMONSo, demon);
      }
      else {
        { Surrogate* classref = NULL;
          Cons* iter003 = demon->demonClassRefs->theConsList;

          for (; !(iter003 == NIL); iter003 = iter003->rest) {
            classref = ((Surrogate*)(iter003->value));
            { Class* clasS = ((Class*)(classref->surrogateValue));

              if (!((boolean)(clasS))) {
                *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't install demon on non-existant class " << "`" << classref << "'" << std::endl;
                continue;
              }
              if (demon->demonGuardP) {
                setDynamicSlotValue(clasS->dynamicSlots, SYM_DEMONS_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS, ejectDemon(clasS->classGuardDestructorDemons_reader(), demon), NULL);
              }
              else {
                setDynamicSlotValue(clasS->dynamicSlots, SYM_DEMONS_STELLA_CLASS_DESTRUCTOR_DEMONS, ejectDemon(clasS->classDestructorDemons_reader(), demon), NULL);
              }
            }
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

Cons* destructureDefdemonBody(Cons* demontree, Cons*& _Return1) {
  { Cons* optionstree = demontree;
    Cons* bodytree = demontree;
    Cons* trailingcursor = NULL;

    while (keywordP(bodytree->value)) {
      trailingcursor = bodytree;
      bodytree = bodytree->rest->rest;
    }
    if (((boolean)(trailingcursor))) {
      trailingcursor->rest->rest = NIL;
    }
    else {
      optionstree = NIL;
    }
    _Return1 = bodytree;
    return (optionstree);
  }
}

void inPlaceNormalizeDemonOptions(Cons* optionstree) {
  { ConsIterator* it = optionstree->allocateIterator();

    for (; it->nextP(); ) {
      if (wrapperP(it->value)) {
        it->valueSetter(listO(3, SYM_DEMONS_STELLA_WRAP_LITERAL, it->value, NIL));
      }
      else if (it->value == SYM_DEMONS_STELLA_TRUE) {
        it->valueSetter(listO(3, SYM_DEMONS_STELLA_WRAP_BOOLEAN, SYM_DEMONS_STELLA_TRUE, NIL));
      }
      else if (it->value == SYM_DEMONS_STELLA_FALSE) {
        it->valueSetter(listO(3, SYM_DEMONS_STELLA_WRAP_BOOLEAN, SYM_DEMONS_STELLA_FALSE, NIL));
      }
    }
  }
}

Object* defdemon(StringWrapper* name, Cons* parameterstree, Cons* optionsandbody) {
  // Define a demon `name' and attach it to a class or slot.
  { Object* firstparameter = parameterstree->value;
    Surrogate* type = NULL;
    Symbol* demonfunctionname = internSymbol(name->wrapperValue);

    if (!consP(firstparameter)) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Illegal first parameter in demon " << "`" << deUglifyParseTree(name) << "'" << "." << std::endl;
        }
      }
      return (NIL);
    }
    type = typeSpecToBaseType(safeYieldTypeSpecifier(((Cons*)(firstparameter))->rest->value));
    if (!((boolean)(((Class*)(type->surrogateValue))))) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationError();
        if (!(suppressWarningsP())) {
          printErrorContext(">> ERROR: ", STANDARD_ERROR);
          *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Demon defined on the non-existent class " << "`" << deUglifyParseTree(type) << "'" << "." << std::endl;
        }
      }
      return (NIL);
    }
    { Cons* optionstree = NULL;
      Cons* bodytree = NULL;

      optionstree = destructureDefdemonBody(optionsandbody, bodytree);
      inPlaceNormalizeDemonOptions(optionstree);
      return (listO(4, SYM_DEMONS_STELLA_PROGN, listO(3, SYM_DEMONS_STELLA_DEFUN, demonfunctionname, cons(parameterstree, bodytree->concatenate(NIL, 0))), listO(3, SYM_DEMONS_STELLA_STARTUP_TIME_PROGN, listO(3, SYM_DEMONS_STELLA_DEFINE_DEMON, name, optionstree->concatenate(listO(3, KWD_DEMONS_CODE, listO(3, SYM_DEMONS_STELLA_WRAP_LITERAL, listO(4, SYM_DEMONS_STELLA_THE_CODE, KWD_DEMONS_FUNCTION, demonfunctionname, NIL), NIL), NIL), 0)), NIL), NIL));
    }
  }
}

Object* readSlotValue(StandardObject* self, StorageSlot* slot) {
  // Read and return a (possibly wrapped) value for the slot `slot' on `self'.
  { cpp_function_code code = getGenericSlotAccessor(slot, self->primaryClass(), true);

    if (code != NULL) {
      return (((Object*  (*) (StandardObject*, Symbol*, Object*, boolean))code)(self, canonicalSlotName(slot), ((Object*)(NULL)), false));
    }
    else {
      return (NULL);
    }
  }
}

Object* writeSlotValue(StandardObject* self, StorageSlot* slot, Object* value) {
  // Write a (possibly wrapped) `value' for the slot `slot' on `self'.
  { cpp_function_code code = getGenericSlotAccessor(slot, self->primaryClass(), true);

    if (code != NULL) {
      return (((Object*  (*) (StandardObject*, Symbol*, Object*, boolean))code)(self, canonicalSlotName(slot), value, true));
    }
    else {
      return (NULL);
    }
  }
}

Object* putSlotValue(StandardObject* self, StorageSlot* slot, Object* value) {
  // Set or insert `value' for the slot `slot' on `self'.
  // CAUTION: Assumes that collection-valued slots are non-null.
  if (slot->collectionValuedP()) {
    { Collection* oldvalues = ((Collection*)(readSlotValue(self, slot)));

      oldvalues->insert(value);
      return (value);
    }
  }
  else {
    return (writeSlotValue(self, slot, value));
  }
}

void dropSlotValue(StandardObject* self, StorageSlot* slot, Object* value) {
  // Clear or remove `value' for the slot `slot' on `self'.
  // CAUTION: Assumes that collection-valued slots are non-null.
  if (slot->collectionValuedP()) {
    { Collection* oldvalues = ((Collection*)(readSlotValue(self, slot)));

      oldvalues->remove(value);
    }
  }
  else {
    { Object* oldvalue = readSlotValue(self, slot);

      if (eqlP(value, oldvalue)) {
        writeSlotValue(self, slot, NULL);
      }
    }
  }
}

int cppFindNativeSlotValueOffset(StandardObject* self, StorageSlot* slot) {
  // Dynamically determine the byte offset where the native value for `slot' starts in `self'.
  // This basically performs the function of the C++ macro `offsetof' but does it dynamically.  Of course, it
  // relies on a working `read/write-slot-value' mechanism and we currently primarily use this for the Python API.
  // This basically writes value changes of `slot' to determine a byte position where a change occurred and
  // then restores the original value (which can be NULL).  This handles all native OBJECT and LITERAL slots
  // but does not handle special slots such as `dynamic-slots' or hardwired slots or other non-standard types.
  { Surrogate* slottype = slot->type();
    Object* origval = readSlotValue(self, slot);
    Object* beforeval = NULL;
    Object* afterval = NULL;
    char beforebyte = NULL_CHARACTER;
    char afterbyte = NULL_CHARACTER;
    int offset = -1;

    try {
      if (subtypeOfP(slottype, SGT_DEMONS_STELLA_OBJECT)) {
        beforeval = cons(NULL, NIL);
      }
      else if (slottype == SGT_DEMONS_STELLA_BOOLEAN) {
        beforeval = (true ? TRUE_WRAPPER : FALSE_WRAPPER);
      }
      else if (slottype == SGT_DEMONS_STELLA_INTEGER) {
        beforeval = wrapInteger(42);
      }
      else if (slottype == SGT_DEMONS_STELLA_LONG_INTEGER) {
        beforeval = wrapLongInteger(42l);
      }
      else if (slottype == SGT_DEMONS_STELLA_FLOAT) {
        beforeval = wrapFloat(42.0);
      }
      else if (slottype == SGT_DEMONS_STELLA_STRING) {
        beforeval = wrapString("42");
      }
      else if (slottype == SGT_DEMONS_STELLA_MUTABLE_STRING) {
        beforeval = wrapMutableString(strcpy(new (GC) char[strlen("42")+1], "42"));
      }
      else if (slottype == SGT_DEMONS_STELLA_CHARACTER) {
        beforeval = wrapCharacter('4');
      }
      else if (slottype == SGT_DEMONS_STELLA_FUNCTION_CODE) {
        beforeval = wrapFunctionCode(((cpp_function_code)(&cons)));
      }
      else if (slottype == SGT_DEMONS_STELLA_METHOD_CODE) {
        beforeval = wrapMethodCode(((cpp_method_code)(&Cons::emptyP)));
      }
      else {
        return (-1);
      }
      afterval = beforeval;
      { Surrogate* testValue000 = safePrimaryType(afterval);

        if (subtypeOfBooleanP(testValue000)) {
          { Object* afterval000 = afterval;
            BooleanWrapper* afterval = ((BooleanWrapper*)(afterval000));

            beforeval = ((!coerceWrappedBooleanToBoolean(afterval)) ? TRUE_WRAPPER : FALSE_WRAPPER);
          }
        }
        else if (subtypeOfIntegerP(testValue000)) {
          { Object* afterval001 = afterval;
            IntegerWrapper* afterval = ((IntegerWrapper*)(afterval001));

            beforeval = afterval->copyWrappedLiteral();
            { int aftval = afterval->wrapperValue;

              beforebyte = ((char*)&aftval)[0];
                                ((char*)&aftval)[0] = (~ beforebyte);
              afterval->wrapperValue = aftval;
            }
          }
        }
        else if (subtypeOfLongIntegerP(testValue000)) {
          { Object* afterval002 = afterval;
            LongIntegerWrapper* afterval = ((LongIntegerWrapper*)(afterval002));

            beforeval = afterval->copyWrappedLiteral();
            { long long int aftval = afterval->wrapperValue;

              beforebyte = ((char*)&aftval)[0];
                                ((char*)&aftval)[0] = (~ beforebyte);
              afterval->wrapperValue = aftval;
            }
          }
        }
        else if (subtypeOfFloatP(testValue000)) {
          { Object* afterval003 = afterval;
            FloatWrapper* afterval = ((FloatWrapper*)(afterval003));

            beforeval = afterval->copyWrappedLiteral();
            { double aftval = afterval->wrapperValue;

              beforebyte = ((char*)&aftval)[0];
                                ((char*)&aftval)[0] = (~ beforebyte);
              afterval->wrapperValue = aftval;
            }
          }
        }
        else if (subtypeOfStringP(testValue000)) {
          { Object* afterval004 = afterval;
            StringWrapper* afterval = ((StringWrapper*)(afterval004));

            beforeval = afterval->copyWrappedLiteral();
            { const char* aftval = afterval->wrapperValue;

              beforebyte = ((char*)&aftval)[0];
                                ((char*)&aftval)[0] = (~ beforebyte);
              afterval->wrapperValue = aftval;
            }
          }
        }
        else if (subtypeOfCharacterP(testValue000)) {
          { Object* afterval005 = afterval;
            CharacterWrapper* afterval = ((CharacterWrapper*)(afterval005));

            beforeval = afterval->copyWrappedLiteral();
            { char aftval = afterval->wrapperValue;

              beforebyte = ((char*)&aftval)[0];
                                ((char*)&aftval)[0] = (~ beforebyte);
              afterval->wrapperValue = aftval;
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_DEMONS_STELLA_MUTABLE_STRING_WRAPPER)) {
          { Object* afterval006 = afterval;
            MutableStringWrapper* afterval = ((MutableStringWrapper*)(afterval006));

            beforeval = afterval->copyWrappedLiteral();
            { char* aftval = afterval->wrapperValue;

              beforebyte = ((char*)&aftval)[0];
                                ((char*)&aftval)[0] = (~ beforebyte);
              afterval->wrapperValue = aftval;
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_DEMONS_STELLA_FUNCTION_CODE_WRAPPER)) {
          { Object* afterval007 = afterval;
            FunctionCodeWrapper* afterval = ((FunctionCodeWrapper*)(afterval007));

            beforeval = afterval->copyWrappedLiteral();
            { cpp_function_code aftval = afterval->wrapperValue;

              beforebyte = ((char*)&aftval)[0];
                                ((char*)&aftval)[0] = (~ beforebyte);
              afterval->wrapperValue = aftval;
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_DEMONS_STELLA_METHOD_CODE_WRAPPER)) {
          { Object* afterval008 = afterval;
            MethodCodeWrapper* afterval = ((MethodCodeWrapper*)(afterval008));

            beforeval = afterval->copyWrappedLiteral();
            { cpp_method_code aftval = afterval->wrapperValue;

              beforebyte = ((char*)&aftval)[0];
                                ((char*)&aftval)[0] = (~ beforebyte);
              afterval->wrapperValue = aftval;
            }
          }
        }
        else {
          beforebyte = ((char*)&beforeval)[0];
                             ((char*)&afterval)[0] = (~ beforebyte);
        }
      }
      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = 4096;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          writeSlotValue(self, slot, beforeval);
          beforebyte = (((char*)(self)) + i)[0];
          writeSlotValue(self, slot, afterval);
          afterbyte = (((char*)(self)) + i)[0];
          if (!(beforebyte == afterbyte)) {
            offset = i;
            break;
          }
        }
      }
    }
    catch (std::exception ) {
      offset = -99;
    }
    writeSlotValue(self, slot, origval);
    return (offset);
  }
}

boolean checkForSlotDemonsP(StorageSlot* slot) {
  return (((boolean)(oALL_SLOTS_DEMONSo)) ||
      (((boolean)(oALL_SLOTS_GUARD_DEMONSo)) ||
       (((boolean)(slot->slotGuardDemons_reader())) ||
        ((boolean)(slot->slotDemons_reader())))));
}

boolean runSlotGuardDemonsP(StandardObject* self, StorageSlot* slot, Object* oldvalue, Object* newvalue) {
  if (((boolean)(oALL_SLOTS_GUARD_DEMONSo))) {
    { Demon* demon = NULL;
      Cons* iter000 = oALL_SLOTS_GUARD_DEMONSo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        demon = ((Demon*)(iter000->value));
        if (!((boolean  (*) (StandardObject*, StorageSlot*, Object*, Object*))demon->demonCode)(self, slot, oldvalue, newvalue)) {
          return (false);
        }
      }
    }
  }
  if (((boolean)(slot->slotGuardDemons_reader()))) {
    { Demon* demon = NULL;
      Cons* iter001 = slot->slotGuardDemons_reader()->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        demon = ((Demon*)(iter001->value));
        if (!((boolean  (*) (StandardObject*, StorageSlot*, Object*, Object*))demon->demonCode)(self, slot, oldvalue, newvalue)) {
          return (false);
        }
      }
    }
  }
  return (true);
}

void runSlotDemons(StandardObject* self, StorageSlot* slot, Object* oldvalue, Object* newvalue) {
  if (((boolean)(oALL_SLOTS_DEMONSo))) {
    { Demon* demon = NULL;
      Cons* iter000 = oALL_SLOTS_DEMONSo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        demon = ((Demon*)(iter000->value));
        ((void  (*) (StandardObject*, StorageSlot*, Object*, Object*))demon->demonCode)(self, slot, oldvalue, newvalue);
      }
    }
  }
  if (((boolean)(slot->slotDemons_reader()))) {
    { Demon* demon = NULL;
      Cons* iter001 = slot->slotDemons_reader()->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        demon = ((Demon*)(iter001->value));
        ((void  (*) (StandardObject*, StorageSlot*, Object*, Object*))demon->demonCode)(self, slot, oldvalue, newvalue);
      }
    }
  }
}

void runConstructorDemons(StandardObject* self) {
  { Class* clasS = self->primaryClass();

    if (((boolean)(clasS))) {
      if (((boolean)(oCONSTRUCTOR_DEMONSo))) {
        { Demon* demon = NULL;
          Cons* iter000 = oCONSTRUCTOR_DEMONSo->theConsList;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            demon = ((Demon*)(iter000->value));
            ((void  (*) (StandardObject*, Class*))demon->demonCode)(self, clasS);
          }
        }
      }
      if (((boolean)(clasS->classConstructorDemons_reader()))) {
        { Demon* demon = NULL;
          Cons* iter001 = clasS->classConstructorDemons_reader()->theConsList;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            demon = ((Demon*)(iter001->value));
            ((void  (*) (StandardObject*, Class*))demon->demonCode)(self, clasS);
          }
        }
      }
    }
  }
}

void runDestructorDemons(StandardObject* self) {
  { Class* clasS = self->primaryClass();

    if (((boolean)(clasS))) {
      if (((boolean)(oDESTRUCTOR_DEMONSo))) {
        { Demon* demon = NULL;
          Cons* iter000 = oDESTRUCTOR_DEMONSo->theConsList;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            demon = ((Demon*)(iter000->value));
            ((void  (*) (StandardObject*, Class*))demon->demonCode)(self, clasS);
          }
        }
      }
      if (((boolean)(clasS->classDestructorDemons_reader()))) {
        { Demon* demon = NULL;
          Cons* iter001 = clasS->classDestructorDemons_reader()->theConsList;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            demon = ((Demon*)(iter001->value));
            ((void  (*) (StandardObject*, Class*))demon->demonCode)(self, clasS);
          }
        }
      }
    }
  }
}

Cons* yieldActiveSlotReaderBody(StorageSlot* slot, Object* defaultexpression) {
  { Symbol* slotname = slot->slotName;

    if (!slot->collectionValuedP()) {
      return (wrapWithDefaultValueAndReturnCode(slot, defaultexpression));
    }
    else {
      {
        if (((boolean)(defaultexpression))) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Can't define a default value for the active " << "collection-valued slot named." << "`" << slot->slotName << "'" << "Ignoring the default value." << "." << std::endl;
            }
          }
        }
        return (listO(9, SYM_DEMONS_STELLA_LET, cons(listO(3, SYM_DEMONS_STELLA_VALUE, listO(4, SYM_DEMONS_STELLA_SLOT_VALUE, SYM_DEMONS_STELLA_SELF, slotname, NIL), NIL), NIL), listO(4, SYM_DEMONS_STELLA_WHEN, listO(3, SYM_DEMONS_STELLA_DEFINEDp, SYM_DEMONS_STELLA_VALUE, NIL), listO(3, SYM_DEMONS_STELLA_RETURN, SYM_DEMONS_STELLA_VALUE, NIL), NIL), listO(4, SYM_DEMONS_STELLA_SETQ, SYM_DEMONS_STELLA_VALUE, listO(3, SYM_DEMONS_STELLA_NEW, typeToSymbol(slot->type()), NIL), NIL), listO(4, SYM_DEMONS_STELLA_SETF, listO(3, SYM_DEMONS_STELLA_OWNER_INSTANCE, SYM_DEMONS_STELLA_VALUE, NIL), SYM_DEMONS_STELLA_SELF, NIL), listO(4, SYM_DEMONS_STELLA_SETF, listO(3, SYM_DEMONS_STELLA_ACTIVE_SLOT, SYM_DEMONS_STELLA_VALUE, NIL), listO(4, SYM_DEMONS_STELLA_GET_SLOT, SYM_DEMONS_STELLA_SELF, listO(3, SYM_DEMONS_STELLA_BQUOTE, slot->slotName, NIL), NIL), NIL), listO(4, SYM_DEMONS_STELLA_SETF, listO(4, SYM_DEMONS_STELLA_SLOT_VALUE, SYM_DEMONS_STELLA_SELF, slotname, NIL), SYM_DEMONS_STELLA_VALUE, NIL), listO(3, SYM_DEMONS_STELLA_RETURN, SYM_DEMONS_STELLA_VALUE, NIL), NIL));
      }
    }
  }
}

void cantOverwriteActiveCollectionSlot(StandardObject* self, Symbol* slotname) {
  *(STANDARD_WARNING->nativeStream) << "Warning: " << "Can't replace the value of the active slot " << "`" << slotname << "'" << " on the object " << std::endl << "`" << self << "'" << ".  Call `insert' or `remove' to add/remove slot values." << std::endl;
}

Cons* yieldActiveSlotWriterBody(StorageSlot* slot) {
  { Symbol* slotname = slot->slotName;
    Symbol* wrappingfunction = ((slot->slotBaseType == SGT_DEMONS_STELLA_BOOLEAN) ? SYM_DEMONS_STELLA_WRAP_BOOLEAN : SYM_DEMONS_STELLA_WRAP_LITERAL);

    if (slot->collectionValuedP()) {
      return (listO(5, SYM_DEMONS_STELLA_PROGN, SYM_DEMONS_STELLA_VALUE, listO(4, SYM_DEMONS_STELLA_CANT_OVERWRITE_ACTIVE_COLLECTION_SLOT, SYM_DEMONS_STELLA_SELF, listO(3, SYM_DEMONS_STELLA_BQUOTE, slotname, NIL), NIL), listO(3, SYM_DEMONS_STELLA_RETURN, listO(4, SYM_DEMONS_STELLA_SLOT_VALUE, SYM_DEMONS_STELLA_SELF, slot->slotName, NIL), NIL), NIL));
    }
    else if (subtypeOfP(slot->type(), SGT_DEMONS_STELLA_LITERAL)) {
      return (listO(4, SYM_DEMONS_STELLA_LET, listO(3, listO(3, SYM_DEMONS_STELLA_SLOT, listO(4, SYM_DEMONS_STELLA_GET_SLOT, SYM_DEMONS_STELLA_SELF, listO(3, SYM_DEMONS_STELLA_BQUOTE, slotname, NIL), NIL), NIL), listO(3, SYM_DEMONS_STELLA_OLDVALUE, listO(4, SYM_DEMONS_STELLA_SLOT_VALUE, SYM_DEMONS_STELLA_SELF, slotname, NIL), NIL), NIL), listO(4, SYM_DEMONS_STELLA_WHEN, listO(3, SYM_DEMONS_STELLA_NOT, listO(4, SYM_DEMONS_STELLA_EQLp, SYM_DEMONS_STELLA_OLDVALUE, SYM_DEMONS_STELLA_VALUE, NIL), NIL), listO(5, SYM_DEMONS_STELLA_IF, listO(3, SYM_DEMONS_STELLA_CHECK_FOR_SLOT_DEMONSp, SYM_DEMONS_STELLA_SLOT, NIL), listO(5, SYM_DEMONS_STELLA_LET, listO(3, listO(3, SYM_DEMONS_STELLA_WRAPPEDOLDVALUE, listO(5, SYM_DEMONS_STELLA_CHOOSE, listO(3, SYM_DEMONS_STELLA_DEFINEDp, SYM_DEMONS_STELLA_OLDVALUE, NIL), cons(wrappingfunction, cons(SYM_DEMONS_STELLA_OLDVALUE, NIL)), SYM_DEMONS_STELLA_NULL, NIL), NIL), listO(3, SYM_DEMONS_STELLA_WRAPPEDNEWVALUE, listO(5, SYM_DEMONS_STELLA_CHOOSE, listO(3, SYM_DEMONS_STELLA_DEFINEDp, SYM_DEMONS_STELLA_VALUE, NIL), cons(wrappingfunction, cons(SYM_DEMONS_STELLA_VALUE, NIL)), SYM_DEMONS_STELLA_NULL, NIL), NIL), NIL), listO(8, SYM_DEMONS_STELLA_WHEN, listO(6, SYM_DEMONS_STELLA_RUN_SLOT_GUARD_DEMONSp, SYM_DEMONS_STELLA_SELF, SYM_DEMONS_STELLA_SLOT, SYM_DEMONS_STELLA_WRAPPEDOLDVALUE, SYM_DEMONS_STELLA_WRAPPEDNEWVALUE, NIL), listO(4, SYM_DEMONS_STELLA_SETF, listO(4, SYM_DEMONS_STELLA_SLOT_VALUE, SYM_DEMONS_STELLA_SELF, slotname, NIL), SYM_DEMONS_STELLA_VALUE, NIL), listO(6, SYM_DEMONS_STELLA_RUN_SLOT_DEMONS, SYM_DEMONS_STELLA_SELF, SYM_DEMONS_STELLA_SLOT, SYM_DEMONS_STELLA_WRAPPEDOLDVALUE, SYM_DEMONS_STELLA_WRAPPEDNEWVALUE, NIL), listO(4, SYM_DEMONS_STELLA_WHEN, listO(3, SYM_DEMONS_STELLA_DEFINEDp, SYM_DEMONS_STELLA_WRAPPEDOLDVALUE, NIL), listO(3, SYM_DEMONS_STELLA_FREE, SYM_DEMONS_STELLA_WRAPPEDOLDVALUE, NIL), NIL), listO(4, SYM_DEMONS_STELLA_WHEN, listO(3, SYM_DEMONS_STELLA_DEFINEDp, SYM_DEMONS_STELLA_WRAPPEDNEWVALUE, NIL), listO(3, SYM_DEMONS_STELLA_FREE, SYM_DEMONS_STELLA_WRAPPEDNEWVALUE, NIL), NIL), listO(3, SYM_DEMONS_STELLA_RETURN, SYM_DEMONS_STELLA_VALUE, NIL), NIL), listO(3, SYM_DEMONS_STELLA_RETURN, SYM_DEMONS_STELLA_OLDVALUE, NIL), NIL), listO(3, SYM_DEMONS_STELLA_RETURN, listO(4, SYM_DEMONS_STELLA_SETF, listO(4, SYM_DEMONS_STELLA_SLOT_VALUE, SYM_DEMONS_STELLA_SELF, slotname, NIL), SYM_DEMONS_STELLA_VALUE, NIL), NIL), NIL), NIL), NIL));
    }
    else {
      return (listO(5, SYM_DEMONS_STELLA_LET, listO(3, listO(3, SYM_DEMONS_STELLA_SLOT, listO(4, SYM_DEMONS_STELLA_GET_SLOT, SYM_DEMONS_STELLA_SELF, listO(3, SYM_DEMONS_STELLA_BQUOTE, slotname, NIL), NIL), NIL), listO(3, SYM_DEMONS_STELLA_OLDVALUE, listO(4, SYM_DEMONS_STELLA_SLOT_VALUE, SYM_DEMONS_STELLA_SELF, slotname, NIL), NIL), NIL), listO(6, SYM_DEMONS_STELLA_WHEN, listO(4, SYM_DEMONS_STELLA_AND, listO(3, SYM_DEMONS_STELLA_NOT, listO(4, SYM_DEMONS_STELLA_EQp, SYM_DEMONS_STELLA_OLDVALUE, SYM_DEMONS_STELLA_VALUE, NIL), NIL), listO(6, SYM_DEMONS_STELLA_RUN_SLOT_GUARD_DEMONSp, SYM_DEMONS_STELLA_SELF, SYM_DEMONS_STELLA_SLOT, SYM_DEMONS_STELLA_OLDVALUE, SYM_DEMONS_STELLA_VALUE, NIL), NIL), listO(4, SYM_DEMONS_STELLA_SETF, listO(4, SYM_DEMONS_STELLA_SLOT_VALUE, SYM_DEMONS_STELLA_SELF, slotname, NIL), SYM_DEMONS_STELLA_VALUE, NIL), listO(6, SYM_DEMONS_STELLA_RUN_SLOT_DEMONS, SYM_DEMONS_STELLA_SELF, SYM_DEMONS_STELLA_SLOT, SYM_DEMONS_STELLA_OLDVALUE, SYM_DEMONS_STELLA_VALUE, NIL), listO(3, SYM_DEMONS_STELLA_RETURN, SYM_DEMONS_STELLA_VALUE, NIL), NIL), listO(3, SYM_DEMONS_STELLA_RETURN, SYM_DEMONS_STELLA_OLDVALUE, NIL), NIL));
    }
  }
}

void ActiveList::insert(Object* value) {
  { ActiveList* self = this;

    { StorageSlot* slot = self->activeSlot;
      StandardObject* owner = self->ownerInstance;

      if (runSlotGuardDemonsP(owner, slot, self, value)) {
        self->theConsList = cons(value, self->theConsList);
        runSlotDemons(owner, slot, NULL, value);
      }
    }
  }
}

void ActiveSet::insert(Object* value) {
  { ActiveSet* self = this;

    { StorageSlot* slot = self->activeSlot;
      StandardObject* owner = self->ownerInstance;

      if (!(self->theConsList->memberP(value))) {
        if (runSlotGuardDemonsP(owner, slot, self, value)) {
          self->theConsList = cons(value, self->theConsList);
          runSlotDemons(owner, slot, NULL, value);
        }
      }
    }
  }
}

AbstractCollection* ActiveList::remove(Object* value) {
  { ActiveList* self = this;

    { StorageSlot* slot = self->activeSlot;
      StandardObject* owner = self->ownerInstance;

      if (self->theConsList->memberP(value)) {
        if (runSlotGuardDemonsP(owner, slot, value, NULL)) {
          self->theConsList = self->theConsList->remove(value);
          runSlotDemons(owner, slot, value, NULL);
        }
      }
      return (self);
    }
  }
}

AbstractCollection* ActiveSet::remove(Object* value) {
  { ActiveSet* self = this;

    { StorageSlot* slot = self->activeSlot;
      StandardObject* owner = self->ownerInstance;

      if (self->theConsList->memberP(value)) {
        if (runSlotGuardDemonsP(owner, slot, value, NULL)) {
          self->theConsList = self->theConsList->remove(value);
          runSlotDemons(owner, slot, value, NULL);
        }
      }
      return (self);
    }
  }
}

HookList* newHookList() {
  { HookList* self = NULL;

    self = new HookList();
    self->theKvList = NULL;
    self->documentation = NULL;
    self->signature = NULL;
    return (self);
  }
}

Surrogate* HookList::primaryType() {
  { HookList* self = this;

    return (SGT_DEMONS_STELLA_HOOK_LIST);
  }
}

Object* accessHookListSlotValue(HookList* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_DEMONS_STELLA_SIGNATURE) {
    if (setvalueP) {
      self->signature = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->signature);
    }
  }
  else if (slotname == SYM_DEMONS_STELLA_DOCUMENTATION) {
    if (setvalueP) {
      self->documentation = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->documentation);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

void addHook(HookList* hooklist, Symbol* hookfunction) {
  // Insert the function named `hookFunction' into `hookList'.
  { MethodSlot* function = lookupFunction(hookfunction);

    if (!((boolean)(function))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Reference to non-existent hook function: `hookFunction'." << std::endl;
      return;
    }
    hooklist->insertAt(hookfunction, wrapFunctionCode(function->functionCode));
  }
}

void dropHook(HookList* hooklist, Symbol* hookfunction) {
  // Remove the function named `hookFunction' from `hookList'.
  hooklist->removeAt(hookfunction);
}

void runHooks(HookList* hooklist, Object* argument) {
  // Run all hook functions in `hooklist', applying
  // each one to `argument'.
  { KvListIterator* it = ((KvListIterator*)(hooklist->allocateIterator()));

    for (; it->nextP(); ) {
      ((void  (*) (Object*))((FunctionCodeWrapper*)(((FunctionCodeWrapper*)(it->value))))->wrapperValue)(argument);
    }
  }
}

// HOOK-LIST called by `in-module', applied to a
// `module' argument.
HookList* oCHANGE_MODULE_HOOKSo = NULL;

// HOOK-LIST called by `clear-module', applied to a
// `module' argument.
HookList* oCLEAR_MODULE_HOOKSo = NULL;

// HOOK-LIST called by `clear-module', applied to a
// `module' argument.
HookList* oDESTROY_CONTEXT_HOOKSo = NULL;

// HOOK-LIST is called by `undefine-old-class'.  Each
// hook function is passed a LIST of two RELATION objects; the first is the
// old relation object and the second is the new (redefined) relation object.
// The hook functions are expected to copy/transfer information from the
// old relation to the new relation so that it won't be lost.
HookList* oREDEFINE_RELATION_HOOKSo = NULL;

// HOOK-LIST is called by `finalize-one-class'
// and `finalize-local-slot', applied to a RELATION argument.
HookList* oFINALIZE_RELATION_HOOKSo = NULL;

// HOOK-LIST called by `create-native-class', applied to
// a STELLA class.  Return value of TRUE blocks creation.
HookList* oBLOCK_NATIVE_CLASS_CREATION_HOOKSo = NULL;

// HOOK-LIST of cleanup functions to be called upon exit from
// the STELLA application or any point where such cleanup is required.  The
// functions on this list should be highly tolerant of their invocation environment
// and not assume any special state; that is, they should be no-ops if no special
// cleanup is required.
HookList* oSTELLA_EXIT_HOOKSo = NULL;

void helpStartupDemons1() {
  {
    KWD_DEMONS_MODIFY = ((Keyword*)(internRigidSymbolWrtModule("MODIFY", NULL, 2)));
    KWD_DEMONS_CREATE = ((Keyword*)(internRigidSymbolWrtModule("CREATE", NULL, 2)));
    KWD_DEMONS_DESTROY = ((Keyword*)(internRigidSymbolWrtModule("DESTROY", NULL, 2)));
    KWD_DEMONS_ALL = ((Keyword*)(internRigidSymbolWrtModule("ALL", NULL, 2)));
    KWD_DEMONS_CLASS = ((Keyword*)(internRigidSymbolWrtModule("CLASS", NULL, 2)));
    KWD_DEMONS_SLOT = ((Keyword*)(internRigidSymbolWrtModule("SLOT", NULL, 2)));
    KWD_DEMONS_CODE = ((Keyword*)(internRigidSymbolWrtModule("CODE", NULL, 2)));
    KWD_DEMONS_METHOD = ((Keyword*)(internRigidSymbolWrtModule("METHOD", NULL, 2)));
    KWD_DEMONS_GUARDp = ((Keyword*)(internRigidSymbolWrtModule("GUARD?", NULL, 2)));
    KWD_DEMONS_INHERITEDp = ((Keyword*)(internRigidSymbolWrtModule("INHERITED?", NULL, 2)));
    KWD_DEMONS_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
    KWD_DEMONS_ACTIVATEp = ((Keyword*)(internRigidSymbolWrtModule("ACTIVATE?", NULL, 2)));
    SYM_DEMONS_STELLA_SLOT_GUARD_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("SLOT-GUARD-DEMONS", NULL, 0)));
    SYM_DEMONS_STELLA_SLOT_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("SLOT-DEMONS", NULL, 0)));
    SYM_DEMONS_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-GUARD-CONSTRUCTOR-DEMONS", NULL, 0)));
    SYM_DEMONS_STELLA_CLASS_CONSTRUCTOR_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CONSTRUCTOR-DEMONS", NULL, 0)));
    SYM_DEMONS_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-GUARD-DESTRUCTOR-DEMONS", NULL, 0)));
    SYM_DEMONS_STELLA_CLASS_DESTRUCTOR_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("CLASS-DESTRUCTOR-DEMONS", NULL, 0)));
    SYM_DEMONS_STELLA_WRAP_LITERAL = ((Symbol*)(internRigidSymbolWrtModule("WRAP-LITERAL", NULL, 0)));
    SYM_DEMONS_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    SYM_DEMONS_STELLA_WRAP_BOOLEAN = ((Symbol*)(internRigidSymbolWrtModule("WRAP-BOOLEAN", NULL, 0)));
    SYM_DEMONS_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    SYM_DEMONS_STELLA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("PROGN", NULL, 0)));
    SYM_DEMONS_STELLA_DEFUN = ((Symbol*)(internRigidSymbolWrtModule("DEFUN", NULL, 0)));
    SYM_DEMONS_STELLA_STARTUP_TIME_PROGN = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-TIME-PROGN", NULL, 0)));
    SYM_DEMONS_STELLA_DEFINE_DEMON = ((Symbol*)(internRigidSymbolWrtModule("DEFINE-DEMON", NULL, 0)));
    SYM_DEMONS_STELLA_THE_CODE = ((Symbol*)(internRigidSymbolWrtModule("THE-CODE", NULL, 0)));
    KWD_DEMONS_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SGT_DEMONS_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
    SGT_DEMONS_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 1)));
    SGT_DEMONS_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", NULL, 1)));
    SGT_DEMONS_STELLA_LONG_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("LONG-INTEGER", NULL, 1)));
    SGT_DEMONS_STELLA_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT", NULL, 1)));
    SGT_DEMONS_STELLA_STRING = ((Surrogate*)(internRigidSymbolWrtModule("STRING", NULL, 1)));
    SGT_DEMONS_STELLA_MUTABLE_STRING = ((Surrogate*)(internRigidSymbolWrtModule("MUTABLE-STRING", NULL, 1)));
    SGT_DEMONS_STELLA_CHARACTER = ((Surrogate*)(internRigidSymbolWrtModule("CHARACTER", NULL, 1)));
    SGT_DEMONS_STELLA_FUNCTION_CODE = ((Surrogate*)(internRigidSymbolWrtModule("FUNCTION-CODE", NULL, 1)));
    SGT_DEMONS_STELLA_METHOD_CODE = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-CODE", NULL, 1)));
    SGT_DEMONS_STELLA_MUTABLE_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("MUTABLE-STRING-WRAPPER", NULL, 1)));
    SGT_DEMONS_STELLA_FUNCTION_CODE_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("FUNCTION-CODE-WRAPPER", NULL, 1)));
    SGT_DEMONS_STELLA_METHOD_CODE_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-CODE-WRAPPER", NULL, 1)));
    SYM_DEMONS_STELLA_LET = ((Symbol*)(internRigidSymbolWrtModule("LET", NULL, 0)));
    SYM_DEMONS_STELLA_VALUE = ((Symbol*)(internRigidSymbolWrtModule("VALUE", NULL, 0)));
    SYM_DEMONS_STELLA_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SLOT-VALUE", NULL, 0)));
    SYM_DEMONS_STELLA_SELF = ((Symbol*)(internRigidSymbolWrtModule("SELF", NULL, 0)));
    SYM_DEMONS_STELLA_WHEN = ((Symbol*)(internRigidSymbolWrtModule("WHEN", NULL, 0)));
    SYM_DEMONS_STELLA_DEFINEDp = ((Symbol*)(internRigidSymbolWrtModule("DEFINED?", NULL, 0)));
    SYM_DEMONS_STELLA_RETURN = ((Symbol*)(internRigidSymbolWrtModule("RETURN", NULL, 0)));
    SYM_DEMONS_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", NULL, 0)));
    SYM_DEMONS_STELLA_NEW = ((Symbol*)(internRigidSymbolWrtModule("NEW", NULL, 0)));
    SYM_DEMONS_STELLA_SETF = ((Symbol*)(internRigidSymbolWrtModule("SETF", NULL, 0)));
    SYM_DEMONS_STELLA_OWNER_INSTANCE = ((Symbol*)(internRigidSymbolWrtModule("OWNER-INSTANCE", NULL, 0)));
    SYM_DEMONS_STELLA_ACTIVE_SLOT = ((Symbol*)(internRigidSymbolWrtModule("ACTIVE-SLOT", NULL, 0)));
    SYM_DEMONS_STELLA_GET_SLOT = ((Symbol*)(internRigidSymbolWrtModule("GET-SLOT", NULL, 0)));
    SYM_DEMONS_STELLA_BQUOTE = ((Symbol*)(internRigidSymbolWrtModule("BQUOTE", NULL, 0)));
    SYM_DEMONS_STELLA_CANT_OVERWRITE_ACTIVE_COLLECTION_SLOT = ((Symbol*)(internRigidSymbolWrtModule("CANT-OVERWRITE-ACTIVE-COLLECTION-SLOT", NULL, 0)));
    SGT_DEMONS_STELLA_LITERAL = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL", NULL, 1)));
    SYM_DEMONS_STELLA_SLOT = ((Symbol*)(internRigidSymbolWrtModule("SLOT", NULL, 0)));
    SYM_DEMONS_STELLA_OLDVALUE = ((Symbol*)(internRigidSymbolWrtModule("OLDVALUE", NULL, 0)));
    SYM_DEMONS_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", NULL, 0)));
  }
}

void helpStartupDemons2() {
  {
    SYM_DEMONS_STELLA_EQLp = ((Symbol*)(internRigidSymbolWrtModule("EQL?", NULL, 0)));
    SYM_DEMONS_STELLA_IF = ((Symbol*)(internRigidSymbolWrtModule("IF", NULL, 0)));
    SYM_DEMONS_STELLA_CHECK_FOR_SLOT_DEMONSp = ((Symbol*)(internRigidSymbolWrtModule("CHECK-FOR-SLOT-DEMONS?", NULL, 0)));
    SYM_DEMONS_STELLA_WRAPPEDOLDVALUE = ((Symbol*)(internRigidSymbolWrtModule("WRAPPEDOLDVALUE", NULL, 0)));
    SYM_DEMONS_STELLA_CHOOSE = ((Symbol*)(internRigidSymbolWrtModule("CHOOSE", NULL, 0)));
    SYM_DEMONS_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    SYM_DEMONS_STELLA_WRAPPEDNEWVALUE = ((Symbol*)(internRigidSymbolWrtModule("WRAPPEDNEWVALUE", NULL, 0)));
    SYM_DEMONS_STELLA_RUN_SLOT_GUARD_DEMONSp = ((Symbol*)(internRigidSymbolWrtModule("RUN-SLOT-GUARD-DEMONS?", NULL, 0)));
    SYM_DEMONS_STELLA_RUN_SLOT_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("RUN-SLOT-DEMONS", NULL, 0)));
    SYM_DEMONS_STELLA_FREE = ((Symbol*)(internRigidSymbolWrtModule("FREE", NULL, 0)));
    SYM_DEMONS_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", NULL, 0)));
    SYM_DEMONS_STELLA_EQp = ((Symbol*)(internRigidSymbolWrtModule("EQ?", NULL, 0)));
    SGT_DEMONS_STELLA_HOOK_LIST = ((Surrogate*)(internRigidSymbolWrtModule("HOOK-LIST", NULL, 1)));
    SYM_DEMONS_STELLA_SIGNATURE = ((Symbol*)(internRigidSymbolWrtModule("SIGNATURE", NULL, 0)));
    SYM_DEMONS_STELLA_DOCUMENTATION = ((Symbol*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 0)));
    SYM_DEMONS_STELLA_STARTUP_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-DEMONS", NULL, 0)));
    SYM_DEMONS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void startupDemons() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupDemons1();
      helpStartupDemons2();
    }
    if (currentStartupTimePhaseP(4)) {
      oDEMONS_TABLEo = newStringHashTable();
      oCHANGE_MODULE_HOOKSo = newHookList();
      oCLEAR_MODULE_HOOKSo = newHookList();
      oDESTROY_CONTEXT_HOOKSo = newHookList();
      oREDEFINE_RELATION_HOOKSo = newHookList();
      oFINALIZE_RELATION_HOOKSo = newHookList();
      oBLOCK_NATIVE_CLASS_CREATION_HOOKSo = newHookList();
      oSTELLA_EXIT_HOOKSo = newHookList();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("HOOK-LIST", "(DEFCLASS HOOK-LIST (KEY-VALUE-LIST) :DOCUMENTATION \"Each HOOK-LIST object contains a list of zero or\nmore function codes that get funcall'd some procedure.\" :PARAMETERS ((ANY-KEY :TYPE SYMBOL) (ANY-VALUE :TYPE FUNCTION-CODE-WRAPPER)) :SLOTS ((SIGNATURE :TYPE STRING) (DOCUMENTATION :TYPE STRING)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newHookList));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessHookListSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("VALIDATE-DEMON-REFERENCES?", "(DEFUN (VALIDATE-DEMON-REFERENCES? BOOLEAN) ((DEMON DEMON)))", ((cpp_function_code)(&validateDemonReferencesP)), NULL);
      defineFunctionObject("INCORPORATE-DEMON-OPTIONS?", "(DEFUN (INCORPORATE-DEMON-OPTIONS? BOOLEAN) ((DEMON DEMON) (OPTIONS PROPERTY-LIST)))", ((cpp_function_code)(&incorporateDemonOptionsP)), NULL);
      defineFunctionObject("LOOKUP-DEMON", "(DEFUN (LOOKUP-DEMON DEMON) ((NAME STRING)) :DOCUMENTATION \"Return the demon named `name'.\")", ((cpp_function_code)(&lookupDemon)), NULL);
      defineFunctionObject("DEFINE-DEMON", "(DEFUN (DEFINE-DEMON DEMON) ((NAME STRING) |&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Define a class or slot demon.  Options are :create,\n:destroy, :class, :slot, :guard?, :code, :method, :inherit?, and :documentation.\")", ((cpp_function_code)(&defineDemon)), NULL);
      defineFunctionObject("INJECT-DEMON", "(DEFUN (INJECT-DEMON (LIST OF DEMON)) ((DEMONLIST (LIST OF DEMON)) (DEMON DEMON)))", ((cpp_function_code)(&injectDemon)), NULL);
      defineFunctionObject("EJECT-DEMON", "(DEFUN (EJECT-DEMON (LIST OF DEMON)) ((DEMONLIST (LIST OF DEMON)) (DEMON DEMON)))", ((cpp_function_code)(&ejectDemon)), NULL);
      defineFunctionObject("ACTIVATE-DEMON", "(DEFUN ACTIVATE-DEMON ((DEMON DEMON)) :DOCUMENTATION \"Install `demon' in the location(s) specified by its internal\nstructure.\")", ((cpp_function_code)(&activateDemon)), NULL);
      defineFunctionObject("DEACTIVATE-DEMON", "(DEFUN DEACTIVATE-DEMON ((DEMON DEMON)) :DOCUMENTATION \"Detach `demon' from the location(s) specified by its internal\nstructure.\")", ((cpp_function_code)(&deactivateDemon)), NULL);
      defineFunctionObject("DESTRUCTURE-DEFDEMON-BODY", "(DEFUN (DESTRUCTURE-DEFDEMON-BODY CONS CONS) ((DEMONTREE CONS)))", ((cpp_function_code)(&destructureDefdemonBody)), NULL);
      defineFunctionObject("IN-PLACE-NORMALIZE-DEMON-OPTIONS", "(DEFUN IN-PLACE-NORMALIZE-DEMON-OPTIONS ((OPTIONSTREE CONS)))", ((cpp_function_code)(&inPlaceNormalizeDemonOptions)), NULL);
      defineFunctionObject("DEFDEMON", "(DEFUN DEFDEMON ((NAME STRING-WRAPPER) (PARAMETERSTREE CONS) |&BODY| (OPTIONSANDBODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Define a demon `name' and attach it to a class or slot.\" :PUBLIC? TRUE :LISP-MACRO? TRUE)", ((cpp_function_code)(&defdemon)), NULL);
      defineFunctionObject("READ-SLOT-VALUE", "(DEFUN (READ-SLOT-VALUE OBJECT) ((SELF STANDARD-OBJECT) (SLOT STORAGE-SLOT)) :DOCUMENTATION \"Read and return a (possibly wrapped) value for the slot `slot' on `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&readSlotValue)), NULL);
      defineFunctionObject("WRITE-SLOT-VALUE", "(DEFUN (WRITE-SLOT-VALUE OBJECT) ((SELF STANDARD-OBJECT) (SLOT STORAGE-SLOT) (VALUE OBJECT)) :DOCUMENTATION \"Write a (possibly wrapped) `value' for the slot `slot' on `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&writeSlotValue)), NULL);
      defineFunctionObject("PUT-SLOT-VALUE", "(DEFUN (PUT-SLOT-VALUE OBJECT) ((SELF STANDARD-OBJECT) (SLOT STORAGE-SLOT) (VALUE OBJECT)) :DOCUMENTATION \"Set or insert `value' for the slot `slot' on `self'.\nCAUTION: Assumes that collection-valued slots are non-null.\" :PUBLIC? TRUE)", ((cpp_function_code)(&putSlotValue)), NULL);
      defineFunctionObject("DROP-SLOT-VALUE", "(DEFUN DROP-SLOT-VALUE ((SELF STANDARD-OBJECT) (SLOT STORAGE-SLOT) (VALUE OBJECT)) :DOCUMENTATION \"Clear or remove `value' for the slot `slot' on `self'.\nCAUTION: Assumes that collection-valued slots are non-null.\" :PUBLIC? TRUE)", ((cpp_function_code)(&dropSlotValue)), NULL);
      defineFunctionObject("CPP-FIND-NATIVE-SLOT-VALUE-OFFSET", "(DEFUN (CPP-FIND-NATIVE-SLOT-VALUE-OFFSET INTEGER) ((SELF STANDARD-OBJECT) (SLOT STORAGE-SLOT)) :DOCUMENTATION \"Dynamically determine the byte offset where the native value for `slot' starts in `self'.\nThis basically performs the function of the C++ macro `offsetof' but does it dynamically.  Of course, it\nrelies on a working `read/write-slot-value' mechanism and we currently primarily use this for the Python API.\nThis basically writes value changes of `slot' to determine a byte position where a change occurred and\nthen restores the original value (which can be NULL).  This handles all native OBJECT and LITERAL slots\nbut does not handle special slots such as `dynamic-slots' or hardwired slots or other non-standard types.\" :PUBLIC? TRUE)", ((cpp_function_code)(&cppFindNativeSlotValueOffset)), NULL);
      defineFunctionObject("CHECK-FOR-SLOT-DEMONS?", "(DEFUN (CHECK-FOR-SLOT-DEMONS? BOOLEAN) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&checkForSlotDemonsP)), NULL);
      defineFunctionObject("RUN-SLOT-GUARD-DEMONS?", "(DEFUN (RUN-SLOT-GUARD-DEMONS? BOOLEAN) ((SELF STANDARD-OBJECT) (SLOT STORAGE-SLOT) (OLDVALUE OBJECT) (NEWVALUE OBJECT)))", ((cpp_function_code)(&runSlotGuardDemonsP)), NULL);
      defineFunctionObject("RUN-SLOT-DEMONS", "(DEFUN RUN-SLOT-DEMONS ((SELF STANDARD-OBJECT) (SLOT STORAGE-SLOT) (OLDVALUE OBJECT) (NEWVALUE OBJECT)))", ((cpp_function_code)(&runSlotDemons)), NULL);
      defineFunctionObject("RUN-CONSTRUCTOR-DEMONS", "(DEFUN RUN-CONSTRUCTOR-DEMONS ((SELF STANDARD-OBJECT)))", ((cpp_function_code)(&runConstructorDemons)), NULL);
      defineFunctionObject("RUN-DESTRUCTOR-DEMONS", "(DEFUN RUN-DESTRUCTOR-DEMONS ((SELF STANDARD-OBJECT)))", ((cpp_function_code)(&runDestructorDemons)), NULL);
      defineFunctionObject("YIELD-ACTIVE-SLOT-READER-BODY", "(DEFUN (YIELD-ACTIVE-SLOT-READER-BODY CONS) ((SLOT STORAGE-SLOT) (DEFAULTEXPRESSION OBJECT)))", ((cpp_function_code)(&yieldActiveSlotReaderBody)), NULL);
      defineFunctionObject("CANT-OVERWRITE-ACTIVE-COLLECTION-SLOT", "(DEFUN CANT-OVERWRITE-ACTIVE-COLLECTION-SLOT ((SELF STANDARD-OBJECT) (SLOTNAME SYMBOL)))", ((cpp_function_code)(&cantOverwriteActiveCollectionSlot)), NULL);
      defineFunctionObject("YIELD-ACTIVE-SLOT-WRITER-BODY", "(DEFUN (YIELD-ACTIVE-SLOT-WRITER-BODY CONS) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&yieldActiveSlotWriterBody)), NULL);
      defineMethodObject("(DEFMETHOD INSERT ((SELF ACTIVE-LIST) (VALUE (LIKE (ANY-VALUE SELF)))))", wrapMethodCode(((cpp_method_code)(&ActiveList::insert))), NULL);
      defineMethodObject("(DEFMETHOD INSERT ((SELF ACTIVE-SET) (VALUE (LIKE (ANY-VALUE SELF)))))", wrapMethodCode(((cpp_method_code)(&ActiveSet::insert))), NULL);
      defineMethodObject("(DEFMETHOD (REMOVE ACTIVE-LIST) ((SELF ACTIVE-LIST) (VALUE (LIKE (ANY-VALUE SELF)))))", wrapMethodCode(((cpp_method_code)(&ActiveList::remove))), NULL);
      defineMethodObject("(DEFMETHOD (REMOVE ACTIVE-SET) ((SELF ACTIVE-SET) (VALUE (LIKE (ANY-VALUE SELF)))))", wrapMethodCode(((cpp_method_code)(&ActiveSet::remove))), NULL);
      defineFunctionObject("ADD-HOOK", "(DEFUN ADD-HOOK ((HOOKLIST HOOK-LIST) (HOOKFUNCTION SYMBOL)) :PUBLIC? TRUE :DOCUMENTATION \"Insert the function named `hookFunction' into `hookList'.\")", ((cpp_function_code)(&addHook)), NULL);
      defineFunctionObject("DROP-HOOK", "(DEFUN DROP-HOOK ((HOOKLIST HOOK-LIST) (HOOKFUNCTION SYMBOL)) :PUBLIC? TRUE :DOCUMENTATION \"Remove the function named `hookFunction' from `hookList'.\")", ((cpp_function_code)(&dropHook)), NULL);
      defineFunctionObject("RUN-HOOKS", "(DEFUN RUN-HOOKS ((HOOKLIST HOOK-LIST) (ARGUMENT OBJECT)) :DOCUMENTATION \"Run all hook functions in `hooklist', applying\neach one to `argument'.\")", ((cpp_function_code)(&runHooks)), NULL);
      defineFunctionObject("STARTUP-DEMONS", "(DEFUN STARTUP-DEMONS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupDemons)), NULL);
      { MethodSlot* function = lookupFunction(SYM_DEMONS_STELLA_STARTUP_DEMONS);

        setDynamicSlotValue(function->dynamicSlots, SYM_DEMONS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupDemons"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL *DEMONS-TABLE* STRING-HASH-TABLE (NEW STRING-HASH-TABLE) :DOCUMENTATION \"Table containing all active and inactive demons, indexed\non their names.\")", &oDEMONS_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *CONSTRUCTOR-DEMONS* (LIST OF DEMON) NULL :DOCUMENTATION \"These demons trigger every time an active instance is created.\")", &oCONSTRUCTOR_DEMONSo);
      defineGlobalVariableObject("(DEFGLOBAL *DESTRUCTOR-DEMONS* (LIST OF DEMON) NULL :DOCUMENTATION \"These demons trigger every time an active instance is destroyed.\")", &oDESTRUCTOR_DEMONSo);
      defineGlobalVariableObject("(DEFGLOBAL *ALL-SLOTS-DEMONS* (LIST OF DEMON) NULL :DOCUMENTATION \"These demons trigger every time a slot value is modified.\")", &oALL_SLOTS_DEMONSo);
      defineGlobalVariableObject("(DEFGLOBAL *ALL-SLOTS-GUARD-DEMONS* (LIST OF DEMON) NULL :DOCUMENTATION \"These demons trigger every time a slot value is modified, and\ncancel slot update when they return `false'.\")", &oALL_SLOTS_GUARD_DEMONSo);
      defineGlobalVariableObject("(DEFGLOBAL *CHANGE-MODULE-HOOKS* HOOK-LIST (NEW HOOK-LIST) :DOCUMENTATION \"HOOK-LIST called by `in-module', applied to a\n`module' argument.\")", &oCHANGE_MODULE_HOOKSo);
      defineGlobalVariableObject("(DEFGLOBAL *CLEAR-MODULE-HOOKS* HOOK-LIST (NEW HOOK-LIST) :DOCUMENTATION \"HOOK-LIST called by `clear-module', applied to a\n`module' argument.\")", &oCLEAR_MODULE_HOOKSo);
      defineGlobalVariableObject("(DEFGLOBAL *DESTROY-CONTEXT-HOOKS* HOOK-LIST (NEW HOOK-LIST) :DOCUMENTATION \"HOOK-LIST called by `clear-module', applied to a\n`module' argument.\")", &oDESTROY_CONTEXT_HOOKSo);
      defineGlobalVariableObject("(DEFGLOBAL *REDEFINE-RELATION-HOOKS* HOOK-LIST (NEW HOOK-LIST) :DOCUMENTATION \"HOOK-LIST is called by `undefine-old-class'.  Each\nhook function is passed a LIST of two RELATION objects; the first is the\nold relation object and the second is the new (redefined) relation object.\nThe hook functions are expected to copy/transfer information from the\nold relation to the new relation so that it won't be lost.\")", &oREDEFINE_RELATION_HOOKSo);
      defineGlobalVariableObject("(DEFGLOBAL *FINALIZE-RELATION-HOOKS* HOOK-LIST (NEW HOOK-LIST) :DOCUMENTATION \"HOOK-LIST is called by `finalize-one-class'\nand `finalize-local-slot', applied to a RELATION argument.\")", &oFINALIZE_RELATION_HOOKSo);
      defineGlobalVariableObject("(DEFGLOBAL *BLOCK-NATIVE-CLASS-CREATION-HOOKS* HOOK-LIST (NEW HOOK-LIST) :DOCUMENTATION \"HOOK-LIST called by `create-native-class', applied to\na STELLA class.  Return value of TRUE blocks creation.\")", &oBLOCK_NATIVE_CLASS_CREATION_HOOKSo);
      defineGlobalVariableObject("(DEFGLOBAL *STELLA-EXIT-HOOKS* HOOK-LIST (NEW HOOK-LIST) :DOCUMENTATION \"HOOK-LIST of cleanup functions to be called upon exit from\nthe STELLA application or any point where such cleanup is required.  The\nfunctions on this list should be highly tolerant of their invocation environment\nand not assume any special state; that is, they should be no-ops if no special\ncleanup is required.\")", &oSTELLA_EXIT_HOOKSo);
    }
  }
}

Keyword* KWD_DEMONS_MODIFY = NULL;

Keyword* KWD_DEMONS_CREATE = NULL;

Keyword* KWD_DEMONS_DESTROY = NULL;

Keyword* KWD_DEMONS_ALL = NULL;

Keyword* KWD_DEMONS_CLASS = NULL;

Keyword* KWD_DEMONS_SLOT = NULL;

Keyword* KWD_DEMONS_CODE = NULL;

Keyword* KWD_DEMONS_METHOD = NULL;

Keyword* KWD_DEMONS_GUARDp = NULL;

Keyword* KWD_DEMONS_INHERITEDp = NULL;

Keyword* KWD_DEMONS_DOCUMENTATION = NULL;

Keyword* KWD_DEMONS_ACTIVATEp = NULL;

Symbol* SYM_DEMONS_STELLA_SLOT_GUARD_DEMONS = NULL;

Symbol* SYM_DEMONS_STELLA_SLOT_DEMONS = NULL;

Symbol* SYM_DEMONS_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS = NULL;

Symbol* SYM_DEMONS_STELLA_CLASS_CONSTRUCTOR_DEMONS = NULL;

Symbol* SYM_DEMONS_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS = NULL;

Symbol* SYM_DEMONS_STELLA_CLASS_DESTRUCTOR_DEMONS = NULL;

Symbol* SYM_DEMONS_STELLA_WRAP_LITERAL = NULL;

Symbol* SYM_DEMONS_STELLA_TRUE = NULL;

Symbol* SYM_DEMONS_STELLA_WRAP_BOOLEAN = NULL;

Symbol* SYM_DEMONS_STELLA_FALSE = NULL;

Symbol* SYM_DEMONS_STELLA_PROGN = NULL;

Symbol* SYM_DEMONS_STELLA_DEFUN = NULL;

Symbol* SYM_DEMONS_STELLA_STARTUP_TIME_PROGN = NULL;

Symbol* SYM_DEMONS_STELLA_DEFINE_DEMON = NULL;

Symbol* SYM_DEMONS_STELLA_THE_CODE = NULL;

Keyword* KWD_DEMONS_FUNCTION = NULL;

Surrogate* SGT_DEMONS_STELLA_OBJECT = NULL;

Surrogate* SGT_DEMONS_STELLA_BOOLEAN = NULL;

Surrogate* SGT_DEMONS_STELLA_INTEGER = NULL;

Surrogate* SGT_DEMONS_STELLA_LONG_INTEGER = NULL;

Surrogate* SGT_DEMONS_STELLA_FLOAT = NULL;

Surrogate* SGT_DEMONS_STELLA_STRING = NULL;

Surrogate* SGT_DEMONS_STELLA_MUTABLE_STRING = NULL;

Surrogate* SGT_DEMONS_STELLA_CHARACTER = NULL;

Surrogate* SGT_DEMONS_STELLA_FUNCTION_CODE = NULL;

Surrogate* SGT_DEMONS_STELLA_METHOD_CODE = NULL;

Surrogate* SGT_DEMONS_STELLA_MUTABLE_STRING_WRAPPER = NULL;

Surrogate* SGT_DEMONS_STELLA_FUNCTION_CODE_WRAPPER = NULL;

Surrogate* SGT_DEMONS_STELLA_METHOD_CODE_WRAPPER = NULL;

Symbol* SYM_DEMONS_STELLA_LET = NULL;

Symbol* SYM_DEMONS_STELLA_VALUE = NULL;

Symbol* SYM_DEMONS_STELLA_SLOT_VALUE = NULL;

Symbol* SYM_DEMONS_STELLA_SELF = NULL;

Symbol* SYM_DEMONS_STELLA_WHEN = NULL;

Symbol* SYM_DEMONS_STELLA_DEFINEDp = NULL;

Symbol* SYM_DEMONS_STELLA_RETURN = NULL;

Symbol* SYM_DEMONS_STELLA_SETQ = NULL;

Symbol* SYM_DEMONS_STELLA_NEW = NULL;

Symbol* SYM_DEMONS_STELLA_SETF = NULL;

Symbol* SYM_DEMONS_STELLA_OWNER_INSTANCE = NULL;

Symbol* SYM_DEMONS_STELLA_ACTIVE_SLOT = NULL;

Symbol* SYM_DEMONS_STELLA_GET_SLOT = NULL;

Symbol* SYM_DEMONS_STELLA_BQUOTE = NULL;

Symbol* SYM_DEMONS_STELLA_CANT_OVERWRITE_ACTIVE_COLLECTION_SLOT = NULL;

Surrogate* SGT_DEMONS_STELLA_LITERAL = NULL;

Symbol* SYM_DEMONS_STELLA_SLOT = NULL;

Symbol* SYM_DEMONS_STELLA_OLDVALUE = NULL;

Symbol* SYM_DEMONS_STELLA_NOT = NULL;

Symbol* SYM_DEMONS_STELLA_EQLp = NULL;

Symbol* SYM_DEMONS_STELLA_IF = NULL;

Symbol* SYM_DEMONS_STELLA_CHECK_FOR_SLOT_DEMONSp = NULL;

Symbol* SYM_DEMONS_STELLA_WRAPPEDOLDVALUE = NULL;

Symbol* SYM_DEMONS_STELLA_CHOOSE = NULL;

Symbol* SYM_DEMONS_STELLA_NULL = NULL;

Symbol* SYM_DEMONS_STELLA_WRAPPEDNEWVALUE = NULL;

Symbol* SYM_DEMONS_STELLA_RUN_SLOT_GUARD_DEMONSp = NULL;

Symbol* SYM_DEMONS_STELLA_RUN_SLOT_DEMONS = NULL;

Symbol* SYM_DEMONS_STELLA_FREE = NULL;

Symbol* SYM_DEMONS_STELLA_AND = NULL;

Symbol* SYM_DEMONS_STELLA_EQp = NULL;

Surrogate* SGT_DEMONS_STELLA_HOOK_LIST = NULL;

Symbol* SYM_DEMONS_STELLA_SIGNATURE = NULL;

Symbol* SYM_DEMONS_STELLA_DOCUMENTATION = NULL;

Symbol* SYM_DEMONS_STELLA_STARTUP_DEMONS = NULL;

Symbol* SYM_DEMONS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
