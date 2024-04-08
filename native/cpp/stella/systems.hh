//  -*- Mode: C++ -*-

// systems.hh

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

// Class definitions:
class CmdLineOption : public StandardObject {
public:
  const char* documentation;
  Cons* keys;
  Surrogate* valueType;
  boolean multiValuedP;
  // The number of args expected by this option.
  // Common values are 0 or 1, but certain options might take more than one argument.
  int nArguments;
  // The value to use for 0-arg options.
  // Defaults to TRUE for 0-arg options with boolean value type.
  Object* defaultValue;
  const char* configurationProperty;
  cpp_function_code handler;
  // One of :ignore, :warn, :error.
  Keyword* errorAction;
public:
  virtual Surrogate* primaryType();
};


// Global declarations:
extern Cons* oFILE_LOAD_PATHo;
extern Cons* oSTELLA_FILE_EXTENSIONSo;
extern DECLARE_STELLA_SPECIAL(oCURRENTLOADFILEo, const char* );
extern List* oSYSTEMDEFINITIONSo;
extern DECLARE_STELLA_SPECIAL(oCURRENT_SYSTEM_ACTIONo, PropertyList* );
extern KeyValueList* oSYSTEM_CONFIGURATION_TABLEo;
extern const char* oPL_ROOT_DIRECTORYo;
extern KeyValueMap* oREGISTERED_PROPERTY_DEMONSo;
extern KeyValueMap* oREGISTERED_COMMAND_LINE_OPTIONSo;
extern Cons* oUNPROCESSED_COMMAND_LINE_ARGUMENTSo;
extern const char* oCOMMAND_LINE_HELP_HEADERo;
extern const char* oCOMMAND_LINE_HELP_TRAILERo;

