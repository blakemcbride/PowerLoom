//  -*- Mode: C++ -*-

// descriptions.cc

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

Iterator* directSuperrelations(Relation* self) {
  // Return direct super classes/slots of 'self'.
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfClassP(testValue000)) {
      { Relation* self000 = self;
        Class* self = ((Class*)(self000));

        return (self->directSuperClasses());
      }
    }
    else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_STELLA_SLOT)) {
      { Relation* self001 = self;
        Slot* self = ((Slot*)(self001));

        return (((ListIterator*)(self->slotDirectSupers_reader()->allocateIterator())));
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

Cons* slotColumnTypes(Slot* self, int count) {
  { boolean dummy1;

    if (subtypeOfStorageSlotP(safePrimaryType(self))) {
      { Slot* self000 = self;
        StorageSlot* self = ((StorageSlot*)(self000));

        { Surrogate* domain = self->slotOwner;
          Surrogate* range = self->slotBaseType;
          Cons* typeslist = (booleanTypeP(range) ? consList(1, domain) : consList(2, domain, range));

          return (typeslist);
        }
      }
    }
    else {
      { List* typespecifiers = (isaP(self, SGT_DESCRIPTIONS_STELLA_METHOD_SLOT) ? ((MethodSlot*)(self))->methodParameterTypeSpecifiers_reader() : ((Table*)(self))->tupleDomains);
        Cons* typeslist = NIL;
        Cons* variabletypes = NIL;
        Cons* returntypes = NIL;
        Surrogate* returntype = unwrapWrappedType(self->slotBaseType);

        if (((boolean)(returntype)) &&
            (!booleanTypeP(returntype))) {
          returntypes = cons(returntype, returntypes);
        }
        if (self->arity() == NULL_INTEGER) {
          { StandardObject* variableargumentstype = extractParameterType(((ParametricTypeSpecifier*)(typespecifiers->last())), SYM_DESCRIPTIONS_STELLA_ANY_VALUE, dummy1);

            { Object* tspec = NULL;
              Iterator* iter000 = typespecifiers->butLast();
              Cons* collect000 = NULL;

              for  (; iter000->nextP(); ) {
                tspec = iter000->value;
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(unwrapWrappedType(typeSpecToBaseType(((StandardObject*)(tspec)))), NIL);
                    if (typeslist == NIL) {
                      typeslist = collect000;
                    }
                    else {
                      addConsToEndOfConsList(typeslist, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(unwrapWrappedType(typeSpecToBaseType(((StandardObject*)(tspec)))), NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
            if (count == NULL_INTEGER) {
              count = 1;
            }
            else {
              count = count - (typeslist->length() + returntypes->length());
            }
            { int i = NULL_INTEGER;
              int iter001 = 1;
              int upperBound000 = count;
              boolean unboundedP000 = upperBound000 == NULL_INTEGER;

              for  (; unboundedP000 ||
                        (iter001 <= upperBound000); 
                    iter001 = iter001 + 1) {
                i = iter001;
                i = i;
                variabletypes = cons(variableargumentstype, variabletypes);
              }
            }
            typeslist = typeslist->concatenate(variabletypes, 0);
          }
        }
        else {
          { Object* tspec = NULL;
            Cons* iter002 = typespecifiers->theConsList;
            Cons* collect001 = NULL;

            for  (; !(iter002 == NIL); 
                  iter002 = iter002->rest) {
              tspec = iter002->value;
              if (!((boolean)(collect001))) {
                {
                  collect001 = cons(unwrapWrappedType(typeSpecToBaseType(((StandardObject*)(tspec)))), NIL);
                  if (typeslist == NIL) {
                    typeslist = collect001;
                  }
                  else {
                    addConsToEndOfConsList(typeslist, collect001);
                  }
                }
              }
              else {
                {
                  collect001->rest = cons(unwrapWrappedType(typeSpecToBaseType(((StandardObject*)(tspec)))), NIL);
                  collect001 = collect001->rest;
                }
              }
            }
          }
        }
        typeslist = typeslist->concatenate(returntypes, 0);
        return (typeslist);
      }
    }
  }
}

// Installed in a description with undetermined arity.
Vector* FAKE_IO_VARIABLES = NULL;

Description* createDescription(int arity, boolean namedP) {
  enforceCodeOnly();
  { Description* description = (namedP ? newNamedDescription() : newDescription());

    description->ioVariables = ((arity != NULL_INTEGER) ? stella::newVector(arity) : FAKE_IO_VARIABLES);
    return (description);
  }
}

Symbol* Description::descriptionName() {
  // Return the name of the description `self', if it has one.
  { Description* self = this;

    return (NULL);
  }
}

Symbol* NamedDescription::descriptionName() {
  // Return the name of the description `self'.
  { NamedDescription* self = this;

    return (objectName(self));
  }
}

void createBaseRelationForPolymorphicDescription(Description* description) {
  { Surrogate* surrogate = internSurrogateInModule(description->descriptionName()->symbolName, ((Module*)(description->homeContext)), true);
    Object* relation = surrogate->surrogateValue;

    if (!((boolean)(relation))) {
      { 
        BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_DESCRIPTIONS_EXTENSIONAL_ASSERTION);
        BIND_STELLA_SPECIAL(oFILLINGCONSTRAINTPROPAGATIONQUEUESpo, boolean, false);
        assertIsaProposition(createLogicInstance(surrogate, SGT_DESCRIPTIONS_PL_KERNEL_KB_RELATION), SGT_DESCRIPTIONS_PL_KERNEL_KB_POLYMORPHIC);
      }
    }
  }
}

Cons* SYSTEM_DEFINED_ARGUMENT_NAMES = NULL;

Symbol* yieldSystemDefinedParameterName(int index, Object* referenceobject) {
  if (index < 100) {
    return (internSymbolInModule(((Symbol*)(SYSTEM_DEFINED_ARGUMENT_NAMES->nth(index)))->symbolName, referenceobject->homeModule(), true));
  }
  else {
    return (internSymbolInModule(stringConcatenate("?X", integerToString(((long long int)(index + 1))), 0), referenceobject->homeModule(), true));
  }
}

void ensureDescriptionBody(Description* description) {
  if (((!((boolean)(description->proposition))) ||
      (description->proposition == TRUE_PROPOSITION)) &&
      isaP(description, SGT_DESCRIPTIONS_LOGIC_NAMED_DESCRIPTION)) {
    materializePrimitiveDescriptionBody(((NamedDescription*)(description)));
  }
}

void materializePrimitiveDescriptionBody(NamedDescription* description) {
  { boolean nativeP = ((boolean)(description->nativeRelation()));
    Symbol* name = (nativeP ? internSymbolInModule(description->nativeRelation()->name(), description->nativeRelation()->homeModule(), true) : description->descriptionName());
    List* variabletypes = description->ioVariableTypes;
    int arity = variabletypes->length();
    Cons* tree = NULL;
    Cons* variables = NIL;
    Cons* arguments = NIL;

    { IntegerIntervalIterator* i = interval(1, arity);
      Symbol* name = NULL;
      Cons* iter000 = SYSTEM_DEFINED_ARGUMENT_NAMES;
      Cons* collect000 = NULL;

      for  (; i->nextP() &&
                (!(iter000 == NIL)); 
            iter000 = iter000->rest) {
        name = ((Symbol*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(name, NIL);
            if (variables == NIL) {
              variables = collect000;
            }
            else {
              addConsToEndOfConsList(variables, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(name, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    arguments = copyConsList(variables);
    if (nativeP &&
        (arity > 1)) {
      variables->firstSetter(listO(3, SYM_DESCRIPTIONS_STELLA_ISA, variables->value, cons(typeToSymbol(((Surrogate*)(variabletypes->first()))), NIL)));
    }
    tree = listO(3, SYM_DESCRIPTIONS_LOGIC_KAPPA, variables, cons(cons(name, arguments->concatenate(NIL, 0)), NIL));
    { 
      BIND_STELLA_SPECIAL(oLOGIC_DIALECTo, Keyword*, KWD_DESCRIPTIONS_KIF);
      BIND_STELLA_SPECIAL(oLOGICVARIABLETABLEo, Cons*, NIL);
      BIND_STELLA_SPECIAL(oTERMUNDERCONSTRUCTIONo, Object*, tree);
      BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_DESCRIPTIONS_DESCRIPTION);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, description->homeContext);
      { Description* sacrificialdescription = evaluateDescriptionTerm(tree, false);

        description->ioVariables = sacrificialdescription->ioVariables;
        description->proposition = sacrificialdescription->proposition;
        sacrificialdescription->deletedPSetter(true);
      }
    }
  }
}

NamedDescription* createPrimitiveDescription(List* iovariablenames, List* iovariabletypes, boolean variablearityP, boolean classP, boolean functionP, Module* module) {
  if (iovariabletypes->length() > SYSTEM_DEFINED_ARGUMENT_NAMES->length()) {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "PowerLoom can't handle relations with arity > " << "`" << SYSTEM_DEFINED_ARGUMENT_NAMES->length() << "'" << std::endl;
      throw *newStellaException(stream000->theStringReader());
    }
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    { NamedDescription* description = ((NamedDescription*)(createDescription(NULL_INTEGER, true)));

      description->ioVariableNames = iovariablenames;
      description->ioVariableTypes = iovariabletypes;
      description->surrogateValueInverse = SGT_DESCRIPTIONS_LOGIC_UNFINALIZED;
      { 
        BIND_STELLA_SPECIAL(oFILLINGCONSTRAINTPROPAGATIONQUEUESpo, boolean, false);
        BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_DESCRIPTIONS_EXTENSIONAL_ASSERTION);
        if (classP) {
          linkOriginatedProposition(description, assertIsaProposition(description, SGT_DESCRIPTIONS_PL_KERNEL_KB_CONCEPT));
        }
        else if (functionP) {
          linkOriginatedProposition(description, assertIsaProposition(description, SGT_DESCRIPTIONS_PL_KERNEL_KB_FUNCTION));
        }
        else {
          linkOriginatedProposition(description, assertIsaProposition(description, SGT_DESCRIPTIONS_PL_KERNEL_KB_RELATION));
        }
        if (variablearityP) {
          linkOriginatedProposition(description, assertProperty(description, SGT_DESCRIPTIONS_PL_KERNEL_KB_VARIABLE_ARITY));
        }
        description->surrogateValueInverse = NULL;
        return (description);
      }
    }
  }
}

void linkStellaRelationAndDescription(Relation* self, NamedDescription* description) {
  setDynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_DESCRIPTION, description, NULL);
  description->nativeRelationSetter(self);
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfClassP(testValue000)) {
      { Relation* self000 = self;
        Class* self = ((Class*)(self000));

        description->surrogateValueInverse = classLogicalType(self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_STELLA_SLOT)) {
      { Relation* self001 = self;
        Slot* self = ((Slot*)(self001));

        description->surrogateValueInverse = self->slotSlotref;
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
  if (polymorphicRelationP(self)) {
    createBaseRelationForPolymorphicDescription(description);
  }
  return;
}

NamedDescription* createDescriptionForStellaRelation(Relation* self) {
  { Relation* super = NULL;
    Iterator* iter000 = directSuperrelations(self);

    for (; iter000->nextP(); ) {
      super = ((Relation*)(iter000->value));
      if (((boolean)(super)) &&
          ((!isaP(super, SGT_DESCRIPTIONS_STELLA_CLASS)) ||
           logicClassP(((Class*)(super))))) {
        getDescription(super);
      }
    }
  }
  { NamedDescription* description = NULL;
    Module* homemodule = NULL;

    { Surrogate* testValue000 = safePrimaryType(self);

      if (subtypeOfClassP(testValue000)) {
        { Relation* self000 = self;
          Class* self = ((Class*)(self000));

          homemodule = classLogicalType(self)->homeModule();
        }
      }
      else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_STELLA_SLOT)) {
        { Relation* self001 = self;
          Slot* self = ((Slot*)(self001));

          homemodule = self->homeModule();
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    if (!(visibleFromP(oPL_KERNEL_MODULEo, homemodule))) {
      homemodule = oPL_KERNEL_MODULEo;
    }
    { Surrogate* testValue001 = safePrimaryType(self);

      if (subtypeOfClassP(testValue001)) {
        { Relation* self004 = self;
          Class* self = ((Class*)(self004));

          if (!logicClassP(self)) {
            { OutputStringStream* stream001 = newOutputStringStream();

              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                *(stream001->nativeStream) << "ERROR: " << "Can't use the class " << "`" << self << "'" << " as a logic class because it" << std::endl << "   does not inherit the top-level class THING." << "." << std::endl;
                helpSignalPropositionError(stream001, KWD_DESCRIPTIONS_ERROR);
              }
              throw *newPropositionError(stream001->theStringReader());
            }
          }
          description = createPrimitiveDescription(NIL_LIST, list(1, classLogicalType(self)), false, true, false, homemodule);
        }
      }
      else if (subtypeOfP(testValue001, SGT_DESCRIPTIONS_STELLA_SLOT)) {
        { Relation* self005 = self;
          Slot* self = ((Slot*)(self005));

          { Surrogate* slotref = self->slotSlotref;
            Surrogate* superslotref = mostGeneralEquivalentSlotref(slotref);

            if (!(slotref == superslotref)) {
              self = ((Slot*)(superslotref->surrogateValue));
              if (((boolean)(((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_DESCRIPTION, NULL)))))) {
                return (((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_DESCRIPTION, NULL))));
              }
            }
          }
          { List* self008 = newList();

            self008->theConsList = slotColumnTypes(self, NULL_INTEGER);
            description = createPrimitiveDescription(NIL_LIST, self008, false, false, !booleanTypeP(self->slotBaseType), homemodule);
          }
        }
      }
      else {
        { OutputStringStream* stream002 = newOutputStringStream();

          *(stream002->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
          throw *newStellaException(stream002->theStringReader());
        }
      }
    }
    linkStellaRelationAndDescription(self, description);
    finalizeSuperrelationLinks(self);
    ensureDescriptionBody(description);
    return (description);
  }
}

NamedDescription* surrogateToDescription(Surrogate* self) {
  { Object* surrogatevalue = self->surrogateValue;

    if (!((boolean)(surrogatevalue))) {
      return (NULL);
    }
    if (isaP(surrogatevalue, SGT_DESCRIPTIONS_LOGIC_NAMED_DESCRIPTION)) {
      return (((NamedDescription*)(surrogatevalue)));
    }
    else {
      return (getDescription(self));
    }
  }
}

NamedDescription* getDescription(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_NAMED_DESCRIPTION)) {
      { Object* self000 = self;
        NamedDescription* self = ((NamedDescription*)(self000));

        return (self);
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* self001 = self;
        Surrogate* self = ((Surrogate*)(self001));

        return (surrogateDgetDescription(self));
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* self002 = self;
        Symbol* self = ((Symbol*)(self002));

        return (getDescription(symbolToSurrogate(self)));
      }
    }
    else if (subtypeOfStringP(testValue000)) {
      { Object* self003 = self;
        StringWrapper* self = ((StringWrapper*)(self003));

        return (stringDgetDescription(self->wrapperValue));
      }
    }
    else if (subtypeOfClassP(testValue000)) {
      { Object* self004 = self;
        Class* self = ((Class*)(self004));

        return (classDgetDescription(self));
      }
    }
    else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_STELLA_SLOT)) {
      { Object* self005 = self;
        Slot* self = ((Slot*)(self005));

        return (slotDgetDescription(self));
      }
    }
    else {
      return (NULL);
    }
  }
}

NamedDescription* surrogateDgetDescription(Surrogate* self) {
  { Object* value = self->surrogateValue;
    ObjectStore* store = NULL;

    if (((boolean)(value))) {
      { Surrogate* testValue000 = safePrimaryType(value);

        if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_NAMED_DESCRIPTION)) {
          { Object* value000 = value;
            NamedDescription* value = ((NamedDescription*)(value000));

            return (value);
          }
        }
        else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_STELLA_RELATION)) {
          { Object* value001 = value;
            Relation* value = ((Relation*)(value001));

            if (((boolean)(((NamedDescription*)(dynamicSlotValue(value->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_DESCRIPTION, NULL)))))) {
              return (((NamedDescription*)(dynamicSlotValue(value->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_DESCRIPTION, NULL))));
            }
            else {
              return (createDescriptionForStellaRelation(value));
            }
          }
        }
        else {
          return (NULL);
        }
      }
    }
    else if (((boolean)(store = homeObjectStore(self)))) {
      return (store->fetchRelation(self));
    }
    else {
      return (NULL);
    }
  }
}

NamedDescription* stringDgetDescription(const char* self) {
  { Surrogate* surrogate = lookupSurrogate(self);
    ObjectStore* store = NULL;

    if (((boolean)(surrogate))) {
      return (getDescription(surrogate));
    }
    else if (((boolean)(store = ((ObjectStore*)(dynamicSlotValue(oMODULEo->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_OBJECT_STORE, NULL)))))) {
      return (store->fetchRelation(wrapString(self)));
    }
    else {
      return (NULL);
    }
  }
}

NamedDescription* classDgetDescription(Class* self) {
  if (((boolean)(((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_DESCRIPTION, NULL)))))) {
    return (((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_DESCRIPTION, NULL))));
  }
  else if (!logicClassP(self)) {
    if (!(oSUPPRESSNONLOGICOBJECTWARNINGpo)) {
      std::cout << "Reference to non-logic class: " << "`" << self->name() << "'" << std::endl << "Class must inherit 'THING' to be used by PowerLoom's logic." << std::endl << std::endl;
    }
    return (NULL);
  }
  else {
    return (getDescription(classLogicalType(self)));
  }
}

NamedDescription* slotDgetDescription(Slot* self) {
  if (((boolean)(((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_DESCRIPTION, NULL)))))) {
    return (((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_DESCRIPTION, NULL))));
  }
  else if (((boolean)(self->slotSlotref))) {
    return (getDescription(self->slotSlotref));
  }
  else {
    return (getDescription(lookupSlotref(self->slotOwner, self->slotName)));
  }
}

Surrogate* ensureDeferredDescription(Surrogate* self) {
  if ((!((boolean)(self->surrogateValue))) &&
      ((boolean)(homeObjectStore(self)))) {
    getDescription(self);
  }
  return (self);
}

boolean logicClassP(Class* self) {
  // Return TRUE if the class 'self' or one of its
  // supers supports indices that record extensions referenced by
  // the logic system. Also return true for literal classes.
  { boolean testValue000 = false;

    if (((boolean)(((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_DESCRIPTION, NULL)))))) {
      testValue000 = true;
    }
    else {
      {
        { boolean foundP000 = false;

          { Class* c = NULL;
            Cons* iter000 = self->classAllSuperClasses;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              c = ((Class*)(iter000->value));
              if (((boolean)(((NamedDescription*)(dynamicSlotValue(c->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_DESCRIPTION, NULL))))) ||
                  (c == ((Class*)(SGT_DESCRIPTIONS_STELLA_THING->surrogateValue)))) {
                foundP000 = true;
                break;
              }
            }
          }
          testValue000 = foundP000;
        }
        if (!testValue000) {
          testValue000 = (self == ((Class*)(SGT_DESCRIPTIONS_STELLA_THING->surrogateValue))) ||
              (subclassOfP(self, ((Class*)(SGT_DESCRIPTIONS_STELLA_LITERAL->surrogateValue))) ||
               (self == ((Class*)(SGT_DESCRIPTIONS_LOGIC_PROPOSITION->surrogateValue))));
        }
      }
    }
    if (testValue000) {
      return (true);
    }
  }
  if (!self->classFinalizedP) {
    { List* badsupers = collectBadSuperClasses(self->classType, list(0));

      if (badsupers->emptyP()) {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(STANDARD_WARNING->nativeStream) << "WARNING: " << "Could not determine whether " << self << " is a logic class, " << "because it is not finalized." << std::endl;
          helpSignalPropositionError(STANDARD_WARNING, KWD_DESCRIPTIONS_WARNING);
        }
      }
      else {
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(STANDARD_WARNING->nativeStream) << "WARNING: " << "Could not determine whether " << self << " is a logic class, " << "because it is not finalized." << std::endl << "   It has these undefined or bad supers: " << badsupers->theConsList << std::endl;
          helpSignalPropositionError(STANDARD_WARNING, KWD_DESCRIPTIONS_WARNING);
        }
      }
    }
  }
  return (false);
}

