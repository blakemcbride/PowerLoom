//  -*- Mode: C++ -*-

// normalize.cc

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

boolean searchControlPropositionP(Proposition* self) {
  { GeneralizedSymbol* testValue000 = self->operatoR;

    if ((testValue000 == SGT_NORMALIZE_PL_KERNEL_KB_CUT) ||
        ((testValue000 == SGT_NORMALIZE_PL_KERNEL_KB_BOUND_VARIABLES) ||
         ((testValue000 == SGT_NORMALIZE_PL_KERNEL_KB_FORK) ||
          (testValue000 == SGT_NORMALIZE_PL_KERNEL_KB_QUERY)))) {
      return (true);
    }
    else {
      return (false);
    }
  }
}

boolean duplicateAndOrArgumentsP(Proposition* prop1, Proposition* prop2) {
  return (equivalentPropositionsP(prop1, prop2, NULL) &&
      (!(searchControlPropositionP(prop1) ||
      searchControlPropositionP(prop2))));
}

void collectFlatConjuncts(Proposition* self, List* flatconjuncts) {
  { Keyword* testValue000 = self->kind;

    if (testValue000 == KWD_NORMALIZE_AND) {
      { Object* arg = NULL;
        Vector* vector000 = self->arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          arg = (vector000->theArray)[index000];
          collectFlatConjuncts(((Proposition*)(arg)), flatconjuncts);
        }
      }
      return;
    }
    else if (testValue000 == KWD_NORMALIZE_CONSTANT) {
      if (self->operatoR == SGT_NORMALIZE_STELLA_TRUE) {
        return;
      }
    }
    else {
      self->dependentPropositions->clear();
    }
  }
  { boolean foundP000 = false;

    { Proposition* prop = NULL;
      Cons* iter000 = flatconjuncts->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        prop = ((Proposition*)(iter000->value));
        if (duplicateAndOrArgumentsP(prop, self)) {
          foundP000 = true;
          break;
        }
      }
    }
    if (!(foundP000)) {
      flatconjuncts->push(self);
    }
  }
}

void overlayWithConstantProposition(Proposition* self, Proposition* constantproposition) {
  { Proposition* overlay = createProposition(SYM_NORMALIZE_LOGIC_CONSTANT, 0);

    overlay->operatoR = constantproposition->operatoR;
    { Proposition* object000 = overlay;
      TruthValue* value000 = ((TruthValue*)(accessInContext(constantproposition->truthValue, constantproposition->homeContext, false)));
      Object* oldValue001 = object000->truthValue;
      Object* newValue000 = updateInContext(oldValue001, value000, object000->homeContext, false);

      if (!(((boolean)(oldValue001)) &&
          (oldValue001->primaryType() == SGT_NORMALIZE_STELLA_CS_VALUE))) {
        object000->truthValue = newValue000;
      }
    }
    overlayProposition(self, overlay);
  }
}

Proposition* conjoinPropositions(Cons* conjuncts) {
  { List* flatconjuncts = newList();
    Proposition* result = NULL;

    { Proposition* c = NULL;
      Cons* iter000 = conjuncts;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        c = ((Proposition*)(iter000->value));
        collectFlatConjuncts(c, flatconjuncts);
      }
    }
    flatconjuncts->reverse();
    switch (flatconjuncts->length()) {
      case 0: 
        { Proposition* proposition = createProposition(SYM_NORMALIZE_LOGIC_CONSTANT, 0);

          overlayWithConstantProposition(proposition, TRUE_PROPOSITION);
          return (proposition);
        }
        break;
      case 1: 
        return (((Proposition*)(flatconjuncts->first())));
      default:
        break;
    }
    result = createProposition(SYM_NORMALIZE_STELLA_AND, flatconjuncts->length());
    result->arguments = copyListToArgumentsVector(flatconjuncts);
    if (((BooleanWrapper*)(dynamicSlotValue(((Proposition*)(flatconjuncts->first()))->dynamicSlots, SYM_NORMALIZE_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue) {
      setDynamicSlotValue(result->dynamicSlots, SYM_NORMALIZE_LOGIC_DESCRIPTIVEp, TRUE_WRAPPER, FALSE_WRAPPER);
    }
    return (result);
  }
}

Proposition* conjoinTwoPropositions(Proposition* prop1, Proposition* prop2) {
  if (!((boolean)(prop1))) {
    return (prop2);
  }
  else if (!((boolean)(prop2))) {
    return (prop1);
  }
  else if (duplicateAndOrArgumentsP(prop1, prop2)) {
    return (prop1);
  }
  else {
    { Proposition* andproposition = createProposition(SYM_NORMALIZE_STELLA_AND, 2);

      (andproposition->arguments->theArray)[0] = prop1;
      (andproposition->arguments->theArray)[1] = prop2;
      if (((BooleanWrapper*)(dynamicSlotValue(prop1->dynamicSlots, SYM_NORMALIZE_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue) {
        setDynamicSlotValue(andproposition->dynamicSlots, SYM_NORMALIZE_LOGIC_DESCRIPTIVEp, TRUE_WRAPPER, FALSE_WRAPPER);
      }
      return (andproposition);
    }
  }
}

void collectFlatDisjuncts(Proposition* self, List* flatdisjuncts) {
  if (self->kind == KWD_NORMALIZE_OR) {
    { Object* arg = NULL;
      Vector* vector000 = self->arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        collectFlatDisjuncts(((Proposition*)(arg)), flatdisjuncts);
      }
    }
    self->free();
  }
  else {
    { boolean foundP000 = false;

      { Proposition* prop = NULL;
        Cons* iter000 = flatdisjuncts->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          prop = ((Proposition*)(iter000->value));
          if (duplicateAndOrArgumentsP(prop, self)) {
            foundP000 = true;
            break;
          }
        }
      }
      if (!(foundP000)) {
        flatdisjuncts->push(self);
        self->dependentPropositions->clear();
      }
    }
  }
}

Proposition* disjoinPropositions(Cons* disjuncts) {
  if (disjuncts == NIL) {
    return (FALSE_PROPOSITION);
  }
  { List* flatdisjuncts = newList();
    Proposition* result = NULL;

    { Proposition* c = NULL;
      Cons* iter000 = disjuncts;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        c = ((Proposition*)(iter000->value));
        collectFlatDisjuncts(c, flatdisjuncts);
      }
    }
    flatdisjuncts->reverse();
    switch (flatdisjuncts->length()) {
      case 0: 
        { Proposition* proposition = createProposition(SYM_NORMALIZE_LOGIC_CONSTANT, 0);

          overlayWithConstantProposition(proposition, FALSE_PROPOSITION);
          return (proposition);
        }
        break;
      case 1: 
        return (((Proposition*)(flatdisjuncts->first())));
      default:
        break;
    }
    result = createProposition(SYM_NORMALIZE_STELLA_OR, flatdisjuncts->length());
    result->arguments = copyListToArgumentsVector(flatdisjuncts);
    if (((BooleanWrapper*)(dynamicSlotValue(((Proposition*)(flatdisjuncts->first()))->dynamicSlots, SYM_NORMALIZE_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue) {
      setDynamicSlotValue(result->dynamicSlots, SYM_NORMALIZE_LOGIC_DESCRIPTIVEp, TRUE_WRAPPER, FALSE_WRAPPER);
    }
    return (result);
  }
}

PatternVariable* renameLogicVariableApart(PatternVariable* variable, boolean destructiveP) {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, variable->homeModule());
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    { Symbol* newname = localGensym(variable->skolemName->symbolName);

      if (!(destructiveP)) {
        variable = copyVariable(variable, newKeyValueMap());
      }
      variable->skolemName = newname;
      return (variable);
    }
  }
}

void overlayProposition(Proposition* self, Proposition* overlayingprop) {
  self->kind = overlayingprop->kind;
  self->operatoR = overlayingprop->operatoR;
  { Proposition* object000 = self;
    TruthValue* value000 = ((TruthValue*)(accessInContext(overlayingprop->truthValue, overlayingprop->homeContext, false)));
    Object* oldValue001 = object000->truthValue;
    Object* newValue000 = updateInContext(oldValue001, value000, object000->homeContext, false);

    if (!(((boolean)(oldValue001)) &&
        (oldValue001->primaryType() == SGT_NORMALIZE_STELLA_CS_VALUE))) {
      object000->truthValue = newValue000;
    }
  }
  setDynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_WEIGHT, wrapFloat(((FloatWrapper*)(dynamicSlotValue(overlayingprop->dynamicSlots, SYM_NORMALIZE_LOGIC_WEIGHT, NULL_FLOAT_WRAPPER)))->wrapperValue), NULL_FLOAT_WRAPPER);
  setDynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_NEURAL_NET, ((NeuralNetwork*)(dynamicSlotValue(overlayingprop->dynamicSlots, SYM_NORMALIZE_LOGIC_NEURAL_NET, NULL))), NULL);
  self->arguments = overlayingprop->arguments->copy();
  if (((boolean)(((Vector*)(dynamicSlotValue(overlayingprop->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, NULL)))))) {
    setDynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, ((Vector*)(dynamicSlotValue(overlayingprop->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, NULL)))->copy(), NULL);
  }
  if (coerceWrappedBooleanToBoolean(overlayingprop->variableTypeP_reader())) {
    setDynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_VARIABLE_TYPEp, TRUE_WRAPPER, NULL);
  }
  if (((BooleanWrapper*)(dynamicSlotValue(overlayingprop->dynamicSlots, SYM_NORMALIZE_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue) {
    setDynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_DESCRIPTIVEp, TRUE_WRAPPER, FALSE_WRAPPER);
  }
}

void normalizeExistsProposition(Proposition* self) {
  { Proposition* whereproposition = ((Proposition*)((self->arguments->theArray)[0]));

    { 
      BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_NORMALIZE_DESCRIPTION);
      normalizeProposition(whereproposition);
    }
    if (whereproposition->kind == KWD_NORMALIZE_EXISTS) {
      { Cons* combinedargs = NIL;

        { PatternVariable* vbl = NULL;
          Vector* vector000 = ((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, NULL)));
          int index000 = 0;
          int length000 = vector000->length();
          Cons* collect000 = NULL;

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            vbl = ((PatternVariable*)((vector000->theArray)[index000]));
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(vbl, NIL);
                if (combinedargs == NIL) {
                  combinedargs = collect000;
                }
                else {
                  addConsToEndOfConsList(combinedargs, collect000);
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
        { PatternVariable* vbl = NULL;
          Vector* vector001 = ((Vector*)(dynamicSlotValue(whereproposition->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, NULL)));
          int index001 = 0;
          int length001 = vector001->length();
          Cons* collect001 = NULL;

          for  (; index001 < length001; 
                index001 = index001 + 1) {
            vbl = ((PatternVariable*)((vector001->theArray)[index001]));
            if (!((boolean)(collect001))) {
              {
                collect001 = cons(vbl, NIL);
                if (combinedargs == NIL) {
                  combinedargs = collect001;
                }
                else {
                  addConsToEndOfConsList(combinedargs, collect001);
                }
              }
            }
            else {
              {
                collect001->rest = cons(vbl, NIL);
                collect001 = collect001->rest;
              }
            }
          }
        }
        setDynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, copyConsListToVariablesVector(combinedargs), NULL);
        self->arguments = whereproposition->arguments;
        whereproposition->deletedPSetter(true);
      }
    }
    if (((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, NULL)))->emptyP() ||
        (whereproposition->kind == KWD_NORMALIZE_CONSTANT)) {
      overlayProposition(self, whereproposition);
    }
  }
}

