//  -*- Mode: C -*-

// pli.h

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
 | The Original Code is the PowerLoom KR&R System.                            |
 |                                                                            |
 | The Initial Developer of the Original Code is                              |
 | UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
 | 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
 |                                                                            |
 | Portions created by the Initial Developer are Copyright (C) 1997-2019      |
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
 +----------------------------- END LICENSE BLOCK ----------------------------+
*/

// Include file for the C-version of the PLI API.
// This was constructed via `grep 'extern "C"' pli.cc > pli.h' with some manual post-editing.


// To compile your own C program myprog.c that uses PowerLoom programmatically, do the following:
// (1) #include pli.h                       // in myprog.c
// (2) compile the C++ version of PowerLoom
// (3) setenv PL_HOME .../powerloom-x.y.z   # where your C++-compiled PowerLoom and libraries reside
// (4) gcc -fPIC -I$PL_HOME/native/cpp/logic -o myprog myprog.c -L$PL_HOME/native/cpp/lib -lpowerloom -lpowerloom-extensions -lutilities -llogic -lstella -lgc -lm -lstdc++
// To create a shared library instead of an executable, do this:
// (5) gcc -shared -fPIC -I$PL_HOME/native/cpp/logic -o myprog.so myprog.c -L$PL_HOME/native/cpp/lib -lpowerloom -lpowerloom-extensions -lutilities -llogic -lstella -lgc -lm -lstdc++
// To run or use the library, make sure to set the load library path:
// (6) setenv LD_LIBRARY_PATH $PL_HOME/native/cpp/lib


// Non-C types referenced below which were then manually prefixed
// with pli_ and typedef'ed to C primitives or void* pointers:
//
// Cons*
// StringWrapper*
// IntegerWrapper*
// LongIntegerWrapper*
// FloatWrapper*
// BooleanWrapper*
// Environment*
// InputStream*
// Keyword*
// List*
// LogicObject*
// Module*
// Object*
// OutputStream*
// Iterator*
// PlIterator*
// Proposition*
// Symbol*
// TruthValue*
// boolean
// cpp_function_code
// std::istream*

typedef void  pli_Cons;
typedef void  pli_StringWrapper;
typedef void  pli_IntegerWrapper;
typedef void  pli_LongIntegerWrapper;
typedef void  pli_FloatWrapper;
typedef void  pli_BooleanWrapper;
typedef void  pli_Environment;
typedef void  pli_InputStream;
typedef void  pli_Keyword;
typedef void  pli_List;
typedef void  pli_LogicObject;
typedef void  pli_Skolem;
typedef void  pli_PatternVariable;
typedef void  pli_Module;
typedef void  pli_Object;
typedef void  pli_OutputStream;
typedef void  pli_PlIterator;
typedef void  pli_Iterator;
typedef void  pli_Proposition;
typedef void  pli_Symbol;
typedef void  pli_TruthValue;
typedef void  pli_ControlFrame;
typedef void* pli_cpp_function_code;
// this one still needs a C-callable constructor:
typedef void  pli_istream;
typedef int   pli_boolean;

