//  -*- Mode: C++ -*-

// kif-in.cc

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

char symbolTypeCharacter(Object* symbol) {
  if (subtypeOfSymbolP(safePrimaryType(symbol))) {
    { Object* symbol000 = symbol;
      Symbol* symbol = ((Symbol*)(symbol000));

      { const char* name = symbol->symbolName;

        if (!stringEqlP(name, "")) {
          return (name[0]);
        }
      }
    }
  }
  else {
  }
  return (NULL_CHARACTER);
}

boolean questionMarkSymbolP(Object* symbol) {
  return (symbolTypeCharacter(symbol) == '?');
}

boolean sequenceVariableSymbolP(Object* self) {
  self = self;
  return (false);
}

// Character that identifies variables representing
// instances named by the system.
char oAUTOMATIC_INSTANCE_CHARACTERo = '$';

boolean automaticInstanceSymbolP(Object* symbol) {
  return (symbolTypeCharacter(symbol) == oAUTOMATIC_INSTANCE_CHARACTERo);
}

GeneralizedSymbol* kifSymbolToStellaSymbol(Symbol* symbol) {
  if (questionMarkSymbolP(symbol) ||
      automaticInstanceSymbolP(symbol)) {
    return (symbol);
  }
  else {
    return (coerceToBoundOrLocalSurrogate(symbol));
  }
}

Symbol* kifVariableToStellaVariable(Object* variable) {
  if (subtypeOfSymbolP(safePrimaryType(variable))) {
    { Object* variable000 = variable;
      Symbol* variable = ((Symbol*)(variable000));

      if (!questionMarkSymbolP(variable)) {
        { OutputStringStream* stream000 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream000->nativeStream) << "PARSING ERROR: " << "Missing question mark on KIF variable: " << "`" << variable << "'" << "." << std::endl;
            helpSignalPropositionError(stream000, KWD_KIF_IN_ERROR);
          }
          throw *newParsingError(stream000->theStringReader());
        }
      }
      return (((Symbol*)(kifSymbolToStellaSymbol(variable))));
    }
  }
  else {
    { OutputStringStream* stream001 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream001->nativeStream) << "PARSING ERROR: " << "Illegal value in KIF expression where symbol expected " << "`" << variable << "'" << "." << std::endl;
        helpSignalPropositionError(stream001, KWD_KIF_IN_ERROR);
      }
      throw *newParsingError(stream001->theStringReader());
    }
  }
}

boolean kifVariableDeclarationP(Object* tree) {
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (testValue000 == SGT_KIF_IN_STELLA_CONS) {
      { Object* tree000 = tree;
        Cons* tree = ((Cons*)(tree000));

        switch (tree->length()) {
          case 1: 
            return (questionMarkSymbolP(tree->value));
          case 2: 
            return (questionMarkSymbolP(tree->value) &&
                (symbolP(tree->rest->value) &&
                 (!questionMarkSymbolP(tree->rest->value))));
          default:
            return (false);
        }
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* tree001 = tree;
        Symbol* tree = ((Symbol*)(tree001));

        if (questionMarkSymbolP(tree)) {
          return (true);
        }
      }
    }
    else {
      return (false);
    }
  }
  return (false);
}

Object* oneKifVariableDeclarationToStella(Object* tree) {
  if (!kifVariableDeclarationP(tree)) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "PARSING ERROR: " << "Illegal KIF variable declaration: " << "`" << tree << "'" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_KIF_IN_ERROR);
      }
      throw *newParsingError(stream000->theStringReader());
    }
  }
  if (safePrimaryType(tree) == SGT_KIF_IN_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      tree->firstSetter(kifVariableToStellaVariable(tree->value));
      if (((boolean)(tree->rest->value))) {
        {
          tree->secondSetter(kifSymbolToStellaSymbol(((Symbol*)(tree->rest->value))));
          return (cons(SYM_KIF_IN_STELLA_ISA, tree->concatenate(NIL, 0)));
        }
      }
      else {
        return (kifVariableToStellaVariable(tree->value));
      }
    }
  }
  else {
    return (kifVariableToStellaVariable(tree));
  }
}

boolean stellaVariableDeclarationsP(Object* tree) {
  if (safePrimaryType(tree) == SGT_KIF_IN_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if ((tree->value == SYM_KIF_IN_STELLA_ISA) ||
          (consP(tree->value) &&
           (((Cons*)(tree->value))->value == SYM_KIF_IN_STELLA_ISA))) {
        return (true);
      }
    }
  }
  else {
  }
  return (false);
}

Cons* kifVariableDeclarationsToStella(Object* tree, boolean errorP) {
  if (stellaVariableDeclarationsP(tree)) {
    {
      return (((Cons*)(tree)));
    }
  }
  else {
    if (kifVariableDeclarationP(tree)) {
      {
        return (cons(oneKifVariableDeclarationToStella(tree), NIL));
      }
    }
    else {
      { boolean testValue000 = false;

        testValue000 = consP(tree);
        if (testValue000) {
          { boolean alwaysP000 = true;

            { Object* d = NULL;
              Cons* iter000 = ((Cons*)(tree));

              for (; !(iter000 == NIL); iter000 = iter000->rest) {
                d = iter000->value;
                if (!kifVariableDeclarationP(d)) {
                  alwaysP000 = false;
                  break;
                }
              }
            }
            testValue000 = alwaysP000;
          }
        }
        if (testValue000) {
          {
            { ConsIterator* it = ((Cons*)(tree))->allocateIterator();

              for (; it->nextP(); ) {
                it->valueSetter(oneKifVariableDeclarationToStella(it->value));
              }
            }
            return (((Cons*)(tree)));
          }
        }
        else {
          {
            if (errorP) {
              { OutputStringStream* stream000 = newOutputStringStream();

                { 
                  BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                  *(stream000->nativeStream) << "PARSING ERROR: " << "Illegal declaration syntax: " << "`" << tree << "'" << "." << std::endl;
                  helpSignalPropositionError(stream000, KWD_KIF_IN_ERROR);
                }
                throw *newParsingError(stream000->theStringReader());
              }
            }
            return (NULL);
          }
        }
      }
    }
  }
}

boolean kifQuantifierSymbolP(Symbol* self) {
  if ((self == SYM_KIF_IN_STELLA_EXISTS) ||
      ((self == SYM_KIF_IN_STELLA_FORALL) ||
       ((self == SYM_KIF_IN_LOGIC_SETOFALL) ||
        ((self == SYM_KIF_IN_LOGIC_KAPPA) ||
         (self == SYM_KIF_IN_LOGIC_THE))))) {
    return (true);
  }
  else {
    return (false);
  }
}

Cons* kifTheToStellaTheOnly(Cons* tree) {
  tree = kifSetofallToStellaSetofall(tree);
  tree->firstSetter(SYM_KIF_IN_LOGIC_THE_ONLY);
  return (tree);
}

Cons* kifSetofallToStellaSetofall(Cons* tree) {
  if (!((tree->length() == 3) ||
      (tree->length() == 2))) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "PARSING ERROR: " << "Illegal " << "`" << tree->value << "'" << " tree: " << "`" << tree << "'" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_KIF_IN_ERROR);
      }
      throw *newParsingError(stream000->theStringReader());
    }
  }
  { Cons* declarations = kifVariableDeclarationsToStella(tree->rest->value, false);

    if (!((boolean)(declarations))) {
      declarations = ((Cons*)(kifTermToUntypedStellaTerm(tree->rest->value)));
    }
    else if (declarations->length() > 1) {
      { OutputStringStream* stream001 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream001->nativeStream) << "PARSING ERROR: " << "Too many declarations in SETOFALL expression" << "." << std::endl;
          helpSignalPropositionError(stream001, KWD_KIF_IN_ERROR);
        }
        throw *newParsingError(stream001->theStringReader());
      }
    }
    tree->secondSetter(declarations);
  }
  if (((boolean)(tree->rest->rest->value))) {
    tree->thirdSetter(kifSentenceToUntypedStellaSentence(tree->rest->rest->value));
  }
  return (tree);
}

Cons* kifKappaToStellaKappa(Cons* tree) {
  if (!(tree->length() >= 2)) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "PARSING ERROR: " << "Illegal KAPPA tree: " << "`" << tree << "'" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_KIF_IN_ERROR);
      }
      throw *newParsingError(stream000->theStringReader());
    }
  }
  { Cons* sentences = tree->rest->rest;

    tree->secondSetter(kifVariableDeclarationsToStella(tree->rest->value, true));
    { ConsIterator* it = sentences->allocateIterator();

      for (; it->nextP(); ) {
        it->valueSetter(kifSentenceToUntypedStellaSentence(it->value));
      }
    }
    switch (sentences->length()) {
      case 0: 
        tree->rest->rest = cons(SYM_KIF_IN_STELLA_TRUE, NIL);
        break;
      case 1: 
        tree->thirdSetter(tree->rest->rest->value);
        break;
      default:
        tree->rest->rest = cons(cons(SYM_KIF_IN_STELLA_AND, sentences->concatenate(NIL, 0)), NIL);
        break;
    }
    return (tree);
  }
}