boolean migrateConsequentGoalsToAntecedentP(Proposition* self) {
  { Proposition* antecedent = NULL;
    Proposition* consequent = ((Proposition*)((self->arguments->theArray)[1]));
    Cons* positivegoals = NIL;
    Cons* negatedgoals = NIL;

    if (!(consequent->kind == KWD_NORMALIZE_OR)) {
      return (false);
    }
    { Object* arg = NULL;
      Vector* vector000 = consequent->arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        { Proposition* disjunct = ((Proposition*)(arg));

          if (disjunct->kind == KWD_NORMALIZE_NOT) {
            negatedgoals = cons((disjunct->arguments->theArray)[0], negatedgoals);
          }
          else {
            positivegoals = cons(disjunct, positivegoals);
          }
        }
      }
    }
    if ((!(positivegoals == NIL)) &&
        (!(negatedgoals == NIL))) {
      antecedent = conjoinPropositions(negatedgoals->reverse());
      consequent = disjoinPropositions(positivegoals->reverse());
      normalizeProposition(antecedent);
      normalizeProposition(consequent);
      (self->arguments->theArray)[0] = antecedent;
      (self->arguments->theArray)[1] = consequent;
      return (true);
    }
    return (false);
  }
}

void flattenNestedForallProposition(Proposition* self) {
  { Cons* iovariables = NIL;
    Object* outerantecedent = (self->arguments->theArray)[0];
    Proposition* nestedforall = ((Proposition*)((self->arguments->theArray)[1]));
    Object* innerantecedent = (nestedforall->arguments->theArray)[0];
    Object* innerconsequent = (nestedforall->arguments->theArray)[1];

    { PatternVariable* v = NULL;
      Vector* vector000 = ((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, NULL)));
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        v = ((PatternVariable*)((vector000->theArray)[index000]));
        iovariables = cons(v, iovariables);
      }
    }
    { PatternVariable* v = NULL;
      Vector* vector001 = ((Vector*)(dynamicSlotValue(nestedforall->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, NULL)));
      int index001 = 0;
      int length001 = vector001->length();

      for  (; index001 < length001; 
            index001 = index001 + 1) {
        v = ((PatternVariable*)((vector001->theArray)[index001]));
        iovariables = cons(v, iovariables);
      }
    }
    setDynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, copyConsListToVariablesVector(iovariables->reverse()), NULL);
    (self->arguments->theArray)[0] = (conjoinTwoPropositions(((Proposition*)(outerantecedent)), ((Proposition*)(innerantecedent))));
    (self->arguments->theArray)[1] = innerconsequent;
    normalizeProposition(((Proposition*)((self->arguments->theArray)[0])));
  }
}

void normalizeForallProposition(Proposition* self) {
  { Object* antarg = (self->arguments->theArray)[0];
    Object* cqarg = (self->arguments->theArray)[1];
    Proposition* antecedent = NULL;
    Proposition* consequent = NULL;

    if (variableP(antarg) ||
        variableP(cqarg)) {
      { OutputStringStream* stream000 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream000->nativeStream) << "ERROR: " << "Can't yet handle propositional variables within FORALL" << "." << std::endl;
          helpSignalPropositionError(stream000, KWD_NORMALIZE_ERROR);
        }
        throw *newPropositionError(stream000->theStringReader());
      }
    }
    antecedent = ((Proposition*)(antarg));
    consequent = ((Proposition*)(cqarg));
    { 
      BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_NORMALIZE_DESCRIPTION);
      normalizeProposition(antecedent);
      normalizeProposition(consequent);
    }
    if (antecedent->kind == KWD_NORMALIZE_CONSTANT) {
      { GeneralizedSymbol* testValue000 = antecedent->operatoR;

        if (testValue000 == SGT_NORMALIZE_STELLA_TRUE) {
          if (migrateConsequentGoalsToAntecedentP(self)) {
            return;
          }
        }
        else if (testValue000 == SGT_NORMALIZE_STELLA_FALSE) {
          overlayWithConstantProposition(self, TRUE_PROPOSITION);
          return;
        }
        else {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream001->theStringReader());
          }
        }
      }
    }
    { Keyword* testValue001 = consequent->kind;

      if (testValue001 == KWD_NORMALIZE_FORALL) {
        if (!naturalDeductionModeP()) {
          flattenNestedForallProposition(self);
        }
      }
      else if (testValue001 == KWD_NORMALIZE_CONSTANT) {
        { GeneralizedSymbol* testValue002 = consequent->operatoR;

          if (testValue002 == SGT_NORMALIZE_STELLA_FALSE) {
            overlayProposition(self, antecedent);
            invertProposition(self);
            return;
          }
          else if (testValue002 == SGT_NORMALIZE_STELLA_TRUE) {
            overlayWithConstantProposition(self, TRUE_PROPOSITION);
            return;
          }
          else {
            { OutputStringStream* stream002 = newOutputStringStream();

              *(stream002->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
              throw *newStellaException(stream002->theStringReader());
            }
          }
        }
      }
      else {
      }
    }
    if (((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, NULL)))->emptyP()) {
      antecedent = invertProposition(antecedent);
      overlayProposition(self, disjoinPropositions(consList(2, antecedent, consequent)));
      normalizeProposition(self);
      return;
    }
    { Proposition* impliesproposition = deriveImpliesFromForall(self);

      if (((boolean)(impliesproposition))) {
        overlayProposition(self, impliesproposition);
      }
    }
  }
}

