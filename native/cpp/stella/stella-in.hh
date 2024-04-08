//  -*- Mode: C++ -*-

// stella-in.hh

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
extern boolean oREDEFINE_IDENTICAL_CLASSESpo;
extern List* oUNSUPPORTED_EXTERNAL_SLOT_OPTIONSo;
extern MethodSlot* oDEFAULT_OPTION_HANDLERo;

// Function signatures:
Object* permanentifyForm(Object* form);
Object* transientifyForm(Object* form);
const char* stringifyInModule(Object* tree, Module* module);
Object* unstringifyInModule(const char* string, Module* module);
Object* unstringifyStellaSource(const char* source, Module* module);
List* collectFeatureList(Object* tree);
KeyValueList* collectKeyValueList(Object* tree);
MethodSlot* defineInlineMethod(Symbol* name, Cons* parametersandbody);
Class* helpDefineClassFromParseTree(Cons* parsetree, const char* stringifiedsource);
StorageSlot* defineStorageSlotFromParseTree(Cons* slotdef, Surrogate* owner);
Module* recordSlotHomeModule(Slot* self);
boolean explicitlyQualifiedNameP(GeneralizedSymbol* name, Module* definitionmodule);
Class* getIdenticalClass(const char* classname, const char* stringifiedsource);
Class* defineClassFromParseTree(Cons* parsetree);
Class* defineClassFromStringifiedSource(const char* classname, const char* stringifiedsource);
Cons* extractOptions(Cons* tree, KeyValueList* optionstable);
Object* destructureDefmethodTree(Cons* methodTree, KeyValueList* optionsTable, Cons*& _Return1, Cons*& _Return2);
Symbol* yieldSetterMethodName(Symbol* methodname);
Symbol* destructureMethodNameTree(Object* nametree, Cons*& _Return1);
void inPlaceNormalizeMethodOptions(KeywordKeyValueList* methodoptions, Symbol* methodname);
MethodSlot* getFunctionWithIdenticalSignature(Symbol* name, const char* stringifiedsource);
MethodSlot* getMethodWithIdenticalSignature(Symbol* name, Cons* parameterstree, const char* stringifiedsource);
MethodSlot* helpDefineMethodFromParseTree(Cons* inputtree, const char* stringifiedsource, boolean& _Return1);
MethodSlot* defineMethodFromParseTree(Cons* parsetree);
const char* stringifyMethodSignature(Cons* parsetree);
boolean stringifyMethodBodyP(MethodSlot* method);
MethodSlot* defineMethodFromStringifiedSource(const char* methodname, const char* classname, const char* stringifiedsource);
void defineMethodObject(const char* definition, CodeWrapper* code, CodeWrapper* wrappercode);
void defineInlineMethodCode(Surrogate* classtype, Symbol* methodname, CodeWrapper* code, CodeWrapper* wrappercode);
StorageSlot* defineExternalSlotFromParseTree(Cons* parsetree);
StorageSlot* defineExternalSlotFromStringifiedSource(const char* stringifiedsource);
StorageSlot* lookupSlotFromOptionKeyword(Surrogate* owner, Keyword* keyword);
MethodSlot* lookupOptionHandler(StorageSlot* slot);
boolean runOptionHandlerP(Object* object, Keyword* option, Object* valuetree);
void defaultOptionHandler(Object* self, StorageSlot* slot, Object* tree);
void helpStartupStellaIn1();
void helpStartupStellaIn2();
void startupStellaIn();

