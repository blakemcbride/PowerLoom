//  -*- Mode: C++ -*-

// literals.hh

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
extern IntegerWrapper* ZERO_WRAPPER;
extern IntegerWrapper* ONE_WRAPPER;
extern BooleanWrapper* TRUE_WRAPPER;
extern BooleanWrapper* FALSE_WRAPPER;
extern IntegerWrapper* NULL_INTEGER_WRAPPER;
extern LongIntegerWrapper* NULL_LONG_INTEGER_WRAPPER;
extern FloatWrapper* NULL_FLOAT_WRAPPER;
extern StringWrapper* NULL_STRING_WRAPPER;
extern MutableStringWrapper* NULL_MUTABLE_STRING_WRAPPER;
extern CharacterWrapper* NULL_CHARACTER_WRAPPER;
extern FunctionCodeWrapper* NULL_FUNCTION_CODE_WRAPPER;
extern MethodCodeWrapper* NULL_METHOD_CODE_WRAPPER;
extern HashTable* oLITERAL_TYPE_INFO_TABLEo;
extern List* oLITERAL_TYPESo;
extern Keyword** oCHARACTER_TYPE_TABLEo;
extern const char* oCHARACTER_UPCASE_TABLEo;
extern const char* oCHARACTER_DOWNCASE_TABLEo;

// Function signatures:
Object* lookupLiteralTypeInfo(Surrogate* type, Keyword* key);
void setLiteralTypeInfo(Surrogate* type, Keyword* key, Object* value);
IntegerWrapper* wrapInteger(int value);
int unwrapInteger(IntegerWrapper* wrapper);
LongIntegerWrapper* wrapLongInteger(long long int value);
long long int unwrapLongInteger(LongIntegerWrapper* wrapper);
NumberWrapper* wrapIntegerValue(long long int value);
FloatWrapper* wrapFloat(double value);
double unwrapFloat(FloatWrapper* wrapper);
StringWrapper* wrapString(const char* value);
const char* unwrapString(StringWrapper* wrapper);
MutableStringWrapper* wrapMutableString(char* value);
char* unwrapMutableString(MutableStringWrapper* wrapper);
CharacterWrapper* wrapCharacter(char value);
char unwrapCharacter(CharacterWrapper* wrapper);
FunctionCodeWrapper* wrapFunctionCode(cpp_function_code value);
cpp_function_code unwrapFunctionCode(FunctionCodeWrapper* wrapper);
MethodCodeWrapper* wrapMethodCode(cpp_method_code value);
cpp_method_code unwrapMethodCode(MethodCodeWrapper* wrapper);
BooleanWrapper* wrapBoolean(boolean value);
boolean unwrapBoolean(BooleanWrapper* wrapper);
boolean coerceWrappedBooleanToBoolean(BooleanWrapper* wrapper);
Object* inlineWrapBoolean(Object* expression);
Object* inlineUnwrapBoolean(Object* expression);
IntegerWrapper* integerWrapLiteral(int value);
LongIntegerWrapper* longIntegerWrapLiteral(long long int value);
FloatWrapper* floatWrapLiteral(double value);
MutableStringWrapper* mutableStringWrapLiteral(char* value);
StringWrapper* stringWrapLiteral(const char* value);
CharacterWrapper* characterWrapLiteral(char value);
FunctionCodeWrapper* functionCodeWrapLiteral(cpp_function_code value);
MethodCodeWrapper* methodCodeWrapLiteral(cpp_method_code value);
boolean eqlToBooleanP(Object* y, boolean x);
boolean eqlToIntegerP(Object* y, int x);
boolean eqlToLongIntegerP(Object* y, long long int x);
boolean eqlToFloatP(Object* y, double x);
boolean eqlToStringP(Object* y, const char* x);
boolean eqlToCharacterP(Object* y, char x);
Object* helpBquotify(Object* tree);
Object* bquotify(Object* tree);
Object* expandBquoteTree(Object* tree);
Object* simplifyBquoteTree(Object* tree);
Object* permanentCopy(Object* tree);
void printCharacter(char chaR, std::ostream* stream);
Keyword** createCharacterTypeTable();
boolean digitCharacterP(char ch);
boolean letterCharacterP(char ch);
boolean upperCaseCharacterP(char ch);
boolean lowerCaseCharacterP(char ch);
boolean whiteSpaceCharacterP(char ch);
boolean eightBitCharacterP(char ch);
boolean allUpperCaseStringP(const char* s);
boolean allLowerCaseStringP(const char* s);
const char* initializeCharacterUpcaseTable();
const char* initializeCharacterDowncaseTable();
char upcaseCharacter(char chaR);
char downcaseCharacter(char chaR);
void printStringReadably(const char* string, std::ostream* stream);
char* stringToMutableString(const char* s);
const char* mutableStringToString(char* s);
void helpStartupLiterals1();
void helpStartupLiterals2();
void helpStartupLiterals3();
void helpStartupLiterals4();
void startupLiterals();

