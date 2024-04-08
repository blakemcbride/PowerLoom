//  -*- Mode: C++ -*-

// loom-support.cc

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

#include "logic/logic-system.hh"

namespace pl_kernel_kb_pl_kernel_kb_loom_api {
  using namespace stella;
  using namespace logic;
  using namespace pl_kernel_kb;

Surrogate* safeSurrogatify(Object* surrogateref) {
  if (!((boolean)(surrogateref))) {
    return (NULL);
  }
  { Surrogate* testValue000 = safePrimaryType(surrogateref);

    if (subtypeOfStringP(testValue000)) {
      { Object* surrogateref000 = surrogateref;
        StringWrapper* surrogateref = ((StringWrapper*)(surrogateref000));

        return (stringToSurrogate(surrogateref->wrapperValue));
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* surrogateref001 = surrogateref;
        Surrogate* surrogateref = ((Surrogate*)(surrogateref001));

        return (surrogateref);
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* surrogateref002 = surrogateref;
        Symbol* surrogateref = ((Symbol*)(surrogateref002));

        return (symbolToSurrogate(surrogateref));
      }
    }
    else {
      return (NULL);
    }
  }
}

LoomRole* newLoomRole() {
  { LoomRole* self = NULL;

    self = new LoomRole();
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    return (self);
  }
}

Surrogate* LoomRole::primaryType() {
  { LoomRole* self = this;

    return (SGT_LOOM_SUPPORT_LOOM_API_LOOM_ROLE);
  }
}

Object* accessLoomRoleSlotValue(LoomRole* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (TRUE) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

LoomRole* findOrCreateLoomRole(Object* instanceref, Object* relationref, boolean createP) {
  // Return a LOOM-ROLE instance if 'instanceRef' has
  // a Loom role named 'relationRef'.  If 'create?', create a role
  // instance if one doesn't already exist.
  { Cons* dummy1;
    Cons* dummy2;

    { Object* instance = getInstance(instanceref);
      LogicObject* relation = getRelation(relationref);
      LoomRole* role = NULL;

      if ((!((boolean)(instance))) ||
          (!((boolean)(relation)))) {
        return (NULL);
      }
      role = ((LoomRole*)(applyCachedRetrieve(listO(4, SYM_LOOM_SUPPORT_LOOM_API_pI, SYM_LOOM_SUPPORT_LOOM_API_pR, SYM_LOOM_SUPPORT_LOOM_API_pROLE, NIL), listO(5, SYM_LOOM_SUPPORT_LOOM_API_LOOM_ROLE_OF, SYM_LOOM_SUPPORT_LOOM_API_pI, SYM_LOOM_SUPPORT_LOOM_API_pR, SYM_LOOM_SUPPORT_LOOM_API_pROLE, NIL), consList(3, instance, relation, NULL), consList(0), SYM_LOOM_SUPPORT_LOOM_API_F_FIND_OR_CREATE_LOOM_ROLE_QUERY_000, dummy1, dummy2)->value));
      if (((boolean)(role)) ||
          (!createP)) {
        return (role);
      }
      role = ((LoomRole*)(createLogicInstance(NULL, SGT_LOOM_SUPPORT_LOOM_API_LOOM_ROLE)));
      assertTuple(SGT_LOOM_SUPPORT_LOOM_API_LOOM_ROLE_OF, consList(3, instance, relation, role));
      return (role);
    }
  }
}

Cons* getLoomRoles(Object* instanceref, boolean inferrolesP) {
  // Return a list of LOOM-ROLEs on 'instanceRef'.  If
  // 'inferRoles', create roles on the fly corresponding to
  // frame predicate or domain propositions inherited by 'instance'.
  { Cons* dummy1;
    Cons* dummy2;

    { Object* instance = getInstance(instanceref);

      if (!((boolean)(instance))) {
        return (NULL);
      }
      if (inferrolesP) {
        getRelationInducedRoles(instance);
      }
      return (applyCachedRetrieve(listO(3, SYM_LOOM_SUPPORT_LOOM_API_pI, SYM_LOOM_SUPPORT_LOOM_API_pROLE, NIL), listO(4, SYM_LOOM_SUPPORT_STELLA_EXISTS, SYM_LOOM_SUPPORT_LOOM_API_pR, listO(5, SYM_LOOM_SUPPORT_LOOM_API_LOOM_ROLE_OF, SYM_LOOM_SUPPORT_LOOM_API_pI, SYM_LOOM_SUPPORT_LOOM_API_pR, SYM_LOOM_SUPPORT_LOOM_API_pROLE, NIL), NIL), consList(2, instance, NULL), consList(0), SYM_LOOM_SUPPORT_LOOM_API_F_GET_LOOM_ROLES_QUERY_000, dummy1, dummy2));
    }
  }
}

Cons* getRelationInducedRoles(Object* instanceref) {
  { Cons* dummy1;
    Cons* dummy2;

    { Object* instance = getInstance(instanceref);
      Cons* relations = NIL;
      Cons* roles = NIL;

      if (!((boolean)(instance))) {
        return (NULL);
      }
      relations = applyCachedRetrieve(listO(3, SYM_LOOM_SUPPORT_LOOM_API_pR, SYM_LOOM_SUPPORT_LOOM_API_pI, NIL), listO(4, SYM_LOOM_SUPPORT_STELLA_OR, listO(4, SYM_LOOM_SUPPORT_STELLA_EXISTS, listO(3, SYM_LOOM_SUPPORT_LOOM_API_pFR, SYM_LOOM_SUPPORT_LOOM_API_pV, NIL), listO(5, SYM_LOOM_SUPPORT_STELLA_AND, listO(3, SYM_LOOM_SUPPORT_LOOM_API_FRAME_PREDICATE, SYM_LOOM_SUPPORT_LOOM_API_pFR, NIL), listO(6, SYM_LOOM_SUPPORT_PL_KERNEL_KB_HOLDS, SYM_LOOM_SUPPORT_LOOM_API_pFR, SYM_LOOM_SUPPORT_LOOM_API_pR, SYM_LOOM_SUPPORT_LOOM_API_pI, SYM_LOOM_SUPPORT_LOOM_API_pV, NIL), listO(3, SYM_LOOM_SUPPORT_STELLA_NOT, listO(4, SYM_LOOM_SUPPORT_STELLA_AND, listO(4, SYM_LOOM_SUPPORT_STELLA_e, SYM_LOOM_SUPPORT_LOOM_API_pFR, SYM_LOOM_SUPPORT_PL_KERNEL_KB_RANGE_MAX_CARDINALITY, NIL), listO(4, SYM_LOOM_SUPPORT_STELLA_e, SYM_LOOM_SUPPORT_LOOM_API_pV, wrapInteger(0), NIL), NIL), NIL), NIL), NIL), listO(4, SYM_LOOM_SUPPORT_STELLA_EXISTS, cons(SYM_LOOM_SUPPORT_LOGIC_pC, NIL), listO(4, SYM_LOOM_SUPPORT_STELLA_AND, listO(4, SYM_LOOM_SUPPORT_LOOM_API_INSTANCE_OF, SYM_LOOM_SUPPORT_LOOM_API_pI, SYM_LOOM_SUPPORT_LOGIC_pC, NIL), listO(4, SYM_LOOM_SUPPORT_PL_KERNEL_KB_DOMAIN, SYM_LOOM_SUPPORT_LOOM_API_pR, SYM_LOOM_SUPPORT_LOGIC_pC, NIL), NIL), NIL), NIL), consList(2, NULL, instance), consList(0), SYM_LOOM_SUPPORT_LOOM_API_F_GET_RELATION_INDUCED_ROLES_QUERY_000, dummy1, dummy2);
      { Object* r = NULL;
        Cons* iter000 = relations;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          r = iter000->value;
          roles = cons(findOrCreateLoomRole(instance, r, true), roles);
        }
      }
      return (roles);
    }
  }
}

NamedDescription* relationOfLoomRole(LoomRole* role) {
  // Return the relation for the Loom role 'role'.
  { Cons* dummy1;
    Cons* dummy2;

    return (((NamedDescription*)(applyCachedRetrieve(listO(3, SYM_LOOM_SUPPORT_LOOM_API_pR, SYM_LOOM_SUPPORT_LOOM_API_pROLE, NIL), listO(4, SYM_LOOM_SUPPORT_STELLA_EXISTS, SYM_LOOM_SUPPORT_LOOM_API_pI, listO(5, SYM_LOOM_SUPPORT_LOOM_API_LOOM_ROLE_OF, SYM_LOOM_SUPPORT_LOOM_API_pI, SYM_LOOM_SUPPORT_LOOM_API_pR, SYM_LOOM_SUPPORT_LOOM_API_pROLE, NIL), NIL), consList(2, NULL, role), consList(0), SYM_LOOM_SUPPORT_LOOM_API_F_RELATION_OF_LOOM_ROLE_QUERY_000, dummy1, dummy2)->value)));
  }
}

Cons* getRoleNamesAndValues(Object* instanceref) {
  // Return a list of lists, with each sublist containing
  // a relation (role) name (a symbol) followed by one or more fillers of
  // that role on 'instanceRef'.
  { Object* instance = getInstance(instanceref);
    KeyValueList* table = newKeyValueList();

    if (!((boolean)(instance))) {
      return (NULL);
    }
    { Proposition* p = NULL;
      Iterator* iter000 = ((Iterator*)(allTrueDependentPropositions(instance, NULL, true)->concatenate(allTrueDependentPropositions(instance, NULL, true), 0)));

      for (; iter000->nextP(); ) {
        p = ((Proposition*)(iter000->value));
        if ((p->arguments->length() == 2) &&
            eqlP((p->arguments->theArray)[0], instance)) {
          { Symbol* relation = internSymbolInModule(((Surrogate*)(p->operatoR))->symbolName, ((Module*)(((Surrogate*)(p->operatoR))->homeContext)), true);
            Object* filler = valueOf((p->arguments->theArray)[1]);

            if (((boolean)(filler))) {
              { Cons* bucket = ((Cons*)(table->lookup(relation)));

                if (!((boolean)(bucket))) {
                  table->insertAt(relation, consList(1, filler));
                }
                else {
                  table->insertAt(relation, cons(filler, bucket));
                }
              }
            }
          }
        }
      }
    }
    { Cons* result = NIL;

      { Object* key = NULL;
        Object* value = NULL;
        KvCons* iter001 = table->theKvList;

        for  (; ((boolean)(iter001)); 
              iter001 = iter001->rest) {
          key = iter001->key;
          value = iter001->value;
          result = cons(cons(key, ((Cons*)(value))->concatenate(NIL, 0)), result);
        }
      }
      return (result);
    }
  }
}

Module* getXcontext(Object* contextref) {
  // Return the module referenced by 'contextRef'.
  return (getModule(contextref));
}

Cons* getParentContexts(Object* moduleref) {
  // Return a list of parent modules of 'moduleRef'.
  { Module* module = getModule(moduleref);

    if (!((boolean)(module))) {
      return (NULL);
    }
    else {
      return (module->parentModules->consify());
    }
  }
}

Cons* getChildContexts(Object* moduleref) {
  // Return a list of child modules of 'moduleRef'.
  { Module* module = getModule(moduleref);
    Cons* children = NIL;

    if (!((boolean)(module))) {
      return (NULL);
    }
    { Context* cxt = NULL;
      Cons* iter000 = module->childContexts->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        cxt = ((Context*)(iter000->value));
        if (isaP(cxt, SGT_LOOM_SUPPORT_STELLA_MODULE)) {
          children = cons(cxt, children);
        }
      }
    }
    return (children);
  }
}

