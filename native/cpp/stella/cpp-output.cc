//  -*- Mode: C++ -*-

// cpp-output.cc

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

DEFINE_STELLA_SPECIAL(oCPP_INDENT_CHARSo, int , 0);

// `true' when outputting a defprint, used to 
//             conditionally dereference streams in print-native-stream 
//             statements.  Also used to take the address of streams
//             when passed to functions inside of a defprint
DEFINE_STELLA_SPECIAL(oOUTPUTTINGDEFPRINTpo, boolean , false);

Object* cppOutputToString(Cons* statement) {
  { Symbol* resultvar = localGensym("RESULT");

    return (listO(5, SYM_CPP_OUTPUT_STELLA_VRLET, cons(cons(resultvar, listO(3, SYM_CPP_OUTPUT_STELLA_STRING, SYM_CPP_OUTPUT_STELLA_NULL, NIL)), NIL), listO(4, SYM_CPP_OUTPUT_STELLA_SPECIAL, cons(listO(3, SYM_CPP_OUTPUT_STELLA_oCURRENT_STREAMo, listO(3, SYM_CPP_OUTPUT_STELLA_NEW, SYM_CPP_OUTPUT_STELLA_OUTPUT_STRING_STREAM, NIL), NIL), NIL), statement, cons(listO(3, SYM_CPP_OUTPUT_STELLA_SETQ, resultvar, cons(listO(3, SYM_CPP_OUTPUT_STELLA_THE_STRING, listO(4, SYM_CPP_OUTPUT_STELLA_CAST, SYM_CPP_OUTPUT_STELLA_oCURRENT_STREAMo, SYM_CPP_OUTPUT_STELLA_OUTPUT_STRING_STREAM, NIL), NIL), NIL)), NIL)), resultvar, NIL));
  }
}

void cppOutputParseTree(Cons* constree) {
  { 
    BIND_STELLA_SPECIAL(oCPP_INDENT_CHARSo, int, 0);
    cppOutputStatement(constree);
  }
}

