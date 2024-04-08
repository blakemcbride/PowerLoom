//  -*- Mode: C++ -*-

// generate.cc

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

// Maps variables to symbols in SYSTEM-DEFINED-ARGUMENT-NAMES.
DEFINE_STELLA_SPECIAL(oCANONICALVARIABLENAMEMAPPINGo, KeyValueList* , NULL);

// Number of the last canonically-mapped variable.
DEFINE_STELLA_SPECIAL(oCANONICALVARIABLECOUNTERo, int , NULL_INTEGER);

TermGenerationException* newTermGenerationException(Object* offendingTerm, const char* message) {
  { TermGenerationException* self = NULL;

    self = new TermGenerationException(message);
    self->offendingTerm = offendingTerm;
    return (self);
  }
}

Object* generateExpression(Object* self, boolean canonicalizevariablenamesP) {
  // Return an s-expression representing the source expression for 'self'.
  { 
    BIND_STELLA_SPECIAL(oCANONICALVARIABLENAMEMAPPINGo, KeyValueList*, (canonicalizevariablenamesP ? newKeyValueList() : NULL));
    BIND_STELLA_SPECIAL(oCANONICALVARIABLECOUNTERo, int, -1);
    BIND_STELLA_SPECIAL(oPRINTQUANTIFIEDOBJECTSSTACKo, Cons*, NIL);
    return (generateTerm(self));
  }
}

Symbol* generateNameOfVariable(PatternVariable* self) {
  if (((boolean)(oSKOLEMNAMEMAPPINGTABLEo))) {
    { Skolem* temp000 = ((Skolem*)(oSKOLEMNAMEMAPPINGTABLEo->lookup(self)));

      self = (((boolean)(temp000)) ? ((PatternVariable*)(temp000)) : self);
    }
  }
  if (!((boolean)(oCANONICALVARIABLENAMEMAPPINGo))) {
    return (self->skolemName);
  }
  { Object* canonicalname = oCANONICALVARIABLENAMEMAPPINGo->lookup(self);

    if (!((boolean)(canonicalname))) {
      canonicalname = ((Symbol*)(SYSTEM_DEFINED_ARGUMENT_NAMES->nth(oCANONICALVARIABLECOUNTERo = oCANONICALVARIABLECOUNTERo + 1)));
      oCANONICALVARIABLENAMEMAPPINGo->insertAt(self, canonicalname);
    }
    return (((Symbol*)(canonicalname)));
  }
}

Object* generateOneVariable(PatternVariable* self, boolean typedP) {
  { Object* value = NULL;

    if (((boolean)(oCURRENTJUSTIFICATIONo))) {
      value = justificationArgumentBoundTo(self, NULL);
    }
    if (!((boolean)(value))) {
      value = safeArgumentBoundTo(self);
    }
    if (((boolean)(value)) &&
        ((!(value == self)) &&
         (!quantifiedObjectVariableP(self)))) {
      return (generateTerm(value));
    }
    else {
      { Symbol* name = generateNameOfVariable(self);

        if (typedP &&
            (!(logicalType(self) == SGT_GENERATE_STELLA_THING))) {
          return (cons(name, cons(symbolize(logicalType(self)), NIL)));
        }
        else {
          return (name);
        }
      }
    }
  }
}

Object* generateOneQuantifiedVariable(PatternVariable* self, boolean typedP) {
  { Symbol* name = generateNameOfVariable(self);

    if (typedP &&
        (!(logicalType(self) == SGT_GENERATE_STELLA_THING))) {
      return (cons(name, cons(symbolize(logicalType(self)), NIL)));
    }
    else {
      return (name);
    }
  }
}

