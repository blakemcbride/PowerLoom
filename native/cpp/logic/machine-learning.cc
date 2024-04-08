//  -*- Mode: C++ -*-

// machine-learning.cc

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

TrainingExample* newTrainingExample() {
  { TrainingExample* self = NULL;

    self = new TrainingExample();
    self->timestamp = NULL_INTEGER;
    self->cachedSolution = NULL;
    self->temp = NULL_FLOAT;
    self->output = NULL;
    self->nnHidden = NULL;
    self->facts = NULL;
    self->input = NULL;
    self->inputFeatures = NULL;
    self->module = NULL;
    self->score = NULL_FLOAT;
    self->name = NULL;
    self->concept = NULL;
    self->query = NULL;
    return (self);
  }
}

Surrogate* TrainingExample::primaryType() {
  { TrainingExample* self = this;

    return (SGT_MACHINE_LEARNING_LOGIC_TRAINING_EXAMPLE);
  }
}

Object* accessTrainingExampleSlotValue(TrainingExample* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_MACHINE_LEARNING_LOGIC_QUERY) {
    if (setvalueP) {
      self->query = ((Cons*)(value));
    }
    else {
      value = self->query;
    }
  }
  else if (slotname == SYM_MACHINE_LEARNING_LOGIC_CONCEPT) {
    if (setvalueP) {
      self->concept = ((Symbol*)(value));
    }
    else {
      value = self->concept;
    }
  }
  else if (slotname == SYM_MACHINE_LEARNING_STELLA_NAME) {
    if (setvalueP) {
      self->name = ((Symbol*)(value));
    }
    else {
      value = self->name;
    }
  }
  else if (slotname == SYM_MACHINE_LEARNING_LOGIC_SCORE) {
    if (setvalueP) {
      self->score = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->score);
    }
  }
  else if (slotname == SYM_MACHINE_LEARNING_STELLA_MODULE) {
    if (setvalueP) {
      self->module = ((Module*)(value));
    }
    else {
      value = self->module;
    }
  }
  else if (slotname == SYM_MACHINE_LEARNING_LOGIC_INPUT_FEATURES) {
    if (setvalueP) {
      self->inputFeatures = ((List*)(value));
    }
    else {
      value = self->inputFeatures;
    }
  }
  else if (slotname == SYM_MACHINE_LEARNING_LOGIC_INPUT) {
    if (setvalueP) {
      self->input = ((Vector*)(value));
    }
    else {
      value = self->input;
    }
  }
  else if (slotname == SYM_MACHINE_LEARNING_LOGIC_FACTS) {
    if (setvalueP) {
      self->facts = ((Cons*)(value));
    }
    else {
      value = self->facts;
    }
  }
  else if (slotname == SYM_MACHINE_LEARNING_LOGIC_NN_HIDDEN) {
    if (setvalueP) {
      self->nnHidden = ((Vector*)(value));
    }
    else {
      value = self->nnHidden;
    }
  }
  else if (slotname == SYM_MACHINE_LEARNING_LOGIC_OUTPUT) {
    if (setvalueP) {
      self->output = value;
    }
    else {
      value = self->output;
    }
  }
  else if (slotname == SYM_MACHINE_LEARNING_LOGIC_TEMP) {
    if (setvalueP) {
      self->temp = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->temp);
    }
  }
  else if (slotname == SYM_MACHINE_LEARNING_LOGIC_CACHED_SOLUTION) {
    if (setvalueP) {
      self->cachedSolution = value;
    }
    else {
      value = self->cachedSolution;
    }
  }
  else if (slotname == SYM_MACHINE_LEARNING_LOGIC_TIMESTAMP) {
    if (setvalueP) {
      self->timestamp = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->timestamp);
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

List* oTRAINING_EXAMPLESo = NULL;

List* oTESTING_EXAMPLESo = NULL;

boolean oCLOSED_WORLD_TRAINING_EXAMPLESo = true;

void setClosedWorldTrainingExamples(boolean b) {
  oCLOSED_WORLD_TRAINING_EXAMPLESo = b;
}

void setClosedWorldTrainingExamplesEvaluatorWrapper(Cons* arguments) {
  setClosedWorldTrainingExamples(((BooleanWrapper*)(arguments->value))->wrapperValue);
}

void printTrainingExample(TrainingExample* example) {
  std::cout << example->query << " in " << example->module << std::endl;
}

void addTrainingExample(Cons* form, double score) {
  // Add a query and score pair to the master list of 
  //   training examples
  { TrainingExample* example = newTrainingExample();

    example->query = copyConsList(form);
    example->score = score;
    oTRAINING_EXAMPLESo->push(example);
  }
}

void addTrainingExampleEvaluatorWrapper(Cons* arguments) {
  addTrainingExample(((Cons*)(arguments->value)), ((FloatWrapper*)(arguments->rest->value))->wrapperValue);
}

void addTrainingExampleInModule(Cons* form, double score, Symbol* module) {
  module = ((Symbol*)(module->permanentify()));
  { TrainingExample* example = newTrainingExample();

    example->query = copyConsList(form);
    example->score = score;
    example->module = getModule(module);
    oTRAINING_EXAMPLESo->push(example);
  }
}

void addTrainingExampleInModuleEvaluatorWrapper(Cons* arguments) {
  addTrainingExampleInModule(((Cons*)(arguments->value)), ((FloatWrapper*)(arguments->rest->value))->wrapperValue, ((Symbol*)(arguments->rest->rest->value)));
}

void addTestingExample(Cons* form, double score) {
  // Add a query and score pair to the master list of 
  //   testing examples
  { TrainingExample* example = newTrainingExample();

    example->query = copyConsList(form);
    example->score = score;
    oTESTING_EXAMPLESo->push(example);
  }
}

void addTestingExampleEvaluatorWrapper(Cons* arguments) {
  addTestingExample(((Cons*)(arguments->value)), ((FloatWrapper*)(arguments->rest->value))->wrapperValue);
}

void clearTrainingExamples() {
  oTRAINING_EXAMPLESo = newList();
}

void shuffleList(List* cards) {
  { int num = cards->length();
    double stop = num / 2.0;
    Object* temp = NULL;
    int i = 0;
    int one = 0;
    int two = 0;

    while (i < stop) {
      i = i + 1;
      one = stella::random(num);
      two = stella::random(num);
      temp = cards->nth(one);
      cards->nthSetter(cards->nth(two), one);
      cards->nthSetter(temp, two);
    }
  }
}

void shuffleVector(Vector* cards) {
  { int num = cards->length();
    double stop = num / 2.0;
    Object* temp = NULL;
    int i = 0;
    int one = 0;
    int two = 0;

    while (i < stop) {
      i = i + 1;
      one = stella::random(num);
      two = stella::random(num);
      temp = (cards->theArray)[one];
      (cards->theArray)[one] = ((cards->theArray)[two]);
      (cards->theArray)[two] = temp;
    }
  }
}

void saveTrainingExamples() {
  { OutputFileStream* nameFile = newOutputFileStream("training.names");
    OutputFileStream* dataFile = newOutputFileStream("training.data");

    createPropositionalTrainingExamples(oTRAINING_EXAMPLESo, nameFile, dataFile);
    nameFile->free();
    dataFile->free();
  }
}

int createPropositionalTrainingExamples(List* examples, OutputFileStream* nameFile, OutputFileStream* dataFile) {
  { int numInputs = 0;
    Module* home = oMODULEo;
    int temp = 0;
    Vector* input = NULL;

    { TrainingExample* example = NULL;
      Cons* iter000 = examples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (!(!((boolean)(example->module)))) {
          example->module->changeModule();
        }
        input = createInputSignature(example->query);
        example->input = input;
        home->changeModule();
        { IntegerWrapper* ele = NULL;
          Vector* vector000 = input;
          int index000 = 0;
          int length000 = vector000->length();

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            ele = ((IntegerWrapper*)((vector000->theArray)[index000]));
            temp = ele->wrapperValue;
            *(dataFile->nativeStream) << temp << ",";
          }
        }
        *(dataFile->nativeStream) << example->output << std::endl;
      }
    }
    numInputs = input->length();
    *(nameFile->nativeStream) << "true,false" << std::endl;
    { int i = NULL_INTEGER;
      int iter001 = 0;
      int upperBound000 = numInputs - 1;

      for  (; iter001 <= upperBound000; 
            iter001 = iter001 + 1) {
        i = iter001;
        *(nameFile->nativeStream) << "A" << stringify(wrapInteger(i)) << ":  1,0" << std::endl;
      }
    }
    return (numInputs);
  }
}

void fillInExampleOutputs(List* examples, Symbol* slotName) {
  { Surrogate* slot = getDescription(slotName)->surrogateValueInverse;
    Object* slotValue = NULL;
    LogicObject* instance = NULL;

    { TrainingExample* example = NULL;
      Cons* iter000 = examples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (((boolean)(example->module))) {
          example->module->changeModule();
        }
        instance = ((LogicObject*)(getInstance(example->query->rest->value)));
        slotValue = getSlotValue(instance, slot);
        example->output = slotValue;
      }
    }
  }
}