Cons* cppFlattenStatements(Cons* statements) {
  if (((boolean)(statements)) &&
      (!(statements == NIL))) {
    { Surrogate* testValue000 = safePrimaryType(statements->value);

      if (testValue000 == SGT_CPP_OUTPUT_STELLA_CONS) {
        { Cons* flattenedsubtree = NIL;
          Cons* flattenedtree = NIL;

          while (!(statements == NIL)) {
            flattenedsubtree = cppFlattenStatements(((Cons*)(statements->value)));
            if (consP(flattenedsubtree->value)) {
              flattenedtree = flattenedsubtree->reverse()->concatenate(flattenedtree, 0);
            }
            else {
              flattenedtree = cons(flattenedsubtree, flattenedtree);
            }
            statements = statements->rest;
          }
          return (flattenedtree->reverse());
        }
      }
      else if (subtypeOfSymbolP(testValue000)) {
        { GeneralizedSymbol* testValue001 = ((GeneralizedSymbol*)(statements->value));

          if ((testValue001 == SYM_CPP_OUTPUT_STELLA_CPP_PROGN) ||
              (testValue001 == SYM_CPP_OUTPUT_STELLA_CPP_STATEMENTS)) {
            if (statements->rest == NIL) {
              return (NIL);
            }
            else {
              return (cppFlattenStatements(statements->rest));
            }
          }
          else {
            return (statements);
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
  else {
    return (statements);
  }
}

Cons* cppPrognifyStatement(Object* statement) {
  if (cppPrognP(statement)) {
    return (((Cons*)(statement)));
  }
  else {
    return (listO(3, SYM_CPP_OUTPUT_STELLA_CPP_PROGN, listO(3, SYM_CPP_OUTPUT_STELLA_CPP_STATEMENTS, statement, NIL), NIL));
  }
}

Cons* cppStatementToList(Object* statement) {
  { Cons* flattenedstatement = cppFlattenStatements(((Cons*)(statement)));

    if (flattenedstatement == statement) {
      return (cons(flattenedstatement, NIL));
    }
    else {
      return (flattenedstatement);
    }
  }
}

void cppOutputStatement(Object* statement) {
  if (safePrimaryType(statement) == SGT_CPP_OUTPUT_STELLA_CONS) {
    { Object* statement000 = statement;
      Cons* statement = ((Cons*)(statement000));

      if (statement == NIL) {
        return;
      }
      if (consP(statement->value) ||
          (!((boolean)(statement->value)))) {
        {
          cppOutputStatement(statement->value);
          cppOutputStatement(statement->rest);
        }
      }
      else {
        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(statement->value));

          if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_COMMENT) {
            cppOutputComment(((StringWrapper*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_CLASS) {
            cppOutputClass(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_HANDLER_CASE) {
            cppOutputHandlerCase(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_CATCH) {
            cppOutputCatch(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_SIGNAL) {
            cppOutputSignal(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_UNWIND_PROTECT) {
            cppOutputUnwindProtect(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_VERBATIM) {
            cppOutputVerbatim(((StringWrapper*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_CAST) {
            cppOutputCast(statement->rest);
          }
          else if ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_GLOBAL) ||
              ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_SPECIAL) ||
               (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_LOCAL))) {
            cppOutputVariableDefinition(statement);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_TYPE) {
            cppOutputTypeExpression(((Cons*)(statement->rest)));
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_DEREFERENCE) {
            cppOutputDereference(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_ARRAY_REFERENCE) {
            cppOutputArrayReference(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_PROGN) {
            cppOutputProgn(((Cons*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_WITH_PROCESS_LOCK) {
            cppOutputWithProcessLock(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_BREAK) {
            cppOutputBreak();
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_CONTINUE) {
            cppOutputContinue();
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_GOTO) {
            cppOutputGoto(statement->rest->value);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_GOTO_LABEL) {
            cppOutputGotoLabel(statement->rest->value);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_IF) {
            cppOutputIf(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_SIGNATURE) {
            cppOutputFuncallFunctionSignature(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_METHOD_SIGNATURE) {
            cppOutputMethodCodeCallSignature(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_COND) {
            cppOutputCond(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_CASE) {
            cppOutputCase(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_WHEN) {
            cppOutputWhen(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_UNLESS) {
            cppOutputUnless(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_ASSIGN) {
            cppOutputAssignment(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_LOOP) {
            cppOutputLoop(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_WHILE) {
            cppOutputWhile(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_FOREACH) {
            cppOutputForeach(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_BLOCK) {
            cppOutputBlock(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_IDENT) {
            cppOutputIdentifier(((StringWrapper*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_PRINT_STREAM) {
            cppOutputPrintStream(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_PRINT_NATIVE_STREAM) {
            cppOutputPrintNativeStream(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_LITERAL) {
            statement->rest->value->cppOutputLiteral();
          }
          else if ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION) ||
              (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_METHOD)) {
            cppOutputFunction(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_RETURN) {
            cppOutputReturn(((Cons*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_SYMBOL) {
            statement->rest->value->cppOutputLiteral();
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_MAKE) {
            cppOutputMake(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_FUNCALL) {
            cppOutputFuncall(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_METHOD_CODE_CALL) {
            cppOutputMethodCodeCall(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_POINTER) {
            cppOutputFunctionPointer(((StringWrapper*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_METHOD_POINTER) {
            cppOutputMethodPointer(((StringWrapper*)(statement->rest->value)));
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_SLOT_VALUE) {
            cppOutputSlotValue(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_REFERENCED_SLOT_VALUE) {
            cppOutputReferencedSlotValue(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_SLOT_VALUE_SETTER) {
            cppOutputSlotValueSetter(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_DECLARATIONS) {
            cppOutputDeclarations(((Keyword*)(statement->rest->value)), ((Cons*)(statement->rest->rest->value)));
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_DEFINITIONS) {
            cppOutputDefinitions(((Keyword*)(statement->rest->value)), ((Cons*)(statement->rest->rest->value)));
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_SIGNATURES) {
            cppOutputSignatures(((Keyword*)(statement->rest->value)), ((Cons*)(statement->rest->rest->value)));
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_STATEMENTS) {
            cppOutputStatements(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_UNARY_OP) {
            cppOutputUnaryOperator(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_BINARY_OP) {
            cppOutputBinaryOperator(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_TERNARY_OP) {
            cppOutputTernaryOperator(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_CALL) {
            cppOutputFunctionCall(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_METHOD_SETTER_CALL) {
            cppOutputMethodSetterCall(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_METHOD_CALL) {
            cppOutputMethodCall(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_REFERENCED_METHOD_CALL) {
            cppOutputReferencedMethodCall(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_ACTUALS) {
            cppOutputActualParameters(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_DEFPRINT) {
            cppOutputDefprint(statement->rest);
          }
          else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_EXTERN_C) {
            cppOutputExternC(statement->rest);
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
    cppOutputAtomicExpression(statement);
  }
}

void cppOutputVerbatim(StringWrapper* verbatimstatement) {
  *(oCURRENT_STREAMo->nativeStream) << verbatimstatement->wrapperValue;
}

void cppOutputComment(StringWrapper* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "// ";
  { boolean returnp = false;

    { char chaR = NULL_CHARACTER;
      const char* vector000 = tree->wrapperValue;
      int index000 = 0;
      int length000 = strlen(vector000);

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        chaR = vector000[index000];
        switch (chaR) {
          case '\n': 
            if (!(returnp)) {
              *(oCURRENT_STREAMo->nativeStream) << std::endl;
              cppIndent();
              *(oCURRENT_STREAMo->nativeStream) << "// ";
            }
            returnp = false;
            break;
          case '\r': 
            *(oCURRENT_STREAMo->nativeStream) << std::endl;
            cppIndent();
            *(oCURRENT_STREAMo->nativeStream) << "// ";
            returnp = true;
            break;
          default:
            *(oCURRENT_STREAMo->nativeStream) << chaR;
            returnp = false;
            break;
        }
      }
    }
    *(oCURRENT_STREAMo->nativeStream) << std::endl;
  }
}

void cppOutputDereference(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "*";
  cppOutputStatement(tree);
}

void cppOutputArrayReference(Cons* tree) {
  cppMaybeOutputStatementWithParentheses(tree->value);
  { Object* indexexpression = NULL;
    Cons* iter000 = tree->rest;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      indexexpression = iter000->value;
      *(oCURRENT_STREAMo->nativeStream) << "[";
      cppOutputStatement(indexexpression);
      *(oCURRENT_STREAMo->nativeStream) << "]";
    }
  }
}

void cppOutputCast(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "(";
  if (subtypeOfStringP(safePrimaryType(tree->rest->value))) {
    *(oCURRENT_STREAMo->nativeStream) << "(" << unwrapString(((StringWrapper*)(tree->rest->value))) << ")";
  }
  else {
    cppOutputStatement(tree->rest->value);
  }
  *(oCURRENT_STREAMo->nativeStream) << "(";
  cppOutputStatement(tree->value);
  *(oCURRENT_STREAMo->nativeStream) << "))";
}

void cppOutputSignal(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "throw ";
  cppOutputStatement(tree->value);
}

void cppOutputHandlerCase(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "try {" << std::endl;
  cppBumpIndent();
  cppOutputStatements(cppStatementToList(tree->value));
  cppUnbumpIndent();
  cppIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
  cppOutputStatements(tree->rest);
}

void cppOutputCatch(Cons* tree) {
  { Cons* variabledecl = ((Cons*)(tree->value));

    *(oCURRENT_STREAMo->nativeStream) << "catch (";
    cppOutputStatement(variabledecl->value);
    if (((boolean)(variabledecl->rest->value))) {
      cppOutputStatement(variabledecl->rest->value);
    }
    *(oCURRENT_STREAMo->nativeStream) << ") {" << std::endl;
    cppBumpIndent();
    cppOutputStatements(cppFlattenStatements(tree->rest));
    cppUnbumpIndent();
    cppIndent();
    *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
  }
}

void cppOutputUnwindProtect(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "try {" << std::endl;
  cppBumpIndent();
  cppOutputStatements(cppStatementToList(tree->value));
  cppUnbumpIndent();
  cppIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
  *(oCURRENT_STREAMo->nativeStream) << "catch (...) {" << std::endl;
  cppBumpIndent();
  cppOutputStatements(((Cons*)(copyConsTree(tree->rest))));
  cppIndent();
  *(oCURRENT_STREAMo->nativeStream) << "throw;" << std::endl;
  cppUnbumpIndent();
  cppIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
  cppOutputStatements(tree->rest);
}

void cppOutputGlobalDeclaration(Cons* global) {
  { Object* kind = global->value;
    Object* type = global->rest->rest->value;
    Object* name = global->fourth();

    *(oCURRENT_STREAMo->nativeStream) << "extern ";
    if (((GeneralizedSymbol*)(kind)) == SYM_CPP_OUTPUT_STELLA_CPP_SPECIAL) {
      if (specialImplementationStyle() == KWD_CPP_OUTPUT_UNBIND_WITH_DESTRUCTORS) {
        cppOutputStatement(listO(4, SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_OUTPUT_STELLA_CPP_IDENT, wrapString("DECLARE_STELLA_SPECIAL"), NIL), listO(4, SYM_CPP_OUTPUT_STELLA_CPP_ACTUALS, listO(3, SYM_CPP_OUTPUT_STELLA_CPP_IDENT, name, NIL), type, NIL), NIL));
      }
      else {
        cppOutputTypedEntity(type, name, NULL);
      }
    }
    else {
      cppOutputTypedEntity(type, name, NULL);
    }
    *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
  }
}

void cppOutputVariableDefinition(Cons* variable) {
  { Object* kind = variable->value;
    const char* documentation = unwrapString(((StringWrapper*)(variable->rest->value)));
    Object* type = variable->rest->rest->value;
    Object* name = variable->fourth();
    Object* initialvalue = variable->fifth();

    if (documentation != NULL) {
      cppOutputComment(wrapString(documentation));
    }
    if (((GeneralizedSymbol*)(kind)) == SYM_CPP_OUTPUT_STELLA_CPP_SPECIAL) {
      if (specialImplementationStyle() == KWD_CPP_OUTPUT_UNBIND_WITH_DESTRUCTORS) {
        if (supportUnexecP()) {
          cppOutputStatement(listO(4, SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_OUTPUT_STELLA_CPP_IDENT, wrapString("DECLARE_STELLA_SPECIAL"), NIL), listO(4, SYM_CPP_OUTPUT_STELLA_CPP_ACTUALS, listO(3, SYM_CPP_OUTPUT_STELLA_CPP_IDENT, name, NIL), type, NIL), NIL));
        }
        else {
          cppOutputStatement(listO(4, SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_CALL, listO(3, SYM_CPP_OUTPUT_STELLA_CPP_IDENT, wrapString("DEFINE_STELLA_SPECIAL"), NIL), listO(4, SYM_CPP_OUTPUT_STELLA_CPP_ACTUALS, listO(3, SYM_CPP_OUTPUT_STELLA_CPP_IDENT, name, NIL), type, cons(initialvalue, NIL)), NIL));
        }
      }
      else {
        cppOutputTypedEntity(type, name, initialvalue);
      }
    }
    else {
      cppOutputTypedEntity(type, name, initialvalue);
    }
    *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl << std::endl;
  }
}

void cppOutputFuncallFunctionSignature(Cons* signature) {
  { Cons* returntypes = ((Cons*)(signature->value));
    StringWrapper* returntype = ((StringWrapper*)(returntypes->value));
    Cons* parametertypes = ((Cons*)(signature->rest->value));
    int nofparameters = parametertypes->length();

    { const char* result000 = NULL;

      { 
        BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, newOutputStringStream());
        {
          *(oCURRENT_STREAMo->nativeStream) << " (*) (";
          { StringWrapper* partype = NULL;
            Cons* iter000 = parametertypes;
            int i = NULL_INTEGER;
            int iter001 = 1;
            int upperBound000 = nofparameters;
            boolean unboundedP000 = upperBound000 == NULL_INTEGER;

            for  (; (!(iter000 == NIL)) &&
                      (unboundedP000 ||
                       (iter001 <= upperBound000)); 
                  iter000 = iter000->rest,
                  iter001 = iter001 + 1) {
              partype = ((StringWrapper*)(iter000->value));
              i = iter001;
              *(oCURRENT_STREAMo->nativeStream) << partype->wrapperValue;
              if (i < nofparameters) {
                *(oCURRENT_STREAMo->nativeStream) << ", ";
              }
            }
          }
          *(oCURRENT_STREAMo->nativeStream) << ")";
        }
        result000 = ((OutputStringStream*)(oCURRENT_STREAMo))->theStringReader();
      }
      { const char* baresignature = result000;

        *(oCURRENT_STREAMo->nativeStream) << "(";
        cppOutputTypedEntity(returntype, wrapString(baresignature), NULL);
        *(oCURRENT_STREAMo->nativeStream) << ")";
      }
    }
  }
}

void cppOutputMethodCodeCallSignature(Cons* signature) {
  { Cons* returntypes = ((Cons*)(signature->value));
    StringWrapper* returntype = ((StringWrapper*)(returntypes->value));
    const char* objecttype = ((StringWrapper*)(signature->rest->value))->wrapperValue;
    Cons* parametertypes = ((Cons*)(signature->rest->rest->value));
    int nofparameters = parametertypes->length();

    { const char* result000 = NULL;

      { 
        BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, newOutputStringStream());
        {
          *(oCURRENT_STREAMo->nativeStream) << " (";
          *(oCURRENT_STREAMo->nativeStream) << objecttype;
          *(oCURRENT_STREAMo->nativeStream) << "::*) (";
          { StringWrapper* partype = NULL;
            Cons* iter000 = parametertypes;
            int i = NULL_INTEGER;
            int iter001 = 1;
            int upperBound000 = nofparameters;
            boolean unboundedP000 = upperBound000 == NULL_INTEGER;

            for  (; (!(iter000 == NIL)) &&
                      (unboundedP000 ||
                       (iter001 <= upperBound000)); 
                  iter000 = iter000->rest,
                  iter001 = iter001 + 1) {
              partype = ((StringWrapper*)(iter000->value));
              i = iter001;
              *(oCURRENT_STREAMo->nativeStream) << partype->wrapperValue;
              if (i < nofparameters) {
                *(oCURRENT_STREAMo->nativeStream) << ", ";
              }
            }
          }
          *(oCURRENT_STREAMo->nativeStream) << ")";
        }
        result000 = ((OutputStringStream*)(oCURRENT_STREAMo))->theStringReader();
      }
      { const char* baresignature = result000;

        *(oCURRENT_STREAMo->nativeStream) << "(";
        cppOutputTypedEntity(returntype, wrapString(baresignature), NULL);
        *(oCURRENT_STREAMo->nativeStream) << ")";
      }
    }
  }
}

void cppOutputFuncall(Cons* funcall) {
  *(oCURRENT_STREAMo->nativeStream) << "(";
  cppOutputStatement(funcall->value);
  cppOutputStatement(funcall->rest->value);
  *(oCURRENT_STREAMo->nativeStream) << ")";
  cppOutputStatement(funcall->rest->rest->value);
}

void cppOutputMethodCodeCall(Cons* methodcall) {
  *(oCURRENT_STREAMo->nativeStream) << "(";
  cppMaybeOutputStatementWithParentheses(methodcall->rest->rest->value);
  *(oCURRENT_STREAMo->nativeStream) << "->*(";
  cppOutputStatement(methodcall->value);
  *(oCURRENT_STREAMo->nativeStream) << " ";
  cppOutputStatement(methodcall->rest->value);
  *(oCURRENT_STREAMo->nativeStream) << ")) ";
  cppOutputStatement(methodcall->fourth());
}

void cppOutputBreak() {
  *(oCURRENT_STREAMo->nativeStream) << "break;" << std::endl;
}

void cppOutputContinue() {
  *(oCURRENT_STREAMo->nativeStream) << "continue;" << std::endl;
}

void cppOutputGoto(Object* label) {
  *(oCURRENT_STREAMo->nativeStream) << "goto ";
  cppOutputStatement(label);
  *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
}

void cppOutputGotoLabel(Object* label) {
  cppOutputStatement(label);
  *(oCURRENT_STREAMo->nativeStream) << ":;" << std::endl;
}

boolean cppLastStatementIsReturnP(Cons* statements) {
  { Object* lastitem = statements->last();

    return (consP(lastitem) &&
        (((Cons*)(lastitem))->value == SYM_CPP_OUTPUT_STELLA_CPP_RETURN));
  }
}

void cppOutputCase(Cons* casE) {
  { Object* keyform = casE->value;
    Object* defaultcase = casE->rest->value;
    Object* conditions = casE->rest->rest->value;

    *(oCURRENT_STREAMo->nativeStream) << "switch (";
    cppOutputStatement(keyform);
    *(oCURRENT_STREAMo->nativeStream) << ") {" << std::endl;
    cppBumpIndent();
    { Cons* c = NULL;
      Cons* iter000 = ((Cons*)(conditions));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        c = ((Cons*)(iter000->value));
        { Cons* condition = c;

          { Object* cond = NULL;
            Cons* iter001 = ((Cons*)((consP(((Cons*)(condition->value))->value) ? condition->value : cons(condition->value, NIL))));

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              cond = iter001->value;
              cppIndent();
              *(oCURRENT_STREAMo->nativeStream) << "case ";
              cppOutputStatement(cond);
              *(oCURRENT_STREAMo->nativeStream) << ": " << std::endl;
            }
          }
          cppBumpIndent();
          cppOutputStatement(condition->rest->value);
          if (!(cppLastStatementIsReturnP(((Cons*)(condition->rest->value))))) {
            cppIndent();
            *(oCURRENT_STREAMo->nativeStream) << "break;" << std::endl;
          }
          cppUnbumpIndent();
        }
      }
    }
    if (!((boolean)(defaultcase))) {
      std::cerr << "Safety violation: " << "INTERNAL ERROR: `cpp-output-case' expects an `otherwise' clause.";
    }
    cppIndent();
    *(oCURRENT_STREAMo->nativeStream) << "default:" << std::endl;
    cppBumpIndent();
    cppOutputStatement(defaultcase);
    if (!(cppLastStatementIsReturnP(((Cons*)(defaultcase))))) {
      cppIndent();
      *(oCURRENT_STREAMo->nativeStream) << "break;" << std::endl;
    }
    cppUnbumpIndent();
    cppUnbumpIndent();
    cppIndent();
    *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
  }
}

void cppOutputCond(Cons* cond) {
  { Cons* defaultcondition = ((Cons*)(cond->value));
    Cons* conditions = ((Cons*)(cond->rest->value));
    Cons* firstcondition = ((Cons*)(conditions->value));
    Cons* restconditions = conditions->rest;

    if (((boolean)(defaultcondition)) &&
        (conditions == NIL)) {
      *(oCURRENT_STREAMo->nativeStream) << "if (TRUE) ";
      cppOutputStatement(defaultcondition);
      return;
    }
    *(oCURRENT_STREAMo->nativeStream) << "if (";
    cppOutputStatement(firstcondition->value);
    *(oCURRENT_STREAMo->nativeStream) << ") ";
    cppOutputStatement(firstcondition->rest->value);
    { Object* c = NULL;
      Cons* iter000 = restconditions;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        c = iter000->value;
        { Cons* condition = ((Cons*)(c));

          cppIndent();
          *(oCURRENT_STREAMo->nativeStream) << "else if (";
          cppOutputStatement(condition->value);
          *(oCURRENT_STREAMo->nativeStream) << ") ";
          cppOutputStatement(condition->rest->value);
        }
      }
    }
    if (((boolean)(defaultcondition))) {
      cppIndent();
      *(oCURRENT_STREAMo->nativeStream) << "else ";
      cppOutputStatement(defaultcondition);
    }
  }
}

boolean cppPrognP(Object* tree) {
  return (consP(tree) &&
      (((Cons*)(tree))->value == SYM_CPP_OUTPUT_STELLA_CPP_PROGN));
}

boolean cppBlockP(Object* tree) {
  if (safePrimaryType(tree) == SGT_CPP_OUTPUT_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

        if ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_BLOCK) ||
            (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_PROGN)) {
          return (true);
        }
        else {
        }
      }
    }
  }
  else {
  }
  return (false);
}

void cppOutputIf(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "if (";
  cppOutputStatement(tree->value);
  *(oCURRENT_STREAMo->nativeStream) << ") ";
  if (cppBlockP(tree->rest->value)) {
    cppOutputStatement(tree->rest->value);
  }
  else {
    {
      *(oCURRENT_STREAMo->nativeStream) << std::endl;
      cppBumpIndent();
      cppIndent();
      cppOutputStatement(tree->rest->value);
      *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
      cppUnbumpIndent();
    }
  }
  if (!(!((boolean)(tree->rest->rest->value)))) {
    cppIndent();
    *(oCURRENT_STREAMo->nativeStream) << "else ";
    if (cppBlockP(tree->rest->rest->value)) {
      cppOutputStatement(tree->rest->rest->value);
    }
    else {
      {
        *(oCURRENT_STREAMo->nativeStream) << std::endl;
        cppBumpIndent();
        cppIndent();
        cppOutputStatement(tree->rest->rest->value);
        *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
        cppUnbumpIndent();
      }
    }
  }
}

void cppOutputWhen(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "if (";
  cppOutputStatement(tree->value);
  *(oCURRENT_STREAMo->nativeStream) << ") {" << std::endl;
  cppBumpIndent();
  cppOutputStatement(tree->rest->value);
  cppUnbumpIndent();
  cppIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
}

void cppOutputUnless(Cons* tree) {
  *(oCURRENT_STREAMo->nativeStream) << "if (!(";
  cppOutputStatement(tree->value);
  *(oCURRENT_STREAMo->nativeStream) << ")) {" << std::endl;
  cppBumpIndent();
  cppOutputStatement(tree->rest->value);
  cppUnbumpIndent();
  cppIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
}

void cppOutputAssignment(Cons* assignment) {
  cppOutputStatement(assignment->value);
  *(oCURRENT_STREAMo->nativeStream) << " = ";
  cppOutputStatement(assignment->rest->value);
}

void cppOutputLoop(Cons* loop) {
  *(oCURRENT_STREAMo->nativeStream) << "for (;;) ";
  cppOutputStatement(loop->value);
}

void cppOutputWhile(Cons* loop) {
  *(oCURRENT_STREAMo->nativeStream) << "while (";
  cppOutputStatement(loop->value);
  *(oCURRENT_STREAMo->nativeStream) << ") ";
  cppOutputStatement(loop->rest->value);
}

void cppOutputForeach(Cons* loop) {
  { Cons* variables = ((Cons*)(loop->value));
    int nofvariables = variables->length();
    Object* continuationtest = loop->rest->value;
    Cons* valueassignments = ((Cons*)(loop->rest->rest->value));
    Cons* nextassignments = ((Cons*)(loop->fourth()));
    int nofnextassignments = nextassignments->length();
    Cons* body = ((Cons*)(loop->fifth()));
    boolean eolseparateexpressionsP = (nofvariables > 2) ||
        (oCPP_INDENT_CHARSo > 35);

    cppIndent();
    if (eolseparateexpressionsP) {
      *(oCURRENT_STREAMo->nativeStream) << "for  (";
    }
    else {
      *(oCURRENT_STREAMo->nativeStream) << "for (";
    }
    cppBumpIndent();
    cppBumpIndent();
    cppBumpIndent();
    *(oCURRENT_STREAMo->nativeStream) << "; ";
    cppOutputStatement(continuationtest);
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
            cppIndent();
          }
          cppOutputStatement(next);
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
    cppUnbumpIndent();
    cppUnbumpIndent();
    cppOutputStatements(cppFlattenStatements(valueassignments->concatenate(body, 0)));
    cppUnbumpIndent();
    cppIndent();
    *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
  }
}

void cppOutputFunctionPointer(StringWrapper* functionname) {
  *(oCURRENT_STREAMo->nativeStream) << "&" << functionname->wrapperValue;
}

void cppOutputMethodPointer(StringWrapper* methodname) {
  *(oCURRENT_STREAMo->nativeStream) << "&" << methodname->wrapperValue;
}

void cppOutputSlotValue(Cons* statement) {
  cppMaybeOutputStatementWithParentheses(statement->value);
  *(oCURRENT_STREAMo->nativeStream) << "->" << ((StringWrapper*)(statement->rest->value))->wrapperValue;
}

void cppOutputReferencedSlotValue(Cons* statement) {
  cppMaybeOutputStatementWithParentheses(statement->value);
  *(oCURRENT_STREAMo->nativeStream) << "." << ((StringWrapper*)(statement->rest->value))->wrapperValue;
}

void cppOutputSlotValueSetter(Cons* statement) {
  cppMaybeOutputStatementWithParentheses(statement->value);
  *(oCURRENT_STREAMo->nativeStream) << "->" << ((StringWrapper*)(statement->rest->value))->wrapperValue << " = ";
  cppOutputStatement(statement->rest->rest->value);
}

void cppOutputMake(Cons* statement) {
  *(oCURRENT_STREAMo->nativeStream) << "new ";
  cppOutputStatement(statement->value);
  if (((boolean)(statement->rest->value))) {
    cppOutputStatement(statement->rest->value);
  }
}

void cppBumpIndent() {
  oCPP_INDENT_CHARSo = oCPP_INDENT_CHARSo + 2;
}

void cppUnbumpIndent() {
  oCPP_INDENT_CHARSo = oCPP_INDENT_CHARSo - 2;
}

void Object::cppOutputLiteral() {
  { Object* object = this;

  }
}

void CharacterWrapper::cppOutputLiteral() {
  { CharacterWrapper* character = this;

    { char ch = character->wrapperValue;

      switch (ch) {
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
        case '\0': 
          *(oCURRENT_STREAMo->nativeStream) << "'\\0'";
          break;
        default:
          if (ch == NULL_CHARACTER) {
            *(oCURRENT_STREAMo->nativeStream) << "'\\0'";
          }
          else {
            *(oCURRENT_STREAMo->nativeStream) << "'" << ch << "'";
          }
          break;
      }
    }
  }
}

void IntegerWrapper::cppOutputLiteral() {
  { IntegerWrapper* inT = this;

    *(oCURRENT_STREAMo->nativeStream) << inT->wrapperValue;
  }
}

void LongIntegerWrapper::cppOutputLiteral() {
  { LongIntegerWrapper* inT = this;

    *(oCURRENT_STREAMo->nativeStream) << inT->wrapperValue << "l";
  }
}

void FloatWrapper::cppOutputLiteral() {
  { FloatWrapper* floaT = this;

    { const char* value = floatToString(floaT->wrapperValue);
      boolean integervalueP = true;

      { char ch = NULL_CHARACTER;
        const char* vector000 = value;
        int index000 = 0;
        int length000 = strlen(vector000);

        for  (; index000 < length000; 
              index000 = index000 + 1) {
          ch = vector000[index000];
          if (stringMemberP(".eE", ch)) {
            integervalueP = false;
            break;
          }
        }
      }
      if (integervalueP) {
        value = stringConcatenate(value, ".0", 0);
      }
      *(oCURRENT_STREAMo->nativeStream) << value;
    }
  }
}

void BooleanWrapper::cppOutputLiteral() {
  { BooleanWrapper* boolean = this;

    if (boolean->wrapperValue) {
      *(oCURRENT_STREAMo->nativeStream) << "TRUE";
    }
    else {
      *(oCURRENT_STREAMo->nativeStream) << "FALSE";
    }
  }
}

void Cons::cppOutputLiteral() {
  { Cons* cons = this;

    if (cons == NIL) {
      *(oCURRENT_STREAMo->nativeStream) << "NIL";
    }
    else {
      {
        *(oCURRENT_STREAMo->nativeStream) << "(" << cons->value << " . ";
        cons->rest->cppOutputLiteral();
      }
    }
  }
}

const char* replaceCharacterWithSubstring(const char* string, const char* neW, char character) {
  return (replaceSubstrings(string, neW, makeString(1, character)));
}

// C++ string literals longer than this are broken
// into multiple pieces to avoid problems with certain MS compilers.
int oCPP_MAX_STRING_LITERAL_LENGTHo = 1024;

void stringCppOutputLiteral(const char* string) {
  { int free = oCPP_MAX_STRING_LITERAL_LENGTHo;

    *(oCURRENT_STREAMo->nativeStream) << "\"";
    { char ch = NULL_CHARACTER;
      const char* vector000 = string;
      int index000 = 0;
      int length000 = strlen(vector000);

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        ch = vector000[index000];
        if (free <= 1) {
          *(oCURRENT_STREAMo->nativeStream) << "\" \"";
          free = oCPP_MAX_STRING_LITERAL_LENGTHo;
        }
        switch (ch) {
          case '\\': 
          case '"': 
            *(oCURRENT_STREAMo->nativeStream) << "\\";
            free = free - 1;
            break;
          case '\n': 
            *(oCURRENT_STREAMo->nativeStream) << "\\";
            free = free - 1;
            ch = 'n';
            break;
          case '\r': 
            *(oCURRENT_STREAMo->nativeStream) << "\\";
            free = free - 1;
            ch = 'r';
            break;
          default:
            break;
        }
        *(oCURRENT_STREAMo->nativeStream) << ch;
        free = free - 1;
      }
    }
    *(oCURRENT_STREAMo->nativeStream) << "\"";
  }
}

void StringWrapper::cppOutputLiteral() {
  { StringWrapper* string = this;

    stringCppOutputLiteral(string->wrapperValue);
  }
}

void MutableStringWrapper::cppOutputLiteral() {
  { MutableStringWrapper* string = this;

    stringCppOutputLiteral((string->wrapperValue));
  }
}

void QuotedExpression::cppOutputLiteral() {
  { QuotedExpression* tree = this;

    *(oCURRENT_STREAMo->nativeStream) << "\"" << tree << "\"";
  }
}

void Symbol::cppOutputLiteral() {
  { Symbol* symbol = this;

    *(oCURRENT_STREAMo->nativeStream) << cppTranslateSymbolName(symbol)->wrapperValue;
  }
}

void Surrogate::cppOutputLiteral() {
  { Surrogate* surrogate = this;

    *(oCURRENT_STREAMo->nativeStream) << cppTranslateSurrogateName(surrogate)->wrapperValue;
  }
}

void Keyword::cppOutputLiteral() {
  { Keyword* keyword = this;

    *(oCURRENT_STREAMo->nativeStream) << cppTranslateKeywordName(keyword)->wrapperValue;
  }
}

void cppOutputIdentifier(StringWrapper* identifier) {
  *(oCURRENT_STREAMo->nativeStream) << identifier->wrapperValue;
}

void cppOutputAtomicExpression(Object* atom) {
  { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(atom));

    if (testValue000 == SYM_CPP_OUTPUT_STELLA_NEWLINE) {
      *(oCURRENT_STREAMo->nativeStream) << std::endl;
    }
    else if (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_NULL_VALUE) {
      *(oCURRENT_STREAMo->nativeStream) << "NULL_VALUE";
    }
    else if (testValue000 == SYM_CPP_OUTPUT_STELLA_ASSIGN) {
      *(oCURRENT_STREAMo->nativeStream) << "=";
    }
    else if (testValue000 == SYM_CPP_OUTPUT_STELLA_SCOLON) {
      *(oCURRENT_STREAMo->nativeStream) << ";";
    }
    else if (testValue000 == SYM_CPP_OUTPUT_STELLA_LPAREN) {
      *(oCURRENT_STREAMo->nativeStream) << "(";
    }
    else if (testValue000 == SYM_CPP_OUTPUT_STELLA_RPAREN) {
      *(oCURRENT_STREAMo->nativeStream) << ")";
    }
    else {
      atom->cppOutputLiteral();
    }
  }
}

void cppIndent() {
  { int i = NULL_INTEGER;
    int iter000 = 1;
    int upperBound000 = oCPP_INDENT_CHARSo;
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

boolean cppOutputSemicolonP(Cons* statement) {
  if (((boolean)(statement))) {
    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(statement->value));

      if ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_ASSIGN) ||
          ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_UNARY_OP) ||
           ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_BINARY_OP) ||
            ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_TERNARY_OP) ||
             ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_CAST) ||
              ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_FUNCALL) ||
               ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_CALL) ||
                ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_POINTER) ||
                 ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_MAKE) ||
                  ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_METHOD_CALL) ||
                   ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_METHOD_CODE_CALL) ||
                    ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_METHOD_POINTER) ||
                     ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_METHOD_SETTER_CALL) ||
                      ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_NEW) ||
                       ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_PRINT_NATIVE_STREAM) ||
                        ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_PRINT_STREAM) ||
                         ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_REFERENCED_METHOD_CALL) ||
                          ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_RETURN) ||
                           ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_SIGNAL) ||
                            ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_SLOT_VALUE_SETTER) ||
                             ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_THROW) ||
                              (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_VERBATIM)))))))))))))))))))))) {
        return (true);
      }
      else {
      }
    }
  }
  return (false);
}

