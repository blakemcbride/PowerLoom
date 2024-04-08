//  -*- Mode: C++ -*-

// propositions.hh

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


namespace logic {
  using namespace stella;

// Class definitions:
class BacklinksIndex : public StandardObject {
// Contains several types of indices pointing at dependent propositions.
public:
  SequenceIndex* dependentPropositionsList;
  SequenceIndex* dependentIsaPropositionsList;
  HashTable* predicatePropositionsTable;
public:
  virtual Surrogate* primaryType();
  virtual BacklinksIndex* removeDeletedMembers();
};

class LogicObject : public ContextSensitiveObject {
// Object with propositions, and possibly a variable value.
public:
  // List of direct parents whose `variable-value' slot points to this object.
  Object* variableValueInverse;
  Surrogate* surrogateValueInverse;
  KeyValueList* dynamicSlots;
  BacklinksIndex* dependentPropositionsIndex;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
  virtual void processDefinitionOptions(Object* options);
  virtual int introductionTimestamp();
  virtual void markAsIncoherent();
  virtual boolean deletedPSetter(boolean value);
  virtual boolean deletedP();
  virtual BooleanWrapper* badP_reader();
  virtual Cons* variableValueInverse_reader();
};

class LogicThing : public Thing {
// A subclass of THING so we can add methods to it in
// the PowerLoom LOGIC module.
public:
  virtual Surrogate* primaryType();
  virtual Object* generateSpecializedTerm();
};

class Skolem : public LogicObject {
// Object whose identity and type are not fixed at creation time.
// Potentially unifiable with any other object.
public:
  Surrogate* skolemType;
  Symbol* skolemName;
  Object* variableValue;
  Proposition* definingProposition;
public:
  virtual Surrogate* primaryType();
  virtual void markAsIncoherent();
  virtual void reactToInferenceUpdate();
  virtual boolean objectEqualP(Object* other);
  virtual int skolemGenerationCount_reader();
  virtual Cons* conflictingDefaultValues_reader();
};

class PatternVariable : public Skolem {
// A variable in a logical expression.
public:
  int boundToOffset;
public:
  virtual Surrogate* primaryType();
};

class ForwardChainingIndex : public StandardObject {
public:
  Proposition* forwardGoal;
  Proposition* masterRule;
  Cons* ioVariables;
  Cons* queryBody;
  Cons* inputBindings;
  Symbol* cacheId;
  Description* consequent;
public:
  virtual Surrogate* primaryType();
  virtual boolean deletedP();
};

class Description : public LogicObject {
public:
  Proposition* proposition;
  Vector* ioVariables;
  // The set of internally quantified variables besides the
  // descriptions's IO variables.  This set includes any top-level implicit
  // existential variables plus any variables introduced by some nested quantifier.
  // IMPORTANT: therefore, a description's internal variables are not necessarily
  // equivalent to its top-level implicit existential variables.
  Vector* internalVariables;
  KeyValueList* queryPatterns;
public:
  virtual Surrogate* primaryType();
  virtual boolean virginP();
  virtual LogicObject* findDuplicateNamedDescription();
  virtual Symbol* descriptionName();
  virtual Surrogate* descriptionSurrogate();
  virtual int arity();
  virtual Relation* nativeRelation();
  virtual List* structuralFunctionEvaluationOrder_reader();
  virtual BooleanWrapper* deferredContrapositivesP_reader();
  virtual List* forwardChainingIndices_reader();
public:
  virtual void helpPrintOutline(OutputStream* stream, int currentDepth, int depth, boolean namedP);
};

class NamedDescription : public Description {
public:
  List* ioVariableNames;
  List* ioVariableTypes;
  SequenceIndex* extension;
  const char* objectStringifiedSource;
  // List of propositions generated by the definition of
  // this description.
  List* objectOriginatedPropositions;
public:
  virtual Surrogate* primaryType();
  virtual void processDefinitionOptions(Object* options);
  virtual void describeObject(OutputStream* stream, Keyword* mode);
  virtual Symbol* descriptionName();
  virtual int arity();
  virtual Relation* nativeRelation();
  virtual void nativeRelationSetter(Relation* value);
  virtual List* uniquenessvectors_reader();
public:
  virtual void helpPrintOutline(OutputStream* stream, int currentDepth, int depth, boolean namedP);
};

class TruthValue : public LogicObject {
public:
  // One of :TRUE, :FALSE, :UNKNOWN or :INCONSISTENT.
  Keyword* polarity;
  // Either NULL, :STRICT or :DEFAULT.
  Keyword* strength;
  double matchScore;
public:
  virtual Surrogate* primaryType();
};

class PartialSupport : public StandardObject {
public:
  Proposition* fact;
  Proposition* axiom;
  double score;
  int id;
  Cons* argumentScores;
public:
  virtual Surrogate* primaryType();
};

class Proposition : public ContextSensitiveObject {
// 
public:
  Keyword* kind;
  Object* truthValue;
  Vector* arguments;
  GeneralizedSymbol* operatoR;
  NonPagingIndex* dependentPropositions;
  KeyValueList* dynamicSlots;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
  virtual void processDefinitionOptions(Object* options);
  virtual boolean clusteredConjunctionP();
  virtual void reactToInferenceUpdate();
  virtual boolean deletedPSetter(boolean value);
  virtual boolean deletedP();
  virtual List* forwardJustifications_reader();
  virtual List* forwardChainingGoals_reader();
  virtual Cons* clashExceptions_reader();
  virtual BooleanWrapper* badP_reader();
  virtual Cons* support_reader();
  virtual double weightDelta_reader();
  virtual BooleanWrapper* unfastenedP_reader();
  virtual List* satellitePropositions_reader();
  virtual BooleanWrapper* variableTypeP_reader();
};

class QuantityLogicWrapper : public LogicThing {
public:
  Quantity* wrapperValue;
  Cons* functionTerm;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
};

class IntegerLogicWrapper : public IntegerWrapper {
public:
  BacklinksIndex* dependentPropositionsIndex;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
};

class FloatLogicWrapper : public FloatWrapper {
public:
  BacklinksIndex* dependentPropositionsIndex;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
};

class StringLogicWrapper : public StringWrapper {
public:
  BacklinksIndex* dependentPropositionsIndex;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
};

class LogicException : public StellaException {
public:
  LogicException(const std::string& msg) : StellaException(msg) {
}

};

class PropositionError : public LogicException {
public:
  PropositionError(const std::string& msg) : LogicException(msg) {
}

};

class ParsingError : public LogicException {
public:
  ParsingError(const std::string& msg) : LogicException(msg) {
}

};

class Clash : public LogicException {
public:
  // The main proposition involved in the clash
  Proposition* proposition;
  // The context in which the clash occurred
  Context* context;
public:
  Clash(const std::string& msg) : LogicException(msg) {
}

};

class TruthValueClash : public Clash {
public:
  TruthValueClash(const std::string& msg) : Clash(msg) {
}

};

class IntervalClash : public Clash {
public:
  // The owner of the interval cache that is unsatisfiable.
  LogicObject* intervalMember;
  Object* lowerBound;
  Object* upperBound;
  boolean strictLowerBoundP;
  boolean strictUpperBoundP;
public:
  IntervalClash(const std::string& msg) : Clash(msg) {
}

};

class VariableValueClash : public Clash {
public:
  // Skolem which is getting multiple values.
  Skolem* skolem;
  // First value in value clash
  Object* value1;
  // Second value in value clash
  Object* value2;
public:
  VariableValueClash(const std::string& msg) : Clash(msg) {
}

};

class UnificationClash : public Clash {
public:
  // First value in unification clash
  Object* value1;
  // Second value in unification clash
  Object* value2;
public:
  UnificationClash(const std::string& msg) : Clash(msg) {
}

};

class FailException : public LogicException {
public:
  FailException(const std::string& msg) : LogicException(msg) {
}

};

class QueryThreadLimitViolation : public LogicException {
public:
  QueryThreadLimitViolation(const std::string& msg) : LogicException(msg) {
}

};

class ExceptionRecord : public StandardObject {
public:
  StellaException* exception;
  Context* context;
  Module* module;
public:
  virtual Surrogate* primaryType();
};

class ObjectAlreadyExistsException : public StellaException {
public:
  Object* existingObject;
public:
  ObjectAlreadyExistsException(const std::string& msg) : StellaException(msg) {
}

};

class CheckTypesRecord : public StandardObject {
public:
  Proposition* proposition;
  Object* parentProposition;
  Description* parentDescription;
  Module* module;
public:
  virtual Surrogate* primaryType();
};


// Global declarations:
extern Vector* ZERO_VARIABLES_VECTOR;
extern int oPARTIAL_SUPPORT_COUNTERo;
extern PropertyList* oOPERATOR_NAME_TO_SURROGATE_TABLEo;
extern Module* oLOGIC_MODULEo;
extern Module* oPL_KERNEL_MODULEo;
extern int oNOW_TIMESTAMPo;
extern Keyword* oLAST_KB_ACTIONo;
extern LogicObject* BOTTOM;
extern DECLARE_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword* );
extern DECLARE_STELLA_SPECIAL(oCLIPPINGENABLEDpo, boolean );
extern DECLARE_STELLA_SPECIAL(oNATURALDEDUCTIONMODEpo, boolean );
extern boolean oCONTEXT_DEPENDENT_SEARCH_MODEpo;
extern DECLARE_STELLA_SPECIAL(oCOMPUTEDQUERYpo, boolean );
extern int oSKOLEM_ID_COUNTERo;
extern DECLARE_STELLA_SPECIAL(oVARIABLEIDCOUNTERo, int );
extern DECLARE_STELLA_SPECIAL(oFREESKOLEMSo, Cons* );
extern TruthValue* TRUE_TRUTH_VALUE;
extern TruthValue* FALSE_TRUTH_VALUE;
extern TruthValue* DEFAULT_TRUE_TRUTH_VALUE;
extern TruthValue* DEFAULT_FALSE_TRUTH_VALUE;
extern TruthValue* UNKNOWN_TRUTH_VALUE;
extern TruthValue* INCONSISTENT_TRUTH_VALUE;
extern DECLARE_STELLA_SPECIAL(oSUPPRESSUNTYPEDTYPEERRORpo, boolean );
extern boolean oEQUIVALENCE_COLLECTIONSpo;
extern Proposition* TRUE_PROPOSITION;
extern Proposition* FALSE_PROPOSITION;
extern Symbol* ANONYMOUS_VARIABLE_NAME;
extern KeyValueList* oMISSING_KEY_VALUE_LISTo;
extern DECLARE_STELLA_SPECIAL(oAUTOMATICINSTANCETABLEo, KeyValueList* );
extern DECLARE_STELLA_SPECIAL(oDEFAULTCREATIONTYPEo, Surrogate* );
extern KeyValueMap* oSTRUCTURED_OBJECTS_INDEXo;
extern DECLARE_STELLA_SPECIAL(oDONT_CHECK_FOR_DUPLICATE_PROPOSITIONSpo, boolean );
extern DECLARE_STELLA_SPECIAL(oVISITEDUNFASTENEDDEFININGPROPOSITIONSo, List* );
extern boolean oAUTO_COERCE_PROPOSITIONAL_ARGUMENTSpo;
extern Keyword* oTYPE_CHECK_POLICYo;
extern DECLARE_STELLA_SPECIAL(oTYPECHECKMODEo, Keyword* );
extern VectorSequence* oCHECK_TYPES_AGENDAo;
extern DECLARE_STELLA_SPECIAL(oDEFERRED_TERMS_TO_UNLINKo, HashSet* );

