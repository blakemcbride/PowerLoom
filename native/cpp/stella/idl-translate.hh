//  -*- Mode: C++ -*-

// idl-translate.hh

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
extern const char* oIDL_CHARACTER_SUBSTITUTION_TABLEo;
extern StringHashTable* oIDL_RESERVED_WORD_TABLEo;

// Function signatures:
Object* idlTranslateATree(Object* tree);
Cons* idlTranslateUnit(TranslationUnit* unit);
Cons* idlTranslateDeftypeUnit(TranslationUnit* unit);
Cons* idlTranslateNull();
StringWrapper* idlTranslateTypeSpec(StandardObject* typespec);
StringWrapper* idlTranslateClassName(GeneralizedSymbol* namesymbol);
const char* idlCreateCharacterSubstitutionTable();
const char* idlSubstituteForbiddenCharacters(const char* name, Keyword* caseconvention);
const char* idlChangeCase(GeneralizedSymbol* symbol, Keyword* caseconvention);
StringWrapper* idlYieldRenamedReservedWord(Symbol* word);
StringHashTable* idlCreateReservedWordTable();
StringWrapper* idlLookupReservedWordTable(Symbol* word);
StringWrapper* idlTranslateName(Symbol* namesymbol);
StringWrapper* idlTranslateSymbolConstantName(GeneralizedSymbol* symbol);
StringWrapper* idlTranslateSymbolConstantId(GeneralizedSymbol* symbol);
StringWrapper* idlTranslateSymbolName(Symbol* symbol);
StringWrapper* idlTranslateSymbolId(Symbol* symbol);
StringWrapper* idlTranslateSurrogateName(Surrogate* surrogate);
StringWrapper* idlTranslateSurrogateId(Surrogate* surrogate);
StringWrapper* idlTranslateKeywordName(Keyword* keyword);
StringWrapper* idlTranslateKeywordId(Keyword* keyword);
StringWrapper* idlTranslateClassParameterName(Symbol* namesymbol);
Symbol* idlCreateOverloadedFunctionName(Symbol* functionname, Surrogate* classtype);
boolean idlMethodObjectIsOverloadedFunctionP(MethodSlot* method);
StringWrapper* idlTranslateFunctionName(MethodSlot* function);
Object* idlTranslateMethodParameter(Symbol* name, StandardObject* type, Symbol* direction);
Cons* idlTranslateMethodParameters(MethodSlot* method);
StringWrapper* idlTranslateConstructorName(MethodSlot* constructor);
void helpStartupIdlTranslate1();
void startupIdlTranslate();

// Auxiliary global declarations:
extern Surrogate* SGT_IDL_TRANSLATE_STELLA_CONS;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_GLOBAL_VARIABLE;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_TYPE;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_CLASS;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_METHOD;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_MACRO;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_PRINT_METHOD;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_STARTUP_TIME_PROGN;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_VERBATIM;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_IDL_TYPEDEF;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_IDL_IDENT;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_IDL_LITERAL;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_CLASS_IDL_NATIVE_TYPE;
extern Keyword* KWD_IDL_TRANSLATE_CAPITALIZED;
extern Keyword* KWD_IDL_TRANSLATE_UPPERCASE;
extern Keyword* KWD_IDL_TRANSLATE_LOWERCASE;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_ASM;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_AUTO;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_BREAK;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_CASE;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_CATCH;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_CHAR;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_CONST;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_CONTINUE;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_DEFAULT;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_DELETE;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_DO;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_DOUBLE;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_ELSE;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_ENUM;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_EXTERN;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_FLOAT;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_FOR;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_FRIEND;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_GOTO;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_IF;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_INLINE;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_INT;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_LONG;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_NEW;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_OPERATOR;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_PRIVATE;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_PROTECTED;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_PUBLIC;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_REGISTER;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_RETURN;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_SHORT;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_SIGNED;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_SIZEOF;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_STATIC;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_STRUCT;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_SWITCH;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_TEMPLATE;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_THROW;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_TRY;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_TYPEDEF;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_UNION;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_UNSIGNED;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_VIRTUAL;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_VOID;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_VOLATILE;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_WHILE;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_TYPENAME;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_IN;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_STARTUP_IDL_TRANSLATE;
extern Symbol* SYM_IDL_TRANSLATE_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