void detectNoiseInTrainingExamples(List* examples) {
  { Module* home = oMODULEo;
    int sigLength = 0;
    boolean same = true;

    { TrainingExample* example = NULL;
      Cons* iter000 = examples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (!((boolean)(example->input))) {
          if (!(!((boolean)(example->module)))) {
            example->module->changeModule();
          }
          example->input = createInputSignature(example->query);
          home->changeModule();
        }
      }
    }
    sigLength = ((TrainingExample*)(examples->first()))->input->length();
    { TrainingExample* example1 = NULL;
      Cons* iter001 = examples->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        example1 = ((TrainingExample*)(iter001->value));
        { TrainingExample* example2 = NULL;
          Cons* iter002 = examples->theConsList;

          for (; !(iter002 == NIL); iter002 = iter002->rest) {
            example2 = ((TrainingExample*)(iter002->value));
            same = true;
            { int k = NULL_INTEGER;
              int iter003 = 0;
              int upperBound000 = sigLength - 1;

              for  (; iter003 <= upperBound000; 
                    iter003 = iter003 + 1) {
                k = iter003;
                if (!eqlP((example1->input->theArray)[k], (example2->input->theArray)[k])) {
                  same = false;
                  break;
                }
              }
            }
            if (same &&
                (!eqlP(example1->output, example2->output))) {
              std::cout << example1->query->last() << " and " << example2->query->last() << " have the same input but different output" << std::endl;
            }
          }
        }
      }
    }
  }
}

List* getClassificationRelations(Cons* consQuery) {
  { Cons* options = listO(7, KWD_MACHINE_LEARNING_MATCH_MODE, KWD_MACHINE_LEARNING_BASIC, KWD_MACHINE_LEARNING_MAXIMIZE_SCOREp, SYM_MACHINE_LEARNING_STELLA_TRUE, KWD_MACHINE_LEARNING_MOVEOUT, wrapInteger(100000), NIL);
    QueryIterator* query = makeQuery(NIL, ((Cons*)(copyConsTree(consQuery))), NIL, options);
    List* result = newList();
    IncrementalPartialMatch* pmf = NULL;

    callAskPartial(query);
    pmf = ((IncrementalPartialMatch*)(query->baseControlFrame->partialMatchFrame->child->child));
    { Proposition* prop = NULL;
      Vector* vector000 = ((Vector*)(pmf->controlFrame->proposition->arguments));
      int index000 = 0;
      int length000 = vector000->length();
      Cons* collect000 = NULL;

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        prop = ((Proposition*)((vector000->theArray)[index000]));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(prop, NIL);
            if (result->theConsList == NIL) {
              result->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(result->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(prop, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (result);
  }
}

Vector* createInputSignature(Cons* consQuery) {
  { QueryIterator* query = makeQuery(NIL, ((Cons*)(copyConsTree(consQuery))), NIL, NIL);
    IncrementalPartialMatch* pmf = NULL;
    Cons* argScores = NIL;
    Vector* signature = NULL;

    oFAIL_UNBOUND_CLAUSESpo = true;
    query->options->insertAt(KWD_MACHINE_LEARNING_MATCH_MODE, KWD_MACHINE_LEARNING_BASIC);
    query->options->insertAt(KWD_MACHINE_LEARNING_MAXIMIZE_SCOREp, TRUE_WRAPPER);
    callAskPartial(query);
    pmf = ((IncrementalPartialMatch*)(query->baseControlFrame->partialMatchFrame->child->child));
    argScores = pmf->argumentScores;
    signature = stella::newVector(argScores->length());
    { Object* score = NULL;
      Cons* iter000 = argScores->reverse();
      int i = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        score = iter000->value;
        i = iter001;
        if (eqlP(score, wrapFloat(1.0))) {
          (signature->theArray)[i] = (wrapInteger(1));
        }
        else {
          (signature->theArray)[i] = (wrapInteger(0));
        }
      }
    }
    return (signature);
  }
}

void generateClassificationRule(Vector* instances, Symbol* conceptName, Symbol* className, boolean buildRuleP) {
  { int numInstances = instances->length();
    Surrogate* kind = getDescription(className)->surrogateValueInverse;
    Symbol* name = NULL;
    Proposition* prop = NULL;
    boolean functionValuesP = oDROP_FUNCTION_VALUESpo;

    oDROP_FUNCTION_VALUESpo = false;
    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = numInstances - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        name = objectName(((LogicObject*)((instances->theArray)[i])));
        prop = ((Proposition*)(conceiveFormula(consList(2, conceptName, name))));
        if (trueP(prop)) {
          helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_RETRACT_TRUE);
          buildCaseFromInstance(((LogicObject*)((instances->theArray)[i])), kind);
          helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_ASSERT_TRUE);
        }
        if (falseP(prop)) {
          helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_RETRACT_FALSE);
          buildCaseFromInstance(((LogicObject*)((instances->theArray)[i])), kind);
          helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_ASSERT_FALSE);
        }
      }
    }
    oDROP_FUNCTION_VALUESpo = functionValuesP;
    if (buildRuleP) {
      buildClassificationRule(conceptName, className);
    }
  }
}

void buildClassificationRule(Symbol* kind, Symbol* className) {
  { Symbol* ruleName = internSymbol(stringConcatenate(kind->symbolName, "-Classification-Rule", 0));
    Symbol* relationName = internSymbol(stringConcatenate(kind->symbolName, "-Classification", 0));
    const char* index = stringConcatenate(className->symbolName, "-match", 0);
    List* ruleAntecedent = ((List*)(oCASE_ANTECEDENT_TABLEo->lookup(index)));
    Cons* convertedAntecedent = NIL;
    List* ruleTypes = ((List*)(oCASE_TYPES_TABLEo->lookup(index)));
    Cons* convertedTypes = NIL;
    Cons* relation = listO(3, SYM_MACHINE_LEARNING_LOGIC_DEFRELATION, relationName, cons(cons(listO(3, SYM_MACHINE_LEARNING_LOGIC_pP, SYM_MACHINE_LEARNING_STELLA_THING, NIL), NIL), NIL));
    Cons* rule = NIL;

    { Cons* clause = NULL;
      Cons* iter000 = ruleAntecedent->theConsList;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest) {
        clause = ((Cons*)(iter000->value));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(clause, NIL);
            if (convertedAntecedent == NIL) {
              convertedAntecedent = collect000;
            }
            else {
              addConsToEndOfConsList(convertedAntecedent, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(clause, NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { Symbol* type = NULL;
      Cons* iter001 = ruleTypes->theConsList;
      Cons* collect001 = NULL;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest) {
        type = ((Symbol*)(iter001->value));
        if (!((boolean)(collect001))) {
          {
            collect001 = cons(type, NIL);
            if (convertedTypes == NIL) {
              convertedTypes = collect001;
            }
            else {
              addConsToEndOfConsList(convertedTypes, collect001);
            }
          }
        }
        else {
          {
            collect001->rest = cons(type, NIL);
            collect001 = collect001->rest;
          }
        }
      }
    }
    rule = ((Cons*)(copyConsTree(listO(3, SYM_MACHINE_LEARNING_LOGIC_DEFRULE, ruleName, cons(listO(3, SYM_MACHINE_LEARNING_STELLA_FORALL, convertedTypes, cons(listO(4, SYM_MACHINE_LEARNING_STELLA_eg, cons(SYM_MACHINE_LEARNING_STELLA_AND, convertedAntecedent->concatenate(NIL, 0)), cons(relationName, cons(SYM_MACHINE_LEARNING_LOGIC_pY, NIL)), NIL), NIL)), NIL)))));
    if (oLOG_MATCH_RULESo) {
      std::cout << rule << std::endl;
    }
    std::cout << "Building classification rule with " << convertedAntecedent->length() << " clauses and " << convertedTypes->length() << " variables" << std::endl;
    if (!ruleAntecedent->emptyP()) {
      evaluateLogicCommand(relation, false);
      evaluateLogicCommand(rule, false);
    }
  }
}

int oldGenerateClassificationTrainingExamples(Vector* instances, Surrogate* concept) {
  { int numInstances = instances->length();
    Cons* consQuery = NIL;
    boolean target = false;
    Symbol* conceptName = internSymbol(concept->symbolName);

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = numInstances - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        { TrainingExample* example = newTrainingExample();

          target = trueTruthValueP(callAsk(makeQuery(NIL, consList(2, conceptName, objectName(((LogicObject*)((instances->theArray)[i])))), NIL, NIL)));
          consQuery = consList(2, internSymbol(stringConcatenate(conceptName->symbolName, "-Classification", 0)), objectName(((LogicObject*)((instances->theArray)[i]))));
          example->query = consQuery;
          example->output = (target ? TRUE_WRAPPER : FALSE_WRAPPER);
          example->concept = conceptName;
          example->name = objectName(((LogicObject*)((instances->theArray)[i])));
          example->module = oMODULEo;
          example->input = createInputSignature(consQuery);
          example->timestamp = -1;
          oTRAINING_EXAMPLESo->push(example);
        }
      }
    }
    return (numInstances);
  }
}

void testDomainTheory(Symbol* relationName, Symbol* className) {
  { Surrogate* clasS = getDescription(className)->surrogateValueInverse;
    Proposition* prop = NULL;
    Cons* consQuery = NIL;
    QueryIterator* query = NULL;
    List* instances = allClassInstances(clasS)->listify();
    boolean correctP = true;
    int numCorrect = 0;

    { Object* instance = NULL;
      Cons* iter000 = instances->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        instance = iter000->value;
        consQuery = consList(2, relationName, objectName(instance));
        prop = ((Proposition*)(conceiveFormula(((Cons*)(copyConsTree(consQuery))))));
        correctP = true;
        if (trueP(prop)) {
          std::cout << consQuery << " is true" << std::endl;
          helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_RETRACT_TRUE);
          query = makeQuery(NIL, ((Cons*)(copyConsTree(listO(3, SYM_MACHINE_LEARNING_STELLA_NOT, consQuery, NIL)))), NIL, NIL);
          if (trueTruthValueP(callAsk(query))) {
            correctP = false;
            std::cout << "  **Theory disproves " << consQuery << " true" << std::endl;
          }
          query = makeQuery(NIL, ((Cons*)(copyConsTree(consQuery))), NIL, NIL);
          if (!trueTruthValueP(callAsk(query))) {
            correctP = false;
            std::cout << "  **Theory cannot prove " << consQuery << std::endl;
          }
          helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_ASSERT_TRUE);
        }
        if (falseP(prop)) {
          std::cout << consQuery << " is false" << std::endl;
          helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_RETRACT_FALSE);
          query = makeQuery(NIL, ((Cons*)(copyConsTree(consQuery))), NIL, NIL);
          if (trueTruthValueP(callAsk(query))) {
            correctP = false;
            std::cout << "  **Theory proves " << consQuery << "true" << std::endl;
          }
          query = makeQuery(NIL, ((Cons*)(copyConsTree(listO(3, SYM_MACHINE_LEARNING_STELLA_NOT, consQuery, NIL)))), NIL, NIL);
          if (!trueTruthValueP(callAsk(query))) {
            correctP = false;
            std::cout << "  **Theory cannot disprove " << consQuery << std::endl;
          }
          helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_ASSERT_FALSE);
        }
        if (correctP) {
          numCorrect = numCorrect + 1;
        }
      }
    }
    std::cout << std::endl << "Theory got " << numCorrect << " out of " << instances->length() << std::endl;
  }
}