void normalizeNotProposition(Proposition* self) {
  { Object* argument = (self->arguments->theArray)[0];
    Proposition* proposition = NULL;

    if (variableP(argument)) {
      { OutputStringStream* stream000 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream000->nativeStream) << "ERROR: " << "Can't yet handle propositional variables within negations" << "." << std::endl;
          helpSignalPropositionError(stream000, KWD_NORMALIZE_ERROR);
        }
        throw *newPropositionError(stream000->theStringReader());
      }
    }
    proposition = ((Proposition*)(argument));
    if (proposition->kind == KWD_NORMALIZE_EQUIVALENT) {
      normalizeProposition(proposition);
    }
    { Keyword* testValue000 = proposition->kind;

      if ((testValue000 == KWD_NORMALIZE_ISA) ||
          ((testValue000 == KWD_NORMALIZE_PREDICATE) ||
           (testValue000 == KWD_NORMALIZE_FUNCTION))) {
        if (coerceWrappedBooleanToBoolean(proposition->variableTypeP_reader())) {
          overlayWithConstantProposition(self, FALSE_PROPOSITION);
        }
        else {
          normalizeProposition(proposition);
        }
      }
      else if (testValue000 == KWD_NORMALIZE_CONSTANT) {
        { GeneralizedSymbol* testValue001 = proposition->operatoR;

          if (testValue001 == SGT_NORMALIZE_STELLA_TRUE) {
            overlayWithConstantProposition(self, FALSE_PROPOSITION);
          }
          else if (testValue001 == SGT_NORMALIZE_STELLA_FALSE) {
            overlayWithConstantProposition(self, TRUE_PROPOSITION);
          }
          else {
          }
        }
      }
      else {
        invertProposition(proposition);
        overlayProposition(self, proposition);
      }
    }
  }
}

void normalizeAndProposition(Proposition* self) {
  { Cons* otherprops = NIL;
    boolean conjoinP = false;
    Cons* existsvariables = NIL;

    { Object* arg = NULL;
      Vector* vector000 = self->arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        if (variableP(arg)) {
          { OutputStringStream* stream000 = newOutputStringStream();

            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              *(stream000->nativeStream) << "ERROR: " << "Can't yet handle propositional variables within conjunctions" << "." << std::endl;
              helpSignalPropositionError(stream000, KWD_NORMALIZE_ERROR);
            }
            throw *newPropositionError(stream000->theStringReader());
          }
        }
        { Proposition* conjunct = ((Proposition*)(arg));

          normalizeProposition(conjunct);
          { Keyword* testValue000 = conjunct->kind;

            if (testValue000 == KWD_NORMALIZE_EXISTS) {
              { PatternVariable* v = NULL;
                Vector* vector001 = ((Vector*)(dynamicSlotValue(conjunct->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, NULL)));
                int index001 = 0;
                int length001 = vector001->length();
                Cons* collect000 = NULL;

                for  (; index001 < length001; 
                      index001 = index001 + 1) {
                  v = ((PatternVariable*)((vector001->theArray)[index001]));
                  { boolean foundP000 = false;

                    { PatternVariable* var = NULL;
                      Cons* iter000 = existsvariables;

                      for (; !(iter000 == NIL); iter000 = iter000->rest) {
                        var = ((PatternVariable*)(iter000->value));
                        if (variableEqlP(var->skolemName, v->skolemName)) {
                          foundP000 = true;
                          break;
                        }
                      }
                    }
                    if (foundP000) {
                      renameLogicVariableApart(v, true);
                    }
                  }
                  if (!((boolean)(collect000))) {
                    {
                      collect000 = cons(v, NIL);
                      if (existsvariables == NIL) {
                        existsvariables = collect000;
                      }
                      else {
                        addConsToEndOfConsList(existsvariables, collect000);
                      }
                    }
                  }
                  else {
                    {
                      collect000->rest = cons(v, NIL);
                      collect000 = collect000->rest;
                    }
                  }
                }
              }
              otherprops = cons((conjunct->arguments->theArray)[0], otherprops);
              conjoinP = true;
            }
            else if (testValue000 == KWD_NORMALIZE_AND) {
              otherprops = cons(conjunct, otherprops);
              conjoinP = true;
            }
            else if (testValue000 == KWD_NORMALIZE_CONSTANT) {
              if (conjunct->operatoR == SGT_NORMALIZE_STELLA_TRUE) {
                conjoinP = true;
                otherprops = cons(conjunct, otherprops);
              }
              else if (conjunct->operatoR == SGT_NORMALIZE_STELLA_FALSE) {
                overlayWithConstantProposition(self, FALSE_PROPOSITION);
                return;
              }
            }
            else {
              { boolean testValue001 = false;

                testValue001 = !conjoinP;
                if (testValue001) {
                  { boolean foundP001 = false;

                    { Object* prop = NULL;
                      Cons* iter001 = otherprops;

                      for (; !(iter001 == NIL); iter001 = iter001->rest) {
                        prop = iter001->value;
                        if (duplicateAndOrArgumentsP(((Proposition*)(prop)), conjunct)) {
                          foundP001 = true;
                          break;
                        }
                      }
                    }
                    testValue001 = foundP001;
                  }
                }
                if (testValue001) {
                  conjoinP = true;
                }
                else {
                  otherprops = cons(conjunct, otherprops);
                }
              }
            }
          }
        }
      }
    }
    otherprops = otherprops->reverse();
    if (!(existsvariables == NIL)) {
      { Proposition* existsproposition = createProposition(SYM_NORMALIZE_STELLA_EXISTS, 1);

        setDynamicSlotValue(existsproposition->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, copyConsListToVariablesVector(existsvariables), NULL);
        (existsproposition->arguments->theArray)[0] = (conjoinPropositions(otherprops));
        overlayProposition(self, existsproposition);
      }
      return;
    }
    if (conjoinP ||
        (otherprops->length() <= 1)) {
      overlayProposition(self, conjoinPropositions(otherprops));
    }
  }
}

void normalizeOrProposition(Proposition* self) {
  { Cons* propositions = NIL;
    boolean disjoinP = false;

    { Object* arg = NULL;
      Vector* vector000 = self->arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        if (variableP(arg)) {
          { OutputStringStream* stream000 = newOutputStringStream();

            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              *(stream000->nativeStream) << "ERROR: " << "Can't yet handle propositional variables within disjunctions" << "." << std::endl;
              helpSignalPropositionError(stream000, KWD_NORMALIZE_ERROR);
            }
            throw *newPropositionError(stream000->theStringReader());
          }
        }
        { Proposition* disjunct = ((Proposition*)(arg));

          normalizeProposition(disjunct);
          { Keyword* testValue000 = disjunct->kind;

            if (testValue000 == KWD_NORMALIZE_OR) {
              propositions = cons(disjunct, propositions);
              disjoinP = true;
            }
            else if (testValue000 == KWD_NORMALIZE_CONSTANT) {
              if (disjunct->operatoR == SGT_NORMALIZE_STELLA_FALSE) {
                disjoinP = true;
              }
              else if (disjunct->operatoR == SGT_NORMALIZE_STELLA_TRUE) {
                overlayWithConstantProposition(self, TRUE_PROPOSITION);
                return;
              }
              else {
                if (propositions->memberP(disjunct)) {
                  disjoinP = true;
                }
                else {
                  propositions = cons(disjunct, propositions);
                }
              }
            }
            else {
              { boolean testValue001 = false;

                testValue001 = !disjoinP;
                if (testValue001) {
                  { boolean foundP000 = false;

                    { Object* prop = NULL;
                      Cons* iter000 = propositions;

                      for (; !(iter000 == NIL); iter000 = iter000->rest) {
                        prop = iter000->value;
                        if (duplicateAndOrArgumentsP(((Proposition*)(prop)), disjunct)) {
                          foundP000 = true;
                          break;
                        }
                      }
                    }
                    testValue001 = foundP000;
                  }
                }
                if (testValue001) {
                  disjoinP = true;
                }
                else {
                  propositions = cons(disjunct, propositions);
                }
              }
            }
          }
        }
      }
    }
    if (disjoinP ||
        (propositions->length() <= 1)) {
      overlayProposition(self, disjoinPropositions(propositions));
    }
  }
}

