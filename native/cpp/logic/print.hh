//  -*- Mode: C++ -*-

// print.hh

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
 | The Original Code is the PowerLoom KR&R System.                            |
 |                                                                            |
 | The Initial Developer of the Original Code is                              |
 | UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
 | 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
 |                                                                            |
 | Portions created by the Initial Developer are Copyright (C) 1997-2023      |
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
 +----------------------------- END LICENSE BLOCK ----------------------------+
*/



namespace logic {
  using namespace stella;

// Global declarations:
extern boolean oDEBUG_PRINT_MODEpo;
extern DECLARE_STELLA_SPECIAL(oPRINTMODEo, Keyword* );
extern DECLARE_STELLA_SPECIAL(oPRINTFUNCTIONSASRELATIONSpo, boolean );
extern const char* VARIABLE_BINDING_SEPARATOR;
extern const char* VALUE_OF_SEPARATOR;
extern DECLARE_STELLA_SPECIAL(oSKOLEMNAMEMAPPINGTABLEo, KeyValueMap* );

// Function signatures:
OutputStream* wrapNativeOutputStream(std::ostream* nativestream);
void printTopLevelObject(Object* self, std::ostream* nativestream);
void printLogicObject(LogicObject* self, OutputStream* stream, boolean toplevelP);
const char* getSkolemPrintName(Skolem* self);
void printValueOfChain(Skolem* self, OutputStream* stream, Object* chainend);
void printSkolemName(Skolem* self, OutputStream* stream);
void printVariableName(PatternVariable* self, OutputStream* stream);
void printVariableValue(Object* self, OutputStream* stream);
void printSkolem(Skolem* self, OutputStream* stream, boolean toplevelP);
void printVariable(PatternVariable* self, OutputStream* stream);
void printQuantifiedVariable(PatternVariable* self, OutputStream* stream);
void printProposition(Proposition* self, OutputStream* stream, boolean toplevelP);
void printDescription(Description* self, OutputStream* stream, boolean toplevelP);
void startupPrint();

// Auxiliary global declarations:
extern Surrogate* SGT_PRINT_LOGIC_DESCRIPTION;
extern Surrogate* SGT_PRINT_LOGIC_PATTERN_VARIABLE;
extern Surrogate* SGT_PRINT_LOGIC_SKOLEM;
extern Surrogate* SGT_PRINT_LOGIC_TRUTH_VALUE;
extern Surrogate* SGT_PRINT_LOGIC_LOGIC_OBJECT;
extern Surrogate* SGT_PRINT_LOGIC_PROPOSITION;
extern Keyword* KWD_PRINT_FLAT;
extern Keyword* KWD_PRINT_REALISTIC;
extern Keyword* KWD_PRINT_ORIGINAL;
extern Keyword* KWD_PRINT_DEBUG_LOW;
extern Keyword* KWD_PRINT_DEBUG_HIGH;
extern Surrogate* SGT_PRINT_STELLA_RELATION;
extern Symbol* SYM_PRINT_LOGIC_DESCRIPTION;
extern Symbol* SYM_PRINT_LOGIC_DESCRIPTIVEp;
extern Symbol* SYM_PRINT_STELLA_SURROGATE_VALUE_INVERSE;
extern Symbol* SYM_PRINT_LOGIC_STARTUP_PRINT;
extern Symbol* SYM_PRINT_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
