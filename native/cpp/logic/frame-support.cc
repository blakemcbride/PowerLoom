//  -*- Mode: C++ -*-

// frame-support.cc

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

namespace logic {
  using namespace stella;

Object* coerceToInstanceInModule(Object* self, Module* module, boolean localP, Object* original) {
  if (!((boolean)(self))) {
    if (((boolean)(original))) {
      std::cout << "Can't find the entity referenced as: " << "`" << original << "'" << "." << std::endl;
    }
    return (NULL);
  }
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_FRAME_SUPPORT_LOGIC_LOGIC_OBJECT)) {
      { Object* self000 = self;
        LogicObject* self = ((LogicObject*)(self000));

        return (self);
      }
    }
    else if (subtypeOfStringP(testValue000)) {
      { Object* self001 = self;
        StringWrapper* self = ((StringWrapper*)(self001));

        { const char* name = self->wrapperValue;
          Module* modulefromstring = NULL;

          if (qualifiedStellaNameP(name)) {
            modulefromstring = computeModuleAndBareName(name, name);
          }
          if (!((boolean)(module))) {
            if (((boolean)(modulefromstring))) {
              module = modulefromstring;
            }
            else {
              module = oMODULEo;
            }
          }
          { Surrogate* surrogate = lookupSurrogateInModule(name, module, localP);

            if ((!((boolean)(surrogate))) ||
                (!((boolean)(surrogate->surrogateValue)))) {
              if (((boolean)(surrogate)) &&
                  ((boolean)(homeObjectStore(surrogate)))) {
                homeObjectStore(surrogate)->fetchInstance(surrogate);
              }
              else if ((!((boolean)(surrogate))) &&
                  ((boolean)(((ObjectStore*)(dynamicSlotValue(module->dynamicSlots, SYM_FRAME_SUPPORT_LOGIC_OBJECT_STORE, NULL)))))) {
                ((ObjectStore*)(dynamicSlotValue(module->dynamicSlots, SYM_FRAME_SUPPORT_LOGIC_OBJECT_STORE, NULL)))->fetchInstance(internSurrogateInModule(name, module, localP));
              }
            }
            if (((boolean)(surrogate)) &&
                ((boolean)(surrogate->surrogateValue))) {
              return (coerceToInstanceInModule(surrogate, module, true, original));
            }
            else {
              return (NULL);
            }
          }
        }
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* self002 = self;
        Symbol* self = ((Symbol*)(self002));

        { Module* startingmodule = (((boolean)(module)) ? module : ((Module*)(self->homeContext)));
          Object* value = coerceToInstanceInModule(lookupSurrogateInModule(self->symbolName, startingmodule, localP), NULL, localP, NULL);

          if (((boolean)(value))) {
            return (value);
          }
          else if (!(module == oMODULEo)) {
            return (coerceToInstanceInModule(lookupSurrogateInModule(self->symbolName, oMODULEo, localP), oMODULEo, localP, original));
          }
          else if (((boolean)(original))) {
            return (coerceToInstanceInModule(NULL, NULL, false, original));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* self003 = self;
        Surrogate* self = ((Surrogate*)(self003));

        { Object* value = self->surrogateValue;

          if (((boolean)(value))) {
            return (coerceToInstanceInModule(value, NULL, true, original));
          }
          else {
            return (coerceToInstanceInModule(wrapString(self->symbolName), ((Module*)(self->homeContext)), localP, original));
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_FRAME_SUPPORT_STELLA_RELATION)) {
      { Object* self004 = self;
        Relation* self = ((Relation*)(self004));

        return (getDescription(self));
      }
    }
    else if (subtypeOfKeywordP(testValue000)) {
      { Object* self005 = self;
        Keyword* self = ((Keyword*)(self005));

        return (coerceToInstanceInModule(wrapString(self->symbolName), module, localP, original));
      }
    }
    else if (subtypeOfP(testValue000, SGT_FRAME_SUPPORT_STELLA_THING)) {
      { Object* self006 = self;
        Thing* self = ((Thing*)(self006));

        return (self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_FRAME_SUPPORT_LOGIC_PROPOSITION)) {
      { Object* self007 = self;
        Proposition* self = ((Proposition*)(self007));

        return (self);
      }
    }
    else {
      return (coerceToInstanceInModule(NULL, NULL, false, original));
    }
  }
}

Object* getInstance(Object* instanceref) {
  // Return the nearest instance with name 'instanceRef'
  // visible from the current module.  'instanceRef' can be a string, symbol,
  // or surrogate.  If 'instanceRef' is a surrogate, the search originates
  // in the module the surrogate was interned in.
  if (!((boolean)(instanceref))) {
    return (NULL);
  }
  else if (isaP(instanceref, SGT_FRAME_SUPPORT_LOGIC_LOGIC_OBJECT)) {
    return (instanceref);
  }
  else {
    return (coerceToInstanceInModule(instanceref, NULL, false, NULL));
  }
}

Object* findInstance(Object* instanceref) {
  // Return the nearest instance with name 'instanceRef'
  // visible from the current module.  'instanceRef' can be a string, symbol,
  // or surrogate.  If 'instanceRef' is a surrogate, the search originates
  // in the module the surrogate was interned in.
  return (getInstance(instanceref));
}

LogicObject* getSelfOrPrototype(Object* instanceref) {
  // Used to convert a computation to reference so-called
  // 'template' slots rather than 'own' slots:  If 'instanceRef' denotes a class,
  // return a prototype of that class.  Otherwise, return 'instanceRef'.
  return ((classP(instanceref) ? getPrototype(((Description*)(instanceref))) : ((LogicObject*)(instanceref))));
}

LogicObject* getClass(Object* instanceref) {
  // Return the nearest class with name 'instanceRef'
  // visible from the current module.  'instanceRef' can be a string, symbol,
  // or surrogate.  If 'instanceRef' is a surrogate, the search originates
  // in the module the surrogate was interned in.
  { Object* instance = coerceToInstanceInModule(instanceref, NULL, false, NULL);

    if (classP(instance)) {
      return (((LogicObject*)(instance)));
    }
    else {
      return (NULL);
    }
  }
}

LogicObject* getRelation(Object* instanceref) {
  // Return the nearest relation with name 'instanceRef'
  // visible from the current module.  'instanceRef' can be a string, symbol,
  // or surrogate.  If 'instanceRef' is a surrogate, the search originates
  // in the module the surrogate was interned in.
  { Object* instance = coerceToInstanceInModule(instanceref, NULL, false, NULL);

    if (relationP(instance)) {
      return (((LogicObject*)(instance)));
    }
    else {
      return (NULL);
    }
  }
}

Module* getModule(Object* moduleref) {
  // Return a module named 'moduleRef'.
  { Surrogate* testValue000 = safePrimaryType(moduleref);

    if (subtypeOfStringP(testValue000)) {
      { Object* moduleref000 = moduleref;
        StringWrapper* moduleref = ((StringWrapper*)(moduleref000));

        return (getStellaModule(moduleref->wrapperValue, false));
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* moduleref001 = moduleref;
        Surrogate* moduleref = ((Surrogate*)(moduleref001));

        return (getStellaModule(moduleref->symbolName, false));
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* moduleref002 = moduleref;
        Symbol* moduleref = ((Symbol*)(moduleref002));

        return (getStellaModule(moduleref->symbolName, false));
      }
    }
    else if (subtypeOfP(testValue000, SGT_FRAME_SUPPORT_STELLA_MODULE)) {
      { Object* moduleref003 = moduleref;
        Module* moduleref = ((Module*)(moduleref003));

        return (moduleref);
      }
    }
    else {
      return (NULL);
    }
  }
}

boolean collectionP(Object* objectref) {
  // Return TRUE if 'objectRef' denotes a relation or a class.
  { Object* instance = getInstance(objectref);

    if (!((boolean)(instance))) {
      return (false);
    }
    if (subtypeOfP(safePrimaryType(instance), SGT_FRAME_SUPPORT_LOGIC_LOGIC_OBJECT)) {
      { Object* instance000 = instance;
        LogicObject* instance = ((LogicObject*)(instance000));

        return (testIsaP(instance, SGT_FRAME_SUPPORT_PL_KERNEL_KB_COLLECTION));
      }
    }
    else {
      return (false);
    }
  }
}

boolean classP(Object* objectref) {
  // Return TRUE if 'objectRef' denotes a class.
  { Object* instance = getInstance(objectref);

    if (!((boolean)(instance))) {
      return (false);
    }
    else {
      return (testIsaP(instance, SGT_FRAME_SUPPORT_PL_KERNEL_KB_CLASS));
    }
  }
}

boolean relationP(Object* objectref) {
  // Return TRUE if 'objectRef' denotes a relation or a class.
  { Object* instance = getInstance(objectref);

    if (!((boolean)(instance))) {
      return (false);
    }
    else {
      return (testIsaP(instance, SGT_FRAME_SUPPORT_PL_KERNEL_KB_RELATION));
    }
  }
}

boolean functionP(Object* relationref) {
  // Return TRUE if 'relationRef' references a function.
  { Object* instance = getInstance(relationref);

    if ((!((boolean)(instance))) ||
        (!((boolean)(SGT_FRAME_SUPPORT_PL_KERNEL_KB_FUNCTION->surrogateValue)))) {
      return (false);
    }
    else {
      return (testIsaP(instance, SGT_FRAME_SUPPORT_PL_KERNEL_KB_FUNCTION));
    }
  }
}

boolean constantP(Object* objectref) {
  // Return TRUE if `objectRef' denotes a literal or scalar.
  { Surrogate* testValue000 = safePrimaryType(objectref);

    if (subtypeOfP(testValue000, SGT_FRAME_SUPPORT_STELLA_LITERAL_WRAPPER)) {
      { Object* objectref000 = objectref;
        LiteralWrapper* objectref = ((LiteralWrapper*)(objectref000));

        return (true);
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* objectref001 = objectref;
        Surrogate* objectref = ((Surrogate*)(objectref001));

        return (constantP(objectref->surrogateValue));
      }
    }
    else if (subtypeOfP(testValue000, SGT_FRAME_SUPPORT_STELLA_THING)) {
      { Object* objectref002 = objectref;
        Thing* objectref = ((Thing*)(objectref002));

        return (testIsaP(objectref, SGT_FRAME_SUPPORT_STELLA_LITERAL) ||
            testIsaP(objectref, SGT_FRAME_SUPPORT_PL_KERNEL_KB_SCALAR));
      }
    }
    else if (subtypeOfP(testValue000, SGT_FRAME_SUPPORT_LOGIC_LOGIC_OBJECT)) {
      { Object* objectref003 = objectref;
        LogicObject* objectref = ((LogicObject*)(objectref003));

        return (testIsaP(objectref, SGT_FRAME_SUPPORT_STELLA_LITERAL) ||
            testIsaP(objectref, SGT_FRAME_SUPPORT_PL_KERNEL_KB_SCALAR));
      }
    }
    else {
      return (false);
    }
  }
}

const char* relationName(NamedDescription* self) {
  // Given a relation object, return it's name.
  return (self->surrogateValueInverse->symbolName);
}

Object* termify(Object* self) {
  // Convert 'self' into an equivalent PowerLoom object
  // that can be passed as an argument wherever an instance is expected.
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_FRAME_SUPPORT_STELLA_LITERAL_WRAPPER)) {
      { Object* self000 = self;
        LiteralWrapper* self = ((LiteralWrapper*)(self000));

        return (((LiteralWrapper*)(self->permanentify())));
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* self001 = self;
        Surrogate* self = ((Surrogate*)(self001));

        if (((boolean)(self->surrogateValue))) {
          return (valueOf(self->surrogateValue));
        }
        std::cout << "Can't termify the surrogate 'self' because it is undefined.";
        return (NULL);
      }
    }
    else if (subtypeOfP(testValue000, SGT_FRAME_SUPPORT_LOGIC_LOGIC_OBJECT)) {
      { Object* self002 = self;
        LogicObject* self = ((LogicObject*)(self002));

        return (valueOf(self));
      }
    }
    else if (subtypeOfP(testValue000, SGT_FRAME_SUPPORT_STELLA_THING)) {
      { Object* self003 = self;
        Thing* self = ((Thing*)(self003));

        return (self);
      }
    }
    else {
      std::cout << "Can't 'termify': " << self;
      return (NULL);
    }
  }
}