void helpNormalizePredicateProposition(Proposition* self, Surrogate* relationref, Vector* predicatearguments) {
  { Object* outputargument = predicatearguments->last();
    Cons* inputarguments = NIL;
    Proposition* functionprop = NULL;
    Proposition* equivalenceprop = NULL;

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = predicatearguments->length() - 2;
      Cons* collect000 = NULL;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons((predicatearguments->theArray)[i], NIL);
            if (inputarguments == NIL) {
              inputarguments = collect000;
            }
            else {
              addConsToEndOfConsList(inputarguments, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons((predicatearguments->theArray)[i], NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    functionprop = findOrCreateFunctionProposition(relationref, inputarguments);
    equivalenceprop = createEquivalenceProposition(functionprop->arguments->last(), outputargument);
    overlayProposition(self, equivalenceprop);
    normalizeProposition(self);
  }
}

void normalizeHoldsProposition(Proposition* self) {
  { KeyValueMap* dummy1;

    { Vector* holdsarguments = self->arguments;
      Object* relationterm = (holdsarguments->theArray)[0];
      int nofarguments = holdsarguments->length() - 1;
      Surrogate* surrogate = evaluateRelationTerm(relationterm, self);
      Vector* predicatearguments = stella::newVector(nofarguments);
      Description* description = NULL;

      if ((!((boolean)(surrogate))) &&
          ((!isaP(relationterm, SGT_NORMALIZE_LOGIC_DESCRIPTION)) ||
           (!argumentBoundP(relationterm)))) {
        return;
      }
      { int i = NULL_INTEGER;
        int iter000 = 1;
        int upperBound000 = nofarguments;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter000 <= upperBound000); 
              iter000 = iter000 + 1) {
          i = iter000;
          (predicatearguments->theArray)[(i - 1)] = ((holdsarguments->theArray)[i]);
        }
      }
      if (((boolean)(surrogate))) {
        description = ((Description*)(evaluatePredicate(surrogate, (holdsarguments->theArray)[1])));
        if (!((boolean)(description))) {
          { OutputStringStream* stream000 = newOutputStringStream();

            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              *(stream000->nativeStream) << "ERROR: " << "Relation argument " << "`" << surrogate->symbolName << "'" << " in HOLDS proposition is not defined as a relation: " << "`" << self << "'" << "." << std::endl;
              helpSignalPropositionError(stream000, KWD_NORMALIZE_ERROR);
            }
            throw *newPropositionError(stream000->theStringReader());
          }
        }
        if (classP(description)) {
          self->kind = KWD_NORMALIZE_ISA;
        }
        else if (functionP(description)) {
          helpNormalizePredicateProposition(self, description->surrogateValueInverse, predicatearguments);
          return;
        }
        self->operatoR = description->surrogateValueInverse;
        self->arguments = predicatearguments;
        normalizeProposition(self);
        return;
      }
      else {
        description = ((Description*)(relationterm));
        if (!(description->arity() == nofarguments)) {
          { OutputStringStream* stream001 = newOutputStringStream();

            { 
              BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
              *(stream001->nativeStream) << "ERROR: " << "Arity violation in HOLDS proposition: " << "`" << self << "'" << "." << std::endl;
              helpSignalPropositionError(stream001, KWD_NORMALIZE_ERROR);
            }
            throw *newPropositionError(stream001->theStringReader());
          }
        }
        overlayProposition(self, conjoinPropositions(inheritDescriptionPropositions(predicatearguments, description, dummy1)));
        normalizeProposition(self);
      }
    }
  }
}

void normalizePredicateProposition(Proposition* self) {
  if (self->operatoR == SGT_NORMALIZE_PL_KERNEL_KB_HOLDS) {
    normalizeHoldsProposition(self);
    if (!(self->operatoR == SGT_NORMALIZE_PL_KERNEL_KB_HOLDS)) {
      return;
    }
  }
  if (self->operatoR == SGT_NORMALIZE_STELLA_THING) {
    overlayProposition(self, TRUE_PROPOSITION);
    return;
  }
  { Object* clause = NULL;
    Vector* vector000 = self->arguments;
    int index000 = 0;
    int length000 = vector000->length();

    for  (; index000 < length000; 
          index000 = index000 + 1) {
      clause = (vector000->theArray)[index000];
      if (isaP(clause, SGT_NORMALIZE_LOGIC_PROPOSITION)) {
        normalizeProposition(((Proposition*)(clause)));
      }
    }
  }
}

void normalizeFunctionProposition(Proposition* self) {
  { Object* clause = NULL;
    Vector* vector000 = self->arguments;
    int index000 = 0;
    int length000 = vector000->length();

    for  (; index000 < length000; 
          index000 = index000 + 1) {
      clause = (vector000->theArray)[index000];
      if (isaP(clause, SGT_NORMALIZE_LOGIC_PROPOSITION)) {
        normalizeProposition(((Proposition*)(clause)));
      }
    }
  }
}

Surrogate* computeRelationTermSurrogate(Skolem* skolem, Proposition* proposition) {
  { Proposition* functionprop = skolem->definingProposition;
    const char* string = stringify(generateFunctionAsTerm(functionprop));
    Surrogate* surrogate = NULL;
    int arity = 0;
    List* argumentnames = NULL;
    List* argumenttypes = NULL;
    NamedDescription* description = NULL;

    surrogate = internDerivedSurrogate(((Surrogate*)(functionprop->operatoR)), string);
    if (((boolean)(surrogate->surrogateValue))) {
      return (surrogate);
    }
    if (testPropertyP(skolem, SGT_NORMALIZE_PL_KERNEL_KB_VARIABLE_ARITY)) {
      arity = -1;
    }
    else if (((boolean)(accessBinaryValue(skolem, SGT_NORMALIZE_PL_KERNEL_KB_ARITY)))) {
      arity = ((IntegerWrapper*)(accessBinaryValue(skolem, SGT_NORMALIZE_PL_KERNEL_KB_ARITY)))->wrapperValue;
    }
    else {
      arity = proposition->arguments->length() - 1;
    }
    if (arity == -1) {
      argumentnames = list(1, yieldSystemDefinedParameterName(1, skolem));
      argumenttypes = list(1, SGT_NORMALIZE_STELLA_THING);
    }
    else {
      argumentnames = newList();
      argumenttypes = newList();
      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = arity - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          argumentnames->insert(yieldSystemDefinedParameterName(i, skolem));
          argumenttypes->insert(SGT_NORMALIZE_STELLA_THING);
        }
      }
      argumentnames->reverse();
      argumenttypes->reverse();
    }
    description = createPrimitiveDescription(argumentnames, argumenttypes, arity < 0, (logicalType(skolem) == SGT_NORMALIZE_PL_KERNEL_KB_CLASS) ||
        classP(skolem), (logicalType(skolem) == SGT_NORMALIZE_PL_KERNEL_KB_FUNCTION) ||
        ((proposition->operatoR == SGT_NORMALIZE_PL_KERNEL_KB_VALUE) ||
         functionP(skolem)), ((Module*)(surrogate->homeContext)));
    surrogate->surrogateValue = description;
    description->surrogateValueInverse = surrogate;
    ensureDescriptionBody(description);
    return (surrogate);
  }
}

Surrogate* evaluateRelationTerm(Object* relationterm, Proposition* proposition) {
  { Surrogate* testValue000 = safePrimaryType(relationterm);

    if (subtypeOfSurrogateP(testValue000)) {
      { Object* relationterm000 = relationterm;
        Surrogate* relationterm = ((Surrogate*)(relationterm000));

        return (relationterm);
      }
    }
    else if (subtypeOfP(testValue000, SGT_NORMALIZE_LOGIC_PATTERN_VARIABLE)) {
      { Object* relationterm001 = relationterm;
        PatternVariable* relationterm = ((PatternVariable*)(relationterm001));

        return (NULL);
      }
    }
    else if (subtypeOfP(testValue000, SGT_NORMALIZE_LOGIC_SKOLEM)) {
      { Object* relationterm002 = relationterm;
        Skolem* relationterm = ((Skolem*)(relationterm002));

        if (!functionOutputSkolemP(relationterm)) {
          return (NULL);
        }
        { Vector* arguments = relationterm->definingProposition->arguments;
          Surrogate* relationtermsurrogate = NULL;
          Object* relationtermvalue = valueOf(relationterm);

          { boolean foundP000 = false;

            { Object* arg = NULL;
              Vector* vector000 = arguments;
              int index000 = 0;
              int length000 = vector000->length();

              for  (; index000 < length000; 
                    index000 = index000 + 1) {
                arg = (vector000->theArray)[index000];
                if (isaP(arg, SGT_NORMALIZE_LOGIC_PATTERN_VARIABLE)) {
                  foundP000 = true;
                  break;
                }
              }
            }
            if (foundP000) {
              return (NULL);
            }
          }
          if (!(relationtermvalue == relationterm)) {
            return (evaluateRelationTerm(relationtermvalue, proposition));
          }
          relationtermsurrogate = computeRelationTermSurrogate(relationterm, proposition);
          transferPropositionsAndBacklinks(relationterm, valueOf(relationtermsurrogate));
          (arguments->theArray)[(arguments->length() - 1)] = relationtermsurrogate;
          return (relationtermsurrogate);
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_NORMALIZE_LOGIC_NAMED_DESCRIPTION)) {
      { Object* relationterm003 = relationterm;
        NamedDescription* relationterm = ((NamedDescription*)(relationterm003));

        return (relationterm->surrogateValueInverse);
      }
    }
    else {
      return (NULL);
    }
  }
}

Proposition* normalizeValueFunction(Proposition* self) {
  { Surrogate* functionsurrogate = evaluateRelationTerm((self->arguments->theArray)[0], self);
    int newargumentcount = self->arguments->length() - 1;
    Proposition* newproposition = NULL;
    Proposition* duplicate = NULL;

    if (!((boolean)(functionsurrogate))) {
      return (self);
    }
    newproposition = createProposition(SYM_NORMALIZE_STELLA_FUNCTION, newargumentcount);
    newproposition->operatoR = functionsurrogate;
    { int i = NULL_INTEGER;
      int iter000 = 1;
      int upperBound000 = newargumentcount;
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter000 <= upperBound000); 
            iter000 = iter000 + 1) {
        i = iter000;
        (newproposition->arguments->theArray)[(i - 1)] = ((self->arguments->theArray)[i]);
      }
    }
    if (skolemP((self->arguments->theArray)[(self->arguments->length() - 1)])) {
      ((Skolem*)((self->arguments->theArray)[(self->arguments->length() - 1)]))->definingProposition = newproposition;
    }
    if (!(descriptionModeP())) {
      duplicate = findDuplicateFunctionProposition(newproposition);
      if (((boolean)(duplicate))) {
        newproposition = duplicate;
      }
    }
    return (newproposition);
  }
}

