//  -*- Mode: C++ -*-

// specialists.cc

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

ComputedProcedure* newComputedProcedure() {
  { ComputedProcedure* self = NULL;

    self = new ComputedProcedure();
    self->dynamicSlots = newKeyValueList();
    self->surrogateValueInverse = NULL;
    self->procedureFunction = NULL;
    self->procedureName = NULL;
    return (self);
  }
}

Surrogate* ComputedProcedure::primaryType() {
  { ComputedProcedure* self = this;

    return (SGT_SPECIALISTS_LOGIC_COMPUTED_PROCEDURE);
  }
}

Object* accessComputedProcedureSlotValue(ComputedProcedure* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SPECIALISTS_LOGIC_PROCEDURE_NAME) {
    if (setvalueP) {
      self->procedureName = ((Symbol*)(value));
    }
    else {
      value = self->procedureName;
    }
  }
  else if (slotname == SYM_SPECIALISTS_LOGIC_PROCEDURE_FUNCTION) {
    if (setvalueP) {
      self->procedureFunction = ((MethodSlot*)(value));
    }
    else {
      value = self->procedureFunction;
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

MethodSlot* stellaFunctionFromProcedure(ComputedProcedure* procedure) {
  if (((boolean)(procedure->procedureFunction))) {
    return (procedure->procedureFunction);
  }
  { Symbol* procedurename = procedure->procedureName;
    MethodSlot* stellafunction = NULL;

    if (!((boolean)(procedurename))) {
      procedurename = internSymbolInModule(procedure->surrogateValueInverse->symbolName, ((Module*)(procedure->surrogateValueInverse->homeContext)), true);
      procedure->procedureName = procedurename;
    }
    stellafunction = lookupFunction(procedurename);
    if (!((boolean)(stellafunction))) {
      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, procedure->surrogateValueInverse->homeModule());
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        stellafunction = lookupFunctionByName(procedurename->symbolName);
      }
    }
    if (!((boolean)(stellafunction))) {
      stellafunction = lookupFunctionByName(procedurename->symbolName);
    }
    if (!((boolean)(stellafunction))) {
      { Symbol* kernelname = lookupSymbolInModule(procedurename->symbolName, oPL_KERNEL_MODULEo, false);

        if (((boolean)(kernelname))) {
          stellafunction = lookupFunction(kernelname);
        }
      }
    }
    if (!((boolean)(stellafunction))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream000->nativeStream) << "ERROR: " << "Missing specialist, no STELLA function is named " << "`" << procedurename << "'" << "." << std::endl;
          helpSignalPropositionError(stream000, KWD_SPECIALISTS_ERROR);
        }
        throw *newPropositionError(stream000->theStringReader());
      }
    }
    if (oPOWERLOOM_EXECUTION_MODEo == KWD_SPECIALISTS_RELEASE) {
      procedure->procedureFunction = stellafunction;
    }
    return (stellafunction);
  }
}

cpp_function_code functionCodeFromProcedure(ComputedProcedure* procedure) {
  { MethodSlot* stellafunction = procedure->procedureFunction;

    if (!((boolean)(stellafunction))) {
      stellafunction = stellaFunctionFromProcedure(procedure);
    }
    return (stellafunction->functionCode);
  }
}

cpp_function_code lookupSpecialist(NamedDescription* description) {
  { Object* specialistprocedure = accessBinaryValue(description, SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_SPECIALIST);
    cpp_function_code functioncode = NULL;

    if (((boolean)(specialistprocedure))) {
      if (oREVERSEPOLARITYpo &&
          (!testPropertyP(specialistprocedure, SGT_SPECIALISTS_PL_KERNEL_KB_HANDLES_REVERSE_POLARITY))) {
        return (NULL);
      }
      else {
        functioncode = functionCodeFromProcedure(((ComputedProcedure*)(specialistprocedure)));
      }
    }
    if (functioncode == NULL) {
      if (((boolean)(description->nativeRelation())) &&
          (!classDescriptionP(description))) {
        functioncode = ((cpp_function_code)(&nativeSlotReaderSpecialist));
      }
    }
    return (functioncode);
  }
}

MethodSlot* lookupConstraintFunction(NamedDescription* description) {
  { Object* computationprocedure = accessBinaryValue(description, SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_CONSTRAINT);

    if (((boolean)(computationprocedure))) {
      return (stellaFunctionFromProcedure(((ComputedProcedure*)(computationprocedure))));
    }
    else {
      return (NULL);
    }
  }
}

cpp_function_code lookupConstraint(NamedDescription* description) {
  { MethodSlot* function = lookupConstraintFunction(description);

    if (((boolean)(function))) {
      return (function->functionCode);
    }
    else {
      return (NULL);
    }
  }
}

MethodSlot* lookupComputationFunction(NamedDescription* description) {
  { Object* computationprocedure = accessBinaryValue(description, SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_COMPUTATION);

    if (((boolean)(computationprocedure))) {
      return (stellaFunctionFromProcedure(((ComputedProcedure*)(computationprocedure))));
    }
    else {
      return (NULL);
    }
  }
}

cpp_function_code lookupComputation(NamedDescription* description) {
  { MethodSlot* function = lookupComputationFunction(description);

    if (((boolean)(function))) {
      return (function->functionCode);
    }
    else {
      return (NULL);
    }
  }
}

MethodSlot* lookupEvaluatorFunction(NamedDescription* description) {
  { Object* computationprocedure = accessBinaryValue(description, SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_EVALUATOR);

    if (((boolean)(computationprocedure))) {
      return (stellaFunctionFromProcedure(((ComputedProcedure*)(computationprocedure))));
    }
    else {
      return (NULL);
    }
  }
}

cpp_function_code lookupEvaluator(NamedDescription* description) {
  { MethodSlot* function = lookupEvaluatorFunction(description);

    if (((boolean)(function))) {
      return (function->functionCode);
    }
    else {
      return (NULL);
    }
  }
}

boolean successResultP(Keyword* result) {
  return ((result == KWD_SPECIALISTS_CONTINUING_SUCCESS) ||
      (result == KWD_SPECIALISTS_FINAL_SUCCESS));
}

boolean failureResultP(Keyword* result) {
  return ((result == KWD_SPECIALISTS_FAILURE) ||
      (result == KWD_SPECIALISTS_TERMINAL_FAILURE));
}

boolean continuingResultP(Keyword* result) {
  return ((result == KWD_SPECIALISTS_CONTINUING_SUCCESS) ||
      (result == KWD_SPECIALISTS_FAILURE));
}

boolean finalResultP(Keyword* result) {
  return ((result == KWD_SPECIALISTS_FINAL_SUCCESS) ||
      (result == KWD_SPECIALISTS_TERMINAL_FAILURE));
}

Keyword* selectTestResult(boolean successP, boolean terminalP, ControlFrame* frame) {
  // Helping function for specialists testing the validity of a
  // fully bound inference frame.  Based on the test result `success?'
  // and `reversePolarity?*', set the truth value of `frame' and return
  // an appropriate keyword.  The keyword will be either `:final-success'
  // `:terminal-failure' if `terminal?' is true.  Otherwise it will be
  // `:final-success' or `:failure'.
  if (successP == oREVERSEPOLARITYpo) {
    setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
    if (((boolean)(oQUERYITERATORo)) &&
        ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
      oQUERYITERATORo->partialMatchStrategy->setBasePartialMatchTruth(frame->proposition, KWD_SPECIALISTS_FAIL);
    }
    return ((terminalP ? KWD_SPECIALISTS_TERMINAL_FAILURE : KWD_SPECIALISTS_FAILURE));
  }
  else {
    setFrameTruthValue(frame, TRUE_TRUTH_VALUE);
    if (((boolean)(oQUERYITERATORo)) &&
        ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
      oQUERYITERATORo->partialMatchStrategy->setBasePartialMatchTruth(frame->proposition, KWD_SPECIALISTS_TRUE);
    }
    return (KWD_SPECIALISTS_FINAL_SUCCESS);
  }
}

Keyword* selectProofResult(boolean successP, boolean continuingP, boolean terminalP) {
  // Helping function for specialists.   Return the appropriate
  // keyword indicating success or failure of a proof.
  return ((successP ? ((continuingP ? KWD_SPECIALISTS_CONTINUING_SUCCESS : KWD_SPECIALISTS_FINAL_SUCCESS)) : ((terminalP ? KWD_SPECIALISTS_TERMINAL_FAILURE : KWD_SPECIALISTS_FAILURE))));
}

boolean nullWrapperP(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_SPECIALISTS_STELLA_THING)) {
      { Object* self000 = self;
        Thing* self = ((Thing*)(self000));

        return (self == NULL);
      }
    }
    else if (subtypeOfIntegerP(testValue000)) {
      { Object* self001 = self;
        IntegerWrapper* self = ((IntegerWrapper*)(self001));

        return (eqlP(self, NULL_INTEGER_WRAPPER));
      }
    }
    else if (subtypeOfStringP(testValue000)) {
      { Object* self002 = self;
        StringWrapper* self = ((StringWrapper*)(self002));

        return (eqlP(self, NULL_STRING_WRAPPER));
      }
    }
    else if (subtypeOfFloatP(testValue000)) {
      { Object* self003 = self;
        FloatWrapper* self = ((FloatWrapper*)(self003));

        return (eqlP(self, NULL_FLOAT_WRAPPER));
      }
    }
    else if (subtypeOfCharacterP(testValue000)) {
      { Object* self004 = self;
        CharacterWrapper* self = ((CharacterWrapper*)(self004));

        return (eqlP(self, NULL_CHARACTER_WRAPPER));
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALISTS_STELLA_FUNCTION_CODE_WRAPPER)) {
      { Object* self005 = self;
        FunctionCodeWrapper* self = ((FunctionCodeWrapper*)(self005));

        return (eqlP(self, NULL_FUNCTION_CODE_WRAPPER));
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALISTS_STELLA_METHOD_CODE_WRAPPER)) {
      { Object* self006 = self;
        MethodCodeWrapper* self = ((MethodCodeWrapper*)(self006));

        return (eqlP(self, NULL_METHOD_CODE_WRAPPER));
      }
    }
    else {
      std::cout << "Not prepared to handle native slots with type " << self->primaryType() << std::endl;
    }
  }
  return (false);
}

Keyword* nativeSlotReaderSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    NamedDescription* description = getDescription(((Surrogate*)(proposition->operatoR)));
    Object* argumentvalue = argumentBoundTo((proposition->arguments->theArray)[0]);
    Slot* slot = ((!classDescriptionP(description)) ? ((Slot*)(description->nativeRelation())) : NULL);
    boolean successP = false;

    lastmove = lastmove;
    if (((boolean)(argumentvalue)) &&
        (((boolean)(slot)) &&
         (isaP(argumentvalue, SGT_SPECIALISTS_STELLA_THING) &&
          (!slot->abstractP)))) {
      { Object* value = readSlotValue(((StandardObject*)(argumentvalue)), ((StorageSlot*)(slot)));

        if (!((boolean)(value))) {
          return (KWD_SPECIALISTS_FAILURE);
        }
        if (!nullWrapperP(value)) {
          if (functionDescriptionP(description)) {
            successP = bindVariableToValueP(((PatternVariable*)((proposition->arguments->theArray)[(proposition->arguments->length() - 1)])), value, true);
          }
          else {
            successP = eqlP(value, TRUE_WRAPPER);
          }
          return (selectTestResult(successP, true, frame));
        }
      }
    }
    return (KWD_SPECIALISTS_FAILURE);
  }
}

SubstringPositionIterator* newSubstringPositionIterator(const char* superString, const char* subString) {
  { SubstringPositionIterator* self = NULL;

    self = new SubstringPositionIterator();
    self->superString = superString;
    self->subString = subString;
    self->firstIterationP = true;
    self->value = NULL;
    self->subLength = strlen((self->subString));
    self->start = 0;
    return (self);
  }
}

Surrogate* SubstringPositionIterator::primaryType() {
  { SubstringPositionIterator* self = this;

    return (SGT_SPECIALISTS_LOGIC_SUBSTRING_POSITION_ITERATOR);
  }
}

Object* accessSubstringPositionIteratorSlotValue(SubstringPositionIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SPECIALISTS_LOGIC_SUPER_STRING) {
    if (setvalueP) {
      self->superString = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->superString);
    }
  }
  else if (slotname == SYM_SPECIALISTS_LOGIC_SUB_STRING) {
    if (setvalueP) {
      self->subString = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->subString);
    }
  }
  else if (slotname == SYM_SPECIALISTS_STELLA_START) {
    if (setvalueP) {
      self->start = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->start);
    }
  }
  else if (slotname == SYM_SPECIALISTS_LOGIC_SUB_LENGTH) {
    if (setvalueP) {
      self->subLength = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->subLength);
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

boolean SubstringPositionIterator::nextP() {
  { SubstringPositionIterator* it = this;

    { int p1 = stringSearch(it->superString, it->subString, it->start);

      if (p1 != NULL_INTEGER) {
        {
          it->value = cons(wrapInteger(p1), cons(wrapInteger(p1 + it->subLength), NIL));
          it->start = p1 + 1;
          return (true);
        }
      }
      else {
        {
          it->value = NULL;
          return (false);
        }
      }
    }
  }
}

int SubstringPositionIterator::length() {
  { SubstringPositionIterator* it = this;

    { int count = 0;
      const char* super = it->superString;
      const char* sub = it->subString;
      int p1 = stringSearch(super, sub, 0);

      while (p1 != NULL_INTEGER) {
        count = count + 1;
        p1 = stringSearch(super, sub, p1 + 1);
      }
      return (count);
    }
  }
}

boolean boundComputationInputSkolemP(Skolem* skolem) {
  if (logicalCollectionP(skolem)) {
    return (true);
  }
  else {
    { Proposition* prop = skolem->definingProposition;

      return (((boolean)(prop)) &&
          testPropertyP(getDescription(((Surrogate*)(prop->operatoR))), SGT_SPECIALISTS_PL_KERNEL_KB_TOTAL));
    }
  }
}

Surrogate* argumentTargetType(List* parametertypes, int ninputtypes, int argindex) {
  { StandardObject* targettype = ((StandardObject*)(parametertypes->nth(stella::integerMin(argindex, ninputtypes - 1))));

    if (typeSpecToBaseType(targettype) == SGT_SPECIALISTS_STELLA_CONS) {
      if (subtypeOfParametricTypeSpecifierP(safePrimaryType(targettype))) {
        { StandardObject* targettype000 = targettype;
          ParametricTypeSpecifier* targettype = ((ParametricTypeSpecifier*)(targettype000));

          return (typeSpecToBaseType(((StandardObject*)(targettype->specifierParameterTypes->first()))));
        }
      }
      else {
        return (SGT_SPECIALISTS_STELLA_OBJECT);
      }
    }
    else {
      return (((Surrogate*)(targettype)));
    }
  }
}

Object* computeRelationValue(Proposition* proposition, MethodSlot* computation, boolean errorP) {
  { Vector* arguments = proposition->arguments;
    NamedDescription* description = getDescription(((Surrogate*)(proposition->operatoR)));
    boolean functionP = functionDescriptionP(description);
    List* argtypes = description->ioVariableTypes;
    int ninputtypes = argtypes->length() - ((functionP ? 1 : 0));
    List* compargtypes = NULL;
    Object* value = NULL;
    Cons* boundarguments = NIL;
    boolean variablearityP = variableArityP(description);

    if (!((boolean)(computation))) {
      computation = lookupComputationFunction(description);
    }
    compargtypes = computation->methodParameterTypeSpecifiers_reader();
    { Object* arg = NULL;
      Vector* vector000 = arguments;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = arguments->length() - ((functionP ? 2 : 1));
      Cons* collect000 = NULL;

      for  (; (index000 < length000) &&
                (iter000 <= upperBound000); 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        arg = (vector000->theArray)[index000];
        i = iter000;
        value = safeArgumentBoundTo(arg);
        if (!((boolean)(value))) {
          return (NULL);
        }
        else if (checkStrictTypeP(value, argumentTargetType(argtypes, ninputtypes, i), true) &&
            subtypeOfP(value->primaryType(), argumentTargetType(compargtypes, ninputtypes, i))) {
        }
        else if (skolemP(value) &&
            (!boundComputationInputSkolemP(((Skolem*)(value))))) {
          return (NULL);
        }
        else {
          if (errorP) {
            { OutputStringStream* stream000 = newOutputStringStream();

              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                *(stream000->nativeStream) << "ERROR: " << "compute-relation-value: incorrect argument type for " << "`" << value << "'" << " in " << "`" << proposition << "'" << "." << std::endl;
                helpSignalPropositionError(stream000, KWD_SPECIALISTS_ERROR);
              }
              throw *newPropositionError(stream000->theStringReader());
            }
          }
          else {
            return (NULL);
          }
        }
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(value, NIL);
            if (boundarguments == NIL) {
              boundarguments = collect000;
            }
            else {
              addConsToEndOfConsList(boundarguments, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(value, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    if (variablearityP) {
      { int nfixed = argtypes->length() - ((functionP ? 2 : 1));

        if (nfixed == 0) {
          boundarguments = cons(boundarguments, NIL);
        }
        else if (boundarguments->length() >= nfixed) {
          boundarguments->nthRestSetter(cons(boundarguments->nthRest(nfixed), NIL), nfixed);
        }
        else {
          return (NULL);
        }
      }
    }
    value = apply(computation->functionCode, boundarguments);
    return (value);
  }
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* computationSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* value = computeRelationValue(proposition, NULL, false);
    BooleanWrapper* successP = NULL;

    if (!((boolean)(value))) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    if (functionDescriptionP(getDescription(((Surrogate*)(proposition->operatoR))))) {
      successP = (bindArgumentToValueP((proposition->arguments->theArray)[(proposition->arguments->length() - 1)], value, true) ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
    else {
      successP = ((BooleanWrapper*)(value));
    }
    return (selectTestResult(coerceWrappedBooleanToBoolean(successP), true, frame));
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

Object* computeSimpleRelationConstraint(Proposition* proposition, MethodSlot* computation, boolean errorP, int& _Return1) {
  { Vector* arguments = proposition->arguments;
    NamedDescription* description = getDescription(((Surrogate*)(proposition->operatoR)));
    List* argtypes = description->ioVariableTypes;
    int ninputtypes = argtypes->length();
    List* compargtypes = NULL;
    Object* value = NULL;
    int nullcount = 0;
    int variableindex = -1;
    Cons* boundarguments = NIL;

    if (!((boolean)(computation))) {
      computation = lookupConstraintFunction(description);
    }
    compargtypes = computation->methodParameterTypeSpecifiers_reader();
    { Object* arg = NULL;
      Vector* vector000 = arguments;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter000 = 0;
      Cons* collect000 = NULL;

      for  (; index000 < length000; 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        arg = (vector000->theArray)[index000];
        i = iter000;
        value = safeArgumentBoundTo(arg);
        if (!((boolean)(value))) {
          value = NULL;
          nullcount = nullcount + 1;
          variableindex = i;
        }
        else if (checkStrictTypeP(value, argumentTargetType(argtypes, ninputtypes, i), true) &&
            subtypeOfP(value->primaryType(), argumentTargetType(compargtypes, ninputtypes + 1, i + 1))) {
        }
        else if (skolemP(value) &&
            (!boundComputationInputSkolemP(((Skolem*)(value))))) {
          value = NULL;
          nullcount = nullcount + 1;
          variableindex = i;
        }
        else {
          if (errorP) {
            { OutputStringStream* stream000 = newOutputStringStream();

              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                *(stream000->nativeStream) << "ERROR: " << "compute-relation-constraint: incorrect argument type for " << "`" << value << "'" << " in " << "`" << proposition << "'" << "." << std::endl;
                helpSignalPropositionError(stream000, KWD_SPECIALISTS_ERROR);
              }
              throw *newPropositionError(stream000->theStringReader());
            }
          }
          else {
            _Return1 = -1;
            return (NULL);
          }
        }
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(value, NIL);
            if (boundarguments == NIL) {
              boundarguments = collect000;
            }
            else {
              addConsToEndOfConsList(boundarguments, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(value, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    switch (nullcount) {
      case 0: 
        value = apply(computation->functionCode, cons(wrapInteger(variableindex), boundarguments));
        break;
      case 1: 
        if (oREVERSEPOLARITYpo) {
          _Return1 = -1;
          return (NULL);
        }
        value = apply(computation->functionCode, cons(wrapInteger(variableindex), boundarguments));
        break;
      default:
        _Return1 = -1;
        return (NULL);
        break;
    }
    _Return1 = variableindex;
    return (value);
  }
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* constraintSpecialist(ControlFrame* frame, Keyword* lastmove) {
  lastmove = lastmove;
  { Object* value = NULL;
    int variableindex = NULL_INTEGER;

    value = computeSimpleRelationConstraint(frame->proposition, NULL, false, variableindex);
    if (!((boolean)(value))) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    switch (variableindex) {
      case -1: 
        return (selectTestResult(((BooleanWrapper*)(value)) == TRUE_WRAPPER, true, frame));
      default:
        return (selectTestResult(bindArgumentToValueP((frame->proposition->arguments->theArray)[variableindex], value, true), true, frame));
    }
  }
}

Keyword* squareRootSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* mainarg = (proposition->arguments->theArray)[0];
    Object* mainargvalue = argumentBoundTo(mainarg);
    Object* rootarg = (proposition->arguments->theArray)[1];
    Object* rootargvalue = argumentBoundTo(rootarg);
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)));
    Cons* collection = NIL;

    lastmove = lastmove;
    if (!((boolean)(iterator))) {
      if (!((boolean)(mainargvalue))) {
        if (!((boolean)(rootargvalue))) {
          return (KWD_SPECIALISTS_TERMINAL_FAILURE);
        }
        else {
          if (isaP(rootargvalue, SGT_SPECIALISTS_STELLA_NUMBER_WRAPPER)) {
            if (oREVERSEPOLARITYpo) {
              return (KWD_SPECIALISTS_FAILURE);
            }
            else {
              return (selectProofResult(bindArgumentToValueP(mainarg, timesComputation(((NumberWrapper*)(rootargvalue)), ((NumberWrapper*)(rootargvalue))), true), false, true));
            }
          }
          else {
            return (KWD_SPECIALISTS_TERMINAL_FAILURE);
          }
        }
      }
      else {
        if (isaP(mainargvalue, SGT_SPECIALISTS_STELLA_NUMBER_WRAPPER)) {
          if (arithmeticLessTest(((NumberWrapper*)(mainargvalue)), wrapInteger(0))) {
            return (KWD_SPECIALISTS_TERMINAL_FAILURE);
          }
          else {
            if ((!((boolean)(rootargvalue))) &&
                oREVERSEPOLARITYpo) {
              return (KWD_SPECIALISTS_FAILURE);
            }
            else {
              { NumberWrapper* sqrt = sqrtComputation(((NumberWrapper*)(mainargvalue)));

                collection = consList(2, sqrt, negateComputation(sqrt));
              }
            }
          }
        }
        else {
          return (KWD_SPECIALISTS_TERMINAL_FAILURE);
        }
      }
    }
    if (((boolean)(rootargvalue))) {
      return (selectTestResult(arithmeticEqualTest(((NumberWrapper*)(rootargvalue)), ((NumberWrapper*)(collection->value))) ||
          arithmeticEqualTest(((NumberWrapper*)(rootargvalue)), ((NumberWrapper*)(collection->rest->value))), true, frame));
    }
    if (!((boolean)(iterator))) {
      iterator = collection->allocateIterator();
      setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, iterator, NULL);
    }
    if (iterator->nextP() &&
        bindArgumentToValueP(rootarg, iterator->value, true)) {
      return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
    }
    else {
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
  }
}

Keyword* absoluteValueSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* mainarg = (proposition->arguments->theArray)[0];
    Object* mainargvalue = argumentBoundTo(mainarg);
    Object* absarg = (proposition->arguments->theArray)[1];
    Object* absargvalue = argumentBoundTo(absarg);
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)));
    Cons* collection = NIL;

    lastmove = lastmove;
    if (!((boolean)(iterator))) {
      if (!((boolean)(absargvalue))) {
        if (!((boolean)(mainargvalue))) {
          return (KWD_SPECIALISTS_TERMINAL_FAILURE);
        }
        else {
          if (isaP(mainargvalue, SGT_SPECIALISTS_STELLA_NUMBER_WRAPPER)) {
            if (oREVERSEPOLARITYpo) {
              return (KWD_SPECIALISTS_FAILURE);
            }
            else {
              return (selectProofResult(bindArgumentToValueP(absarg, absComputation(((NumberWrapper*)(mainargvalue))), true), false, true));
            }
          }
          else {
            return (KWD_SPECIALISTS_TERMINAL_FAILURE);
          }
        }
      }
      else {
        if (isaP(absargvalue, SGT_SPECIALISTS_STELLA_NUMBER_WRAPPER)) {
          if (arithmeticLessTest(((NumberWrapper*)(absargvalue)), wrapInteger(0))) {
            return (KWD_SPECIALISTS_TERMINAL_FAILURE);
          }
          else {
            if (oREVERSEPOLARITYpo) {
              return (KWD_SPECIALISTS_FAILURE);
            }
            else {
              collection = consList(2, absargvalue, negateComputation(((NumberWrapper*)(absargvalue))));
            }
          }
        }
        else {
          return (KWD_SPECIALISTS_TERMINAL_FAILURE);
        }
      }
    }
    if (((boolean)(mainargvalue))) {
      return (selectTestResult(arithmeticEqualTest(((NumberWrapper*)(mainargvalue)), ((NumberWrapper*)(collection->value))) ||
          arithmeticEqualTest(((NumberWrapper*)(mainargvalue)), ((NumberWrapper*)(collection->rest->value))), true, frame));
    }
    if (!((boolean)(iterator))) {
      iterator = collection->allocateIterator();
      setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, iterator, NULL);
    }
    if (iterator->nextP() &&
        bindArgumentToValueP(mainarg, iterator->value, true)) {
      return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
    }
    else {
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

List* enumerationsContainingMember(Object* self) {
  { List* list = newList();

    { Proposition* p = NULL;
      Iterator* iter000 = allTrueDependentPropositions(self, SGT_SPECIALISTS_PL_KERNEL_KB_COLLECTIONOF, true);

      for (; iter000->nextP(); ) {
        p = ((Proposition*)(iter000->value));
        { Object* skolemlist = (p->arguments->theArray)[(p->arguments->length() - 1)];

          if (!eqlP(self, skolemlist)) {
            list->push(skolemlist);
          }
        }
      }
    }
    return (list);
  }
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* memberOfSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Vector* arguments = proposition->arguments;
    Object* memberarg = (arguments->theArray)[0];
    Object* member = argumentBoundTo(memberarg);
    Object* collectionarg = (arguments->theArray)[1];
    Object* collection = argumentBoundTo(collectionarg);
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)));

    if (lastmove == KWD_SPECIALISTS_UP_TRUE) {
      return ((((boolean)(frame->down)) ? KWD_SPECIALISTS_CONTINUING_SUCCESS : KWD_SPECIALISTS_FINAL_SUCCESS));
    }
    else if (lastmove == KWD_SPECIALISTS_UP_FAIL) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    else {
    }
    if (!((boolean)(iterator))) {
      if (!((boolean)(collection))) {
        if (!((boolean)(member))) {
          return (KWD_SPECIALISTS_FAILURE);
        }
        iterator = ((ListIterator*)(enumerationsContainingMember(member)->allocateIterator()));
      }
      else {
        { Surrogate* testValue000 = safePrimaryType(collection);

          if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION)) {
            { Object* collection000 = collection;
              NamedDescription* collection = ((NamedDescription*)(collection000));

              { Proposition* isaprop = createProposition(SYM_SPECIALISTS_STELLA_ISA, 1);

                isaprop->operatoR = collection->surrogateValueInverse;
                (isaprop->arguments->theArray)[0] = memberarg;
                createDownFrame(frame, isaprop);
                return (KWD_SPECIALISTS_MOVE_DOWN);
              }
            }
          }
          else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_DESCRIPTION)) {
            { Object* collection001 = collection;
              Description* collection = ((Description*)(collection001));

              { boolean testValue001 = false;

                testValue001 = collection->arity() == 1;
                if (testValue001) {
                  if (!((boolean)(((Vector*)(dynamicSlotValue(collection->dynamicSlots, SYM_SPECIALISTS_LOGIC_EXTERNAL_VARIABLES, NULL)))))) {
                    testValue001 = true;
                  }
                  else {
                    { boolean alwaysP000 = true;

                      { PatternVariable* var = NULL;
                        Vector* vector000 = ((Vector*)(dynamicSlotValue(collection->dynamicSlots, SYM_SPECIALISTS_LOGIC_EXTERNAL_VARIABLES, NULL)));
                        int index000 = 0;
                        int length000 = vector000->length();

                        for  (; index000 < length000; 
                              index000 = index000 + 1) {
                          var = ((PatternVariable*)((vector000->theArray)[index000]));
                          if (!((boolean)(safeArgumentBoundTo(var)))) {
                            alwaysP000 = false;
                            break;
                          }
                        }
                      }
                      testValue001 = alwaysP000;
                    }
                  }
                }
                if (testValue001) {
                  {
                    if (overlayWithPatternFrameP(createDownFrame(frame, NULL), collection, stella::vector(1, memberarg))) {
                      return (KWD_SPECIALISTS_MOVE_DOWN);
                    }
                    else {
                      return (KWD_SPECIALISTS_FAILURE);
                    }
                  }
                }
                else {
                  {
                    return (KWD_SPECIALISTS_FAILURE);
                  }
                }
              }
            }
          }
          else if (subtypeOfP(testValue000, SGT_SPECIALISTS_STELLA_COLLECTION)) {
            { Object* collection002 = collection;
              stella::Collection* collection = ((stella::Collection*)(collection002));

              if (!((boolean)(member))) {
                iterator = ((ListIterator*)(assertedCollectionMembers(collection, false)->allocateIterator()));
              }
              else {
                return (selectTestResult(memberOfCollectionP(member, collection), false, frame));
              }
            }
          }
          else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_LOGIC_OBJECT)) {
            { Object* collection003 = collection;
              LogicObject* collection = ((LogicObject*)(collection003));

              if (!((boolean)(member))) {
                iterator = ((ListIterator*)(assertedCollectionMembers(collection, false)->allocateIterator()));
              }
              else {
                return (selectTestResult(memberOfCollectionP(member, collection), false, frame));
              }
            }
          }
          else {
            return (KWD_SPECIALISTS_FAILURE);
          }
        }
      }
      setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, iterator, NULL);
    }
    while (iterator->nextP()) {
      if (!((boolean)(collection))) {
        if (bindVariableToValueP(((PatternVariable*)(collectionarg)), valueOf(iterator->value), true)) {
          return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
        }
      }
      else {
        if (bindVariableToValueP(((PatternVariable*)(memberarg)), valueOf(iterator->value), true)) {
          return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
        }
      }
    }
    return (KWD_SPECIALISTS_FAILURE);
  }
}

