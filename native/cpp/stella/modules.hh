//  -*- Mode: C++ -*-

// modules.hh

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
extern Keyword* oSUBCONTEXT_REVISION_POLICYo;
extern DECLARE_STELLA_SPECIAL(oSHADOWEDSURROGATESo, Cons* );
extern HookList* oDEFINE_MODULE_HOOKSo;
extern Cons* oMODULE_NON_STRUCTURAL_OPTIONSo;

// Function signatures:
Context* computeContextOrModuleFromPathname(const char* pathname, boolean moduleP, boolean symbolnameP, int& _Return1);
boolean componentMatchP(const char* component, const char* string, int start, int end);
Module* computeModuleAndBareName(const char* name, const char*& _Return1);
Context* helpGetStellaContextOrModule(const char* pathname, boolean moduleP);
Context* getStellaContext(const char* pathname, boolean errorP);
Module* getStellaModule(const char* pathname, boolean errorP);
Module* helpGetStellaModule(const char* pathname, boolean errorP);
const char* coerceToModuleName(Object* namespec, boolean warnP);
Module* coerceToModule(Object* object, boolean warnP);
Module* findOrCreateModule(const char* pathname);
Module* changeCurrentModule(Module* module);
Context* changeCurrentContext(Context* context);
Context* stringChangeContext(const char* contextname);
Module* stringChangeModule(const char* modulename);
void normalizeParentModules(Module* self);
void inheritUsedModules(Module* module);
void uninheritUsedModules(Module* module);
void finalizeModule(Module* self);
void finalizeWorld(World* self);
void destroyModule(Module* self);
void helpDestroyModule(Module* self);
void destroyWorld(World* self);
void stringDestroyContext(const char* self);
void linkToParentModule(Module* self, Module* parent, boolean insertFirstP);
void incorporateModuleName(Module* module, const char* name);
void incorporateIncludesModules(Module* module, Object* includees);
void incorporateUsesModules(Module* module, Object* usees);
boolean trueOptionP(Object* value);
void incorporateModuleOptions(Module* self, Cons* options);
void undefineModule(Module* oldmodule, Module* newmodule);
Module* defineModule(const char* name, Cons* options);
void updateNonStructuralModuleOptions(Module* oldmodule, Module* newmodule, const char* newoptions);
boolean identicalModuleStructureP(Module* oldmodule, Module* newmodule, const char* newoptions);
Module* defineModuleFromStringifiedSource(const char* name, const char* stringifiedoptions);
Cons* yieldDefineModule(Module* module);
void defmodule(Object* name, Cons* options);
void defmoduleEvaluatorWrapper(Cons* arguments);
Module* inModule(Object* name);
World* createWorld(Context* parentcontext, const char* name);
World* pushWorld();
Context* popWorld();
AllPurposeIterator* allSubcontexts(Context* context, Keyword* traversal);
boolean allSubcontextsNextP(AllPurposeIterator* self);
boolean allTopdownSubcontextsNextP(AllPurposeIterator* self);
Iterator* allContexts();
boolean filterModuleP(Object* self, AllPurposeIterator* iterator);
Iterator* allModules();
Cons* listModules(boolean kbOnlyP);
Cons* listModulesEvaluatorWrapper(Cons* arguments);
Iterator* allIncludedModules(Module* self);
Cons* visibleModules(Module* from);
Cons* helpMemoizeVisibleModules(Module* from);
boolean cardinalModuleP(Module* self);
boolean visibleFromP(Context* viewedcontext, Context* fromcontext);
void clearOneContext(Context* self);
void helpClearContext(Context* self);
void clearContext(Context* self);
void callClearModule(Cons* name);
void callClearModuleEvaluatorWrapper(Cons* arguments);
void clearModule(Cons* name);
void clearModuleEvaluatorWrapper(Cons* arguments);
void helpStartupModules1();
void helpStartupModules2();
void startupModules();

// Auxiliary global declarations:
extern Keyword* KWD_MODULES_CLEAR;
extern Surrogate* SGT_MODULES_STELLA_MODULE;
extern Keyword* KWD_MODULES_SYMBOL;
extern Keyword* KWD_MODULES_SURROGATE;
extern Keyword* KWD_MODULES_KEYWORD;
extern Surrogate* SGT_MODULES_STELLA_F_GET_STELLA_MODULE_MEMO_TABLE_000;
extern Symbol* SYM_MODULES_STELLA_NAME;
extern Surrogate* SGT_MODULES_STELLA_MUTABLE_STRING_WRAPPER;
extern Symbol* SYM_MODULES_STELLA_SHADOWED_SURROGATES;
extern Keyword* KWD_MODULES_MODULE_UPDATE;
extern Surrogate* SGT_MODULES_STELLA_CONS;
extern Symbol* SYM_MODULES_STELLA_TRUE;
extern Surrogate* SGT_MODULES_STELLA_SYMBOL;
extern Keyword* KWD_MODULES_INCLUDES;
extern Keyword* KWD_MODULES_USES;
extern Keyword* KWD_MODULES_SHADOW;
extern Keyword* KWD_MODULES_DOCUMENTATION;
extern Keyword* KWD_MODULES_CASE_SENSITIVEp;
extern Keyword* KWD_MODULES_APIp;
extern Symbol* SYM_MODULES_STELLA_APIp;
extern Keyword* KWD_MODULES_LISP_PACKAGE;
extern Symbol* SYM_MODULES_STELLA_MODULE_LISP_PACKAGE;
extern Keyword* KWD_MODULES_CPP_PACKAGE;
extern Symbol* SYM_MODULES_STELLA_MODULE_CPP_PACKAGE;
extern Keyword* KWD_MODULES_JAVA_PACKAGE;
extern Symbol* SYM_MODULES_STELLA_JAVA_PACKAGE;
extern Keyword* KWD_MODULES_JAVA_CATCHALL_CLASS;
extern Symbol* SYM_MODULES_STELLA_JAVA_FLOTSAM_CLASS;
extern Keyword* KWD_MODULES_NICKNAME;
extern Keyword* KWD_MODULES_CLEARABLEp;
extern Symbol* SYM_MODULES_STELLA_CLEARABLEp;
extern Keyword* KWD_MODULES_PROTECT_SURROGATESp;
extern Symbol* SYM_MODULES_STELLA_PROTECT_SURROGATESp;
extern Keyword* KWD_MODULES_CODE_ONLYp;
extern Symbol* SYM_MODULES_STELLA_CODE_ONLYp;
extern Keyword* KWD_MODULES_NAMESPACEp;
extern Symbol* SYM_MODULES_STELLA_NAMESPACEp;
extern Keyword* KWD_MODULES_REQUIRES;
extern Keyword* KWD_MODULES_DESTROY;
extern Keyword* KWD_MODULES_PRESERVE;
extern Keyword* KWD_MODULES_PREORDER;
extern Surrogate* SGT_MODULES_STELLA_WORLD;
extern Keyword* KWD_MODULES_TOPDOWN;
extern Symbol* SYM_MODULES_STELLA_DEFINE_MODULE_FROM_STRINGIFIED_SOURCE;
extern Symbol* SYM_MODULES_STELLA_WORLD_NAME;
extern Keyword* KWD_MODULES_POSTORDER;
extern Keyword* KWD_MODULES_INORDER;
extern Surrogate* SGT_MODULES_STELLA_F_VISIBLE_MODULES_MEMO_TABLE_000;
extern Symbol* SYM_MODULES_STELLA_STARTUP_MODULES;
extern Symbol* SYM_MODULES_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