// Function signatures:
Cons* parseDirectoryPath(const char* path);
Cons* setLoadPath(const char* path);
Cons* setLoadPathEvaluatorWrapper(Cons* arguments);
Cons* getLoadPath();
Cons* pushLoadPath(const char* path);
Cons* pushLoadPathEvaluatorWrapper(Cons* arguments);
const char* popLoadPath();
StringWrapper* popLoadPathEvaluatorWrapper(Cons* arguments);
Cons* addLoadPath(const char* path);
Cons* addLoadPathEvaluatorWrapper(Cons* arguments);
Cons* dropLoadPath(const char* path);
Cons* dropLoadPathEvaluatorWrapper(Cons* arguments);
const char* findFileInLoadPath(const char* file, Cons* extensions);
StringWrapper* findFileInLoadPathEvaluatorWrapper(Cons* arguments);
BooleanWrapper* coerceValueToBoolean(Object* value, boolean errorP);
BooleanWrapper* coerceToBoolean(Object* object);
const char* coerceValueToString(Object* value, boolean errorP);
const char* coerceToString(Object* object);
double coerceValueToFloat(Object* value, boolean errorP);
double coerceToFloat(Object* object);
Object* coerceValueToType(Object* value, Surrogate* type, boolean errorP);
Object* coerceOptionValue(Object* value, Surrogate* type);
PropertyList* vetOptions(Object* plist, Cons* legaloptions);
PropertyList* parseOptions(Object* options, Cons* legaloptionsAtypes, boolean coercionerrorP, boolean allowotherkeysP);
Object* evaluateCommand(Object* command, boolean finalizeP);
void loadFile(const char* file);
void loadFileEvaluatorWrapper(Cons* arguments);
const char* makeSystemDefinitionFileName(const char* name);
Cons* buildStellaSystemsPath();
const char* findSystemDefinitionFile(const char* name);
const char* findSystemRootDirectoryFromFile(const char* sysdeffile);
const char* findSystemRootDirectory(SystemDefinition* system);
void computeSystemRootDirectories(SystemDefinition* system);
Cons* parseListOfFilePaths(Cons* files);
SystemDefinition* defineSystem(Object* name, Cons* options);
SystemDefinition* defsystem(Symbol* name, Cons* options);
SystemDefinition* defsystemEvaluatorWrapper(Cons* arguments);
SystemDefinition* getSystemDefinition(const char* name, boolean errorP);
Module* getCardinalModule(SystemDefinition* system);
void helpGetSystemFiles(const char* filename, List* collection, boolean probefileP);
List* getSystemFiles(SystemDefinition* system, Keyword* type, boolean probefilesP);
void cleanSystem(const char* systemname);
void computeOptimizationLevels(SystemDefinition* system, boolean productionmodeP);
boolean makeSystem(const char* systemname, Cons* languageAoptions);
BooleanWrapper* makeSystemEvaluatorWrapper(Cons* arguments);
void runSystemFinalization(SystemDefinition* system);
Cons* systemDefinitionSourceFiles(SystemDefinition* system);
Cons* filesPlusSystemStartup(Cons* files);
Cons* systemDefinitionNativeFiles(SystemDefinition* system);
boolean systemLoadedP(const char* name);
boolean systemLoadedOrStartedUpP(const char* name);
void clearSystem(const char* name);
void loadPreprocessedFiles(const char* systemname);
boolean loadSystem(const char* systemname, Cons* languageAoptions);
BooleanWrapper* loadSystemEvaluatorWrapper(Cons* arguments);
boolean compileAndLoadFiles(Cons* files, Keyword* language, boolean forcerecompilationP);
void runSystemStartupFunction(SystemDefinition* system);
const char* stringSystemStartupFunctionName(const char* systemname);
Symbol* systemStartupFunctionSymbol(SystemDefinition* system);
Symbol* startupNameFromFile(const char* file);
Cons* startupNamesFromFiles(Cons* files);
const char* systemStartupFileName(SystemDefinition* system);
boolean systemStartupFileP(const char* file);
boolean systemStartedUpP(const char* systemname, const char* systemmodulename);
Cons* yieldStartupRequiredSystems(SystemDefinition* system);
Cons* collectStartupFormsFromSystemFile(SystemDefinition* system);
Cons* collectDefinedModulesFromSystemFile(SystemDefinition* system);
void createSystemStartupFile(SystemDefinition* system);
List* helpAllRequiredSystems(const char* systemName, List* found);
Cons* allRequiredSystems(const char* systemName);
const char* dateToVersionString(CalendarDate* date, Keyword* granularity);
CalendarDate* getSystemLastModifiedDate(SystemDefinition* system);
const char* getSystemVersionString(SystemDefinition* system);
cpp_function_code autoload(const char* qualifiedname, const char* systemname, Surrogate* cache, boolean errorP);
void makeStella(boolean forcerecompilationP);
StringWrapper* parseConfigurationFileLine(const char* line, Wrapper*& _Return1, Keyword*& _Return2);
KeyValueList* loadConfigurationFile(const char* file);
KeyValueList* loadConfigurationFileEvaluatorWrapper(Cons* arguments);
void saveConfigurationValue(OutputStream* stream, Object* value);
void saveConfigurationFile(KeyValueList* table, const char* file, const char* title);
Object* lookupConfigurationProperty(const char* property, Object* defaultvalue, KeyValueList* configuration);
Cons* lookupConfigurationPropertyValues(const char* property, Object* defaultvalue, KeyValueList* configuration);
Object* setConfigurationProperty(const char* property, Object* value, KeyValueList* configuration);
Object* addConfigurationProperty(const char* property, Object* value, KeyValueList* configuration);
Object* clearConfigurationProperty(const char* property, KeyValueList* configuration);
Object* removeConfigurationProperty(const char* property, Object* value, KeyValueList* configuration);
void printConfigurationProperties(KeyValueList* configuration, OutputStream* stream);
const char* OPlRootDirectoryOSetter(const char* value);
void configureStella(const char* file);
void configureStellaEvaluatorWrapper(Cons* arguments);
Object* getProperty(Object* property, Cons* defaultvalue);
Object* getPropertyEvaluatorWrapper(Cons* arguments);
void setProperty(Object* property, Object* value);
void addPropertyValue(Object* property, Object* value);
void printProperties();
void registerPropertyDemon(const char* property, Symbol* demonname);
void unregisterPropertyDemon(const char* property);
MethodSlot* lookupVariableDemonSetter(GlobalVariable* demon);
void runConfigurationPropertyDemon(Keyword* action, const char* property, Object* value, KeyValueList* table);
void demonPropertyHandler(MappableObject* demon, StorageSlot* slot, Object* property);
void testPropertyDemon(Keyword* action, const char* property, Object* value, KeyValueList* table);
CmdLineOption* newCmdLineOption();
Object* accessCmdLineOptionSlotValue(CmdLineOption* self, Symbol* slotname, Object* value, boolean setvalueP);
void registerCmdLineOption(int options, ...);
void unregisterCmdLineOption(const char* key);
void unregisterAllCmdLineOptions();
void defaultCmdLineOptionHandler(CmdLineOption* option, Object* value);
void processCommandLineArguments(int count, const char** arguments, Keyword* unhandledoptionaction);
Cons* unprocessedCommandLineArguments();
void evalOptionHandler(CmdLineOption* option, Object* value);
void evalInModuleOptionHandler(CmdLineOption* option, Object* value);
void loadPathOptionHandler(CmdLineOption* option, Object* value);
void configFileOptionHandler(CmdLineOption* option, Object* value);
void loadFileOptionHandler(CmdLineOption* option, Object* value);
void definePropertyOptionHandler(CmdLineOption* option, Object* value);
void helpOptionHandler(CmdLineOption* option, Object* value);
void helpStartupSystems1();
void helpStartupSystems2();
void helpStartupSystems3();
void helpStartupSystems4();
void helpStartupSystems5();
void helpStartupSystems6();
void startupSystems();

