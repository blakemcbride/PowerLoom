//  -*- Mode: C++ -*-

// rule-induction.cc

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

Keyword* oRULE_INDUCTION_STRATEGYo = NULL;

Keyword* oSIGNATURE_STRATEGYo = NULL;

void setSignatureStrategy(Keyword* k) {
  oSIGNATURE_STRATEGYo = k;
}

boolean oENABLE_USER_THINGo = true;

boolean oOPTIMIZE_INDUCED_QUERIESo = true;

// Flag to control whether we try to simplify the rule antecedent.
// This should be set to FALSE if we expect the user to edit the rule and
// TRUE if we want to have final rules as general as possible.
boolean oSIMPLIFY_RULE_ANTECEDENTpo = false;

boolean oTRACE_ID3o = false;

boolean oTRACE_FOILo = false;

boolean oINDUCE_RULES_FROM_SIGNATURESo = true;

void setSignatureRules(boolean b) {
  oINDUCE_RULES_FROM_SIGNATURESo = b;
}

void setSignatureRulesEvaluatorWrapper(Cons* arguments) {
  setSignatureRules(((BooleanWrapper*)(arguments->value))->wrapperValue);
}

int oNUM_LGGSo = 2000;

boolean oENFORCE_LINKED_VARIABLESo = false;

boolean oLOG_INDUCED_RULESo = false;

boolean oALLOW_RECURSIVE_DECISION_NODESo = true;

boolean oLOG_DECISION_RULE_CONSTRUCTIONo = false;

double LOG_2 = 0.6931472;

void setRuleInductionStrategy(Keyword* k) {
  oRULE_INDUCTION_STRATEGYo = k;
}

void setRecursiveDecisionNodes(boolean b) {
  oALLOW_RECURSIVE_DECISION_NODESo = b;
}

void setRecursiveDecisionNodesEvaluatorWrapper(Cons* arguments) {
  setRecursiveDecisionNodes(((BooleanWrapper*)(arguments->value))->wrapperValue);
}

DecisionTree* newDecisionTree() {
  { DecisionTree* self = NULL;

    self = new DecisionTree();
    self->falseBranch = NULL;
    self->trueBranch = NULL;
    self->concept = NULL;
    self->truthValue = false;
    self->proposition = NULL;
    self->featureIndex = NULL_INTEGER;
    self->feature = NULL;
    return (self);
  }
}

Surrogate* DecisionTree::primaryType() {
  { DecisionTree* self = this;

    return (SGT_RULE_INDUCTION_LOGIC_DECISION_TREE);
  }
}

Object* accessDecisionTreeSlotValue(DecisionTree* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_RULE_INDUCTION_LOGIC_FEATURE) {
    if (setvalueP) {
      self->feature = ((Symbol*)(value));
    }
    else {
      value = self->feature;
    }
  }
  else if (slotname == SYM_RULE_INDUCTION_LOGIC_FEATURE_INDEX) {
    if (setvalueP) {
      self->featureIndex = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->featureIndex);
    }
  }
  else if (slotname == SYM_RULE_INDUCTION_LOGIC_PROPOSITION) {
    if (setvalueP) {
      self->proposition = ((Proposition*)(value));
    }
    else {
      value = self->proposition;
    }
  }
  else if (slotname == SYM_RULE_INDUCTION_LOGIC_TRUTH_VALUE) {
    if (setvalueP) {
      self->truthValue = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->truthValue ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_RULE_INDUCTION_LOGIC_CONCEPT) {
    if (setvalueP) {
      self->concept = ((Symbol*)(value));
    }
    else {
      value = self->concept;
    }
  }
  else if (slotname == SYM_RULE_INDUCTION_LOGIC_TRUE_BRANCH) {
    if (setvalueP) {
      self->trueBranch = ((DecisionTree*)(value));
    }
    else {
      value = self->trueBranch;
    }
  }
  else if (slotname == SYM_RULE_INDUCTION_LOGIC_FALSE_BRANCH) {
    if (setvalueP) {
      self->falseBranch = ((DecisionTree*)(value));
    }
    else {
      value = self->falseBranch;
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

void DecisionTree::printObject(std::ostream* stream) {
  { DecisionTree* self = this;

    printDecisionTree(self, stream);
  }
}

List* oINDUCED_DECISION_RULESo = NULL;

int oINDUCED_RULE_COUNTERo = 0;

Vector* oCANDIDATE_CLAUSESo = NULL;

void induceInferenceRules(Symbol* relationName, Symbol* className) {
  relationName = ((Symbol*)(relationName->permanentify()));
  clearCases();
  clearTrainingExamples();
  oINDUCED_DECISION_RULESo = newList();
  className = ((Symbol*)(className->permanentify()));
  { Surrogate* clasS = getDescription(className)->surrogateValueInverse;
    Surrogate* relation = getDescription(relationName)->surrogateValueInverse;
    List* ilist = allClassInstances(clasS)->listify();
    int num = ilist->length();
    Vector* instances = stella::newVector(num);

    { Object* instance = NULL;
      Cons* iter000 = ilist->theConsList;
      int i = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        instance = iter000->value;
        i = iter001;
        (instances->theArray)[i] = (((LogicObject*)(instance)));
      }
    }
    if (oRULE_INDUCTION_STRATEGYo == KWD_RULE_INDUCTION_TOP_DOWN) {
      oENABLE_USER_THINGo = true;
      if (!oALLOW_RECURSIVE_DECISION_NODESo) {
        oTABOO_OPERATORSo->insertNew(relation);
      }
      generateClassificationRule(instances, relationName, className, true);
      { List* clauses = ((List*)(oCASE_ANTECEDENT_TABLEo->lookup(stringConcatenate(className->symbolName, "-match", 0))));

        oCANDIDATE_CLAUSESo = stella::newVector(clauses->length());
        { Cons* clause = NULL;
          Cons* iter002 = clauses->theConsList;
          int i = NULL_INTEGER;
          int iter003 = 0;

          for  (; !(iter002 == NIL); 
                iter002 = iter002->rest,
                iter003 = iter003 + 1) {
            clause = ((Cons*)(iter002->value));
            i = iter003;
            (oCANDIDATE_CLAUSESo->theArray)[i] = clause;
          }
        }
      }
      std::cout << "Generating Training Examples" << std::endl;
      generateClassificationTrainingExamples(instances, relation, oINDUCE_RULES_FROM_SIGNATURESo);
      oOPTIMIZE_INDUCED_QUERIESo = true;
      std::cout << "Generating Decision Rules" << std::endl;
      topDownRuleInduction(oTRAINING_EXAMPLESo);
    }
    else if (oRULE_INDUCTION_STRATEGYo == KWD_RULE_INDUCTION_BOTTOM_UP) {
      oENABLE_USER_THINGo = false;
      generateTrainingExamples(instances, relation);
      oOPTIMIZE_INDUCED_QUERIESo = true;
      bottomUpRuleInduction(oTRAINING_EXAMPLESo, oSIMPLIFY_RULE_ANTECEDENTpo);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oRULE_INDUCTION_STRATEGYo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

void modularInduceInferenceRules(Symbol* relationName, Symbol* className, List* modules) {
  clearTrainingExamples();
  clearCases();
  { Surrogate* clasS = getDescription(className)->surrogateValueInverse;
    Surrogate* relation = getDescription(relationName)->surrogateValueInverse;
    List* ilist = newList();
    Module* home = oMODULEo;
    boolean failUnbound = oFAIL_UNBOUND_CLAUSESpo;
    int num = ilist->length();
    Vector* instanceVec = stella::newVector(modules->length());
    Vector* instances = NULL;

    oFAIL_UNBOUND_CLAUSESpo = true;
    if (!oALLOW_RECURSIVE_DECISION_NODESo) {
      oTABOO_OPERATORSo->insertNew(relation);
    }
    if (oRULE_INDUCTION_STRATEGYo == KWD_RULE_INDUCTION_TOP_DOWN) {
      std::cout << "Building Classification Rule" << std::endl;
      oENABLE_USER_THINGo = true;
      { Module* module = NULL;
        Cons* iter000 = modules->theConsList;
        int j = NULL_INTEGER;
        int iter001 = 0;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest,
              iter001 = iter001 + 1) {
          module = ((Module*)(iter000->value));
          j = iter001;
          module->changeModule();
          ilist = allClassInstances(clasS)->listify();
          num = ilist->length();
          instances = stella::newVector(num);
          { Object* instance = NULL;
            Cons* iter002 = ilist->theConsList;
            int i = NULL_INTEGER;
            int iter003 = 0;

            for  (; !(iter002 == NIL); 
                  iter002 = iter002->rest,
                  iter003 = iter003 + 1) {
              instance = iter002->value;
              i = iter003;
              (instances->theArray)[i] = (((LogicObject*)(instance)));
            }
          }
          (instanceVec->theArray)[j] = instances;
          generateClassificationRule(instances, relationName, className, false);
        }
      }
      home->changeModule();
      buildClassificationRule(relationName, className);
      { List* clauses = ((List*)(oCASE_ANTECEDENT_TABLEo->lookup(stringConcatenate(className->symbolName, "-match", 0))));

        oCANDIDATE_CLAUSESo = stella::newVector(clauses->length());
        { Cons* clause = NULL;
          Cons* iter004 = clauses->theConsList;
          int i = NULL_INTEGER;
          int iter005 = 0;

          for  (; !(iter004 == NIL); 
                iter004 = iter004->rest,
                iter005 = iter005 + 1) {
            clause = ((Cons*)(iter004->value));
            i = iter005;
            (oCANDIDATE_CLAUSESo->theArray)[i] = clause;
          }
        }
      }
      std::cout << "Generating Training Examples" << std::endl;
      { Module* module = NULL;
        Cons* iter006 = modules->theConsList;
        Vector* vec = NULL;
        Vector* vector000 = instanceVec;
        int index000 = 0;
        int length000 = vector000->length();

        for  (; (!(iter006 == NIL)) &&
                  (index000 < length000); 
              iter006 = iter006->rest,
              index000 = index000 + 1) {
          module = ((Module*)(iter006->value));
          vec = ((Vector*)((vector000->theArray)[index000]));
          module->changeModule();
          generateClassificationTrainingExamples(vec, relation, true);
        }
      }
      std::cout << "Generating Inference Rules" << std::endl;
      topDownRuleInduction(oTRAINING_EXAMPLESo);
      oFAIL_UNBOUND_CLAUSESpo = failUnbound;
    }
    else if (oRULE_INDUCTION_STRATEGYo == KWD_RULE_INDUCTION_BOTTOM_UP) {
      oENABLE_USER_THINGo = false;
      { Module* module = NULL;
        Cons* iter007 = modules->theConsList;
        Vector* vec = NULL;
        Vector* vector001 = instanceVec;
        int index001 = 0;
        int length001 = vector001->length();

        for  (; (!(iter007 == NIL)) &&
                  (index001 < length001); 
              iter007 = iter007->rest,
              index001 = index001 + 1) {
          module = ((Module*)(iter007->value));
          vec = ((Vector*)((vector001->theArray)[index001]));
          vec = vec;
          module->changeModule();
          generateTrainingExamples(instances, relation);
        }
      }
      oOPTIMIZE_INDUCED_QUERIESo = true;
      bottomUpRuleInduction(oTRAINING_EXAMPLESo, oSIMPLIFY_RULE_ANTECEDENTpo);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oRULE_INDUCTION_STRATEGYo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

void bottomUpRuleInduction(List* examples, boolean simplifyRuleP) {
  { List* positive = newList();
    List* negative = newList();
    List* allPositive = NULL;
    List* allNegative = NULL;
    List* rules = newList();
    Symbol* concept = ((TrainingExample*)(examples->first()))->concept;
    Cons* rule = NIL;

    { TrainingExample* example = NULL;
      Cons* iter000 = examples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)(example->output)))) {
          positive->push(example);
        }
        else {
          negative->push(example);
        }
      }
    }
    allPositive = positive->copy();
    allNegative = negative->copy();
    collectFactsInExamples(positive);
    { TrainingExample* example = NULL;
      Cons* iter001 = positive->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        example = ((TrainingExample*)(iter001->value));
        example->facts = ((Cons*)(substituteConsTree(example->facts, SYM_RULE_INDUCTION_LOGIC_pY, example->name)));
      }
    }
    std::cout << "Starting rule induction with " << positive->length() << " positive and " << negative->length() << " negative examples" << std::endl;
    while (!positive->emptyP()) {
      rule = learnOneRuleBottomUp(positive, negative);
      if (rule == NIL) {
        std::cout << "Quiting with " << positive->length() << " examples uncovered" << std::endl;
        break;
      }
      else if (simplifyRuleP &&
          allNegative->nonEmptyP()) {
        rule = simplifyAntecedent(rule, getQuotedTree("((?Y) \"/LOGIC\")", "/LOGIC"), allPositive, allNegative);
      }
      else {
      }
      rules->push(listO(4, SYM_RULE_INDUCTION_STELLA_eg, cons(SYM_RULE_INDUCTION_STELLA_AND, ((Cons*)(copyConsTree(rule)))->concatenate(NIL, 0)), cons(concept, cons(SYM_RULE_INDUCTION_LOGIC_pY, NIL)), NIL));
    }
    std::cout << std::endl << "PowerLoom has induced the following rules" << std::endl << std::endl;
    if (((boolean)(rules))) {
      { Cons* rule = NULL;
        Cons* iter002 = rules->theConsList;

        for (; !(iter002 == NIL); iter002 = iter002->rest) {
          rule = ((Cons*)(iter002->value));
          std::cout << rule << std::endl;
        }
      }
      oINDUCED_DECISION_RULESo = rules;
    }
  }
}

void bottomUpRuleInductionEvaluatorWrapper(Cons* arguments) {
  bottomUpRuleInduction(((List*)(arguments->value)), ((BooleanWrapper*)(arguments->rest->value))->wrapperValue);
}

Cons* learnOneRuleBottomUp(List* positive, List* negative) {
  { Cons* lgg = NIL;
    Cons* rule = NIL;
    int score = 0;
    int numPositive = positive->length();
    int index1 = 0;
    int index2 = 0;
    Cons* facts1 = NIL;
    Cons* facts2 = NIL;
    int max = 0;
    int cover = 0;
    int numLggs = positive->length() * 5;
    Cons* bestLgg = NIL;

    std::cout << "Learning rule bottom up over " << positive->length() << " positives" << std::endl;
    max = 0;
    bestLgg = NIL;
    if (positive->length() == 1) {
      rule = ((TrainingExample*)(positive->first()))->facts;
      positive->pop();
      return (rule);
    }
    while (positive->nonEmptyP()) {
      cover = max + cover;
      max = 0;
      if (!(rule == NIL)) {
        std::cout << "   Current rule covers " << cover << " positive examples" << std::endl;
        std::cout << "           rule is " << rule << std::endl;
      }
      if (!(rule == NIL)) {
        removeCoveredExamples(rule, positive);
      }
      numLggs = positive->length() * 5;
      { int i = NULL_INTEGER;
        int iter000 = 1;
        int upperBound000 = numLggs;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter000 <= upperBound000); 
              iter000 = iter000 + 1) {
          i = iter000;
          i = i;
          index1 = stella::random(positive->length());
          facts1 = ((TrainingExample*)(positive->nth(index1)))->facts;
          if (rule == NIL) {
            {
              index2 = stella::random(positive->length());
              while (index1 == index2) {
                index2 = stella::random(positive->length());
              }
              facts2 = ((TrainingExample*)(positive->nth(index2)))->facts;
            }
          }
          else {
            facts2 = rule;
          }
          lgg = leastGeneralGeneralization(facts1, facts2);
          if (!ruleCoversAnyExampleP(lgg, negative)) {
            score = numExamplesCovered(lgg, positive);
            if (score > max) {
              std::cout << "   Best covers " << score << " positives" << std::endl;
              bestLgg = lgg;
              if ((cover + score) >= numPositive) {
                lgg = simplifyAntecedent(lgg, getQuotedTree("((?Y) \"/LOGIC\")", "/LOGIC"), positive, negative);
                removeCoveredExamples(lgg, positive);
                return (removeRedundantClauses(lgg));
              }
              max = score;
            }
          }
        }
      }
      bestLgg = simplifyAntecedent(bestLgg, getQuotedTree("((?Y) \"/LOGIC\")", "/LOGIC"), positive, negative);
      rule = bestLgg;
      if ((max == 0) ||
          (rule == NIL)) {
        break;
      }
    }
    return (removeRedundantClauses(rule));
  }
}