void normalizeEquivalentProposition(Proposition* self) {
  { Object* firstarg = (self->arguments->theArray)[0];
    Object* secondarg = (self->arguments->theArray)[1];

    if (eqlP(firstarg, secondarg)) {
      overlayWithConstantProposition(self, TRUE_PROPOSITION);
    }
    else if (skolemP(firstarg) ||
        (skolemP(secondarg) ||
         (collectionP(firstarg) ||
          collectionP(secondarg)))) {
    }
    else {
      overlayWithConstantProposition(self, FALSE_PROPOSITION);
    }
  }
}

Proposition* shallowCopyProposition(Proposition* self) {
  { Proposition* copy = createProposition(SYM_NORMALIZE_STELLA_AND, 0);

    if (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue) {
      setDynamicSlotValue(copy->dynamicSlots, SYM_NORMALIZE_LOGIC_DESCRIPTIVEp, TRUE_WRAPPER, FALSE_WRAPPER);
    }
    if (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_DONT_OPTIMIZEp, FALSE_WRAPPER)))->wrapperValue) {
      setDynamicSlotValue(copy->dynamicSlots, SYM_NORMALIZE_LOGIC_DONT_OPTIMIZEp, TRUE_WRAPPER, FALSE_WRAPPER);
    }
    overlayProposition(copy, self);
    return (copy);
  }
}

void normalizeProposition(Proposition* self) {
  if (!coerceWrappedBooleanToBoolean(self->unfastenedP_reader())) {
    return;
  }
  if (containsNestedArgumentP(self)) {
    { Proposition* proposition = shallowCopyProposition(self);

      proposition = flattenNestedFunctionArguments(proposition);
      overlayProposition(self, proposition);
    }
  }
  { Keyword* testValue000 = self->kind;

    if (testValue000 == KWD_NORMALIZE_AND) {
      normalizeAndProposition(self);
    }
    else if (testValue000 == KWD_NORMALIZE_OR) {
      normalizeOrProposition(self);
    }
    else if (testValue000 == KWD_NORMALIZE_NOT) {
      normalizeNotProposition(self);
    }
    else if ((testValue000 == KWD_NORMALIZE_ISA) ||
        (testValue000 == KWD_NORMALIZE_PREDICATE)) {
      normalizePredicateProposition(self);
    }
    else if (testValue000 == KWD_NORMALIZE_FUNCTION) {
      normalizeFunctionProposition(self);
    }
    else if (testValue000 == KWD_NORMALIZE_EXISTS) {
      normalizeExistsProposition(self);
    }
    else if (testValue000 == KWD_NORMALIZE_FORALL) {
      normalizeForallProposition(self);
    }
    else if (testValue000 == KWD_NORMALIZE_EQUIVALENT) {
      normalizeEquivalentProposition(self);
    }
    else if ((testValue000 == KWD_NORMALIZE_IMPLIES) ||
        ((testValue000 == KWD_NORMALIZE_FAIL) ||
         ((testValue000 == KWD_NORMALIZE_COLLECT_INTO) ||
          (testValue000 == KWD_NORMALIZE_CONSTANT)))) {
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

void normalizeTopLevelProposition(Proposition* self) {
  normalizeProposition(self);
  if (self->kind == KWD_NORMALIZE_FORALL) {
    { Vector* iovars = ((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, NULL)));
      Vector* args = self->arguments;

      normalizeDescriptiveProposition(((Proposition*)((args->theArray)[0])), iovars, KWD_NORMALIZE_TAIL);
      normalizeDescriptiveProposition(((Proposition*)((args->theArray)[1])), iovars, KWD_NORMALIZE_HEAD);
    }
  }
}

void normalizeDescriptiveProposition(Proposition* self, Vector* iovariables, Keyword* kind) {
  { 
    BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_NORMALIZE_DESCRIPTION);
    try {
      equateTopLevelEquivalences(self, iovariables, kind);
    }
    catch (Clash& _e) {
      Clash* e = &_e;

      *(STANDARD_ERROR->nativeStream) << exceptionMessage(e) << std::endl;
    }
    tightenArgumentBindings(self, iovariables);
    simplifyProposition(self);
    collapseValueOfChainsForIoVariables(iovariables);
  }
}

void invertAtomicProposition(Proposition* self) {
  { Proposition* newatomicproposition = createProposition(SYM_NORMALIZE_STELLA_NOT, 1);
    Vector* newnotarguments = newatomicproposition->arguments;
    Proposition* newnotproposition = self;

    (newnotarguments->theArray)[0] = newatomicproposition;
    newatomicproposition->kind = self->kind;
    newatomicproposition->operatoR = self->operatoR;
    newatomicproposition->arguments = self->arguments;
    if (coerceWrappedBooleanToBoolean(self->variableTypeP_reader())) {
      setDynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_VARIABLE_TYPEp, NULL, NULL);
      setDynamicSlotValue(newatomicproposition->dynamicSlots, SYM_NORMALIZE_LOGIC_VARIABLE_TYPEp, TRUE_WRAPPER, NULL);
    }
    if (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue) {
      setDynamicSlotValue(newatomicproposition->dynamicSlots, SYM_NORMALIZE_LOGIC_DESCRIPTIVEp, TRUE_WRAPPER, FALSE_WRAPPER);
    }
    newnotproposition->kind = KWD_NORMALIZE_NOT;
    newnotproposition->operatoR = SGT_NORMALIZE_LOGIC_NOT;
    newnotproposition->arguments = newnotarguments;
  }
}

void invertExistsProposition(Proposition* self) {
  { Proposition* whereproposition = ((Proposition*)((self->arguments->theArray)[0]));
    Vector* newarguments = stella::newVector(2);

    self->arguments->free();
    normalizeProposition(whereproposition);
    whereproposition = safelyInvertProposition(whereproposition);
    self->kind = KWD_NORMALIZE_FORALL;
    self->operatoR = SGT_NORMALIZE_LOGIC_FORALL;
    (newarguments->theArray)[0] = TRUE_PROPOSITION;
    (newarguments->theArray)[1] = whereproposition;
    self->arguments = newarguments;
    normalizeProposition(self);
  }
}

void invertForallProposition(Proposition* self) {
  { Proposition* antecedent = ((Proposition*)((self->arguments->theArray)[0]));
    Proposition* consequent = ((Proposition*)((self->arguments->theArray)[1]));
    Vector* newarguments = stella::newVector(1);

    self->arguments->free();
    normalizeProposition(antecedent);
    normalizeProposition(consequent);
    consequent = safelyInvertProposition(consequent);
    self->kind = KWD_NORMALIZE_EXISTS;
    self->operatoR = SGT_NORMALIZE_LOGIC_EXISTS;
    (newarguments->theArray)[0] = (conjoinTwoPropositions(antecedent, consequent));
    self->arguments = newarguments;
    normalizeProposition(self);
  }
}