Cons* kifLambdaToStellaKappa(Cons* tree) {
  { Symbol* valuevariable = gensym("?v");
    Cons* variables = ((Cons*)(tree->rest->value));
    Object* term = tree->rest->rest->value;
    boolean openquantifierP = (variables->length() == 2) &&
        (!questionMarkSymbolP(variables->rest->value));

    if (openquantifierP) {
      variables = cons(variables, NIL);
    }
    return (listO(4, SYM_KIF_IN_LOGIC_KAPPA, variables->concatenate(cons(valuevariable, NIL), 0), listO(3, SYM_KIF_IN_STELLA_e, valuevariable, cons(term, NIL)), NIL));
  }
}

Cons* kifCondToIf(Cons* conditions) {
  if (conditions == NIL) {
    return (NIL);
  }
  else {
    {
      if (!(consP(conditions->value) &&
          (!(((Cons*)(conditions->value))->rest->value == NIL)))) {
        { OutputStringStream* stream000 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream000->nativeStream) << "PARSING ERROR: " << "Illegal condition in 'COND': " << "`" << conditions->value << "'" << "." << std::endl;
            helpSignalPropositionError(stream000, KWD_KIF_IN_ERROR);
          }
          throw *newParsingError(stream000->theStringReader());
        }
      }
      { Cons* firstcondition = ((Cons*)(conditions->value));
        Cons* valueterm = kifCondToIf(conditions->rest);

        if (!(valueterm == NIL)) {
          valueterm = consList(1, valueterm);
        }
        return (listO(3, SYM_KIF_IN_STELLA_IF, ((Cons*)(firstcondition->value)), cons(((Cons*)(firstcondition->rest->value)), valueterm->concatenate(NIL, 0))));
      }
    }
  }
}

Object* kifInvertSentence(Object* tree) {
  if (consP(tree) &&
      (((Cons*)(tree))->value == SYM_KIF_IN_STELLA_NOT)) {
    return (((Cons*)(tree))->rest->value);
  }
  else {
    return (listO(3, SYM_KIF_IN_STELLA_NOT, tree, NIL));
  }
}

Cons* kifImpliesToOrNot(Cons* tree) {
  if (tree->length() < 2) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "PARSING ERROR: " << "Illegal implication tree: " << "`" << tree << "'" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_KIF_IN_ERROR);
      }
      throw *newParsingError(stream000->theStringReader());
    }
  }
  if (((GeneralizedSymbol*)(tree->value)) == SYM_KIF_IN_STELLA_le) {
    tree->rest = tree->rest->reverse();
  }
  else {
  }
  changeKifExpressionsToStellaExpressions(tree->rest, false);
  tree->firstSetter(SYM_KIF_IN_STELLA_OR);
  switch (tree->length()) {
    case 2: 
      return (((Cons*)(tree->rest->value)));
    case 3: 
      tree->secondSetter(kifInvertSentence(tree->rest->value));
      return (tree);
    default:
      tree->rest = tree->rest->reverse();
      tree->rest->rest = cons(cons(SYM_KIF_IN_STELLA_AND, tree->rest->rest->reverse()->concatenate(NIL, 0)), NIL);
      tree->rest = tree->rest->reverse();
      tree->secondSetter(kifInvertSentence(tree->rest->value));
      return (tree);
  }
}

Cons* kifBiconditionalToTwoImplies(Cons* tree) {
  if (tree->length() > 3) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "PARSING ERROR: " << "Too many arguments to <=>: " << "`" << tree << "'" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_KIF_IN_ERROR);
      }
      throw *newParsingError(stream000->theStringReader());
    }
  }
  { Cons* copy = ((Cons*)(copyConsTree(tree)));
    Object* arrow = tree->value;
    Symbol* forwardarrow = SYM_KIF_IN_STELLA_eg;
    Symbol* backwardarrow = SYM_KIF_IN_STELLA_le;

    { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(arrow));

      if (testValue000 == SYM_KIF_IN_LOGIC_legg) {
        forwardarrow = SYM_KIF_IN_LOGIC_egg;
      }
      else if (testValue000 == SYM_KIF_IN_LOGIC_lleg) {
        backwardarrow = SYM_KIF_IN_LOGIC_lle;
      }
      else if (testValue000 == SYM_KIF_IN_LOGIC_llegg) {
        forwardarrow = SYM_KIF_IN_LOGIC_egg;
        backwardarrow = SYM_KIF_IN_LOGIC_lle;
      }
      else if (testValue000 == SYM_KIF_IN_LOGIC_ltg) {
        forwardarrow = SYM_KIF_IN_LOGIC_tg;
        backwardarrow = SYM_KIF_IN_LOGIC_lt;
      }
      else if (testValue000 == SYM_KIF_IN_LOGIC_ltgg) {
        forwardarrow = SYM_KIF_IN_LOGIC_tgg;
        backwardarrow = SYM_KIF_IN_LOGIC_lt;
      }
      else if (testValue000 == SYM_KIF_IN_LOGIC_lltg) {
        forwardarrow = SYM_KIF_IN_LOGIC_tg;
        backwardarrow = SYM_KIF_IN_LOGIC_llt;
      }
      else if (testValue000 == SYM_KIF_IN_LOGIC_lltgg) {
        forwardarrow = SYM_KIF_IN_LOGIC_tgg;
        backwardarrow = SYM_KIF_IN_LOGIC_llt;
      }
      else {
      }
    }
    copy->firstSetter(forwardarrow);
    tree->firstSetter(backwardarrow);
    return (listO(3, SYM_KIF_IN_STELLA_AND, tree, cons(copy, NIL)));
  }
}

Cons* kifExistsToStellaExists(Cons* tree) {
  if ((tree->length() < 3) ||
      (tree->length() > 4)) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "PARSING ERROR: " << "Illegal EXISTS tree: " << "`" << tree << "'" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_KIF_IN_ERROR);
      }
      throw *newParsingError(stream000->theStringReader());
    }
  }
  { Object* sentence1 = kifSentenceToUntypedStellaSentence(tree->rest->rest->value);
    Object* sentence2 = kifSentenceToUntypedStellaSentence(tree->fourth());

    tree->secondSetter(kifVariableDeclarationsToStella(tree->rest->value, true));
    if (((boolean)(sentence2))) {
      return (listO(3, SYM_KIF_IN_STELLA_EXISTS, tree->rest->value, cons(listO(3, SYM_KIF_IN_STELLA_AND, sentence1, cons(sentence2, NIL)), NIL)));
    }
    tree->thirdSetter(sentence1);
    return (tree);
  }
}

Cons* kifThreeArgumentForallToStellaForall(Cons* tree, Cons* declarations) {
  { Object* antecedent = kifSentenceToUntypedStellaSentence(tree->rest->rest->value);
    Object* consequent = kifSentenceToUntypedStellaSentence(tree->fourth());

    return (listO(3, SYM_KIF_IN_STELLA_FORALL, declarations, cons(antecedent, cons(consequent, NIL))));
  }
}

Cons* kifTwoArgumentForallToStellaForall(Cons* tree, Cons* declarations) {
  { Object* sentence = kifSentenceToUntypedStellaSentence(tree->rest->rest->value);

    if (safePrimaryType(sentence) == SGT_KIF_IN_STELLA_CONS) {
      { Object* sentence000 = sentence;
        Cons* sentence = ((Cons*)(sentence000));

        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(sentence->value));

          if (testValue000 == SYM_KIF_IN_STELLA_AND) {
            { Cons* foralls = NIL;

              { Object* conjunct = NULL;
                Cons* iter000 = sentence->rest;

                for (; !(iter000 == NIL); iter000 = iter000->rest) {
                  conjunct = iter000->value;
                  foralls = cons(listO(3, SYM_KIF_IN_STELLA_FORALL, copyConsTree(tree->rest->value), cons(conjunct, NIL)), foralls);
                }
              }
              return (((Cons*)(kifSentenceToUntypedStellaSentence(cons(SYM_KIF_IN_STELLA_AND, foralls->concatenate(NIL, 0))))));
            }
          }
          else if (testValue000 == SYM_KIF_IN_STELLA_OR) {
            { Object* antecedent = kifInvertSentence(sentence->rest->value);
              Object* consequent = sentence->rest->rest->value;

              return (listO(3, SYM_KIF_IN_STELLA_FORALL, declarations, cons(antecedent, cons(consequent, NIL))));
            }
          }
          else if (testValue000 == SYM_KIF_IN_STELLA_FORALL) {
            { Object* v = NULL;
              Cons* iter001 = declarations;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                v = iter001->value;
                sentence->secondSetter(cons(v, ((Cons*)(sentence->rest->value))));
              }
            }
            return (sentence);
          }
          else if (testValue000 == SYM_KIF_IN_LOGIC_ABOUT) {
            return (listO(3, SYM_KIF_IN_LOGIC_ABOUT, kifSentenceToUntypedStellaSentence(listO(3, SYM_KIF_IN_STELLA_FORALL, declarations, cons(sentence->rest->value, NIL))), sentence->rest->rest->concatenate(NIL, 0)));
          }
          else {
          }
        }
      }
    }
    else {
    }
    return (listO(3, SYM_KIF_IN_STELLA_FORALL, declarations, listO(3, SYM_KIF_IN_STELLA_TRUE, sentence, NIL)));
  }
}