boolean containsOutputVariableP(Cons* clause, Cons* outputVariables) {
  { Object* term = NULL;
    Cons* iter000 = clause;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      term = iter000->value;
      { Surrogate* testValue000 = safePrimaryType(term);

        if (subtypeOfSymbolP(testValue000)) {
          { Object* term000 = term;
            Symbol* term = ((Symbol*)(term000));

            if (outputVariables->memberP(term)) {
              return (true);
            }
          }
        }
        else if (testValue000 == SGT_RULE_INDUCTION_STELLA_CONS) {
          { Object* term001 = term;
            Cons* term = ((Cons*)(term001));

            if (containsOutputVariableP(term, outputVariables)) {
              return (true);
            }
          }
        }
        else {
        }
      }
    }
  }
  return (false);
}

Cons* simplifyAntecedent(Cons* antecedent, Cons* outputVariables, List* positive, List* negative) {
  { Cons* newAntecedent = NIL;
    Cons* candidate = NIL;
    Cons* discardedPotentialGenerators = NIL;
    int coveredExamples = 0;
    int previousCoveredExamples = 0;
    int score = numExamplesCovered(antecedent, positive);

    while (!(antecedent == NIL)) {
      { Cons* head000 = ((Cons*)(antecedent->value));

        antecedent = antecedent->rest;
        candidate = head000;
      }
      if (ruleCoversAnyExampleP(append(newAntecedent, antecedent), negative)) {
        newAntecedent = cons(candidate, newAntecedent);
      }
      else {
        {
          std::cout << "Removing clause " << candidate << std::endl;
          if (containsOutputVariableP(candidate, outputVariables)) {
            discardedPotentialGenerators = cons(candidate, discardedPotentialGenerators);
          }
        }
      }
    }
    coveredExamples = numExamplesCovered(newAntecedent, positive);
    while ((!(discardedPotentialGenerators == NIL)) &&
        (coveredExamples < score)) {
      { Object* head001 = discardedPotentialGenerators->value;

        discardedPotentialGenerators = discardedPotentialGenerators->rest;
        candidate = ((Cons*)(head001));
      }
      previousCoveredExamples = coveredExamples;
      coveredExamples = numExamplesCovered(cons(candidate, newAntecedent), positive);
      if (coveredExamples > previousCoveredExamples) {
        std::cout << "Reinserting clause " << candidate << std::endl;
        newAntecedent = cons(candidate, newAntecedent);
      }
    }
    return (newAntecedent);
  }
}

DEFINE_STELLA_SPECIAL(oBOTTOM_UP_VARIABLE_COUNTERo, int , -1);

Cons* leastGeneralGeneralization(Cons* clause1, Cons* clause2) {
  { List* matches = newList();
    Cons* probe = NIL;
    Symbol* operatoR = NULL;
    List* bindings = newList();
    Cons* newClause = NIL;
    List* vars1 = getVariablesFromConsPropositions(consList(1, clause1));
    List* vars2 = getVariablesFromConsPropositions(consList(1, clause2));
    boolean notP = false;
    Symbol* var = NULL;
    Cons* result = NIL;

    { Symbol* var = NULL;
      Cons* iter000 = vars1->theConsList;
      int i = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        var = ((Symbol*)(iter000->value));
        i = iter001;
        if (!(var == SYM_RULE_INDUCTION_LOGIC_pY)) {
          clause1 = ((Cons*)(substituteConsTree(clause1, var, internSymbol(stringConcatenate("?A", stringify(wrapInteger(i)), 0)))));
        }
      }
    }
    { Symbol* var = NULL;
      Cons* iter002 = vars2->theConsList;
      int i = NULL_INTEGER;
      int iter003 = 0;

      for  (; !(iter002 == NIL); 
            iter002 = iter002->rest,
            iter003 = iter003 + 1) {
        var = ((Symbol*)(iter002->value));
        i = iter003;
        if (!(var == SYM_RULE_INDUCTION_LOGIC_pY)) {
          clause2 = ((Cons*)(substituteConsTree(clause1, var, internSymbol(stringConcatenate("?B", stringify(wrapInteger(i)), 0)))));
        }
      }
    }
    oBOTTOM_UP_VARIABLE_COUNTERo = 0;
    { Cons* clause = NULL;
      Cons* iter004 = ((Cons*)(copyConsTree(clause1)));

      for (; !(iter004 == NIL); iter004 = iter004->rest) {
        clause = ((Cons*)(iter004->value));
        if (clause->value == SYM_RULE_INDUCTION_STELLA_NOT) {
          {
            notP = true;
            probe = ((Cons*)(clause->rest->value));
          }
        }
        else {
          {
            notP = false;
            probe = clause;
          }
        }
        operatoR = ((Symbol*)(probe->value));
        matches = newList();
        { Cons* potentialMatch = NULL;
          Cons* iter005 = ((Cons*)(copyConsTree(clause2)));

          for (; !(iter005 == NIL); iter005 = iter005->rest) {
            potentialMatch = ((Cons*)(iter005->value));
            if (notP &&
                ((potentialMatch->value == SYM_RULE_INDUCTION_STELLA_NOT) &&
                 (((Cons*)(potentialMatch->rest->value))->value == operatoR))) {
              matches->push(((Cons*)(potentialMatch->rest->value)));
            }
            if ((!notP) &&
                (potentialMatch->value == operatoR)) {
              matches->push(potentialMatch);
            }
          }
        }
        if (!matches->emptyP()) {
          { Cons* match = NULL;
            Cons* iter006 = matches->theConsList;

            for (; !(iter006 == NIL); iter006 = iter006->rest) {
              match = ((Cons*)(iter006->value));
              if ((operatoR == SYM_RULE_INDUCTION_STELLA_g) ||
                  ((operatoR == SYM_RULE_INDUCTION_STELLA_l) ||
                   ((operatoR == SYM_RULE_INDUCTION_STELLA_ge) ||
                    (operatoR == SYM_RULE_INDUCTION_STELLA_el)))) {
                newClause = generalizeInequality(probe, match, bindings);
              }
              else {
                newClause = cons(operatoR, NIL);
                { Object* arg1 = NULL;
                  Cons* iter007 = probe->rest;
                  Object* arg2 = NULL;
                  Cons* iter008 = match->rest;

                  for  (; (!(iter007 == NIL)) &&
                            (!(iter008 == NIL)); 
                        iter007 = iter007->rest,
                        iter008 = iter008->rest) {
                    arg1 = iter007->value;
                    arg2 = iter008->value;
                    if (!equalConsTreesP(arg1, arg2)) {
                      {
                        var = ((Symbol*)(lookupVariableInBindings(arg1, arg2, bindings)));
                        if (!((boolean)(var))) {
                          var = internSymbol(stringConcatenate("?X", stringify(wrapInteger(oBOTTOM_UP_VARIABLE_COUNTERo)), 0));
                          if (!eitherNumbersP(arg1, arg2)) {
                            bindings->push(consList(3, arg1, arg2, var));
                          }
                          oBOTTOM_UP_VARIABLE_COUNTERo = oBOTTOM_UP_VARIABLE_COUNTERo + 1;
                        }
                        newClause = cons(var, newClause);
                      }
                    }
                    else {
                      newClause = cons(arg1, newClause);
                    }
                  }
                }
                newClause = newClause->reverse();
              }
              if (notP) {
                newClause = listO(3, SYM_RULE_INDUCTION_STELLA_NOT, newClause, NIL);
              }
              result = cons(newClause, result);
            }
          }
        }
      }
    }
    return (removeRedundantClauses(result->reverse()));
  }
}

Cons* generalizeInequality(Cons* probe, Cons* match, List* bindings) {
  { Object* operatoR = probe->value;
    Cons* newClause = consList(1, operatoR);
    Symbol* var = NULL;

    { Object* arg1 = NULL;
      Cons* iter000 = probe->rest;
      Object* arg2 = NULL;
      Cons* iter001 = match->rest;

      for  (; (!(iter000 == NIL)) &&
                (!(iter001 == NIL)); 
            iter000 = iter000->rest,
            iter001 = iter001->rest) {
        arg1 = iter000->value;
        arg2 = iter001->value;
        if (!equalConsTreesP(arg1, arg2)) {
          if (bothNumbersP(arg1, arg2)) {
            { GeneralizedSymbol* testValue000 = ((GeneralizedSymbol*)(operatoR));

              if ((testValue000 == SYM_RULE_INDUCTION_STELLA_g) ||
                  (testValue000 == SYM_RULE_INDUCTION_STELLA_ge)) {
                newClause = cons(((NumberWrapper*)(arg1))->min(((NumberWrapper*)(arg2))), newClause);
              }
              else if ((testValue000 == SYM_RULE_INDUCTION_STELLA_l) ||
                  (testValue000 == SYM_RULE_INDUCTION_STELLA_el)) {
                newClause = cons(((NumberWrapper*)(arg1))->max(((NumberWrapper*)(arg2))), newClause);
              }
              else {
                std::cout << "Bug in generalize-inequality." << std::endl;
              }
            }
          }
          else {
            {
              var = ((Symbol*)(lookupVariableInBindings(arg1, arg2, bindings)));
              if (!((boolean)(var))) {
                var = internSymbol(stringConcatenate("?X", stringify(wrapInteger(oBOTTOM_UP_VARIABLE_COUNTERo)), 0));
                if (!eitherNumbersP(arg1, arg2)) {
                  bindings->push(consList(3, arg1, arg2, var));
                }
                oBOTTOM_UP_VARIABLE_COUNTERo = oBOTTOM_UP_VARIABLE_COUNTERo + 1;
              }
              newClause = cons(var, newClause);
            }
          }
        }
        else {
          newClause = cons(arg1, newClause);
        }
      }
    }
    return (newClause->reverse());
  }
}

boolean bothNumbersP(Object* t1, Object* t2) {
  if (isaP(t1, SGT_RULE_INDUCTION_STELLA_NUMBER_WRAPPER) &&
      isaP(t2, SGT_RULE_INDUCTION_STELLA_NUMBER_WRAPPER)) {
    return (true);
  }
  else {
    return (false);
  }
}

boolean eitherNumbersP(Object* t1, Object* t2) {
  if (isaP(t1, SGT_RULE_INDUCTION_STELLA_NUMBER_WRAPPER) ||
      isaP(t2, SGT_RULE_INDUCTION_STELLA_NUMBER_WRAPPER)) {
    return (true);
  }
  else {
    return (false);
  }
}

Cons* removeRedundantClauses(Cons* clauses) {
  { Cons* result = NIL;
    HashTable* trueTable = newHashTable();
    HashTable* notTable = newHashTable();
    List* entries = NULL;
    List* sharedVariables = newList();
    List* knownVariables = newList();
    Symbol* operatoR = NULL;
    boolean subsumedP = false;
    List* operators = newList();

    { Cons* clause = NULL;
      Cons* iter000 = ((Cons*)(copyConsTree(clauses)));

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        clause = ((Cons*)(iter000->value));
        if (clause->value == SYM_RULE_INDUCTION_STELLA_NOT) {
          {
            operatoR = ((Symbol*)(((Cons*)(clause->rest->value))->value));
            operators->insertNew(operatoR);
            entries = ((List*)(notTable->lookup(operatoR)));
            if (!((boolean)(entries))) {
              entries = newList();
            }
            entries->push(((Cons*)(clause->rest->value)));
            notTable->insertAt(operatoR, entries);
          }
        }
        else {
          {
            operatoR = ((Symbol*)(clause->value));
            operators->insertNew(operatoR);
            entries = ((List*)(trueTable->lookup(operatoR)));
            if (!((boolean)(entries))) {
              entries = newList();
            }
            entries->push(clause);
            trueTable->insertAt(operatoR, entries);
          }
        }
        { Symbol* v = NULL;
          Cons* iter001 = getVariablesFromConsPropositions(consList(1, clause))->theConsList;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            v = ((Symbol*)(iter001->value));
            if (knownVariables->memberP(v)) {
              sharedVariables->insertNew(v);
            }
            else {
              knownVariables->push(v);
            }
          }
        }
      }
    }
    { Symbol* operatoR = NULL;
      Cons* iter002 = operators->theConsList;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        operatoR = ((Symbol*)(iter002->value));
        entries = ((List*)(trueTable->lookup(operatoR)));
        if (((boolean)(entries))) {
          { Cons* clause1 = NULL;
            Cons* iter003 = entries->theConsList;

            for (; !(iter003 == NIL); iter003 = iter003->rest) {
              clause1 = ((Cons*)(iter003->value));
              subsumedP = false;
              { Cons* clause2 = NULL;
                Cons* iter004 = entries->theConsList;

                for (; !(iter004 == NIL); iter004 = iter004->rest) {
                  clause2 = ((Cons*)(iter004->value));
                  if (!(clause1 == clause2)) {
                    subsumedP = true;
                    { Object* arg1 = NULL;
                      Cons* iter005 = clause1->rest;
                      Object* arg2 = NULL;
                      Cons* iter006 = clause2->rest;

                      for  (; (!(iter005 == NIL)) &&
                                (!(iter006 == NIL)); 
                            iter005 = iter005->rest,
                            iter006 = iter006->rest) {
                        arg1 = iter005->value;
                        arg2 = iter006->value;
                        if ((!equalConsTreesP(arg1, arg2)) &&
                            ((symbolP(arg1) &&
                            sharedVariables->memberP(arg1)) ||
                             consP(arg1))) {
                          subsumedP = false;
                          break;
                        }
                      }
                    }
                    if (subsumedP) {
                      break;
                    }
                  }
                }
              }
              if (!subsumedP) {
                result = cons(clause1, result);
              }
            }
          }
        }
        entries = ((List*)(notTable->lookup(operatoR)));
        if (((boolean)(entries))) {
          { Cons* clause1 = NULL;
            Cons* iter007 = entries->theConsList;

            for (; !(iter007 == NIL); iter007 = iter007->rest) {
              clause1 = ((Cons*)(iter007->value));
              subsumedP = false;
              { Cons* clause2 = NULL;
                Cons* iter008 = entries->theConsList;

                for (; !(iter008 == NIL); iter008 = iter008->rest) {
                  clause2 = ((Cons*)(iter008->value));
                  if (!(clause1 == clause2)) {
                    subsumedP = true;
                    { Object* arg1 = NULL;
                      Cons* iter009 = clause1->rest;
                      Object* arg2 = NULL;
                      Cons* iter010 = clause2->rest;

                      for  (; (!(iter009 == NIL)) &&
                                (!(iter010 == NIL)); 
                            iter009 = iter009->rest,
                            iter010 = iter010->rest) {
                        arg1 = iter009->value;
                        arg2 = iter010->value;
                        if ((!equalConsTreesP(arg1, arg2)) &&
                            ((symbolP(arg1) &&
                            sharedVariables->memberP(arg1)) ||
                             consP(arg1))) {
                          subsumedP = false;
                          break;
                        }
                      }
                    }
                    if (subsumedP) {
                      break;
                    }
                  }
                }
              }
              if (!subsumedP) {
                result = cons(listO(3, SYM_RULE_INDUCTION_STELLA_NOT, clause1, NIL), result);
              }
            }
          }
        }
      }
    }
    return (result);
  }
}

Object* lookupVariableInBindings(Object* obj1, Object* obj2, List* bindings) {
  { Cons* bind = NULL;
    Cons* iter000 = bindings->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      bind = ((Cons*)(iter000->value));
      if (equalConsTreesP(bind->value, obj1) &&
          equalConsTreesP(bind->rest->value, obj2)) {
        return (bind->rest->rest->value);
      }
    }
  }
  if (consP(obj1) &&
      consP(obj2)) {
    { Cons* answer = NIL;
      Object* bind = NULL;

      { Object* arg1 = NULL;
        Cons* iter001 = ((Cons*)(obj1));
        Object* arg2 = NULL;
        Cons* iter002 = ((Cons*)(obj2));

        for  (; (!(iter001 == NIL)) &&
                  (!(iter002 == NIL)); 
              iter001 = iter001->rest,
              iter002 = iter002->rest) {
          arg1 = iter001->value;
          arg2 = iter002->value;
          if (eqlP(arg1, arg2)) {
            answer = cons(arg1, answer);
          }
          else {
            {
              bind = lookupVariableInBindings(arg1, arg2, bindings);
              if (!((boolean)(bind))) {
                return (NULL);
              }
              answer = cons(bind, answer);
            }
          }
        }
      }
      return (answer->reverse());
    }
  }
  return (NULL);
}

