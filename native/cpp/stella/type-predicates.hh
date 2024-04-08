//  -*- Mode: C++ -*-

// type-predicates.hh

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
extern boolean oCLASS_HIERARCHY_BOOTEDpo;

// Function signatures:
Surrogate* safePrimaryType(Object* x);
boolean bootstrapIsaP(Object* x, Surrogate* type);
boolean bootstrapSubtypeOfP(Surrogate* subtype, Surrogate* supertype);
boolean booleanP(Object* x);
boolean subtypeOfBooleanP(Surrogate* type);
boolean integerP(Object* x);
boolean subtypeOfIntegerP(Surrogate* type);
boolean longIntegerP(Object* x);
boolean subtypeOfLongIntegerP(Surrogate* type);
boolean floatP(Object* x);
boolean subtypeOfFloatP(Surrogate* type);
boolean stringP(Object* x);
boolean subtypeOfStringP(Surrogate* type);
boolean verbatimStringP(Object* x);
boolean subtypeOfVerbatimStringP(Surrogate* type);
boolean characterP(Object* x);
boolean subtypeOfCharacterP(Surrogate* type);
boolean wrapperP(Object* x);
boolean subtypeOfWrapperP(Surrogate* type);
boolean surrogateP(Object* x);
boolean subtypeOfSurrogateP(Surrogate* type);
boolean typeP(Object* x);
boolean subtypeOfTypeP(Surrogate* type);
boolean symbolP(Object* x);
boolean subtypeOfSymbolP(Surrogate* type);
boolean transientSymbolP(Object* x);
boolean subtypeOfTransientSymbolP(Surrogate* type);
boolean keywordP(Object* x);
boolean subtypeOfKeywordP(Surrogate* type);
boolean consP(Object* x);
boolean subtypeOfConsP(Surrogate* type);
boolean stellaClassP(Object* x);
boolean subtypeOfClassP(Surrogate* type);
boolean storageSlotP(Object* x);
boolean subtypeOfStorageSlotP(Surrogate* type);
boolean methodSlotP(Object* x);
boolean subtypeOfMethodSlotP(Surrogate* type);
boolean anchoredTypeSpecifierP(Object* x);
boolean subtypeOfAnchoredTypeSpecifierP(Surrogate* type);
boolean parametricTypeSpecifierP(Object* x);
boolean subtypeOfParametricTypeSpecifierP(Surrogate* type);
void helpStartupTypePredicates1();
void startupTypePredicates();

// Auxiliary global declarations:
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_UNKNOWN;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_BOOLEAN_WRAPPER;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_INTEGER_WRAPPER;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_LONG_INTEGER_WRAPPER;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_FLOAT_WRAPPER;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_STRING_WRAPPER;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_VERBATIM_STRING_WRAPPER;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_CHARACTER_WRAPPER;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_WRAPPER;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_SURROGATE;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_SYMBOL;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_TRANSIENT_SYMBOL;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_KEYWORD;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_CONS;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_CLASS;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_STORAGE_SLOT;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_METHOD_SLOT;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_ANCHORED_TYPE_SPECIFIER;
extern Surrogate* SGT_TYPE_PREDICATES_STELLA_PARAMETRIC_TYPE_SPECIFIER;
extern Symbol* SYM_TYPE_PREDICATES_STELLA_STARTUP_TYPE_PREDICATES;
extern Symbol* SYM_TYPE_PREDICATES_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