void memberOfEvaluator(Proposition* self) {
  { Object* member = valueOf((self->arguments->theArray)[0]);
    Object* collection = valueOf((self->arguments->theArray)[1]);

    if (trueP(self)) {
      if (isaP(collection, SGT_SPECIALISTS_LOGIC_DESCRIPTION) &&
          (isaP(member, SGT_SPECIALISTS_LOGIC_LOGIC_OBJECT) &&
           (!namedDescriptionP(((Description*)(collection)))))) {
        inheritUnnamedDescription(((LogicObject*)(member)), ((Description*)(collection)), defaultTrueP(self));
      }
      if (logicalCollectionP(collection)) {
        { 
          BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, true);
          if (memberOfCollectionP(member, collection) &&
              (!skolemP(member))) {
            signalTruthValueClash(self);
          }
        }
      }
    }
  }
}

Keyword* instanceOfSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Vector* arguments = proposition->arguments;
    Object* memberarg = (arguments->theArray)[0];
    Object* member = argumentBoundTo(memberarg);
    Object* collectionarg = (arguments->theArray)[1];
    Object* collection = argumentBoundTo(collectionarg);
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)));

    if (lastmove == KWD_SPECIALISTS_UP_TRUE) {
      return ((((boolean)(frame->down)) ? KWD_SPECIALISTS_CONTINUING_SUCCESS : KWD_SPECIALISTS_FINAL_SUCCESS));
    }
    else if (lastmove == KWD_SPECIALISTS_UP_FAIL) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    else {
    }
    if (!((boolean)(iterator))) {
      if (((boolean)(collection))) {
        if (classP(collection) &&
            isaP(collection, SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION)) {
          { Proposition* isaproposition = createProposition(SYM_SPECIALISTS_STELLA_ISA, 1);

            isaproposition->operatoR = ((NamedDescription*)(collection))->surrogateValueInverse;
            (isaproposition->arguments->theArray)[0] = memberarg;
            createSubgoalFrame(frame, isaproposition, NULL);
            return (KWD_SPECIALISTS_MOVE_DOWN);
          }
        }
        else if (!((boolean)(member))) {
          createSubgoalFrame(frame, frame->proposition, KWD_SPECIALISTS_SCAN_COLLECTION);
          return (KWD_SPECIALISTS_MOVE_DOWN);
        }
        else {
          if (memberOfCollectionP(member, collection)) {
            return (KWD_SPECIALISTS_FINAL_SUCCESS);
          }
          else {
            return (KWD_SPECIALISTS_FAILURE);
          }
        }
      }
      else if (((boolean)(member))) {
        iterator = allTypes(member)->allocateIterator();
        setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, iterator, NULL);
      }
      else {
        return (KWD_SPECIALISTS_FAILURE);
      }
    }
    if (((boolean)(iterator))) {
      while (iterator->nextP()) {
        if (bindVariableToValueP(((PatternVariable*)(collectionarg)), iterator->value, true)) {
          return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
        }
      }
      return (KWD_SPECIALISTS_FAILURE);
    }
    return (KWD_SPECIALISTS_FAILURE);
  }
}

Keyword* buggyDirectInstanceOfSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Vector* arguments = proposition->arguments;
    Object* memberarg = (arguments->theArray)[0];
    Object* member = argumentBoundTo(memberarg);
    Object* collectionarg = (arguments->theArray)[1];
    Object* collection = argumentBoundTo(collectionarg);
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)));

    if (lastmove == KWD_SPECIALISTS_UP_TRUE) {
      return ((((boolean)(frame->down)) ? KWD_SPECIALISTS_CONTINUING_SUCCESS : KWD_SPECIALISTS_FINAL_SUCCESS));
    }
    else if (lastmove == KWD_SPECIALISTS_UP_FAIL) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    else {
    }
    if (!((boolean)(iterator))) {
      if (((boolean)(collection)) &&
          (classP(collection) &&
           isaP(collection, SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION))) {
        if (!((boolean)(member))) {
          iterator = allExtensionMembers(((NamedDescription*)(collection)));
        }
        else if (ASSERTION_INFERENCE->levellizedTestTypeOnInstanceP(member, objectSurrogate(collection))) {
          return (KWD_SPECIALISTS_FINAL_SUCCESS);
        }
        else {
          return (KWD_SPECIALISTS_FAILURE);
        }
      }
      else if (((boolean)(member))) {
        iterator = allDirectTypes(member)->allocateIterator();
      }
      else {
        return (KWD_SPECIALISTS_FAILURE);
      }
      setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, iterator, NULL);
    }
    if (((boolean)(iterator))) {
      while (iterator->nextP()) {
        { Object* value = iterator->value;

          if (subtypeOfP(safePrimaryType(value), SGT_SPECIALISTS_LOGIC_PROPOSITION)) {
            { Object* value000 = value;
              Proposition* value = ((Proposition*)(value000));

              if (bindVariableToValueP(((PatternVariable*)(memberarg)), (value->arguments->theArray)[0], true)) {
                return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
              }
            }
          }
          else {
            if (bindVariableToValueP(((PatternVariable*)(collectionarg)), value, true)) {
              return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
            }
          }
        }
      }
      return (KWD_SPECIALISTS_FAILURE);
    }
    return (KWD_SPECIALISTS_FAILURE);
  }
}

Keyword* directInstanceOfSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Vector* arguments = frame->proposition->arguments;
    Object* memberarg = (arguments->theArray)[0];
    Object* collectionarg = (arguments->theArray)[1];

    if ((lastmove == KWD_SPECIALISTS_DOWN) &&
        ((!((boolean)(frame->down))) &&
         (!((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)))))))) {
      { Object* member = argumentBoundTo(memberarg);
        Object* collection = argumentBoundTo(collectionarg);

        if (((boolean)(member)) &&
            ((boolean)(collection))) {
          if (allDirectTypes(member)->memberP(collection)) {
            return (KWD_SPECIALISTS_FINAL_SUCCESS);
          }
          else {
            return (KWD_SPECIALISTS_TERMINAL_FAILURE);
          }
        }
        else if (((boolean)(member))) {
          setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, allDirectTypes(member)->allocateIterator(), NULL);
        }
      }
    }
    { Keyword* instanceofvalue = instanceOfSpecialist(frame, lastmove);

      if ((instanceofvalue == KWD_SPECIALISTS_CONTINUING_SUCCESS) ||
          (instanceofvalue == KWD_SPECIALISTS_FINAL_SUCCESS)) {
        if (((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)))))) {
          return (instanceofvalue);
        }
        else if (allDirectTypes(argumentBoundTo(memberarg))->memberP(argumentBoundTo(collectionarg))) {
          return (instanceofvalue);
        }
        else {
          return (KWD_SPECIALISTS_MOVE_DOWN);
        }
      }
      else {
        return (instanceofvalue);
      }
    }
  }
}

Keyword* assertedInstanceOfSpecialist(ControlFrame* frame, Keyword* lastmove) {
  lastmove = lastmove;
  { Proposition* proposition = frame->proposition;
    Vector* arguments = proposition->arguments;
    Object* memberarg = (arguments->theArray)[0];
    Object* member = argumentBoundTo(memberarg);
    Object* collectionarg = (arguments->theArray)[1];
    Object* collection = argumentBoundTo(collectionarg);
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)));

    if (!((boolean)(iterator))) {
      if (((boolean)(member))) {
        iterator = allTrueDependentIsaPropositions(member);
      }
      else if (((boolean)(collection)) &&
          (classP(collection) &&
           isaP(collection, SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION))) {
        iterator = allTrueExtensionMembers(((NamedDescription*)(collection)), false);
      }
      else {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, iterator, NULL);
    }
    while (iterator->nextP()) {
      { Proposition* isaprop = ((Proposition*)(iterator->value));
        NamedDescription* isatype = getDescription(((Surrogate*)(isaprop->operatoR)));
        Object* isaarg = (isaprop->arguments->theArray)[0];

        if (assertedTrueP(isaprop) &&
            (bindArgumentToValueP(collectionarg, isatype, true) &&
             bindArgumentToValueP(memberarg, isaarg, true))) {
          if ((!((boolean)(member))) ||
              (!((boolean)(collection)))) {
            return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
          }
          else {
            return (KWD_SPECIALISTS_FINAL_SUCCESS);
          }
        }
      }
    }
    return (KWD_SPECIALISTS_TERMINAL_FAILURE);
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

boolean testDisjointTermsP(Object* term1, Object* term2) {
  if (subtypeOfP(safePrimaryType(term1), SGT_SPECIALISTS_LOGIC_DESCRIPTION)) {
    { Object* term1000 = term1;
      Description* term1 = ((Description*)(term1000));

      if (subtypeOfP(safePrimaryType(term2), SGT_SPECIALISTS_LOGIC_DESCRIPTION)) {
        { Object* term2000 = term2;
          Description* term2 = ((Description*)(term2000));

          if (currentInferenceLevel() == REFUTATION_INFERENCE) {
            return (expensiveDisjointTermsP(term1, term2));
          }
          else {
            return (disjointTermsP(term1, term2));
          }
        }
      }
      else {
        return (false);
      }
    }
  }
  else {
    return (false);
  }
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* subsetOfSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* subcollectionarg = (proposition->arguments->theArray)[0];
    Object* supercollectionarg = (proposition->arguments->theArray)[1];
    Object* subcollection = equivalentValueOf(argumentBoundTo(subcollectionarg));
    Object* supercollection = equivalentValueOf(argumentBoundTo(supercollectionarg));
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)));

    lastmove = lastmove;
    if (!((boolean)(iterator))) {
      if (((boolean)(subcollection)) &&
          ((boolean)(supercollection))) {
        if (isaP(subcollection, SGT_SPECIALISTS_LOGIC_LOGIC_OBJECT) &&
            (isaP(supercollection, SGT_SPECIALISTS_LOGIC_LOGIC_OBJECT) &&
             collectionImpliesCollectionP(((LogicObject*)(subcollection)), ((LogicObject*)(supercollection))))) {
          return (selectTestResult(true, true, frame));
        }
        else if (testDisjointTermsP(subcollection, supercollection)) {
          return (selectTestResult(false, true, frame));
        }
        else {
          return (KWD_SPECIALISTS_FAILURE);
        }
      }
      else if (((boolean)(subcollection))) {
        { Surrogate* testValue000 = safePrimaryType(subcollection);

          if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_LOGIC_OBJECT)) {
            { Object* subcollection000 = subcollection;
              LogicObject* subcollection = ((LogicObject*)(subcollection000));

              iterator = cons(subcollection, NIL)->allocateIterator()->concatenate(allSupercollections(subcollection), 0);
            }
          }
          else if (subtypeOfP(testValue000, SGT_SPECIALISTS_STELLA_COLLECTION)) {
            { Object* subcollection001 = subcollection;
              stella::Collection* subcollection = ((stella::Collection*)(subcollection001));

              return (KWD_SPECIALISTS_FAILURE);
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
      else if (((boolean)(supercollection))) {
        { Surrogate* testValue001 = safePrimaryType(supercollection);

          if (subtypeOfP(testValue001, SGT_SPECIALISTS_LOGIC_LOGIC_OBJECT)) {
            { Object* supercollection000 = supercollection;
              LogicObject* supercollection = ((LogicObject*)(supercollection000));

              iterator = cons(supercollection, NIL)->allocateIterator()->concatenate(allSubcollections(supercollection), 0);
            }
          }
          else if (subtypeOfP(testValue001, SGT_SPECIALISTS_STELLA_COLLECTION)) {
            { Object* supercollection001 = supercollection;
              stella::Collection* supercollection = ((stella::Collection*)(supercollection001));

              return (KWD_SPECIALISTS_FAILURE);
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
      else {
        std::cout << std::endl << " Found 'subset-of' goal with two unbound arguments." << std::endl << "   Possibly the query needs rewriting." << std::endl << std::endl;
        return (KWD_SPECIALISTS_FAILURE);
      }
      setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, iterator, NULL);
    }
    while (iterator->nextP()) {
      { Object* value = valueOf(iterator->value);

        if (true &&
            ((((boolean)(subcollection)) ? bindVariableToValueP(((PatternVariable*)(supercollectionarg)), value, true) : bindVariableToValueP(((PatternVariable*)(subcollectionarg)), value, true)))) {
          return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
        }
      }
    }
    return (KWD_SPECIALISTS_FAILURE);
  }
}

Keyword* holdsSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* holdsproposition = frame->proposition;
    Vector* holdsarguments = holdsproposition->arguments;
    int holdsarity = holdsarguments->length() - 1;
    Object* description = argumentBoundTo((holdsarguments->theArray)[0]);

    if (((boolean)(description))) {
      if (lastmove == KWD_SPECIALISTS_UP_TRUE) {
        return ((((boolean)(frame->down)) ? KWD_SPECIALISTS_CONTINUING_SUCCESS : KWD_SPECIALISTS_FINAL_SUCCESS));
      }
      else if (lastmove == KWD_SPECIALISTS_UP_FAIL) {
        return (KWD_SPECIALISTS_FAILURE);
      }
      else if (lastmove == KWD_SPECIALISTS_DOWN) {
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      { Surrogate* testValue000 = safePrimaryType(description);

        if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION)) {
          { Object* description000 = description;
            NamedDescription* description = ((NamedDescription*)(description000));

            { int argcountminus1 = holdsarguments->length() - 1;
              Symbol* kind = SYM_SPECIALISTS_STELLA_PREDICATE;
              Proposition* relationproposition = NULL;
              Surrogate* relationref = description->surrogateValueInverse;

              if (classDescriptionP(description)) {
                kind = SYM_SPECIALISTS_STELLA_ISA;
              }
              else if (functionDescriptionP(description)) {
                kind = SYM_SPECIALISTS_STELLA_FUNCTION;
              }
              relationproposition = createProposition(kind, argcountminus1);
              relationproposition->operatoR = relationref;
              { int i = NULL_INTEGER;
                int iter000 = 0;
                int upperBound000 = argcountminus1 - 1;

                for  (; iter000 <= upperBound000; 
                      iter000 = iter000 + 1) {
                  i = iter000;
                  (relationproposition->arguments->theArray)[i] = ((holdsarguments->theArray)[(i + 1)]);
                }
              }
              createSubgoalFrame(frame, relationproposition, NULL);
              return (KWD_SPECIALISTS_MOVE_DOWN);
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_DESCRIPTION)) {
          { Object* description001 = description;
            Description* description = ((Description*)(description001));

            { int argcountminus1 = holdsarguments->length() - 1;
              Proposition* dummyproposition = createProposition(SYM_SPECIALISTS_STELLA_DUMMY, argcountminus1);
              ControlFrame* subgoalframe = createSubgoalFrame(frame, dummyproposition, KWD_SPECIALISTS_FULL_SUBQUERY);

              { int i = NULL_INTEGER;
                int iter001 = 0;
                int upperBound001 = argcountminus1 - 1;

                for  (; iter001 <= upperBound001; 
                      iter001 = iter001 + 1) {
                  i = iter001;
                  (dummyproposition->arguments->theArray)[i] = ((holdsarguments->theArray)[(i + 1)]);
                }
              }
              setDynamicSlotValue(subgoalframe->dynamicSlots, SYM_SPECIALISTS_LOGIC_DESCRIPTION, description, NULL);
              return (KWD_SPECIALISTS_MOVE_DOWN);
            }
          }
        }
        else {
        }
      }
    }
    else {
      { Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)));
        Object* backlinkedarg = NULL;
        int backlinkedargposition = -1;
        boolean nomatchesP = false;

        nomatchesP = nomatchesP;
        if (!((boolean)(iterator))) {
          backlinkedarg = selectArgumentWithBacklinks(holdsproposition, nomatchesP);
          if (((boolean)(backlinkedarg))) {
            { int value000 = NULL_INTEGER;

              { int i = NULL_INTEGER;
                IntegerIntervalIterator* iter002 = interval(-1, NULL_INTEGER);
                Object* arg = NULL;
                Vector* vector000 = holdsarguments;
                int index000 = 0;
                int length000 = vector000->length();

                for  (; iter002->nextP() &&
                          (index000 < length000); 
                      index000 = index000 + 1) {
                  i = iter002->value;
                  arg = (vector000->theArray)[index000];
                  if ((i >= 0) &&
                      eqlP(backlinkedarg, argumentBoundTo(arg))) {
                    value000 = i;
                    break;
                  }
                }
              }
              backlinkedargposition = value000;
            }
            { Cons* value001 = NIL;

              { Proposition* prop = NULL;
                Iterator* iter003 = unfilteredDependentPropositions(backlinkedarg, NULL)->allocateIterator();
                Cons* collect000 = NULL;

                for  (; iter003->nextP(); ) {
                  prop = ((Proposition*)(iter003->value));
                  if (((prop->kind == KWD_SPECIALISTS_FUNCTION) ||
                      ((prop->kind == KWD_SPECIALISTS_PREDICATE) ||
                       (prop->kind == KWD_SPECIALISTS_ISA))) &&
                      ((prop->arguments->length() == holdsarity) &&
                       (((!prop->deletedP()) &&
                      ((oREVERSEPOLARITYpo ? falseP(prop) : (trueP(prop) ||
                      functionWithDefinedValueP(prop))))) &&
                        (prop->arguments->position(backlinkedarg, 0) == backlinkedargposition)))) {
                    if (!((boolean)(collect000))) {
                      {
                        collect000 = cons(prop, NIL);
                        if (value001 == NIL) {
                          value001 = collect000;
                        }
                        else {
                          addConsToEndOfConsList(value001, collect000);
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
              iterator = value001->allocateIterator();
            }
          }
          setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, iterator, NULL);
        }
        if (((boolean)(iterator))) {
          { PatternRecord* patternrecord = oQUERYITERATORo->currentPatternRecord;
            int ubstackoffset = patternrecord->topUnbindingStackOffset;

            { Proposition* prop = NULL;
              Iterator* iter004 = ((Iterator*)(iterator));

              for (; iter004->nextP(); ) {
                prop = ((Proposition*)(iter004->value));
                if (!(bindVariableToValueP(((PatternVariable*)((holdsarguments->theArray)[0])), getDescription(((Surrogate*)(prop->operatoR))), true))) {
                  continue;
                }
                { boolean alwaysP000 = true;

                  { Object* arg = NULL;
                    Vector* vector001 = holdsarguments;
                    int index001 = 0;
                    int length001 = vector001->length();
                    int i = NULL_INTEGER;
                    int iter005 = -1;

                    for  (; index001 < length001; 
                          index001 = index001 + 1,
                          iter005 = iter005 + 1) {
                      arg = (vector001->theArray)[index001];
                      i = iter005;
                      if (i >= 0) {
                        if (!bindArgumentToValueP(arg, (prop->arguments->theArray)[i], true)) {
                          alwaysP000 = false;
                          break;
                        }
                      }
                    }
                  }
                  if (alwaysP000) {
                    return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
                  }
                }
                unbindVariablesBeginningAt(patternrecord, ubstackoffset + 1);
              }
            }
          }
        }
      }
    }
    return (KWD_SPECIALISTS_FAILURE);
  }
}

Keyword* totalValueSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* valueproposition = frame->proposition;
    Vector* valuearguments = valueproposition->arguments;
    Object* description = argumentBoundTo((valuearguments->theArray)[0]);

    if (((boolean)(description))) {
      if (lastmove == KWD_SPECIALISTS_UP_TRUE) {
        if (!((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)))))) {
          setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, EMPTY_PROPOSITIONS_ITERATOR, NULL);
        }
        return ((((boolean)(frame->down)) ? KWD_SPECIALISTS_CONTINUING_SUCCESS : KWD_SPECIALISTS_FINAL_SUCCESS));
      }
      else if (lastmove == KWD_SPECIALISTS_UP_FAIL) {
        if (((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL))))) ||
            frame->reversePolarityP) {
          return (KWD_SPECIALISTS_FAILURE);
        }
        else if (isaP(description, SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION) &&
            (functionDescriptionP(((NamedDescription*)(description))) &&
             (allKeyArgumentsBoundP(valueproposition) &&
              (!((boolean)(argumentBoundTo(valuearguments->last()))))))) {
          { Cons* value000 = NIL;

            { int i = NULL_INTEGER;
              int iter000 = 1;
              int upperBound000 = valuearguments->length() - 2;
              Cons* collect000 = NULL;

              for  (; iter000 <= upperBound000; 
                    iter000 = iter000 + 1) {
                i = iter000;
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(argumentBoundTo((valuearguments->theArray)[i]), NIL);
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
                    collect000->rest = cons(argumentBoundTo((valuearguments->theArray)[i]), NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
            { Proposition* functionprop = findOrCreateFunctionProposition(objectSurrogate(description), value000);

              bindVariableToValueP(((PatternVariable*)((valueproposition->arguments->theArray)[(valueproposition->arguments->length() - 1)])), (functionprop->arguments->theArray)[(functionprop->arguments->length() - 1)], true);
              return (KWD_SPECIALISTS_FINAL_SUCCESS);
            }
          }
        }
        else {
          return (KWD_SPECIALISTS_FAILURE);
        }
      }
      else if (lastmove == KWD_SPECIALISTS_DOWN) {
        return (holdsSpecialist(frame, lastmove));
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    else {
      return (holdsSpecialist(frame, lastmove));
    }
  }
}

Object* thatComputation(Object* p) {
  if (subtypeOfP(safePrimaryType(p), SGT_SPECIALISTS_LOGIC_PROPOSITION)) {
    { Object* p000 = p;
      Proposition* p = ((Proposition*)(p000));

      if (allArgumentsBoundP(p)) {
        { KeyValueMap* mapping = newKeyValueMap();
          Proposition* that = NULL;

          { Object* arg = NULL;
            Vector* vector000 = p->arguments;
            int index000 = 0;
            int length000 = vector000->length();

            for  (; index000 < length000; 
                  index000 = index000 + 1) {
              arg = (vector000->theArray)[index000];
              { Object* value = safeArgumentBoundTo(arg);

                if (!eqlP(arg, value)) {
                  mapping->insertAt(arg, value);
                }
              }
            }
          }
          that = findMatchingNonDescriptiveProposition(p, mapping);
          if (((boolean)(that)) &&
              visibleFromP(that->homeModule(), oMODULEo)) {
            return (that);
          }
        }
      }
    }
  }
  else {
  }
  return (NULL);
}

Object* propositionRelationComputation(Object* p) {
  if (functionOutputSkolemP(p)) {
    p = ((Skolem*)(p))->definingProposition;
  }
  if (subtypeOfP(safePrimaryType(p), SGT_SPECIALISTS_LOGIC_PROPOSITION)) {
    { Object* p000 = p;
      Proposition* p = ((Proposition*)(p000));

      { GeneralizedSymbol* operatoR = p->operatoR;

        if (subtypeOfSurrogateP(safePrimaryType(operatoR))) {
          { GeneralizedSymbol* operator000 = operatoR;
            Surrogate* operatoR = ((Surrogate*)(operator000));

            return (operatoR->surrogateValue);
          }
        }
        else {
        }
      }
    }
  }
  else {
  }
  return (NULL);
}

Object* propositionArgumentComputation(Object* p, IntegerWrapper* i) {
  { Surrogate* testValue000 = safePrimaryType(p);

    if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_PROPOSITION)) {
      { Object* p000 = p;
        Proposition* p = ((Proposition*)(p000));

        { Vector* arguments = p->arguments;
          int arity = arguments->length();

          if (i->wrapperValue < 0) {
            i = wrapInteger(arity + i->wrapperValue);
          }
          if ((i->wrapperValue >= 0) &&
              (i->wrapperValue < arity)) {
            return ((arguments->theArray)[(i->wrapperValue)]);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_SKOLEM)) {
      { Object* p001 = p;
        Skolem* p = ((Skolem*)(p001));

        if (functionOutputSkolemP(p)) {
          { Proposition* prop = ((Skolem*)(p))->definingProposition;
            Vector* arguments = prop->arguments;
            int arity = arguments->length();

            if (i->wrapperValue < 0) {
              i = wrapInteger((arity + i->wrapperValue) - 1);
            }
            if ((i->wrapperValue >= 0) &&
                (i->wrapperValue < (arity - 1))) {
              return ((arguments->theArray)[(i->wrapperValue)]);
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

Skolem* propositionArgumentsComputation(Object* p) {
  { Surrogate* testValue000 = safePrimaryType(p);

    if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_PROPOSITION)) {
      { Object* p000 = p;
        Proposition* p = ((Proposition*)(p000));

        return (createLogicalList(p->arguments->listify()));
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_SKOLEM)) {
      { Object* p001 = p;
        Skolem* p = ((Skolem*)(p001));

        if (functionOutputSkolemP(p)) {
          return (createLogicalList(((Skolem*)(p))->definingProposition->arguments->butLast()->listify()));
        }
      }
    }
    else {
    }
  }
  return (NULL);
}

IntegerWrapper* propositionArityComputation(Object* p) {
  { Surrogate* testValue000 = safePrimaryType(p);

    if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_PROPOSITION)) {
      { Object* p000 = p;
        Proposition* p = ((Proposition*)(p000));

        return (wrapInteger(p->arguments->length()));
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_SKOLEM)) {
      { Object* p001 = p;
        Skolem* p = ((Skolem*)(p001));

        if (functionOutputSkolemP(p)) {
          return (wrapInteger(((Skolem*)(p))->definingProposition->arguments->length() - 1));
        }
      }
    }
    else {
    }
  }
  return (NULL);
}

Keyword* conceivedPropositionTermSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { boolean dummy1;

    lastmove = lastmove;
    { Vector* arguments = frame->proposition->arguments;
      Object* goalvalue = argumentBoundTo((arguments->theArray)[0]);
      Proposition* goalprop = NULL;
      boolean holdsP = false;
      Object* termarg = (arguments->theArray)[1];
      Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)));

      if ((!((boolean)(goalvalue))) ||
          (!isaP(goalvalue, SGT_SPECIALISTS_LOGIC_PROPOSITION))) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      goalprop = ((Proposition*)(goalvalue));
      holdsP = goalprop->operatoR == SGT_SPECIALISTS_PL_KERNEL_KB_HOLDS;
      if (!((boolean)(iterator))) {
        if (holdsP) {
          { Vector* goalarguments = goalprop->arguments;
            Object* relation = argumentBoundTo((goalarguments->theArray)[0]);
            Object* backlinkedarg = NULL;

            if (((boolean)(relation))) {
              relation = objectSurrogate(relation);
              { Cons* value000 = NIL;

                { int i = NULL_INTEGER;
                  int iter000 = 1;
                  int upperBound000 = goalarguments->length() - 1;
                  Cons* collect000 = NULL;

                  for  (; iter000 <= upperBound000; 
                        iter000 = iter000 + 1) {
                    i = iter000;
                    if (!((boolean)(collect000))) {
                      {
                        collect000 = cons(argumentBoundTo((goalarguments->theArray)[i]), NIL);
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
                        collect000->rest = cons(argumentBoundTo((goalarguments->theArray)[i]), NIL);
                        collect000 = collect000->rest;
                      }
                    }
                  }
                }
                backlinkedarg = selectInstanceWithBacklinks(value000, ((Surrogate*)(relation)));
              }
            }
            else {
              backlinkedarg = selectArgumentWithBacklinks(goalprop, dummy1);
            }
            if (((boolean)(backlinkedarg))) {
              iterator = unfilteredDependentPropositions(backlinkedarg, ((Surrogate*)(relation)))->allocateIterator();
            }
            else if (((boolean)(relation))) {
              iterator = allExtensionMembers(surrogateToDescription(((Surrogate*)(relation))));
            }
          }
        }
        else {
          iterator = trueToConceivedPropositionsIterator(allMatchingPropositions(goalprop));
        }
        if (iterator == EMPTY_PROPOSITIONS_ITERATOR) {
          iterator = NULL;
        }
        else {
          setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, iterator, NULL);
        }
      }
      if (((boolean)(iterator))) {
        while (iterator->nextP()) {
          if (visibleFromP(iterator->value->homeModule(), oCONTEXTo) &&
              (allArgumentsBoundP(((Proposition*)(iterator->value))) &&
               (relationAndArgumentsUnifyP(((Proposition*)(iterator->value)), goalprop, false) &&
                bindArgumentToValueP(termarg, iterator->value, true)))) {
            return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
          }
        }
      }
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
  }
}

