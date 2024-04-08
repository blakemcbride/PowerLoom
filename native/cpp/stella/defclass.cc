//  -*- Mode: C++ -*-

// defclass.cc

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

Object* typeToNullValueTree(Surrogate* type) {
  { Class* clasS = typeToClass(type);

    if (((boolean)(clasS)) &&
        (subtypeOfP(type, SGT_DEFCLASS_STELLA_LITERAL) ||
         subtypeOfP(type, SGT_DEFCLASS_STELLA_SECOND_CLASS_OBJECT))) {
      { Object* nullvalue = clasS->initialValue();

        if (((boolean)(nullvalue))) {
          return (copyConsTree(nullvalue));
        }
      }
    }
    return (SYM_DEFCLASS_STELLA_NULL);
  }
}

Object* typeToWalkedNullValueTree(StandardObject* typespec, Surrogate* type) {
  { StandardObject* dummy1;
    StandardObject* dummy2;

    { Object* nullvalue = typeToNullValueTree(type);

      if (!(nullvalue == SYM_DEFCLASS_STELLA_NULL)) {
        nullvalue = walkExpressionTree(nullvalue, type, SYM_DEFCLASS_STELLA_NULL, false, dummy1);
      }
      if (arrayTypeSpecifierP(typespec) &&
          (oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_COMMON_LISP)) {
        return (walkExpressionTree(listO(4, SYM_DEFCLASS_STELLA_VERBATIM, KWD_DEFCLASS_COMMON_LISP, wrapString(lispNullArraySymbolString(arrayTypeRank(((ParametricTypeSpecifier*)(typespec))))), NIL), type, SYM_DEFCLASS_STELLA_NULL, false, dummy2));
      }
      else {
        return (nullvalue);
      }
    }
  }
}

Cons* yieldConsListFromSequence(Sequence* sequence) {
  { Cons* list = NIL;

    { Object* item = NULL;
      Iterator* iter000 = ((Iterator*)(sequence->allocateIterator()));
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        item = iter000->value;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(item, NIL);
            if (list == NIL) {
              list = collect000;
            }
            else {
              addConsToEndOfConsList(list, collect000);
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
    }
    return (list);
  }
}

Cons* yieldDefineStellaClass(Class* clasS) {
  // Return a cons tree that (when evaluated) constructs
  // a Stella class object.
  return (listO(3, SYM_DEFCLASS_STELLA_DEFINE_CLASS_FROM_STRINGIFIED_SOURCE, wrapString(clasS->name()), cons(yieldStringConstantTree(clasS->classStringifiedSource), NIL)));
}

boolean createNativeClassP(Class* clasS) {
  { const char* classnativetype = NULL;

    if (oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_COMMON_LISP) {
      classnativetype = ((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_CL_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue;
    }
    else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_IDL) {
      classnativetype = ((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_IDL_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue;
    }
    else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_JAVA) {
      classnativetype = ((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_JAVA_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue;
    }
    else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_CPP) ||
        (oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_CPP_STANDALONE)) {
      classnativetype = ((StringWrapper*)(dynamicSlotValue(clasS->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_CPP_NATIVE_TYPE, NULL_STRING_WRAPPER)))->wrapperValue;
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    return (!(subtypeOfP(clasS->classType, SGT_DEFCLASS_STELLA_SECOND_CLASS_OBJECT) ||
        (subtypeOfP(clasS->classType, SGT_DEFCLASS_STELLA_NON_OBJECT) ||
         ((classnativetype != NULL) ||
          (!clasS->primitiveP())))));
  }
}

boolean exceptionClassP(Class* clasS) {
  return (subtypeOfP(clasS->classType, SGT_DEFCLASS_STELLA_NATIVE_EXCEPTION));
}

void warnAboutMultipleParents(Class* clasS) {
  if (clasS->multipleParentsP() &&
      createNativeClassP(clasS)) {
    if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_CPP_STANDALONE) ||
        (oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_IDL)) {
    }
    else if ((oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_COMMON_LISP) ||
        ((oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_CPP) ||
         (oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_JAVA))) {
      { int nofsupers = 0;
        int nofmixinsupers = 0;

        { Surrogate* super = NULL;
          Cons* iter000 = classNativeSupers(clasS)->theConsList;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            super = ((Surrogate*)(iter000->value));
            nofsupers = nofsupers + 1;
            if (((Class*)(super->surrogateValue))->mixinP) {
              nofmixinsupers = nofmixinsupers + 1;
            }
          }
        }
        if ((nofsupers - nofmixinsupers) > 1) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            signalTranslationError();
            if (!(suppressWarningsP())) {
              printErrorContext(">> ERROR: ", STANDARD_ERROR);
              *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Class " << "`" << className(clasS) << "'" << " illegally inherits " << "`" << (nofsupers - nofmixinsupers) << "'" << " native non-mixin classes" << "." << std::endl;
            }
          }
        }
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

void warnAboutNonDirectSupers(Class* clasS) {
  if (clasS->multipleParentsP() &&
      createNativeClassP(clasS)) {
    { List* directsupers = clasS->classDirectSupers;

      { Surrogate* super = NULL;
        Cons* iter000 = directsupers->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          super = ((Surrogate*)(iter000->value));
          { boolean foundP000 = false;

            { Surrogate* othersuper = NULL;
              Cons* iter001 = directsupers->theConsList;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                othersuper = ((Surrogate*)(iter001->value));
                if ((!(super == othersuper)) &&
                    subtypeOfP(othersuper, super)) {
                  foundP000 = true;
                  break;
                }
              }
            }
            if (foundP000) {
              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                signalTranslationError();
                if (!(suppressWarningsP())) {
                  printErrorContext(">> ERROR: ", STANDARD_ERROR);
                  *(STANDARD_ERROR->nativeStream) << std::endl << " " << "Bad list of supers defined for class " << "`" << className(clasS) << "'" << "." << std::endl << " The class " << "`" << super->symbolName << "'" << " is not a direct superclass" << "." << std::endl;
                }
              }
              return;
            }
          }
        }
      }
    }
  }
}

boolean spaceSaverSlotAllocationP(StorageSlot* slot) {
  if (slot->allocation() == KWD_DEFCLASS_DYNAMIC) {
    if (((boolean)(dynamicSlotValue(slot->dynamicSlots, SYM_DEFCLASS_STELLA_SLOT_INITIAL_VALUE, NULL)))) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Dynamic slot " << "`" << slot->slotName << "'" << " should not have an" << std::endl << "   initial value (or it shouldn't be dynamic)." << std::endl;
    }
    return (true);
  }
  else if ((slot->allocation() == KWD_DEFCLASS_BIT) ||
      ((slot->type() == SGT_DEFCLASS_STELLA_BOOLEAN) &&
       (!((boolean)(slot->slotAllocation_reader()))))) {
    return (true);
  }
  else {
    return (false);
  }
}

boolean dynamicSlotP(StorageSlot* slot) {
  return (slot->allocation() == KWD_DEFCLASS_DYNAMIC);
}

boolean classSlotP(StorageSlot* slot) {
  return (slot->allocation() == KWD_DEFCLASS_CLASS);
}

boolean redundantSlotP(StorageSlot* slot) {
  { Slot* equivslot = slot->slotDirectEquivalent;

    return (((boolean)(equivslot)) &&
        (((Symbol*)(dynamicSlotValue(slot->dynamicSlots, SYM_DEFCLASS_STELLA_SLOT_RENAMES, NULL))) == equivslot->slotName));
  }
}

boolean nativeSlotP(StorageSlot* slot) {
  return ((!slot->abstractP) &&
      ((!slot->slotHardwiredP) &&
       ((!spaceSaverSlotAllocationP(slot)) &&
        (!redundantSlotP(slot)))));
}

boolean parameterSlotP(StorageSlot* slot) {
  { Surrogate* owner = slot->slotOwner;

    return (slot->abstractP &&
        (((boolean)(owner)) &&
         (((boolean)(((Class*)(owner->surrogateValue)))) &&
          ((Class*)(owner->surrogateValue))->parameters()->memberP(slot->slotName))));
  }
}

boolean nativeMethodP(MethodSlot* slot) {
  return ((!slot->abstractP) &&
      (!methodContainsUnknownTypeP(slot)));
}

boolean mixinSlotP(Slot* self) {
  { Surrogate* owner = self->slotOwner;

    return (storageSlotP(self) &&
        (((boolean)(owner)) &&
         (((boolean)(((Class*)(owner->surrogateValue)))) &&
          ((Class*)(owner->surrogateValue))->mixinP)));
  }
}

boolean mixinMethodP(Slot* self) {
  { Surrogate* owner = self->slotOwner;

    return (methodSlotP(self) &&
        ((!((MethodSlot*)(self))->methodFunctionP) &&
         (((boolean)(owner)) &&
          (((boolean)(((Class*)(owner->surrogateValue)))) &&
           ((Class*)(owner->surrogateValue))->mixinP))));
  }
}

StorageSlot* canonicalSlot(StorageSlot* slot) {
  // Computes the slot at the base of a renaming chain for 'slot'.
  { StorageSlot* canonicalslot = slot;

    while (((boolean)(canonicalslot->slotDirectEquivalent)) &&
        (canonicalslot->slotDirectEquivalent->slotName == ((Symbol*)(dynamicSlotValue(canonicalslot->dynamicSlots, SYM_DEFCLASS_STELLA_SLOT_RENAMES, NULL))))) {
      canonicalslot = ((StorageSlot*)(canonicalslot->slotDirectEquivalent));
    }
    return (canonicalslot);
  }
}

Symbol* canonicalSlotName(StorageSlot* slot) {
  // Name of the slot at the base of a renaming chain for 'slot'.
  return (canonicalSlot(slot)->slotName);
}

boolean unknownTypeP(Surrogate* type) {
  return ((type == SGT_DEFCLASS_STELLA_UNKNOWN) ||
      ((!((boolean)(typeToClass(type)))) ||
       ((typeToClass(type) == typeToClass(SGT_DEFCLASS_STELLA_UNKNOWN)) ||
        (subtypeOfP(type, SGT_DEFCLASS_STELLA_NON_OBJECT) &&
         typeToClass(type)->abstractP))));
}

boolean slotHasUnknownTypeP(StorageSlot* slot, Class* clasS) {
  return (unknownTypeP(typeSpecToBaseType(slot->computeReturnTypeSpec(clasS->classType))));
}

Class* nativeStorageSlotHome(StorageSlot* slot, Class* clasS) {
  { StorageSlot* slotwithknowntype = NULL;

    for (;;) {
      if (unknownTypeP(slot->type())) {
        break;
      }
      slotwithknowntype = slot;
      clasS = typeToClass(slot->slotOwner);
      if (((boolean)(slot->slotDirectEquivalent)) &&
          nativeSlotP(((StorageSlot*)(slot->slotDirectEquivalent)))) {
        slot = ((StorageSlot*)(slot->slotDirectEquivalent));
      }
      else {
        break;
      }
    }
    if (((boolean)(slotwithknowntype))) {
      return (clasS);
    }
    if (slotHasUnknownTypeP(slot, clasS)) {
      return (NULL);
    }
    { Class* super = NULL;
      Cons* iter000 = clasS->classAllSuperClasses;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        super = ((Class*)(iter000->value));
        if (slotHasUnknownTypeP(slot, super)) {
          return (clasS);
        }
        else {
          clasS = super;
        }
      }
    }
    return (clasS);
  }
}

Class* nativeSlotHome(Slot* slot, Class* clasS) {
  { Class* nativeslothome = (storageSlotP(slot) ? nativeStorageSlotHome(((StorageSlot*)(slot)), clasS) : ((Class*)(slot->slotOwner->surrogateValue)));
    Class* candidate = clasS;
    Slot* visibleslot = NULL;

    if (!(((boolean)(nativeslothome)) &&
        (nativeslothome->mixinP &&
         translateToSingleInheritanceLanguageP()))) {
      return (nativeslothome);
    }
    if (candidate->mixinP) {
      return (NULL);
    }
    visibleslot = lookupSlot(clasS, slot->slotName);
    if ((!(slot == visibleslot)) &&
        subtypeOfP(visibleslot->slotOwner, slot->slotOwner)) {
      return (NULL);
    }
    { Class* superclass = NULL;
      Cons* iter000 = clasS->classAllSuperClasses;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        superclass = ((Class*)(iter000->value));
        if ((!superclass->mixinP) &&
            superclass->classAllSuperClasses->memberP(nativeslothome)) {
          candidate = superclass;
        }
      }
    }
    return (candidate);
  }
}

boolean slotNameConflictP(Slot* slot, Class* clasS) {
  { Symbol* name = slot->slotName;
    const char* nameString = name->symbolName;

    { Slot* siblingslot = NULL;
      Cons* iter000 = clasS->classLocalSlots->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        siblingslot = ((Slot*)(iter000->value));
        if ((!(siblingslot->slotName == name)) &&
            stringEqlP(siblingslot->slotName->symbolName, nameString)) {
          return (true);
        }
      }
    }
    { Class* superclass = NULL;
      Cons* iter001 = clasS->classAllSuperClasses;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        superclass = ((Class*)(iter001->value));
        { Slot* superslot = NULL;
          Cons* iter002 = superclass->classLocalSlots->theConsList;

          for (; !(iter002 == NIL); iter002 = iter002->rest) {
            superslot = ((Slot*)(iter002->value));
            if ((!(superslot->slotName == name)) &&
                stringEqlP(superslot->slotName->symbolName, nameString)) {
              return (true);
            }
          }
        }
      }
    }
    return (false);
  }
}

boolean methodContainsUnknownTypeP(MethodSlot* method) {
  { boolean foundP000 = false;

    { StandardObject* rtype = NULL;
      Cons* iter000 = method->methodReturnTypeSpecifiers_reader()->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        rtype = ((StandardObject*)(iter000->value));
        if (unknownTypeP(typeSpecToBaseType(computeRelativeTypeSpec(rtype, method->slotOwner)))) {
          foundP000 = true;
          break;
        }
      }
    }
    if (foundP000) {
      return (true);
    }
  }
  { StandardObject* ptype = NULL;
    Cons* iter001 = method->methodParameterTypeSpecifiers_reader()->theConsList;

    for (; !(iter001 == NIL); iter001 = iter001->rest) {
      ptype = ((StandardObject*)(iter001->value));
      if (unknownTypeP(typeSpecToBaseType(computeRelativeTypeSpec(ptype, method->slotOwner)))) {
        return (true);
      }
    }
  }
  return (false);
}

boolean methodContainsAnchoredTypeP(MethodSlot* method) {
  if (((Class*)(method->slotOwner->surrogateValue))->abstractP) {
    if (((boolean)(((CompoundTypeSpecifier*)(dynamicSlotValue(method->dynamicSlots, SYM_DEFCLASS_STELLA_SLOT_TYPE_SPECIFIER, NULL))))) &&
        isaP(((CompoundTypeSpecifier*)(dynamicSlotValue(method->dynamicSlots, SYM_DEFCLASS_STELLA_SLOT_TYPE_SPECIFIER, NULL))), SGT_DEFCLASS_STELLA_ANCHORED_TYPE_SPECIFIER)) {
      return (true);
    }
    { StandardObject* ptype = NULL;
      Cons* iter000 = method->methodParameterTypeSpecifiers_reader()->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        ptype = ((StandardObject*)(iter000->value));
        if (isaP(ptype, SGT_DEFCLASS_STELLA_ANCHORED_TYPE_SPECIFIER)) {
          return (true);
        }
      }
    }
  }
  return (false);
}

Symbol* yieldRecycleListName(Class* clasS) {
  return (internDerivedSymbol(clasS->classType, stringConcatenate("*RECYCLE-LIST-FOR-", className(clasS), 1, "-S*")));
}

StorageSlot* recycleSlot(Class* clasS) {
  { Surrogate* instancetype = clasS->classType;
    StorageSlot* recycleslot = NULL;

    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();

      for (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if (subtypeOfStorageSlotP(safePrimaryType(slot))) {
          { Slot* slot000 = slot;
            StorageSlot* slot = ((StorageSlot*)(slot000));

            if ((!(slot->slotName == SYM_DEFCLASS_STELLA_NEXT_SWEEP_LIST_OBJECT)) &&
                nativeSlotP(slot)) {
              if (instancetype == slot->slotBaseType) {
                return (slot);
              }
              if (((boolean)(((Class*)(slot->slotBaseType->surrogateValue)))) &&
                  subtypeOfP(instancetype, slot->slotBaseType)) {
                recycleslot = slot;
              }
            }
          }
        }
        else {
        }
      }
    }
    return (recycleslot);
  }
}

boolean useFreeListP(Class* clasS) {
  return ((clasS->classRecycleMethod_reader() == KWD_DEFCLASS_FREE_LIST) ||
      (clasS->classRecycleMethod_reader() == KWD_DEFCLASS_FREE_AND_SWEEP_LIST));
}

boolean useSweepListP(Class* clasS) {
  return ((clasS->classRecycleMethod_reader() == KWD_DEFCLASS_SWEEP_LIST) ||
      ((clasS->classRecycleMethod_reader() == KWD_DEFCLASS_FREE_AND_SWEEP_LIST) &&
       (!(oTRANSLATE_WITH_RECYCLE_LIST_DEBUGGINGpo ||
      ((boolean)(oCURRENTLY_RECYCLED_ITEMSo))))));
}

boolean decidedToRecycleP(Class* clasS) {
  return ((!(clasS->abstractP ||
      ((boolean)(((Symbol*)(dynamicSlotValue(clasS->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_CREATOR, NULL))))))) &&
      (useFreeListP(clasS) ||
       useSweepListP(clasS)));
}

int computeRecycledItemSize(Class* clasS) {
  { int size = NULL_INTEGER;

    if (((boolean)(clasS))) {
      if (oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_COMMON_LISP) {
        if (oCURRENT_STELLA_FEATURESo->membP(KWD_DEFCLASS_USE_COMMON_LISP_STRUCTS) ||
            oCURRENT_STELLA_FEATURESo->membP(KWD_DEFCLASS_USE_COMMON_LISP_VECTOR_STRUCTS)) {
          size = 4;
        }
        else {
          size = 10;
        }
      }
      else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_CPP) {
        size = 1;
      }
      else if (oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_JAVA) {
        size = 2;
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << oTRANSLATOROUTPUTLANGUAGEo << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      { Slot* slot = NULL;
        Iterator* iter000 = clasS->classSlots();

        for (; iter000->nextP(); ) {
          slot = ((Slot*)(iter000->value));
          if (storageSlotP(slot) &&
              (nativeSlotP(((StorageSlot*)(slot))) &&
               (!(((boolean)(slot->slotDirectEquivalent)) &&
              nativeSlotP(((StorageSlot*)(slot->slotDirectEquivalent))))))) {
            size = size + 1;
          }
        }
      }
      if (useFreeListP(clasS) &&
          (!((boolean)(recycleSlot(clasS))))) {
        size = size + 2;
      }
    }
    return (size);
  }
}

Cons* yieldRecycleListDefinitions(Class* clasS) {
  if (decidedToRecycleP(clasS)) {
    return (cons(listO(3, SYM_DEFCLASS_STELLA_DEFGLOBAL, yieldRecycleListName(clasS), listO(3, listO(4, SYM_DEFCLASS_STELLA_RECYCLE_LIST, SYM_DEFCLASS_STELLA_OF, classSymbol(clasS), NIL), listO(3, SYM_DEFCLASS_STELLA_CREATE_RECYCLE_LIST, clasS->classType, cons(wrapInteger(computeRecycledItemSize(clasS)), NIL)), NIL)), NIL));
  }
  else {
    return (NIL);
  }
}

Cons* yieldMakeTrees(Class* clasS) {
  return (cons(listO(4, SYM_DEFCLASS_STELLA_SETQ, SYM_DEFCLASS_STELLA_SELF, listO(3, SYM_DEFCLASS_STELLA_MAKE, classSymbol(clasS), NIL), NIL), NIL));
}

Symbol* yieldConstructorName(Class* clasS) {
  { const char* baseName = className(clasS);
    const char* prefix = (allUpperCaseStringP(baseName) ? "NEW-" : "new-");

    return (internDerivedSymbol(clasS->classType, stringConcatenate(prefix, baseName, 0)));
  }
}

Cons* yieldCreationTrees(Class* clasS) {
  if (((boolean)(((Symbol*)(dynamicSlotValue(clasS->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_CREATOR, NULL)))))) {
    if (((Symbol*)(dynamicSlotValue(clasS->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_CREATOR, NULL))) == yieldConstructorName(clasS)) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal creator name " << "`" << ((Symbol*)(dynamicSlotValue(clasS->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_CREATOR, NULL))) << "'" << " for the class " << std::endl << "`" << className(clasS) << "'" << ".  Using the default creator." << std::endl;
      return (yieldMakeTrees(clasS));
    }
    return (cons(listO(4, SYM_DEFCLASS_STELLA_SETQ, SYM_DEFCLASS_STELLA_SELF, cons(((Symbol*)(dynamicSlotValue(clasS->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_CREATOR, NULL))), NIL), NIL), NIL));
  }
  else if (decidedToRecycleP(clasS)) {
    return (yieldCreationOrReuseTrees(clasS));
  }
  else {
    return (yieldMakeTrees(clasS));
  }
}