Cons* kifForallToStellaForall(Cons* tree) {
  if ((tree->length() < 3) ||
      (tree->length() > 4)) {
    { OutputStringStream* stream000 = newOutputStringStream();

      { 
        BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
        *(stream000->nativeStream) << "PARSING ERROR: " << "Illegal FORALL tree: " << "`" << tree << "'" << "." << std::endl;
        helpSignalPropositionError(stream000, KWD_KIF_IN_ERROR);
      }
      throw *newParsingError(stream000->theStringReader());
    }
  }
  { Cons* declarations = kifVariableDeclarationsToStella(tree->rest->value, true);

    switch (tree->length()) {
      case 3: 
        return (kifTwoArgumentForallToStellaForall(tree, declarations));
      case 4: 
        return (kifThreeArgumentForallToStellaForall(tree, declarations));
      default:
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "`" << tree->length() << "'" << " is not a valid case option";
          throw *newStellaException(stream001->theStringReader());
        }
        break;
    }
  }
}

Cons* kifPredicationToStellaPredication(Cons* tree) {
  { Symbol* operatoR = kifOperatorToInternalStella(((Symbol*)(tree->value)));
    Cons* arguments = tree->rest;

    tree->firstSetter(operatoR);
    changeKifExpressionsToStellaExpressions(arguments, true);
    return (tree);
  }
}

Cons* helpTransformKifFunction(Object* arg1, Object* arg2) {
  if (!consP(arg1)) {
    if (safePrimaryType(arg2) == SGT_KIF_IN_STELLA_CONS) {
      { Object* arg2000 = arg2;
        Cons* arg2 = ((Cons*)(arg2000));

        if (!termKifSpecialFormP(arg2->value)) {
          return (arg2->concatenate(cons(arg1, NIL), 0));
        }
      }
    }
    else {
    }
  }
  return (NULL);
}

Cons* kifEqualityToStellaEquality(Cons* tree) {
  if (tree->length() == 3) {
    { Cons* functiontree = NULL;
      Object* arg1 = tree->rest->value;
      Object* arg2 = tree->rest->rest->value;

      { boolean testValue000 = false;

        { 
          functiontree = helpTransformKifFunction(arg1, arg2);
          testValue000 = ((boolean)(functiontree));
        }
        if (!testValue000) {
          { 
            functiontree = helpTransformKifFunction(arg2, arg1);
            testValue000 = ((boolean)(functiontree));
          }
        }
        if (testValue000) {
          if (consP(functiontree->value)) {
            functiontree = cons(SYM_KIF_IN_PL_KERNEL_KB_VALUE, functiontree);
          }
          functiontree->firstSetter(kifOperatorToInternalStella(((Symbol*)(functiontree->value))));
          changeKifExpressionsToStellaExpressions(functiontree->rest, true);
          return (functiontree);
        }
      }
    }
  }
  changeKifExpressionsToStellaExpressions(tree->rest, true);
  return (tree);
}

Symbol* kifOperatorToInternalStella(Symbol* operatoR) {
  return (operatoR);
}

Symbol* internalStellaOperatorToKif(Symbol* operatoR) {
  return (operatoR);
}

void changeKifExpressionsToStellaExpressions(Cons* expressions, boolean termsP) {
  { ConsIterator* it = expressions->allocateIterator();

    for (; it->nextP(); ) {
      it->valueSetter((termsP ? kifTermToUntypedStellaTerm(it->value) : kifSentenceToUntypedStellaSentence(it->value)));
    }
  }
}

Cons* oANNOTATION_TRANSLATION_TABLEo = NULL;

Cons* canonicalizeAnnotation(Cons* tree) {
  { Object* operatoR = tree->value;

    if (operatoR == KWD_KIF_IN_ABOUT) {
      tree->firstSetter(SYM_KIF_IN_LOGIC_ABOUT);
      return (tree);
    }
    { Cons* entry = NULL;
      Cons* iter000 = oANNOTATION_TRANSLATION_TABLEo;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        entry = ((Cons*)(iter000->value));
        if (eqlP(operatoR, entry->value)) {
          tree->firstSetter(entry->rest->value);
          return (listO(3, SYM_KIF_IN_LOGIC_ABOUT, tree, ((Cons*)(copyConsTree(((Cons*)(entry->rest->rest->value)))))->concatenate(NIL, 0)));
        }
      }
    }
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << "`" << operatoR << "'" << "' not found in *ANNOTATION-TRANSLATION-TABLE*";
      throw *newStellaException(stream000->theStringReader());
    }
  }
}

Object* kifSentenceToUntypedStellaSentence(Object* tree) {
  if (!((boolean)(tree))) {
    return (NULL);
  }
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (testValue000 == SGT_KIF_IN_STELLA_CONS) {
      { Object* tree000 = tree;
        Cons* tree = ((Cons*)(tree000));

        { Object* operatoR = tree->value;

          if (isaP(operatoR, SGT_KIF_IN_STELLA_CONS)) {
            return (kifPredicationToStellaPredication(cons(SYM_KIF_IN_PL_KERNEL_KB_HOLDS, tree->concatenate(NIL, 0))));
          }
          if (!symbolP(operatoR)) {
            { OutputStringStream* stream000 = newOutputStringStream();

              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                *(stream000->nativeStream) << "PARSING ERROR: " << "Bad first argument in KIF sentence: " << "`" << operatoR << "'" << std::endl << "   Operator must be a symbol or an expression" << "." << std::endl;
                helpSignalPropositionError(stream000, KWD_KIF_IN_ERROR);
              }
              throw *newParsingError(stream000->theStringReader());
            }
          }
          { GeneralizedSymbol* testValue001 = ((GeneralizedSymbol*)(operatoR));

            if ((testValue001 == SYM_KIF_IN_STELLA_AND) ||
                ((testValue001 == SYM_KIF_IN_STELLA_OR) ||
                 ((testValue001 == SYM_KIF_IN_STELLA_NOT) ||
                  (testValue001 == SYM_KIF_IN_LOGIC_FAIL)))) {
              changeKifExpressionsToStellaExpressions(tree->rest, false);
              return (tree);
            }
            else if ((testValue001 == SYM_KIF_IN_STELLA_eg) ||
                (testValue001 == SYM_KIF_IN_STELLA_le)) {
              return (kifImpliesToOrNot(tree));
            }
            else if ((testValue001 == SYM_KIF_IN_LOGIC_leg) ||
                ((testValue001 == SYM_KIF_IN_LOGIC_legg) ||
                 ((testValue001 == SYM_KIF_IN_LOGIC_lleg) ||
                  ((testValue001 == SYM_KIF_IN_LOGIC_llegg) ||
                   ((testValue001 == SYM_KIF_IN_LOGIC_ltg) ||
                    ((testValue001 == SYM_KIF_IN_LOGIC_ltgg) ||
                     ((testValue001 == SYM_KIF_IN_LOGIC_lltg) ||
                      (testValue001 == SYM_KIF_IN_LOGIC_lltgg)))))))) {
              return (kifSentenceToUntypedStellaSentence(kifBiconditionalToTwoImplies(tree)));
            }
            else if (testValue001 == SYM_KIF_IN_STELLA_EXISTS) {
              return (kifExistsToStellaExists(tree));
            }
            else if (testValue001 == SYM_KIF_IN_STELLA_FORALL) {
              return (kifForallToStellaForall(tree));
            }
            else if (testValue001 == SYM_KIF_IN_STELLA_e) {
              return (kifEqualityToStellaEquality(tree));
            }
            else if (testValue001 == SYM_KIF_IN_LOGIC_ABOUT) {
              tree->secondSetter(kifSentenceToUntypedStellaSentence(tree->rest->value));
              return (tree);
            }
            else if ((testValue001 == KWD_KIF_IN_ABOUT) ||
                ((testValue001 == SYM_KIF_IN_LOGIC_lle) ||
                 ((testValue001 == SYM_KIF_IN_LOGIC_egg) ||
                  ((testValue001 == SYM_KIF_IN_LOGIC_lt) ||
                   ((testValue001 == SYM_KIF_IN_LOGIC_tg) ||
                    ((testValue001 == SYM_KIF_IN_LOGIC_llt) ||
                     (testValue001 == SYM_KIF_IN_LOGIC_tgg))))))) {
              return (kifSentenceToUntypedStellaSentence(canonicalizeAnnotation(tree)));
            }
            else {
              return (kifPredicationToStellaPredication(tree));
            }
          }
        }
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* tree001 = tree;
        Symbol* tree = ((Symbol*)(tree001));

        return (kifSymbolToStellaSymbol(tree));
      }
    }
    else if (subtypeOfStringP(testValue000)) {
      { Object* tree002 = tree;
        StringWrapper* tree = ((StringWrapper*)(tree002));

        { OutputStringStream* stream001 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream001->nativeStream) << "PARSING ERROR: " << "Illegal term in sentence position: " << "`" << tree << "'" << "." << std::endl;
            helpSignalPropositionError(stream001, KWD_KIF_IN_ERROR);
          }
          throw *newParsingError(stream001->theStringReader());
        }
      }
    }
    else {
      return (tree);
    }
  }
}

