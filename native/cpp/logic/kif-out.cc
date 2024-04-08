//  -*- Mode: C++ -*-

// kif-out.cc

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

// Controls whether logical forms print on single lines
// (unformatted) or multi-line indented.
DEFINE_STELLA_SPECIAL(oPRETTYPRINTLOGICALFORMSpo, boolean , false);

// Controls whether KIF expressions print on single lines
// (unformatted) or multi-line indented.
DEFINE_STELLA_SPECIAL(oPRETTYPRINTKIFpo, boolean , false);

// Eliminates necessity of passing stream argument
// throughout 'print-logical-form' functions.
DEFINE_STELLA_SPECIAL(oPRINTLOGICALFORMSTREAMo, OutputStream* , NULL);

// Controls whether down-casing happens during logical
// form printing (leading to lots more string garbage).
DEFINE_STELLA_SPECIAL(oDOWNCASEOPERATORSpo, boolean , false);

// Table to allow extension of the logical form printing code
// by associating keywords with print functions.  Should have values added only
// via the associated function REGISTER-LOGIC-DIALECT-PRINT-FUNCTION.
KeyValueList* oLOGIC_DIALECT_PRINT_FUNCTIONSo = NULL;

void registerLogicDialectPrintFunction(Keyword* dialect, FunctionCodeWrapper* fn) {
  // Register `fn' as a logic-object print function for `dialect'.
  // Each function should have the signature `((self OBJECT) (stream OUTPUT-STREAM))'.
  // Any return values will be ignored.
  oLOGIC_DIALECT_PRINT_FUNCTIONSo->insertAt(dialect, fn);
}

// Used to register objects that quantify variables, so we
// can decide in certain contexts whether to print a variable or its value.
DEFINE_STELLA_SPECIAL(oPRINTQUANTIFIEDOBJECTSSTACKo, Cons* , NULL);

void pushQuantifiedObject(Object* object) {
  if (((boolean)(oPRINTQUANTIFIEDOBJECTSSTACKo))) {
    oPRINTQUANTIFIEDOBJECTSSTACKo = cons(object, oPRINTQUANTIFIEDOBJECTSSTACKo);
  }
}

void popQuantifiedObject() {
  if (((boolean)(oPRINTQUANTIFIEDOBJECTSSTACKo))) {
    oPRINTQUANTIFIEDOBJECTSSTACKo = oPRINTQUANTIFIEDOBJECTSSTACKo->rest;
  }
}

boolean quantifiedObjectVariableP(Skolem* var) {
  if (((boolean)(oPRINTQUANTIFIEDOBJECTSSTACKo))) {
    { Object* obj = NULL;
      Cons* iter000 = oPRINTQUANTIFIEDOBJECTSSTACKo;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        obj = iter000->value;
        { Surrogate* testValue000 = safePrimaryType(obj);

          if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_PROPOSITION)) {
            { Object* obj000 = obj;
              Proposition* obj = ((Proposition*)(obj000));

              if (((Vector*)(dynamicSlotValue(obj->dynamicSlots, SYM_KIF_OUT_LOGIC_IO_VARIABLES, NULL)))->memberP(var)) {
                return (true);
              }
            }
          }
          else if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_DESCRIPTION)) {
            { Object* obj001 = obj;
              Description* obj = ((Description*)(obj001));

              if (obj->ioVariables->memberP(var) ||
                  obj->internalVariables->memberP(var)) {
                return (true);
              }
            }
          }
          else if (subtypeOfP(testValue000, SGT_KIF_OUT_STELLA_VECTOR)) {
            { Object* obj002 = obj;
              Vector* obj = ((Vector*)(obj002));

              if (obj->memberP(var)) {
                return (true);
              }
            }
          }
          else if (testValue000 == SGT_KIF_OUT_STELLA_CONS) {
            { Object* obj003 = obj;
              Cons* obj = ((Cons*)(obj003));

              if (obj->memberP(var)) {
                return (true);
              }
            }
          }
          else if (subtypeOfP(testValue000, SGT_KIF_OUT_STELLA_LIST)) {
            { Object* obj004 = obj;
              List* obj = ((List*)(obj004));

              if (obj->memberP(var)) {
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
  return (false);
}

const char* maybeDowncase(const char* string) {
  if (!oMODULEo->caseSensitiveP) {
    if (oDOWNCASEOPERATORSpo) {
      return (stringDowncase(string));
    }
    if (stringEqlP(string, "FORALL")) {
      return ("forall");
    }
    else if (stringEqlP(string, "EXISTS")) {
      return ("exists");
    }
    else if (stringEqlP(string, "THE")) {
      return ("the");
    }
    else if (stringEqlP(string, "AND")) {
      return ("and");
    }
    else if (stringEqlP(string, "OR")) {
      return ("or");
    }
    else if (stringEqlP(string, "NOT")) {
      return ("not");
    }
    else if (stringEqlP(string, "KAPPA")) {
      return ("kappa");
    }
    else if (stringEqlP(string, "SUBSET-OF")) {
      return ("subset-of");
    }
    else {
    }
  }
  return (string);
}

// The number of spaces prepended during printing a logical form.
DEFINE_STELLA_SPECIAL(oINDENTCOUNTERo, int , 0);

// The number of spaces added by a call to 'increase-indent'.
int oINDENT_QUANTUMo = 3;

void increaseIndent(int indent) {
  if (indent == NULL_INTEGER) {
    indent = oINDENT_QUANTUMo;
  }
  oINDENTCOUNTERo = oINDENTCOUNTERo + indent;
}

void decreaseIndent(int indent) {
  if (indent == NULL_INTEGER) {
    indent = oINDENT_QUANTUMo;
  }
  oINDENTCOUNTERo = oINDENTCOUNTERo - indent;
}

void printIndent(OutputStream* stream, int indent) {
  if (indent == NULL_INTEGER) {
    indent = oINDENTCOUNTERo;
  }
  { int i = NULL_INTEGER;
    int iter000 = 1;
    int upperBound000 = indent;
    boolean unboundedP000 = upperBound000 == NULL_INTEGER;

    for  (; unboundedP000 ||
              (iter000 <= upperBound000); 
          iter000 = iter000 + 1) {
      i = iter000;
      i = i;
      *(stream->nativeStream) << " ";
    }
  }
}

void printLogicalFormInDialect(Object* self, Keyword* dialect, OutputStream* stream) {
  // Produce a stringified version of a logical representation
  // of 'self' and write it to the stream 'stream'.  Use the dialect 'dialect',
  // or use the current dialect if 'dialect' is NULL.
  if (!((boolean)(self))) {
    return;
  }
  if (!((boolean)(dialect))) {
    dialect = oLOGIC_DIALECTo;
  }
  if (dialect == KWD_KIF_OUT_KIF) {
    printAsKif(self, stream);
  }
  else if ((dialect == KWD_KIF_OUT_STELLA) ||
      (dialect == KWD_KIF_OUT_PREFIX_STELLA)) {
    printAsKif(self, stream);
  }
  else if (dialect == KWD_KIF_OUT_SQL) {
  }
  else {
    { FunctionCodeWrapper* fn = ((FunctionCodeWrapper*)(oLOGIC_DIALECT_PRINT_FUNCTIONSo->lookup(dialect)));

      if (((boolean)(fn))) {
        ((void  (*) (Object*, OutputStream*))fn->wrapperValue)(self, stream);
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Unknown dialect for printing logic forms: " << "`" << dialect << "'";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

void printLogicalForm(Object* form, OutputStream* stream) {
  // Print the logical form `form' to `stream' according to
  // the current setting of `*logic-dialect*'.  Pretty-printing is controlled
  // by the current setting of `*prettyPrintLogicalForms?*'.
  { 
    BIND_STELLA_SPECIAL(oPRINTQUANTIFIEDOBJECTSSTACKo, Cons*, NIL);
    printLogicalFormInDialect(form, oLOGIC_DIALECTo, stream);
  }
}

void prettyPrintLogicalForm(Object* form, OutputStream* stream) {
  // Pretty-print the logical form `form' to `stream' according
  // to the current setting of `*logic-dialect*'.
  { 
    BIND_STELLA_SPECIAL(oPRETTYPRINTLOGICALFORMSpo, boolean, true);
    BIND_STELLA_SPECIAL(oPRINTQUANTIFIEDOBJECTSSTACKo, Cons*, NIL);
    printLogicalFormInDialect(form, oLOGIC_DIALECTo, stream);
  }
}

void printUnformattedLogicalForm(Object* form, OutputStream* stream) {
  // Print the logical form `form' to `stream' according to
  // the current setting of `*logic-dialect*'.  Pretty-printing is explicitly
  // forced to be turned off.
  { 
    BIND_STELLA_SPECIAL(oPRETTYPRINTLOGICALFORMSpo, boolean, false);
    BIND_STELLA_SPECIAL(oPRINTQUANTIFIEDOBJECTSSTACKo, Cons*, NIL);
    printLogicalFormInDialect(form, oLOGIC_DIALECTo, stream);
  }
}

void printFormula(Object* formula, int indent) {
  { 
    BIND_STELLA_SPECIAL(oINDENTCOUNTERo, int, indent);
    printUnformattedLogicalForm(formula, STANDARD_OUTPUT);
  }
}

void printAsKif(Object* self, OutputStream* stream) {
  { int currentindentcounter = oINDENTCOUNTERo;

    { 
      BIND_STELLA_SPECIAL(oINDENTCOUNTERo, int, currentindentcounter);
      BIND_STELLA_SPECIAL(oPRINTLOGICALFORMSTREAMo, OutputStream*, stream);
      BIND_STELLA_SPECIAL(oPRETTYPRINTKIFpo, boolean, oPRETTYPRINTLOGICALFORMSpo);
      BIND_STELLA_SPECIAL(oPRINTQUANTIFIEDOBJECTSSTACKo, Cons*, NIL);
      printAsKifInternal(self);
    }
  }
}

void printAsKifInternal(Object* self) {
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;

    if (!((boolean)(self))) {
      *(stream->nativeStream) << "NULL";
      return;
    }
    if (self->deletedP()) {
      *(stream->nativeStream) << "DeLeTeD";
      return;
    }
    { Surrogate* testValue000 = safePrimaryType(self);

      if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_PROPOSITION)) {
        { Object* self000 = self;
          Proposition* self = ((Proposition*)(self000));

          printKifProposition(self);
        }
      }
      else if (subtypeOfWrapperP(testValue000)) {
        { Object* self001 = self;
          Wrapper* self = ((Wrapper*)(self001));

          printKifWrapper(((LiteralWrapper*)(self)));
        }
      }
      else if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_DESCRIPTION)) {
        { Object* self002 = self;
          Description* self = ((Description*)(self002));

          printKifDescription(self);
        }
      }
      else if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_PATTERN_VARIABLE)) {
        { Object* self003 = self;
          PatternVariable* self = ((PatternVariable*)(self003));

          printKifVariable(self);
        }
      }
      else if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_SKOLEM)) {
        { Object* self004 = self;
          Skolem* self = ((Skolem*)(self004));

          printKifSkolem(self, false);
        }
      }
      else if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_LOGIC_OBJECT)) {
        { Object* self005 = self;
          LogicObject* self = ((LogicObject*)(self005));

          printKifLogicObject(self);
        }
      }
      else if (subtypeOfSurrogateP(testValue000)) {
        { Object* self006 = self;
          Surrogate* self = ((Surrogate*)(self006));

          *(stream->nativeStream) << stringifiedSurrogate(self);
        }
      }
      else if (subtypeOfKeywordP(testValue000)) {
        { Object* self007 = self;
          Keyword* self = ((Keyword*)(self007));

          *(stream->nativeStream) << self;
        }
      }
      else if (subtypeOfP(testValue000, SGT_KIF_OUT_STELLA_COLLECTION)) {
        { Object* self008 = self;
          Collection* self = ((Collection*)(self008));

          printKifStellaCollection(self);
        }
      }
      else if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_LOGIC_THING)) {
        { Object* self009 = self;
          LogicThing* self = ((LogicThing*)(self009));

          *(stream->nativeStream) << generateTerm(self);
        }
      }
      else if (subtypeOfP(testValue000, SGT_KIF_OUT_STELLA_THING)) {
        { Object* self010 = self;
          Thing* self = ((Thing*)(self010));

          *(stream->nativeStream) << self;
        }
      }
      else {
        *(stream->nativeStream) << "|Illegal Logical Form|: " << self;
      }
    }
  }
}

boolean visibleArgumentP(Object* self) {
  if (!((boolean)(self))) {
    return (true);
  }
  if (subtypeOfP(safePrimaryType(self), SGT_KIF_OUT_LOGIC_PROPOSITION)) {
    { Object* self000 = self;
      Proposition* self = ((Proposition*)(self000));

      if ((self->kind == KWD_KIF_OUT_ISA) &&
          coerceWrappedBooleanToBoolean(self->variableTypeP_reader())) {
        if (((boolean)(oCURRENTJUSTIFICATIONo))) {
          return (true);
        }
        if ((oPRINTMODEo == KWD_KIF_OUT_REALISTIC) ||
            (oPRINTMODEo == KWD_KIF_OUT_ORIGINAL)) {
          return (false);
        }
        else {
        }
      }
    }
  }
  else {
  }
  return (true);
}