double testTheoryOverExamples(List* examples) {
  { double correct = 0.0;
    QueryIterator* query = NULL;
    Cons* consQuery = NIL;
    Proposition* prop = NULL;

    { TrainingExample* example = NULL;
      Cons* iter000 = examples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        consQuery = ((Cons*)(copyConsTree(example->query)));
        prop = ((Proposition*)(conceiveFormula(((Cons*)(copyConsTree(consQuery))))));
        query = makeQuery(NIL, ((Cons*)(copyConsTree(example->query))), NIL, NIL);
        if (subtypeOfBooleanP(safePrimaryType(example->output))) {
          if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)(example->output)))) {
            {
              helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_RETRACT_TRUE);
              if (trueTruthValueP(callAsk(query))) {
                correct = correct + 1;
              }
              helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_ASSERT_TRUE);
            }
          }
          else {
            {
              helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_RETRACT_FALSE);
              if (!trueTruthValueP(callAsk(query))) {
                correct = correct + 1;
              }
              helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_ASSERT_FALSE);
            }
          }
        }
        else {
        }
      }
    }
    return (correct / examples->length());
  }
}

int generateTrainingExamples(Vector* instances, Surrogate* concept) {
  { int numInstances = instances->length();
    Cons* consQuery = NIL;
    int numExamples = 0;
    TrainingExample* example = NULL;
    Proposition* prop = NULL;
    QueryIterator* query = NULL;
    Symbol* conceptName = internSymbol(concept->symbolName);

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = numInstances - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        consQuery = consList(2, conceptName, objectName(((LogicObject*)((instances->theArray)[i]))));
        prop = ((Proposition*)(conceiveFormula(((Cons*)(copyConsTree(consQuery))))));
        example = NULL;
        if (trueP(prop)) {
          {
            helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_RETRACT_TRUE);
            query = makeQuery(NIL, ((Cons*)(copyConsTree(consQuery))), NIL, NIL);
            if (!trueTruthValueP(callAsk(query))) {
              example = newTrainingExample();
              example->query = consQuery;
              example->output = TRUE_WRAPPER;
              example->concept = conceptName;
              example->name = objectName(((LogicObject*)((instances->theArray)[i])));
              example->score = 1.0;
            }
            helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_ASSERT_TRUE);
          }
        }
        else {
          if (falseP(prop) ||
              oCLOSED_WORLD_TRAINING_EXAMPLESo) {
            {
              example = newTrainingExample();
              example->query = consQuery;
              example->output = FALSE_WRAPPER;
              example->concept = conceptName;
              example->name = objectName(((LogicObject*)((instances->theArray)[i])));
              example->score = 0.0;
            }
          }
        }
        if (!(!((boolean)(example)))) {
          example->module = oMODULEo;
          example->timestamp = -1;
          numExamples = numExamples + 1;
          oTRAINING_EXAMPLESo->push(example);
        }
      }
    }
    return (numExamples);
  }
}

int generateClassificationTrainingExamples(Vector* instances, Surrogate* concept, boolean createSignatureP) {
  { int numInstances = instances->length();
    Cons* consQuery = NIL;
    int numExamples = 0;
    TrainingExample* example = NULL;
    Proposition* prop = NULL;
    Cons* classificationQuery = NIL;
    QueryIterator* query = NULL;
    Symbol* conceptName = internSymbol(concept->symbolName);

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = numInstances - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        consQuery = consList(2, conceptName, objectName(((LogicObject*)((instances->theArray)[i]))));
        classificationQuery = consList(2, internSymbol(stringConcatenate(conceptName->symbolName, "-Classification", 0)), objectName(((LogicObject*)((instances->theArray)[i]))));
        prop = ((Proposition*)(conceiveFormula(((Cons*)(copyConsTree(consQuery))))));
        example = NULL;
        if (trueP(prop)) {
          {
            helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_RETRACT_TRUE);
            query = makeQuery(NIL, ((Cons*)(copyConsTree(consQuery))), NIL, NIL);
            if (!trueTruthValueP(callAsk(query))) {
              example = newTrainingExample();
              example->query = classificationQuery;
              example->output = TRUE_WRAPPER;
              example->concept = conceptName;
              example->name = objectName(((LogicObject*)((instances->theArray)[i])));
              example->score = 1.0;
            }
            helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_ASSERT_TRUE);
          }
        }
        else {
          if (falseP(prop) ||
              oCLOSED_WORLD_TRAINING_EXAMPLESo) {
            {
              example = newTrainingExample();
              example->query = classificationQuery;
              example->output = FALSE_WRAPPER;
              example->concept = conceptName;
              example->name = objectName(((LogicObject*)((instances->theArray)[i])));
              example->score = 0.0;
            }
          }
        }
        if (!(!((boolean)(example)))) {
          if (createSignatureP) {
            example->input = createInputSignature(classificationQuery);
          }
          example->module = oMODULEo;
          example->timestamp = -1;
          numExamples = numExamples + 1;
          oTRAINING_EXAMPLESo->push(example);
        }
      }
    }
    return (numExamples);
  }
}