Proposition* extractProposition(Description* self, KeyValueMap* mapping) {
  { Proposition* proposition = self->proposition;
    Cons* existentials = (self->internalVariables->nonEmptyP() ? topLevelExistentialVariables(self) : NIL);
    Proposition* existsproposition = ((!(existentials == NIL)) ? createProposition(SYM_NORMALIZE_STELLA_EXISTS, 1) : ((Proposition*)(NULL)));

    if (((boolean)(existsproposition))) {
      setDynamicSlotValue(existsproposition->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, copyVariablesVector(copyConsListToVariablesVector(existentials), mapping), NULL);
    }
    proposition = copyProposition(proposition, mapping);
    mapping->removeAt(self->proposition);
    if (((boolean)(existsproposition))) {
      (existsproposition->arguments->theArray)[0] = proposition;
      proposition = existsproposition;
    }
    return (proposition);
  }
}

void invertImpliesProposition(Proposition* self) {
  { Vector* arguments = self->arguments;
    Object* arg1Value = (surrogateP((arguments->theArray)[0]) ? getDescription(((Surrogate*)((arguments->theArray)[0]))) : (arguments->theArray)[0]);
    Object* arg2Value = (surrogateP((arguments->theArray)[1]) ? getDescription(((Surrogate*)((arguments->theArray)[1]))) : (arguments->theArray)[1]);

    if (!(isaP(arg1Value, SGT_NORMALIZE_LOGIC_DESCRIPTION) &&
        isaP(arg2Value, SGT_NORMALIZE_LOGIC_DESCRIPTION))) {
      invertAtomicProposition(self);
      return;
    }
    { Description* subset = ((Description*)(arg1Value));
      Description* superset = ((Description*)(arg2Value));
      Proposition* subsetprop = NULL;
      Proposition* supersetprop = NULL;
      KeyValueMap* mapping = newKeyValueMap();
      Vector* newarguments = stella::newVector(1);

      self->kind = KWD_NORMALIZE_EXISTS;
      self->operatoR = SGT_NORMALIZE_LOGIC_EXISTS;
      setDynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, copyVariablesVector(subset->ioVariables, mapping), NULL);
      { PatternVariable* iovar = NULL;
        Vector* vector000 = ((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_NORMALIZE_LOGIC_IO_VARIABLES, NULL)));
        int index000 = 0;
        int length000 = vector000->length();
        PatternVariable* supvar = NULL;
        Vector* vector001 = superset->ioVariables;
        int index001 = 0;
        int length001 = vector001->length();

        for  (; (index000 < length000) &&
                  (index001 < length001); 
              index000 = index000 + 1,
              index001 = index001 + 1) {
          iovar = ((PatternVariable*)((vector000->theArray)[index000]));
          supvar = ((PatternVariable*)((vector001->theArray)[index001]));
          mapping->insertAt(supvar, iovar);
        }
      }
      subsetprop = extractProposition(subset, mapping);
      supersetprop = extractProposition(superset, mapping);
      setDynamicSlotValue(supersetprop->dynamicSlots, SYM_NORMALIZE_LOGIC_VARIABLE_TYPEp, NULL, NULL);
      invertProposition(supersetprop);
      (newarguments->theArray)[0] = (conjoinTwoPropositions(subsetprop, supersetprop));
      self->arguments = newarguments;
      normalizeProposition(self);
    }
  }
}

Proposition* invertProposition(Proposition* self) {
  { Keyword* testValue000 = self->kind;

    if ((testValue000 == KWD_NORMALIZE_ISA) ||
        ((testValue000 == KWD_NORMALIZE_PREDICATE) ||
         ((testValue000 == KWD_NORMALIZE_FUNCTION) ||
          (testValue000 == KWD_NORMALIZE_EQUIVALENT)))) {
      invertAtomicProposition(self);
    }
    else if (testValue000 == KWD_NORMALIZE_AND) {
      { int argumentcount = self->arguments->length();

        simplifyProposition(self);
        if (self->arguments->length() < argumentcount) {
          return (invertProposition(self));
        }
      }
      self->kind = KWD_NORMALIZE_OR;
      self->operatoR = SGT_NORMALIZE_LOGIC_OR;
      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = self->arguments->length() - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          (self->arguments->theArray)[i] = (safelyInvertProposition(((Proposition*)((self->arguments->theArray)[i]))));
        }
      }
    }
    else if (testValue000 == KWD_NORMALIZE_OR) {
      self->kind = KWD_NORMALIZE_AND;
      self->operatoR = SGT_NORMALIZE_LOGIC_AND;
      { int i = NULL_INTEGER;
        int iter001 = 0;
        int upperBound001 = self->arguments->length() - 1;

        for  (; iter001 <= upperBound001; 
              iter001 = iter001 + 1) {
          i = iter001;
          (self->arguments->theArray)[i] = (safelyInvertProposition(((Proposition*)((self->arguments->theArray)[i]))));
        }
      }
    }
    else if (testValue000 == KWD_NORMALIZE_NOT) {
      overlayProposition(self, ((Proposition*)((self->arguments->theArray)[0])));
      normalizeProposition(self);
    }
    else if (testValue000 == KWD_NORMALIZE_EXISTS) {
      if (functionInducedExistsP(self)) {
        embedNegationWithinFunctionInducedExists(self);
      }
      else {
        invertExistsProposition(self);
      }
    }
    else if (testValue000 == KWD_NORMALIZE_FORALL) {
      invertForallProposition(self);
    }
    else if (testValue000 == KWD_NORMALIZE_IMPLIES) {
      invertImpliesProposition(self);
    }
    else if (testValue000 == KWD_NORMALIZE_CONSTANT) {
      { GeneralizedSymbol* testValue001 = self->operatoR;

        if (testValue001 == SGT_NORMALIZE_STELLA_TRUE) {
          return (FALSE_PROPOSITION);
        }
        else if (testValue001 == SGT_NORMALIZE_STELLA_FALSE) {
          return (TRUE_PROPOSITION);
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
    else if (testValue000 == KWD_NORMALIZE_FAIL) {
      invertAtomicProposition(self);
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream001->theStringReader());
      }
    }
  }
  return (self);
}

Proposition* safelyInvertProposition(Proposition* self) {
  { Proposition* copy = shallowCopyProposition(self);

    invertProposition(copy);
    return (copy);
  }
}

