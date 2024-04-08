//  -*- Mode: C++ -*-

// demons.hh

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

// Class definitions:
class HookList : public KeyValueList {
// Each HOOK-LIST object contains a list of zero or
// more function codes that get funcall'd some procedure.
public:
  const char* signature;
  const char* documentation;
public:
  virtual Surrogate* primaryType();
};


// Global declarations:
extern StringHashTable* oDEMONS_TABLEo;
extern List* oCONSTRUCTOR_DEMONSo;
extern List* oDESTRUCTOR_DEMONSo;
extern List* oALL_SLOTS_DEMONSo;
extern List* oALL_SLOTS_GUARD_DEMONSo;
extern HookList* oCHANGE_MODULE_HOOKSo;
extern HookList* oCLEAR_MODULE_HOOKSo;
extern HookList* oDESTROY_CONTEXT_HOOKSo;
extern HookList* oREDEFINE_RELATION_HOOKSo;
extern HookList* oFINALIZE_RELATION_HOOKSo;
extern HookList* oBLOCK_NATIVE_CLASS_CREATION_HOOKSo;
extern HookList* oSTELLA_EXIT_HOOKSo;

// Function signatures:
boolean validateDemonReferencesP(Demon* demon);
boolean incorporateDemonOptionsP(Demon* demon, PropertyList* options);
Demon* lookupDemon(const char* name);
Demon* defineDemon(const char* name, int options, ...);
List* injectDemon(List* demonlist, Demon* demon);
List* ejectDemon(List* demonlist, Demon* demon);
void activateDemon(Demon* demon);
void deactivateDemon(Demon* demon);
Cons* destructureDefdemonBody(Cons* demontree, Cons*& _Return1);
void inPlaceNormalizeDemonOptions(Cons* optionstree);
Object* defdemon(StringWrapper* name, Cons* parameterstree, Cons* optionsandbody);
Object* readSlotValue(StandardObject* self, StorageSlot* slot);
Object* writeSlotValue(StandardObject* self, StorageSlot* slot, Object* value);
Object* putSlotValue(StandardObject* self, StorageSlot* slot, Object* value);
void dropSlotValue(StandardObject* self, StorageSlot* slot, Object* value);
int cppFindNativeSlotValueOffset(StandardObject* self, StorageSlot* slot);
boolean checkForSlotDemonsP(StorageSlot* slot);
boolean runSlotGuardDemonsP(StandardObject* self, StorageSlot* slot, Object* oldvalue, Object* newvalue);
void runSlotDemons(StandardObject* self, StorageSlot* slot, Object* oldvalue, Object* newvalue);
void runConstructorDemons(StandardObject* self);
void runDestructorDemons(StandardObject* self);
Cons* yieldActiveSlotReaderBody(StorageSlot* slot, Object* defaultexpression);
void cantOverwriteActiveCollectionSlot(StandardObject* self, Symbol* slotname);
Cons* yieldActiveSlotWriterBody(StorageSlot* slot);
HookList* newHookList();
Object* accessHookListSlotValue(HookList* self, Symbol* slotname, Object* value, boolean setvalueP);
void addHook(HookList* hooklist, Symbol* hookfunction);
void dropHook(HookList* hooklist, Symbol* hookfunction);
void runHooks(HookList* hooklist, Object* argument);
void helpStartupDemons1();
void helpStartupDemons2();
void startupDemons();

