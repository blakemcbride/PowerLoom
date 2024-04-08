//  -*- Mode: C++ -*-

// macros.hh

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
Object* pushq(Symbol* variable, Object* value);
Object* popq(Symbol* variable);
Object* pushf(Cons* place, Object* value);
Object* pushqNew(Symbol* variable, Object* value);
Object* stella_Increment(Object* place, Cons* increment);
Object* stella_Decrement(Object* place, Cons* decrement);
Object* oneI(Object* expression);
Object* one(Object* expression);
Object* setqP(Symbol* variable, Cons* expression);
Object* firstDefined(Cons* forms);
Object* allDefinedP(Cons* forms);
Object* either(Object* value1, Object* value2);
Object* collect(Cons* body);
Object* withPermanentObjects(Cons* body);
Object* withTransientObjects(Cons* body);
Object* ignore(Cons* variables);
Object* onlyIf(Object* test, Object* expression);
Object* phaseToInteger(Keyword* startuptimephase);
Object* ifOutputLanguage(Keyword* language, Object* thenform, Object* elseform);
Object* ifStellaFeature(Keyword* feature, Object* thenform, Object* elseform);
Object* withinWorld(Object* worldform, Cons* body);
Object* withinContext(Object* contextform, Cons* body);
Object* withinModule(Object* moduleform, Cons* body);
Object* coerceARestToCons(Symbol* restvariable);
Object* withSystemDefinition(Object* systemnameexpression, Cons* body);
Object* defmain(Cons* varlist, Cons* body);
void helpStartupMacros1();
void startupMacros();

// Auxiliary global declarations:
extern Symbol* SYM_MACROS_STELLA_SETQ;
extern Symbol* SYM_MACROS_STELLA_CONS;
extern Symbol* SYM_MACROS_STELLA_VRLET;
extern Symbol* SYM_MACROS_STELLA_VALUE;
extern Symbol* SYM_MACROS_STELLA_REST;
extern Symbol* SYM_MACROS_STELLA_SETF;
extern Symbol* SYM_MACROS_STELLA_CHOOSE;
extern Symbol* SYM_MACROS_STELLA_MEMBERp;
extern Symbol* SYM_MACROS_STELLA_i;
extern Symbol* SYM_MACROS_STELLA___;
extern Keyword* KWD_MACROS_JAVA;
extern Keyword* KWD_MACROS_FUNCTION;
extern Symbol* SYM_MACROS_STELLA__;
extern Symbol* SYM_MACROS_STELLA_DEFINEDp;
extern Symbol* SYM_MACROS_STELLA_NULL;
extern Symbol* SYM_MACROS_STELLA_FIRST_DEFINED;
extern Symbol* SYM_MACROS_STELLA_TRUE;
extern Symbol* SYM_MACROS_STELLA_AND;
extern Symbol* SYM_MACROS_STELLA_FOREACH;
extern Symbol* SYM_MACROS_STELLA_NIL;
extern Symbol* SYM_MACROS_STELLA_COLLECT;
extern Symbol* SYM_MACROS_STELLA_INTO;
extern Symbol* SYM_MACROS_STELLA_SPECIAL;
extern Symbol* SYM_MACROS_STELLA_oTRANSIENTOBJECTSpo;
extern Symbol* SYM_MACROS_STELLA_FALSE;
extern Keyword* KWD_MACROS_READ_ONLYp;
extern Symbol* SYM_MACROS_STELLA_oCONTEXTo;
extern Symbol* SYM_MACROS_STELLA_SAFETY;
extern Symbol* SYM_MACROS_STELLA_EQLp;
extern Symbol* SYM_MACROS_STELLA_BASE_MODULE;
extern Symbol* SYM_MACROS_STELLA_CAST;
extern Symbol* SYM_MACROS_STELLA_WORLD;
extern Symbol* SYM_MACROS_STELLA_oMODULEo;
extern Symbol* SYM_MACROS_STELLA_IN;
extern Symbol* SYM_MACROS_STELLA_oCURRENTSYSTEMDEFINITIONo;
extern Symbol* SYM_MACROS_STELLA_GET_SYSTEM_DEFINITION;
extern Symbol* SYM_MACROS_STELLA_oCURRENTSYSTEMDEFINITIONSUBDIRECTORYo;
extern Symbol* SYM_MACROS_STELLA_DIRECTORY;
extern Symbol* SYM_MACROS_STELLA_PROGN;
extern Keyword* KWD_MACROS_STARTUP_SYSTEMp;
extern Symbol* SYM_MACROS_STELLA_IF_STELLA_FEATURE;
extern Keyword* KWD_MACROS_SUPPORT_UNEXEC;
extern Symbol* SYM_MACROS_STELLA_VERBATIM;
extern Keyword* KWD_MACROS_CPP;
extern Keyword* KWD_MACROS_OTHERWISE;
extern Keyword* KWD_MACROS_PUBLICp;
extern Keyword* KWD_MACROS_COMMON_LISP;
extern Symbol* SYM_MACROS_STELLA_DEFUN;
extern Keyword* KWD_MACROS_CPP_STANDALONE;
extern Keyword* KWD_MACROS_IDL;
extern Symbol* SYM_MACROS_STELLA_INTEGER;
extern Symbol* SYM_MACROS_STELLA_RETURN;
extern Symbol* SYM_MACROS_STELLA_ARRAY;
extern Symbol* SYM_MACROS_STELLA_OF;
extern Symbol* SYM_MACROS_STELLA_STRING;
extern Symbol* SYM_MACROS_STELLA_aREST;
extern Symbol* SYM_MACROS_STELLA_rrARGS;
extern Symbol* SYM_MACROS_STELLA_LET;
extern Keyword* KWD_MACROS_INITIAL_CONTENTS;
extern Symbol* SYM_MACROS_STELLA_STARTUP_MACROS;
extern Symbol* SYM_MACROS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