void helpStartupNormalize1() {
  {
    SGT_NORMALIZE_PL_KERNEL_KB_CUT = ((Surrogate*)(internRigidSymbolWrtModule("CUT", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_NORMALIZE_PL_KERNEL_KB_BOUND_VARIABLES = ((Surrogate*)(internRigidSymbolWrtModule("BOUND-VARIABLES", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_NORMALIZE_PL_KERNEL_KB_FORK = ((Surrogate*)(internRigidSymbolWrtModule("FORK", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_NORMALIZE_PL_KERNEL_KB_QUERY = ((Surrogate*)(internRigidSymbolWrtModule("QUERY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_NORMALIZE_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    KWD_NORMALIZE_CONSTANT = ((Keyword*)(internRigidSymbolWrtModule("CONSTANT", NULL, 2)));
    SGT_NORMALIZE_STELLA_TRUE = ((Surrogate*)(internRigidSymbolWrtModule("TRUE", getStellaModule("/STELLA", true), 1)));
    SYM_NORMALIZE_LOGIC_CONSTANT = ((Symbol*)(internRigidSymbolWrtModule("CONSTANT", NULL, 0)));
    SGT_NORMALIZE_STELLA_CS_VALUE = ((Surrogate*)(internRigidSymbolWrtModule("CS-VALUE", getStellaModule("/STELLA", true), 1)));
    SYM_NORMALIZE_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    SYM_NORMALIZE_LOGIC_DESCRIPTIVEp = ((Symbol*)(internRigidSymbolWrtModule("DESCRIPTIVE?", NULL, 0)));
    KWD_NORMALIZE_OR = ((Keyword*)(internRigidSymbolWrtModule("OR", NULL, 2)));
    SYM_NORMALIZE_STELLA_OR = ((Symbol*)(internRigidSymbolWrtModule("OR", getStellaModule("/STELLA", true), 0)));
    SYM_NORMALIZE_LOGIC_WEIGHT = ((Symbol*)(internRigidSymbolWrtModule("WEIGHT", NULL, 0)));
    SYM_NORMALIZE_LOGIC_NEURAL_NET = ((Symbol*)(internRigidSymbolWrtModule("NEURAL-NET", NULL, 0)));
    SYM_NORMALIZE_LOGIC_IO_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("IO-VARIABLES", NULL, 0)));
    SYM_NORMALIZE_LOGIC_VARIABLE_TYPEp = ((Symbol*)(internRigidSymbolWrtModule("VARIABLE-TYPE?", NULL, 0)));
    KWD_NORMALIZE_DESCRIPTION = ((Keyword*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 2)));
    KWD_NORMALIZE_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("EXISTS", NULL, 2)));
    KWD_NORMALIZE_NOT = ((Keyword*)(internRigidSymbolWrtModule("NOT", NULL, 2)));
    KWD_NORMALIZE_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    SGT_NORMALIZE_STELLA_FALSE = ((Surrogate*)(internRigidSymbolWrtModule("FALSE", getStellaModule("/STELLA", true), 1)));
    KWD_NORMALIZE_FORALL = ((Keyword*)(internRigidSymbolWrtModule("FORALL", NULL, 2)));
    KWD_NORMALIZE_EQUIVALENT = ((Keyword*)(internRigidSymbolWrtModule("EQUIVALENT", NULL, 2)));
    KWD_NORMALIZE_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    KWD_NORMALIZE_PREDICATE = ((Keyword*)(internRigidSymbolWrtModule("PREDICATE", NULL, 2)));
    KWD_NORMALIZE_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SYM_NORMALIZE_STELLA_EXISTS = ((Symbol*)(internRigidSymbolWrtModule("EXISTS", getStellaModule("/STELLA", true), 0)));
    SGT_NORMALIZE_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
    SGT_NORMALIZE_PL_KERNEL_KB_HOLDS = ((Surrogate*)(internRigidSymbolWrtModule("HOLDS", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_NORMALIZE_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
    SGT_NORMALIZE_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    SGT_NORMALIZE_PL_KERNEL_KB_VARIABLE_ARITY = ((Surrogate*)(internRigidSymbolWrtModule("VARIABLE-ARITY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_NORMALIZE_PL_KERNEL_KB_ARITY = ((Surrogate*)(internRigidSymbolWrtModule("ARITY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_NORMALIZE_PL_KERNEL_KB_CLASS = ((Surrogate*)(internRigidSymbolWrtModule("CLASS", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_NORMALIZE_PL_KERNEL_KB_FUNCTION = ((Surrogate*)(internRigidSymbolWrtModule("FUNCTION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_NORMALIZE_PL_KERNEL_KB_VALUE = ((Surrogate*)(internRigidSymbolWrtModule("VALUE", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_NORMALIZE_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", NULL, 1)));
    SGT_NORMALIZE_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", NULL, 1)));
    SGT_NORMALIZE_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
    SYM_NORMALIZE_STELLA_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("FUNCTION", getStellaModule("/STELLA", true), 0)));
    SYM_NORMALIZE_LOGIC_DONT_OPTIMIZEp = ((Symbol*)(internRigidSymbolWrtModule("DONT-OPTIMIZE?", NULL, 0)));
    KWD_NORMALIZE_IMPLIES = ((Keyword*)(internRigidSymbolWrtModule("IMPLIES", NULL, 2)));
    KWD_NORMALIZE_FAIL = ((Keyword*)(internRigidSymbolWrtModule("FAIL", NULL, 2)));
    KWD_NORMALIZE_COLLECT_INTO = ((Keyword*)(internRigidSymbolWrtModule("COLLECT-INTO", NULL, 2)));
    KWD_NORMALIZE_TAIL = ((Keyword*)(internRigidSymbolWrtModule("TAIL", NULL, 2)));
    KWD_NORMALIZE_HEAD = ((Keyword*)(internRigidSymbolWrtModule("HEAD", NULL, 2)));
    SYM_NORMALIZE_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", getStellaModule("/STELLA", true), 0)));
    SGT_NORMALIZE_LOGIC_NOT = ((Surrogate*)(internRigidSymbolWrtModule("NOT", NULL, 1)));
    SGT_NORMALIZE_LOGIC_FORALL = ((Surrogate*)(internRigidSymbolWrtModule("FORALL", NULL, 1)));
    SGT_NORMALIZE_LOGIC_EXISTS = ((Surrogate*)(internRigidSymbolWrtModule("EXISTS", NULL, 1)));
    SGT_NORMALIZE_LOGIC_OR = ((Surrogate*)(internRigidSymbolWrtModule("OR", NULL, 1)));
    SGT_NORMALIZE_LOGIC_AND = ((Surrogate*)(internRigidSymbolWrtModule("AND", NULL, 1)));
    SYM_NORMALIZE_LOGIC_STARTUP_NORMALIZE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-NORMALIZE", NULL, 0)));
    SYM_NORMALIZE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void startupNormalize() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupNormalize1();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("SEARCH-CONTROL-PROPOSITION?", "(DEFUN (SEARCH-CONTROL-PROPOSITION? BOOLEAN) ((SELF PROPOSITION)))", ((cpp_function_code)(&searchControlPropositionP)), NULL);
      defineFunctionObject("DUPLICATE-AND-OR-ARGUMENTS?", "(DEFUN (DUPLICATE-AND-OR-ARGUMENTS? BOOLEAN) ((PROP1 PROPOSITION) (PROP2 PROPOSITION)))", ((cpp_function_code)(&duplicateAndOrArgumentsP)), NULL);
      defineFunctionObject("COLLECT-FLAT-CONJUNCTS", "(DEFUN COLLECT-FLAT-CONJUNCTS ((SELF PROPOSITION) (FLATCONJUNCTS (LIST OF PROPOSITION))))", ((cpp_function_code)(&collectFlatConjuncts)), NULL);
      defineFunctionObject("OVERLAY-WITH-CONSTANT-PROPOSITION", "(DEFUN OVERLAY-WITH-CONSTANT-PROPOSITION ((SELF PROPOSITION) (CONSTANTPROPOSITION PROPOSITION)))", ((cpp_function_code)(&overlayWithConstantProposition)), NULL);
      defineFunctionObject("CONJOIN-PROPOSITIONS", "(DEFUN (CONJOIN-PROPOSITIONS PROPOSITION) ((CONJUNCTS (CONS OF PROPOSITION))))", ((cpp_function_code)(&conjoinPropositions)), NULL);
      defineFunctionObject("CONJOIN-TWO-PROPOSITIONS", "(DEFUN (CONJOIN-TWO-PROPOSITIONS PROPOSITION) ((PROP1 PROPOSITION) (PROP2 PROPOSITION)))", ((cpp_function_code)(&conjoinTwoPropositions)), NULL);
      defineFunctionObject("COLLECT-FLAT-DISJUNCTS", "(DEFUN COLLECT-FLAT-DISJUNCTS ((SELF PROPOSITION) (FLATDISJUNCTS (LIST OF PROPOSITION))))", ((cpp_function_code)(&collectFlatDisjuncts)), NULL);
      defineFunctionObject("DISJOIN-PROPOSITIONS", "(DEFUN (DISJOIN-PROPOSITIONS PROPOSITION) ((DISJUNCTS (CONS OF PROPOSITION))))", ((cpp_function_code)(&disjoinPropositions)), NULL);
      defineFunctionObject("RENAME-LOGIC-VARIABLE-APART", "(DEFUN (RENAME-LOGIC-VARIABLE-APART PATTERN-VARIABLE) ((VARIABLE PATTERN-VARIABLE) (DESTRUCTIVE? BOOLEAN)))", ((cpp_function_code)(&renameLogicVariableApart)), NULL);
      defineFunctionObject("OVERLAY-PROPOSITION", "(DEFUN OVERLAY-PROPOSITION ((SELF PROPOSITION) (OVERLAYINGPROP PROPOSITION)))", ((cpp_function_code)(&overlayProposition)), NULL);
      defineFunctionObject("NORMALIZE-EXISTS-PROPOSITION", "(DEFUN NORMALIZE-EXISTS-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&normalizeExistsProposition)), NULL);
      defineFunctionObject("MIGRATE-CONSEQUENT-GOALS-TO-ANTECEDENT?", "(DEFUN (MIGRATE-CONSEQUENT-GOALS-TO-ANTECEDENT? BOOLEAN) ((SELF PROPOSITION)))", ((cpp_function_code)(&migrateConsequentGoalsToAntecedentP)), NULL);
      defineFunctionObject("FLATTEN-NESTED-FORALL-PROPOSITION", "(DEFUN FLATTEN-NESTED-FORALL-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&flattenNestedForallProposition)), NULL);
      defineFunctionObject("NORMALIZE-FORALL-PROPOSITION", "(DEFUN NORMALIZE-FORALL-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&normalizeForallProposition)), NULL);
      defineFunctionObject("NORMALIZE-NOT-PROPOSITION", "(DEFUN NORMALIZE-NOT-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&normalizeNotProposition)), NULL);
      defineFunctionObject("NORMALIZE-AND-PROPOSITION", "(DEFUN NORMALIZE-AND-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&normalizeAndProposition)), NULL);
      defineFunctionObject("NORMALIZE-OR-PROPOSITION", "(DEFUN NORMALIZE-OR-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&normalizeOrProposition)), NULL);
      defineFunctionObject("HELP-NORMALIZE-PREDICATE-PROPOSITION", "(DEFUN HELP-NORMALIZE-PREDICATE-PROPOSITION ((SELF PROPOSITION) (RELATIONREF SURROGATE) (PREDICATEARGUMENTS VECTOR)))", ((cpp_function_code)(&helpNormalizePredicateProposition)), NULL);
      defineFunctionObject("NORMALIZE-HOLDS-PROPOSITION", "(DEFUN NORMALIZE-HOLDS-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&normalizeHoldsProposition)), NULL);
      defineFunctionObject("NORMALIZE-PREDICATE-PROPOSITION", "(DEFUN NORMALIZE-PREDICATE-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&normalizePredicateProposition)), NULL);
      defineFunctionObject("NORMALIZE-FUNCTION-PROPOSITION", "(DEFUN NORMALIZE-FUNCTION-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&normalizeFunctionProposition)), NULL);
      defineFunctionObject("COMPUTE-RELATION-TERM-SURROGATE", "(DEFUN (COMPUTE-RELATION-TERM-SURROGATE SURROGATE) ((SKOLEM SKOLEM) (PROPOSITION PROPOSITION)))", ((cpp_function_code)(&computeRelationTermSurrogate)), NULL);
      defineFunctionObject("EVALUATE-RELATION-TERM", "(DEFUN (EVALUATE-RELATION-TERM SURROGATE) ((RELATIONTERM OBJECT) (PROPOSITION PROPOSITION)))", ((cpp_function_code)(&evaluateRelationTerm)), NULL);
      defineFunctionObject("NORMALIZE-VALUE-FUNCTION", "(DEFUN (NORMALIZE-VALUE-FUNCTION PROPOSITION) ((SELF PROPOSITION)))", ((cpp_function_code)(&normalizeValueFunction)), NULL);
      defineFunctionObject("NORMALIZE-EQUIVALENT-PROPOSITION", "(DEFUN NORMALIZE-EQUIVALENT-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&normalizeEquivalentProposition)), NULL);
      defineFunctionObject("SHALLOW-COPY-PROPOSITION", "(DEFUN (SHALLOW-COPY-PROPOSITION PROPOSITION) ((SELF PROPOSITION)))", ((cpp_function_code)(&shallowCopyProposition)), NULL);
      defineFunctionObject("NORMALIZE-PROPOSITION", "(DEFUN NORMALIZE-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&normalizeProposition)), NULL);
      defineFunctionObject("NORMALIZE-TOP-LEVEL-PROPOSITION", "(DEFUN NORMALIZE-TOP-LEVEL-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&normalizeTopLevelProposition)), NULL);
      defineFunctionObject("NORMALIZE-DESCRIPTIVE-PROPOSITION", "(DEFUN NORMALIZE-DESCRIPTIVE-PROPOSITION ((SELF PROPOSITION) (IOVARIABLES VARIABLES-VECTOR) (KIND KEYWORD)))", ((cpp_function_code)(&normalizeDescriptiveProposition)), NULL);
      defineFunctionObject("INVERT-ATOMIC-PROPOSITION", "(DEFUN INVERT-ATOMIC-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&invertAtomicProposition)), NULL);
      defineFunctionObject("INVERT-EXISTS-PROPOSITION", "(DEFUN INVERT-EXISTS-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&invertExistsProposition)), NULL);
      defineFunctionObject("INVERT-FORALL-PROPOSITION", "(DEFUN INVERT-FORALL-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&invertForallProposition)), NULL);
      defineFunctionObject("EXTRACT-PROPOSITION", "(DEFUN (EXTRACT-PROPOSITION PROPOSITION) ((SELF DESCRIPTION) (MAPPING ENTITY-MAPPING)))", ((cpp_function_code)(&extractProposition)), NULL);
      defineFunctionObject("INVERT-IMPLIES-PROPOSITION", "(DEFUN INVERT-IMPLIES-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&invertImpliesProposition)), NULL);
      defineFunctionObject("INVERT-PROPOSITION", "(DEFUN (INVERT-PROPOSITION PROPOSITION) ((SELF PROPOSITION)))", ((cpp_function_code)(&invertProposition)), NULL);
      defineFunctionObject("SAFELY-INVERT-PROPOSITION", "(DEFUN (SAFELY-INVERT-PROPOSITION PROPOSITION) ((SELF PROPOSITION)))", ((cpp_function_code)(&safelyInvertProposition)), NULL);
      defineFunctionObject("STARTUP-NORMALIZE", "(DEFUN STARTUP-NORMALIZE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupNormalize)), NULL);
      { MethodSlot* function = lookupFunction(SYM_NORMALIZE_LOGIC_STARTUP_NORMALIZE);

        setDynamicSlotValue(function->dynamicSlots, SYM_NORMALIZE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupNormalize"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
    }
  }
}

Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_CUT = NULL;

Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_BOUND_VARIABLES = NULL;

Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_FORK = NULL;

Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_QUERY = NULL;

Keyword* KWD_NORMALIZE_AND = NULL;

Keyword* KWD_NORMALIZE_CONSTANT = NULL;

Surrogate* SGT_NORMALIZE_STELLA_TRUE = NULL;

Symbol* SYM_NORMALIZE_LOGIC_CONSTANT = NULL;

Surrogate* SGT_NORMALIZE_STELLA_CS_VALUE = NULL;

Symbol* SYM_NORMALIZE_STELLA_AND = NULL;

Symbol* SYM_NORMALIZE_LOGIC_DESCRIPTIVEp = NULL;

Keyword* KWD_NORMALIZE_OR = NULL;

Symbol* SYM_NORMALIZE_STELLA_OR = NULL;

Symbol* SYM_NORMALIZE_LOGIC_WEIGHT = NULL;

Symbol* SYM_NORMALIZE_LOGIC_NEURAL_NET = NULL;

Symbol* SYM_NORMALIZE_LOGIC_IO_VARIABLES = NULL;

Symbol* SYM_NORMALIZE_LOGIC_VARIABLE_TYPEp = NULL;

Keyword* KWD_NORMALIZE_DESCRIPTION = NULL;

Keyword* KWD_NORMALIZE_EXISTS = NULL;

Keyword* KWD_NORMALIZE_NOT = NULL;

Keyword* KWD_NORMALIZE_ERROR = NULL;

Surrogate* SGT_NORMALIZE_STELLA_FALSE = NULL;

Keyword* KWD_NORMALIZE_FORALL = NULL;

Keyword* KWD_NORMALIZE_EQUIVALENT = NULL;

Keyword* KWD_NORMALIZE_ISA = NULL;

Keyword* KWD_NORMALIZE_PREDICATE = NULL;

Keyword* KWD_NORMALIZE_FUNCTION = NULL;

Symbol* SYM_NORMALIZE_STELLA_EXISTS = NULL;

Surrogate* SGT_NORMALIZE_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_HOLDS = NULL;

Surrogate* SGT_NORMALIZE_STELLA_THING = NULL;

Surrogate* SGT_NORMALIZE_LOGIC_PROPOSITION = NULL;

Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_VARIABLE_ARITY = NULL;

Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_ARITY = NULL;

Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_CLASS = NULL;

Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_FUNCTION = NULL;

Surrogate* SGT_NORMALIZE_PL_KERNEL_KB_VALUE = NULL;

Surrogate* SGT_NORMALIZE_LOGIC_PATTERN_VARIABLE = NULL;

Surrogate* SGT_NORMALIZE_LOGIC_SKOLEM = NULL;

Surrogate* SGT_NORMALIZE_LOGIC_NAMED_DESCRIPTION = NULL;

Symbol* SYM_NORMALIZE_STELLA_FUNCTION = NULL;

Symbol* SYM_NORMALIZE_LOGIC_DONT_OPTIMIZEp = NULL;

Keyword* KWD_NORMALIZE_IMPLIES = NULL;

Keyword* KWD_NORMALIZE_FAIL = NULL;

Keyword* KWD_NORMALIZE_COLLECT_INTO = NULL;

Keyword* KWD_NORMALIZE_TAIL = NULL;

Keyword* KWD_NORMALIZE_HEAD = NULL;

Symbol* SYM_NORMALIZE_STELLA_NOT = NULL;

Surrogate* SGT_NORMALIZE_LOGIC_NOT = NULL;

Surrogate* SGT_NORMALIZE_LOGIC_FORALL = NULL;

Surrogate* SGT_NORMALIZE_LOGIC_EXISTS = NULL;

Surrogate* SGT_NORMALIZE_LOGIC_OR = NULL;

Surrogate* SGT_NORMALIZE_LOGIC_AND = NULL;

Symbol* SYM_NORMALIZE_LOGIC_STARTUP_NORMALIZE = NULL;

Symbol* SYM_NORMALIZE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