Cons* oKIF_SENTENCE_OPERATORSo = NULL;

Cons* oKIF_TERM_OPERATORSo = NULL;

boolean termKifSpecialFormP(Object* operatoR) {
  return (oKIF_TERM_OPERATORSo->membP(operatoR));
}

Object* kifTermToUntypedStellaTerm(Object* tree) {
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (subtypeOfSymbolP(testValue000)) {
      { Object* tree000 = tree;
        Symbol* tree = ((Symbol*)(tree000));

        return (kifSymbolToStellaSymbol(tree));
      }
    }
    else if (testValue000 == SGT_KIF_IN_STELLA_CONS) {
      { Object* tree001 = tree;
        Cons* tree = ((Cons*)(tree001));

        { Object* operatoR = tree->value;

          if (isaP(operatoR, SGT_KIF_IN_STELLA_CONS)) {
            return (kifTermToUntypedStellaTerm(cons(SYM_KIF_IN_PL_KERNEL_KB_VALUE, tree->concatenate(NIL, 0))));
          }
          if (!symbolP(operatoR)) {
            { OutputStringStream* stream000 = newOutputStringStream();

              { 
                BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                *(stream000->nativeStream) << "PARSING ERROR: " << "Bad first argument in KIF term: " << "`" << operatoR << "'" << std::endl << "   Operator must be a symbol or an expression" << "." << std::endl;
                helpSignalPropositionError(stream000, KWD_KIF_IN_ERROR);
              }
              throw *newParsingError(stream000->theStringReader());
            }
          }
          if (oKIF_SENTENCE_OPERATORSo->memberP(operatoR)) {
            return (kifSentenceToUntypedStellaSentence(tree));
          }
          else if (termKifSpecialFormP(operatoR)) {
            { GeneralizedSymbol* testValue001 = ((GeneralizedSymbol*)(operatoR));

              if (testValue001 == SYM_KIF_IN_LOGIC_THE) {
                return (kifTheToStellaTheOnly(tree));
              }
              else if (testValue001 == SYM_KIF_IN_LOGIC_SETOFALL) {
                return (kifSetofallToStellaSetofall(tree));
              }
              else if (testValue001 == SYM_KIF_IN_LOGIC_KAPPA) {
                return (kifKappaToStellaKappa(tree));
              }
              else if (testValue001 == SYM_KIF_IN_LOGIC_LAMBDA) {
                return (kifTermToUntypedStellaTerm(kifLambdaToStellaKappa(tree)));
              }
              else if (testValue001 == SYM_KIF_IN_STELLA_IF) {
                tree->secondSetter(kifSentenceToUntypedStellaSentence(tree->rest->value));
                changeKifExpressionsToStellaExpressions(tree->rest->rest, true);
                return (tree);
              }
              else if (testValue001 == SYM_KIF_IN_STELLA_COND) {
                return (kifTermToUntypedStellaTerm(kifCondToIf(tree->rest)));
              }
              else if ((testValue001 == SYM_KIF_IN_PL_KERNEL_KB_SETOF) ||
                  (testValue001 == SYM_KIF_IN_PL_KERNEL_KB_LISTOF)) {
                changeKifExpressionsToStellaExpressions(tree->rest, true);
                return (tree);
              }
              else {
                { OutputStringStream* stream001 = newOutputStringStream();

                  *(stream001->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                  throw *newStellaException(stream001->theStringReader());
                }
              }
            }
          }
          else {
            tree->firstSetter(kifOperatorToInternalStella(((Symbol*)(operatoR))));
            changeKifExpressionsToStellaExpressions(tree->rest, true);
            return (tree);
          }
        }
      }
    }
    else {
      return (tree);
    }
  }
}

boolean kifVariableP(Object* self) {
  return (questionMarkSymbolP(self));
}

Cons* extractVariablesFromDeclarations(Object* declarations) {
  { Cons* result = NIL;

    if (safePrimaryType(declarations) == SGT_KIF_IN_STELLA_CONS) {
      { Object* declarations000 = declarations;
        Cons* declarations = ((Cons*)(declarations000));

        { Object* item = NULL;
          Cons* iter000 = declarations;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            item = iter000->value;
            if (safePrimaryType(item) == SGT_KIF_IN_STELLA_CONS) {
              { Object* item000 = item;
                Cons* item = ((Cons*)(item000));

                if (kifVariableP(item->value)) {
                  result = cons(item->value, result);
                }
                else {
                  { OutputStringStream* stream000 = newOutputStringStream();

                    { 
                      BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
                      *(stream000->nativeStream) << "PARSING ERROR: " << "Non-variable " << "`" << item->value << "'" << " found where ?variable expected" << "." << std::endl;
                      helpSignalPropositionError(stream000, KWD_KIF_IN_ERROR);
                    }
                    throw *newParsingError(stream000->theStringReader());
                  }
                }
              }
            }
            else {
              if (kifVariableP(item)) {
                result = cons(item, result);
              }
            }
          }
        }
      }
    }
    else {
      if (kifVariableP(declarations)) {
        result = cons(declarations, result);
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          { 
            BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
            *(stream001->nativeStream) << "PARSING ERROR: " << "Non-variable " << "`" << declarations << "'" << " found where ?variable expected" << "." << std::endl;
            helpSignalPropositionError(stream001, KWD_KIF_IN_ERROR);
          }
          throw *newParsingError(stream001->theStringReader());
        }
      }
    }
    return (result->reverse());
  }
}

void collectUndeclaredVariables(Object* tree, Cons* declaredvariables, List* undeclaredvariables) {
  { Surrogate* testValue000 = safePrimaryType(tree);

    if (testValue000 == SGT_KIF_IN_STELLA_CONS) {
      { Object* tree000 = tree;
        Cons* tree = ((Cons*)(tree000));

        { Object* operatoR = tree->value;

          { Surrogate* testValue001 = safePrimaryType(operatoR);

            if (testValue001 == SGT_KIF_IN_STELLA_CONS) {
              { Object* operator000 = operatoR;
                Cons* operatoR = ((Cons*)(operator000));

                collectUndeclaredVariables(operatoR, declaredvariables, undeclaredvariables);
                { Object* arg = NULL;
                  Cons* iter000 = tree->rest;

                  for (; !(iter000 == NIL); iter000 = iter000->rest) {
                    arg = iter000->value;
                    collectUndeclaredVariables(arg, declaredvariables, undeclaredvariables);
                  }
                }
              }
            }
            else if (subtypeOfSymbolP(testValue001)) {
              { Object* operator001 = operatoR;
                Symbol* operatoR = ((Symbol*)(operator001));

                if ((operatoR == SYM_KIF_IN_STELLA_EXISTS) ||
                    (operatoR == SYM_KIF_IN_STELLA_FORALL)) {
                  { Object* v = NULL;
                    Cons* iter001 = extractVariablesFromDeclarations(tree->rest->value);

                    for (; !(iter001 == NIL); iter001 = iter001->rest) {
                      v = iter001->value;
                      declaredvariables = cons(v, declaredvariables);
                    }
                  }
                  { Object* arg = NULL;
                    Cons* iter002 = tree->rest->rest;

                    for (; !(iter002 == NIL); iter002 = iter002->rest) {
                      arg = iter002->value;
                      collectUndeclaredVariables(arg, declaredvariables, undeclaredvariables);
                    }
                  }
                }
                else if ((operatoR == SYM_KIF_IN_LOGIC_SETOFALL) ||
                    ((operatoR == SYM_KIF_IN_LOGIC_KAPPA) ||
                     ((operatoR == SYM_KIF_IN_LOGIC_LAMBDA) ||
                      (operatoR == SYM_KIF_IN_LOGIC_THE)))) {
                }
                else {
                  { Object* arg = NULL;
                    Cons* iter003 = tree->rest;

                    for (; !(iter003 == NIL); iter003 = iter003->rest) {
                      arg = iter003->value;
                      collectUndeclaredVariables(arg, declaredvariables, undeclaredvariables);
                    }
                  }
                }
              }
            }
            else {
            }
          }
        }
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* tree001 = tree;
        Symbol* tree = ((Symbol*)(tree001));

        if (questionMarkSymbolP(tree) &&
            (!declaredvariables->memberP(tree))) {
          if (!undeclaredvariables->memberP(tree)) {
            undeclaredvariables->insertLast(tree);
          }
        }
      }
    }
    else {
    }
  }
}

