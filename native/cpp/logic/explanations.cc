//  -*- Mode: C++ -*-

// explanations.cc

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

#include "logic/logic-system.hh"

namespace logic {
  using namespace stella;

ExplainException* newExplainException(const char* message) {
  { ExplainException* self = NULL;

    self = new ExplainException(message);
    return (self);
  }
}

ExplainNoQueryException* newExplainNoQueryException(const char* message) {
  { ExplainNoQueryException* self = NULL;

    self = new ExplainNoQueryException(message);
    return (self);
  }
}

ExplainNoSolutionException* newExplainNoSolutionException(const char* message) {
  { ExplainNoSolutionException* self = NULL;

    self = new ExplainNoSolutionException(message);
    return (self);
  }
}

ExplainNoMoreSolutionsException* newExplainNoMoreSolutionsException(const char* message) {
  { ExplainNoMoreSolutionsException* self = NULL;

    self = new ExplainNoMoreSolutionsException(message);
    return (self);
  }
}

ExplainNotEnabledException* newExplainNotEnabledException(const char* message) {
  { ExplainNotEnabledException* self = NULL;

    self = new ExplainNotEnabledException(message);
    return (self);
  }
}

ExplainNoSuchLabelException* newExplainNoSuchLabelException(const char* message) {
  { ExplainNoSuchLabelException* self = NULL;

    self = new ExplainNoSuchLabelException(message);
    return (self);
  }
}

ExplainQueryTrueException* newExplainQueryTrueException(const char* message) {
  { ExplainQueryTrueException* self = NULL;

    self = new ExplainQueryTrueException(message);
    return (self);
  }
}

// Keyword to control the explanation format.
// Valid values are :ASCII, :HTML and :XML
DEFINE_STELLA_SPECIAL(oEXPLANATION_FORMATo, Keyword* , NULL);

// Keywords that controls how detailed explanations will be.
// Valid values are :VERBOSE and :BRIEF.
DEFINE_STELLA_SPECIAL(oEXPLANATION_STYLEo, Keyword* , NULL);

// Keywords that controls the language for justifications.
// Valid values are :TECHNICAL and :LAY
DEFINE_STELLA_SPECIAL(oEXPLANATION_AUDIENCEo, Keyword* , NULL);

// Maximal explanation depth used if not otherwise specified.
int oDEFAULT_EXPLANATION_DEPTHo = 3;

const char* oEXPLANATION_TAB_STRINGo = "    ";

// Maximum length of a label string for which the following
// proposition will be printed on the same line.
int oMAX_INLINE_LABEL_LENGTHo = 10;

const char* oEXPLANATION_ASSERTION_MARKERo = "!";

const char* oEXPLANATION_FAILURE_MARKERo = "?";

const char* oEXPLANATION_CUTOFF_MARKERo = "x";

const char* oEXPLANATION_INFERENCE_MARKERo = " ";

const char* explanationTruthMarker(Justification* justification) {
  { Keyword* holdsby = NULL;

    if (markAsExplicitAssertionP(justification)) {
      holdsby = KWD_EXPLANATIONS_ASSERTION;
    }
    else if (markAsFailedGoalP(justification)) {
      holdsby = KWD_EXPLANATIONS_FAILURE;
    }
    else if (markAsCutoffGoalP(justification)) {
      holdsby = KWD_EXPLANATIONS_CUTOFF;
    }
    else {
      holdsby = KWD_EXPLANATIONS_INFERENCE;
    }
    if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
      { const char* label = "Fact:";
        const char* green = "#00ff00";
        const char* yellow = "#ffd70";
        const char* red = "#ff0000";
        const char* color = NULL;

        if (holdsby == KWD_EXPLANATIONS_ASSERTION) {
          if (justification->proposition->kind == KWD_EXPLANATIONS_IMPLIES) {
            label = "Rule:";
          }
          color = green;
        }
        else if (holdsby == KWD_EXPLANATIONS_FAILURE) {
          color = red;
          label = "Unknown:";
        }
        else if (holdsby == KWD_EXPLANATIONS_CUTOFF) {
          color = red;
          label = "Cutoff:";
        }
        else if (holdsby == KWD_EXPLANATIONS_INFERENCE) {
          label = "Inferred:";
          if (partiallyFollowsP(justification)) {
            color = yellow;
          }
          else {
            color = green;
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << holdsby << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
        if (color != NULL) {
          label = stringConcatenate("<font color=\"", color, 5, "\">", "<strong>", label, "</strong>", "</font>");
        }
        return (label);
      }
    }
    else {
      if (holdsby == KWD_EXPLANATIONS_ASSERTION) {
        return (oEXPLANATION_ASSERTION_MARKERo);
      }
      else if (holdsby == KWD_EXPLANATIONS_FAILURE) {
        return (oEXPLANATION_FAILURE_MARKERo);
      }
      else if (holdsby == KWD_EXPLANATIONS_CUTOFF) {
        return (oEXPLANATION_CUTOFF_MARKERo);
      }
      else if (holdsby == KWD_EXPLANATIONS_INFERENCE) {
        return (oEXPLANATION_INFERENCE_MARKERo);
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "`" << holdsby << "'" << " is not a valid case option";
          throw *newStellaException(stream001->theStringReader());
        }
      }
    }
  }
}

// The currently active vocabulary lookup table
DEFINE_STELLA_SPECIAL(oEXPLANATION_VOCABULARYo, HashTable* , NULL);

// List of vocabularies with keyword keys
KeyValueList* oEXPLANATION_VOCABULARIESo = NULL;

void defineExplanationPhrase(Keyword* phrasekey, Keyword* audience, const char* phrase, int modifiers, ...) {
  { HashTable* vocabulary = ((HashTable*)(oEXPLANATION_VOCABULARIESo->lookup(audience)));

    { Cons* arglist000 = NIL;

      { va_list iter000;
        int iter000Count = modifiers;
        Keyword* arg000 = NULL;
        Cons* collect000 = NULL;

        va_start(iter000, modifiers);
                for  (; (iter000Count--) > 0; ) {
          arg000 = va_arg(iter000, Keyword*);
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(arg000, NIL);
              if (arglist000 == NIL) {
                arglist000 = collect000;
              }
              else {
                addConsToEndOfConsList(arglist000, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(arg000, NIL);
              collect000 = collect000->rest;
            }
          }
        }
        va_end(iter000);
      }
      { Cons* mods = arglist000;
        Cons* entry = NIL;

        if (!((boolean)(vocabulary))) {
          vocabulary = newHashTable();
          oEXPLANATION_VOCABULARIESo->insertAt(audience, vocabulary);
        }
        entry = ((Cons*)(vocabulary->lookup(phrasekey)));
        if (!((boolean)(entry))) {
          entry = NIL;
        }
        vocabulary->insertAt(phrasekey, cons(cons(wrapString(phrase), mods), entry));
      }
    }
  }
}

const char* lookupExplanationPhrase(Keyword* phrasekey, Cons* modifiers, Keyword* audience) {
  { HashTable* vocabulary = ((HashTable*)(oEXPLANATION_VOCABULARIESo->lookup((((boolean)(audience)) ? audience : oEXPLANATION_AUDIENCEo))));
    Cons* entry = NIL;
    const char* bestphrase = NULL;
    int bestscore = -1;

    if (!((boolean)(vocabulary))) {
      vocabulary = ((HashTable*)(oEXPLANATION_VOCABULARIESo->lookup(KWD_EXPLANATIONS_TECHNICAL)));
    }
    if (!((boolean)(phrasekey))) {
      phrasekey = KWD_EXPLANATIONS_UNKNOWN_RULE;
    }
    entry = ((Cons*)(vocabulary->lookup(phrasekey)));
    if (!((boolean)(entry))) {
      vocabulary = ((HashTable*)(oEXPLANATION_VOCABULARIESo->lookup(KWD_EXPLANATIONS_TECHNICAL)));
      entry = ((Cons*)(vocabulary->lookup(phrasekey)));
    }
    if (!((boolean)(entry))) {
      return (lookupExplanationPhrase(KWD_EXPLANATIONS_UNKNOWN_RULE, NIL, audience));
    }
    { Cons* phrase = NULL;
      Cons* iter000 = entry;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        phrase = ((Cons*)(iter000->value));
        { boolean testValue000 = false;

          { boolean alwaysP000 = true;

            { Object* mod = NULL;
              Cons* iter001 = phrase->rest;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                mod = iter001->value;
                if (!modifiers->membP(mod)) {
                  alwaysP000 = false;
                  break;
                }
              }
            }
            testValue000 = alwaysP000;
          }
          if (testValue000) {
            testValue000 = phrase->rest->length() > bestscore;
          }
          if (testValue000) {
            bestscore = phrase->rest->length();
            bestphrase = ((StringWrapper*)(phrase->value))->wrapperValue;
          }
        }
      }
    }
    return (bestphrase);
  }
}

ExplanationInfo* newExplanationInfo() {
  { ExplanationInfo* self = NULL;

    self = new ExplanationInfo();
    self->explainedP = false;
    self->depth = NULL_INTEGER;
    self->label = NULL;
    return (self);
  }
}

Surrogate* ExplanationInfo::primaryType() {
  { ExplanationInfo* self = this;

    return (SGT_EXPLANATIONS_LOGIC_EXPLANATION_INFO);
  }
}