boolean variableArityDomainTypesNextP(AllPurposeIterator* self) {
  { Iterator* nestediterator = self->iteratorNestedIterator;

    if (((boolean)(nestediterator)) &&
        nestediterator->nextP()) {
      self->value = nestediterator->value;
    }
    else {
      {
        self->iteratorNestedIterator = NULL;
        self->value = self->iteratorObject;
      }
    }
    return (true);
  }
}

Iterator* wrapIteratorForVariableArity(Iterator* iterator) {
  { AllPurposeIterator* allpurposeiterator = newAllPurposeIterator();

    allpurposeiterator->iteratorNextCode = ((cpp_function_code)(&variableArityDomainTypesNextP));
    allpurposeiterator->iteratorNestedIterator = iterator;
    return (allpurposeiterator);
  }
}

Iterator* allDomainTypes(NamedDescription* self) {
  { Iterator* iterator = (functionDescriptionP(self) ? ((Iterator*)(self->ioVariableTypes->butLast())) : ((ListIterator*)(self->ioVariableTypes->allocateIterator())));

    if (variableArityP(self)) {
      return (wrapIteratorForVariableArity(iterator));
    }
    else {
      return (iterator);
    }
  }
}

Iterator* allArgumentTypes(NamedDescription* self) {
  if (variableArityP(self)) {
    return (wrapIteratorForVariableArity(((ListIterator*)(self->ioVariableTypes->allocateIterator()))));
  }
  else {
    return (((ListIterator*)(self->ioVariableTypes->allocateIterator())));
  }
}

// Table mapping logic variable names to variables or skolems.
// Used during construction of a proposition or description.
DEFINE_STELLA_SPECIAL(oLOGICVARIABLETABLEo, Cons* , NULL);

void pushLogicVariableBinding(Skolem* variable) {
  if (anonymousVariableP(variable)) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "ERROR: " << "Illegal nameless variable '?' found in list of\nquantified variables." << std::endl << "   Quantified variables must have names." << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_DESCRIPTIONS_ERROR);
      }
      throw *newPropositionError(stream000->theStringReader());
    }
  }
  oLOGICVARIABLETABLEo = cons(variable, oLOGICVARIABLETABLEo);
}

void popLogicVariableBinding() {
  { Cons* headcons = oLOGICVARIABLETABLEo;

    oLOGICVARIABLETABLEo = headcons->rest;
    headcons->free();
  }
}

void popLogicVariableBindings(Cons* variables) {
  { int i = NULL_INTEGER;
    int iter000 = 1;
    int upperBound000 = variables->length();

    for  (; iter000 <= upperBound000; 
          iter000 = iter000 + 1) {
      i = iter000;
      i = i;
      popLogicVariableBinding();
    }
  }
}

Object* lookupLogicVariableBinding(Symbol* variablename) {
  if (((boolean)(oLOGICVARIABLETABLEo))) {
    { Skolem* vbl = NULL;
      Cons* iter000 = oLOGICVARIABLETABLEo;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        vbl = ((Skolem*)(iter000->value));
        if (vbl->skolemName == variablename) {
          return (vbl);
        }
      }
    }
  }
  return (NULL);
}

// List of propositions extracted from parsing
// a list of quantified, typed variables.
DEFINE_STELLA_SPECIAL(oVARIABLETYPEPROPOSITIONSo, Cons* , NULL);

void parseOneVariableDeclaration(Object* vdec, List* localdeclarations) {
  { Symbol* variablename = NULL;
    Cons* isatree = NULL;
    PatternVariable* variable = NULL;

    { Surrogate* testValue000 = safePrimaryType(vdec);

      if (testValue000 == SGT_DESCRIPTIONS_STELLA_CONS) {
        { Object* vdec000 = vdec;
          Cons* vdec = ((Cons*)(vdec000));

          variablename = ((Symbol*)(vdec->rest->value));
          isatree = vdec;
        }
      }
      else if (subtypeOfSymbolP(testValue000)) {
        { Object* vdec001 = vdec;
          Symbol* vdec = ((Symbol*)(vdec001));

          variablename = vdec;
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    { PatternVariable* v = NULL;
      Cons* iter000 = localdeclarations->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        v = ((PatternVariable*)(iter000->value));
        if (v->skolemName == variablename) {
          variable = v;
        }
      }
    }
    if (!((boolean)(variable))) {
      variable = createVariable(NULL, variablename, true);
    }
    pushLogicVariableBinding(variable);
    localdeclarations->insertLast(variable);
    if (((boolean)(isatree))) {
      { Proposition* proposition = buildTopLevelProposition(isatree, false);

        if (!((boolean)(proposition))) {
          { OutputStringStream* stream001 = newOutputStringStream();

            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              *(stream001->nativeStream) << "ERROR: " << "Error in declarations" << "." << std::endl;
              helpSignalPropositionError(stream001, KWD_DESCRIPTIONS_ERROR);
            }
            throw *newPropositionError(stream001->theStringReader());
          }
        }
        if (proposition->kind == KWD_DESCRIPTIONS_ISA) {
          setDynamicSlotValue(proposition->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_VARIABLE_TYPEp, TRUE_WRAPPER, NULL);
          updateSkolemType(((Skolem*)((proposition->arguments->theArray)[0])), ((Surrogate*)(proposition->operatoR)));
          oVARIABLETYPEPROPOSITIONSo = cons(proposition, oVARIABLETYPEPROPOSITIONSo);
        }
      }
    }
  }
}

Cons* parseLogicVariableDeclarations(Object* tree) {
  { Cons* constree = (isaP(tree, SGT_DESCRIPTIONS_STELLA_CONS) ? ((Cons*)(tree)) : consList(1, tree));
    List* declarations = newList();

    { Object* term = NULL;
      Cons* iter000 = constree;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        term = iter000->value;
        parseOneVariableDeclaration(term, declarations);
      }
    }
    return (declarations->theConsList);
  }
}

Cons* helpBuildQuantifiedProposition(Cons* tree, boolean converttypestoconstraintsP, Proposition*& _Return1, Proposition*& _Return2) {
  { 
    BIND_STELLA_SPECIAL(oVARIABLETYPEPROPOSITIONSo, Cons*, NIL);
    { Object* quantifier = tree->value;
      Object* antecedentclause = tree->rest->rest->value;
      Object* consequentclause = tree->fourth();
      Cons* variables = NULL;
      Proposition* antecedentproposition = NULL;
      Proposition* consequentproposition = NULL;

      variables = parseLogicVariableDeclarations(tree->rest->value);
      if (((boolean)(antecedentclause))) {
        antecedentproposition = ((Proposition*)(buildProposition(antecedentclause)));
      }
      if (((boolean)(consequentclause))) {
        consequentproposition = ((Proposition*)(buildProposition(consequentclause)));
      }
      popLogicVariableBindings(variables);
      if (converttypestoconstraintsP) {
        if (!(oVARIABLETYPEPROPOSITIONSo == NIL)) {
          if (((boolean)(antecedentproposition))) {
            oVARIABLETYPEPROPOSITIONSo = cons(antecedentproposition, oVARIABLETYPEPROPOSITIONSo);
          }
          oVARIABLETYPEPROPOSITIONSo = oVARIABLETYPEPROPOSITIONSo->reverse()->removeDuplicates();
          antecedentproposition = conjoinPropositions(oVARIABLETYPEPROPOSITIONSo);
        }
      }
      _Return1 = antecedentproposition;
      _Return2 = consequentproposition;
      return (variables);
    }
  }
}

Cons* buildQuantifiedProposition(Cons* tree, boolean converttypestoconstraintsP, Proposition*& _Return1, Proposition*& _Return2) {
  if (((GeneralizedSymbol*)(tree->value)) == SYM_DESCRIPTIONS_STELLA_EXISTS) {
    { 
      BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_DESCRIPTIONS_DESCRIPTION);
      return (helpBuildQuantifiedProposition(tree, converttypestoconstraintsP, _Return1, _Return2));
    }
  }
  else {
    { 
      BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_DESCRIPTIONS_DESCRIPTION);
      return (helpBuildQuantifiedProposition(tree, converttypestoconstraintsP, _Return1, _Return2));
    }
  }
}

Vector* copyConsListToVariablesVector(Cons* conslist) {
  if (conslist == NIL) {
    return (ZERO_VARIABLES_VECTOR);
  }
  { Vector* vector = stella::newVector(conslist->length());

    { Object* t = NULL;
      Cons* iter000 = conslist;
      int i = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        t = iter000->value;
        i = iter001;
        (vector->theArray)[i] = (((PatternVariable*)(t)));
      }
    }
    return (vector);
  }
}

boolean equivalentHoldsPropositionP(Proposition* self, Proposition* other, KeyValueMap* mapping) {
  { boolean testValue000 = false;

    testValue000 = equivalentFormulaeP((self->arguments->theArray)[0], other->operatoR, mapping);
    if (testValue000) {
      testValue000 = (self->arguments->length() - 1) == other->arguments->length();
      if (testValue000) {
        { boolean alwaysP000 = true;

          { int i1 = NULL_INTEGER;
            int iter000 = 1;
            Object* arg2 = NULL;
            Vector* vector000 = other->arguments;
            int index000 = 0;
            int length000 = vector000->length();

            for  (; index000 < length000; 
                  iter000 = iter000 + 1,
                  index000 = index000 + 1) {
              i1 = iter000;
              arg2 = (vector000->theArray)[index000];
              if (!equivalentFormulaeP((self->arguments->theArray)[i1], arg2, mapping)) {
                alwaysP000 = false;
                break;
              }
            }
          }
          testValue000 = alwaysP000;
        }
      }
    }
    { boolean value000 = testValue000;

      return (value000);
    }
  }
}

boolean equivalentCommutativePropositionsP(Proposition* self, Proposition* other, KeyValueMap* mapping) {
  { boolean testValue000 = false;

    testValue000 = self->operatoR == other->operatoR;
    if (testValue000) {
      testValue000 = self->arguments->length() == other->arguments->length();
      if (testValue000) {
        { boolean alwaysP000 = true;

          { Object* arg1 = NULL;
            Vector* vector000 = self->arguments;
            int index000 = 0;
            int length000 = vector000->length();

            for  (; index000 < length000; 
                  index000 = index000 + 1) {
              arg1 = (vector000->theArray)[index000];
              { boolean testValue001 = false;

                { boolean foundP000 = false;

                  { Object* arg2 = NULL;
                    Vector* vector001 = other->arguments;
                    int index001 = 0;
                    int length001 = vector001->length();

                    for  (; index001 < length001; 
                          index001 = index001 + 1) {
                      arg2 = (vector001->theArray)[index001];
                      if (equivalentFormulaeP(arg1, arg2, mapping)) {
                        foundP000 = true;
                        break;
                      }
                    }
                  }
                  testValue001 = foundP000;
                }
                testValue001 = !testValue001;
                if (testValue001) {
                  alwaysP000 = false;
                  break;
                }
              }
            }
          }
          testValue000 = alwaysP000;
        }
      }
    }
    { boolean value000 = testValue000;

      return (value000);
    }
  }
}

boolean helpEquivalentPropositionsP(Proposition* self, Proposition* other, KeyValueMap* mapping, boolean ignorelastargP) {
  if (self == other) {
    return (true);
  }
  if (!(self->kind == other->kind)) {
    return (false);
  }
  { Keyword* testValue000 = self->kind;

    if ((testValue000 == KWD_DESCRIPTIONS_AND) ||
        ((testValue000 == KWD_DESCRIPTIONS_OR) ||
         (testValue000 == KWD_DESCRIPTIONS_EQUIVALENT))) {
      return (equivalentCommutativePropositionsP(self, other, mapping));
    }
    else {
      { Keyword* testValue001 = self->kind;

        if ((testValue001 == KWD_DESCRIPTIONS_FORALL) ||
            (testValue001 == KWD_DESCRIPTIONS_EXISTS)) {
          { Vector* iovars1 = ((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_IO_VARIABLES, NULL)));
            Vector* iovars2 = ((Vector*)(dynamicSlotValue(other->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_IO_VARIABLES, NULL)));

            if (!(iovars1->length() == iovars2->length())) {
              return (false);
            }
            if (!((boolean)(mapping))) {
              mapping = newKeyValueMap();
            }
            { PatternVariable* v1 = NULL;
              Vector* vector000 = iovars1;
              int index000 = 0;
              int length000 = vector000->length();
              PatternVariable* v2 = NULL;
              Vector* vector001 = iovars2;
              int index001 = 0;
              int length001 = vector001->length();

              for  (; (index000 < length000) &&
                        (index001 < length001); 
                    index000 = index000 + 1,
                    index001 = index001 + 1) {
                v1 = ((PatternVariable*)((vector000->theArray)[index000]));
                v2 = ((PatternVariable*)((vector001->theArray)[index001]));
                mapping->insertAt(v1, v2);
              }
            }
          }
        }
        else {
        }
      }
      { Vector* selfargs = self->arguments;
        Vector* otherargs = other->arguments;

        { boolean testValue002 = false;

          testValue002 = self->operatoR == other->operatoR;
          if (testValue002) {
            { boolean alwaysP000 = true;

              { Object* arg1 = NULL;
                Vector* vector002 = selfargs;
                int index002 = 0;
                int length002 = vector002->length();
                Object* arg2 = NULL;
                Vector* vector003 = otherargs;
                int index003 = 0;
                int length003 = vector003->length();
                int i = NULL_INTEGER;
                int iter000 = 2;
                int upperBound000 = (ignorelastargP ? selfargs->length() : NULL_INTEGER);
                boolean unboundedP000 = upperBound000 == NULL_INTEGER;

                for  (; (index002 < length002) &&
                          ((index003 < length003) &&
                           (unboundedP000 ||
                            (iter000 <= upperBound000))); 
                      index002 = index002 + 1,
                      index003 = index003 + 1,
                      iter000 = iter000 + 1) {
                  arg1 = (vector002->theArray)[index002];
                  arg2 = (vector003->theArray)[index003];
                  i = iter000;
                  if (!equivalentFormulaeP(arg1, arg2, mapping)) {
                    alwaysP000 = false;
                    break;
                  }
                }
              }
              testValue002 = alwaysP000;
            }
            if (testValue002) {
              testValue002 = selfargs->length() == otherargs->length();
            }
          }
          if (!testValue002) {
            testValue002 = ((boolean)(mapping)) &&
                ((self->operatoR == SGT_DESCRIPTIONS_PL_KERNEL_KB_HOLDS) &&
                 equivalentHoldsPropositionP(self, other, mapping));
          }
          { boolean value000 = testValue002;

            return (value000);
          }
        }
      }
    }
  }
}

boolean equivalentPropositionsP(Proposition* self, Proposition* other, KeyValueMap* mapping) {
  return (helpEquivalentPropositionsP(self, other, mapping, false));
}

boolean equivalentFunctionPropositionsP(Proposition* self, Proposition* other, KeyValueMap* mapping) {
  return ((self->kind == KWD_DESCRIPTIONS_FUNCTION) &&
      ((other->kind == KWD_DESCRIPTIONS_FUNCTION) &&
       helpEquivalentPropositionsP(self, other, mapping, true)));
}

boolean equivalentDescriptionsP(Description* self, Description* other, KeyValueMap* mapping) {
  if (self == other) {
    return (true);
  }
  if (((boolean)(self->descriptionName())) &&
      ((boolean)(other->descriptionName()))) {
    return (false);
  }
  if (!(self->arity() == other->arity())) {
    return (false);
  }
  if (namedDescriptionP(self)) {
    return (false);
  }
  else {
    if (!((boolean)(mapping))) {
      mapping = newKeyValueMap();
    }
    { PatternVariable* v1 = NULL;
      Vector* vector000 = self->ioVariables;
      int index000 = 0;
      int length000 = vector000->length();
      PatternVariable* v2 = NULL;
      Vector* vector001 = other->ioVariables;
      int index001 = 0;
      int length001 = vector001->length();

      for  (; (index000 < length000) &&
                (index001 < length001); 
            index000 = index000 + 1,
            index001 = index001 + 1) {
        v1 = ((PatternVariable*)((vector000->theArray)[index000]));
        v2 = ((PatternVariable*)((vector001->theArray)[index001]));
        mapping->insertAt(v1, v2);
        mapping->insertAt(v2, v1);
      }
    }
    { PatternVariable* v1 = NULL;
      Vector* vector002 = self->ioVariables;
      int index002 = 0;
      int length002 = vector002->length();
      PatternVariable* v2 = NULL;
      Vector* vector003 = other->ioVariables;
      int index003 = 0;
      int length003 = vector003->length();

      for  (; (index002 < length002) &&
                (index003 < length003); 
            index002 = index002 + 1,
            index003 = index003 + 1) {
        v1 = ((PatternVariable*)((vector002->theArray)[index002]));
        v2 = ((PatternVariable*)((vector003->theArray)[index003]));
        if (!((mapping->lookup(v1) == v2) &&
            (mapping->lookup(v2) == v1))) {
          return (false);
        }
      }
    }
    { PatternVariable* v1 = NULL;
      Vector* vector004 = self->internalVariables;
      int index004 = 0;
      int length004 = vector004->length();
      PatternVariable* v2 = NULL;
      Vector* vector005 = other->internalVariables;
      int index005 = 0;
      int length005 = vector005->length();

      for  (; (index004 < length004) &&
                (index005 < length005); 
            index004 = index004 + 1,
            index005 = index005 + 1) {
        v1 = ((PatternVariable*)((vector004->theArray)[index004]));
        v2 = ((PatternVariable*)((vector005->theArray)[index005]));
        mapping->insertAt(v1, v2);
      }
    }
    return (equivalentFormulaeP(self->proposition, other->proposition, mapping));
  }
}

boolean equivalentEnumerationsP(Collection* self, Collection* other) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_STELLA_SET)) {
      { Collection* self000 = self;
        Set* self = ((Set*)(self000));

        { boolean testValue001 = false;

          testValue001 = self->length() == other->length();
          if (testValue001) {
            { boolean alwaysP000 = true;

              { Object* m = NULL;
                ListIterator* iter000 = ((ListIterator*)(self->allocateIterator()));

                for (; iter000->nextP(); ) {
                  m = iter000->value;
                  if (!other->memberP(m)) {
                    alwaysP000 = false;
                    break;
                  }
                }
              }
              testValue001 = alwaysP000;
            }
          }
          { boolean value000 = testValue001;

            return (value000);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_STELLA_LIST)) {
      { Collection* self001 = self;
        List* self = ((List*)(self001));

        { boolean testValue002 = false;

          testValue002 = self->length() == other->length();
          if (testValue002) {
            { boolean alwaysP001 = true;

              { Object* m = NULL;
                Cons* iter001 = self->theConsList;

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  m = iter001->value;
                  if (!other->memberP(m)) {
                    alwaysP001 = false;
                    break;
                  }
                }
              }
              testValue002 = alwaysP001;
            }
          }
          { boolean value001 = testValue002;

            return (value001);
          }
        }
      }
    }
    else {
      return (false);
    }
  }
}