boolean cppIndentStatementP(Cons* statement) {
  if (((boolean)(statement))) {
    return (!getQuotedTree("((CPP_STATEMENTS) \"/STELLA\")", "/STELLA")->memberP(statement->value));
  }
  else {
    return (false);
  }
}

boolean illegalCppStatementP(Cons* statement) {
  if (((boolean)(statement))) {
    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(statement->value));

      if ((testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_LITERAL) ||
          (testValue000 == SYM_CPP_OUTPUT_STELLA_CPP_IDENT)) {
        return (true);
      }
      else {
      }
    }
  }
  return (false);
}

void cppOutputStatements(Cons* statementlist) {
  { Object* statement = NULL;
    Cons* iter000 = statementlist;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      statement = iter000->value;
      if (!(illegalCppStatementP(((Cons*)(statement))))) {
        if (cppIndentStatementP(((Cons*)(statement)))) {
          cppIndent();
        }
        cppOutputStatement(statement);
        if (cppOutputSemicolonP(((Cons*)(statement)))) {
          *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
        }
      }
    }
  }
}

void cppMaybeOutputStatementWithParentheses(Object* statement) {
  { boolean operatorP = cppOperatorP(statement);

    if (operatorP) {
      *(oCURRENT_STREAMo->nativeStream) << "(";
    }
    cppOutputStatement(statement);
    if (operatorP) {
      *(oCURRENT_STREAMo->nativeStream) << ")";
    }
  }
}

void cppOutputStreamPrintItems(Cons* items) {
  { Object* e = NULL;
    Cons* iter000 = items;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      e = iter000->value;
      *(oCURRENT_STREAMo->nativeStream) << " << ";
      cppMaybeOutputStatementWithParentheses(e);
    }
  }
}

void cppOutputPrintStream(Cons* exps) {
  { Object* stream = exps->value;

    if (stream == SYM_CPP_OUTPUT_STELLA_CPP_STANDARD_OUT) {
      *(oCURRENT_STREAMo->nativeStream) << "std::cout";
    }
    else if (stream == SYM_CPP_OUTPUT_STELLA_CPP_STANDARD_ERROR) {
      *(oCURRENT_STREAMo->nativeStream) << "std::cerr";
    }
    else {
      *(oCURRENT_STREAMo->nativeStream) << "get_ostream(";
      cppOutputStatement(stream);
      *(oCURRENT_STREAMo->nativeStream) << ")";
    }
    cppOutputStreamPrintItems(exps->rest);
  }
}

void cppOutputPrintNativeStream(Cons* exps) {
  { Object* stream = exps->value;

    if (stream == SYM_CPP_OUTPUT_STELLA_CPP_STANDARD_OUT) {
      *(oCURRENT_STREAMo->nativeStream) << "std::cout";
    }
    else if (stream == SYM_CPP_OUTPUT_STELLA_CPP_STANDARD_ERROR) {
      *(oCURRENT_STREAMo->nativeStream) << "std::cerr";
    }
    else {
      if (!(oOUTPUTTINGDEFPRINTpo)) {
        *(oCURRENT_STREAMo->nativeStream) << "*(";
      }
      cppOutputStatement(stream);
      if (!(oOUTPUTTINGDEFPRINTpo)) {
        *(oCURRENT_STREAMo->nativeStream) << ")";
      }
    }
    cppOutputStreamPrintItems(exps->rest);
  }
}