void generateRegressionRuleWoSlot(Vector* cases, Symbol* slotName, Symbol* className, boolean reallyBuildRule) {
  { int numCases = cases->length();
    Surrogate* kind = getDescription(className)->surrogateValueInverse;
    List* caseNames = newList();
    Surrogate* slot = getDescription(slotName)->surrogateValueInverse;
    Vector* slotValues = stella::newVector(numCases);
    boolean functionValuesP = oDROP_FUNCTION_VALUESpo;

    oDROP_FUNCTION_VALUESpo = false;
    { LogicObject* casE = NULL;
      Vector* vector000 = cases;
      int index000 = 0;
      int length000 = vector000->length();
      Cons* collect000 = NULL;

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        casE = ((LogicObject*)((vector000->theArray)[index000]));
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(objectName(casE), NIL);
            if (caseNames->theConsList == NIL) {
              caseNames->theConsList = collect000;
            }
            else {
              addConsToEndOfConsList(caseNames->theConsList, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(objectName(casE), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    { LogicObject* casE = NULL;
      Vector* vector001 = cases;
      int index001 = 0;
      int length001 = vector001->length();
      Symbol* caseName = NULL;
      Cons* iter000 = caseNames->theConsList;
      int i = NULL_INTEGER;
      int iter001 = 0;

      for  (; (index001 < length001) &&
                (!(iter000 == NIL)); 
            index001 = index001 + 1,
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        casE = ((LogicObject*)((vector001->theArray)[index001]));
        caseName = ((Symbol*)(iter000->value));
        i = iter001;
        { Object* val = getSlotValue(casE, slot);

          (slotValues->theArray)[i] = val;
          if (!(!((boolean)(val)))) {
            smartUpdateProposition(cons(slotName, cons(caseName, cons(val, NIL))), KWD_MACHINE_LEARNING_RETRACT_TRUE);
          }
        }
      }
    }
    { int i = NULL_INTEGER;
      int iter002 = 0;
      int upperBound000 = numCases - 1;

      for  (; iter002 <= upperBound000; 
            iter002 = iter002 + 1) {
        i = iter002;
        if (!(!((boolean)((slotValues->theArray)[i])))) {
          buildCaseFromInstance(((LogicObject*)((cases->theArray)[i])), kind);
        }
      }
    }
    if (reallyBuildRule) {
      buildClassificationRule(slotName, className);
    }
    oDROP_FUNCTION_VALUESpo = functionValuesP;
    { Object* val = NULL;
      Vector* vector002 = slotValues;
      int index002 = 0;
      int length002 = vector002->length();
      Symbol* caseName = NULL;
      Cons* iter003 = caseNames->theConsList;

      for  (; (index002 < length002) &&
                (!(iter003 == NIL)); 
            index002 = index002 + 1,
            iter003 = iter003->rest) {
        val = (vector002->theArray)[index002];
        caseName = ((Symbol*)(iter003->value));
        if (!(!((boolean)(val)))) {
          smartUpdateProposition(cons(slotName, cons(caseName, cons(val, NIL))), KWD_MACHINE_LEARNING_ASSERT_TRUE);
        }
      }
    }
  }
}

int generateRegressionTrainingExamples(Vector* instances, Surrogate* slot) {
  { int numInstances = instances->length();
    Symbol* predName = internSymbol(stringConcatenate(slot->symbolName, "-Classification", 0));
    Vector* slotValues = stella::newVector(numInstances);

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = numInstances - 1;
      LogicObject* inst = NULL;
      Vector* vector000 = instances;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; (iter000 <= upperBound000) &&
                (index000 < length000); 
            iter000 = iter000 + 1,
            index000 = index000 + 1) {
        i = iter000;
        inst = ((LogicObject*)((vector000->theArray)[index000]));
        (slotValues->theArray)[i] = (((FloatWrapper*)(getSlotValue(inst, slot))));
      }
    }
    normalizeNumbers(slotValues);
    { int i = NULL_INTEGER;
      int iter001 = 0;
      int upperBound001 = numInstances - 1;

      for  (; iter001 <= upperBound001; 
            iter001 = iter001 + 1) {
        i = iter001;
        if (!(!((boolean)(((FloatWrapper*)((slotValues->theArray)[i])))))) {
          { TrainingExample* example = newTrainingExample();

            example->query = cons(predName, cons(logicSymbol(((LogicObject*)((instances->theArray)[i]))), NIL));
            example->concept = internSymbol(slot->symbolName);
            example->name = objectName(((LogicObject*)((instances->theArray)[i])));
            example->score = ((FloatWrapper*)((slotValues->theArray)[i]))->wrapperValue;
            example->timestamp = -1;
            oTRAINING_EXAMPLESo->push(example);
          }
        }
      }
    }
    return (numInstances);
  }
}

double approximate(Symbol* instName, Symbol* slotName) {
  instName = ((Symbol*)(instName->permanentify()));
  slotName = ((Symbol*)(slotName->permanentify()));
  { Surrogate* slot = getDescription(slotName)->surrogateValueInverse;

    if (floatFunctionP(slot)) {
      return (generateSlotApproximation(instName, slot));
    }
    else {
      {
        *(STANDARD_ERROR->nativeStream) << "ERROR " << slotName << " is not a function of type float or integer" << std::endl;
        return (0.0);
      }
    }
  }
}

FloatWrapper* approximateEvaluatorWrapper(Cons* arguments) {
  { double result = approximate(((Symbol*)(arguments->value)), ((Symbol*)(arguments->rest->value)));

    if (result != NULL_FLOAT) {
      return (wrapFloat(result));
    }
    else {
      return (NULL);
    }
  }
}

double generateSlotApproximation(Symbol* instName, Surrogate* slot) {
  { Object* probe = getInstance(instName);
    Surrogate* clasS = ((LogicObject*)(getMostSpecificClasses(((LogicObject*)(probe)))->last()))->surrogateValueInverse;
    Symbol* ruleName = internSymbol(stringConcatenate(slot->symbolName, "-Classification", 0));
    List* instances = allClassInstances(clasS)->listify();
    double max = 0.0;
    double score = 0.0;
    double min = 999999.0;
    double range = 0.0;
    Cons* prop = cons(ruleName, cons(instName, NIL));

    { Object* instance = NULL;
      Cons* iter000 = instances->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        instance = iter000->value;
        { Object* value = getSlotValue(((LogicObject*)(instance)), slot);

          if (!(!((boolean)(value)))) {
            { double flValue = ((FloatWrapper*)(value))->wrapperValue;

              if (flValue > max) {
                max = ((FloatWrapper*)(value))->wrapperValue;
              }
              if (flValue < min) {
                min = flValue;
              }
            }
          }
        }
      }
    }
    range = max - min;
    score = returnPartialTruth(makeQuery(NIL, coerceToTree(prop), NIL, NIL), true);
    return ((score * range) + min);
  }
}

boolean floatFunctionP(Surrogate* relation) {
  { NamedDescription* des = ((NamedDescription*)(relation->surrogateValue));

    if (functionDescriptionP(des) &&
        (((Surrogate*)(des->ioVariableTypes->last())) == SGT_MACHINE_LEARNING_STELLA_FLOAT)) {
      return (true);
    }
    else {
      return (false);
    }
  }
}

int oMAX_STRUCTURE_DEPTHo = 3;

boolean oDROP_FUNCTION_VALUESpo = true;

void setStructureDepth(int d) {
  oMAX_STRUCTURE_DEPTHo = d;
}

void setStructureDepthEvaluatorWrapper(Cons* arguments) {
  setStructureDepth(((IntegerWrapper*)(arguments->value))->wrapperValue);
}

List* oTABOO_OPERATORSo = NULL;

void addTabooOperators(Symbol* s) {
  oTABOO_OPERATORSo->insertNew(s->surrogatify());
}

List* getAssertionStructure(Symbol* inst, int depth) {
  oVISITED_PROPOSITIONSo = newList();
  oVISITED_INSTANCESo = newList();
  return (helpGetAssertionStructure(inst, depth));
}

List* helpGetAssertionStructure(Symbol* inst, int depth) {
  oVISITED_INSTANCESo->push(inst);
  { Module* home = ((Module*)(inst->homeContext));
    List* facts = newList();
    List* antecedent = newList();
    List* children = NULL;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, home);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      facts = allFactsOfInstance(getInstance(inst), false, false);
    }
    { Proposition* fact = NULL;
      Cons* iter000 = facts->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        fact = ((Proposition*)(iter000->value));
        if ((!oVISITED_PROPOSITIONSo->memberP(fact)) &&
            ((!((boolean)(oTABOO_OPERATORSo))) ||
             (!oTABOO_OPERATORSo->memberP(fact->operatoR)))) {
          oVISITED_PROPOSITIONSo->push(fact);
          { Cons* consProp = propositionToCons(fact);
            Cons* consProps = NIL;

            if (fact->kind == KWD_MACHINE_LEARNING_ISA) {
              consProps = cons(consProp, consProps);
            }
            else if (depth < oMAX_STRUCTURE_DEPTHo) {
              if (fact->kind == KWD_MACHINE_LEARNING_FUNCTION) {
                consProps = cons(consProp, consProps);
                if (isaP(consProp->last(), SGT_MACHINE_LEARNING_STELLA_NUMBER_WRAPPER)) {
                  { Cons* skolemName = ((Cons*)(copyConsTree(consProp)))->reverse()->rest->reverse();
                    Object* skolemValue = consProp->last();

                    consProps = cons(listO(3, SYM_MACHINE_LEARNING_STELLA_ge, ((Cons*)(copyConsTree(skolemName))), cons(skolemValue, NIL)), consProps);
                    consProps = cons(listO(3, SYM_MACHINE_LEARNING_STELLA_el, ((Cons*)(copyConsTree(skolemName))), cons(skolemValue, NIL)), consProps);
                  }
                }
              }
              else {
                if (!((consProp->value == SYM_MACHINE_LEARNING_STELLA_e) &&
                    eqlP(consProp->rest->value, consProp->rest->rest->value))) {
                  consProps = cons(consProp, consProps);
                }
              }
            }
            else {
            }
            if (!(consProps == NIL)) {
              { Cons* prop = NULL;
                Cons* iter001 = consProps;

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  prop = ((Cons*)(iter001->value));
                  antecedent->push(prop);
                }
              }
              { Object* ele = NULL;
                Cons* iter002 = consProp->rest;

                for (; !(iter002 == NIL); iter002 = iter002->rest) {
                  ele = iter002->value;
                  if (isaP(ele, SGT_MACHINE_LEARNING_STELLA_SYMBOL) &&
                      ((!oVISITED_INSTANCESo->memberP(ele)) &&
                       (depth < oMAX_STRUCTURE_DEPTHo))) {
                    if (!((boolean)(children))) {
                      children = helpGetAssertionStructure(((Symbol*)(ele)), depth + 1);
                    }
                    else {
                      children = helpGetAssertionStructure(((Symbol*)(ele)), depth + 1)->concatenate(children, 0);
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    if (!((boolean)(children))) {
      return (antecedent);
    }
    else {
      return (antecedent->concatenate(children, 0));
    }
  }
}

void collectFactsInExamples(List* examples) {
  { Proposition* prop = NULL;

    { TrainingExample* example = NULL;
      Cons* iter000 = examples->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (((boolean)(example->module))) {
          example->module->changeModule();
        }
        prop = ((Proposition*)(conceiveFormula(example->query)));
        if (trueP(prop)) {
          helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_RETRACT_TRUE);
          example->facts = getAssertionStructure(example->name, 1)->consify();
          helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_ASSERT_TRUE);
        }
        if (falseP(prop)) {
          helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_RETRACT_FALSE);
          example->facts = getAssertionStructure(example->name, 1)->consify();
          helpUpdateTopLevelProposition(prop, KWD_MACHINE_LEARNING_ASSERT_FALSE);
        }
      }
    }
  }
}

Cons* oldRecursiveBuildAntecedent(Symbol* inst, int depth) {
  oVISITED_INSTANCESo->push(inst);
  { Module* home = ((Module*)(inst->homeContext));
    List* facts = newList();
    Cons* antecedent = NIL;
    Cons* children = NIL;

    { 
      BIND_STELLA_SPECIAL(oMODULEo, Module*, home);
      BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
      facts = allFactsOfInstance(getInstance(inst), false, false);
    }
    { Proposition* fact = NULL;
      Cons* iter000 = facts->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        fact = ((Proposition*)(iter000->value));
        if ((!oVISITED_PROPOSITIONSo->memberP(fact)) &&
            (!oTABOO_OPERATORSo->memberP(fact->operatoR))) {
          oVISITED_PROPOSITIONSo->push(fact);
          { Cons* consProp = propositionToCons(fact);

            { Keyword* testValue000 = fact->kind;

              if (testValue000 == KWD_MACHINE_LEARNING_FUNCTION) {
                if (oDROP_FUNCTION_VALUESpo) {
                  consProp = listO(3, SYM_MACHINE_LEARNING_STELLA_e, consProp->reverse()->rest->reverse(), NIL);
                }
                else {
                  consProp = listO(3, SYM_MACHINE_LEARNING_STELLA_AND, consProp, NIL);
                }
              }
              else if (testValue000 == KWD_MACHINE_LEARNING_ISA) {
                consProp = listO(3, SYM_MACHINE_LEARNING_STELLA_AND, consProp, NIL);
              }
              else {
                if (depth < oMAX_STRUCTURE_DEPTHo) {
                  consProp = listO(3, SYM_MACHINE_LEARNING_STELLA_AND, consProp, NIL);
                }
                else {
                  consProp = NIL;
                }
              }
            }
            if (!(consProp == NIL)) {
              antecedent = cons(consProp, antecedent);
              { Object* ele = NULL;
                Cons* iter001 = ((Cons*)(consProp->rest->value))->rest;

                for (; !(iter001 == NIL); iter001 = iter001->rest) {
                  ele = iter001->value;
                  if (isaP(ele, SGT_MACHINE_LEARNING_STELLA_SYMBOL) &&
                      ((!oVISITED_INSTANCESo->memberP(ele)) &&
                       (depth < oMAX_STRUCTURE_DEPTHo))) {
                    children = oldRecursiveBuildAntecedent(((Symbol*)(ele)), depth + 1)->concatenate(children, 0);
                  }
                }
              }
            }
          }
        }
      }
    }
    if (children == NIL) {
      return (antecedent);
    }
    else {
      return (antecedent->concatenate(children, 0));
    }
  }
}

Object* getArgumentBinding(Object* arg) {
  { Object* bind = argumentBoundTo(arg);

    if (!((boolean)(bind))) {
      return (internSymbol(getSkolemPrintName(((Skolem*)(arg)))));
    }
    else {
      { Surrogate* testValue000 = safePrimaryType(bind);

        if (subtypeOfP(testValue000, SGT_MACHINE_LEARNING_LOGIC_DESCRIPTION)) {
          { Object* bind000 = bind;
            Description* bind = ((Description*)(bind000));

            return (bind->nativeRelation());
          }
        }
        else if (subtypeOfP(testValue000, SGT_MACHINE_LEARNING_LOGIC_SKOLEM)) {
          { Object* bind001 = bind;
            Skolem* bind = ((Skolem*)(bind001));

            if (((boolean)(bind->definingProposition))) {
              return (propositionToCons(bind->definingProposition));
            }
            else if (stringEqlP(getSkolemPrintName(bind), "ANONYMOUS")) {
              return (internSymbol(getSkolemPrintName(((Skolem*)(arg)))));
            }
            else {
              return (bind);
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_MACHINE_LEARNING_LOGIC_LOGIC_OBJECT)) {
          { Object* bind002 = bind;
            LogicObject* bind = ((LogicObject*)(bind002));

            return (internSymbol(bind->surrogateValueInverse->symbolName));
          }
        }
        else {
          return (bind);
        }
      }
    }
  }
}

Object* consifyArgument(Object* arg) {
  { Surrogate* testValue000 = safePrimaryType(arg);

    if (subtypeOfP(testValue000, SGT_MACHINE_LEARNING_LOGIC_PROPOSITION)) {
      { Object* arg000 = arg;
        Proposition* arg = ((Proposition*)(arg000));

        return (propositionToCons(arg));
      }
    }
    else if (subtypeOfP(testValue000, SGT_MACHINE_LEARNING_LOGIC_PATTERN_VARIABLE)) {
      { Object* arg001 = arg;
        PatternVariable* arg = ((PatternVariable*)(arg001));

        if (!((boolean)(oQUERYITERATORo))) {
          return (internSymbol(getSkolemPrintName(arg)));
        }
        else {
          return (getArgumentBinding(arg));
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_MACHINE_LEARNING_LOGIC_NAMED_DESCRIPTION)) {
      { Object* arg002 = arg;
        NamedDescription* arg = ((NamedDescription*)(arg002));

        return (internSymbol(arg->surrogateValueInverse->symbolName));
      }
    }
    else if (subtypeOfP(testValue000, SGT_MACHINE_LEARNING_LOGIC_DESCRIPTION)) {
      { Object* arg003 = arg;
        Description* arg = ((Description*)(arg003));

        throw *newLogicException("Can't consify");
      }
    }
    else if (subtypeOfSurrogateP(testValue000)) {
      { Object* arg004 = arg;
        Surrogate* arg = ((Surrogate*)(arg004));

        return (internSymbol(((Surrogate*)(arg))->symbolName));
      }
    }
    else if (subtypeOfP(testValue000, SGT_MACHINE_LEARNING_LOGIC_SKOLEM)) {
      { Object* arg005 = arg;
        Skolem* arg = ((Skolem*)(arg005));

        if (((boolean)(((Object*)(accessInContext(arg->variableValue, arg->homeContext, false)))))) {
          return (consifyArgument(((Object*)(accessInContext(arg->variableValue, arg->homeContext, false)))));
        }
        else {
          if (((boolean)(arg->definingProposition))) {
            { Proposition* prop = arg->definingProposition;
              Vector* skArgs = prop->arguments;
              Cons* consArgs = NIL;

              { int i = NULL_INTEGER;
                int iter000 = 0;
                int upperBound000 = skArgs->length() - 2;
                Cons* collect000 = NULL;

                for  (; iter000 <= upperBound000; 
                      iter000 = iter000 + 1) {
                  i = iter000;
                  if (!((boolean)(collect000))) {
                    {
                      collect000 = cons(consifyArgument((skArgs->theArray)[i]), NIL);
                      if (consArgs == NIL) {
                        consArgs = collect000;
                      }
                      else {
                        addConsToEndOfConsList(consArgs, collect000);
                      }
                    }
                  }
                  else {
                    {
                      collect000->rest = cons(consifyArgument((skArgs->theArray)[i]), NIL);
                      collect000 = collect000->rest;
                    }
                  }
                }
              }
              return (cons(internSymbol(stringifiedKifOperator(prop)), consArgs));
            }
          }
          else {
            return (arg);
          }
        }
      }
    }
    else if (subtypeOfP(testValue000, SGT_MACHINE_LEARNING_LOGIC_LOGIC_OBJECT)) {
      { Object* arg006 = arg;
        LogicObject* arg = ((LogicObject*)(arg006));

        return (internSymbol(arg->surrogateValueInverse->symbolName));
      }
    }
    else {
      return (arg);
    }
  }
}

Cons* propositionToCons(Proposition* prop) {
  { Cons* result = NIL;

    { Object* arg = NULL;
      Vector* vector000 = prop->arguments;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        arg = (vector000->theArray)[index000];
        result = cons(consifyArgument(arg), result);
      }
    }
    { Keyword* testValue000 = prop->kind;

      if (testValue000 == KWD_MACHINE_LEARNING_IN) {
        return (result);
      }
      else if ((testValue000 == KWD_MACHINE_LEARNING_PREDICATE) ||
          (testValue000 == KWD_MACHINE_LEARNING_FUNCTION)) {
        result = cons(internSymbolInModule(((Surrogate*)(prop->operatoR))->symbolName, ((Module*)(((Surrogate*)(prop->operatoR))->homeContext)), true), result->reverse());
      }
      else if (testValue000 == KWD_MACHINE_LEARNING_EQUIVALENT) {
        result = cons(SYM_MACHINE_LEARNING_STELLA_e, result->reverse());
      }
      else if ((testValue000 == KWD_MACHINE_LEARNING_FORALL) ||
          (testValue000 == KWD_MACHINE_LEARNING_EXISTS)) {
        if (!(result->rest == NIL)) {
          result = consList(3, SYM_MACHINE_LEARNING_STELLA_OR, consList(2, SYM_MACHINE_LEARNING_STELLA_NOT, result->rest->value), result->value);
        }
        else {
          result = ((Cons*)(result->value));
        }
        { Cons* bindings = NIL;

          { PatternVariable* io = NULL;
            Vector* vector001 = ((Vector*)(dynamicSlotValue(prop->dynamicSlots, SYM_MACHINE_LEARNING_LOGIC_IO_VARIABLES, NULL)));
            int index001 = 0;
            int length001 = vector001->length();

            for  (; index001 < length001; 
                  index001 = index001 + 1) {
              io = ((PatternVariable*)((vector001->theArray)[index001]));
              if (!((boolean)(argumentBoundTo(io)))) {
                bindings = cons(consList(2, internSymbol(getSkolemPrintName(io)), internSymbol(logicalType(io)->symbolName)), bindings);
              }
            }
          }
          if (!(bindings == NIL)) {
            result = consList(3, internSymbol(prop->kind->symbolName), bindings, result);
          }
        }
      }
      else {
        result = cons(internSymbol(((Surrogate*)(prop->operatoR))->symbolName), result->reverse());
      }
    }
    if (falseP(prop)) {
      return (listO(3, SYM_MACHINE_LEARNING_STELLA_NOT, result, NIL));
    }
    else {
      return (result);
    }
  }
}

void thingifyUntypedInstances() {
  { LogicObject* item = NULL;
    Iterator* iter000 = allNamedInstances(oMODULEo, true);

    for (; iter000->nextP(); ) {
      item = ((LogicObject*)(iter000->value));
      if (allAssertedTypes(item) == NIL) {
        assertIsaProposition(item, SGT_MACHINE_LEARNING_STELLA_THING);
      }
    }
  }
}

void helpStartupMachineLearning1() {
  {
    SGT_MACHINE_LEARNING_LOGIC_TRAINING_EXAMPLE = ((Surrogate*)(internRigidSymbolWrtModule("TRAINING-EXAMPLE", NULL, 1)));
    SYM_MACHINE_LEARNING_LOGIC_QUERY = ((Symbol*)(internRigidSymbolWrtModule("QUERY", NULL, 0)));
    SYM_MACHINE_LEARNING_LOGIC_CONCEPT = ((Symbol*)(internRigidSymbolWrtModule("CONCEPT", NULL, 0)));
    SYM_MACHINE_LEARNING_STELLA_NAME = ((Symbol*)(internRigidSymbolWrtModule("NAME", getStellaModule("/STELLA", true), 0)));
    SYM_MACHINE_LEARNING_LOGIC_SCORE = ((Symbol*)(internRigidSymbolWrtModule("SCORE", NULL, 0)));
    SYM_MACHINE_LEARNING_STELLA_MODULE = ((Symbol*)(internRigidSymbolWrtModule("MODULE", getStellaModule("/STELLA", true), 0)));
    SYM_MACHINE_LEARNING_LOGIC_INPUT_FEATURES = ((Symbol*)(internRigidSymbolWrtModule("INPUT-FEATURES", NULL, 0)));
    SYM_MACHINE_LEARNING_LOGIC_INPUT = ((Symbol*)(internRigidSymbolWrtModule("INPUT", NULL, 0)));
    SYM_MACHINE_LEARNING_LOGIC_FACTS = ((Symbol*)(internRigidSymbolWrtModule("FACTS", NULL, 0)));
    SYM_MACHINE_LEARNING_LOGIC_NN_HIDDEN = ((Symbol*)(internRigidSymbolWrtModule("NN-HIDDEN", NULL, 0)));
    SYM_MACHINE_LEARNING_LOGIC_OUTPUT = ((Symbol*)(internRigidSymbolWrtModule("OUTPUT", NULL, 0)));
    SYM_MACHINE_LEARNING_LOGIC_TEMP = ((Symbol*)(internRigidSymbolWrtModule("TEMP", NULL, 0)));
    SYM_MACHINE_LEARNING_LOGIC_CACHED_SOLUTION = ((Symbol*)(internRigidSymbolWrtModule("CACHED-SOLUTION", NULL, 0)));
    SYM_MACHINE_LEARNING_LOGIC_TIMESTAMP = ((Symbol*)(internRigidSymbolWrtModule("TIMESTAMP", NULL, 0)));
    KWD_MACHINE_LEARNING_MATCH_MODE = ((Keyword*)(internRigidSymbolWrtModule("MATCH-MODE", NULL, 2)));
    KWD_MACHINE_LEARNING_BASIC = ((Keyword*)(internRigidSymbolWrtModule("BASIC", NULL, 2)));
    KWD_MACHINE_LEARNING_MAXIMIZE_SCOREp = ((Keyword*)(internRigidSymbolWrtModule("MAXIMIZE-SCORE?", NULL, 2)));
    SYM_MACHINE_LEARNING_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", getStellaModule("/STELLA", true), 0)));
    KWD_MACHINE_LEARNING_MOVEOUT = ((Keyword*)(internRigidSymbolWrtModule("MOVEOUT", NULL, 2)));
    KWD_MACHINE_LEARNING_RETRACT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("RETRACT-TRUE", NULL, 2)));
    KWD_MACHINE_LEARNING_ASSERT_TRUE = ((Keyword*)(internRigidSymbolWrtModule("ASSERT-TRUE", NULL, 2)));
    KWD_MACHINE_LEARNING_RETRACT_FALSE = ((Keyword*)(internRigidSymbolWrtModule("RETRACT-FALSE", NULL, 2)));
    KWD_MACHINE_LEARNING_ASSERT_FALSE = ((Keyword*)(internRigidSymbolWrtModule("ASSERT-FALSE", NULL, 2)));
    SYM_MACHINE_LEARNING_LOGIC_DEFRELATION = ((Symbol*)(internRigidSymbolWrtModule("DEFRELATION", NULL, 0)));
    SYM_MACHINE_LEARNING_LOGIC_pP = ((Symbol*)(internRigidSymbolWrtModule("?P", NULL, 0)));
    SYM_MACHINE_LEARNING_STELLA_THING = ((Symbol*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 0)));
    SYM_MACHINE_LEARNING_LOGIC_DEFRULE = ((Symbol*)(internRigidSymbolWrtModule("DEFRULE", NULL, 0)));
    SYM_MACHINE_LEARNING_STELLA_FORALL = ((Symbol*)(internRigidSymbolWrtModule("FORALL", getStellaModule("/STELLA", true), 0)));
    SYM_MACHINE_LEARNING_STELLA_eg = ((Symbol*)(internRigidSymbolWrtModule("=>", getStellaModule("/STELLA", true), 0)));
    SYM_MACHINE_LEARNING_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    SYM_MACHINE_LEARNING_LOGIC_pY = ((Symbol*)(internRigidSymbolWrtModule("?Y", NULL, 0)));
    SYM_MACHINE_LEARNING_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", getStellaModule("/STELLA", true), 0)));
    SGT_MACHINE_LEARNING_STELLA_FLOAT = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT", getStellaModule("/STELLA", true), 1)));
    KWD_MACHINE_LEARNING_ISA = ((Keyword*)(internRigidSymbolWrtModule("ISA", NULL, 2)));
    KWD_MACHINE_LEARNING_FUNCTION = ((Keyword*)(internRigidSymbolWrtModule("FUNCTION", NULL, 2)));
    SGT_MACHINE_LEARNING_STELLA_NUMBER_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", getStellaModule("/STELLA", true), 1)));
    SYM_MACHINE_LEARNING_STELLA_ge = ((Symbol*)(internRigidSymbolWrtModule(">=", getStellaModule("/STELLA", true), 0)));
    SYM_MACHINE_LEARNING_STELLA_el = ((Symbol*)(internRigidSymbolWrtModule("=<", getStellaModule("/STELLA", true), 0)));
    SYM_MACHINE_LEARNING_STELLA_e = ((Symbol*)(internRigidSymbolWrtModule("=", getStellaModule("/STELLA", true), 0)));
    SGT_MACHINE_LEARNING_STELLA_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("SYMBOL", getStellaModule("/STELLA", true), 1)));
    SGT_MACHINE_LEARNING_LOGIC_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("DESCRIPTION", NULL, 1)));
    SGT_MACHINE_LEARNING_LOGIC_SKOLEM = ((Surrogate*)(internRigidSymbolWrtModule("SKOLEM", NULL, 1)));
    SGT_MACHINE_LEARNING_LOGIC_LOGIC_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("LOGIC-OBJECT", NULL, 1)));
    SGT_MACHINE_LEARNING_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    SGT_MACHINE_LEARNING_LOGIC_PATTERN_VARIABLE = ((Surrogate*)(internRigidSymbolWrtModule("PATTERN-VARIABLE", NULL, 1)));
    SGT_MACHINE_LEARNING_LOGIC_NAMED_DESCRIPTION = ((Surrogate*)(internRigidSymbolWrtModule("NAMED-DESCRIPTION", NULL, 1)));
    KWD_MACHINE_LEARNING_IN = ((Keyword*)(internRigidSymbolWrtModule("IN", NULL, 2)));
    KWD_MACHINE_LEARNING_PREDICATE = ((Keyword*)(internRigidSymbolWrtModule("PREDICATE", NULL, 2)));
    KWD_MACHINE_LEARNING_EQUIVALENT = ((Keyword*)(internRigidSymbolWrtModule("EQUIVALENT", NULL, 2)));
    KWD_MACHINE_LEARNING_FORALL = ((Keyword*)(internRigidSymbolWrtModule("FORALL", NULL, 2)));
    KWD_MACHINE_LEARNING_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("EXISTS", NULL, 2)));
    SYM_MACHINE_LEARNING_STELLA_OR = ((Symbol*)(internRigidSymbolWrtModule("OR", getStellaModule("/STELLA", true), 0)));
    SYM_MACHINE_LEARNING_LOGIC_IO_VARIABLES = ((Symbol*)(internRigidSymbolWrtModule("IO-VARIABLES", NULL, 0)));
    SGT_MACHINE_LEARNING_STELLA_THING = ((Surrogate*)(internRigidSymbolWrtModule("THING", getStellaModule("/STELLA", true), 1)));
    SYM_MACHINE_LEARNING_LOGIC_STARTUP_MACHINE_LEARNING = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-MACHINE-LEARNING", NULL, 0)));
    SYM_MACHINE_LEARNING_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void startupMachineLearning() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupMachineLearning1();
    }
    if (currentStartupTimePhaseP(4)) {
      oTRAINING_EXAMPLESo = newList();
      oTESTING_EXAMPLESo = newList();
      oTABOO_OPERATORSo = newList();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("TRAINING-EXAMPLE", "(DEFCLASS TRAINING-EXAMPLE (STANDARD-OBJECT) :DOCUMENTATION \"A single example of a proposition paired with the score\n  that should be returned and the module it should be evaluated in.\" :SLOTS ((QUERY :TYPE CONS) (CONCEPT :TYPE SYMBOL) (NAME :TYPE SYMBOL) (SCORE :TYPE PARTIAL-MATCH-SCORE) (MODULE :TYPE MODULE) (INPUT-FEATURES :TYPE LIST) (INPUT :TYPE VECTOR) (FACTS :TYPE (CONS OF CONS)) (NN-HIDDEN :TYPE (VECTOR OF FLOAT-WRAPPER)) (OUTPUT :TYPE OBJECT) (TEMP :TYPE FLOAT) (CACHED-SOLUTION :TYPE OBJECT) (TIMESTAMP :TYPE TIMESTAMP)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newTrainingExample));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessTrainingExampleSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("SET-CLOSED-WORLD-TRAINING-EXAMPLES", "(DEFUN SET-CLOSED-WORLD-TRAINING-EXAMPLES ((B BOOLEAN)) :COMMAND? TRUE)", ((cpp_function_code)(&setClosedWorldTrainingExamples)), ((cpp_function_code)(&setClosedWorldTrainingExamplesEvaluatorWrapper)));
      defineFunctionObject("PRINT-TRAINING-EXAMPLE", "(DEFUN PRINT-TRAINING-EXAMPLE ((EXAMPLE TRAINING-EXAMPLE)))", ((cpp_function_code)(&printTrainingExample)), NULL);
      defineFunctionObject("ADD-TRAINING-EXAMPLE", "(DEFUN ADD-TRAINING-EXAMPLE ((FORM CONS) (SCORE PARTIAL-MATCH-SCORE)) :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :PUBLIC? TRUE :DOCUMENTATION \"Add a query and score pair to the master list of \n  training examples\")", ((cpp_function_code)(&addTrainingExample)), ((cpp_function_code)(&addTrainingExampleEvaluatorWrapper)));
      defineFunctionObject("ADD-TRAINING-EXAMPLE-IN-MODULE", "(DEFUN ADD-TRAINING-EXAMPLE-IN-MODULE ((FORM CONS) (SCORE PARTIAL-MATCH-SCORE) (MODULE SYMBOL)) :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :PUBLIC? TRUE)", ((cpp_function_code)(&addTrainingExampleInModule)), ((cpp_function_code)(&addTrainingExampleInModuleEvaluatorWrapper)));
      defineFunctionObject("ADD-TESTING-EXAMPLE", "(DEFUN ADD-TESTING-EXAMPLE ((FORM CONS) (SCORE PARTIAL-MATCH-SCORE)) :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :PUBLIC? TRUE :DOCUMENTATION \"Add a query and score pair to the master list of \n  testing examples\")", ((cpp_function_code)(&addTestingExample)), ((cpp_function_code)(&addTestingExampleEvaluatorWrapper)));
      defineFunctionObject("CLEAR-TRAINING-EXAMPLES", "(DEFUN CLEAR-TRAINING-EXAMPLES () :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&clearTrainingExamples)), NULL);
      defineFunctionObject("SHUFFLE-LIST", "(DEFUN SHUFFLE-LIST ((CARDS LIST)))", ((cpp_function_code)(&shuffleList)), NULL);
      defineFunctionObject("SHUFFLE-VECTOR", "(DEFUN SHUFFLE-VECTOR ((CARDS VECTOR)))", ((cpp_function_code)(&shuffleVector)), NULL);
      defineFunctionObject("SAVE-TRAINING-EXAMPLES", "(DEFUN SAVE-TRAINING-EXAMPLES () :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&saveTrainingExamples)), NULL);
      defineFunctionObject("CREATE-PROPOSITIONAL-TRAINING-EXAMPLES", "(DEFUN (CREATE-PROPOSITIONAL-TRAINING-EXAMPLES INTEGER) ((EXAMPLES (LIST OF TRAINING-EXAMPLE)) (NAME-FILE OUTPUT-FILE-STREAM) (DATA-FILE OUTPUT-FILE-STREAM)))", ((cpp_function_code)(&createPropositionalTrainingExamples)), NULL);
      defineFunctionObject("FILL-IN-EXAMPLE-OUTPUTS", "(DEFUN FILL-IN-EXAMPLE-OUTPUTS ((EXAMPLES (LIST OF TRAINING-EXAMPLE)) (SLOT-NAME SYMBOL)))", ((cpp_function_code)(&fillInExampleOutputs)), NULL);
      defineFunctionObject("DETECT-NOISE-IN-TRAINING-EXAMPLES", "(DEFUN DETECT-NOISE-IN-TRAINING-EXAMPLES ((EXAMPLES (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&detectNoiseInTrainingExamples)), NULL);
      defineFunctionObject("GET-CLASSIFICATION-RELATIONS", "(DEFUN (GET-CLASSIFICATION-RELATIONS (LIST OF PROPOSITION)) ((CONS-QUERY CONS)))", ((cpp_function_code)(&getClassificationRelations)), NULL);
      defineFunctionObject("CREATE-INPUT-SIGNATURE", "(DEFUN (CREATE-INPUT-SIGNATURE (VECTOR OF INTEGER-WRAPPER)) ((CONS-QUERY CONS)))", ((cpp_function_code)(&createInputSignature)), NULL);
      defineFunctionObject("GENERATE-CLASSIFICATION-RULE", "(DEFUN GENERATE-CLASSIFICATION-RULE ((INSTANCES (VECTOR OF LOGIC-OBJECT)) (CONCEPT-NAME SYMBOL) (CLASS-NAME SYMBOL) (BUILD-RULE? BOOLEAN)))", ((cpp_function_code)(&generateClassificationRule)), NULL);
      defineFunctionObject("BUILD-CLASSIFICATION-RULE", "(DEFUN BUILD-CLASSIFICATION-RULE ((KIND SYMBOL) (CLASS-NAME SYMBOL)))", ((cpp_function_code)(&buildClassificationRule)), NULL);
      defineFunctionObject("OLD-GENERATE-CLASSIFICATION-TRAINING-EXAMPLES", "(DEFUN (OLD-GENERATE-CLASSIFICATION-TRAINING-EXAMPLES INTEGER) ((INSTANCES (VECTOR OF LOGIC-OBJECT)) (CONCEPT SURROGATE)))", ((cpp_function_code)(&oldGenerateClassificationTrainingExamples)), NULL);
      defineFunctionObject("TEST-DOMAIN-THEORY", "(DEFUN TEST-DOMAIN-THEORY ((RELATION-NAME SYMBOL) (CLASS-NAME SYMBOL)) :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :PUBLIC? TRUE)", ((cpp_function_code)(&testDomainTheory)), NULL);
      defineFunctionObject("TEST-THEORY-OVER-EXAMPLES", "(DEFUN (TEST-THEORY-OVER-EXAMPLES FLOAT) ((EXAMPLES (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&testTheoryOverExamples)), NULL);
      defineFunctionObject("GENERATE-TRAINING-EXAMPLES", "(DEFUN (GENERATE-TRAINING-EXAMPLES INTEGER) ((INSTANCES (VECTOR OF LOGIC-OBJECT)) (CONCEPT SURROGATE)))", ((cpp_function_code)(&generateTrainingExamples)), NULL);
      defineFunctionObject("GENERATE-CLASSIFICATION-TRAINING-EXAMPLES", "(DEFUN (GENERATE-CLASSIFICATION-TRAINING-EXAMPLES INTEGER) ((INSTANCES (VECTOR OF LOGIC-OBJECT)) (CONCEPT SURROGATE) (CREATE-SIGNATURE? BOOLEAN)))", ((cpp_function_code)(&generateClassificationTrainingExamples)), NULL);
      defineFunctionObject("GENERATE-REGRESSION-RULE-WO-SLOT", "(DEFUN GENERATE-REGRESSION-RULE-WO-SLOT ((CASES (VECTOR OF LOGIC-OBJECT)) (SLOT-NAME SYMBOL) (CLASS-NAME SYMBOL) (REALLY-BUILD-RULE BOOLEAN)))", ((cpp_function_code)(&generateRegressionRuleWoSlot)), NULL);
      defineFunctionObject("GENERATE-REGRESSION-TRAINING-EXAMPLES", "(DEFUN (GENERATE-REGRESSION-TRAINING-EXAMPLES INTEGER) ((INSTANCES (VECTOR OF LOGIC-OBJECT)) (SLOT SURROGATE)))", ((cpp_function_code)(&generateRegressionTrainingExamples)), NULL);
      defineFunctionObject("APPROXIMATE", "(DEFUN (APPROXIMATE FLOAT) ((INST-NAME SYMBOL) (SLOT-NAME SYMBOL)) :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :PUBLIC? TRUE)", ((cpp_function_code)(&approximate)), ((cpp_function_code)(&approximateEvaluatorWrapper)));
      defineFunctionObject("GENERATE-SLOT-APPROXIMATION", "(DEFUN (GENERATE-SLOT-APPROXIMATION FLOAT) ((INST-NAME SYMBOL) (SLOT SURROGATE)))", ((cpp_function_code)(&generateSlotApproximation)), NULL);
      defineFunctionObject("FLOAT-FUNCTION?", "(DEFUN (FLOAT-FUNCTION? BOOLEAN) ((RELATION SURROGATE)))", ((cpp_function_code)(((boolean  (*) (Surrogate*))(&floatFunctionP)))), NULL);
      defineFunctionObject("SET-STRUCTURE-DEPTH", "(DEFUN SET-STRUCTURE-DEPTH ((D INTEGER)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setStructureDepth)), ((cpp_function_code)(&setStructureDepthEvaluatorWrapper)));
      defineFunctionObject("ADD-TABOO-OPERATORS", "(DEFUN ADD-TABOO-OPERATORS ((S SYMBOL)) :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&addTabooOperators)), NULL);
      defineFunctionObject("GET-ASSERTION-STRUCTURE", "(DEFUN (GET-ASSERTION-STRUCTURE (LIST OF CONS)) ((INST SYMBOL) (DEPTH INTEGER)))", ((cpp_function_code)(&getAssertionStructure)), NULL);
      defineFunctionObject("HELP-GET-ASSERTION-STRUCTURE", "(DEFUN (HELP-GET-ASSERTION-STRUCTURE (LIST OF CONS)) ((INST SYMBOL) (DEPTH INTEGER)))", ((cpp_function_code)(&helpGetAssertionStructure)), NULL);
      defineFunctionObject("COLLECT-FACTS-IN-EXAMPLES", "(DEFUN COLLECT-FACTS-IN-EXAMPLES ((EXAMPLES (LIST OF TRAINING-EXAMPLE))))", ((cpp_function_code)(&collectFactsInExamples)), NULL);
      defineFunctionObject("OLD-RECURSIVE-BUILD-ANTECEDENT", "(DEFUN (OLD-RECURSIVE-BUILD-ANTECEDENT CONS) ((INST SYMBOL) (DEPTH INTEGER)))", ((cpp_function_code)(&oldRecursiveBuildAntecedent)), NULL);
      defineFunctionObject("GET-ARGUMENT-BINDING", "(DEFUN (GET-ARGUMENT-BINDING OBJECT) ((ARG OBJECT)))", ((cpp_function_code)(&getArgumentBinding)), NULL);
      defineFunctionObject("CONSIFY-ARGUMENT", "(DEFUN (CONSIFY-ARGUMENT OBJECT) ((ARG OBJECT)))", ((cpp_function_code)(&consifyArgument)), NULL);
      defineFunctionObject("PROPOSITION-TO-CONS", "(DEFUN (PROPOSITION-TO-CONS CONS) ((PROP PROPOSITION)))", ((cpp_function_code)(&propositionToCons)), NULL);
      defineFunctionObject("THINGIFY-UNTYPED-INSTANCES", "(DEFUN THINGIFY-UNTYPED-INSTANCES () :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&thingifyUntypedInstances)), NULL);
      defineFunctionObject("STARTUP-MACHINE-LEARNING", "(DEFUN STARTUP-MACHINE-LEARNING () :PUBLIC? TRUE)", ((cpp_function_code)(&startupMachineLearning)), NULL);
      { MethodSlot* function = lookupFunction(SYM_MACHINE_LEARNING_LOGIC_STARTUP_MACHINE_LEARNING);

        setDynamicSlotValue(function->dynamicSlots, SYM_MACHINE_LEARNING_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupMachineLearning"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFGLOBAL *TRAINING-EXAMPLES* (LIST OF TRAINING-EXAMPLE) (NEW LIST))", &oTRAINING_EXAMPLESo);
      defineGlobalVariableObject("(DEFGLOBAL *TESTING-EXAMPLES* (LIST OF TRAINING-EXAMPLE) (NEW LIST))", &oTESTING_EXAMPLESo);
      defineGlobalVariableObject("(DEFGLOBAL *CLOSED-WORLD-TRAINING-EXAMPLES* BOOLEAN TRUE)", &oCLOSED_WORLD_TRAINING_EXAMPLESo);
      defineGlobalVariableObject("(DEFGLOBAL *MAX-STRUCTURE-DEPTH* INTEGER 3)", &oMAX_STRUCTURE_DEPTHo);
      defineGlobalVariableObject("(DEFGLOBAL *DROP-FUNCTION-VALUES?* BOOLEAN TRUE)", &oDROP_FUNCTION_VALUESpo);
      defineGlobalVariableObject("(DEFGLOBAL *TABOO-OPERATORS* (LIST OF SURROGATE) (NEW (LIST OF SURROGATE)))", &oTABOO_OPERATORSo);
    }
  }
}

Surrogate* SGT_MACHINE_LEARNING_LOGIC_TRAINING_EXAMPLE = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_QUERY = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_CONCEPT = NULL;

Symbol* SYM_MACHINE_LEARNING_STELLA_NAME = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_SCORE = NULL;

Symbol* SYM_MACHINE_LEARNING_STELLA_MODULE = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_INPUT_FEATURES = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_INPUT = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_FACTS = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_NN_HIDDEN = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_OUTPUT = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_TEMP = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_CACHED_SOLUTION = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_TIMESTAMP = NULL;

Keyword* KWD_MACHINE_LEARNING_MATCH_MODE = NULL;

Keyword* KWD_MACHINE_LEARNING_BASIC = NULL;

Keyword* KWD_MACHINE_LEARNING_MAXIMIZE_SCOREp = NULL;

Symbol* SYM_MACHINE_LEARNING_STELLA_TRUE = NULL;

Keyword* KWD_MACHINE_LEARNING_MOVEOUT = NULL;

Keyword* KWD_MACHINE_LEARNING_RETRACT_TRUE = NULL;

Keyword* KWD_MACHINE_LEARNING_ASSERT_TRUE = NULL;

Keyword* KWD_MACHINE_LEARNING_RETRACT_FALSE = NULL;

Keyword* KWD_MACHINE_LEARNING_ASSERT_FALSE = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_DEFRELATION = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_pP = NULL;

Symbol* SYM_MACHINE_LEARNING_STELLA_THING = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_DEFRULE = NULL;

Symbol* SYM_MACHINE_LEARNING_STELLA_FORALL = NULL;

Symbol* SYM_MACHINE_LEARNING_STELLA_eg = NULL;

Symbol* SYM_MACHINE_LEARNING_STELLA_AND = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_pY = NULL;

Symbol* SYM_MACHINE_LEARNING_STELLA_NOT = NULL;

Surrogate* SGT_MACHINE_LEARNING_STELLA_FLOAT = NULL;

Keyword* KWD_MACHINE_LEARNING_ISA = NULL;

Keyword* KWD_MACHINE_LEARNING_FUNCTION = NULL;

Surrogate* SGT_MACHINE_LEARNING_STELLA_NUMBER_WRAPPER = NULL;

Symbol* SYM_MACHINE_LEARNING_STELLA_ge = NULL;

Symbol* SYM_MACHINE_LEARNING_STELLA_el = NULL;

Symbol* SYM_MACHINE_LEARNING_STELLA_e = NULL;

Surrogate* SGT_MACHINE_LEARNING_STELLA_SYMBOL = NULL;

Surrogate* SGT_MACHINE_LEARNING_LOGIC_DESCRIPTION = NULL;

Surrogate* SGT_MACHINE_LEARNING_LOGIC_SKOLEM = NULL;

Surrogate* SGT_MACHINE_LEARNING_LOGIC_LOGIC_OBJECT = NULL;

Surrogate* SGT_MACHINE_LEARNING_LOGIC_PROPOSITION = NULL;

Surrogate* SGT_MACHINE_LEARNING_LOGIC_PATTERN_VARIABLE = NULL;

Surrogate* SGT_MACHINE_LEARNING_LOGIC_NAMED_DESCRIPTION = NULL;

Keyword* KWD_MACHINE_LEARNING_IN = NULL;

Keyword* KWD_MACHINE_LEARNING_PREDICATE = NULL;

Keyword* KWD_MACHINE_LEARNING_EQUIVALENT = NULL;

Keyword* KWD_MACHINE_LEARNING_FORALL = NULL;

Keyword* KWD_MACHINE_LEARNING_EXISTS = NULL;

Symbol* SYM_MACHINE_LEARNING_STELLA_OR = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_IO_VARIABLES = NULL;

Surrogate* SGT_MACHINE_LEARNING_STELLA_THING = NULL;

Symbol* SYM_MACHINE_LEARNING_LOGIC_STARTUP_MACHINE_LEARNING = NULL;

Symbol* SYM_MACHINE_LEARNING_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