Keyword* cutSpecialist(ControlFrame* frame, Keyword* lastmove) {
  lastmove = lastmove;
  if (!((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)))))) {
    setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, EMPTY_PROPOSITIONS_ITERATOR, NULL);
    return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
  }
  else {
    { ControlFrame* parentframe = frame->up;

      if ((!((boolean)(parentframe))) ||
          (!(parentframe->state == KWD_SPECIALISTS_AND))) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      { Vector* conjuncts = ((Vector*)(dynamicSlotValue(parentframe->dynamicSlots, SYM_SPECIALISTS_STELLA_ARGUMENTS, NULL)));

        if (((boolean)(conjuncts))) {
          { ControlFrame* conjunct = NULL;
            Vector* vector000 = conjuncts;
            int index000 = 0;
            int length000 = vector000->length();

            for  (; index000 < length000; 
                  index000 = index000 + 1) {
              conjunct = ((ControlFrame*)((vector000->theArray)[index000]));
              if (conjunct == frame) {
                break;
              }
              else {
                popControlFrame(conjunct);
              }
            }
          }
        }
      }
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
  }
}

Keyword* boundVariablesSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { boolean alwaysP000 = true;

    { Object* arg = NULL;
      Vector* vector000 = frame->proposition->arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        if (!((boolean)(argumentBoundTo(arg)))) {
          alwaysP000 = false;
          break;
        }
      }
    }
    { boolean allboundP = alwaysP000;

      lastmove = lastmove;
      return (selectTestResult(allboundP, true, frame));
    }
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

ForkProofAdjunct* newForkProofAdjunct() {
  { ForkProofAdjunct* self = NULL;

    self = new ForkProofAdjunct();
    self->downFrame = NULL;
    self->conditionJustification = NULL;
    return (self);
  }
}

Surrogate* ForkProofAdjunct::primaryType() {
  { ForkProofAdjunct* self = this;

    return (SGT_SPECIALISTS_LOGIC_FORK_PROOF_ADJUNCT);
  }
}

Object* accessForkProofAdjunctSlotValue(ForkProofAdjunct* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SPECIALISTS_LOGIC_CONDITION_JUSTIFICATION) {
    if (setvalueP) {
      self->conditionJustification = ((Justification*)(value));
    }
    else {
      value = self->conditionJustification;
    }
  }
  else if (slotname == SYM_SPECIALISTS_LOGIC_DOWN_FRAME) {
    if (setvalueP) {
      self->downFrame = ((ControlFrame*)(value));
    }
    else {
      value = self->downFrame;
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


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* forkSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { boolean recordjustificationsP = oRECORD_JUSTIFICATIONSpo;
    ForkProofAdjunct* adjunct = ((ForkProofAdjunct*)(((ProofAdjunct*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_LOGIC_PROOF_ADJUNCT, NULL)))));

    if (lastmove == KWD_SPECIALISTS_DOWN) {
      frame->choicePointUnbindingOffset = NULL_INTEGER;
      if (recordjustificationsP) {
        if (!((boolean)(adjunct))) {
          adjunct = newForkProofAdjunct();
          setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_LOGIC_PROOF_ADJUNCT, adjunct, NULL);
        }
        frame->down = adjunct->downFrame;
      }
      return (KWD_SPECIALISTS_MOVE_DOWN);
    }
    else if (lastmove == KWD_SPECIALISTS_UP_TRUE) {
      if (frame->argumentCursor > 0) {
        if (recordjustificationsP) {
          adjunct->downFrame = frame->down;
          propagateFrameTruthValue(frame->result, frame);
          { Justification* self001 = newJustification();

            self001->inferenceRule = ((adjunct->conditionJustification->inferenceRule == KWD_SPECIALISTS_FAIL_INTRODUCTION) ? KWD_SPECIALISTS_FORK_ELSE : KWD_SPECIALISTS_FORK_THEN);
            self001->antecedents = cons(adjunct->conditionJustification, cons(((Justification*)(dynamicSlotValue(frame->result->dynamicSlots, SYM_SPECIALISTS_LOGIC_JUSTIFICATION, NULL))), NIL));
            recordGoalJustification(frame, self001);
          }
        }
        if (((boolean)(frame->down))) {
          if (recordjustificationsP) {
            frame->down = NULL;
          }
          return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
        }
        else {
          return (KWD_SPECIALISTS_FINAL_SUCCESS);
        }
      }
      if (recordjustificationsP) {
        adjunct->conditionJustification = ((Justification*)(dynamicSlotValue(frame->result->dynamicSlots, SYM_SPECIALISTS_LOGIC_JUSTIFICATION, NULL)));
      }
      frame->down = NULL;
      frame->argumentCursor = 1;
      return (KWD_SPECIALISTS_MOVE_DOWN);
    }
    else if (lastmove == KWD_SPECIALISTS_UP_FAIL) {
      if (frame->argumentCursor > 0) {
        return (KWD_SPECIALISTS_FAILURE);
      }
      if (recordjustificationsP) {
        recordFailJustification(frame->result, KWD_SPECIALISTS_UP_FAIL);
        adjunct->conditionJustification = ((Justification*)(dynamicSlotValue(frame->result->dynamicSlots, SYM_SPECIALISTS_LOGIC_JUSTIFICATION, NULL)));
      }
      frame->down = NULL;
      frame->argumentCursor = 2;
      return (KWD_SPECIALISTS_MOVE_DOWN);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

Proposition* computeSubqueryOptions(ControlFrame* frame, PropertyList*& _Return1) {
  { Vector* arguments = frame->proposition->arguments;
    Object* arg = NULL;
    Proposition* proparg = NULL;
    int lastoptionargindex = arguments->length() - 1;
    int cursor = 1;
    Object* key = NULL;
    Object* value = NULL;
    PropertyList* subqueryoptions = newPropertyList();
    PropertyList* parentoptions = oQUERYITERATORo->options;

    if (lastoptionargindex < 0) {
      _Return1 = NULL;
      return (NULL);
    }
    arg = argumentBoundTo((arguments->theArray)[0]);
    if (((boolean)(arg)) &&
        isaP(arg, SGT_SPECIALISTS_LOGIC_PROPOSITION)) {
      proparg = ((Proposition*)(arg));
    }
    else if (lastoptionargindex >= 1) {
      cursor = 0;
      key = KWD_SPECIALISTS_HOW_MANY;
      value = arg;
      arg = argumentBoundTo((arguments->theArray)[1]);
      if (((boolean)(arg)) &&
          isaP(arg, SGT_SPECIALISTS_LOGIC_PROPOSITION)) {
        proparg = ((Proposition*)(arg));
      }
      else {
        _Return1 = NULL;
        return (NULL);
      }
    }
    else {
      _Return1 = NULL;
      return (NULL);
    }
    if (!((lastoptionargindex - cursor) % 2)) {
      lastoptionargindex = lastoptionargindex - 1;
    }
    while (cursor < lastoptionargindex) {
      if (cursor == 0) {
      }
      else {
        key = generateTerm(argumentBoundTo((arguments->theArray)[cursor]));
        value = generateTerm(argumentBoundTo((arguments->theArray)[(cursor + 1)]));
      }
      cursor = cursor + 2;
      if ((!((boolean)(key))) ||
          (!((boolean)(value)))) {
        _Return1 = NULL;
        return (NULL);
      }
      if (key == KWD_SPECIALISTS_INHERIT) {
        if ((value == KWD_SPECIALISTS_ALL) ||
            (value == KWD_SPECIALISTS_CURRENT)) {
          { Object* pkey = NULL;
            Object* pvalue = NULL;
            Cons* iter000 = parentoptions->thePlist;

            for  (; !(iter000 == NIL); 
                  iter000 = iter000->rest->rest) {
              pkey = iter000->value;
              pvalue = iter000->rest->value;
              subqueryoptions->insertAt(pkey, pvalue);
            }
          }
        }
      }
      else if ((value == KWD_SPECIALISTS_INHERIT) ||
          (value == KWD_SPECIALISTS_CURRENT)) {
        if (((boolean)(lookupQueryOption(parentoptions, ((Keyword*)(key)))))) {
          subqueryoptions->insertAt(key, lookupQueryOption(parentoptions, ((Keyword*)(key))));
        }
      }
      else {
        subqueryoptions->insertAt(key, value);
      }
    }
    _Return1 = subqueryoptions;
    return (proparg);
  }
}

List* ControlFrame::querySpecialistIoVariables_reader() {
  { ControlFrame* self = this;

    { List* answer = ((List*)(dynamicSlotValue(self->dynamicSlots, SYM_SPECIALISTS_LOGIC_QUERY_SPECIALIST_IO_VARIABLES, NULL)));

      if (!((boolean)(answer))) {
        return (NIL_LIST);
      }
      else {
        return (answer);
      }
    }
  }
}

QueryIterator* createQuerySpecialistIterator(ControlFrame* frame, boolean& _Return1, boolean& _Return2) {
  { Proposition* proposition = NULL;
    PropertyList* subqueryoptions = NULL;

    proposition = computeSubqueryOptions(frame, subqueryoptions);
    { QueryIterator* subqueryiterator = allocateQueryIterator();
      Description* subquerydescription = NULL;
      Object* matchmode = NULL;
      boolean truefalsequeryP = false;
      boolean partialqueryP = false;
      List* iovariables = newList();
      Vector* iovariablebindings = NULL;

      if (!((boolean)(proposition))) {
        _Return1 = false;
        _Return2 = false;
        return (NULL);
      }
      else {
        processQueryOptions(subqueryiterator, subqueryoptions);
      }
      matchmode = lookupQueryOption(subqueryiterator, KWD_SPECIALISTS_MATCH_MODE);
      if (((boolean)(matchmode)) &&
          (!stringEqualP(coerceToString(matchmode), "STRICT"))) {
        partialqueryP = true;
      }
      collectFreeVariables(proposition, iovariables, list(0), list(0));
      setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_LOGIC_QUERY_SPECIALIST_IO_VARIABLES, iovariables, NULL);
      { 
        BIND_STELLA_SPECIAL(oEVALUATIONMODEo, Keyword*, KWD_SPECIALISTS_DESCRIPTION);
        { Description* self001 = newDescription();

          self001->ioVariables = ((Vector*)(copyListToArgumentsVector(iovariables)));
          self001->proposition = proposition;
          subquerydescription = self001;
        }
        computeInternalVariables(subquerydescription);
        { Description* temp000 = findDuplicateDescription(subquerydescription);

          subquerydescription = (((boolean)(temp000)) ? temp000 : subquerydescription);
        }
      }
      iovariablebindings = stella::newVector(iovariables->length());
      truefalsequeryP = true;
      { Object* var = NULL;
        Cons* iter000 = iovariables->theConsList;
        int i = NULL_INTEGER;
        int iter001 = 0;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          var = iter000->value;
          i = iter001;
          (iovariablebindings->theArray)[i] = (argumentBoundTo(var));
          if (!((boolean)((iovariablebindings->theArray)[i]))) {
            truefalsequeryP = false;
          }
        }
      }
      initializeQueryIterator(subqueryiterator, subquerydescription, iovariablebindings);
      _Return1 = truefalsequeryP;
      _Return2 = partialqueryP;
      return (subqueryiterator);
    }
  }
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* querySpecialist(ControlFrame* frame, Keyword* lastmove) {
  { QueryIterator* subqueryiterator = ((QueryIterator*)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)))));
    boolean truefalsequeryP = false;
    boolean partialqueryP = false;
    boolean sortedqueryP = false;
    boolean successP = false;
    ControlFrame* result = NULL;

    lastmove = lastmove;
    if (!((boolean)(subqueryiterator))) {
      subqueryiterator = createQuerySpecialistIterator(frame, truefalsequeryP, partialqueryP);
      if (!((boolean)(subqueryiterator))) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      else {
        setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, subqueryiterator, NULL);
      }
      if (partialqueryP) {
        if (truefalsequeryP) {
          callAskPartial(subqueryiterator);
        }
        else {
          callRetrievePartial(subqueryiterator);
        }
      }
      else if ((!truefalsequeryP) &&
          ((boolean)(lookupQueryOption(subqueryiterator, KWD_SPECIALISTS_SORT_BY)))) {
        sortedqueryP = true;
        callRetrieve(subqueryiterator);
      }
    }
    else {
      partialqueryP = ((boolean)(subqueryiterator->partialMatchStrategy));
      sortedqueryP = ((boolean)(lookupQueryOption(subqueryiterator, KWD_SPECIALISTS_SORT_BY)));
    }
    if (((boolean)(oTRACED_KEYWORDSo)) &&
        oTRACED_KEYWORDSo->membP(KWD_SPECIALISTS_GOAL_TREE)) {
      std::cout << std::endl;
    }
    for (;;) {
      if (partialqueryP ||
          sortedqueryP) {
        successP = subqueryiterator->querySucceededP();
        if (successP) {
          { QuerySolution* solution = subqueryiterator->solutions->pop();

            result = subqueryiterator->baseControlFrame;
            if (!(truefalsequeryP)) {
              subqueryiterator->value = solution;
            }
            result->truthValue = solution->truthValue;
            if (oRECORD_JUSTIFICATIONSpo) {
              setDynamicSlotValue(result->dynamicSlots, SYM_SPECIALISTS_LOGIC_JUSTIFICATION, solution->justification, NULL);
            }
            if (partialqueryP) {
              result->partialMatchFrame->matchScore = solution->matchScore;
            }
          }
        }
      }
      else {
        { 
          BIND_STELLA_SPECIAL(oQUERYITERATORo, QueryIterator*, subqueryiterator);
          BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, frame->reversePolarityP);
          BIND_STELLA_SPECIAL(oINFERENCELEVELo, NormalInferenceLevel*, currentInferenceLevel());
          BIND_STELLA_SPECIAL(oGENERATE_ALL_PROOFSpo, boolean, false);
          { int howmany = lookupHowManySolutions(subqueryiterator);

            if ((howmany == NULL_INTEGER) ||
                (howmany >= 1)) {
              successP = subqueryiterator->nextP();
            }
            if (howmany == NULL_INTEGER) {
            }
            else if (howmany <= 1) {
              subqueryiterator->exhaustedP = true;
            }
            else {
              subqueryiterator->options->insertAt(KWD_SPECIALISTS_HOW_MANY, wrapInteger(howmany - 1));
            }
            if (successP) {
              result = subqueryiterator->baseControlFrame;
            }
          }
        }
      }
      if (successP) {
        { Object* var = NULL;
          Cons* iter000 = frame->querySpecialistIoVariables_reader()->theConsList;
          Object* value = NULL;
          Vector* vector000 = ((QuerySolution*)(subqueryiterator->value))->bindings;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; (!(iter000 == NIL)) &&
                    (index000 < length000); 
                iter000 = iter000->rest,
                index000 = index000 + 1) {
            var = iter000->value;
            value = (vector000->theArray)[index000];
            if (!(bindVariableToValueP(((PatternVariable*)(var)), value, true))) {
              successP = false;
              break;
            }
          }
        }
        if ((!successP) &&
            (!truefalsequeryP)) {
          continue;
        }
      }
      break;
    }
    if (((boolean)(oTRACED_KEYWORDSo)) &&
        oTRACED_KEYWORDSo->membP(KWD_SPECIALISTS_GOAL_TREE)) {
      std::cout << std::endl;
    }
    if (successP) {
      propagateFrameTruthValue(result, frame);
      if ((((boolean)(oQUERYITERATORo)) &&
          ((boolean)(oQUERYITERATORo->partialMatchStrategy))) &&
          partialqueryP) {
        result->partialMatchFrame->propagateFramePartialTruth(frame);
      }
      if (oRECORD_JUSTIFICATIONSpo) {
        recordGoalJustification(frame, ((Justification*)(dynamicSlotValue(result->dynamicSlots, SYM_SPECIALISTS_LOGIC_JUSTIFICATION, NULL))));
      }
      if (truefalsequeryP) {
        return (KWD_SPECIALISTS_FINAL_SUCCESS);
      }
      else {
        return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
      }
    }
    else {
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

SavedInferenceLevelProofAdjunct* newSavedInferenceLevelProofAdjunct() {
  { SavedInferenceLevelProofAdjunct* self = NULL;

    self = new SavedInferenceLevelProofAdjunct();
    self->downFrame = NULL;
    self->inferenceLevel = NULL;
    self->savedInferenceLevel = NULL;
    return (self);
  }
}

Surrogate* SavedInferenceLevelProofAdjunct::primaryType() {
  { SavedInferenceLevelProofAdjunct* self = this;

    return (SGT_SPECIALISTS_LOGIC_SAVED_INFERENCE_LEVEL_PROOF_ADJUNCT);
  }
}

Object* accessSavedInferenceLevelProofAdjunctSlotValue(SavedInferenceLevelProofAdjunct* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SPECIALISTS_LOGIC_SAVED_INFERENCE_LEVEL) {
    if (setvalueP) {
      self->savedInferenceLevel = ((InferenceLevel*)(value));
    }
    else {
      value = self->savedInferenceLevel;
    }
  }
  else if (slotname == SYM_SPECIALISTS_LOGIC_INFERENCE_LEVEL) {
    if (setvalueP) {
      self->inferenceLevel = ((InferenceLevel*)(value));
    }
    else {
      value = self->inferenceLevel;
    }
  }
  else if (slotname == SYM_SPECIALISTS_LOGIC_DOWN_FRAME) {
    if (setvalueP) {
      self->downFrame = ((ControlFrame*)(value));
    }
    else {
      value = self->downFrame;
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

InferenceLevel* leveledQueryRelationToInferenceLevel(Surrogate* relation) {
  if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_ASSERTION_QUERY) {
    return (ASSERTION_INFERENCE);
  }
  else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_SHALLOW_QUERY) {
    return (SHALLOW_INFERENCE);
  }
  else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_SUBSUMPTION_QUERY) {
    return (SUBSUMPTION_INFERENCE);
  }
  else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_BACKTRACKING_QUERY) {
    return (BACKTRACKING_INFERENCE);
  }
  else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_NORMAL_QUERY) {
    return (NORMAL_INFERENCE);
  }
  else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_REFUTATION_QUERY) {
    return (REFUTATION_INFERENCE);
  }
  else {
    return (getInferenceLevel(((StringWrapper*)(splitString(relation->symbolName, '-')->value))->keywordify()));
  }
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* leveledQuerySpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    SavedInferenceLevelProofAdjunct* adjunct = ((SavedInferenceLevelProofAdjunct*)(((ProofAdjunct*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_LOGIC_PROOF_ADJUNCT, NULL)))));

    if (lastmove == KWD_SPECIALISTS_DOWN) {
      if (!((boolean)(adjunct))) {
        { Object* argpropvalue = argumentBoundTo((proposition->arguments->theArray)[0]);

          if ((!((boolean)(argpropvalue))) ||
              (!isaP(argpropvalue, SGT_SPECIALISTS_LOGIC_PROPOSITION))) {
            return (KWD_SPECIALISTS_TERMINAL_FAILURE);
          }
          frame->choicePointUnbindingOffset = NULL_INTEGER;
          { SavedInferenceLevelProofAdjunct* self000 = newSavedInferenceLevelProofAdjunct();

            self000->savedInferenceLevel = currentInferenceLevel();
            self000->inferenceLevel = leveledQueryRelationToInferenceLevel(((Surrogate*)(proposition->operatoR)));
            self000->downFrame = createDownFrame(frame, ((Proposition*)(argpropvalue)));
            adjunct = self000;
          }
          setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_LOGIC_PROOF_ADJUNCT, adjunct, NULL);
        }
      }
      frame->down = adjunct->downFrame;
      callSetInferenceLevel(adjunct->inferenceLevel->keyword, NULL);
      oINFERENCELEVELo = ((NormalInferenceLevel*)(adjunct->inferenceLevel));
      return (KWD_SPECIALISTS_MOVE_DOWN);
    }
    else if (lastmove == KWD_SPECIALISTS_UP_TRUE) {
      propagateFrameTruthValue(frame->result, frame);
      if (((boolean)(oQUERYITERATORo)) &&
          ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
        frame->result->partialMatchFrame->propagateFramePartialTruth(frame);
      }
      if (oRECORD_JUSTIFICATIONSpo) {
        { Justification* self001 = newJustification();

          self001->inferenceRule = KWD_SPECIALISTS_LEVELED_QUERY;
          self001->antecedents = cons(((Justification*)(dynamicSlotValue(frame->result->dynamicSlots, SYM_SPECIALISTS_LOGIC_JUSTIFICATION, NULL))), NIL);
          recordGoalJustification(frame, self001);
        }
      }
      callSetInferenceLevel(adjunct->savedInferenceLevel->keyword, NULL);
      oINFERENCELEVELo = ((NormalInferenceLevel*)(adjunct->savedInferenceLevel));
      if (((boolean)(frame->down))) {
        adjunct->downFrame = frame->down;
        frame->down = NULL;
        return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
      }
      else {
        return (KWD_SPECIALISTS_FINAL_SUCCESS);
      }
    }
    else if (lastmove == KWD_SPECIALISTS_UP_FAIL) {
      propagateFrameTruthValue(frame->result, frame);
      if (((boolean)(oQUERYITERATORo)) &&
          ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
        frame->result->partialMatchFrame->propagateFramePartialTruth(frame);
      }
      if (oRECORD_JUSTIFICATIONSpo) {
        recordPrimitiveJustification(frame, KWD_SPECIALISTS_UP_FAIL);
      }
      callSetInferenceLevel(adjunct->savedInferenceLevel->keyword, NULL);
      oINFERENCELEVELo = ((NormalInferenceLevel*)(adjunct->savedInferenceLevel));
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

int oPROTOTYPE_ID_COUNTERo = 0;


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* conceptPrototypeSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* clasS = argumentBoundTo((proposition->arguments->theArray)[0]);
    Object* prototypeargument = (proposition->arguments->theArray)[1];
    LogicObject* prototype = NULL;

    lastmove = lastmove;
    if ((!((boolean)(clasS))) ||
        (!isaP(clasS, SGT_SPECIALISTS_LOGIC_DESCRIPTION))) {
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
    prototype = ((LogicObject*)(accessBinaryValue(clasS, SGT_SPECIALISTS_PL_KERNEL_KB_CONCEPT_PROTOTYPE)));
    if (!((boolean)(prototype))) {
      { Proposition* equivalence = NULL;

        { 
          BIND_STELLA_SPECIAL(oCONTEXTo, Context*, ((Description*)(clasS))->homeContext);
          BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
          prototype = createHypothesizedInstance((isaP(clasS, SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION) ? stringConcatenate("proto-", objectNameString(clasS), 0) : "prototype"));
          { 
            BIND_STELLA_SPECIAL(oINVISIBLEASSERTIONpo, boolean, true);
            assertMemberOfProposition(prototype, clasS);
            equivalence = assertBinaryValue(SGT_SPECIALISTS_PL_KERNEL_KB_CONCEPT_PROTOTYPE, clasS, prototype);
          }
        }
        equivalence->reactToInferenceUpdate();
      }
    }
    return (selectProofResult(bindArgumentToValueP(prototypeargument, prototype, true), false, true));
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

NamedDescription* conceptPrototypeOf(LogicObject* self) {
  if (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_SPECIALISTS_LOGIC_HYPOTHESIZED_INSTANCEp, FALSE_WRAPPER)))->wrapperValue) {
    { Proposition* prop = NULL;
      Iterator* iter000 = allTrueDependentIsaPropositions(self);

      for (; iter000->nextP(); ) {
        prop = ((Proposition*)(iter000->value));
        if (((boolean)(accessBinaryValue(surrogateToDescription(((Surrogate*)(prop->operatoR))), SGT_SPECIALISTS_PL_KERNEL_KB_CONCEPT_PROTOTYPE)))) {
          return (surrogateToDescription(((Surrogate*)(prop->operatoR))));
        }
      }
    }
  }
  return (NULL);
}

boolean conceptPrototypeP(LogicObject* self) {
  return (((boolean)(conceptPrototypeOf(self))));
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* closedSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* argvalue = argumentBoundTo((proposition->arguments->theArray)[0]);
    boolean closedP = closedTermP(argvalue);

    lastmove = lastmove;
    if (!((boolean)(argvalue))) {
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
    if (oREVERSEPOLARITYpo) {
      closedP = !closedP;
    }
    return (selectProofResult(closedP, false, true));
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

boolean closedByAssertionP(Object* self) {
  return (testPropertyP(self, SGT_SPECIALISTS_PL_KERNEL_KB_CLOSED));
}

boolean closedTermP(Object* self) {
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_SPECIALISTS_LOGIC_F_CLOSED_TERMp_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_SPECIALISTS_LOGIC_F_CLOSED_TERMp_MEMO_TABLE_000, "(:MAX-VALUES 500 :TIMESTAMPS (:KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_SPECIALISTS_LOGIC_F_CLOSED_TERMp_MEMO_TABLE_000->surrogateValue));
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
      memoizedValue000 = (helpClosedTermP(self, NIL) ? TRUE_WRAPPER : FALSE_WRAPPER);
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { BooleanWrapper* value000 = ((BooleanWrapper*)(memoizedValue000));

      return (coerceWrappedBooleanToBoolean(value000));
    }
  }
}

boolean helpClosedTermP(Object* self, Cons* activeterms) {
  if (!((boolean)(self))) {
    return (false);
  }
  if (activeterms->membP(self)) {
    return (false);
  }
  else {
    activeterms = cons(self, activeterms);
  }
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION)) {
      { Object* self000 = self;
        NamedDescription* self = ((NamedDescription*)(self000));

        return (testPropertyP(self, SGT_SPECIALISTS_PL_KERNEL_KB_CLOSED) ||
            (((boolean)(((Description*)(accessInContext(dynamicSlotValue(self->dynamicSlots, SYM_SPECIALISTS_LOGIC_EQUIVALENT_VALUE, NULL), self->homeContext, false))))) &&
             helpClosedTermP(((Description*)(accessInContext(dynamicSlotValue(self->dynamicSlots, SYM_SPECIALISTS_LOGIC_EQUIVALENT_VALUE, NULL), self->homeContext, false))), activeterms)));
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_DESCRIPTION)) {
      { Object* self001 = self;
        Description* self = ((Description*)(self001));

        return (testPropertyP(self, SGT_SPECIALISTS_PL_KERNEL_KB_CLOSED) ||
            helpClosedPropositionP(self->proposition, activeterms));
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* self002 = self;
        Surrogate* self = ((Surrogate*)(self002));

        return (helpClosedTermP(valueOf(self), activeterms));
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_PATTERN_VARIABLE)) {
      { Object* self003 = self;
        PatternVariable* self = ((PatternVariable*)(self003));

        return (false);
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_SKOLEM)) {
      { Object* self004 = self;
        Skolem* self = ((Skolem*)(self004));

        { Proposition* definingprop = self->definingProposition;

          return ((((boolean)(definingprop)) &&
              collectionofPropositionP(definingprop)) ||
              testPropertyP(self, SGT_SPECIALISTS_PL_KERNEL_KB_CLOSED));
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_LOGIC_OBJECT)) {
      { Object* self005 = self;
        LogicObject* self = ((LogicObject*)(self005));

        return (testPropertyP(self, SGT_SPECIALISTS_PL_KERNEL_KB_CLOSED));
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALISTS_STELLA_THING)) {
      { Object* self006 = self;
        Thing* self = ((Thing*)(self006));

        return (testPropertyP(self, SGT_SPECIALISTS_PL_KERNEL_KB_CLOSED));
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALISTS_STELLA_COLLECTION)) {
      { Object* self007 = self;
        Collection* self = ((Collection*)(self007));

        return (true);
      }
    }
    else {
      return (false);
    }
  }
}

boolean closedPropositionP(Proposition* self) {
  { MemoizationTable* memoTable000 = NULL;
    Cons* memoizedEntry000 = NULL;
    Object* memoizedValue000 = NULL;

    if (oMEMOIZATION_ENABLEDpo) {
      memoTable000 = ((MemoizationTable*)(SGT_SPECIALISTS_LOGIC_F_CLOSED_PROPOSITIONp_MEMO_TABLE_000->surrogateValue));
      if (!((boolean)(memoTable000))) {
        initializeMemoizationTable(SGT_SPECIALISTS_LOGIC_F_CLOSED_PROPOSITIONp_MEMO_TABLE_000, "(:MAX-VALUES 500 :TIMESTAMPS (:META-KB-UPDATE))");
        memoTable000 = ((MemoizationTable*)(SGT_SPECIALISTS_LOGIC_F_CLOSED_PROPOSITIONp_MEMO_TABLE_000->surrogateValue));
      }
      memoizedEntry000 = lookupMruMemoizedValue(((MruMemoizationTable*)(memoTable000)), self, oCONTEXTo, MEMOIZED_NULL_VALUE, NULL, -1);
      memoizedValue000 = memoizedEntry000->value;
    }
    if (((boolean)(memoizedValue000))) {
      if (memoizedValue000 == MEMOIZED_NULL_VALUE) {
        memoizedValue000 = NULL;
      }
    }
    else {
      memoizedValue000 = (helpClosedPropositionP(self, NIL) ? TRUE_WRAPPER : FALSE_WRAPPER);
      if (oMEMOIZATION_ENABLEDpo) {
        memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
      }
    }
    { BooleanWrapper* value000 = ((BooleanWrapper*)(memoizedValue000));

      return (coerceWrappedBooleanToBoolean(value000));
    }
  }
}

