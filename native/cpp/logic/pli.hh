//  -*- Mode: C++ -*-

// pli.hh

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
 | Portions created by the Initial Developer are Copyright (C) 1997-2023      |
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


namespace pli {
  using namespace stella;
  using namespace logic;

// Class definitions:
class Environment : public StandardObject {
public:
  const char* level;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
};

class PlIterator : public Iterator {
public:
  Cons* cursor;
public:
  virtual Surrogate* primaryType();
  virtual Cons* consify();
  virtual List* listify();
  virtual int length();
  virtual boolean emptyP();
  virtual boolean nextP();
};

class ObjectRegistryList : public List {
public:
  int registryLength;
  int nFreeCells;
public:
  virtual Surrogate* primaryType();
};


// Global declarations:
extern boolean oPOWERLOOM_INITIALIZEDpo;
extern Environment* ASSERTION_ENV;
extern Environment* TAXONOMIC_ENV;
extern Environment* INFERENCE_ENV;
extern PlIterator* EMPTY_PL_ITERATOR;
extern NamedDescription* oLITERAL_CONCEPTo;
extern NamedDescription* oSTRING_CONCEPTo;
extern NamedDescription* oINTEGER_CONCEPTo;
extern NamedDescription* oFLOAT_CONCEPTo;
extern ObjectRegistryList* oOBJECT_REGISTRYo;

// Function signatures:
void initialize();
void resetPowerloom();
void clearCaches();
Environment* newEnvironment();
Object* accessEnvironmentSlotValue(Environment* self, Symbol* slotname, Object* value, boolean setvalueP);
boolean testEnvironmentLevelP(Environment* env, const char* level);
PlIterator* newPlIterator();
Object* accessPlIteratorSlotValue(PlIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
Object* plIteratorValue(PlIterator* self);
boolean plIteratorIsEmpty(PlIterator* self);
PlIterator* consToPlIterator(Cons* self);
PlIterator* listToPlIterator(List* self);
PlIterator* iteratorToPlIterator(Iterator* self);
Cons* createCons(Object* first, Cons* rest);
Cons* createConsList(int length);
int consLength(Cons* self);
boolean consIsEmpty(Cons* self);
Object* consFirst(Cons* self);
Cons* consRest(Cons* self);
Object* consNth(Cons* self, int n);
Cons* consNthRest(Cons* self, int n);
void consSetFirst(Cons* self, Object* value);
void consSetRest(Cons* self, Cons* rest);
void consSetNth(Cons* self, int n, Object* value);
void consSetNthRest(Cons* self, int n, Cons* rest);
Object* listFirst(List* self);
Cons* listRest(List* self);
Object* listNth(List* self, int n);
const char* createString(const char* content);
StringWrapper* createStringWrapper(const char* self);
StringWrapper* createDirectStringWrapper(const char* self);
IntegerWrapper* createIntegerWrapper(int self);
LongIntegerWrapper* createLongIntegerWrapper(long long int self);
FloatWrapper* createFloatWrapper(double self);
BooleanWrapper* createBooleanWrapper(boolean self);
Object* safelyGetObject(const char* name, Module* module, Environment* environment);
Object* safelyGetConcept(const char* name, Module* module, Environment* environment);
Object* safelyGetRelation(const char* name, Module* module, Environment* environment);
Context* safelyGetModule(const char* name, Environment* environment);
Object* safelyGetObjectOrNull(const char* name, Module* module, Environment* environment);
Cons* sequenceToConsList(Object* sequence);
Cons* explodeStringList(const char* stringlist, Module* module);
boolean legalOperatorP(Symbol* operatoR);
Keyword* getKeyword(const char* name);
Symbol* getSymbol(const char* name, Module* module, Environment* environment);
Symbol* getOperator(const char* name);
Object* getObject(const char* name, Module* module, Environment* environment);
Object* sGetObject(const char* name, const char* moduleName, Environment* environment);
LogicObject* getConcept(const char* name, Module* module, Environment* environment);
LogicObject* sGetConcept(const char* name, const char* moduleName, Environment* environment);
LogicObject* getRelation(const char* name, Module* module, Environment* environment);
LogicObject* sGetRelation(const char* name, const char* moduleName, Environment* environment);
PlIterator* getUndefinedRelations(Module* module, Environment* environment);
const char* getNameInModule(Object* obj, Module* module, Environment* environment);
const char* getName(Object* obj);
const char* getShortName(Object* obj);
const char* getSkolemName(Skolem* skolem);
const char* getSkolemShortName(Skolem* skolem);
const char* getVariableName(PatternVariable* variable);
const char* getVariableShortName(PatternVariable* variable);
const char* objectToString(Object* self);
int objectToInteger(Object* self);
double objectToFloat(Object* self);
const char* objectToParsableString(Object* self);
Symbol* getStellaType(Object* self);
Symbol* getLogicType(Object* self);
const char* getStellaTypeName(Object* self);
const char* getStellaTypeShortName(Object* self);
const char* getLogicTypeName(Object* self);
const char* getLogicTypeShortName(Object* self);
Object* stringToObject(const char* string, LogicObject* type, Module* module, Environment* environment);
Object* stringToStellaExpression(const char* expression, Module* module, Environment* environment);
Cons* helpGetTrueExtensionMembers(NamedDescription* relation, boolean specializeP);
Cons* helpGetPropositions(LogicObject* relation, Cons* arguments, int limit, Module* module, Environment* environment);
Proposition* getProposition(Object* relationAndArguments, Module* module, Environment* environment);
Proposition* sGetProposition(const char* relationAndArguments, const char* moduleName, Environment* environment);
PlIterator* getPropositions(Object* relationAndArguments, Module* module, Environment* environment);
PlIterator* sGetPropositions(const char* relationAndArguments, const char* moduleName, Environment* environment);
PlIterator* getInconsistentPropositions(Module* module, Environment* environment);
PlIterator* getUnaryPropositions(LogicObject* relation, Object* arg, Module* module, Environment* environment);
Proposition* getBinaryProposition(LogicObject* relation, Object* arg1, Object* arg2, Module* module, Environment* environment);
PlIterator* getBinaryPropositions(LogicObject* relation, Object* arg1, Object* arg2, Module* module, Environment* environment);
PlIterator* getInferredBinaryPropositionValues(LogicObject* relation, Object* arg, Module* module, Environment* environment);
PlIterator* sGetInferredBinaryPropositionValues(const char* relationName, const char* argName, const char* moduleName, Environment* environment);
PlIterator* getPropositionsOf(LogicObject* object, Module* module, Environment* environment);
PlIterator* sGetPropositionsOf(const char* objectName, const char* moduleName, Environment* environment);
PlIterator* getPropositionsInModule(Module* module, Environment* environment);
boolean isTrueUnaryProposition(LogicObject* relation, Object* arg, Module* module, Environment* environment);
boolean isTrueBinaryProposition(LogicObject* relation, Object* arg, Object* value, Module* module, Environment* environment);
boolean isTrueNaryProposition(Object* relationAndArguments, Module* module, Environment* environment);
boolean sIsTrueNaryProposition(const char* relationAndArguments, const char* moduleName, Environment* environment);
boolean isTrueProposition(Proposition* proposition, Module* module, Environment* environment);
boolean isSubrelation(LogicObject* sub, LogicObject* super, Module* module, Environment* environment);
PlIterator* getProperSubrelations(LogicObject* relation, Module* module, Environment* environment);
PlIterator* getDirectSubrelations(LogicObject* relation, Module* module, Environment* environment);
PlIterator* getProperSuperrelations(LogicObject* relation, Module* module, Environment* environment);
PlIterator* getDirectSuperrelations(LogicObject* relation, Module* module, Environment* environment);
boolean isInstance(Object* object, LogicObject* concept, Module* module, Environment* environment);
boolean isA(Object* object, LogicObject* concept, Module* module, Environment* environment);
PlIterator* getConceptInstances(LogicObject* concept, Module* module, Environment* environment);
PlIterator* sGetConceptInstances(const char* conceptName, const char* moduleName, Environment* environment);
PlIterator* getDirectConceptInstances(LogicObject* concept, Module* module, Environment* environment);
PlIterator* sGetDirectConceptInstances(const char* conceptName, const char* moduleName, Environment* environment);
PlIterator* getConceptInstancesMatchingValue(LogicObject* concept, LogicObject* relation, Object* value, Module* module, Environment* environment);
Object* getConceptInstanceMatchingValue(LogicObject* concept, LogicObject* relation, Object* value, Module* module, Environment* environment);
Cons* helpGetTypes(LogicObject* object, Module* module, Environment* environment);
PlIterator* getTypes(LogicObject* object, Module* module, Environment* environment);
PlIterator* getDirectTypes(LogicObject* object, Module* module, Environment* environment);
PlIterator* getRelationExtension(LogicObject* relation, Module* module, Environment* environment);
PlIterator* sGetRelationExtension(const char* relationName, const char* moduleName, Environment* environment);
Module* getModule(const char* name, Environment* environment);
Module* getExistingModule(const char* name, Environment* environment);
Module* getCurrentModule(Environment* environment);
Module* getHomeModule(LogicObject* object);
PlIterator* getModules(boolean kbModulesOnlyP);
Module* createModule(const char* name, Module* parent, boolean caseSensitiveP);
Module* sCreateModule(const char* name, const char* parentName, boolean caseSensitiveP, Environment* environment);
Module* changeModule(Module* module);
Module* sChangeModule(const char* name, Environment* environment);
Module* clearModule(Module* module);
Module* sClearModule(const char* name, Environment* environment);
PlIterator* getChildModules(Module* module);
PlIterator* sGetChildModules(const char* name, Environment* environment);
PlIterator* getParentModules(Module* module);
PlIterator* sGetParentModules(const char* name, Environment* environment);
const char* generateUniqueName(const char* prefix, Module* module, Environment* environment);
Keyword* createKeyword(const char* name);
Symbol* createSymbol(const char* name, Module* module, Environment* environment);
LogicObject* createObject(const char* name, LogicObject* concept, Module* module, Environment* environment);
LogicObject* sCreateObject(const char* name, const char* conceptName, const char* moduleName, Environment* environment);
LogicObject* createConcept(const char* name, LogicObject* parent, Module* module, Environment* environment);
LogicObject* sCreateConcept(const char* name, const char* parentName, const char* moduleName, Environment* environment);
LogicObject* createRelation(const char* name, int arity, Module* module, Environment* environment);
LogicObject* sCreateRelation(const char* name, int arity, const char* moduleName, Environment* environment);
LogicObject* createFunction(const char* name, int arity, Module* module, Environment* environment);
LogicObject* sCreateFunction(const char* name, int arity, const char* moduleName, Environment* environment);
void registerSpecialistFunction(const char* name, cpp_function_code functionReference, Module* module, Environment* environment);
void sRegisterSpecialistFunction(const char* name, const char* nativeName, const char* moduleName, Environment* environment);
void registerComputationFunction(const char* name, cpp_function_code functionReference, int arity, Module* module, Environment* environment);
void sRegisterComputationFunction(const char* name, const char* nativeName, int arity, const char* moduleName, Environment* environment);
LogicObject* createEnumeratedList(Cons* members, Module* module, Environment* environment);
LogicObject* createEnumeratedSet(Cons* members, Module* module, Environment* environment);
void destroyObject(Object* object);
void sDestroyObject(const char* objectName, const char* moduleName, Environment* environment);
Proposition* assertUnaryProposition(LogicObject* relation, Object* arg, Module* module, Environment* environment);
Proposition* assertBinaryProposition(LogicObject* relation, Object* arg, Object* value, Module* module, Environment* environment);
Proposition* assertNaryProposition(Object* relationAndArguments, Module* module, Environment* environment);
Proposition* retractUnaryProposition(LogicObject* relation, Object* arg, Module* module, Environment* environment);
Proposition* retractBinaryProposition(LogicObject* relation, Object* arg, Object* value, Module* module, Environment* environment);
Proposition* retractNaryProposition(Object* relationAndArguments, Module* module, Environment* environment);
Proposition* assertProposition(Proposition* proposition, Module* module, Environment* environment);
PlIterator* sAssertProposition(const char* sentence, const char* moduleName, Environment* environment);
Proposition* retractProposition(Proposition* proposition, Module* module, Environment* environment);
PlIterator* sRetractProposition(const char* sentence, const char* moduleName, Environment* environment);
PlIterator* conceive(Object* sentence, Module* module, Environment* environment);
PlIterator* sConceive(const char* sentence, const char* moduleName, Environment* environment);
PlIterator* getRules(LogicObject* relation, Module* module, Environment* environment);
PlIterator* sGetRules(const char* relationName, const char* moduleName, Environment* environment);
void sPrintRules(const char* name, OutputStream* stream, const char* moduleName, Environment* environment);
void runForwardRules(Object* module, boolean localP, boolean forceP);
int getArity(LogicObject* relation);
int sGetArity(const char* relationName, const char* moduleName, Environment* environment);
LogicObject* getDomain(LogicObject* relation);
LogicObject* sGetDomain(const char* relationName, const char* moduleName, Environment* environment);
LogicObject* getRange(LogicObject* relation);
LogicObject* sGetRange(const char* relationName, const char* moduleName, Environment* environment);
LogicObject* getNthDomain(LogicObject* relation, int n);
LogicObject* sGetNthDomain(const char* relationName, int n, const char* moduleName, Environment* environment);
void load(const char* filename, Environment* environment);
void loadInModule(const char* filename, Module* module, Environment* environment);
void loadStream(InputStream* stream, Environment* environment);
void loadStreamInModule(InputStream* stream, Module* module, Environment* environment);
void loadNativeStream(std::istream* stream, Environment* environment);
void loadNativeStreamInModule(std::istream* stream, Module* module, Environment* environment);
void saveModule(Module* module, const char* filename, const char* ifexists, Environment* environment);
void sSaveModule(const char* moduleName, const char* filename, const char* ifexists, Environment* environment);
LogicObject* getPredicate(Proposition* prop);
int getColumnCount(Object* obj);
Object* getNthValue(Object* sequence, int n, Module* module, Environment* environment);
const char* getNthString(Object* sequence, int n, Module* module, Environment* environment);
int getNthInteger(Object* sequence, int n, Module* module, Environment* environment);
double getNthFloat(Object* sequence, int n, Module* module, Environment* environment);
LogicObject* getNthLogicObject(Object* sequence, int n, Module* module, Environment* environment);
Cons* getEnumeratedCollectionMembers(Object* collection, Module* module, Environment* environment);
Object* evaluate(Object* command, Module* module, Environment* environment);
Object* sEvaluate(const char* command, const char* moduleName, Environment* environment);
void powerloom(Module* module, Environment* environment);
boolean isLogicObject(Object* obj);
boolean isSkolem(Object* obj);
boolean isVariable(Object* obj);
boolean isInteger(Object* obj);
boolean isFloat(Object* obj);
boolean isNumber(Object* obj);
boolean isString(Object* obj);
boolean isEnumeratedCollection(Object* obj);
boolean isEnumeratedSet(Object* obj);
boolean isEnumeratedList(Object* obj);
boolean isTrue(TruthValue* tv);
boolean isFalse(TruthValue* tv);
boolean isUnknown(TruthValue* tv);
boolean isKnown(TruthValue* tv);
boolean isInconsistent(TruthValue* tv);
boolean isStrict(TruthValue* tv);
boolean isDefault(TruthValue* tv);
TruthValue* ask(Cons* query, Module* module, Environment* environment);
TruthValue* sAsk(const char* query, const char* moduleName, Environment* environment);
PlIterator* retrieve(Cons* query, Module* module, Environment* environment);
PlIterator* sRetrieve(const char* query, const char* moduleName, Environment* environment);
Proposition* getFrameProposition(ControlFrame* frame);
int getFrameArity(ControlFrame* frame);
PlIterator* getFrameIterator(ControlFrame* frame);
void setFrameIterator(ControlFrame* frame, PlIterator* iterator);
Object* getNthFrameArgument(ControlFrame* frame, int n);
Object* getNthFrameBinding(ControlFrame* frame, int n);
boolean setNthFrameBinding(ControlFrame* frame, int n, Object* value);
boolean isFrameBindingPattern(ControlFrame* frame, const char* pattern);
const char* getFrameBindingPattern(ControlFrame* frame);
Cons* getFrameBindingState(ControlFrame* frame);
void setFrameBindingState(ControlFrame* frame, Cons* state);
Object* getPropertyObject(const char* property, Object* defaultvalue);
const char* getPropertyString(const char* property, const char* defaultvalue);
const char* getProperty(const char* property, const char* defaultvalue);
int getPropertyInteger(const char* property, int defaultvalue);
double getPropertyFloat(const char* property, double defaultvalue);
boolean getPropertyBoolean(const char* property, boolean defaultvalue);
void setPropertyObject(const char* property, Object* value);
void setPropertyString(const char* property, const char* value);
void setProperty(const char* property, const char* value);
void setPropertyInteger(const char* property, int value);
void setPropertyFloat(const char* property, double value);
void setPropertyBoolean(const char* property, boolean value);
boolean isDefinedProperty(const char* property);
void printProperties();
cpp_function_code getExceptionHandler();
void setExceptionHandler(cpp_function_code handler);
ObjectRegistryList* newObjectRegistryList();
Object* accessObjectRegistryListSlotValue(ObjectRegistryList* self, Symbol* slotname, Object* value, boolean setvalueP);
Cons* registerObject(Object* object);
void unregisterObject(Cons* objecthandle);
void helpStartupPli1();
void helpStartupPli2();
void helpStartupPli3();
void helpStartupPli4();
void helpStartupPli5();
void helpStartupPli6();
void helpStartupPli7();
void helpStartupPli8();
void startupPli();

// Auxiliary global declarations:
extern Symbol* SYM_PLI_STELLA_C_CALLABLE_WRAPPER_CODE;
extern Surrogate* SGT_PLI_PLI_ENVIRONMENT;
extern Symbol* SYM_PLI_LOGIC_LEVEL;
extern Surrogate* SGT_PLI_PLI_PL_ITERATOR;
extern Symbol* SYM_PLI_STELLA_CURSOR;
extern Surrogate* SGT_PLI_STELLA_CONS;
extern Surrogate* SGT_PLI_STELLA_LIST;
extern Surrogate* SGT_PLI_STELLA_VECTOR;
extern Symbol* SYM_PLI_STELLA_NULL;
extern Surrogate* SGT_PLI_LOGIC_SKOLEM;
extern Surrogate* SGT_PLI_LOGIC_LOGIC_OBJECT;
extern Surrogate* SGT_PLI_STELLA_GENERALIZED_SYMBOL;
extern Surrogate* SGT_PLI_STELLA_MODULE;
extern Surrogate* SGT_PLI_STELLA_CONTEXT;
extern Surrogate* SGT_PLI_LOGIC_COMPUTED_PROCEDURE;
extern Surrogate* SGT_PLI_STELLA_LITERAL_WRAPPER;
extern Surrogate* SGT_PLI_LOGIC_NAMED_DESCRIPTION;
extern Symbol* SYM_PLI_PLI_pR;
extern Symbol* SYM_PLI_PLI_pI;
extern Symbol* SYM_PLI_PLI_pV;
extern Symbol* SYM_PLI_PLI_F_GET_INFERRED_BINARY_PROPOSITION_VALUES_QUERY_000;
extern Symbol* SYM_PLI_LOGIC_ALL;
extern Symbol* SYM_PLI_LOGIC_pX;
extern Symbol* SYM_PLI_STELLA_AND;
extern Symbol* SYM_PLI_LOGIC_FAIL;
extern Symbol* SYM_PLI_STELLA_EXISTS;
extern Symbol* SYM_PLI_LOGIC_pY;
extern Symbol* SYM_PLI_PLI_PROPER_SUBRELATION;
extern Symbol* SYM_PLI_STELLA_TRUE;
extern Symbol* SYM_PLI_STELLA_FALSE;
extern Keyword* KWD_PLI_CASE_SENSITIVEp;
extern Keyword* KWD_PLI_SUBSET_OF;
extern Keyword* KWD_PLI_ERROR;
extern Keyword* KWD_PLI_RETRACT_TRUE;
extern Keyword* KWD_PLI_ASSERT_TRUE;
extern Surrogate* SGT_PLI_LOGIC_PROPOSITION;
extern Surrogate* SGT_PLI_LOGIC_DESCRIPTION;
extern Surrogate* SGT_PLI_PL_KERNEL_KB_NTH_DOMAIN;
extern Keyword* KWD_PLI_MODULE;
extern Surrogate* SGT_PLI_LOGIC_PATTERN_VARIABLE;
extern Surrogate* SGT_PLI_STELLA_INTEGER_WRAPPER;
extern Surrogate* SGT_PLI_STELLA_FLOAT_WRAPPER;
extern Surrogate* SGT_PLI_STELLA_NUMBER_WRAPPER;
extern Surrogate* SGT_PLI_STELLA_STRING_WRAPPER;
extern Symbol* SYM_PLI_STELLA_ITERATOR;
extern Surrogate* SGT_PLI_PLI_OBJECT_REGISTRY_LIST;
extern Symbol* SYM_PLI_PLI_REGISTRY_LENGTH;
extern Symbol* SYM_PLI_PLI_N_FREE_CELLS;
extern Keyword* KWD_PLI_DOCUMENTATION;
extern Symbol* SYM_PLI_PLI_STARTUP_PLI;
extern Symbol* SYM_PLI_STELLA_METHOD_STARTUP_CLASSNAME;

// Function signatures:
int main();

} // end of namespace pli
