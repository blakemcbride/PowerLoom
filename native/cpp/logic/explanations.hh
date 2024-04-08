//  -*- Mode: C++ -*-

// explanations.hh

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
class ExplainException : public LogicException {
public:
  ExplainException(const std::string& msg) : LogicException(msg) {
}

};

class ExplainNoQueryException : public ExplainException {
public:
  ExplainNoQueryException(const std::string& msg) : ExplainException(msg) {
}

};

class ExplainNoSolutionException : public ExplainException {
public:
  ExplainNoSolutionException(const std::string& msg) : ExplainException(msg) {
}

};

class ExplainNoMoreSolutionsException : public ExplainException {
public:
  ExplainNoMoreSolutionsException(const std::string& msg) : ExplainException(msg) {
}

};

class ExplainNotEnabledException : public ExplainException {
public:
  ExplainNotEnabledException(const std::string& msg) : ExplainException(msg) {
}

};

class ExplainNoSuchLabelException : public ExplainException {
public:
  ExplainNoSuchLabelException(const std::string& msg) : ExplainException(msg) {
}

};

class ExplainQueryTrueException : public ExplainException {
public:
  ExplainQueryTrueException(const std::string& msg) : ExplainException(msg) {
}

};

class ExplanationInfo : public StandardObject {
public:
  const char* label;
  int depth;
  boolean explainedP;
public:
  virtual Surrogate* primaryType();
};


// Global declarations:
extern DECLARE_STELLA_SPECIAL(oEXPLANATION_FORMATo, Keyword* );
extern DECLARE_STELLA_SPECIAL(oEXPLANATION_STYLEo, Keyword* );
extern DECLARE_STELLA_SPECIAL(oEXPLANATION_AUDIENCEo, Keyword* );
extern int oDEFAULT_EXPLANATION_DEPTHo;
extern const char* oEXPLANATION_TAB_STRINGo;
extern int oMAX_INLINE_LABEL_LENGTHo;
extern const char* oEXPLANATION_ASSERTION_MARKERo;
extern const char* oEXPLANATION_FAILURE_MARKERo;
extern const char* oEXPLANATION_CUTOFF_MARKERo;
extern const char* oEXPLANATION_INFERENCE_MARKERo;
extern DECLARE_STELLA_SPECIAL(oEXPLANATION_VOCABULARYo, HashTable* );
extern KeyValueList* oEXPLANATION_VOCABULARIESo;
extern DECLARE_STELLA_SPECIAL(oCURRENTJUSTIFICATIONo, Justification* );
extern DECLARE_STELLA_SPECIAL(oMOST_RECENT_EXPLANATION_MAPPINGo, KeyValueList* );

// Function signatures:
ExplainException* newExplainException(const char* message);
ExplainNoQueryException* newExplainNoQueryException(const char* message);
ExplainNoSolutionException* newExplainNoSolutionException(const char* message);
ExplainNoMoreSolutionsException* newExplainNoMoreSolutionsException(const char* message);
ExplainNotEnabledException* newExplainNotEnabledException(const char* message);
ExplainNoSuchLabelException* newExplainNoSuchLabelException(const char* message);
ExplainQueryTrueException* newExplainQueryTrueException(const char* message);
const char* explanationTruthMarker(Justification* justification);
void defineExplanationPhrase(Keyword* phrasekey, Keyword* audience, const char* phrase, int modifiers, ...);
const char* lookupExplanationPhrase(Keyword* phrasekey, Cons* modifiers, Keyword* audience);
ExplanationInfo* newExplanationInfo();
Object* accessExplanationInfoSlotValue(ExplanationInfo* self, Symbol* slotname, Object* value, boolean setvalueP);
ExplanationInfo* registerJustification(Justification* self, KeyValueList* mapping);
ExplanationInfo* getExplanationInfo(Justification* self, KeyValueList* mapping, boolean createP);
ExplanationInfo* explanationInfo(Justification* self, KeyValueList* mapping);
Justification* lookupJustification(KeyValueList* mapping, const char* label);
void resetMappingForSubexplanation(KeyValueList* mapping);
KeyValueList* printExplanation(Justification* self, OutputStream* stream, KeyValueList* mapping, int maxdepth, Keyword* audience);
void printExplanationSupport(Justification* self, OutputStream* stream, KeyValueList* mapping, int maxdepth, List* unexplained);
void printOneExplanation(Justification* self, OutputStream* stream, KeyValueList* mapping, int maxdepth, List* unexplained);
boolean printingJustificationP();
void printJustificationPropositionForFormat(Justification* self, OutputStream* stream, int indent);
void printJustificationProposition(Justification* self, OutputStream* stream, int indent);
void printExplanationLabel(OutputStream* stream, const char* label, boolean headP);
void printExplanationHeader(Justification* self, OutputStream* stream, KeyValueList* mapping);
void printExplanationText(Justification* self, OutputStream* stream, KeyValueList* mapping);
boolean markAsExplicitAssertionP(Justification* self);
boolean markAsFailedGoalP(Justification* self);
boolean markAsCutoffGoalP(Justification* self);
boolean partiallyFollowsP(Justification* self);
const char* makeRuleOriginExplanationPhrase(Justification* self);
KeyValueMap* getExplanationSubstitution(Justification* self);
void printOneVariableSubstitution(OutputStream* stream, Object* var, Object* value);
void printExplanationSubstitution(Justification* self, OutputStream* stream, KeyValueList* mapping);
void printExplanationAntecedents(Justification* self, OutputStream* stream, KeyValueList* mapping, int maxdepth, List* unexplained);
Justification* visibleJustification(Justification* self);
List* visibleAntecedents(Justification* self);
void collectVisibleAntecedents(Justification* self, List* visibleantecedents);
void why(Cons* args);
void whyEvaluatorWrapper(Cons* arguments);
void explainWhy(const char* label, Keyword* style, int maxdepth, OutputStream* stream);
void explainProposition(Proposition* prop, Keyword* style, int maxdepth, OutputStream* stream);
Justification* getWhyJustification(const char* label);
boolean commandOptionEqlP(Object* arg, const char* option);
const char* parseWhyArguments(Cons* args, Keyword*& _Return1, int& _Return2, boolean& _Return3);
void helpStartupExplanations1();
void helpStartupExplanations2();
void helpStartupExplanations3();
void startupExplanations();