Object* accessExplanationInfoSlotValue(ExplanationInfo* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_EXPLANATIONS_STELLA_LABEL) {
    if (setvalueP) {
      self->label = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->label);
    }
  }
  else if (slotname == SYM_EXPLANATIONS_STELLA_DEPTH) {
    if (setvalueP) {
      self->depth = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->depth);
    }
  }
  else if (slotname == SYM_EXPLANATIONS_LOGIC_EXPLAINEDp) {
    if (setvalueP) {
      self->explainedP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->explainedP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

ExplanationInfo* registerJustification(Justification* self, KeyValueList* mapping) {
  return (getExplanationInfo(self, mapping, true));
}

ExplanationInfo* getExplanationInfo(Justification* self, KeyValueList* mapping, boolean createP) {
  { ExplanationInfo* info = ((ExplanationInfo*)(mapping->lookup(self)));

    if (!(((boolean)(info)))) {
      { Justification* just = NULL;
        ExplanationInfo* info = NULL;
        KvCons* iter000 = mapping->theKvList;

        for  (; ((boolean)(iter000)); 
              iter000 = iter000->rest) {
          just = ((Justification*)(iter000->key));
          info = ((ExplanationInfo*)(iter000->value));
          if (justificationEqlP(just, self)) {
            mapping->insertAt(self, info);
            return (info);
          }
        }
      }
      if (createP) {
        info = newExplanationInfo();
        mapping->insertAt(self, info);
      }
    }
    return (info);
  }
}

ExplanationInfo* explanationInfo(Justification* self, KeyValueList* mapping) {
  return (getExplanationInfo(self, mapping, false));
}

Justification* lookupJustification(KeyValueList* mapping, const char* label) {
  { Justification* justification = NULL;
    ExplanationInfo* info = NULL;
    KvCons* iter000 = mapping->theKvList;

    for  (; ((boolean)(iter000)); 
          iter000 = iter000->rest) {
      justification = ((Justification*)(iter000->key));
      info = ((ExplanationInfo*)(iter000->value));
      if (stringEqlP(info->label, label)) {
        return (justification);
      }
    }
  }
  return (NULL);
}

void resetMappingForSubexplanation(KeyValueList* mapping) {
  { Justification* justification = NULL;
    ExplanationInfo* info = NULL;
    KvCons* iter000 = mapping->theKvList;

    for  (; ((boolean)(iter000)); 
          iter000 = iter000->rest) {
      justification = ((Justification*)(iter000->key));
      info = ((ExplanationInfo*)(iter000->value));
      justification = justification;
      info->explainedP = false;
    }
  }
}

KeyValueList* printExplanation(Justification* self, OutputStream* stream, KeyValueList* mapping, int maxdepth, Keyword* audience) {
  { List* unexplained = newList();
    ExplanationInfo* info = NULL;

    self = visibleJustification(self);
    if (!((boolean)(mapping))) {
      mapping = newKeyValueList();
      info = registerJustification(self, mapping);
      info->label = "1";
      info->depth = 1;
    }
    else {
      info = explanationInfo(self, mapping);
      if (!((boolean)(info))) {
        throw *newStellaException("Justification not found in supplied explanation mapping.");
      }
      resetMappingForSubexplanation(mapping);
      maxdepth = (info->depth + maxdepth) - 1;
    }
    unexplained->push(self);
    { 
      BIND_STELLA_SPECIAL(oEXPLANATION_AUDIENCEo, Keyword*, audience);
      while (unexplained->nonEmptyP()) {
        self = ((Justification*)(unexplained->pop()));
        printOneExplanation(self, stream, mapping, maxdepth, unexplained);
      }
    }
    oMOST_RECENT_EXPLANATION_MAPPINGo = mapping;
    return (mapping);
  }
}

void printExplanationSupport(Justification* self, OutputStream* stream, KeyValueList* mapping, int maxdepth, List* unexplained) {
  printExplanationText(self, stream, mapping);
  printExplanationSubstitution(self, stream, mapping);
  printExplanationAntecedents(self, stream, mapping, maxdepth, unexplained);
}

void printOneExplanation(Justification* self, OutputStream* stream, KeyValueList* mapping, int maxdepth, List* unexplained) {
  if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_ASCII) {
    printExplanationHeader(self, stream, mapping);
    printExplanationSupport(self, stream, mapping, maxdepth, unexplained);
    *(stream->nativeStream) << std::endl;
  }
  else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_XML) {
    {
      *(stream->nativeStream) << "<inference>";
      *(stream->nativeStream) << std::endl;
      printExplanationHeader(self, stream, mapping);
      {
        *(stream->nativeStream) << "<support>";
        *(stream->nativeStream) << std::endl;
        printExplanationSupport(self, stream, mapping, maxdepth, unexplained);
        *(stream->nativeStream) << "</support>" << std::endl;
      }
      *(stream->nativeStream) << "</inference>" << std::endl;
    }
  }
  else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
    {
      *(stream->nativeStream) << "<TABLE>";
      {
        *(stream->nativeStream) << "<TR>";
        *(stream->nativeStream) << std::endl;
        printExplanationHeader(self, stream, mapping);
        printExplanationSupport(self, stream, mapping, maxdepth, unexplained);
        *(stream->nativeStream) << "</TD>";
        *(stream->nativeStream) << "</TR>" << std::endl;
      }
      *(stream->nativeStream) << "</TABLE>" << std::endl;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << oEXPLANATION_FORMATo << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

DEFINE_STELLA_SPECIAL(oCURRENTJUSTIFICATIONo, Justification* , NULL);

boolean printingJustificationP() {
  return (((boolean)(oCURRENTJUSTIFICATIONo)));
}

void printJustificationPropositionForFormat(Justification* self, OutputStream* stream, int indent) {
  if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_ASCII) {
    printJustificationProposition(self, stream, indent);
  }
  else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
    { OutputStringStream* stringStream = newOutputStringStream();
      boolean quotehtmlP = true;

      printJustificationProposition(self, stringStream, indent);
      if (oCYC_KLUDGES_ENABLEDpo) {
        if (oLOGIC_DIALECTo == KWD_EXPLANATIONS_CYC_NL) {
          quotehtmlP = false;
        }
      }
      if ((oLOGIC_DIALECTo == KWD_EXPLANATIONS_KIF_ONTOSAURUS) ||
          (oLOGIC_DIALECTo == KWD_EXPLANATIONS_JAVA_GUI_HTML)) {
        quotehtmlP = false;
      }
      if (quotehtmlP) {
        writeHtmlQuotingSpecialCharacters(stream->nativeStream, stringStream->theStringReader());
      }
      else {
        *(stream->nativeStream) << stringStream->theStringReader();
      }
    }
  }
  else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_XML) {
    { Proposition* proposition = self->proposition;
      OutputStringStream* stringStream = newOutputStringStream();

      printJustificationProposition(self, stringStream, 0);
      *(stream->nativeStream) << "<proposition type=\"";
      if (proposition->kind == KWD_EXPLANATIONS_IMPLIES) {
        *(stream->nativeStream) << "RULE";
      }
      else {
        *(stream->nativeStream) << "FACT";
      }
      *(stream->nativeStream) << "\" truthvalue=\"" << (((!((boolean)(self->truthValue))) ? UNKNOWN_TRUTH_VALUE : self->truthValue));
      *(stream->nativeStream) << "\">" << std::endl;
      writeHtmlQuotingSpecialCharacters(stream->nativeStream, stringStream->theStringReader());
      *(stream->nativeStream) << std::endl << "</proposition>";
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << oEXPLANATION_FORMATo << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void printJustificationProposition(Justification* self, OutputStream* stream, int indent) {
  { 
    BIND_STELLA_SPECIAL(oINDENTCOUNTERo, int, indent);
    BIND_STELLA_SPECIAL(oPRINTMODEo, Keyword*, KWD_EXPLANATIONS_REALISTIC);
    { Proposition* proposition = self->proposition;

      if (self->reversePolarityP) {
        proposition = createProposition(SYM_EXPLANATIONS_STELLA_NOT, 1);
        (proposition->arguments->theArray)[0] = (self->proposition);
      }
      { 
        BIND_STELLA_SPECIAL(oCURRENTJUSTIFICATIONo, Justification*, self);
        prettyPrintLogicalForm(proposition, stream);
      }
    }
  }
}

void printExplanationLabel(OutputStream* stream, const char* label, boolean headP) {
  headP = headP;
  if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_ASCII) {
    *(stream->nativeStream) << label;
  }
  else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_XML) {
    {
      *(stream->nativeStream) << "<label>";
      *(stream->nativeStream) << label;
      *(stream->nativeStream) << "</label>" << std::endl;
    }
  }
  else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
    {
      *(stream->nativeStream) << "<STRONG>";
      *(stream->nativeStream) << label << "&nbsp;";
      *(stream->nativeStream) << "</STRONG>";
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << oEXPLANATION_FORMATo << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void printExplanationHeader(Justification* self, OutputStream* stream, KeyValueList* mapping) {
  { ExplanationInfo* info = explanationInfo(self, mapping);
    const char* label = info->label;
    int indent = strlen(label) + 1;

    if ((oEXPLANATION_FORMATo == KWD_EXPLANATIONS_XML) ||
        (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_ASCII)) {
      printExplanationLabel(stream, label, true);
    }
    else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
      {
        *(stream->nativeStream) << "<TD align=left valign=top>";
        printExplanationLabel(stream, label, true);
        *(stream->nativeStream) << "</TD>" << std::endl;
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oEXPLANATION_FORMATo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    if (strlen(label) > oMAX_INLINE_LABEL_LENGTHo) {
      *(stream->nativeStream) << std::endl << oEXPLANATION_TAB_STRINGo;
      indent = strlen(oEXPLANATION_TAB_STRINGo);
    }
    else {
      *(stream->nativeStream) << " ";
    }
    if ((oEXPLANATION_FORMATo == KWD_EXPLANATIONS_XML) ||
        (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_ASCII)) {
    }
    else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
      *(stream->nativeStream) << "<TD align=left valign=top>";
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "`" << oEXPLANATION_FORMATo << "'" << " is not a valid case option";
        throw *newStellaException(stream001->theStringReader());
      }
    }
    printJustificationPropositionForFormat(self, stream, indent);
    *(stream->nativeStream) << std::endl;
    info->explainedP = true;
  }
}

void printExplanationText(Justification* self, OutputStream* stream, KeyValueList* mapping) {
  { const char* introduction = "";
    const char* inference = NULL;
    const char* amplification = "";
    Cons* modifiers = NIL;
    Cons* modifiersI = cons(KWD_EXPLANATIONS_AMPLIFICATION, NIL);

    if (self->reversePolarityP) {
      modifiers = cons(KWD_EXPLANATIONS_REVERSE, modifiers);
      modifiersI = cons(KWD_EXPLANATIONS_REVERSE, modifiersI);
    }
    if (partiallyFollowsP(self)) {
      modifiers = cons(KWD_EXPLANATIONS_PARTIAL, modifiers);
      modifiersI = cons(KWD_EXPLANATIONS_PARTIAL, modifiersI);
    }
    if (failedGoalJustificationP(self)) {
      introduction = lookupExplanationPhrase(KWD_EXPLANATIONS_FAILED, modifiers, NULL);
    }
    else if (isaP(self, SGT_EXPLANATIONS_LOGIC_CLASH_JUSTIFICATION)) {
      introduction = lookupExplanationPhrase(KWD_EXPLANATIONS_INCONSISTENT, modifiers, NULL);
    }
    else {
      introduction = lookupExplanationPhrase(KWD_EXPLANATIONS_FOLLOWS, modifiers, NULL);
    }
    if (self->inferenceRule == KWD_EXPLANATIONS_PRIMITIVE_STRATEGY) {
      if (self->inferenceStrategy() == KWD_EXPLANATIONS_SCAN_PROPOSITIONS) {
        if (((boolean)(((Proposition*)(dynamicSlotValue(self->proposition->dynamicSlots, SYM_EXPLANATIONS_LOGIC_MASTER_PROPOSITION, NULL)))))) {
          introduction = lookupExplanationPhrase(KWD_EXPLANATIONS_HOLDS, NIL, NULL);
          inference = makeRuleOriginExplanationPhrase(self);
        }
      }
      else {
      }
      if (inference == NULL) {
        inference = lookupExplanationPhrase(self->inferenceStrategy(), modifiers, NULL);
      }
    }
    else {
      inference = lookupExplanationPhrase(self->inferenceRule, modifiers, NULL);
      amplification = lookupExplanationPhrase(self->inferenceRule, modifiersI, NULL);
    }
    if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_ASCII) {
      *(stream->nativeStream) << oEXPLANATION_TAB_STRINGo;
      *(stream->nativeStream) << introduction << " " << inference;
      if ((strlen(amplification) > 0) &&
          (!stringEqlP(amplification, inference))) {
        *(stream->nativeStream) << " " << amplification;
      }
      if (self->inferenceDirection() == KWD_EXPLANATIONS_FORWARD) {
        *(stream->nativeStream) << " [Forward]";
      }
      *(stream->nativeStream) << std::endl;
    }
    else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
      *(stream->nativeStream) << "<BR>" << std::endl;
      *(stream->nativeStream) << introduction << " " << inference;
      if ((strlen(amplification) > 0) &&
          (!stringEqlP(amplification, inference))) {
        *(stream->nativeStream) << " " << amplification;
      }
      if (self->inferenceDirection() == KWD_EXPLANATIONS_FORWARD) {
        *(stream->nativeStream) << " [Forward]";
      }
      *(stream->nativeStream) << std::endl;
    }
    else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_XML) {
      *(stream->nativeStream) << "<method";
      if (self->inferenceDirection() == KWD_EXPLANATIONS_FORWARD) {
        *(stream->nativeStream) << " direction='forward'";
      }
      *(stream->nativeStream) << ">" << inference << "</method>" << std::endl;
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oEXPLANATION_FORMATo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

boolean markAsExplicitAssertionP(Justification* self) {
  if (oEXPLANATION_STYLEo == KWD_EXPLANATIONS_BRIEF) {
    if (self->inferenceRule == KWD_EXPLANATIONS_PRIMITIVE_STRATEGY) {
      { Keyword* testValue000 = ((PrimitiveStrategy*)(self))->strategy;

        if ((testValue000 == KWD_EXPLANATIONS_SCAN_COLLECTION) ||
            ((testValue000 == KWD_EXPLANATIONS_SCAN_PROPOSITIONS) ||
             ((testValue000 == KWD_EXPLANATIONS_LOOKUP_ASSERTIONS) ||
              (testValue000 == KWD_EXPLANATIONS_EQUIVALENCE)))) {
          return (true);
        }
        else {
        }
      }
    }
    else {
    }
  }
  return (false);
}

boolean markAsFailedGoalP(Justification* self) {
  return ((oEXPLANATION_STYLEo == KWD_EXPLANATIONS_BRIEF) &&
      ((self->inferenceRule == KWD_EXPLANATIONS_PRIMITIVE_STRATEGY) &&
       failedGoalJustificationP(self)));
}

boolean markAsCutoffGoalP(Justification* self) {
  return (cutoffGoalJustificationP(self));
}

boolean partiallyFollowsP(Justification* self) {
  return ((self->truthValue == UNKNOWN_TRUTH_VALUE) ||
      (!((boolean)(self->truthValue))));
}

const char* makeRuleOriginExplanationPhrase(Justification* self) {
  { Proposition* satellite = self->proposition;
    Proposition* master = ((Proposition*)(dynamicSlotValue(satellite->dynamicSlots, SYM_EXPLANATIONS_LOGIC_MASTER_PROPOSITION, NULL)));
    Description* head = ((Description*)((satellite->arguments->theArray)[1]));
    Description* tail = ((Description*)((satellite->arguments->theArray)[0]));
    NamedDescription* namedsource = NULL;
    Description* source = NULL;

    { int i = NULL_INTEGER;
      int iter000 = 1;
      int upperBound000 = 4;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        switch (i) {
          case 1: 
            source = head;
            break;
          case 2: 
            source = ((Description*)(dynamicSlotValue(head->dynamicSlots, SYM_EXPLANATIONS_LOGIC_COMPLEMENT_DESCRIPTION, NULL)));
            break;
          case 3: 
            source = tail;
            break;
          case 4: 
            source = ((Description*)(dynamicSlotValue(tail->dynamicSlots, SYM_EXPLANATIONS_LOGIC_COMPLEMENT_DESCRIPTION, NULL)));
            break;
          default:
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << i << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
            break;
        }
        if (((boolean)(source)) &&
            isaP(source, SGT_EXPLANATIONS_LOGIC_NAMED_DESCRIPTION)) {
          if (originatedPropositions(source)->memberP(master)) {
            namedsource = ((NamedDescription*)(source));
            break;
          }
        }
      }
    }
    if (((boolean)(namedsource))) {
      return (stringConcatenate(lookupExplanationPhrase(KWD_EXPLANATIONS_DEFINITION, NIL, NULL), " ", 3, nameObjectMetaclass(namedsource), " ", namedsource->descriptionName()->symbolName));
    }
    else {
      return (lookupExplanationPhrase(KWD_EXPLANATIONS_LOOKUP_ASSERTIONS, NIL, NULL));
    }
  }
}

