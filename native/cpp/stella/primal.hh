//  -*- Mode: C++ -*-

// primal.hh

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
extern double PI;
extern int NULL_INTEGER;
extern short int NULL_SHORT_INTEGER;
extern long long int NULL_LONG_INTEGER;
extern unsigned short int NULL_UNSIGNED_SHORT_INTEGER;
extern unsigned long int NULL_UNSIGNED_LONG_INTEGER;
extern double NULL_FLOAT;
extern float NULL_SINGLE_FLOAT;
extern double NULL_DOUBLE_FLOAT;
extern char NULL_CHARACTER;
extern char NULL_BYTE;
extern char NULL_OCTET;
extern int MOST_POSITIVE_INTEGER;
extern int MOST_NEGATIVE_INTEGER;
extern long long int MOST_POSITIVE_LONG_INTEGER;
extern long long int MOST_NEGATIVE_LONG_INTEGER;
extern double MOST_POSITIVE_FLOAT;
extern double MOST_NEGATIVE_FLOAT;
extern double LEAST_POSITIVE_FLOAT;
extern double LEAST_NEGATIVE_FLOAT;
extern double RECIPROCAL_NL2;
extern double RECIPROCAL_NL10;
extern DECLARE_STELLA_SPECIAL(oTRANSIENTOBJECTSpo, boolean );
extern int* oHASH_BYTE_RANDOM_TABLEo;
extern int oINTEGER_MSB_MASKo;
extern int oINTEGER_UNSIGNED_BITS_MASKo;
extern long long int oLONG_INTEGER_MSB_MASKo;
extern long long int oLONG_INTEGER_UNSIGNED_BITS_MASKo;
extern Vector* oHASH_TABLE_SIZE_PRIME_STRINGSo;
extern Vector* oHASH_TABLE_SIZE_PRIMESo;
extern int LONG_INTEGER_BIT_WIDTH;
extern void* oBOOTSTRAP_LOCKo;