boolean equivalentFormulaeP(Object* self, Object* other, KeyValueMap* mapping) {
  { Object* surrogatevalue = NULL;

    if (isaP(self, SGT_DESCRIPTIONS_STELLA_SURROGATE)) {
      surrogatevalue = ((Surrogate*)(self))->surrogateValue;
      if (((boolean)(surrogatevalue))) {
        self = surrogatevalue;
      }
    }
    if (isaP(other, SGT_DESCRIPTIONS_STELLA_SURROGATE)) {
      surrogatevalue = ((Surrogate*)(other))->surrogateValue;
      if (((boolean)(surrogatevalue))) {
        other = surrogatevalue;
      }
    }
  }
  if (((boolean)(mapping)) &&
      (eqlP(other, mapping->lookup(self)) ||
       eqlP(self, mapping->lookup(other)))) {
    return (true);
  }
  if (equalP(self, other)) {
    return (true);
  }
  if (((boolean)(mapping))) {
    if (oUNIFY_PROPOSITIONSpo &&
        (variableP(self) ||
         variableP(other))) {
      if (!((boolean)(oQUERYITERATORo))) {
        mapping->insertAt(self, other);
        return (true);
      }
      { Object* value1 = argumentBoundTo(self);
        Object* value2 = argumentBoundTo(other);

        if ((!((boolean)(value1))) ||
            (!((boolean)(value2)))) {
          mapping->insertAt(self, other);
          return (true);
        }
        else {
          return (equalP(value1, value2));
        }
      }
    }
  }
  if (!(self->primaryType() == other->primaryType())) {
    return (false);
  }
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_PROPOSITION)) {
      { Object* self000 = self;
        Proposition* self = ((Proposition*)(self000));

        return (equivalentPropositionsP(self, ((Proposition*)(other)), mapping));
      }
    }
    else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_DESCRIPTION)) {
      { Object* self001 = self;
        Description* self = ((Description*)(self001));

        return (equivalentDescriptionsP(self, ((Description*)(other)), mapping));
      }
    }
    else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_STELLA_SET)) {
      { Object* self002 = self;
        Set* self = ((Set*)(self002));

        return (equivalentEnumerationsP(self, ((Collection*)(other))));
      }
    }
    else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_STELLA_LIST)) {
      { Object* self003 = self;
        List* self = ((List*)(self003));

        return (equivalentEnumerationsP(self, ((Collection*)(other))));
      }
    }
    else {
      return (false);
    }
  }
}

boolean sameAndUniqueArgumentsP(Vector* variables, Vector* arguments) {
  if (equalP(variables, arguments)) {
    { int count = 0;

      { PatternVariable* v = NULL;
        Vector* vector000 = variables;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          v = ((PatternVariable*)((vector000->theArray)[index000]));
          { PatternVariable* v2 = NULL;
            Vector* vector001 = variables;
            int index001 = 0;
            int length001 = vector001->length();

            for  (; index001 < length001; 
                  index001 = index001 + 1) {
              v2 = ((PatternVariable*)((vector001->theArray)[index001]));
              if (v == v2) {
                count = count + 1;
              }
            }
          }
        }
      }
      return (count == variables->length());
    }
  }
  return (false);
}

DEFINE_STELLA_SPECIAL(oUNIFY_PROPOSITIONSpo, boolean , false);

boolean unifyPropositionsP(Proposition* self, Proposition* other, KeyValueMap* mapping) {
  { 
    BIND_STELLA_SPECIAL(oUNIFY_PROPOSITIONSpo, boolean, true);
    return (equivalentPropositionsP(self, other, mapping));
  }
}

boolean descriptionP(Object* self) {
  // Return TRUE if 'self' is a description.
  return (((boolean)(self)) &&
      isaP(self, SGT_DESCRIPTIONS_LOGIC_DESCRIPTION));
}

boolean unnamedDescriptionP(Object* self) {
  // Return TRUE if 'self' is an unnamed description.
  return (((boolean)(self)) &&
      (isaP(self, SGT_DESCRIPTIONS_LOGIC_DESCRIPTION) &&
       (!((boolean)(((Description*)(self))->surrogateValueInverse)))));
}

boolean namedDescriptionP(Description* self) {
  // Return TRUE if 'self' is the description of a named class or relation.
  return (((boolean)(self->surrogateValueInverse)));
}

LogicObject* Description::findDuplicateNamedDescription() {
  { Description* self = this;

    if (namedDescriptionP(self)) {
      return (self);
    }
    { Proposition* proposition = self->proposition;

      { Keyword* testValue000 = proposition->kind;

        if (testValue000 == KWD_DESCRIPTIONS_AND) {
          { Proposition* onlygoal = NULL;

            { Object* arg = NULL;
              Vector* vector000 = proposition->arguments;
              int index000 = 0;
              int length000 = vector000->length();

              for  (; index000 < length000; 
                    index000 = index000 + 1) {
                arg = (vector000->theArray)[index000];
                if (coerceWrappedBooleanToBoolean(((Proposition*)(arg))->variableTypeP_reader())) {
                }
                else if (((boolean)(onlygoal))) {
                  return (NULL);
                }
                else {
                  onlygoal = ((Proposition*)(arg));
                }
              }
            }
            if (((boolean)(onlygoal)) &&
                sameAndUniqueArgumentsP(self->ioVariables, ((onlygoal->kind == KWD_DESCRIPTIONS_NOT) ? ((Proposition*)((onlygoal->arguments->theArray)[0]))->arguments : onlygoal->arguments))) {
              return (extractGoalDescription(onlygoal, NULL));
            }
          }
        }
        else if (testValue000 == KWD_DESCRIPTIONS_NOT) {
          if (sameAndUniqueArgumentsP(self->ioVariables, ((Proposition*)((proposition->arguments->theArray)[0]))->arguments)) {
            return (extractGoalDescription(proposition, NULL));
          }
        }
        else {
          if (sameAndUniqueArgumentsP(self->ioVariables, proposition->arguments)) {
            { Description* nameddescription = extractGoalDescription(proposition, NULL);

              if (((boolean)(nameddescription)) &&
                  (self->ioVariables->length() == nameddescription->ioVariables->length())) {
                return (nameddescription);
              }
            }
          }
        }
      }
      return (NULL);
    }
  }
}

Description* findDuplicateComplexDescription(Description* self) {
  { IntegerWrapper* index = wrapInteger(propositionHashIndex(self->proposition, NULL, false));
    List* bucket = ((List*)(oSTRUCTURED_OBJECTS_INDEXo->lookup(index)));
    Module* homemodule = self->homeContext->baseModule;
    KeyValueMap* mapping = newKeyValueMap();

    if (!((boolean)(bucket))) {
      oSTRUCTURED_OBJECTS_INDEXo->insertAt(index, list(1, self));
      return (NULL);
    }
    bucket->removeDeletedMembers();
    if (((boolean)(((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_EXTERNAL_VARIABLES, NULL))))) &&
        ((boolean)(oQUERYITERATORo))) {
      mapping = newKeyValueMap();
      { PatternVariable* v = NULL;
        Vector* vector000 = ((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_EXTERNAL_VARIABLES, NULL)));
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          v = ((PatternVariable*)((vector000->theArray)[index000]));
          { Object* temp000 = argumentBoundTo(v);

            mapping->insertAt(v, (((boolean)(temp000)) ? temp000 : v));
          }
        }
      }
    }
    { ContextSensitiveObject* d = NULL;
      Cons* iter000 = bucket->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        d = ((ContextSensitiveObject*)(iter000->value));
        if (isaP(d, SGT_DESCRIPTIONS_LOGIC_DESCRIPTION) &&
            (equivalentDescriptionsP(self, ((Description*)(d)), mapping) &&
             subcontextP(homemodule, d->homeContext->baseModule))) {
          return (((Description*)(d)));
        }
      }
    }
    bucket->push(self);
    return (NULL);
  }
}

Description* findDuplicateDescription(Description* self) {
  if (namedDescriptionP(self)) {
    return (NULL);
  }
  else {
    { LogicObject* temp000 = self->findDuplicateNamedDescription();

      { LogicObject* value000 = (((boolean)(temp000)) ? temp000 : findDuplicateComplexDescription(self));

        return (((Description*)(value000)));
      }
    }
  }
}

boolean containsNestedArgumentP(Proposition* proposition) {
  { Keyword* testValue000 = proposition->kind;

    if ((testValue000 == KWD_DESCRIPTIONS_ISA) ||
        ((testValue000 == KWD_DESCRIPTIONS_FUNCTION) ||
         ((testValue000 == KWD_DESCRIPTIONS_PREDICATE) ||
          ((testValue000 == KWD_DESCRIPTIONS_EQUIVALENT) ||
           (testValue000 == KWD_DESCRIPTIONS_IMPLIES))))) {
      { Object* term = NULL;
        Vector* vector000 = proposition->arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          term = (vector000->theArray)[index000];
          if (subtypeOfP(safePrimaryType(term), SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
            { Object* term000 = term;
              PatternVariable* term = ((PatternVariable*)(term000));

              if (((boolean)(term->definingProposition))) {
                return (true);
              }
            }
          }
          else {
          }
        }
      }
    }
    else {
    }
  }
  return (false);
}

Proposition* expandIfProposition(Proposition* ifproposition) {
  { Vector* arguments = ifproposition->arguments;
    Object* testprop = (arguments->theArray)[0];
    Proposition* negatedtestprop = createProposition(SYM_DESCRIPTIONS_STELLA_NOT, 1);
    Object* truevalue = (arguments->theArray)[1];
    Object* falsevalue = (arguments->theArray)[2];
    PatternVariable* valuevariable = ((PatternVariable*)((ifproposition->arguments->theArray)[(ifproposition->arguments->length() - 1)]));
    Proposition* trueequivalence = createEquivalenceProposition(valuevariable, truevalue);
    Proposition* falseequivalence = (((boolean)(falsevalue)) ? createEquivalenceProposition(valuevariable, falsevalue) : ((Proposition*)(NULL)));

    valuevariable->definingProposition = NULL;
    if (((boolean)(falsevalue))) {
      {
        (negatedtestprop->arguments->theArray)[0] = ((isaP(testprop, SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE) ? testprop : shallowCopyProposition(((Proposition*)(testprop)))));
        return (disjoinPropositions(consList(2, conjoinTwoPropositions(((Proposition*)(testprop)), trueequivalence), conjoinTwoPropositions(negatedtestprop, falseequivalence))));
      }
    }
    else {
      return (conjoinTwoPropositions(((Proposition*)(testprop)), trueequivalence));
    }
  }
}

void helpCollectFlattenedArguments(Proposition* self, List* flattenedarguments, List* existsvariables) {
  { Object* term = NULL;
    Vector* vector000 = self->arguments;
    int index000 = 0;
    int length000 = vector000->length();

    for  (; index000 < length000; 
          index000 = index000 + 1) {
      term = (vector000->theArray)[index000];
      if (subtypeOfP(safePrimaryType(term), SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
        { Object* term000 = term;
          PatternVariable* term = ((PatternVariable*)(term000));

          { Proposition* functionarg = term->definingProposition;

            if (((boolean)(functionarg)) &&
                (!existsvariables->memberP(term))) {
              existsvariables->push(term);
              helpCollectFlattenedArguments(functionarg, flattenedarguments, existsvariables);
              if (functionarg->operatoR == SGT_DESCRIPTIONS_STELLA_PROPOSITIONdIF) {
                flattenedarguments->push(expandIfProposition(functionarg));
              }
              else {
                flattenedarguments->push(functionarg);
              }
            }
          }
        }
      }
      else {
      }
    }
  }
}

List* yieldFlattenedArguments(Proposition* proposition, List* existsvariables) {
  { List* flattenedarguments = newList();

    helpCollectFlattenedArguments(proposition, flattenedarguments, existsvariables);
    flattenedarguments->push(proposition);
    existsvariables->reverse();
    return (flattenedarguments->reverse());
  }
}

Proposition* flattenNestedFunctionArguments(Proposition* proposition) {
  { Proposition* existsproposition = createProposition(SYM_DESCRIPTIONS_STELLA_EXISTS, 1);
    List* existsvariables = newList();
    List* flattenedpropositions = yieldFlattenedArguments(proposition, existsvariables);
    Proposition* andproposition = createProposition(SYM_DESCRIPTIONS_STELLA_AND, flattenedpropositions->length());

    { Proposition* prop = NULL;
      Cons* iter000 = flattenedpropositions->theConsList;
      int i = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        prop = ((Proposition*)(iter000->value));
        i = iter001;
        (andproposition->arguments->theArray)[i] = prop;
      }
    }
    { PatternVariable* vbl = NULL;
      Cons* iter002 = existsvariables->theConsList;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        vbl = ((PatternVariable*)(iter002->value));
        vbl->definingProposition = NULL;
      }
    }
    setDynamicSlotValue(existsproposition->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_IO_VARIABLES, copyConsListToVariablesVector(existsvariables->theConsList), NULL);
    existsvariables->free();
    (existsproposition->arguments->theArray)[0] = andproposition;
    return (existsproposition);
  }
}

void collapseValueOfChainsForIoVariables(Vector* iovariables) {
  { PatternVariable* tightestvariable = NULL;

    { PatternVariable* vbl = NULL;
      Vector* vector000 = iovariables;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter000 = 0;

      for  (; index000 < length000; 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        vbl = ((PatternVariable*)((vector000->theArray)[index000]));
        i = iter000;
        if (!(vbl == innermostVariableOf(vbl))) {
          tightestvariable = innermostVariableOf(vbl);
          (iovariables->theArray)[i] = tightestvariable;
          tightestvariable->skolemName = vbl->skolemName;
          { PatternVariable* object000 = tightestvariable;
            Cons* value000 = NIL;
            Object* oldValue000 = object000->variableValueInverse;
            Object* newValue000 = updateInContext(oldValue000, value000, object000->homeContext, false);

            if (!(((boolean)(oldValue000)) &&
                (oldValue000->primaryType() == SGT_DESCRIPTIONS_STELLA_CS_VALUE))) {
              object000->variableValueInverse = newValue000;
            }
          }
        }
      }
    }
  }
}

Vector* removeNullsInVariablesVector(Vector* iovariables) {
  if (!iovariables->memberP(NULL)) {
    return (iovariables);
  }
  { Cons* newvbllist = NIL;
    Vector* result = NULL;

    { PatternVariable* vbl = NULL;
      Vector* vector000 = iovariables;
      int index000 = 0;
      int length000 = vector000->length();
      Cons* collect000 = NULL;

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        vbl = ((PatternVariable*)((vector000->theArray)[index000]));
        if (((boolean)(vbl))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(vbl, NIL);
              if (newvbllist == NIL) {
                newvbllist = collect000;
              }
              else {
                addConsToEndOfConsList(newvbllist, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(vbl, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    result = copyConsListToVariablesVector(newvbllist);
    return (result);
  }
}

void tightenArgumentBindings(Proposition* proposition, Vector* iovariables) {
  { 
    { Object* arg = NULL;
      Vector* vector000 = proposition->arguments;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter000 = 0;

      for  (; index000 < length000; 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        arg = (vector000->theArray)[index000];
        i = iter000;
        { Surrogate* testValue000 = safePrimaryType(arg);

          if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
            { Object* arg000 = arg;
              PatternVariable* arg = ((PatternVariable*)(arg000));

              { Object* value = ((((boolean)(iovariables)) &&
                    iovariables->memberP(arg)) ? innermostVariableOf(arg) : innermostOf(arg));

                if (!(value == arg)) {
                  (proposition->arguments->theArray)[i] = value;
                }
              }
            }
          }
          else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_PROPOSITION)) {
            { Object* arg001 = arg;
              Proposition* arg = ((Proposition*)(arg001));

              tightenArgumentBindings(arg, iovariables);
            }
          }
          else {
          }
        }
      }
    }
    if (((boolean)(((Vector*)(dynamicSlotValue(proposition->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_IO_VARIABLES, NULL)))))) {
      { Vector* quantifiedvariables = ((Vector*)(dynamicSlotValue(proposition->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_IO_VARIABLES, NULL)));

        { PatternVariable* vbl = NULL;
          Vector* vector001 = quantifiedvariables;
          int index001 = 0;
          int length001 = vector001->length();
          int i = NULL_INTEGER;
          int iter001 = 0;

          for  (; index001 < length001; 
                index001 = index001 + 1,
                iter001 = iter001 + 1) {
            vbl = ((PatternVariable*)((vector001->theArray)[index001]));
            i = iter001;
            if (!(vbl == innermostVariableOf(vbl))) {
              (quantifiedvariables->theArray)[i] = NULL;
            }
          }
        }
        setDynamicSlotValue(proposition->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_IO_VARIABLES, removeNullsInVariablesVector(quantifiedvariables), NULL);
        normalizeProposition(proposition);
      }
    }
  }
}

void equateTopLevelEquivalences(Proposition* proposition, Vector* iovariables, Keyword* kind) {
  { Vector* arguments = proposition->arguments;

    { Keyword* testValue000 = proposition->kind;

      if (testValue000 == KWD_DESCRIPTIONS_EQUIVALENT) {
        { Object* arg1 = innermostOf((arguments->theArray)[0]);
          Object* arg2 = innermostOf((arguments->theArray)[1]);

          if ((variableP(arg1) ||
              argumentBoundP(arg1)) &&
              (variableP(arg2) ||
               argumentBoundP(arg2))) {
            if (iovariables->memberP(arg1)) {
              if (iovariables->memberP(arg2)) {
                if (kind == KWD_DESCRIPTIONS_TAIL) {
                  equateValues(proposition, arg1, arg2);
                }
              }
              else {
                equateValues(proposition, arg2, arg1);
              }
            }
            else {
              equateValues(proposition, arg1, arg2);
            }
          }
        }
      }
      else if (testValue000 == KWD_DESCRIPTIONS_AND) {
        { Object* arg = NULL;
          Vector* vector000 = arguments;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            arg = (vector000->theArray)[index000];
            equateTopLevelEquivalences(((Proposition*)(arg)), iovariables, kind);
          }
        }
      }
      else if (testValue000 == KWD_DESCRIPTIONS_EXISTS) {
        equateTopLevelEquivalences(((Proposition*)((arguments->theArray)[0])), iovariables, kind);
      }
      else if (testValue000 == KWD_DESCRIPTIONS_FUNCTION) {
        evaluateFunctionProposition(proposition);
      }
      else {
      }
    }
  }
}

void collectAllVariables(Proposition* self, List* collection, List* beenthere) {
  beenthere->insert(self);
  { Object* arg = NULL;
    Vector* vector000 = self->arguments;
    int index000 = 0;
    int length000 = vector000->length();

    for  (; index000 < length000; 
          index000 = index000 + 1) {
      arg = (vector000->theArray)[index000];
      { Surrogate* testValue000 = safePrimaryType(arg);

        if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
          { Object* arg000 = arg;
            PatternVariable* arg = ((PatternVariable*)(arg000));

            collection->insertNew(arg);
          }
        }
        else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_PROPOSITION)) {
          { Object* arg001 = arg;
            Proposition* arg = ((Proposition*)(arg001));

            if (!(beenthere->memberP(arg))) {
              collectAllVariables(arg, collection, beenthere);
            }
          }
        }
        else {
        }
      }
    }
  }
}

void computeInternalVariables(Description* self) {
  { List* collection = newList();
    List* beenthere = newList();

    collectAllVariables(self->proposition, collection, beenthere);
    { PatternVariable* vbl = NULL;
      Vector* vector000 = self->ioVariables;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        vbl = ((PatternVariable*)((vector000->theArray)[index000]));
        collection->remove(vbl);
      }
    }
    if (((boolean)(((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_EXTERNAL_VARIABLES, NULL)))))) {
      { PatternVariable* vbl = NULL;
        Vector* vector001 = ((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_EXTERNAL_VARIABLES, NULL)));
        int index001 = 0;
        int length001 = vector001->length();

        for  (; index001 < length001; 
              index001 = index001 + 1) {
          vbl = ((PatternVariable*)((vector001->theArray)[index001]));
          collection->remove(vbl);
        }
      }
    }
    self->internalVariables = copyConsListToVariablesVector(collection->theConsList);
    collection->free();
    beenthere->free();
  }
}

// Used by 'evaluate-DESCRIPTION-term' for collecting
// a list of variables declared external to the description in which they
// are referenced.
DEFINE_STELLA_SPECIAL(oEXTERNALVARIABLESo, Cons* , NULL);

