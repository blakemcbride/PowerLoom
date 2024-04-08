//  -*- Mode: C++ -*-

// propositions.cc

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

BacklinksIndex* newBacklinksIndex() {
  { BacklinksIndex* self = NULL;

    self = new BacklinksIndex();
    self->predicatePropositionsTable = NULL;
    self->dependentIsaPropositionsList = NULL;
    self->dependentPropositionsList = NULL;
    return (self);
  }
}

Surrogate* BacklinksIndex::primaryType() {
  { BacklinksIndex* self = this;

    return (SGT_PROPOSITIONS_LOGIC_BACKLINKS_INDEX);
  }
}

Object* accessBacklinksIndexSlotValue(BacklinksIndex* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PROPOSITIONS_LOGIC_DEPENDENT_PROPOSITIONS_LIST) {
    if (setvalueP) {
      self->dependentPropositionsList = ((SequenceIndex*)(value));
    }
    else {
      value = self->dependentPropositionsList;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_DEPENDENT_ISA_PROPOSITIONS_LIST) {
    if (setvalueP) {
      self->dependentIsaPropositionsList = ((SequenceIndex*)(value));
    }
    else {
      value = self->dependentIsaPropositionsList;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_PREDICATE_PROPOSITIONS_TABLE) {
    if (setvalueP) {
      self->predicatePropositionsTable = ((HashTable*)(value));
    }
    else {
      value = self->predicatePropositionsTable;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

LogicObject* newLogicObject() {
  { LogicObject* self = NULL;

    self = new LogicObject();
    self->dependentPropositionsIndex = NULL;
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->variableValueInverse = NULL;
    self->homeContext = oMODULEo;
    logLogicObject(self);
    return (self);
  }
}

Surrogate* LogicObject::primaryType() {
  { LogicObject* self = this;

    return (SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT);
  }
}

Cons* LogicObject::variableValueInverse_reader() {
  { LogicObject* self = this;

    { Cons* answer = ((Cons*)(accessInContext(self->variableValueInverse, self->homeContext, false)));

      if (!((boolean)(answer))) {
        return (NIL);
      }
      else {
        return (answer);
      }
    }
  }
}

BooleanWrapper* LogicObject::badP_reader() {
  { LogicObject* self = this;

    { BooleanWrapper* answer = ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_STELLA_BADp, NULL)));

      if (!((boolean)(answer))) {
        return (FALSE_WRAPPER);
      }
      else {
        return (answer);
      }
    }
  }
}

Object* accessLogicObjectSlotValue(LogicObject* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PROPOSITIONS_LOGIC_VARIABLE_VALUE_INVERSE) {
    if (setvalueP) {
      { LogicObject* object000 = self;
        Cons* value000 = ((Cons*)(value));
        Object* oldValue000 = object000->variableValueInverse;
        Object* newValue000 = updateInContext(oldValue000, value000, object000->homeContext, false);

        if (!(((boolean)(oldValue000)) &&
            (oldValue000->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
          object000->variableValueInverse = newValue000;
        }
      }
    }
    else {
      value = self->variableValueInverse_reader();
    }
  }
  else if (slotname == SYM_PROPOSITIONS_STELLA_SURROGATE_VALUE_INVERSE) {
    if (setvalueP) {
      self->surrogateValueInverse = ((Surrogate*)(value));
    }
    else {
      value = self->surrogateValueInverse;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_OBJECT_STRINGIFIED_SOURCE) {
    if (setvalueP) {
      stringifiedSourceSetter(self, ((StringWrapper*)(value))->wrapperValue);
    }
    else {
      value = wrapString(stringifiedSource(self));
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_OBJECT_ORIGINATED_PROPOSITIONS) {
    if (setvalueP) {
      originatedPropositionsSetter(self, ((List*)(value)));
    }
    else {
      value = originatedPropositions(self);
    }
  }
  else {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

boolean LogicObject::deletedP() {
  { LogicObject* self = this;

    { BooleanWrapper* deletedP = ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_STELLA_DELETED_OBJECTp, NULL)));

      if (((boolean)(deletedP))) {
        return (coerceWrappedBooleanToBoolean(deletedP));
      }
      else {
        return (false);
      }
    }
  }
}

boolean LogicObject::deletedPSetter(boolean value) {
  { LogicObject* self = this;

    setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_STELLA_DELETED_OBJECTp, (value ? TRUE_WRAPPER : FALSE_WRAPPER), NULL);
    return (value);
  }
}

void LogicObject::printObject(std::ostream* stream) {
  { LogicObject* self = this;

    printTopLevelObject(self, stream);
  }
}

LogicThing* newLogicThing() {
  { LogicThing* self = NULL;

    self = new LogicThing();
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    return (self);
  }
}

Surrogate* LogicThing::primaryType() {
  { LogicThing* self = this;

    return (SGT_PROPOSITIONS_LOGIC_LOGIC_THING);
  }
}

Object* accessLogicThingSlotValue(LogicThing* self, Symbol* slotname, Object* value, boolean setvalueP) {
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

void logLogicObject(LogicObject* self) {
  if (descriptionModeP() ||
      isaP(self, SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE)) {
    return;
  }
  if (!oLOADINGREGENERABLEOBJECTSpo) {
    locallyConceivedInstances(oCONTEXTo)->push(self);
  }
}

Skolem* newSkolem() {
  { Skolem* self = NULL;

    self = new Skolem();
    self->dependentPropositionsIndex = NULL;
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->variableValueInverse = NULL;
    self->homeContext = oMODULEo;
    self->definingProposition = NULL;
    self->variableValue = NULL;
    self->skolemName = NULL;
    self->skolemType = NULL;
    logLogicObject(self);
    return (self);
  }
}

Surrogate* Skolem::primaryType() {
  { Skolem* self = this;

    return (SGT_PROPOSITIONS_LOGIC_SKOLEM);
  }
}

Object* accessSkolemSlotValue(Skolem* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PROPOSITIONS_LOGIC_SKOLEM_TYPE) {
    if (setvalueP) {
      self->skolemType = ((Surrogate*)(value));
    }
    else {
      value = self->skolemType;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_SKOLEM_NAME) {
    if (setvalueP) {
      self->skolemName = ((Symbol*)(value));
    }
    else {
      value = self->skolemName;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_VARIABLE_VALUE) {
    if (setvalueP) {
      { Skolem* object000 = self;
        Object* value000 = value;
        Object* oldValue000 = object000->variableValue;
        Object* newValue000 = updateInContext(oldValue000, value000, object000->homeContext, false);

        if (!(((boolean)(oldValue000)) &&
            (oldValue000->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
          object000->variableValue = newValue000;
        }
      }
    }
    else {
      value = ((Object*)(accessInContext(self->variableValue, self->homeContext, false)));
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_DEFINING_PROPOSITION) {
    if (setvalueP) {
      self->definingProposition = ((Proposition*)(value));
    }
    else {
      value = self->definingProposition;
    }
  }
  else {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

PatternVariable* newPatternVariable() {
  { PatternVariable* self = NULL;

    self = new PatternVariable();
    self->dependentPropositionsIndex = NULL;
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->variableValueInverse = NULL;
    self->homeContext = oMODULEo;
    self->definingProposition = NULL;
    self->variableValue = NULL;
    self->skolemType = NULL;
    self->skolemName = NULL;
    self->boundToOffset = NULL_INTEGER;
    logLogicObject(self);
    return (self);
  }
}

Surrogate* PatternVariable::primaryType() {
  { PatternVariable* self = this;

    return (SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE);
  }
}

Object* accessPatternVariableSlotValue(PatternVariable* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PROPOSITIONS_LOGIC_BOUND_TO_OFFSET) {
    if (setvalueP) {
      self->boundToOffset = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->boundToOffset);
    }
  }
  else {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

// Save space by structure-sharing zero-length variable vectors.
Vector* ZERO_VARIABLES_VECTOR = NULL;

ForwardChainingIndex* newForwardChainingIndex() {
  { ForwardChainingIndex* self = NULL;

    self = new ForwardChainingIndex();
    self->consequent = NULL;
    self->cacheId = NULL;
    self->inputBindings = NULL;
    self->queryBody = NULL;
    self->ioVariables = NULL;
    self->masterRule = NULL;
    self->forwardGoal = NULL;
    return (self);
  }
}

Surrogate* ForwardChainingIndex::primaryType() {
  { ForwardChainingIndex* self = this;

    return (SGT_PROPOSITIONS_LOGIC_FORWARD_CHAINING_INDEX);
  }
}

Object* accessForwardChainingIndexSlotValue(ForwardChainingIndex* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PROPOSITIONS_LOGIC_FORWARD_GOAL) {
    if (setvalueP) {
      self->forwardGoal = ((Proposition*)(value));
    }
    else {
      value = self->forwardGoal;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_MASTER_RULE) {
    if (setvalueP) {
      self->masterRule = ((Proposition*)(value));
    }
    else {
      value = self->masterRule;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_IO_VARIABLES) {
    if (setvalueP) {
      self->ioVariables = ((Cons*)(value));
    }
    else {
      value = self->ioVariables;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_QUERY_BODY) {
    if (setvalueP) {
      self->queryBody = ((Cons*)(value));
    }
    else {
      value = self->queryBody;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_INPUT_BINDINGS) {
    if (setvalueP) {
      self->inputBindings = ((Cons*)(value));
    }
    else {
      value = self->inputBindings;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_CACHE_ID) {
    if (setvalueP) {
      self->cacheId = ((Symbol*)(value));
    }
    else {
      value = self->cacheId;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_CONSEQUENT) {
    if (setvalueP) {
      self->consequent = ((Description*)(value));
    }
    else {
      value = self->consequent;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

boolean ForwardChainingIndex::deletedP() {
  { ForwardChainingIndex* self = this;

    return ((!((boolean)(self->masterRule))) ||
        deletedPropositionP(self->masterRule));
  }
}

Description* newDescription() {
  { Description* self = NULL;

    self = new Description();
    self->dependentPropositionsIndex = NULL;
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->variableValueInverse = NULL;
    self->homeContext = oMODULEo;
    self->queryPatterns = NULL;
    self->internalVariables = ZERO_VARIABLES_VECTOR;
    self->ioVariables = NULL;
    self->proposition = NULL;
    logLogicObject(self);
    return (self);
  }
}

Surrogate* Description::primaryType() {
  { Description* self = this;

    return (SGT_PROPOSITIONS_LOGIC_DESCRIPTION);
  }
}

Relation* Description::nativeRelation() {
  { Description* self = this;

    return (NULL);
  }
}

List* Description::forwardChainingIndices_reader() {
  { Description* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_FORWARD_CHAINING_INDICES, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

BooleanWrapper* Description::deferredContrapositivesP_reader() {
  { Description* self = this;

    { BooleanWrapper* answer = ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DEFERRED_CONTRAPOSITIVESp, NULL)));

      if (!((boolean)(answer))) {
        return (FALSE_WRAPPER);
      }
      else {
        return (answer);
      }
    }
  }
}

Object* accessDescriptionSlotValue(Description* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PROPOSITIONS_LOGIC_PROPOSITION) {
    if (setvalueP) {
      self->proposition = ((Proposition*)(value));
    }
    else {
      value = self->proposition;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_IO_VARIABLES) {
    if (setvalueP) {
      self->ioVariables = ((Vector*)(value));
    }
    else {
      value = self->ioVariables;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_INTERNAL_VARIABLES) {
    if (setvalueP) {
      self->internalVariables = ((Vector*)(value));
    }
    else {
      value = self->internalVariables;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_QUERY_PATTERNS) {
    if (setvalueP) {
      self->queryPatterns = ((KeyValueList*)(value));
    }
    else {
      value = self->queryPatterns;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_FORWARD_CHAINING_INDICES) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_FORWARD_CHAINING_INDICES, ((List*)(value)), NULL);
    }
    else {
      value = self->forwardChainingIndices_reader();
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_DEFERRED_CONTRAPOSITIVESp) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DEFERRED_CONTRAPOSITIVESp, ((BooleanWrapper*)(value)), NULL);
    }
    else {
      value = self->deferredContrapositivesP_reader();
    }
  }
  else {
    if (slotname == SYM_PROPOSITIONS_LOGIC_RELATIVE_COMPLEMENT) {
      slotname = SYM_PROPOSITIONS_LOGIC_COMPLEMENT_DESCRIPTION;
    }
    else {
    }
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

NamedDescription* newNamedDescription() {
  { NamedDescription* self = NULL;

    self = new NamedDescription();
    self->dependentPropositionsIndex = NULL;
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->variableValueInverse = NULL;
    self->homeContext = oMODULEo;
    self->queryPatterns = NULL;
    self->internalVariables = ZERO_VARIABLES_VECTOR;
    self->ioVariables = NULL;
    self->proposition = NULL;
    self->objectOriginatedPropositions = NULL;
    self->objectStringifiedSource = NULL;
    self->extension = NULL;
    self->ioVariableTypes = NULL;
    self->ioVariableNames = NULL;
    logLogicObject(self);
    return (self);
  }
}

Surrogate* NamedDescription::primaryType() {
  { NamedDescription* self = this;

    return (SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION);
  }
}

Relation* NamedDescription::nativeRelation() {
  { NamedDescription* self = this;

    return (((Relation*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_NATIVE_RELATION_BACK_POINTER, NULL))));
  }
}

void NamedDescription::nativeRelationSetter(Relation* value) {
  { NamedDescription* self = this;

    setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_NATIVE_RELATION_BACK_POINTER, value, NULL);
  }
}

Object* accessNamedDescriptionSlotValue(NamedDescription* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PROPOSITIONS_LOGIC_IO_VARIABLE_NAMES) {
    if (setvalueP) {
      self->ioVariableNames = ((List*)(value));
    }
    else {
      value = self->ioVariableNames;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_IO_VARIABLE_TYPES) {
    if (setvalueP) {
      self->ioVariableTypes = ((List*)(value));
    }
    else {
      value = self->ioVariableTypes;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_STELLA_EXTENSION) {
    if (setvalueP) {
      self->extension = ((SequenceIndex*)(value));
    }
    else {
      value = self->extension;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_OBJECT_STRINGIFIED_SOURCE) {
    if (setvalueP) {
      stringifiedSourceSetter(self, ((StringWrapper*)(value))->wrapperValue);
    }
    else {
      value = wrapString(stringifiedSource(self));
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_OBJECT_ORIGINATED_PROPOSITIONS) {
    if (setvalueP) {
      originatedPropositionsSetter(self, ((List*)(value)));
    }
    else {
      value = originatedPropositions(self);
    }
  }
  else {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

TruthValue* newTruthValue() {
  { TruthValue* self = NULL;

    self = new TruthValue();
    self->dependentPropositionsIndex = NULL;
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->variableValueInverse = NULL;
    self->homeContext = oMODULEo;
    self->matchScore = 0.0;
    self->strength = NULL;
    self->polarity = KWD_PROPOSITIONS_UNKNOWN;
    logLogicObject(self);
    return (self);
  }
}

Surrogate* TruthValue::primaryType() {
  { TruthValue* self = this;

    return (SGT_PROPOSITIONS_LOGIC_TRUTH_VALUE);
  }
}

Object* accessTruthValueSlotValue(TruthValue* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PROPOSITIONS_LOGIC_POLARITY) {
    if (setvalueP) {
      self->polarity = ((Keyword*)(value));
    }
    else {
      value = self->polarity;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_STRENGTH) {
    if (setvalueP) {
      self->strength = ((Keyword*)(value));
    }
    else {
      value = self->strength;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_MATCH_SCORE) {
    if (setvalueP) {
      self->matchScore = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->matchScore);
    }
  }
  else {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

PartialSupport* newPartialSupport() {
  { PartialSupport* self = NULL;

    self = new PartialSupport();
    self->argumentScores = NULL;
    self->id = NULL_INTEGER;
    self->score = NULL_FLOAT;
    self->axiom = NULL;
    self->fact = NULL;
    return (self);
  }
}

Surrogate* PartialSupport::primaryType() {
  { PartialSupport* self = this;

    return (SGT_PROPOSITIONS_LOGIC_PARTIAL_SUPPORT);
  }
}

Object* accessPartialSupportSlotValue(PartialSupport* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PROPOSITIONS_LOGIC_FACT) {
    if (setvalueP) {
      self->fact = ((Proposition*)(value));
    }
    else {
      value = self->fact;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_AXIOM) {
    if (setvalueP) {
      self->axiom = ((Proposition*)(value));
    }
    else {
      value = self->axiom;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_SCORE) {
    if (setvalueP) {
      self->score = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->score);
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_ID) {
    if (setvalueP) {
      self->id = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->id);
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_ARGUMENT_SCORES) {
    if (setvalueP) {
      self->argumentScores = ((Cons*)(value));
    }
    else {
      value = self->argumentScores;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

int oPARTIAL_SUPPORT_COUNTERo = 0;

Proposition* newProposition() {
  { Proposition* self = NULL;

    self = new Proposition();
    self->dynamicSlots = newKeyValueList();
    self->dependentPropositions = NIL_NON_PAGING_INDEX;
    self->operatoR = NULL;
    self->arguments = NULL;
    self->truthValue = NULL;
    self->kind = NULL;
    self->homeContext = oMODULEo;
    return (self);
  }
}

Surrogate* Proposition::primaryType() {
  { Proposition* self = this;

    return (SGT_PROPOSITIONS_LOGIC_PROPOSITION);
  }
}

BooleanWrapper* Proposition::variableTypeP_reader() {
  { Proposition* self = this;

    { BooleanWrapper* answer = ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_VARIABLE_TYPEp, NULL)));

      if (!((boolean)(answer))) {
        return (FALSE_WRAPPER);
      }
      else {
        return (answer);
      }
    }
  }
}

List* Proposition::satellitePropositions_reader() {
  { Proposition* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_SATELLITE_PROPOSITIONS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

BooleanWrapper* Proposition::unfastenedP_reader() {
  { Proposition* self = this;

    { BooleanWrapper* answer = ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_UNFASTENEDp, NULL)));

      if (!((boolean)(answer))) {
        return (FALSE_WRAPPER);
      }
      else {
        return (answer);
      }
    }
  }
}

double Proposition::weightDelta_reader() {
  { Proposition* self = this;

    { double answer = ((FloatWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_WEIGHT_DELTA, NULL_FLOAT_WRAPPER)))->wrapperValue;

      if (answer == NULL_FLOAT) {
        return (0.0);
      }
      else {
        return (answer);
      }
    }
  }
}

Cons* Proposition::support_reader() {
  { Proposition* self = this;

    { Cons* answer = ((Cons*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_SUPPORT, NULL)));

      if (!((boolean)(answer))) {
        return (NIL);
      }
      else {
        return (answer);
      }
    }
  }
}

BooleanWrapper* Proposition::badP_reader() {
  { Proposition* self = this;

    { BooleanWrapper* answer = ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_STELLA_BADp, NULL)));

      if (!((boolean)(answer))) {
        return (FALSE_WRAPPER);
      }
      else {
        return (answer);
      }
    }
  }
}

Object* accessPropositionSlotValue(Proposition* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PROPOSITIONS_LOGIC_KIND) {
    if (setvalueP) {
      self->kind = ((Keyword*)(value));
    }
    else {
      value = self->kind;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_TRUTH_VALUE) {
    if (setvalueP) {
      { Proposition* object000 = self;
        TruthValue* value000 = ((TruthValue*)(value));
        Object* oldValue000 = object000->truthValue;
        Object* newValue000 = updateInContext(oldValue000, value000, object000->homeContext, false);

        if (!(((boolean)(oldValue000)) &&
            (oldValue000->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
          object000->truthValue = newValue000;
        }
      }
    }
    else {
      value = ((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false)));
    }
  }
  else if (slotname == SYM_PROPOSITIONS_STELLA_ARGUMENTS) {
    if (setvalueP) {
      self->arguments = ((Vector*)(value));
    }
    else {
      value = self->arguments;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_STELLA_OPERATOR) {
    if (setvalueP) {
      self->operatoR = ((GeneralizedSymbol*)(value));
    }
    else {
      value = self->operatoR;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_RELATIONREF) {
    if (setvalueP) {
      self->operatoR = ((Surrogate*)(value));
    }
    else {
      value = ((Surrogate*)(self->operatoR));
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_DEPENDENT_PROPOSITIONS) {
    if (setvalueP) {
      self->dependentPropositions = ((NonPagingIndex*)(value));
    }
    else {
      value = self->dependentPropositions;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_VARIABLE_TYPEp) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_VARIABLE_TYPEp, ((BooleanWrapper*)(value)), NULL);
    }
    else {
      value = self->variableTypeP_reader();
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_SATELLITE_PROPOSITIONS) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_SATELLITE_PROPOSITIONS, ((List*)(value)), NULL);
    }
    else {
      value = self->satellitePropositions_reader();
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_PROPOSITION_ORIGINATED_PROPOSITIONS) {
    if (setvalueP) {
      originatedPropositionsSetter(self, ((List*)(value)));
    }
    else {
      value = originatedPropositions(self);
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_PROPOSITION_STRINGIFIED_SOURCE) {
    if (setvalueP) {
      stringifiedSourceSetter(self, ((StringWrapper*)(value))->wrapperValue);
    }
    else {
      value = wrapString(stringifiedSource(self));
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_UNFASTENEDp) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_UNFASTENEDp, ((BooleanWrapper*)(value)), NULL);
    }
    else {
      value = self->unfastenedP_reader();
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_WEIGHT_DELTA) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_WEIGHT_DELTA, wrapFloat(((FloatWrapper*)(value))->wrapperValue), NULL_FLOAT_WRAPPER);
    }
    else {
      value = wrapFloat(self->weightDelta_reader());
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_SUPPORT) {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_SUPPORT, ((Cons*)(value)), NULL);
    }
    else {
      value = self->support_reader();
    }
  }
  else {
    if (slotname == SYM_PROPOSITIONS_LOGIC_PROPOSITION_NEURAL_NETWORK) {
      slotname = SYM_PROPOSITIONS_LOGIC_NEURAL_NET;
    }
    else if (slotname == SYM_PROPOSITIONS_LOGIC_NEURAL_NETWORK) {
      slotname = SYM_PROPOSITIONS_LOGIC_NEURAL_NET;
    }
    else {
    }
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

void Proposition::printObject(std::ostream* stream) {
  { Proposition* self = this;

    printTopLevelObject(self, stream);
  }
}

QuantityLogicWrapper* newQuantityLogicWrapper(Quantity* wrapperValue) {
  { QuantityLogicWrapper* self = NULL;

    self = new QuantityLogicWrapper();
    self->wrapperValue = wrapperValue;
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->functionTerm = NULL;
    return (self);
  }
}

Surrogate* QuantityLogicWrapper::primaryType() {
  { QuantityLogicWrapper* self = this;

    return (SGT_PROPOSITIONS_LOGIC_QUANTITY_LOGIC_WRAPPER);
  }
}

Object* accessQuantityLogicWrapperSlotValue(QuantityLogicWrapper* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PROPOSITIONS_STELLA_WRAPPER_VALUE) {
    if (setvalueP) {
      self->wrapperValue = ((Quantity*)(value));
    }
    else {
      value = self->wrapperValue;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_FUNCTION_TERM) {
    if (setvalueP) {
      self->functionTerm = ((Cons*)(value));
    }
    else {
      value = self->functionTerm;
    }
  }
  else {
    if (setvalueP) {
      setDynamicSlotValue(self->dynamicSlots, slotname, value, NULL);
    }
    else {
      value = self->dynamicSlots->lookup(slotname);
    }
  }
  return (value);
}

void QuantityLogicWrapper::printObject(std::ostream* stream) {
  { QuantityLogicWrapper* self = this;

    if (oPRINTREADABLYpo) {
      *(stream) << self->wrapperValue;
    }
    else {
      *(stream) << "|Q|" << self->wrapperValue;
    }
  }
}

IntegerLogicWrapper* newIntegerLogicWrapper(int wrapperValue) {
  { IntegerLogicWrapper* self = NULL;

    self = new IntegerLogicWrapper();
    self->wrapperValue = wrapperValue;
    self->dependentPropositionsIndex = NULL;
    return (self);
  }
}

Surrogate* IntegerLogicWrapper::primaryType() {
  { IntegerLogicWrapper* self = this;

    return (SGT_PROPOSITIONS_LOGIC_INTEGER_LOGIC_WRAPPER);
  }
}

void IntegerLogicWrapper::printObject(std::ostream* stream) {
  { IntegerLogicWrapper* self = this;

    if (oPRINTREADABLYpo) {
      *(stream) << self->wrapperValue;
    }
    else {
      *(stream) << "|W|" << self->wrapperValue;
    }
  }
}

FloatLogicWrapper* newFloatLogicWrapper(double wrapperValue) {
  { FloatLogicWrapper* self = NULL;

    self = new FloatLogicWrapper();
    self->wrapperValue = wrapperValue;
    self->dependentPropositionsIndex = NULL;
    return (self);
  }
}

Surrogate* FloatLogicWrapper::primaryType() {
  { FloatLogicWrapper* self = this;

    return (SGT_PROPOSITIONS_LOGIC_FLOAT_LOGIC_WRAPPER);
  }
}

void FloatLogicWrapper::printObject(std::ostream* stream) {
  { FloatLogicWrapper* self = this;

    if (oPRINTREADABLYpo) {
      *(stream) << self->wrapperValue;
    }
    else {
      *(stream) << "|W|" << self->wrapperValue;
    }
  }
}

StringLogicWrapper* newStringLogicWrapper(const char* wrapperValue) {
  { StringLogicWrapper* self = NULL;

    self = new StringLogicWrapper();
    self->wrapperValue = wrapperValue;
    self->dependentPropositionsIndex = NULL;
    return (self);
  }
}

Surrogate* StringLogicWrapper::primaryType() {
  { StringLogicWrapper* self = this;

    return (SGT_PROPOSITIONS_LOGIC_STRING_LOGIC_WRAPPER);
  }
}

void StringLogicWrapper::printObject(std::ostream* stream) {
  { StringLogicWrapper* self = this;

    { const char* value = self->wrapperValue;

      if (oPRINTREADABLYpo) {
        printStringReadably(value, stream);
      }
      else {
        if (value != NULL) {
          *(stream) << "|W|" << "\"" << value << "\"";
        }
        else {
          *(stream) << "|W|" << "NULL-STRING";
        }
      }
    }
  }
}

const char* stringifiedSource(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
      { Object* self000 = self;
        NamedDescription* self = ((NamedDescription*)(self000));

        return (self->objectStringifiedSource);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* self001 = self;
        LogicObject* self = ((LogicObject*)(self001));

        return (((StringWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_OBJECT_STRINGIFIED_SOURCE, NULL_STRING_WRAPPER)))->wrapperValue);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
      { Object* self002 = self;
        Proposition* self = ((Proposition*)(self002));

        return (((StringWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_PROPOSITION_STRINGIFIED_SOURCE, NULL_STRING_WRAPPER)))->wrapperValue);
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

const char* stringifiedSourceSetter(Object* self, const char* value) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
      { Object* self000 = self;
        NamedDescription* self = ((NamedDescription*)(self000));

        self->objectStringifiedSource = value;
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* self001 = self;
        LogicObject* self = ((LogicObject*)(self001));

        setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_OBJECT_STRINGIFIED_SOURCE, wrapString(value), NULL_STRING_WRAPPER);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
      { Object* self002 = self;
        Proposition* self = ((Proposition*)(self002));

        setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_PROPOSITION_STRINGIFIED_SOURCE, wrapString(value), NULL_STRING_WRAPPER);
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
  return (value);
}

List* originatedPropositions(Object* self) {
  { Object* value = NULL;

    { Surrogate* testValue000 = safePrimaryType(self);

      if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
        { Object* self000 = self;
          NamedDescription* self = ((NamedDescription*)(self000));

          value = self->objectOriginatedPropositions;
        }
      }
      else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
        { Object* self001 = self;
          LogicObject* self = ((LogicObject*)(self001));

          value = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_OBJECT_ORIGINATED_PROPOSITIONS, NULL)));
        }
      }
      else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
        { Object* self002 = self;
          Proposition* self = ((Proposition*)(self002));

          value = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_PROPOSITION_ORIGINATED_PROPOSITIONS, NULL)));
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    if (!((boolean)(value))) {
      return (NIL_LIST);
    }
    else {
      return (((List*)(value)));
    }
  }
}

List* originatedPropositionsSetter(Object* self, List* value) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
      { Object* self000 = self;
        NamedDescription* self = ((NamedDescription*)(self000));

        self->objectOriginatedPropositions = value;
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* self001 = self;
        LogicObject* self = ((LogicObject*)(self001));

        setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_OBJECT_ORIGINATED_PROPOSITIONS, value, NULL);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
      { Object* self002 = self;
        Proposition* self = ((Proposition*)(self002));

        setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_PROPOSITION_ORIGINATED_PROPOSITIONS, value, NULL);
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
  return (value);
}

// Maps names of KIF operators to relational surrogates.
PropertyList* oOPERATOR_NAME_TO_SURROGATE_TABLEo = NULL;

Proposition* createProposition(Symbol* kind, int argumentcount) {
  enforceCodeOnly();
  { Proposition* proposition = newProposition();

    proposition->arguments = stella::newVector(argumentcount);
    proposition->kind = internKeyword(kind->symbolName);
    if ((kind == SYM_PROPOSITIONS_STELLA_FUNCTION) ||
        ((kind == SYM_PROPOSITIONS_STELLA_PREDICATE) ||
         (kind == SYM_PROPOSITIONS_STELLA_ISA))) {
    }
    else {
      proposition->operatoR = ((Surrogate*)(oOPERATOR_NAME_TO_SURROGATE_TABLEo->lookup(proposition->kind)));
    }
    if (descriptionModeP()) {
      setDynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTIVEp, TRUE_WRAPPER, FALSE_WRAPPER);
    }
    setDynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_UNFASTENEDp, TRUE_WRAPPER, NULL);
    return (proposition);
  }
}

void enforceCodeOnly() {
  if (((BooleanWrapper*)(dynamicSlotValue(oMODULEo->dynamicSlots, SYM_PROPOSITIONS_STELLA_CODE_ONLYp, FALSE_WRAPPER)))->wrapperValue) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "ERROR: " << "Can't create a relation, instance or proposition in module:" << std::endl << "       " << "`" << oMODULEo->moduleName << "'" << std::endl << "    because it is marked as 'code-only?'" << std::endl << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
      }
      throw *newPropositionError(stream000->theStringReader());
    }
  }
}

Surrogate* getPropositionBaseOperator(Proposition* prop) {
  if (prop->kind == KWD_PROPOSITIONS_EQUIVALENT) {
    { Object* term1 = (prop->arguments->theArray)[0];
      Object* term2 = (prop->arguments->theArray)[1];

      if (functionOutputSkolemP(term1)) {
        return (((Surrogate*)(((Skolem*)(term1))->definingProposition->operatoR)));
      }
      else if (functionOutputSkolemP(term2)) {
        return (((Surrogate*)(((Skolem*)(term2))->definingProposition->operatoR)));
      }
      else {
        return (((Surrogate*)(prop->operatoR)));
      }
    }
  }
  return (((Surrogate*)(prop->operatoR)));
}

LogicException* newLogicException(const char* message) {
  { LogicException* self = NULL;

    self = new LogicException(message);
    return (self);
  }
}

PropositionError* newPropositionError(const char* message) {
  { PropositionError* self = NULL;

    self = new PropositionError(message);
    return (self);
  }
}

ParsingError* newParsingError(const char* message) {
  { ParsingError* self = NULL;

    self = new ParsingError(message);
    return (self);
  }
}

Clash* newClash(const char* message) {
  { Clash* self = NULL;

    self = new Clash(message);
    self->context = NULL;
    self->proposition = NULL;
    return (self);
  }
}

TruthValueClash* newTruthValueClash(const char* message) {
  { TruthValueClash* self = NULL;

    self = new TruthValueClash(message);
    self->context = NULL;
    self->proposition = NULL;
    return (self);
  }
}

IntervalClash* newIntervalClash(const char* message) {
  { IntervalClash* self = NULL;

    self = new IntervalClash(message);
    self->context = NULL;
    self->proposition = NULL;
    self->strictUpperBoundP = false;
    self->strictLowerBoundP = false;
    self->upperBound = NULL;
    self->lowerBound = NULL;
    self->intervalMember = NULL;
    return (self);
  }
}

VariableValueClash* newVariableValueClash(const char* message) {
  { VariableValueClash* self = NULL;

    self = new VariableValueClash(message);
    self->context = NULL;
    self->proposition = NULL;
    self->value2 = NULL;
    self->value1 = NULL;
    self->skolem = NULL;
    return (self);
  }
}

UnificationClash* newUnificationClash(const char* message) {
  { UnificationClash* self = NULL;

    self = new UnificationClash(message);
    self->context = NULL;
    self->proposition = NULL;
    self->value2 = NULL;
    self->value1 = NULL;
    return (self);
  }
}

FailException* newFailException(const char* message) {
  { FailException* self = NULL;

    self = new FailException(message);
    return (self);
  }
}

QueryThreadLimitViolation* newQueryThreadLimitViolation(const char* message) {
  { QueryThreadLimitViolation* self = NULL;

    self = new QueryThreadLimitViolation(message);
    return (self);
  }
}

ExceptionRecord* newExceptionRecord() {
  { ExceptionRecord* self = NULL;

    self = new ExceptionRecord();
    self->module = NULL;
    self->context = NULL;
    self->exception = NULL;
    return (self);
  }
}

Surrogate* ExceptionRecord::primaryType() {
  { ExceptionRecord* self = this;

    return (SGT_PROPOSITIONS_LOGIC_EXCEPTION_RECORD);
  }
}

Object* accessExceptionRecordSlotValue(ExceptionRecord* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PROPOSITIONS_STELLA_CONTEXT) {
    if (setvalueP) {
      self->context = ((Context*)(value));
    }
    else {
      value = self->context;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_STELLA_MODULE) {
    if (setvalueP) {
      self->module = ((Module*)(value));
    }
    else {
      value = self->module;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

Module* oLOGIC_MODULEo = NULL;

Module* oPL_KERNEL_MODULEo = NULL;

boolean logicModuleP(Module* self) {
  // Return TRUE if 'self' is a logic module, implying
  // that relations defined within it define a knowledge base.  A module
  // is a logic module iff it inherits the module 'PL-KERNEL'.
  { boolean testValue000 = false;

    if (self == oPL_KERNEL_MODULEo) {
      testValue000 = true;
    }
    else {
      {
        { boolean foundP000 = false;

          { Module* m = NULL;
            Cons* iter000 = self->parentModules->theConsList;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              m = ((Module*)(iter000->value));
              if (logicModuleP(m)) {
                foundP000 = true;
                break;
              }
            }
          }
          testValue000 = foundP000;
        }
        if (!testValue000) {
          { boolean foundP001 = false;

            { Module* m = NULL;
              Cons* iter001 = self->uses->theConsList;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                m = ((Module*)(iter001->value));
                if (logicModuleP(m)) {
                  foundP001 = true;
                  break;
                }
              }
            }
            testValue000 = foundP001;
          }
        }
      }
    }
    { boolean value000 = testValue000;

      return (value000);
    }
  }
}

SequenceIndex* locallyConceivedPropositions(Module* self) {
  { SequenceIndex* propositions = ((SequenceIndex*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_LOCALLY_CONCEIVED_PROPOSITIONS_INTERNAL, NULL)));

    if (!((boolean)(propositions))) {
      propositions = createSequenceIndex(KWD_PROPOSITIONS_PAGING, cons(KWD_PROPOSITIONS_CONTEXT_PROPOSITIONS, cons(((!((boolean)(NIL))) ? NIL : NIL), cons(self, NIL))));
      setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_LOCALLY_CONCEIVED_PROPOSITIONS_INTERNAL, propositions, NULL);
    }
    return (propositions);
  }
}

void locallyConceivedPropositionsSetter(Module* self, SequenceIndex* value) {
  setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_LOCALLY_CONCEIVED_PROPOSITIONS_INTERNAL, value, NULL);
}

SequenceIndex* locallyConceivedInstances(Context* self) {
  { SequenceIndex* instances = ((SequenceIndex*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_LOCALLY_CONCEIVED_INSTANCES_INTERNAL, NULL)));

    if (!((boolean)(instances))) {
      instances = createSequenceIndex(KWD_PROPOSITIONS_PAGING, cons(KWD_PROPOSITIONS_CONTEXT_INSTANCES, cons(((!((boolean)(NIL))) ? NIL : NIL), cons(self, NIL))));
      setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_LOCALLY_CONCEIVED_INSTANCES_INTERNAL, instances, NULL);
    }
    return (instances);
  }
}

void locallyConceivedInstancesSetter(Context* self, SequenceIndex* value) {
  setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_LOCALLY_CONCEIVED_INSTANCES_INTERNAL, value, NULL);
}

// The NOW time stamp is incremented whenever a series
// of one or more updates is followed by a query.
int oNOW_TIMESTAMPo = 0;

void incrementNowTimestamp() {
  oNOW_TIMESTAMPo = oNOW_TIMESTAMPo + 1;
}

int getNowTimestamp() {
  return (oNOW_TIMESTAMPo);
}

// Records whether the last KB access was a query or
// an update.  Used to determine when to increment the NOW time stamp
// counter.
Keyword* oLAST_KB_ACTIONo = NULL;

void updateNowTimestamp(Keyword* kbaction) {
  if (kbaction == oLAST_KB_ACTIONo) {
    return;
  }
  if (kbaction == KWD_PROPOSITIONS_UPDATE_PROPOSITION) {
    if (descriptionModeP() ||
        ((!(oMODULEo == oCONTEXTo)) ||
         oINVISIBLEASSERTIONpo)) {
      return;
    }
    incrementNowTimestamp();
  }
  else if (kbaction == KWD_PROPOSITIONS_EXECUTE_QUERY) {
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << kbaction << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  oLAST_KB_ACTIONo = kbaction;
}

// The undefined individual.  Denotes the non-existence of
// an individual in whatever slot it occupies.
LogicObject* BOTTOM = NULL;

boolean bottomP(Object* self) {
  // Return TRUE if 'self' is the undefined individual BOTTOM.
  return (self == BOTTOM);
}

boolean subrelationOfP(NamedDescription* desc1, NamedDescription* desc2) {
  { 
    BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
    return (collectionImpliesCollectionP(desc1, desc2));
  }
}

boolean logicalSubtypeOfP(Surrogate* type1, Surrogate* type2) {
  if (type1 == type2) {
    return (true);
  }
  else {
    { NamedDescription* desc1 = getDescription(type1);
      NamedDescription* desc2 = getDescription(type2);

      if ((!((boolean)(desc1))) ||
          (!((boolean)(desc2)))) {
        return (false);
      }
      return (subrelationOfP(desc1, desc2));
    }
  }
}

boolean logicalSubtypeOfLiteralP(Surrogate* type) {
  { NamedDescription* desc = surrogateToDescription(type);
    NamedDescription* literalclass = surrogateToDescription(SGT_PROPOSITIONS_STELLA_LITERAL);
    Cons* literalsubs = NIL;

    if (!((boolean)(desc))) {
      return (false);
    }
    else if (desc == literalclass) {
      return (true);
    }
    else {
      { 
        BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getPropertyTestContext());
        { MemoizationTable* memoTable000 = NULL;
          Cons* memoizedEntry000 = NULL;
          Object* memoizedValue000 = NULL;

          if (oMEMOIZATION_ENABLEDpo) {
            memoTable000 = ((MemoizationTable*)(SGT_PROPOSITIONS_LOGIC_F_LOGICAL_SUBTYPE_OF_LITERALp_MEMO_TABLE_000->surrogateValue));
            if (!((boolean)(memoTable000))) {
              initializeMemoizationTable(SGT_PROPOSITIONS_LOGIC_F_LOGICAL_SUBTYPE_OF_LITERALp_MEMO_TABLE_000, "(:MAX-VALUES 10 :TIMESTAMPS (:META-KB-UPDATE))");
              memoTable000 = ((MemoizationTable*)(SGT_PROPOSITIONS_LOGIC_F_LOGICAL_SUBTYPE_OF_LITERALp_MEMO_TABLE_000->surrogateValue));
            }
            memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), oCONTEXTo, MEMOIZED_NULL_VALUE, NULL, NULL, -1);
            memoizedValue000 = memoizedEntry000->value;
          }
          if (((boolean)(memoizedValue000))) {
            if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
              memoizedValue000 = NULL;
            }
          }
          else {
            memoizedValue000 = allSubcollections(literalclass)->consify();
            if (oMEMOIZATION_ENABLEDpo) {
              memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
            }
          }
          literalsubs = ((Cons*)(memoizedValue000));
        }
        if (literalsubs->membP(desc)) {
          return (true);
        }
      }
    }
    return (false);
  }
}

boolean literalTypeP(Surrogate* type) {
  { Object* value = type->surrogateValue;

    return (isaP(value, SGT_PROPOSITIONS_STELLA_CLASS) &&
        (subtypeOfP(type, SGT_PROPOSITIONS_STELLA_LITERAL) ||
         subtypeOfP(type, SGT_PROPOSITIONS_STELLA_LITERAL_WRAPPER)));
  }
}

boolean booleanTypeP(Surrogate* self) {
  return ((self == SGT_PROPOSITIONS_STELLA_BOOLEAN) ||
      (self == SGT_PROPOSITIONS_STELLA_BOOLEAN_WRAPPER));
}

boolean propositionTypeP(Surrogate* self) {
  return (self == SGT_PROPOSITIONS_LOGIC_PROPOSITION);
}

boolean classDescriptionP(NamedDescription* self) {
  return (classP(self));
}

boolean functionDescriptionP(NamedDescription* self) {
  return (functionP(self));
}

boolean variableArityP(Description* self) {
  return (testPropertyP(self, SGT_PROPOSITIONS_PL_KERNEL_KB_VARIABLE_ARITY));
}

int NamedDescription::arity() {
  { NamedDescription* self = this;

    if (variableArityP(self)) {
      return (-1);
    }
    else {
      return (self->ioVariableTypes->length());
    }
  }
}

int Description::arity() {
  { Description* self = this;

    return (self->ioVariables->length());
  }
}

boolean monadicP(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) {
      { Object* self000 = self;
        Description* self = ((Description*)(self000));

        return (self->arity() == 1);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_COLLECTION)) {
      { Object* self001 = self;
        Collection* self = ((Collection*)(self001));

        return (true);
      }
    }
    else {
      return (false);
    }
  }
}

boolean computedRelationP(NamedDescription* description) {
  return ((((boolean)(description->nativeRelation())) &&
      (!description->nativeRelation()->abstractP)) ||
      ((boolean)(accessBinaryValue(description, SGT_PROPOSITIONS_PL_KERNEL_KB_RELATION_COMPUTATION))));
}

Object* lastArgument(Proposition* proposition) {
  return ((proposition->arguments->theArray)[(proposition->arguments->length() - 1)]);
}

Surrogate* objectSurrogate(Object* self) {
  // Return the surrogate naming the object `self', which
  // may be a Stella class that is used in PowerLoom as well as
  // a more normal powerloom object.
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* self000 = self;
        LogicObject* self = ((LogicObject*)(self000));

        return (self->surrogateValueInverse);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
      { Object* self001 = self;
        Proposition* self = ((Proposition*)(self001));

        return (((Surrogate*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_STELLA_SURROGATE_VALUE_INVERSE, NULL))));
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_THING)) {
      { Object* self002 = self;
        Thing* self = ((Thing*)(self002));

        return (self->surrogateValueInverse);
      }
    }
    else if (subtypeOfClassP(testValue000)) {
      { Object* self003 = self;
        Class* self = ((Class*)(self003));

        return (self->classType);
      }
    }
    else {
      return (NULL);
    }
  }
}

Surrogate* objectSurrogateSetter(Object* self, Surrogate* name) {
  // Return the name of the logic object `self' to `name'.
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* self000 = self;
        LogicObject* self = ((LogicObject*)(self000));

        self->surrogateValueInverse = name;
        return (name);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
      { Object* self001 = self;
        Proposition* self = ((Proposition*)(self001));

        setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_STELLA_SURROGATE_VALUE_INVERSE, name, NULL);
        return (name);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_THING)) {
      { Object* self002 = self;
        Thing* self = ((Thing*)(self002));

        self->surrogateValueInverse = name;
        return (name);
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

Symbol* objectName(Object* self) {
  // Return the name symbol for the logic object `self'.
  { Surrogate* surrogate = objectSurrogate(self);

    if (((boolean)(surrogate))) {
      return (internSymbolInModule(surrogate->symbolName, ((Module*)(surrogate->homeContext)), true));
    }
    else {
      return (NULL);
    }
  }
}

const char* objectNameString(Object* self) {
  // Return the name string for the logic object `self'.
  { Surrogate* surrogate = objectSurrogate(self);

    if (((boolean)(surrogate))) {
      return (surrogate->symbolName);
    }
    else {
      return (NULL);
    }
  }
}

const char* objectStringName(Object* self) {
  return (objectNameString(self));
}

// Indicates the context for evaluating a proposition.  One
// of :DESCRIPTION, :INTENSIONAL-ASSERTION, or :EXTENSIONAL-ASSERTION.
DEFINE_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword* , NULL);

boolean descriptionModeP() {
  return (oEVALUATIONMODEo == KWD_PROPOSITIONS_DESCRIPTION);
}

// When enabled, slot-value assertions can be retracted
// by later conflicting assertions.
DEFINE_STELLA_SPECIAL(oCLIPPINGENABLEDpo, boolean , true);

// When enabled, blocks normalizations that significantly
// change the behavior of inference rules.
DEFINE_STELLA_SPECIAL(oNATURALDEDUCTIONMODEpo, boolean , true);

boolean naturalDeductionModeP() {
  // True if normalization is governed by natural
  // deduction semantics.
  return (oNATURALDEDUCTIONMODEpo);
}

// Signals that we are performing search across multiple
// contexts.  Used to disable retraction from collections, since that increases
// the overhead of the context mechanism.
boolean oCONTEXT_DEPENDENT_SEARCH_MODEpo = false;

boolean contextDependentSearchModeP() {
  return (oCONTEXT_DEPENDENT_SEARCH_MODEpo);
}

void logNewlyConceivedProposition(Module* self, Proposition* proposition) {
  { boolean testValue000 = false;

    { boolean foundP000 = false;

      { Object* arg = NULL;
        Vector* vector000 = proposition->arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          arg = (vector000->theArray)[index000];
          if (isaP(arg, SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE)) {
            foundP000 = true;
            break;
          }
        }
      }
      testValue000 = foundP000;
    }
    if (testValue000) {
      testValue000 = oPOWERLOOM_EXECUTION_MODEo == KWD_PROPOSITIONS_DEVELOPMENT;
    }
    if (testValue000) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(STANDARD_WARNING->nativeStream) << "WARNING: " << "LOGGED QUESTIONABLE CONCEPTION: " << std::endl << "   " << proposition << std::endl;
        helpSignalPropositionError(STANDARD_WARNING, KWD_PROPOSITIONS_WARNING);
      }
    }
  }
  locallyConceivedPropositions(self)->insert(proposition);
}

void clipOrClashWithOldPredicateValue(Proposition* proposition) {
  { Vector* arguments = proposition->arguments;
    int countminustwo = arguments->length() - 2;

    { Proposition* p = NULL;
      Iterator* iter000 = allTrueDependentPropositions((arguments->theArray)[0], ((Surrogate*)(proposition->operatoR)), false);

      for (; iter000->nextP(); ) {
        p = ((Proposition*)(iter000->value));
        { boolean alwaysP000 = true;

          { int i = NULL_INTEGER;
            int iter001 = 1;
            int upperBound000 = countminustwo;
            boolean unboundedP000 = upperBound000 == NULL_INTEGER;

            for  (; unboundedP000 ||
                      (iter001 <= upperBound000); 
                  iter001 = iter001 + 1) {
              i = iter001;
              if (!eqlP(valueOf((arguments->theArray)[i]), valueOf((p->arguments->theArray)[i]))) {
                alwaysP000 = false;
                break;
              }
            }
          }
          if (alwaysP000) {
            if (eqlP(valueOf((p->arguments->theArray)[(p->arguments->length() - 1)]), valueOf(arguments->last()))) {
            }
            else if (oCLIPPINGENABLEDpo &&
                worldStateP(oCONTEXTo)) {
              deassignTruthValue(p, KWD_PROPOSITIONS_RETRACT_TRUE);
            }
            else {
              equateValues(proposition, valueOf((p->arguments->theArray)[(p->arguments->length() - 1)]), valueOf(arguments->last()));
            }
          }
        }
      }
    }
  }
}

void runUpdateEquivalencePropositionDemon(Proposition* proposition, Keyword* updatemode) {
  { Object* term1 = (proposition->arguments->theArray)[0];
    Object* term2 = (proposition->arguments->theArray)[1];
    NamedDescription* description = (functionOutputSkolemP(term1) ? getDescription(((Surrogate*)(((Skolem*)(term1))->definingProposition->operatoR))) : ((functionOutputSkolemP(term2) ? getDescription(((Surrogate*)(((Skolem*)(term2))->definingProposition->operatoR))) : ((NamedDescription*)(NULL)))));
    Object* demoncomputation = (((boolean)(description)) ? accessBinaryValue(description, SGT_PROPOSITIONS_PL_KERNEL_KB_UPDATE_PROPOSITION_DEMON) : ((Object*)(NULL)));

    if (((boolean)(demoncomputation))) {
      { cpp_function_code functioncode = functionCodeFromProcedure(((ComputedProcedure*)(demoncomputation)));

        if (functioncode != NULL) {
          ((void  (*) (Proposition*, Keyword*))functioncode)(proposition, updatemode);
        }
      }
    }
  }
}

void helpRunUpdatePropositionDemon(Proposition* proposition, Keyword* updatemode) {
  { NamedDescription* description = getDescription(((Surrogate*)(proposition->operatoR)));
    Object* demoncomputation = (((boolean)(description)) ? accessBinaryValue(description, SGT_PROPOSITIONS_PL_KERNEL_KB_UPDATE_PROPOSITION_DEMON) : ((Object*)(NULL)));

    if (((boolean)(demoncomputation))) {
      { cpp_function_code functioncode = functionCodeFromProcedure(((ComputedProcedure*)(demoncomputation)));

        if (functioncode != NULL) {
          ((void  (*) (Proposition*, Keyword*))functioncode)(proposition, updatemode);
        }
      }
    }
  }
}

void runUpdatePropositionDemon(Proposition* proposition, Keyword* updatemode) {
  if (((boolean)(((ObjectStore*)(dynamicSlotValue(oMODULEo->dynamicSlots, SYM_PROPOSITIONS_LOGIC_OBJECT_STORE, NULL)))))) {
    ((ObjectStore*)(dynamicSlotValue(oMODULEo->dynamicSlots, SYM_PROPOSITIONS_LOGIC_OBJECT_STORE, NULL)))->updatePropositionInStore(proposition, updatemode);
  }
  if (proposition->kind == KWD_PROPOSITIONS_EQUIVALENT) {
    runUpdateEquivalencePropositionDemon(proposition, updatemode);
  }
  else {
    helpRunUpdatePropositionDemon(proposition, updatemode);
  }
}

void runTruthChangeDemon(Proposition* proposition, Surrogate* truthchangerelation) {
  { NamedDescription* description = getDescription(((Surrogate*)(proposition->operatoR)));
    Object* demoncomputation = (((boolean)(description)) ? accessBinaryValue(description, truthchangerelation) : ((Object*)(NULL)));

    if (((boolean)(demoncomputation))) {
      { cpp_function_code functioncode = functionCodeFromProcedure(((ComputedProcedure*)(demoncomputation)));

        if (functioncode != NULL) {
          ((void  (*) (Proposition*))functioncode)(proposition);
        }
      }
    }
  }
}

void runGoesTrueDemons(Proposition* proposition) {
  { Keyword* testValue000 = proposition->kind;

    if ((testValue000 == KWD_PROPOSITIONS_FUNCTION) ||
        (testValue000 == KWD_PROPOSITIONS_ISA)) {
      runTruthChangeDemon(proposition, SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_TRUE_DEMON);
    }
    else if (testValue000 == KWD_PROPOSITIONS_PREDICATE) {
      { NamedDescription* description = getDescription(((Surrogate*)(proposition->operatoR)));

        if (singleValuedTermP(description)) {
          clipOrClashWithOldPredicateValue(proposition);
        }
      }
      runTruthChangeDemon(proposition, SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_TRUE_DEMON);
    }
    else if (testValue000 == KWD_PROPOSITIONS_IMPLIES) {
      reviseEquivalences(proposition, true);
      if (oMODULEo == oCONTEXTo) {
        bumpInferableTimestamp();
      }
      flushInferableDirectSubdescriptionsCache(proposition);
    }
    else if (testValue000 == KWD_PROPOSITIONS_FORALL) {
      if (proposition->satellitePropositions_reader() == NIL_LIST) {
        deriveSatelliteRules(proposition);
      }
      bumpInferableTimestamp();
    }
    else {
    }
  }
  return;
}

void runGoesFalseDemons(Proposition* proposition) {
  { Keyword* testValue000 = proposition->kind;

    if ((testValue000 == KWD_PROPOSITIONS_FUNCTION) ||
        ((testValue000 == KWD_PROPOSITIONS_ISA) ||
         (testValue000 == KWD_PROPOSITIONS_PREDICATE))) {
      runTruthChangeDemon(proposition, SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_FALSE_DEMON);
    }
    else {
    }
  }
  return;
}

void runGoesUnknownDemons(Proposition* proposition) {
  { Keyword* testValue000 = proposition->kind;

    if (testValue000 == KWD_PROPOSITIONS_ISA) {
      { Object* argument = (proposition->arguments->theArray)[0];

        if (subtypeOfP(safePrimaryType(argument), SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
          { Object* argument000 = argument;
            Skolem* argument = ((Skolem*)(argument000));

            { Surrogate* skolemtype = argument->skolemType;

              if ((skolemtype == ((Surrogate*)(proposition->operatoR))) &&
                  (!(skolemtype == SGT_PROPOSITIONS_STELLA_THING))) {
                std::cout << "Can't retract skolem type of " << "`" << argument << "'" << " equaling " << "`" << skolemtype->symbolName << "'" << "." << std::endl << std::endl;
              }
            }
          }
        }
        else {
        }
      }
      runTruthChangeDemon(proposition, SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_UNKNOWN_DEMON);
    }
    else if ((testValue000 == KWD_PROPOSITIONS_PREDICATE) ||
        (testValue000 == KWD_PROPOSITIONS_FUNCTION)) {
      runTruthChangeDemon(proposition, SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_UNKNOWN_DEMON);
    }
    else if (testValue000 == KWD_PROPOSITIONS_IMPLIES) {
      dropTaxonomyImpliesSubsumesLink(((Description*)((proposition->arguments->theArray)[0])), ((Description*)((proposition->arguments->theArray)[1])));
      reviseEquivalences(proposition, false);
      { Proposition* p = ((Proposition*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_MASTER_PROPOSITION, NULL)));

        if (((boolean)(p)) &&
            trueP(p)) {
          deassignTruthValue(p, KWD_PROPOSITIONS_RETRACT_TRUE);
        }
      }
    }
    else if (testValue000 == KWD_PROPOSITIONS_FORALL) {
      { Proposition* p = NULL;
        Cons* iter000 = proposition->satellitePropositions_reader()->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          p = ((Proposition*)(iter000->value));
          deassignTruthValue(p, KWD_PROPOSITIONS_RETRACT_TRUE);
        }
      }
    }
    else {
    }
  }
  return;
}

void updateLinksAndTimestamps(Proposition* proposition, Keyword* updatemode) {
  if (!((boolean)(proposition))) {
    return;
  }
  updateNowTimestamp(KWD_PROPOSITIONS_UPDATE_PROPOSITION);
  if ((updatemode == KWD_PROPOSITIONS_ASSERT_TRUE) ||
      (updatemode == KWD_PROPOSITIONS_PRESUME_TRUE)) {
    runGoesTrueDemons(proposition);
  }
  else if ((updatemode == KWD_PROPOSITIONS_ASSERT_FALSE) ||
      (updatemode == KWD_PROPOSITIONS_PRESUME_FALSE)) {
    runGoesFalseDemons(proposition);
  }
  else if (updatemode == KWD_PROPOSITIONS_RETRACT_TRUE) {
    runGoesUnknownDemons(proposition);
  }
  else if (updatemode == KWD_PROPOSITIONS_RETRACT_FALSE) {
    runGoesUnknownDemons(proposition);
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << updatemode << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void assignTruthValue(Proposition* self, Object* truthvalue) {
  { TruthValue* oldtruthvalue = ((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false)));
    TruthValue* newtruthvalue = NULL;

    if (truthvalue == TRUE_WRAPPER) {
      newtruthvalue = TRUE_TRUTH_VALUE;
    }
    else if (truthvalue == FALSE_WRAPPER) {
      newtruthvalue = FALSE_TRUTH_VALUE;
    }
    else {
      newtruthvalue = ((TruthValue*)(truthvalue));
    }
    if (oldtruthvalue == newtruthvalue) {
    }
    else if (((boolean)(oldtruthvalue))) {
      if ((self == TRUE_PROPOSITION) ||
          (self == FALSE_PROPOSITION)) {
        signalTruthValueClash(self);
      }
      else if (oldtruthvalue == INCONSISTENT_TRUTH_VALUE) {
      }
      else if (newtruthvalue == TRUE_TRUTH_VALUE) {
        if (oldtruthvalue == DEFAULT_TRUE_TRUTH_VALUE) {
          { Proposition* object000 = self;
            TruthValue* value000 = NULL;
            Object* oldValue001 = object000->truthValue;
            Object* newValue000 = updateInContext(oldValue001, value000, object000->homeContext, false);

            if (!(((boolean)(oldValue001)) &&
                (oldValue001->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
              object000->truthValue = newValue000;
            }
          }
          assignTruthValue(self, newtruthvalue);
        }
        else if (oldtruthvalue == DEFAULT_FALSE_TRUTH_VALUE) {
          deassignTruthValue(self, KWD_PROPOSITIONS_RETRACT_FALSE);
          assignTruthValue(self, newtruthvalue);
        }
        else if (oldtruthvalue == FALSE_TRUTH_VALUE) {
          signalTruthValueClash(self);
        }
      }
      else if (newtruthvalue == FALSE_TRUTH_VALUE) {
        if (oldtruthvalue == DEFAULT_FALSE_TRUTH_VALUE) {
          { Proposition* object001 = self;
            TruthValue* value001 = NULL;
            Object* oldValue002 = object001->truthValue;
            Object* newValue001 = updateInContext(oldValue002, value001, object001->homeContext, false);

            if (!(((boolean)(oldValue002)) &&
                (oldValue002->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
              object001->truthValue = newValue001;
            }
          }
          assignTruthValue(self, newtruthvalue);
        }
        else if (oldtruthvalue == DEFAULT_TRUE_TRUTH_VALUE) {
          deassignTruthValue(self, KWD_PROPOSITIONS_RETRACT_TRUE);
          assignTruthValue(self, newtruthvalue);
        }
        else if (oldtruthvalue == TRUE_TRUTH_VALUE) {
          signalTruthValueClash(self);
        }
      }
      else if (newtruthvalue == DEFAULT_TRUE_TRUTH_VALUE) {
        if (oDEFERINGDEFAULTFORWARDINFERENCESpo) {
          getPropagationEnvironment(oCONTEXTo)->deferDefaultProposition(self);
          return;
        }
        else if ((oldtruthvalue == TRUE_TRUTH_VALUE) ||
            (oldtruthvalue == FALSE_TRUTH_VALUE)) {
        }
        else if (oldtruthvalue == DEFAULT_FALSE_TRUTH_VALUE) {
          deassignTruthValue(self, KWD_PROPOSITIONS_RETRACT_FALSE);
        }
      }
      else if (newtruthvalue == DEFAULT_FALSE_TRUTH_VALUE) {
        if (oDEFERINGDEFAULTFORWARDINFERENCESpo) {
          getPropagationEnvironment(oCONTEXTo)->deferDefaultProposition(self);
          return;
        }
        else if ((oldtruthvalue == FALSE_TRUTH_VALUE) ||
            (oldtruthvalue == TRUE_TRUTH_VALUE)) {
        }
        else if (oldtruthvalue == DEFAULT_TRUE_TRUTH_VALUE) {
          deassignTruthValue(self, KWD_PROPOSITIONS_RETRACT_TRUE);
        }
      }
      else if (newtruthvalue == INCONSISTENT_TRUTH_VALUE) {
        if ((oldtruthvalue == TRUE_TRUTH_VALUE) ||
            (oldtruthvalue == DEFAULT_TRUE_TRUTH_VALUE)) {
          deassignTruthValue(self, KWD_PROPOSITIONS_RETRACT_TRUE);
        }
        else if ((oldtruthvalue == FALSE_TRUTH_VALUE) ||
            (oldtruthvalue == DEFAULT_FALSE_TRUTH_VALUE)) {
          deassignTruthValue(self, KWD_PROPOSITIONS_RETRACT_FALSE);
        }
        assignTruthValue(self, newtruthvalue);
      }
      else {
        signalTruthValueClash(self);
      }
    }
    else if (self->kind == KWD_PROPOSITIONS_FUNCTION) {
      { Proposition* object002 = self;
        TruthValue* value002 = TRUE_TRUTH_VALUE;
        Object* oldValue003 = object002->truthValue;
        Object* newValue002 = updateInContext(oldValue003, value002, object002->homeContext, false);

        if (!(((boolean)(oldValue003)) &&
            (oldValue003->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
          object002->truthValue = newValue002;
        }
      }
    }
    else if (newtruthvalue == INCONSISTENT_TRUTH_VALUE) {
      { Proposition* object003 = self;
        TruthValue* value003 = newtruthvalue;
        Object* oldValue004 = object003->truthValue;
        Object* newValue003 = updateInContext(oldValue004, value003, object003->homeContext, false);

        if (!(((boolean)(oldValue004)) &&
            (oldValue004->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
          object003->truthValue = newValue003;
        }
      }
    }
    else {
      { Proposition* object004 = self;
        TruthValue* value004 = newtruthvalue;
        Object* oldValue005 = object004->truthValue;
        Object* newValue004 = updateInContext(oldValue005, value004, object004->homeContext, false);

        if (!(((boolean)(oldValue005)) &&
            (oldValue005->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
          object004->truthValue = newValue004;
        }
      }
      handleOutOfDateInferenceCache(KWD_PROPOSITIONS_ASSERT, self);
      if (newtruthvalue == TRUE_TRUTH_VALUE) {
        updateLinksAndTimestamps(self, KWD_PROPOSITIONS_ASSERT_TRUE);
      }
      else if (newtruthvalue == FALSE_TRUTH_VALUE) {
        updateLinksAndTimestamps(self, KWD_PROPOSITIONS_ASSERT_FALSE);
      }
      else if (newtruthvalue == DEFAULT_TRUE_TRUTH_VALUE) {
        updateLinksAndTimestamps(self, KWD_PROPOSITIONS_PRESUME_TRUE);
      }
      else if (newtruthvalue == DEFAULT_FALSE_TRUTH_VALUE) {
        updateLinksAndTimestamps(self, KWD_PROPOSITIONS_PRESUME_FALSE);
      }
      reactToKbUpdate(oCONTEXTo, self);
    }
  }
}

void deassignTruthValue(Proposition* self, Keyword* updatemode) {
  { Proposition* object000 = self;
    TruthValue* value000 = NULL;
    Object* oldValue000 = object000->truthValue;
    Object* newValue000 = updateInContext(oldValue000, value000, object000->homeContext, false);

    if (!(((boolean)(oldValue000)) &&
        (oldValue000->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
      object000->truthValue = newValue000;
    }
  }
  if (!(updatemode == KWD_PROPOSITIONS_RETRACT_INCONSISTENT)) {
    handleOutOfDateInferenceCache(KWD_PROPOSITIONS_RETRACT, self);
    updateLinksAndTimestamps(self, updatemode);
  }
}

void updatePropositionTruthValue(Proposition* self, Keyword* updatemode) {
  if (updatemode == KWD_PROPOSITIONS_ASSERT_TRUE) {
    assignTruthValue(self, TRUE_WRAPPER);
  }
  else if (updatemode == KWD_PROPOSITIONS_ASSERT_FALSE) {
    assignTruthValue(self, FALSE_WRAPPER);
  }
  else if (updatemode == KWD_PROPOSITIONS_PRESUME_TRUE) {
    assignTruthValue(self, DEFAULT_TRUE_TRUTH_VALUE);
  }
  else if (updatemode == KWD_PROPOSITIONS_PRESUME_FALSE) {
    assignTruthValue(self, DEFAULT_FALSE_TRUTH_VALUE);
  }
  else if (updatemode == KWD_PROPOSITIONS_RETRACT_TRUE) {
    if (trueP(self) &&
        (!(self->kind == KWD_PROPOSITIONS_FUNCTION))) {
      deassignTruthValue(self, updatemode);
    }
  }
  else if (updatemode == KWD_PROPOSITIONS_RETRACT_FALSE) {
    if (falseP(self)) {
      deassignTruthValue(self, updatemode);
    }
  }
  else if (updatemode == KWD_PROPOSITIONS_CONCEIVE) {
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << updatemode << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  runUpdatePropositionDemon(self, updatemode);
}

void assignPropositionWeight(Proposition* self, double weight) {
  { TruthValue* tv = ((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false)));

    if (weight == 1.0) {
      assignTruthValue(self, TRUE_WRAPPER);
    }
    else if (weight == 0.0) {
      assignTruthValue(self, FALSE_WRAPPER);
    }
    else if ((tv == TRUE_TRUTH_VALUE) ||
        ((tv == FALSE_TRUTH_VALUE) ||
         (!((boolean)(tv))))) {
      { TruthValue* self000 = newTruthValue();

        self000->matchScore = weight;
        { Proposition* object000 = self;
          TruthValue* value000 = self000;
          Object* oldValue001 = object000->truthValue;
          Object* newValue000 = updateInContext(oldValue001, value000, object000->homeContext, false);

          if (!(((boolean)(oldValue001)) &&
              (oldValue001->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
            object000->truthValue = newValue000;
          }
        }
      }
    }
    else {
      ((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false)))->matchScore = weight;
    }
  }
}

Context* tickleContext() {
  { NamedDescription* description = getDescription(SGT_PROPOSITIONS_PL_KERNEL_KB_HIDDEN_RELATION);

    assertProperty(description, SGT_PROPOSITIONS_PL_KERNEL_KB_HIDDEN_RELATION);
    updateProperty(description, SGT_PROPOSITIONS_PL_KERNEL_KB_HIDDEN_RELATION, KWD_PROPOSITIONS_RETRACT_TRUE);
    return (oCONTEXTo);
  }
}

Context* tickleInstances() {
  { Object* temp000 = getInstance(wrapString("HIDDEN-INSTANCE"));

    { Object* instance = (((boolean)(temp000)) ? temp000 : createLogicInstance(SGT_PROPOSITIONS_LOGIC_HIDDEN_INSTANCE, NULL));

      assertProperty(((LogicObject*)(instance)), SGT_PROPOSITIONS_PL_KERNEL_KB_HIDDEN_RELATION);
      updateProperty(((LogicObject*)(instance)), SGT_PROPOSITIONS_PL_KERNEL_KB_HIDDEN_RELATION, KWD_PROPOSITIONS_RETRACT_TRUE);
      return (oCONTEXTo);
    }
  }
}

Cons* listInconsistentPropositions(Cons* options) {
  // Return a list of all currently known inconsistent proposition in the module defined
  // by the :module option (which defaults to the current module).  If `:local?' is specified
  // as TRUE only look in the specified module but not any modules it inherits.  Note, that
  // this simply reports propositions that have been assigned an inconsistent truth value so
  // far (e.g., in clash exceptions), it will not try to detect any new or all inconsistencies
  // in a module.
  { PropertyList* theoptions = parseOptions(options, listO(5, KWD_PROPOSITIONS_MODULE, SGT_PROPOSITIONS_STELLA_MODULE, KWD_PROPOSITIONS_LOCALp, SGT_PROPOSITIONS_STELLA_BOOLEAN, NIL), true, false);
    Module* themodule = ((Module*)(theoptions->lookupWithDefault(KWD_PROPOSITIONS_MODULE, oMODULEo)));
    boolean localP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(theoptions->lookupWithDefault(KWD_PROPOSITIONS_LOCALp, FALSE_WRAPPER))));

    return (allInconsistentPropositions(themodule, localP)->consify());
  }
}

Cons* listInconsistentPropositionsEvaluatorWrapper(Cons* arguments) {
  return (listInconsistentPropositions(arguments));
}

void reactToSkolemValueUpdate(Skolem* skolem, Object* oldvalue, Object* newvalue, boolean toplevelupdateP) {
  { Proposition* proposition = skolem->definingProposition;

    if (toplevelupdateP &&
        nativeSlotPropositionP(proposition)) {
      { Relation* slot = getDescription(((Surrogate*)(proposition->operatoR)))->nativeRelation();
        Object* nativefirstargvalue = valueOf((proposition->arguments->theArray)[0]);

        if (((boolean)(newvalue))) {
          assignNativeSlotValue(proposition, ((Thing*)(nativefirstargvalue)), ((StorageSlot*)(slot)), newvalue);
        }
        else {
          dropNativeSlotValue(((Thing*)(nativefirstargvalue)), ((StorageSlot*)(slot)), oldvalue);
        }
      }
    }
    if (!eqlP(oldvalue, newvalue)) {
      bumpMemoizationTimestamp(KWD_PROPOSITIONS_KB_UPDATE);
      if ((((boolean)(newvalue)) &&
          isaP(newvalue, SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) ||
          metaPropositionP(proposition)) {
        bumpMemoizationTimestamp(KWD_PROPOSITIONS_META_KB_UPDATE);
      }
      if (((boolean)(oldvalue))) {
        updateLinksAndTimestamps(proposition, KWD_PROPOSITIONS_RETRACT_TRUE);
      }
      if (((boolean)(newvalue))) {
        updateLinksAndTimestamps(proposition, KWD_PROPOSITIONS_ASSERT_TRUE);
      }
    }
  }
}

boolean nativeSlotPropositionP(Proposition* self) {
  { Vector* arguments = self->arguments;

    if ((!(arguments->length()))) {
      return (false);
    }
    { Object* firstarg = (((boolean)((arguments->theArray)[0])) ? valueOf((arguments->theArray)[0]) : ((Object*)(NULL)));

      if (((boolean)(firstarg)) &&
          isaP(firstarg, SGT_PROPOSITIONS_STELLA_THING)) {
        { NamedDescription* description = getDescription(self->operatoR);

          if (((boolean)(description)) &&
              (((boolean)(description->nativeRelation())) &&
               isaP(description->nativeRelation(), SGT_PROPOSITIONS_STELLA_STORAGE_SLOT))) {
            return (true);
          }
        }
      }
      return (false);
    }
  }
}

Cons* updateNativeSlotProposition(Proposition* proposition, Keyword* updatemode) {
  { Relation* slot = surrogateToDescription(((Surrogate*)(proposition->operatoR)))->nativeRelation();
    Object* object = valueOf((proposition->arguments->theArray)[0]);
    Object* value = valueOf((proposition->arguments->theArray)[1]);

    if (updatemode == KWD_PROPOSITIONS_ASSERT_TRUE) {
      if (oCLIPPINGENABLEDpo) {
        clearNativeSlotValue(((Thing*)(object)), ((StorageSlot*)(slot)));
      }
      assignNativeSlotValue(proposition, ((Thing*)(object)), ((StorageSlot*)(slot)), value);
    }
    else if (updatemode == KWD_PROPOSITIONS_RETRACT_TRUE) {
      dropNativeSlotValue(((Thing*)(object)), ((StorageSlot*)(slot)), value);
    }
    else {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal update to native slot value.  Mode:  " << "`" << updatemode << "'" << std::endl << "   Proposition:  " << "`" << proposition << "'" << std::endl << std::endl;
    }
    return (NIL);
  }
}

void assignNativeSlotValue(Proposition* prop, Thing* self, StorageSlot* slot, Object* value) {
  if (skolemP(value)) {
    return;
  }
  { Object* oldvalue = readSlotValue(self, slot);

    if (eqlP(oldvalue, value)) {
      return;
    }
    if (((boolean)(oldvalue))) {
      signalUnificationClash(prop, oldvalue, value);
    }
    putSlotValue(self, slot, value);
  }
}

void clearNativeSlotValue(Thing* object, StorageSlot* slot) {
  putSlotValue(object, slot, NULL);
}

void dropNativeSlotValue(Thing* self, StorageSlot* slot, Object* value) {
  { Object* oldvalue = readSlotValue(self, slot);

    if (eqlP(value, oldvalue)) {
      clearNativeSlotValue(self, slot);
    }
  }
}

Surrogate* lookupSlotrefOnInstance(Object* term, Symbol* slotname) {
  { Surrogate* termtype = NULL;

    termtype = safeLogicalType(term);
    if (!((boolean)(termtype))) {
      return (NULL);
    }
    if ((!((boolean)(termtype->surrogateValue))) ||
        ((!isaP(termtype->surrogateValue, SGT_PROPOSITIONS_STELLA_CLASS)) ||
         (termtype == SGT_PROPOSITIONS_STELLA_THING))) {
      return (NULL);
    }
    if (((boolean)(lookupFunction(slotname)))) {
      return (NULL);
    }
    { Surrogate* surrogate = lookupSlotref(termtype, slotname);

      if (((boolean)(surrogate))) {
        return (surrogate);
      }
      if (subtypeOfP(safePrimaryType(term), SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
        { Object* term000 = term;
          LogicObject* term = ((LogicObject*)(term000));

          { Proposition* prop = NULL;
            Iterator* iter000 = unfilteredDependentIsaPropositions(term)->allocateIterator();

            for (; iter000->nextP(); ) {
              prop = ((Proposition*)(iter000->value));
              if (prop->kind == KWD_PROPOSITIONS_ISA) {
                surrogate = lookupSlotref(((Surrogate*)(prop->operatoR)), slotname);
                if (((boolean)(surrogate))) {
                  return (surrogate);
                }
              }
            }
          }
        }
      }
      else {
      }
      if (subtypeOfP(safePrimaryType(term), SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
        { Object* term001 = term;
          Skolem* term = ((Skolem*)(term001));

          if (((boolean)(term->definingProposition)) &&
              isaP(term->definingProposition->operatoR, SGT_PROPOSITIONS_STELLA_SURROGATE)) {
            { NamedDescription* description = getDescription(((Surrogate*)(term->definingProposition->operatoR)));

              if (((boolean)(description))) {
                termtype = ((Surrogate*)(description->ioVariableTypes->last()));
                surrogate = lookupSlotref(termtype, slotname);
                if (((boolean)(surrogate))) {
                  return (surrogate);
                }
              }
            }
          }
        }
      }
      else {
      }
      return (NULL);
    }
  }
}

boolean unboundP(Skolem* skolem) {
  return (!((boolean)(((Object*)(accessInContext(skolem->variableValue, skolem->homeContext, false))))));
}

Object* valueOf(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
      { Object* self000 = self;
        Skolem* self = ((Skolem*)(self000));

        if (!((boolean)(((Object*)(accessInContext(self->variableValue, self->homeContext, false)))))) {
          return (self);
        }
        else {
          return (valueOf(((Object*)(accessInContext(self->variableValue, self->homeContext, false)))));
        }
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* self001 = self;
        Surrogate* self = ((Surrogate*)(self001));

        return (surrogateDvalueOf(self));
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_RELATION)) {
      { Object* self002 = self;
        Relation* self = ((Relation*)(self002));

        return (relationDvalueOf(self));
      }
    }
    else {
      return (self);
    }
  }
}

Object* surrogateDvalueOf(Surrogate* self) {
  { Object* value = self->surrogateValue;

    if (((boolean)(value))) {
      return (valueOf(value));
    }
    else {
      {
        if (dottedStringP(self->symbolName)) {
          { Slot* slot = ((Slot*)(stringToSlot(self->symbolName)));

            if (((boolean)(slot))) {
              return (valueOf(slot));
            }
          }
        }
        if (!(oSUPPRESSNONLOGICOBJECTWARNINGpo)) {
          signalUndefinedTerm(wrapString(self->symbolName));
        }
        return (NULL);
      }
    }
  }
}

Description* relationDvalueOf(Relation* self) {
  { NamedDescription* description = ((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTION, NULL)));

    if (((boolean)(description))) {
      return (description);
    }
    if (subtypeOfP(safePrimaryType(self), SGT_PROPOSITIONS_STELLA_RELATION)) {
      { Relation* self000 = self;
        Relation* self = self000;

        description = getDescription(self);
      }
    }
    else {
    }
    if (((boolean)(description))) {
      return (description);
    }
    if (!(oSUPPRESSNONLOGICOBJECTWARNINGpo)) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(STANDARD_WARNING->nativeStream) << "WARNING: " << "value-of: encountered missing description on class or relation " << self->name() << std::endl;
        helpSignalPropositionError(STANDARD_WARNING, KWD_PROPOSITIONS_WARNING);
      }
    }
    return (NULL);
  }
}

Object* equivalentValueOf(Object* self) {
  if (!((boolean)(self))) {
    return (NULL);
  }
  if (subtypeOfP(safePrimaryType(self), SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
    { Object* self000 = self;
      LogicObject* self = ((LogicObject*)(self000));

      if (((boolean)(((Description*)(accessInContext(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_EQUIVALENT_VALUE, NULL), self->homeContext, false)))))) {
        return (equivalentValueOf(((Description*)(accessInContext(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_EQUIVALENT_VALUE, NULL), self->homeContext, false)))));
      }
      else {
        return (self);
      }
    }
  }
  else {
    return (self);
  }
}

// Used to signal 'ground-value-of' that it can
// call 'bound-to' safely.
DEFINE_STELLA_SPECIAL(oCOMPUTEDQUERYpo, boolean , false);

Object* groundValueOf(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE)) {
      { Object* self000 = self;
        PatternVariable* self = ((PatternVariable*)(self000));

        { Object* value = NULL;

          if ((self->boundToOffset != NULL_INTEGER) &&
              oCOMPUTEDQUERYpo) {
            value = (oQUERYITERATORo->currentPatternRecord->variableBindings->theArray)[(self->boundToOffset)];
          }
          if (!((boolean)(value))) {
            value = ((Object*)(accessInContext(self->variableValue, self->homeContext, false)));
          }
          if (((boolean)(value))) {
            return (groundValueOf(value));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
      { Object* self001 = self;
        Skolem* self = ((Skolem*)(self001));

        { Object* value = ((Object*)(accessInContext(self->variableValue, self->homeContext, false)));

          if (((boolean)(value))) {
            return (groundValueOf(value));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* self002 = self;
        Surrogate* self = ((Surrogate*)(self002));

        { Object* value = self->surrogateValue;

          if (((boolean)(value))) {
            return (groundValueOf(value));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_RELATION)) {
      { Object* self003 = self;
        Relation* self = ((Relation*)(self003));

        return (((NamedDescription*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTION, NULL))));
      }
    }
    else {
      return (self);
    }
  }
}

boolean skolemP(Object* self) {
  return (((boolean)(self)) &&
      isaP(self, SGT_PROPOSITIONS_LOGIC_SKOLEM));
}

boolean variableP(Object* self) {
  return (((boolean)(self)) &&
      isaP(self, SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE));
}

boolean nativeValueP(Object* self) {
  if (((boolean)(self))) {
    return (!isaP(self, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT));
  }
  else {
    return (false);
  }
}

Object* nativeValueOf(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE)) {
      { Object* self000 = self;
        PatternVariable* self = ((PatternVariable*)(self000));

        { Object* value = groundValueOf(self);

          if (((boolean)(value))) {
            return (nativeValueOf(value));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
      { Object* self001 = self;
        Skolem* self = ((Skolem*)(self001));

        { Object* value = ((Object*)(accessInContext(self->variableValue, self->homeContext, false)));

          if (((boolean)(value))) {
            return (nativeValueOf(value));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* self002 = self;
        LogicObject* self = ((LogicObject*)(self002));

        return (NULL);
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* self003 = self;
        Surrogate* self = ((Surrogate*)(self003));

        { Object* value = self->surrogateValue;

          if (((boolean)(value))) {
            return (nativeValueOf(value));
          }
          else {
            return (NULL);
          }
        }
      }
    }
    else {
      return (self);
    }
  }
}

PatternVariable* innermostVariableOf(PatternVariable* self) {
  for (;;) {
    { PatternVariable* tightestvariable = self;
      Object* value = NULL;

      for (;;) {
        value = ((Object*)(accessInContext(tightestvariable->variableValue, tightestvariable->homeContext, false)));
        if (((boolean)(value)) &&
            variableP(value)) {
          tightestvariable = ((PatternVariable*)(value));
        }
        else {
          return (tightestvariable);
        }
      }
    }
  }
}

Object* innermostOf(Object* self) {
  if (descriptionModeP()) {
    { Object* nextvalue = self;
      PatternVariable* tightestvariable = NULL;
      Object* equivalent = NULL;

      for (;;) {
        { Surrogate* testValue000 = safePrimaryType(nextvalue);

          if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE)) {
            { Object* nextvalue000 = nextvalue;
              PatternVariable* nextvalue = ((PatternVariable*)(nextvalue000));

              equivalent = ((Object*)(accessInContext(nextvalue->variableValue, nextvalue->homeContext, false)));
              if (!((boolean)(equivalent))) {
                return (nextvalue);
              }
              tightestvariable = nextvalue;
            }
          }
          else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) {
            { Object* nextvalue001 = nextvalue;
              Description* nextvalue = ((Description*)(nextvalue001));

              return (nextvalue);
            }
          }
          else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
            { Object* nextvalue002 = nextvalue;
              LogicObject* nextvalue = ((LogicObject*)(nextvalue002));

              return (tightestvariable);
            }
          }
          else if (subtypeOfSurrogateP(testValue000)) {
            { Object* nextvalue003 = nextvalue;
              Surrogate* nextvalue = ((Surrogate*)(nextvalue003));

              return (nextvalue);
            }
          }
          else {
            return (nextvalue);
          }
        }
        nextvalue = equivalent;
      }
    }
  }
  else {
    { Object* tightestvalue = self;
      Object* equivalent = NULL;

      for (;;) {
        { Surrogate* testValue001 = safePrimaryType(tightestvalue);

          if (subtypeOfP(testValue001, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
            { Object* tightestvalue000 = tightestvalue;
              Skolem* tightestvalue = ((Skolem*)(tightestvalue000));

              if (!((boolean)(((Object*)(accessInContext(tightestvalue->variableValue, tightestvalue->homeContext, false)))))) {
                return (tightestvalue);
              }
              equivalent = ((Object*)(accessInContext(tightestvalue->variableValue, tightestvalue->homeContext, false)));
            }
          }
          else if (subtypeOfSurrogateP(testValue001)) {
            { Object* tightestvalue001 = tightestvalue;
              Surrogate* tightestvalue = ((Surrogate*)(tightestvalue001));

              if (!((boolean)(tightestvalue->surrogateValue))) {
                return (tightestvalue);
              }
              equivalent = tightestvalue->surrogateValue;
            }
          }
          else {
            return (tightestvalue);
          }
        }
        tightestvalue = equivalent;
      }
    }
  }
}

int oSKOLEM_ID_COUNTERo = 0;

DEFINE_STELLA_SPECIAL(oVARIABLEIDCOUNTERo, int , 0);

Symbol* yieldAnonymousSkolemName(boolean variableP) {
  { const char* suffix = (variableP ? integerToString(((long long int)(oVARIABLEIDCOUNTERo = oVARIABLEIDCOUNTERo + 1))) : integerToString(((long long int)(oSKOLEM_ID_COUNTERo = oSKOLEM_ID_COUNTERo + 1))));

    return (internSymbol(stringConcatenate((variableP ? "?V" : "SK"), ((strlen(suffix) == 1) ? "0" : ""), 1, suffix)));
  }
}

// Cons-list of top-level existentially-quantified skolems.
DEFINE_STELLA_SPECIAL(oFREESKOLEMSo, Cons* , NULL);

Skolem* helpCreateSkolem(Skolem* self, Surrogate* type, Symbol* name, boolean assertisaP) {
  type = unwrapWrappedType(type);
  if (!(((boolean)(name)))) {
    name = yieldAnonymousSkolemName(variableP(self));
  }
  self->skolemName = name;
  if (assertisaP &&
      ((boolean)(type))) {
    assertIsaProposition(self, type);
  }
  return (self);
}

Skolem* createSkolem(Surrogate* type, Symbol* name) {
  { Skolem* skolem = newSkolem();

    if (((boolean)(oFREESKOLEMSo))) {
      oFREESKOLEMSo = cons(skolem, oFREESKOLEMSo);
    }
    helpCreateSkolem(skolem, type, name, true);
    return (skolem);
  }
}

PatternVariable* createVariable(Surrogate* type, Symbol* name, boolean assertisaP) {
  { Keyword* evaluationmode = oEVALUATIONMODEo;

    { 
      BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, evaluationmode);
      if (assertisaP &&
          (!descriptionModeP())) {
        oEVALUATIONMODEo = KWD_PROPOSITIONS_DESCRIPTION;
      }
      return (((PatternVariable*)(helpCreateSkolem(newPatternVariable(), type, name, assertisaP))));
    }
  }
}

Skolem* createVariableOrSkolem(Surrogate* type, Symbol* name) {
  if (descriptionModeP()) {
    return (createVariable(type, name, false));
  }
  else {
    { Skolem* skolem = newSkolem();

      { 
        BIND_STELLA_SPECIAL(oINVISIBLEASSERTIONpo, boolean, true);
        helpCreateSkolem(skolem, type, name, false);
      }
      return (skolem);
    }
  }
}

boolean Skolem::objectEqualP(Object* other) {
  { Skolem* self = this;

    if (self == other) {
      return (true);
    }
    else {
      if (skolemP(other)) {
        { Proposition* propself = self->definingProposition;
          Proposition* propother = ((Skolem*)(other))->definingProposition;

          return (((boolean)(propself)) &&
              (((boolean)(propother)) &&
               equivalentFunctionPropositionsP(propself, propother, NULL)));
        }
      }
    }
    return (false);
  }
}

// Value representing TRUE.
TruthValue* TRUE_TRUTH_VALUE = NULL;

// Value representing FALSE.
TruthValue* FALSE_TRUTH_VALUE = NULL;

// Value representing DEFAULT-TRUE.
TruthValue* DEFAULT_TRUE_TRUTH_VALUE = NULL;

// Value representing DEFAULT-FALSE.
TruthValue* DEFAULT_FALSE_TRUTH_VALUE = NULL;

// Value representing UNKNOWN.  Needed for those cases
// where we need a non-NULL truth value to represents UNKNOWN.
TruthValue* UNKNOWN_TRUTH_VALUE = NULL;

// Value representing a contradiction.
TruthValue* INCONSISTENT_TRUTH_VALUE = NULL;

boolean trueP(Proposition* self) {
  // Return true if `self' is true (or default-true if we are
  // considering default assertions).
  { TruthValue* truthvalue = ((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false)));

    if (truthvalue == TRUE_TRUTH_VALUE) {
      return (true);
    }
    else if (truthvalue == DEFAULT_TRUE_TRUTH_VALUE) {
      if (!oDONTUSEDEFAULTKNOWLEDGEpo) {
        return (true);
      }
    }
    else if (((boolean)(truthvalue)) &&
        ((truthvalue->polarity == KWD_PROPOSITIONS_TRUE) &&
         ((!oDONTUSEDEFAULTKNOWLEDGEpo) ||
          (truthvalue->strength == KWD_PROPOSITIONS_STRICT)))) {
      return (true);
    }
    return (false);
  }
}

boolean falseP(Proposition* self) {
  // Return true if `self' is false (or default-false if we are
  // considering default assertions).
  { TruthValue* truthvalue = ((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false)));

    if (truthvalue == FALSE_TRUTH_VALUE) {
      return (true);
    }
    else if (truthvalue == DEFAULT_FALSE_TRUTH_VALUE) {
      if (!oDONTUSEDEFAULTKNOWLEDGEpo) {
        return (true);
      }
    }
    else if (((boolean)(truthvalue)) &&
        ((truthvalue->polarity == KWD_PROPOSITIONS_FALSE) &&
         ((!oDONTUSEDEFAULTKNOWLEDGEpo) ||
          (truthvalue->strength == KWD_PROPOSITIONS_STRICT)))) {
      return (true);
    }
    return (false);
  }
}

boolean unknownP(Proposition* self) {
  // Return true if the truth of `self' is unknown.
  { TruthValue* tv = ((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false)));

    return (((tv == UNKNOWN_TRUTH_VALUE) ||
        (!((boolean)(tv)))) ||
        (((!(!oDONTUSEDEFAULTKNOWLEDGEpo)) &&
        ((tv == DEFAULT_TRUE_TRUTH_VALUE) ||
         (tv == DEFAULT_FALSE_TRUTH_VALUE))) ||
         (tv == INCONSISTENT_TRUTH_VALUE)));
  }
}

boolean inconsistentP(Proposition* self) {
  // Return true if `self' is inconsistent (true and false).
  return (((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false))) == INCONSISTENT_TRUTH_VALUE);
}

boolean defaultTrueP(Proposition* self) {
  // Return true if `self' is default true.
  return (((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false))) == DEFAULT_TRUE_TRUTH_VALUE);
}

boolean defaultFalseP(Proposition* self) {
  // Return true if `self' is default false.
  return (((TruthValue*)(accessInContext(self->truthValue, self->homeContext, false))) == DEFAULT_FALSE_TRUTH_VALUE);
}

boolean assertedTrueP(Proposition* self) {
  // Return true if `self' has been asserted to be true.
  { 
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getWorldState(oCONTEXTo));
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
    return (trueP(self));
  }
}

boolean assertedFalseP(Proposition* self) {
  // Return true if `self' has been asserted to be false.
  { 
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getWorldState(oCONTEXTo));
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
    return (falseP(self));
  }
}

TruthValue* defaultifyTruthValue(boolean trueP, boolean bydefaultP) {
  return ((trueP ? ((bydefaultP ? DEFAULT_TRUE_TRUTH_VALUE : TRUE_TRUTH_VALUE)) : ((bydefaultP ? DEFAULT_FALSE_TRUTH_VALUE : FALSE_TRUTH_VALUE))));
}

TruthValue* conjoinTruthValues(TruthValue* tv1, TruthValue* tv2) {
  // Return the logical conjunction of truth values `tv1' and `tv2'.
  if ((tv1 == INCONSISTENT_TRUTH_VALUE) ||
      (tv2 == INCONSISTENT_TRUTH_VALUE)) {
    return (INCONSISTENT_TRUTH_VALUE);
  }
  else if ((tv1 == FALSE_TRUTH_VALUE) ||
      (tv2 == FALSE_TRUTH_VALUE)) {
    return (FALSE_TRUTH_VALUE);
  }
  else if ((tv1 == DEFAULT_FALSE_TRUTH_VALUE) &&
      (tv2 == DEFAULT_TRUE_TRUTH_VALUE)) {
    return (UNKNOWN_TRUTH_VALUE);
  }
  else if ((tv1 == DEFAULT_TRUE_TRUTH_VALUE) &&
      (tv2 == DEFAULT_FALSE_TRUTH_VALUE)) {
    return (UNKNOWN_TRUTH_VALUE);
  }
  else if ((!((boolean)(tv1))) ||
      ((tv1 == UNKNOWN_TRUTH_VALUE) ||
       ((!((boolean)(tv2))) ||
        (tv2 == UNKNOWN_TRUTH_VALUE)))) {
    return (UNKNOWN_TRUTH_VALUE);
  }
  else if ((tv1 == DEFAULT_FALSE_TRUTH_VALUE) ||
      (tv2 == DEFAULT_FALSE_TRUTH_VALUE)) {
    return (DEFAULT_FALSE_TRUTH_VALUE);
  }
  else if ((tv1 == DEFAULT_TRUE_TRUTH_VALUE) ||
      (tv2 == DEFAULT_TRUE_TRUTH_VALUE)) {
    return (DEFAULT_TRUE_TRUTH_VALUE);
  }
  else {
    return (TRUE_TRUTH_VALUE);
  }
}

TruthValue* disjoinTruthValues(TruthValue* tv1, TruthValue* tv2) {
  // Return the logical disjunction of truth values `tv1' and `tv2'.
  if ((tv1 == TRUE_TRUTH_VALUE) ||
      (tv2 == TRUE_TRUTH_VALUE)) {
    return (TRUE_TRUTH_VALUE);
  }
  else if ((tv1 == DEFAULT_TRUE_TRUTH_VALUE) ||
      (tv2 == DEFAULT_TRUE_TRUTH_VALUE)) {
    return (DEFAULT_TRUE_TRUTH_VALUE);
  }
  else if ((!((boolean)(tv1))) ||
      ((tv1 == UNKNOWN_TRUTH_VALUE) ||
       ((!((boolean)(tv2))) ||
        (tv2 == UNKNOWN_TRUTH_VALUE)))) {
    return (UNKNOWN_TRUTH_VALUE);
  }
  else if ((tv1 == DEFAULT_FALSE_TRUTH_VALUE) ||
      (tv2 == DEFAULT_FALSE_TRUTH_VALUE)) {
    return (DEFAULT_FALSE_TRUTH_VALUE);
  }
  else {
    return (FALSE_TRUTH_VALUE);
  }
}

TruthValue* invertTruthValue(TruthValue* self) {
  // Return the logical negation of `self'.
  if (self == TRUE_TRUTH_VALUE) {
    return (FALSE_TRUTH_VALUE);
  }
  else if (self == DEFAULT_TRUE_TRUTH_VALUE) {
    return (DEFAULT_FALSE_TRUTH_VALUE);
  }
  else if (self == FALSE_TRUTH_VALUE) {
    return (TRUE_TRUTH_VALUE);
  }
  else if (self == DEFAULT_FALSE_TRUTH_VALUE) {
    return (DEFAULT_TRUE_TRUTH_VALUE);
  }
  else if (self == INCONSISTENT_TRUTH_VALUE) {
    return (INCONSISTENT_TRUTH_VALUE);
  }
  else {
    return (UNKNOWN_TRUTH_VALUE);
  }
}

boolean strongerTruthValueP(TruthValue* tv1, TruthValue* tv2) {
  // Compare the two truth values and return `true' if `tv1' is strictly
  // stronger than `tv2'.  Stronger uses the following partial order:
  //   INCONSISTENT > STRICT > DEFAULT > UNKNOWN.
  // Truth values at the same level are equal in strength.
  if (tv1 == tv2) {
    return (false);
  }
  else if (tv1 == INCONSISTENT_TRUTH_VALUE) {
    return (!(tv2 == INCONSISTENT_TRUTH_VALUE));
  }
  else if (tv2 == INCONSISTENT_TRUTH_VALUE) {
    return (false);
  }
  else if ((tv1 == TRUE_TRUTH_VALUE) ||
      (tv1 == FALSE_TRUTH_VALUE)) {
    return (!((tv2 == TRUE_TRUTH_VALUE) ||
        (tv2 == FALSE_TRUTH_VALUE)));
  }
  else if ((tv2 == TRUE_TRUTH_VALUE) ||
      (tv2 == FALSE_TRUTH_VALUE)) {
    return (false);
  }
  else if ((tv1 == DEFAULT_TRUE_TRUTH_VALUE) ||
      (tv1 == DEFAULT_FALSE_TRUTH_VALUE)) {
    return (!((tv2 == DEFAULT_TRUE_TRUTH_VALUE) ||
        (tv2 == DEFAULT_FALSE_TRUTH_VALUE)));
  }
  else if ((tv2 == DEFAULT_TRUE_TRUTH_VALUE) ||
      (tv2 == DEFAULT_FALSE_TRUTH_VALUE)) {
    return (false);
  }
  else if (((tv1 == UNKNOWN_TRUTH_VALUE) ||
      (!((boolean)(tv1)))) &&
      ((tv2 == UNKNOWN_TRUTH_VALUE) ||
       (!((boolean)(tv2))))) {
    return (false);
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Internal Error: STRONGER-TRUTH-VALUE?: Shouldn't get here. tv1=" << "`" << tv1 << "'" << " tv2=" << "`" << tv2 << "'";
      throw *newLogicException(stream000->theStringReader());
    }
  }
}

TruthValue* mergeTruthValues(TruthValue* tv1, TruthValue* tv2) {
  // Merge two truth values that are describing the "same" logical
  // proposition.  This handles subordination of default to strict values, 
  // known over unknown and potential inconsistent values.
  // 
  // In particular, this can be used to check for negated values by asking for
  // the truth of a proposition and its negation, inverting the negation and then
  // using merge to come up with an answer.
  if (tv1 == tv2) {
    return (tv1);
  }
  else if ((tv1 == INCONSISTENT_TRUTH_VALUE) ||
      (tv2 == INCONSISTENT_TRUTH_VALUE)) {
    return (INCONSISTENT_TRUTH_VALUE);
  }
  else if (((tv1 == TRUE_TRUTH_VALUE) ||
      (tv1 == FALSE_TRUTH_VALUE)) &&
      ((tv2 == DEFAULT_TRUE_TRUTH_VALUE) ||
       (tv2 == DEFAULT_FALSE_TRUTH_VALUE))) {
    return (tv1);
  }
  else if (((tv1 == DEFAULT_TRUE_TRUTH_VALUE) ||
      (tv1 == DEFAULT_FALSE_TRUTH_VALUE)) &&
      ((tv2 == TRUE_TRUTH_VALUE) ||
       (tv2 == FALSE_TRUTH_VALUE))) {
    return (tv2);
  }
  else if (knownTruthValueP(tv1) &&
      ((tv2 == UNKNOWN_TRUTH_VALUE) ||
       (!((boolean)(tv2))))) {
    return (tv1);
  }
  else if (((tv1 == UNKNOWN_TRUTH_VALUE) ||
      (!((boolean)(tv1)))) &&
      knownTruthValueP(tv2)) {
    return (tv2);
  }
  else if (((tv1 == DEFAULT_TRUE_TRUTH_VALUE) ||
      (tv1 == DEFAULT_FALSE_TRUTH_VALUE)) &&
      ((tv2 == DEFAULT_TRUE_TRUTH_VALUE) ||
       (tv2 == DEFAULT_FALSE_TRUTH_VALUE))) {
    return (UNKNOWN_TRUTH_VALUE);
  }
  else if (((tv1 == TRUE_TRUTH_VALUE) ||
      (tv1 == FALSE_TRUTH_VALUE)) &&
      ((tv2 == TRUE_TRUTH_VALUE) ||
       (tv2 == FALSE_TRUTH_VALUE))) {
    return (INCONSISTENT_TRUTH_VALUE);
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Internal Error: MERGE-TRUTH-VALUES: Shouldn't get here. tv1=" << "`" << tv1 << "'" << " tv2=" << "`" << tv2 << "'";
      throw *newLogicException(stream000->theStringReader());
    }
  }
}

TruthValue* weakenTruthValue(TruthValue* tv1, TruthValue* tv2) {
  // If `tv2' has lesser strength than `tv1', adapt the strength of `tv1' (not
  // its value!) and return the result.  Otherwise, return `tv1' unmodified.
  if ((tv2 == UNKNOWN_TRUTH_VALUE) ||
      (!((boolean)(tv2)))) {
    return (UNKNOWN_TRUTH_VALUE);
  }
  else if ((tv2 == DEFAULT_TRUE_TRUTH_VALUE) ||
      (tv2 == DEFAULT_FALSE_TRUTH_VALUE)) {
    if ((tv1 == TRUE_TRUTH_VALUE) ||
        (tv1 == DEFAULT_TRUE_TRUTH_VALUE)) {
      return (DEFAULT_TRUE_TRUTH_VALUE);
    }
    if ((tv1 == FALSE_TRUTH_VALUE) ||
        (tv1 == DEFAULT_FALSE_TRUTH_VALUE)) {
      return (DEFAULT_FALSE_TRUTH_VALUE);
    }
  }
  return (tv1);
}

TruthValue* strengthenTruthValue(TruthValue* tv1, TruthValue* tv2) {
  // If `tv2' has greater strength than `tv1', adapt the strength of `tv1' (not
  // its value!) and return the result.  Otherwise, return `tv1' unmodified.
  if (((tv2 == TRUE_TRUTH_VALUE) ||
      (tv2 == FALSE_TRUTH_VALUE)) &&
      ((tv1 == DEFAULT_TRUE_TRUTH_VALUE) ||
       (tv1 == DEFAULT_FALSE_TRUTH_VALUE))) {
    if ((tv1 == TRUE_TRUTH_VALUE) ||
        (tv1 == DEFAULT_TRUE_TRUTH_VALUE)) {
      return (TRUE_TRUTH_VALUE);
    }
    if ((tv1 == FALSE_TRUTH_VALUE) ||
        (tv1 == DEFAULT_FALSE_TRUTH_VALUE)) {
      return (FALSE_TRUTH_VALUE);
    }
  }
  return (tv1);
}

boolean trueTruthValueP(TruthValue* self) {
  // Return TRUE if `self' represents some form of truth.
  return ((self == TRUE_TRUTH_VALUE) ||
      (self == DEFAULT_TRUE_TRUTH_VALUE));
}

boolean falseTruthValueP(TruthValue* self) {
  // Return TRUE if `self' represents some form of falsehood.
  return ((self == FALSE_TRUTH_VALUE) ||
      (self == DEFAULT_FALSE_TRUTH_VALUE));
}

boolean strictTruthValueP(TruthValue* self) {
  // Return TRUE if `self' is a strict truth value.
  return ((self == TRUE_TRUTH_VALUE) ||
      (self == FALSE_TRUTH_VALUE));
}

boolean defaultTruthValueP(TruthValue* self) {
  // Return TRUE if `self' is a default truth value.
  return ((self == DEFAULT_TRUE_TRUTH_VALUE) ||
      (self == DEFAULT_FALSE_TRUTH_VALUE));
}

boolean unknownTruthValueP(TruthValue* self) {
  // Return TRUE if `self' represents UNKNOWN.
  return ((self == UNKNOWN_TRUTH_VALUE) ||
      (!((boolean)(self))));
}

boolean knownTruthValueP(TruthValue* self) {
  // Return TRUE if `self' is a known truth value, that is
  // either TRUE or FALSE, but not UNKNOWN, INCONSISTENT, etc.
  return (((self == TRUE_TRUTH_VALUE) ||
      (self == DEFAULT_TRUE_TRUTH_VALUE)) ||
      ((self == FALSE_TRUTH_VALUE) ||
       (self == DEFAULT_FALSE_TRUTH_VALUE)));
}

boolean inconsistentTruthValueP(TruthValue* self) {
  // Return TRUE if `self' represents INCONSISTENT.
  return (self == INCONSISTENT_TRUTH_VALUE);
}

const char* truthValueToString(TruthValue* self, boolean abbreviateP) {
  if (self == TRUE_TRUTH_VALUE) {
    return ((abbreviateP ? "T" : "TRUE"));
  }
  else if (self == FALSE_TRUTH_VALUE) {
    return ((abbreviateP ? "F" : "FALSE"));
  }
  else if (self == DEFAULT_TRUE_TRUTH_VALUE) {
    return ((abbreviateP ? "t" : "DEFAULT-TRUE"));
  }
  else if (self == DEFAULT_FALSE_TRUTH_VALUE) {
    return ((abbreviateP ? "f" : "DEFAULT-FALSE"));
  }
  else if (self == UNKNOWN_TRUTH_VALUE) {
    return ((abbreviateP ? "U" : "UNKNOWN"));
  }
  else if (self == INCONSISTENT_TRUTH_VALUE) {
    return ((abbreviateP ? "#" : "INCONSISTENT"));
  }
  else {
    return (NULL);
  }
}

void printTruthValue(TruthValue* self, OutputStream* stream) {
  { const char* tvString = truthValueToString(self, false);

    if (tvString == NULL) {
      *(stream->nativeStream) << "|i|" << self->primaryType();
    }
    else {
      *(stream->nativeStream) << tvString;
    }
  }
}

void signalUnificationClash(Proposition* prop, Object* term1, Object* term2) {
  { const char* message = "Unification clash.";
    UnificationClash* clashObject = NULL;

    if (((boolean)(prop))) {
      assignTruthValue(prop, INCONSISTENT_TRUTH_VALUE);
    }
    else {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Internal: SIGNAL-UNIFICATION-CLASH doesn't have responsible proposition available." << std::endl;
    }
    if (oRECORD_JUSTIFICATIONSpo) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "SIGNAL-UNIFICATION-CLASH doesn't yet have justification support" << std::endl;
    }
    if (((boolean)(term1)) &&
        ((boolean)(term2))) {
      { const char* message000 = NULL;

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          message000 = stringConcatenate("`", stringify(term1), 5, "'", " clashes with ", "`", stringify(term2), "'");
        }
        message = message000;
      }
    }
    clashObject = newUnificationClash(message);
    clashObject->proposition = prop;
    clashObject->context = oCONTEXTo;
    clashObject->value1 = term1;
    clashObject->value2 = term2;
    handleClashException(clashObject);
  }
}

void signalVariableValueClash(Proposition* prop, Skolem* skolem, Object* value1, Object* value2) {
  assignTruthValue(prop, INCONSISTENT_TRUTH_VALUE);
  { const char* message = "Variable value clash.";
    VariableValueClash* exception = NULL;

    if (((boolean)(value1)) &&
        ((boolean)(value2))) {
      { const char* message000 = NULL;

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          message000 = stringConcatenate("Skolem ", "`", 13, stringify(skolem), "'", " is equated with multiple values:", "\n", "   ", "`", stringify(value1), "'", " and ", "`", stringify(value2), "'", ".");
        }
        message = message000;
      }
    }
    exception = newVariableValueClash(message);
    exception->proposition = prop;
    exception->context = oCONTEXTo;
    exception->skolem = skolem;
    exception->value1 = value1;
    exception->value2 = value2;
    handleClashException(exception);
  }
}

void signalTruthValueClash(Proposition* proposition) {
  if (!((proposition == TRUE_PROPOSITION) ||
      (proposition == FALSE_PROPOSITION))) {
    assignTruthValue(proposition, INCONSISTENT_TRUTH_VALUE);
    if (oRECORD_JUSTIFICATIONSpo) {
      { Proposition* negatedProposition = conceiveInvertedProposition(proposition);
        Cons* antecedents = NIL;

        if (hasSupportedForwardJustificationsP(negatedProposition)) {
          antecedents = getSupportedForwardJustifications(negatedProposition)->theConsList;
        }
        else {
          { PrimitiveStrategy* self000 = newPrimitiveStrategy();

            self000->proposition = negatedProposition;
            self000->strategy = KWD_PROPOSITIONS_LOOKUP_ASSERTIONS;
            antecedents = cons(self000, antecedents);
          }
        }
        if (hasSupportedForwardJustificationsP(proposition)) {
          antecedents = append(getSupportedForwardJustifications(proposition)->theConsList, antecedents);
        }
        else {
          { PrimitiveStrategy* self001 = newPrimitiveStrategy();

            self001->proposition = proposition;
            self001->strategy = KWD_PROPOSITIONS_LOOKUP_ASSERTIONS;
            antecedents = cons(self001, antecedents);
          }
        }
        addForwardJustification(proposition, createClashJustification(proposition, antecedents, KWD_PROPOSITIONS_FORWARD));
        addForwardJustification(negatedProposition, createClashJustification(negatedProposition, copyConsList(antecedents)->reverse(), KWD_PROPOSITIONS_FORWARD));
      }
    }
  }
  { const char* message = NULL;
    Context* exceptionContext = oCONTEXTo;
    TruthValueClash* exception = NULL;

    if (oCONTEXTo == ((World*)(dynamicSlotValue(oMODULEo->dynamicSlots, SYM_PROPOSITIONS_LOGIC_META_INFERENCE_CACHE, NULL)))) {
      { const char* message000 = NULL;

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          message000 = stringConcatenate("Derived both TRUE and FALSE for the proposition ", "`", 9, stringify(proposition), "'", ".", "\n", "   Clash occurred in the meta inference cache for module ", "`", stringify(oMODULEo), "'", ".");
        }
        message = message000;
      }
    }
    else if (oCONTEXTo == ((World*)(dynamicSlotValue(oMODULEo->dynamicSlots, SYM_PROPOSITIONS_LOGIC_TRUTH_MAINTAINED_INFERENCE_CACHE, NULL)))) {
      { const char* message001 = NULL;

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          message001 = stringConcatenate("Derived both TRUE and FALSE for the proposition ", "`", 9, stringify(proposition), "'", ".", "\n", "   Clash occurred in the default inference cache for module ", "`", stringify(oMODULEo), "'", ".");
        }
        message = message001;
      }
    }
    else if (oCONTEXTo == oMODULEo) {
      { const char* message002 = NULL;

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          message002 = stringConcatenate("Derived both TRUE and FALSE for the proposition ", "`", 9, stringify(proposition), "'", ".", "\n", "   Clash occurred in module ", "`", stringify(oMODULEo), "'", ".");
        }
        message = message002;
      }
    }
    else {
      { const char* message003 = NULL;

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          message003 = stringConcatenate("Derived both TRUE and FALSE for the proposition ", "`", 13, stringify(proposition), "'", ".", "\n", "   Clash occurred in the world ", "`", stringify(oCONTEXTo), "'", " in module ", "`", stringify(oMODULEo), "'", ".");
        }
        message = message003;
      }
    }
    exception = newTruthValueClash(message);
    exception->proposition = proposition;
    exception->context = exceptionContext;
    handleClashException(exception);
  }
}

Cons* Proposition::clashExceptions_reader() {
  { Proposition* self = this;

    { Cons* answer = ((Cons*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_CLASH_EXCEPTIONS, NULL)));

      if (!((boolean)(answer))) {
        return (NIL);
      }
      else {
        return (answer);
      }
    }
  }
}

Cons* getVisibleClashExceptions(Proposition* incoherentprop) {
  // Return the set of clash exceptions for 'incoherentProp' that are visible from the
  // current context.  These are recorded most-recent first in order of occurrance.
  { Cons* value000 = NIL;

    { ExceptionRecord* record = NULL;
      Cons* iter000 = incoherentprop->clashExceptions_reader();
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        record = ((ExceptionRecord*)(iter000->value));
        if ((oCONTEXTo == record->context) ||
            oCONTEXTo->allSuperContexts->membP(record->context)) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(record, NIL);
              if (value000 == NIL) {
                value000 = collect000;
              }
              else {
                addConsToEndOfConsList(value000, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(record, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    { Cons* value001 = value000;

      return (value001);
    }
  }
}

void handleClashException(Clash* clashexception) {
  { Proposition* proposition = clashexception->proposition;
    Context* context = getWorldState(clashexception->context);
    Proposition* incoherentprop = createProposition(SYM_PROPOSITIONS_STELLA_PREDICATE, 2);

    incoherentprop->operatoR = SGT_PROPOSITIONS_PL_KERNEL_KB_INCOHERENT;
    (incoherentprop->arguments->theArray)[0] = context;
    (incoherentprop->arguments->theArray)[1] = proposition;
    incoherentprop = fastenDownOneProposition(incoherentprop, false);
    { ExceptionRecord* self000 = newExceptionRecord();

      self000->exception = clashexception;
      self000->context = context;
      self000->module = context->baseModule;
      setDynamicSlotValue(incoherentprop->dynamicSlots, SYM_PROPOSITIONS_LOGIC_CLASH_EXCEPTIONS, cons(self000, incoherentprop->clashExceptions_reader()), NULL);
    }
    updatePropositionTruthValue(incoherentprop, KWD_PROPOSITIONS_ASSERT_TRUE);
    if (!(((boolean)(accessBinaryValue(getDescription(SGT_PROPOSITIONS_PL_KERNEL_KB_INCOHERENT), SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_TRUE_DEMON))) ||
        ((boolean)(accessBinaryValue(getDescription(SGT_PROPOSITIONS_PL_KERNEL_KB_INCOHERENT), SGT_PROPOSITIONS_PL_KERNEL_KB_UPDATE_PROPOSITION_DEMON))))) {
      throw *clashexception;
    }
  }
}

Surrogate* logicalType(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) {
      { Object* self000 = self;
        Description* self = ((Description*)(self000));

        if (monadicP(self) &&
            ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_IOTAp, FALSE_WRAPPER)))->wrapperValue) {
          return (((PatternVariable*)((self->ioVariables->theArray)[0]))->skolemType);
        }
        else if (monadicP(self) &&
            (self->ioVariables->nonEmptyP() &&
             (((boolean)(((PatternVariable*)((self->ioVariables->theArray)[0]))->skolemType)) &&
              classDescriptionP(surrogateToDescription(((PatternVariable*)((self->ioVariables->theArray)[0]))->skolemType))))) {
          return (SGT_PROPOSITIONS_PL_KERNEL_KB_CONCEPT);
        }
        else {
          return (SGT_PROPOSITIONS_PL_KERNEL_KB_RELATION);
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE)) {
      { Object* self001 = self;
        PatternVariable* self = ((PatternVariable*)(self001));

        { Surrogate* type = self->skolemType;

          if (((boolean)(type)) &&
              (!(type == SGT_PROPOSITIONS_STELLA_THING))) {
            return (type);
          }
        }
        { Proposition* p = NULL;
          Iterator* iter000 = unfilteredDependentIsaPropositions(self)->allocateIterator();

          for (; iter000->nextP(); ) {
            p = ((Proposition*)(iter000->value));
            if ((p->kind == KWD_PROPOSITIONS_ISA) &&
                coerceWrappedBooleanToBoolean(p->variableTypeP_reader())) {
              return (((Surrogate*)(p->operatoR)));
            }
          }
        }
        return (SGT_PROPOSITIONS_STELLA_THING);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
      { Object* self002 = self;
        Skolem* self = ((Skolem*)(self002));

        if (((boolean)(self->skolemType))) {
          return (self->skolemType);
        }
        else {
          return (SGT_PROPOSITIONS_STELLA_THING);
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* self003 = self;
        LogicObject* self = ((LogicObject*)(self003));

        return (SGT_PROPOSITIONS_STELLA_THING);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
      { Object* self004 = self;
        Proposition* self = ((Proposition*)(self004));

        return (SGT_PROPOSITIONS_LOGIC_PROPOSITION);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_LITERAL_WRAPPER)) {
      { Object* self005 = self;
        LiteralWrapper* self = ((LiteralWrapper*)(self005));

        return (wrapperValueType(self));
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* self006 = self;
        Surrogate* self = ((Surrogate*)(self006));

        if (((boolean)(self->surrogateValue)) &&
            (!(self->surrogateValue == BOTTOM))) {
          return (logicalType(self->surrogateValue));
        }
        else {
          return (SGT_PROPOSITIONS_STELLA_THING);
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_SET)) {
      { Object* self007 = self;
        Set* self = ((Set*)(self007));

        return (SGT_PROPOSITIONS_PL_KERNEL_KB_SET);
      }
    }
    else if (subtypeOfClassP(testValue000)) {
      { Object* self008 = self;
        Class* self = ((Class*)(self008));

        return (SGT_PROPOSITIONS_PL_KERNEL_KB_CONCEPT);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_SLOT)) {
      { Object* self009 = self;
        Slot* self = ((Slot*)(self009));

        if (booleanTypeP(self->slotBaseType)) {
          return (SGT_PROPOSITIONS_PL_KERNEL_KB_RELATION);
        }
        else {
          return (SGT_PROPOSITIONS_PL_KERNEL_KB_FUNCTION);
        }
      }
    }
    else {
      return (self->primaryType());
    }
  }
}

// Used by 'safe-logical-type' to ask for a type
// without signalling an error if none exists.
DEFINE_STELLA_SPECIAL(oSUPPRESSUNTYPEDTYPEERRORpo, boolean , false);

Surrogate* safeLogicalType(Object* self) {
  { 
    BIND_STELLA_SPECIAL(oSUPPRESSUNTYPEDTYPEERRORpo, boolean, true);
    return (logicalType(self));
  }
}

Surrogate* classLogicalType(Class* self) {
  return (self->classType);
}

void unifyTypes(Proposition* prop, Skolem* term1, Object* term2) {
  { Surrogate* type1 = logicalType(term1);
    Surrogate* type2 = logicalType(term2);

    if ((type1 == type2) ||
        (logicalSubtypeOfP(type1, type2) ||
         logicalSubtypeOfP(type2, type1))) {
    }
    else if (type1 == SGT_PROPOSITIONS_STELLA_THING) {
      if (isaP(term1, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
      }
      ((Skolem*)(term1))->skolemType = type2;
    }
    else if (type2 == SGT_PROPOSITIONS_STELLA_THING) {
      if (isaP(term2, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
        ((Skolem*)(term2))->skolemType = type1;
      }
    }
    else {
      if (bottomP(term2)) {
        return;
      }
      signalUnificationClash(prop, term1, term2);
    }
  }
}

void unifySkolemAndValue(Skolem* skolem, Object* value) {
  { Proposition* prop = NULL;
    Iterator* iter000 = unfilteredDependentPropositions(skolem, NULL)->allocateIterator();

    for (; iter000->nextP(); ) {
      prop = ((Proposition*)(iter000->value));
      evaluateProposition(prop);
    }
  }
}

void verifySkolemAndValueTypes(Skolem* fromskolem, Object* tovalue) {
  { boolean typeisokP = false;
    Surrogate* type = fromskolem->skolemType;
    Proposition* equatingproposition = NULL;

    if (skolemP(tovalue)) {
      equatingproposition = findEquatingProposition(tovalue, fromskolem);
      if (((boolean)(equatingproposition)) &&
          defaultTrueP(equatingproposition)) {
        { OutputStringStream* stream000 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream000->nativeStream) << "ERROR: " << "Equating two skolems " << "`" << fromskolem << "'" << " and " << "`" << tovalue << "'" << " by default is not yet supported." << std::endl << "." << std::endl;
            helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
          }
          throw *newPropositionError(stream000->theStringReader());
        }
      }
    }
    typeisokP = checkCoercedTypeP(tovalue, type, true, tovalue);
    if (!typeisokP) {
      equatingproposition = findEquatingProposition(tovalue, fromskolem);
      if (!((boolean)(equatingproposition))) {
        { 
          BIND_STELLA_SPECIAL(oTERMUNDERCONSTRUCTIONo, Object*, oTERMUNDERCONSTRUCTIONo);
          if (!((boolean)(oTERMUNDERCONSTRUCTIONo))) {
            oTERMUNDERCONSTRUCTIONo = fromskolem->definingProposition;
          }
          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(STANDARD_WARNING->nativeStream) << "WARNING: " << "Type check violation: Assigned value `" << tovalue << "'" << std::endl << "   to skolem with type `" << type << "'." << std::endl;
            helpSignalPropositionError(STANDARD_WARNING, KWD_PROPOSITIONS_WARNING);
          }
        }
      }
      else {
        verifyArgumentTypesAndCount(equatingproposition);
      }
    }
  }
}

boolean skolemWithVariableValueCycleP(Object* self) {
  { Object* cursor = self;

    for (;;) {
      if (skolemP(cursor)) {
        { Object* value = ((Object*)(accessInContext(((Skolem*)(cursor))->variableValue, ((Skolem*)(cursor))->homeContext, false)));

          if (eqlP(value, self)) {
            return (true);
          }
          else {
            cursor = value;
          }
        }
      }
      else {
        break;
      }
    }
    return (false);
  }
}

void synchronizeVariableValueInferenceCaches(Skolem* fromskolem, Skolem* tovalue) {
  if (justInTimeInferenceCacheP(oCONTEXTo)) {
    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getInferenceCache(getWorldState(oCONTEXTo), KWD_PROPOSITIONS_META));
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      { Skolem* object000 = fromskolem;
        Object* value000 = tovalue;
        Object* oldValue000 = object000->variableValue;
        Object* newValue000 = updateInContext(oldValue000, value000, object000->homeContext, false);

        if (!(((boolean)(oldValue000)) &&
            (oldValue000->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
          object000->variableValue = newValue000;
        }
      }
      if (!(tovalue->variableValueInverse_reader()->membP(fromskolem))) {
        { Skolem* object001 = tovalue;
          Cons* value001 = cons(fromskolem, tovalue->variableValueInverse_reader());
          Object* oldValue001 = object001->variableValueInverse;
          Object* newValue001 = updateInContext(oldValue001, value001, object001->homeContext, false);

          if (!(((boolean)(oldValue001)) &&
              (oldValue001->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
            object001->variableValueInverse = newValue001;
          }
        }
      }
    }
  }
  else if (metaInferenceCacheP(oCONTEXTo)) {
    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getInferenceCache(getWorldState(oCONTEXTo), KWD_PROPOSITIONS_JUST_IN_TIME));
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      { Skolem* object002 = fromskolem;
        Object* value002 = tovalue;
        Object* oldValue002 = object002->variableValue;
        Object* newValue002 = updateInContext(oldValue002, value002, object002->homeContext, false);

        if (!(((boolean)(oldValue002)) &&
            (oldValue002->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
          object002->variableValue = newValue002;
        }
      }
      { Cons* inverses = ((Cons*)(accessInContext(tovalue->variableValueInverse, tovalue->homeContext, true)));

        if (!((boolean)(inverses))) {
          inverses = NIL;
        }
        if (!(inverses->membP(fromskolem))) {
          { Skolem* object003 = tovalue;
            Cons* value003 = cons(fromskolem, inverses);
            Object* oldValue004 = object003->variableValueInverse;
            Object* newValue003 = updateInContext(oldValue004, value003, object003->homeContext, false);

            if (!(((boolean)(oldValue004)) &&
                (oldValue004->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
              object003->variableValueInverse = newValue003;
            }
          }
        }
      }
    }
  }
}

void bindSkolemToValue(Skolem* fromskolem, Object* tovalue, boolean toplevelupdateP) {
  verifySkolemAndValueTypes(fromskolem, tovalue);
  { Skolem* object000 = fromskolem;
    Object* value000 = tovalue;
    Object* oldValue000 = object000->variableValue;
    Object* newValue000 = updateInContext(oldValue000, value000, object000->homeContext, false);

    if (!(((boolean)(oldValue000)) &&
        (oldValue000->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
      object000->variableValue = newValue000;
    }
  }
  { Surrogate* testValue000 = safePrimaryType(tovalue);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
      { Object* tovalue000 = tovalue;
        Skolem* tovalue = ((Skolem*)(tovalue000));

        if (skolemWithVariableValueCycleP(tovalue)) {
          { Skolem* object001 = fromskolem;
            Object* value001 = NULL;
            Object* oldValue001 = object001->variableValue;
            Object* newValue001 = updateInContext(oldValue001, value001, object001->homeContext, false);

            if (!(((boolean)(oldValue001)) &&
                (oldValue001->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
              object001->variableValue = newValue001;
            }
          }
          return;
        }
        { Skolem* object002 = tovalue;
          Cons* value002 = cons(fromskolem, tovalue->variableValueInverse_reader());
          Object* oldValue002 = object002->variableValueInverse;
          Object* newValue002 = updateInContext(oldValue002, value002, object002->homeContext, false);

          if (!(((boolean)(oldValue002)) &&
              (oldValue002->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
            object002->variableValueInverse = newValue002;
          }
        }
        synchronizeVariableValueInferenceCaches(fromskolem, tovalue);
        if (!((boolean)(tovalue->skolemType))) {
          tovalue->skolemType = fromskolem->skolemType;
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* tovalue001 = tovalue;
        LogicObject* tovalue = ((LogicObject*)(tovalue001));

        { LogicObject* object003 = tovalue;
          Cons* value003 = cons(fromskolem, tovalue->variableValueInverse_reader());
          Object* oldValue003 = object003->variableValueInverse;
          Object* newValue003 = updateInContext(oldValue003, value003, object003->homeContext, false);

          if (!(((boolean)(oldValue003)) &&
              (oldValue003->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
            object003->variableValueInverse = newValue003;
          }
        }
      }
    }
    else {
      { Proposition* proposition = fromskolem->definingProposition;

        if (((boolean)(proposition)) &&
            rewrapIthArgumentP(tovalue, proposition, proposition->arguments->length())) {
          { Skolem* object004 = fromskolem;
            Object* value004 = rewrapArgument(tovalue);
            Object* oldValue004 = object004->variableValue;
            Object* newValue004 = updateInContext(oldValue004, value004, object004->homeContext, false);

            if (!(((boolean)(oldValue004)) &&
                (oldValue004->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
              object004->variableValue = newValue004;
            }
          }
        }
      }
    }
  }
  handleOutOfDateInferenceCache(KWD_PROPOSITIONS_ASSERT, fromskolem->definingProposition);
  reactToKbUpdate(oCONTEXTo, fromskolem);
  if (!skolemP(tovalue)) {
    if (((boolean)(fromskolem->definingProposition))) {
      reactToSkolemValueUpdate(fromskolem, NULL, tovalue, toplevelupdateP);
    }
  }
}

void unbindSkolemValue(Skolem* skolem, boolean toplevelupdateP) {
  { Object* oldvalue = valueOf(skolem);
    Proposition* definingprop = skolem->definingProposition;
    Proposition* equatingprop = NULL;

    unlinkEquivalentValue(skolem);
    equatingprop = findEquatingProposition(oldvalue, skolem);
    if (((boolean)(equatingprop))) {
      updatePropositionTruthValue(equatingprop, KWD_PROPOSITIONS_RETRACT_TRUE);
      handleOutOfDateInferenceCache(KWD_PROPOSITIONS_RETRACT, equatingprop);
    }
    else {
      handleOutOfDateInferenceCache(KWD_PROPOSITIONS_RETRACT, definingprop);
    }
    if (((boolean)(definingprop))) {
      reactToSkolemValueUpdate(skolem, oldvalue, NULL, toplevelupdateP);
    }
  }
}

boolean hasEquivalentValuesP(Object* term) {
  { Surrogate* testValue000 = safePrimaryType(term);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
      { Object* term000 = term;
        Skolem* term = ((Skolem*)(term000));

        return (((boolean)(((Object*)(accessInContext(term->variableValue, term->homeContext, false))))) ||
            (!(term->variableValueInverse_reader() == NIL)));
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* term001 = term;
        LogicObject* term = ((LogicObject*)(term001));

        return (!(term->variableValueInverse_reader() == NIL));
      }
    }
    else {
      { boolean foundP000 = false;

        { Proposition* prop = NULL;
          Iterator* iter000 = unfilteredDependentPropositions(term, SGT_PROPOSITIONS_PL_KERNEL_KB_EQUIVALENT)->allocateIterator();

          for (; iter000->nextP(); ) {
            prop = ((Proposition*)(iter000->value));
            if ((prop->operatoR == SGT_PROPOSITIONS_PL_KERNEL_KB_EQUIVALENT) &&
                (descriptionModeP() ||
                 ((!prop->deletedP()) &&
                  ((oREVERSEPOLARITYpo ? falseP(prop) : (trueP(prop) ||
                functionWithDefinedValueP(prop))))))) {
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
}

Cons* getVariableValueInverses(Object* term) {
  { Cons* equivs = NIL;

    if (subtypeOfP(safePrimaryType(term), SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* term000 = term;
        LogicObject* term = ((LogicObject*)(term000));

        equivs = term->variableValueInverse_reader();
      }
    }
    else {
      { Proposition* prop = NULL;
        Iterator* iter000 = unfilteredDependentPropositions(term, SGT_PROPOSITIONS_PL_KERNEL_KB_EQUIVALENT)->allocateIterator();

        for (; iter000->nextP(); ) {
          prop = ((Proposition*)(iter000->value));
          if ((prop->operatoR == SGT_PROPOSITIONS_PL_KERNEL_KB_EQUIVALENT) &&
              (descriptionModeP() ||
               ((!prop->deletedP()) &&
                ((oREVERSEPOLARITYpo ? falseP(prop) : (trueP(prop) ||
              functionWithDefinedValueP(prop))))))) {
            { Object* arg = NULL;
              Vector* vector000 = prop->arguments;
              int index000 = 0;
              int length000 = vector000->length();
              Cons* collect000 = NULL;

              for  (; index000 < length000; 
                    index000 = index000 + 1) {
                arg = (vector000->theArray)[index000];
                if ((!eqlP(arg, term)) &&
                    (!equivs->memberP(arg))) {
                  if (!((boolean)(collect000))) {
                    {
                      collect000 = cons(arg, NIL);
                      if (equivs == NIL) {
                        equivs = collect000;
                      }
                      else {
                        addConsToEndOfConsList(equivs, collect000);
                      }
                    }
                  }
                  else {
                    {
                      collect000->rest = cons(arg, NIL);
                      collect000 = collect000->rest;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    return (equivs);
  }
}

Cons* getAllVariableValueInverses(Object* term) {
  { Cons* equivs = NIL;
    Cons* seeds = cons(term, NIL);
    Cons* newequivs = NIL;

    while (!(seeds == NIL)) {
      { Object* seed = NULL;
        Cons* iter000 = seeds;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          seed = iter000->value;
          { Object* equiv = NULL;
            Cons* iter001 = getVariableValueInverses(seed);
            Cons* collect000 = NULL;

            for  (; !(iter001 == NIL); 
                  iter001 = iter001->rest) {
              equiv = iter001->value;
              if (!equivs->memberP(equiv)) {
                equivs = cons(equiv, equivs);
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(equiv, NIL);
                    if (newequivs == NIL) {
                      newequivs = collect000;
                    }
                    else {
                      addConsToEndOfConsList(newequivs, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(equiv, NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
          }
        }
      }
      seeds = newequivs;
      newequivs = NIL;
    }
    return (equivs);
  }
}

Cons* getAllEquivalentValues(Object* term) {
  { Object* rep = valueOf(term);

    if (eqlP(rep, term)) {
      return (getAllVariableValueInverses(rep));
    }
    else {
      return (cons(rep, getAllVariableValueInverses(rep)->remove(term)));
    }
  }
}

void constrainAsSubset(Proposition* prop, Collection* set1, Collection* set2) {
  if (set1->length() > set2->length()) {
    signalUnificationClash(prop, set1, set2);
  }
  { Cons* copy1 = NIL;
    Cons* copy2 = NIL;

    { Object* i2 = NULL;
      Iterator* iter000 = ((Iterator*)(set2->allocateIterator()));

      for (; iter000->nextP(); ) {
        i2 = iter000->value;
        copy2 = cons(i2, copy2);
      }
    }
    { Object* i1 = NULL;
      Iterator* iter001 = ((Iterator*)(set1->allocateIterator()));

      for (; iter001->nextP(); ) {
        i1 = iter001->value;
        if (copy2->memberP(i1)) {
          copy2 = copy2->remove(i1);
        }
        else {
          copy1 = cons(i1, copy1);
        }
      }
    }
    if (copy1 == NIL) {
      return;
    }
    if (copy2->length() == 1) {
      { Object* item1 = copy1->value;
        Object* item2 = copy2->value;

        equateValues(prop, item1, item2);
        return;
      }
    }
    { int skolemcount1 = 0;
      int skolemcount2 = 0;

      { Object* i1 = NULL;
        Cons* iter002 = copy1;

        for (; !(iter002 == NIL); iter002 = iter002->rest) {
          i1 = iter002->value;
          if (skolemP(i1)) {
            skolemcount1 = skolemcount1 + 1;
          }
        }
      }
      { Object* i2 = NULL;
        Cons* iter003 = copy2;

        for (; !(iter003 == NIL); iter003 = iter003->rest) {
          i2 = iter003->value;
          if (skolemP(i2)) {
            skolemcount2 = skolemcount2 + 1;
          }
        }
      }
      if ((skolemcount1 + skolemcount2) == 0) {
        signalUnificationClash(prop, set1, set2);
      }
    }
  }
}

void equateCollections(Proposition* prop, Collection* col1, Collection* col2) {
  if (col1->orderedP() &&
      col2->orderedP()) {
    { Object* i1 = NULL;
      Iterator* iter000 = ((Iterator*)(col1->allocateIterator()));
      Object* i2 = NULL;
      Iterator* iter001 = ((Iterator*)(col2->allocateIterator()));

      for  (; iter000->nextP() &&
                iter001->nextP(); ) {
        i1 = iter000->value;
        i2 = iter001->value;
        equateValues(prop, i1, i2);
      }
    }
    return;
  }
  if (col1->noDuplicatesP() &&
      col2->noDuplicatesP()) {
    constrainAsSubset(prop, col1, col2);
    constrainAsSubset(prop, col2, col1);
  }
}

boolean logicCollectionP(Object* term) {
  return (testTypeOnInstanceP(term, SGT_PROPOSITIONS_STELLA_COLLECTION));
}

void equateValues(Proposition* prop, Object* term1, Object* term2) {
  if (eqlP(term1, term2)) {
  }
  else if (skolemP(term1)) {
    bindSkolemToValue(((Skolem*)(term1)), term2, false);
  }
  else if (skolemP(term2)) {
    bindSkolemToValue(((Skolem*)(term2)), term1, false);
  }
  else if (stellaCollectionP(term1) &&
      stellaCollectionP(term2)) {
    equateCollections(prop, ((Collection*)(term1)), ((Collection*)(term2)));
  }
  else if (isaP(term1, SGT_PROPOSITIONS_PL_KERNEL_KB_INTERVAL_CACHE) &&
      isaP(term2, SGT_PROPOSITIONS_PL_KERNEL_KB_INTERVAL_CACHE)) {
    pl_kernel_kb::unifyIntervalCaches(((pl_kernel_kb::IntervalCache*)(term1)), ((pl_kernel_kb::IntervalCache*)(term2)), SGT_PROPOSITIONS_PL_KERNEL_KB_ge);
    pl_kernel_kb::unifyIntervalCaches(((pl_kernel_kb::IntervalCache*)(term2)), ((pl_kernel_kb::IntervalCache*)(term1)), SGT_PROPOSITIONS_PL_KERNEL_KB_ge);
  }
  else {
    signalUnificationClash(prop, term1, term2);
  }
}

Cons* Skolem::conflictingDefaultValues_reader() {
  { Skolem* self = this;

    { Cons* answer = ((Cons*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_CONFLICTING_DEFAULT_VALUES, NULL)));

      if (!((boolean)(answer))) {
        return (NIL);
      }
      else {
        return (answer);
      }
    }
  }
}

boolean unequateConflictingDefaultValuesP(Proposition* newequatingprop) {
  { Vector* arguments = newequatingprop->arguments;
    Object* firstarg = (arguments->theArray)[0];
    boolean firstargisskolemP = skolemP(firstarg);
    Object* firstargvalue = innermostOf(firstarg);
    Object* secondarg = (arguments->theArray)[1];
    boolean secondargisskolemP = skolemP(secondarg);
    Object* secondargvalue = innermostOf(secondarg);
    boolean newisdefaultP = defaultTrueP(newequatingprop);
    Object* newtruthvalue = NULL;
    Proposition* equatingprop = NULL;

    if (eqlP(firstargvalue, secondargvalue)) {
      return (true);
    }
    else if (skolemP(firstargvalue)) {
      if ((((Skolem*)(firstargvalue))->conflictingDefaultValues_reader() == NIL) ||
          (!newisdefaultP)) {
        return (true);
      }
      else {
        return (false);
      }
    }
    else if (skolemP(secondargvalue)) {
      if ((((Skolem*)(secondargvalue))->conflictingDefaultValues_reader() == NIL) ||
          (!newisdefaultP)) {
        return (true);
      }
      else {
        return (false);
      }
    }
    if (firstargisskolemP &&
        (secondargisskolemP &&
         newisdefaultP)) {
      { OutputStringStream* stream000 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream000->nativeStream) << "ERROR: " << "Equating two skolems " << "`" << firstarg << "'" << " and " << "`" << secondarg << "'" << " by default is not yet supported." << std::endl << "." << std::endl;
          helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
        }
        throw *newPropositionError(stream000->theStringReader());
      }
    }
    newtruthvalue = newequatingprop->truthValue;
    newequatingprop->truthValue = NULL;
    if (firstargisskolemP) {
      { 
        BIND_STELLA_SPECIAL(oDONTUSEDEFAULTKNOWLEDGEpo, boolean, true);
        equatingprop = findEquatingProposition(firstargvalue, ((LogicObject*)(firstarg)));
      }
      if (!((boolean)(equatingprop))) {
        equatingprop = findEquatingProposition(firstargvalue, ((LogicObject*)(firstarg)));
        while (!eqlP(valueOf(firstarg), firstargvalue)) {
          firstarg = valueOf(firstarg);
        }
        { Skolem* skolem = ((Skolem*)(firstarg));

          { Skolem* object000 = skolem;
            Object* value000 = NULL;
            Object* oldValue001 = object000->variableValue;
            Object* newValue000 = updateInContext(oldValue001, value000, object000->homeContext, false);

            if (!(((boolean)(oldValue001)) &&
                (oldValue001->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
              object000->variableValue = newValue000;
            }
          }
          setDynamicSlotValue(skolem->dynamicSlots, SYM_PROPOSITIONS_LOGIC_CONFLICTING_DEFAULT_VALUES, cons(equatingprop, skolem->conflictingDefaultValues_reader()), NULL);
          if (newisdefaultP) {
            setDynamicSlotValue(skolem->dynamicSlots, SYM_PROPOSITIONS_LOGIC_CONFLICTING_DEFAULT_VALUES, cons(newequatingprop, skolem->conflictingDefaultValues_reader()), NULL);
          }
        }
      }
    }
    if (secondargisskolemP) {
      { 
        BIND_STELLA_SPECIAL(oDONTUSEDEFAULTKNOWLEDGEpo, boolean, true);
        equatingprop = findEquatingProposition(secondargvalue, ((LogicObject*)(secondarg)));
      }
      if (!((boolean)(equatingprop))) {
        equatingprop = findEquatingProposition(firstargvalue, ((LogicObject*)(firstarg)));
        while (!eqlP(valueOf(secondarg), secondargvalue)) {
          secondarg = valueOf(secondarg);
        }
        { Skolem* skolem = ((Skolem*)(secondarg));

          { Skolem* object001 = skolem;
            Object* value001 = NULL;
            Object* oldValue002 = object001->variableValue;
            Object* newValue001 = updateInContext(oldValue002, value001, object001->homeContext, false);

            if (!(((boolean)(oldValue002)) &&
                (oldValue002->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
              object001->variableValue = newValue001;
            }
          }
          setDynamicSlotValue(skolem->dynamicSlots, SYM_PROPOSITIONS_LOGIC_CONFLICTING_DEFAULT_VALUES, cons(equatingprop, skolem->conflictingDefaultValues_reader()), NULL);
          if (newisdefaultP) {
            setDynamicSlotValue(skolem->dynamicSlots, SYM_PROPOSITIONS_LOGIC_CONFLICTING_DEFAULT_VALUES, cons(newequatingprop, skolem->conflictingDefaultValues_reader()), NULL);
          }
        }
      }
    }
    newequatingprop->truthValue = ((TruthValue*)(newtruthvalue));
    return (((!firstargisskolemP) &&
        (!secondargisskolemP)) ||
        (!newisdefaultP));
  }
}

boolean unequateValuesP(Object* term1, Object* term2) {
  if (subtypeOfP(safePrimaryType(term1), SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
    { Object* term1000 = term1;
      Skolem* term1 = ((Skolem*)(term1000));

      if (eqlP(((Object*)(accessInContext(term1->variableValue, term1->homeContext, false))), term2)) {
        unbindSkolemValue(term1, false);
        return (true);
      }
    }
  }
  else {
  }
  return (false);
}

void bindToEquivalentValue(LogicObject* from, Description* to) {
  if (from == to) {
    return;
  }
  if (subtypeOfP(safePrimaryType(from), SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
    { LogicObject* from000 = from;
      Skolem* from = ((Skolem*)(from000));

      { Skolem* object000 = from;
        Object* value000 = to;
        Object* oldValue000 = object000->variableValue;
        Object* newValue000 = updateInContext(oldValue000, value000, object000->homeContext, false);

        if (!(((boolean)(oldValue000)) &&
            (oldValue000->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
          object000->variableValue = newValue000;
        }
      }
    }
  }
  else {
    if (((Description*)(accessInContext(dynamicSlotValue(from->dynamicSlots, SYM_PROPOSITIONS_LOGIC_EQUIVALENT_VALUE, NULL), from->homeContext, false))) == to) {
      return;
    }
    { LogicObject* object001 = from;
      Description* value001 = to;
      Object* oldValue002 = dynamicSlotValue(object001->dynamicSlots, SYM_PROPOSITIONS_LOGIC_EQUIVALENT_VALUE, NULL);
      Object* newValue001 = updateInContext(oldValue002, value001, object001->homeContext, false);

      if (!(((boolean)(oldValue002)) &&
          (oldValue002->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
        setDynamicSlotValue(object001->dynamicSlots, SYM_PROPOSITIONS_LOGIC_EQUIVALENT_VALUE, newValue001, NULL);
      }
    }
  }
  { Description* object002 = to;
    Cons* value002 = cons(from, from->variableValueInverse_reader());
    Object* oldValue003 = object002->variableValueInverse;
    Object* newValue002 = updateInContext(oldValue003, value002, object002->homeContext, false);

    if (!(((boolean)(oldValue003)) &&
        (oldValue003->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
      object002->variableValueInverse = newValue002;
    }
  }
}

void unbindEquivalentValue(LogicObject* self) {
  if (subtypeOfP(safePrimaryType(self), SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
    { LogicObject* self000 = self;
      Skolem* self = ((Skolem*)(self000));

      unbindSkolemValue(self, false);
    }
  }
  else {
    unlinkEquivalentValue(self);
    handleOutOfDateInferenceCache(KWD_PROPOSITIONS_RETRACT, NULL);
  }
}

void unlinkEquivalentValue(LogicObject* self) {
  { Object* oldvalue = NULL;

    if (subtypeOfP(safePrimaryType(self), SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
      { LogicObject* self000 = self;
        Skolem* self = ((Skolem*)(self000));

        oldvalue = valueOf(self);
        { Skolem* object000 = self;
          Object* value000 = NULL;
          Object* oldValue000 = object000->variableValue;
          Object* newValue000 = updateInContext(oldValue000, value000, object000->homeContext, false);

          if (!(((boolean)(oldValue000)) &&
              (oldValue000->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
            object000->variableValue = newValue000;
          }
        }
      }
    }
    else {
      oldvalue = equivalentValueOf(self);
      { LogicObject* object001 = self;
        Description* value001 = NULL;
        Object* oldValue001 = dynamicSlotValue(object001->dynamicSlots, SYM_PROPOSITIONS_LOGIC_EQUIVALENT_VALUE, NULL);
        Object* newValue001 = updateInContext(oldValue001, value001, object001->homeContext, false);

        if (!(((boolean)(oldValue001)) &&
            (oldValue001->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
          setDynamicSlotValue(object001->dynamicSlots, SYM_PROPOSITIONS_LOGIC_EQUIVALENT_VALUE, newValue001, NULL);
        }
      }
    }
    if (subtypeOfP(safePrimaryType(oldvalue), SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* oldvalue000 = oldvalue;
        LogicObject* oldvalue = ((LogicObject*)(oldvalue000));

        if (((LogicObject*)(oldvalue->variableValueInverse_reader()->value)) == self) {
          { LogicObject* object002 = oldvalue;
            Cons* value002 = oldvalue->variableValueInverse_reader()->rest;
            Object* oldValue002 = object002->variableValueInverse;
            Object* newValue002 = updateInContext(oldValue002, value002, object002->homeContext, false);

            if (!(((boolean)(oldValue002)) &&
                (oldValue002->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
              object002->variableValueInverse = newValue002;
            }
          }
        }
        else {
          { LogicObject* object003 = oldvalue;
            Cons* value003 = copyConsList(oldvalue->variableValueInverse_reader())->remove(self);
            Object* oldValue003 = object003->variableValueInverse;
            Object* newValue003 = updateInContext(oldValue003, value003, object003->homeContext, false);

            if (!(((boolean)(oldValue003)) &&
                (oldValue003->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
              object003->variableValueInverse = newValue003;
            }
          }
        }
      }
    }
    else {
    }
  }
}

int equivalentCollectionPriority(LogicObject* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
      { LogicObject* self000 = self;
        NamedDescription* self = ((NamedDescription*)(self000));

        return (1);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) {
      { LogicObject* self001 = self;
        Description* self = ((Description*)(self001));

        return (2);
      }
    }
    else {
      return (0);
    }
  }
}

// Experiment with equality reasoning on collections.
boolean oEQUIVALENCE_COLLECTIONSpo = true;

void equivalenceCollections(LogicObject* collection1, LogicObject* collection2) {
  if (!oEQUIVALENCE_COLLECTIONSpo) {
    return;
  }
  { Object* value1 = equivalentValueOf(valueOf(collection1));
    Object* value2 = equivalentValueOf(valueOf(collection2));

    if (equivalentCollectionPriority(((LogicObject*)(value1))) > equivalentCollectionPriority(((LogicObject*)(value2)))) {
      bindToEquivalentValue(((LogicObject*)(value2)), ((Description*)(value1)));
    }
    else {
      bindToEquivalentValue(((LogicObject*)(value1)), ((Description*)(value2)));
    }
  }
}

void reviseEquivalences(Proposition* proposition, boolean goestrueP) {
  { LogicObject* arg1 = ((LogicObject*)((proposition->arguments->theArray)[0]));
    LogicObject* arg2 = ((LogicObject*)((proposition->arguments->theArray)[1]));

    if (!oEQUIVALENCE_COLLECTIONSpo) {
      return;
    }
    if (goestrueP) {
      if (collectionImpliesCollectionP(arg1, arg2) &&
          collectionImpliesCollectionP(arg2, arg1)) {
        equivalenceCollections(arg1, arg2);
      }
    }
    else if (((boolean)(((Description*)(accessInContext(dynamicSlotValue(arg1->dynamicSlots, SYM_PROPOSITIONS_LOGIC_EQUIVALENT_VALUE, NULL), arg1->homeContext, false))))) ||
        ((boolean)(((Description*)(accessInContext(dynamicSlotValue(arg2->dynamicSlots, SYM_PROPOSITIONS_LOGIC_EQUIVALENT_VALUE, NULL), arg2->homeContext, false)))))) {
      std::cout << "DIDN'T FINISH 'revise-equivalences' YET. DON'T KNOW HOW" << std::endl << "   TO REMOVE AN 'equivalent-value' LINK" << std::endl;
    }
    else if ((isaP(arg1, SGT_PROPOSITIONS_LOGIC_SKOLEM) &&
        ((boolean)(((Object*)(accessInContext(((Skolem*)(arg1))->variableValue, ((Skolem*)(arg1))->homeContext, false)))))) ||
        (isaP(arg2, SGT_PROPOSITIONS_LOGIC_SKOLEM) &&
         ((boolean)(((Object*)(accessInContext(((Skolem*)(arg2))->variableValue, ((Skolem*)(arg2))->homeContext, false))))))) {
      std::cout << "DIDN'T FINISH 'revise-equivalences' YET. DON'T KNOW HOW" << std::endl << "   TO REMOVE AN 'equivalent-value' LINK" << std::endl;
    }
  }
}

Proposition* findEquatingProposition(Object* directobject, LogicObject* indirectobject) {
  { Object* indirectobjectvalue = valueOf(indirectobject);
    Object* backlinkedindirectobject = indirectobjectvalue;

    if (!isaP(backlinkedindirectobject, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      backlinkedindirectobject = indirectobject;
    }
    { Proposition* value000 = NULL;

      { Proposition* prop = NULL;
        Iterator* iter000 = ((Iterator*)((descriptionModeP() ? unfilteredDependentPropositions(backlinkedindirectobject, SGT_PROPOSITIONS_PL_KERNEL_KB_EQUIVALENT)->allocateIterator() : allTrueDependentPropositions(backlinkedindirectobject, SGT_PROPOSITIONS_PL_KERNEL_KB_EQUIVALENT, false))));

        for (; iter000->nextP(); ) {
          prop = ((Proposition*)(iter000->value));
          if ((prop->operatoR == SGT_PROPOSITIONS_PL_KERNEL_KB_EQUIVALENT) &&
              ((eqlP((prop->arguments->theArray)[0], directobject) &&
              eqlP(valueOf((prop->arguments->theArray)[1]), indirectobjectvalue)) ||
               (eqlP((prop->arguments->theArray)[1], directobject) &&
                eqlP(valueOf((prop->arguments->theArray)[0]), indirectobjectvalue)))) {
            value000 = prop;
            break;
          }
        }
      }
      { Proposition* value001 = value000;

        return (value001);
      }
    }
  }
}

Proposition* TRUE_PROPOSITION = NULL;

Proposition* FALSE_PROPOSITION = NULL;

boolean constantPropositionP(Proposition* self) {
  // Return true if `self' is a constant such as TRUE or FALSE.
  return (self->kind == KWD_PROPOSITIONS_CONSTANT);
}

Object* evaluateTerm(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_LITERAL_WRAPPER)) {
      { Object* self000 = self;
        LiteralWrapper* self = ((LiteralWrapper*)(self000));

        return (evaluateLiteralWrapperTerm(self));
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* self001 = self;
        Surrogate* self = ((Surrogate*)(self001));

        return (evaluateSurrogateTerm(self));
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* self002 = self;
        Symbol* self = ((Symbol*)(self002));

        return (evaluateSymbolTerm(self));
      }
    }
    else if (testValue000 == SGT_PROPOSITIONS_STELLA_CONS) {
      { Object* self003 = self;
        Cons* self = ((Cons*)(self003));

        { GeneralizedSymbol* testValue001 = ((GeneralizedSymbol*)(self->value));

          if ((testValue001 == SYM_PROPOSITIONS_LOGIC_SETOFALL) ||
              ((testValue001 == SYM_PROPOSITIONS_LOGIC_THE_ONLY) ||
               (testValue001 == SYM_PROPOSITIONS_LOGIC_KAPPA))) {
            return (evaluateLogicObjectTerm(evaluateDescriptionTerm(self, true)));
          }
          else if (testValue001 == SYM_PROPOSITIONS_LOGIC_CREATE) {
            return (evaluateCreateTerm(self));
          }
          else {
            return (evaluateFunctionTerm(self));
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* self004 = self;
        LogicObject* self = ((LogicObject*)(self004));

        return (evaluateLogicObjectTerm(self));
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
      { Object* self005 = self;
        Proposition* self = ((Proposition*)(self005));

        return (self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_THING)) {
      { Object* self006 = self;
        Thing* self = ((Thing*)(self006));

        return (self);
      }
    }
    else if (subtypeOfKeywordP(testValue000)) {
      { Object* self007 = self;
        Keyword* self = ((Keyword*)(self007));

        return (self);
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't evaluate the term " << "`" << self << "'";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Object* evaluateLiteralWrapperTerm(LiteralWrapper* self) {
  if (oBACKLINK_ALL_PROPOSITION_ARGUMENTSpo) {
    return (rewrapArgument(self));
  }
  else {
    return (self);
  }
}

Object* evaluateSurrogateTerm(Surrogate* self) {
  if (oEVALUATIONMODEo == KWD_PROPOSITIONS_EXTENSIONAL_ASSERTION) {
    { Object* value = self->surrogateValue;
      ObjectStore* store = NULL;

      if (((boolean)(value))) {
        if (subtypeOfP(safePrimaryType(value), SGT_PROPOSITIONS_STELLA_RELATION)) {
          { Object* value000 = value;
            Relation* value = ((Relation*)(value000));

            return (getDescription(self));
          }
        }
        else {
          return (value);
        }
      }
      else {
        self = coerceToBoundOrLocalSurrogate(self);
        store = homeObjectStore(self);
        if (((boolean)(store))) {
          store->fetchInstance(self);
        }
        if (!((boolean)(self->surrogateValue))) {
          createLogicInstance(self, NULL);
        }
        return (self->surrogateValue);
      }
    }
  }
  else if (oEVALUATIONMODEo == KWD_PROPOSITIONS_DESCRIPTION) {
    { Object* surrogatevalue = self->surrogateValue;
      ObjectStore* store = NULL;

      if (!((boolean)(surrogatevalue))) {
        self = coerceToBoundOrLocalSurrogate(self);
        store = homeObjectStore(self);
        if (((boolean)(store))) {
          store->fetchInstance(self);
        }
        if (!((boolean)(self->surrogateValue))) {
          createLogicInstance(self, NULL);
        }
        return (self);
      }
      else if (isaP(surrogatevalue, SGT_PROPOSITIONS_STELLA_LITERAL_WRAPPER)) {
        return (surrogatevalue);
      }
      else {
        return (self);
      }
    }
  }
  else if (oEVALUATIONMODEo == KWD_PROPOSITIONS_INTENSIONAL_ASSERTION) {
    { Object* directvalue = self->surrogateValue;
      Skolem* intensionalskolem = NULL;

      if (skolemP(directvalue)) {
        return (directvalue);
      }
      intensionalskolem = createSkolem((((boolean)(directvalue)) ? logicalType(valueOf(directvalue)) : NULL), NULL);
      self->surrogateValue = intensionalskolem;
      bindSkolemToValue(intensionalskolem, directvalue, false);
      return (intensionalskolem);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << oEVALUATIONMODEo << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Object* evaluateLogicObjectTerm(LogicObject* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE)) {
      { LogicObject* self000 = self;
        PatternVariable* self = ((PatternVariable*)(self000));

        return (self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
      { LogicObject* self001 = self;
        Skolem* self = ((Skolem*)(self001));

        return (self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) {
      { LogicObject* self002 = self;
        Description* self = ((Description*)(self002));

        if (descriptionModeP()) {
          { Surrogate* name = self->surrogateValueInverse;

            if (((boolean)(name))) {
              return (name);
            }
          }
        }
        return (self);
      }
    }
    else {
      if (descriptionModeP()) {
        { Surrogate* name = self->surrogateValueInverse;

          if (((boolean)(name))) {
            return (name);
          }
        }
      }
      else {
        return (self);
      }
    }
  }
  { OutputStringStream* stream000 = newOutputStringStream();

    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      *(stream000->nativeStream) << "ERROR: " << "Illegal LOGIC-OBJECT term: " << "`" << self << "'" << "." << std::endl;
      helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
    }
    throw *newPropositionError(stream000->theStringReader());
  }
}

// Variables with name 'ANONYMOUS-VARIABLE-NAME' are considered
// anonymous, and are not assumed to be identical to any other variable also named
// 'ANONYMOUS-VARIABLE-NAME'.
Symbol* ANONYMOUS_VARIABLE_NAME = NULL;

boolean anonymousVariableP(Skolem* self) {
  return ((self->skolemName == ANONYMOUS_VARIABLE_NAME) &&
      variableP(self));
}

Object* evaluateSymbolTerm(Symbol* self) {
  { Object* value = lookupLogicVariableBinding(self);

    if (((boolean)(value))) {
      return (value);
    }
    else if (self == ANONYMOUS_VARIABLE_NAME) {
      return (createVariable(NULL, ANONYMOUS_VARIABLE_NAME, false));
    }
    else if (questionMarkSymbolP(self)) {
      { OutputStringStream* stream000 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream000->nativeStream) << "ERROR: " << "Reference to undeclared variable: " << "`" << self << "'" << "." << std::endl;
          helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
        }
        throw *newPropositionError(stream000->theStringReader());
      }
    }
    else if (automaticInstanceSymbolP(self)) {
      return (evaluateAutomaticInstance(self));
    }
    else {
      value = symbolToSurrogate(self)->surrogateValue;
      if (((boolean)(value))) {
        return (value);
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream001->nativeStream) << "ERROR: " << "Reference to undeclared symbol: " << "`" << self << "'" << "." << std::endl;
            helpSignalPropositionError(stream001, KWD_PROPOSITIONS_ERROR);
          }
          throw *newPropositionError(stream001->theStringReader());
        }
      }
    }
  }
}

// Represents a key-value list that should never be used.
KeyValueList* oMISSING_KEY_VALUE_LISTo = NULL;

// Used by 'evaluate-automatic-instance' to
// record current bindings of automatic instance symbols.
DEFINE_STELLA_SPECIAL(oAUTOMATICINSTANCETABLEo, KeyValueList* , NULL);

Object* evaluateAutomaticInstance(Symbol* name) {
  if (oAUTOMATICINSTANCETABLEo == oMISSING_KEY_VALUE_LISTo) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "ERROR: " << "Automatic instance " << "`" << name << "'" << " found outside" << std::endl << "   the scope of an assertion." << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
      }
      throw *newPropositionError(stream000->theStringReader());
    }
  }
  { LogicObject* instance = (((boolean)(oAUTOMATICINSTANCETABLEo)) ? ((LogicObject*)(oAUTOMATICINSTANCETABLEo->lookup(name))) : ((LogicObject*)(NULL)));

    if (!((boolean)(instance))) {
      { Surrogate* surrogate = stringToSurrogate(gensym(stringSubsequence(name->symbolName, 1, NULL_INTEGER))->symbolName);

        instance = ((LogicObject*)(createLogicInstance(surrogate, NULL)));
        if (!((boolean)(oAUTOMATICINSTANCETABLEo))) {
          oAUTOMATICINSTANCETABLEo = newKeyValueList();
        }
        oAUTOMATICINSTANCETABLEo->insertAt(name, instance);
      }
    }
    return (evaluateLogicObjectTerm(instance));
  }
}

void signalUndefinedTerm(Object* term) {
  { OutputStringStream* stream000 = newOutputStringStream();

    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      *(stream000->nativeStream) << "ERROR: " << "Reference to undefined term: " << "`" << term << "'" << "." << std::endl;
      helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
    }
    throw *newPropositionError(stream000->theStringReader());
  }
}

void signalUntypedTerm(Object* term) {
  if (!oSUPPRESSUNTYPEDTYPEERRORpo) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "ERROR: " << "Need a type for the untyped term: " << "`" << term << "'" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
      }
      throw *newPropositionError(stream000->theStringReader());
    }
  }
}

Object* evaluateCreateTerm(Cons* term) {
  { Symbol* namesymbol = ((Symbol*)(term->rest->value));
    Surrogate* name = (((boolean)(namesymbol)) ? symbolToSurrogate(namesymbol) : ((Surrogate*)(NULL)));
    Symbol* typesymbol = ((Symbol*)(term->rest->rest->value));
    Surrogate* type = (((boolean)(typesymbol)) ? symbolToSurrogate(typesymbol) : ((Surrogate*)(NULL)));
    Object* term = NULL;

    try {
      term = createLogicInstance(name, type);
    }
    catch (LogicException& _e) {
      LogicException* e = &_e;

      *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
    }
    return (term);
  }
}

Object* create(GeneralizedSymbol* name, Cons* type) {
  // Create a logic object with name 'name' and return it.
  // If `type' is also supplied, assert that the object belongs to that type.
  { Cons* createtree = listO(3, SYM_PROPOSITIONS_LOGIC_CREATE, name, type->concatenate(NIL, 0));
    Object* result = evaluateCreateTerm(createtree);

    return (result);
  }
}

Object* createEvaluatorWrapper(Cons* arguments) {
  return (create(((GeneralizedSymbol*)(arguments->value)), arguments->rest));
}

void updateSkolemType(Skolem* self, Surrogate* type) {
  { Surrogate* oldtype = self->skolemType;

    if ((!((boolean)(oldtype))) ||
        logicalSubtypeOfP(type, oldtype)) {
      self->skolemType = type;
    }
  }
}

void updateSkolemTypeFromIsaAssertions(Proposition* self) {
  { Keyword* testValue000 = self->kind;

    if (testValue000 == KWD_PROPOSITIONS_ISA) {
      { Object* object = (self->arguments->theArray)[0];

        if (isaP(object, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
          updateSkolemType(((Skolem*)(object)), ((Surrogate*)(self->operatoR)));
        }
      }
    }
    else if (testValue000 == KWD_PROPOSITIONS_AND) {
      { Object* arg = NULL;
        Vector* vector000 = self->arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          arg = (vector000->theArray)[index000];
          updateSkolemTypeFromIsaAssertions(((Proposition*)(arg)));
        }
      }
    }
    else {
    }
  }
}

boolean descriptionExtensionL(Description* desc1, Description* desc2) {
  return (getDescriptionExtension(((NamedDescription*)(desc1)), true)->estimatedLength() < getDescriptionExtension(((NamedDescription*)(desc2)), true)->estimatedLength());
}

void printExtensionSizes(Module* module, int sizecutoff) {
  // Print the extension sizes of concepts visible in `module'.
  // If `module' is NULL the current module is used.  Do not report extensions
  // with size less than `sizeCutoff' (default is 10).
  if (sizecutoff == NULL_INTEGER) {
    sizecutoff = 10;
  }
  if (!((boolean)(module))) {
    module = oMODULEo;
  }
  { List* descriptions = newList();
    const char* size = NULL;

    { NamedDescription* d = NULL;
      Iterator* iter000 = allNamedDescriptions(module, false);
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        d = ((NamedDescription*)(iter000->value));
        if (((boolean)(d->extension)) &&
            (d->extension->estimatedLength() >= sizecutoff)) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(d, NIL);
              if (descriptions->theConsList == NIL) {
                descriptions->theConsList = collect000;
              }
              else {
                addConsToEndOfConsList(descriptions->theConsList, collect000);
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
    descriptions->sort(((cpp_function_code)(&descriptionExtensionL)));
    { NamedDescription* desc = NULL;
      Cons* iter001 = descriptions->reverse()->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        desc = ((NamedDescription*)(iter001->value));
        size = integerToString(((long long int)(desc->extension->estimatedLength())));
        size = stringConcatenate(makeString(8 - strlen(size), ' '), size, 0);
        std::cout << size << " : " << desc->descriptionName() << std::endl;
      }
    }
  }
}

void transferLogicInformationFromRelationHook(List* relationslist) {
  { Relation* oldrelation = ((Relation*)(relationslist->first()));
    Relation* newrelation = ((Relation*)(relationslist->second()));
    NamedDescription* olddescription = ((NamedDescription*)(dynamicSlotValue(oldrelation->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTION, NULL)));
    NamedDescription* newdescription = ((NamedDescription*)(dynamicSlotValue(newrelation->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTION, NULL)));

    if (((boolean)(olddescription))) {
      retractRelationAxioms(olddescription);
      if (((boolean)(newdescription))) {
        {
          transferPropositionsAndBacklinks(((NamedDescription*)(dynamicSlotValue(oldrelation->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTION, NULL))), ((NamedDescription*)(dynamicSlotValue(newrelation->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTION, NULL))));
          destroyInstance(olddescription);
        }
      }
      else {
        {
          setDynamicSlotValue(newrelation->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTION, olddescription, NULL);
          olddescription->nativeRelationSetter(newrelation);
          finalizeSuperrelationLinks(newrelation);
        }
      }
      setDynamicSlotValue(oldrelation->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTION, NULL, NULL);
    }
    if (subtypeOfClassP(safePrimaryType(oldrelation))) {
      { Relation* oldrelation000 = oldrelation;
        Class* oldrelation = ((Class*)(oldrelation000));

        setDynamicSlotValue(((Class*)(newrelation))->dynamicSlots, SYM_PROPOSITIONS_STELLA_CLASS_EXTENSION, ((ClassExtension*)(dynamicSlotValue(oldrelation->dynamicSlots, SYM_PROPOSITIONS_STELLA_CLASS_EXTENSION, NULL))), NULL);
        setDynamicSlotValue(oldrelation->dynamicSlots, SYM_PROPOSITIONS_STELLA_CLASS_EXTENSION, NULL, NULL);
      }
    }
    else {
    }
  }
}

void retractRelationAxioms(NamedDescription* oldrelation) {
  { List* originatedpropositions = originatedPropositions(oldrelation);

    if (((boolean)(originatedpropositions))) {
      { Proposition* proposition = NULL;
        Cons* iter000 = originatedpropositions->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          proposition = ((Proposition*)(iter000->value));
          unassertProposition(proposition);
        }
      }
    }
  }
}

Proposition* assertDescriptionImpliesDescription(Description* sub, Description* super, boolean dontupdateP) {
  { Proposition* impliesprop = createImpliesProposition(sub, super);

    impliesprop = fastenDownOneProposition(impliesprop, false);
    if (!(dontupdateP)) {
      updatePropositionTruthValue(impliesprop, KWD_PROPOSITIONS_ASSERT_TRUE);
    }
    return (impliesprop);
  }
}

Proposition* assertImpliesLinkBetweenRelations(NamedDescription* sub, NamedDescription* super) {
  { Proposition* impliesprop = assertDescriptionImpliesDescription(sub, super, true);

    setDynamicSlotValue(impliesprop->dynamicSlots, SYM_PROPOSITIONS_LOGIC_SUBRELATION_LINKp, TRUE_WRAPPER, FALSE_WRAPPER);
    updatePropositionTruthValue(impliesprop, KWD_PROPOSITIONS_ASSERT_TRUE);
    linkOriginatedProposition(sub, impliesprop);
    return (impliesprop);
  }
}

void finalizeSuperrelationLinks(Relation* self) {
  { NamedDescription* subdescription = getDescription(self);

    { 
      BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_PROPOSITIONS_EXTENSIONAL_ASSERTION);
      BIND_STELLA_SPECIAL(oFILLINGCONSTRAINTPROPAGATIONQUEUESpo, boolean, false);
      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, ((Module*)(subdescription->homeContext)));
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        { Relation* super = NULL;
          Iterator* iter000 = directSuperrelations(self);

          for (; iter000->nextP(); ) {
            super = ((Relation*)(iter000->value));
            if (((boolean)(((NamedDescription*)(dynamicSlotValue(super->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTION, NULL)))))) {
              assertImpliesLinkBetweenRelations(subdescription, getDescription(super));
            }
          }
        }
      }
    }
  }
}

Proposition* updateIsaProposition(Object* self, Surrogate* type, Keyword* updatemode) {
  { Proposition* value000 = NULL;

    { Proposition* p = NULL;
      Iterator* iter000 = unfilteredDependentIsaPropositions(self)->allocateIterator();

      for (; iter000->nextP(); ) {
        p = ((Proposition*)(iter000->value));
        if (((Surrogate*)(p->operatoR)) == type) {
          value000 = p;
          break;
        }
      }
    }
    { Proposition* isaproposition = value000;

      if (!((boolean)(isaproposition))) {
        isaproposition = createProposition(SYM_PROPOSITIONS_STELLA_ISA, 1);
        isaproposition->operatoR = type;
        (isaproposition->arguments->theArray)[0] = self;
        fastenDownOneProposition(isaproposition, false);
      }
      updatePropositionTruthValue(isaproposition, updatemode);
      return (isaproposition);
    }
  }
}

Proposition* assertIsaProposition(Object* self, Surrogate* type) {
  if (((boolean)(type))) {
    return (updateIsaProposition(self, type, KWD_PROPOSITIONS_ASSERT_TRUE));
  }
  else {
    return (NULL);
  }
}

Proposition* retractIsaProposition(Object* self, Surrogate* type) {
  if (((boolean)(type))) {
    return (updateIsaProposition(self, type, KWD_PROPOSITIONS_RETRACT_TRUE));
  }
  else {
    return (NULL);
  }
}

Proposition* updateProperty(LogicObject* self, Surrogate* surrogate, Keyword* updatemode) {
  { Proposition* value000 = NULL;

    { Proposition* p = NULL;
      Iterator* iter000 = unfilteredDependentPropositions(self, surrogate)->allocateIterator();

      for (; iter000->nextP(); ) {
        p = ((Proposition*)(iter000->value));
        if ((((Surrogate*)(p->operatoR)) == surrogate) &&
            (p->arguments->length() == 1)) {
          value000 = p;
          break;
        }
      }
    }
    { Proposition* propertyproposition = value000;

      if ((!((boolean)(surrogate))) ||
          (!((boolean)(surrogate->surrogateValue)))) {
        std::cout << "Error: Property " << surrogate << " is not defined." << std::endl;
        return (NULL);
      }
      if (!((boolean)(propertyproposition))) {
        propertyproposition = createProposition(SYM_PROPOSITIONS_STELLA_PREDICATE, 1);
        (propertyproposition->arguments->theArray)[0] = self;
        propertyproposition->operatoR = surrogate;
        fastenDownOneProposition(propertyproposition, false);
      }
      updatePropositionTruthValue(propertyproposition, updatemode);
      return (propertyproposition);
    }
  }
}

Proposition* assertProperty(LogicObject* instance, Surrogate* property) {
  return (updateProperty(instance, property, KWD_PROPOSITIONS_ASSERT_TRUE));
}

Proposition* retractProperty(LogicObject* instance, Surrogate* property) {
  return (updateProperty(instance, property, KWD_PROPOSITIONS_RETRACT_TRUE));
}

Proposition* updateTuple(Surrogate* relation, Cons* arguments, Keyword* updatemode) {
  // Assert or retract a proposition that applies 'relation' to 'arguments'.
  { boolean holdsP = relation == SGT_PROPOSITIONS_PL_KERNEL_KB_HOLDS;
    NamedDescription* description = (holdsP ? getDescription(arguments->value) : getDescription(relation));
    Proposition* proposition = NULL;

    if (holdsP) {
      relation = description->surrogateValueInverse;
      arguments = arguments->rest;
    }
    if (functionDescriptionP(description)) {
      { Proposition* definingproposition = findOrCreateFunctionProposition(relation, arguments->butLast()->consify());

        proposition = updateEquivalenceProposition(createEquivalenceProposition((definingproposition->arguments->theArray)[(definingproposition->arguments->length() - 1)], arguments->last()), updatemode);
        if (!((boolean)(proposition))) {
          return (definingproposition);
        }
      }
    }
    else if (classDescriptionP(description)) {
      return (updateIsaProposition(arguments->value, relation, updatemode));
    }
    else {
      proposition = createProposition(SYM_PROPOSITIONS_STELLA_PREDICATE, arguments->length());
      proposition->operatoR = relation;
      { Object* arg = NULL;
        Cons* iter000 = arguments;
        int i = NULL_INTEGER;
        int iter001 = 0;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          arg = iter000->value;
          i = iter001;
          (proposition->arguments->theArray)[i] = arg;
        }
      }
    }
    proposition = fastenDownOneProposition(proposition, false);
    updatePropositionTruthValue(proposition, updatemode);
    return (proposition);
  }
}

Proposition* assertTuple(Surrogate* relation, Cons* arguments) {
  return (updateTuple(relation, arguments, KWD_PROPOSITIONS_ASSERT_TRUE));
}

Proposition* updateBinaryValue(Surrogate* relation, Object* self, Object* value, Keyword* updatemode) {
  { 
    BIND_STELLA_SPECIAL(oCLIPPINGENABLEDpo, boolean, true);
    if (functionDescriptionP(getDescription(relation))) {
      { Proposition* value000 = NULL;

        { Proposition* p = NULL;
          Iterator* iter000 = unfilteredDependentPropositions(self, relation)->allocateIterator();

          for (; iter000->nextP(); ) {
            p = ((Proposition*)(iter000->value));
            if (((Surrogate*)(p->operatoR)) == relation) {
              value000 = p;
              break;
            }
          }
        }
        { Proposition* proposition = value000;

          if ((!((boolean)(proposition))) ||
              skolemP(value)) {
            return (updateTuple(relation, consList(2, self, value), updatemode));
          }
          { Object* skolemoutput = (proposition->arguments->theArray)[(proposition->arguments->length() - 1)];

            if (updatemode == KWD_PROPOSITIONS_ASSERT_TRUE) {
              if (clipValueP(skolemoutput, value)) {
              }
              else {
                equateValues(proposition, valueOf(skolemoutput), valueOf(value));
              }
            }
            else if (updatemode == KWD_PROPOSITIONS_RETRACT_TRUE) {
              unequateValuesP(skolemoutput, value);
            }
            else {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "`" << updatemode << "'" << " is not a valid case option";
                throw *newStellaException(stream000->theStringReader());
              }
            }
            return (proposition);
          }
        }
      }
    }
    else {
      return (updateTuple(relation, consList(2, self, value), updatemode));
    }
  }
}

Proposition* assertBinaryValue(Surrogate* relation, Object* self, Object* value) {
  return (updateBinaryValue(relation, self, value, KWD_PROPOSITIONS_ASSERT_TRUE));
}

Proposition* retractBinaryValue(Surrogate* relation, Object* self, Object* value) {
  return (updateBinaryValue(relation, self, value, KWD_PROPOSITIONS_RETRACT_TRUE));
}

Proposition* assertMemberOfProposition(Object* self, Object* collection) {
  if (!((boolean)(collection))) {
    return (NULL);
  }
  if (subtypeOfP(safePrimaryType(collection), SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
    { Object* collection000 = collection;
      NamedDescription* collection = ((NamedDescription*)(collection000));

      if (collection->surrogateValueInverse == SGT_PROPOSITIONS_STELLA_THING) {
        return (NULL);
      }
      return (assertIsaProposition(self, collection->surrogateValueInverse));
    }
  }
  else {
    return (assertTuple(SGT_PROPOSITIONS_PL_KERNEL_KB_MEMBER_OF, consList(2, self, collection)));
  }
}

DEFINE_STELLA_SPECIAL(oDEFAULTCREATIONTYPEo, Surrogate* , NULL);

ObjectAlreadyExistsException* newObjectAlreadyExistsException(const char* message) {
  { ObjectAlreadyExistsException* self = NULL;

    self = new ObjectAlreadyExistsException(message);
    self->existingObject = NULL;
    return (self);
  }
}

Object* helpCreateLogicInstance(Surrogate* name, Surrogate* type) {
  enforceCodeOnly();
  if (!((boolean)(type))) {
    type = oDEFAULTCREATIONTYPEo;
  }
  { NamedDescription* description = (((boolean)(type)) ? getDescription(type) : ((NamedDescription*)(NULL)));
    Class* nativeclass = NULL;
    Object* newobject = NULL;

    if (((boolean)(type)) &&
        (!((boolean)(description)))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Can't create an instance of the undefined class " << "`" << type->symbolName << "'";
        throw *newUndefinedClassException(stream000->theStringReader());
      }
    }
    if (!((boolean)(description))) {
      newobject = newLogicObject();
    }
    else {
      {
        if (!classDescriptionP(description)) {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "Can't create an instance of a relation: " << "`" << type->symbolName << "'";
            throw *newObjectNotClassException(stream001->theStringReader());
          }
        }
        nativeclass = ((Class*)(description->nativeRelation()));
        if ((!((boolean)(nativeclass))) ||
            nativeclass->abstractP) {
          newobject = newLogicObject();
        }
        else if (subtypeOfP(nativeclass->classType, SGT_PROPOSITIONS_STELLA_THING)) {
          newobject = createObject(type, 0);
        }
        else {
          { OutputStringStream* stream002 = newOutputStringStream();

            *(stream002->nativeStream) << "Can't create an instance of the class " << "`" << type->symbolName << "'" << std::endl << "   because it doesn't inherit the class 'THING'.";
            throw *newBadArgumentException(stream002->theStringReader());
          }
        }
      }
    }
    if (((boolean)(name))) {
      if (((boolean)(name->surrogateValue))) {
        { ObjectAlreadyExistsException* self008 = newObjectAlreadyExistsException(stringConcatenate("An object named ", name->symbolName, 1, " already exists."));

          self008->existingObject = name->surrogateValue;
          { ObjectAlreadyExistsException* error = self008;

            throw *error;
          }
        }
      }
      name->surrogateValue = newobject;
      { Surrogate* testValue000 = safePrimaryType(newobject);

        if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
          { Object* newobject000 = newobject;
            LogicObject* newobject = ((LogicObject*)(newobject000));

            newobject->surrogateValueInverse = name;
          }
        }
        else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_THING)) {
          { Object* newobject001 = newobject;
            Thing* newobject = ((Thing*)(newobject001));

            newobject->surrogateValueInverse = name;
          }
        }
        else {
          { OutputStringStream* stream003 = newOutputStringStream();

            *(stream003->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream003->theStringReader());
          }
        }
      }
    }
    return (newobject);
  }
}

Object* createLogicInstance(Surrogate* name, Surrogate* type) {
  try {
    return (helpCreateLogicInstance(name, type));
  }
  catch (UndefinedClassException& _undefined) {
    UndefinedClassException* undefined = &_undefined;

    std::cout << "`" << exceptionMessage(undefined) << "'" << std::endl;
    return (NULL);
  }
  catch (ObjectNotClassException& _noClass) {
    ObjectNotClassException* noClass = &_noClass;

    std::cout << "`" << exceptionMessage(noClass) << "'" << std::endl;
    return (NULL);
  }
  catch (BadArgumentException& _badArg) {
    BadArgumentException* badArg = &_badArg;

    std::cout << "`" << exceptionMessage(badArg) << "'" << std::endl;
    return (NULL);
  }
  catch (ObjectAlreadyExistsException& _exists) {
    ObjectAlreadyExistsException* exists = &_exists;

    std::cout << exceptionMessage(exists) << std::endl << "Redefining the surrogate " << name->symbolName << " will cause the existing" << std::endl << "   object named " << name->symbolName << " to be destroyed. ";
    if (yOrNP("Do it? ")) {
      {
        destroyInstance(exists->existingObject);
        return (helpCreateLogicInstance(name, type));
      }
    }
    else {
      {
        std::cout << "Returning existing object:" << std::endl;
        return (exists->existingObject);
      }
    }
  }
}

// Contains a table of propositions and descriptions, indexed by a
// structure hash code which might be shared by different objects.
KeyValueMap* oSTRUCTURED_OBJECTS_INDEXo = NULL;

void cleanupStructuredObjectsIndex(Module* clearmodule) {
  { IntegerWrapper* key = NULL;
    List* bucket = NULL;
    DictionaryIterator* iter000 = ((DictionaryIterator*)(oSTRUCTURED_OBJECTS_INDEXo->allocateIterator()));

    for  (; iter000->nextP(); ) {
      key = ((IntegerWrapper*)(iter000->key));
      bucket = ((List*)(iter000->value));
      { ContextSensitiveObject* obj = NULL;
        Cons* iter001 = bucket->theConsList;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          obj = ((ContextSensitiveObject*)(iter001->value));
          { Context* context = obj->homeContext;

            if (((boolean)(context)) &&
                (context->deletedP() ||
                 ((context == clearmodule) ||
                  context->allSuperContexts->membP(clearmodule)))) {
              destroyObject(obj);
            }
          }
        }
      }
      bucket->removeDeletedMembers();
      if (bucket->emptyP()) {
        oSTRUCTURED_OBJECTS_INDEXo->removeAt(key);
      }
    }
  }
}

int propositionHashIndex(Proposition* self, KeyValueMap* mapping, boolean derefsurrogatesP) {
  { boolean mappedP = ((boolean)(mapping));
    int code = (size_t)(self->operatoR);
    Vector* arguments = self->arguments;
    Object* functionoutput = ((mappedP &&
        (self->kind == KWD_PROPOSITIONS_FUNCTION)) ? arguments->last() : ((Object*)(NULL)));
    Object* priorarg = NULL;
    int argcode = 0;
    boolean commutativeP = false;

    { Keyword* testValue000 = self->kind;

      if ((testValue000 == KWD_PROPOSITIONS_AND) ||
          ((testValue000 == KWD_PROPOSITIONS_OR) ||
           (testValue000 == KWD_PROPOSITIONS_EQUIVALENT))) {
        commutativeP = true;
      }
      else {
      }
    }
    { Object* arg = NULL;
      Vector* vector000 = arguments;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter000 = 0;

      for  (; index000 < length000; 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        arg = (vector000->theArray)[index000];
        i = iter000;
        if (mappedP) {
          if (eqlP(arg, functionoutput)) {
            arg = NULL;
          }
          else {
            arg = mappedValueOf(arg, mapping, false);
          }
        }
        if (((boolean)(oQUERYITERATORo)) &&
            variableP(arg)) {
          { Object* temp000 = safeBoundTo(((PatternVariable*)(arg)));

            arg = (((boolean)(temp000)) ? temp000 : arg);
          }
        }
        if (!((boolean)(arg))) {
          argcode = (size_t)SGT_PROPOSITIONS_LOGIC_SKOLEM;
        }
        else {
          { Surrogate* testValue001 = safePrimaryType(arg);

            if (subtypeOfP(testValue001, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
              { Object* arg000 = arg;
                Proposition* arg = ((Proposition*)(arg000));

                argcode = propositionHashIndex(arg, mapping, derefsurrogatesP);
              }
            }
            else if (subtypeOfP(testValue001, SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
              { Object* arg001 = arg;
                NamedDescription* arg = ((NamedDescription*)(arg001));

                argcode = (size_t)arg;
              }
            }
            else if (subtypeOfP(testValue001, SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) {
              { Object* arg002 = arg;
                Description* arg = ((Description*)(arg002));

                argcode = propositionHashIndex(arg->proposition, mapping, derefsurrogatesP);
              }
            }
            else if (subtypeOfP(testValue001, SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE)) {
              { Object* arg003 = arg;
                PatternVariable* arg = ((PatternVariable*)(arg003));

                argcode = (size_t)SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE;
              }
            }
            else if (subtypeOfP(testValue001, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
              { Object* arg004 = arg;
                Skolem* arg = ((Skolem*)(arg004));

                if (valueOf((arguments->theArray)[i]) == arg) {
                  arg = ((Skolem*)((arguments->theArray)[i]));
                }
                { Proposition* definingprop = arg->definingProposition;

                  if (((boolean)(definingprop)) &&
                      (!(definingprop == self))) {
                    argcode = propositionHashIndex(definingprop, mapping, derefsurrogatesP);
                  }
                  else {
                    argcode = (size_t)SGT_PROPOSITIONS_LOGIC_SKOLEM;
                  }
                }
              }
            }
            else if (subtypeOfSurrogateP(testValue001)) {
              { Object* arg005 = arg;
                Surrogate* arg = ((Surrogate*)(arg005));

                if (derefsurrogatesP) {
                  argcode = arg->surrogateValue->hashCode();
                }
                else {
                  argcode = arg->hashCode();
                }
              }
            }
            else if (subtypeOfWrapperP(testValue001)) {
              { Object* arg006 = arg;
                Wrapper* arg = ((Wrapper*)(arg006));

                argcode = arg->hashCode();
              }
            }
            else {
              argcode = (size_t)arg;
            }
          }
        }
        if ((!((boolean)(priorarg))) ||
            ((!commutativeP) ||
             eqlP(arg, priorarg))) {
          code = (((code & 1) == 0) ? ((unsigned int)code >> 1) : (((code >> 1)) | oINTEGER_MSB_MASKo));
        }
        code = (code ^ argcode);
        priorarg = arg;
      }
    }
    return (code);
  }
}

Proposition* lookupMatchingPropositionInBucket(List* bucket, Proposition* self, KeyValueMap* mapping) {
  { Module* homemodule = self->homeContext->baseModule;
    boolean functionP = self->kind == KWD_PROPOSITIONS_FUNCTION;
    GeneralizedSymbol* operatoR = self->operatoR;
    Vector* arguments = self->arguments;
    int arity = arguments->length();
    boolean rewrappedP = false;

    bucket->removeDeletedMembers();
    { Object* p = NULL;
      Cons* iter000 = bucket->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        p = iter000->value;
        if (subtypeOfP(safePrimaryType(p), SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
          { Object* p000 = p;
            Proposition* p = ((Proposition*)(p000));

            if ((operatoR == p->operatoR) &&
                (arity == p->arguments->length())) {
              for (;;) {
                if ((functionP &&
                    equivalentFunctionPropositionsP(self, p, mapping)) ||
                    ((!functionP) &&
                     equivalentPropositionsP(self, p, mapping))) {
                  if (subcontextP(homemodule, p->homeContext->baseModule)) {
                    return (p);
                  }
                  else {
                    break;
                  }
                }
                if (rewrappedP) {
                  break;
                }
                else {
                  rewrapPropositionArguments(self);
                  rewrappedP = true;
                  continue;
                }
              }
            }
          }
        }
        else {
        }
      }
    }
    return (NULL);
  }
}

Proposition* findDuplicateComplexProposition(Proposition* self) {
  { IntegerWrapper* index = wrapInteger(propositionHashIndex(self, NULL, false));
    List* bucket = ((List*)(oSTRUCTURED_OBJECTS_INDEXo->lookup(index)));
    Proposition* duplicate = NULL;

    if (!((boolean)(bucket))) {
      oSTRUCTURED_OBJECTS_INDEXo->insertAt(index, list(1, self));
      return (NULL);
    }
    duplicate = lookupMatchingPropositionInBucket(bucket, self, NULL);
    if (((boolean)(duplicate))) {
      return (duplicate);
    }
    bucket->push(self);
    return (NULL);
  }
}

Proposition* findDuplicateProposition(Proposition* self) {
  if (descriptionModeP() ||
      ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue) {
    return (NULL);
  }
  if (self->kind == KWD_PROPOSITIONS_DISABLED) {
    { Proposition* value000 = NULL;

      { Proposition* p = NULL;
        Iterator* iter000 = findSimilarPropositions(self)->allocateIterator();

        for (; iter000->nextP(); ) {
          p = ((Proposition*)(iter000->value));
          if (equivalentPropositionsP(self, p, NULL) &&
              subcontextP(self->homeContext->baseModule, p->homeContext->baseModule)) {
            value000 = p;
            break;
          }
        }
      }
      { Proposition* value001 = value000;

        return (value001);
      }
    }
  }
  else {
    { ObjectStore* store = homeObjectStore(self);

      if (((boolean)(store))) {
        return (store->fetchDuplicateProposition(self));
      }
      else {
        return (findDuplicateComplexProposition(self));
      }
    }
  }
}

Proposition* findMatchingNonDescriptiveProposition(Proposition* self, KeyValueMap* mapping) {
  if (!((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue) {
    return (self);
  }
  { IntegerWrapper* index = wrapInteger(propositionHashIndex(self, mapping, true));
    List* bucket = ((List*)(oSTRUCTURED_OBJECTS_INDEXo->lookup(index)));

    if (((boolean)(bucket))) {
      return (lookupMatchingPropositionInBucket(bucket, self, mapping));
    }
    else {
      return (NULL);
    }
  }
}

// If TRUE never check for the existence of duplicate
// propositions when building a new proposition.
DEFINE_STELLA_SPECIAL(oDONT_CHECK_FOR_DUPLICATE_PROPOSITIONSpo, boolean , false);

Proposition* fastenDownOneProposition(Proposition* self, boolean dontcheckforduplicatesP) {
  if (nativeSlotPropositionP(self)) {
    return (self);
  }
  if (!(oLOADINGREGENERABLEOBJECTSpo)) {
    surrogatifyDiscouragedArguments(self);
  }
  { Proposition* duplicate = NULL;

    if (!(dontcheckforduplicatesP ||
        (oDONT_CHECK_FOR_DUPLICATE_PROPOSITIONSpo &&
         (!(self->kind == KWD_PROPOSITIONS_FUNCTION))))) {
      duplicate = findDuplicateProposition(self);
    }
    if (((boolean)(duplicate))) {
      {
        if (!equalP(((PropertyList*)(dynamicSlotValue(duplicate->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ANNOTATIONS, NULL))), ((PropertyList*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ANNOTATIONS, NULL))))) {
          clearPropositionAnnotations(duplicate);
          setDynamicSlotValue(duplicate->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ANNOTATIONS, ((PropertyList*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ANNOTATIONS, NULL))), NULL);
          finalizePropositionAnnotations(duplicate);
          evaluateNewProposition(duplicate);
        }
        return (duplicate);
      }
    }
    else {
      {
        if (!(((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue ||
            descriptionModeP())) {
          if (!oLOADINGREGENERABLEOBJECTSpo) {
            logNewlyConceivedProposition(oMODULEo, self);
          }
        }
        if (!oLOADINGREGENERABLEOBJECTSpo) {
          rewrapPropositionArguments(self);
        }
        if (!oLOADINGREGENERABLEOBJECTSpo) {
          { Object* arg = NULL;
            Vector* vector000 = self->arguments;
            int index000 = 0;
            int length000 = vector000->length();

            for  (; index000 < length000; 
                  index000 = index000 + 1) {
              arg = (vector000->theArray)[index000];
              addDependentPropositionLink(arg, self);
            }
          }
        }
        updateDescriptionExtension(self);
        setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_UNFASTENEDp, NULL, NULL);
        finalizePropositionAnnotations(self);
        evaluateNewProposition(self);
        return (self);
      }
    }
  }
}

// Used by 'recursively-fasten-down-propositions'.
DEFINE_STELLA_SPECIAL(oVISITEDUNFASTENEDDEFININGPROPOSITIONSo, List* , NULL);

Proposition* helpFastenDownPropositions(Proposition* self, boolean dontcheckforduplicatesP) {
  { boolean dontcheckargsforduplicatesP = dontcheckforduplicatesP;

    { Keyword* testValue000 = self->kind;

      if ((testValue000 == KWD_PROPOSITIONS_FORALL) ||
          (testValue000 == KWD_PROPOSITIONS_EXISTS)) {
        dontcheckargsforduplicatesP = true;
      }
      else {
        if (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue) {
          dontcheckargsforduplicatesP = true;
        }
      }
    }
    { Object* arg = NULL;
      Vector* vector000 = self->arguments;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter000 = 0;

      for  (; index000 < length000; 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        arg = (vector000->theArray)[index000];
        i = iter000;
        { Surrogate* testValue001 = safePrimaryType(arg);

          if (subtypeOfP(testValue001, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
            { Object* arg000 = arg;
              Proposition* arg = ((Proposition*)(arg000));

              if (coerceWrappedBooleanToBoolean(arg->unfastenedP_reader())) {
                (self->arguments->theArray)[i] = (helpFastenDownPropositions(arg, dontcheckargsforduplicatesP));
              }
            }
          }
          else if (subtypeOfP(testValue001, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
            { Object* arg001 = arg;
              Skolem* arg = ((Skolem*)(arg001));

              { Proposition* definingprop = arg->definingProposition;

                if (((boolean)(definingprop)) &&
                    (coerceWrappedBooleanToBoolean(definingprop->unfastenedP_reader()) &&
                     (!oVISITEDUNFASTENEDDEFININGPROPOSITIONSo->memberP(definingprop)))) {
                  oVISITEDUNFASTENEDDEFININGPROPOSITIONSo->insert(definingprop);
                  helpFastenDownPropositions(definingprop, dontcheckargsforduplicatesP);
                }
              }
            }
          }
          else {
          }
        }
      }
    }
    return (fastenDownOneProposition(self, dontcheckforduplicatesP));
  }
}

Proposition* recursivelyFastenDownPropositions(Proposition* self, boolean dontcheckforduplicatesP) {
  if (!coerceWrappedBooleanToBoolean(self->unfastenedP_reader())) {
    return (self);
  }
  { 
    BIND_STELLA_SPECIAL(oVISITEDUNFASTENEDDEFININGPROPOSITIONSo, List*, list(0));
    return (helpFastenDownPropositions(self, dontcheckforduplicatesP));
  }
}

void unfastenProposition(Proposition* proposition) {
  { Object* arg = NULL;
    Vector* vector000 = proposition->arguments;
    int index000 = 0;
    int length000 = vector000->length();

    for  (; index000 < length000; 
          index000 = index000 + 1) {
      arg = (vector000->theArray)[index000];
      removeDependentPropositionLink(arg, proposition);
    }
  }
  setDynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_UNFASTENEDp, TRUE_WRAPPER, NULL);
}

void instantiateUndefinedSurrogates(Proposition* self) {
  { Keyword* testValue000 = self->kind;

    if ((testValue000 == KWD_PROPOSITIONS_AND) ||
        ((testValue000 == KWD_PROPOSITIONS_OR) ||
         ((testValue000 == KWD_PROPOSITIONS_NOT) ||
          (testValue000 == KWD_PROPOSITIONS_EXISTS)))) {
      { Object* arg = NULL;
        Vector* vector000 = self->arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          arg = (vector000->theArray)[index000];
          instantiateUndefinedSurrogates(((Proposition*)(arg)));
        }
      }
    }
    else if ((testValue000 == KWD_PROPOSITIONS_PREDICATE) ||
        ((testValue000 == KWD_PROPOSITIONS_FUNCTION) ||
         (testValue000 == KWD_PROPOSITIONS_ISA))) {
      { Object* arg = NULL;
        Vector* vector001 = self->arguments;
        int index001 = 0;
        int length001 = vector001->length();

        for  (; index001 < length001; 
              index001 = index001 + 1) {
          arg = (vector001->theArray)[index001];
          if (subtypeOfSurrogateP(safePrimaryType(arg))) {
            { Object* arg000 = arg;
              Surrogate* arg = ((Surrogate*)(arg000));

              if (!((boolean)(arg->surrogateValue))) {
                createLogicInstance(arg, NULL);
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
}

Proposition* buildTopLevelProposition(Object* tree, boolean trueassertionP) {
  if (isaP(tree, SGT_PROPOSITIONS_STELLA_STRING_WRAPPER)) {
    return (buildTopLevelProposition(readSExpressionFromString(((StringWrapper*)(tree))->wrapperValue), trueassertionP));
  }
  { Proposition* proposition = NULL;
    Cons* logicvariabletable = oLOGICVARIABLETABLEo;

    { 
      BIND_STELLA_SPECIAL(oLOGICVARIABLETABLEo, Cons*, ((Cons*)((((boolean)(logicvariabletable)) ? logicvariabletable : NIL))));
      BIND_STELLA_SPECIAL(oVARIABLEIDCOUNTERo, int, oVARIABLEIDCOUNTERo);
      BIND_STELLA_SPECIAL(oTERMUNDERCONSTRUCTIONo, Object*, tree);
      proposition = ((Proposition*)(buildProposition(tree)));
      if (((boolean)(proposition))) {
        normalizeTopLevelProposition(proposition);
        verifyForallPropositions(proposition);
        if (!(collectUnresolvedSlotReferences(proposition) == NIL)) {
          if (trueassertionP) {
            updateSkolemTypeFromIsaAssertions(proposition);
          }
          resolveUnresolvedSlotReferences(proposition);
        }
        if (trueassertionP &&
            ((proposition->kind == KWD_PROPOSITIONS_EXISTS) &&
             (!descriptionModeP()))) {
          instantiateUndefinedSurrogates(proposition);
        }
        proposition = recursivelyFastenDownPropositions(proposition, false);
      }
    }
    return (proposition);
  }
}

Object* buildProposition(Object* tree) {
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (testValue000 == SGT_PROPOSITIONS_STELLA_CONS) {
      { Object* tree000 = tree;
        Cons* tree = ((Cons*)(tree000));

        return (consDbuildProposition(tree));
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* tree001 = tree;
        Surrogate* tree = ((Surrogate*)(tree001));

        return (surrogateDbuildProposition(tree));
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* tree002 = tree;
        Symbol* tree = ((Symbol*)(tree002));

        return (symbolDbuildProposition(tree));
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE)) {
      { Object* tree003 = tree;
        PatternVariable* tree = ((PatternVariable*)(tree003));

        return (tree);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
      { Object* tree004 = tree;
        Proposition* tree = ((Proposition*)(tree004));

        return (tree);
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream000->nativeStream) << "ERROR: " << "Illegal logical sentence: " << "`" << tree << "'" << "." << std::endl;
          helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
        }
        throw *newPropositionError(stream000->theStringReader());
      }
    }
  }
}

Proposition* surrogateDbuildProposition(Surrogate* self) {
  { Object* value = self->surrogateValue;
    Proposition* proposition = NULL;

    if (((boolean)(value))) {
      if (subtypeOfP(safePrimaryType(value), SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
        { Object* value000 = value;
          Proposition* value = ((Proposition*)(value000));

          proposition = value;
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream000->nativeStream) << "ERROR: " << "Expected " << "`" << self->symbolName << "'" << " to have type proposition" << "." << std::endl;
            helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
          }
          throw *newPropositionError(stream000->theStringReader());
        }
      }
    }
    else {
      {
        proposition = createProposition(SYM_PROPOSITIONS_LOGIC_CONSTANT, 0);
        proposition->operatoR = self;
        self->surrogateValue = proposition;
        setDynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_STELLA_SURROGATE_VALUE_INVERSE, self, NULL);
      }
    }
    return (proposition);
  }
}

Object* symbolDbuildProposition(Symbol* symbol) {
  { Proposition* proposition = NULL;

    if (symbol == SYM_PROPOSITIONS_STELLA_TRUE) {
      proposition = TRUE_PROPOSITION;
    }
    else if (symbol == SYM_PROPOSITIONS_STELLA_FALSE) {
      proposition = FALSE_PROPOSITION;
    }
    else {
      return (evaluateSymbolTerm(symbol));
    }
    return (proposition);
  }
}

Proposition* consDbuildProposition(Cons* tree) {
  { Proposition* proposition = NULL;

    if (!isaP(tree->value, SGT_PROPOSITIONS_STELLA_SYMBOL)) {
      std::cerr << "Safety violation: " << "INTERNAL ERROR: Illegal operator in proposition tree.";
    }
    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

      if (testValue000 == SYM_PROPOSITIONS_STELLA_e) {
        proposition = buildEquivalenceProposition(tree);
      }
      else if ((testValue000 == SYM_PROPOSITIONS_STELLA_AND) ||
          ((testValue000 == SYM_PROPOSITIONS_STELLA_OR) ||
           (testValue000 == SYM_PROPOSITIONS_STELLA_NOT))) {
        proposition = buildAndOrNotProposition(tree);
      }
      else if (testValue000 == SYM_PROPOSITIONS_STELLA_ISA) {
        proposition = buildIsaProposition(tree);
      }
      else if (testValue000 == SYM_PROPOSITIONS_PL_KERNEL_KB_MEMBER_OF) {
        proposition = buildMemberOfProposition(tree);
      }
      else if ((testValue000 == SYM_PROPOSITIONS_LOGIC_IMPLIES) ||
          (testValue000 == SYM_PROPOSITIONS_PL_KERNEL_KB_SUBSET_OF)) {
        proposition = buildImpliesProposition(tree);
      }
      else if (testValue000 == SYM_PROPOSITIONS_STELLA_EXISTS) {
        proposition = buildExistsProposition(tree);
      }
      else if (testValue000 == SYM_PROPOSITIONS_STELLA_FORALL) {
        proposition = buildForallProposition(tree);
      }
      else if (testValue000 == SYM_PROPOSITIONS_LOGIC_FAIL) {
        proposition = buildFailProposition(tree);
      }
      else if (testValue000 == SYM_PROPOSITIONS_STELLA_COLLECT_INTO) {
        proposition = buildCollectIntoProposition(tree);
      }
      else if (testValue000 == SYM_PROPOSITIONS_LOGIC_ABOUT) {
        proposition = buildAnnotatedProposition(tree);
      }
      else {
        proposition = buildPredicateProposition(tree);
      }
    }
    if (!((boolean)(proposition))) {
      return (NULL);
    }
    if (containsNestedArgumentP(proposition)) {
      proposition = flattenNestedFunctionArguments(proposition);
    }
    return (proposition);
  }
}

void verifyNumberOfPropositionArguments(Cons* tree, int correctnumber) {
  if (!(tree->rest->length() == correctnumber)) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "ERROR: " << "Wrong number of arguments in proposition: " << "`" << tree << "'" << std::endl << "   Expected " << "`" << correctnumber << "'" << " arguments." << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
      }
      throw *newPropositionError(stream000->theStringReader());
    }
  }
}

Surrogate* Description::descriptionSurrogate() {
  { Description* self = this;

    { Relation* nativerelation = self->nativeRelation();

      if (((boolean)(nativerelation))) {
        { Surrogate* testValue000 = safePrimaryType(nativerelation);

          if (subtypeOfClassP(testValue000)) {
            { Relation* nativerelation000 = nativerelation;
              Class* nativerelation = ((Class*)(nativerelation000));

              return (classLogicalType(nativerelation));
            }
          }
          else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_SLOT)) {
            { Relation* nativerelation001 = nativerelation;
              Slot* nativerelation = ((Slot*)(nativerelation001));

              return (nativerelation->slotSlotref);
            }
          }
          else {
          }
        }
      }
      return (NULL);
    }
  }
}

Proposition* buildIsaProposition(Cons* tree) {
  verifyNumberOfPropositionArguments(tree, 2);
  { Proposition* proposition = createProposition(SYM_PROPOSITIONS_STELLA_ISA, 1);
    Surrogate* type = NULL;
    Object* symbol = tree->rest->rest->value;

    { Surrogate* testValue000 = safePrimaryType(symbol);

      if (subtypeOfSurrogateP(testValue000)) {
        { Object* symbol000 = symbol;
          Surrogate* symbol = ((Surrogate*)(symbol000));

          type = symbol;
        }
      }
      else if (subtypeOfSymbolP(testValue000)) {
        { Object* symbol001 = symbol;
          Symbol* symbol = ((Symbol*)(symbol001));

          type = symbolToSurrogate(symbol);
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream000->nativeStream) << "ERROR: " << "Illegal token where symbol expected: " << "`" << symbol << "'" << "." << std::endl;
            helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
          }
          throw *newPropositionError(stream000->theStringReader());
        }
      }
    }
    { NamedDescription* clasS = getDescription(type);

      if (!((boolean)(clasS))) {
        { OutputStringStream* stream001 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream001->nativeStream) << "ERROR: " << "No class is associated with the term " << "`" << type->symbolName << "'" << "." << std::endl;
            helpSignalPropositionError(stream001, KWD_PROPOSITIONS_ERROR);
          }
          throw *newPropositionError(stream001->theStringReader());
        }
      }
      if (!classDescriptionP(clasS)) {
        { OutputStringStream* stream002 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream002->nativeStream) << "ERROR: " << "Term " << "`" << type->symbolName << "'" << " found where class expected." << "." << std::endl;
            helpSignalPropositionError(stream002, KWD_PROPOSITIONS_ERROR);
          }
          throw *newPropositionError(stream002->theStringReader());
        }
      }
    }
    proposition->operatoR = type;
    (proposition->arguments->theArray)[0] = (evaluateTypedArgument(tree->rest->value, type));
    return (proposition);
  }
}

Proposition* buildMemberOfProposition(Cons* tree) {
  verifyNumberOfPropositionArguments(tree, 2);
  { Object* collectionref = tree->rest->rest->value;

    { Surrogate* testValue000 = safePrimaryType(collectionref);

      if (subtypeOfSurrogateP(testValue000)) {
        { Object* collectionref000 = collectionref;
          Surrogate* collectionref = ((Surrogate*)(collectionref000));

          if (((boolean)(collectionref->getStellaClass(false)))) {
            return (buildIsaProposition(tree));
          }
        }
      }
      else if (subtypeOfSymbolP(testValue000)) {
        { Object* collectionref001 = collectionref;
          Symbol* collectionref = ((Symbol*)(collectionref001));

          if (((boolean)(collectionref->getStellaClass(false)))) {
            return (buildIsaProposition(tree));
          }
        }
      }
      else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) {
        { Object* collectionref002 = collectionref;
          Description* collectionref = ((Description*)(collectionref002));

          if (namedDescriptionP(collectionref) &&
              classDescriptionP(((NamedDescription*)(collectionref)))) {
            return (buildIsaProposition(listO(3, SYM_PROPOSITIONS_STELLA_ISA, tree->rest->value, cons(collectionref->descriptionSurrogate(), NIL))));
          }
        }
      }
      else {
      }
    }
  }
  return (buildPredicateProposition(tree));
}

boolean memberOfPropositionP(Proposition* proposition) {
  return (proposition->operatoR == SGT_PROPOSITIONS_PL_KERNEL_KB_MEMBER_OF);
}

boolean subsetOfPropositionP(Proposition* proposition) {
  return (proposition->operatoR == SGT_PROPOSITIONS_PL_KERNEL_KB_SUBSET_OF);
}

boolean simpleSubrelationPropositionP(Proposition* proposition) {
  return ((proposition->operatoR == SGT_PROPOSITIONS_PL_KERNEL_KB_SUBSET_OF) &&
      (isaP((proposition->arguments->theArray)[0], SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION) &&
       isaP((proposition->arguments->theArray)[1], SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)));
}

Object* extractAnnotation(Object* tree, Keyword* option, Object*& _Return1) {
  { Object* value = NULL;

    if (safePrimaryType(tree) == SGT_PROPOSITIONS_STELLA_CONS) {
      { Object* tree000 = tree;
        Cons* tree = ((Cons*)(tree000));

        if (tree->value == SYM_PROPOSITIONS_LOGIC_ABOUT) {
          { PropertyList* self000 = newPropertyList();

            self000->thePlist = tree->rest->rest;
            { PropertyList* options = self000;

              value = options->lookup(option);
              if (((boolean)(value))) {
                options->removeAt(option);
                tree->rest->rest = options->thePlist;
              }
            }
          }
        }
      }
    }
    else {
    }
    _Return1 = value;
    return (tree);
  }
}

Object* lookupAnnotation(Proposition* proposition, Keyword* key) {
  { PropertyList* annotations = ((PropertyList*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ANNOTATIONS, NULL)));

    if (((boolean)(annotations))) {
      return (annotations->lookup(key));
    }
    else {
      return (NULL);
    }
  }
}

void insertAnnotation(Proposition* proposition, Keyword* key, Object* value) {
  { PropertyList* annotations = ((PropertyList*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ANNOTATIONS, NULL)));

    if (!((boolean)(annotations))) {
      annotations = newPropertyList();
      setDynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ANNOTATIONS, annotations, NULL);
    }
    annotations->insertAt(key, value);
  }
}

void removeAnnotation(Proposition* proposition, Keyword* key) {
  { PropertyList* annotations = ((PropertyList*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ANNOTATIONS, NULL)));

    if (!((boolean)(annotations))) {
      return;
    }
    annotations->removeAt(key);
    if (annotations->thePlist == NIL) {
      setDynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ANNOTATIONS, NULL, NULL);
    }
  }
}

Proposition* buildAnnotatedProposition(Cons* tree) {
  { Proposition* proposition = ((Proposition*)(buildProposition(tree->rest->value)));
    Cons* options = tree->rest->rest;

    while (!(options == NIL)) {
      if (isaP(options->value, SGT_PROPOSITIONS_STELLA_GENERALIZED_SYMBOL)) {
        options->firstSetter(((GeneralizedSymbol*)(options->value))->keywordify());
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream000->nativeStream) << "PARSING ERROR: " << "Illegal annotation option: " << "`" << options->value << "'" << "." << std::endl;
            helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
          }
          throw *newParsingError(stream000->theStringReader());
        }
      }
      if (!(((boolean)(options->rest->value)))) {
        { OutputStringStream* stream001 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream001->nativeStream) << "PARSING ERROR: " << "Missing annotation value for option: " << "`" << options->value << "'" << "." << std::endl;
            helpSignalPropositionError(stream001, KWD_PROPOSITIONS_ERROR);
          }
          throw *newParsingError(stream001->theStringReader());
        }
      }
      options = options->rest->rest;
    }
    { PropertyList* self004 = newPropertyList();

      self004->thePlist = tree->rest->rest;
      setDynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ANNOTATIONS, self004, NULL);
    }
    finalizePropositionAnnotations(proposition);
    return (proposition);
  }
}

void finalizePropositionAnnotations(Proposition* proposition) {
  { PropertyList* annotations = ((PropertyList*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ANNOTATIONS, NULL)));

    if (((boolean)(annotations))) {
      { Keyword* option = NULL;
        Object* value = NULL;
        Cons* iter000 = annotations->thePlist;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest->rest) {
          option = ((Keyword*)(iter000->value));
          value = iter000->rest->value;
          if (option == KWD_PROPOSITIONS_DIRECTION) {
            if (subtypeOfP(safePrimaryType(value), SGT_PROPOSITIONS_STELLA_GENERALIZED_SYMBOL)) {
              { Object* value000 = value;
                GeneralizedSymbol* value = ((GeneralizedSymbol*)(value000));

                { const char* testValue000 = stringUpcase(value->symbolName);

                  if (stringEqlP(testValue000, "FORWARD")) {
                    setDynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_FORWARD_ONLYp, TRUE_WRAPPER, FALSE_WRAPPER);
                  }
                  else if (stringEqlP(testValue000, "BACKWARD")) {
                    setDynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_BACKWARD_ONLYp, TRUE_WRAPPER, FALSE_WRAPPER);
                  }
                  else {
                    annotations->removeAt(option);
                    { OutputStringStream* stream000 = newOutputStringStream();

                      { 
                        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                        *(stream000->nativeStream) << "PARSING ERROR: " << "Illegal value for :direction option: " << "`" << value << "'" << "." << std::endl;
                        helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
                      }
                      throw *newParsingError(stream000->theStringReader());
                    }
                  }
                }
              }
            }
            else {
              annotations->removeAt(option);
              { OutputStringStream* stream001 = newOutputStringStream();

                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  *(stream001->nativeStream) << "PARSING ERROR: " << "Illegal value for :direction option: " << "`" << value << "'" << "." << std::endl;
                  helpSignalPropositionError(stream001, KWD_PROPOSITIONS_ERROR);
                }
                throw *newParsingError(stream001->theStringReader());
              }
            }
          }
          else if (option == KWD_PROPOSITIONS_WEIGHT) {
            { Surrogate* testValue001 = safePrimaryType(value);

              if (subtypeOfIntegerP(testValue001)) {
                { Object* value001 = value;
                  IntegerWrapper* value = ((IntegerWrapper*)(value001));

                  setDynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_WEIGHT, wrapFloat(value->numberWrapperToFloat()), NULL_FLOAT_WRAPPER);
                }
              }
              else if (subtypeOfFloatP(testValue001)) {
                { Object* value002 = value;
                  FloatWrapper* value = ((FloatWrapper*)(value002));

                  setDynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_WEIGHT, wrapFloat(value->wrapperValue), NULL_FLOAT_WRAPPER);
                }
              }
              else {
                annotations->removeAt(option);
                { OutputStringStream* stream002 = newOutputStringStream();

                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    *(stream002->nativeStream) << "PARSING ERROR: " << "Illegal value for :weight option: " << "`" << value << "'" << "." << std::endl;
                    helpSignalPropositionError(stream002, KWD_PROPOSITIONS_ERROR);
                  }
                  throw *newParsingError(stream002->theStringReader());
                }
              }
            }
          }
          else if (option == KWD_PROPOSITIONS_SCORE) {
            { Surrogate* testValue002 = safePrimaryType(value);

              if (subtypeOfIntegerP(testValue002)) {
                { Object* value003 = value;
                  IntegerWrapper* value = ((IntegerWrapper*)(value003));

                  { Proposition* object000 = proposition;
                    FloatWrapper* value005 = wrapFloat(coerceToFloat(value));
                    Object* oldValue000 = dynamicSlotValue(object000->dynamicSlots, SYM_PROPOSITIONS_LOGIC_SCORE, NULL);
                    Object* newValue000 = updateInContext(oldValue000, value005, object000->homeContext, false);

                    if (!(((boolean)(oldValue000)) &&
                        (oldValue000->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
                      setDynamicSlotValue(object000->dynamicSlots, SYM_PROPOSITIONS_LOGIC_SCORE, newValue000, NULL);
                    }
                  }
                }
              }
              else if (subtypeOfFloatP(testValue002)) {
                { Object* value004 = value;
                  FloatWrapper* value = ((FloatWrapper*)(value004));

                  { Proposition* object001 = proposition;
                    FloatWrapper* value006 = wrapFloat(coerceToFloat(value));
                    Object* oldValue001 = dynamicSlotValue(object001->dynamicSlots, SYM_PROPOSITIONS_LOGIC_SCORE, NULL);
                    Object* newValue001 = updateInContext(oldValue001, value006, object001->homeContext, false);

                    if (!(((boolean)(oldValue001)) &&
                        (oldValue001->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
                      setDynamicSlotValue(object001->dynamicSlots, SYM_PROPOSITIONS_LOGIC_SCORE, newValue001, NULL);
                    }
                  }
                }
              }
              else {
                annotations->removeAt(option);
                { OutputStringStream* stream003 = newOutputStringStream();

                  { 
                    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                    *(stream003->nativeStream) << "PARSING ERROR: " << "Illegal value for :score option: " << "`" << value << "'" << "." << std::endl;
                    helpSignalPropositionError(stream003, KWD_PROPOSITIONS_ERROR);
                  }
                  throw *newParsingError(stream003->theStringReader());
                }
              }
            }
          }
          else if (option == KWD_PROPOSITIONS_CONFIDENCE_LEVEL) {
          }
          else {
            if (!(runOptionHandlerP(proposition, option, value))) {
              annotations->removeAt(option);
              { OutputStringStream* stream004 = newOutputStringStream();

                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  *(stream004->nativeStream) << "PARSING ERROR: " << "Unrecognized annotation option: " << "`" << option << "'" << "." << std::endl;
                  helpSignalPropositionError(stream004, KWD_PROPOSITIONS_ERROR);
                }
                throw *newParsingError(stream004->theStringReader());
              }
            }
          }
        }
      }
    }
  }
}

void clearPropositionAnnotations(Proposition* proposition) {
  { PropertyList* annotations = ((PropertyList*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ANNOTATIONS, NULL)));

    if (((boolean)(annotations))) {
      { Keyword* option = NULL;
        Object* value = NULL;
        Cons* iter000 = annotations->thePlist;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest->rest) {
          option = ((Keyword*)(iter000->value));
          value = iter000->rest->value;
          value = value;
          if (option == KWD_PROPOSITIONS_DIRECTION) {
            setDynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER, FALSE_WRAPPER);
            setDynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_BACKWARD_ONLYp, FALSE_WRAPPER, FALSE_WRAPPER);
          }
          else if (option == KWD_PROPOSITIONS_WEIGHT) {
            setDynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_WEIGHT, wrapFloat(NULL_FLOAT), NULL_FLOAT_WRAPPER);
          }
          else {
            runOptionHandlerP(proposition, option, NULL);
          }
        }
      }
    }
  }
}

void forwardBackwardOptionHandler(Proposition* self, StorageSlot* slot, Object* tree) {
  if (tree == SYM_PROPOSITIONS_STELLA_TRUE) {
    if (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue) {
      setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER, FALSE_WRAPPER);
    }
    if (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_BACKWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue) {
      setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_BACKWARD_ONLYp, FALSE_WRAPPER, FALSE_WRAPPER);
    }
  }
  defaultOptionHandler(self, slot, tree);
}

void inheritPropositionAnnotations(PropertyList* annotations, Proposition* to) {
  if (((boolean)(annotations))) {
    { Object* key = NULL;
      Object* value = NULL;
      Cons* iter000 = annotations->thePlist;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest->rest) {
        key = iter000->value;
        value = iter000->rest->value;
        if (!((boolean)(lookupAnnotation(to, ((Keyword*)(key)))))) {
          insertAnnotation(to, ((Keyword*)(key)), value);
        }
      }
    }
    finalizePropositionAnnotations(to);
  }
}

boolean functionInducedExistsP(Proposition* proposition) {
  if (proposition->kind == KWD_PROPOSITIONS_EXISTS) {
    { Object* firstargument = (proposition->arguments->theArray)[0];

      if (isaP(firstargument, SGT_PROPOSITIONS_LOGIC_PROPOSITION) &&
          (((Proposition*)(firstargument))->kind == KWD_PROPOSITIONS_AND)) {
        { Vector* existsvariables = ((Vector*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_IO_VARIABLES, NULL)));
          Proposition* andprop = ((Proposition*)(firstargument));
          Vector* andarguments = andprop->arguments;
          int nonfunctionscount = 0;

          { boolean alwaysP000 = true;

            { PatternVariable* variable = NULL;
              Vector* vector000 = existsvariables;
              int index000 = 0;
              int length000 = vector000->length();

              for  (; index000 < length000; 
                    index000 = index000 + 1) {
                variable = ((PatternVariable*)((vector000->theArray)[index000]));
                { boolean testValue000 = false;

                  { boolean foundP000 = false;

                    { Proposition* arg = NULL;
                      Vector* vector001 = andarguments;
                      int index001 = 0;
                      int length001 = vector001->length();

                      for  (; index001 < length001; 
                            index001 = index001 + 1) {
                        arg = ((Proposition*)((vector001->theArray)[index001]));
                        if ((arg->kind == KWD_PROPOSITIONS_FUNCTION) &&
                            (arg->arguments->last() == variable)) {
                          foundP000 = true;
                          break;
                        }
                      }
                    }
                    testValue000 = foundP000;
                  }
                  testValue000 = !testValue000;
                  if (testValue000) {
                    alwaysP000 = false;
                    break;
                  }
                }
              }
            }
            if (alwaysP000) {
              { Proposition* arg = NULL;
                Vector* vector002 = andarguments;
                int index002 = 0;
                int length002 = vector002->length();

                for  (; index002 < length002; 
                      index002 = index002 + 1) {
                  arg = ((Proposition*)((vector002->theArray)[index002]));
                  if ((!(arg->kind == KWD_PROPOSITIONS_FUNCTION)) &&
                      (!coerceWrappedBooleanToBoolean(arg->variableTypeP_reader()))) {
                    nonfunctionscount = nonfunctionscount + 1;
                  }
                }
              }
              return (nonfunctionscount == 1);
            }
          }
        }
      }
    }
  }
  return (false);
}

Proposition* predicateOfFunctionInducedExists(Proposition* existsproposition) {
  { Proposition* value000 = NULL;

    { Proposition* arg = NULL;
      Vector* vector000 = ((Vector*)(((Proposition*)((existsproposition->arguments->theArray)[0]))->arguments));
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = ((Proposition*)((vector000->theArray)[index000]));
        if ((!(arg->kind == KWD_PROPOSITIONS_FUNCTION)) &&
            (!coerceWrappedBooleanToBoolean(arg->variableTypeP_reader()))) {
          value000 = arg;
          break;
        }
      }
    }
    { Proposition* value001 = value000;

      return (value001);
    }
  }
}

Proposition* embedNegationWithinFunctionInducedExists(Proposition* existsproposition) {
  invertProposition(predicateOfFunctionInducedExists(existsproposition));
  return (existsproposition);
}

Proposition* buildAndOrNotProposition(Cons* tree) {
  { Object* term = NULL;
    Cons* arguments = NIL;
    Proposition* proposition = NULL;
    Vector* argumentsvector = NULL;

    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

      if ((testValue000 == SYM_PROPOSITIONS_STELLA_AND) ||
          ((testValue000 == SYM_PROPOSITIONS_STELLA_OR) ||
           (testValue000 == SYM_PROPOSITIONS_STELLA_NOT))) {
        { Object* arg = NULL;
          Cons* iter000 = tree->rest;
          Cons* collect000 = NULL;

          for  (; !(iter000 == NIL); 
                iter000 = iter000->rest) {
            arg = iter000->value;
            { 
              term = buildProposition(arg);
              if (((boolean)(term))) {
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(term, NIL);
                    if (arguments == NIL) {
                      arguments = collect000;
                    }
                    else {
                      addConsToEndOfConsList(arguments, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(term, NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
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
    if ((arguments == NIL) &&
        (tree->value == SYM_PROPOSITIONS_STELLA_NOT)) {
      { OutputStringStream* stream001 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream001->nativeStream) << "ERROR: " << "Missing argument in NOT proposition: " << "`" << tree << "'" << "." << std::endl;
          helpSignalPropositionError(stream001, KWD_PROPOSITIONS_ERROR);
        }
        throw *newPropositionError(stream001->theStringReader());
      }
    }
    if ((tree->value == SYM_PROPOSITIONS_STELLA_NOT) &&
        (isaP(arguments->value, SGT_PROPOSITIONS_LOGIC_PROPOSITION) &&
         functionInducedExistsP(((Proposition*)(arguments->value))))) {
      return (embedNegationWithinFunctionInducedExists(((Proposition*)(arguments->value))));
    }
    proposition = createProposition(((Symbol*)(tree->value)), arguments->length());
    argumentsvector = proposition->arguments;
    { Object* arg = NULL;
      Cons* iter001 = arguments;
      int i = NULL_INTEGER;
      int iter002 = 0;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest,
            iter002 = iter002 + 1) {
        arg = iter001->value;
        i = iter002;
        (argumentsvector->theArray)[i] = arg;
      }
    }
    return (proposition);
  }
}

Proposition* conceiveInvertedProposition(Proposition* prop) {
  // Return the simplest inversion of `prop', trying to reuse existing
  // negations or negated arguments of `prop' if possible.
  if (!(!(prop->kind == KWD_PROPOSITIONS_FUNCTION))) {
    std::cerr << "Safety violation: " << "INTERNAL ERROR: conceive-inverted-proposition: can't invert function terms: " << "`" << prop << "'";
  }
  if (!coerceWrappedBooleanToBoolean(prop->unfastenedP_reader())) {
    if (prop->kind == KWD_PROPOSITIONS_NOT) {
      return (((Proposition*)((prop->arguments->theArray)[0])));
    }
    { Proposition* parent = NULL;
      Iterator* iter000 = prop->dependentPropositions->allocateIterator();

      for (; iter000->nextP(); ) {
        parent = ((Proposition*)(iter000->value));
        if ((parent->kind == KWD_PROPOSITIONS_NOT) &&
            ((parent->arguments->theArray)[0] == prop)) {
          return (parent);
        }
      }
    }
  }
  prop = safelyInvertProposition(prop);
  { Proposition* object000 = prop;
    TruthValue* value000 = NULL;
    Object* oldValue000 = object000->truthValue;
    Object* newValue000 = updateInContext(oldValue000, value000, object000->homeContext, false);

    if (!(((boolean)(oldValue000)) &&
        (oldValue000->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
      object000->truthValue = newValue000;
    }
  }
  return (recursivelyFastenDownPropositions(prop, false));
}

boolean functionalTermP(Object* term) {
  if (safePrimaryType(term) == SGT_PROPOSITIONS_STELLA_CONS) {
    { Object* term000 = term;
      Cons* term = ((Cons*)(term000));

      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(term->value));

        if ((testValue000 == SYM_PROPOSITIONS_LOGIC_SETOFALL) ||
            ((testValue000 == SYM_PROPOSITIONS_LOGIC_THE_ONLY) ||
             ((testValue000 == SYM_PROPOSITIONS_PL_KERNEL_KB_SETOF) ||
              ((testValue000 == SYM_PROPOSITIONS_PL_KERNEL_KB_LISTOF) ||
               (testValue000 == SYM_PROPOSITIONS_LOGIC_KAPPA))))) {
          return (false);
        }
        else {
          return (true);
        }
      }
    }
  }
  else {
    return (false);
  }
}

boolean clipValueP(Object* term1, Object* term2) {
  if (subtypeOfP(safePrimaryType(term1), SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
    { Object* term1000 = term1;
      Skolem* term1 = ((Skolem*)(term1000));

      { Object* value1 = valueOf(term1);

        if (eqlP(value1, term2)) {
          return (true);
        }
        if ((!skolemP(value1)) &&
            (((boolean)(term1->definingProposition)) &&
             oCLIPPINGENABLEDpo)) {
          unbindSkolemValue(term1, true);
          bindSkolemToValue(term1, valueOf(term2), true);
          return (true);
        }
      }
    }
  }
  else {
  }
  return (false);
}

Proposition* createEquivalenceProposition(Object* term1, Object* term2) {
  { Proposition* proposition = createProposition(SYM_PROPOSITIONS_LOGIC_EQUIVALENT, 2);
    Vector* argumentsvector = proposition->arguments;

    (argumentsvector->theArray)[0] = term1;
    (argumentsvector->theArray)[1] = term2;
    return (proposition);
  }
}

Proposition* buildEquivalenceProposition(Cons* tree) {
  switch (tree->length()) {
    case 3: 
      return (createEquivalenceProposition(evaluateTerm(tree->rest->value), evaluateTerm(tree->rest->rest->value)));
    case 1: 
    case 2: 
      { OutputStringStream* stream000 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream000->nativeStream) << "ERROR: " << "Missing argument/s in `=' proposition." << "." << std::endl;
          helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
        }
        throw *newPropositionError(stream000->theStringReader());
      }
      break;
    default:
      return (buildConjunctionOfEqualityPropositions(tree->rest, NIL));
  }
}

Proposition* buildConjunctionOfEqualityPropositions(Cons* remainingterms, Cons* equivalences) {
  if (remainingterms->rest == NIL) {
    return (conjoinPropositions(equivalences));
  }
  equivalences = cons(buildEquivalenceProposition(listO(3, SYM_PROPOSITIONS_STELLA_e, remainingterms->value, cons(remainingterms->rest->value, NIL))), equivalences);
  return (buildConjunctionOfEqualityPropositions(remainingterms->rest, equivalences));
}

Proposition* buildFailProposition(Cons* tree) {
  { Proposition* proposition = createProposition(SYM_PROPOSITIONS_LOGIC_FAIL, 1);
    Object* argument = buildProposition(tree->rest->value);

    if (!((boolean)(argument))) {
      return (NULL);
    }
    (proposition->arguments->theArray)[0] = argument;
    return (proposition);
  }
}

Proposition* buildCollectIntoProposition(Cons* tree) {
  { Proposition* proposition = createProposition(SYM_PROPOSITIONS_STELLA_COLLECT_INTO, 2);
    Vector* argumentsvector = proposition->arguments;

    (argumentsvector->theArray)[0] = (evaluateTerm(tree->rest->value));
    (argumentsvector->theArray)[1] = (evaluateTerm(tree->rest->rest->value));
    return (proposition);
  }
}

boolean holdsOperatorP(Object* operatoR) {
  { Surrogate* testValue000 = safePrimaryType(operatoR);

    if (subtypeOfSymbolP(testValue000)) {
      { Object* operator000 = operatoR;
        Symbol* operatoR = ((Symbol*)(operator000));

        return ((operatoR == SYM_PROPOSITIONS_PL_KERNEL_KB_HOLDS) ||
            ((boolean)(lookupLogicVariableBinding(operatoR))));
      }
    }
    else if (testValue000 == SGT_PROPOSITIONS_STELLA_CONS) {
      { Object* operator001 = operatoR;
        Cons* operatoR = ((Cons*)(operator001));

        return (true);
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

void verifyEvaluableOperator(Object* operatoR, Keyword* kind) {
  if (subtypeOfP(safePrimaryType(operatoR), SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE)) {
    { Object* operator000 = operatoR;
      PatternVariable* operatoR = ((PatternVariable*)(operator000));

      if (kind == KWD_PROPOSITIONS_PREDICATE) {
        operatoR->skolemType = SGT_PROPOSITIONS_PL_KERNEL_KB_RELATION;
      }
      else if (kind == KWD_PROPOSITIONS_FUNCTION) {
        operatoR->skolemType = SGT_PROPOSITIONS_PL_KERNEL_KB_FUNCTION;
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << kind << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
  else {
  }
}

Proposition* buildHoldsProposition(Cons* tree) {
  { Object* operatorexpression = tree->value;
    boolean explicitholdsP = operatorexpression == SYM_PROPOSITIONS_PL_KERNEL_KB_HOLDS;
    int argcount = tree->rest->length();
    Proposition* proposition = createProposition(SYM_PROPOSITIONS_STELLA_PREDICATE, (explicitholdsP ? argcount : (argcount + 1)));

    proposition->operatoR = SGT_PROPOSITIONS_PL_KERNEL_KB_HOLDS;
    if (explicitholdsP) {
      { Object* arg = NULL;
        Cons* iter000 = tree->rest;
        int i = NULL_INTEGER;
        int iter001 = 0;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          arg = iter000->value;
          i = iter001;
          if (i == 0) {
            arg = evaluateFirstArgument(arg, SYM_PROPOSITIONS_PL_KERNEL_KB_HOLDS);
          }
          else if (propositionalArgumentP(arg)) {
            arg = evaluatePropositionTerm(arg);
          }
          else {
            arg = evaluateTerm(arg);
          }
          (proposition->arguments->theArray)[i] = arg;
        }
      }
      return (proposition);
    }
    { Object* operatoR = NULL;

      { Surrogate* testValue000 = safePrimaryType(operatorexpression);

        if (subtypeOfSymbolP(testValue000)) {
          { Object* operatorexpression000 = operatorexpression;
            Symbol* operatorexpression = ((Symbol*)(operatorexpression000));

            operatoR = lookupLogicVariableBinding(operatorexpression);
          }
        }
        else if (testValue000 == SGT_PROPOSITIONS_STELLA_CONS) {
          { Object* operatorexpression001 = operatorexpression;
            Cons* operatorexpression = ((Cons*)(operatorexpression001));

            operatoR = evaluateFirstArgument(operatorexpression, SYM_PROPOSITIONS_PL_KERNEL_KB_HOLDS);
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      verifyEvaluableOperator(operatoR, KWD_PROPOSITIONS_PREDICATE);
      (proposition->arguments->theArray)[0] = operatoR;
      { Object* arg = NULL;
        Cons* iter002 = tree->rest;
        int i = NULL_INTEGER;
        int iter003 = 1;

        for  (; !(iter002 == NIL); 
              iter002 = iter002->rest,
              iter003 = iter003 + 1) {
          arg = iter002->value;
          i = iter003;
          (proposition->arguments->theArray)[i] = (evaluateTerm(arg));
        }
      }
      return (proposition);
    }
  }
}

Surrogate* mostGeneralEquivalentSlotref(Surrogate* surrogate) {
  { Slot* slot = ((Slot*)(surrogate->surrogateValue));

    if (!((boolean)(slot))) {
      return (NULL);
    }
    if (((boolean)(slot->slotDirectEquivalent))) {
      while (((boolean)(slot->slotDirectEquivalent))) {
        slot = slot->slotDirectEquivalent;
      }
      if (!((boolean)(slot->slotSlotref))) {
        lookupSlotref(slot->slotOwner, slot->slotName);
      }
    }
    return (slot->slotSlotref);
  }
}

boolean polymorphicRelationP(Relation* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfStorageSlotP(testValue000)) {
      { Relation* self000 = self;
        StorageSlot* self = ((StorageSlot*)(self000));

        return (true);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_TABLE)) {
      { Relation* self001 = self;
        Table* self = ((Table*)(self001));

        return (true);
      }
    }
    else {
      return (false);
    }
  }
}

boolean nonPolymorphicPredicateP(LogicObject* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
      { LogicObject* self000 = self;
        NamedDescription* self = ((NamedDescription*)(self000));

        { Relation* relation = self->nativeRelation();

          return (!(((boolean)(relation)) &&
              polymorphicRelationP(relation)));
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { LogicObject* self001 = self;
        LogicObject* self = self001;

        return (!testIsaP(self, SGT_PROPOSITIONS_PL_KERNEL_KB_POLYMORPHIC));
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

LogicObject* evaluatePredicate(GeneralizedSymbol* name, Object* firstargument) {
  { Surrogate* surrogate = NULL;
    LogicObject* predicatevalue = NULL;

    { Surrogate* testValue000 = safePrimaryType(name);

      if (subtypeOfSymbolP(testValue000)) {
        { GeneralizedSymbol* name000 = name;
          Symbol* name = ((Symbol*)(name000));

          surrogate = symbolToSurrogate(name);
        }
      }
      else if (subtypeOfSurrogateP(testValue000)) {
        { GeneralizedSymbol* name001 = name;
          Surrogate* name = ((Surrogate*)(name001));

          surrogate = name;
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    predicatevalue = getDescription(surrogate);
    if (((boolean)(predicatevalue))) {
      return (predicatevalue);
    }
    else {
      {
        predicatevalue = ((LogicObject*)(surrogate->surrogateValue));
        if (((boolean)(predicatevalue)) &&
            (testIsaP(predicatevalue, SGT_PROPOSITIONS_PL_KERNEL_KB_RELATION) &&
             nonPolymorphicPredicateP(predicatevalue))) {
          return (predicatevalue);
        }
      }
    }
    if (((boolean)(firstargument))) {
      { Object* firstargvalue = valueOf(firstargument);
        Symbol* symbol = surrogateToSymbol(surrogate);

        if (!((boolean)(firstargvalue))) {
          signalUndefinedTerm(firstargument);
        }
        surrogate = lookupSlotrefOnInstance(firstargvalue, symbol);
        if (((boolean)(surrogate))) {
          return (getDescription(mostGeneralEquivalentSlotref(surrogate)));
        }
      }
    }
    return (NULL);
  }
}

// If TRUE, automatically coerce propositional arguments of a
// proposition, even if the corresponding argument type of the hosting relation
// doesn't indicate that.
boolean oAUTO_COERCE_PROPOSITIONAL_ARGUMENTSpo = false;

boolean propositionalArgumentP(Object* argument) {
  if (safePrimaryType(argument) == SGT_PROPOSITIONS_STELLA_CONS) {
    { Object* argument000 = argument;
      Cons* argument = ((Cons*)(argument000));

      { Object* operatoR = argument->value;
        Object* firstarg = argument->rest->value;

        if ((!(operatoR == SYM_PROPOSITIONS_PL_KERNEL_KB_VALUE)) &&
            holdsOperatorP(operatoR)) {
          return (true);
        }
        if (symbolP(operatoR)) {
          { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(operatoR));

            if ((testValue000 == SYM_PROPOSITIONS_STELLA_AND) ||
                ((testValue000 == SYM_PROPOSITIONS_STELLA_OR) ||
                 ((testValue000 == SYM_PROPOSITIONS_STELLA_NOT) ||
                  ((testValue000 == SYM_PROPOSITIONS_STELLA_EXISTS) ||
                   ((testValue000 == SYM_PROPOSITIONS_STELLA_FORALL) ||
                    (testValue000 == SYM_PROPOSITIONS_STELLA_e)))))) {
              return (true);
            }
            else {
              { LogicObject* predicate = evaluatePredicate(((GeneralizedSymbol*)(operatoR)), firstarg);
                int arity = 0;

                if (((boolean)(predicate))) {
                  if (subtypeOfP(safePrimaryType(predicate), SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
                    { LogicObject* predicate000 = predicate;
                      NamedDescription* predicate = ((NamedDescription*)(predicate000));

                      if (functionP(predicate)) {
                        arity = predicate->arity();
                        if ((arity == -1) ||
                            (arity == argument->length())) {
                          return (false);
                        }
                        else {
                          return (true);
                        }
                      }
                      else {
                        return (true);
                      }
                    }
                  }
                  else {
                  }
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
  return (false);
}

Object* evaluateTypedArgument(Object* argument, Surrogate* type) {
  if ((type == SGT_PROPOSITIONS_LOGIC_PROPOSITION) ||
      (oAUTO_COERCE_PROPOSITIONAL_ARGUMENTSpo &&
       propositionalArgumentP(argument))) {
    return (evaluatePropositionTerm(argument));
  }
  else if (((boolean)(type))) {
    { 
      BIND_STELLA_SPECIAL(oDEFAULTCREATIONTYPEo, Surrogate*, type);
      return (evaluateTerm(argument));
    }
  }
  else {
    return (evaluateTerm(argument));
  }
}

Object* evaluatePropositionTerm(Object* tree) {
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
      { Object* tree000 = tree;
        Proposition* tree = ((Proposition*)(tree000));

        return (tree);
      }
    }
    else if (testValue000 == SGT_PROPOSITIONS_STELLA_CONS) {
      { Object* tree001 = tree;
        Cons* tree = ((Cons*)(tree001));

        { LogicObject* predicate = NULL;
          Object* firstargument = NULL;

          predicate = evaluatePredicateAndFirstArgument(tree, firstargument);
          if (((boolean)(firstargument))) {
            tree->secondSetter(firstargument);
          }
          if (functionP(predicate) &&
              (((NamedDescription*)(predicate))->arity() == tree->length())) {
            return (evaluateFunctionTerm(tree));
          }
          else {
            return (buildProposition(tree));
          }
        }
      }
    }
    else {
      return (buildProposition(tree));
    }
  }
}

LogicObject* evaluatePredicateAndFirstArgument(Cons* tree, Object*& _Return1) {
  { Object* predicate = tree->value;
    Object* firstargument = tree->rest->value;

    if (subtypeOfP(safePrimaryType(predicate), SGT_PROPOSITIONS_STELLA_GENERALIZED_SYMBOL)) {
      { Object* predicate000 = predicate;
        GeneralizedSymbol* predicate = ((GeneralizedSymbol*)(predicate000));

        if ((predicate == SYM_PROPOSITIONS_STELLA_EXISTS) ||
            (predicate == SYM_PROPOSITIONS_STELLA_FORALL)) {
          firstargument = NULL;
          predicate = NULL;
        }
        else if ((predicate == SYM_PROPOSITIONS_STELLA_AND) ||
            ((predicate == SYM_PROPOSITIONS_STELLA_OR) ||
             (predicate == SYM_PROPOSITIONS_STELLA_NOT))) {
          firstargument = NULL;
          predicate = NULL;
        }
        else {
        }
      }
    }
    else {
      predicate = NULL;
    }
    if (((boolean)(predicate))) {
      if (((boolean)(firstargument))) {
        firstargument = evaluateFirstArgument(tree->rest->value, ((Symbol*)(predicate)));
      }
      predicate = evaluatePredicate(((GeneralizedSymbol*)(predicate)), firstargument);
    }
    _Return1 = firstargument;
    return (((LogicObject*)(predicate)));
  }
}

Object* evaluateFirstArgument(Object* argument, Symbol* relationname) {
  { LogicObject* predicatevalue = evaluatePredicate(relationname, NULL);
    Surrogate* type = NULL;
    Object* firstargument = NULL;

    if (!((boolean)(argument))) {
      return (NULL);
    }
    if (((boolean)(predicatevalue)) &&
        isaP(predicatevalue, SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
      type = ((Surrogate*)(((NamedDescription*)(predicatevalue))->ioVariableTypes->first()));
    }
    firstargument = evaluateTypedArgument(argument, type);
    if ((relationname == SYM_PROPOSITIONS_PL_KERNEL_KB_VALUE) ||
        (relationname == SYM_PROPOSITIONS_PL_KERNEL_KB_HOLDS)) {
      if (descriptionModeP() &&
          variableP(firstargument)) {
        { Proposition* fnprop = ((PatternVariable*)(firstargument))->definingProposition;

          { boolean testValue000 = false;

            testValue000 = ((boolean)(fnprop));
            if (testValue000) {
              { boolean foundP000 = false;

                { int i = NULL_INTEGER;
                  int iter000 = 0;
                  int upperBound000 = fnprop->arguments->length() - 2;

                  for  (; iter000 <= upperBound000; 
                        iter000 = iter000 + 1) {
                    i = iter000;
                    if (variableP((fnprop->arguments->theArray)[i])) {
                      foundP000 = true;
                      break;
                    }
                  }
                }
                testValue000 = foundP000;
              }
              testValue000 = !testValue000;
            }
            if (testValue000) {
              { 
                BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_PROPOSITIONS_EXTENSIONAL_ASSERTION);
                firstargument = evaluateTypedArgument(argument, type);
              }
            }
          }
        }
      }
    }
    else {
    }
    if (!((boolean)(firstargument))) {
      signalUndefinedTerm(argument);
    }
    { 
      BIND_STELLA_SPECIAL(oSUPPRESSNONLOGICOBJECTWARNINGpo, boolean, true);
      if (valueOf(firstargument) == BOTTOM) {
        signalUndefinedTerm(firstargument);
      }
    }
    return (firstargument);
  }
}

Cons* evaluateRemainingArguments(LogicObject* predicatevalue, Cons* arguments) {
  { Cons* evaluatedarguments = NIL;

    if (((boolean)(predicatevalue)) &&
        isaP(predicatevalue, SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
      { List* variabletypes = ((NamedDescription*)(predicatevalue))->ioVariableTypes;

        { Surrogate* type = NULL;
          Cons* iter000 = variabletypes->rest();

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            type = ((Surrogate*)(iter000->value));
            { Object* head000 = arguments->value;

              arguments = arguments->rest;
              { Object* arg = head000;

                if (((boolean)(arg))) {
                  evaluatedarguments = cons(evaluateTypedArgument(arg, type), evaluatedarguments);
                }
              }
            }
          }
        }
        { Object* arg = NULL;
          Cons* iter001 = arguments;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            arg = iter001->value;
            evaluatedarguments = cons(evaluateTypedArgument(arg, ((Surrogate*)(variabletypes->last()))), evaluatedarguments);
          }
        }
        return (evaluatedarguments->reverse());
      }
    }
    else {
      {
        { Object* arg = NULL;
          Cons* iter002 = arguments;
          Cons* collect000 = NULL;

          for  (; !(iter002 == NIL); 
                iter002 = iter002->rest) {
            arg = iter002->value;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(evaluateTerm(arg), NIL);
                if (evaluatedarguments == NIL) {
                  evaluatedarguments = collect000;
                }
                else {
                  addConsToEndOfConsList(evaluatedarguments, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(evaluateTerm(arg), NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        return (evaluatedarguments);
      }
    }
  }
}

boolean classOperatorP(GeneralizedSymbol* operatoR) {
  { NamedDescription* description = getDescription(operatoR);

    return (((boolean)(description)) &&
        classDescriptionP(description));
  }
}

Proposition* buildPredicateProposition(Cons* tree) {
  if ((tree->length() == 2) &&
      classOperatorP(((GeneralizedSymbol*)(tree->value)))) {
    return (buildIsaProposition(listO(3, SYM_PROPOSITIONS_STELLA_ISA, tree->rest->value, cons(tree->value, NIL))));
  }
  if (holdsOperatorP(tree->value)) {
    return (buildHoldsProposition(tree));
  }
  { Object* predicatename = tree->value;
    Proposition* proposition = createProposition(SYM_PROPOSITIONS_STELLA_PREDICATE, tree->rest->length());
    Object* firstargument = NULL;
    LogicObject* predicatevalue = NULL;

    predicatevalue = evaluatePredicateAndFirstArgument(tree, firstargument);
    if (((boolean)(firstargument))) {
      tree->secondSetter(firstargument);
      (proposition->arguments->theArray)[0] = firstargument;
    }
    if (((boolean)(predicatevalue)) &&
        functionP(predicatevalue)) {
      if (descriptionModeP()) {
        proposition->kind = KWD_PROPOSITIONS_FUNCTION;
      }
      else {
        { int lastargindex = tree->length() - 1;
          Object* resultargument = evaluateTypedArgument(tree->nth(lastargindex), ((Surrogate*)(((NamedDescription*)(predicatevalue))->ioVariableTypes->last())));

          tree->nthSetter(NULL, lastargindex);
          tree = tree->remove(NULL);
          return (((Proposition*)(buildProposition(listO(3, SYM_PROPOSITIONS_STELLA_e, tree, cons(resultargument, NIL))))));
        }
      }
    }
    { Object* arg = NULL;
      Cons* iter000 = evaluateRemainingArguments(predicatevalue, tree->rest->rest);
      int i = NULL_INTEGER;
      int iter001 = 1;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        arg = iter000->value;
        i = iter001;
        (proposition->arguments->theArray)[i] = arg;
      }
    }
    proposition->operatoR = (((boolean)(predicatevalue)) ? predicatevalue->surrogateValueInverse : ((GeneralizedSymbol*)(predicatename)));
    if (proposition->operatoR == SGT_PROPOSITIONS_PL_KERNEL_KB_VALUE) {
      proposition = normalizeValueFunction(proposition);
    }
    verifyArgumentTypesAndCount(proposition);
    return (proposition);
  }
}

boolean checkStrictTypeP(Object* self, Surrogate* type, boolean shallowP) {
  shallowP = shallowP;
  if ((!((boolean)(type))) ||
      ((!((boolean)(self))) ||
       (type == SGT_PROPOSITIONS_STELLA_THING))) {
    return (true);
  }
  if ((type == SGT_PROPOSITIONS_STELLA_BOOLEAN) &&
      ((self == TRUE_PROPOSITION) ||
       (self == FALSE_PROPOSITION))) {
    return (true);
  }
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE)) {
      { Object* self000 = self;
        PatternVariable* self = ((PatternVariable*)(self000));

        return (true);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_LITERAL_WRAPPER)) {
      { Object* self001 = self;
        LiteralWrapper* self = ((LiteralWrapper*)(self001));

        if (isaP(type->surrogateValue, SGT_PROPOSITIONS_STELLA_CLASS) &&
            subtypeOfP(logicalType(self), type)) {
          return (true);
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
      { Object* self002 = self;
        Proposition* self = ((Proposition*)(self002));

        if (isaP(type->surrogateValue, SGT_PROPOSITIONS_STELLA_CLASS) &&
            subtypeOfP(logicalType(self), type)) {
          return (true);
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_QUANTITY_LOGIC_WRAPPER)) {
      { Object* self003 = self;
        QuantityLogicWrapper* self = ((QuantityLogicWrapper*)(self003));

        return (true);
      }
    }
    else {
    }
  }
  return (testIsaP(self, type) ||
      logicalSubtypeOfP(logicalType(self), type));
}

boolean checkTypeP(Object* self, Surrogate* type, boolean shallowP) {
  return ((((boolean)(oQUERYITERATORo)) &&
      ((boolean)(oQUERYITERATORo->partialMatchStrategy))) ||
      checkStrictTypeP(self, type, shallowP));
}

boolean checkCoercedTypeP(Object* self, Surrogate* type, boolean shallowP, Object*& _Return1) {
  if (checkStrictTypeP(self, type, shallowP)) {
    _Return1 = self;
    return (true);
  }
  { Object* substitutedvalue = coerceIncompatibleValue(self, type);

    if (((boolean)(substitutedvalue))) {
      _Return1 = substitutedvalue;
      return (true);
    }
  }
  if (((boolean)(oQUERYITERATORo)) &&
      ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
    _Return1 = self;
    return (true);
  }
  else {
    _Return1 = self;
    return (false);
  }
}

Object* coerceIncompatibleValue(Object* value, Surrogate* type) {
  { Object* substituteValue = NULL;

    if (relationrefSpecializesRelationrefP(type, SGT_PROPOSITIONS_PL_KERNEL_KB_QUANTITY)) {
      return (coerceQuantity(value, type));
    }
    else if (relationrefSpecializesRelationrefP(type, SGT_PROPOSITIONS_PL_KERNEL_KB_DATE)) {
      return (coerceDate(value, type));
    }
    else if (isaP(value, SGT_PROPOSITIONS_STELLA_LITERAL_WRAPPER) &&
        testIsaP(rewrapArgument(value), type)) {
      return (rewrapArgument(value));
    }
    { Surrogate* testValue000 = safePrimaryType(value);

      if (subtypeOfIntegerP(testValue000)) {
        { Object* value000 = value;
          IntegerWrapper* value = ((IntegerWrapper*)(value000));

          if (type == SGT_PROPOSITIONS_STELLA_FLOAT) {
            { int intvalue = value->wrapperValue;
              double floatvalue = ((double)(intvalue));

              substituteValue = wrapFloat(floatvalue);
            }
          }
        }
      }
      else if (subtypeOfFloatP(testValue000)) {
        { Object* value001 = value;
          FloatWrapper* value = ((FloatWrapper*)(value001));

          if (type == SGT_PROPOSITIONS_STELLA_INTEGER) {
            { double floatvalue = value->wrapperValue;
              int intvalue = stella::floor(floatvalue);

              if (((double)(intvalue)) == floatvalue) {
                substituteValue = wrapInteger(intvalue);
              }
            }
          }
        }
      }
      else {
      }
    }
    return (substituteValue);
  }
}

Object* coerceQuantity(Object* value, Surrogate* quantitytyperef) {
  return (value);
}

Object* coerceDate(Object* value, Surrogate* datetyperef) {
  return (value);
}

// Three policies are implemented:
//    :AUTOMATICALLY-FIX-TYPE-VIOLATIONS asserts missing types to fix type
//        violations (default),
//    :REPORT-TYPE-VIOLATIONS complains about missing or incorrect types,
//    :SIGNAL-TYPE-VIOLATIONS throws exception for missing or incorrect types, and
//    :IGNORE-TYPE-VIOLATIONS which disables all type checking.
Keyword* oTYPE_CHECK_POLICYo = NULL;

// Controls the behavior of the type-checking
// routines in the event that a type-check fails.  Options are:
//   :POST-TYPE-VIOLATIONS              push offending proposition onto queue,
//   :REPORT-TYPE-VIOLATIONS            print occasions of failed type checks,
//   :SIGNAL-TYPE-VIOLATIONS            throw exception for failed type checks,
//   :AUTOMATICALLY-FIX-TYPE-VIOLATIONS assert missing types on propositions, and
//   :IGNORE-TYPE-VIOLATIONS            don't perform any type checking at all.
DEFINE_STELLA_SPECIAL(oTYPECHECKMODEo, Keyword* , NULL);

void verifyOneArgumentType(Object* arg, Surrogate* type, Proposition* proposition, NamedDescription* description) {
  if ((oTYPECHECKMODEo == KWD_PROPOSITIONS_IGNORE_TYPE_VIOLATIONS) ||
      (!((boolean)(type->surrogateValue)))) {
    return;
  }
  { Object* argvalue = valueOf(arg);
    boolean typeisokP = false;
    Object* substitutevalue = NULL;

    typeisokP = checkCoercedTypeP(argvalue, type, false, substitutevalue);
    if (!eqlP(argvalue, substitutevalue)) {
      { Object* argtoo = NULL;
        Vector* vector000 = proposition->arguments;
        int index000 = 0;
        int length000 = vector000->length();
        Surrogate* t = NULL;
        Cons* iter000 = description->ioVariableTypes->theConsList;
        int i = NULL_INTEGER;
        int iter001 = 0;

        for  (; (index000 < length000) &&
                  (!(iter000 == NIL)); 
              index000 = index000 + 1,
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          argtoo = (vector000->theArray)[index000];
          t = ((Surrogate*)(iter000->value));
          i = iter001;
          if (eqlP(argtoo, arg) &&
              (t == type)) {
            (proposition->arguments->theArray)[i] = substitutevalue;
          }
        }
      }
    }
    else if (!typeisokP) {
      handleArgumentTypeViolation(proposition, arg, type);
    }
  }
}

void verifyArgumentTypesAndCount(Proposition* proposition) {
  if ((oTYPECHECKMODEo == KWD_PROPOSITIONS_IGNORE_TYPE_VIOLATIONS) ||
      ((!worldStateP(oCONTEXTo)) ||
       (!isaP(proposition->operatoR, SGT_PROPOSITIONS_STELLA_SURROGATE)))) {
    return;
  }
  { NamedDescription* description = getDescription(((Surrogate*)(proposition->operatoR)));
    int argumentcount = proposition->arguments->length();

    { Keyword* testValue000 = proposition->kind;

      if ((testValue000 == KWD_PROPOSITIONS_PREDICATE) ||
          ((testValue000 == KWD_PROPOSITIONS_FUNCTION) ||
           (testValue000 == KWD_PROPOSITIONS_ISA))) {
        if (!((boolean)(description))) {
          return;
        }
        { int arity = description->arity();
          boolean variablearityP = !(arity > 0);
          boolean functionP = proposition->kind == KWD_PROPOSITIONS_FUNCTION;

          if ((!variablearityP) &&
              (!(argumentcount == arity))) {
            handleArityViolation(proposition, arity);
          }
          { Object* arg = NULL;
            Vector* vector000 = proposition->arguments;
            int index000 = 0;
            int length000 = vector000->length();
            IntegerIntervalIterator* i = interval(1, ((variablearityP &&
                functionP) ? (argumentcount - 1) : argumentcount));
            Object* type = NULL;
            Iterator* iter000 = allDomainTypes(description);

            for  (; (index000 < length000) &&
                      (i->nextP() &&
                       iter000->nextP()); 
                  index000 = index000 + 1) {
              arg = (vector000->theArray)[index000];
              type = iter000->value;
              if (((boolean)(type)) &&
                  ((!(type == SGT_PROPOSITIONS_STELLA_THING)) &&
                   ((boolean)(arg)))) {
                verifyOneArgumentType(arg, ((Surrogate*)(type)), proposition, description);
              }
            }
          }
          if (functionP) {
            verifyOneArgumentType(proposition->arguments->last(), ((Surrogate*)(description->ioVariableTypes->last())), proposition, description);
          }
        }
      }
      else if (testValue000 == KWD_PROPOSITIONS_EQUIVALENT) {
        { Object* arg1 = (proposition->arguments->theArray)[0];
          Object* arg2 = (proposition->arguments->theArray)[1];
          Surrogate* requiredtype = NULL;
          Object* constrainingarg = NULL;
          Object* offendingarg = NULL;
          boolean typeisokP = false;
          Object* substitutevalue = NULL;

          requiredtype = safeLogicalType(arg2);
          typeisokP = checkCoercedTypeP(arg1, requiredtype, false, substitutevalue);
          if (!eqlP(arg1, substitutevalue)) {
            (proposition->arguments->theArray)[0] = substitutevalue;
            return;
          }
          else if (!typeisokP) {
            constrainingarg = arg2;
            offendingarg = arg1;
          }
          if (typeisokP) {
            requiredtype = safeLogicalType(arg1);
            typeisokP = checkCoercedTypeP(arg2, requiredtype, false, substitutevalue);
            if (!eqlP(arg2, substitutevalue)) {
              (proposition->arguments->theArray)[1] = substitutevalue;
              return;
            }
            else if (!typeisokP) {
              constrainingarg = arg1;
              offendingarg = arg2;
            }
          }
          if (!(typeisokP)) {
            { 
              BIND_STELLA_SPECIAL(oTERMUNDERCONSTRUCTIONo, Object*, oTERMUNDERCONSTRUCTIONo);
              if ((!((boolean)(oTERMUNDERCONSTRUCTIONo))) &&
                  skolemP(constrainingarg)) {
                oTERMUNDERCONSTRUCTIONo = ((Skolem*)(constrainingarg))->definingProposition;
              }
              handleArgumentTypeViolation(proposition, offendingarg, requiredtype);
            }
          }
        }
      }
      else {
      }
    }
  }
}

void handleArgumentTypeViolation(Proposition* proposition, Object* arg, Surrogate* requiredtype) {
  if (oTYPECHECKMODEo == KWD_PROPOSITIONS_POST_TYPE_VIOLATIONS) {
    postToCheckTypesAgenda(proposition);
  }
  else if (oTYPECHECKMODEo == KWD_PROPOSITIONS_REPORT_TYPE_VIOLATIONS) {
    { 
      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
      *(STANDARD_WARNING->nativeStream) << "WARNING: " << "Type check violation on argument `" << arg << "' in proposition" << std::endl << "   " << proposition << "." << std::endl << "   Argument must have type `" << requiredtype->symbolName << "'." << std::endl;
      helpSignalPropositionError(STANDARD_WARNING, KWD_PROPOSITIONS_WARNING);
    }
  }
  else if (oTYPECHECKMODEo == KWD_PROPOSITIONS_SIGNAL_TYPE_VIOLATIONS) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "ERROR: " << "Type check violation on argument `" << "`" << arg << "'" << "' in proposition" << std::endl << "   " << "`" << proposition << "'" << "." << std::endl << "   Argument must have type `" << "`" << requiredtype->symbolName << "'" << "'." << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
      }
      throw *newPropositionError(stream000->theStringReader());
    }
  }
  else if (oTYPECHECKMODEo == KWD_PROPOSITIONS_AUTOMATICALLY_FIX_TYPE_VIOLATIONS) {
    { Proposition* isaproposition = assertIsaProposition(arg, requiredtype);

      setDynamicSlotValue(isaproposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ASSERTED_BY_TYPE_CHECKERp, TRUE_WRAPPER, FALSE_WRAPPER);
    }
  }
  else {
    { OutputStringStream* stream001 = newOutputStringStream();

      *(stream001->nativeStream) << "`" << oTYPECHECKMODEo << "'" << " is not a valid case option";
      throw *newStellaException(stream001->theStringReader());
    }
  }
}

void handleArityViolation(Proposition* proposition, int requiredarity) {
  if (oTYPECHECKMODEo == KWD_PROPOSITIONS_POST_TYPE_VIOLATIONS) {
    postToCheckTypesAgenda(proposition);
  }
  else if ((oTYPECHECKMODEo == KWD_PROPOSITIONS_SIGNAL_TYPE_VIOLATIONS) ||
      ((oTYPECHECKMODEo == KWD_PROPOSITIONS_REPORT_TYPE_VIOLATIONS) ||
       (oTYPECHECKMODEo == KWD_PROPOSITIONS_AUTOMATICALLY_FIX_TYPE_VIOLATIONS))) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "ERROR: " << "Too " << "`" << (((proposition->arguments->length() > requiredarity) ? "many" : "few")) << "'" << " arguments in the proposition" << std::endl << "   " << "`" << generateTerm(proposition) << "'" << std::endl << "   Expected " << "`" << requiredarity << "'" << " argument(s)." << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
      }
      throw *newPropositionError(stream000->theStringReader());
    }
  }
  else {
    { OutputStringStream* stream001 = newOutputStringStream();

      *(stream001->nativeStream) << "`" << oTYPECHECKMODEo << "'" << " is not a valid case option";
      throw *newStellaException(stream001->theStringReader());
    }
  }
}

CheckTypesRecord* newCheckTypesRecord() {
  { CheckTypesRecord* self = NULL;

    self = new CheckTypesRecord();
    self->module = NULL;
    self->parentDescription = NULL;
    self->parentProposition = NULL;
    self->proposition = NULL;
    return (self);
  }
}

Surrogate* CheckTypesRecord::primaryType() {
  { CheckTypesRecord* self = this;

    return (SGT_PROPOSITIONS_LOGIC_CHECK_TYPES_RECORD);
  }
}

Object* accessCheckTypesRecordSlotValue(CheckTypesRecord* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_PROPOSITIONS_LOGIC_PROPOSITION) {
    if (setvalueP) {
      self->proposition = ((Proposition*)(value));
    }
    else {
      value = self->proposition;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_PARENT_PROPOSITION) {
    if (setvalueP) {
      self->parentProposition = value;
    }
    else {
      value = self->parentProposition;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_LOGIC_PARENT_DESCRIPTION) {
    if (setvalueP) {
      self->parentDescription = ((Description*)(value));
    }
    else {
      value = self->parentDescription;
    }
  }
  else if (slotname == SYM_PROPOSITIONS_STELLA_MODULE) {
    if (setvalueP) {
      self->module = ((Module*)(value));
    }
    else {
      value = self->module;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

// List of propositions that have failed a type check,
// but might pass once finalization is complete.
VectorSequence* oCHECK_TYPES_AGENDAo = NULL;

void postToCheckTypesAgenda(Proposition* self) {
  { int length = oCHECK_TYPES_AGENDAo->sequenceLength;

    if ((length == 0) ||
        (!(self == ((CheckTypesRecord*)((oCHECK_TYPES_AGENDAo->theArray)[(length - 1)]))->proposition))) {
      { CheckTypesRecord* self000 = newCheckTypesRecord();

        self000->proposition = self;
        self000->parentProposition = oTERMUNDERCONSTRUCTIONo;
        self000->parentDescription = ((Description*)(oDESCRIPTIONUNDERCONSTRUCTIONo));
        self000->module = oMODULEo;
        oCHECK_TYPES_AGENDAo->insert(self000);
      }
      length = length + 1;
    }
    if (integerMod(length, 100000) == 0) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(STANDARD_WARNING->nativeStream) << "WARNING: " << "Queued " << length << " type violations, consider running `(process-definitions)'" << std::endl;
        helpSignalPropositionError(STANDARD_WARNING, KWD_PROPOSITIONS_WARNING);
      }
    }
  }
}

void processCheckTypesAgenda() {
  if ((oCHECK_TYPES_AGENDAo->sequenceLength == 0) ||
      oINHIBITOBJECTFINALIZATIONpo) {
    return;
  }
  plLog(KWD_PROPOSITIONS_MEDIUM, 1, wrapString("Processing check-types agenda..."));
  { VectorSequence* agenda = oCHECK_TYPES_AGENDAo;
    Proposition* proposition = NULL;

    oCHECK_TYPES_AGENDAo = newVectorSequence(4);
    { CheckTypesRecord* record = NULL;
      VectorSequence* vector000 = agenda;
      int index000 = 0;
      int length000 = vector000->sequenceLength;

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        record = ((CheckTypesRecord*)((vector000->theArray)[index000]));
        proposition = record->proposition;
        if (!proposition->deletedP()) {
          { 
            BIND_STELLA_SPECIAL(oTYPECHECKMODEo, Keyword*, ((((BooleanWrapper*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue &&
                (!(oTYPE_CHECK_POLICYo == KWD_PROPOSITIONS_IGNORE_TYPE_VIOLATIONS))) ? KWD_PROPOSITIONS_REPORT_TYPE_VIOLATIONS : oTYPE_CHECK_POLICYo));
            BIND_STELLA_SPECIAL(oTERMUNDERCONSTRUCTIONo, Object*, record->parentProposition);
            BIND_STELLA_SPECIAL(oDESCRIPTIONUNDERCONSTRUCTIONo, Object*, record->parentDescription);
            BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_PROPOSITIONS_EXTENSIONAL_ASSERTION);
            if ((((boolean)(oTERMUNDERCONSTRUCTIONo)) &&
                oTERMUNDERCONSTRUCTIONo->deletedP()) ||
                (((boolean)(oDESCRIPTIONUNDERCONSTRUCTIONo)) &&
                 oDESCRIPTIONUNDERCONSTRUCTIONo->deletedP())) {
              continue;
            }
            try {
              { 
                BIND_STELLA_SPECIAL(oMODULEo, Module*, record->module);
                BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
                verifyArgumentTypesAndCount(proposition);
              }
            }
            catch (LogicException& _e) {
              LogicException* e = &_e;

              *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
            }
          }
        }
      }
    }
  }
}

void processDefinitions() {
  // Finish processing all definitions and assertions that have
  // been evaluated/loaded since that last call to 'process-definitions'.
  // PowerLoom defers complete processing of definitions to make it easier
  // to support cyclic definitions.  Following finalization of definitions,
  // this call performs semantic validation of any assertions evaluated since
  // the last call to 'process-definitions'.  PowerLoom calls this function
  // internally before each query; the primary reason to call it explicitly
  // is to force the production of any diagnostic information that results from
  // the processing and validation.
  finalizeObjects();
  processCheckTypesAgenda();
}

Proposition* buildExistsProposition(Cons* tree) {
  { Cons* variables = NULL;
    Proposition* proposition = NULL;
    Proposition* unused = NULL;

    variables = buildQuantifiedProposition(tree, true, proposition, unused);
    unused = unused;
    { Proposition* existsprop = createProposition(SYM_PROPOSITIONS_STELLA_EXISTS, 1);

      existsprop->kind = KWD_PROPOSITIONS_EXISTS;
      (existsprop->arguments->theArray)[0] = proposition;
      setDynamicSlotValue(existsprop->dynamicSlots, SYM_PROPOSITIONS_LOGIC_IO_VARIABLES, copyConsListToVariablesVector(variables), NULL);
      return (existsprop);
    }
  }
}

boolean topLevelExistsPropositionP(Proposition* proposition) {
  return ((!unknownP(proposition)) &&
      helpCollectSkolemizedExistsVariablesP(proposition, NULL));
}

Vector* collectSkolemizedExistsVariables(Proposition* proposition) {
  { List* skolems = newList();
    Vector* result = NULL;

    helpCollectSkolemizedExistsVariablesP(proposition, skolems);
    if (skolems->emptyP()) {
      result = ZERO_VARIABLES_VECTOR;
    }
    else {
      result = stella::newVector(skolems->length());
    }
    { Skolem* skolem = NULL;
      Cons* iter000 = skolems->theConsList;
      int i = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        skolem = ((Skolem*)(iter000->value));
        i = iter001;
        (result->theArray)[i] = skolem;
      }
    }
    skolems->free();
    return (result);
  }
}

boolean helpCollectSkolemizedExistsVariablesP(Proposition* proposition, List* result) {
  { Vector* arguments = proposition->arguments;
    int argumentcount = arguments->length();

    if (proposition->kind == KWD_PROPOSITIONS_FUNCTION) {
      argumentcount = argumentcount - 1;
    }
    { Object* arg = NULL;
      Vector* vector000 = arguments;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter000 = 1;
      int upperBound000 = argumentcount;
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; (index000 < length000) &&
                (unboundedP000 ||
                 (iter000 <= upperBound000)); 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        arg = (vector000->theArray)[index000];
        i = iter000;
        i = i;
        { Surrogate* testValue000 = safePrimaryType(arg);

          if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
            { Object* arg000 = arg;
              Proposition* arg = ((Proposition*)(arg000));

              if (helpCollectSkolemizedExistsVariablesP(arg, result) &&
                  (!((boolean)(result)))) {
                return (true);
              }
            }
          }
          else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE)) {
            { Object* arg001 = arg;
              PatternVariable* arg = ((PatternVariable*)(arg001));

            }
          }
          else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
            { Object* arg002 = arg;
              Skolem* arg = ((Skolem*)(arg002));

              { boolean foundP000 = false;

                { Proposition* prop = NULL;
                  Iterator* iter001 = unfilteredDependentIsaPropositions(arg)->allocateIterator();

                  for (; iter001->nextP(); ) {
                    prop = ((Proposition*)(iter001->value));
                    if ((prop->kind == KWD_PROPOSITIONS_ISA) &&
                        (trueP(prop) &&
                         coerceWrappedBooleanToBoolean(prop->variableTypeP_reader()))) {
                      foundP000 = true;
                      break;
                    }
                  }
                }
                if (foundP000) {
                  if (((boolean)(result))) {
                    result->insertNew(arg);
                  }
                  else {
                    return (true);
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
    if (((boolean)(result))) {
      return (result->nonEmptyP());
    }
    else {
      return (false);
    }
  }
}

Proposition* buildForallProposition(Cons* tree) {
  { Proposition* forallprop = createProposition(SYM_PROPOSITIONS_STELLA_FORALL, 2);

    { Cons* variables = NULL;
      Proposition* antecedent = NULL;
      Proposition* consequent = NULL;

      variables = buildQuantifiedProposition(tree, true, antecedent, consequent);
      forallprop->kind = KWD_PROPOSITIONS_FORALL;
      setDynamicSlotValue(forallprop->dynamicSlots, SYM_PROPOSITIONS_LOGIC_IO_VARIABLES, copyConsListToVariablesVector(variables), NULL);
      (forallprop->arguments->theArray)[0] = ((((boolean)(antecedent)) ? antecedent : TRUE_PROPOSITION));
      (forallprop->arguments->theArray)[1] = consequent;
    }
    return (forallprop);
  }
}

void verifyForallPropositions(Proposition* proposition) {
  { Keyword* testValue000 = proposition->kind;

    if (testValue000 == KWD_PROPOSITIONS_FORALL) {
      { Proposition* antecedent = ((Proposition*)((proposition->arguments->theArray)[0]));
        Proposition* consequent = ((Proposition*)((proposition->arguments->theArray)[1]));
        List* antvars = NULL;
        List* cqvars = NULL;

        if (antecedent->kind == KWD_PROPOSITIONS_CONSTANT) {
          return;
        }
        antvars = list(0);
        cqvars = list(0);
        collectFreeVariables(antecedent, antvars, list(0), list(0));
        collectFreeVariables(consequent, cqvars, list(0), list(0));
        if (!(cqvars->nonEmptyP() &&
            cqvars->subsetP(antvars))) {
          { 
            BIND_STELLA_SPECIAL(oTERMSOURCEBEINGPARSEDo, const char*, NULL);
            BIND_STELLA_SPECIAL(oTERMUNDERCONSTRUCTIONo, Object*, NULL);
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            BIND_STELLA_SPECIAL(oPRINTMODEo, Keyword*, KWD_PROPOSITIONS_REALISTIC);
            BIND_STELLA_SPECIAL(oPRETTYPRINTLOGICALFORMSpo, boolean, true);
            BIND_STELLA_SPECIAL(oPRETTYPRINTKIFpo, boolean, true);
            cqvars = cqvars->difference(antvars);
            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              *(STANDARD_WARNING->nativeStream) << "WARNING: " << "Potentially problematic implication rule, consequent variable(s) " << replaceSubstrings(stringify(cqvars->theConsList), "?", "|V|?") << std::endl << "   are not restricted/used by the antecedent: " << std::endl << proposition << std::endl;
              helpSignalPropositionError(STANDARD_WARNING, KWD_PROPOSITIONS_WARNING);
            }
          }
        }
      }
    }
    else if (testValue000 == KWD_PROPOSITIONS_AND) {
      { Object* arg = NULL;
        Vector* vector000 = proposition->arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          arg = (vector000->theArray)[index000];
          verifyForallPropositions(((Proposition*)(arg)));
        }
      }
    }
    else {
    }
  }
}

Object* maybeSubstituteSurrogateArgument(Object* arg1, Object* arg2) {
  if (skolemP(arg2) ||
      descriptionModeP()) {
    if (subtypeOfP(safePrimaryType(arg1), SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) {
      { Object* arg1000 = arg1;
        Description* arg1 = ((Description*)(arg1000));

        if (((boolean)(arg1->descriptionSurrogate()))) {
          return (arg1->descriptionSurrogate());
        }
      }
    }
    else {
    }
  }
  return (arg1);
}

Proposition* createImpliesProposition(Object* tail, Object* head) {
  { Proposition* impliesprop = createProposition(SYM_PROPOSITIONS_LOGIC_IMPLIES, 2);

    (impliesprop->arguments->theArray)[0] = (maybeSubstituteSurrogateArgument(tail, head));
    (impliesprop->arguments->theArray)[1] = (maybeSubstituteSurrogateArgument(head, tail));
    verifyArgumentTypesAndCount(impliesprop);
    return (impliesprop);
  }
}

Proposition* buildImpliesProposition(Cons* tree) {
  verifyNumberOfPropositionArguments(tree, 2);
  { Object* tailarg = evaluateTerm(tree->rest->value);
    Object* headarg = evaluateTerm(tree->rest->rest->value);

    return (createImpliesProposition(tailarg, headarg));
  }
}

Proposition* findDuplicateFunctionProposition(Proposition* proposition) {
  if (!isaP(proposition->operatoR, SGT_PROPOSITIONS_STELLA_SURROGATE)) {
    return (NULL);
  }
  else {
    return (findDuplicateProposition(proposition));
  }
}

Surrogate* unwrapWrappedType(Surrogate* type) {
  if (((boolean)(type)) &&
      (((boolean)(type->surrogateValue)) &&
       (isaP(type->surrogateValue, SGT_PROPOSITIONS_STELLA_CLASS) &&
        subtypeOfP(type, SGT_PROPOSITIONS_STELLA_LITERAL_WRAPPER)))) {
    type = wrappedTypeToType(type);
  }
  return (type);
}

Proposition* beginCreatingFunctionProposition(GeneralizedSymbol* surrogate, Cons* inputarguments) {
  { int argcount = inputarguments->length() + 1;
    Proposition* proposition = createProposition(SYM_PROPOSITIONS_STELLA_FUNCTION, argcount);

    proposition->operatoR = surrogate;
    { Object* arg = NULL;
      Cons* iter000 = inputarguments;
      int i = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        arg = iter000->value;
        i = iter001;
        (proposition->arguments->theArray)[i] = arg;
      }
    }
    return (proposition);
  }
}

Proposition* finishCreatingFunctionProposition(Proposition* proposition) {
  { int argcount = proposition->arguments->length();
    NamedDescription* description = getDescription(proposition->operatoR);
    Surrogate* type = NULL;
    Skolem* skolem = NULL;

    if (((boolean)(description))) {
      type = unwrapWrappedType(((Surrogate*)(description->ioVariableTypes->last())));
    }
    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, proposition->homeContext);
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      skolem = createVariableOrSkolem(type, NULL);
    }
    (proposition->arguments->theArray)[(argcount - 1)] = skolem;
    skolem->definingProposition = proposition;
    if (((boolean)(type))) {
      updateSkolemType(skolem, type);
    }
    if (proposition->operatoR == SGT_PROPOSITIONS_PL_KERNEL_KB_VALUE) {
      proposition = normalizeValueFunction(proposition);
    }
    else {
      normalizeFunctionProposition(proposition);
    }
    verifyArgumentTypesAndCount(proposition);
    if (isaP(proposition->operatoR, SGT_PROPOSITIONS_STELLA_SURROGATE)) {
      fastenDownOneProposition(proposition, true);
      helpFastenDownPropositions(proposition, false);
    }
    return (proposition);
  }
}

Proposition* findOrCreateFunctionProposition(GeneralizedSymbol* predicate, Cons* inputarguments) {
  { Proposition* proposition = beginCreatingFunctionProposition(predicate, inputarguments);
    Proposition* duplicate = ((!descriptionModeP()) ? findDuplicateFunctionProposition(proposition) : ((Proposition*)(NULL)));

    if (((boolean)(duplicate))) {
      return (duplicate);
    }
    proposition = finishCreatingFunctionProposition(proposition);
    { boolean testValue000 = false;

      if (!((BooleanWrapper*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue) {
        testValue000 = true;
      }
      else {
        { boolean alwaysP000 = true;

          { int i = NULL_INTEGER;
            int iter000 = 0;
            int upperBound000 = proposition->arguments->length() - 2;

            for  (; iter000 <= upperBound000; 
                  iter000 = iter000 + 1) {
              i = iter000;
              if (!(!variableP((proposition->arguments->theArray)[i]))) {
                alwaysP000 = false;
                break;
              }
            }
          }
          testValue000 = alwaysP000;
        }
      }
      if (testValue000) {
        runGoesTrueDemons(proposition);
      }
    }
    return (proposition);
  }
}

Proposition* createFunctionProposition(GeneralizedSymbol* predicate, Cons* inputarguments) {
  { Proposition* proposition = beginCreatingFunctionProposition(predicate, inputarguments);
    Proposition* duplicate = ((!descriptionModeP()) ? findDuplicateFunctionProposition(proposition) : ((Proposition*)(NULL)));

    if (!(!((boolean)(duplicate)))) {
      std::cerr << "Safety violation: " << "INTERNAL ERROR: encountered unexpected duplicate" << " function proposition: " << "`" << duplicate << "'";
    }
    return (finishCreatingFunctionProposition(proposition));
  }
}

Object* evaluateFunctionTerm(Cons* tree) {
  if (!(isaP(tree->value, SGT_PROPOSITIONS_STELLA_GENERALIZED_SYMBOL))) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "ERROR: " << "Illegal function name in function term: " << "`" << tree << "'" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
      }
      throw *newPropositionError(stream000->theStringReader());
    }
  }
  { GeneralizedSymbol* name = ((GeneralizedSymbol*)(tree->value));
    Object* firstargument = evaluateFirstArgument(tree->rest->value, ((Symbol*)(name)));
    LogicObject* predicatevalue = evaluatePredicate(name, firstargument);
    Cons* inputarguments = evaluateRemainingArguments(predicatevalue, tree->rest->rest);

    if (((boolean)(predicatevalue)) &&
        (isaP(predicatevalue, SGT_PROPOSITIONS_LOGIC_DESCRIPTION) &&
         (!functionDescriptionP(((NamedDescription*)(predicatevalue)))))) {
      { OutputStringStream* stream001 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream001->nativeStream) << "ERROR: " << "Relation " << "`" << ((NamedDescription*)(predicatevalue))->descriptionName() << "'" << " found in function position." << "." << std::endl;
          helpSignalPropositionError(stream001, KWD_PROPOSITIONS_ERROR);
        }
        throw *newPropositionError(stream001->theStringReader());
      }
    }
    if (((boolean)(firstargument))) {
      inputarguments = cons(firstargument, inputarguments);
    }
    if (((boolean)(predicatevalue)) &&
        (objectSurrogate(predicatevalue) == SGT_PROPOSITIONS_PL_KERNEL_KB_SETOF)) {
      inputarguments = normalizeSetofArguments(inputarguments);
    }
    { Proposition* functionproposition = findOrCreateFunctionProposition((((boolean)(predicatevalue)) ? predicatevalue->surrogateValueInverse : name), inputarguments);

      if (symbolP(functionproposition->operatoR) &&
          (!descriptionModeP())) {
        complainAboutUndeclaredReference(functionproposition);
        createDummyRelation(functionproposition);
      }
      return ((functionproposition->arguments->theArray)[(functionproposition->arguments->length() - 1)]);
    }
  }
}

boolean extensionalIndividualP(Object* individual) {
  { Surrogate* testValue000 = safePrimaryType(individual);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE)) {
      { Object* individual000 = individual;
        PatternVariable* individual = ((PatternVariable*)(individual000));

        return (false);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
      { Object* individual001 = individual;
        Skolem* individual = ((Skolem*)(individual001));

        { Proposition* definingproposition = individual->definingProposition;

          { boolean foundP000 = false;

            { Proposition* prop = NULL;
              Iterator* iter000 = unfilteredDependentPropositions(individual, NULL)->allocateIterator();

              for (; iter000->nextP(); ) {
                prop = ((Proposition*)(iter000->value));
                if ((!(prop == definingproposition)) &&
                    ((!prop->deletedP()) &&
                     ((oREVERSEPOLARITYpo ? falseP(prop) : (trueP(prop) ||
                    functionWithDefinedValueP(prop)))))) {
                  foundP000 = true;
                  break;
                }
              }
            }
            if (foundP000) {
              return (true);
            }
          }
        }
        { boolean foundP001 = false;

          { LogicObject* sk = NULL;
            Cons* iter001 = individual->variableValueInverse_reader();

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              sk = ((LogicObject*)(iter001->value));
              if (extensionalIndividualP(sk)) {
                foundP001 = true;
                break;
              }
            }
          }
          { boolean value000 = foundP001;

            return (value000);
          }
        }
      }
    }
    else {
      return (true);
    }
  }
}

boolean functionWithDefinedValueP(Proposition* proposition) {
  if (!(proposition->kind == KWD_PROPOSITIONS_FUNCTION)) {
    return (false);
  }
  { Object* lastargument = proposition->arguments->last();
    boolean resultP = testPropertyP(getDescription(((Surrogate*)(proposition->operatoR))), SGT_PROPOSITIONS_PL_KERNEL_KB_TOTAL) ||
        extensionalIndividualP(valueOf(lastargument));

    if (resultP &&
        (!worldStateP(oCONTEXTo))) {
      assignTruthValue(proposition, TRUE_WRAPPER);
      if (subtypeOfP(safePrimaryType(lastargument), SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
        { Object* lastargument000 = lastargument;
          Skolem* lastargument = ((Skolem*)(lastargument000));

          if (((boolean)(lastargument->skolemType)) &&
              (!(lastargument->skolemType == SGT_PROPOSITIONS_STELLA_THING))) {
            { 
              BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_PROPOSITIONS_EXTENSIONAL_ASSERTION);
              BIND_STELLA_SPECIAL(oINVISIBLEASSERTIONpo, boolean, true);
              assertIsaProposition(lastargument, lastargument->skolemType);
            }
          }
        }
      }
      else {
      }
    }
    return (resultP);
  }
}

Cons* normalizeSetofArguments(Cons* args) {
  return (copyConsList(args)->removeDuplicates()->sort(((cpp_function_code)(&logicFormLessP))));
}

Skolem* createEnumeratedSet(List* set) {
  { Cons* setelements = normalizeSetofArguments(set->theConsList);
    Proposition* setprop = beginCreatingFunctionProposition(SGT_PROPOSITIONS_PL_KERNEL_KB_SETOF, setelements);
    Proposition* duplicate = ((!descriptionModeP()) ? findDuplicateFunctionProposition(setprop) : ((Proposition*)(NULL)));
    Skolem* skolem = NULL;

    if (((boolean)(duplicate))) {
      return (((Skolem*)((duplicate->arguments->theArray)[(duplicate->arguments->length() - 1)])));
    }
    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, setprop->homeContext);
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      skolem = createSkolem(SGT_PROPOSITIONS_PL_KERNEL_KB_SET, NULL);
    }
    (setprop->arguments->theArray)[(setprop->arguments->length() - 1)] = skolem;
    skolem->definingProposition = setprop;
    addDependentPropositionLink(skolem, setprop);
    setDynamicSlotValue(setprop->dynamicSlots, SYM_PROPOSITIONS_LOGIC_UNFASTENEDp, NULL, NULL);
    return (skolem);
  }
}

Skolem* createLogicalList(List* list) {
  { Proposition* listprop = beginCreatingFunctionProposition(SGT_PROPOSITIONS_PL_KERNEL_KB_LISTOF, list->theConsList);
    Proposition* duplicate = ((!descriptionModeP()) ? findDuplicateFunctionProposition(listprop) : ((Proposition*)(NULL)));
    Skolem* skolem = NULL;

    if (((boolean)(duplicate))) {
      return (((Skolem*)((duplicate->arguments->theArray)[(duplicate->arguments->length() - 1)])));
    }
    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, listprop->homeContext);
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      skolem = createSkolem(SGT_PROPOSITIONS_PL_KERNEL_KB_LIST, NULL);
    }
    (listprop->arguments->theArray)[(list->length())] = skolem;
    skolem->definingProposition = listprop;
    addDependentPropositionLink(skolem, listprop);
    setDynamicSlotValue(listprop->dynamicSlots, SYM_PROPOSITIONS_LOGIC_UNFASTENEDp, NULL, NULL);
    return (skolem);
  }
}

boolean logicalCollectionP(Object* self) {
  if (subtypeOfP(safePrimaryType(self), SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
    { Object* self000 = self;
      Skolem* self = ((Skolem*)(self000));

      { Proposition* definingproposition = self->definingProposition;

        return (((boolean)(definingproposition)) &&
            collectionofPropositionP(definingproposition));
      }
    }
  }
  else {
    return (false);
  }
}

boolean functionOutputSkolemP(Object* self) {
  if (subtypeOfP(safePrimaryType(self), SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
    { Object* self000 = self;
      Skolem* self = ((Skolem*)(self000));

      return (((boolean)(self->definingProposition)));
    }
  }
  else {
    return (false);
  }
}

boolean skolemDefinedByOperatorP(Object* self, Surrogate* operatoR) {
  if (subtypeOfP(safePrimaryType(self), SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
    { Object* self000 = self;
      Skolem* self = ((Skolem*)(self000));

      { Proposition* definingproposition = self->definingProposition;

        return (((boolean)(definingproposition)) &&
            (definingproposition->operatoR == operatoR));
      }
    }
  }
  else {
    return (false);
  }
}

Skolem* getSkolemAndValueTerms(Proposition* proposition, Object*& _Return1) {
  { Object* term1 = (proposition->arguments->theArray)[0];
    Object* term2 = (proposition->arguments->theArray)[1];

    if (functionOutputSkolemP(term1)) {
      _Return1 = term2;
      return (((Skolem*)(term1)));
    }
    else if (functionOutputSkolemP(term2)) {
      _Return1 = term1;
      return (((Skolem*)(term2)));
    }
    else {
      _Return1 = NULL;
      return (NULL);
    }
  }
}

boolean enumeratedSetP(Object* self) {
  return (skolemDefinedByOperatorP(self, SGT_PROPOSITIONS_PL_KERNEL_KB_SETOF));
}

boolean enumeratedListP(Object* self) {
  return (skolemDefinedByOperatorP(self, SGT_PROPOSITIONS_PL_KERNEL_KB_LISTOF));
}

Object* canonicalizePropositionTree(Object* tree) {
  return (tree);
}

Proposition* updateEquivalenceProposition(Proposition* proposition, Keyword* updatemode) {
  { Object* term1 = (proposition->arguments->theArray)[0];
    Object* term2 = (proposition->arguments->theArray)[1];

    if (skolemP(term1) &&
        skolemP(term2)) {
      if (updatemode == KWD_PROPOSITIONS_PRESUME_TRUE) {
        { OutputStringStream* stream000 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream000->nativeStream) << "ERROR: " << "Equating two skolems by default is not yet supported." << std::endl << "." << std::endl;
            helpSignalPropositionError(stream000, KWD_PROPOSITIONS_ERROR);
          }
          throw *newPropositionError(stream000->theStringReader());
        }
      }
      return (proposition);
    }
    if ((updatemode == KWD_PROPOSITIONS_ASSERT_TRUE) ||
        (updatemode == KWD_PROPOSITIONS_PRESUME_TRUE)) {
      updatePropositionTruthValue(proposition, updatemode);
      if (clipValueP(term1, term2)) {
      }
      else if (clipValueP(term2, term1)) {
      }
      else {
        equateValues(proposition, valueOf(term1), valueOf(term2));
      }
    }
    else if (updatemode == KWD_PROPOSITIONS_RETRACT_TRUE) {
      if (unequateValuesP(term1, term2)) {
      }
      else if (unequateValuesP(term2, term1)) {
      }
    }
    else if (updatemode == KWD_PROPOSITIONS_CONCEIVE) {
      return (proposition);
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "`" << updatemode << "'" << " is not a valid case option";
        throw *newStellaException(stream001->theStringReader());
      }
    }
    if (functionOutputSkolemP(term1) &&
        (!functionOutputSkolemP(term2))) {
      runUpdatePropositionDemon(proposition, updatemode);
      return ((proposition->deletedP() ? NULL : ((Skolem*)(term1))->definingProposition));
    }
    if (functionOutputSkolemP(term2) &&
        (!functionOutputSkolemP(term1))) {
      runUpdatePropositionDemon(proposition, updatemode);
      return ((proposition->deletedP() ? NULL : ((Skolem*)(term2))->definingProposition));
    }
    return (NULL);
  }
}

Proposition* skolemizeExistsProposition(Proposition* existsproposition) {
  { KeyValueMap* mapping = newKeyValueMap();
    Proposition* skolemizedproposition = NULL;

    { PatternVariable* var = NULL;
      Vector* vector000 = ((Vector*)(dynamicSlotValue(existsproposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_IO_VARIABLES, NULL)));
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        var = ((PatternVariable*)((vector000->theArray)[index000]));
        createSkolemForUnmappedVariable(var, mapping);
      }
    }
    skolemizedproposition = recursivelyFastenDownPropositions(inheritProposition(((Proposition*)((existsproposition->arguments->theArray)[0])), mapping), false);
    destroyRedundantProposition(existsproposition);
    return (skolemizedproposition);
  }
}

Cons* helpUpdateTopLevelProposition(Proposition* proposition, Keyword* updatemode) {
  if (!((boolean)(proposition))) {
    return (NULL);
  }
  if (lookupAnnotation(proposition, KWD_PROPOSITIONS_CONFIDENCE_LEVEL) == KWD_PROPOSITIONS_DEFAULT) {
    updatemode = defaultifyUpdateMode(updatemode);
    if ((updatemode == KWD_PROPOSITIONS_PRESUME_TRUE) ||
        (updatemode == KWD_PROPOSITIONS_PRESUME_FALSE)) {
      removeAnnotation(proposition, KWD_PROPOSITIONS_CONFIDENCE_LEVEL);
    }
  }
  if (nativeSlotPropositionP(proposition)) {
    return (updateNativeSlotProposition(proposition, updatemode));
  }
  { 
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getTopLevelUpdateContext());
    { Keyword* testValue000 = proposition->kind;

      if (testValue000 == KWD_PROPOSITIONS_AND) {
        { Cons* propositions = NIL;
          PropertyList* annotations = ((PropertyList*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ANNOTATIONS, NULL)));

          { Object* arg = NULL;
            Vector* vector000 = proposition->arguments;
            int index000 = 0;
            int length000 = vector000->length();

            for  (; index000 < length000; 
                  index000 = index000 + 1) {
              arg = (vector000->theArray)[index000];
              { Proposition* p = NULL;
                Cons* iter000 = helpUpdateTopLevelProposition(((Proposition*)(arg)), updatemode);
                Cons* collect000 = NULL;

                for  (; !(iter000 == NIL); 
                      iter000 = iter000->rest) {
                  p = ((Proposition*)(iter000->value));
                  if (((boolean)(p)) &&
                      (!p->deletedP())) {
                    if (!((boolean)(collect000))) {
                      {
                        collect000 = cons(p, NIL);
                        if (propositions == NIL) {
                          propositions = collect000;
                        }
                        else {
                          addConsToEndOfConsList(propositions, collect000);
                        }
                      }
                    }
                    else {
                      {
                        collect000->rest = cons(p, NIL);
                        collect000 = collect000->rest;
                      }
                    }
                  }
                }
              }
            }
          }
          if (((boolean)(annotations))) {
            { Object* arg = NULL;
              Cons* iter001 = propositions;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                arg = iter001->value;
                inheritPropositionAnnotations(annotations, ((Proposition*)(arg)));
              }
            }
          }
          destroyRedundantProposition(proposition);
          return (propositions);
        }
      }
      else if (testValue000 == KWD_PROPOSITIONS_EQUIVALENT) {
        proposition = updateEquivalenceProposition(proposition, updatemode);
        if (!((boolean)(proposition))) {
          return (NIL);
        }
      }
      else if (testValue000 == KWD_PROPOSITIONS_NOT) {
        { Object* argument = (proposition->arguments->theArray)[0];

          if ((updatemode == KWD_PROPOSITIONS_ASSERT_TRUE) ||
              ((updatemode == KWD_PROPOSITIONS_ASSERT_FALSE) ||
               ((updatemode == KWD_PROPOSITIONS_PRESUME_TRUE) ||
                ((updatemode == KWD_PROPOSITIONS_PRESUME_FALSE) ||
                 ((updatemode == KWD_PROPOSITIONS_RETRACT_TRUE) ||
                  (updatemode == KWD_PROPOSITIONS_RETRACT_FALSE)))))) {
            updatePropositionTruthValue(((Proposition*)(argument)), invertUpdateMode(updatemode));
            inheritPropositionAnnotations(((PropertyList*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_ANNOTATIONS, NULL))), ((Proposition*)(argument)));
            destroyRedundantProposition(proposition);
            if (((boolean)(argument)) &&
                (!argument->deletedP())) {
              return (consList(1, argument));
            }
            else {
              return (NIL);
            }
          }
          else {
          }
        }
      }
      else if (testValue000 == KWD_PROPOSITIONS_EXISTS) {
        return (helpUpdateTopLevelProposition(skolemizeExistsProposition(proposition), updatemode));
      }
      else {
      }
    }
    if (!(proposition->kind == KWD_PROPOSITIONS_FUNCTION)) {
      updatePropositionTruthValue(proposition, updatemode);
    }
    if (proposition->deletedP()) {
      return (NIL);
    }
    else {
      return (consList(1, proposition));
    }
  }
}

Keyword* invertUpdateMode(Keyword* updatemode) {
  if (updatemode == KWD_PROPOSITIONS_ASSERT_TRUE) {
    return (KWD_PROPOSITIONS_ASSERT_FALSE);
  }
  else if (updatemode == KWD_PROPOSITIONS_PRESUME_TRUE) {
    return (KWD_PROPOSITIONS_PRESUME_FALSE);
  }
  else if (updatemode == KWD_PROPOSITIONS_RETRACT_TRUE) {
    return (KWD_PROPOSITIONS_RETRACT_FALSE);
  }
  else if (updatemode == KWD_PROPOSITIONS_ASSERT_FALSE) {
    return (KWD_PROPOSITIONS_ASSERT_TRUE);
  }
  else if (updatemode == KWD_PROPOSITIONS_PRESUME_FALSE) {
    return (KWD_PROPOSITIONS_PRESUME_TRUE);
  }
  else if (updatemode == KWD_PROPOSITIONS_RETRACT_FALSE) {
    return (KWD_PROPOSITIONS_RETRACT_TRUE);
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << updatemode << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Keyword* defaultifyUpdateMode(Keyword* updatemode) {
  if (updatemode == KWD_PROPOSITIONS_ASSERT_TRUE) {
    return (KWD_PROPOSITIONS_PRESUME_TRUE);
  }
  else if (updatemode == KWD_PROPOSITIONS_ASSERT_FALSE) {
    return (KWD_PROPOSITIONS_PRESUME_FALSE);
  }
  else {
    return (updatemode);
  }
}

Cons* updateTopLevelProposition(Object* tree, Keyword* updatemode) {
  if ((updatemode == KWD_PROPOSITIONS_ASSERT_FALSE) ||
      ((updatemode == KWD_PROPOSITIONS_PRESUME_FALSE) ||
       (updatemode == KWD_PROPOSITIONS_RETRACT_FALSE))) {
    tree = listO(3, SYM_PROPOSITIONS_STELLA_NOT, tree, NIL);
    updatemode = invertUpdateMode(updatemode);
  }
  else {
  }
  if (updatemode == KWD_PROPOSITIONS_ASSERT_TRUE) {
    { 
      BIND_STELLA_SPECIAL(oAUTOMATICINSTANCETABLEo, KeyValueList*, NULL);
      return (helpUpdateTopLevelProposition(buildTopLevelProposition(tree, true), updatemode));
    }
  }
  else {
    return (helpUpdateTopLevelProposition(buildTopLevelProposition(tree, false), updatemode));
  }
}

Object* standardizePropositionTree(Object* tree) {
  if (stringP(tree)) {
    tree = readSExpressionFromString(((StringWrapper*)(tree))->wrapperValue);
  }
  tree = standardizeLogicalParseTree(tree);
  if (consP(tree)) {
    tree = canonicalizePropositionTree(tree);
  }
  return (tree);
}

Cons* updateProposition(Object* tree, Keyword* updatemode) {
  try {
    { 
      BIND_STELLA_SPECIAL(oINHIBITOBJECTFINALIZATIONpo, boolean, true);
      return (updateTopLevelProposition(standardizePropositionTree(tree), updatemode));
    }
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
  }
  catch (ReadException& _e) {
    ReadException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
  }
  return (NULL);
}

Object* buildTopLevelTerm(Object* tree) {
  { Object* term = NULL;

    { 
      BIND_STELLA_SPECIAL(oLOGICVARIABLETABLEo, Cons*, NIL);
      BIND_STELLA_SPECIAL(oVARIABLEIDCOUNTERo, int, 0);
      BIND_STELLA_SPECIAL(oTERMUNDERCONSTRUCTIONo, Object*, tree);
      if (safePrimaryType(tree) == SGT_PROPOSITIONS_STELLA_CONS) {
        { Object* tree000 = tree;
          Cons* tree = ((Cons*)(tree000));

          if (getQuotedTree("((FORALL EXISTS IMPLIES AND OR NOT) \"/LOGIC\")", "/LOGIC")->memberP(tree->value)) {
            *(STANDARD_WARNING->nativeStream) << "Warning: " << "Sentence where term expected: " << "`" << tree << "'" << std::endl << std::endl;
            return (NULL);
          }
        }
      }
      else {
      }
      term = evaluateTerm(tree);
    }
    return (term);
  }
}

Object* conceiveTerm(Object* tree) {
  // `tree' is a term expression (a string or an s-expression),
  // or is a class reference (a symbol or surrogate).  Return a (possibly 
  // newly-conceived) term representing the internalized representation of that term.
  try {
    { Object* standardizedtree = standardizePropositionTree(tree);
      Object* operatoR = NULL;
      Object* term = NULL;

      if (consP(standardizedtree)) {
        operatoR = ((Cons*)(standardizedtree))->value;
      }
      if (((boolean)(operatoR)) &&
          (((boolean)(getRelation(operatoR))) &&
           (!functionP(getRelation(operatoR))))) {
        term = conceiveSentence(tree);
      }
      else {
        term = buildTopLevelTerm(standardizedtree);
      }
      return (term);
    }
  }
  catch (LogicException& _e) {
    LogicException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
  }
  catch (ReadException& _e) {
    ReadException* e = &_e;

    *(STANDARD_ERROR->nativeStream) << exceptionMessage(e);
  }
  return (NULL);
}

Object* conceiveSentence(Object* tree) {
  if (subtypeOfStringP(safePrimaryType(tree))) {
    { Object* tree000 = tree;
      StringWrapper* tree = ((StringWrapper*)(tree000));

      return (conceiveSentence(readSExpressionFromString(tree->wrapperValue)));
    }
  }
  else {
    return (smartUpdateProposition(tree, KWD_PROPOSITIONS_CONCEIVE));
  }
}

Object* conceiveFormula(Object* tree) {
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (subtypeOfStringP(testValue000)) {
      { Object* tree000 = tree;
        StringWrapper* tree = ((StringWrapper*)(tree000));

        return (conceiveFormula(readSExpressionFromString(tree->wrapperValue)));
      }
    }
    else if (testValue000 == SGT_PROPOSITIONS_STELLA_CONS) {
      { Object* tree001 = tree;
        Cons* tree = ((Cons*)(tree001));

        if (symbolP(tree->value)) {
          { GeneralizedSymbol* testValue001 = ((GeneralizedSymbol*)(tree->value));

            if ((testValue001 == SYM_PROPOSITIONS_LOGIC_KAPPA) ||
                ((testValue001 == SYM_PROPOSITIONS_LOGIC_LAMBDA) ||
                 ((testValue001 == SYM_PROPOSITIONS_LOGIC_SETOFALL) ||
                  ((testValue001 == SYM_PROPOSITIONS_PL_KERNEL_KB_SETOF) ||
                   ((testValue001 == SYM_PROPOSITIONS_PL_KERNEL_KB_LISTOF) ||
                    (testValue001 == SYM_PROPOSITIONS_LOGIC_BAGOF)))))) {
              return (conceiveTerm(tree));
            }
            else {
            }
          }
        }
        return (conceiveSentence(tree));
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* tree002 = tree;
        Symbol* tree = ((Symbol*)(tree002));

        return (conceiveTerm(tree));
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* tree003 = tree;
        Surrogate* tree = ((Surrogate*)(tree003));

        return (conceiveTerm(internSymbolInModule(tree->symbolName, ((Module*)(tree->homeContext)), true)));
      }
    }
    else {
      return (conceiveSentence(tree));
    }
  }
}

Object* smartUpdateProposition(Object* tree, Keyword* updatemode) {
  { Cons* propositions = updateProposition(tree, updatemode);

    if (((boolean)(propositions)) &&
        (propositions->rest == NIL)) {
      return (((Proposition*)(propositions->value)));
    }
    else {
      return (propositions);
    }
  }
}

Object* asserT(Object* proposition) {
  // Assert the truth of `proposition'.  Return the asserted proposition object.
  // KIF example:  "(assert (happy Fred))" asserts that Fred is indeed happy.
  // Note that for this assertion to succeed, the relation `happy' must already
  // be defined.  If the constant `Fred' has not yet been created, it is
  // automatically created as a side-effect of calling `assert'.
  return (smartUpdateProposition(proposition, KWD_PROPOSITIONS_ASSERT_TRUE));
}

Object* presume(Object* proposition) {
  // Presume the default truth of `proposition'.  Return the presumed
  // proposition object.  KIF example:  "(presume (happy Fred))" states that Fred
  // is most probably happy.  Note, that for this to succeed, the relation
  // `happy' must already be defined (see `assert').
  return (smartUpdateProposition(proposition, KWD_PROPOSITIONS_PRESUME_TRUE));
}

Object* retract(Object* proposition) {
  // Retract the truth of `proposition'.  Return the retracted proposition
  // object.  KIF example:  "(retract (happy Fred))" retracts that Fred is
  // happy.  Note that for this assertion to succeed, the relation `happy' must already
  // be defined.  If the constant `Fred' has not yet been created, it is
  // automatically created as a side-effect of calling `retract'.
  return (smartUpdateProposition(proposition, KWD_PROPOSITIONS_RETRACT_TRUE));
}

Object* deny(Object* proposition) {
  // Assert the falsity of `proposition'.  Return the asserted proposition
  // object.  KIF example:  "(deny (happy Fred))" asserts that Fred is not happy,
  // which could have been done equivalently by "(assert (not (happy Fred)))".
  // Note, that for this to succeed, the relation `happy' must already be defined
  // (see `assert').
  return (smartUpdateProposition(proposition, KWD_PROPOSITIONS_ASSERT_FALSE));
}

Object* conceive(Object* formula) {
  // Guess whether 'formula' represents a term or a sentence/proposition.
  // If we are not sure, assume its a proposition.
  // If it is a term, return its internal representation.  If a proposition,
  // construct a proposition for 'formula' without asserting its truth value.
  // Return the conceived proposition object.  KIF example: "(conceive (happy Fred))"
  // builds the proposition expressing that Fred is happy without explictly asserting
  // or denying it.  Note, that for this to succeed, the relation `happy' must already
  // be defined (see `assert').  If the logic constant `Fred' has not yet been
  // created, it is automatically created as a side-effect of calling `conceive'.
  return (conceiveFormula(formula));
}

Object* unassert(Object* proposition) {
  // Retract the truth, falsity or inconsistency of `proposition'.  This is a
  // more general version of `retract' that also handles falsity.  For example, if
  // we assert the proposition "(not (sad Fred))", and then execute the statement
  // "(unassert (sad Fred))", the truth value of the proposition "(sad Fred)"
  // will be set to UNKNOWN.  If we had called `retract' in place of `unassert',
  // the proposition "(sad Fred)" would remain set to FALSE.   Note that for this
  // unassertion to succeed, the logic constant `Fred' and the relation `sad' must
  // already be defined.
  { Cons* parsedprops = updateProposition(proposition, KWD_PROPOSITIONS_CONCEIVE);
    Cons* result = NIL;

    if (((boolean)(parsedprops))) {
      { Proposition* prop = NULL;
        Cons* iter000 = parsedprops;
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          prop = ((Proposition*)(iter000->value));
          if (prop->kind == KWD_PROPOSITIONS_NOT) {
            prop = ((Proposition*)((prop->arguments->theArray)[0]));
          }
          unassertProposition(prop);
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(prop, NIL);
              if (result == NIL) {
                result = collect000;
              }
              else {
                addConsToEndOfConsList(result, collect000);
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
    return (((result->length() > 1) ? result : result->value));
  }
}

void unassertProposition(Proposition* self) {
  // Retract the truth, falsity or inconsistency of the proposition `self'.
  if (((boolean)(self))) {
    { boolean equivalenceP = self->kind == KWD_PROPOSITIONS_EQUIVALENT;

      if (trueP(self)) {
        if (equivalenceP) {
          updateEquivalenceProposition(self, KWD_PROPOSITIONS_RETRACT_TRUE);
        }
        else {
          updatePropositionTruthValue(self, KWD_PROPOSITIONS_RETRACT_TRUE);
        }
      }
      else if (falseP(self)) {
        if (equivalenceP) {
          updateEquivalenceProposition(self, KWD_PROPOSITIONS_RETRACT_FALSE);
        }
        else {
          updatePropositionTruthValue(self, KWD_PROPOSITIONS_RETRACT_FALSE);
        }
      }
      else if (inconsistentP(self)) {
        if (equivalenceP) {
          deassignTruthValue(self, KWD_PROPOSITIONS_RETRACT_INCONSISTENT);
          updateEquivalenceProposition(self, KWD_PROPOSITIONS_RETRACT_TRUE);
          updateEquivalenceProposition(self, KWD_PROPOSITIONS_RETRACT_FALSE);
        }
        else {
          deassignTruthValue(self, KWD_PROPOSITIONS_RETRACT_INCONSISTENT);
          updatePropositionTruthValue(self, KWD_PROPOSITIONS_RETRACT_TRUE);
          updatePropositionTruthValue(self, KWD_PROPOSITIONS_RETRACT_FALSE);
        }
      }
    }
  }
}

boolean Proposition::deletedP() {
  { Proposition* self = this;

    return (deletedPropositionP(self));
  }
}

boolean Proposition::deletedPSetter(boolean value) {
  { Proposition* self = this;

    if (value) {
      self->kind = KWD_PROPOSITIONS_DELETED;
    }
    return (value);
  }
}

boolean deletedPropositionP(Proposition* self) {
  if (self->kind == KWD_PROPOSITIONS_DELETED) {
    return (true);
  }
  return (false);
}

DEFINE_STELLA_SPECIAL(oDEFERRED_TERMS_TO_UNLINKo, HashSet* , NULL);

Proposition* destroyProposition(Proposition* proposition) {
  // Retract and destroy the proposition 'proposition'.
  // Recursively destroy all propositions that reference 'proposition'.
  // Also, destroy all satellite propositions of 'proposition'.
  if (proposition->deletedP()) {
    return (proposition);
  }
  proposition->deletedPSetter(true);
  if (((boolean)(((Surrogate*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_STELLA_SURROGATE_VALUE_INVERSE, NULL)))))) {
    ((Surrogate*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_STELLA_SURROGATE_VALUE_INVERSE, NULL)))->surrogateValue = NULL;
  }
  { Object* arg = NULL;
    Vector* vector000 = proposition->arguments;
    int index000 = 0;
    int length000 = vector000->length();

    for  (; index000 < length000; 
          index000 = index000 + 1) {
      arg = (vector000->theArray)[index000];
      if (((boolean)(arg)) &&
          (!arg->deletedP())) {
        if (skolemP(arg) &&
            (((Skolem*)(arg))->definingProposition == proposition)) {
          destroyTerm(((LogicObject*)(arg)));
        }
        if (((boolean)(oDEFERRED_TERMS_TO_UNLINKo))) {
          oDEFERRED_TERMS_TO_UNLINKo->insert(arg);
        }
        else {
          removeDependentPropositionLink(arg, proposition);
        }
      }
    }
  }
  { Object* dep = NULL;
    Iterator* iter000 = proposition->dependentPropositions->copy()->allocateIterator();

    for (; iter000->nextP(); ) {
      dep = iter000->value;
      destroyProposition(((Proposition*)(dep)));
    }
  }
  { Proposition* satellite = NULL;
    Cons* iter001 = proposition->satellitePropositions_reader()->copy()->theConsList;

    for (; !(iter001 == NIL); iter001 = iter001->rest) {
      satellite = ((Proposition*)(iter001->value));
      destroyProposition(satellite);
    }
  }
  if (((boolean)(((Proposition*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_MASTER_PROPOSITION, NULL)))))) {
    ((Proposition*)(dynamicSlotValue(proposition->dynamicSlots, SYM_PROPOSITIONS_LOGIC_MASTER_PROPOSITION, NULL)))->satellitePropositions_reader()->remove(proposition);
  }
  if (!(!((boolean)(proposition->homeContext)))) {
    handleOutOfDateInferenceCache(KWD_PROPOSITIONS_RETRACT, proposition);
  }
  proposition->dependentPropositions = NULL;
  proposition->operatoR = NULL;
  proposition->arguments = NULL;
  proposition->homeContext = NULL;
  proposition->truthValue = NULL;
  proposition->dynamicSlots = NULL;
  return (proposition);
}

void destroyRedundantProposition(Proposition* proposition) {
  proposition->homeContext = NULL;
  destroyProposition(proposition);
}

void destroyLogicInstance(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* self000 = self;
        LogicObject* self = ((LogicObject*)(self000));

        if ((!((boolean)(self))) ||
            self->deletedP()) {
          return;
        }
        self->deletedPSetter(true);
        { Surrogate* surrogate = self->surrogateValueInverse;

          if (((boolean)(surrogate)) &&
              (surrogate->surrogateValue == self)) {
            surrogate->surrogateValue = NULL;
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_THING)) {
      { Object* self001 = self;
        Thing* self = ((Thing*)(self001));

        if ((!((boolean)(self))) ||
            self->deletedP()) {
          return;
        }
        self->deletedPSetter(true);
        { Surrogate* surrogate = self->surrogateValueInverse;

          if (((boolean)(surrogate)) &&
              (surrogate->surrogateValue == self)) {
            surrogate->surrogateValue = NULL;
          }
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
  { Proposition* p = NULL;
    Iterator* iter000 = unfilteredDependentPropositions(self, NULL)->allocateIterator();

    for (; iter000->nextP(); ) {
      p = ((Proposition*)(iter000->value));
      destroyProposition(p);
    }
  }
  if (subtypeOfP(safePrimaryType(self), SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
    { Object* self004 = self;
      LogicObject* self = ((LogicObject*)(self004));

      unlinkEquivalentValue(self);
      { LogicObject* equivalent = NULL;
        Cons* iter001 = self->variableValueInverse_reader();

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          equivalent = ((LogicObject*)(iter001->value));
          if (!equivalent->deletedP()) {
            { Surrogate* testValue001 = safePrimaryType(equivalent);

              if (subtypeOfP(testValue001, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
                { LogicObject* equivalent000 = equivalent;
                  Skolem* equivalent = ((Skolem*)(equivalent000));

                  { Skolem* object000 = equivalent;
                    Object* value000 = NULL;
                    Object* oldValue000 = object000->variableValue;
                    Object* newValue000 = updateInContext(oldValue000, value000, object000->homeContext, false);

                    if (!(((boolean)(oldValue000)) &&
                        (oldValue000->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
                      object000->variableValue = newValue000;
                    }
                  }
                }
              }
              else if (subtypeOfP(testValue001, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
                { LogicObject* equivalent001 = equivalent;
                  LogicObject* equivalent = equivalent001;

                  { LogicObject* object001 = equivalent;
                    Description* value001 = NULL;
                    Object* oldValue001 = dynamicSlotValue(object001->dynamicSlots, SYM_PROPOSITIONS_LOGIC_EQUIVALENT_VALUE, NULL);
                    Object* newValue001 = updateInContext(oldValue001, value001, object001->homeContext, false);

                    if (!(((boolean)(oldValue001)) &&
                        (oldValue001->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
                      setDynamicSlotValue(object001->dynamicSlots, SYM_PROPOSITIONS_LOGIC_EQUIVALENT_VALUE, newValue001, NULL);
                    }
                  }
                }
              }
              else {
                { OutputStringStream* stream001 = newOutputStringStream();

                  *(stream001->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                  throw *newStellaException(stream001->theStringReader());
                }
              }
            }
          }
        }
      }
      { LogicObject* object002 = self;
        Cons* value002 = NULL;
        Object* oldValue002 = object002->variableValueInverse;
        Object* newValue002 = updateInContext(oldValue002, value002, object002->homeContext, false);

        if (!(((boolean)(oldValue002)) &&
            (oldValue002->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
          object002->variableValueInverse = newValue002;
        }
      }
    }
  }
  else {
  }
}

void destroyTerm(LogicObject* self) {
  // Destroy all propositions that reference 'self',
  // and mark it as 'deleted?', thereby making it invisible within class
  // extensions.  Unlink descriptions from native relations.
  if ((!((boolean)(self))) ||
      self->deletedP()) {
    return;
  }
  destroyLogicInstance(self);
  if (subtypeOfP(safePrimaryType(self), SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) {
    { LogicObject* self000 = self;
      Description* self = ((Description*)(self000));

      if (subtypeOfP(safePrimaryType(self), SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
        { Description* self001 = self;
          NamedDescription* self = ((NamedDescription*)(self001));

          { Relation* nativerelation = self->nativeRelation();

            self->nativeRelationSetter(NULL);
            if (((boolean)(nativerelation))) {
              setDynamicSlotValue(nativerelation->dynamicSlots, SYM_PROPOSITIONS_LOGIC_DESCRIPTION, NULL, NULL);
            }
            if (((boolean)(self->extension))) {
              self->extension = NULL;
            }
          }
        }
      }
      else {
      }
      { Description* complement = ((Description*)(dynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_COMPLEMENT_DESCRIPTION, NULL)));

        if (((boolean)(complement))) {
          setDynamicSlotValue(complement->dynamicSlots, SYM_PROPOSITIONS_LOGIC_COMPLEMENT_DESCRIPTION, NULL, NULL);
          setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_COMPLEMENT_DESCRIPTION, NULL, NULL);
        }
      }
      removeAllDependentPropositionLinks(self);
      self->ioVariables = NULL;
      self->internalVariables = NULL;
      self->proposition = NULL;
      self->homeContext = NULL;
    }
  }
  else {
  }
  self->dynamicSlots->clear();
  self->deletedPSetter(true);
}

void destroyInstance(Object* self) {
  // Destroy all propositions that reference 'self',
  // and mark it as 'deleted?', thereby making it invisible within class
  // extensions.
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* self000 = self;
        LogicObject* self = ((LogicObject*)(self000));

        destroyTerm(self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_THING)) {
      { Object* self001 = self;
        Thing* self = ((Thing*)(self001));

        destroyLogicInstance(self);
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

void destroyObject(Object* self) {
  // Destroy `self' which can be a term or a proposition.  Destroy all
  // propositions that reference 'self' and mark it as 'deleted?' (thereby
  // making it invisible within class extensions).
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* self000 = self;
        LogicObject* self = ((LogicObject*)(self000));

        destroyTerm(self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_THING)) {
      { Object* self001 = self;
        Thing* self = ((Thing*)(self001));

        destroyLogicInstance(self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
      { Object* self002 = self;
        Proposition* self = ((Proposition*)(self002));

        destroyProposition(self);
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

Object* destroy(Object* objectspec) {
  // Find an object or proposition as specified by `objectSpec', and destroy all
  // propositions and indices that reference it.  `objectSpec' must be a name or
  // a parse tree that evaluates to a proposition.  Return the deleted object, or
  // NULL if no matching object was found.
  { Object* object = NULL;

    if (safePrimaryType(objectspec) == SGT_PROPOSITIONS_STELLA_CONS) {
      { Object* objectspec000 = objectspec;
        Cons* objectspec = ((Cons*)(objectspec000));

        object = conceiveFormula(objectspec);
      }
    }
    else {
      object = coerceToInstanceInModule(objectspec, NULL, false, NULL);
    }
    if (((boolean)(object))) {
      destroyObject(object);
    }
    return (object);
  }
}

boolean relationInModuleP(NamedDescription* self) {
  return (self->homeContext == oMODULEo);
}

void introduceModule(Module* module) {
  module->surrogateValueInverse = NULL;
  { 
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oPL_KERNEL_MODULEo);
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
    if (!((boolean)(module->surrogateValueInverse))) {
      { boolean successP = false;
        Object* unused = NULL;
        Surrogate* surrogate = NULL;

        successP = bindToSurrogateP(module, module->name(), true, true, unused, surrogate);
        unused = unused;
        if (successP) {
          module->surrogateValueInverse = surrogate;
        }
      }
    }
    assertIsaProposition(module, SGT_PROPOSITIONS_STELLA_MODULE);
  }
}

void clearLogicModuleHook(Module* module) {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    { 
      BIND_STELLA_SPECIAL(oDEFERRED_TERMS_TO_UNLINKo, HashSet*, newHashSet());
      destroyInferenceCaches(module);
      clearInlineQueryCaches();
      { Object* term = NULL;
        Cons* iter000 = allTerms(module, true)->listify()->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          term = iter000->value;
          destroyInstance(term);
        }
      }
      { Proposition* proposition = NULL;
        Iterator* iter001 = allPropositions(module, true);

        for (; iter001->nextP(); ) {
          proposition = ((Proposition*)(iter001->value));
          destroyProposition(proposition);
        }
      }
      { Object* term = NULL;
        DictionaryIterator* iter002 = ((DictionaryIterator*)(oDEFERRED_TERMS_TO_UNLINKo->allocateIterator()));

        for (; iter002->nextP(); ) {
          term = iter002->value;
          if (!term->deletedP()) {
            { BacklinksIndex* index = getBacklinksIndex(term);

              if (((boolean)(index))) {
                index->removeDeletedMembers();
              }
            }
          }
        }
      }
      cleanupStructuredObjectsIndex(module);
      locallyConceivedPropositions(module)->removeDeletedMembers();
      locallyConceivedInstances(module)->removeDeletedMembers();
      cleanupAllDescriptionExtensions();
      cleanupUnfinalizedObjects();
      { Proposition* proposition = NULL;
        Iterator* iter003 = allLocallyModifiedPropositions(module);

        for (; iter003->nextP(); ) {
          proposition = ((Proposition*)(iter003->value));
          { Object* truthvalue = proposition->truthValue;

            if (((boolean)(truthvalue)) &&
                isaP(truthvalue, SGT_PROPOSITIONS_STELLA_KEY_VALUE_LIST)) {
              ((KeyValueList*)(truthvalue))->removeAt(module);
            }
          }
        }
      }
      clearMemoizationTables(KWD_PROPOSITIONS_KB_UPDATE);
      clearMemoizationTables(KWD_PROPOSITIONS_META_KB_UPDATE);
    }
  }
}

void clearInstances(Cons* name) {
  // Destroy all instances belonging to module `name' or any of its children.
  // Leave meta-objects, e.g., concepts and relations, alone.
  // If no `name' is supplied, the current module will be cleared after
  // confirming with the user.
  { Cons* optionalname = name;
    Module* module = coerceToModule(optionalname->value, true);

    if (((boolean)(module))) {
      if ((!(optionalname == NIL)) ||
          yOrNP(stringConcatenate("Really clear instances of module ", stringConcatenate(module->moduleFullName, "? ", 0), 0))) {
        doClearInstances(module);
      }
    }
  }
}

void clearInstancesEvaluatorWrapper(Cons* arguments) {
  clearInstances(arguments);
}

void doClearInstances(Module* module) {
  // Function version of `clear-instances' that evaluates its argument.
  { Context* child = NULL;
    Cons* iter000 = module->childContexts->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      child = ((Context*)(iter000->value));
      if (isaP(child, SGT_PROPOSITIONS_STELLA_MODULE)) {
        doClearInstances(((Module*)(child)));
      }
    }
  }
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    destroyInferenceCaches(module);
    { LogicObject* instance = NULL;
      Iterator* iter001 = allInstances(module, true);

      for (; iter001->nextP(); ) {
        instance = ((LogicObject*)(iter001->value));
        destroyInstance(instance);
      }
    }
    locallyConceivedPropositions(module)->removeDeletedMembers();
  }
}

void destroyLogicContextHook(Context* self) {
  setDynamicSlotValue(self->dynamicSlots, SYM_PROPOSITIONS_LOGIC_MONOTONICp, FALSE_WRAPPER, FALSE_WRAPPER);
  { 
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, self);
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
    { LogicObject* i = NULL;
      Iterator* iter000 = locallyConceivedInstances(self)->allocateIterator();

      for (; iter000->nextP(); ) {
        i = ((LogicObject*)(iter000->value));
        destroyTerm(i);
      }
    }
  }
  if (isaP(self, SGT_PROPOSITIONS_STELLA_MODULE)) {
    clearLogicModuleHook(((Module*)(self)));
    self->surrogateValueInverse->surrogateValue = NULL;
  }
  if (isaP(self, SGT_PROPOSITIONS_STELLA_WORLD)) {
    unlinkInferenceCache(((World*)(self)));
    unlinkPropagationEnvironment(self);
  }
  self->dynamicSlots->clear();
}

void clearCaches() {
  // Clear all query and memoization caches.
  clearQueryResultsCache();
  clearInlineQueryCaches();
  clearAllMemoizationTables();
}

void resetPowerloom() {
  // Reset PowerLoom to its initial state.
  // CAUTION: This will destroy all loaded knowledge bases and might break other
  // loaded STELLA systems if they do reference PowerLoom symbols in their code.
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    { List* modules = list(4, getStellaModule("PLI", true), oPL_ANONYMOUS_MODULEo, oPL_KERNEL_MODULEo, oLOGIC_MODULEo);

      { Module* mod = NULL;
        Cons* iter000 = modules->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          mod = ((Module*)(iter000->value));
          setDynamicSlotValue(mod->dynamicSlots, SYM_PROPOSITIONS_STELLA_CLEARABLEp, TRUE_WRAPPER, FALSE_WRAPPER);
          setDynamicSlotValue(mod->dynamicSlots, SYM_PROPOSITIONS_STELLA_PROTECT_SURROGATESp, FALSE_WRAPPER, FALSE_WRAPPER);
          { Context* sub = NULL;
            AllPurposeIterator* iter001 = allSubcontexts(mod, KWD_PROPOSITIONS_PREORDER);

            for (; iter001->nextP(); ) {
              sub = ((Context*)(iter001->value));
              if (subtypeOfP(safePrimaryType(sub), SGT_PROPOSITIONS_STELLA_MODULE)) {
                { Context* sub000 = sub;
                  Module* sub = ((Module*)(sub000));

                  setDynamicSlotValue(sub->dynamicSlots, SYM_PROPOSITIONS_STELLA_CLEARABLEp, TRUE_WRAPPER, FALSE_WRAPPER);
                  setDynamicSlotValue(sub->dynamicSlots, SYM_PROPOSITIONS_STELLA_PROTECT_SURROGATESp, FALSE_WRAPPER, FALSE_WRAPPER);
                }
              }
              else {
              }
            }
          }
        }
      }
      { Module* mod = NULL;
        Cons* iter002 = modules->theConsList;

        for (; !(iter002 == NIL); iter002 = iter002->rest) {
          mod = ((Module*)(iter002->value));
          clearContext(mod);
        }
      }
      dropHook(oDEFINE_MODULE_HOOKSo, SYM_PROPOSITIONS_LOGIC_INTRODUCE_MODULE);
      dropHook(oCLEAR_MODULE_HOOKSo, SYM_PROPOSITIONS_LOGIC_CLEAR_LOGIC_MODULE_HOOK);
      dropHook(oDESTROY_CONTEXT_HOOKSo, SYM_PROPOSITIONS_LOGIC_DESTROY_LOGIC_CONTEXT_HOOK);
      dropHook(oREDEFINE_RELATION_HOOKSo, SYM_PROPOSITIONS_LOGIC_TRANSFER_LOGIC_INFORMATION_FROM_RELATION_HOOK);
      { Module* mod = NULL;
        Cons* iter003 = modules->theConsList;

        for (; !(iter003 == NIL); iter003 = iter003->rest) {
          mod = ((Module*)(iter003->value));
          destroyModule(mod);
        }
      }
      oPL_KERNEL_MODULEo = NULL;
      oLOGIC_MODULEo = NULL;
      clearAllMemoizationTables();
      startupLogicSystem();
    }
  }
  getStellaModule("PL-USER", true)->changeModule();
}

boolean consLessThanP(Cons* o1, Cons* o2) {
  { Object* i1 = NULL;
    Cons* iter000 = o1;
    Object* i2 = NULL;
    Cons* iter001 = o2;

    for  (; (!(iter000 == NIL)) &&
              (!(iter001 == NIL)); 
          iter000 = iter000->rest,
          iter001 = iter001->rest) {
      i1 = iter000->value;
      i2 = iter001->value;
      if (logicFormLessP(i1, i2)) {
        return (true);
      }
      if (logicFormLessP(i2, i1)) {
        return (false);
      }
    }
  }
  return (o1->length() < o2->length());
}

boolean stringTermLessP(const char* s1, const char* s2) {
  return (stringCompareCaseNormalized(s1, s2) < 0);
}

boolean safeStringTermLessP(const char* s1, const char* s2) {
  if ((s1 != NULL) &&
      (s2 != NULL)) {
    return (stringCompareCaseNormalized(s1, s2) < 0);
  }
  else if (s2 != NULL) {
    return (false);
  }
  else {
    return (true);
  }
}

boolean safeQuantityLessP(Quantity* q1, Object* o2) {
  if (((boolean)(q1)) &&
      ((boolean)(o2))) {
    try {
      return (q1->lessP(o2));
    }
    catch (IncompatibleQuantityException ) {
      return (false);
    }
  }
  else if (((boolean)(o2))) {
    return (false);
  }
  else {
    return (true);
  }
}

boolean safeQuantityGreaterEqualP(Quantity* q1, Object* o2) {
  if (((boolean)(q1)) &&
      ((boolean)(o2))) {
    try {
      return (q1->greaterEqualP(o2));
    }
    catch (IncompatibleQuantityException ) {
      return (false);
    }
  }
  else if (((boolean)(o2))) {
    return (false);
  }
  else {
    return (true);
  }
}

boolean objectNameLessThanP(LogicObject* o1, LogicObject* o2) {
  return (safeStringTermLessP(objectName(o1)->symbolName, objectName(o2)->symbolName));
}

boolean moduleNameLessThanP(Context* m1, Context* m2) {
  return (safeStringTermLessP(m1->contextName(), m2->contextName()));
}

boolean propositionLessThanP(Proposition* p1, Proposition* p2) {
  { const char* operator1 = p1->operatoR->symbolName;
    const char* operator2 = p2->operatoR->symbolName;
    Vector* arguments1 = p1->arguments;
    Vector* arguments2 = p2->arguments;
    int end1 = arguments1->length() - 1;
    int end2 = arguments2->length() - 1;
    Object* a1 = NULL;
    Object* a2 = NULL;

    if (stringTermLessP(operator1, operator2)) {
      return (true);
    }
    if (stringTermLessP(operator2, operator1)) {
      return (false);
    }
    { int i1 = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = end1;
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;
      int i2 = NULL_INTEGER;
      int iter001 = 0;
      int upperBound001 = end2;
      boolean unboundedP001 = upperBound001 == NULL_INTEGER;

      for  (; (unboundedP000 ||
                (iter000 <= upperBound000)) &&
                (unboundedP001 ||
                 (iter001 <= upperBound001)); 
            iter000 = iter000 + 1,
            iter001 = iter001 + 1) {
        i1 = iter000;
        i2 = iter001;
        a1 = (arguments1->theArray)[i1];
        a2 = (arguments2->theArray)[i2];
        if ((i1 == end1) &&
            ((i2 == end2) &&
             (functionOutputSkolemP(a1) &&
              (functionOutputSkolemP(a2) &&
               ((((Skolem*)(a1))->definingProposition == p1) &&
                ((((Skolem*)(a2))->definingProposition == p2) &&
                 (eqlP(valueOf(a1), a1) &&
                  eqlP(valueOf(a2), a2)))))))) {
          return (false);
        }
        if (logicFormLessP(a1, a2)) {
          return (true);
        }
        else {
          if (logicFormLessP(a2, a1)) {
            return (false);
          }
        }
      }
    }
    return (end1 < end2);
  }
}

const char* propositionHeadSortString(Proposition* p) {
  if (p->kind == KWD_PROPOSITIONS_IMPLIES) {
    if (isaP((p->arguments->theArray)[0], SGT_PROPOSITIONS_LOGIC_DESCRIPTION) &&
        isaP((p->arguments->theArray)[1], SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) {
      return ("FORALL");
    }
    else {
      return ("SUBSET-OF");
    }
  }
  else {
    return (p->operatoR->symbolName);
  }
}

const char* objectSortString(Object* o) {
  if (!((boolean)(o))) {
    return ("NULL");
  }
  { Surrogate* testValue000 = safePrimaryType(o);

    if (subtypeOfIntegerP(testValue000)) {
      { Object* o000 = o;
        IntegerWrapper* o = ((IntegerWrapper*)(o000));

        return (stringify(o));
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* o001 = o;
        FloatWrapper* o = ((FloatWrapper*)(o001));

        return (stringify(o));
      }
    }
    else if (subtypeOfBooleanP(testValue000)) {
      { Object* o002 = o;
        BooleanWrapper* o = ((BooleanWrapper*)(o002));

        if (o == FALSE_WRAPPER) {
          return ("FALSE");
        }
        else if (o == TRUE_WRAPPER) {
          return ("TRUE");
        }
        else {
          return ("UNKNOWN");
        }
      }
    }
    else if (subtypeOfStringP(testValue000)) {
      { Object* o003 = o;
        StringWrapper* o = ((StringWrapper*)(o003));

        return (o->wrapperValue);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_MUTABLE_STRING_WRAPPER)) {
      { Object* o004 = o;
        MutableStringWrapper* o = ((MutableStringWrapper*)(o004));

        return ((o->wrapperValue));
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_GENERALIZED_SYMBOL)) {
      { Object* o005 = o;
        GeneralizedSymbol* o = ((GeneralizedSymbol*)(o005));

        return (o->symbolName);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
      { Object* o006 = o;
        Skolem* o = ((Skolem*)(o006));

        { Object* val = ((Object*)(accessInContext(o->variableValue, o->homeContext, false)));

          if ((!((boolean)(val))) ||
              (val == o)) {
            return (stringify(o));
          }
          else {
            return (objectSortString(((Object*)(accessInContext(o->variableValue, o->homeContext, false)))));
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT)) {
      { Object* o007 = o;
        LogicObject* o = ((LogicObject*)(o007));

        return (objectStringName(o));
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_STELLA_CONTEXT)) {
      { Object* o008 = o;
        Context* o = ((Context*)(o008));

        return (o->contextName());
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_COMPUTED_PROCEDURE)) {
      { Object* o009 = o;
        ComputedProcedure* o = ((ComputedProcedure*)(o009));

        return (o->surrogateValueInverse->symbolName);
      }
    }
    else {
      if (o->primaryType()->homeModule() == oLOGIC_MODULEo) {
        *(STANDARD_WARNING->nativeStream) << "Warning: " << "OBJECT-SORT-STRING: Doesn't specifically handle object " << "`" << o << "'" << " yet!" << std::endl;
      }
      return (stringify(o));
    }
  }
}

boolean logicFormLessP(Object* o1, Object* o2) {
  // A sorting predicate for objects `o1' and `o2' that can appear in logical
  // forms.  Performs a combined numeric and lexocographic sort that accounts
  // for lists, collections and propositions.  Numbers precede all other values,
  // `null' follows all other values.
  if (o1 == o2) {
    return (false);
  }
  if (isaP(o1, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
    { Object* value = ((Object*)(accessInContext(((Skolem*)(o1))->variableValue, ((Skolem*)(o1))->homeContext, false)));

      if (((boolean)(value))) {
        o1 = value;
      }
      else if (functionOutputSkolemP(o1)) {
        o1 = ((Skolem*)(o1))->definingProposition;
      }
      else {
        o1 = ((Skolem*)(o1))->skolemName;
      }
    }
  }
  if (isaP(o2, SGT_PROPOSITIONS_LOGIC_SKOLEM)) {
    { Object* value = ((Object*)(accessInContext(((Skolem*)(o2))->variableValue, ((Skolem*)(o2))->homeContext, false)));

      if (((boolean)(value))) {
        o2 = value;
      }
      else if (functionOutputSkolemP(o2)) {
        o2 = ((Skolem*)(o2))->definingProposition;
      }
      else {
        o2 = ((Skolem*)(o2))->skolemName;
      }
    }
  }
  if (!((boolean)(o1))) {
    return (false);
  }
  if (!((boolean)(o2))) {
    return (true);
  }
  { Surrogate* testValue000 = safePrimaryType(o1);

    if (subtypeOfIntegerP(testValue000)) {
      { Object* o1000 = o1;
        IntegerWrapper* o1 = ((IntegerWrapper*)(o1000));

        { Surrogate* testValue001 = safePrimaryType(o2);

          if (subtypeOfIntegerP(testValue001)) {
            { Object* o2000 = o2;
              IntegerWrapper* o2 = ((IntegerWrapper*)(o2000));

              return (o1->wrapperValue < o2->wrapperValue);
            }
          }
          else if (subtypeOfFloatP(testValue001)) {
            { Object* o2001 = o2;
              FloatWrapper* o2 = ((FloatWrapper*)(o2001));

              return (o1->wrapperValue < o2->wrapperValue);
            }
          }
          else if (subtypeOfP(testValue001, SGT_PROPOSITIONS_LOGIC_QUANTITY_LOGIC_WRAPPER)) {
            { Object* o2002 = o2;
              QuantityLogicWrapper* o2 = ((QuantityLogicWrapper*)(o2002));

              return (!safeQuantityGreaterEqualP(o2->wrapperValue, o1));
            }
          }
          else {
            return (true);
          }
        }
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* o1001 = o1;
        FloatWrapper* o1 = ((FloatWrapper*)(o1001));

        { Surrogate* testValue002 = safePrimaryType(o2);

          if (subtypeOfIntegerP(testValue002)) {
            { Object* o2003 = o2;
              IntegerWrapper* o2 = ((IntegerWrapper*)(o2003));

              return (o1->wrapperValue < o2->wrapperValue);
            }
          }
          else if (subtypeOfFloatP(testValue002)) {
            { Object* o2004 = o2;
              FloatWrapper* o2 = ((FloatWrapper*)(o2004));

              return (o1->wrapperValue < o2->wrapperValue);
            }
          }
          else if (subtypeOfP(testValue002, SGT_PROPOSITIONS_LOGIC_QUANTITY_LOGIC_WRAPPER)) {
            { Object* o2005 = o2;
              QuantityLogicWrapper* o2 = ((QuantityLogicWrapper*)(o2005));

              return (!safeQuantityGreaterEqualP(o2->wrapperValue, o1));
            }
          }
          else {
            return (true);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_QUANTITY_LOGIC_WRAPPER)) {
      { Object* o1002 = o1;
        QuantityLogicWrapper* o1 = ((QuantityLogicWrapper*)(o1002));

        { Surrogate* testValue003 = safePrimaryType(o2);

          if (subtypeOfP(testValue003, SGT_PROPOSITIONS_LOGIC_QUANTITY_LOGIC_WRAPPER)) {
            { Object* o2006 = o2;
              QuantityLogicWrapper* o2 = ((QuantityLogicWrapper*)(o2006));

              return (safeQuantityLessP(o1->wrapperValue, o2->wrapperValue));
            }
          }
          else if (subtypeOfP(testValue003, SGT_PROPOSITIONS_STELLA_NUMBER_WRAPPER)) {
            { Object* o2007 = o2;
              NumberWrapper* o2 = ((NumberWrapper*)(o2007));

              return (safeQuantityLessP(o1->wrapperValue, o2));
            }
          }
          else {
            return (true);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
      { Object* o1003 = o1;
        Proposition* o1 = ((Proposition*)(o1003));

        { Surrogate* testValue004 = safePrimaryType(o2);

          if (subtypeOfP(testValue004, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
            { Object* o2008 = o2;
              Proposition* o2 = ((Proposition*)(o2008));

              return (propositionLessThanP(o1, o2));
            }
          }
          else if (subtypeOfP(testValue004, SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
            { Object* o2009 = o2;
              NamedDescription* o2 = ((NamedDescription*)(o2009));

              return (stringTermLessP(propositionHeadSortString(o1), objectSortString(o2)));
            }
          }
          else if (subtypeOfP(testValue004, SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) {
            { Object* o2010 = o2;
              Description* o2 = ((Description*)(o2010));

              return (propositionLessThanP(o1, o2->proposition));
            }
          }
          else {
            return (stringTermLessP(propositionHeadSortString(o1), objectSortString(o2)));
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
      { Object* o1004 = o1;
        NamedDescription* o1 = ((NamedDescription*)(o1004));

        { Surrogate* testValue005 = safePrimaryType(o2);

          if (subtypeOfP(testValue005, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
            { Object* o2011 = o2;
              Proposition* o2 = ((Proposition*)(o2011));

              return (stringTermLessP(objectSortString(o1), propositionHeadSortString(o2)));
            }
          }
          else if (subtypeOfP(testValue005, SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
            { Object* o2012 = o2;
              NamedDescription* o2 = ((NamedDescription*)(o2012));

              return (stringTermLessP(objectSortString(o1), objectSortString(o2)));
            }
          }
          else if (subtypeOfP(testValue005, SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) {
            { Object* o2013 = o2;
              Description* o2 = ((Description*)(o2013));

              return (stringTermLessP(objectSortString(o1), propositionHeadSortString(o2->proposition)));
            }
          }
          else {
            return (stringTermLessP(objectSortString(o1), objectSortString(o2)));
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) {
      { Object* o1005 = o1;
        Description* o1 = ((Description*)(o1005));

        return (logicFormLessP(o1->proposition, o2));
      }
    }
    else {
      { Surrogate* testValue006 = safePrimaryType(o2);

        if (subtypeOfP(testValue006, SGT_PROPOSITIONS_LOGIC_PROPOSITION)) {
          { Object* o2014 = o2;
            Proposition* o2 = ((Proposition*)(o2014));

            return (stringTermLessP(objectSortString(o1), propositionHeadSortString(o2)));
          }
        }
        else if (subtypeOfP(testValue006, SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION)) {
          { Object* o2015 = o2;
            NamedDescription* o2 = ((NamedDescription*)(o2015));

            return (stringTermLessP(objectSortString(o1), objectSortString(o2)));
          }
        }
        else if (subtypeOfP(testValue006, SGT_PROPOSITIONS_LOGIC_DESCRIPTION)) {
          { Object* o2016 = o2;
            Description* o2 = ((Description*)(o2016));

            return (stringTermLessP(objectSortString(o1), propositionHeadSortString(o2->proposition)));
          }
        }
        else {
          return (stringTermLessP(objectSortString(o1), objectSortString(o2)));
        }
      }
    }
  }
}

void helpStartupPropositions1() {
  {
    SYM_PROPOSITIONS_LOGIC_PROPOSITIONS_INDEX = ((Symbol*)(internRigidSymbolWrtModule("PROPOSITIONS-INDEX", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_INSTANCES_INDEX = ((Symbol*)(internRigidSymbolWrtModule("INSTANCES-INDEX", NULL, 0)));
    SGT_PROPOSITIONS_LOGIC_BACKLINKS_INDEX = ((Surrogate*)(internRigidSymbolWrtModule("BACKLINKS-INDEX", NULL, 1)));
    SYM_PROPOSITIONS_LOGIC_DEPENDENT_PROPOSITIONS_LIST = ((Symbol*)(internRigidSymbolWrtModule("DEPENDENT-PROPOSITIONS-LIST", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_DEPENDENT_ISA_PROPOSITIONS_LIST = ((Symbol*)(internRigidSymbolWrtModule("DEPENDENT-ISA-PROPOSITIONS-LIST", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_PREDICATE_PROPOSITIONS_TABLE = ((Symbol*)(internRigidSymbolWrtModule("PREDICATE-PROPOSITIONS-TABLE", NULL, 0)));
    SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
    SYM_PROPOSITIONS_STELLA_BADp = ((Symbol*)(internRigidSymbolWrtModule("BAD?", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_LOGIC_VARIABLE_VALUE_INVERSE = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-VALUE-INVERSE", NULL, 0)));
    SYM_PROPOSITIONS_STELLA_SURROGATE_VALUE_INVERSE = ((Symbol*)(internRigidSymbolWrtModule("SURROGATE-VALUE-INVERSE", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_LOGIC_OBJECT_STRINGIFIED_SOURCE = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-STRINGIFIED-SOURCE", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_OBJECT_ORIGINATED_PROPOSITIONS = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-ORIGINATED-PROPOSITIONS", NULL, 0)));
    SGT_PROPOSITIONS_STELLA_CS_VALUE = ((Surrogate*)(internRigidSymbolWrtModule("CS-VALUE", getStellaModule("/STELLA", true), 1)));
    SYM_PROPOSITIONS_STELLA_DELETED_OBJECTp = ((Symbol*)(internRigidSymbolWrtModule("DELETED-OBJECT?", getStellaModule("/STELLA", true), 0)));
    SGT_PROPOSITIONS_LOGIC_LOGIC_THING = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-THING", NULL, 1)));
    SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", NULL, 1)));
    SGT_PROPOSITIONS_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", NULL, 1)));
    SYM_PROPOSITIONS_LOGIC_SKOLEM_TYPE = ((Symbol*)(internRigidSymbolWrtModule("SKOLEM-TYPE", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_SKOLEM_NAME = ((Symbol*)(internRigidSymbolWrtModule("SKOLEM-NAME", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_VARIABLE_VALUE = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-VALUE", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_DEFINING_PROPOSITION = ((Symbol*)(internRigidSymbolWrtModule("DEFINING-PROPOSITION", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_BOUND_TO_OFFSET = ((Symbol*)(internRigidSymbolWrtModule("BOUND-TO-OFFSET", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_OBJECT_VECTOR = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-VECTOR", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_ARGUMENTS_VECTOR = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENTS-VECTOR", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_VARIABLES_VECTOR = ((Symbol*)(internRigidSymbolWrtModule("VARIABLES-VECTOR", NULL, 0)));
    SGT_PROPOSITIONS_LOGIC_FORWARD_CHAINING_INDEX = ((Surrogate*)(internRigidSymbolWrtModule("FORWARD-CHAINING-INDEX", NULL, 1)));
    SYM_PROPOSITIONS_LOGIC_FORWARD_GOAL = ((Symbol*)(internRigidSymbolWrtModule("FORWARD-GOAL", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_MASTER_RULE = ((Symbol*)(internRigidSymbolWrtModule("MASTER-RULE", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_IO_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("IO-VARIABLES", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_QUERY_BODY = ((Symbol*)(internRigidSymbolWrtModule("QUERY-BODY", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_INPUT_BINDINGS = ((Symbol*)(internRigidSymbolWrtModule("INPUT-BINDINGS", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_CACHE_ID = ((Symbol*)(internRigidSymbolWrtModule("CACHE-ID", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_CONSEQUENT = ((Symbol*)(internRigidSymbolWrtModule("CONSEQUENT", NULL, 0)));
    SGT_PROPOSITIONS_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
    SYM_PROPOSITIONS_LOGIC_NATIVE_RELATION = ((Symbol*)(internRigidSymbolWrtModule("NATIVE-RELATION", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_FORWARD_CHAINING_INDICES = ((Symbol*)(internRigidSymbolWrtModule("FORWARD-CHAINING-INDICES", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_DEFERRED_CONTRAPOSITIVESp = ((Symbol*)(internRigidSymbolWrtModule("DEFERRED-CONTRAPOSITIVES?", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_PROPOSITION = ((Symbol*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_INTERNAL_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("INTERNAL-VARIABLES", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_QUERY_PATTERNS = ((Symbol*)(internRigidSymbolWrtModule("QUERY-PATTERNS", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_RELATIVE_COMPLEMENT = ((Symbol*)(internRigidSymbolWrtModule("RELATIVE-COMPLEMENT", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_COMPLEMENT_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("COMPLEMENT-DESCRIPTION", NULL, 0)));
    SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
    SYM_PROPOSITIONS_LOGIC_NATIVE_RELATION_BACK_POINTER = ((Symbol*)(internRigidSymbolWrtModule("NATIVE-RELATION-BACK-POINTER", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_NATIVE_RELATION_SETTER = ((Symbol*)(internRigidSymbolWrtModule("NATIVE-RELATION-SETTER", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_IO_VARIABLE_NAMES = ((Symbol*)(internRigidSymbolWrtModule("IO-VARIABLE-NAMES", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_IO_VARIABLE_TYPES = ((Symbol*)(internRigidSymbolWrtModule("IO-VARIABLE-TYPES", NULL, 0)));
    SYM_PROPOSITIONS_STELLA_EXTENSION = ((Symbol*)(internRigidSymbolWrtModule("EXTENSION", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_LOGIC_PARTIAL_MATCH_SCORE = ((Symbol*)(internRigidSymbolWrtModule("PARTIAL-MATCH-SCORE", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_SET_OF_SUPPORT = ((Symbol*)(internRigidSymbolWrtModule("SET-OF-SUPPORT", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_TIMESTAMP = ((Symbol*)(internRigidSymbolWrtModule("TIMESTAMP", NULL, 0)));
    KWD_PROPOSITIONS_UNKNOWN = ((Keyword*)(internRigidSymbolWrtModule("UNKNOWN", NULL, 2)));
    SGT_PROPOSITIONS_LOGIC_TRUTH_VALUE = ((Surrogate*)(internRigidSymbolWrtModule("TRUTH-VALUE", NULL, 1)));
    SYM_PROPOSITIONS_LOGIC_POLARITY = ((Symbol*)(internRigidSymbolWrtModule("POLARITY", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_STRENGTH = ((Symbol*)(internRigidSymbolWrtModule("STRENGTH", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_MATCH_SCORE = ((Symbol*)(internRigidSymbolWrtModule("MATCH-SCORE", NULL, 0)));
    SGT_PROPOSITIONS_LOGIC_PARTIAL_SUPPORT = ((Surrogate*)(internRigidSymbolWrtModule("PARTIAL-SUPPORT", NULL, 1)));
    SYM_PROPOSITIONS_LOGIC_FACT = ((Symbol*)(internRigidSymbolWrtModule("FACT", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_AXIOM = ((Symbol*)(internRigidSymbolWrtModule("AXIOM", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_SCORE = ((Symbol*)(internRigidSymbolWrtModule("SCORE", NULL, 0)));
  }
}

void helpStartupPropositions2() {
  {
    SYM_PROPOSITIONS_LOGIC_ID = ((Symbol*)(internRigidSymbolWrtModule("ID", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_ARGUMENT_SCORES = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENT-SCORES", NULL, 0)));
    SGT_PROPOSITIONS_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    SYM_PROPOSITIONS_LOGIC_VARIABLE_TYPEp = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-TYPE?", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_SATELLITE_PROPOSITIONS = ((Symbol*)(internRigidSymbolWrtModule("SATELLITE-PROPOSITIONS", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_UNFASTENEDp = ((Symbol*)(internRigidSymbolWrtModule("UNFASTENED?", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_WEIGHT_DELTA = ((Symbol*)(internRigidSymbolWrtModule("WEIGHT-DELTA", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_SUPPORT = ((Symbol*)(internRigidSymbolWrtModule("SUPPORT", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_KIND = ((Symbol*)(internRigidSymbolWrtModule("KIND", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_TRUTH_VALUE = ((Symbol*)(internRigidSymbolWrtModule("TRUTH-VALUE", NULL, 0)));
    SYM_PROPOSITIONS_STELLA_ARGUMENTS = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENTS", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_STELLA_OPERATOR = ((Symbol*)(internRigidSymbolWrtModule("OPERATOR", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_LOGIC_RELATIONREF = ((Symbol*)(internRigidSymbolWrtModule("RELATIONREF", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_DEPENDENT_PROPOSITIONS = ((Symbol*)(internRigidSymbolWrtModule("DEPENDENT-PROPOSITIONS", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_PROPOSITION_ORIGINATED_PROPOSITIONS = ((Symbol*)(internRigidSymbolWrtModule("PROPOSITION-ORIGINATED-PROPOSITIONS", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_PROPOSITION_STRINGIFIED_SOURCE = ((Symbol*)(internRigidSymbolWrtModule("PROPOSITION-STRINGIFIED-SOURCE", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_PROPOSITION_NEURAL_NETWORK = ((Symbol*)(internRigidSymbolWrtModule("PROPOSITION-NEURAL-NETWORK", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_NEURAL_NETWORK = ((Symbol*)(internRigidSymbolWrtModule("NEURAL-NETWORK", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_NEURAL_NET = ((Symbol*)(internRigidSymbolWrtModule("NEURAL-NET", NULL, 0)));
    SGT_PROPOSITIONS_LOGIC_QUANTITY_LOGIC_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("QUANTITY-LOGIC-WRAPPER", NULL, 1)));
    SYM_PROPOSITIONS_STELLA_WRAPPER_VALUE = ((Symbol*)(internRigidSymbolWrtModule("WRAPPER-VALUE", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_LOGIC_FUNCTION_TERM = ((Symbol*)(internRigidSymbolWrtModule("FUNCTION-TERM", NULL, 0)));
    SGT_PROPOSITIONS_LOGIC_INTEGER_LOGIC_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-LOGIC-WRAPPER", NULL, 1)));
    SGT_PROPOSITIONS_LOGIC_FLOAT_LOGIC_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT-LOGIC-WRAPPER", NULL, 1)));
    SGT_PROPOSITIONS_LOGIC_STRING_LOGIC_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("STRING-LOGIC-WRAPPER", NULL, 1)));
    SYM_PROPOSITIONS_LOGIC_ENTITY_MAPPING = ((Symbol*)(internRigidSymbolWrtModule("ENTITY-MAPPING", NULL, 0)));
    KWD_PROPOSITIONS_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_AND = ((Surrogate*)(internRigidSymbolWrtModule("AND", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_PROPOSITIONS_OR = ((Keyword*)(internRigidSymbolWrtModule("OR", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_OR = ((Surrogate*)(internRigidSymbolWrtModule("OR", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_PROPOSITIONS_NOT = ((Keyword*)(internRigidSymbolWrtModule("NOT", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_NOT = ((Surrogate*)(internRigidSymbolWrtModule("NOT", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_PROPOSITIONS_FORALL = ((Keyword*)(internRigidSymbolWrtModule("FORALL", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_FORALL = ((Surrogate*)(internRigidSymbolWrtModule("FORALL", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_PROPOSITIONS_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("EXISTS", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_EXISTS = ((Surrogate*)(internRigidSymbolWrtModule("EXISTS", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_PROPOSITIONS_EQUIVALENT = ((Keyword*)(internRigidSymbolWrtModule("EQUIVALENT", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_EQUIVALENT = ((Surrogate*)(internRigidSymbolWrtModule("EQUIVALENT", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_PROPOSITIONS_FAIL = ((Keyword*)(internRigidSymbolWrtModule("FAIL", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_FAIL = ((Surrogate*)(internRigidSymbolWrtModule("FAIL", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_PROPOSITIONS_COLLECT_INTO = ((Keyword*)(internRigidSymbolWrtModule("COLLECT-INTO", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_COLLECT_INTO = ((Surrogate*)(internRigidSymbolWrtModule("COLLECT-INTO", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_PROPOSITIONS_IMPLIES = ((Keyword*)(internRigidSymbolWrtModule("IMPLIES", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_SUBSET_OF = ((Surrogate*)(internRigidSymbolWrtModule("SUBSET-OF", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_PROPOSITIONS_STELLA_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("FUNCTION", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_STELLA_PREDICATE = ((Symbol*)(internRigidSymbolWrtModule("PREDICATE", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_STELLA_ISA = ((Symbol*)(internRigidSymbolWrtModule("ISA", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_LOGIC_DESCRIPTIVEp = ((Symbol*)(internRigidSymbolWrtModule("DESCRIPTIVE?", NULL, 0)));
    SYM_PROPOSITIONS_STELLA_CODE_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("CODE-ONLY?", getStellaModule("/STELLA", true), 0)));
    KWD_PROPOSITIONS_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    SGT_PROPOSITIONS_LOGIC_EXCEPTION_RECORD = ((Surrogate*)(internRigidSymbolWrtModule("EXCEPTION-RECORD", NULL, 1)));
    SYM_PROPOSITIONS_STELLA_CONTEXT = ((Symbol*)(internRigidSymbolWrtModule("CONTEXT", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_STELLA_MODULE = ((Symbol*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_LOGIC_LOCALLY_CONCEIVED_PROPOSITIONS_INTERNAL = ((Symbol*)(internRigidSymbolWrtModule("LOCALLY-CONCEIVED-PROPOSITIONS-INTERNAL", NULL, 0)));
    KWD_PROPOSITIONS_PAGING = ((Keyword*)(internRigidSymbolWrtModule("PAGING", NULL, 2)));
    KWD_PROPOSITIONS_CONTEXT_PROPOSITIONS = ((Keyword*)(internRigidSymbolWrtModule("CONTEXT-PROPOSITIONS", NULL, 2)));
    SYM_PROPOSITIONS_LOGIC_LOCALLY_CONCEIVED_INSTANCES_INTERNAL = ((Symbol*)(internRigidSymbolWrtModule("LOCALLY-CONCEIVED-INSTANCES-INTERNAL", NULL, 0)));
    KWD_PROPOSITIONS_CONTEXT_INSTANCES = ((Keyword*)(internRigidSymbolWrtModule("CONTEXT-INSTANCES", NULL, 2)));
    KWD_PROPOSITIONS_UPDATE_PROPOSITION = ((Keyword*)(internRigidSymbolWrtModule("UPDATE-PROPOSITION", NULL, 2)));
    KWD_PROPOSITIONS_EXECUTE_QUERY = ((Keyword*)(internRigidSymbolWrtModule("EXECUTE-QUERY", NULL, 2)));
  }
}

void helpStartupPropositions3() {
  {
    SYM_PROPOSITIONS_LOGIC_BOTTOM = ((Symbol*)(internRigidSymbolWrtModule("BOTTOM", NULL, 0)));
    SGT_PROPOSITIONS_STELLA_LITERAL = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_LOGIC_F_LOGICAL_SUBTYPE_OF_LITERALp_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-LOGICAL-SUBTYPE-OF-LITERAL?-MEMO-TABLE-000", NULL, 1)));
    SGT_PROPOSITIONS_STELLA_CLASS = ((Surrogate*)(internRigidSymbolWrtModule("CLASS", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_STELLA_LITERAL_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_STELLA_BOOLEAN = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_STELLA_BOOLEAN_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("BOOLEAN-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_VARIABLE_ARITY = ((Surrogate*)(internRigidSymbolWrtModule("VARIABLE-ARITY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_PROPOSITIONS_STELLA_COLLECTION = ((Surrogate*)(internRigidSymbolWrtModule("COLLECTION", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_RELATION_COMPUTATION = ((Surrogate*)(internRigidSymbolWrtModule("RELATION-COMPUTATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_PROPOSITIONS_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
    KWD_PROPOSITIONS_EXTENSIONAL_ASSERTION = ((Keyword*)(internRigidSymbolWrtModule("EXTENSIONAL-ASSERTION", NULL, 2)));
    KWD_PROPOSITIONS_DESCRIPTION = ((Keyword*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 2)));
    KWD_PROPOSITIONS_DEVELOPMENT = ((Keyword*)(internRigidSymbolWrtModule("DEVELOPMENT", NULL, 2)));
    KWD_PROPOSITIONS_WARNING = ((Keyword*)(internRigidSymbolWrtModule("WARNING", NULL, 2)));
    KWD_PROPOSITIONS_RETRACT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("RETRACT-TRUE", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_UPDATE_PROPOSITION_DEMON = ((Surrogate*)(internRigidSymbolWrtModule("UPDATE-PROPOSITION-DEMON", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_PROPOSITIONS_LOGIC_OBJECT_STORE = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-STORE", NULL, 0)));
    KWD_PROPOSITIONS_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    KWD_PROPOSITIONS_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_TRUE_DEMON = ((Surrogate*)(internRigidSymbolWrtModule("GOES-TRUE-DEMON", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_PROPOSITIONS_PREDICATE = ((Keyword*)(internRigidSymbolWrtModule("PREDICATE", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_FALSE_DEMON = ((Surrogate*)(internRigidSymbolWrtModule("GOES-FALSE-DEMON", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_UNKNOWN_DEMON = ((Surrogate*)(internRigidSymbolWrtModule("GOES-UNKNOWN-DEMON", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_PROPOSITIONS_LOGIC_MASTER_PROPOSITION = ((Symbol*)(internRigidSymbolWrtModule("MASTER-PROPOSITION", NULL, 0)));
    KWD_PROPOSITIONS_ASSERT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("ASSERT-TRUE", NULL, 2)));
    KWD_PROPOSITIONS_PRESUME_TRUE = ((Keyword*)(internRigidSymbolWrtModule("PRESUME-TRUE", NULL, 2)));
    KWD_PROPOSITIONS_ASSERT_FALSE = ((Keyword*)(internRigidSymbolWrtModule("ASSERT-FALSE", NULL, 2)));
    KWD_PROPOSITIONS_PRESUME_FALSE = ((Keyword*)(internRigidSymbolWrtModule("PRESUME-FALSE", NULL, 2)));
    KWD_PROPOSITIONS_RETRACT_FALSE = ((Keyword*)(internRigidSymbolWrtModule("RETRACT-FALSE", NULL, 2)));
    KWD_PROPOSITIONS_ASSERT = ((Keyword*)(internRigidSymbolWrtModule("ASSERT", NULL, 2)));
    KWD_PROPOSITIONS_RETRACT_INCONSISTENT = ((Keyword*)(internRigidSymbolWrtModule("RETRACT-INCONSISTENT", NULL, 2)));
    KWD_PROPOSITIONS_RETRACT = ((Keyword*)(internRigidSymbolWrtModule("RETRACT", NULL, 2)));
    KWD_PROPOSITIONS_CONCEIVE = ((Keyword*)(internRigidSymbolWrtModule("CONCEIVE", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_HIDDEN_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("HIDDEN-RELATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_PROPOSITIONS_LOGIC_HIDDEN_INSTANCE = ((Surrogate*)(internRigidSymbolWrtModule("HIDDEN-INSTANCE", NULL, 1)));
    KWD_PROPOSITIONS_MODULE = ((Keyword*)(internRigidSymbolWrtModule("MODULE", NULL, 2)));
    SGT_PROPOSITIONS_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 1)));
    KWD_PROPOSITIONS_LOCALp = ((Keyword*)(internRigidSymbolWrtModule("LOCAL?", NULL, 2)));
    KWD_PROPOSITIONS_KB_UPDATE = ((Keyword*)(internRigidSymbolWrtModule("KB-UPDATE", NULL, 2)));
    KWD_PROPOSITIONS_META_KB_UPDATE = ((Keyword*)(internRigidSymbolWrtModule("META-KB-UPDATE", NULL, 2)));
    SGT_PROPOSITIONS_STELLA_STORAGE_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("STORAGE-SLOT", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_STELLA_SURROGATE = ((Surrogate*)(internRigidSymbolWrtModule("SURROGATE", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_STELLA_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("RELATION", getStellaModule("/STELLA", true), 1)));
    SYM_PROPOSITIONS_LOGIC_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_EQUIVALENT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("EQUIVALENT-VALUE", NULL, 0)));
    KWD_PROPOSITIONS_TRUE = ((Keyword*)(internRigidSymbolWrtModule("TRUE", NULL, 2)));
    KWD_PROPOSITIONS_STRICT = ((Keyword*)(internRigidSymbolWrtModule("STRICT", NULL, 2)));
    KWD_PROPOSITIONS_FALSE = ((Keyword*)(internRigidSymbolWrtModule("FALSE", NULL, 2)));
    KWD_PROPOSITIONS_DEFAULT = ((Keyword*)(internRigidSymbolWrtModule("DEFAULT", NULL, 2)));
    KWD_PROPOSITIONS_INCONSISTENT = ((Keyword*)(internRigidSymbolWrtModule("INCONSISTENT", NULL, 2)));
    KWD_PROPOSITIONS_LOOKUP_ASSERTIONS = ((Keyword*)(internRigidSymbolWrtModule("LOOKUP-ASSERTIONS", NULL, 2)));
    KWD_PROPOSITIONS_FORWARD = ((Keyword*)(internRigidSymbolWrtModule("FORWARD", NULL, 2)));
    SYM_PROPOSITIONS_LOGIC_META_INFERENCE_CACHE = ((Symbol*)(internRigidSymbolWrtModule("META-INFERENCE-CACHE", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_TRUTH_MAINTAINED_INFERENCE_CACHE = ((Symbol*)(internRigidSymbolWrtModule("TRUTH-MAINTAINED-INFERENCE-CACHE", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_CLASH_EXCEPTIONS = ((Symbol*)(internRigidSymbolWrtModule("CLASH-EXCEPTIONS", NULL, 0)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_INCOHERENT = ((Surrogate*)(internRigidSymbolWrtModule("INCOHERENT", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_PROPOSITIONS_LOGIC_IOTAp = ((Symbol*)(internRigidSymbolWrtModule("IOTA?", NULL, 0)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_CONCEPT = ((Surrogate*)(internRigidSymbolWrtModule("CONCEPT", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("RELATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
  }
}

void helpStartupPropositions4() {
  {
    SGT_PROPOSITIONS_STELLA_SET = ((Surrogate*)(internRigidSymbolWrtModule("SET", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_SET = ((Surrogate*)(internRigidSymbolWrtModule("SET", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_PROPOSITIONS_STELLA_SLOT = ((Surrogate*)(internRigidSymbolWrtModule("SLOT", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_FUNCTION = ((Surrogate*)(internRigidSymbolWrtModule("FUNCTION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_PROPOSITIONS_META = ((Keyword*)(internRigidSymbolWrtModule("META", NULL, 2)));
    KWD_PROPOSITIONS_JUST_IN_TIME = ((Keyword*)(internRigidSymbolWrtModule("JUST-IN-TIME", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_INTERVAL_CACHE = ((Surrogate*)(internRigidSymbolWrtModule("INTERVAL-CACHE", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_ge = ((Surrogate*)(internRigidSymbolWrtModule(">=", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_PROPOSITIONS_LOGIC_CONFLICTING_DEFAULT_VALUES = ((Symbol*)(internRigidSymbolWrtModule("CONFLICTING-DEFAULT-VALUES", NULL, 0)));
    KWD_PROPOSITIONS_CONSTANT = ((Keyword*)(internRigidSymbolWrtModule("CONSTANT", NULL, 2)));
    SGT_PROPOSITIONS_STELLA_TRUE = ((Surrogate*)(internRigidSymbolWrtModule("TRUE", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_STELLA_FALSE = ((Surrogate*)(internRigidSymbolWrtModule("FALSE", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    SYM_PROPOSITIONS_LOGIC_SETOFALL = ((Symbol*)(internRigidSymbolWrtModule("SETOFALL", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_THE_ONLY = ((Symbol*)(internRigidSymbolWrtModule("THE-ONLY", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_KAPPA = ((Symbol*)(internRigidSymbolWrtModule("KAPPA", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_CREATE = ((Symbol*)(internRigidSymbolWrtModule("CREATE", NULL, 0)));
    KWD_PROPOSITIONS_INTENSIONAL_ASSERTION = ((Keyword*)(internRigidSymbolWrtModule("INTENSIONAL-ASSERTION", NULL, 2)));
    SYM_PROPOSITIONS_STELLA_p = ((Symbol*)(internRigidSymbolWrtModule("?", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_STELLA_CLASS_EXTENSION = ((Symbol*)(internRigidSymbolWrtModule("CLASS-EXTENSION", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_LOGIC_TRANSFER_LOGIC_INFORMATION_FROM_RELATION_HOOK = ((Symbol*)(internRigidSymbolWrtModule("TRANSFER-LOGIC-INFORMATION-FROM-RELATION-HOOK", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_SUBRELATION_LINKp = ((Symbol*)(internRigidSymbolWrtModule("SUBRELATION-LINK?", NULL, 0)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_HOLDS = ((Surrogate*)(internRigidSymbolWrtModule("HOLDS", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_MEMBER_OF = ((Surrogate*)(internRigidSymbolWrtModule("MEMBER-OF", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_PROPOSITIONS_DISABLED = ((Keyword*)(internRigidSymbolWrtModule("DISABLED", NULL, 2)));
    SYM_PROPOSITIONS_LOGIC_ANNOTATIONS = ((Symbol*)(internRigidSymbolWrtModule("ANNOTATIONS", NULL, 0)));
    SGT_PROPOSITIONS_STELLA_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("STRING-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SYM_PROPOSITIONS_LOGIC_CONSTANT = ((Symbol*)(internRigidSymbolWrtModule("CONSTANT", NULL, 0)));
    SYM_PROPOSITIONS_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", getStellaModule("/STELLA", true), 0)));
    SGT_PROPOSITIONS_STELLA_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("SYMBOL", getStellaModule("/STELLA", true), 1)));
    SYM_PROPOSITIONS_STELLA_e = ((Symbol*)(internRigidSymbolWrtModule("=", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_STELLA_OR = ((Symbol*)(internRigidSymbolWrtModule("OR", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_PL_KERNEL_KB_MEMBER_OF = ((Symbol*)(internRigidSymbolWrtModule("MEMBER-OF", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_PROPOSITIONS_LOGIC_IMPLIES = ((Symbol*)(internRigidSymbolWrtModule("IMPLIES", NULL, 0)));
    SYM_PROPOSITIONS_PL_KERNEL_KB_SUBSET_OF = ((Symbol*)(internRigidSymbolWrtModule("SUBSET-OF", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_PROPOSITIONS_STELLA_EXISTS = ((Symbol*)(internRigidSymbolWrtModule("EXISTS", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_STELLA_FORALL = ((Symbol*)(internRigidSymbolWrtModule("FORALL", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_LOGIC_FAIL = ((Symbol*)(internRigidSymbolWrtModule("FAIL", NULL, 0)));
    SYM_PROPOSITIONS_STELLA_COLLECT_INTO = ((Symbol*)(internRigidSymbolWrtModule("COLLECT-INTO", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_LOGIC_ABOUT = ((Symbol*)(internRigidSymbolWrtModule("ABOUT", NULL, 0)));
    SGT_PROPOSITIONS_STELLA_GENERALIZED_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("GENERALIZED-SYMBOL", getStellaModule("/STELLA", true), 1)));
    KWD_PROPOSITIONS_DIRECTION = ((Keyword*)(internRigidSymbolWrtModule("DIRECTION", NULL, 2)));
    SYM_PROPOSITIONS_LOGIC_FORWARD_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("FORWARD-ONLY?", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_BACKWARD_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("BACKWARD-ONLY?", NULL, 0)));
    KWD_PROPOSITIONS_WEIGHT = ((Keyword*)(internRigidSymbolWrtModule("WEIGHT", NULL, 2)));
    SYM_PROPOSITIONS_LOGIC_WEIGHT = ((Symbol*)(internRigidSymbolWrtModule("WEIGHT", NULL, 0)));
    KWD_PROPOSITIONS_SCORE = ((Keyword*)(internRigidSymbolWrtModule("SCORE", NULL, 2)));
    KWD_PROPOSITIONS_CONFIDENCE_LEVEL = ((Keyword*)(internRigidSymbolWrtModule("CONFIDENCE-LEVEL", NULL, 2)));
    SYM_PROPOSITIONS_PL_KERNEL_KB_SETOF = ((Symbol*)(internRigidSymbolWrtModule("SETOF", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_PROPOSITIONS_PL_KERNEL_KB_LISTOF = ((Symbol*)(internRigidSymbolWrtModule("LISTOF", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_PROPOSITIONS_LOGIC_EQUIVALENT = ((Symbol*)(internRigidSymbolWrtModule("EQUIVALENT", NULL, 0)));
    SYM_PROPOSITIONS_PL_KERNEL_KB_HOLDS = ((Symbol*)(internRigidSymbolWrtModule("HOLDS", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SGT_PROPOSITIONS_STELLA_TABLE = ((Surrogate*)(internRigidSymbolWrtModule("TABLE", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_POLYMORPHIC = ((Surrogate*)(internRigidSymbolWrtModule("POLYMORPHIC", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_PROPOSITIONS_PL_KERNEL_KB_VALUE = ((Symbol*)(internRigidSymbolWrtModule("VALUE", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_VALUE = ((Surrogate*)(internRigidSymbolWrtModule("VALUE", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_QUANTITY = ((Surrogate*)(internRigidSymbolWrtModule("QUANTITY", getStellaModule("/PL-KERNEL-KB", true), 1)));
  }
}

void helpStartupPropositions5() {
  {
    SGT_PROPOSITIONS_PL_KERNEL_KB_DATE = ((Surrogate*)(internRigidSymbolWrtModule("DATE", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_PROPOSITIONS_STELLA_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_STELLA_INTEGER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER", getStellaModule("/STELLA", true), 1)));
    KWD_PROPOSITIONS_AUTOMATICALLY_FIX_TYPE_VIOLATIONS = ((Keyword*)(internRigidSymbolWrtModule("AUTOMATICALLY-FIX-TYPE-VIOLATIONS", NULL, 2)));
    KWD_PROPOSITIONS_POST_TYPE_VIOLATIONS = ((Keyword*)(internRigidSymbolWrtModule("POST-TYPE-VIOLATIONS", NULL, 2)));
    KWD_PROPOSITIONS_IGNORE_TYPE_VIOLATIONS = ((Keyword*)(internRigidSymbolWrtModule("IGNORE-TYPE-VIOLATIONS", NULL, 2)));
    KWD_PROPOSITIONS_REPORT_TYPE_VIOLATIONS = ((Keyword*)(internRigidSymbolWrtModule("REPORT-TYPE-VIOLATIONS", NULL, 2)));
    KWD_PROPOSITIONS_SIGNAL_TYPE_VIOLATIONS = ((Keyword*)(internRigidSymbolWrtModule("SIGNAL-TYPE-VIOLATIONS", NULL, 2)));
    SYM_PROPOSITIONS_LOGIC_ASSERTED_BY_TYPE_CHECKERp = ((Symbol*)(internRigidSymbolWrtModule("ASSERTED-BY-TYPE-CHECKER?", NULL, 0)));
    SGT_PROPOSITIONS_LOGIC_CHECK_TYPES_RECORD = ((Surrogate*)(internRigidSymbolWrtModule("CHECK-TYPES-RECORD", NULL, 1)));
    SYM_PROPOSITIONS_LOGIC_PARENT_PROPOSITION = ((Symbol*)(internRigidSymbolWrtModule("PARENT-PROPOSITION", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_PARENT_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("PARENT-DESCRIPTION", NULL, 0)));
    KWD_PROPOSITIONS_MEDIUM = ((Keyword*)(internRigidSymbolWrtModule("MEDIUM", NULL, 2)));
    KWD_PROPOSITIONS_REALISTIC = ((Keyword*)(internRigidSymbolWrtModule("REALISTIC", NULL, 2)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_SETOF = ((Surrogate*)(internRigidSymbolWrtModule("SETOF", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_TOTAL = ((Surrogate*)(internRigidSymbolWrtModule("TOTAL", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_LISTOF = ((Surrogate*)(internRigidSymbolWrtModule("LISTOF", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_PROPOSITIONS_PL_KERNEL_KB_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_PROPOSITIONS_LOGIC_LAMBDA = ((Symbol*)(internRigidSymbolWrtModule("LAMBDA", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_BAGOF = ((Symbol*)(internRigidSymbolWrtModule("BAGOF", NULL, 0)));
    SYM_PROPOSITIONS_STELLA_ASSERT = ((Symbol*)(internRigidSymbolWrtModule("ASSERT", getStellaModule("/STELLA", true), 0)));
    KWD_PROPOSITIONS_CPP = ((Keyword*)(internRigidSymbolWrtModule("CPP", NULL, 2)));
    KWD_PROPOSITIONS_DELETED = ((Keyword*)(internRigidSymbolWrtModule("DELETED", NULL, 2)));
    SYM_PROPOSITIONS_LOGIC_INTRODUCE_MODULE = ((Symbol*)(internRigidSymbolWrtModule("INTRODUCE-MODULE", NULL, 0)));
    SGT_PROPOSITIONS_STELLA_KEY_VALUE_LIST = ((Surrogate*)(internRigidSymbolWrtModule("KEY-VALUE-LIST", getStellaModule("/STELLA", true), 1)));
    SYM_PROPOSITIONS_LOGIC_CLEAR_LOGIC_MODULE_HOOK = ((Symbol*)(internRigidSymbolWrtModule("CLEAR-LOGIC-MODULE-HOOK", NULL, 0)));
    SYM_PROPOSITIONS_LOGIC_MONOTONICp = ((Symbol*)(internRigidSymbolWrtModule("MONOTONIC?", NULL, 0)));
    SGT_PROPOSITIONS_STELLA_WORLD = ((Surrogate*)(internRigidSymbolWrtModule("WORLD", getStellaModule("/STELLA", true), 1)));
    SYM_PROPOSITIONS_LOGIC_DESTROY_LOGIC_CONTEXT_HOOK = ((Symbol*)(internRigidSymbolWrtModule("DESTROY-LOGIC-CONTEXT-HOOK", NULL, 0)));
    SYM_PROPOSITIONS_STELLA_CLEARABLEp = ((Symbol*)(internRigidSymbolWrtModule("CLEARABLE?", getStellaModule("/STELLA", true), 0)));
    SYM_PROPOSITIONS_STELLA_PROTECT_SURROGATESp = ((Symbol*)(internRigidSymbolWrtModule("PROTECT-SURROGATES?", getStellaModule("/STELLA", true), 0)));
    KWD_PROPOSITIONS_PREORDER = ((Keyword*)(internRigidSymbolWrtModule("PREORDER", NULL, 2)));
    SGT_PROPOSITIONS_STELLA_MUTABLE_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("MUTABLE-STRING-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_STELLA_CONTEXT = ((Surrogate*)(internRigidSymbolWrtModule("CONTEXT", getStellaModule("/STELLA", true), 1)));
    SGT_PROPOSITIONS_LOGIC_COMPUTED_PROCEDURE = ((Surrogate*)(internRigidSymbolWrtModule("COMPUTED-PROCEDURE", NULL, 1)));
    SGT_PROPOSITIONS_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SYM_PROPOSITIONS_LOGIC_STARTUP_PROPOSITIONS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-PROPOSITIONS", NULL, 0)));
    SYM_PROPOSITIONS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupPropositions6() {
  {
    ZERO_VARIABLES_VECTOR = stella::newVector(0);
    { PropertyList* self004 = newPropertyList();

      self004->thePlist = listO(19, KWD_PROPOSITIONS_AND, SGT_PROPOSITIONS_PL_KERNEL_KB_AND, KWD_PROPOSITIONS_OR, SGT_PROPOSITIONS_PL_KERNEL_KB_OR, KWD_PROPOSITIONS_NOT, SGT_PROPOSITIONS_PL_KERNEL_KB_NOT, KWD_PROPOSITIONS_FORALL, SGT_PROPOSITIONS_PL_KERNEL_KB_FORALL, KWD_PROPOSITIONS_EXISTS, SGT_PROPOSITIONS_PL_KERNEL_KB_EXISTS, KWD_PROPOSITIONS_EQUIVALENT, SGT_PROPOSITIONS_PL_KERNEL_KB_EQUIVALENT, KWD_PROPOSITIONS_FAIL, SGT_PROPOSITIONS_PL_KERNEL_KB_FAIL, KWD_PROPOSITIONS_COLLECT_INTO, SGT_PROPOSITIONS_PL_KERNEL_KB_COLLECT_INTO, KWD_PROPOSITIONS_IMPLIES, SGT_PROPOSITIONS_PL_KERNEL_KB_SUBSET_OF, NIL);
      oOPERATOR_NAME_TO_SURROGATE_TABLEo = self004;
    }
    oLOGIC_MODULEo = getStellaModule("LOGIC", true);
    oPL_KERNEL_MODULEo = getStellaModule("PL-KERNEL", true);
    oLAST_KB_ACTIONo = KWD_PROPOSITIONS_UPDATE_PROPOSITION;
    oEVALUATIONMODEo = KWD_PROPOSITIONS_EXTENSIONAL_ASSERTION;
    { TruthValue* self005 = newTruthValue();

      self005->polarity = KWD_PROPOSITIONS_TRUE;
      self005->strength = KWD_PROPOSITIONS_STRICT;
      self005->matchScore = 1.0;
      TRUE_TRUTH_VALUE = self005;
    }
    { TruthValue* self006 = newTruthValue();

      self006->polarity = KWD_PROPOSITIONS_FALSE;
      self006->strength = KWD_PROPOSITIONS_STRICT;
      self006->matchScore = -1.0;
      FALSE_TRUTH_VALUE = self006;
    }
    { TruthValue* self007 = newTruthValue();

      self007->polarity = KWD_PROPOSITIONS_TRUE;
      self007->strength = KWD_PROPOSITIONS_DEFAULT;
      self007->matchScore = 0.8;
      DEFAULT_TRUE_TRUTH_VALUE = self007;
    }
    { TruthValue* self008 = newTruthValue();

      self008->polarity = KWD_PROPOSITIONS_FALSE;
      self008->strength = KWD_PROPOSITIONS_DEFAULT;
      self008->matchScore = -0.8;
      DEFAULT_FALSE_TRUTH_VALUE = self008;
    }
    { TruthValue* self009 = newTruthValue();

      self009->polarity = KWD_PROPOSITIONS_UNKNOWN;
      UNKNOWN_TRUTH_VALUE = self009;
    }
    { TruthValue* self010 = newTruthValue();

      self010->polarity = KWD_PROPOSITIONS_INCONSISTENT;
      self010->strength = KWD_PROPOSITIONS_STRICT;
      INCONSISTENT_TRUTH_VALUE = self010;
    }
    { Proposition* self011 = newProposition();

      self011->kind = KWD_PROPOSITIONS_CONSTANT;
      self011->operatoR = SGT_PROPOSITIONS_STELLA_TRUE;
      self011->arguments = stella::newVector(0);
      { Proposition* object013 = self011;
        TruthValue* value014 = TRUE_TRUTH_VALUE;
        Object* oldValue015 = object013->truthValue;
        Object* newValue016 = updateInContext(oldValue015, value014, object013->homeContext, false);

        if (!(((boolean)(oldValue015)) &&
            (oldValue015->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
          object013->truthValue = newValue016;
        }
      }
      self011->homeContext = oPL_KERNEL_MODULEo;
      TRUE_PROPOSITION = self011;
    }
    { Proposition* self017 = newProposition();

      self017->kind = KWD_PROPOSITIONS_CONSTANT;
      self017->operatoR = SGT_PROPOSITIONS_STELLA_FALSE;
      self017->arguments = stella::newVector(0);
      { Proposition* object019 = self017;
        TruthValue* value020 = FALSE_TRUTH_VALUE;
        Object* oldValue021 = object019->truthValue;
        Object* newValue022 = updateInContext(oldValue021, value020, object019->homeContext, false);

        if (!(((boolean)(oldValue021)) &&
            (oldValue021->primaryType() == SGT_PROPOSITIONS_STELLA_CS_VALUE))) {
          object019->truthValue = newValue022;
        }
      }
      self017->homeContext = oPL_KERNEL_MODULEo;
      FALSE_PROPOSITION = self017;
    }
    ANONYMOUS_VARIABLE_NAME = SYM_PROPOSITIONS_STELLA_p;
    oMISSING_KEY_VALUE_LISTo = newKeyValueList();
    oAUTOMATICINSTANCETABLEo = oMISSING_KEY_VALUE_LISTo;
    oSTRUCTURED_OBJECTS_INDEXo = newKeyValueMap();
    oTYPE_CHECK_POLICYo = KWD_PROPOSITIONS_AUTOMATICALLY_FIX_TYPE_VIOLATIONS;
    oTYPECHECKMODEo = KWD_PROPOSITIONS_POST_TYPE_VIOLATIONS;
    oCHECK_TYPES_AGENDAo = newVectorSequence(4);
  }
}

void helpStartupPropositions7() {
  {
    defineStellaTypeFromStringifiedSource("(DEFTYPE PROPOSITIONS-INDEX (SEQUENCE-INDEX OF PROPOSITION))");
    defineStellaTypeFromStringifiedSource("(DEFTYPE INSTANCES-INDEX (SEQUENCE-INDEX OF LOGIC-OBJECT))");
    { Class* clasS = defineClassFromStringifiedSource("BACKLINKS-INDEX", "(DEFCLASS BACKLINKS-INDEX (STANDARD-OBJECT) :DOCUMENTATION \"Contains several types of indices pointing at dependent propositions.\" :SLOTS ((DEPENDENT-PROPOSITIONS-LIST :TYPE PROPOSITIONS-INDEX) (DEPENDENT-ISA-PROPOSITIONS-LIST :TYPE PROPOSITIONS-INDEX) (PREDICATE-PROPOSITIONS-TABLE :TYPE (HASH-TABLE OF SURROGATE PROPOSITIONS-INDEX))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newBacklinksIndex));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessBacklinksIndexSlotValue));
    }
    defineClassFromStringifiedSource("BACKLINKS-MIXIN", "(DEFCLASS BACKLINKS-MIXIN () :DOCUMENTATION \"Inherited by objects that point back at propositions that reference\nthem.\" :SLOTS ((DEPENDENT-PROPOSITIONS-INDEX :TYPE BACKLINKS-INDEX)) :MIXIN? TRUE)");
    { Class* clasS = defineClassFromStringifiedSource("LOGIC-OBJECT", "(DEFCLASS LOGIC-OBJECT (CONTEXT-SENSITIVE-OBJECT DYNAMIC-SLOTS-MIXIN BACKLINKS-MIXIN) :DOCUMENTATION \"Object with propositions, and possibly a variable value.\" :PUBLIC-SLOTS ((HOME-CONTEXT :INITIALLY *MODULE*) (VARIABLE-VALUE-INVERSE :TYPE (CONS OF LOGIC-OBJECT) :DEFAULT NIL :CONTEXT-SENSITIVE? TRUE :DOCUMENTATION \"List of direct parents whose `variable-value' slot points to this object.\") (EQUIVALENT-VALUE :TYPE DESCRIPTION :CONTEXT-SENSITIVE? TRUE :ALLOCATION :DYNAMIC) (SURROGATE-VALUE-INVERSE :TYPE SURROGATE) (UNDECLARED? :TYPE BOOLEAN :ALLOCATION :DYNAMIC) (HYPOTHESIZED-INSTANCE? :TYPE BOOLEAN :ALLOCATION :DYNAMIC) (OBJECT-STRINGIFIED-SOURCE :TYPE STRING :ALLOCATION :DYNAMIC :READER STRINGIFIED-SOURCE :WRITER STRINGIFIED-SOURCE-SETTER) (OBJECT-ORIGINATED-PROPOSITIONS :TYPE (LIST OF PROPOSITION) :DEFAULT NIL-LIST :ALLOCATION :DYNAMIC :READER ORIGINATED-PROPOSITIONS :WRITER ORIGINATED-PROPOSITIONS-SETTER :DOCUMENTATION \"List of propositions generated by the definition of\nthis object.\")) :PRINT-FORM " "(PRINT-TOP-LEVEL-OBJECT SELF STREAM) :INITIALIZER LOG-LOGIC-OBJECT)");

      clasS->classConstructorCode = ((cpp_function_code)(&newLogicObject));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessLogicObjectSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("LOGIC-THING", "(DEFCLASS LOGIC-THING (THING) :DOCUMENTATION \"A subclass of THING so we can add methods to it in\nthe PowerLoom LOGIC module.\")");

      clasS->classConstructorCode = ((cpp_function_code)(&newLogicThing));
    }
    { Class* clasS = defineClassFromStringifiedSource("SKOLEM", "(DEFCLASS SKOLEM (LOGIC-OBJECT) :DOCUMENTATION \"Object whose identity and type are not fixed at creation time.\nPotentially unifiable with any other object.\" :PUBLIC-SLOTS ((SKOLEM-TYPE :TYPE TYPE) (SKOLEM-NAME :TYPE SYMBOL) (VARIABLE-VALUE :TYPE OBJECT :CONTEXT-SENSITIVE? TRUE) (DEFINING-PROPOSITION :TYPE PROPOSITION)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newSkolem));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessSkolemSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("PATTERN-VARIABLE", "(DEFCLASS PATTERN-VARIABLE (SKOLEM) :DOCUMENTATION \"A variable in a logical expression.\" :SLOTS ((BOUND-TO-OFFSET :TYPE INTEGER) (ORIGINAL-SKOLEM-NAME :TYPE SYMBOL :ALLOCATION :DYNAMIC) (VARIABLE-NAME :RENAMES SKOLEM-NAME)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newPatternVariable));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessPatternVariableSlotValue));
    }
    defineStellaTypeFromStringifiedSource("(DEFTYPE OBJECT-VECTOR (VECTOR OF OBJECT))");
    defineStellaTypeFromStringifiedSource("(DEFTYPE ARGUMENTS-VECTOR OBJECT-VECTOR)");
    defineStellaTypeFromStringifiedSource("(DEFTYPE VARIABLES-VECTOR (VECTOR OF PATTERN-VARIABLE))");
    { Class* clasS = defineClassFromStringifiedSource("FORWARD-CHAINING-INDEX", "(DEFCLASS FORWARD-CHAINING-INDEX (STANDARD-OBJECT) :SLOTS ((FORWARD-GOAL :TYPE PROPOSITION) (MASTER-RULE :TYPE PROPOSITION) (IO-VARIABLES :TYPE CONS) (QUERY-BODY :TYPE CONS) (INPUT-BINDINGS :TYPE CONS) (CACHE-ID :TYPE SYMBOL) (CONSEQUENT :TYPE DESCRIPTION)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newForwardChainingIndex));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessForwardChainingIndexSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("DESCRIPTION", "(DEFCLASS DESCRIPTION (LOGIC-OBJECT) :PUBLIC-SLOTS ((PROPOSITION :TYPE PROPOSITION) (IO-VARIABLES :TYPE VARIABLES-VECTOR) (INTERNAL-VARIABLES :TYPE VARIABLES-VECTOR :INITIALLY ZERO-VARIABLES-VECTOR :DOCUMENTATION \"The set of internally quantified variables besides the\ndescriptions's IO variables.  This set includes any top-level implicit\nexistential variables plus any variables introduced by some nested quantifier.\nIMPORTANT: therefore, a description's internal variables are not necessarily\nequivalent to its top-level implicit existential variables.\") (EXTERNAL-VARIABLES :TYPE VARIABLES-VECTOR :ALLOCATION :DYNAMIC) (QUERY-PATTERNS :TYPE (KEY-VALUE-LIST OF BOOLEAN-VECTOR DESCRIPTION)) (COMPLEMENT-DESCRIPTION :TYPE DESCRIPTION :ALLOCATION :DYNAMIC) (RELATIVE-COMPLEMENT :RENAMES COMPLEMENT-DESCRIPTION) (TAXONOMY-NODE :TYPE TAXONOMY-NODE :ALLOCATION :DYNAMIC) (IOTA? :TYPE BOOLEAN :ALLOCATION :DYNAMIC) (DONT-OPTIMIZE? :TYPE BOOLEAN :ALLOCATION :DYNAMIC) (FORWARD-CHAINING-INDICES :TYPE (LIST OF FORWARD-CHAIN" "ING-INDEX) :ALLOCATION :DYNAMIC) (RULES-WITH-DEFERRED-SATELLITES :TYPE PROPOSITIONS-INDEX :ALLOCATION :DYNAMIC) (DEFERRED-CONTRAPOSITIVES? :TYPE BOOLEAN-WRAPPER :ALLOCATION :DYNAMIC :DEFAULT FALSE)) :METHODS ((NATIVE-RELATION ((SELF DESCRIPTION)) :TYPE RELATION (RETURN NULL))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newDescription));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessDescriptionSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("NAMED-DESCRIPTION", "(DEFCLASS NAMED-DESCRIPTION (DESCRIPTION) :PUBLIC-SLOTS ((IO-VARIABLE-NAMES :TYPE (LIST OF SYMBOL)) (IO-VARIABLE-TYPES :TYPE (LIST OF TYPE)) (EXTENSION :TYPE PROPOSITIONS-INDEX) (OBJECT-STRINGIFIED-SOURCE :ALLOCATION :INSTANCE) (OBJECT-ORIGINATED-PROPOSITIONS :TYPE (LIST OF PROPOSITION) :DEFAULT NIL-LIST :ALLOCATION :INSTANCE :DOCUMENTATION \"List of propositions generated by the definition of\nthis description.\") (NATIVE-RELATION-BACK-POINTER :TYPE RELATION :ALLOCATION :DYNAMIC) (CHECK-FOR-CACHED-GOALS? :TYPE BOOLEAN :ALLOCATION :DYNAMIC) (INVERSE-DESCRIPTION :TYPE NAMED-DESCRIPTION :ALLOCATION :DYNAMIC)) :METHODS ((NATIVE-RELATION ((SELF NAMED-DESCRIPTION)) :TYPE RELATION (RETURN (NATIVE-RELATION-BACK-POINTER SELF))) (NATIVE-RELATION-SETTER ((SELF NAMED-DESCRIPTION) (VALUE RELATION)) (SETF (NATIVE-RELATION-BACK-POINTER SELF) VALUE))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newNamedDescription));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessNamedDescriptionSlotValue));
    }
    defineStellaTypeFromStringifiedSource("(DEFTYPE PARTIAL-MATCH-SCORE FLOAT)");
    defineStellaTypeFromStringifiedSource("(DEFTYPE SET-OF-SUPPORT LIST)");
    defineStellaTypeFromStringifiedSource("(DEFTYPE TIMESTAMP INTEGER)");
    { Class* clasS = defineClassFromStringifiedSource("TRUTH-VALUE", "(DEFCLASS TRUTH-VALUE (LOGIC-OBJECT) :PUBLIC-SLOTS ((POLARITY :TYPE KEYWORD :INITIALLY :UNKNOWN :DOCUMENTATION \"One of :TRUE, :FALSE, :UNKNOWN or :INCONSISTENT.\") (STRENGTH :TYPE KEYWORD :INITIALLY NULL :DOCUMENTATION \"Either NULL, :STRICT or :DEFAULT.\") (MATCH-SCORE :TYPE PARTIAL-MATCH-SCORE :INITIALLY 0.0)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newTruthValue));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTruthValueSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("PARTIAL-SUPPORT", "(DEFCLASS PARTIAL-SUPPORT (STANDARD-OBJECT) :PUBLIC-SLOTS ((FACT :TYPE PROPOSITION) (AXIOM :TYPE PROPOSITION) (SCORE :TYPE FLOAT) (ID :TYPE INTEGER) (ARGUMENT-SCORES :TYPE (CONS OF FLOAT-WRAPPER))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newPartialSupport));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessPartialSupportSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("PROPOSITION", "(DEFCLASS PROPOSITION (CONTEXT-SENSITIVE-OBJECT DYNAMIC-SLOTS-MIXIN BACKLINKS-MIXIN) :DOCUMENTATION \"\" :PUBLIC-SLOTS ((HOME-CONTEXT :INITIALLY *MODULE*) (KIND :TYPE KEYWORD) (TRUTH-VALUE :TYPE TRUTH-VALUE :CONTEXT-SENSITIVE? TRUE) (ARGUMENTS :TYPE VECTOR) (OPERATOR :TYPE GENERALIZED-SYMBOL) (RELATIONREF :TYPE SURROGATE :RENAMES OPERATOR) (DEPENDENT-PROPOSITIONS :TYPE (NON-PAGING-INDEX OF PROPOSITION) :INITIALLY NIL-NON-PAGING-INDEX) (SURROGATE-VALUE-INVERSE :TYPE SURROGATE :ALLOCATION :DYNAMIC) (IO-VARIABLES :TYPE VARIABLES-VECTOR :ALLOCATION :DYNAMIC) (VARIABLE-TYPE? :TYPE BOOLEAN-WRAPPER :ALLOCATION :DYNAMIC :DEFAULT FALSE) (ASSERTED-BY-TYPE-CHECKER? :TYPE BOOLEAN :ALLOCATION :DYNAMIC) (DESCRIPTIVE? :TYPE BOOLEAN :ALLOCATION :DYNAMIC) (SUBRELATION-LINK? :TYPE BOOLEAN :ALLOCATION :DYNAMIC) (SUBSUMPTION-LINK? :TYPE BOOLEAN :ALLOCATION :DYNAMIC) (SATELLITE-PROPOSITIONS :TYPE (LIST OF PROPOSITION) :ALLOCATION :DYNAMIC) (MASTER-PROPOSITION :TYPE PROPOSITION :ALLOCATION :DYNAMIC) (PROPOSITION-ORIGINATED-PROPOS" "ITIONS :TYPE (LIST OF PROPOSITION) :DEFAULT NIL-LIST :ALLOCATION :DYNAMIC :READER ORIGINATED-PROPOSITIONS :WRITER ORIGINATED-PROPOSITIONS-SETTER :DOCUMENTATION \"List of propositions generated by the definition of\nthis proposition.\") (DONT-OPTIMIZE? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :OPTION-KEYWORD :DONT-OPTIMIZE?) (FORWARD-ONLY? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :OPTION-KEYWORD :FORWARD-ONLY? :OPTION-HANDLER FORWARD-BACKWARD-OPTION-HANDLER) (BACKWARD-ONLY? :TYPE BOOLEAN :ALLOCATION :DYNAMIC :OPTION-KEYWORD :BACKWARD-ONLY? :OPTION-HANDLER FORWARD-BACKWARD-OPTION-HANDLER) (PROPOSITION-STRINGIFIED-SOURCE :TYPE STRING :ALLOCATION :DYNAMIC :READER STRINGIFIED-SOURCE :WRITER STRINGIFIED-SOURCE-SETTER) (UNFASTENED? :TYPE BOOLEAN-WRAPPER :ALLOCATION :DYNAMIC :DEFAULT FALSE) (ANNOTATIONS :TYPE (PROPERTY-LIST OF KEYWORD OBJECT) :ALLOCATION :DYNAMIC) (WEIGHT :TYPE FLOAT :ALLOCATION :DYNAMIC) (SCORE :TYPE FLOAT-WRAPPER :ALLOCATION :DYNAMIC :CONTEXT-SENSITIVE? TRUE) (NEURAL-NET :TYPE NEURAL-NETWORK :ALLOCATION :DYNA" "MIC) (PROPOSITION-NEURAL-NETWORK :RENAMES NEURAL-NET :TYPE PROPOSITION-NEURAL-NETWORK) (NEURAL-NETWORK :RENAMES PROPOSITION-NEURAL-NETWORK) (WEIGHT-DELTA :TYPE FLOAT :DEFAULT 0.0 :ALLOCATION :DYNAMIC) (MATCH-SCORE :TYPE FLOAT :ALLOCATION :DYNAMIC) (SUPPORT :TYPE (CONS OF PARTIAL-SUPPORT) :ALLOCATION :DYNAMIC)) :PRINT-FORM (PRINT-TOP-LEVEL-OBJECT SELF STREAM))");

      clasS->classConstructorCode = ((cpp_function_code)(&newProposition));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessPropositionSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("QUANTITY-LOGIC-WRAPPER", "(DEFCLASS QUANTITY-LOGIC-WRAPPER (LOGIC-THING) :PUBLIC? TRUE :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE QUANTITY :REQUIRED? TRUE) (FUNCTION-TERM :TYPE CONS)) :PRINT-FORM (IF *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM (WRAPPER-VALUE SELF)) (PRINT-NATIVE-STREAM STREAM \"|Q|\" (WRAPPER-VALUE SELF))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newQuantityLogicWrapper));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessQuantityLogicWrapperSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("INTEGER-LOGIC-WRAPPER", "(DEFCLASS INTEGER-LOGIC-WRAPPER (INTEGER-WRAPPER BACKLINKS-MIXIN) :PRINT-FORM (IF *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM (WRAPPER-VALUE SELF)) (PRINT-NATIVE-STREAM STREAM \"|W|\" (WRAPPER-VALUE SELF))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newIntegerLogicWrapper));
    }
    { Class* clasS = defineClassFromStringifiedSource("FLOAT-LOGIC-WRAPPER", "(DEFCLASS FLOAT-LOGIC-WRAPPER (FLOAT-WRAPPER BACKLINKS-MIXIN) :PRINT-FORM (IF *PRINTREADABLY?* (PRINT-NATIVE-STREAM STREAM (WRAPPER-VALUE SELF)) (PRINT-NATIVE-STREAM STREAM \"|W|\" (WRAPPER-VALUE SELF))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newFloatLogicWrapper));
    }
    { Class* clasS = defineClassFromStringifiedSource("STRING-LOGIC-WRAPPER", "(DEFCLASS STRING-LOGIC-WRAPPER (STRING-WRAPPER BACKLINKS-MIXIN) :PRINT-FORM (LET ((VALUE (WRAPPER-VALUE SELF))) (IF *PRINTREADABLY?* (PRINT-STRING-READABLY VALUE STREAM) (IF (DEFINED? VALUE) (PRINT-NATIVE-STREAM STREAM \"|W|\" #\\\" VALUE #\\\") (PRINT-NATIVE-STREAM STREAM \"|W|\" \"NULL-STRING\")))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newStringLogicWrapper));
    }
    defineStellaTypeFromStringifiedSource("(DEFTYPE ENTITY-MAPPING (KEY-VALUE-MAP OF OBJECT OBJECT) :DOCUMENTATION \"Used to keep track of copied or substituted variables\nand propositions within 'copy-description', etc.  This needs to be a\nsubtype of DICTIONARY.  KEY-VALUE-LIST is a good choice for most cases,\nhowever, for very high-arity relations and descriptions we do get bad performance\nduring copying and equivalence checking and KEY-VALUE-MAP (though more\nheavy-weight) would be the better option.\")");
    { Class* clasS = defineClassFromStringifiedSource("LOGIC-EXCEPTION", "(DEFCLASS LOGIC-EXCEPTION (STELLA-EXCEPTION))");

      clasS->classConstructorCode = ((cpp_function_code)(&newLogicException));
    }
    { Class* clasS = defineClassFromStringifiedSource("PROPOSITION-ERROR", "(DEFCLASS PROPOSITION-ERROR (LOGIC-EXCEPTION))");

      clasS->classConstructorCode = ((cpp_function_code)(&newPropositionError));
    }
    { Class* clasS = defineClassFromStringifiedSource("PARSING-ERROR", "(DEFCLASS PARSING-ERROR (LOGIC-EXCEPTION))");

      clasS->classConstructorCode = ((cpp_function_code)(&newParsingError));
    }
    { Class* clasS = defineClassFromStringifiedSource("CLASH", "(DEFCLASS CLASH (LOGIC-EXCEPTION) :PUBLIC-SLOTS ((PROPOSITION :TYPE PROPOSITION :DOCUMENTATION \"The main proposition involved in the clash\") (CONTEXT :TYPE CONTEXT :DOCUMENTATION \"The context in which the clash occurred\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newClash));
    }
    { Class* clasS = defineClassFromStringifiedSource("TRUTH-VALUE-CLASH", "(DEFCLASS TRUTH-VALUE-CLASH (CLASH))");

      clasS->classConstructorCode = ((cpp_function_code)(&newTruthValueClash));
    }
    { Class* clasS = defineClassFromStringifiedSource("INTERVAL-CLASH", "(DEFCLASS INTERVAL-CLASH (CLASH) :PUBLIC-SLOTS ((INTERVAL-MEMBER :TYPE LOGIC-OBJECT :DOCUMENTATION \"The owner of the interval cache that is unsatisfiable.\") (LOWER-BOUND :TYPE OBJECT) (UPPER-BOUND :TYPE OBJECT) (STRICT-LOWER-BOUND? :TYPE BOOLEAN) (STRICT-UPPER-BOUND? :TYPE BOOLEAN)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newIntervalClash));
    }
    { Class* clasS = defineClassFromStringifiedSource("VARIABLE-VALUE-CLASH", "(DEFCLASS VARIABLE-VALUE-CLASH (CLASH) :PUBLIC-SLOTS ((SKOLEM :TYPE SKOLEM :DOCUMENTATION \"Skolem which is getting multiple values.\") (VALUE1 :TYPE OBJECT :DOCUMENTATION \"First value in value clash\") (VALUE2 :TYPE OBJECT :DOCUMENTATION \"Second value in value clash\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newVariableValueClash));
    }
    { Class* clasS = defineClassFromStringifiedSource("UNIFICATION-CLASH", "(DEFCLASS UNIFICATION-CLASH (CLASH) :PUBLIC-SLOTS ((VALUE1 :TYPE OBJECT :DOCUMENTATION \"First value in unification clash\") (VALUE2 :TYPE OBJECT :DOCUMENTATION \"Second value in unification clash\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newUnificationClash));
    }
    { Class* clasS = defineClassFromStringifiedSource("FAIL-EXCEPTION", "(DEFCLASS FAIL-EXCEPTION (LOGIC-EXCEPTION))");

      clasS->classConstructorCode = ((cpp_function_code)(&newFailException));
    }
    { Class* clasS = defineClassFromStringifiedSource("QUERY-THREAD-LIMIT-VIOLATION", "(DEFCLASS QUERY-THREAD-LIMIT-VIOLATION (LOGIC-EXCEPTION))");

      clasS->classConstructorCode = ((cpp_function_code)(&newQueryThreadLimitViolation));
    }
    { Class* clasS = defineClassFromStringifiedSource("EXCEPTION-RECORD", "(DEFCLASS EXCEPTION-RECORD (STANDARD-OBJECT) :SLOTS ((EXCEPTION :TYPE STELLA-EXCEPTION) (CONTEXT :TYPE CONTEXT) (MODULE :TYPE MODULE)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newExceptionRecord));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessExceptionRecordSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("OBJECT-ALREADY-EXISTS-EXCEPTION", "(DEFCLASS OBJECT-ALREADY-EXISTS-EXCEPTION (STELLA-EXCEPTION) :PUBLIC? TRUE :PUBLIC-SLOTS ((EXISTING-OBJECT :TYPE OBJECT)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newObjectAlreadyExistsException));
    }
    { Class* clasS = defineClassFromStringifiedSource("CHECK-TYPES-RECORD", "(DEFCLASS CHECK-TYPES-RECORD (STANDARD-OBJECT) :SLOTS ((PROPOSITION :TYPE PROPOSITION) (PARENT-PROPOSITION :TYPE OBJECT) (PARENT-DESCRIPTION :TYPE DESCRIPTION) (MODULE :TYPE MODULE)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newCheckTypesRecord));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessCheckTypesRecordSlotValue));
    }
  }
}

void helpStartupPropositions8() {
  {
    defineFunctionObject("LOG-LOGIC-OBJECT", "(DEFUN LOG-LOGIC-OBJECT ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&logLogicObject)), NULL);
    defineMethodObject("(DEFMETHOD (DELETED? BOOLEAN) ((SELF FORWARD-CHAINING-INDEX)))", wrapMethodCode(((cpp_method_code)(&ForwardChainingIndex::deletedP))), NULL);
    defineInlineMethodCode(SGT_PROPOSITIONS_LOGIC_DESCRIPTION, SYM_PROPOSITIONS_LOGIC_NATIVE_RELATION, wrapMethodCode(((cpp_method_code)(&Description::nativeRelation))), NULL);
    defineInlineMethodCode(SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION, SYM_PROPOSITIONS_LOGIC_NATIVE_RELATION, wrapMethodCode(((cpp_method_code)(&NamedDescription::nativeRelation))), NULL);
    defineInlineMethodCode(SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION, SYM_PROPOSITIONS_LOGIC_NATIVE_RELATION_SETTER, wrapMethodCode(((cpp_method_code)(&NamedDescription::nativeRelationSetter))), NULL);
    defineFunctionObject("STRINGIFIED-SOURCE", "(DEFUN (STRINGIFIED-SOURCE STRING) ((SELF OBJECT)))", ((cpp_function_code)(&stringifiedSource)), NULL);
    defineFunctionObject("STRINGIFIED-SOURCE-SETTER", "(DEFUN (STRINGIFIED-SOURCE-SETTER STRING) ((SELF OBJECT) (VALUE STRING)))", ((cpp_function_code)(&stringifiedSourceSetter)), NULL);
    defineFunctionObject("ORIGINATED-PROPOSITIONS", "(DEFUN (ORIGINATED-PROPOSITIONS (LIST OF PROPOSITION)) ((SELF OBJECT)))", ((cpp_function_code)(&originatedPropositions)), NULL);
    defineFunctionObject("ORIGINATED-PROPOSITIONS-SETTER", "(DEFUN (ORIGINATED-PROPOSITIONS-SETTER (LIST OF PROPOSITION)) ((SELF OBJECT) (VALUE (LIST OF PROPOSITION))))", ((cpp_function_code)(&originatedPropositionsSetter)), NULL);
    defineFunctionObject("CREATE-PROPOSITION", "(DEFUN (CREATE-PROPOSITION PROPOSITION) ((KIND SYMBOL) (ARGUMENTCOUNT INTEGER)))", ((cpp_function_code)(&createProposition)), NULL);
    defineFunctionObject("ENFORCE-CODE-ONLY", "(DEFUN ENFORCE-CODE-ONLY ())", ((cpp_function_code)(&enforceCodeOnly)), NULL);
    defineFunctionObject("GET-PROPOSITION-BASE-OPERATOR", "(DEFUN (GET-PROPOSITION-BASE-OPERATOR SURROGATE) ((PROP PROPOSITION)) :PUBLIC? TRUE)", ((cpp_function_code)(&getPropositionBaseOperator)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT CONTEXT MONOTONIC? :TYPE BOOLEAN :PUBLIC? TRUE :DOCUMENTATION \"Mark context as not allowing any retractions.\" :ALLOCATION :DYNAMIC)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT WORLD TRUTH-MAINTAINED? :TYPE BOOLEAN :PUBLIC? TRUE :ALLOCATION :DYNAMIC)");
    defineExternalSlotFromStringifiedSource("(DEFSLOT WORLD UP-TO-DATE-INFERENCES? :TYPE BOOLEAN :PUBLIC? TRUE :ALLOCATION :DYNAMIC)");
    defineFunctionObject("LOGIC-MODULE?", "(DEFUN (LOGIC-MODULE? BOOLEAN) ((SELF MODULE)) :DOCUMENTATION \"Return TRUE if 'self' is a logic module, implying\nthat relations defined within it define a knowledge base.  A module\nis a logic module iff it inherits the module 'PL-KERNEL'.\")", ((cpp_function_code)(&logicModuleP)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT MODULE LOCALLY-CONCEIVED-PROPOSITIONS-INTERNAL :TYPE PROPOSITIONS-INDEX :ALLOCATION :DYNAMIC)");
    defineFunctionObject("LOCALLY-CONCEIVED-PROPOSITIONS", "(DEFUN (LOCALLY-CONCEIVED-PROPOSITIONS PROPOSITIONS-INDEX) ((SELF MODULE)))", ((cpp_function_code)(&locallyConceivedPropositions)), NULL);
    defineFunctionObject("LOCALLY-CONCEIVED-PROPOSITIONS-SETTER", "(DEFUN LOCALLY-CONCEIVED-PROPOSITIONS-SETTER ((SELF MODULE) (VALUE PROPOSITIONS-INDEX)))", ((cpp_function_code)(&locallyConceivedPropositionsSetter)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT CONTEXT LOCALLY-CONCEIVED-INSTANCES-INTERNAL :TYPE INSTANCES-INDEX :ALLOCATION :DYNAMIC)");
    defineFunctionObject("LOCALLY-CONCEIVED-INSTANCES", "(DEFUN (LOCALLY-CONCEIVED-INSTANCES INSTANCES-INDEX) ((SELF CONTEXT)))", ((cpp_function_code)(&locallyConceivedInstances)), NULL);
    defineFunctionObject("LOCALLY-CONCEIVED-INSTANCES-SETTER", "(DEFUN LOCALLY-CONCEIVED-INSTANCES-SETTER ((SELF CONTEXT) (VALUE INSTANCES-INDEX)))", ((cpp_function_code)(&locallyConceivedInstancesSetter)), NULL);
    defineFunctionObject("INCREMENT-NOW-TIMESTAMP", "(DEFUN INCREMENT-NOW-TIMESTAMP ())", ((cpp_function_code)(&incrementNowTimestamp)), NULL);
    defineFunctionObject("GET-NOW-TIMESTAMP", "(DEFUN (GET-NOW-TIMESTAMP TIMESTAMP) ())", ((cpp_function_code)(&getNowTimestamp)), NULL);
    defineFunctionObject("UPDATE-NOW-TIMESTAMP", "(DEFUN UPDATE-NOW-TIMESTAMP ((KBACTION KEYWORD)))", ((cpp_function_code)(&updateNowTimestamp)), NULL);
    defineFunctionObject("BOTTOM?", "(DEFUN (BOTTOM? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Return TRUE if 'self' is the undefined individual BOTTOM.\")", ((cpp_function_code)(&bottomP)), NULL);
    defineFunctionObject("SUBRELATION-OF?", "(DEFUN (SUBRELATION-OF? BOOLEAN) ((DESC1 NAMED-DESCRIPTION) (DESC2 NAMED-DESCRIPTION)) :PUBLIC? TRUE)", ((cpp_function_code)(&subrelationOfP)), NULL);
    defineFunctionObject("LOGICAL-SUBTYPE-OF?", "(DEFUN (LOGICAL-SUBTYPE-OF? BOOLEAN) ((TYPE1 SURROGATE) (TYPE2 SURROGATE)) :PUBLIC? TRUE)", ((cpp_function_code)(&logicalSubtypeOfP)), NULL);
    defineFunctionObject("LOGICAL-SUBTYPE-OF-LITERAL?", "(DEFUN (LOGICAL-SUBTYPE-OF-LITERAL? BOOLEAN) ((TYPE SURROGATE)) :PUBLIC? TRUE)", ((cpp_function_code)(&logicalSubtypeOfLiteralP)), NULL);
    defineFunctionObject("LITERAL-TYPE?", "(DEFUN (LITERAL-TYPE? BOOLEAN) ((TYPE SURROGATE)) :PUBLIC? TRUE)", ((cpp_function_code)(((boolean  (*) (Surrogate*))(&literalTypeP)))), NULL);
    defineFunctionObject("BOOLEAN-TYPE?", "(DEFUN (BOOLEAN-TYPE? BOOLEAN) ((SELF TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(((boolean  (*) (Surrogate*))(&booleanTypeP)))), NULL);
    defineFunctionObject("PROPOSITION-TYPE?", "(DEFUN (PROPOSITION-TYPE? BOOLEAN) ((SELF TYPE)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (EQL? SELF @PROPOSITION)))", ((cpp_function_code)(&propositionTypeP)), NULL);
    defineFunctionObject("CLASS-DESCRIPTION?", "(DEFUN (CLASS-DESCRIPTION? BOOLEAN) ((SELF NAMED-DESCRIPTION)) :PUBLIC? TRUE)", ((cpp_function_code)(&classDescriptionP)), NULL);
    defineFunctionObject("FUNCTION-DESCRIPTION?", "(DEFUN (FUNCTION-DESCRIPTION? BOOLEAN) ((SELF NAMED-DESCRIPTION)) :PUBLIC? TRUE)", ((cpp_function_code)(&functionDescriptionP)), NULL);
    defineFunctionObject("VARIABLE-ARITY?", "(DEFUN (VARIABLE-ARITY? BOOLEAN) ((SELF DESCRIPTION)) :PUBLIC? TRUE)", ((cpp_function_code)(&variableArityP)), NULL);
    defineMethodObject("(DEFMETHOD (ARITY INTEGER) ((SELF NAMED-DESCRIPTION)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NamedDescription::arity))), NULL);
    defineMethodObject("(DEFMETHOD (ARITY INTEGER) ((SELF DESCRIPTION)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&Description::arity))), NULL);
    defineFunctionObject("MONADIC?", "(DEFUN (MONADIC? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&monadicP)), NULL);
    defineFunctionObject("COMPUTED-RELATION?", "(DEFUN (COMPUTED-RELATION? BOOLEAN) ((DESCRIPTION NAMED-DESCRIPTION)) :PUBLIC? TRUE)", ((cpp_function_code)(&computedRelationP)), NULL);
    defineFunctionObject("LAST-ARGUMENT", "(DEFUN (LAST-ARGUMENT OBJECT) ((PROPOSITION PROPOSITION)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NTH (ARGUMENTS PROPOSITION) (1- (LENGTH (ARGUMENTS PROPOSITION))))))", ((cpp_function_code)(&lastArgument)), NULL);
    defineFunctionObject("OBJECT-SURROGATE", "(DEFUN (OBJECT-SURROGATE SURROGATE) ((SELF OBJECT)) :DOCUMENTATION \"Return the surrogate naming the object `self', which\nmay be a Stella class that is used in PowerLoom as well as\na more normal powerloom object.\" :PUBLIC? TRUE)", ((cpp_function_code)(&objectSurrogate)), NULL);
    defineFunctionObject("OBJECT-SURROGATE-SETTER", "(DEFUN (OBJECT-SURROGATE-SETTER SURROGATE) ((SELF OBJECT) (NAME SURROGATE)) :DOCUMENTATION \"Return the name of the logic object `self' to `name'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&objectSurrogateSetter)), NULL);
    defineFunctionObject("OBJECT-NAME", "(DEFUN (OBJECT-NAME SYMBOL) ((SELF OBJECT)) :DOCUMENTATION \"Return the name symbol for the logic object `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&objectName)), NULL);
    defineFunctionObject("OBJECT-NAME-STRING", "(DEFUN (OBJECT-NAME-STRING STRING) ((SELF OBJECT)) :DOCUMENTATION \"Return the name string for the logic object `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&objectNameString)), NULL);
    defineFunctionObject("OBJECT-STRING-NAME", "(DEFUN (OBJECT-STRING-NAME STRING) ((SELF OBJECT)))", ((cpp_function_code)(&objectStringName)), NULL);
    defineFunctionObject("DESCRIPTION-MODE?", "(DEFUN (DESCRIPTION-MODE? BOOLEAN) ())", ((cpp_function_code)(&descriptionModeP)), NULL);
    defineFunctionObject("NATURAL-DEDUCTION-MODE?", "(DEFUN (NATURAL-DEDUCTION-MODE? BOOLEAN) () :DOCUMENTATION \"True if normalization is governed by natural\ndeduction semantics.\")", ((cpp_function_code)(&naturalDeductionModeP)), NULL);
    defineFunctionObject("CONTEXT-DEPENDENT-SEARCH-MODE?", "(DEFUN (CONTEXT-DEPENDENT-SEARCH-MODE? BOOLEAN) ())", ((cpp_function_code)(&contextDependentSearchModeP)), NULL);
    defineFunctionObject("LOG-NEWLY-CONCEIVED-PROPOSITION", "(DEFUN LOG-NEWLY-CONCEIVED-PROPOSITION ((SELF MODULE) (PROPOSITION PROPOSITION)))", ((cpp_function_code)(&logNewlyConceivedProposition)), NULL);
    defineFunctionObject("CLIP-OR-CLASH-WITH-OLD-PREDICATE-VALUE", "(DEFUN CLIP-OR-CLASH-WITH-OLD-PREDICATE-VALUE ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&clipOrClashWithOldPredicateValue)), NULL);
    defineFunctionObject("RUN-UPDATE-EQUIVALENCE-PROPOSITION-DEMON", "(DEFUN RUN-UPDATE-EQUIVALENCE-PROPOSITION-DEMON ((PROPOSITION PROPOSITION) (UPDATEMODE KEYWORD)))", ((cpp_function_code)(&runUpdateEquivalencePropositionDemon)), NULL);
    defineFunctionObject("HELP-RUN-UPDATE-PROPOSITION-DEMON", "(DEFUN HELP-RUN-UPDATE-PROPOSITION-DEMON ((PROPOSITION PROPOSITION) (UPDATEMODE KEYWORD)))", ((cpp_function_code)(&helpRunUpdatePropositionDemon)), NULL);
    defineFunctionObject("RUN-UPDATE-PROPOSITION-DEMON", "(DEFUN RUN-UPDATE-PROPOSITION-DEMON ((PROPOSITION PROPOSITION) (UPDATEMODE KEYWORD)))", ((cpp_function_code)(&runUpdatePropositionDemon)), NULL);
    defineFunctionObject("RUN-TRUTH-CHANGE-DEMON", "(DEFUN RUN-TRUTH-CHANGE-DEMON ((PROPOSITION PROPOSITION) (TRUTHCHANGERELATION SURROGATE)))", ((cpp_function_code)(&runTruthChangeDemon)), NULL);
    defineFunctionObject("RUN-GOES-TRUE-DEMONS", "(DEFUN RUN-GOES-TRUE-DEMONS ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&runGoesTrueDemons)), NULL);
    defineFunctionObject("RUN-GOES-FALSE-DEMONS", "(DEFUN RUN-GOES-FALSE-DEMONS ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&runGoesFalseDemons)), NULL);
    defineFunctionObject("RUN-GOES-UNKNOWN-DEMONS", "(DEFUN RUN-GOES-UNKNOWN-DEMONS ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&runGoesUnknownDemons)), NULL);
    defineFunctionObject("UPDATE-LINKS-AND-TIMESTAMPS", "(DEFUN UPDATE-LINKS-AND-TIMESTAMPS ((PROPOSITION PROPOSITION) (UPDATEMODE KEYWORD)))", ((cpp_function_code)(&updateLinksAndTimestamps)), NULL);
    defineFunctionObject("ASSIGN-TRUTH-VALUE", "(DEFUN ASSIGN-TRUTH-VALUE ((SELF PROPOSITION) (TRUTHVALUE OBJECT)))", ((cpp_function_code)(&assignTruthValue)), NULL);
    defineFunctionObject("DEASSIGN-TRUTH-VALUE", "(DEFUN DEASSIGN-TRUTH-VALUE ((SELF PROPOSITION) (UPDATEMODE KEYWORD)))", ((cpp_function_code)(&deassignTruthValue)), NULL);
  }
}

void helpStartupPropositions9() {
  {
    defineFunctionObject("UPDATE-PROPOSITION-TRUTH-VALUE", "(DEFUN UPDATE-PROPOSITION-TRUTH-VALUE ((SELF PROPOSITION) (UPDATEMODE KEYWORD)))", ((cpp_function_code)(&updatePropositionTruthValue)), NULL);
    defineFunctionObject("ASSIGN-PROPOSITION-WEIGHT", "(DEFUN ASSIGN-PROPOSITION-WEIGHT ((SELF PROPOSITION) (WEIGHT PARTIAL-MATCH-SCORE)))", ((cpp_function_code)(&assignPropositionWeight)), NULL);
    defineFunctionObject("TICKLE-CONTEXT", "(DEFUN (TICKLE-CONTEXT CONTEXT) ())", ((cpp_function_code)(&tickleContext)), NULL);
    defineFunctionObject("TICKLE-INSTANCES", "(DEFUN (TICKLE-INSTANCES CONTEXT) ())", ((cpp_function_code)(&tickleInstances)), NULL);
    defineFunctionObject("LIST-INCONSISTENT-PROPOSITIONS", "(DEFUN (LIST-INCONSISTENT-PROPOSITIONS (CONS OF PROPOSITION)) (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Return a list of all currently known inconsistent proposition in the module defined\nby the :module option (which defaults to the current module).  If `:local?' is specified\nas TRUE only look in the specified module but not any modules it inherits.  Note, that\nthis simply reports propositions that have been assigned an inconsistent truth value so\nfar (e.g., in clash exceptions), it will not try to detect any new or all inconsistencies\nin a module.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&listInconsistentPropositions)), ((cpp_function_code)(&listInconsistentPropositionsEvaluatorWrapper)));
    defineFunctionObject("REACT-TO-SKOLEM-VALUE-UPDATE", "(DEFUN REACT-TO-SKOLEM-VALUE-UPDATE ((SKOLEM SKOLEM) (OLDVALUE OBJECT) (NEWVALUE OBJECT) (TOPLEVELUPDATE? BOOLEAN)))", ((cpp_function_code)(&reactToSkolemValueUpdate)), NULL);
    defineFunctionObject("NATIVE-SLOT-PROPOSITION?", "(DEFUN (NATIVE-SLOT-PROPOSITION? BOOLEAN) ((SELF PROPOSITION)))", ((cpp_function_code)(&nativeSlotPropositionP)), NULL);
    defineFunctionObject("UPDATE-NATIVE-SLOT-PROPOSITION", "(DEFUN (UPDATE-NATIVE-SLOT-PROPOSITION (CONS OF PROPOSITION)) ((PROPOSITION PROPOSITION) (UPDATEMODE KEYWORD)))", ((cpp_function_code)(&updateNativeSlotProposition)), NULL);
    defineFunctionObject("ASSIGN-NATIVE-SLOT-VALUE", "(DEFUN ASSIGN-NATIVE-SLOT-VALUE ((PROP PROPOSITION) (SELF THING) (SLOT STORAGE-SLOT) (VALUE OBJECT)))", ((cpp_function_code)(&assignNativeSlotValue)), NULL);
    defineFunctionObject("CLEAR-NATIVE-SLOT-VALUE", "(DEFUN CLEAR-NATIVE-SLOT-VALUE ((OBJECT THING) (SLOT STORAGE-SLOT)))", ((cpp_function_code)(&clearNativeSlotValue)), NULL);
    defineFunctionObject("DROP-NATIVE-SLOT-VALUE", "(DEFUN DROP-NATIVE-SLOT-VALUE ((SELF THING) (SLOT STORAGE-SLOT) (VALUE OBJECT)))", ((cpp_function_code)(&dropNativeSlotValue)), NULL);
    defineFunctionObject("LOOKUP-SLOTREF-ON-INSTANCE", "(DEFUN (LOOKUP-SLOTREF-ON-INSTANCE SURROGATE) ((TERM OBJECT) (SLOTNAME SYMBOL)))", ((cpp_function_code)(&lookupSlotrefOnInstance)), NULL);
    defineFunctionObject("UNBOUND?", "(DEFUN (UNBOUND? BOOLEAN) ((SKOLEM SKOLEM)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (NULL? (VARIABLE-VALUE SKOLEM))))", ((cpp_function_code)(&unboundP)), NULL);
    defineFunctionObject("VALUE-OF", "(DEFUN (VALUE-OF OBJECT) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&valueOf)), NULL);
    defineFunctionObject("SURROGATE.VALUE-OF", "(DEFUN (SURROGATE.VALUE-OF OBJECT) ((SELF SURROGATE)))", ((cpp_function_code)(&surrogateDvalueOf)), NULL);
    defineFunctionObject("RELATION.VALUE-OF", "(DEFUN (RELATION.VALUE-OF DESCRIPTION) ((SELF RELATION)))", ((cpp_function_code)(&relationDvalueOf)), NULL);
    defineFunctionObject("EQUIVALENT-VALUE-OF", "(DEFUN (EQUIVALENT-VALUE-OF OBJECT) ((SELF OBJECT)))", ((cpp_function_code)(&equivalentValueOf)), NULL);
    defineFunctionObject("GROUND-VALUE-OF", "(DEFUN (GROUND-VALUE-OF OBJECT) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&groundValueOf)), NULL);
    defineFunctionObject("SKOLEM?", "(DEFUN (SKOLEM? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&skolemP)), NULL);
    defineFunctionObject("VARIABLE?", "(DEFUN (VARIABLE? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&variableP)), NULL);
    defineFunctionObject("NATIVE-VALUE?", "(DEFUN (NATIVE-VALUE? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&nativeValueP)), NULL);
    defineFunctionObject("NATIVE-VALUE-OF", "(DEFUN (NATIVE-VALUE-OF OBJECT) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&nativeValueOf)), NULL);
    defineFunctionObject("INNERMOST-VARIABLE-OF", "(DEFUN (INNERMOST-VARIABLE-OF PATTERN-VARIABLE) ((SELF PATTERN-VARIABLE)))", ((cpp_function_code)(&innermostVariableOf)), NULL);
    defineFunctionObject("INNERMOST-OF", "(DEFUN (INNERMOST-OF OBJECT) ((SELF OBJECT)))", ((cpp_function_code)(&innermostOf)), NULL);
    defineFunctionObject("YIELD-ANONYMOUS-SKOLEM-NAME", "(DEFUN (YIELD-ANONYMOUS-SKOLEM-NAME SYMBOL) ((VARIABLE? BOOLEAN)))", ((cpp_function_code)(&yieldAnonymousSkolemName)), NULL);
    defineFunctionObject("HELP-CREATE-SKOLEM", "(DEFUN (HELP-CREATE-SKOLEM SKOLEM) ((SELF SKOLEM) (TYPE TYPE) (NAME SYMBOL) (ASSERTISA? BOOLEAN)))", ((cpp_function_code)(&helpCreateSkolem)), NULL);
    defineFunctionObject("CREATE-SKOLEM", "(DEFUN (CREATE-SKOLEM SKOLEM) ((TYPE TYPE) (NAME SYMBOL)) :PUBLIC? TRUE)", ((cpp_function_code)(&createSkolem)), NULL);
    defineFunctionObject("CREATE-VARIABLE", "(DEFUN (CREATE-VARIABLE PATTERN-VARIABLE) ((TYPE TYPE) (NAME SYMBOL) (ASSERTISA? BOOLEAN)) :PUBLIC? TRUE)", ((cpp_function_code)(&createVariable)), NULL);
    defineFunctionObject("CREATE-VARIABLE-OR-SKOLEM", "(DEFUN (CREATE-VARIABLE-OR-SKOLEM SKOLEM) ((TYPE TYPE) (NAME SYMBOL)) :PUBLIC? TRUE)", ((cpp_function_code)(&createVariableOrSkolem)), NULL);
    defineMethodObject("(DEFMETHOD (OBJECT-EQUAL? BOOLEAN) ((SELF SKOLEM) (OTHER OBJECT)))", wrapMethodCode(((cpp_method_code)(&Skolem::objectEqualP))), NULL);
    defineFunctionObject("TRUE?", "(DEFUN (TRUE? BOOLEAN) ((SELF PROPOSITION)) :DOCUMENTATION \"Return true if `self' is true (or default-true if we are\nconsidering default assertions).\" :PUBLIC? TRUE)", ((cpp_function_code)(&trueP)), NULL);
    defineFunctionObject("FALSE?", "(DEFUN (FALSE? BOOLEAN) ((SELF PROPOSITION)) :DOCUMENTATION \"Return true if `self' is false (or default-false if we are\nconsidering default assertions).\" :PUBLIC? TRUE)", ((cpp_function_code)(&falseP)), NULL);
    defineFunctionObject("UNKNOWN?", "(DEFUN (UNKNOWN? BOOLEAN) ((SELF PROPOSITION)) :DOCUMENTATION \"Return true if the truth of `self' is unknown.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unknownP)), NULL);
    defineFunctionObject("INCONSISTENT?", "(DEFUN (INCONSISTENT? BOOLEAN) ((SELF PROPOSITION)) :DOCUMENTATION \"Return true if `self' is inconsistent (true and false).\" :PUBLIC? TRUE)", ((cpp_function_code)(&inconsistentP)), NULL);
    defineFunctionObject("DEFAULT-TRUE?", "(DEFUN (DEFAULT-TRUE? BOOLEAN) ((SELF PROPOSITION)) :DOCUMENTATION \"Return true if `self' is default true.\" :PUBLIC? TRUE)", ((cpp_function_code)(&defaultTrueP)), NULL);
    defineFunctionObject("DEFAULT-FALSE?", "(DEFUN (DEFAULT-FALSE? BOOLEAN) ((SELF PROPOSITION)) :DOCUMENTATION \"Return true if `self' is default false.\" :PUBLIC? TRUE)", ((cpp_function_code)(&defaultFalseP)), NULL);
    defineFunctionObject("ASSERTED-TRUE?", "(DEFUN (ASSERTED-TRUE? BOOLEAN) ((SELF PROPOSITION)) :DOCUMENTATION \"Return true if `self' has been asserted to be true.\" :PUBLIC? TRUE)", ((cpp_function_code)(&assertedTrueP)), NULL);
    defineFunctionObject("ASSERTED-FALSE?", "(DEFUN (ASSERTED-FALSE? BOOLEAN) ((SELF PROPOSITION)) :DOCUMENTATION \"Return true if `self' has been asserted to be false.\" :PUBLIC? TRUE)", ((cpp_function_code)(&assertedFalseP)), NULL);
    defineFunctionObject("DEFAULTIFY-TRUTH-VALUE", "(DEFUN (DEFAULTIFY-TRUTH-VALUE TRUTH-VALUE) ((TRUE? BOOLEAN) (BYDEFAULT? BOOLEAN)))", ((cpp_function_code)(&defaultifyTruthValue)), NULL);
    defineFunctionObject("CONJOIN-TRUTH-VALUES", "(DEFUN (CONJOIN-TRUTH-VALUES TRUTH-VALUE) ((TV1 TRUTH-VALUE) (TV2 TRUTH-VALUE)) :DOCUMENTATION \"Return the logical conjunction of truth values `tv1' and `tv2'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&conjoinTruthValues)), NULL);
    defineFunctionObject("DISJOIN-TRUTH-VALUES", "(DEFUN (DISJOIN-TRUTH-VALUES TRUTH-VALUE) ((TV1 TRUTH-VALUE) (TV2 TRUTH-VALUE)) :DOCUMENTATION \"Return the logical disjunction of truth values `tv1' and `tv2'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&disjoinTruthValues)), NULL);
    defineFunctionObject("INVERT-TRUTH-VALUE", "(DEFUN (INVERT-TRUTH-VALUE TRUTH-VALUE) ((SELF TRUTH-VALUE)) :DOCUMENTATION \"Return the logical negation of `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&invertTruthValue)), NULL);
    defineFunctionObject("STRONGER-TRUTH-VALUE?", "(DEFUN (STRONGER-TRUTH-VALUE? BOOLEAN) ((TV1 TRUTH-VALUE) (TV2 TRUTH-VALUE)) :DOCUMENTATION \"Compare the two truth values and return `true' if `tv1' is strictly\nstronger than `tv2'.  Stronger uses the following partial order:\n  INCONSISTENT > STRICT > DEFAULT > UNKNOWN.\nTruth values at the same level are equal in strength.\" :PUBLIC? TRUE)", ((cpp_function_code)(&strongerTruthValueP)), NULL);
    defineFunctionObject("MERGE-TRUTH-VALUES", "(DEFUN (MERGE-TRUTH-VALUES TRUTH-VALUE) ((TV1 TRUTH-VALUE) (TV2 TRUTH-VALUE)) :DOCUMENTATION \"Merge two truth values that are describing the \\\"same\\\" logical\nproposition.  This handles subordination of default to strict values, \nknown over unknown and potential inconsistent values.\n\nIn particular, this can be used to check for negated values by asking for\nthe truth of a proposition and its negation, inverting the negation and then\nusing merge to come up with an answer.\" :PUBLIC? TRUE)", ((cpp_function_code)(&mergeTruthValues)), NULL);
    defineFunctionObject("WEAKEN-TRUTH-VALUE", "(DEFUN (WEAKEN-TRUTH-VALUE TRUTH-VALUE) ((TV1 TRUTH-VALUE) (TV2 TRUTH-VALUE)) :DOCUMENTATION \"If `tv2' has lesser strength than `tv1', adapt the strength of `tv1' (not\nits value!) and return the result.  Otherwise, return `tv1' unmodified.\" :PUBLIC? TRUE)", ((cpp_function_code)(&weakenTruthValue)), NULL);
    defineFunctionObject("STRENGTHEN-TRUTH-VALUE", "(DEFUN (STRENGTHEN-TRUTH-VALUE TRUTH-VALUE) ((TV1 TRUTH-VALUE) (TV2 TRUTH-VALUE)) :DOCUMENTATION \"If `tv2' has greater strength than `tv1', adapt the strength of `tv1' (not\nits value!) and return the result.  Otherwise, return `tv1' unmodified.\" :PUBLIC? TRUE)", ((cpp_function_code)(&strengthenTruthValue)), NULL);
    defineFunctionObject("TRUE-TRUTH-VALUE?", "(DEFUN (TRUE-TRUTH-VALUE? BOOLEAN) ((SELF TRUTH-VALUE)) :DOCUMENTATION \"Return TRUE if `self' represents some form of truth.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (OR (EQL? SELF TRUE-TRUTH-VALUE) (EQL? SELF DEFAULT-TRUE-TRUTH-VALUE))))", ((cpp_function_code)(&trueTruthValueP)), NULL);
    defineFunctionObject("FALSE-TRUTH-VALUE?", "(DEFUN (FALSE-TRUTH-VALUE? BOOLEAN) ((SELF TRUTH-VALUE)) :DOCUMENTATION \"Return TRUE if `self' represents some form of falsehood.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (OR (EQL? SELF FALSE-TRUTH-VALUE) (EQL? SELF DEFAULT-FALSE-TRUTH-VALUE))))", ((cpp_function_code)(&falseTruthValueP)), NULL);
    defineFunctionObject("STRICT-TRUTH-VALUE?", "(DEFUN (STRICT-TRUTH-VALUE? BOOLEAN) ((SELF TRUTH-VALUE)) :DOCUMENTATION \"Return TRUE if `self' is a strict truth value.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (OR (EQL? SELF TRUE-TRUTH-VALUE) (EQL? SELF FALSE-TRUTH-VALUE))))", ((cpp_function_code)(&strictTruthValueP)), NULL);
    defineFunctionObject("DEFAULT-TRUTH-VALUE?", "(DEFUN (DEFAULT-TRUTH-VALUE? BOOLEAN) ((SELF TRUTH-VALUE)) :DOCUMENTATION \"Return TRUE if `self' is a default truth value.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (OR (EQL? SELF DEFAULT-TRUE-TRUTH-VALUE) (EQL? SELF DEFAULT-FALSE-TRUTH-VALUE))))", ((cpp_function_code)(&defaultTruthValueP)), NULL);
    defineFunctionObject("UNKNOWN-TRUTH-VALUE?", "(DEFUN (UNKNOWN-TRUTH-VALUE? BOOLEAN) ((SELF TRUTH-VALUE)) :DOCUMENTATION \"Return TRUE if `self' represents UNKNOWN.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (OR (EQL? SELF UNKNOWN-TRUTH-VALUE) (NULL? SELF))))", ((cpp_function_code)(((boolean  (*) (TruthValue*))(&unknownTruthValueP)))), NULL);
    defineFunctionObject("KNOWN-TRUTH-VALUE?", "(DEFUN (KNOWN-TRUTH-VALUE? BOOLEAN) ((SELF TRUTH-VALUE)) :DOCUMENTATION \"Return TRUE if `self' is a known truth value, that is\neither TRUE or FALSE, but not UNKNOWN, INCONSISTENT, etc.\")", ((cpp_function_code)(&knownTruthValueP)), NULL);
    defineFunctionObject("INCONSISTENT-TRUTH-VALUE?", "(DEFUN (INCONSISTENT-TRUTH-VALUE? BOOLEAN) ((SELF TRUTH-VALUE)) :DOCUMENTATION \"Return TRUE if `self' represents INCONSISTENT.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (EQL? SELF INCONSISTENT-TRUTH-VALUE)))", ((cpp_function_code)(&inconsistentTruthValueP)), NULL);
    defineFunctionObject("TRUTH-VALUE-TO-STRING", "(DEFUN (TRUTH-VALUE-TO-STRING STRING) ((SELF TRUTH-VALUE) (ABBREVIATE? BOOLEAN)))", ((cpp_function_code)(&truthValueToString)), NULL);
    defineFunctionObject("PRINT-TRUTH-VALUE", "(DEFUN PRINT-TRUTH-VALUE ((SELF TRUTH-VALUE) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printTruthValue)), NULL);
    defineFunctionObject("SIGNAL-UNIFICATION-CLASH", "(DEFUN SIGNAL-UNIFICATION-CLASH ((PROP PROPOSITION) (TERM1 OBJECT) (TERM2 OBJECT)))", ((cpp_function_code)(&signalUnificationClash)), NULL);
    defineFunctionObject("SIGNAL-VARIABLE-VALUE-CLASH", "(DEFUN SIGNAL-VARIABLE-VALUE-CLASH ((PROP PROPOSITION) (SKOLEM SKOLEM) (VALUE1 OBJECT) (VALUE2 OBJECT)))", ((cpp_function_code)(&signalVariableValueClash)), NULL);
    defineFunctionObject("SIGNAL-TRUTH-VALUE-CLASH", "(DEFUN SIGNAL-TRUTH-VALUE-CLASH ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&signalTruthValueClash)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT PROPOSITION CLASH-EXCEPTIONS :TYPE (CONS OF EXCEPTION-RECORD) :DEFAULT NIL :DOCUMENTATION \"Stores a set of clash exception records that occurred for a\nparticular 'inchoherent' proposition.\" :ALLOCATION :DYNAMIC)");
    defineFunctionObject("GET-VISIBLE-CLASH-EXCEPTIONS", "(DEFUN (GET-VISIBLE-CLASH-EXCEPTIONS (CONS OF EXCEPTION-RECORD)) ((INCOHERENTPROP PROPOSITION)) :DOCUMENTATION \"Return the set of clash exceptions for 'incoherentProp' that are visible from the\ncurrent context.  These are recorded most-recent first in order of occurrance.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getVisibleClashExceptions)), NULL);
  }
}

void helpStartupPropositions10() {
  {
    defineFunctionObject("HANDLE-CLASH-EXCEPTION", "(DEFUN HANDLE-CLASH-EXCEPTION ((CLASHEXCEPTION CLASH)))", ((cpp_function_code)(&handleClashException)), NULL);
    defineFunctionObject("LOGICAL-TYPE", "(DEFUN (LOGICAL-TYPE TYPE) ((SELF OBJECT)))", ((cpp_function_code)(&logicalType)), NULL);
    defineFunctionObject("SAFE-LOGICAL-TYPE", "(DEFUN (SAFE-LOGICAL-TYPE TYPE) ((SELF OBJECT)))", ((cpp_function_code)(&safeLogicalType)), NULL);
    defineFunctionObject("CLASS-LOGICAL-TYPE", "(DEFUN (CLASS-LOGICAL-TYPE TYPE) ((SELF CLASS)))", ((cpp_function_code)(&classLogicalType)), NULL);
    defineFunctionObject("UNIFY-TYPES", "(DEFUN UNIFY-TYPES ((PROP PROPOSITION) (TERM1 SKOLEM) (TERM2 OBJECT)))", ((cpp_function_code)(&unifyTypes)), NULL);
    defineFunctionObject("UNIFY-SKOLEM-AND-VALUE", "(DEFUN UNIFY-SKOLEM-AND-VALUE ((SKOLEM SKOLEM) (VALUE OBJECT)))", ((cpp_function_code)(&unifySkolemAndValue)), NULL);
    defineFunctionObject("VERIFY-SKOLEM-AND-VALUE-TYPES", "(DEFUN VERIFY-SKOLEM-AND-VALUE-TYPES ((FROMSKOLEM SKOLEM) (TOVALUE OBJECT)))", ((cpp_function_code)(&verifySkolemAndValueTypes)), NULL);
    defineFunctionObject("SKOLEM-WITH-VARIABLE-VALUE-CYCLE?", "(DEFUN (SKOLEM-WITH-VARIABLE-VALUE-CYCLE? BOOLEAN) ((SELF OBJECT)))", ((cpp_function_code)(&skolemWithVariableValueCycleP)), NULL);
    defineFunctionObject("SYNCHRONIZE-VARIABLE-VALUE-INFERENCE-CACHES", "(DEFUN SYNCHRONIZE-VARIABLE-VALUE-INFERENCE-CACHES ((FROMSKOLEM SKOLEM) (TOVALUE SKOLEM)))", ((cpp_function_code)(&synchronizeVariableValueInferenceCaches)), NULL);
    defineFunctionObject("BIND-SKOLEM-TO-VALUE", "(DEFUN BIND-SKOLEM-TO-VALUE ((FROMSKOLEM SKOLEM) (TOVALUE OBJECT) (TOPLEVELUPDATE? BOOLEAN)))", ((cpp_function_code)(&bindSkolemToValue)), NULL);
    defineFunctionObject("UNBIND-SKOLEM-VALUE", "(DEFUN UNBIND-SKOLEM-VALUE ((SKOLEM SKOLEM) (TOPLEVELUPDATE? BOOLEAN)))", ((cpp_function_code)(&unbindSkolemValue)), NULL);
    defineFunctionObject("HAS-EQUIVALENT-VALUES?", "(DEFUN (HAS-EQUIVALENT-VALUES? BOOLEAN) ((TERM OBJECT)))", ((cpp_function_code)(&hasEquivalentValuesP)), NULL);
    defineFunctionObject("GET-VARIABLE-VALUE-INVERSES", "(DEFUN (GET-VARIABLE-VALUE-INVERSES CONS) ((TERM OBJECT)))", ((cpp_function_code)(&getVariableValueInverses)), NULL);
    defineFunctionObject("GET-ALL-VARIABLE-VALUE-INVERSES", "(DEFUN (GET-ALL-VARIABLE-VALUE-INVERSES CONS) ((TERM OBJECT)))", ((cpp_function_code)(&getAllVariableValueInverses)), NULL);
    defineFunctionObject("GET-ALL-EQUIVALENT-VALUES", "(DEFUN (GET-ALL-EQUIVALENT-VALUES CONS) ((TERM OBJECT)))", ((cpp_function_code)(&getAllEquivalentValues)), NULL);
    defineFunctionObject("CONSTRAIN-AS-SUBSET", "(DEFUN CONSTRAIN-AS-SUBSET ((PROP PROPOSITION) (SET1 COLLECTION) (SET2 COLLECTION)))", ((cpp_function_code)(&constrainAsSubset)), NULL);
    defineFunctionObject("EQUATE-COLLECTIONS", "(DEFUN EQUATE-COLLECTIONS ((PROP PROPOSITION) (COL1 COLLECTION) (COL2 COLLECTION)))", ((cpp_function_code)(&equateCollections)), NULL);
    defineFunctionObject("LOGIC-COLLECTION?", "(DEFUN (LOGIC-COLLECTION? BOOLEAN) ((TERM OBJECT)))", ((cpp_function_code)(&logicCollectionP)), NULL);
    defineFunctionObject("EQUATE-VALUES", "(DEFUN EQUATE-VALUES ((PROP PROPOSITION) (TERM1 OBJECT) (TERM2 OBJECT)))", ((cpp_function_code)(&equateValues)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT SKOLEM CONFLICTING-DEFAULT-VALUES :TYPE (CONS OF PROPOSITION) :DEFAULT NIL :ALLOCATION :DYNAMIC)");
    defineFunctionObject("UNEQUATE-CONFLICTING-DEFAULT-VALUES?", "(DEFUN (UNEQUATE-CONFLICTING-DEFAULT-VALUES? BOOLEAN) ((NEWEQUATINGPROP PROPOSITION)))", ((cpp_function_code)(&unequateConflictingDefaultValuesP)), NULL);
    defineFunctionObject("UNEQUATE-VALUES?", "(DEFUN (UNEQUATE-VALUES? BOOLEAN) ((TERM1 OBJECT) (TERM2 OBJECT)))", ((cpp_function_code)(&unequateValuesP)), NULL);
    defineFunctionObject("BIND-TO-EQUIVALENT-VALUE", "(DEFUN BIND-TO-EQUIVALENT-VALUE ((FROM LOGIC-OBJECT) (TO DESCRIPTION)))", ((cpp_function_code)(&bindToEquivalentValue)), NULL);
    defineFunctionObject("UNBIND-EQUIVALENT-VALUE", "(DEFUN UNBIND-EQUIVALENT-VALUE ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&unbindEquivalentValue)), NULL);
    defineFunctionObject("UNLINK-EQUIVALENT-VALUE", "(DEFUN UNLINK-EQUIVALENT-VALUE ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&unlinkEquivalentValue)), NULL);
    defineFunctionObject("EQUIVALENT-COLLECTION-PRIORITY", "(DEFUN (EQUIVALENT-COLLECTION-PRIORITY INTEGER) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&equivalentCollectionPriority)), NULL);
    defineFunctionObject("EQUIVALENCE-COLLECTIONS", "(DEFUN EQUIVALENCE-COLLECTIONS ((COLLECTION1 LOGIC-OBJECT) (COLLECTION2 LOGIC-OBJECT)))", ((cpp_function_code)(&equivalenceCollections)), NULL);
    defineFunctionObject("REVISE-EQUIVALENCES", "(DEFUN REVISE-EQUIVALENCES ((PROPOSITION PROPOSITION) (GOESTRUE? BOOLEAN)))", ((cpp_function_code)(&reviseEquivalences)), NULL);
    defineFunctionObject("FIND-EQUATING-PROPOSITION", "(DEFUN (FIND-EQUATING-PROPOSITION PROPOSITION) ((DIRECTOBJECT OBJECT) (INDIRECTOBJECT LOGIC-OBJECT)))", ((cpp_function_code)(&findEquatingProposition)), NULL);
    defineFunctionObject("CONSTANT-PROPOSITION?", "(DEFUN (CONSTANT-PROPOSITION? BOOLEAN) ((SELF PROPOSITION)) :DOCUMENTATION \"Return true if `self' is a constant such as TRUE or FALSE.\" :PUBLIC? TRUE)", ((cpp_function_code)(&constantPropositionP)), NULL);
    defineFunctionObject("EVALUATE-TERM", "(DEFUN (EVALUATE-TERM OBJECT) ((SELF OBJECT)))", ((cpp_function_code)(&evaluateTerm)), NULL);
    defineFunctionObject("EVALUATE-LITERAL-WRAPPER-TERM", "(DEFUN (EVALUATE-LITERAL-WRAPPER-TERM OBJECT) ((SELF LITERAL-WRAPPER)))", ((cpp_function_code)(&evaluateLiteralWrapperTerm)), NULL);
    defineFunctionObject("EVALUATE-SURROGATE-TERM", "(DEFUN (EVALUATE-SURROGATE-TERM OBJECT) ((SELF SURROGATE)))", ((cpp_function_code)(&evaluateSurrogateTerm)), NULL);
    defineFunctionObject("EVALUATE-LOGIC-OBJECT-TERM", "(DEFUN (EVALUATE-LOGIC-OBJECT-TERM OBJECT) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&evaluateLogicObjectTerm)), NULL);
    defineFunctionObject("ANONYMOUS-VARIABLE?", "(DEFUN (ANONYMOUS-VARIABLE? BOOLEAN) ((SELF SKOLEM)))", ((cpp_function_code)(&anonymousVariableP)), NULL);
    defineFunctionObject("EVALUATE-SYMBOL-TERM", "(DEFUN (EVALUATE-SYMBOL-TERM OBJECT) ((SELF SYMBOL)))", ((cpp_function_code)(&evaluateSymbolTerm)), NULL);
    defineFunctionObject("EVALUATE-AUTOMATIC-INSTANCE", "(DEFUN (EVALUATE-AUTOMATIC-INSTANCE OBJECT) ((NAME SYMBOL)))", ((cpp_function_code)(&evaluateAutomaticInstance)), NULL);
    defineFunctionObject("SIGNAL-UNDEFINED-TERM", "(DEFUN SIGNAL-UNDEFINED-TERM ((TERM OBJECT)))", ((cpp_function_code)(&signalUndefinedTerm)), NULL);
    defineFunctionObject("SIGNAL-UNTYPED-TERM", "(DEFUN SIGNAL-UNTYPED-TERM ((TERM OBJECT)))", ((cpp_function_code)(&signalUntypedTerm)), NULL);
    defineFunctionObject("EVALUATE-CREATE-TERM", "(DEFUN (EVALUATE-CREATE-TERM OBJECT) ((TERM CONS)))", ((cpp_function_code)(&evaluateCreateTerm)), NULL);
    defineFunctionObject("CREATE", "(DEFUN (CREATE OBJECT) ((NAME GENERALIZED-SYMBOL) |&REST| (TYPE GENERALIZED-SYMBOL)) :DOCUMENTATION \"Create a logic object with name 'name' and return it.\nIf `type' is also supplied, assert that the object belongs to that type.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&create)), ((cpp_function_code)(&createEvaluatorWrapper)));
    defineFunctionObject("UPDATE-SKOLEM-TYPE", "(DEFUN UPDATE-SKOLEM-TYPE ((SELF SKOLEM) (TYPE TYPE)))", ((cpp_function_code)(&updateSkolemType)), NULL);
    defineFunctionObject("UPDATE-SKOLEM-TYPE-FROM-ISA-ASSERTIONS", "(DEFUN UPDATE-SKOLEM-TYPE-FROM-ISA-ASSERTIONS ((SELF PROPOSITION)))", ((cpp_function_code)(&updateSkolemTypeFromIsaAssertions)), NULL);
    defineFunctionObject("DESCRIPTION-EXTENSION<", "(DEFUN (DESCRIPTION-EXTENSION< BOOLEAN) ((DESC1 DESCRIPTION) (DESC2 DESCRIPTION)))", ((cpp_function_code)(&descriptionExtensionL)), NULL);
    defineFunctionObject("PRINT-EXTENSION-SIZES", "(DEFUN PRINT-EXTENSION-SIZES ((MODULE MODULE) (SIZECUTOFF INTEGER)) :DOCUMENTATION \"Print the extension sizes of concepts visible in `module'.\nIf `module' is NULL the current module is used.  Do not report extensions\nwith size less than `sizeCutoff' (default is 10).\" :PUBLIC? TRUE)", ((cpp_function_code)(&printExtensionSizes)), NULL);
    defineFunctionObject("TRANSFER-LOGIC-INFORMATION-FROM-RELATION-HOOK", "(DEFUN TRANSFER-LOGIC-INFORMATION-FROM-RELATION-HOOK ((RELATIONSLIST (LIST OF RELATION))))", ((cpp_function_code)(&transferLogicInformationFromRelationHook)), NULL);
    defineFunctionObject("RETRACT-RELATION-AXIOMS", "(DEFUN RETRACT-RELATION-AXIOMS ((OLDRELATION NAMED-DESCRIPTION)))", ((cpp_function_code)(&retractRelationAxioms)), NULL);
    defineFunctionObject("ASSERT-DESCRIPTION-IMPLIES-DESCRIPTION", "(DEFUN (ASSERT-DESCRIPTION-IMPLIES-DESCRIPTION PROPOSITION) ((SUB DESCRIPTION) (SUPER DESCRIPTION) (DONTUPDATE? BOOLEAN)))", ((cpp_function_code)(&assertDescriptionImpliesDescription)), NULL);
    defineFunctionObject("ASSERT-IMPLIES-LINK-BETWEEN-RELATIONS", "(DEFUN (ASSERT-IMPLIES-LINK-BETWEEN-RELATIONS PROPOSITION) ((SUB NAMED-DESCRIPTION) (SUPER NAMED-DESCRIPTION)))", ((cpp_function_code)(&assertImpliesLinkBetweenRelations)), NULL);
    defineFunctionObject("FINALIZE-SUPERRELATION-LINKS", "(DEFUN FINALIZE-SUPERRELATION-LINKS ((SELF RELATION)))", ((cpp_function_code)(&finalizeSuperrelationLinks)), NULL);
    defineFunctionObject("UPDATE-ISA-PROPOSITION", "(DEFUN (UPDATE-ISA-PROPOSITION PROPOSITION) ((SELF OBJECT) (TYPE TYPE) (UPDATEMODE KEYWORD)) :PUBLIC? TRUE)", ((cpp_function_code)(&updateIsaProposition)), NULL);
    defineFunctionObject("ASSERT-ISA-PROPOSITION", "(DEFUN (ASSERT-ISA-PROPOSITION PROPOSITION) ((SELF OBJECT) (TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&assertIsaProposition)), NULL);
    defineFunctionObject("RETRACT-ISA-PROPOSITION", "(DEFUN (RETRACT-ISA-PROPOSITION PROPOSITION) ((SELF OBJECT) (TYPE TYPE)) :PUBLIC? TRUE)", ((cpp_function_code)(&retractIsaProposition)), NULL);
    defineFunctionObject("UPDATE-PROPERTY", "(DEFUN (UPDATE-PROPERTY PROPOSITION) ((SELF LOGIC-OBJECT) (SURROGATE SURROGATE) (UPDATEMODE KEYWORD)) :PUBLIC? TRUE)", ((cpp_function_code)(&updateProperty)), NULL);
    defineFunctionObject("ASSERT-PROPERTY", "(DEFUN (ASSERT-PROPERTY PROPOSITION) ((INSTANCE LOGIC-OBJECT) (PROPERTY SURROGATE)) :PUBLIC? TRUE)", ((cpp_function_code)(&assertProperty)), NULL);
    defineFunctionObject("RETRACT-PROPERTY", "(DEFUN (RETRACT-PROPERTY PROPOSITION) ((INSTANCE LOGIC-OBJECT) (PROPERTY SURROGATE)) :PUBLIC? TRUE)", ((cpp_function_code)(&retractProperty)), NULL);
    defineFunctionObject("UPDATE-TUPLE", "(DEFUN (UPDATE-TUPLE PROPOSITION) ((RELATION SURROGATE) (ARGUMENTS (CONS OF OBJECT)) (UPDATEMODE KEYWORD)) :DOCUMENTATION \"Assert or retract a proposition that applies 'relation' to 'arguments'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&updateTuple)), NULL);
    defineFunctionObject("ASSERT-TUPLE", "(DEFUN (ASSERT-TUPLE PROPOSITION) ((RELATION SURROGATE) (ARGUMENTS (CONS OF OBJECT))) :PUBLIC? TRUE)", ((cpp_function_code)(&assertTuple)), NULL);
    defineFunctionObject("UPDATE-BINARY-VALUE", "(DEFUN (UPDATE-BINARY-VALUE PROPOSITION) ((RELATION SURROGATE) (SELF OBJECT) (VALUE OBJECT) (UPDATEMODE KEYWORD)) :PUBLIC? TRUE)", ((cpp_function_code)(&updateBinaryValue)), NULL);
    defineFunctionObject("ASSERT-BINARY-VALUE", "(DEFUN (ASSERT-BINARY-VALUE PROPOSITION) ((RELATION SURROGATE) (SELF OBJECT) (VALUE OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&assertBinaryValue)), NULL);
  }
}

void helpStartupPropositions11() {
  {
    defineFunctionObject("RETRACT-BINARY-VALUE", "(DEFUN (RETRACT-BINARY-VALUE PROPOSITION) ((RELATION SURROGATE) (SELF OBJECT) (VALUE OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&retractBinaryValue)), NULL);
    defineFunctionObject("ASSERT-MEMBER-OF-PROPOSITION", "(DEFUN (ASSERT-MEMBER-OF-PROPOSITION PROPOSITION) ((SELF OBJECT) (COLLECTION OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&assertMemberOfProposition)), NULL);
    defineFunctionObject("HELP-CREATE-LOGIC-INSTANCE", "(DEFUN (HELP-CREATE-LOGIC-INSTANCE OBJECT) ((NAME SURROGATE) (TYPE SURROGATE)) :PUBLIC? TRUE)", ((cpp_function_code)(&helpCreateLogicInstance)), NULL);
    defineFunctionObject("CREATE-LOGIC-INSTANCE", "(DEFUN (CREATE-LOGIC-INSTANCE OBJECT) ((NAME SURROGATE) (TYPE SURROGATE)) :PUBLIC? TRUE)", ((cpp_function_code)(&createLogicInstance)), NULL);
    defineFunctionObject("CLEANUP-STRUCTURED-OBJECTS-INDEX", "(DEFUN CLEANUP-STRUCTURED-OBJECTS-INDEX ((CLEARMODULE MODULE)))", ((cpp_function_code)(&cleanupStructuredObjectsIndex)), NULL);
    defineFunctionObject("PROPOSITION-HASH-INDEX", "(DEFUN (PROPOSITION-HASH-INDEX INTEGER) ((SELF PROPOSITION) (MAPPING ENTITY-MAPPING) (DEREFSURROGATES? BOOLEAN)))", ((cpp_function_code)(&propositionHashIndex)), NULL);
    defineFunctionObject("LOOKUP-MATCHING-PROPOSITION-IN-BUCKET", "(DEFUN (LOOKUP-MATCHING-PROPOSITION-IN-BUCKET PROPOSITION) ((BUCKET LIST) (SELF PROPOSITION) (MAPPING ENTITY-MAPPING)))", ((cpp_function_code)(&lookupMatchingPropositionInBucket)), NULL);
    defineFunctionObject("FIND-DUPLICATE-COMPLEX-PROPOSITION", "(DEFUN (FIND-DUPLICATE-COMPLEX-PROPOSITION PROPOSITION) ((SELF PROPOSITION)))", ((cpp_function_code)(&findDuplicateComplexProposition)), NULL);
    defineFunctionObject("FIND-DUPLICATE-PROPOSITION", "(DEFUN (FIND-DUPLICATE-PROPOSITION PROPOSITION) ((SELF PROPOSITION)))", ((cpp_function_code)(&findDuplicateProposition)), NULL);
    defineFunctionObject("FIND-MATCHING-NON-DESCRIPTIVE-PROPOSITION", "(DEFUN (FIND-MATCHING-NON-DESCRIPTIVE-PROPOSITION PROPOSITION) ((SELF PROPOSITION) (MAPPING ENTITY-MAPPING)))", ((cpp_function_code)(&findMatchingNonDescriptiveProposition)), NULL);
    defineFunctionObject("FASTEN-DOWN-ONE-PROPOSITION", "(DEFUN (FASTEN-DOWN-ONE-PROPOSITION PROPOSITION) ((SELF PROPOSITION) (DONTCHECKFORDUPLICATES? BOOLEAN)))", ((cpp_function_code)(&fastenDownOneProposition)), NULL);
    defineFunctionObject("HELP-FASTEN-DOWN-PROPOSITIONS", "(DEFUN (HELP-FASTEN-DOWN-PROPOSITIONS PROPOSITION) ((SELF PROPOSITION) (DONTCHECKFORDUPLICATES? BOOLEAN)))", ((cpp_function_code)(&helpFastenDownPropositions)), NULL);
    defineFunctionObject("RECURSIVELY-FASTEN-DOWN-PROPOSITIONS", "(DEFUN (RECURSIVELY-FASTEN-DOWN-PROPOSITIONS PROPOSITION) ((SELF PROPOSITION) (DONTCHECKFORDUPLICATES? BOOLEAN)))", ((cpp_function_code)(&recursivelyFastenDownPropositions)), NULL);
    defineFunctionObject("UNFASTEN-PROPOSITION", "(DEFUN UNFASTEN-PROPOSITION ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&unfastenProposition)), NULL);
    defineFunctionObject("INSTANTIATE-UNDEFINED-SURROGATES", "(DEFUN INSTANTIATE-UNDEFINED-SURROGATES ((SELF PROPOSITION)))", ((cpp_function_code)(&instantiateUndefinedSurrogates)), NULL);
    defineFunctionObject("BUILD-TOP-LEVEL-PROPOSITION", "(DEFUN (BUILD-TOP-LEVEL-PROPOSITION PROPOSITION) ((TREE OBJECT) (TRUEASSERTION? BOOLEAN)))", ((cpp_function_code)(&buildTopLevelProposition)), NULL);
    defineFunctionObject("BUILD-PROPOSITION", "(DEFUN (BUILD-PROPOSITION OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&buildProposition)), NULL);
    defineFunctionObject("SURROGATE.BUILD-PROPOSITION", "(DEFUN (SURROGATE.BUILD-PROPOSITION PROPOSITION) ((SELF SURROGATE)))", ((cpp_function_code)(&surrogateDbuildProposition)), NULL);
    defineFunctionObject("SYMBOL.BUILD-PROPOSITION", "(DEFUN (SYMBOL.BUILD-PROPOSITION OBJECT) ((SYMBOL SYMBOL)))", ((cpp_function_code)(&symbolDbuildProposition)), NULL);
    defineFunctionObject("CONS.BUILD-PROPOSITION", "(DEFUN (CONS.BUILD-PROPOSITION PROPOSITION) ((TREE CONS)))", ((cpp_function_code)(&consDbuildProposition)), NULL);
    defineFunctionObject("VERIFY-NUMBER-OF-PROPOSITION-ARGUMENTS", "(DEFUN VERIFY-NUMBER-OF-PROPOSITION-ARGUMENTS ((TREE CONS) (CORRECTNUMBER INTEGER)))", ((cpp_function_code)(&verifyNumberOfPropositionArguments)), NULL);
    defineMethodObject("(DEFMETHOD (DESCRIPTION-SURROGATE TYPE) ((SELF DESCRIPTION)))", wrapMethodCode(((cpp_method_code)(&Description::descriptionSurrogate))), NULL);
    defineFunctionObject("BUILD-ISA-PROPOSITION", "(DEFUN (BUILD-ISA-PROPOSITION PROPOSITION) ((TREE CONS)))", ((cpp_function_code)(&buildIsaProposition)), NULL);
    defineFunctionObject("BUILD-MEMBER-OF-PROPOSITION", "(DEFUN (BUILD-MEMBER-OF-PROPOSITION PROPOSITION) ((TREE CONS)))", ((cpp_function_code)(&buildMemberOfProposition)), NULL);
    defineFunctionObject("MEMBER-OF-PROPOSITION?", "(DEFUN (MEMBER-OF-PROPOSITION? BOOLEAN) ((PROPOSITION PROPOSITION)) :GLOBALLY-INLINE? TRUE (RETURN (EQL? (OPERATOR PROPOSITION) /PL-KERNEL-KB/@MEMBER-OF)))", ((cpp_function_code)(&memberOfPropositionP)), NULL);
    defineFunctionObject("SUBSET-OF-PROPOSITION?", "(DEFUN (SUBSET-OF-PROPOSITION? BOOLEAN) ((PROPOSITION PROPOSITION)) :GLOBALLY-INLINE? TRUE (RETURN (EQL? (OPERATOR PROPOSITION) /PL-KERNEL-KB/@SUBSET-OF)))", ((cpp_function_code)(&subsetOfPropositionP)), NULL);
    defineFunctionObject("SIMPLE-SUBRELATION-PROPOSITION?", "(DEFUN (SIMPLE-SUBRELATION-PROPOSITION? BOOLEAN) ((PROPOSITION PROPOSITION)) :PUBLIC? TRUE)", ((cpp_function_code)(&simpleSubrelationPropositionP)), NULL);
    defineFunctionObject("EXTRACT-ANNOTATION", "(DEFUN (EXTRACT-ANNOTATION OBJECT OBJECT) ((TREE OBJECT) (OPTION KEYWORD)))", ((cpp_function_code)(&extractAnnotation)), NULL);
    defineFunctionObject("LOOKUP-ANNOTATION", "(DEFUN (LOOKUP-ANNOTATION OBJECT) ((PROPOSITION PROPOSITION) (KEY KEYWORD)))", ((cpp_function_code)(&lookupAnnotation)), NULL);
    defineFunctionObject("INSERT-ANNOTATION", "(DEFUN INSERT-ANNOTATION ((PROPOSITION PROPOSITION) (KEY KEYWORD) (VALUE OBJECT)))", ((cpp_function_code)(&insertAnnotation)), NULL);
    defineFunctionObject("REMOVE-ANNOTATION", "(DEFUN REMOVE-ANNOTATION ((PROPOSITION PROPOSITION) (KEY KEYWORD)))", ((cpp_function_code)(&removeAnnotation)), NULL);
    defineFunctionObject("BUILD-ANNOTATED-PROPOSITION", "(DEFUN (BUILD-ANNOTATED-PROPOSITION PROPOSITION) ((TREE CONS)))", ((cpp_function_code)(&buildAnnotatedProposition)), NULL);
    defineFunctionObject("FINALIZE-PROPOSITION-ANNOTATIONS", "(DEFUN FINALIZE-PROPOSITION-ANNOTATIONS ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&finalizePropositionAnnotations)), NULL);
    defineFunctionObject("CLEAR-PROPOSITION-ANNOTATIONS", "(DEFUN CLEAR-PROPOSITION-ANNOTATIONS ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&clearPropositionAnnotations)), NULL);
    defineFunctionObject("FORWARD-BACKWARD-OPTION-HANDLER", "(DEFUN FORWARD-BACKWARD-OPTION-HANDLER ((SELF PROPOSITION) (SLOT STORAGE-SLOT) (TREE OBJECT)))", ((cpp_function_code)(&forwardBackwardOptionHandler)), NULL);
    defineFunctionObject("INHERIT-PROPOSITION-ANNOTATIONS", "(DEFUN INHERIT-PROPOSITION-ANNOTATIONS ((ANNOTATIONS PROPERTY-LIST) (TO PROPOSITION)))", ((cpp_function_code)(&inheritPropositionAnnotations)), NULL);
    defineFunctionObject("FUNCTION-INDUCED-EXISTS?", "(DEFUN (FUNCTION-INDUCED-EXISTS? BOOLEAN) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&functionInducedExistsP)), NULL);
    defineFunctionObject("PREDICATE-OF-FUNCTION-INDUCED-EXISTS", "(DEFUN (PREDICATE-OF-FUNCTION-INDUCED-EXISTS PROPOSITION) ((EXISTSPROPOSITION PROPOSITION)))", ((cpp_function_code)(&predicateOfFunctionInducedExists)), NULL);
    defineFunctionObject("EMBED-NEGATION-WITHIN-FUNCTION-INDUCED-EXISTS", "(DEFUN (EMBED-NEGATION-WITHIN-FUNCTION-INDUCED-EXISTS PROPOSITION) ((EXISTSPROPOSITION PROPOSITION)))", ((cpp_function_code)(&embedNegationWithinFunctionInducedExists)), NULL);
    defineFunctionObject("BUILD-AND-OR-NOT-PROPOSITION", "(DEFUN (BUILD-AND-OR-NOT-PROPOSITION PROPOSITION) ((TREE CONS)))", ((cpp_function_code)(&buildAndOrNotProposition)), NULL);
    defineFunctionObject("CONCEIVE-INVERTED-PROPOSITION", "(DEFUN (CONCEIVE-INVERTED-PROPOSITION PROPOSITION) ((PROP PROPOSITION)) :DOCUMENTATION \"Return the simplest inversion of `prop', trying to reuse existing\nnegations or negated arguments of `prop' if possible.\" :PUBLIC? TRUE)", ((cpp_function_code)(&conceiveInvertedProposition)), NULL);
    defineFunctionObject("FUNCTIONAL-TERM?", "(DEFUN (FUNCTIONAL-TERM? BOOLEAN) ((TERM OBJECT)))", ((cpp_function_code)(&functionalTermP)), NULL);
    defineFunctionObject("CLIP-VALUE?", "(DEFUN (CLIP-VALUE? BOOLEAN) ((TERM1 OBJECT) (TERM2 OBJECT)))", ((cpp_function_code)(&clipValueP)), NULL);
    defineFunctionObject("CREATE-EQUIVALENCE-PROPOSITION", "(DEFUN (CREATE-EQUIVALENCE-PROPOSITION PROPOSITION) ((TERM1 OBJECT) (TERM2 OBJECT)))", ((cpp_function_code)(&createEquivalenceProposition)), NULL);
    defineFunctionObject("BUILD-EQUIVALENCE-PROPOSITION", "(DEFUN (BUILD-EQUIVALENCE-PROPOSITION PROPOSITION) ((TREE CONS)))", ((cpp_function_code)(&buildEquivalenceProposition)), NULL);
    defineFunctionObject("BUILD-CONJUNCTION-OF-EQUALITY-PROPOSITIONS", "(DEFUN (BUILD-CONJUNCTION-OF-EQUALITY-PROPOSITIONS PROPOSITION) ((REMAININGTERMS CONS) (EQUIVALENCES (CONS OF PROPOSITION))))", ((cpp_function_code)(&buildConjunctionOfEqualityPropositions)), NULL);
    defineFunctionObject("BUILD-FAIL-PROPOSITION", "(DEFUN (BUILD-FAIL-PROPOSITION PROPOSITION) ((TREE CONS)))", ((cpp_function_code)(&buildFailProposition)), NULL);
    defineFunctionObject("BUILD-COLLECT-INTO-PROPOSITION", "(DEFUN (BUILD-COLLECT-INTO-PROPOSITION PROPOSITION) ((TREE CONS)))", ((cpp_function_code)(&buildCollectIntoProposition)), NULL);
    defineFunctionObject("HOLDS-OPERATOR?", "(DEFUN (HOLDS-OPERATOR? BOOLEAN) ((OPERATOR OBJECT)))", ((cpp_function_code)(&holdsOperatorP)), NULL);
    defineFunctionObject("VERIFY-EVALUABLE-OPERATOR", "(DEFUN VERIFY-EVALUABLE-OPERATOR ((OPERATOR OBJECT) (KIND KEYWORD)))", ((cpp_function_code)(&verifyEvaluableOperator)), NULL);
    defineFunctionObject("BUILD-HOLDS-PROPOSITION", "(DEFUN (BUILD-HOLDS-PROPOSITION PROPOSITION) ((TREE CONS)))", ((cpp_function_code)(&buildHoldsProposition)), NULL);
    defineFunctionObject("MOST-GENERAL-EQUIVALENT-SLOTREF", "(DEFUN (MOST-GENERAL-EQUIVALENT-SLOTREF SURROGATE) ((SURROGATE SURROGATE)))", ((cpp_function_code)(&mostGeneralEquivalentSlotref)), NULL);
    defineFunctionObject("POLYMORPHIC-RELATION?", "(DEFUN (POLYMORPHIC-RELATION? BOOLEAN) ((SELF RELATION)))", ((cpp_function_code)(&polymorphicRelationP)), NULL);
    defineFunctionObject("NON-POLYMORPHIC-PREDICATE?", "(DEFUN (NON-POLYMORPHIC-PREDICATE? BOOLEAN) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&nonPolymorphicPredicateP)), NULL);
    defineFunctionObject("EVALUATE-PREDICATE", "(DEFUN (EVALUATE-PREDICATE LOGIC-OBJECT) ((NAME GENERALIZED-SYMBOL) (FIRSTARGUMENT OBJECT)))", ((cpp_function_code)(&evaluatePredicate)), NULL);
    defineFunctionObject("PROPOSITIONAL-ARGUMENT?", "(DEFUN (PROPOSITIONAL-ARGUMENT? BOOLEAN) ((ARGUMENT OBJECT)))", ((cpp_function_code)(&propositionalArgumentP)), NULL);
    defineFunctionObject("EVALUATE-TYPED-ARGUMENT", "(DEFUN (EVALUATE-TYPED-ARGUMENT OBJECT) ((ARGUMENT OBJECT) (TYPE SURROGATE)))", ((cpp_function_code)(&evaluateTypedArgument)), NULL);
    defineFunctionObject("EVALUATE-PROPOSITION-TERM", "(DEFUN (EVALUATE-PROPOSITION-TERM OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&evaluatePropositionTerm)), NULL);
    defineFunctionObject("EVALUATE-PREDICATE-AND-FIRST-ARGUMENT", "(DEFUN (EVALUATE-PREDICATE-AND-FIRST-ARGUMENT LOGIC-OBJECT OBJECT) ((TREE CONS)))", ((cpp_function_code)(&evaluatePredicateAndFirstArgument)), NULL);
    defineFunctionObject("EVALUATE-FIRST-ARGUMENT", "(DEFUN (EVALUATE-FIRST-ARGUMENT OBJECT) ((ARGUMENT OBJECT) (RELATIONNAME SYMBOL)))", ((cpp_function_code)(&evaluateFirstArgument)), NULL);
  }
}

void helpStartupPropositions12() {
  {
    defineFunctionObject("EVALUATE-REMAINING-ARGUMENTS", "(DEFUN (EVALUATE-REMAINING-ARGUMENTS CONS) ((PREDICATEVALUE LOGIC-OBJECT) (ARGUMENTS CONS)))", ((cpp_function_code)(&evaluateRemainingArguments)), NULL);
    defineFunctionObject("CLASS-OPERATOR?", "(DEFUN (CLASS-OPERATOR? BOOLEAN) ((OPERATOR GENERALIZED-SYMBOL)))", ((cpp_function_code)(&classOperatorP)), NULL);
    defineFunctionObject("BUILD-PREDICATE-PROPOSITION", "(DEFUN (BUILD-PREDICATE-PROPOSITION PROPOSITION) ((TREE CONS)))", ((cpp_function_code)(&buildPredicateProposition)), NULL);
    defineFunctionObject("CHECK-STRICT-TYPE?", "(DEFUN (CHECK-STRICT-TYPE? BOOLEAN) ((SELF OBJECT) (TYPE SURROGATE) (SHALLOW? BOOLEAN)))", ((cpp_function_code)(&checkStrictTypeP)), NULL);
    defineFunctionObject("CHECK-TYPE?", "(DEFUN (CHECK-TYPE? BOOLEAN) ((SELF OBJECT) (TYPE SURROGATE) (SHALLOW? BOOLEAN)) :GLOBALLY-INLINE? TRUE (RETURN (OR (PARTIAL-MATCH-MODE?) (CHECK-STRICT-TYPE? SELF TYPE SHALLOW?))))", ((cpp_function_code)(&checkTypeP)), NULL);
    defineFunctionObject("CHECK-COERCED-TYPE?", "(DEFUN (CHECK-COERCED-TYPE? BOOLEAN OBJECT) ((SELF OBJECT) (TYPE SURROGATE) (SHALLOW? BOOLEAN)))", ((cpp_function_code)(&checkCoercedTypeP)), NULL);
    defineFunctionObject("COERCE-INCOMPATIBLE-VALUE", "(DEFUN (COERCE-INCOMPATIBLE-VALUE OBJECT) ((VALUE OBJECT) (TYPE SURROGATE)))", ((cpp_function_code)(&coerceIncompatibleValue)), NULL);
    defineFunctionObject("COERCE-QUANTITY", "(DEFUN (COERCE-QUANTITY OBJECT) ((VALUE OBJECT) (QUANTITYTYPEREF SURROGATE)))", ((cpp_function_code)(&coerceQuantity)), NULL);
    defineFunctionObject("COERCE-DATE", "(DEFUN (COERCE-DATE OBJECT) ((VALUE OBJECT) (DATETYPEREF SURROGATE)))", ((cpp_function_code)(&coerceDate)), NULL);
    defineFunctionObject("VERIFY-ONE-ARGUMENT-TYPE", "(DEFUN VERIFY-ONE-ARGUMENT-TYPE ((ARG OBJECT) (TYPE SURROGATE) (PROPOSITION PROPOSITION) (DESCRIPTION NAMED-DESCRIPTION)))", ((cpp_function_code)(&verifyOneArgumentType)), NULL);
    defineFunctionObject("VERIFY-ARGUMENT-TYPES-AND-COUNT", "(DEFUN VERIFY-ARGUMENT-TYPES-AND-COUNT ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&verifyArgumentTypesAndCount)), NULL);
    defineFunctionObject("HANDLE-ARGUMENT-TYPE-VIOLATION", "(DEFUN HANDLE-ARGUMENT-TYPE-VIOLATION ((PROPOSITION PROPOSITION) (ARG OBJECT) (REQUIREDTYPE SURROGATE)))", ((cpp_function_code)(&handleArgumentTypeViolation)), NULL);
    defineFunctionObject("HANDLE-ARITY-VIOLATION", "(DEFUN HANDLE-ARITY-VIOLATION ((PROPOSITION PROPOSITION) (REQUIREDARITY INTEGER)))", ((cpp_function_code)(&handleArityViolation)), NULL);
    defineFunctionObject("POST-TO-CHECK-TYPES-AGENDA", "(DEFUN POST-TO-CHECK-TYPES-AGENDA ((SELF PROPOSITION)))", ((cpp_function_code)(&postToCheckTypesAgenda)), NULL);
    defineFunctionObject("PROCESS-CHECK-TYPES-AGENDA", "(DEFUN PROCESS-CHECK-TYPES-AGENDA ())", ((cpp_function_code)(&processCheckTypesAgenda)), NULL);
    defineFunctionObject("PROCESS-DEFINITIONS", "(DEFUN PROCESS-DEFINITIONS () :PUBLIC? TRUE :COMMAND? TRUE :DOCUMENTATION \"Finish processing all definitions and assertions that have\nbeen evaluated/loaded since that last call to 'process-definitions'.\nPowerLoom defers complete processing of definitions to make it easier\nto support cyclic definitions.  Following finalization of definitions,\nthis call performs semantic validation of any assertions evaluated since\nthe last call to 'process-definitions'.  PowerLoom calls this function\ninternally before each query; the primary reason to call it explicitly\nis to force the production of any diagnostic information that results from\nthe processing and validation.\")", ((cpp_function_code)(&processDefinitions)), NULL);
    defineFunctionObject("BUILD-EXISTS-PROPOSITION", "(DEFUN (BUILD-EXISTS-PROPOSITION PROPOSITION) ((TREE CONS)))", ((cpp_function_code)(&buildExistsProposition)), NULL);
    defineFunctionObject("TOP-LEVEL-EXISTS-PROPOSITION?", "(DEFUN (TOP-LEVEL-EXISTS-PROPOSITION? BOOLEAN) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&topLevelExistsPropositionP)), NULL);
    defineFunctionObject("COLLECT-SKOLEMIZED-EXISTS-VARIABLES", "(DEFUN (COLLECT-SKOLEMIZED-EXISTS-VARIABLES (VECTOR OF SKOLEM)) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&collectSkolemizedExistsVariables)), NULL);
    defineFunctionObject("HELP-COLLECT-SKOLEMIZED-EXISTS-VARIABLES?", "(DEFUN (HELP-COLLECT-SKOLEMIZED-EXISTS-VARIABLES? BOOLEAN) ((PROPOSITION PROPOSITION) (RESULT (LIST OF SKOLEM))))", ((cpp_function_code)(&helpCollectSkolemizedExistsVariablesP)), NULL);
    defineFunctionObject("BUILD-FORALL-PROPOSITION", "(DEFUN (BUILD-FORALL-PROPOSITION PROPOSITION) ((TREE CONS)))", ((cpp_function_code)(&buildForallProposition)), NULL);
    defineFunctionObject("VERIFY-FORALL-PROPOSITIONS", "(DEFUN VERIFY-FORALL-PROPOSITIONS ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&verifyForallPropositions)), NULL);
    defineFunctionObject("MAYBE-SUBSTITUTE-SURROGATE-ARGUMENT", "(DEFUN (MAYBE-SUBSTITUTE-SURROGATE-ARGUMENT OBJECT) ((ARG1 OBJECT) (ARG2 OBJECT)))", ((cpp_function_code)(&maybeSubstituteSurrogateArgument)), NULL);
    defineFunctionObject("CREATE-IMPLIES-PROPOSITION", "(DEFUN (CREATE-IMPLIES-PROPOSITION PROPOSITION) ((TAIL OBJECT) (HEAD OBJECT)))", ((cpp_function_code)(&createImpliesProposition)), NULL);
    defineFunctionObject("BUILD-IMPLIES-PROPOSITION", "(DEFUN (BUILD-IMPLIES-PROPOSITION PROPOSITION) ((TREE CONS)))", ((cpp_function_code)(&buildImpliesProposition)), NULL);
    defineFunctionObject("FIND-DUPLICATE-FUNCTION-PROPOSITION", "(DEFUN (FIND-DUPLICATE-FUNCTION-PROPOSITION PROPOSITION) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&findDuplicateFunctionProposition)), NULL);
    defineFunctionObject("UNWRAP-WRAPPED-TYPE", "(DEFUN (UNWRAP-WRAPPED-TYPE TYPE) ((TYPE TYPE)))", ((cpp_function_code)(&unwrapWrappedType)), NULL);
    defineFunctionObject("BEGIN-CREATING-FUNCTION-PROPOSITION", "(DEFUN (BEGIN-CREATING-FUNCTION-PROPOSITION PROPOSITION) ((SURROGATE GENERALIZED-SYMBOL) (INPUTARGUMENTS CONS)))", ((cpp_function_code)(&beginCreatingFunctionProposition)), NULL);
    defineFunctionObject("FINISH-CREATING-FUNCTION-PROPOSITION", "(DEFUN (FINISH-CREATING-FUNCTION-PROPOSITION PROPOSITION) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&finishCreatingFunctionProposition)), NULL);
    defineFunctionObject("FIND-OR-CREATE-FUNCTION-PROPOSITION", "(DEFUN (FIND-OR-CREATE-FUNCTION-PROPOSITION PROPOSITION) ((PREDICATE GENERALIZED-SYMBOL) (INPUTARGUMENTS CONS)))", ((cpp_function_code)(&findOrCreateFunctionProposition)), NULL);
    defineFunctionObject("CREATE-FUNCTION-PROPOSITION", "(DEFUN (CREATE-FUNCTION-PROPOSITION PROPOSITION) ((PREDICATE GENERALIZED-SYMBOL) (INPUTARGUMENTS CONS)))", ((cpp_function_code)(&createFunctionProposition)), NULL);
    defineFunctionObject("EVALUATE-FUNCTION-TERM", "(DEFUN (EVALUATE-FUNCTION-TERM OBJECT) ((TREE CONS)))", ((cpp_function_code)(&evaluateFunctionTerm)), NULL);
    defineFunctionObject("EXTENSIONAL-INDIVIDUAL?", "(DEFUN (EXTENSIONAL-INDIVIDUAL? BOOLEAN) ((INDIVIDUAL OBJECT)))", ((cpp_function_code)(&extensionalIndividualP)), NULL);
    defineFunctionObject("FUNCTION-WITH-DEFINED-VALUE?", "(DEFUN (FUNCTION-WITH-DEFINED-VALUE? BOOLEAN) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&functionWithDefinedValueP)), NULL);
    defineFunctionObject("NORMALIZE-SETOF-ARGUMENTS", "(DEFUN (NORMALIZE-SETOF-ARGUMENTS CONS) ((ARGS CONS)))", ((cpp_function_code)(&normalizeSetofArguments)), NULL);
    defineFunctionObject("CREATE-ENUMERATED-SET", "(DEFUN (CREATE-ENUMERATED-SET SKOLEM) ((SET LIST)))", ((cpp_function_code)(&createEnumeratedSet)), NULL);
    defineFunctionObject("CREATE-LOGICAL-LIST", "(DEFUN (CREATE-LOGICAL-LIST SKOLEM) ((LIST LIST)))", ((cpp_function_code)(&createLogicalList)), NULL);
    defineFunctionObject("LOGICAL-COLLECTION?", "(DEFUN (LOGICAL-COLLECTION? BOOLEAN) ((SELF OBJECT)))", ((cpp_function_code)(&logicalCollectionP)), NULL);
    defineFunctionObject("FUNCTION-OUTPUT-SKOLEM?", "(DEFUN (FUNCTION-OUTPUT-SKOLEM? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&functionOutputSkolemP)), NULL);
    defineFunctionObject("SKOLEM-DEFINED-BY-OPERATOR?", "(DEFUN (SKOLEM-DEFINED-BY-OPERATOR? BOOLEAN) ((SELF OBJECT) (OPERATOR SURROGATE)) :GLOBALLY-INLINE? TRUE (TYPECASE SELF (SKOLEM (LET ((DEFININGPROPOSITION (DEFINING-PROPOSITION SELF))) (RETURN (AND (DEFINED? DEFININGPROPOSITION) (EQL? (OPERATOR DEFININGPROPOSITION) OPERATOR))))) (OTHERWISE (RETURN FALSE))))", ((cpp_function_code)(&skolemDefinedByOperatorP)), NULL);
    defineFunctionObject("GET-SKOLEM-AND-VALUE-TERMS", "(DEFUN (GET-SKOLEM-AND-VALUE-TERMS SKOLEM OBJECT) ((PROPOSITION PROPOSITION)) :PUBLIC? TRUE)", ((cpp_function_code)(&getSkolemAndValueTerms)), NULL);
    defineFunctionObject("ENUMERATED-SET?", "(DEFUN (ENUMERATED-SET? BOOLEAN) ((SELF OBJECT)))", ((cpp_function_code)(&enumeratedSetP)), NULL);
    defineFunctionObject("ENUMERATED-LIST?", "(DEFUN (ENUMERATED-LIST? BOOLEAN) ((SELF OBJECT)))", ((cpp_function_code)(&enumeratedListP)), NULL);
    defineFunctionObject("CANONICALIZE-PROPOSITION-TREE", "(DEFUN (CANONICALIZE-PROPOSITION-TREE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&canonicalizePropositionTree)), NULL);
    defineFunctionObject("UPDATE-EQUIVALENCE-PROPOSITION", "(DEFUN (UPDATE-EQUIVALENCE-PROPOSITION PROPOSITION) ((PROPOSITION PROPOSITION) (UPDATEMODE KEYWORD)))", ((cpp_function_code)(&updateEquivalenceProposition)), NULL);
    defineFunctionObject("SKOLEMIZE-EXISTS-PROPOSITION", "(DEFUN (SKOLEMIZE-EXISTS-PROPOSITION PROPOSITION) ((EXISTSPROPOSITION PROPOSITION)))", ((cpp_function_code)(&skolemizeExistsProposition)), NULL);
    defineFunctionObject("HELP-UPDATE-TOP-LEVEL-PROPOSITION", "(DEFUN (HELP-UPDATE-TOP-LEVEL-PROPOSITION (CONS OF PROPOSITION)) ((PROPOSITION PROPOSITION) (UPDATEMODE KEYWORD)))", ((cpp_function_code)(&helpUpdateTopLevelProposition)), NULL);
    defineFunctionObject("INVERT-UPDATE-MODE", "(DEFUN (INVERT-UPDATE-MODE KEYWORD) ((UPDATEMODE KEYWORD)))", ((cpp_function_code)(&invertUpdateMode)), NULL);
    defineFunctionObject("DEFAULTIFY-UPDATE-MODE", "(DEFUN (DEFAULTIFY-UPDATE-MODE KEYWORD) ((UPDATEMODE KEYWORD)))", ((cpp_function_code)(&defaultifyUpdateMode)), NULL);
    defineFunctionObject("UPDATE-TOP-LEVEL-PROPOSITION", "(DEFUN (UPDATE-TOP-LEVEL-PROPOSITION (CONS OF PROPOSITION)) ((TREE OBJECT) (UPDATEMODE KEYWORD)))", ((cpp_function_code)(&updateTopLevelProposition)), NULL);
    defineFunctionObject("STANDARDIZE-PROPOSITION-TREE", "(DEFUN (STANDARDIZE-PROPOSITION-TREE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&standardizePropositionTree)), NULL);
    defineFunctionObject("UPDATE-PROPOSITION", "(DEFUN (UPDATE-PROPOSITION (CONS OF PROPOSITION)) ((TREE OBJECT) (UPDATEMODE KEYWORD)))", ((cpp_function_code)(&updateProposition)), NULL);
    defineFunctionObject("BUILD-TOP-LEVEL-TERM", "(DEFUN (BUILD-TOP-LEVEL-TERM OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&buildTopLevelTerm)), NULL);
    defineFunctionObject("CONCEIVE-TERM", "(DEFUN (CONCEIVE-TERM OBJECT) ((TREE OBJECT)) :DOCUMENTATION \"`tree' is a term expression (a string or an s-expression),\nor is a class reference (a symbol or surrogate).  Return a (possibly \nnewly-conceived) term representing the internalized representation of that term.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? TRUE :LISP-MACRO? FALSE)", ((cpp_function_code)(&conceiveTerm)), NULL);
    defineFunctionObject("CONCEIVE-SENTENCE", "(DEFUN (CONCEIVE-SENTENCE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&conceiveSentence)), NULL);
    defineFunctionObject("CONCEIVE-FORMULA", "(DEFUN (CONCEIVE-FORMULA OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&conceiveFormula)), NULL);
    defineFunctionObject("SMART-UPDATE-PROPOSITION", "(DEFUN (SMART-UPDATE-PROPOSITION OBJECT) ((TREE OBJECT) (UPDATEMODE KEYWORD)))", ((cpp_function_code)(&smartUpdateProposition)), NULL);
    defineFunctionObject("ASSERT", "(DEFUN (ASSERT OBJECT) ((PROPOSITION PARSE-TREE)) :DOCUMENTATION \"Assert the truth of `proposition'.  Return the asserted proposition object.\nKIF example:  \\\"(assert (happy Fred))\\\" asserts that Fred is indeed happy.\nNote that for this assertion to succeed, the relation `happy' must already\nbe defined.  If the constant `Fred' has not yet been created, it is\nautomatically created as a side-effect of calling `assert'.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&asserT)), NULL);
    defineFunctionObject("PRESUME", "(DEFUN (PRESUME OBJECT) ((PROPOSITION PARSE-TREE)) :DOCUMENTATION \"Presume the default truth of `proposition'.  Return the presumed\nproposition object.  KIF example:  \\\"(presume (happy Fred))\\\" states that Fred\nis most probably happy.  Note, that for this to succeed, the relation\n`happy' must already be defined (see `assert').\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&presume)), NULL);
    defineFunctionObject("RETRACT", "(DEFUN (RETRACT OBJECT) ((PROPOSITION PARSE-TREE)) :DOCUMENTATION \"Retract the truth of `proposition'.  Return the retracted proposition\nobject.  KIF example:  \\\"(retract (happy Fred))\\\" retracts that Fred is\nhappy.  Note that for this assertion to succeed, the relation `happy' must already\nbe defined.  If the constant `Fred' has not yet been created, it is\nautomatically created as a side-effect of calling `retract'.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&retract)), NULL);
  }
}

void helpStartupPropositions13() {
  {
    defineFunctionObject("DENY", "(DEFUN (DENY OBJECT) ((PROPOSITION PARSE-TREE)) :DOCUMENTATION \"Assert the falsity of `proposition'.  Return the asserted proposition\nobject.  KIF example:  \\\"(deny (happy Fred))\\\" asserts that Fred is not happy,\nwhich could have been done equivalently by \\\"(assert (not (happy Fred)))\\\".\nNote, that for this to succeed, the relation `happy' must already be defined\n(see `assert').\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&deny)), NULL);
    defineFunctionObject("CONCEIVE", "(DEFUN (CONCEIVE OBJECT) ((FORMULA PARSE-TREE)) :DOCUMENTATION \"Guess whether 'formula' represents a term or a sentence/proposition.\nIf we are not sure, assume its a proposition.\nIf it is a term, return its internal representation.  If a proposition,\nconstruct a proposition for 'formula' without asserting its truth value.\nReturn the conceived proposition object.  KIF example: \\\"(conceive (happy Fred))\\\"\nbuilds the proposition expressing that Fred is happy without explictly asserting\nor denying it.  Note, that for this to succeed, the relation `happy' must already\nbe defined (see `assert').  If the logic constant `Fred' has not yet been\ncreated, it is automatically created as a side-effect of calling `conceive'.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&conceive)), NULL);
    defineFunctionObject("UNASSERT", "(DEFUN (UNASSERT OBJECT) ((PROPOSITION PARSE-TREE)) :DOCUMENTATION \"Retract the truth, falsity or inconsistency of `proposition'.  This is a\nmore general version of `retract' that also handles falsity.  For example, if\nwe assert the proposition \\\"(not (sad Fred))\\\", and then execute the statement\n\\\"(unassert (sad Fred))\\\", the truth value of the proposition \\\"(sad Fred)\\\"\nwill be set to UNKNOWN.  If we had called `retract' in place of `unassert',\nthe proposition \\\"(sad Fred)\\\" would remain set to FALSE.   Note that for this\nunassertion to succeed, the logic constant `Fred' and the relation `sad' must\nalready be defined.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&unassert)), NULL);
    defineFunctionObject("UNASSERT-PROPOSITION", "(DEFUN UNASSERT-PROPOSITION ((SELF PROPOSITION)) :DOCUMENTATION \"Retract the truth, falsity or inconsistency of the proposition `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unassertProposition)), NULL);
    defineMethodObject("(DEFMETHOD (DELETED? BOOLEAN) ((SELF PROPOSITION)))", wrapMethodCode(((cpp_method_code)(&Proposition::deletedP))), NULL);
    defineMethodObject("(DEFMETHOD (DELETED?-SETTER BOOLEAN) ((SELF PROPOSITION) (VALUE BOOLEAN)))", wrapMethodCode(((cpp_method_code)(&Proposition::deletedPSetter))), NULL);
    defineFunctionObject("DELETED-PROPOSITION?", "(DEFUN (DELETED-PROPOSITION? BOOLEAN) ((SELF PROPOSITION)))", ((cpp_function_code)(&deletedPropositionP)), NULL);
    defineFunctionObject("DESTROY-PROPOSITION", "(DEFUN (DESTROY-PROPOSITION PROPOSITION) ((PROPOSITION PROPOSITION)) :DOCUMENTATION \"Retract and destroy the proposition 'proposition'.\nRecursively destroy all propositions that reference 'proposition'.\nAlso, destroy all satellite propositions of 'proposition'.\")", ((cpp_function_code)(&destroyProposition)), NULL);
    defineFunctionObject("DESTROY-REDUNDANT-PROPOSITION", "(DEFUN DESTROY-REDUNDANT-PROPOSITION ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&destroyRedundantProposition)), NULL);
    defineFunctionObject("DESTROY-LOGIC-INSTANCE", "(DEFUN DESTROY-LOGIC-INSTANCE ((SELF OBJECT)))", ((cpp_function_code)(&destroyLogicInstance)), NULL);
    defineFunctionObject("DESTROY-TERM", "(DEFUN DESTROY-TERM ((SELF LOGIC-OBJECT)) :DOCUMENTATION \"Destroy all propositions that reference 'self',\nand mark it as 'deleted?', thereby making it invisible within class\nextensions.  Unlink descriptions from native relations.\" :PUBLIC? TRUE)", ((cpp_function_code)(&destroyTerm)), NULL);
    defineFunctionObject("DESTROY-INSTANCE", "(DEFUN DESTROY-INSTANCE ((SELF OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Destroy all propositions that reference 'self',\nand mark it as 'deleted?', thereby making it invisible within class\nextensions.\")", ((cpp_function_code)(&destroyInstance)), NULL);
    defineFunctionObject("DESTROY-OBJECT", "(DEFUN DESTROY-OBJECT ((SELF OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Destroy `self' which can be a term or a proposition.  Destroy all\npropositions that reference 'self' and mark it as 'deleted?' (thereby\nmaking it invisible within class extensions).\")", ((cpp_function_code)(&destroyObject)), NULL);
    defineFunctionObject("DESTROY", "(DEFUN (DESTROY OBJECT) ((OBJECTSPEC PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Find an object or proposition as specified by `objectSpec', and destroy all\npropositions and indices that reference it.  `objectSpec' must be a name or\na parse tree that evaluates to a proposition.  Return the deleted object, or\nNULL if no matching object was found.\")", ((cpp_function_code)(&destroy)), NULL);
    defineFunctionObject("RELATION-IN-MODULE?", "(DEFUN (RELATION-IN-MODULE? BOOLEAN) ((SELF NAMED-DESCRIPTION)))", ((cpp_function_code)(&relationInModuleP)), NULL);
    defineFunctionObject("INTRODUCE-MODULE", "(DEFUN INTRODUCE-MODULE ((MODULE MODULE)) :PUBLIC? TRUE)", ((cpp_function_code)(&introduceModule)), NULL);
    defineFunctionObject("CLEAR-LOGIC-MODULE-HOOK", "(DEFUN CLEAR-LOGIC-MODULE-HOOK ((MODULE MODULE)))", ((cpp_function_code)(&clearLogicModuleHook)), NULL);
    defineFunctionObject("CLEAR-INSTANCES", "(DEFUN CLEAR-INSTANCES (|&REST| (NAME NAME)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Destroy all instances belonging to module `name' or any of its children.\nLeave meta-objects, e.g., concepts and relations, alone.\nIf no `name' is supplied, the current module will be cleared after\nconfirming with the user.\")", ((cpp_function_code)(&clearInstances)), ((cpp_function_code)(&clearInstancesEvaluatorWrapper)));
    defineFunctionObject("DO-CLEAR-INSTANCES", "(DEFUN DO-CLEAR-INSTANCES ((MODULE MODULE)) :DOCUMENTATION \"Function version of `clear-instances' that evaluates its argument.\" :PUBLIC? TRUE)", ((cpp_function_code)(&doClearInstances)), NULL);
    defineFunctionObject("DESTROY-LOGIC-CONTEXT-HOOK", "(DEFUN DESTROY-LOGIC-CONTEXT-HOOK ((SELF CONTEXT)))", ((cpp_function_code)(&destroyLogicContextHook)), NULL);
    defineFunctionObject("CLEAR-CACHES", "(DEFUN CLEAR-CACHES () :DOCUMENTATION \"Clear all query and memoization caches.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&clearCaches)), NULL);
    defineFunctionObject("RESET-POWERLOOM", "(DEFUN RESET-POWERLOOM () :DOCUMENTATION \"Reset PowerLoom to its initial state.\nCAUTION: This will destroy all loaded knowledge bases and might break other\nloaded STELLA systems if they do reference PowerLoom symbols in their code.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&resetPowerloom)), NULL);
    defineFunctionObject("CONS-LESS-THAN?", "(DEFUN (CONS-LESS-THAN? BOOLEAN) ((O1 CONS) (O2 CONS)))", ((cpp_function_code)(&consLessThanP)), NULL);
    defineFunctionObject("STRING-TERM-LESS?", "(DEFUN (STRING-TERM-LESS? BOOLEAN) ((S1 STRING) (S2 STRING)))", ((cpp_function_code)(((boolean  (*) (const char*, const char*))(&stringTermLessP)))), NULL);
    defineFunctionObject("SAFE-STRING-TERM-LESS?", "(DEFUN (SAFE-STRING-TERM-LESS? BOOLEAN) ((S1 STRING) (S2 STRING)))", ((cpp_function_code)(&safeStringTermLessP)), NULL);
    defineFunctionObject("SAFE-QUANTITY-LESS?", "(DEFUN (SAFE-QUANTITY-LESS? BOOLEAN) ((Q1 QUANTITY) (O2 OBJECT)))", ((cpp_function_code)(&safeQuantityLessP)), NULL);
    defineFunctionObject("SAFE-QUANTITY-GREATER-EQUAL?", "(DEFUN (SAFE-QUANTITY-GREATER-EQUAL? BOOLEAN) ((Q1 QUANTITY) (O2 OBJECT)))", ((cpp_function_code)(&safeQuantityGreaterEqualP)), NULL);
    defineFunctionObject("OBJECT-NAME-LESS-THAN?", "(DEFUN (OBJECT-NAME-LESS-THAN? BOOLEAN) ((O1 LOGIC-OBJECT) (O2 LOGIC-OBJECT)))", ((cpp_function_code)(&objectNameLessThanP)), NULL);
    defineFunctionObject("MODULE-NAME-LESS-THAN?", "(DEFUN (MODULE-NAME-LESS-THAN? BOOLEAN) ((M1 CONTEXT) (M2 CONTEXT)))", ((cpp_function_code)(&moduleNameLessThanP)), NULL);
    defineFunctionObject("PROPOSITION-LESS-THAN?", "(DEFUN (PROPOSITION-LESS-THAN? BOOLEAN) ((P1 PROPOSITION) (P2 PROPOSITION)))", ((cpp_function_code)(&propositionLessThanP)), NULL);
    defineFunctionObject("PROPOSITION-HEAD-SORT-STRING", "(DEFUN (PROPOSITION-HEAD-SORT-STRING STRING) ((P PROPOSITION)))", ((cpp_function_code)(&propositionHeadSortString)), NULL);
    defineFunctionObject("OBJECT-SORT-STRING", "(DEFUN (OBJECT-SORT-STRING STRING) ((O OBJECT)))", ((cpp_function_code)(&objectSortString)), NULL);
    defineFunctionObject("LOGIC-FORM-LESS?", "(DEFUN (LOGIC-FORM-LESS? BOOLEAN) ((O1 OBJECT) (O2 OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"A sorting predicate for objects `o1' and `o2' that can appear in logical\nforms.  Performs a combined numeric and lexocographic sort that accounts\nfor lists, collections and propositions.  Numbers precede all other values,\n`null' follows all other values.\")", ((cpp_function_code)(&logicFormLessP)), NULL);
    defineFunctionObject("STARTUP-PROPOSITIONS", "(DEFUN STARTUP-PROPOSITIONS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupPropositions)), NULL);
    { MethodSlot* function = lookupFunction(SYM_PROPOSITIONS_LOGIC_STARTUP_PROPOSITIONS);

      setDynamicSlotValue(function->dynamicSlots, SYM_PROPOSITIONS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupPropositions"), NULL_STRING_WRAPPER);
    }
  }
}

void startupPropositions() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupPropositions1();
      helpStartupPropositions2();
      helpStartupPropositions3();
      helpStartupPropositions4();
      helpStartupPropositions5();
    }
    if (currentStartupTimePhaseP(4)) {
      helpStartupPropositions6();
    }
    if (currentStartupTimePhaseP(5)) {
      helpStartupPropositions7();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupPropositions8();
      helpStartupPropositions9();
      helpStartupPropositions10();
      helpStartupPropositions11();
      helpStartupPropositions12();
      helpStartupPropositions13();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFCONSTANT ZERO-VARIABLES-VECTOR VARIABLES-VECTOR (NEW VARIABLES-VECTOR :ARRAY-SIZE 0) :DOCUMENTATION \"Save space by structure-sharing zero-length variable vectors.\")", &ZERO_VARIABLES_VECTOR);
      defineGlobalVariableObject("(DEFGLOBAL *PARTIAL-SUPPORT-COUNTER* INTEGER 0)", &oPARTIAL_SUPPORT_COUNTERo);
      defineGlobalVariableObject("(DEFGLOBAL *OPERATOR-NAME-TO-SURROGATE-TABLE* (PROPERTY-LIST OF KEYWORD SURROGATE) (NEW PROPERTY-LIST :THE-PLIST (BQUOTE (:AND /PL-KERNEL-KB/@AND :OR /PL-KERNEL-KB/@OR :NOT /PL-KERNEL-KB/@NOT :FORALL /PL-KERNEL-KB/@FORALL :EXISTS /PL-KERNEL-KB/@EXISTS :EQUIVALENT /PL-KERNEL-KB/@EQUIVALENT :FAIL /PL-KERNEL-KB/@FAIL :COLLECT-INTO /PL-KERNEL-KB/@COLLECT-INTO :IMPLIES /PL-KERNEL-KB/@SUBSET-OF))) :DOCUMENTATION \"Maps names of KIF operators to relational surrogates.\")", &oOPERATOR_NAME_TO_SURROGATE_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *LOGIC-MODULE* MODULE (GET-STELLA-MODULE \"LOGIC\" TRUE) :PUBLIC? TRUE)", &oLOGIC_MODULEo);
      defineGlobalVariableObject("(DEFGLOBAL *PL-KERNEL-MODULE* MODULE (GET-STELLA-MODULE \"PL-KERNEL\" TRUE) :PUBLIC? TRUE)", &oPL_KERNEL_MODULEo);
      defineGlobalVariableObject("(DEFGLOBAL *NOW-TIMESTAMP* TIMESTAMP 0 :DOCUMENTATION \"The NOW time stamp is incremented whenever a series\nof one or more updates is followed by a query.\")", &oNOW_TIMESTAMPo);
      defineGlobalVariableObject("(DEFGLOBAL *LAST-KB-ACTION* KEYWORD :UPDATE-PROPOSITION :DOCUMENTATION \"Records whether the last KB access was a query or\nan update.  Used to determine when to increment the NOW time stamp\ncounter.\")", &oLAST_KB_ACTIONo);
      defineGlobalVariableObject("(DEFGLOBAL BOTTOM LOGIC-OBJECT NULL :PUBLIC? TRUE :DOCUMENTATION \"The undefined individual.  Denotes the non-existence of\nan individual in whatever slot it occupies.\")", &BOTTOM);
      BOTTOM = createSkolem(NULL, SYM_PROPOSITIONS_LOGIC_BOTTOM);
      defineGlobalVariableObject("(DEFSPECIAL *EVALUATIONMODE* KEYWORD :EXTENSIONAL-ASSERTION :DOCUMENTATION \"Indicates the context for evaluating a proposition.  One\nof :DESCRIPTION, :INTENSIONAL-ASSERTION, or :EXTENSIONAL-ASSERTION.\")", &oEVALUATIONMODEo);
      defineGlobalVariableObject("(DEFSPECIAL *CLIPPINGENABLED?* BOOLEAN TRUE :DOCUMENTATION \"When enabled, slot-value assertions can be retracted\nby later conflicting assertions.\")", &oCLIPPINGENABLEDpo);
      defineGlobalVariableObject("(DEFSPECIAL *NATURALDEDUCTIONMODE?* BOOLEAN TRUE :DOCUMENTATION \"When enabled, blocks normalizations that significantly\nchange the behavior of inference rules.\")", &oNATURALDEDUCTIONMODEpo);
      defineGlobalVariableObject("(DEFGLOBAL *CONTEXT-DEPENDENT-SEARCH-MODE?* BOOLEAN FALSE :DOCUMENTATION \"Signals that we are performing search across multiple\ncontexts.  Used to disable retraction from collections, since that increases\nthe overhead of the context mechanism.\")", &oCONTEXT_DEPENDENT_SEARCH_MODEpo);
      defineGlobalVariableObject("(DEFSPECIAL *COMPUTEDQUERY?* BOOLEAN FALSE :DOCUMENTATION \"Used to signal 'ground-value-of' that it can\ncall 'bound-to' safely.\")", &oCOMPUTEDQUERYpo);
      defineGlobalVariableObject("(DEFGLOBAL *SKOLEM-ID-COUNTER* INTEGER 0)", &oSKOLEM_ID_COUNTERo);
      defineGlobalVariableObject("(DEFSPECIAL *VARIABLEIDCOUNTER* INTEGER 0)", &oVARIABLEIDCOUNTERo);
      defineGlobalVariableObject("(DEFSPECIAL *FREESKOLEMS* CONS NULL :DOCUMENTATION \"Cons-list of top-level existentially-quantified skolems.\")", &oFREESKOLEMSo);
      defineGlobalVariableObject("(DEFCONSTANT TRUE-TRUTH-VALUE TRUTH-VALUE (NEW TRUTH-VALUE :POLARITY :TRUE :STRENGTH :STRICT :MATCH-SCORE 1.0) :DOCUMENTATION \"Value representing TRUE.\")", &TRUE_TRUTH_VALUE);
      defineGlobalVariableObject("(DEFCONSTANT FALSE-TRUTH-VALUE TRUTH-VALUE (NEW TRUTH-VALUE :POLARITY :FALSE :STRENGTH :STRICT :MATCH-SCORE -1.0) :DOCUMENTATION \"Value representing FALSE.\")", &FALSE_TRUTH_VALUE);
      defineGlobalVariableObject("(DEFCONSTANT DEFAULT-TRUE-TRUTH-VALUE TRUTH-VALUE (NEW TRUTH-VALUE :POLARITY :TRUE :STRENGTH :DEFAULT :MATCH-SCORE 0.8) :DOCUMENTATION \"Value representing DEFAULT-TRUE.\")", &DEFAULT_TRUE_TRUTH_VALUE);
      defineGlobalVariableObject("(DEFCONSTANT DEFAULT-FALSE-TRUTH-VALUE TRUTH-VALUE (NEW TRUTH-VALUE :POLARITY :FALSE :STRENGTH :DEFAULT :MATCH-SCORE -0.8) :DOCUMENTATION \"Value representing DEFAULT-FALSE.\")", &DEFAULT_FALSE_TRUTH_VALUE);
      defineGlobalVariableObject("(DEFCONSTANT UNKNOWN-TRUTH-VALUE TRUTH-VALUE (NEW TRUTH-VALUE :POLARITY :UNKNOWN) :DOCUMENTATION \"Value representing UNKNOWN.  Needed for those cases\nwhere we need a non-NULL truth value to represents UNKNOWN.\")", &UNKNOWN_TRUTH_VALUE);
      defineGlobalVariableObject("(DEFCONSTANT INCONSISTENT-TRUTH-VALUE TRUTH-VALUE (NEW TRUTH-VALUE :POLARITY :INCONSISTENT :STRENGTH :STRICT) :DOCUMENTATION \"Value representing a contradiction.\")", &INCONSISTENT_TRUTH_VALUE);
      defineGlobalVariableObject("(DEFSPECIAL *SUPPRESSUNTYPEDTYPEERROR?* BOOLEAN FALSE :DOCUMENTATION \"Used by 'safe-logical-type' to ask for a type\nwithout signalling an error if none exists.\")", &oSUPPRESSUNTYPEDTYPEERRORpo);
      defineGlobalVariableObject("(DEFGLOBAL *EQUIVALENCE-COLLECTIONS?* BOOLEAN TRUE :DOCUMENTATION \"Experiment with equality reasoning on collections.\")", &oEQUIVALENCE_COLLECTIONSpo);
      defineGlobalVariableObject("(DEFCONSTANT TRUE-PROPOSITION PROPOSITION (NEW PROPOSITION :KIND :CONSTANT :OPERATOR @TRUE :ARGUMENTS (NEW ARGUMENTS-VECTOR :ARRAY-SIZE 0) :TRUTH-VALUE TRUE-TRUTH-VALUE :HOME-CONTEXT *PL-KERNEL-MODULE*))", &TRUE_PROPOSITION);
      defineGlobalVariableObject("(DEFCONSTANT FALSE-PROPOSITION PROPOSITION (NEW PROPOSITION :KIND :CONSTANT :OPERATOR @FALSE :ARGUMENTS (NEW ARGUMENTS-VECTOR :ARRAY-SIZE 0) :TRUTH-VALUE FALSE-TRUTH-VALUE :HOME-CONTEXT *PL-KERNEL-MODULE*))", &FALSE_PROPOSITION);
      SGT_PROPOSITIONS_STELLA_TRUE->surrogateValue = TRUE_PROPOSITION;
      SGT_PROPOSITIONS_STELLA_FALSE->surrogateValue = FALSE_PROPOSITION;
      findDuplicateProposition(TRUE_PROPOSITION);
      findDuplicateProposition(FALSE_PROPOSITION);
      defineGlobalVariableObject("(DEFCONSTANT ANONYMOUS-VARIABLE-NAME SYMBOL (QUOTE ?) :DOCUMENTATION \"Variables with name 'ANONYMOUS-VARIABLE-NAME' are considered\nanonymous, and are not assumed to be identical to any other variable also named\n'ANONYMOUS-VARIABLE-NAME'.\")", &ANONYMOUS_VARIABLE_NAME);
      defineGlobalVariableObject("(DEFGLOBAL *MISSING-KEY-VALUE-LIST* KEY-VALUE-LIST (NEW KEY-VALUE-LIST) :DOCUMENTATION \"Represents a key-value list that should never be used.\")", &oMISSING_KEY_VALUE_LISTo);
      defineGlobalVariableObject("(DEFSPECIAL *AUTOMATICINSTANCETABLE* (KEY-VALUE-LIST OF SYMBOL LOGIC-OBJECT) *MISSING-KEY-VALUE-LIST* :DOCUMENTATION \"Used by 'evaluate-automatic-instance' to\nrecord current bindings of automatic instance symbols.\")", &oAUTOMATICINSTANCETABLEo);
      addHook(oREDEFINE_RELATION_HOOKSo, SYM_PROPOSITIONS_LOGIC_TRANSFER_LOGIC_INFORMATION_FROM_RELATION_HOOK);
      defineGlobalVariableObject("(DEFSPECIAL *DEFAULTCREATIONTYPE* SURROGATE NULL)", &oDEFAULTCREATIONTYPEo);
      defineGlobalVariableObject("(DEFGLOBAL *STRUCTURED-OBJECTS-INDEX* (KEY-VALUE-MAP OF INTEGER-WRAPPER (LIST OF CONTEXT-SENSITIVE-OBJECT)) (NEW KEY-VALUE-MAP) :DOCUMENTATION \"Contains a table of propositions and descriptions, indexed by a\nstructure hash code which might be shared by different objects.\")", &oSTRUCTURED_OBJECTS_INDEXo);
      defineGlobalVariableObject("(DEFSPECIAL *DONT-CHECK-FOR-DUPLICATE-PROPOSITIONS?* BOOLEAN FALSE :DOCUMENTATION \"If TRUE never check for the existence of duplicate\npropositions when building a new proposition.\")", &oDONT_CHECK_FOR_DUPLICATE_PROPOSITIONSpo);
      defineGlobalVariableObject("(DEFSPECIAL *VISITEDUNFASTENEDDEFININGPROPOSITIONS* LIST NULL :DOCUMENTATION \"Used by 'recursively-fasten-down-propositions'.\")", &oVISITEDUNFASTENEDDEFININGPROPOSITIONSo);
      defineGlobalVariableObject("(DEFGLOBAL *AUTO-COERCE-PROPOSITIONAL-ARGUMENTS?* BOOLEAN FALSE :DOCUMENTATION \"If TRUE, automatically coerce propositional arguments of a\nproposition, even if the corresponding argument type of the hosting relation\ndoesn't indicate that.\" :DEMON-PROPERTY \"powerloom.autoCoercePropositionalArguments\" :PUBLIC? TRUE)", &oAUTO_COERCE_PROPOSITIONAL_ARGUMENTSpo);
      defineGlobalVariableObject("(DEFGLOBAL *TYPE-CHECK-POLICY* KEYWORD :AUTOMATICALLY-FIX-TYPE-VIOLATIONS :DOCUMENTATION \"Three policies are implemented:\n   :AUTOMATICALLY-FIX-TYPE-VIOLATIONS asserts missing types to fix type\n       violations (default),\n   :REPORT-TYPE-VIOLATIONS complains about missing or incorrect types,\n   :SIGNAL-TYPE-VIOLATIONS throws exception for missing or incorrect types, and\n   :IGNORE-TYPE-VIOLATIONS which disables all type checking.\")", &oTYPE_CHECK_POLICYo);
      defineGlobalVariableObject("(DEFSPECIAL *TYPECHECKMODE* KEYWORD :POST-TYPE-VIOLATIONS :DOCUMENTATION \"Controls the behavior of the type-checking\nroutines in the event that a type-check fails.  Options are:\n  :POST-TYPE-VIOLATIONS              push offending proposition onto queue,\n  :REPORT-TYPE-VIOLATIONS            print occasions of failed type checks,\n  :SIGNAL-TYPE-VIOLATIONS            throw exception for failed type checks,\n  :AUTOMATICALLY-FIX-TYPE-VIOLATIONS assert missing types on propositions, and\n  :IGNORE-TYPE-VIOLATIONS            don't perform any type checking at all.\")", &oTYPECHECKMODEo);
      defineGlobalVariableObject("(DEFGLOBAL *CHECK-TYPES-AGENDA* (VECTOR-SEQUENCE OF CHECK-TYPES-RECORD) (NEW VECTOR-SEQUENCE :ARRAY-SIZE 4) :DOCUMENTATION \"List of propositions that have failed a type check,\nbut might pass once finalization is complete.\")", &oCHECK_TYPES_AGENDAo);
      registerNativeName(SYM_PROPOSITIONS_STELLA_ASSERT, KWD_PROPOSITIONS_CPP, KWD_PROPOSITIONS_FUNCTION);
      defineGlobalVariableObject("(DEFSPECIAL *DEFERRED-TERMS-TO-UNLINK* HASH-SET NULL)", &oDEFERRED_TERMS_TO_UNLINKo);
      addHook(oDEFINE_MODULE_HOOKSo, SYM_PROPOSITIONS_LOGIC_INTRODUCE_MODULE);
      addHook(oCLEAR_MODULE_HOOKSo, SYM_PROPOSITIONS_LOGIC_CLEAR_LOGIC_MODULE_HOOK);
      addHook(oDESTROY_CONTEXT_HOOKSo, SYM_PROPOSITIONS_LOGIC_DESTROY_LOGIC_CONTEXT_HOOK);
    }
  }
}

Symbol* SYM_PROPOSITIONS_LOGIC_PROPOSITIONS_INDEX = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_INSTANCES_INDEX = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_BACKLINKS_INDEX = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_DEPENDENT_PROPOSITIONS_LIST = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_DEPENDENT_ISA_PROPOSITIONS_LIST = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_PREDICATE_PROPOSITIONS_TABLE = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_LOGIC_OBJECT = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_BADp = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_VARIABLE_VALUE_INVERSE = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_SURROGATE_VALUE_INVERSE = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_OBJECT_STRINGIFIED_SOURCE = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_OBJECT_ORIGINATED_PROPOSITIONS = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_CS_VALUE = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_DELETED_OBJECTp = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_LOGIC_THING = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_PATTERN_VARIABLE = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_SKOLEM = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_SKOLEM_TYPE = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_SKOLEM_NAME = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_VARIABLE_VALUE = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_DEFINING_PROPOSITION = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_BOUND_TO_OFFSET = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_OBJECT_VECTOR = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_ARGUMENTS_VECTOR = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_VARIABLES_VECTOR = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_FORWARD_CHAINING_INDEX = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_FORWARD_GOAL = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_MASTER_RULE = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_IO_VARIABLES = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_QUERY_BODY = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_INPUT_BINDINGS = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_CACHE_ID = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_CONSEQUENT = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_DESCRIPTION = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_NATIVE_RELATION = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_FORWARD_CHAINING_INDICES = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_DEFERRED_CONTRAPOSITIVESp = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_PROPOSITION = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_INTERNAL_VARIABLES = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_QUERY_PATTERNS = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_RELATIVE_COMPLEMENT = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_COMPLEMENT_DESCRIPTION = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_NAMED_DESCRIPTION = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_NATIVE_RELATION_BACK_POINTER = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_NATIVE_RELATION_SETTER = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_IO_VARIABLE_NAMES = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_IO_VARIABLE_TYPES = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_EXTENSION = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_PARTIAL_MATCH_SCORE = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_SET_OF_SUPPORT = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_TIMESTAMP = NULL;

Keyword* KWD_PROPOSITIONS_UNKNOWN = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_TRUTH_VALUE = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_POLARITY = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_STRENGTH = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_MATCH_SCORE = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_PARTIAL_SUPPORT = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_FACT = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_AXIOM = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_SCORE = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_ID = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_ARGUMENT_SCORES = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_PROPOSITION = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_VARIABLE_TYPEp = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_SATELLITE_PROPOSITIONS = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_UNFASTENEDp = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_WEIGHT_DELTA = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_SUPPORT = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_KIND = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_TRUTH_VALUE = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_ARGUMENTS = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_OPERATOR = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_RELATIONREF = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_DEPENDENT_PROPOSITIONS = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_PROPOSITION_ORIGINATED_PROPOSITIONS = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_PROPOSITION_STRINGIFIED_SOURCE = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_PROPOSITION_NEURAL_NETWORK = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_NEURAL_NETWORK = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_NEURAL_NET = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_QUANTITY_LOGIC_WRAPPER = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_WRAPPER_VALUE = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_FUNCTION_TERM = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_INTEGER_LOGIC_WRAPPER = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_FLOAT_LOGIC_WRAPPER = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_STRING_LOGIC_WRAPPER = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_ENTITY_MAPPING = NULL;

Keyword* KWD_PROPOSITIONS_AND = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_AND = NULL;

Keyword* KWD_PROPOSITIONS_OR = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_OR = NULL;

Keyword* KWD_PROPOSITIONS_NOT = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_NOT = NULL;

Keyword* KWD_PROPOSITIONS_FORALL = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_FORALL = NULL;

Keyword* KWD_PROPOSITIONS_EXISTS = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_EXISTS = NULL;

Keyword* KWD_PROPOSITIONS_EQUIVALENT = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_EQUIVALENT = NULL;

Keyword* KWD_PROPOSITIONS_FAIL = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_FAIL = NULL;

Keyword* KWD_PROPOSITIONS_COLLECT_INTO = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_COLLECT_INTO = NULL;

Keyword* KWD_PROPOSITIONS_IMPLIES = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_SUBSET_OF = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_FUNCTION = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_PREDICATE = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_ISA = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_DESCRIPTIVEp = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_CODE_ONLYp = NULL;

Keyword* KWD_PROPOSITIONS_ERROR = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_EXCEPTION_RECORD = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_CONTEXT = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_MODULE = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_LOCALLY_CONCEIVED_PROPOSITIONS_INTERNAL = NULL;

Keyword* KWD_PROPOSITIONS_PAGING = NULL;

Keyword* KWD_PROPOSITIONS_CONTEXT_PROPOSITIONS = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_LOCALLY_CONCEIVED_INSTANCES_INTERNAL = NULL;

Keyword* KWD_PROPOSITIONS_CONTEXT_INSTANCES = NULL;

Keyword* KWD_PROPOSITIONS_UPDATE_PROPOSITION = NULL;

Keyword* KWD_PROPOSITIONS_EXECUTE_QUERY = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_BOTTOM = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_LITERAL = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_F_LOGICAL_SUBTYPE_OF_LITERALp_MEMO_TABLE_000 = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_CLASS = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_LITERAL_WRAPPER = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_BOOLEAN = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_BOOLEAN_WRAPPER = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_VARIABLE_ARITY = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_COLLECTION = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_RELATION_COMPUTATION = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_THING = NULL;

Keyword* KWD_PROPOSITIONS_EXTENSIONAL_ASSERTION = NULL;

Keyword* KWD_PROPOSITIONS_DESCRIPTION = NULL;

Keyword* KWD_PROPOSITIONS_DEVELOPMENT = NULL;

Keyword* KWD_PROPOSITIONS_WARNING = NULL;

Keyword* KWD_PROPOSITIONS_RETRACT_TRUE = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_UPDATE_PROPOSITION_DEMON = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_OBJECT_STORE = NULL;

Keyword* KWD_PROPOSITIONS_FUNCTION = NULL;

Keyword* KWD_PROPOSITIONS_ISA = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_TRUE_DEMON = NULL;

Keyword* KWD_PROPOSITIONS_PREDICATE = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_FALSE_DEMON = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_GOES_UNKNOWN_DEMON = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_MASTER_PROPOSITION = NULL;

Keyword* KWD_PROPOSITIONS_ASSERT_TRUE = NULL;

Keyword* KWD_PROPOSITIONS_PRESUME_TRUE = NULL;

Keyword* KWD_PROPOSITIONS_ASSERT_FALSE = NULL;

Keyword* KWD_PROPOSITIONS_PRESUME_FALSE = NULL;

Keyword* KWD_PROPOSITIONS_RETRACT_FALSE = NULL;

Keyword* KWD_PROPOSITIONS_ASSERT = NULL;

Keyword* KWD_PROPOSITIONS_RETRACT_INCONSISTENT = NULL;

Keyword* KWD_PROPOSITIONS_RETRACT = NULL;

Keyword* KWD_PROPOSITIONS_CONCEIVE = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_HIDDEN_RELATION = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_HIDDEN_INSTANCE = NULL;

Keyword* KWD_PROPOSITIONS_MODULE = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_MODULE = NULL;

Keyword* KWD_PROPOSITIONS_LOCALp = NULL;

Keyword* KWD_PROPOSITIONS_KB_UPDATE = NULL;

Keyword* KWD_PROPOSITIONS_META_KB_UPDATE = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_STORAGE_SLOT = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_SURROGATE = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_RELATION = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_DESCRIPTION = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_EQUIVALENT_VALUE = NULL;

Keyword* KWD_PROPOSITIONS_TRUE = NULL;

Keyword* KWD_PROPOSITIONS_STRICT = NULL;

Keyword* KWD_PROPOSITIONS_FALSE = NULL;

Keyword* KWD_PROPOSITIONS_DEFAULT = NULL;

Keyword* KWD_PROPOSITIONS_INCONSISTENT = NULL;

Keyword* KWD_PROPOSITIONS_LOOKUP_ASSERTIONS = NULL;

Keyword* KWD_PROPOSITIONS_FORWARD = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_META_INFERENCE_CACHE = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_TRUTH_MAINTAINED_INFERENCE_CACHE = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_CLASH_EXCEPTIONS = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_INCOHERENT = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_IOTAp = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_CONCEPT = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_RELATION = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_SET = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_SET = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_SLOT = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_FUNCTION = NULL;

Keyword* KWD_PROPOSITIONS_META = NULL;

Keyword* KWD_PROPOSITIONS_JUST_IN_TIME = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_INTERVAL_CACHE = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_ge = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_CONFLICTING_DEFAULT_VALUES = NULL;

Keyword* KWD_PROPOSITIONS_CONSTANT = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_TRUE = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_FALSE = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_CONS = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_SETOFALL = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_THE_ONLY = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_KAPPA = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_CREATE = NULL;

Keyword* KWD_PROPOSITIONS_INTENSIONAL_ASSERTION = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_p = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_CLASS_EXTENSION = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_TRANSFER_LOGIC_INFORMATION_FROM_RELATION_HOOK = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_SUBRELATION_LINKp = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_HOLDS = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_MEMBER_OF = NULL;

Keyword* KWD_PROPOSITIONS_DISABLED = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_ANNOTATIONS = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_STRING_WRAPPER = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_CONSTANT = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_TRUE = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_FALSE = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_SYMBOL = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_e = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_AND = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_OR = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_NOT = NULL;

Symbol* SYM_PROPOSITIONS_PL_KERNEL_KB_MEMBER_OF = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_IMPLIES = NULL;

Symbol* SYM_PROPOSITIONS_PL_KERNEL_KB_SUBSET_OF = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_EXISTS = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_FORALL = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_FAIL = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_COLLECT_INTO = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_ABOUT = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_GENERALIZED_SYMBOL = NULL;

Keyword* KWD_PROPOSITIONS_DIRECTION = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_FORWARD_ONLYp = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_BACKWARD_ONLYp = NULL;

Keyword* KWD_PROPOSITIONS_WEIGHT = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_WEIGHT = NULL;

Keyword* KWD_PROPOSITIONS_SCORE = NULL;

Keyword* KWD_PROPOSITIONS_CONFIDENCE_LEVEL = NULL;

Symbol* SYM_PROPOSITIONS_PL_KERNEL_KB_SETOF = NULL;

Symbol* SYM_PROPOSITIONS_PL_KERNEL_KB_LISTOF = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_EQUIVALENT = NULL;

Symbol* SYM_PROPOSITIONS_PL_KERNEL_KB_HOLDS = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_TABLE = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_POLYMORPHIC = NULL;

Symbol* SYM_PROPOSITIONS_PL_KERNEL_KB_VALUE = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_VALUE = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_QUANTITY = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_DATE = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_FLOAT = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_INTEGER = NULL;

Keyword* KWD_PROPOSITIONS_AUTOMATICALLY_FIX_TYPE_VIOLATIONS = NULL;

Keyword* KWD_PROPOSITIONS_POST_TYPE_VIOLATIONS = NULL;

Keyword* KWD_PROPOSITIONS_IGNORE_TYPE_VIOLATIONS = NULL;

Keyword* KWD_PROPOSITIONS_REPORT_TYPE_VIOLATIONS = NULL;

Keyword* KWD_PROPOSITIONS_SIGNAL_TYPE_VIOLATIONS = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_ASSERTED_BY_TYPE_CHECKERp = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_CHECK_TYPES_RECORD = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_PARENT_PROPOSITION = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_PARENT_DESCRIPTION = NULL;

Keyword* KWD_PROPOSITIONS_MEDIUM = NULL;

Keyword* KWD_PROPOSITIONS_REALISTIC = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_SETOF = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_TOTAL = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_LISTOF = NULL;

Surrogate* SGT_PROPOSITIONS_PL_KERNEL_KB_LIST = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_LAMBDA = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_BAGOF = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_ASSERT = NULL;

Keyword* KWD_PROPOSITIONS_CPP = NULL;

Keyword* KWD_PROPOSITIONS_DELETED = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_INTRODUCE_MODULE = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_KEY_VALUE_LIST = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_CLEAR_LOGIC_MODULE_HOOK = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_MONOTONICp = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_WORLD = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_DESTROY_LOGIC_CONTEXT_HOOK = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_CLEARABLEp = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_PROTECT_SURROGATESp = NULL;

Keyword* KWD_PROPOSITIONS_PREORDER = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_MUTABLE_STRING_WRAPPER = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_CONTEXT = NULL;

Surrogate* SGT_PROPOSITIONS_LOGIC_COMPUTED_PROCEDURE = NULL;

Surrogate* SGT_PROPOSITIONS_STELLA_NUMBER_WRAPPER = NULL;

Symbol* SYM_PROPOSITIONS_LOGIC_STARTUP_PROPOSITIONS = NULL;

Symbol* SYM_PROPOSITIONS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