KeyValueMap* getExplanationSubstitution(Justification* self) {
  { Justification* ruleJustification = ((Justification*)(self->antecedents->value));
    Proposition* rule = ruleJustification->proposition;
    Justification* antecedentJustification = ((Justification*)(self->antecedents->rest->value));
    KeyValueMap* antecedentSubstitution = antecedentJustification->substitution;

    if (isaP(self, SGT_EXPLANATIONS_LOGIC_FORWARD_JUSTIFICATION)) {
      antecedentSubstitution = self->substitution;
    }
    return (antecedentSubstitution);
  }
}

void printOneVariableSubstitution(OutputStream* stream, Object* var, Object* value) {
  if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_ASCII) {
    prettyPrintLogicalForm(var, stream);
    if (eqlP(valueOf(var), var)) {
      *(stream->nativeStream) << "/";
      if (((boolean)(value)) &&
          isaP(value, SGT_EXPLANATIONS_LOGIC_ALTERNATIVE_BINDINGS_SET)) {
        *(stream->nativeStream) << "{";
        { Object* binding = NULL;
          ListIterator* iter000 = ((ListIterator*)(((AlternativeBindingsSet*)(value))->bindings->allocateIterator()));

          for (; iter000->nextP(); ) {
            binding = iter000->value;
            prettyPrintLogicalForm(binding, stream);
            *(stream->nativeStream) << ", ";
          }
        }
        *(stream->nativeStream) << "...}";
      }
      else {
        prettyPrintLogicalForm(value, stream);
      }
    }
  }
  else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
    { OutputStringStream* stringStream = newOutputStringStream();
      boolean quotehtmlP = true;

      if (oCYC_KLUDGES_ENABLEDpo) {
        if (oLOGIC_DIALECTo == KWD_EXPLANATIONS_CYC_NL) {
          quotehtmlP = false;
        }
      }
      if ((oLOGIC_DIALECTo == KWD_EXPLANATIONS_KIF_ONTOSAURUS) ||
          (oLOGIC_DIALECTo == KWD_EXPLANATIONS_JAVA_GUI_HTML)) {
        quotehtmlP = false;
      }
      prettyPrintLogicalForm(var, stringStream);
      if (eqlP(valueOf(var), var)) {
        *(stringStream->nativeStream) << "/";
        if (((boolean)(value)) &&
            isaP(value, SGT_EXPLANATIONS_LOGIC_ALTERNATIVE_BINDINGS_SET)) {
          *(stringStream->nativeStream) << "{one of ";
          { Object* binding = NULL;
            ListIterator* iter001 = ((ListIterator*)(((AlternativeBindingsSet*)(value))->bindings->allocateIterator()));

            for (; iter001->nextP(); ) {
              binding = iter001->value;
              prettyPrintLogicalForm(binding, stringStream);
              *(stringStream->nativeStream) << ", ";
            }
          }
          *(stringStream->nativeStream) << "etc.}";
        }
        else {
          prettyPrintLogicalForm(value, stringStream);
        }
      }
      if (quotehtmlP) {
        writeHtmlQuotingSpecialCharacters(stream->nativeStream, stringStream->theStringReader());
      }
      else {
        *(stream->nativeStream) << stringStream->theStringReader();
      }
    }
  }
  else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_XML) {
    { OutputStringStream* stringStream = newOutputStringStream();

      {
        *(stream->nativeStream) << "<binding>";
        prettyPrintLogicalForm(var, stringStream);
        {
          *(stream->nativeStream) << "<variable>";
          writeHtmlQuotingSpecialCharacters(stream->nativeStream, stringStream->theStringReader());
          *(stream->nativeStream) << "</variable>" << std::endl;
        }
        if (eqlP(valueOf(var), var)) {
          stringStream = newOutputStringStream();
          prettyPrintLogicalForm(value, stringStream);
          {
            *(stream->nativeStream) << "<value>";
            writeHtmlQuotingSpecialCharacters(stream->nativeStream, stringStream->theStringReader());
            *(stream->nativeStream) << "</value>";
          }
        }
        *(stream->nativeStream) << "</binding>" << std::endl;
      }
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << oEXPLANATION_FORMATo << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

void printExplanationSubstitution(Justification* self, OutputStream* stream, KeyValueList* mapping) {
  mapping = mapping;
  if ((self->inferenceRule == KWD_EXPLANATIONS_MODUS_PONENS) ||
      (self->inferenceRule == KWD_EXPLANATIONS_MODUS_TOLLENS)) {
    { KeyValueMap* substitution = getExplanationSubstitution(self);
      int nofvars = NULL_INTEGER;

      if (((boolean)(substitution))) {
        nofvars = substitution->length();
        if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_ASCII) {
          *(stream->nativeStream) << oEXPLANATION_TAB_STRINGo << "with substitution {";
        }
        else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
          *(stream->nativeStream) << "<BR><TABLE><TR>" << std::endl;
          {
            *(stream->nativeStream) << "<TD align=left valign=top>";
            *(stream->nativeStream) << "with&nbsp;substitution" << std::endl;
            *(stream->nativeStream) << "</TD>" << std::endl;
          }
          *(stream->nativeStream) << "<TD>{";
        }
        else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_XML) {
          *(stream->nativeStream) << "<variables>";
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << oEXPLANATION_FORMATo << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
        { Object* var = NULL;
          Object* value = NULL;
          DictionaryIterator* iter000 = ((DictionaryIterator*)(substitution->allocateIterator()));
          int i = NULL_INTEGER;
          int iter001 = 1;
          int upperBound000 = nofvars;
          boolean unboundedP000 = upperBound000 == NULL_INTEGER;

          for  (; iter000->nextP() &&
                    (unboundedP000 ||
                     (iter001 <= upperBound000)); 
                iter001 = iter001 + 1) {
            var = iter000->key;
            value = iter000->value;
            i = iter001;
            printOneVariableSubstitution(stream, var, value);
            if ((i < nofvars) &&
                ((oEXPLANATION_FORMATo == KWD_EXPLANATIONS_ASCII) ||
                 (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML))) {
              *(stream->nativeStream) << ", ";
              if (oCYC_KLUDGES_ENABLEDpo) {
                if ((oEXPLANATION_FORMATo == KWD_EXPLANATIONS_ASCII) ||
                    (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML)) {
                  *(stream->nativeStream) << std::endl << oEXPLANATION_TAB_STRINGo << "                   ";
                }
              }
            }
          }
        }
        if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_ASCII) {
          *(stream->nativeStream) << "}" << std::endl;
        }
        else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
          *(stream->nativeStream) << "}</TD></TR></TABLE>" << std::endl;
        }
        else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_XML) {
          *(stream->nativeStream) << "</variables>" << std::endl;
        }
        else {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "`" << oEXPLANATION_FORMATo << "'" << " is not a valid case option";
            throw *newStellaException(stream001->theStringReader());
          }
        }
      }
    }
  }
}