Cons* learnOneRuleBottomUpFromSignatures(List* positive, List* negative, List* covered, Vector* consProps) {
  { List* tempPositive = positive->copy();
    int max = 0;
    int cover = 0;
    int index1 = 0;
    int index2 = 0;
    int vecSize = ((TrainingExample*)(negative->first()))->input->length();
    List* indices = NULL;
    List* bestIndices = newList();
    Vector* lgg = NULL;
    Vector* sig1 = NULL;
    Vector* sig2 = NULL;
    boolean stop = false;
    Cons* result = NIL;
    int score = 0;
    int numLggs = 0;

    while ((max > 0) ||
        (!((boolean)(lgg)))) {
      cover = cover + max;
      std::cout << "   Current rule covers " << cover << " positive examples" << std::endl;
      if (((boolean)(lgg))) {
        { TrainingExample* example = NULL;
          Cons* iter000 = removeSignatureCoveredExamples(bestIndices, tempPositive)->theConsList;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            example = ((TrainingExample*)(iter000->value));
            covered->push(example);
          }
        }
      }
      numLggs = tempPositive->length() * 1;
      max = 0;
      { int i = NULL_INTEGER;
        int iter001 = 1;
        int upperBound000 = numLggs;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter001 <= upperBound000); 
              iter001 = iter001 + 1) {
          i = iter001;
          i = i;
          index1 = stella::random(tempPositive->length());
          sig1 = ((TrainingExample*)(tempPositive->nth(index1)))->input;
          if (!((boolean)(lgg))) {
            {
              index2 = stella::random(tempPositive->length());
              while (index1 == index2) {
                index2 = stella::random(tempPositive->length());
              }
              sig2 = ((TrainingExample*)(tempPositive->nth(index2)))->input;
            }
          }
          else {
            sig2 = lgg;
          }
          indices = intersectSignatures(sig1, sig2);
          if (!signatureIndicesCoverAnyExampleP(indices, negative)) {
            score = numSignatureIndicesCovered(indices, tempPositive);
            if (score > max) {
              std::cout << "    New best: " << score << " examples" << std::endl;
              bestIndices = indices;
              max = score;
            }
          }
        }
      }
      lgg = stella::newVector(vecSize);
      { int i = NULL_INTEGER;
        int iter002 = 0;
        int upperBound001 = vecSize - 1;

        for  (; iter002 <= upperBound001; 
              iter002 = iter002 + 1) {
          i = iter002;
          (lgg->theArray)[i] = (wrapInteger(2));
        }
      }
      { IntegerWrapper* index = NULL;
        Cons* iter003 = bestIndices->theConsList;

        for (; !(iter003 == NIL); iter003 = iter003->rest) {
          index = ((IntegerWrapper*)(iter003->value));
          if (index->wrapperValue > 0) {
            (lgg->theArray)[(index->wrapperValue - 1)] = (wrapInteger(1));
          }
          else {
            (lgg->theArray)[((0 - index->wrapperValue) - 1)] = (wrapInteger(0));
          }
        }
      }
    }
    while (stop) {
      stop = true;
      { IntegerWrapper* index = NULL;
        Cons* iter004 = bestIndices->copy()->theConsList;

        for (; !(iter004 == NIL); iter004 = iter004->rest) {
          index = ((IntegerWrapper*)(iter004->value));
          if (!signatureIndicesCoverAnyExampleP(((List*)(bestIndices->copy()->remove(index))), negative)) {
            std::cout << "     Removing clause" << std::endl;
            bestIndices = ((List*)(bestIndices->remove(index)));
            stop = false;
            break;
          }
        }
      }
    }
    { IntegerWrapper* index = NULL;
      Cons* iter005 = bestIndices->theConsList;

      for (; !(iter005 == NIL); iter005 = iter005->rest) {
        index = ((IntegerWrapper*)(iter005->value));
        if (index->wrapperValue > 0) {
          result = cons(((Cons*)((consProps->theArray)[(index->wrapperValue - 1)])), result);
        }
        else {
          result = cons(listO(3, SYM_RULE_INDUCTION_LOGIC_FAIL, ((Cons*)((consProps->theArray)[((0 - index->wrapperValue) - 1)])), NIL), result);
        }
      }
    }
    return (result);
  }
}

List* intersectSignatures(Vector* sig1, Vector* sig2) {
  { List* result = newList();

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = sig1->length() - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        if (eqlP((sig1->theArray)[i], ONE_WRAPPER) &&
            eqlP((sig2->theArray)[i], ONE_WRAPPER)) {
          result->push(wrapInteger(i + 1));
        }
        if (eqlP((sig1->theArray)[i], ZERO_WRAPPER) &&
            eqlP((sig2->theArray)[i], ZERO_WRAPPER)) {
          result->push(wrapInteger(0 - (i + 1)));
        }
      }
    }
    return (result);
  }
}

List* removeSignatureCoveredExamples(List* indices, List* examples) {
  { List* removed = newList();

    { TrainingExample* example = NULL;
      Cons* iter000 = examples->copy()->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (signatureIndicesCoverExampleP(indices, example)) {
          removed->push(example);
          examples = ((List*)(examples->remove(example)));
        }
      }
    }
    return (removed);
  }
}

int numSignatureIndicesCovered(List* indices, List* examples) {
  { int count = 0;

    { TrainingExample* example = NULL;
      Cons* iter000 = examples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (signatureIndicesCoverExampleP(indices, example)) {
          count = count + 1;
        }
      }
    }
    return (count);
  }
}

boolean signatureIndicesCoverAnyExampleP(List* indices, List* examples) {
  { TrainingExample* example = NULL;
    Cons* iter000 = examples->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      example = ((TrainingExample*)(iter000->value));
      if (signatureIndicesCoverExampleP(indices, example)) {
        return (true);
      }
    }
  }
  return (false);
}

boolean signatureIndicesCoverExampleP(List* indices, TrainingExample* example) {
  { int actual = 0;

    { IntegerWrapper* index = NULL;
      Cons* iter000 = indices->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        index = ((IntegerWrapper*)(iter000->value));
        actual = integerAbs(index->wrapperValue) - 1;
        if (index->wrapperValue > 0) {
          if (eqlP((example->input->theArray)[actual], ZERO_WRAPPER)) {
            return (false);
          }
        }
        else {
          if (eqlP((example->input->theArray)[actual], ONE_WRAPPER)) {
            return (false);
          }
        }
      }
    }
  }
  return (true);
}

void topDownRuleInduction(List* examples) {
  { List* positive = newList();
    List* allPositives = newList();
    List* negative = newList();
    List* uncovered = NULL;
    List* covered = newList();
    Cons* antecedent = NIL;
    List* linkedAntecedents = NULL;
    Symbol* concept = ((TrainingExample*)(examples->first()))->concept;
    int numRules = 0;
    int loopCheck = 0;
    boolean signaturesP = oINDUCE_RULES_FROM_SIGNATURESo;
    Vector* consProps = NULL;
    List* props = newList();
    Vector* propositionVector = NULL;

    oINDUCED_DECISION_RULESo = newList();
    if (((boolean)(((TrainingExample*)(oTRAINING_EXAMPLESo->first()))->module))) {
      ((TrainingExample*)(oTRAINING_EXAMPLESo->first()))->module->changeModule();
    }
    props = getClassificationRelations(((TrainingExample*)(oTRAINING_EXAMPLESo->first()))->query);
    consProps = stella::newVector(props->length());
    propositionVector = stella::newVector(props->length());
    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = props->length() - 1;
      Proposition* prop = NULL;
      Cons* iter001 = props->theConsList;

      for  (; (iter000 <= upperBound000) &&
                (!(iter001 == NIL)); 
            iter000 = iter000 + 1,
            iter001 = iter001->rest) {
        i = iter000;
        prop = ((Proposition*)(iter001->value));
        (propositionVector->theArray)[i] = prop;
        (consProps->theArray)[i] = (propositionToCons(prop));
      }
    }
    { TrainingExample* example = NULL;
      Cons* iter002 = examples->theConsList;

      for (; !(iter002 == NIL); iter002 = iter002->rest) {
        example = ((TrainingExample*)(iter002->value));
        if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)(example->output)))) {
          {
            positive->push(example);
            allPositives->push(example);
          }
        }
        else {
          negative->push(example);
        }
      }
    }
    std::cout << "Starting rule induction with " << positive->length() << " positive and " << negative->length() << " negative examples" << std::endl;
    while (!positive->emptyP()) {
      std::cout << std::endl << positive->length() << " positive examples left to be covered" << std::endl;
      covered = newList();
      linkedAntecedents = list(1, NIL);
      if (oINDUCE_RULES_FROM_SIGNATURESo) {
        if (oSIGNATURE_STRATEGYo == KWD_RULE_INDUCTION_BOTTOM_UP) {
          antecedent = learnOneRuleBottomUpFromSignatures(positive, negative, covered, consProps);
          linkedAntecedents = linkVariablesInInducedRule(antecedent, covered, consProps);
        }
        else if (oSIGNATURE_STRATEGYo == KWD_RULE_INDUCTION_DECISION_TREE) {
          uncovered = newList();
          { TrainingExample* example = NULL;
            Cons* iter003 = positive->theConsList;

            for (; !(iter003 == NIL); iter003 = iter003->rest) {
              example = ((TrainingExample*)(iter003->value));
              uncovered->push(example);
            }
          }
          { TrainingExample* example = NULL;
            Cons* iter004 = negative->theConsList;

            for (; !(iter004 == NIL); iter004 = iter004->rest) {
              example = ((TrainingExample*)(iter004->value));
              uncovered->push(example);
            }
          }
          { Cons* treeRule = NULL;
            Cons* iter005 = getRulesFromTree(((TrainingExample*)(uncovered->first()))->query, induceDecisionTree(uncovered))->theConsList;
            Cons* collect000 = NULL;

            for  (; !(iter005 == NIL); 
                  iter005 = iter005->rest) {
              treeRule = ((Cons*)(iter005->value));
              if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)(treeRule->value)))) {
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(treeRule->rest, NIL);
                    if (linkedAntecedents->theConsList == NIL) {
                      linkedAntecedents->theConsList = collect000;
                    }
                    else {
                      addConsToEndOfConsList(linkedAntecedents->theConsList, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(treeRule->rest, NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
          }
          linkedAntecedents = ((List*)(linkedAntecedents->remove(NIL)));
        }
        else if (oSIGNATURE_STRATEGYo == KWD_RULE_INDUCTION_TOP_DOWN) {
          antecedent = learnOneRuleTopDownFromSignatures(positive, negative, covered, consProps);
          linkedAntecedents = linkVariablesInInducedRule(antecedent, covered, consProps);
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << oSIGNATURE_STRATEGYo << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      { Cons* ant = NULL;
        Cons* iter006 = linkedAntecedents->theConsList;

        for (; !(iter006 == NIL); iter006 = iter006->rest) {
          ant = ((Cons*)(iter006->value));
          covered = getCoveredExamples(ant, negative);
          if ((covered->length() < 10) ||
              ((covered->length() < positive->length()) ||
               (ant == NIL))) {
            if (covered->length() > 0) {
              ant = specializeRule(ant, oCANDIDATE_CLAUSESo, positive, covered);
              loopCheck = 0;
              while ((!(ant == NIL)) &&
                  ruleCoversAnyExampleP(ant, negative)) {
                loopCheck = loopCheck + 1;
                if (loopCheck == 4) {
                  ant = NIL;
                  covered = negative;
                  break;
                }
                ant = specializeRule(ant, oCANDIDATE_CLAUSESo, positive, covered);
              }
              if (!(ant == NIL)) {
                covered = NULL;
              }
            }
            if ((!((boolean)(covered))) ||
                covered->emptyP()) {
              covered = getCoveredExamples(ant, positive);
              { TrainingExample* example = NULL;
                Cons* iter007 = covered->theConsList;

                for (; !(iter007 == NIL); iter007 = iter007->rest) {
                  example = ((TrainingExample*)(iter007->value));
                  positive = ((List*)(positive->remove(example)));
                }
              }
              if (covered->length() == 0) {
                std::cout << "No Positives Covered by" << ant << std::endl;
              }
              if (covered->length() > 0) {
                oINDUCED_DECISION_RULESo->push(listO(4, SYM_RULE_INDUCTION_STELLA_eg, cons(SYM_RULE_INDUCTION_STELLA_AND, ((Cons*)(copyConsTree(ant)))->reverse()->concatenate(NIL, 0)), cons(concept, cons(SYM_RULE_INDUCTION_LOGIC_pY, NIL)), NIL));
                std::cout << "Adding rule to cover " << covered->length() << " examples" << std::endl;
              }
            }
          }
        }
      }
      if (oINDUCED_DECISION_RULESo->length() == numRules) {
        {
          if (!oINDUCE_RULES_FROM_SIGNATURESo) {
            std::cout << "Stopping with " << positive->length() << " examples uncovered" << std::endl;
            break;
          }
          std::cout << positive->length() << " examples uncovered, switching to full query-based induction" << std::endl;
          oINDUCE_RULES_FROM_SIGNATURESo = false;
        }
      }
      else {
        oINDUCE_RULES_FROM_SIGNATURESo = signaturesP;
      }
      numRules = oINDUCED_DECISION_RULESo->length();
    }
    oINDUCE_RULES_FROM_SIGNATURESo = signaturesP;
    std::cout << std::endl << "PowerLoom has induced the following rules" << std::endl << std::endl;
    { Cons* rule = NULL;
      Cons* iter008 = oINDUCED_DECISION_RULESo->theConsList;

      for (; !(iter008 == NIL); iter008 = iter008->rest) {
        rule = ((Cons*)(iter008->value));
        std::cout << rule << std::endl;
      }
    }
  }
}

Cons* buildAntecedentFromRuleIndex(Vector* props, List* ruleIndex) {
  { Cons* antecedent = NIL;
    Cons* consProp = NIL;

    { IntegerWrapper* index = NULL;
      Cons* iter000 = ruleIndex->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        index = ((IntegerWrapper*)(iter000->value));
        if (index->wrapperValue < 0) {
          consProp = listO(3, SYM_RULE_INDUCTION_LOGIC_FAIL, ((Cons*)((props->theArray)[(integerAbs(index->wrapperValue) - 1)])), NIL);
        }
        else {
          consProp = ((Cons*)((props->theArray)[(integerAbs(index->wrapperValue) - 1)]));
        }
        antecedent = cons(consProp, antecedent);
      }
    }
    return (antecedent);
  }
}

