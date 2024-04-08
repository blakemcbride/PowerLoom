//  -*- Mode: C++ -*-

// cpp-class-out.hh

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

// Function signatures:
Cons* cppYieldInitialNullValue();
Cons* cppYieldMemberVarTree(StorageSlot* slot, Class* clasS);
Cons* cppYieldParameterizedMemberVarTree(StorageSlot* slot, Class* clasS);
Cons* cppYieldStaticMemberAllocationTree(StorageSlot* slot, Class* clasS);
Cons* cppYieldMemberFuncSignatureTree(MethodSlot* method);
Cons* cppYieldConstructorSignatureTree(MethodSlot* method);
Cons* cppYieldExceptionConstructorDefinition(Class* clasS);
boolean slotHasClassParameterTypeP(StorageSlot* slot, Class* clasS);
Symbol* getSlotClassParameterName(StorageSlot* slot);
boolean cppNativeMethodP(MethodSlot* methodslot);
Cons* cppGetParameterizedMemberVariableDefinitions(Class* clasS);
Cons* cppGetMemberVariableDefinitions(Class* clasS, Cons*& _Return1);
Cons* cppGetStaticVariableDefinitions(Class* clasS);
Cons* cppGetConstructorDefinitions(Class* clasS);
Cons* cppGetMethodDefinitions(Class* clasS, Cons*& _Return1);
void markRenamingSlots(Class* clasS);
boolean cppClassHasOnlyNativeParentsP(Class* clasS);
Cons* cppTranslateDefineNativeClassUnit(TranslationUnit* unit);
void startupCppClassOut();

// Auxiliary global declarations:
extern Surrogate* SGT_CPP_CLASS_OUT_STELLA_OBJECT;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_DOCUMENTATION;
extern Keyword* KWD_CPP_CLASS_OUT_EMBEDDED;
extern Keyword* KWD_CPP_CLASS_OUT_INSTANCE;
extern Keyword* KWD_CPP_CLASS_OUT_CLASS;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_NULL;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_FUNCTION;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_FUNCTION_CALL;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_IDENT;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_ACTUALS;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_SLOT_TYPE_SPECIFIER;
extern Surrogate* SGT_CPP_CLASS_OUT_STELLA_ANCHORED_TYPE_SPECIFIER;
extern Surrogate* SGT_CPP_CLASS_OUT_STELLA_UNKNOWN;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_DEFINEDp;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_NULLp;
extern Surrogate* SGT_CPP_CLASS_OUT_STELLA_METHOD_SLOT;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_CLASS_CPP_NATIVE_TYPE;
extern Keyword* KWD_CPP_CLASS_OUT_CPP;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_GC;
extern Keyword* KWD_CPP_CLASS_OUT_CPP_STANDALONE;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_CLASS;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_COMMENT;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_DECLARATIONS;
extern Keyword* KWD_CPP_CLASS_OUT_PUBLIC;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_SIGNATURES;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_CPP_DEFINITIONS;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_STARTUP_CPP_CLASS_OUT;
extern Symbol* SYM_CPP_CLASS_OUT_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
