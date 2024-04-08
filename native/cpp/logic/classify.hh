//  -*- Mode: C++ -*-

// classify.hh

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
class MarkerTable : public StandardObject {
// Used to record (mark) a set of objects.
// Can be optimized for testing only, or also for recall.
public:
  HashTable* testTable;
  List* recallTable;
  boolean supportsRecallP;
public:
  virtual Surrogate* primaryType();
  virtual ListIterator* recallMarkedObjects();
  virtual boolean testMarkerP(Object* object);
  virtual void setMarker(Object* object);
};

class ClassificationCache : public StandardObject {
// Records various kinds of data about a description
// during a classification session.
public:
  List* inferableDirectSubdescriptions;
  int cacheUpclassificationTimestamp;
  int cacheDownclassificationTimestamp;
  int introductionTimestamp;
public:
  virtual Surrogate* primaryType();
};

class ClassificationSession : public StandardObject {
public:
  World* classificationWorld;
  HashTable* classificationCacheTable;
  int classificationTimeclock;
  List* introductionTimestampStack;
  boolean everythingClassifiedP;
  LogicObject* lastCacheTableKey;
  ClassificationCache* lastCacheTableValue;
public:
  virtual Surrogate* primaryType();
};


// Global declarations:
extern DECLARE_STELLA_SPECIAL(oSPECIALMARKERTABLEo, MarkerTable* );
extern DECLARE_STELLA_SPECIAL(oFINDSUPERSANDSUBSDESCRIPTIONo, Description* );
extern DECLARE_STELLA_SPECIAL(oCLASSIFICATIONSESSIONo, ClassificationSession* );
extern boolean oCACHE_INFERABLE_SUBCOLLECTIONSpo;
extern DECLARE_STELLA_SPECIAL(oCLASSIFY_FROM_NON_INFERABLE_PARENTS_ONLYpo, boolean );