boolean cppIndentableBinaryOperatorP(StringWrapper* operatoR) {
  return (getQuotedTree("((\"||\" \"&&\") \"/STELLA\")", "/STELLA")->memberP(operatoR));
}

boolean cppCommutativeBinaryOperatorP(StringWrapper* operatoR) {
  return (getQuotedTree("((\"+\" \"*\") \"/STELLA\")", "/STELLA")->memberP(operatoR));
}

boolean cppBinaryOperatorP(Object* statement) {
  return (consP(statement) &&
      (SYM_CPP_OUTPUT_STELLA_CPP_BINARY_OP == ((Cons*)(statement))->value));
}

boolean cppOperatorP(Object* statement) {
  return (consP(statement) &&
      getQuotedTree("((CPP_UNARY_OP CPP_BINARY_OP CPP_TERNARY_OP CPP_ASSIGN CPP_SLOT_VALUE_SETTER) \"/STELLA\")", "/STELLA")->memberP(((Cons*)(statement))->value));
}

boolean cppAssignmentP(Cons* statement) {
  return (statement->value == SYM_CPP_OUTPUT_STELLA_CPP_ASSIGN);
}

void cppOutputUnaryOperator(Cons* expression) {
  { StringWrapper* op = NULL;
    Object* arg = NULL;
    boolean postfixP = false;

    if (subtypeOfStringP(safePrimaryType(expression->value))) {
      op = ((StringWrapper*)(expression->value));
      arg = expression->rest->value;
    }
    else {
      op = ((StringWrapper*)(expression->rest->value));
      arg = expression->value;
      postfixP = true;
    }
    if (!(postfixP)) {
      *(oCURRENT_STREAMo->nativeStream) << op->wrapperValue;
    }
    cppMaybeOutputStatementWithParentheses(arg);
    if (postfixP) {
      *(oCURRENT_STREAMo->nativeStream) << op->wrapperValue;
    }
  }
}

boolean cppNestedOperatorNeedsParenthesesP(StringWrapper* op, Object* nested) {
  return (cppOperatorP(nested) &&
      (!(cppCommutativeBinaryOperatorP(op) &&
      stringEqlP(op->wrapperValue, ((StringWrapper*)(((Cons*)(nested))->rest->rest->value))->wrapperValue))));
}

void cppHelpOutputBinaryOperator(Cons* expression, int nestlevel) {
  { Object* arg1 = expression->value;
    StringWrapper* op = ((StringWrapper*)(expression->rest->value));
    Object* arg2 = expression->rest->rest->value;

    if (cppNestedOperatorNeedsParenthesesP(op, arg1)) {
      *(oCURRENT_STREAMo->nativeStream) << "(";
    }
    if (cppBinaryOperatorP(op)) {
      cppHelpOutputBinaryOperator(((Cons*)(arg1))->rest, nestlevel + 1);
    }
    else {
      cppOutputStatement(arg1);
    }
    if (cppNestedOperatorNeedsParenthesesP(op, arg1)) {
      *(oCURRENT_STREAMo->nativeStream) << ")";
    }
    *(oCURRENT_STREAMo->nativeStream) << " ";
    *(oCURRENT_STREAMo->nativeStream) << op->wrapperValue;
    if (cppIndentableBinaryOperatorP(op)) {
      {
        *(oCURRENT_STREAMo->nativeStream) << std::endl;
        cppIndent();
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
    if (cppNestedOperatorNeedsParenthesesP(op, arg2)) {
      *(oCURRENT_STREAMo->nativeStream) << "(";
    }
    if (cppBinaryOperatorP(arg2)) {
      cppHelpOutputBinaryOperator(((Cons*)(arg2))->rest, nestlevel + 1);
    }
    else {
      cppOutputStatement(arg2);
    }
    if (cppNestedOperatorNeedsParenthesesP(op, arg2)) {
      *(oCURRENT_STREAMo->nativeStream) << ")";
    }
  }
}

void cppOutputBinaryOperator(Cons* expression) {
  cppHelpOutputBinaryOperator(expression, 0);
}

void cppOutputTernaryOperator(Cons* expression) {
  { Object* arg1 = expression->value;
    StringWrapper* op1 = ((StringWrapper*)(expression->rest->value));
    Object* arg2 = expression->rest->rest->value;
    StringWrapper* op2 = ((StringWrapper*)(expression->fourth()));
    Object* arg3 = expression->fifth();
    const char* translatedarg = NULL;

    *(oCURRENT_STREAMo->nativeStream) << "(";
    cppMaybeOutputStatementWithParentheses(arg1);
    *(oCURRENT_STREAMo->nativeStream) << " ";
    *(oCURRENT_STREAMo->nativeStream) << op1->wrapperValue;
    *(oCURRENT_STREAMo->nativeStream) << " ";
    { const char* result000 = NULL;

      { 
        BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, newOutputStringStream());
        cppMaybeOutputStatementWithParentheses(arg2);
        result000 = ((OutputStringStream*)(oCURRENT_STREAMo))->theStringReader();
      }
      translatedarg = result000;
    }
    *(oCURRENT_STREAMo->nativeStream) << translatedarg;
    *(oCURRENT_STREAMo->nativeStream) << " ";
    *(oCURRENT_STREAMo->nativeStream) << op2->wrapperValue;
    *(oCURRENT_STREAMo->nativeStream) << " ";
    { const char* result001 = NULL;

      { 
        BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, newOutputStringStream());
        cppMaybeOutputStatementWithParentheses(arg3);
        result001 = ((OutputStringStream*)(oCURRENT_STREAMo))->theStringReader();
      }
      translatedarg = result001;
    }
    *(oCURRENT_STREAMo->nativeStream) << translatedarg;
    *(oCURRENT_STREAMo->nativeStream) << ")";
  }
}

void cppOutputStatementLine(Cons* statement) {
  cppOutputStatement(statement->value);
  { Object* e = NULL;
    Cons* iter000 = statement->rest;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      e = iter000->value;
      *(oCURRENT_STREAMo->nativeStream) << " ";
      cppOutputStatement(e);
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
}

void cppOutputReturn(Cons* returnstatement) {
  *(oCURRENT_STREAMo->nativeStream) << "return";
  if (((boolean)(returnstatement))) {
    *(oCURRENT_STREAMo->nativeStream) << " (";
    cppOutputStatement(returnstatement);
    *(oCURRENT_STREAMo->nativeStream) << ")";
  }
}

void cppOutputTypeExpression(Cons* typeexpression) {
  { StringWrapper* typeexpr = NULL;
    Cons* iter000 = typeexpression;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      typeexpr = ((StringWrapper*)(iter000->value));
      *(oCURRENT_STREAMo->nativeStream) << typeexpr->wrapperValue << " ";
    }
  }
}

void cppOutputTypedEntity(Object* type, Object* entity, Object* initialvalue) {
  { boolean arraytypeP = cppTranslatedArrayTypeP(type);

    if (arraytypeP) {
      { const char* translatedtype = NULL;
        const char* translatedentity = NULL;

        { Surrogate* testValue000 = safePrimaryType(type);

          if (testValue000 == SGT_CPP_OUTPUT_STELLA_CONS) {
            { Object* type000 = type;
              Cons* type = ((Cons*)(type000));

              if (!(type->value == SYM_CPP_OUTPUT_STELLA_CPP_TYPE)) {
                type = cons(SYM_CPP_OUTPUT_STELLA_CPP_TYPE, type);
              }
              { const char* result000 = NULL;

                { 
                  BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, newOutputStringStream());
                  cppOutputStatement(type);
                  result000 = ((OutputStringStream*)(oCURRENT_STREAMo))->theStringReader();
                }
                translatedtype = result000;
              }
            }
          }
          else if (subtypeOfStringP(testValue000)) {
            { Object* type001 = type;
              StringWrapper* type = ((StringWrapper*)(type001));

              translatedtype = type->wrapperValue;
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
        { Surrogate* testValue001 = safePrimaryType(entity);

          if (testValue001 == SGT_CPP_OUTPUT_STELLA_CONS) {
            { Object* entity000 = entity;
              Cons* entity = ((Cons*)(entity000));

              { const char* result001 = NULL;

                { 
                  BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, newOutputStringStream());
                  cppOutputStatement(entity);
                  result001 = ((OutputStringStream*)(oCURRENT_STREAMo))->theStringReader();
                }
                translatedentity = result001;
              }
            }
          }
          else if (subtypeOfStringP(testValue001)) {
            { Object* entity001 = entity;
              StringWrapper* entity = ((StringWrapper*)(entity001));

              translatedentity = entity->wrapperValue;
            }
          }
          else {
            { OutputStringStream* stream001 = newOutputStringStream();

              *(stream001->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
              throw *newStellaException(stream001->theStringReader());
            }
          }
        }
        *(oCURRENT_STREAMo->nativeStream) << cppGenerateArrayTypedEntity(translatedentity, translatedtype);
      }
    }
    else {
      { Surrogate* testValue002 = safePrimaryType(type);

        if (testValue002 == SGT_CPP_OUTPUT_STELLA_CONS) {
          { Object* type002 = type;
            Cons* type = ((Cons*)(type002));

            if (!(type->value == SYM_CPP_OUTPUT_STELLA_CPP_TYPE)) {
              type = cons(SYM_CPP_OUTPUT_STELLA_CPP_TYPE, type);
            }
            cppOutputStatement(type);
          }
        }
        else if (subtypeOfStringP(testValue002)) {
          { Object* type003 = type;
            StringWrapper* type = ((StringWrapper*)(type003));

            *(oCURRENT_STREAMo->nativeStream) << type->wrapperValue << " ";
          }
        }
        else {
          { OutputStringStream* stream002 = newOutputStringStream();

            *(stream002->nativeStream) << "`" << testValue002 << "'" << " is not a valid case option";
            throw *newStellaException(stream002->theStringReader());
          }
        }
      }
      { Surrogate* testValue003 = safePrimaryType(entity);

        if (testValue003 == SGT_CPP_OUTPUT_STELLA_CONS) {
          { Object* entity002 = entity;
            Cons* entity = ((Cons*)(entity002));

            cppOutputStatement(entity);
          }
        }
        else if (subtypeOfStringP(testValue003)) {
          { Object* entity003 = entity;
            StringWrapper* entity = ((StringWrapper*)(entity003));

            *(oCURRENT_STREAMo->nativeStream) << entity->wrapperValue;
          }
        }
        else {
          { OutputStringStream* stream003 = newOutputStringStream();

            *(stream003->nativeStream) << "`" << testValue003 << "'" << " is not a valid case option";
            throw *newStellaException(stream003->theStringReader());
          }
        }
      }
    }
    if (((boolean)(initialvalue))) {
      *(oCURRENT_STREAMo->nativeStream) << " = ";
      cppOutputStatement(initialvalue);
    }
  }
}

void cppOutputDeclarations(Keyword* accesscontrolmode, Cons* declarations) {
  cppIndent();
  if (accesscontrolmode == KWD_CPP_OUTPUT_PUBLIC) {
    *(oCURRENT_STREAMo->nativeStream) << "public:" << std::endl;
  }
  else if (accesscontrolmode == KWD_CPP_OUTPUT_PRIVATE) {
    *(oCURRENT_STREAMo->nativeStream) << "private:" << std::endl;
  }
  else if (accesscontrolmode == KWD_CPP_OUTPUT_PROTECTED) {
    *(oCURRENT_STREAMo->nativeStream) << "protected:" << std::endl;
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << accesscontrolmode << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  if (((boolean)(accesscontrolmode))) {
    cppBumpIndent();
  }
  { Cons* declaration = NULL;
    Cons* iter000 = declarations;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      declaration = ((Cons*)(iter000->value));
      if (((boolean)(declaration->rest->rest->value))) {
        cppIndent();
        cppOutputComment(((StringWrapper*)(declaration->rest->rest->value)));
      }
      cppIndent();
      cppOutputTypedEntity(declaration->value, declaration->rest->value, NULL);
      *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
    }
  }
  if (((boolean)(accesscontrolmode))) {
    cppUnbumpIndent();
  }
}

void cppOutputSignature(Cons* signature, boolean outputmethodclassP) {
  { StringWrapper* methodclass = ((StringWrapper*)(signature->value));
    Object* returntype = signature->rest->value;
    StringWrapper* name = ((StringWrapper*)(signature->rest->rest->value));
    Object* parameters = signature->fourth();

    { const char* result000 = NULL;

      { 
        BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, newOutputStringStream());
        {
          if (outputmethodclassP &&
              ((boolean)(methodclass))) {
            *(oCURRENT_STREAMo->nativeStream) << methodclass->wrapperValue;
            *(oCURRENT_STREAMo->nativeStream) << "::";
          }
          *(oCURRENT_STREAMo->nativeStream) << name->wrapperValue;
          cppOutputFormalParameters(((Cons*)(parameters)));
        }
        result000 = ((OutputStringStream*)(oCURRENT_STREAMo))->theStringReader();
      }
      { const char* baresignature = result000;

        cppOutputTypedEntity(returntype, wrapString(baresignature), NULL);
      }
    }
  }
}

void cppOutputSignatures(Keyword* accesscontrolmode, Cons* signatures) {
  cppIndent();
  if (accesscontrolmode == KWD_CPP_OUTPUT_PUBLIC) {
    *(oCURRENT_STREAMo->nativeStream) << "public:" << std::endl;
  }
  else if (accesscontrolmode == KWD_CPP_OUTPUT_PRIVATE) {
    *(oCURRENT_STREAMo->nativeStream) << "private:" << std::endl;
  }
  else if (accesscontrolmode == KWD_CPP_OUTPUT_PROTECTED) {
    *(oCURRENT_STREAMo->nativeStream) << "protected:" << std::endl;
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << accesscontrolmode << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  if (((boolean)(accesscontrolmode))) {
    cppBumpIndent();
  }
  { Object* signature = NULL;
    Cons* iter000 = signatures;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      signature = iter000->value;
      cppIndent();
      cppOutputSignature(((Cons*)(signature)), false);
      *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
    }
  }
  if (((boolean)(accesscontrolmode))) {
    cppUnbumpIndent();
  }
}

void cppOutputDefinitions(Keyword* accesscontrolmode, Cons* definitions) {
  cppIndent();
  if (accesscontrolmode == KWD_CPP_OUTPUT_PUBLIC) {
    *(oCURRENT_STREAMo->nativeStream) << "public:" << std::endl;
  }
  else if (accesscontrolmode == KWD_CPP_OUTPUT_PRIVATE) {
    *(oCURRENT_STREAMo->nativeStream) << "private:" << std::endl;
  }
  else if (accesscontrolmode == KWD_CPP_OUTPUT_PROTECTED) {
    *(oCURRENT_STREAMo->nativeStream) << "protected:" << std::endl;
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << accesscontrolmode << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  if (((boolean)(accesscontrolmode))) {
    cppBumpIndent();
  }
  { Object* definition = NULL;
    Cons* iter000 = definitions;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      definition = iter000->value;
      cppIndent();
      cppOutputStatement(definition);
    }
  }
  if (((boolean)(accesscontrolmode))) {
    cppUnbumpIndent();
  }
}

void cppOutputProgn(Cons* progn) {
  *(oCURRENT_STREAMo->nativeStream) << "{" << std::endl;
  cppBumpIndent();
  cppOutputStatement(progn);
  cppUnbumpIndent();
  cppIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
}

void cppOutputBlock(Cons* block) {
  { boolean firststatementP = true;

    *(oCURRENT_STREAMo->nativeStream) << "{ ";
    cppBumpIndent();
    { Cons* declaration = NULL;
      Cons* iter000 = ((Cons*)(block->value));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        declaration = ((Cons*)(iter000->value));
        if (!(firststatementP)) {
          cppIndent();
        }
        firststatementP = false;
        cppOutputTypedEntity(declaration->value, declaration->rest->value, declaration->rest->rest->value);
        *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
      }
    }
    *(oCURRENT_STREAMo->nativeStream) << std::endl;
    cppOutputStatement(block->rest->value);
    cppUnbumpIndent();
    cppIndent();
    *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
  }
}