void collectExternalVariables(Proposition* proposition) {
  { Object* arg = NULL;
    Vector* vector000 = proposition->arguments;
    int index000 = 0;
    int length000 = vector000->length();

    for  (; index000 < length000; 
          index000 = index000 + 1) {
      arg = (vector000->theArray)[index000];
      { Surrogate* testValue000 = safePrimaryType(arg);

        if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
          { Object* arg000 = arg;
            PatternVariable* arg = ((PatternVariable*)(arg000));

            if (oLOGICVARIABLETABLEo->memberP(arg) &&
                (!oEXTERNALVARIABLESo->memberP(arg))) {
              oEXTERNALVARIABLESo = cons(arg, oEXTERNALVARIABLESo);
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_PROPOSITION)) {
          { Object* arg001 = arg;
            Proposition* arg = ((Proposition*)(arg001));

            collectExternalVariables(arg);
          }
        }
        else {
        }
      }
    }
  }
}

Description* finishBuildingDescription(Description* description, boolean checkforduplicateP, Keyword* kind) {
  { Proposition* proposition = description->proposition;

    normalizeProposition(proposition);
    if (proposition->kind == KWD_DESCRIPTIONS_EXISTS) {
      proposition = ((Proposition*)((proposition->arguments->theArray)[0]));
      description->proposition = proposition;
    }
    resolveUnresolvedSlotReferences(description);
    updateSkolemTypeFromIsaAssertions(proposition);
    normalizeDescriptiveProposition(proposition, description->ioVariables, kind);
    recursivelyFastenDownPropositions(proposition, true);
    computeInternalVariables(description);
    if (checkforduplicateP) {
      { Description* duplicatedescription = findDuplicateDescription(description);

        if (((boolean)(duplicatedescription))) {
          description = duplicatedescription;
        }
      }
    }
    return (description);
  }
}

Description* evaluateDescriptionTerm(Cons* term, boolean checkforduplicateP) {
  { Description* description = createDescription(NULL_INTEGER, false);

    if (((GeneralizedSymbol*)(term->value)) == SYM_DESCRIPTIONS_LOGIC_THE_ONLY) {
      setDynamicSlotValue(description->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_IOTAp, TRUE_WRAPPER, FALSE_WRAPPER);
    }
    else {
    }
    { 
      BIND_STELLA_SPECIAL(oDESCRIPTIONUNDERCONSTRUCTIONo, Object*, description);
      BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_DESCRIPTIONS_DESCRIPTION);
      BIND_STELLA_SPECIAL(oVARIABLEIDCOUNTERo, int, oVARIABLEIDCOUNTERo);
      { Cons* iovars = NULL;
        Proposition* proposition = NULL;
        Proposition* unused = NULL;

        iovars = buildQuantifiedProposition(term, true, proposition, unused);
        unused = unused;
        description->ioVariables = copyConsListToVariablesVector(iovars);
        if (!(oLOGICVARIABLETABLEo == NIL)) {
          { 
            BIND_STELLA_SPECIAL(oEXTERNALVARIABLESo, Cons*, NIL);
            collectExternalVariables(proposition);
            if (!(oEXTERNALVARIABLESo == NIL)) {
              setDynamicSlotValue(description->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_EXTERNAL_VARIABLES, copyConsListToVariablesVector(oEXTERNALVARIABLESo), NULL);
            }
          }
        }
        description->proposition = (((boolean)(proposition)) ? proposition : TRUE_PROPOSITION);
      }
      return (finishBuildingDescription(description, checkforduplicateP, KWD_DESCRIPTIONS_TOP_LEVEL));
    }
  }
}

Cons* removeVariableTypePropositions(Proposition* proposition) {
  { Keyword* testValue000 = proposition->kind;

    if (testValue000 == KWD_DESCRIPTIONS_AND) {
      { Cons* typedeclarations = NIL;
        Proposition* goalproposition = NULL;

        { Object* arg = NULL;
          Vector* vector000 = proposition->arguments;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            arg = (vector000->theArray)[index000];
            if (coerceWrappedBooleanToBoolean(((Proposition*)(arg))->variableTypeP_reader())) {
              typedeclarations = cons(arg, typedeclarations);
            }
            else if (((boolean)(goalproposition))) {
            }
            else {
              goalproposition = ((Proposition*)(arg));
            }
          }
        }
        overlayProposition(proposition, goalproposition);
        return (typedeclarations);
      }
    }
    else if ((testValue000 == KWD_DESCRIPTIONS_ISA) ||
        ((testValue000 == KWD_DESCRIPTIONS_PREDICATE) ||
         ((testValue000 == KWD_DESCRIPTIONS_FUNCTION) ||
          (testValue000 == KWD_DESCRIPTIONS_NOT)))) {
      return (NIL);
    }
    else {
    }
  }
  return (NIL);
}

// Used to prevent infinite looping.
DEFINE_STELLA_SPECIAL(oRECURSIVEGETCOMPLEMENTARGUMENTo, NamedDescription* , NULL);

Description* getComplementOfGoalDescription(NamedDescription* self) {
  { Description* complement = ((Description*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_COMPLEMENT_DESCRIPTION, NULL)));

    if (((boolean)(complement))) {
      return (complement);
    }
    if (self == oRECURSIVEGETCOMPLEMENTARGUMENTo) {
      return (NULL);
    }
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, self->homeModule());
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      { Cons* declarations = NIL;
        Cons* variables = NIL;
        Cons* clauses = NIL;

        { PatternVariable* v = NULL;
          Vector* vector000 = self->ioVariables;
          int index000 = 0;
          int length000 = vector000->length();
          Surrogate* type = NULL;
          Cons* iter000 = self->ioVariableTypes->theConsList;
          Cons* collect000 = NULL;

          for  (; (index000 < length000) &&
                    (!(iter000 == NIL)); 
                index000 = index000 + 1,
                iter000 = iter000->rest) {
            v = ((PatternVariable*)((vector000->theArray)[index000]));
            type = ((Surrogate*)(iter000->value));
            if ((!((boolean)(type))) ||
                classDescriptionP(self)) {
              declarations = cons(v->skolemName, declarations);
            }
            else {
              declarations = cons(cons(v->skolemName, cons(internSymbolInModule(type->symbolName, ((Module*)(type->homeContext)), true), NIL)), declarations);
            }
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(v->skolemName, NIL);
                if (variables == NIL) {
                  variables = collect000;
                }
                else {
                  addConsToEndOfConsList(variables, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(v->skolemName, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        declarations = declarations->reverse();
        clauses = cons(listO(3, SYM_DESCRIPTIONS_STELLA_NOT, cons(self->descriptionName(), variables->concatenate(NIL, 0)), NIL), NIL);
        if (classDescriptionP(self)) {
          { NamedDescription* p = NULL;
            Cons* iter001 = allDirectSuperrelations(self, true);

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              p = ((NamedDescription*)(iter001->value));
              clauses = cons(cons(p->descriptionName(), cons(variables->value, NIL)), clauses);
            }
          }
        }
        { 
          BIND_STELLA_SPECIAL(oRECURSIVEGETCOMPLEMENTARGUMENTo, NamedDescription*, self);
          complement = ((Description*)(conceiveTerm(listO(3, SYM_DESCRIPTIONS_LOGIC_KAPPA, declarations, cons(cons(SYM_DESCRIPTIONS_STELLA_AND, clauses->concatenate(NIL, 0)), NIL)))));
        }
        if (!((boolean)(complement))) {
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(STANDARD_WARNING->nativeStream) << "WARNING: " << "Couldn't conceive goal complement for" << std::endl << listO(3, SYM_DESCRIPTIONS_LOGIC_KAPPA, declarations, cons(cons(SYM_DESCRIPTIONS_STELLA_AND, clauses->concatenate(NIL, 0)), NIL)) << std::endl;
            helpSignalPropositionError(STANDARD_WARNING, KWD_DESCRIPTIONS_WARNING);
          }
          return (NULL);
        }
        setDynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_COMPLEMENT_DESCRIPTION, complement, NULL);
        setDynamicSlotValue(complement->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_COMPLEMENT_DESCRIPTION, self, NULL);
        deriveDeferredContrapositiveSatelliteRules(self);
        return (complement);
      }
    }
  }
}

void collectFreeVariables(Object* self, List* collection, List* quantifiedvars, List* beenthere) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
      { Object* self000 = self;
        PatternVariable* self = ((PatternVariable*)(self000));

        if ((!quantifiedvars->memberP(self)) &&
            (!collection->memberP(self))) {
          collection->insertLast(self);
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_PROPOSITION)) {
      { Object* self001 = self;
        Proposition* self = ((Proposition*)(self001));

        if (!(beenthere->memberP(self))) {
          { Keyword* testValue001 = self->kind;

            if ((testValue001 == KWD_DESCRIPTIONS_FORALL) ||
                (testValue001 == KWD_DESCRIPTIONS_EXISTS)) {
              { PatternVariable* v = NULL;
                Vector* vector000 = ((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_IO_VARIABLES, NULL)));
                int index000 = 0;
                int length000 = vector000->length();

                for  (; index000 < length000; 
                      index000 = index000 + 1) {
                  v = ((PatternVariable*)((vector000->theArray)[index000]));
                  quantifiedvars->insert(v);
                }
              }
            }
            else {
            }
          }
          beenthere->insert(self);
          { Object* arg = NULL;
            Vector* vector001 = self->arguments;
            int index001 = 0;
            int length001 = vector001->length();

            for  (; index001 < length001; 
                  index001 = index001 + 1) {
              arg = (vector001->theArray)[index001];
              collectFreeVariables(arg, collection, quantifiedvars, beenthere);
            }
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_DESCRIPTION)) {
      { Object* self002 = self;
        Description* self = ((Description*)(self002));

        { PatternVariable* v = NULL;
          Vector* vector002 = self->ioVariables;
          int index002 = 0;
          int length002 = vector002->length();

          for  (; index002 < length002; 
                index002 = index002 + 1) {
            v = ((PatternVariable*)((vector002->theArray)[index002]));
            quantifiedvars->insert(v);
          }
        }
        { PatternVariable* v = NULL;
          Cons* iter000 = topLevelExistentialVariables(self);

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            v = ((PatternVariable*)(iter000->value));
            quantifiedvars->insert(v);
          }
        }
        collectFreeVariables(self->proposition, collection, quantifiedvars, beenthere);
      }
    }
    else {
    }
  }
}

Cons* topLevelExistentialVariables(Description* self) {
  { List* quantifiedvariables = newList();
    List* beenthere = newList();
    List* collection = newList();

    { PatternVariable* v = NULL;
      Vector* vector000 = self->ioVariables;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        v = ((PatternVariable*)((vector000->theArray)[index000]));
        quantifiedvariables->insert(v);
      }
    }
    if (((boolean)(((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_EXTERNAL_VARIABLES, NULL)))))) {
      { PatternVariable* v = NULL;
        Vector* vector001 = ((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_EXTERNAL_VARIABLES, NULL)));
        int index001 = 0;
        int length001 = vector001->length();

        for  (; index001 < length001; 
              index001 = index001 + 1) {
          v = ((PatternVariable*)((vector001->theArray)[index001]));
          quantifiedvariables->insert(v);
        }
      }
    }
    if (!((boolean)(self->proposition))) {
      return (quantifiedvariables->theConsList);
    }
    collectFreeVariables(self->proposition, collection, quantifiedvariables, beenthere);
    quantifiedvariables->free();
    beenthere->free();
    return (collection->theConsList);
  }
}

boolean topLevelExistentialVariableP(PatternVariable* variable, Description* description) {
  return ((!description->ioVariables->memberP(variable)) &&
      (description->internalVariables->memberP(variable) &&
       freeVariableP(variable, description->proposition)));
}

boolean freeVariableP(PatternVariable* variable, Proposition* proposition) {
  { Keyword* testValue000 = proposition->kind;

    if ((testValue000 == KWD_DESCRIPTIONS_FORALL) ||
        (testValue000 == KWD_DESCRIPTIONS_EXISTS)) {
      if (((Vector*)(dynamicSlotValue(proposition->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_IO_VARIABLES, NULL)))->memberP(variable)) {
        return (false);
      }
    }
    else {
    }
  }
  { boolean alwaysP000 = true;

    { Object* arg = NULL;
      Vector* vector000 = proposition->arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        if (isaP(arg, SGT_DESCRIPTIONS_LOGIC_PROPOSITION)) {
          if (!freeVariableP(variable, ((Proposition*)(arg)))) {
            alwaysP000 = false;
            break;
          }
        }
      }
    }
    { boolean value000 = alwaysP000;

      return (value000);
    }
  }
}

List* mostSpecificTypes(List* types) {
  if (!((boolean)(types->rest()))) {
    return (types);
  }
  { Cons* cursor1 = types->theConsList;
    Cons* cursor2 = NULL;
    Object* value1 = NULL;
    Object* value2 = NULL;

    while (!(cursor1 == NIL)) {
      value1 = ((Surrogate*)(cursor1->value));
      if (((boolean)(((Surrogate*)(cursor1->value))))) {
        cursor2 = cursor1->rest;
        while (!(cursor2 == NIL)) {
          value2 = cursor2->value;
          if (((boolean)(value2))) {
            if (logicalSubtypeOfP(((Surrogate*)(value1)), ((Surrogate*)(value2)))) {
              cursor2->value = NULL;
            }
            else {
              if (logicalSubtypeOfP(((Surrogate*)(value2)), ((Surrogate*)(value1)))) {
                cursor1->value = NULL;
                break;
              }
            }
          }
          cursor2 = cursor2->rest;
        }
      }
      cursor1 = cursor1->rest;
    }
  }
  types->remove(NULL);
  return (types);
}

// Used by 'infer-variable-types'.
DEFINE_STELLA_SPECIAL(oADDEDNEWTYPEpo, boolean , false);

void addVariableType(PatternVariable* variable, Surrogate* newtype, KeyValueList* table, Cons* visiblevariables) {
  if (!visiblevariables->memberP(variable)) {
    return;
  }
  { List* types = ((List*)(table->lookup(variable)));

    if (!((boolean)(types))) {
      table->insertAt(variable, list(1, newtype));
    }
    else {
      {
        { Surrogate* t = NULL;
          Cons* iter000 = types->theConsList;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            t = ((Surrogate*)(iter000->value));
            if (logicalSubtypeOfP(t, newtype)) {
              return;
            }
            if (logicalSubtypeOfP(newtype, t)) {
              types->remove(t);
              addVariableType(variable, newtype, table, visiblevariables);
              return;
            }
          }
        }
        types->insert(newtype);
      }
    }
    oADDEDNEWTYPEpo = true;
  }
}

Object* inferPredicateFromOperatorAndTypes(Object* operatoR, List* types) {
  { Surrogate* testValue000 = safePrimaryType(operatoR);

    if (subtypeOfSurrogateP(testValue000)) {
      { Object* operator000 = operatoR;
        Surrogate* operatoR = ((Surrogate*)(operator000));

        if (isaP(operatoR->surrogateValue, SGT_DESCRIPTIONS_STELLA_SLOT)) {
          { Slot* slot = ((Slot*)(operatoR->surrogateValue));

            slot = ((Slot*)(inferPredicateFromOperatorAndTypes(slot->slotName, types)));
            if (((boolean)(slot))) {
              return (slot);
            }
            else {
              return (operatoR->surrogateValue);
            }
          }
        }
        else {
          return (operatoR->surrogateValue);
        }
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* operator001 = operatoR;
        Symbol* operatoR = ((Symbol*)(operator001));

        { Surrogate* slotref = NULL;

          { Surrogate* type = NULL;
            Cons* iter000 = types->theConsList;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              type = ((Surrogate*)(iter000->value));
              if (isaP(type->surrogateValue, SGT_DESCRIPTIONS_STELLA_CLASS)) {
                slotref = lookupSlotref(type, operatoR);
                if (((boolean)(slotref))) {
                  return (slotref->surrogateValue);
                }
                if (logicalSubtypeOfLiteralP(type)) {
                  type = type->typeToWrappedType();
                  slotref = lookupSlotref(type, operatoR);
                  if (((boolean)(slotref))) {
                    return (slotref->surrogateValue);
                  }
                }
              }
            }
          }
        }
      }
    }
    else {
    }
  }
  return (NULL);
}

