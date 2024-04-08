//  -*- Mode: C++ -*-

// print.cc

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

OutputStream* wrapNativeOutputStream(std::ostream* nativestream) {
  if (nativestream == STANDARD_OUTPUT->nativeStream) {
    return (STANDARD_OUTPUT);
  }
  else {
    { OutputStream* self000 = newOutputStream();

      self000->nativeStream = nativestream;
      { OutputStream* value000 = self000;

        return (value000);
      }
    }
  }
}

void printTopLevelObject(Object* self, std::ostream* nativestream) {
  { OutputStream* stream = wrapNativeOutputStream(nativestream);

    if (self->deletedP()) {
      *(stream->nativeStream) << "#DELETED#";
    }
    { Surrogate* testValue000 = safePrimaryType(self);

      if (subtypeOfP(testValue000, SGT_PRINT_LOGIC_DESCRIPTION)) {
        { Object* self000 = self;
          Description* self = ((Description*)(self000));

          printDescription(self, stream, true);
        }
      }
      else if (subtypeOfP(testValue000, SGT_PRINT_LOGIC_PATTERN_VARIABLE)) {
        { Object* self001 = self;
          PatternVariable* self = ((PatternVariable*)(self001));

          *(stream->nativeStream) << "|V|";
          printVariable(self, stream);
        }
      }
      else if (subtypeOfP(testValue000, SGT_PRINT_LOGIC_SKOLEM)) {
        { Object* self002 = self;
          Skolem* self = ((Skolem*)(self002));

          printSkolem(self, stream, true);
        }
      }
      else if (subtypeOfP(testValue000, SGT_PRINT_LOGIC_TRUTH_VALUE)) {
        { Object* self003 = self;
          TruthValue* self = ((TruthValue*)(self003));

          printTruthValue(self, stream);
        }
      }
      else if (subtypeOfP(testValue000, SGT_PRINT_LOGIC_LOGIC_OBJECT)) {
        { Object* self004 = self;
          LogicObject* self = ((LogicObject*)(self004));

          printLogicObject(self, stream, true);
        }
      }
      else if (subtypeOfP(testValue000, SGT_PRINT_LOGIC_PROPOSITION)) {
        { Object* self005 = self;
          Proposition* self = ((Proposition*)(self005));

          printProposition(self, stream, true);
        }
      }
      else {
        *(stream->nativeStream) << self;
      }
    }
  }
}

// If set to TRUE, modify printing so that it
// doesn't break and is more informative during a debugging session.
boolean oDEBUG_PRINT_MODEpo = false;

// Controls the kind of detail that gets printed about
// individual objects.  Values are :ORIGINAL, :REALISTIC, :FLAT, :DEBUG-LOW, and
//  :DEBUG-HIGH.
DEFINE_STELLA_SPECIAL(oPRINTMODEo, Keyword* , NULL);

// Controls whether functions are printed as relations (F i v) or
// as functions (= (F i) v).
DEFINE_STELLA_SPECIAL(oPRINTFUNCTIONSASRELATIONSpo, boolean , false);

void printLogicObject(LogicObject* self, OutputStream* stream, boolean toplevelP) {
  { const char* prefix = ((toplevelP &&
        (!oPRINTREADABLYpo)) ? "|i|" : "");

    if (((boolean)(self->surrogateValueInverse))) {
      if ((!(self->surrogateValueInverse->surrogateValue == self)) &&
          (!synonymSurrogateP(self->surrogateValueInverse))) {
        prefix = "|BAD surrogate|";
      }
      *(stream->nativeStream) << prefix << stringifiedSurrogate(self->surrogateValueInverse);
    }
    else {
      *(stream->nativeStream) << prefix << "_" << logicalType(self)->symbolName;
    }
  }
}

const char* VARIABLE_BINDING_SEPARATOR = "/";

const char* VALUE_OF_SEPARATOR = "//";

// If set, maps some skolems to names other than
// their own.
DEFINE_STELLA_SPECIAL(oSKOLEMNAMEMAPPINGTABLEo, KeyValueMap* , NULL);

const char* getSkolemPrintName(Skolem* self) {
  if (((boolean)(oSKOLEMNAMEMAPPINGTABLEo))) {
    { Skolem* substituteskolem = ((Skolem*)(oSKOLEMNAMEMAPPINGTABLEo->lookup(self)));

      return ((((boolean)(substituteskolem)) ? substituteskolem->skolemName->symbolName : self->skolemName->symbolName));
    }
  }
  else {
    return (self->skolemName->symbolName);
  }
}