// Auxiliary global declarations:
extern Symbol* SYM_STELLA_IN_STELLA_TRUE;
extern Symbol* SYM_STELLA_IN_STELLA_FALSE;
extern Surrogate* SGT_STELLA_IN_STELLA_CONS;
extern Surrogate* SGT_STELLA_IN_STELLA_GENERALIZED_SYMBOL;
extern Symbol* SYM_STELLA_IN_STELLA_DEFMETHOD;
extern Keyword* KWD_STELLA_IN_PUBLIC_SLOTS;
extern Keyword* KWD_STELLA_IN_SLOTS;
extern Keyword* KWD_STELLA_IN_PUBLIC_METHODS;
extern Keyword* KWD_STELLA_IN_METHODS;
extern Keyword* KWD_STELLA_IN_PARAMETERS;
extern Keyword* KWD_STELLA_IN_KEY;
extern Keyword* KWD_STELLA_IN_SYNONYMS;
extern Keyword* KWD_STELLA_IN_DOCUMENTATION;
extern Keyword* KWD_STELLA_IN_CL_NATIVE_TYPE;
extern Keyword* KWD_STELLA_IN_CPP_NATIVE_TYPE;
extern Keyword* KWD_STELLA_IN_JAVA_NATIVE_TYPE;
extern Keyword* KWD_STELLA_IN_IDL_NATIVE_TYPE;
extern Keyword* KWD_STELLA_IN_ABSTRACTp;
extern Keyword* KWD_STELLA_IN_ACTIVEp;
extern Keyword* KWD_STELLA_IN_PUBLICp;
extern Keyword* KWD_STELLA_IN_CL_STRUCTp;
extern Keyword* KWD_STELLA_IN_MIXINp;
extern Keyword* KWD_STELLA_IN_RECYCLE_METHOD;
extern Symbol* SYM_STELLA_IN_STELLA_NEXT_SWEEP_LIST_OBJECT;
extern Keyword* KWD_STELLA_IN_TYPE;
extern Keyword* KWD_STELLA_IN_EXTENSION;
extern Keyword* KWD_STELLA_IN_CREATOR;
extern Keyword* KWD_STELLA_IN_DESTRUCTOR;
extern Keyword* KWD_STELLA_IN_INITIALIZER;
extern Keyword* KWD_STELLA_IN_TERMINATOR;
extern Keyword* KWD_STELLA_IN_EQUALITY_TEST;
extern Keyword* KWD_STELLA_IN_INITIAL_VALUE;
extern Keyword* KWD_STELLA_IN_PRINT_FORM;
extern Keyword* KWD_STELLA_IN_PROPERTIES;
extern Keyword* KWD_STELLA_IN_META_ATTRIBUTES;
extern Keyword* KWD_STELLA_IN_CHILDREN;
extern Keyword* KWD_STELLA_IN_INITIALLY;
extern Keyword* KWD_STELLA_IN_DEFAULT;
extern Symbol* SYM_STELLA_IN_STELLA_LIKE;
extern Keyword* KWD_STELLA_IN_ALLOCATION;
extern Keyword* KWD_STELLA_IN_READER;
extern Keyword* KWD_STELLA_IN_WRITER;
extern Keyword* KWD_STELLA_IN_INVERSE;
extern Keyword* KWD_STELLA_IN_RENAMES;
extern Keyword* KWD_STELLA_IN_REQUIREDp;
extern Keyword* KWD_STELLA_IN_COMPONENTp;
extern Keyword* KWD_STELLA_IN_READ_ONLYp;
extern Keyword* KWD_STELLA_IN_CONTEXT_SENSITIVEp;
extern Keyword* KWD_STELLA_IN_HARDWIREDp;
extern Keyword* KWD_STELLA_IN_OPTION_KEYWORD;
extern Keyword* KWD_STELLA_IN_OPTION_HANDLER;
extern Symbol* SYM_STELLA_IN_STELLA_SLOT_HOME_MODULE;
extern Symbol* SYM_STELLA_IN_STELLA_SETTER;
extern Keyword* KWD_STELLA_IN_RETURN_TYPES;
extern Keyword* KWD_STELLA_IN_STORAGE_SLOT;
extern Keyword* KWD_STELLA_IN_INHERITS_THROUGH;
extern Keyword* KWD_STELLA_IN_SETTERp;
extern Keyword* KWD_STELLA_IN_NATIVEp;
extern Keyword* KWD_STELLA_IN_CONSTRUCTORp;
extern Keyword* KWD_STELLA_IN_AUXILIARYp;
extern Keyword* KWD_STELLA_IN_GLOBALLY_INLINEp;
extern Keyword* KWD_STELLA_IN_COMMANDp;
extern Keyword* KWD_STELLA_IN_LISP_MACROp;
extern Keyword* KWD_STELLA_IN_EVALUATE_ARGUMENTSp;
extern Keyword* KWD_STELLA_IN_C_CALLABLEp;
extern Keyword* KWD_STELLA_IN_INLINE;
extern Symbol* SYM_STELLA_IN_STELLA_DEFUN;
extern Symbol* SYM_STELLA_IN_STELLA_SLOT_AUXILIARYp;
extern Symbol* SYM_STELLA_IN_STELLA_METHOD_GLOBALLY_INLINEp;
extern Keyword* KWD_STELLA_IN_DYNAMIC;
extern Surrogate* SGT_STELLA_IN_STELLA_DYNAMIC_SLOTS_MIXIN;
extern Symbol* SYM_STELLA_IN_STELLA_SLOT_OPTION_KEYWORD;
extern Symbol* SYM_STELLA_IN_STELLA_DEFAULT_OPTION_HANDLER;
extern Symbol* SYM_STELLA_IN_STELLA_SLOT_OPTION_HANDLER;
extern Surrogate* SGT_STELLA_IN_STELLA_BOOLEAN;
extern Symbol* SYM_STELLA_IN_STELLA_STARTUP_STELLA_IN;
extern Symbol* SYM_STELLA_IN_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
