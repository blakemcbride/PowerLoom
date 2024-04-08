//  -*- Mode: C++ -*-

// loom-support.hh

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


namespace pl_kernel_kb_pl_kernel_kb_loom_api {
  using namespace stella;
  using namespace logic;
  using namespace pl_kernel_kb;

// Class definitions:
class LoomRole : public Thing {
// 
public:
  virtual Surrogate* primaryType();
};



// Function signatures:
Surrogate* safeSurrogatify(Object* surrogateref);
LoomRole* newLoomRole();
Object* accessLoomRoleSlotValue(LoomRole* self, Symbol* slotname, Object* value, boolean setvalueP);
LoomRole* findOrCreateLoomRole(Object* instanceref, Object* relationref, boolean createP);
Cons* getLoomRoles(Object* instanceref, boolean inferrolesP);
Cons* getRelationInducedRoles(Object* instanceref);
NamedDescription* relationOfLoomRole(LoomRole* role);
Cons* getRoleNamesAndValues(Object* instanceref);
Module* getXcontext(Object* contextref);
Cons* getParentContexts(Object* moduleref);
Cons* getChildContexts(Object* moduleref);
Module* contextOfInstance(Object* instanceref);
void clearUserContexts();
Cons* listContext(Module* context, Keyword* values);
int relationArity(Object* relationref);
LogicObject* findClass(Object* instanceref, Module* module, boolean localP);
LogicObject* findRelation(Object* instanceref, Module* module, boolean localP);
Surrogate* getInstanceSurrogate(Object* instanceref);
Symbol* getInstanceName(Object* instanceref);
Cons* getEquivalentNames(Object* relationref);
boolean instanceP(Object* objectref);
boolean individualP(Object* object);
boolean namedP(Object* instanceref);
Object* createInstance(Object* instanceref, Object* classref);
LogicObject* findOrCreateInstance(Object* instanceref, Object* classref);
boolean instanceOfP(Object* instanceref, Object* classref);
void addType(Object* instanceref, Object* classref);
void removeType(Object* instanceref, Object* classref);
Cons* getTypes(Object* instanceref, Keyword* directorasserted);
void updateRoleValue(Object* instanceref, Object* relationref, Object* valueref, boolean assertP);
void addRoleValue(Object* instanceref, Object* relationref, Object* valueref);
void removeRoleValue(Object* instanceref, Object* relationref, Object* valueref);
Object* getRoleValue(Object* instanceref, Object* relationref);
Cons* getRoleValues(Object* instanceref, Object* relationref);
Cons* getRoleDefaultValues(Object* instanceref, Object* relationref);
Cons* getClassInstances(Object* classref, boolean directP);
boolean subrelationP(Object* subrelationref, Object* superrelationref);
Cons* getSuperrelations(Object* relationref, boolean directP);
Cons* getSubrelations(Object* relationref, boolean directP);
Cons* mostSpecificRelations(Cons* relationrefs, boolean classifyfirstP);
Description* computeConjunctionRelation(Cons* relationrefs);
NamedDescription* getDomain(Object* relationref);
NamedDescription* getRange(Object* relationref);
int getMinCardinality(Object* instanceref, Object* relationref);
int getMaxCardinality(Object* instanceref, Object* relationref);
Description* getValueRestriction(Object* instanceref, Object* relationref);
void assertLoomProposition(Cons* loomsentence, boolean retractP);
void deleteInstance(Object* instanceref);
Object* generateSourceExpression(Object* instanceref);
Cons* getPartitions(Object* classref);
boolean disjointRelationsP(Object* relationref1, Object* relationref2);
boolean coveringP(Object* instanceref, Object* classref);
Cons* collectionMembers(Object* instanceref);
void helpStartupLoomSupport1();
void helpStartupLoomSupport2();
void startupLoomSupport();

// Auxiliary global declarations:
extern Surrogate* SGT_LOOM_SUPPORT_LOOM_API_LOOM_ROLE;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_LOOM_ROLE_OF;
extern Keyword* KWD_LOOM_SUPPORT_DOCUMENTATION;
extern Keyword* KWD_LOOM_SUPPORT_AXIOMS;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_pI;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_pR;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_pROLE;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_FIND_OR_CREATE_LOOM_ROLE_QUERY_000;
extern Surrogate* SGT_LOOM_SUPPORT_LOOM_API_LOOM_ROLE_OF;
extern Symbol* SYM_LOOM_SUPPORT_STELLA_EXISTS;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_GET_LOOM_ROLES_QUERY_000;
extern Symbol* SYM_LOOM_SUPPORT_STELLA_OR;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_pFR;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_pV;
extern Symbol* SYM_LOOM_SUPPORT_STELLA_AND;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_FRAME_PREDICATE;
extern Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_HOLDS;
extern Symbol* SYM_LOOM_SUPPORT_STELLA_NOT;
extern Symbol* SYM_LOOM_SUPPORT_STELLA_e;
extern Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_RANGE_MAX_CARDINALITY;
extern Symbol* SYM_LOOM_SUPPORT_LOGIC_pC;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_INSTANCE_OF;
extern Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_DOMAIN;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_GET_RELATION_INDUCED_ROLES_QUERY_000;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_RELATION_OF_LOOM_ROLE_QUERY_000;
extern Surrogate* SGT_LOOM_SUPPORT_STELLA_MODULE;
extern Surrogate* SGT_LOOM_SUPPORT_LOGIC_LOGIC_OBJECT;
extern Keyword* KWD_LOOM_SUPPORT_ALL;
extern Keyword* KWD_LOOM_SUPPORT_CONCEPTS;
extern Symbol* SYM_LOOM_SUPPORT_LOGIC_pX;
extern Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_CLASS;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_LIST_CONTEXT_QUERY_000;
extern Keyword* KWD_LOOM_SUPPORT_RELATIONS;
extern Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_RELATION;
extern Symbol* SYM_LOOM_SUPPORT_LOGIC_FAIL;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_LIST_CONTEXT_QUERY_001;
extern Keyword* KWD_LOOM_SUPPORT_INSTANCES;
extern Surrogate* SGT_LOOM_SUPPORT_LOGIC_DESCRIPTION;
extern Surrogate* SGT_LOOM_SUPPORT_PL_KERNEL_KB_ARITY;
extern Surrogate* SGT_LOOM_SUPPORT_STELLA_SURROGATE;
extern Surrogate* SGT_LOOM_SUPPORT_STELLA_THING;
extern Keyword* KWD_LOOM_SUPPORT_ASSERT_TRUE;
extern Keyword* KWD_LOOM_SUPPORT_RETRACT_TRUE;
extern Keyword* KWD_LOOM_SUPPORT_DIRECT;
extern Keyword* KWD_LOOM_SUPPORT_ASSERTED;
extern Keyword* KWD_LOOM_SUPPORT_DEFAULT;
extern Keyword* KWD_LOOM_SUPPORT_STRICT;
extern Keyword* KWD_LOOM_SUPPORT_DESCRIPTION;
extern Symbol* SYM_LOOM_SUPPORT_LOGIC_KAPPA;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_pD;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_GET_DOMAIN_QUERY_000;
extern Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_RANGE;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_GET_RANGE_QUERY_000;
extern Symbol* SYM_LOOM_SUPPORT_LOGIC_pMDC;
extern Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_MEMBER_OF;
extern Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_GET_PARTITIONS_QUERY_000;
extern Surrogate* SGT_LOOM_SUPPORT_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_pCOVERED;
extern Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_COVERING;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_COVERINGp_QUERY_000;
extern Symbol* SYM_LOOM_SUPPORT_LOOM_API_STARTUP_LOOM_SUPPORT;
extern Symbol* SYM_LOOM_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace pl_kernel_kb_pl_kernel_kb_loom_api
