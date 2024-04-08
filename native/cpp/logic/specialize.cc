//  -*- Mode: C++ -*-

// specialize.cc

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

AbstractPropositionsIterator* newAbstractPropositionsIterator() {
  { AbstractPropositionsIterator* self = NULL;

    self = new AbstractPropositionsIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->equivalentsStack = NULL;
    self->propositionCursor = NULL;
    self->selectionPattern = NULL;
    return (self);
  }
}

Surrogate* AbstractPropositionsIterator::primaryType() {
  { AbstractPropositionsIterator* self = this;

    return (SGT_SPECIALIZE_LOGIC_ABSTRACT_PROPOSITIONS_ITERATOR);
  }
}

Object* accessAbstractPropositionsIteratorSlotValue(AbstractPropositionsIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SPECIALIZE_LOGIC_SELECTION_PATTERN) {
    if (setvalueP) {
      self->selectionPattern = ((Cons*)(value));
    }
    else {
      value = self->selectionPattern;
    }
  }
  else if (slotname == SYM_SPECIALIZE_LOGIC_PROPOSITION_CURSOR) {
    if (setvalueP) {
      self->propositionCursor = ((Iterator*)(value));
    }
    else {
      value = self->propositionCursor;
    }
  }
  else if (slotname == SYM_SPECIALIZE_LOGIC_EQUIVALENTS_STACK) {
    if (setvalueP) {
      self->equivalentsStack = ((Cons*)(value));
    }
    else {
      value = self->equivalentsStack;
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

TruePropositionsIterator* newTruePropositionsIterator() {
  { TruePropositionsIterator* self = NULL;

    self = new TruePropositionsIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->equivalentsStack = NULL;
    self->propositionCursor = NULL;
    self->selectionPattern = NULL;
    self->truthValue = NULL;
    return (self);
  }
}

Surrogate* TruePropositionsIterator::primaryType() {
  { TruePropositionsIterator* self = this;

    return (SGT_SPECIALIZE_LOGIC_TRUE_PROPOSITIONS_ITERATOR);
  }
}

Object* accessTruePropositionsIteratorSlotValue(TruePropositionsIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SPECIALIZE_LOGIC_TRUTH_VALUE) {
    if (setvalueP) {
      self->truthValue = ((TruthValue*)(value));
    }
    else {
      value = self->truthValue;
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

SpecializingPropositionsIterator* newSpecializingPropositionsIterator() {
  { SpecializingPropositionsIterator* self = NULL;

    self = new SpecializingPropositionsIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->equivalentsStack = NULL;
    self->propositionCursor = NULL;
    self->selectionPattern = NULL;
    self->truthValue = NULL;
    self->specializingRelations = NULL;
    return (self);
  }
}

Surrogate* SpecializingPropositionsIterator::primaryType() {
  { SpecializingPropositionsIterator* self = this;

    return (SGT_SPECIALIZE_LOGIC_SPECIALIZING_PROPOSITIONS_ITERATOR);
  }
}

Object* accessSpecializingPropositionsIteratorSlotValue(SpecializingPropositionsIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SPECIALIZE_LOGIC_SPECIALIZING_RELATIONS) {
    if (setvalueP) {
      self->specializingRelations = ((Cons*)(value));
    }
    else {
      value = self->specializingRelations;
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

TruthValue* propositionsIteratorTruthValue(Iterator* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_SPECIALIZE_LOGIC_TRUE_PROPOSITIONS_ITERATOR)) {
      { Iterator* self000 = self;
        TruePropositionsIterator* self = ((TruePropositionsIterator*)(self000));

        return (self->truthValue);
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALIZE_LOGIC_DESCRIPTION_EXTENSION_ITERATOR)) {
      { Iterator* self001 = self;
        DescriptionExtensionIterator* self = ((DescriptionExtensionIterator*)(self001));

        return (self->truthValue);
      }
    }
    else {
      return (NULL);
    }
  }
}

Cons* nextEquivalentSelectionPattern(AbstractPropositionsIterator* self) {
  { Cons* pattern = self->selectionPattern;
    Object* keywithequivalents = findSelectionKeyWithEquivalents(pattern);
    Cons* equivalentskolems = self->equivalentsStack;
    Object* newskolem = NULL;

    if (((boolean)(keywithequivalents)) &&
        (!((boolean)(equivalentskolems)))) {
      equivalentskolems = getAllEquivalentValues(keywithequivalents);
    }
    if ((!((boolean)(equivalentskolems))) ||
        (equivalentskolems == NIL)) {
      return (NULL);
    }
    newskolem = equivalentskolems->value;
    self->equivalentsStack = equivalentskolems->rest;
    return (((Cons*)(substituteConsTree(((Cons*)(copyConsTree(pattern))), newskolem, keywithequivalents))));
  }
}

TruthValue* propositionTruthValue(Proposition* proposition) {
  { TruthValue* truthvalue = ((TruthValue*)(accessInContext(proposition->truthValue, proposition->homeContext, false)));

    if (((boolean)(truthvalue))) {
      return (truthvalue);
    }
    else {
      if ((!oREVERSEPOLARITYpo) &&
          functionWithDefinedValueP(proposition)) {
        return (TRUE_TRUTH_VALUE);
      }
      else {
        return (NULL);
      }
    }
  }
}

boolean truePropositionP(Proposition* proposition) {
  return ((!proposition->deletedP()) &&
      ((oREVERSEPOLARITYpo ? falseP(proposition) : (trueP(proposition) ||
      functionWithDefinedValueP(proposition)))));
}

boolean truePropositionsIteratorDnextP(TruePropositionsIterator* self) {
  { Iterator* cursor = self->propositionCursor;
    Proposition* proposition = NULL;

    if (!((boolean)(cursor))) {
      return (false);
    }
    for (;;) {
      if (cursor->nextP()) {
        proposition = ((Proposition*)(cursor->value));
      }
      else {
        { Cons* pattern = nextEquivalentSelectionPattern(self);

          if (((boolean)(pattern))) {
            cursor = selectPropositions(pattern)->allocateIterator();
            self->propositionCursor = cursor;
            continue;
          }
          else {
            self->propositionCursor = NULL;
            return (false);
          }
        }
      }
      if ((!proposition->deletedP()) &&
          ((oREVERSEPOLARITYpo ? falseP(proposition) : (trueP(proposition) ||
          functionWithDefinedValueP(proposition))))) {
        self->value = proposition;
        self->truthValue = propositionTruthValue(proposition);
        return (true);
      }
    }
  }
}

boolean TruePropositionsIterator::nextP() {
  { TruePropositionsIterator* self = this;

    return (truePropositionsIteratorDnextP(self));
  }
}

boolean specializingPropositionsIteratorDnextP(SpecializingPropositionsIterator* self) {
  { Cons* specializingrelations = self->specializingRelations;

    for (;;) {
      if (truePropositionsIteratorDnextP(self)) {
        if (((boolean)(specializingrelations)) &&
            (!(specializingrelations == NIL))) {
          self->truthValue = conjoinTruthValues(self->truthValue, ((TruthValue*)(((Cons*)(specializingrelations->value))->rest->value)));
        }
        self->specializingRelations = specializingrelations;
        return (true);
      }
      if (!((boolean)(specializingrelations))) {
        if (((Keyword*)(self->selectionPattern->value)) == KWD_SPECIALIZE_RELATION) {
          { NamedDescription* relationdescription = surrogateToDescription(((Surrogate*)(self->selectionPattern->rest->rest->value)));

            if (((boolean)(relationdescription))) {
              specializingrelations = allSupportedNamedSubcollections(relationdescription);
            }
            else {
              specializingrelations = NIL;
            }
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "Illegal selection pattern in " << "`" << self << "'";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      else {
        specializingrelations = specializingrelations->rest;
      }
      if (specializingrelations == NIL) {
        self->value = NULL;
        return (false);
      }
      self->selectionPattern = copyConsList(self->selectionPattern);
      self->selectionPattern->rest->rest->firstSetter(((NamedDescription*)(((Cons*)(specializingrelations->value))->value))->surrogateValueInverse);
      self->propositionCursor = selectPropositions(self->selectionPattern)->allocateIterator();
      self->equivalentsStack = NULL;
    }
  }
}

boolean SpecializingPropositionsIterator::nextP() {
  { SpecializingPropositionsIterator* self = this;

    return (specializingPropositionsIteratorDnextP(self));
  }
}

// This iterator returns no values whenever its called.
Iterator* EMPTY_PROPOSITIONS_ITERATOR = NULL;

boolean emptyPropositionsIndexP(SequenceIndex* index, Object* primarykey, boolean specializeP) {
  return ((!specializeP) &&
      (((index == NIL_PAGING_INDEX) ||
      (index == NIL_NON_PAGING_INDEX)) &&
       (!hasEquivalentValuesP(primarykey))));
}

Iterator* allTrueDependentPropositions(Object* self, Surrogate* relation, boolean specializeP) {
  if (!(((boolean)(relation)) ||
      (!specializeP))) {
    std::cerr << "Safety violation: " << "INTERNAL-ERROR: Expected defined relation argument";
  }
  { Cons* pattern = (((boolean)(relation)) ? cons(KWD_SPECIALIZE_RELATION, cons(((!((boolean)(NIL))) ? NIL : NIL), cons(relation, cons(valueOf(self), NIL)))) : cons(KWD_SPECIALIZE_DEPENDENTS, cons(((!((boolean)(NIL))) ? NIL : NIL), cons(valueOf(self), NIL))));
    SequenceIndex* index = selectPropositions(pattern);
    TruePropositionsIterator* iterator = NULL;

    if (emptyPropositionsIndexP(index, self, specializeP)) {
      return (EMPTY_PROPOSITIONS_ITERATOR);
    }
    iterator = (specializeP ? newSpecializingPropositionsIterator() : newTruePropositionsIterator());
    iterator->selectionPattern = pattern;
    iterator->propositionCursor = index->allocateIterator();
    return (iterator);
  }
}

Iterator* allTrueDependentIsaPropositions(Object* self) {
  { Cons* pattern = cons(KWD_SPECIALIZE_ISA, cons(((!((boolean)(NIL))) ? NIL : NIL), cons(valueOf(self), NIL)));
    SequenceIndex* index = selectPropositions(pattern);

    if (emptyPropositionsIndexP(index, self, false)) {
      return (EMPTY_PROPOSITIONS_ITERATOR);
    }
    else {
      { TruePropositionsIterator* self000 = newTruePropositionsIterator();

        self000->selectionPattern = pattern;
        self000->propositionCursor = index->allocateIterator();
        { TruePropositionsIterator* value000 = self000;

          return (value000);
        }
      }
    }
  }
}

boolean relationAndArgumentsUnifyP(Proposition* subproposition, Proposition* referenceproposition, boolean dontunifyrelationP) {
  { PatternRecord* patternrecord = oQUERYITERATORo->currentPatternRecord;
    int ubstackoffset = patternrecord->topUnbindingStackOffset;
    int refstart = 0;
    Vector* refargs = referenceproposition->arguments;
    int numrefargs = refargs->length();
    int substart = 0;
    Vector* subargs = subproposition->arguments;
    int numsubargs = subargs->length();
    boolean successP = true;

    if (!(dontunifyrelationP)) {
      if (referenceproposition->operatoR == SGT_SPECIALIZE_PL_KERNEL_KB_HOLDS) {
        refstart = refstart + 1;
      }
      if (subproposition->operatoR == SGT_SPECIALIZE_PL_KERNEL_KB_HOLDS) {
        substart = substart + 1;
      }
      { Object* suboperator = ((substart > 0) ? argumentBoundTo((subargs->theArray)[0]) : ((Surrogate*)(subproposition->operatoR))->surrogateValue);

        if (!((boolean)(suboperator))) {
          successP = false;
        }
        else if (refstart > 0) {
          successP = bindArgumentToValueP((refargs->theArray)[0], suboperator, false);
        }
        else {
          successP = eqlP(((Surrogate*)(referenceproposition->operatoR))->surrogateValue, suboperator);
        }
      }
    }
    if (successP) {
      { boolean testValue000 = false;

        { boolean alwaysP000 = true;

          { int supi = NULL_INTEGER;
            int iter000 = refstart;
            int upperBound000 = numrefargs - 1;
            int subi = NULL_INTEGER;
            int iter001 = substart;
            int upperBound001 = numsubargs - 1;

            for  (; (iter000 <= upperBound000) &&
                      (iter001 <= upperBound001); 
                  iter000 = iter000 + 1,
                  iter001 = iter001 + 1) {
              supi = iter000;
              subi = iter001;
              if (!((!nullInstanceP((subargs->theArray)[subi])) &&
                  bindArgumentToValueP((refargs->theArray)[supi], valueOf((subargs->theArray)[subi]), false))) {
                alwaysP000 = false;
                break;
              }
            }
          }
          testValue000 = alwaysP000;
        }
        if (testValue000) {
          testValue000 = (numrefargs - refstart) == (numsubargs - substart);
        }
        successP = testValue000;
      }
    }
    if (!successP) {
      unbindVariablesBeginningAt(patternrecord, ubstackoffset + 1);
    }
    return (successP);
  }
}

boolean argumentsUnifyWithArgumentsP(Proposition* subproposition, Proposition* referenceproposition) {
  // Return TRUE if the arguments in proposition 'subProposition' unify with
  // those in 'referenceProposition'.  If one of the propositions is a HOLDS, the other one
  // has to be also for unification to succeed.
  return (relationAndArgumentsUnifyP(subproposition, referenceproposition, true));
}

boolean argumentsEqualArgumentsP(Proposition* subproposition, Proposition* referenceproposition) {
  { boolean testValue000 = false;

    { boolean alwaysP000 = true;

      { Object* superarg = NULL;
        Vector* vector000 = referenceproposition->arguments;
        int index000 = 0;
        int length000 = vector000->length();
        Object* subarg = NULL;
        Vector* vector001 = subproposition->arguments;
        int index001 = 0;
        int length001 = vector001->length();

        for  (; (index000 < length000) &&
                  (index001 < length001); 
              index000 = index000 + 1,
              index001 = index001 + 1) {
          superarg = (vector000->theArray)[index000];
          subarg = (vector001->theArray)[index001];
          if (!eqlP(valueOf(superarg), valueOf(subarg))) {
            alwaysP000 = false;
            break;
          }
        }
      }
      testValue000 = alwaysP000;
    }
    if (testValue000) {
      testValue000 = referenceproposition->arguments->length() == subproposition->arguments->length();
    }
    { boolean value000 = testValue000;

      return (value000);
    }
  }
}

boolean argumentsMatchArgumentsP(Proposition* subproposition, Proposition* referenceproposition) {
  if (((boolean)(oQUERYITERATORo))) {
    return (relationAndArgumentsUnifyP(subproposition, referenceproposition, true));
  }
  else {
    return (argumentsEqualArgumentsP(subproposition, referenceproposition));
  }
}

boolean prefixArgumentsEqualArgumentsP(Proposition* subproposition, Proposition* referenceproposition) {
  { boolean testValue000 = false;

    { boolean alwaysP000 = true;

      { Object* superarg = NULL;
        Vector* vector000 = referenceproposition->arguments;
        int index000 = 0;
        int length000 = vector000->length();
        Object* subarg = NULL;
        Vector* vector001 = subproposition->arguments;
        int index001 = 0;
        int length001 = vector001->length();

        for  (; (index000 < length000) &&
                  (index001 < length001); 
              index000 = index000 + 1,
              index001 = index001 + 1) {
          superarg = (vector000->theArray)[index000];
          subarg = (vector001->theArray)[index001];
          if (!eqlP(valueOf(superarg), valueOf(subarg))) {
            alwaysP000 = false;
            break;
          }
        }
      }
      testValue000 = alwaysP000;
    }
    { boolean value000 = testValue000;

      return (value000);
    }
  }
}

Iterator* allMatchingPropositions(Proposition* self) {
  { Object* backlinkedargument = NULL;
    boolean nomatchingpropositionsP = false;

    backlinkedargument = selectArgumentWithBacklinks(self, nomatchingpropositionsP);
    if (nomatchingpropositionsP) {
      return (EMPTY_PROPOSITIONS_ITERATOR);
    }
    if (!((boolean)(backlinkedargument))) {
      if (oREVERSEPOLARITYpo) {
        return (EMPTY_PROPOSITIONS_ITERATOR);
      }
      if (oCYC_KLUDGES_ENABLEDpo) {
        { boolean testValue000 = false;

          { boolean foundP000 = false;

            { Object* arg = NULL;
              Vector* vector000 = self->arguments;
              int index000 = 0;
              int length000 = vector000->length();

              for  (; index000 < length000; 
                    index000 = index000 + 1) {
                arg = (vector000->theArray)[index000];
                if (((boolean)(argumentBoundTo(arg)))) {
                  foundP000 = true;
                  break;
                }
              }
            }
            testValue000 = foundP000;
          }
          if (testValue000) {
            testValue000 = dynamicallyEstimateExtensionSize(getDescription(self->operatoR)) > 500;
          }
          if (testValue000) {
            return (EMPTY_PROPOSITIONS_ITERATOR);
          }
        }
      }
      return (allMatchingExtensionMembers(self, true));
    }
    { Cons* patternargs = NIL;
      Object* binding = NULL;

      { Object* arg = NULL;
        Vector* vector001 = self->arguments;
        int index001 = 0;
        int length001 = vector001->length();
        Cons* collect000 = NULL;

        for  (; index001 < length001; 
              index001 = index001 + 1) {
          arg = (vector001->theArray)[index001];
          binding = argumentBoundTo(arg);
          if (((boolean)(binding)) &&
              (isaP(binding, SGT_SPECIALIZE_LOGIC_PROPOSITION) &&
               (!allArgumentsBoundP(((Proposition*)(binding)))))) {
            binding = NULL;
          }
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(valueOf(binding), NIL);
              if (patternargs == NIL) {
                patternargs = collect000;
              }
              else {
                addConsToEndOfConsList(patternargs, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(valueOf(binding), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      if (patternargs->rest == NIL) {
        return (allTrueDependentPropositions(backlinkedargument, ((Surrogate*)(self->operatoR)), true));
      }
      else {
        { Cons* pattern = cons(KWD_SPECIALIZE_RELATION, cons(((!((boolean)(NIL))) ? NIL : NIL), cons(self->operatoR, patternargs)));

          { SpecializingPropositionsIterator* self000 = newSpecializingPropositionsIterator();

            self000->selectionPattern = pattern;
            self000->propositionCursor = selectPropositions(pattern)->allocateIterator();
            { SpecializingPropositionsIterator* value000 = self000;

              return (value000);
            }
          }
        }
      }
    }
  }
}

Cons* allPropositionsMatchingArguments(Cons* arguments, Surrogate* relation, boolean specializeP) {
  { Object* backlinkedinstance = selectInstanceWithBacklinks(arguments, relation);

    if (!((boolean)(backlinkedinstance))) {
      return (NIL);
    }
    { Cons* value000 = NIL;

      { Proposition* prop = NULL;
        Iterator* iter000 = allTrueDependentPropositions(backlinkedinstance, relation, specializeP);
        Cons* collect000 = NULL;

        for  (; iter000->nextP(); ) {
          prop = ((Proposition*)(iter000->value));
          { boolean alwaysP000 = true;

            { Object* a1 = NULL;
              Cons* iter001 = arguments;
              int i = NULL_INTEGER;
              int iter002 = 0;

              for  (; !(iter001 == NIL); 
                    iter001 = iter001->rest,
                    iter002 = iter002 + 1) {
                a1 = iter001->value;
                i = iter002;
                if (!eqlP(valueOf(a1), valueOf((prop->arguments->theArray)[i]))) {
                  alwaysP000 = false;
                  break;
                }
              }
            }
            if (alwaysP000) {
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(prop, NIL);
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
                  collect000->rest = cons(prop, NIL);
                  collect000 = collect000->rest;
                }
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
}

Cons* allDefiningPropositions(Object* outputargument, Surrogate* relation, boolean specializeP) {
  { 
    BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
    { Cons* result = NIL;
      Object* outputargumentvalue = valueOf(outputargument);

      { Proposition* prop = NULL;
        Iterator* iter000 = allTrueDependentPropositions(outputargumentvalue, relation, specializeP);
        Cons* collect000 = NULL;

        for  (; iter000->nextP(); ) {
          prop = ((Proposition*)(iter000->value));
          if ((prop->kind == KWD_SPECIALIZE_FUNCTION) &&
              (eqlP(valueOf((prop->arguments->theArray)[(prop->arguments->length() - 1)]), outputargumentvalue) &&
               (!result->membP(prop)))) {
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
      return (result);
    }
  }
}

Iterator* trueToConceivedPropositionsIterator(Iterator* self) {
  if (self == EMPTY_PROPOSITIONS_ITERATOR) {
    return (self);
  }
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_SPECIALIZE_LOGIC_SPECIALIZING_PROPOSITIONS_ITERATOR)) {
      { Iterator* self000 = self;
        SpecializingPropositionsIterator* self = ((SpecializingPropositionsIterator*)(self000));

        return (self->propositionCursor);
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALIZE_LOGIC_TRUE_PROPOSITIONS_ITERATOR)) {
      { Iterator* self001 = self;
        TruePropositionsIterator* self = ((TruePropositionsIterator*)(self001));

        return (self->propositionCursor);
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALIZE_LOGIC_DESCRIPTION_EXTENSION_ITERATOR)) {
      { Iterator* self002 = self;
        DescriptionExtensionIterator* self = ((DescriptionExtensionIterator*)(self002));

        return (self->extensionIterator);
      }
    }
    else {
      return (EMPTY_PROPOSITIONS_ITERATOR);
    }
  }
}

boolean helpMemoizeTestPropertyP(Object* self, Surrogate* relation) {
  { 
    BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getPropertyTestContext());
    if (isaP(self, SGT_SPECIALIZE_LOGIC_LOGIC_OBJECT) &&
        (((LogicObject*)(self))->variableValueInverse_reader() == NIL)) {
      { boolean foundP000 = false;

        { Proposition* p = NULL;
          Iterator* iter000 = unfilteredDependentPropositions(self, relation)->allocateIterator();

          for (; iter000->nextP(); ) {
            p = ((Proposition*)(iter000->value));
            if ((((Surrogate*)(p->operatoR)) == relation) &&
                ((!p->deletedP()) &&
                 ((oREVERSEPOLARITYpo ? falseP(p) : (trueP(p) ||
                functionWithDefinedValueP(p)))))) {
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
    else {
      return (allTrueDependentPropositions(self, relation, false)->nextP());
    }
  }
}

boolean testPropertyP(Object* self, Surrogate* relation) {
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_SPECIALIZE_LOGIC_F_TEST_PROPERTYp_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_SPECIALIZE_LOGIC_F_TEST_PROPERTYp_MEMO_TABLE_000, "(:MAX-VALUES 500 :TIMESTAMPS (:KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_SPECIALIZE_LOGIC_F_TEST_PROPERTYp_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), self, relation, oCONTEXTo, MEMOIZED_NULL_VALUE, 6);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = (helpMemoizeTestPropertyP(self, relation) ? TRUE_WRAPPER : FALSE_WRAPPER);
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { BooleanWrapper* value000 = ((BooleanWrapper*)(memoizedValue000));

      return (coerceWrappedBooleanToBoolean(value000));
    }
  }
}

boolean helpMemoizeTestIsaP(Object* member, Surrogate* type) {
  { 
    BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getPropertyTestContext());
    { boolean foundP000 = false;

      { Proposition* prop = NULL;
        Iterator* iter000 = allTrueDependentIsaPropositions(member);

        for (; iter000->nextP(); ) {
          prop = ((Proposition*)(iter000->value));
          if (relationrefSpecializesRelationrefP(((Surrogate*)(prop->operatoR)), type)) {
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

boolean testIsaP(Object* member, Surrogate* type) {
  if (type == SGT_SPECIALIZE_STELLA_THING) {
    return (true);
  }
  else if ((type == SGT_SPECIALIZE_PL_KERNEL_KB_CLASS) ||
      ((type == SGT_SPECIALIZE_PL_KERNEL_KB_RELATION) ||
       ((type == SGT_SPECIALIZE_PL_KERNEL_KB_FUNCTION) ||
        ((type == SGT_SPECIALIZE_PL_KERNEL_KB_COLLECTION) ||
         (type == SGT_SPECIALIZE_PL_KERNEL_KB_SET))))) {
    { MemoizationTable* memoTable000 = NULL;
      Cons* memoizedEntry000 = NULL;
      Object* memoizedValue000 = NULL;

      if (oMEMOIZATION_ENABLEDpo) {
        memoTable000 = ((MemoizationTable*)(SGT_SPECIALIZE_LOGIC_F_TEST_ISAp_MEMO_TABLE_000->surrogateValue));
        if (!((boolean)(memoTable000))) {
          initializeMemoizationTable(SGT_SPECIALIZE_LOGIC_F_TEST_ISAp_MEMO_TABLE_000, "(:MAX-VALUES 1000 :TIMESTAMPS (:META-KB-UPDATE))");
          memoTable000 = ((MemoizationTable*)(SGT_SPECIALIZE_LOGIC_F_TEST_ISAp_MEMO_TABLE_000->surrogateValue));
        }
        memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), member, type, oCONTEXTo, MEMOIZED_NULL_VALUE, 6);
        memoizedValue000 = memoizedEntry000->value;
      }
      if (((boolean)(memoizedValue000))) {
        if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
          memoizedValue000 = NULL;
        }
      }
      else {
        memoizedValue000 = (helpMemoizeTestIsaP(member, type) ? TRUE_WRAPPER : FALSE_WRAPPER);
        if (oMEMOIZATION_ENABLEDpo) {
          memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
        }
      }
      { BooleanWrapper* value000 = ((BooleanWrapper*)(memoizedValue000));

        return (coerceWrappedBooleanToBoolean(value000));
      }
    }
  }
  else {
    { MemoizationTable* memoTable001 = NULL;
      Cons* memoizedEntry001 = NULL;
      Object* memoizedValue001 = NULL;

      if (oMEMOIZATION_ENABLEDpo) {
        memoTable001 = ((MemoizationTable*)(SGT_SPECIALIZE_LOGIC_F_TEST_ISAp_MEMO_TABLE_001->surrogateValue));
        if (!((boolean)(memoTable001))) {
          initializeMemoizationTable(SGT_SPECIALIZE_LOGIC_F_TEST_ISAp_MEMO_TABLE_001, "(:MAX-VALUES 1000 :TIMESTAMPS (:KB-UPDATE))");
          memoTable001 = ((MemoizationTable*)(SGT_SPECIALIZE_LOGIC_F_TEST_ISAp_MEMO_TABLE_001->surrogateValue));
        }
        memoizedEntry001 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable001)), member, type, oCONTEXTo, MEMOIZED_NULL_VALUE, 6);
        memoizedValue001 = memoizedEntry001->value;
      }
      if (((boolean)(memoizedValue001))) {
        if (memoizedValue001 == MEMOIZED_NULL_VALUE) {
          memoizedValue001 = NULL;
        }
      }
      else {
        memoizedValue001 = (helpMemoizeTestIsaP(member, type) ? TRUE_WRAPPER : FALSE_WRAPPER);
        if (oMEMOIZATION_ENABLEDpo) {
          memoizedEntry001->value = ((!((boolean)(memoizedValue001))) ? MEMOIZED_NULL_VALUE : memoizedValue001);
        }
      }
      { BooleanWrapper* value001 = ((BooleanWrapper*)(memoizedValue001));

        return (coerceWrappedBooleanToBoolean(value001));
      }
    }
  }
}

Object* helpMemoizeAccessBinaryValue(Object* self, Surrogate* relation) {
  { 
    BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getPropertyTestContext());
    { Object* result = NULL;
      Iterator* iterator = allTrueDependentPropositions(self, relation, false);
      Proposition* proposition = NULL;

      while (iterator->nextP()) {
        proposition = ((Proposition*)(iterator->value));
        if (eqlP((proposition->arguments->theArray)[0], self)) {
          result = valueOf((proposition->arguments->theArray)[1]);
          return (result);
        }
      }
      return (NULL);
    }
  }
}

Object* accessBinaryValue(Object* self, Surrogate* relation) {
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_SPECIALIZE_LOGIC_F_ACCESS_BINARY_VALUE_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_SPECIALIZE_LOGIC_F_ACCESS_BINARY_VALUE_MEMO_TABLE_000, "(:MAX-VALUES 1000 :TIMESTAMPS (:KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_SPECIALIZE_LOGIC_F_ACCESS_BINARY_VALUE_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), self, relation, oCONTEXTo, MEMOIZED_NULL_VALUE, 6);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = helpMemoizeAccessBinaryValue(self, relation);
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Object* value000 = ((Object*)(memoizedValue000));

      return (value000);
    }
  }
}

boolean testCollectionofMemberOfP(Object* member, Surrogate* type) {
  { 
    BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getPropertyTestContext());
    { Proposition* p = NULL;
      Iterator* iter000 = allTrueDependentPropositions(member, SGT_SPECIALIZE_PL_KERNEL_KB_COLLECTIONOF, true);

      for (; iter000->nextP(); ) {
        p = ((Proposition*)(iter000->value));
        if ((!p->deletedP()) &&
            ((oREVERSEPOLARITYpo ? falseP(p) : (trueP(p) ||
            functionWithDefinedValueP(p))))) {
          { Object* collection = p->arguments->last();

            if ((!eqlP(member, collection)) &&
                collectionImpliesCollectionP(((LogicObject*)(collection)), surrogateToDescription(type))) {
              return (true);
            }
          }
        }
      }
    }
    return (false);
  }
}

TransitiveClosureIterator* newTransitiveClosureIterator() {
  { TransitiveClosureIterator* self = NULL;

    self = new TransitiveClosureIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->beenThereList = NULL;
    self->adjacencyIteratorStack = NIL;
    self->filterP = NULL;
    self->allocateAdjacencyIteratorFunction = NULL;
    return (self);
  }
}

Surrogate* TransitiveClosureIterator::primaryType() {
  { TransitiveClosureIterator* self = this;

    return (SGT_SPECIALIZE_LOGIC_TRANSITIVE_CLOSURE_ITERATOR);
  }
}

Object* accessTransitiveClosureIteratorSlotValue(TransitiveClosureIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SPECIALIZE_LOGIC_ALLOCATE_ADJACENCY_ITERATOR_FUNCTION) {
    if (setvalueP) {
      self->allocateAdjacencyIteratorFunction = ((FunctionCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFunctionCode(self->allocateAdjacencyIteratorFunction);
    }
  }
  else if (slotname == SYM_SPECIALIZE_LOGIC_FILTERp) {
    if (setvalueP) {
      self->filterP = ((FunctionCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFunctionCode(self->filterP);
    }
  }
  else if (slotname == SYM_SPECIALIZE_LOGIC_ADJACENCY_ITERATOR_STACK) {
    if (setvalueP) {
      self->adjacencyIteratorStack = ((Cons*)(value));
    }
    else {
      value = self->adjacencyIteratorStack;
    }
  }
  else if (slotname == SYM_SPECIALIZE_LOGIC_BEEN_THERE_LIST) {
    if (setvalueP) {
      self->beenThereList = ((Cons*)(value));
    }
    else {
      value = self->beenThereList;
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

boolean transitiveClosureIteratorDnextP(TransitiveClosureIterator* self) {
  { Object* node = self->value;
    Iterator* adjacencyiterator = ((Iterator*  (*) (Object*))self->allocateAdjacencyIteratorFunction)(node);

    if (((boolean)(adjacencyiterator))) {
      self->adjacencyIteratorStack = cons(adjacencyiterator, self->adjacencyIteratorStack);
    }
    else {
      {
        adjacencyiterator = ((Iterator*)(self->adjacencyIteratorStack->value));
        if (!((boolean)(adjacencyiterator))) {
          return (false);
        }
      }
    }
    for (;;) {
      while (!adjacencyiterator->nextP()) {
        self->adjacencyIteratorStack = self->adjacencyIteratorStack->rest;
        adjacencyiterator = ((Iterator*)(self->adjacencyIteratorStack->value));
        if (!((boolean)(adjacencyiterator))) {
          return (false);
        }
      }
      node = adjacencyiterator->value;
      if ((!self->beenThereList->memberP(node)) &&
          ((self->filterP == NULL) ||
           ((boolean  (*) (Object*))self->filterP)(node))) {
        self->beenThereList = cons(node, self->beenThereList);
        self->value = node;
        return (true);
      }
    }
  }
}

boolean TransitiveClosureIterator::nextP() {
  { TransitiveClosureIterator* self = this;

    return (transitiveClosureIteratorDnextP(self));
  }
}

Iterator* allocateTransitiveClosureIterator(Object* startnode, cpp_function_code allocateadjacencyiterator, cpp_function_code filterfunction) {
  // Return an iterator that generates the transitive
  // closure of applying iterators generated by 'allocateAdjacencyIterator'
  // to 'startNode'.  If 'filterFunction' is non-null, that function is applied
  // as a filter to each node generated (nodes filtered out still generate
  // descendants, but they don't get returned).
  { TransitiveClosureIterator* iterator = newTransitiveClosureIterator();

    iterator->value = startnode;
    iterator->beenThereList = NIL;
    iterator->allocateAdjacencyIteratorFunction = allocateadjacencyiterator;
    iterator->filterP = filterfunction;
    return (iterator);
  }
}

SupportedClosureIterator* newSupportedClosureIterator() {
  { SupportedClosureIterator* self = NULL;

    self = new SupportedClosureIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->beenThereList = NULL;
    self->filterP = NULL;
    self->allocateAdjacencyIteratorFunction = NULL;
    self->adjacencyIteratorStack = NIL;
    return (self);
  }
}

Surrogate* SupportedClosureIterator::primaryType() {
  { SupportedClosureIterator* self = this;

    return (SGT_SPECIALIZE_LOGIC_SUPPORTED_CLOSURE_ITERATOR);
  }
}

SupportedClosureIterator* allocateSupportedClosureIterator(Cons* startnode, cpp_function_code allocateadjacencyiterator, cpp_function_code filterfunction) {
  // Similar to `allocate-transitive-closure-iterator' (which see),
  // but return a SUPPORTED-CLOSURE-ITERATOR instead.
  { SupportedClosureIterator* iterator = newSupportedClosureIterator();

    iterator->value = startnode;
    iterator->beenThereList = NIL;
    iterator->allocateAdjacencyIteratorFunction = allocateadjacencyiterator;
    iterator->filterP = filterfunction;
    return (iterator);
  }
}

boolean SupportedClosureIterator::nextP() {
  { SupportedClosureIterator* self = this;

    if (transitiveClosureIteratorDnextP(self)) {
      self->value = cons(self->value, cons(((TruePropositionsIterator*)(self->adjacencyIteratorStack->value))->truthValue, NIL));
      return (true);
    }
    else {
      return (false);
    }
  }
}

DirectlyLinkedObjectsIterator* newDirectlyLinkedObjectsIterator() {
  { DirectlyLinkedObjectsIterator* self = NULL;

    self = new DirectlyLinkedObjectsIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->equivalentsStack = NULL;
    self->propositionCursor = NULL;
    self->selectionPattern = NULL;
    self->truthValue = NULL;
    self->rootTruthValue = TRUE_TRUTH_VALUE;
    self->inverseP = false;
    return (self);
  }
}

Surrogate* DirectlyLinkedObjectsIterator::primaryType() {
  { DirectlyLinkedObjectsIterator* self = this;

    return (SGT_SPECIALIZE_LOGIC_DIRECTLY_LINKED_OBJECTS_ITERATOR);
  }
}

Object* accessDirectlyLinkedObjectsIteratorSlotValue(DirectlyLinkedObjectsIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SPECIALIZE_LOGIC_INVERSEp) {
    if (setvalueP) {
      self->inverseP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->inverseP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_SPECIALIZE_LOGIC_ROOT_TRUTH_VALUE) {
    if (setvalueP) {
      self->rootTruthValue = ((TruthValue*)(value));
    }
    else {
      value = self->rootTruthValue;
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

boolean DirectlyLinkedObjectsIterator::nextP() {
  { DirectlyLinkedObjectsIterator* self = this;

    { Proposition* proposition = NULL;

      { 
        BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
        if (truePropositionsIteratorDnextP(self)) {
          proposition = ((Proposition*)(self->value));
          self->value = valueOf((self->inverseP ? (proposition->arguments->theArray)[0] : (proposition->arguments->theArray)[1]));
          self->truthValue = conjoinTruthValues(self->truthValue, self->rootTruthValue);
          return (true);
        }
        self->value = NULL;
        return (false);
      }
    }
  }
}

Iterator* allDirectlyLinkedObjects(Object* self, Surrogate* relation, boolean inverseP) {
  { Cons* pattern = (inverseP ? makeRelationPattern2(relation, NULL, valueOf(self)) : makeRelationPattern2(relation, valueOf(self), NULL));
    SequenceIndex* index = selectPropositions(pattern);

    if (emptyPropositionsIndexP(index, self, false)) {
      return (EMPTY_PROPOSITIONS_ITERATOR);
    }
    { DirectlyLinkedObjectsIterator* self000 = newDirectlyLinkedObjectsIterator();

      self000->selectionPattern = pattern;
      self000->propositionCursor = index->allocateIterator();
      self000->inverseP = inverseP;
      { DirectlyLinkedObjectsIterator* value000 = self000;

        return (value000);
      }
    }
  }
}

Iterator* allDirectSupercollections(LogicObject* self, boolean performfilteringP) {
  if (isaP(self, SGT_SPECIALIZE_LOGIC_DESCRIPTION)) {
    deriveDeferredSatelliteRules(((Description*)(self)));
  }
  { Iterator* directlylinkedobjects = allDirectlyLinkedObjects(self, SGT_SPECIALIZE_PL_KERNEL_KB_SUBSET_OF, oREVERSEPOLARITYpo);

    if (!performfilteringP) {
      return (directlylinkedobjects);
    }
    { Cons* directsupers = NIL;
      Cons* equivalents = allEquivalentCollections(self, true);

      if (!(equivalents->rest == NIL)) {
        { LogicObject* e = NULL;
          Cons* iter000 = equivalents;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            e = ((LogicObject*)(iter000->value));
            { LogicObject* parent = NULL;
              Iterator* iter001 = allDirectSupercollections(e, false);

              for (; iter001->nextP(); ) {
                parent = ((LogicObject*)(iter001->value));
                if ((!equivalents->memberP(parent)) &&
                    (!directsupers->memberP(parent))) {
                  directsupers = cons(parent, directsupers);
                }
              }
            }
          }
        }
      }
      else {
        directsupers = ((Cons*)(directlylinkedobjects->consify()));
      }
      return (mostSpecificCollections(directsupers)->allocateIterator());
    }
  }
}

Iterator* allDirectSupercollectionsWithEquivalents(LogicObject* self) {
  return (allDirectSupercollections(self, false));
}

Iterator* allDirectSubcollections(LogicObject* self, boolean performfilteringP) {
  if (isaP(self, SGT_SPECIALIZE_LOGIC_DESCRIPTION)) {
    deriveDeferredSatelliteRules(((Description*)(self)));
  }
  { Iterator* directlylinkedobjects = allDirectlyLinkedObjects(self, SGT_SPECIALIZE_PL_KERNEL_KB_SUBSET_OF, !oREVERSEPOLARITYpo);

    if (!performfilteringP) {
      return (directlylinkedobjects);
    }
    { Cons* directsubs = NIL;
      Cons* equivalents = allEquivalentCollections(self, true);

      if (!(equivalents->rest == NIL)) {
        { LogicObject* e = NULL;
          Cons* iter000 = equivalents;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            e = ((LogicObject*)(iter000->value));
            { LogicObject* child = NULL;
              Iterator* iter001 = allDirectSubcollections(e, false);

              for (; iter001->nextP(); ) {
                child = ((LogicObject*)(iter001->value));
                if ((!equivalents->memberP(child)) &&
                    (!directsubs->memberP(child))) {
                  directsubs = cons(child, directsubs);
                }
              }
            }
          }
        }
      }
      else {
        directsubs = ((Cons*)(directlylinkedobjects->consify()));
      }
      return (mostGeneralCollections(directsubs)->allocateIterator());
    }
  }
}

Iterator* allDirectSubcollectionsWithEquivalents(LogicObject* self) {
  return (allDirectSubcollections(self, false));
}

Iterator* allSupercollections(LogicObject* self) {
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_SPECIALIZE_LOGIC_F_ALL_SUPERCOLLECTIONS_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_SPECIALIZE_LOGIC_F_ALL_SUPERCOLLECTIONS_MEMO_TABLE_000, "(:MAX-VALUES 1000 :TIMESTAMPS (:META-KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_SPECIALIZE_LOGIC_F_ALL_SUPERCOLLECTIONS_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), self, oCONTEXTo, (oREVERSEPOLARITYpo ? TRUE_WRAPPER : FALSE_WRAPPER), MEMOIZED_NULL_VALUE, -1);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = newMemoizableIterator(allocateTransitiveClosureIterator(self, ((cpp_function_code)(&allDirectSupercollectionsWithEquivalents)), NULL));
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Iterator* value000 = cloneMemoizedIterator(((MemoizableIterator*)(memoizedValue000)));

      return (((Iterator*)(value000)));
    }
  }
}

Iterator* allSubcollections(LogicObject* self) {
  return (allocateTransitiveClosureIterator(self, ((cpp_function_code)(&allDirectSubcollectionsWithEquivalents)), NULL));
}

Cons* allIsaCollections(Object* self) {
  { Cons* collections = NIL;

    { Proposition* p = NULL;
      Iterator* iter000 = allTrueDependentPropositions(self, NULL, false);

      for (; iter000->nextP(); ) {
        p = ((Proposition*)(iter000->value));
        if (p->kind == KWD_SPECIALIZE_ISA) {
          collections = cons(getDescription(((Surrogate*)(p->operatoR))), collections);
        }
      }
    }
    { Proposition* p = NULL;
      Iterator* iter001 = allTrueDependentPropositions(self, SGT_SPECIALIZE_PL_KERNEL_KB_MEMBER_OF, false);

      for (; iter001->nextP(); ) {
        p = ((Proposition*)(iter001->value));
        collections = cons((p->arguments->theArray)[1], collections);
      }
    }
    return (collections);
  }
}

Cons* allSupportedNamedSubcollections(LogicObject* self) {
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_SPECIALIZE_LOGIC_F_ALL_SUPPORTED_NAMED_SUBCOLLECTIONS_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_SPECIALIZE_LOGIC_F_ALL_SUPPORTED_NAMED_SUBCOLLECTIONS_MEMO_TABLE_000, "(:MAX-VALUES 1000 :TIMESTAMPS (:META-KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_SPECIALIZE_LOGIC_F_ALL_SUPPORTED_NAMED_SUBCOLLECTIONS_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), self, ((!oDONTUSEDEFAULTKNOWLEDGEpo) ? TRUE_WRAPPER : FALSE_WRAPPER), oCONTEXTo, (oREVERSEPOLARITYpo ? TRUE_WRAPPER : FALSE_WRAPPER), -1);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = helpAllSupportedNamedSubcollections(self);
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { Cons* value000 = ((Cons*)(memoizedValue000));

      return (value000);
    }
  }
}

TruePropositionsIterator* allDirectlyLinkedSubcollections(Object* self) {
  { LogicObject* object = NULL;
    TruthValue* truthvalue = NULL;
    Iterator* iterator = NULL;

    { Surrogate* testValue000 = safePrimaryType(self);

      if (testValue000 == SGT_SPECIALIZE_STELLA_CONS) {
        { Object* self000 = self;
          Cons* self = ((Cons*)(self000));

          object = ((LogicObject*)(self->value));
          truthvalue = ((TruthValue*)(self->rest->value));
        }
      }
      else if (subtypeOfP(testValue000, SGT_SPECIALIZE_LOGIC_LOGIC_OBJECT)) {
        { Object* self001 = self;
          LogicObject* self = ((LogicObject*)(self001));

          object = self;
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    if (isaP(object, SGT_SPECIALIZE_LOGIC_DESCRIPTION)) {
      deriveDeferredSatelliteRules(((Description*)(object)));
    }
    iterator = allDirectlyLinkedObjects(object, SGT_SPECIALIZE_PL_KERNEL_KB_SUBSET_OF, !oREVERSEPOLARITYpo);
    if (subtypeOfP(safePrimaryType(iterator), SGT_SPECIALIZE_LOGIC_DIRECTLY_LINKED_OBJECTS_ITERATOR)) {
      { Iterator* iterator000 = iterator;
        DirectlyLinkedObjectsIterator* iterator = ((DirectlyLinkedObjectsIterator*)(iterator000));

        if (((boolean)(truthvalue))) {
          iterator->rootTruthValue = truthvalue;
        }
        return (iterator);
      }
    }
    else {
      return (NULL);
    }
  }
}

Cons* helpAllSupportedNamedSubcollections(LogicObject* self) {
  { Cons* subcollections = NIL;
    SupportedClosureIterator* closureiterator = allocateSupportedClosureIterator(cons(self, cons(TRUE_TRUTH_VALUE, NIL)), ((cpp_function_code)(&allDirectlyLinkedSubcollections)), NULL);

    { Cons* sub = NULL;
      SupportedClosureIterator* iter000 = closureiterator;
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        sub = ((Cons*)(iter000->value));
        if (isaP(sub->value, SGT_SPECIALIZE_LOGIC_NAMED_DESCRIPTION) &&
            (!(sub->value == self))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(sub, NIL);
              if (subcollections == NIL) {
                subcollections = collect000;
              }
              else {
                addConsToEndOfConsList(subcollections, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(sub, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (subcollections);
  }
}

boolean valueClashesWithSkolemP(Skolem* skolem, Object* value) {
  { Surrogate* type = skolem->skolemType;

    if (!((boolean)(type))) {
      return (false);
    }
    else if (!((((boolean)(oQUERYITERATORo)) &&
        ((boolean)(oQUERYITERATORo->partialMatchStrategy))) ||
        checkStrictTypeP(value, type, true))) {
      return (true);
    }
    else if (literalTypeP(type) &&
        logicalSubtypeOfP(type, SGT_SPECIALIZE_STELLA_NUMBER)) {
      return (!pl_kernel_kb::satisfiesIntervalBoundsP(skolem, ((NumberWrapper*)(value))));
    }
    else {
      return (false);
    }
  }
}

boolean clashesWithFunctionPropositionP(Proposition* nextproposition, Proposition* referenceproposition) {
  { boolean alwaysP000 = true;

    { Object* superarg = NULL;
      Iterator* iter000 = referenceproposition->arguments->butLast();
      Object* subarg = NULL;
      Iterator* iter001 = nextproposition->arguments->butLast();

      for  (; iter000->nextP() &&
                iter001->nextP(); ) {
        superarg = iter000->value;
        subarg = iter001->value;
        if (!eqlP(argumentBoundTo(superarg), valueOf(subarg))) {
          alwaysP000 = false;
          break;
        }
      }
    }
    if (alwaysP000) {
      { Object* lastsupervalue = argumentBoundTo(referenceproposition->arguments->last());
        Object* lastsubvalue = valueOf(nextproposition->arguments->last());

        if (((boolean)(lastsupervalue)) &&
            ((boolean)(lastsubvalue))) {
          if (isaP(lastsubvalue, SGT_SPECIALIZE_LOGIC_SKOLEM)) {
            if (isaP(lastsupervalue, SGT_SPECIALIZE_LOGIC_SKOLEM)) {
              return (false);
            }
            else {
              return (valueClashesWithSkolemP(((Skolem*)(lastsubvalue)), lastsupervalue));
            }
          }
          else {
            if (isaP(lastsupervalue, SGT_SPECIALIZE_LOGIC_SKOLEM)) {
              return (valueClashesWithSkolemP(((Skolem*)(lastsupervalue)), lastsubvalue));
            }
            else {
              return (!eqlP(lastsupervalue, lastsubvalue));
            }
          }
        }
      }
    }
  }
  return (false);
}

ClashingPropositionsIterator* newClashingPropositionsIterator() {
  { ClashingPropositionsIterator* self = NULL;

    self = new ClashingPropositionsIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->equivalentsStack = NULL;
    self->propositionCursor = NULL;
    self->selectionPattern = NULL;
    self->truthValue = NULL;
    self->referenceProposition = NULL;
    return (self);
  }
}

Surrogate* ClashingPropositionsIterator::primaryType() {
  { ClashingPropositionsIterator* self = this;

    return (SGT_SPECIALIZE_LOGIC_CLASHING_PROPOSITIONS_ITERATOR);
  }
}

Object* accessClashingPropositionsIteratorSlotValue(ClashingPropositionsIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SPECIALIZE_LOGIC_REFERENCE_PROPOSITION) {
    if (setvalueP) {
      self->referenceProposition = ((Proposition*)(value));
    }
    else {
      value = self->referenceProposition;
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

boolean ClashingPropositionsIterator::nextP() {
  { ClashingPropositionsIterator* self = this;

    { Proposition* referenceprop = self->referenceProposition;

      while (truePropositionsIteratorDnextP(self)) {
        if (clashesWithFunctionPropositionP(((Proposition*)(self->value)), referenceprop)) {
          return (true);
        }
      }
      self->value = NULL;
      return (false);
    }
  }
}

Iterator* allClashingPropositions(Proposition* self) {
  { boolean dummy1;

    { Vector* arguments = self->arguments;
      Object* lastarg = arguments->last();
      Object* backlinkedarg = NULL;

      arguments->lastSetter(NULL);
      backlinkedarg = selectArgumentWithBacklinks(self, dummy1);
      arguments->lastSetter(lastarg);
      if (!((boolean)(backlinkedarg))) {
        return (EMPTY_PROPOSITIONS_ITERATOR);
      }
      { Cons* pattern = cons(KWD_SPECIALIZE_RELATION, cons(((!((boolean)(NIL))) ? NIL : NIL), cons(((Surrogate*)(self->operatoR)), cons(valueOf(backlinkedarg), NIL))));
        SequenceIndex* index = selectPropositions(pattern);

        if (emptyPropositionsIndexP(index, backlinkedarg, false)) {
          return (EMPTY_PROPOSITIONS_ITERATOR);
        }
        { ClashingPropositionsIterator* self000 = newClashingPropositionsIterator();

          self000->selectionPattern = pattern;
          self000->propositionCursor = index->allocateIterator();
          self000->referenceProposition = self;
          { ClashingPropositionsIterator* value000 = self000;

            return (value000);
          }
        }
      }
    }
  }
}

TaxonomyGraph* oIMPLICATION_SUBSUMPTION_GRAPHo = NULL;

List* relationsWithDescriptions() {
  { List* result = newList();

    { Class* clasS = NULL;
      Iterator* iter000 = allClasses(NULL, false);
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        clasS = ((Class*)(iter000->value));
        if (((boolean)(((NamedDescription*)(dynamicSlotValue(clasS->dynamicSlots, SYM_SPECIALIZE_LOGIC_DESCRIPTION, NULL)))))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(clasS, NIL);
              if (result->theConsList == NIL) {
                result->theConsList = collect000;
              }
              else {
                addConsToEndOfConsList(result->theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(clasS, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    { Slot* slot = NULL;
      Iterator* iter001 = allSlots(NULL, false);
      Cons* collect001 = NULL;

      for  (; iter001->nextP(); ) {
        slot = ((Slot*)(iter001->value));
        if (((boolean)(((NamedDescription*)(dynamicSlotValue(slot->dynamicSlots, SYM_SPECIALIZE_LOGIC_DESCRIPTION, NULL)))))) {
          if (!((boolean)(collect001))) {
            {
              collect001 = cons(slot, NIL);
              if (result->theConsList == NIL) {
                result->theConsList = collect001;
              }
              else {
                addConsToEndOfConsList(result->theConsList, collect001);
              }
            }
          }
          else {
            {
              collect001->rest = cons(slot, NIL);
              collect001 = collect001->rest;
            }
          }
        }
      }
    }
    return (result);
  }
}

void buildSubsumptionTaxonomyGraph() {
  { List* relationswithdescriptions = relationsWithDescriptions();

    { Relation* r = NULL;
      Cons* iter000 = relationswithdescriptions->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        r = ((Relation*)(iter000->value));
        createDescriptionImplicationSubsumptionNode(((NamedDescription*)(dynamicSlotValue(r->dynamicSlots, SYM_SPECIALIZE_LOGIC_DESCRIPTION, NULL))), NULL);
      }
    }
    { Relation* r = NULL;
      Cons* iter001 = relationswithdescriptions->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        r = ((Relation*)(iter001->value));
        { Relation* super = NULL;
          Iterator* iter002 = directSuperrelations(r);

          for (; iter002->nextP(); ) {
            super = ((Relation*)(iter002->value));
            if (relationswithdescriptions->memberP(super)) {
              createTaxonomyLink(oIMPLICATION_SUBSUMPTION_GRAPHo, findDescriptionImplicationSubsumptionNode(((NamedDescription*)(dynamicSlotValue(super->dynamicSlots, SYM_SPECIALIZE_LOGIC_DESCRIPTION, NULL)))), findDescriptionImplicationSubsumptionNode(((NamedDescription*)(dynamicSlotValue(r->dynamicSlots, SYM_SPECIALIZE_LOGIC_DESCRIPTION, NULL)))));
            }
          }
        }
      }
    }
  }
}

void clearImplicationSubsumptionGraph() {
  { Relation* r = NULL;
    Cons* iter000 = relationsWithDescriptions()->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      r = ((Relation*)(iter000->value));
      setDynamicSlotValue(((NamedDescription*)(dynamicSlotValue(r->dynamicSlots, SYM_SPECIALIZE_LOGIC_DESCRIPTION, NULL)))->dynamicSlots, SYM_SPECIALIZE_STELLA_TAXONOMY_NODE, NULL, NULL);
    }
  }
}

void initializeImplicationSubsumptionGraph() {
  clearImplicationSubsumptionGraph();
  oIMPLICATION_SUBSUMPTION_GRAPHo = newTaxonomyGraph();
  finalizeTaxonomyGraph(oIMPLICATION_SUBSUMPTION_GRAPHo);
}

TaxonomyNode* findDescriptionImplicationSubsumptionNode(Description* description) {
  return (((TaxonomyNode*)(dynamicSlotValue(description->dynamicSlots, SYM_SPECIALIZE_STELLA_TAXONOMY_NODE, NULL))));
}

TaxonomyNode* createDescriptionImplicationSubsumptionNode(Description* description, TaxonomyNode* parentnode) {
  { TaxonomyNode* node = createTaxonomyNode(oIMPLICATION_SUBSUMPTION_GRAPHo, parentnode, description, !((boolean)(parentnode)));

    linkTaxonomyNodes(oIMPLICATION_SUBSUMPTION_GRAPHo, parentnode, node);
    setDynamicSlotValue(description->dynamicSlots, SYM_SPECIALIZE_STELLA_TAXONOMY_NODE, node, NULL);
    return (node);
  }
}

TaxonomyNode* findOrCreateDescriptionImplicationSubsumptionNode(Description* description) {
  { TaxonomyNode* result = findDescriptionImplicationSubsumptionNode(description);

    if (((boolean)(result))) {
      return (result);
    }
    return (createDescriptionImplicationSubsumptionNode(description, NULL));
  }
}

Description* createDescriptionForStellaRelationAndAncestors(Relation* self) {
  if (!((boolean)(self))) {
    return (NULL);
  }
  { NamedDescription* description = getDescription(self);
    TaxonomyNode* taxonomynode = findOrCreateDescriptionImplicationSubsumptionNode(description);

    { Relation* super = NULL;
      Iterator* iter000 = directSuperrelations(self);

      for (; iter000->nextP(); ) {
        super = ((Relation*)(iter000->value));
        { Description* superdescription = createDescriptionForStellaRelationAndAncestors(super);
          TaxonomyNode* supertaxonomynode = findDescriptionImplicationSubsumptionNode(superdescription);

          createTaxonomyLink(oIMPLICATION_SUBSUMPTION_GRAPHo, supertaxonomynode, taxonomynode);
        }
      }
    }
    return (description);
  }
}

void addTaxonomyImpliesSubsumesLink(Description* taildescription, Description* headdescription) {
  return;
}

void dropTaxonomyImpliesSubsumesLink(Description* taildescription, Description* headdescription) {
  {
    headdescription = headdescription;
    taildescription = taildescription;
  }
  return;
}

boolean taxonomyImpliesOrIsSubsumedP(Relation* premise, Relation* conclusion) {
  { NamedDescription* premisedescription = ((NamedDescription*)(dynamicSlotValue(premise->dynamicSlots, SYM_SPECIALIZE_LOGIC_DESCRIPTION, NULL)));
    Description* conclusiondescription = NULL;

    if ((!((boolean)(premisedescription))) ||
        (!((boolean)(findDescriptionImplicationSubsumptionNode(premisedescription))))) {
      premisedescription = ((NamedDescription*)(createDescriptionForStellaRelationAndAncestors(premise)));
    }
    conclusiondescription = ((NamedDescription*)(dynamicSlotValue(conclusion->dynamicSlots, SYM_SPECIALIZE_LOGIC_DESCRIPTION, NULL)));
    if (!((boolean)(conclusiondescription))) {
      return (false);
    }
    if (!((boolean)(findDescriptionImplicationSubsumptionNode(conclusiondescription)))) {
      throw *newStellaException("'taxonomy-implies-or-is-subsumed?' conclusionDescription should have taxonomy-node");
    }
    return (taxonomySubnodeOfP(findDescriptionImplicationSubsumptionNode(premisedescription), findDescriptionImplicationSubsumptionNode(conclusiondescription)));
  }
}

void helpStartupSpecialize1() {
  {
    SGT_SPECIALIZE_LOGIC_ABSTRACT_PROPOSITIONS_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("ABSTRACT-PROPOSITIONS-ITERATOR", NULL, 1)));
    SYM_SPECIALIZE_LOGIC_SELECTION_PATTERN = ((Symbol*)(internRigidSymbolWrtModule("SELECTION-PATTERN", NULL, 0)));
    SYM_SPECIALIZE_LOGIC_PROPOSITION_CURSOR = ((Symbol*)(internRigidSymbolWrtModule("PROPOSITION-CURSOR", NULL, 0)));
    SYM_SPECIALIZE_LOGIC_EQUIVALENTS_STACK = ((Symbol*)(internRigidSymbolWrtModule("EQUIVALENTS-STACK", NULL, 0)));
    SGT_SPECIALIZE_LOGIC_TRUE_PROPOSITIONS_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("TRUE-PROPOSITIONS-ITERATOR", NULL, 1)));
    SYM_SPECIALIZE_LOGIC_TRUTH_VALUE = ((Symbol*)(internRigidSymbolWrtModule("TRUTH-VALUE", NULL, 0)));
    SGT_SPECIALIZE_LOGIC_SPECIALIZING_PROPOSITIONS_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("SPECIALIZING-PROPOSITIONS-ITERATOR", NULL, 1)));
    SYM_SPECIALIZE_LOGIC_SPECIALIZING_RELATIONS = ((Symbol*)(internRigidSymbolWrtModule("SPECIALIZING-RELATIONS", NULL, 0)));
    SGT_SPECIALIZE_LOGIC_DESCRIPTION_EXTENSION_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION-EXTENSION-ITERATOR", NULL, 1)));
    KWD_SPECIALIZE_RELATION = ((Keyword*)(internRigidSymbolWrtModule("RELATION", NULL, 2)));
    KWD_SPECIALIZE_DEPENDENTS = ((Keyword*)(internRigidSymbolWrtModule("DEPENDENTS", NULL, 2)));
    KWD_SPECIALIZE_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    SGT_SPECIALIZE_PL_KERNEL_KB_HOLDS = ((Surrogate*)(internRigidSymbolWrtModule("HOLDS", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALIZE_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    KWD_SPECIALIZE_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SGT_SPECIALIZE_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
    SGT_SPECIALIZE_LOGIC_F_TEST_PROPERTYp_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-TEST-PROPERTY?-MEMO-TABLE-000", NULL, 1)));
    SGT_SPECIALIZE_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
    SGT_SPECIALIZE_PL_KERNEL_KB_CLASS = ((Surrogate*)(internRigidSymbolWrtModule("CLASS", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALIZE_PL_KERNEL_KB_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("RELATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALIZE_PL_KERNEL_KB_FUNCTION = ((Surrogate*)(internRigidSymbolWrtModule("FUNCTION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALIZE_PL_KERNEL_KB_COLLECTION = ((Surrogate*)(internRigidSymbolWrtModule("COLLECTION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALIZE_PL_KERNEL_KB_SET = ((Surrogate*)(internRigidSymbolWrtModule("SET", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALIZE_LOGIC_F_TEST_ISAp_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-TEST-ISA?-MEMO-TABLE-000", NULL, 1)));
    SGT_SPECIALIZE_LOGIC_F_TEST_ISAp_MEMO_TABLE_001 = ((Surrogate*)(internRigidSymbolWrtModule("F-TEST-ISA?-MEMO-TABLE-001", NULL, 1)));
    SGT_SPECIALIZE_LOGIC_F_ACCESS_BINARY_VALUE_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-ACCESS-BINARY-VALUE-MEMO-TABLE-000", NULL, 1)));
    SGT_SPECIALIZE_PL_KERNEL_KB_COLLECTIONOF = ((Surrogate*)(internRigidSymbolWrtModule("COLLECTIONOF", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALIZE_LOGIC_TRANSITIVE_CLOSURE_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("TRANSITIVE-CLOSURE-ITERATOR", NULL, 1)));
    SYM_SPECIALIZE_LOGIC_ALLOCATE_ADJACENCY_ITERATOR_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("ALLOCATE-ADJACENCY-ITERATOR-FUNCTION", NULL, 0)));
    SYM_SPECIALIZE_LOGIC_FILTERp = ((Symbol*)(internRigidSymbolWrtModule("FILTER?", NULL, 0)));
    SYM_SPECIALIZE_LOGIC_ADJACENCY_ITERATOR_STACK = ((Symbol*)(internRigidSymbolWrtModule("ADJACENCY-ITERATOR-STACK", NULL, 0)));
    SYM_SPECIALIZE_LOGIC_BEEN_THERE_LIST = ((Symbol*)(internRigidSymbolWrtModule("BEEN-THERE-LIST", NULL, 0)));
    SGT_SPECIALIZE_LOGIC_SUPPORTED_CLOSURE_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("SUPPORTED-CLOSURE-ITERATOR", NULL, 1)));
    SGT_SPECIALIZE_LOGIC_DIRECTLY_LINKED_OBJECTS_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("DIRECTLY-LINKED-OBJECTS-ITERATOR", NULL, 1)));
    SYM_SPECIALIZE_LOGIC_INVERSEp = ((Symbol*)(internRigidSymbolWrtModule("INVERSE?", NULL, 0)));
    SYM_SPECIALIZE_LOGIC_ROOT_TRUTH_VALUE = ((Symbol*)(internRigidSymbolWrtModule("ROOT-TRUTH-VALUE", NULL, 0)));
    SGT_SPECIALIZE_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
    SGT_SPECIALIZE_PL_KERNEL_KB_SUBSET_OF = ((Surrogate*)(internRigidSymbolWrtModule("SUBSET-OF", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALIZE_LOGIC_F_ALL_SUPERCOLLECTIONS_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-ALL-SUPERCOLLECTIONS-MEMO-TABLE-000", NULL, 1)));
    SGT_SPECIALIZE_PL_KERNEL_KB_MEMBER_OF = ((Surrogate*)(internRigidSymbolWrtModule("MEMBER-OF", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALIZE_LOGIC_F_ALL_SUPPORTED_NAMED_SUBCOLLECTIONS_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-ALL-SUPPORTED-NAMED-SUBCOLLECTIONS-MEMO-TABLE-000", NULL, 1)));
    SGT_SPECIALIZE_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    SGT_SPECIALIZE_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
    SGT_SPECIALIZE_STELLA_NUMBER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER", getStellaModule("/STELLA", true), 1)));
    SGT_SPECIALIZE_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", NULL, 1)));
    SGT_SPECIALIZE_LOGIC_CLASHING_PROPOSITIONS_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("CLASHING-PROPOSITIONS-ITERATOR", NULL, 1)));
    SYM_SPECIALIZE_LOGIC_REFERENCE_PROPOSITION = ((Symbol*)(internRigidSymbolWrtModule("REFERENCE-PROPOSITION", NULL, 0)));
    SYM_SPECIALIZE_LOGIC_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 0)));
    SYM_SPECIALIZE_STELLA_TAXONOMY_NODE = ((Symbol*)(internRigidSymbolWrtModule("TAXONOMY-NODE", getStellaModule("/STELLA", true), 0)));
    SYM_SPECIALIZE_LOGIC_STARTUP_SPECIALIZE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-SPECIALIZE", NULL, 0)));
    SYM_SPECIALIZE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupSpecialize2() {
  {
    { Class* clasS = defineClassFromStringifiedSource("ABSTRACT-PROPOSITIONS-ITERATOR", "(DEFCLASS ABSTRACT-PROPOSITIONS-ITERATOR (ITERATOR) :DOCUMENTATION \"Iterator class that can generate sets of propositions matching\nits `selection-pattern'.\" :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :SLOTS ((SELECTION-PATTERN :TYPE SELECTION-PATTERN) (PROPOSITION-CURSOR :TYPE (ITERATOR OF PROPOSITION)) (EQUIVALENTS-STACK :TYPE CONS :INITIALLY NULL)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newAbstractPropositionsIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessAbstractPropositionsIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("TRUE-PROPOSITIONS-ITERATOR", "(DEFCLASS TRUE-PROPOSITIONS-ITERATOR (ABSTRACT-PROPOSITIONS-ITERATOR) :DOCUMENTATION \"Iterator class that can generate sets of true propositions\nmatching its `selection-pattern'.\" :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :SLOTS ((TRUTH-VALUE :TYPE TRUTH-VALUE :DOCUMENTATION \"Truth-value of the most recently generated proposition (or\nprojected argument thereof).  This truth value is not necessarily the strictest\nand might have involved defaults.\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newTruePropositionsIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTruePropositionsIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("SPECIALIZING-PROPOSITIONS-ITERATOR", "(DEFCLASS SPECIALIZING-PROPOSITIONS-ITERATOR (TRUE-PROPOSITIONS-ITERATOR) :DOCUMENTATION \"Iterator class that can generate sets of true propositions\nmatching its `selection-pattern' or a more specific pattern that substitutes\none of the relations in `specializing-relations'.\" :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :SLOTS ((SPECIALIZING-RELATIONS :TYPE (CONS OF CONS) :INITIALLY NULL)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newSpecializingPropositionsIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessSpecializingPropositionsIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("TRANSITIVE-CLOSURE-ITERATOR", "(DEFCLASS TRANSITIVE-CLOSURE-ITERATOR (ITERATOR) :DOCUMENTATION \"Iterator that visits all nodes reachable using an\nembedded adjacency function.\" :SLOTS ((ALLOCATE-ADJACENCY-ITERATOR-FUNCTION :TYPE FUNCTION-CODE) (FILTER? :TYPE FUNCTION-CODE) (ADJACENCY-ITERATOR-STACK :TYPE (CONS OF ITERATOR) :INITIALLY NIL) (BEEN-THERE-LIST :TYPE CONS)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newTransitiveClosureIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTransitiveClosureIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("SUPPORTED-CLOSURE-ITERATOR", "(DEFCLASS SUPPORTED-CLOSURE-ITERATOR (TRANSITIVE-CLOSURE-ITERATOR) :DOCUMENTATION \"Iterator that visits all objects reachable via true link propositions\ngenerated by an embedded link proposition iterator.  Each new object reached\nis represented as an `(<object> <truth-value>)' pair, where <truth-value> is\nthe cumulative truth value of the links followed from the start to reach it.\nThe embedded `allocate-adjacency-iterator-function' needs to be able to take\nan `(<object> <truth-value>)' pair as an argument which is different than the\nrequirement for TRANSITIVE-CLOSURE-ITERATOR's.\" :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :SLOTS ((ADJACENCY-ITERATOR-STACK :TYPE (CONS OF TRUE-PROPOSITIONS-ITERATOR))))");

      clasS->classConstructorCode = ((cpp_function_code)(&newSupportedClosureIterator));
    }
    { Class* clasS = defineClassFromStringifiedSource("DIRECTLY-LINKED-OBJECTS-ITERATOR", "(DEFCLASS DIRECTLY-LINKED-OBJECTS-ITERATOR (TRUE-PROPOSITIONS-ITERATOR) :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :SLOTS ((INVERSE? :TYPE BOOLEAN) (ROOT-TRUTH-VALUE :TYPE TRUTH-VALUE :INITIALLY TRUE-TRUTH-VALUE)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newDirectlyLinkedObjectsIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessDirectlyLinkedObjectsIteratorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("CLASHING-PROPOSITIONS-ITERATOR", "(DEFCLASS CLASHING-PROPOSITIONS-ITERATOR (TRUE-PROPOSITIONS-ITERATOR) :PARAMETERS ((ANY-VALUE :TYPE PROPOSITION)) :SLOTS ((REFERENCE-PROPOSITION :TYPE PROPOSITION)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newClashingPropositionsIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessClashingPropositionsIteratorSlotValue));
    }
  }
}

void helpStartupSpecialize3() {
  {
    defineFunctionObject("PROPOSITIONS-ITERATOR-TRUTH-VALUE", "(DEFUN (PROPOSITIONS-ITERATOR-TRUTH-VALUE TRUTH-VALUE) ((SELF (ITERATOR OF PROPOSITION))))", ((cpp_function_code)(&propositionsIteratorTruthValue)), NULL);
    defineFunctionObject("NEXT-EQUIVALENT-SELECTION-PATTERN", "(DEFUN (NEXT-EQUIVALENT-SELECTION-PATTERN CONS) ((SELF ABSTRACT-PROPOSITIONS-ITERATOR)))", ((cpp_function_code)(&nextEquivalentSelectionPattern)), NULL);
    defineFunctionObject("PROPOSITION-TRUTH-VALUE", "(DEFUN (PROPOSITION-TRUTH-VALUE TRUTH-VALUE) ((PROPOSITION PROPOSITION)))", ((cpp_function_code)(&propositionTruthValue)), NULL);
    defineFunctionObject("TRUE-PROPOSITION?", "(DEFUN (TRUE-PROPOSITION? BOOLEAN) ((PROPOSITION PROPOSITION)) :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (AND (NOT (DELETED? PROPOSITION)) (CHOOSE *REVERSEPOLARITY?* (FALSE? PROPOSITION) (OR (TRUE? PROPOSITION) (FUNCTION-WITH-DEFINED-VALUE? PROPOSITION))))))", ((cpp_function_code)(&truePropositionP)), NULL);
    defineFunctionObject("TRUE-PROPOSITIONS-ITERATOR.NEXT?", "(DEFUN (TRUE-PROPOSITIONS-ITERATOR.NEXT? BOOLEAN) ((SELF TRUE-PROPOSITIONS-ITERATOR)) :PUBLIC? TRUE)", ((cpp_function_code)(&truePropositionsIteratorDnextP)), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF TRUE-PROPOSITIONS-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&TruePropositionsIterator::nextP))), NULL);
    defineFunctionObject("SPECIALIZING-PROPOSITIONS-ITERATOR.NEXT?", "(DEFUN (SPECIALIZING-PROPOSITIONS-ITERATOR.NEXT? BOOLEAN) ((SELF SPECIALIZING-PROPOSITIONS-ITERATOR)))", ((cpp_function_code)(&specializingPropositionsIteratorDnextP)), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF SPECIALIZING-PROPOSITIONS-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&SpecializingPropositionsIterator::nextP))), NULL);
    defineFunctionObject("EMPTY-PROPOSITIONS-INDEX?", "(DEFUN (EMPTY-PROPOSITIONS-INDEX? BOOLEAN) ((INDEX PROPOSITIONS-INDEX) (PRIMARYKEY OBJECT) (SPECIALIZE? BOOLEAN)))", ((cpp_function_code)(&emptyPropositionsIndexP)), NULL);
    defineFunctionObject("ALL-TRUE-DEPENDENT-PROPOSITIONS", "(DEFUN (ALL-TRUE-DEPENDENT-PROPOSITIONS (ITERATOR OF PROPOSITION)) ((SELF OBJECT) (RELATION SURROGATE) (SPECIALIZE? BOOLEAN)))", ((cpp_function_code)(&allTrueDependentPropositions)), NULL);
    defineFunctionObject("ALL-TRUE-DEPENDENT-ISA-PROPOSITIONS", "(DEFUN (ALL-TRUE-DEPENDENT-ISA-PROPOSITIONS (ITERATOR OF PROPOSITION)) ((SELF OBJECT)))", ((cpp_function_code)(&allTrueDependentIsaPropositions)), NULL);
    defineFunctionObject("RELATION-AND-ARGUMENTS-UNIFY?", "(DEFUN (RELATION-AND-ARGUMENTS-UNIFY? BOOLEAN) ((SUBPROPOSITION PROPOSITION) (REFERENCEPROPOSITION PROPOSITION) (DONTUNIFYRELATION? BOOLEAN)))", ((cpp_function_code)(&relationAndArgumentsUnifyP)), NULL);
    defineFunctionObject("ARGUMENTS-UNIFY-WITH-ARGUMENTS?", "(DEFUN (ARGUMENTS-UNIFY-WITH-ARGUMENTS? BOOLEAN) ((SUBPROPOSITION PROPOSITION) (REFERENCEPROPOSITION PROPOSITION)) :DOCUMENTATION \"Return TRUE if the arguments in proposition 'subProposition' unify with\nthose in 'referenceProposition'.  If one of the propositions is a HOLDS, the other one\nhas to be also for unification to succeed.\" :GLOBALLY-INLINE? TRUE (RETURN (RELATION-AND-ARGUMENTS-UNIFY? SUBPROPOSITION REFERENCEPROPOSITION TRUE)))", ((cpp_function_code)(&argumentsUnifyWithArgumentsP)), NULL);
    defineFunctionObject("ARGUMENTS-EQUAL-ARGUMENTS?", "(DEFUN (ARGUMENTS-EQUAL-ARGUMENTS? BOOLEAN) ((SUBPROPOSITION PROPOSITION) (REFERENCEPROPOSITION PROPOSITION)))", ((cpp_function_code)(&argumentsEqualArgumentsP)), NULL);
    defineFunctionObject("ARGUMENTS-MATCH-ARGUMENTS?", "(DEFUN (ARGUMENTS-MATCH-ARGUMENTS? BOOLEAN) ((SUBPROPOSITION PROPOSITION) (REFERENCEPROPOSITION PROPOSITION)))", ((cpp_function_code)(&argumentsMatchArgumentsP)), NULL);
    defineFunctionObject("PREFIX-ARGUMENTS-EQUAL-ARGUMENTS?", "(DEFUN (PREFIX-ARGUMENTS-EQUAL-ARGUMENTS? BOOLEAN) ((SUBPROPOSITION PROPOSITION) (REFERENCEPROPOSITION PROPOSITION)))", ((cpp_function_code)(&prefixArgumentsEqualArgumentsP)), NULL);
    defineFunctionObject("ALL-MATCHING-PROPOSITIONS", "(DEFUN (ALL-MATCHING-PROPOSITIONS (ITERATOR OF PROPOSITION)) ((SELF PROPOSITION)))", ((cpp_function_code)(&allMatchingPropositions)), NULL);
    defineFunctionObject("ALL-PROPOSITIONS-MATCHING-ARGUMENTS", "(DEFUN (ALL-PROPOSITIONS-MATCHING-ARGUMENTS (CONS OF PROPOSITION)) ((ARGUMENTS CONS) (RELATION SURROGATE) (SPECIALIZE? BOOLEAN)))", ((cpp_function_code)(&allPropositionsMatchingArguments)), NULL);
    defineFunctionObject("ALL-DEFINING-PROPOSITIONS", "(DEFUN (ALL-DEFINING-PROPOSITIONS (CONS OF PROPOSITION)) ((OUTPUTARGUMENT OBJECT) (RELATION SURROGATE) (SPECIALIZE? BOOLEAN)))", ((cpp_function_code)(&allDefiningPropositions)), NULL);
    defineFunctionObject("TRUE-TO-CONCEIVED-PROPOSITIONS-ITERATOR", "(DEFUN (TRUE-TO-CONCEIVED-PROPOSITIONS-ITERATOR (ITERATOR OF PROPOSITION)) ((SELF (ITERATOR OF PROPOSITION))))", ((cpp_function_code)(&trueToConceivedPropositionsIterator)), NULL);
    defineFunctionObject("HELP-MEMOIZE-TEST-PROPERTY?", "(DEFUN (HELP-MEMOIZE-TEST-PROPERTY? BOOLEAN) ((SELF OBJECT) (RELATION SURROGATE)))", ((cpp_function_code)(&helpMemoizeTestPropertyP)), NULL);
    defineFunctionObject("TEST-PROPERTY?", "(DEFUN (TEST-PROPERTY? BOOLEAN) ((SELF OBJECT) (RELATION SURROGATE)) :PUBLIC? TRUE)", ((cpp_function_code)(&testPropertyP)), NULL);
    defineFunctionObject("HELP-MEMOIZE-TEST-ISA?", "(DEFUN (HELP-MEMOIZE-TEST-ISA? BOOLEAN) ((MEMBER OBJECT) (TYPE SURROGATE)))", ((cpp_function_code)(&helpMemoizeTestIsaP)), NULL);
    defineFunctionObject("TEST-ISA?", "(DEFUN (TEST-ISA? BOOLEAN) ((MEMBER OBJECT) (TYPE SURROGATE)) :PUBLIC? TRUE)", ((cpp_function_code)(&testIsaP)), NULL);
    defineFunctionObject("HELP-MEMOIZE-ACCESS-BINARY-VALUE", "(DEFUN (HELP-MEMOIZE-ACCESS-BINARY-VALUE OBJECT) ((SELF OBJECT) (RELATION SURROGATE)))", ((cpp_function_code)(&helpMemoizeAccessBinaryValue)), NULL);
    defineFunctionObject("ACCESS-BINARY-VALUE", "(DEFUN (ACCESS-BINARY-VALUE OBJECT) ((SELF OBJECT) (RELATION SURROGATE)) :PUBLIC? TRUE)", ((cpp_function_code)(&accessBinaryValue)), NULL);
    defineFunctionObject("TEST-COLLECTIONOF-MEMBER-OF?", "(DEFUN (TEST-COLLECTIONOF-MEMBER-OF? BOOLEAN) ((MEMBER OBJECT) (TYPE SURROGATE)))", ((cpp_function_code)(&testCollectionofMemberOfP)), NULL);
    defineFunctionObject("TRANSITIVE-CLOSURE-ITERATOR.NEXT?", "(DEFUN (TRANSITIVE-CLOSURE-ITERATOR.NEXT? BOOLEAN) ((SELF TRANSITIVE-CLOSURE-ITERATOR)))", ((cpp_function_code)(&transitiveClosureIteratorDnextP)), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF TRANSITIVE-CLOSURE-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&TransitiveClosureIterator::nextP))), NULL);
    defineFunctionObject("ALLOCATE-TRANSITIVE-CLOSURE-ITERATOR", "(DEFUN (ALLOCATE-TRANSITIVE-CLOSURE-ITERATOR ITERATOR) ((STARTNODE OBJECT) (ALLOCATEADJACENCYITERATOR FUNCTION-CODE) (FILTERFUNCTION FUNCTION-CODE)) :DOCUMENTATION \"Return an iterator that generates the transitive\nclosure of applying iterators generated by 'allocateAdjacencyIterator'\nto 'startNode'.  If 'filterFunction' is non-null, that function is applied\nas a filter to each node generated (nodes filtered out still generate\ndescendants, but they don't get returned).\" :PUBLIC? TRUE)", ((cpp_function_code)(&allocateTransitiveClosureIterator)), NULL);
    defineFunctionObject("ALLOCATE-SUPPORTED-CLOSURE-ITERATOR", "(DEFUN (ALLOCATE-SUPPORTED-CLOSURE-ITERATOR SUPPORTED-CLOSURE-ITERATOR) ((STARTNODE CONS) (ALLOCATEADJACENCYITERATOR FUNCTION-CODE) (FILTERFUNCTION FUNCTION-CODE)) :DOCUMENTATION \"Similar to `allocate-transitive-closure-iterator' (which see),\nbut return a SUPPORTED-CLOSURE-ITERATOR instead.\" :PUBLIC? TRUE)", ((cpp_function_code)(&allocateSupportedClosureIterator)), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF SUPPORTED-CLOSURE-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&SupportedClosureIterator::nextP))), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF DIRECTLY-LINKED-OBJECTS-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&DirectlyLinkedObjectsIterator::nextP))), NULL);
    defineFunctionObject("ALL-DIRECTLY-LINKED-OBJECTS", "(DEFUN (ALL-DIRECTLY-LINKED-OBJECTS ITERATOR) ((SELF OBJECT) (RELATION SURROGATE) (INVERSE? BOOLEAN)))", ((cpp_function_code)(&allDirectlyLinkedObjects)), NULL);
    defineFunctionObject("ALL-DIRECT-SUPERCOLLECTIONS", "(DEFUN (ALL-DIRECT-SUPERCOLLECTIONS (ITERATOR OF LOGIC-OBJECT)) ((SELF LOGIC-OBJECT) (PERFORMFILTERING? BOOLEAN)))", ((cpp_function_code)(&allDirectSupercollections)), NULL);
    defineFunctionObject("ALL-DIRECT-SUPERCOLLECTIONS-WITH-EQUIVALENTS", "(DEFUN (ALL-DIRECT-SUPERCOLLECTIONS-WITH-EQUIVALENTS (ITERATOR OF LOGIC-OBJECT)) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&allDirectSupercollectionsWithEquivalents)), NULL);
    defineFunctionObject("ALL-DIRECT-SUBCOLLECTIONS", "(DEFUN (ALL-DIRECT-SUBCOLLECTIONS (ITERATOR OF LOGIC-OBJECT)) ((SELF LOGIC-OBJECT) (PERFORMFILTERING? BOOLEAN)))", ((cpp_function_code)(&allDirectSubcollections)), NULL);
    defineFunctionObject("ALL-DIRECT-SUBCOLLECTIONS-WITH-EQUIVALENTS", "(DEFUN (ALL-DIRECT-SUBCOLLECTIONS-WITH-EQUIVALENTS (ITERATOR OF LOGIC-OBJECT)) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&allDirectSubcollectionsWithEquivalents)), NULL);
    defineFunctionObject("ALL-SUPERCOLLECTIONS", "(DEFUN (ALL-SUPERCOLLECTIONS (ITERATOR OF LOGIC-OBJECT)) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&allSupercollections)), NULL);
    defineFunctionObject("ALL-SUBCOLLECTIONS", "(DEFUN (ALL-SUBCOLLECTIONS (ITERATOR OF LOGIC-OBJECT)) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&allSubcollections)), NULL);
    defineFunctionObject("ALL-ISA-COLLECTIONS", "(DEFUN (ALL-ISA-COLLECTIONS (CONS OF LOGIC-OBJECT)) ((SELF OBJECT)))", ((cpp_function_code)(&allIsaCollections)), NULL);
    defineFunctionObject("ALL-SUPPORTED-NAMED-SUBCOLLECTIONS", "(DEFUN (ALL-SUPPORTED-NAMED-SUBCOLLECTIONS (CONS OF CONS)) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&allSupportedNamedSubcollections)), NULL);
    defineFunctionObject("ALL-DIRECTLY-LINKED-SUBCOLLECTIONS", "(DEFUN (ALL-DIRECTLY-LINKED-SUBCOLLECTIONS TRUE-PROPOSITIONS-ITERATOR) ((SELF OBJECT)))", ((cpp_function_code)(&allDirectlyLinkedSubcollections)), NULL);
    defineFunctionObject("HELP-ALL-SUPPORTED-NAMED-SUBCOLLECTIONS", "(DEFUN (HELP-ALL-SUPPORTED-NAMED-SUBCOLLECTIONS (CONS OF CONS)) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&helpAllSupportedNamedSubcollections)), NULL);
    defineFunctionObject("VALUE-CLASHES-WITH-SKOLEM?", "(DEFUN (VALUE-CLASHES-WITH-SKOLEM? BOOLEAN) ((SKOLEM SKOLEM) (VALUE OBJECT)))", ((cpp_function_code)(&valueClashesWithSkolemP)), NULL);
    defineFunctionObject("CLASHES-WITH-FUNCTION-PROPOSITION?", "(DEFUN (CLASHES-WITH-FUNCTION-PROPOSITION? BOOLEAN) ((NEXTPROPOSITION PROPOSITION) (REFERENCEPROPOSITION PROPOSITION)))", ((cpp_function_code)(&clashesWithFunctionPropositionP)), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF CLASHING-PROPOSITIONS-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&ClashingPropositionsIterator::nextP))), NULL);
    defineFunctionObject("ALL-CLASHING-PROPOSITIONS", "(DEFUN (ALL-CLASHING-PROPOSITIONS (ITERATOR OF PROPOSITION)) ((SELF PROPOSITION)))", ((cpp_function_code)(&allClashingPropositions)), NULL);
    defineFunctionObject("RELATIONS-WITH-DESCRIPTIONS", "(DEFUN (RELATIONS-WITH-DESCRIPTIONS (LIST OF RELATION)) ())", ((cpp_function_code)(&relationsWithDescriptions)), NULL);
    defineFunctionObject("BUILD-SUBSUMPTION-TAXONOMY-GRAPH", "(DEFUN BUILD-SUBSUMPTION-TAXONOMY-GRAPH ())", ((cpp_function_code)(&buildSubsumptionTaxonomyGraph)), NULL);
    defineFunctionObject("CLEAR-IMPLICATION-SUBSUMPTION-GRAPH", "(DEFUN CLEAR-IMPLICATION-SUBSUMPTION-GRAPH ())", ((cpp_function_code)(&clearImplicationSubsumptionGraph)), NULL);
    defineFunctionObject("INITIALIZE-IMPLICATION-SUBSUMPTION-GRAPH", "(DEFUN INITIALIZE-IMPLICATION-SUBSUMPTION-GRAPH ())", ((cpp_function_code)(&initializeImplicationSubsumptionGraph)), NULL);
    defineFunctionObject("FIND-DESCRIPTION-IMPLICATION-SUBSUMPTION-NODE", "(DEFUN (FIND-DESCRIPTION-IMPLICATION-SUBSUMPTION-NODE TAXONOMY-NODE) ((DESCRIPTION DESCRIPTION)))", ((cpp_function_code)(&findDescriptionImplicationSubsumptionNode)), NULL);
    defineFunctionObject("CREATE-DESCRIPTION-IMPLICATION-SUBSUMPTION-NODE", "(DEFUN (CREATE-DESCRIPTION-IMPLICATION-SUBSUMPTION-NODE TAXONOMY-NODE) ((DESCRIPTION DESCRIPTION) (PARENTNODE TAXONOMY-NODE)))", ((cpp_function_code)(&createDescriptionImplicationSubsumptionNode)), NULL);
    defineFunctionObject("FIND-OR-CREATE-DESCRIPTION-IMPLICATION-SUBSUMPTION-NODE", "(DEFUN (FIND-OR-CREATE-DESCRIPTION-IMPLICATION-SUBSUMPTION-NODE TAXONOMY-NODE) ((DESCRIPTION DESCRIPTION)))", ((cpp_function_code)(&findOrCreateDescriptionImplicationSubsumptionNode)), NULL);
    defineFunctionObject("CREATE-DESCRIPTION-FOR-STELLA-RELATION-AND-ANCESTORS", "(DEFUN (CREATE-DESCRIPTION-FOR-STELLA-RELATION-AND-ANCESTORS DESCRIPTION) ((SELF RELATION)))", ((cpp_function_code)(&createDescriptionForStellaRelationAndAncestors)), NULL);
    defineFunctionObject("ADD-TAXONOMY-IMPLIES-SUBSUMES-LINK", "(DEFUN ADD-TAXONOMY-IMPLIES-SUBSUMES-LINK ((TAILDESCRIPTION DESCRIPTION) (HEADDESCRIPTION DESCRIPTION)))", ((cpp_function_code)(&addTaxonomyImpliesSubsumesLink)), NULL);
    defineFunctionObject("DROP-TAXONOMY-IMPLIES-SUBSUMES-LINK", "(DEFUN DROP-TAXONOMY-IMPLIES-SUBSUMES-LINK ((TAILDESCRIPTION DESCRIPTION) (HEADDESCRIPTION DESCRIPTION)))", ((cpp_function_code)(&dropTaxonomyImpliesSubsumesLink)), NULL);
    defineFunctionObject("TAXONOMY-IMPLIES-OR-IS-SUBSUMED?", "(DEFUN (TAXONOMY-IMPLIES-OR-IS-SUBSUMED? BOOLEAN) ((PREMISE RELATION) (CONCLUSION RELATION)))", ((cpp_function_code)(&taxonomyImpliesOrIsSubsumedP)), NULL);
    defineFunctionObject("STARTUP-SPECIALIZE", "(DEFUN STARTUP-SPECIALIZE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupSpecialize)), NULL);
    { MethodSlot* function = lookupFunction(SYM_SPECIALIZE_LOGIC_STARTUP_SPECIALIZE);

      setDynamicSlotValue(function->dynamicSlots, SYM_SPECIALIZE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupSpecialize"), NULL_STRING_WRAPPER);
    }
  }
}

void startupSpecialize() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupSpecialize1();
    }
    if (currentStartupTimePhaseP(4)) {
      EMPTY_PROPOSITIONS_ITERATOR = newTruePropositionsIterator();
    }
    if (currentStartupTimePhaseP(5)) {
      helpStartupSpecialize2();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupSpecialize3();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFCONSTANT EMPTY-PROPOSITIONS-ITERATOR (ITERATOR OF PROPOSITION) (NEW TRUE-PROPOSITIONS-ITERATOR) :DOCUMENTATION \"This iterator returns no values whenever its called.\")", &EMPTY_PROPOSITIONS_ITERATOR);
      defineGlobalVariableObject("(DEFGLOBAL *IMPLICATION-SUBSUMPTION-GRAPH* TAXONOMY-GRAPH NULL)", &oIMPLICATION_SUBSUMPTION_GRAPHo);
      initializeImplicationSubsumptionGraph();
    }
  }
}

Surrogate* SGT_SPECIALIZE_LOGIC_ABSTRACT_PROPOSITIONS_ITERATOR = NULL;

Symbol* SYM_SPECIALIZE_LOGIC_SELECTION_PATTERN = NULL;

Symbol* SYM_SPECIALIZE_LOGIC_PROPOSITION_CURSOR = NULL;

Symbol* SYM_SPECIALIZE_LOGIC_EQUIVALENTS_STACK = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_TRUE_PROPOSITIONS_ITERATOR = NULL;

Symbol* SYM_SPECIALIZE_LOGIC_TRUTH_VALUE = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_SPECIALIZING_PROPOSITIONS_ITERATOR = NULL;

Symbol* SYM_SPECIALIZE_LOGIC_SPECIALIZING_RELATIONS = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_DESCRIPTION_EXTENSION_ITERATOR = NULL;

Keyword* KWD_SPECIALIZE_RELATION = NULL;

Keyword* KWD_SPECIALIZE_DEPENDENTS = NULL;

Keyword* KWD_SPECIALIZE_ISA = NULL;

Surrogate* SGT_SPECIALIZE_PL_KERNEL_KB_HOLDS = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_PROPOSITION = NULL;

Keyword* KWD_SPECIALIZE_FUNCTION = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_LOGIC_OBJECT = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_F_TEST_PROPERTYp_MEMO_TABLE_000 = NULL;

Surrogate* SGT_SPECIALIZE_STELLA_THING = NULL;

Surrogate* SGT_SPECIALIZE_PL_KERNEL_KB_CLASS = NULL;

Surrogate* SGT_SPECIALIZE_PL_KERNEL_KB_RELATION = NULL;

Surrogate* SGT_SPECIALIZE_PL_KERNEL_KB_FUNCTION = NULL;

Surrogate* SGT_SPECIALIZE_PL_KERNEL_KB_COLLECTION = NULL;

Surrogate* SGT_SPECIALIZE_PL_KERNEL_KB_SET = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_F_TEST_ISAp_MEMO_TABLE_000 = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_F_TEST_ISAp_MEMO_TABLE_001 = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_F_ACCESS_BINARY_VALUE_MEMO_TABLE_000 = NULL;

Surrogate* SGT_SPECIALIZE_PL_KERNEL_KB_COLLECTIONOF = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_TRANSITIVE_CLOSURE_ITERATOR = NULL;

Symbol* SYM_SPECIALIZE_LOGIC_ALLOCATE_ADJACENCY_ITERATOR_FUNCTION = NULL;

Symbol* SYM_SPECIALIZE_LOGIC_FILTERp = NULL;

Symbol* SYM_SPECIALIZE_LOGIC_ADJACENCY_ITERATOR_STACK = NULL;

Symbol* SYM_SPECIALIZE_LOGIC_BEEN_THERE_LIST = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_SUPPORTED_CLOSURE_ITERATOR = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_DIRECTLY_LINKED_OBJECTS_ITERATOR = NULL;

Symbol* SYM_SPECIALIZE_LOGIC_INVERSEp = NULL;

Symbol* SYM_SPECIALIZE_LOGIC_ROOT_TRUTH_VALUE = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_SPECIALIZE_PL_KERNEL_KB_SUBSET_OF = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_F_ALL_SUPERCOLLECTIONS_MEMO_TABLE_000 = NULL;

Surrogate* SGT_SPECIALIZE_PL_KERNEL_KB_MEMBER_OF = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_F_ALL_SUPPORTED_NAMED_SUBCOLLECTIONS_MEMO_TABLE_000 = NULL;

Surrogate* SGT_SPECIALIZE_STELLA_CONS = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_NAMED_DESCRIPTION = NULL;

Surrogate* SGT_SPECIALIZE_STELLA_NUMBER = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_SKOLEM = NULL;

Surrogate* SGT_SPECIALIZE_LOGIC_CLASHING_PROPOSITIONS_ITERATOR = NULL;

Symbol* SYM_SPECIALIZE_LOGIC_REFERENCE_PROPOSITION = NULL;

Symbol* SYM_SPECIALIZE_LOGIC_DESCRIPTION = NULL;

Symbol* SYM_SPECIALIZE_STELLA_TAXONOMY_NODE = NULL;

Symbol* SYM_SPECIALIZE_LOGIC_STARTUP_SPECIALIZE = NULL;

Symbol* SYM_SPECIALIZE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