void inferTypesFromOneProposition(Proposition* proposition, KeyValueList* table, Cons* visiblevars) {
  if (proposition->arguments->length() == 0) {
    return;
  }
  { Vector* arguments = proposition->arguments;
    Object* firstarg = (arguments->theArray)[0];

    { Keyword* testValue000 = proposition->kind;

      if (testValue000 == KWD_DESCRIPTIONS_ISA) {
        if (isaP(firstarg, SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
          addVariableType(((PatternVariable*)(firstarg)), ((Surrogate*)(proposition->operatoR)), table, visiblevars);
        }
      }
      else if ((testValue000 == KWD_DESCRIPTIONS_PREDICATE) ||
          (testValue000 == KWD_DESCRIPTIONS_FUNCTION)) {
        { Object* predicate = NULL;

          { Surrogate* testValue001 = safePrimaryType(firstarg);

            if (subtypeOfP(testValue001, SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
              { Object* firstarg000 = firstarg;
                PatternVariable* firstarg = ((PatternVariable*)(firstarg000));

                { List* types = ((List*)(table->lookup(firstarg)));

                  if (((boolean)(types))) {
                    predicate = inferPredicateFromOperatorAndTypes(proposition->operatoR, types);
                  }
                }
              }
            }
            else if (subtypeOfSurrogateP(testValue001)) {
              { Object* firstarg001 = firstarg;
                Surrogate* firstarg = ((Surrogate*)(firstarg001));

                { Object* value = firstarg->surrogateValue;
                  List* types = newList();

                  if (((boolean)(value)) &&
                      isaP(value, SGT_DESCRIPTIONS_LOGIC_LOGIC_OBJECT)) {
                    { NamedDescription* d = NULL;
                      Cons* iter000 = allAssertedTypes(value);
                      Cons* collect000 = NULL;

                      for  (; !(iter000 == NIL); 
                            iter000 = iter000->rest) {
                        d = ((NamedDescription*)(iter000->value));
                        if (!((boolean)(collect000))) {
                          {
                            collect000 = cons(d->surrogateValueInverse, NIL);
                            if (types->theConsList == NIL) {
                              types->theConsList = collect000;
                            }
                            else {
                              addConsToEndOfConsList(types->theConsList, collect000);
                            }
                          }
                        }
                        else {
                          {
                            collect000->rest = cons(d->surrogateValueInverse, NIL);
                            collect000 = collect000->rest;
                          }
                        }
                      }
                    }
                    types = mostSpecificTypes(types);
                    predicate = inferPredicateFromOperatorAndTypes(proposition->operatoR, types);
                  }
                }
              }
            }
            else {
              { GeneralizedSymbol* operatoR = proposition->operatoR;

                if (isaP(operatoR, SGT_DESCRIPTIONS_STELLA_SURROGATE) &&
                    isaP(((Surrogate*)(operatoR))->surrogateValue, SGT_DESCRIPTIONS_STELLA_SLOT)) {
                  predicate = ((Slot*)(((Surrogate*)(operatoR))->surrogateValue));
                }
              }
            }
          }
          if (((boolean)(predicate))) {
            { Surrogate* testValue002 = safePrimaryType(predicate);

              if (subtypeOfP(testValue002, SGT_DESCRIPTIONS_LOGIC_NAMED_DESCRIPTION)) {
                { Object* predicate000 = predicate;
                  NamedDescription* predicate = ((NamedDescription*)(predicate000));

                  if (((boolean)(predicate->ioVariableTypes))) {
                    { Object* arg = NULL;
                      Vector* vector000 = arguments;
                      int index000 = 0;
                      int length000 = vector000->length();
                      Surrogate* type = NULL;
                      Cons* iter001 = predicate->ioVariableTypes->theConsList;

                      for  (; (index000 < length000) &&
                                (!(iter001 == NIL)); 
                            index000 = index000 + 1,
                            iter001 = iter001->rest) {
                        arg = (vector000->theArray)[index000];
                        type = ((Surrogate*)(iter001->value));
                        if (isaP(arg, SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
                          addVariableType(((PatternVariable*)(arg)), type, table, visiblevars);
                        }
                      }
                    }
                  }
                  else {
                  }
                }
              }
              else if (subtypeOfP(testValue002, SGT_DESCRIPTIONS_STELLA_SLOT)) {
                { Object* predicate001 = predicate;
                  Slot* predicate = ((Slot*)(predicate001));

                  { Object* arg = NULL;
                    Vector* vector001 = arguments;
                    int index001 = 0;
                    int length001 = vector001->length();
                    Surrogate* columntype = NULL;
                    Cons* iter002 = slotColumnTypes(predicate, arguments->length());

                    for  (; (index001 < length001) &&
                              (!(iter002 == NIL)); 
                          index001 = index001 + 1,
                          iter002 = iter002->rest) {
                      arg = (vector001->theArray)[index001];
                      columntype = ((Surrogate*)(iter002->value));
                      if (isaP(arg, SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
                        addVariableType(((PatternVariable*)(arg)), columntype, table, visiblevars);
                      }
                    }
                  }
                }
              }
              else if (subtypeOfP(testValue002, SGT_DESCRIPTIONS_LOGIC_LOGIC_OBJECT)) {
                { Object* predicate002 = predicate;
                  LogicObject* predicate = ((LogicObject*)(predicate002));

                }
              }
              else {
                { OutputStringStream* stream000 = newOutputStringStream();

                  *(stream000->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
                  throw *newStellaException(stream000->theStringReader());
                }
              }
            }
          }
        }
      }
      else if (testValue000 == KWD_DESCRIPTIONS_EQUIVALENT) {
        { Object* secondarg = (arguments->theArray)[1];

          if (isaP(firstarg, SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
            if (isaP(secondarg, SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
              { Object* t = NULL;
                Cons* iter003 = mapNullToNilList(((List*)(table->lookup(((PatternVariable*)(secondarg))))))->theConsList;

                for (; !(iter003 == NIL); iter003 = iter003->rest) {
                  t = iter003->value;
                  addVariableType(((PatternVariable*)(firstarg)), ((Surrogate*)(t)), table, visiblevars);
                }
              }
            }
            else {
              addVariableType(((PatternVariable*)(firstarg)), logicalType(secondarg), table, visiblevars);
            }
          }
          if (isaP(secondarg, SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
            if (isaP(firstarg, SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
              { Object* t = NULL;
                Cons* iter004 = mapNullToNilList(((List*)(table->lookup(((PatternVariable*)(firstarg))))))->theConsList;

                for (; !(iter004 == NIL); iter004 = iter004->rest) {
                  t = iter004->value;
                  addVariableType(((PatternVariable*)(secondarg)), ((Surrogate*)(t)), table, visiblevars);
                }
              }
            }
            else {
              addVariableType(((PatternVariable*)(secondarg)), logicalType(firstarg), table, visiblevars);
            }
          }
        }
      }
      else {
      }
    }
  }
}

void inferTypesFromPropositions(Proposition* proposition, KeyValueList* table, Cons* visiblevars) {
  { Vector* arguments = proposition->arguments;

    { Keyword* testValue000 = proposition->kind;

      if (testValue000 == KWD_DESCRIPTIONS_AND) {
        { Object* arg = NULL;
          Vector* vector000 = arguments;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            arg = (vector000->theArray)[index000];
            inferTypesFromPropositions(((Proposition*)(arg)), table, visiblevars);
          }
        }
      }
      else if (testValue000 == KWD_DESCRIPTIONS_OR) {
        { Object* arg = NULL;
          Vector* vector001 = arguments;
          int index001 = 0;
          int length001 = vector001->length();

          for  (; index001 < length001; 
                index001 = index001 + 1) {
            arg = (vector001->theArray)[index001];
            inferTypesFromPropositions(((Proposition*)(arg)), table, NIL);
          }
        }
      }
      else if ((testValue000 == KWD_DESCRIPTIONS_ISA) ||
          ((testValue000 == KWD_DESCRIPTIONS_PREDICATE) ||
           ((testValue000 == KWD_DESCRIPTIONS_FUNCTION) ||
            (testValue000 == KWD_DESCRIPTIONS_EQUIVALENT)))) {
        inferTypesFromOneProposition(proposition, table, visiblevars);
      }
      else if (testValue000 == KWD_DESCRIPTIONS_FORALL) {
        visiblevars = NIL;
        { PatternVariable* v = NULL;
          Vector* vector002 = ((Vector*)(dynamicSlotValue(proposition->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_IO_VARIABLES, NULL)));
          int index002 = 0;
          int length002 = vector002->length();

          for  (; index002 < length002; 
                index002 = index002 + 1) {
            v = ((PatternVariable*)((vector002->theArray)[index002]));
            visiblevars = cons(v, visiblevars);
          }
        }
        inferTypesFromPropositions(((Proposition*)((arguments->theArray)[0])), table, visiblevars);
        inferTypesFromPropositions(((Proposition*)((arguments->theArray)[1])), table, visiblevars);
      }
      else if (testValue000 == KWD_DESCRIPTIONS_EXISTS) {
        { PatternVariable* v = NULL;
          Vector* vector003 = ((Vector*)(dynamicSlotValue(proposition->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_IO_VARIABLES, NULL)));
          int index003 = 0;
          int length003 = vector003->length();

          for  (; index003 < length003; 
                index003 = index003 + 1) {
            v = ((PatternVariable*)((vector003->theArray)[index003]));
            visiblevars = cons(v, visiblevars);
          }
        }
        inferTypesFromPropositions(((Proposition*)((arguments->theArray)[0])), table, visiblevars);
      }
      else {
      }
    }
  }
}

KeyValueList* inferVariableTypesInProposition(Proposition* proposition, Cons* visiblevariables) {
  { KeyValueList* variabletypestable = newKeyValueList();

    { 
      BIND_STELLA_SPECIAL(oADDEDNEWTYPEpo, boolean, false);
      for (;;) {
        oADDEDNEWTYPEpo = false;
        inferTypesFromPropositions(proposition, variabletypestable, visiblevariables);
        if (!oADDEDNEWTYPEpo) {
          return (variabletypestable);
        }
      }
    }
  }
}

KeyValueList* inferVariableTypesInDescription(Description* description) {
  { Cons* visiblevariables = NIL;

    { PatternVariable* v = NULL;
      Vector* vector000 = description->ioVariables;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        v = ((PatternVariable*)((vector000->theArray)[index000]));
        visiblevariables = cons(v, visiblevariables);
      }
    }
    { PatternVariable* v = NULL;
      Cons* iter000 = topLevelExistentialVariables(description);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        v = ((PatternVariable*)(iter000->value));
        visiblevariables = cons(v, visiblevariables);
      }
    }
    return (inferVariableTypesInProposition(description->proposition, visiblevariables));
  }
}

Cons* collectUnresolvedSlotReferences(Proposition* self) {
  { Cons* unresolvedslotreferences = NIL;

    if (getQuotedTree("((:PREDICATE :FUNCTION) \"/LOGIC\")", "/LOGIC")->memberP(self->kind) &&
        isaP(self->operatoR, SGT_DESCRIPTIONS_STELLA_SYMBOL)) {
      unresolvedslotreferences = cons(self, unresolvedslotreferences);
    }
    { Object* arg = NULL;
      Vector* vector000 = self->arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        if (isaP(arg, SGT_DESCRIPTIONS_LOGIC_PROPOSITION)) {
          { Proposition* u = NULL;
            Cons* iter000 = collectUnresolvedSlotReferences(((Proposition*)(arg)));

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              u = ((Proposition*)(iter000->value));
              unresolvedslotreferences = cons(u, unresolvedslotreferences);
            }
          }
        }
      }
    }
    return (unresolvedslotreferences);
  }
}

boolean resolveOneSlotReferenceP(Proposition* proposition, KeyValueList* variabletypestable) {
  { Object* firstargument = (proposition->arguments->theArray)[0];
    Object* predicate = NULL;

    { Surrogate* testValue000 = safePrimaryType(firstargument);

      if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE)) {
        { Object* firstargument000 = firstargument;
          PatternVariable* firstargument = ((PatternVariable*)(firstargument000));

          { List* types = ((List*)(variabletypestable->lookup(firstargument)));

            if (((boolean)(types))) {
              predicate = inferPredicateFromOperatorAndTypes(proposition->operatoR, ((List*)(variabletypestable->lookup(firstargument))));
            }
          }
        }
      }
      else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_LOGIC_OBJECT)) {
        { Object* firstargument001 = firstargument;
          LogicObject* firstargument = ((LogicObject*)(firstargument001));

          { Surrogate* roottype = safeLogicalType(firstargument);

            if (((boolean)(roottype))) {
              predicate = inferPredicateFromOperatorAndTypes(proposition->operatoR, list(1, roottype));
            }
          }
        }
      }
      else {
      }
    }
    if (((boolean)(predicate))) {
      if (subtypeOfP(safePrimaryType(predicate), SGT_DESCRIPTIONS_STELLA_SLOT)) {
        { Object* predicate000 = predicate;
          Slot* predicate = ((Slot*)(predicate000));

          { Surrogate* returntype = unwrapWrappedType(predicate->slotBaseType);

            if (!booleanTypeP(returntype)) {
              proposition->kind = KWD_DESCRIPTIONS_FUNCTION;
              if (variableP((proposition->arguments->theArray)[(proposition->arguments->length() - 1)])) {
                { PatternVariable* lastargument = ((PatternVariable*)((proposition->arguments->theArray)[(proposition->arguments->length() - 1)]));

                  updateSkolemType(lastargument, returntype);
                }
              }
            }
            proposition->operatoR = mostGeneralEquivalentSlotref(predicate->slotSlotref);
            evaluateNewProposition(proposition);
            return (true);
          }
        }
      }
      else {
      }
    }
    return (false);
  }
}

void resolveUnresolvedSlotReferences(Object* formula) {
  { Proposition* proposition = NULL;
    Cons* unresolvedpropositions = NULL;
    KeyValueList* variabletypestable = NULL;
    Cons* unresolvablepropositions = NIL;

    { Surrogate* testValue000 = safePrimaryType(formula);

      if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_DESCRIPTION)) {
        { Object* formula000 = formula;
          Description* formula = ((Description*)(formula000));

          proposition = formula->proposition;
        }
      }
      else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_PROPOSITION)) {
        { Object* formula001 = formula;
          Proposition* formula = ((Proposition*)(formula001));

          proposition = formula;
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    unresolvedpropositions = collectUnresolvedSlotReferences(proposition);
    if (unresolvedpropositions == NIL) {
      return;
    }
    { Surrogate* testValue001 = safePrimaryType(formula);

      if (subtypeOfP(testValue001, SGT_DESCRIPTIONS_LOGIC_DESCRIPTION)) {
        { Object* formula002 = formula;
          Description* formula = ((Description*)(formula002));

          variabletypestable = inferVariableTypesInDescription(formula);
        }
      }
      else if (subtypeOfP(testValue001, SGT_DESCRIPTIONS_LOGIC_PROPOSITION)) {
        { Object* formula003 = formula;
          Proposition* formula = ((Proposition*)(formula003));

          variabletypestable = inferVariableTypesInProposition(formula, NIL);
        }
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
          throw *newStellaException(stream001->theStringReader());
        }
      }
    }
    { Proposition* prop = NULL;
      Cons* iter000 = unresolvedpropositions;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        prop = ((Proposition*)(iter000->value));
        if (symbolP(prop->operatoR) &&
            (!resolveOneSlotReferenceP(prop, variabletypestable))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(prop, NIL);
              if (unresolvablepropositions == NIL) {
                unresolvablepropositions = collect000;
              }
              else {
                addConsToEndOfConsList(unresolvablepropositions, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(prop, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    if (!(unresolvablepropositions == NIL)) {
      { Proposition* p = NULL;
        Cons* iter001 = unresolvablepropositions;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          p = ((Proposition*)(iter001->value));
          complainAboutUndeclaredReference(p);
          createDummyRelation(p);
        }
      }
    }
  }
}

void createDummyRelation(Proposition* waywardproposition) {
  { List* fakevariabletypes = newList();
    Symbol* symbolref = ((Symbol*)(waywardproposition->operatoR));
    Surrogate* relationref = symbolToSurrogate(symbolref);
    NamedDescription* description = NULL;

    { IntegerIntervalIterator* i = interval(1, waywardproposition->arguments->length());

      for (; i->nextP(); ) {
        fakevariabletypes->push(SGT_DESCRIPTIONS_STELLA_THING);
      }
    }
    description = createPrimitiveDescription(NIL_LIST, fakevariabletypes, false, waywardproposition->kind == KWD_DESCRIPTIONS_ISA, waywardproposition->kind == KWD_DESCRIPTIONS_FUNCTION, ((Module*)(relationref->homeContext)));
    waywardproposition->operatoR = relationref;
    bindLogicObjectToSurrogate(symbolref, description);
    setDynamicSlotValue(description->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_UNDECLAREDp, TRUE_WRAPPER, FALSE_WRAPPER);
  }
}

boolean definedRelationP(NamedDescription* self) {
  return ((!((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_UNDECLAREDp, FALSE_WRAPPER)))->wrapperValue) &&
      ((stringifiedSource(self) != NULL) ||
       ((boolean)(self->nativeRelation()))));
}

Cons* listUndefinedRelations(Cons* options) {
  // Return a list of as yet undefined concepts and relations in the module defined
  // by the :module option (which defaults to the current module).  These relations were
  // defined by the system, since they were referenced but have not yet been defined by
  // the user.  If `:local?' is specified as TRUE only look in the specified module but
  // not any modules it inherits.  For backwards compatibility, this command also supports
  // the old <module> <local?> arguments specified without keywords.
  { Cons* optionslist = options;
    PropertyList* theoptions = parseOptions((keywordP(optionslist->value) ? optionslist : consList(4, KWD_DESCRIPTIONS_MODULE, optionslist->value, KWD_DESCRIPTIONS_LOCALp, optionslist->rest->value)), listO(5, KWD_DESCRIPTIONS_MODULE, SGT_DESCRIPTIONS_STELLA_MODULE, KWD_DESCRIPTIONS_LOCALp, SGT_DESCRIPTIONS_STELLA_BOOLEAN, NIL), true, false);
    Module* themodule = ((Module*)(theoptions->lookupWithDefault(KWD_DESCRIPTIONS_MODULE, oMODULEo)));
    boolean localP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_DESCRIPTIONS_LOCALp, FALSE_WRAPPER))));

    return (callListUndefinedRelations(themodule, localP));
  }
}

Cons* listUndefinedRelationsEvaluatorWrapper(Cons* arguments) {
  return (listUndefinedRelations(arguments));
}

Cons* callListUndefinedRelations(Module* module, boolean localP) {
  // Callable version of `list-undefined-relations' (which see).
  { TruthValue* dummy1;

    { Cons* undefined = NIL;

      finalizeObjects();
      { Object* term = NULL;
        Iterator* iter000 = allNamedTerms(module, localP);

        for (; iter000->nextP(); ) {
          term = iter000->value;
          { Surrogate* testValue000 = safePrimaryType(term);

            if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_NAMED_DESCRIPTION)) {
              { Object* term000 = term;
                NamedDescription* term = ((NamedDescription*)(term000));

                if (!definedRelationP(term)) {
                  undefined = cons(term, undefined);
                }
              }
            }
            else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_LOGIC_OBJECT)) {
              { Object* term001 = term;
                LogicObject* term = ((LogicObject*)(term001));

                { 
                  BIND_STELLA_SPECIAL(oMODULEo, Module*, ((!((boolean)(module))) ? term->homeModule() : module));
                  BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
                  if (applyCachedAsk(cons(SYM_DESCRIPTIONS_LOGIC_pX, NIL), listO(3, SYM_DESCRIPTIONS_PL_KERNEL_KB_RELATION, SYM_DESCRIPTIONS_LOGIC_pX, NIL), consList(1, term), consList(0), SYM_DESCRIPTIONS_LOGIC_F_CALL_LIST_UNDEFINED_RELATIONS_QUERY_000, dummy1)) {
                    undefined = cons(term, undefined);
                  }
                }
              }
            }
            else {
            }
          }
        }
      }
      return (undefined);
    }
  }
}

void complainAboutUndeclaredReference(Proposition* waywardproposition) {
  if (((BooleanWrapper*)(dynamicSlotValue(waywardproposition->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "ERROR: " << "Undeclared predicate or function reference: " << "`" << waywardproposition->operatoR << "'" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_DESCRIPTIONS_ERROR);
      }
      throw *newPropositionError(stream000->theStringReader());
    }
  }
  else {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      *(STANDARD_WARNING->nativeStream) << "WARNING: " << "Undeclared predicate or function reference: " << waywardproposition->operatoR << std::endl;
      helpSignalPropositionError(STANDARD_WARNING, KWD_DESCRIPTIONS_WARNING);
    }
  }
}

boolean allNamedDescriptionsNextP(AllPurposeIterator* self) {
  { int cursor = self->iteratorInteger;
    Surrogate* surrogate = NULL;
    Object* surrogatevalue = NULL;
    NamedDescription* description = NULL;

    while (cursor < self->iteratorSecondInteger) {
      surrogate = ((Surrogate*)((oSURROGATE_ARRAYo->theArray)[cursor]));
      if (((boolean)(surrogate))) {
        surrogatevalue = surrogate->surrogateValue;
        if (((boolean)(surrogatevalue))) {
          if (!(selectedMetaObjectP(self, surrogatevalue->homeModule()))) {
            surrogatevalue = NULL;
          }
        }
      }
      description = NULL;
      if (((boolean)(surrogatevalue))) {
        { Surrogate* testValue000 = safePrimaryType(surrogatevalue);

          if (subtypeOfClassP(testValue000)) {
            { Object* surrogatevalue000 = surrogatevalue;
              Class* surrogatevalue = ((Class*)(surrogatevalue000));

              if (((Class*)(surrogatevalue))->classType == surrogate) {
                description = ((NamedDescription*)(dynamicSlotValue(surrogatevalue->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_DESCRIPTION, NULL)));
              }
            }
          }
          else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_STELLA_RELATION)) {
            { Object* surrogatevalue001 = surrogatevalue;
              Relation* surrogatevalue = ((Relation*)(surrogatevalue001));

              description = ((NamedDescription*)(dynamicSlotValue(surrogatevalue->dynamicSlots, SYM_DESCRIPTIONS_LOGIC_DESCRIPTION, NULL)));
            }
          }
          else if (subtypeOfP(testValue000, SGT_DESCRIPTIONS_LOGIC_NAMED_DESCRIPTION)) {
            { Object* surrogatevalue002 = surrogatevalue;
              NamedDescription* surrogatevalue = ((NamedDescription*)(surrogatevalue002));

              description = surrogatevalue;
            }
          }
          else {
          }
        }
      }
      if (((boolean)(description))) {
        self->value = description;
        self->iteratorInteger = cursor + 1;
        return (true);
      }
      cursor = cursor + 1;
    }
    return (false);
  }
}

Iterator* allNamedDescriptions(Module* module, boolean localP) {
  // Iterate over all named descriptions visible from 'module'.
  // If 'local?', return only named descriptions interned in 'module'.
  // If 'module' is null, return all named descriptions interned everywhere.
  return (allocateAllMetaObjectsIterator(oSURROGATE_ARRAYo->topSymbolOffset + 1, ((cpp_function_code)(&allNamedDescriptionsNextP)), module, localP));
}

