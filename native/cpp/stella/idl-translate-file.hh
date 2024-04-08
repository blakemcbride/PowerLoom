//  -*- Mode: C++ -*-

// idl-translate-file.hh

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
extern const char* oIDL_TRANSLATED_FILE_SUFFIXo;

// Function signatures:
void idlTranslateClassToStream(Class* clasS, std::ostream* nativeStream);
const char* idlMakeCodeOutputFileName(const char* sourcefile);
void idlOutputAllUnitsToFile(const char* sourcefile);
void idlTranslateFile(const char* filename);
void startupIdlTranslateFile();

// Auxiliary global declarations:
extern Symbol* SYM_IDL_TRANSLATE_FILE_STELLA_METHOD;
extern Symbol* SYM_IDL_TRANSLATE_FILE_STELLA_PRINT_METHOD;
extern Symbol* SYM_IDL_TRANSLATE_FILE_STELLA_MACRO;
extern Symbol* SYM_IDL_TRANSLATE_FILE_STELLA_VERBATIM;
extern Symbol* SYM_IDL_TRANSLATE_FILE_STELLA_GLOBAL_VARIABLE;
extern Keyword* KWD_IDL_TRANSLATE_FILE_IDL;
extern Symbol* SYM_IDL_TRANSLATE_FILE_STELLA_STARTUP_IDL_TRANSLATE_FILE;
extern Symbol* SYM_IDL_TRANSLATE_FILE_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