int visibleArgumentsCount(Vector* arguments) {
  { int count = 0;

    { Object* arg = NULL;
      Vector* vector000 = arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        if (visibleArgumentP(arg)) {
          count = count + 1;
        }
      }
    }
    return (count);
  }
}

void printKifArguments(Vector* arguments, boolean separatelinesP, boolean omitlastargumentP) {
  if (!((boolean)(arguments))) {
    return;
  }
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;
    Iterator* argumentsiterator = (omitlastargumentP ? arguments->butLast() : ((Iterator*)(arguments->allocateIterator())));
    int visibleargcount = visibleArgumentsCount(arguments);
    int argindex = 0;

    if (omitlastargumentP &&
        visibleArgumentP(arguments->last())) {
      visibleargcount = visibleargcount - 1;
    }
    { Object* arg = NULL;
      Iterator* iter000 = argumentsiterator;

      for (; iter000->nextP(); ) {
        arg = iter000->value;
        if (visibleArgumentP(arg) ||
            (visibleargcount == 0)) {
          argindex = argindex + 1;
          if (argindex > 1) {
            if (separatelinesP &&
                oPRETTYPRINTKIFpo) {
              *(stream->nativeStream) << std::endl;
              printIndent(stream, NULL_INTEGER);
            }
            else {
              *(stream->nativeStream) << " ";
            }
          }
          printAsKifInternal(arg);
        }
      }
    }
  }
}

void printKifOperatorWithArguments(const char* operatoR, Vector* arguments, boolean separatelinesP, boolean omitlastargumentP) {
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;

    *(stream->nativeStream) << "(" << operatoR << (((arguments->length() > 0) ? " " : ""));
    increaseIndent(strlen(operatoR) + 2);
    printKifArguments(arguments, separatelinesP, omitlastargumentP);
    decreaseIndent(strlen(operatoR) + 2);
    *(stream->nativeStream) << ")";
  }
}

const char* stringifiedSurrogate(Surrogate* operatoR) {
  { NamedDescription* description = getDescription(operatoR);
    const char* string = NULL;
    boolean visibleP = operatoR == lookupSurrogateInModule(operatoR->symbolName, oMODULEo, false);

    if (((boolean)(description))) {
      string = internalStellaOperatorToKif(surrogateToSymbol(operatoR))->symbolName;
    }
    else {
      string = operatoR->symbolName;
    }
    if ((oPRINTREADABLYpo ||
        (!visibleP)) &&
        ((!((boolean)(description))) ||
         (!(string[0] == '(')))) {
      { Keyword* testValue000 = computeSymbolEscapeCode(string, oMODULEo->caseSensitiveP);

        if (testValue000 == KWD_KIF_OUT_UNESCAPED) {
          if (visibleP) {
            string = maybeDowncase(string);
          }
        }
        else if (testValue000 == KWD_KIF_OUT_ESCAPED) {
          string = stringConcatenate("|", string, 1, "|");
        }
        else if (testValue000 == KWD_KIF_OUT_COMPLEX_ESCAPED) {
          string = replaceSubstrings(string, "\\\\", "\\");
          string = replaceSubstrings(string, "\\|", "|");
          string = stringConcatenate("|", string, 1, "|");
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
    if (visibleP) {
      return (string);
    }
    else {
      return (computeFullName(string, ((Module*)(operatoR->homeContext))));
    }
  }
}

const char* stringifiedKifOperator(Proposition* self) {
  { GeneralizedSymbol* operatoR = self->operatoR;

    if (!((boolean)(operatoR))) {
      return ("NULL");
    }
    { Surrogate* testValue000 = safePrimaryType(operatoR);

      if (subtypeOfSurrogateP(testValue000)) {
        { GeneralizedSymbol* operator000 = operatoR;
          Surrogate* operatoR = ((Surrogate*)(operator000));

          return (stringifiedSurrogate(operatoR));
        }
      }
      else if (subtypeOfSymbolP(testValue000)) {
        { GeneralizedSymbol* operator001 = operatoR;
          Symbol* operatoR = ((Symbol*)(operator001));

          return (maybeDowncase(operatoR->symbolName));
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

DEFINE_STELLA_SPECIAL(oTOPLEVELPRINTKIFPROPOSITIONpo, boolean , true);

void printKifProposition(Proposition* self) {
  if (self == NULL) {
    return;
  }
  { boolean toplevelP = oTOPLEVELPRINTKIFPROPOSITIONpo;
    OutputStream* stream = oPRINTLOGICALFORMSTREAMo;
    boolean printexplicitnegationP = toplevelP &&
        ((falseP(self) ||
        defaultFalseP(self)) &&
         (!(self->operatoR == SGT_KIF_OUT_STELLA_FALSE)));

    { 
      BIND_STELLA_SPECIAL(oTOPLEVELPRINTKIFPROPOSITIONpo, boolean, false);
      if (printexplicitnegationP) {
        *(stream->nativeStream) << "(" << stringifiedSurrogate(SGT_KIF_OUT_PL_KERNEL_KB_NOT) << " ";
        increaseIndent(5);
      }
      if (((oPRINTMODEo == KWD_KIF_OUT_REALISTIC) ||
          (oPRINTMODEo == KWD_KIF_OUT_ORIGINAL)) &&
          (toplevelP &&
           topLevelExistsPropositionP(self))) {
        printKifTopLevelExistsProposition(self);
      }
      else {
        helpPrintKifProposition(self);
      }
      if (printexplicitnegationP) {
        *(stream->nativeStream) << ")";
        decreaseIndent(5);
      }
    }
  }
}

void helpPrintKifProposition(Proposition* self) {
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;
    const char* operatoR = NULL;
    boolean separatelinesP = false;

    { Keyword* testValue000 = self->kind;

      if ((testValue000 == KWD_KIF_OUT_AND) ||
          (testValue000 == KWD_KIF_OUT_OR)) {
        if (self->kind == KWD_KIF_OUT_AND) {
          operatoR = stringifiedSurrogate(SGT_KIF_OUT_PL_KERNEL_KB_AND);
        }
        else {
          operatoR = stringifiedSurrogate(SGT_KIF_OUT_PL_KERNEL_KB_OR);
        }
        separatelinesP = true;
        if (visibleArgumentsCount(self->arguments) == 1) {
          if ((oPRINTMODEo == KWD_KIF_OUT_REALISTIC) ||
              (oPRINTMODEo == KWD_KIF_OUT_ORIGINAL)) {
            printKifArguments(self->arguments, false, false);
            return;
          }
          else {
          }
        }
      }
      else if (testValue000 == KWD_KIF_OUT_NOT) {
        operatoR = stringifiedSurrogate(SGT_KIF_OUT_PL_KERNEL_KB_NOT);
      }
      else if (testValue000 == KWD_KIF_OUT_EQUIVALENT) {
        operatoR = "=";
      }
      else if ((testValue000 == KWD_KIF_OUT_ISA) ||
          (testValue000 == KWD_KIF_OUT_PREDICATE)) {
        operatoR = stringifiedKifOperator(self);
        if (self->operatoR == SGT_KIF_OUT_PL_KERNEL_KB_FORK) {
          separatelinesP = true;
        }
      }
      else if (testValue000 == KWD_KIF_OUT_FUNCTION) {
        printKifFunctionProposition(self);
        return;
      }
      else if (testValue000 == KWD_KIF_OUT_IMPLIES) {
        printKifImpliesProposition(self);
        return;
      }
      else if ((testValue000 == KWD_KIF_OUT_FORALL) ||
          (testValue000 == KWD_KIF_OUT_EXISTS)) {
        printKifQuantification(self);
        return;
      }
      else if (testValue000 == KWD_KIF_OUT_CONSTANT) {
        *(stream->nativeStream) << ((Surrogate*)(self->operatoR))->symbolName;
        return;
      }
      else if (testValue000 == KWD_KIF_OUT_CONTAINED_BY) {
        operatoR = ":CONTAINED-BY";
      }
      else if (testValue000 == KWD_KIF_OUT_DELETED) {
        operatoR = ":DELETED";
      }
      else {
        operatoR = self->kind->symbolName;
      }
    }
    printKifOperatorWithArguments(operatoR, self->arguments, separatelinesP, false);
  }
}

void printKifFunctionProposition(Proposition* self) {
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;
    const char* downcasedname = stringifiedKifOperator(self);
    Object* lastargument = (self->arguments->theArray)[(self->arguments->length() - 1)];
    boolean printasrelationP = oPRINTFUNCTIONSASRELATIONSpo;

    if (!(printasrelationP)) {
      *(stream->nativeStream) << "(= ";
    }
    *(stream->nativeStream) << "(" << downcasedname << " ";
    increaseIndent(strlen(downcasedname) + 2);
    printKifArguments(self->arguments, false, true);
    decreaseIndent(strlen(downcasedname) + 2);
    if (!(printasrelationP)) {
      *(stream->nativeStream) << ")";
    }
    *(stream->nativeStream) << " ";
    if (((boolean)(lastargument))) {
      { Surrogate* testValue000 = safePrimaryType(lastargument);

        if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_PATTERN_VARIABLE)) {
          { Object* lastargument000 = lastargument;
            PatternVariable* lastargument = ((PatternVariable*)(lastargument000));

            printKifVariable(lastargument);
          }
        }
        else if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_SKOLEM)) {
          { Object* lastargument001 = lastargument;
            Skolem* lastargument = ((Skolem*)(lastargument001));

            printKifSkolem(lastargument, true);
          }
        }
        else {
          printAsKifInternal(lastargument);
        }
      }
    }
    *(stream->nativeStream) << ")";
  }
}

void printKifFunctionExpression(Proposition* self) {
  { const char* downcasedname = stringifiedKifOperator(self);

    printKifOperatorWithArguments(downcasedname, self->arguments, false, true);
  }
}

void printKifImpliesProposition(Proposition* self) {
  { Object* tailarg = (self->arguments->theArray)[0];
    Object* headarg = (self->arguments->theArray)[1];

    if (isaP(headarg, SGT_KIF_OUT_LOGIC_DESCRIPTION) &&
        isaP(tailarg, SGT_KIF_OUT_LOGIC_DESCRIPTION)) {
      printDescriptionsAsKifRule(((Description*)(headarg)), ((Description*)(tailarg)), self, false);
    }
    else {
      printKifOperatorWithArguments(stringifiedSurrogate(SGT_KIF_OUT_PL_KERNEL_KB_SUBSET_OF), self->arguments, false, false);
    }
  }
}

void printKifQuantifiedVariables(Vector* variables, boolean includetypesP) {
  if (!((boolean)(variables))) {
    return;
  }
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;

    *(stream->nativeStream) << "(";
    { Skolem* vbl = NULL;
      Vector* vector000 = variables;
      int index000 = 0;
      int length000 = vector000->length();
      int i = NULL_INTEGER;
      int iter000 = 1;

      for  (; index000 < length000; 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        vbl = ((Skolem*)((vector000->theArray)[index000]));
        i = iter000;
        { boolean printtypeP = includetypesP &&
              (!(logicalType(vbl) == SGT_KIF_OUT_STELLA_THING));

          if (printtypeP) {
            *(stream->nativeStream) << "(";
          }
          { Surrogate* testValue000 = safePrimaryType(vbl);

            if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_PATTERN_VARIABLE)) {
              { Skolem* vbl000 = vbl;
                PatternVariable* vbl = ((PatternVariable*)(vbl000));

                printQuantifiedVariable(vbl, stream);
              }
            }
            else if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_SKOLEM)) {
              { Skolem* vbl001 = vbl;
                Skolem* vbl = vbl001;

                printValueOfChain(vbl, stream, vbl);
              }
            }
            else {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
                throw *newStellaException(stream000->theStringReader());
              }
            }
          }
          if (printtypeP) {
            *(stream->nativeStream) << " " << logicalType(vbl)->symbolName << ")";
          }
          if (i < variables->length()) {
            *(stream->nativeStream) << " ";
          }
        }
      }
    }
    *(stream->nativeStream) << ")";
  }
}

