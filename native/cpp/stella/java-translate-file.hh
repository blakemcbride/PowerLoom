//  -*- Mode: C++ -*-

// java-translate-file.hh

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
extern DECLARE_STELLA_SPECIAL(oCURRENT_JAVA_OUTPUT_CLASSo, Class* );
extern Keyword* oJAVA_BUILD_METHODo;

// Function signatures:
void clt();
void jt();
void jptrans(Object* statement);
const char* stringJavaMakeCodeOutputFileName(const char* barefile, boolean donttruncateP);
const char* javaMakeGlobalOutputFileName(Module* module, boolean donttruncateP);
void javaOutputFlotsamUnitsToFile(HashTable* globalsht, HashTable* functionht, Cons* codemodulelist);
void javaOutputFlotsamUnitsToFileForModule(const char* classoutputfile, Module* module, TranslationUnit* classunit, Cons* globals, Cons* functions);
void javaOutputFileHeader(OutputStream* stream, const char* filename);
void javaOutputClassToFile(Class* clasS);
void javaOutputClassUnitToFile(TranslationUnit* classunit);
boolean javaFlotsamFunctionP(MethodSlot* method);
void javaOutputStartupUnitsToFile(StringHashTable* startupht, Cons* keylist);
void javaPushIntoHashTable(HashTable* ht, Object* key, Object* object);
void javaPushIntoStringHashTable(StringHashTable* ht, const char* key, Object* object);
boolean javaClassUnitDefinesFlotsamClassP(TranslationUnit* classunit);
void javaOutputAllUnitsToFile();
void javaInitializeFileTranslation();
void javaTranslateFile(const char* filename);
void javaTranslateFileAsPartOfSystem(const char* filename);
void javaTranslateWalkedSystemUnits(KeyValueList* systemunits);
void javaOutputSystemSpecificFiles();
void javaTranslateSystem(const char* systemname);
const char* javaGetSystemMavenTemplateFile();
const char* javaGetSystemParentMavenTemplateFile();
const char* javaYieldSystemGroupName(SystemDefinition* system);
const char* javaYieldSystemVersion(SystemDefinition* system);
const char* javaYieldSystemParentName(SystemDefinition* system);
void substituteTemplateVariablesToMavenFile(const char* templatefile, const char* outputfile, KeyValueList* variables);
void javaOutputSystemMavenFiles();
void helpStartupJavaTranslateFile1();
void startupJavaTranslateFile();

// Auxiliary global declarations:
extern Keyword* KWD_JAVA_TRANSLATE_FILE_COMMON_LISP;
extern Keyword* KWD_JAVA_TRANSLATE_FILE_JAVA;
extern Keyword* KWD_JAVA_TRANSLATE_FILE_IF_NOT_EXISTS;
extern Keyword* KWD_JAVA_TRANSLATE_FILE_CREATE_PATH;
extern Keyword* KWD_JAVA_TRANSLATE_FILE_MINIMIZE_JAVA_PREFIXES;
extern Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD_CONSTRUCTORp;
extern Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD_NATIVEp;
extern Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD;
extern Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_MACRO;
extern Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_PRINT_METHOD;
extern Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_TYPE;
extern Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_VERBATIM;
extern Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_CLASS;
extern Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_GLOBAL_VARIABLE;
extern Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME;
extern Keyword* KWD_JAVA_TRANSLATE_FILE_MAVEN;
extern Keyword* KWD_JAVA_TRANSLATE_FILE_TWO_PASSp;
extern Keyword* KWD_JAVA_TRANSLATE_FILE_FORCE_TRANSLATIONp;
extern Keyword* KWD_JAVA_TRANSLATE_FILE_PRODUCTION_SETTINGSp;
extern Keyword* KWD_JAVA_TRANSLATE_FILE_STELLA;
extern Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_SYSTEM_GROUP_NAME;
extern Keyword* KWD_JAVA_TRANSLATE_FILE_MINUTES;
extern Symbol* SYM_JAVA_TRANSLATE_FILE_STELLA_STARTUP_JAVA_TRANSLATE_FILE;


} // end of namespace stella