void pli_initialize();
void pli_resetPowerloom();
void pli_clearCaches();
pli_boolean pli_plIteratorNextP(pli_PlIterator* self);
pli_Object* pli_plIteratorValue(pli_PlIterator* self);
pli_boolean pli_plIteratorEmptyP(pli_PlIterator* self);
pli_boolean pli_plIteratorIsEmpty(pli_PlIterator* self);
int pli_plIteratorLength(pli_PlIterator* self);
pli_PlIterator* pli_consToPlIterator(pli_Cons* self);
pli_PlIterator* pli_listToPlIterator(pli_List* self);
pli_PlIterator* pli_iteratorToPlIterator(pli_Iterator* self);
pli_List* pli_plIteratorListify(pli_PlIterator* self);
pli_Cons* pli_plIteratorConsify(pli_PlIterator* self);
pli_Cons* pli_createCons(pli_Object* first, pli_Cons* rest);
pli_Cons* pli_createConsList(int length);
int pli_consLength(pli_Cons* self);
pli_boolean pli_consIsEmpty(pli_Cons* self);
pli_Object* pli_consFirst(pli_Cons* self);
pli_Cons* pli_consRest(pli_Cons* self);
pli_Object* pli_consNth(pli_Cons* self, int n);
pli_Cons* pli_consNthRest(pli_Cons* self, int n);
void pli_consSetFirst(pli_Cons* self, pli_Object* value);
void pli_consSetRest(pli_Cons* self, pli_Cons* rest);
void pli_consSetNth(pli_Cons* self, int n, pli_Object* value);
void pli_consSetNthRest(pli_Cons* self, int n, pli_Cons* rest);
pli_Object* pli_listFirst(pli_List* self);
pli_Cons* pli_listRest(pli_List* self);
pli_Object* pli_listNth(pli_List* self, int n);
char* pli_createString(char* content);
pli_StringWrapper* pli_createStringWrapper(char* self);
pli_StringWrapper* pli_createDirectStringWrapper(char* self);
pli_IntegerWrapper* pli_createIntegerWrapper(int self);
pli_LongIntegerWrapper* pli_createLongIntegerWrapper(long long int self);
pli_FloatWrapper* pli_createFloatWrapper(double self);
pli_BooleanWrapper* pli_createBooleanWrapper(pli_boolean self);
pli_Keyword* pli_getKeyword(char* name);
pli_Symbol* pli_getSymbol(char* name, pli_Module* module, pli_Environment* environment);
pli_Symbol* pli_getOperator(char* name);
pli_Object* pli_getObject(char* name, pli_Module* module, pli_Environment* environment);
pli_Object* pli_sGetObject(char* name, char* moduleName, pli_Environment* environment);
pli_LogicObject* pli_getConcept(char* name, pli_Module* module, pli_Environment* environment);
pli_LogicObject* pli_sGetConcept(char* name, char* moduleName, pli_Environment* environment);
pli_LogicObject* pli_getRelation(char* name, pli_Module* module, pli_Environment* environment);
pli_LogicObject* pli_sGetRelation(char* name, char* moduleName, pli_Environment* environment);
pli_PlIterator* pli_getUndefinedRelations(pli_Module* module, pli_Environment* environment);
char* pli_getNameInModule(pli_Object* obj, pli_Module* module, pli_Environment* environment);
char* pli_getName(pli_Object* obj);
char* pli_getShortName(pli_Object* obj);
char* pli_getSkolemName(pli_Skolem* skolem);
char* pli_getSkolemShortName(pli_Skolem* skolem);
char* pli_getVariableName(pli_PatternVariable* variable);
char* pli_getVariableShortName(pli_PatternVariable* variable);
char* pli_objectToString(pli_Object* self);
int pli_objectToInteger(pli_Object* self);
double pli_objectToFloat(pli_Object* self);
char* pli_objectToParsableString(pli_Object* self);
pli_Symbol* pli_getStellaType(pli_Object* self);
pli_Symbol* pli_getLogicType(pli_Object* self);
char* pli_getStellaTypeName(pli_Object* self);
char* pli_getStellaTypeShortName(pli_Object* self);
char* pli_getLogicTypeName(pli_Object* self);
char* pli_getLogicTypeShortName(pli_Object* self);
pli_Object* pli_stringToObject(char* string, pli_LogicObject* type, pli_Module* module, pli_Environment* environment);
pli_Object* pli_stringToStellaExpression(char* expression, pli_Module* module, pli_Environment* environment);
pli_Proposition* pli_getProposition(pli_Object* relationAndArguments, pli_Module* module, pli_Environment* environment);
pli_Proposition* pli_sGetProposition(char* relationAndArguments, char* moduleName, pli_Environment* environment);
pli_PlIterator* pli_getPropositions(pli_Object* relationAndArguments, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_sGetPropositions(char* relationAndArguments, char* moduleName, pli_Environment* environment);
pli_PlIterator* pli_getInconsistentPropositions(pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_getUnaryPropositions(pli_LogicObject* relation, pli_Object* arg, pli_Module* module, pli_Environment* environment);
pli_Proposition* pli_getBinaryProposition(pli_LogicObject* relation, pli_Object* arg1, pli_Object* arg2, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_getBinaryPropositions(pli_LogicObject* relation, pli_Object* arg1, pli_Object* arg2, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_getInferredBinaryPropositionValues(pli_LogicObject* relation, pli_Object* arg, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_sGetInferredBinaryPropositionValues(char* relationName, char* argName, char* moduleName, pli_Environment* environment);
pli_PlIterator* pli_getPropositionsOf(pli_LogicObject* object, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_sGetPropositionsOf(char* objectName, char* moduleName, pli_Environment* environment);
pli_PlIterator* pli_getPropositionsInModule(pli_Module* module, pli_Environment* environment);
pli_boolean pli_isTrueUnaryProposition(pli_LogicObject* relation, pli_Object* arg, pli_Module* module, pli_Environment* environment);
pli_boolean pli_isTrueBinaryProposition(pli_LogicObject* relation, pli_Object* arg, pli_Object* value, pli_Module* module, pli_Environment* environment);
pli_boolean pli_isTrueNaryProposition(pli_Object* relationAndArguments, pli_Module* module, pli_Environment* environment);
pli_boolean pli_sIsTrueNaryProposition(char* relationAndArguments, char* moduleName, pli_Environment* environment);
pli_boolean pli_isTrueProposition(pli_Proposition* proposition, pli_Module* module, pli_Environment* environment);
pli_boolean pli_isSubrelation(pli_LogicObject* sub, pli_LogicObject* super, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_getProperSubrelations(pli_LogicObject* relation, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_getDirectSubrelations(pli_LogicObject* relation, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_getProperSuperrelations(pli_LogicObject* relation, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_getDirectSuperrelations(pli_LogicObject* relation, pli_Module* module, pli_Environment* environment);
pli_boolean pli_isInstance(pli_Object* object, pli_LogicObject* concept, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_getConceptInstances(pli_LogicObject* concept, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_sGetConceptInstances(char* conceptName, char* moduleName, pli_Environment* environment);
pli_PlIterator* pli_getDirectConceptInstances(pli_LogicObject* concept, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_sGetDirectConceptInstances(char* conceptName, char* moduleName, pli_Environment* environment);
pli_PlIterator* pli_getConceptInstancesMatchingValue(pli_LogicObject* concept, pli_LogicObject* relation, pli_Object* value, pli_Module* module, pli_Environment* environment);
pli_Object* pli_getConceptInstanceMatchingValue(pli_LogicObject* concept, pli_LogicObject* relation, pli_Object* value, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_getTypes(pli_LogicObject* object, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_getDirectTypes(pli_LogicObject* object, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_getRelationExtension(pli_LogicObject* relation, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_sGetRelationExtension(char* relationName, char* moduleName, pli_Environment* environment);
pli_Module* pli_getModule(char* name, pli_Environment* environment);
pli_Module* pli_getExistingModule(char* name, pli_Environment* environment);
pli_Module* pli_getCurrentModule(pli_Environment* environment);
pli_Module* pli_getHomeModule(pli_LogicObject* object);
pli_PlIterator* pli_getModules(pli_boolean kbModulesOnlyP);
pli_Module* pli_createModule(char* name, pli_Module* parent, pli_boolean caseSensitiveP);
pli_Module* pli_sCreateModule(char* name, char* parentName, pli_boolean caseSensitiveP, pli_Environment* environment);
pli_Module* pli_changeModule(pli_Module* module);
pli_Module* pli_sChangeModule(char* name, pli_Environment* environment);
pli_Module* pli_clearModule(pli_Module* module);
pli_Module* pli_sClearModule(char* name, pli_Environment* environment);
pli_PlIterator* pli_getChildModules(pli_Module* module);
pli_PlIterator* pli_sGetChildModules(char* name, pli_Environment* environment);
pli_PlIterator* pli_getParentModules(pli_Module* module);
pli_PlIterator* pli_sGetParentModules(char* name, pli_Environment* environment);
char* pli_generateUniqueName(char* prefix, pli_Module* module, pli_Environment* environment);
pli_Keyword* pli_createKeyword(char* name);
pli_Symbol* pli_createSymbol(char* name, pli_Module* module, pli_Environment* environment);
pli_LogicObject* pli_createObject(char* name, pli_LogicObject* concept, pli_Module* module, pli_Environment* environment);
pli_LogicObject* pli_sCreateObject(char* name, char* conceptName, char* moduleName, pli_Environment* environment);
pli_LogicObject* pli_createConcept(char* name, pli_LogicObject* parent, pli_Module* module, pli_Environment* environment);
pli_LogicObject* pli_sCreateConcept(char* name, char* parentName, char* moduleName, pli_Environment* environment);
pli_LogicObject* pli_createRelation(char* name, int arity, pli_Module* module, pli_Environment* environment);
pli_LogicObject* pli_sCreateRelation(char* name, int arity, char* moduleName, pli_Environment* environment);
pli_LogicObject* pli_createFunction(char* name, int arity, pli_Module* module, pli_Environment* environment);
pli_LogicObject* pli_sCreateFunction(char* name, int arity, char* moduleName, pli_Environment* environment);
void pli_registerSpecialistFunction(char* name, pli_cpp_function_code functionReference, pli_Module* module, pli_Environment* environment);
void pli_sRegisterSpecialistFunction(char* name, char* nativeName, char* moduleName, pli_Environment* environment);
void pli_registerComputationFunction(char* name, pli_cpp_function_code functionReference, int arity, pli_Module* module, pli_Environment* environment);
void pli_sRegisterComputationFunction(char* name, char* nativeName, int arity, char* moduleName, pli_Environment* environment);
pli_LogicObject* pli_createEnumeratedList(pli_Cons* members, pli_Module* module, pli_Environment* environment);
pli_LogicObject* pli_createEnumeratedSet(pli_Cons* members, pli_Module* module, pli_Environment* environment);
void pli_destroyObject(pli_Object* object);
void pli_sDestroyObject(char* objectName, char* moduleName, pli_Environment* environment);
pli_Proposition* pli_assertUnaryProposition(pli_LogicObject* relation, pli_Object* arg, pli_Module* module, pli_Environment* environment);
pli_Proposition* pli_assertBinaryProposition(pli_LogicObject* relation, pli_Object* arg, pli_Object* value, pli_Module* module, pli_Environment* environment);
pli_Proposition* pli_assertNaryProposition(pli_Object* relationAndArguments, pli_Module* module, pli_Environment* environment);
pli_Proposition* pli_retractUnaryProposition(pli_LogicObject* relation, pli_Object* arg, pli_Module* module, pli_Environment* environment);
pli_Proposition* pli_retractBinaryProposition(pli_LogicObject* relation, pli_Object* arg, pli_Object* value, pli_Module* module, pli_Environment* environment);
pli_Proposition* pli_retractNaryProposition(pli_Object* relationAndArguments, pli_Module* module, pli_Environment* environment);
pli_Proposition* pli_assertProposition(pli_Proposition* proposition, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_sAssertProposition(char* sentence, char* moduleName, pli_Environment* environment);
pli_Proposition* pli_retractProposition(pli_Proposition* proposition, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_sRetractProposition(char* sentence, char* moduleName, pli_Environment* environment);
pli_PlIterator* pli_conceive(pli_Object* sentence, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_sConceive(char* sentence, char* moduleName, pli_Environment* environment);
pli_PlIterator* pli_getRules(pli_LogicObject* relation, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_sGetRules(char* relationName, char* moduleName, pli_Environment* environment);
void pli_sPrintRules(char* name, pli_OutputStream* stream, char* moduleName, pli_Environment* environment);
void pli_runForwardRules(pli_Object* module, pli_boolean localP, pli_boolean forceP);
int pli_getArity(pli_LogicObject* relation);
int pli_sGetArity(char* relationName, char* moduleName, pli_Environment* environment);
pli_LogicObject* pli_getDomain(pli_LogicObject* relation);
pli_LogicObject* pli_sGetDomain(char* relationName, char* moduleName, pli_Environment* environment);
pli_LogicObject* pli_getRange(pli_LogicObject* relation);
pli_LogicObject* pli_sGetRange(char* relationName, char* moduleName, pli_Environment* environment);
pli_LogicObject* pli_getNthDomain(pli_LogicObject* relation, int n);
pli_LogicObject* pli_sGetNthDomain(char* relationName, int n, char* moduleName, pli_Environment* environment);
void pli_load(char* filename, pli_Environment* environment);
void pli_loadInModule(char* filename, pli_Module* module, pli_Environment* environment);
void pli_loadStream(pli_InputStream* stream, pli_Environment* environment);
void pli_loadStreamInModule(pli_InputStream* stream, pli_Module* module, pli_Environment* environment);
void pli_loadNativeStream(pli_istream* stream, pli_Environment* environment);
void pli_loadNativeStreamInModule(pli_istream* stream, pli_Module* module, pli_Environment* environment);
void pli_saveModule(pli_Module* module, char* filename, char* ifexists, pli_Environment* environment);
void pli_sSaveModule(char* moduleName, char* filename, char* ifexists, pli_Environment* environment);
pli_LogicObject* pli_getPredicate(pli_Proposition* prop);
int pli_getColumnCount(pli_Object* obj);
pli_Object* pli_getNthValue(pli_Object* sequence, int n, pli_Module* module, pli_Environment* environment);
char* pli_getNthString(pli_Object* sequence, int n, pli_Module* module, pli_Environment* environment);
int pli_getNthInteger(pli_Object* sequence, int n, pli_Module* module, pli_Environment* environment);
double pli_getNthFloat(pli_Object* sequence, int n, pli_Module* module, pli_Environment* environment);
pli_LogicObject* pli_getNthLogicObject(pli_Object* sequence, int n, pli_Module* module, pli_Environment* environment);
pli_Cons* pli_getEnumeratedCollectionMembers(pli_Object* collection, pli_Module* module, pli_Environment* environment);
pli_Object* pli_evaluate(pli_Object* command, pli_Module* module, pli_Environment* environment);
pli_Object* pli_sEvaluate(char* command, char* moduleName, pli_Environment* environment);
void pli_powerloom(pli_Module* module, pli_Environment* environment);
pli_boolean pli_isLogicObject(pli_Object* obj);
pli_boolean pli_isSkolem(pli_Object* obj);
pli_boolean pli_isVariable(pli_Object* obj);
pli_boolean pli_isInteger(pli_Object* obj);
pli_boolean pli_isFloat(pli_Object* obj);
pli_boolean pli_isNumber(pli_Object* obj);
pli_boolean pli_isString(pli_Object* obj);
pli_boolean pli_isEnumeratedCollection(pli_Object* obj);
pli_boolean pli_isEnumeratedSet(pli_Object* obj);
pli_boolean pli_isEnumeratedList(pli_Object* obj);
pli_boolean pli_isTrue(pli_TruthValue* tv);
pli_boolean pli_isFalse(pli_TruthValue* tv);
pli_boolean pli_isUnknown(pli_TruthValue* tv);
pli_boolean pli_isKnown(pli_TruthValue* tv);
pli_boolean pli_isInconsistent(pli_TruthValue* tv);
pli_boolean pli_isStrict(pli_TruthValue* tv);
pli_boolean pli_isDefault(pli_TruthValue* tv);
pli_TruthValue* pli_ask(pli_Cons* query, pli_Module* module, pli_Environment* environment);
pli_TruthValue* pli_sAsk(char* query, char* moduleName, pli_Environment* environment);
pli_PlIterator* pli_retrieve(pli_Cons* query, pli_Module* module, pli_Environment* environment);
pli_PlIterator* pli_sRetrieve(char* query, char* moduleName, pli_Environment* environment);
pli_Proposition* pli_getFrameProposition(pli_ControlFrame* frame);
int pli_getFrameArity(pli_ControlFrame* frame);
pli_PlIterator* pli_getFrameIterator(pli_ControlFrame* frame);
void pli_setFrameIterator(pli_ControlFrame* frame, pli_PlIterator* iterator);
pli_Object* pli_getNthFrameArgument(pli_ControlFrame* frame, int n);
pli_Object* pli_getNthFrameBinding(pli_ControlFrame* frame, int n);
int pli_setNthFrameBinding(pli_ControlFrame* frame, int n, pli_Object* value);
int pli_isFrameBindingPattern(pli_ControlFrame* frame, char* pattern);
char* pli_getFrameBindingPattern(pli_ControlFrame* frame);
pli_Cons* pli_getFrameBindingState(pli_ControlFrame* frame);
void pli_setFrameBindingState(pli_ControlFrame* frame, pli_Cons* state);
pli_Object* pli_getPropertyObject(char* property, pli_Object* defaultvalue);
char* pli_getPropertyString(char* property, char* defaultvalue);
char* pli_getProperty(char* property, char* defaultvalue);
int pli_getPropertyInteger(char* property, int defaultvalue);
double pli_getPropertyFloat(char* property, double defaultvalue);
pli_boolean pli_getPropertyBoolean(char* property, pli_boolean defaultvalue);
void pli_setPropertyObject(char* property, pli_Object* value);
void pli_setPropertyString(char* property, char* value);
void pli_setProperty(char* property, char* value);
void pli_setPropertyInteger(char* property, int value);
void pli_setPropertyFloat(char* property, double value);
void pli_setPropertyBoolean(char* property, pli_boolean value);
pli_boolean pli_isDefinedProperty(char* property);
void pli_printProperties();
pli_cpp_function_code pli_getExceptionHandler();
void pli_setExceptionHandler(pli_cpp_function_code handler);
pli_Cons* pli_registerObject(pli_Object* object);
void pli_unregisterObject(pli_Cons* objecthandle);