Cons* learnOneRuleTopDownFromSignatures(List* positive, List* negative, List* covered_pos, Vector* consProps) {
  { double current_utility = 0.0;
    List* rule = newList();
    double gain = 0.0;
    double max_gain = 0.0;
    List* used_features = newList();
    int num_features = 0;
    List* vars = newList();
    Vector* variableTable = NULL;
    int feature_index = 0;
    List* covered_neg = newList();

    std::cout << "Learning rule top down from signatures over " << positive->length() << " positives" << std::endl;
    if (positive->emptyP()) {
      return (NIL);
    }
    num_features = ((TrainingExample*)(positive->first()))->input->length();
    variableTable = stella::newVector(num_features + 1);
    { int i = NULL_INTEGER;
      int iter000 = 1;
      int upperBound000 = num_features;
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter000 <= upperBound000); 
            iter000 = iter000 + 1) {
        i = iter000;
        (variableTable->theArray)[i] = (getVariablesFromConsPropositions(consList(1, ((Cons*)((consProps->theArray)[(i - 1)])))));
      }
    }
    vars->push(SYM_RULE_INDUCTION_LOGIC_pY);
    { TrainingExample* example = NULL;
      Cons* iter001 = negative->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest) {
        example = ((TrainingExample*)(iter001->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(example, NIL);
            if (covered_neg->theConsList == NIL) {
              covered_neg->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(covered_neg->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(example, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { TrainingExample* example = NULL;
      Cons* iter002 = positive->theConsList;
      Cons* collect001 = NULL;

      for  (; !(iter002 == NIL); 
            iter002 = iter002->rest) {
        example = ((TrainingExample*)(iter002->value));
        if (!((boolean)(collect001))) {
          {
            collect001 = cons(example, NIL);
            if (covered_pos->theConsList == NIL) {
              covered_pos->theConsList = collect001;
            }
            else {
              addConsToEndOfConsList(covered_pos->theConsList, collect001);
            }
          }
        }
        else {
          {
            collect001->rest = cons(example, NIL);
            collect001 = collect001->rest;
          }
        }
      }
    }
    while (!covered_neg->emptyP()) {
      current_utility = foilUtility(covered_pos->length(), covered_neg->length());
      max_gain = 0.0;
      { int i = NULL_INTEGER;
        int iter003 = 1;
        int upperBound001 = num_features;
        boolean unboundedP001 = upperBound001 == NULL_INTEGER;

        for  (; unboundedP001 ||
                  (iter003 <= upperBound001); 
              iter003 = iter003 + 1) {
          i = iter003;
          if (!used_features->memberP(wrapInteger(i))) {
            { boolean testValue000 = false;

              testValue000 = oENFORCE_LINKED_VARIABLESo;
              if (testValue000) {
                { boolean foundP000 = false;

                  { Symbol* ele = NULL;
                    Cons* iter004 = ((List*)((variableTable->theArray)[i]))->theConsList;

                    for (; !(iter004 == NIL); iter004 = iter004->rest) {
                      ele = ((Symbol*)(iter004->value));
                      if (vars->memberP(ele)) {
                        foundP000 = true;
                        break;
                      }
                    }
                  }
                  testValue000 = foundP000;
                }
                testValue000 = !testValue000;
              }
              if (testValue000) {
                gain = -9999.0;
              }
              else {
                gain = foilGain(i, current_utility, covered_pos, covered_neg);
              }
            }
            if (oTRACE_FOILo) {
              std::cout << "Foil gain on feature " << i << ": " << gain << std::endl;
            }
            if (gain > max_gain) {
              feature_index = i;
              max_gain = gain;
            }
            { boolean testValue001 = false;

              testValue001 = oENFORCE_LINKED_VARIABLESo;
              if (testValue001) {
                { boolean foundP001 = false;

                  { Symbol* ele = NULL;
                    Cons* iter005 = ((List*)((variableTable->theArray)[i]))->theConsList;

                    for (; !(iter005 == NIL); iter005 = iter005->rest) {
                      ele = ((Symbol*)(iter005->value));
                      if (vars->memberP(ele)) {
                        foundP001 = true;
                        break;
                      }
                    }
                  }
                  testValue001 = foundP001;
                }
                testValue001 = !testValue001;
              }
              if (testValue001) {
                gain = -9999.0;
              }
              else {
                gain = foilGain(0 - i, current_utility, covered_pos, covered_neg);
              }
            }
            if (oTRACE_FOILo) {
              std::cout << "Foil gain on feature " << i << ": " << gain << std::endl;
            }
            if (gain > max_gain) {
              feature_index = 0 - i;
              max_gain = gain;
            }
          }
        }
      }
      if (max_gain == 0.0) {
        covered_pos = newList();
        std::cout << "   Darn, nothing we can do here, returning nil." << std::endl;
        return (NIL);
      }
      if (oTRACE_FOILo) {
        std::cout << "** Choosing feature " << ((Cons*)((consProps->theArray)[(integerAbs(feature_index - 1))])) << std::endl;
      }
      if (oENFORCE_LINKED_VARIABLESo) {
        { Symbol* var = NULL;
          Cons* iter006 = ((List*)((variableTable->theArray)[(((feature_index < 0) ? (0 - feature_index) : feature_index))]))->theConsList;

          for (; !(iter006 == NIL); iter006 = iter006->rest) {
            var = ((Symbol*)(iter006->value));
            if (!vars->memberP(var)) {
              vars->push(var);
            }
          }
        }
      }
      updateCoveredExamples(feature_index, covered_pos, covered_neg);
      used_features->push(wrapInteger(((feature_index < 0) ? (0 - feature_index) : feature_index)));
      rule->push(wrapInteger(feature_index));
    }
    std::cout << "   Returning with " << covered_pos->length() << " positives and " << covered_neg->length() << " negatives covered" << std::endl;
    return (buildAntecedentFromRuleIndex(consProps, rule));
  }
}

void updateExampleMatches(List* examples, int index, IntegerWrapper* matchValue) {
  { Cons* temp = NIL;

    { TrainingExample* example = NULL;
      Cons* iter000 = examples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (example->input->length() <= index) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Bad training example, not enough features.  Needs " << "`" << (index + 1) << "'" << std::endl << "`" << example->query << "'" << std::endl;
        }
        else if (eqlP((example->input->theArray)[index], matchValue)) {
          temp = cons(example, temp);
        }
      }
    }
    examples->theConsList = temp;
  }
}

void updateCoveredExamples(int feature_index, List* covered_pos, List* covered_neg) {
  { IntegerWrapper* matchValue = ((feature_index > 0) ? ZERO_WRAPPER : ONE_WRAPPER);
    int index = (((feature_index < 0) ? (0 - feature_index) : feature_index)) - 1;

    updateExampleMatches(covered_pos, index, matchValue);
    updateExampleMatches(covered_neg, index, matchValue);
  }
}

int countExampleMatches(List* examples, int index, IntegerWrapper* matchValue) {
  { int n = 0;

    { TrainingExample* example = NULL;
      Cons* iter000 = examples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (example->input->length() <= index) {
          *(STANDARD_WARNING->nativeStream) << "Warning: " << "Bad training example, not enough features.  Needs " << "`" << (index + 1) << "'" << std::endl << "`" << example->query << "'" << std::endl;
        }
        else if (eqlP((example->input->theArray)[index], matchValue)) {
          n = n + 1;
        }
      }
    }
    return (n);
  }
}

double foilGain(int featureIndex, double utility, List* coveredPos, List* coveredNeg) {
  { IntegerWrapper* matchValue = ((featureIndex < 0) ? ZERO_WRAPPER : ONE_WRAPPER);
    int index = (((featureIndex < 0) ? (0 - featureIndex) : featureIndex)) - 1;
    int p = countExampleMatches(coveredPos, index, matchValue);
    int n = countExampleMatches(coveredNeg, index, matchValue);

    return (p * (foilUtility(p, n) - utility));
  }
}

double foilUtility(int p, int n) {
  if (p == 0) {
    return (((double)(0)));
  }
  return (::log((((double)(p)) / (p + n))) / LOG_2);
}

Cons* learnOneRuleTopDown(Vector* propositions, List* positive, List* negative) {
  return (specializeRule(NIL, propositions, positive, negative));
}

Cons* specializeRule(Cons* rule, Vector* propositions, List* positive, List* negative) {
  std::cout << "Specializing " << std::endl;
  { List* candidates = newList();
    List* coveredNegs = newList();
    List* coveredPos = newList();
    double current_utility = 0.0;
    int featureIndex = 0;
    Cons* newClause = NIL;
    List* vars = getVariablesFromConsPropositions(rule);
    Vector* variableTable = NULL;
    double gain = 0.0;
    double max = 0.0;

    { TrainingExample* example = NULL;
      Cons* iter000 = negative->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (ruleCoversExampleP(rule, example)) {
          coveredNegs->push(example);
        }
      }
    }
    { TrainingExample* example = NULL;
      Cons* iter001 = positive->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        example = ((TrainingExample*)(iter001->value));
        if (ruleCoversExampleP(rule, example)) {
          coveredPos->push(example);
        }
      }
    }
    if (coveredNegs->emptyP()) {
      std::cout << " No covered negatives" << std::endl;
      return (rule);
    }
    if (!vars->memberP(SYM_RULE_INDUCTION_LOGIC_pY)) {
      vars->push(SYM_RULE_INDUCTION_LOGIC_pY);
    }
    variableTable = stella::newVector(propositions->length() + 1);
    { int i = NULL_INTEGER;
      int iter002 = 1;
      int upperBound000 = propositions->length();

      for  (; iter002 <= upperBound000; 
            iter002 = iter002 + 1) {
        i = iter002;
        (variableTable->theArray)[i] = (getVariablesFromConsPropositions(consList(1, ((Cons*)((propositions->theArray)[(i - 1)])))));
      }
    }
    { int i = NULL_INTEGER;
      int iter003 = 1;
      int upperBound001 = propositions->length();

      for  (; iter003 <= upperBound001; 
            iter003 = iter003 + 1) {
        i = iter003;
        candidates->push(wrapInteger(i));
        candidates->push(wrapInteger(0 - i));
      }
    }
    { Cons* clause = NULL;
      Cons* iter004 = rule;

      for (; !(iter004 == NIL); iter004 = iter004->rest) {
        clause = ((Cons*)(iter004->value));
        { Cons* prop = NULL;
          Vector* vector000 = propositions;
          int index000 = 0;
          int length000 = vector000->length();
          int i = NULL_INTEGER;
          int iter005 = 1;

          for  (; index000 < length000; 
                index000 = index000 + 1,
                iter005 = iter005 + 1) {
            prop = ((Cons*)((vector000->theArray)[index000]));
            i = iter005;
            if (equalConsTreesP(prop, clause)) {
              candidates = ((List*)(candidates->remove(wrapInteger(i))));
              break;
            }
            if (equalConsTreesP(listO(3, SYM_RULE_INDUCTION_LOGIC_FAIL, prop, NIL), clause)) {
              candidates = ((List*)(candidates->remove(wrapInteger(0 - i))));
              break;
            }
          }
        }
      }
    }
    while (!coveredNegs->emptyP()) {
      std::cout << "   Covers " << coveredNegs->length() << " negs, and " << coveredPos->length() << " pos" << std::endl;
      current_utility = foilUtility(coveredPos->length(), coveredNegs->length());
      max = 0.0;
      { IntegerWrapper* i = NULL;
        Cons* iter006 = candidates->copy()->theConsList;

        for (; !(iter006 == NIL); iter006 = iter006->rest) {
          i = ((IntegerWrapper*)(iter006->value));
          { boolean foundP000 = false;

            { Symbol* ele = NULL;
              Cons* iter007 = ((List*)((variableTable->theArray)[(integerAbs(i->wrapperValue))]))->theConsList;

              for (; !(iter007 == NIL); iter007 = iter007->rest) {
                ele = ((Symbol*)(iter007->value));
                if (vars->memberP(ele)) {
                  foundP000 = true;
                  break;
                }
              }
            }
            if (foundP000) {
              if (i->wrapperValue > 0) {
                gain = queryFoilGain(cons(((Cons*)((propositions->theArray)[(i->wrapperValue - 1)])), rule), current_utility, coveredPos, coveredNegs);
              }
              else {
                gain = queryFoilGain(cons(listO(3, SYM_RULE_INDUCTION_LOGIC_FAIL, ((Cons*)((propositions->theArray)[((0 - i->wrapperValue) - 1)])), NIL), rule), current_utility, coveredPos, coveredNegs);
              }
              if (gain > max) {
                std::cout << "    Current: " << ((Cons*)((propositions->theArray)[(integerAbs(i->wrapperValue) - 1)])) << ": " << gain;
                if (i->wrapperValue < 0) {
                  std::cout << " Negated" << std::endl;
                }
                else {
                  std::cout << std::endl;
                }
                featureIndex = i->wrapperValue;
                max = gain;
              }
            }
          }
        }
      }
      if (max == 0.0) {
        std::cout << "   No features provide any gain" << std::endl;
        std::cout << "   Can't separate " << std::endl;
        { TrainingExample* pos = NULL;
          Cons* iter008 = coveredPos->theConsList;

          for (; !(iter008 == NIL); iter008 = iter008->rest) {
            pos = ((TrainingExample*)(iter008->value));
            std::cout << "     " << pos->name << std::endl;
          }
        }
        std::cout << "   From " << std::endl;
        { TrainingExample* neg = NULL;
          Cons* iter009 = coveredNegs->theConsList;

          for (; !(iter009 == NIL); iter009 = iter009->rest) {
            neg = ((TrainingExample*)(iter009->value));
            std::cout << "     " << neg->name << std::endl;
          }
        }
        return (NIL);
      }
      { Symbol* var = NULL;
        Cons* iter010 = ((List*)((variableTable->theArray)[(((featureIndex < 0) ? (0 - featureIndex) : featureIndex))]))->theConsList;

        for (; !(iter010 == NIL); iter010 = iter010->rest) {
          var = ((Symbol*)(iter010->value));
          if (!vars->memberP(var)) {
            vars->push(var);
          }
        }
      }
      candidates = ((List*)(candidates->remove(wrapInteger(featureIndex))));
      newClause = ((Cons*)(copyConsTree(((Cons*)((propositions->theArray)[((((featureIndex < 0) ? (0 - featureIndex) : featureIndex)) - 1)])))));
      if (featureIndex < 0) {
        newClause = listO(3, SYM_RULE_INDUCTION_LOGIC_FAIL, newClause, NIL);
      }
      std::cout << "   Adding clause " << newClause << std::endl;
      rule = cons(newClause, rule);
      removeExcludedExamples(rule, coveredPos, coveredNegs);
    }
    return (rule);
  }
}

void removeExcludedExamples(Cons* rule, List* coveredPos, List* coveredNeg) {
  { TrainingExample* example = NULL;
    Cons* iter000 = coveredNeg->copy()->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      example = ((TrainingExample*)(iter000->value));
      if (!ruleCoversExampleP(rule, example)) {
        coveredNeg = ((List*)(coveredNeg->remove(example)));
      }
    }
  }
  { TrainingExample* example = NULL;
    Cons* iter001 = coveredPos->copy()->theConsList;

    for (; !(iter001 == NIL); iter001 = iter001->rest) {
      example = ((TrainingExample*)(iter001->value));
      if (!ruleCoversExampleP(rule, example)) {
        coveredPos = ((List*)(coveredPos->remove(example)));
      }
    }
  }
}

double queryFoilGain(Cons* rule, double utility, List* coveredPos, List* coveredNeg) {
  { int p = 0;
    int n = 0;
    double result = 0.0;

    { TrainingExample* example = NULL;
      Cons* iter000 = coveredNeg->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (ruleCoversExampleP(rule, example)) {
          n = n + 1;
        }
      }
    }
    { TrainingExample* example = NULL;
      Cons* iter001 = coveredPos->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        example = ((TrainingExample*)(iter001->value));
        if (ruleCoversExampleP(rule, example)) {
          p = p + 1;
        }
      }
    }
    if ((p == 0) &&
        (n == 0)) {
      return (0.0);
    }
    result = p * (foilUtility(p, n) - utility);
    if (result < 1.0e-6) {
      result = 0.0;
    }
    return (result);
  }
}