Object* wrapKifWithForall(Object* tree, Cons* declaredvariables) {
  if (safePrimaryType(tree) == SGT_KIF_IN_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if (symbolP(tree->value)) {
        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

          if (testValue000 == SYM_KIF_IN_STELLA_AND) {
            { Cons* sentences = NIL;

              { Object* conjunct = NULL;
                Cons* iter000 = tree->rest;
                Cons* collect000 = NULL;

                for  (; !(iter000 == NIL); 
                      iter000 = iter000->rest) {
                  conjunct = iter000->value;
                  if (!((boolean)(collect000))) {
                    {
                      collect000 = cons(wrapKifWithForall(conjunct, declaredvariables), NIL);
                      if (sentences == NIL) {
                        sentences = collect000;
                      }
                      else {
                        addConsToEndOfConsList(sentences, collect000);
                      }
                    }
                  }
                  else {
                    {
                      collect000->rest = cons(wrapKifWithForall(conjunct, declaredvariables), NIL);
                      collect000 = collect000->rest;
                    }
                  }
                }
              }
              return (cons(SYM_KIF_IN_STELLA_AND, sentences->concatenate(NIL, 0)));
            }
          }
          else if (testValue000 == SYM_KIF_IN_LOGIC_leg) {
            return (wrapKifWithForall(kifBiconditionalToTwoImplies(tree), declaredvariables));
          }
          else {
          }
        }
      }
    }
  }
  else {
  }
  { List* undeclaredvariables = newList();

    collectUndeclaredVariables(tree, declaredvariables, undeclaredvariables);
    switch (undeclaredvariables->length()) {
      case 0: 
        undeclaredvariables->free();
        return (tree);
      case 1: 
        return (listO(3, SYM_KIF_IN_STELLA_FORALL, undeclaredvariables->first(), cons(tree, NIL)));
      default:
        return (listO(3, SYM_KIF_IN_STELLA_FORALL, copyConsTree(undeclaredvariables->theConsList), cons(tree, NIL)));
    }
  }
}

Object* kifExpressionToUntypedStellaExpression(Object* tree) {
  if (safePrimaryType(tree) == SGT_KIF_IN_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      if (symbolP(tree->value)) {
        { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(tree->value));

          if ((testValue000 == SYM_KIF_IN_LOGIC_THE) ||
              ((testValue000 == SYM_KIF_IN_LOGIC_SETOFALL) ||
               (testValue000 == SYM_KIF_IN_LOGIC_KAPPA))) {
            return (kifTermToUntypedStellaTerm(tree));
          }
          else {
          }
        }
      }
    }
  }
  else {
  }
  tree = wrapKifWithForall(tree, NIL);
  return (kifSentenceToUntypedStellaSentence(tree));
}

Object* convertToPrefixPropositionTree(Object* tree) {
  if (safePrimaryType(tree) == SGT_KIF_IN_STELLA_CONS) {
    { Object* tree000 = tree;
      Cons* tree = ((Cons*)(tree000));

      { Symbol* operatoR = ((Symbol*)(tree->value));

        if (kifQuantifierSymbolP(operatoR)) {
          tree = infixToPrefixQuantificationTree(tree);
        }
        else {
          { ConsIterator* it = tree->rest->allocateIterator();

            for (; it->nextP(); ) {
              if (consP(it->value)) {
                it->valueSetter(convertToPrefixPropositionTree(it->value));
              }
            }
          }
        }
        return (tree);
      }
    }
  }
  else {
    return (tree);
  }
}

Cons* infixToPrefixQuantificationTree(Cons* tree) {
  { Object* quantifier = tree->value;
    Cons* generatorsclause = NULL;
    Object* whereclause = NULL;
    Object* alwaysclause = NULL;
    Cons* residue = tree->rest;
    Cons* otree = NULL;

    generatorsclause = extractGeneratorsClause(residue, residue);
    if (!((boolean)(generatorsclause))) {
      return (NULL);
    }
    whereclause = extractOptionAndResidue(SYM_KIF_IN_STELLA_WHERE, residue, residue);
    alwaysclause = extractOptionAndResidue(SYM_KIF_IN_STELLA_ALWAYS, residue, residue);
    otree = cons(quantifier, cons(convertToPrefixPropositionTree(generatorsclause), ((((boolean)(whereclause)) ? cons(convertToPrefixPropositionTree(whereclause), NIL) : getQuotedTree("((TRUE) \"/LOGIC\")", "/LOGIC")))->concatenate(((((boolean)(alwaysclause)) ? cons(convertToPrefixPropositionTree(alwaysclause), NIL) : NIL))->concatenate(NIL, 0), 0)));
    if (!(residue == NIL)) {
      { OutputStringStream* stream000 = newOutputStringStream();

        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          *(stream000->nativeStream) << "PARSING ERROR: " << "Extra expressions at the end of quantified expression" << "." << std::endl;
          helpSignalPropositionError(stream000, KWD_KIF_IN_ERROR);
        }
        throw *newParsingError(stream000->theStringReader());
      }
    }
    return (otree);
  }
}

// Indicates the current dialect of logic used to phrase
// queries, assertions, and definitions.
DEFINE_STELLA_SPECIAL(oLOGIC_DIALECTo, Keyword* , NULL);

