//  -*- Mode: C++ -*-

// java-output.cc

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
| The Original Code is the STELLA Programming Language.                      |
|                                                                            |
| The Initial Developer of the Original Code is                              |
| UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
| 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
|                                                                            |
| Portions created by the Initial Developer are Copyright (C) 1996-2023      |
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
+---------------------------- END LICENSE BLOCK -----------------------------+
*/

#include "stella/stella-system.hh"

namespace stella {

DEFINE_STELLA_SPECIAL(oJAVA_INDENT_CHARSo, int , 0);

KeyValueList* oJAVA_STELLA_PACKAGE_MAPPINGo = NULL;

const char* javaStellaPackage() {
  { const char* stellapackage = oSTELLA_MODULEo->javaPackage_reader();

    if (stellapackage != NULL) {
      return (stellapackage);
    }
    else {
      return ("edu.isi.stella");
    }
  }
}

void javaOutputParseTree(Cons* constree) {
  { 
    BIND_STELLA_SPECIAL(oJAVA_INDENT_CHARSo, int, 0);
    oJAVA_STELLA_PACKAGE_MAPPINGo->insertAt(wrapString("STELLAROOT"), wrapString(javaStellaPackage()));
    javaOutputStatement(constree);
  }
}

void javaBumpIndent() {
  oJAVA_INDENT_CHARSo = oJAVA_INDENT_CHARSo + 2;
}

void javaUnbumpIndent() {
  oJAVA_INDENT_CHARSo = oJAVA_INDENT_CHARSo - 2;
}

void javaIndent() {
  { int i = NULL_INTEGER;
    int iter000 = 1;
    int upperBound000 = oJAVA_INDENT_CHARSo;
    boolean unboundedP000 = upperBound000 == NULL_INTEGER;

    for  (; unboundedP000 ||
              (iter000 <= upperBound000); 
          iter000 = iter000 + 1) {
      i = iter000;
      i = i;
      *(oCURRENT_STREAMo->nativeStream) << " ";
    }
  }
}

void javaOutputStatement(Object* statement) {
  if (safePrimaryType(statement) == SGT_JAVA_OUTPUT_STELLA_CONS) {
    { Object* statement000 = statement;
      Cons* statement = ((Cons*)(statement000));

      if (statement == NIL) {
        return;
      }
      if (consP(statement->value) ||
          (!((boolean)(statement->value)))) {
        {
          javaOutputStatement(statement->value);
          javaOutputStatement(statement->rest);
        }
      }
      else {
        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(statement->value));

          if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_CLASS) {
            javaOutputClass(statement->rest, false);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_EXCEPTION_CLASS) {
            javaOutputClass(statement->rest, true);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_NAMED_STATEMENT) {
            javaOutputNamedStatement(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_STATEMENTS) {
            javaOutputStatements(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_IDENT) {
            javaOutputIdentifier(((StringWrapper*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_EOL) {
            javaOutputIdentifier(((StringWrapper*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_LITERAL) {
            statement->rest->value->javaOutputLiteral();
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_COMMENT) {
            javaOutputComment(((StringWrapper*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_SYMBOL) {
            statement->rest->value->javaOutputLiteral();
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_CATCH) {
            javaOutputCatch(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_THROW) {
            javaOutputThrow(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_UNWIND_PROTECT) {
            javaOutputUnwindProtect(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_HANDLER_CASE) {
            javaOutputHandlerCase(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_SIGNAL) {
            javaOutputSignal(((Cons*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_VERBATIM) {
            javaOutputVerbatim(((StringWrapper*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_CAST) {
            javaOutputCast(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_GLOBAL) {
            javaOutputGlobalDefinition(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_TYPE) {
            javaOutputTypeExpression(((Cons*)(statement->rest)));
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_PROGN) {
            javaOutputProgn(((Cons*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_BLOCK) {
            javaOutputBlock(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_WITH_PROCESS_LOCK) {
            javaOutputWithProcessLock(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_RETURN) {
            javaOutputReturn(((Cons*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_MAKE) {
            javaOutputMake(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCALL) {
            javaOutputFuncall(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_CODE_CALL) {
            javaOutputMethodCodeCall(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_ASSIGN) {
            javaOutputAssignment(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_BREAK) {
            javaOutputBreak(((Cons*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_CONTINUE) {
            javaOutputContinue(((Cons*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_COND) {
            javaOutputCond(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_CASE) {
            javaOutputCase(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_IF) {
            javaOutputIf(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_WHEN) {
            javaOutputWhen(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_UNLESS) {
            javaOutputUnless(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_LOOP) {
            javaOutputLoop(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_WHILE) {
            javaOutputWhile(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_FOREACH) {
            javaOutputForeach(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_SLOT_VALUE) {
            javaOutputSlotValue(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_SLOT_VALUE_SETTER) {
            javaOutputSlotValueSetter(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_UNARY_OP) {
            javaOutputUnaryOperator(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_BINARY_OP) {
            javaOutputBinaryOperator(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_TERNARY_OP) {
            javaOutputTernaryOperator(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCTION_CALL) {
            javaOutputFunctionCall(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_CALL) {
            javaOutputMethodCall(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_ACTUALS) {
            javaOutputActualParameters(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_MAKE_ARRAY) {
            javaOutputMakeArray(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_ARRAY_INITIALIZER) {
            javaOutputArray(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_ANONYMOUS_ARRAY) {
            javaOutputAnonymousArray(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_AREF) {
            javaOutputAref(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD) {
            javaOutputMethod(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCTION) {
            javaOutputMethod(statement->rest);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_PRINT_STREAM) {
            javaOutputPrintStream(statement->rest, false);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_PRINT_NATIVE_STREAM) {
            javaOutputPrintStream(statement->rest, true);
          }
          else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_DECLARATIONS) {
            javaOutputDeclarations(((Cons*)(statement->rest)));
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
  else {
    if (!((boolean)(statement))) {
      return;
    }
    statement->javaOutputLiteral();
  }
}

void javaMaybeOutputStatementWithParentheses(Object* statement) {
  if (javaOperatorP(statement)) {
    *(oCURRENT_STREAMo->nativeStream) << "(";
  }
  javaOutputStatement(statement);
  if (javaOperatorP(statement)) {
    *(oCURRENT_STREAMo->nativeStream) << ")";
  }
}

void javaOutputIdentifier(StringWrapper* identifier) {
  *(oCURRENT_STREAMo->nativeStream) << identifier->wrapperValue;
}

void Object::javaOutputLiteral() {
  { Object* object = this;

  }
}

void stringJavaOutputLiteral(const char* string) {
  { int maxsize = 65535 - 1;
    int length = strlen(string);
    boolean toolongP = length > maxsize;
    int chunksize = 0;

    if (toolongP) {
      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        signalTranslationWarning();
        if (!(suppressWarningsP())) {
          printErrorContext(">> WARNING: ", STANDARD_WARNING);
          *(STANDARD_WARNING->nativeStream) << std::endl << " " << "Encountered too long string constant (" << "`" << stringSubsequence(string, 0, 80) << "'" << "...), breaking it up which is INEFFICIENT" << "." << std::endl;
        }
      }
      *(oCURRENT_STREAMo->nativeStream) << "new String().concat(";
    }
    *(oCURRENT_STREAMo->nativeStream) << "\"";
    { char ch = NULL_CHARACTER;
      const char* vector000 = string;
      int index000 = 0;
      int length000 = strlen(vector000);

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        ch = vector000[index000];
        chunksize = chunksize + 1;
        switch (ch) {
          case '\n': 
            *(oCURRENT_STREAMo->nativeStream) << "\\n";
            chunksize = chunksize + 1;
            break;
          case '\r': 
            *(oCURRENT_STREAMo->nativeStream) << "\\r";
            chunksize = chunksize + 1;
            break;
          case '"': 
            *(oCURRENT_STREAMo->nativeStream) << "\\\"";
            chunksize = chunksize + 1;
            break;
          case '\\': 
            *(oCURRENT_STREAMo->nativeStream) << "\\\\";
            chunksize = chunksize + 1;
            break;
          default:
            *(oCURRENT_STREAMo->nativeStream) << ch;
            break;
        }
        if ((chunksize >= maxsize) &&
            toolongP) {
          *(oCURRENT_STREAMo->nativeStream) << "\").concat(\"";
          chunksize = 0;
        }
      }
    }
    *(oCURRENT_STREAMo->nativeStream) << "\"";
    if (toolongP) {
      *(oCURRENT_STREAMo->nativeStream) << ")";
    }
  }
}

void StringWrapper::javaOutputLiteral() {
  { StringWrapper* string = this;

    stringJavaOutputLiteral(string->wrapperValue);
  }
}

void MutableStringWrapper::javaOutputLiteral() {
  { MutableStringWrapper* string = this;

    *(oCURRENT_STREAMo->nativeStream) << "new StringBuffer(";
    stringJavaOutputLiteral((string->wrapperValue));
    *(oCURRENT_STREAMo->nativeStream) << ")";
  }
}

void CharacterWrapper::javaOutputLiteral() {
  { CharacterWrapper* character = this;

    switch (character->wrapperValue) {
      case '\'': 
        *(oCURRENT_STREAMo->nativeStream) << "'\\''";
        break;
      case '\\': 
        *(oCURRENT_STREAMo->nativeStream) << "'\\\\'";
        break;
      case '\n': 
        *(oCURRENT_STREAMo->nativeStream) << "'\\n'";
        break;
      case '\b': 
        *(oCURRENT_STREAMo->nativeStream) << "'\\b'";
        break;
      case '\t': 
        *(oCURRENT_STREAMo->nativeStream) << "'\\t'";
        break;
      case '\r': 
        *(oCURRENT_STREAMo->nativeStream) << "'\\r'";
        break;
      case '\f': 
        *(oCURRENT_STREAMo->nativeStream) << "'\\f'";
        break;
      default:
        *(oCURRENT_STREAMo->nativeStream) << "'" << character->wrapperValue << "'";
        break;
    }
  }
}

void IntegerWrapper::javaOutputLiteral() {
  { IntegerWrapper* inT = this;

    *(oCURRENT_STREAMo->nativeStream) << inT->wrapperValue;
  }
}

void LongIntegerWrapper::javaOutputLiteral() {
  { LongIntegerWrapper* inT = this;

    *(oCURRENT_STREAMo->nativeStream) << inT->wrapperValue << "l";
  }
}

void FloatWrapper::javaOutputLiteral() {
  { FloatWrapper* floaT = this;

    *(oCURRENT_STREAMo->nativeStream) << floaT->wrapperValue;
  }
}

void BooleanWrapper::javaOutputLiteral() {
  { BooleanWrapper* boolean = this;

    if (boolean->wrapperValue) {
      *(oCURRENT_STREAMo->nativeStream) << "true";
    }
    else {
      *(oCURRENT_STREAMo->nativeStream) << "false";
    }
  }
}

void javaOutputMakeArray(Cons* statement) {
  *(oCURRENT_STREAMo->nativeStream) << "new ";
  *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(statement->value))->wrapperValue;
  { Object* dimension = NULL;
    Cons* iter000 = statement->rest;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      dimension = iter000->value;
      *(oCURRENT_STREAMo->nativeStream) << "[";
      javaOutputStatement(dimension);
      *(oCURRENT_STREAMo->nativeStream) << "]";
    }
  }
}

void javaOutputArray(Cons* arrayelements) {
  *(oCURRENT_STREAMo->nativeStream) << "{";
  if (((boolean)(arrayelements->value))) {
    javaOutputStatement(arrayelements->value);
  }
  { Object* element = NULL;
    Cons* iter000 = arrayelements->rest;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      element = iter000->value;
      *(oCURRENT_STREAMo->nativeStream) << ", ";
      javaOutputStatement(element);
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << "}";
}

void javaOutputAnonymousArray(Cons* statement) {
  *(oCURRENT_STREAMo->nativeStream) << "new ";
  *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(statement->value))->wrapperValue;
  *(oCURRENT_STREAMo->nativeStream) << " [] ";
  javaOutputArray(statement->rest);
}

void javaOutputAref(Cons* statement) {
  javaOutputStatement(statement->value);
  { Object* dimension = NULL;
    Cons* iter000 = statement->rest;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      dimension = iter000->value;
      *(oCURRENT_STREAMo->nativeStream) << "[";
      javaOutputStatement(dimension);
      *(oCURRENT_STREAMo->nativeStream) << "]";
    }
  }
}

void javaOutputSlotValue(Cons* statement) {
  javaOutputStatement(statement->value);
  *(oCURRENT_STREAMo->nativeStream) << "." << ((StringWrapper*)(statement->rest->value))->wrapperValue;
}

void javaOutputSlotValueSetter(Cons* statement) {
  javaOutputStatement(statement->value);
  *(oCURRENT_STREAMo->nativeStream) << "." << ((StringWrapper*)(statement->rest->value))->wrapperValue << " = ";
  javaOutputStatement(statement->rest->rest->value);
}

void javaOutputImplementsInterfaces(Cons* interfacelist) {
  *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(interfacelist->value))->wrapperValue;
  { StringWrapper* interface = NULL;
    Cons* iter000 = interfacelist->rest;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      interface = ((StringWrapper*)(iter000->value));
      *(oCURRENT_STREAMo->nativeStream) << ", " << interface->wrapperValue;
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << " ";
}

void javaOutputClass(Cons* classdef, boolean exceptionclassP) {
  javaOutputClassDeclaration(classdef);
  *(oCURRENT_STREAMo->nativeStream) << "{" << std::endl;
  javaBumpIndent();
  javaOutputClassVariableDefinitions(((Cons*)(classdef->nth(6))));
  javaOutputClassConstructors(((Cons*)(classdef->nth(7))), ((StringWrapper*)(classdef->fourth()))->wrapperValue, exceptionclassP);
  javaOutputClassMethods(((Cons*)(classdef->nth(8))));
  javaUnbumpIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl << std::endl;
}

void javaOutputClassDeclaration(Cons* classdef) {
  if (unwrapString(((StringWrapper*)(classdef->value))) != NULL) {
    javaOutputJavadocComment(((StringWrapper*)(classdef->value)), NULL, NULL, "Stella Java Translator", NULL);
  }
  { Object* m = NULL;
    Cons* iter000 = ((Cons*)(classdef->rest->value));

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      m = iter000->value;
      *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(m))->wrapperValue << " ";
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(classdef->rest->rest->value))->wrapperValue << " " << ((StringWrapper*)(classdef->fourth()))->wrapperValue << " ";
  if (((boolean)(classdef->fifth()))) {
    *(oCURRENT_STREAMo->nativeStream) << "extends " << ((StringWrapper*)(classdef->fifth()))->wrapperValue << " ";
  }
  if (!(((Cons*)(classdef->nth(5))) == NIL)) {
    *(oCURRENT_STREAMo->nativeStream) << "implements ";
    javaOutputImplementsInterfaces(((Cons*)(classdef->nth(5))));
  }
}

void javaOutputClassVariableDefinitions(Cons* variabletranslations) {
  { Object* statement = NULL;
    Cons* iter000 = variabletranslations;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      statement = iter000->value;
      javaOutputStatement(((Cons*)(statement)));
    }
  }
}

void javaOutputClassConstructors(Cons* constructors, const char* classname, boolean exceptionclassP) {
  if (exceptionclassP) {
    javaOutputExceptionConstructor(classname);
  }
  { TranslationUnit* statement = NULL;
    Cons* iter000 = constructors;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      statement = ((TranslationUnit*)(iter000->value));
      javaOutputStatement(javaTranslateUnit(statement));
      statement->translation = NULL;
      statement->codeRegister = NULL;
    }
  }
}

void javaOutputClassMethods(Cons* methods) {
  { TranslationUnit* statement = NULL;
    Cons* iter000 = methods;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      statement = ((TranslationUnit*)(iter000->value));
      javaOutputStatement(javaTranslateUnit(statement));
      statement->translation = NULL;
      statement->codeRegister = NULL;
    }
  }
}

void javaOutputExceptionConstructor(const char* exceptionname) {
  javaIndent();
  *(oCURRENT_STREAMo->nativeStream) << "public " << exceptionname << " (String message) {" << std::endl;
  javaBumpIndent();
  javaIndent();
  *(oCURRENT_STREAMo->nativeStream) << "super(message);" << std::endl;
  javaUnbumpIndent();
  javaIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl << std::endl;
}

void javaOutputNamedStatement(Cons* namedstatement) {
  javaOutputStatement(namedstatement->value);
  *(oCURRENT_STREAMo->nativeStream) << " : ";
  javaOutputStatement(namedstatement->rest->value);
}

void javaOutputFormalParameters(Cons* parameters) {
  *(oCURRENT_STREAMo->nativeStream) << "(";
  if (!(parameters == NIL)) {
    *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(((Cons*)(parameters->value))->value))->wrapperValue << " " << ((StringWrapper*)(((Cons*)(parameters->value))->rest->value))->wrapperValue;
    { Cons* parameter = NULL;
      Cons* iter000 = parameters->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        parameter = ((Cons*)(iter000->value));
        *(oCURRENT_STREAMo->nativeStream) << ", " << ((StringWrapper*)(parameter->value))->wrapperValue << " " << ((StringWrapper*)(parameter->rest->value))->wrapperValue;
      }
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << ")";
}

void javaOutputMethodSignature(Cons* method) {
  { Object* m = NULL;
    Cons* iter000 = ((Cons*)(method->value));

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      m = iter000->value;
      *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(m))->wrapperValue << " ";
    }
  }
  javaOutputTypeExpression(((Cons*)(method->rest->value)));
  *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(method->rest->rest->value))->wrapperValue;
  javaOutputFormalParameters(((Cons*)(method->fourth())));
}

Cons* javaSeparateCommentFromBody(Cons* body, Cons*& _Return1) {
  if ((body->value == SYM_JAVA_OUTPUT_STELLA_JAVA_STATEMENTS) &&
      ((!(body->rest == NIL)) &&
       (isaP(body->rest->value, SGT_JAVA_OUTPUT_STELLA_CONS) &&
        (((Cons*)(body->rest->value))->value == SYM_JAVA_OUTPUT_STELLA_JAVA_COMMENT)))) {
    { Object* comment = body->rest->value;

      body->rest = body->rest->rest;
      if (body->rest == NIL) {
        _Return1 = ((Cons*)(comment));
        return (NIL);
      }
      else {
        _Return1 = ((Cons*)(comment));
        return (body);
      }
    }
  }
  else {
    _Return1 = NULL;
    return (body);
  }
}

void javaOutputMethod(Cons* method) {
  { Cons* body = NULL;
    Cons* comment = NULL;

    body = javaSeparateCommentFromBody(((Cons*)(method->fifth())), comment);
    if (((boolean)(comment))) {
      javaIndent();
      javaOutputJavadocComment(((StringWrapper*)(comment->rest->value)), ((Cons*)(method->fourth())), ((StringWrapper*)(((Cons*)(method->rest->value))->value)), NULL, NULL);
    }
    javaIndent();
    javaOutputMethodSignature(method);
    if (!(body == NIL)) {
      *(oCURRENT_STREAMo->nativeStream) << " {" << std::endl;
      javaBumpIndent();
      javaOutputStatement(body);
      javaUnbumpIndent();
      javaIndent();
      *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
    }
    else if (((Cons*)(method->value))->memberP(wrapString("abstract"))) {
      *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
    }
    else if (((Cons*)(method->rest->value))->memberP(wrapString("void"))) {
      std::cout << "Note: Void method " << "`" << method->rest->rest->value << "'" << " has an empty body." << std::endl;
      *(oCURRENT_STREAMo->nativeStream) << " {}" << std::endl;
    }
    else {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Method " << "`" << method->rest->rest->value << "'" << " has an empty body but is not abstract or void!" << std::endl;
      *(oCURRENT_STREAMo->nativeStream) << " {}" << std::endl;
    }
    *(oCURRENT_STREAMo->nativeStream) << std::endl;
  }
}

void Cons::javaOutputLiteral() {
  { Cons* cons = this;

    if (cons == NIL) {
      *(oCURRENT_STREAMo->nativeStream) << "NIL";
    }
    else {
      {
        *(oCURRENT_STREAMo->nativeStream) << "(" << cons->value << " . ";
        cons->rest->javaOutputLiteral();
      }
    }
  }
}

void QuotedExpression::javaOutputLiteral() {
  { QuotedExpression* tree = this;

    *(oCURRENT_STREAMo->nativeStream) << "\"" << tree << "\"";
  }
}

void Symbol::javaOutputLiteral() {
  { Symbol* symbol = this;

    *(oCURRENT_STREAMo->nativeStream) << javaTranslateSymbolName(symbol)->wrapperValue;
  }
}

void Surrogate::javaOutputLiteral() {
  { Surrogate* surrogate = this;

    *(oCURRENT_STREAMo->nativeStream) << javaTranslateSurrogateName(surrogate)->wrapperValue;
  }
}

void Keyword::javaOutputLiteral() {
  { Keyword* keyword = this;

    *(oCURRENT_STREAMo->nativeStream) << javaTranslateKeywordName(keyword)->wrapperValue;
  }
}

void javaOutputTypeExpression(Cons* typeexpression) {
  { StringWrapper* typeexpr = NULL;
    Cons* iter000 = typeexpression;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      typeexpr = ((StringWrapper*)(iter000->value));
      *(oCURRENT_STREAMo->nativeStream) << typeexpr->wrapperValue << " ";
    }
  }
}

Cons* oJAVA_SEMICOLON_STATEMENTSo = NULL;

boolean javaOutputSemicolonP(Cons* statement) {
  if (((boolean)(statement))) {
    return (oJAVA_SEMICOLON_STATEMENTSo->memberP(statement->value));
  }
  else {
    return (false);
  }
}

boolean javaIndentStatementP(Cons* statement) {
  if (((boolean)(statement))) {
    return (!getQuotedTree("((JAVA_STATEMENTS JAVA_CATCH) \"/STELLA\")", "/STELLA")->memberP(statement->value));
  }
  else {
    return (false);
  }
}

boolean javaIllegalStatementP(Cons* statement) {
  if (((boolean)(statement))) {
    return (getQuotedTree("((JAVA_LITERAL JAVA_IDENT) \"/STELLA\")", "/STELLA")->memberP(statement->value));
  }
  else {
    return (false);
  }
}

void javaOutputStatements(Cons* statementlist) {
  { Object* statement = NULL;
    Cons* iter000 = statementlist;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      statement = iter000->value;
      if (!(javaIllegalStatementP(((Cons*)(statement))))) {
        if (javaIndentStatementP(((Cons*)(statement)))) {
          javaIndent();
        }
        javaOutputStatement(statement);
        if (javaOutputSemicolonP(((Cons*)(statement)))) {
          *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
        }
      }
    }
  }
}

void javaOutputDeclarations(Cons* declarations) {
  javaBumpIndent();
  { Cons* declaration = NULL;
    Cons* iter000 = declarations;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      declaration = ((Cons*)(iter000->value));
      if (((boolean)(declaration->rest->rest->value))) {
        javaIndent();
        javaOutputJavadocComment(((StringWrapper*)(declaration->rest->rest->value)), NIL, NULL, NULL, NULL);
      }
      javaIndent();
      javaOutputTypeExpression(((Cons*)(declaration->value)));
      *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(declaration->rest->value))->wrapperValue;
      *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << std::endl;
  javaUnbumpIndent();
}

const char* javaHeuristicallyTranslateName(const char* stellaName, Cons* caseConvertedNameList) {
  { StringWrapper* pname = NULL;
    Cons* iter000 = caseConvertedNameList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      pname = ((StringWrapper*)(iter000->value));
      if (stringEqualP(pname->wrapperValue, stellaName)) {
        return (pname->wrapperValue);
      }
    }
  }
  { boolean testValue000 = false;

    if (oMODULEo->caseSensitiveP) {
      testValue000 = true;
    }
    else {
      { boolean foundP000 = false;

        { char ch = NULL_CHARACTER;
          const char* vector000 = stellaName;
          int index000 = 0;
          int length000 = strlen(vector000);

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            ch = vector000[index000];
            if (upperCaseCharacterP(ch)) {
              foundP000 = true;
              break;
            }
          }
        }
        testValue000 = foundP000;
      }
    }
    if (testValue000) {
      {
        return (javaTranslateNamestring(makeMatchingNameFull(stellaName, KWD_JAVA_OUTPUT_NO, KWD_JAVA_OUTPUT_NO, "- ", "", "", "", "", KWD_JAVA_OUTPUT_PRESERVE, "_")));
      }
    }
    else {
      if (stringMemberP(stellaName, '*')) {
        {
          return (javaTranslateNamestring(makeMatchingNameFull(stellaName, KWD_JAVA_OUTPUT_CLEVER, KWD_JAVA_OUTPUT_CLEVER, "- ", "", "", "", "", KWD_JAVA_OUTPUT_UPCASE, "_")));
        }
      }
      else {
        {
          return (javaTranslateNamestring(makeMatchingNameFull(stellaName, KWD_JAVA_OUTPUT_CLEVER, KWD_JAVA_OUTPUT_CLEVER, "- ", "", "", "", "", KWD_JAVA_OUTPUT_TITLECASEX, "")));
        }
      }
    }
  }
}

void javaOutputCommentString(const char* comment, const char* commentStart, const char* commentContinuation, const char* commentEnd, boolean javadocCommentP, Cons* caseConvertedNameList) {
  { boolean returnP = false;
    boolean escapeP = false;
    boolean eolLastP = false;
    boolean insideQuoteP = false;
    OutputStream* savedStream = oCURRENT_STREAMo;
    OutputStringStream* stringStream = NULL;
    const char* stellaName = NULL;

    *(oCURRENT_STREAMo->nativeStream) << commentStart;
    { char chaR = NULL_CHARACTER;
      const char* vector000 = comment;
      int index000 = 0;
      int length000 = strlen(vector000);

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        chaR = vector000[index000];
        switch (chaR) {
          case '\n': 
            if (!(returnP)) {
              if (eolLastP &&
                  javadocCommentP) {
                *(oCURRENT_STREAMo->nativeStream) << "<p>" << std::endl;
              }
              else {
                *(oCURRENT_STREAMo->nativeStream) << std::endl;
              }
              eolLastP = true;
              javaIndent();
              *(oCURRENT_STREAMo->nativeStream) << commentContinuation;
            }
            escapeP = false;
            returnP = false;
            break;
          case '\r': 
            if (eolLastP &&
                javadocCommentP) {
              *(oCURRENT_STREAMo->nativeStream) << "<p>" << std::endl;
            }
            else {
              *(oCURRENT_STREAMo->nativeStream) << std::endl;
            }
            javaIndent();
            *(oCURRENT_STREAMo->nativeStream) << commentContinuation;
            eolLastP = true;
            returnP = true;
            escapeP = false;
            continue;
            break;
          case '`': 
            if (escapeP) {
              *(oCURRENT_STREAMo->nativeStream) << chaR;
            }
            else if (insideQuoteP) {
              *(STANDARD_WARNING->nativeStream) << "Warning: " << "Encountered unescaped ` inside ` form in comment " << "`" << comment << "'" << std::endl;
              *(oCURRENT_STREAMo->nativeStream) << chaR;
            }
            else {
              stringStream = newOutputStringStream();
              oCURRENT_STREAMo = stringStream;
              insideQuoteP = true;
            }
            escapeP = false;
            returnP = false;
            eolLastP = false;
            break;
          case '\'': 
            if (escapeP) {
              *(oCURRENT_STREAMo->nativeStream) << chaR;
            }
            else if (insideQuoteP) {
              oCURRENT_STREAMo = savedStream;
              stellaName = stringStream->theStringReader();
              if (javadocCommentP) {
                *(oCURRENT_STREAMo->nativeStream) << "<code>";
              }
              else {
                *(oCURRENT_STREAMo->nativeStream) << "`";
              }
              *(oCURRENT_STREAMo->nativeStream) << javaHeuristicallyTranslateName(stellaName, caseConvertedNameList);
              if (javadocCommentP) {
                *(oCURRENT_STREAMo->nativeStream) << "</code>";
              }
              else {
                *(oCURRENT_STREAMo->nativeStream) << "'";
              }
              insideQuoteP = false;
            }
            else {
              *(oCURRENT_STREAMo->nativeStream) << chaR;
            }
            escapeP = false;
            returnP = false;
            eolLastP = false;
            break;
          case '\\': 
            if (escapeP) {
              {
                *(oCURRENT_STREAMo->nativeStream) << chaR;
                escapeP = false;
              }
            }
            else {
              escapeP = true;
            }
            returnP = false;
            eolLastP = false;
            break;
          default:
            if (insideQuoteP ||
                (!javadocCommentP)) {
              *(oCURRENT_STREAMo->nativeStream) << chaR;
            }
            else {
              writeHtmlCharacterQuotingSpecialCharacters(oCURRENT_STREAMo->nativeStream, chaR);
            }
            returnP = false;
            escapeP = false;
            eolLastP = false;
            break;
        }
      }
    }
    if (insideQuoteP) {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "Comment ended while inside a ` form in comment " << "`" << comment << "'" << std::endl;
      oCURRENT_STREAMo = savedStream;
      *(oCURRENT_STREAMo->nativeStream) << "`";
      *(oCURRENT_STREAMo->nativeStream) << stringStream->theStringReader();
    }
    if ((commentEnd != NULL) &&
        (!stringEqlP(commentEnd, ""))) {
      {
        javaIndent();
        *(oCURRENT_STREAMo->nativeStream) << commentEnd;
      }
    }
    else {
      *(oCURRENT_STREAMo->nativeStream) << std::endl;
    }
  }
}

void javaOutputComment(StringWrapper* tree) {
  javaOutputCommentString(tree->wrapperValue, "// ", "// ", NULL, false, NIL);
}

void javaOutputJavadocComment(StringWrapper* tree, Cons* parameterNamesAndTypes, StringWrapper* returnValue, const char* author, const char* version) {
  { Cons* parameterNames = NIL;

    if (((boolean)(parameterNamesAndTypes))) {
      { Cons* n = NULL;
        Cons* iter000 = parameterNamesAndTypes;
        Cons* collect000 = NULL;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest) {
          n = ((Cons*)(iter000->value));
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(((StringWrapper*)(n->rest->value)), NIL);
              if (parameterNames == NIL) {
                parameterNames = collect000;
              }
              else {
                addConsToEndOfConsList(parameterNames, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(((StringWrapper*)(n->rest->value)), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    javaOutputCommentString(tree->wrapperValue, "/** ", " * ", NULL, true, parameterNames);
    { StringWrapper* n = NULL;
      Cons* iter001 = parameterNames;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        n = ((StringWrapper*)(iter001->value));
        javaIndent();
        *(oCURRENT_STREAMo->nativeStream) << " * @param " << n->wrapperValue << std::endl;
      }
    }
    if (((boolean)(returnValue)) &&
        (!stringEqlP(returnValue->wrapperValue, "void"))) {
      javaIndent();
      *(oCURRENT_STREAMo->nativeStream) << " * @return " << returnValue->wrapperValue << std::endl;
    }
    if ((author != NULL) &&
        (!(author == ""))) {
      javaIndent();
      *(oCURRENT_STREAMo->nativeStream) << " * @author " << author << std::endl;
    }
    if ((version != NULL) &&
        (!(version == ""))) {
      javaIndent();
      *(oCURRENT_STREAMo->nativeStream) << " * @version " << version << std::endl;
    }
    javaIndent();
    *(oCURRENT_STREAMo->nativeStream) << " */" << std::endl;
  }
}

const char* fixupDocumentationStringQuoting(const char* documentation) {
  if (documentation == NULL) {
    return (NULL);
  }
  { int closingquoteposition = NULL_INTEGER;
    char precedingcharacter = NULL_CHARACTER;
    const char* openparentheses = "([{";
    char* buffer = strcpy(new (GC) char[strlen(documentation)+1], documentation);

    { char chaR = NULL_CHARACTER;
      const char* vector000 = documentation;
      int index000 = 0;
      int length000 = strlen(vector000);
      int i = NULL_INTEGER;
      int iter000 = 0;

      for  (; index000 < length000; 
            index000 = index000 + 1,
            iter000 = iter000 + 1) {
        chaR = vector000[index000];
        i = iter000;
        switch (chaR) {
          case '`': 
          case '\'': 
            if (i == closingquoteposition) {
              continue;
            }
            if (i == 0) {
              precedingcharacter = ' ';
            }
            else {
              precedingcharacter = documentation[(i - 1)];
            }
            if ((oCHARACTER_TYPE_TABLEo[(int)(unsigned char) precedingcharacter] == KWD_JAVA_OUTPUT_WHITE_SPACE) ||
                stringMemberP(openparentheses, precedingcharacter)) {
              closingquoteposition = stringPosition(documentation, '\'', i + 1);
              if (closingquoteposition != NULL_INTEGER) {
                buffer[i] = '`';
              }
            }
            break;
          default:
            break;
        }
      }
    }
    return (buffer);
  }
}

void javaOutputVerbatim(StringWrapper* verbatimstatement) {
  { const char* vstring = verbatimstatement->wrapperValue;

    if (stringMemberP(vstring, '\n') ||
        stringMemberP(vstring, '\r')) {
      substituteTemplateVariablesToStream(makeTokenizerStringStream(vstring), oCURRENT_STREAMo, oJAVA_STELLA_PACKAGE_MAPPINGo);
    }
    else {
      *(oCURRENT_STREAMo->nativeStream) << substituteTemplateVariablesInString(vstring, oJAVA_STELLA_PACKAGE_MAPPINGo);
    }
  }
}

void javaOutputMake(Cons* statement) {
  *(oCURRENT_STREAMo->nativeStream) << "new ";
  javaOutputStatement(statement->value);
  javaOutputStatement(statement->rest->value);
}

void javaOutputCast(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "((" << ((StringWrapper*)(tree->rest->value))->wrapperValue << ")(";
  javaOutputStatement(tree->value);
  *(oCURRENT_STREAMo->nativeStream) << "))";
}

void javaOutputProgn(Cons* progn) {
  *(oCURRENT_STREAMo->nativeStream) << "{" << std::endl;
  javaBumpIndent();
  javaOutputStatement(progn);
  javaUnbumpIndent();
  javaIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
}

void javaOutputBlock(Cons* block) {
  { boolean firststatementP = true;

    *(oCURRENT_STREAMo->nativeStream) << "{ ";
    javaBumpIndent();
    { Cons* declaration = NULL;
      Cons* iter000 = ((Cons*)(block->value));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        declaration = ((Cons*)(iter000->value));
        if (!(firststatementP)) {
          javaIndent();
        }
        firststatementP = false;
        *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(declaration->value))->wrapperValue;
        *(oCURRENT_STREAMo->nativeStream) << " ";
        javaOutputStatement(declaration->rest->value);
        if (!(!((boolean)(declaration->rest->rest->value)))) {
          *(oCURRENT_STREAMo->nativeStream) << " = ";
          javaOutputStatement(declaration->rest->rest->value);
        }
        *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
      }
    }
    *(oCURRENT_STREAMo->nativeStream) << std::endl;
    javaOutputStatement(block->rest->value);
    javaUnbumpIndent();
    javaIndent();
    *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
  }
}

void javaOutputWithProcessLock(Cons* synch) {
  *(oCURRENT_STREAMo->nativeStream) << "synchronized (";
  javaOutputStatement(synch->value);
  *(oCURRENT_STREAMo->nativeStream) << ") ";
  javaOutputProgn(((Cons*)(synch->rest->value)));
}

void javaOutputReturn(Cons* returnstatement) {
  *(oCURRENT_STREAMo->nativeStream) << "return";
  if (((boolean)(returnstatement))) {
    *(oCURRENT_STREAMo->nativeStream) << " (";
    javaOutputStatement(returnstatement);
    *(oCURRENT_STREAMo->nativeStream) << ")";
  }
}

void javaOutputThrow(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "throw new ";
  *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(tree->value))->wrapperValue;
}

void javaOutputCatch(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << " catch (";
  *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(((Cons*)(tree->value))->value))->wrapperValue;
  *(oCURRENT_STREAMo->nativeStream) << " ";
  *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(((Cons*)(tree->value))->rest->value))->wrapperValue;
  *(oCURRENT_STREAMo->nativeStream) << ") {" << std::endl;
  javaBumpIndent();
  javaOutputStatements(tree->rest);
  javaUnbumpIndent();
  javaIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}";
}

void javaOutputUnwindProtect(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "try {" << std::endl;
  javaBumpIndent();
  if (javaPrognP(tree->value)) {
    javaOutputStatement(((Cons*)(tree->value))->rest->value);
  }
  else if (javaIndentStatementP(((Cons*)(tree->value)))) {
    javaIndent();
    javaOutputStatement(tree->value);
    if (javaOutputSemicolonP(((Cons*)(tree->value)))) {
      *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
    }
  }
  else {
    javaOutputStatement(tree->value);
  }
  javaUnbumpIndent();
  *(oCURRENT_STREAMo->nativeStream) << std::endl;
  javaIndent();
  *(oCURRENT_STREAMo->nativeStream) << "} finally {" << std::endl;
  javaBumpIndent();
  javaOutputStatements(tree->rest);
  javaUnbumpIndent();
  javaIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
}

void javaOutputHandlerCase(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "try {" << std::endl;
  javaBumpIndent();
  if (javaPrognP(tree->value)) {
    javaOutputStatement(((Cons*)(tree->value))->rest->value);
  }
  else {
    {
      javaIndent();
      javaOutputStatement(tree->value);
      if (javaOutputSemicolonP(((Cons*)(tree->value)))) {
        *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
      }
    }
  }
  javaUnbumpIndent();
  javaIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}";
  javaOutputStatements(tree->rest);
  *(oCURRENT_STREAMo->nativeStream) << std::endl;
}

void javaOutputSignal(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "throw ";
  javaOutputStatement(tree);
}

void javaOutputGlobalDefinition(Cons* global) {
  if (((StringWrapper*)(global->value))->wrapperValue != NULL) {
    javaIndent();
    javaOutputJavadocComment(((StringWrapper*)(global->value)), NIL, NULL, NULL, NULL);
  }
  javaIndent();
  javaOutputStatement(global->rest->value);
  *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(global->rest->rest->value))->wrapperValue;
  if (!(global->rest->rest->rest == NIL)) {
    *(oCURRENT_STREAMo->nativeStream) << " = ";
    javaOutputStatement(global->fourth());
  }
  *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl << std::endl;
}

void javaOutputActualsAsConsExpression(Cons* arglist) {
  if (arglist == NIL) {
    *(oCURRENT_STREAMo->nativeStream) << javaPrependGlobalClassName("NIL", oSTELLA_MODULEo);
  }
  else {
    {
      *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(oJAVA_STELLA_PACKAGE_MAPPINGo->lookup(wrapString("STELLAROOT")))) << ".Stella_Object.cons(";
      javaOutputStatement(arglist->value);
      *(oCURRENT_STREAMo->nativeStream) << ", ";
      javaOutputActualsAsConsExpression(arglist->rest);
      *(oCURRENT_STREAMo->nativeStream) << ")";
    }
  }
}

void javaOutputFuncall(Cons* funcall) {
  *(oCURRENT_STREAMo->nativeStream) << javaYieldFullNativeClassName() << ".funcall(";
  javaOutputStatement(funcall->rest->value);
  *(oCURRENT_STREAMo->nativeStream) << ", null, new java.lang.Object [] ";
  javaOutputArray(((Cons*)(funcall->rest->rest->value))->rest);
  *(oCURRENT_STREAMo->nativeStream) << ")";
}

void javaOutputMethodCodeCall(Cons* methodcall) {
  *(oCURRENT_STREAMo->nativeStream) << javaYieldFullNativeClassName() << ".funcall(";
  javaOutputStatement(methodcall->rest->value);
  *(oCURRENT_STREAMo->nativeStream) << ", ";
  javaOutputStatement(methodcall->rest->rest->value);
  *(oCURRENT_STREAMo->nativeStream) << ", new java.lang.Object []";
  javaOutputArray(((Cons*)(methodcall->fourth()))->rest);
  *(oCURRENT_STREAMo->nativeStream) << ")";
}

void javaOutputBreak(Cons* tag) {
  *(oCURRENT_STREAMo->nativeStream) << "break ";
  javaOutputStatement(tag);
  *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
}

void javaOutputContinue(Cons* tag) {
  *(oCURRENT_STREAMo->nativeStream) << "continue ";
  javaOutputStatement(tag);
  *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
}

boolean javaStatementReturnsP(Cons* statement) {
  if (!((boolean)(statement))) {
    return (false);
  }
  else if (statement == NIL) {
    return (false);
  }
  else {
    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(statement->value));

      if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_VERBATIM) {
        return (stringSearch(((StringWrapper*)(statement->rest->value))->wrapperValue, "throw new Error", 0) != NULL_INTEGER);
      }
      else if ((testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_RETURN) ||
          ((testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_CONTINUE) ||
           ((testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_BREAK) ||
            (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_SIGNAL)))) {
        return (true);
      }
      else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_STATEMENTS) {
        return (javaLastStatementReturnsP(statement->rest));
      }
      else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_PROGN) {
        return (javaLastStatementReturnsP(((Cons*)(statement->rest->value))));
      }
      else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_BLOCK) {
        return (javaLastStatementReturnsP(((Cons*)(statement->rest->rest->value))));
      }
      else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_IF) {
        return (javaStatementReturnsP(((Cons*)(statement->rest->rest->value))) &&
            javaStatementReturnsP(((Cons*)(statement->fourth()))));
      }
      else if (testValue000 == SYM_JAVA_OUTPUT_STELLA_JAVA_COND) {
        { boolean testValue001 = false;

          testValue001 = javaStatementReturnsP(((Cons*)(statement->rest->value)));
          if (testValue001) {
            { boolean alwaysP000 = true;

              { Object* c = NULL;
                Cons* iter000 = ((Cons*)(statement->rest->rest->value));

                for (; !(iter000 == NIL); iter000 = iter000->rest) {
                  c = iter000->value;
                  if (!javaLastStatementReturnsP(((Cons*)(c)))) {
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
      else {
        return (false);
      }
    }
  }
}

boolean javaLastStatementReturnsP(Cons* statements) {
  { Object* lastStatement = statements->last();

    return (isaP(lastStatement, SGT_JAVA_OUTPUT_STELLA_CONS) &&
        javaStatementReturnsP(((Cons*)(lastStatement))));
  }
}

void javaOutputCase(Cons* casE) {
  { Object* keyform = casE->value;
    Object* defaultcase = casE->rest->value;
    Object* conditions = casE->rest->rest->value;

    *(oCURRENT_STREAMo->nativeStream) << "switch (";
    javaOutputStatement(keyform);
    *(oCURRENT_STREAMo->nativeStream) << ") {" << std::endl;
    javaBumpIndent();
    { Cons* c = NULL;
      Cons* iter000 = ((Cons*)(conditions));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        c = ((Cons*)(iter000->value));
        { Cons* condition = c;

          { Object* cond = NULL;
            Cons* iter001 = ((Cons*)((consP(((Cons*)(condition->value))->value) ? condition->value : cons(condition->value, NIL))));

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              cond = iter001->value;
              javaIndent();
              *(oCURRENT_STREAMo->nativeStream) << "case ";
              javaOutputStatement(cond);
              *(oCURRENT_STREAMo->nativeStream) << ": " << std::endl;
            }
          }
          javaBumpIndent();
          javaOutputStatement(condition->rest->value);
          javaUnbumpIndent();
          if (!(javaLastStatementReturnsP(((Cons*)(condition->rest->value))))) {
            javaIndent();
            *(oCURRENT_STREAMo->nativeStream) << "break;" << std::endl;
          }
        }
      }
    }
    if (!((boolean)(defaultcase))) {
      std::cerr << "Safety violation: " << "INTERNAL ERROR: `java-output-case' expects an `otherwise' clause.";
    }
    javaIndent();
    *(oCURRENT_STREAMo->nativeStream) << "default:" << std::endl;
    javaBumpIndent();
    javaOutputStatement(defaultcase);
    javaUnbumpIndent();
    if (!(javaLastStatementReturnsP(((Cons*)(defaultcase))))) {
      javaIndent();
      *(oCURRENT_STREAMo->nativeStream) << "break;" << std::endl;
    }
    javaUnbumpIndent();
    javaIndent();
    *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
  }
}

void javaOutputCond(Cons* cond) {
  { Cons* defaultcondition = ((Cons*)(cond->value));
    Cons* conditions = ((Cons*)(cond->rest->value));
    Cons* firstcondition = ((Cons*)(conditions->value));
    Cons* restconditions = conditions->rest;

    if (((boolean)(defaultcondition)) &&
        (conditions == NIL)) {
      *(oCURRENT_STREAMo->nativeStream) << "if (true) ";
      javaOutputStatement(defaultcondition);
      return;
    }
    *(oCURRENT_STREAMo->nativeStream) << "if (";
    javaOutputStatement(firstcondition->value);
    *(oCURRENT_STREAMo->nativeStream) << ") ";
    javaOutputStatement(firstcondition->rest->value);
    { Object* c = NULL;
      Cons* iter000 = restconditions;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        c = iter000->value;
        { Cons* condition = ((Cons*)(c));

          javaIndent();
          *(oCURRENT_STREAMo->nativeStream) << "else if (";
          javaOutputStatement(condition->value);
          *(oCURRENT_STREAMo->nativeStream) << ") ";
          javaOutputStatement(condition->rest->value);
        }
      }
    }
    if (((boolean)(defaultcondition))) {
      javaIndent();
      *(oCURRENT_STREAMo->nativeStream) << "else ";
      javaOutputStatement(defaultcondition);
    }
  }
}

boolean javaPrognP(Object* tree) {
  return (consP(tree) &&
      (((Cons*)(tree))->value == SYM_JAVA_OUTPUT_STELLA_JAVA_PROGN));
}

boolean javaBlockP(Object* tree) {
  return (consP(tree) &&
      (((Cons*)(tree))->value == SYM_JAVA_OUTPUT_STELLA_JAVA_BLOCK));
}

void javaOutputIf(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "if (";
  javaOutputStatement(tree->value);
  *(oCURRENT_STREAMo->nativeStream) << ") ";
  if (javaPrognP(tree->rest->value) ||
      javaBlockP(tree->rest->value)) {
    javaOutputStatement(tree->rest->value);
  }
  else {
    {
      *(oCURRENT_STREAMo->nativeStream) << std::endl;
      javaBumpIndent();
      javaIndent();
      javaOutputStatement(tree->rest->value);
      *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
      javaUnbumpIndent();
    }
  }
  if (!(!((boolean)(tree->rest->rest->value)))) {
    javaIndent();
    *(oCURRENT_STREAMo->nativeStream) << "else ";
    if (javaPrognP(tree->rest->rest->value) ||
        javaBlockP(tree->rest->rest->value)) {
      javaOutputStatement(tree->rest->rest->value);
    }
    else {
      {
        *(oCURRENT_STREAMo->nativeStream) << std::endl;
        javaBumpIndent();
        javaIndent();
        javaOutputStatement(tree->rest->rest->value);
        *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
        javaUnbumpIndent();
      }
    }
  }
}

void javaOutputWhen(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "if (";
  javaOutputStatement(tree->value);
  *(oCURRENT_STREAMo->nativeStream) << ") {" << std::endl;
  javaBumpIndent();
  javaOutputStatement(tree->rest->value);
  javaUnbumpIndent();
  javaIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
}

void javaOutputUnless(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "if (!(";
  javaOutputStatement(tree->value);
  *(oCURRENT_STREAMo->nativeStream) << ")) {" << std::endl;
  javaBumpIndent();
  javaOutputStatement(tree->rest->value);
  javaUnbumpIndent();
  javaIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
}

void javaOutputAssignment(Cons* assignment) {
  javaOutputStatement(assignment->value);
  *(oCURRENT_STREAMo->nativeStream) << " = ";
  javaOutputStatement(assignment->rest->value);
}

void javaOutputLoop(Cons* loop) {
  *(oCURRENT_STREAMo->nativeStream) << "for (;;) ";
  javaOutputStatement(loop->value);
}

void javaOutputWhile(Cons* loop) {
  *(oCURRENT_STREAMo->nativeStream) << "while (";
  javaOutputStatement(loop->value);
  *(oCURRENT_STREAMo->nativeStream) << ") ";
  javaOutputStatement(loop->rest->value);
}

void javaOutputForeach(Cons* loop) {
  { Object* continuationtest = loop->rest->value;
    Cons* valueassignments = ((Cons*)(loop->rest->rest->value));
    Cons* nextassignments = ((Cons*)(loop->fourth()));
    int nofnextassignments = nextassignments->length();
    Cons* body = ((Cons*)(loop->fifth()));
    boolean eolseparateexpressionsP = (nofnextassignments > 2) ||
        (oJAVA_INDENT_CHARSo > 35);

    if (nofnextassignments == 0) {
      *(oCURRENT_STREAMo->nativeStream) << "while (";
      javaOutputStatement(continuationtest);
      *(oCURRENT_STREAMo->nativeStream) << ") {" << std::endl;
      javaBumpIndent();
      javaOutputStatements(valueassignments->concatenate(body, 0));
      javaUnbumpIndent();
      javaIndent();
      *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
      return;
    }
    *(oCURRENT_STREAMo->nativeStream) << "for (;";
    javaBumpIndent();
    javaBumpIndent();
    javaBumpIndent();
    javaOutputStatement(continuationtest);
    *(oCURRENT_STREAMo->nativeStream) << "; ";
    if (!(nextassignments == NIL)) {
      if (eolseparateexpressionsP) {
        *(oCURRENT_STREAMo->nativeStream) << std::endl;
      }
      { Object* next = NULL;
        Cons* iter000 = nextassignments;
        int i = NULL_INTEGER;
        int iter001 = 1;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          next = iter000->value;
          i = iter001;
          if (eolseparateexpressionsP) {
            javaIndent();
          }
          javaOutputStatement(next);
          if (!(i == nofnextassignments)) {
            if (eolseparateexpressionsP) {
              *(oCURRENT_STREAMo->nativeStream) << "," << std::endl;
            }
            else {
              *(oCURRENT_STREAMo->nativeStream) << ", ";
            }
          }
        }
      }
    }
    *(oCURRENT_STREAMo->nativeStream) << ") {" << std::endl;
    javaUnbumpIndent();
    javaUnbumpIndent();
    javaOutputStatements(valueassignments->concatenate(body, 0));
    javaUnbumpIndent();
    javaIndent();
    *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
  }
}

boolean javaEndOfLineTokenP(Object* token) {
  if (safePrimaryType(token) == SGT_JAVA_OUTPUT_STELLA_CONS) {
    { Object* token000 = token;
      Cons* token = ((Cons*)(token000));

      return (token->value == SYM_JAVA_OUTPUT_STELLA_JAVA_EOL);
    }
  }
  else {
  }
  return (false);
}

void javaOutputPrintStream(Cons* exps, boolean nativestreamP) {
  { Object* stream = exps->value;
    boolean foundeolP = false;
    boolean embeddedeolP = false;
    Cons* printitems = NIL;

    { Object* i = NULL;
      Cons* iter000 = exps->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        i = iter000->value;
        if (foundeolP) {
          embeddedeolP = true;
          break;
        }
        if (javaEndOfLineTokenP(i)) {
          foundeolP = true;
        }
      }
    }
    if (embeddedeolP) {
      *(oCURRENT_STREAMo->nativeStream) << "{" << std::endl;
      javaBumpIndent();
    }
    { ConsIterator* it = exps->rest->allocateIterator();

      for (; it->nextP(); ) {
        { Object* item = it->value;

          if (javaEndOfLineTokenP(item)) {
            {
              if (embeddedeolP) {
                javaIndent();
              }
              javaHelpOutputPrintStream(stream, javaReverseAndConsolidateStrings(printitems), nativestreamP, true);
              if (embeddedeolP) {
                *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
              }
              printitems = NIL;
            }
          }
          else {
            printitems = cons(item, printitems);
          }
        }
      }
    }
    if (!(printitems == NIL)) {
      if (embeddedeolP) {
        javaIndent();
      }
      javaHelpOutputPrintStream(stream, javaReverseAndConsolidateStrings(printitems), nativestreamP, false);
      if (embeddedeolP) {
        *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
      }
    }
    if (embeddedeolP) {
      javaUnbumpIndent();
      javaIndent();
      *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
    }
  }
}

boolean javaLiteralStringP(Cons* item) {
  return ((item->value == SYM_JAVA_OUTPUT_STELLA_JAVA_LITERAL) &&
      isaP(item->rest->value, SGT_JAVA_OUTPUT_STELLA_STRING_WRAPPER));
}

Cons* javaReverseAndConsolidateStrings(Cons* items) {
  if (items == NIL) {
    return (NIL);
  }
  { Cons* outputItems = NIL;
    Cons* lastItem = ((Cons*)(items->value));

    { Cons* newItem = NULL;
      Cons* iter000 = items->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        newItem = ((Cons*)(iter000->value));
        if (javaLiteralStringP(newItem)) {
          if (javaLiteralStringP(lastItem)) {
            lastItem = listO(3, SYM_JAVA_OUTPUT_STELLA_JAVA_LITERAL, wrapString(stringConcatenate(((StringWrapper*)(newItem->rest->value))->wrapperValue, ((StringWrapper*)(lastItem->rest->value))->wrapperValue, 0)), NIL);
          }
          else {
            {
              outputItems = cons(lastItem, outputItems);
              lastItem = newItem;
            }
          }
        }
        else {
          {
            outputItems = cons(lastItem, outputItems);
            lastItem = newItem;
          }
        }
      }
    }
    outputItems = cons(lastItem, outputItems);
    return (outputItems);
  }
}

void javaHelpOutputPrintStream(Object* stream, Cons* exps, boolean nativestreamP, boolean endoflineP) {
  if (stream == SYM_JAVA_OUTPUT_STELLA_JAVA_STANDARD_OUT) {
    if (((boolean)(stringGetStellaClass("SYSTEM", false))) ||
        inheritedClassNameConflictsP("SYSTEM")) {
      *(oCURRENT_STREAMo->nativeStream) << "java.lang.System.out";
    }
    else {
      *(oCURRENT_STREAMo->nativeStream) << "System.out";
    }
  }
  else if (stream == SYM_JAVA_OUTPUT_STELLA_JAVA_STANDARD_ERROR) {
    if (((boolean)(stringGetStellaClass("SYSTEM", false))) ||
        inheritedClassNameConflictsP("SYSTEM")) {
      *(oCURRENT_STREAMo->nativeStream) << "java.lang.System.err";
    }
    else {
      *(oCURRENT_STREAMo->nativeStream) << "System.err";
    }
  }
  else {
    javaOutputStatement(stream);
    if (!nativestreamP) {
      *(oCURRENT_STREAMo->nativeStream) << ".nativeStream";
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << ((endoflineP ? ".println(" : ".print("));
  javaMaybeOutputStatementWithParentheses(exps->value);
  { Object* e = NULL;
    Cons* iter000 = exps->rest;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      e = iter000->value;
      *(oCURRENT_STREAMo->nativeStream) << " + ";
      javaMaybeOutputStatementWithParentheses(e);
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << ")";
}

boolean javaIndentableBinaryOperatorP(StringWrapper* operatoR) {
  return (getQuotedTree("((\"||\" \"&&\") \"/STELLA\")", "/STELLA")->memberP(operatoR));
}

boolean javaCommutativeBinaryOperatorP(StringWrapper* operatoR) {
  return (getQuotedTree("((\"+\" \"*\") \"/STELLA\")", "/STELLA")->memberP(operatoR));
}

boolean javaBinaryOperatorP(Object* statement) {
  return (consP(statement) &&
      (SYM_JAVA_OUTPUT_STELLA_JAVA_BINARY_OP == ((Cons*)(statement))->value));
}

boolean javaOperatorP(Object* statement) {
  return (consP(statement) &&
      getQuotedTree("((JAVA_UNARY_OP JAVA_BINARY_OP JAVA_TERNARY_OP JAVA_ASSIGN JAVA_SLOT_VALUE_SETTER) \"/STELLA\")", "/STELLA")->memberP(((Cons*)(statement))->value));
}

void javaOutputUnaryOperator(Cons* expression) {
  { StringWrapper* op = ((StringWrapper*)(expression->value));
    Object* arg = expression->rest->value;

    *(oCURRENT_STREAMo->nativeStream) << op->wrapperValue;
    javaMaybeOutputStatementWithParentheses(arg);
  }
}

boolean javaNestedOperatorNeedsParenthesesP(StringWrapper* op, Object* nested) {
  return (javaOperatorP(nested) &&
      (!(javaCommutativeBinaryOperatorP(op) &&
      stringEqlP(op->wrapperValue, ((StringWrapper*)(((Cons*)(nested))->rest->rest->value))->wrapperValue))));
}

void javaHelpOutputBinaryOperator(Cons* expression, int nestlevel) {
  { Object* arg1 = expression->value;
    StringWrapper* op = ((StringWrapper*)(expression->rest->value));
    Object* arg2 = expression->rest->rest->value;

    if (javaNestedOperatorNeedsParenthesesP(op, arg1)) {
      *(oCURRENT_STREAMo->nativeStream) << "(";
    }
    if (javaBinaryOperatorP(op)) {
      javaHelpOutputBinaryOperator(((Cons*)(arg1))->rest, nestlevel + 1);
    }
    else {
      javaOutputStatement(arg1);
    }
    if (javaNestedOperatorNeedsParenthesesP(op, arg1)) {
      *(oCURRENT_STREAMo->nativeStream) << ")";
    }
    *(oCURRENT_STREAMo->nativeStream) << " ";
    *(oCURRENT_STREAMo->nativeStream) << op->wrapperValue;
    if (javaIndentableBinaryOperatorP(op)) {
      {
        *(oCURRENT_STREAMo->nativeStream) << std::endl;
        javaIndent();
        *(oCURRENT_STREAMo->nativeStream) << "    ";
        { int i = NULL_INTEGER;
          int iter000 = 1;
          int upperBound000 = nestlevel;
          boolean unboundedP000 = upperBound000 == NULL_INTEGER;

          for  (; unboundedP000 ||
                    (iter000 <= upperBound000); 
                iter000 = iter000 + 1) {
            i = iter000;
            i = i;
            *(oCURRENT_STREAMo->nativeStream) << " ";
          }
        }
      }
    }
    else {
      *(oCURRENT_STREAMo->nativeStream) << " ";
    }
    if (javaNestedOperatorNeedsParenthesesP(op, arg2)) {
      *(oCURRENT_STREAMo->nativeStream) << "(";
    }
    if (javaBinaryOperatorP(arg2)) {
      javaHelpOutputBinaryOperator(((Cons*)(arg2))->rest, nestlevel + 1);
    }
    else {
      javaOutputStatement(arg2);
    }
    if (javaNestedOperatorNeedsParenthesesP(op, arg2)) {
      *(oCURRENT_STREAMo->nativeStream) << ")";
    }
  }
}

void javaOutputBinaryOperator(Cons* expression) {
  javaHelpOutputBinaryOperator(expression, 0);
}

void javaOutputTernaryOperator(Cons* expression) {
  { Object* arg1 = expression->value;
    StringWrapper* op1 = ((StringWrapper*)(expression->rest->value));
    Object* arg2 = expression->rest->rest->value;
    StringWrapper* op2 = ((StringWrapper*)(expression->fourth()));
    Object* arg3 = expression->fifth();

    *(oCURRENT_STREAMo->nativeStream) << "(";
    javaMaybeOutputStatementWithParentheses(arg1);
    *(oCURRENT_STREAMo->nativeStream) << " ";
    *(oCURRENT_STREAMo->nativeStream) << op1->wrapperValue;
    *(oCURRENT_STREAMo->nativeStream) << " ";
    javaMaybeOutputStatementWithParentheses(arg2);
    *(oCURRENT_STREAMo->nativeStream) << " ";
    *(oCURRENT_STREAMo->nativeStream) << op2->wrapperValue;
    *(oCURRENT_STREAMo->nativeStream) << " ";
    javaMaybeOutputStatementWithParentheses(arg3);
    *(oCURRENT_STREAMo->nativeStream) << ")";
  }
}

void javaOutputMethodCall(Cons* methodcall) {
  javaMaybeOutputStatementWithParentheses(methodcall->rest->rest->value);
  *(oCURRENT_STREAMo->nativeStream) << ".";
  javaOutputStatement(methodcall->rest->value);
  javaOutputStatement(methodcall->fourth());
}

void javaOutputFunctionCall(Cons* functioncall) {
  javaMaybeOutputStatementWithParentheses(functioncall->value);
  *(oCURRENT_STREAMo->nativeStream) << ".";
  javaOutputStatement(functioncall->rest->value);
  javaOutputStatement(functioncall->rest->rest->value);
}

void javaOutputActualParameters(Cons* parameters) {
  *(oCURRENT_STREAMo->nativeStream) << "(";
  if (((boolean)(parameters->value))) {
    javaOutputStatement(parameters->value);
  }
  { Object* parameter = NULL;
    Cons* iter000 = parameters->rest;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      parameter = iter000->value;
      *(oCURRENT_STREAMo->nativeStream) << ", ";
      javaOutputStatement(parameter);
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << ")";
}

void helpStartupJavaOutput1() {
  {
    SGT_JAVA_OUTPUT_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_CLASS = ((Symbol*)(internRigidSymbolWrtModule("JAVA_CLASS", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_EXCEPTION_CLASS = ((Symbol*)(internRigidSymbolWrtModule("JAVA_EXCEPTION_CLASS", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_NAMED_STATEMENT = ((Symbol*)(internRigidSymbolWrtModule("JAVA_NAMED_STATEMENT", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_STATEMENTS = ((Symbol*)(internRigidSymbolWrtModule("JAVA_STATEMENTS", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_IDENT = ((Symbol*)(internRigidSymbolWrtModule("JAVA_IDENT", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_EOL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_EOL", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_LITERAL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_LITERAL", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_COMMENT = ((Symbol*)(internRigidSymbolWrtModule("JAVA_COMMENT", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_SYMBOL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_SYMBOL", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_CATCH = ((Symbol*)(internRigidSymbolWrtModule("JAVA_CATCH", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_THROW = ((Symbol*)(internRigidSymbolWrtModule("JAVA_THROW", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_UNWIND_PROTECT = ((Symbol*)(internRigidSymbolWrtModule("JAVA_UNWIND_PROTECT", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_HANDLER_CASE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_HANDLER_CASE", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_SIGNAL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_SIGNAL", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_VERBATIM = ((Symbol*)(internRigidSymbolWrtModule("JAVA_VERBATIM", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_CAST = ((Symbol*)(internRigidSymbolWrtModule("JAVA_CAST", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_GLOBAL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_GLOBAL", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_TYPE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_TYPE", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("JAVA_PROGN", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_BLOCK = ((Symbol*)(internRigidSymbolWrtModule("JAVA_BLOCK", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_WITH_PROCESS_LOCK = ((Symbol*)(internRigidSymbolWrtModule("JAVA_WITH_PROCESS_LOCK", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_RETURN = ((Symbol*)(internRigidSymbolWrtModule("JAVA_RETURN", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_MAKE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_MAKE", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCALL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_FUNCALL", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_CODE_CALL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_METHOD_CODE_CALL", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_ASSIGN = ((Symbol*)(internRigidSymbolWrtModule("JAVA_ASSIGN", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_BREAK = ((Symbol*)(internRigidSymbolWrtModule("JAVA_BREAK", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_CONTINUE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_CONTINUE", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_COND = ((Symbol*)(internRigidSymbolWrtModule("JAVA_COND", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_CASE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_CASE", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_IF = ((Symbol*)(internRigidSymbolWrtModule("JAVA_IF", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_WHEN = ((Symbol*)(internRigidSymbolWrtModule("JAVA_WHEN", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_UNLESS = ((Symbol*)(internRigidSymbolWrtModule("JAVA_UNLESS", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_LOOP = ((Symbol*)(internRigidSymbolWrtModule("JAVA_LOOP", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_WHILE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_WHILE", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("JAVA_FOREACH", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("JAVA_SLOT_VALUE", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_SLOT_VALUE_SETTER = ((Symbol*)(internRigidSymbolWrtModule("JAVA_SLOT_VALUE_SETTER", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_UNARY_OP = ((Symbol*)(internRigidSymbolWrtModule("JAVA_UNARY_OP", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_BINARY_OP = ((Symbol*)(internRigidSymbolWrtModule("JAVA_BINARY_OP", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_TERNARY_OP = ((Symbol*)(internRigidSymbolWrtModule("JAVA_TERNARY_OP", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCTION_CALL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_FUNCTION_CALL", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_CALL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_METHOD_CALL", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_ACTUALS = ((Symbol*)(internRigidSymbolWrtModule("JAVA_ACTUALS", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_MAKE_ARRAY = ((Symbol*)(internRigidSymbolWrtModule("JAVA_MAKE_ARRAY", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_ARRAY_INITIALIZER = ((Symbol*)(internRigidSymbolWrtModule("JAVA_ARRAY_INITIALIZER", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_ANONYMOUS_ARRAY = ((Symbol*)(internRigidSymbolWrtModule("JAVA_ANONYMOUS_ARRAY", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_AREF = ((Symbol*)(internRigidSymbolWrtModule("JAVA_AREF", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD = ((Symbol*)(internRigidSymbolWrtModule("JAVA_METHOD", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("JAVA_FUNCTION", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_PRINT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("JAVA_PRINT_STREAM", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_PRINT_NATIVE_STREAM = ((Symbol*)(internRigidSymbolWrtModule("JAVA_PRINT_NATIVE_STREAM", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_DECLARATIONS = ((Symbol*)(internRigidSymbolWrtModule("JAVA_DECLARATIONS", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCTION_POINTER = ((Symbol*)(internRigidSymbolWrtModule("JAVA_FUNCTION_POINTER", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_POINTER = ((Symbol*)(internRigidSymbolWrtModule("JAVA_METHOD_POINTER", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_SETTER_CALL = ((Symbol*)(internRigidSymbolWrtModule("JAVA_METHOD_SETTER_CALL", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_NEW = ((Symbol*)(internRigidSymbolWrtModule("JAVA_NEW", NULL, 0)));
    KWD_JAVA_OUTPUT_NO = ((Keyword*)(internRigidSymbolWrtModule("NO", NULL, 2)));
    KWD_JAVA_OUTPUT_PRESERVE = ((Keyword*)(internRigidSymbolWrtModule("PRESERVE", NULL, 2)));
  }
}

void helpStartupJavaOutput2() {
  {
    KWD_JAVA_OUTPUT_CLEVER = ((Keyword*)(internRigidSymbolWrtModule("CLEVER", NULL, 2)));
    KWD_JAVA_OUTPUT_UPCASE = ((Keyword*)(internRigidSymbolWrtModule("UPCASE", NULL, 2)));
    KWD_JAVA_OUTPUT_TITLECASEX = ((Keyword*)(internRigidSymbolWrtModule("TITLECASEX", NULL, 2)));
    KWD_JAVA_OUTPUT_WHITE_SPACE = ((Keyword*)(internRigidSymbolWrtModule("WHITE-SPACE", NULL, 2)));
    SGT_JAVA_OUTPUT_STELLA_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("STRING-WRAPPER", NULL, 1)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_STANDARD_OUT = ((Symbol*)(internRigidSymbolWrtModule("JAVA_STANDARD_OUT", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_JAVA_STANDARD_ERROR = ((Symbol*)(internRigidSymbolWrtModule("JAVA_STANDARD_ERROR", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_STARTUP_JAVA_OUTPUT = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-JAVA-OUTPUT", NULL, 0)));
    SYM_JAVA_OUTPUT_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupJavaOutput3() {
  {
    defineFunctionObject("JAVA-STELLA-PACKAGE", "(DEFUN (JAVA-STELLA-PACKAGE STRING) ())", ((cpp_function_code)(&javaStellaPackage)), NULL);
    defineFunctionObject("JAVA-OUTPUT-PARSE-TREE", "(DEFUN JAVA-OUTPUT-PARSE-TREE ((CONSTREE CONS)))", ((cpp_function_code)(&javaOutputParseTree)), NULL);
    defineFunctionObject("JAVA-BUMP-INDENT", "(DEFUN JAVA-BUMP-INDENT ())", ((cpp_function_code)(&javaBumpIndent)), NULL);
    defineFunctionObject("JAVA-UNBUMP-INDENT", "(DEFUN JAVA-UNBUMP-INDENT ())", ((cpp_function_code)(&javaUnbumpIndent)), NULL);
    defineFunctionObject("JAVA-INDENT", "(DEFUN JAVA-INDENT ())", ((cpp_function_code)(&javaIndent)), NULL);
    defineFunctionObject("JAVA-OUTPUT-STATEMENT", "(DEFUN JAVA-OUTPUT-STATEMENT ((STATEMENT OBJECT)))", ((cpp_function_code)(&javaOutputStatement)), NULL);
    defineFunctionObject("JAVA-MAYBE-OUTPUT-STATEMENT-WITH-PARENTHESES", "(DEFUN JAVA-MAYBE-OUTPUT-STATEMENT-WITH-PARENTHESES ((STATEMENT OBJECT)))", ((cpp_function_code)(&javaMaybeOutputStatementWithParentheses)), NULL);
    defineFunctionObject("JAVA-OUTPUT-IDENTIFIER", "(DEFUN JAVA-OUTPUT-IDENTIFIER ((IDENTIFIER STRING-WRAPPER)))", ((cpp_function_code)(&javaOutputIdentifier)), NULL);
    defineMethodObject("(DEFMETHOD JAVA-OUTPUT-LITERAL ((OBJECT OBJECT)))", wrapMethodCode(((cpp_method_code)(&Object::javaOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD JAVA-OUTPUT-LITERAL ((STRING STRING)))", wrapFunctionCode(((cpp_function_code)(((void  (*) (const char*))(&stringJavaOutputLiteral))))), NULL);
    defineMethodObject("(DEFMETHOD JAVA-OUTPUT-LITERAL ((STRING STRING-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&StringWrapper::javaOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD JAVA-OUTPUT-LITERAL ((STRING MUTABLE-STRING-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&MutableStringWrapper::javaOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD JAVA-OUTPUT-LITERAL ((CHARACTER CHARACTER-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&CharacterWrapper::javaOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD JAVA-OUTPUT-LITERAL ((INT INTEGER-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&IntegerWrapper::javaOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD JAVA-OUTPUT-LITERAL ((INT LONG-INTEGER-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&LongIntegerWrapper::javaOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD JAVA-OUTPUT-LITERAL ((FLOAT FLOAT-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&FloatWrapper::javaOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD JAVA-OUTPUT-LITERAL ((BOOLEAN BOOLEAN-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&BooleanWrapper::javaOutputLiteral))), NULL);
    defineFunctionObject("JAVA-OUTPUT-MAKE-ARRAY", "(DEFUN JAVA-OUTPUT-MAKE-ARRAY ((STATEMENT CONS)))", ((cpp_function_code)(&javaOutputMakeArray)), NULL);
    defineFunctionObject("JAVA-OUTPUT-ARRAY", "(DEFUN JAVA-OUTPUT-ARRAY ((ARRAYELEMENTS CONS)))", ((cpp_function_code)(&javaOutputArray)), NULL);
    defineFunctionObject("JAVA-OUTPUT-ANONYMOUS-ARRAY", "(DEFUN JAVA-OUTPUT-ANONYMOUS-ARRAY ((STATEMENT CONS)))", ((cpp_function_code)(&javaOutputAnonymousArray)), NULL);
    defineFunctionObject("JAVA-OUTPUT-AREF", "(DEFUN JAVA-OUTPUT-AREF ((STATEMENT CONS)))", ((cpp_function_code)(&javaOutputAref)), NULL);
    defineFunctionObject("JAVA-OUTPUT-SLOT-VALUE", "(DEFUN JAVA-OUTPUT-SLOT-VALUE ((STATEMENT CONS)))", ((cpp_function_code)(&javaOutputSlotValue)), NULL);
    defineFunctionObject("JAVA-OUTPUT-SLOT-VALUE-SETTER", "(DEFUN JAVA-OUTPUT-SLOT-VALUE-SETTER ((STATEMENT CONS)))", ((cpp_function_code)(&javaOutputSlotValueSetter)), NULL);
    defineFunctionObject("JAVA-OUTPUT-IMPLEMENTS-INTERFACES", "(DEFUN JAVA-OUTPUT-IMPLEMENTS-INTERFACES ((INTERFACELIST (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&javaOutputImplementsInterfaces)), NULL);
    defineFunctionObject("JAVA-OUTPUT-CLASS", "(DEFUN JAVA-OUTPUT-CLASS ((CLASSDEF CONS) (EXCEPTIONCLASS? BOOLEAN)))", ((cpp_function_code)(&javaOutputClass)), NULL);
    defineFunctionObject("JAVA-OUTPUT-CLASS-DECLARATION", "(DEFUN JAVA-OUTPUT-CLASS-DECLARATION ((CLASSDEF CONS)))", ((cpp_function_code)(&javaOutputClassDeclaration)), NULL);
    defineFunctionObject("JAVA-OUTPUT-CLASS-VARIABLE-DEFINITIONS", "(DEFUN JAVA-OUTPUT-CLASS-VARIABLE-DEFINITIONS ((VARIABLETRANSLATIONS CONS)))", ((cpp_function_code)(&javaOutputClassVariableDefinitions)), NULL);
    defineFunctionObject("JAVA-OUTPUT-CLASS-CONSTRUCTORS", "(DEFUN JAVA-OUTPUT-CLASS-CONSTRUCTORS ((CONSTRUCTORS (CONS OF TRANSLATION-UNIT)) (CLASSNAME STRING) (EXCEPTIONCLASS? BOOLEAN)))", ((cpp_function_code)(&javaOutputClassConstructors)), NULL);
    defineFunctionObject("JAVA-OUTPUT-CLASS-METHODS", "(DEFUN JAVA-OUTPUT-CLASS-METHODS ((METHODS (CONS OF TRANSLATION-UNIT))))", ((cpp_function_code)(&javaOutputClassMethods)), NULL);
    defineFunctionObject("JAVA-OUTPUT-EXCEPTION-CONSTRUCTOR", "(DEFUN JAVA-OUTPUT-EXCEPTION-CONSTRUCTOR ((EXCEPTIONNAME STRING)))", ((cpp_function_code)(&javaOutputExceptionConstructor)), NULL);
    defineFunctionObject("JAVA-OUTPUT-NAMED-STATEMENT", "(DEFUN JAVA-OUTPUT-NAMED-STATEMENT ((NAMEDSTATEMENT CONS)))", ((cpp_function_code)(&javaOutputNamedStatement)), NULL);
    defineFunctionObject("JAVA-OUTPUT-FORMAL-PARAMETERS", "(DEFUN JAVA-OUTPUT-FORMAL-PARAMETERS ((PARAMETERS (CONS OF CONS))))", ((cpp_function_code)(&javaOutputFormalParameters)), NULL);
    defineFunctionObject("JAVA-OUTPUT-METHOD-SIGNATURE", "(DEFUN JAVA-OUTPUT-METHOD-SIGNATURE ((METHOD CONS)))", ((cpp_function_code)(&javaOutputMethodSignature)), NULL);
    defineFunctionObject("JAVA-SEPARATE-COMMENT-FROM-BODY", "(DEFUN (JAVA-SEPARATE-COMMENT-FROM-BODY CONS CONS) ((BODY CONS)))", ((cpp_function_code)(&javaSeparateCommentFromBody)), NULL);
    defineFunctionObject("JAVA-OUTPUT-METHOD", "(DEFUN JAVA-OUTPUT-METHOD ((METHOD CONS)))", ((cpp_function_code)(&javaOutputMethod)), NULL);
    defineMethodObject("(DEFMETHOD JAVA-OUTPUT-LITERAL ((CONS CONS)))", wrapMethodCode(((cpp_method_code)(&Cons::javaOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD JAVA-OUTPUT-LITERAL ((TREE QUOTED-EXPRESSION)))", wrapMethodCode(((cpp_method_code)(&QuotedExpression::javaOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD JAVA-OUTPUT-LITERAL ((SYMBOL SYMBOL)))", wrapMethodCode(((cpp_method_code)(&Symbol::javaOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD JAVA-OUTPUT-LITERAL ((SURROGATE SURROGATE)))", wrapMethodCode(((cpp_method_code)(&Surrogate::javaOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD JAVA-OUTPUT-LITERAL ((KEYWORD KEYWORD)))", wrapMethodCode(((cpp_method_code)(&Keyword::javaOutputLiteral))), NULL);
    defineFunctionObject("JAVA-OUTPUT-TYPE-EXPRESSION", "(DEFUN JAVA-OUTPUT-TYPE-EXPRESSION ((TYPEEXPRESSION (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&javaOutputTypeExpression)), NULL);
    defineFunctionObject("JAVA-OUTPUT-SEMICOLON?", "(DEFUN (JAVA-OUTPUT-SEMICOLON? BOOLEAN) ((STATEMENT CONS)))", ((cpp_function_code)(&javaOutputSemicolonP)), NULL);
    defineFunctionObject("JAVA-INDENT-STATEMENT?", "(DEFUN (JAVA-INDENT-STATEMENT? BOOLEAN) ((STATEMENT CONS)))", ((cpp_function_code)(&javaIndentStatementP)), NULL);
    defineFunctionObject("JAVA-ILLEGAL-STATEMENT?", "(DEFUN (JAVA-ILLEGAL-STATEMENT? BOOLEAN) ((STATEMENT CONS)))", ((cpp_function_code)(&javaIllegalStatementP)), NULL);
    defineFunctionObject("JAVA-OUTPUT-STATEMENTS", "(DEFUN JAVA-OUTPUT-STATEMENTS ((STATEMENTLIST CONS)))", ((cpp_function_code)(&javaOutputStatements)), NULL);
    defineFunctionObject("JAVA-OUTPUT-DECLARATIONS", "(DEFUN JAVA-OUTPUT-DECLARATIONS ((DECLARATIONS (CONS OF CONS))))", ((cpp_function_code)(&javaOutputDeclarations)), NULL);
    defineFunctionObject("JAVA-HEURISTICALLY-TRANSLATE-NAME", "(DEFUN (JAVA-HEURISTICALLY-TRANSLATE-NAME STRING) ((STELLA-NAME STRING) (CASE-CONVERTED-NAME-LIST (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&javaHeuristicallyTranslateName)), NULL);
    defineFunctionObject("JAVA-OUTPUT-COMMENT-STRING", "(DEFUN JAVA-OUTPUT-COMMENT-STRING ((COMMENT STRING) (COMMENT-START STRING) (COMMENT-CONTINUATION STRING) (COMMENT-END STRING) (JAVADOC-COMMENT? BOOLEAN) (CASE-CONVERTED-NAME-LIST (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&javaOutputCommentString)), NULL);
    defineFunctionObject("JAVA-OUTPUT-COMMENT", "(DEFUN JAVA-OUTPUT-COMMENT ((TREE STRING-WRAPPER)))", ((cpp_function_code)(&javaOutputComment)), NULL);
    defineFunctionObject("JAVA-OUTPUT-JAVADOC-COMMENT", "(DEFUN JAVA-OUTPUT-JAVADOC-COMMENT ((TREE STRING-WRAPPER) (PARAMETER-NAMES-AND-TYPES (CONS OF (CONS OF STRING-WRAPPER))) (RETURN-VALUE STRING-WRAPPER) (AUTHOR STRING) (VERSION STRING)))", ((cpp_function_code)(&javaOutputJavadocComment)), NULL);
    defineFunctionObject("FIXUP-DOCUMENTATION-STRING-QUOTING", "(DEFUN (FIXUP-DOCUMENTATION-STRING-QUOTING STRING) ((DOCUMENTATION STRING)))", ((cpp_function_code)(&fixupDocumentationStringQuoting)), NULL);
    defineFunctionObject("JAVA-OUTPUT-VERBATIM", "(DEFUN JAVA-OUTPUT-VERBATIM ((VERBATIMSTATEMENT STRING-WRAPPER)))", ((cpp_function_code)(&javaOutputVerbatim)), NULL);
    defineFunctionObject("JAVA-OUTPUT-MAKE", "(DEFUN JAVA-OUTPUT-MAKE ((STATEMENT CONS)))", ((cpp_function_code)(&javaOutputMake)), NULL);
    defineFunctionObject("JAVA-OUTPUT-CAST", "(DEFUN JAVA-OUTPUT-CAST ((TREE CONS)))", ((cpp_function_code)(&javaOutputCast)), NULL);
    defineFunctionObject("JAVA-OUTPUT-PROGN", "(DEFUN JAVA-OUTPUT-PROGN ((PROGN CONS)))", ((cpp_function_code)(&javaOutputProgn)), NULL);
    defineFunctionObject("JAVA-OUTPUT-BLOCK", "(DEFUN JAVA-OUTPUT-BLOCK ((BLOCK CONS)))", ((cpp_function_code)(&javaOutputBlock)), NULL);
    defineFunctionObject("JAVA-OUTPUT-WITH-PROCESS-LOCK", "(DEFUN JAVA-OUTPUT-WITH-PROCESS-LOCK ((SYNCH CONS)))", ((cpp_function_code)(&javaOutputWithProcessLock)), NULL);
    defineFunctionObject("JAVA-OUTPUT-RETURN", "(DEFUN JAVA-OUTPUT-RETURN ((RETURNSTATEMENT CONS)))", ((cpp_function_code)(&javaOutputReturn)), NULL);
    defineFunctionObject("JAVA-OUTPUT-THROW", "(DEFUN JAVA-OUTPUT-THROW ((TREE CONS)))", ((cpp_function_code)(&javaOutputThrow)), NULL);
    defineFunctionObject("JAVA-OUTPUT-CATCH", "(DEFUN JAVA-OUTPUT-CATCH ((TREE CONS)))", ((cpp_function_code)(&javaOutputCatch)), NULL);
  }
}

void startupJavaOutput() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupJavaOutput1();
      helpStartupJavaOutput2();
    }
    if (currentStartupTimePhaseP(4)) {
      oJAVA_STELLA_PACKAGE_MAPPINGo = newKeyValueList();
      oJAVA_SEMICOLON_STATEMENTSo = listO(22, SYM_JAVA_OUTPUT_STELLA_JAVA_ASSIGN, SYM_JAVA_OUTPUT_STELLA_JAVA_UNARY_OP, SYM_JAVA_OUTPUT_STELLA_JAVA_BINARY_OP, SYM_JAVA_OUTPUT_STELLA_JAVA_TERNARY_OP, SYM_JAVA_OUTPUT_STELLA_JAVA_CAST, SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCALL, SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCTION_CALL, SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCTION_POINTER, SYM_JAVA_OUTPUT_STELLA_JAVA_MAKE, SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_CALL, SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_CODE_CALL, SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_POINTER, SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_SETTER_CALL, SYM_JAVA_OUTPUT_STELLA_JAVA_NEW, SYM_JAVA_OUTPUT_STELLA_JAVA_PRINT_NATIVE_STREAM, SYM_JAVA_OUTPUT_STELLA_JAVA_PRINT_STREAM, SYM_JAVA_OUTPUT_STELLA_JAVA_RETURN, SYM_JAVA_OUTPUT_STELLA_JAVA_SIGNAL, SYM_JAVA_OUTPUT_STELLA_JAVA_SLOT_VALUE_SETTER, SYM_JAVA_OUTPUT_STELLA_JAVA_THROW, SYM_JAVA_OUTPUT_STELLA_JAVA_VERBATIM, NIL);
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupJavaOutput3();
      defineFunctionObject("JAVA-OUTPUT-UNWIND-PROTECT", "(DEFUN JAVA-OUTPUT-UNWIND-PROTECT ((TREE CONS)))", ((cpp_function_code)(&javaOutputUnwindProtect)), NULL);
      defineFunctionObject("JAVA-OUTPUT-HANDLER-CASE", "(DEFUN JAVA-OUTPUT-HANDLER-CASE ((TREE CONS)))", ((cpp_function_code)(&javaOutputHandlerCase)), NULL);
      defineFunctionObject("JAVA-OUTPUT-SIGNAL", "(DEFUN JAVA-OUTPUT-SIGNAL ((TREE CONS)))", ((cpp_function_code)(&javaOutputSignal)), NULL);
      defineFunctionObject("JAVA-OUTPUT-GLOBAL-DEFINITION", "(DEFUN JAVA-OUTPUT-GLOBAL-DEFINITION ((GLOBAL CONS)))", ((cpp_function_code)(&javaOutputGlobalDefinition)), NULL);
      defineFunctionObject("JAVA-OUTPUT-ACTUALS-AS-CONS-EXPRESSION", "(DEFUN JAVA-OUTPUT-ACTUALS-AS-CONS-EXPRESSION ((ARGLIST CONS)))", ((cpp_function_code)(&javaOutputActualsAsConsExpression)), NULL);
      defineFunctionObject("JAVA-OUTPUT-FUNCALL", "(DEFUN JAVA-OUTPUT-FUNCALL ((FUNCALL CONS)))", ((cpp_function_code)(&javaOutputFuncall)), NULL);
      defineFunctionObject("JAVA-OUTPUT-METHOD-CODE-CALL", "(DEFUN JAVA-OUTPUT-METHOD-CODE-CALL ((METHODCALL CONS)))", ((cpp_function_code)(&javaOutputMethodCodeCall)), NULL);
      defineFunctionObject("JAVA-OUTPUT-BREAK", "(DEFUN JAVA-OUTPUT-BREAK ((TAG CONS)))", ((cpp_function_code)(&javaOutputBreak)), NULL);
      defineFunctionObject("JAVA-OUTPUT-CONTINUE", "(DEFUN JAVA-OUTPUT-CONTINUE ((TAG CONS)))", ((cpp_function_code)(&javaOutputContinue)), NULL);
      defineFunctionObject("JAVA-STATEMENT-RETURNS?", "(DEFUN (JAVA-STATEMENT-RETURNS? BOOLEAN) ((STATEMENT CONS)))", ((cpp_function_code)(&javaStatementReturnsP)), NULL);
      defineFunctionObject("JAVA-LAST-STATEMENT-RETURNS?", "(DEFUN (JAVA-LAST-STATEMENT-RETURNS? BOOLEAN) ((STATEMENTS CONS)))", ((cpp_function_code)(&javaLastStatementReturnsP)), NULL);
      defineFunctionObject("JAVA-OUTPUT-CASE", "(DEFUN JAVA-OUTPUT-CASE ((CASE CONS)))", ((cpp_function_code)(&javaOutputCase)), NULL);
      defineFunctionObject("JAVA-OUTPUT-COND", "(DEFUN JAVA-OUTPUT-COND ((COND CONS)))", ((cpp_function_code)(&javaOutputCond)), NULL);
      defineFunctionObject("JAVA-PROGN?", "(DEFUN (JAVA-PROGN? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&javaPrognP)), NULL);
      defineFunctionObject("JAVA-BLOCK?", "(DEFUN (JAVA-BLOCK? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&javaBlockP)), NULL);
      defineFunctionObject("JAVA-OUTPUT-IF", "(DEFUN JAVA-OUTPUT-IF ((TREE CONS)))", ((cpp_function_code)(&javaOutputIf)), NULL);
      defineFunctionObject("JAVA-OUTPUT-WHEN", "(DEFUN JAVA-OUTPUT-WHEN ((TREE CONS)))", ((cpp_function_code)(&javaOutputWhen)), NULL);
      defineFunctionObject("JAVA-OUTPUT-UNLESS", "(DEFUN JAVA-OUTPUT-UNLESS ((TREE CONS)))", ((cpp_function_code)(&javaOutputUnless)), NULL);
      defineFunctionObject("JAVA-OUTPUT-ASSIGNMENT", "(DEFUN JAVA-OUTPUT-ASSIGNMENT ((ASSIGNMENT CONS)))", ((cpp_function_code)(&javaOutputAssignment)), NULL);
      defineFunctionObject("JAVA-OUTPUT-LOOP", "(DEFUN JAVA-OUTPUT-LOOP ((LOOP CONS)))", ((cpp_function_code)(&javaOutputLoop)), NULL);
      defineFunctionObject("JAVA-OUTPUT-WHILE", "(DEFUN JAVA-OUTPUT-WHILE ((LOOP CONS)))", ((cpp_function_code)(&javaOutputWhile)), NULL);
      defineFunctionObject("JAVA-OUTPUT-FOREACH", "(DEFUN JAVA-OUTPUT-FOREACH ((LOOP CONS)))", ((cpp_function_code)(&javaOutputForeach)), NULL);
      defineFunctionObject("JAVA-END-OF-LINE-TOKEN?", "(DEFUN (JAVA-END-OF-LINE-TOKEN? BOOLEAN) ((TOKEN OBJECT)))", ((cpp_function_code)(&javaEndOfLineTokenP)), NULL);
      defineFunctionObject("JAVA-OUTPUT-PRINT-STREAM", "(DEFUN JAVA-OUTPUT-PRINT-STREAM ((EXPS CONS) (NATIVESTREAM? BOOLEAN)))", ((cpp_function_code)(&javaOutputPrintStream)), NULL);
      defineFunctionObject("JAVA-LITERAL-STRING?", "(DEFUN (JAVA-LITERAL-STRING? BOOLEAN) ((ITEM CONS)))", ((cpp_function_code)(&javaLiteralStringP)), NULL);
      defineFunctionObject("JAVA-REVERSE-AND-CONSOLIDATE-STRINGS", "(DEFUN (JAVA-REVERSE-AND-CONSOLIDATE-STRINGS CONS) ((ITEMS (CONS OF CONS))))", ((cpp_function_code)(&javaReverseAndConsolidateStrings)), NULL);
      defineFunctionObject("JAVA-HELP-OUTPUT-PRINT-STREAM", "(DEFUN JAVA-HELP-OUTPUT-PRINT-STREAM ((STREAM OBJECT) (EXPS CONS) (NATIVESTREAM? BOOLEAN) (ENDOFLINE? BOOLEAN)))", ((cpp_function_code)(&javaHelpOutputPrintStream)), NULL);
      defineFunctionObject("JAVA-INDENTABLE-BINARY-OPERATOR?", "(DEFUN (JAVA-INDENTABLE-BINARY-OPERATOR? BOOLEAN) ((OPERATOR STRING-WRAPPER)))", ((cpp_function_code)(&javaIndentableBinaryOperatorP)), NULL);
      defineFunctionObject("JAVA-COMMUTATIVE-BINARY-OPERATOR?", "(DEFUN (JAVA-COMMUTATIVE-BINARY-OPERATOR? BOOLEAN) ((OPERATOR STRING-WRAPPER)))", ((cpp_function_code)(&javaCommutativeBinaryOperatorP)), NULL);
      defineFunctionObject("JAVA-BINARY-OPERATOR?", "(DEFUN (JAVA-BINARY-OPERATOR? BOOLEAN) ((STATEMENT OBJECT)))", ((cpp_function_code)(&javaBinaryOperatorP)), NULL);
      defineFunctionObject("JAVA-OPERATOR?", "(DEFUN (JAVA-OPERATOR? BOOLEAN) ((STATEMENT OBJECT)))", ((cpp_function_code)(&javaOperatorP)), NULL);
      defineFunctionObject("JAVA-OUTPUT-UNARY-OPERATOR", "(DEFUN JAVA-OUTPUT-UNARY-OPERATOR ((EXPRESSION CONS)))", ((cpp_function_code)(&javaOutputUnaryOperator)), NULL);
      defineFunctionObject("JAVA-NESTED-OPERATOR-NEEDS-PARENTHESES?", "(DEFUN (JAVA-NESTED-OPERATOR-NEEDS-PARENTHESES? BOOLEAN) ((OP STRING-WRAPPER) (NESTED OBJECT)))", ((cpp_function_code)(&javaNestedOperatorNeedsParenthesesP)), NULL);
      defineFunctionObject("JAVA-HELP-OUTPUT-BINARY-OPERATOR", "(DEFUN JAVA-HELP-OUTPUT-BINARY-OPERATOR ((EXPRESSION CONS) (NESTLEVEL INTEGER)))", ((cpp_function_code)(&javaHelpOutputBinaryOperator)), NULL);
      defineFunctionObject("JAVA-OUTPUT-BINARY-OPERATOR", "(DEFUN JAVA-OUTPUT-BINARY-OPERATOR ((EXPRESSION CONS)))", ((cpp_function_code)(&javaOutputBinaryOperator)), NULL);
      defineFunctionObject("JAVA-OUTPUT-TERNARY-OPERATOR", "(DEFUN JAVA-OUTPUT-TERNARY-OPERATOR ((EXPRESSION CONS)))", ((cpp_function_code)(&javaOutputTernaryOperator)), NULL);
      defineFunctionObject("JAVA-OUTPUT-METHOD-CALL", "(DEFUN JAVA-OUTPUT-METHOD-CALL ((METHODCALL CONS)))", ((cpp_function_code)(&javaOutputMethodCall)), NULL);
      defineFunctionObject("JAVA-OUTPUT-FUNCTION-CALL", "(DEFUN JAVA-OUTPUT-FUNCTION-CALL ((FUNCTIONCALL CONS)))", ((cpp_function_code)(&javaOutputFunctionCall)), NULL);
      defineFunctionObject("JAVA-OUTPUT-ACTUAL-PARAMETERS", "(DEFUN JAVA-OUTPUT-ACTUAL-PARAMETERS ((PARAMETERS CONS)))", ((cpp_function_code)(&javaOutputActualParameters)), NULL);
      defineFunctionObject("STARTUP-JAVA-OUTPUT", "(DEFUN STARTUP-JAVA-OUTPUT () :PUBLIC? TRUE)", ((cpp_function_code)(&startupJavaOutput)), NULL);
      { MethodSlot* function = lookupFunction(SYM_JAVA_OUTPUT_STELLA_STARTUP_JAVA_OUTPUT);

        setDynamicSlotValue(function->dynamicSlots, SYM_JAVA_OUTPUT_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupJavaOutput"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFSPECIAL *JAVA-INDENT-CHARS* INTEGER 0)", &oJAVA_INDENT_CHARSo);
      defineGlobalVariableObject("(DEFGLOBAL *JAVA-STELLA-PACKAGE-MAPPING* (KEY-VALUE-LIST OF STRING-WRAPPER STRING-WRAPPER) (NEW (KEY-VALUE-LIST OF STRING-WRAPPER STRING-WRAPPER)))", &oJAVA_STELLA_PACKAGE_MAPPINGo);
      defineGlobalVariableObject("(DEFGLOBAL *JAVA-SEMICOLON-STATEMENTS* (CONS OF SYMBOL) (BQUOTE (JAVA_ASSIGN JAVA_UNARY_OP JAVA_BINARY_OP JAVA_TERNARY_OP JAVA_CAST JAVA_FUNCALL JAVA_FUNCTION_CALL JAVA_FUNCTION_POINTER JAVA_MAKE JAVA_METHOD_CALL JAVA_METHOD_CODE_CALL JAVA_METHOD_POINTER JAVA_METHOD_SETTER_CALL JAVA_NEW JAVA_PRINT_NATIVE_STREAM JAVA_PRINT_STREAM JAVA_RETURN JAVA_SIGNAL JAVA_SLOT_VALUE_SETTER JAVA_THROW JAVA_VERBATIM)))", &oJAVA_SEMICOLON_STATEMENTSo);
    }
  }
}

Surrogate* SGT_JAVA_OUTPUT_STELLA_CONS = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_CLASS = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_EXCEPTION_CLASS = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_NAMED_STATEMENT = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_STATEMENTS = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_IDENT = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_EOL = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_LITERAL = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_COMMENT = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_SYMBOL = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_CATCH = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_THROW = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_UNWIND_PROTECT = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_HANDLER_CASE = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_SIGNAL = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_VERBATIM = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_CAST = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_GLOBAL = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_TYPE = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_PROGN = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_BLOCK = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_WITH_PROCESS_LOCK = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_RETURN = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_MAKE = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCALL = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_CODE_CALL = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_ASSIGN = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_BREAK = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_CONTINUE = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_COND = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_CASE = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_IF = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_WHEN = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_UNLESS = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_LOOP = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_WHILE = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_FOREACH = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_SLOT_VALUE = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_SLOT_VALUE_SETTER = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_UNARY_OP = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_BINARY_OP = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_TERNARY_OP = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCTION_CALL = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_CALL = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_ACTUALS = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_MAKE_ARRAY = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_ARRAY_INITIALIZER = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_ANONYMOUS_ARRAY = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_AREF = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCTION = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_PRINT_STREAM = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_PRINT_NATIVE_STREAM = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_DECLARATIONS = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCTION_POINTER = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_POINTER = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_SETTER_CALL = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_NEW = NULL;

Keyword* KWD_JAVA_OUTPUT_NO = NULL;

Keyword* KWD_JAVA_OUTPUT_PRESERVE = NULL;

Keyword* KWD_JAVA_OUTPUT_CLEVER = NULL;

Keyword* KWD_JAVA_OUTPUT_UPCASE = NULL;

Keyword* KWD_JAVA_OUTPUT_TITLECASEX = NULL;

Keyword* KWD_JAVA_OUTPUT_WHITE_SPACE = NULL;

Surrogate* SGT_JAVA_OUTPUT_STELLA_STRING_WRAPPER = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_STANDARD_OUT = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_STANDARD_ERROR = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_STARTUP_JAVA_OUTPUT = NULL;

Symbol* SYM_JAVA_OUTPUT_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