void queryAndUpdateCoveredExamples(Cons* rule, List* uncovered, List* covered) {
  { TrainingExample* example = NULL;
    Cons* iter000 = uncovered->copy()->theConsList;
    Cons* collect000 = NULL;

    for  (; !(iter000 == NIL); 
          iter000 = iter000->rest) {
      example = ((TrainingExample*)(iter000->value));
      if (ruleCoversExampleP(rule, example)) {
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(example, NIL);
            if (covered->theConsList == NIL) {
              covered->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(covered->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(example, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
  }
}

void removeCoveredExamples(Cons* rule, List* uncovered) {
  { TrainingExample* example = NULL;
    Cons* iter000 = uncovered->copy()->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      example = ((TrainingExample*)(iter000->value));
      if (ruleCoversExampleP(rule, example)) {
        uncovered = ((List*)(uncovered->remove(example)));
      }
    }
  }
}

int numExamplesCovered(Cons* rule, List* examples) {
  { int count = 0;

    { TrainingExample* example = NULL;
      Cons* iter000 = examples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (ruleCoversExampleP(rule, example)) {
          count = count + 1;
        }
      }
    }
    return (count);
  }
}

List* getCoveredExamples(Cons* rule, List* uncovered) {
  { List* covered = newList();

    { TrainingExample* example = NULL;
      Cons* iter000 = uncovered->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (ruleCoversExampleP(rule, example)) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(example, NIL);
              if (covered->theConsList == NIL) {
                covered->theConsList = collect000;
              }
              else {
                addConsToEndOfConsList(covered->theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(example, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (covered);
  }
}

boolean ruleCoversAnyExampleP(Cons* rule, List* examples) {
  { TrainingExample* example = NULL;
    Cons* iter000 = examples->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      example = ((TrainingExample*)(iter000->value));
      if (ruleCoversExampleP(rule, example)) {
        return (true);
      }
    }
  }
  return (false);
}

boolean ruleCoversExampleP(Cons* reverseRule, TrainingExample* example) {
  if (reverseRule == NIL) {
    return (true);
  }
  { QueryIterator* query = NULL;
    Cons* rule = ((Cons*)(copyConsTree(reverseRule)))->reverse();
    List* vars = ((List*)(getVariablesFromConsPropositions(rule)->remove(SYM_RULE_INDUCTION_LOGIC_pY)));
    Cons* consQuery = NIL;
    Cons* types = NIL;

    if (((boolean)(example->module))) {
      example->module->changeModule();
    }
    consQuery = cons(SYM_RULE_INDUCTION_STELLA_AND, ((Cons*)(substituteConsTree(rule, example->name, SYM_RULE_INDUCTION_LOGIC_pY))));
    if (!vars->emptyP()) {
      { Symbol* var = NULL;
        Cons* iter000 = vars->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          var = ((Symbol*)(iter000->value));
          if (oENABLE_USER_THINGo &&
              ((var->symbolName)[1] == 'X')) {
            types = cons(cons(var, cons(SYM_RULE_INDUCTION_LOGIC_USER_THING, NIL)), types);
          }
          else {
            types = cons(var, types);
          }
        }
      }
      consQuery = listO(3, SYM_RULE_INDUCTION_STELLA_EXISTS, types, cons(consQuery, NIL));
    }
    if (oOPTIMIZE_INDUCED_QUERIESo) {
      query = makeQuery(NIL, consQuery, NIL, listO(3, KWD_RULE_INDUCTION_TIMEOUT, wrapInteger(300), NIL));
    }
    else {
      query = makeQuery(NIL, consQuery, NIL, listO(5, KWD_RULE_INDUCTION_TIMEOUT, wrapInteger(300), KWD_RULE_INDUCTION_DONT_OPTIMIZEp, SYM_RULE_INDUCTION_STELLA_TRUE, NIL));
    }
    return (trueTruthValueP(callAsk(query)));
  }
}

List* linkVariablesInInducedRule(Cons* rule, List* examples, Vector* consProps) {
  { List* vars = NULL;
    Cons* tempRule = NIL;
    Symbol* var = NULL;
    List* unlinked = NULL;
    List* linked = NULL;
    List* newRules = newList();

    vars = getVariablesFromConsPropositions(rule);
    { TrainingExample* example = NULL;
      Cons* iter000 = examples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (!((boolean)(example->input))) {
          example->input = createInputSignature(example->query);
        }
        tempRule = ((Cons*)(copyConsTree(rule)));
        unlinked = newList();
        linked = newList();
        { Symbol* var = NULL;
          Cons* iter001 = vars->theConsList;
          Cons* collect000 = NULL;

          for  (; !(iter001 == NIL); 
                iter001 = iter001->rest) {
            var = ((Symbol*)(iter001->value));
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(var, NIL);
                if (unlinked->theConsList == NIL) {
                  unlinked->theConsList = collect000;
                }
                else {
                  addConsToEndOfConsList(unlinked->theConsList, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(var, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        unlinked = ((List*)(unlinked->remove(SYM_RULE_INDUCTION_LOGIC_pY)));
        linked->push(SYM_RULE_INDUCTION_LOGIC_pY);
        while (!unlinked->emptyP()) {
          var = ((Symbol*)(unlinked->pop()));
          { Cons* prop = NULL;
            Vector* vector000 = consProps;
            int index000 = 0;
            int length000 = vector000->length();
            int i = NULL_INTEGER;
            int iter002 = 0;

            for  (; index000 < length000; 
                  index000 = index000 + 1,
                  iter002 = iter002 + 1) {
              prop = ((Cons*)((vector000->theArray)[index000]));
              i = iter002;
              if (prop->memberP(var)) {
                { boolean foundP000 = false;

                  { Object* ele = NULL;
                    Cons* iter003 = tempRule;

                    for (; !(iter003 == NIL); iter003 = iter003->rest) {
                      ele = iter003->value;
                      if (equalConsTreesP(ele, prop)) {
                        foundP000 = true;
                        break;
                      }
                    }
                  }
                  if (foundP000) {
                    linked->push(var);
                    break;
                  }
                }
                if (eqlP((example->input->theArray)[i], ONE_WRAPPER)) {
                  tempRule = tempRule->concatenate(consList(1, ((Cons*)(copyConsTree(prop)))), 0);
                  { Object* newVar = NULL;
                    Cons* iter004 = prop->rest;

                    for (; !(iter004 == NIL); iter004 = iter004->rest) {
                      newVar = iter004->value;
                      if ((!(newVar == var)) &&
                          (symbolP(newVar) &&
                           (!linked->memberP(newVar)))) {
                        unlinked->push(((Symbol*)(newVar)));
                      }
                    }
                  }
                  linked->push(var);
                  break;
                }
              }
            }
          }
        }
        { boolean testValue000 = false;

          { boolean foundP001 = false;

            { Cons* ele = NULL;
              Cons* iter005 = newRules->theConsList;

              for (; !(iter005 == NIL); iter005 = iter005->rest) {
                ele = ((Cons*)(iter005->value));
                if (equalConsTreesP(ele, tempRule)) {
                  foundP001 = true;
                  break;
                }
              }
            }
            testValue000 = foundP001;
          }
          testValue000 = !testValue000;
          if (testValue000) {
            newRules->push(tempRule);
          }
        }
      }
    }
    { ListIterator* it = ((ListIterator*)(newRules->allocateIterator()));

      for (; it->nextP(); ) {
        it->valueSetter(((Cons*)(((Cons*)(it->value))))->reverse());
      }
    }
    return (newRules);
  }
}

Vector* evaluateRuleInduction(Symbol* relationName, Symbol* className, int numTrials, int curveSplits) {
  { Surrogate* clasS = getDescription(className)->surrogateValueInverse;
    Surrogate* relation = getDescription(relationName)->surrogateValueInverse;
    List* ilist = allClassInstances(clasS)->listify();
    int num = ilist->length();
    double numTrain = (1 * num) / 2.0;
    double currentSplit = numTrain;
    Vector* trainingInstances = NULL;
    Vector* instances = stella::newVector(num);
    double result = 0.0;
    Vector* results = stella::newVector(curveSplits);

    { Object* instance = NULL;
      Cons* iter000 = ilist->theConsList;
      int i = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        instance = iter000->value;
        i = iter001;
        (instances->theArray)[i] = (((LogicObject*)(instance)));
      }
    }
    { int i = NULL_INTEGER;
      int iter002 = 0;
      int upperBound000 = curveSplits - 1;

      for  (; iter002 <= upperBound000; 
            iter002 = iter002 + 1) {
        i = iter002;
        (results->theArray)[i] = (wrapFloat(0.0));
      }
    }
    { int split = NULL_INTEGER;
      int iter003 = 0;
      int upperBound001 = curveSplits - 1;

      for  (; iter003 <= upperBound001; 
            iter003 = iter003 + 1) {
        split = iter003;
        currentSplit = numTrain * (((double)(split + 1)) / curveSplits);
        { int i = NULL_INTEGER;
          int iter004 = 0;
          int upperBound002 = numTrials - 1;

          for  (; iter004 <= upperBound002; 
                iter004 = iter004 + 1) {
            i = iter004;
            shuffleVector(instances);
            std::cout << "Starting Trial " << (i + 1) << " of split " << (split + 1) << " with " << currentSplit << " examples" << std::endl;
            clearTrainingExamples();
            clearCases();
            trainingInstances = stella::newVector(((int)(currentSplit)));
            { int j = NULL_INTEGER;
              int iter005 = 0;
              int upperBound003 = ((int)(currentSplit - 1));

              for  (; iter005 <= upperBound003; 
                    iter005 = iter005 + 1) {
                j = iter005;
                (trainingInstances->theArray)[j] = (((LogicObject*)((instances->theArray)[j])));
              }
            }
            if (oRULE_INDUCTION_STRATEGYo == KWD_RULE_INDUCTION_TOP_DOWN) {
              oENABLE_USER_THINGo = true;
              std::cout << "  Creating Match Criteria" << std::endl;
              generateClassificationRule(trainingInstances, relationName, className, true);
              setCandidateClauses(className);
              std::cout << "  Generating Training Examples" << std::endl;
              generateClassificationTrainingExamples(instances, relation, true);
              oOPTIMIZE_INDUCED_QUERIESo = true;
            }
            else if (oRULE_INDUCTION_STRATEGYo == KWD_RULE_INDUCTION_BOTTOM_UP) {
              oENABLE_USER_THINGo = false;
              generateTrainingExamples(instances, relation);
              oOPTIMIZE_INDUCED_QUERIESo = true;
            }
            else {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "`" << oRULE_INDUCTION_STRATEGYo << "'" << " is not a valid case option";
                throw *newStellaException(stream000->theStringReader());
              }
            }
            oTRAINING_EXAMPLESo = oTRAINING_EXAMPLESo->reverse();
            { List* trainSet = newList();
              List* testSet = newList();

              { TrainingExample* example = NULL;
                Cons* iter006 = oTRAINING_EXAMPLESo->theConsList;
                int j = NULL_INTEGER;
                int iter007 = 0;

                for  (; !(iter006 == NIL); 
                      iter006 = iter006->rest,
                      iter007 = iter007 + 1) {
                  example = ((TrainingExample*)(iter006->value));
                  j = iter007;
                  if (j < currentSplit) {
                    trainSet->push(example);
                  }
                  if (j >= numTrain) {
                    testSet->push(example);
                  }
                }
              }
              result = trainAndTestRuleInduction(trainSet, testSet);
              (results->theArray)[split] = (wrapFloat(((FloatWrapper*)((results->theArray)[split]))->wrapperValue + result));
              std::cout << std::endl << "  Result: " << result << std::endl;
            }
          }
        }
      }
    }
    { int i = NULL_INTEGER;
      int iter008 = 0;
      int upperBound004 = curveSplits - 1;

      for  (; iter008 <= upperBound004; 
            iter008 = iter008 + 1) {
        i = iter008;
        (results->theArray)[i] = (wrapFloat(((FloatWrapper*)((results->theArray)[i]))->wrapperValue / numTrials));
      }
    }
    return (results);
  }
}

Vector* evaluateRuleInductionEvaluatorWrapper(Cons* arguments) {
  return (evaluateRuleInduction(((Symbol*)(arguments->value)), ((Symbol*)(arguments->rest->value)), ((IntegerWrapper*)(arguments->rest->rest->value))->wrapperValue, ((IntegerWrapper*)(arguments->rest->rest->rest->value))->wrapperValue));
}

double trainAndTestRuleInduction(List* trainSet, List* testSet) {
  { Module* homeModule = ((Module*)(oCONTEXTo));
    Module* testModule = findOrCreateModule(stringConcatenate(((Module*)(oCONTEXTo))->moduleFullName, "INDUCED-RULES", 0));
    double result = 0.0;

    testModule->changeModule();
    clearContext(testModule);
    if (oRULE_INDUCTION_STRATEGYo == KWD_RULE_INDUCTION_TOP_DOWN) {
      topDownRuleInduction(trainSet);
    }
    else if (oRULE_INDUCTION_STRATEGYo == KWD_RULE_INDUCTION_BOTTOM_UP) {
      bottomUpRuleInduction(trainSet, oSIMPLIFY_RULE_ANTECEDENTpo);
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oRULE_INDUCTION_STRATEGYo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    assertInducedRules();
    result = testTheoryOverExamples(testSet);
    homeModule->changeModule();
    return (result);
  }
}

void induceDecisionRules(Symbol* relationName, Symbol* className) {
  relationName = ((Symbol*)(relationName->permanentify()));
  clearCases();
  clearTrainingExamples();
  oINDUCED_DECISION_RULESo = newList();
  className = ((Symbol*)(className->permanentify()));
  { Surrogate* clasS = getDescription(className)->surrogateValueInverse;
    Surrogate* relation = getDescription(relationName)->surrogateValueInverse;
    List* ilist = allClassInstances(clasS)->listify();
    int num = ilist->length();
    DecisionTree* tree = NULL;
    Vector* instances = stella::newVector(num);

    { Object* instance = NULL;
      Cons* iter000 = ilist->theConsList;
      int i = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        instance = iter000->value;
        i = iter001;
        (instances->theArray)[i] = (((LogicObject*)(instance)));
      }
    }
    if (!oALLOW_RECURSIVE_DECISION_NODESo) {
      oTABOO_OPERATORSo->insertNew(relation);
    }
    generateClassificationRule(instances, relationName, className, true);
    std::cout << "Generating Training Examples" << std::endl;
    generateClassificationTrainingExamples(instances, relation, true);
    std::cout << "Generating Decision Rules" << std::endl;
    tree = induceDecisionTree(oTRAINING_EXAMPLESo);
    tree->concept = relationName;
    getRulesFromTree(((TrainingExample*)(oTRAINING_EXAMPLESo->first()))->query, tree);
  }
}

void modularInduceDecisionRules(Symbol* relationName, Symbol* className, List* modules) {
  relationName = ((Symbol*)(relationName->permanentify()));
  className = ((Symbol*)(className->permanentify()));
  clearTrainingExamples();
  clearCases();
  { Surrogate* clasS = getDescription(className)->surrogateValueInverse;
    Surrogate* relation = getDescription(relationName)->surrogateValueInverse;
    List* ilist = newList();
    DecisionTree* tree = NULL;
    Module* home = oMODULEo;
    int num = ilist->length();
    Vector* instanceVec = stella::newVector(modules->length());
    Vector* instances = NULL;

    if (!oALLOW_RECURSIVE_DECISION_NODESo) {
      oTABOO_OPERATORSo->insertNew(relation);
    }
    std::cout << "Building Classification Rule" << std::endl;
    { Module* module = NULL;
      Cons* iter000 = modules->theConsList;
      int j = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        module = ((Module*)(iter000->value));
        j = iter001;
        module->changeModule();
        ilist = allClassInstances(clasS)->listify();
        num = ilist->length();
        instances = stella::newVector(num);
        { Object* instance = NULL;
          Cons* iter002 = ilist->theConsList;
          int i = NULL_INTEGER;
          int iter003 = 0;

          for  (; !(iter002 == NIL); 
                iter002 = iter002->rest,
                iter003 = iter003 + 1) {
            instance = iter002->value;
            i = iter003;
            (instances->theArray)[i] = (((LogicObject*)(instance)));
          }
        }
        (instanceVec->theArray)[j] = instances;
        generateClassificationRule(instances, relationName, className, false);
      }
    }
    home->changeModule();
    buildClassificationRule(relationName, className);
    std::cout << "Generating Training Examples" << std::endl;
    { Module* module = NULL;
      Cons* iter004 = modules->theConsList;
      Vector* vec = NULL;
      Vector* vector000 = instanceVec;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; (!(iter004 == NIL)) &&
                (index000 < length000); 
            iter004 = iter004->rest,
            index000 = index000 + 1) {
        module = ((Module*)(iter004->value));
        vec = ((Vector*)((vector000->theArray)[index000]));
        module->changeModule();
        generateClassificationTrainingExamples(vec, relation, true);
      }
    }
    std::cout << "Inducing Decision Tree" << std::endl;
    tree = induceDecisionTree(oTRAINING_EXAMPLESo);
    tree->concept = relationName;
    if (((boolean)(((TrainingExample*)(oTRAINING_EXAMPLESo->first()))->module))) {
      ((TrainingExample*)(oTRAINING_EXAMPLESo->first()))->module->changeModule();
    }
  }
}

boolean askDecisionTree(DecisionTree* tree, Cons* query) {
  { Vector* signature = createInputSignature(query);

    return (traverseDecisionTree(tree, signature));
  }
}

boolean traverseDecisionTree(DecisionTree* tree, Vector* features) {
  if (!((boolean)(tree->feature))) {
    return (tree->truthValue);
  }
  if (eqlP(((IntegerWrapper*)((features->theArray)[(tree->featureIndex)])), ONE_WRAPPER)) {
    return (traverseDecisionTree(tree->trueBranch, features));
  }
  else {
    return (traverseDecisionTree(tree->falseBranch, features));
  }
}

DecisionTree* induceDecisionTree(List* examples) {
  { List* features = newList();
    Symbol* feature = NULL;
    DecisionTree* tree = NULL;
    List* props = newList();
    HashTable* propositionTable = newHashTable();

    std::cout << "  Inducing decision tree" << std::endl;
    if (((boolean)(((TrainingExample*)(examples->first()))->module))) {
      ((TrainingExample*)(examples->first()))->module->changeModule();
    }
    props = getClassificationRelations(((TrainingExample*)(examples->first()))->query);
    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = props->length() - 1;
      Cons* collect000 = NULL;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        feature = internSymbol(stringConcatenate("A", stringify(wrapInteger(i)), 0));
        propositionTable->insertAt(feature, ((Proposition*)(props->nth(i))));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(feature, NIL);
            if (features->theConsList == NIL) {
              features->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(features->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(feature, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    tree = ((DecisionTree*)(buildDecisionTree(examples, features, NIL)));
    addPropositionsToDecisionTree(tree, propositionTable);
    return (tree);
  }
}

void addPropositionsToDecisionTree(DecisionTree* tree, HashTable* table) {
  if (!((boolean)(tree->feature))) {
    return;
  }
  tree->proposition = ((Proposition*)(table->lookup(tree->feature)));
  addPropositionsToDecisionTree(tree->trueBranch, table);
  addPropositionsToDecisionTree(tree->falseBranch, table);
}

Object* buildDecisionTree(List* examples, List* features, Cons* featureStack) {
  { int p = 0;
    int n = 0;
    double currentEntropy = 0.0;
    double newEntropy = 0.0;
    DecisionTree* tree = newDecisionTree();
    double minNewEntropy = 1.0;
    int featureIndex = 0;
    Symbol* splitFeature = NULL;

    { TrainingExample* example = NULL;
      Cons* iter000 = examples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)(example->output)))) {
          p = p + 1;
        }
        else {
          n = n + 1;
        }
      }
    }
    if (p > n) {
      tree->truthValue = true;
    }
    else {
      tree->truthValue = false;
    }
    if ((p == 0) ||
        (n == 0)) {
      return (tree);
    }
    currentEntropy = entropy(p, n);
    { Symbol* feature = NULL;
      Cons* iter001 = features->theConsList;
      int i = NULL_INTEGER;
      int iter002 = 0;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest,
            iter002 = iter002 + 1) {
        feature = ((Symbol*)(iter001->value));
        i = iter002;
        if (!featureStack->memberP(feature)) {
          newEntropy = expectedEntropy(i, examples);
          if (newEntropy < minNewEntropy) {
            if (oTRACE_ID3o) {
              std::cout << "Info gain for feature " << feature << ": " << (currentEntropy - newEntropy) << std::endl;
            }
            minNewEntropy = newEntropy;
            featureIndex = i;
            splitFeature = feature;
          }
        }
      }
    }
    if (oTRACE_ID3o) {
      std::cout << "Splitting on feature " << splitFeature << std::endl;
    }
    if (!((boolean)(splitFeature))) {
      return (tree);
    }
    { List* leftExamples = newList();
      List* rightExamples = newList();

      { TrainingExample* example = NULL;
        Cons* iter003 = examples->theConsList;

        for (; !(iter003 == NIL); iter003 = iter003->rest) {
          example = ((TrainingExample*)(iter003->value));
          if (eqlP((example->input->theArray)[featureIndex], ONE_WRAPPER)) {
            leftExamples->push(example);
          }
          else {
            rightExamples->push(example);
          }
        }
      }
      tree->feature = splitFeature;
      tree->featureIndex = featureIndex;
      tree->trueBranch = ((DecisionTree*)(buildDecisionTree(leftExamples, features, cons(splitFeature, featureStack))));
      tree->falseBranch = ((DecisionTree*)(buildDecisionTree(rightExamples, features, cons(splitFeature, featureStack))));
    }
    return (tree);
  }
}

double expectedEntropy(int featureIndex, List* examples) {
  { double e = 0.0;
    int numExamples = examples->length();
    int p = 0;
    int n = 0;

    { TrainingExample* example = NULL;
      Cons* iter000 = examples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (eqlP((example->input->theArray)[featureIndex], ONE_WRAPPER)) {
          if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)(example->output)))) {
            p = p + 1;
          }
          else {
            n = n + 1;
          }
        }
      }
    }
    e = (((double)(p + n)) / numExamples) * entropy(p, n);
    p = 0;
    n = 0;
    { TrainingExample* example = NULL;
      Cons* iter001 = examples->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        example = ((TrainingExample*)(iter001->value));
        if (eqlP((example->input->theArray)[featureIndex], ZERO_WRAPPER)) {
          if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)(example->output)))) {
            p = p + 1;
          }
          else {
            n = n + 1;
          }
        }
      }
    }
    e = e + ((((double)(p + n)) / numExamples) * entropy(p, n));
    return (e);
  }
}

