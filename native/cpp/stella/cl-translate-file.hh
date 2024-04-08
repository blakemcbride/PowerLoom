//  -*- Mode: C++ -*-

// cl-translate-file.hh

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
void lptrans(Object* statement);
void ptrans(Object* statement);
void helpLptrans(Object* statement);
boolean auxiliaryVariableUnitP(TranslationUnit* unit);
void clOutputOneUnit(TranslationUnit* unit, std::ostream* stream);
void clOutputAllUnitsToFile(const char* sourcefile);
void clOutputFileHeader(OutputStream* stream, const char* file, boolean ensurepackageP);
void clOutputEnsurePackageDefinition(OutputStream* stream, const char* package);
void clOutputInPackageDeclaration(OutputStream* stream, const char* package);
void clOutputForwardDeclarations(std::ostream* stream);
void clTranslateFile(const char* file, boolean relativeP);
void clTranslateWalkedSystemUnits(KeyValueList* systemunits);
List* sortClStructClasses(List* unsortedclasses);
const char* clYieldStructClassFileName(const char* systemname);
void clOutputSystemClStructsFile(List* classunits);
void clTranslateSystem(const char* systemName);
boolean clCompileAndLoadFiles(Cons* files, boolean relativeP, boolean forcerecompilationP);
void clTranslateStella(boolean productionsettingsP);
void clRetranslateStella(boolean productionsettingsP);
void startupClTranslateFile();

// Auxiliary global declarations:
extern Keyword* KWD_CL_TRANSLATE_FILE_COMMON_LISP;
extern Symbol* SYM_CL_TRANSLATE_FILE_STELLA_GLOBAL_VARIABLE;
extern Surrogate* SGT_CL_TRANSLATE_FILE_STELLA_CONS;
extern Keyword* KWD_CL_TRANSLATE_FILE_LISP;
extern Keyword* KWD_CL_TRANSLATE_FILE_IF_NOT_EXISTS;
extern Keyword* KWD_CL_TRANSLATE_FILE_CREATE_PATH;
extern Keyword* KWD_CL_TRANSLATE_FILE_USE_COMMON_LISP_STRUCTS;
extern Keyword* KWD_CL_TRANSLATE_FILE_USE_COMMON_LISP_VECTOR_STRUCTS;
extern Symbol* SYM_CL_TRANSLATE_FILE_STELLA_CLASS;
extern Keyword* KWD_CL_TRANSLATE_FILE_STELLA;
extern Keyword* KWD_CL_TRANSLATE_FILE_FINALIZE;
extern Keyword* KWD_CL_TRANSLATE_FILE_TWO_PASSp;
extern Keyword* KWD_CL_TRANSLATE_FILE_FORCE_TRANSLATIONp;
extern Keyword* KWD_CL_TRANSLATE_FILE_PRODUCTION_SETTINGSp;
extern Keyword* KWD_CL_TRANSLATE_FILE_LISP_BINARY;
extern Symbol* SYM_CL_TRANSLATE_FILE_STELLA_STARTUP_CL_TRANSLATE_FILE;
extern Symbol* SYM_CL_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