// Auxiliary global declarations:
extern Symbol* SYM_SYSTEMS_STELLA_TRUE;
extern Keyword* KWD_SYSTEMS_TRUE;
extern Symbol* SYM_SYSTEMS_STELLA_FALSE;
extern Keyword* KWD_SYSTEMS_FALSE;
extern Surrogate* SGT_SYSTEMS_STELLA_UNKNOWN;
extern Surrogate* SGT_SYSTEMS_STELLA_GENERALIZED_SYMBOL;
extern Surrogate* SGT_SYSTEMS_STELLA_INTEGER;
extern Surrogate* SGT_SYSTEMS_STELLA_FLOAT;
extern Surrogate* SGT_SYSTEMS_STELLA_NUMBER;
extern Surrogate* SGT_SYSTEMS_STELLA_STRING;
extern Surrogate* SGT_SYSTEMS_STELLA_KEYWORD;
extern Surrogate* SGT_SYSTEMS_STELLA_SYMBOL;
extern Surrogate* SGT_SYSTEMS_STELLA_BOOLEAN;
extern Surrogate* SGT_SYSTEMS_STELLA_MODULE;
extern Surrogate* SGT_SYSTEMS_STELLA_PROPERTY_LIST;
extern Surrogate* SGT_SYSTEMS_STELLA_CONS;
extern Surrogate* SGT_SYSTEMS_STELLA_LIST;
extern Keyword* KWD_SYSTEMS_OPTIONS;
extern Surrogate* SGT_SYSTEMS_STELLA_IDENTITY;
extern Keyword* KWD_SYSTEMS_DEFINE;
extern Symbol* SYM_SYSTEMS_STELLA_IN_MODULE;
extern Keyword* KWD_SYSTEMS_FINALIZE;
extern Symbol* SYM_SYSTEMS_STELLA_DEFMODULE;
extern Symbol* SYM_SYSTEMS_STELLA_DEFSYSTEM;
extern Symbol* SYM_SYSTEMS_STELLA_DEFCLASS;
extern Symbol* SYM_SYSTEMS_STELLA_DEFSLOT;
extern Symbol* SYM_SYSTEMS_STELLA_DEFUN;
extern Symbol* SYM_SYSTEMS_STELLA_DEFMETHOD;
extern Keyword* KWD_SYSTEMS_DOCUMENTATION;
extern Keyword* KWD_SYSTEMS_PUBLICp;
extern Keyword* KWD_SYSTEMS_DIRECTORY;
extern Keyword* KWD_SYSTEMS_FILES;
extern Keyword* KWD_SYSTEMS_REQUIRED_SYSTEMS;
extern Keyword* KWD_SYSTEMS_ACTION;
extern Keyword* KWD_SYSTEMS_LOAD_SYSTEM;
extern Keyword* KWD_SYSTEMS_LANGUAGE;
extern Keyword* KWD_SYSTEMS_MAKE_SYSTEM;
extern Keyword* KWD_SYSTEMS_LISP_ONLY_FILES;
extern Keyword* KWD_SYSTEMS_CPP_ONLY_FILES;
extern Keyword* KWD_SYSTEMS_JAVA_ONLY_FILES;
extern Keyword* KWD_SYSTEMS_DATA_FILES;
extern Keyword* KWD_SYSTEMS_PREPROCESSED_FILES;
extern Keyword* KWD_SYSTEMS_CARDINAL_MODULE;
extern Keyword* KWD_SYSTEMS_ROOT_SOURCE_DIRECTORY;
extern Keyword* KWD_SYSTEMS_ROOT_NATIVE_DIRECTORY;
extern Keyword* KWD_SYSTEMS_ROOT_BINARY_DIRECTORY;
extern Keyword* KWD_SYSTEMS_BANNER;
extern Keyword* KWD_SYSTEMS_COPYRIGHT_HEADER;
extern Keyword* KWD_SYSTEMS_PRODUCTION_SETTINGS;
extern Keyword* KWD_SYSTEMS_DEVELOPMENT_SETTINGS;
extern Keyword* KWD_SYSTEMS_FINALIZATION_FUNCTION;
extern Keyword* KWD_SYSTEMS_JAVA;
extern Keyword* KWD_SYSTEMS_LISP;
extern Keyword* KWD_SYSTEMS_CPP;
extern Keyword* KWD_SYSTEMS_LISP_BINARY;
extern Keyword* KWD_SYSTEMS_TWO_PASSp;
extern Keyword* KWD_SYSTEMS_DEVELOPMENT_SETTINGSp;
extern Keyword* KWD_SYSTEMS_PRODUCTION_SETTINGSp;
extern Keyword* KWD_SYSTEMS_FORCE_TRANSLATIONp;
extern Keyword* KWD_SYSTEMS_FORCE_RECOMPILATIONp;
extern Keyword* KWD_SYSTEMS_LOAD_SYSTEMp;
extern Keyword* KWD_SYSTEMS_STARTUPp;
extern Keyword* KWD_SYSTEMS_RECURSIVEp;
extern Surrogate* SGT_SYSTEMS_STELLA_FILE_NAME;
extern Keyword* KWD_SYSTEMS_PROCESSED;
extern Keyword* KWD_SYSTEMS_COMMON_LISP;
extern Keyword* KWD_SYSTEMS_USE_COMMON_LISP_STRUCTS;
extern Keyword* KWD_SYSTEMS_STELLA;
extern Keyword* KWD_SYSTEMS_WARN_ABOUT_UNDEFINED_METHODS;
extern Symbol* SYM_SYSTEMS_STELLA_UNLESS;
extern Symbol* SYM_SYSTEMS_STELLA_SYSTEM_STARTED_UPp;
extern Symbol* SYM_SYSTEMS_STELLA_STARTUP_TIME_PROGN;
extern Keyword* KWD_SYSTEMS_EARLY_INITS;
extern Keyword* KWD_SYSTEMS_MODULES;
extern Symbol* SYM_SYSTEMS_STELLA_DEFINE_MODULE_FROM_STRINGIFIED_SOURCE;
extern Symbol* SYM_SYSTEMS_STELLA_STARTUP;
extern Symbol* SYM_SYSTEMS_STELLA_FOREACH;
extern Symbol* SYM_SYSTEMS_STELLA_PHASE;
extern Symbol* SYM_SYSTEMS_STELLA_IN;
extern Symbol* SYM_SYSTEMS_STELLA_INTERVAL;
extern Symbol* SYM_SYSTEMS_STELLA_PHASE_TO_INTEGER;
extern Keyword* KWD_SYSTEMS_FINAL;
extern Symbol* SYM_SYSTEMS_STELLA_DO;
extern Symbol* SYM_SYSTEMS_STELLA_SETQ;
extern Symbol* SYM_SYSTEMS_STELLA_oSTARTUP_TIME_PHASEo;
extern Keyword* KWD_SYSTEMS_DAYS;
extern Keyword* KWD_SYSTEMS_HOURS;
extern Keyword* KWD_SYSTEMS_MINUTES;
extern Keyword* KWD_SYSTEMS_SECONDS;
extern Symbol* SYM_SYSTEMS_STELLA_SYSTEM_VERSION;
extern Keyword* KWD_SYSTEMS_SET;
extern Keyword* KWD_SYSTEMS_WHITE_SPACE;
extern Keyword* KWD_SYSTEMS_ADD;
extern Symbol* SYM_SYSTEMS_STELLA_CONFIGURATION_TABLE;
extern Keyword* KWD_SYSTEMS_CLEAR;
extern Keyword* KWD_SYSTEMS_REMOVE;
extern Keyword* KWD_SYSTEMS_ROOT_DIRECTORY;
extern Surrogate* SGT_SYSTEMS_STELLA_GLOBAL_VARIABLE;
extern Surrogate* SGT_SYSTEMS_STELLA_LONG_INTEGER;
extern Symbol* SYM_SYSTEMS_STELLA_TEST_PROPERTY_DEMON;
extern Keyword* KWD_SYSTEMS_ERROR;
extern Surrogate* SGT_SYSTEMS_STELLA_CMD_LINE_OPTION;
extern Symbol* SYM_SYSTEMS_STELLA_DOCUMENTATION;
extern Symbol* SYM_SYSTEMS_STELLA_KEYS;
extern Symbol* SYM_SYSTEMS_STELLA_VALUE_TYPE;
extern Symbol* SYM_SYSTEMS_STELLA_MULTI_VALUEDp;
extern Symbol* SYM_SYSTEMS_STELLA_N_ARGUMENTS;
extern Symbol* SYM_SYSTEMS_STELLA_DEFAULT_VALUE;
extern Symbol* SYM_SYSTEMS_STELLA_CONFIGURATION_PROPERTY;
extern Symbol* SYM_SYSTEMS_STELLA_HANDLER;
extern Symbol* SYM_SYSTEMS_STELLA_ERROR_ACTION;
extern Keyword* KWD_SYSTEMS_KEY;
extern Keyword* KWD_SYSTEMS_KEY2;
extern Keyword* KWD_SYSTEMS_KEY3;
extern Keyword* KWD_SYSTEMS_KEYS;
extern Keyword* KWD_SYSTEMS_VALUE_TYPE;
extern Surrogate* SGT_SYSTEMS_STELLA_TYPE;
extern Keyword* KWD_SYSTEMS_MULTI_VALUEDp;
extern Keyword* KWD_SYSTEMS_N_ARGUMENTS;
extern Keyword* KWD_SYSTEMS_DEFAULT_VALUE;
extern Surrogate* SGT_SYSTEMS_STELLA_OBJECT;
extern Keyword* KWD_SYSTEMS_PROPERTY;
extern Keyword* KWD_SYSTEMS_HANDLER;
extern Keyword* KWD_SYSTEMS_ERROR_ACTION;
extern Keyword* KWD_SYSTEMS_WARN;
extern Keyword* KWD_SYSTEMS_IGNORE;
extern Symbol* SYM_SYSTEMS_STELLA_EVAL_OPTION_HANDLER;
extern Symbol* SYM_SYSTEMS_STELLA_EVAL_IN_MODULE_OPTION_HANDLER;
extern Symbol* SYM_SYSTEMS_STELLA_LOAD_PATH_OPTION_HANDLER;
extern Symbol* SYM_SYSTEMS_STELLA_CONFIG_FILE_OPTION_HANDLER;
extern Symbol* SYM_SYSTEMS_STELLA_LOAD_FILE_OPTION_HANDLER;
extern Symbol* SYM_SYSTEMS_STELLA_DEFINE_PROPERTY_OPTION_HANDLER;
extern Symbol* SYM_SYSTEMS_STELLA_HELP_OPTION_HANDLER;
extern Symbol* SYM_SYSTEMS_STELLA_STARTUP_SYSTEMS;
extern Symbol* SYM_SYSTEMS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
