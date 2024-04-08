//  -*- Mode: C++ -*-

// frame-support.hh

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

// Global declarations:
extern boolean oLEVELLIZED_BACKCHAINING_ENABLEDpo;

// Function signatures:
Object* coerceToInstanceInModule(Object* self, Module* module, boolean localP, Object* original);
Object* getInstance(Object* instanceref);
Object* findInstance(Object* instanceref);
LogicObject* getSelfOrPrototype(Object* instanceref);
LogicObject* getClass(Object* instanceref);
LogicObject* getRelation(Object* instanceref);
Module* getModule(Object* moduleref);
boolean collectionP(Object* objectref);
boolean classP(Object* objectref);
boolean relationP(Object* objectref);
boolean functionP(Object* relationref);
boolean constantP(Object* objectref);
const char* relationName(NamedDescription* self);
Object* termify(Object* self);
boolean relationArityOkP(Surrogate* relationref, int arity);
Cons* filterOutUnnamedDescriptions(Cons* descriptions);
Cons* allAssertedTypes(Object* self);
Cons* allTaxonomicTypes(Object* self);
Cons* allTypes(Object* self);
Cons* helpAllTypes(Object* self, boolean doSubtypesP);
void helpAllSubtypes(Description* super, Object* self, List* types);
Cons* allDirectTypes(Object* self);
boolean testTypeOnInstanceP(Object* self, Surrogate* type);
Cons* allEquivalentRelations(NamedDescription* relation, boolean reflexiveP);
Cons* removeEquivalentRelations(Cons* relationslist, NamedDescription* relation);
Cons* helpMemoizeAllSuperrelations(NamedDescription* relation, boolean removeequivalentsP);
Cons* allSuperrelations(NamedDescription* relation, boolean removeequivalentsP);
Cons* helpMemoizeAllSubrelations(NamedDescription* relation, boolean removeequivalentsP);
Cons* allSubrelations(NamedDescription* relation, boolean removeequivalentsP);
Cons* allDirectSuperrelations(NamedDescription* relation, boolean removeequivalentsP);
Cons* allDirectSubrelations(NamedDescription* relation, boolean removeequivalentsP);
boolean testSubrelationP(Surrogate* subrelation, Surrogate* superrelation);
Cons* allClassInstances(Surrogate* type);
Cons* allRelationValues(Surrogate* relation, Cons* nminusonearguments);
boolean testRelationOnArgumentsP(Surrogate* relation, Cons* arguments);
Cons* allSlotValues(LogicObject* self, Surrogate* relation);
Object* getSlotValue(LogicObject* self, Surrogate* relation);
boolean testSlotValueP(LogicObject* self, Surrogate* relation, Object* filler);
int getSlotMinimumCardinality(LogicObject* self, Surrogate* relation);
boolean testClosedSlotP(Surrogate* relation);
boolean testFunctionSlotP(Surrogate* relation);
int getSlotMaximumCardinality(LogicObject* self, Surrogate* relation);
NamedDescription* getSlotValueType(LogicObject* self, Surrogate* relation);
Cons* allSlotValueTypes(LogicObject* self, Surrogate* relation);
void helpStartupFrameSupport1();
void helpStartupFrameSupport2();
void startupFrameSupport();

// Auxiliary global declarations:
extern Surrogate* SGT_FRAME_SUPPORT_LOGIC_LOGIC_OBJECT;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_OBJECT_STORE;
extern Surrogate* SGT_FRAME_SUPPORT_STELLA_RELATION;
extern Surrogate* SGT_FRAME_SUPPORT_STELLA_THING;
extern Surrogate* SGT_FRAME_SUPPORT_LOGIC_PROPOSITION;
extern Surrogate* SGT_FRAME_SUPPORT_STELLA_MODULE;
extern Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_COLLECTION;
extern Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_CLASS;
extern Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_RELATION;
extern Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_FUNCTION;
extern Surrogate* SGT_FRAME_SUPPORT_STELLA_LITERAL_WRAPPER;
extern Surrogate* SGT_FRAME_SUPPORT_STELLA_LITERAL;
extern Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_SCALAR;
extern Surrogate* SGT_FRAME_SUPPORT_LOGIC_NAMED_DESCRIPTION;
extern Surrogate* SGT_FRAME_SUPPORT_LOGIC_F_ALL_TAXONOMIC_TYPES_MEMO_TABLE_000;
extern Surrogate* SGT_FRAME_SUPPORT_LOGIC_F_ALL_TYPES_MEMO_TABLE_000;
extern Keyword* KWD_FRAME_SUPPORT_ISA;
extern Surrogate* SGT_FRAME_SUPPORT_LOGIC_F_ALL_EQUIVALENT_RELATIONS_MEMO_TABLE_000;
extern Surrogate* SGT_FRAME_SUPPORT_LOGIC_F_ALL_SUPERRELATIONS_MEMO_TABLE_000;
extern Surrogate* SGT_FRAME_SUPPORT_LOGIC_F_ALL_SUBRELATIONS_MEMO_TABLE_000;
extern Surrogate* SGT_FRAME_SUPPORT_LOGIC_F_ALL_DIRECT_SUPERRELATIONS_MEMO_TABLE_000;
extern Surrogate* SGT_FRAME_SUPPORT_LOGIC_F_ALL_DIRECT_SUBRELATIONS_MEMO_TABLE_000;
extern Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_MIN_CARDINALITY;
extern Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_MAX_CARDINALITY;
extern Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_TYPE;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_pCONCEPT;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_pINSTANCE;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_TYPE_ON_INSTANCEp_QUERY_000;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_pX;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_CLASS_INSTANCES_QUERY_000;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_pRELATION;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_000;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_pY;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_001;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_pZ;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_002;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_pW;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_003;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_ALL;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_000;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_001;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_002;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_003;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_pOBJECT;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_pN;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_RANGE_MIN_CARDINALITY;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_GET_SLOT_MINIMUM_CARDINALITY_QUERY_000;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_RANGE_MAX_CARDINALITY;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_GET_SLOT_MAXIMUM_CARDINALITY_QUERY_000;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_pTYPE;
extern Symbol* SYM_FRAME_SUPPORT_STELLA_AND;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_RANGE_TYPE;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_BOUND_VARIABLES;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_CONCEPT;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_SLOT_VALUE_TYPES_QUERY_000;
extern Symbol* SYM_FRAME_SUPPORT_LOGIC_STARTUP_FRAME_SUPPORT;
extern Symbol* SYM_FRAME_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