boolean helpClosedPropositionP(Proposition* self, Cons* activeterms) {
  if (activeterms->membP(self)) {
    return (false);
  }
  else {
    activeterms = cons(self, activeterms);
  }
  { Keyword* testValue000 = self->kind;

    if ((testValue000 == KWD_SPECIALISTS_AND) ||
        ((testValue000 == KWD_SPECIALISTS_OR) ||
         ((testValue000 == KWD_SPECIALISTS_NOT) ||
          ((testValue000 == KWD_SPECIALISTS_FORALL) ||
           (testValue000 == KWD_SPECIALISTS_EXISTS))))) {
      { boolean alwaysP000 = true;

        { Object* arg = NULL;
          Vector* vector000 = self->arguments;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            arg = (vector000->theArray)[index000];
            if (!helpClosedPropositionP(((Proposition*)(arg)), activeterms)) {
              alwaysP000 = false;
              break;
            }
          }
        }
        { boolean value000 = alwaysP000;

          return (value000);
        }
      }
    }
    else if ((testValue000 == KWD_SPECIALISTS_PREDICATE) ||
        ((testValue000 == KWD_SPECIALISTS_FUNCTION) ||
         (testValue000 == KWD_SPECIALISTS_ISA))) {
      if (((Surrogate*)(self->operatoR)) == SGT_SPECIALISTS_PL_KERNEL_KB_MEMBER_OF) {
        { Object* collectionarg = (self->arguments->theArray)[1];
          Object* collectionvalue = safeArgumentBoundTo(collectionarg);

          if (((boolean)(collectionvalue))) {
            return (helpClosedTermP(collectionvalue, activeterms));
          }
          else {
            { boolean foundP000 = false;

              { Proposition* prop = NULL;
                Iterator* iter000 = unfilteredDependentPropositions(collectionarg, NULL)->allocateIterator();

                for (; iter000->nextP(); ) {
                  prop = ((Proposition*)(iter000->value));
                  if (eqlP(collectionarg, prop->arguments->last()) &&
                      collectionofPropositionP(prop)) {
                    foundP000 = true;
                    break;
                  }
                }
              }
              { boolean value001 = foundP000;

                return (value001);
              }
            }
          }
        }
      }
      else {
        return (helpClosedTermP(getDescription(((Surrogate*)(self->operatoR))), activeterms));
      }
    }
    else if (testValue000 == KWD_SPECIALISTS_FAIL) {
      return (true);
    }
    else {
      return (false);
    }
  }
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* singleValuedSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* argvalue = argumentBoundTo((proposition->arguments->theArray)[0]);
    boolean singlevaluedP = singleValuedTermP(argvalue);

    lastmove = lastmove;
    if (!((boolean)(argvalue))) {
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
    if (oREVERSEPOLARITYpo) {
      singlevaluedP = !singlevaluedP;
    }
    if (singlevaluedP) {
      return (KWD_SPECIALISTS_FINAL_SUCCESS);
    }
    else {
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

boolean singleValuedTermP(Object* self) {
  { 
    BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
    if (oCYC_KLUDGES_ENABLEDpo) {
      return (functionP(self) ||
          testPropertyP(self, SGT_SPECIALISTS_PL_KERNEL_KB_SINGLE_VALUED));
    }
    { MemoizationTable* memoTable000 = NULL;
      Cons* memoizedEntry000 = NULL;
      Object* memoizedValue000 = NULL;

      if (oMEMOIZATION_ENABLEDpo) {
        memoTable000 = ((MemoizationTable*)(SGT_SPECIALISTS_LOGIC_F_SINGLE_VALUED_TERMp_MEMO_TABLE_000->surrogateValue));
        if (!((boolean)(memoTable000))) {
          initializeMemoizationTable(SGT_SPECIALISTS_LOGIC_F_SINGLE_VALUED_TERMp_MEMO_TABLE_000, "(:MAX-VALUES 500 :TIMESTAMPS (:META-KB-UPDATE))");
          memoTable000 = ((MemoizationTable*)(SGT_SPECIALISTS_LOGIC_F_SINGLE_VALUED_TERMp_MEMO_TABLE_000->surrogateValue));
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
        { boolean testValue001 = false;

          if (nonRecursiveSingleValuedTermP(self)) {
            testValue001 = true;
          }
          else {
            {
              testValue001 = !classP(self);
              if (testValue001) {
                { boolean foundP001 = false;

                  { LogicObject* d = NULL;
                    Iterator* iter001 = allSupercollections(((LogicObject*)(self)));

                    for (; iter001->nextP(); ) {
                      d = ((LogicObject*)(iter001->value));
                      if (nonRecursiveSingleValuedTermP(d)) {
                        foundP001 = true;
                        break;
                      }
                    }
                  }
                  testValue001 = foundP001;
                }
              }
            }
          }
          memoizedValue000 = (testValue001 ? TRUE_WRAPPER : FALSE_WRAPPER);
        }
        if (oMEMOIZATION_ENABLEDpo) {
          memoizedEntry000->value = ((!((boolean)(memoizedValue000))) ? MEMOIZED_NULL_VALUE : memoizedValue000);
        }
      }
      { BooleanWrapper* value000 = ((BooleanWrapper*)(memoizedValue000));

        return (coerceWrappedBooleanToBoolean(value000));
      }
    }
  }
}

boolean nonRecursiveSingleValuedTermP(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION)) {
      { Object* self000 = self;
        NamedDescription* self = ((NamedDescription*)(self000));

        return (functionDescriptionP(self) ||
            testPropertyP(self, SGT_SPECIALISTS_PL_KERNEL_KB_SINGLE_VALUED));
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_DESCRIPTION)) {
      { Object* self001 = self;
        Description* self = ((Description*)(self001));

        { Proposition* proposition = self->proposition;
          Cons* iovariables = NIL;

          { PatternVariable* arg = NULL;
            Vector* vector000 = self->ioVariables;
            int index000 = 0;
            int length000 = vector000->length();

            for  (; index000 < length000; 
                  index000 = index000 + 1) {
              arg = ((PatternVariable*)((vector000->theArray)[index000]));
              iovariables = cons(arg, iovariables);
            }
          }
          return (helpSingleValuedGoalP(proposition, iovariables, copyConsList(iovariables->rest), false));
        }
      }
    }
    else {
      return (false);
    }
  }
}

boolean singleValuedGoalP(Proposition* proposition, Cons* iovariables, Cons* boundvariables) {
  return (helpSingleValuedGoalP(proposition, iovariables, boundvariables, true));
}

boolean helpSingleValuedGoalP(Proposition* proposition, Cons* iovariables, Cons* boundvariables, boolean recursiveP) {
  { List* boundvariableslist = boundvariables->listify();
    int oldcount = boundvariableslist->length();
    int newcount = NULL_INTEGER;

    for (;;) {
      helpCollectSinglyBoundVariables(proposition, boundvariableslist, recursiveP);
      newcount = boundvariableslist->length();
      if (oldcount == newcount) {
        break;
      }
      oldcount = newcount;
    }
    { boolean alwaysP000 = true;

      { PatternVariable* vbl = NULL;
        Cons* iter000 = iovariables;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          vbl = ((PatternVariable*)(iter000->value));
          if (!boundvariableslist->memberP(vbl)) {
            alwaysP000 = false;
            break;
          }
        }
      }
      { boolean value000 = alwaysP000;

        return (value000);
      }
    }
  }
}

void helpCollectSinglyBoundVariables(Proposition* proposition, List* boundvariables, boolean recursiveP) {
  { Keyword* testValue000 = proposition->kind;

    if (testValue000 == KWD_SPECIALISTS_AND) {
      { Object* arg = NULL;
        Vector* vector000 = proposition->arguments;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          arg = (vector000->theArray)[index000];
          helpCollectSinglyBoundVariables(((Proposition*)(arg)), boundvariables, recursiveP);
        }
      }
    }
    else if ((testValue000 == KWD_SPECIALISTS_FUNCTION) ||
        (testValue000 == KWD_SPECIALISTS_PREDICATE)) {
      if (proposition->arguments->length() > 0) {
        { Object* lastarg = (proposition->arguments->theArray)[(proposition->arguments->length() - 1)];

          { boolean testValue001 = false;

            testValue001 = variableP(lastarg);
            if (testValue001) {
              testValue001 = !boundvariables->memberP(lastarg);
              if (testValue001) {
                testValue001 = (proposition->kind == KWD_SPECIALISTS_FUNCTION) ||
                    ((recursiveP &&
                    singleValuedTermP(getDescription(((Surrogate*)(proposition->operatoR))))) ||
                     ((!recursiveP) &&
                      nonRecursiveSingleValuedTermP(getDescription(((Surrogate*)(proposition->operatoR))))));
                if (testValue001) {
                  { boolean alwaysP000 = true;

                    { Object* arg = NULL;
                      Iterator* iter000 = proposition->arguments->butLast();

                      for (; iter000->nextP(); ) {
                        arg = iter000->value;
                        if (!((!variableP(arg)) ||
                            boundvariables->memberP(arg))) {
                          alwaysP000 = false;
                          break;
                        }
                      }
                    }
                    testValue001 = alwaysP000;
                  }
                }
              }
            }
            if (testValue001) {
              boundvariables->push(((PatternVariable*)(lastarg)));
            }
          }
        }
      }
    }
    else if (testValue000 == KWD_SPECIALISTS_EQUIVALENT) {
      { Cons* unboundvariables = NIL;

        { Object* arg = NULL;
          Vector* vector001 = proposition->arguments;
          int index001 = 0;
          int length001 = vector001->length();

          for  (; index001 < length001; 
                index001 = index001 + 1) {
            arg = (vector001->theArray)[index001];
            if (variableP(arg) &&
                (!boundvariables->memberP(arg))) {
              unboundvariables = cons(arg, unboundvariables);
            }
          }
        }
        if (unboundvariables->length() == 1) {
          boundvariables->push(((PatternVariable*)(unboundvariables->value)));
        }
      }
    }
    else {
    }
  }
}

void createCollectDescriptionExtensionFrame(ControlFrame* frame, Description* description) {
  { ControlFrame* downframe = createDownFrame(frame, NULL);

    overlayWithPatternFrameP(downframe, description, NULL);
    downframe->patternRecord->collectionList = newList();
  }
}

boolean collectDescriptionExtensionFrameP(ControlFrame* frame) {
  return (((boolean)(frame->patternRecord)) &&
      ((boolean)(frame->patternRecord->collectionList)));
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* collectMembersSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* collectionarg = (proposition->arguments->theArray)[0];
    Object* collectionvalue = argumentBoundTo(collectionarg);
    Object* listarg = (proposition->arguments->theArray)[1];
    boolean listP = false;
    boolean uniqueP = true;
    boolean countP = false;
    stella::List* members = NULL;
    Object* result = NULL;

    lastmove = lastmove;
    if (!((boolean)(collectionvalue))) {
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
    { GeneralizedSymbol* testValue000 = proposition->operatoR;

      if (testValue000 == SGT_SPECIALISTS_PL_KERNEL_KB_COLLECT_INTO_LIST) {
        listP = true;
        uniqueP = false;
      }
      else if (testValue000 == SGT_SPECIALISTS_PL_KERNEL_KB_COLLECT_INTO_ORDERED_SET) {
        listP = true;
      }
      else if (testValue000 == SGT_SPECIALISTS_PL_KERNEL_KB_COUNT_MEMBERS) {
        countP = true;
      }
      else {
      }
    }
    if ((!((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)))))) &&
        (((enumeratedSetP(collectionvalue) &&
        (!listP)) ||
        (enumeratedListP(collectionvalue) &&
         (!uniqueP))) &&
         (((LogicObject*)(collectionvalue))->variableValueInverse_reader() == NIL))) {
      result = collectionvalue;
    }
    else if (!((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)))))) {
      { Surrogate* testValue001 = safePrimaryType(collectionvalue);

        if (subtypeOfP(testValue001, SGT_SPECIALISTS_STELLA_COLLECTION)) {
          { Object* collectionvalue000 = collectionvalue;
            stella::Collection* collectionvalue = ((stella::Collection*)(collectionvalue000));

            members = assertedCollectionMembers(collectionvalue, false);
            if (!((boolean)(members))) {
              return (KWD_SPECIALISTS_TERMINAL_FAILURE);
            }
          }
        }
        else if (subtypeOfP(testValue001, SGT_SPECIALISTS_LOGIC_SKOLEM)) {
          { Object* collectionvalue001 = collectionvalue;
            Skolem* collectionvalue = ((Skolem*)(collectionvalue001));

            members = assertedCollectionMembers(collectionvalue, false);
            if (!((boolean)(members))) {
              return (KWD_SPECIALISTS_TERMINAL_FAILURE);
            }
          }
        }
        else if (subtypeOfP(testValue001, SGT_SPECIALISTS_LOGIC_DESCRIPTION)) {
          { Object* collectionvalue002 = collectionvalue;
            Description* collectionvalue = ((Description*)(collectionvalue002));

            { boolean testValue002 = false;

              testValue002 = ((boolean)(((Vector*)(dynamicSlotValue(collectionvalue->dynamicSlots, SYM_SPECIALISTS_LOGIC_EXTERNAL_VARIABLES, NULL)))));
              if (testValue002) {
                { boolean foundP000 = false;

                  { PatternVariable* v = NULL;
                    Vector* vector000 = ((Vector*)(dynamicSlotValue(collectionvalue->dynamicSlots, SYM_SPECIALISTS_LOGIC_EXTERNAL_VARIABLES, NULL)));
                    int index000 = 0;
                    int length000 = vector000->length();

                    for  (; index000 < length000; 
                          index000 = index000 + 1) {
                      v = ((PatternVariable*)((vector000->theArray)[index000]));
                      if (!((boolean)(safeArgumentBoundTo(v)))) {
                        foundP000 = true;
                        break;
                      }
                    }
                  }
                  testValue002 = foundP000;
                }
              }
              if (testValue002) {
                return (KWD_SPECIALISTS_TERMINAL_FAILURE);
              }
            }
            if (inferableP(collectionvalue)) {
              createCollectDescriptionExtensionFrame(frame, collectionvalue);
              setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, EMPTY_PROPOSITIONS_ITERATOR, NULL);
              return (KWD_SPECIALISTS_MOVE_DOWN);
            }
            else {
              members = assertedCollectionMembers(collectionvalue, false);
              if (!((boolean)(members))) {
                return (KWD_SPECIALISTS_TERMINAL_FAILURE);
              }
              uniqueP = false;
            }
          }
        }
        else {
          return (KWD_SPECIALISTS_FAILURE);
        }
      }
    }
    else {
      if (!((boolean)(frame->down))) {
        return (KWD_SPECIALISTS_FAILURE);
      }
      { ControlFrame* patternframe = frame->down;

        members = patternframe->patternRecord->collectionList->reverse();
        popFramesUpTo(patternframe);
        if (((boolean)(((Keyword*)(dynamicSlotValue(patternframe->dynamicSlots, SYM_SPECIALISTS_LOGIC_INFERENCE_CUTOFF_REASON, NULL)))))) {
          return (KWD_SPECIALISTS_FAILURE);
        }
      }
    }
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oMODULEo);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      if (((boolean)(result))) {
        if (countP) {
          result = wrapInteger(((Skolem*)(result))->definingProposition->arguments->length() - 1);
        }
      }
      else {
        if (uniqueP) {
          members = (consP(members->first()) ? members->removeDuplicatesEqual() : ((stella::List*)(members->removeDuplicates())));
        }
        if (countP) {
          result = wrapInteger(members->length());
        }
        else if (listP) {
          result = createLogicalList(members);
        }
        else {
          result = createEnumeratedSet(members);
        }
      }
    }
    { Keyword* success = selectTestResult(bindArgumentToValueP(listarg, result, true), true, frame);

      if (oRECORD_JUSTIFICATIONSpo &&
          (!(success == KWD_SPECIALISTS_TERMINAL_FAILURE))) {
        { Justification* self000 = newJustification();

          self000->inferenceRule = KWD_SPECIALISTS_COLLECT_MEMBERS;
          { Justification* justification = self000;
            Justification* antecedents = (((boolean)(frame->result)) ? ((Justification*)(dynamicSlotValue(frame->result->dynamicSlots, SYM_SPECIALISTS_LOGIC_JUSTIFICATION, NULL))) : ((Justification*)(NULL)));

            if (((boolean)(antecedents))) {
              justification->antecedents = cons(antecedents, NIL);
            }
            recordGoalJustification(frame, justification);
          }
        }
      }
      return (success);
    }
  }
}

Keyword* nthElementSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* collectionarg = (proposition->arguments->theArray)[0];
    Object* collection = argumentBoundTo(collectionarg);
    Object* narg = (proposition->arguments->theArray)[1];
    Object* n = argumentBoundTo(narg);
    Object* elementarg = (proposition->arguments->theArray)[2];
    Object* element = argumentBoundTo(elementarg);

    lastmove = lastmove;
    if (logicalCollectionP(collection)) {
      { int then = NULL_INTEGER;
        Vector* arguments = ((Skolem*)(collection))->definingProposition->arguments;
        int nargs = arguments->length() - 1;

        if (integerP(n)) {
          then = unwrapInteger(((IntegerWrapper*)(n)));
          if (then < 0) {
            then = nargs + then;
          }
          if ((then >= 0) &&
              (then < nargs)) {
            return (selectTestResult(bindArgumentToValueP(elementarg, (arguments->theArray)[then], true), true, frame));
          }
        }
        else if ((!((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)))))) &&
            ((!((boolean)(n))) &&
             (((boolean)(element)) &&
              enumeratedSetP(collection)))) {
          { Object* arg = NULL;
            Vector* vector000 = arguments;
            int index000 = 0;
            int length000 = vector000->length();
            int i = NULL_INTEGER;
            int iter000 = 0;
            int upperBound000 = nargs - 1;

            for  (; (index000 < length000) &&
                      (iter000 <= upperBound000); 
                  index000 = index000 + 1,
                  iter000 = iter000 + 1) {
              arg = (vector000->theArray)[index000];
              i = iter000;
              if (eqlP(argumentBoundTo(arg), element)) {
                return (selectTestResult(bindArgumentToValueP(narg, wrapInteger(i), true), true, frame));
              }
            }
          }
        }
        else {
          { AllPurposeIterator* iterator = ((AllPurposeIterator*)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)))));
            PatternRecord* patternrecord = oQUERYITERATORo->currentPatternRecord;
            int ubstackoffset = patternrecord->topUnbindingStackOffset;

            if (!((boolean)(iterator))) {
              iterator = ((AllPurposeIterator*)(((Iterator*)(arguments->allocateIterator()))));
              setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, iterator, NULL);
            }
            { Object* element = NULL;
              AllPurposeIterator* iter001 = iterator;

              for (; iter001->nextP(); ) {
                element = iter001->value;
                if (iterator->iteratorInteger <= nargs) {
                  then = iterator->iteratorInteger - 1;
                  if (bindArgumentToValueP(narg, wrapInteger(then), true) &&
                      bindArgumentToValueP(elementarg, element, true)) {
                    return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
                  }
                  else {
                    unbindVariablesBeginningAt(patternrecord, ubstackoffset + 1);
                  }
                }
              }
            }
          }
        }
      }
    }
    return (KWD_SPECIALISTS_TERMINAL_FAILURE);
  }
}

Skolem* nthHeadComputation(Skolem* list, IntegerWrapper* narg) {
  if (!(enumeratedListP(list))) {
    return (NULL);
  }
  { int n = narg->wrapperValue;
    Vector* elements = list->definingProposition->arguments;
    int nelements = elements->length() - 1;
    stella::List* headelements = stella::newList();

    if (n < 0) {
      n = nelements + n;
    }
    if ((n < 0) ||
        (n > nelements)) {
      return (NULL);
    }
    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = n - 1;
      Cons* collect000 = NULL;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons((elements->theArray)[i], NIL);
            if (headelements->theConsList == NIL) {
              headelements->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(headelements->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons((elements->theArray)[i], NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (createLogicalList(headelements));
  }
}

Skolem* nthRestComputation(Skolem* list, IntegerWrapper* narg) {
  if (!(enumeratedListP(list))) {
    return (NULL);
  }
  { int n = narg->wrapperValue;
    Vector* elements = list->definingProposition->arguments;
    int nelements = elements->length() - 1;
    stella::List* restelements = stella::newList();

    if (n < 0) {
      n = nelements + n;
    }
    if ((n < 0) ||
        (n > nelements)) {
      return (NULL);
    }
    { int i = NULL_INTEGER;
      int iter000 = n;
      int upperBound000 = nelements - 1;
      Cons* collect000 = NULL;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons((elements->theArray)[i], NIL);
            if (restelements->theConsList == NIL) {
              restelements->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(restelements->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons((elements->theArray)[i], NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (createLogicalList(restelements));
  }
}

Skolem* insertElementComputation(Skolem* list, IntegerWrapper* narg, Object* element) {
  if (!(enumeratedListP(list))) {
    return (NULL);
  }
  { int n = narg->wrapperValue;
    Vector* elements = list->definingProposition->arguments;
    int nelements = elements->length() - 1;
    stella::List* newelements = stella::newList();

    if (n < 0) {
      n = nelements + n + 1;
    }
    if ((n < 0) ||
        (n > nelements)) {
      return (NULL);
    }
    { Object* elt = NULL;
      Vector* vector000 = elements;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = nelements - 1;

      for  (; (index000 < length000) &&
                (iter000 <= upperBound000); 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        elt = (vector000->theArray)[index000];
        i = iter000;
        if (i == n) {
          newelements->push(element);
        }
        newelements->push(elt);
      }
    }
    if (n == nelements) {
      newelements->push(element);
    }
    return (createLogicalList(newelements->reverse()));
  }
}

Keyword* minimumOfNumbersSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* listarg = (proposition->arguments->theArray)[0];
    Object* listskolem = argumentBoundTo(listarg);
    Object* minarg = (proposition->arguments->theArray)[1];
    Object* minvalue = argumentBoundTo(minarg);
    NumberWrapper* minimum = NULL;
    boolean missingnumbersP = false;

    lastmove = lastmove;
    if (((boolean)(listskolem)) &&
        (!logicalCollectionP(listskolem))) {
      std::cout << std::endl << "Non list appears in second argument to 'MINIMUM-OF-NUMBERS'" << std::endl << std::endl;
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
    { stella::List* listvalue = assertedCollectionMembers(listskolem, true);

      if (listvalue->emptyP()) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      { Object* v = NULL;
        Cons* iter000 = listvalue->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          v = iter000->value;
          if (isaP(v, SGT_SPECIALISTS_STELLA_NUMBER_WRAPPER)) {
            if ((!((boolean)(minimum))) ||
                arithmeticLessTest(((NumberWrapper*)(v)), minimum)) {
              minimum = ((NumberWrapper*)(v));
            }
          }
          else {
            missingnumbersP = true;
          }
        }
      }
      if (!((boolean)(minimum))) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      if (missingnumbersP) {
        if (((boolean)(minvalue)) &&
            (isaP(minvalue, SGT_SPECIALISTS_STELLA_NUMBER_WRAPPER) &&
             arithmeticGreaterTest(((NumberWrapper*)(minvalue)), minimum))) {
          {
            setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
            return (KWD_SPECIALISTS_TERMINAL_FAILURE);
          }
        }
        else {
          {
            setFrameTruthValue(frame, UNKNOWN_TRUTH_VALUE);
            return (KWD_SPECIALISTS_FAILURE);
          }
        }
      }
      return (selectTestResult(bindArgumentToValueP(minarg, minimum, true), true, frame));
    }
  }
}

Keyword* maximumOfNumbersSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* listarg = (proposition->arguments->theArray)[0];
    Object* listskolem = argumentBoundTo(listarg);
    Object* maxarg = (proposition->arguments->theArray)[1];
    Object* maxvalue = argumentBoundTo(maxarg);
    NumberWrapper* maximum = NULL;
    boolean missingnumbersP = false;

    lastmove = lastmove;
    if (((boolean)(listskolem)) &&
        (!logicalCollectionP(listskolem))) {
      std::cout << std::endl << "Non list appears in second argument to 'MAXIMUM-OF-NUMBERS'" << std::endl << std::endl;
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
    { stella::List* listvalue = assertedCollectionMembers(listskolem, true);

      if (listvalue->emptyP()) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      { Object* v = NULL;
        Cons* iter000 = listvalue->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          v = iter000->value;
          if (isaP(v, SGT_SPECIALISTS_STELLA_NUMBER_WRAPPER)) {
            if ((!((boolean)(maximum))) ||
                arithmeticGreaterTest(((NumberWrapper*)(v)), maximum)) {
              maximum = ((NumberWrapper*)(v));
            }
          }
          else {
            missingnumbersP = true;
          }
        }
      }
      if (!((boolean)(maximum))) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      if (missingnumbersP) {
        if (((boolean)(maxvalue)) &&
            (isaP(maxvalue, SGT_SPECIALISTS_STELLA_NUMBER_WRAPPER) &&
             arithmeticLessTest(((NumberWrapper*)(maxvalue)), maximum))) {
          {
            setFrameTruthValue(frame, FALSE_TRUTH_VALUE);
            return (KWD_SPECIALISTS_TERMINAL_FAILURE);
          }
        }
        else {
          {
            setFrameTruthValue(frame, UNKNOWN_TRUTH_VALUE);
            return (KWD_SPECIALISTS_FAILURE);
          }
        }
      }
      return (selectTestResult(bindArgumentToValueP(maxarg, maximum, true), true, frame));
    }
  }
}

Keyword* sumOfNumbersSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* listarg = (proposition->arguments->theArray)[0];
    Object* listskolem = argumentBoundTo(listarg);
    Object* sumarg = (proposition->arguments->theArray)[1];
    NumberWrapper* sum = wrapInteger(0);

    lastmove = lastmove;
    if (((boolean)(listskolem)) &&
        (!logicalCollectionP(listskolem))) {
      std::cout << std::endl << "Non list appears in second argument to 'SUM-OF-NUMBERS'" << std::endl << std::endl;
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
    { stella::List* listvalue = assertedCollectionMembers(listskolem, true);

      { Object* v = NULL;
        Cons* iter000 = listvalue->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          v = iter000->value;
          if (isaP(v, SGT_SPECIALISTS_STELLA_NUMBER_WRAPPER)) {
            sum = plusComputation(((NumberWrapper*)(v)), sum);
          }
          else {
            return (KWD_SPECIALISTS_TERMINAL_FAILURE);
          }
        }
      }
      return (selectTestResult(bindArgumentToValueP(sumarg, sum, true), true, frame));
    }
  }
}

Keyword* meanOfNumbersSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* listarg = (proposition->arguments->theArray)[0];
    Object* listskolem = argumentBoundTo(listarg);
    Object* meanarg = (proposition->arguments->theArray)[1];
    NumberWrapper* sum = wrapInteger(0);
    int numbercount = 0;

    lastmove = lastmove;
    if (((boolean)(listskolem)) &&
        (!logicalCollectionP(listskolem))) {
      std::cout << std::endl << "Non list appears in second argument to 'MEAN-OF-NUMBERS'" << std::endl << std::endl;
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
    { stella::List* listvalue = assertedCollectionMembers(listskolem, true);

      if (listvalue->emptyP()) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      { Object* v = NULL;
        Cons* iter000 = listvalue->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          v = iter000->value;
          if (isaP(v, SGT_SPECIALISTS_STELLA_NUMBER_WRAPPER)) {
            {
              sum = plusComputation(((NumberWrapper*)(v)), sum);
              numbercount = numbercount + 1;
            }
          }
          else {
            return (KWD_SPECIALISTS_FAILURE);
          }
        }
      }
      if (numbercount == 0) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      else {
        return (selectTestResult(bindArgumentToValueP(meanarg, divideComputation(sum, wrapInteger(numbercount)), true), true, frame));
      }
    }
  }
}

Keyword* medianOfNumbersSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* listarg = (proposition->arguments->theArray)[0];
    stella::List* sortlist = stella::newList();
    Object* listskolem = argumentBoundTo(listarg);
    Object* medianarg = (proposition->arguments->theArray)[1];
    int numbercount = 0;
    NumberWrapper* result = NULL;

    lastmove = lastmove;
    if (((boolean)(listskolem)) &&
        (!logicalCollectionP(listskolem))) {
      std::cout << std::endl << "Non list appears in second argument to 'MEDIAN-OF-NUMBERS'" << std::endl << std::endl;
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
    { stella::List* listvalue = assertedCollectionMembers(listskolem, true);

      if (listvalue->emptyP()) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      { Object* v = NULL;
        Cons* iter000 = listvalue->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          v = iter000->value;
          if (isaP(v, SGT_SPECIALISTS_STELLA_NUMBER_WRAPPER)) {
            sortlist->push(((NumberWrapper*)(v)));
          }
          else {
            return (KWD_SPECIALISTS_FAILURE);
          }
        }
      }
      numbercount = sortlist->length();
      if (numbercount == 0) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      sortlist->sort(((cpp_function_code)(&arithmeticLessTest)));
      if ((numbercount % 2)) {
        result = ((NumberWrapper*)(sortlist->nth(((int)((numbercount - 1) / 2.0)))));
      }
      else {
        result = divideComputation(plusComputation(((NumberWrapper*)(sortlist->nth(((int)((numbercount / 2.0) - 1))))), ((NumberWrapper*)(sortlist->nth(((int)(numbercount / 2.0)))))), wrapInteger(2));
      }
      return (selectTestResult(bindArgumentToValueP(medianarg, result, true), true, frame));
    }
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