boolean relationArityOkP(Surrogate* relationref, int arity) {
  { NamedDescription* relation = getDescription(relationref);

    if (!((boolean)(relation))) {
      std::cout << "Reference to undefined relation " << relationref->symbolName << std::endl;
      return (false);
    }
    if (!(relation->arity() == arity)) {
      std::cout << "Error:  Relation " << relationref->symbolName << " has arity " << relation->arity() << std::endl << "   when arity " << arity << " expected." << std::endl;
      return (false);
    }
    return (true);
  }
}

Cons* filterOutUnnamedDescriptions(Cons* descriptions) {
  { Cons* namedones = NIL;

    { LogicObject* d = NULL;
      Cons* iter000 = descriptions;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        d = ((LogicObject*)(iter000->value));
        if (isaP(d, SGT_FRAME_SUPPORT_LOGIC_NAMED_DESCRIPTION)) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(d, NIL);
              if (namedones == NIL) {
                namedones = collect000;
              }
              else {
                addConsToEndOfConsList(namedones, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(d, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (namedones);
  }
}

Cons* allAssertedTypes(Object* self) {
  // Return a set of all of the types that are
  // asserted to be satisfied by 'self'.
  { Cons* types = NIL;

    { Proposition* p = NULL;
      Iterator* iter000 = allTrueDependentIsaPropositions(self);

      for (; iter000->nextP(); ) {
        p = ((Proposition*)(iter000->value));
        { NamedDescription* description = getDescription(((Surrogate*)(p->operatoR)));

          if (!types->memberP(description)) {
            types = cons(description, types);
          }
        }
      }
    }
    return (types);
  }
}

Cons* allTaxonomicTypes(Object* self) {
  // Return a set of all of the types that are
  // satisfied by 'self', using only assertions and upward
  // taxonomic reasoning.
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_FRAME_SUPPORT_LOGIC_F_ALL_TAXONOMIC_TYPES_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_FRAME_SUPPORT_LOGIC_F_ALL_TAXONOMIC_TYPES_MEMO_TABLE_000, "(:MAX-VALUES 500 :TIMESTAMPS (:KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_FRAME_SUPPORT_LOGIC_F_ALL_TAXONOMIC_TYPES_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), self, oCONTEXTo, MEMOIZED_NULL_VALUE, NULL, 2);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = helpAllTypes(self, false);
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Cons* value000 = ((Cons*)(memoizedValue000));

      return (value000);
    }
  }
}

Cons* allTypes(Object* self) {
  // Return a set of all of the types that are
  // satisfied by 'self'.
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_FRAME_SUPPORT_LOGIC_F_ALL_TYPES_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_FRAME_SUPPORT_LOGIC_F_ALL_TYPES_MEMO_TABLE_000, "(:MAX-VALUES 500 :TIMESTAMPS (:KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_FRAME_SUPPORT_LOGIC_F_ALL_TYPES_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), self, oCONTEXTo, MEMOIZED_NULL_VALUE, NULL, 2);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = helpAllTypes(self, true);
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Cons* value000 = ((Cons*)(memoizedValue000));

      return (value000);
    }
  }
}

Cons* helpAllTypes(Object* self, boolean doSubtypesP) {
  { Cons* assertedtypes = allAssertedTypes(self);

    { List* self000 = newList();

      self000->theConsList = copyConsList(assertedtypes);
      { List* types = self000;

        { NamedDescription* d = NULL;
          Cons* iter000 = assertedtypes;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            d = ((NamedDescription*)(iter000->value));
            { LogicObject* c = NULL;
              Iterator* iter001 = allSupercollections(d);

              for (; iter001->nextP(); ) {
                c = ((LogicObject*)(iter001->value));
                if (isaP(c, SGT_FRAME_SUPPORT_LOGIC_NAMED_DESCRIPTION)) {
                  if (!types->memberP(c)) {
                    types->push(c);
                  }
                }
              }
            }
            if (doSubtypesP) {
              helpAllSubtypes(d, self, types);
            }
          }
        }
        return (((Cons*)(types->theConsList)));
      }
    }
  }
}

void helpAllSubtypes(Description* super, Object* self, List* types) {
  { LogicObject* c = NULL;
    Iterator* iter000 = allDirectSubcollections(super, true);

    for (; iter000->nextP(); ) {
      c = ((LogicObject*)(iter000->value));
      if (isaP(c, SGT_FRAME_SUPPORT_LOGIC_NAMED_DESCRIPTION)) {
        if ((!types->memberP(c)) &&
            testTypeOnInstanceP(self, ((NamedDescription*)(c))->surrogateValueInverse)) {
          types->insertNew(c);
          helpAllSubtypes(((Description*)(c)), self, types);
        }
      }
      else {
        helpAllSubtypes(((Description*)(c)), self, types);
      }
    }
  }
}

Cons* allDirectTypes(Object* self) {
  // Return a set of most specific types that are satisfied by 'self'.
  return (mostSpecificNamedDescriptions(copyConsList(allTypes(self))));
}

boolean testTypeOnInstanceP(Object* self, Surrogate* type) {
  // Return TRUE if 'self' satisfies 'type'.
  return (currentInferenceLevel()->levellizedTestTypeOnInstanceP(self, type));
}

boolean SubsumptionInferenceLevel::levellizedTestTypeOnInstanceP(Object* self, Surrogate* type) {
  { SubsumptionInferenceLevel* level = this;

    { boolean foundP000 = false;

      { Proposition* p = NULL;
        Iterator* iter000 = allTrueDependentPropositions(self, type, true);

        for (; iter000->nextP(); ) {
          p = ((Proposition*)(iter000->value));
          if (p->kind == KWD_FRAME_SUPPORT_ISA) {
            foundP000 = true;
            break;
          }
        }
      }
      { boolean value000 = foundP000;

        return (value000);
      }
    }
  }
}

boolean ShallowInferenceLevel::levellizedTestTypeOnInstanceP(Object* self, Surrogate* type) {
  { ShallowInferenceLevel* level = this;

    { boolean foundP000 = false;

      { Proposition* p = NULL;
        Iterator* iter000 = allTrueDependentPropositions(self, type, false);

        for (; iter000->nextP(); ) {
          p = ((Proposition*)(iter000->value));
          if (p->kind == KWD_FRAME_SUPPORT_ISA) {
            foundP000 = true;
            break;
          }
        }
      }
      { boolean value000 = foundP000;

        return (value000);
      }
    }
  }
}

Cons* allEquivalentRelations(NamedDescription* relation, boolean reflexiveP) {
  // Return a list of all relations equivalent to 'relation'.
  // If 'reflexive?', include 'relation' in the list.
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_FRAME_SUPPORT_LOGIC_F_ALL_EQUIVALENT_RELATIONS_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_FRAME_SUPPORT_LOGIC_F_ALL_EQUIVALENT_RELATIONS_MEMO_TABLE_000, "(:MAX-VALUES 500 :TIMESTAMPS (:META-KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_FRAME_SUPPORT_LOGIC_F_ALL_EQUIVALENT_RELATIONS_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), relation, oCONTEXTo, (reflexiveP ? TRUE_WRAPPER : FALSE_WRAPPER), MEMOIZED_NULL_VALUE, -1);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = filterOutUnnamedDescriptions(allEquivalentCollections(relation, reflexiveP));
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Cons* value000 = ((Cons*)(memoizedValue000));

      return (value000);
    }
  }
}

Cons* removeEquivalentRelations(Cons* relationslist, NamedDescription* relation) {
  if (relationslist->memberP(relation)) {
    { NamedDescription* m = NULL;
      Cons* iter000 = allEquivalentRelations(relation, true);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        m = ((NamedDescription*)(iter000->value));
        relationslist = relationslist->remove(m);
      }
    }
  }
  return (relationslist);
}

Cons* helpMemoizeAllSuperrelations(NamedDescription* relation, boolean removeequivalentsP) {
  { Cons* superslots = filterOutUnnamedDescriptions(allSupercollections(relation)->consify());

    if (removeequivalentsP) {
      return (removeEquivalentRelations(superslots, relation));
    }
    else {
      return (superslots);
    }
  }
}

Cons* allSuperrelations(NamedDescription* relation, boolean removeequivalentsP) {
  // Return a set of all relations that subsume relation.
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_FRAME_SUPPORT_LOGIC_F_ALL_SUPERRELATIONS_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_FRAME_SUPPORT_LOGIC_F_ALL_SUPERRELATIONS_MEMO_TABLE_000, "(:MAX-VALUES 500 :TIMESTAMPS (:META-KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_FRAME_SUPPORT_LOGIC_F_ALL_SUPERRELATIONS_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), relation, oCONTEXTo, (removeequivalentsP ? TRUE_WRAPPER : FALSE_WRAPPER), MEMOIZED_NULL_VALUE, -1);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = helpMemoizeAllSuperrelations(relation, removeequivalentsP);
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Cons* value000 = ((Cons*)(memoizedValue000));

      return (value000);
    }
  }
}