void printExplanationAntecedents(Justification* self, OutputStream* stream, KeyValueList* mapping, int maxdepth, List* unexplained) {
  { ExplanationInfo* info = explanationInfo(self, mapping);
    const char* label = info->label;
    int depth = info->depth;
    List* antecedents = visibleAntecedents(self);
    Cons* newantecedents = NIL;
    int newantecedentsindex = 0;
    int maxlabellength = 0;
    boolean havemarkedantecedentP = false;
    int labelstartposition = strlen(oEXPLANATION_TAB_STRINGo) + 6;
    int propositionstartposition = 0;
    int indent = 0;

    { Justification* antecedent = NULL;
      Cons* iter000 = antecedents->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        antecedent = ((Justification*)(iter000->value));
        info = explanationInfo(antecedent, mapping);
        if (!((boolean)(info))) {
          info = registerJustification(antecedent, mapping);
          info->label = stringConcatenate(label, ".", 1, integerToString(((long long int)(newantecedentsindex = newantecedentsindex + 1))));
          info->depth = depth + 1;
        }
        maxlabellength = stella::integerMax(maxlabellength, strlen((info->label)));
        if (!havemarkedantecedentP) {
          havemarkedantecedentP = markAsExplicitAssertionP(antecedent) ||
              markAsFailedGoalP(antecedent);
        }
      }
    }
    if (maxlabellength > oMAX_INLINE_LABEL_LENGTHo) {
      propositionstartposition = labelstartposition;
    }
    else {
      propositionstartposition = labelstartposition + maxlabellength + 1;
    }
    if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
      *(stream->nativeStream) << "<TABLE>" << std::endl;
    }
    else {
    }
    { Justification* antecedent = NULL;
      Cons* iter001 = antecedents->theConsList;
      int i = NULL_INTEGER;
      int iter002 = 1;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest,
            iter002 = iter002 + 1) {
        antecedent = ((Justification*)(iter001->value));
        i = iter002;
        info = explanationInfo(antecedent, mapping);
        label = info->label;
        if (!(info->explainedP ||
            (markAsExplicitAssertionP(antecedent) ||
             (markAsFailedGoalP(antecedent) ||
              ((maxdepth != NULL_INTEGER) &&
               (info->depth > maxdepth)))))) {
          newantecedents = cons(antecedent, newantecedents);
        }
        if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_ASCII) {
          *(stream->nativeStream) << oEXPLANATION_TAB_STRINGo << (((i == 1) ? "since " : "and   "));
          printExplanationLabel(stream, label, false);
          *(stream->nativeStream) << " ";
          if (maxlabellength > oMAX_INLINE_LABEL_LENGTHo) {
            *(stream->nativeStream) << std::endl;
            indent = propositionstartposition;
          }
          else {
            indent = (propositionstartposition - (labelstartposition + strlen(label))) - 1;
          }
          { int i = NULL_INTEGER;
            int iter003 = 1;
            int upperBound000 = indent;
            boolean unboundedP000 = upperBound000 == NULL_INTEGER;

            for  (; unboundedP000 ||
                      (iter003 <= upperBound000); 
                  iter003 = iter003 + 1) {
              i = iter003;
              i = i;
              *(stream->nativeStream) << " ";
            }
          }
          if (havemarkedantecedentP) {
            *(stream->nativeStream) << explanationTruthMarker(antecedent) << " ";
          }
        }
        else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
          *(stream->nativeStream) << "<TR>" << std::endl;
          {
            *(stream->nativeStream) << "<TD align=right valign=top>";
            *(stream->nativeStream) << (((i == 1) ? "since&nbsp;" : "and&nbsp;"));
            printExplanationLabel(stream, label, false);
            {
              *(stream->nativeStream) << "<TD align=left valign=top>";
              if (havemarkedantecedentP) {
                *(stream->nativeStream) << explanationTruthMarker(antecedent);
              }
              *(stream->nativeStream) << "</TD>";
            }
            *(stream->nativeStream) << "</TD>" << std::endl;
          }
        }
        else if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_XML) {
          printExplanationLabel(stream, label, false);
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << oEXPLANATION_FORMATo << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
        if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
          *(stream->nativeStream) << "<TD>" << std::endl;
        }
        else {
        }
        printJustificationPropositionForFormat(antecedent, stream, (havemarkedantecedentP ? (propositionstartposition + strlen((explanationTruthMarker(antecedent))) + 1) : propositionstartposition));
        *(stream->nativeStream) << std::endl;
        if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
          *(stream->nativeStream) << "</TD></TR>" << std::endl;
        }
        else {
        }
      }
    }
    if (oEXPLANATION_FORMATo == KWD_EXPLANATIONS_HTML) {
      *(stream->nativeStream) << "</TABLE>" << std::endl;
    }
    else {
    }
    { Object* antecedent = NULL;
      Cons* iter004 = newantecedents;

      for (; !(iter004 == NIL); iter004 = iter004->rest) {
        antecedent = iter004->value;
        unexplained->push(((Justification*)(antecedent)));
      }
    }
  }
}

Justification* visibleJustification(Justification* self) {
  if (((self->inferenceRule == KWD_EXPLANATIONS_DISPROOF) &&
      (!self->reversePolarityP)) ||
      ((self->inferenceRule == KWD_EXPLANATIONS_PRIMITIVE_STRATEGY) &&
       (self->inferenceStrategy() == KWD_EXPLANATIONS_GOAL_COMPLEMENT))) {
    return (visibleJustification(((Justification*)(self->antecedents->value))));
  }
  else if (self->inferenceRule == KWD_EXPLANATIONS_PATTERN) {
    return (visibleJustification(((Justification*)(self->antecedents->value))));
  }
  else {
    return (self);
  }
}

List* visibleAntecedents(Justification* self) {
  { List* visibleantecedents = newList();

    collectVisibleAntecedents(self, visibleantecedents);
    return (visibleantecedents->reverse());
  }
}

void collectVisibleAntecedents(Justification* self, List* visibleantecedents) {
  { Cons* antecedents = self->antecedents;

    { Justification* antecedent = NULL;
      Cons* iter000 = antecedents;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        antecedent = ((Justification*)(iter000->value));
        antecedent = visibleJustification(antecedent);
        { Keyword* testValue000 = antecedent->inferenceRule;

          if (testValue000 == KWD_EXPLANATIONS_AND_INTRODUCTION) {
            if (oEXPLANATION_STYLEo == KWD_EXPLANATIONS_BRIEF) {
              { Justification* subantecedent = NULL;
                Cons* iter001 = visibleAntecedents(antecedent)->theConsList;

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  subantecedent = ((Justification*)(iter001->value));
                  visibleantecedents->push(subantecedent);
                }
              }
            }
            else {
              visibleantecedents->push(antecedent);
            }
          }
          else if (testValue000 == KWD_EXPLANATIONS_PRIMITIVE_STRATEGY) {
            if (((PrimitiveStrategy*)(antecedent))->strategy == KWD_EXPLANATIONS_EQUIVALENCE) {
              if (!(auxiliaryEquivalencePropositionP(antecedent->proposition))) {
                visibleantecedents->push(antecedent);
              }
            }
            else {
              visibleantecedents->push(antecedent);
            }
          }
          else {
            visibleantecedents->push(antecedent);
          }
        }
      }
    }
  }
}

DEFINE_STELLA_SPECIAL(oMOST_RECENT_EXPLANATION_MAPPINGo, KeyValueList* , NULL);

void why(Cons* args) {
  // Print an explanation for the result of the most recent query.
  // Without any arguments, `why' prints an explanation of the top level
  // query proposition down to a maximum depth of 3.  `(why all)' prints
  // an explanation to unlimited depth.  Alternatively, a particular depth
  // can be specified, for example, `(why 5)' explains down to a depth of 5.
  // A proof step that was not explained explicitly (e.g., due to a depth
  // cutoff) can be explained by supplying the label of the step as the
  // first argument to `why', for example, `(why 1.2.3 5)' prints an explanation
  // starting at 1.2.3 down to a depth of 5 (which is counted relative to the
  // depth of the starting point).  The keywords `brief' and `verbose' can be
  // used to select a particular explanation style.  In brief mode, explicitly
  // asserted propositions are not further explained and indicated with a
  // `!' assertion marker.  Additionally, relatively uninteresting proof steps
  // such as AND-introductions are skipped.  This explanation style option is
  // sticky and will affect future calls to `why' until it gets changed again.
  // The various options can be combined in any way, for example,
  // `(why 1.2.3 brief 3)' explains starting from step 1.2.3 down to a depth
  // of 3 in brief explanation mode.
  { const char* label = NULL;
    Keyword* style = NULL;
    int maxdepth = NULL_INTEGER;
    boolean summaryP = false;

    label = parseWhyArguments(args, style, maxdepth, summaryP);
    summaryP = summaryP;
    explainWhy(label, style, maxdepth, STANDARD_OUTPUT);
  }
}

void whyEvaluatorWrapper(Cons* arguments) {
  why(arguments);
}

void explainWhy(const char* label, Keyword* style, int maxdepth, OutputStream* stream) {
  // Programmer's interface to WHY function.
  try {
    { Justification* justification = getWhyJustification(label);

      { 
        BIND_STELLA_SPECIAL(oEXPLANATION_STYLEo, Keyword*, (((boolean)(style)) ? style : KWD_EXPLANATIONS_BRIEF));
        printExplanation(justification, stream, oMOST_RECENT_EXPLANATION_MAPPINGo, maxdepth, oEXPLANATION_AUDIENCEo);
      }
    }
  }
  catch (ExplainException& _ee) {
    ExplainException* ee = &_ee;

    std::cout << exceptionMessage(ee);
  }
}

void explainProposition(Proposition* prop, Keyword* style, int maxdepth, OutputStream* stream) {
  // Print an explanation for `prop' if there is one.  This will only happen
  // for forward-chained propositions.
  try {
    { 
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, getQueryContext());
      BIND_STELLA_SPECIAL(oMODULEo, Module*, oCONTEXTo->baseModule);
      { List* justifications = getSupportedForwardJustifications(prop);

        if (((boolean)(justifications))) {
          { 
            BIND_STELLA_SPECIAL(oEXPLANATION_STYLEo, Keyword*, (((boolean)(style)) ? style : KWD_EXPLANATIONS_BRIEF));
            BIND_STELLA_SPECIAL(oMOST_RECENT_EXPLANATION_MAPPINGo, KeyValueList*, NULL);
            { ForwardJustification* justification = NULL;
              Cons* iter000 = justifications->theConsList;

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                justification = ((ForwardJustification*)(iter000->value));
                oMOST_RECENT_EXPLANATION_MAPPINGo = NULL;
                printExplanation(justification, stream, oMOST_RECENT_EXPLANATION_MAPPINGo, maxdepth, oEXPLANATION_AUDIENCEo);
              }
            }
          }
        }
      }
    }
  }
  catch (ExplainException& _ee) {
    ExplainException* ee = &_ee;

    std::cout << exceptionMessage(ee);
  }
}