void printValueOfChain(Skolem* self, OutputStream* stream, Object* chainend) {
  if (!((boolean)(chainend))) {
    chainend = self;
  }
  if ((oPRINTMODEo == KWD_PRINT_REALISTIC) ||
      (oPRINTMODEo == KWD_PRINT_ORIGINAL)) {
    if (subtypeOfP(safePrimaryType(self), SGT_PRINT_LOGIC_PATTERN_VARIABLE)) {
      { Skolem* self000 = self;
        PatternVariable* self = ((PatternVariable*)(self000));

        { 
          BIND_STELLA_SPECIAL(oPRINTMODEo, Keyword*, KWD_PRINT_FLAT);
          printValueOfChain(self, stream, chainend);
        }
      }
    }
    else {
      printVariableValue(chainend, stream);
    }
  }
  else if ((oPRINTMODEo == KWD_PRINT_FLAT) ||
      (oPRINTMODEo == KWD_PRINT_DEBUG_LOW)) {
    printSkolemName(self, stream);
    if (self == chainend) {
      return;
    }
    *(stream->nativeStream) << VALUE_OF_SEPARATOR;
    printVariableValue(chainend, stream);
  }
  else if (oPRINTMODEo == KWD_PRINT_DEBUG_HIGH) {
    printSkolemName(self, stream);
    if (self == chainend) {
      return;
    }
    { Object* cursor = self;
      Object* nextvalue = NULL;

      for (;;) {
        { Surrogate* testValue000 = safePrimaryType(cursor);

          if (subtypeOfP(testValue000, SGT_PRINT_LOGIC_SKOLEM)) {
            { Object* cursor000 = cursor;
              Skolem* cursor = ((Skolem*)(cursor000));

              nextvalue = ((Object*)(accessInContext(cursor->variableValue, cursor->homeContext, false)));
            }
          }
          else if (subtypeOfP(testValue000, SGT_PRINT_LOGIC_LOGIC_OBJECT)) {
            { Object* cursor001 = cursor;
              LogicObject* cursor = ((LogicObject*)(cursor001));

              nextvalue = cursor;
            }
          }
          else if (subtypeOfSurrogateP(testValue000)) {
            { Object* cursor002 = cursor;
              Surrogate* cursor = ((Surrogate*)(cursor002));

              nextvalue = cursor->surrogateValue;
            }
          }
          else if (subtypeOfP(testValue000, SGT_PRINT_STELLA_RELATION)) {
            { Object* cursor003 = cursor;
              Relation* cursor = ((Relation*)(cursor003));

              nextvalue = ((NamedDescription*)(dynamicSlotValue(cursor->dynamicSlots, SYM_PRINT_LOGIC_DESCRIPTION, NULL)));
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
        *(stream->nativeStream) << VALUE_OF_SEPARATOR;
        printVariableValue(nextvalue, stream);
        if (eqlP(nextvalue, chainend)) {
          break;
        }
        cursor = nextvalue;
      }
    }
  }
  else {
    { OutputStringStream* stream001 = newOutputStringStream();

      *(stream001->nativeStream) << "`" << oPRINTMODEo << "'" << " is not a valid case option";
      throw *newStellaException(stream001->theStringReader());
    }
  }
}

void printSkolemName(Skolem* self, OutputStream* stream) {
  *(stream->nativeStream) << stringDowncase(getSkolemPrintName(self));
}

void printVariableName(PatternVariable* self, OutputStream* stream) {
  printSkolemName(self, stream);
}

void printVariableValue(Object* self, OutputStream* stream) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_PRINT_LOGIC_PATTERN_VARIABLE)) {
      { Object* self000 = self;
        PatternVariable* self = ((PatternVariable*)(self000));

        printVariableName(self, stream);
      }
    }
    else if (subtypeOfP(testValue000, SGT_PRINT_LOGIC_SKOLEM)) {
      { Object* self001 = self;
        Skolem* self = ((Skolem*)(self001));

        printSkolemName(self, stream);
      }
    }
    else {
      printLogicalForm(self, stream);
    }
  }
}