Cons* helpMemoizeAllSubrelations(NamedDescription* relation, boolean removeequivalentsP) {
  { Cons* subslots = filterOutUnnamedDescriptions(allSubcollections(relation)->consify());

    if (removeequivalentsP) {
      return (removeEquivalentRelations(subslots, relation));
    }
    else {
      return (subslots);
    }
  }
}

Cons* allSubrelations(NamedDescription* relation, boolean removeequivalentsP) {
  // Return a set of all (named) relations that specialize
  // relation.
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_FRAME_SUPPORT_LOGIC_F_ALL_SUBRELATIONS_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_FRAME_SUPPORT_LOGIC_F_ALL_SUBRELATIONS_MEMO_TABLE_000, "(:MAX-VALUES 1000 :TIMESTAMPS (:META-KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_FRAME_SUPPORT_LOGIC_F_ALL_SUBRELATIONS_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), relation, oCONTEXTo, (removeequivalentsP ? TRUE_WRAPPER : FALSE_WRAPPER), MEMOIZED_NULL_VALUE, -1);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = helpMemoizeAllSubrelations(relation, removeequivalentsP);
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Cons* value000 = ((Cons*)(memoizedValue000));

      return (value000);
    }
  }
}

Cons* allDirectSuperrelations(NamedDescription* relation, boolean removeequivalentsP) {
  // Return a set of relations that immediately subsume
  // 'relation'.  If 'removeEquivalents?' (recommended), don't include any
  // relations equivalent to 'relation'.
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_FRAME_SUPPORT_LOGIC_F_ALL_DIRECT_SUPERRELATIONS_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_FRAME_SUPPORT_LOGIC_F_ALL_DIRECT_SUPERRELATIONS_MEMO_TABLE_000, "(:MAX-VALUES 500 :TIMESTAMPS (:META-KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_FRAME_SUPPORT_LOGIC_F_ALL_DIRECT_SUPERRELATIONS_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), relation, oCONTEXTo, (removeequivalentsP ? TRUE_WRAPPER : FALSE_WRAPPER), MEMOIZED_NULL_VALUE, -1);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = filterOutUnnamedDescriptions(allDirectSupercollections(relation, removeequivalentsP)->consify());
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Cons* value000 = ((Cons*)(memoizedValue000));

      return (value000);
    }
  }
}

Cons* allDirectSubrelations(NamedDescription* relation, boolean removeequivalentsP) {
  // Return a set of relations that immediately specialize
  // 'relation'.  If 'removeEquivalents?' (recommended), don't include any
  // relations equivalent to 'relation'.
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_FRAME_SUPPORT_LOGIC_F_ALL_DIRECT_SUBRELATIONS_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_FRAME_SUPPORT_LOGIC_F_ALL_DIRECT_SUBRELATIONS_MEMO_TABLE_000, "(:MAX-VALUES 500 :TIMESTAMPS (:META-KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_FRAME_SUPPORT_LOGIC_F_ALL_DIRECT_SUBRELATIONS_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), relation, oCONTEXTo, (removeequivalentsP ? TRUE_WRAPPER : FALSE_WRAPPER), MEMOIZED_NULL_VALUE, -1);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = filterOutUnnamedDescriptions(allDirectSubcollections(relation, removeequivalentsP)->consify());
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Cons* value000 = ((Cons*)(memoizedValue000));

      return (value000);
    }
  }
}

boolean testSubrelationP(Surrogate* subrelation, Surrogate* superrelation) {
  // Return TRUE if 'subrelation' specializes 'superrelation'.
  if (subrelation == superrelation) {
    return (true);
  }
  { NamedDescription* description = getDescription(subrelation);

    { boolean foundP000 = false;

      { LogicObject* super = NULL;
        Iterator* iter000 = allSupercollections(description);

        for (; iter000->nextP(); ) {
          super = ((LogicObject*)(iter000->value));
          if (super->surrogateValueInverse == superrelation) {
            foundP000 = true;
            break;
          }
        }
      }
      { boolean value000 = foundP000;

        return (value000);
      }
    }
  }
}

Cons* allClassInstances(Surrogate* type) {
  // Return a set of instances that belong to the class 'type'.
  return (currentInferenceLevel()->levellizedAllClassInstances(type)->removeDuplicates());
}

Cons* SubsumptionInferenceLevel::levellizedAllClassInstances(Surrogate* type) {
  { SubsumptionInferenceLevel* level = this;

    { Cons* members = NIL;

      { Object* m = NULL;
        Cons* iter000 = assertedCollectionMembers(getDescription(type), false)->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          m = iter000->value;
          members = cons(m, members);
        }
      }
      return (members);
    }
  }
}

Cons* AssertionInferenceLevel::levellizedAllClassInstances(Surrogate* type) {
  { AssertionInferenceLevel* level = this;

    { Cons* members = NIL;

      { Object* m = NULL;
        Cons* iter000 = assertedCollectionMembers(getDescription(type), true)->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          m = iter000->value;
          if (level->levellizedTestTypeOnInstanceP(m, type)) {
            members = cons(m, members);
          }
        }
      }
      return (members);
    }
  }
}

Cons* allRelationValues(Surrogate* relation, Cons* nminusonearguments) {
  // Return a set of values that satisfy the relation
  // 'relation' (a surrogate) applied to 'nMinusOneArguments' plus that last value.
  if (!relationArityOkP(relation, nminusonearguments->length() + 1)) {
    return (NIL);
  }
  return (currentInferenceLevel()->levellizedAllRelationValues(relation, nminusonearguments));
}

Cons* SubsumptionInferenceLevel::levellizedAllRelationValues(Surrogate* relation, Cons* nminusonearguments) {
  { SubsumptionInferenceLevel* level = this;

    { Cons* values = NIL;

      { Proposition* p = NULL;
        Cons* iter000 = allPropositionsMatchingArguments(nminusonearguments, relation, level == SUBSUMPTION_INFERENCE);

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          p = ((Proposition*)(iter000->value));
          { Object* value000 = valueOf((p->arguments->theArray)[(p->arguments->length() - 1)]);

            values = (values->memberP(value000) ? values : cons(value000, values));
          }
        }
      }
      return (values);
    }
  }
}

boolean testRelationOnArgumentsP(Surrogate* relation, Cons* arguments) {
  // Return TRUE if 'relation' (a surrogate) is TRUE when
  // applied to 'arguments'.
  if (!relationArityOkP(relation, arguments->length())) {
    return (false);
  }
  return (currentInferenceLevel()->levellizedTestRelationOnArgumentsP(relation, arguments));
}

boolean SubsumptionInferenceLevel::levellizedTestRelationOnArgumentsP(Surrogate* relation, Cons* arguments) {
  { SubsumptionInferenceLevel* level = this;

    { boolean foundP000 = false;

      { ConsIterator* p = allPropositionsMatchingArguments(arguments, relation, level == SUBSUMPTION_INFERENCE)->allocateIterator();

        for (; p->nextP(); ) {
          foundP000 = true;
          break;
        }
      }
      { boolean value000 = foundP000;

        return (value000);
      }
    }
  }
}

Cons* allSlotValues(LogicObject* self, Surrogate* relation) {
  // Return a set of values for the slot 'relation' (a surrogate)
  // applied to 'self' (an object).
  return (allRelationValues(relation, consList(1, self)));
}

Object* getSlotValue(LogicObject* self, Surrogate* relation) {
  // Return a single value for the slot 'relation' (a surrogate)
  // applied to 'self' (an object).
  return (allSlotValues(self, relation)->value);
}

boolean testSlotValueP(LogicObject* self, Surrogate* relation, Object* filler) {
  // Return TRUE if the proposition '(<relation> <self> <filler>)'
  // is true.
  return (testRelationOnArgumentsP(relation, consList(2, self, filler)));
}

int getSlotMinimumCardinality(LogicObject* self, Surrogate* relation) {
  // Return a minimum value for the number of fillers of relation
  // 'relation' (a surrogate) applied to the instance 'self' (an object).
  return (currentInferenceLevel()->levellizedGetSlotMinimumCardinality(self, relation));
}

int ShallowInferenceLevel::levellizedGetSlotMinimumCardinality(LogicObject* self, Surrogate* relation) {
  { ShallowInferenceLevel* level = this;

    { NamedDescription* description = getDescription(relation);
      Object* mincardinality = allRelationValues(SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_MIN_CARDINALITY, consList(2, description, self))->value;
      int fillercount = allSlotValues(self, relation)->length();

      if (!((boolean)(mincardinality))) {
        mincardinality = wrapInteger(0);
      }
      return (stella::integerMax(fillercount, ((IntegerWrapper*)(mincardinality))->wrapperValue));
    }
  }
}

int SubsumptionInferenceLevel::levellizedGetSlotMinimumCardinality(LogicObject* self, Surrogate* relation) {
  { SubsumptionInferenceLevel* level = this;

    { int mincardinality = SHALLOW_INFERENCE->levellizedGetSlotMinimumCardinality(self, relation);

      { NamedDescription* subdescription = NULL;
        Cons* iter000 = allSubrelations(getDescription(relation), false);

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          subdescription = ((NamedDescription*)(iter000->value));
          { Object* submincardinality = allRelationValues(SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_MIN_CARDINALITY, consList(2, subdescription, self))->value;

            if (((boolean)(submincardinality))) {
              mincardinality = stella::integerMax(mincardinality, ((IntegerWrapper*)(submincardinality))->wrapperValue);
            }
          }
        }
      }
      return (mincardinality);
    }
  }
}

boolean testClosedSlotP(Surrogate* relation) {
  // Return TRUE if 'relation' (a surrogate) is asserted to 
  // be closed or if the current module closes all relations.
  return (closedTermP(getDescription(relation)));
}

boolean testFunctionSlotP(Surrogate* relation) {
  // Return TRUE if 'relation' (a surrogate) is a function.
  return (functionDescriptionP(getDescription(relation)));
}