Keyword* computeVarianceOrStandardDeviation(ControlFrame* frame, Keyword* lastmove, boolean standardDeviationP) {
  { Proposition* proposition = frame->proposition;
    Object* listarg = (proposition->arguments->theArray)[0];
    Object* listskolem = argumentBoundTo(listarg);
    Object* resultargg = (proposition->arguments->theArray)[1];
    double sum = 0.0;
    double sum2 = 0.0;
    double x = 0.0;
    int numbercount = 0;

    lastmove = lastmove;
    if (((boolean)(listskolem)) &&
        (!logicalCollectionP(listskolem))) {
      std::cout << std::endl << "Non list appears in second argument to 'VARIANCE or STANDARD-DEVIATION'" << std::endl << std::endl;
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
    { List* listvalue = assertedCollectionMembers(listskolem, true);

      if (listvalue->emptyP()) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      { Object* v = NULL;
        Cons* iter000 = listvalue->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          v = iter000->value;
          { Surrogate* testValue000 = safePrimaryType(v);

            if (subtypeOfIntegerP(testValue000)) {
              { Object* v000 = v;
                IntegerWrapper* v = ((IntegerWrapper*)(v000));

                x = ((double)(v->wrapperValue));
              }
            }
            else if (subtypeOfFloatP(testValue000)) {
              { Object* v001 = v;
                FloatWrapper* v = ((FloatWrapper*)(v001));

                x = v->wrapperValue;
              }
            }
            else {
              setFrameTruthValue(frame, UNKNOWN_TRUTH_VALUE);
              return (KWD_SPECIALISTS_FAILURE);
            }
          }
          sum = sum + x;
          sum2 = sum2 + (x * x);
          numbercount = numbercount + 1;
        }
      }
      switch (numbercount) {
        case 0: 
          return (KWD_SPECIALISTS_TERMINAL_FAILURE);
        case 1: 
          return (selectTestResult(bindArgumentToValueP(resultargg, wrapFloat(0.0), true), true, frame));
        default:
          x = (sum2 - ((sum * sum) / numbercount)) / (numbercount - 1);
          if (standardDeviationP) {
            x = ::sqrt(x);
          }
          return (selectTestResult(bindArgumentToValueP(resultargg, wrapFloat(x), true), true, frame));
      }
    }
  }
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* standardDeviationSpecialist(ControlFrame* frame, Keyword* lastmove) {
  return (computeVarianceOrStandardDeviation(frame, lastmove, true));
}

Keyword* varianceSpecialist(ControlFrame* frame, Keyword* lastmove) {
  return (computeVarianceOrStandardDeviation(frame, lastmove, false));
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

void helpDerivePartitionMemberships(LogicObject* self, LogicObject* super, List* tuples) {
  { Cons* dummy1;
    Cons* dummy2;

    { Object* mc = NULL;
      Cons* iter000 = applyCachedRetrieve(listO(3, SYM_SPECIALISTS_LOGIC_pSUPER, SYM_SPECIALISTS_LOGIC_pMDC, NIL), listO(4, SYM_SPECIALISTS_STELLA_AND, listO(4, SYM_SPECIALISTS_LOGIC_MEMBER_OF, SYM_SPECIALISTS_LOGIC_pSUPER, SYM_SPECIALISTS_LOGIC_pMDC, NIL), listO(3, SYM_SPECIALISTS_LOGIC_MUTUALLY_DISJOINT_COLLECTION, SYM_SPECIALISTS_LOGIC_pMDC, NIL), NIL), consList(2, super, NULL), consList(0), SYM_SPECIALISTS_LOGIC_F_HELP_DERIVE_PARTITION_MEMBERSHIPS_QUERY_000, dummy1, dummy2);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        mc = iter000->value;
        { Proposition* mdcproposition = ((Proposition*)(allTrueDependentPropositions(mc, SGT_SPECIALISTS_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION, false)->consify()->value));

          tuples->push(assertTuple(SGT_SPECIALISTS_PL_KERNEL_KB_PARTITION_MEMBERSHIP, consList(3, self, mdcproposition, super)));
        }
      }
    }
    { Proposition* p = NULL;
      Iterator* iter001 = allTrueDependentPropositions(super, SGT_SPECIALISTS_PL_KERNEL_KB_DISJOINT, false);

      for (; iter001->nextP(); ) {
        p = ((Proposition*)(iter001->value));
        tuples->push(assertTuple(SGT_SPECIALISTS_PL_KERNEL_KB_PARTITION_MEMBERSHIP, consList(3, self, p, super)));
      }
    }
  }
}

boolean derivePartitionMembershipsP(LogicObject* self) {
  { List* tuples = list(0);

    helpDerivePartitionMemberships(self, self, tuples);
    { LogicObject* super = NULL;
      Iterator* iter000 = allSupercollections(self);

      for (; iter000->nextP(); ) {
        super = ((LogicObject*)(iter000->value));
        helpDerivePartitionMemberships(self, super, tuples);
      }
    }
    return (tuples->nonEmptyP());
  }
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* hasPartitionMembershipSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* argumentvalue = argumentBoundTo((proposition->arguments->theArray)[0]);

    lastmove = lastmove;
    if ((!((boolean)(argumentvalue))) ||
        (!isaP(argumentvalue, SGT_SPECIALISTS_LOGIC_LOGIC_OBJECT))) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    { Proposition* value000 = NULL;

      { Proposition* p = NULL;
        Iterator* iter000 = unfilteredDependentPropositions(argumentvalue, SGT_SPECIALISTS_PL_KERNEL_KB_HAS_PARTITION_MEMBERSHIP)->allocateIterator();

        for (; iter000->nextP(); ) {
          p = ((Proposition*)(iter000->value));
          if (((Surrogate*)(p->operatoR)) == SGT_SPECIALISTS_PL_KERNEL_KB_HAS_PARTITION_MEMBERSHIP) {
            value000 = p;
            break;
          }
        }
      }
      { Proposition* haspartitionproposition = value000;

        if (((boolean)(haspartitionproposition))) {
          if (trueP(haspartitionproposition)) {
            return (KWD_SPECIALISTS_FINAL_SUCCESS);
          }
          else if (falseP(haspartitionproposition)) {
            return (KWD_SPECIALISTS_TERMINAL_FAILURE);
          }
        }
        if (derivePartitionMembershipsP(((LogicObject*)(argumentvalue)))) {
          {
            updateProperty(((LogicObject*)(argumentvalue)), SGT_SPECIALISTS_PL_KERNEL_KB_HAS_PARTITION_MEMBERSHIP, KWD_SPECIALISTS_ASSERT_TRUE);
            return (KWD_SPECIALISTS_FINAL_SUCCESS);
          }
        }
        else {
          {
            updateProperty(((LogicObject*)(argumentvalue)), SGT_SPECIALISTS_PL_KERNEL_KB_HAS_PARTITION_MEMBERSHIP, KWD_SPECIALISTS_ASSERT_FALSE);
            return (KWD_SPECIALISTS_TERMINAL_FAILURE);
          }
        }
      }
    }
  }
}

Keyword* refutationDisjointSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* arg1 = argumentBoundTo((proposition->arguments->theArray)[0]);
    Object* arg2 = argumentBoundTo((proposition->arguments->theArray)[1]);

    lastmove = lastmove;
    if ((!((boolean)(arg1))) ||
        ((!((boolean)(arg2))) ||
         ((!isaP(arg1, SGT_SPECIALISTS_LOGIC_DESCRIPTION)) ||
          ((!isaP(arg2, SGT_SPECIALISTS_LOGIC_DESCRIPTION)) ||
           (proposition->arguments->length() > 2))))) {
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
    pushMonotonicWorld();
    initializeInferenceWorld(((World*)(oCONTEXTo)));
    try {
      { LogicObject* skolem = createHypothesizedInstance("refutation-disjoint");

        { Description* c = NULL;
          Cons* iter000 = ((Cons*)(consList(2, arg1, arg2)));

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            c = ((Description*)(iter000->value));
            assertMemberOfProposition(skolem, c);
          }
        }
        elaborateInstance(skolem);
      }
    }
    catch (Clash ) {
      popWorld();
      return (KWD_SPECIALISTS_FINAL_SUCCESS);
    }
    popWorld();
    return (KWD_SPECIALISTS_FAILURE);
  }
}

Keyword* emptySpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* argvalue = argumentBoundTo((proposition->arguments->theArray)[0]);
    boolean emptyP = emptyTermP(argvalue);

    lastmove = lastmove;
    return (selectProofResult(emptyP, false, true));
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

boolean emptyTermP(Object* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_LOGIC_OBJECT)) {
      { Object* self000 = self;
        LogicObject* self = ((LogicObject*)(self000));

        return (cheapEmptyTermP(self) ||
            expensiveEmptyTermP(self));
      }
    }
    else if (subtypeOfP(testValue000, SGT_SPECIALISTS_STELLA_COLLECTION)) {
      { Object* self001 = self;
        Collection* self = ((Collection*)(self001));

        return (self->length() == 0);
      }
    }
    else {
      return (false);
    }
  }
}

boolean cheapEmptyTermP(LogicObject* self) {
  if (skolemP(self)) {
    { Proposition* definingproposition = ((Skolem*)(self))->definingProposition;

      if (((boolean)(definingproposition)) &&
          (collectionofPropositionP(definingproposition) &&
           (definingproposition->arguments->length() == 1))) {
        return (true);
      }
    }
  }
  { boolean testValue000 = false;

    if (testPropertyP(self, SGT_SPECIALISTS_PL_KERNEL_KB_EMPTY)) {
      testValue000 = true;
    }
    else {
      { boolean foundP000 = false;

        { LogicObject* super = NULL;
          Iterator* iter000 = allDirectSupercollections(self, false);

          for (; iter000->nextP(); ) {
            super = ((LogicObject*)(iter000->value));
            if (cheapEmptyTermP(super)) {
              foundP000 = true;
              break;
            }
          }
        }
        testValue000 = foundP000;
      }
    }
    { boolean value000 = testValue000;

      return (value000);
    }
  }
}

boolean expensiveEmptyTermP(LogicObject* self) {
  { LogicObject* super1 = NULL;
    Iterator* iter000 = allDirectSupercollections(self, false);

    for (; iter000->nextP(); ) {
      super1 = ((LogicObject*)(iter000->value));
      { LogicObject* super2 = NULL;
        Iterator* iter001 = allDirectSupercollections(self, false);

        for (; iter001->nextP(); ) {
          super2 = ((LogicObject*)(iter001->value));
          if ((!(super1 == super2)) &&
              disjointTermsP(((Description*)(super1)), ((Description*)(super2)))) {
            return (true);
          }
        }
      }
    }
  }
  return (false);
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Context* objectContextComputation(Object* instance) {
  return (instance->homeModule());
}

Context* objectNameContextComputation(Object* instance) {
  { Surrogate* namesymbol = objectSurrogate(valueOf(instance));

    if (!((boolean)(namesymbol))) {
      return (NULL);
    }
    else {
      return (namesymbol->homeModule());
    }
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

SavedContextProofAdjunct* newSavedContextProofAdjunct() {
  { SavedContextProofAdjunct* self = NULL;

    self = new SavedContextProofAdjunct();
    self->downFrame = NULL;
    self->savedContext = NULL;
    return (self);
  }
}

Surrogate* SavedContextProofAdjunct::primaryType() {
  { SavedContextProofAdjunct* self = this;

    return (SGT_SPECIALISTS_LOGIC_SAVED_CONTEXT_PROOF_ADJUNCT);
  }
}

Object* accessSavedContextProofAdjunctSlotValue(SavedContextProofAdjunct* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_SPECIALISTS_LOGIC_SAVED_CONTEXT) {
    if (setvalueP) {
      self->savedContext = ((Context*)(value));
    }
    else {
      value = self->savedContext;
    }
  }
  else if (slotname == SYM_SPECIALISTS_LOGIC_DOWN_FRAME) {
    if (setvalueP) {
      self->downFrame = ((ControlFrame*)(value));
    }
    else {
      value = self->downFrame;
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


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* istSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* contextvalue = argumentBoundTo((proposition->arguments->theArray)[0]);
    SavedContextProofAdjunct* adjunct = ((SavedContextProofAdjunct*)(((ProofAdjunct*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_LOGIC_PROOF_ADJUNCT, NULL)))));

    if (lastmove == KWD_SPECIALISTS_DOWN) {
      if (!((boolean)(adjunct))) {
        { Object* propositionvalue = argumentBoundTo((proposition->arguments->theArray)[1]);

          if ((!((boolean)(contextvalue))) ||
              ((!((boolean)(propositionvalue))) ||
               (!isaP(contextvalue, SGT_SPECIALISTS_STELLA_CONTEXT)))) {
            return (KWD_SPECIALISTS_TERMINAL_FAILURE);
          }
          frame->choicePointUnbindingOffset = NULL_INTEGER;
          { SavedContextProofAdjunct* self000 = newSavedContextProofAdjunct();

            self000->savedContext = oCONTEXTo;
            self000->downFrame = createDownFrame(frame, ((Proposition*)(propositionvalue)));
            adjunct = self000;
          }
          setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_LOGIC_PROOF_ADJUNCT, adjunct, NULL);
        }
      }
      frame->down = adjunct->downFrame;
      getInferenceCache(((Context*)(contextvalue)), KWD_SPECIALISTS_JUST_IN_TIME);
      bestInferenceCache(((Context*)(contextvalue)))->changeContext();
      return (KWD_SPECIALISTS_MOVE_DOWN);
    }
    else if (lastmove == KWD_SPECIALISTS_UP_TRUE) {
      propagateFrameTruthValue(frame->result, frame);
      if (((boolean)(oQUERYITERATORo)) &&
          ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
        frame->result->partialMatchFrame->propagateFramePartialTruth(frame);
      }
      if (oRECORD_JUSTIFICATIONSpo) {
        { Justification* self001 = newJustification();

          self001->inferenceRule = KWD_SPECIALISTS_IST_INTRODUCTION;
          self001->antecedents = cons(((Justification*)(dynamicSlotValue(frame->result->dynamicSlots, SYM_SPECIALISTS_LOGIC_JUSTIFICATION, NULL))), NIL);
          recordGoalJustification(frame, self001);
        }
      }
      adjunct->savedContext->changeContext();
      if (((boolean)(frame->down))) {
        adjunct->downFrame = frame->down;
        frame->down = NULL;
        return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
      }
      else {
        return (KWD_SPECIALISTS_FINAL_SUCCESS);
      }
    }
    else if (lastmove == KWD_SPECIALISTS_UP_FAIL) {
      propagateFrameTruthValue(frame->result, frame);
      if (((boolean)(oQUERYITERATORo)) &&
          ((boolean)(oQUERYITERATORo->partialMatchStrategy))) {
        frame->result->partialMatchFrame->propagateFramePartialTruth(frame);
      }
      if (oRECORD_JUSTIFICATIONSpo) {
        recordPrimitiveJustification(frame, KWD_SPECIALISTS_UP_FAIL);
      }
      adjunct->savedContext->changeContext();
      return (KWD_SPECIALISTS_FAILURE);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << lastmove << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

// Used to test how big is the effect of the frame
// specialists.
boolean oACCELERATE_FRAME_COMPUTATIONSpo = true;

Skolem* getRolesetOf(NamedDescription* relation, Object* instance) {
  return (((Skolem*)(allRelationValues(SGT_SPECIALISTS_PL_KERNEL_KB_THE_ROLESET, consList(2, relation, instance))->value)));
}

int computeStoredBoundOnRoleset(NamedDescription* relation, Object* instance, Keyword* lowerorupper) {
  { Skolem* roleset = getRolesetOf(relation, instance);
    Object* cardinality = NULL;
    pl_kernel_kb::IntervalCache* intervalcache = NULL;
    Object* bound = NULL;

    if (!((boolean)(roleset))) {
      return (NULL_INTEGER);
    }
    cardinality = accessBinaryValue(roleset, SGT_SPECIALISTS_PL_KERNEL_KB_CARDINALITY);
    if (((boolean)(cardinality))) {
      { Surrogate* testValue000 = safePrimaryType(cardinality);

        if (subtypeOfIntegerP(testValue000)) {
          { Object* cardinality000 = cardinality;
            IntegerWrapper* cardinality = ((IntegerWrapper*)(cardinality000));

            return (cardinality->wrapperValue);
          }
        }
        else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_SKOLEM)) {
          { Object* cardinality001 = cardinality;
            Skolem* cardinality = ((Skolem*)(cardinality001));

            { 
              intervalcache = pl_kernel_kb::getIntervalCache(cardinality);
              if (((boolean)(intervalcache))) {
                if (lowerorupper == KWD_SPECIALISTS_LOWER) {
                  bound = intervalcache->lowerBound;
                }
                else if (lowerorupper == KWD_SPECIALISTS_UPPER) {
                  bound = intervalcache->upperBound;
                }
                else {
                  { OutputStringStream* stream000 = newOutputStringStream();

                    *(stream000->nativeStream) << "`" << lowerorupper << "'" << " is not a valid case option";
                    throw *newStellaException(stream000->theStringReader());
                  }
                }
                if (((boolean)(bound)) &&
                    isaP(bound, SGT_SPECIALISTS_STELLA_INTEGER_WRAPPER)) {
                  return (unwrapInteger(((IntegerWrapper*)(bound))));
                }
              }
            }
          }
        }
        else {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream001->theStringReader());
          }
        }
      }
    }
    return (NULL_INTEGER);
  }
}

int computeMinimumCardinality(NamedDescription* relation, Object* instance) {
  { 
    BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
    { Surrogate* relationref = relation->surrogateValueInverse;

      if (singleValuedTermP(relation) &&
          ((boolean)(accessBinaryValue(instance, relationref)))) {
        return (1);
      }
      { Cons* mincards = consList(2, wrapInteger(0), wrapInteger(computeStoredBoundOnRoleset(relation, instance, KWD_SPECIALISTS_LOWER)));

        mincards = cons(wrapInteger(allSlotValues(((LogicObject*)(instance)), relationref)->length()), mincards);
        { NamedDescription* subr = NULL;
          Cons* iter000 = allSubrelations(relation, false);

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            subr = ((NamedDescription*)(iter000->value));
            mincards = cons(wrapInteger(computeStoredBoundOnRoleset(subr, instance, KWD_SPECIALISTS_LOWER)), mincards);
          }
        }
        { int maxmin = ((IntegerWrapper*)(mincards->value))->wrapperValue;

          { IntegerWrapper* lb = NULL;
            Cons* iter001 = mincards->rest;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              lb = ((IntegerWrapper*)(iter001->value));
              if (((boolean)(lb))) {
                maxmin = stella::integerMax(maxmin, lb->wrapperValue);
              }
            }
          }
          return (maxmin);
        }
      }
    }
  }
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* rangeMinCardinalitySpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* relation = argumentBoundTo((proposition->arguments->theArray)[0]);
    Object* instance = argumentBoundTo((proposition->arguments->theArray)[1]);
    Object* mincardarg = (proposition->arguments->theArray)[2];
    Object* mincardvalue = argumentBoundTo(mincardarg);
    int computedvalue = NULL_INTEGER;

    lastmove = lastmove;
    if (!oACCELERATE_FRAME_COMPUTATIONSpo) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    if ((!((boolean)(relation))) ||
        (!((boolean)(instance)))) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    { boolean testValue000 = false;

      testValue000 = isaP(relation, SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION);
      if (testValue000) {
        { 
          computedvalue = computeMinimumCardinality(((NamedDescription*)(relation)), instance);
          testValue000 = computedvalue != NULL_INTEGER;
        }
      }
      if (testValue000) {
        { TruthValue* tv = UNKNOWN_TRUTH_VALUE;

          if (((boolean)(mincardvalue)) &&
              isaP(mincardvalue, SGT_SPECIALISTS_STELLA_INTEGER_WRAPPER)) {
            if (computedvalue >= ((NumberWrapper*)(mincardvalue))->numberWrapperToFloat()) {
              {
                tv = TRUE_TRUTH_VALUE;
              }
            }
            else {
              if (closedTermP(relation)) {
                {
                  tv = FALSE_TRUTH_VALUE;
                }
              }
              else {
                { boolean testValue001 = false;

                  { 
                    computedvalue = computeMaximumCardinality(((NamedDescription*)(relation)), instance);
                    testValue001 = computedvalue != NULL_INTEGER;
                  }
                  if (testValue001) {
                    testValue001 = computedvalue < ((NumberWrapper*)(mincardvalue))->numberWrapperToFloat();
                  }
                  if (testValue001) {
                    tv = FALSE_TRUTH_VALUE;
                  }
                }
              }
            }
          }
          else {
            if (bindArgumentToValueP(mincardarg, wrapInteger(computedvalue), true)) {
              tv = TRUE_TRUTH_VALUE;
            }
            else {
              tv = FALSE_TRUTH_VALUE;
            }
          }
          if (oREVERSEPOLARITYpo) {
            tv = invertTruthValue(tv);
          }
          setFrameTruthValue(frame, tv);
          if ((tv == TRUE_TRUTH_VALUE) ||
              (tv == DEFAULT_TRUE_TRUTH_VALUE)) {
            return (KWD_SPECIALISTS_FINAL_SUCCESS);
          }
          else if ((tv == FALSE_TRUTH_VALUE) ||
              (tv == DEFAULT_FALSE_TRUTH_VALUE)) {
            return (KWD_SPECIALISTS_FAILURE);
          }
          else {
            return (KWD_SPECIALISTS_FAILURE);
          }
        }
      }
      else {
        return (KWD_SPECIALISTS_FAILURE);
      }
    }
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

int computeMaximumCardinality(NamedDescription* relation, Object* instance) {
  { 
    BIND_STELLA_SPECIAL(oREVERSEPOLARITYpo, boolean, false);
    { Surrogate* relationref = relation->surrogateValueInverse;
      boolean singlevaluedP = singleValuedTermP(relation);

      if (singlevaluedP &&
          ((boolean)(accessBinaryValue(instance, relationref)))) {
        return (1);
      }
      { Cons* maxcards = consList(1, wrapInteger(computeStoredBoundOnRoleset(relation, instance, KWD_SPECIALISTS_UPPER)));

        if (singlevaluedP) {
          maxcards = cons(wrapInteger(1), maxcards);
        }
        { Skolem* roleset = getRolesetOf(relation, instance);

          if (((boolean)(roleset)) &&
              emptyTermP(roleset)) {
            return (0);
          }
        }
        if (closedTermP(relation)) {
          maxcards = cons(wrapInteger(computeMinimumCardinality(relation, instance)), maxcards);
        }
        { NamedDescription* superr = NULL;
          Cons* iter000 = allSuperrelations(relation, false);

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            superr = ((NamedDescription*)(iter000->value));
            maxcards = cons(wrapInteger(computeStoredBoundOnRoleset(superr, instance, KWD_SPECIALISTS_UPPER)), maxcards);
          }
        }
        { int minmax = ((IntegerWrapper*)(maxcards->value))->wrapperValue;

          { IntegerWrapper* ub = NULL;
            Cons* iter001 = maxcards->rest;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              ub = ((IntegerWrapper*)(iter001->value));
              if (((boolean)(ub))) {
                minmax = stella::integerMin(minmax, ub->wrapperValue);
              }
            }
          }
          return (minmax);
        }
      }
    }
  }
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* rangeMaxCardinalitySpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* relation = argumentBoundTo((proposition->arguments->theArray)[0]);
    Object* instance = argumentBoundTo((proposition->arguments->theArray)[1]);
    Object* maxcardarg = (proposition->arguments->theArray)[2];
    Object* maxcardvalue = argumentBoundTo(maxcardarg);
    int computedvalue = NULL_INTEGER;

    lastmove = lastmove;
    if (!oACCELERATE_FRAME_COMPUTATIONSpo) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    if ((!((boolean)(relation))) ||
        (!((boolean)(instance)))) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    { boolean testValue000 = false;

      testValue000 = isaP(relation, SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION);
      if (testValue000) {
        { 
          computedvalue = computeMaximumCardinality(((NamedDescription*)(relation)), instance);
          testValue000 = computedvalue != NULL_INTEGER;
        }
      }
      if (testValue000) {
        { boolean successP = ((((boolean)(maxcardvalue)) &&
              isaP(maxcardvalue, SGT_SPECIALISTS_STELLA_INTEGER_WRAPPER)) ? (computedvalue <= ((NumberWrapper*)(maxcardvalue))->numberWrapperToFloat()) : bindArgumentToValueP(maxcardarg, wrapInteger(computedvalue), true));

          return (selectTestResult(successP, true, frame));
        }
      }
      else {
        { boolean testValue001 = false;

          testValue001 = ((boolean)(maxcardvalue));
          if (testValue001) {
            testValue001 = isaP(maxcardvalue, SGT_SPECIALISTS_STELLA_INTEGER_WRAPPER);
            if (testValue001) {
              { 
                computedvalue = computeMinimumCardinality(((NamedDescription*)(relation)), instance);
                testValue001 = computedvalue != NULL_INTEGER;
              }
              if (testValue001) {
                testValue001 = computedvalue > ((NumberWrapper*)(maxcardvalue))->numberWrapperToFloat();
              }
            }
          }
          if (testValue001) {
            return (selectTestResult(false, true, frame));
          }
          else {
            return (KWD_SPECIALISTS_FAILURE);
          }
        }
      }
    }
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

boolean testRangeTypeP(NamedDescription* relation, Object* instance, NamedDescription* valuetype) {
  { Surrogate* relationref = relation->surrogateValueInverse;
    Surrogate* valuesurrogate = valuetype->surrogateValueInverse;

    if (singleValuedTermP(relation)) {
      { Object* filler = accessBinaryValue(instance, relationref);

        if (((boolean)(filler))) {
          return (testTypeOnInstanceP(filler, valuesurrogate));
        }
      }
    }
    { Skolem* roleset = getRolesetOf(relation, instance);
      boolean closedP = closedTermP(relation) ||
          closedTermP(roleset);

      if (((boolean)(roleset))) {
        { boolean testValue000 = false;

          if (collectionImpliesCollectionP(roleset, valuetype)) {
            testValue000 = true;
          }
          else {
            {
              testValue000 = closedP;
              if (testValue000) {
                { boolean alwaysP000 = true;

                  { Object* filler = NULL;
                    Cons* iter000 = allSlotValues(((LogicObject*)(instance)), relationref);

                    for (; !(iter000 == NIL); iter000 = iter000->rest) {
                      filler = iter000->value;
                      if (!testTypeOnInstanceP(filler, valuesurrogate)) {
                        alwaysP000 = false;
                        break;
                      }
                    }
                  }
                  testValue000 = alwaysP000;
                }
              }
            }
          }
          if (testValue000) {
            return (true);
          }
        }
      }
      else {
        { boolean testValue001 = false;

          testValue001 = closedP;
          if (testValue001) {
            { boolean alwaysP001 = true;

              { Object* filler = NULL;
                Cons* iter001 = allSlotValues(((LogicObject*)(instance)), relationref);

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  filler = iter001->value;
                  if (!testTypeOnInstanceP(filler, valuesurrogate)) {
                    alwaysP001 = false;
                    break;
                  }
                }
              }
              testValue001 = alwaysP001;
            }
          }
          if (testValue001) {
            return (true);
          }
        }
      }
    }
    { NamedDescription* superr = NULL;
      Cons* iter002 = allSuperrelations(relation, false);

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        superr = ((NamedDescription*)(iter002->value));
        { Skolem* superroleset = getRolesetOf(superr, instance);

          if (((boolean)(superroleset)) &&
              collectionImpliesCollectionP(superroleset, valuetype)) {
            return (true);
          }
        }
      }
    }
    return (false);
  }
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* rangeTypeSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* relation = argumentBoundTo((proposition->arguments->theArray)[0]);
    Object* instance = argumentBoundTo((proposition->arguments->theArray)[1]);
    Object* valuetypearg = (proposition->arguments->theArray)[2];
    Object* valuetypevalue = argumentBoundTo(valuetypearg);

    lastmove = lastmove;
    if (!oACCELERATE_FRAME_COMPUTATIONSpo) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    if ((!((boolean)(relation))) ||
        (!((boolean)(instance)))) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    if (!((boolean)(valuetypevalue))) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    if (isaP(valuetypevalue, SGT_SPECIALISTS_STELLA_SURROGATE)) {
      valuetypevalue = surrogateToDescription(((Surrogate*)(valuetypevalue)));
    }
    if ((!isaP(relation, SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION)) ||
        ((!isaP(valuetypevalue, SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION)) ||
         (!((boolean)(valuetypevalue))))) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    if (testRangeTypeP(((NamedDescription*)(relation)), instance, ((NamedDescription*)(valuetypevalue)))) {
      return (selectTestResult(true, true, frame));
    }
    else {
      return (KWD_SPECIALISTS_FAILURE);
    }
  }
}

Keyword* reflexiveRelationSpecialist(ControlFrame* frame, Keyword* lastmove) {
  lastmove = lastmove;
  { Proposition* proposition = frame->proposition;
    Object* arg1 = (proposition->arguments->theArray)[0];
    Object* arg2 = (proposition->arguments->theArray)[1];
    Object* arg1Val = argumentBoundTo(arg1);
    Object* arg2Val = argumentBoundTo(arg2);

    if (((boolean)(arg1Val)) &&
        bindArgumentToValueP(arg2, arg1Val, true)) {
      return (selectTestResult(true, true, frame));
    }
    else if (((boolean)(arg2Val)) &&
        bindArgumentToValueP(arg1, arg2Val, true)) {
      return (selectTestResult(true, true, frame));
    }
    else {
      return (KWD_SPECIALISTS_FAILURE);
    }
  }
}

Keyword* irreflexiveRelationSpecialist(ControlFrame* frame, Keyword* lastmove) {
  lastmove = lastmove;
  { Proposition* proposition = frame->proposition;
    Object* arg1 = argumentBoundTo((proposition->arguments->theArray)[0]);
    Object* arg2 = argumentBoundTo((proposition->arguments->theArray)[1]);

    if (((boolean)(arg1)) &&
        eqlP(arg1, arg2)) {
      return (selectTestResult(false, true, frame));
    }
    else {
      return (KWD_SPECIALISTS_FAILURE);
    }
  }
}