Justification* getWhyJustification(const char* label) {
  // Returns the current WHY justification.  May also throw one of the
  // following subtypes of EXPLAIN-EXCEPTION:
  //    EXPLAIN-NO-QUERY-EXCEPTION
  //    EXPLAIN-NO-SOLUTION-EXCEPTION
  //    EXPLAIN-NO-MORE-SOLUTIONS-EXCEPTION
  //    EXPLAIN-NOT-ENABLED-EXCEPTION
  //    EXPLAIN-NO-SUCH-LABEL-EXCEPTION
  //    EXPLAIN-QUERY-TRUE-EXCEPTION
  { QueryIterator* query = oMOST_RECENT_QUERYo;
    boolean partialqueryP = false;
    Justification* justification = NULL;

    if (!((boolean)(query))) {
      throw *newExplainNoQueryException("There is nothing to explain.");
    }
    partialqueryP = ((boolean)(oMOST_RECENT_QUERYo->partialMatchStrategy));
    justification = ((Justification*)(dynamicSlotValue(query->baseControlFrame->dynamicSlots, SYM_EXPLANATIONS_LOGIC_JUSTIFICATION, NULL)));
    if (!((boolean)(justification))) {
      if (query->solutions->nonEmptyP()) {
        if (query->exhaustedP) {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "There were either no more solutions, or you used the `all' keyword." << std::endl << "   The query must generate only a single answer for explanation" << std::endl << "   to be possible, thus don't use the `all' keyword to `retrieve'.";
            throw *newExplainNoSolutionException(stream000->theStringReader());
          }
        }
        else {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "No justifications available.  You have to enable justifications" << std::endl << "   with `(set-feature justifications)' and rerun the query in" << std::endl << "   order to enable the explanation of results.";
            throw *newExplainNotEnabledException(stream001->theStringReader());
          }
        }
      }
      else if (query->exhaustedP) {
        throw *newExplainNoSolutionException("There was no solution.");
      }
      else {
        throw *newExplainNoSolutionException("There is no solution yet.");
      }
    }
    else if (query->exhaustedP &&
        (!partialqueryP)) {
      throw *newExplainNoMoreSolutionsException("There were no more solutions.");
    }
    else {
      if (label != NULL) {
        if (((boolean)(oMOST_RECENT_EXPLANATION_MAPPINGo))) {
          justification = lookupJustification(oMOST_RECENT_EXPLANATION_MAPPINGo, label);
        }
        if (!((boolean)(justification))) {
          { OutputStringStream* stream002 = newOutputStringStream();

            *(stream002->nativeStream) << "Label " << "`" << label << "'" << " does not exists in the current explanation.";
            throw *newExplainNoSuchLabelException(stream002->theStringReader());
          }
        }
      }
      else {
        oMOST_RECENT_EXPLANATION_MAPPINGo = NULL;
      }
      return (justification);
    }
  }
}

boolean commandOptionEqlP(Object* arg, const char* option) {
  { Surrogate* testValue000 = safePrimaryType(arg);

    if (subtypeOfP(testValue000, SGT_EXPLANATIONS_STELLA_GENERALIZED_SYMBOL)) {
      { Object* arg000 = arg;
        GeneralizedSymbol* arg = ((GeneralizedSymbol*)(arg000));

        return (stringEqlP(stringUpcase(arg->symbolName), option));
      }
    }
    else if (subtypeOfStringP(testValue000)) {
      { Object* arg001 = arg;
        StringWrapper* arg = ((StringWrapper*)(arg001));

        return (stringEqlP(stringUpcase(arg->wrapperValue), option));
      }
    }
    else {
      return (false);
    }
  }
}

const char* parseWhyArguments(Cons* args, Keyword*& _Return1, int& _Return2, boolean& _Return3) {
  { const char* label = NULL;
    int depth = oDEFAULT_EXPLANATION_DEPTHo;
    Keyword* style = NULL;
    boolean summaryP = false;
    Object* firstarg = args->value;

    if (((boolean)(firstarg))) {
      { Surrogate* testValue000 = safePrimaryType(firstarg);

        if (subtypeOfStringP(testValue000)) {
          { Object* firstarg000 = firstarg;
            StringWrapper* firstarg = ((StringWrapper*)(firstarg000));

            label = firstarg->wrapperValue;
            args = args->rest;
          }
        }
        else if (subtypeOfIntegerP(testValue000)) {
          { Object* firstarg001 = firstarg;
            IntegerWrapper* firstarg = ((IntegerWrapper*)(firstarg001));

            if (eqlP(firstarg, ONE_WRAPPER)) {
              label = "1";
              args = args->rest;
            }
          }
        }
        else if (subtypeOfFloatP(testValue000)) {
          { Object* firstarg002 = firstarg;
            FloatWrapper* firstarg = ((FloatWrapper*)(firstarg002));

            label = stringify(firstarg);
            args = args->rest;
          }
        }
        else if (subtypeOfSymbolP(testValue000)) {
          { Object* firstarg003 = firstarg;
            Symbol* firstarg = ((Symbol*)(firstarg003));

            if (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) ((firstarg->symbolName)[0])] == KWD_EXPLANATIONS_DIGIT) {
              label = firstarg->symbolName;
              args = args->rest;
            }
          }
        }
        else {
        }
      }
      { Object* arg = NULL;
        Cons* iter000 = args;
        int i = NULL_INTEGER;
        int iter001 = 0;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          arg = iter000->value;
          i = iter001;
          if (commandOptionEqlP(arg, "BRIEF")) {
            style = KWD_EXPLANATIONS_BRIEF;
          }
          if (commandOptionEqlP(arg, "VERBOSE")) {
            style = KWD_EXPLANATIONS_VERBOSE;
          }
          if (commandOptionEqlP(arg, "SUMMARY")) {
            summaryP = true;
          }
          if (integerP(arg)) {
            depth = ((IntegerWrapper*)(arg))->wrapperValue;
          }
          if (arg == KWD_EXPLANATIONS_DEPTH) {
            if (!((boolean)(args->nth(i + 1)))) {
              depth = NULL_INTEGER;
            }
          }
          if (commandOptionEqlP(arg, "ALL")) {
            depth = NULL_INTEGER;
          }
        }
      }
    }
    _Return1 = style;
    _Return2 = depth;
    _Return3 = summaryP;
    return (label);
  }
}