int getSlotMaximumCardinality(LogicObject* self, Surrogate* relation) {
  // Return a maximum value for the number of fillers of relation
  // 'relation' (a surrogate) applied to the instance 'self' (an object).
  return (currentInferenceLevel()->levellizedGetSlotMaximumCardinality(self, relation));
}

int ShallowInferenceLevel::levellizedGetSlotMaximumCardinality(LogicObject* self, Surrogate* relation) {
  { ShallowInferenceLevel* level = this;

    { NamedDescription* description = getDescription(relation);
      Object* maxcardinality = allRelationValues(SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_MAX_CARDINALITY, consList(2, description, self))->value;
      int fillercount = NULL_INTEGER;

      if (testClosedSlotP(relation)) {
        fillercount = allSlotValues(self, relation)->length();
      }
      else if (testFunctionSlotP(relation)) {
        fillercount = 1;
      }
      if (!((boolean)(maxcardinality))) {
        return (fillercount);
      }
      else if (fillercount == NULL_INTEGER) {
        return (((IntegerWrapper*)(maxcardinality))->wrapperValue);
      }
      else {
        return (stella::integerMin(fillercount, ((IntegerWrapper*)(maxcardinality))->wrapperValue));
      }
    }
  }
}

int SubsumptionInferenceLevel::levellizedGetSlotMaximumCardinality(LogicObject* self, Surrogate* relation) {
  { SubsumptionInferenceLevel* level = this;

    { int maxcardinality = SHALLOW_INFERENCE->levellizedGetSlotMaximumCardinality(self, relation);

      { NamedDescription* superdescription = NULL;
        Cons* iter000 = allSuperrelations(getDescription(relation), false);

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          superdescription = ((NamedDescription*)(iter000->value));
          { Object* supermaxcardinality = allRelationValues(SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_MAX_CARDINALITY, consList(2, superdescription, self))->value;

            if (((boolean)(supermaxcardinality))) {
              if (maxcardinality != NULL_INTEGER) {
                maxcardinality = stella::integerMin(maxcardinality, ((IntegerWrapper*)(supermaxcardinality))->wrapperValue);
              }
              else {
                maxcardinality = ((IntegerWrapper*)(supermaxcardinality))->wrapperValue;
              }
            }
          }
        }
      }
      return (maxcardinality);
    }
  }
}

NamedDescription* getSlotValueType(LogicObject* self, Surrogate* relation) {
  // Return a most specific type for fillers of the slot 'relation'
  // (a surrogate) applied to 'self'. If there is more than one, pick one.
  return (((NamedDescription*)(allSlotValueTypes(self, relation)->value)));
}

Cons* allSlotValueTypes(LogicObject* self, Surrogate* relation) {
  // Return a set of the most specific types for fillers
  // of the slot 'relation' applied to 'self'.
  return (mostSpecificNamedDescriptions(copyConsList(currentInferenceLevel()->levellizedAllSlotValueTypes(self, relation))));
}

Cons* ShallowInferenceLevel::levellizedAllSlotValueTypes(LogicObject* self, Surrogate* relation) {
  { ShallowInferenceLevel* level = this;

    { NamedDescription* description = getDescription(relation);
      Cons* valuetypes = allRelationValues(SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_TYPE, consList(2, description, self));

      if (testClosedSlotP(relation) ||
          testFunctionSlotP(relation)) {
        { Cons* fillers = allSlotValues(self, relation);
          Cons* possibletypes = NIL;

          { Object* f = NULL;
            Cons* iter000 = fillers;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              f = iter000->value;
              { NamedDescription* d = NULL;
                Cons* iter001 = allAssertedTypes(f);

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  d = ((NamedDescription*)(iter001->value));
                  if (!possibletypes->memberP(d)) {
                    possibletypes = cons(d, possibletypes);
                  }
                }
              }
            }
          }
          { LogicObject* d = NULL;
            Cons* iter002 = possibletypes;

            for (; !(iter002 == NIL); iter002 = iter002->rest) {
              d = ((LogicObject*)(iter002->value));
              { boolean testValue000 = false;

                testValue000 = !valuetypes->memberP(d);
                if (testValue000) {
                  { boolean alwaysP000 = true;

                    { Object* f = NULL;
                      Cons* iter003 = fillers;

                      for (; !(iter003 == NIL); iter003 = iter003->rest) {
                        f = iter003->value;
                        if (!testTypeOnInstanceP(f, d->surrogateValueInverse)) {
                          alwaysP000 = false;
                          break;
                        }
                      }
                    }
                    testValue000 = alwaysP000;
                  }
                }
                if (testValue000) {
                  valuetypes = cons(d, valuetypes);
                }
              }
            }
          }
        }
      }
      return (filterOutUnnamedDescriptions(valuetypes));
    }
  }
}

Cons* SubsumptionInferenceLevel::levellizedAllSlotValueTypes(LogicObject* self, Surrogate* relation) {
  { SubsumptionInferenceLevel* level = this;

    { Cons* valuetypes = SHALLOW_INFERENCE->levellizedAllSlotValueTypes(self, relation);

      { NamedDescription* superrelation = NULL;
        Cons* iter000 = allSuperrelations(getDescription(relation), false);

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          superrelation = ((NamedDescription*)(iter000->value));
          { Object* supertype = NULL;
            Cons* iter001 = allRelationValues(SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_TYPE, consList(2, superrelation, self));

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              supertype = iter001->value;
              if (!valuetypes->memberP(supertype)) {
                valuetypes = cons(supertype, valuetypes);
              }
            }
          }
        }
      }
      return (filterOutUnnamedDescriptions(valuetypes));
    }
  }
}

// KLUDGE: until we know how to handle recursive subgoals
// across recursive query invocations, this allows us to disable chaining.
boolean oLEVELLIZED_BACKCHAINING_ENABLEDpo = false;

boolean NormalInferenceLevel::levellizedTestTypeOnInstanceP(Object* self, Surrogate* type) {
  { NormalInferenceLevel* level = this;
    TruthValue* dummy1;

    if (!(oLEVELLIZED_BACKCHAINING_ENABLEDpo)) {
      return (SUBSUMPTION_INFERENCE->levellizedTestTypeOnInstanceP(self, type));
    }
    return (applyCachedAsk(listO(3, SYM_FRAME_SUPPORT_LOGIC_pCONCEPT, SYM_FRAME_SUPPORT_LOGIC_pINSTANCE, NIL), listO(3, SYM_FRAME_SUPPORT_LOGIC_pCONCEPT, SYM_FRAME_SUPPORT_LOGIC_pINSTANCE, NIL), consList(2, type, self), consList(0), SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_TYPE_ON_INSTANCEp_QUERY_000, dummy1));
  }
}

Cons* NormalInferenceLevel::levellizedAllClassInstances(Surrogate* type) {
  { NormalInferenceLevel* level = this;
    Cons* dummy1;
    Cons* dummy2;

    if (!(oLEVELLIZED_BACKCHAINING_ENABLEDpo)) {
      return (SUBSUMPTION_INFERENCE->levellizedAllClassInstances(type));
    }
    return (applyCachedRetrieve(listO(3, SYM_FRAME_SUPPORT_LOGIC_pCONCEPT, SYM_FRAME_SUPPORT_LOGIC_pX, NIL), listO(3, SYM_FRAME_SUPPORT_LOGIC_pCONCEPT, SYM_FRAME_SUPPORT_LOGIC_pX, NIL), consList(2, type, NULL), consList(0), SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_CLASS_INSTANCES_QUERY_000, dummy1, dummy2));
  }
}

Cons* NormalInferenceLevel::levellizedAllRelationValues(Surrogate* relation, Cons* nminusonearguments) {
  { NormalInferenceLevel* level = this;
    Cons* dummy1;
    Cons* dummy2;
    Cons* dummy3;
    Cons* dummy4;
    Cons* dummy5;
    Cons* dummy6;
    Cons* dummy7;
    Cons* dummy8;

    if (!(oLEVELLIZED_BACKCHAINING_ENABLEDpo)) {
      return (SUBSUMPTION_INFERENCE->levellizedAllRelationValues(relation, nminusonearguments));
    }
    switch (nminusonearguments->length()) {
      case 0: 
        return (applyCachedRetrieve(listO(3, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pX, NIL), listO(3, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pX, NIL), consList(2, relation, NULL), consList(0), SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_000, dummy1, dummy2));
      case 1: 
        { Object* arg1 = nminusonearguments->value;

          return (applyCachedRetrieve(listO(4, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pX, SYM_FRAME_SUPPORT_LOGIC_pY, NIL), listO(4, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pX, SYM_FRAME_SUPPORT_LOGIC_pY, NIL), consList(3, relation, arg1, NULL), consList(0), SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_001, dummy3, dummy4));
        }
        break;
      case 2: 
        { Object* arg1 = nminusonearguments->value;
          Object* arg2 = nminusonearguments->rest->value;

          return (applyCachedRetrieve(listO(5, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pX, SYM_FRAME_SUPPORT_LOGIC_pY, SYM_FRAME_SUPPORT_LOGIC_pZ, NIL), listO(5, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pX, SYM_FRAME_SUPPORT_LOGIC_pY, SYM_FRAME_SUPPORT_LOGIC_pZ, NIL), consList(4, relation, arg1, arg2, NULL), consList(0), SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_002, dummy5, dummy6));
        }
        break;
      case 3: 
        { Object* arg1 = nminusonearguments->value;
          Object* arg2 = nminusonearguments->rest->value;
          Object* arg3 = nminusonearguments->rest->rest->value;

          return (applyCachedRetrieve(listO(6, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pW, SYM_FRAME_SUPPORT_LOGIC_pX, SYM_FRAME_SUPPORT_LOGIC_pY, SYM_FRAME_SUPPORT_LOGIC_pZ, NIL), listO(6, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pW, SYM_FRAME_SUPPORT_LOGIC_pX, SYM_FRAME_SUPPORT_LOGIC_pY, SYM_FRAME_SUPPORT_LOGIC_pZ, NIL), consList(5, relation, arg1, arg2, arg3, NULL), consList(0), SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_003, dummy7, dummy8));
        }
        break;
      default:
        return (callRetrieve(listO(4, SYM_FRAME_SUPPORT_LOGIC_ALL, SYM_FRAME_SUPPORT_LOGIC_pX, cons(internSymbolInModule(relation->symbolName, ((Module*)(relation->homeContext)), false), nminusonearguments->concatenate(cons(SYM_FRAME_SUPPORT_LOGIC_pX, NIL), 0)), NIL))->consify());
    }
  }
}

