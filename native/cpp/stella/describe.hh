//  -*- Mode: C++ -*-

// describe.hh

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
extern KeyValueList* oSTRING_TO_OBJECT_FUNCTIONSo;
extern List* oINTEGER_TO_OBJECT_FUNCTIONSo;
extern Keyword* oDEFAULT_DESCRIBE_MODEo;
extern int oPRETTY_PRINT_LIST_CUTOFFo;
extern DECLARE_STELLA_SPECIAL(oSLOTOPTIONSLOTSo, Cons* );
extern DECLARE_STELLA_SPECIAL(oCLASSOPTIONSLOTSo, Cons* );
extern DECLARE_STELLA_SPECIAL(oCLASSUNSTRINGIFIEDOPTIONSo, PropertyList* );

// Function signatures:
Object* get(Object* name, Cons* type);
Object* getEvaluatorWrapper(Cons* arguments);
Object* stringGetObject(const char* self, Object* type);
Object* integerGetObject(int self, Object* type);
Object* stringSearchForObject(const char* string, Surrogate* classtype);
Object* searchForObject(Object* self, Object* typeref);
boolean filterStringToClassP(Class* self, AllPurposeIterator* iterator);
Iterator* stringToClasses(const char* string, boolean exactP);
Object* stringToClass(const char* string);
Object* stringToContext(const char* string);
Object* stringToFunction(const char* string);
boolean dottedStringP(const char* string);
const char* yieldExplodedMethodName(const char* dottedstring, const char*& _Return1);
Object* stringToSlot(const char* string);
Object* stringToSurrogateValue(const char* string);
Object* stringToDemon(const char* string);
Object* integerToContext(int integer);
void describe(Object* name, Cons* mode);
void describeEvaluatorWrapper(Cons* arguments);
void describeTersely(Object* self, OutputStream* stream);
void prettyPrintStellaTree(Cons* tree, OutputStream* stream);
void prettyPrintDefinitionTree(Cons* tree, OutputStream* stream);
Object* consifyListsAndIterators(Object* tree);
void printClassList(Iterator* self, OutputStream* stream);
Cons* getClassOptions();
PropertyList* getUnstringifiedClassOptions(Class* clasS);
Cons* getSlotOptions();
void prettyPrintLiteral(Object* literal, OutputStream* stream);
boolean literalEqlP(Object* x, Object* y);
Object* convertToLiteral(Object* object);
void prettyPrintClassOptions(Class* clasS, OutputStream* stream);
void prettyPrintSlotOptions(StorageSlot* slot, OutputStream* stream);
void prettyPrintMethodParameters(OutputStream* stream, MethodSlot* method);
void prettyPrintSlotBlock(OutputStream* stream, Iterator* iterator, const char* slotgroup);
void prettyPrintSlots(Class* self, OutputStream* stream);
const char* xmoduleStringifiedSource(Module* self);
const char* shortDocumentation(const char* documentation);
void printDocumentationString(const char* string, int indent, OutputStream* stream);
void helpStartupDescribe1();
void helpStartupDescribe2();
void startupDescribe();

// Auxiliary global declarations:
extern Surrogate* SGT_DESCRIBE_STELLA_FUNCTION_CODE_WRAPPER;
extern Surrogate* SGT_DESCRIBE_STELLA_CLASS;
extern Surrogate* SGT_DESCRIBE_STELLA_OBJECT;
extern Surrogate* SGT_DESCRIBE_STELLA_CONTEXT;
extern Surrogate* SGT_DESCRIBE_STELLA_METHOD_SLOT;
extern Surrogate* SGT_DESCRIBE_STELLA_SLOT;
extern Surrogate* SGT_DESCRIBE_STELLA_DEMON;
extern Keyword* KWD_DESCRIBE_VERBOSE;
extern Surrogate* SGT_DESCRIBE_STELLA_GENERALIZED_SYMBOL;
extern Surrogate* SGT_DESCRIBE_STELLA_CONS;
extern Surrogate* SGT_DESCRIBE_STELLA_LIST;
extern Surrogate* SGT_DESCRIBE_STELLA_ITERATOR;
extern Symbol* SYM_DESCRIBE_STELLA_SLOT_OPTION_KEYWORD;
extern Surrogate* SGT_DESCRIBE_STELLA_RELATION;
extern Surrogate* SGT_DESCRIBE_STELLA_STORAGE_SLOT;
extern Surrogate* SGT_DESCRIBE_STELLA_BOOLEAN_WRAPPER;
extern Surrogate* SGT_DESCRIBE_STELLA_LITERAL_WRAPPER;
extern Symbol* SYM_DESCRIBE_STELLA_TRUE;
extern Symbol* SYM_DESCRIBE_STELLA_FALSE;
extern Symbol* SYM_DESCRIBE_STELLA_SLOT_INITIAL_VALUE;
extern Symbol* SYM_DESCRIBE_STELLA_SLOT_TYPE_SPECIFIER;
extern Symbol* SYM_DESCRIBE_STELLA_METHOD_VARIABLE_ARGUMENTSp;
extern Keyword* KWD_DESCRIBE_SOURCE;
extern Keyword* KWD_DESCRIBE_TERSE;
extern Symbol* SYM_DESCRIBE_STELLA_SLOT;
extern Keyword* KWD_DESCRIBE_OWNER;
extern Keyword* KWD_DESCRIBE_TYPE;
extern Keyword* KWD_DESCRIBE_INITIALLY;
extern Symbol* SYM_DESCRIBE_STELLA_DEFMODULE;
extern Keyword* KWD_DESCRIBE_INCLUDES;
extern Keyword* KWD_DESCRIBE_USES;
extern Keyword* KWD_DESCRIBE_SHADOWS;
extern Symbol* SYM_DESCRIBE_STELLA_gg_INFERRED_SLOTS;
extern Keyword* KWD_DESCRIBE_CHILDREN;
extern Keyword* KWD_DESCRIBE_USED_BY;
extern Keyword* KWD_DESCRIBE_CARDINAL_MODULE;
extern Symbol* SYM_DESCRIBE_STELLA_DOCUMENTATION;
extern Symbol* SYM_DESCRIBE_STELLA_STARTUP_DESCRIBE;
extern Symbol* SYM_DESCRIBE_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