// Function signatures:
BacklinksIndex* newBacklinksIndex();
Object* accessBacklinksIndexSlotValue(BacklinksIndex* self, Symbol* slotname, Object* value, boolean setvalueP);
LogicObject* newLogicObject();
Object* accessLogicObjectSlotValue(LogicObject* self, Symbol* slotname, Object* value, boolean setvalueP);
LogicThing* newLogicThing();
Object* accessLogicThingSlotValue(LogicThing* self, Symbol* slotname, Object* value, boolean setvalueP);
void logLogicObject(LogicObject* self);
Skolem* newSkolem();
Object* accessSkolemSlotValue(Skolem* self, Symbol* slotname, Object* value, boolean setvalueP);
PatternVariable* newPatternVariable();
Object* accessPatternVariableSlotValue(PatternVariable* self, Symbol* slotname, Object* value, boolean setvalueP);
ForwardChainingIndex* newForwardChainingIndex();
Object* accessForwardChainingIndexSlotValue(ForwardChainingIndex* self, Symbol* slotname, Object* value, boolean setvalueP);
Description* newDescription();
Object* accessDescriptionSlotValue(Description* self, Symbol* slotname, Object* value, boolean setvalueP);
NamedDescription* newNamedDescription();
Object* accessNamedDescriptionSlotValue(NamedDescription* self, Symbol* slotname, Object* value, boolean setvalueP);
TruthValue* newTruthValue();
Object* accessTruthValueSlotValue(TruthValue* self, Symbol* slotname, Object* value, boolean setvalueP);
PartialSupport* newPartialSupport();
Object* accessPartialSupportSlotValue(PartialSupport* self, Symbol* slotname, Object* value, boolean setvalueP);
Proposition* newProposition();
Object* accessPropositionSlotValue(Proposition* self, Symbol* slotname, Object* value, boolean setvalueP);
QuantityLogicWrapper* newQuantityLogicWrapper(Quantity* wrapperValue);
Object* accessQuantityLogicWrapperSlotValue(QuantityLogicWrapper* self, Symbol* slotname, Object* value, boolean setvalueP);
IntegerLogicWrapper* newIntegerLogicWrapper(int wrapperValue);
FloatLogicWrapper* newFloatLogicWrapper(double wrapperValue);
StringLogicWrapper* newStringLogicWrapper(const char* wrapperValue);
const char* stringifiedSource(Object* self);
const char* stringifiedSourceSetter(Object* self, const char* value);
List* originatedPropositions(Object* self);
List* originatedPropositionsSetter(Object* self, List* value);
Proposition* createProposition(Symbol* kind, int argumentcount);
void enforceCodeOnly();
Surrogate* getPropositionBaseOperator(Proposition* prop);
LogicException* newLogicException(const char* message);
PropositionError* newPropositionError(const char* message);
ParsingError* newParsingError(const char* message);
Clash* newClash(const char* message);
TruthValueClash* newTruthValueClash(const char* message);
IntervalClash* newIntervalClash(const char* message);
VariableValueClash* newVariableValueClash(const char* message);
UnificationClash* newUnificationClash(const char* message);
FailException* newFailException(const char* message);
QueryThreadLimitViolation* newQueryThreadLimitViolation(const char* message);
ExceptionRecord* newExceptionRecord();
Object* accessExceptionRecordSlotValue(ExceptionRecord* self, Symbol* slotname, Object* value, boolean setvalueP);
boolean logicModuleP(Module* self);
SequenceIndex* locallyConceivedPropositions(Module* self);
void locallyConceivedPropositionsSetter(Module* self, SequenceIndex* value);
SequenceIndex* locallyConceivedInstances(Context* self);
void locallyConceivedInstancesSetter(Context* self, SequenceIndex* value);
void incrementNowTimestamp();
int getNowTimestamp();
void updateNowTimestamp(Keyword* kbaction);
boolean bottomP(Object* self);
boolean subrelationOfP(NamedDescription* desc1, NamedDescription* desc2);
boolean logicalSubtypeOfP(Surrogate* type1, Surrogate* type2);
boolean logicalSubtypeOfLiteralP(Surrogate* type);
boolean literalTypeP(Surrogate* type);
boolean booleanTypeP(Surrogate* self);
boolean propositionTypeP(Surrogate* self);
boolean classDescriptionP(NamedDescription* self);
boolean functionDescriptionP(NamedDescription* self);
boolean variableArityP(Description* self);
boolean monadicP(Object* self);
boolean computedRelationP(NamedDescription* description);
Object* lastArgument(Proposition* proposition);
Surrogate* objectSurrogate(Object* self);
Surrogate* objectSurrogateSetter(Object* self, Surrogate* name);
Symbol* objectName(Object* self);
const char* objectNameString(Object* self);
const char* objectStringName(Object* self);
boolean descriptionModeP();
boolean naturalDeductionModeP();
boolean contextDependentSearchModeP();
void logNewlyConceivedProposition(Module* self, Proposition* proposition);
void clipOrClashWithOldPredicateValue(Proposition* proposition);
void runUpdateEquivalencePropositionDemon(Proposition* proposition, Keyword* updatemode);
void helpRunUpdatePropositionDemon(Proposition* proposition, Keyword* updatemode);
void runUpdatePropositionDemon(Proposition* proposition, Keyword* updatemode);
void runTruthChangeDemon(Proposition* proposition, Surrogate* truthchangerelation);
void runGoesTrueDemons(Proposition* proposition);
void runGoesFalseDemons(Proposition* proposition);
void runGoesUnknownDemons(Proposition* proposition);
void updateLinksAndTimestamps(Proposition* proposition, Keyword* updatemode);
void assignTruthValue(Proposition* self, Object* truthvalue);
void deassignTruthValue(Proposition* self, Keyword* updatemode);
void updatePropositionTruthValue(Proposition* self, Keyword* updatemode);
void assignPropositionWeight(Proposition* self, double weight);
Context* tickleContext();
Context* tickleInstances();
Cons* listInconsistentPropositions(Cons* options);
Cons* listInconsistentPropositionsEvaluatorWrapper(Cons* arguments);
void reactToSkolemValueUpdate(Skolem* skolem, Object* oldvalue, Object* newvalue, boolean toplevelupdateP);
boolean nativeSlotPropositionP(Proposition* self);
Cons* updateNativeSlotProposition(Proposition* proposition, Keyword* updatemode);
void assignNativeSlotValue(Proposition* prop, Thing* self, StorageSlot* slot, Object* value);
void clearNativeSlotValue(Thing* object, StorageSlot* slot);
void dropNativeSlotValue(Thing* self, StorageSlot* slot, Object* value);
Surrogate* lookupSlotrefOnInstance(Object* term, Symbol* slotname);
boolean unboundP(Skolem* skolem);
Object* valueOf(Object* self);
Object* surrogateDvalueOf(Surrogate* self);
Description* relationDvalueOf(Relation* self);
Object* equivalentValueOf(Object* self);
Object* groundValueOf(Object* self);
boolean skolemP(Object* self);
boolean variableP(Object* self);
boolean nativeValueP(Object* self);
Object* nativeValueOf(Object* self);
PatternVariable* innermostVariableOf(PatternVariable* self);
Object* innermostOf(Object* self);
Symbol* yieldAnonymousSkolemName(boolean variableP);
Skolem* helpCreateSkolem(Skolem* self, Surrogate* type, Symbol* name, boolean assertisaP);
Skolem* createSkolem(Surrogate* type, Symbol* name);
PatternVariable* createVariable(Surrogate* type, Symbol* name, boolean assertisaP);
Skolem* createVariableOrSkolem(Surrogate* type, Symbol* name);
boolean trueP(Proposition* self);
boolean falseP(Proposition* self);
boolean unknownP(Proposition* self);
boolean inconsistentP(Proposition* self);
boolean defaultTrueP(Proposition* self);
boolean defaultFalseP(Proposition* self);
boolean assertedTrueP(Proposition* self);
boolean assertedFalseP(Proposition* self);
TruthValue* defaultifyTruthValue(boolean trueP, boolean bydefaultP);
TruthValue* conjoinTruthValues(TruthValue* tv1, TruthValue* tv2);
TruthValue* disjoinTruthValues(TruthValue* tv1, TruthValue* tv2);
TruthValue* invertTruthValue(TruthValue* self);
boolean strongerTruthValueP(TruthValue* tv1, TruthValue* tv2);
TruthValue* mergeTruthValues(TruthValue* tv1, TruthValue* tv2);
TruthValue* weakenTruthValue(TruthValue* tv1, TruthValue* tv2);
TruthValue* strengthenTruthValue(TruthValue* tv1, TruthValue* tv2);
boolean trueTruthValueP(TruthValue* self);
boolean falseTruthValueP(TruthValue* self);
boolean strictTruthValueP(TruthValue* self);
boolean defaultTruthValueP(TruthValue* self);
boolean unknownTruthValueP(TruthValue* self);
boolean knownTruthValueP(TruthValue* self);
boolean inconsistentTruthValueP(TruthValue* self);
const char* truthValueToString(TruthValue* self, boolean abbreviateP);
void printTruthValue(TruthValue* self, OutputStream* stream);
void signalUnificationClash(Proposition* prop, Object* term1, Object* term2);
void signalVariableValueClash(Proposition* prop, Skolem* skolem, Object* value1, Object* value2);
void signalTruthValueClash(Proposition* proposition);
Cons* getVisibleClashExceptions(Proposition* incoherentprop);
void handleClashException(Clash* clashexception);
Surrogate* logicalType(Object* self);
Surrogate* safeLogicalType(Object* self);
Surrogate* classLogicalType(Class* self);
void unifyTypes(Proposition* prop, Skolem* term1, Object* term2);
void unifySkolemAndValue(Skolem* skolem, Object* value);
void verifySkolemAndValueTypes(Skolem* fromskolem, Object* tovalue);
boolean skolemWithVariableValueCycleP(Object* self);
void synchronizeVariableValueInferenceCaches(Skolem* fromskolem, Skolem* tovalue);
void bindSkolemToValue(Skolem* fromskolem, Object* tovalue, boolean toplevelupdateP);
void unbindSkolemValue(Skolem* skolem, boolean toplevelupdateP);
boolean hasEquivalentValuesP(Object* term);
Cons* getVariableValueInverses(Object* term);
Cons* getAllVariableValueInverses(Object* term);
Cons* getAllEquivalentValues(Object* term);
void constrainAsSubset(Proposition* prop, Collection* set1, Collection* set2);
void equateCollections(Proposition* prop, Collection* col1, Collection* col2);
boolean logicCollectionP(Object* term);
void equateValues(Proposition* prop, Object* term1, Object* term2);
boolean unequateConflictingDefaultValuesP(Proposition* newequatingprop);
boolean unequateValuesP(Object* term1, Object* term2);
void bindToEquivalentValue(LogicObject* from, Description* to);
void unbindEquivalentValue(LogicObject* self);
void unlinkEquivalentValue(LogicObject* self);
int equivalentCollectionPriority(LogicObject* self);
void equivalenceCollections(LogicObject* collection1, LogicObject* collection2);
void reviseEquivalences(Proposition* proposition, boolean goestrueP);
Proposition* findEquatingProposition(Object* directobject, LogicObject* indirectobject);
boolean constantPropositionP(Proposition* self);
Object* evaluateTerm(Object* self);
Object* evaluateLiteralWrapperTerm(LiteralWrapper* self);
Object* evaluateSurrogateTerm(Surrogate* self);
Object* evaluateLogicObjectTerm(LogicObject* self);
boolean anonymousVariableP(Skolem* self);
Object* evaluateSymbolTerm(Symbol* self);
Object* evaluateAutomaticInstance(Symbol* name);
void signalUndefinedTerm(Object* term);
void signalUntypedTerm(Object* term);
Object* evaluateCreateTerm(Cons* term);
Object* create(GeneralizedSymbol* name, Cons* type);
Object* createEvaluatorWrapper(Cons* arguments);
void updateSkolemType(Skolem* self, Surrogate* type);
void updateSkolemTypeFromIsaAssertions(Proposition* self);
boolean descriptionExtensionL(Description* desc1, Description* desc2);
void printExtensionSizes(Module* module, int sizecutoff);
void transferLogicInformationFromRelationHook(List* relationslist);
void retractRelationAxioms(NamedDescription* oldrelation);
Proposition* assertDescriptionImpliesDescription(Description* sub, Description* super, boolean dontupdateP);
Proposition* assertImpliesLinkBetweenRelations(NamedDescription* sub, NamedDescription* super);
void finalizeSuperrelationLinks(Relation* self);
Proposition* updateIsaProposition(Object* self, Surrogate* type, Keyword* updatemode);
Proposition* assertIsaProposition(Object* self, Surrogate* type);
Proposition* retractIsaProposition(Object* self, Surrogate* type);
Proposition* updateProperty(LogicObject* self, Surrogate* surrogate, Keyword* updatemode);
Proposition* assertProperty(LogicObject* instance, Surrogate* property);
Proposition* retractProperty(LogicObject* instance, Surrogate* property);
Proposition* updateTuple(Surrogate* relation, Cons* arguments, Keyword* updatemode);
Proposition* assertTuple(Surrogate* relation, Cons* arguments);
Proposition* updateBinaryValue(Surrogate* relation, Object* self, Object* value, Keyword* updatemode);
Proposition* assertBinaryValue(Surrogate* relation, Object* self, Object* value);
Proposition* retractBinaryValue(Surrogate* relation, Object* self, Object* value);
Proposition* assertMemberOfProposition(Object* self, Object* collection);
ObjectAlreadyExistsException* newObjectAlreadyExistsException(const char* message);
Object* helpCreateLogicInstance(Surrogate* name, Surrogate* type);
Object* createLogicInstance(Surrogate* name, Surrogate* type);
void cleanupStructuredObjectsIndex(Module* clearmodule);
int propositionHashIndex(Proposition* self, KeyValueMap* mapping, boolean derefsurrogatesP);
Proposition* lookupMatchingPropositionInBucket(List* bucket, Proposition* self, KeyValueMap* mapping);
Proposition* findDuplicateComplexProposition(Proposition* self);
Proposition* findDuplicateProposition(Proposition* self);
Proposition* findMatchingNonDescriptiveProposition(Proposition* self, KeyValueMap* mapping);
Proposition* fastenDownOneProposition(Proposition* self, boolean dontcheckforduplicatesP);
Proposition* helpFastenDownPropositions(Proposition* self, boolean dontcheckforduplicatesP);
Proposition* recursivelyFastenDownPropositions(Proposition* self, boolean dontcheckforduplicatesP);
void unfastenProposition(Proposition* proposition);
void instantiateUndefinedSurrogates(Proposition* self);
Proposition* buildTopLevelProposition(Object* tree, boolean trueassertionP);
Object* buildProposition(Object* tree);
Proposition* surrogateDbuildProposition(Surrogate* self);
Object* symbolDbuildProposition(Symbol* symbol);
Proposition* consDbuildProposition(Cons* tree);
void verifyNumberOfPropositionArguments(Cons* tree, int correctnumber);
Proposition* buildIsaProposition(Cons* tree);
Proposition* buildMemberOfProposition(Cons* tree);
boolean memberOfPropositionP(Proposition* proposition);
boolean subsetOfPropositionP(Proposition* proposition);
boolean simpleSubrelationPropositionP(Proposition* proposition);
Object* extractAnnotation(Object* tree, Keyword* option, Object*& _Return1);
Object* lookupAnnotation(Proposition* proposition, Keyword* key);
void insertAnnotation(Proposition* proposition, Keyword* key, Object* value);
void removeAnnotation(Proposition* proposition, Keyword* key);
Proposition* buildAnnotatedProposition(Cons* tree);
void finalizePropositionAnnotations(Proposition* proposition);
void clearPropositionAnnotations(Proposition* proposition);
void forwardBackwardOptionHandler(Proposition* self, StorageSlot* slot, Object* tree);
void inheritPropositionAnnotations(PropertyList* annotations, Proposition* to);
boolean functionInducedExistsP(Proposition* proposition);
Proposition* predicateOfFunctionInducedExists(Proposition* existsproposition);
Proposition* embedNegationWithinFunctionInducedExists(Proposition* existsproposition);
Proposition* buildAndOrNotProposition(Cons* tree);
Proposition* conceiveInvertedProposition(Proposition* prop);
boolean functionalTermP(Object* term);
boolean clipValueP(Object* term1, Object* term2);
Proposition* createEquivalenceProposition(Object* term1, Object* term2);
Proposition* buildEquivalenceProposition(Cons* tree);
Proposition* buildConjunctionOfEqualityPropositions(Cons* remainingterms, Cons* equivalences);
Proposition* buildFailProposition(Cons* tree);
Proposition* buildCollectIntoProposition(Cons* tree);
boolean holdsOperatorP(Object* operatoR);
void verifyEvaluableOperator(Object* operatoR, Keyword* kind);
Proposition* buildHoldsProposition(Cons* tree);
Surrogate* mostGeneralEquivalentSlotref(Surrogate* surrogate);
boolean polymorphicRelationP(Relation* self);
boolean nonPolymorphicPredicateP(LogicObject* self);
LogicObject* evaluatePredicate(GeneralizedSymbol* name, Object* firstargument);
boolean propositionalArgumentP(Object* argument);
Object* evaluateTypedArgument(Object* argument, Surrogate* type);
Object* evaluatePropositionTerm(Object* tree);
LogicObject* evaluatePredicateAndFirstArgument(Cons* tree, Object*& _Return1);
Object* evaluateFirstArgument(Object* argument, Symbol* relationname);
Cons* evaluateRemainingArguments(LogicObject* predicatevalue, Cons* arguments);
boolean classOperatorP(GeneralizedSymbol* operatoR);
Proposition* buildPredicateProposition(Cons* tree);
boolean checkStrictTypeP(Object* self, Surrogate* type, boolean shallowP);
boolean checkTypeP(Object* self, Surrogate* type, boolean shallowP);
boolean checkCoercedTypeP(Object* self, Surrogate* type, boolean shallowP, Object*& _Return1);
Object* coerceIncompatibleValue(Object* value, Surrogate* type);
Object* coerceQuantity(Object* value, Surrogate* quantitytyperef);
Object* coerceDate(Object* value, Surrogate* datetyperef);
void verifyOneArgumentType(Object* arg, Surrogate* type, Proposition* proposition, NamedDescription* description);
void verifyArgumentTypesAndCount(Proposition* proposition);
void handleArgumentTypeViolation(Proposition* proposition, Object* arg, Surrogate* requiredtype);
void handleArityViolation(Proposition* proposition, int requiredarity);
CheckTypesRecord* newCheckTypesRecord();
Object* accessCheckTypesRecordSlotValue(CheckTypesRecord* self, Symbol* slotname, Object* value, boolean setvalueP);
void postToCheckTypesAgenda(Proposition* self);
void processCheckTypesAgenda();
void processDefinitions();
Proposition* buildExistsProposition(Cons* tree);
boolean topLevelExistsPropositionP(Proposition* proposition);
Vector* collectSkolemizedExistsVariables(Proposition* proposition);
boolean helpCollectSkolemizedExistsVariablesP(Proposition* proposition, List* result);
Proposition* buildForallProposition(Cons* tree);
void verifyForallPropositions(Proposition* proposition);
Object* maybeSubstituteSurrogateArgument(Object* arg1, Object* arg2);
Proposition* createImpliesProposition(Object* tail, Object* head);
Proposition* buildImpliesProposition(Cons* tree);
Proposition* findDuplicateFunctionProposition(Proposition* proposition);
Surrogate* unwrapWrappedType(Surrogate* type);
Proposition* beginCreatingFunctionProposition(GeneralizedSymbol* surrogate, Cons* inputarguments);
Proposition* finishCreatingFunctionProposition(Proposition* proposition);
Proposition* findOrCreateFunctionProposition(GeneralizedSymbol* predicate, Cons* inputarguments);
Proposition* createFunctionProposition(GeneralizedSymbol* predicate, Cons* inputarguments);
Object* evaluateFunctionTerm(Cons* tree);
boolean extensionalIndividualP(Object* individual);
boolean functionWithDefinedValueP(Proposition* proposition);
Cons* normalizeSetofArguments(Cons* args);
Skolem* createEnumeratedSet(List* set);
Skolem* createLogicalList(List* list);
boolean logicalCollectionP(Object* self);
boolean functionOutputSkolemP(Object* self);
boolean skolemDefinedByOperatorP(Object* self, Surrogate* operatoR);
Skolem* getSkolemAndValueTerms(Proposition* proposition, Object*& _Return1);
boolean enumeratedSetP(Object* self);
boolean enumeratedListP(Object* self);
Object* canonicalizePropositionTree(Object* tree);
Proposition* updateEquivalenceProposition(Proposition* proposition, Keyword* updatemode);
Proposition* skolemizeExistsProposition(Proposition* existsproposition);
Cons* helpUpdateTopLevelProposition(Proposition* proposition, Keyword* updatemode);
Keyword* invertUpdateMode(Keyword* updatemode);
Keyword* defaultifyUpdateMode(Keyword* updatemode);
Cons* updateTopLevelProposition(Object* tree, Keyword* updatemode);
Object* standardizePropositionTree(Object* tree);
Cons* updateProposition(Object* tree, Keyword* updatemode);
Object* buildTopLevelTerm(Object* tree);
Object* conceiveTerm(Object* tree);
Object* conceiveSentence(Object* tree);
Object* conceiveFormula(Object* tree);
Object* smartUpdateProposition(Object* tree, Keyword* updatemode);
Object* asserT(Object* proposition);
Object* presume(Object* proposition);
Object* retract(Object* proposition);
Object* deny(Object* proposition);
Object* conceive(Object* formula);
Object* unassert(Object* proposition);
void unassertProposition(Proposition* self);
boolean deletedPropositionP(Proposition* self);
Proposition* destroyProposition(Proposition* proposition);
void destroyRedundantProposition(Proposition* proposition);
void destroyLogicInstance(Object* self);
void destroyTerm(LogicObject* self);
void destroyInstance(Object* self);
void destroyObject(Object* self);
Object* destroy(Object* objectspec);
boolean relationInModuleP(NamedDescription* self);
void introduceModule(Module* module);
void clearLogicModuleHook(Module* module);
void clearInstances(Cons* name);
void clearInstancesEvaluatorWrapper(Cons* arguments);
void doClearInstances(Module* module);
void destroyLogicContextHook(Context* self);
void clearCaches();
void resetPowerloom();
boolean consLessThanP(Cons* o1, Cons* o2);
boolean stringTermLessP(const char* s1, const char* s2);
boolean safeStringTermLessP(const char* s1, const char* s2);
boolean safeQuantityLessP(Quantity* q1, Object* o2);
boolean safeQuantityGreaterEqualP(Quantity* q1, Object* o2);
boolean objectNameLessThanP(LogicObject* o1, LogicObject* o2);
boolean moduleNameLessThanP(Context* m1, Context* m2);
boolean propositionLessThanP(Proposition* p1, Proposition* p2);
const char* propositionHeadSortString(Proposition* p);
const char* objectSortString(Object* o);
boolean logicFormLessP(Object* o1, Object* o2);
void helpStartupPropositions1();
void helpStartupPropositions2();
void helpStartupPropositions3();
void helpStartupPropositions4();
void helpStartupPropositions5();
void helpStartupPropositions6();
void helpStartupPropositions7();
void helpStartupPropositions8();
void helpStartupPropositions9();
void helpStartupPropositions10();
void helpStartupPropositions11();
void helpStartupPropositions12();
void helpStartupPropositions13();
void startupPropositions();