// Function signatures:
const char* lispNullArraySymbolString(int rank);
void printNumericConstants();
boolean eqlP(Object* x, Object* y);
boolean equalP(Object* x, Object* y);
boolean integerZeroP(int x);
boolean longIntegerZeroP(long long int x);
boolean integerPlusP(int x);
boolean longIntegerPlusP(long long int x);
boolean integerEvenP(int x);
boolean longIntegerEvenP(long long int x);
boolean integerOddP(int x);
boolean longIntegerOddP(long long int x);
int integerDiv(int x, int y);
long long int longIntegerDiv(long long int x, long long int y);
int integerRem(int x, int y);
long long int longIntegerRem(long long int x, long long int y);
double frem(double x, double y);
int integerMod(int x, int modulus);
long long int longIntegerMod(long long int x, long long int modulus);
double fmod(double x, double modulus);
long long int gcd(long long int x, long long int y);
boolean regularIntegerValuedP(long long int x);
boolean integerValuedP(double x);
Cons* floatToBase60(double x, boolean allIntegersP);
double base60ToFloat(Cons* l);
int random(int n);
void seedRandomNumberGenerator();
void seedRandomNumberGenerator2();
double sqrt(double n);
double cos(double n);
double sin(double n);
double tan(double n);
double acos(double n);
double asin(double n);
double atan(double n);
double atan2(double x, double y);
double log(double n);
double log2(double n);
double log10(double n);
double exp(double n);
double expt(double x, double y);
int integerMin(int x, int y);
long long int longIntegerMin(long long int x, long long int y);
double floatMin(double x, double y);
int integerMax(int x, int y);
long long int longIntegerMax(long long int x, long long int y);
double floatMax(double x, double y);
int integerAbs(int x);
long long int longIntegerAbs(long long int x);
double floatAbs(double x);
int characterCode(char ch);
char codeCharacter(int code);
char characterDowncase(char ch);
char characterUpcase(char ch);
char characterCapitalize(char ch);
boolean stringEqlP(const char* x, const char* y);
boolean stringEqualP(const char* x, const char* y);
int stringCompare(const char* x, const char* y, boolean caseSensitiveP);
boolean stringEmptyP(const char* x);
boolean stringNonEmptyP(const char* x);
boolean blankStringP(const char* string);
boolean stringL(const char* x, const char* y);
boolean stringLE(const char* x, const char* y);
boolean stringGE(const char* x, const char* y);
boolean stringG(const char* x, const char* y);
boolean stringLessP(const char* x, const char* y);
boolean stringLessEqualP(const char* x, const char* y);
boolean stringGreaterEqualP(const char* x, const char* y);
boolean stringGreaterP(const char* x, const char* y);
int stringCompareCaseNormalized(const char* x, const char* y);
int compareStrings(const char* x, const char* y, Keyword* collation);
int safeCompareStrings(const char* x, const char* y, Keyword* collation);
char* makeMutableString(int size, char initchar);
char* makeRawMutableString(int size);
const char* stringConcatenate(const char* string1, const char* string2, int otherstrings, ...);
char* helpSubstituteCharacters(char* self, const char* newChars, const char* oldChars);
char* mutableStringSubstituteCharacters(char* self, const char* newChars, const char* oldChars);
const char* stringSubstituteCharacters(const char* self, const char* newChars, const char* oldChars);
const char* replaceSubstrings(const char* string, const char* neW, const char* old);
const char* instantiateStringTemplate(const char* templatE, int varsAvalues, ...);
int insertString(const char* source, int start, int end, char* target, int targetIndex, Keyword* caseConversion);
const char* stringTrim(const char* string);
const char* intToString(int i);
const char* characterToString(char c);
const char* stellaIntegerToStringInBase(long long int integer, int base);
int stringToInt(const char* string);
const char* formatWithPadding(const char* input, int length, char padchar, Keyword* align, boolean truncateP);
const char* zeroPadInteger(int value, int size);
const char* zeroPadString(const char* input, int size);
char stringFirst(const char* self);
char mutableStringFirst(char* self);
char mutableStringFirstSetter(char* self, char ch);
char stringSecond(const char* self);
char mutableStringSecond(char* self);
char mutableStringSecondSetter(char* self, char ch);
char stringThird(const char* self);
char mutableStringThird(char* self);
char mutableStringThirdSetter(char* self, char ch);
char stringFourth(const char* self);
char mutableStringFourth(char* self);
char mutableStringFourthSetter(char* self, char ch);
char stringFifth(const char* self);
char mutableStringFifth(char* self);
char mutableStringFifthSetter(char* self, char ch);
char stringNth(const char* self, int position);
char mutableStringNth(char* self, int position);
char mutableStringNthSetter(char* self, char ch, int position);
int stringLength(const char* self);
int mutableStringLength(char* self);
int stringSearchIgnoreCase(const char* string, const char* substring, int start);
boolean startsWithP(const char* string, const char* prefix, int start);
boolean endsWithP(const char* string, const char* suffix, int end);
int helpFindMatchingPrefixLength(const char* string1, int start1, int end1, const char* string2, int start2, int end2);
int findMatchingPrefixLength(const char* string1, int start1, int end1, const char* string2, int start2, int end2);
int findMismatch(const char* string1, int start1, int end1, const char* string2, int start2, int end2, int& _Return1);
int nonMatchingPositionHelper(const char* source, int start, int end, const char* match);
int nonMatchingPosition(const char* source, int start, const char* match);
int helpAdvancePastWhitespace(const char* source, int start, int end);
int advancePastWhitespace(const char* source, int start);
boolean eqlExceptInWhitespaceP(const char* s1, const char* s2);
Cons* splitString(const char* input, char separator);
Object* unstringify(const char* string);
int hashmod(int code, int size);
int rotateHashCode(int arg);
int objectHashCode(Object* self);
int safeHashCode(Object* self);
int stringHashCode(const char* self);
int integerHashCode(int self);
int longIntegerHashCode(long long int self);
int floatHashCode(double self);
int characterHashCode(char self);
int safeEqualHashCode(Object* self);
int hashString(const char* string, int seedcode);
int pickHashTableSizePrime(int minsize);
void resizeVector(Vector* self, int size);
Object* nativeVectorNth(Object** self, int position);
Object* nativeVectorNthSetter(Object** self, Object* value, int position);
void unmake(Object* self);
boolean nativeProbeDirectoryP(const char* filename);
boolean probeFileP(const char* filename);
boolean probeDirectoryP(const char* filename);
CalendarDate* fileWriteDate(const char* filename);
long long int fileLength(const char* filename);
void deleteFile(const char* filename);
void renameFile(const char* fromfile, const char* tofile);
void copyStreamToStream(InputStream* in, OutputStream* out);
void copyFile(const char* fromfile, const char* tofile);
const char* getTempDirectory();
const char* makeTemporaryFileName(const char* prefix, const char* suffix);
const char* makeTemporaryFile(const char* prefix, const char* suffix);
Cons* clListDirectoryFiles(const char* directory);
Cons* cppListDirectoryFiles(const char* directory);
Cons* javaListDirectoryFiles(const char* directory);
Cons* listDirectoryFiles(const char* directory);
Cons* listDirectoryFilesEvaluatorWrapper(Cons* arguments);
Cons* listDirectoryFilesRecursively(const char* directory);
Cons* listDirectoryFilesRecursivelyEvaluatorWrapper(Cons* arguments);
void cppCreateDirectory(const char* directory);
void createDirectories(const char* directory);
void createDirectoriesEvaluatorWrapper(Cons* arguments);
void ensureDirectoriesExist(const char* filename);
void ensureDirectoriesExistEvaluatorWrapper(Cons* arguments);
int integerLognot(int arg);
long long int longIntegerLognot(long long int arg);
int integerLogand(int arg1, int arg2);
long long int longIntegerLogand(long long int arg1, long long int arg2);
int integerLogor(int arg1, int arg2);
long long int longIntegerLogor(long long int arg1, long long int arg2);
int integerLogxor(int arg1, int arg2);
long long int longIntegerLogxor(long long int arg1, long long int arg2);
int integerLength(long long int x);
int integerLength10(long long int x);
int integerShiftLeft(int arg, int count);
long long int longIntegerShiftLeft(long long int arg, int count);
int integerShiftRight(int arg, int count);
long long int longIntegerShiftRight(long long int arg, int count);
int integerUnsignedShiftRightBy1(int arg);
long long int longIntegerUnsignedShiftRightBy1(long long int arg);
const char* generateUuid(Keyword* uuidType);
const char* generateRandomUuid();
Object* stellify(Object* self);
boolean stellaObjectP(Object* self);
boolean runningAsLispP();
Keyword* runningInLanguage();
const char* runningSystemInformation();
const char* getenv(const char* varname, Cons* deflt);
StringWrapper* getenvEvaluatorWrapper(Cons* arguments);
void sleep(double seconds);
const char* exceptionMessage(std::exception* e);
void printExceptionContext(std::exception* e, OutputStream* stream);
const char* exceptionContext(std::exception* e);
void* makeProcessLock();
void helpStartupPrimal1();
void helpStartupPrimal2();
void helpStartupPrimal3();
void helpStartupPrimal4();
void helpStartupPrimal5();
void helpStartupPrimal6();
void startupPrimal();