double entropy(int p, int n) {
  if ((p == 0) &&
      (n == 0)) {
    return (0.0);
  }
  { int sum = p + n;
    double posImpurity = 0.0;
    double posPerc = ((double)(p)) / sum;
    double negImpurity = 0.0;
    double negPerc = ((double)(n)) / sum;

    if (p == 0) {
      posImpurity = 0.0;
    }
    else {
      posImpurity = 0 - (posPerc * (::log(posPerc) / ::log((2.0))));
    }
    if (n == 0) {
      negImpurity = 0.0;
    }
    else {
      negImpurity = 0 - (negPerc * (::log(negPerc) / ::log((2.0))));
    }
    return (posImpurity + negImpurity);
  }
}

void printDecisionTree(DecisionTree* tree, std::ostream* stream) {
  helpPrintDecisionTree(tree, 0, stream);
}

void helpPrintDecisionTree(DecisionTree* tree, int level, std::ostream* stream) {
  if (!((boolean)(tree->feature))) {
    if (tree->truthValue) {
      *(stream) << "True" << std::endl;
    }
    else {
      *(stream) << "False" << std::endl;
    }
    return;
  }
  *(stream) << std::endl;
  { int i = NULL_INTEGER;
    int iter000 = 1;
    int upperBound000 = level;
    boolean unboundedP000 = upperBound000 == NULL_INTEGER;

    for  (; unboundedP000 ||
              (iter000 <= upperBound000); 
          iter000 = iter000 + 1) {
      i = iter000;
      i = i;
      *(stream) << "|   ";
    }
  }
  *(stream) << tree->proposition << " = 1: ";
  helpPrintDecisionTree(tree->trueBranch, level + 1, stream);
  { int i = NULL_INTEGER;
    int iter001 = 1;
    int upperBound001 = level;
    boolean unboundedP001 = upperBound001 == NULL_INTEGER;

    for  (; unboundedP001 ||
              (iter001 <= upperBound001); 
          iter001 = iter001 + 1) {
      i = iter001;
      i = i;
      *(stream) << "|   ";
    }
  }
  *(stream) << tree->proposition << " = 0: ";
  helpPrintDecisionTree(tree->falseBranch, level + 1, stream);
}

List* getRulesFromTree(Cons* query, DecisionTree* tree) {
  std::cout << "  Extracting rules from decision tree" << std::endl;
  return (buildRulesFromTree(tree, getClassificationRelations(query)));
}

