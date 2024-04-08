//  -*- Mode: C++ -*-

// cpp-output.hh

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



namespace stella {

// Global declarations:
extern DECLARE_STELLA_SPECIAL(oCPP_INDENT_CHARSo, int );
extern DECLARE_STELLA_SPECIAL(oOUTPUTTINGDEFPRINTpo, boolean );
extern int oCPP_MAX_STRING_LITERAL_LENGTHo;

// Function signatures:
Object* cppOutputToString(Cons* statement);
void cppOutputParseTree(Cons* constree);
Cons* cppFlattenStatements(Cons* statements);
Cons* cppPrognifyStatement(Object* statement);
Cons* cppStatementToList(Object* statement);
void cppOutputStatement(Object* statement);
void cppOutputVerbatim(StringWrapper* verbatimstatement);
void cppOutputComment(StringWrapper* tree);
void cppOutputDereference(Cons* tree);
void cppOutputArrayReference(Cons* tree);
void cppOutputCast(Cons* tree);
void cppOutputSignal(Cons* tree);
void cppOutputHandlerCase(Cons* tree);
void cppOutputCatch(Cons* tree);
void cppOutputUnwindProtect(Cons* tree);
void cppOutputGlobalDeclaration(Cons* global);
void cppOutputVariableDefinition(Cons* variable);
void cppOutputFuncallFunctionSignature(Cons* signature);
void cppOutputMethodCodeCallSignature(Cons* signature);
void cppOutputFuncall(Cons* funcall);
void cppOutputMethodCodeCall(Cons* methodcall);
void cppOutputBreak();
void cppOutputContinue();
void cppOutputGoto(Object* label);
void cppOutputGotoLabel(Object* label);
boolean cppLastStatementIsReturnP(Cons* statements);
void cppOutputCase(Cons* casE);
void cppOutputCond(Cons* cond);
boolean cppPrognP(Object* tree);
boolean cppBlockP(Object* tree);
void cppOutputIf(Cons* tree);
void cppOutputWhen(Cons* tree);
void cppOutputUnless(Cons* tree);
void cppOutputAssignment(Cons* assignment);
void cppOutputLoop(Cons* loop);
void cppOutputWhile(Cons* loop);
void cppOutputForeach(Cons* loop);
void cppOutputFunctionPointer(StringWrapper* functionname);
void cppOutputMethodPointer(StringWrapper* methodname);
void cppOutputSlotValue(Cons* statement);
void cppOutputReferencedSlotValue(Cons* statement);
void cppOutputSlotValueSetter(Cons* statement);
void cppOutputMake(Cons* statement);
void cppBumpIndent();
void cppUnbumpIndent();
const char* replaceCharacterWithSubstring(const char* string, const char* neW, char character);
void stringCppOutputLiteral(const char* string);
void cppOutputIdentifier(StringWrapper* identifier);
void cppOutputAtomicExpression(Object* atom);
void cppIndent();
boolean cppOutputSemicolonP(Cons* statement);
boolean cppIndentStatementP(Cons* statement);
boolean illegalCppStatementP(Cons* statement);
void cppOutputStatements(Cons* statementlist);
void cppMaybeOutputStatementWithParentheses(Object* statement);
void cppOutputStreamPrintItems(Cons* items);
void cppOutputPrintStream(Cons* exps);
void cppOutputPrintNativeStream(Cons* exps);
boolean cppIndentableBinaryOperatorP(StringWrapper* operatoR);
boolean cppCommutativeBinaryOperatorP(StringWrapper* operatoR);
boolean cppBinaryOperatorP(Object* statement);
boolean cppOperatorP(Object* statement);
boolean cppAssignmentP(Cons* statement);
void cppOutputUnaryOperator(Cons* expression);
boolean cppNestedOperatorNeedsParenthesesP(StringWrapper* op, Object* nested);
void cppHelpOutputBinaryOperator(Cons* expression, int nestlevel);
void cppOutputBinaryOperator(Cons* expression);
void cppOutputTernaryOperator(Cons* expression);
void cppOutputStatementLine(Cons* statement);
void cppOutputReturn(Cons* returnstatement);
void cppOutputTypeExpression(Cons* typeexpression);
void cppOutputTypedEntity(Object* type, Object* entity, Object* initialvalue);
void cppOutputDeclarations(Keyword* accesscontrolmode, Cons* declarations);
void cppOutputSignature(Cons* signature, boolean outputmethodclassP);
void cppOutputSignatures(Keyword* accesscontrolmode, Cons* signatures);
void cppOutputDefinitions(Keyword* accesscontrolmode, Cons* definitions);
void cppOutputProgn(Cons* progn);
void cppOutputBlock(Cons* block);
void cppOutputWithProcessLock(Cons* synch);
void cppOutputStaticMemberVars(StringWrapper* clasS, Cons* declarations);
void cppOutputDerivedClasses(Cons* classlist);
void cppOutputTemplateParameters(Cons* parameters);
boolean cppOutputTemplateClassesP();
void cppOutputClass(Cons* classdef);
void cppOutputFormalParameters(Cons* parameters);
boolean cppArgumentIsStreamP(Object* arg);
void cppOutputOneActualParameter(Object* parameter);
void cppOutputActualParameters(Cons* parameters);
void cppOutputMethodSetterCall(Cons* methodsettercall);
void cppOutputMethodCall(Cons* methodcall);
void cppOutputReferencedMethodCall(Cons* methodcall);
void cppOutputFunctionCall(Cons* functioncall);
void cppOutputDefprintSignature(Cons* defprint);
void cppOutputDefprint(Cons* defprint);
void cppOutputFunctionSignature(Cons* function);
void cppOutputFunction(Cons* function);
void cppOutputExternC(Cons* statement);
void helpStartupCppOutput1();
void helpStartupCppOutput2();
void helpStartupCppOutput3();
void startupCppOutput();

// Auxiliary global declarations:
extern Symbol* SYM_CPP_OUTPUT_STELLA_VRLET;
extern Symbol* SYM_CPP_OUTPUT_STELLA_STRING;
extern Symbol* SYM_CPP_OUTPUT_STELLA_NULL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_SPECIAL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_oCURRENT_STREAMo;
extern Symbol* SYM_CPP_OUTPUT_STELLA_NEW;
extern Symbol* SYM_CPP_OUTPUT_STELLA_OUTPUT_STRING_STREAM;
extern Symbol* SYM_CPP_OUTPUT_STELLA_SETQ;
extern Symbol* SYM_CPP_OUTPUT_STELLA_THE_STRING;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CAST;
extern Surrogate* SGT_CPP_OUTPUT_STELLA_CONS;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_PROGN;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_STATEMENTS;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_COMMENT;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_CLASS;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_HANDLER_CASE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_CATCH;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_SIGNAL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_UNWIND_PROTECT;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_VERBATIM;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_CAST;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_GLOBAL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_SPECIAL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_LOCAL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_TYPE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_DEREFERENCE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_ARRAY_REFERENCE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_WITH_PROCESS_LOCK;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_BREAK;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_CONTINUE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_GOTO;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_GOTO_LABEL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_IF;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_SIGNATURE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_METHOD_SIGNATURE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_COND;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_CASE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_WHEN;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_UNLESS;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_ASSIGN;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_LOOP;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_WHILE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_FOREACH;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_BLOCK;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_IDENT;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_PRINT_STREAM;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_PRINT_NATIVE_STREAM;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_LITERAL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_METHOD;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_RETURN;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_SYMBOL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_MAKE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_FUNCALL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_METHOD_CODE_CALL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_POINTER;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_METHOD_POINTER;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_SLOT_VALUE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_REFERENCED_SLOT_VALUE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_SLOT_VALUE_SETTER;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_DECLARATIONS;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_DEFINITIONS;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_SIGNATURES;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_UNARY_OP;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_BINARY_OP;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_TERNARY_OP;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_FUNCTION_CALL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_METHOD_SETTER_CALL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_METHOD_CALL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_REFERENCED_METHOD_CALL;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_ACTUALS;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_DEFPRINT;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_EXTERN_C;
extern Keyword* KWD_CPP_OUTPUT_UNBIND_WITH_DESTRUCTORS;
extern Symbol* SYM_CPP_OUTPUT_STELLA_NEWLINE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_NULL_VALUE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_ASSIGN;
extern Symbol* SYM_CPP_OUTPUT_STELLA_SCOLON;
extern Symbol* SYM_CPP_OUTPUT_STELLA_LPAREN;
extern Symbol* SYM_CPP_OUTPUT_STELLA_RPAREN;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_NEW;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_THROW;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_STANDARD_OUT;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_STANDARD_ERROR;
extern Keyword* KWD_CPP_OUTPUT_PUBLIC;
extern Keyword* KWD_CPP_OUTPUT_PRIVATE;
extern Keyword* KWD_CPP_OUTPUT_PROTECTED;
extern Keyword* KWD_CPP_OUTPUT_CPP_STANDALONE;
extern Symbol* SYM_CPP_OUTPUT_STELLA_CPP_VAR_ARGS;
extern Symbol* SYM_CPP_OUTPUT_STELLA_STARTUP_CPP_OUTPUT;
extern Symbol* SYM_CPP_OUTPUT_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
