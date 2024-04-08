//  -*- Mode: C++ -*-

// cl-translate.hh

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
extern VerbatimStringWrapper* oCL_TRUE_STRING_WRAPPERo;
extern VerbatimStringWrapper* oCL_FALSE_STRING_WRAPPERo;
extern KeyValueList* oCL_OPERATOR_TABLEo;
extern DECLARE_STELLA_SPECIAL(oNEEDEXPLICITRETURNpo, boolean );

// Function signatures:
Symbol* destructureCallTree(Cons* tree, Surrogate*& _Return1, Cons*& _Return2);
boolean useClConsesP();
boolean useDefconsmethodP(MethodSlot* method);
boolean useClStructsP();
boolean useVectorStructsP();
Cons* clTranslateListOfTrees(Cons* trees);
Cons* clTranslateVoidSys(Cons* tree);
Object* clTranslateTypedSys(Cons* tree);
Object* clTranslateBadSys(Cons* tree);
Object* clTranslateATree(Object* tree);
Object* helpClTranslateATree(Object* tree);
Object* clTranslateGlobalSymbol(Symbol* symbol);
const char* yieldReadableSymbolName(Module* symbolmodule, const char* symbolname, boolean localP);
Object* yieldGlobalLispSymbol(Module* symbolmodule, const char* symbolname);
Object* clTranslateLocalSymbol(Symbol* symbol);
Cons* clTranslateSetqTree(Cons* tree);
Object* yieldStructSlotAccessorName(Surrogate* classtype, Symbol* slotname);
Object* yieldClosSlotAccessorName(Symbol* slotname);
Cons* yieldSlotValueReaderTree(Symbol* slotname, Object* objectref, Surrogate* objecttype);
Cons* yieldSlotValueWriterTree(Symbol* slotname, Object* objectref, Surrogate* objecttype, Object* valueref);
Symbol* trueSlotName(Symbol* slotname, Surrogate* type);
Cons* clTranslateFixedSlotValueTree(Cons* tree);
Cons* clTranslateFixedSlotValueSetterTree(Cons* tree);
Object* clTranslateCallMethodTree(Cons* tree);
Object* clTranslateCallSuperMethodTree(Cons* tree);
Symbol* methodCallTypeForVectorStructs(Symbol* slotname, Surrogate* owner, boolean functionP);
Cons* clTranslateNormalCallMethodTree(Symbol* operatoR, Surrogate* owner, Cons* arguments);
Cons* clTranslateNthTree(Cons* tree);
Cons* clTranslateArefTree(Cons* tree);
Object* clTranslateArgumentListTree(Cons* tree);
boolean duplicateCursorVariableP(Symbol* variable, Cons* iteratorbindings);
Cons* clTranslateForeachTree(Cons* tree);
Cons* maybeWrapWithContinueLabel(Cons* translatedloopbody);
Cons* clTranslateLetTree(Cons* tree, boolean specialP);
Cons* clTranslateSpecialTree(Cons* tree);
Cons* clTranslateStartupTimePrognTree(Cons* tree);
Cons* clTranslateUnwindProtectTree(Cons* tree);
Cons* clTranslateSignalTree(Cons* tree);
Cons* clTranslateHandlerCaseTree(Cons* tree);
Cons* clTranslateHandleExceptionTree(Cons* tree);
Object* cast(Object* value, Surrogate* type);
NumberWrapper* coerceNumericConstant(NumberWrapper* constant, Surrogate* type);
Object* clTranslateCastTree(Cons* tree);
Object* clTranslateReturnTree(Cons* tree);
Object* clTranslateBooleanTest(Object* tree, boolean invertP);
Object* clTranslatePlainBooleanTest(Object* tree, boolean invertP);
Cons* clTranslateWhileTree(Cons* tree);
Cons* clTranslateConditionalTree(Cons* tree);
Cons* clTranslateCondTree(Cons* tree);
Cons* clTranslateCaseTree(Cons* tree);
Cons* clTranslateBooleanTree(Cons* tree);
Object* clTranslateClassName(Class* clasS);
Object* yieldStructConstructorName(Class* clasS);
Cons* clTranslateMakeTree(Cons* tree);
Cons* clTranslateNewTree(Cons* tree);
Cons* clTranslateNewArrayTree(Cons* tree);
Cons* clTranslateOperatorTree(Cons* tree);
Cons* yieldFormatArguments(Cons* tree);
Cons* yieldPrintTree(Cons* tree);
Cons* clTranslatePrintStreamTree(Cons* tree);
Cons* clTranslateCallFunctionCodeTree(Cons* tree);
Object* clTranslateInlineCallTree(Cons* tree);
Object* clTranslateVerbatimBodySymbols(Object* body, List* parameters);
Cons* clTranslateTheCodeTree(Cons* tree);
Object* clTranslateVerbatimTree(Cons* tree);
Cons* clTranslateInlineTree(Cons* tree);
boolean generateClTypeDeclarationsP();
Object* lookupClTypeFromStellaType(StandardObject* type);
Object* clYieldTypedExpressionTree(Object* tree, StandardObject* type);
Cons* clYieldMethodParameterTypeDeclarationTrees(MethodSlot* method);
Cons* clYieldLetVariableTypeDeclarationTrees(Cons* bindingstree);
Cons* clYieldGlobalVariableTypeDeclarationTree(GlobalVariable* global);
Cons* clYieldMethodArglistTypeDeclarations(MethodSlot* method);
Object* clYieldMethodReturnTypeDeclaration(MethodSlot* method);
Cons* clYieldMethodTypeDeclarationTree(MethodSlot* method);
Cons* clYieldDeclareTree(Cons* declarations, boolean includeTypeChecksP);
Object* clConditionalizeTypeDeclarationTree(Object* declaration);
Object* clTranslateUnit(TranslationUnit* unit);
Cons* clTranslateMethodParameters(MethodSlot* method);
Symbol* clMethodDefinitionOperator(MethodSlot* method);
Cons* clTranslateDefineMethodUnit(TranslationUnit* unit);
Cons* yieldClosSlotTypeTree(StorageSlot* slot);
Cons* yieldClosSlotTree(StorageSlot* slot);
Cons* yieldClosClassTree(Class* clasS);
List* computeClStructSlots(Class* clasS);
List* clStructSlots(Class* clasS);
int clStructSlotOffset(Symbol* slotname, Surrogate* classtype);
Cons* yieldStructSlotTree(StorageSlot* slot);
Cons* yieldStructSlotTrees(Class* clasS);
Cons* yieldStructTree(Class* clasS);
Object* yieldVectorStructName(Class* clasS);
Cons* yieldVectorStructTree(Class* clasS);
Cons* yieldConditionTree(Class* clasS);
boolean clAlwaysTranslateToClosClassP(Class* clasS);
Cons* clTranslateDefineNativeClassUnit(TranslationUnit* unit);
Cons* clTranslateDefineGlobalVariableUnit(TranslationUnit* unit);
Cons* clTranslateDefprintUnit(TranslationUnit* unit);
void helpStartupClTranslate1();
void helpStartupClTranslate2();
void helpStartupClTranslate3();
void helpStartupClTranslate4();
void startupClTranslate();