Module* contextOfInstance(Object* instanceref) {
  // Return the home context (a module) of 'instanceRef',
  // or NULL if it is not context sensitive.
  { Object* instance = getInstance(instanceref);

    if (!((boolean)(instance))) {
      return (NULL);
    }
    if (subtypeOfP(safePrimaryType(instance), SGT_LOOM_SUPPORT_LOGIC_LOGIC_OBJECT)) {
      { Object* instance000 = instance;
        LogicObject* instance = ((LogicObject*)(instance000));

        return (((Module*)(instance->homeContext)));
      }
    }
    else {
      return (NULL);
    }
  }
}

void clearUserContexts() {
  // Destroy the contents of all non-system-defined modules.
  { Module* mdl = NULL;
    Iterator* iter000 = allModules();

    for (; iter000->nextP(); ) {
      mdl = ((Module*)(iter000->value));
      if (mdl->clearableP_reader() &&
          (!consList(1, oPL_KERNEL_MODULEo)->memberP(mdl))) {
        std::cout << "Clearing: " << mdl << std::endl;
        callClearModule(consList(1, mdl));
      }
    }
  }
}

Cons* listContext(Module* context, Keyword* values) {
  { Cons* dummy1;
    Cons* dummy2;
    Cons* dummy3;
    Cons* dummy4;

    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, context);
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      if (values == KWD_LOOM_SUPPORT_ALL) {
        return (allNamedTerms(context, false)->consify());
      }
      else if (values == KWD_LOOM_SUPPORT_CONCEPTS) {
        return (applyCachedRetrieve(cons(SYM_LOOM_SUPPORT_LOGIC_pX, NIL), listO(3, SYM_LOOM_SUPPORT_PL_KERNEL_KB_CLASS, SYM_LOOM_SUPPORT_LOGIC_pX, NIL), consList(1, NULL), consList(0), SYM_LOOM_SUPPORT_LOOM_API_F_LIST_CONTEXT_QUERY_000, dummy1, dummy2));
      }
      else if (values == KWD_LOOM_SUPPORT_RELATIONS) {
        return (applyCachedRetrieve(cons(SYM_LOOM_SUPPORT_LOGIC_pX, NIL), listO(4, SYM_LOOM_SUPPORT_STELLA_AND, listO(3, SYM_LOOM_SUPPORT_PL_KERNEL_KB_RELATION, SYM_LOOM_SUPPORT_LOGIC_pX, NIL), listO(3, SYM_LOOM_SUPPORT_LOGIC_FAIL, listO(3, SYM_LOOM_SUPPORT_PL_KERNEL_KB_CLASS, SYM_LOOM_SUPPORT_LOGIC_pX, NIL), NIL), NIL), consList(1, NULL), consList(0), SYM_LOOM_SUPPORT_LOOM_API_F_LIST_CONTEXT_QUERY_001, dummy3, dummy4));
      }
      else if (values == KWD_LOOM_SUPPORT_INSTANCES) {
        return (allInstances(context, false)->consify());
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << values << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

int relationArity(Object* relationref) {
  // Return the arity of the relation 'relationRef'.
  { LogicObject* relation = getRelation(relationref);

    if (((boolean)(relation))) {
      { Surrogate* testValue000 = safePrimaryType(relation);

        if (subtypeOfP(testValue000, SGT_LOOM_SUPPORT_LOGIC_DESCRIPTION)) {
          { LogicObject* relation000 = relation;
            Description* relation = ((Description*)(relation000));

            return (relation->arity());
          }
        }
        else if (subtypeOfP(testValue000, SGT_LOOM_SUPPORT_LOGIC_LOGIC_OBJECT)) {
          { LogicObject* relation001 = relation;
            LogicObject* relation = relation001;

            return (((IntegerWrapper*)(getSlotValue(relation, SGT_LOOM_SUPPORT_PL_KERNEL_KB_ARITY)))->wrapperValue);
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
    else {
      return (NULL_INTEGER);
    }
  }
}

LogicObject* findClass(Object* instanceref, Module* module, boolean localP) {
  // Return the nearest class with name 'instanceRef' in
  // the module 'module'.  If 'local?' is FALSE, also search modules inherited
  // by 'module'.  'instanceRef' can be a string, symbol, or surrogate.
  { Object* instance = coerceToInstanceInModule(instanceref, module, localP, NULL);

    if (classP(instance)) {
      return (((LogicObject*)(instance)));
    }
    else {
      return (NULL);
    }
  }
}

LogicObject* findRelation(Object* instanceref, Module* module, boolean localP) {
  // Return the nearest relation with name 'instanceRef' in
  // the module 'module'.  If 'local?' is FALSE, also search modules inherited
  // by 'module'.  'instanceRef' can be a string, symbol, or surrogate.
  { Object* instance = coerceToInstanceInModule(instanceref, module, localP, NULL);

    if (relationP(instance)) {
      return (((LogicObject*)(instance)));
    }
    else {
      return (NULL);
    }
  }
}

Surrogate* getInstanceSurrogate(Object* instanceref) {
  // Return the surrogate pointing to the instance referenced by
  // 'instanceRef'.
  if (!((boolean)(instanceref))) {
    return (NULL);
  }
  else if (isaP(instanceref, SGT_LOOM_SUPPORT_STELLA_SURROGATE)) {
    if (!((boolean)(((Surrogate*)(instanceref))->surrogateValue))) {
      return (NULL);
    }
    else {
      return (((Surrogate*)(instanceref)));
    }
  }
  else {
    { Object* instance = getInstance(instanceref);

      if (!((boolean)(instance))) {
        return (NULL);
      }
      { Surrogate* testValue000 = safePrimaryType(instance);

        if (subtypeOfP(testValue000, SGT_LOOM_SUPPORT_LOGIC_LOGIC_OBJECT)) {
          { Object* instance000 = instance;
            LogicObject* instance = ((LogicObject*)(instance000));

            if (((boolean)(instance))) {
              return (instance->surrogateValueInverse);
            }
            else {
              return (NULL);
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_LOOM_SUPPORT_STELLA_THING)) {
          { Object* instance001 = instance;
            Thing* instance = ((Thing*)(instance001));

            if (((boolean)(instance))) {
              return (instance->surrogateValueInverse);
            }
            else {
              return (NULL);
            }
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
  }
}

Symbol* getInstanceName(Object* instanceref) {
  // Return the name (a symbol) of the instance referenced by
  // 'instanceRef'.
  { Object* instance = getInstance(instanceref);

    { Surrogate* testValue000 = safePrimaryType(instance);

      if (subtypeOfP(testValue000, SGT_LOOM_SUPPORT_LOGIC_LOGIC_OBJECT)) {
        { Object* instance000 = instance;
          LogicObject* instance = ((LogicObject*)(instance000));

          if (((boolean)(instance)) &&
              ((boolean)(instance->surrogateValueInverse))) {
            return (internSymbolInModule(instance->surrogateValueInverse->symbolName, ((Module*)(instance->surrogateValueInverse->homeContext)), true));
          }
        }
      }
      else if (subtypeOfP(testValue000, SGT_LOOM_SUPPORT_STELLA_THING)) {
        { Object* instance001 = instance;
          Thing* instance = ((Thing*)(instance001));

          if (((boolean)(instance)) &&
              ((boolean)(instance->surrogateValueInverse))) {
            return (internSymbolInModule(instance->surrogateValueInverse->symbolName, ((Module*)(instance->surrogateValueInverse->homeContext)), true));
          }
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    return (NULL);
  }
}

Cons* getEquivalentNames(Object* relationref) {
  // Return a list containing the name of 'relationRef'
  // plus the names of any equivalent relations.
  { LogicObject* relation = getRelation(relationref);
    Cons* equivalentnames = NIL;

    if (!((boolean)(relation))) {
      return (NULL);
    }
    { LogicObject* e = NULL;
      Cons* iter000 = allEquivalentCollections(relation, true);
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        e = ((LogicObject*)(iter000->value));
        if (namedDescriptionP(((Description*)(e)))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(((Description*)(e))->descriptionName(), NIL);
              if (equivalentnames == NIL) {
                equivalentnames = collect000;
              }
              else {
                addConsToEndOfConsList(equivalentnames, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(((Description*)(e))->descriptionName(), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (equivalentnames);
  }
}

boolean instanceP(Object* objectref) {
  // Return TRUE if 'objectRef' is an instance or the
  // name of an instance.
  { 
    BIND_STELLA_SPECIAL(oSUPPRESSNONLOGICOBJECTWARNINGpo, boolean, true);
    return (((boolean)(getInstance(objectref))));
  }
}

boolean individualP(Object* object) {
  // Return TRUE if 'objectRef' is an instance or the
  // name of an instance, and does not denote a relation, class, or set.
  { 
    BIND_STELLA_SPECIAL(oSUPPRESSNONLOGICOBJECTWARNINGpo, boolean, true);
    { Object* instance = getInstance(object);

      return (((boolean)(instance)) &&
          (!collectionP(instance)));
    }
  }
}

boolean namedP(Object* instanceref) {
  // Return TRUE if the object returned by 'instanceRef'
  // is matched with a logical constant.
  return (((boolean)(getInstanceName(instanceref))));
}

Object* createInstance(Object* instanceref, Object* classref) {
  // Create an instance named 'instanceRef'
  // of type 'classRef'.
  { Surrogate* classtype = getInstanceSurrogate(classref);
    Surrogate* surrogate = safeSurrogatify(instanceref);

    if (classP(classtype) &&
        ((!((boolean)(instanceref))) ||
         ((boolean)(surrogate)))) {
      return (createLogicInstance(surrogate, classtype));
    }
    else {
      return (NULL);
    }
  }
}

LogicObject* findOrCreateInstance(Object* instanceref, Object* classref) {
  // Find an existing instance refenced by 'instanceRef'
  // of type 'classRef', or create one of type 'classRef'.
  { Object* instance = getInstance(instanceref);
    Surrogate* classtype = getInstanceSurrogate(classref);

    if (((boolean)(instance))) {
      if ((!((boolean)(classref))) ||
          instanceOfP(instance, classtype)) {
        return (((LogicObject*)(instance)));
      }
      else {
        return (NULL);
      }
    }
    else {
      return (((LogicObject*)(createInstance(instanceref, classref))));
    }
  }
}

boolean instanceOfP(Object* instanceref, Object* classref) {
  // Return TRUE if the instance referenced by 'instanceRef'
  // belongs to the class referenced by 'classRef'.
  { Object* instance = getInstance(instanceref);
    Surrogate* classtype = getInstanceSurrogate(classref);

    return (((boolean)(instance)) &&
        (((boolean)(classtype)) &&
         testTypeOnInstanceP(instance, classtype)));
  }
}

void addType(Object* instanceref, Object* classref) {
  // Assert that the instance referenced by 'instanceRef'
  // is an instance of the class referenced by 'classRef'.
  { Object* instance = getInstance(instanceref);
    Surrogate* classtype = getInstanceSurrogate(classref);

    if (((boolean)(instance)) &&
        classP(classtype)) {
      updateIsaProposition(instance, classtype, KWD_LOOM_SUPPORT_ASSERT_TRUE);
    }
  }
}

void removeType(Object* instanceref, Object* classref) {
  // Retract that the instance referenced by 'instanceRef'
  // is an instance of the class referenced by 'classRef'.
  { Object* instance = getInstance(instanceref);
    Surrogate* classtype = getInstanceSurrogate(classref);

    if (((boolean)(instance)) &&
        classP(classtype)) {
      updateIsaProposition(instance, classtype, KWD_LOOM_SUPPORT_RETRACT_TRUE);
    }
  }
}

Cons* getTypes(Object* instanceref, Keyword* directorasserted) {
  // Return a list of classes that instance belongs to.
  { Object* instance = getInstance(instanceref);
    Cons* result = NIL;

    if (!((boolean)(instance))) {
      return (NULL);
    }
    if (directorasserted == KWD_LOOM_SUPPORT_DIRECT) {
      { LogicObject* d = NULL;
        Cons* iter000 = allDirectTypes(instance);

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          d = ((LogicObject*)(iter000->value));
          result = cons(d, result);
        }
      }
    }
    else if (directorasserted == KWD_LOOM_SUPPORT_ASSERTED) {
      { NamedDescription* d = NULL;
        Cons* iter001 = allAssertedTypes(instance);

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          d = ((NamedDescription*)(iter001->value));
          result = cons(d, result);
        }
      }
    }
    else {
      { NamedDescription* d = NULL;
        Cons* iter002 = allTypes(instance);

        for (; !(iter002 == NIL); iter002 = iter002->rest) {
          d = ((NamedDescription*)(iter002->value));
          result = cons(d, result);
        }
      }
    }
    return (result);
  }
}

void updateRoleValue(Object* instanceref, Object* relationref, Object* valueref, boolean assertP) {
  // Assert the tuple '(relationRef instanceRef valueRef)',
  // or retract if 'assert?' is FALSE.
  { Object* instance = getInstance(instanceref);
    LogicObject* relation = getRelation(relationref);
    Object* value = getInstance(valueref);

    if (((boolean)(instance)) &&
        (((boolean)(relation)) &&
         ((relationArity(relation) == 2) &&
          ((boolean)(value))))) {
      updateTuple(getInstanceSurrogate(relation), consList(2, instance, value), (assertP ? KWD_LOOM_SUPPORT_ASSERT_TRUE : KWD_LOOM_SUPPORT_RETRACT_TRUE));
    }
  }
}

void addRoleValue(Object* instanceref, Object* relationref, Object* valueref) {
  // Assert the tuple '(relationRef instanceRef valueRef)'.
  updateRoleValue(instanceref, relationref, valueref, true);
}

void removeRoleValue(Object* instanceref, Object* relationref, Object* valueref) {
  // Retract the tuple '(relationRef instanceRef valueRef)'.
  updateRoleValue(instanceref, relationref, valueref, false);
}

Object* getRoleValue(Object* instanceref, Object* relationref) {
  // Return a value for the binary relation 'relationRef'
  // applied to 'instanceRef'.
  { Object* instance = getInstance(instanceref);
    LogicObject* relation = getRelation(relationref);

    if (((boolean)(instance)) &&
        (((boolean)(relation)) &&
         (relationArity(relation) == 2))) {
      return (getSlotValue(((LogicObject*)(instance)), getInstanceSurrogate(relation)));
    }
    else {
      return (NULL);
    }
  }
}

Cons* getRoleValues(Object* instanceref, Object* relationref) {
  // Return a list of values for the binary relation 'relationRef'
  // applied to 'instanceRef'.
  { Object* instance = getInstance(instanceref);
    LogicObject* relation = getRelation(relationref);

    if (((boolean)(instance)) &&
        (((boolean)(relation)) &&
         (relationArity(relation) == 2))) {
      return (allSlotValues(((LogicObject*)(instance)), getInstanceSurrogate(relation)));
    }
    else {
      return (NULL);
    }
  }
}

Cons* getRoleDefaultValues(Object* instanceref, Object* relationref) {
  // Return a list of default values for the binary relation
  // 'relationRef' applied to 'instanceRef'.
  { Cons* defaultvalues = NULL;

    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getInferenceCache(oMODULEo, KWD_LOOM_SUPPORT_DEFAULT));
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      defaultvalues = getRoleValues(instanceref, relationref);
    }
    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getInferenceCache(oMODULEo, KWD_LOOM_SUPPORT_STRICT));
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      { Object* v = NULL;
        Cons* iter000 = getRoleValues(instanceref, relationref);

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          v = iter000->value;
          defaultvalues = defaultvalues->remove(v);
        }
      }
    }
    return (defaultvalues);
  }
}

Cons* getClassInstances(Object* classref, boolean directP) {
  // Return a list of instances belonging to the class 'classRef'.
  { Surrogate* classtype = getInstanceSurrogate(classref);

    if (classP(classtype)) {
      if (directP) {
        { Cons* instances = allClassInstances(classtype);
          Cons* directinstances = NIL;
          Cons* directsubs = allDirectSubrelations(((NamedDescription*)(getInstance(classref))), true);
          boolean instanceOfSubP = false;

          { Object* i = NULL;
            Cons* iter000 = instances;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              i = iter000->value;
              instanceOfSubP = false;
              { NamedDescription* s = NULL;
                Cons* iter001 = directsubs;

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  s = ((NamedDescription*)(iter001->value));
                  if (instanceOfP(i, s)) {
                    instanceOfSubP = true;
                    break;
                  }
                }
              }
              if (!(instanceOfSubP)) {
                directinstances = cons(i, directinstances);
              }
            }
          }
          return (directinstances);
        }
      }
      else {
        return (allClassInstances(classtype));
      }
    }
    else {
      return (NIL);
    }
  }
}

boolean subrelationP(Object* subrelationref, Object* superrelationref) {
  // Return TRUE if 'subrelationRef' specializes 'superrelationRef'.
  // Side-effect: Upclassify 'subrelationRef'.
  { Cons* dummy1;
    Cons* dummy2;

    { LogicObject* subrelation = getRelation(subrelationref);
      Surrogate* subrelationtype = (((boolean)(subrelation)) ? subrelation->surrogateValueInverse : ((Surrogate*)(NULL)));
      Surrogate* superrelationtype = getInstanceSurrogate(superrelationref);

      if (relationP(subrelationtype) &&
          relationP(superrelationtype)) {
        {
          findDirectSupersAndSubs(((Description*)(subrelation)), true, dummy1, dummy2);
          return (testSubrelationP(subrelationtype, superrelationtype));
        }
      }
      else {
        return (false);
      }
    }
  }
}

Cons* getSuperrelations(Object* relationref, boolean directP) {
  // Return a list of relations that generalize 'relationRef'.
  // Does not include relations equivalent to 'relationRef'.
  finalizeObjects();
  { Object* relation = getInstance(relationref);
    Cons* result = NIL;

    if (relationP(relation)) {
      if (directP) {
        { NamedDescription* super = NULL;
          Cons* iter000 = allDirectSuperrelations(((NamedDescription*)(relation)), true);

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            super = ((NamedDescription*)(iter000->value));
            result = cons(super, result);
          }
        }
      }
      else {
        { NamedDescription* super = NULL;
          Cons* iter001 = allSuperrelations(((NamedDescription*)(relation)), true);

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            super = ((NamedDescription*)(iter001->value));
            result = cons(super, result);
          }
        }
      }
    }
    return (result);
  }
}

Cons* getSubrelations(Object* relationref, boolean directP) {
  // Return a list of relations that specialize 'relationRef'.
  // Does not include relations equivalent to 'relationRef'.
  finalizeObjects();
  { Object* relation = getInstance(relationref);
    Cons* result = NIL;

    if (relationP(relation)) {
      if (directP) {
        { NamedDescription* sub = NULL;
          Cons* iter000 = allDirectSubrelations(((NamedDescription*)(relation)), true);

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            sub = ((NamedDescription*)(iter000->value));
            result = cons(sub, result);
          }
        }
      }
      else {
        { NamedDescription* sub = NULL;
          Cons* iter001 = allSubrelations(((NamedDescription*)(relation)), true);

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            sub = ((NamedDescription*)(iter001->value));
            result = cons(sub, result);
          }
        }
      }
    }
    return (result);
  }
}

Cons* mostSpecificRelations(Cons* relationrefs, boolean classifyfirstP) {
  // Return a list of the most specific among the
  // relations in 'relationRefs'.  If 'classifyFirst?', insure that
  // all relations are classified before filtering for most-specific.
  { Cons* relations = NIL;

    { Object* r = NULL;
      Cons* iter000 = relationrefs;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        r = iter000->value;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(getRelation(r), NIL);
            if (relations == NIL) {
              relations = collect000;
            }
            else {
              addConsToEndOfConsList(relations, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(getRelation(r), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    relations = relations->removeDuplicates();
    if (relations->rest == NIL) {
      return (relations);
    }
    if (classifyfirstP) {
      { 
        BIND_STELLA_SPECIAL(oCLASSIFICATIONSESSIONo, ClassificationSession*, getClassificationSession(KWD_LOOM_SUPPORT_DESCRIPTION));
        { 
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getClassificationWorld());
          { Description* youngestrelation = ((Description*)(relations->value));

            { Description* r = NULL;
              Cons* iter001 = relations->rest;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                r = ((Description*)(iter001->value));
                if (r->introductionTimestamp() > youngestrelation->introductionTimestamp()) {
                  youngestrelation = r;
                }
              }
            }
            { Description* r = NULL;
              Cons* iter002 = relations;

              for (; !(iter002 == NIL); iter002 = iter002->rest) {
                r = ((Description*)(iter002->value));
                if (!upclassifiedLaterThanP(r, youngestrelation)) {
                  upclassifyOneDescription(r);
                }
              }
            }
            return (mostSpecificNamedCollections(relations));
          }
        }
      }
    }
    return (mostSpecificNamedCollections(relations));
  }
}

Description* computeConjunctionRelation(Cons* relationrefs) {
  // Return a relation representing the conjunction
  // of relations in 'relationRefs'.
  { Cons* relations = NIL;
    LogicObject* conjunctiondescription = NULL;

    { NamedDescription* r = NULL;
      Cons* iter000 = relationrefs;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        r = ((NamedDescription*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(getRelation(r), NIL);
            if (relations == NIL) {
              relations = collect000;
            }
            else {
              addConsToEndOfConsList(relations, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(getRelation(r), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    relations = relations->removeDuplicates();
    if (relations->rest == NIL) {
      return (((Description*)(relations->value)));
    }
    { Cons* clauses = NIL;
      Cons* variables = NIL;

      { Symbol* v = NULL;
        Cons* iter001 = SYSTEM_DEFINED_ARGUMENT_NAMES;
        IntegerIntervalIterator* i = interval(1, relationArity(((Description*)(relations->value))));
        Cons* collect001 = NULL;

        for  (; (!(iter001 == NIL)) &&
                  i->nextP(); 
              iter001 = iter001->rest) {
          v = ((Symbol*)(iter001->value));
          if (!((boolean)(collect001))) {
            {
              collect001 = cons(v, NIL);
              if (variables == NIL) {
                variables = collect001;
              }
              else {
                addConsToEndOfConsList(variables, collect001);
              }
            }
          }
          else {
            {
              collect001->rest = cons(v, NIL);
              collect001 = collect001->rest;
            }
          }
        }
      }
      { Description* r = NULL;
        Cons* iter002 = relations;

        for (; !(iter002 == NIL); iter002 = iter002->rest) {
          r = ((Description*)(iter002->value));
          if (namedP(r)) {
            clauses = cons(cons(internSymbolInModule(r->surrogateValueInverse->symbolName, ((Module*)(r->surrogateValueInverse->homeContext)), true), copyConsList(variables)->concatenate(NIL, 0)), clauses);
          }
          else {
            clauses = cons(((Cons*)(generateExpression(r, true)))->rest->rest->value, clauses);
          }
        }
      }
      conjunctiondescription = ((LogicObject*)(conceiveTerm(listO(4, SYM_LOOM_SUPPORT_LOGIC_KAPPA, cons(variables, NIL), cons(SYM_LOOM_SUPPORT_STELLA_AND, clauses->concatenate(NIL, 0)), NIL))));
    }
    { Cons* supers = NULL;
      Cons* subs = NULL;
      Cons* equivalents = NULL;

      supers = findDirectSupersAndSubs(((Description*)(conjunctiondescription)), true, subs, equivalents);
      {
        supers = supers;
        subs = subs;
      }
      if (!(equivalents == NIL)) {
        return (((Description*)(equivalents->value)));
      }
      else {
        return (((Description*)(conjunctiondescription)));
      }
    }
  }
}

NamedDescription* getDomain(Object* relationref) {
  // Return the domain of the binary relation 'relationRef'.
  { Cons* dummy1;
    Cons* dummy2;

    { LogicObject* relation = getRelation(relationref);

      if (!((boolean)(relation))) {
        return (NULL);
      }
      return (((NamedDescription*)(applyCachedRetrieve(listO(3, SYM_LOOM_SUPPORT_LOOM_API_pD, SYM_LOOM_SUPPORT_LOOM_API_pR, NIL), listO(4, SYM_LOOM_SUPPORT_PL_KERNEL_KB_DOMAIN, SYM_LOOM_SUPPORT_LOOM_API_pR, SYM_LOOM_SUPPORT_LOOM_API_pD, NIL), consList(2, NULL, relation), consList(0), SYM_LOOM_SUPPORT_LOOM_API_F_GET_DOMAIN_QUERY_000, dummy1, dummy2)->value)));
    }
  }
}

NamedDescription* getRange(Object* relationref) {
  // Return the range of the binary relation 'relationRef'.
  { Cons* dummy1;
    Cons* dummy2;

    { LogicObject* relation = getRelation(relationref);

      if (!((boolean)(relation))) {
        return (NULL);
      }
      return (((NamedDescription*)(applyCachedRetrieve(listO(3, SYM_LOOM_SUPPORT_LOOM_API_pD, SYM_LOOM_SUPPORT_LOOM_API_pR, NIL), listO(4, SYM_LOOM_SUPPORT_PL_KERNEL_KB_RANGE, SYM_LOOM_SUPPORT_LOOM_API_pR, SYM_LOOM_SUPPORT_LOOM_API_pD, NIL), consList(2, NULL, relation), consList(0), SYM_LOOM_SUPPORT_LOOM_API_F_GET_RANGE_QUERY_000, dummy1, dummy2)->value)));
    }
  }
}

int getMinCardinality(Object* instanceref, Object* relationref) {
  // Infer a minimum cardinality for the set of fillers of
  // the range of relation 'relationRef' applied to 'instanceRef'.
  { Object* instance = getInstance(instanceref);
    Surrogate* relationsurrogate = getInstanceSurrogate(relationref);

    return (getSlotMinimumCardinality(((LogicObject*)(instance)), relationsurrogate));
  }
}

int getMaxCardinality(Object* instanceref, Object* relationref) {
  // Infer a maximum cardinality for the set of fillers of
  // the range of relation 'relationRef' applied to 'instanceRef'.
  { Object* instance = getInstance(instanceref);
    Surrogate* relationsurrogate = getInstanceSurrogate(relationref);

    return (getSlotMaximumCardinality(((LogicObject*)(instance)), relationsurrogate));
  }
}

Description* getValueRestriction(Object* instanceref, Object* relationref) {
  // Infer a type restriction on the set of fillers of
  // the range of relation 'relationRef' applied to 'instanceRef'.
  { Object* instance = getInstance(instanceref);
    Surrogate* relationsurrogate = getInstanceSurrogate(relationref);
    NamedDescription* type = getSlotValueType(((LogicObject*)(instance)), relationsurrogate);

    if (!((boolean)(type))) {
      type = getDescription(SGT_LOOM_SUPPORT_STELLA_THING);
    }
    return (type);
  }
}

void assertLoomProposition(Cons* loomsentence, boolean retractP) {
  // Convert each Loom sentence into a KIF equivalent
  // and assert it or retract it.
  updateProposition(translateLoomSentenceToKif(loomsentence), (retractP ? KWD_LOOM_SUPPORT_RETRACT_TRUE : KWD_LOOM_SUPPORT_ASSERT_TRUE));
}

void deleteInstance(Object* instanceref) {
  // Destroy the instance, class or relation 'instanceRef'.
  { Object* instance = getInstance(instanceref);

    if (((boolean)(instance))) {
      destroyTerm(((LogicObject*)(instance)));
    }
  }
}

Object* generateSourceExpression(Object* instanceref) {
  // Return an s-expression representing the
  // source expression for 'instanceRef'.
  { Object* instance = getInstance(instanceref);

    return (generateExpression(instance, false));
  }
}

Cons* getPartitions(Object* classref) {
  // Return a list of partitions that
  // specify disjointness of children of the class classRef'.
  { Cons* dummy1;
    Cons* dummy2;

    { LogicObject* clasS = getClass(classref);
      Cons* partitions = NIL;

      if (((boolean)(clasS))) {
        { LogicObject* c = NULL;
          Cons* iter000 = getSubrelations(clasS, true);

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            c = ((LogicObject*)(iter000->value));
            { Object* mdc = NULL;
              Cons* iter001 = applyCachedRetrieve(listO(3, SYM_LOOM_SUPPORT_LOGIC_pC, SYM_LOOM_SUPPORT_LOGIC_pMDC, NIL), listO(4, SYM_LOOM_SUPPORT_STELLA_AND, listO(4, SYM_LOOM_SUPPORT_PL_KERNEL_KB_MEMBER_OF, SYM_LOOM_SUPPORT_LOGIC_pC, SYM_LOOM_SUPPORT_LOGIC_pMDC, NIL), listO(3, SYM_LOOM_SUPPORT_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION, SYM_LOOM_SUPPORT_LOGIC_pMDC, NIL), NIL), consList(2, c, NULL), consList(0), SYM_LOOM_SUPPORT_LOOM_API_F_GET_PARTITIONS_QUERY_000, dummy1, dummy2);

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                mdc = iter001->value;
                if (!partitions->memberP(mdc)) {
                  partitions = cons(mdc, partitions);
                }
              }
            }
          }
        }
      }
      return (partitions);
    }
  }
}

boolean disjointRelationsP(Object* relationref1, Object* relationref2) {
  // Return TRUE if 'relationRef1' and 'relationRef2' are
  // disjoint.
  { LogicObject* relation1 = getRelation(relationref1);
    LogicObject* relation2 = getRelation(relationref2);

    return (expensiveDisjointTermsP(((Description*)(relation1)), ((Description*)(relation2))));
  }
}

boolean coveringP(Object* instanceref, Object* classref) {
  // Return TRUE if the mutually disjoint collection 'instanceRef'
  // covers 'classRef'.  If 'classRef' is NULL, return TRUE if 'instanceRef' covers
  // some concept.
  { Cons* dummy1;
    Cons* dummy2;

    { Object* mdc = getInstance(instanceref);
      LogicObject* coveredclass = getClass(classref);

      if ((!((boolean)(mdc))) ||
          (!testPropertyP(mdc, SGT_LOOM_SUPPORT_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION))) {
        return (false);
      }
      { ConsIterator* c = applyCachedRetrieve(listO(3, SYM_LOOM_SUPPORT_LOGIC_pMDC, SYM_LOOM_SUPPORT_LOOM_API_pCOVERED, NIL), listO(4, SYM_LOOM_SUPPORT_PL_KERNEL_KB_COVERING, SYM_LOOM_SUPPORT_LOGIC_pMDC, SYM_LOOM_SUPPORT_LOOM_API_pCOVERED, NIL), consList(2, mdc, coveredclass), consList(0), SYM_LOOM_SUPPORT_LOOM_API_F_COVERINGp_QUERY_000, dummy1, dummy2)->allocateIterator();

        for (; c->nextP(); ) {
          return (true);
        }
      }
      return (false);
    }
  }
}

Cons* collectionMembers(Object* instanceref) {
  // Return a list of concepts that belong to the collection 'instanceRef'.
  { Object* instance = getInstance(instanceref);

    if (((boolean)(instance))) {
      return (assertedCollectionMembers(instance, false)->consify());
    }
    return (NIL);
  }
}

void helpStartupLoomSupport1() {
  {
    SGT_LOOM_SUPPORT_LOOM_API_LOOM_ROLE = ((Surrogate*)(internRigidSymbolWrtModule("LOOM-ROLE", NULL, 1)));
    SYM_LOOM_SUPPORT_LOOM_API_LOOM_ROLE_OF = ((Symbol*)(internRigidSymbolWrtModule("LOOM-ROLE-OF", NULL, 0)));
    KWD_LOOM_SUPPORT_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
    KWD_LOOM_SUPPORT_AXIOMS = ((Keyword*)(internRigidSymbolWrtModule("AXIOMS", NULL, 2)));
    SYM_LOOM_SUPPORT_LOOM_API_pI = ((Symbol*)(internRigidSymbolWrtModule("?I", NULL, 0)));
    SYM_LOOM_SUPPORT_LOOM_API_pR = ((Symbol*)(internRigidSymbolWrtModule("?R", NULL, 0)));
    SYM_LOOM_SUPPORT_LOOM_API_pROLE = ((Symbol*)(internRigidSymbolWrtModule("?ROLE", NULL, 0)));
    SYM_LOOM_SUPPORT_LOOM_API_F_FIND_OR_CREATE_LOOM_ROLE_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("F-FIND-OR-CREATE-LOOM-ROLE-QUERY-000", NULL, 0)));
    SGT_LOOM_SUPPORT_LOOM_API_LOOM_ROLE_OF = ((Surrogate*)(internRigidSymbolWrtModule("LOOM-ROLE-OF", NULL, 1)));
    SYM_LOOM_SUPPORT_STELLA_EXISTS = ((Symbol*)(internRigidSymbolWrtModule("EXISTS", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_SUPPORT_LOOM_API_F_GET_LOOM_ROLES_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("F-GET-LOOM-ROLES-QUERY-000", NULL, 0)));
    SYM_LOOM_SUPPORT_STELLA_OR = ((Symbol*)(internRigidSymbolWrtModule("OR", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_SUPPORT_LOOM_API_pFR = ((Symbol*)(internRigidSymbolWrtModule("?FR", NULL, 0)));
    SYM_LOOM_SUPPORT_LOOM_API_pV = ((Symbol*)(internRigidSymbolWrtModule("?V", NULL, 0)));
    SYM_LOOM_SUPPORT_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_SUPPORT_LOOM_API_FRAME_PREDICATE = ((Symbol*)(internRigidSymbolWrtModule("FRAME-PREDICATE", NULL, 0)));
    SYM_LOOM_SUPPORT_PL_KERNEL_KB_HOLDS = ((Symbol*)(internRigidSymbolWrtModule("HOLDS", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_SUPPORT_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_SUPPORT_STELLA_e = ((Symbol*)(internRigidSymbolWrtModule("=", getStellaModule("/STELLA", true), 0)));
    SYM_LOOM_SUPPORT_PL_KERNEL_KB_RANGE_MAX_CARDINALITY = ((Symbol*)(internRigidSymbolWrtModule("RANGE-MAX-CARDINALITY", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_SUPPORT_LOGIC_pC = ((Symbol*)(internRigidSymbolWrtModule("?C", getStellaModule("/LOGIC", true), 0)));
    SYM_LOOM_SUPPORT_LOOM_API_INSTANCE_OF = ((Symbol*)(internRigidSymbolWrtModule("INSTANCE-OF", NULL, 0)));
    SYM_LOOM_SUPPORT_PL_KERNEL_KB_DOMAIN = ((Symbol*)(internRigidSymbolWrtModule("DOMAIN", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_SUPPORT_LOOM_API_F_GET_RELATION_INDUCED_ROLES_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("F-GET-RELATION-INDUCED-ROLES-QUERY-000", NULL, 0)));
    SYM_LOOM_SUPPORT_LOOM_API_F_RELATION_OF_LOOM_ROLE_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("F-RELATION-OF-LOOM-ROLE-QUERY-000", NULL, 0)));
    SGT_LOOM_SUPPORT_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 1)));
    SGT_LOOM_SUPPORT_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", getStellaModule("/LOGIC", true), 1)));
    KWD_LOOM_SUPPORT_ALL = ((Keyword*)(internRigidSymbolWrtModule("ALL", NULL, 2)));
    KWD_LOOM_SUPPORT_CONCEPTS = ((Keyword*)(internRigidSymbolWrtModule("CONCEPTS", NULL, 2)));
    SYM_LOOM_SUPPORT_LOGIC_pX = ((Symbol*)(internRigidSymbolWrtModule("?X", getStellaModule("/LOGIC", true), 0)));
    SYM_LOOM_SUPPORT_PL_KERNEL_KB_CLASS = ((Symbol*)(internRigidSymbolWrtModule("CLASS", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_SUPPORT_LOOM_API_F_LIST_CONTEXT_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("F-LIST-CONTEXT-QUERY-000", NULL, 0)));
    KWD_LOOM_SUPPORT_RELATIONS = ((Keyword*)(internRigidSymbolWrtModule("RELATIONS", NULL, 2)));
    SYM_LOOM_SUPPORT_PL_KERNEL_KB_RELATION = ((Symbol*)(internRigidSymbolWrtModule("RELATION", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_SUPPORT_LOGIC_FAIL = ((Symbol*)(internRigidSymbolWrtModule("FAIL", getStellaModule("/LOGIC", true), 0)));
    SYM_LOOM_SUPPORT_LOOM_API_F_LIST_CONTEXT_QUERY_001 = ((Symbol*)(internRigidSymbolWrtModule("F-LIST-CONTEXT-QUERY-001", NULL, 0)));
    KWD_LOOM_SUPPORT_INSTANCES = ((Keyword*)(internRigidSymbolWrtModule("INSTANCES", NULL, 2)));
    SGT_LOOM_SUPPORT_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", getStellaModule("/LOGIC", true), 1)));
    SGT_LOOM_SUPPORT_PL_KERNEL_KB_ARITY = ((Surrogate*)(internRigidSymbolWrtModule("ARITY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_LOOM_SUPPORT_STELLA_SURROGATE = ((Surrogate*)(internRigidSymbolWrtModule("SURROGATE", getStellaModule("/STELLA", true), 1)));
    SGT_LOOM_SUPPORT_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
    KWD_LOOM_SUPPORT_ASSERT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("ASSERT-TRUE", NULL, 2)));
    KWD_LOOM_SUPPORT_RETRACT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("RETRACT-TRUE", NULL, 2)));
    KWD_LOOM_SUPPORT_DIRECT = ((Keyword*)(internRigidSymbolWrtModule("DIRECT", NULL, 2)));
    KWD_LOOM_SUPPORT_ASSERTED = ((Keyword*)(internRigidSymbolWrtModule("ASSERTED", NULL, 2)));
    KWD_LOOM_SUPPORT_DEFAULT = ((Keyword*)(internRigidSymbolWrtModule("DEFAULT", NULL, 2)));
    KWD_LOOM_SUPPORT_STRICT = ((Keyword*)(internRigidSymbolWrtModule("STRICT", NULL, 2)));
    KWD_LOOM_SUPPORT_DESCRIPTION = ((Keyword*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 2)));
    SYM_LOOM_SUPPORT_LOGIC_KAPPA = ((Symbol*)(internRigidSymbolWrtModule("KAPPA", getStellaModule("/LOGIC", true), 0)));
    SYM_LOOM_SUPPORT_LOOM_API_pD = ((Symbol*)(internRigidSymbolWrtModule("?D", NULL, 0)));
    SYM_LOOM_SUPPORT_LOOM_API_F_GET_DOMAIN_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("F-GET-DOMAIN-QUERY-000", NULL, 0)));
    SYM_LOOM_SUPPORT_PL_KERNEL_KB_RANGE = ((Symbol*)(internRigidSymbolWrtModule("RANGE", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_SUPPORT_LOOM_API_F_GET_RANGE_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("F-GET-RANGE-QUERY-000", NULL, 0)));
    SYM_LOOM_SUPPORT_LOGIC_pMDC = ((Symbol*)(internRigidSymbolWrtModule("?MDC", getStellaModule("/LOGIC", true), 0)));
    SYM_LOOM_SUPPORT_PL_KERNEL_KB_MEMBER_OF = ((Symbol*)(internRigidSymbolWrtModule("MEMBER-OF", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_SUPPORT_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION = ((Symbol*)(internRigidSymbolWrtModule("MUTUALLY-DISJOINT-COLLECTION", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_LOOM_SUPPORT_LOOM_API_F_GET_PARTITIONS_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("F-GET-PARTITIONS-QUERY-000", NULL, 0)));
    SGT_LOOM_SUPPORT_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION = ((Surrogate*)(internRigidSymbolWrtModule("MUTUALLY-DISJOINT-COLLECTION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_LOOM_SUPPORT_LOOM_API_pCOVERED = ((Symbol*)(internRigidSymbolWrtModule("?COVERED", NULL, 0)));
    SYM_LOOM_SUPPORT_PL_KERNEL_KB_COVERING = ((Symbol*)(internRigidSymbolWrtModule("COVERING", getStellaModule("/PL-KERNEL-KB", true), 0)));
  }
}

void helpStartupLoomSupport2() {
  {
    defineFunctionObject("SAFE-SURROGATIFY", "(DEFUN (SAFE-SURROGATIFY SURROGATE) ((SURROGATEREF OBJECT)))", ((cpp_function_code)(&safeSurrogatify)), NULL);
    defineFunctionObject("FIND-OR-CREATE-LOOM-ROLE", "(DEFUN (FIND-OR-CREATE-LOOM-ROLE LOOM-ROLE) ((INSTANCEREF OBJECT) (RELATIONREF OBJECT) (CREATE? BOOLEAN)) :DOCUMENTATION \"Return a LOOM-ROLE instance if 'instanceRef' has\na Loom role named 'relationRef'.  If 'create?', create a role\ninstance if one doesn't already exist.\")", ((cpp_function_code)(&findOrCreateLoomRole)), NULL);
    defineFunctionObject("GET-LOOM-ROLES", "(DEFUN (GET-LOOM-ROLES (CONS OF LOOM-ROLE)) ((INSTANCEREF OBJECT) (INFERROLES? BOOLEAN)) :DOCUMENTATION \"Return a list of LOOM-ROLEs on 'instanceRef'.  If\n'inferRoles', create roles on the fly corresponding to\nframe predicate or domain propositions inherited by 'instance'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getLoomRoles)), NULL);
    defineFunctionObject("GET-RELATION-INDUCED-ROLES", "(DEFUN (GET-RELATION-INDUCED-ROLES (CONS OF LOOM-ROLE)) ((INSTANCEREF OBJECT)))", ((cpp_function_code)(&getRelationInducedRoles)), NULL);
    defineFunctionObject("RELATION-OF-LOOM-ROLE", "(DEFUN (RELATION-OF-LOOM-ROLE NAMED-DESCRIPTION) ((ROLE LOOM-ROLE)) :DOCUMENTATION \"Return the relation for the Loom role 'role'.\")", ((cpp_function_code)(&relationOfLoomRole)), NULL);
    defineFunctionObject("GET-ROLE-NAMES-AND-VALUES", "(DEFUN (GET-ROLE-NAMES-AND-VALUES CONS) ((INSTANCEREF OBJECT)) :DOCUMENTATION \"Return a list of lists, with each sublist containing\na relation (role) name (a symbol) followed by one or more fillers of\nthat role on 'instanceRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getRoleNamesAndValues)), NULL);
    defineFunctionObject("GET-XCONTEXT", "(DEFUN (GET-XCONTEXT MODULE) ((CONTEXTREF OBJECT)) :DOCUMENTATION \"Return the module referenced by 'contextRef'.\")", ((cpp_function_code)(&getXcontext)), NULL);
    defineFunctionObject("GET-PARENT-CONTEXTS", "(DEFUN (GET-PARENT-CONTEXTS (CONS OF MODULE)) ((MODULEREF OBJECT)) :DOCUMENTATION \"Return a list of parent modules of 'moduleRef'.\")", ((cpp_function_code)(&getParentContexts)), NULL);
    defineFunctionObject("GET-CHILD-CONTEXTS", "(DEFUN (GET-CHILD-CONTEXTS (CONS OF MODULE)) ((MODULEREF OBJECT)) :DOCUMENTATION \"Return a list of child modules of 'moduleRef'.\")", ((cpp_function_code)(&getChildContexts)), NULL);
    defineFunctionObject("CONTEXT-OF-INSTANCE", "(DEFUN (CONTEXT-OF-INSTANCE MODULE) ((INSTANCEREF OBJECT)) :DOCUMENTATION \"Return the home context (a module) of 'instanceRef',\nor NULL if it is not context sensitive.\")", ((cpp_function_code)(&contextOfInstance)), NULL);
    defineFunctionObject("CLEAR-USER-CONTEXTS", "(DEFUN CLEAR-USER-CONTEXTS () :DOCUMENTATION \"Destroy the contents of all non-system-defined modules.\")", ((cpp_function_code)(&clearUserContexts)), NULL);
    defineFunctionObject("LIST-CONTEXT", "(DEFUN (LIST-CONTEXT CONS) ((CONTEXT MODULE) (VALUES KEYWORD)))", ((cpp_function_code)(&listContext)), NULL);
    defineFunctionObject("RELATION-ARITY", "(DEFUN (RELATION-ARITY INTEGER) ((RELATIONREF OBJECT)) :DOCUMENTATION \"Return the arity of the relation 'relationRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&relationArity)), NULL);
    defineFunctionObject("FIND-CLASS", "(DEFUN (FIND-CLASS LOGIC-OBJECT) ((INSTANCEREF OBJECT) (MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Return the nearest class with name 'instanceRef' in\nthe module 'module'.  If 'local?' is FALSE, also search modules inherited\nby 'module'.  'instanceRef' can be a string, symbol, or surrogate.\" :PUBLIC? TRUE)", ((cpp_function_code)(&findClass)), NULL);
    defineFunctionObject("FIND-RELATION", "(DEFUN (FIND-RELATION LOGIC-OBJECT) ((INSTANCEREF OBJECT) (MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Return the nearest relation with name 'instanceRef' in\nthe module 'module'.  If 'local?' is FALSE, also search modules inherited\nby 'module'.  'instanceRef' can be a string, symbol, or surrogate.\" :PUBLIC? TRUE)", ((cpp_function_code)(&findRelation)), NULL);
    defineFunctionObject("GET-INSTANCE-SURROGATE", "(DEFUN (GET-INSTANCE-SURROGATE SURROGATE) ((INSTANCEREF OBJECT)) :DOCUMENTATION \"Return the surrogate pointing to the instance referenced by\n'instanceRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getInstanceSurrogate)), NULL);
    defineFunctionObject("GET-INSTANCE-NAME", "(DEFUN (GET-INSTANCE-NAME SYMBOL) ((INSTANCEREF OBJECT)) :DOCUMENTATION \"Return the name (a symbol) of the instance referenced by\n'instanceRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getInstanceName)), NULL);
    defineFunctionObject("GET-EQUIVALENT-NAMES", "(DEFUN (GET-EQUIVALENT-NAMES (CONS OF SYMBOL)) ((RELATIONREF OBJECT)) :DOCUMENTATION \"Return a list containing the name of 'relationRef'\nplus the names of any equivalent relations.\")", ((cpp_function_code)(&getEquivalentNames)), NULL);
    defineFunctionObject("INSTANCE?", "(DEFUN (INSTANCE? BOOLEAN) ((OBJECTREF OBJECT)) :DOCUMENTATION \"Return TRUE if 'objectRef' is an instance or the\nname of an instance.\" :PUBLIC? TRUE)", ((cpp_function_code)(&instanceP)), NULL);
    defineFunctionObject("INDIVIDUAL?", "(DEFUN (INDIVIDUAL? BOOLEAN) ((OBJECT OBJECT)) :DOCUMENTATION \"Return TRUE if 'objectRef' is an instance or the\nname of an instance, and does not denote a relation, class, or set.\" :PUBLIC? TRUE)", ((cpp_function_code)(&individualP)), NULL);
    defineFunctionObject("NAMED?", "(DEFUN (NAMED? BOOLEAN) ((INSTANCEREF OBJECT)) :DOCUMENTATION \"Return TRUE if the object returned by 'instanceRef'\nis matched with a logical constant.\" :PUBLIC? TRUE)", ((cpp_function_code)(&namedP)), NULL);
    defineFunctionObject("CREATE-INSTANCE", "(DEFUN (CREATE-INSTANCE OBJECT) ((INSTANCEREF OBJECT) (CLASSREF OBJECT)) :DOCUMENTATION \"Create an instance named 'instanceRef'\nof type 'classRef'.\")", ((cpp_function_code)(&createInstance)), NULL);
    defineFunctionObject("FIND-OR-CREATE-INSTANCE", "(DEFUN (FIND-OR-CREATE-INSTANCE LOGIC-OBJECT) ((INSTANCEREF OBJECT) (CLASSREF OBJECT)) :DOCUMENTATION \"Find an existing instance refenced by 'instanceRef'\nof type 'classRef', or create one of type 'classRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&findOrCreateInstance)), NULL);
    defineFunctionObject("INSTANCE-OF?", "(DEFUN (INSTANCE-OF? BOOLEAN) ((INSTANCEREF OBJECT) (CLASSREF OBJECT)) :DOCUMENTATION \"Return TRUE if the instance referenced by 'instanceRef'\nbelongs to the class referenced by 'classRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&instanceOfP)), NULL);
    defineFunctionObject("ADD-TYPE", "(DEFUN ADD-TYPE ((INSTANCEREF OBJECT) (CLASSREF OBJECT)) :DOCUMENTATION \"Assert that the instance referenced by 'instanceRef'\nis an instance of the class referenced by 'classRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&addType)), NULL);
    defineFunctionObject("REMOVE-TYPE", "(DEFUN REMOVE-TYPE ((INSTANCEREF OBJECT) (CLASSREF OBJECT)) :DOCUMENTATION \"Retract that the instance referenced by 'instanceRef'\nis an instance of the class referenced by 'classRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&removeType)), NULL);
    defineFunctionObject("GET-TYPES", "(DEFUN (GET-TYPES (CONS OF DESCRIPTION)) ((INSTANCEREF OBJECT) (DIRECTORASSERTED KEYWORD)) :DOCUMENTATION \"Return a list of classes that instance belongs to.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getTypes)), NULL);
    defineFunctionObject("UPDATE-ROLE-VALUE", "(DEFUN UPDATE-ROLE-VALUE ((INSTANCEREF OBJECT) (RELATIONREF OBJECT) (VALUEREF OBJECT) (ASSERT? BOOLEAN)) :DOCUMENTATION \"Assert the tuple '(relationRef instanceRef valueRef)',\nor retract if 'assert?' is FALSE.\")", ((cpp_function_code)(&updateRoleValue)), NULL);
    defineFunctionObject("ADD-ROLE-VALUE", "(DEFUN ADD-ROLE-VALUE ((INSTANCEREF OBJECT) (RELATIONREF OBJECT) (VALUEREF OBJECT)) :DOCUMENTATION \"Assert the tuple '(relationRef instanceRef valueRef)'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&addRoleValue)), NULL);
    defineFunctionObject("REMOVE-ROLE-VALUE", "(DEFUN REMOVE-ROLE-VALUE ((INSTANCEREF OBJECT) (RELATIONREF OBJECT) (VALUEREF OBJECT)) :DOCUMENTATION \"Retract the tuple '(relationRef instanceRef valueRef)'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&removeRoleValue)), NULL);
    defineFunctionObject("GET-ROLE-VALUE", "(DEFUN (GET-ROLE-VALUE OBJECT) ((INSTANCEREF OBJECT) (RELATIONREF OBJECT)) :DOCUMENTATION \"Return a value for the binary relation 'relationRef'\napplied to 'instanceRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getRoleValue)), NULL);
    defineFunctionObject("GET-ROLE-VALUES", "(DEFUN (GET-ROLE-VALUES CONS) ((INSTANCEREF OBJECT) (RELATIONREF OBJECT)) :DOCUMENTATION \"Return a list of values for the binary relation 'relationRef'\napplied to 'instanceRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getRoleValues)), NULL);
    defineFunctionObject("GET-ROLE-DEFAULT-VALUES", "(DEFUN (GET-ROLE-DEFAULT-VALUES CONS) ((INSTANCEREF OBJECT) (RELATIONREF OBJECT)) :DOCUMENTATION \"Return a list of default values for the binary relation\n'relationRef' applied to 'instanceRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getRoleDefaultValues)), NULL);
    defineFunctionObject("GET-CLASS-INSTANCES", "(DEFUN (GET-CLASS-INSTANCES CONS) ((CLASSREF OBJECT) (DIRECT? BOOLEAN)) :DOCUMENTATION \"Return a list of instances belonging to the class 'classRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getClassInstances)), NULL);
    defineFunctionObject("SUBRELATION?", "(DEFUN (SUBRELATION? BOOLEAN) ((SUBRELATIONREF OBJECT) (SUPERRELATIONREF OBJECT)) :DOCUMENTATION \"Return TRUE if 'subrelationRef' specializes 'superrelationRef'.\nSide-effect: Upclassify 'subrelationRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&subrelationP)), NULL);
    defineFunctionObject("GET-SUPERRELATIONS", "(DEFUN (GET-SUPERRELATIONS (CONS OF LOGIC-OBJECT)) ((RELATIONREF OBJECT) (DIRECT? BOOLEAN)) :DOCUMENTATION \"Return a list of relations that generalize 'relationRef'.\nDoes not include relations equivalent to 'relationRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getSuperrelations)), NULL);
    defineFunctionObject("GET-SUBRELATIONS", "(DEFUN (GET-SUBRELATIONS (CONS OF LOGIC-OBJECT)) ((RELATIONREF OBJECT) (DIRECT? BOOLEAN)) :DOCUMENTATION \"Return a list of relations that specialize 'relationRef'.\nDoes not include relations equivalent to 'relationRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getSubrelations)), NULL);
    defineFunctionObject("MOST-SPECIFIC-RELATIONS", "(DEFUN (MOST-SPECIFIC-RELATIONS (CONS OF LOGIC-OBJECT)) ((RELATIONREFS CONS) (CLASSIFYFIRST? BOOLEAN)) :DOCUMENTATION \"Return a list of the most specific among the\nrelations in 'relationRefs'.  If 'classifyFirst?', insure that\nall relations are classified before filtering for most-specific.\" :PUBLIC? TRUE)", ((cpp_function_code)(&mostSpecificRelations)), NULL);
    defineFunctionObject("COMPUTE-CONJUNCTION-RELATION", "(DEFUN (COMPUTE-CONJUNCTION-RELATION DESCRIPTION) ((RELATIONREFS (CONS OF NAMED-DESCRIPTION))) :DOCUMENTATION \"Return a relation representing the conjunction\nof relations in 'relationRefs'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&computeConjunctionRelation)), NULL);
    defineFunctionObject("GET-DOMAIN", "(DEFUN (GET-DOMAIN NAMED-DESCRIPTION) ((RELATIONREF OBJECT)) :DOCUMENTATION \"Return the domain of the binary relation 'relationRef'.\")", ((cpp_function_code)(&getDomain)), NULL);
    defineFunctionObject("GET-RANGE", "(DEFUN (GET-RANGE NAMED-DESCRIPTION) ((RELATIONREF OBJECT)) :DOCUMENTATION \"Return the range of the binary relation 'relationRef'.\")", ((cpp_function_code)(&getRange)), NULL);
    defineFunctionObject("GET-MIN-CARDINALITY", "(DEFUN (GET-MIN-CARDINALITY INTEGER) ((INSTANCEREF OBJECT) (RELATIONREF OBJECT)) :DOCUMENTATION \"Infer a minimum cardinality for the set of fillers of\nthe range of relation 'relationRef' applied to 'instanceRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getMinCardinality)), NULL);
    defineFunctionObject("GET-MAX-CARDINALITY", "(DEFUN (GET-MAX-CARDINALITY INTEGER) ((INSTANCEREF OBJECT) (RELATIONREF OBJECT)) :DOCUMENTATION \"Infer a maximum cardinality for the set of fillers of\nthe range of relation 'relationRef' applied to 'instanceRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getMaxCardinality)), NULL);
    defineFunctionObject("GET-VALUE-RESTRICTION", "(DEFUN (GET-VALUE-RESTRICTION DESCRIPTION) ((INSTANCEREF OBJECT) (RELATIONREF OBJECT)) :DOCUMENTATION \"Infer a type restriction on the set of fillers of\nthe range of relation 'relationRef' applied to 'instanceRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getValueRestriction)), NULL);
    defineFunctionObject("ASSERT-LOOM-PROPOSITION", "(DEFUN ASSERT-LOOM-PROPOSITION ((LOOMSENTENCE CONS) (RETRACT? BOOLEAN)) :DOCUMENTATION \"Convert each Loom sentence into a KIF equivalent\nand assert it or retract it.\")", ((cpp_function_code)(&assertLoomProposition)), NULL);
    defineFunctionObject("DELETE-INSTANCE", "(DEFUN DELETE-INSTANCE ((INSTANCEREF OBJECT)) :DOCUMENTATION \"Destroy the instance, class or relation 'instanceRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&deleteInstance)), NULL);
    defineFunctionObject("GENERATE-SOURCE-EXPRESSION", "(DEFUN (GENERATE-SOURCE-EXPRESSION OBJECT) ((INSTANCEREF OBJECT)) :DOCUMENTATION \"Return an s-expression representing the\nsource expression for 'instanceRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&generateSourceExpression)), NULL);
    defineFunctionObject("GET-PARTITIONS", "(DEFUN (GET-PARTITIONS CONS) ((CLASSREF OBJECT)) :DOCUMENTATION \"Return a list of partitions that\nspecify disjointness of children of the class classRef'.\")", ((cpp_function_code)(&getPartitions)), NULL);
    defineFunctionObject("DISJOINT-RELATIONS?", "(DEFUN (DISJOINT-RELATIONS? BOOLEAN) ((RELATIONREF1 OBJECT) (RELATIONREF2 OBJECT)) :DOCUMENTATION \"Return TRUE if 'relationRef1' and 'relationRef2' are\ndisjoint.\" :PUBLIC? TRUE)", ((cpp_function_code)(&disjointRelationsP)), NULL);
    defineFunctionObject("COVERING?", "(DEFUN (COVERING? BOOLEAN) ((INSTANCEREF OBJECT) (CLASSREF OBJECT)) :DOCUMENTATION \"Return TRUE if the mutually disjoint collection 'instanceRef'\ncovers 'classRef'.  If 'classRef' is NULL, return TRUE if 'instanceRef' covers\nsome concept.\")", ((cpp_function_code)(&coveringP)), NULL);
    defineFunctionObject("COLLECTION-MEMBERS", "(DEFUN (COLLECTION-MEMBERS CONS) ((INSTANCEREF OBJECT)) :DOCUMENTATION \"Return a list of concepts that belong to the collection 'instanceRef'.\")", ((cpp_function_code)(&collectionMembers)), NULL);
    defineFunctionObject("STARTUP-LOOM-SUPPORT", "(DEFUN STARTUP-LOOM-SUPPORT () :PUBLIC? TRUE)", ((cpp_function_code)(&startupLoomSupport)), NULL);
    { MethodSlot* function = lookupFunction(SYM_LOOM_SUPPORT_LOOM_API_STARTUP_LOOM_SUPPORT);

      setDynamicSlotValue(function->dynamicSlots, SYM_LOOM_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupLoomSupport"), NULL_STRING_WRAPPER);
    }
  }
}

void startupLoomSupport() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/PL-KERNEL-KB/LOOM-API", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupLoomSupport1();
      SYM_LOOM_SUPPORT_LOOM_API_F_COVERINGp_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("F-COVERING?-QUERY-000", NULL, 0)));
      SYM_LOOM_SUPPORT_LOOM_API_STARTUP_LOOM_SUPPORT = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-LOOM-SUPPORT", NULL, 0)));
      SYM_LOOM_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(5)) {
      { stella::Class* clasS = defineClassFromStringifiedSource("LOOM-ROLE", "(DEFCLASS LOOM-ROLE (THING) :DOCUMENTATION \"\")");

        clasS->classConstructorCode = ((cpp_function_code)(&newLoomRole));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupLoomSupport2();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOOM-API")))));
      defrelation(consList(6, ((Symbol*)(copyConsTree(SYM_LOOM_SUPPORT_LOOM_API_LOOM_ROLE_OF))), ((Cons*)(copyConsTree(getQuotedTree("(((?C CLASS) (?R RELATION) (?ROLE LOOM-ROLE)) \"/PL-KERNEL-KB/LOOM-API\")", "/PL-KERNEL-KB/LOOM-API")))), KWD_LOOM_SUPPORT_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("")))), KWD_LOOM_SUPPORT_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((SINGLE-VALUED LOOM-ROLE-OF) \"/PL-KERNEL-KB/LOOM-API\")", "/PL-KERNEL-KB/LOOM-API"))))));
    }
  }
}

Surrogate* SGT_LOOM_SUPPORT_LOOM_API_LOOM_ROLE = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_LOOM_ROLE_OF = NULL;

Keyword* KWD_LOOM_SUPPORT_DOCUMENTATION = NULL;

Keyword* KWD_LOOM_SUPPORT_AXIOMS = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_pI = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_pR = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_pROLE = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_FIND_OR_CREATE_LOOM_ROLE_QUERY_000 = NULL;

Surrogate* SGT_LOOM_SUPPORT_LOOM_API_LOOM_ROLE_OF = NULL;

Symbol* SYM_LOOM_SUPPORT_STELLA_EXISTS = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_GET_LOOM_ROLES_QUERY_000 = NULL;

Symbol* SYM_LOOM_SUPPORT_STELLA_OR = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_pFR = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_pV = NULL;

Symbol* SYM_LOOM_SUPPORT_STELLA_AND = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_FRAME_PREDICATE = NULL;

Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_HOLDS = NULL;

Symbol* SYM_LOOM_SUPPORT_STELLA_NOT = NULL;

Symbol* SYM_LOOM_SUPPORT_STELLA_e = NULL;

Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_RANGE_MAX_CARDINALITY = NULL;

Symbol* SYM_LOOM_SUPPORT_LOGIC_pC = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_INSTANCE_OF = NULL;

Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_DOMAIN = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_GET_RELATION_INDUCED_ROLES_QUERY_000 = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_RELATION_OF_LOOM_ROLE_QUERY_000 = NULL;

Surrogate* SGT_LOOM_SUPPORT_STELLA_MODULE = NULL;

Surrogate* SGT_LOOM_SUPPORT_LOGIC_LOGIC_OBJECT = NULL;

Keyword* KWD_LOOM_SUPPORT_ALL = NULL;

Keyword* KWD_LOOM_SUPPORT_CONCEPTS = NULL;

Symbol* SYM_LOOM_SUPPORT_LOGIC_pX = NULL;

Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_CLASS = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_LIST_CONTEXT_QUERY_000 = NULL;

Keyword* KWD_LOOM_SUPPORT_RELATIONS = NULL;

Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_RELATION = NULL;

Symbol* SYM_LOOM_SUPPORT_LOGIC_FAIL = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_LIST_CONTEXT_QUERY_001 = NULL;

Keyword* KWD_LOOM_SUPPORT_INSTANCES = NULL;

Surrogate* SGT_LOOM_SUPPORT_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_LOOM_SUPPORT_PL_KERNEL_KB_ARITY = NULL;

Surrogate* SGT_LOOM_SUPPORT_STELLA_SURROGATE = NULL;

Surrogate* SGT_LOOM_SUPPORT_STELLA_THING = NULL;

Keyword* KWD_LOOM_SUPPORT_ASSERT_TRUE = NULL;

Keyword* KWD_LOOM_SUPPORT_RETRACT_TRUE = NULL;

Keyword* KWD_LOOM_SUPPORT_DIRECT = NULL;

Keyword* KWD_LOOM_SUPPORT_ASSERTED = NULL;

Keyword* KWD_LOOM_SUPPORT_DEFAULT = NULL;

Keyword* KWD_LOOM_SUPPORT_STRICT = NULL;

Keyword* KWD_LOOM_SUPPORT_DESCRIPTION = NULL;

Symbol* SYM_LOOM_SUPPORT_LOGIC_KAPPA = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_pD = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_GET_DOMAIN_QUERY_000 = NULL;

Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_RANGE = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_GET_RANGE_QUERY_000 = NULL;

Symbol* SYM_LOOM_SUPPORT_LOGIC_pMDC = NULL;

Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_MEMBER_OF = NULL;

Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_GET_PARTITIONS_QUERY_000 = NULL;

Surrogate* SGT_LOOM_SUPPORT_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_pCOVERED = NULL;

Symbol* SYM_LOOM_SUPPORT_PL_KERNEL_KB_COVERING = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_F_COVERINGp_QUERY_000 = NULL;

Symbol* SYM_LOOM_SUPPORT_LOOM_API_STARTUP_LOOM_SUPPORT = NULL;

Symbol* SYM_LOOM_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace pl_kernel_kb_pl_kernel_kb_loom_api
