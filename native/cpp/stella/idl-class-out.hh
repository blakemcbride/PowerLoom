//  -*- Mode: C++ -*-

// idl-class-out.hh

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
Cons* idlYieldInitialNullValue();
Cons* idlYieldAttributeTree(StorageSlot* slot, Class* clasS);
Cons* idlYieldParameterizedAttributeTree(StorageSlot* slot, Class* clasS);
Cons* idlYieldStaticMemberAllocationTree(StorageSlot* slot, Class* clasS);
Cons* idlYieldOperationSignatureTree(MethodSlot* method);
Cons* idlYieldConstructorSignatureTree(MethodSlot* method);
boolean illegalIdlMethodP(MethodSlot* methodslot);
Cons* idlGetParameterizedAttributeDefinitions(Class* clasS);
Cons* idlGetAttributeDefinitions(Class* clasS);
Cons* idlGetStaticVariableDefinitions(Class* clasS);
boolean idlConstructorP(MethodSlot* method);
Cons* idlGetConstructorDefinitions(Class* clasS);
Cons* idlGetOperationDefinitions(Class* clasS);
Symbol* idlClassCategory(Class* clasS);
Cons* idlTranslateDefineNativeClassUnit(TranslationUnit* unit);
void startupIdlClassOut();

// Auxiliary global declarations:
extern Symbol* SYM_IDL_CLASS_OUT_STELLA_IDL_INTERFACE;
extern Keyword* KWD_IDL_CLASS_OUT_EMBEDDED;
extern Keyword* KWD_IDL_CLASS_OUT_INSTANCE;
extern Keyword* KWD_IDL_CLASS_OUT_CLASS;
extern Surrogate* SGT_IDL_CLASS_OUT_STELLA_METHOD_SLOT;
extern Surrogate* SGT_IDL_CLASS_OUT_STELLA_VOID;
extern Symbol* SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYsinterface;
extern Symbol* SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYsstruct;
extern Symbol* SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYsenum;
extern Symbol* SYM_IDL_CLASS_OUT_STELLA_sIDL_THEORYstypedef;
extern Symbol* SYM_IDL_CLASS_OUT_STELLA_IDL_STRUCT;
extern Symbol* SYM_IDL_CLASS_OUT_STELLA_IDL_ENUM;
extern Symbol* SYM_IDL_CLASS_OUT_STELLA_IDL_TYPEDEF;
extern Symbol* SYM_IDL_CLASS_OUT_STELLA_IDL_DECLARATIONS;
extern Symbol* SYM_IDL_CLASS_OUT_STELLA_IDL_SIGNATURES;
extern Symbol* SYM_IDL_CLASS_OUT_STELLA_STARTUP_IDL_CLASS_OUT;
extern Symbol* SYM_IDL_CLASS_OUT_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