void helpStartupDescriptions1() {
  {
    SGT_DESCRIPTIONS_STELLA_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("SLOT", getStellaModule("/STELLA", true), 1)));
    SGT_DESCRIPTIONS_STELLA_METHOD_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-SLOT", getStellaModule("/STELLA", true), 1)));
    SYM_DESCRIPTIONS_STELLA_ANY_VALUE = ((Symbol*)(internRigidSymbolWrtModule("ANY-VALUE", getStellaModule("/STELLA", true), 0)));
    KWD_DESCRIPTIONS_EXTENSIONAL_ASSERTION = ((Keyword*)(internRigidSymbolWrtModule("EXTENSIONAL-ASSERTION", NULL, 2)));
    SGT_DESCRIPTIONS_PL_KERNEL_KB_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("RELATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_DESCRIPTIONS_PL_KERNEL_KB_POLYMORPHIC = ((Surrogate*)(internRigidSymbolWrtModule("POLYMORPHIC", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_DESCRIPTIONS_LOGIC_pX1 = ((Symbol*)(internRigidSymbolWrtModule("?X1", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX2 = ((Symbol*)(internRigidSymbolWrtModule("?X2", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX3 = ((Symbol*)(internRigidSymbolWrtModule("?X3", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX4 = ((Symbol*)(internRigidSymbolWrtModule("?X4", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX5 = ((Symbol*)(internRigidSymbolWrtModule("?X5", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX6 = ((Symbol*)(internRigidSymbolWrtModule("?X6", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX7 = ((Symbol*)(internRigidSymbolWrtModule("?X7", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX8 = ((Symbol*)(internRigidSymbolWrtModule("?X8", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX9 = ((Symbol*)(internRigidSymbolWrtModule("?X9", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX10 = ((Symbol*)(internRigidSymbolWrtModule("?X10", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX11 = ((Symbol*)(internRigidSymbolWrtModule("?X11", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX12 = ((Symbol*)(internRigidSymbolWrtModule("?X12", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX13 = ((Symbol*)(internRigidSymbolWrtModule("?X13", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX14 = ((Symbol*)(internRigidSymbolWrtModule("?X14", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX15 = ((Symbol*)(internRigidSymbolWrtModule("?X15", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX16 = ((Symbol*)(internRigidSymbolWrtModule("?X16", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX17 = ((Symbol*)(internRigidSymbolWrtModule("?X17", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX18 = ((Symbol*)(internRigidSymbolWrtModule("?X18", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX19 = ((Symbol*)(internRigidSymbolWrtModule("?X19", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX20 = ((Symbol*)(internRigidSymbolWrtModule("?X20", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX21 = ((Symbol*)(internRigidSymbolWrtModule("?X21", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX22 = ((Symbol*)(internRigidSymbolWrtModule("?X22", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX23 = ((Symbol*)(internRigidSymbolWrtModule("?X23", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX24 = ((Symbol*)(internRigidSymbolWrtModule("?X24", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX25 = ((Symbol*)(internRigidSymbolWrtModule("?X25", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX26 = ((Symbol*)(internRigidSymbolWrtModule("?X26", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX27 = ((Symbol*)(internRigidSymbolWrtModule("?X27", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX28 = ((Symbol*)(internRigidSymbolWrtModule("?X28", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX29 = ((Symbol*)(internRigidSymbolWrtModule("?X29", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX30 = ((Symbol*)(internRigidSymbolWrtModule("?X30", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX31 = ((Symbol*)(internRigidSymbolWrtModule("?X31", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX32 = ((Symbol*)(internRigidSymbolWrtModule("?X32", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX33 = ((Symbol*)(internRigidSymbolWrtModule("?X33", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX34 = ((Symbol*)(internRigidSymbolWrtModule("?X34", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX35 = ((Symbol*)(internRigidSymbolWrtModule("?X35", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX36 = ((Symbol*)(internRigidSymbolWrtModule("?X36", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX37 = ((Symbol*)(internRigidSymbolWrtModule("?X37", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX38 = ((Symbol*)(internRigidSymbolWrtModule("?X38", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX39 = ((Symbol*)(internRigidSymbolWrtModule("?X39", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX40 = ((Symbol*)(internRigidSymbolWrtModule("?X40", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX41 = ((Symbol*)(internRigidSymbolWrtModule("?X41", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX42 = ((Symbol*)(internRigidSymbolWrtModule("?X42", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX43 = ((Symbol*)(internRigidSymbolWrtModule("?X43", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX44 = ((Symbol*)(internRigidSymbolWrtModule("?X44", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX45 = ((Symbol*)(internRigidSymbolWrtModule("?X45", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX46 = ((Symbol*)(internRigidSymbolWrtModule("?X46", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX47 = ((Symbol*)(internRigidSymbolWrtModule("?X47", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX48 = ((Symbol*)(internRigidSymbolWrtModule("?X48", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX49 = ((Symbol*)(internRigidSymbolWrtModule("?X49", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX50 = ((Symbol*)(internRigidSymbolWrtModule("?X50", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX51 = ((Symbol*)(internRigidSymbolWrtModule("?X51", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX52 = ((Symbol*)(internRigidSymbolWrtModule("?X52", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX53 = ((Symbol*)(internRigidSymbolWrtModule("?X53", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX54 = ((Symbol*)(internRigidSymbolWrtModule("?X54", NULL, 0)));
  }
}

