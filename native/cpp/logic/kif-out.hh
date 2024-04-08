//  -*- Mode: C++ -*-

// kif-out.hh

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
extern DECLARE_STELLA_SPECIAL(oPRETTYPRINTLOGICALFORMSpo, boolean );
extern DECLARE_STELLA_SPECIAL(oPRETTYPRINTKIFpo, boolean );
extern DECLARE_STELLA_SPECIAL(oPRINTLOGICALFORMSTREAMo, OutputStream* );
extern DECLARE_STELLA_SPECIAL(oDOWNCASEOPERATORSpo, boolean );
extern KeyValueList* oLOGIC_DIALECT_PRINT_FUNCTIONSo;
extern DECLARE_STELLA_SPECIAL(oPRINTQUANTIFIEDOBJECTSSTACKo, Cons* );
extern DECLARE_STELLA_SPECIAL(oINDENTCOUNTERo, int );
extern int oINDENT_QUANTUMo;
extern DECLARE_STELLA_SPECIAL(oTOPLEVELPRINTKIFPROPOSITIONpo, boolean );
extern DECLARE_STELLA_SPECIAL(oEXCLUDEDPROPOSITIONSo, HashTable* );
extern Cons* oBUILT_IN_MODULE_NAMESo;

// Function signatures:
void registerLogicDialectPrintFunction(Keyword* dialect, FunctionCodeWrapper* fn);
void pushQuantifiedObject(Object* object);
void popQuantifiedObject();
boolean quantifiedObjectVariableP(Skolem* var);
const char* maybeDowncase(const char* string);
void increaseIndent(int indent);
void decreaseIndent(int indent);
void printIndent(OutputStream* stream, int indent);
void printLogicalFormInDialect(Object* self, Keyword* dialect, OutputStream* stream);
void printLogicalForm(Object* form, OutputStream* stream);
void prettyPrintLogicalForm(Object* form, OutputStream* stream);
void printUnformattedLogicalForm(Object* form, OutputStream* stream);
void printFormula(Object* formula, int indent);
void printAsKif(Object* self, OutputStream* stream);
void printAsKifInternal(Object* self);
boolean visibleArgumentP(Object* self);
int visibleArgumentsCount(Vector* arguments);
void printKifArguments(Vector* arguments, boolean separatelinesP, boolean omitlastargumentP);
void printKifOperatorWithArguments(const char* operatoR, Vector* arguments, boolean separatelinesP, boolean omitlastargumentP);
const char* stringifiedSurrogate(Surrogate* operatoR);
const char* stringifiedKifOperator(Proposition* self);
void printKifProposition(Proposition* self);
void helpPrintKifProposition(Proposition* self);
void printKifFunctionProposition(Proposition* self);
void printKifFunctionExpression(Proposition* self);
void printKifImpliesProposition(Proposition* self);
void printKifQuantifiedVariables(Vector* variables, boolean includetypesP);
void printKifQuantification(Proposition* self);
void printKifTopLevelExistsProposition(Proposition* self);
void printKifWrapper(LiteralWrapper* self);
void printKifLogicObject(LogicObject* self);
void printKifSkolem(Skolem* self, boolean suppressdefiningpropositionP);
void printKifVariable(PatternVariable* self);
void printKifStellaCollection(Collection* self);
void printKifDescription(Description* self);
void printKifDescriptionProposition(Description* self, boolean invertP);
Surrogate* chooseImplicationOperator(Proposition* rule, boolean forwardP);
KeyValueMap* createSkolemMappingTable(Vector* oldvars, Vector* newvars);
void printDescriptionsAsKifRule(Description* head, Description* tail, Proposition* rule, boolean reversepolarityP);
void excludeOriginatedPropositions();
boolean hiddenRelationP(Surrogate* relationRef);
boolean excludedPropositionP(Proposition* proposition, Module* module);
void prettyPrintNamedDescription(NamedDescription* self, OutputStream* stream);
const char* stellaRelationStringifiedSource(Relation* self);
void prettyPrintRelationDefinition(Relation* self, OutputStream* stream);
void prettyPrintRelationDefinitionTree(Cons* tree, OutputStream* stream);
void helpPrettyPrintRelationDefinitionTree(Cons* tree, OutputStream* stream, int startindent, int keyindent, boolean forcefirstkeyonseparatelineP);
void prettyPrintAssertion(Proposition* proposition, OutputStream* stream);
void prettyPrintNamedRule(Surrogate* rulename, OutputStream* stream);
void printModuleFileHeader(Module* module, OutputStream* stream);
void printModuleFileTrailer(Module* module, OutputStream* stream);
void saveObject(Object* object, Object* store);
void doSaveModule(Module* module, Object* store);
void saveModule(Cons* options);
void saveModuleEvaluatorWrapper(Cons* arguments);
void helpStartupKifOut1();
void helpStartupKifOut2();
void helpStartupKifOut3();
void startupKifOut();