void helpStartupExplanations1() {
  {
    KWD_EXPLANATIONS_ASCII = ((Keyword*)(internRigidSymbolWrtModule("ASCII", NULL, 2)));
    KWD_EXPLANATIONS_BRIEF = ((Keyword*)(internRigidSymbolWrtModule("BRIEF", NULL, 2)));
    KWD_EXPLANATIONS_TECHNICAL = ((Keyword*)(internRigidSymbolWrtModule("TECHNICAL", NULL, 2)));
    KWD_EXPLANATIONS_ASSERTION = ((Keyword*)(internRigidSymbolWrtModule("ASSERTION", NULL, 2)));
    KWD_EXPLANATIONS_FAILURE = ((Keyword*)(internRigidSymbolWrtModule("FAILURE", NULL, 2)));
    KWD_EXPLANATIONS_CUTOFF = ((Keyword*)(internRigidSymbolWrtModule("CUTOFF", NULL, 2)));
    KWD_EXPLANATIONS_INFERENCE = ((Keyword*)(internRigidSymbolWrtModule("INFERENCE", NULL, 2)));
    KWD_EXPLANATIONS_HTML = ((Keyword*)(internRigidSymbolWrtModule("HTML", NULL, 2)));
    KWD_EXPLANATIONS_IMPLIES = ((Keyword*)(internRigidSymbolWrtModule("IMPLIES", NULL, 2)));
    SYM_EXPLANATIONS_LOGIC_EXPLANATION_VOCABULARY = ((Symbol*)(internRigidSymbolWrtModule("EXPLANATION-VOCABULARY", NULL, 0)));
    KWD_EXPLANATIONS_UNKNOWN_RULE = ((Keyword*)(internRigidSymbolWrtModule("UNKNOWN-RULE", NULL, 2)));
    KWD_EXPLANATIONS_FOLLOWS = ((Keyword*)(internRigidSymbolWrtModule("FOLLOWS", NULL, 2)));
    KWD_EXPLANATIONS_LAY = ((Keyword*)(internRigidSymbolWrtModule("LAY", NULL, 2)));
    KWD_EXPLANATIONS_PARTIAL = ((Keyword*)(internRigidSymbolWrtModule("PARTIAL", NULL, 2)));
    KWD_EXPLANATIONS_HOLDS = ((Keyword*)(internRigidSymbolWrtModule("HOLDS", NULL, 2)));
    KWD_EXPLANATIONS_DEFINITION = ((Keyword*)(internRigidSymbolWrtModule("DEFINITION", NULL, 2)));
    KWD_EXPLANATIONS_FAILED = ((Keyword*)(internRigidSymbolWrtModule("FAILED", NULL, 2)));
    KWD_EXPLANATIONS_INCONSISTENT = ((Keyword*)(internRigidSymbolWrtModule("INCONSISTENT", NULL, 2)));
    KWD_EXPLANATIONS_CLASH = ((Keyword*)(internRigidSymbolWrtModule("CLASH", NULL, 2)));
    KWD_EXPLANATIONS_NOT_ASSERTED = ((Keyword*)(internRigidSymbolWrtModule("NOT-ASSERTED", NULL, 2)));
    KWD_EXPLANATIONS_NO_RULES = ((Keyword*)(internRigidSymbolWrtModule("NO-RULES", NULL, 2)));
    SGT_EXPLANATIONS_LOGIC_EXPLANATION_INFO = ((Surrogate*)(internRigidSymbolWrtModule("EXPLANATION-INFO", NULL, 1)));
    SYM_EXPLANATIONS_STELLA_LABEL = ((Symbol*)(internRigidSymbolWrtModule("LABEL", getStellaModule("/STELLA", true), 0)));
    SYM_EXPLANATIONS_STELLA_DEPTH = ((Symbol*)(internRigidSymbolWrtModule("DEPTH", getStellaModule("/STELLA", true), 0)));
    SYM_EXPLANATIONS_LOGIC_EXPLAINEDp = ((Symbol*)(internRigidSymbolWrtModule("EXPLAINED?", NULL, 0)));
    SYM_EXPLANATIONS_LOGIC_EXPLANATION_MAPPING = ((Symbol*)(internRigidSymbolWrtModule("EXPLANATION-MAPPING", NULL, 0)));
    KWD_EXPLANATIONS_XML = ((Keyword*)(internRigidSymbolWrtModule("XML", NULL, 2)));
    KWD_EXPLANATIONS_CYC_NL = ((Keyword*)(internRigidSymbolWrtModule("CYC-NL", NULL, 2)));
    KWD_EXPLANATIONS_KIF_ONTOSAURUS = ((Keyword*)(internRigidSymbolWrtModule("KIF-ONTOSAURUS", NULL, 2)));
    KWD_EXPLANATIONS_JAVA_GUI_HTML = ((Keyword*)(internRigidSymbolWrtModule("JAVA-GUI-HTML", NULL, 2)));
    KWD_EXPLANATIONS_REALISTIC = ((Keyword*)(internRigidSymbolWrtModule("REALISTIC", NULL, 2)));
    SYM_EXPLANATIONS_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", getStellaModule("/STELLA", true), 0)));
    KWD_EXPLANATIONS_AMPLIFICATION = ((Keyword*)(internRigidSymbolWrtModule("AMPLIFICATION", NULL, 2)));
    KWD_EXPLANATIONS_REVERSE = ((Keyword*)(internRigidSymbolWrtModule("REVERSE", NULL, 2)));
    SGT_EXPLANATIONS_LOGIC_CLASH_JUSTIFICATION = ((Surrogate*)(internRigidSymbolWrtModule("CLASH-JUSTIFICATION", NULL, 1)));
    KWD_EXPLANATIONS_PRIMITIVE_STRATEGY = ((Keyword*)(internRigidSymbolWrtModule("PRIMITIVE-STRATEGY", NULL, 2)));
    KWD_EXPLANATIONS_SCAN_PROPOSITIONS = ((Keyword*)(internRigidSymbolWrtModule("SCAN-PROPOSITIONS", NULL, 2)));
    SYM_EXPLANATIONS_LOGIC_MASTER_PROPOSITION = ((Symbol*)(internRigidSymbolWrtModule("MASTER-PROPOSITION", NULL, 0)));
    KWD_EXPLANATIONS_FORWARD = ((Keyword*)(internRigidSymbolWrtModule("FORWARD", NULL, 2)));
    KWD_EXPLANATIONS_SCAN_COLLECTION = ((Keyword*)(internRigidSymbolWrtModule("SCAN-COLLECTION", NULL, 2)));
    KWD_EXPLANATIONS_LOOKUP_ASSERTIONS = ((Keyword*)(internRigidSymbolWrtModule("LOOKUP-ASSERTIONS", NULL, 2)));
    KWD_EXPLANATIONS_EQUIVALENCE = ((Keyword*)(internRigidSymbolWrtModule("EQUIVALENCE", NULL, 2)));
    SYM_EXPLANATIONS_LOGIC_COMPLEMENT_DESCRIPTION = ((Symbol*)(internRigidSymbolWrtModule("COMPLEMENT-DESCRIPTION", NULL, 0)));
    SGT_EXPLANATIONS_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
    SGT_EXPLANATIONS_LOGIC_FORWARD_JUSTIFICATION = ((Surrogate*)(internRigidSymbolWrtModule("FORWARD-JUSTIFICATION", NULL, 1)));
    SGT_EXPLANATIONS_LOGIC_ALTERNATIVE_BINDINGS_SET = ((Surrogate*)(internRigidSymbolWrtModule("ALTERNATIVE-BINDINGS-SET", NULL, 1)));
    KWD_EXPLANATIONS_MODUS_PONENS = ((Keyword*)(internRigidSymbolWrtModule("MODUS-PONENS", NULL, 2)));
    KWD_EXPLANATIONS_MODUS_TOLLENS = ((Keyword*)(internRigidSymbolWrtModule("MODUS-TOLLENS", NULL, 2)));
    KWD_EXPLANATIONS_DISPROOF = ((Keyword*)(internRigidSymbolWrtModule("DISPROOF", NULL, 2)));
    KWD_EXPLANATIONS_GOAL_COMPLEMENT = ((Keyword*)(internRigidSymbolWrtModule("GOAL-COMPLEMENT", NULL, 2)));
    KWD_EXPLANATIONS_PATTERN = ((Keyword*)(internRigidSymbolWrtModule("PATTERN", NULL, 2)));
    KWD_EXPLANATIONS_AND_INTRODUCTION = ((Keyword*)(internRigidSymbolWrtModule("AND-INTRODUCTION", NULL, 2)));
    SYM_EXPLANATIONS_LOGIC_JUSTIFICATION = ((Symbol*)(internRigidSymbolWrtModule("JUSTIFICATION", NULL, 0)));
    SGT_EXPLANATIONS_STELLA_GENERALIZED_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("GENERALIZED-SYMBOL", getStellaModule("/STELLA", true), 1)));
    KWD_EXPLANATIONS_DIGIT = ((Keyword*)(internRigidSymbolWrtModule("DIGIT", NULL, 2)));
    KWD_EXPLANATIONS_VERBOSE = ((Keyword*)(internRigidSymbolWrtModule("VERBOSE", NULL, 2)));
    KWD_EXPLANATIONS_DEPTH = ((Keyword*)(internRigidSymbolWrtModule("DEPTH", NULL, 2)));
    SYM_EXPLANATIONS_LOGIC_STARTUP_EXPLANATIONS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-EXPLANATIONS", NULL, 0)));
    SYM_EXPLANATIONS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupExplanations2() {
  {
    { Class* clasS = defineClassFromStringifiedSource("EXPLAIN-EXCEPTION", "(DEFCLASS EXPLAIN-EXCEPTION (LOGIC-EXCEPTION))");

      clasS->classConstructorCode = ((cpp_function_code)(&newExplainException));
    }
    { Class* clasS = defineClassFromStringifiedSource("EXPLAIN-NO-QUERY-EXCEPTION", "(DEFCLASS EXPLAIN-NO-QUERY-EXCEPTION (EXPLAIN-EXCEPTION))");

      clasS->classConstructorCode = ((cpp_function_code)(&newExplainNoQueryException));
    }
    { Class* clasS = defineClassFromStringifiedSource("EXPLAIN-NO-SOLUTION-EXCEPTION", "(DEFCLASS EXPLAIN-NO-SOLUTION-EXCEPTION (EXPLAIN-EXCEPTION))");

      clasS->classConstructorCode = ((cpp_function_code)(&newExplainNoSolutionException));
    }
    { Class* clasS = defineClassFromStringifiedSource("EXPLAIN-NO-MORE-SOLUTIONS-EXCEPTION", "(DEFCLASS EXPLAIN-NO-MORE-SOLUTIONS-EXCEPTION (EXPLAIN-EXCEPTION))");

      clasS->classConstructorCode = ((cpp_function_code)(&newExplainNoMoreSolutionsException));
    }
    { Class* clasS = defineClassFromStringifiedSource("EXPLAIN-NOT-ENABLED-EXCEPTION", "(DEFCLASS EXPLAIN-NOT-ENABLED-EXCEPTION (EXPLAIN-EXCEPTION))");

      clasS->classConstructorCode = ((cpp_function_code)(&newExplainNotEnabledException));
    }
    { Class* clasS = defineClassFromStringifiedSource("EXPLAIN-NO-SUCH-LABEL-EXCEPTION", "(DEFCLASS EXPLAIN-NO-SUCH-LABEL-EXCEPTION (EXPLAIN-EXCEPTION))");

      clasS->classConstructorCode = ((cpp_function_code)(&newExplainNoSuchLabelException));
    }
    { Class* clasS = defineClassFromStringifiedSource("EXPLAIN-QUERY-TRUE-EXCEPTION", "(DEFCLASS EXPLAIN-QUERY-TRUE-EXCEPTION (EXPLAIN-EXCEPTION))");

      clasS->classConstructorCode = ((cpp_function_code)(&newExplainQueryTrueException));
    }
    defineStellaTypeFromStringifiedSource("(DEFTYPE EXPLANATION-VOCABULARY (HASH-TABLE OF KEYWORD (CONS OF CONS)))");
    { Class* clasS = defineClassFromStringifiedSource("EXPLANATION-INFO", "(DEFCLASS EXPLANATION-INFO (STANDARD-OBJECT) :SLOTS ((LABEL :TYPE STRING) (DEPTH :TYPE INTEGER) (EXPLAINED? :TYPE BOOLEAN)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newExplanationInfo));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessExplanationInfoSlotValue));
    }
    defineStellaTypeFromStringifiedSource("(DEFTYPE EXPLANATION-MAPPING (KEY-VALUE-LIST OF JUSTIFICATION EXPLANATION-INFO))");
  }
}

void helpStartupExplanations3() {
  {
    defineFunctionObject("EXPLANATION-TRUTH-MARKER", "(DEFUN (EXPLANATION-TRUTH-MARKER STRING) ((JUSTIFICATION JUSTIFICATION)))", ((cpp_function_code)(&explanationTruthMarker)), NULL);
    defineFunctionObject("DEFINE-EXPLANATION-PHRASE", "(DEFUN DEFINE-EXPLANATION-PHRASE ((PHRASEKEY KEYWORD) (AUDIENCE KEYWORD) (PHRASE STRING) |&REST| (MODIFIERS KEYWORD)))", ((cpp_function_code)(&defineExplanationPhrase)), NULL);
    defineFunctionObject("LOOKUP-EXPLANATION-PHRASE", "(DEFUN (LOOKUP-EXPLANATION-PHRASE STRING) ((PHRASEKEY KEYWORD) (MODIFIERS (CONS OF KEYWORD)) (AUDIENCE KEYWORD)))", ((cpp_function_code)(&lookupExplanationPhrase)), NULL);
    defineFunctionObject("REGISTER-JUSTIFICATION", "(DEFUN (REGISTER-JUSTIFICATION EXPLANATION-INFO) ((SELF JUSTIFICATION) (MAPPING EXPLANATION-MAPPING)))", ((cpp_function_code)(&registerJustification)), NULL);
    defineFunctionObject("GET-EXPLANATION-INFO", "(DEFUN (GET-EXPLANATION-INFO EXPLANATION-INFO) ((SELF JUSTIFICATION) (MAPPING EXPLANATION-MAPPING) (CREATE? BOOLEAN)))", ((cpp_function_code)(&getExplanationInfo)), NULL);
    defineFunctionObject("EXPLANATION-INFO", "(DEFUN (EXPLANATION-INFO EXPLANATION-INFO) ((SELF JUSTIFICATION) (MAPPING EXPLANATION-MAPPING)))", ((cpp_function_code)(&explanationInfo)), NULL);
    defineFunctionObject("LOOKUP-JUSTIFICATION", "(DEFUN (LOOKUP-JUSTIFICATION JUSTIFICATION) ((MAPPING EXPLANATION-MAPPING) (LABEL STRING)))", ((cpp_function_code)(&lookupJustification)), NULL);
    defineFunctionObject("RESET-MAPPING-FOR-SUBEXPLANATION", "(DEFUN RESET-MAPPING-FOR-SUBEXPLANATION ((MAPPING EXPLANATION-MAPPING)))", ((cpp_function_code)(&resetMappingForSubexplanation)), NULL);
    defineFunctionObject("PRINT-EXPLANATION", "(DEFUN (PRINT-EXPLANATION EXPLANATION-MAPPING) ((SELF JUSTIFICATION) (STREAM OUTPUT-STREAM) (MAPPING EXPLANATION-MAPPING) (MAXDEPTH INTEGER) (AUDIENCE KEYWORD)))", ((cpp_function_code)(&printExplanation)), NULL);
    defineFunctionObject("PRINT-EXPLANATION-SUPPORT", "(DEFUN PRINT-EXPLANATION-SUPPORT ((SELF JUSTIFICATION) (STREAM OUTPUT-STREAM) (MAPPING EXPLANATION-MAPPING) (MAXDEPTH INTEGER) (UNEXPLAINED (LIST OF JUSTIFICATION))))", ((cpp_function_code)(&printExplanationSupport)), NULL);
    defineFunctionObject("PRINT-ONE-EXPLANATION", "(DEFUN PRINT-ONE-EXPLANATION ((SELF JUSTIFICATION) (STREAM OUTPUT-STREAM) (MAPPING EXPLANATION-MAPPING) (MAXDEPTH INTEGER) (UNEXPLAINED (LIST OF JUSTIFICATION))))", ((cpp_function_code)(&printOneExplanation)), NULL);
    defineFunctionObject("PRINTING-JUSTIFICATION?", "(DEFUN (PRINTING-JUSTIFICATION? BOOLEAN) () :GLOBALLY-INLINE? TRUE (RETURN (DEFINED? *CURRENTJUSTIFICATION*)))", ((cpp_function_code)(&printingJustificationP)), NULL);
    defineFunctionObject("PRINT-JUSTIFICATION-PROPOSITION-FOR-FORMAT", "(DEFUN PRINT-JUSTIFICATION-PROPOSITION-FOR-FORMAT ((SELF JUSTIFICATION) (STREAM OUTPUT-STREAM) (INDENT INTEGER)))", ((cpp_function_code)(&printJustificationPropositionForFormat)), NULL);
    defineFunctionObject("PRINT-JUSTIFICATION-PROPOSITION", "(DEFUN PRINT-JUSTIFICATION-PROPOSITION ((SELF JUSTIFICATION) (STREAM OUTPUT-STREAM) (INDENT INTEGER)))", ((cpp_function_code)(&printJustificationProposition)), NULL);
    defineFunctionObject("PRINT-EXPLANATION-LABEL", "(DEFUN PRINT-EXPLANATION-LABEL ((STREAM OUTPUT-STREAM) (LABEL STRING) (HEAD? BOOLEAN)))", ((cpp_function_code)(&printExplanationLabel)), NULL);
    defineFunctionObject("PRINT-EXPLANATION-HEADER", "(DEFUN PRINT-EXPLANATION-HEADER ((SELF JUSTIFICATION) (STREAM OUTPUT-STREAM) (MAPPING EXPLANATION-MAPPING)))", ((cpp_function_code)(&printExplanationHeader)), NULL);
    defineFunctionObject("PRINT-EXPLANATION-TEXT", "(DEFUN PRINT-EXPLANATION-TEXT ((SELF JUSTIFICATION) (STREAM OUTPUT-STREAM) (MAPPING EXPLANATION-MAPPING)))", ((cpp_function_code)(&printExplanationText)), NULL);
    defineFunctionObject("MARK-AS-EXPLICIT-ASSERTION?", "(DEFUN (MARK-AS-EXPLICIT-ASSERTION? BOOLEAN) ((SELF JUSTIFICATION)))", ((cpp_function_code)(&markAsExplicitAssertionP)), NULL);
    defineFunctionObject("MARK-AS-FAILED-GOAL?", "(DEFUN (MARK-AS-FAILED-GOAL? BOOLEAN) ((SELF JUSTIFICATION)))", ((cpp_function_code)(&markAsFailedGoalP)), NULL);
    defineFunctionObject("MARK-AS-CUTOFF-GOAL?", "(DEFUN (MARK-AS-CUTOFF-GOAL? BOOLEAN) ((SELF JUSTIFICATION)))", ((cpp_function_code)(&markAsCutoffGoalP)), NULL);
    defineFunctionObject("PARTIALLY-FOLLOWS?", "(DEFUN (PARTIALLY-FOLLOWS? BOOLEAN) ((SELF JUSTIFICATION)))", ((cpp_function_code)(&partiallyFollowsP)), NULL);
    defineFunctionObject("MAKE-RULE-ORIGIN-EXPLANATION-PHRASE", "(DEFUN (MAKE-RULE-ORIGIN-EXPLANATION-PHRASE STRING) ((SELF JUSTIFICATION)))", ((cpp_function_code)(&makeRuleOriginExplanationPhrase)), NULL);
    defineFunctionObject("GET-EXPLANATION-SUBSTITUTION", "(DEFUN (GET-EXPLANATION-SUBSTITUTION ENTITY-MAPPING) ((SELF JUSTIFICATION)))", ((cpp_function_code)(&getExplanationSubstitution)), NULL);
    defineFunctionObject("PRINT-ONE-VARIABLE-SUBSTITUTION", "(DEFUN PRINT-ONE-VARIABLE-SUBSTITUTION ((STREAM OUTPUT-STREAM) (VAR OBJECT) (VALUE OBJECT)))", ((cpp_function_code)(&printOneVariableSubstitution)), NULL);
    defineFunctionObject("PRINT-EXPLANATION-SUBSTITUTION", "(DEFUN PRINT-EXPLANATION-SUBSTITUTION ((SELF JUSTIFICATION) (STREAM OUTPUT-STREAM) (MAPPING EXPLANATION-MAPPING)))", ((cpp_function_code)(&printExplanationSubstitution)), NULL);
    defineFunctionObject("PRINT-EXPLANATION-ANTECEDENTS", "(DEFUN PRINT-EXPLANATION-ANTECEDENTS ((SELF JUSTIFICATION) (STREAM OUTPUT-STREAM) (MAPPING EXPLANATION-MAPPING) (MAXDEPTH INTEGER) (UNEXPLAINED (LIST OF JUSTIFICATION))))", ((cpp_function_code)(&printExplanationAntecedents)), NULL);
    defineFunctionObject("VISIBLE-JUSTIFICATION", "(DEFUN (VISIBLE-JUSTIFICATION JUSTIFICATION) ((SELF JUSTIFICATION)))", ((cpp_function_code)(&visibleJustification)), NULL);
    defineFunctionObject("VISIBLE-ANTECEDENTS", "(DEFUN (VISIBLE-ANTECEDENTS (LIST OF JUSTIFICATION)) ((SELF JUSTIFICATION)))", ((cpp_function_code)(&visibleAntecedents)), NULL);
    defineFunctionObject("COLLECT-VISIBLE-ANTECEDENTS", "(DEFUN COLLECT-VISIBLE-ANTECEDENTS ((SELF JUSTIFICATION) (VISIBLEANTECEDENTS (LIST OF JUSTIFICATION))))", ((cpp_function_code)(&collectVisibleAntecedents)), NULL);
    defineFunctionObject("WHY", "(DEFUN WHY (|&REST| (ARGS OBJECT)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Print an explanation for the result of the most recent query.\nWithout any arguments, `why' prints an explanation of the top level\nquery proposition down to a maximum depth of 3.  `(why all)' prints\nan explanation to unlimited depth.  Alternatively, a particular depth\ncan be specified, for example, `(why 5)' explains down to a depth of 5.\nA proof step that was not explained explicitly (e.g., due to a depth\ncutoff) can be explained by supplying the label of the step as the\nfirst argument to `why', for example, `(why 1.2.3 5)' prints an explanation\nstarting at 1.2.3 down to a depth of 5 (which is counted relative to the\ndepth of the starting point).  The keywords `brief' and `verbose' can be\nused to select a particular explanation style.  In brief mode, explicitly\nasserted propositions are not further explained and indicated with a\n`!' assertion marker.  Additionally, relatively uninteresting " "proof steps\nsuch as AND-introductions are skipped.  This explanation style option is\nsticky and will affect future calls to `why' until it gets changed again.\nThe various options can be combined in any way, for example,\n`(why 1.2.3 brief 3)' explains starting from step 1.2.3 down to a depth\nof 3 in brief explanation mode.\")", ((cpp_function_code)(&why)), ((cpp_function_code)(&whyEvaluatorWrapper)));
    defineFunctionObject("EXPLAIN-WHY", "(DEFUN EXPLAIN-WHY ((LABEL STRING) (STYLE KEYWORD) (MAXDEPTH INTEGER) (STREAM OUTPUT-STREAM)) :PUBLIC? TRUE :DOCUMENTATION \"Programmer's interface to WHY function.\")", ((cpp_function_code)(&explainWhy)), NULL);
    defineFunctionObject("EXPLAIN-PROPOSITION", "(DEFUN EXPLAIN-PROPOSITION ((PROP PROPOSITION) (STYLE KEYWORD) (MAXDEPTH INTEGER) (STREAM OUTPUT-STREAM)) :PUBLIC? TRUE :DOCUMENTATION \"Print an explanation for `prop' if there is one.  This will only happen\nfor forward-chained propositions.\")", ((cpp_function_code)(&explainProposition)), NULL);
    defineFunctionObject("GET-WHY-JUSTIFICATION", "(DEFUN (GET-WHY-JUSTIFICATION JUSTIFICATION) ((LABEL STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the current WHY justification.  May also throw one of the\nfollowing subtypes of EXPLAIN-EXCEPTION:\n   EXPLAIN-NO-QUERY-EXCEPTION\n   EXPLAIN-NO-SOLUTION-EXCEPTION\n   EXPLAIN-NO-MORE-SOLUTIONS-EXCEPTION\n   EXPLAIN-NOT-ENABLED-EXCEPTION\n   EXPLAIN-NO-SUCH-LABEL-EXCEPTION\n   EXPLAIN-QUERY-TRUE-EXCEPTION\")", ((cpp_function_code)(&getWhyJustification)), NULL);
    defineFunctionObject("COMMAND-OPTION-EQL?", "(DEFUN (COMMAND-OPTION-EQL? BOOLEAN) ((ARG OBJECT) (OPTION STRING)))", ((cpp_function_code)(&commandOptionEqlP)), NULL);
    defineFunctionObject("PARSE-WHY-ARGUMENTS", "(DEFUN (PARSE-WHY-ARGUMENTS STRING KEYWORD INTEGER BOOLEAN) ((ARGS (CONS OF OBJECT))))", ((cpp_function_code)(&parseWhyArguments)), NULL);
    defineFunctionObject("STARTUP-EXPLANATIONS", "(DEFUN STARTUP-EXPLANATIONS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupExplanations)), NULL);
    { MethodSlot* function = lookupFunction(SYM_EXPLANATIONS_LOGIC_STARTUP_EXPLANATIONS);

      setDynamicSlotValue(function->dynamicSlots, SYM_EXPLANATIONS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupExplanations"), NULL_STRING_WRAPPER);
    }
  }
}

void startupExplanations() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupExplanations1();
    }
    if (currentStartupTimePhaseP(4)) {
      oEXPLANATION_FORMATo = KWD_EXPLANATIONS_ASCII;
      oEXPLANATION_STYLEo = KWD_EXPLANATIONS_BRIEF;
      oEXPLANATION_AUDIENCEo = KWD_EXPLANATIONS_TECHNICAL;
      oEXPLANATION_VOCABULARIESo = newKeyValueList();
    }
    if (currentStartupTimePhaseP(5)) {
      helpStartupExplanations2();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupExplanations3();
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFSPECIAL *EXPLANATION-FORMAT* KEYWORD :ASCII :DOCUMENTATION \"Keyword to control the explanation format.\nValid values are :ASCII, :HTML and :XML\")", &oEXPLANATION_FORMATo);
      defineGlobalVariableObject("(DEFSPECIAL *EXPLANATION-STYLE* KEYWORD :BRIEF :DOCUMENTATION \"Keywords that controls how detailed explanations will be.\nValid values are :VERBOSE and :BRIEF.\" :PUBLIC? TRUE)", &oEXPLANATION_STYLEo);
      defineGlobalVariableObject("(DEFSPECIAL *EXPLANATION-AUDIENCE* KEYWORD :TECHNICAL :DOCUMENTATION \"Keywords that controls the language for justifications.\nValid values are :TECHNICAL and :LAY\" :PUBLIC? TRUE)", &oEXPLANATION_AUDIENCEo);
      defineGlobalVariableObject("(DEFGLOBAL *DEFAULT-EXPLANATION-DEPTH* INTEGER 3 :DOCUMENTATION \"Maximal explanation depth used if not otherwise specified.\" :PUBLIC? TRUE)", &oDEFAULT_EXPLANATION_DEPTHo);
      defineGlobalVariableObject("(DEFGLOBAL *EXPLANATION-TAB-STRING* STRING \"    \")", &oEXPLANATION_TAB_STRINGo);
      defineGlobalVariableObject("(DEFGLOBAL *MAX-INLINE-LABEL-LENGTH* INTEGER 10 :DOCUMENTATION \"Maximum length of a label string for which the following\nproposition will be printed on the same line.\")", &oMAX_INLINE_LABEL_LENGTHo);
      defineGlobalVariableObject("(DEFGLOBAL *EXPLANATION-ASSERTION-MARKER* STRING \"!\")", &oEXPLANATION_ASSERTION_MARKERo);
      defineGlobalVariableObject("(DEFGLOBAL *EXPLANATION-FAILURE-MARKER* STRING \"?\")", &oEXPLANATION_FAILURE_MARKERo);
      defineGlobalVariableObject("(DEFGLOBAL *EXPLANATION-CUTOFF-MARKER* STRING \"x\")", &oEXPLANATION_CUTOFF_MARKERo);
      defineGlobalVariableObject("(DEFGLOBAL *EXPLANATION-INFERENCE-MARKER* STRING \" \")", &oEXPLANATION_INFERENCE_MARKERo);
      defineGlobalVariableObject("(DEFSPECIAL *EXPLANATION-VOCABULARY* EXPLANATION-VOCABULARY NULL :DOCUMENTATION \"The currently active vocabulary lookup table\")", &oEXPLANATION_VOCABULARYo);
      defineGlobalVariableObject("(DEFGLOBAL *EXPLANATION-VOCABULARIES* (KEY-VALUE-LIST OF KEYWORD EXPLANATION-VOCABULARY) (NEW KEY-VALUE-LIST) :DOCUMENTATION \"List of vocabularies with keyword keys\")", &oEXPLANATION_VOCABULARIESo);
      defineExplanationPhrase(KWD_EXPLANATIONS_UNKNOWN_RULE, KWD_EXPLANATIONS_TECHNICAL, "because of an inference PowerLoom can't explain yet", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_FOLLOWS, KWD_EXPLANATIONS_TECHNICAL, "follows", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_FOLLOWS, KWD_EXPLANATIONS_LAY, "is true", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_FOLLOWS, KWD_EXPLANATIONS_TECHNICAL, "is partially true", 1, KWD_EXPLANATIONS_PARTIAL);
      defineExplanationPhrase(KWD_EXPLANATIONS_FOLLOWS, KWD_EXPLANATIONS_LAY, "is true to some part", 1, KWD_EXPLANATIONS_PARTIAL);
      defineExplanationPhrase(KWD_EXPLANATIONS_HOLDS, KWD_EXPLANATIONS_TECHNICAL, "holds", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_HOLDS, KWD_EXPLANATIONS_LAY, "is true", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_DEFINITION, KWD_EXPLANATIONS_TECHNICAL, "by the definition of", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_DEFINITION, KWD_EXPLANATIONS_LAY, "by the definition of", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_FAILED, KWD_EXPLANATIONS_TECHNICAL, "failed", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_FAILED, KWD_EXPLANATIONS_LAY, "could not be proven", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_INCONSISTENT, KWD_EXPLANATIONS_TECHNICAL, "is inconsistent", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_INCONSISTENT, KWD_EXPLANATIONS_LAY, "has a contradiction", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_CLASH, KWD_EXPLANATIONS_TECHNICAL, "because it and its negation were inferred", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_CLASH, KWD_EXPLANATIONS_LAY, "because opposite conclusions were reached", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_NOT_ASSERTED, KWD_EXPLANATIONS_TECHNICAL, "is not asserted", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_NOT_ASSERTED, KWD_EXPLANATIONS_LAY, "is not asserted to be true", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_NO_RULES, KWD_EXPLANATIONS_TECHNICAL, "no potential inference leading to the proposition could be found", 0);
      defineExplanationPhrase(KWD_EXPLANATIONS_NO_RULES, KWD_EXPLANATIONS_LAY, "no rules for proving the proposition could be found", 0);
      defineGlobalVariableObject("(DEFSPECIAL *CURRENTJUSTIFICATION* JUSTIFICATION NULL)", &oCURRENTJUSTIFICATIONo);
      defineGlobalVariableObject("(DEFSPECIAL *MOST-RECENT-EXPLANATION-MAPPING* EXPLANATION-MAPPING NULL)", &oMOST_RECENT_EXPLANATION_MAPPINGo);
    }
  }
}