void helpStartupDescriptions2() {
  {
    SYM_DESCRIPTIONS_LOGIC_pX55 = ((Symbol*)(internRigidSymbolWrtModule("?X55", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX56 = ((Symbol*)(internRigidSymbolWrtModule("?X56", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX57 = ((Symbol*)(internRigidSymbolWrtModule("?X57", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX58 = ((Symbol*)(internRigidSymbolWrtModule("?X58", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX59 = ((Symbol*)(internRigidSymbolWrtModule("?X59", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX60 = ((Symbol*)(internRigidSymbolWrtModule("?X60", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX61 = ((Symbol*)(internRigidSymbolWrtModule("?X61", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX62 = ((Symbol*)(internRigidSymbolWrtModule("?X62", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX63 = ((Symbol*)(internRigidSymbolWrtModule("?X63", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX64 = ((Symbol*)(internRigidSymbolWrtModule("?X64", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX65 = ((Symbol*)(internRigidSymbolWrtModule("?X65", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX66 = ((Symbol*)(internRigidSymbolWrtModule("?X66", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX67 = ((Symbol*)(internRigidSymbolWrtModule("?X67", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX68 = ((Symbol*)(internRigidSymbolWrtModule("?X68", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX69 = ((Symbol*)(internRigidSymbolWrtModule("?X69", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX70 = ((Symbol*)(internRigidSymbolWrtModule("?X70", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX71 = ((Symbol*)(internRigidSymbolWrtModule("?X71", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX72 = ((Symbol*)(internRigidSymbolWrtModule("?X72", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX73 = ((Symbol*)(internRigidSymbolWrtModule("?X73", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX74 = ((Symbol*)(internRigidSymbolWrtModule("?X74", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX75 = ((Symbol*)(internRigidSymbolWrtModule("?X75", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX76 = ((Symbol*)(internRigidSymbolWrtModule("?X76", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX77 = ((Symbol*)(internRigidSymbolWrtModule("?X77", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX78 = ((Symbol*)(internRigidSymbolWrtModule("?X78", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX79 = ((Symbol*)(internRigidSymbolWrtModule("?X79", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX80 = ((Symbol*)(internRigidSymbolWrtModule("?X80", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX81 = ((Symbol*)(internRigidSymbolWrtModule("?X81", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX82 = ((Symbol*)(internRigidSymbolWrtModule("?X82", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX83 = ((Symbol*)(internRigidSymbolWrtModule("?X83", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX84 = ((Symbol*)(internRigidSymbolWrtModule("?X84", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX85 = ((Symbol*)(internRigidSymbolWrtModule("?X85", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX86 = ((Symbol*)(internRigidSymbolWrtModule("?X86", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX87 = ((Symbol*)(internRigidSymbolWrtModule("?X87", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX88 = ((Symbol*)(internRigidSymbolWrtModule("?X88", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX89 = ((Symbol*)(internRigidSymbolWrtModule("?X89", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX90 = ((Symbol*)(internRigidSymbolWrtModule("?X90", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX91 = ((Symbol*)(internRigidSymbolWrtModule("?X91", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX92 = ((Symbol*)(internRigidSymbolWrtModule("?X92", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX93 = ((Symbol*)(internRigidSymbolWrtModule("?X93", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX94 = ((Symbol*)(internRigidSymbolWrtModule("?X94", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX95 = ((Symbol*)(internRigidSymbolWrtModule("?X95", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX96 = ((Symbol*)(internRigidSymbolWrtModule("?X96", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX97 = ((Symbol*)(internRigidSymbolWrtModule("?X97", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX98 = ((Symbol*)(internRigidSymbolWrtModule("?X98", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX99 = ((Symbol*)(internRigidSymbolWrtModule("?X99", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_pX100 = ((Symbol*)(internRigidSymbolWrtModule("?X100", NULL, 0)));
    SGT_DESCRIPTIONS_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
    SYM_DESCRIPTIONS_STELLA_ISA = ((Symbol*)(internRigidSymbolWrtModule("ISA", getStellaModule("/STELLA", true), 0)));
    SYM_DESCRIPTIONS_LOGIC_KAPPA = ((Symbol*)(internRigidSymbolWrtModule("KAPPA", NULL, 0)));
    KWD_DESCRIPTIONS_KIF = ((Keyword*)(internRigidSymbolWrtModule("KIF", NULL, 2)));
    KWD_DESCRIPTIONS_DESCRIPTION = ((Keyword*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 2)));
    SGT_DESCRIPTIONS_LOGIC_UNFINALIZED = ((Surrogate*)(internRigidSymbolWrtModule("UNFINALIZED", NULL, 1)));
    SGT_DESCRIPTIONS_PL_KERNEL_KB_CONCEPT = ((Surrogate*)(internRigidSymbolWrtModule("CONCEPT", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_DESCRIPTIONS_PL_KERNEL_KB_FUNCTION = ((Surrogate*)(internRigidSymbolWrtModule("FUNCTION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_DESCRIPTIONS_PL_KERNEL_KB_VARIABLE_ARITY = ((Surrogate*)(internRigidSymbolWrtModule("VARIABLE-ARITY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_DESCRIPTIONS_LOGIC_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 0)));
    SGT_DESCRIPTIONS_STELLA_CLASS = ((Surrogate*)(internRigidSymbolWrtModule("CLASS", getStellaModule("/STELLA", true), 1)));
    KWD_DESCRIPTIONS_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    SGT_DESCRIPTIONS_STELLA_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("RELATION", getStellaModule("/STELLA", true), 1)));
    SYM_DESCRIPTIONS_LOGIC_OBJECT_STORE = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-STORE", NULL, 0)));
  }
}

void helpStartupDescriptions3() {
  {
    SGT_DESCRIPTIONS_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
    SGT_DESCRIPTIONS_STELLA_LITERAL = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL", getStellaModule("/STELLA", true), 1)));
    SGT_DESCRIPTIONS_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    KWD_DESCRIPTIONS_WARNING = ((Keyword*)(internRigidSymbolWrtModule("WARNING", NULL, 2)));
    SGT_DESCRIPTIONS_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    KWD_DESCRIPTIONS_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    SYM_DESCRIPTIONS_LOGIC_VARIABLE_TYPEp = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-TYPE?", NULL, 0)));
    SYM_DESCRIPTIONS_STELLA_EXISTS = ((Symbol*)(internRigidSymbolWrtModule("EXISTS", getStellaModule("/STELLA", true), 0)));
    KWD_DESCRIPTIONS_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    KWD_DESCRIPTIONS_OR = ((Keyword*)(internRigidSymbolWrtModule("OR", NULL, 2)));
    KWD_DESCRIPTIONS_EQUIVALENT = ((Keyword*)(internRigidSymbolWrtModule("EQUIVALENT", NULL, 2)));
    KWD_DESCRIPTIONS_FORALL = ((Keyword*)(internRigidSymbolWrtModule("FORALL", NULL, 2)));
    KWD_DESCRIPTIONS_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("EXISTS", NULL, 2)));
    SYM_DESCRIPTIONS_LOGIC_IO_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("IO-VARIABLES", NULL, 0)));
    SGT_DESCRIPTIONS_PL_KERNEL_KB_HOLDS = ((Surrogate*)(internRigidSymbolWrtModule("HOLDS", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_DESCRIPTIONS_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SGT_DESCRIPTIONS_STELLA_SET = ((Surrogate*)(internRigidSymbolWrtModule("SET", getStellaModule("/STELLA", true), 1)));
    SGT_DESCRIPTIONS_STELLA_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", getStellaModule("/STELLA", true), 1)));
    SGT_DESCRIPTIONS_STELLA_SURROGATE = ((Surrogate*)(internRigidSymbolWrtModule("SURROGATE", getStellaModule("/STELLA", true), 1)));
    SGT_DESCRIPTIONS_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
    KWD_DESCRIPTIONS_NOT = ((Keyword*)(internRigidSymbolWrtModule("NOT", NULL, 2)));
    SYM_DESCRIPTIONS_LOGIC_EXTERNAL_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("EXTERNAL-VARIABLES", NULL, 0)));
    KWD_DESCRIPTIONS_PREDICATE = ((Keyword*)(internRigidSymbolWrtModule("PREDICATE", NULL, 2)));
    KWD_DESCRIPTIONS_IMPLIES = ((Keyword*)(internRigidSymbolWrtModule("IMPLIES", NULL, 2)));
    SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", NULL, 1)));
    SYM_DESCRIPTIONS_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", getStellaModule("/STELLA", true), 0)));
    SGT_DESCRIPTIONS_STELLA_PROPOSITIONdIF = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION.IF", getStellaModule("/STELLA", true), 1)));
    SYM_DESCRIPTIONS_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    SGT_DESCRIPTIONS_STELLA_CS_VALUE = ((Surrogate*)(internRigidSymbolWrtModule("CS-VALUE", getStellaModule("/STELLA", true), 1)));
    KWD_DESCRIPTIONS_TAIL = ((Keyword*)(internRigidSymbolWrtModule("TAIL", NULL, 2)));
    SYM_DESCRIPTIONS_LOGIC_THE_ONLY = ((Symbol*)(internRigidSymbolWrtModule("THE-ONLY", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_IOTAp = ((Symbol*)(internRigidSymbolWrtModule("IOTA?", NULL, 0)));
    KWD_DESCRIPTIONS_TOP_LEVEL = ((Keyword*)(internRigidSymbolWrtModule("TOP-LEVEL", NULL, 2)));
    SYM_DESCRIPTIONS_LOGIC_COMPLEMENT_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("COMPLEMENT-DESCRIPTION", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_VARIABLE_TYPE_TABLE = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-TYPE-TABLE", NULL, 0)));
    SGT_DESCRIPTIONS_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
    SGT_DESCRIPTIONS_STELLA_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("SYMBOL", getStellaModule("/STELLA", true), 1)));
    SYM_DESCRIPTIONS_LOGIC_UNDECLAREDp = ((Symbol*)(internRigidSymbolWrtModule("UNDECLARED?", NULL, 0)));
    KWD_DESCRIPTIONS_MODULE = ((Keyword*)(internRigidSymbolWrtModule("MODULE", NULL, 2)));
    KWD_DESCRIPTIONS_LOCALp = ((Keyword*)(internRigidSymbolWrtModule("LOCAL?", NULL, 2)));
    SGT_DESCRIPTIONS_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 1)));
    SGT_DESCRIPTIONS_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", getStellaModule("/STELLA", true), 1)));
    SYM_DESCRIPTIONS_LOGIC_pX = ((Symbol*)(internRigidSymbolWrtModule("?X", NULL, 0)));
    SYM_DESCRIPTIONS_PL_KERNEL_KB_RELATION = ((Symbol*)(internRigidSymbolWrtModule("RELATION", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_DESCRIPTIONS_LOGIC_F_CALL_LIST_UNDEFINED_RELATIONS_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("F-CALL-LIST-UNDEFINED-RELATIONS-QUERY-000", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_DESCRIPTIVEp = ((Symbol*)(internRigidSymbolWrtModule("DESCRIPTIVE?", NULL, 0)));
    SYM_DESCRIPTIONS_LOGIC_STARTUP_DESCRIPTIONS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-DESCRIPTIONS", NULL, 0)));
    SYM_DESCRIPTIONS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupDescriptions4() {
  {
    defineExternalSlotFromStringifiedSource("(DEFSLOT RELATION DESCRIPTION :TYPE NAMED-DESCRIPTION :DOCUMENTATION \"Maps a relation (class or slot or table) to a\nprimitive description.\" :ALLOCATION :DYNAMIC)");
    defineFunctionObject("DIRECT-SUPERRELATIONS", "(DEFUN (DIRECT-SUPERRELATIONS (ITERATOR OF (LIKE SELF))) ((SELF RELATION)) :DOCUMENTATION \"Return direct super classes/slots of 'self'.\")", ((cpp_function_code)(&directSuperrelations)), NULL);
    defineFunctionObject("SLOT-COLUMN-TYPES", "(DEFUN (SLOT-COLUMN-TYPES (CONS OF TYPE)) ((SELF SLOT) (COUNT INTEGER)))", ((cpp_function_code)(&slotColumnTypes)), NULL);
    defineFunctionObject("CREATE-DESCRIPTION", "(DEFUN (CREATE-DESCRIPTION DESCRIPTION) ((ARITY INTEGER) (NAMED? BOOLEAN)) :PUBLIC? TRUE)", ((cpp_function_code)(&createDescription)), NULL);
    defineMethodObject("(DEFMETHOD (DESCRIPTION-NAME SYMBOL) ((SELF DESCRIPTION)) :DOCUMENTATION \"Return the name of the description `self', if it has one.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Description::descriptionName))), NULL);
    defineMethodObject("(DEFMETHOD (DESCRIPTION-NAME SYMBOL) ((SELF NAMED-DESCRIPTION)) :DOCUMENTATION \"Return the name of the description `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NamedDescription::descriptionName))), NULL);
    defineFunctionObject("CREATE-BASE-RELATION-FOR-POLYMORPHIC-DESCRIPTION", "(DEFUN CREATE-BASE-RELATION-FOR-POLYMORPHIC-DESCRIPTION ((DESCRIPTION DESCRIPTION)))", ((cpp_function_code)(&createBaseRelationForPolymorphicDescription)), NULL);
    defineFunctionObject("YIELD-SYSTEM-DEFINED-PARAMETER-NAME", "(DEFUN (YIELD-SYSTEM-DEFINED-PARAMETER-NAME SYMBOL) ((INDEX INTEGER) (REFERENCEOBJECT OBJECT)))", ((cpp_function_code)(&yieldSystemDefinedParameterName)), NULL);
    defineFunctionObject("ENSURE-DESCRIPTION-BODY", "(DEFUN ENSURE-DESCRIPTION-BODY ((DESCRIPTION DESCRIPTION)))", ((cpp_function_code)(&ensureDescriptionBody)), NULL);
    defineFunctionObject("MATERIALIZE-PRIMITIVE-DESCRIPTION-BODY", "(DEFUN MATERIALIZE-PRIMITIVE-DESCRIPTION-BODY ((DESCRIPTION NAMED-DESCRIPTION)))", ((cpp_function_code)(&materializePrimitiveDescriptionBody)), NULL);
    defineFunctionObject("CREATE-PRIMITIVE-DESCRIPTION", "(DEFUN (CREATE-PRIMITIVE-DESCRIPTION NAMED-DESCRIPTION) ((IOVARIABLENAMES (LIST OF SYMBOL)) (IOVARIABLETYPES (LIST OF TYPE)) (VARIABLEARITY? BOOLEAN) (CLASS? BOOLEAN) (FUNCTION? BOOLEAN) (MODULE MODULE)))", ((cpp_function_code)(&createPrimitiveDescription)), NULL);
    defineFunctionObject("LINK-STELLA-RELATION-AND-DESCRIPTION", "(DEFUN LINK-STELLA-RELATION-AND-DESCRIPTION ((SELF RELATION) (DESCRIPTION NAMED-DESCRIPTION)))", ((cpp_function_code)(&linkStellaRelationAndDescription)), NULL);
    defineFunctionObject("CREATE-DESCRIPTION-FOR-STELLA-RELATION", "(DEFUN (CREATE-DESCRIPTION-FOR-STELLA-RELATION NAMED-DESCRIPTION) ((SELF RELATION)))", ((cpp_function_code)(&createDescriptionForStellaRelation)), NULL);
    defineFunctionObject("SURROGATE-TO-DESCRIPTION", "(DEFUN (SURROGATE-TO-DESCRIPTION NAMED-DESCRIPTION) ((SELF SURROGATE)))", ((cpp_function_code)(&surrogateToDescription)), NULL);
    defineFunctionObject("GET-DESCRIPTION", "(DEFUN (GET-DESCRIPTION NAMED-DESCRIPTION) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&getDescription)), NULL);
    defineFunctionObject("SURROGATE.GET-DESCRIPTION", "(DEFUN (SURROGATE.GET-DESCRIPTION NAMED-DESCRIPTION) ((SELF SURROGATE)))", ((cpp_function_code)(&surrogateDgetDescription)), NULL);
    defineFunctionObject("STRING.GET-DESCRIPTION", "(DEFUN (STRING.GET-DESCRIPTION NAMED-DESCRIPTION) ((SELF STRING)))", ((cpp_function_code)(&stringDgetDescription)), NULL);
    defineFunctionObject("CLASS.GET-DESCRIPTION", "(DEFUN (CLASS.GET-DESCRIPTION NAMED-DESCRIPTION) ((SELF CLASS)))", ((cpp_function_code)(&classDgetDescription)), NULL);
    defineFunctionObject("SLOT.GET-DESCRIPTION", "(DEFUN (SLOT.GET-DESCRIPTION NAMED-DESCRIPTION) ((SELF SLOT)))", ((cpp_function_code)(&slotDgetDescription)), NULL);
    defineFunctionObject("ENSURE-DEFERRED-DESCRIPTION", "(DEFUN (ENSURE-DEFERRED-DESCRIPTION SURROGATE) ((SELF SURROGATE)))", ((cpp_function_code)(&ensureDeferredDescription)), NULL);
    defineFunctionObject("LOGIC-CLASS?", "(DEFUN (LOGIC-CLASS? BOOLEAN) ((SELF CLASS)) :DOCUMENTATION \"Return TRUE if the class 'self' or one of its\nsupers supports indices that record extensions referenced by\nthe logic system. Also return true for literal classes.\")", ((cpp_function_code)(&logicClassP)), NULL);
    defineFunctionObject("VARIABLE-ARITY-DOMAIN-TYPES-NEXT?", "(DEFUN (VARIABLE-ARITY-DOMAIN-TYPES-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&variableArityDomainTypesNextP)), NULL);
    defineFunctionObject("WRAP-ITERATOR-FOR-VARIABLE-ARITY", "(DEFUN (WRAP-ITERATOR-FOR-VARIABLE-ARITY ITERATOR) ((ITERATOR ITERATOR)))", ((cpp_function_code)(&wrapIteratorForVariableArity)), NULL);
    defineFunctionObject("ALL-DOMAIN-TYPES", "(DEFUN (ALL-DOMAIN-TYPES ITERATOR) ((SELF NAMED-DESCRIPTION)))", ((cpp_function_code)(&allDomainTypes)), NULL);
    defineFunctionObject("ALL-ARGUMENT-TYPES", "(DEFUN (ALL-ARGUMENT-TYPES ITERATOR) ((SELF NAMED-DESCRIPTION)))", ((cpp_function_code)(&allArgumentTypes)), NULL);
    defineFunctionObject("PUSH-LOGIC-VARIABLE-BINDING", "(DEFUN PUSH-LOGIC-VARIABLE-BINDING ((VARIABLE SKOLEM)))", ((cpp_function_code)(&pushLogicVariableBinding)), NULL);
    defineFunctionObject("POP-LOGIC-VARIABLE-BINDING", "(DEFUN POP-LOGIC-VARIABLE-BINDING ())", ((cpp_function_code)(&popLogicVariableBinding)), NULL);
    defineFunctionObject("POP-LOGIC-VARIABLE-BINDINGS", "(DEFUN POP-LOGIC-VARIABLE-BINDINGS ((VARIABLES (CONS OF SKOLEM))))", ((cpp_function_code)(&popLogicVariableBindings)), NULL);
    defineFunctionObject("LOOKUP-LOGIC-VARIABLE-BINDING", "(DEFUN (LOOKUP-LOGIC-VARIABLE-BINDING OBJECT) ((VARIABLENAME SYMBOL)))", ((cpp_function_code)(&lookupLogicVariableBinding)), NULL);
    defineFunctionObject("PARSE-ONE-VARIABLE-DECLARATION", "(DEFUN PARSE-ONE-VARIABLE-DECLARATION ((VDEC OBJECT) (LOCALDECLARATIONS (LIST OF PATTERN-VARIABLE))))", ((cpp_function_code)(&parseOneVariableDeclaration)), NULL);
    defineFunctionObject("PARSE-LOGIC-VARIABLE-DECLARATIONS", "(DEFUN (PARSE-LOGIC-VARIABLE-DECLARATIONS (CONS OF PATTERN-VARIABLE)) ((TREE OBJECT)))", ((cpp_function_code)(&parseLogicVariableDeclarations)), NULL);
    defineFunctionObject("HELP-BUILD-QUANTIFIED-PROPOSITION", "(DEFUN (HELP-BUILD-QUANTIFIED-PROPOSITION (CONS OF SKOLEM) PROPOSITION PROPOSITION) ((TREE CONS) (CONVERTTYPESTOCONSTRAINTS? BOOLEAN)))", ((cpp_function_code)(&helpBuildQuantifiedProposition)), NULL);
    defineFunctionObject("BUILD-QUANTIFIED-PROPOSITION", "(DEFUN (BUILD-QUANTIFIED-PROPOSITION (CONS OF SKOLEM) PROPOSITION PROPOSITION) ((TREE CONS) (CONVERTTYPESTOCONSTRAINTS? BOOLEAN)))", ((cpp_function_code)(&buildQuantifiedProposition)), NULL);
    defineFunctionObject("COPY-CONS-LIST-TO-VARIABLES-VECTOR", "(DEFUN (COPY-CONS-LIST-TO-VARIABLES-VECTOR VARIABLES-VECTOR) ((CONSLIST CONS)))", ((cpp_function_code)(&copyConsListToVariablesVector)), NULL);
    defineFunctionObject("EQUIVALENT-HOLDS-PROPOSITION?", "(DEFUN (EQUIVALENT-HOLDS-PROPOSITION? BOOLEAN) ((SELF PROPOSITION) (OTHER PROPOSITION) (MAPPING ENTITY-MAPPING)))", ((cpp_function_code)(&equivalentHoldsPropositionP)), NULL);
    defineFunctionObject("EQUIVALENT-COMMUTATIVE-PROPOSITIONS?", "(DEFUN (EQUIVALENT-COMMUTATIVE-PROPOSITIONS? BOOLEAN) ((SELF PROPOSITION) (OTHER PROPOSITION) (MAPPING ENTITY-MAPPING)))", ((cpp_function_code)(&equivalentCommutativePropositionsP)), NULL);
    defineFunctionObject("HELP-EQUIVALENT-PROPOSITIONS?", "(DEFUN (HELP-EQUIVALENT-PROPOSITIONS? BOOLEAN) ((SELF PROPOSITION) (OTHER PROPOSITION) (MAPPING ENTITY-MAPPING) (IGNORELASTARG? BOOLEAN)))", ((cpp_function_code)(&helpEquivalentPropositionsP)), NULL);
    defineFunctionObject("EQUIVALENT-PROPOSITIONS?", "(DEFUN (EQUIVALENT-PROPOSITIONS? BOOLEAN) ((SELF PROPOSITION) (OTHER PROPOSITION) (MAPPING ENTITY-MAPPING)))", ((cpp_function_code)(&equivalentPropositionsP)), NULL);
    defineFunctionObject("EQUIVALENT-FUNCTION-PROPOSITIONS?", "(DEFUN (EQUIVALENT-FUNCTION-PROPOSITIONS? BOOLEAN) ((SELF PROPOSITION) (OTHER PROPOSITION) (MAPPING ENTITY-MAPPING)))", ((cpp_function_code)(&equivalentFunctionPropositionsP)), NULL);
    defineFunctionObject("EQUIVALENT-DESCRIPTIONS?", "(DEFUN (EQUIVALENT-DESCRIPTIONS? BOOLEAN) ((SELF DESCRIPTION) (OTHER DESCRIPTION) (MAPPING ENTITY-MAPPING)))", ((cpp_function_code)(&equivalentDescriptionsP)), NULL);
    defineFunctionObject("EQUIVALENT-ENUMERATIONS?", "(DEFUN (EQUIVALENT-ENUMERATIONS? BOOLEAN) ((SELF COLLECTION) (OTHER COLLECTION)))", ((cpp_function_code)(&equivalentEnumerationsP)), NULL);
    defineFunctionObject("EQUIVALENT-FORMULAE?", "(DEFUN (EQUIVALENT-FORMULAE? BOOLEAN) ((SELF OBJECT) (OTHER OBJECT) (MAPPING ENTITY-MAPPING)))", ((cpp_function_code)(&equivalentFormulaeP)), NULL);
    defineFunctionObject("SAME-AND-UNIQUE-ARGUMENTS?", "(DEFUN (SAME-AND-UNIQUE-ARGUMENTS? BOOLEAN) ((VARIABLES VARIABLES-VECTOR) (ARGUMENTS VECTOR)))", ((cpp_function_code)(&sameAndUniqueArgumentsP)), NULL);
    defineFunctionObject("UNIFY-PROPOSITIONS?", "(DEFUN (UNIFY-PROPOSITIONS? BOOLEAN) ((SELF PROPOSITION) (OTHER PROPOSITION) (MAPPING ENTITY-MAPPING)))", ((cpp_function_code)(&unifyPropositionsP)), NULL);
    defineFunctionObject("DESCRIPTION?", "(DEFUN (DESCRIPTION? BOOLEAN) ((SELF OBJECT)) :DOCUMENTATION \"Return TRUE if 'self' is a description.\" :PUBLIC? TRUE)", ((cpp_function_code)(&descriptionP)), NULL);
    defineFunctionObject("UNNAMED-DESCRIPTION?", "(DEFUN (UNNAMED-DESCRIPTION? BOOLEAN) ((SELF OBJECT)) :DOCUMENTATION \"Return TRUE if 'self' is an unnamed description.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unnamedDescriptionP)), NULL);
    defineFunctionObject("NAMED-DESCRIPTION?", "(DEFUN (NAMED-DESCRIPTION? BOOLEAN) ((SELF DESCRIPTION)) :DOCUMENTATION \"Return TRUE if 'self' is the description of a named class or relation.\" :PUBLIC? TRUE)", ((cpp_function_code)(&namedDescriptionP)), NULL);
    defineMethodObject("(DEFMETHOD (FIND-DUPLICATE-NAMED-DESCRIPTION LOGIC-OBJECT) ((SELF DESCRIPTION)))", wrapMethodCode(((cpp_method_code)(&Description::findDuplicateNamedDescription))), NULL);
    defineFunctionObject("FIND-DUPLICATE-COMPLEX-DESCRIPTION", "(DEFUN (FIND-DUPLICATE-COMPLEX-DESCRIPTION DESCRIPTION) ((SELF DESCRIPTION)))", ((cpp_function_code)(&findDuplicateComplexDescription)), NULL);
    defineFunctionObject("FIND-DUPLICATE-DESCRIPTION", "(DEFUN (FIND-DUPLICATE-DESCRIPTION DESCRIPTION) ((SELF DESCRIPTION)))", ((cpp_function_code)(&findDuplicateDescription)), NULL);
    defineFunctionObject("CONTAINS-NESTED-ARGUMENT?", "(DEFUN (CONTAINS-NESTED-ARGUMENT? BOOLEAN) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&containsNestedArgumentP)), NULL);
    defineFunctionObject("EXPAND-IF-PROPOSITION", "(DEFUN (EXPAND-IF-PROPOSITION PROPOSITION) ((IFPROPOSITION PROPOSITION)))", ((cpp_function_code)(&expandIfProposition)), NULL);
    defineFunctionObject("HELP-COLLECT-FLATTENED-ARGUMENTS", "(DEFUN HELP-COLLECT-FLATTENED-ARGUMENTS ((SELF PROPOSITION) (FLATTENEDARGUMENTS (LIST OF PROPOSITION)) (EXISTSVARIABLES (LIST OF PATTERN-VARIABLE))))", ((cpp_function_code)(&helpCollectFlattenedArguments)), NULL);
    defineFunctionObject("YIELD-FLATTENED-ARGUMENTS", "(DEFUN (YIELD-FLATTENED-ARGUMENTS (LIST OF PROPOSITION)) ((PROPOSITION PROPOSITION) (EXISTSVARIABLES (LIST OF PATTERN-VARIABLE))))", ((cpp_function_code)(&yieldFlattenedArguments)), NULL);
    defineFunctionObject("FLATTEN-NESTED-FUNCTION-ARGUMENTS", "(DEFUN (FLATTEN-NESTED-FUNCTION-ARGUMENTS PROPOSITION) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&flattenNestedFunctionArguments)), NULL);
    defineFunctionObject("COLLAPSE-VALUE-OF-CHAINS-FOR-IO-VARIABLES", "(DEFUN COLLAPSE-VALUE-OF-CHAINS-FOR-IO-VARIABLES ((IOVARIABLES VARIABLES-VECTOR)))", ((cpp_function_code)(&collapseValueOfChainsForIoVariables)), NULL);
    defineFunctionObject("REMOVE-NULLS-IN-VARIABLES-VECTOR", "(DEFUN (REMOVE-NULLS-IN-VARIABLES-VECTOR VARIABLES-VECTOR) ((IOVARIABLES VARIABLES-VECTOR)))", ((cpp_function_code)(&removeNullsInVariablesVector)), NULL);
    defineFunctionObject("TIGHTEN-ARGUMENT-BINDINGS", "(DEFUN TIGHTEN-ARGUMENT-BINDINGS ((PROPOSITION PROPOSITION) (IOVARIABLES VARIABLES-VECTOR)))", ((cpp_function_code)(&tightenArgumentBindings)), NULL);
    defineFunctionObject("EQUATE-TOP-LEVEL-EQUIVALENCES", "(DEFUN EQUATE-TOP-LEVEL-EQUIVALENCES ((PROPOSITION PROPOSITION) (IOVARIABLES VARIABLES-VECTOR) (KIND KEYWORD)))", ((cpp_function_code)(&equateTopLevelEquivalences)), NULL);
    defineFunctionObject("COLLECT-ALL-VARIABLES", "(DEFUN COLLECT-ALL-VARIABLES ((SELF PROPOSITION) (COLLECTION (LIST OF PATTERN-VARIABLE)) (BEENTHERE LIST)))", ((cpp_function_code)(&collectAllVariables)), NULL);
  }
}

void startupDescriptions() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupDescriptions1();
      helpStartupDescriptions2();
      helpStartupDescriptions3();
    }
    if (currentStartupTimePhaseP(4)) {
      FAKE_IO_VARIABLES = stella::newVector(0);
      SYSTEM_DEFINED_ARGUMENT_NAMES = listO(101, SYM_DESCRIPTIONS_LOGIC_pX1, SYM_DESCRIPTIONS_LOGIC_pX2, SYM_DESCRIPTIONS_LOGIC_pX3, SYM_DESCRIPTIONS_LOGIC_pX4, SYM_DESCRIPTIONS_LOGIC_pX5, SYM_DESCRIPTIONS_LOGIC_pX6, SYM_DESCRIPTIONS_LOGIC_pX7, SYM_DESCRIPTIONS_LOGIC_pX8, SYM_DESCRIPTIONS_LOGIC_pX9, SYM_DESCRIPTIONS_LOGIC_pX10, SYM_DESCRIPTIONS_LOGIC_pX11, SYM_DESCRIPTIONS_LOGIC_pX12, SYM_DESCRIPTIONS_LOGIC_pX13, SYM_DESCRIPTIONS_LOGIC_pX14, SYM_DESCRIPTIONS_LOGIC_pX15, SYM_DESCRIPTIONS_LOGIC_pX16, SYM_DESCRIPTIONS_LOGIC_pX17, SYM_DESCRIPTIONS_LOGIC_pX18, SYM_DESCRIPTIONS_LOGIC_pX19, SYM_DESCRIPTIONS_LOGIC_pX20, SYM_DESCRIPTIONS_LOGIC_pX21, SYM_DESCRIPTIONS_LOGIC_pX22, SYM_DESCRIPTIONS_LOGIC_pX23, SYM_DESCRIPTIONS_LOGIC_pX24, SYM_DESCRIPTIONS_LOGIC_pX25, SYM_DESCRIPTIONS_LOGIC_pX26, SYM_DESCRIPTIONS_LOGIC_pX27, SYM_DESCRIPTIONS_LOGIC_pX28, SYM_DESCRIPTIONS_LOGIC_pX29, SYM_DESCRIPTIONS_LOGIC_pX30, SYM_DESCRIPTIONS_LOGIC_pX31, SYM_DESCRIPTIONS_LOGIC_pX32, SYM_DESCRIPTIONS_LOGIC_pX33, SYM_DESCRIPTIONS_LOGIC_pX34, SYM_DESCRIPTIONS_LOGIC_pX35, SYM_DESCRIPTIONS_LOGIC_pX36, SYM_DESCRIPTIONS_LOGIC_pX37, SYM_DESCRIPTIONS_LOGIC_pX38, SYM_DESCRIPTIONS_LOGIC_pX39, SYM_DESCRIPTIONS_LOGIC_pX40, SYM_DESCRIPTIONS_LOGIC_pX41, SYM_DESCRIPTIONS_LOGIC_pX42, SYM_DESCRIPTIONS_LOGIC_pX43, SYM_DESCRIPTIONS_LOGIC_pX44, SYM_DESCRIPTIONS_LOGIC_pX45, SYM_DESCRIPTIONS_LOGIC_pX46, SYM_DESCRIPTIONS_LOGIC_pX47, SYM_DESCRIPTIONS_LOGIC_pX48, SYM_DESCRIPTIONS_LOGIC_pX49, SYM_DESCRIPTIONS_LOGIC_pX50, SYM_DESCRIPTIONS_LOGIC_pX51, SYM_DESCRIPTIONS_LOGIC_pX52, SYM_DESCRIPTIONS_LOGIC_pX53, SYM_DESCRIPTIONS_LOGIC_pX54, SYM_DESCRIPTIONS_LOGIC_pX55, SYM_DESCRIPTIONS_LOGIC_pX56, SYM_DESCRIPTIONS_LOGIC_pX57, SYM_DESCRIPTIONS_LOGIC_pX58, SYM_DESCRIPTIONS_LOGIC_pX59, SYM_DESCRIPTIONS_LOGIC_pX60, SYM_DESCRIPTIONS_LOGIC_pX61, SYM_DESCRIPTIONS_LOGIC_pX62, SYM_DESCRIPTIONS_LOGIC_pX63, SYM_DESCRIPTIONS_LOGIC_pX64, SYM_DESCRIPTIONS_LOGIC_pX65, SYM_DESCRIPTIONS_LOGIC_pX66, SYM_DESCRIPTIONS_LOGIC_pX67, SYM_DESCRIPTIONS_LOGIC_pX68, SYM_DESCRIPTIONS_LOGIC_pX69, SYM_DESCRIPTIONS_LOGIC_pX70, SYM_DESCRIPTIONS_LOGIC_pX71, SYM_DESCRIPTIONS_LOGIC_pX72, SYM_DESCRIPTIONS_LOGIC_pX73, SYM_DESCRIPTIONS_LOGIC_pX74, SYM_DESCRIPTIONS_LOGIC_pX75, SYM_DESCRIPTIONS_LOGIC_pX76, SYM_DESCRIPTIONS_LOGIC_pX77, SYM_DESCRIPTIONS_LOGIC_pX78, SYM_DESCRIPTIONS_LOGIC_pX79, SYM_DESCRIPTIONS_LOGIC_pX80, SYM_DESCRIPTIONS_LOGIC_pX81, SYM_DESCRIPTIONS_LOGIC_pX82, SYM_DESCRIPTIONS_LOGIC_pX83, SYM_DESCRIPTIONS_LOGIC_pX84, SYM_DESCRIPTIONS_LOGIC_pX85, SYM_DESCRIPTIONS_LOGIC_pX86, SYM_DESCRIPTIONS_LOGIC_pX87, SYM_DESCRIPTIONS_LOGIC_pX88, SYM_DESCRIPTIONS_LOGIC_pX89, SYM_DESCRIPTIONS_LOGIC_pX90, SYM_DESCRIPTIONS_LOGIC_pX91, SYM_DESCRIPTIONS_LOGIC_pX92, SYM_DESCRIPTIONS_LOGIC_pX93, SYM_DESCRIPTIONS_LOGIC_pX94, SYM_DESCRIPTIONS_LOGIC_pX95, SYM_DESCRIPTIONS_LOGIC_pX96, SYM_DESCRIPTIONS_LOGIC_pX97, SYM_DESCRIPTIONS_LOGIC_pX98, SYM_DESCRIPTIONS_LOGIC_pX99, SYM_DESCRIPTIONS_LOGIC_pX100, NIL);
      oVARIABLETYPEPROPOSITIONSo = NIL;
    }
    if (currentStartupTimePhaseP(5)) {
      defineStellaTypeFromStringifiedSource("(DEFTYPE VARIABLE-TYPE-TABLE (KEY-VALUE-LIST OF PATTERN-VARIABLE (LIST OF TYPE)))");
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupDescriptions4();
      defineFunctionObject("COMPUTE-INTERNAL-VARIABLES", "(DEFUN COMPUTE-INTERNAL-VARIABLES ((SELF DESCRIPTION)))", ((cpp_function_code)(&computeInternalVariables)), NULL);
      defineFunctionObject("COLLECT-EXTERNAL-VARIABLES", "(DEFUN COLLECT-EXTERNAL-VARIABLES ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&collectExternalVariables)), NULL);
      defineFunctionObject("FINISH-BUILDING-DESCRIPTION", "(DEFUN (FINISH-BUILDING-DESCRIPTION DESCRIPTION) ((DESCRIPTION DESCRIPTION) (CHECKFORDUPLICATE? BOOLEAN) (KIND KEYWORD)))", ((cpp_function_code)(&finishBuildingDescription)), NULL);
      defineFunctionObject("EVALUATE-DESCRIPTION-TERM", "(DEFUN (EVALUATE-DESCRIPTION-TERM DESCRIPTION) ((TERM CONS) (CHECKFORDUPLICATE? BOOLEAN)))", ((cpp_function_code)(&evaluateDescriptionTerm)), NULL);
      defineFunctionObject("REMOVE-VARIABLE-TYPE-PROPOSITIONS", "(DEFUN (REMOVE-VARIABLE-TYPE-PROPOSITIONS (CONS OF PROPOSITION)) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&removeVariableTypePropositions)), NULL);
      defineFunctionObject("GET-COMPLEMENT-OF-GOAL-DESCRIPTION", "(DEFUN (GET-COMPLEMENT-OF-GOAL-DESCRIPTION DESCRIPTION) ((SELF NAMED-DESCRIPTION)))", ((cpp_function_code)(&getComplementOfGoalDescription)), NULL);
      defineFunctionObject("COLLECT-FREE-VARIABLES", "(DEFUN COLLECT-FREE-VARIABLES ((SELF OBJECT) (COLLECTION (LIST OF PATTERN-VARIABLE)) (QUANTIFIEDVARS LIST) (BEENTHERE LIST)))", ((cpp_function_code)(&collectFreeVariables)), NULL);
      defineFunctionObject("TOP-LEVEL-EXISTENTIAL-VARIABLES", "(DEFUN (TOP-LEVEL-EXISTENTIAL-VARIABLES (CONS OF PATTERN-VARIABLE)) ((SELF DESCRIPTION)))", ((cpp_function_code)(&topLevelExistentialVariables)), NULL);
      defineFunctionObject("TOP-LEVEL-EXISTENTIAL-VARIABLE?", "(DEFUN (TOP-LEVEL-EXISTENTIAL-VARIABLE? BOOLEAN) ((VARIABLE PATTERN-VARIABLE) (DESCRIPTION DESCRIPTION)))", ((cpp_function_code)(&topLevelExistentialVariableP)), NULL);
      defineFunctionObject("FREE-VARIABLE?", "(DEFUN (FREE-VARIABLE? BOOLEAN) ((VARIABLE PATTERN-VARIABLE) (PROPOSITION PROPOSITION)))", ((cpp_function_code)(&freeVariableP)), NULL);
      defineFunctionObject("MOST-SPECIFIC-TYPES", "(DEFUN (MOST-SPECIFIC-TYPES (LIST OF TYPE)) ((TYPES (LIST OF TYPE))))", ((cpp_function_code)(&mostSpecificTypes)), NULL);
      defineFunctionObject("ADD-VARIABLE-TYPE", "(DEFUN ADD-VARIABLE-TYPE ((VARIABLE PATTERN-VARIABLE) (NEWTYPE TYPE) (TABLE VARIABLE-TYPE-TABLE) (VISIBLEVARIABLES (CONS OF PATTERN-VARIABLE))))", ((cpp_function_code)(&addVariableType)), NULL);
      defineFunctionObject("INFER-PREDICATE-FROM-OPERATOR-AND-TYPES", "(DEFUN (INFER-PREDICATE-FROM-OPERATOR-AND-TYPES OBJECT) ((OPERATOR OBJECT) (TYPES (LIST OF TYPE))))", ((cpp_function_code)(&inferPredicateFromOperatorAndTypes)), NULL);
      defineFunctionObject("INFER-TYPES-FROM-ONE-PROPOSITION", "(DEFUN INFER-TYPES-FROM-ONE-PROPOSITION ((PROPOSITION PROPOSITION) (TABLE VARIABLE-TYPE-TABLE) (VISIBLEVARS (CONS OF PATTERN-VARIABLE))))", ((cpp_function_code)(&inferTypesFromOneProposition)), NULL);
      defineFunctionObject("INFER-TYPES-FROM-PROPOSITIONS", "(DEFUN INFER-TYPES-FROM-PROPOSITIONS ((PROPOSITION PROPOSITION) (TABLE VARIABLE-TYPE-TABLE) (VISIBLEVARS (CONS OF PATTERN-VARIABLE))))", ((cpp_function_code)(&inferTypesFromPropositions)), NULL);
      defineFunctionObject("INFER-VARIABLE-TYPES-IN-PROPOSITION", "(DEFUN (INFER-VARIABLE-TYPES-IN-PROPOSITION VARIABLE-TYPE-TABLE) ((PROPOSITION PROPOSITION) (VISIBLEVARIABLES (CONS OF PATTERN-VARIABLE))))", ((cpp_function_code)(&inferVariableTypesInProposition)), NULL);
      defineFunctionObject("INFER-VARIABLE-TYPES-IN-DESCRIPTION", "(DEFUN (INFER-VARIABLE-TYPES-IN-DESCRIPTION VARIABLE-TYPE-TABLE) ((DESCRIPTION DESCRIPTION)))", ((cpp_function_code)(&inferVariableTypesInDescription)), NULL);
      defineFunctionObject("COLLECT-UNRESOLVED-SLOT-REFERENCES", "(DEFUN (COLLECT-UNRESOLVED-SLOT-REFERENCES (CONS OF PROPOSITION)) ((SELF PROPOSITION)))", ((cpp_function_code)(&collectUnresolvedSlotReferences)), NULL);
      defineFunctionObject("RESOLVE-ONE-SLOT-REFERENCE?", "(DEFUN (RESOLVE-ONE-SLOT-REFERENCE? BOOLEAN) ((PROPOSITION PROPOSITION) (VARIABLETYPESTABLE VARIABLE-TYPE-TABLE)))", ((cpp_function_code)(&resolveOneSlotReferenceP)), NULL);
      defineFunctionObject("RESOLVE-UNRESOLVED-SLOT-REFERENCES", "(DEFUN RESOLVE-UNRESOLVED-SLOT-REFERENCES ((FORMULA OBJECT)))", ((cpp_function_code)(&resolveUnresolvedSlotReferences)), NULL);
      defineFunctionObject("CREATE-DUMMY-RELATION", "(DEFUN CREATE-DUMMY-RELATION ((WAYWARDPROPOSITION PROPOSITION)))", ((cpp_function_code)(&createDummyRelation)), NULL);
      defineFunctionObject("DEFINED-RELATION?", "(DEFUN (DEFINED-RELATION? BOOLEAN) ((SELF NAMED-DESCRIPTION)))", ((cpp_function_code)(&definedRelationP)), NULL);
      defineFunctionObject("LIST-UNDEFINED-RELATIONS", "(DEFUN (LIST-UNDEFINED-RELATIONS (CONS OF NAMED-DESCRIPTION)) (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Return a list of as yet undefined concepts and relations in the module defined\nby the :module option (which defaults to the current module).  These relations were\ndefined by the system, since they were referenced but have not yet been defined by\nthe user.  If `:local?' is specified as TRUE only look in the specified module but\nnot any modules it inherits.  For backwards compatibility, this command also supports\nthe old <module> <local?> arguments specified without keywords.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&listUndefinedRelations)), ((cpp_function_code)(&listUndefinedRelationsEvaluatorWrapper)));
      defineFunctionObject("CALL-LIST-UNDEFINED-RELATIONS", "(DEFUN (CALL-LIST-UNDEFINED-RELATIONS CONS) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Callable version of `list-undefined-relations' (which see).\" :PUBLIC? TRUE)", ((cpp_function_code)(&callListUndefinedRelations)), NULL);
      defineFunctionObject("COMPLAIN-ABOUT-UNDECLARED-REFERENCE", "(DEFUN COMPLAIN-ABOUT-UNDECLARED-REFERENCE ((WAYWARDPROPOSITION PROPOSITION)))", ((cpp_function_code)(&complainAboutUndeclaredReference)), NULL);
      defineFunctionObject("ALL-NAMED-DESCRIPTIONS-NEXT?", "(DEFUN (ALL-NAMED-DESCRIPTIONS-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))", ((cpp_function_code)(&allNamedDescriptionsNextP)), NULL);
      defineFunctionObject("ALL-NAMED-DESCRIPTIONS", "(DEFUN (ALL-NAMED-DESCRIPTIONS (ITERATOR OF NAMED-DESCRIPTION)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all named descriptions visible from 'module'.\nIf 'local?', return only named descriptions interned in 'module'.\nIf 'module' is null, return all named descriptions interned everywhere.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allNamedDescriptions)), NULL);
      defineFunctionObject("STARTUP-DESCRIPTIONS", "(DEFUN STARTUP-DESCRIPTIONS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupDescriptions)), NULL);
      { MethodSlot* function = lookupFunction(SYM_DESCRIPTIONS_LOGIC_STARTUP_DESCRIPTIONS);

        setDynamicSlotValue(function->dynamicSlots, SYM_DESCRIPTIONS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupDescriptions"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFCONSTANT FAKE-IO-VARIABLES VARIABLES-VECTOR (NEW VARIABLES-VECTOR :ARRAY-SIZE 0) :DOCUMENTATION \"Installed in a description with undetermined arity.\")", &FAKE_IO_VARIABLES);
      defineGlobalVariableObject("(DEFCONSTANT SYSTEM-DEFINED-ARGUMENT-NAMES (CONS OF SYMBOL) (BQUOTE (?X1 ?X2 ?X3 ?X4 ?X5 ?X6 ?X7 ?X8 ?X9 ?X10 ?X11 ?X12 ?X13 ?X14 ?X15 ?X16 ?X17 ?X18 ?X19 ?X20 ?X21 ?X22 ?X23 ?X24 ?X25 ?X26 ?X27 ?X28 ?X29 ?X30 ?X31 ?X32 ?X33 ?X34 ?X35 ?X36 ?X37 ?X38 ?X39 ?X40 ?X41 ?X42 ?X43 ?X44 ?X45 ?X46 ?X47 ?X48 ?X49 ?X50 ?X51 ?X52 ?X53 ?X54 ?X55 ?X56 ?X57 ?X58 ?X59 ?X60 ?X61 ?X62 ?X63 ?X64 ?X65 ?X66 ?X67 ?X68 ?X69 ?X70 ?X71 ?X72 ?X73 ?X74 ?X75 ?X76 ?X77 ?X78 ?X79 ?X80 ?X81 ?X82 ?X83 ?X84 ?X85 ?X86 ?X87 ?X88 ?X89 ?X90 ?X91 ?X92 ?X93 ?X94 ?X95 ?X96 ?X97 ?X98 ?X99 ?X100)) :PUBLIC? TRUE)", &SYSTEM_DEFINED_ARGUMENT_NAMES);
      defineGlobalVariableObject("(DEFSPECIAL *LOGICVARIABLETABLE* (CONS OF SKOLEM) NULL :DOCUMENTATION \"Table mapping logic variable names to variables or skolems.\nUsed during construction of a proposition or description.\")", &oLOGICVARIABLETABLEo);
      defineGlobalVariableObject("(DEFSPECIAL *VARIABLETYPEPROPOSITIONS* (CONS OF PROPOSITION) NIL :DOCUMENTATION \"List of propositions extracted from parsing\na list of quantified, typed variables.\")", &oVARIABLETYPEPROPOSITIONSo);
      defineGlobalVariableObject("(DEFSPECIAL *UNIFY-PROPOSITIONS?* BOOLEAN FALSE)", &oUNIFY_PROPOSITIONSpo);
      defineGlobalVariableObject("(DEFSPECIAL *EXTERNALVARIABLES* CONS :DOCUMENTATION \"Used by 'evaluate-DESCRIPTION-term' for collecting\na list of variables declared external to the description in which they\nare referenced.\")", &oEXTERNALVARIABLESo);
      defineGlobalVariableObject("(DEFSPECIAL *RECURSIVEGETCOMPLEMENTARGUMENT* NAMED-DESCRIPTION NULL :DOCUMENTATION \"Used to prevent infinite looping.\")", &oRECURSIVEGETCOMPLEMENTARGUMENTo);
      defineGlobalVariableObject("(DEFSPECIAL *ADDEDNEWTYPE?* BOOLEAN FALSE :DOCUMENTATION \"Used by 'infer-variable-types'.\")", &oADDEDNEWTYPEpo);
    }
  }
}

Surrogate* SGT_DESCRIPTIONS_STELLA_SLOT = NULL;

Surrogate* SGT_DESCRIPTIONS_STELLA_METHOD_SLOT = NULL;

Symbol* SYM_DESCRIPTIONS_STELLA_ANY_VALUE = NULL;

Keyword* KWD_DESCRIPTIONS_EXTENSIONAL_ASSERTION = NULL;

Surrogate* SGT_DESCRIPTIONS_PL_KERNEL_KB_RELATION = NULL;

Surrogate* SGT_DESCRIPTIONS_PL_KERNEL_KB_POLYMORPHIC = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX1 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX2 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX3 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX4 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX5 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX6 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX7 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX8 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX9 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX10 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX11 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX12 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX13 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX14 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX15 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX16 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX17 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX18 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX19 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX20 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX21 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX22 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX23 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX24 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX25 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX26 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX27 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX28 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX29 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX30 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX31 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX32 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX33 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX34 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX35 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX36 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX37 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX38 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX39 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX40 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX41 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX42 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX43 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX44 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX45 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX46 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX47 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX48 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX49 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX50 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX51 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX52 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX53 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX54 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX55 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX56 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX57 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX58 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX59 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX60 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX61 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX62 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX63 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX64 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX65 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX66 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX67 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX68 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX69 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX70 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX71 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX72 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX73 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX74 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX75 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX76 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX77 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX78 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX79 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX80 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX81 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX82 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX83 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX84 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX85 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX86 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX87 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX88 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX89 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX90 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX91 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX92 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX93 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX94 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX95 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX96 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX97 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX98 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX99 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX100 = NULL;

Surrogate* SGT_DESCRIPTIONS_LOGIC_NAMED_DESCRIPTION = NULL;

Symbol* SYM_DESCRIPTIONS_STELLA_ISA = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_KAPPA = NULL;

Keyword* KWD_DESCRIPTIONS_KIF = NULL;

Keyword* KWD_DESCRIPTIONS_DESCRIPTION = NULL;

Surrogate* SGT_DESCRIPTIONS_LOGIC_UNFINALIZED = NULL;

Surrogate* SGT_DESCRIPTIONS_PL_KERNEL_KB_CONCEPT = NULL;

Surrogate* SGT_DESCRIPTIONS_PL_KERNEL_KB_FUNCTION = NULL;

Surrogate* SGT_DESCRIPTIONS_PL_KERNEL_KB_VARIABLE_ARITY = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_DESCRIPTIONS_STELLA_CLASS = NULL;

Keyword* KWD_DESCRIPTIONS_ERROR = NULL;

Surrogate* SGT_DESCRIPTIONS_STELLA_RELATION = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_OBJECT_STORE = NULL;

Surrogate* SGT_DESCRIPTIONS_STELLA_THING = NULL;

Surrogate* SGT_DESCRIPTIONS_STELLA_LITERAL = NULL;

Surrogate* SGT_DESCRIPTIONS_LOGIC_PROPOSITION = NULL;

Keyword* KWD_DESCRIPTIONS_WARNING = NULL;

Surrogate* SGT_DESCRIPTIONS_STELLA_CONS = NULL;

Keyword* KWD_DESCRIPTIONS_ISA = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_VARIABLE_TYPEp = NULL;

Symbol* SYM_DESCRIPTIONS_STELLA_EXISTS = NULL;

Keyword* KWD_DESCRIPTIONS_AND = NULL;

Keyword* KWD_DESCRIPTIONS_OR = NULL;

Keyword* KWD_DESCRIPTIONS_EQUIVALENT = NULL;

Keyword* KWD_DESCRIPTIONS_FORALL = NULL;

Keyword* KWD_DESCRIPTIONS_EXISTS = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_IO_VARIABLES = NULL;

Surrogate* SGT_DESCRIPTIONS_PL_KERNEL_KB_HOLDS = NULL;

Keyword* KWD_DESCRIPTIONS_FUNCTION = NULL;

Surrogate* SGT_DESCRIPTIONS_STELLA_SET = NULL;

Surrogate* SGT_DESCRIPTIONS_STELLA_LIST = NULL;

Surrogate* SGT_DESCRIPTIONS_STELLA_SURROGATE = NULL;

Surrogate* SGT_DESCRIPTIONS_LOGIC_DESCRIPTION = NULL;

Keyword* KWD_DESCRIPTIONS_NOT = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_EXTERNAL_VARIABLES = NULL;

Keyword* KWD_DESCRIPTIONS_PREDICATE = NULL;

Keyword* KWD_DESCRIPTIONS_IMPLIES = NULL;

Surrogate* SGT_DESCRIPTIONS_LOGIC_PATTERN_VARIABLE = NULL;

Symbol* SYM_DESCRIPTIONS_STELLA_NOT = NULL;

Surrogate* SGT_DESCRIPTIONS_STELLA_PROPOSITIONdIF = NULL;

Symbol* SYM_DESCRIPTIONS_STELLA_AND = NULL;

Surrogate* SGT_DESCRIPTIONS_STELLA_CS_VALUE = NULL;

Keyword* KWD_DESCRIPTIONS_TAIL = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_THE_ONLY = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_IOTAp = NULL;

Keyword* KWD_DESCRIPTIONS_TOP_LEVEL = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_COMPLEMENT_DESCRIPTION = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_VARIABLE_TYPE_TABLE = NULL;

Surrogate* SGT_DESCRIPTIONS_LOGIC_LOGIC_OBJECT = NULL;

Surrogate* SGT_DESCRIPTIONS_STELLA_SYMBOL = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_UNDECLAREDp = NULL;

Keyword* KWD_DESCRIPTIONS_MODULE = NULL;

Keyword* KWD_DESCRIPTIONS_LOCALp = NULL;

Surrogate* SGT_DESCRIPTIONS_STELLA_MODULE = NULL;

Surrogate* SGT_DESCRIPTIONS_STELLA_BOOLEAN = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_pX = NULL;

Symbol* SYM_DESCRIPTIONS_PL_KERNEL_KB_RELATION = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_F_CALL_LIST_UNDEFINED_RELATIONS_QUERY_000 = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_DESCRIPTIVEp = NULL;

Symbol* SYM_DESCRIPTIONS_LOGIC_STARTUP_DESCRIPTIONS = NULL;

Symbol* SYM_DESCRIPTIONS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
