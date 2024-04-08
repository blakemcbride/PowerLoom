//  -*- Mode: C++ -*-

// java-translate.hh

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
extern StringWrapper* oJAVA_TRUE_STRING_WRAPPERo;
extern StringWrapper* oJAVA_FALSE_STRING_WRAPPERo;
extern DECLARE_STELLA_SPECIAL(oVARARGSTATEMENTSo, Cons* );
extern DECLARE_STELLA_SPECIAL(oVARARGDECLSo, Cons* );
extern DECLARE_STELLA_SPECIAL(oCURRENTVARARGINDEXo, int );
extern KeyValueList* oJAVA_OPERATOR_TABLEo;
extern const char* oJAVA_CHARACTER_SUBSTITUTION_TABLEo;
extern StringHashTable* oJAVA_RESERVED_WORD_TABLEo;
extern DECLARE_STELLA_SPECIAL(oJAVA_LOOP_NAMEo, Symbol* );
extern DECLARE_STELLA_SPECIAL(oJAVA_LOOP_NAME_USEDpo, boolean );
extern KeyValueList* oJAVA_PRIMITIVE_ARRAY_TYPE_NAMESo;

// Function signatures:
const char* javaYieldFlotsamClassName(Module* mod);
const char* javaYieldNativeClassName();
const char* javaYieldSpecialVariableClassName();
const char* javaYieldFullNativeClassName();
Cons* javaTranslateUnit(TranslationUnit* unit);
Cons* javaTranslateDefineGlobalVariableUnit(TranslationUnit* unit);
Cons* wrapMethodBodyWithJavaAuxiliaryDeclarations(Cons* methodbody, Cons* declarations);
boolean javaSynchronizedMethodP(MethodSlot* method);
Cons* javaTranslateMethodSignature(MethodSlot* method);
Cons* javaTranslateDefineMethodUnit(TranslationUnit* unit);
Cons* javaTranslateDefprintUnit(TranslationUnit* unit);
Cons* javaTranslateListOfTrees(Cons* trees);
Object* javaTranslateATree(Object* tree);
Cons* javaLookupOperatorTable(Symbol* operatoR);
const char* javaCreateCharacterSubstitutionTable();
const char* javaSubstituteForbiddenCharacters(const char* name, Keyword* caseconvention);
const char* javaChangeCase(GeneralizedSymbol* symbol, Keyword* caseconvention);
boolean javaLiteralP(StandardObject* typespec);
StringWrapper* javaNativeLiteralWrapperNames(StandardObject* typespec, StringWrapper*& _Return1);
StringWrapper* javaSpecialSetterName(StandardObject* typespec);
const char* javaYieldFlotsamTypeName(const char* flotsamClassName);
StringWrapper* javaTranslateSymbolConstantName(GeneralizedSymbol* symbol);
StringWrapper* javaTranslateSymbolConstantId(GeneralizedSymbol* symbol);
StringWrapper* javaTranslateSymbolName(Symbol* symbol);
StringWrapper* javaTranslateSymbolId(Symbol* symbol);
StringWrapper* javaTranslateSurrogateName(Surrogate* surrogate);
StringWrapper* javaTranslateSurrogateId(Surrogate* surrogate);
StringWrapper* javaTranslateKeywordName(Keyword* keyword);
StringWrapper* javaTranslateKeywordId(Keyword* keyword);
StringWrapper* javaTranslateClassNamestring(StringWrapper* namestring);
StringWrapper* javaTranslateClassName(GeneralizedSymbol* namesymbol);
boolean inCurrentJavaPackageP(Module* module);
boolean inheritedClassNameConflictsP(const char* stellaClassName);
boolean classNameConflictsWithSlotNameP(Class* definingClass, const char* javaClassName);
boolean omitJavaPackagePrefixP(Module* module, const char* stellaClassName);
StringWrapper* javaTranslateTypeSpec(StandardObject* typeSpec);
StringWrapper* javaTranslateTypeSpecForFunction(StandardObject* typeSpec);
StringWrapper* javaTranslateTypeSpecHelper(StandardObject* typeSpec, boolean functionP);
StringWrapper* javaTranslateArrayType(ParametricTypeSpecifier* arraytype);
StringWrapper* javaTranslateArrayOfTypeSpec(StandardObject* typespec, boolean fullyqualifiedP);
StringWrapper* javaYieldRenamedReservedWord(Symbol* word);
StringHashTable* javaCreateReservedWordTable();
const char* javaLookupReservedWordTable(const char* word);
const char* javaTranslateNamestring(const char* namestring);
StringWrapper* javaTranslateName(Symbol* namesymbol);
Cons* javaTranslateSpecialTree(Cons* tree);
Cons* javaTranslateVerbatimTree(Cons* tree);
Object* javaTranslateInlineCallTree(Cons* tree);
Cons* javaTranslateUnwindProtect(Cons* tree);
Cons* javaTranslateSignal(Cons* tree);
Cons* javaTranslateHandlerCase(Cons* tree);
Cons* javaTranslateHandleException(Cons* tree);
Cons* javaTranslateVoidSys(Cons* tree);
Cons* javaTranslateTypedSys(Cons* tree);
Object* javaTranslateBadSys(Cons* tree);
Object* javaTranslateSetqTree(Cons* tree);
Object* javaTranslateSysSetDefault(Cons* tree);
Cons* javaTranslateSysSlotValueSetter(Cons* tree);
Cons* javaTranslateSysSlotValue(Cons* tree);
Cons* javaTranslateProgn(Cons* tree);
Cons* javaTranslateWithProcessLock(Cons* tree);
Cons* javaTranslateLoop(Cons* tree);
Cons* javaTranslateForeachTree(Cons* tree);
Cons* javaTranslateLetTree(Cons* tree);
Cons* javaTranslateCast(Cons* tree);
Cons* javaTranslateReturnTree(Cons* tree);
Cons* javaTranslateBreak(Cons* tree);
Cons* javaTranslateContinue(Cons* tree);
Cons* javaTranslateIfTree(Cons* tree);
boolean javaSymbolCaseP(Object* keyform);
Cons* javaYieldSymbolIdForm(int symbolid);
Cons* javaTranslateCondition(Cons* condition, boolean symbolcasep);
Cons* javaTranslateCaseTree(Cons* tree);
Cons* javaTranslateCondTree(Cons* tree);
Cons* javaTranslateWhile(Cons* tree);
Cons* javaTranslateChooseTree(Cons* tree);
Cons* javaTranslateWhenTree(Cons* tree);
Cons* javaTranslateUnlessTree(Cons* tree);
Cons* javaTranslateMakeTree(Cons* tree);
Cons* javaTranslateSysNew(Cons* tree);
Cons* javaTranslateNewArray(Cons* tree);
Cons* javaTranslateMvSetq(Cons* tree);
Cons* javaTranslateMvFunctionCall(Cons* functioncall, Symbol* mvvectorname);
Cons* javaTranslateCodeSignature(Cons* signature);
Cons* javaTranslateWithNativeWrapper(Object* tree, StandardObject* type);
Cons* javaTranslateActualParametersWithNativeWrappers(Cons* trees, Cons* parametertypes);
Cons* javaWrapWithNativeValueExtraction(Cons* tree, StandardObject* primaryreturntype);
Cons* javaTranslateObjectToReturnType(Cons* tree, StandardObject* returntype);
Cons* javaTranslateCallFunctionCode(Cons* tree);
Cons* javaTranslateCallMethodCode(Cons* tree);
const char* javaPackagePrefix(Module* module, const char* separator);
StringWrapper* javaYieldFullyQualifiedTypeName(StandardObject* typespec);
StringWrapper* javaYieldTranslatedClassAndFunctionNames(MethodSlot* f, StringWrapper*& _Return1);
const char* javaYieldTranslatedClassAndMethodNames(StandardObject* owner, MethodSlot* f, const char*& _Return1);
Cons* javaTranslateClassObjectLookup(const char* classname);
Cons* javaYieldClassObjectArrayExpression(StandardObject* typespec, int ndimensions);
Cons* javaYieldClassObjectExpression(StandardObject* typespec);
const char* yieldClassObjectLookupNameForNativeType(const char* nativetype);
Cons* javaTranslateParamTypeSpecifications(MethodSlot* fn, StandardObject* owner);
Object* javaTranslateTheCode(Cons* tree);
StringWrapper* javaTranslateFunctionName(MethodSlot* function);
Object* javaTranslateIgnoreTree(Cons* tree);
boolean javaStreamIsStandardOutputP(Object* tree);
Cons* javaTranslatePrintStream(Cons* tree);
Cons* javaTranslatePrintNativeStream(Cons* tree);
Cons* javaTranslateNull();
Cons* javaTranslateEol();
const char* javaPrependGlobalClassName(const char* namestring, Module* module);
StringWrapper* javaTranslateGlobalName(Symbol* namesymbol, boolean definitionP);
Cons* javaTranslateGeneralSymbol(Symbol* tree);
Object* javaTranslateMethodParameter(Symbol* name, StandardObject* type, MethodSlot* method);
Cons* javaTranslateReturnParameter();
Cons* javaTranslateMethodParameters(MethodSlot* method);
boolean zeroArgumentFunctionP(MethodSlot* method);
boolean javaMethodObjectDefinedOnNativeTypeP(MethodSlot* method);
boolean javaMethodObjectIsOverloadedFunctionP(MethodSlot* method);
boolean javaMethodObjectIsFunctionP(MethodSlot* method);
boolean javaFunctionInDifferentModuleP(MethodSlot* method);
Symbol* javaCreateOverloadedFunctionName(Symbol* functionname, Surrogate* classtype);
Cons* javaDeleteQuotedNullStatements(Cons* trees);
Cons* javaWrapMethodBodyWithVarargDeclarations(Cons* methodbody);
Cons* javaWrapMethodBodyWithVarargValueSetup(Cons* methodbody);
StringWrapper* javaTranslateVariableLengthArgName(Symbol* namesymbol, int parameternumber);
Cons* javaTranslateVariableLengthActuals(Cons* actuals, MethodSlot* unusedMethod);
Cons* javaTranslateActualParameters(Cons* tree);
const char* javaYieldClassNameForFunction(MethodSlot* function);
Cons* javaTranslateFunctionCall(Cons* tree, MethodSlot* method);
Cons* javaTranslateDefinedOrNull(Surrogate* classtype, Object* object, boolean nullP);
Cons* javaTranslateMethodCall(Cons* tree);
Object* javaTranslateSuperMethodCall(Cons* tree);
Cons* javaTranslateNormalMethodCall(Symbol* methodname, Surrogate* classtype, Cons* allargs);
Cons* javaTranslateOperatorTree(Cons* tree);
Cons* javaTranslateOperatorCall(Cons* operatornames, Cons* arguments, int arity);
Cons* javaTranslateArefMethodCall(Symbol* operatoR, Surrogate* owner, Cons* arguments);
Cons* javaTranslateNthMethodCall(Symbol* operatoR, Surrogate* owner, Cons* arguments);
void helpStartupJavaTranslate1();
void helpStartupJavaTranslate2();
void helpStartupJavaTranslate3();
void helpStartupJavaTranslate4();
void helpStartupJavaTranslate5();
void helpStartupJavaTranslate6();
void helpStartupJavaTranslate7();
void startupJavaTranslate();

