//  -*- Mode: C++ -*-

// classes.hh

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
class AllClassSlotsIterator : public Iterator {
public:
  Cons* iteratorConsList;
  Object* iteratorObject;
public:
  virtual boolean nextP();
  virtual Surrogate* primaryType();
};


// Global declarations:
extern DECLARE_STELLA_SPECIAL(oWARNIFREDEFINEpo, boolean );
extern List* oUNFINALIZED_CLASSESo;
extern boolean oNEWLY_UNFINALIZED_CLASSESpo;
extern List* oCLASSES_WITH_UNRESOLVED_CHILDREN_REFERENCESo;
extern int oSYMBOL_SLOT_OFFSET_COUNTERo;
extern int oSLOT_CACHE_SIZEo;
extern TaxonomyGraph* oCLASS_TAXONOMY_GRAPHo;

// Function signatures:
const char* className(Class* clasS);
Surrogate* classSurrogate(Class* clasS);
Symbol* classSymbol(Class* clasS);
Class* stringLookupClass(const char* name);
Class* lookupClassByQualifiedName(const char* qualifiedname);
Class* typeToClass(Surrogate* type);
Class* stringGetStellaClass(const char* className, boolean errorP);
boolean bindToSurrogateP(Object* self, const char* name, boolean clipoldvalueP, boolean askforpermissionP, Object*& _Return1, Surrogate*& _Return2);
Symbol* shadowSymbol(const char* name);
Surrogate* shadowSurrogate(const char* name);
boolean shadowedSymbolP(GeneralizedSymbol* symbol);
cpp_function_code getConstructor(Class* clasS, boolean warnP);
Object* createObject(Surrogate* type, int initialValuePairs, ...);
Class* defineStellaClass(Surrogate* name, List* supers, List* slots, KeywordKeyValueList* options);
Slot* defineStellaSlot(Symbol* name, Surrogate* owner, Surrogate* basetype, Cons* typespecifier, KeywordKeyValueList* options);
void incorporateClassOptions(Class* clasS, KeywordKeyValueList* options);
boolean inlineMethodP(Slot* slot);
void transferExternalSlotToNewClass(Slot* externalslot, Class* newclass);
void transferDemonsFromOldclass(Class* oldclass, Class* newclass);
void undefineOldClass(Class* oldclass, Class* newclass);
void destroyClassAndSubclasses(Class* self);
void insertPrimitiveSuper(Surrogate* newsuper, List* supers);
void collectMostSpecificPrimitiveSupers(Class* clasS, List* supers);
List* mostSpecificPrimitiveSupers(Class* clasS);
List* classNativeSupers(Class* clasS);
void rememberUnfinalizedClass(Class* clasS, boolean forceP);
void forgetUnfinalizedClass(Class* clasS);
void finalizeClasses();
void resolveChildrenReferences();
void finalizeSlots();
void cleanupUnfinalizedClasses();
void finalizeClassesAndSlots();
void activateClass(Class* clasS);
void addPrimaryType(Class* clasS);
void finalizeOneClass(Class* clasS);
boolean finalizeClass(Class* clasS);
boolean helpFinalizeClass(Class* clasS, Surrogate* finalizedparent);
void unfinalizeClassAndSubclasses(Class* clasS);
Slot* attachSlotToOwner(Slot* newslot);
void computeSlotDirectEquivalent(Slot* self);
void checkConformanceOfSlotSignature(Slot* self);
Surrogate* collectionToActiveCollection(Surrogate* type);
void activateSlot(StorageSlot* self);
boolean multiValuedSlotWithDuplicatesP(Slot* self);
void computeSlotInverses(Slot* self);
void finalizeLocalSlot(Slot* self);
void finalizeClassSlots(Class* clasS);
void unfinalizeClassSlots(Class* clasS);
void helpUnfinalizeClassSlots(Class* clasS);
void addDirectSupersBackLinks(Class* clasS);
void addDirectSubsBackLinks(Class* clasS);
void removeDirectSupersBackLinks(Class* clasS);
void collectDirectSuperClasses(Class* clasS, List* parents);
void inheritSuperclasses(Class* clasS);
void uninheritSuperclasses(Class* clasS);
Class* twoArgumentLeastCommonSuperclass(Class* class1, Class* class2);
StandardObject* twoArgumentLeastCommonSupertype(StandardObject* type1, StandardObject* type2);
void inheritSlots(Class* clasS);
boolean localSlotP(Slot* slot, Class* clasS);
void uninheritSlots(Class* clasS);
void initializeSlotAndMethodCache(Class* clasS);
void registerSlotName(Slot* slot);
void unregisterSlotName(Slot* slot);
boolean registeredSlotNameP(Symbol* slotName);
boolean warnAboutSlotShadowedByAFunctionP(Slot* slot);
boolean warnAboutFunctionShadowingSlotsP(MethodSlot* function);
Slot* lookupSlot(Class* clasS, Symbol* slotName);
Slot* safeLookupSlot(Class* clasS, Symbol* slotName);
Slot* lookupVisibleSlot(Class* clasS, Object* slotName);
Slot* lookupLocalSlot(Class* clasS, Symbol* slotName);
void clearSlotAndMethodCache(Class* clasS);
void resizeSlotCaches(int size);
Slot* getSlot(StandardObject* self, Symbol* slotName);
Slot* lookupSlotAndClassByQualifiedName(const char* qualifiedname, Class*& _Return1);
Slot* lookupSlotByQualifiedName(const char* qualifiedname);
boolean conformingTypeSpecP(StandardObject* subTypeSpec, StandardObject* superTypeSpec);
boolean identicalSignaturesP(MethodSlot* method1, MethodSlot* method2);
void computeRequiredSlotNames(Class* clasS);
void freeRequiredSlotNames(Class* clasS);
AllClassSlotsIterator* newAllClassSlotsIterator();
Object* accessAllClassSlotsIteratorSlotValue(AllClassSlotsIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
void repairSlots();
void disconnectClasses();
boolean filterUnboundSurrogateP(Surrogate* self, AllPurposeIterator* iterator);
Iterator* unboundSurrogates(Module* module, boolean localP);
const char* nameToString(Object* name);
void printUnboundSurrogates(Cons* args);
void printUnboundSurrogatesEvaluatorWrapper(Cons* arguments);
GeneralizedSymbol* coerceToSymbol(Object* name);
void printUndefinedSuperClasses(Object* clasS);
List* collectBadSuperClasses(Surrogate* type, List* badones);
boolean rootClassP(Class* clasS);
void createClassTaxonomy();
boolean subclassOfP(Class* subclass, Class* superclass);
boolean fastSubclassOfP(Class* subclass, Class* superclass);
boolean subtypeOfP(Surrogate* subType, Surrogate* superType);
boolean isaP(Object* object, Surrogate* type);
boolean taxonomySubclassOfP(Class* subclass, Class* superclass);
boolean taxonomyIsaP(Object* object, Surrogate* type);
Surrogate* internSlotref(const char* classname, const char* slotname);
Surrogate* lookupSlotref(Surrogate* self, Symbol* slotname);
boolean slotrefP(Surrogate* self);
Slot* lookupSlotFromSlotref(Surrogate* slotref);
Surrogate* slotrefType(Surrogate* slotref);
void helpStartupClasses1();
void helpStartupClasses2();
void helpStartupClasses3();
void helpStartupClasses4();
void startupClasses();

// Auxiliary global declarations:
extern Surrogate* SGT_CLASSES_STELLA_CLASS;
extern Surrogate* SGT_CLASSES_STELLA_OBJECT;
extern Keyword* KWD_CLASSES_PUBLICp;
extern Keyword* KWD_CLASSES_PARAMETERS;
extern Symbol* SYM_CLASSES_STELLA_SLOT_TYPE_SPECIFIER;
extern Keyword* KWD_CLASSES_REQUIREDp;
extern Keyword* KWD_CLASSES_COMPONENTp;
extern Keyword* KWD_CLASSES_READ_ONLYp;
extern Keyword* KWD_CLASSES_ACTIVEp;
extern Symbol* SYM_CLASSES_STELLA_STORED_ACTIVEp;
extern Keyword* KWD_CLASSES_CONTEXT_SENSITIVEp;
extern Keyword* KWD_CLASSES_HARDWIREDp;
extern Keyword* KWD_CLASSES_ABSTRACTp;
extern Keyword* KWD_CLASSES_ALLOCATION;
extern Keyword* KWD_CLASSES_CLASS;
extern Symbol* SYM_CLASSES_STELLA_SLOT_ALLOCATION;
extern Keyword* KWD_CLASSES_INITIALLY;
extern Symbol* SYM_CLASSES_STELLA_SLOT_INITIAL_VALUE;
extern Keyword* KWD_CLASSES_DEFAULT;
extern Symbol* SYM_CLASSES_STELLA_SLOT_DEFAULT_EXPRESSION;
extern Keyword* KWD_CLASSES_READER;
extern Symbol* SYM_CLASSES_STELLA_SLOT_READER;
extern Keyword* KWD_CLASSES_WRITER;
extern Symbol* SYM_CLASSES_STELLA_SLOT_WRITER;
extern Keyword* KWD_CLASSES_INVERSE;
extern Symbol* SYM_CLASSES_STELLA_SLOT_INVERSE;
extern Keyword* KWD_CLASSES_RENAMES;
extern Symbol* SYM_CLASSES_STELLA_SLOT_RENAMES;
extern Keyword* KWD_CLASSES_DOCUMENTATION;
extern Symbol* SYM_CLASSES_STELLA_DOCUMENTATION;
extern Keyword* KWD_CLASSES_PROPERTIES;
extern Symbol* SYM_CLASSES_STELLA_PROPERTIES;
extern Keyword* KWD_CLASSES_META_ATTRIBUTES;
extern Symbol* SYM_CLASSES_STELLA_META_ATTRIBUTES;
extern Keyword* KWD_CLASSES_OPTION_KEYWORD;
extern Symbol* SYM_CLASSES_STELLA_SLOT_OPTION_KEYWORD;
extern Keyword* KWD_CLASSES_OPTION_HANDLER;
extern Symbol* SYM_CLASSES_STELLA_SLOT_OPTION_HANDLER;
extern Surrogate* SGT_CLASSES_STELLA_BOOLEAN;
extern Keyword* KWD_CLASSES_BIT;
extern Keyword* KWD_CLASSES_CL_NATIVE_TYPE;
extern Symbol* SYM_CLASSES_STELLA_CLASS_CL_NATIVE_TYPE;
extern Keyword* KWD_CLASSES_CPP_NATIVE_TYPE;
extern Symbol* SYM_CLASSES_STELLA_CLASS_CPP_NATIVE_TYPE;
extern Keyword* KWD_CLASSES_IDL_NATIVE_TYPE;
extern Symbol* SYM_CLASSES_STELLA_CLASS_IDL_NATIVE_TYPE;
extern Keyword* KWD_CLASSES_JAVA_NATIVE_TYPE;
extern Symbol* SYM_CLASSES_STELLA_CLASS_JAVA_NATIVE_TYPE;
extern Keyword* KWD_CLASSES_CL_STRUCTp;
extern Keyword* KWD_CLASSES_MIXINp;
extern Keyword* KWD_CLASSES_RECYCLE_METHOD;
extern Symbol* SYM_CLASSES_STELLA_CLASS_RECYCLE_METHOD;
extern Keyword* KWD_CLASSES_EXTENSION;
extern Symbol* SYM_CLASSES_STELLA_CLASS_EXTENSION_NAME;
extern Keyword* KWD_CLASSES_CREATOR;
extern Symbol* SYM_CLASSES_STELLA_CLASS_CREATOR;
extern Keyword* KWD_CLASSES_INITIALIZER;
extern Symbol* SYM_CLASSES_STELLA_CLASS_INITIALIZER;
extern Keyword* KWD_CLASSES_TERMINATOR;
extern Symbol* SYM_CLASSES_STELLA_CLASS_TERMINATOR;
extern Keyword* KWD_CLASSES_DESTRUCTOR;
extern Symbol* SYM_CLASSES_STELLA_CLASS_DESTRUCTOR;
extern Keyword* KWD_CLASSES_INITIAL_VALUE;
extern Symbol* SYM_CLASSES_STELLA_CLASS_INITIAL_VALUE;
extern Keyword* KWD_CLASSES_PRINT_FORM;
extern Symbol* SYM_CLASSES_STELLA_PRINT_FORM;
extern Keyword* KWD_CLASSES_EQUALITY_TEST;
extern Keyword* KWD_CLASSES_KEY;
extern Symbol* SYM_CLASSES_STELLA_CLASS_KEY;
extern Symbol* SYM_CLASSES_STELLA_CLASS_PARAMETERS;
extern Keyword* KWD_CLASSES_SYNONYMS;
extern Symbol* SYM_CLASSES_STELLA_CLASS_SYNONYMS;
extern Keyword* KWD_CLASSES_CHILDREN;
extern Surrogate* SGT_CLASSES_STELLA_METHOD_SLOT;
extern Symbol* SYM_CLASSES_STELLA_SLOT_GUARD_DEMONS;
extern Symbol* SYM_CLASSES_STELLA_SLOT_DEMONS;
extern Symbol* SYM_CLASSES_STELLA_CLASS_CONSTRUCTOR_DEMONS;
extern Symbol* SYM_CLASSES_STELLA_CLASS_GUARD_CONSTRUCTOR_DEMONS;
extern Symbol* SYM_CLASSES_STELLA_CLASS_DESTRUCTOR_DEMONS;
extern Symbol* SYM_CLASSES_STELLA_CLASS_GUARD_DESTRUCTOR_DEMONS;
extern Surrogate* SGT_CLASSES_STELLA_ACTIVE_OBJECT;
extern Surrogate* SGT_CLASSES_STELLA_STANDARD_OBJECT;
extern Symbol* SYM_CLASSES_STELLA_PRIMARY_TYPE;
extern Symbol* SYM_CLASSES_STELLA_SELF;
extern Keyword* KWD_CLASSES_TYPE;
extern Symbol* SYM_CLASSES_STELLA_TYPE;
extern Keyword* KWD_CLASSES_AUXILIARYp;
extern Symbol* SYM_CLASSES_STELLA_TRUE;
extern Symbol* SYM_CLASSES_STELLA_RETURN;
extern Symbol* SYM_CLASSES_STELLA_CLASS_EXTENSION;
extern Symbol* SYM_CLASSES_STELLA_BADp;
extern Surrogate* SGT_CLASSES_STELLA_SET;
extern Surrogate* SGT_CLASSES_STELLA_ACTIVE_SET;
extern Surrogate* SGT_CLASSES_STELLA_LIST;
extern Surrogate* SGT_CLASSES_STELLA_ACTIVE_LIST;
extern Surrogate* SGT_CLASSES_STELLA_UNKNOWN;
extern Surrogate* SGT_CLASSES_STELLA_COLLECTION;
extern Surrogate* SGT_CLASSES_STELLA_SET_MIXIN;
extern Symbol* SYM_CLASSES_STELLA_INVERSE;
extern Keyword* KWD_CLASSES_DYNAMIC;
extern Surrogate* SGT_CLASSES_STELLA_DYNAMIC_SLOTS_MIXIN;
extern Keyword* KWD_CLASSES_INSTANCE;
extern Surrogate* SGT_CLASSES_STELLA_CONTEXT_SENSITIVE_OBJECT;
extern Surrogate* SGT_CLASSES_STELLA_CONTEXT_SENSITIVE_MIXIN;
extern Surrogate* SGT_CLASSES_STELLA_VOID;
extern Symbol* SYM_CLASSES_STELLA_METHOD_MACROp;
extern Surrogate* SGT_CLASSES_STELLA_TABLE;
extern Symbol* SYM_CLASSES_STELLA_CLASS_REQUIRED_SLOT_NAMES;
extern Surrogate* SGT_CLASSES_STELLA_ALL_CLASS_SLOTS_ITERATOR;
extern Symbol* SYM_CLASSES_STELLA_ITERATOR_CONS_LIST;
extern Symbol* SYM_CLASSES_STELLA_ITERATOR_OBJECT;
extern Symbol* SYM_CLASSES_STELLA_FALSE;
extern Surrogate* SGT_CLASSES_STELLA_GENERALIZED_SYMBOL;
extern Symbol* SYM_CLASSES_STELLA_ANY;
extern Surrogate* SGT_CLASSES_STELLA_ANY;
extern Surrogate* SGT_CLASSES_STELLA_SLOT;
extern Symbol* SYM_CLASSES_STELLA_STARTUP_CLASSES;
extern Symbol* SYM_CLASSES_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