// Auxiliary global declarations:
extern Keyword* KWD_PRIMAL_IF_NOT_EXISTS;
extern Keyword* KWD_PRIMAL_ABORT;
extern Symbol* SYM_PRIMAL_STELLA_FLOOR;
extern Keyword* KWD_PRIMAL_CPP;
extern Keyword* KWD_PRIMAL_FUNCTION;
extern Symbol* SYM_PRIMAL_STELLA_ROUND;
extern Symbol* SYM_PRIMAL_STELLA_FMOD;
extern Symbol* SYM_PRIMAL_STELLA_RANDOM;
extern Symbol* SYM_PRIMAL_STELLA_SQRT;
extern Symbol* SYM_PRIMAL_STELLA_COS;
extern Symbol* SYM_PRIMAL_STELLA_SIN;
extern Symbol* SYM_PRIMAL_STELLA_TAN;
extern Symbol* SYM_PRIMAL_STELLA_ACOS;
extern Symbol* SYM_PRIMAL_STELLA_ASIN;
extern Symbol* SYM_PRIMAL_STELLA_ATAN;
extern Symbol* SYM_PRIMAL_STELLA_ATAN2;
extern Symbol* SYM_PRIMAL_STELLA_EXP;
extern Symbol* SYM_PRIMAL_STELLA_LOG;
extern Symbol* SYM_PRIMAL_STELLA_MIN;
extern Symbol* SYM_PRIMAL_STELLA_MAX;
extern Keyword* KWD_PRIMAL_WHITE_SPACE;
extern Keyword* KWD_PRIMAL_ASCII_CASE_SENSITIVE;
extern Keyword* KWD_PRIMAL_ASCII_CASE_INSENSITIVE;
extern Keyword* KWD_PRIMAL_ASCII_CASE_NORMALIZED;
extern Keyword* KWD_PRIMAL_UPCASE;
extern Keyword* KWD_PRIMAL_DOWNCASE;
extern Keyword* KWD_PRIMAL_CAPITALIZE;
extern Keyword* KWD_PRIMAL_PRESERVE;
extern Keyword* KWD_PRIMAL_LEFT;
extern Keyword* KWD_PRIMAL_RIGHT;
extern Keyword* KWD_PRIMAL_CENTER;
extern Symbol* SYM_PRIMAL_STELLA_HASH_CODE;
extern Keyword* KWD_PRIMAL_JAVA;
extern Keyword* KWD_PRIMAL_UNIX;
extern Keyword* KWD_PRIMAL_MAC;
extern Keyword* KWD_PRIMAL_WINDOWS;
extern Keyword* KWD_PRIMAL_IF_EXISTS;
extern Keyword* KWD_PRIMAL_ERROR;
extern Keyword* KWD_PRIMAL_TYPE_4;
extern Keyword* KWD_PRIMAL_RANDOM;
extern Symbol* SYM_PRIMAL_STELLA_SLEEP;
extern Symbol* SYM_PRIMAL_STELLA_STARTUP_PRIMAL;
extern Symbol* SYM_PRIMAL_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