boolean NormalInferenceLevel::levellizedTestRelationOnArgumentsP(Surrogate* relation, Cons* arguments) {
  { NormalInferenceLevel* level = this;
    TruthValue* dummy1;
    TruthValue* dummy2;
    TruthValue* dummy3;
    TruthValue* dummy4;

    if (!(oLEVELLIZED_BACKCHAINING_ENABLEDpo)) {
      return (SUBSUMPTION_INFERENCE->levellizedTestRelationOnArgumentsP(relation, arguments));
    }
    switch (arguments->length()) {
      case 1: 
        { Object* arg1 = arguments->value;

          return (applyCachedAsk(listO(3, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pX, NIL), listO(3, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pX, NIL), consList(2, relation, arg1), consList(0), SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_000, dummy1));
        }
        break;
      case 2: 
        { Object* arg1 = arguments->value;
          Object* arg2 = arguments->rest->value;

          return (applyCachedAsk(listO(4, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pX, SYM_FRAME_SUPPORT_LOGIC_pY, NIL), listO(4, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pX, SYM_FRAME_SUPPORT_LOGIC_pY, NIL), consList(3, relation, arg1, arg2), consList(0), SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_001, dummy2));
        }
        break;
      case 3: 
        { Object* arg1 = arguments->value;
          Object* arg2 = arguments->rest->value;
          Object* arg3 = arguments->rest->rest->value;

          return (applyCachedAsk(listO(4, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pX, SYM_FRAME_SUPPORT_LOGIC_pY, NIL), listO(4, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pX, SYM_FRAME_SUPPORT_LOGIC_pY, NIL), consList(4, relation, arg1, arg2, arg3), consList(0), SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_002, dummy3));
        }
        break;
      case 4: 
        { Object* arg1 = arguments->value;
          Object* arg2 = arguments->rest->value;
          Object* arg3 = arguments->rest->rest->value;
          Object* arg4 = arguments->fourth();

          return (applyCachedAsk(listO(6, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pW, SYM_FRAME_SUPPORT_LOGIC_pX, SYM_FRAME_SUPPORT_LOGIC_pY, SYM_FRAME_SUPPORT_LOGIC_pZ, NIL), listO(6, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pW, SYM_FRAME_SUPPORT_LOGIC_pX, SYM_FRAME_SUPPORT_LOGIC_pY, SYM_FRAME_SUPPORT_LOGIC_pZ, NIL), consList(5, relation, arg1, arg2, arg3, arg4), consList(0), SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_003, dummy4));
        }
        break;
      default:
        return (trueTruthValueP(callAsk(cons(cons(internSymbolInModule(relation->symbolName, ((Module*)(relation->homeContext)), false), arguments->concatenate(NIL, 0)), NIL))));
    }
  }
}

int NormalInferenceLevel::levellizedGetSlotMinimumCardinality(LogicObject* self, Surrogate* relation) {
  { NormalInferenceLevel* level = this;
    Cons* dummy1;
    Cons* dummy2;

    if (!(oLEVELLIZED_BACKCHAINING_ENABLEDpo)) {
      return (SUBSUMPTION_INFERENCE->levellizedGetSlotMinimumCardinality(self, relation));
    }
    { Cons* n = applyCachedRetrieve(listO(4, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pOBJECT, SYM_FRAME_SUPPORT_LOGIC_pN, NIL), listO(5, SYM_FRAME_SUPPORT_LOGIC_RANGE_MIN_CARDINALITY, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pOBJECT, SYM_FRAME_SUPPORT_LOGIC_pN, NIL), consList(3, relation, self, NULL), consList(0), SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_GET_SLOT_MINIMUM_CARDINALITY_QUERY_000, dummy1, dummy2);

      if (n == NIL) {
        return (0);
      }
      else {
        return (unwrapInteger(((IntegerWrapper*)(n->value))));
      }
    }
  }
}

int NormalInferenceLevel::levellizedGetSlotMaximumCardinality(LogicObject* self, Surrogate* relation) {
  { NormalInferenceLevel* level = this;
    Cons* dummy1;
    Cons* dummy2;

    if (!(oLEVELLIZED_BACKCHAINING_ENABLEDpo)) {
      return (SUBSUMPTION_INFERENCE->levellizedGetSlotMaximumCardinality(self, relation));
    }
    { Cons* n = applyCachedRetrieve(listO(4, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pOBJECT, SYM_FRAME_SUPPORT_LOGIC_pN, NIL), listO(5, SYM_FRAME_SUPPORT_LOGIC_RANGE_MAX_CARDINALITY, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pOBJECT, SYM_FRAME_SUPPORT_LOGIC_pN, NIL), consList(3, relation, self, NULL), consList(0), SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_GET_SLOT_MAXIMUM_CARDINALITY_QUERY_000, dummy1, dummy2);

      if (n == NIL) {
        return (NULL_INTEGER);
      }
      else {
        return (unwrapInteger(((IntegerWrapper*)(n->value))));
      }
    }
  }
}

Cons* NormalInferenceLevel::levellizedAllSlotValueTypes(LogicObject* self, Surrogate* relation) {
  { NormalInferenceLevel* level = this;
    Cons* dummy1;
    Cons* dummy2;

    if (!(oLEVELLIZED_BACKCHAINING_ENABLEDpo)) {
      return (SUBSUMPTION_INFERENCE->levellizedAllSlotValueTypes(self, relation));
    }
    return (applyCachedRetrieve(listO(4, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pOBJECT, SYM_FRAME_SUPPORT_LOGIC_pTYPE, NIL), listO(5, SYM_FRAME_SUPPORT_STELLA_AND, listO(5, SYM_FRAME_SUPPORT_LOGIC_RANGE_TYPE, SYM_FRAME_SUPPORT_LOGIC_pRELATION, SYM_FRAME_SUPPORT_LOGIC_pOBJECT, SYM_FRAME_SUPPORT_LOGIC_pTYPE, NIL), listO(3, SYM_FRAME_SUPPORT_LOGIC_BOUND_VARIABLES, SYM_FRAME_SUPPORT_LOGIC_pTYPE, NIL), listO(3, SYM_FRAME_SUPPORT_LOGIC_CONCEPT, SYM_FRAME_SUPPORT_LOGIC_pTYPE, NIL), NIL), consList(3, relation, self, NULL), consList(0), SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_SLOT_VALUE_TYPES_QUERY_000, dummy1, dummy2));
  }
}