// Function signatures:
void bumpInferableTimestamp();
void helpCollectIntensionalParents(Description* description, Proposition* proposition, List* collection);
List* allIntensionalParents(Description* self);
boolean inferableThroughBySomeDescendantP(NamedDescription* self, LogicObject* throughchild, Cons* alreadyvisitedlist);
boolean inferableWithCycleCheckP(Description* self, Cons* alreadyvisitedlist);
boolean inferableP(Description* self);
boolean nonInferableP(Description* self);
MarkerTable* newMarkerTable();
Object* accessMarkerTableSlotValue(MarkerTable* self, Symbol* slotname, Object* value, boolean setvalueP);
MarkerTable* createMarkerStorage(boolean supportrecallP);
boolean testSpecialMarkerTableP(Object* self);
Cons* allNamedDirectSuperdescriptions(Description* self, boolean removeequivalentsP);
Cons* allNamedDirectSubdescriptions(Description* self);
void addIsaLink(LogicObject* instance, Description* superdescription);
void addSubsumptionLink(Description* subdescription, Description* superdescription);
Cons* mostSpecificCollections(Cons* descriptions);
Cons* mostGeneralCollections(Cons* descriptions);
boolean namedCollectionP(LogicObject* self);
Cons* mostSpecificNamedCollections(Cons* descriptions);
Cons* mostSpecificNamedDescriptions(Cons* descriptions);
ClassificationCache* newClassificationCache();
Object* accessClassificationCacheSlotValue(ClassificationCache* self, Symbol* slotname, Object* value, boolean setvalueP);
ClassificationSession* newClassificationSession();
Object* accessClassificationSessionSlotValue(ClassificationSession* self, Symbol* slotname, Object* value, boolean setvalueP);
World* getClassificationWorld();
ClassificationSession* getClassificationSession(Keyword* instanceordescription);
ClassificationCache* getClassificationCache(Object* self);
const char* toggleInferableDirectSubcollectionsCaching();
List* allInferableDirectSubcollections(LogicObject* self);
void flushInferableDirectSubdescriptionsCache(Proposition* impliesproposition);
int currentClassificationTime();
int bumpClassificationTimeclock();
void introduceIntoClassificationSession(Description* self);
int youngestIntroductionTimestamp();
int upclassificationTimestamp(Object* self);
int downclassificationTimestamp(LogicObject* self);
void refreshUpclassificationTimestamp(Object* self);
void refreshDownclassificationTimestamp(LogicObject* self);
void flushClassificationSessions();
boolean upclassifiedP(Object* self);
boolean upclassifiedLaterThanP(LogicObject* self, LogicObject* other);
boolean downclassifiedP(LogicObject* self);
void markUnmarkedSuperrelations(Description* description, MarkerTable* selfisbelowtable);
boolean applySubsumptionTestP(cpp_function_code subsumptiontest, LogicObject* self, LogicObject* super);
boolean helpCollectParentsBelowP(LogicObject* self, Description* super, List* newparentdescriptions, MarkerTable* alreadyvisitedtable, MarkerTable* selfisbelowtable, cpp_function_code subsumptiontest);
void collectSubsumingParentsBelow(LogicObject* self, Description* super, List* newparentdescriptions, MarkerTable* alreadyvisitedtable, MarkerTable* selfisbelowtable, cpp_function_code subsumptiontest);
Iterator* allAncestorsOfParents(Cons* supers);
Iterator* allAncestorCollections(Object* self, Keyword* instanceordescription);
void helpUpclassifyOneEntity(LogicObject* self, Keyword* instanceordescription);
void upclassifyOneInstance(LogicObject* self);
void upclassifyOneDescription(LogicObject* self);
void helpDownclassifyOneDescription(LogicObject* node, LogicObject* self, Cons* necessaryancestors, MarkerTable* alreadyvisitedtable);
LogicObject* collectionWithFewestChildren(Cons* collections);
LogicObject* chooseBestDownclassifiedParent(Cons* parents);
void downclassifyOneDescription(LogicObject* self);
void evaporateVirgin(Description* self);
Cons* findDirectSupersAndSubs(Description* self, boolean onlysupersP, Cons*& _Return1, Cons*& _Return2);
Cons* findDirectSupersOfInstance(Object* self);
void upclassifyNamedDescriptions(Module* module, boolean localP);
void classifyRelations(Cons* options);
void classifyRelationsEvaluatorWrapper(Cons* arguments);
Cons* listUnclassifiedRelations(Cons* options);
Cons* listUnclassifiedRelationsEvaluatorWrapper(Cons* arguments);
void upclassifyInstances(Module* module, boolean localP);
void classifyInstances(Cons* options);
void classifyInstancesEvaluatorWrapper(Cons* arguments);
Cons* listUnclassifiedInstances(Cons* options);
Cons* listUnclassifiedInstancesEvaluatorWrapper(Cons* arguments);
void upclassifyAllDescriptions();
void upclassifyAllInstances();
Cons* allEquivalentCollections(LogicObject* self, boolean reflexiveP);
Cons* allCycles(Module* module, boolean localP);
void helpStartupClassify1();
void helpStartupClassify2();
void startupClassify();