void cppOutputWithProcessLock(Cons* synch) {
  { OutputStringStream* s = newOutputStringStream();

    { 
      BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, s);
      cppOutputStatement(synch->value);
    }
    cppOutputComment(wrapString(stringConcatenate("Should be synchronized on process lock ", s->theStringReader(), 0)));
    cppIndent();
  }
  cppOutputProgn(((Cons*)(synch->rest->value)));
}

void cppOutputStaticMemberVars(StringWrapper* clasS, Cons* declarations) {
  { Cons* declaration = NULL;
    Cons* iter000 = declarations;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      declaration = ((Cons*)(iter000->value));
      cppIndent();
      cppOutputTypedEntity(declaration->value, wrapString(stringConcatenate(clasS->wrapperValue, "::", 1, ((StringWrapper*)(declaration->rest->value))->wrapperValue)), declaration->rest->rest->value);
      *(oCURRENT_STREAMo->nativeStream) << ";" << std::endl;
    }
  }
  if (!(declarations == NIL)) {
    *(oCURRENT_STREAMo->nativeStream) << std::endl;
  }
}

void cppOutputDerivedClasses(Cons* classlist) {
  if (((boolean)(classlist->value))) {
    *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(classlist->value))->wrapperValue;
  }
  { Object* clasS = NULL;
    Cons* iter000 = classlist->rest;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      clasS = iter000->value;
      *(oCURRENT_STREAMo->nativeStream) << ", public ";
      if (oTRANSLATOROUTPUTLANGUAGEo == KWD_CPP_OUTPUT_CPP_STANDALONE) {
        *(oCURRENT_STREAMo->nativeStream) << "virtual ";
      }
      else {
      }
      *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(clasS))->wrapperValue;
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << " ";
}

void cppOutputTemplateParameters(Cons* parameters) {
  if (!(parameters == NIL)) {
    *(oCURRENT_STREAMo->nativeStream) << "template <";
    *(oCURRENT_STREAMo->nativeStream) << "class " << ((StringWrapper*)(parameters->value))->wrapperValue;
    { Object* parameter = NULL;
      Cons* iter000 = parameters->rest;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        parameter = iter000->value;
        *(oCURRENT_STREAMo->nativeStream) << "class " << ((StringWrapper*)(parameter)) << ", ";
      }
    }
    *(oCURRENT_STREAMo->nativeStream) << ">" << std::endl;
  }
}

boolean cppOutputTemplateClassesP() {
  return (oTRANSLATOROUTPUTLANGUAGEo == KWD_CPP_OUTPUT_CPP_STANDALONE);
}

void cppOutputClass(Cons* classdef) {
  if (cppOutputTemplateClassesP()) {
    cppOutputTemplateParameters(((Cons*)(classdef->rest->value)));
  }
  *(oCURRENT_STREAMo->nativeStream) << "class " << ((StringWrapper*)(classdef->value))->wrapperValue << " ";
  if (!(((Cons*)(classdef->rest->rest->value)) == NIL)) {
    *(oCURRENT_STREAMo->nativeStream) << ": public ";
    if (oTRANSLATOROUTPUTLANGUAGEo == KWD_CPP_OUTPUT_CPP_STANDALONE) {
      *(oCURRENT_STREAMo->nativeStream) << "virtual ";
    }
    else {
    }
    cppOutputDerivedClasses(((Cons*)(classdef->rest->rest->value)));
  }
  *(oCURRENT_STREAMo->nativeStream) << "{" << std::endl;
  { Object* statement = NULL;
    Cons* iter000 = classdef->nthRest(4);

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      statement = iter000->value;
      cppOutputStatement(statement);
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << "};" << std::endl << std::endl;
  cppOutputStaticMemberVars(((StringWrapper*)(classdef->value)), ((Cons*)(classdef->fourth())));
}

void cppOutputFormalParameters(Cons* parameters) {
  { int nParameters = parameters->length();
    boolean variableArgumentsP = false;

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
          {
            variableArgumentsP = parameter->value == SYM_CPP_OUTPUT_STELLA_CPP_VAR_ARGS;
            cppOutputTypedEntity((variableArgumentsP ? wrapString("int") : parameter->value), parameter->rest->value, NULL);
            if (variableArgumentsP) {
              *(oCURRENT_STREAMo->nativeStream) << ", ...";
            }
          }
        }
        else {
          {
            cppOutputTypedEntity(parameter->value, parameter->rest->value, NULL);
            *(oCURRENT_STREAMo->nativeStream) << ", ";
          }
        }
      }
    }
    *(oCURRENT_STREAMo->nativeStream) << ")";
  }
}

boolean cppArgumentIsStreamP(Object* arg) {
  if (safePrimaryType(arg) == SGT_CPP_OUTPUT_STELLA_CONS) {
    { Object* arg000 = arg;
      Cons* arg = ((Cons*)(arg000));

      return ((arg->value == SYM_CPP_OUTPUT_STELLA_CPP_IDENT) &&
          eqlToStringP(arg->rest->value, "stream"));
    }
  }
  else {
    return (false);
  }
}

void cppOutputOneActualParameter(Object* parameter) {
  if (oOUTPUTTINGDEFPRINTpo &&
      cppArgumentIsStreamP(parameter)) {
    {
      *(oCURRENT_STREAMo->nativeStream) << "&";
      cppOutputStatement(parameter);
    }
  }
  else {
    cppOutputStatement(parameter);
  }
}

void cppOutputActualParameters(Cons* parameters) {
  *(oCURRENT_STREAMo->nativeStream) << "(";
  if (((boolean)(parameters->value))) {
    cppOutputOneActualParameter(parameters->value);
  }
  { Object* parameter = NULL;
    Cons* iter000 = parameters->rest;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      parameter = iter000->value;
      *(oCURRENT_STREAMo->nativeStream) << ", ";
      cppOutputOneActualParameter(parameter);
    }
  }
  *(oCURRENT_STREAMo->nativeStream) << ")";
}

void cppOutputMethodSetterCall(Cons* methodsettercall) {
  cppMaybeOutputStatementWithParentheses(methodsettercall->rest->value);
  *(oCURRENT_STREAMo->nativeStream) << "->";
  cppOutputStatement(methodsettercall->value);
  *(oCURRENT_STREAMo->nativeStream) << "_setter(";
  cppOutputStatement(methodsettercall->rest->rest->value);
  *(oCURRENT_STREAMo->nativeStream) << ")";
}

void cppOutputMethodCall(Cons* methodcall) {
  cppMaybeOutputStatementWithParentheses(methodcall->rest->rest->value);
  *(oCURRENT_STREAMo->nativeStream) << "->";
  cppOutputStatement(methodcall->rest->value);
  cppOutputStatement(methodcall->fourth());
}

void cppOutputReferencedMethodCall(Cons* methodcall) {
  cppMaybeOutputStatementWithParentheses(methodcall->rest->rest->value);
  *(oCURRENT_STREAMo->nativeStream) << ".";
  cppOutputStatement(methodcall->rest->value);
  cppOutputStatement(methodcall->fourth());
}

void cppOutputFunctionCall(Cons* functioncall) {
  cppOutputStatement(functioncall->value);
  cppOutputStatement(functioncall->rest->value);
}

void cppOutputDefprintSignature(Cons* defprint) {
  *(oCURRENT_STREAMo->nativeStream) << "std::ostream& operator << (std::ostream& stream, ";
  *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(defprint->value))->wrapperValue;
  *(oCURRENT_STREAMo->nativeStream) << " self)";
}

void cppOutputDefprint(Cons* defprint) {
  cppOutputDefprintSignature(defprint);
  *(oCURRENT_STREAMo->nativeStream) << " {" << std::endl;
  cppBumpIndent();
  { 
    BIND_STELLA_SPECIAL(oOUTPUTTINGDEFPRINTpo, boolean, true);
    cppOutputStatement(defprint->rest->value);
  }
  cppUnbumpIndent();
  *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
  *(oCURRENT_STREAMo->nativeStream) << std::endl;
}

void cppOutputFunctionSignature(Cons* function) {
  { const char* result000 = NULL;

    { 
      BIND_STELLA_SPECIAL(oCURRENT_STREAMo, OutputStream*, newOutputStringStream());
      {
        *(oCURRENT_STREAMo->nativeStream) << ((StringWrapper*)(function->rest->value))->wrapperValue;
        cppOutputFormalParameters(((Cons*)(function->rest->rest->value)));
      }
      result000 = ((OutputStringStream*)(oCURRENT_STREAMo))->theStringReader();
    }
    { const char* baresignature = result000;

      cppOutputTypedEntity(function->value, wrapString(baresignature), NULL);
    }
  }
}

void cppOutputFunction(Cons* function) {
  { Object* body = function->fourth();
    Cons* basemembers = ((Cons*)(function->fifth()));

    cppOutputFunctionSignature(function);
    if (((boolean)(basemembers))) {
      *(oCURRENT_STREAMo->nativeStream) << " : ";
      { Object* member = NULL;
        Cons* iter000 = basemembers;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          member = iter000->value;
          cppOutputStatement(member);
        }
      }
    }
    *(oCURRENT_STREAMo->nativeStream) << " {" << std::endl;
    cppBumpIndent();
    cppOutputStatement(body);
    cppUnbumpIndent();
    *(oCURRENT_STREAMo->nativeStream) << "}" << std::endl;
    *(oCURRENT_STREAMo->nativeStream) << std::endl;
  }
}

void cppOutputExternC(Cons* statement) {
  *(oCURRENT_STREAMo->nativeStream) << "extern \"C\" ";
  cppOutputStatement(statement);
}