void printKifQuantification(Proposition* self) {
  pushQuantifiedObject(self);
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;
    Proposition* tail = ((Proposition*)((self->arguments->theArray)[0]));
    Proposition* head = ((self->arguments->length() == 2) ? ((Proposition*)((self->arguments->theArray)[1])) : NULL);
    boolean implicationP = ((boolean)(head));
    Surrogate* implicationoperator = (implicationP ? chooseImplicationOperator(self, ((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_KIF_OUT_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue) : ((Surrogate*)(NULL)));

    if (((boolean)(implicationoperator)) &&
        (((BooleanWrapper*)(dynamicSlotValue(self->dynamicSlots, SYM_KIF_OUT_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue &&
         (!(implicationoperator == SGT_KIF_OUT_PL_KERNEL_KB_le)))) {
      { Proposition* temp = tail;

        tail = head;
        head = temp;
      }
    }
    { Keyword* testValue000 = self->kind;

      if (testValue000 == KWD_KIF_OUT_FORALL) {
        *(stream->nativeStream) << "(" << stringifiedSurrogate(SGT_KIF_OUT_PL_KERNEL_KB_FORALL) << " ";
      }
      else if (testValue000 == KWD_KIF_OUT_EXISTS) {
        *(stream->nativeStream) << "(" << stringifiedSurrogate(SGT_KIF_OUT_PL_KERNEL_KB_EXISTS) << " ";
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    printKifQuantifiedVariables(((Vector*)(dynamicSlotValue(self->dynamicSlots, SYM_KIF_OUT_LOGIC_IO_VARIABLES, NULL))), false);
    *(stream->nativeStream) << std::endl;
    increaseIndent(NULL_INTEGER);
    printIndent(stream, NULL_INTEGER);
    if (implicationP) {
      *(stream->nativeStream) << "(" << stringifiedSurrogate(implicationoperator) << " ";
      increaseIndent(strlen((implicationoperator->symbolName)) + 2);
      printKifProposition(head);
      *(stream->nativeStream) << std::endl;
      printIndent(stream, NULL_INTEGER);
    }
    printKifProposition(tail);
    if (implicationP) {
      *(stream->nativeStream) << ")";
      decreaseIndent(strlen((implicationoperator->symbolName)) + 2);
    }
    decreaseIndent(NULL_INTEGER);
    *(stream->nativeStream) << ")";
    popQuantifiedObject();
  }
}

void printKifTopLevelExistsProposition(Proposition* self) {
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;
    Vector* variables = collectSkolemizedExistsVariables(self);

    pushQuantifiedObject(variables);
    *(stream->nativeStream) << "(" << stringifiedSurrogate(SGT_KIF_OUT_PL_KERNEL_KB_EXISTS) << " ";
    printKifQuantifiedVariables(variables, false);
    *(stream->nativeStream) << std::endl;
    increaseIndent(NULL_INTEGER);
    printIndent(stream, NULL_INTEGER);
    printKifProposition(self);
    decreaseIndent(NULL_INTEGER);
    *(stream->nativeStream) << ")";
    popQuantifiedObject();
  }
}

void printKifWrapper(LiteralWrapper* self) {
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;

    { Surrogate* testValue000 = safePrimaryType(self);

      if (subtypeOfIntegerP(testValue000)) {
        { LiteralWrapper* self000 = self;
          IntegerWrapper* self = ((IntegerWrapper*)(self000));

          *(stream->nativeStream) << self->wrapperValue;
        }
      }
      else if (subtypeOfLongIntegerP(testValue000)) {
        { LiteralWrapper* self001 = self;
          LongIntegerWrapper* self = ((LongIntegerWrapper*)(self001));

          *(stream->nativeStream) << self->wrapperValue;
        }
      }
      else if (subtypeOfFloatP(testValue000)) {
        { LiteralWrapper* self002 = self;
          FloatWrapper* self = ((FloatWrapper*)(self002));

          *(stream->nativeStream) << self->wrapperValue;
        }
      }
      else if (subtypeOfBooleanP(testValue000)) {
        { LiteralWrapper* self003 = self;
          BooleanWrapper* self = ((BooleanWrapper*)(self003));

          *(stream->nativeStream) << self->wrapperValue;
        }
      }
      else if (subtypeOfStringP(testValue000)) {
        { LiteralWrapper* self004 = self;
          StringWrapper* self = ((StringWrapper*)(self004));

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream->nativeStream) << self;
          }
        }
      }
      else if (subtypeOfCharacterP(testValue000)) {
        { LiteralWrapper* self005 = self;
          CharacterWrapper* self = ((CharacterWrapper*)(self005));

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream->nativeStream) << self;
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

void printKifLogicObject(LogicObject* self) {
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;

    if (((boolean)(self->surrogateValueInverse))) {
      *(stream->nativeStream) << stringifiedSurrogate(self->surrogateValueInverse);
    }
    else {
      *(stream->nativeStream) << "Unnamed_Object";
    }
  }
}

void printKifSkolem(Skolem* self, boolean suppressdefiningpropositionP) {
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;

    if (quantifiedObjectVariableP(self)) {
      printSkolemName(self, stream);
    }
    else if (suppressdefiningpropositionP) {
      printSkolem(self, stream, false);
    }
    else if (((boolean)(self->definingProposition))) {
      printKifFunctionExpression(self->definingProposition);
    }
    else {
      printSkolem(self, stream, false);
    }
  }
}

void printKifVariable(PatternVariable* self) {
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;

    if (quantifiedObjectVariableP(self)) {
      printQuantifiedVariable(self, stream);
    }
    else {
      printVariable(self, stream);
    }
  }
}

void printKifStellaCollection(Collection* self) {
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;

    *(stream->nativeStream) << "(" << ((self->noDuplicatesP() ? stringifiedSurrogate(SGT_KIF_OUT_PL_KERNEL_KB_SETOF) : stringifiedSurrogate(SGT_KIF_OUT_PL_KERNEL_KB_LISTOF)));
    { Object* m = NULL;
      Iterator* iter000 = ((Iterator*)(self->allocateIterator()));

      for (; iter000->nextP(); ) {
        m = iter000->value;
        *(stream->nativeStream) << " ";
        printAsKifInternal(m);
      }
    }
    *(stream->nativeStream) << ")";
  }
}

void printKifDescription(Description* self) {
  { 
    BIND_STELLA_SPECIAL(oQUERYITERATORo, QueryIterator*, NULL);
    pushQuantifiedObject(self);
    { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;
      Description* complement = ((Description*)(dynamicSlotValue(self->dynamicSlots, SYM_KIF_OUT_LOGIC_COMPLEMENT_DESCRIPTION, NULL)));

      if (((boolean)(self->surrogateValueInverse))) {
        *(stream->nativeStream) << stringifiedSurrogate(self->surrogateValueInverse);
      }
      else if (((boolean)(complement)) &&
          (((boolean)(complement->surrogateValueInverse)) &&
           (!((oPRINTMODEo == KWD_KIF_OUT_REALISTIC) ||
          (oPRINTMODEo == KWD_KIF_OUT_ORIGINAL))))) {
        *(stream->nativeStream) << "not-" << stringifiedSurrogate(complement->surrogateValueInverse);
      }
      else {
        *(stream->nativeStream) << "(" << stringifiedSurrogate(SGT_KIF_OUT_PL_KERNEL_KB_KAPPA) << " ";
        printKifQuantifiedVariables(self->ioVariables, true);
        *(stream->nativeStream) << " ";
        printKifDescriptionProposition(self, false);
        *(stream->nativeStream) << ")";
      }
      popQuantifiedObject();
    }
  }
}

void printKifDescriptionProposition(Description* self, boolean invertP) {
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;
    Vector* existentials = (self->internalVariables->nonEmptyP() ? copyConsListToVariablesVector(topLevelExistentialVariables(self)) : ZERO_VARIABLES_VECTOR);

    if (invertP) {
      *(stream->nativeStream) << "(" << stringifiedSurrogate(SGT_KIF_OUT_PL_KERNEL_KB_NOT) << " ";
      increaseIndent(4);
    }
    if (existentials->nonEmptyP()) {
      *(stream->nativeStream) << "(" << stringifiedSurrogate(SGT_KIF_OUT_PL_KERNEL_KB_EXISTS) << " ";
      printKifQuantifiedVariables(existentials, false);
      *(stream->nativeStream) << std::endl;
      increaseIndent(NULL_INTEGER);
      printIndent(stream, NULL_INTEGER);
    }
    printAsKifInternal(self->proposition);
    if (existentials->nonEmptyP()) {
      *(stream->nativeStream) << ")";
      decreaseIndent(NULL_INTEGER);
    }
    if (invertP) {
      *(stream->nativeStream) << ")";
      decreaseIndent(4);
    }
  }
}

Surrogate* chooseImplicationOperator(Proposition* rule, boolean forwardP) {
  { Surrogate* operatorprefix = (forwardP ? SGT_KIF_OUT_PL_KERNEL_KB_eg : SGT_KIF_OUT_PL_KERNEL_KB_le);

    if (oPRINTMODEo == KWD_KIF_OUT_REALISTIC) {
    }
    else if (forwardP &&
        ((BooleanWrapper*)(dynamicSlotValue(rule->dynamicSlots, SYM_KIF_OUT_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue) {
      operatorprefix = SGT_KIF_OUT_PL_KERNEL_KB_egg;
    }
    else if (((BooleanWrapper*)(dynamicSlotValue(rule->dynamicSlots, SYM_KIF_OUT_LOGIC_BACKWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue &&
        (!forwardP)) {
      operatorprefix = SGT_KIF_OUT_PL_KERNEL_KB_lle;
    }
    if (defaultTrueP(rule) &&
        (!(oPRINTMODEo == KWD_KIF_OUT_REALISTIC))) {
      if (operatorprefix == SGT_KIF_OUT_PL_KERNEL_KB_le) {
        operatorprefix = SGT_KIF_OUT_PL_KERNEL_KB_lt;
      }
      else if (operatorprefix == SGT_KIF_OUT_PL_KERNEL_KB_eg) {
        operatorprefix = SGT_KIF_OUT_PL_KERNEL_KB_tg;
      }
      else if (operatorprefix == SGT_KIF_OUT_PL_KERNEL_KB_lle) {
        operatorprefix = SGT_KIF_OUT_PL_KERNEL_KB_llt;
      }
      else if (operatorprefix == SGT_KIF_OUT_PL_KERNEL_KB_egg) {
        operatorprefix = SGT_KIF_OUT_PL_KERNEL_KB_tgg;
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << operatorprefix << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
    return (operatorprefix);
  }
}

KeyValueMap* createSkolemMappingTable(Vector* oldvars, Vector* newvars) {
  { KeyValueMap* mapping = NULL;

    { PatternVariable* oldvar = NULL;
      Vector* vector000 = oldvars;
      int index000 = 0;
      int length000 = vector000->length();
      PatternVariable* newvar = NULL;
      Vector* vector001 = newvars;
      int index001 = 0;
      int length001 = vector001->length();

      for  (; (index000 < length000) &&
                (index001 < length001); 
            index000 = index000 + 1,
            index001 = index001 + 1) {
        oldvar = ((PatternVariable*)((vector000->theArray)[index000]));
        newvar = ((PatternVariable*)((vector001->theArray)[index001]));
        if (!(oldvar->skolemName == newvar->skolemName)) {
          if (!((boolean)(mapping))) {
            mapping = newKeyValueMap();
          }
          mapping->insertAt(oldvar, newvar);
        }
      }
    }
    return (mapping);
  }
}

void printDescriptionsAsKifRule(Description* head, Description* tail, Proposition* rule, boolean reversepolarityP) {
  { OutputStream* stream = oPRINTLOGICALFORMSTREAMo;
    boolean forwardarrowP = ((BooleanWrapper*)(dynamicSlotValue(rule->dynamicSlots, SYM_KIF_OUT_LOGIC_FORWARD_ONLYp, FALSE_WRAPPER)))->wrapperValue &&
        (!reversepolarityP);
    boolean reverseargumentsP = forwardarrowP ||
        reversepolarityP;
    int currentindentcounter = oINDENTCOUNTERo;
    Surrogate* operatorprefix = chooseImplicationOperator(rule, forwardarrowP);
    int operatorprefixindent = 2 + strlen((operatorprefix->symbolName));
    boolean mapheadvariablesP = namedDescriptionP(head);
    Vector* ruleVariables = ((Vector*)(dynamicSlotValue(rule->dynamicSlots, SYM_KIF_OUT_LOGIC_IO_VARIABLES, NULL)));
    KeyValueMap* headvariablemapping = NULL;
    KeyValueMap* tailvariablemapping = NULL;

    if (head->deletedP() ||
        tail->deletedP()) {
      *(stream->nativeStream) << "(=> <DeLeTeD ArGuMeNt(S)>)";
      return;
    }
    if (reverseargumentsP) {
      { Description* temp = head;

        head = tail;
        tail = temp;
      }
      mapheadvariablesP = !mapheadvariablesP;
    }
    if (((boolean)(ruleVariables))) {
      headvariablemapping = ((KeyValueMap*)(createSkolemMappingTable(head->ioVariables, ruleVariables)));
      tailvariablemapping = ((KeyValueMap*)(createSkolemMappingTable(tail->ioVariables, ruleVariables)));
    }
    else if (mapheadvariablesP) {
      ruleVariables = tail->ioVariables;
      headvariablemapping = ((KeyValueMap*)(createSkolemMappingTable(head->ioVariables, ruleVariables)));
    }
    else {
      ruleVariables = head->ioVariables;
      tailvariablemapping = ((KeyValueMap*)(createSkolemMappingTable(tail->ioVariables, ruleVariables)));
    }
    { 
      BIND_STELLA_SPECIAL(oINDENTCOUNTERo, int, currentindentcounter);
      *(stream->nativeStream) << "(" << stringifiedSurrogate(SGT_KIF_OUT_PL_KERNEL_KB_FORALL) << " ";
      printKifQuantifiedVariables(ruleVariables, false);
      *(stream->nativeStream) << std::endl;
      increaseIndent(NULL_INTEGER);
      printIndent(stream, NULL_INTEGER);
      *(stream->nativeStream) << "(" << stringifiedSurrogate(operatorprefix) << " ";
      increaseIndent(operatorprefixindent);
      pushQuantifiedObject(head);
      { 
        BIND_STELLA_SPECIAL(oSKOLEMNAMEMAPPINGTABLEo, KeyValueMap*, headvariablemapping);
        printKifDescriptionProposition(head, reversepolarityP);
      }
      popQuantifiedObject();
      *(stream->nativeStream) << std::endl;
      printIndent(stream, NULL_INTEGER);
      pushQuantifiedObject(tail);
      { 
        BIND_STELLA_SPECIAL(oSKOLEMNAMEMAPPINGTABLEo, KeyValueMap*, tailvariablemapping);
        printKifDescriptionProposition(tail, reversepolarityP);
      }
      popQuantifiedObject();
      *(stream->nativeStream) << "))";
      decreaseIndent(operatorprefixindent);
      decreaseIndent(NULL_INTEGER);
    }
  }
}

// List of propositions that shouldn't be saved by `save-module'.
DEFINE_STELLA_SPECIAL(oEXCLUDEDPROPOSITIONSo, HashTable* , NULL);

void excludeOriginatedPropositions() {
  { NamedDescription* d = NULL;
    Iterator* iter000 = allNamedDescriptions(NULL, false);

    for (; iter000->nextP(); ) {
      d = ((NamedDescription*)(iter000->value));
      { Proposition* prop = NULL;
        Cons* iter001 = originatedPropositions(d)->theConsList;

        for (; !(iter001 == NIL); iter001 = iter001->rest) {
          prop = ((Proposition*)(iter001->value));
          oEXCLUDEDPROPOSITIONSo->insertAt(prop, TRUE_WRAPPER);
        }
      }
    }
  }
  { Proposition* p = NULL;
    Iterator* iter002 = locallyConceivedPropositions(oMODULEo)->allocateIterator();

    for (; iter002->nextP(); ) {
      p = ((Proposition*)(iter002->value));
      if (((boolean)(objectSurrogate(p)))) {
        { Proposition* prop = NULL;
          Cons* iter003 = originatedPropositions(p)->theConsList;

          for (; !(iter003 == NIL); iter003 = iter003->rest) {
            prop = ((Proposition*)(iter003->value));
            oEXCLUDEDPROPOSITIONSo->insertAt(prop, TRUE_WRAPPER);
          }
        }
      }
    }
  }
}

boolean hiddenRelationP(Surrogate* relationRef) {
  return (allTrueDependentPropositions(relationRef->surrogateValue, SGT_KIF_OUT_PL_KERNEL_KB_HIDDEN_RELATION, false)->nextP());
}

boolean excludedPropositionP(Proposition* proposition, Module* module) {
  if (unknownP(proposition) &&
      (proposition->homeModule() == module)) {
    return (true);
  }
  if (((boolean)(((BooleanWrapper*)(oEXCLUDEDPROPOSITIONSo->lookup(proposition))))) ||
      ((boolean)(((Proposition*)(dynamicSlotValue(proposition->dynamicSlots, SYM_KIF_OUT_LOGIC_MASTER_PROPOSITION, NULL)))))) {
    return (true);
  }
  { Keyword* testValue000 = proposition->kind;

    if (testValue000 == KWD_KIF_OUT_ISA) {
      if (((BooleanWrapper*)(dynamicSlotValue(proposition->dynamicSlots, SYM_KIF_OUT_LOGIC_ASSERTED_BY_TYPE_CHECKERp, FALSE_WRAPPER)))->wrapperValue ||
          hiddenRelationP(((Surrogate*)(proposition->operatoR)))) {
        return (true);
      }
    }
    else if (testValue000 == KWD_KIF_OUT_FUNCTION) {
      { Object* lastarg = proposition->arguments->last();

        if ((skolemP(lastarg) &&
            (eqlP(valueOf(lastarg), lastarg) &&
             (!topLevelExistsPropositionP(proposition)))) ||
            hiddenRelationP(((Surrogate*)(proposition->operatoR)))) {
          return (true);
        }
      }
    }
    else if (testValue000 == KWD_KIF_OUT_PREDICATE) {
      if (hiddenRelationP(((Surrogate*)(proposition->operatoR)))) {
        return (true);
      }
    }
    else {
    }
  }
  return (false);
}

void prettyPrintNamedDescription(NamedDescription* self, OutputStream* stream) {
  prettyPrintRelationDefinitionTree(((Cons*)(unstringifyInModule(stringifiedSource(self), self->homeModule()))), stream);
}

void NamedDescription::describeObject(OutputStream* stream, Keyword* mode) {
  // Prints a description of 'self' to stream 'stream'.  'mode'
  // can be :terse, :verbose, or :source.  Used by `describe'.
  { NamedDescription* self = this;

    if (mode == KWD_KIF_OUT_TERSE) {
      describeTersely(self, stream);
    }
    else if ((mode == KWD_KIF_OUT_VERBOSE) ||
        (mode == KWD_KIF_OUT_SOURCE)) {
      prettyPrintNamedDescription(self, stream);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << mode << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

const char* stellaRelationStringifiedSource(Relation* self) {
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfClassP(testValue000)) {
      { Relation* self000 = self;
        Class* self = ((Class*)(self000));

        return (self->classStringifiedSource);
      }
    }
    else if (subtypeOfMethodSlotP(testValue000)) {
      { Relation* self001 = self;
        MethodSlot* self = ((MethodSlot*)(self001));

        return (self->methodStringifiedSource);
      }
    }
    else {
      return (NULL);
    }
  }
}

void prettyPrintRelationDefinition(Relation* self, OutputStream* stream) {
  { const char* definitionstring = stellaRelationStringifiedSource(self);

    if (definitionstring != NULL) {
      prettyPrintRelationDefinitionTree(((Cons*)(unstringifyInModule(definitionstring, self->homeModule()))), stream);
    }
  }
}

void prettyPrintRelationDefinitionTree(Cons* tree, OutputStream* stream) {
  helpPrettyPrintRelationDefinitionTree(tree, stream, 0, 2, true);
  *(stream->nativeStream) << std::endl;
}

void helpPrettyPrintRelationDefinitionTree(Cons* tree, OutputStream* stream, int startindent, int keyindent, boolean forcefirstkeyonseparatelineP) {
  { 
    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
    BIND_STELLA_SPECIAL(oPRINTPRETTYpo, boolean, true);
    { Object* value000 = NULL;

      { Object* element = NULL;
        Cons* iter000 = tree;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          element = iter000->value;
          if (keywordP(element)) {
            value000 = element;
            break;
          }
        }
      }
      { int nofheaderelements = tree->position(value000, 0);

        { PropertyList* self000 = newPropertyList();

          self000->thePlist = extractOptions(tree, NULL);
          { PropertyList* options = self000;
            int keylength = NULL_INTEGER;

            if (nofheaderelements == NULL_INTEGER) {
              nofheaderelements = tree->length();
            }
            forcefirstkeyonseparatelineP = forcefirstkeyonseparatelineP ||
                (options->length() > 1);
            *(stream->nativeStream) << "(";
            { Object* element = NULL;
              Cons* iter001 = tree;
              int i = NULL_INTEGER;
              int iter002 = 1;
              int upperBound000 = nofheaderelements;
              boolean unboundedP000 = upperBound000 == NULL_INTEGER;

              for  (; (!(iter001 == NIL)) &&
                        (unboundedP000 ||
                         (iter002 <= upperBound000)); 
                    iter001 = iter001->rest,
                    iter002 = iter002 + 1) {
                element = iter001->value;
                i = iter002;
                if (i > 1) {
                  *(stream->nativeStream) << " ";
                }
                *(stream->nativeStream) << element;
              }
            }
            { Object* key = NULL;
              Object* value = NULL;
              Cons* iter003 = options->thePlist;
              int i = NULL_INTEGER;
              int iter004 = 1;

              for  (; !(iter003 == NIL); 
                    iter003 = iter003->rest->rest,
                    iter004 = iter004 + 1) {
                key = iter003->value;
                value = iter003->rest->value;
                i = iter004;
                if ((i == 1) &&
                    (!forcefirstkeyonseparatelineP)) {
                  if (nofheaderelements > 0) {
                    *(stream->nativeStream) << " ";
                  }
                }
                else {
                  *(stream->nativeStream) << std::endl;
                  printIndent(stream, startindent + keyindent);
                }
                if (subtypeOfKeywordP(safePrimaryType(key))) {
                  { Object* key000 = key;
                    Keyword* key = ((Keyword*)(key000));

                    keylength = strlen((key->symbolName)) + 1;
                    *(stream->nativeStream) << ":" << key->symbolName;
                  }
                }
                else {
                  keylength = 4;
                  *(stream->nativeStream) << key;
                }
                *(stream->nativeStream) << " ";
                if (((key == KWD_KIF_OUT_SLOTS) ||
                    ((key == KWD_KIF_OUT_PUBLIC_SLOTS) ||
                     ((key == KWD_KIF_OUT_METHODS) ||
                      (key == KWD_KIF_OUT_PUBLIC_METHODS)))) &&
                    consP(value)) {
                  *(stream->nativeStream) << "(";
                  { Object* element = NULL;
                    Cons* iter005 = ((Cons*)(value));
                    int i = NULL_INTEGER;
                    int iter006 = 1;

                    for  (; !(iter005 == NIL); 
                          iter005 = iter005->rest,
                          iter006 = iter006 + 1) {
                      element = iter005->value;
                      i = iter006;
                      if (i > 1) {
                        *(stream->nativeStream) << std::endl;
                        printIndent(stream, keyindent + keylength + 2);
                      }
                      if (consP(element)) {
                        helpPrettyPrintRelationDefinitionTree(((Cons*)(element)), stream, startindent + keyindent + keylength + 2, keyindent, false);
                      }
                      else {
                        *(stream->nativeStream) << value;
                      }
                    }
                  }
                  *(stream->nativeStream) << ")";
                }
                else {
                  *(stream->nativeStream) << value;
                }
              }
            }
            { Object* element = NULL;
              Cons* iter007 = tree->nthRest(nofheaderelements);

              for (; !(iter007 == NIL); iter007 = iter007->rest) {
                element = iter007->value;
                *(stream->nativeStream) << std::endl;
                printIndent(stream, keyindent);
                *(stream->nativeStream) << element;
              }
            }
            *(stream->nativeStream) << ")";
            options->free();
          }
        }
      }
    }
  }
}

void prettyPrintAssertion(Proposition* proposition, OutputStream* stream) {
  { Symbol* operatoR = SYM_KIF_OUT_STELLA_ASSERT;
    Surrogate* name = ((Surrogate*)(dynamicSlotValue(proposition->dynamicSlots, SYM_KIF_OUT_STELLA_SURROGATE_VALUE_INVERSE, NULL)));
    TruthValue* truthvalue = ((TruthValue*)(accessInContext(proposition->truthValue, proposition->homeContext, false)));

    if (((boolean)(name))) {
      prettyPrintNamedRule(name, stream);
      return;
    }
    if ((truthvalue == DEFAULT_TRUE_TRUTH_VALUE) ||
        (truthvalue == DEFAULT_FALSE_TRUTH_VALUE)) {
      operatoR = SYM_KIF_OUT_LOGIC_PRESUME;
    }
    else if ((truthvalue == UNKNOWN_TRUTH_VALUE) ||
        (!((boolean)(truthvalue)))) {
      operatoR = SYM_KIF_OUT_STELLA_RETRACT;
    }
    { 
      BIND_STELLA_SPECIAL(oPRINTMODEo, Keyword*, KWD_KIF_OUT_ORIGINAL);
      BIND_STELLA_SPECIAL(oPRINTLOGICALFORMSTREAMo, OutputStream*, stream);
      BIND_STELLA_SPECIAL(oINDENTCOUNTERo, int, 8);
      *(stream->nativeStream) << "(" << operatoR << " ";
      prettyPrintLogicalForm(proposition, stream);
      *(stream->nativeStream) << ")" << std::endl;
    }
  }
}

void prettyPrintNamedRule(Surrogate* rulename, OutputStream* stream) {
  { Symbol* operatoR = SYM_KIF_OUT_LOGIC_DEFRULE;
    Proposition* proposition = ((Proposition*)(rulename->surrogateValue));

    { 
      BIND_STELLA_SPECIAL(oPRINTMODEo, Keyword*, KWD_KIF_OUT_ORIGINAL);
      BIND_STELLA_SPECIAL(oPRINTLOGICALFORMSTREAMo, OutputStream*, stream);
      BIND_STELLA_SPECIAL(oINDENTCOUNTERo, int, 2);
      *(stream->nativeStream) << "(" << operatoR << " " << internSymbolInModule(rulename->symbolName, ((Module*)(rulename->homeContext)), true) << std::endl;
      printIndent(stream, NULL_INTEGER);
      prettyPrintLogicalForm(proposition, stream);
      { Proposition* prop = NULL;
        Cons* iter000 = originatedPropositions(proposition)->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          prop = ((Proposition*)(iter000->value));
          { Keyword* testValue000 = prop->kind;

            if ((testValue000 == KWD_KIF_OUT_PREDICATE) ||
                (testValue000 == KWD_KIF_OUT_FUNCTION)) {
              if ((prop->arguments->length() == 2) &&
                  ((prop->arguments->theArray)[0] == proposition)) {
                *(stream->nativeStream) << std::endl << "  " << prop->operatoR->keywordify() << " ";
                prettyPrintLogicalForm((prop->arguments->theArray)[1], stream);
                continue;
              }
            }
            else {
            }
          }
          *(stream->nativeStream) << std::endl << "  :AXIOMS ";
          prettyPrintLogicalForm(prop, stream);
        }
      }
      *(stream->nativeStream) << ")" << std::endl;
    }
  }
}

Cons* oBUILT_IN_MODULE_NAMESo = NULL;

void printModuleFileHeader(Module* module, OutputStream* stream) {
  clOutputFileHeader(stream, NULL, false);
  if (!(oBUILT_IN_MODULE_NAMESo->memberP(wrapString(module->name())))) {
    module->printDefinition(stream);
  }
  *(stream->nativeStream) << std::endl;
  *(stream->nativeStream) << "(IN-MODULE \"" << module->moduleFullName << "\")" << std::endl << std::endl << "(" << SYM_KIF_OUT_LOGIC_IN_DIALECT << " " << oLOGIC_DIALECTo << ")" << std::endl << std::endl;
}

void printModuleFileTrailer(Module* module, OutputStream* stream) {
  {
    module = module;
    stream = stream;
  }
}

void ObjectStore::storeNativeRelation(Relation* relation) {
  { ObjectStore* store = this;

    relation = relation;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "store-native-relation: not implemented on " << "`" << store << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void ObjectStore::storeRelation(NamedDescription* relation) {
  { ObjectStore* store = this;

    relation = relation;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "store-relation: not implemented on " << "`" << store << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void ObjectStore::storeAssertion(Proposition* proposition) {
  { ObjectStore* store = this;

    proposition = proposition;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "store-proposition: not implemented on " << "`" << store << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void ObjectStore::storeModuleHeader(Module* module) {
  { ObjectStore* store = this;

    module = module;
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "store-module-header: not implemented on " << "`" << store << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void ObjectStore::storeModuleTrailer(Module* module) {
  { ObjectStore* store = this;

    {
      store = store;
      module = module;
    }
  }
}

void ObjectStore::clearObjectStore() {
  { ObjectStore* store = this;

    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "clear-object-store: not implemented on " << "`" << store << "'";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void saveObject(Object* object, Object* store) {
  { Surrogate* testValue000 = safePrimaryType(object);

    if (subtypeOfP(testValue000, SGT_KIF_OUT_STELLA_RELATION)) {
      { Object* object000 = object;
        Relation* object = ((Relation*)(object000));

        { Surrogate* testValue001 = safePrimaryType(store);

          if (subtypeOfP(testValue001, SGT_KIF_OUT_STELLA_OUTPUT_STREAM)) {
            { Object* store000 = store;
              OutputStream* store = ((OutputStream*)(store000));

              prettyPrintRelationDefinition(object, store);
            }
          }
          else if (subtypeOfP(testValue001, SGT_KIF_OUT_LOGIC_OBJECT_STORE)) {
            { Object* store001 = store;
              ObjectStore* store = ((ObjectStore*)(store001));

              store->storeNativeRelation(object);
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_NAMED_DESCRIPTION)) {
      { Object* object001 = object;
        NamedDescription* object = ((NamedDescription*)(object001));

        if (((BooleanWrapper*)(dynamicSlotValue(object->dynamicSlots, SYM_KIF_OUT_LOGIC_UNDECLAREDp, FALSE_WRAPPER)))->wrapperValue) {
          return;
        }
        { Surrogate* testValue002 = safePrimaryType(store);

          if (subtypeOfP(testValue002, SGT_KIF_OUT_STELLA_OUTPUT_STREAM)) {
            { Object* store002 = store;
              OutputStream* store = ((OutputStream*)(store002));

              prettyPrintNamedDescription(object, store);
            }
          }
          else if (subtypeOfP(testValue002, SGT_KIF_OUT_LOGIC_OBJECT_STORE)) {
            { Object* store003 = store;
              ObjectStore* store = ((ObjectStore*)(store003));

              store->storeRelation(object);
            }
          }
          else {
            { OutputStringStream* stream001 = newOutputStringStream();

              *(stream001->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
              throw *newStellaException(stream001->theStringReader());
            }
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_PROPOSITION)) {
      { Object* object002 = object;
        Proposition* object = ((Proposition*)(object002));

        { Surrogate* testValue003 = safePrimaryType(store);

          if (subtypeOfP(testValue003, SGT_KIF_OUT_STELLA_OUTPUT_STREAM)) {
            { Object* store004 = store;
              OutputStream* store = ((OutputStream*)(store004));

              prettyPrintAssertion(object, store);
            }
          }
          else if (subtypeOfP(testValue003, SGT_KIF_OUT_LOGIC_OBJECT_STORE)) {
            { Object* store005 = store;
              ObjectStore* store = ((ObjectStore*)(store005));

              store->storeAssertion(object);
            }
          }
          else {
            { OutputStringStream* stream002 = newOutputStringStream();

              *(stream002->nativeStream) << "`" << testValue003 << "'" << " is not a valid case option";
              throw *newStellaException(stream002->theStringReader());
            }
          }
        }
      }
    }
    else {
      { OutputStringStream* stream003 = newOutputStringStream();

        *(stream003->nativeStream) << "save-object: Don't know how to save " << "`" << object << "'" << " to " << "`" << store << "'";
        throw *newStellaException(stream003->theStringReader());
      }
    }
  }
}

void doSaveModule(Module* module, Object* store) {
  // Save `module' to the persistent store `store' which can
  // either be an output stream or a persistent OBJECT-STORE.
  { 
    BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, module);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      { Surrogate* testValue000 = safePrimaryType(store);

        if (subtypeOfP(testValue000, SGT_KIF_OUT_STELLA_OUTPUT_STREAM)) {
          { Object* store000 = store;
            OutputStream* store = ((OutputStream*)(store000));

            printModuleFileHeader(module, store);
          }
        }
        else if (subtypeOfP(testValue000, SGT_KIF_OUT_LOGIC_OBJECT_STORE)) {
          { Object* store001 = store;
            ObjectStore* store = ((ObjectStore*)(store001));

            store->storeModuleHeader(module);
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      { NamedDescription* description = NULL;
        Iterator* iter000 = allNamedDescriptions(module, true);

        for (; iter000->nextP(); ) {
          description = ((NamedDescription*)(iter000->value));
          if (classDescriptionP(description) &&
              ((boolean)(description->nativeRelation()))) {
            { Class* clasS = ((Class*)(description->nativeRelation()));

              saveObject(clasS, store);
              { Slot* slot = NULL;
                Cons* iter001 = clasS->classLocalSlots->theConsList;

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  slot = ((Slot*)(iter001->value));
                  if (stellaRelationStringifiedSource(slot) != NULL) {
                    saveObject(slot, store);
                  }
                }
              }
            }
          }
          else {
            saveObject(description, store);
          }
        }
      }
      { MethodSlot* function = NULL;
        Iterator* iter002 = allFunctions(module, true);

        for (; iter002->nextP(); ) {
          function = ((MethodSlot*)(iter002->value));
          if (stellaRelationStringifiedSource(function) != NULL) {
            saveObject(function, store);
          }
        }
      }
      { 
        BIND_STELLA_SPECIAL(oEXCLUDEDPROPOSITIONSo, HashTable*, newHashTable());
        excludeOriginatedPropositions();
        { Cons* reversedpropositions = NIL;

          { Proposition* p = NULL;
            Iterator* iter003 = allPropositions(module, false);

            for (; iter003->nextP(); ) {
              p = ((Proposition*)(iter003->value));
              if (locallyModifiedPropositionP(p, module) &&
                  (!excludedPropositionP(p, module))) {
                reversedpropositions = cons(p, reversedpropositions);
              }
            }
          }
          { Object* p = NULL;
            Cons* iter004 = reversedpropositions;

            for (; !(iter004 == NIL); iter004 = iter004->rest) {
              p = iter004->value;
              saveObject(p, store);
            }
          }
        }
      }
      { Surrogate* testValue001 = safePrimaryType(store);

        if (subtypeOfP(testValue001, SGT_KIF_OUT_STELLA_OUTPUT_STREAM)) {
          { Object* store002 = store;
            OutputStream* store = ((OutputStream*)(store002));

            printModuleFileTrailer(module, store);
          }
        }
        else if (subtypeOfP(testValue001, SGT_KIF_OUT_LOGIC_OBJECT_STORE)) {
          { Object* store003 = store;
            ObjectStore* store = ((ObjectStore*)(store003));

            store->storeModuleTrailer(module);
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

void saveModule(Cons* options) {
  // Save all definitions and assertions of the specified :module (which
  // defaults to the current module) to a file or persistent store.  If :file is specified,
  // the KB is saved to that file.  If no :file is specified but the specified :module is
  // associated with a persistent store, the KB will saved to that store, otherwise, an
  // error will be signalled.  The specifics on how a save operation will proceed for a
  // persistent store depends on the particular type of store (see respective documentation).
  // For backwards compatibility, this command also supports the old <module> <file> arguments
  // specified without keywords.
  { Cons* optionslist = options;
    PropertyList* theoptions = parseOptions((keywordP(optionslist->value) ? optionslist : consList(4, KWD_KIF_OUT_MODULE, optionslist->value, KWD_KIF_OUT_FILE, optionslist->rest->value)), listO(5, KWD_KIF_OUT_MODULE, SGT_KIF_OUT_STELLA_MODULE, KWD_KIF_OUT_FILE, SGT_KIF_OUT_STELLA_STRING, NIL), true, false);
    Module* themodule = ((Module*)(theoptions->lookupWithDefault(KWD_KIF_OUT_MODULE, oMODULEo)));
    StringWrapper* file = ((StringWrapper*)(theoptions->lookupWithDefault(KWD_KIF_OUT_FILE, NULL)));

    if (((boolean)(themodule)) &&
        ((boolean)(file))) {
      plLog(KWD_KIF_OUT_MEDIUM, 5, wrapString("Saving module "), wrapString(themodule->moduleFullName), wrapString(" to "), file, wrapString("..."));
      { OutputFileStream* stream = NULL;

        try {
          stream = openOutputFile(file->wrapperValue, 0);
          doSaveModule(themodule, stream);
        }
catch (...) {
          if (((boolean)(stream))) {
            stream->free();
          }
          throw;
        }
        if (((boolean)(stream))) {
          stream->free();
        }
      }
    }
    else if (((boolean)(themodule)) &&
        ((boolean)(((ObjectStore*)(dynamicSlotValue(themodule->dynamicSlots, SYM_KIF_OUT_LOGIC_OBJECT_STORE, NULL)))))) {
      plLog(KWD_KIF_OUT_MEDIUM, 3, wrapString("Saving module "), wrapString(themodule->moduleFullName), wrapString(" to the associated store..."));
      doSaveModule(themodule, ((ObjectStore*)(dynamicSlotValue(themodule->dynamicSlots, SYM_KIF_OUT_LOGIC_OBJECT_STORE, NULL))));
    }
    else if (!((boolean)(file))) {
      throw *newStellaException("save-module: no file or persistent store specified to save to");
    }
  }
}

void saveModuleEvaluatorWrapper(Cons* arguments) {
  saveModule(arguments);
}

void helpStartupKifOut1() {
  {
    SGT_KIF_OUT_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    SYM_KIF_OUT_LOGIC_IO_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("IO-VARIABLES", NULL, 0)));
    SGT_KIF_OUT_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
    SGT_KIF_OUT_STELLA_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("VECTOR", getStellaModule("/STELLA", true), 1)));
    SGT_KIF_OUT_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    SGT_KIF_OUT_STELLA_LIST = ((Surrogate*)(internRigidSymbolWrtModule("LIST", getStellaModule("/STELLA", true), 1)));
    KWD_KIF_OUT_KIF = ((Keyword*)(internRigidSymbolWrtModule("KIF", NULL, 2)));
    KWD_KIF_OUT_STELLA = ((Keyword*)(internRigidSymbolWrtModule("STELLA", NULL, 2)));
    KWD_KIF_OUT_PREFIX_STELLA = ((Keyword*)(internRigidSymbolWrtModule("PREFIX-STELLA", NULL, 2)));
    KWD_KIF_OUT_SQL = ((Keyword*)(internRigidSymbolWrtModule("SQL", NULL, 2)));
    SGT_KIF_OUT_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", NULL, 1)));
    SGT_KIF_OUT_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", NULL, 1)));
    SGT_KIF_OUT_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
    SGT_KIF_OUT_STELLA_COLLECTION = ((Surrogate*)(internRigidSymbolWrtModule("COLLECTION", getStellaModule("/STELLA", true), 1)));
    SGT_KIF_OUT_LOGIC_LOGIC_THING = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-THING", NULL, 1)));
    SGT_KIF_OUT_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
    KWD_KIF_OUT_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    KWD_KIF_OUT_REALISTIC = ((Keyword*)(internRigidSymbolWrtModule("REALISTIC", NULL, 2)));
    KWD_KIF_OUT_ORIGINAL = ((Keyword*)(internRigidSymbolWrtModule("ORIGINAL", NULL, 2)));
    KWD_KIF_OUT_UNESCAPED = ((Keyword*)(internRigidSymbolWrtModule("UNESCAPED", NULL, 2)));
    KWD_KIF_OUT_ESCAPED = ((Keyword*)(internRigidSymbolWrtModule("ESCAPED", NULL, 2)));
    KWD_KIF_OUT_COMPLEX_ESCAPED = ((Keyword*)(internRigidSymbolWrtModule("COMPLEX-ESCAPED", NULL, 2)));
    SGT_KIF_OUT_STELLA_FALSE = ((Surrogate*)(internRigidSymbolWrtModule("FALSE", getStellaModule("/STELLA", true), 1)));
    SGT_KIF_OUT_PL_KERNEL_KB_NOT = ((Surrogate*)(internRigidSymbolWrtModule("NOT", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_KIF_OUT_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    KWD_KIF_OUT_OR = ((Keyword*)(internRigidSymbolWrtModule("OR", NULL, 2)));
    SGT_KIF_OUT_PL_KERNEL_KB_AND = ((Surrogate*)(internRigidSymbolWrtModule("AND", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_KIF_OUT_PL_KERNEL_KB_OR = ((Surrogate*)(internRigidSymbolWrtModule("OR", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_KIF_OUT_NOT = ((Keyword*)(internRigidSymbolWrtModule("NOT", NULL, 2)));
    KWD_KIF_OUT_EQUIVALENT = ((Keyword*)(internRigidSymbolWrtModule("EQUIVALENT", NULL, 2)));
    KWD_KIF_OUT_PREDICATE = ((Keyword*)(internRigidSymbolWrtModule("PREDICATE", NULL, 2)));
    SGT_KIF_OUT_PL_KERNEL_KB_FORK = ((Surrogate*)(internRigidSymbolWrtModule("FORK", getStellaModule("/PL-KERNEL-KB", true), 1)));
    KWD_KIF_OUT_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    KWD_KIF_OUT_IMPLIES = ((Keyword*)(internRigidSymbolWrtModule("IMPLIES", NULL, 2)));
    KWD_KIF_OUT_FORALL = ((Keyword*)(internRigidSymbolWrtModule("FORALL", NULL, 2)));
    KWD_KIF_OUT_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("EXISTS", NULL, 2)));
    KWD_KIF_OUT_CONSTANT = ((Keyword*)(internRigidSymbolWrtModule("CONSTANT", NULL, 2)));
    KWD_KIF_OUT_CONTAINED_BY = ((Keyword*)(internRigidSymbolWrtModule("CONTAINED-BY", NULL, 2)));
    KWD_KIF_OUT_DELETED = ((Keyword*)(internRigidSymbolWrtModule("DELETED", NULL, 2)));
    SGT_KIF_OUT_PL_KERNEL_KB_SUBSET_OF = ((Surrogate*)(internRigidSymbolWrtModule("SUBSET-OF", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_KIF_OUT_LOGIC_FORWARD_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("FORWARD-ONLY?", NULL, 0)));
    SGT_KIF_OUT_PL_KERNEL_KB_le = ((Surrogate*)(internRigidSymbolWrtModule("<=", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_KIF_OUT_PL_KERNEL_KB_FORALL = ((Surrogate*)(internRigidSymbolWrtModule("FORALL", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_KIF_OUT_PL_KERNEL_KB_EXISTS = ((Surrogate*)(internRigidSymbolWrtModule("EXISTS", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_KIF_OUT_PL_KERNEL_KB_SETOF = ((Surrogate*)(internRigidSymbolWrtModule("SETOF", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_KIF_OUT_PL_KERNEL_KB_LISTOF = ((Surrogate*)(internRigidSymbolWrtModule("LISTOF", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_KIF_OUT_LOGIC_COMPLEMENT_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("COMPLEMENT-DESCRIPTION", NULL, 0)));
    SGT_KIF_OUT_PL_KERNEL_KB_KAPPA = ((Surrogate*)(internRigidSymbolWrtModule("KAPPA", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_KIF_OUT_PL_KERNEL_KB_eg = ((Surrogate*)(internRigidSymbolWrtModule("=>", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_KIF_OUT_PL_KERNEL_KB_egg = ((Surrogate*)(internRigidSymbolWrtModule("=>>", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_KIF_OUT_LOGIC_BACKWARD_ONLYp = ((Symbol*)(internRigidSymbolWrtModule("BACKWARD-ONLY?", NULL, 0)));
    SGT_KIF_OUT_PL_KERNEL_KB_lle = ((Surrogate*)(internRigidSymbolWrtModule("<<=", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_KIF_OUT_PL_KERNEL_KB_lt = ((Surrogate*)(internRigidSymbolWrtModule("<~", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_KIF_OUT_PL_KERNEL_KB_tg = ((Surrogate*)(internRigidSymbolWrtModule("~>", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_KIF_OUT_PL_KERNEL_KB_llt = ((Surrogate*)(internRigidSymbolWrtModule("<<~", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_KIF_OUT_PL_KERNEL_KB_tgg = ((Surrogate*)(internRigidSymbolWrtModule("~>>", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SGT_KIF_OUT_PL_KERNEL_KB_HIDDEN_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("HIDDEN-RELATION", getStellaModule("/PL-KERNEL-KB", true), 1)));
    SYM_KIF_OUT_LOGIC_MASTER_PROPOSITION = ((Symbol*)(internRigidSymbolWrtModule("MASTER-PROPOSITION", NULL, 0)));
    SYM_KIF_OUT_LOGIC_ASSERTED_BY_TYPE_CHECKERp = ((Symbol*)(internRigidSymbolWrtModule("ASSERTED-BY-TYPE-CHECKER?", NULL, 0)));
    KWD_KIF_OUT_TERSE = ((Keyword*)(internRigidSymbolWrtModule("TERSE", NULL, 2)));
  }
}

void helpStartupKifOut2() {
  {
    KWD_KIF_OUT_VERBOSE = ((Keyword*)(internRigidSymbolWrtModule("VERBOSE", NULL, 2)));
    KWD_KIF_OUT_SOURCE = ((Keyword*)(internRigidSymbolWrtModule("SOURCE", NULL, 2)));
    KWD_KIF_OUT_SLOTS = ((Keyword*)(internRigidSymbolWrtModule("SLOTS", NULL, 2)));
    KWD_KIF_OUT_PUBLIC_SLOTS = ((Keyword*)(internRigidSymbolWrtModule("PUBLIC-SLOTS", NULL, 2)));
    KWD_KIF_OUT_METHODS = ((Keyword*)(internRigidSymbolWrtModule("METHODS", NULL, 2)));
    KWD_KIF_OUT_PUBLIC_METHODS = ((Keyword*)(internRigidSymbolWrtModule("PUBLIC-METHODS", NULL, 2)));
    SYM_KIF_OUT_STELLA_ASSERT = ((Symbol*)(internRigidSymbolWrtModule("ASSERT", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_OUT_STELLA_SURROGATE_VALUE_INVERSE = ((Symbol*)(internRigidSymbolWrtModule("SURROGATE-VALUE-INVERSE", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_OUT_LOGIC_PRESUME = ((Symbol*)(internRigidSymbolWrtModule("PRESUME", NULL, 0)));
    SYM_KIF_OUT_STELLA_RETRACT = ((Symbol*)(internRigidSymbolWrtModule("RETRACT", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_OUT_LOGIC_DEFRULE = ((Symbol*)(internRigidSymbolWrtModule("DEFRULE", NULL, 0)));
    SYM_KIF_OUT_LOGIC_IN_DIALECT = ((Symbol*)(internRigidSymbolWrtModule("IN-DIALECT", NULL, 0)));
    SGT_KIF_OUT_STELLA_RELATION = ((Surrogate*)(internRigidSymbolWrtModule("RELATION", getStellaModule("/STELLA", true), 1)));
    SGT_KIF_OUT_STELLA_OUTPUT_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("OUTPUT-STREAM", getStellaModule("/STELLA", true), 1)));
    SGT_KIF_OUT_LOGIC_OBJECT_STORE = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT-STORE", NULL, 1)));
    SGT_KIF_OUT_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
    SYM_KIF_OUT_LOGIC_UNDECLAREDp = ((Symbol*)(internRigidSymbolWrtModule("UNDECLARED?", NULL, 0)));
    KWD_KIF_OUT_MODULE = ((Keyword*)(internRigidSymbolWrtModule("MODULE", NULL, 2)));
    KWD_KIF_OUT_FILE = ((Keyword*)(internRigidSymbolWrtModule("FILE", NULL, 2)));
    SGT_KIF_OUT_STELLA_MODULE = ((Surrogate*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 1)));
    SGT_KIF_OUT_STELLA_STRING = ((Surrogate*)(internRigidSymbolWrtModule("STRING", getStellaModule("/STELLA", true), 1)));
    KWD_KIF_OUT_MEDIUM = ((Keyword*)(internRigidSymbolWrtModule("MEDIUM", NULL, 2)));
    SYM_KIF_OUT_LOGIC_OBJECT_STORE = ((Symbol*)(internRigidSymbolWrtModule("OBJECT-STORE", NULL, 0)));
    SYM_KIF_OUT_LOGIC_STARTUP_KIF_OUT = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-KIF-OUT", NULL, 0)));
    SYM_KIF_OUT_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupKifOut3() {
  {
    defineFunctionObject("REGISTER-LOGIC-DIALECT-PRINT-FUNCTION", "(DEFUN REGISTER-LOGIC-DIALECT-PRINT-FUNCTION ((DIALECT KEYWORD) (FN FUNCTION-CODE-WRAPPER)) :DOCUMENTATION \"Register `fn' as a logic-object print function for `dialect'.\nEach function should have the signature `((self OBJECT) (stream OUTPUT-STREAM))'.\nAny return values will be ignored.\" :PUBLIC? TRUE)", ((cpp_function_code)(&registerLogicDialectPrintFunction)), NULL);
    defineFunctionObject("PUSH-QUANTIFIED-OBJECT", "(DEFUN PUSH-QUANTIFIED-OBJECT ((OBJECT OBJECT)))", ((cpp_function_code)(&pushQuantifiedObject)), NULL);
    defineFunctionObject("POP-QUANTIFIED-OBJECT", "(DEFUN POP-QUANTIFIED-OBJECT ())", ((cpp_function_code)(&popQuantifiedObject)), NULL);
    defineFunctionObject("QUANTIFIED-OBJECT-VARIABLE?", "(DEFUN (QUANTIFIED-OBJECT-VARIABLE? BOOLEAN) ((VAR SKOLEM)))", ((cpp_function_code)(&quantifiedObjectVariableP)), NULL);
    defineFunctionObject("MAYBE-DOWNCASE", "(DEFUN (MAYBE-DOWNCASE STRING) ((STRING STRING)))", ((cpp_function_code)(&maybeDowncase)), NULL);
    defineFunctionObject("INCREASE-INDENT", "(DEFUN INCREASE-INDENT ((INDENT INTEGER)))", ((cpp_function_code)(&increaseIndent)), NULL);
    defineFunctionObject("DECREASE-INDENT", "(DEFUN DECREASE-INDENT ((INDENT INTEGER)))", ((cpp_function_code)(&decreaseIndent)), NULL);
    defineFunctionObject("PRINT-INDENT", "(DEFUN PRINT-INDENT ((STREAM OUTPUT-STREAM) (INDENT INTEGER)))", ((cpp_function_code)(&printIndent)), NULL);
    defineFunctionObject("PRINT-LOGICAL-FORM-IN-DIALECT", "(DEFUN PRINT-LOGICAL-FORM-IN-DIALECT ((SELF OBJECT) (DIALECT KEYWORD) (STREAM OUTPUT-STREAM)) :PUBLIC? TRUE :DOCUMENTATION \"Produce a stringified version of a logical representation\nof 'self' and write it to the stream 'stream'.  Use the dialect 'dialect',\nor use the current dialect if 'dialect' is NULL.\")", ((cpp_function_code)(&printLogicalFormInDialect)), NULL);
    defineFunctionObject("PRINT-LOGICAL-FORM", "(DEFUN PRINT-LOGICAL-FORM ((FORM OBJECT) (STREAM OUTPUT-STREAM)) :PUBLIC? TRUE :DOCUMENTATION \"Print the logical form `form' to `stream' according to\nthe current setting of `*logic-dialect*'.  Pretty-printing is controlled\nby the current setting of `*prettyPrintLogicalForms?*'.\")", ((cpp_function_code)(&printLogicalForm)), NULL);
    defineFunctionObject("PRETTY-PRINT-LOGICAL-FORM", "(DEFUN PRETTY-PRINT-LOGICAL-FORM ((FORM OBJECT) (STREAM OUTPUT-STREAM)) :PUBLIC? TRUE :DOCUMENTATION \"Pretty-print the logical form `form' to `stream' according\nto the current setting of `*logic-dialect*'.\")", ((cpp_function_code)(&prettyPrintLogicalForm)), NULL);
    defineFunctionObject("PRINT-UNFORMATTED-LOGICAL-FORM", "(DEFUN PRINT-UNFORMATTED-LOGICAL-FORM ((FORM OBJECT) (STREAM OUTPUT-STREAM)) :PUBLIC? TRUE :DOCUMENTATION \"Print the logical form `form' to `stream' according to\nthe current setting of `*logic-dialect*'.  Pretty-printing is explicitly\nforced to be turned off.\")", ((cpp_function_code)(&printUnformattedLogicalForm)), NULL);
    defineFunctionObject("PRINT-FORMULA", "(DEFUN PRINT-FORMULA ((FORMULA OBJECT) (INDENT INTEGER)))", ((cpp_function_code)(&printFormula)), NULL);
    defineFunctionObject("PRINT-AS-KIF", "(DEFUN PRINT-AS-KIF ((SELF OBJECT) (STREAM OUTPUT-STREAM)) :PUBLIC? TRUE)", ((cpp_function_code)(&printAsKif)), NULL);
    defineFunctionObject("PRINT-AS-KIF-INTERNAL", "(DEFUN PRINT-AS-KIF-INTERNAL ((SELF OBJECT)))", ((cpp_function_code)(&printAsKifInternal)), NULL);
    defineFunctionObject("VISIBLE-ARGUMENT?", "(DEFUN (VISIBLE-ARGUMENT? BOOLEAN) ((SELF OBJECT)))", ((cpp_function_code)(&visibleArgumentP)), NULL);
    defineFunctionObject("VISIBLE-ARGUMENTS-COUNT", "(DEFUN (VISIBLE-ARGUMENTS-COUNT INTEGER) ((ARGUMENTS ARGUMENTS-VECTOR)))", ((cpp_function_code)(&visibleArgumentsCount)), NULL);
    defineFunctionObject("PRINT-KIF-ARGUMENTS", "(DEFUN PRINT-KIF-ARGUMENTS ((ARGUMENTS ARGUMENTS-VECTOR) (SEPARATELINES? BOOLEAN) (OMITLASTARGUMENT? BOOLEAN)))", ((cpp_function_code)(&printKifArguments)), NULL);
    defineFunctionObject("PRINT-KIF-OPERATOR-WITH-ARGUMENTS", "(DEFUN PRINT-KIF-OPERATOR-WITH-ARGUMENTS ((OPERATOR STRING) (ARGUMENTS ARGUMENTS-VECTOR) (SEPARATELINES? BOOLEAN) (OMITLASTARGUMENT? BOOLEAN)))", ((cpp_function_code)(&printKifOperatorWithArguments)), NULL);
    defineFunctionObject("STRINGIFIED-SURROGATE", "(DEFUN (STRINGIFIED-SURROGATE STRING) ((OPERATOR SURROGATE)))", ((cpp_function_code)(&stringifiedSurrogate)), NULL);
    defineFunctionObject("STRINGIFIED-KIF-OPERATOR", "(DEFUN (STRINGIFIED-KIF-OPERATOR STRING) ((SELF PROPOSITION)))", ((cpp_function_code)(&stringifiedKifOperator)), NULL);
    defineFunctionObject("PRINT-KIF-PROPOSITION", "(DEFUN PRINT-KIF-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&printKifProposition)), NULL);
    defineFunctionObject("HELP-PRINT-KIF-PROPOSITION", "(DEFUN HELP-PRINT-KIF-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&helpPrintKifProposition)), NULL);
    defineFunctionObject("PRINT-KIF-FUNCTION-PROPOSITION", "(DEFUN PRINT-KIF-FUNCTION-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&printKifFunctionProposition)), NULL);
    defineFunctionObject("PRINT-KIF-FUNCTION-EXPRESSION", "(DEFUN PRINT-KIF-FUNCTION-EXPRESSION ((SELF PROPOSITION)))", ((cpp_function_code)(&printKifFunctionExpression)), NULL);
    defineFunctionObject("PRINT-KIF-IMPLIES-PROPOSITION", "(DEFUN PRINT-KIF-IMPLIES-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&printKifImpliesProposition)), NULL);
    defineFunctionObject("PRINT-KIF-QUANTIFIED-VARIABLES", "(DEFUN PRINT-KIF-QUANTIFIED-VARIABLES ((VARIABLES (VECTOR OF SKOLEM)) (INCLUDETYPES? BOOLEAN)))", ((cpp_function_code)(&printKifQuantifiedVariables)), NULL);
    defineFunctionObject("PRINT-KIF-QUANTIFICATION", "(DEFUN PRINT-KIF-QUANTIFICATION ((SELF PROPOSITION)))", ((cpp_function_code)(&printKifQuantification)), NULL);
    defineFunctionObject("PRINT-KIF-TOP-LEVEL-EXISTS-PROPOSITION", "(DEFUN PRINT-KIF-TOP-LEVEL-EXISTS-PROPOSITION ((SELF PROPOSITION)))", ((cpp_function_code)(&printKifTopLevelExistsProposition)), NULL);
    defineFunctionObject("PRINT-KIF-WRAPPER", "(DEFUN PRINT-KIF-WRAPPER ((SELF LITERAL-WRAPPER)))", ((cpp_function_code)(&printKifWrapper)), NULL);
    defineFunctionObject("PRINT-KIF-LOGIC-OBJECT", "(DEFUN PRINT-KIF-LOGIC-OBJECT ((SELF LOGIC-OBJECT)))", ((cpp_function_code)(&printKifLogicObject)), NULL);
    defineFunctionObject("PRINT-KIF-SKOLEM", "(DEFUN PRINT-KIF-SKOLEM ((SELF SKOLEM) (SUPPRESSDEFININGPROPOSITION? BOOLEAN)))", ((cpp_function_code)(&printKifSkolem)), NULL);
    defineFunctionObject("PRINT-KIF-VARIABLE", "(DEFUN PRINT-KIF-VARIABLE ((SELF PATTERN-VARIABLE)))", ((cpp_function_code)(&printKifVariable)), NULL);
    defineFunctionObject("PRINT-KIF-STELLA-COLLECTION", "(DEFUN PRINT-KIF-STELLA-COLLECTION ((SELF COLLECTION)))", ((cpp_function_code)(&printKifStellaCollection)), NULL);
    defineFunctionObject("PRINT-KIF-DESCRIPTION", "(DEFUN PRINT-KIF-DESCRIPTION ((SELF DESCRIPTION)))", ((cpp_function_code)(&printKifDescription)), NULL);
    defineFunctionObject("PRINT-KIF-DESCRIPTION-PROPOSITION", "(DEFUN PRINT-KIF-DESCRIPTION-PROPOSITION ((SELF DESCRIPTION) (INVERT? BOOLEAN)))", ((cpp_function_code)(&printKifDescriptionProposition)), NULL);
    defineFunctionObject("CHOOSE-IMPLICATION-OPERATOR", "(DEFUN (CHOOSE-IMPLICATION-OPERATOR SURROGATE) ((RULE PROPOSITION) (FORWARD? BOOLEAN)))", ((cpp_function_code)(&chooseImplicationOperator)), NULL);
    defineFunctionObject("CREATE-SKOLEM-MAPPING-TABLE", "(DEFUN (CREATE-SKOLEM-MAPPING-TABLE ENTITY-MAPPING) ((OLDVARS VARIABLES-VECTOR) (NEWVARS VARIABLES-VECTOR)))", ((cpp_function_code)(&createSkolemMappingTable)), NULL);
    defineFunctionObject("PRINT-DESCRIPTIONS-AS-KIF-RULE", "(DEFUN PRINT-DESCRIPTIONS-AS-KIF-RULE ((HEAD DESCRIPTION) (TAIL DESCRIPTION) (RULE PROPOSITION) (REVERSEPOLARITY? BOOLEAN)))", ((cpp_function_code)(&printDescriptionsAsKifRule)), NULL);
    defineFunctionObject("EXCLUDE-ORIGINATED-PROPOSITIONS", "(DEFUN EXCLUDE-ORIGINATED-PROPOSITIONS ())", ((cpp_function_code)(&excludeOriginatedPropositions)), NULL);
    defineFunctionObject("HIDDEN-RELATION?", "(DEFUN (HIDDEN-RELATION? BOOLEAN) ((RELATION-REF SURROGATE)))", ((cpp_function_code)(&hiddenRelationP)), NULL);
    defineFunctionObject("EXCLUDED-PROPOSITION?", "(DEFUN (EXCLUDED-PROPOSITION? BOOLEAN) ((PROPOSITION PROPOSITION) (MODULE MODULE)))", ((cpp_function_code)(&excludedPropositionP)), NULL);
    defineFunctionObject("PRETTY-PRINT-NAMED-DESCRIPTION", "(DEFUN PRETTY-PRINT-NAMED-DESCRIPTION ((SELF NAMED-DESCRIPTION) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&prettyPrintNamedDescription)), NULL);
    defineMethodObject("(DEFMETHOD DESCRIBE-OBJECT ((SELF NAMED-DESCRIPTION) (STREAM OUTPUT-STREAM) (MODE KEYWORD)) :DOCUMENTATION \"Prints a description of 'self' to stream 'stream'.  'mode'\ncan be :terse, :verbose, or :source.  Used by `describe'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NamedDescription::describeObject))), NULL);
    defineFunctionObject("STELLA-RELATION-STRINGIFIED-SOURCE", "(DEFUN (STELLA-RELATION-STRINGIFIED-SOURCE STRING) ((SELF RELATION)))", ((cpp_function_code)(&stellaRelationStringifiedSource)), NULL);
    defineFunctionObject("PRETTY-PRINT-RELATION-DEFINITION", "(DEFUN PRETTY-PRINT-RELATION-DEFINITION ((SELF RELATION) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&prettyPrintRelationDefinition)), NULL);
    defineFunctionObject("PRETTY-PRINT-RELATION-DEFINITION-TREE", "(DEFUN PRETTY-PRINT-RELATION-DEFINITION-TREE ((TREE CONS) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&prettyPrintRelationDefinitionTree)), NULL);
    defineFunctionObject("HELP-PRETTY-PRINT-RELATION-DEFINITION-TREE", "(DEFUN HELP-PRETTY-PRINT-RELATION-DEFINITION-TREE ((TREE CONS) (STREAM OUTPUT-STREAM) (STARTINDENT INTEGER) (KEYINDENT INTEGER) (FORCEFIRSTKEYONSEPARATELINE? BOOLEAN)))", ((cpp_function_code)(&helpPrettyPrintRelationDefinitionTree)), NULL);
    defineFunctionObject("PRETTY-PRINT-ASSERTION", "(DEFUN PRETTY-PRINT-ASSERTION ((PROPOSITION PROPOSITION) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&prettyPrintAssertion)), NULL);
    defineFunctionObject("PRETTY-PRINT-NAMED-RULE", "(DEFUN PRETTY-PRINT-NAMED-RULE ((RULENAME SURROGATE) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&prettyPrintNamedRule)), NULL);
    defineFunctionObject("PRINT-MODULE-FILE-HEADER", "(DEFUN PRINT-MODULE-FILE-HEADER ((MODULE MODULE) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printModuleFileHeader)), NULL);
    defineFunctionObject("PRINT-MODULE-FILE-TRAILER", "(DEFUN PRINT-MODULE-FILE-TRAILER ((MODULE MODULE) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printModuleFileTrailer)), NULL);
    defineMethodObject("(DEFMETHOD STORE-NATIVE-RELATION ((STORE OBJECT-STORE) (RELATION RELATION)))", wrapMethodCode(((cpp_method_code)(&ObjectStore::storeNativeRelation))), NULL);
    defineMethodObject("(DEFMETHOD STORE-RELATION ((STORE OBJECT-STORE) (RELATION NAMED-DESCRIPTION)))", wrapMethodCode(((cpp_method_code)(&ObjectStore::storeRelation))), NULL);
    defineMethodObject("(DEFMETHOD STORE-ASSERTION ((STORE OBJECT-STORE) (PROPOSITION PROPOSITION)))", wrapMethodCode(((cpp_method_code)(&ObjectStore::storeAssertion))), NULL);
    defineMethodObject("(DEFMETHOD STORE-MODULE-HEADER ((STORE OBJECT-STORE) (MODULE MODULE)))", wrapMethodCode(((cpp_method_code)(&ObjectStore::storeModuleHeader))), NULL);
    defineMethodObject("(DEFMETHOD STORE-MODULE-TRAILER ((STORE OBJECT-STORE) (MODULE MODULE)))", wrapMethodCode(((cpp_method_code)(&ObjectStore::storeModuleTrailer))), NULL);
    defineMethodObject("(DEFMETHOD CLEAR-OBJECT-STORE ((STORE OBJECT-STORE)))", wrapMethodCode(((cpp_method_code)(&ObjectStore::clearObjectStore))), NULL);
    defineFunctionObject("SAVE-OBJECT", "(DEFUN SAVE-OBJECT ((OBJECT OBJECT) (STORE OBJECT)))", ((cpp_function_code)(&saveObject)), NULL);
    defineFunctionObject("DO-SAVE-MODULE", "(DEFUN DO-SAVE-MODULE ((MODULE MODULE) (STORE OBJECT)) :DOCUMENTATION \"Save `module' to the persistent store `store' which can\neither be an output stream or a persistent OBJECT-STORE.\" :PUBLIC? TRUE)", ((cpp_function_code)(&doSaveModule)), NULL);
  }
}

void startupKifOut() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupKifOut1();
      helpStartupKifOut2();
    }
    if (currentStartupTimePhaseP(4)) {
      oLOGIC_DIALECT_PRINT_FUNCTIONSo = newKeyValueList();
      oBUILT_IN_MODULE_NAMESo = getQuotedTree("((\"PL-USER\" \"PL-KERNEL-KB\" \"PLI\" \"LOOM-API\" \"CYC-FRAME-ONTOLOGY\" \"KIF-FRAME-ONTOLOGY\" \"IDL-THEORY\" \"IDL-USER-THEORY\" \"LOGIC\" \"STELLA\" \"COMMON-LISP\") \"/LOGIC\")", "/LOGIC");
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupKifOut3();
      defineFunctionObject("SAVE-MODULE", "(DEFUN SAVE-MODULE (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Save all definitions and assertions of the specified :module (which\ndefaults to the current module) to a file or persistent store.  If :file is specified,\nthe KB is saved to that file.  If no :file is specified but the specified :module is\nassociated with a persistent store, the KB will saved to that store, otherwise, an\nerror will be signalled.  The specifics on how a save operation will proceed for a\npersistent store depends on the particular type of store (see respective documentation).\nFor backwards compatibility, this command also supports the old <module> <file> arguments\nspecified without keywords.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&saveModule)), ((cpp_function_code)(&saveModuleEvaluatorWrapper)));
      defineFunctionObject("STARTUP-KIF-OUT", "(DEFUN STARTUP-KIF-OUT () :PUBLIC? TRUE)", ((cpp_function_code)(&startupKifOut)), NULL);
      { MethodSlot* function = lookupFunction(SYM_KIF_OUT_LOGIC_STARTUP_KIF_OUT);

        setDynamicSlotValue(function->dynamicSlots, SYM_KIF_OUT_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupKifOut"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFSPECIAL *PRETTYPRINTLOGICALFORMS?* BOOLEAN FALSE :PUBLIC? TRUE :DOCUMENTATION \"Controls whether logical forms print on single lines\n(unformatted) or multi-line indented.\")", &oPRETTYPRINTLOGICALFORMSpo);
      defineGlobalVariableObject("(DEFSPECIAL *PRETTYPRINTKIF?* BOOLEAN FALSE :PUBLIC? TRUE :DOCUMENTATION \"Controls whether KIF expressions print on single lines\n(unformatted) or multi-line indented.\")", &oPRETTYPRINTKIFpo);
      defineGlobalVariableObject("(DEFSPECIAL *PRINTLOGICALFORMSTREAM* OUTPUT-STREAM NULL :PUBLIC? TRUE :DOCUMENTATION \"Eliminates necessity of passing stream argument\nthroughout 'print-logical-form' functions.\")", &oPRINTLOGICALFORMSTREAMo);
      defineGlobalVariableObject("(DEFSPECIAL *DOWNCASEOPERATORS?* BOOLEAN FALSE :PUBLIC? TRUE :DOCUMENTATION \"Controls whether down-casing happens during logical\nform printing (leading to lots more string garbage).\")", &oDOWNCASEOPERATORSpo);
      defineGlobalVariableObject("(DEFGLOBAL *LOGIC-DIALECT-PRINT-FUNCTIONS* (KEY-VALUE-LIST OF KEYWORD FUNCTION-CODE-WRAPPER) (NEW (KEY-VALUE-LIST OF KEYWORD FUNCTION-CODE-WRAPPER)) :DOCUMENTATION \"Table to allow extension of the logical form printing code\nby associating keywords with print functions.  Should have values added only\nvia the associated function REGISTER-LOGIC-DIALECT-PRINT-FUNCTION.\")", &oLOGIC_DIALECT_PRINT_FUNCTIONSo);
      defineGlobalVariableObject("(DEFSPECIAL *PRINTQUANTIFIEDOBJECTSSTACK* CONS NULL :DOCUMENTATION \"Used to register objects that quantify variables, so we\ncan decide in certain contexts whether to print a variable or its value.\")", &oPRINTQUANTIFIEDOBJECTSSTACKo);
      defineGlobalVariableObject("(DEFSPECIAL *INDENTCOUNTER* INTEGER 0 :PUBLIC? TRUE :DOCUMENTATION \"The number of spaces prepended during printing a logical form.\")", &oINDENTCOUNTERo);
      defineGlobalVariableObject("(DEFGLOBAL *INDENT-QUANTUM* INTEGER 3 :PUBLIC? TRUE :DOCUMENTATION \"The number of spaces added by a call to 'increase-indent'.\")", &oINDENT_QUANTUMo);
      defineGlobalVariableObject("(DEFSPECIAL *TOPLEVELPRINTKIFPROPOSITION?* BOOLEAN TRUE)", &oTOPLEVELPRINTKIFPROPOSITIONpo);
      defineGlobalVariableObject("(DEFSPECIAL *EXCLUDEDPROPOSITIONS* (HASH-TABLE OF PROPOSITION BOOLEAN-WRAPPER) NULL :PUBLIC? TRUE :DOCUMENTATION \"List of propositions that shouldn't be saved by `save-module'.\")", &oEXCLUDEDPROPOSITIONSo);
      defineGlobalVariableObject("(DEFGLOBAL *BUILT-IN-MODULE-NAMES* (CONS OF STRING-WRAPPER) (QUOTE (\"PL-USER\" \"PL-KERNEL-KB\" \"PLI\" \"LOOM-API\" \"CYC-FRAME-ONTOLOGY\" \"KIF-FRAME-ONTOLOGY\" \"IDL-THEORY\" \"IDL-USER-THEORY\" \"LOGIC\" \"STELLA\" \"COMMON-LISP\")))", &oBUILT_IN_MODULE_NAMESo);
    }
  }
}

Surrogate* SGT_KIF_OUT_LOGIC_PROPOSITION = NULL;

Symbol* SYM_KIF_OUT_LOGIC_IO_VARIABLES = NULL;

Surrogate* SGT_KIF_OUT_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_KIF_OUT_STELLA_VECTOR = NULL;

Surrogate* SGT_KIF_OUT_STELLA_CONS = NULL;

Surrogate* SGT_KIF_OUT_STELLA_LIST = NULL;

Keyword* KWD_KIF_OUT_KIF = NULL;

Keyword* KWD_KIF_OUT_STELLA = NULL;

Keyword* KWD_KIF_OUT_PREFIX_STELLA = NULL;

Keyword* KWD_KIF_OUT_SQL = NULL;

Surrogate* SGT_KIF_OUT_LOGIC_PATTERN_VARIABLE = NULL;

Surrogate* SGT_KIF_OUT_LOGIC_SKOLEM = NULL;

Surrogate* SGT_KIF_OUT_LOGIC_LOGIC_OBJECT = NULL;

Surrogate* SGT_KIF_OUT_STELLA_COLLECTION = NULL;

Surrogate* SGT_KIF_OUT_LOGIC_LOGIC_THING = NULL;

Surrogate* SGT_KIF_OUT_STELLA_THING = NULL;

Keyword* KWD_KIF_OUT_ISA = NULL;

Keyword* KWD_KIF_OUT_REALISTIC = NULL;

Keyword* KWD_KIF_OUT_ORIGINAL = NULL;

Keyword* KWD_KIF_OUT_UNESCAPED = NULL;

Keyword* KWD_KIF_OUT_ESCAPED = NULL;

Keyword* KWD_KIF_OUT_COMPLEX_ESCAPED = NULL;

Surrogate* SGT_KIF_OUT_STELLA_FALSE = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_NOT = NULL;

Keyword* KWD_KIF_OUT_AND = NULL;

Keyword* KWD_KIF_OUT_OR = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_AND = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_OR = NULL;

Keyword* KWD_KIF_OUT_NOT = NULL;

Keyword* KWD_KIF_OUT_EQUIVALENT = NULL;

Keyword* KWD_KIF_OUT_PREDICATE = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_FORK = NULL;

Keyword* KWD_KIF_OUT_FUNCTION = NULL;

Keyword* KWD_KIF_OUT_IMPLIES = NULL;

Keyword* KWD_KIF_OUT_FORALL = NULL;

Keyword* KWD_KIF_OUT_EXISTS = NULL;

Keyword* KWD_KIF_OUT_CONSTANT = NULL;

Keyword* KWD_KIF_OUT_CONTAINED_BY = NULL;

Keyword* KWD_KIF_OUT_DELETED = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_SUBSET_OF = NULL;

Symbol* SYM_KIF_OUT_LOGIC_FORWARD_ONLYp = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_le = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_FORALL = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_EXISTS = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_SETOF = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_LISTOF = NULL;

Symbol* SYM_KIF_OUT_LOGIC_COMPLEMENT_DESCRIPTION = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_KAPPA = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_eg = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_egg = NULL;

Symbol* SYM_KIF_OUT_LOGIC_BACKWARD_ONLYp = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_lle = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_lt = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_tg = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_llt = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_tgg = NULL;

Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_HIDDEN_RELATION = NULL;

Symbol* SYM_KIF_OUT_LOGIC_MASTER_PROPOSITION = NULL;

Symbol* SYM_KIF_OUT_LOGIC_ASSERTED_BY_TYPE_CHECKERp = NULL;

Keyword* KWD_KIF_OUT_TERSE = NULL;

Keyword* KWD_KIF_OUT_VERBOSE = NULL;

Keyword* KWD_KIF_OUT_SOURCE = NULL;

Keyword* KWD_KIF_OUT_SLOTS = NULL;

Keyword* KWD_KIF_OUT_PUBLIC_SLOTS = NULL;

Keyword* KWD_KIF_OUT_METHODS = NULL;

Keyword* KWD_KIF_OUT_PUBLIC_METHODS = NULL;

Symbol* SYM_KIF_OUT_STELLA_ASSERT = NULL;

Symbol* SYM_KIF_OUT_STELLA_SURROGATE_VALUE_INVERSE = NULL;

Symbol* SYM_KIF_OUT_LOGIC_PRESUME = NULL;

Symbol* SYM_KIF_OUT_STELLA_RETRACT = NULL;

Symbol* SYM_KIF_OUT_LOGIC_DEFRULE = NULL;

Symbol* SYM_KIF_OUT_LOGIC_IN_DIALECT = NULL;

Surrogate* SGT_KIF_OUT_STELLA_RELATION = NULL;

Surrogate* SGT_KIF_OUT_STELLA_OUTPUT_STREAM = NULL;

Surrogate* SGT_KIF_OUT_LOGIC_OBJECT_STORE = NULL;

Surrogate* SGT_KIF_OUT_LOGIC_NAMED_DESCRIPTION = NULL;

Symbol* SYM_KIF_OUT_LOGIC_UNDECLAREDp = NULL;

Keyword* KWD_KIF_OUT_MODULE = NULL;

Keyword* KWD_KIF_OUT_FILE = NULL;

Surrogate* SGT_KIF_OUT_STELLA_MODULE = NULL;

Surrogate* SGT_KIF_OUT_STELLA_STRING = NULL;

Keyword* KWD_KIF_OUT_MEDIUM = NULL;

Symbol* SYM_KIF_OUT_LOGIC_OBJECT_STORE = NULL;

Symbol* SYM_KIF_OUT_LOGIC_STARTUP_KIF_OUT = NULL;

Symbol* SYM_KIF_OUT_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
