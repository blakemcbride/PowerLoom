//  -*- Mode: C++ -*-

// generate.hh

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

// Class definitions:
class TermGenerationException : public LogicException {
// Signals an exception during term generation.
public:
  Object* offendingTerm;
public:
  TermGenerationException(const std::string& msg) : LogicException(msg) {
}

};


// Global declarations:
extern DECLARE_STELLA_SPECIAL(oCANONICALVARIABLENAMEMAPPINGo, KeyValueList* );
extern DECLARE_STELLA_SPECIAL(oCANONICALVARIABLECOUNTERo, int );

// Function signatures:
TermGenerationException* newTermGenerationException(Object* offendingTerm, const char* message);
Object* generateExpression(Object* self, boolean canonicalizevariablenamesP);
Symbol* generateNameOfVariable(PatternVariable* self);
Object* generateOneVariable(PatternVariable* self, boolean typedP);
Object* generateOneQuantifiedVariable(PatternVariable* self, boolean typedP);
Cons* generateVariables(Vector* vector, boolean typedP);
Cons* generateQuantifiedVariables(Vector* vector, boolean typedP);
Cons* generateStellaCollection(Collection* self);
Object* generateDescription(Description* self);
Cons* generateArguments(Vector* arguments);
Symbol* generateOperator(Proposition* self);
Object* generateProposition(Proposition* self);
Cons* generateFunctionAsTerm(Proposition* self);
Cons* generateFunctionProposition(Proposition* self);
Object* generateSkolem(Skolem* self);
Object* generateTerm(Object* self);
Cons* generateImpliesProposition(Proposition* self);
Cons* generateDescriptionProposition(Description* self, boolean invertP);
Cons* generateDescriptionsAsRule(Description* head, Description* tail, Proposition* rule, boolean reversepolarityP);
Object* deobjectifyTree(Object* self);
void helpStartupGenerate1();
void startupGenerate();

// Auxiliary global declarations:
extern Surrogate* SGT_GENERATE_STELLA_THING;
extern Symbol* SYM_GENERATE_PL_KERNEL_KB_SETOF;
extern Symbol* SYM_GENERATE_PL_KERNEL_KB_LISTOF;
extern Symbol* SYM_GENERATE_LOGIC_COMPLEMENT_DESCRIPTION;
extern Symbol* SYM_GENERATE_STELLA_NOT;
extern Symbol* SYM_GENERATE_LOGIC_KAPPA;
extern Symbol* SYM_GENERATE_STELLA_NULL;
extern Surrogate* SGT_GENERATE_PL_KERNEL_KB_EQUIVALENT;
extern Symbol* SYM_GENERATE_STELLA_e;
extern Keyword* KWD_GENERATE_PREDICATE;
extern Keyword* KWD_GENERATE_ISA;
extern Keyword* KWD_GENERATE_EQUIVALENT;
extern Keyword* KWD_GENERATE_AND;
extern Keyword* KWD_GENERATE_OR;
extern Keyword* KWD_GENERATE_NOT;
extern Keyword* KWD_GENERATE_FUNCTION;
extern Keyword* KWD_GENERATE_EXISTS;
extern Symbol* SYM_GENERATE_STELLA_EXISTS;
extern Symbol* SYM_GENERATE_LOGIC_IO_VARIABLES;
extern Keyword* KWD_GENERATE_FORALL;
extern Symbol* SYM_GENERATE_LOGIC_BACKWARD_ONLYp;
extern Symbol* SYM_GENERATE_STELLA_FORALL;
extern Keyword* KWD_GENERATE_IMPLIES;
extern Keyword* KWD_GENERATE_FAIL;
extern Symbol* SYM_GENERATE_LOGIC_FAIL;
extern Keyword* KWD_GENERATE_CONSTANT;
extern Symbol* SYM_GENERATE_PL_KERNEL_KB_CONCEPT_PROTOTYPE;
extern Symbol* SYM_GENERATE_LOGIC_UNIDENTIFIED_SKOLEM;
extern Surrogate* SGT_GENERATE_LOGIC_PROPOSITION;
extern Surrogate* SGT_GENERATE_STELLA_LITERAL_WRAPPER;
extern Surrogate* SGT_GENERATE_LOGIC_DESCRIPTION;
extern Surrogate* SGT_GENERATE_LOGIC_PATTERN_VARIABLE;
extern Surrogate* SGT_GENERATE_LOGIC_SKOLEM;
extern Surrogate* SGT_GENERATE_LOGIC_LOGIC_OBJECT;
extern Symbol* SYM_GENERATE_LOGIC_UNNAMED_OBJECT;
extern Surrogate* SGT_GENERATE_STELLA_COLLECTION;
extern Surrogate* SGT_GENERATE_LOGIC_LOGIC_THING;
extern Symbol* SYM_GENERATE_LOGIC_ILLEGAL_TERM;
extern Symbol* SYM_GENERATE_PL_KERNEL_KB_SUBSET_OF;
extern Symbol* SYM_GENERATE_LOGIC_FORWARD_ONLYp;
extern Surrogate* SGT_GENERATE_STELLA_CONS;
extern Symbol* SYM_GENERATE_LOGIC_STARTUP_GENERATE;
extern Symbol* SYM_GENERATE_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
