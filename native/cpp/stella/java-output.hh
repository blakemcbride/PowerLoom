//  -*- Mode: C++ -*-

// java-output.hh

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
extern DECLARE_STELLA_SPECIAL(oJAVA_INDENT_CHARSo, int );
extern KeyValueList* oJAVA_STELLA_PACKAGE_MAPPINGo;
extern Cons* oJAVA_SEMICOLON_STATEMENTSo;

// Function signatures:
const char* javaStellaPackage();
void javaOutputParseTree(Cons* constree);
void javaBumpIndent();
void javaUnbumpIndent();
void javaIndent();
void javaOutputStatement(Object* statement);
void javaMaybeOutputStatementWithParentheses(Object* statement);
void javaOutputIdentifier(StringWrapper* identifier);
void stringJavaOutputLiteral(const char* string);
void javaOutputMakeArray(Cons* statement);
void javaOutputArray(Cons* arrayelements);
void javaOutputAnonymousArray(Cons* statement);
void javaOutputAref(Cons* statement);
void javaOutputSlotValue(Cons* statement);
void javaOutputSlotValueSetter(Cons* statement);
void javaOutputImplementsInterfaces(Cons* interfacelist);
void javaOutputClass(Cons* classdef, boolean exceptionclassP);
void javaOutputClassDeclaration(Cons* classdef);
void javaOutputClassVariableDefinitions(Cons* variabletranslations);
void javaOutputClassConstructors(Cons* constructors, const char* classname, boolean exceptionclassP);
void javaOutputClassMethods(Cons* methods);
void javaOutputExceptionConstructor(const char* exceptionname);
void javaOutputNamedStatement(Cons* namedstatement);
void javaOutputFormalParameters(Cons* parameters);
void javaOutputMethodSignature(Cons* method);
Cons* javaSeparateCommentFromBody(Cons* body, Cons*& _Return1);
void javaOutputMethod(Cons* method);
void javaOutputTypeExpression(Cons* typeexpression);
boolean javaOutputSemicolonP(Cons* statement);
boolean javaIndentStatementP(Cons* statement);
boolean javaIllegalStatementP(Cons* statement);
void javaOutputStatements(Cons* statementlist);
void javaOutputDeclarations(Cons* declarations);
const char* javaHeuristicallyTranslateName(const char* stellaName, Cons* caseConvertedNameList);
void javaOutputCommentString(const char* comment, const char* commentStart, const char* commentContinuation, const char* commentEnd, boolean javadocCommentP, Cons* caseConvertedNameList);
void javaOutputComment(StringWrapper* tree);
void javaOutputJavadocComment(StringWrapper* tree, Cons* parameterNamesAndTypes, StringWrapper* returnValue, const char* author, const char* version);
const char* fixupDocumentationStringQuoting(const char* documentation);
void javaOutputVerbatim(StringWrapper* verbatimstatement);
void javaOutputMake(Cons* statement);
void javaOutputCast(Cons* tree);
void javaOutputProgn(Cons* progn);
void javaOutputBlock(Cons* block);
void javaOutputWithProcessLock(Cons* synch);
void javaOutputReturn(Cons* returnstatement);
void javaOutputThrow(Cons* tree);
void javaOutputCatch(Cons* tree);
void javaOutputUnwindProtect(Cons* tree);
void javaOutputHandlerCase(Cons* tree);
void javaOutputSignal(Cons* tree);
void javaOutputGlobalDefinition(Cons* global);
void javaOutputActualsAsConsExpression(Cons* arglist);
void javaOutputFuncall(Cons* funcall);
void javaOutputMethodCodeCall(Cons* methodcall);
void javaOutputBreak(Cons* tag);
void javaOutputContinue(Cons* tag);
boolean javaStatementReturnsP(Cons* statement);
boolean javaLastStatementReturnsP(Cons* statements);
void javaOutputCase(Cons* casE);
void javaOutputCond(Cons* cond);
boolean javaPrognP(Object* tree);
boolean javaBlockP(Object* tree);
void javaOutputIf(Cons* tree);
void javaOutputWhen(Cons* tree);
void javaOutputUnless(Cons* tree);
void javaOutputAssignment(Cons* assignment);
void javaOutputLoop(Cons* loop);
void javaOutputWhile(Cons* loop);
void javaOutputForeach(Cons* loop);
boolean javaEndOfLineTokenP(Object* token);
void javaOutputPrintStream(Cons* exps, boolean nativestreamP);
boolean javaLiteralStringP(Cons* item);
Cons* javaReverseAndConsolidateStrings(Cons* items);
void javaHelpOutputPrintStream(Object* stream, Cons* exps, boolean nativestreamP, boolean endoflineP);
boolean javaIndentableBinaryOperatorP(StringWrapper* operatoR);
boolean javaCommutativeBinaryOperatorP(StringWrapper* operatoR);
boolean javaBinaryOperatorP(Object* statement);
boolean javaOperatorP(Object* statement);
void javaOutputUnaryOperator(Cons* expression);
boolean javaNestedOperatorNeedsParenthesesP(StringWrapper* op, Object* nested);
void javaHelpOutputBinaryOperator(Cons* expression, int nestlevel);
void javaOutputBinaryOperator(Cons* expression);
void javaOutputTernaryOperator(Cons* expression);
void javaOutputMethodCall(Cons* methodcall);
void javaOutputFunctionCall(Cons* functioncall);
void javaOutputActualParameters(Cons* parameters);
void helpStartupJavaOutput1();
void helpStartupJavaOutput2();
void helpStartupJavaOutput3();
void startupJavaOutput();

