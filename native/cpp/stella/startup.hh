//  -*- Mode: C++ -*-

// startup.hh

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
extern const char* oSTELLA_VERSIONo;
extern int oSTELLA_MAJOR_VERSION_NUMBERo;
extern int oSTELLA_MINOR_VERSION_NUMBERo;
extern int oSTELLA_PATCH_LEVELo;
extern const char* oSTELLA_RELEASE_STATEo;
extern const char* oSTELLA_VERSION_STRINGo;
extern const char* oSTELLA_GC_VERSIONo;
extern List* oSTARTUP_TIME_PHASESo;
extern int oSTARTUP_TIME_PHASEo;

// Function signatures:
const char* stellaVersionString();
const char* stellaInformation();
StringWrapper* stellaInformationEvaluatorWrapper(Cons* arguments);
boolean currentStartupTimePhaseP(int phase);
int encodeStartupTimePhase(Keyword* phase);
void startupKernel(boolean verboseP);
void startupCppTranslator();
void startupJavaTranslator();
void startupIdlTranslator();
void startup(boolean verboseP);
void interpretCommandLineArguments(int count, const char** arguments);
Cons* consifyCommandLineArguments(int count, const char** arguments);
void startupStartup();

// Auxiliary global declarations:
extern Keyword* KWD_STARTUP_EARLY_INITS;
extern Keyword* KWD_STARTUP_MODULES;
extern Keyword* KWD_STARTUP_SYMBOLS;
extern Keyword* KWD_STARTUP_QUOTED_CONSTANTS;
extern Keyword* KWD_STARTUP_GLOBALS;
extern Keyword* KWD_STARTUP_CLASSES;
extern Keyword* KWD_STARTUP_FINALIZE_CLASSES;
extern Keyword* KWD_STARTUP_METHODS;
extern Keyword* KWD_STARTUP_FINALIZE_METHODS;
extern Keyword* KWD_STARTUP_FINAL;
extern Symbol* SYM_STARTUP_STELLA_C_CALLABLE_WRAPPER_CODE;
extern Keyword* KWD_STARTUP_WARN;
extern Keyword* KWD_STARTUP_DOCUMENTATION;
extern Symbol* SYM_STARTUP_STELLA_STARTUP_STARTUP;
extern Symbol* SYM_STARTUP_STELLA_METHOD_STARTUP_CLASSNAME;

// Function signatures:
int main(int count, const char** arguments);

} // end of namespace stella