Cons* generateVariables(Vector* vector, boolean typedP) {
  { Cons* result = NIL;

    { Object* v = NULL;
      Vector* vector000 = vector;
      int index000 = 0;
      int length000 = vector000->length();
      Cons* collect000 = NULL;

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        v = (vector000->theArray)[index000];
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(generateOneVariable(((PatternVariable*)(v)), typedP), NIL);
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
            collect000->rest = cons(generateOneVariable(((PatternVariable*)(v)), typedP), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (result);
  }
}

Cons* generateQuantifiedVariables(Vector* vector, boolean typedP) {
  { Cons* result = NIL;

    { Object* v = NULL;
      Vector* vector000 = vector;
      int index000 = 0;
      int length000 = vector000->length();
      Cons* collect000 = NULL;

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        v = (vector000->theArray)[index000];
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(generateOneQuantifiedVariable(((PatternVariable*)(v)), typedP), NIL);
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
            collect000->rest = cons(generateOneQuantifiedVariable(((PatternVariable*)(v)), typedP), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (result);
  }
}

Cons* generateStellaCollection(Collection* self) {
  { Cons* collection = NIL;

    { Object* m = NULL;
      Iterator* iter000 = ((Iterator*)(self->allocateIterator()));
      Cons* collect000 = NULL;

      for  (; iter000->nextP(); ) {
        m = iter000->value;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(generateTerm(m), NIL);
            if (collection == NIL) {
              collection = collect000;
            }
            else {
              addConsToEndOfConsList(collection, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(generateTerm(m), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (cons((self->noDuplicatesP() ? SYM_GENERATE_PL_KERNEL_KB_SETOF : SYM_GENERATE_PL_KERNEL_KB_LISTOF), collection->concatenate(NIL, 0)));
  }
}

Object* generateDescription(Description* self) {
  if (namedDescriptionP(self)) {
    return (internalStellaOperatorToKif(self->descriptionName()));
  }
  else if (((boolean)(((Description*)(dynamicSlotValue(self->dynamicSlots, SYM_GENERATE_LOGIC_COMPLEMENT_DESCRIPTION, NULL)))))) {
    return (listO(3, SYM_GENERATE_STELLA_NOT, internalStellaOperatorToKif(((Description*)(dynamicSlotValue(self->dynamicSlots, SYM_GENERATE_LOGIC_COMPLEMENT_DESCRIPTION, NULL)))->descriptionName()), NIL));
  }
  else {
    pushQuantifiedObject(self);
    { Cons* result = listO(3, SYM_GENERATE_LOGIC_KAPPA, generateQuantifiedVariables(self->ioVariables, true), cons(generateDescriptionProposition(self, false), NIL));

      popQuantifiedObject();
      return (result);
    }
  }
}

Cons* generateArguments(Vector* arguments) {
  { Cons* result = NIL;

    { Object* arg = NULL;
      Vector* vector000 = arguments;
      int index000 = 0;
      int length000 = vector000->length();
      Cons* collect000 = NULL;

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(generateTerm(arg), NIL);
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
            collect000->rest = cons(generateTerm(arg), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (result);
  }
}

Symbol* generateOperator(Proposition* self) {
  { GeneralizedSymbol* operatoR = self->operatoR;

    if (!((boolean)(operatoR))) {
      return (SYM_GENERATE_STELLA_NULL);
    }
    { Surrogate* testValue000 = safePrimaryType(operatoR);

      if (subtypeOfSurrogateP(testValue000)) {
        { GeneralizedSymbol* operator000 = operatoR;
          Surrogate* operatoR = ((Surrogate*)(operator000));

          if (operatoR == SGT_GENERATE_PL_KERNEL_KB_EQUIVALENT) {
            return (SYM_GENERATE_STELLA_e);
          }
          else {
            return (internSymbolInModule(operatoR->symbolName, ((Module*)(operatoR->homeContext)), false));
          }
        }
      }
      else if (subtypeOfSymbolP(testValue000)) {
        { GeneralizedSymbol* operator001 = operatoR;
          Symbol* operatoR = ((Symbol*)(operator001));

          return (operatoR);
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

Object* generateProposition(Proposition* self) {
  { Keyword* testValue000 = self->kind;

    if ((testValue000 == KWD_GENERATE_PREDICATE) ||
        ((testValue000 == KWD_GENERATE_ISA) ||
         ((testValue000 == KWD_GENERATE_EQUIVALENT) ||
          ((testValue000 == KWD_GENERATE_AND) ||
           ((testValue000 == KWD_GENERATE_OR) ||
            (testValue000 == KWD_GENERATE_NOT)))))) {
      { Symbol* operatoR = generateOperator(self);

        return (cons(operatoR, generateArguments(self->arguments)->concatenate(NIL, 0)));
      }
    }
    else if (testValue000 == KWD_GENERATE_FUNCTION) {
      return (generateFunctionProposition(self));
    }
    else if (testValue000 == KWD_GENERATE_EXISTS) {
      pushQuantifiedObject(self);
      { Cons* result = listO(3, SYM_GENERATE_STELLA_EXISTS, generateQuantifiedVariables(((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_GENERATE_LOGIC_IO_VARIABLES, NULL))), false), cons(generateProposition(((Proposition*)((self->arguments->theArray)[0]))), NIL));

        popQuantifiedObject();
        return (result);
      }
    }
    else if (testValue000 == KWD_GENERATE_FORALL) {
      pushQuantifiedObject(self);
      { boolean forwardP = !((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_GENERATE_LOGIC_BACKWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue;
        Symbol* arrow = symbolize(chooseImplicationOperator(self, forwardP));
        Cons* result = listO(3, SYM_GENERATE_STELLA_FORALL, generateQuantifiedVariables(((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_GENERATE_LOGIC_IO_VARIABLES, NULL))), false), cons(cons(arrow, cons(generateProposition(((Proposition*)((self->arguments->theArray)[((forwardP ? 0 : 1))]))), cons(generateProposition(((Proposition*)((self->arguments->theArray)[((forwardP ? 1 : 0))]))), NIL))), NIL));

        popQuantifiedObject();
        return (result);
      }
    }
    else if (testValue000 == KWD_GENERATE_IMPLIES) {
      return (generateImpliesProposition(self));
    }
    else if (testValue000 == KWD_GENERATE_FAIL) {
      return (cons(SYM_GENERATE_LOGIC_FAIL, generateArguments(self->arguments)->concatenate(NIL, 0)));
    }
    else if (testValue000 == KWD_GENERATE_CONSTANT) {
      return (generateOperator(self));
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

Cons* generateFunctionAsTerm(Proposition* self) {
  { Vector* args = self->arguments;
    Cons* arguments = NIL;

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = args->length() - 2;
      Cons* collect000 = NULL;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(generateTerm((args->theArray)[i]), NIL);
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
            collect000->rest = cons(generateTerm((args->theArray)[i]), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (cons(generateOperator(self), arguments->concatenate(NIL, 0)));
  }
}

Cons* generateFunctionProposition(Proposition* self) {
  { Cons* result = generateFunctionAsTerm(self);
    Object* lastarg = self->arguments->last();
    Object* lastargvalue = innermostOf(lastarg);

    if (((boolean)(lastargvalue)) &&
        (!eqlP(lastargvalue, lastarg))) {
      lastarg = generateTerm(lastargvalue);
    }
    else {
      lastarg = generateTerm(lastarg);
    }
    if (oPRINTFUNCTIONSASRELATIONSpo) {
      return (result->concatenate(cons(lastarg, NIL), 0));
    }
    else {
      return (listO(3, SYM_GENERATE_STELLA_e, result, cons(lastarg, NIL)));
    }
  }
}

Object* generateSkolem(Skolem* self) {
  if (((boolean)(nativeValueOf(self)))) {
    return (generateTerm(nativeValueOf(self)));
  }
  else if (((boolean)(self->definingProposition))) {
    return (generateFunctionAsTerm(self->definingProposition));
  }
  else if (((boolean)(innermostOf(self))) &&
      (!(self == innermostOf(self)))) {
    return (generateTerm(innermostOf(self)));
  }
  else if (conceptPrototypeP(self)) {
    return (listO(3, SYM_GENERATE_PL_KERNEL_KB_CONCEPT_PROTOTYPE, generateTerm(conceptPrototypeOf(self)), NIL));
  }
  else {
    *(STANDARD_WARNING->nativeStream) << "Warning: " << "Don't know how to generate skolem: " << "`" << self << "'" << std::endl << std::endl;
    return (SYM_GENERATE_LOGIC_UNIDENTIFIED_SKOLEM);
  }
}

Object* LogicThing::generateSpecializedTerm() {
  // Method to generate a specialized term for `self'.  This is designed
  // to allow for extension of the term generation code to cover other
  // types of objects for the logic.  This particular method will signal
  // an error unless there is a surrogate-value-inverse link set.
  { LogicThing* self = this;

    if (((boolean)(self->surrogateValueInverse))) {
      return (self->surrogateValueInverse);
    }
    else {
      throw *newTermGenerationException(self, stringConcatenate("DON'T KNOW HOW TO GENERATE EXPRESSION FOR THE THING: ", stringify(self), 0));
    }
  }
}

Object* generateTerm(Object* self) {
  if (!((boolean)(self))) {
    return (NULL);
  }
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_GENERATE_LOGIC_PROPOSITION)) {
      { Object* self000 = self;
        Proposition* self = ((Proposition*)(self000));

        return (generateProposition(self));
      }
    }
    else if (subtypeOfP(testValue000, SGT_GENERATE_STELLA_LITERAL_WRAPPER)) {
      { Object* self001 = self;
        LiteralWrapper* self = ((LiteralWrapper*)(self001));

        return (self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_GENERATE_LOGIC_DESCRIPTION)) {
      { Object* self002 = self;
        Description* self = ((Description*)(self002));

        return (generateDescription(self));
      }
    }
    else if (subtypeOfP(testValue000, SGT_GENERATE_LOGIC_PATTERN_VARIABLE)) {
      { Object* self003 = self;
        PatternVariable* self = ((PatternVariable*)(self003));

        return (generateOneVariable(self, false));
      }
    }
    else if (subtypeOfP(testValue000, SGT_GENERATE_LOGIC_SKOLEM)) {
      { Object* self004 = self;
        Skolem* self = ((Skolem*)(self004));

        return (generateSkolem(self));
      }
    }
    else if (subtypeOfP(testValue000, SGT_GENERATE_LOGIC_LOGIC_OBJECT)) {
      { Object* self005 = self;
        LogicObject* self = ((LogicObject*)(self005));

        if (((boolean)(self->surrogateValueInverse))) {
          return (internSymbolInModule(self->surrogateValueInverse->symbolName, ((Module*)(self->surrogateValueInverse->homeContext)), false));
        }
        else {
          return (SYM_GENERATE_LOGIC_UNNAMED_OBJECT);
        }
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* self006 = self;
        Surrogate* self = ((Surrogate*)(self006));

        return (internSymbolInModule(self->symbolName, ((Module*)(self->homeContext)), false));
      }
    }
    else if (subtypeOfKeywordP(testValue000)) {
      { Object* self007 = self;
        Keyword* self = ((Keyword*)(self007));

        return (self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_GENERATE_STELLA_COLLECTION)) {
      { Object* self008 = self;
        Collection* self = ((Collection*)(self008));

        return (generateStellaCollection(self));
      }
    }
    else if (subtypeOfP(testValue000, SGT_GENERATE_LOGIC_LOGIC_THING)) {
      { Object* self009 = self;
        LogicThing* self = ((LogicThing*)(self009));

        return (self->generateSpecializedTerm());
      }
    }
    else if (subtypeOfP(testValue000, SGT_GENERATE_STELLA_THING)) {
      { Object* self010 = self;
        Thing* self = ((Thing*)(self010));

        if (((boolean)(self->surrogateValueInverse))) {
          return (self->surrogateValueInverse);
        }
        else {
          throw *newTermGenerationException(self, stringConcatenate("DON'T KNOW HOW TO GENERATE EXPRESSION FOR THE THING: ", stringify(self), 0));
        }
      }
    }
    else {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Illegal logical form: " << "`" << self << "'" << std::endl << std::endl;
      return (SYM_GENERATE_LOGIC_ILLEGAL_TERM);
    }
  }
}

Cons* generateImpliesProposition(Proposition* self) {
  { Object* tailarg = (self->arguments->theArray)[0];
    Object* headarg = (self->arguments->theArray)[1];

    if (isaP(headarg, SGT_GENERATE_LOGIC_DESCRIPTION) &&
        isaP(tailarg, SGT_GENERATE_LOGIC_DESCRIPTION)) {
      return (generateDescriptionsAsRule(((Description*)(headarg)), ((Description*)(tailarg)), self, false));
    }
    else {
      return (cons(SYM_GENERATE_PL_KERNEL_KB_SUBSET_OF, generateArguments(self->arguments)->concatenate(NIL, 0)));
    }
  }
}

Cons* generateDescriptionProposition(Description* self, boolean invertP) {
  { Object* prop = generateProposition(self->proposition);
    Cons* existentals = (self->internalVariables->nonEmptyP() ? topLevelExistentialVariables(self) : NIL);

    { Object* var = NULL;
      Cons* iter000 = existentals;
      int i = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        var = iter000->value;
        i = iter001;
        existentals->nthSetter(generateOneVariable(((PatternVariable*)(var)), true), i);
      }
    }
    if (!(existentals == NIL)) {
      prop = listO(3, SYM_GENERATE_STELLA_EXISTS, existentals, cons(prop, NIL));
    }
    if (invertP) {
      return (listO(3, SYM_GENERATE_STELLA_NOT, prop, NIL));
    }
    else {
      return (((Cons*)(prop)));
    }
  }
}

Cons* generateDescriptionsAsRule(Description* head, Description* tail, Proposition* rule, boolean reversepolarityP) {
  { boolean forwardarrowP = ((BooleanWrapper*)(dynamicSlotValue(rule->dynamicSlots, SYM_GENERATE_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue &&
        (!reversepolarityP);
    boolean reverseargumentsP = forwardarrowP ||
        reversepolarityP;
    Symbol* arrow = symbolize(chooseImplicationOperator(rule, forwardarrowP));
    boolean mapheadvariablesP = namedDescriptionP(head);
    Object* headprop = NULL;
    Object* tailprop = NULL;
    Cons* universals = NIL;

    if (reverseargumentsP) {
      { Description* temp = head;

        head = tail;
        tail = temp;
      }
      mapheadvariablesP = !mapheadvariablesP;
    }
    { PatternVariable* var = NULL;
      Vector* vector000 = (mapheadvariablesP ? tail->ioVariables : head->ioVariables);
      int index000 = 0;
      int length000 = vector000->length();
      Cons* collect000 = NULL;

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        var = ((PatternVariable*)((vector000->theArray)[index000]));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(generateOneVariable(var, true), NIL);
            if (universals == NIL) {
              universals = collect000;
            }
            else {
              addConsToEndOfConsList(universals, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(generateOneVariable(var, true), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { 
      BIND_STELLA_SPECIAL(oSKOLEMNAMEMAPPINGTABLEo, KeyValueMap*, (mapheadvariablesP ? ((KeyValueMap*)(createSkolemMappingTable(head->ioVariables, tail->ioVariables))) : NULL));
      pushQuantifiedObject(head);
      headprop = generateDescriptionProposition(head, reversepolarityP);
      popQuantifiedObject();
    }
    { 
      BIND_STELLA_SPECIAL(oSKOLEMNAMEMAPPINGTABLEo, KeyValueMap*, ((!mapheadvariablesP) ? ((KeyValueMap*)(createSkolemMappingTable(tail->ioVariables, head->ioVariables))) : NULL));
      pushQuantifiedObject(tail);
      tailprop = generateDescriptionProposition(tail, reversepolarityP);
      popQuantifiedObject();
    }
    return (listO(3, SYM_GENERATE_STELLA_FORALL, universals, cons(cons(arrow, cons(headprop, cons(tailprop, NIL))), NIL)));
  }
}

Object* deobjectifyTree(Object* self) {
  // Return a copy of `self' where all logic objects are
  // replaced by their `generated' parse-tree version.  This is useful to
  // convert the result of a retrieval query into a regular parse tree.
  { Surrogate* testValue000 = safePrimaryType(self);

    if (testValue000 == SGT_GENERATE_STELLA_CONS) {
      { Object* self000 = self;
        Cons* self = ((Cons*)(self000));

        { Cons* result = NIL;

          { Object* elt = NULL;
            Cons* iter000 = self;
            Cons* collect000 = NULL;

            for  (; !(iter000 == NIL); 
                  iter000 = iter000->rest) {
              elt = iter000->value;
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(deobjectifyTree(elt), NIL);
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
                  collect000->rest = cons(deobjectifyTree(elt), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
          return (result);
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_GENERATE_LOGIC_PROPOSITION)) {
      { Object* self001 = self;
        Proposition* self = ((Proposition*)(self001));

        return (generateTerm(self));
      }
    }
    else if (subtypeOfP(testValue000, SGT_GENERATE_LOGIC_LOGIC_OBJECT)) {
      { Object* self002 = self;
        LogicObject* self = ((LogicObject*)(self002));

        return (generateTerm(self));
      }
    }
    else if (subtypeOfP(testValue000, SGT_GENERATE_STELLA_COLLECTION)) {
      { Object* self003 = self;
        Collection* self = ((Collection*)(self003));

        return (generateTerm(self));
      }
    }
    else if (subtypeOfP(testValue000, SGT_GENERATE_STELLA_THING)) {
      { Object* self004 = self;
        Thing* self = ((Thing*)(self004));

        return (generateTerm(self));
      }
    }
    else {
      return (self);
    }
  }
}

void helpStartupGenerate1() {
  {
    SGT_GENERATE_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
    SYM_GENERATE_PL_KERNEL_KB_SETOF = ((Symbol*)(internRigidSymbolWrtModule("SETOF", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_GENERATE_PL_KERNEL_KB_LISTOF = ((Symbol*)(internRigidSymbolWrtModule("LISTOF", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_GENERATE_LOGIC_COMPLEMENT_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("COMPLEMENT-DESCRIPTION", NULL, 0)));
    SYM_GENERATE_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", getStellaModule("/STELLA", true), 0)));
    SYM_GENERATE_LOGIC_KAPPA = ((Symbol*)(internRigidSymbolWrtModule("KAPPA", NULL, 0)));
    SYM_GENERATE_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", getStellaModule("/STELLA", true), 0)));
    SGT_GENERATE_PL_KERNEL_KB_EQUIVALENT = ((Surrogate*)(internRigidSymbolWrtModule("EQUIVALENT", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_GENERATE_STELLA_e = ((Symbol*)(internRigidSymbolWrtModule("=", getStellaModule("/STELLA", true), 0)));
    KWD_GENERATE_PREDICATE = ((Keyword*)(internRigidSymbolWrtModule("PREDICATE", NULL, 2)));
    KWD_GENERATE_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    KWD_GENERATE_EQUIVALENT = ((Keyword*)(internRigidSymbolWrtModule("EQUIVALENT", NULL, 2)));
    KWD_GENERATE_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    KWD_GENERATE_OR = ((Keyword*)(internRigidSymbolWrtModule("OR", NULL, 2)));
    KWD_GENERATE_NOT = ((Keyword*)(internRigidSymbolWrtModule("NOT", NULL, 2)));
    KWD_GENERATE_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    KWD_GENERATE_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("EXISTS", NULL, 2)));
    SYM_GENERATE_STELLA_EXISTS = ((Symbol*)(internRigidSymbolWrtModule("EXISTS", getStellaModule("/STELLA", true), 0)));
    SYM_GENERATE_LOGIC_IO_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("IO-VARIABLES", NULL, 0)));
    KWD_GENERATE_FORALL = ((Keyword*)(internRigidSymbolWrtModule("FORALL", NULL, 2)));
    SYM_GENERATE_LOGIC_BACKWARD_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("BACKWARD-ONLY?", NULL, 0)));
    SYM_GENERATE_STELLA_FORALL = ((Symbol*)(internRigidSymbolWrtModule("FORALL", getStellaModule("/STELLA", true), 0)));
    KWD_GENERATE_IMPLIES = ((Keyword*)(internRigidSymbolWrtModule("IMPLIES", NULL, 2)));
    KWD_GENERATE_FAIL = ((Keyword*)(internRigidSymbolWrtModule("FAIL", NULL, 2)));
    SYM_GENERATE_LOGIC_FAIL = ((Symbol*)(internRigidSymbolWrtModule("FAIL", NULL, 0)));
    KWD_GENERATE_CONSTANT = ((Keyword*)(internRigidSymbolWrtModule("CONSTANT", NULL, 2)));
    SYM_GENERATE_PL_KERNEL_KB_CONCEPT_PROTOTYPE = ((Symbol*)(internRigidSymbolWrtModule("CONCEPT-PROTOTYPE", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_GENERATE_LOGIC_UNIDENTIFIED_SKOLEM = ((Symbol*)(internRigidSymbolWrtModule("UNIDENTIFIED-SKOLEM", NULL, 0)));
    SGT_GENERATE_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    SGT_GENERATE_STELLA_LITERAL_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_GENERATE_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
    SGT_GENERATE_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", NULL, 1)));
    SGT_GENERATE_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", NULL, 1)));
    SGT_GENERATE_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
    SYM_GENERATE_LOGIC_UNNAMED_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("UNNAMED_OBJECT", NULL, 0)));
    SGT_GENERATE_STELLA_COLLECTION = ((Surrogate*)(internRigidSymbolWrtModule("COLLECTION", getStellaModule("/STELLA", true), 1)));
    SGT_GENERATE_LOGIC_LOGIC_THING = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-THING", NULL, 1)));
    SYM_GENERATE_LOGIC_ILLEGAL_TERM = ((Symbol*)(internRigidSymbolWrtModule("ILLEGAL-TERM", NULL, 0)));
    SYM_GENERATE_PL_KERNEL_KB_SUBSET_OF = ((Symbol*)(internRigidSymbolWrtModule("SUBSET-OF", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_GENERATE_LOGIC_FORWARD_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("FORWARD-ONLY?", NULL, 0)));
    SGT_GENERATE_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    SYM_GENERATE_LOGIC_STARTUP_GENERATE = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-GENERATE", NULL, 0)));
    SYM_GENERATE_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void startupGenerate() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupGenerate1();
    }
    if (currentStartupTimePhaseP(4)) {
      oCANONICALVARIABLECOUNTERo = NULL_INTEGER;
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("TERM-GENERATION-EXCEPTION", "(DEFCLASS TERM-GENERATION-EXCEPTION (LOGIC-EXCEPTION) :PUBLIC? TRUE :DOCUMENTATION \"Signals an exception during term generation.\" :PUBLIC-SLOTS ((OFFENDING-TERM :TYPE OBJECT :REQUIRED? TRUE)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newTermGenerationException));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("GENERATE-EXPRESSION", "(DEFUN (GENERATE-EXPRESSION OBJECT) ((SELF OBJECT) (CANONICALIZEVARIABLENAMES? BOOLEAN)) :DOCUMENTATION \"Return an s-expression representing the source expression for 'self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&generateExpression)), NULL);
      defineFunctionObject("GENERATE-NAME-OF-VARIABLE", "(DEFUN (GENERATE-NAME-OF-VARIABLE SYMBOL) ((SELF PATTERN-VARIABLE)))", ((cpp_function_code)(&generateNameOfVariable)), NULL);
      defineFunctionObject("GENERATE-ONE-VARIABLE", "(DEFUN (GENERATE-ONE-VARIABLE OBJECT) ((SELF PATTERN-VARIABLE) (TYPED? BOOLEAN)))", ((cpp_function_code)(&generateOneVariable)), NULL);
      defineFunctionObject("GENERATE-ONE-QUANTIFIED-VARIABLE", "(DEFUN (GENERATE-ONE-QUANTIFIED-VARIABLE OBJECT) ((SELF PATTERN-VARIABLE) (TYPED? BOOLEAN)))", ((cpp_function_code)(&generateOneQuantifiedVariable)), NULL);
      defineFunctionObject("GENERATE-VARIABLES", "(DEFUN (GENERATE-VARIABLES CONS) ((VECTOR VECTOR) (TYPED? BOOLEAN)))", ((cpp_function_code)(&generateVariables)), NULL);
      defineFunctionObject("GENERATE-QUANTIFIED-VARIABLES", "(DEFUN (GENERATE-QUANTIFIED-VARIABLES CONS) ((VECTOR VECTOR) (TYPED? BOOLEAN)))", ((cpp_function_code)(&generateQuantifiedVariables)), NULL);
      defineFunctionObject("GENERATE-STELLA-COLLECTION", "(DEFUN (GENERATE-STELLA-COLLECTION CONS) ((SELF COLLECTION)))", ((cpp_function_code)(&generateStellaCollection)), NULL);
      defineFunctionObject("GENERATE-DESCRIPTION", "(DEFUN (GENERATE-DESCRIPTION OBJECT) ((SELF DESCRIPTION)))", ((cpp_function_code)(&generateDescription)), NULL);
      defineFunctionObject("GENERATE-ARGUMENTS", "(DEFUN (GENERATE-ARGUMENTS CONS) ((ARGUMENTS VECTOR)))", ((cpp_function_code)(&generateArguments)), NULL);
      defineFunctionObject("GENERATE-OPERATOR", "(DEFUN (GENERATE-OPERATOR SYMBOL) ((SELF PROPOSITION)))", ((cpp_function_code)(&generateOperator)), NULL);
      defineFunctionObject("GENERATE-PROPOSITION", "(DEFUN (GENERATE-PROPOSITION OBJECT) ((SELF PROPOSITION)))", ((cpp_function_code)(&generateProposition)), NULL);
      defineFunctionObject("GENERATE-FUNCTION-AS-TERM", "(DEFUN (GENERATE-FUNCTION-AS-TERM CONS) ((SELF PROPOSITION)))", ((cpp_function_code)(&generateFunctionAsTerm)), NULL);
      defineFunctionObject("GENERATE-FUNCTION-PROPOSITION", "(DEFUN (GENERATE-FUNCTION-PROPOSITION CONS) ((SELF PROPOSITION)))", ((cpp_function_code)(&generateFunctionProposition)), NULL);
      defineFunctionObject("GENERATE-SKOLEM", "(DEFUN (GENERATE-SKOLEM OBJECT) ((SELF SKOLEM)))", ((cpp_function_code)(&generateSkolem)), NULL);
      defineMethodObject("(DEFMETHOD (GENERATE-SPECIALIZED-TERM OBJECT) ((SELF LOGIC-THING)) :PUBLIC? TRUE :DOCUMENTATION \"Method to generate a specialized term for `self'.  This is designed\nto allow for extension of the term generation code to cover other\ntypes of objects for the logic.  This particular method will signal\nan error unless there is a surrogate-value-inverse link set.\")", wrapMethodCode(((cpp_method_code)(&LogicThing::generateSpecializedTerm))), NULL);
      defineFunctionObject("GENERATE-TERM", "(DEFUN (GENERATE-TERM OBJECT) ((SELF OBJECT)))", ((cpp_function_code)(&generateTerm)), NULL);
      defineFunctionObject("GENERATE-IMPLIES-PROPOSITION", "(DEFUN (GENERATE-IMPLIES-PROPOSITION CONS) ((SELF PROPOSITION)))", ((cpp_function_code)(&generateImpliesProposition)), NULL);
      defineFunctionObject("GENERATE-DESCRIPTION-PROPOSITION", "(DEFUN (GENERATE-DESCRIPTION-PROPOSITION CONS) ((SELF DESCRIPTION) (INVERT? BOOLEAN)))", ((cpp_function_code)(&generateDescriptionProposition)), NULL);
      defineFunctionObject("GENERATE-DESCRIPTIONS-AS-RULE", "(DEFUN (GENERATE-DESCRIPTIONS-AS-RULE CONS) ((HEAD DESCRIPTION) (TAIL DESCRIPTION) (RULE PROPOSITION) (REVERSEPOLARITY? BOOLEAN)))", ((cpp_function_code)(&generateDescriptionsAsRule)), NULL);
      defineFunctionObject("DEOBJECTIFY-TREE", "(DEFUN (DEOBJECTIFY-TREE OBJECT) ((SELF OBJECT)) :DOCUMENTATION \"Return a copy of `self' where all logic objects are\nreplaced by their `generated' parse-tree version.  This is useful to\nconvert the result of a retrieval query into a regular parse tree.\" :PUBLIC? TRUE)", ((cpp_function_code)(&deobjectifyTree)), NULL);
      defineFunctionObject("STARTUP-GENERATE", "(DEFUN STARTUP-GENERATE () :PUBLIC? TRUE)", ((cpp_function_code)(&startupGenerate)), NULL);
      { MethodSlot* function = lookupFunction(SYM_GENERATE_LOGIC_STARTUP_GENERATE);

        setDynamicSlotValue(function->dynamicSlots, SYM_GENERATE_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupGenerate"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFSPECIAL *CANONICALVARIABLENAMEMAPPING* KEY-VALUE-LIST NULL :DOCUMENTATION \"Maps variables to symbols in SYSTEM-DEFINED-ARGUMENT-NAMES.\")", &oCANONICALVARIABLENAMEMAPPINGo);
      defineGlobalVariableObject("(DEFSPECIAL *CANONICALVARIABLECOUNTER* INTEGER NULL :DOCUMENTATION \"Number of the last canonically-mapped variable.\")", &oCANONICALVARIABLECOUNTERo);
    }
  }
}

Surrogate* SGT_GENERATE_STELLA_THING = NULL;

Symbol* SYM_GENERATE_PL_KERNEL_KB_SETOF = NULL;

Symbol* SYM_GENERATE_PL_KERNEL_KB_LISTOF = NULL;

Symbol* SYM_GENERATE_LOGIC_COMPLEMENT_DESCRIPTION = NULL;

Symbol* SYM_GENERATE_STELLA_NOT = NULL;

Symbol* SYM_GENERATE_LOGIC_KAPPA = NULL;

Symbol* SYM_GENERATE_STELLA_NULL = NULL;

Surrogate* SGT_GENERATE_PL_KERNEL_KB_EQUIVALENT = NULL;

Symbol* SYM_GENERATE_STELLA_e = NULL;

Keyword* KWD_GENERATE_PREDICATE = NULL;

Keyword* KWD_GENERATE_ISA = NULL;

Keyword* KWD_GENERATE_EQUIVALENT = NULL;

Keyword* KWD_GENERATE_AND = NULL;

Keyword* KWD_GENERATE_OR = NULL;

Keyword* KWD_GENERATE_NOT = NULL;

Keyword* KWD_GENERATE_FUNCTION = NULL;

Keyword* KWD_GENERATE_EXISTS = NULL;

Symbol* SYM_GENERATE_STELLA_EXISTS = NULL;

Symbol* SYM_GENERATE_LOGIC_IO_VARIABLES = NULL;

Keyword* KWD_GENERATE_FORALL = NULL;

Symbol* SYM_GENERATE_LOGIC_BACKWARD_ONLYp = NULL;

Symbol* SYM_GENERATE_STELLA_FORALL = NULL;

Keyword* KWD_GENERATE_IMPLIES = NULL;

Keyword* KWD_GENERATE_FAIL = NULL;

Symbol* SYM_GENERATE_LOGIC_FAIL = NULL;

Keyword* KWD_GENERATE_CONSTANT = NULL;

Symbol* SYM_GENERATE_PL_KERNEL_KB_CONCEPT_PROTOTYPE = NULL;

Symbol* SYM_GENERATE_LOGIC_UNIDENTIFIED_SKOLEM = NULL;

Surrogate* SGT_GENERATE_LOGIC_PROPOSITION = NULL;

Surrogate* SGT_GENERATE_STELLA_LITERAL_WRAPPER = NULL;

Surrogate* SGT_GENERATE_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_GENERATE_LOGIC_PATTERN_VARIABLE = NULL;

Surrogate* SGT_GENERATE_LOGIC_SKOLEM = NULL;

Surrogate* SGT_GENERATE_LOGIC_LOGIC_OBJECT = NULL;

Symbol* SYM_GENERATE_LOGIC_UNNAMED_OBJECT = NULL;

Surrogate* SGT_GENERATE_STELLA_COLLECTION = NULL;

Surrogate* SGT_GENERATE_LOGIC_LOGIC_THING = NULL;

Symbol* SYM_GENERATE_LOGIC_ILLEGAL_TERM = NULL;

Symbol* SYM_GENERATE_PL_KERNEL_KB_SUBSET_OF = NULL;

Symbol* SYM_GENERATE_LOGIC_FORWARD_ONLYp = NULL;

Surrogate* SGT_GENERATE_STELLA_CONS = NULL;

Symbol* SYM_GENERATE_LOGIC_STARTUP_GENERATE = NULL;

Symbol* SYM_GENERATE_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