Keyword* KWD_EXPLANATIONS_ASCII = NULL;

Keyword* KWD_EXPLANATIONS_BRIEF = NULL;

Keyword* KWD_EXPLANATIONS_TECHNICAL = NULL;

Keyword* KWD_EXPLANATIONS_ASSERTION = NULL;

Keyword* KWD_EXPLANATIONS_FAILURE = NULL;

Keyword* KWD_EXPLANATIONS_CUTOFF = NULL;

Keyword* KWD_EXPLANATIONS_INFERENCE = NULL;

Keyword* KWD_EXPLANATIONS_HTML = NULL;

Keyword* KWD_EXPLANATIONS_IMPLIES = NULL;

Symbol* SYM_EXPLANATIONS_LOGIC_EXPLANATION_VOCABULARY = NULL;

Keyword* KWD_EXPLANATIONS_UNKNOWN_RULE = NULL;

Keyword* KWD_EXPLANATIONS_FOLLOWS = NULL;

Keyword* KWD_EXPLANATIONS_LAY = NULL;

Keyword* KWD_EXPLANATIONS_PARTIAL = NULL;

Keyword* KWD_EXPLANATIONS_HOLDS = NULL;

Keyword* KWD_EXPLANATIONS_DEFINITION = NULL;

Keyword* KWD_EXPLANATIONS_FAILED = NULL;

