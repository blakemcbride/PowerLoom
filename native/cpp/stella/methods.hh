//  -*- Mode: C++ -*-

// methods.hh

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
extern int oMAXIMUM_STRING_CONSTANT_SIZEo;
extern HashTable* oFUNCTION_LOOKUP_TABLEo;
extern HashTable* oGLOBAL_VARIABLE_LOOKUP_TABLEo;

// Function signatures:
Object* apply(cpp_function_code code, Cons* arguments);
Object* applyMethod(cpp_method_code code, Cons* arguments);
int applyIntegerMethod(cpp_method_code code, Cons* arguments);
long long int applyLongIntegerMethod(cpp_method_code code, Cons* arguments);
const char* applyStringMethod(cpp_method_code code, Cons* arguments);
boolean applyBooleanMethod(cpp_method_code code, Cons* arguments);
double applyFloatMethod(cpp_method_code code, Cons* arguments);
boolean definedTypeP(Surrogate* type);
StandardObject* realTypeSpecifier(Surrogate* type);
Surrogate* canonicalType(Surrogate* type);
ParametricTypeSpecifier* yieldParametricTypeSpecifier(Cons* typespectree);
List* parseArrayDimensionsSpec(Object* dimensionsspec);
Cons* yieldArrayDimensionsTree(ParametricTypeSpecifier* arraytype);
boolean arrayTypeSpecifierP(StandardObject* typespec);
int arrayTypeRank(ParametricTypeSpecifier* arraytype);
List* arrayTypeDimensions(ParametricTypeSpecifier* arraytype);
boolean indefiniteArrayTypeP(ParametricTypeSpecifier* arraytype);
AnchoredTypeSpecifier* yieldAnchoredTypeSpecifier(Cons* typespectree);
void incorporateInputParameters(MethodSlot* method, Cons* parameters);
void incorporateFirstInputParameter(MethodSlot* method);
MethodSlot* defineStellaMethodSlot(Symbol* inputname, Cons* returntypes, boolean functionP, Cons* inputparameters, KeywordKeyValueList* options);
MethodSlot* attachMethodSlotToOwner(MethodSlot* newmethod);
Object* yieldStringConstantTree(const char* string);
boolean defineFunctionObjectEagerlyP(MethodSlot* function);
Cons* yieldDefineStellaMethodObject(MethodSlot* method, MethodSlot* codemethod, MethodSlot* wrappermethod);
Cons* yieldClassParameterTypes(Class* clasS);
boolean optimisticSubtypeOfP(Surrogate* subtype, Surrogate* supertype);
void warnOfParameterMismatch(ParametricTypeSpecifier* self, const char* message);
Surrogate* validateTypeSpecifier(StandardObject* self, Class* anchorclass, boolean skipanchoredtypeP);
Cons* synthesizeMethodBody(MethodSlot* method);
void undefineExternalSlots(Symbol* name);
void destroyExternalSlot(Slot* self);
void destroyMethod(MethodSlot* self);
Surrogate* typeSpecToBaseType(StandardObject* self);
StandardObject* baseTypeToTypeSpec(StandardObject* self);
Class* typeSpecToClass(StandardObject* self);
boolean compatibleParameterTypesP(StandardObject* subtype, StandardObject* supertype);
boolean subTypeSpecOfP(StandardObject* subtype, StandardObject* supertype);
boolean voidP(StandardObject* type);
StandardObject* extractParameterType(StandardObject* self, Symbol* parameter, boolean& _Return1);
StandardObject* computeAnchoredTypeSpec(StandardObject* ownertype, AnchoredTypeSpecifier* reltype);
StandardObject* computeRelativeTypeSpec(StandardObject* relativetype, StandardObject* ownertype);
Object* yieldTypeSpecTree(StandardObject* self);
MethodSlot* attachFunction(MethodSlot* newfunction);
MethodSlot* lookupFunction(Symbol* functionsymbol);
MethodSlot* lookupFunctionByName(const char* name);
MethodSlot* lookupFunctionByQualifiedName(const char* qualifiedname);
MethodSlot* lookupFunctionOrStellaFunction(Symbol* functionsymbol);
Module* lookupFunctionHomeModule(Symbol* functionsymbol);
void undefineFunction(Symbol* name);
void destroyFunction(MethodSlot* function);
boolean undefineConflictingDefinitionsP(MethodSlot* newslot);
void defineFunctionObject(const char* name, const char* definition, cpp_function_code code, cpp_function_code wrappercode);
GlobalVariable* internGlobalVariable(GlobalVariable* global);
GlobalVariable* stringLookupGlobalVariable(const char* self);
GlobalVariable* lookupGlobalVariableByName(const char* name);
GlobalVariable* lookupGlobalVariableByQualifiedName(const char* qualifiedname);
StandardObject* globalVariableTypeSpec(GlobalVariable* global);
StandardObject* lookupGlobalVariableType(Symbol* name);
GlobalVariable* defineStellaGlobalVariableFromParseTree(Cons* tree, const char* stringifiedsource, Object*& _Return1);
void defineStellaGlobalVariableFromStringifiedSource(const char* stringifiedsource);
void defineGlobalVariableObject(const char* definition, void* nativeobject);
Module* recordVariableHomeModule(GlobalVariable* self);
void destroyGlobalVariable(GlobalVariable* variable);
void* getGlobalVariableNativeObject(GlobalVariable* variable);
Object* readNativeVariableValue(void* var, Surrogate* type);
void writeNativeVariableValue(void* var, Surrogate* type, Object* value);
Object* readGlobalVariableValue(GlobalVariable* variable);
void writeGlobalVariableValue(GlobalVariable* variable, Object* value);
Surrogate* defineStellaTypeFromParseTree(Cons* tree);
void defineStellaTypeFromStringifiedSource(const char* stringifiedsource);
void helpStartupMethods1();
void helpStartupMethods2();
void helpStartupMethods3();
void startupMethods();