// Auxiliary global declarations:
extern Surrogate* SGT_LITERALS_STELLA_BOOLEAN;
extern Keyword* KWD_LITERALS_NULL_WRAPPER;
extern Symbol* SYM_LITERALS_STELLA_FALSE_WRAPPER;
extern Surrogate* SGT_LITERALS_STELLA_INTEGER;
extern Symbol* SYM_LITERALS_STELLA_NULL_INTEGER_WRAPPER;
extern Surrogate* SGT_LITERALS_STELLA_LONG_INTEGER;
extern Symbol* SYM_LITERALS_STELLA_NULL_LONG_INTEGER_WRAPPER;
extern Surrogate* SGT_LITERALS_STELLA_FLOAT;
extern Symbol* SYM_LITERALS_STELLA_NULL_FLOAT_WRAPPER;
extern Surrogate* SGT_LITERALS_STELLA_STRING;
extern Symbol* SYM_LITERALS_STELLA_NULL_STRING_WRAPPER;
extern Surrogate* SGT_LITERALS_STELLA_MUTABLE_STRING;
extern Symbol* SYM_LITERALS_STELLA_NULL_MUTABLE_STRING_WRAPPER;
extern Surrogate* SGT_LITERALS_STELLA_CHARACTER;
extern Symbol* SYM_LITERALS_STELLA_NULL_CHARACTER_WRAPPER;
extern Surrogate* SGT_LITERALS_STELLA_FUNCTION_CODE;
extern Symbol* SYM_LITERALS_STELLA_NULL_FUNCTION_CODE_WRAPPER;
extern Surrogate* SGT_LITERALS_STELLA_METHOD_CODE;
extern Symbol* SYM_LITERALS_STELLA_NULL_METHOD_CODE_WRAPPER;
extern Symbol* SYM_LITERALS_STELLA_TRUE;
extern Symbol* SYM_LITERALS_STELLA_TRUE_WRAPPER;
extern Symbol* SYM_LITERALS_STELLA_FALSE;
extern Symbol* SYM_LITERALS_STELLA_WRAP_BOOLEAN;
extern Symbol* SYM_LITERALS_STELLA_COERCE_WRAPPED_BOOLEAN_TO_BOOLEAN;
extern Keyword* KWD_LITERALS_WRAP_FUNCTION;
extern Symbol* SYM_LITERALS_STELLA_WRAP_INTEGER;
extern Symbol* SYM_LITERALS_STELLA_WRAP_LONG_INTEGER;
extern Symbol* SYM_LITERALS_STELLA_WRAP_FLOAT;
extern Symbol* SYM_LITERALS_STELLA_WRAP_STRING;
extern Symbol* SYM_LITERALS_STELLA_WRAP_MUTABLE_STRING;
extern Symbol* SYM_LITERALS_STELLA_WRAP_CHARACTER;
extern Symbol* SYM_LITERALS_STELLA_WRAP_FUNCTION_CODE;
extern Symbol* SYM_LITERALS_STELLA_WRAP_METHOD_CODE;
extern Surrogate* SGT_LITERALS_STELLA_INTEGER_WRAPPER;
extern Surrogate* SGT_LITERALS_STELLA_LONG_INTEGER_WRAPPER;
extern Surrogate* SGT_LITERALS_STELLA_FLOAT_WRAPPER;
extern Surrogate* SGT_LITERALS_STELLA_BOOLEAN_WRAPPER;
extern Surrogate* SGT_LITERALS_STELLA_STRING_WRAPPER;
extern Surrogate* SGT_LITERALS_STELLA_VERBATIM_STRING_WRAPPER;
extern Surrogate* SGT_LITERALS_STELLA_CHARACTER_WRAPPER;
extern Symbol* SYM_LITERALS_STELLA_NULL;
extern Surrogate* SGT_LITERALS_STELLA_CONS;
extern Symbol* SYM_LITERALS_STELLA_NIL;
extern Symbol* SYM_LITERALS_STELLA_CONS;
extern Symbol* SYM_LITERALS_STELLA_WRAP_LITERAL;
extern Symbol* SYM_LITERALS_STELLA_GET_KWD;
extern Symbol* SYM_LITERALS_STELLA_TYPED_SYS;
extern Surrogate* SGT_LITERALS_STELLA_SYMBOL;
extern Symbol* SYM_LITERALS_STELLA_GET_SGT;
extern Symbol* SYM_LITERALS_STELLA_INTERN_COMMON_LISP_SYMBOL;
extern Symbol* SYM_LITERALS_STELLA_GET_SYM;
extern Symbol* SYM_LITERALS_STELLA_LISTo;
extern Symbol* SYM_LITERALS_STELLA_a;
extern Symbol* SYM_LITERALS_STELLA_aa;
extern Symbol* SYM_LITERALS_STELLA_CONCATENATE;
extern Keyword* KWD_LITERALS_OTHER;
extern Keyword* KWD_LITERALS_DIGIT;
extern Keyword* KWD_LITERALS_LETTER;
extern Keyword* KWD_LITERALS_SYMBOL_CONSTITUENT;
extern Keyword* KWD_LITERALS_SYMBOL_QUALIFIER;
extern Keyword* KWD_LITERALS_ESCAPE;
extern Keyword* KWD_LITERALS_DELIMITER;
extern Keyword* KWD_LITERALS_WHITE_SPACE;
extern Symbol* SYM_LITERALS_STELLA_NULL_STRING;
extern Symbol* SYM_LITERALS_STELLA_STARTUP_LITERALS;
extern Symbol* SYM_LITERALS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