Keyword* KWD_EXPLANATIONS_INCONSISTENT = NULL;

Keyword* KWD_EXPLANATIONS_CLASH = NULL;

Keyword* KWD_EXPLANATIONS_NOT_ASSERTED = NULL;

Keyword* KWD_EXPLANATIONS_NO_RULES = NULL;

Surrogate* SGT_EXPLANATIONS_LOGIC_EXPLANATION_INFO = NULL;

Symbol* SYM_EXPLANATIONS_STELLA_LABEL = NULL;

Symbol* SYM_EXPLANATIONS_STELLA_DEPTH = NULL;

Symbol* SYM_EXPLANATIONS_LOGIC_EXPLAINEDp = NULL;

Symbol* SYM_EXPLANATIONS_LOGIC_EXPLANATION_MAPPING = NULL;

Keyword* KWD_EXPLANATIONS_XML = NULL;

Keyword* KWD_EXPLANATIONS_CYC_NL = NULL;

Keyword* KWD_EXPLANATIONS_KIF_ONTOSAURUS = NULL;

Keyword* KWD_EXPLANATIONS_JAVA_GUI_HTML = NULL;

Keyword* KWD_EXPLANATIONS_REALISTIC = NULL;

Symbol* SYM_EXPLANATIONS_STELLA_NOT = NULL;

Keyword* KWD_EXPLANATIONS_AMPLIFICATION = NULL;

Keyword* KWD_EXPLANATIONS_REVERSE = NULL;

Surrogate* SGT_EXPLANATIONS_LOGIC_CLASH_JUSTIFICATION = NULL;

Keyword* KWD_EXPLANATIONS_PRIMITIVE_STRATEGY = NULL;

Keyword* KWD_EXPLANATIONS_SCAN_PROPOSITIONS = NULL;

Symbol* SYM_EXPLANATIONS_LOGIC_MASTER_PROPOSITION = NULL;

Keyword* KWD_EXPLANATIONS_FORWARD = NULL;

Keyword* KWD_EXPLANATIONS_SCAN_COLLECTION = NULL;

Keyword* KWD_EXPLANATIONS_LOOKUP_ASSERTIONS = NULL;

Keyword* KWD_EXPLANATIONS_EQUIVALENCE = NULL;

Symbol* SYM_EXPLANATIONS_LOGIC_COMPLEMENT_DESCRIPTION = NULL;

Surrogate* SGT_EXPLANATIONS_LOGIC_NAMED_DESCRIPTION = NULL;

Surrogate* SGT_EXPLANATIONS_LOGIC_FORWARD_JUSTIFICATION = NULL;

Surrogate* SGT_EXPLANATIONS_LOGIC_ALTERNATIVE_BINDINGS_SET = NULL;

Keyword* KWD_EXPLANATIONS_MODUS_PONENS = NULL;

Keyword* KWD_EXPLANATIONS_MODUS_TOLLENS = NULL;

Keyword* KWD_EXPLANATIONS_DISPROOF = NULL;

Keyword* KWD_EXPLANATIONS_GOAL_COMPLEMENT = NULL;

Keyword* KWD_EXPLANATIONS_PATTERN = NULL;

Keyword* KWD_EXPLANATIONS_AND_INTRODUCTION = NULL;

Symbol* SYM_EXPLANATIONS_LOGIC_JUSTIFICATION = NULL;

Surrogate* SGT_EXPLANATIONS_STELLA_GENERALIZED_SYMBOL = NULL;

Keyword* KWD_EXPLANATIONS_DIGIT = NULL;

Keyword* KWD_EXPLANATIONS_VERBOSE = NULL;

Keyword* KWD_EXPLANATIONS_DEPTH = NULL;

Symbol* SYM_EXPLANATIONS_LOGIC_STARTUP_EXPLANATIONS = NULL;

Symbol* SYM_EXPLANATIONS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