// Auxiliary global declarations:
extern Keyword* KWD_CLASSIFY_IMPLIES_PROPOSITION_UPDATE;
extern Keyword* KWD_CLASSIFY_PREDICATE;
extern Keyword* KWD_CLASSIFY_FUNCTION;
extern Keyword* KWD_CLASSIFY_ISA;
extern Keyword* KWD_CLASSIFY_AND;
extern Keyword* KWD_CLASSIFY_EXISTS;
extern Surrogate* SGT_CLASSIFY_LOGIC_NAMED_DESCRIPTION;
extern Keyword* KWD_CLASSIFY_BACKWARD;
extern Symbol* SYM_CLASSIFY_LOGIC_FORWARD_ONLYp;
extern Surrogate* SGT_CLASSIFY_LOGIC_DESCRIPTION;
extern Surrogate* SGT_CLASSIFY_STELLA_THING;
extern Surrogate* SGT_CLASSIFY_LOGIC_F_INFERABLE_WITH_CYCLE_CHECKp_MEMO_TABLE_000;
extern Surrogate* SGT_CLASSIFY_LOGIC_MARKER_TABLE;
extern Symbol* SYM_CLASSIFY_LOGIC_TEST_TABLE;
extern Symbol* SYM_CLASSIFY_LOGIC_RECALL_TABLE;
extern Symbol* SYM_CLASSIFY_LOGIC_SUPPORTS_RECALLp;
extern Symbol* SYM_CLASSIFY_LOGIC_SUBSUMPTION_LINKp;
extern Keyword* KWD_CLASSIFY_CLASSIFIER_INFERENCES;
extern Surrogate* SGT_CLASSIFY_LOGIC_CLASSIFICATION_CACHE;
extern Symbol* SYM_CLASSIFY_LOGIC_INFERABLE_DIRECT_SUBDESCRIPTIONS;
extern Symbol* SYM_CLASSIFY_LOGIC_CACHE_UPCLASSIFICATION_TIMESTAMP;
extern Symbol* SYM_CLASSIFY_LOGIC_CACHE_DOWNCLASSIFICATION_TIMESTAMP;
extern Symbol* SYM_CLASSIFY_LOGIC_INTRODUCTION_TIMESTAMP;
extern Surrogate* SGT_CLASSIFY_LOGIC_CLASSIFICATION_SESSION;
extern Symbol* SYM_CLASSIFY_LOGIC_CLASSIFICATION_WORLD;
extern Symbol* SYM_CLASSIFY_LOGIC_CLASSIFICATION_CACHE_TABLE;
extern Symbol* SYM_CLASSIFY_LOGIC_CLASSIFICATION_TIMECLOCK;
extern Symbol* SYM_CLASSIFY_LOGIC_INTRODUCTION_TIMESTAMP_STACK;
extern Symbol* SYM_CLASSIFY_LOGIC_EVERYTHING_CLASSIFIEDp;
extern Symbol* SYM_CLASSIFY_LOGIC_LAST_CACHE_TABLE_KEY;
extern Symbol* SYM_CLASSIFY_LOGIC_LAST_CACHE_TABLE_VALUE;
extern Keyword* KWD_CLASSIFY_DESCRIPTION;
extern Keyword* KWD_CLASSIFY_META;
extern Keyword* KWD_CLASSIFY_INSTANCE;
extern Keyword* KWD_CLASSIFY_TMS;
extern Symbol* SYM_CLASSIFY_LOGIC_CLASSIFICATION_SESSION;
extern Symbol* SYM_CLASSIFY_LOGIC_META_INFERENCE_CACHE;
extern Keyword* KWD_CLASSIFY_JUST_IN_TIME;
extern Keyword* KWD_CLASSIFY_CLASSIFIER;
extern Keyword* KWD_CLASSIFY_CLASSIFIER_PROFILE;
extern Keyword* KWD_CLASSIFY_UPCLASSIFY;
extern Keyword* KWD_CLASSIFY_DOWNCLASSIFY;
extern Symbol* SYM_CLASSIFY_LOGIC_SUBRELATION_LINKp;
extern Keyword* KWD_CLASSIFY_ASSERT_TRUE;
extern Keyword* KWD_CLASSIFY_MODULE;
extern Keyword* KWD_CLASSIFY_LOCALp;
extern Surrogate* SGT_CLASSIFY_STELLA_MODULE;
extern Surrogate* SGT_CLASSIFY_STELLA_BOOLEAN;
extern Symbol* SYM_CLASSIFY_LOGIC_STARTUP_CLASSIFY;
extern Symbol* SYM_CLASSIFY_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