// Auxiliary global declarations:
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_FLOTSAM_CLASS;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_GLOBAL_VARIABLE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_CLASS;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_TYPE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_METHOD;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_MACRO;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_PRINT_METHOD;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_STARTUP_TIME_PROGN;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_VERBATIM;
extern Keyword* KWD_JAVA_TRANSLATE_UNBOUND_SPECIAL_VARIABLE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_GLOBAL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_TYPE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_MAKE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_IDENT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_ACTUALS;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_STATEMENTS;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_BLOCK;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_THIS;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_DOCUMENTATION;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_COMMENT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SELF;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_CONS;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SPECIAL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_UNWIND_PROTECT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_SIGNAL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_HANDLER_CASE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_HANDLE_EXCEPTION;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_VOID_SYS;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_TYPED_SYS;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_BAD_SYS;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SETQ;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_SET_DEFAULT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_SLOT_VALUE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_SLOT_VALUE_SETTER;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_METHOD;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_FUNCTION;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_SUPER_METHOD;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_PROGN;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_WITH_PROCESS_LOCK;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_LOOP;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_FOREACH;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_LET;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_CAST;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SAFE_CAST;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_RETURN;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_BREAK;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_CONTINUE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_WHILE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_IF;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_CHOOSE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_WHEN;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_UNLESS;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_AND;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_OR;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_NOT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_EQp;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_g;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_ge;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_l;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_le;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_ii;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA___;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_COND;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_CASE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_MAKE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_NEW;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_MV_SETQ;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_FUNCTION_CODE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_CALL_METHOD_CODE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYS_INLINE_CALL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_THE_CODE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_INLINE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_IGNORE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_PRINT_STREAM;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_PRINT_NATIVE_STREAM;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_KEY_VALUE_LIST;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_i;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA__;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_o;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_s;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_eg;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_el;
extern Keyword* KWD_JAVA_TRANSLATE_UPPERCASE;
extern Keyword* KWD_JAVA_TRANSLATE_LOWERCASE;
extern Keyword* KWD_JAVA_TRANSLATE_CAPITALIZED;
extern Keyword* KWD_JAVA_TRANSLATE_CLEVER;
extern Keyword* KWD_JAVA_TRANSLATE_YES;
extern Keyword* KWD_JAVA_TRANSLATE_NO;
extern Keyword* KWD_JAVA_TRANSLATE_PRESERVE;
extern Keyword* KWD_JAVA_TRANSLATE_UPCASE;
extern Keyword* KWD_JAVA_TRANSLATE_TITLECASEX;
extern Keyword* KWD_JAVA_TRANSLATE_TITLECASE;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_LITERAL;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_STRING;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_MUTABLE_STRING;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_CODE;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_BOOLEAN;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_INTEGER;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_SHORT_INTEGER;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_UNSIGNED_SHORT_INTEGER;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_BYTE;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_OCTET;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_THIRY_TWO_BIT_VECTOR;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_FLOAT;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_DOUBLE;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_CHARACTER;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_LONG_INTEGER;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_SINGLE_FLOAT;
extern Keyword* KWD_JAVA_TRANSLATE_CAPITALIZE;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_MODULE;
extern Keyword* KWD_JAVA_TRANSLATE_MINIMIZE_JAVA_PREFIXES;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_CLASS_JAVA_NATIVE_TYPE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_ANY_VALUE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_OBJECT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_ABSTRACT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_BOOLEAN;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_BYTE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_CATCH;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_CHAR;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_CONST;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_DEFAULT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_DO;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_DOUBLE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_ELSE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_EXTENDS;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_FINAL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_FINALLY;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_FLOAT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_FOR;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_GOTO;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_IMPLEMENTS;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_IMPORT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_INSTANCEOF;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_INT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_INTERFACE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_LONG;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_NATIVE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_NEW;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_PACKAGE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_PRIVATE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_PROTECTED;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_PUBLIC;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SHORT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_STATIC;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SUPER;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SWITCH;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYNCHRONIZED;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_THROW;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_THROWS;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_TRANSIENT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_TRY;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_VOID;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_VOLATILE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_ASSERT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_ENUM;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CALL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_UNWIND_PROTECT;
extern Keyword* KWD_JAVA_TRANSLATE_JAVA;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_VERBATIM;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_SIGNAL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_FILL_IN_STACK_TRACE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_HANDLER_CASE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_CATCH;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION_CALL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_ASSIGN;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_VARIABLE_TYPE_SPECIFIER;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_SLOT_VALUE_SETTER;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_SLOT_VALUE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_PROGN;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_WITH_PROCESS_LOCK;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_NAMED_STATEMENT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_LOOP;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_FOREACH;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_NUMBER;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_NUMBER_WRAPPER;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_CAST;
extern Keyword* KWD_JAVA_TRANSLATE_WRAP_FUNCTION;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_AREF;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_MV_returnarray;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_RETURN;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_BREAK;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_CONTINUE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_IF;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_SYMBOL_ID;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_OTHERWISE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_CASE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_COND;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_WHILE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_WHEN;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_UNLESS;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_MAKE_ARRAY;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_NATIVE_OBJECT_POINTER;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_caller_MV_returnarray;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCTION_SIGNATURE;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_VOID;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_FUNCALL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_METHOD_CODE_CALL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_PACKAGE;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_ARGUMENT_LIST;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_METHOD_NATIVEp;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_METHOD_CONSTRUCTORp;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_DOUBLE_FLOAT;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_UNSIGNED_LONG_INTEGER;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_THIRTY_TWO_BIT_VECTOR;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_TICKTOCK;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_NATIVE_DATE_TIME;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_ANONYMOUS_ARRAY;
extern Keyword* KWD_JAVA_TRANSLATE_FUNCTION;
extern Keyword* KWD_JAVA_TRANSLATE_METHOD;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_PRINT_STREAM;
extern Keyword* KWD_JAVA_TRANSLATE_WARN;
extern Keyword* KWD_JAVA_TRANSLATE_ERROR;
extern Keyword* KWD_JAVA_TRANSLATE_CONTINUABLE_ERROR;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_STANDARD_ERROR;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_STANDARD_OUT;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_OBJECT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_LITERAL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_PRINT_NATIVE_STREAM;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_EOL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_EOL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_TRUE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_FALSE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_NULL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_GET_SYM;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_INTEGER_WRAPPER;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_SYMBOL;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_GET_KWD;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_GET_SGT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_DEFINEDp;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_NULLp;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_CONCATENATE;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_NTH;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_NTH_SETTER;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_AREF;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_AREF_SETTER;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_METHOD_SLOT;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_UNARY_OP;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_BINARY_OP;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_JAVA_TERNARY_OP;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_ARRAY;
extern Surrogate* SGT_JAVA_TRANSLATE_STELLA_NATIVE_VECTOR;
extern Symbol* SYM_JAVA_TRANSLATE_STELLA_STARTUP_JAVA_TRANSLATE;


} // end of namespace stella
