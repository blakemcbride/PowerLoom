//  -*- Mode: C++ -*-

// cpp-translate.hh

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
extern StringWrapper* oCPP_TRUE_STRING_WRAPPERo;
extern StringWrapper* oCPP_FALSE_STRING_WRAPPERo;
extern DECLARE_STELLA_SPECIAL(oDUMMYDECLARATIONSo, Cons* );
extern DECLARE_STELLA_SPECIAL(oCURRENTDUMMYINDEXo, int );
extern KeyValueList* oCPP_OPERATOR_TABLEo;
extern StringHashTable* oCPP_RESERVED_WORD_TABLEo;
extern DECLARE_STELLA_SPECIAL(oCPP_CURRENT_UNIT_MODULEo, Module* );
extern DECLARE_STELLA_SPECIAL(oCPPLOOPEXITo, Symbol* );
extern DECLARE_STELLA_SPECIAL(oCPPLOOPEXITACTIVEpo, boolean );
extern const char* oCPP_CHARACTER_SUBSTITUTION_TABLEo;
extern DECLARE_STELLA_SPECIAL(oCPP_NAME_QUALIFICATION_MODEo, Keyword* );
extern const char* oCPP_NAMESPACE_SEPARATORo;

// Function signatures:
Module* overloadedFunctionNameModule(Symbol* functionName, Surrogate* classType);
boolean cppUseGarbageCollectorP();
Cons* cppLookupOperatorTable(Symbol* operatoR);
StringWrapper* cppYieldRenamedReservedWord(Symbol* word);
StringHashTable* cppCreateReservedWordTable();
StringWrapper* cppLookupReservedWordTable(Symbol* word);
Cons* cppTranslateUnit(TranslationUnit* unit);
Cons* cppTranslateListOfTrees(Cons* trees);
Object* cppTranslateATree(Object* tree);
Cons* cppTranslateVerbatimTree(Cons* tree);
Cons* cppTranslateSpecialTree(Cons* tree);
Cons* cppTranslateInlineTree(Cons* tree);
Cons* tokenizeVerbatimMethodBody(Cons* tree);
Object* cppTranslateInlineCallTree(Cons* tree);
Cons* cppTranslatePrintNativeStream(Cons* tree);
Cons* cppTranslateDefprintUnit(TranslationUnit* unit);
Cons* cppTranslateSignal(Cons* tree);
Cons* cppTranslateHandlerCase(Cons* tree);
Cons* cppTranslateHandleException(Cons* tree);
Cons* cppTranslateUnwindProtect(Cons* tree);
Cons* cppTranslateCast(Cons* tree);
Cons* cppTranslateMvSetq(Cons* tree);
Cons* cppTranslateMvFunctionCall(Cons* functioncall, Cons* variables);
Cons* cppTranslateDefineGlobalVariableUnit(TranslationUnit* unit);
StringWrapper* cppTranslateGlobalVariableName(GlobalVariable* global);
StringWrapper* cppTranslateGlobalVariableAddress(GlobalVariable* global);
boolean symbolCaseP(Object* keyform);
Cons* cppYieldSymbolIdForm(int symbolid);
Cons* cppTranslateCondition(Cons* condition, boolean symbolcasep);
Cons* cppTranslateCaseTree(Cons* tree);
Cons* cppTranslateCondTree(Cons* tree);
Cons* cppTranslateLoop(Cons* tree);
Cons* cppTranslateWhile(Cons* tree);
Cons* cppTranslateProgn(Cons* tree);
Cons* cppTranslateWithProcessLock(Cons* tree);
Cons* cppTranslateBreak(Cons* tree);
Cons* cppTranslateContinue(Cons* tree);
Cons* cppTranslateIfTree(Cons* tree);
Cons* cppTranslateChooseTree(Cons* tree);
Cons* cppTranslateWhenTree(Cons* tree);
Cons* cppTranslateUnlessTree(Cons* tree);
Cons* cppTranslateForeachTree(Cons* tree);
Cons* cppYieldVaStartTree(Symbol* iteratorvar);
Cons* cppYieldVaEndTree(Symbol* iteratorvar);
Symbol* cppYieldVaIteratorHelperVariable(Symbol* iteratorvar);
Cons* cppYieldVaIteratorDeclarations(Symbol* iteratorvar);
Cons* cppTranslateArgumentListTree(Symbol* operatoR, Surrogate* owner, Object* argument);
Cons* cppTranslateTheCode(Cons* tree);
Cons* cppTranslateSysPointerToFunction(Cons* tree);
Cons* cppTranslateSysNew(Cons* tree);
boolean cppNonPointerTypeP(StandardObject* typespec);
boolean cppTypeWithoutInteriorPointersP(StandardObject* typespec);
Cons* cppTranslateNewArray(Cons* tree);
Cons* cppTranslateVoidSys(Cons* tree);
Cons* cppTranslateTypedSys(Cons* tree);
Object* cppTranslateBadSys(Cons* tree);
Cons* cppTranslateSysReferencedSlotValue(Cons* tree);
Cons* cppTranslateSysSlotValue(Cons* tree);
Cons* cppTranslateSysSlotValueSetter(Cons* tree);
Cons* cppTranslateMakeTree(Cons* tree);
Cons* cppTranslateStartupTimeProgn(Cons* tree);
boolean cppStreamIsStandardOutputP(Object* tree);
Cons* cppTranslatePrintStream(Cons* tree);
Cons* cppTranslateSetqTree(Cons* tree);
Object* cppTranslateSysSetDefault(Cons* tree);
Cons* cppTranslateNull();
Cons* cppTranslateLetTree(Cons* tree);
StringWrapper* cppTranslateTypeSpec(StandardObject* typespec);
StringWrapper* cppTranslateAndPointerizeTypeSpec(StandardObject* typespec);
StringWrapper* cppTranslateAndReferencizeTypeSpec(StandardObject* typespec);
StringWrapper* cppTranslateArrayType(ParametricTypeSpecifier* arraytype);
boolean cppTranslatedArrayTypeP(Object* translatedtype);
const char* cppGenerateArrayTypedEntity(const char* entity, const char* translatedarraytype);
boolean cppNativePointerTypeP(const char* nativetype);
const char* cppUnpointerizeNativeType(const char* nativetype);
const char* cppCreateCharacterSubstitutionTable();
const char* replaceFirstCharacterWithString(const char* string, const char* newprefix);
const char* cppSubstituteForbiddenCharacters(const char* name, Keyword* caseconvention);
const char* cppChangeCase(GeneralizedSymbol* symbol, Keyword* caseconvention);
const char* helpCppChangeCase(GeneralizedSymbol* symbol, Keyword* caseconvention);
const char* cppYieldNamespacePrefixFromModule(Module* module);
const char* cppYieldNamespacePrefix(GeneralizedSymbol* symbol);
Keyword* cppNameQualificationMode();
boolean cppQualifyNameP(GeneralizedSymbol* namesymbol);
const char* cppYieldQualifiedName(const char* translatedname, GeneralizedSymbol* sourcesymbol);
Symbol* cppFixupNameSymbol(Symbol* namesymbol, Module* homemodule);
StringWrapper* cppTranslateName(Symbol* namesymbol);
StringWrapper* cppTranslateGlobalName(Symbol* namesymbol);
StringWrapper* cppTranslateClassParameterName(Symbol* namesymbol);
StringWrapper* cppTranslateReturnParameterName(Symbol* namesymbol, int parameternumber);
StringWrapper* cppTranslateSymbolConstantName(GeneralizedSymbol* symbol);
StringWrapper* cppTranslateSymbolConstantId(GeneralizedSymbol* symbol);
StringWrapper* cppTranslateSymbolName(Symbol* symbol);
StringWrapper* cppTranslateSymbolId(Symbol* symbol);
StringWrapper* cppTranslateSurrogateName(Surrogate* surrogate);
StringWrapper* cppTranslateSurrogateId(Surrogate* surrogate);
StringWrapper* cppTranslateKeywordName(Keyword* keyword);
StringWrapper* cppTranslateKeywordId(Keyword* keyword);
StringWrapper* cppTranslateClassTypename(GeneralizedSymbol* namesymbol);
StringWrapper* cppTranslateClassName(GeneralizedSymbol* namesymbol);
boolean cppReferenceTypeP(StandardObject* typespec);
StringWrapper* cppReferencizeType(StandardObject* typespec);
Object* cppTranslateFunctionParameter(Symbol* name, StandardObject* type, MethodSlot* method);
Cons* cppTranslateReturnParameter(int parameternumber, StandardObject* parametertype);
Cons* cppTranslateFunctionParameters(MethodSlot* method);
boolean slotReaderFromNameP(Symbol* methodname, StandardObject* methodowner);
boolean slotReaderP(MethodSlot* method);
StringWrapper* cppTranslateConstructorName(MethodSlot* constructor);
StringWrapper* cppTranslateFunctionNameFromName(Symbol* functionname);
StringWrapper* cppTranslateFunctionName(MethodSlot* function, boolean qualifyP);
StringWrapper* cppTranslateMethodNameFromName(Symbol* methodname, StandardObject* methodowner);
StringWrapper* cppTranslateMethodName(MethodSlot* method, boolean qualifyP);
Cons* deleteQuotedNullStatements(Cons* trees);
boolean cppMethodObjectIsFunctionP(MethodSlot* method);
boolean cppMethodObjectIsOverloadedFunctionP(MethodSlot* method);
Cons* wrapMethodBodyWithCppAuxiliaryDeclarations(Cons* methodbody, Cons* declarations);
Cons* cppTranslateDefineMethodUnit(TranslationUnit* unit);
Cons* cppTranslateReturnTree(Cons* tree);
Cons* cppTranslateActualParameters(Cons* tree);
Cons* cppTranslateVariableLengthActuals(Cons* actuals, MethodSlot* method);
Cons* cppTranslateCallMethodSetter(Cons* tree);
Symbol* cppCreateOverloadedFunctionName(Symbol* functionname, Surrogate* classtype);
boolean cppPossiblyOverloadedFunctionNameP(Symbol* functionname);
Cons* cppTranslateMethodCall(Cons* tree, boolean referencedP);
Cons* cppTranslateSuperMethodCall(Cons* tree);
Cons* cppTranslateNormalMethodCall(Symbol* methodname, Surrogate* owner, Cons* arguments, boolean referencedP);
Cons* cppTranslateDefinedPMethodCall(Surrogate* argumenttype, Object* argument, boolean nullP);
Cons* cppTranslateNthMethodCall(Symbol* operatoR, Surrogate* owner, Cons* arguments);
Cons* cppTranslateArefMethodCall(Symbol* operatoR, Surrogate* owner, Cons* arguments);
Cons* cppTranslateFunctionSignature(MethodSlot* function);
Cons* cppTranslateCodeSignature(Cons* signature);
Cons* cppTranslateMethodCodeSignature(Cons* signature);
Cons* cppTranslateCallFunctionCode(Cons* tree);
Cons* cppTranslateCallMethodCode(Cons* tree);
Cons* getLastNElements(Cons* list, int n);
Cons* cppYieldUnusedDummyArgs(MethodSlot* method, Cons* args);
Cons* cppTranslateFunctionCall(Cons* tree, MethodSlot* method);
Cons* cppTranslateOperatorTree(Cons* tree);
Cons* cppTranslateOperatorCall(Cons* operatornames, Cons* arguments, int arity);
Cons* cppTranslateHardcodedSymbolReference(Symbol* operatoR, int offset);
void helpStartupCppTranslate1();
void helpStartupCppTranslate2();
void helpStartupCppTranslate3();
void helpStartupCppTranslate4();
void helpStartupCppTranslate5();
void helpStartupCppTranslate6();
void helpStartupCppTranslate7();
void helpStartupCppTranslate8();
void startupCppTranslate();

