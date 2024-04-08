//  -*- Mode: C++ -*-

// contexts.hh

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
extern boolean oUNLINK_DISCARDED_CONTEXTS_ON_READpo;
extern boolean oUNLINK_DISCARDED_CONTEXTS_ON_WRITEpo;
extern boolean oCONTEXT_BACKTRACKING_MODEo;

// Function signatures:
boolean csValueP(Object* self);
boolean subcontextP(Context* subcontext, Context* supercontext);
boolean discardedContextP(Context* context);
Context* helpFindContextByNumber(int number, List* siblings);
Context* findContextByNumber(int contextnumber);
Context* stringGetStellaContextSlowly(const char* self);
Context* integerGetStellaContextSlowly(int self);
Context* changeContextSlowly(Context* self);
Context* cc(Cons* name);
Context* ccEvaluatorWrapper(Cons* arguments);
Context* ccc(Cons* name);
Context* cccEvaluatorWrapper(Cons* arguments);
void printContext(Context* self, std::ostream* stream);
void helpPrintContextTree(List* list, int level);
void printContextTree(Context* root);
Object* accessInContext(Object* value, Context* homecontext, boolean dontinheritP);
void helpInsertACsValue(KvCons* kvcons, Object* newvalue, Context* target, boolean overwriteP);
Object* updateInContext(Object* oldvalue, Object* newvalue, Context* homecontext, boolean copytochildrenP);
void copyCurrentValueToChildren(CsValue* csvalue, Context* homecontext, Object* parentvalue);
void startupContexts();

// Auxiliary global declarations:
extern Surrogate* SGT_CONTEXTS_STELLA_CS_VALUE;
extern Surrogate* SGT_CONTEXTS_STELLA_MODULE;
extern Surrogate* SGT_CONTEXTS_STELLA_WORLD;
extern Symbol* SYM_CONTEXTS_STELLA_WORLD_NAME;
extern Symbol* SYM_CONTEXTS_STELLA_STARTUP_CONTEXTS;
extern Symbol* SYM_CONTEXTS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