// Auxiliary global declarations:
extern Symbol* SYM_CL_TRANSLATE_STELLA_SYS_CALL_FUNCTION;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SYS_CALL_METHOD;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_KEY_VALUE_LIST;
extern Symbol* SYM_CL_TRANSLATE_STELLA_i;
extern Symbol* SYM_CL_TRANSLATE_STELLA__;
extern Symbol* SYM_CL_TRANSLATE_STELLA_o;
extern Symbol* SYM_CL_TRANSLATE_STELLA_s;
extern Symbol* SYM_CL_TRANSLATE_STELLA_EQp;
extern Symbol* SYM_CL_TRANSLATE_STELLA_l;
extern Symbol* SYM_CL_TRANSLATE_STELLA_le;
extern Symbol* SYM_CL_TRANSLATE_STELLA_ge;
extern Symbol* SYM_CL_TRANSLATE_STELLA_g;
extern Symbol* SYM_CL_TRANSLATE_STELLA_e;
extern Symbol* SYM_CL_TRANSLATE_STELLA_xe;
extern Keyword* KWD_CL_TRANSLATE_USE_COMMON_LISP_CONSES;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_CONS;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_STANDARD_OBJECT;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_OBJECT;
extern Keyword* KWD_CL_TRANSLATE_USE_COMMON_LISP_STRUCTS;
extern Keyword* KWD_CL_TRANSLATE_USE_COMMON_LISP_VECTOR_STRUCTS;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_VOID;
extern Symbol* SYM_CL_TRANSLATE_STELLA_VOID_SYS;
extern Symbol* SYM_CL_TRANSLATE_STELLA_TYPED_SYS;
extern Symbol* SYM_CL_TRANSLATE_STELLA_BAD_SYS;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SETQ;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SYS_SLOT_VALUE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SYS_SLOT_VALUE_SETTER;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SYS_CALL_SUPER_METHOD;
extern Symbol* SYM_CL_TRANSLATE_STELLA_PROGN;
extern Symbol* SYM_CL_TRANSLATE_STELLA_WITH_PROCESS_LOCK;
extern Symbol* SYM_CL_TRANSLATE_STELLA_LOOP;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SYS_FOREACH;
extern Symbol* SYM_CL_TRANSLATE_STELLA_LET;
extern Symbol* SYM_CL_TRANSLATE_STELLA_STARTUP_TIME_PROGN;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SPECIAL;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SYS_UNWIND_PROTECT;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SYS_HANDLER_CASE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SYS_HANDLE_EXCEPTION;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SYS_SIGNAL;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CAST;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SAFE_CAST;
extern Symbol* SYM_CL_TRANSLATE_STELLA_RETURN;
extern Symbol* SYM_CL_TRANSLATE_STELLA_BREAK;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CONTINUE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_WHILE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_IF;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CHOOSE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_WHEN;
extern Symbol* SYM_CL_TRANSLATE_STELLA_UNLESS;
extern Symbol* SYM_CL_TRANSLATE_STELLA_AND;
extern Symbol* SYM_CL_TRANSLATE_STELLA_OR;
extern Symbol* SYM_CL_TRANSLATE_STELLA_NOT;
extern Symbol* SYM_CL_TRANSLATE_STELLA_COND;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CASE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_MAKE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SYS_NEW;
extern Symbol* SYM_CL_TRANSLATE_STELLA_MV_SETQ;
extern Symbol* SYM_CL_TRANSLATE_STELLA_QUOTE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SYS_CALL_FUNCTION_CODE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SYS_CALL_METHOD_CODE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SYS_INLINE_CALL;
extern Symbol* SYM_CL_TRANSLATE_STELLA_THE_CODE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_PRINT_STREAM;
extern Symbol* SYM_CL_TRANSLATE_STELLA_PRINT_NATIVE_STREAM;
extern Symbol* SYM_CL_TRANSLATE_STELLA_VERBATIM;
extern Symbol* SYM_CL_TRANSLATE_STELLA_INLINE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_IGNORE;
extern Keyword* KWD_CL_TRANSLATE_CONTINUE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_TRUE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_FALSE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_GET_KWD;
extern Symbol* SYM_CL_TRANSLATE_STELLA_GET_SGT;
extern Symbol* SYM_CL_TRANSLATE_STELLA_MODULE_LISP_PACKAGE;
extern Keyword* KWD_CL_TRANSLATE_UNESCAPED;
extern Keyword* KWD_CL_TRANSLATE_ESCAPED;
extern Keyword* KWD_CL_TRANSLATE_COMPLEX_ESCAPED;
extern Symbol* SYM_CL_TRANSLATE_STELLA_VALUE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_REST;
extern Symbol* SYM_CL_TRANSLATE_STELLA_rrVALUE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_rrREST;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_SVAL;
extern Symbol* SYM_CL_TRANSLATE_STELLA_NTH;
extern Symbol* SYM_CL_TRANSLATE_STELLA_NTH_SETTER;
extern Symbol* SYM_CL_TRANSLATE_STELLA_AREF;
extern Symbol* SYM_CL_TRANSLATE_STELLA_AREF_SETTER;
extern Symbol* SYM_CL_TRANSLATE_STELLA_NULLp;
extern Symbol* SYM_CL_TRANSLATE_STELLA_DEFINEDp;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_ARGUMENT_LIST;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_ARGUMENT_LIST_ITERATOR;
extern Symbol* SYM_CL_TRANSLATE_STELLA_NORMAL_CALL;
extern Symbol* SYM_CL_TRANSLATE_STELLA_NON_OBJECT_METHOD;
extern Symbol* SYM_CL_TRANSLATE_STELLA_PRINT_OBJECT;
extern Symbol* SYM_CL_TRANSLATE_STELLA_OBJECT_METHOD;
extern Keyword* KWD_CL_TRANSLATE_COMMON_LISP;
extern Keyword* KWD_CL_TRANSLATE_FUNCTION;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_CALL;
extern Symbol* SYM_CL_TRANSLATE_STELLA_NULL;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_STRING;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_MUTABLE_STRING;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_NATIVE_VECTOR;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_ARRAY;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_INTEGER;
extern Symbol* SYM_CL_TRANSLATE_STELLA_ALLOCATE_ITERATOR;
extern Symbol* SYM_CL_TRANSLATE_STELLA_LENGTH;
extern Symbol* SYM_CL_TRANSLATE_STELLA_NEXTp;
extern Symbol* SYM_CL_TRANSLATE_STELLA_ARGUMENT;
extern Symbol* SYM_CL_TRANSLATE_STELLA_DO;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_FLOAT;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_LONG_INTEGER;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_NUMBER;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_NUMBER_WRAPPER;
extern Symbol* SYM_CL_TRANSLATE_STELLA_PRIMARY_TYPE;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_LITERAL;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_BOOLEAN;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_SECOND_CLASS_OBJECT;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_CODE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_NULL_ARRAYp;
extern Symbol* SYM_CL_TRANSLATE_STELLA_OTHERWISE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CLASS_CL_NATIVE_TYPE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_oCONDITION_MESSAGE_KEYWORDo;
extern Symbol* SYM_CL_TRANSLATE_STELLA_REPLACE_SUBSTRINGS;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_MAKE;
extern Keyword* KWD_CL_TRANSLATE_INITIAL_ELEMENT;
extern Symbol* SYM_CL_TRANSLATE_STELLA_rrPRINT_STREAM;
extern Keyword* KWD_CL_TRANSLATE_WARN;
extern Keyword* KWD_CL_TRANSLATE_ERROR;
extern Keyword* KWD_CL_TRANSLATE_CONTINUABLE_ERROR;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_METHOD_CODE_CALL;
extern Surrogate* SGT_CL_TRANSLATE_STELLA_SHORT_INTEGER;
extern Symbol* SYM_CL_TRANSLATE_STELLA_GLOBAL_VARIABLE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CLASS;
extern Symbol* SYM_CL_TRANSLATE_STELLA_METHOD;
extern Symbol* SYM_CL_TRANSLATE_STELLA_MACRO;
extern Symbol* SYM_CL_TRANSLATE_STELLA_PRINT_METHOD;
extern Symbol* SYM_CL_TRANSLATE_STELLA_TYPE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_SELF;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_DUMMY;
extern Symbol* SYM_CL_TRANSLATE_STELLA_METHOD_VARIABLE_ARGUMENTSp;
extern Symbol* SYM_CL_TRANSLATE_STELLA_rrDEFCONSMETHOD;
extern Symbol* SYM_CL_TRANSLATE_STELLA_rrDEFINTEGERMETHOD;
extern Symbol* SYM_CL_TRANSLATE_STELLA_DOCUMENTATION;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SELF;
extern Symbol* SYM_CL_TRANSLATE_STELLA_oCLSYS_SELFo;
extern Keyword* KWD_CL_TRANSLATE_VOID;
extern Symbol* SYM_CL_TRANSLATE_STELLA_SLOT_AUXILIARYp;
extern Keyword* KWD_CL_TRANSLATE_INITFORM;
extern Keyword* KWD_CL_TRANSLATE_TYPE;
extern Keyword* KWD_CL_TRANSLATE_EMBEDDED;
extern Keyword* KWD_CL_TRANSLATE_INSTANCE;
extern Keyword* KWD_CL_TRANSLATE_ALLOCATION;
extern Keyword* KWD_CL_TRANSLATE_DOCUMENTATION;
extern Keyword* KWD_CL_TRANSLATE_ACCESSOR;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_ROOT_OBJECT;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CLASS_CL_STRUCT_SLOTS;
extern Symbol* SYM_CL_TRANSLATE_STELLA_CLSYS_ROOT_STRUCT;
extern Keyword* KWD_CL_TRANSLATE_CONC_NAME;
extern Keyword* KWD_CL_TRANSLATE_CONSTRUCTOR;
extern Keyword* KWD_CL_TRANSLATE_COPIER;
extern Keyword* KWD_CL_TRANSLATE_PREDICATE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_;
extern Keyword* KWD_CL_TRANSLATE_INCLUDE;
extern Keyword* KWD_CL_TRANSLATE_UNBOUND_SPECIAL_VARIABLE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_STREAM;
extern Symbol* SYM_CL_TRANSLATE_STELLA_STARTUP_CL_TRANSLATE;
extern Symbol* SYM_CL_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