// Auxiliary global declarations:
extern Symbol* SYM_PROPOSITIONS_LOGIC_PROPOSITIONS_INDEX;
extern Symbol* SYM_PROPOSITIONS_LOGIC_INSTANCES_INDEX;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_BACKLINKS_INDEX;
extern Symbol* SYM_PROPOSITIONS_LOGIC_DEPENDENT_PROPOSITIONS_LIST;
extern Symbol* SYM_PROPOSITIONS_LOGIC_DEPENDENT_ISA_PROPOSITIONS_LIST;
extern Symbol* SYM_PROPOSITIONS_LOGIC_PREDICATE_PROPOSITIONS_TABLE;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT;
extern Symbol* SYM_PROPOSITIONS_STELLA_BADp;
extern Symbol* SYM_PROPOSITIONS_LOGIC_VARIABLE_VALUE_INVERSE;
extern Symbol* SYM_PROPOSITIONS_STELLA_SURROGATE_VALUE_INVERSE;
extern Symbol* SYM_PROPOSITIONS_LOGIC_OBJECT_STRINGIFIED_SOURCE;
extern Symbol* SYM_PROPOSITIONS_LOGIC_OBJECT_ORIGINATED_PROPOSITIONS;
extern Surrogate* SGT_PROPOSITIONS_STELLA_CS_VALUE;
extern Symbol* SYM_PROPOSITIONS_STELLA_DELETED_OBJECTp;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_LOGIC_THING;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_SKOLEM;
extern Symbol* SYM_PROPOSITIONS_LOGIC_SKOLEM_TYPE;
extern Symbol* SYM_PROPOSITIONS_LOGIC_SKOLEM_NAME;
extern Symbol* SYM_PROPOSITIONS_LOGIC_VARIABLE_VALUE;
extern Symbol* SYM_PROPOSITIONS_LOGIC_DEFINING_PROPOSITION;
extern Symbol* SYM_PROPOSITIONS_LOGIC_BOUND_TO_OFFSET;
extern Symbol* SYM_PROPOSITIONS_LOGIC_OBJECT_VECTOR;
extern Symbol* SYM_PROPOSITIONS_LOGIC_ARGUMENTS_VECTOR;
extern Symbol* SYM_PROPOSITIONS_LOGIC_VARIABLES_VECTOR;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_FORWARD_CHAINING_INDEX;
extern Symbol* SYM_PROPOSITIONS_LOGIC_FORWARD_GOAL;
extern Symbol* SYM_PROPOSITIONS_LOGIC_MASTER_RULE;
extern Symbol* SYM_PROPOSITIONS_LOGIC_IO_VARIABLES;
extern Symbol* SYM_PROPOSITIONS_LOGIC_QUERY_BODY;
extern Symbol* SYM_PROPOSITIONS_LOGIC_INPUT_BINDINGS;
extern Symbol* SYM_PROPOSITIONS_LOGIC_CACHE_ID;
extern Symbol* SYM_PROPOSITIONS_LOGIC_CONSEQUENT;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_DESCRIPTION;
extern Symbol* SYM_PROPOSITIONS_LOGIC_NATIVE_RELATION;
extern Symbol* SYM_PROPOSITIONS_LOGIC_FORWARD_CHAINING_INDICES;
extern Symbol* SYM_PROPOSITIONS_LOGIC_DEFERRED_CONTRAPOSITIVESp;
extern Symbol* SYM_PROPOSITIONS_LOGIC_PROPOSITION;
extern Symbol* SYM_PROPOSITIONS_LOGIC_INTERNAL_VARIABLES;
extern Symbol* SYM_PROPOSITIONS_LOGIC_QUERY_PATTERNS;
extern Symbol* SYM_PROPOSITIONS_LOGIC_RELATIVE_COMPLEMENT;
extern Symbol* SYM_PROPOSITIONS_LOGIC_COMPLEMENT_DESCRIPTION;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION;
extern Symbol* SYM_PROPOSITIONS_LOGIC_NATIVE_RELATION_BACK_POINTER;
extern Symbol* SYM_PROPOSITIONS_LOGIC_NATIVE_RELATION_SETTER;
extern Symbol* SYM_PROPOSITIONS_LOGIC_IO_VARIABLE_NAMES;
extern Symbol* SYM_PROPOSITIONS_LOGIC_IO_VARIABLE_TYPES;
extern Symbol* SYM_PROPOSITIONS_STELLA_EXTENSION;
extern Symbol* SYM_PROPOSITIONS_LOGIC_PARTIAL_MATCH_SCORE;
extern Symbol* SYM_PROPOSITIONS_LOGIC_SET_OF_SUPPORT;
extern Symbol* SYM_PROPOSITIONS_LOGIC_TIMESTAMP;
extern Keyword* KWD_PROPOSITIONS_UNKNOWN;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_TRUTH_VALUE;
extern Symbol* SYM_PROPOSITIONS_LOGIC_POLARITY;
extern Symbol* SYM_PROPOSITIONS_LOGIC_STRENGTH;
extern Symbol* SYM_PROPOSITIONS_LOGIC_MATCH_SCORE;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_PARTIAL_SUPPORT;
extern Symbol* SYM_PROPOSITIONS_LOGIC_FACT;
extern Symbol* SYM_PROPOSITIONS_LOGIC_AXIOM;
extern Symbol* SYM_PROPOSITIONS_LOGIC_SCORE;
extern Symbol* SYM_PROPOSITIONS_LOGIC_ID;
extern Symbol* SYM_PROPOSITIONS_LOGIC_ARGUMENT_SCORES;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_PROPOSITION;
extern Symbol* SYM_PROPOSITIONS_LOGIC_VARIABLE_TYPEp;
extern Symbol* SYM_PROPOSITIONS_LOGIC_SATELLITE_PROPOSITIONS;
extern Symbol* SYM_PROPOSITIONS_LOGIC_UNFASTENEDp;
extern Symbol* SYM_PROPOSITIONS_LOGIC_WEIGHT_DELTA;
extern Symbol* SYM_PROPOSITIONS_LOGIC_SUPPORT;
extern Symbol* SYM_PROPOSITIONS_LOGIC_KIND;
extern Symbol* SYM_PROPOSITIONS_LOGIC_TRUTH_VALUE;
extern Symbol* SYM_PROPOSITIONS_STELLA_ARGUMENTS;
extern Symbol* SYM_PROPOSITIONS_STELLA_OPERATOR;
extern Symbol* SYM_PROPOSITIONS_LOGIC_RELATIONREF;
extern Symbol* SYM_PROPOSITIONS_LOGIC_DEPENDENT_PROPOSITIONS;
extern Symbol* SYM_PROPOSITIONS_LOGIC_PROPOSITION_ORIGINATED_PROPOSITIONS;
extern Symbol* SYM_PROPOSITIONS_LOGIC_PROPOSITION_STRINGIFIED_SOURCE;
extern Symbol* SYM_PROPOSITIONS_LOGIC_PROPOSITION_NEURAL_NETWORK;
extern Symbol* SYM_PROPOSITIONS_LOGIC_NEURAL_NETWORK;
extern Symbol* SYM_PROPOSITIONS_LOGIC_NEURAL_NET;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_QUANTITY_LOGIC_WRAPPER;
extern Symbol* SYM_PROPOSITIONS_STELLA_WRAPPER_VALUE;
extern Symbol* SYM_PROPOSITIONS_LOGIC_FUNCTION_TERM;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_INTEGER_LOGIC_WRAPPER;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_FLOAT_LOGIC_WRAPPER;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_STRING_LOGIC_WRAPPER;
extern Symbol* SYM_PROPOSITIONS_LOGIC_ENTITY_MAPPING;
extern Keyword* KWD_PROPOSITIONS_AND;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_AND;
extern Keyword* KWD_PROPOSITIONS_OR;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_OR;
extern Keyword* KWD_PROPOSITIONS_NOT;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_NOT;
extern Keyword* KWD_PROPOSITIONS_FORALL;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_FORALL;
extern Keyword* KWD_PROPOSITIONS_EXISTS;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_EXISTS;
extern Keyword* KWD_PROPOSITIONS_EQUIVALENT;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_EQUIVALENT;
extern Keyword* KWD_PROPOSITIONS_FAIL;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_FAIL;
extern Keyword* KWD_PROPOSITIONS_COLLECT_INTO;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_COLLECT_INTO;
extern Keyword* KWD_PROPOSITIONS_IMPLIES;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_SUBSET_OF;
extern Symbol* SYM_PROPOSITIONS_STELLA_FUNCTION;
extern Symbol* SYM_PROPOSITIONS_STELLA_PREDICATE;
extern Symbol* SYM_PROPOSITIONS_STELLA_ISA;
extern Symbol* SYM_PROPOSITIONS_LOGIC_DESCRIPTIVEp;
extern Symbol* SYM_PROPOSITIONS_STELLA_CODE_ONLYp;
extern Keyword* KWD_PROPOSITIONS_ERROR;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_EXCEPTION_RECORD;
extern Symbol* SYM_PROPOSITIONS_STELLA_CONTEXT;
extern Symbol* SYM_PROPOSITIONS_STELLA_MODULE;
extern Symbol* SYM_PROPOSITIONS_LOGIC_LOCALLY_CONCEIVED_PROPOSITIONS_INTERNAL;
extern Keyword* KWD_PROPOSITIONS_PAGING;
extern Keyword* KWD_PROPOSITIONS_CONTEXT_PROPOSITIONS;
extern Symbol* SYM_PROPOSITIONS_LOGIC_LOCALLY_CONCEIVED_INSTANCES_INTERNAL;
extern Keyword* KWD_PROPOSITIONS_CONTEXT_INSTANCES;
extern Keyword* KWD_PROPOSITIONS_UPDATE_PROPOSITION;
extern Keyword* KWD_PROPOSITIONS_EXECUTE_QUERY;
extern Symbol* SYM_PROPOSITIONS_LOGIC_BOTTOM;
extern Surrogate* SGT_PROPOSITIONS_STELLA_LITERAL;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_F_LOGICAL_SUBTYPE_OF_LITERALp_MEMO_TABLE_000;
extern Surrogate* SGT_PROPOSITIONS_STELLA_CLASS;
extern Surrogate* SGT_PROPOSITIONS_STELLA_LITERAL_WRAPPER;
extern Surrogate* SGT_PROPOSITIONS_STELLA_BOOLEAN;
extern Surrogate* SGT_PROPOSITIONS_STELLA_BOOLEAN_WRAPPER;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_VARIABLE_ARITY;
extern Surrogate* SGT_PROPOSITIONS_STELLA_COLLECTION;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_RELATION_COMPUTATION;
extern Surrogate* SGT_PROPOSITIONS_STELLA_THING;
extern Keyword* KWD_PROPOSITIONS_EXTENSIONAL_ASSERTION;
extern Keyword* KWD_PROPOSITIONS_DESCRIPTION;
extern Keyword* KWD_PROPOSITIONS_DEVELOPMENT;
extern Keyword* KWD_PROPOSITIONS_WARNING;
extern Keyword* KWD_PROPOSITIONS_RETRACT_TRUE;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_UPDATE_PROPOSITION_DEMON;
extern Symbol* SYM_PROPOSITIONS_LOGIC_OBJECT_STORE;
extern Keyword* KWD_PROPOSITIONS_FUNCTION;
extern Keyword* KWD_PROPOSITIONS_ISA;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_TRUE_DEMON;
extern Keyword* KWD_PROPOSITIONS_PREDICATE;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_FALSE_DEMON;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_UNKNOWN_DEMON;
extern Symbol* SYM_PROPOSITIONS_LOGIC_MASTER_PROPOSITION;
extern Keyword* KWD_PROPOSITIONS_ASSERT_TRUE;
extern Keyword* KWD_PROPOSITIONS_PRESUME_TRUE;
extern Keyword* KWD_PROPOSITIONS_ASSERT_FALSE;
extern Keyword* KWD_PROPOSITIONS_PRESUME_FALSE;
extern Keyword* KWD_PROPOSITIONS_RETRACT_FALSE;
extern Keyword* KWD_PROPOSITIONS_ASSERT;
extern Keyword* KWD_PROPOSITIONS_RETRACT_INCONSISTENT;
extern Keyword* KWD_PROPOSITIONS_RETRACT;
extern Keyword* KWD_PROPOSITIONS_CONCEIVE;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_HIDDEN_RELATION;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_HIDDEN_INSTANCE;
extern Keyword* KWD_PROPOSITIONS_MODULE;
extern Surrogate* SGT_PROPOSITIONS_STELLA_MODULE;
extern Keyword* KWD_PROPOSITIONS_LOCALp;
extern Keyword* KWD_PROPOSITIONS_KB_UPDATE;
extern Keyword* KWD_PROPOSITIONS_META_KB_UPDATE;
extern Surrogate* SGT_PROPOSITIONS_STELLA_STORAGE_SLOT;
extern Surrogate* SGT_PROPOSITIONS_STELLA_SURROGATE;
extern Surrogate* SGT_PROPOSITIONS_STELLA_RELATION;
extern Symbol* SYM_PROPOSITIONS_LOGIC_DESCRIPTION;
extern Symbol* SYM_PROPOSITIONS_LOGIC_EQUIVALENT_VALUE;
extern Keyword* KWD_PROPOSITIONS_TRUE;
extern Keyword* KWD_PROPOSITIONS_STRICT;
extern Keyword* KWD_PROPOSITIONS_FALSE;
extern Keyword* KWD_PROPOSITIONS_DEFAULT;
extern Keyword* KWD_PROPOSITIONS_INCONSISTENT;
extern Keyword* KWD_PROPOSITIONS_LOOKUP_ASSERTIONS;
extern Keyword* KWD_PROPOSITIONS_FORWARD;
extern Symbol* SYM_PROPOSITIONS_LOGIC_META_INFERENCE_CACHE;
extern Symbol* SYM_PROPOSITIONS_LOGIC_TRUTH_MAINTAINED_INFERENCE_CACHE;
extern Symbol* SYM_PROPOSITIONS_LOGIC_CLASH_EXCEPTIONS;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_INCOHERENT;
extern Symbol* SYM_PROPOSITIONS_LOGIC_IOTAp;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_CONCEPT;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_RELATION;
extern Surrogate* SGT_PROPOSITIONS_STELLA_SET;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_SET;
extern Surrogate* SGT_PROPOSITIONS_STELLA_SLOT;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_FUNCTION;
extern Keyword* KWD_PROPOSITIONS_META;
extern Keyword* KWD_PROPOSITIONS_JUST_IN_TIME;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_INTERVAL_CACHE;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_ge;
extern Symbol* SYM_PROPOSITIONS_LOGIC_CONFLICTING_DEFAULT_VALUES;
extern Keyword* KWD_PROPOSITIONS_CONSTANT;
extern Surrogate* SGT_PROPOSITIONS_STELLA_TRUE;
extern Surrogate* SGT_PROPOSITIONS_STELLA_FALSE;
extern Surrogate* SGT_PROPOSITIONS_STELLA_CONS;
extern Symbol* SYM_PROPOSITIONS_LOGIC_SETOFALL;
extern Symbol* SYM_PROPOSITIONS_LOGIC_THE_ONLY;
extern Symbol* SYM_PROPOSITIONS_LOGIC_KAPPA;
extern Symbol* SYM_PROPOSITIONS_LOGIC_CREATE;
extern Keyword* KWD_PROPOSITIONS_INTENSIONAL_ASSERTION;
extern Symbol* SYM_PROPOSITIONS_STELLA_p;
extern Symbol* SYM_PROPOSITIONS_STELLA_CLASS_EXTENSION;
extern Symbol* SYM_PROPOSITIONS_LOGIC_TRANSFER_LOGIC_INFORMATION_FROM_RELATION_HOOK;
extern Symbol* SYM_PROPOSITIONS_LOGIC_SUBRELATION_LINKp;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_HOLDS;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_MEMBER_OF;
extern Keyword* KWD_PROPOSITIONS_DISABLED;
extern Symbol* SYM_PROPOSITIONS_LOGIC_ANNOTATIONS;
extern Surrogate* SGT_PROPOSITIONS_STELLA_STRING_WRAPPER;
extern Symbol* SYM_PROPOSITIONS_LOGIC_CONSTANT;
extern Symbol* SYM_PROPOSITIONS_STELLA_TRUE;
extern Symbol* SYM_PROPOSITIONS_STELLA_FALSE;
extern Surrogate* SGT_PROPOSITIONS_STELLA_SYMBOL;
extern Symbol* SYM_PROPOSITIONS_STELLA_e;
extern Symbol* SYM_PROPOSITIONS_STELLA_AND;
extern Symbol* SYM_PROPOSITIONS_STELLA_OR;
extern Symbol* SYM_PROPOSITIONS_STELLA_NOT;
extern Symbol* SYM_PROPOSITIONS_PL_KERNEL_KB_MEMBER_OF;
extern Symbol* SYM_PROPOSITIONS_LOGIC_IMPLIES;
extern Symbol* SYM_PROPOSITIONS_PL_KERNEL_KB_SUBSET_OF;
extern Symbol* SYM_PROPOSITIONS_STELLA_EXISTS;
extern Symbol* SYM_PROPOSITIONS_STELLA_FORALL;
extern Symbol* SYM_PROPOSITIONS_LOGIC_FAIL;
extern Symbol* SYM_PROPOSITIONS_STELLA_COLLECT_INTO;
extern Symbol* SYM_PROPOSITIONS_LOGIC_ABOUT;
extern Surrogate* SGT_PROPOSITIONS_STELLA_GENERALIZED_SYMBOL;
extern Keyword* KWD_PROPOSITIONS_DIRECTION;
extern Symbol* SYM_PROPOSITIONS_LOGIC_FORWARD_ONLYp;
extern Symbol* SYM_PROPOSITIONS_LOGIC_BACKWARD_ONLYp;
extern Keyword* KWD_PROPOSITIONS_WEIGHT;
extern Symbol* SYM_PROPOSITIONS_LOGIC_WEIGHT;
extern Keyword* KWD_PROPOSITIONS_SCORE;
extern Keyword* KWD_PROPOSITIONS_CONFIDENCE_LEVEL;
extern Symbol* SYM_PROPOSITIONS_PL_KERNEL_KB_SETOF;
extern Symbol* SYM_PROPOSITIONS_PL_KERNEL_KB_LISTOF;
extern Symbol* SYM_PROPOSITIONS_LOGIC_EQUIVALENT;
extern Symbol* SYM_PROPOSITIONS_PL_KERNEL_KB_HOLDS;
extern Surrogate* SGT_PROPOSITIONS_STELLA_TABLE;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_POLYMORPHIC;
extern Symbol* SYM_PROPOSITIONS_PL_KERNEL_KB_VALUE;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_VALUE;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_QUANTITY;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_DATE;
extern Surrogate* SGT_PROPOSITIONS_STELLA_FLOAT;
extern Surrogate* SGT_PROPOSITIONS_STELLA_INTEGER;
extern Keyword* KWD_PROPOSITIONS_AUTOMATICALLY_FIX_TYPE_VIOLATIONS;
extern Keyword* KWD_PROPOSITIONS_POST_TYPE_VIOLATIONS;
extern Keyword* KWD_PROPOSITIONS_IGNORE_TYPE_VIOLATIONS;
extern Keyword* KWD_PROPOSITIONS_REPORT_TYPE_VIOLATIONS;
extern Keyword* KWD_PROPOSITIONS_SIGNAL_TYPE_VIOLATIONS;
extern Symbol* SYM_PROPOSITIONS_LOGIC_ASSERTED_BY_TYPE_CHECKERp;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_CHECK_TYPES_RECORD;
extern Symbol* SYM_PROPOSITIONS_LOGIC_PARENT_PROPOSITION;
extern Symbol* SYM_PROPOSITIONS_LOGIC_PARENT_DESCRIPTION;
extern Keyword* KWD_PROPOSITIONS_MEDIUM;
extern Keyword* KWD_PROPOSITIONS_REALISTIC;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_SETOF;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_TOTAL;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_LISTOF;
extern Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_LIST;
extern Symbol* SYM_PROPOSITIONS_LOGIC_LAMBDA;
extern Symbol* SYM_PROPOSITIONS_LOGIC_BAGOF;
extern Symbol* SYM_PROPOSITIONS_STELLA_ASSERT;
extern Keyword* KWD_PROPOSITIONS_CPP;
extern Keyword* KWD_PROPOSITIONS_DELETED;
extern Symbol* SYM_PROPOSITIONS_LOGIC_INTRODUCE_MODULE;
extern Surrogate* SGT_PROPOSITIONS_STELLA_KEY_VALUE_LIST;
extern Symbol* SYM_PROPOSITIONS_LOGIC_CLEAR_LOGIC_MODULE_HOOK;
extern Symbol* SYM_PROPOSITIONS_LOGIC_MONOTONICp;
extern Surrogate* SGT_PROPOSITIONS_STELLA_WORLD;
extern Symbol* SYM_PROPOSITIONS_LOGIC_DESTROY_LOGIC_CONTEXT_HOOK;
extern Symbol* SYM_PROPOSITIONS_STELLA_CLEARABLEp;
extern Symbol* SYM_PROPOSITIONS_STELLA_PROTECT_SURROGATESp;
extern Keyword* KWD_PROPOSITIONS_PREORDER;
extern Surrogate* SGT_PROPOSITIONS_STELLA_MUTABLE_STRING_WRAPPER;
extern Surrogate* SGT_PROPOSITIONS_STELLA_CONTEXT;
extern Surrogate* SGT_PROPOSITIONS_LOGIC_COMPUTED_PROCEDURE;
extern Surrogate* SGT_PROPOSITIONS_STELLA_NUMBER_WRAPPER;
extern Symbol* SYM_PROPOSITIONS_LOGIC_STARTUP_PROPOSITIONS;
extern Symbol* SYM_PROPOSITIONS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