void printSkolem(Skolem* self, OutputStream* stream, boolean toplevelP) {
  toplevelP = toplevelP;
  { const char* prefix = "|SK|";

    if (oDEBUG_PRINT_MODEpo) {
      *(stream->nativeStream) << prefix;
      printSkolemName(self, stream);
      return;
    }
    if ((oPRINTMODEo == KWD_PRINT_ORIGINAL) ||
        (oPRINTMODEo == KWD_PRINT_REALISTIC)) {
      prefix = "";
      if (((boolean)(nativeValueOf(self)))) {
        printVariableValue(nativeValueOf(self), stream);
        return;
      }
    }
    else {
    }
    if (((boolean)(self->definingProposition)) &&
        (!((boolean)(((Object*)(accessInContext(self->variableValue, self->homeContext, false))))))) {
      *(stream->nativeStream) << prefix;
      { 
        BIND_STELLA_SPECIAL(oPRINTLOGICALFORMSTREAMo, OutputStream*, stream);
        BIND_STELLA_SPECIAL(oINDENTCOUNTERo, int, 20);
        printKifFunctionExpression(self->definingProposition);
      }
      return;
    }
    printValueOfChain(self, stream, innermostOf(self));
  }
}

void printVariable(PatternVariable* self, OutputStream* stream) {
  if (((boolean)(oCURRENTJUSTIFICATIONo)) &&
      ((boolean)(justificationArgumentBoundTo(self, NULL)))) {
    prettyPrintLogicalForm(justificationArgumentBoundTo(self, NULL), stream);
    return;
  }
  { Object* value = (((boolean)(oPRINTINFRAMEo)) ? boundToInFrame(self, oPRINTINFRAMEo) : safeBoundTo(self));

    if (((boolean)(value))) {
      printVariableName(self, stream);
      *(stream->nativeStream) << VARIABLE_BINDING_SEPARATOR;
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        printVariableValue(value, stream);
        return;
      }
    }
  }
  printValueOfChain(self, stream, innermostOf(self));
}

void printQuantifiedVariable(PatternVariable* self, OutputStream* stream) {
  if (oPRINTREADABLYpo) {
    printVariableName(self, stream);
  }
  else {
    printVariable(self, stream);
  }
}

void printProposition(Proposition* self, OutputStream* stream, boolean toplevelP) {
  { const char* prefix = NULL;

    if (self->deletedP()) {
      *(stream->nativeStream) << "|dElEtEd-proposition|";
      return;
    }
    if (toplevelP &&
        (!oPRINTREADABLYpo)) {
      if (defaultTrueP(self) ||
          defaultFalseP(self)) {
        prefix = (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PRINT_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue ? "|pd|" : "|p|");
      }
      else if (((!self->deletedP()) &&
          ((oREVERSEPOLARITYpo ? falseP(self) : (trueP(self) ||
          functionWithDefinedValueP(self))))) ||
          falseP(self)) {
        prefix = (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PRINT_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue ? "|Pd|" : "|P|");
      }
      else if (inconsistentP(self)) {
        prefix = (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PRINT_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue ? "|Pd#|" : "|P#|");
      }
      else {
        prefix = (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PRINT_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue ? "|Pd?|" : "|P?|");
      }
    }
    if (coerceWrappedBooleanToBoolean(self->unfastenedP_reader())) {
      prefix = (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_PRINT_LOGIC_DESCRIPTIVEp, FALSE_WRAPPER)))->wrapperValue ? "|uPd|" : "|uP|");
    }
    if (((boolean)(((Surrogate*)(dynamicSlotValue(self->dynamicSlots, SYM_PRINT_STELLA_SURROGATE_VALUE_INVERSE, NULL))))) &&
        (!(((Surrogate*)(dynamicSlotValue(self->dynamicSlots, SYM_PRINT_STELLA_SURROGATE_VALUE_INVERSE, NULL)))->surrogateValue == self))) {
      prefix = "|BAD surrogate|";
    }
    if (prefix != NULL) {
      *(stream->nativeStream) << prefix;
    }
  }
  printLogicalForm(self, stream);
}

void printDescription(Description* self, OutputStream* stream, boolean toplevelP) {
  if (self->deletedP()) {
    *(stream->nativeStream) << "|dElEtEd-description|";
    if (((boolean)(self->surrogateValueInverse))) {
      *(stream->nativeStream) << self->surrogateValueInverse;
    }
    return;
  }
  if (oLOADINGREGENERABLEOBJECTSpo ||
      (coerceWrappedBooleanToBoolean(self->badP_reader()) ||
       oDEBUG_PRINT_MODEpo)) {
    *(stream->nativeStream) << "|d|";
  }
  else if (toplevelP &&
      (!oPRINTREADABLYpo)) {
    if (classP(self)) {
      *(stream->nativeStream) << "|c|";
    }
    else if (functionP(self)) {
      *(stream->nativeStream) << "|f|";
    }
    else if (relationP(self)) {
      *(stream->nativeStream) << "|r|";
    }
    else {
      *(stream->nativeStream) << "|d|";
    }
  }
  printLogicalForm(self, stream);
}