StringWrapper* objectNameComputation(Object* objectarg) {
  { const char* nameString = objectNameString(valueOf(objectarg));

    if (nameString == NULL) {
      return (NULL);
    }
    else {
      return (wrapString(nameString));
    }
  }
}

StringWrapper* objectPrintNameComputation(Object* objectarg) {
  { Symbol* namesymbol = logic::objectName(valueOf(objectarg));

    if (!((boolean)(namesymbol))) {
      return (NULL);
    }
    else {
      return (wrapString(namesymbol->relativeName(true)));
    }
  }
}

Object* nameToObjectComputation(Object* namearg) {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (!stringP(namearg)) {
      { Object* instance = getInstance(namearg);

        if (((boolean)(instance))) {
          return (instance);
        }
      }
    }
    { const char* nameargstring = pli::objectToString(namearg);
      Surrogate* instancename = lookupSurrogate(nameargstring);

      { Object* temp000 = getInstance(instancename);

        { Object* value000 = (((boolean)(temp000)) ? temp000 : createLogicInstance(internSurrogateInModule(nameargstring, oMODULEo, true), NULL));

          return (value000);
        }
      }
    }
  }
}

Object* printNameToObjectComputation(Object* namearg) {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (!stringP(namearg)) {
      { Object* instance = getInstance(namearg);

        if (((boolean)(instance))) {
          return (instance);
        }
      }
    }
    try {
      { const char* nameargstring = pli::objectToString(namearg);
        GeneralizedSymbol* instancename = internStellaName(nameargstring);

        { Object* temp000 = getInstance(instancename);

          { Object* value000 = (((boolean)(temp000)) ? temp000 : createLogicInstance(internSurrogateInModule(instancename->symbolName, ((Module*)(instancename->homeContext)), true), NULL));

            return (value000);
          }
        }
      }
    }
    catch (StellaException ) {
      return (NULL);
    }
  }
}

IntegerWrapper* arityComputation(Object* descriptionarg) {
  { Object* description = valueOf(descriptionarg);

    if (((boolean)(description))) {
      if (subtypeOfP(safePrimaryType(description), SGT_SPECIALISTS_LOGIC_DESCRIPTION)) {
        { Object* description000 = description;
          Description* description = ((Description*)(description000));

          return (wrapInteger(description->arity()));
        }
      }
      else {
        return (NULL);
      }
    }
    else {
      return (NULL);
    }
  }
}

Keyword* aritySpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* relationArg = (proposition->arguments->theArray)[0];
    Object* relationArgValue = argumentBoundTo(relationArg);
    Object* arityArg = (proposition->arguments->theArray)[1];
    Object* arityArgValue = argumentBoundTo(arityArg);
    IntegerWrapper* computedArity = arityComputation(relationArgValue);
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)));

    lastmove = lastmove;
    if (!((boolean)(iterator))) {
      if (!((boolean)(relationArgValue))) {
        iterator = allNamedDescriptions(oMODULEo, false);
        setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, iterator, NULL);
      }
      else if (!((boolean)(arityArgValue))) {
        return (selectProofResult(bindArgumentToValueP(arityArg, computedArity, true), false, true));
      }
      else {
        if (!((boolean)(computedArity))) {
          return (KWD_SPECIALISTS_FAILURE);
        }
        else {
          if (subtypeOfIntegerP(safePrimaryType(arityArgValue))) {
            { Object* arityArgValue000 = arityArgValue;
              IntegerWrapper* arityArgValue = ((IntegerWrapper*)(arityArgValue000));

              return (selectTestResult(eqlP(arityArgValue, computedArity), true, frame));
            }
          }
          else {
            return (selectTestResult(bindArgumentToValueP(arityArg, computedArity, true), true, frame));
          }
        }
      }
    }
    { NamedDescription* description = NULL;

      while (iterator->nextP()) {
        description = ((NamedDescription*)(iterator->value));
        computedArity = arityComputation(description);
        if (bindArgumentToValueP(arityArg, computedArity, true) &&
            bindArgumentToValueP(relationArg, description, true)) {
          return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
        }
      }
      return (KWD_SPECIALISTS_FAILURE);
    }
  }
}

Keyword* relationHierarchySpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    GeneralizedSymbol* relation = proposition->operatoR;
    Object* boundarg = (proposition->arguments->theArray)[0];
    Object* boundargvalue = argumentBoundTo(boundarg);
    Object* otherarg = (proposition->arguments->theArray)[1];
    Object* otherargvalue = argumentBoundTo(otherarg);
    boolean reflexiveP = false;
    Iterator* iterator = ((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)));
    Cons* collection = NIL;

    lastmove = lastmove;
    if (!((boolean)(boundargvalue))) {
      if (!((boolean)(otherargvalue))) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      else {
        boundarg = otherarg;
        boundargvalue = otherargvalue;
        otherarg = (proposition->arguments->theArray)[0];
        otherargvalue = NULL;
        if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_DIRECT_SUBRELATION) {
          relation = SGT_SPECIALISTS_PL_KERNEL_KB_DIRECT_SUPERRELATION;
        }
        else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_DIRECT_SUPERRELATION) {
          relation = SGT_SPECIALISTS_PL_KERNEL_KB_DIRECT_SUBRELATION;
        }
        else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_SUBRELATION) {
          relation = SGT_SPECIALISTS_PL_KERNEL_KB_SUPERRELATION;
        }
        else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_SUPERRELATION) {
          relation = SGT_SPECIALISTS_PL_KERNEL_KB_SUBRELATION;
        }
        else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_PROPER_SUBRELATION) {
          relation = SGT_SPECIALISTS_PL_KERNEL_KB_PROPER_SUPERRELATION;
        }
        else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_PROPER_SUPERRELATION) {
          relation = SGT_SPECIALISTS_PL_KERNEL_KB_PROPER_SUBRELATION;
        }
        else {
        }
      }
    }
    if (!isaP(boundargvalue, SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION)) {
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
    if (!((boolean)(iterator))) {
      if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_DIRECT_SUBRELATION) {
        collection = allDirectSubrelations(((NamedDescription*)(boundargvalue)), true);
      }
      else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_SUBRELATION) {
        reflexiveP = true;
        collection = allSubrelations(((NamedDescription*)(boundargvalue)), false);
      }
      else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_PROPER_SUBRELATION) {
        collection = allSubrelations(((NamedDescription*)(boundargvalue)), true);
      }
      else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_DIRECT_SUPERRELATION) {
        collection = allDirectSuperrelations(((NamedDescription*)(boundargvalue)), true);
      }
      else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_SUPERRELATION) {
        reflexiveP = true;
        collection = allSuperrelations(((NamedDescription*)(boundargvalue)), false);
      }
      else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_PROPER_SUPERRELATION) {
        collection = allSuperrelations(((NamedDescription*)(boundargvalue)), true);
      }
      else if (relation == SGT_SPECIALISTS_PL_KERNEL_KB_EQUIVALENT_RELATION) {
        collection = allEquivalentRelations(((NamedDescription*)(boundargvalue)), true);
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << relation << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      if (reflexiveP &&
          (!collection->membP(boundargvalue))) {
        collection = cons(boundargvalue, collection);
      }
    }
    if (((boolean)(otherargvalue))) {
      if (collection->membP(otherargvalue)) {
        return (KWD_SPECIALISTS_FINAL_SUCCESS);
      }
      else {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
    }
    if (!((boolean)(iterator))) {
      if (collection == NIL) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      iterator = collection->allocateIterator();
      setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, iterator, NULL);
    }
    if (iterator->nextP() &&
        bindArgumentToValueP(otherarg, iterator->value, true)) {
      return (KWD_SPECIALISTS_CONTINUING_SUCCESS);
    }
    else {
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

List* helpProjectNthColumn(int n, List* tuplelist) {
  if (!((boolean)(tuplelist))) {
    return (NULL);
  }
  { List* projectedlist = newList();
    Object* item = NULL;

    { Object* tuple = NULL;
      Cons* iter000 = tuplelist->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        tuple = iter000->value;
        { Surrogate* testValue000 = safePrimaryType(tuple);

          if (testValue000 == SGT_SPECIALISTS_STELLA_CONS) {
            { Object* tuple000 = tuple;
              Cons* tuple = ((Cons*)(tuple000));

              item = tuple->nth(n);
            }
          }
          else if (subtypeOfP(testValue000, SGT_SPECIALISTS_STELLA_LIST)) {
            { Object* tuple001 = tuple;
              List* tuple = ((List*)(tuple001));

              item = tuple->nth(n);
            }
          }
          else if (subtypeOfP(testValue000, SGT_SPECIALISTS_STELLA_COLLECTION)) {
            { Object* tuple002 = tuple;
              Collection* tuple = ((Collection*)(tuple002));

              { List* members = assertedCollectionMembers(tuple, false);

                if (((boolean)(members))) {
                  item = members->nth(n);
                }
                else {
                  continue;
                }
              }
            }
          }
          else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_SKOLEM)) {
            { Object* tuple003 = tuple;
              Skolem* tuple = ((Skolem*)(tuple003));

              { List* members = assertedCollectionMembers(tuple, false);

                if (((boolean)(members))) {
                  item = members->nth(n);
                }
                else {
                  continue;
                }
              }
            }
          }
          else {
            std::cout << "Can't handle tuple object " << "`" << tuple << "'" << std::endl << std::endl;
            continue;
          }
        }
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(item, NIL);
            if (projectedlist->theConsList == NIL) {
              projectedlist->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(projectedlist->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(item, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    if (projectedlist->emptyP()) {
      return (NULL);
    }
    else {
      return (projectedlist);
    }
  }
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* projectColumnSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Proposition* proposition = frame->proposition;
    Object* projectionarg = (proposition->arguments->theArray)[0];
    Object* projectionvalue = argumentBoundTo(projectionarg);
    Object* collectionarg = (proposition->arguments->theArray)[1];
    Object* collectionvalue = argumentBoundTo(collectionarg);
    int selector = NULL_INTEGER;
    Object* listarg = (proposition->arguments->theArray)[2];

    lastmove = lastmove;
    if ((!((boolean)(collectionvalue))) ||
        ((!((boolean)(projectionvalue))) ||
         (!isaP(projectionvalue, SGT_SPECIALISTS_STELLA_INTEGER_WRAPPER)))) {
      return (KWD_SPECIALISTS_TERMINAL_FAILURE);
    }
    selector = ((IntegerWrapper*)(projectionvalue))->wrapperValue;
    if (!((boolean)(((Iterator*)(dynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, NULL)))))) {
      { Surrogate* testValue000 = safePrimaryType(collectionvalue);

        if (subtypeOfP(testValue000, SGT_SPECIALISTS_STELLA_COLLECTION)) {
          { Object* collectionvalue000 = collectionvalue;
            stella::Collection* collectionvalue = ((stella::Collection*)(collectionvalue000));

            { stella::List* members = helpProjectNthColumn(selector, assertedCollectionMembers(collectionvalue, false));

              if (!((boolean)(members))) {
                return (KWD_SPECIALISTS_TERMINAL_FAILURE);
              }
              return (selectProofResult(bindArgumentToValueP(listarg, createLogicalList(members), true), false, true));
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_SKOLEM)) {
          { Object* collectionvalue001 = collectionvalue;
            Skolem* collectionvalue = ((Skolem*)(collectionvalue001));

            { stella::List* members = helpProjectNthColumn(selector, assertedCollectionMembers(collectionvalue, false));

              if (!((boolean)(members))) {
                return (KWD_SPECIALISTS_TERMINAL_FAILURE);
              }
              return (selectProofResult(bindArgumentToValueP(listarg, createLogicalList(members), true), false, true));
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_SPECIALISTS_LOGIC_DESCRIPTION)) {
          { Object* collectionvalue002 = collectionvalue;
            Description* collectionvalue = ((Description*)(collectionvalue002));

            { boolean testValue001 = false;

              testValue001 = ((boolean)(((Vector*)(dynamicSlotValue(collectionvalue->dynamicSlots, SYM_SPECIALISTS_LOGIC_EXTERNAL_VARIABLES, NULL)))));
              if (testValue001) {
                { boolean foundP000 = false;

                  { PatternVariable* v = NULL;
                    Vector* vector000 = ((Vector*)(dynamicSlotValue(collectionvalue->dynamicSlots, SYM_SPECIALISTS_LOGIC_EXTERNAL_VARIABLES, NULL)));
                    int index000 = 0;
                    int length000 = vector000->length();

                    for  (; index000 < length000; 
                          index000 = index000 + 1) {
                      v = ((PatternVariable*)((vector000->theArray)[index000]));
                      if (!((boolean)(argumentBoundTo(v)))) {
                        foundP000 = true;
                        break;
                      }
                    }
                  }
                  testValue001 = foundP000;
                }
              }
              if (testValue001) {
                return (KWD_SPECIALISTS_TERMINAL_FAILURE);
              }
            }
            if (inferableP(collectionvalue)) {
              {
                createCollectDescriptionExtensionFrame(frame, collectionvalue);
                setDynamicSlotValue(frame->dynamicSlots, SYM_SPECIALISTS_STELLA_ITERATOR, EMPTY_PROPOSITIONS_ITERATOR, NULL);
                return (KWD_SPECIALISTS_MOVE_DOWN);
              }
            }
            else {
              { stella::List* members = helpProjectNthColumn(selector, assertedCollectionMembers(collectionvalue, false));

                if (!((boolean)(members))) {
                  return (KWD_SPECIALISTS_TERMINAL_FAILURE);
                }
                return (selectProofResult(bindArgumentToValueP(listarg, createLogicalList(members), true), false, true));
              }
            }
          }
        }
        else {
          return (KWD_SPECIALISTS_FAILURE);
        }
      }
    }
    if (!((boolean)(frame->down))) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    { stella::List* list = helpProjectNthColumn(selector, frame->down->patternRecord->collectionList);

      popFramesUpTo(frame->down);
      if (!((boolean)(list))) {
        return (KWD_SPECIALISTS_TERMINAL_FAILURE);
      }
      return (selectProofResult(bindArgumentToValueP(listarg, createLogicalList(list), true), false, true));
    }
  }
}

void assertSynonymDemon(Proposition* self) {
  { Object* term = valueOf((self->arguments->theArray)[0]);
    Object* synonym = valueOf((self->arguments->theArray)[1]);
    Surrogate* synonymname = NULL;

    if ((!eqlP(term, synonym)) &&
        isaP(synonym, SGT_SPECIALISTS_LOGIC_LOGIC_OBJECT)) {
      synonymname = ((LogicObject*)(synonym))->surrogateValueInverse;
      synonymname->surrogateValue = term;
      assertTuple(SGT_SPECIALISTS_PL_KERNEL_KB_SYNONYM, consList(2, term, term));
    }
  }
}

void retractSynonymDemon(Proposition* self) {
  { Object* term = valueOf((self->arguments->theArray)[0]);
    Object* synonym = NULL;
    Surrogate* synonymname = NULL;

    { Proposition* prop = NULL;
      Iterator* iter000 = allTrueDependentPropositions(term, SGT_SPECIALISTS_PL_KERNEL_KB_SYNONYM, false);

      for (; iter000->nextP(); ) {
        prop = ((Proposition*)(iter000->value));
        synonym = valueOf((prop->arguments->theArray)[1]);
        if (isaP(synonym, SGT_SPECIALISTS_LOGIC_LOGIC_OBJECT)) {
          synonymname = ((LogicObject*)(synonym))->surrogateValueInverse;
          synonymname->surrogateValue = synonym;
        }
        { Proposition* object000 = prop;
          TruthValue* value000 = NULL;
          Object* oldValue000 = object000->truthValue;
          Object* newValue000 = updateInContext(oldValue000, value000, object000->homeContext, false);

          if (!(((boolean)(oldValue000)) &&
              (oldValue000->primaryType() == SGT_SPECIALISTS_STELLA_CS_VALUE))) {
            object000->truthValue = newValue000;
          }
        }
      }
    }
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

Cons* getSynonyms(Object* term) {
  { Object* termvalue = valueOf(term);
    Object* firstarg = NULL;
    Object* secondarg = NULL;
    Cons* synonyms = NIL;

    { Proposition* prop = NULL;
      Iterator* iter000 = allTrueDependentPropositions(term, SGT_SPECIALISTS_PL_KERNEL_KB_SYNONYM, false);

      for (; iter000->nextP(); ) {
        prop = ((Proposition*)(iter000->value));
        firstarg = valueOf((prop->arguments->theArray)[0]);
        secondarg = valueOf((prop->arguments->theArray)[1]);
        if (eqlP(firstarg, termvalue) &&
            ((!eqlP(firstarg, secondarg)) &&
             (!synonyms->membP(secondarg)))) {
          synonyms = cons(secondarg, synonyms);
        }
      }
    }
    return (synonyms);
  }
}

boolean synonymSurrogateP(Surrogate* name) {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, name->homeModule());
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    { Object* value = name->surrogateValue;
      Surrogate* valuename = objectSurrogate(value);

      { boolean testValue000 = false;

        testValue000 = ((boolean)(valuename));
        if (testValue000) {
          testValue000 = !(name == valuename);
          if (testValue000) {
            { boolean foundP000 = false;

              { LogicObject* synonym = NULL;
                Cons* iter000 = getSynonyms(value);

                for (; !(iter000 == NIL); iter000 = iter000->rest) {
                  synonym = ((LogicObject*)(iter000->value));
                  if (synonym->surrogateValueInverse == name) {
                    foundP000 = true;
                    break;
                  }
                }
              }
              testValue000 = foundP000;
            }
          }
        }
        { boolean value000 = testValue000;

          return (value000);
        }
      }
    }
  }
}

void transferSynonyms(Object* oldobject, Object* newobject) {
  { List* originatedprops = originatedPropositions(oldobject);

    { LogicObject* synonym = NULL;
      Cons* iter000 = getSynonyms(oldobject);

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        synonym = ((LogicObject*)(iter000->value));
        { boolean foundP000 = false;

          { Proposition* prop = NULL;
            Iterator* iter001 = allTrueDependentPropositions(synonym, SGT_SPECIALISTS_PL_KERNEL_KB_SYNONYM, false);

            for (; iter001->nextP(); ) {
              prop = ((Proposition*)(iter001->value));
              if (eqlP((prop->arguments->theArray)[0], oldobject) &&
                  (((prop->arguments->theArray)[1] == synonym) &&
                   (!originatedprops->membP(prop)))) {
                foundP000 = true;
                break;
              }
            }
          }
          if (foundP000) {
            objectSurrogate(synonym)->surrogateValue = newobject;
          }
          else {
            objectSurrogate(synonym)->surrogateValue = NULL;
          }
        }
      }
    }
  }
}


} // end of namespace logic


namespace pl_kernel_kb {
  using namespace stella;
  using namespace logic;

Keyword* differentSpecialist(ControlFrame* frame, Keyword* lastmove) {
  { Vector* arguments = frame->proposition->arguments;
    Cons* argumentvalues = NIL;
    boolean unboundargsP = false;
    Object* value = NULL;

    lastmove = lastmove;
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
            collect000 = cons(valueOf(argumentBoundTo(arg)), NIL);
            if (argumentvalues == NIL) {
              argumentvalues = collect000;
            }
            else {
              addConsToEndOfConsList(argumentvalues, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(valueOf(argumentBoundTo(arg)), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    while (!(argumentvalues == NIL)) {
      value = argumentvalues->value;
      if (!((boolean)(value))) {
        unboundargsP = true;
      }
      else {
        { boolean foundP000 = false;

          { Object* value2 = NULL;
            Cons* iter000 = argumentvalues->rest;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              value2 = iter000->value;
              if (eqlP(value, value2)) {
                foundP000 = true;
                break;
              }
            }
          }
          if (foundP000) {
            return (selectTestResult(false, true, frame));
          }
        }
      }
      argumentvalues = argumentvalues->rest;
    }
    if (unboundargsP) {
      return (KWD_SPECIALISTS_FAILURE);
    }
    else {
      return (selectTestResult(true, true, frame));
    }
  }
}

Object* equivalentTermsComputation(Object* term) {
  { Cons* equivs = cons(term, getAllEquivalentValues(term));

    equivs = equivs->sort(((cpp_function_code)(&logicFormLessP)));
    return (createLogicalList(equivs->listify()));
  }
}


} // end of namespace pl_kernel_kb


namespace logic {
  using namespace stella;

cpp_function_code lookupNativeSpecialist(const char* nativeName) {
  // Returns the native funtion code for `native-name' if it exists
  // and the underlying programming languages supports such lookups.  Uses the signature
  // of a specialist function.
  { cpp_function_code code = NULL;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Not implemented in " << "`" << runningInLanguage() << "'";
      throw *newStellaException(stream000->theStringReader());
    }
    if (code == NULL) {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "Couldn't locate native function for " << "`" << nativeName << "'";
        throw *newStellaException(stream001->theStringReader());
      }
    }
    return (code);
  }
}

void registerSpecialistFunction(const char* name, cpp_function_code code) {
  // Creates a registration entry for `name' as a specialist which
  // executes `code'.  Essentially just builds the Stella meta-information
  // tructure needed to funcall `name' as a specialist.  The function definition
  // in `code' needs to accept a CONTROL-FRAME and KEYWORD as arguments and
  // return a KEYWORD.  Side effects on elements of the proposition in the
  // control frame can be used to bind and thus return values.
  defineFunctionObject(stringConcatenate(" ", name, 0), stringConcatenate("(DEFUN (", name, 1, " KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))"), code, NULL);
}

void registerSpecialistFunctionName(const char* stellaName, const char* nativeName) {
  // registers a specialist function `stella-name' based on the `native-name'
  // for the particular programming language in question.  Use of this command makes
  // the resulting code or knowledge bases non-portable to other target languages.
  registerSpecialistFunction(stellaName, lookupNativeSpecialist(nativeName));
}

void registerSpecialistFunctionNameEvaluatorWrapper(Cons* arguments) {
  registerSpecialistFunctionName(((StringWrapper*)(arguments->value))->wrapperValue, ((StringWrapper*)(arguments->rest->value))->wrapperValue);
}

cpp_function_code lookupNativeComputation(const char* nativeName, int arity) {
  // Returns the native funtion code for `native-name' if it exists
  // and the underlying programming languages supports such lookups.  It is looked up
  // using the signature of a computation function supported by the computation specialist.
  { cpp_function_code code = NULL;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Not implemented in " << "`" << runningInLanguage() << "'";
      throw *newStellaException(stream000->theStringReader());
    }
    if (code == NULL) {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "Couldn't locate native function for " << "`" << nativeName << "'";
        throw *newStellaException(stream001->theStringReader());
      }
    }
    return (code);
  }
}

void registerComputationFunction(const char* name, cpp_function_code code, int arity) {
  // Creates a registration entry for `name' as a computation which
  // executes `code'.  Essentially just builds the Stella meta-information
  // tructure needed to funcall `name' as a computation function by the
  // computation specialist.  The function definition in `code' needs to
  // accept ARITY Stella OBJECTs as arguments and return a Stella OBJECT 
  // suitable for PowerLoom use.  (These are generally LOGIC-OBJECTs and the
  // literal wrappers FLOAT-WRAPPER, INTEGER-WRAPPER and STRING-WRAPPER.)
  { const char* definitionString = "(DEFUN (";

    definitionString = stringConcatenate(definitionString, name, 1, " OBJECT) (");
    { int i = NULL_INTEGER;
      int iter000 = 1;
      int upperBound000 = arity;
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter000 <= upperBound000); 
            iter000 = iter000 + 1) {
        i = iter000;
        definitionString = stringConcatenate(definitionString, "(X", 2, integerToString(((long long int)(i))), " OBJECT) ");
      }
    }
    definitionString = stringConcatenate(definitionString, "))", 0);
    defineFunctionObject(stringConcatenate(" ", name, 0), definitionString, code, NULL);
  }
}

void registerComputationFunctionName(const char* stellaName, const char* nativeName, int arity) {
  // registers a computation function `stella-name' based on the `native-name'
  // for the particular programming language in question.  Use of this command makes
  // the resulting code or knowledge bases non-portable to other target languages.
  registerComputationFunction(stellaName, lookupNativeComputation(nativeName, arity), arity);
}

void registerComputationFunctionNameEvaluatorWrapper(Cons* arguments) {
  registerComputationFunctionName(((StringWrapper*)(arguments->value))->wrapperValue, ((StringWrapper*)(arguments->rest->value))->wrapperValue, ((IntegerWrapper*)(arguments->rest->rest->value))->wrapperValue);
}

void helpStartupSpecialists1() {
  {
    SGT_SPECIALISTS_LOGIC_COMPUTED_PROCEDURE = ((Surrogate*)(internRigidSymbolWrtModule("COMPUTED-PROCEDURE", NULL, 1)));
    SYM_SPECIALISTS_LOGIC_PROCEDURE_NAME = ((Symbol*)(internRigidSymbolWrtModule("PROCEDURE-NAME", NULL, 0)));
    SYM_SPECIALISTS_LOGIC_PROCEDURE_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("PROCEDURE-FUNCTION", NULL, 0)));
    KWD_SPECIALISTS_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    KWD_SPECIALISTS_RELEASE = ((Keyword*)(internRigidSymbolWrtModule("RELEASE", NULL, 2)));
    SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_SPECIALIST = ((Surrogate*)(internRigidSymbolWrtModule("RELATION-SPECIALIST", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_HANDLES_REVERSE_POLARITY = ((Surrogate*)(internRigidSymbolWrtModule("HANDLES-REVERSE-POLARITY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_CONSTRAINT = ((Surrogate*)(internRigidSymbolWrtModule("RELATION-CONSTRAINT", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_COMPUTATION = ((Surrogate*)(internRigidSymbolWrtModule("RELATION-COMPUTATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_EVALUATOR = ((Surrogate*)(internRigidSymbolWrtModule("RELATION-EVALUATOR", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_SPECIALISTS_CONTINUING_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("CONTINUING-SUCCESS", NULL, 2)));
    KWD_SPECIALISTS_FINAL_SUCCESS = ((Keyword*)(internRigidSymbolWrtModule("FINAL-SUCCESS", NULL, 2)));
    KWD_SPECIALISTS_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("FAILURE", NULL, 2)));
    KWD_SPECIALISTS_TERMINAL_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("TERMINAL-FAILURE", NULL, 2)));
    KWD_SPECIALISTS_FAIL = ((Keyword*)(internRigidSymbolWrtModule("FAIL", NULL, 2)));
    KWD_SPECIALISTS_TRUE = ((Keyword*)(internRigidSymbolWrtModule("TRUE", NULL, 2)));
    SGT_SPECIALISTS_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
    SGT_SPECIALISTS_STELLA_FUNCTION_CODE_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("FUNCTION-CODE-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_SPECIALISTS_STELLA_METHOD_CODE_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("METHOD-CODE-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_SPECIALISTS_LOGIC_SUBSTRING_POSITION_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("SUBSTRING-POSITION-ITERATOR", NULL, 1)));
    SYM_SPECIALISTS_LOGIC_SUPER_STRING = ((Symbol*)(internRigidSymbolWrtModule("SUPER-STRING", NULL, 0)));
    SYM_SPECIALISTS_LOGIC_SUB_STRING = ((Symbol*)(internRigidSymbolWrtModule("SUB-STRING", NULL, 0)));
    SYM_SPECIALISTS_STELLA_START = ((Symbol*)(internRigidSymbolWrtModule("START", getStellaModule("/STELLA", true), 0)));
    SYM_SPECIALISTS_LOGIC_SUB_LENGTH = ((Symbol*)(internRigidSymbolWrtModule("SUB-LENGTH", NULL, 0)));
    SGT_SPECIALISTS_PL_KERNEL_KB_TOTAL = ((Surrogate*)(internRigidSymbolWrtModule("TOTAL", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    SGT_SPECIALISTS_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", getStellaModule("/STELLA", true), 1)));
    SYM_SPECIALISTS_STELLA_ITERATOR = ((Symbol*)(internRigidSymbolWrtModule("ITERATOR", getStellaModule("/STELLA", true), 0)));
    SGT_SPECIALISTS_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_COLLECTIONOF = ((Surrogate*)(internRigidSymbolWrtModule("COLLECTIONOF", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_SPECIALISTS_UP_TRUE = ((Keyword*)(internRigidSymbolWrtModule("UP-TRUE", NULL, 2)));
    KWD_SPECIALISTS_UP_FAIL = ((Keyword*)(internRigidSymbolWrtModule("UP-FAIL", NULL, 2)));
    SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
    SYM_SPECIALISTS_STELLA_ISA = ((Symbol*)(internRigidSymbolWrtModule("ISA", getStellaModule("/STELLA", true), 0)));
    KWD_SPECIALISTS_MOVE_DOWN = ((Keyword*)(internRigidSymbolWrtModule("MOVE-DOWN", NULL, 2)));
    SGT_SPECIALISTS_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
    SYM_SPECIALISTS_LOGIC_EXTERNAL_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("EXTERNAL-VARIABLES", NULL, 0)));
    SGT_SPECIALISTS_STELLA_COLLECTION = ((Surrogate*)(internRigidSymbolWrtModule("COLLECTION", getStellaModule("/STELLA", true), 1)));
    SGT_SPECIALISTS_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
    KWD_SPECIALISTS_SCAN_COLLECTION = ((Keyword*)(internRigidSymbolWrtModule("SCAN-COLLECTION", NULL, 2)));
    SGT_SPECIALISTS_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    KWD_SPECIALISTS_DOWN = ((Keyword*)(internRigidSymbolWrtModule("DOWN", NULL, 2)));
    SYM_SPECIALISTS_STELLA_PREDICATE = ((Symbol*)(internRigidSymbolWrtModule("PREDICATE", getStellaModule("/STELLA", true), 0)));
    SYM_SPECIALISTS_STELLA_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("FUNCTION", getStellaModule("/STELLA", true), 0)));
    SYM_SPECIALISTS_STELLA_DUMMY = ((Symbol*)(internRigidSymbolWrtModule("DUMMY", getStellaModule("/STELLA", true), 0)));
    KWD_SPECIALISTS_FULL_SUBQUERY = ((Keyword*)(internRigidSymbolWrtModule("FULL-SUBQUERY", NULL, 2)));
    SYM_SPECIALISTS_LOGIC_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 0)));
    KWD_SPECIALISTS_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    KWD_SPECIALISTS_PREDICATE = ((Keyword*)(internRigidSymbolWrtModule("PREDICATE", NULL, 2)));
    KWD_SPECIALISTS_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    SGT_SPECIALISTS_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", NULL, 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_HOLDS = ((Surrogate*)(internRigidSymbolWrtModule("HOLDS", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_SPECIALISTS_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    SYM_SPECIALISTS_STELLA_ARGUMENTS = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENTS", getStellaModule("/STELLA", true), 0)));
    SGT_SPECIALISTS_LOGIC_FORK_PROOF_ADJUNCT = ((Surrogate*)(internRigidSymbolWrtModule("FORK-PROOF-ADJUNCT", NULL, 1)));
    SYM_SPECIALISTS_LOGIC_CONDITION_JUSTIFICATION = ((Symbol*)(internRigidSymbolWrtModule("CONDITION-JUSTIFICATION", NULL, 0)));
    SYM_SPECIALISTS_LOGIC_DOWN_FRAME = ((Symbol*)(internRigidSymbolWrtModule("DOWN-FRAME", NULL, 0)));
    SYM_SPECIALISTS_LOGIC_PROOF_ADJUNCT = ((Symbol*)(internRigidSymbolWrtModule("PROOF-ADJUNCT", NULL, 0)));
    KWD_SPECIALISTS_FAIL_INTRODUCTION = ((Keyword*)(internRigidSymbolWrtModule("FAIL-INTRODUCTION", NULL, 2)));
    KWD_SPECIALISTS_FORK_ELSE = ((Keyword*)(internRigidSymbolWrtModule("FORK-ELSE", NULL, 2)));
  }
}