// Auxiliary global declarations:
extern Surrogate* SGT_KIF_OUT_LOGIC_PROPOSITION;
extern Symbol* SYM_KIF_OUT_LOGIC_IO_VARIABLES;
extern Surrogate* SGT_KIF_OUT_LOGIC_DESCRIPTION;
extern Surrogate* SGT_KIF_OUT_STELLA_VECTOR;
extern Surrogate* SGT_KIF_OUT_STELLA_CONS;
extern Surrogate* SGT_KIF_OUT_STELLA_LIST;
extern Keyword* KWD_KIF_OUT_KIF;
extern Keyword* KWD_KIF_OUT_STELLA;
extern Keyword* KWD_KIF_OUT_PREFIX_STELLA;
extern Keyword* KWD_KIF_OUT_SQL;
extern Surrogate* SGT_KIF_OUT_LOGIC_PATTERN_VARIABLE;
extern Surrogate* SGT_KIF_OUT_LOGIC_SKOLEM;
extern Surrogate* SGT_KIF_OUT_LOGIC_LOGIC_OBJECT;
extern Surrogate* SGT_KIF_OUT_STELLA_COLLECTION;
extern Surrogate* SGT_KIF_OUT_LOGIC_LOGIC_THING;
extern Surrogate* SGT_KIF_OUT_STELLA_THING;
extern Keyword* KWD_KIF_OUT_ISA;
extern Keyword* KWD_KIF_OUT_REALISTIC;
extern Keyword* KWD_KIF_OUT_ORIGINAL;
extern Keyword* KWD_KIF_OUT_UNESCAPED;
extern Keyword* KWD_KIF_OUT_ESCAPED;
extern Keyword* KWD_KIF_OUT_COMPLEX_ESCAPED;
extern Surrogate* SGT_KIF_OUT_STELLA_FALSE;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_NOT;
extern Keyword* KWD_KIF_OUT_AND;
extern Keyword* KWD_KIF_OUT_OR;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_AND;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_OR;
extern Keyword* KWD_KIF_OUT_NOT;
extern Keyword* KWD_KIF_OUT_EQUIVALENT;
extern Keyword* KWD_KIF_OUT_PREDICATE;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_FORK;
extern Keyword* KWD_KIF_OUT_FUNCTION;
extern Keyword* KWD_KIF_OUT_IMPLIES;
extern Keyword* KWD_KIF_OUT_FORALL;
extern Keyword* KWD_KIF_OUT_EXISTS;
extern Keyword* KWD_KIF_OUT_CONSTANT;
extern Keyword* KWD_KIF_OUT_CONTAINED_BY;
extern Keyword* KWD_KIF_OUT_DELETED;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_SUBSET_OF;
extern Symbol* SYM_KIF_OUT_LOGIC_FORWARD_ONLYp;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_le;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_FORALL;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_EXISTS;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_SETOF;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_LISTOF;
extern Symbol* SYM_KIF_OUT_LOGIC_COMPLEMENT_DESCRIPTION;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_KAPPA;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_eg;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_egg;
extern Symbol* SYM_KIF_OUT_LOGIC_BACKWARD_ONLYp;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_lle;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_lt;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_tg;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_llt;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_tgg;
extern Surrogate* SGT_KIF_OUT_PL_KERNEL_KB_HIDDEN_RELATION;
extern Symbol* SYM_KIF_OUT_LOGIC_MASTER_PROPOSITION;
extern Symbol* SYM_KIF_OUT_LOGIC_ASSERTED_BY_TYPE_CHECKERp;
extern Keyword* KWD_KIF_OUT_TERSE;
extern Keyword* KWD_KIF_OUT_VERBOSE;
extern Keyword* KWD_KIF_OUT_SOURCE;
extern Keyword* KWD_KIF_OUT_SLOTS;
extern Keyword* KWD_KIF_OUT_PUBLIC_SLOTS;
extern Keyword* KWD_KIF_OUT_METHODS;
extern Keyword* KWD_KIF_OUT_PUBLIC_METHODS;
extern Symbol* SYM_KIF_OUT_STELLA_ASSERT;
extern Symbol* SYM_KIF_OUT_STELLA_SURROGATE_VALUE_INVERSE;
extern Symbol* SYM_KIF_OUT_LOGIC_PRESUME;
extern Symbol* SYM_KIF_OUT_STELLA_RETRACT;
extern Symbol* SYM_KIF_OUT_LOGIC_DEFRULE;
extern Symbol* SYM_KIF_OUT_LOGIC_IN_DIALECT;
extern Surrogate* SGT_KIF_OUT_STELLA_RELATION;
extern Surrogate* SGT_KIF_OUT_STELLA_OUTPUT_STREAM;
extern Surrogate* SGT_KIF_OUT_LOGIC_OBJECT_STORE;
extern Surrogate* SGT_KIF_OUT_LOGIC_NAMED_DESCRIPTION;
extern Symbol* SYM_KIF_OUT_LOGIC_UNDECLAREDp;
extern Keyword* KWD_KIF_OUT_MODULE;
extern Keyword* KWD_KIF_OUT_FILE;
extern Surrogate* SGT_KIF_OUT_STELLA_MODULE;
extern Surrogate* SGT_KIF_OUT_STELLA_STRING;
extern Keyword* KWD_KIF_OUT_MEDIUM;
extern Symbol* SYM_KIF_OUT_LOGIC_OBJECT_STORE;
extern Symbol* SYM_KIF_OUT_LOGIC_STARTUP_KIF_OUT;
extern Symbol* SYM_KIF_OUT_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