Cons* yieldTerminateObjectTrees(Class* clasS) {
  { Cons* trees = NIL;
    Symbol* terminator = clasS->terminator();

    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();

      for (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if (subtypeOfStorageSlotP(safePrimaryType(slot))) {
          { Slot* slot000 = slot;
            StorageSlot* slot = ((StorageSlot*)(slot000));

            if (slot->componentP()) {
              trees = cons(listO(4, SYM_DEFCLASS_STELLA_WHEN, listO(3, SYM_DEFCLASS_STELLA_DEFINEDp, cons(slot->slotName, cons(SYM_DEFCLASS_STELLA_SELF, NIL)), NIL), listO(3, SYM_DEFCLASS_STELLA_FREE, cons(slot->slotName, cons(SYM_DEFCLASS_STELLA_SELF, NIL)), NIL), NIL), trees);
            }
          }
        }
        else {
        }
      }
    }
    if (((boolean)(lookupSlot(clasS, SYM_DEFCLASS_STELLA_DYNAMIC_SLOTS)))) {
      trees = cons(listO(3, SYM_DEFCLASS_STELLA_CLEAR, listO(3, SYM_DEFCLASS_STELLA_DYNAMIC_SLOTS, SYM_DEFCLASS_STELLA_SELF, NIL), NIL), trees);
    }
    if (((boolean)(terminator))) {
      if (useSweepListP(clasS)) {
        trees = cons(cons(terminator, cons(SYM_DEFCLASS_STELLA_SELF, NIL)), trees);
      }
      else {
        trees = cons(listO(4, SYM_DEFCLASS_STELLA_UNLESS, cons(terminator, cons(SYM_DEFCLASS_STELLA_SELF, NIL)), cons(SYM_DEFCLASS_STELLA_RETURN, NIL), NIL), trees);
      }
    }
    return (trees->reverse()->concatenate(yieldInitialValueAssignments(clasS, KWD_DEFCLASS_FORCE_NULL_VALUE), 0));
  }
}

Cons* yieldCreationOrReuseTrees(Class* clasS) {
  { boolean usefreelistP = useFreeListP(clasS);
    boolean usesweeplistP = useSweepListP(clasS);

    if (usefreelistP &&
        usesweeplistP) {
      return (yieldCreationOrReuseTreesFromFreeOrSweepList(clasS));
    }
    else if (usefreelistP) {
      return (yieldCreationOrReuseTreesFromFreeList(clasS));
    }
    else if (usesweeplistP) {
      return (yieldCreationOrReuseTreesFromSweepList(clasS));
    }
    else {
      throw *newStellaException("Assuming CLASS uses at least one of Free-list or sweep-list");
    }
  }
}

Cons* yieldCreationOrReuseTreesFromFreeList(Class* clasS) {
  { StorageSlot* recycleslot = recycleSlot(clasS);
    Cons* recycleslotresettree = (((boolean)(recycleslot)) ? yieldInitialValueAssignment(recycleslot, KWD_DEFCLASS_NULL_VALUE_ONLY) : ((Cons*)(NULL)));
    Symbol* recyclelist = yieldRecycleListName(clasS);

    recyclelist = yieldRecycleListName(clasS);
    return (listO(3, listO(4, SYM_DEFCLASS_STELLA_WHEN, listO(4, SYM_DEFCLASS_STELLA_AND, SYM_DEFCLASS_STELLA_oRECYCLING_ENABLEDpo, listO(3, SYM_DEFCLASS_STELLA_DEFINEDp, recyclelist, NIL), NIL), listO(4, SYM_DEFCLASS_STELLA_SETQ, SYM_DEFCLASS_STELLA_SELF, (((boolean)(recycleslot)) ? listO(3, SYM_DEFCLASS_STELLA_RECYCLED_ITEMS, recyclelist, NIL) : listO(3, SYM_DEFCLASS_STELLA_POP, listO(3, SYM_DEFCLASS_STELLA_LIST_OF_RECYCLED_ITEMS, recyclelist, NIL), NIL)), NIL), NIL), listO(4, SYM_DEFCLASS_STELLA_COND, cons(listO(3, SYM_DEFCLASS_STELLA_DEFINEDp, SYM_DEFCLASS_STELLA_SELF, NIL), ((((boolean)(recycleslot)) ? cons(listO(4, SYM_DEFCLASS_STELLA_SETF, listO(3, SYM_DEFCLASS_STELLA_RECYCLED_ITEMS, recyclelist, NIL), listO(4, SYM_DEFCLASS_STELLA_SLOT_VALUE, SYM_DEFCLASS_STELLA_SELF, recycleslot->slotName, NIL), NIL), NIL) : NIL))->concatenate(((((boolean)(recycleslotresettree)) ? cons(recycleslotresettree, NIL) : NIL))->concatenate(cons(listO(3, SYM_DEFCLASS_STELLA___, listO(3, SYM_DEFCLASS_STELLA_CURRENT_LENGTH, recyclelist, NIL), NIL), yieldUnregisterRecycledItemTrees()->concatenate(NIL, 0)), 0), 0)), cons(SYM_DEFCLASS_STELLA_OTHERWISE, yieldMakeTrees(clasS)->concatenate(yieldInitialValueAssignments(clasS, KWD_DEFCLASS_NULL_VALUE_ONLY)->concatenate(NIL, 0), 0)), NIL), NIL));
  }
}

Cons* yieldCreationOrReuseTreesFromSweepList(Class* clasS) {
  { Symbol* recyclelist = yieldRecycleListName(clasS);

    recyclelist = yieldRecycleListName(clasS);
    return (cons(listO(4, SYM_DEFCLASS_STELLA_COND, listO(4, listO(4, SYM_DEFCLASS_STELLA_AND, SYM_DEFCLASS_STELLA_oRECYCLING_ENABLEDpo, listO(3, SYM_DEFCLASS_STELLA_DEFINEDp, recyclelist, NIL), NIL), listO(4, SYM_DEFCLASS_STELLA_SETQ, SYM_DEFCLASS_STELLA_SELF, listO(3, SYM_DEFCLASS_STELLA_UNUSED_ITEMS, recyclelist, NIL), NIL), listO(4, SYM_DEFCLASS_STELLA_COND, listO(3, listO(3, SYM_DEFCLASS_STELLA_DEFINEDp, SYM_DEFCLASS_STELLA_SELF, NIL), listO(4, SYM_DEFCLASS_STELLA_SETF, listO(3, SYM_DEFCLASS_STELLA_UNUSED_ITEMS, recyclelist, NIL), listO(3, SYM_DEFCLASS_STELLA_NEXT_SWEEP_LIST_OBJECT, listO(3, SYM_DEFCLASS_STELLA_UNUSED_ITEMS, recyclelist, NIL), NIL), NIL), NIL), cons(SYM_DEFCLASS_STELLA_OTHERWISE, yieldMakeTrees(clasS)->concatenate(yieldInitialValueAssignments(clasS, KWD_DEFCLASS_NULL_VALUE_ONLY)->concatenate(listO(5, listO(4, SYM_DEFCLASS_STELLA_SETF, listO(3, SYM_DEFCLASS_STELLA_NEXT_SWEEP_LIST_OBJECT, SYM_DEFCLASS_STELLA_SELF, NIL), listO(3, SYM_DEFCLASS_STELLA_ALL_ITEMS, recyclelist, NIL), NIL), listO(4, SYM_DEFCLASS_STELLA_SETF, listO(3, SYM_DEFCLASS_STELLA_ALL_ITEMS, recyclelist, NIL), SYM_DEFCLASS_STELLA_SELF, NIL), listO(3, SYM_DEFCLASS_STELLA_ii, listO(3, SYM_DEFCLASS_STELLA_CURRENT_LENGTH, recyclelist, NIL), NIL), listO(4, SYM_DEFCLASS_STELLA_WHEN, listO(4, SYM_DEFCLASS_STELLA_e, listO(3, SYM_DEFCLASS_STELLA___, SYM_DEFCLASS_STELLA_oRECYCLE_LISTS_MAINTENANCE_TIMERo, NIL), wrapInteger(0), NIL), cons(SYM_DEFCLASS_STELLA_MAINTAIN_RECYCLE_LISTS, NIL), NIL), NIL), 0), 0)), NIL), NIL), cons(SYM_DEFCLASS_STELLA_OTHERWISE, yieldMakeTrees(clasS)->concatenate(yieldInitialValueAssignments(clasS, KWD_DEFCLASS_NULL_VALUE_ONLY)->concatenate(NIL, 0), 0)), NIL), NIL));
  }
}

Cons* yieldCreationOrReuseTreesFromFreeOrSweepList(Class* clasS) {
  { StorageSlot* recycleslot = recycleSlot(clasS);
    Cons* recycleslotresettree = (((boolean)(recycleslot)) ? yieldInitialValueAssignment(recycleslot, KWD_DEFCLASS_NULL_VALUE_ONLY) : ((Cons*)(NULL)));
    Symbol* recyclelist = yieldRecycleListName(clasS);

    recyclelist = yieldRecycleListName(clasS);
    return (cons(listO(4, SYM_DEFCLASS_STELLA_COND, listO(4, listO(4, SYM_DEFCLASS_STELLA_AND, SYM_DEFCLASS_STELLA_oRECYCLING_ENABLEDpo, listO(3, SYM_DEFCLASS_STELLA_DEFINEDp, recyclelist, NIL), NIL), listO(4, SYM_DEFCLASS_STELLA_SETQ, SYM_DEFCLASS_STELLA_SELF, (((boolean)(recycleslot)) ? listO(3, SYM_DEFCLASS_STELLA_RECYCLED_ITEMS, recyclelist, NIL) : listO(3, SYM_DEFCLASS_STELLA_POP, listO(3, SYM_DEFCLASS_STELLA_LIST_OF_RECYCLED_ITEMS, recyclelist, NIL), NIL)), NIL), listO(4, SYM_DEFCLASS_STELLA_COND, cons(listO(3, SYM_DEFCLASS_STELLA_DEFINEDp, SYM_DEFCLASS_STELLA_SELF, NIL), ((((boolean)(recycleslot)) ? cons(listO(4, SYM_DEFCLASS_STELLA_SETF, listO(3, SYM_DEFCLASS_STELLA_RECYCLED_ITEMS, recyclelist, NIL), listO(4, SYM_DEFCLASS_STELLA_SLOT_VALUE, SYM_DEFCLASS_STELLA_SELF, recycleslot->slotName, NIL), NIL), NIL) : NIL))->concatenate(((((boolean)(recycleslotresettree)) ? cons(recycleslotresettree, NIL) : NIL))->concatenate(NIL, 0), 0)), listO(4, SYM_DEFCLASS_STELLA_OTHERWISE, listO(4, SYM_DEFCLASS_STELLA_SETQ, SYM_DEFCLASS_STELLA_SELF, listO(3, SYM_DEFCLASS_STELLA_UNUSED_ITEMS, recyclelist, NIL), NIL), listO(4, SYM_DEFCLASS_STELLA_COND, listO(3, listO(3, SYM_DEFCLASS_STELLA_DEFINEDp, SYM_DEFCLASS_STELLA_SELF, NIL), listO(4, SYM_DEFCLASS_STELLA_SETF, listO(3, SYM_DEFCLASS_STELLA_UNUSED_ITEMS, recyclelist, NIL), listO(3, SYM_DEFCLASS_STELLA_NEXT_SWEEP_LIST_OBJECT, listO(3, SYM_DEFCLASS_STELLA_UNUSED_ITEMS, recyclelist, NIL), NIL), NIL), NIL), cons(SYM_DEFCLASS_STELLA_OTHERWISE, yieldMakeTrees(clasS)->concatenate(yieldInitialValueAssignments(clasS, KWD_DEFCLASS_NULL_VALUE_ONLY)->concatenate(listO(5, listO(4, SYM_DEFCLASS_STELLA_SETF, listO(3, SYM_DEFCLASS_STELLA_NEXT_SWEEP_LIST_OBJECT, SYM_DEFCLASS_STELLA_SELF, NIL), listO(3, SYM_DEFCLASS_STELLA_ALL_ITEMS, recyclelist, NIL), NIL), listO(4, SYM_DEFCLASS_STELLA_SETF, listO(3, SYM_DEFCLASS_STELLA_ALL_ITEMS, recyclelist, NIL), SYM_DEFCLASS_STELLA_SELF, NIL), listO(3, SYM_DEFCLASS_STELLA_ii, listO(3, SYM_DEFCLASS_STELLA_CURRENT_LENGTH, recyclelist, NIL), NIL), listO(4, SYM_DEFCLASS_STELLA_WHEN, listO(4, SYM_DEFCLASS_STELLA_e, listO(3, SYM_DEFCLASS_STELLA___, SYM_DEFCLASS_STELLA_oRECYCLE_LISTS_MAINTENANCE_TIMERo, NIL), wrapInteger(0), NIL), cons(SYM_DEFCLASS_STELLA_MAINTAIN_RECYCLE_LISTS, NIL), NIL), NIL), 0), 0)), NIL), NIL), NIL), NIL), cons(SYM_DEFCLASS_STELLA_OTHERWISE, yieldMakeTrees(clasS)->concatenate(yieldInitialValueAssignments(clasS, KWD_DEFCLASS_NULL_VALUE_ONLY)->concatenate(NIL, 0), 0)), NIL), NIL));
  }
}

void markDirectEquivalentSlot(Slot* slot) {
  { Slot* directequivalent = slot->slotDirectEquivalent;

    if (((boolean)(directequivalent))) {
      if (directequivalent->slotMarkedP) {
        slot->slotMarkedP = true;
      }
      else {
        directequivalent->slotMarkedP = true;
      }
    }
  }
}

boolean isContextSensitiveSlotP(StorageSlot* slot) {
  return (slot->slotContextSensitiveP ||
      (((boolean)(slot->slotDirectEquivalent)) &&
       isContextSensitiveSlotP(((StorageSlot*)(slot->slotDirectEquivalent)))));
}

Cons* yieldInitialValueAssignment(StorageSlot* slot, Keyword* mode) {
  { Object* initialvalueexpression = yieldInitialValueExpression(slot);
    boolean requiredslotP = slot->requiredP();

    if (((boolean)(initialvalueexpression)) &&
        (!(slot->slotName == SYM_DEFCLASS_STELLA_NEXT_SWEEP_LIST_OBJECT))) {
      if (mode == KWD_DEFCLASS_NULL_VALUE_ONLY) {
        if (requiredslotP ||
            (!equalConsTreesP(typeToWalkedNullValueTree(slot->typeSpecifier(), slot->type()), initialvalueexpression))) {
          initialvalueexpression = NULL;
        }
      }
      else if (mode == KWD_DEFCLASS_INITIAL_VALUE_ONLY) {
        if (requiredslotP ||
            equalConsTreesP(typeToWalkedNullValueTree(slot->typeSpecifier(), slot->type()), initialvalueexpression)) {
          initialvalueexpression = NULL;
        }
      }
      else if (mode == KWD_DEFCLASS_FORCE_NULL_VALUE) {
        initialvalueexpression = typeToWalkedNullValueTree(slot->typeSpecifier(), slot->type());
      }
      else if (mode == KWD_DEFCLASS_ANY_INITIAL_VALUE) {
        if (requiredslotP) {
          initialvalueexpression = NULL;
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << mode << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      if (((boolean)(initialvalueexpression))) {
        return (listO(4, SYM_DEFCLASS_STELLA_SETF, listO(4, SYM_DEFCLASS_STELLA_SLOT_VALUE, SYM_DEFCLASS_STELLA_SELF, canonicalSlot(slot)->slotName, ((isContextSensitiveSlotP(slot) ? listO(3, KWD_DEFCLASS_CONTEXT_SENSITIVEp, SYM_DEFCLASS_STELLA_FALSE, NIL) : NIL))->concatenate(NIL, 0)), initialvalueexpression, NIL));
      }
    }
    return (NULL);
  }
}

Cons* yieldInitialValueAssignments(Class* clasS, Keyword* mode) {
  { Cons* assignments = NIL;
    Object* initialvalueassignment = NULL;

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
        markDirectEquivalentSlot(slot);
      }
    }
    { Slot* slot = NULL;
      Iterator* iter002 = clasS->classSlots();

      for (; iter002->nextP(); ) {
        slot = ((Slot*)(iter002->value));
        if ((!slot->slotMarkedP) &&
            storageSlotP(slot)) {
          initialvalueassignment = yieldInitialValueAssignment(((StorageSlot*)(slot)), mode);
          if (((boolean)(initialvalueassignment))) {
            assignments = cons(initialvalueassignment, assignments);
          }
        }
      }
    }
    return (assignments);
  }
}

Cons* yieldLocalInitialValueAssignments(Class* clasS) {
  { Cons* assignments = NIL;
    Object* initialvalueassignment = NULL;

    { Slot* slot = NULL;
      Cons* iter000 = clasS->classLocalSlots->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        slot = ((Slot*)(iter000->value));
        slot->slotMarkedP = false;
      }
    }
    { Slot* slot = NULL;
      Cons* iter001 = clasS->classLocalSlots->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        slot = ((Slot*)(iter001->value));
        markDirectEquivalentSlot(slot);
      }
    }
    { Slot* slot = NULL;
      Cons* iter002 = clasS->classLocalSlots->theConsList;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        slot = ((Slot*)(iter002->value));
        if ((!slot->slotMarkedP) &&
            storageSlotP(slot)) {
          initialvalueassignment = yieldInitialValueAssignment(((StorageSlot*)(slot)), KWD_DEFCLASS_ANY_INITIAL_VALUE);
          if (((boolean)(initialvalueassignment))) {
            assignments = cons(initialvalueassignment, assignments);
          }
        }
      }
    }
    return (assignments->reverse());
  }
}

Cons* yieldInitializerTrees(Class* clasS) {
  { Cons* initializers = NIL;
    Cons* cursor = NIL;

    if (((boolean)(((Symbol*)(dynamicSlotValue(clasS->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_INITIALIZER, NULL)))))) {
      initializers = cons(((Symbol*)(dynamicSlotValue(clasS->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_INITIALIZER, NULL))), initializers);
    }
    { Class* super = NULL;
      Cons* iter000 = clasS->classAllSuperClasses;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        super = ((Class*)(iter000->value));
        if (((boolean)(((Symbol*)(dynamicSlotValue(super->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_INITIALIZER, NULL))))) &&
            (!initializers->membP(((Symbol*)(dynamicSlotValue(super->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_INITIALIZER, NULL)))))) {
          initializers = cons(((Symbol*)(dynamicSlotValue(super->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_INITIALIZER, NULL))), initializers);
        }
      }
    }
    cursor = initializers;
    while (!(cursor == NIL)) {
      cursor->firstSetter(cons(cursor->value, cons(SYM_DEFCLASS_STELLA_SELF, NIL)));
      cursor = cursor->rest;
    }
    return (initializers);
  }
}

