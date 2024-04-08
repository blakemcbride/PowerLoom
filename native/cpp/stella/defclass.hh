//  -*- Mode: C++ -*-

// defclass.hh

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



namespace stella {

// Global declarations:
extern DECLARE_STELLA_SPECIAL(oRECYCLING_ENABLEDpo, boolean );
extern List* oALL_RECYCLE_LISTSo;
extern int oMAX_RECYCLE_LIST_BYTESo;
extern int oRECYCLE_LISTS_MAINTENANCE_INTERVALo;
extern int oRECYCLE_LISTS_MAINTENANCE_TIMERo;
extern HashTable* oCURRENTLY_RECYCLED_ITEMSo;
extern boolean oTRANSLATE_WITH_RECYCLE_LIST_DEBUGGINGpo;

// Function signatures:
Object* typeToNullValueTree(Surrogate* type);
Object* typeToWalkedNullValueTree(StandardObject* typespec, Surrogate* type);
Cons* yieldConsListFromSequence(Sequence* sequence);
Cons* yieldDefineStellaClass(Class* clasS);
boolean createNativeClassP(Class* clasS);
boolean exceptionClassP(Class* clasS);
void warnAboutMultipleParents(Class* clasS);
void warnAboutNonDirectSupers(Class* clasS);
boolean spaceSaverSlotAllocationP(StorageSlot* slot);
boolean dynamicSlotP(StorageSlot* slot);
boolean classSlotP(StorageSlot* slot);
boolean redundantSlotP(StorageSlot* slot);
boolean nativeSlotP(StorageSlot* slot);
boolean parameterSlotP(StorageSlot* slot);
boolean nativeMethodP(MethodSlot* slot);
boolean mixinSlotP(Slot* self);
boolean mixinMethodP(Slot* self);
StorageSlot* canonicalSlot(StorageSlot* slot);
Symbol* canonicalSlotName(StorageSlot* slot);
boolean unknownTypeP(Surrogate* type);
boolean slotHasUnknownTypeP(StorageSlot* slot, Class* clasS);
Class* nativeStorageSlotHome(StorageSlot* slot, Class* clasS);
Class* nativeSlotHome(Slot* slot, Class* clasS);
boolean slotNameConflictP(Slot* slot, Class* clasS);
boolean methodContainsUnknownTypeP(MethodSlot* method);
boolean methodContainsAnchoredTypeP(MethodSlot* method);
Symbol* yieldRecycleListName(Class* clasS);
StorageSlot* recycleSlot(Class* clasS);
boolean useFreeListP(Class* clasS);
boolean useSweepListP(Class* clasS);
boolean decidedToRecycleP(Class* clasS);
int computeRecycledItemSize(Class* clasS);
Cons* yieldRecycleListDefinitions(Class* clasS);
Cons* yieldMakeTrees(Class* clasS);
Symbol* yieldConstructorName(Class* clasS);
Cons* yieldCreationTrees(Class* clasS);
Cons* yieldTerminateObjectTrees(Class* clasS);
Cons* yieldCreationOrReuseTrees(Class* clasS);
Cons* yieldCreationOrReuseTreesFromFreeList(Class* clasS);
Cons* yieldCreationOrReuseTreesFromSweepList(Class* clasS);
Cons* yieldCreationOrReuseTreesFromFreeOrSweepList(Class* clasS);
void markDirectEquivalentSlot(Slot* slot);
boolean isContextSensitiveSlotP(StorageSlot* slot);
Cons* yieldInitialValueAssignment(StorageSlot* slot, Keyword* mode);
Cons* yieldInitialValueAssignments(Class* clasS, Keyword* mode);
Cons* yieldLocalInitialValueAssignments(Class* clasS);
Cons* yieldInitializerTrees(Class* clasS);
Cons* yieldConstructorBody(Class* clasS, Cons* requiredassignments);
Cons* yieldConstructorDefinition(Class* clasS);
Cons* yieldExceptionConstructorBody(Class* clasS, Symbol* messageparameter, Cons* requiredassignments);
Cons* yieldExceptionConstructorDefinition(Class* clasS);
Cons* yieldDestructorDefinitions(Class* clasS);
void createConstructorAndDestructorUnits(Class* clasS);
boolean parameterizedClassP(Class* clasS);
boolean classWithInitializerP(Class* clasS);
Symbol* yieldInitializerName(Class* clasS);
Cons* yieldInitializerDefinition(Class* clasS);
void createCppConstructorUnit(Class* clasS);
boolean cppConstructorP(MethodSlot* method);
RecycleList* createRecycleList(Surrogate* classtype, int itemsize);
void clearRecycleList(RecycleList* list);
void clearRecycleLists();
void printRecycleLists();
void maintainRecycleLists();
int recycleListSize(RecycleList* list);
int totalRecycleListsSize();
boolean recycleListSizeL(RecycleList* list1, RecycleList* list2);
void reduceRecycleListSize(RecycleList* list, double fraction);
void sweepTransients();
List* makeNonRecycledList();
void registerRecycledItem(Object* item);
void unregisterRecycledItem(Object* item);
void startRecycleListDebugging();
void stopRecycleListDebugging();
boolean recycleListDebuggingEnabledP();
boolean translateWithRecycleListDebuggingP();
Cons* yieldRegisterRecycledItemTrees();
Cons* yieldUnregisterRecycledItemTrees();
boolean hasNonNullDefaultValueP(StorageSlot* slot);
boolean systemDefinedSlotReaderP(StorageSlot* slot);
boolean systemDefinedSlotWriterP(StorageSlot* slot);
Object* yieldSlotTypeTree(StorageSlot* slot);
Symbol* yieldHardwiredSlotVariable(StorageSlot* slot);
Cons* yieldHardwiredSlotReaderBody(StorageSlot* slot, Cons*& _Return1);
void finalizeAuxiliaryMethod(MethodSlot* method);
Cons* wrapWithDefaultValueAndReturnCode(StorageSlot* slot, Object* defaultexpression);
Cons* yieldSlotReaderTree(StorageSlot* slot, Class* clasS);
Cons* yieldSlotWriterTree(StorageSlot* slot, Class* clasS);
boolean slotValueIsBareLiteralP(Slot* slot);
boolean genericallyAccessibleTypeP(Surrogate* type);
boolean genericSlotReaderP(StorageSlot* slot, Class* clasS);
boolean genericSlotWriterP(StorageSlot* slot, Class* clasS);
boolean slotAccessMethodP(StorageSlot* slot);
Symbol* yieldGenericSlotAccessorName(Class* clasS);
Cons* yieldGenericSlotAccessorDefinition(Class* clasS);
void createGenericSlotAccessorUnit(Class* clasS);
Cons* yieldGenericSlotAccessorAttachment(Class* clasS, Symbol* classref);
cpp_function_code getGenericSlotAccessor(StorageSlot* slot, Class* clasS, boolean warnP);
Cons* yieldMixinClassUsersTree(Class* clasS);
Symbol* yieldMixinSlotReaderName(StorageSlot* slot);
Symbol* yieldMixinSlotWriterName(StorageSlot* slot);
Cons* yieldMixinSlotReaderTree(StorageSlot* slot);
Cons* yieldMixinSlotWriterTree(StorageSlot* slot);
Symbol* yieldNativeSlotReaderName(StorageSlot* slot);
Symbol* yieldNativeSlotWriterName(StorageSlot* slot);
Cons* yieldNativeSlotReaderTree(StorageSlot* slot, Class* clasS);
Cons* yieldNativeSlotWriterTree(StorageSlot* slot, Class* clasS);
void createKeyedEqualityMethodUnit(Class* clasS);
boolean transientObjectP(Object* object);
void helpStartupDefclass1();
void helpStartupDefclass2();
void helpStartupDefclass3();
void helpStartupDefclass4();
void startupDefclass();

// Auxiliary global declarations:
extern Surrogate* SGT_DEFCLASS_STELLA_LITERAL;
extern Surrogate* SGT_DEFCLASS_STELLA_SECOND_CLASS_OBJECT;
extern Symbol* SYM_DEFCLASS_STELLA_NULL;
extern Keyword* KWD_DEFCLASS_COMMON_LISP;
extern Symbol* SYM_DEFCLASS_STELLA_VERBATIM;
extern Symbol* SYM_DEFCLASS_STELLA_DEFINE_CLASS_FROM_STRINGIFIED_SOURCE;
extern Symbol* SYM_DEFCLASS_STELLA_CLASS_CL_NATIVE_TYPE;
extern Keyword* KWD_DEFCLASS_IDL;
extern Symbol* SYM_DEFCLASS_STELLA_CLASS_IDL_NATIVE_TYPE;
extern Keyword* KWD_DEFCLASS_JAVA;
extern Symbol* SYM_DEFCLASS_STELLA_CLASS_JAVA_NATIVE_TYPE;
extern Keyword* KWD_DEFCLASS_CPP;
extern Keyword* KWD_DEFCLASS_CPP_STANDALONE;
extern Symbol* SYM_DEFCLASS_STELLA_CLASS_CPP_NATIVE_TYPE;
extern Surrogate* SGT_DEFCLASS_STELLA_NON_OBJECT;
extern Surrogate* SGT_DEFCLASS_STELLA_NATIVE_EXCEPTION;
extern Keyword* KWD_DEFCLASS_DYNAMIC;
extern Symbol* SYM_DEFCLASS_STELLA_SLOT_INITIAL_VALUE;
extern Keyword* KWD_DEFCLASS_BIT;
extern Surrogate* SGT_DEFCLASS_STELLA_BOOLEAN;
extern Keyword* KWD_DEFCLASS_CLASS;
extern Symbol* SYM_DEFCLASS_STELLA_SLOT_RENAMES;
extern Surrogate* SGT_DEFCLASS_STELLA_UNKNOWN;
extern Symbol* SYM_DEFCLASS_STELLA_SLOT_TYPE_SPECIFIER;
extern Surrogate* SGT_DEFCLASS_STELLA_ANCHORED_TYPE_SPECIFIER;
extern Symbol* SYM_DEFCLASS_STELLA_NEXT_SWEEP_LIST_OBJECT;
extern Keyword* KWD_DEFCLASS_FREE_LIST;
extern Keyword* KWD_DEFCLASS_FREE_AND_SWEEP_LIST;
extern Keyword* KWD_DEFCLASS_SWEEP_LIST;
extern Symbol* SYM_DEFCLASS_STELLA_CLASS_CREATOR;
extern Keyword* KWD_DEFCLASS_USE_COMMON_LISP_STRUCTS;
extern Keyword* KWD_DEFCLASS_USE_COMMON_LISP_VECTOR_STRUCTS;
extern Symbol* SYM_DEFCLASS_STELLA_DEFGLOBAL;
extern Symbol* SYM_DEFCLASS_STELLA_RECYCLE_LIST;
extern Symbol* SYM_DEFCLASS_STELLA_OF;
extern Symbol* SYM_DEFCLASS_STELLA_CREATE_RECYCLE_LIST;
extern Symbol* SYM_DEFCLASS_STELLA_SETQ;
extern Symbol* SYM_DEFCLASS_STELLA_SELF;
extern Symbol* SYM_DEFCLASS_STELLA_MAKE;
extern Symbol* SYM_DEFCLASS_STELLA_WHEN;
extern Symbol* SYM_DEFCLASS_STELLA_DEFINEDp;
extern Symbol* SYM_DEFCLASS_STELLA_FREE;
extern Symbol* SYM_DEFCLASS_STELLA_DYNAMIC_SLOTS;
extern Symbol* SYM_DEFCLASS_STELLA_CLEAR;
extern Symbol* SYM_DEFCLASS_STELLA_UNLESS;
extern Symbol* SYM_DEFCLASS_STELLA_RETURN;
extern Keyword* KWD_DEFCLASS_FORCE_NULL_VALUE;
extern Keyword* KWD_DEFCLASS_NULL_VALUE_ONLY;
extern Symbol* SYM_DEFCLASS_STELLA_AND;
extern Symbol* SYM_DEFCLASS_STELLA_oRECYCLING_ENABLEDpo;
extern Symbol* SYM_DEFCLASS_STELLA_COND;
extern Symbol* SYM_DEFCLASS_STELLA___;
extern Symbol* SYM_DEFCLASS_STELLA_CURRENT_LENGTH;
extern Symbol* SYM_DEFCLASS_STELLA_OTHERWISE;
extern Symbol* SYM_DEFCLASS_STELLA_RECYCLED_ITEMS;
extern Symbol* SYM_DEFCLASS_STELLA_POP;
extern Symbol* SYM_DEFCLASS_STELLA_LIST_OF_RECYCLED_ITEMS;
extern Symbol* SYM_DEFCLASS_STELLA_SETF;
extern Symbol* SYM_DEFCLASS_STELLA_SLOT_VALUE;
extern Symbol* SYM_DEFCLASS_STELLA_UNUSED_ITEMS;
extern Symbol* SYM_DEFCLASS_STELLA_ALL_ITEMS;
extern Symbol* SYM_DEFCLASS_STELLA_ii;
extern Symbol* SYM_DEFCLASS_STELLA_e;
extern Symbol* SYM_DEFCLASS_STELLA_oRECYCLE_LISTS_MAINTENANCE_TIMERo;
extern Symbol* SYM_DEFCLASS_STELLA_MAINTAIN_RECYCLE_LISTS;
extern Keyword* KWD_DEFCLASS_INITIAL_VALUE_ONLY;
extern Keyword* KWD_DEFCLASS_ANY_INITIAL_VALUE;
extern Keyword* KWD_DEFCLASS_CONTEXT_SENSITIVEp;
extern Symbol* SYM_DEFCLASS_STELLA_FALSE;
extern Symbol* SYM_DEFCLASS_STELLA_CLASS_INITIALIZER;
extern Symbol* SYM_DEFCLASS_STELLA_RUN_CONSTRUCTOR_DEMONS;
extern Symbol* SYM_DEFCLASS_STELLA_DEFUN;
extern Keyword* KWD_DEFCLASS_CONSTRUCTORp;
extern Symbol* SYM_DEFCLASS_STELLA_TRUE;
extern Keyword* KWD_DEFCLASS_PUBLICp;
extern Symbol* SYM_DEFCLASS_STELLA_LET;
extern Symbol* SYM_DEFCLASS_STELLA_MESSAGE;
extern Symbol* SYM_DEFCLASS_STELLA_CLASS_DESTRUCTOR;
extern Symbol* SYM_DEFCLASS_STELLA_DEFMETHOD;
extern Surrogate* SGT_DEFCLASS_STELLA_STANDARD_OBJECT;
extern Symbol* SYM_DEFCLASS_STELLA_PUSH;
extern Symbol* SYM_DEFCLASS_STELLA_SWEEP;
extern Symbol* SYM_DEFCLASS_STELLA_UNUSED;
extern Symbol* SYM_DEFCLASS_STELLA_WHILE;
extern Symbol* SYM_DEFCLASS_STELLA_NOT;
extern Symbol* SYM_DEFCLASS_STELLA_EQLp;
extern Symbol* SYM_DEFCLASS_STELLA_UNMAKE;
extern Surrogate* SGT_DEFCLASS_STELLA_VOID;
extern Surrogate* SGT_DEFCLASS_STELLA_TRANSIENT_MIXIN;
extern Symbol* SYM_DEFCLASS_STELLA_RECYCLE_LIST_DEBUGGING_ENABLEDp;
extern Symbol* SYM_DEFCLASS_STELLA_REGISTER_RECYCLED_ITEM;
extern Symbol* SYM_DEFCLASS_STELLA_UNREGISTER_RECYCLED_ITEM;
extern Keyword* KWD_DEFCLASS_NULL_WRAPPER;
extern Symbol* SYM_DEFCLASS_STELLA_INLINE_WRAP_BOOLEAN;
extern Symbol* SYM_DEFCLASS_STELLA_FALSE_WRAPPER;
extern Symbol* SYM_DEFCLASS_STELLA_ANSWER;
extern Symbol* SYM_DEFCLASS_STELLA_IF;
extern Symbol* SYM_DEFCLASS_STELLA_NULLp;
extern Symbol* SYM_DEFCLASS_STELLA_PROGN;
extern Symbol* SYM_DEFCLASS_STELLA_ERROR;
extern Keyword* KWD_DEFCLASS_AUXILIARYp;
extern Symbol* SYM_DEFCLASS_STELLA_VALUE;
extern Symbol* SYM_DEFCLASS_STELLA_IGNORE;
extern Surrogate* SGT_DEFCLASS_STELLA_OBJECT;
extern Keyword* KWD_DEFCLASS_WRAP_FUNCTION;
extern Symbol* SYM_DEFCLASS_STELLA_CAST;
extern Symbol* SYM_DEFCLASS_STELLA_SETVALUEp;
extern Surrogate* SGT_DEFCLASS_STELLA_DYNAMIC_SLOTS_MIXIN;
extern Symbol* SYM_DEFCLASS_STELLA_SLOTNAME;
extern Symbol* SYM_DEFCLASS_STELLA_QUOTE;
extern Symbol* SYM_DEFCLASS_STELLA_CASE;
extern Symbol* SYM_DEFCLASS_STELLA_SET_DYNAMIC_SLOT_VALUE;
extern Symbol* SYM_DEFCLASS_STELLA_LOOKUP;
extern Symbol* SYM_DEFCLASS_STELLA_OBJECT;
extern Symbol* SYM_DEFCLASS_STELLA_SYMBOL;
extern Symbol* SYM_DEFCLASS_STELLA_BOOLEAN;
extern Symbol* SYM_DEFCLASS_STELLA_CLASS_SLOT_ACCESSOR_CODE;
extern Symbol* SYM_DEFCLASS_STELLA_THE_CODE;
extern Keyword* KWD_DEFCLASS_FUNCTION;
extern Symbol* SYM_DEFCLASS_STELLA_TYPECASE;
extern Symbol* SYM_DEFCLASS_STELLA_EQp;
extern Symbol* SYM_DEFCLASS_STELLA_OTHER;
extern Symbol* SYM_DEFCLASS_STELLA_EQUAL;
extern Symbol* SYM_DEFCLASS_STELLA_STARTUP_DEFCLASS;
extern Symbol* SYM_DEFCLASS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