void helpStartupCppOutput1() {
  {
    SYM_CPP_OUTPUT_STELLA_VRLET = ((Symbol*)(internRigidSymbolWrtModule("VRLET", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_STRING = ((Symbol*)(internRigidSymbolWrtModule("STRING", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_SPECIAL = ((Symbol*)(internRigidSymbolWrtModule("SPECIAL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_oCURRENT_STREAMo = ((Symbol*)(internRigidSymbolWrtModule("*CURRENT-STREAM*", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_NEW = ((Symbol*)(internRigidSymbolWrtModule("NEW", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_OUTPUT_STRING_STREAM = ((Symbol*)(internRigidSymbolWrtModule("OUTPUT-STRING-STREAM", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_THE_STRING = ((Symbol*)(internRigidSymbolWrtModule("THE-STRING", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CAST = ((Symbol*)(internRigidSymbolWrtModule("CAST", NULL, 0)));
    SGT_CPP_OUTPUT_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SYM_CPP_OUTPUT_STELLA_CPP_PROGN = ((Symbol*)(internRigidSymbolWrtModule("CPP_PROGN", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_STATEMENTS = ((Symbol*)(internRigidSymbolWrtModule("CPP_STATEMENTS", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_COMMENT = ((Symbol*)(internRigidSymbolWrtModule("CPP_COMMENT", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_CLASS = ((Symbol*)(internRigidSymbolWrtModule("CPP_CLASS", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_HANDLER_CASE = ((Symbol*)(internRigidSymbolWrtModule("CPP_HANDLER_CASE", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_CATCH = ((Symbol*)(internRigidSymbolWrtModule("CPP_CATCH", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_SIGNAL = ((Symbol*)(internRigidSymbolWrtModule("CPP_SIGNAL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_UNWIND_PROTECT = ((Symbol*)(internRigidSymbolWrtModule("CPP_UNWIND_PROTECT", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_VERBATIM = ((Symbol*)(internRigidSymbolWrtModule("CPP_VERBATIM", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_CAST = ((Symbol*)(internRigidSymbolWrtModule("CPP_CAST", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_GLOBAL = ((Symbol*)(internRigidSymbolWrtModule("CPP_GLOBAL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_SPECIAL = ((Symbol*)(internRigidSymbolWrtModule("CPP_SPECIAL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_LOCAL = ((Symbol*)(internRigidSymbolWrtModule("CPP_LOCAL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_TYPE = ((Symbol*)(internRigidSymbolWrtModule("CPP_TYPE", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_DEREFERENCE = ((Symbol*)(internRigidSymbolWrtModule("CPP_DEREFERENCE", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_ARRAY_REFERENCE = ((Symbol*)(internRigidSymbolWrtModule("CPP_ARRAY_REFERENCE", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_WITH_PROCESS_LOCK = ((Symbol*)(internRigidSymbolWrtModule("CPP_WITH_PROCESS_LOCK", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_BREAK = ((Symbol*)(internRigidSymbolWrtModule("CPP_BREAK", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_CONTINUE = ((Symbol*)(internRigidSymbolWrtModule("CPP_CONTINUE", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_GOTO = ((Symbol*)(internRigidSymbolWrtModule("CPP_GOTO", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_GOTO_LABEL = ((Symbol*)(internRigidSymbolWrtModule("CPP_GOTO_LABEL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_IF = ((Symbol*)(internRigidSymbolWrtModule("CPP_IF", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_SIGNATURE = ((Symbol*)(internRigidSymbolWrtModule("CPP_FUNCTION_SIGNATURE", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_METHOD_SIGNATURE = ((Symbol*)(internRigidSymbolWrtModule("CPP_METHOD_SIGNATURE", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_COND = ((Symbol*)(internRigidSymbolWrtModule("CPP_COND", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_CASE = ((Symbol*)(internRigidSymbolWrtModule("CPP_CASE", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_WHEN = ((Symbol*)(internRigidSymbolWrtModule("CPP_WHEN", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_UNLESS = ((Symbol*)(internRigidSymbolWrtModule("CPP_UNLESS", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_ASSIGN = ((Symbol*)(internRigidSymbolWrtModule("CPP_ASSIGN", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_LOOP = ((Symbol*)(internRigidSymbolWrtModule("CPP_LOOP", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_WHILE = ((Symbol*)(internRigidSymbolWrtModule("CPP_WHILE", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("CPP_FOREACH", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_BLOCK = ((Symbol*)(internRigidSymbolWrtModule("CPP_BLOCK", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_IDENT = ((Symbol*)(internRigidSymbolWrtModule("CPP_IDENT", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_PRINT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("CPP_PRINT_STREAM", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_PRINT_NATIVE_STREAM = ((Symbol*)(internRigidSymbolWrtModule("CPP_PRINT_NATIVE_STREAM", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_LITERAL = ((Symbol*)(internRigidSymbolWrtModule("CPP_LITERAL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("CPP_FUNCTION", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_METHOD = ((Symbol*)(internRigidSymbolWrtModule("CPP_METHOD", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_RETURN = ((Symbol*)(internRigidSymbolWrtModule("CPP_RETURN", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_SYMBOL = ((Symbol*)(internRigidSymbolWrtModule("CPP_SYMBOL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_MAKE = ((Symbol*)(internRigidSymbolWrtModule("CPP_MAKE", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_FUNCALL = ((Symbol*)(internRigidSymbolWrtModule("CPP_FUNCALL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_METHOD_CODE_CALL = ((Symbol*)(internRigidSymbolWrtModule("CPP_METHOD_CODE_CALL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_POINTER = ((Symbol*)(internRigidSymbolWrtModule("CPP_FUNCTION_POINTER", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_METHOD_POINTER = ((Symbol*)(internRigidSymbolWrtModule("CPP_METHOD_POINTER", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("CPP_SLOT_VALUE", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_REFERENCED_SLOT_VALUE = ((Symbol*)(internRigidSymbolWrtModule("CPP_REFERENCED_SLOT_VALUE", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_SLOT_VALUE_SETTER = ((Symbol*)(internRigidSymbolWrtModule("CPP_SLOT_VALUE_SETTER", NULL, 0)));
  }
}

void helpStartupCppOutput2() {
  {
    SYM_CPP_OUTPUT_STELLA_CPP_DECLARATIONS = ((Symbol*)(internRigidSymbolWrtModule("CPP_DECLARATIONS", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_DEFINITIONS = ((Symbol*)(internRigidSymbolWrtModule("CPP_DEFINITIONS", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_SIGNATURES = ((Symbol*)(internRigidSymbolWrtModule("CPP_SIGNATURES", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_UNARY_OP = ((Symbol*)(internRigidSymbolWrtModule("CPP_UNARY_OP", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_BINARY_OP = ((Symbol*)(internRigidSymbolWrtModule("CPP_BINARY_OP", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_TERNARY_OP = ((Symbol*)(internRigidSymbolWrtModule("CPP_TERNARY_OP", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_CALL = ((Symbol*)(internRigidSymbolWrtModule("CPP_FUNCTION_CALL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_METHOD_SETTER_CALL = ((Symbol*)(internRigidSymbolWrtModule("CPP_METHOD_SETTER_CALL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_METHOD_CALL = ((Symbol*)(internRigidSymbolWrtModule("CPP_METHOD_CALL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_REFERENCED_METHOD_CALL = ((Symbol*)(internRigidSymbolWrtModule("CPP_REFERENCED_METHOD_CALL", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_ACTUALS = ((Symbol*)(internRigidSymbolWrtModule("CPP_ACTUALS", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_DEFPRINT = ((Symbol*)(internRigidSymbolWrtModule("CPP_DEFPRINT", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_EXTERN_C = ((Symbol*)(internRigidSymbolWrtModule("CPP_EXTERN_C", NULL, 0)));
    KWD_CPP_OUTPUT_UNBIND_WITH_DESTRUCTORS = ((Keyword*)(internRigidSymbolWrtModule("UNBIND-WITH-DESTRUCTORS", NULL, 2)));
    SYM_CPP_OUTPUT_STELLA_NEWLINE = ((Symbol*)(internRigidSymbolWrtModule("NEWLINE", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_NULL_VALUE = ((Symbol*)(internRigidSymbolWrtModule("CPP_NULL_VALUE", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_ASSIGN = ((Symbol*)(internRigidSymbolWrtModule("ASSIGN", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_SCOLON = ((Symbol*)(internRigidSymbolWrtModule("SCOLON", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_LPAREN = ((Symbol*)(internRigidSymbolWrtModule("LPAREN", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_RPAREN = ((Symbol*)(internRigidSymbolWrtModule("RPAREN", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_NEW = ((Symbol*)(internRigidSymbolWrtModule("CPP_NEW", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_THROW = ((Symbol*)(internRigidSymbolWrtModule("CPP_THROW", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_STANDARD_OUT = ((Symbol*)(internRigidSymbolWrtModule("CPP_STANDARD_OUT", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_CPP_STANDARD_ERROR = ((Symbol*)(internRigidSymbolWrtModule("CPP_STANDARD_ERROR", NULL, 0)));
    KWD_CPP_OUTPUT_PUBLIC = ((Keyword*)(internRigidSymbolWrtModule("PUBLIC", NULL, 2)));
    KWD_CPP_OUTPUT_PRIVATE = ((Keyword*)(internRigidSymbolWrtModule("PRIVATE", NULL, 2)));
    KWD_CPP_OUTPUT_PROTECTED = ((Keyword*)(internRigidSymbolWrtModule("PROTECTED", NULL, 2)));
    KWD_CPP_OUTPUT_CPP_STANDALONE = ((Keyword*)(internRigidSymbolWrtModule("CPP-STANDALONE", NULL, 2)));
    SYM_CPP_OUTPUT_STELLA_CPP_VAR_ARGS = ((Symbol*)(internRigidSymbolWrtModule("CPP_VAR_ARGS", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_STARTUP_CPP_OUTPUT = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-CPP-OUTPUT", NULL, 0)));
    SYM_CPP_OUTPUT_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupCppOutput3() {
  {
    defineFunctionObject("CPP-OUTPUT-TO-STRING", "(DEFUN CPP-OUTPUT-TO-STRING ((STATEMENT CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&cppOutputToString)), NULL);
    defineFunctionObject("CPP-OUTPUT-PARSE-TREE", "(DEFUN CPP-OUTPUT-PARSE-TREE ((CONSTREE CONS)))", ((cpp_function_code)(&cppOutputParseTree)), NULL);
    defineFunctionObject("CPP-FLATTEN-STATEMENTS", "(DEFUN (CPP-FLATTEN-STATEMENTS CONS) ((STATEMENTS CONS)))", ((cpp_function_code)(&cppFlattenStatements)), NULL);
    defineFunctionObject("CPP-PROGNIFY-STATEMENT", "(DEFUN (CPP-PROGNIFY-STATEMENT CONS) ((STATEMENT OBJECT)))", ((cpp_function_code)(&cppPrognifyStatement)), NULL);
    defineFunctionObject("CPP-STATEMENT-TO-LIST", "(DEFUN (CPP-STATEMENT-TO-LIST CONS) ((STATEMENT OBJECT)))", ((cpp_function_code)(&cppStatementToList)), NULL);
    defineFunctionObject("CPP-OUTPUT-STATEMENT", "(DEFUN CPP-OUTPUT-STATEMENT ((STATEMENT OBJECT)))", ((cpp_function_code)(&cppOutputStatement)), NULL);
    defineFunctionObject("CPP-OUTPUT-VERBATIM", "(DEFUN CPP-OUTPUT-VERBATIM ((VERBATIMSTATEMENT STRING-WRAPPER)))", ((cpp_function_code)(&cppOutputVerbatim)), NULL);
    defineFunctionObject("CPP-OUTPUT-COMMENT", "(DEFUN CPP-OUTPUT-COMMENT ((TREE STRING-WRAPPER)))", ((cpp_function_code)(&cppOutputComment)), NULL);
    defineFunctionObject("CPP-OUTPUT-DEREFERENCE", "(DEFUN CPP-OUTPUT-DEREFERENCE ((TREE CONS)))", ((cpp_function_code)(&cppOutputDereference)), NULL);
    defineFunctionObject("CPP-OUTPUT-ARRAY-REFERENCE", "(DEFUN CPP-OUTPUT-ARRAY-REFERENCE ((TREE CONS)))", ((cpp_function_code)(&cppOutputArrayReference)), NULL);
    defineFunctionObject("CPP-OUTPUT-CAST", "(DEFUN CPP-OUTPUT-CAST ((TREE CONS)))", ((cpp_function_code)(&cppOutputCast)), NULL);
    defineFunctionObject("CPP-OUTPUT-SIGNAL", "(DEFUN CPP-OUTPUT-SIGNAL ((TREE CONS)))", ((cpp_function_code)(&cppOutputSignal)), NULL);
    defineFunctionObject("CPP-OUTPUT-HANDLER-CASE", "(DEFUN CPP-OUTPUT-HANDLER-CASE ((TREE CONS)))", ((cpp_function_code)(&cppOutputHandlerCase)), NULL);
    defineFunctionObject("CPP-OUTPUT-CATCH", "(DEFUN CPP-OUTPUT-CATCH ((TREE CONS)))", ((cpp_function_code)(&cppOutputCatch)), NULL);
    defineFunctionObject("CPP-OUTPUT-UNWIND-PROTECT", "(DEFUN CPP-OUTPUT-UNWIND-PROTECT ((TREE CONS)))", ((cpp_function_code)(&cppOutputUnwindProtect)), NULL);
    defineFunctionObject("CPP-OUTPUT-GLOBAL-DECLARATION", "(DEFUN CPP-OUTPUT-GLOBAL-DECLARATION ((GLOBAL CONS)))", ((cpp_function_code)(&cppOutputGlobalDeclaration)), NULL);
    defineFunctionObject("CPP-OUTPUT-VARIABLE-DEFINITION", "(DEFUN CPP-OUTPUT-VARIABLE-DEFINITION ((VARIABLE CONS)))", ((cpp_function_code)(&cppOutputVariableDefinition)), NULL);
    defineFunctionObject("CPP-OUTPUT-FUNCALL-FUNCTION-SIGNATURE", "(DEFUN CPP-OUTPUT-FUNCALL-FUNCTION-SIGNATURE ((SIGNATURE CONS)))", ((cpp_function_code)(&cppOutputFuncallFunctionSignature)), NULL);
    defineFunctionObject("CPP-OUTPUT-METHOD-CODE-CALL-SIGNATURE", "(DEFUN CPP-OUTPUT-METHOD-CODE-CALL-SIGNATURE ((SIGNATURE CONS)))", ((cpp_function_code)(&cppOutputMethodCodeCallSignature)), NULL);
    defineFunctionObject("CPP-OUTPUT-FUNCALL", "(DEFUN CPP-OUTPUT-FUNCALL ((FUNCALL CONS)))", ((cpp_function_code)(&cppOutputFuncall)), NULL);
    defineFunctionObject("CPP-OUTPUT-METHOD-CODE-CALL", "(DEFUN CPP-OUTPUT-METHOD-CODE-CALL ((METHODCALL CONS)))", ((cpp_function_code)(&cppOutputMethodCodeCall)), NULL);
    defineFunctionObject("CPP-OUTPUT-BREAK", "(DEFUN CPP-OUTPUT-BREAK ())", ((cpp_function_code)(&cppOutputBreak)), NULL);
    defineFunctionObject("CPP-OUTPUT-CONTINUE", "(DEFUN CPP-OUTPUT-CONTINUE ())", ((cpp_function_code)(&cppOutputContinue)), NULL);
    defineFunctionObject("CPP-OUTPUT-GOTO", "(DEFUN CPP-OUTPUT-GOTO ((LABEL OBJECT)))", ((cpp_function_code)(&cppOutputGoto)), NULL);
    defineFunctionObject("CPP-OUTPUT-GOTO-LABEL", "(DEFUN CPP-OUTPUT-GOTO-LABEL ((LABEL OBJECT)))", ((cpp_function_code)(&cppOutputGotoLabel)), NULL);
    defineFunctionObject("CPP-LAST-STATEMENT-IS-RETURN?", "(DEFUN (CPP-LAST-STATEMENT-IS-RETURN? BOOLEAN) ((STATEMENTS CONS)))", ((cpp_function_code)(&cppLastStatementIsReturnP)), NULL);
    defineFunctionObject("CPP-OUTPUT-CASE", "(DEFUN CPP-OUTPUT-CASE ((CASE CONS)))", ((cpp_function_code)(&cppOutputCase)), NULL);
    defineFunctionObject("CPP-OUTPUT-COND", "(DEFUN CPP-OUTPUT-COND ((COND CONS)))", ((cpp_function_code)(&cppOutputCond)), NULL);
    defineFunctionObject("CPP-PROGN?", "(DEFUN (CPP-PROGN? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&cppPrognP)), NULL);
    defineFunctionObject("CPP-BLOCK?", "(DEFUN (CPP-BLOCK? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&cppBlockP)), NULL);
    defineFunctionObject("CPP-OUTPUT-IF", "(DEFUN CPP-OUTPUT-IF ((TREE CONS)))", ((cpp_function_code)(&cppOutputIf)), NULL);
    defineFunctionObject("CPP-OUTPUT-WHEN", "(DEFUN CPP-OUTPUT-WHEN ((TREE CONS)))", ((cpp_function_code)(&cppOutputWhen)), NULL);
    defineFunctionObject("CPP-OUTPUT-UNLESS", "(DEFUN CPP-OUTPUT-UNLESS ((TREE CONS)))", ((cpp_function_code)(&cppOutputUnless)), NULL);
    defineFunctionObject("CPP-OUTPUT-ASSIGNMENT", "(DEFUN CPP-OUTPUT-ASSIGNMENT ((ASSIGNMENT CONS)))", ((cpp_function_code)(&cppOutputAssignment)), NULL);
    defineFunctionObject("CPP-OUTPUT-LOOP", "(DEFUN CPP-OUTPUT-LOOP ((LOOP CONS)))", ((cpp_function_code)(&cppOutputLoop)), NULL);
    defineFunctionObject("CPP-OUTPUT-WHILE", "(DEFUN CPP-OUTPUT-WHILE ((LOOP CONS)))", ((cpp_function_code)(&cppOutputWhile)), NULL);
    defineFunctionObject("CPP-OUTPUT-FOREACH", "(DEFUN CPP-OUTPUT-FOREACH ((LOOP CONS)))", ((cpp_function_code)(&cppOutputForeach)), NULL);
    defineFunctionObject("CPP-OUTPUT-FUNCTION-POINTER", "(DEFUN CPP-OUTPUT-FUNCTION-POINTER ((FUNCTIONNAME STRING-WRAPPER)))", ((cpp_function_code)(&cppOutputFunctionPointer)), NULL);
    defineFunctionObject("CPP-OUTPUT-METHOD-POINTER", "(DEFUN CPP-OUTPUT-METHOD-POINTER ((METHODNAME STRING-WRAPPER)))", ((cpp_function_code)(&cppOutputMethodPointer)), NULL);
    defineFunctionObject("CPP-OUTPUT-SLOT-VALUE", "(DEFUN CPP-OUTPUT-SLOT-VALUE ((STATEMENT CONS)))", ((cpp_function_code)(&cppOutputSlotValue)), NULL);
    defineFunctionObject("CPP-OUTPUT-REFERENCED-SLOT-VALUE", "(DEFUN CPP-OUTPUT-REFERENCED-SLOT-VALUE ((STATEMENT CONS)))", ((cpp_function_code)(&cppOutputReferencedSlotValue)), NULL);
    defineFunctionObject("CPP-OUTPUT-SLOT-VALUE-SETTER", "(DEFUN CPP-OUTPUT-SLOT-VALUE-SETTER ((STATEMENT CONS)))", ((cpp_function_code)(&cppOutputSlotValueSetter)), NULL);
    defineFunctionObject("CPP-OUTPUT-MAKE", "(DEFUN CPP-OUTPUT-MAKE ((STATEMENT CONS)))", ((cpp_function_code)(&cppOutputMake)), NULL);
    defineFunctionObject("CPP-BUMP-INDENT", "(DEFUN CPP-BUMP-INDENT ())", ((cpp_function_code)(&cppBumpIndent)), NULL);
    defineFunctionObject("CPP-UNBUMP-INDENT", "(DEFUN CPP-UNBUMP-INDENT ())", ((cpp_function_code)(&cppUnbumpIndent)), NULL);
    defineMethodObject("(DEFMETHOD CPP-OUTPUT-LITERAL ((OBJECT OBJECT)))", wrapMethodCode(((cpp_method_code)(&Object::cppOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD CPP-OUTPUT-LITERAL ((CHARACTER CHARACTER-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&CharacterWrapper::cppOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD CPP-OUTPUT-LITERAL ((INT INTEGER-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&IntegerWrapper::cppOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD CPP-OUTPUT-LITERAL ((INT LONG-INTEGER-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&LongIntegerWrapper::cppOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD CPP-OUTPUT-LITERAL ((FLOAT FLOAT-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&FloatWrapper::cppOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD CPP-OUTPUT-LITERAL ((BOOLEAN BOOLEAN-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&BooleanWrapper::cppOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD CPP-OUTPUT-LITERAL ((CONS CONS)))", wrapMethodCode(((cpp_method_code)(&Cons::cppOutputLiteral))), NULL);
    defineFunctionObject("REPLACE-CHARACTER-WITH-SUBSTRING", "(DEFUN (REPLACE-CHARACTER-WITH-SUBSTRING STRING) ((STRING STRING) (NEW STRING) (CHARACTER CHARACTER)) :GLOBALLY-INLINE? TRUE (RETURN (REPLACE-SUBSTRINGS STRING NEW CHARACTER)))", ((cpp_function_code)(&replaceCharacterWithSubstring)), NULL);
    defineMethodObject("(DEFMETHOD CPP-OUTPUT-LITERAL ((STRING STRING)))", wrapFunctionCode(((cpp_function_code)(((void  (*) (const char*))(&stringCppOutputLiteral))))), NULL);
    defineMethodObject("(DEFMETHOD CPP-OUTPUT-LITERAL ((STRING STRING-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&StringWrapper::cppOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD CPP-OUTPUT-LITERAL ((STRING MUTABLE-STRING-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&MutableStringWrapper::cppOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD CPP-OUTPUT-LITERAL ((TREE QUOTED-EXPRESSION)))", wrapMethodCode(((cpp_method_code)(&QuotedExpression::cppOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD CPP-OUTPUT-LITERAL ((SYMBOL SYMBOL)))", wrapMethodCode(((cpp_method_code)(&Symbol::cppOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD CPP-OUTPUT-LITERAL ((SURROGATE SURROGATE)))", wrapMethodCode(((cpp_method_code)(&Surrogate::cppOutputLiteral))), NULL);
    defineMethodObject("(DEFMETHOD CPP-OUTPUT-LITERAL ((KEYWORD KEYWORD)))", wrapMethodCode(((cpp_method_code)(&Keyword::cppOutputLiteral))), NULL);
  }
}

void startupCppOutput() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupCppOutput1();
      helpStartupCppOutput2();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupCppOutput3();
      defineFunctionObject("CPP-OUTPUT-IDENTIFIER", "(DEFUN CPP-OUTPUT-IDENTIFIER ((IDENTIFIER STRING-WRAPPER)))", ((cpp_function_code)(&cppOutputIdentifier)), NULL);
      defineFunctionObject("CPP-OUTPUT-ATOMIC-EXPRESSION", "(DEFUN CPP-OUTPUT-ATOMIC-EXPRESSION ((ATOM OBJECT)))", ((cpp_function_code)(&cppOutputAtomicExpression)), NULL);
      defineFunctionObject("CPP-INDENT", "(DEFUN CPP-INDENT ())", ((cpp_function_code)(&cppIndent)), NULL);
      defineFunctionObject("CPP-OUTPUT-SEMICOLON?", "(DEFUN (CPP-OUTPUT-SEMICOLON? BOOLEAN) ((STATEMENT CONS)))", ((cpp_function_code)(&cppOutputSemicolonP)), NULL);
      defineFunctionObject("CPP-INDENT-STATEMENT?", "(DEFUN (CPP-INDENT-STATEMENT? BOOLEAN) ((STATEMENT CONS)))", ((cpp_function_code)(&cppIndentStatementP)), NULL);
      defineFunctionObject("ILLEGAL-CPP-STATEMENT?", "(DEFUN (ILLEGAL-CPP-STATEMENT? BOOLEAN) ((STATEMENT CONS)))", ((cpp_function_code)(&illegalCppStatementP)), NULL);
      defineFunctionObject("CPP-OUTPUT-STATEMENTS", "(DEFUN CPP-OUTPUT-STATEMENTS ((STATEMENTLIST CONS)))", ((cpp_function_code)(&cppOutputStatements)), NULL);
      defineFunctionObject("CPP-MAYBE-OUTPUT-STATEMENT-WITH-PARENTHESES", "(DEFUN CPP-MAYBE-OUTPUT-STATEMENT-WITH-PARENTHESES ((STATEMENT OBJECT)))", ((cpp_function_code)(&cppMaybeOutputStatementWithParentheses)), NULL);
      defineFunctionObject("CPP-OUTPUT-STREAM-PRINT-ITEMS", "(DEFUN CPP-OUTPUT-STREAM-PRINT-ITEMS ((ITEMS CONS)))", ((cpp_function_code)(&cppOutputStreamPrintItems)), NULL);
      defineFunctionObject("CPP-OUTPUT-PRINT-STREAM", "(DEFUN CPP-OUTPUT-PRINT-STREAM ((EXPS CONS)))", ((cpp_function_code)(&cppOutputPrintStream)), NULL);
      defineFunctionObject("CPP-OUTPUT-PRINT-NATIVE-STREAM", "(DEFUN CPP-OUTPUT-PRINT-NATIVE-STREAM ((EXPS CONS)))", ((cpp_function_code)(&cppOutputPrintNativeStream)), NULL);
      defineFunctionObject("CPP-INDENTABLE-BINARY-OPERATOR?", "(DEFUN (CPP-INDENTABLE-BINARY-OPERATOR? BOOLEAN) ((OPERATOR STRING-WRAPPER)))", ((cpp_function_code)(&cppIndentableBinaryOperatorP)), NULL);
      defineFunctionObject("CPP-COMMUTATIVE-BINARY-OPERATOR?", "(DEFUN (CPP-COMMUTATIVE-BINARY-OPERATOR? BOOLEAN) ((OPERATOR STRING-WRAPPER)))", ((cpp_function_code)(&cppCommutativeBinaryOperatorP)), NULL);
      defineFunctionObject("CPP-BINARY-OPERATOR?", "(DEFUN (CPP-BINARY-OPERATOR? BOOLEAN) ((STATEMENT OBJECT)))", ((cpp_function_code)(&cppBinaryOperatorP)), NULL);
      defineFunctionObject("CPP-OPERATOR?", "(DEFUN (CPP-OPERATOR? BOOLEAN) ((STATEMENT OBJECT)))", ((cpp_function_code)(&cppOperatorP)), NULL);
      defineFunctionObject("CPP-ASSIGNMENT?", "(DEFUN (CPP-ASSIGNMENT? BOOLEAN) ((STATEMENT CONS)))", ((cpp_function_code)(&cppAssignmentP)), NULL);
      defineFunctionObject("CPP-OUTPUT-UNARY-OPERATOR", "(DEFUN CPP-OUTPUT-UNARY-OPERATOR ((EXPRESSION CONS)))", ((cpp_function_code)(&cppOutputUnaryOperator)), NULL);
      defineFunctionObject("CPP-NESTED-OPERATOR-NEEDS-PARENTHESES?", "(DEFUN (CPP-NESTED-OPERATOR-NEEDS-PARENTHESES? BOOLEAN) ((OP STRING-WRAPPER) (NESTED OBJECT)))", ((cpp_function_code)(&cppNestedOperatorNeedsParenthesesP)), NULL);
      defineFunctionObject("CPP-HELP-OUTPUT-BINARY-OPERATOR", "(DEFUN CPP-HELP-OUTPUT-BINARY-OPERATOR ((EXPRESSION CONS) (NESTLEVEL INTEGER)))", ((cpp_function_code)(&cppHelpOutputBinaryOperator)), NULL);
      defineFunctionObject("CPP-OUTPUT-BINARY-OPERATOR", "(DEFUN CPP-OUTPUT-BINARY-OPERATOR ((EXPRESSION CONS)))", ((cpp_function_code)(&cppOutputBinaryOperator)), NULL);
      defineFunctionObject("CPP-OUTPUT-TERNARY-OPERATOR", "(DEFUN CPP-OUTPUT-TERNARY-OPERATOR ((EXPRESSION CONS)))", ((cpp_function_code)(&cppOutputTernaryOperator)), NULL);
      defineFunctionObject("CPP-OUTPUT-STATEMENT-LINE", "(DEFUN CPP-OUTPUT-STATEMENT-LINE ((STATEMENT CONS)))", ((cpp_function_code)(&cppOutputStatementLine)), NULL);
      defineFunctionObject("CPP-OUTPUT-RETURN", "(DEFUN CPP-OUTPUT-RETURN ((RETURNSTATEMENT CONS)))", ((cpp_function_code)(&cppOutputReturn)), NULL);
      defineFunctionObject("CPP-OUTPUT-TYPE-EXPRESSION", "(DEFUN CPP-OUTPUT-TYPE-EXPRESSION ((TYPEEXPRESSION (CONS OF STRING-WRAPPER))))", ((cpp_function_code)(&cppOutputTypeExpression)), NULL);
      defineFunctionObject("CPP-OUTPUT-TYPED-ENTITY", "(DEFUN CPP-OUTPUT-TYPED-ENTITY ((TYPE OBJECT) (ENTITY OBJECT) (INITIALVALUE OBJECT)))", ((cpp_function_code)(&cppOutputTypedEntity)), NULL);
      defineFunctionObject("CPP-OUTPUT-DECLARATIONS", "(DEFUN CPP-OUTPUT-DECLARATIONS ((ACCESSCONTROLMODE KEYWORD) (DECLARATIONS (CONS OF CONS))))", ((cpp_function_code)(&cppOutputDeclarations)), NULL);
      defineFunctionObject("CPP-OUTPUT-SIGNATURE", "(DEFUN CPP-OUTPUT-SIGNATURE ((SIGNATURE CONS) (OUTPUTMETHODCLASS? BOOLEAN)))", ((cpp_function_code)(&cppOutputSignature)), NULL);
      defineFunctionObject("CPP-OUTPUT-SIGNATURES", "(DEFUN CPP-OUTPUT-SIGNATURES ((ACCESSCONTROLMODE KEYWORD) (SIGNATURES CONS)))", ((cpp_function_code)(&cppOutputSignatures)), NULL);
      defineFunctionObject("CPP-OUTPUT-DEFINITIONS", "(DEFUN CPP-OUTPUT-DEFINITIONS ((ACCESSCONTROLMODE KEYWORD) (DEFINITIONS CONS)))", ((cpp_function_code)(&cppOutputDefinitions)), NULL);
      defineFunctionObject("CPP-OUTPUT-PROGN", "(DEFUN CPP-OUTPUT-PROGN ((PROGN CONS)))", ((cpp_function_code)(&cppOutputProgn)), NULL);
      defineFunctionObject("CPP-OUTPUT-BLOCK", "(DEFUN CPP-OUTPUT-BLOCK ((BLOCK CONS)))", ((cpp_function_code)(&cppOutputBlock)), NULL);
      defineFunctionObject("CPP-OUTPUT-WITH-PROCESS-LOCK", "(DEFUN CPP-OUTPUT-WITH-PROCESS-LOCK ((SYNCH CONS)))", ((cpp_function_code)(&cppOutputWithProcessLock)), NULL);
      defineFunctionObject("CPP-OUTPUT-STATIC-MEMBER-VARS", "(DEFUN CPP-OUTPUT-STATIC-MEMBER-VARS ((CLASS STRING-WRAPPER) (DECLARATIONS (CONS OF CONS))))", ((cpp_function_code)(&cppOutputStaticMemberVars)), NULL);
      defineFunctionObject("CPP-OUTPUT-DERIVED-CLASSES", "(DEFUN CPP-OUTPUT-DERIVED-CLASSES ((CLASSLIST CONS)))", ((cpp_function_code)(&cppOutputDerivedClasses)), NULL);
      defineFunctionObject("CPP-OUTPUT-TEMPLATE-PARAMETERS", "(DEFUN CPP-OUTPUT-TEMPLATE-PARAMETERS ((PARAMETERS CONS)))", ((cpp_function_code)(&cppOutputTemplateParameters)), NULL);
      defineFunctionObject("CPP-OUTPUT-TEMPLATE-CLASSES?", "(DEFUN (CPP-OUTPUT-TEMPLATE-CLASSES? BOOLEAN) ())", ((cpp_function_code)(&cppOutputTemplateClassesP)), NULL);
      defineFunctionObject("CPP-OUTPUT-CLASS", "(DEFUN CPP-OUTPUT-CLASS ((CLASSDEF CONS)))", ((cpp_function_code)(&cppOutputClass)), NULL);
      defineFunctionObject("CPP-OUTPUT-FORMAL-PARAMETERS", "(DEFUN CPP-OUTPUT-FORMAL-PARAMETERS ((PARAMETERS (CONS OF CONS))))", ((cpp_function_code)(&cppOutputFormalParameters)), NULL);
      defineFunctionObject("CPP-ARGUMENT-IS-STREAM?", "(DEFUN (CPP-ARGUMENT-IS-STREAM? BOOLEAN) ((ARG OBJECT)))", ((cpp_function_code)(&cppArgumentIsStreamP)), NULL);
      defineFunctionObject("CPP-OUTPUT-ONE-ACTUAL-PARAMETER", "(DEFUN CPP-OUTPUT-ONE-ACTUAL-PARAMETER ((PARAMETER OBJECT)))", ((cpp_function_code)(&cppOutputOneActualParameter)), NULL);
      defineFunctionObject("CPP-OUTPUT-ACTUAL-PARAMETERS", "(DEFUN CPP-OUTPUT-ACTUAL-PARAMETERS ((PARAMETERS CONS)))", ((cpp_function_code)(&cppOutputActualParameters)), NULL);
      defineFunctionObject("CPP-OUTPUT-METHOD-SETTER-CALL", "(DEFUN CPP-OUTPUT-METHOD-SETTER-CALL ((METHODSETTERCALL CONS)))", ((cpp_function_code)(&cppOutputMethodSetterCall)), NULL);
      defineFunctionObject("CPP-OUTPUT-METHOD-CALL", "(DEFUN CPP-OUTPUT-METHOD-CALL ((METHODCALL CONS)))", ((cpp_function_code)(&cppOutputMethodCall)), NULL);
      defineFunctionObject("CPP-OUTPUT-REFERENCED-METHOD-CALL", "(DEFUN CPP-OUTPUT-REFERENCED-METHOD-CALL ((METHODCALL CONS)))", ((cpp_function_code)(&cppOutputReferencedMethodCall)), NULL);
      defineFunctionObject("CPP-OUTPUT-FUNCTION-CALL", "(DEFUN CPP-OUTPUT-FUNCTION-CALL ((FUNCTIONCALL CONS)))", ((cpp_function_code)(&cppOutputFunctionCall)), NULL);
      defineFunctionObject("CPP-OUTPUT-DEFPRINT-SIGNATURE", "(DEFUN CPP-OUTPUT-DEFPRINT-SIGNATURE ((DEFPRINT CONS)))", ((cpp_function_code)(&cppOutputDefprintSignature)), NULL);
      defineFunctionObject("CPP-OUTPUT-DEFPRINT", "(DEFUN CPP-OUTPUT-DEFPRINT ((DEFPRINT CONS)))", ((cpp_function_code)(&cppOutputDefprint)), NULL);
      defineFunctionObject("CPP-OUTPUT-FUNCTION-SIGNATURE", "(DEFUN CPP-OUTPUT-FUNCTION-SIGNATURE ((FUNCTION CONS)))", ((cpp_function_code)(&cppOutputFunctionSignature)), NULL);
      defineFunctionObject("CPP-OUTPUT-FUNCTION", "(DEFUN CPP-OUTPUT-FUNCTION ((FUNCTION CONS)))", ((cpp_function_code)(&cppOutputFunction)), NULL);
      defineFunctionObject("CPP-OUTPUT-EXTERN-C", "(DEFUN CPP-OUTPUT-EXTERN-C ((STATEMENT CONS)))", ((cpp_function_code)(&cppOutputExternC)), NULL);
      defineFunctionObject("STARTUP-CPP-OUTPUT", "(DEFUN STARTUP-CPP-OUTPUT () :PUBLIC? TRUE)", ((cpp_function_code)(&startupCppOutput)), NULL);
      { MethodSlot* function = lookupFunction(SYM_CPP_OUTPUT_STELLA_STARTUP_CPP_OUTPUT);

        setDynamicSlotValue(function->dynamicSlots, SYM_CPP_OUTPUT_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupCppOutput"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFSPECIAL *CPP-INDENT-CHARS* INTEGER 0)", &oCPP_INDENT_CHARSo);
      defineGlobalVariableObject("(DEFSPECIAL *OUTPUTTINGDEFPRINT?* BOOLEAN FALSE :DOCUMENTATION \"`true' when outputting a defprint, used to \n            conditionally dereference streams in print-native-stream \n            statements.  Also used to take the address of streams\n            when passed to functions inside of a defprint\")", &oOUTPUTTINGDEFPRINTpo);
      defineGlobalVariableObject("(DEFGLOBAL *CPP-MAX-STRING-LITERAL-LENGTH* INTEGER 1024 :DOCUMENTATION \"C++ string literals longer than this are broken\ninto multiple pieces to avoid problems with certain MS compilers.\")", &oCPP_MAX_STRING_LITERAL_LENGTHo);
    }
  }
}

Symbol* SYM_CPP_OUTPUT_STELLA_VRLET = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_STRING = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_NULL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_SPECIAL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_oCURRENT_STREAMo = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_NEW = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_OUTPUT_STRING_STREAM = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_SETQ = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_THE_STRING = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CAST = NULL;

Surrogate* SGT_CPP_OUTPUT_STELLA_CONS = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_PROGN = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_STATEMENTS = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_COMMENT = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_CLASS = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_HANDLER_CASE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_CATCH = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_SIGNAL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_UNWIND_PROTECT = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_VERBATIM = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_CAST = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_GLOBAL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_SPECIAL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_LOCAL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_TYPE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_DEREFERENCE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_ARRAY_REFERENCE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_WITH_PROCESS_LOCK = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_BREAK = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_CONTINUE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_GOTO = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_GOTO_LABEL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_IF = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_SIGNATURE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_METHOD_SIGNATURE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_COND = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_CASE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_WHEN = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_UNLESS = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_ASSIGN = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_LOOP = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_WHILE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_FOREACH = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_BLOCK = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_IDENT = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_PRINT_STREAM = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_PRINT_NATIVE_STREAM = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_LITERAL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_METHOD = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_RETURN = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_SYMBOL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_MAKE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_FUNCALL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_METHOD_CODE_CALL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_POINTER = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_METHOD_POINTER = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_SLOT_VALUE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_REFERENCED_SLOT_VALUE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_SLOT_VALUE_SETTER = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_DECLARATIONS = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_DEFINITIONS = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_SIGNATURES = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_UNARY_OP = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_BINARY_OP = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_TERNARY_OP = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_CALL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_METHOD_SETTER_CALL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_METHOD_CALL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_REFERENCED_METHOD_CALL = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_ACTUALS = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_DEFPRINT = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_EXTERN_C = NULL;

Keyword* KWD_CPP_OUTPUT_UNBIND_WITH_DESTRUCTORS = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_NEWLINE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_NULL_VALUE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_ASSIGN = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_SCOLON = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_LPAREN = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_RPAREN = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_NEW = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_THROW = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_STANDARD_OUT = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_STANDARD_ERROR = NULL;

Keyword* KWD_CPP_OUTPUT_PUBLIC = NULL;

Keyword* KWD_CPP_OUTPUT_PRIVATE = NULL;

Keyword* KWD_CPP_OUTPUT_PROTECTED = NULL;

Keyword* KWD_CPP_OUTPUT_CPP_STANDALONE = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_CPP_VAR_ARGS = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_STARTUP_CPP_OUTPUT = NULL;

Symbol* SYM_CPP_OUTPUT_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