Cons* yieldConstructorBody(Class* clasS, Cons* requiredassignments) {
  { Cons* initialvalueassignments = yieldInitialValueAssignments(clasS, (decidedToRecycleP(clasS) ? KWD_DEFCLASS_INITIAL_VALUE_ONLY : KWD_DEFCLASS_ANY_INITIAL_VALUE));

    if ((initialvalueassignments == NIL) &&
        ((requiredassignments == NIL) &&
         ((!((boolean)(clasS->initializer()))) &&
          ((!clasS->activeP()) &&
           (!decidedToRecycleP(clasS)))))) {
      return (yieldCreationTrees(clasS));
    }
    return (yieldCreationTrees(clasS)->concatenate(requiredassignments->concatenate(initialvalueassignments->concatenate(yieldInitializerTrees(clasS)->concatenate(((clasS->activeP() ? cons(listO(3, SYM_DEFCLASS_STELLA_RUN_CONSTRUCTOR_DEMONS, SYM_DEFCLASS_STELLA_SELF, NIL), NIL) : NIL))->concatenate(NIL, 0), 0), 0), 0), 0));
  }
}

Cons* yieldConstructorDefinition(Class* clasS) {
  if (exceptionClassP(clasS)) {
    return (yieldExceptionConstructorDefinition(clasS));
  }
  { Cons* requiredparameters = NIL;
    Cons* assignments = NIL;
    Slot* slot = NULL;

    { Symbol* slotname = NULL;
      Cons* iter000 = clasS->classRequiredSlotNames_reader()->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        slotname = ((Symbol*)(iter000->value));
        assignments = cons(listO(4, SYM_DEFCLASS_STELLA_SETF, cons(slotname, cons(SYM_DEFCLASS_STELLA_SELF, NIL)), slotname, NIL), assignments);
        slot = lookupSlot(clasS, slotname);
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(cons(slotname, cons(typeToSymbol(slot->type()), NIL)), NIL);
            if (requiredparameters == NIL) {
              requiredparameters = collect000;
            }
            else {
              addConsToEndOfConsList(requiredparameters, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(cons(slotname, cons(typeToSymbol(slot->type()), NIL)), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (listO(8, SYM_DEFCLASS_STELLA_DEFUN, cons(yieldConstructorName(clasS), cons(classSymbol(clasS), NIL)), requiredparameters->concatenate(NIL, 0), KWD_DEFCLASS_CONSTRUCTORp, SYM_DEFCLASS_STELLA_TRUE, KWD_DEFCLASS_PUBLICp, (clasS->publicP() ? TRUE_WRAPPER : FALSE_WRAPPER), cons(listO(3, SYM_DEFCLASS_STELLA_LET, cons(listO(3, SYM_DEFCLASS_STELLA_SELF, classSymbol(clasS), cons(SYM_DEFCLASS_STELLA_NULL, NIL)), NIL), yieldConstructorBody(clasS, assignments->reverse())->concatenate(cons(listO(3, SYM_DEFCLASS_STELLA_RETURN, SYM_DEFCLASS_STELLA_SELF, NIL), NIL), 0)), NIL)));
  }
}

Cons* yieldExceptionConstructorBody(Class* clasS, Symbol* messageparameter, Cons* requiredassignments) {
  { Cons* initialvalueassignments = yieldInitialValueAssignments(clasS, (decidedToRecycleP(clasS) ? KWD_DEFCLASS_INITIAL_VALUE_ONLY : KWD_DEFCLASS_ANY_INITIAL_VALUE));

    if ((initialvalueassignments == NIL) &&
        ((requiredassignments == NIL) &&
         ((!((boolean)(clasS->initializer()))) &&
          ((!clasS->activeP()) &&
           (!decidedToRecycleP(clasS)))))) {
      return (cons(listO(4, SYM_DEFCLASS_STELLA_SETQ, SYM_DEFCLASS_STELLA_SELF, listO(3, SYM_DEFCLASS_STELLA_MAKE, classSymbol(clasS), cons(messageparameter, NIL)), NIL), NIL));
    }
    return (cons(listO(4, SYM_DEFCLASS_STELLA_SETQ, SYM_DEFCLASS_STELLA_SELF, listO(3, SYM_DEFCLASS_STELLA_MAKE, classSymbol(clasS), cons(messageparameter, NIL)), NIL), requiredassignments->concatenate(initialvalueassignments->concatenate(yieldInitializerTrees(clasS)->concatenate(((clasS->activeP() ? cons(listO(3, SYM_DEFCLASS_STELLA_RUN_CONSTRUCTOR_DEMONS, SYM_DEFCLASS_STELLA_SELF, NIL), NIL) : NIL))->concatenate(NIL, 0), 0), 0), 0)));
  }
}

Cons* yieldExceptionConstructorDefinition(Class* clasS) {
  { Cons* requiredparameters = NIL;
    Cons* assignments = NIL;
    Slot* slot = NULL;
    Symbol* messageparameter = SYM_DEFCLASS_STELLA_MESSAGE;

    { Symbol* slotname = NULL;
      Cons* iter000 = clasS->classRequiredSlotNames_reader()->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        slotname = ((Symbol*)(iter000->value));
        if (!(slotname == messageparameter)) {
          assignments = cons(listO(4, SYM_DEFCLASS_STELLA_SETF, cons(slotname, cons(SYM_DEFCLASS_STELLA_SELF, NIL)), slotname, NIL), assignments);
        }
        slot = lookupSlot(clasS, slotname);
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(cons(slotname, cons(typeToSymbol(slot->type()), NIL)), NIL);
            if (requiredparameters == NIL) {
              requiredparameters = collect000;
            }
            else {
              addConsToEndOfConsList(requiredparameters, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(cons(slotname, cons(typeToSymbol(slot->type()), NIL)), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (listO(8, SYM_DEFCLASS_STELLA_DEFUN, cons(yieldConstructorName(clasS), cons(classSymbol(clasS), NIL)), requiredparameters->concatenate(NIL, 0), KWD_DEFCLASS_CONSTRUCTORp, SYM_DEFCLASS_STELLA_TRUE, KWD_DEFCLASS_PUBLICp, (clasS->publicP() ? TRUE_WRAPPER : FALSE_WRAPPER), cons(listO(3, SYM_DEFCLASS_STELLA_LET, cons(listO(3, SYM_DEFCLASS_STELLA_SELF, classSymbol(clasS), cons(SYM_DEFCLASS_STELLA_NULL, NIL)), NIL), yieldExceptionConstructorBody(clasS, messageparameter, assignments->reverse())->concatenate(cons(listO(3, SYM_DEFCLASS_STELLA_RETURN, SYM_DEFCLASS_STELLA_SELF, NIL), NIL), 0)), NIL)));
  }
}

Cons* yieldDestructorDefinitions(Class* clasS) {
  { Symbol* classname = classSymbol(clasS);
    Symbol* destructor = ((Symbol*)(dynamicSlotValue(clasS->dynamicSlots, SYM_DEFCLASS_STELLA_CLASS_DESTRUCTOR, NULL)));
    Symbol* terminator = clasS->terminator();
    Cons* definitions = NIL;

    if (decidedToRecycleP(clasS)) {
      { StorageSlot* recycleslot = recycleSlot(clasS);
        Symbol* recyclelist = yieldRecycleListName(clasS);

        if (useFreeListP(clasS)) {
          definitions = cons(listO(5, SYM_DEFCLASS_STELLA_DEFMETHOD, SYM_DEFCLASS_STELLA_FREE, cons(listO(3, SYM_DEFCLASS_STELLA_SELF, classname, NIL), NIL), listO(3, SYM_DEFCLASS_STELLA_WHEN, listO(4, SYM_DEFCLASS_STELLA_AND, SYM_DEFCLASS_STELLA_oRECYCLING_ENABLEDpo, listO(3, SYM_DEFCLASS_STELLA_DEFINEDp, recyclelist, NIL), (((useSweepListP(clasS) &&
              (!subtypeOfP(clasS->classType, SGT_DEFCLASS_STELLA_STANDARD_OBJECT))) ? cons(listO(3, SYM_DEFCLASS_STELLA_DEFINEDp, listO(3, SYM_DEFCLASS_STELLA_ALL_ITEMS, recyclelist, NIL), NIL), NIL) : NIL))->concatenate(NIL, 0)), yieldTerminateObjectTrees(clasS)->concatenate(yieldRegisterRecycledItemTrees()->concatenate(((((boolean)(recycleslot)) ? listO(3, listO(4, SYM_DEFCLASS_STELLA_SETF, listO(4, SYM_DEFCLASS_STELLA_SLOT_VALUE, SYM_DEFCLASS_STELLA_SELF, recycleslot->slotName, NIL), listO(3, SYM_DEFCLASS_STELLA_RECYCLED_ITEMS, recyclelist, NIL), NIL), listO(4, SYM_DEFCLASS_STELLA_SETF, listO(3, SYM_DEFCLASS_STELLA_RECYCLED_ITEMS, recyclelist, NIL), SYM_DEFCLASS_STELLA_SELF, NIL), NIL) : cons(listO(4, SYM_DEFCLASS_STELLA_PUSH, listO(3, SYM_DEFCLASS_STELLA_LIST_OF_RECYCLED_ITEMS, recyclelist, NIL), SYM_DEFCLASS_STELLA_SELF, NIL), NIL)))->concatenate((((!useSweepListP(clasS)) ? listO(3, listO(3, SYM_DEFCLASS_STELLA_ii, listO(3, SYM_DEFCLASS_STELLA_CURRENT_LENGTH, recyclelist, NIL), NIL), listO(4, SYM_DEFCLASS_STELLA_WHEN, listO(4, SYM_DEFCLASS_STELLA_e, listO(3, SYM_DEFCLASS_STELLA___, SYM_DEFCLASS_STELLA_oRECYCLE_LISTS_MAINTENANCE_TIMERo, NIL), wrapInteger(0), NIL), cons(SYM_DEFCLASS_STELLA_MAINTAIN_RECYCLE_LISTS, NIL), NIL), NIL) : NIL))->concatenate(NIL, 0), 0), 0), 0)), NIL), definitions);
        }
        if (useSweepListP(clasS)) {
          if (!useFreeListP(clasS)) {
            definitions = cons(listO(5, SYM_DEFCLASS_STELLA_DEFMETHOD, SYM_DEFCLASS_STELLA_FREE, cons(listO(3, SYM_DEFCLASS_STELLA_SELF, classname, NIL), NIL), SYM_DEFCLASS_STELLA_NULL, NIL), definitions);
          }
          definitions = cons(listO(5, SYM_DEFCLASS_STELLA_DEFMETHOD, SYM_DEFCLASS_STELLA_SWEEP, cons(listO(3, SYM_DEFCLASS_STELLA_SELF, classname, NIL), NIL), listO(3, SYM_DEFCLASS_STELLA_WHEN, listO(4, SYM_DEFCLASS_STELLA_AND, SYM_DEFCLASS_STELLA_oRECYCLING_ENABLEDpo, listO(3, SYM_DEFCLASS_STELLA_DEFINEDp, recyclelist, NIL), NIL), ((useFreeListP(clasS) ? ((((boolean)(recycleSlot(clasS))) ? cons(listO(4, SYM_DEFCLASS_STELLA_SETF, listO(3, SYM_DEFCLASS_STELLA_RECYCLED_ITEMS, recyclelist, NIL), SYM_DEFCLASS_STELLA_NULL, NIL), NIL) : cons(listO(3, SYM_DEFCLASS_STELLA_CLEAR, listO(3, SYM_DEFCLASS_STELLA_LIST_OF_RECYCLED_ITEMS, recyclelist, NIL), NIL), NIL))) : NIL))->concatenate(cons(listO(6, SYM_DEFCLASS_STELLA_LET, cons(listO(3, SYM_DEFCLASS_STELLA_UNUSED, listO(3, SYM_DEFCLASS_STELLA_UNUSED_ITEMS, recyclelist, NIL), NIL), NIL), listO(4, SYM_DEFCLASS_STELLA_SETQ, SYM_DEFCLASS_STELLA_SELF, listO(3, SYM_DEFCLASS_STELLA_ALL_ITEMS, recyclelist, NIL), NIL), listO(3, SYM_DEFCLASS_STELLA_WHILE, listO(3, SYM_DEFCLASS_STELLA_NOT, listO(4, SYM_DEFCLASS_STELLA_EQLp, SYM_DEFCLASS_STELLA_SELF, SYM_DEFCLASS_STELLA_UNUSED, NIL), NIL), yieldTerminateObjectTrees(clasS)->concatenate(cons(listO(4, SYM_DEFCLASS_STELLA_SETQ, SYM_DEFCLASS_STELLA_SELF, listO(3, SYM_DEFCLASS_STELLA_NEXT_SWEEP_LIST_OBJECT, SYM_DEFCLASS_STELLA_SELF, NIL), NIL), NIL), 0)), listO(4, SYM_DEFCLASS_STELLA_SETF, listO(3, SYM_DEFCLASS_STELLA_UNUSED_ITEMS, recyclelist, NIL), listO(3, SYM_DEFCLASS_STELLA_ALL_ITEMS, recyclelist, NIL), NIL), NIL), NIL), 0)), NIL), definitions);
        }
      }
    }
    else if (((boolean)(terminator)) ||
        ((boolean)(destructor))) {
      if (!(((boolean)(destructor)))) {
        destructor = SYM_DEFCLASS_STELLA_UNMAKE;
      }
      if (!(destructor == SYM_DEFCLASS_STELLA_FREE)) {
        definitions = cons(listO(5, SYM_DEFCLASS_STELLA_DEFMETHOD, SYM_DEFCLASS_STELLA_FREE, cons(listO(3, SYM_DEFCLASS_STELLA_SELF, classname, NIL), NIL), (((boolean)(terminator)) ? listO(4, SYM_DEFCLASS_STELLA_WHEN, cons(terminator, cons(SYM_DEFCLASS_STELLA_SELF, NIL)), cons(destructor, cons(SYM_DEFCLASS_STELLA_SELF, NIL)), NIL) : cons(destructor, cons(SYM_DEFCLASS_STELLA_SELF, NIL))), NIL), definitions);
      }
    }
    return (definitions->reverse());
  }
}

void createConstructorAndDestructorUnits(Class* clasS) {
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_DEFCLASS_CPP_STANDALONE) {
    createCppConstructorUnit(clasS);
    return;
  }
  if (!(clasS->abstractP ||
      subtypeOfP(clasS->classType, SGT_DEFCLASS_STELLA_LITERAL))) {
    { Object* definition = NULL;
      Cons* iter000 = yieldRecycleListDefinitions(clasS);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        definition = iter000->value;
        walkAuxiliaryTree(((Cons*)(definition)));
      }
    }
    walkAuxiliaryTree(yieldConstructorDefinition(clasS));
    { Object* destructor = NULL;
      Cons* iter001 = yieldDestructorDefinitions(clasS);

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        destructor = iter001->value;
        walkAuxiliaryTree(((Cons*)(destructor)));
      }
    }
  }
}

boolean parameterizedClassP(Class* clasS) {
  return (clasS->parameters()->nonEmptyP());
}

boolean classWithInitializerP(Class* clasS) {
  { boolean foundP000 = false;

    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();

      for (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if (storageSlotP(slot)) {
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

Symbol* yieldInitializerName(Class* clasS) {
  { const char* baseName = className(clasS);
    const char* prefix = (allUpperCaseStringP(baseName) ? "INITIALIZE-" : "initialize-");

    return (internDerivedSymbol(clasS->classType, stringConcatenate(prefix, baseName, 0)));
  }
}

Cons* yieldInitializerDefinition(Class* clasS) {
  { Cons* parentinitforms = NIL;

    { Surrogate* super = NULL;
      Cons* iter000 = clasS->classDirectSupers->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        super = ((Surrogate*)(iter000->value));
        if (classWithInitializerP(((Class*)(super->surrogateValue)))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(cons(yieldInitializerName(((Class*)(super->surrogateValue))), cons(SYM_DEFCLASS_STELLA_SELF, NIL)), NIL);
              if (parentinitforms == NIL) {
                parentinitforms = collect000;
              }
              else {
                addConsToEndOfConsList(parentinitforms, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(cons(yieldInitializerName(((Class*)(super->surrogateValue))), cons(SYM_DEFCLASS_STELLA_SELF, NIL)), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (listO(3, SYM_DEFCLASS_STELLA_DEFUN, yieldInitializerName(clasS), cons(cons(listO(3, SYM_DEFCLASS_STELLA_SELF, yieldTypeSpecTree(clasS->classType), NIL), NIL), parentinitforms->concatenate(yieldLocalInitialValueAssignments(clasS)->concatenate(NIL, 0), 0))));
  }
}

void createCppConstructorUnit(Class* clasS) {
  if (!(parameterizedClassP(clasS))) {
    { Object* classname = yieldTypeSpecTree(clasS->classType);
      boolean hasinitializerP = classWithInitializerP(clasS);

      if (hasinitializerP) {
        walkAuxiliaryTree(yieldInitializerDefinition(clasS));
      }
      helpWalkAuxiliaryTree(listO(3, SYM_DEFCLASS_STELLA_DEFMETHOD, classname, listO(4, cons(listO(3, SYM_DEFCLASS_STELLA_SELF, classname, NIL), NIL), KWD_DEFCLASS_PUBLICp, (clasS->publicP() ? TRUE_WRAPPER : FALSE_WRAPPER), ((hasinitializerP ? cons(cons(yieldInitializerName(clasS), cons(SYM_DEFCLASS_STELLA_SELF, NIL)), NIL) : cons(SYM_DEFCLASS_STELLA_NULL, NIL)))->concatenate(NIL, 0))), false);
    }
  }
}

boolean cppConstructorP(MethodSlot* method) {
  return ((method->type() == SGT_DEFCLASS_STELLA_VOID) &&
      ((method->methodParameterNames_reader()->length() == 1) &&
       (stringEqlP(method->slotOwner->symbolName, method->slotName->symbolName) &&
        (((Module*)(method->slotOwner->homeContext)) == ((Module*)(method->slotName->homeContext))))));
}

// If `TRUE' calls to `new' or `free' on classes with :recycle-method;
// specifications will actually operate on recycle lists.  Otherwise, all
// recycle list operations will be no-ops.
DEFINE_STELLA_SPECIAL(oRECYCLING_ENABLEDpo, boolean , true);

List* oALL_RECYCLE_LISTSo = NULL;

RecycleList* createRecycleList(Surrogate* classtype, int itemsize) {
  { RecycleList* list = newRecycleList();

    { RecycleList* value000 = NULL;

      { RecycleList* list = NULL;
        Cons* iter000 = oALL_RECYCLE_LISTSo->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          list = ((RecycleList*)(iter000->value));
          if (list->recycleListOf == classtype) {
            value000 = list;
            break;
          }
        }
      }
      { RecycleList* oldlist = value000;

        if (((boolean)(oldlist))) {
          clearRecycleList(oldlist);
          oALL_RECYCLE_LISTSo->remove(oldlist);
        }
        oALL_RECYCLE_LISTSo->push(list);
        list->recycleListOf = classtype;
        list->itemSize = itemsize;
        return (list);
      }
    }
  }
}

void clearRecycleList(RecycleList* list) {
  // Reset `list' to its empty state.
  list->allItems = NULL;
  list->unusedItems = NULL;
  list->recycledItems = NULL;
  list->listOfRecycledItems->theConsList = NIL;
  list->currentLength = 0;
}

void clearRecycleLists() {
  // Reset all currently active recycle lists to their empty state.
  oRECYCLE_LISTS_MAINTENANCE_TIMERo = oRECYCLE_LISTS_MAINTENANCE_INTERVALo;
  { RecycleList* list = NULL;
    Cons* iter000 = oALL_RECYCLE_LISTSo->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      list = ((RecycleList*)(iter000->value));
      clearRecycleList(list);
    }
  }
}

void printRecycleLists() {
  // Print the current state of all recycle lists.
  std::cout << "Approximate space occupied by recycle lists: " << (totalRecycleListsSize() * 4) << " bytes" << std::endl;
  { RecycleList* list = NULL;
    Cons* iter000 = oALL_RECYCLE_LISTSo->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      list = ((RecycleList*)(iter000->value));
      std::cout << list << std::endl;
    }
  }
}

// Maximum number of bytes to be occupied by recycle lists.
int oMAX_RECYCLE_LIST_BYTESo = 3000000;

// Total number of recycle list extensions after which a
// size maintenance operation is performed to ensure that
// the `*MAX-RECYCLE-LIST-BYTES*' limit is still met.
int oRECYCLE_LISTS_MAINTENANCE_INTERVALo = 5000;

int oRECYCLE_LISTS_MAINTENANCE_TIMERo = NULL_INTEGER;

void maintainRecycleLists() {
  if (((boolean)(oCURRENTLY_RECYCLED_ITEMSo))) {
    return;
  }
  { int totalsize = totalRecycleListsSize();
    int maxsize = stella::floor(oMAX_RECYCLE_LIST_BYTESo / 4.0);
    int listsize = NULL_INTEGER;
    boolean classredefinitionP = false;

    oRECYCLE_LISTS_MAINTENANCE_TIMERo = oRECYCLE_LISTS_MAINTENANCE_INTERVALo;
    { RecycleList* list = NULL;
      Cons* iter000 = oALL_RECYCLE_LISTSo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        list = ((RecycleList*)(iter000->value));
        if (((boolean)(((Class*)(list->recycleListOf->surrogateValue)))) &&
            (!decidedToRecycleP(((Class*)(list->recycleListOf->surrogateValue))))) {
          classredefinitionP = true;
          clearRecycleList(list);
          list->deletedPSetter(true);
        }
      }
    }
    if (classredefinitionP) {
      oALL_RECYCLE_LISTSo->removeDeletedMembers();
    }
    if (totalsize > maxsize) {
      oALL_RECYCLE_LISTSo->sort(((cpp_function_code)(&recycleListSizeL)));
      oALL_RECYCLE_LISTSo->reverse();
      while (totalsize > maxsize) {
        { RecycleList* list = NULL;
          Cons* iter001 = oALL_RECYCLE_LISTSo->theConsList;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            list = ((RecycleList*)(iter001->value));
            if (totalsize <= maxsize) {
              break;
            }
            listsize = list->itemSize * list->currentLength;
            if (listsize > 0) {
              totalsize = totalsize - listsize;
            }
            else {
              continue;
            }
            reduceRecycleListSize(list, 0.5);
            totalsize = totalsize + (list->itemSize * list->currentLength);
          }
        }
      }
    }
  }
}

boolean RecycleList::deletedP() {
  { RecycleList* self = this;

    return (!((boolean)(self->recycleListOf)));
  }
}

boolean RecycleList::deletedPSetter(boolean value) {
  { RecycleList* self = this;

    if (value) {
      self->recycleListOf = NULL;
    }
    else {
      if (!((boolean)(self->recycleListOf))) {
        self->recycleListOf = SGT_DEFCLASS_STELLA_UNKNOWN;
      }
    }
    return (value);
  }
}

int recycleListSize(RecycleList* list) {
  return (list->itemSize * list->currentLength);
}

int totalRecycleListsSize() {
  { int size = 0;

    { RecycleList* list = NULL;
      Cons* iter000 = oALL_RECYCLE_LISTSo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        list = ((RecycleList*)(iter000->value));
        size = size + (list->itemSize * list->currentLength);
      }
    }
    return (size);
  }
}

boolean recycleListSizeL(RecycleList* list1, RecycleList* list2) {
  return ((list1->itemSize * list1->currentLength) < (list2->itemSize * list2->currentLength));
}

void reduceRecycleListSize(RecycleList* list, double fraction) {
  { int length = list->currentLength;
    int reducedlength = stella::floor(length * fraction);
    Surrogate* itemtype = list->recycleListOf;
    Object* cursor = NULL;
    Object* trailingcursor = NULL;
    Object* unused = NULL;
    StorageSlot* nextslot = NULL;

    if ((((boolean)(list->allItems)) ||
        ((boolean)(list->recycledItems))) &&
        (!subtypeOfP(itemtype, SGT_DEFCLASS_STELLA_STANDARD_OBJECT))) {
      clearRecycleList(list);
      return;
    }
    oRECYCLING_ENABLEDpo = false;
    if (((boolean)(list->allItems))) {
      cursor = list->allItems;
      unused = list->unusedItems;
      nextslot = ((StorageSlot*)(lookupSlot(((Class*)(itemtype->surrogateValue)), SYM_DEFCLASS_STELLA_NEXT_SWEEP_LIST_OBJECT)));
      { int i = NULL_INTEGER;
        int iter000 = 1;
        int upperBound000 = length - reducedlength;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          i = i;
          if (cursor == unused) {
            list->unusedItems = list->allItems;
          }
          trailingcursor = cursor;
          cursor = readSlotValue(((StandardObject*)(cursor)), nextslot);
          putSlotValue(((StandardObject*)(trailingcursor)), nextslot, NULL);
        }
      }
      if (eqlP(list->unusedItems, list->allItems)) {
        list->unusedItems = cursor;
      }
      list->allItems = cursor;
    }
    if (list->listOfRecycledItems->nonEmptyP()) {
      cursor = list->listOfRecycledItems->theConsList->nthRest(reducedlength);
      if (((boolean)(cursor))) {
        ((Cons*)(cursor))->rest = NIL;
      }
    }
    else if (((boolean)(list->recycledItems))) {
      if (((boolean)(list->allItems))) {
        list->recycledItems = NULL;
      }
      else {
        cursor = list->recycledItems;
        nextslot = recycleSlot(((Class*)(itemtype->surrogateValue)));
        { int i = NULL_INTEGER;
          int iter001 = 2;
          int upperBound001 = reducedlength;
          boolean unboundedP000 = upperBound001 == NULL_INTEGER;

          for  (; unboundedP000 ||
                    (iter001 <= upperBound001); 
                iter001 = iter001 + 1) {
            i = iter001;
            cursor = readSlotValue(((StandardObject*)(cursor)), nextslot);
            if (!((boolean)(cursor))) {
              break;
            }
          }
        }
        if (((boolean)(cursor))) {
          putSlotValue(((StandardObject*)(cursor)), nextslot, NULL);
        }
      }
    }
    list->currentLength = reducedlength;
    oRECYCLING_ENABLEDpo = true;
  }
}

void Object::sweep() {
  // Default method.  Sweep up all `self'-type objects.
  { Object* self = this;

  }
}

void sweepTransients() {
  { RecycleList* recyclelist = NULL;
    Cons* iter000 = oALL_RECYCLE_LISTSo->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      recyclelist = ((RecycleList*)(iter000->value));
      if (((boolean)(recyclelist->allItems)) &&
          isaP(recyclelist->allItems, SGT_DEFCLASS_STELLA_TRANSIENT_MIXIN)) {
        recyclelist->allItems->sweep();
      }
    }
  }
  freeTransientSymbols();
}

List* makeNonRecycledList() {
  { List* list = new List();

    list->theConsList = NIL;
    return (list);
  }
}

// During recycle list debugging holds all items that live in
// some free list.  Depending on program behavior, this table can get quite large!
HashTable* oCURRENTLY_RECYCLED_ITEMSo = NULL;

void registerRecycledItem(Object* item) {
  if (((boolean)(oCURRENTLY_RECYCLED_ITEMSo->lookup(item)))) {
    breakProgram("Trying to recyle an already recycled item!");
  }
  else {
    oCURRENTLY_RECYCLED_ITEMSo->insertAt(item, item);
  }
}

void unregisterRecycledItem(Object* item) {
  oCURRENTLY_RECYCLED_ITEMSo->removeAt(item);
}

void startRecycleListDebugging() {
  oCURRENTLY_RECYCLED_ITEMSo = NULL;
  clearRecycleLists();
  oCURRENTLY_RECYCLED_ITEMSo = newHashTable();
}

void stopRecycleListDebugging() {
  oCURRENTLY_RECYCLED_ITEMSo = NULL;
}

boolean recycleListDebuggingEnabledP() {
  return (((boolean)(oCURRENTLY_RECYCLED_ITEMSo)));
}

boolean oTRANSLATE_WITH_RECYCLE_LIST_DEBUGGINGpo = false;

boolean translateWithRecycleListDebuggingP() {
  return (oTRANSLATE_WITH_RECYCLE_LIST_DEBUGGINGpo);
}

Cons* yieldRegisterRecycledItemTrees() {
  if (oTRANSLATE_WITH_RECYCLE_LIST_DEBUGGINGpo) {
    return (cons(listO(4, SYM_DEFCLASS_STELLA_WHEN, cons(SYM_DEFCLASS_STELLA_RECYCLE_LIST_DEBUGGING_ENABLEDp, NIL), listO(3, SYM_DEFCLASS_STELLA_REGISTER_RECYCLED_ITEM, SYM_DEFCLASS_STELLA_SELF, NIL), NIL), NIL));
  }
  else {
    return (NIL);
  }
}

Cons* yieldUnregisterRecycledItemTrees() {
  if (oTRANSLATE_WITH_RECYCLE_LIST_DEBUGGINGpo) {
    return (cons(listO(4, SYM_DEFCLASS_STELLA_WHEN, cons(SYM_DEFCLASS_STELLA_RECYCLE_LIST_DEBUGGING_ENABLEDp, NIL), listO(3, SYM_DEFCLASS_STELLA_UNREGISTER_RECYCLED_ITEM, SYM_DEFCLASS_STELLA_SELF, NIL), NIL), NIL));
  }
  else {
    return (NIL);
  }
}

boolean hasNonNullDefaultValueP(StorageSlot* slot) {
  { Object* defaultform = slot->systemDefaultValue();

    return (((boolean)(defaultform)) &&
        (!equalConsTreesP(typeToWalkedNullValueTree(slot->typeSpecifier(), slot->type()), defaultform)));
  }
}

boolean systemDefinedSlotReaderP(StorageSlot* slot) {
  return ((!((boolean)(slot->reader()))) &&
      (hasNonNullDefaultValueP(slot) ||
       (slot->activeP() ||
        slot->slotHardwiredP)));
}

boolean systemDefinedSlotWriterP(StorageSlot* slot) {
  return ((!((boolean)(slot->writer()))) &&
      slot->activeP());
}

Object* yieldSlotTypeTree(StorageSlot* slot) {
  return (yieldTypeSpecTree((((boolean)(((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_DEFCLASS_STELLA_SLOT_TYPE_SPECIFIER, NULL))))) ? ((StandardObject*)(((CompoundTypeSpecifier*)(dynamicSlotValue(slot->dynamicSlots, SYM_DEFCLASS_STELLA_SLOT_TYPE_SPECIFIER, NULL))))) : ((StandardObject*)(slot->slotBaseType)))));
}

Symbol* yieldHardwiredSlotVariable(StorageSlot* slot) {
  return (internDerivedSymbol(slot->slotName, stringConcatenate("*HARDWIRED-", slot->slotName->symbolName, 3, "-ON-", slot->slotOwner->symbolName, "*")));
}

Cons* yieldHardwiredSlotReaderBody(StorageSlot* slot, Cons*& _Return1) {
  { Symbol* slotvariable = yieldHardwiredSlotVariable(slot);
    Object* slottypedesc = yieldTypeSpecTree(slot->computeReturnTypeSpec(slot->slotOwner));

    { Cons* _Return0 = listO(3, SYM_DEFCLASS_STELLA_RETURN, slotvariable, NIL);

      _Return1 = listO(3, SYM_DEFCLASS_STELLA_DEFGLOBAL, slotvariable, cons(slottypedesc, cons(SYM_DEFCLASS_STELLA_NULL, NIL)));
      return (_Return0);
    }
  }
}

void finalizeAuxiliaryMethod(MethodSlot* method) {
  if ((!((boolean)(method->slotBaseType))) &&
      ((boolean)(((CompoundTypeSpecifier*)(dynamicSlotValue(method->dynamicSlots, SYM_DEFCLASS_STELLA_SLOT_TYPE_SPECIFIER, NULL)))))) {
    method->slotBaseType = validateTypeSpecifier(((CompoundTypeSpecifier*)(dynamicSlotValue(method->dynamicSlots, SYM_DEFCLASS_STELLA_SLOT_TYPE_SPECIFIER, NULL))), ((Class*)(method->slotOwner->surrogateValue)), false);
  }
}

Cons* wrapWithDefaultValueAndReturnCode(StorageSlot* slot, Object* defaultexpression) {
  { StandardObject* dummy1;
    StandardObject* dummy2;

    { Cons* readcode = listO(4, SYM_DEFCLASS_STELLA_SLOT_VALUE, SYM_DEFCLASS_STELLA_SELF, slot->slotName, NIL);

      if (((boolean)(defaultexpression))) {
        if (slot->type() == SGT_DEFCLASS_STELLA_BOOLEAN) {
          if (!(slot->allocation() == KWD_DEFCLASS_DYNAMIC)) {
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              signalTranslationWarning();
              if (!(suppressWarningsP())) {
                printErrorContext(">> WARNING: ", STANDARD_WARNING);
                *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Ignoring :default annotation on non-dynamic BOOLEAN slot " << "`" << deUglifyParseTree(slot) << "'" << "." << std::endl << " Limited :default support is available for dynamic BOOLEAN " << "slots," << std::endl << " and full support for THREE-VALUED-BOOLEAN slots" << "." << std::endl;
              }
            }
          }
          else {
            {
              setLiteralTypeInfo(SGT_DEFCLASS_STELLA_BOOLEAN, KWD_DEFCLASS_NULL_WRAPPER, listO(3, SYM_DEFCLASS_STELLA_INLINE_WRAP_BOOLEAN, defaultexpression, NIL));
              pushVariableBinding(SYM_DEFCLASS_STELLA_SELF, slot->slotOwner);
              readcode = sysTree(walkExpressionTree(readcode, SGT_DEFCLASS_STELLA_BOOLEAN, slot->slotName, false, dummy2), SGT_DEFCLASS_STELLA_BOOLEAN, dummy1);
              popVariableBinding();
              setLiteralTypeInfo(SGT_DEFCLASS_STELLA_BOOLEAN, KWD_DEFCLASS_NULL_WRAPPER, SYM_DEFCLASS_STELLA_FALSE_WRAPPER);
            }
          }
          return (listO(3, SYM_DEFCLASS_STELLA_RETURN, readcode, NIL));
        }
        else {
          return (listO(4, SYM_DEFCLASS_STELLA_LET, cons(listO(3, SYM_DEFCLASS_STELLA_ANSWER, readcode, NIL), NIL), listO(5, SYM_DEFCLASS_STELLA_IF, listO(3, SYM_DEFCLASS_STELLA_NULLp, SYM_DEFCLASS_STELLA_ANSWER, NIL), listO(3, SYM_DEFCLASS_STELLA_RETURN, copyConsTree(defaultexpression), NIL), listO(3, SYM_DEFCLASS_STELLA_RETURN, SYM_DEFCLASS_STELLA_ANSWER, NIL), NIL), NIL));
        }
      }
      else {
        return (listO(3, SYM_DEFCLASS_STELLA_RETURN, readcode, NIL));
      }
    }
  }
}

Cons* yieldSlotReaderTree(StorageSlot* slot, Class* clasS) {
  { Cons* parameters = cons(listO(3, SYM_DEFCLASS_STELLA_SELF, internSymbolInModule(clasS->classType->symbolName, ((Module*)(clasS->classType->homeContext)), true), NIL), NIL);
    Object* typetree = yieldSlotTypeTree(slot);
    Object* defaultexpression = (hasNonNullDefaultValueP(slot) ? slot->systemDefaultValue() : ((Object*)(NULL)));
    boolean slotvisibleP = subtypeOfP(clasS->classType, slot->slotOwner);
    Cons* readcode = NULL;
    Cons* auxiliarycode = NULL;

    if (!slotvisibleP) {
      readcode = listO(4, SYM_DEFCLASS_STELLA_PROGN, listO(4, SYM_DEFCLASS_STELLA_ERROR, wrapString("Slot '"), wrapString(slot->slotName->symbolName), listO(3, wrapString("' does not exist on "), SYM_DEFCLASS_STELLA_SELF, NIL)), listO(3, SYM_DEFCLASS_STELLA_RETURN, SYM_DEFCLASS_STELLA_NULL, NIL), NIL);
    }
    else if (slot->activeP()) {
      readcode = yieldActiveSlotReaderBody(slot, defaultexpression);
    }
    else if (slot->slotHardwiredP) {
      readcode = yieldHardwiredSlotReaderBody(slot, auxiliarycode);
      if (clasS->classType == slot->slotOwner) {
        walkAuxiliaryTree(auxiliarycode);
      }
    }
    else {
      readcode = wrapWithDefaultValueAndReturnCode(slot, defaultexpression);
    }
    return (listO(4, SYM_DEFCLASS_STELLA_DEFMETHOD, cons(slot->slotName, cons(typetree, NIL)), parameters, listO(4, KWD_DEFCLASS_AUXILIARYp, SYM_DEFCLASS_STELLA_TRUE, readcode, NIL)));
  }
}

Cons* yieldSlotWriterTree(StorageSlot* slot, Class* clasS) {
  { Object* typetree = yieldSlotTypeTree(slot);
    Cons* parameters = listO(3, listO(3, SYM_DEFCLASS_STELLA_SELF, internSymbolInModule(clasS->classType->symbolName, ((Module*)(clasS->classType->homeContext)), true), NIL), listO(3, SYM_DEFCLASS_STELLA_VALUE, typetree, NIL), NIL);
    boolean slotvisibleP = subtypeOfP(clasS->classType, slot->slotOwner);
    Cons* writecode = NULL;

    if (!slotvisibleP) {
      writecode = listO(4, SYM_DEFCLASS_STELLA_PROGN, listO(4, SYM_DEFCLASS_STELLA_ERROR, wrapString("Slot '"), wrapString(slot->slotName->symbolName), listO(3, wrapString("' does not exist on "), SYM_DEFCLASS_STELLA_SELF, NIL)), listO(3, SYM_DEFCLASS_STELLA_RETURN, SYM_DEFCLASS_STELLA_NULL, NIL), NIL);
    }
    else if (slot->activeP()) {
      writecode = yieldActiveSlotWriterBody(slot);
    }
    else {
      writecode = listO(3, SYM_DEFCLASS_STELLA_RETURN, listO(4, SYM_DEFCLASS_STELLA_SETF, listO(4, SYM_DEFCLASS_STELLA_SLOT_VALUE, SYM_DEFCLASS_STELLA_SELF, slot->slotName, NIL), SYM_DEFCLASS_STELLA_VALUE, NIL), NIL);
    }
    return (listO(4, SYM_DEFCLASS_STELLA_DEFMETHOD, cons(yieldSetterMethodName(slot->slotName), cons(copyConsTree(typetree), NIL)), parameters, listO(3, KWD_DEFCLASS_AUXILIARYp, SYM_DEFCLASS_STELLA_TRUE, ((slotvisibleP ? NIL : cons(listO(3, SYM_DEFCLASS_STELLA_IGNORE, SYM_DEFCLASS_STELLA_VALUE, NIL), NIL)))->concatenate(cons(writecode, NIL), 0))));
  }
}

boolean slotValueIsBareLiteralP(Slot* slot) {
  { Surrogate* type = slot->type();

    return (((boolean)(type)) &&
        (((boolean)(((Class*)(type->surrogateValue)))) &&
         subtypeOfP(slot->type(), SGT_DEFCLASS_STELLA_LITERAL)));
  }
}

boolean genericallyAccessibleTypeP(Surrogate* type) {
  return (subtypeOfP(type, SGT_DEFCLASS_STELLA_OBJECT) ||
      (subtypeOfP(type, SGT_DEFCLASS_STELLA_LITERAL) &&
       ((boolean)(lookupLiteralTypeInfo(type, KWD_DEFCLASS_WRAP_FUNCTION)))));
}

boolean genericSlotReaderP(StorageSlot* slot, Class* clasS) {
  if ((!slot->abstractP) &&
      (subtypeOfP(slot->slotOwner, SGT_DEFCLASS_STELLA_OBJECT) &&
       (nativeSlotHome(slot, clasS) == clasS))) {
    { Surrogate* type = canonicalType(typeSpecToBaseType(computeRealSlotType(slot, clasS->classType, canonicalType(slot->type()))));

      if (((boolean)(((Class*)(type->surrogateValue)))) &&
          genericallyAccessibleTypeP(type)) {
        return (true);
      }
    }
  }
  return (false);
}

boolean genericSlotWriterP(StorageSlot* slot, Class* clasS) {
  return ((!slot->slotHardwiredP) &&
      genericSlotReaderP(slot, clasS));
}

boolean slotAccessMethodP(StorageSlot* slot) {
  return (((boolean)(slot->reader())) ||
      (systemDefinedSlotReaderP(slot) ||
       (((boolean)(slot->writer())) ||
        systemDefinedSlotWriterP(slot))));
}

Symbol* yieldGenericSlotAccessorName(Class* clasS) {
  { const char* baseName = clasS->classType->symbolName;
    const char* prefix = (allUpperCaseStringP(baseName) ? "ACCESS-" : "access-");
    const char* suffix = (allUpperCaseStringP(baseName) ? "-SLOT-VALUE" : "-Slot-Value");

    return (internDerivedSymbol(clasS->classType, stringConcatenate(prefix, baseName, 1, suffix)));
  }
}

Cons* yieldGenericSlotAccessorDefinition(Class* clasS) {
  { Cons* clauses = NIL;
    Cons* accesstree = NIL;
    Object* valuetree = NULL;
    Surrogate* slottype = NULL;

    if (!subclassOfP(clasS, ((Class*)(SGT_DEFCLASS_STELLA_OBJECT->surrogateValue)))) {
      return (NULL);
    }
    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();

      for (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if (storageSlotP(slot) &&
            genericSlotReaderP(((StorageSlot*)(slot)), clasS)) {
          if (slot->slotExternalP ||
              (spaceSaverSlotAllocationP(((StorageSlot*)(slot))) &&
               (!slotAccessMethodP(((StorageSlot*)(slot)))))) {
            continue;
          }
          accesstree = listO(4, SYM_DEFCLASS_STELLA_SETQ, SYM_DEFCLASS_STELLA_VALUE, cons(slot->slotName, cons(SYM_DEFCLASS_STELLA_SELF, NIL)), NIL);
          if (!((StorageSlot*)(slot))->slotHardwiredP) {
            slottype = canonicalType(slot->type());
            valuetree = SYM_DEFCLASS_STELLA_VALUE;
            if (subtypeOfP(slottype, SGT_DEFCLASS_STELLA_LITERAL) &&
                ((boolean)(lookupLiteralTypeInfo(slottype, KWD_DEFCLASS_WRAP_FUNCTION)))) {
              valuetree = listO(4, SYM_DEFCLASS_STELLA_CAST, SYM_DEFCLASS_STELLA_VALUE, slottype->typeToWrappedType(), NIL);
            }
            accesstree = listO(5, SYM_DEFCLASS_STELLA_IF, SYM_DEFCLASS_STELLA_SETVALUEp, listO(4, SYM_DEFCLASS_STELLA_SETF, cons(slot->slotName, cons(SYM_DEFCLASS_STELLA_SELF, NIL)), valuetree, NIL), accesstree, NIL);
          }
          clauses = cons(cons(slot->slotName, cons(accesstree, NIL)), clauses);
        }
      }
    }
    if (subclassOfP(clasS, ((Class*)(SGT_DEFCLASS_STELLA_DYNAMIC_SLOTS_MIXIN->surrogateValue)))) {
      { Cons* renameclauses = NIL;

        { Slot* slot = NULL;
          Cons* iter001 = clasS->classLocalSlots->theConsList;
          Cons* collect000 = NULL;

          for  (; !(iter001 == NIL); 
                iter001 = iter001->rest) {
            slot = ((Slot*)(iter001->value));
            if (storageSlotP(slot) &&
                ((!slot->slotExternalP) &&
                 (spaceSaverSlotAllocationP(((StorageSlot*)(slot))) &&
                  ((!slotAccessMethodP(((StorageSlot*)(slot)))) &&
                   (!(slot == canonicalSlot(((StorageSlot*)(slot))))))))) {
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(cons(slot->slotName, cons(listO(4, SYM_DEFCLASS_STELLA_SETQ, SYM_DEFCLASS_STELLA_SLOTNAME, listO(3, SYM_DEFCLASS_STELLA_QUOTE, canonicalSlot(((StorageSlot*)(slot)))->slotName, NIL), NIL), NIL)), NIL);
                  if (renameclauses == NIL) {
                    renameclauses = collect000;
                  }
                  else {
                    addConsToEndOfConsList(renameclauses, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(cons(slot->slotName, cons(listO(4, SYM_DEFCLASS_STELLA_SETQ, SYM_DEFCLASS_STELLA_SLOTNAME, listO(3, SYM_DEFCLASS_STELLA_QUOTE, canonicalSlot(((StorageSlot*)(slot)))->slotName, NIL), NIL), NIL)), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
        }
        if (!(renameclauses == NIL)) {
          renameclauses = cons(listO(3, SYM_DEFCLASS_STELLA_CASE, SYM_DEFCLASS_STELLA_SLOTNAME, renameclauses->concatenate(cons(listO(3, SYM_DEFCLASS_STELLA_OTHERWISE, SYM_DEFCLASS_STELLA_NULL, NIL), NIL), 0)), NIL);
        }
        clauses = cons(cons(SYM_DEFCLASS_STELLA_OTHERWISE, renameclauses->concatenate(cons(listO(5, SYM_DEFCLASS_STELLA_IF, SYM_DEFCLASS_STELLA_SETVALUEp, listO(6, SYM_DEFCLASS_STELLA_SET_DYNAMIC_SLOT_VALUE, listO(3, SYM_DEFCLASS_STELLA_DYNAMIC_SLOTS, SYM_DEFCLASS_STELLA_SELF, NIL), SYM_DEFCLASS_STELLA_SLOTNAME, SYM_DEFCLASS_STELLA_VALUE, SYM_DEFCLASS_STELLA_NULL, NIL), listO(4, SYM_DEFCLASS_STELLA_SETQ, SYM_DEFCLASS_STELLA_VALUE, listO(4, SYM_DEFCLASS_STELLA_LOOKUP, listO(3, SYM_DEFCLASS_STELLA_DYNAMIC_SLOTS, SYM_DEFCLASS_STELLA_SELF, NIL), SYM_DEFCLASS_STELLA_SLOTNAME, NIL), NIL), NIL), NIL), 0)), clauses);
      }
    }
    if (clauses == NIL) {
      return (NULL);
    }
    else {
      return (listO(6, SYM_DEFCLASS_STELLA_DEFUN, cons(yieldGenericSlotAccessorName(clasS), cons(SYM_DEFCLASS_STELLA_OBJECT, NIL)), listO(5, listO(3, SYM_DEFCLASS_STELLA_SELF, clasS->classType, NIL), listO(3, SYM_DEFCLASS_STELLA_SLOTNAME, SYM_DEFCLASS_STELLA_SYMBOL, NIL), listO(3, SYM_DEFCLASS_STELLA_VALUE, SYM_DEFCLASS_STELLA_OBJECT, NIL), listO(3, SYM_DEFCLASS_STELLA_SETVALUEp, SYM_DEFCLASS_STELLA_BOOLEAN, NIL), NIL), listO(3, SYM_DEFCLASS_STELLA_CASE, SYM_DEFCLASS_STELLA_SLOTNAME, clauses->reverse()->concatenate(NIL, 0)), listO(3, SYM_DEFCLASS_STELLA_RETURN, SYM_DEFCLASS_STELLA_VALUE, NIL), NIL));
    }
  }
}

void createGenericSlotAccessorUnit(Class* clasS) {
  { Cons* tree = yieldGenericSlotAccessorDefinition(clasS);

    if (((boolean)(tree))) {
      walkAuxiliaryTree(tree);
    }
  }
}

Cons* yieldGenericSlotAccessorAttachment(Class* clasS, Symbol* classref) {
  { boolean foundP000 = false;

    { Slot* slot = NULL;
      Iterator* iter000 = clasS->classSlots();

      for (; iter000->nextP(); ) {
        slot = ((Slot*)(iter000->value));
        if (storageSlotP(slot) &&
            genericSlotReaderP(((StorageSlot*)(slot)), clasS)) {
          foundP000 = true;
          break;
        }
      }
    }
    if (foundP000) {
      return (cons(listO(4, SYM_DEFCLASS_STELLA_SETF, listO(3, SYM_DEFCLASS_STELLA_CLASS_SLOT_ACCESSOR_CODE, classref, NIL), listO(4, SYM_DEFCLASS_STELLA_THE_CODE, KWD_DEFCLASS_FUNCTION, yieldGenericSlotAccessorName(clasS), NIL), NIL), NIL));
    }
    else {
      return (NIL);
    }
  }
}

cpp_function_code getGenericSlotAccessor(StorageSlot* slot, Class* clasS, boolean warnP) {
  // Return the accessor code to read `slot' on an object of type `class',
  // or NULL if no such accessor exists.  In that case, print a warning if `warn?' is TRUE.
  // NOTE: the accessor expects `canonical-slot-name's (which see).
  slot = canonicalSlot(slot);
  { boolean slotvisibleP = subclassOfP(clasS, ((Class*)(slot->slotOwner->surrogateValue)));
    Class* nativehome = nativeSlotHome(slot, clasS);
    boolean slotreadableP = ((boolean)(nativehome)) &&
        genericSlotReaderP(slot, nativehome);
    cpp_function_code accessorcode = ((slotvisibleP &&
        slotreadableP) ? nativeSlotHome(slot, clasS)->classSlotAccessorCode : ((cpp_function_code)(NULL)));

    if ((accessorcode == NULL) &&
        warnP) {
      if (slotvisibleP) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "No generic slot accessor available for " << "`" << slot << "'" << std::endl;
      }
      else {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "Slot " << "`" << slot << "'" << " does not exist on objects of type " << "`" << clasS->classType << "'" << std::endl;
      }
    }
    return (accessorcode);
  }
}

Cons* yieldMixinClassUsersTree(Class* clasS) {
  { Cons* result = NIL;

    { Surrogate* sub = NULL;
      Cons* iter000 = clasS->classDirectSubs->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        sub = ((Surrogate*)(iter000->value));
        if (!typeToClass(sub)->mixinP) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(internSymbolInModule(sub->symbolName, ((Module*)(sub->homeContext)), true), NIL);
              if (result == NIL) {
                result = collect000;
              }
              else {
                addConsToEndOfConsList(result, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(internSymbolInModule(sub->symbolName, ((Module*)(sub->homeContext)), true), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (result);
  }
}

Symbol* yieldMixinSlotReaderName(StorageSlot* slot) {
  { const char* preName = slot->slotName->symbolName;
    const char* postName = slot->slotOwner->symbolName;
    const char* infix = ((allUpperCaseStringP(preName) &&
        allUpperCaseStringP(postName)) ? "-ON-" : "-On-");

    return (internDerivedSymbol(slot->slotName, stringConcatenate(preName, infix, 1, postName)));
  }
}

Symbol* yieldMixinSlotWriterName(StorageSlot* slot) {
  return (yieldSetterMethodName(yieldMixinSlotReaderName(slot)));
}

Cons* yieldMixinSlotReaderTree(StorageSlot* slot) {
  { Symbol* readername = yieldMixinSlotReaderName(slot);
    Object* typetree = yieldSlotTypeTree(slot);

    return (listO(7, SYM_DEFCLASS_STELLA_DEFUN, cons(readername, cons(typetree, NIL)), cons(listO(3, SYM_DEFCLASS_STELLA_SELF, SYM_DEFCLASS_STELLA_OBJECT, NIL), NIL), KWD_DEFCLASS_AUXILIARYp, SYM_DEFCLASS_STELLA_TRUE, listO(5, SYM_DEFCLASS_STELLA_TYPECASE, SYM_DEFCLASS_STELLA_SELF, cons(yieldMixinClassUsersTree(((Class*)(slot->slotOwner->surrogateValue))), cons(listO(3, SYM_DEFCLASS_STELLA_RETURN, cons(slot->slotName, cons(SYM_DEFCLASS_STELLA_SELF, NIL)), NIL), NIL)), listO(3, SYM_DEFCLASS_STELLA_OTHERWISE, listO(3, SYM_DEFCLASS_STELLA_RETURN, SYM_DEFCLASS_STELLA_NULL, NIL), NIL), NIL), NIL));
  }
}

Cons* yieldMixinSlotWriterTree(StorageSlot* slot) {
  { Symbol* writername = yieldMixinSlotWriterName(slot);
    Object* typetree = yieldSlotTypeTree(slot);

    return (listO(7, SYM_DEFCLASS_STELLA_DEFUN, cons(writername, cons(typetree, NIL)), listO(3, listO(3, SYM_DEFCLASS_STELLA_SELF, SYM_DEFCLASS_STELLA_OBJECT, NIL), listO(3, SYM_DEFCLASS_STELLA_VALUE, copyConsTree(typetree), NIL), NIL), KWD_DEFCLASS_AUXILIARYp, SYM_DEFCLASS_STELLA_TRUE, listO(5, SYM_DEFCLASS_STELLA_TYPECASE, SYM_DEFCLASS_STELLA_SELF, cons(yieldMixinClassUsersTree(((Class*)(slot->slotOwner->surrogateValue))), cons(listO(3, SYM_DEFCLASS_STELLA_RETURN, listO(4, SYM_DEFCLASS_STELLA_SETF, cons(slot->slotName, cons(SYM_DEFCLASS_STELLA_SELF, NIL)), SYM_DEFCLASS_STELLA_VALUE, NIL), NIL), NIL)), listO(3, SYM_DEFCLASS_STELLA_OTHERWISE, listO(3, SYM_DEFCLASS_STELLA_RETURN, SYM_DEFCLASS_STELLA_NULL, NIL), NIL), NIL), NIL));
  }
}

Symbol* yieldNativeSlotReaderName(StorageSlot* slot) {
  { const char* baseName = slot->slotName->symbolName;
    const char* suffix = (allUpperCaseStringP(baseName) ? "-NATIVE-VALUE" : "-Native-Value");

    return (internDerivedSymbol(slot->slotName, stringConcatenate(baseName, suffix, 0)));
  }
}

Symbol* yieldNativeSlotWriterName(StorageSlot* slot) {
  return (yieldSetterMethodName(yieldNativeSlotReaderName(slot)));
}

Cons* yieldNativeSlotReaderTree(StorageSlot* slot, Class* clasS) {
  { Symbol* readername = yieldNativeSlotReaderName(slot);
    Object* typetree = yieldSlotTypeTree(slot);
    boolean slotvisibleP = subtypeOfP(clasS->classType, slot->slotOwner);

    return (listO(6, SYM_DEFCLASS_STELLA_DEFMETHOD, cons(readername, cons(typetree, NIL)), cons(listO(3, SYM_DEFCLASS_STELLA_SELF, classSymbol(clasS), NIL), NIL), KWD_DEFCLASS_AUXILIARYp, SYM_DEFCLASS_STELLA_TRUE, ((slotvisibleP ? cons(listO(3, SYM_DEFCLASS_STELLA_RETURN, listO(4, SYM_DEFCLASS_STELLA_SLOT_VALUE, SYM_DEFCLASS_STELLA_SELF, slot->slotName, listO(3, KWD_DEFCLASS_CONTEXT_SENSITIVEp, SYM_DEFCLASS_STELLA_FALSE, NIL)), NIL), NIL) : listO(3, listO(4, SYM_DEFCLASS_STELLA_ERROR, wrapString("Slot '"), wrapString(slot->slotName->symbolName), listO(3, wrapString("' does not exist on "), SYM_DEFCLASS_STELLA_SELF, NIL)), listO(3, SYM_DEFCLASS_STELLA_RETURN, SYM_DEFCLASS_STELLA_NULL, NIL), NIL)))->concatenate(NIL, 0)));
  }
}

Cons* yieldNativeSlotWriterTree(StorageSlot* slot, Class* clasS) {
  { Symbol* writername = yieldNativeSlotWriterName(slot);
    Object* typetree = yieldSlotTypeTree(slot);
    boolean slotvisibleP = subtypeOfP(clasS->classType, slot->slotOwner);

    return (listO(6, SYM_DEFCLASS_STELLA_DEFMETHOD, cons(writername, cons(typetree, NIL)), listO(3, listO(3, SYM_DEFCLASS_STELLA_SELF, classSymbol(clasS), NIL), listO(3, SYM_DEFCLASS_STELLA_VALUE, copyConsTree(typetree), NIL), NIL), KWD_DEFCLASS_AUXILIARYp, SYM_DEFCLASS_STELLA_TRUE, ((slotvisibleP ? cons(listO(3, SYM_DEFCLASS_STELLA_RETURN, listO(4, SYM_DEFCLASS_STELLA_SETF, listO(4, SYM_DEFCLASS_STELLA_SLOT_VALUE, SYM_DEFCLASS_STELLA_SELF, slot->slotName, listO(3, KWD_DEFCLASS_CONTEXT_SENSITIVEp, SYM_DEFCLASS_STELLA_FALSE, NIL)), SYM_DEFCLASS_STELLA_VALUE, NIL), NIL), NIL) : listO(4, listO(3, SYM_DEFCLASS_STELLA_IGNORE, SYM_DEFCLASS_STELLA_VALUE, NIL), listO(4, SYM_DEFCLASS_STELLA_ERROR, wrapString("Slot '"), wrapString(slot->slotName->symbolName), listO(3, wrapString("' does not exist on "), SYM_DEFCLASS_STELLA_SELF, NIL)), listO(3, SYM_DEFCLASS_STELLA_RETURN, SYM_DEFCLASS_STELLA_NULL, NIL), NIL)))->concatenate(NIL, 0)));
  }
}

void createKeyedEqualityMethodUnit(Class* clasS) {
  { Cons* testtrees = NIL;

    { Slot* slotname = NULL;
      Cons* iter000 = clasS->classKey_reader()->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        slotname = ((Slot*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(listO(4, SYM_DEFCLASS_STELLA_EQp, cons(slotname, cons(SYM_DEFCLASS_STELLA_SELF, NIL)), cons(slotname, cons(SYM_DEFCLASS_STELLA_OTHER, NIL)), NIL), NIL);
            if (testtrees == NIL) {
              testtrees = collect000;
            }
            else {
              addConsToEndOfConsList(testtrees, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(listO(4, SYM_DEFCLASS_STELLA_EQp, cons(slotname, cons(SYM_DEFCLASS_STELLA_SELF, NIL)), cons(slotname, cons(SYM_DEFCLASS_STELLA_OTHER, NIL)), NIL), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    walkAuxiliaryTree(listO(5, SYM_DEFCLASS_STELLA_DEFMETHOD, listO(3, SYM_DEFCLASS_STELLA_EQUAL, SYM_DEFCLASS_STELLA_BOOLEAN, NIL), listO(3, listO(3, SYM_DEFCLASS_STELLA_SELF, classSymbol(clasS), NIL), SYM_DEFCLASS_STELLA_OTHER, NIL), listO(3, SYM_DEFCLASS_STELLA_RETURN, cons(SYM_DEFCLASS_STELLA_AND, testtrees->concatenate(NIL, 0)), NIL), NIL));
  }
}

boolean transientObjectP(Object* object) {
  { Surrogate* type = object->primaryType();

    return (subtypeOfP(type, SGT_DEFCLASS_STELLA_TRANSIENT_MIXIN));
  }
}

void helpStartupDefclass1() {
  {
    SGT_DEFCLASS_STELLA_LITERAL = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL", NULL, 1)));
    SGT_DEFCLASS_STELLA_SECOND_CLASS_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("SECOND-CLASS-OBJECT", NULL, 1)));
    SYM_DEFCLASS_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    KWD_DEFCLASS_COMMON_LISP = ((Keyword*)(internRigidSymbolWrtModule("COMMON-LISP", NULL, 2)));
    SYM_DEFCLASS_STELLA_VERBATIM = ((Symbol*)(internRigidSymbolWrtModule("VERBATIM", NULL, 0)));
    SYM_DEFCLASS_STELLA_DEFINE_CLASS_FROM_STRINGIFIED_SOURCE = ((Symbol*)(internRigidSymbolWrtModule("DEFINE-CLASS-FROM-STRINGIFIED-SOURCE", NULL, 0)));
    SYM_DEFCLASS_STELLA_CLASS_CL_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CL-NATIVE-TYPE", NULL, 0)));
    KWD_DEFCLASS_IDL = ((Keyword*)(internRigidSymbolWrtModule("IDL", NULL, 2)));
    SYM_DEFCLASS_STELLA_CLASS_IDL_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-IDL-NATIVE-TYPE", NULL, 0)));
    KWD_DEFCLASS_JAVA = ((Keyword*)(internRigidSymbolWrtModule("JAVA", NULL, 2)));
    SYM_DEFCLASS_STELLA_CLASS_JAVA_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-JAVA-NATIVE-TYPE", NULL, 0)));
    KWD_DEFCLASS_CPP = ((Keyword*)(internRigidSymbolWrtModule("CPP", NULL, 2)));
    KWD_DEFCLASS_CPP_STANDALONE = ((Keyword*)(internRigidSymbolWrtModule("CPP-STANDALONE", NULL, 2)));
    SYM_DEFCLASS_STELLA_CLASS_CPP_NATIVE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CPP-NATIVE-TYPE", NULL, 0)));
    SGT_DEFCLASS_STELLA_NON_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("NON-OBJECT", NULL, 1)));
    SGT_DEFCLASS_STELLA_NATIVE_EXCEPTION = ((Surrogate*)(internRigidSymbolWrtModule("NATIVE-EXCEPTION", NULL, 1)));
    KWD_DEFCLASS_DYNAMIC = ((Keyword*)(internRigidSymbolWrtModule("DYNAMIC", NULL, 2)));
    SYM_DEFCLASS_STELLA_SLOT_INITIAL_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SLOT-INITIAL-VALUE", NULL, 0)));
    KWD_DEFCLASS_BIT = ((Keyword*)(internRigidSymbolWrtModule("BIT", NULL, 2)));
    SGT_DEFCLASS_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 1)));
    KWD_DEFCLASS_CLASS = ((Keyword*)(internRigidSymbolWrtModule("CLASS", NULL, 2)));
    SYM_DEFCLASS_STELLA_SLOT_RENAMES = ((Symbol*)(internRigidSymbolWrtModule("SLOT-RENAMES", NULL, 0)));
    SGT_DEFCLASS_STELLA_UNKNOWN = ((Surrogate*)(internRigidSymbolWrtModule("UNKNOWN", NULL, 1)));
    SYM_DEFCLASS_STELLA_SLOT_TYPE_SPECIFIER = ((Symbol*)(internRigidSymbolWrtModule("SLOT-TYPE-SPECIFIER", NULL, 0)));
    SGT_DEFCLASS_STELLA_ANCHORED_TYPE_SPECIFIER = ((Surrogate*)(internRigidSymbolWrtModule("ANCHORED-TYPE-SPECIFIER", NULL, 1)));
    SYM_DEFCLASS_STELLA_NEXT_SWEEP_LIST_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("NEXT-SWEEP-LIST-OBJECT", NULL, 0)));
    KWD_DEFCLASS_FREE_LIST = ((Keyword*)(internRigidSymbolWrtModule("FREE-LIST", NULL, 2)));
    KWD_DEFCLASS_FREE_AND_SWEEP_LIST = ((Keyword*)(internRigidSymbolWrtModule("FREE-AND-SWEEP-LIST", NULL, 2)));
    KWD_DEFCLASS_SWEEP_LIST = ((Keyword*)(internRigidSymbolWrtModule("SWEEP-LIST", NULL, 2)));
    SYM_DEFCLASS_STELLA_CLASS_CREATOR = ((Symbol*)(internRigidSymbolWrtModule("CLASS-CREATOR", NULL, 0)));
    KWD_DEFCLASS_USE_COMMON_LISP_STRUCTS = ((Keyword*)(internRigidSymbolWrtModule("USE-COMMON-LISP-STRUCTS", NULL, 2)));
    KWD_DEFCLASS_USE_COMMON_LISP_VECTOR_STRUCTS = ((Keyword*)(internRigidSymbolWrtModule("USE-COMMON-LISP-VECTOR-STRUCTS", NULL, 2)));
    SYM_DEFCLASS_STELLA_DEFGLOBAL = ((Symbol*)(internRigidSymbolWrtModule("DEFGLOBAL", NULL, 0)));
    SYM_DEFCLASS_STELLA_RECYCLE_LIST = ((Symbol*)(internRigidSymbolWrtModule("RECYCLE-LIST", NULL, 0)));
    SYM_DEFCLASS_STELLA_OF = ((Symbol*)(internRigidSymbolWrtModule("OF", NULL, 0)));
    SYM_DEFCLASS_STELLA_CREATE_RECYCLE_LIST = ((Symbol*)(internRigidSymbolWrtModule("CREATE-RECYCLE-LIST", NULL, 0)));
    SYM_DEFCLASS_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", NULL, 0)));
    SYM_DEFCLASS_STELLA_SELF = ((Symbol*)(internRigidSymbolWrtModule("SELF", NULL, 0)));
    SYM_DEFCLASS_STELLA_MAKE = ((Symbol*)(internRigidSymbolWrtModule("MAKE", NULL, 0)));
    SYM_DEFCLASS_STELLA_WHEN = ((Symbol*)(internRigidSymbolWrtModule("WHEN", NULL, 0)));
    SYM_DEFCLASS_STELLA_DEFINEDp = ((Symbol*)(internRigidSymbolWrtModule("DEFINED?", NULL, 0)));
    SYM_DEFCLASS_STELLA_FREE = ((Symbol*)(internRigidSymbolWrtModule("FREE", NULL, 0)));
    SYM_DEFCLASS_STELLA_DYNAMIC_SLOTS = ((Symbol*)(internRigidSymbolWrtModule("DYNAMIC-SLOTS", NULL, 0)));
    SYM_DEFCLASS_STELLA_CLEAR = ((Symbol*)(internRigidSymbolWrtModule("CLEAR", NULL, 0)));
    SYM_DEFCLASS_STELLA_UNLESS = ((Symbol*)(internRigidSymbolWrtModule("UNLESS", NULL, 0)));
    SYM_DEFCLASS_STELLA_RETURN = ((Symbol*)(internRigidSymbolWrtModule("RETURN", NULL, 0)));
    KWD_DEFCLASS_FORCE_NULL_VALUE = ((Keyword*)(internRigidSymbolWrtModule("FORCE-NULL-VALUE", NULL, 2)));
    KWD_DEFCLASS_NULL_VALUE_ONLY = ((Keyword*)(internRigidSymbolWrtModule("NULL-VALUE-ONLY", NULL, 2)));
    SYM_DEFCLASS_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", NULL, 0)));
    SYM_DEFCLASS_STELLA_oRECYCLING_ENABLEDpo = ((Symbol*)(internRigidSymbolWrtModule("*RECYCLING-ENABLED?*", NULL, 0)));
    SYM_DEFCLASS_STELLA_COND = ((Symbol*)(internRigidSymbolWrtModule("COND", NULL, 0)));
    SYM_DEFCLASS_STELLA___ = ((Symbol*)(internRigidSymbolWrtModule("--", NULL, 0)));
    SYM_DEFCLASS_STELLA_CURRENT_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("CURRENT-LENGTH", NULL, 0)));
    SYM_DEFCLASS_STELLA_OTHERWISE = ((Symbol*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 0)));
    SYM_DEFCLASS_STELLA_RECYCLED_ITEMS = ((Symbol*)(internRigidSymbolWrtModule("RECYCLED-ITEMS", NULL, 0)));
    SYM_DEFCLASS_STELLA_POP = ((Symbol*)(internRigidSymbolWrtModule("POP", NULL, 0)));
    SYM_DEFCLASS_STELLA_LIST_OF_RECYCLED_ITEMS = ((Symbol*)(internRigidSymbolWrtModule("LIST-OF-RECYCLED-ITEMS", NULL, 0)));
    SYM_DEFCLASS_STELLA_SETF = ((Symbol*)(internRigidSymbolWrtModule("SETF", NULL, 0)));
    SYM_DEFCLASS_STELLA_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SLOT-VALUE", NULL, 0)));
    SYM_DEFCLASS_STELLA_UNUSED_ITEMS = ((Symbol*)(internRigidSymbolWrtModule("UNUSED-ITEMS", NULL, 0)));
  }
}

void helpStartupDefclass2() {
  {
    SYM_DEFCLASS_STELLA_ALL_ITEMS = ((Symbol*)(internRigidSymbolWrtModule("ALL-ITEMS", NULL, 0)));
    SYM_DEFCLASS_STELLA_ii = ((Symbol*)(internRigidSymbolWrtModule("++", NULL, 0)));
    SYM_DEFCLASS_STELLA_e = ((Symbol*)(internRigidSymbolWrtModule("=", NULL, 0)));
    SYM_DEFCLASS_STELLA_oRECYCLE_LISTS_MAINTENANCE_TIMERo = ((Symbol*)(internRigidSymbolWrtModule("*RECYCLE-LISTS-MAINTENANCE-TIMER*", NULL, 0)));
    SYM_DEFCLASS_STELLA_MAINTAIN_RECYCLE_LISTS = ((Symbol*)(internRigidSymbolWrtModule("MAINTAIN-RECYCLE-LISTS", NULL, 0)));
    KWD_DEFCLASS_INITIAL_VALUE_ONLY = ((Keyword*)(internRigidSymbolWrtModule("INITIAL-VALUE-ONLY", NULL, 2)));
    KWD_DEFCLASS_ANY_INITIAL_VALUE = ((Keyword*)(internRigidSymbolWrtModule("ANY-INITIAL-VALUE", NULL, 2)));
    KWD_DEFCLASS_CONTEXT_SENSITIVEp = ((Keyword*)(internRigidSymbolWrtModule("CONTEXT-SENSITIVE?", NULL, 2)));
    SYM_DEFCLASS_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", NULL, 0)));
    SYM_DEFCLASS_STELLA_CLASS_INITIALIZER = ((Symbol*)(internRigidSymbolWrtModule("CLASS-INITIALIZER", NULL, 0)));
    SYM_DEFCLASS_STELLA_RUN_CONSTRUCTOR_DEMONS = ((Symbol*)(internRigidSymbolWrtModule("RUN-CONSTRUCTOR-DEMONS", NULL, 0)));
    SYM_DEFCLASS_STELLA_DEFUN = ((Symbol*)(internRigidSymbolWrtModule("DEFUN", NULL, 0)));
    KWD_DEFCLASS_CONSTRUCTORp = ((Keyword*)(internRigidSymbolWrtModule("CONSTRUCTOR?", NULL, 2)));
    SYM_DEFCLASS_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    KWD_DEFCLASS_PUBLICp = ((Keyword*)(internRigidSymbolWrtModule("PUBLIC?", NULL, 2)));
    SYM_DEFCLASS_STELLA_LET = ((Symbol*)(internRigidSymbolWrtModule("LET", NULL, 0)));
    SYM_DEFCLASS_STELLA_MESSAGE = ((Symbol*)(internRigidSymbolWrtModule("MESSAGE", NULL, 0)));
    SYM_DEFCLASS_STELLA_CLASS_DESTRUCTOR = ((Symbol*)(internRigidSymbolWrtModule("CLASS-DESTRUCTOR", NULL, 0)));
    SYM_DEFCLASS_STELLA_DEFMETHOD = ((Symbol*)(internRigidSymbolWrtModule("DEFMETHOD", NULL, 0)));
    SGT_DEFCLASS_STELLA_STANDARD_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("STANDARD-OBJECT", NULL, 1)));
    SYM_DEFCLASS_STELLA_PUSH = ((Symbol*)(internRigidSymbolWrtModule("PUSH", NULL, 0)));
    SYM_DEFCLASS_STELLA_SWEEP = ((Symbol*)(internRigidSymbolWrtModule("SWEEP", NULL, 0)));
    SYM_DEFCLASS_STELLA_UNUSED = ((Symbol*)(internRigidSymbolWrtModule("UNUSED", NULL, 0)));
    SYM_DEFCLASS_STELLA_WHILE = ((Symbol*)(internRigidSymbolWrtModule("WHILE", NULL, 0)));
    SYM_DEFCLASS_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", NULL, 0)));
    SYM_DEFCLASS_STELLA_EQLp = ((Symbol*)(internRigidSymbolWrtModule("EQL?", NULL, 0)));
    SYM_DEFCLASS_STELLA_UNMAKE = ((Symbol*)(internRigidSymbolWrtModule("UNMAKE", NULL, 0)));
    SGT_DEFCLASS_STELLA_VOID = ((Surrogate*)(internRigidSymbolWrtModule("VOID", NULL, 1)));
    SGT_DEFCLASS_STELLA_TRANSIENT_MIXIN = ((Surrogate*)(internRigidSymbolWrtModule("TRANSIENT-MIXIN", NULL, 1)));
    SYM_DEFCLASS_STELLA_RECYCLE_LIST_DEBUGGING_ENABLEDp = ((Symbol*)(internRigidSymbolWrtModule("RECYCLE-LIST-DEBUGGING-ENABLED?", NULL, 0)));
    SYM_DEFCLASS_STELLA_REGISTER_RECYCLED_ITEM = ((Symbol*)(internRigidSymbolWrtModule("REGISTER-RECYCLED-ITEM", NULL, 0)));
    SYM_DEFCLASS_STELLA_UNREGISTER_RECYCLED_ITEM = ((Symbol*)(internRigidSymbolWrtModule("UNREGISTER-RECYCLED-ITEM", NULL, 0)));
    KWD_DEFCLASS_NULL_WRAPPER = ((Keyword*)(internRigidSymbolWrtModule("NULL-WRAPPER", NULL, 2)));
    SYM_DEFCLASS_STELLA_INLINE_WRAP_BOOLEAN = ((Symbol*)(internRigidSymbolWrtModule("INLINE-WRAP-BOOLEAN", NULL, 0)));
    SYM_DEFCLASS_STELLA_FALSE_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("FALSE-WRAPPER", NULL, 0)));
    SYM_DEFCLASS_STELLA_ANSWER = ((Symbol*)(internRigidSymbolWrtModule("ANSWER", NULL, 0)));
    SYM_DEFCLASS_STELLA_IF = ((Symbol*)(internRigidSymbolWrtModule("IF", NULL, 0)));
    SYM_DEFCLASS_STELLA_NULLp = ((Symbol*)(internRigidSymbolWrtModule("NULL?", NULL, 0)));
    SYM_DEFCLASS_STELLA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("PROGN", NULL, 0)));
    SYM_DEFCLASS_STELLA_ERROR = ((Symbol*)(internRigidSymbolWrtModule("ERROR", NULL, 0)));
    KWD_DEFCLASS_AUXILIARYp = ((Keyword*)(internRigidSymbolWrtModule("AUXILIARY?", NULL, 2)));
    SYM_DEFCLASS_STELLA_VALUE = ((Symbol*)(internRigidSymbolWrtModule("VALUE", NULL, 0)));
    SYM_DEFCLASS_STELLA_IGNORE = ((Symbol*)(internRigidSymbolWrtModule("IGNORE", NULL, 0)));
    SGT_DEFCLASS_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
    KWD_DEFCLASS_WRAP_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("WRAP-FUNCTION", NULL, 2)));
    SYM_DEFCLASS_STELLA_CAST = ((Symbol*)(internRigidSymbolWrtModule("CAST", NULL, 0)));
    SYM_DEFCLASS_STELLA_SETVALUEp = ((Symbol*)(internRigidSymbolWrtModule("SETVALUE?", NULL, 0)));
    SGT_DEFCLASS_STELLA_DYNAMIC_SLOTS_MIXIN = ((Surrogate*)(internRigidSymbolWrtModule("DYNAMIC-SLOTS-MIXIN", NULL, 1)));
    SYM_DEFCLASS_STELLA_SLOTNAME = ((Symbol*)(internRigidSymbolWrtModule("SLOTNAME", NULL, 0)));
    SYM_DEFCLASS_STELLA_QUOTE = ((Symbol*)(internRigidSymbolWrtModule("QUOTE", NULL, 0)));
    SYM_DEFCLASS_STELLA_CASE = ((Symbol*)(internRigidSymbolWrtModule("CASE", NULL, 0)));
    SYM_DEFCLASS_STELLA_SET_DYNAMIC_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("SET-DYNAMIC-SLOT-VALUE", NULL, 0)));
    SYM_DEFCLASS_STELLA_LOOKUP = ((Symbol*)(internRigidSymbolWrtModule("LOOKUP", NULL, 0)));
    SYM_DEFCLASS_STELLA_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("OBJECT", NULL, 0)));
    SYM_DEFCLASS_STELLA_SYMBOL = ((Symbol*)(internRigidSymbolWrtModule("SYMBOL", NULL, 0)));
    SYM_DEFCLASS_STELLA_BOOLEAN = ((Symbol*)(internRigidSymbolWrtModule("BOOLEAN", NULL, 0)));
    SYM_DEFCLASS_STELLA_CLASS_SLOT_ACCESSOR_CODE = ((Symbol*)(internRigidSymbolWrtModule("CLASS-SLOT-ACCESSOR-CODE", NULL, 0)));
    SYM_DEFCLASS_STELLA_THE_CODE = ((Symbol*)(internRigidSymbolWrtModule("THE-CODE", NULL, 0)));
    KWD_DEFCLASS_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SYM_DEFCLASS_STELLA_TYPECASE = ((Symbol*)(internRigidSymbolWrtModule("TYPECASE", NULL, 0)));
  }
}