// Auxiliary global declarations:
extern Keyword* KWD_DEMONS_MODIFY;
extern Keyword* KWD_DEMONS_CREATE;
extern Keyword* KWD_DEMONS_DESTROY;
extern Keyword* KWD_DEMONS_ALL;
extern Keyword* KWD_DEMONS_CLASS;
extern Keyword* KWD_DEMONS_SLOT;
extern Keyword* KWD_DEMONS_CODE;
extern Keyword* KWD_DEMONS_METHOD;
extern Keyword* KWD_DEMONS_GUARDp;
extern Keyword* KWD_DEMONS_INHERITEDp;
extern Keyword* KWD_DEMONS_DOCUMENTATION;
extern Keyword* KWD_DEMONS_ACTIVATEp;
extern Symbol* SYM_DEMONS_STELLA_SLOT_GUARD_DEMONS;
extern Symbol* SYM_DEMONS_STELLA_SLOT_DEMONS;
extern Symbol* SYM_DEMONS_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS;
extern Symbol* SYM_DEMONS_STELLA_CLASS_CONSTRUCTOR_DEMONS;
extern Symbol* SYM_DEMONS_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS;
extern Symbol* SYM_DEMONS_STELLA_CLASS_DESTRUCTOR_DEMONS;
extern Symbol* SYM_DEMONS_STELLA_WRAP_LITERAL;
extern Symbol* SYM_DEMONS_STELLA_TRUE;
extern Symbol* SYM_DEMONS_STELLA_WRAP_BOOLEAN;
extern Symbol* SYM_DEMONS_STELLA_FALSE;
extern Symbol* SYM_DEMONS_STELLA_PROGN;
extern Symbol* SYM_DEMONS_STELLA_DEFUN;
extern Symbol* SYM_DEMONS_STELLA_STARTUP_TIME_PROGN;
extern Symbol* SYM_DEMONS_STELLA_DEFINE_DEMON;
extern Symbol* SYM_DEMONS_STELLA_THE_CODE;
extern Keyword* KWD_DEMONS_FUNCTION;
extern Surrogate* SGT_DEMONS_STELLA_OBJECT;
extern Surrogate* SGT_DEMONS_STELLA_BOOLEAN;
extern Surrogate* SGT_DEMONS_STELLA_INTEGER;
extern Surrogate* SGT_DEMONS_STELLA_LONG_INTEGER;
extern Surrogate* SGT_DEMONS_STELLA_FLOAT;
extern Surrogate* SGT_DEMONS_STELLA_STRING;
extern Surrogate* SGT_DEMONS_STELLA_MUTABLE_STRING;
extern Surrogate* SGT_DEMONS_STELLA_CHARACTER;
extern Surrogate* SGT_DEMONS_STELLA_FUNCTION_CODE;
extern Surrogate* SGT_DEMONS_STELLA_METHOD_CODE;
extern Surrogate* SGT_DEMONS_STELLA_MUTABLE_STRING_WRAPPER;
extern Surrogate* SGT_DEMONS_STELLA_FUNCTION_CODE_WRAPPER;
extern Surrogate* SGT_DEMONS_STELLA_METHOD_CODE_WRAPPER;
extern Symbol* SYM_DEMONS_STELLA_LET;
extern Symbol* SYM_DEMONS_STELLA_VALUE;
extern Symbol* SYM_DEMONS_STELLA_SLOT_VALUE;
extern Symbol* SYM_DEMONS_STELLA_SELF;
extern Symbol* SYM_DEMONS_STELLA_WHEN;
extern Symbol* SYM_DEMONS_STELLA_DEFINEDp;
extern Symbol* SYM_DEMONS_STELLA_RETURN;
extern Symbol* SYM_DEMONS_STELLA_SETQ;
extern Symbol* SYM_DEMONS_STELLA_NEW;
extern Symbol* SYM_DEMONS_STELLA_SETF;
extern Symbol* SYM_DEMONS_STELLA_OWNER_INSTANCE;
extern Symbol* SYM_DEMONS_STELLA_ACTIVE_SLOT;
extern Symbol* SYM_DEMONS_STELLA_GET_SLOT;
extern Symbol* SYM_DEMONS_STELLA_BQUOTE;
extern Symbol* SYM_DEMONS_STELLA_CANT_OVERWRITE_ACTIVE_COLLECTION_SLOT;
extern Surrogate* SGT_DEMONS_STELLA_LITERAL;
extern Symbol* SYM_DEMONS_STELLA_SLOT;
extern Symbol* SYM_DEMONS_STELLA_OLDVALUE;
extern Symbol* SYM_DEMONS_STELLA_NOT;
extern Symbol* SYM_DEMONS_STELLA_EQLp;
extern Symbol* SYM_DEMONS_STELLA_IF;
extern Symbol* SYM_DEMONS_STELLA_CHECK_FOR_SLOT_DEMONSp;
extern Symbol* SYM_DEMONS_STELLA_WRAPPEDOLDVALUE;
extern Symbol* SYM_DEMONS_STELLA_CHOOSE;
extern Symbol* SYM_DEMONS_STELLA_NULL;
extern Symbol* SYM_DEMONS_STELLA_WRAPPEDNEWVALUE;
extern Symbol* SYM_DEMONS_STELLA_RUN_SLOT_GUARD_DEMONSp;
extern Symbol* SYM_DEMONS_STELLA_RUN_SLOT_DEMONS;
extern Symbol* SYM_DEMONS_STELLA_FREE;
extern Symbol* SYM_DEMONS_STELLA_AND;
extern Symbol* SYM_DEMONS_STELLA_EQp;
extern Surrogate* SGT_DEMONS_STELLA_HOOK_LIST;
extern Symbol* SYM_DEMONS_STELLA_SIGNATURE;
extern Symbol* SYM_DEMONS_STELLA_DOCUMENTATION;
extern Symbol* SYM_DEMONS_STELLA_STARTUP_DEMONS;
extern Symbol* SYM_DEMONS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