void helpStartupFrameSupport1() {
  {
    SGT_FRAME_SUPPORT_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
    SYM_FRAME_SUPPORT_LOGIC_OBJECT_STORE = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-STORE", NULL, 0)));
    SGT_FRAME_SUPPORT_STELLA_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("RELATION", getStellaModule("/STELLA", true), 1)));
    SGT_FRAME_SUPPORT_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
    SGT_FRAME_SUPPORT_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    SGT_FRAME_SUPPORT_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 1)));
    SGT_FRAME_SUPPORT_PL_KERNEL_KB_COLLECTION = ((Surrogate*)(internRigidSymbolWrtModule("COLLECTION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_FRAME_SUPPORT_PL_KERNEL_KB_CLASS = ((Surrogate*)(internRigidSymbolWrtModule("CLASS", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_FRAME_SUPPORT_PL_KERNEL_KB_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("RELATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_FRAME_SUPPORT_PL_KERNEL_KB_FUNCTION = ((Surrogate*)(internRigidSymbolWrtModule("FUNCTION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_FRAME_SUPPORT_STELLA_LITERAL_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_FRAME_SUPPORT_STELLA_LITERAL = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL", getStellaModule("/STELLA", true), 1)));
    SGT_FRAME_SUPPORT_PL_KERNEL_KB_SCALAR = ((Surrogate*)(internRigidSymbolWrtModule("SCALAR", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_FRAME_SUPPORT_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
    SGT_FRAME_SUPPORT_LOGIC_F_ALL_TAXONOMIC_TYPES_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-ALL-TAXONOMIC-TYPES-MEMO-TABLE-000", NULL, 1)));
    SGT_FRAME_SUPPORT_LOGIC_F_ALL_TYPES_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-ALL-TYPES-MEMO-TABLE-000", NULL, 1)));
    KWD_FRAME_SUPPORT_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    SGT_FRAME_SUPPORT_LOGIC_F_ALL_EQUIVALENT_RELATIONS_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-ALL-EQUIVALENT-RELATIONS-MEMO-TABLE-000", NULL, 1)));
    SGT_FRAME_SUPPORT_LOGIC_F_ALL_SUPERRELATIONS_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-ALL-SUPERRELATIONS-MEMO-TABLE-000", NULL, 1)));
    SGT_FRAME_SUPPORT_LOGIC_F_ALL_SUBRELATIONS_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-ALL-SUBRELATIONS-MEMO-TABLE-000", NULL, 1)));
    SGT_FRAME_SUPPORT_LOGIC_F_ALL_DIRECT_SUPERRELATIONS_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-ALL-DIRECT-SUPERRELATIONS-MEMO-TABLE-000", NULL, 1)));
    SGT_FRAME_SUPPORT_LOGIC_F_ALL_DIRECT_SUBRELATIONS_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-ALL-DIRECT-SUBRELATIONS-MEMO-TABLE-000", NULL, 1)));
    SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_MIN_CARDINALITY = ((Surrogate*)(internRigidSymbolWrtModule("RANGE-MIN-CARDINALITY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_MAX_CARDINALITY = ((Surrogate*)(internRigidSymbolWrtModule("RANGE-MAX-CARDINALITY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_TYPE = ((Surrogate*)(internRigidSymbolWrtModule("RANGE-TYPE", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_FRAME_SUPPORT_LOGIC_pCONCEPT = ((Symbol*)(internRigidSymbolWrtModule("?CONCEPT", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_pINSTANCE = ((Symbol*)(internRigidSymbolWrtModule("?INSTANCE", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_TYPE_ON_INSTANCEp_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("M-NORMAL-INFERENCE-LEVEL.LEVELLIZED-TEST-TYPE-ON-INSTANCE?-QUERY-000", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_pX = ((Symbol*)(internRigidSymbolWrtModule("?X", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_CLASS_INSTANCES_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("M-NORMAL-INFERENCE-LEVEL.LEVELLIZED-ALL-CLASS-INSTANCES-QUERY-000", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_pRELATION = ((Symbol*)(internRigidSymbolWrtModule("?RELATION", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("M-NORMAL-INFERENCE-LEVEL.LEVELLIZED-ALL-RELATION-VALUES-QUERY-000", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_pY = ((Symbol*)(internRigidSymbolWrtModule("?Y", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_001 = ((Symbol*)(internRigidSymbolWrtModule("M-NORMAL-INFERENCE-LEVEL.LEVELLIZED-ALL-RELATION-VALUES-QUERY-001", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_pZ = ((Symbol*)(internRigidSymbolWrtModule("?Z", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_002 = ((Symbol*)(internRigidSymbolWrtModule("M-NORMAL-INFERENCE-LEVEL.LEVELLIZED-ALL-RELATION-VALUES-QUERY-002", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_pW = ((Symbol*)(internRigidSymbolWrtModule("?W", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_003 = ((Symbol*)(internRigidSymbolWrtModule("M-NORMAL-INFERENCE-LEVEL.LEVELLIZED-ALL-RELATION-VALUES-QUERY-003", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_ALL = ((Symbol*)(internRigidSymbolWrtModule("ALL", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("M-NORMAL-INFERENCE-LEVEL.LEVELLIZED-TEST-RELATION-ON-ARGUMENTS?-QUERY-000", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_001 = ((Symbol*)(internRigidSymbolWrtModule("M-NORMAL-INFERENCE-LEVEL.LEVELLIZED-TEST-RELATION-ON-ARGUMENTS?-QUERY-001", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_002 = ((Symbol*)(internRigidSymbolWrtModule("M-NORMAL-INFERENCE-LEVEL.LEVELLIZED-TEST-RELATION-ON-ARGUMENTS?-QUERY-002", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_003 = ((Symbol*)(internRigidSymbolWrtModule("M-NORMAL-INFERENCE-LEVEL.LEVELLIZED-TEST-RELATION-ON-ARGUMENTS?-QUERY-003", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_pOBJECT = ((Symbol*)(internRigidSymbolWrtModule("?OBJECT", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_pN = ((Symbol*)(internRigidSymbolWrtModule("?N", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_RANGE_MIN_CARDINALITY = ((Symbol*)(internRigidSymbolWrtModule("RANGE-MIN-CARDINALITY", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_GET_SLOT_MINIMUM_CARDINALITY_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("M-NORMAL-INFERENCE-LEVEL.LEVELLIZED-GET-SLOT-MINIMUM-CARDINALITY-QUERY-000", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_RANGE_MAX_CARDINALITY = ((Symbol*)(internRigidSymbolWrtModule("RANGE-MAX-CARDINALITY", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_GET_SLOT_MAXIMUM_CARDINALITY_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("M-NORMAL-INFERENCE-LEVEL.LEVELLIZED-GET-SLOT-MAXIMUM-CARDINALITY-QUERY-000", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_pTYPE = ((Symbol*)(internRigidSymbolWrtModule("?TYPE", NULL, 0)));
    SYM_FRAME_SUPPORT_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    SYM_FRAME_SUPPORT_LOGIC_RANGE_TYPE = ((Symbol*)(internRigidSymbolWrtModule("RANGE-TYPE", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_BOUND_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("BOUND-VARIABLES", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_CONCEPT = ((Symbol*)(internRigidSymbolWrtModule("CONCEPT", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_SLOT_VALUE_TYPES_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("M-NORMAL-INFERENCE-LEVEL.LEVELLIZED-ALL-SLOT-VALUE-TYPES-QUERY-000", NULL, 0)));
    SYM_FRAME_SUPPORT_LOGIC_STARTUP_FRAME_SUPPORT = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-FRAME-SUPPORT", NULL, 0)));
    SYM_FRAME_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupFrameSupport2() {
  {
    defineFunctionObject("COERCE-TO-INSTANCE-IN-MODULE", "(DEFUN (COERCE-TO-INSTANCE-IN-MODULE OBJECT) ((SELF OBJECT) (MODULE MODULE) (LOCAL? BOOLEAN) (ORIGINAL OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&coerceToInstanceInModule)), NULL);
    defineFunctionObject("GET-INSTANCE", "(DEFUN (GET-INSTANCE OBJECT) ((INSTANCEREF OBJECT)) :DOCUMENTATION \"Return the nearest instance with name 'instanceRef'\nvisible from the current module.  'instanceRef' can be a string, symbol,\nor surrogate.  If 'instanceRef' is a surrogate, the search originates\nin the module the surrogate was interned in.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getInstance)), NULL);
    defineFunctionObject("FIND-INSTANCE", "(DEFUN (FIND-INSTANCE OBJECT) ((INSTANCEREF OBJECT)) :DOCUMENTATION \"Return the nearest instance with name 'instanceRef'\nvisible from the current module.  'instanceRef' can be a string, symbol,\nor surrogate.  If 'instanceRef' is a surrogate, the search originates\nin the module the surrogate was interned in.\" :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&findInstance)), NULL);
    defineFunctionObject("GET-SELF-OR-PROTOTYPE", "(DEFUN (GET-SELF-OR-PROTOTYPE LOGIC-OBJECT) ((INSTANCEREF OBJECT)) :DOCUMENTATION \"Used to convert a computation to reference so-called\n'template' slots rather than 'own' slots:  If 'instanceRef' denotes a class,\nreturn a prototype of that class.  Otherwise, return 'instanceRef'.\")", ((cpp_function_code)(&getSelfOrPrototype)), NULL);
    defineFunctionObject("GET-CLASS", "(DEFUN (GET-CLASS LOGIC-OBJECT) ((INSTANCEREF OBJECT)) :DOCUMENTATION \"Return the nearest class with name 'instanceRef'\nvisible from the current module.  'instanceRef' can be a string, symbol,\nor surrogate.  If 'instanceRef' is a surrogate, the search originates\nin the module the surrogate was interned in.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getClass)), NULL);
    defineFunctionObject("GET-RELATION", "(DEFUN (GET-RELATION LOGIC-OBJECT) ((INSTANCEREF OBJECT)) :DOCUMENTATION \"Return the nearest relation with name 'instanceRef'\nvisible from the current module.  'instanceRef' can be a string, symbol,\nor surrogate.  If 'instanceRef' is a surrogate, the search originates\nin the module the surrogate was interned in.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getRelation)), NULL);
    defineFunctionObject("GET-MODULE", "(DEFUN (GET-MODULE MODULE) ((MODULEREF OBJECT)) :DOCUMENTATION \"Return a module named 'moduleRef'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getModule)), NULL);
    defineFunctionObject("COLLECTION?", "(DEFUN (COLLECTION? BOOLEAN) ((OBJECTREF OBJECT)) :DOCUMENTATION \"Return TRUE if 'objectRef' denotes a relation or a class.\" :PUBLIC? TRUE)", ((cpp_function_code)(&collectionP)), NULL);
    defineFunctionObject("CLASS?", "(DEFUN (CLASS? BOOLEAN) ((OBJECTREF OBJECT)) :DOCUMENTATION \"Return TRUE if 'objectRef' denotes a class.\" :PUBLIC? TRUE)", ((cpp_function_code)(&classP)), NULL);
    defineFunctionObject("RELATION?", "(DEFUN (RELATION? BOOLEAN) ((OBJECTREF OBJECT)) :DOCUMENTATION \"Return TRUE if 'objectRef' denotes a relation or a class.\" :PUBLIC? TRUE)", ((cpp_function_code)(&relationP)), NULL);
    defineFunctionObject("FUNCTION?", "(DEFUN (FUNCTION? BOOLEAN) ((RELATIONREF OBJECT)) :DOCUMENTATION \"Return TRUE if 'relationRef' references a function.\" :PUBLIC? TRUE)", ((cpp_function_code)(&functionP)), NULL);
    defineFunctionObject("CONSTANT?", "(DEFUN (CONSTANT? BOOLEAN) ((OBJECTREF OBJECT)) :DOCUMENTATION \"Return TRUE if `objectRef' denotes a literal or scalar.\")", ((cpp_function_code)(&constantP)), NULL);
    defineFunctionObject("RELATION-NAME", "(DEFUN (RELATION-NAME STRING) ((SELF NAMED-DESCRIPTION)) :DOCUMENTATION \"Given a relation object, return it's name.\")", ((cpp_function_code)(&relationName)), NULL);
    defineFunctionObject("TERMIFY", "(DEFUN (TERMIFY OBJECT) ((SELF OBJECT)) :DOCUMENTATION \"Convert 'self' into an equivalent PowerLoom object\nthat can be passed as an argument wherever an instance is expected.\")", ((cpp_function_code)(&termify)), NULL);
    defineFunctionObject("RELATION-ARITY-OK?", "(DEFUN (RELATION-ARITY-OK? BOOLEAN) ((RELATIONREF SURROGATE) (ARITY INTEGER)))", ((cpp_function_code)(&relationArityOkP)), NULL);
    defineFunctionObject("FILTER-OUT-UNNAMED-DESCRIPTIONS", "(DEFUN (FILTER-OUT-UNNAMED-DESCRIPTIONS (CONS OF NAMED-DESCRIPTION)) ((DESCRIPTIONS (CONS OF LOGIC-OBJECT))))", ((cpp_function_code)(&filterOutUnnamedDescriptions)), NULL);
    defineFunctionObject("ALL-ASSERTED-TYPES", "(DEFUN (ALL-ASSERTED-TYPES (CONS OF NAMED-DESCRIPTION)) ((SELF OBJECT)) :DOCUMENTATION \"Return a set of all of the types that are\nasserted to be satisfied by 'self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allAssertedTypes)), NULL);
    defineFunctionObject("ALL-TAXONOMIC-TYPES", "(DEFUN (ALL-TAXONOMIC-TYPES (CONS OF NAMED-DESCRIPTION)) ((SELF OBJECT)) :DOCUMENTATION \"Return a set of all of the types that are\nsatisfied by 'self', using only assertions and upward\ntaxonomic reasoning.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allTaxonomicTypes)), NULL);
    defineFunctionObject("ALL-TYPES", "(DEFUN (ALL-TYPES (CONS OF NAMED-DESCRIPTION)) ((SELF OBJECT)) :DOCUMENTATION \"Return a set of all of the types that are\nsatisfied by 'self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allTypes)), NULL);
    defineFunctionObject("HELP-ALL-TYPES", "(DEFUN (HELP-ALL-TYPES (CONS OF NAMED-DESCRIPTION)) ((SELF OBJECT) (DO-SUBTYPES? BOOLEAN)))", ((cpp_function_code)(&helpAllTypes)), NULL);
    defineFunctionObject("HELP-ALL-SUBTYPES", "(DEFUN HELP-ALL-SUBTYPES ((SUPER DESCRIPTION) (SELF OBJECT) (TYPES LIST)))", ((cpp_function_code)(&helpAllSubtypes)), NULL);
    defineFunctionObject("ALL-DIRECT-TYPES", "(DEFUN (ALL-DIRECT-TYPES (CONS OF LOGIC-OBJECT)) ((SELF OBJECT)) :DOCUMENTATION \"Return a set of most specific types that are satisfied by 'self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allDirectTypes)), NULL);
    defineFunctionObject("TEST-TYPE-ON-INSTANCE?", "(DEFUN (TEST-TYPE-ON-INSTANCE? BOOLEAN) ((SELF OBJECT) (TYPE SURROGATE)) :DOCUMENTATION \"Return TRUE if 'self' satisfies 'type'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&testTypeOnInstanceP)), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-TEST-TYPE-ON-INSTANCE? BOOLEAN) ((LEVEL SUBSUMPTION-INFERENCE-LEVEL) (SELF OBJECT) (TYPE SURROGATE)))", wrapMethodCode(((cpp_method_code)(&SubsumptionInferenceLevel::levellizedTestTypeOnInstanceP))), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-TEST-TYPE-ON-INSTANCE? BOOLEAN) ((LEVEL SHALLOW-INFERENCE-LEVEL) (SELF OBJECT) (TYPE SURROGATE)))", wrapMethodCode(((cpp_method_code)(&ShallowInferenceLevel::levellizedTestTypeOnInstanceP))), NULL);
    defineFunctionObject("ALL-EQUIVALENT-RELATIONS", "(DEFUN (ALL-EQUIVALENT-RELATIONS (CONS OF NAMED-DESCRIPTION)) ((RELATION NAMED-DESCRIPTION) (REFLEXIVE? BOOLEAN)) :DOCUMENTATION \"Return a list of all relations equivalent to 'relation'.\nIf 'reflexive?', include 'relation' in the list.\")", ((cpp_function_code)(&allEquivalentRelations)), NULL);
    defineFunctionObject("REMOVE-EQUIVALENT-RELATIONS", "(DEFUN (REMOVE-EQUIVALENT-RELATIONS (LIKE SELF)) ((RELATIONSLIST (CONS OF LOGIC-OBJECT)) (RELATION NAMED-DESCRIPTION)))", ((cpp_function_code)(&removeEquivalentRelations)), NULL);
    defineFunctionObject("HELP-MEMOIZE-ALL-SUPERRELATIONS", "(DEFUN (HELP-MEMOIZE-ALL-SUPERRELATIONS (CONS OF NAMED-DESCRIPTION)) ((RELATION NAMED-DESCRIPTION) (REMOVEEQUIVALENTS? BOOLEAN)))", ((cpp_function_code)(&helpMemoizeAllSuperrelations)), NULL);
    defineFunctionObject("ALL-SUPERRELATIONS", "(DEFUN (ALL-SUPERRELATIONS (CONS OF NAMED-DESCRIPTION)) ((RELATION NAMED-DESCRIPTION) (REMOVEEQUIVALENTS? BOOLEAN)) :DOCUMENTATION \"Return a set of all relations that subsume relation.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allSuperrelations)), NULL);
    defineFunctionObject("HELP-MEMOIZE-ALL-SUBRELATIONS", "(DEFUN (HELP-MEMOIZE-ALL-SUBRELATIONS (CONS OF NAMED-DESCRIPTION)) ((RELATION NAMED-DESCRIPTION) (REMOVEEQUIVALENTS? BOOLEAN)))", ((cpp_function_code)(&helpMemoizeAllSubrelations)), NULL);
    defineFunctionObject("ALL-SUBRELATIONS", "(DEFUN (ALL-SUBRELATIONS (CONS OF NAMED-DESCRIPTION)) ((RELATION NAMED-DESCRIPTION) (REMOVEEQUIVALENTS? BOOLEAN)) :DOCUMENTATION \"Return a set of all (named) relations that specialize\nrelation.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allSubrelations)), NULL);
    defineFunctionObject("ALL-DIRECT-SUPERRELATIONS", "(DEFUN (ALL-DIRECT-SUPERRELATIONS (CONS OF NAMED-DESCRIPTION)) ((RELATION NAMED-DESCRIPTION) (REMOVEEQUIVALENTS? BOOLEAN)) :DOCUMENTATION \"Return a set of relations that immediately subsume\n'relation'.  If 'removeEquivalents?' (recommended), don't include any\nrelations equivalent to 'relation'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allDirectSuperrelations)), NULL);
    defineFunctionObject("ALL-DIRECT-SUBRELATIONS", "(DEFUN (ALL-DIRECT-SUBRELATIONS (CONS OF NAMED-DESCRIPTION)) ((RELATION NAMED-DESCRIPTION) (REMOVEEQUIVALENTS? BOOLEAN)) :DOCUMENTATION \"Return a set of relations that immediately specialize\n'relation'.  If 'removeEquivalents?' (recommended), don't include any\nrelations equivalent to 'relation'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allDirectSubrelations)), NULL);
    defineFunctionObject("TEST-SUBRELATION?", "(DEFUN (TEST-SUBRELATION? BOOLEAN) ((SUBRELATION SURROGATE) (SUPERRELATION SURROGATE)) :DOCUMENTATION \"Return TRUE if 'subrelation' specializes 'superrelation'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&testSubrelationP)), NULL);
    defineFunctionObject("ALL-CLASS-INSTANCES", "(DEFUN (ALL-CLASS-INSTANCES CONS) ((TYPE SURROGATE)) :DOCUMENTATION \"Return a set of instances that belong to the class 'type'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allClassInstances)), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-ALL-CLASS-INSTANCES CONS) ((LEVEL SUBSUMPTION-INFERENCE-LEVEL) (TYPE SURROGATE)))", wrapMethodCode(((cpp_method_code)(&SubsumptionInferenceLevel::levellizedAllClassInstances))), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-ALL-CLASS-INSTANCES CONS) ((LEVEL ASSERTION-INFERENCE-LEVEL) (TYPE SURROGATE)))", wrapMethodCode(((cpp_method_code)(&AssertionInferenceLevel::levellizedAllClassInstances))), NULL);
    defineFunctionObject("ALL-RELATION-VALUES", "(DEFUN (ALL-RELATION-VALUES CONS) ((RELATION SURROGATE) (NMINUSONEARGUMENTS CONS)) :DOCUMENTATION \"Return a set of values that satisfy the relation\n'relation' (a surrogate) applied to 'nMinusOneArguments' plus that last value.\")", ((cpp_function_code)(&allRelationValues)), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-ALL-RELATION-VALUES CONS) ((LEVEL SUBSUMPTION-INFERENCE-LEVEL) (RELATION SURROGATE) (NMINUSONEARGUMENTS CONS)))", wrapMethodCode(((cpp_method_code)(&SubsumptionInferenceLevel::levellizedAllRelationValues))), NULL);
    defineFunctionObject("TEST-RELATION-ON-ARGUMENTS?", "(DEFUN (TEST-RELATION-ON-ARGUMENTS? BOOLEAN) ((RELATION SURROGATE) (ARGUMENTS CONS)) :DOCUMENTATION \"Return TRUE if 'relation' (a surrogate) is TRUE when\napplied to 'arguments'.\")", ((cpp_function_code)(&testRelationOnArgumentsP)), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-TEST-RELATION-ON-ARGUMENTS? BOOLEAN) ((LEVEL SUBSUMPTION-INFERENCE-LEVEL) (RELATION SURROGATE) (ARGUMENTS CONS)))", wrapMethodCode(((cpp_method_code)(&SubsumptionInferenceLevel::levellizedTestRelationOnArgumentsP))), NULL);
    defineFunctionObject("ALL-SLOT-VALUES", "(DEFUN (ALL-SLOT-VALUES CONS) ((SELF LOGIC-OBJECT) (RELATION SURROGATE)) :DOCUMENTATION \"Return a set of values for the slot 'relation' (a surrogate)\napplied to 'self' (an object).\" :PUBLIC? TRUE)", ((cpp_function_code)(&allSlotValues)), NULL);
    defineFunctionObject("GET-SLOT-VALUE", "(DEFUN (GET-SLOT-VALUE OBJECT) ((SELF LOGIC-OBJECT) (RELATION SURROGATE)) :DOCUMENTATION \"Return a single value for the slot 'relation' (a surrogate)\napplied to 'self' (an object).\" :PUBLIC? TRUE)", ((cpp_function_code)(&getSlotValue)), NULL);
    defineFunctionObject("TEST-SLOT-VALUE?", "(DEFUN (TEST-SLOT-VALUE? BOOLEAN) ((SELF LOGIC-OBJECT) (RELATION SURROGATE) (FILLER OBJECT)) :DOCUMENTATION \"Return TRUE if the proposition '(<relation> <self> <filler>)'\nis true.\" :PUBLIC? TRUE)", ((cpp_function_code)(&testSlotValueP)), NULL);
    defineFunctionObject("GET-SLOT-MINIMUM-CARDINALITY", "(DEFUN (GET-SLOT-MINIMUM-CARDINALITY INTEGER) ((SELF LOGIC-OBJECT) (RELATION SURROGATE)) :DOCUMENTATION \"Return a minimum value for the number of fillers of relation\n'relation' (a surrogate) applied to the instance 'self' (an object).\" :PUBLIC? TRUE)", ((cpp_function_code)(&getSlotMinimumCardinality)), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-GET-SLOT-MINIMUM-CARDINALITY INTEGER) ((LEVEL SHALLOW-INFERENCE-LEVEL) (SELF LOGIC-OBJECT) (RELATION SURROGATE)))", wrapMethodCode(((cpp_method_code)(&ShallowInferenceLevel::levellizedGetSlotMinimumCardinality))), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-GET-SLOT-MINIMUM-CARDINALITY INTEGER) ((LEVEL SUBSUMPTION-INFERENCE-LEVEL) (SELF LOGIC-OBJECT) (RELATION SURROGATE)))", wrapMethodCode(((cpp_method_code)(&SubsumptionInferenceLevel::levellizedGetSlotMinimumCardinality))), NULL);
    defineFunctionObject("TEST-CLOSED-SLOT?", "(DEFUN (TEST-CLOSED-SLOT? BOOLEAN) ((RELATION SURROGATE)) :DOCUMENTATION \"Return TRUE if 'relation' (a surrogate) is asserted to \nbe closed or if the current module closes all relations.\" :PUBLIC? TRUE)", ((cpp_function_code)(&testClosedSlotP)), NULL);
    defineFunctionObject("TEST-FUNCTION-SLOT?", "(DEFUN (TEST-FUNCTION-SLOT? BOOLEAN) ((RELATION SURROGATE)) :DOCUMENTATION \"Return TRUE if 'relation' (a surrogate) is a function.\" :PUBLIC? TRUE)", ((cpp_function_code)(&testFunctionSlotP)), NULL);
    defineFunctionObject("GET-SLOT-MAXIMUM-CARDINALITY", "(DEFUN (GET-SLOT-MAXIMUM-CARDINALITY INTEGER) ((SELF LOGIC-OBJECT) (RELATION SURROGATE)) :DOCUMENTATION \"Return a maximum value for the number of fillers of relation\n'relation' (a surrogate) applied to the instance 'self' (an object).\" :PUBLIC? TRUE)", ((cpp_function_code)(&getSlotMaximumCardinality)), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-GET-SLOT-MAXIMUM-CARDINALITY INTEGER) ((LEVEL SHALLOW-INFERENCE-LEVEL) (SELF LOGIC-OBJECT) (RELATION SURROGATE)))", wrapMethodCode(((cpp_method_code)(&ShallowInferenceLevel::levellizedGetSlotMaximumCardinality))), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-GET-SLOT-MAXIMUM-CARDINALITY INTEGER) ((LEVEL SUBSUMPTION-INFERENCE-LEVEL) (SELF LOGIC-OBJECT) (RELATION SURROGATE)))", wrapMethodCode(((cpp_method_code)(&SubsumptionInferenceLevel::levellizedGetSlotMaximumCardinality))), NULL);
    defineFunctionObject("GET-SLOT-VALUE-TYPE", "(DEFUN (GET-SLOT-VALUE-TYPE NAMED-DESCRIPTION) ((SELF LOGIC-OBJECT) (RELATION SURROGATE)) :DOCUMENTATION \"Return a most specific type for fillers of the slot 'relation'\n(a surrogate) applied to 'self'. If there is more than one, pick one.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getSlotValueType)), NULL);
    defineFunctionObject("ALL-SLOT-VALUE-TYPES", "(DEFUN (ALL-SLOT-VALUE-TYPES (CONS OF NAMED-DESCRIPTION)) ((SELF LOGIC-OBJECT) (RELATION SURROGATE)) :DOCUMENTATION \"Return a set of the most specific types for fillers\nof the slot 'relation' applied to 'self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allSlotValueTypes)), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-ALL-SLOT-VALUE-TYPES (CONS OF NAMED-DESCRIPTION)) ((LEVEL SHALLOW-INFERENCE-LEVEL) (SELF LOGIC-OBJECT) (RELATION SURROGATE)))", wrapMethodCode(((cpp_method_code)(&ShallowInferenceLevel::levellizedAllSlotValueTypes))), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-ALL-SLOT-VALUE-TYPES (CONS OF NAMED-DESCRIPTION)) ((LEVEL SUBSUMPTION-INFERENCE-LEVEL) (SELF LOGIC-OBJECT) (RELATION SURROGATE)))", wrapMethodCode(((cpp_method_code)(&SubsumptionInferenceLevel::levellizedAllSlotValueTypes))), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-TEST-TYPE-ON-INSTANCE? BOOLEAN) ((LEVEL NORMAL-INFERENCE-LEVEL) (SELF OBJECT) (TYPE SURROGATE)))", wrapMethodCode(((cpp_method_code)(&NormalInferenceLevel::levellizedTestTypeOnInstanceP))), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-ALL-CLASS-INSTANCES CONS) ((LEVEL NORMAL-INFERENCE-LEVEL) (TYPE SURROGATE)))", wrapMethodCode(((cpp_method_code)(&NormalInferenceLevel::levellizedAllClassInstances))), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-ALL-RELATION-VALUES CONS) ((LEVEL NORMAL-INFERENCE-LEVEL) (RELATION SURROGATE) (NMINUSONEARGUMENTS CONS)))", wrapMethodCode(((cpp_method_code)(&NormalInferenceLevel::levellizedAllRelationValues))), NULL);
    defineMethodObject("(DEFMETHOD (LEVELLIZED-TEST-RELATION-ON-ARGUMENTS? BOOLEAN) ((LEVEL NORMAL-INFERENCE-LEVEL) (RELATION SURROGATE) (ARGUMENTS CONS)))", wrapMethodCode(((cpp_method_code)(&NormalInferenceLevel::levellizedTestRelationOnArgumentsP))), NULL);
  }
}

void startupFrameSupport() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupFrameSupport1();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupFrameSupport2();
      defineMethodObject("(DEFMETHOD (LEVELLIZED-GET-SLOT-MINIMUM-CARDINALITY INTEGER) ((LEVEL NORMAL-INFERENCE-LEVEL) (SELF LOGIC-OBJECT) (RELATION SURROGATE)))", wrapMethodCode(((cpp_method_code)(&NormalInferenceLevel::levellizedGetSlotMinimumCardinality))), NULL);
      defineMethodObject("(DEFMETHOD (LEVELLIZED-GET-SLOT-MAXIMUM-CARDINALITY INTEGER) ((LEVEL NORMAL-INFERENCE-LEVEL) (SELF LOGIC-OBJECT) (RELATION SURROGATE)))", wrapMethodCode(((cpp_method_code)(&NormalInferenceLevel::levellizedGetSlotMaximumCardinality))), NULL);
      defineMethodObject("(DEFMETHOD (LEVELLIZED-ALL-SLOT-VALUE-TYPES (CONS OF NAMED-DESCRIPTION)) ((LEVEL NORMAL-INFERENCE-LEVEL) (SELF LOGIC-OBJECT) (RELATION SURROGATE)))", wrapMethodCode(((cpp_method_code)(&NormalInferenceLevel::levellizedAllSlotValueTypes))), NULL);
      defineFunctionObject("STARTUP-FRAME-SUPPORT", "(DEFUN STARTUP-FRAME-SUPPORT () :PUBLIC? TRUE)", ((cpp_function_code)(&startupFrameSupport)), NULL);
      { MethodSlot* function = lookupFunction(SYM_FRAME_SUPPORT_LOGIC_STARTUP_FRAME_SUPPORT);

        setDynamicSlotValue(function->dynamicSlots, SYM_FRAME_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupFrameSupport"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFGLOBAL *LEVELLIZED-BACKCHAINING-ENABLED?* BOOLEAN FALSE :DOCUMENTATION \"KLUDGE: until we know how to handle recursive subgoals\nacross recursive query invocations, this allows us to disable chaining.\")", &oLEVELLIZED_BACKCHAINING_ENABLEDpo);
    }
  }
}

Surrogate* SGT_FRAME_SUPPORT_LOGIC_LOGIC_OBJECT = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_OBJECT_STORE = NULL;

Surrogate* SGT_FRAME_SUPPORT_STELLA_RELATION = NULL;

Surrogate* SGT_FRAME_SUPPORT_STELLA_THING = NULL;

Surrogate* SGT_FRAME_SUPPORT_LOGIC_PROPOSITION = NULL;

Surrogate* SGT_FRAME_SUPPORT_STELLA_MODULE = NULL;

Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_COLLECTION = NULL;

Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_CLASS = NULL;

Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_RELATION = NULL;

Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_FUNCTION = NULL;

Surrogate* SGT_FRAME_SUPPORT_STELLA_LITERAL_WRAPPER = NULL;

Surrogate* SGT_FRAME_SUPPORT_STELLA_LITERAL = NULL;

Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_SCALAR = NULL;

Surrogate* SGT_FRAME_SUPPORT_LOGIC_NAMED_DESCRIPTION = NULL;

Surrogate* SGT_FRAME_SUPPORT_LOGIC_F_ALL_TAXONOMIC_TYPES_MEMO_TABLE_000 = NULL;

Surrogate* SGT_FRAME_SUPPORT_LOGIC_F_ALL_TYPES_MEMO_TABLE_000 = NULL;

Keyword* KWD_FRAME_SUPPORT_ISA = NULL;

Surrogate* SGT_FRAME_SUPPORT_LOGIC_F_ALL_EQUIVALENT_RELATIONS_MEMO_TABLE_000 = NULL;

Surrogate* SGT_FRAME_SUPPORT_LOGIC_F_ALL_SUPERRELATIONS_MEMO_TABLE_000 = NULL;

Surrogate* SGT_FRAME_SUPPORT_LOGIC_F_ALL_SUBRELATIONS_MEMO_TABLE_000 = NULL;

Surrogate* SGT_FRAME_SUPPORT_LOGIC_F_ALL_DIRECT_SUPERRELATIONS_MEMO_TABLE_000 = NULL;

Surrogate* SGT_FRAME_SUPPORT_LOGIC_F_ALL_DIRECT_SUBRELATIONS_MEMO_TABLE_000 = NULL;

Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_MIN_CARDINALITY = NULL;

Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_MAX_CARDINALITY = NULL;

Surrogate* SGT_FRAME_SUPPORT_PL_KERNEL_KB_RANGE_TYPE = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_pCONCEPT = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_pINSTANCE = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_TYPE_ON_INSTANCEp_QUERY_000 = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_pX = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_CLASS_INSTANCES_QUERY_000 = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_pRELATION = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_000 = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_pY = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_001 = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_pZ = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_002 = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_pW = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_RELATION_VALUES_QUERY_003 = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_ALL = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_000 = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_001 = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_002 = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_TEST_RELATION_ON_ARGUMENTSp_QUERY_003 = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_pOBJECT = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_pN = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_RANGE_MIN_CARDINALITY = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_GET_SLOT_MINIMUM_CARDINALITY_QUERY_000 = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_RANGE_MAX_CARDINALITY = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_GET_SLOT_MAXIMUM_CARDINALITY_QUERY_000 = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_pTYPE = NULL;

Symbol* SYM_FRAME_SUPPORT_STELLA_AND = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_RANGE_TYPE = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_BOUND_VARIABLES = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_CONCEPT = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_M_NORMAL_INFERENCE_LEVELdLEVELLIZED_ALL_SLOT_VALUE_TYPES_QUERY_000 = NULL;

Symbol* SYM_FRAME_SUPPORT_LOGIC_STARTUP_FRAME_SUPPORT = NULL;

Symbol* SYM_FRAME_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