Object* standardizeLogicalParseTree(Object* tree) {
  { Object* standardizedtree = NULL;

    if (oLOGIC_DIALECTo == KWD_KIF_IN_KIF) {
      standardizedtree = kifExpressionToUntypedStellaExpression(tree);
    }
    else if (oLOGIC_DIALECTo == KWD_KIF_IN_STELLA) {
      standardizedtree = convertToPrefixPropositionTree(tree);
    }
    else if (oLOGIC_DIALECTo == KWD_KIF_IN_PREFIX_STELLA) {
      standardizedtree = tree;
    }
    else if (oLOGIC_DIALECTo == KWD_KIF_IN_MELD) {
    }
    else if (oLOGIC_DIALECTo == KWD_KIF_IN_LOOM) {
      standardizedtree = kifExpressionToUntypedStellaExpression(tree);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oLOGIC_DIALECTo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    return (standardizedtree);
  }
}

Keyword* inDialect(Object* dialect) {
  // Change the current logic dialect to `dialect'.
  // Currently supported dialects are `KIF', `STELLA', and `PREFIX-STELLA'.
  // The STELLA dialects are not recommended for the construction of knowledge
  // bases, they are mainly used internally by PowerLoom.
  { Surrogate* testValue000 = safePrimaryType(dialect);

    if (subtypeOfSymbolP(testValue000)) {
      { Object* dialect000 = dialect;
        Symbol* dialect = ((Symbol*)(dialect000));

        oLOGIC_DIALECTo = dialect->keywordify();
      }
    }
    else if (subtypeOfStringP(testValue000)) {
      { Object* dialect001 = dialect;
        StringWrapper* dialect = ((StringWrapper*)(dialect001));

        oLOGIC_DIALECTo = stringKeywordify(dialect->wrapperValue);
      }
    }
    else if (subtypeOfKeywordP(testValue000)) {
      { Object* dialect002 = dialect;
        Keyword* dialect = ((Keyword*)(dialect002));

        oLOGIC_DIALECTo = dialect;
      }
    }
    else {
      *(STANDARD_WARNING->nativeStream) << "Warning: " << "IN-DIALECT: Illegal dialect specification: " << "`" << dialect << "'" << std::endl;
    }
  }
  return (oLOGIC_DIALECTo);
}

void helpStartupKifIn1() {
  {
    SYM_KIF_IN_LOGIC_PARSE_TREE = ((Symbol*)(internRigidSymbolWrtModule("PARSE-TREE", NULL, 0)));
    KWD_KIF_IN_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    SGT_KIF_IN_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    SYM_KIF_IN_STELLA_ISA = ((Symbol*)(internRigidSymbolWrtModule("ISA", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_IN_STELLA_EXISTS = ((Symbol*)(internRigidSymbolWrtModule("EXISTS", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_IN_STELLA_FORALL = ((Symbol*)(internRigidSymbolWrtModule("FORALL", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_IN_LOGIC_SETOFALL = ((Symbol*)(internRigidSymbolWrtModule("SETOFALL", NULL, 0)));
    SYM_KIF_IN_LOGIC_KAPPA = ((Symbol*)(internRigidSymbolWrtModule("KAPPA", NULL, 0)));
    SYM_KIF_IN_LOGIC_THE = ((Symbol*)(internRigidSymbolWrtModule("THE", NULL, 0)));
    SYM_KIF_IN_LOGIC_THE_ONLY = ((Symbol*)(internRigidSymbolWrtModule("THE-ONLY", NULL, 0)));
    SYM_KIF_IN_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_IN_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_IN_STELLA_e = ((Symbol*)(internRigidSymbolWrtModule("=", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_IN_STELLA_IF = ((Symbol*)(internRigidSymbolWrtModule("IF", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_IN_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_IN_STELLA_le = ((Symbol*)(internRigidSymbolWrtModule("<=", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_IN_STELLA_OR = ((Symbol*)(internRigidSymbolWrtModule("OR", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_IN_STELLA_eg = ((Symbol*)(internRigidSymbolWrtModule("=>", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_IN_LOGIC_legg = ((Symbol*)(internRigidSymbolWrtModule("<=>>", NULL, 0)));
    SYM_KIF_IN_LOGIC_lleg = ((Symbol*)(internRigidSymbolWrtModule("<<=>", NULL, 0)));
    SYM_KIF_IN_LOGIC_llegg = ((Symbol*)(internRigidSymbolWrtModule("<<=>>", NULL, 0)));
    SYM_KIF_IN_LOGIC_ltg = ((Symbol*)(internRigidSymbolWrtModule("<~>", NULL, 0)));
    SYM_KIF_IN_LOGIC_ltgg = ((Symbol*)(internRigidSymbolWrtModule("<~>>", NULL, 0)));
    SYM_KIF_IN_LOGIC_lltg = ((Symbol*)(internRigidSymbolWrtModule("<<~>", NULL, 0)));
    SYM_KIF_IN_LOGIC_lltgg = ((Symbol*)(internRigidSymbolWrtModule("<<~>>", NULL, 0)));
    SYM_KIF_IN_LOGIC_egg = ((Symbol*)(internRigidSymbolWrtModule("=>>", NULL, 0)));
    SYM_KIF_IN_LOGIC_lle = ((Symbol*)(internRigidSymbolWrtModule("<<=", NULL, 0)));
    SYM_KIF_IN_LOGIC_tg = ((Symbol*)(internRigidSymbolWrtModule("~>", NULL, 0)));
    SYM_KIF_IN_LOGIC_lt = ((Symbol*)(internRigidSymbolWrtModule("<~", NULL, 0)));
    SYM_KIF_IN_LOGIC_tgg = ((Symbol*)(internRigidSymbolWrtModule("~>>", NULL, 0)));
    SYM_KIF_IN_LOGIC_llt = ((Symbol*)(internRigidSymbolWrtModule("<<~", NULL, 0)));
    SYM_KIF_IN_LOGIC_ABOUT = ((Symbol*)(internRigidSymbolWrtModule("ABOUT", NULL, 0)));
    SYM_KIF_IN_PL_KERNEL_KB_VALUE = ((Symbol*)(internRigidSymbolWrtModule("VALUE", getStellaModule("/PL-KERNEL-KB", true), 0)));
    KWD_KIF_IN_DIRECTION = ((Keyword*)(internRigidSymbolWrtModule("DIRECTION", NULL, 2)));
    KWD_KIF_IN_BACKWARD = ((Keyword*)(internRigidSymbolWrtModule("BACKWARD", NULL, 2)));
    KWD_KIF_IN_FORWARD = ((Keyword*)(internRigidSymbolWrtModule("FORWARD", NULL, 2)));
    KWD_KIF_IN_CONFIDENCE_LEVEL = ((Keyword*)(internRigidSymbolWrtModule("CONFIDENCE-LEVEL", NULL, 2)));
    KWD_KIF_IN_DEFAULT = ((Keyword*)(internRigidSymbolWrtModule("DEFAULT", NULL, 2)));
    KWD_KIF_IN_ABOUT = ((Keyword*)(internRigidSymbolWrtModule("ABOUT", NULL, 2)));
    SYM_KIF_IN_PL_KERNEL_KB_HOLDS = ((Symbol*)(internRigidSymbolWrtModule("HOLDS", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_KIF_IN_LOGIC_FAIL = ((Symbol*)(internRigidSymbolWrtModule("FAIL", NULL, 0)));
    SYM_KIF_IN_LOGIC_leg = ((Symbol*)(internRigidSymbolWrtModule("<=>", NULL, 0)));
    SYM_KIF_IN_LOGIC_LAMBDA = ((Symbol*)(internRigidSymbolWrtModule("LAMBDA", NULL, 0)));
    SYM_KIF_IN_STELLA_COND = ((Symbol*)(internRigidSymbolWrtModule("COND", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_IN_PL_KERNEL_KB_SETOF = ((Symbol*)(internRigidSymbolWrtModule("SETOF", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_KIF_IN_PL_KERNEL_KB_LISTOF = ((Symbol*)(internRigidSymbolWrtModule("LISTOF", getStellaModule("/PL-KERNEL-KB", true), 0)));
    SYM_KIF_IN_STELLA_WHERE = ((Symbol*)(internRigidSymbolWrtModule("WHERE", getStellaModule("/STELLA", true), 0)));
    SYM_KIF_IN_STELLA_ALWAYS = ((Symbol*)(internRigidSymbolWrtModule("ALWAYS", getStellaModule("/STELLA", true), 0)));
    KWD_KIF_IN_KIF = ((Keyword*)(internRigidSymbolWrtModule("KIF", NULL, 2)));
    KWD_KIF_IN_STELLA = ((Keyword*)(internRigidSymbolWrtModule("STELLA", NULL, 2)));
    KWD_KIF_IN_PREFIX_STELLA = ((Keyword*)(internRigidSymbolWrtModule("PREFIX-STELLA", NULL, 2)));
    KWD_KIF_IN_MELD = ((Keyword*)(internRigidSymbolWrtModule("MELD", NULL, 2)));
    KWD_KIF_IN_LOOM = ((Keyword*)(internRigidSymbolWrtModule("LOOM", NULL, 2)));
    SYM_KIF_IN_LOGIC_STARTUP_KIF_IN = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-KIF-IN", NULL, 0)));
    SYM_KIF_IN_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void startupKifIn() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupKifIn1();
    }
    if (currentStartupTimePhaseP(4)) {
      oANNOTATION_TRANSLATION_TABLEo = listO(7, listO(4, SYM_KIF_IN_LOGIC_lle, SYM_KIF_IN_STELLA_le, listO(3, KWD_KIF_IN_DIRECTION, KWD_KIF_IN_BACKWARD, NIL), NIL), listO(4, SYM_KIF_IN_LOGIC_egg, SYM_KIF_IN_STELLA_eg, listO(3, KWD_KIF_IN_DIRECTION, KWD_KIF_IN_FORWARD, NIL), NIL), listO(4, SYM_KIF_IN_LOGIC_lt, SYM_KIF_IN_STELLA_le, listO(3, KWD_KIF_IN_CONFIDENCE_LEVEL, KWD_KIF_IN_DEFAULT, NIL), NIL), listO(4, SYM_KIF_IN_LOGIC_tg, SYM_KIF_IN_STELLA_eg, listO(3, KWD_KIF_IN_CONFIDENCE_LEVEL, KWD_KIF_IN_DEFAULT, NIL), NIL), listO(4, SYM_KIF_IN_LOGIC_llt, SYM_KIF_IN_STELLA_le, listO(5, KWD_KIF_IN_CONFIDENCE_LEVEL, KWD_KIF_IN_DEFAULT, KWD_KIF_IN_DIRECTION, KWD_KIF_IN_BACKWARD, NIL), NIL), listO(4, SYM_KIF_IN_LOGIC_tgg, SYM_KIF_IN_STELLA_eg, listO(5, KWD_KIF_IN_CONFIDENCE_LEVEL, KWD_KIF_IN_DEFAULT, KWD_KIF_IN_DIRECTION, KWD_KIF_IN_FORWARD, NIL), NIL), NIL);
      oKIF_SENTENCE_OPERATORSo = getQuotedTree("((AND OR NOT FAIL EXISTS FORALL => <= <=> =) \"/LOGIC\")", "/LOGIC");
      oKIF_TERM_OPERATORSo = getQuotedTree("((THE SETOFALL KAPPA LAMBDA COND IF SETOF LISTOF) \"/LOGIC\")", "/LOGIC");
      oLOGIC_DIALECTo = KWD_KIF_IN_KIF;
    }
    if (currentStartupTimePhaseP(5)) {
      defineStellaTypeFromStringifiedSource("(DEFTYPE PARSE-TREE OBJECT)");
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("SYMBOL-TYPE-CHARACTER", "(DEFUN (SYMBOL-TYPE-CHARACTER CHARACTER) ((SYMBOL OBJECT)))", ((cpp_function_code)(&symbolTypeCharacter)), NULL);
      defineFunctionObject("QUESTION-MARK-SYMBOL?", "(DEFUN (QUESTION-MARK-SYMBOL? BOOLEAN) ((SYMBOL OBJECT)))", ((cpp_function_code)(&questionMarkSymbolP)), NULL);
      defineFunctionObject("SEQUENCE-VARIABLE-SYMBOL?", "(DEFUN (SEQUENCE-VARIABLE-SYMBOL? BOOLEAN) ((SELF OBJECT)))", ((cpp_function_code)(&sequenceVariableSymbolP)), NULL);
      defineFunctionObject("AUTOMATIC-INSTANCE-SYMBOL?", "(DEFUN (AUTOMATIC-INSTANCE-SYMBOL? BOOLEAN) ((SYMBOL OBJECT)))", ((cpp_function_code)(&automaticInstanceSymbolP)), NULL);
      defineFunctionObject("KIF-SYMBOL-TO-STELLA-SYMBOL", "(DEFUN (KIF-SYMBOL-TO-STELLA-SYMBOL GENERALIZED-SYMBOL) ((SYMBOL SYMBOL)))", ((cpp_function_code)(&kifSymbolToStellaSymbol)), NULL);
      defineFunctionObject("KIF-VARIABLE-TO-STELLA-VARIABLE", "(DEFUN (KIF-VARIABLE-TO-STELLA-VARIABLE SYMBOL) ((VARIABLE OBJECT)))", ((cpp_function_code)(&kifVariableToStellaVariable)), NULL);
      defineFunctionObject("KIF-VARIABLE-DECLARATION?", "(DEFUN (KIF-VARIABLE-DECLARATION? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&kifVariableDeclarationP)), NULL);
      defineFunctionObject("ONE-KIF-VARIABLE-DECLARATION-TO-STELLA", "(DEFUN (ONE-KIF-VARIABLE-DECLARATION-TO-STELLA OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&oneKifVariableDeclarationToStella)), NULL);
      defineFunctionObject("STELLA-VARIABLE-DECLARATIONS?", "(DEFUN (STELLA-VARIABLE-DECLARATIONS? BOOLEAN) ((TREE OBJECT)))", ((cpp_function_code)(&stellaVariableDeclarationsP)), NULL);
      defineFunctionObject("KIF-VARIABLE-DECLARATIONS-TO-STELLA", "(DEFUN (KIF-VARIABLE-DECLARATIONS-TO-STELLA CONS) ((TREE OBJECT) (ERROR? BOOLEAN)))", ((cpp_function_code)(&kifVariableDeclarationsToStella)), NULL);
      defineFunctionObject("KIF-QUANTIFIER-SYMBOL?", "(DEFUN (KIF-QUANTIFIER-SYMBOL? BOOLEAN) ((SELF SYMBOL)))", ((cpp_function_code)(&kifQuantifierSymbolP)), NULL);
      defineFunctionObject("KIF-THE-TO-STELLA-THE-ONLY", "(DEFUN (KIF-THE-TO-STELLA-THE-ONLY CONS) ((TREE CONS)))", ((cpp_function_code)(&kifTheToStellaTheOnly)), NULL);
      defineFunctionObject("KIF-SETOFALL-TO-STELLA-SETOFALL", "(DEFUN (KIF-SETOFALL-TO-STELLA-SETOFALL CONS) ((TREE CONS)))", ((cpp_function_code)(&kifSetofallToStellaSetofall)), NULL);
      defineFunctionObject("KIF-KAPPA-TO-STELLA-KAPPA", "(DEFUN (KIF-KAPPA-TO-STELLA-KAPPA CONS) ((TREE CONS)))", ((cpp_function_code)(&kifKappaToStellaKappa)), NULL);
      defineFunctionObject("KIF-LAMBDA-TO-STELLA-KAPPA", "(DEFUN (KIF-LAMBDA-TO-STELLA-KAPPA CONS) ((TREE CONS)))", ((cpp_function_code)(&kifLambdaToStellaKappa)), NULL);
      defineFunctionObject("KIF-COND-TO-IF", "(DEFUN (KIF-COND-TO-IF CONS) ((CONDITIONS CONS)))", ((cpp_function_code)(&kifCondToIf)), NULL);
      defineFunctionObject("KIF-INVERT-SENTENCE", "(DEFUN (KIF-INVERT-SENTENCE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&kifInvertSentence)), NULL);
      defineFunctionObject("KIF-IMPLIES-TO-OR-NOT", "(DEFUN (KIF-IMPLIES-TO-OR-NOT CONS) ((TREE CONS)))", ((cpp_function_code)(&kifImpliesToOrNot)), NULL);
      defineFunctionObject("KIF-BICONDITIONAL-TO-TWO-IMPLIES", "(DEFUN (KIF-BICONDITIONAL-TO-TWO-IMPLIES CONS) ((TREE CONS)))", ((cpp_function_code)(&kifBiconditionalToTwoImplies)), NULL);
      defineFunctionObject("KIF-EXISTS-TO-STELLA-EXISTS", "(DEFUN (KIF-EXISTS-TO-STELLA-EXISTS CONS) ((TREE CONS)))", ((cpp_function_code)(&kifExistsToStellaExists)), NULL);
      defineFunctionObject("KIF-THREE-ARGUMENT-FORALL-TO-STELLA-FORALL", "(DEFUN (KIF-THREE-ARGUMENT-FORALL-TO-STELLA-FORALL CONS) ((TREE CONS) (DECLARATIONS CONS)))", ((cpp_function_code)(&kifThreeArgumentForallToStellaForall)), NULL);
      defineFunctionObject("KIF-TWO-ARGUMENT-FORALL-TO-STELLA-FORALL", "(DEFUN (KIF-TWO-ARGUMENT-FORALL-TO-STELLA-FORALL CONS) ((TREE CONS) (DECLARATIONS CONS)))", ((cpp_function_code)(&kifTwoArgumentForallToStellaForall)), NULL);
      defineFunctionObject("KIF-FORALL-TO-STELLA-FORALL", "(DEFUN (KIF-FORALL-TO-STELLA-FORALL CONS) ((TREE CONS)))", ((cpp_function_code)(&kifForallToStellaForall)), NULL);
      defineFunctionObject("KIF-PREDICATION-TO-STELLA-PREDICATION", "(DEFUN (KIF-PREDICATION-TO-STELLA-PREDICATION CONS) ((TREE CONS)))", ((cpp_function_code)(&kifPredicationToStellaPredication)), NULL);
      defineFunctionObject("HELP-TRANSFORM-KIF-FUNCTION", "(DEFUN (HELP-TRANSFORM-KIF-FUNCTION CONS) ((ARG1 OBJECT) (ARG2 OBJECT)))", ((cpp_function_code)(&helpTransformKifFunction)), NULL);
      defineFunctionObject("KIF-EQUALITY-TO-STELLA-EQUALITY", "(DEFUN (KIF-EQUALITY-TO-STELLA-EQUALITY CONS) ((TREE CONS)))", ((cpp_function_code)(&kifEqualityToStellaEquality)), NULL);
      defineFunctionObject("KIF-OPERATOR-TO-INTERNAL-STELLA", "(DEFUN (KIF-OPERATOR-TO-INTERNAL-STELLA SYMBOL) ((OPERATOR SYMBOL)))", ((cpp_function_code)(&kifOperatorToInternalStella)), NULL);
      defineFunctionObject("INTERNAL-STELLA-OPERATOR-TO-KIF", "(DEFUN (INTERNAL-STELLA-OPERATOR-TO-KIF SYMBOL) ((OPERATOR SYMBOL)))", ((cpp_function_code)(&internalStellaOperatorToKif)), NULL);
      defineFunctionObject("CHANGE-KIF-EXPRESSIONS-TO-STELLA-EXPRESSIONS", "(DEFUN CHANGE-KIF-EXPRESSIONS-TO-STELLA-EXPRESSIONS ((EXPRESSIONS CONS) (TERMS? BOOLEAN)))", ((cpp_function_code)(&changeKifExpressionsToStellaExpressions)), NULL);
      defineFunctionObject("CANONICALIZE-ANNOTATION", "(DEFUN (CANONICALIZE-ANNOTATION CONS) ((TREE CONS)))", ((cpp_function_code)(&canonicalizeAnnotation)), NULL);
      defineFunctionObject("KIF-SENTENCE-TO-UNTYPED-STELLA-SENTENCE", "(DEFUN (KIF-SENTENCE-TO-UNTYPED-STELLA-SENTENCE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&kifSentenceToUntypedStellaSentence)), NULL);
      defineFunctionObject("TERM-KIF-SPECIAL-FORM?", "(DEFUN (TERM-KIF-SPECIAL-FORM? BOOLEAN) ((OPERATOR OBJECT)))", ((cpp_function_code)(&termKifSpecialFormP)), NULL);
      defineFunctionObject("KIF-TERM-TO-UNTYPED-STELLA-TERM", "(DEFUN (KIF-TERM-TO-UNTYPED-STELLA-TERM OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&kifTermToUntypedStellaTerm)), NULL);
      defineFunctionObject("KIF-VARIABLE?", "(DEFUN (KIF-VARIABLE? BOOLEAN) ((SELF OBJECT)))", ((cpp_function_code)(&kifVariableP)), NULL);
      defineFunctionObject("EXTRACT-VARIABLES-FROM-DECLARATIONS", "(DEFUN (EXTRACT-VARIABLES-FROM-DECLARATIONS CONS) ((DECLARATIONS OBJECT)))", ((cpp_function_code)(&extractVariablesFromDeclarations)), NULL);
      defineFunctionObject("COLLECT-UNDECLARED-VARIABLES", "(DEFUN COLLECT-UNDECLARED-VARIABLES ((TREE OBJECT) (DECLAREDVARIABLES CONS) (UNDECLAREDVARIABLES (LIST OF SYMBOL))))", ((cpp_function_code)(&collectUndeclaredVariables)), NULL);
      defineFunctionObject("WRAP-KIF-WITH-FORALL", "(DEFUN (WRAP-KIF-WITH-FORALL OBJECT) ((TREE OBJECT) (DECLAREDVARIABLES CONS)))", ((cpp_function_code)(&wrapKifWithForall)), NULL);
      defineFunctionObject("KIF-EXPRESSION-TO-UNTYPED-STELLA-EXPRESSION", "(DEFUN (KIF-EXPRESSION-TO-UNTYPED-STELLA-EXPRESSION OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&kifExpressionToUntypedStellaExpression)), NULL);
      defineFunctionObject("CONVERT-TO-PREFIX-PROPOSITION-TREE", "(DEFUN (CONVERT-TO-PREFIX-PROPOSITION-TREE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&convertToPrefixPropositionTree)), NULL);
      defineFunctionObject("INFIX-TO-PREFIX-QUANTIFICATION-TREE", "(DEFUN (INFIX-TO-PREFIX-QUANTIFICATION-TREE CONS) ((TREE CONS)))", ((cpp_function_code)(&infixToPrefixQuantificationTree)), NULL);
      defineFunctionObject("STANDARDIZE-LOGICAL-PARSE-TREE", "(DEFUN (STANDARDIZE-LOGICAL-PARSE-TREE OBJECT) ((TREE OBJECT)))", ((cpp_function_code)(&standardizeLogicalParseTree)), NULL);
      defineFunctionObject("IN-DIALECT", "(DEFUN (IN-DIALECT KEYWORD) ((DIALECT NAME)) :DOCUMENTATION \"Change the current logic dialect to `dialect'.\nCurrently supported dialects are `KIF', `STELLA', and `PREFIX-STELLA'.\nThe STELLA dialects are not recommended for the construction of knowledge\nbases, they are mainly used internally by PowerLoom.\" :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&inDialect)), NULL);
      defineFunctionObject("STARTUP-KIF-IN", "(DEFUN STARTUP-KIF-IN () :PUBLIC? TRUE)", ((cpp_function_code)(&startupKifIn)), NULL);
      { MethodSlot* function = lookupFunction(SYM_KIF_IN_LOGIC_STARTUP_KIF_IN);

        setDynamicSlotValue(function->dynamicSlots, SYM_KIF_IN_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupKifIn"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFGLOBAL *AUTOMATIC-INSTANCE-CHARACTER* CHARACTER #\\$ :DOCUMENTATION \"Character that identifies variables representing\ninstances named by the system.\")", &oAUTOMATIC_INSTANCE_CHARACTERo);
      defineGlobalVariableObject("(DEFGLOBAL *ANNOTATION-TRANSLATION-TABLE* (CONS OF CONS) (BQUOTE ((<<= <= (:DIRECTION :BACKWARD)) (=>> => (:DIRECTION :FORWARD)) (<~ <= (:CONFIDENCE-LEVEL :DEFAULT)) (~> => (:CONFIDENCE-LEVEL :DEFAULT)) (<<~ <= (:CONFIDENCE-LEVEL :DEFAULT :DIRECTION :BACKWARD)) (~>> => (:CONFIDENCE-LEVEL :DEFAULT :DIRECTION :FORWARD)))))", &oANNOTATION_TRANSLATION_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *KIF-SENTENCE-OPERATORS* (CONS OF SYMBOL) (QUOTE (AND OR NOT FAIL EXISTS FORALL => <= <=> =)))", &oKIF_SENTENCE_OPERATORSo);
      defineGlobalVariableObject("(DEFGLOBAL *KIF-TERM-OPERATORS* (CONS OF SYMBOL) (QUOTE (THE SETOFALL KAPPA LAMBDA COND IF SETOF LISTOF)))", &oKIF_TERM_OPERATORSo);
      defineGlobalVariableObject("(DEFSPECIAL *LOGIC-DIALECT* KEYWORD :KIF :DOCUMENTATION \"Indicates the current dialect of logic used to phrase\nqueries, assertions, and definitions.\")", &oLOGIC_DIALECTo);
    }
  }
}

Symbol* SYM_KIF_IN_LOGIC_PARSE_TREE = NULL;

Keyword* KWD_KIF_IN_ERROR = NULL;

Surrogate* SGT_KIF_IN_STELLA_CONS = NULL;

Symbol* SYM_KIF_IN_STELLA_ISA = NULL;

Symbol* SYM_KIF_IN_STELLA_EXISTS = NULL;

Symbol* SYM_KIF_IN_STELLA_FORALL = NULL;

Symbol* SYM_KIF_IN_LOGIC_SETOFALL = NULL;

Symbol* SYM_KIF_IN_LOGIC_KAPPA = NULL;

Symbol* SYM_KIF_IN_LOGIC_THE = NULL;

Symbol* SYM_KIF_IN_LOGIC_THE_ONLY = NULL;

Symbol* SYM_KIF_IN_STELLA_TRUE = NULL;

Symbol* SYM_KIF_IN_STELLA_AND = NULL;

Symbol* SYM_KIF_IN_STELLA_e = NULL;

Symbol* SYM_KIF_IN_STELLA_IF = NULL;

Symbol* SYM_KIF_IN_STELLA_NOT = NULL;

Symbol* SYM_KIF_IN_STELLA_le = NULL;

Symbol* SYM_KIF_IN_STELLA_OR = NULL;

Symbol* SYM_KIF_IN_STELLA_eg = NULL;

Symbol* SYM_KIF_IN_LOGIC_legg = NULL;

Symbol* SYM_KIF_IN_LOGIC_lleg = NULL;

Symbol* SYM_KIF_IN_LOGIC_llegg = NULL;

Symbol* SYM_KIF_IN_LOGIC_ltg = NULL;

Symbol* SYM_KIF_IN_LOGIC_ltgg = NULL;

Symbol* SYM_KIF_IN_LOGIC_lltg = NULL;

Symbol* SYM_KIF_IN_LOGIC_lltgg = NULL;

Symbol* SYM_KIF_IN_LOGIC_egg = NULL;

Symbol* SYM_KIF_IN_LOGIC_lle = NULL;

Symbol* SYM_KIF_IN_LOGIC_tg = NULL;

Symbol* SYM_KIF_IN_LOGIC_lt = NULL;

Symbol* SYM_KIF_IN_LOGIC_tgg = NULL;

Symbol* SYM_KIF_IN_LOGIC_llt = NULL;

Symbol* SYM_KIF_IN_LOGIC_ABOUT = NULL;

Symbol* SYM_KIF_IN_PL_KERNEL_KB_VALUE = NULL;

Keyword* KWD_KIF_IN_DIRECTION = NULL;

Keyword* KWD_KIF_IN_BACKWARD = NULL;

Keyword* KWD_KIF_IN_FORWARD = NULL;

Keyword* KWD_KIF_IN_CONFIDENCE_LEVEL = NULL;

Keyword* KWD_KIF_IN_DEFAULT = NULL;

Keyword* KWD_KIF_IN_ABOUT = NULL;

Symbol* SYM_KIF_IN_PL_KERNEL_KB_HOLDS = NULL;

Symbol* SYM_KIF_IN_LOGIC_FAIL = NULL;

Symbol* SYM_KIF_IN_LOGIC_leg = NULL;

Symbol* SYM_KIF_IN_LOGIC_LAMBDA = NULL;

Symbol* SYM_KIF_IN_STELLA_COND = NULL;

Symbol* SYM_KIF_IN_PL_KERNEL_KB_SETOF = NULL;

Symbol* SYM_KIF_IN_PL_KERNEL_KB_LISTOF = NULL;

Symbol* SYM_KIF_IN_STELLA_WHERE = NULL;

Symbol* SYM_KIF_IN_STELLA_ALWAYS = NULL;

Keyword* KWD_KIF_IN_KIF = NULL;

Keyword* KWD_KIF_IN_STELLA = NULL;

Keyword* KWD_KIF_IN_PREFIX_STELLA = NULL;

Keyword* KWD_KIF_IN_MELD = NULL;

Keyword* KWD_KIF_IN_LOOM = NULL;

Symbol* SYM_KIF_IN_LOGIC_STARTUP_KIF_IN = NULL;

Symbol* SYM_KIF_IN_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