void startupPrint() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SGT_PRINT_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
      SGT_PRINT_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", NULL, 1)));
      SGT_PRINT_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", NULL, 1)));
      SGT_PRINT_LOGIC_TRUTH_VALUE = ((Surrogate*)(internRigidSymbolWrtModule("TRUTH-VALUE", NULL, 1)));
      SGT_PRINT_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
      SGT_PRINT_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
      KWD_PRINT_FLAT = ((Keyword*)(internRigidSymbolWrtModule("FLAT", NULL, 2)));
      KWD_PRINT_REALISTIC = ((Keyword*)(internRigidSymbolWrtModule("REALISTIC", NULL, 2)));
      KWD_PRINT_ORIGINAL = ((Keyword*)(internRigidSymbolWrtModule("ORIGINAL", NULL, 2)));
      KWD_PRINT_DEBUG_LOW = ((Keyword*)(internRigidSymbolWrtModule("DEBUG-LOW", NULL, 2)));
      KWD_PRINT_DEBUG_HIGH = ((Keyword*)(internRigidSymbolWrtModule("DEBUG-HIGH", NULL, 2)));
      SGT_PRINT_STELLA_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("RELATION", getStellaModule("/STELLA", true), 1)));
      SYM_PRINT_LOGIC_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 0)));
      SYM_PRINT_LOGIC_DESCRIPTIVEp = ((Symbol*)(internRigidSymbolWrtModule("DESCRIPTIVE?", NULL, 0)));
      SYM_PRINT_STELLA_SURROGATE_VALUE_INVERSE = ((Symbol*)(internRigidSymbolWrtModule("SURROGATE-VALUE-INVERSE", getStellaModule("/STELLA", true), 0)));
      SYM_PRINT_LOGIC_STARTUP_PRINT = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-PRINT", NULL, 0)));
      SYM_PRINT_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(4)) {
      oPRINTMODEo = KWD_PRINT_FLAT;
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("WRAP-NATIVE-OUTPUT-STREAM", "(DEFUN (WRAP-NATIVE-OUTPUT-STREAM OUTPUT-STREAM) ((NATIVESTREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&wrapNativeOutputStream)), NULL);
      defineFunctionObject("PRINT-TOP-LEVEL-OBJECT", "(DEFUN PRINT-TOP-LEVEL-OBJECT ((SELF OBJECT) (NATIVESTREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&printTopLevelObject)), NULL);
      defineFunctionObject("PRINT-LOGIC-OBJECT", "(DEFUN PRINT-LOGIC-OBJECT ((SELF LOGIC-OBJECT) (STREAM OUTPUT-STREAM) (TOPLEVEL? BOOLEAN)))", ((cpp_function_code)(&printLogicObject)), NULL);
      defineFunctionObject("GET-SKOLEM-PRINT-NAME", "(DEFUN (GET-SKOLEM-PRINT-NAME STRING) ((SELF SKOLEM)))", ((cpp_function_code)(&getSkolemPrintName)), NULL);
      defineFunctionObject("PRINT-VALUE-OF-CHAIN", "(DEFUN PRINT-VALUE-OF-CHAIN ((SELF SKOLEM) (STREAM OUTPUT-STREAM) (CHAINEND OBJECT)))", ((cpp_function_code)(&printValueOfChain)), NULL);
      defineFunctionObject("PRINT-SKOLEM-NAME", "(DEFUN PRINT-SKOLEM-NAME ((SELF SKOLEM) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printSkolemName)), NULL);
      defineFunctionObject("PRINT-VARIABLE-NAME", "(DEFUN PRINT-VARIABLE-NAME ((SELF PATTERN-VARIABLE) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printVariableName)), NULL);
      defineFunctionObject("PRINT-VARIABLE-VALUE", "(DEFUN PRINT-VARIABLE-VALUE ((SELF OBJECT) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printVariableValue)), NULL);
      defineFunctionObject("PRINT-SKOLEM", "(DEFUN PRINT-SKOLEM ((SELF SKOLEM) (STREAM OUTPUT-STREAM) (TOPLEVEL? BOOLEAN)))", ((cpp_function_code)(&printSkolem)), NULL);
      defineFunctionObject("PRINT-VARIABLE", "(DEFUN PRINT-VARIABLE ((SELF PATTERN-VARIABLE) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printVariable)), NULL);
      defineFunctionObject("PRINT-QUANTIFIED-VARIABLE", "(DEFUN PRINT-QUANTIFIED-VARIABLE ((SELF PATTERN-VARIABLE) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printQuantifiedVariable)), NULL);
      defineFunctionObject("PRINT-PROPOSITION", "(DEFUN PRINT-PROPOSITION ((SELF PROPOSITION) (STREAM OUTPUT-STREAM) (TOPLEVEL? BOOLEAN)))", ((cpp_function_code)(&printProposition)), NULL);
      defineFunctionObject("PRINT-DESCRIPTION", "(DEFUN PRINT-DESCRIPTION ((SELF DESCRIPTION) (STREAM OUTPUT-STREAM) (TOPLEVEL? BOOLEAN)))", ((cpp_function_code)(&printDescription)), NULL);
      defineFunctionObject("STARTUP-PRINT", "(DEFUN STARTUP-PRINT () :PUBLIC? TRUE)", ((cpp_function_code)(&startupPrint)), NULL);
      { MethodSlot* function = lookupFunction(SYM_PRINT_LOGIC_STARTUP_PRINT);

        setDynamicSlotValue(function->dynamicSlots, SYM_PRINT_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupPrint"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFGLOBAL *DEBUG-PRINT-MODE?* BOOLEAN FALSE :DOCUMENTATION \"If set to TRUE, modify printing so that it\ndoesn't break and is more informative during a debugging session.\")", &oDEBUG_PRINT_MODEpo);
      defineGlobalVariableObject("(DEFSPECIAL *PRINTMODE* KEYWORD :FLAT :DOCUMENTATION \"Controls the kind of detail that gets printed about\nindividual objects.  Values are :ORIGINAL, :REALISTIC, :FLAT, :DEBUG-LOW, and\n :DEBUG-HIGH.\")", &oPRINTMODEo);
      defineGlobalVariableObject("(DEFSPECIAL *PRINTFUNCTIONSASRELATIONS?* BOOLEAN FALSE :DOCUMENTATION \"Controls whether functions are printed as relations (F i v) or\nas functions (= (F i) v).\")", &oPRINTFUNCTIONSASRELATIONSpo);
      defineGlobalVariableObject("(DEFCONSTANT VARIABLE-BINDING-SEPARATOR STRING \"/\")", &VARIABLE_BINDING_SEPARATOR);
      defineGlobalVariableObject("(DEFCONSTANT VALUE-OF-SEPARATOR STRING \"//\")", &VALUE_OF_SEPARATOR);
      defineGlobalVariableObject("(DEFSPECIAL *SKOLEMNAMEMAPPINGTABLE* (ENTITY-MAPPING OF SKOLEM SKOLEM) NULL :DOCUMENTATION \"If set, maps some skolems to names other than\ntheir own.\")", &oSKOLEMNAMEMAPPINGTABLEo);
    }
  }
}

Surrogate* SGT_PRINT_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_PRINT_LOGIC_PATTERN_VARIABLE = NULL;

Surrogate* SGT_PRINT_LOGIC_SKOLEM = NULL;

Surrogate* SGT_PRINT_LOGIC_TRUTH_VALUE = NULL;

Surrogate* SGT_PRINT_LOGIC_LOGIC_OBJECT = NULL;

Surrogate* SGT_PRINT_LOGIC_PROPOSITION = NULL;

Keyword* KWD_PRINT_FLAT = NULL;

Keyword* KWD_PRINT_REALISTIC = NULL;

Keyword* KWD_PRINT_ORIGINAL = NULL;

Keyword* KWD_PRINT_DEBUG_LOW = NULL;

Keyword* KWD_PRINT_DEBUG_HIGH = NULL;

Surrogate* SGT_PRINT_STELLA_RELATION = NULL;

Symbol* SYM_PRINT_LOGIC_DESCRIPTION = NULL;

Symbol* SYM_PRINT_LOGIC_DESCRIPTIVEp = NULL;

Symbol* SYM_PRINT_STELLA_SURROGATE_VALUE_INVERSE = NULL;

Symbol* SYM_PRINT_LOGIC_STARTUP_PRINT = NULL;

Symbol* SYM_PRINT_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