// Auxiliary global declarations:
extern Surrogate* SGT_METHODS_STELLA_SURROGATE;
extern Surrogate* SGT_METHODS_STELLA_PARAMETRIC_TYPE_SPECIFIER;
extern Surrogate* SGT_METHODS_STELLA_ANCHORED_TYPE_SPECIFIER;
extern Surrogate* SGT_METHODS_STELLA_OBJECT;
extern Surrogate* SGT_METHODS_STELLA_VOID;
extern Symbol* SYM_METHODS_STELLA_LIKE;
extern Symbol* SYM_METHODS_STELLA_SIZE;
extern Symbol* SYM_METHODS_STELLA_UNKNOWN;
extern Symbol* SYM_METHODS_STELLA_OF;
extern Symbol* SYM_METHODS_STELLA_NULL;
extern Surrogate* SGT_METHODS_STELLA_ARRAY;
extern Symbol* SYM_METHODS_STELLA_SELF;
extern Surrogate* SGT_METHODS_STELLA_CONS;
extern Symbol* SYM_METHODS_STELLA_IN;
extern Symbol* SYM_METHODS_STELLA_OUT;
extern Symbol* SYM_METHODS_STELLA_INOUT;
extern Symbol* SYM_METHODS_STELLA_METHOD_PARAMETER_DIRECTIONS;
extern Symbol* SYM_METHODS_STELLA_ARGUMENT_LIST;
extern Symbol* SYM_METHODS_STELLA_aREST;
extern Symbol* SYM_METHODS_STELLA_METHOD_VARIABLE_ARGUMENTSp;
extern Symbol* SYM_METHODS_STELLA_aBODY;
extern Symbol* SYM_METHODS_STELLA_METHOD_BODY_ARGUMENTp;
extern Surrogate* SGT_METHODS_STELLA_UNKNOWN;
extern Keyword* KWD_METHODS_TYPE;
extern Keyword* KWD_METHODS_RETURN_TYPES;
extern Symbol* SYM_METHODS_STELLA_SLOT_TYPE_SPECIFIER;
extern Keyword* KWD_METHODS_PUBLICp;
extern Keyword* KWD_METHODS_ABSTRACTp;
extern Keyword* KWD_METHODS_NATIVEp;
extern Symbol* SYM_METHODS_STELLA_METHOD_NATIVEp;
extern Keyword* KWD_METHODS_CONSTRUCTORp;
extern Symbol* SYM_METHODS_STELLA_METHOD_CONSTRUCTORp;
extern Keyword* KWD_METHODS_GLOBALLY_INLINEp;
extern Symbol* SYM_METHODS_STELLA_METHOD_GLOBALLY_INLINEp;
extern Keyword* KWD_METHODS_INLINE;
extern Symbol* SYM_METHODS_STELLA_METHOD_INLINED_FUNCTIONS;
extern Keyword* KWD_METHODS_AUXILIARYp;
extern Symbol* SYM_METHODS_STELLA_SLOT_AUXILIARYp;
extern Keyword* KWD_METHODS_DOCUMENTATION;
extern Symbol* SYM_METHODS_STELLA_DOCUMENTATION;
extern Keyword* KWD_METHODS_RETURNS;
extern Keyword* KWD_METHODS_STORAGE_SLOT;
extern Symbol* SYM_METHODS_STELLA_STORAGE_SLOT;
extern Keyword* KWD_METHODS_INHERITS_THROUGH;
extern Symbol* SYM_METHODS_STELLA_METHOD_INHERITS_THROUGH;
extern Keyword* KWD_METHODS_PROPERTIES;
extern Symbol* SYM_METHODS_STELLA_PROPERTIES;
extern Keyword* KWD_METHODS_META_ATTRIBUTES;
extern Symbol* SYM_METHODS_STELLA_META_ATTRIBUTES;
extern Keyword* KWD_METHODS_COMMANDp;
extern Symbol* SYM_METHODS_STELLA_METHOD_COMMANDp;
extern Keyword* KWD_METHODS_LISP_MACROp;
extern Symbol* SYM_METHODS_STELLA_METHOD_LISP_MACROp;
extern Keyword* KWD_METHODS_EVALUATE_ARGUMENTSp;
extern Symbol* SYM_METHODS_STELLA_METHOD_EVALUATE_ARGUMENTSp;
extern Keyword* KWD_METHODS_C_CALLABLEp;
extern Symbol* SYM_METHODS_STELLA_METHOD_C_CALLABLEp;
extern Symbol* SYM_METHODS_STELLA_CONCATENATE;
extern Surrogate* SGT_METHODS_STELLA_METHOD_SLOT;
extern Symbol* SYM_METHODS_STELLA_SLOT_OPTION_HANDLER;
extern Symbol* SYM_METHODS_STELLA_DEFINE_FUNCTION_OBJECT;
extern Symbol* SYM_METHODS_STELLA_THE_CODE;
extern Keyword* KWD_METHODS_FUNCTION;
extern Symbol* SYM_METHODS_STELLA_DEFINE_INLINE_METHOD_CODE;
extern Symbol* SYM_METHODS_STELLA_QUOTE;
extern Keyword* KWD_METHODS_METHOD;
extern Symbol* SYM_METHODS_STELLA_DEFINE_METHOD_OBJECT;
extern Surrogate* SGT_METHODS_STELLA_BOOLEAN;
extern Symbol* SYM_METHODS_STELLA_SUPER_CLASSES;
extern Symbol* SYM_METHODS_STELLA_EQUIVALENT_SLOT;
extern Symbol* SYM_METHODS_STELLA_CLASS_ALL_SUPER_CLASSES;
extern Symbol* SYM_METHODS_STELLA_SLOT_DIRECT_EQUIVALENT;
extern Symbol* SYM_METHODS_STELLA_LET;
extern Symbol* SYM_METHODS_STELLA_CURSOR;
extern Symbol* SYM_METHODS_STELLA_VALUE;
extern Symbol* SYM_METHODS_STELLA_SLOT_VALUE;
extern Symbol* SYM_METHODS_STELLA_LOOP;
extern Symbol* SYM_METHODS_STELLA_WHEN;
extern Symbol* SYM_METHODS_STELLA_RETURN;
extern Symbol* SYM_METHODS_STELLA_SETQ;
extern Symbol* SYM_METHODS_STELLA_IF;
extern Symbol* SYM_METHODS_STELLA_DEFINEDp;
extern Surrogate* SGT_METHODS_STELLA_COLLECTION;
extern Symbol* SYM_METHODS_STELLA_FIRST;
extern Symbol* SYM_METHODS_STELLA_VARIABLE_ARITY_TABLEp;
extern Surrogate* SGT_METHODS_STELLA_VECTOR;
extern Symbol* SYM_METHODS_STELLA_EVALUATOR_WRAPPER_CODE;
extern Symbol* SYM_METHODS_STELLA_METHOD_MACROp;
extern Symbol* SYM_METHODS_STELLA_VARIABLE_TYPE_SPECIFIER;
extern Symbol* SYM_METHODS_STELLA_DEFSPECIAL;
extern Symbol* SYM_METHODS_STELLA_DEFCONSTANT;
extern Keyword* KWD_METHODS_UNBOUND_SPECIAL_VARIABLE;
extern Symbol* SYM_METHODS_STELLA_VARIABLE_HOME_MODULE;
extern Surrogate* SGT_METHODS_STELLA_LITERAL;
extern Surrogate* SGT_METHODS_STELLA_STRING;
extern Surrogate* SGT_METHODS_STELLA_INTEGER;
extern Surrogate* SGT_METHODS_STELLA_FLOAT;
extern Surrogate* SGT_METHODS_STELLA_LONG_INTEGER;
extern Surrogate* SGT_METHODS_STELLA_CHARACTER;
extern Surrogate* SGT_METHODS_STELLA_MUTABLE_STRING;
extern Surrogate* SGT_METHODS_STELLA_FUNCTION_CODE;
extern Surrogate* SGT_METHODS_STELLA_METHOD_CODE;
extern Surrogate* SGT_METHODS_STELLA_WRAPPER;
extern Symbol* SYM_METHODS_STELLA_STARTUP_METHODS;
extern Symbol* SYM_METHODS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