// Auxiliary global declarations:
extern Surrogate* SGT_JAVA_OUTPUT_STELLA_CONS;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_CLASS;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_EXCEPTION_CLASS;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_NAMED_STATEMENT;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_STATEMENTS;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_IDENT;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_EOL;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_LITERAL;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_COMMENT;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_SYMBOL;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_CATCH;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_THROW;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_UNWIND_PROTECT;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_HANDLER_CASE;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_SIGNAL;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_VERBATIM;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_CAST;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_GLOBAL;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_TYPE;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_PROGN;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_BLOCK;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_WITH_PROCESS_LOCK;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_RETURN;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_MAKE;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCALL;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_CODE_CALL;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_ASSIGN;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_BREAK;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_CONTINUE;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_COND;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_CASE;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_IF;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_WHEN;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_UNLESS;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_LOOP;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_WHILE;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_FOREACH;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_SLOT_VALUE;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_SLOT_VALUE_SETTER;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_UNARY_OP;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_BINARY_OP;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_TERNARY_OP;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCTION_CALL;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_CALL;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_ACTUALS;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_MAKE_ARRAY;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_ARRAY_INITIALIZER;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_ANONYMOUS_ARRAY;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_AREF;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCTION;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_PRINT_STREAM;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_PRINT_NATIVE_STREAM;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_DECLARATIONS;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_FUNCTION_POINTER;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_POINTER;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_METHOD_SETTER_CALL;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_NEW;
extern Keyword* KWD_JAVA_OUTPUT_NO;
extern Keyword* KWD_JAVA_OUTPUT_PRESERVE;
extern Keyword* KWD_JAVA_OUTPUT_CLEVER;
extern Keyword* KWD_JAVA_OUTPUT_UPCASE;
extern Keyword* KWD_JAVA_OUTPUT_TITLECASEX;
extern Keyword* KWD_JAVA_OUTPUT_WHITE_SPACE;
extern Surrogate* SGT_JAVA_OUTPUT_STELLA_STRING_WRAPPER;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_STANDARD_OUT;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_JAVA_STANDARD_ERROR;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_STARTUP_JAVA_OUTPUT;
extern Symbol* SYM_JAVA_OUTPUT_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