// Auxiliary global declarations:
extern Keyword* KWD_EXPLANATIONS_ASCII;
extern Keyword* KWD_EXPLANATIONS_BRIEF;
extern Keyword* KWD_EXPLANATIONS_TECHNICAL;
extern Keyword* KWD_EXPLANATIONS_ASSERTION;
extern Keyword* KWD_EXPLANATIONS_FAILURE;
extern Keyword* KWD_EXPLANATIONS_CUTOFF;
extern Keyword* KWD_EXPLANATIONS_INFERENCE;
extern Keyword* KWD_EXPLANATIONS_HTML;
extern Keyword* KWD_EXPLANATIONS_IMPLIES;
extern Symbol* SYM_EXPLANATIONS_LOGIC_EXPLANATION_VOCABULARY;
extern Keyword* KWD_EXPLANATIONS_UNKNOWN_RULE;
extern Keyword* KWD_EXPLANATIONS_FOLLOWS;
extern Keyword* KWD_EXPLANATIONS_LAY;
extern Keyword* KWD_EXPLANATIONS_PARTIAL;
extern Keyword* KWD_EXPLANATIONS_HOLDS;
extern Keyword* KWD_EXPLANATIONS_DEFINITION;
extern Keyword* KWD_EXPLANATIONS_FAILED;
extern Keyword* KWD_EXPLANATIONS_INCONSISTENT;
extern Keyword* KWD_EXPLANATIONS_CLASH;
extern Keyword* KWD_EXPLANATIONS_NOT_ASSERTED;
extern Keyword* KWD_EXPLANATIONS_NO_RULES;
extern Surrogate* SGT_EXPLANATIONS_LOGIC_EXPLANATION_INFO;
extern Symbol* SYM_EXPLANATIONS_STELLA_LABEL;
extern Symbol* SYM_EXPLANATIONS_STELLA_DEPTH;
extern Symbol* SYM_EXPLANATIONS_LOGIC_EXPLAINEDp;
extern Symbol* SYM_EXPLANATIONS_LOGIC_EXPLANATION_MAPPING;
extern Keyword* KWD_EXPLANATIONS_XML;
extern Keyword* KWD_EXPLANATIONS_CYC_NL;
extern Keyword* KWD_EXPLANATIONS_KIF_ONTOSAURUS;
extern Keyword* KWD_EXPLANATIONS_JAVA_GUI_HTML;
extern Keyword* KWD_EXPLANATIONS_REALISTIC;
extern Symbol* SYM_EXPLANATIONS_STELLA_NOT;
extern Keyword* KWD_EXPLANATIONS_AMPLIFICATION;
extern Keyword* KWD_EXPLANATIONS_REVERSE;
extern Surrogate* SGT_EXPLANATIONS_LOGIC_CLASH_JUSTIFICATION;
extern Keyword* KWD_EXPLANATIONS_PRIMITIVE_STRATEGY;
extern Keyword* KWD_EXPLANATIONS_SCAN_PROPOSITIONS;
extern Symbol* SYM_EXPLANATIONS_LOGIC_MASTER_PROPOSITION;
extern Keyword* KWD_EXPLANATIONS_FORWARD;
extern Keyword* KWD_EXPLANATIONS_SCAN_COLLECTION;
extern Keyword* KWD_EXPLANATIONS_LOOKUP_ASSERTIONS;
extern Keyword* KWD_EXPLANATIONS_EQUIVALENCE;
extern Symbol* SYM_EXPLANATIONS_LOGIC_COMPLEMENT_DESCRIPTION;
extern Surrogate* SGT_EXPLANATIONS_LOGIC_NAMED_DESCRIPTION;
extern Surrogate* SGT_EXPLANATIONS_LOGIC_FORWARD_JUSTIFICATION;
extern Surrogate* SGT_EXPLANATIONS_LOGIC_ALTERNATIVE_BINDINGS_SET;
extern Keyword* KWD_EXPLANATIONS_MODUS_PONENS;
extern Keyword* KWD_EXPLANATIONS_MODUS_TOLLENS;
extern Keyword* KWD_EXPLANATIONS_DISPROOF;
extern Keyword* KWD_EXPLANATIONS_GOAL_COMPLEMENT;
extern Keyword* KWD_EXPLANATIONS_PATTERN;
extern Keyword* KWD_EXPLANATIONS_AND_INTRODUCTION;
extern Symbol* SYM_EXPLANATIONS_LOGIC_JUSTIFICATION;
extern Surrogate* SGT_EXPLANATIONS_STELLA_GENERALIZED_SYMBOL;
extern Keyword* KWD_EXPLANATIONS_DIGIT;
extern Keyword* KWD_EXPLANATIONS_VERBOSE;
extern Keyword* KWD_EXPLANATIONS_DEPTH;
extern Symbol* SYM_EXPLANATIONS_LOGIC_STARTUP_EXPLANATIONS;
extern Symbol* SYM_EXPLANATIONS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
