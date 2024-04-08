//  -*- Mode: C++ -*-

// idl-output.cc

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

DEFINE_STELLA_SPECIAL(oIDL_INDENT_CHARSo, int , 0);

void idlOutputParseTree(Cons* constree) {
  { 
    BIND_STELLA_SPECIAL(oIDL_INDENT_CHARSo, int, 0);
    idlOutputStatement(constree);
  }
}

void idlOutputStatement(Object* statement) {
  if (safePrimaryType(statement) == SGT_IDL_OUTPUT_STELLA_CONS) {
    { Object* statement000 = statement;
      Cons* statement = ((Cons*)(statement000));

      if (statement == NIL) {
        return;
      }
      if (consP(statement->value) ||
          (!((boolean)(statement->value)))) {
        {
          idlOutputStatement(statement->value);
          idlOutputStatement(statement->rest);
        }
      }
      else {
        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(statement->value));

          if (testValue000 == SYM_IDL_OUTPUT_STELLA_IDL_COMMENT) {
            idlOutputComment(((StringWrapper*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_IDL_OUTPUT_STELLA_IDL_TYPEDEF) {
            idlOutputTypedef(statement->rest);
          }
          else if (testValue000 == SYM_IDL_OUTPUT_STELLA_IDL_ENUM) {
            idlOutputEnum(statement->rest);
          }
          else if (testValue000 == SYM_IDL_OUTPUT_STELLA_IDL_INTERFACE) {
            idlOutputInterface(((Cons*)(statement->rest)));
          }
          else if (testValue000 == SYM_IDL_OUTPUT_STELLA_IDL_STRUCT) {
            idlOutputStruct(((Cons*)(statement->rest)));
          }
          else if (testValue000 == SYM_IDL_OUTPUT_STELLA_IDL_DECLARATIONS) {
            idlOutputDeclarations(((Cons*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_IDL_OUTPUT_STELLA_IDL_IDENT) {
            idlOutputIdentifier(((StringWrapper*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_IDL_OUTPUT_STELLA_IDL_TYPE) {
            idlOutputTypeExpression(((Cons*)(statement->rest)));
          }
          else if (testValue000 == SYM_IDL_OUTPUT_STELLA_IDL_SIGNATURES) {
            idlOutputSignatures(((Cons*)(statement->rest->value)));
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
    idlOutputAtomicExpression(statement);
  }
}

void idlIndent() {
  { int i = NULL_INTEGER;
    int iter000 = 1;
    int upperBound000 = oIDL_INDENT_CHARSo;
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

void idlBumpIndent() {
  oIDL_INDENT_CHARSo = oIDL_INDENT_CHARSo + 2;
}

void idlUnbumpIndent() {
  oIDL_INDENT_CHARSo = oIDL_INDENT_CHARSo - 2;
}

void idlOutputTypedef(Cons* typedeF) {
  *(oCURRENT_STREAMo->nativeStream) << "typedef " << ((StringWrapper*)(typedeF->rest->value))->wrapperValue << " " << ((StringWrapper*)(typedeF->value))->wrapperValue << ";" << std::endl << std::endl;
}

void idlOutputEnumerands(Cons* enumerands) {
  if (((boolean)(((Cons*)(enumerands->value))))) {
    *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(((Cons*)(enumerands->value))->rest->value))->wrapperValue;
  }
  { Cons* enumerand = NULL;
    Cons* iter000 = enumerands->rest;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      enumerand = ((Cons*)(iter000->value));
      *(oCURRENT_STREAMo->nativeStream) << ", " << ((StringWrapper*)(enumerand->rest->value))->wrapperValue;
    }
  }
}

void idlOutputEnum(Cons* enuM) {
  *(oCURRENT_STREAMo->nativeStream) << "enum {";
  idlOutputEnumerands(((Cons*)(((Cons*)(enuM->nth(4)))->rest->value)));
  *(oCURRENT_STREAMo->nativeStream) << "};" << std::endl << std::endl;
}

void idlOutputTypeExpression(Cons* typeexpression) {
  { StringWrapper* typeexpr = NULL;
    Cons* iter000 = typeexpression;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      typeexpr = ((StringWrapper*)(iter000->value));
      *(oCURRENT_STREAMo->nativeStream) << typeexpr->wrapperValue << " ";
    }
  }
}

void Object::idlOutputLiteral() {
  { Object* object = this;

  }
}

void stringIdlOutputLiteral(const char* string) {
  *(oCURRENT_STREAMo->nativeStream) << "\"" << replaceSubstrings(replaceSubstrings(replaceSubstrings(replaceSubstrings(string, "\\\\", "\\"), "\\\"", makeString(1, '"')), "\\n", makeString(1, '\n')), "\\r", makeString(1, '\r')) << "\"";
}

void StringWrapper::idlOutputLiteral() {
  { StringWrapper* string = this;

    stringIdlOutputLiteral(string->wrapperValue);
  }
}

void MutableStringWrapper::idlOutputLiteral() {
  { MutableStringWrapper* string = this;

    stringIdlOutputLiteral((string->wrapperValue));
  }
}

void QuotedExpression::idlOutputLiteral() {
  { QuotedExpression* tree = this;

    *(oCURRENT_STREAMo->nativeStream) << "\"" << tree << "\"";
  }
}

void Symbol::idlOutputLiteral() {
  { Symbol* symbol = this;

    *(oCURRENT_STREAMo->nativeStream) << idlTranslateSymbolName(symbol)->wrapperValue;
  }
}

void Surrogate::idlOutputLiteral() {
  { Surrogate* surrogate = this;

    *(oCURRENT_STREAMo->nativeStream) << idlTranslateSurrogateName(surrogate)->wrapperValue;
  }
}

void Keyword::idlOutputLiteral() {
  { Keyword* keyword = this;

    *(oCURRENT_STREAMo->nativeStream) << idlTranslateKeywordName(keyword)->wrapperValue;
  }
}

void idlOutputAtomicExpression(Object* atom) {
  atom->idlOutputLiteral();
}

void idlOutputComment(StringWrapper* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "// " << tree->wrapperValue << std::endl;
}

void idlOutputIdentifier(StringWrapper* identifier) {
  *(oCURRENT_STREAMo->nativeStream) << identifier->wrapperValue;
}

void idlOutputDerivedClasses(Cons* classList) {
  if (((boolean)(((StringWrapper*)(classList->value))))) {
    *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(classList->value))->wrapperValue;
  }
  { StringWrapper* clasS = NULL;
    Cons* iter000 = classList->rest;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      clasS = ((StringWrapper*)(iter000->value));
      *(oCURRENT_STREAMo->nativeStream) << ", " << clasS->wrapperValue;
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << " ";
}

void idlOutputTemplateParameters(Cons* parameters) {
  if (!(parameters == NIL)) {
    *(oCURRENT_STREAMo->nativeStream) << "template <class " << ((StringWrapper*)(parameters->value))->wrapperValue;
    { StringWrapper* parameter = NULL;
      Cons* iter000 = parameters->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        parameter = ((StringWrapper*)(iter000->value));
        *(oCURRENT_STREAMo->nativeStream) << ", class " << parameter->wrapperValue;
      }
    }
    *(oCURRENT_STREAMo->nativeStream) << ">" << std::endl;
  }
}

boolean idlOutputTemplateClassesP() {
  return (true);
}

void idlOutputInterface(Cons* classdef) {
  if (idlOutputTemplateClassesP()) {
    idlOutputTemplateParameters(((Cons*)(classdef->rest->value)));
  }
  *(oCURRENT_STREAMo->nativeStream) << "interface " << ((StringWrapper*)(classdef->value))->wrapperValue << " ";
  if (!(((Cons*)(classdef->rest->rest->value)) == NIL)) {
    *(oCURRENT_STREAMo->nativeStream) << ": ";
    idlOutputDerivedClasses(((Cons*)(classdef->rest->rest->value)));
  }
  *(oCURRENT_STREAMo->nativeStream) << "{" << std::endl;
  { Object* statement = NULL;
    Cons* iter000 = classdef->nthRest(4);

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      statement = iter000->value;
      idlOutputStatement(statement);
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << "};" << std::endl << std::endl;
}

void idlOutputStruct(Cons* classdef) {
  if (idlOutputTemplateClassesP()) {
    idlOutputTemplateParameters(((Cons*)(classdef->rest->value)));
  }
  *(oCURRENT_STREAMo->nativeStream) << "struct " << ((StringWrapper*)(classdef->value))->wrapperValue << " ";
  if (!(((Cons*)(classdef->rest->rest->value)) == NIL)) {
    *(oCURRENT_STREAMo->nativeStream) << ": ";
    idlOutputDerivedClasses(((Cons*)(classdef->rest->rest->value)));
  }
  *(oCURRENT_STREAMo->nativeStream) << "{" << std::endl;
  { Object* statement = NULL;
    Cons* iter000 = classdef->nthRest(4);

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      statement = iter000->value;
      idlOutputStatement(statement);
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << "};" << std::endl << std::endl;
}

void idlOutputOneFormalParameter(Cons* parameter) {
  *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(parameter->value))->wrapperValue << " " << ((StringWrapper*)(parameter->rest->value))->wrapperValue << " " << ((StringWrapper*)(parameter->rest->rest->value))->wrapperValue;
}

void idlOutputFormalParameters(Cons* parameters) {
  { int nParameters = parameters->length();

    *(oCURRENT_STREAMo->nativeStream) << "(";
    { Cons* parameter = NULL;
      Cons* iter000 = parameters;
      int n = NULL_INTEGER;
      int iter001 = 1;
      int upperBound000 = nParameters;
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; (!(iter000 == NIL)) &&
                (unboundedP000 ||
                 (iter001 <= upperBound000)); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        parameter = ((Cons*)(iter000->value));
        n = iter001;
        if (n == nParameters) {
          if (parameter->value == SYM_IDL_OUTPUT_STELLA_IDL_VAR_ARGS) {
            {
              *(oCURRENT_STREAMo->nativeStream) << "int ";
              *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(parameter->rest->value))->wrapperValue;
              *(oCURRENT_STREAMo->nativeStream) << ", ...";
            }
          }
          else {
            idlOutputOneFormalParameter(parameter);
          }
        }
        else {
          {
            idlOutputOneFormalParameter(parameter);
            *(oCURRENT_STREAMo->nativeStream) << ", ";
          }
        }
      }
    }
    *(oCURRENT_STREAMo->nativeStream) << ")";
  }
}

void idlOutputFunctionSignature(Cons* function) {
  idlOutputTypeExpression(((Cons*)(function->value)));
  *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(function->rest->value))->wrapperValue;
  idlOutputFormalParameters(((Cons*)(function->rest->rest->value)));
}

void idlOutputDeclarations(Cons* declarations) {
  idlBumpIndent();
  { Cons* declaration = NULL;
    Cons* iter000 = declarations;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      declaration = ((Cons*)(iter000->value));
      idlIndent();
      idlOutputTypeExpression(((Cons*)(declaration->value)));
      *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(declaration->rest->value))->wrapperValue;
      *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
    }
  }
  idlUnbumpIndent();
}

void idlOutputSignature(Cons* signature, boolean outputmethodclassP) {
  idlOutputTypeExpression(((Cons*)(signature->rest->value)));
  if (outputmethodclassP &&
      ((boolean)(signature->value))) {
    *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(signature->value))->wrapperValue;
    *(oCURRENT_STREAMo->nativeStream) << "::";
  }
  *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(signature->rest->rest->value))->wrapperValue;
  idlOutputFormalParameters(((Cons*)(signature->fourth())));
}

void idlOutputSignatures(Cons* signatures) {
  idlIndent();
  idlBumpIndent();
  { Object* signature = NULL;
    Cons* iter000 = signatures;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      signature = iter000->value;
      idlIndent();
      idlOutputSignature(((Cons*)(signature)), false);
      *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
    }
  }
  idlUnbumpIndent();
}

void startupIdlOutput() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SGT_IDL_OUTPUT_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
      SYM_IDL_OUTPUT_STELLA_IDL_COMMENT = ((Symbol*)(internRigidSymbolWrtModule("IDL_COMMENT", NULL, 0)));
      SYM_IDL_OUTPUT_STELLA_IDL_TYPEDEF = ((Symbol*)(internRigidSymbolWrtModule("IDL_TYPEDEF", NULL, 0)));
      SYM_IDL_OUTPUT_STELLA_IDL_ENUM = ((Symbol*)(internRigidSymbolWrtModule("IDL_ENUM", NULL, 0)));
      SYM_IDL_OUTPUT_STELLA_IDL_INTERFACE = ((Symbol*)(internRigidSymbolWrtModule("IDL_INTERFACE", NULL, 0)));
      SYM_IDL_OUTPUT_STELLA_IDL_STRUCT = ((Symbol*)(internRigidSymbolWrtModule("IDL_STRUCT", NULL, 0)));
      SYM_IDL_OUTPUT_STELLA_IDL_DECLARATIONS = ((Symbol*)(internRigidSymbolWrtModule("IDL_DECLARATIONS", NULL, 0)));
      SYM_IDL_OUTPUT_STELLA_IDL_IDENT = ((Symbol*)(internRigidSymbolWrtModule("IDL_IDENT", NULL, 0)));
      SYM_IDL_OUTPUT_STELLA_IDL_TYPE = ((Symbol*)(internRigidSymbolWrtModule("IDL_TYPE", NULL, 0)));
      SYM_IDL_OUTPUT_STELLA_IDL_SIGNATURES = ((Symbol*)(internRigidSymbolWrtModule("IDL_SIGNATURES", NULL, 0)));
      SYM_IDL_OUTPUT_STELLA_IDL_VAR_ARGS = ((Symbol*)(internRigidSymbolWrtModule("IDL_VAR_ARGS", NULL, 0)));
      SYM_IDL_OUTPUT_STELLA_STARTUP_IDL_OUTPUT = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-IDL-OUTPUT", NULL, 0)));
      SYM_IDL_OUTPUT_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("IDL-OUTPUT-PARSE-TREE", "(DEFUN IDL-OUTPUT-PARSE-TREE ((CONSTREE CONS)))", ((cpp_function_code)(&idlOutputParseTree)), NULL);
      defineFunctionObject("IDL-OUTPUT-STATEMENT", "(DEFUN IDL-OUTPUT-STATEMENT ((STATEMENT OBJECT)))", ((cpp_function_code)(&idlOutputStatement)), NULL);
      defineFunctionObject("IDL-INDENT", "(DEFUN IDL-INDENT ())", ((cpp_function_code)(&idlIndent)), NULL);
      defineFunctionObject("IDL-BUMP-INDENT", "(DEFUN IDL-BUMP-INDENT ())", ((cpp_function_code)(&idlBumpIndent)), NULL);
      defineFunctionObject("IDL-UNBUMP-INDENT", "(DEFUN IDL-UNBUMP-INDENT ())", ((cpp_function_code)(&idlUnbumpIndent)), NULL);
      defineFunctionObject("IDL-OUTPUT-TYPEDEF", "(DEFUN IDL-OUTPUT-TYPEDEF ((TYPEDEF CONS)))", ((cpp_function_code)(&idlOutputTypedef)), NULL);
      defineFunctionObject("IDL-OUTPUT-ENUMERANDS", "(DEFUN IDL-OUTPUT-ENUMERANDS ((ENUMERANDS (CONS OF CONS))))", ((cpp_function_code)(&idlOutputEnumerands)), NULL);
      defineFunctionObject("IDL-OUTPUT-ENUM", "(DEFUN IDL-OUTPUT-ENUM ((ENUM CONS)))", ((cpp_function_code)(&idlOutputEnum)), NULL);
      defineFunctionObject("IDL-OUTPUT-TYPE-EXPRESSION", "(DEFUN IDL-OUTPUT-TYPE-EXPRESSION ((TYPEEXPRESSION (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&idlOutputTypeExpression)), NULL);
      defineMethodObject("(DEFMETHOD IDL-OUTPUT-LITERAL ((OBJECT OBJECT)))", wrapMethodCode(((cpp_method_code)(&Object::idlOutputLiteral))), NULL);
      defineMethodObject("(DEFMETHOD IDL-OUTPUT-LITERAL ((STRING STRING)))", wrapFunctionCode(((cpp_function_code)(((void  (*) (const char*))(&stringIdlOutputLiteral))))), NULL);
      defineMethodObject("(DEFMETHOD IDL-OUTPUT-LITERAL ((STRING STRING-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&StringWrapper::idlOutputLiteral))), NULL);
      defineMethodObject("(DEFMETHOD IDL-OUTPUT-LITERAL ((STRING MUTABLE-STRING-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&MutableStringWrapper::idlOutputLiteral))), NULL);
      defineMethodObject("(DEFMETHOD IDL-OUTPUT-LITERAL ((TREE QUOTED-EXPRESSION)))", wrapMethodCode(((cpp_method_code)(&QuotedExpression::idlOutputLiteral))), NULL);
      defineMethodObject("(DEFMETHOD IDL-OUTPUT-LITERAL ((SYMBOL SYMBOL)))", wrapMethodCode(((cpp_method_code)(&Symbol::idlOutputLiteral))), NULL);
      defineMethodObject("(DEFMETHOD IDL-OUTPUT-LITERAL ((SURROGATE SURROGATE)))", wrapMethodCode(((cpp_method_code)(&Surrogate::idlOutputLiteral))), NULL);
      defineMethodObject("(DEFMETHOD IDL-OUTPUT-LITERAL ((KEYWORD KEYWORD)))", wrapMethodCode(((cpp_method_code)(&Keyword::idlOutputLiteral))), NULL);
      defineFunctionObject("IDL-OUTPUT-ATOMIC-EXPRESSION", "(DEFUN IDL-OUTPUT-ATOMIC-EXPRESSION ((ATOM OBJECT)))", ((cpp_function_code)(&idlOutputAtomicExpression)), NULL);
      defineFunctionObject("IDL-OUTPUT-COMMENT", "(DEFUN IDL-OUTPUT-COMMENT ((TREE STRING-WRAPPER)))", ((cpp_function_code)(&idlOutputComment)), NULL);
      defineFunctionObject("IDL-OUTPUT-IDENTIFIER", "(DEFUN IDL-OUTPUT-IDENTIFIER ((IDENTIFIER STRING-WRAPPER)))", ((cpp_function_code)(&idlOutputIdentifier)), NULL);
      defineFunctionObject("IDL-OUTPUT-DERIVED-CLASSES", "(DEFUN IDL-OUTPUT-DERIVED-CLASSES ((CLASS-LIST (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&idlOutputDerivedClasses)), NULL);
      defineFunctionObject("IDL-OUTPUT-TEMPLATE-PARAMETERS", "(DEFUN IDL-OUTPUT-TEMPLATE-PARAMETERS ((PARAMETERS (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&idlOutputTemplateParameters)), NULL);
      defineFunctionObject("IDL-OUTPUT-TEMPLATE-CLASSES?", "(DEFUN (IDL-OUTPUT-TEMPLATE-CLASSES? BOOLEAN) ())", ((cpp_function_code)(&idlOutputTemplateClassesP)), NULL);
      defineFunctionObject("IDL-OUTPUT-INTERFACE", "(DEFUN IDL-OUTPUT-INTERFACE ((CLASSDEF CONS)))", ((cpp_function_code)(&idlOutputInterface)), NULL);
      defineFunctionObject("IDL-OUTPUT-STRUCT", "(DEFUN IDL-OUTPUT-STRUCT ((CLASSDEF CONS)))", ((cpp_function_code)(&idlOutputStruct)), NULL);
      defineFunctionObject("IDL-OUTPUT-ONE-FORMAL-PARAMETER", "(DEFUN IDL-OUTPUT-ONE-FORMAL-PARAMETER ((PARAMETER (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&idlOutputOneFormalParameter)), NULL);
      defineFunctionObject("IDL-OUTPUT-FORMAL-PARAMETERS", "(DEFUN IDL-OUTPUT-FORMAL-PARAMETERS ((PARAMETERS (CONS OF CONS))))", ((cpp_function_code)(&idlOutputFormalParameters)), NULL);
      defineFunctionObject("IDL-OUTPUT-FUNCTION-SIGNATURE", "(DEFUN IDL-OUTPUT-FUNCTION-SIGNATURE ((FUNCTION CONS)))", ((cpp_function_code)(&idlOutputFunctionSignature)), NULL);
      defineFunctionObject("IDL-OUTPUT-DECLARATIONS", "(DEFUN IDL-OUTPUT-DECLARATIONS ((DECLARATIONS (CONS OF CONS))))", ((cpp_function_code)(&idlOutputDeclarations)), NULL);
      defineFunctionObject("IDL-OUTPUT-SIGNATURE", "(DEFUN IDL-OUTPUT-SIGNATURE ((SIGNATURE CONS) (OUTPUTMETHODCLASS? BOOLEAN)))", ((cpp_function_code)(&idlOutputSignature)), NULL);
      defineFunctionObject("IDL-OUTPUT-SIGNATURES", "(DEFUN IDL-OUTPUT-SIGNATURES ((SIGNATURES CONS)))", ((cpp_function_code)(&idlOutputSignatures)), NULL);
      defineFunctionObject("STARTUP-IDL-OUTPUT", "(DEFUN STARTUP-IDL-OUTPUT () :PUBLIC? TRUE)", ((cpp_function_code)(&startupIdlOutput)), NULL);
      { MethodSlot* function = lookupFunction(SYM_IDL_OUTPUT_STELLA_STARTUP_IDL_OUTPUT);

        setDynamicSlotValue(function->dynamicSlots, SYM_IDL_OUTPUT_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupIdlOutput"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFSPECIAL *IDL-INDENT-CHARS* INTEGER 0)", &oIDL_INDENT_CHARSo);
    }
  }
}

Surrogate* SGT_IDL_OUTPUT_STELLA_CONS = NULL;

Symbol* SYM_IDL_OUTPUT_STELLA_IDL_COMMENT = NULL;

Symbol* SYM_IDL_OUTPUT_STELLA_IDL_TYPEDEF = NULL;

Symbol* SYM_IDL_OUTPUT_STELLA_IDL_ENUM = NULL;

Symbol* SYM_IDL_OUTPUT_STELLA_IDL_INTERFACE = NULL;

Symbol* SYM_IDL_OUTPUT_STELLA_IDL_STRUCT = NULL;

Symbol* SYM_IDL_OUTPUT_STELLA_IDL_DECLARATIONS = NULL;

Symbol* SYM_IDL_OUTPUT_STELLA_IDL_IDENT = NULL;

Symbol* SYM_IDL_OUTPUT_STELLA_IDL_TYPE = NULL;

Symbol* SYM_IDL_OUTPUT_STELLA_IDL_SIGNATURES = NULL;

Symbol* SYM_IDL_OUTPUT_STELLA_IDL_VAR_ARGS = NULL;

Symbol* SYM_IDL_OUTPUT_STELLA_STARTUP_IDL_OUTPUT = NULL;

Symbol* SYM_IDL_OUTPUT_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