void helpStartupSpecialists2() {
  {
    KWD_SPECIALISTS_FORK_THEN = ((Keyword*)(internRigidSymbolWrtModule("FORK-THEN", NULL, 2)));
    SYM_SPECIALISTS_LOGIC_JUSTIFICATION = ((Symbol*)(internRigidSymbolWrtModule("JUSTIFICATION", NULL, 0)));
    KWD_SPECIALISTS_TECHNICAL = ((Keyword*)(internRigidSymbolWrtModule("TECHNICAL", NULL, 2)));
    KWD_SPECIALISTS_LAY = ((Keyword*)(internRigidSymbolWrtModule("LAY", NULL, 2)));
    KWD_SPECIALISTS_HOW_MANY = ((Keyword*)(internRigidSymbolWrtModule("HOW-MANY", NULL, 2)));
    KWD_SPECIALISTS_INHERIT = ((Keyword*)(internRigidSymbolWrtModule("INHERIT", NULL, 2)));
    KWD_SPECIALISTS_ALL = ((Keyword*)(internRigidSymbolWrtModule("ALL", NULL, 2)));
    KWD_SPECIALISTS_CURRENT = ((Keyword*)(internRigidSymbolWrtModule("CURRENT", NULL, 2)));
    SYM_SPECIALISTS_LOGIC_QUERY_SPECIALIST_IO_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("QUERY-SPECIALIST-IO-VARIABLES", NULL, 0)));
    KWD_SPECIALISTS_MATCH_MODE = ((Keyword*)(internRigidSymbolWrtModule("MATCH-MODE", NULL, 2)));
    KWD_SPECIALISTS_DESCRIPTION = ((Keyword*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 2)));
    KWD_SPECIALISTS_SORT_BY = ((Keyword*)(internRigidSymbolWrtModule("SORT-BY", NULL, 2)));
    KWD_SPECIALISTS_GOAL_TREE = ((Keyword*)(internRigidSymbolWrtModule("GOAL-TREE", NULL, 2)));
    SGT_SPECIALISTS_LOGIC_SAVED_INFERENCE_LEVEL_PROOF_ADJUNCT = ((Surrogate*)(internRigidSymbolWrtModule("SAVED-INFERENCE-LEVEL-PROOF-ADJUNCT", NULL, 1)));
    SYM_SPECIALISTS_LOGIC_SAVED_INFERENCE_LEVEL = ((Symbol*)(internRigidSymbolWrtModule("SAVED-INFERENCE-LEVEL", NULL, 0)));
    SYM_SPECIALISTS_LOGIC_INFERENCE_LEVEL = ((Symbol*)(internRigidSymbolWrtModule("INFERENCE-LEVEL", NULL, 0)));
    SGT_SPECIALISTS_PL_KERNEL_KB_ASSERTION_QUERY = ((Surrogate*)(internRigidSymbolWrtModule("ASSERTION-QUERY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_SHALLOW_QUERY = ((Surrogate*)(internRigidSymbolWrtModule("SHALLOW-QUERY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_SUBSUMPTION_QUERY = ((Surrogate*)(internRigidSymbolWrtModule("SUBSUMPTION-QUERY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_BACKTRACKING_QUERY = ((Surrogate*)(internRigidSymbolWrtModule("BACKTRACKING-QUERY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_NORMAL_QUERY = ((Surrogate*)(internRigidSymbolWrtModule("NORMAL-QUERY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_REFUTATION_QUERY = ((Surrogate*)(internRigidSymbolWrtModule("REFUTATION-QUERY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_SPECIALISTS_LEVELED_QUERY = ((Keyword*)(internRigidSymbolWrtModule("LEVELED-QUERY", NULL, 2)));
    SGT_SPECIALISTS_PL_KERNEL_KB_CONCEPT_PROTOTYPE = ((Surrogate*)(internRigidSymbolWrtModule("CONCEPT-PROTOTYPE", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_SPECIALISTS_LOGIC_HYPOTHESIZED_INSTANCEp = ((Symbol*)(internRigidSymbolWrtModule("HYPOTHESIZED-INSTANCE?", NULL, 0)));
    SGT_SPECIALISTS_PL_KERNEL_KB_CLOSED = ((Surrogate*)(internRigidSymbolWrtModule("CLOSED", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_LOGIC_F_CLOSED_TERMp_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-CLOSED-TERM?-MEMO-TABLE-000", NULL, 1)));
    SYM_SPECIALISTS_LOGIC_EQUIVALENT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("EQUIVALENT-VALUE", NULL, 0)));
    SGT_SPECIALISTS_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", NULL, 1)));
    SGT_SPECIALISTS_LOGIC_F_CLOSED_PROPOSITIONp_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-CLOSED-PROPOSITION?-MEMO-TABLE-000", NULL, 1)));
    KWD_SPECIALISTS_OR = ((Keyword*)(internRigidSymbolWrtModule("OR", NULL, 2)));
    KWD_SPECIALISTS_NOT = ((Keyword*)(internRigidSymbolWrtModule("NOT", NULL, 2)));
    KWD_SPECIALISTS_FORALL = ((Keyword*)(internRigidSymbolWrtModule("FORALL", NULL, 2)));
    KWD_SPECIALISTS_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("EXISTS", NULL, 2)));
    SGT_SPECIALISTS_PL_KERNEL_KB_MEMBER_OF = ((Surrogate*)(internRigidSymbolWrtModule("MEMBER-OF", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_SINGLE_VALUED = ((Surrogate*)(internRigidSymbolWrtModule("SINGLE-VALUED", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_LOGIC_F_SINGLE_VALUED_TERMp_MEMO_TABLE_000 = ((Surrogate*)(internRigidSymbolWrtModule("F-SINGLE-VALUED-TERM?-MEMO-TABLE-000", NULL, 1)));
    KWD_SPECIALISTS_EQUIVALENT = ((Keyword*)(internRigidSymbolWrtModule("EQUIVALENT", NULL, 2)));
    SGT_SPECIALISTS_PL_KERNEL_KB_COLLECT_INTO_LIST = ((Surrogate*)(internRigidSymbolWrtModule("COLLECT-INTO-LIST", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_COLLECT_INTO_ORDERED_SET = ((Surrogate*)(internRigidSymbolWrtModule("COLLECT-INTO-ORDERED-SET", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_COUNT_MEMBERS = ((Surrogate*)(internRigidSymbolWrtModule("COUNT-MEMBERS", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_SPECIALISTS_LOGIC_INFERENCE_CUTOFF_REASON = ((Symbol*)(internRigidSymbolWrtModule("INFERENCE-CUTOFF-REASON", NULL, 0)));
    KWD_SPECIALISTS_COLLECT_MEMBERS = ((Keyword*)(internRigidSymbolWrtModule("COLLECT-MEMBERS", NULL, 2)));
    SYM_SPECIALISTS_LOGIC_pSUPER = ((Symbol*)(internRigidSymbolWrtModule("?SUPER", NULL, 0)));
    SYM_SPECIALISTS_LOGIC_pMDC = ((Symbol*)(internRigidSymbolWrtModule("?MDC", NULL, 0)));
    SYM_SPECIALISTS_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    SYM_SPECIALISTS_LOGIC_MEMBER_OF = ((Symbol*)(internRigidSymbolWrtModule("MEMBER-OF", NULL, 0)));
    SYM_SPECIALISTS_LOGIC_MUTUALLY_DISJOINT_COLLECTION = ((Symbol*)(internRigidSymbolWrtModule("MUTUALLY-DISJOINT-COLLECTION", NULL, 0)));
    SYM_SPECIALISTS_LOGIC_F_HELP_DERIVE_PARTITION_MEMBERSHIPS_QUERY_000 = ((Symbol*)(internRigidSymbolWrtModule("F-HELP-DERIVE-PARTITION-MEMBERSHIPS-QUERY-000", NULL, 0)));
    SGT_SPECIALISTS_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION = ((Surrogate*)(internRigidSymbolWrtModule("MUTUALLY-DISJOINT-COLLECTION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_PARTITION_MEMBERSHIP = ((Surrogate*)(internRigidSymbolWrtModule("PARTITION-MEMBERSHIP", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_DISJOINT = ((Surrogate*)(internRigidSymbolWrtModule("DISJOINT", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_HAS_PARTITION_MEMBERSHIP = ((Surrogate*)(internRigidSymbolWrtModule("HAS-PARTITION-MEMBERSHIP", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_SPECIALISTS_ASSERT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("ASSERT-TRUE", NULL, 2)));
    KWD_SPECIALISTS_ASSERT_FALSE = ((Keyword*)(internRigidSymbolWrtModule("ASSERT-FALSE", NULL, 2)));
    SGT_SPECIALISTS_PL_KERNEL_KB_EMPTY = ((Surrogate*)(internRigidSymbolWrtModule("EMPTY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_LOGIC_SAVED_CONTEXT_PROOF_ADJUNCT = ((Surrogate*)(internRigidSymbolWrtModule("SAVED-CONTEXT-PROOF-ADJUNCT", NULL, 1)));
    SYM_SPECIALISTS_LOGIC_SAVED_CONTEXT = ((Symbol*)(internRigidSymbolWrtModule("SAVED-CONTEXT", NULL, 0)));
    SGT_SPECIALISTS_STELLA_CONTEXT = ((Surrogate*)(internRigidSymbolWrtModule("CONTEXT", getStellaModule("/STELLA", true), 1)));
    KWD_SPECIALISTS_JUST_IN_TIME = ((Keyword*)(internRigidSymbolWrtModule("JUST-IN-TIME", NULL, 2)));
  }
}

void helpStartupSpecialists3() {
  {
    KWD_SPECIALISTS_IST_INTRODUCTION = ((Keyword*)(internRigidSymbolWrtModule("IST-INTRODUCTION", NULL, 2)));
    KWD_SPECIALISTS_PARTIAL = ((Keyword*)(internRigidSymbolWrtModule("PARTIAL", NULL, 2)));
    SGT_SPECIALISTS_PL_KERNEL_KB_THE_ROLESET = ((Surrogate*)(internRigidSymbolWrtModule("THE-ROLESET", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_CARDINALITY = ((Surrogate*)(internRigidSymbolWrtModule("CARDINALITY", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_SPECIALISTS_LOWER = ((Keyword*)(internRigidSymbolWrtModule("LOWER", NULL, 2)));
    KWD_SPECIALISTS_UPPER = ((Keyword*)(internRigidSymbolWrtModule("UPPER", NULL, 2)));
    SGT_SPECIALISTS_STELLA_INTEGER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("INTEGER-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SGT_SPECIALISTS_STELLA_SURROGATE = ((Surrogate*)(internRigidSymbolWrtModule("SURROGATE", getStellaModule("/STELLA", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_DIRECT_SUBRELATION = ((Surrogate*)(internRigidSymbolWrtModule("DIRECT-SUBRELATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_DIRECT_SUPERRELATION = ((Surrogate*)(internRigidSymbolWrtModule("DIRECT-SUPERRELATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_SUBRELATION = ((Surrogate*)(internRigidSymbolWrtModule("SUBRELATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_SUPERRELATION = ((Surrogate*)(internRigidSymbolWrtModule("SUPERRELATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_PROPER_SUBRELATION = ((Surrogate*)(internRigidSymbolWrtModule("PROPER-SUBRELATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_PROPER_SUPERRELATION = ((Surrogate*)(internRigidSymbolWrtModule("PROPER-SUPERRELATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_EQUIVALENT_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("EQUIVALENT-RELATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_STELLA_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", getStellaModule("/STELLA", true), 1)));
    SGT_SPECIALISTS_PL_KERNEL_KB_SYNONYM = ((Surrogate*)(internRigidSymbolWrtModule("SYNONYM", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_SPECIALISTS_STELLA_CS_VALUE = ((Surrogate*)(internRigidSymbolWrtModule("CS-VALUE", getStellaModule("/STELLA", true), 1)));
    SYM_SPECIALISTS_LOGIC_STARTUP_SPECIALISTS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-SPECIALISTS", NULL, 0)));
    SYM_SPECIALISTS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupSpecialists4() {
  {
    defineFunctionObject("STELLA-FUNCTION-FROM-PROCEDURE", "(DEFUN (STELLA-FUNCTION-FROM-PROCEDURE FUNCTION) ((PROCEDURE /PL-KERNEL-KB/COMPUTED-PROCEDURE)))", ((cpp_function_code)(&stellaFunctionFromProcedure)), NULL);
    defineFunctionObject("FUNCTION-CODE-FROM-PROCEDURE", "(DEFUN (FUNCTION-CODE-FROM-PROCEDURE FUNCTION-CODE) ((PROCEDURE /PL-KERNEL-KB/COMPUTED-PROCEDURE)))", ((cpp_function_code)(((cpp_function_code  (*) (ComputedProcedure*))(&functionCodeFromProcedure)))), NULL);
    defineFunctionObject("LOOKUP-SPECIALIST", "(DEFUN (LOOKUP-SPECIALIST FUNCTION-CODE) ((DESCRIPTION NAMED-DESCRIPTION)))", ((cpp_function_code)(&lookupSpecialist)), NULL);
    defineFunctionObject("LOOKUP-CONSTRAINT-FUNCTION", "(DEFUN (LOOKUP-CONSTRAINT-FUNCTION FUNCTION) ((DESCRIPTION NAMED-DESCRIPTION)))", ((cpp_function_code)(&lookupConstraintFunction)), NULL);
    defineFunctionObject("LOOKUP-CONSTRAINT", "(DEFUN (LOOKUP-CONSTRAINT FUNCTION-CODE) ((DESCRIPTION NAMED-DESCRIPTION)))", ((cpp_function_code)(&lookupConstraint)), NULL);
    defineFunctionObject("LOOKUP-COMPUTATION-FUNCTION", "(DEFUN (LOOKUP-COMPUTATION-FUNCTION FUNCTION) ((DESCRIPTION NAMED-DESCRIPTION)))", ((cpp_function_code)(&lookupComputationFunction)), NULL);
    defineFunctionObject("LOOKUP-COMPUTATION", "(DEFUN (LOOKUP-COMPUTATION FUNCTION-CODE) ((DESCRIPTION NAMED-DESCRIPTION)))", ((cpp_function_code)(&lookupComputation)), NULL);
    defineFunctionObject("LOOKUP-EVALUATOR-FUNCTION", "(DEFUN (LOOKUP-EVALUATOR-FUNCTION FUNCTION) ((DESCRIPTION NAMED-DESCRIPTION)))", ((cpp_function_code)(&lookupEvaluatorFunction)), NULL);
    defineFunctionObject("LOOKUP-EVALUATOR", "(DEFUN (LOOKUP-EVALUATOR FUNCTION-CODE) ((DESCRIPTION NAMED-DESCRIPTION)))", ((cpp_function_code)(&lookupEvaluator)), NULL);
    defineFunctionObject("SUCCESS-RESULT?", "(DEFUN (SUCCESS-RESULT? BOOLEAN) ((RESULT KEYWORD)) :GLOBALLY-INLINE? TRUE (RETURN (OR (EQL? RESULT :CONTINUING-SUCCESS) (EQL? RESULT :FINAL-SUCCESS))))", ((cpp_function_code)(&successResultP)), NULL);
    defineFunctionObject("FAILURE-RESULT?", "(DEFUN (FAILURE-RESULT? BOOLEAN) ((RESULT KEYWORD)) :GLOBALLY-INLINE? TRUE (RETURN (OR (EQL? RESULT :FAILURE) (EQL? RESULT :TERMINAL-FAILURE))))", ((cpp_function_code)(&failureResultP)), NULL);
    defineFunctionObject("CONTINUING-RESULT?", "(DEFUN (CONTINUING-RESULT? BOOLEAN) ((RESULT KEYWORD)) :GLOBALLY-INLINE? TRUE (RETURN (OR (EQL? RESULT :CONTINUING-SUCCESS) (EQL? RESULT :FAILURE))))", ((cpp_function_code)(&continuingResultP)), NULL);
    defineFunctionObject("FINAL-RESULT?", "(DEFUN (FINAL-RESULT? BOOLEAN) ((RESULT KEYWORD)) :GLOBALLY-INLINE? TRUE (RETURN (OR (EQL? RESULT :FINAL-SUCCESS) (EQL? RESULT :TERMINAL-FAILURE))))", ((cpp_function_code)(&finalResultP)), NULL);
    defineFunctionObject("SELECT-TEST-RESULT", "(DEFUN (SELECT-TEST-RESULT KEYWORD) ((SUCCESS? BOOLEAN) (TERMINAL? BOOLEAN) (FRAME CONTROL-FRAME)) :PUBLIC? TRUE :DOCUMENTATION \"Helping function for specialists testing the validity of a\nfully bound inference frame.  Based on the test result `success?'\nand `reversePolarity?*', set the truth value of `frame' and return\nan appropriate keyword.  The keyword will be either `:final-success'\n`:terminal-failure' if `terminal?' is true.  Otherwise it will be\n`:final-success' or `:failure'.\")", ((cpp_function_code)(&selectTestResult)), NULL);
    defineFunctionObject("SELECT-PROOF-RESULT", "(DEFUN (SELECT-PROOF-RESULT KEYWORD) ((SUCCESS? BOOLEAN) (CONTINUING? BOOLEAN) (TERMINAL? BOOLEAN)) :PUBLIC? TRUE :DOCUMENTATION \"Helping function for specialists.   Return the appropriate\nkeyword indicating success or failure of a proof.\")", ((cpp_function_code)(&selectProofResult)), NULL);
    defineFunctionObject("NULL-WRAPPER?", "(DEFUN (NULL-WRAPPER? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&nullWrapperP)), NULL);
    defineFunctionObject("NATIVE-SLOT-READER-SPECIALIST", "(DEFUN (NATIVE-SLOT-READER-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&nativeSlotReaderSpecialist)), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((IT SUBSTRING-POSITION-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&SubstringPositionIterator::nextP))), NULL);
    defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((IT SUBSTRING-POSITION-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&SubstringPositionIterator::length))), NULL);
    defineFunctionObject("BOUND-COMPUTATION-INPUT-SKOLEM?", "(DEFUN (BOUND-COMPUTATION-INPUT-SKOLEM? BOOLEAN) ((SKOLEM SKOLEM)))", ((cpp_function_code)(&boundComputationInputSkolemP)), NULL);
    defineFunctionObject("ARGUMENT-TARGET-TYPE", "(DEFUN (ARGUMENT-TARGET-TYPE TYPE) ((PARAMETERTYPES (LIST OF TYPE-SPEC)) (NINPUTTYPES INTEGER) (ARGINDEX INTEGER)))", ((cpp_function_code)(&argumentTargetType)), NULL);
    defineFunctionObject("COMPUTE-RELATION-VALUE", "(DEFUN (COMPUTE-RELATION-VALUE OBJECT) ((PROPOSITION PROPOSITION) (COMPUTATION FUNCTION) (ERROR? BOOLEAN)))", ((cpp_function_code)(&computeRelationValue)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/COMPUTATION-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/COMPUTATION-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::computationSpecialist)), NULL);
    defineFunctionObject("COMPUTE-SIMPLE-RELATION-CONSTRAINT", "(DEFUN (COMPUTE-SIMPLE-RELATION-CONSTRAINT OBJECT INTEGER) ((PROPOSITION PROPOSITION) (COMPUTATION FUNCTION) (ERROR? BOOLEAN)))", ((cpp_function_code)(&computeSimpleRelationConstraint)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/CONSTRAINT-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/CONSTRAINT-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::constraintSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/SQUARE-ROOT-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/SQUARE-ROOT-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::squareRootSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/ABSOLUTE-VALUE-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/ABSOLUTE-VALUE-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::absoluteValueSpecialist)), NULL);
    defineFunctionObject("ENUMERATIONS-CONTAINING-MEMBER", "(DEFUN (ENUMERATIONS-CONTAINING-MEMBER LIST) ((SELF OBJECT)))", ((cpp_function_code)(&enumerationsContainingMember)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/MEMBER-OF-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/MEMBER-OF-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::memberOfSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/MEMBER-OF-EVALUATOR", "(DEFUN /PL-KERNEL-KB/MEMBER-OF-EVALUATOR ((SELF PROPOSITION)))", ((cpp_function_code)(&pl_kernel_kb::memberOfEvaluator)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/INSTANCE-OF-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/INSTANCE-OF-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::instanceOfSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/BUGGY-DIRECT-INSTANCE-OF-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/BUGGY-DIRECT-INSTANCE-OF-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::buggyDirectInstanceOfSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/DIRECT-INSTANCE-OF-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/DIRECT-INSTANCE-OF-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::directInstanceOfSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/ASSERTED-INSTANCE-OF-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/ASSERTED-INSTANCE-OF-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::assertedInstanceOfSpecialist)), NULL);
    defineFunctionObject("TEST-DISJOINT-TERMS?", "(DEFUN (TEST-DISJOINT-TERMS? BOOLEAN) ((TERM1 OBJECT) (TERM2 OBJECT)))", ((cpp_function_code)(&testDisjointTermsP)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/SUBSET-OF-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/SUBSET-OF-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::subsetOfSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/HOLDS-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/HOLDS-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::holdsSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/TOTAL-VALUE-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/TOTAL-VALUE-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::totalValueSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/THAT-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/THAT-COMPUTATION OBJECT) ((P OBJECT)))", ((cpp_function_code)(&pl_kernel_kb::thatComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/PROPOSITION-RELATION-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/PROPOSITION-RELATION-COMPUTATION OBJECT) ((P OBJECT)))", ((cpp_function_code)(&pl_kernel_kb::propositionRelationComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/PROPOSITION-ARGUMENT-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/PROPOSITION-ARGUMENT-COMPUTATION OBJECT) ((P OBJECT) (I INTEGER-WRAPPER)))", ((cpp_function_code)(&pl_kernel_kb::propositionArgumentComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/PROPOSITION-ARGUMENTS-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/PROPOSITION-ARGUMENTS-COMPUTATION SKOLEM) ((P OBJECT)))", ((cpp_function_code)(&pl_kernel_kb::propositionArgumentsComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/PROPOSITION-ARITY-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/PROPOSITION-ARITY-COMPUTATION INTEGER-WRAPPER) ((P OBJECT)))", ((cpp_function_code)(&pl_kernel_kb::propositionArityComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/CONCEIVED-PROPOSITION-TERM-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/CONCEIVED-PROPOSITION-TERM-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::conceivedPropositionTermSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/CUT-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/CUT-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::cutSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/BOUND-VARIABLES-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/BOUND-VARIABLES-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::boundVariablesSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/FORK-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/FORK-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::forkSpecialist)), NULL);
    defineFunctionObject("COMPUTE-SUBQUERY-OPTIONS", "(DEFUN (COMPUTE-SUBQUERY-OPTIONS PROPOSITION PROPERTY-LIST) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&computeSubqueryOptions)), NULL);
    defineExternalSlotFromStringifiedSource("(DEFSLOT CONTROL-FRAME QUERY-SPECIALIST-IO-VARIABLES :TYPE LIST :ALLOCATION :DYNAMIC)");
    defineFunctionObject("CREATE-QUERY-SPECIALIST-ITERATOR", "(DEFUN (CREATE-QUERY-SPECIALIST-ITERATOR QUERY-ITERATOR BOOLEAN BOOLEAN) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&createQuerySpecialistIterator)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/QUERY-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/QUERY-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::querySpecialist)), NULL);
    defineFunctionObject("LEVELED-QUERY-RELATION-TO-INFERENCE-LEVEL", "(DEFUN (LEVELED-QUERY-RELATION-TO-INFERENCE-LEVEL INFERENCE-LEVEL) ((RELATION SURROGATE)))", ((cpp_function_code)(&leveledQueryRelationToInferenceLevel)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/LEVELED-QUERY-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/LEVELED-QUERY-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::leveledQuerySpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/CONCEPT-PROTOTYPE-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/CONCEPT-PROTOTYPE-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::conceptPrototypeSpecialist)), NULL);
    defineFunctionObject("CONCEPT-PROTOTYPE-OF", "(DEFUN (CONCEPT-PROTOTYPE-OF NAMED-DESCRIPTION) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&conceptPrototypeOf)), NULL);
    defineFunctionObject("CONCEPT-PROTOTYPE?", "(DEFUN (CONCEPT-PROTOTYPE? BOOLEAN) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&conceptPrototypeP)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/CLOSED-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/CLOSED-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::closedSpecialist)), NULL);
    defineFunctionObject("CLOSED-BY-ASSERTION?", "(DEFUN (CLOSED-BY-ASSERTION? BOOLEAN) ((SELF OBJECT)) :GLOBALLY-INLINE? TRUE (RETURN (AND (TEST-PROPERTY? SELF /PL-KERNEL-KB/@CLOSED))))", ((cpp_function_code)(&closedByAssertionP)), NULL);
    defineFunctionObject("CLOSED-TERM?", "(DEFUN (CLOSED-TERM? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (MEMOIZE (SELF *CONTEXT*) :TIMESTAMPS :KB-UPDATE :MAX-VALUES 500 (HELP-CLOSED-TERM? SELF NIL))))", ((cpp_function_code)(&closedTermP)), NULL);
    defineFunctionObject("HELP-CLOSED-TERM?", "(DEFUN (HELP-CLOSED-TERM? BOOLEAN) ((SELF OBJECT) (ACTIVETERMS CONS)))", ((cpp_function_code)(&helpClosedTermP)), NULL);
  }
}

void helpStartupSpecialists5() {
  {
    defineFunctionObject("CLOSED-PROPOSITION?", "(DEFUN (CLOSED-PROPOSITION? BOOLEAN) ((SELF PROPOSITION)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (MEMOIZE (SELF *CONTEXT*) :TIMESTAMPS :META-KB-UPDATE :MAX-VALUES 500 (HELP-CLOSED-PROPOSITION? SELF NIL))))", ((cpp_function_code)(&closedPropositionP)), NULL);
    defineFunctionObject("HELP-CLOSED-PROPOSITION?", "(DEFUN (HELP-CLOSED-PROPOSITION? BOOLEAN) ((SELF PROPOSITION) (ACTIVETERMS CONS)))", ((cpp_function_code)(&helpClosedPropositionP)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/SINGLE-VALUED-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/SINGLE-VALUED-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::singleValuedSpecialist)), NULL);
    defineFunctionObject("SINGLE-VALUED-TERM?", "(DEFUN (SINGLE-VALUED-TERM? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&singleValuedTermP)), NULL);
    defineFunctionObject("NON-RECURSIVE-SINGLE-VALUED-TERM?", "(DEFUN (NON-RECURSIVE-SINGLE-VALUED-TERM? BOOLEAN) ((SELF OBJECT)))", ((cpp_function_code)(&nonRecursiveSingleValuedTermP)), NULL);
    defineFunctionObject("SINGLE-VALUED-GOAL?", "(DEFUN (SINGLE-VALUED-GOAL? BOOLEAN) ((PROPOSITION PROPOSITION) (IOVARIABLES (CONS OF PATTERN-VARIABLE)) (BOUNDVARIABLES (CONS OF PATTERN-VARIABLE))) :PUBLIC? TRUE)", ((cpp_function_code)(&singleValuedGoalP)), NULL);
    defineFunctionObject("HELP-SINGLE-VALUED-GOAL?", "(DEFUN (HELP-SINGLE-VALUED-GOAL? BOOLEAN) ((PROPOSITION PROPOSITION) (IOVARIABLES (CONS OF PATTERN-VARIABLE)) (BOUNDVARIABLES (CONS OF PATTERN-VARIABLE)) (RECURSIVE? BOOLEAN)) :PUBLIC? TRUE)", ((cpp_function_code)(&helpSingleValuedGoalP)), NULL);
    defineFunctionObject("HELP-COLLECT-SINGLY-BOUND-VARIABLES", "(DEFUN HELP-COLLECT-SINGLY-BOUND-VARIABLES ((PROPOSITION PROPOSITION) (BOUNDVARIABLES (LIST OF PATTERN-VARIABLE)) (RECURSIVE? BOOLEAN)))", ((cpp_function_code)(&helpCollectSinglyBoundVariables)), NULL);
    defineFunctionObject("CREATE-COLLECT-DESCRIPTION-EXTENSION-FRAME", "(DEFUN CREATE-COLLECT-DESCRIPTION-EXTENSION-FRAME ((FRAME CONTROL-FRAME) (DESCRIPTION DESCRIPTION)))", ((cpp_function_code)(&createCollectDescriptionExtensionFrame)), NULL);
    defineFunctionObject("COLLECT-DESCRIPTION-EXTENSION-FRAME?", "(DEFUN (COLLECT-DESCRIPTION-EXTENSION-FRAME? BOOLEAN) ((FRAME CONTROL-FRAME)))", ((cpp_function_code)(&collectDescriptionExtensionFrameP)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/COLLECT-MEMBERS-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/COLLECT-MEMBERS-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::collectMembersSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/NTH-ELEMENT-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/NTH-ELEMENT-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::nthElementSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/NTH-HEAD-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/NTH-HEAD-COMPUTATION SKOLEM) ((LIST SKOLEM) (NARG INTEGER-WRAPPER)))", ((cpp_function_code)(&pl_kernel_kb::nthHeadComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/NTH-REST-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/NTH-REST-COMPUTATION SKOLEM) ((LIST SKOLEM) (NARG INTEGER-WRAPPER)))", ((cpp_function_code)(&pl_kernel_kb::nthRestComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/INSERT-ELEMENT-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/INSERT-ELEMENT-COMPUTATION SKOLEM) ((LIST SKOLEM) (NARG INTEGER-WRAPPER) (ELEMENT OBJECT)))", ((cpp_function_code)(&pl_kernel_kb::insertElementComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/MINIMUM-OF-NUMBERS-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/MINIMUM-OF-NUMBERS-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::minimumOfNumbersSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/MAXIMUM-OF-NUMBERS-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/MAXIMUM-OF-NUMBERS-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::maximumOfNumbersSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/SUM-OF-NUMBERS-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/SUM-OF-NUMBERS-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::sumOfNumbersSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/MEAN-OF-NUMBERS-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/MEAN-OF-NUMBERS-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::meanOfNumbersSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/MEDIAN-OF-NUMBERS-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/MEDIAN-OF-NUMBERS-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::medianOfNumbersSpecialist)), NULL);
    defineFunctionObject("COMPUTE-VARIANCE-OR-STANDARD-DEVIATION", "(DEFUN (COMPUTE-VARIANCE-OR-STANDARD-DEVIATION KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD) (STANDARD-DEVIATION? BOOLEAN)))", ((cpp_function_code)(&computeVarianceOrStandardDeviation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/STANDARD-DEVIATION-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/STANDARD-DEVIATION-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::standardDeviationSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/VARIANCE-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/VARIANCE-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::varianceSpecialist)), NULL);
    defineFunctionObject("HELP-DERIVE-PARTITION-MEMBERSHIPS", "(DEFUN HELP-DERIVE-PARTITION-MEMBERSHIPS ((SELF LOGIC-OBJECT) (SUPER LOGIC-OBJECT) (TUPLES (LIST OF PROPOSITION))))", ((cpp_function_code)(&helpDerivePartitionMemberships)), NULL);
    defineFunctionObject("DERIVE-PARTITION-MEMBERSHIPS?", "(DEFUN (DERIVE-PARTITION-MEMBERSHIPS? BOOLEAN) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&derivePartitionMembershipsP)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/HAS-PARTITION-MEMBERSHIP-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/HAS-PARTITION-MEMBERSHIP-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::hasPartitionMembershipSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/REFUTATION-DISJOINT-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/REFUTATION-DISJOINT-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::refutationDisjointSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/EMPTY-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/EMPTY-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::emptySpecialist)), NULL);
    defineFunctionObject("EMPTY-TERM?", "(DEFUN (EMPTY-TERM? BOOLEAN) ((SELF OBJECT)) :PUBLIC? TRUE)", ((cpp_function_code)(&emptyTermP)), NULL);
    defineFunctionObject("CHEAP-EMPTY-TERM?", "(DEFUN (CHEAP-EMPTY-TERM? BOOLEAN) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&cheapEmptyTermP)), NULL);
    defineFunctionObject("EXPENSIVE-EMPTY-TERM?", "(DEFUN (EXPENSIVE-EMPTY-TERM? BOOLEAN) ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&expensiveEmptyTermP)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/OBJECT-CONTEXT-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/OBJECT-CONTEXT-COMPUTATION CONTEXT) ((INSTANCE OBJECT)))", ((cpp_function_code)(&pl_kernel_kb::objectContextComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/OBJECT-NAME-CONTEXT-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/OBJECT-NAME-CONTEXT-COMPUTATION CONTEXT) ((INSTANCE OBJECT)))", ((cpp_function_code)(&pl_kernel_kb::objectNameContextComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/IST-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/IST-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::istSpecialist)), NULL);
    defineFunctionObject("GET-ROLESET-OF", "(DEFUN (GET-ROLESET-OF SKOLEM) ((RELATION NAMED-DESCRIPTION) (INSTANCE OBJECT)))", ((cpp_function_code)(&getRolesetOf)), NULL);
    defineFunctionObject("COMPUTE-STORED-BOUND-ON-ROLESET", "(DEFUN (COMPUTE-STORED-BOUND-ON-ROLESET INTEGER) ((RELATION NAMED-DESCRIPTION) (INSTANCE OBJECT) (LOWERORUPPER KEYWORD)))", ((cpp_function_code)(&computeStoredBoundOnRoleset)), NULL);
    defineFunctionObject("COMPUTE-MINIMUM-CARDINALITY", "(DEFUN (COMPUTE-MINIMUM-CARDINALITY INTEGER) ((RELATION NAMED-DESCRIPTION) (INSTANCE OBJECT)))", ((cpp_function_code)(&computeMinimumCardinality)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/RANGE-MIN-CARDINALITY-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/RANGE-MIN-CARDINALITY-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::rangeMinCardinalitySpecialist)), NULL);
    defineFunctionObject("COMPUTE-MAXIMUM-CARDINALITY", "(DEFUN (COMPUTE-MAXIMUM-CARDINALITY INTEGER) ((RELATION NAMED-DESCRIPTION) (INSTANCE OBJECT)))", ((cpp_function_code)(&computeMaximumCardinality)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/RANGE-MAX-CARDINALITY-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/RANGE-MAX-CARDINALITY-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::rangeMaxCardinalitySpecialist)), NULL);
    defineFunctionObject("TEST-RANGE-TYPE?", "(DEFUN (TEST-RANGE-TYPE? BOOLEAN) ((RELATION NAMED-DESCRIPTION) (INSTANCE OBJECT) (VALUETYPE NAMED-DESCRIPTION)))", ((cpp_function_code)(&testRangeTypeP)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/RANGE-TYPE-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/RANGE-TYPE-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::rangeTypeSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/REFLEXIVE-RELATION-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/REFLEXIVE-RELATION-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::reflexiveRelationSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/IRREFLEXIVE-RELATION-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/IRREFLEXIVE-RELATION-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::irreflexiveRelationSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/OBJECT-NAME-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/OBJECT-NAME-COMPUTATION STRING-WRAPPER) ((OBJECTARG OBJECT)))", ((cpp_function_code)(&pl_kernel_kb::objectNameComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/OBJECT-PRINT-NAME-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/OBJECT-PRINT-NAME-COMPUTATION STRING-WRAPPER) ((OBJECTARG OBJECT)))", ((cpp_function_code)(&pl_kernel_kb::objectPrintNameComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/NAME-TO-OBJECT-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/NAME-TO-OBJECT-COMPUTATION OBJECT) ((NAMEARG OBJECT)))", ((cpp_function_code)(&pl_kernel_kb::nameToObjectComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/PRINT-NAME-TO-OBJECT-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/PRINT-NAME-TO-OBJECT-COMPUTATION OBJECT) ((NAMEARG OBJECT)))", ((cpp_function_code)(&pl_kernel_kb::printNameToObjectComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/ARITY-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/ARITY-COMPUTATION INTEGER-WRAPPER) ((DESCRIPTIONARG OBJECT)))", ((cpp_function_code)(&pl_kernel_kb::arityComputation)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/ARITY-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/ARITY-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::aritySpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/RELATION-HIERARCHY-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/RELATION-HIERARCHY-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::relationHierarchySpecialist)), NULL);
    defineFunctionObject("HELP-PROJECT-NTH-COLUMN", "(DEFUN (HELP-PROJECT-NTH-COLUMN LIST) ((N INTEGER) (TUPLELIST LIST)))", ((cpp_function_code)(&helpProjectNthColumn)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/PROJECT-COLUMN-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/PROJECT-COLUMN-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::projectColumnSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/ASSERT-SYNONYM-DEMON", "(DEFUN /PL-KERNEL-KB/ASSERT-SYNONYM-DEMON ((SELF PROPOSITION)))", ((cpp_function_code)(&pl_kernel_kb::assertSynonymDemon)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/RETRACT-SYNONYM-DEMON", "(DEFUN /PL-KERNEL-KB/RETRACT-SYNONYM-DEMON ((SELF PROPOSITION)))", ((cpp_function_code)(&pl_kernel_kb::retractSynonymDemon)), NULL);
    defineFunctionObject("GET-SYNONYMS", "(DEFUN (GET-SYNONYMS (CONS OF LOGIC-OBJECT)) ((TERM OBJECT)))", ((cpp_function_code)(&getSynonyms)), NULL);
    defineFunctionObject("SYNONYM-SURROGATE?", "(DEFUN (SYNONYM-SURROGATE? BOOLEAN) ((NAME SURROGATE)))", ((cpp_function_code)(&synonymSurrogateP)), NULL);
    defineFunctionObject("TRANSFER-SYNONYMS", "(DEFUN TRANSFER-SYNONYMS ((OLDOBJECT OBJECT) (NEWOBJECT OBJECT)))", ((cpp_function_code)(&transferSynonyms)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/DIFFERENT-SPECIALIST", "(DEFUN (/PL-KERNEL-KB/DIFFERENT-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))", ((cpp_function_code)(&pl_kernel_kb::differentSpecialist)), NULL);
    defineFunctionObject(" /PL-KERNEL-KB/EQUIVALENT-TERMS-COMPUTATION", "(DEFUN (/PL-KERNEL-KB/EQUIVALENT-TERMS-COMPUTATION OBJECT) ((TERM OBJECT)))", ((cpp_function_code)(&pl_kernel_kb::equivalentTermsComputation)), NULL);
  }
}

void startupSpecialists() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupSpecialists1();
      helpStartupSpecialists2();
      helpStartupSpecialists3();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("COMPUTED-PROCEDURE", "(DEFCLASS COMPUTED-PROCEDURE (THING) :DOCUMENTATION \"Each instance denotes a programming language \nfunction that computes some procedure.  The slot 'procedure-name'\nprovides the name of the procedure.  The slot 'procedure-function'\npoints to the STELLA function object carrying out the computation.\nIf neither is supplied, the procedure will be looked up by extracting\nits name from the name of the instance.  Pointing to a function object\ninstead of just the code gives us access to argument type information.\nNote that we support external non-STELLA functions by creating a dummy\nSTELLA function object during registration of the computation (see\n`register-computation-function' and friends).\" :PUBLIC? TRUE :PUBLIC-SLOTS ((PROCEDURE-NAME :TYPE SYMBOL) (PROCEDURE-FUNCTION :TYPE FUNCTION)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newComputedProcedure));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessComputedProcedureSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("SUBSTRING-POSITION-ITERATOR", "(DEFCLASS SUBSTRING-POSITION-ITERATOR (ITERATOR) :SLOTS ((SUPER-STRING :TYPE STRING :REQUIRED? TRUE) (SUB-STRING :TYPE STRING :REQUIRED? TRUE) (START :TYPE INTEGER :INITIALLY 0) (SUB-LENGTH :TYPE INTEGER :INITIALLY (LENGTH (SUB-STRING SELF)))))");

        clasS->classConstructorCode = ((cpp_function_code)(&newSubstringPositionIterator));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessSubstringPositionIteratorSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("FORK-PROOF-ADJUNCT", "(DEFCLASS FORK-PROOF-ADJUNCT (PROOF-ADJUNCT) :SLOTS ((CONDITION-JUSTIFICATION :TYPE JUSTIFICATION) (DOWN-FRAME :TYPE CONTROL-FRAME)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newForkProofAdjunct));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessForkProofAdjunctSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("SAVED-INFERENCE-LEVEL-PROOF-ADJUNCT", "(DEFCLASS SAVED-INFERENCE-LEVEL-PROOF-ADJUNCT (PROOF-ADJUNCT) :SLOTS ((SAVED-INFERENCE-LEVEL :TYPE INFERENCE-LEVEL) (INFERENCE-LEVEL :TYPE INFERENCE-LEVEL) (DOWN-FRAME :TYPE CONTROL-FRAME)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newSavedInferenceLevelProofAdjunct));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessSavedInferenceLevelProofAdjunctSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("SAVED-CONTEXT-PROOF-ADJUNCT", "(DEFCLASS SAVED-CONTEXT-PROOF-ADJUNCT (PROOF-ADJUNCT) :SLOTS ((SAVED-CONTEXT :TYPE CONTEXT) (DOWN-FRAME :TYPE CONTROL-FRAME)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newSavedContextProofAdjunct));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessSavedContextProofAdjunctSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupSpecialists4();
      helpStartupSpecialists5();
      defineFunctionObject("LOOKUP-NATIVE-SPECIALIST", "(DEFUN (LOOKUP-NATIVE-SPECIALIST FUNCTION-CODE) ((NATIVE-NAME STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the native funtion code for `native-name' if it exists\nand the underlying programming languages supports such lookups.  Uses the signature\nof a specialist function.\")", ((cpp_function_code)(&lookupNativeSpecialist)), NULL);
      defineFunctionObject("REGISTER-SPECIALIST-FUNCTION", "(DEFUN REGISTER-SPECIALIST-FUNCTION ((NAME STRING) (CODE FUNCTION-CODE)) :DOCUMENTATION \"Creates a registration entry for `name' as a specialist which\nexecutes `code'.  Essentially just builds the Stella meta-information\ntructure needed to funcall `name' as a specialist.  The function definition\nin `code' needs to accept a CONTROL-FRAME and KEYWORD as arguments and\nreturn a KEYWORD.  Side effects on elements of the proposition in the\ncontrol frame can be used to bind and thus return values.\" :PUBLIC? TRUE)", ((cpp_function_code)(&registerSpecialistFunction)), NULL);
      defineFunctionObject("REGISTER-SPECIALIST-FUNCTION-NAME", "(DEFUN REGISTER-SPECIALIST-FUNCTION-NAME ((STELLA-NAME STRING) (NATIVE-NAME STRING)) :PUBLIC? TRUE :COMMAND? TRUE :DOCUMENTATION \"registers a specialist function `stella-name' based on the `native-name'\nfor the particular programming language in question.  Use of this command makes\nthe resulting code or knowledge bases non-portable to other target languages.\")", ((cpp_function_code)(&registerSpecialistFunctionName)), ((cpp_function_code)(&registerSpecialistFunctionNameEvaluatorWrapper)));
      defineFunctionObject("LOOKUP-NATIVE-COMPUTATION", "(DEFUN (LOOKUP-NATIVE-COMPUTATION FUNCTION-CODE) ((NATIVE-NAME STRING) (ARITY INTEGER)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the native funtion code for `native-name' if it exists\nand the underlying programming languages supports such lookups.  It is looked up\nusing the signature of a computation function supported by the computation specialist.\")", ((cpp_function_code)(&lookupNativeComputation)), NULL);
      defineFunctionObject("REGISTER-COMPUTATION-FUNCTION", "(DEFUN REGISTER-COMPUTATION-FUNCTION ((NAME STRING) (CODE FUNCTION-CODE) (ARITY INTEGER)) :DOCUMENTATION \"Creates a registration entry for `name' as a computation which\nexecutes `code'.  Essentially just builds the Stella meta-information\ntructure needed to funcall `name' as a computation function by the\ncomputation specialist.  The function definition in `code' needs to\naccept ARITY Stella OBJECTs as arguments and return a Stella OBJECT \nsuitable for PowerLoom use.  (These are generally LOGIC-OBJECTs and the\nliteral wrappers FLOAT-WRAPPER, INTEGER-WRAPPER and STRING-WRAPPER.)\" :PUBLIC? TRUE)", ((cpp_function_code)(&registerComputationFunction)), NULL);
      defineFunctionObject("REGISTER-COMPUTATION-FUNCTION-NAME", "(DEFUN REGISTER-COMPUTATION-FUNCTION-NAME ((STELLA-NAME STRING) (NATIVE-NAME STRING) (ARITY INTEGER)) :PUBLIC? TRUE :COMMAND? TRUE :DOCUMENTATION \"registers a computation function `stella-name' based on the `native-name'\nfor the particular programming language in question.  Use of this command makes\nthe resulting code or knowledge bases non-portable to other target languages.\")", ((cpp_function_code)(&registerComputationFunctionName)), ((cpp_function_code)(&registerComputationFunctionNameEvaluatorWrapper)));
      defineFunctionObject("STARTUP-SPECIALISTS", "(DEFUN STARTUP-SPECIALISTS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupSpecialists)), NULL);
      { MethodSlot* function = lookupFunction(SYM_SPECIALISTS_LOGIC_STARTUP_SPECIALISTS);

        setDynamicSlotValue(function->dynamicSlots, SYM_SPECIALISTS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupSpecialists"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineExplanationPhrase(KWD_SPECIALISTS_FORK_THEN, KWD_SPECIALISTS_TECHNICAL, "by FORK-introduction of its THEN argument", 0);
      defineExplanationPhrase(KWD_SPECIALISTS_FORK_THEN, KWD_SPECIALISTS_LAY, "since the condition and THEN-clause of a FORK-proposition succeeded", 0);
      defineExplanationPhrase(KWD_SPECIALISTS_FORK_ELSE, KWD_SPECIALISTS_TECHNICAL, "by FORK-introduction of its ELSE argument", 0);
      defineExplanationPhrase(KWD_SPECIALISTS_FORK_ELSE, KWD_SPECIALISTS_LAY, "since the condition and ELSE-clause of a FORK-proposition succeeded", 0);
      defineGlobalVariableObject("(DEFGLOBAL *PROTOTYPE-ID-COUNTER* INTEGER 0)", &oPROTOTYPE_ID_COUNTERo);
      defineExplanationPhrase(KWD_SPECIALISTS_COLLECT_MEMBERS, KWD_SPECIALISTS_TECHNICAL, "since it was proven by the COLLECT-MEMBERS specialist", 0);
      defineExplanationPhrase(KWD_SPECIALISTS_COLLECT_MEMBERS, KWD_SPECIALISTS_LAY, "because of a specialized COLLECT-MEMBERS reasoning procedure", 0);
      defineExplanationPhrase(KWD_SPECIALISTS_IST_INTRODUCTION, KWD_SPECIALISTS_TECHNICAL, "by IST-Introduction", 0);
      defineExplanationPhrase(KWD_SPECIALISTS_IST_INTRODUCTION, KWD_SPECIALISTS_LAY, "because its argument is true", 0);
      defineExplanationPhrase(KWD_SPECIALISTS_IST_INTRODUCTION, KWD_SPECIALISTS_LAY, "because its argument is partly true", 1, KWD_SPECIALISTS_PARTIAL);
      defineGlobalVariableObject("(DEFGLOBAL *ACCELERATE-FRAME-COMPUTATIONS?* BOOLEAN TRUE :DOCUMENTATION \"Used to test how big is the effect of the frame\nspecialists.\")", &oACCELERATE_FRAME_COMPUTATIONSpo);
    }
  }
}

Surrogate* SGT_SPECIALISTS_LOGIC_COMPUTED_PROCEDURE = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_PROCEDURE_NAME = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_PROCEDURE_FUNCTION = NULL;

Keyword* KWD_SPECIALISTS_ERROR = NULL;

Keyword* KWD_SPECIALISTS_RELEASE = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_SPECIALIST = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_HANDLES_REVERSE_POLARITY = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_CONSTRAINT = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_COMPUTATION = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_RELATION_EVALUATOR = NULL;

Keyword* KWD_SPECIALISTS_CONTINUING_SUCCESS = NULL;

Keyword* KWD_SPECIALISTS_FINAL_SUCCESS = NULL;

Keyword* KWD_SPECIALISTS_FAILURE = NULL;

Keyword* KWD_SPECIALISTS_TERMINAL_FAILURE = NULL;

Keyword* KWD_SPECIALISTS_FAIL = NULL;

Keyword* KWD_SPECIALISTS_TRUE = NULL;

Surrogate* SGT_SPECIALISTS_STELLA_THING = NULL;

Surrogate* SGT_SPECIALISTS_STELLA_FUNCTION_CODE_WRAPPER = NULL;

Surrogate* SGT_SPECIALISTS_STELLA_METHOD_CODE_WRAPPER = NULL;

Surrogate* SGT_SPECIALISTS_LOGIC_SUBSTRING_POSITION_ITERATOR = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_SUPER_STRING = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_SUB_STRING = NULL;

Symbol* SYM_SPECIALISTS_STELLA_START = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_SUB_LENGTH = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_TOTAL = NULL;

Surrogate* SGT_SPECIALISTS_STELLA_CONS = NULL;

Surrogate* SGT_SPECIALISTS_STELLA_OBJECT = NULL;

Symbol* SYM_SPECIALISTS_STELLA_ITERATOR = NULL;

Surrogate* SGT_SPECIALISTS_STELLA_NUMBER_WRAPPER = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_COLLECTIONOF = NULL;

Keyword* KWD_SPECIALISTS_UP_TRUE = NULL;

Keyword* KWD_SPECIALISTS_UP_FAIL = NULL;

Surrogate* SGT_SPECIALISTS_LOGIC_NAMED_DESCRIPTION = NULL;

Symbol* SYM_SPECIALISTS_STELLA_ISA = NULL;

Keyword* KWD_SPECIALISTS_MOVE_DOWN = NULL;

Surrogate* SGT_SPECIALISTS_LOGIC_DESCRIPTION = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_EXTERNAL_VARIABLES = NULL;

Surrogate* SGT_SPECIALISTS_STELLA_COLLECTION = NULL;

Surrogate* SGT_SPECIALISTS_LOGIC_LOGIC_OBJECT = NULL;

Keyword* KWD_SPECIALISTS_SCAN_COLLECTION = NULL;

Surrogate* SGT_SPECIALISTS_LOGIC_PROPOSITION = NULL;

Keyword* KWD_SPECIALISTS_DOWN = NULL;

Symbol* SYM_SPECIALISTS_STELLA_PREDICATE = NULL;

Symbol* SYM_SPECIALISTS_STELLA_FUNCTION = NULL;

Symbol* SYM_SPECIALISTS_STELLA_DUMMY = NULL;

Keyword* KWD_SPECIALISTS_FULL_SUBQUERY = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_DESCRIPTION = NULL;

Keyword* KWD_SPECIALISTS_FUNCTION = NULL;

Keyword* KWD_SPECIALISTS_PREDICATE = NULL;

Keyword* KWD_SPECIALISTS_ISA = NULL;

Surrogate* SGT_SPECIALISTS_LOGIC_SKOLEM = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_HOLDS = NULL;

Keyword* KWD_SPECIALISTS_AND = NULL;

Symbol* SYM_SPECIALISTS_STELLA_ARGUMENTS = NULL;

Surrogate* SGT_SPECIALISTS_LOGIC_FORK_PROOF_ADJUNCT = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_CONDITION_JUSTIFICATION = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_DOWN_FRAME = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_PROOF_ADJUNCT = NULL;

Keyword* KWD_SPECIALISTS_FAIL_INTRODUCTION = NULL;

Keyword* KWD_SPECIALISTS_FORK_ELSE = NULL;

Keyword* KWD_SPECIALISTS_FORK_THEN = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_JUSTIFICATION = NULL;

Keyword* KWD_SPECIALISTS_TECHNICAL = NULL;

Keyword* KWD_SPECIALISTS_LAY = NULL;

Keyword* KWD_SPECIALISTS_HOW_MANY = NULL;

Keyword* KWD_SPECIALISTS_INHERIT = NULL;

Keyword* KWD_SPECIALISTS_ALL = NULL;

Keyword* KWD_SPECIALISTS_CURRENT = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_QUERY_SPECIALIST_IO_VARIABLES = NULL;

Keyword* KWD_SPECIALISTS_MATCH_MODE = NULL;

Keyword* KWD_SPECIALISTS_DESCRIPTION = NULL;

Keyword* KWD_SPECIALISTS_SORT_BY = NULL;

Keyword* KWD_SPECIALISTS_GOAL_TREE = NULL;

Surrogate* SGT_SPECIALISTS_LOGIC_SAVED_INFERENCE_LEVEL_PROOF_ADJUNCT = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_SAVED_INFERENCE_LEVEL = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_INFERENCE_LEVEL = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_ASSERTION_QUERY = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_SHALLOW_QUERY = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_SUBSUMPTION_QUERY = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_BACKTRACKING_QUERY = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_NORMAL_QUERY = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_REFUTATION_QUERY = NULL;

Keyword* KWD_SPECIALISTS_LEVELED_QUERY = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_CONCEPT_PROTOTYPE = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_HYPOTHESIZED_INSTANCEp = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_CLOSED = NULL;

Surrogate* SGT_SPECIALISTS_LOGIC_F_CLOSED_TERMp_MEMO_TABLE_000 = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_EQUIVALENT_VALUE = NULL;

Surrogate* SGT_SPECIALISTS_LOGIC_PATTERN_VARIABLE = NULL;

Surrogate* SGT_SPECIALISTS_LOGIC_F_CLOSED_PROPOSITIONp_MEMO_TABLE_000 = NULL;

Keyword* KWD_SPECIALISTS_OR = NULL;

Keyword* KWD_SPECIALISTS_NOT = NULL;

Keyword* KWD_SPECIALISTS_FORALL = NULL;

Keyword* KWD_SPECIALISTS_EXISTS = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_MEMBER_OF = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_SINGLE_VALUED = NULL;

Surrogate* SGT_SPECIALISTS_LOGIC_F_SINGLE_VALUED_TERMp_MEMO_TABLE_000 = NULL;

Keyword* KWD_SPECIALISTS_EQUIVALENT = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_COLLECT_INTO_LIST = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_COLLECT_INTO_ORDERED_SET = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_COUNT_MEMBERS = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_INFERENCE_CUTOFF_REASON = NULL;

Keyword* KWD_SPECIALISTS_COLLECT_MEMBERS = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_pSUPER = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_pMDC = NULL;

Symbol* SYM_SPECIALISTS_STELLA_AND = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_MEMBER_OF = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_MUTUALLY_DISJOINT_COLLECTION = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_F_HELP_DERIVE_PARTITION_MEMBERSHIPS_QUERY_000 = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_MUTUALLY_DISJOINT_COLLECTION = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_PARTITION_MEMBERSHIP = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_DISJOINT = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_HAS_PARTITION_MEMBERSHIP = NULL;

Keyword* KWD_SPECIALISTS_ASSERT_TRUE = NULL;

Keyword* KWD_SPECIALISTS_ASSERT_FALSE = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_EMPTY = NULL;

Surrogate* SGT_SPECIALISTS_LOGIC_SAVED_CONTEXT_PROOF_ADJUNCT = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_SAVED_CONTEXT = NULL;

Surrogate* SGT_SPECIALISTS_STELLA_CONTEXT = NULL;

Keyword* KWD_SPECIALISTS_JUST_IN_TIME = NULL;

Keyword* KWD_SPECIALISTS_IST_INTRODUCTION = NULL;

Keyword* KWD_SPECIALISTS_PARTIAL = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_THE_ROLESET = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_CARDINALITY = NULL;

Keyword* KWD_SPECIALISTS_LOWER = NULL;

Keyword* KWD_SPECIALISTS_UPPER = NULL;

Surrogate* SGT_SPECIALISTS_STELLA_INTEGER_WRAPPER = NULL;

Surrogate* SGT_SPECIALISTS_STELLA_SURROGATE = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_DIRECT_SUBRELATION = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_DIRECT_SUPERRELATION = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_SUBRELATION = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_SUPERRELATION = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_PROPER_SUBRELATION = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_PROPER_SUPERRELATION = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_EQUIVALENT_RELATION = NULL;

Surrogate* SGT_SPECIALISTS_STELLA_LIST = NULL;

Surrogate* SGT_SPECIALISTS_PL_KERNEL_KB_SYNONYM = NULL;

Surrogate* SGT_SPECIALISTS_STELLA_CS_VALUE = NULL;

Symbol* SYM_SPECIALISTS_LOGIC_STARTUP_SPECIALISTS = NULL;

Symbol* SYM_SPECIALISTS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