List* buildRulesFromTree(DecisionTree* tree, List* props) {
  { List* rules = newList();
    Cons* consProps = NIL;

    { Proposition* prop = NULL;
      Cons* iter000 = props->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        prop = ((Proposition*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(propositionToCons(prop), NIL);
            if (consProps == NIL) {
              consProps = collect000;
            }
            else {
              addConsToEndOfConsList(consProps, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(propositionToCons(prop), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    oINDUCED_DECISION_RULESo = newList();
    extractPathsFromTree(tree, NIL, rules);
    return (rules);
  }
}

void extractPathsFromTree(DecisionTree* tree, Cons* antecedentStack, List* antecedent) {
  if (!((boolean)(tree->feature))) {
    antecedent->push(cons((tree->truthValue ? TRUE_WRAPPER : FALSE_WRAPPER), antecedentStack));
    return;
  }
  { Cons* prop = propositionToCons(tree->proposition);

    extractPathsFromTree(tree->trueBranch, cons(prop, antecedentStack), antecedent);
    extractPathsFromTree(tree->falseBranch, cons(listO(3, SYM_RULE_INDUCTION_LOGIC_FAIL, prop, NIL), antecedentStack), antecedent);
  }
}

void sortExamplesByTree(DecisionTree* tree, List* examples, List* sortedExamples) {
  if (!((boolean)(tree->feature))) {
    sortedExamples->push(examples);
    return;
  }
  { List* trueExamples = newList();
    List* falseExamples = newList();

    { TrainingExample* example = NULL;
      Cons* iter000 = examples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (eqlP((example->input->theArray)[(tree->featureIndex)], ONE_WRAPPER)) {
          trueExamples->push(example);
        }
        else {
          falseExamples->push(example);
        }
      }
    }
    sortExamplesByTree(tree->trueBranch, trueExamples, sortedExamples);
    sortExamplesByTree(tree->falseBranch, falseExamples, sortedExamples);
  }
}

void assertInducedRules() {
  { Cons* command = NIL;
    Symbol* name = NULL;
    List* vars = NULL;
    Cons* types = NIL;

    { Cons* rule = NULL;
      Cons* iter000 = oINDUCED_DECISION_RULESo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        rule = ((Cons*)(iter000->value));
        name = internSymbol(stringConcatenate("Induced-Rule-", stringify(wrapInteger(oINDUCED_RULE_COUNTERo)), 0));
        vars = getVariablesFromConsPropositions(rule);
        types = NIL;
        if (oENABLE_USER_THINGo) {
          { Symbol* var = NULL;
            Cons* iter001 = vars->theConsList;
            Cons* collect000 = NULL;

            for  (; !(iter001 == NIL); 
                  iter001 = iter001->rest) {
              var = ((Symbol*)(iter001->value));
              if (!((boolean)(collect000))) {
                {
                  collect000 = cons(cons(var, cons(SYM_RULE_INDUCTION_LOGIC_USER_THING, NIL)), NIL);
                  if (types == NIL) {
                    types = collect000;
                  }
                  else {
                    addConsToEndOfConsList(types, collect000);
                  }
                }
              }
              else {
                {
                  collect000->rest = cons(cons(var, cons(SYM_RULE_INDUCTION_LOGIC_USER_THING, NIL)), NIL);
                  collect000 = collect000->rest;
                }
              }
            }
          }
        }
        else {
          { Symbol* var = NULL;
            Cons* iter002 = vars->theConsList;
            Cons* collect001 = NULL;

            for  (; !(iter002 == NIL); 
                  iter002 = iter002->rest) {
              var = ((Symbol*)(iter002->value));
              if (!((boolean)(collect001))) {
                {
                  collect001 = cons(var, NIL);
                  if (types == NIL) {
                    types = collect001;
                  }
                  else {
                    addConsToEndOfConsList(types, collect001);
                  }
                }
              }
              else {
                {
                  collect001->rest = cons(var, NIL);
                  collect001 = collect001->rest;
                }
              }
            }
          }
        }
        oINDUCED_RULE_COUNTERo = oINDUCED_RULE_COUNTERo + 1;
        command = listO(3, SYM_RULE_INDUCTION_LOGIC_DEFRULE, name, cons(listO(3, SYM_RULE_INDUCTION_STELLA_FORALL, types, cons(((Cons*)(copyConsTree(rule))), NIL)), NIL));
        if (oLOG_INDUCED_RULESo) {
          std::cout << command << std::endl << std::endl;
        }
        else {
          std::cout << "Asserting " << name << std::endl;
        }
        evaluateLogicCommand(command, false);
      }
    }
  }
}

void setCandidateClauses(Symbol* className) {
  { List* clauses = ((List*)(oCASE_ANTECEDENT_TABLEo->lookup(stringConcatenate(className->symbolName, "-match", 0))));

    oCANDIDATE_CLAUSESo = stella::newVector(clauses->length());
    { Cons* clause = NULL;
      Cons* iter000 = clauses->theConsList;
      int k = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        clause = ((Cons*)(iter000->value));
        k = iter001;
        (oCANDIDATE_CLAUSESo->theArray)[k] = clause;
      }
    }
  }
}

List* getVariablesFromPropositionList(List* props) {
  { List* theList = newList();
    Symbol* variable = NULL;

    { Proposition* prop = NULL;
      Cons* iter000 = props->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        prop = ((Proposition*)(iter000->value));
        { Keyword* testValue000 = prop->kind;

          if ((testValue000 == KWD_RULE_INDUCTION_OR) ||
              ((testValue000 == KWD_RULE_INDUCTION_NOT) ||
               (testValue000 == KWD_RULE_INDUCTION_AND))) {
            { Symbol* var = NULL;
              Cons* iter001 = getVariablesFromPropositionList(((List*)(prop->arguments->listify())))->theConsList;

              for (; !(iter001 == NIL); iter001 = iter001->rest) {
                var = ((Symbol*)(iter001->value));
                theList->insertNew(var);
              }
            }
          }
          else {
            { Object* arg = NULL;
              Vector* vector000 = prop->arguments;
              int index000 = 0;
              int length000 = vector000->length();

              for  (; index000 < length000; 
                    index000 = index000 + 1) {
                arg = (vector000->theArray)[index000];
                { Surrogate* testValue001 = safePrimaryType(arg);

                  if (subtypeOfP(testValue001, SGT_RULE_INDUCTION_LOGIC_PATTERN_VARIABLE)) {
                    { Object* arg000 = arg;
                      PatternVariable* arg = ((PatternVariable*)(arg000));

                      variable = arg->skolemName;
                    }
                  }
                  else if (subtypeOfSymbolP(testValue001)) {
                    { Object* arg001 = arg;
                      Symbol* arg = ((Symbol*)(arg001));

                      variable = arg;
                    }
                  }
                  else if (subtypeOfSurrogateP(testValue001)) {
                    { Object* arg002 = arg;
                      Surrogate* arg = ((Surrogate*)(arg002));

                      variable = internSymbol(arg->symbolName);
                    }
                  }
                  else if (subtypeOfFloatP(testValue001)) {
                    { Object* arg003 = arg;
                      FloatWrapper* arg = ((FloatWrapper*)(arg003));

                      variable = NULL;
                    }
                  }
                  else if (subtypeOfIntegerP(testValue001)) {
                    { Object* arg004 = arg;
                      IntegerWrapper* arg = ((IntegerWrapper*)(arg004));

                      variable = NULL;
                    }
                  }
                  else if (subtypeOfStringP(testValue001)) {
                    { Object* arg005 = arg;
                      StringWrapper* arg = ((StringWrapper*)(arg005));

                      variable = NULL;
                    }
                  }
                  else if (subtypeOfP(testValue001, SGT_RULE_INDUCTION_LOGIC_PROPOSITION)) {
                    { Object* arg006 = arg;
                      Proposition* arg = ((Proposition*)(arg006));

                      std::cout << "Dave, you've got a proposition" << std::endl;
                    }
                  }
                  else if (subtypeOfP(testValue001, SGT_RULE_INDUCTION_LOGIC_LOGIC_OBJECT)) {
                    { Object* arg007 = arg;
                      LogicObject* arg = ((LogicObject*)(arg007));

                      variable = objectName(arg);
                    }
                  }
                  else {
                    { OutputStringStream* stream000 = newOutputStringStream();

                      *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                      throw *newStellaException(stream000->theStringReader());
                    }
                  }
                }
                if (((boolean)(variable))) {
                  theList->insertNew(variable);
                }
              }
            }
          }
        }
      }
    }
    return (theList);
  }
}

List* getVariablesFromConsPropositions(Cons* props) {
  return (helpGetVariablesFromConsPropositions(props, newList()));
}

List* helpGetVariablesFromConsPropositions(Object* ele, List* theList) {
  { Surrogate* testValue000 = safePrimaryType(ele);

    if (testValue000 == SGT_RULE_INDUCTION_STELLA_CONS) {
      { Object* ele000 = ele;
        Cons* ele = ((Cons*)(ele000));

        { Object* arg = NULL;
          Cons* iter000 = ele;

          for (; !(iter000 == NIL); iter000 = iter000->rest) {
            arg = iter000->value;
            helpGetVariablesFromConsPropositions(arg, theList);
          }
        }
      }
    }
    else if (subtypeOfSymbolP(testValue000)) {
      { Object* ele001 = ele;
        Symbol* ele = ((Symbol*)(ele001));

        if ((ele->symbolName)[0] == '?') {
          theList->insertNew(ele);
        }
      }
    }
    else {
    }
  }
  return (theList);
}

List* getPropositionsFromDecisionTree(DecisionTree* tree) {
  if (!((boolean)(tree->feature))) {
    return (newList());
  }
  { List* theList = getPropositionsFromDecisionTree(tree->trueBranch)->concatenate(getPropositionsFromDecisionTree(tree->falseBranch), 0);

    theList->push(tree->proposition);
    return (theList);
  }
}

void helpStartupRuleInduction1() {
  {
    KWD_RULE_INDUCTION_TOP_DOWN = ((Keyword*)(internRigidSymbolWrtModule("TOP-DOWN", NULL, 2)));
    SGT_RULE_INDUCTION_LOGIC_DECISION_TREE = ((Surrogate*)(internRigidSymbolWrtModule("DECISION-TREE", NULL, 1)));
    SYM_RULE_INDUCTION_LOGIC_FEATURE = ((Symbol*)(internRigidSymbolWrtModule("FEATURE", NULL, 0)));
    SYM_RULE_INDUCTION_LOGIC_FEATURE_INDEX = ((Symbol*)(internRigidSymbolWrtModule("FEATURE-INDEX", NULL, 0)));
    SYM_RULE_INDUCTION_LOGIC_PROPOSITION = ((Symbol*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 0)));
    SYM_RULE_INDUCTION_LOGIC_TRUTH_VALUE = ((Symbol*)(internRigidSymbolWrtModule("TRUTH-VALUE", NULL, 0)));
    SYM_RULE_INDUCTION_LOGIC_CONCEPT = ((Symbol*)(internRigidSymbolWrtModule("CONCEPT", NULL, 0)));
    SYM_RULE_INDUCTION_LOGIC_TRUE_BRANCH = ((Symbol*)(internRigidSymbolWrtModule("TRUE-BRANCH", NULL, 0)));
    SYM_RULE_INDUCTION_LOGIC_FALSE_BRANCH = ((Symbol*)(internRigidSymbolWrtModule("FALSE-BRANCH", NULL, 0)));
    KWD_RULE_INDUCTION_BOTTOM_UP = ((Keyword*)(internRigidSymbolWrtModule("BOTTOM-UP", NULL, 2)));
    SYM_RULE_INDUCTION_LOGIC_pY = ((Symbol*)(internRigidSymbolWrtModule("?Y", NULL, 0)));
    SYM_RULE_INDUCTION_STELLA_eg = ((Symbol*)(internRigidSymbolWrtModule("=>", getStellaModule("/STELLA", true), 0)));
    SYM_RULE_INDUCTION_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    SGT_RULE_INDUCTION_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    SYM_RULE_INDUCTION_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", getStellaModule("/STELLA", true), 0)));
    SYM_RULE_INDUCTION_STELLA_g = ((Symbol*)(internRigidSymbolWrtModule(">", getStellaModule("/STELLA", true), 0)));
    SYM_RULE_INDUCTION_STELLA_l = ((Symbol*)(internRigidSymbolWrtModule("<", getStellaModule("/STELLA", true), 0)));
    SYM_RULE_INDUCTION_STELLA_ge = ((Symbol*)(internRigidSymbolWrtModule(">=", getStellaModule("/STELLA", true), 0)));
    SYM_RULE_INDUCTION_STELLA_el = ((Symbol*)(internRigidSymbolWrtModule("=<", getStellaModule("/STELLA", true), 0)));
    SGT_RULE_INDUCTION_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SYM_RULE_INDUCTION_LOGIC_FAIL = ((Symbol*)(internRigidSymbolWrtModule("FAIL", NULL, 0)));
    KWD_RULE_INDUCTION_DECISION_TREE = ((Keyword*)(internRigidSymbolWrtModule("DECISION-TREE", NULL, 2)));
    SYM_RULE_INDUCTION_LOGIC_USER_THING = ((Symbol*)(internRigidSymbolWrtModule("USER-THING", NULL, 0)));
    SYM_RULE_INDUCTION_STELLA_EXISTS = ((Symbol*)(internRigidSymbolWrtModule("EXISTS", getStellaModule("/STELLA", true), 0)));
    KWD_RULE_INDUCTION_TIMEOUT = ((Keyword*)(internRigidSymbolWrtModule("TIMEOUT", NULL, 2)));
    KWD_RULE_INDUCTION_DONT_OPTIMIZEp = ((Keyword*)(internRigidSymbolWrtModule("DONT-OPTIMIZE?", NULL, 2)));
    SYM_RULE_INDUCTION_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", getStellaModule("/STELLA", true), 0)));
    SYM_RULE_INDUCTION_LOGIC_DEFRULE = ((Symbol*)(internRigidSymbolWrtModule("DEFRULE", NULL, 0)));
    SYM_RULE_INDUCTION_STELLA_FORALL = ((Symbol*)(internRigidSymbolWrtModule("FORALL", getStellaModule("/STELLA", true), 0)));
    KWD_RULE_INDUCTION_OR = ((Keyword*)(internRigidSymbolWrtModule("OR", NULL, 2)));
    KWD_RULE_INDUCTION_NOT = ((Keyword*)(internRigidSymbolWrtModule("NOT", NULL, 2)));
    KWD_RULE_INDUCTION_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    SGT_RULE_INDUCTION_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", NULL, 1)));
    SGT_RULE_INDUCTION_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    SGT_RULE_INDUCTION_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
    SYM_RULE_INDUCTION_LOGIC_STARTUP_RULE_INDUCTION = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-RULE-INDUCTION", NULL, 0)));
    SYM_RULE_INDUCTION_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupRuleInduction2() {
  {
    defineFunctionObject("SET-SIGNATURE-STRATEGY", "(DEFUN SET-SIGNATURE-STRATEGY ((K KEYWORD)) :COMMAND? TRUE)", ((cpp_function_code)(&setSignatureStrategy)), NULL);
    defineFunctionObject("SET-SIGNATURE-RULES", "(DEFUN SET-SIGNATURE-RULES ((B BOOLEAN)) :COMMAND? TRUE)", ((cpp_function_code)(&setSignatureRules)), ((cpp_function_code)(&setSignatureRulesEvaluatorWrapper)));
    defineFunctionObject("SET-RULE-INDUCTION-STRATEGY", "(DEFUN SET-RULE-INDUCTION-STRATEGY ((K KEYWORD)) :COMMAND? TRUE)", ((cpp_function_code)(&setRuleInductionStrategy)), NULL);
    defineFunctionObject("SET-RECURSIVE-DECISION-NODES", "(DEFUN SET-RECURSIVE-DECISION-NODES ((B BOOLEAN)) :COMMAND? TRUE)", ((cpp_function_code)(&setRecursiveDecisionNodes)), ((cpp_function_code)(&setRecursiveDecisionNodesEvaluatorWrapper)));
    defineFunctionObject("INDUCE-INFERENCE-RULES", "(DEFUN INDUCE-INFERENCE-RULES ((RELATION-NAME SYMBOL) (CLASS-NAME SYMBOL)) :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&induceInferenceRules)), NULL);
    defineFunctionObject("MODULAR-INDUCE-INFERENCE-RULES", "(DEFUN MODULAR-INDUCE-INFERENCE-RULES ((RELATION-NAME SYMBOL) (CLASS-NAME SYMBOL) (MODULES (LIST OF MODULE))))", ((cpp_function_code)(&modularInduceInferenceRules)), NULL);
    defineFunctionObject("BOTTOM-UP-RULE-INDUCTION", "(DEFUN BOTTOM-UP-RULE-INDUCTION ((EXAMPLES (LIST OF TRAINING-EXAMPLE)) (SIMPLIFY-RULE? BOOLEAN)) :COMMAND? TRUE)", ((cpp_function_code)(&bottomUpRuleInduction)), ((cpp_function_code)(&bottomUpRuleInductionEvaluatorWrapper)));
    defineFunctionObject("LEARN-ONE-RULE-BOTTOM-UP", "(DEFUN (LEARN-ONE-RULE-BOTTOM-UP (CONS OF CONS)) ((POSITIVE (LIST OF TRAINING-EXAMPLE)) (NEGATIVE (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&learnOneRuleBottomUp)), NULL);
    defineFunctionObject("CONTAINS-OUTPUT-VARIABLE?", "(DEFUN (CONTAINS-OUTPUT-VARIABLE? BOOLEAN) ((CLAUSE CONS) (OUTPUT-VARIABLES (CONS OF SYMBOL))))", ((cpp_function_code)(&containsOutputVariableP)), NULL);
    defineFunctionObject("SIMPLIFY-ANTECEDENT", "(DEFUN (SIMPLIFY-ANTECEDENT (CONS OF CONS)) ((ANTECEDENT (CONS OF CONS)) (OUTPUT-VARIABLES (CONS OF SYMBOL)) (POSITIVE (LIST OF TRAINING-EXAMPLE)) (NEGATIVE (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&simplifyAntecedent)), NULL);
    defineFunctionObject("LEAST-GENERAL-GENERALIZATION", "(DEFUN (LEAST-GENERAL-GENERALIZATION CONS) ((CLAUSE1 (CONS OF CONS)) (CLAUSE2 (CONS OF CONS))))", ((cpp_function_code)(&leastGeneralGeneralization)), NULL);
    defineFunctionObject("GENERALIZE-INEQUALITY", "(DEFUN (GENERALIZE-INEQUALITY CONS) ((PROBE CONS) (MATCH CONS) (BINDINGS (LIST OF CONS))))", ((cpp_function_code)(&generalizeInequality)), NULL);
    defineFunctionObject("BOTH-NUMBERS?", "(DEFUN (BOTH-NUMBERS? BOOLEAN) ((T1 OBJECT) (T2 OBJECT)))", ((cpp_function_code)(&bothNumbersP)), NULL);
    defineFunctionObject("EITHER-NUMBERS?", "(DEFUN (EITHER-NUMBERS? BOOLEAN) ((T1 OBJECT) (T2 OBJECT)))", ((cpp_function_code)(&eitherNumbersP)), NULL);
    defineFunctionObject("REMOVE-REDUNDANT-CLAUSES", "(DEFUN (REMOVE-REDUNDANT-CLAUSES (CONS OF CONS)) ((CLAUSES (CONS OF CONS))))", ((cpp_function_code)(&removeRedundantClauses)), NULL);
    defineFunctionObject("LOOKUP-VARIABLE-IN-BINDINGS", "(DEFUN (LOOKUP-VARIABLE-IN-BINDINGS OBJECT) ((OBJ1 OBJECT) (OBJ2 OBJECT) (BINDINGS (LIST OF CONS))))", ((cpp_function_code)(&lookupVariableInBindings)), NULL);
    defineFunctionObject("LEARN-ONE-RULE-BOTTOM-UP-FROM-SIGNATURES", "(DEFUN (LEARN-ONE-RULE-BOTTOM-UP-FROM-SIGNATURES (CONS OF CONS)) ((POSITIVE (LIST OF TRAINING-EXAMPLE)) (NEGATIVE (LIST OF TRAINING-EXAMPLE)) (COVERED (LIST OF TRAINING-EXAMPLE)) (CONS-PROPS (VECTOR OF CONS))))", ((cpp_function_code)(&learnOneRuleBottomUpFromSignatures)), NULL);
    defineFunctionObject("INTERSECT-SIGNATURES", "(DEFUN (INTERSECT-SIGNATURES (LIST OF INTEGER-WRAPPER)) ((SIG1 VECTOR) (SIG2 VECTOR)))", ((cpp_function_code)(&intersectSignatures)), NULL);
    defineFunctionObject("REMOVE-SIGNATURE-COVERED-EXAMPLES", "(DEFUN (REMOVE-SIGNATURE-COVERED-EXAMPLES (LIST OF TRAINING-EXAMPLE)) ((INDICES (LIST OF INTEGER-WRAPPER)) (EXAMPLES (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&removeSignatureCoveredExamples)), NULL);
    defineFunctionObject("NUM-SIGNATURE-INDICES-COVERED", "(DEFUN (NUM-SIGNATURE-INDICES-COVERED INTEGER) ((INDICES (LIST OF INTEGER-WRAPPER)) (EXAMPLES (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&numSignatureIndicesCovered)), NULL);
    defineFunctionObject("SIGNATURE-INDICES-COVER-ANY-EXAMPLE?", "(DEFUN (SIGNATURE-INDICES-COVER-ANY-EXAMPLE? BOOLEAN) ((INDICES (LIST OF INTEGER-WRAPPER)) (EXAMPLES (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&signatureIndicesCoverAnyExampleP)), NULL);
    defineFunctionObject("SIGNATURE-INDICES-COVER-EXAMPLE?", "(DEFUN (SIGNATURE-INDICES-COVER-EXAMPLE? BOOLEAN) ((INDICES (LIST OF INTEGER-WRAPPER)) (EXAMPLE TRAINING-EXAMPLE)))", ((cpp_function_code)(&signatureIndicesCoverExampleP)), NULL);
    defineFunctionObject("TOP-DOWN-RULE-INDUCTION", "(DEFUN TOP-DOWN-RULE-INDUCTION ((EXAMPLES (LIST OF TRAINING-EXAMPLE))) :COMMAND? TRUE)", ((cpp_function_code)(&topDownRuleInduction)), NULL);
    defineFunctionObject("BUILD-ANTECEDENT-FROM-RULE-INDEX", "(DEFUN (BUILD-ANTECEDENT-FROM-RULE-INDEX (CONS OF CONS)) ((PROPS (VECTOR OF CONS)) (RULE-INDEX (LIST OF INTEGER-WRAPPER))))", ((cpp_function_code)(&buildAntecedentFromRuleIndex)), NULL);
    defineFunctionObject("LEARN-ONE-RULE-TOP-DOWN-FROM-SIGNATURES", "(DEFUN (LEARN-ONE-RULE-TOP-DOWN-FROM-SIGNATURES (CONS OF CONS)) ((POSITIVE (LIST OF TRAINING-EXAMPLE)) (NEGATIVE (LIST OF TRAINING-EXAMPLE)) (COVERED_POS (LIST OF TRAINING-EXAMPLE)) (CONS-PROPS (VECTOR OF CONS))))", ((cpp_function_code)(&learnOneRuleTopDownFromSignatures)), NULL);
    defineFunctionObject("UPDATE-EXAMPLE-MATCHES", "(DEFUN UPDATE-EXAMPLE-MATCHES ((EXAMPLES (LIST OF TRAINING-EXAMPLE)) (INDEX INTEGER) (MATCH-VALUE INTEGER-WRAPPER)))", ((cpp_function_code)(&updateExampleMatches)), NULL);
    defineFunctionObject("UPDATE-COVERED-EXAMPLES", "(DEFUN UPDATE-COVERED-EXAMPLES ((FEATURE_INDEX INTEGER) (COVERED_POS (LIST OF TRAINING-EXAMPLE)) (COVERED_NEG (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&updateCoveredExamples)), NULL);
    defineFunctionObject("COUNT-EXAMPLE-MATCHES", "(DEFUN (COUNT-EXAMPLE-MATCHES INTEGER) ((EXAMPLES (LIST OF TRAINING-EXAMPLE)) (INDEX INTEGER) (MATCH-VALUE INTEGER-WRAPPER)))", ((cpp_function_code)(&countExampleMatches)), NULL);
    defineFunctionObject("FOIL-GAIN", "(DEFUN (FOIL-GAIN FLOAT) ((FEATURE-INDEX INTEGER) (UTILITY FLOAT) (COVERED-POS (LIST OF TRAINING-EXAMPLE)) (COVERED-NEG (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&foilGain)), NULL);
    defineFunctionObject("FOIL-UTILITY", "(DEFUN (FOIL-UTILITY FLOAT) ((P INTEGER) (N INTEGER)))", ((cpp_function_code)(&foilUtility)), NULL);
    defineFunctionObject("LEARN-ONE-RULE-TOP-DOWN", "(DEFUN (LEARN-ONE-RULE-TOP-DOWN (CONS OF CONS)) ((PROPOSITIONS (VECTOR OF CONS)) (POSITIVE (LIST OF TRAINING-EXAMPLE)) (NEGATIVE (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&learnOneRuleTopDown)), NULL);
    defineFunctionObject("SPECIALIZE-RULE", "(DEFUN (SPECIALIZE-RULE (CONS OF CONS)) ((RULE (CONS OF CONS)) (PROPOSITIONS (VECTOR OF CONS)) (POSITIVE (LIST OF TRAINING-EXAMPLE)) (NEGATIVE (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&specializeRule)), NULL);
    defineFunctionObject("REMOVE-EXCLUDED-EXAMPLES", "(DEFUN REMOVE-EXCLUDED-EXAMPLES ((RULE (CONS OF CONS)) (COVERED-POS (LIST OF TRAINING-EXAMPLE)) (COVERED-NEG (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&removeExcludedExamples)), NULL);
    defineFunctionObject("QUERY-FOIL-GAIN", "(DEFUN (QUERY-FOIL-GAIN FLOAT) ((RULE (CONS OF CONS)) (UTILITY FLOAT) (COVERED-POS (LIST OF TRAINING-EXAMPLE)) (COVERED-NEG (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&queryFoilGain)), NULL);
    defineFunctionObject("QUERY-AND-UPDATE-COVERED-EXAMPLES", "(DEFUN QUERY-AND-UPDATE-COVERED-EXAMPLES ((RULE (CONS OF CONS)) (UNCOVERED (LIST OF TRAINING-EXAMPLE)) (COVERED (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&queryAndUpdateCoveredExamples)), NULL);
    defineFunctionObject("REMOVE-COVERED-EXAMPLES", "(DEFUN REMOVE-COVERED-EXAMPLES ((RULE (CONS OF CONS)) (UNCOVERED (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&removeCoveredExamples)), NULL);
    defineFunctionObject("NUM-EXAMPLES-COVERED", "(DEFUN (NUM-EXAMPLES-COVERED INTEGER) ((RULE (CONS OF CONS)) (EXAMPLES (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&numExamplesCovered)), NULL);
    defineFunctionObject("GET-COVERED-EXAMPLES", "(DEFUN (GET-COVERED-EXAMPLES (LIST OF TRAINING-EXAMPLE)) ((RULE (CONS OF CONS)) (UNCOVERED (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&getCoveredExamples)), NULL);
    defineFunctionObject("RULE-COVERS-ANY-EXAMPLE?", "(DEFUN (RULE-COVERS-ANY-EXAMPLE? BOOLEAN) ((RULE (CONS OF CONS)) (EXAMPLES (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&ruleCoversAnyExampleP)), NULL);
    defineFunctionObject("RULE-COVERS-EXAMPLE?", "(DEFUN (RULE-COVERS-EXAMPLE? BOOLEAN) ((REVERSE-RULE (CONS OF CONS)) (EXAMPLE TRAINING-EXAMPLE)))", ((cpp_function_code)(&ruleCoversExampleP)), NULL);
    defineFunctionObject("LINK-VARIABLES-IN-INDUCED-RULE", "(DEFUN (LINK-VARIABLES-IN-INDUCED-RULE (LIST OF (CONS OF CONS))) ((RULE (CONS OF CONS)) (EXAMPLES (LIST OF TRAINING-EXAMPLE)) (CONS-PROPS (VECTOR OF CONS))))", ((cpp_function_code)(&linkVariablesInInducedRule)), NULL);
    defineFunctionObject("EVALUATE-RULE-INDUCTION", "(DEFUN (EVALUATE-RULE-INDUCTION (VECTOR OF FLOAT-WRAPPER)) ((RELATION-NAME SYMBOL) (CLASS-NAME SYMBOL) (NUM-TRIALS INTEGER) (CURVE-SPLITS INTEGER)) :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&evaluateRuleInduction)), ((cpp_function_code)(&evaluateRuleInductionEvaluatorWrapper)));
    defineFunctionObject("TRAIN-AND-TEST-RULE-INDUCTION", "(DEFUN (TRAIN-AND-TEST-RULE-INDUCTION FLOAT) ((TRAIN-SET (LIST OF TRAINING-EXAMPLE)) (TEST-SET (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&trainAndTestRuleInduction)), NULL);
    defineFunctionObject("INDUCE-DECISION-RULES", "(DEFUN INDUCE-DECISION-RULES ((RELATION-NAME SYMBOL) (CLASS-NAME SYMBOL)) :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&induceDecisionRules)), NULL);
    defineFunctionObject("MODULAR-INDUCE-DECISION-RULES", "(DEFUN MODULAR-INDUCE-DECISION-RULES ((RELATION-NAME SYMBOL) (CLASS-NAME SYMBOL) (MODULES (LIST OF MODULE))))", ((cpp_function_code)(&modularInduceDecisionRules)), NULL);
    defineFunctionObject("ASK-DECISION-TREE", "(DEFUN (ASK-DECISION-TREE BOOLEAN) ((TREE DECISION-TREE) (QUERY CONS)))", ((cpp_function_code)(&askDecisionTree)), NULL);
    defineFunctionObject("TRAVERSE-DECISION-TREE", "(DEFUN (TRAVERSE-DECISION-TREE BOOLEAN) ((TREE DECISION-TREE) (FEATURES (VECTOR OF INTEGER-WRAPPER))))", ((cpp_function_code)(&traverseDecisionTree)), NULL);
    defineFunctionObject("INDUCE-DECISION-TREE", "(DEFUN (INDUCE-DECISION-TREE DECISION-TREE) ((EXAMPLES (LIST OF TRAINING-EXAMPLE))) :COMMAND? TRUE)", ((cpp_function_code)(&induceDecisionTree)), NULL);
    defineFunctionObject("ADD-PROPOSITIONS-TO-DECISION-TREE", "(DEFUN ADD-PROPOSITIONS-TO-DECISION-TREE ((TREE DECISION-TREE) (TABLE (HASH-TABLE OF SYMBOL PROPOSITION))))", ((cpp_function_code)(&addPropositionsToDecisionTree)), NULL);
    defineFunctionObject("BUILD-DECISION-TREE", "(DEFUN (BUILD-DECISION-TREE OBJECT) ((EXAMPLES (LIST OF TRAINING-EXAMPLE)) (FEATURES (LIST OF SYMBOL)) (FEATURE-STACK (CONS OF SYMBOL))))", ((cpp_function_code)(&buildDecisionTree)), NULL);
    defineFunctionObject("EXPECTED-ENTROPY", "(DEFUN (EXPECTED-ENTROPY FLOAT) ((FEATURE-INDEX INTEGER) (EXAMPLES (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&expectedEntropy)), NULL);
    defineFunctionObject("ENTROPY", "(DEFUN (ENTROPY FLOAT) ((P INTEGER) (N INTEGER)))", ((cpp_function_code)(&entropy)), NULL);
    defineFunctionObject("PRINT-DECISION-TREE", "(DEFUN PRINT-DECISION-TREE ((TREE DECISION-TREE) (STREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&printDecisionTree)), NULL);
    defineFunctionObject("HELP-PRINT-DECISION-TREE", "(DEFUN HELP-PRINT-DECISION-TREE ((TREE DECISION-TREE) (LEVEL INTEGER) (STREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&helpPrintDecisionTree)), NULL);
    defineFunctionObject("GET-RULES-FROM-TREE", "(DEFUN (GET-RULES-FROM-TREE (LIST OF CONS)) ((QUERY CONS) (TREE DECISION-TREE)))", ((cpp_function_code)(&getRulesFromTree)), NULL);
    defineFunctionObject("BUILD-RULES-FROM-TREE", "(DEFUN (BUILD-RULES-FROM-TREE (LIST OF CONS)) ((TREE DECISION-TREE) (PROPS (LIST OF PROPOSITION))))", ((cpp_function_code)(&buildRulesFromTree)), NULL);
    defineFunctionObject("EXTRACT-PATHS-FROM-TREE", "(DEFUN EXTRACT-PATHS-FROM-TREE ((TREE DECISION-TREE) (ANTECEDENT-STACK (CONS OF CONS)) (ANTECEDENT (LIST OF CONS))))", ((cpp_function_code)(&extractPathsFromTree)), NULL);
    defineFunctionObject("SORT-EXAMPLES-BY-TREE", "(DEFUN SORT-EXAMPLES-BY-TREE ((TREE DECISION-TREE) (EXAMPLES (LIST OF TRAINING-EXAMPLE)) (SORTED-EXAMPLES (LIST OF (LIST OF TRAINING-EXAMPLE)))))", ((cpp_function_code)(&sortExamplesByTree)), NULL);
    defineFunctionObject("ASSERT-INDUCED-RULES", "(DEFUN ASSERT-INDUCED-RULES () :COMMAND? TRUE)", ((cpp_function_code)(&assertInducedRules)), NULL);
    defineFunctionObject("SET-CANDIDATE-CLAUSES", "(DEFUN SET-CANDIDATE-CLAUSES ((CLASS-NAME SYMBOL)))", ((cpp_function_code)(&setCandidateClauses)), NULL);
  }
}

void startupRuleInduction() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupRuleInduction1();
    }
    if (currentStartupTimePhaseP(4)) {
      oRULE_INDUCTION_STRATEGYo = KWD_RULE_INDUCTION_TOP_DOWN;
      oSIGNATURE_STRATEGYo = KWD_RULE_INDUCTION_TOP_DOWN;
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("DECISION-TREE", "(DEFCLASS DECISION-TREE (STANDARD-OBJECT) :SLOTS ((FEATURE :TYPE SYMBOL) (FEATURE-INDEX :TYPE INTEGER) (PROPOSITION :TYPE PROPOSITION) (TRUTH-VALUE :TYPE BOOLEAN) (CONCEPT :TYPE SYMBOL) (TRUE-BRANCH :TYPE DECISION-TREE) (FALSE-BRANCH :TYPE DECISION-TREE)) :PRINT-FORM (PRINT-DECISION-TREE SELF STREAM))");

        clasS->classConstructorCode = ((cpp_function_code)(&newDecisionTree));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessDecisionTreeSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupRuleInduction2();
      defineFunctionObject("GET-VARIABLES-FROM-PROPOSITION-LIST", "(DEFUN (GET-VARIABLES-FROM-PROPOSITION-LIST (LIST OF SYMBOL)) ((PROPS (LIST OF PROPOSITION))))", ((cpp_function_code)(&getVariablesFromPropositionList)), NULL);
      defineFunctionObject("GET-VARIABLES-FROM-CONS-PROPOSITIONS", "(DEFUN (GET-VARIABLES-FROM-CONS-PROPOSITIONS (LIST OF SYMBOL)) ((PROPS (CONS OF CONS))))", ((cpp_function_code)(&getVariablesFromConsPropositions)), NULL);
      defineFunctionObject("HELP-GET-VARIABLES-FROM-CONS-PROPOSITIONS", "(DEFUN (HELP-GET-VARIABLES-FROM-CONS-PROPOSITIONS (LIST OF SYMBOL)) ((ELE PARSE-TREE) (THE-LIST (LIST OF SYMBOL))))", ((cpp_function_code)(&helpGetVariablesFromConsPropositions)), NULL);
      defineFunctionObject("GET-PROPOSITIONS-FROM-DECISION-TREE", "(DEFUN (GET-PROPOSITIONS-FROM-DECISION-TREE (LIST OF PROPOSITION)) ((TREE DECISION-TREE)))", ((cpp_function_code)(&getPropositionsFromDecisionTree)), NULL);
      defineFunctionObject("STARTUP-RULE-INDUCTION", "(DEFUN STARTUP-RULE-INDUCTION () :PUBLIC? TRUE)", ((cpp_function_code)(&startupRuleInduction)), NULL);
      { MethodSlot* function = lookupFunction(SYM_RULE_INDUCTION_LOGIC_STARTUP_RULE_INDUCTION);

        setDynamicSlotValue(function->dynamicSlots, SYM_RULE_INDUCTION_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupRuleInduction"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFGLOBAL *RULE-INDUCTION-STRATEGY* KEYWORD :TOP-DOWN :DEMON-PROPERTY \"powerloom.learning.ruleInductionStrategy\" :PUBLIC? TRUE)", &oRULE_INDUCTION_STRATEGYo);
      defineGlobalVariableObject("(DEFGLOBAL *SIGNATURE-STRATEGY* KEYWORD :TOP-DOWN :DEMON-PROPERTY \"powerloom.learning.ruleInductionSignatureStrategy\" :PUBLIC? TRUE)", &oSIGNATURE_STRATEGYo);
      defineGlobalVariableObject("(DEFGLOBAL *ENABLE-USER-THING* BOOLEAN TRUE)", &oENABLE_USER_THINGo);
      defineGlobalVariableObject("(DEFGLOBAL *OPTIMIZE-INDUCED-QUERIES* BOOLEAN TRUE)", &oOPTIMIZE_INDUCED_QUERIESo);
      defineGlobalVariableObject("(DEFGLOBAL *SIMPLIFY-RULE-ANTECEDENT?* BOOLEAN FALSE :DOCUMENTATION \"Flag to control whether we try to simplify the rule antecedent.\nThis should be set to FALSE if we expect the user to edit the rule and\nTRUE if we want to have final rules as general as possible.\" :PUBLIC? TRUE)", &oSIMPLIFY_RULE_ANTECEDENTpo);
      defineGlobalVariableObject("(DEFGLOBAL *TRACE-ID3* BOOLEAN FALSE)", &oTRACE_ID3o);
      defineGlobalVariableObject("(DEFGLOBAL *TRACE-FOIL* BOOLEAN FALSE)", &oTRACE_FOILo);
      defineGlobalVariableObject("(DEFGLOBAL *INDUCE-RULES-FROM-SIGNATURES* BOOLEAN TRUE :DEMON-PROPERTY \"powerloom.learning.induceRulesFromSignatures\" :PUBLIC? TRUE)", &oINDUCE_RULES_FROM_SIGNATURESo);
      defineGlobalVariableObject("(DEFGLOBAL *NUM-LGGS* INTEGER 2000)", &oNUM_LGGSo);
      defineGlobalVariableObject("(DEFGLOBAL *ENFORCE-LINKED-VARIABLES* BOOLEAN FALSE)", &oENFORCE_LINKED_VARIABLESo);
      defineGlobalVariableObject("(DEFGLOBAL *LOG-INDUCED-RULES* BOOLEAN FALSE)", &oLOG_INDUCED_RULESo);
      defineGlobalVariableObject("(DEFGLOBAL *ALLOW-RECURSIVE-DECISION-NODES* BOOLEAN TRUE)", &oALLOW_RECURSIVE_DECISION_NODESo);
      defineGlobalVariableObject("(DEFGLOBAL *LOG-DECISION-RULE-CONSTRUCTION* BOOLEAN FALSE)", &oLOG_DECISION_RULE_CONSTRUCTIONo);
      defineGlobalVariableObject("(DEFGLOBAL LOG_2 FLOAT 0.6931472)", &LOG_2);
      defineGlobalVariableObject("(DEFGLOBAL *INDUCED-DECISION-RULES* (LIST OF CONS) NULL)", &oINDUCED_DECISION_RULESo);
      defineGlobalVariableObject("(DEFGLOBAL *INDUCED-RULE-COUNTER* INTEGER 0)", &oINDUCED_RULE_COUNTERo);
      defineGlobalVariableObject("(DEFGLOBAL *CANDIDATE-CLAUSES* (VECTOR OF CONS) NULL)", &oCANDIDATE_CLAUSESo);
      defineGlobalVariableObject("(DEFSPECIAL *BOTTOM-UP-VARIABLE-COUNTER* INTEGER -1)", &oBOTTOM_UP_VARIABLE_COUNTERo);
    }
  }
}

Keyword* KWD_RULE_INDUCTION_TOP_DOWN = NULL;

Surrogate* SGT_RULE_INDUCTION_LOGIC_DECISION_TREE = NULL;

Symbol* SYM_RULE_INDUCTION_LOGIC_FEATURE = NULL;

Symbol* SYM_RULE_INDUCTION_LOGIC_FEATURE_INDEX = NULL;

Symbol* SYM_RULE_INDUCTION_LOGIC_PROPOSITION = NULL;

Symbol* SYM_RULE_INDUCTION_LOGIC_TRUTH_VALUE = NULL;

Symbol* SYM_RULE_INDUCTION_LOGIC_CONCEPT = NULL;

Symbol* SYM_RULE_INDUCTION_LOGIC_TRUE_BRANCH = NULL;

Symbol* SYM_RULE_INDUCTION_LOGIC_FALSE_BRANCH = NULL;

Keyword* KWD_RULE_INDUCTION_BOTTOM_UP = NULL;

Symbol* SYM_RULE_INDUCTION_LOGIC_pY = NULL;

Symbol* SYM_RULE_INDUCTION_STELLA_eg = NULL;

Symbol* SYM_RULE_INDUCTION_STELLA_AND = NULL;

Surrogate* SGT_RULE_INDUCTION_STELLA_CONS = NULL;

Symbol* SYM_RULE_INDUCTION_STELLA_NOT = NULL;

Symbol* SYM_RULE_INDUCTION_STELLA_g = NULL;

Symbol* SYM_RULE_INDUCTION_STELLA_l = NULL;

Symbol* SYM_RULE_INDUCTION_STELLA_ge = NULL;

Symbol* SYM_RULE_INDUCTION_STELLA_el = NULL;

Surrogate* SGT_RULE_INDUCTION_STELLA_NUMBER_WRAPPER = NULL;

Symbol* SYM_RULE_INDUCTION_LOGIC_FAIL = NULL;

Keyword* KWD_RULE_INDUCTION_DECISION_TREE = NULL;

Symbol* SYM_RULE_INDUCTION_LOGIC_USER_THING = NULL;

Symbol* SYM_RULE_INDUCTION_STELLA_EXISTS = NULL;

Keyword* KWD_RULE_INDUCTION_TIMEOUT = NULL;

Keyword* KWD_RULE_INDUCTION_DONT_OPTIMIZEp = NULL;

Symbol* SYM_RULE_INDUCTION_STELLA_TRUE = NULL;

Symbol* SYM_RULE_INDUCTION_LOGIC_DEFRULE = NULL;

Symbol* SYM_RULE_INDUCTION_STELLA_FORALL = NULL;

Keyword* KWD_RULE_INDUCTION_OR = NULL;

Keyword* KWD_RULE_INDUCTION_NOT = NULL;

Keyword* KWD_RULE_INDUCTION_AND = NULL;

Surrogate* SGT_RULE_INDUCTION_LOGIC_PATTERN_VARIABLE = NULL;

Surrogate* SGT_RULE_INDUCTION_LOGIC_PROPOSITION = NULL;

Surrogate* SGT_RULE_INDUCTION_LOGIC_LOGIC_OBJECT = NULL;

Symbol* SYM_RULE_INDUCTION_LOGIC_STARTUP_RULE_INDUCTION = NULL;

Symbol* SYM_RULE_INDUCTION_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