// Auxiliary global declarations:
extern Keyword* KWD_CPP_TRANSLATE_USE_CPP_GARBAGE_COLLECTOR;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_KEY_VALUE_LIST;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_ii;
extern Symbol* SYM_CPP_TRANSLATE_STELLA___;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_i;
extern Symbol* SYM_CPP_TRANSLATE_STELLA__;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_o;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_s;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_EQp;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_xe;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_g;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_ge;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_eg;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_l;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_el;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_le;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_AND;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_OR;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_NOT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CHOOSE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_ASM;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_ASSERT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_AUTO;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_BREAK;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CASE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CATCH;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CHAR;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CLASS;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CONST;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CONTINUE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_DEFAULT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_DELETE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_DO;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_DOUBLE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_ELSE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_ENUM;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_EXTERN;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_FLOAT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_FOR;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_FRIEND;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_GOTO;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_IF;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_INLINE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_INT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_LONG;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_NAMESPACE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_NEW;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_OPERATOR;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_PRIVATE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_PROTECTED;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_PUBLIC;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_REGISTER;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_RETURN;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SHORT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SIGNED;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SIZEOF;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_STATIC;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_STRUCT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SWITCH;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_TEMPLATE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_THROW;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_TRY;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_TYPEDEF;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_TYPEID;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_UNION;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_UNSIGNED;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_VIRTUAL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_VOID;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_VOLATILE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_WHILE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_TYPENAME;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_GLOBAL_VARIABLE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_TYPE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_METHOD;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_MACRO;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_PRINT_METHOD;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_STARTUP_TIME_PROGN;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_VERBATIM;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_CONS;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SPECIAL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_UNWIND_PROTECT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_SIGNAL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_HANDLER_CASE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_HANDLE_EXCEPTION;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_VOID_SYS;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_BAD_SYS;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_TYPED_SYS;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SETQ;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_SET_DEFAULT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_SLOT_VALUE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_REFERENCED_SLOT_VALUE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_SLOT_VALUE_SETTER;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_CALL_METHOD;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_REFERENCED_CALL_METHOD;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_CALL_SUPER_METHOD;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_CALL_FUNCTION;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_PROGN;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_WITH_PROCESS_LOCK;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_LOOP;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_FOREACH;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_LET;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CAST;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SAFE_CAST;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_WHEN;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_UNLESS;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_COND;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_MAKE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_NEW;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_MV_SETQ;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_CALL_FUNCTION_CODE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_CALL_METHOD_CODE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_INLINE_CALL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_THE_CODE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYS_POINTER_TO_FUNCTION;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_IGNORE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_PRINT_STREAM;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_PRINT_NATIVE_STREAM;
extern Keyword* KWD_CPP_TRANSLATE_CPP;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_VERBATIM;
extern Keyword* KWD_CPP_TRANSLATE_UNBIND_WITH_DESTRUCTORS;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_CALL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_IDENT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_ACTUALS;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_BLOCK;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_STATEMENTS;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_COMMENT;
extern Keyword* KWD_CPP_TRANSLATE_DIGIT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_PRINT_NATIVE_STREAM;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_DEFPRINT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_RETURN;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_STREAM;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_SIGNAL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_DEREFERENCE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_HANDLER_CASE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_CATCH;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_TYPE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_LOCAL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_UNWIND_PROTECT;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_NUMBER;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_NUMBER_WRAPPER;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_CAST;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_ASSIGN;
extern Keyword* KWD_CPP_TRANSLATE_UNBOUND_SPECIAL_VARIABLE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_SPECIAL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_GLOBAL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_SYMBOL_ID;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_OTHERWISE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_CASE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_PROGN;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_COND;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_BREAK;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_LOOP;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_GOTO_LABEL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_WHILE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_WITH_PROCESS_LOCK;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_GOTO;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_CONTINUE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_IF;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_WHEN;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_UNLESS;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_ARGUMENT_LIST_ITERATOR;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_FOREACH;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_VA_START;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_VA_END;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_INTEGER;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_ALLOCATE_ITERATOR;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_LENGTH;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_NEXTp;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_ARGUMENT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_BINARY_OP;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_UNARY_OP;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_LITERAL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_VA_ARG;
extern Keyword* KWD_CPP_TRANSLATE_FUNCTION;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_POINTER;
extern Keyword* KWD_CPP_TRANSLATE_METHOD;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_POINTER;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_TRUE;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_SHORT_INTEGER;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_LONG_INTEGER;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_UNSIGNED_LONG_INTEGER;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_FLOAT;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_SINGLE_FLOAT;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_DOUBLE_FLOAT;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_CHARACTER;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_BYTE;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_OCTET;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_ANY_VALUE;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_NATIVE_EXCEPTION;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_ARRAY_REFERENCE;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_VOID;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_REFERENCED_SLOT_VALUE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_SLOT_VALUE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_SLOT_VALUE_SETTER;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CLASS_CPP_NATIVE_TYPE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_MAKE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_STARTUP_TIME_PROGN;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_PRINT_STREAM;
extern Keyword* KWD_CPP_TRANSLATE_WARN;
extern Keyword* KWD_CPP_TRANSLATE_ERROR;
extern Keyword* KWD_CPP_TRANSLATE_CONTINUABLE_ERROR;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_STANDARD_ERROR;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_STANDARD_OUT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_EOL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_SYMBOL;
extern Keyword* KWD_CPP_TRANSLATE_CPP_STANDALONE;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_UNKNOWN;
extern Keyword* KWD_CPP_TRANSLATE_UPPERCASE;
extern Keyword* KWD_CPP_TRANSLATE_LOWERCASE;
extern Keyword* KWD_CPP_TRANSLATE_CAPITALIZED;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_F_CPP_CHANGE_CASE_MEMO_TABLE_000;
extern Keyword* KWD_CPP_TRANSLATE_CLEVER;
extern Keyword* KWD_CPP_TRANSLATE_YES;
extern Keyword* KWD_CPP_TRANSLATE_NO;
extern Keyword* KWD_CPP_TRANSLATE_PRESERVE;
extern Keyword* KWD_CPP_TRANSLATE_UPCASE;
extern Keyword* KWD_CPP_TRANSLATE_TITLECASEX;
extern Keyword* KWD_CPP_TRANSLATE_TITLECASE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_MODULE_CPP_PACKAGE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_NULL;
extern Keyword* KWD_CPP_TRANSLATE_FULL;
extern Keyword* KWD_CPP_TRANSLATE_NEVER;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_FALSE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp;
extern Symbol* SYM_CPP_TRANSLATE_STELLA__RETURN;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_VAR_ARGS;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_STORAGE_SLOT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_METHOD_NATIVEp;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_LITERAL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_THIS;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_DOCUMENTATION;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_METHOD;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_EXTERN_C;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_SETTER_CALL;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_OBJECT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_DEFINEDp;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_NULLp;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_NTH;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_NTH_SETTER;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_AREF;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_AREF_SETTER;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_ARGUMENT_LIST;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_REFERENCED_METHOD_CALL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_CALL;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_BOOLEAN;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_STRING;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_MUTABLE_STRING;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_NATIVE_VECTOR;
extern Surrogate* SGT_CPP_TRANSLATE_STELLA_ARRAY;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_FUNCTION_SIGNATURE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_SIGNATURE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_FUNCALL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_METHOD_CODE_CALL;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_DUMMY;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_GET_SYM;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_GET_KWD;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_GET_SGT;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_CPP_TERNARY_OP;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_STARTUP_CPP_TRANSLATE;
extern Symbol* SYM_CPP_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