void helpStartupDefclass3() {
  {
    defineFunctionObject("TYPE-TO-NULL-VALUE-TREE", "(DEFUN (TYPE-TO-NULL-VALUE-TREE OBJECT) ((TYPE TYPE)))", ((cpp_function_code)(&typeToNullValueTree)), NULL);
    defineFunctionObject("TYPE-TO-WALKED-NULL-VALUE-TREE", "(DEFUN (TYPE-TO-WALKED-NULL-VALUE-TREE OBJECT) ((TYPESPEC TYPE-SPEC) (TYPE TYPE)))", ((cpp_function_code)(&typeToWalkedNullValueTree)), NULL);
    defineFunctionObject("YIELD-CONS-LIST-FROM-SEQUENCE", "(DEFUN (YIELD-CONS-LIST-FROM-SEQUENCE CONS) ((SEQUENCE SEQUENCE)))", ((cpp_function_code)(&yieldConsListFromSequence)), NULL);
    defineFunctionObject("YIELD-DEFINE-STELLA-CLASS", "(DEFUN (YIELD-DEFINE-STELLA-CLASS CONS) ((CLASS CLASS)) :DOCUMENTATION \"Return a cons tree that (when evaluated) constructs\na Stella class object.\")", ((cpp_function_code)(&yieldDefineStellaClass)), NULL);
    defineFunctionObject("CREATE-NATIVE-CLASS?", "(DEFUN (CREATE-NATIVE-CLASS? BOOLEAN) ((CLASS CLASS)))", ((cpp_function_code)(&createNativeClassP)), NULL);
    defineFunctionObject("EXCEPTION-CLASS?", "(DEFUN (EXCEPTION-CLASS? BOOLEAN) ((CLASS CLASS)))", ((cpp_function_code)(&exceptionClassP)), NULL);
    defineFunctionObject("WARN-ABOUT-MULTIPLE-PARENTS", "(DEFUN WARN-ABOUT-MULTIPLE-PARENTS ((CLASS CLASS)))", ((cpp_function_code)(&warnAboutMultipleParents)), NULL);
    defineFunctionObject("WARN-ABOUT-NON-DIRECT-SUPERS", "(DEFUN WARN-ABOUT-NON-DIRECT-SUPERS ((CLASS CLASS)))", ((cpp_function_code)(&warnAboutNonDirectSupers)), NULL);
    defineFunctionObject("SPACE-SAVER-SLOT-ALLOCATION?", "(DEFUN (SPACE-SAVER-SLOT-ALLOCATION? BOOLEAN) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&spaceSaverSlotAllocationP)), NULL);
    defineFunctionObject("DYNAMIC-SLOT?", "(DEFUN (DYNAMIC-SLOT? BOOLEAN) ((SLOT STORAGE-SLOT)) :GLOBALLY-INLINE? TRUE (RETURN (EQL? (ALLOCATION SLOT) :DYNAMIC)))", ((cpp_function_code)(&dynamicSlotP)), NULL);
    defineFunctionObject("CLASS-SLOT?", "(DEFUN (CLASS-SLOT? BOOLEAN) ((SLOT STORAGE-SLOT)) :GLOBALLY-INLINE? TRUE (RETURN (EQL? (ALLOCATION SLOT) :CLASS)))", ((cpp_function_code)(&classSlotP)), NULL);
    defineFunctionObject("REDUNDANT-SLOT?", "(DEFUN (REDUNDANT-SLOT? BOOLEAN) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&redundantSlotP)), NULL);
    defineFunctionObject("NATIVE-SLOT?", "(DEFUN (NATIVE-SLOT? BOOLEAN) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&nativeSlotP)), NULL);
    defineFunctionObject("PARAMETER-SLOT?", "(DEFUN (PARAMETER-SLOT? BOOLEAN) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&parameterSlotP)), NULL);
    defineFunctionObject("NATIVE-METHOD?", "(DEFUN (NATIVE-METHOD? BOOLEAN) ((SLOT METHOD-SLOT)))", ((cpp_function_code)(&nativeMethodP)), NULL);
    defineFunctionObject("MIXIN-SLOT?", "(DEFUN (MIXIN-SLOT? BOOLEAN) ((SELF SLOT)))", ((cpp_function_code)(&mixinSlotP)), NULL);
    defineFunctionObject("MIXIN-METHOD?", "(DEFUN (MIXIN-METHOD? BOOLEAN) ((SELF SLOT)))", ((cpp_function_code)(&mixinMethodP)), NULL);
    defineFunctionObject("CANONICAL-SLOT", "(DEFUN (CANONICAL-SLOT STORAGE-SLOT) ((SLOT STORAGE-SLOT)) :DOCUMENTATION \"Computes the slot at the base of a renaming chain for 'slot'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&canonicalSlot)), NULL);
    defineFunctionObject("CANONICAL-SLOT-NAME", "(DEFUN (CANONICAL-SLOT-NAME SYMBOL) ((SLOT STORAGE-SLOT)) :DOCUMENTATION \"Name of the slot at the base of a renaming chain for 'slot'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&canonicalSlotName)), NULL);
    defineFunctionObject("UNKNOWN-TYPE?", "(DEFUN (UNKNOWN-TYPE? BOOLEAN) ((TYPE TYPE)))", ((cpp_function_code)(((boolean  (*) (Surrogate*))(&unknownTypeP)))), NULL);
    defineFunctionObject("SLOT-HAS-UNKNOWN-TYPE?", "(DEFUN (SLOT-HAS-UNKNOWN-TYPE? BOOLEAN) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&slotHasUnknownTypeP)), NULL);
    defineFunctionObject("NATIVE-STORAGE-SLOT-HOME", "(DEFUN (NATIVE-STORAGE-SLOT-HOME CLASS) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&nativeStorageSlotHome)), NULL);
    defineFunctionObject("NATIVE-SLOT-HOME", "(DEFUN (NATIVE-SLOT-HOME CLASS) ((SLOT SLOT) (CLASS CLASS)))", ((cpp_function_code)(&nativeSlotHome)), NULL);
    defineFunctionObject("SLOT-NAME-CONFLICT?", "(DEFUN (SLOT-NAME-CONFLICT? BOOLEAN) ((SLOT SLOT) (CLASS CLASS)))", ((cpp_function_code)(&slotNameConflictP)), NULL);
    defineFunctionObject("METHOD-CONTAINS-UNKNOWN-TYPE?", "(DEFUN (METHOD-CONTAINS-UNKNOWN-TYPE? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&methodContainsUnknownTypeP)), NULL);
    defineFunctionObject("METHOD-CONTAINS-ANCHORED-TYPE?", "(DEFUN (METHOD-CONTAINS-ANCHORED-TYPE? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&methodContainsAnchoredTypeP)), NULL);
    defineFunctionObject("YIELD-RECYCLE-LIST-NAME", "(DEFUN (YIELD-RECYCLE-LIST-NAME SYMBOL) ((CLASS CLASS)))", ((cpp_function_code)(&yieldRecycleListName)), NULL);
    defineFunctionObject("RECYCLE-SLOT", "(DEFUN (RECYCLE-SLOT STORAGE-SLOT) ((CLASS CLASS)))", ((cpp_function_code)(&recycleSlot)), NULL);
    defineFunctionObject("USE-FREE-LIST?", "(DEFUN (USE-FREE-LIST? BOOLEAN) ((CLASS CLASS)))", ((cpp_function_code)(&useFreeListP)), NULL);
    defineFunctionObject("USE-SWEEP-LIST?", "(DEFUN (USE-SWEEP-LIST? BOOLEAN) ((CLASS CLASS)))", ((cpp_function_code)(&useSweepListP)), NULL);
    defineFunctionObject("DECIDED-TO-RECYCLE?", "(DEFUN (DECIDED-TO-RECYCLE? BOOLEAN) ((CLASS CLASS)))", ((cpp_function_code)(&decidedToRecycleP)), NULL);
    defineFunctionObject("COMPUTE-RECYCLED-ITEM-SIZE", "(DEFUN (COMPUTE-RECYCLED-ITEM-SIZE INTEGER) ((CLASS CLASS)))", ((cpp_function_code)(&computeRecycledItemSize)), NULL);
    defineFunctionObject("YIELD-RECYCLE-LIST-DEFINITIONS", "(DEFUN (YIELD-RECYCLE-LIST-DEFINITIONS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldRecycleListDefinitions)), NULL);
    defineFunctionObject("YIELD-MAKE-TREES", "(DEFUN (YIELD-MAKE-TREES CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldMakeTrees)), NULL);
    defineFunctionObject("YIELD-CONSTRUCTOR-NAME", "(DEFUN (YIELD-CONSTRUCTOR-NAME SYMBOL) ((CLASS CLASS)))", ((cpp_function_code)(&yieldConstructorName)), NULL);
    defineFunctionObject("YIELD-CREATION-TREES", "(DEFUN (YIELD-CREATION-TREES CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldCreationTrees)), NULL);
    defineFunctionObject("YIELD-TERMINATE-OBJECT-TREES", "(DEFUN (YIELD-TERMINATE-OBJECT-TREES CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldTerminateObjectTrees)), NULL);
    defineFunctionObject("YIELD-CREATION-OR-REUSE-TREES", "(DEFUN (YIELD-CREATION-OR-REUSE-TREES CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldCreationOrReuseTrees)), NULL);
    defineFunctionObject("YIELD-CREATION-OR-REUSE-TREES-FROM-FREE-LIST", "(DEFUN (YIELD-CREATION-OR-REUSE-TREES-FROM-FREE-LIST CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldCreationOrReuseTreesFromFreeList)), NULL);
    defineFunctionObject("YIELD-CREATION-OR-REUSE-TREES-FROM-SWEEP-LIST", "(DEFUN (YIELD-CREATION-OR-REUSE-TREES-FROM-SWEEP-LIST CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldCreationOrReuseTreesFromSweepList)), NULL);
    defineFunctionObject("YIELD-CREATION-OR-REUSE-TREES-FROM-FREE-OR-SWEEP-LIST", "(DEFUN (YIELD-CREATION-OR-REUSE-TREES-FROM-FREE-OR-SWEEP-LIST CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldCreationOrReuseTreesFromFreeOrSweepList)), NULL);
    defineFunctionObject("MARK-DIRECT-EQUIVALENT-SLOT", "(DEFUN MARK-DIRECT-EQUIVALENT-SLOT ((SLOT SLOT)))", ((cpp_function_code)(&markDirectEquivalentSlot)), NULL);
    defineFunctionObject("IS-CONTEXT-SENSITIVE-SLOT?", "(DEFUN (IS-CONTEXT-SENSITIVE-SLOT? BOOLEAN) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&isContextSensitiveSlotP)), NULL);
    defineFunctionObject("YIELD-INITIAL-VALUE-ASSIGNMENT", "(DEFUN (YIELD-INITIAL-VALUE-ASSIGNMENT CONS) ((SLOT STORAGE-SLOT) (MODE KEYWORD)))", ((cpp_function_code)(&yieldInitialValueAssignment)), NULL);
    defineFunctionObject("YIELD-INITIAL-VALUE-ASSIGNMENTS", "(DEFUN (YIELD-INITIAL-VALUE-ASSIGNMENTS CONS) ((CLASS CLASS) (MODE KEYWORD)))", ((cpp_function_code)(&yieldInitialValueAssignments)), NULL);
    defineFunctionObject("YIELD-LOCAL-INITIAL-VALUE-ASSIGNMENTS", "(DEFUN (YIELD-LOCAL-INITIAL-VALUE-ASSIGNMENTS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldLocalInitialValueAssignments)), NULL);
    defineFunctionObject("YIELD-INITIALIZER-TREES", "(DEFUN (YIELD-INITIALIZER-TREES CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldInitializerTrees)), NULL);
    defineFunctionObject("YIELD-CONSTRUCTOR-BODY", "(DEFUN (YIELD-CONSTRUCTOR-BODY CONS) ((CLASS CLASS) (REQUIREDASSIGNMENTS CONS)))", ((cpp_function_code)(&yieldConstructorBody)), NULL);
    defineFunctionObject("YIELD-CONSTRUCTOR-DEFINITION", "(DEFUN (YIELD-CONSTRUCTOR-DEFINITION CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldConstructorDefinition)), NULL);
    defineFunctionObject("YIELD-EXCEPTION-CONSTRUCTOR-BODY", "(DEFUN (YIELD-EXCEPTION-CONSTRUCTOR-BODY CONS) ((CLASS CLASS) (MESSAGEPARAMETER SYMBOL) (REQUIREDASSIGNMENTS CONS)))", ((cpp_function_code)(&yieldExceptionConstructorBody)), NULL);
    defineFunctionObject("YIELD-EXCEPTION-CONSTRUCTOR-DEFINITION", "(DEFUN (YIELD-EXCEPTION-CONSTRUCTOR-DEFINITION CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldExceptionConstructorDefinition)), NULL);
    defineFunctionObject("YIELD-DESTRUCTOR-DEFINITIONS", "(DEFUN (YIELD-DESTRUCTOR-DEFINITIONS CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldDestructorDefinitions)), NULL);
    defineFunctionObject("CREATE-CONSTRUCTOR-AND-DESTRUCTOR-UNITS", "(DEFUN CREATE-CONSTRUCTOR-AND-DESTRUCTOR-UNITS ((CLASS CLASS)))", ((cpp_function_code)(&createConstructorAndDestructorUnits)), NULL);
    defineFunctionObject("PARAMETERIZED-CLASS?", "(DEFUN (PARAMETERIZED-CLASS? BOOLEAN) ((CLASS CLASS)))", ((cpp_function_code)(&parameterizedClassP)), NULL);
    defineFunctionObject("CLASS-WITH-INITIALIZER?", "(DEFUN (CLASS-WITH-INITIALIZER? BOOLEAN) ((CLASS CLASS)))", ((cpp_function_code)(&classWithInitializerP)), NULL);
    defineFunctionObject("YIELD-INITIALIZER-NAME", "(DEFUN (YIELD-INITIALIZER-NAME SYMBOL) ((CLASS CLASS)))", ((cpp_function_code)(&yieldInitializerName)), NULL);
    defineFunctionObject("YIELD-INITIALIZER-DEFINITION", "(DEFUN (YIELD-INITIALIZER-DEFINITION CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldInitializerDefinition)), NULL);
    defineFunctionObject("CREATE-CPP-CONSTRUCTOR-UNIT", "(DEFUN CREATE-CPP-CONSTRUCTOR-UNIT ((CLASS CLASS)))", ((cpp_function_code)(&createCppConstructorUnit)), NULL);
    defineFunctionObject("CPP-CONSTRUCTOR?", "(DEFUN (CPP-CONSTRUCTOR? BOOLEAN) ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&cppConstructorP)), NULL);
    defineFunctionObject("CREATE-RECYCLE-LIST", "(DEFUN (CREATE-RECYCLE-LIST RECYCLE-LIST) ((CLASSTYPE TYPE) (ITEMSIZE INTEGER)))", ((cpp_function_code)(&createRecycleList)), NULL);
  }
}

void helpStartupDefclass4() {
  {
    defineFunctionObject("CLEAR-RECYCLE-LIST", "(DEFUN CLEAR-RECYCLE-LIST ((LIST RECYCLE-LIST)) :DOCUMENTATION \"Reset `list' to its empty state.\")", ((cpp_function_code)(&clearRecycleList)), NULL);
    defineFunctionObject("CLEAR-RECYCLE-LISTS", "(DEFUN CLEAR-RECYCLE-LISTS () :DOCUMENTATION \"Reset all currently active recycle lists to their empty state.\" :PUBLIC? TRUE)", ((cpp_function_code)(&clearRecycleLists)), NULL);
    defineFunctionObject("PRINT-RECYCLE-LISTS", "(DEFUN PRINT-RECYCLE-LISTS () :DOCUMENTATION \"Print the current state of all recycle lists.\" :PUBLIC? TRUE)", ((cpp_function_code)(&printRecycleLists)), NULL);
    defineFunctionObject("MAINTAIN-RECYCLE-LISTS", "(DEFUN MAINTAIN-RECYCLE-LISTS () :PUBLIC? TRUE)", ((cpp_function_code)(&maintainRecycleLists)), NULL);
    defineMethodObject("(DEFMETHOD (DELETED? BOOLEAN) ((SELF RECYCLE-LIST)))", wrapMethodCode(((cpp_method_code)(&RecycleList::deletedP))), NULL);
    defineMethodObject("(DEFMETHOD (DELETED?-SETTER BOOLEAN) ((SELF RECYCLE-LIST) (VALUE BOOLEAN)))", wrapMethodCode(((cpp_method_code)(&RecycleList::deletedPSetter))), NULL);
    defineFunctionObject("RECYCLE-LIST-SIZE", "(DEFUN (RECYCLE-LIST-SIZE INTEGER) ((LIST RECYCLE-LIST)) :GLOBALLY-INLINE? TRUE (RETURN (* (ITEM-SIZE LIST) (CURRENT-LENGTH LIST))))", ((cpp_function_code)(&recycleListSize)), NULL);
    defineFunctionObject("TOTAL-RECYCLE-LISTS-SIZE", "(DEFUN (TOTAL-RECYCLE-LISTS-SIZE INTEGER) ())", ((cpp_function_code)(&totalRecycleListsSize)), NULL);
    defineFunctionObject("RECYCLE-LIST-SIZE<", "(DEFUN (RECYCLE-LIST-SIZE< BOOLEAN) ((LIST1 RECYCLE-LIST) (LIST2 RECYCLE-LIST)))", ((cpp_function_code)(&recycleListSizeL)), NULL);
    defineFunctionObject("REDUCE-RECYCLE-LIST-SIZE", "(DEFUN REDUCE-RECYCLE-LIST-SIZE ((LIST RECYCLE-LIST) (FRACTION FLOAT)))", ((cpp_function_code)(&reduceRecycleListSize)), NULL);
    defineMethodObject("(DEFMETHOD SWEEP ((SELF OBJECT)) :DOCUMENTATION \"Default method.  Sweep up all `self'-type objects.\")", wrapMethodCode(((cpp_method_code)(&Object::sweep))), NULL);
    defineFunctionObject("SWEEP-TRANSIENTS", "(DEFUN SWEEP-TRANSIENTS () :PUBLIC? TRUE)", ((cpp_function_code)(&sweepTransients)), NULL);
    defineFunctionObject("MAKE-NON-RECYCLED-LIST", "(DEFUN (MAKE-NON-RECYCLED-LIST LIST) ())", ((cpp_function_code)(&makeNonRecycledList)), NULL);
    defineFunctionObject("REGISTER-RECYCLED-ITEM", "(DEFUN REGISTER-RECYCLED-ITEM ((ITEM OBJECT)))", ((cpp_function_code)(&registerRecycledItem)), NULL);
    defineFunctionObject("UNREGISTER-RECYCLED-ITEM", "(DEFUN UNREGISTER-RECYCLED-ITEM ((ITEM OBJECT)))", ((cpp_function_code)(&unregisterRecycledItem)), NULL);
    defineFunctionObject("START-RECYCLE-LIST-DEBUGGING", "(DEFUN START-RECYCLE-LIST-DEBUGGING ())", ((cpp_function_code)(&startRecycleListDebugging)), NULL);
    defineFunctionObject("STOP-RECYCLE-LIST-DEBUGGING", "(DEFUN STOP-RECYCLE-LIST-DEBUGGING ())", ((cpp_function_code)(&stopRecycleListDebugging)), NULL);
    defineFunctionObject("RECYCLE-LIST-DEBUGGING-ENABLED?", "(DEFUN (RECYCLE-LIST-DEBUGGING-ENABLED? BOOLEAN) () :GLOBALLY-INLINE? TRUE (RETURN (DEFINED? *CURRENTLY-RECYCLED-ITEMS*)))", ((cpp_function_code)(&recycleListDebuggingEnabledP)), NULL);
    defineFunctionObject("TRANSLATE-WITH-RECYCLE-LIST-DEBUGGING?", "(DEFUN (TRANSLATE-WITH-RECYCLE-LIST-DEBUGGING? BOOLEAN) () :GLOBALLY-INLINE? TRUE (RETURN *TRANSLATE-WITH-RECYCLE-LIST-DEBUGGING?*))", ((cpp_function_code)(&translateWithRecycleListDebuggingP)), NULL);
    defineFunctionObject("YIELD-REGISTER-RECYCLED-ITEM-TREES", "(DEFUN (YIELD-REGISTER-RECYCLED-ITEM-TREES CONS) ())", ((cpp_function_code)(&yieldRegisterRecycledItemTrees)), NULL);
    defineFunctionObject("YIELD-UNREGISTER-RECYCLED-ITEM-TREES", "(DEFUN (YIELD-UNREGISTER-RECYCLED-ITEM-TREES CONS) ())", ((cpp_function_code)(&yieldUnregisterRecycledItemTrees)), NULL);
    defineFunctionObject("HAS-NON-NULL-DEFAULT-VALUE?", "(DEFUN (HAS-NON-NULL-DEFAULT-VALUE? BOOLEAN) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&hasNonNullDefaultValueP)), NULL);
    defineFunctionObject("SYSTEM-DEFINED-SLOT-READER?", "(DEFUN (SYSTEM-DEFINED-SLOT-READER? BOOLEAN) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&systemDefinedSlotReaderP)), NULL);
    defineFunctionObject("SYSTEM-DEFINED-SLOT-WRITER?", "(DEFUN (SYSTEM-DEFINED-SLOT-WRITER? BOOLEAN) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&systemDefinedSlotWriterP)), NULL);
    defineFunctionObject("YIELD-SLOT-TYPE-TREE", "(DEFUN (YIELD-SLOT-TYPE-TREE OBJECT) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&yieldSlotTypeTree)), NULL);
    defineFunctionObject("YIELD-HARDWIRED-SLOT-VARIABLE", "(DEFUN (YIELD-HARDWIRED-SLOT-VARIABLE SYMBOL) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&yieldHardwiredSlotVariable)), NULL);
    defineFunctionObject("YIELD-HARDWIRED-SLOT-READER-BODY", "(DEFUN (YIELD-HARDWIRED-SLOT-READER-BODY CONS CONS) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&yieldHardwiredSlotReaderBody)), NULL);
    defineFunctionObject("FINALIZE-AUXILIARY-METHOD", "(DEFUN FINALIZE-AUXILIARY-METHOD ((METHOD METHOD-SLOT)))", ((cpp_function_code)(&finalizeAuxiliaryMethod)), NULL);
    defineFunctionObject("WRAP-WITH-DEFAULT-VALUE-AND-RETURN-CODE", "(DEFUN (WRAP-WITH-DEFAULT-VALUE-AND-RETURN-CODE CONS) ((SLOT STORAGE-SLOT) (DEFAULTEXPRESSION OBJECT)))", ((cpp_function_code)(&wrapWithDefaultValueAndReturnCode)), NULL);
    defineFunctionObject("YIELD-SLOT-READER-TREE", "(DEFUN (YIELD-SLOT-READER-TREE CONS) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&yieldSlotReaderTree)), NULL);
    defineFunctionObject("YIELD-SLOT-WRITER-TREE", "(DEFUN (YIELD-SLOT-WRITER-TREE CONS) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&yieldSlotWriterTree)), NULL);
    defineFunctionObject("SLOT-VALUE-IS-BARE-LITERAL?", "(DEFUN (SLOT-VALUE-IS-BARE-LITERAL? BOOLEAN) ((SLOT SLOT)))", ((cpp_function_code)(&slotValueIsBareLiteralP)), NULL);
    defineFunctionObject("GENERICALLY-ACCESSIBLE-TYPE?", "(DEFUN (GENERICALLY-ACCESSIBLE-TYPE? BOOLEAN) ((TYPE TYPE)))", ((cpp_function_code)(&genericallyAccessibleTypeP)), NULL);
    defineFunctionObject("GENERIC-SLOT-READER?", "(DEFUN (GENERIC-SLOT-READER? BOOLEAN) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&genericSlotReaderP)), NULL);
    defineFunctionObject("GENERIC-SLOT-WRITER?", "(DEFUN (GENERIC-SLOT-WRITER? BOOLEAN) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&genericSlotWriterP)), NULL);
    defineFunctionObject("SLOT-ACCESS-METHOD?", "(DEFUN (SLOT-ACCESS-METHOD? BOOLEAN) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&slotAccessMethodP)), NULL);
    defineFunctionObject("YIELD-GENERIC-SLOT-ACCESSOR-NAME", "(DEFUN (YIELD-GENERIC-SLOT-ACCESSOR-NAME SYMBOL) ((CLASS CLASS)))", ((cpp_function_code)(&yieldGenericSlotAccessorName)), NULL);
    defineFunctionObject("YIELD-GENERIC-SLOT-ACCESSOR-DEFINITION", "(DEFUN (YIELD-GENERIC-SLOT-ACCESSOR-DEFINITION CONS) ((CLASS CLASS)))", ((cpp_function_code)(&yieldGenericSlotAccessorDefinition)), NULL);
    defineFunctionObject("CREATE-GENERIC-SLOT-ACCESSOR-UNIT", "(DEFUN CREATE-GENERIC-SLOT-ACCESSOR-UNIT ((CLASS CLASS)))", ((cpp_function_code)(&createGenericSlotAccessorUnit)), NULL);
    defineFunctionObject("YIELD-GENERIC-SLOT-ACCESSOR-ATTACHMENT", "(DEFUN (YIELD-GENERIC-SLOT-ACCESSOR-ATTACHMENT CONS) ((CLASS CLASS) (CLASSREF SYMBOL)))", ((cpp_function_code)(&yieldGenericSlotAccessorAttachment)), NULL);
    defineFunctionObject("GET-GENERIC-SLOT-ACCESSOR", "(DEFUN (GET-GENERIC-SLOT-ACCESSOR FUNCTION-CODE) ((SLOT STORAGE-SLOT) (CLASS CLASS) (WARN? BOOLEAN)) :DOCUMENTATION \"Return the accessor code to read `slot' on an object of type `class',\nor NULL if no such accessor exists.  In that case, print a warning if `warn?' is TRUE.\nNOTE: the accessor expects `canonical-slot-name's (which see).\" :PUBLIC? TRUE)", ((cpp_function_code)(&getGenericSlotAccessor)), NULL);
    defineFunctionObject("YIELD-MIXIN-CLASS-USERS-TREE", "(DEFUN (YIELD-MIXIN-CLASS-USERS-TREE (CONS OF SYMBOL)) ((CLASS CLASS)))", ((cpp_function_code)(&yieldMixinClassUsersTree)), NULL);
    defineFunctionObject("YIELD-MIXIN-SLOT-READER-NAME", "(DEFUN (YIELD-MIXIN-SLOT-READER-NAME SYMBOL) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&yieldMixinSlotReaderName)), NULL);
    defineFunctionObject("YIELD-MIXIN-SLOT-WRITER-NAME", "(DEFUN (YIELD-MIXIN-SLOT-WRITER-NAME SYMBOL) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&yieldMixinSlotWriterName)), NULL);
    defineFunctionObject("YIELD-MIXIN-SLOT-READER-TREE", "(DEFUN (YIELD-MIXIN-SLOT-READER-TREE CONS) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&yieldMixinSlotReaderTree)), NULL);
    defineFunctionObject("YIELD-MIXIN-SLOT-WRITER-TREE", "(DEFUN (YIELD-MIXIN-SLOT-WRITER-TREE CONS) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&yieldMixinSlotWriterTree)), NULL);
    defineFunctionObject("YIELD-NATIVE-SLOT-READER-NAME", "(DEFUN (YIELD-NATIVE-SLOT-READER-NAME SYMBOL) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&yieldNativeSlotReaderName)), NULL);
    defineFunctionObject("YIELD-NATIVE-SLOT-WRITER-NAME", "(DEFUN (YIELD-NATIVE-SLOT-WRITER-NAME SYMBOL) ((SLOT STORAGE-SLOT)))", ((cpp_function_code)(&yieldNativeSlotWriterName)), NULL);
    defineFunctionObject("YIELD-NATIVE-SLOT-READER-TREE", "(DEFUN (YIELD-NATIVE-SLOT-READER-TREE CONS) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&yieldNativeSlotReaderTree)), NULL);
    defineFunctionObject("YIELD-NATIVE-SLOT-WRITER-TREE", "(DEFUN (YIELD-NATIVE-SLOT-WRITER-TREE CONS) ((SLOT STORAGE-SLOT) (CLASS CLASS)))", ((cpp_function_code)(&yieldNativeSlotWriterTree)), NULL);
    defineFunctionObject("CREATE-KEYED-EQUALITY-METHOD-UNIT", "(DEFUN CREATE-KEYED-EQUALITY-METHOD-UNIT ((CLASS CLASS)))", ((cpp_function_code)(&createKeyedEqualityMethodUnit)), NULL);
    defineFunctionObject("TRANSIENT-OBJECT?", "(DEFUN (TRANSIENT-OBJECT? BOOLEAN) ((OBJECT OBJECT)))", ((cpp_function_code)(&transientObjectP)), NULL);
    defineFunctionObject("STARTUP-DEFCLASS", "(DEFUN STARTUP-DEFCLASS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupDefclass)), NULL);
    { MethodSlot* function = lookupFunction(SYM_DEFCLASS_STELLA_STARTUP_DEFCLASS);

      setDynamicSlotValue(function->dynamicSlots, SYM_DEFCLASS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupDefclass"), NULL_STRING_WRAPPER);
    }
  }
}

void startupDefclass() {
  if (currentStartupTimePhaseP(0)) {
    oALL_RECYCLE_LISTSo = makeNonRecycledList();
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupDefclass1();
      helpStartupDefclass2();
      SYM_DEFCLASS_STELLA_EQp = ((Symbol*)(internRigidSymbolWrtModule("EQ?", NULL, 0)));
      SYM_DEFCLASS_STELLA_OTHER = ((Symbol*)(internRigidSymbolWrtModule("OTHER", NULL, 0)));
      SYM_DEFCLASS_STELLA_EQUAL = ((Symbol*)(internRigidSymbolWrtModule("EQUAL", NULL, 0)));
      SYM_DEFCLASS_STELLA_STARTUP_DEFCLASS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-DEFCLASS", NULL, 0)));
      SYM_DEFCLASS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(4)) {
      oRECYCLE_LISTS_MAINTENANCE_TIMERo = oRECYCLE_LISTS_MAINTENANCE_INTERVALo;
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupDefclass3();
      helpStartupDefclass4();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFSPECIAL *RECYCLING-ENABLED?* BOOLEAN TRUE :DOCUMENTATION \"If `TRUE' calls to `new' or `free' on classes with :recycle-method;\nspecifications will actually operate on recycle lists.  Otherwise, all\nrecycle list operations will be no-ops.\" :PUBLIC? TRUE)", &oRECYCLING_ENABLEDpo);
      defineGlobalVariableObject("(DEFGLOBAL *ALL-RECYCLE-LISTS* (LIST OF RECYCLE-LIST) NULL)", &oALL_RECYCLE_LISTSo);
      defineGlobalVariableObject("(DEFGLOBAL *MAX-RECYCLE-LIST-BYTES* INTEGER 3000000 :DOCUMENTATION \"Maximum number of bytes to be occupied by recycle lists.\" :PUBLIC? TRUE)", &oMAX_RECYCLE_LIST_BYTESo);
      defineGlobalVariableObject("(DEFGLOBAL *RECYCLE-LISTS-MAINTENANCE-INTERVAL* INTEGER 5000 :DOCUMENTATION \"Total number of recycle list extensions after which a\nsize maintenance operation is performed to ensure that\nthe `*MAX-RECYCLE-LIST-BYTES*' limit is still met.\" :PUBLIC? TRUE)", &oRECYCLE_LISTS_MAINTENANCE_INTERVALo);
      defineGlobalVariableObject("(DEFGLOBAL *RECYCLE-LISTS-MAINTENANCE-TIMER* INTEGER *RECYCLE-LISTS-MAINTENANCE-INTERVAL* :PUBLIC? TRUE)", &oRECYCLE_LISTS_MAINTENANCE_TIMERo);
      defineGlobalVariableObject("(DEFGLOBAL *CURRENTLY-RECYCLED-ITEMS* (HASH-TABLE OF OBJECT OBJECT) NULL :DOCUMENTATION \"During recycle list debugging holds all items that live in\nsome free list.  Depending on program behavior, this table can get quite large!\")", &oCURRENTLY_RECYCLED_ITEMSo);
      defineGlobalVariableObject("(DEFGLOBAL *TRANSLATE-WITH-RECYCLE-LIST-DEBUGGING?* BOOLEAN FALSE)", &oTRANSLATE_WITH_RECYCLE_LIST_DEBUGGINGpo);
    }
  }
}

Surrogate* SGT_DEFCLASS_STELLA_LITERAL = NULL;

Surrogate* SGT_DEFCLASS_STELLA_SECOND_CLASS_OBJECT = NULL;

Symbol* SYM_DEFCLASS_STELLA_NULL = NULL;

Keyword* KWD_DEFCLASS_COMMON_LISP = NULL;

Symbol* SYM_DEFCLASS_STELLA_VERBATIM = NULL;

Symbol* SYM_DEFCLASS_STELLA_DEFINE_CLASS_FROM_STRINGIFIED_SOURCE = NULL;

Symbol* SYM_DEFCLASS_STELLA_CLASS_CL_NATIVE_TYPE = NULL;

Keyword* KWD_DEFCLASS_IDL = NULL;

Symbol* SYM_DEFCLASS_STELLA_CLASS_IDL_NATIVE_TYPE = NULL;

Keyword* KWD_DEFCLASS_JAVA = NULL;

Symbol* SYM_DEFCLASS_STELLA_CLASS_JAVA_NATIVE_TYPE = NULL;

Keyword* KWD_DEFCLASS_CPP = NULL;

Keyword* KWD_DEFCLASS_CPP_STANDALONE = NULL;

Symbol* SYM_DEFCLASS_STELLA_CLASS_CPP_NATIVE_TYPE = NULL;

Surrogate* SGT_DEFCLASS_STELLA_NON_OBJECT = NULL;

Surrogate* SGT_DEFCLASS_STELLA_NATIVE_EXCEPTION = NULL;

Keyword* KWD_DEFCLASS_DYNAMIC = NULL;

Symbol* SYM_DEFCLASS_STELLA_SLOT_INITIAL_VALUE = NULL;

Keyword* KWD_DEFCLASS_BIT = NULL;

Surrogate* SGT_DEFCLASS_STELLA_BOOLEAN = NULL;

Keyword* KWD_DEFCLASS_CLASS = NULL;

Symbol* SYM_DEFCLASS_STELLA_SLOT_RENAMES = NULL;

Surrogate* SGT_DEFCLASS_STELLA_UNKNOWN = NULL;

Symbol* SYM_DEFCLASS_STELLA_SLOT_TYPE_SPECIFIER = NULL;

Surrogate* SGT_DEFCLASS_STELLA_ANCHORED_TYPE_SPECIFIER = NULL;

Symbol* SYM_DEFCLASS_STELLA_NEXT_SWEEP_LIST_OBJECT = NULL;

Keyword* KWD_DEFCLASS_FREE_LIST = NULL;

Keyword* KWD_DEFCLASS_FREE_AND_SWEEP_LIST = NULL;

Keyword* KWD_DEFCLASS_SWEEP_LIST = NULL;

Symbol* SYM_DEFCLASS_STELLA_CLASS_CREATOR = NULL;

Keyword* KWD_DEFCLASS_USE_COMMON_LISP_STRUCTS = NULL;

Keyword* KWD_DEFCLASS_USE_COMMON_LISP_VECTOR_STRUCTS = NULL;

Symbol* SYM_DEFCLASS_STELLA_DEFGLOBAL = NULL;

Symbol* SYM_DEFCLASS_STELLA_RECYCLE_LIST = NULL;

Symbol* SYM_DEFCLASS_STELLA_OF = NULL;

Symbol* SYM_DEFCLASS_STELLA_CREATE_RECYCLE_LIST = NULL;

Symbol* SYM_DEFCLASS_STELLA_SETQ = NULL;

Symbol* SYM_DEFCLASS_STELLA_SELF = NULL;

Symbol* SYM_DEFCLASS_STELLA_MAKE = NULL;

Symbol* SYM_DEFCLASS_STELLA_WHEN = NULL;

Symbol* SYM_DEFCLASS_STELLA_DEFINEDp = NULL;

Symbol* SYM_DEFCLASS_STELLA_FREE = NULL;

Symbol* SYM_DEFCLASS_STELLA_DYNAMIC_SLOTS = NULL;

Symbol* SYM_DEFCLASS_STELLA_CLEAR = NULL;

Symbol* SYM_DEFCLASS_STELLA_UNLESS = NULL;

Symbol* SYM_DEFCLASS_STELLA_RETURN = NULL;

Keyword* KWD_DEFCLASS_FORCE_NULL_VALUE = NULL;

Keyword* KWD_DEFCLASS_NULL_VALUE_ONLY = NULL;

Symbol* SYM_DEFCLASS_STELLA_AND = NULL;

Symbol* SYM_DEFCLASS_STELLA_oRECYCLING_ENABLEDpo = NULL;

Symbol* SYM_DEFCLASS_STELLA_COND = NULL;

Symbol* SYM_DEFCLASS_STELLA___ = NULL;

Symbol* SYM_DEFCLASS_STELLA_CURRENT_LENGTH = NULL;

Symbol* SYM_DEFCLASS_STELLA_OTHERWISE = NULL;

Symbol* SYM_DEFCLASS_STELLA_RECYCLED_ITEMS = NULL;

Symbol* SYM_DEFCLASS_STELLA_POP = NULL;

Symbol* SYM_DEFCLASS_STELLA_LIST_OF_RECYCLED_ITEMS = NULL;

Symbol* SYM_DEFCLASS_STELLA_SETF = NULL;

Symbol* SYM_DEFCLASS_STELLA_SLOT_VALUE = NULL;

Symbol* SYM_DEFCLASS_STELLA_UNUSED_ITEMS = NULL;

Symbol* SYM_DEFCLASS_STELLA_ALL_ITEMS = NULL;

Symbol* SYM_DEFCLASS_STELLA_ii = NULL;

Symbol* SYM_DEFCLASS_STELLA_e = NULL;

Symbol* SYM_DEFCLASS_STELLA_oRECYCLE_LISTS_MAINTENANCE_TIMERo = NULL;

Symbol* SYM_DEFCLASS_STELLA_MAINTAIN_RECYCLE_LISTS = NULL;

Keyword* KWD_DEFCLASS_INITIAL_VALUE_ONLY = NULL;

Keyword* KWD_DEFCLASS_ANY_INITIAL_VALUE = NULL;

Keyword* KWD_DEFCLASS_CONTEXT_SENSITIVEp = NULL;

Symbol* SYM_DEFCLASS_STELLA_FALSE = NULL;

Symbol* SYM_DEFCLASS_STELLA_CLASS_INITIALIZER = NULL;

Symbol* SYM_DEFCLASS_STELLA_RUN_CONSTRUCTOR_DEMONS = NULL;

Symbol* SYM_DEFCLASS_STELLA_DEFUN = NULL;

Keyword* KWD_DEFCLASS_CONSTRUCTORp = NULL;

Symbol* SYM_DEFCLASS_STELLA_TRUE = NULL;

Keyword* KWD_DEFCLASS_PUBLICp = NULL;

Symbol* SYM_DEFCLASS_STELLA_LET = NULL;

Symbol* SYM_DEFCLASS_STELLA_MESSAGE = NULL;

Symbol* SYM_DEFCLASS_STELLA_CLASS_DESTRUCTOR = NULL;

Symbol* SYM_DEFCLASS_STELLA_DEFMETHOD = NULL;

Surrogate* SGT_DEFCLASS_STELLA_STANDARD_OBJECT = NULL;

Symbol* SYM_DEFCLASS_STELLA_PUSH = NULL;

Symbol* SYM_DEFCLASS_STELLA_SWEEP = NULL;

Symbol* SYM_DEFCLASS_STELLA_UNUSED = NULL;

Symbol* SYM_DEFCLASS_STELLA_WHILE = NULL;

Symbol* SYM_DEFCLASS_STELLA_NOT = NULL;

Symbol* SYM_DEFCLASS_STELLA_EQLp = NULL;

Symbol* SYM_DEFCLASS_STELLA_UNMAKE = NULL;

Surrogate* SGT_DEFCLASS_STELLA_VOID = NULL;

Surrogate* SGT_DEFCLASS_STELLA_TRANSIENT_MIXIN = NULL;

Symbol* SYM_DEFCLASS_STELLA_RECYCLE_LIST_DEBUGGING_ENABLEDp = NULL;

Symbol* SYM_DEFCLASS_STELLA_REGISTER_RECYCLED_ITEM = NULL;

Symbol* SYM_DEFCLASS_STELLA_UNREGISTER_RECYCLED_ITEM = NULL;

Keyword* KWD_DEFCLASS_NULL_WRAPPER = NULL;

Symbol* SYM_DEFCLASS_STELLA_INLINE_WRAP_BOOLEAN = NULL;

Symbol* SYM_DEFCLASS_STELLA_FALSE_WRAPPER = NULL;

Symbol* SYM_DEFCLASS_STELLA_ANSWER = NULL;

Symbol* SYM_DEFCLASS_STELLA_IF = NULL;

Symbol* SYM_DEFCLASS_STELLA_NULLp = NULL;

Symbol* SYM_DEFCLASS_STELLA_PROGN = NULL;

Symbol* SYM_DEFCLASS_STELLA_ERROR = NULL;

Keyword* KWD_DEFCLASS_AUXILIARYp = NULL;

Symbol* SYM_DEFCLASS_STELLA_VALUE = NULL;

Symbol* SYM_DEFCLASS_STELLA_IGNORE = NULL;

Surrogate* SGT_DEFCLASS_STELLA_OBJECT = NULL;

Keyword* KWD_DEFCLASS_WRAP_FUNCTION = NULL;

Symbol* SYM_DEFCLASS_STELLA_CAST = NULL;

Symbol* SYM_DEFCLASS_STELLA_SETVALUEp = NULL;

Surrogate* SGT_DEFCLASS_STELLA_DYNAMIC_SLOTS_MIXIN = NULL;

Symbol* SYM_DEFCLASS_STELLA_SLOTNAME = NULL;

Symbol* SYM_DEFCLASS_STELLA_QUOTE = NULL;

Symbol* SYM_DEFCLASS_STELLA_CASE = NULL;

Symbol* SYM_DEFCLASS_STELLA_SET_DYNAMIC_SLOT_VALUE = NULL;

Symbol* SYM_DEFCLASS_STELLA_LOOKUP = NULL;

Symbol* SYM_DEFCLASS_STELLA_OBJECT = NULL;

Symbol* SYM_DEFCLASS_STELLA_SYMBOL = NULL;

Symbol* SYM_DEFCLASS_STELLA_BOOLEAN = NULL;

Symbol* SYM_DEFCLASS_STELLA_CLASS_SLOT_ACCESSOR_CODE = NULL;

Symbol* SYM_DEFCLASS_STELLA_THE_CODE = NULL;

Keyword* KWD_DEFCLASS_FUNCTION = NULL;

Symbol* SYM_DEFCLASS_STELLA_TYPECASE = NULL;

Symbol* SYM_DEFCLASS_STELLA_EQp = NULL;

Symbol* SYM_DEFCLASS_STELLA_OTHER = NULL;

Symbol* SYM_DEFCLASS_STELLA_EQUAL = NULL;

Symbol* SYM_DEFCLASS_STELLA_STARTUP_DEFCLASS = NULL;

Symbol* SYM_DEFCLASS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
