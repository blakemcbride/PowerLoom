//  -*- Mode: C++ -*-

// neural-network.cc

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

Keyword* oNEURAL_NETWORK_TRAINING_METHODo = NULL;

double oLEARNING_RATEo = 0.1;

double oMOMENTUM_TERMo = 0.9;

double oWEIGHT_RANGEo = 0.05;

double oERROR_CUTOFFo = 0.0;

int oERROR_PRINT_CYCLEo = 25;

int oSAVE_NETWORK_CYCLEo = 10000;

const char* oSAVE_NETWORK_FILEo = NULL;

boolean oTRACE_NEURAL_NETWORK_TRAININGo = false;

boolean oTRAIN_CACHED_NETWORKSpo = true;

double oMAX_MOVEMENTo = 1.75;

double oMODE_SWITCHo = 0.0;

double oSHRINK_FACTORo = NULL_FLOAT;

double oWEIGHT_DECAYo = -1.0e-4;

double oSIGMOID_PRIME_OFFSETo = 0.1;

PropositionNeuralNetwork* newPropositionNeuralNetwork() {
  { PropositionNeuralNetwork* self = NULL;

    self = new PropositionNeuralNetwork();
    self->hoPrevSlope = NULL;
    self->hoSlope = NULL;
    self->ihPrevSlope = NULL;
    self->ihSlope = NULL;
    self->hoDelta = NULL;
    self->ho = NULL;
    self->ihDelta = NULL;
    self->ih = NULL;
    self->hiddenError = NULL;
    self->inputError = NULL;
    self->output = NULL_FLOAT;
    self->hidden = NULL;
    self->input = NULL;
    self->proposition = NULL;
    return (self);
  }
}

Surrogate* PropositionNeuralNetwork::primaryType() {
  { PropositionNeuralNetwork* self = this;

    return (SGT_NEURAL_NETWORK_LOGIC_PROPOSITION_NEURAL_NETWORK);
  }
}

Object* accessPropositionNeuralNetworkSlotValue(PropositionNeuralNetwork* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_NEURAL_NETWORK_LOGIC_PROPOSITION) {
    if (setvalueP) {
      self->proposition = ((Proposition*)(value));
    }
    else {
      value = self->proposition;
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_INPUT) {
    if (setvalueP) {
      self->input = ((Vector*)(value));
    }
    else {
      value = self->input;
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_HIDDEN) {
    if (setvalueP) {
      self->hidden = ((Vector*)(value));
    }
    else {
      value = self->hidden;
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_OUTPUT) {
    if (setvalueP) {
      self->output = ((FloatWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFloat(self->output);
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_INPUT_ERROR) {
    if (setvalueP) {
      self->inputError = ((Vector*)(value));
    }
    else {
      value = self->inputError;
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_HIDDEN_ERROR) {
    if (setvalueP) {
      self->hiddenError = ((Vector*)(value));
    }
    else {
      value = self->hiddenError;
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_IH) {
    if (setvalueP) {
      self->ih = ((two_D_array*)(value));
    }
    else {
      value = self->ih;
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_IH_DELTA) {
    if (setvalueP) {
      self->ihDelta = ((two_D_array*)(value));
    }
    else {
      value = self->ihDelta;
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_HO) {
    if (setvalueP) {
      self->ho = ((Vector*)(value));
    }
    else {
      value = self->ho;
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_HO_DELTA) {
    if (setvalueP) {
      self->hoDelta = ((Vector*)(value));
    }
    else {
      value = self->hoDelta;
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_IH_SLOPE) {
    if (setvalueP) {
      self->ihSlope = ((two_D_array*)(value));
    }
    else {
      value = self->ihSlope;
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_IH_PREV_SLOPE) {
    if (setvalueP) {
      self->ihPrevSlope = ((two_D_array*)(value));
    }
    else {
      value = self->ihPrevSlope;
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_HO_SLOPE) {
    if (setvalueP) {
      self->hoSlope = ((Vector*)(value));
    }
    else {
      value = self->hoSlope;
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_HO_PREV_SLOPE) {
    if (setvalueP) {
      self->hoPrevSlope = ((Vector*)(value));
    }
    else {
      value = self->hoPrevSlope;
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

List* oMASTER_NEURAL_NETWORK_LISTo = NULL;

List* oACTIVATED_NETWORKSo = NULL;

PropositionNeuralNetwork* oSAVED_NETo = NULL;

void setTraceNeuralNetworkTraining(boolean b) {
  oTRACE_NEURAL_NETWORK_TRAININGo = b;
}

void setTraceNeuralNetworkTrainingEvaluatorWrapper(Cons* arguments) {
  setTraceNeuralNetworkTraining(((BooleanWrapper*)(arguments->value))->wrapperValue);
}

void setSaveNetworkCycle(int i) {
  // Set number of cycles between which networks are saved to the
  // file established by the last call to `save-all-neural-networks'.  A number <= 0
  // or a NULL number turns off periodic saving.
  if (i == NULL_INTEGER) {
    i = 0;
  }
  oSAVE_NETWORK_CYCLEo = i;
}

void setSaveNetworkCycleEvaluatorWrapper(Cons* arguments) {
  setSaveNetworkCycle(((IntegerWrapper*)(arguments->value))->wrapperValue);
}

void setErrorCutoff(double f) {
  oERROR_CUTOFFo = f;
}

void setErrorCutoffEvaluatorWrapper(Cons* arguments) {
  setErrorCutoff(((FloatWrapper*)(arguments->value))->wrapperValue);
}

void setTrainCachedNeuralNetworks(boolean b) {
  oTRAIN_CACHED_NETWORKSpo = b;
}

void setTrainCachedNeuralNetworksEvaluatorWrapper(Cons* arguments) {
  setTrainCachedNeuralNetworks(((BooleanWrapper*)(arguments->value))->wrapperValue);
}

void setLearningRate(double rate) {
  oLEARNING_RATEo = rate;
}

void setLearningRateEvaluatorWrapper(Cons* arguments) {
  setLearningRate(((FloatWrapper*)(arguments->value))->wrapperValue);
}

void setMomentumTerm(double m) {
  oMOMENTUM_TERMo = m;
}

void setMomentumTermEvaluatorWrapper(Cons* arguments) {
  setMomentumTerm(((FloatWrapper*)(arguments->value))->wrapperValue);
}

void setWeightRange(double w) {
  oWEIGHT_RANGEo = w;
}

void setWeightRangeEvaluatorWrapper(Cons* arguments) {
  setWeightRange(((FloatWrapper*)(arguments->value))->wrapperValue);
}

void setNeuralNetworkTrainingMethod(Keyword* m) {
  oNEURAL_NETWORK_TRAINING_METHODo = m;
}

void setErrorPrintCycle(int i) {
  // Set number of cycles between which error rates are saved to
  // the file established by the last call to `save-all-neural-networks' appended
  // with extension `.err'.  A number <= 0 (or NULL) turns off periodic saving.
  if (i == NULL_INTEGER) {
    i = 0;
  }
  oERROR_PRINT_CYCLEo = i;
}

void setErrorPrintCycleEvaluatorWrapper(Cons* arguments) {
  setErrorPrintCycle(((IntegerWrapper*)(arguments->value))->wrapperValue);
}

void deleteAllNeuralNetworks() {
  oMASTER_NEURAL_NETWORK_LISTo = newList();
}

void checkMasterNetworkList() {
  { PropositionNeuralNetwork* net = NULL;
    Cons* iter000 = oMASTER_NEURAL_NETWORK_LISTo->theConsList;
    int i = NULL_INTEGER;
    int iter001 = 0;

    for  (; !(iter000 == NIL); 
          iter000 = iter000->rest,
          iter001 = iter001 + 1) {
      net = ((PropositionNeuralNetwork*)(iter000->value));
      i = iter001;
      std::cout << "Net " << i << ": " << net->input->length() << " inputs, " << net->hidden->length() << " outputs." << std::endl;
    }
  }
}

void clearAllNeuralNetworks() {
  { PropositionNeuralNetwork* net = NULL;
    Cons* iter000 = oMASTER_NEURAL_NETWORK_LISTo->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      net = ((PropositionNeuralNetwork*)(iter000->value));
      randomizeNeuralNetwork(net);
    }
  }
}

void clearAllSlopes() {
  { PropositionNeuralNetwork* net = NULL;
    Cons* iter000 = oMASTER_NEURAL_NETWORK_LISTo->theConsList;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      net = ((PropositionNeuralNetwork*)(iter000->value));
      clearSlopes(net);
    }
  }
}

void clearSlopes(PropositionNeuralNetwork* net) {
  { int h = NULL_INTEGER;
    int iter000 = 0;
    int upperBound000 = net->hidden->length() - 1;

    for  (; iter000 <= upperBound000; 
          iter000 = iter000 + 1) {
      h = iter000;
      { int i = NULL_INTEGER;
        int iter001 = 0;
        int upperBound001 = net->input->length() - 1;

        for  (; iter001 <= upperBound001; 
              iter001 = iter001 + 1) {
          i = iter001;
          (net->ihPrevSlope->theArray)[((i * net->ihPrevSlope->nofColumns) + h)] = (((FloatWrapper*)((net->ihSlope->theArray)[((i * net->ihSlope->nofColumns) + h)])));
          (net->ihSlope->theArray)[((i * net->ihSlope->nofColumns) + h)] = (wrapFloat(((FloatWrapper*)((net->ih->theArray)[((i * net->ih->nofColumns) + h)]))->wrapperValue * oWEIGHT_DECAYo));
        }
      }
      (net->hoPrevSlope->theArray)[h] = (((FloatWrapper*)((net->hoSlope->theArray)[h])));
      (net->hoSlope->theArray)[h] = (wrapFloat(((FloatWrapper*)((net->ho->theArray)[h]))->wrapperValue * oWEIGHT_DECAYo));
    }
  }
}

void randomizeNeuralNetwork(PropositionNeuralNetwork* net) {
  { int numIn = net->input->length();
    int numHidden = net->hidden->length();

    { int h = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = numHidden - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        h = iter000;
        (net->hoDelta->theArray)[h] = (wrapFloat(0.0));
        { int i = NULL_INTEGER;
          int iter001 = 0;
          int upperBound001 = numIn - 1;

          for  (; iter001 <= upperBound001; 
                iter001 = iter001 + 1) {
            i = iter001;
            (net->ihDelta->theArray)[((i * net->ihDelta->nofColumns) + h)] = (wrapFloat(0.0));
          }
        }
      }
    }
    { int i = NULL_INTEGER;
      int iter002 = 0;
      int upperBound002 = numHidden - 1;

      for  (; iter002 <= upperBound002; 
            iter002 = iter002 + 1) {
        i = iter002;
        { int j = NULL_INTEGER;
          int iter003 = 0;
          int upperBound003 = numIn - 1;

          for  (; iter003 <= upperBound003; 
                iter003 = iter003 + 1) {
            j = iter003;
            (net->ih->theArray)[((j * net->ih->nofColumns) + i)] = (wrapFloat(randomWeight(oWEIGHT_RANGEo)));
          }
        }
        (net->ho->theArray)[i] = (wrapFloat(randomWeight(oWEIGHT_RANGEo)));
      }
    }
  }
}

PropositionNeuralNetwork* createNeuralNetwork(Proposition* prop) {
  { PropositionNeuralNetwork* net = NULL;
    int numIn = prop->arguments->length() + 1;
    int numHidden = stella::integerMin(numIn + 0, 20);

    if (numIn > 100) {
      numHidden = stella::floor(numIn / 10.0) + 10;
    }
    net = allocateNeuralNetwork(numIn, numHidden);
    oMASTER_NEURAL_NETWORK_LISTo->push(net);
    net->proposition = prop;
    { Keyword* testValue000 = prop->kind;

      if ((testValue000 == KWD_NEURAL_NETWORK_AND) ||
          (testValue000 == KWD_NEURAL_NETWORK_OR)) {
        randomizeNeuralNetwork(net);
      }
      else {
        randomizeNeuralNetwork(net);
      }
    }
    return (net);
  }
}

Proposition* gnp(Symbol* name) {
  return (((Proposition*)(lookupSurrogate(name->symbolName)->surrogateValue)));
}

PropositionNeuralNetwork* defnetwork(Cons* args) {
  return (defineNeuralNetworkFromParseTree(args));
}

PropositionNeuralNetwork* defnetworkEvaluatorWrapper(Cons* arguments) {
  return (defnetwork(arguments));
}

PropositionNeuralNetwork* defineNeuralNetworkFromParseTree(Cons* tree) {
  { Object* prop = buildProposition(tree->value);
    PropositionNeuralNetwork* net = createNeuralNetwork(((Proposition*)(prop)));
    Cons* ih = ((Cons*)(tree->rest->value));
    Cons* ho = ((Cons*)(tree->rest->rest->value));
    int k = 0;

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = net->input->length() - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        { int h = NULL_INTEGER;
          int iter001 = 0;
          int upperBound001 = net->hidden->length() - 1;

          for  (; iter001 <= upperBound001; 
                iter001 = iter001 + 1) {
            h = iter001;
            (net->ih->theArray)[((i * net->ih->nofColumns) + h)] = (((FloatWrapper*)(ih->nth(k))));
            k = k + 1;
          }
        }
      }
    }
    { int h = NULL_INTEGER;
      int iter002 = 0;
      int upperBound002 = net->hidden->length() - 1;
      FloatWrapper* num = NULL;
      Cons* iter003 = ho;

      for  (; (iter002 <= upperBound002) &&
                (!(iter003 == NIL)); 
            iter002 = iter002 + 1,
            iter003 = iter003->rest) {
        h = iter002;
        num = ((FloatWrapper*)(iter003->value));
        (net->ho->theArray)[h] = num;
      }
    }
    return (net);
  }
}

PropositionNeuralNetwork* allocateNeuralNetwork(int numIn, int numHidden) {
  { PropositionNeuralNetwork* net = newPropositionNeuralNetwork();

    net->input = stella::newVector(numIn);
    net->hidden = stella::newVector(numHidden);
    net->ih = new2_D_array(numIn, numHidden);
    net->ihDelta = new2_D_array(numIn, numHidden);
    net->inputError = stella::newVector(numIn);
    net->hiddenError = stella::newVector(numHidden);
    net->ho = stella::newVector(numHidden);
    net->hoDelta = stella::newVector(numHidden);
    if (oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_QUICKPROP) {
      net->ihSlope = new2_D_array(numIn, numHidden);
      net->ihPrevSlope = new2_D_array(numIn, numHidden);
      net->hoSlope = stella::newVector(numHidden);
      net->hoPrevSlope = stella::newVector(numHidden);
    }
    return (net);
  }
}

double activatePropositionalNeuralNetwork(PropositionNeuralNetwork* net) {
  { int numIn = net->input->length();
    int numHidden = net->hidden->length();
    Vector* arguments = net->proposition->arguments;
    int stop = numIn - 1;
    Vector* input = net->input;
    Vector* hidden = net->hidden;
    two_D_array* ih = net->ih;
    Vector* ho = net->ho;
    double score = 0.0;
    double sum = 0.0;

    oACTIVATED_NETWORKSo->push(net);
    (net->input->theArray)[0] = (wrapFloat(1.0));
    { int i = NULL_INTEGER;
      int iter000 = 1;
      int upperBound000 = stop;
      boolean unboundedP000 = upperBound000 == NULL_INTEGER;

      for  (; unboundedP000 ||
                (iter000 <= upperBound000); 
            iter000 = iter000 + 1) {
        i = iter000;
        if (((FloatWrapper*)(dynamicSlotValue(((Proposition*)((arguments->theArray)[(i - 1)]))->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue != NULL_FLOAT) {
          (input->theArray)[i] = (wrapFloat(((FloatWrapper*)(dynamicSlotValue(((Proposition*)((arguments->theArray)[(i - 1)]))->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue));
        }
        else {
          (input->theArray)[i] = (wrapFloat(0.0));
        }
      }
    }
    { int i = NULL_INTEGER;
      int iter001 = 0;
      int upperBound001 = numHidden - 1;

      for  (; iter001 <= upperBound001; 
            iter001 = iter001 + 1) {
        i = iter001;
        { int j = NULL_INTEGER;
          int iter002 = 0;
          int upperBound002 = stop;
          boolean unboundedP001 = upperBound002 == NULL_INTEGER;

          for  (; unboundedP001 ||
                    (iter002 <= upperBound002); 
                iter002 = iter002 + 1) {
            j = iter002;
            sum = sum + (((FloatWrapper*)((input->theArray)[j]))->wrapperValue * ((FloatWrapper*)((ih->theArray)[((j * ih->nofColumns) + i)]))->wrapperValue);
          }
        }
        (hidden->theArray)[i] = (wrapFloat(1.0 / (1.0 + ::exp((0 - sum)))));
        score = score + (((FloatWrapper*)((hidden->theArray)[i]))->wrapperValue * ((FloatWrapper*)((ho->theArray)[i]))->wrapperValue);
      }
    }
    if ((1.0 + ::exp((0 - score))) == 0.0) {
      std::cout << "Sum is " << score << std::endl;
    }
    net->output = 1.0 / (1.0 + ::exp((0 - score)));
    setDynamicSlotValue(net->proposition->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, wrapFloat(net->output), NULL_FLOAT_WRAPPER);
    return (net->output);
  }
}

const char* makeNetInputString(Vector* input) {
  return (stringify(input));
}

void trainNeuralNetwork(int cycles, int numTraining) {
  if (oTRAIN_CACHED_NETWORKSpo) {
    trainCachedNeuralNetworks(cycles, numTraining);
  }
  else {
    trainUncachedNeuralNetworks(cycles, numTraining);
  }
}

void trainNeuralNetworkEvaluatorWrapper(Cons* arguments) {
  trainNeuralNetwork(((IntegerWrapper*)(arguments->value))->wrapperValue, ((IntegerWrapper*)(arguments->rest->value))->wrapperValue);
}

void trainUncachedNeuralNetworks(int cycles, int numTraining) {
  { double mse = 0.0;
    int numEx = oTRAINING_EXAMPLESo->length();
    OutputStream* lookPtr = NULL;
    Vector* examples = stella::newVector(numTraining);

    if (numTraining > numEx) {
      *(STANDARD_ERROR->nativeStream) << "Error: There are only " << numEx << " training examples";
      return;
    }
    shuffleList(oTRAINING_EXAMPLESo);
    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = numTraining - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        (examples->theArray)[i] = (((TrainingExample*)(oTRAINING_EXAMPLESo->nth(i))));
      }
    }
    { int cycle = NULL_INTEGER;
      int iter001 = 0;
      int upperBound001 = cycles - 1;

      for  (; iter001 <= upperBound001; 
            iter001 = iter001 + 1) {
        cycle = iter001;
        mse = 0.0;
        if ((oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_BACKPROP) ||
            (oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_BACKPROPAGATION)) {
          shuffleVector(examples);
        }
        else if (oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_QUICKPROP) {
          clearAllSlopes();
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << oNEURAL_NETWORK_TRAINING_METHODo << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
        { TrainingExample* example = NULL;
          Vector* vector000 = examples;
          int index000 = 0;
          int length000 = vector000->length();
          int k = NULL_INTEGER;
          int iter002 = 0;

          for  (; index000 < length000; 
                index000 = index000 + 1,
                iter002 = iter002 + 1) {
            example = ((TrainingExample*)((vector000->theArray)[index000]));
            k = iter002;
            if (oTRACE_NEURAL_NETWORK_TRAININGo) {
              std::cout << "Example " << k << ": " << example->query << "  " << example->score << std::endl;
            }
            if (!(!((boolean)(example->module)))) {
              example->module->changeModule();
            }
            { Cons* form = ((Cons*)(copyConsTree(example->query)));
              double target = example->score;
              QueryIterator* query = makeQuery(NIL, coerceToTree(form), NIL, NIL);
              Proposition* prop = query->baseControlFrame->proposition;
              double output = returnPartialTruth(query, true);
              double error = computeError(target, output);

              if (oTRACE_NEURAL_NETWORK_TRAININGo) {
                std::cout << "   Output: " << output << std::endl;
              }
              mse = mse + (error * error);
              oPARTIAL_SUPPORT_CACHEo = newList();
              if ((oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_BACKPROPAGATION) ||
                  (oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_BACKPROP)) {
                backpropagateError(prop, error);
              }
              else if (oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_QUICKPROP) {
                quickpropagateError(prop, error);
              }
              else {
                { OutputStringStream* stream001 = newOutputStringStream();

                  *(stream001->nativeStream) << "`" << oNEURAL_NETWORK_TRAINING_METHODo << "'" << " is not a valid case option";
                  throw *newStellaException(stream001->theStringReader());
                }
              }
            }
          }
        }
        if (oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_QUICKPROP) {
          modifyWeights();
        }
        if ((oSAVE_NETWORK_CYCLEo > 0) &&
            ((cycle % oSAVE_NETWORK_CYCLEo) == 0)) {
          saveAllNeuralNetworks(oSAVE_NETWORK_FILEo);
        }
        if ((oERROR_PRINT_CYCLEo > 0) &&
            ((cycle % oERROR_PRINT_CYCLEo) == 0)) {
          if (oSAVE_NETWORK_FILEo != NULL) {
            if (!((boolean)(lookPtr))) {
              lookPtr = newOutputFileStream(stringConcatenate(oSAVE_NETWORK_FILEo, ".err", 0));
            }
            *(lookPtr->nativeStream) << "Cycle " << cycle << " Error: " << (mse / numTraining) << std::endl;
          }
          std::cout << "Cycle " << cycle << " Error: " << (mse / numTraining) << std::endl;
        }
      }
    }
    if (((boolean)(lookPtr))) {
      lookPtr->free();
    }
  }
}

List* oPARTIAL_SUPPORT_CACHEo = NULL;

void backpropagateError(Proposition* prop, double error) {
  { PropositionNeuralNetwork* net = ((PropositionNeuralNetwork*)(dynamicSlotValue(prop->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_NEURAL_NET, NULL)));
    double output = ((FloatWrapper*)(dynamicSlotValue(prop->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue;
    int numHidden = 0;
    double delta = 0.0;
    Vector* savedInput = NULL;
    Vector* savedHidden = NULL;
    Vector* hiddenError = NULL;
    Vector* inputError = NULL;
    int numIn = 0;
    boolean recursiveConflict = false;
    double fullError = error;

    if (((boolean)(net))) {
      numIn = net->input->length();
      numHidden = net->hidden->length();
      savedInput = net->input;
      savedHidden = net->hidden;
      (net->input->theArray)[0] = (wrapFloat(1.0));
      { int i = NULL_INTEGER;
        int iter000 = 1;
        int upperBound000 = numIn - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          { double value = ((FloatWrapper*)((net->input->theArray)[i]))->wrapperValue;

            if (!(value == ((FloatWrapper*)(dynamicSlotValue(((Proposition*)((prop->arguments->theArray)[(i - 1)]))->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue)) {
              recursiveConflict = true;
              break;
            }
          }
        }
      }
      if (recursiveConflict) {
        { int i = NULL_INTEGER;
          int iter001 = 1;
          int upperBound001 = numIn - 1;

          for  (; iter001 <= upperBound001; 
                iter001 = iter001 + 1) {
            i = iter001;
            (net->input->theArray)[i] = (wrapFloat(((FloatWrapper*)(dynamicSlotValue(((Proposition*)((prop->arguments->theArray)[(i - 1)]))->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue));
          }
        }
        activatePropositionalNeuralNetwork(net);
      }
      error = error * output * (1.0 - output);
      if (recursiveConflict) {
        savedInput = stella::newVector(numIn);
        savedHidden = stella::newVector(numHidden);
        { int i = NULL_INTEGER;
          int iter002 = 0;
          int upperBound002 = numIn - 1;

          for  (; iter002 <= upperBound002; 
                iter002 = iter002 + 1) {
            i = iter002;
            (savedInput->theArray)[i] = (((FloatWrapper*)((net->input->theArray)[i])));
          }
        }
        { int i = NULL_INTEGER;
          int iter003 = 0;
          int upperBound003 = numHidden - 1;

          for  (; iter003 <= upperBound003; 
                iter003 = iter003 + 1) {
            i = iter003;
            (savedHidden->theArray)[i] = (((FloatWrapper*)((net->hidden->theArray)[i])));
          }
        }
      }
      hiddenError = stella::newVector(numHidden);
      inputError = stella::newVector(numIn);
      { int h = NULL_INTEGER;
        int iter004 = 0;
        int upperBound004 = numHidden - 1;

        for  (; iter004 <= upperBound004; 
              iter004 = iter004 + 1) {
          h = iter004;
          (hiddenError->theArray)[h] = (wrapFloat(error * ((FloatWrapper*)((net->ho->theArray)[h]))->wrapperValue));
          (hiddenError->theArray)[h] = (wrapFloat(((FloatWrapper*)((hiddenError->theArray)[h]))->wrapperValue * ((FloatWrapper*)((net->hidden->theArray)[h]))->wrapperValue * (1.0 - ((FloatWrapper*)((net->hidden->theArray)[h]))->wrapperValue)));
        }
      }
      { int i = NULL_INTEGER;
        int iter005 = 0;
        int upperBound005 = numIn - 1;

        for  (; iter005 <= upperBound005; 
              iter005 = iter005 + 1) {
          i = iter005;
          (inputError->theArray)[i] = (wrapFloat(0.0));
          { int h = NULL_INTEGER;
            int iter006 = 0;
            int upperBound006 = numHidden - 1;

            for  (; iter006 <= upperBound006; 
                  iter006 = iter006 + 1) {
              h = iter006;
              (inputError->theArray)[i] = (wrapFloat(((FloatWrapper*)((inputError->theArray)[i]))->wrapperValue + (((FloatWrapper*)((hiddenError->theArray)[h]))->wrapperValue * ((FloatWrapper*)((net->ih->theArray)[((i * net->ih->nofColumns) + h)]))->wrapperValue)));
            }
          }
        }
      }
    }
    { Keyword* testValue000 = prop->kind;

      if ((testValue000 == KWD_NEURAL_NETWORK_AND) ||
          (testValue000 == KWD_NEURAL_NETWORK_OR)) {
        { Proposition* child = NULL;
          Vector* vector000 = ((Vector*)(prop->arguments));
          int index000 = 0;
          int length000 = vector000->length();
          int i = NULL_INTEGER;
          int iter007 = 1;
          int upperBound007 = numIn - 1;

          for  (; (index000 < length000) &&
                    (iter007 <= upperBound007); 
                index000 = index000 + 1,
                iter007 = iter007 + 1) {
            child = ((Proposition*)((vector000->theArray)[index000]));
            i = iter007;
            backpropagateError(child, ((FloatWrapper*)((inputError->theArray)[i]))->wrapperValue);
          }
        }
        { int h = NULL_INTEGER;
          int iter008 = 0;
          int upperBound008 = numHidden - 1;

          for  (; iter008 <= upperBound008; 
                iter008 = iter008 + 1) {
            h = iter008;
            delta = (oMOMENTUM_TERMo * ((FloatWrapper*)((net->hoDelta->theArray)[h]))->wrapperValue) + (oLEARNING_RATEo * error * ((FloatWrapper*)((savedHidden->theArray)[h]))->wrapperValue);
            (net->ho->theArray)[h] = (wrapFloat(((FloatWrapper*)((net->ho->theArray)[h]))->wrapperValue + delta));
            (net->hoDelta->theArray)[h] = (wrapFloat(delta));
          }
        }
        { int i = NULL_INTEGER;
          int iter009 = 0;
          int upperBound009 = numIn - 1;

          for  (; iter009 <= upperBound009; 
                iter009 = iter009 + 1) {
            i = iter009;
            { int h = NULL_INTEGER;
              int iter010 = 0;
              int upperBound010 = numHidden - 1;

              for  (; iter010 <= upperBound010; 
                    iter010 = iter010 + 1) {
                h = iter010;
                delta = (oMOMENTUM_TERMo * ((FloatWrapper*)((net->ihDelta->theArray)[((i * net->ihDelta->nofColumns) + h)]))->wrapperValue) + (oLEARNING_RATEo * ((FloatWrapper*)((hiddenError->theArray)[h]))->wrapperValue * ((FloatWrapper*)((savedInput->theArray)[i]))->wrapperValue);
                (net->ih->theArray)[((i * net->ih->nofColumns) + h)] = (wrapFloat(((FloatWrapper*)((net->ih->theArray)[((i * net->ih->nofColumns) + h)]))->wrapperValue + delta));
                (net->ihDelta->theArray)[((i * net->ihDelta->nofColumns) + h)] = (wrapFloat(delta));
              }
            }
          }
        }
      }
      else {
        if (!(prop->support_reader() == NIL)) {
          { Cons* proofs = prop->support_reader();
            Cons* guilty = NIL;

            if (oRULE_COMBINATIONo == KWD_NEURAL_NETWORK_MAX) {
              guilty = consList(1, ((PartialSupport*)(proofs->value)));
              { PartialSupport* proof = NULL;
                Cons* iter011 = proofs->rest;

                for (; !(iter011 == NIL); iter011 = iter011->rest) {
                  proof = ((PartialSupport*)(iter011->value));
                  if (proof->score == output) {
                    guilty = consList(1, proof);
                  }
                }
              }
            }
            else if (oRULE_COMBINATIONo == KWD_NEURAL_NETWORK_NOISY_OR) {
              guilty = proofs;
            }
            else {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "`" << oRULE_COMBINATIONo << "'" << " is not a valid case option";
                throw *newStellaException(stream000->theStringReader());
              }
            }
            { PartialSupport* proof = NULL;
              Cons* iter012 = guilty;

              for (; !(iter012 == NIL); iter012 = iter012->rest) {
                proof = ((PartialSupport*)(iter012->value));
                if (!oPARTIAL_SUPPORT_CACHEo->memberP(wrapInteger(proof->id))) {
                  { Proposition* fact = proof->fact;

                    if (proof->argumentScores->length() == 1) {
                      setDynamicSlotValue(fact->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, wrapFloat(((FloatWrapper*)(proof->argumentScores->value))->wrapperValue), NULL_FLOAT_WRAPPER);
                    }
                    else {
                      { FloatWrapper* score = NULL;
                        Cons* iter013 = proof->argumentScores;
                        Object* arg = NULL;
                        Vector* vector001 = fact->arguments;
                        int index001 = 0;
                        int length001 = vector001->length();

                        for  (; (!(iter013 == NIL)) &&
                                  (index001 < length001); 
                              iter013 = iter013->rest,
                              index001 = index001 + 1) {
                          score = ((FloatWrapper*)(iter013->value));
                          arg = (vector001->theArray)[index001];
                          setDynamicSlotValue(((Proposition*)(arg))->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, wrapFloat(score->wrapperValue), NULL_FLOAT_WRAPPER);
                        }
                      }
                    }
                    oPARTIAL_SUPPORT_CACHEo->push(wrapInteger(proof->id));
                    backpropagateError(proof->fact, fullError * proof->score);
                    oPARTIAL_SUPPORT_CACHEo->pop();
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

void quickpropagateError(Proposition* prop, double error) {
  { PropositionNeuralNetwork* net = ((PropositionNeuralNetwork*)(dynamicSlotValue(prop->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_NEURAL_NET, NULL)));
    double output = ((FloatWrapper*)(dynamicSlotValue(prop->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue;
    double fullError = error;
    double temp = 0.0;
    int numIn = 0;
    int numHidden = 0;
    Vector* inputError = NULL;

    if (((boolean)(net))) {
      numIn = net->input->length();
      numHidden = net->hidden->length();
      (net->input->theArray)[0] = (wrapFloat(1.0));
      { int i = NULL_INTEGER;
        int iter000 = 1;
        int upperBound000 = numIn - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          (net->input->theArray)[i] = (wrapFloat(((FloatWrapper*)(dynamicSlotValue(((Proposition*)((prop->arguments->theArray)[(i - 1)]))->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue));
        }
      }
      activatePropositionalNeuralNetwork(net);
      error = error * (oSIGMOID_PRIME_OFFSETo + (output * (1.0 - output)));
      inputError = stella::newVector(numIn);
      zeroVector(inputError);
      { int h = NULL_INTEGER;
        int iter001 = 0;
        int upperBound001 = numHidden - 1;

        for  (; iter001 <= upperBound001; 
              iter001 = iter001 + 1) {
          h = iter001;
          (net->hoSlope->theArray)[h] = (wrapFloat(((FloatWrapper*)((net->hoSlope->theArray)[h]))->wrapperValue + (error * ((FloatWrapper*)((net->hidden->theArray)[h]))->wrapperValue)));
          temp = error * ((FloatWrapper*)((net->ho->theArray)[h]))->wrapperValue * (oSIGMOID_PRIME_OFFSETo + (((FloatWrapper*)((net->hidden->theArray)[h]))->wrapperValue * (1.0 - ((FloatWrapper*)((net->hidden->theArray)[h]))->wrapperValue)));
          { int i = NULL_INTEGER;
            int iter002 = 0;
            int upperBound002 = numIn - 1;

            for  (; iter002 <= upperBound002; 
                  iter002 = iter002 + 1) {
              i = iter002;
              (net->ihSlope->theArray)[((i * net->ihSlope->nofColumns) + h)] = (wrapFloat(((FloatWrapper*)((net->ihSlope->theArray)[((i * net->ihSlope->nofColumns) + h)]))->wrapperValue + (temp * ((FloatWrapper*)((net->input->theArray)[i]))->wrapperValue)));
              (inputError->theArray)[i] = (wrapFloat(((FloatWrapper*)((inputError->theArray)[i]))->wrapperValue + (temp * ((FloatWrapper*)((net->ih->theArray)[((i * net->ih->nofColumns) + h)]))->wrapperValue)));
            }
          }
        }
      }
    }
    { Keyword* testValue000 = prop->kind;

      if ((testValue000 == KWD_NEURAL_NETWORK_AND) ||
          (testValue000 == KWD_NEURAL_NETWORK_OR)) {
        { Proposition* child = NULL;
          Vector* vector000 = ((Vector*)(prop->arguments));
          int index000 = 0;
          int length000 = vector000->length();
          int i = NULL_INTEGER;
          int iter003 = 1;
          int upperBound003 = numIn - 1;

          for  (; (index000 < length000) &&
                    (iter003 <= upperBound003); 
                index000 = index000 + 1,
                iter003 = iter003 + 1) {
            child = ((Proposition*)((vector000->theArray)[index000]));
            i = iter003;
            quickpropagateError(child, ((FloatWrapper*)((inputError->theArray)[i]))->wrapperValue);
          }
        }
      }
      else {
        if (!(prop->support_reader() == NIL)) {
          { Cons* proofs = prop->support_reader();
            Cons* guilty = NIL;

            if (oRULE_COMBINATIONo == KWD_NEURAL_NETWORK_MAX) {
              guilty = consList(1, ((PartialSupport*)(proofs->value)));
              { PartialSupport* proof = NULL;
                Cons* iter004 = proofs->rest;

                for (; !(iter004 == NIL); iter004 = iter004->rest) {
                  proof = ((PartialSupport*)(iter004->value));
                  if (proof->score == output) {
                    guilty = consList(1, proof);
                  }
                }
              }
            }
            else if (oRULE_COMBINATIONo == KWD_NEURAL_NETWORK_NOISY_OR) {
              guilty = proofs;
            }
            else {
              { OutputStringStream* stream000 = newOutputStringStream();

                *(stream000->nativeStream) << "`" << oRULE_COMBINATIONo << "'" << " is not a valid case option";
                throw *newStellaException(stream000->theStringReader());
              }
            }
            { PartialSupport* proof = NULL;
              Cons* iter005 = guilty;

              for (; !(iter005 == NIL); iter005 = iter005->rest) {
                proof = ((PartialSupport*)(iter005->value));
                if (!oPARTIAL_SUPPORT_CACHEo->memberP(wrapInteger(proof->id))) {
                  { Proposition* fact = proof->fact;

                    if (proof->argumentScores->length() == 1) {
                      setDynamicSlotValue(fact->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, wrapFloat(((FloatWrapper*)(proof->argumentScores->value))->wrapperValue), NULL_FLOAT_WRAPPER);
                    }
                    else {
                      { FloatWrapper* score = NULL;
                        Cons* iter006 = proof->argumentScores;
                        Object* arg = NULL;
                        Vector* vector001 = fact->arguments;
                        int index001 = 0;
                        int length001 = vector001->length();

                        for  (; (!(iter006 == NIL)) &&
                                  (index001 < length001); 
                              iter006 = iter006->rest,
                              index001 = index001 + 1) {
                          score = ((FloatWrapper*)(iter006->value));
                          arg = (vector001->theArray)[index001];
                          setDynamicSlotValue(((Proposition*)(arg))->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, wrapFloat(score->wrapperValue), NULL_FLOAT_WRAPPER);
                        }
                      }
                    }
                    oPARTIAL_SUPPORT_CACHEo->push(wrapInteger(proof->id));
                    quickpropagateError(proof->fact, fullError * proof->score);
                    oPARTIAL_SUPPORT_CACHEo->pop();
                  }
                }
              }
            }
          }
        }
      }
    }
  }
}

double computeError(double training, double output) {
  if (training == 1.0) {
    if (output > 0.9) {
      return (0.0);
    }
  }
  else if (training == 0.0) {
    if (output < 0.1) {
      return (0.0);
    }
  }
  else {
  }
  return (training - output);
}

double computeDelta(double slope, double prevSlope, double prevDelta) {
  prevSlope = prevSlope;
  return ((oLEARNING_RATEo * slope) + (oMOMENTUM_TERMo * prevDelta));
}

double computeQpDelta(double slope, double prevSlope, double prevDelta) {
  { double delta = 0.0;

    if (prevDelta > oMODE_SWITCHo) {
      if (slope > 0.0) {
        delta = oLEARNING_RATEo * slope;
      }
      if (slope > (oSHRINK_FACTORo * prevSlope)) {
        delta = delta + (oMAX_MOVEMENTo * prevDelta);
      }
      else {
        delta = delta + ((slope / (prevSlope - slope)) * prevDelta);
      }
    }
    else if (prevDelta < (0.0 - oMODE_SWITCHo)) {
      if (slope < 0.0) {
        delta = oLEARNING_RATEo * slope;
      }
      if (slope < (oSHRINK_FACTORo * prevSlope)) {
        delta = delta + (oMAX_MOVEMENTo * prevDelta);
      }
      else {
        delta = delta + ((slope / (prevSlope - slope)) * prevDelta);
      }
    }
    else {
      delta = (oLEARNING_RATEo * slope) + (oMOMENTUM_TERMo * prevDelta);
    }
    return (delta);
  }
}

void modifyWeights() {
  { double delta = 0.0;
    int numIn = 0;
    int numHidden = 0;

    { PropositionNeuralNetwork* net = NULL;
      Cons* iter000 = oMASTER_NEURAL_NETWORK_LISTo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        net = ((PropositionNeuralNetwork*)(iter000->value));
        numIn = net->input->length();
        numHidden = net->hidden->length();
        { int h = NULL_INTEGER;
          int iter001 = 0;
          int upperBound000 = numHidden - 1;

          for  (; iter001 <= upperBound000; 
                iter001 = iter001 + 1) {
            h = iter001;
            delta = computeQpDelta(((FloatWrapper*)((net->hoSlope->theArray)[h]))->wrapperValue, ((FloatWrapper*)((net->hoPrevSlope->theArray)[h]))->wrapperValue, ((FloatWrapper*)((net->hoDelta->theArray)[h]))->wrapperValue);
            (net->ho->theArray)[h] = (wrapFloat(((FloatWrapper*)((net->ho->theArray)[h]))->wrapperValue + delta));
            (net->hoDelta->theArray)[h] = (wrapFloat(delta));
          }
        }
        { int i = NULL_INTEGER;
          int iter002 = 0;
          int upperBound001 = numIn - 1;

          for  (; iter002 <= upperBound001; 
                iter002 = iter002 + 1) {
            i = iter002;
            { int h = NULL_INTEGER;
              int iter003 = 0;
              int upperBound002 = numHidden - 1;

              for  (; iter003 <= upperBound002; 
                    iter003 = iter003 + 1) {
                h = iter003;
                delta = computeQpDelta(((FloatWrapper*)((net->ihSlope->theArray)[((i * net->ihSlope->nofColumns) + h)]))->wrapperValue, ((FloatWrapper*)((net->ihPrevSlope->theArray)[((i * net->ihPrevSlope->nofColumns) + h)]))->wrapperValue, ((FloatWrapper*)((net->ihDelta->theArray)[((i * net->ihDelta->nofColumns) + h)]))->wrapperValue);
                (net->ih->theArray)[((i * net->ih->nofColumns) + h)] = (wrapFloat(((FloatWrapper*)((net->ih->theArray)[((i * net->ih->nofColumns) + h)]))->wrapperValue + delta));
                (net->ihDelta->theArray)[((i * net->ihDelta->nofColumns) + h)] = (wrapFloat(delta));
              }
            }
          }
        }
      }
    }
  }
}

double testOverTrainingExamples() {
  { double mse = 0.0;
    double error = 0.0;
    double output = 0.0;
    Cons* form = NIL;
    QueryIterator* query = NULL;

    { TrainingExample* example = NULL;
      Cons* iter000 = oTRAINING_EXAMPLESo->theConsList;
      int i = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        example = ((TrainingExample*)(iter000->value));
        i = iter001;
        if (!(!((boolean)(example->module)))) {
          example->module->changeModule();
        }
        form = ((Cons*)(copyConsTree(example->query)));
        query = makeQuery(NIL, coerceToTree(form), NIL, NIL);
        output = returnPartialTruth(query, true);
        std::cout << "Example " << i << ": " << example->query->rest->value << ", " << output << "  Target: " << example->score << std::endl;
        error = example->score - output;
        mse = mse + (error * error);
      }
    }
    return (mse);
  }
}

FloatWrapper* testOverTrainingExamplesEvaluatorWrapper(Cons* arguments) {
  arguments = arguments;
  { double result = testOverTrainingExamples();

    if (result != NULL_FLOAT) {
      return (wrapFloat(result));
    }
    else {
      return (NULL);
    }
  }
}

double trainAndTestNeuralNetwork(int cycles, int numTraining, int numTesting) {
  trainNeuralNetwork(cycles, numTraining);
  { double mse = 0.0;
    Vector* testingExamples = stella::newVector(numTesting);

    { int i = NULL_INTEGER;
      int iter000 = numTraining;
      int upperBound000 = numTraining + (numTesting - 1);

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        (testingExamples->theArray)[(i - numTraining)] = (((TrainingExample*)(oTRAINING_EXAMPLESo->nth(i))));
      }
    }
    { TrainingExample* example = NULL;
      Vector* vector000 = testingExamples;
      int index000 = 0;
      int length000 = vector000->length();

      for  (; index000 < length000; 
            index000 = index000 + 1) {
        example = ((TrainingExample*)((vector000->theArray)[index000]));
        if (!(!((boolean)(example->module)))) {
          example->module->changeModule();
        }
        { Cons* form = ((Cons*)(copyConsTree(example->query)));
          QueryIterator* query = makeQuery(NIL, coerceToTree(form), NIL, NIL);
          double output = returnPartialTruth(query, true);
          double error = example->score - output;

          mse = mse + (error * error);
        }
      }
    }
    mse = mse / numTesting;
    return (mse);
  }
}

FloatWrapper* trainAndTestNeuralNetworkEvaluatorWrapper(Cons* arguments) {
  { double result = trainAndTestNeuralNetwork(((IntegerWrapper*)(arguments->value))->wrapperValue, ((IntegerWrapper*)(arguments->rest->value))->wrapperValue, ((IntegerWrapper*)(arguments->rest->rest->value))->wrapperValue);

    if (result != NULL_FLOAT) {
      return (wrapFloat(result));
    }
    else {
      return (NULL);
    }
  }
}

double testNeuralNetwork() {
  { double errorSum = 0.0;
    int numTesting = oTESTING_EXAMPLESo->length();

    { TrainingExample* example = NULL;
      Cons* iter000 = oTESTING_EXAMPLESo->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        example = ((TrainingExample*)(iter000->value));
        if (!(!((boolean)(example->module)))) {
          example->module->changeModule();
        }
        { Cons* form = ((Cons*)(copyConsTree(example->query)));
          QueryIterator* query = makeQuery(NIL, coerceToTree(form), NIL, NIL);
          double output = returnPartialTruth(query, true);
          double error = example->score - output;

          errorSum = errorSum + (((error < 0.0) ? (0.0 - error) : error));
        }
      }
    }
    errorSum = errorSum / numTesting;
    return (errorSum);
  }
}

FloatWrapper* testNeuralNetworkEvaluatorWrapper(Cons* arguments) {
  arguments = arguments;
  { double result = testNeuralNetwork();

    if (result != NULL_FLOAT) {
      return (wrapFloat(result));
    }
    else {
      return (NULL);
    }
  }
}

double multipleNetworkTrainingRuns(int runs, int cycles, int numTraining) {
  { Vector* errors = stella::newVector(runs);
    double sum = 0.0;

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = runs - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        clearAllNeuralNetworks();
        trainNeuralNetwork(cycles, numTraining);
        (errors->theArray)[i] = (wrapFloat(testNeuralNetwork()));
        sum = sum + ((FloatWrapper*)((errors->theArray)[i]))->wrapperValue;
        std::cout << "** Run " << i << ": " << ((FloatWrapper*)((errors->theArray)[i])) << std::endl;
      }
    }
    std::cout << std::endl << "*** Report" << std::endl;
    { int i = NULL_INTEGER;
      int iter001 = 0;
      int upperBound001 = runs - 1;

      for  (; iter001 <= upperBound001; 
            iter001 = iter001 + 1) {
        i = iter001;
        std::cout << "** Run " << i << ": " << ((FloatWrapper*)((errors->theArray)[i])) << std::endl;
      }
    }
    return (sum / runs);
  }
}

FloatWrapper* multipleNetworkTrainingRunsEvaluatorWrapper(Cons* arguments) {
  { double result = multipleNetworkTrainingRuns(((IntegerWrapper*)(arguments->value))->wrapperValue, ((IntegerWrapper*)(arguments->rest->value))->wrapperValue, ((IntegerWrapper*)(arguments->rest->rest->value))->wrapperValue);

    if (result != NULL_FLOAT) {
      return (wrapFloat(result));
    }
    else {
      return (NULL);
    }
  }
}

void trainCachedNeuralNetworks(int cycles, int numTraining) {
  { double mse = 0.0;
    double absError = 0.0;
    double error = 0.0;
    double target = 0.0;
    double output = 0.0;
    int numEx = oTRAINING_EXAMPLESo->length();
    Vector* index = stella::newVector(numTraining);
    OutputStream* lookPtr = NULL;
    Vector* examples = stella::newVector(numTraining);
    Vector* netRecords = stella::newVector(numTraining);

    if (numTraining > numEx) {
      std::cout << "Error: There are only " << numEx << " training examples";
      return;
    }
    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = numTraining - 1;
      TrainingExample* example = NULL;
      Cons* iter001 = oTRAINING_EXAMPLESo->theConsList;

      for  (; (iter000 <= upperBound000) &&
                (!(iter001 == NIL)); 
            iter000 = iter000 + 1,
            iter001 = iter001->rest) {
        i = iter000;
        example = ((TrainingExample*)(iter001->value));
        (examples->theArray)[i] = example;
        (index->theArray)[i] = (wrapInteger(i));
      }
    }
    { int i = NULL_INTEGER;
      int iter002 = 0;
      int upperBound001 = numTraining - 1;

      for  (; iter002 <= upperBound001; 
            iter002 = iter002 + 1) {
        i = iter002;
        { TrainingExample* example = ((TrainingExample*)((examples->theArray)[i]));
          int timestamp = getNowTimestamp();

          if ((!(!((boolean)(example->cachedSolution)))) &&
              (timestamp == example->timestamp)) {
            (netRecords->theArray)[i] = (((Cons*)(example->cachedSolution)));
          }
          else {
            { Module* currentModule = oMODULEo;

              if (!(!((boolean)(example->module)))) {
                example->module->changeModule();
              }
              (netRecords->theArray)[i] = (createCachedNetwork(example->query));
              example->cachedSolution = ((Cons*)((netRecords->theArray)[i]));
              example->timestamp = timestamp;
              currentModule->changeModule();
            }
          }
        }
      }
    }
    std::cout << "Training Networks" << std::endl;
    { int cycle = NULL_INTEGER;
      int iter003 = 0;
      int upperBound002 = cycles - 1;

      for  (; iter003 <= upperBound002; 
            iter003 = iter003 + 1) {
        cycle = iter003;
        mse = 0.0;
        absError = 0.0;
        if ((oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_BACKPROP) ||
            (oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_BACKPROPAGATION)) {
          shuffleVector(index);
        }
        else if (oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_QUICKPROP) {
          clearAllSlopes();
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << oNEURAL_NETWORK_TRAINING_METHODo << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
        { int k = NULL_INTEGER;
          int iter004 = 0;
          int upperBound003 = numTraining - 1;

          for  (; iter004 <= upperBound003; 
                iter004 = iter004 + 1) {
            k = iter004;
            if (oTRACE_NEURAL_NETWORK_TRAININGo) {
              std::cout << "Example " << k << ": " << ((TrainingExample*)((examples->theArray)[(((IntegerWrapper*)((index->theArray)[k]))->wrapperValue)]))->query << "  " << ((TrainingExample*)((examples->theArray)[(((IntegerWrapper*)((index->theArray)[k]))->wrapperValue)]))->score << std::endl;
            }
            target = ((TrainingExample*)((examples->theArray)[(((IntegerWrapper*)((index->theArray)[k]))->wrapperValue)]))->score;
            output = activateCachedNetwork(((Cons*)((netRecords->theArray)[(((IntegerWrapper*)((index->theArray)[k]))->wrapperValue)])));
            error = computeError(target, output);
            if (oTRACE_NEURAL_NETWORK_TRAININGo) {
              std::cout << "   Output: " << output << std::endl;
            }
            absError = absError + (((error < 0.0) ? (0.0 - error) : error));
            mse = mse + (error * error);
            if ((oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_BACKPROPAGATION) ||
                (oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_BACKPROP)) {
              cachedBackpropagateError(((Cons*)((netRecords->theArray)[(((IntegerWrapper*)((index->theArray)[k]))->wrapperValue)])), error);
            }
            else if (oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_QUICKPROP) {
              cachedQuickpropagateError(((Cons*)((netRecords->theArray)[(((IntegerWrapper*)((index->theArray)[k]))->wrapperValue)])), error);
            }
            else {
              { OutputStringStream* stream001 = newOutputStringStream();

                *(stream001->nativeStream) << "`" << oNEURAL_NETWORK_TRAINING_METHODo << "'" << " is not a valid case option";
                throw *newStellaException(stream001->theStringReader());
              }
            }
          }
        }
        if (oNEURAL_NETWORK_TRAINING_METHODo == KWD_NEURAL_NETWORK_QUICKPROP) {
          modifyWeights();
        }
        if ((oSAVE_NETWORK_CYCLEo > 0) &&
            ((cycle % oSAVE_NETWORK_CYCLEo) == 0)) {
          std::cout << "Saving networks" << std::endl;
          saveAllNeuralNetworks(oSAVE_NETWORK_FILEo);
        }
        if ((oERROR_PRINT_CYCLEo > 0) &&
            ((cycle % oERROR_PRINT_CYCLEo) == 0)) {
          if (oSAVE_NETWORK_FILEo != NULL) {
            if (!((boolean)(lookPtr))) {
              lookPtr = newOutputFileStream(stringConcatenate(oSAVE_NETWORK_FILEo, ".err", 0));
            }
            *(lookPtr->nativeStream) << "Cycle " << cycle << " Error: " << (absError / numTraining) << std::endl;
          }
          std::cout << "Cycle " << cycle << " Error: " << (absError / numTraining) << std::endl;
        }
        if ((mse / numTraining) < oERROR_CUTOFFo) {
          break;
        }
      }
    }
    if (((boolean)(lookPtr))) {
      lookPtr->free();
    }
  }
}

Vector* oLEARNING_CURVEo = NULL;

void cachedBackpropagateError(Cons* tree, double error) {
  { PropositionNeuralNetwork* net = NULL;
    double temp = 0.0;
    double delta = 0.0;
    Vector* input = NULL;
    Vector* hidden = NULL;
    Vector* hiddenError = NULL;
    Vector* inputError = NULL;
    boolean recursiveConflictP = false;

    if (isaP(tree->value, SGT_NEURAL_NETWORK_STELLA_CONS)) {
      if (oRULE_COMBINATIONo == KWD_NEURAL_NETWORK_MAX) {
        { double max = 0.0;
          Cons* guilty = NIL;

          { Object* netDef = NULL;
            Cons* iter000 = tree;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              netDef = iter000->value;
              net = ((PropositionNeuralNetwork*)(((Cons*)(netDef))->value));
              if (net->output > max) {
                max = net->output;
                guilty = ((Cons*)(netDef));
              }
            }
          }
          cachedBackpropagateError(guilty, error);
        }
      }
      else if (oRULE_COMBINATIONo == KWD_NEURAL_NETWORK_NOISY_OR) {
        { Object* netDef = NULL;
          Cons* iter001 = tree;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            netDef = iter001->value;
            cachedBackpropagateError(((Cons*)(netDef)), error * ((PropositionNeuralNetwork*)(((Cons*)(netDef))->value))->output);
          }
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << oRULE_COMBINATIONo << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      return;
    }
    net = ((PropositionNeuralNetwork*)(tree->value));
    input = net->input;
    hidden = net->hidden;
    inputError = net->inputError;
    hiddenError = net->hiddenError;
    error = error * net->output * (1.0 - net->output);
    { int i = NULL_INTEGER;
      int iter002 = 1;
      int upperBound000 = net->input->length() - 1;
      Object* ele = NULL;
      Cons* iter003 = tree->rest;

      for  (; (iter002 <= upperBound000) &&
                (!(iter003 == NIL)); 
            iter002 = iter002 + 1,
            iter003 = iter003->rest) {
        i = iter002;
        ele = iter003->value;
        { Surrogate* testValue000 = safePrimaryType(ele);

          if (testValue000 == SGT_NEURAL_NETWORK_STELLA_CONS) {
            { Object* ele000 = ele;
              Cons* ele = ((Cons*)(ele000));

              if (ele->length() == 1) {
                temp = ((PropositionNeuralNetwork*)(((Cons*)(ele->value))->value))->output;
              }
              else {
                if (oRULE_COMBINATIONo == KWD_NEURAL_NETWORK_MAX) {
                  temp = 0.0;
                  { Object* netDef = NULL;
                    Cons* iter004 = ele;

                    for (; !(iter004 == NIL); iter004 = iter004->rest) {
                      netDef = iter004->value;
                      if (((PropositionNeuralNetwork*)(((Cons*)(netDef))->value))->output > temp) {
                        temp = net->output;
                      }
                    }
                  }
                }
                else if (oRULE_COMBINATIONo == KWD_NEURAL_NETWORK_NOISY_OR) {
                  { Cons* scores = NIL;

                    { Object* netDef = NULL;
                      Cons* iter005 = ele;
                      Cons* collect000 = NULL;

                      for  (; !(iter005 == NIL); 
                            iter005 = iter005->rest) {
                        netDef = iter005->value;
                        if (!((boolean)(collect000))) {
                          {
                            collect000 = cons(wrapFloat(((PropositionNeuralNetwork*)(((Cons*)(netDef))->value))->output), NIL);
                            if (scores == NIL) {
                              scores = collect000;
                            }
                            else {
                              addConsToEndOfConsList(scores, collect000);
                            }
                          }
                        }
                        else {
                          {
                            collect000->rest = cons(wrapFloat(((PropositionNeuralNetwork*)(((Cons*)(netDef))->value))->output), NIL);
                            collect000 = collect000->rest;
                          }
                        }
                      }
                    }
                    temp = probabilisticSumN(scores);
                  }
                }
                else {
                  { OutputStringStream* stream001 = newOutputStringStream();

                    *(stream001->nativeStream) << "`" << oRULE_COMBINATIONo << "'" << " is not a valid case option";
                    throw *newStellaException(stream001->theStringReader());
                  }
                }
              }
            }
          }
          else if (subtypeOfFloatP(testValue000)) {
            { Object* ele001 = ele;
              FloatWrapper* ele = ((FloatWrapper*)(ele001));

              temp = ele->wrapperValue;
            }
          }
          else {
            { OutputStringStream* stream002 = newOutputStringStream();

              *(stream002->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
              throw *newStellaException(stream002->theStringReader());
            }
          }
        }
        { double value = ((FloatWrapper*)((net->input->theArray)[i]))->wrapperValue;

          if (!(value == temp)) {
            recursiveConflictP = true;
            break;
          }
        }
      }
    }
    if (recursiveConflictP) {
      activateCachedNetwork(consList(1, tree));
      hidden = stella::newVector(net->hidden->length());
      hiddenError = stella::newVector(net->hidden->length());
      input = stella::newVector(net->input->length());
      { int i = NULL_INTEGER;
        int iter006 = 0;
        int upperBound001 = input->length() - 1;

        for  (; iter006 <= upperBound001; 
              iter006 = iter006 + 1) {
          i = iter006;
          (input->theArray)[i] = (((FloatWrapper*)((net->input->theArray)[i])));
        }
      }
      { int h = NULL_INTEGER;
        int iter007 = 0;
        int upperBound002 = hidden->length() - 1;

        for  (; iter007 <= upperBound002; 
              iter007 = iter007 + 1) {
          h = iter007;
          (hidden->theArray)[h] = (((FloatWrapper*)((net->hidden->theArray)[h])));
        }
      }
    }
    { int h = NULL_INTEGER;
      int iter008 = 0;
      int upperBound003 = hidden->length() - 1;

      for  (; iter008 <= upperBound003; 
            iter008 = iter008 + 1) {
        h = iter008;
        (hiddenError->theArray)[h] = (wrapFloat(error * ((FloatWrapper*)((net->ho->theArray)[h]))->wrapperValue));
        (hiddenError->theArray)[h] = (wrapFloat(((FloatWrapper*)((hiddenError->theArray)[h]))->wrapperValue * ((FloatWrapper*)((hidden->theArray)[h]))->wrapperValue * (1.0 - ((FloatWrapper*)((hidden->theArray)[h]))->wrapperValue)));
      }
    }
    { int i = NULL_INTEGER;
      int iter009 = 0;
      int upperBound004 = input->length() - 1;

      for  (; iter009 <= upperBound004; 
            iter009 = iter009 + 1) {
        i = iter009;
        (inputError->theArray)[i] = (wrapFloat(0.0));
        { int h = NULL_INTEGER;
          int iter010 = 0;
          int upperBound005 = hidden->length() - 1;

          for  (; iter010 <= upperBound005; 
                iter010 = iter010 + 1) {
            h = iter010;
            (inputError->theArray)[i] = (wrapFloat(((FloatWrapper*)((inputError->theArray)[i]))->wrapperValue + (((FloatWrapper*)((hiddenError->theArray)[h]))->wrapperValue * ((FloatWrapper*)((net->ih->theArray)[((i * net->ih->nofColumns) + h)]))->wrapperValue)));
          }
        }
      }
    }
    { Object* input = NULL;
      Cons* iter011 = tree->rest;
      int i = NULL_INTEGER;
      int iter012 = 1;

      for  (; !(iter011 == NIL); 
            iter011 = iter011->rest,
            iter012 = iter012 + 1) {
        input = iter011->value;
        i = iter012;
        if (isaP(input, SGT_NEURAL_NETWORK_STELLA_CONS)) {
          cachedBackpropagateError(((Cons*)(input)), ((FloatWrapper*)((inputError->theArray)[i]))->wrapperValue);
        }
      }
    }
    { int h = NULL_INTEGER;
      int iter013 = 0;
      int upperBound006 = hidden->length() - 1;

      for  (; iter013 <= upperBound006; 
            iter013 = iter013 + 1) {
        h = iter013;
        delta = (oMOMENTUM_TERMo * ((FloatWrapper*)((net->hoDelta->theArray)[h]))->wrapperValue) + (oLEARNING_RATEo * error * ((FloatWrapper*)((hidden->theArray)[h]))->wrapperValue);
        (net->ho->theArray)[h] = (wrapFloat(((FloatWrapper*)((net->ho->theArray)[h]))->wrapperValue + delta));
        (net->hoDelta->theArray)[h] = (wrapFloat(delta));
        { int i = NULL_INTEGER;
          int iter014 = 0;
          int upperBound007 = input->length() - 1;

          for  (; iter014 <= upperBound007; 
                iter014 = iter014 + 1) {
            i = iter014;
            delta = (oMOMENTUM_TERMo * ((FloatWrapper*)((net->ihDelta->theArray)[((i * net->ihDelta->nofColumns) + h)]))->wrapperValue) + (oLEARNING_RATEo * ((FloatWrapper*)((hiddenError->theArray)[h]))->wrapperValue * ((FloatWrapper*)((input->theArray)[i]))->wrapperValue);
            (net->ih->theArray)[((i * net->ih->nofColumns) + h)] = (wrapFloat(((FloatWrapper*)((net->ih->theArray)[((i * net->ih->nofColumns) + h)]))->wrapperValue + delta));
            (net->ihDelta->theArray)[((i * net->ihDelta->nofColumns) + h)] = (wrapFloat(delta));
          }
        }
      }
    }
  }
}

void cachedQuickpropagateError(Cons* tree, double error) {
  { PropositionNeuralNetwork* net = NULL;
    double temp = 0.0;
    Vector* input = NULL;
    Vector* hidden = NULL;
    Vector* inputError = NULL;
    boolean recursiveConflictP = false;

    if (isaP(tree->value, SGT_NEURAL_NETWORK_STELLA_CONS)) {
      if (oRULE_COMBINATIONo == KWD_NEURAL_NETWORK_MAX) {
        { double max = 0.0;
          Cons* guilty = NIL;

          { Object* netDef = NULL;
            Cons* iter000 = tree;

            for (; !(iter000 == NIL); iter000 = iter000->rest) {
              netDef = iter000->value;
              net = ((PropositionNeuralNetwork*)(((Cons*)(netDef))->value));
              if (net->output > max) {
                max = net->output;
                guilty = ((Cons*)(netDef));
              }
            }
          }
          cachedQuickpropagateError(guilty, error);
        }
      }
      else if (oRULE_COMBINATIONo == KWD_NEURAL_NETWORK_NOISY_OR) {
        { Object* netDef = NULL;
          Cons* iter001 = tree;

          for (; !(iter001 == NIL); iter001 = iter001->rest) {
            netDef = iter001->value;
            cachedQuickpropagateError(((Cons*)(netDef)), error * ((PropositionNeuralNetwork*)(((Cons*)(netDef))->value))->output);
          }
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << oRULE_COMBINATIONo << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
      return;
    }
    net = ((PropositionNeuralNetwork*)(tree->value));
    input = net->input;
    hidden = net->hidden;
    inputError = net->inputError;
    error = error * (oSIGMOID_PRIME_OFFSETo + (net->output * (1.0 - net->output)));
    { int i = NULL_INTEGER;
      int iter002 = 1;
      int upperBound000 = net->input->length() - 1;
      Object* ele = NULL;
      Cons* iter003 = tree->rest;

      for  (; (iter002 <= upperBound000) &&
                (!(iter003 == NIL)); 
            iter002 = iter002 + 1,
            iter003 = iter003->rest) {
        i = iter002;
        ele = iter003->value;
        { Surrogate* testValue000 = safePrimaryType(ele);

          if (testValue000 == SGT_NEURAL_NETWORK_STELLA_CONS) {
            { Object* ele000 = ele;
              Cons* ele = ((Cons*)(ele000));

              if (ele->length() == 1) {
                temp = ((PropositionNeuralNetwork*)(((Cons*)(ele->value))->value))->output;
              }
              else {
                if (oRULE_COMBINATIONo == KWD_NEURAL_NETWORK_MAX) {
                  temp = 0.0;
                  { Object* netDef = NULL;
                    Cons* iter004 = ele;

                    for (; !(iter004 == NIL); iter004 = iter004->rest) {
                      netDef = iter004->value;
                      if (((PropositionNeuralNetwork*)(((Cons*)(netDef))->value))->output > temp) {
                        temp = net->output;
                      }
                    }
                  }
                }
                else if (oRULE_COMBINATIONo == KWD_NEURAL_NETWORK_NOISY_OR) {
                  { Cons* scores = NIL;

                    { Object* netDef = NULL;
                      Cons* iter005 = ele;
                      Cons* collect000 = NULL;

                      for  (; !(iter005 == NIL); 
                            iter005 = iter005->rest) {
                        netDef = iter005->value;
                        if (!((boolean)(collect000))) {
                          {
                            collect000 = cons(wrapFloat(((PropositionNeuralNetwork*)(((Cons*)(netDef))->value))->output), NIL);
                            if (scores == NIL) {
                              scores = collect000;
                            }
                            else {
                              addConsToEndOfConsList(scores, collect000);
                            }
                          }
                        }
                        else {
                          {
                            collect000->rest = cons(wrapFloat(((PropositionNeuralNetwork*)(((Cons*)(netDef))->value))->output), NIL);
                            collect000 = collect000->rest;
                          }
                        }
                      }
                    }
                    temp = probabilisticSumN(scores);
                  }
                }
                else {
                  { OutputStringStream* stream001 = newOutputStringStream();

                    *(stream001->nativeStream) << "`" << oRULE_COMBINATIONo << "'" << " is not a valid case option";
                    throw *newStellaException(stream001->theStringReader());
                  }
                }
              }
            }
          }
          else if (subtypeOfFloatP(testValue000)) {
            { Object* ele001 = ele;
              FloatWrapper* ele = ((FloatWrapper*)(ele001));

              temp = ele->wrapperValue;
            }
          }
          else {
            { OutputStringStream* stream002 = newOutputStringStream();

              *(stream002->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
              throw *newStellaException(stream002->theStringReader());
            }
          }
        }
        { double value = ((FloatWrapper*)((net->input->theArray)[i]))->wrapperValue;

          if (!(value == temp)) {
            recursiveConflictP = true;
            break;
          }
        }
      }
    }
    if (recursiveConflictP) {
      activateCachedNetwork(consList(1, tree));
    }
    zeroVector(inputError);
    { int h = NULL_INTEGER;
      int iter006 = 0;
      int upperBound001 = hidden->length() - 1;

      for  (; iter006 <= upperBound001; 
            iter006 = iter006 + 1) {
        h = iter006;
        (net->hoSlope->theArray)[h] = (wrapFloat(((FloatWrapper*)((net->hoSlope->theArray)[h]))->wrapperValue + (error * ((FloatWrapper*)((hidden->theArray)[h]))->wrapperValue)));
        temp = error * ((FloatWrapper*)((net->ho->theArray)[h]))->wrapperValue * (oSIGMOID_PRIME_OFFSETo + (((FloatWrapper*)((hidden->theArray)[h]))->wrapperValue * (1.0 - ((FloatWrapper*)((hidden->theArray)[h]))->wrapperValue)));
        { int i = NULL_INTEGER;
          int iter007 = 0;
          int upperBound002 = input->length() - 1;

          for  (; iter007 <= upperBound002; 
                iter007 = iter007 + 1) {
            i = iter007;
            (net->ihSlope->theArray)[((i * net->ihSlope->nofColumns) + h)] = (wrapFloat(((FloatWrapper*)((net->ihSlope->theArray)[((i * net->ihSlope->nofColumns) + h)]))->wrapperValue + (temp * ((FloatWrapper*)((input->theArray)[i]))->wrapperValue)));
            (inputError->theArray)[i] = (wrapFloat(((FloatWrapper*)((inputError->theArray)[i]))->wrapperValue + (temp * ((FloatWrapper*)((net->ih->theArray)[((i * net->ih->nofColumns) + h)]))->wrapperValue)));
          }
        }
      }
    }
    { Object* input = NULL;
      Cons* iter008 = tree->rest;
      int i = NULL_INTEGER;
      int iter009 = 1;

      for  (; !(iter008 == NIL); 
            iter008 = iter008->rest,
            iter009 = iter009 + 1) {
        input = iter008->value;
        i = iter009;
        if (isaP(input, SGT_NEURAL_NETWORK_STELLA_CONS)) {
          cachedQuickpropagateError(((Cons*)(input)), ((FloatWrapper*)((inputError->theArray)[i]))->wrapperValue);
        }
      }
    }
  }
}

Cons* createCachedNetwork(Cons* consQuery) {
  { QueryIterator* query = makeQuery(NIL, coerceToTree(((Cons*)(copyConsTree(consQuery)))), NIL, NIL);
    double score = returnPartialTruth(query, true);
    Object* tree = buildNetworkTree(query->baseControlFrame->proposition, NIL);

    score = score;
    if (isaP(tree, SGT_NEURAL_NETWORK_STELLA_CONS)) {
      return (((Cons*)(tree)));
    }
    return (NIL);
  }
}

Object* buildNetworkTree(Proposition* prop, Cons* propList) {
  if (propList->memberP(prop)) {
    return (wrapFloat(((FloatWrapper*)(dynamicSlotValue(prop->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue));
  }
  if (!(prop->support_reader() == NIL)) {
    { Cons* proofs = prop->support_reader();
      Cons* tree = NIL;

      { PartialSupport* proof = NULL;
        Cons* iter000 = proofs;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          proof = ((PartialSupport*)(iter000->value));
          { Proposition* fact = proof->fact;
            Cons* proofTree = NIL;

            { Object* arg = NULL;
              Vector* vector000 = fact->arguments;
              int index000 = 0;
              int length000 = vector000->length();
              FloatWrapper* score = NULL;
              Cons* iter001 = proof->argumentScores;
              Cons* collect000 = NULL;

              for  (; (index000 < length000) &&
                        (!(iter001 == NIL)); 
                    index000 = index000 + 1,
                    iter001 = iter001->rest) {
                arg = (vector000->theArray)[index000];
                score = ((FloatWrapper*)(iter001->value));
                if (isaP(arg, SGT_NEURAL_NETWORK_LOGIC_PROPOSITION)) {
                  setDynamicSlotValue(((Proposition*)(arg))->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, wrapFloat(score->wrapperValue), NULL_FLOAT_WRAPPER);
                  if (!((boolean)(collect000))) {
                    {
                      collect000 = cons(buildNetworkTree(((Proposition*)(arg)), cons(prop, propList)), NIL);
                      if (proofTree == NIL) {
                        proofTree = collect000;
                      }
                      else {
                        addConsToEndOfConsList(proofTree, collect000);
                      }
                    }
                  }
                  else {
                    {
                      collect000->rest = cons(buildNetworkTree(((Proposition*)(arg)), cons(prop, propList)), NIL);
                      collect000 = collect000->rest;
                    }
                  }
                }
              }
            }
            if (((boolean)(((PropositionNeuralNetwork*)(dynamicSlotValue(fact->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_NEURAL_NET, NULL)))))) {
              tree = cons(cons(((PropositionNeuralNetwork*)(dynamicSlotValue(fact->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_NEURAL_NET, NULL))), proofTree), tree);
            }
            else {
              tree = cons(wrapFloat(((FloatWrapper*)(dynamicSlotValue(prop->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue), tree);
            }
          }
        }
      }
      if ((tree->rest == NIL) &&
          (!consP(tree->value))) {
        return (tree->value);
      }
      else {
        return (tree);
      }
    }
  }
  else if (((boolean)(((PropositionNeuralNetwork*)(dynamicSlotValue(prop->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_NEURAL_NET, NULL)))))) {
    { Cons* tree = NIL;

      { Object* arg = NULL;
        Vector* vector001 = prop->arguments;
        int index001 = 0;
        int length001 = vector001->length();
        int i = NULL_INTEGER;
        int iter002 = 1;
        Cons* collect001 = NULL;

        for  (; index001 < length001; 
              index001 = index001 + 1,
              iter002 = iter002 + 1) {
          arg = (vector001->theArray)[index001];
          i = iter002;
          setDynamicSlotValue(((Proposition*)(arg))->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, wrapFloat(((FloatWrapper*)((((PropositionNeuralNetwork*)(dynamicSlotValue(prop->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_NEURAL_NET, NULL)))->input->theArray)[i]))->wrapperValue), NULL_FLOAT_WRAPPER);
          if (!((boolean)(collect001))) {
            {
              collect001 = cons(buildNetworkTree(((Proposition*)(arg)), cons(prop, propList)), NIL);
              if (tree == NIL) {
                tree = collect001;
              }
              else {
                addConsToEndOfConsList(tree, collect001);
              }
            }
          }
          else {
            {
              collect001->rest = cons(buildNetworkTree(((Proposition*)(arg)), cons(prop, propList)), NIL);
              collect001 = collect001->rest;
            }
          }
        }
      }
      tree = cons(((PropositionNeuralNetwork*)(dynamicSlotValue(prop->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_NEURAL_NET, NULL))), tree);
      return (consList(1, tree));
    }
  }
  else {
    return (wrapFloat(((FloatWrapper*)(dynamicSlotValue(prop->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE, NULL_FLOAT_WRAPPER)))->wrapperValue));
  }
}

double activateCachedNetwork(Cons* tree) {
  { Vector* scores = stella::newVector(tree->length());
    double score = 0.0;
    double sum = 0.0;

    { Cons* cachedNet = NULL;
      Cons* iter000 = tree;
      int k = NULL_INTEGER;
      int iter001 = 0;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        cachedNet = ((Cons*)(iter000->value));
        k = iter001;
        { PropositionNeuralNetwork* net = ((PropositionNeuralNetwork*)(cachedNet->value));

          sum = 0.0;
          score = 0.0;
          (net->input->theArray)[0] = (wrapFloat(1.0));
          { int i = NULL_INTEGER;
            int iter002 = 1;
            int upperBound000 = net->input->length() - 1;
            Object* input = NULL;
            Cons* iter003 = cachedNet->rest;

            for  (; (iter002 <= upperBound000) &&
                      (!(iter003 == NIL)); 
                  iter002 = iter002 + 1,
                  iter003 = iter003->rest) {
              i = iter002;
              input = iter003->value;
              if (isaP(input, SGT_NEURAL_NETWORK_STELLA_CONS)) {
                (net->input->theArray)[i] = (wrapFloat(activateCachedNetwork(((Cons*)(input)))));
              }
              else {
                (net->input->theArray)[i] = (((FloatWrapper*)(input)));
              }
            }
          }
          { int i = NULL_INTEGER;
            int iter004 = 0;
            int upperBound001 = net->hidden->length() - 1;

            for  (; iter004 <= upperBound001; 
                  iter004 = iter004 + 1) {
              i = iter004;
              { int j = NULL_INTEGER;
                int iter005 = 0;
                int upperBound002 = net->input->length() - 1;

                for  (; iter005 <= upperBound002; 
                      iter005 = iter005 + 1) {
                  j = iter005;
                  sum = sum + (((FloatWrapper*)((net->input->theArray)[j]))->wrapperValue * ((FloatWrapper*)((net->ih->theArray)[((j * net->ih->nofColumns) + i)]))->wrapperValue);
                }
              }
              (net->hidden->theArray)[i] = (wrapFloat(1.0 / (1.0 + ::exp((0 - sum)))));
              score = score + (((FloatWrapper*)((net->hidden->theArray)[i]))->wrapperValue * ((FloatWrapper*)((net->ho->theArray)[i]))->wrapperValue);
            }
          }
          net->output = 1.0 / (1.0 + ::exp((0 - score)));
          (scores->theArray)[k] = (wrapFloat(net->output));
        }
      }
    }
    if (oRULE_COMBINATIONo == KWD_NEURAL_NETWORK_MAX) {
      { FloatWrapper* max = ((FloatWrapper*)((scores->theArray)[0]));

        { int i = NULL_INTEGER;
          int iter006 = 0;
          int upperBound003 = scores->length() - 1;

          for  (; iter006 <= upperBound003; 
                iter006 = iter006 + 1) {
            i = iter006;
            if (((FloatWrapper*)((scores->theArray)[i]))->wrapperValue > max->wrapperValue) {
              max = ((FloatWrapper*)((scores->theArray)[i]));
            }
          }
        }
        return (max->wrapperValue);
      }
    }
    else if (oRULE_COMBINATIONo == KWD_NEURAL_NETWORK_NOISY_OR) {
      switch (scores->length()) {
        case 0: 
          return (0.0);
        case 1: 
          return (((FloatWrapper*)((scores->theArray)[0]))->wrapperValue);
        case 2: 
          return (probabilisticSum(((FloatWrapper*)((scores->theArray)[0]))->wrapperValue, ((FloatWrapper*)((scores->theArray)[1]))->wrapperValue));
        default:
          { Cons* consScores = NIL;

            { FloatWrapper* ele = NULL;
              Vector* vector000 = scores;
              int index000 = 0;
              int length000 = vector000->length();
              Cons* collect000 = NULL;

              for  (; index000 < length000; 
                    index000 = index000 + 1) {
                ele = ((FloatWrapper*)((vector000->theArray)[index000]));
                if (!((boolean)(collect000))) {
                  {
                    collect000 = cons(ele, NIL);
                    if (consScores == NIL) {
                      consScores = collect000;
                    }
                    else {
                      addConsToEndOfConsList(consScores, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000->rest = cons(ele, NIL);
                    collect000 = collect000->rest;
                  }
                }
              }
            }
            return (probabilisticSumN(consScores));
          }
          break;
      }
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << oRULE_COMBINATIONo << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
  }
}

double randomWeight(double n) {
  if (stella::random(2) == 1) {
    return (randomFloat(n));
  }
  return (0.0 - randomFloat(n));
}

double randomFloat(double n) {
  // Generate a random integer in the interval [0..n-1].
  // 'n' must be <= 2^15.
  if (n > 32768) {
    throw *newStellaException("random: Can only generate random numbers between 0 and (2^15)-1.");
  }
  return (n * (stella::random(32768) / 32767.0));
}

Vector* consToVector(Cons* form) {
  { int size = form->length();
    Vector* vect = stella::newVector(size);

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = size - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        (vect->theArray)[i] = (form->nth(i));
      }
    }
    return (vect);
  }
}

Vector* createVector(int values, ...) {
  // Return a vector containing 'values', in order.
  { Vector* vector = stella::newVector(values);

    { va_list iter000;
      int iter000Count = values;
      Object* v = NULL;
      int i = NULL_INTEGER;
      int iter001 = 0;

      va_start(iter000, values);
            for  (; (iter000Count--) > 0; 
            iter001 = iter001 + 1) {
        v = va_arg(iter000, Object*);
        i = iter001;
        (vector->theArray)[i] = v;
      }
      va_end(iter000);
    }
    return (vector);
  }
}

void zeroVector(Vector* v) {
  { int i = NULL_INTEGER;
    int iter000 = 0;
    int upperBound000 = v->length() - 1;

    for  (; iter000 <= upperBound000; 
          iter000 = iter000 + 1) {
      i = iter000;
      (v->theArray)[i] = (wrapFloat(0.0));
    }
  }
}

void structuredNeuralNetworkRegression(Symbol* className, Symbol* slotName, int cycles) {
  slotName = ((Symbol*)(slotName->permanentify()));
  className = ((Symbol*)(className->permanentify()));
  std::cout << "Generating training examples" << std::endl;
  { Surrogate* clasS = getDescription(className)->surrogateValueInverse;
    Surrogate* slot = getDescription(slotName)->surrogateValueInverse;
    List* ilist = allClassInstances(clasS)->listify();
    Vector* instances = stella::newVector(ilist->length());

    if (!floatFunctionP(slot)) {
      std::cout << "ERROR " << slotName << " is not a function of type float or integer" << std::endl;
      return;
    }
    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = ilist->length() - 1;
      Object* instance = NULL;
      Cons* iter001 = ilist->theConsList;

      for  (; (iter000 <= upperBound000) &&
                (!(iter001 == NIL)); 
            iter000 = iter000 + 1,
            iter001 = iter001->rest) {
        i = iter000;
        instance = iter001->value;
        (instances->theArray)[i] = (((LogicObject*)(instance)));
      }
    }
    clearCases();
    generateRegressionRuleWoSlot(instances, slotName, className, true);
    { int num = generateRegressionTrainingExamples(instances, slot);

      std::cout << "Training regression networks" << std::endl;
      trainCachedNeuralNetworks(cycles, num);
    }
  }
}

void structuredNeuralNetworkRegressionEvaluatorWrapper(Cons* arguments) {
  structuredNeuralNetworkRegression(((Symbol*)(arguments->value)), ((Symbol*)(arguments->rest->value)), ((IntegerWrapper*)(arguments->rest->rest->value))->wrapperValue);
}

List* getNnNearestNeighbors(TrainingExample* probe, List* cases, int k) {
  { List* result = newList();
    Module* currentModule = oMODULEo;
    Vector* neighbors = stella::newVector(k);
    int farthest = 0;
    double distance = 0.0;
    Vector* distances = stella::newVector(k);

    shuffleList(cases);
    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = k - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        (distances->theArray)[i] = (wrapFloat(999999.0));
      }
    }
    probe->nnHidden = createHiddenSignature(probe->query);
    { TrainingExample* casE = NULL;
      Cons* iter001 = cases->theConsList;

      for (; !(iter001 == NIL); iter001 = iter001->rest) {
        casE = ((TrainingExample*)(iter001->value));
        if (!((boolean)(casE->nnHidden))) {
          if (((boolean)(casE->module))) {
            casE->module->changeModule();
          }
          if (!((boolean)(casE->nnHidden))) {
            casE->nnHidden = createHiddenSignature(casE->query);
          }
          currentModule->changeModule();
        }
        distance = euclideanDistance(probe->nnHidden, casE->nnHidden) + 0.0;
        if (oPRINT_CASE_DISTANCESo) {
          std::cout << "  Distance from " << casE->query->last() << ": " << distance << std::endl;
        }
        casE->temp = distance;
        if (distance < ((FloatWrapper*)((distances->theArray)[farthest]))->wrapperValue) {
          (distances->theArray)[farthest] = (wrapFloat(distance));
          (neighbors->theArray)[farthest] = casE;
          farthest = 0;
          { int j = NULL_INTEGER;
            int iter002 = 1;
            int upperBound001 = k - 1;

            for  (; iter002 <= upperBound001; 
                  iter002 = iter002 + 1) {
              j = iter002;
              if (((FloatWrapper*)((distances->theArray)[j]))->wrapperValue > ((FloatWrapper*)((distances->theArray)[farthest]))->wrapperValue) {
                farthest = j;
              }
            }
          }
        }
      }
    }
    { int i = NULL_INTEGER;
      int iter003 = 0;
      int upperBound002 = k - 1;
      Cons* collect000 = NULL;

      for  (; iter003 <= upperBound002; 
            iter003 = iter003 + 1) {
        i = iter003;
        if (((boolean)(((TrainingExample*)((neighbors->theArray)[i]))))) {
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(((TrainingExample*)((neighbors->theArray)[i])), NIL);
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
              collect000->rest = cons(((TrainingExample*)((neighbors->theArray)[i])), NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
    }
    return (result);
  }
}

void swapInNewNetworks(List* oldNets, List* newNets) {
  { PropositionNeuralNetwork* oldNet = NULL;
    Cons* iter000 = oldNets->theConsList;
    PropositionNeuralNetwork* newNet = NULL;
    Cons* iter001 = newNets->theConsList;

    for  (; (!(iter000 == NIL)) &&
              (!(iter001 == NIL)); 
          iter000 = iter000->rest,
          iter001 = iter001->rest) {
      oldNet = ((PropositionNeuralNetwork*)(iter000->value));
      newNet = ((PropositionNeuralNetwork*)(iter001->value));
      setDynamicSlotValue(oldNet->proposition->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_NEURAL_NET, newNet, NULL);
      newNet->proposition = oldNet->proposition;
    }
  }
  oMASTER_NEURAL_NETWORK_LISTo = newNets;
}

void swapInNetworkFile(const char* file) {
  { List* newNets = loadNeuralNetworkFile(file);

    { PropositionNeuralNetwork* oldNet = NULL;
      Cons* iter000 = oMASTER_NEURAL_NETWORK_LISTo->theConsList;
      PropositionNeuralNetwork* newNet = NULL;
      Cons* iter001 = newNets->theConsList;

      for  (; (!(iter000 == NIL)) &&
                (!(iter001 == NIL)); 
            iter000 = iter000->rest,
            iter001 = iter001->rest) {
        oldNet = ((PropositionNeuralNetwork*)(iter000->value));
        newNet = ((PropositionNeuralNetwork*)(iter001->value));
        if ((!(oldNet->input->length() == newNet->input->length())) ||
            (!(oldNet->hidden->length() == newNet->hidden->length()))) {
          std::cout << "Error: network file does not match master list" << std::endl;
          return;
        }
      }
    }
    swapInNewNetworks(oMASTER_NEURAL_NETWORK_LISTo, newNets);
  }
}

void swapInNetworkFileEvaluatorWrapper(Cons* arguments) {
  swapInNetworkFile(((StringWrapper*)(arguments->value))->wrapperValue);
}

List* loadNeuralNetworkFile(const char* file) {
  { boolean dummy1;
    boolean dummy2;
    boolean dummy3;
    boolean dummy4;
    boolean dummy5;
    boolean dummy6;

    { List* nets = newList();
      InputFileStream* stream = newInputFileStream(file);
      int numHidden = 0;
      Cons* prop = NIL;
      Object* temp = NULL;
      int numIn = 0;
      PropositionNeuralNetwork* net = NULL;

      for (;;) {
        if (!(readSExpression(stream, dummy1) == SYM_NEURAL_NETWORK_LOGIC_DEFNETWORK)) {
          return (nets->reverse());
        }
        prop = ((Cons*)(readSExpression(stream, dummy2)));
        numIn = ((IntegerWrapper*)(readSExpression(stream, dummy3)))->wrapperValue;
        numHidden = ((IntegerWrapper*)(readSExpression(stream, dummy4)))->wrapperValue;
        net = allocateNeuralNetwork(numIn, numHidden);
        { int i = NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = numIn - 1;

          for  (; iter000 <= upperBound000; 
                iter000 = iter000 + 1) {
            i = iter000;
            { int h = NULL_INTEGER;
              int iter001 = 0;
              int upperBound001 = numHidden - 1;

              for  (; iter001 <= upperBound001; 
                    iter001 = iter001 + 1) {
                h = iter001;
                temp = readSExpression(stream, dummy5);
                if (eqlP(temp, ZERO_WRAPPER)) {
                  temp = wrapFloat(0.0);
                }
                (net->ih->theArray)[((i * net->ih->nofColumns) + h)] = (((FloatWrapper*)(temp)));
              }
            }
          }
        }
        { int h = NULL_INTEGER;
          int iter002 = 0;
          int upperBound002 = numHidden - 1;

          for  (; iter002 <= upperBound002; 
                iter002 = iter002 + 1) {
            h = iter002;
            (net->ho->theArray)[h] = (((FloatWrapper*)(readSExpression(stream, dummy6))));
          }
        }
        nets->push(net);
      }
    }
  }
}

List* loadNeuralNetworkFileEvaluatorWrapper(Cons* arguments) {
  return (loadNeuralNetworkFile(((StringWrapper*)(arguments->value))->wrapperValue));
}

void saveAllNeuralNetworks(const char* file) {
  // Save all neural networks to `file' (if `file' is non-NULL).
  // If networks are saved periodically (see `set-save-network-cycle') this file
  // name will be used to perform periodic saves.
  oSAVE_NETWORK_FILEo = file;
  if (file != NULL) {
    std::cout << "Saving networks" << std::endl;
    { OutputFileStream* fptr = newOutputFileStream(file);

      { PropositionNeuralNetwork* net = NULL;
        Cons* iter000 = oMASTER_NEURAL_NETWORK_LISTo->theConsList;

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          net = ((PropositionNeuralNetwork*)(iter000->value));
          printNeuralNetwork(net, fptr);
          *(fptr->nativeStream) << std::endl;
        }
      }
      fptr->free();
    }
  }
}

void saveAllNeuralNetworksEvaluatorWrapper(Cons* arguments) {
  saveAllNeuralNetworks(((StringWrapper*)(arguments->value))->wrapperValue);
}

void saveNeuralNetwork(PropositionNeuralNetwork* net, const char* file) {
  { OutputFileStream* fptr = newOutputFileStream(file);

    printNeuralNetwork(net, fptr);
    fptr->free();
  }
}

void saveNeuralNetworkEvaluatorWrapper(Cons* arguments) {
  saveNeuralNetwork(((PropositionNeuralNetwork*)(arguments->value)), ((StringWrapper*)(arguments->rest->value))->wrapperValue);
}

void printNeuralNetwork(PropositionNeuralNetwork* net, OutputStream* stream) {
  *(stream->nativeStream) << "defnetwork " << std::endl;
  printProposition(net->proposition, stream, false);
  *(stream->nativeStream) << std::endl;
  *(stream->nativeStream) << net->input->length() << " " << net->hidden->length() << std::endl;
  { int i = NULL_INTEGER;
    int iter000 = 0;
    int upperBound000 = net->input->length() - 1;

    for  (; iter000 <= upperBound000; 
          iter000 = iter000 + 1) {
      i = iter000;
      { int j = NULL_INTEGER;
        int iter001 = 0;
        int upperBound001 = net->hidden->length() - 1;

        for  (; iter001 <= upperBound001; 
              iter001 = iter001 + 1) {
          j = iter001;
          { double value = ((FloatWrapper*)((net->ih->theArray)[((i * net->ih->nofColumns) + j)]))->wrapperValue;

            *(stream->nativeStream) << " " << value;
          }
        }
      }
    }
  }
  *(stream->nativeStream) << std::endl;
  { FloatWrapper* num = NULL;
    Vector* vector000 = net->ho;
    int index000 = 0;
    int length000 = vector000->length();

    for  (; index000 < length000; 
          index000 = index000 + 1) {
      num = ((FloatWrapper*)((vector000->theArray)[index000]));
      { double value = num->wrapperValue;

        *(stream->nativeStream) << " " << value;
      }
    }
  }
  *(stream->nativeStream) << std::endl;
}

Vector* createHiddenSignature(Cons* consQuery) {
  { QueryIterator* query = makeQuery(NIL, ((Cons*)(copyConsTree(consQuery))), NIL, NIL);
    NnPartialMatch* pmf = NULL;
    PropositionNeuralNetwork* net = NULL;
    Vector* result = NULL;

    query->options->insertAt(KWD_NEURAL_NETWORK_MATCH_MODE, KWD_NEURAL_NETWORK_NN);
    query->options->insertAt(KWD_NEURAL_NETWORK_MAXIMIZE_SCOREp, TRUE_WRAPPER);
    callAskPartial(query);
    pmf = ((NnPartialMatch*)(query->baseControlFrame->partialMatchFrame->child->child));
    net = ((PropositionNeuralNetwork*)(dynamicSlotValue(pmf->controlFrame->proposition->dynamicSlots, SYM_NEURAL_NETWORK_LOGIC_NEURAL_NET, NULL)));
    result = stella::newVector(net->hidden->length());
    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = net->hidden->length() - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        (result->theArray)[i] = (((FloatWrapper*)((net->hidden->theArray)[i])));
      }
    }
    return (result);
  }
}

MultiDimensionalArray* newMultiDimensionalArray() {
  { MultiDimensionalArray* self = NULL;

    self = new (PointerFreeGC)MultiDimensionalArray;
    return (self);
  }
}

Surrogate* MultiDimensionalArray::primaryType() {
  { MultiDimensionalArray* self = this;

    return (SGT_NEURAL_NETWORK_LOGIC_MULTI_DIMENSIONAL_ARRAY);
  }
}

two_D_array* new2_D_array(int nofRows, int nofColumns) {
  { two_D_array* self = NULL;

    self = new two_D_array();
    self->nofRows = nofRows;
    self->nofColumns = nofColumns;
    self->theArray = NULL;
    initialize2_D_array(self);
    return (self);
  }
}

Surrogate* two_D_array::primaryType() {
  { two_D_array* self = this;

    return (SGT_NEURAL_NETWORK_LOGIC_2_D_ARRAY);
  }
}

Object* access2_D_arraySlotValue(two_D_array* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_NEURAL_NETWORK_LOGIC_NOF_ROWS) {
    if (setvalueP) {
      self->nofRows = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->nofRows);
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_NOF_COLUMNS) {
    if (setvalueP) {
      self->nofColumns = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->nofColumns);
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

void two_D_array::printObject(std::ostream* stream) {
  { two_D_array* self = this;

    self->printArray(stream);
  }
}

void initialize2_D_array(two_D_array* self) {
  { Vector* vector = stella::newVector(self->nofRows * self->nofColumns);

    self->theArray = vector->theArray;
    vector->theArray = NULL;
  }
}

Object* two_D_array::two_D_element(int row, int column) {
  // Return the element of `array' at position [`row', `column'].
  { two_D_array* array = this;

    return ((array->theArray)[((row * array->nofColumns) + column)]);
  }
}

Object* two_D_array::two_D_elementSetter(Object* value, int row, int column) {
  // Set the element of `array' at position [`row', `column']
  // to `value' and return the result.
  { two_D_array* array = this;

    return ((array->theArray)[((row * array->nofColumns) + column)] = value);
  }
}

two_D_array* create2_D_array(int nofRows, int nofColumns, int values, ...) {
  // Create a two-dimensional array with `nof-rows' rows and
  // `nof-columns' columns, and initialize it in row-major-order from `values'.
  // Missing values will be padded with NULL, extraneous values will be ignored.
  { two_D_array* array = new2_D_array(nofRows, nofColumns);
    Object** nativearray = array->theArray;

    { va_list iter001;
      int iter001Count = values;
      int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = (nofRows * nofColumns) - 1;
      Object* value = NULL;

      va_start(iter001, values);
            for  (; (iter000 <= upperBound000) &&
                ((iter001Count--) > 0); 
            iter000 = iter000 + 1) {
        i = iter000;
        value = va_arg(iter001, Object*);
        nativearray[i] = value;
      }
      va_end(iter001);
    }
    return (array);
  }
}

void two_D_array::fillArray(int values, ...) {
  // Fill the two-dimensional array `self' in row-major-order
  // from `values'.  Missing values will retain their old values, extraneous values
  // will be ignored.
  { two_D_array* self = this;

    { Object** nativearray = self->theArray;

      { va_list iter001;
        int iter001Count = values;
        int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = (self->nofRows * self->nofColumns) - 1;
        Object* value = NULL;

        va_start(iter001, values);
                for  (; (iter000 <= upperBound000) &&
                  ((iter001Count--) > 0); 
              iter000 = iter000 + 1) {
          i = iter000;
          value = va_arg(iter001, Object*);
          nativearray[i] = value;
        }
        va_end(iter001);
      }
    }
  }
}

void two_D_array::printArray(std::ostream* stream) {
  // Print the array `self' to `stream'.
  { two_D_array* self = this;

    { int nofRows = self->nofRows;
      int nofColumns = self->nofColumns;
      int limit = 9;

      *(stream) << "|i|[";
      { int row = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = nofRows - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          row = iter000;
          *(stream) << "[";
          { int column = NULL_INTEGER;
            int iter001 = 0;
            int upperBound001 = nofColumns - 1;

            for  (; iter001 <= upperBound001; 
                  iter001 = iter001 + 1) {
              column = iter001;
              *(stream) << (self->theArray)[((row * self->nofColumns) + column)];
              if (column > limit) {
                *(stream) << " ...]";
                break;
              }
              else if (column < (nofColumns - 1)) {
                *(stream) << " ";
              }
              else {
                *(stream) << "]";
              }
            }
          }
          if (row > limit) {
            *(stream) << " ...]";
            break;
          }
          else if (row < (nofRows - 1)) {
            *(stream) << " ";
          }
          else {
            *(stream) << "]";
          }
        }
      }
    }
  }
}

FloatVector* newFloatVector(int arraySize) {
  { FloatVector* self = NULL;

    self = new FloatVector();
    self->arraySize = arraySize;
    self->theArray = NULL;
    initializeFloatVector(self);
    return (self);
  }
}

Surrogate* FloatVector::primaryType() {
  { FloatVector* self = this;

    return (SGT_NEURAL_NETWORK_LOGIC_FLOAT_VECTOR);
  }
}

Object* accessFloatVectorSlotValue(FloatVector* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_NEURAL_NETWORK_STELLA_ARRAY_SIZE) {
    if (setvalueP) {
      self->arraySize = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->arraySize);
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

void FloatVector::printObject(std::ostream* stream) {
  { FloatVector* self = this;

    self->printVector(stream);
  }
}

void initializeFloatVector(FloatVector* self) {
  { Vector* vector = stella::newVector(self->arraySize);

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = vector->length() - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        (vector->theArray)[i] = (newFloatWrapper(NULL_FLOAT));
      }
    }
    self->theArray = ((Object**)(vector->theArray));
    vector->theArray = NULL;
  }
}

FloatVector* createFloatVector(int values, ...) {
  // Return a vector containing 'values', in order.
  { FloatVector* vector = newFloatVector(values);

    { va_list iter000;
      int iter000Count = values;
      double v = NULL_FLOAT;
      int i = NULL_INTEGER;
      int iter001 = 0;

      va_start(iter000, values);
            for  (; (iter000Count--) > 0; 
            iter001 = iter001 + 1) {
        v = va_arg(iter000, double);
        i = iter001;
        ((FloatWrapper*)(((FloatWrapper*)((vector->theArray)[i]))))->wrapperValue = v;
      }
      va_end(iter000);
    }
    return (vector);
  }
}

void FloatVector::printVector(std::ostream* stream) {
  { FloatVector* self = this;

    if (self->arraySize == 0) {
      *(stream) << "|i|[]";
    }
    else {
      { int i = 0;
        int limit = 9;

        *(stream) << "|i|[";
        { double element = NULL_FLOAT;
          FloatVector* vector000 = self;
          int index000 = 0;
          int length000 = vector000->arraySize;

          for  (; index000 < length000; 
                index000 = index000 + 1) {
            element = ((FloatWrapper*)(((FloatWrapper*)((vector000->theArray)[index000]))))->wrapperValue;
            *(stream) << element;
            i = i + 1;
            if (i > limit) {
              break;
            }
            if (i < self->arraySize) {
              *(stream) << " ";
            }
          }
        }
        if ((i <= limit) ||
            (i == self->arraySize)) {
          *(stream) << "]";
        }
        else {
          *(stream) << " ...]";
        }
      }
    }
  }
}

boolean FloatVector::emptyP() {
  // Return TRUE if 'self' has length 0.
  { FloatVector* self = this;

    return (self->arraySize == 0);
  }
}

boolean FloatVector::nonEmptyP() {
  // Return TRUE if 'self' has length > 0.
  { FloatVector* self = this;

    return (self->arraySize > 0);
  }
}

double FloatVector::nth(int position) {
  { FloatVector* self = this;

    return (((FloatWrapper*)(((FloatWrapper*)((self->theArray)[position]))))->wrapperValue);
  }
}

double FloatVector::nthSetter(double value, int position) {
  { FloatVector* self = this;

    return (((FloatWrapper*)(((FloatWrapper*)((self->theArray)[position]))))->wrapperValue = value);
  }
}

int FloatVector::length() {
  { FloatVector* self = this;

    return (self->arraySize);
  }
}

boolean FloatVector::memberP(double object) {
  { FloatVector* self = this;

    { Object** array = self->theArray;

      { int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = self->arraySize - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          i = iter000;
          if (((FloatWrapper*)(((FloatWrapper*)(array[i]))))->wrapperValue == object) {
            return (true);
          }
        }
      }
      return (false);
    }
  }
}

two_D_floatArray* new2_D_floatArray(int nofRows, int nofColumns) {
  { two_D_floatArray* self = NULL;

    self = new two_D_floatArray();
    self->nofRows = nofRows;
    self->nofColumns = nofColumns;
    self->theArray = NULL;
    initialize2_D_floatArray(self);
    return (self);
  }
}

Surrogate* two_D_floatArray::primaryType() {
  { two_D_floatArray* self = this;

    return (SGT_NEURAL_NETWORK_LOGIC_2_D_FLOAT_ARRAY);
  }
}

Object* access2_D_floatArraySlotValue(two_D_floatArray* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_NEURAL_NETWORK_LOGIC_NOF_ROWS) {
    if (setvalueP) {
      self->nofRows = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->nofRows);
    }
  }
  else if (slotname == SYM_NEURAL_NETWORK_LOGIC_NOF_COLUMNS) {
    if (setvalueP) {
      self->nofColumns = ((IntegerWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapInteger(self->nofColumns);
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

void two_D_floatArray::printObject(std::ostream* stream) {
  { two_D_floatArray* self = this;

    self->printArray(stream);
  }
}

void initialize2_D_floatArray(two_D_floatArray* self) {
  { Vector* vector = stella::newVector(self->nofRows * self->nofColumns);

    { int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = vector->length() - 1;

      for  (; iter000 <= upperBound000; 
            iter000 = iter000 + 1) {
        i = iter000;
        (vector->theArray)[i] = (newFloatWrapper(NULL_FLOAT));
      }
    }
    self->theArray = ((Object**)(vector->theArray));
    vector->theArray = NULL;
  }
}

double two_D_floatArray::two_D_element(int row, int column) {
  // Return the element of `array' at position [`row', `column'].
  { two_D_floatArray* array = this;

    return (((FloatWrapper*)(((FloatWrapper*)((array->theArray)[((row * array->nofColumns) + column)]))))->wrapperValue);
  }
}

double two_D_floatArray::two_D_elementSetter(double value, int row, int column) {
  // Set the element of `array' at position [`row', `column']
  // to `value' and return the result.
  { two_D_floatArray* array = this;

    return (((FloatWrapper*)(((FloatWrapper*)((array->theArray)[((row * array->nofColumns) + column)]))))->wrapperValue = value);
  }
}

two_D_floatArray* create2_D_floatArray(int nofRows, int nofColumns, int values, ...) {
  // Create a two-dimensional array with `nof-rows' rows and
  // `nof-columns' columns, and initialize it in row-major-order from `values'.
  // Missing values will be padded with NULL, extraneous values will be ignored.
  { two_D_floatArray* array = new2_D_floatArray(nofRows, nofColumns);
    Object** nativearray = array->theArray;

    { va_list iter001;
      int iter001Count = values;
      int i = NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = (nofRows * nofColumns) - 1;
      double value = NULL_FLOAT;

      va_start(iter001, values);
            for  (; (iter000 <= upperBound000) &&
                ((iter001Count--) > 0); 
            iter000 = iter000 + 1) {
        i = iter000;
        value = va_arg(iter001, double);
        ((FloatWrapper*)(((FloatWrapper*)(nativearray[i]))))->wrapperValue = value;
      }
      va_end(iter001);
    }
    return (array);
  }
}

void two_D_floatArray::fillArray(int values, ...) {
  // Fill the two-dimensional array `self' in row-major-order
  // from `values'.  Missing values will retain their old values, extraneous values
  // will be ignored.
  { two_D_floatArray* self = this;

    { Object** nativearray = self->theArray;

      { va_list iter001;
        int iter001Count = values;
        int i = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = (self->nofRows * self->nofColumns) - 1;
        double value = NULL_FLOAT;

        va_start(iter001, values);
                for  (; (iter000 <= upperBound000) &&
                  ((iter001Count--) > 0); 
              iter000 = iter000 + 1) {
          i = iter000;
          value = va_arg(iter001, double);
          ((FloatWrapper*)(((FloatWrapper*)(nativearray[i]))))->wrapperValue = value;
        }
        va_end(iter001);
      }
    }
  }
}

void two_D_floatArray::printArray(std::ostream* stream) {
  // Print the array `self' to `stream'.
  { two_D_floatArray* self = this;

    { int nofRows = self->nofRows;
      int nofColumns = self->nofColumns;
      int limit = 9;

      *(stream) << "|i|[";
      { int row = NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = nofRows - 1;

        for  (; iter000 <= upperBound000; 
              iter000 = iter000 + 1) {
          row = iter000;
          *(stream) << "[";
          { int column = NULL_INTEGER;
            int iter001 = 0;
            int upperBound001 = nofColumns - 1;

            for  (; iter001 <= upperBound001; 
                  iter001 = iter001 + 1) {
              column = iter001;
              *(stream) << ((FloatWrapper*)(((FloatWrapper*)((self->theArray)[((row * self->nofColumns) + column)]))))->wrapperValue;
              if (column > limit) {
                *(stream) << " ...]";
                break;
              }
              else if (column < (nofColumns - 1)) {
                *(stream) << " ";
              }
              else {
                *(stream) << "]";
              }
            }
          }
          if (row > limit) {
            *(stream) << " ...]";
            break;
          }
          else if (row < (nofRows - 1)) {
            *(stream) << " ";
          }
          else {
            *(stream) << "]";
          }
        }
      }
    }
  }
}

void helpStartupNeuralNetwork1() {
  {
    KWD_NEURAL_NETWORK_BACKPROP = ((Keyword*)(internRigidSymbolWrtModule("BACKPROP", NULL, 2)));
    SYM_NEURAL_NETWORK_LOGIC_WEIGHT_VECTOR = ((Symbol*)(internRigidSymbolWrtModule("WEIGHT-VECTOR", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_2_D_WEIGHT_ARRAY = ((Symbol*)(internRigidSymbolWrtModule("2_D_WEIGHT-ARRAY", NULL, 0)));
    SGT_NEURAL_NETWORK_LOGIC_PROPOSITION_NEURAL_NETWORK = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION-NEURAL-NETWORK", NULL, 1)));
    SYM_NEURAL_NETWORK_LOGIC_PROPOSITION = ((Symbol*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_INPUT = ((Symbol*)(internRigidSymbolWrtModule("INPUT", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_HIDDEN = ((Symbol*)(internRigidSymbolWrtModule("HIDDEN", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_OUTPUT = ((Symbol*)(internRigidSymbolWrtModule("OUTPUT", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_INPUT_ERROR = ((Symbol*)(internRigidSymbolWrtModule("INPUT-ERROR", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_HIDDEN_ERROR = ((Symbol*)(internRigidSymbolWrtModule("HIDDEN-ERROR", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_IH = ((Symbol*)(internRigidSymbolWrtModule("IH", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_IH_DELTA = ((Symbol*)(internRigidSymbolWrtModule("IH-DELTA", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_HO = ((Symbol*)(internRigidSymbolWrtModule("HO", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_HO_DELTA = ((Symbol*)(internRigidSymbolWrtModule("HO-DELTA", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_IH_SLOPE = ((Symbol*)(internRigidSymbolWrtModule("IH-SLOPE", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_IH_PREV_SLOPE = ((Symbol*)(internRigidSymbolWrtModule("IH-PREV-SLOPE", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_HO_SLOPE = ((Symbol*)(internRigidSymbolWrtModule("HO-SLOPE", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_HO_PREV_SLOPE = ((Symbol*)(internRigidSymbolWrtModule("HO-PREV-SLOPE", NULL, 0)));
    KWD_NEURAL_NETWORK_AND = ((Keyword*)(internRigidSymbolWrtModule("AND", NULL, 2)));
    KWD_NEURAL_NETWORK_OR = ((Keyword*)(internRigidSymbolWrtModule("OR", NULL, 2)));
    KWD_NEURAL_NETWORK_QUICKPROP = ((Keyword*)(internRigidSymbolWrtModule("QUICKPROP", NULL, 2)));
    SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE = ((Symbol*)(internRigidSymbolWrtModule("MATCH-SCORE", NULL, 0)));
    KWD_NEURAL_NETWORK_BACKPROPAGATION = ((Keyword*)(internRigidSymbolWrtModule("BACKPROPAGATION", NULL, 2)));
    SYM_NEURAL_NETWORK_LOGIC_NEURAL_NET = ((Symbol*)(internRigidSymbolWrtModule("NEURAL-NET", NULL, 0)));
    KWD_NEURAL_NETWORK_MAX = ((Keyword*)(internRigidSymbolWrtModule("MAX", NULL, 2)));
    KWD_NEURAL_NETWORK_NOISY_OR = ((Keyword*)(internRigidSymbolWrtModule("NOISY-OR", NULL, 2)));
    SGT_NEURAL_NETWORK_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", getStellaModule("/STELLA", true), 1)));
    SGT_NEURAL_NETWORK_LOGIC_PROPOSITION = ((Surrogate*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 1)));
    SYM_NEURAL_NETWORK_LOGIC_DEFNETWORK = ((Symbol*)(internRigidSymbolWrtModule("DEFNETWORK", NULL, 0)));
    KWD_NEURAL_NETWORK_MATCH_MODE = ((Keyword*)(internRigidSymbolWrtModule("MATCH-MODE", NULL, 2)));
    KWD_NEURAL_NETWORK_NN = ((Keyword*)(internRigidSymbolWrtModule("NN", NULL, 2)));
    KWD_NEURAL_NETWORK_MAXIMIZE_SCOREp = ((Keyword*)(internRigidSymbolWrtModule("MAXIMIZE-SCORE?", NULL, 2)));
    SGT_NEURAL_NETWORK_LOGIC_MULTI_DIMENSIONAL_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("MULTI-DIMENSIONAL-ARRAY", NULL, 1)));
    SGT_NEURAL_NETWORK_LOGIC_2_D_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("2_D_ARRAY", NULL, 1)));
    SYM_NEURAL_NETWORK_LOGIC_NOF_ROWS = ((Symbol*)(internRigidSymbolWrtModule("NOF-ROWS", NULL, 0)));
    SYM_NEURAL_NETWORK_LOGIC_NOF_COLUMNS = ((Symbol*)(internRigidSymbolWrtModule("NOF-COLUMNS", NULL, 0)));
    SGT_NEURAL_NETWORK_LOGIC_FLOAT_VECTOR = ((Surrogate*)(internRigidSymbolWrtModule("FLOAT-VECTOR", NULL, 1)));
    SYM_NEURAL_NETWORK_STELLA_ARRAY_SIZE = ((Symbol*)(internRigidSymbolWrtModule("ARRAY-SIZE", getStellaModule("/STELLA", true), 0)));
    SGT_NEURAL_NETWORK_LOGIC_2_D_FLOAT_ARRAY = ((Surrogate*)(internRigidSymbolWrtModule("2_D_FLOAT-ARRAY", NULL, 1)));
    SYM_NEURAL_NETWORK_LOGIC_STARTUP_NEURAL_NETWORK = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-NEURAL-NETWORK", NULL, 0)));
    SYM_NEURAL_NETWORK_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
  }
}

void helpStartupNeuralNetwork2() {
  {
    defineStellaTypeFromStringifiedSource("(DEFTYPE WEIGHT-VECTOR (VECTOR OF FLOAT-WRAPPER))");
    defineStellaTypeFromStringifiedSource("(DEFTYPE 2_D_WEIGHT-ARRAY (2_D_ARRAY OF FLOAT-WRAPPER))");
    defineClassFromStringifiedSource("NEURAL-NETWORK", "(DEFCLASS NEURAL-NETWORK (STANDARD-OBJECT) :ABSTRACT? TRUE)");
    { Class* clasS = defineClassFromStringifiedSource("PROPOSITION-NEURAL-NETWORK", "(DEFCLASS PROPOSITION-NEURAL-NETWORK (NEURAL-NETWORK) :SLOTS ((PROPOSITION :TYPE PROPOSITION) (INPUT :TYPE WEIGHT-VECTOR) (HIDDEN :TYPE WEIGHT-VECTOR) (OUTPUT :TYPE FLOAT) (INPUT-ERROR :TYPE WEIGHT-VECTOR) (HIDDEN-ERROR :TYPE WEIGHT-VECTOR) (IH :TYPE 2_D_WEIGHT-ARRAY) (IH-DELTA :TYPE 2_D_WEIGHT-ARRAY) (HO :TYPE WEIGHT-VECTOR) (HO-DELTA :TYPE WEIGHT-VECTOR) (IH-SLOPE :TYPE 2_D_WEIGHT-ARRAY) (IH-PREV-SLOPE :TYPE 2_D_WEIGHT-ARRAY) (HO-SLOPE :TYPE WEIGHT-VECTOR) (HO-PREV-SLOPE :TYPE WEIGHT-VECTOR)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newPropositionNeuralNetwork));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessPropositionNeuralNetworkSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("MULTI-DIMENSIONAL-ARRAY", "(DEFCLASS MULTI-DIMENSIONAL-ARRAY (ABSTRACT-COLLECTION))");

      clasS->classConstructorCode = ((cpp_function_code)(&newMultiDimensionalArray));
    }
    { Class* clasS = defineClassFromStringifiedSource("2_D_ARRAY", "(DEFCLASS 2_D_ARRAY (MULTI-DIMENSIONAL-ARRAY) :DOCUMENTATION \"Two-dimensional arrays with elements of type OBJECT.\" :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :SLOTS ((NOF-ROWS :TYPE INTEGER :REQUIRED? TRUE) (NOF-COLUMNS :TYPE INTEGER :REQUIRED? TRUE) (THE-ARRAY :TYPE (NATIVE-VECTOR OF (LIKE (ANY-VALUE SELF))))) :INITIALIZER INITIALIZE-2_D_ARRAY :PRINT-FORM (PRINT-ARRAY SELF STREAM))");

      clasS->classConstructorCode = ((cpp_function_code)(&new2_D_array));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&access2_D_arraySlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("FLOAT-VECTOR", "(DEFCLASS FLOAT-VECTOR (ABSTRACT-COLLECTION SEQUENCE-MIXIN) :PARAMETERS ((ANY-VALUE :TYPE FLOAT)) :PUBLIC-SLOTS ((ARRAY-SIZE :TYPE INTEGER :REQUIRED? TRUE)) :SLOTS ((THE-ARRAY :TYPE (NATIVE-VECTOR OF FLOAT-WRAPPER))) :PRINT-FORM (PRINT-VECTOR SELF STREAM) :INITIALIZER INITIALIZE-FLOAT-VECTOR)");

      clasS->classConstructorCode = ((cpp_function_code)(&newFloatVector));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessFloatVectorSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("2_D_FLOAT-ARRAY", "(DEFCLASS 2_D_FLOAT-ARRAY (MULTI-DIMENSIONAL-ARRAY) :DOCUMENTATION \"Two-dimensional arrays with elements of type FLOAT.\" :PARAMETERS ((ANY-VALUE :TYPE FLOAT)) :SLOTS ((NOF-ROWS :TYPE INTEGER :REQUIRED? TRUE) (NOF-COLUMNS :TYPE INTEGER :REQUIRED? TRUE) (THE-ARRAY :TYPE (NATIVE-VECTOR OF FLOAT-WRAPPER))) :INITIALIZER INITIALIZE-2_D_FLOAT-ARRAY :PRINT-FORM (PRINT-ARRAY SELF STREAM))");

      clasS->classConstructorCode = ((cpp_function_code)(&new2_D_floatArray));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&access2_D_floatArraySlotValue));
    }
  }
}

void helpStartupNeuralNetwork3() {
  {
    defineFunctionObject("SET-TRACE-NEURAL-NETWORK-TRAINING", "(DEFUN SET-TRACE-NEURAL-NETWORK-TRAINING ((B BOOLEAN)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setTraceNeuralNetworkTraining)), ((cpp_function_code)(&setTraceNeuralNetworkTrainingEvaluatorWrapper)));
    defineFunctionObject("SET-SAVE-NETWORK-CYCLE", "(DEFUN SET-SAVE-NETWORK-CYCLE ((I INTEGER)) :DOCUMENTATION \"Set number of cycles between which networks are saved to the\nfile established by the last call to `save-all-neural-networks'.  A number <= 0\nor a NULL number turns off periodic saving.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setSaveNetworkCycle)), ((cpp_function_code)(&setSaveNetworkCycleEvaluatorWrapper)));
    defineFunctionObject("SET-ERROR-CUTOFF", "(DEFUN SET-ERROR-CUTOFF ((F FLOAT)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setErrorCutoff)), ((cpp_function_code)(&setErrorCutoffEvaluatorWrapper)));
    defineFunctionObject("SET-TRAIN-CACHED-NEURAL-NETWORKS", "(DEFUN SET-TRAIN-CACHED-NEURAL-NETWORKS ((B BOOLEAN)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setTrainCachedNeuralNetworks)), ((cpp_function_code)(&setTrainCachedNeuralNetworksEvaluatorWrapper)));
    defineFunctionObject("SET-LEARNING-RATE", "(DEFUN SET-LEARNING-RATE ((RATE FLOAT)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setLearningRate)), ((cpp_function_code)(&setLearningRateEvaluatorWrapper)));
    defineFunctionObject("SET-MOMENTUM-TERM", "(DEFUN SET-MOMENTUM-TERM ((M FLOAT)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setMomentumTerm)), ((cpp_function_code)(&setMomentumTermEvaluatorWrapper)));
    defineFunctionObject("SET-WEIGHT-RANGE", "(DEFUN SET-WEIGHT-RANGE ((W FLOAT)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setWeightRange)), ((cpp_function_code)(&setWeightRangeEvaluatorWrapper)));
    defineFunctionObject("SET-NEURAL-NETWORK-TRAINING-METHOD", "(DEFUN SET-NEURAL-NETWORK-TRAINING-METHOD ((M KEYWORD)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setNeuralNetworkTrainingMethod)), NULL);
    defineFunctionObject("SET-ERROR-PRINT-CYCLE", "(DEFUN SET-ERROR-PRINT-CYCLE ((I INTEGER)) :DOCUMENTATION \"Set number of cycles between which error rates are saved to\nthe file established by the last call to `save-all-neural-networks' appended\nwith extension `.err'.  A number <= 0 (or NULL) turns off periodic saving.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&setErrorPrintCycle)), ((cpp_function_code)(&setErrorPrintCycleEvaluatorWrapper)));
    defineFunctionObject("DELETE-ALL-NEURAL-NETWORKS", "(DEFUN DELETE-ALL-NEURAL-NETWORKS () :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&deleteAllNeuralNetworks)), NULL);
    defineFunctionObject("CHECK-MASTER-NETWORK-LIST", "(DEFUN CHECK-MASTER-NETWORK-LIST () :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&checkMasterNetworkList)), NULL);
    defineFunctionObject("CLEAR-ALL-NEURAL-NETWORKS", "(DEFUN CLEAR-ALL-NEURAL-NETWORKS () :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&clearAllNeuralNetworks)), NULL);
    defineFunctionObject("CLEAR-ALL-SLOPES", "(DEFUN CLEAR-ALL-SLOPES ())", ((cpp_function_code)(&clearAllSlopes)), NULL);
    defineFunctionObject("CLEAR-SLOPES", "(DEFUN CLEAR-SLOPES ((NET PROPOSITION-NEURAL-NETWORK)))", ((cpp_function_code)(&clearSlopes)), NULL);
    defineFunctionObject("RANDOMIZE-NEURAL-NETWORK", "(DEFUN RANDOMIZE-NEURAL-NETWORK ((NET PROPOSITION-NEURAL-NETWORK)))", ((cpp_function_code)(&randomizeNeuralNetwork)), NULL);
    defineFunctionObject("CREATE-NEURAL-NETWORK", "(DEFUN (CREATE-NEURAL-NETWORK PROPOSITION-NEURAL-NETWORK) ((PROP PROPOSITION)))", ((cpp_function_code)(&createNeuralNetwork)), NULL);
    defineFunctionObject("GNP", "(DEFUN (GNP PROPOSITION) ((NAME SYMBOL)) :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :PUBLIC? TRUE)", ((cpp_function_code)(&gnp)), NULL);
    defineFunctionObject("DEFNETWORK", "(DEFUN (DEFNETWORK PROPOSITION-NEURAL-NETWORK) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE)", ((cpp_function_code)(&defnetwork)), ((cpp_function_code)(&defnetworkEvaluatorWrapper)));
    defineFunctionObject("DEFINE-NEURAL-NETWORK-FROM-PARSE-TREE", "(DEFUN (DEFINE-NEURAL-NETWORK-FROM-PARSE-TREE PROPOSITION-NEURAL-NETWORK) ((TREE CONS)))", ((cpp_function_code)(&defineNeuralNetworkFromParseTree)), NULL);
    defineFunctionObject("ALLOCATE-NEURAL-NETWORK", "(DEFUN (ALLOCATE-NEURAL-NETWORK PROPOSITION-NEURAL-NETWORK) ((NUM-IN INTEGER) (NUM-HIDDEN INTEGER)))", ((cpp_function_code)(&allocateNeuralNetwork)), NULL);
    defineFunctionObject("ACTIVATE-PROPOSITIONAL-NEURAL-NETWORK", "(DEFUN (ACTIVATE-PROPOSITIONAL-NEURAL-NETWORK FLOAT) ((NET PROPOSITION-NEURAL-NETWORK)))", ((cpp_function_code)(&activatePropositionalNeuralNetwork)), NULL);
    defineFunctionObject("MAKE-NET-INPUT-STRING", "(DEFUN (MAKE-NET-INPUT-STRING STRING) ((INPUT WEIGHT-VECTOR)))", ((cpp_function_code)(&makeNetInputString)), NULL);
    defineFunctionObject("TRAIN-NEURAL-NETWORK", "(DEFUN TRAIN-NEURAL-NETWORK ((CYCLES INTEGER) (NUM-TRAINING INTEGER)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&trainNeuralNetwork)), ((cpp_function_code)(&trainNeuralNetworkEvaluatorWrapper)));
    defineFunctionObject("TRAIN-UNCACHED-NEURAL-NETWORKS", "(DEFUN TRAIN-UNCACHED-NEURAL-NETWORKS ((CYCLES INTEGER) (NUM-TRAINING INTEGER)))", ((cpp_function_code)(&trainUncachedNeuralNetworks)), NULL);
    defineFunctionObject("BACKPROPAGATE-ERROR", "(DEFUN BACKPROPAGATE-ERROR ((PROP PROPOSITION) (ERROR FLOAT)))", ((cpp_function_code)(&backpropagateError)), NULL);
    defineFunctionObject("QUICKPROPAGATE-ERROR", "(DEFUN QUICKPROPAGATE-ERROR ((PROP PROPOSITION) (ERROR FLOAT)))", ((cpp_function_code)(&quickpropagateError)), NULL);
    defineFunctionObject("COMPUTE-ERROR", "(DEFUN (COMPUTE-ERROR FLOAT) ((TRAINING FLOAT) (OUTPUT FLOAT)))", ((cpp_function_code)(&computeError)), NULL);
    defineFunctionObject("COMPUTE-DELTA", "(DEFUN (COMPUTE-DELTA FLOAT) ((SLOPE FLOAT) (PREV-SLOPE FLOAT) (PREV-DELTA FLOAT)))", ((cpp_function_code)(&computeDelta)), NULL);
    defineFunctionObject("COMPUTE-QP-DELTA", "(DEFUN (COMPUTE-QP-DELTA FLOAT) ((SLOPE FLOAT) (PREV-SLOPE FLOAT) (PREV-DELTA FLOAT)))", ((cpp_function_code)(&computeQpDelta)), NULL);
    defineFunctionObject("MODIFY-WEIGHTS", "(DEFUN MODIFY-WEIGHTS ())", ((cpp_function_code)(&modifyWeights)), NULL);
    defineFunctionObject("TEST-OVER-TRAINING-EXAMPLES", "(DEFUN (TEST-OVER-TRAINING-EXAMPLES FLOAT) () :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&testOverTrainingExamples)), ((cpp_function_code)(&testOverTrainingExamplesEvaluatorWrapper)));
    defineFunctionObject("TRAIN-AND-TEST-NEURAL-NETWORK", "(DEFUN (TRAIN-AND-TEST-NEURAL-NETWORK FLOAT) ((CYCLES INTEGER) (NUM-TRAINING INTEGER) (NUM-TESTING INTEGER)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&trainAndTestNeuralNetwork)), ((cpp_function_code)(&trainAndTestNeuralNetworkEvaluatorWrapper)));
    defineFunctionObject("TEST-NEURAL-NETWORK", "(DEFUN (TEST-NEURAL-NETWORK FLOAT) () :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&testNeuralNetwork)), ((cpp_function_code)(&testNeuralNetworkEvaluatorWrapper)));
    defineFunctionObject("MULTIPLE-NETWORK-TRAINING-RUNS", "(DEFUN (MULTIPLE-NETWORK-TRAINING-RUNS FLOAT) ((RUNS INTEGER) (CYCLES INTEGER) (NUM-TRAINING INTEGER)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&multipleNetworkTrainingRuns)), ((cpp_function_code)(&multipleNetworkTrainingRunsEvaluatorWrapper)));
    defineFunctionObject("TRAIN-CACHED-NEURAL-NETWORKS", "(DEFUN TRAIN-CACHED-NEURAL-NETWORKS ((CYCLES INTEGER) (NUM-TRAINING INTEGER)))", ((cpp_function_code)(&trainCachedNeuralNetworks)), NULL);
    defineFunctionObject("CACHED-BACKPROPAGATE-ERROR", "(DEFUN CACHED-BACKPROPAGATE-ERROR ((TREE CONS) (ERROR FLOAT)))", ((cpp_function_code)(&cachedBackpropagateError)), NULL);
    defineFunctionObject("CACHED-QUICKPROPAGATE-ERROR", "(DEFUN CACHED-QUICKPROPAGATE-ERROR ((TREE CONS) (ERROR FLOAT)))", ((cpp_function_code)(&cachedQuickpropagateError)), NULL);
    defineFunctionObject("CREATE-CACHED-NETWORK", "(DEFUN (CREATE-CACHED-NETWORK CONS) ((CONS-QUERY CONS)))", ((cpp_function_code)(&createCachedNetwork)), NULL);
    defineFunctionObject("BUILD-NETWORK-TREE", "(DEFUN (BUILD-NETWORK-TREE PARSE-TREE) ((PROP PROPOSITION) (PROP-LIST (CONS OF PROPOSITION))))", ((cpp_function_code)(&buildNetworkTree)), NULL);
    defineFunctionObject("ACTIVATE-CACHED-NETWORK", "(DEFUN (ACTIVATE-CACHED-NETWORK FLOAT) ((TREE (CONS OF CONS))))", ((cpp_function_code)(&activateCachedNetwork)), NULL);
    defineFunctionObject("RANDOM-WEIGHT", "(DEFUN (RANDOM-WEIGHT FLOAT) ((N FLOAT)))", ((cpp_function_code)(&randomWeight)), NULL);
    defineFunctionObject("RANDOM-FLOAT", "(DEFUN (RANDOM-FLOAT FLOAT) ((N FLOAT)) :PUBLIC? TRUE :DOCUMENTATION \"Generate a random integer in the interval [0..n-1].\n'n' must be <= 2^15.\")", ((cpp_function_code)(&randomFloat)), NULL);
    defineFunctionObject("CONS-TO-VECTOR", "(DEFUN (CONS-TO-VECTOR VECTOR) ((FORM CONS)))", ((cpp_function_code)(&consToVector)), NULL);
    defineFunctionObject("CREATE-VECTOR", "(DEFUN (CREATE-VECTOR VECTOR) (|&REST| (VALUES OBJECT)) :DOCUMENTATION \"Return a vector containing 'values', in order.\" :PUBLIC? TRUE)", ((cpp_function_code)(&createVector)), NULL);
    defineFunctionObject("ZERO-VECTOR", "(DEFUN ZERO-VECTOR ((V WEIGHT-VECTOR)))", ((cpp_function_code)(&zeroVector)), NULL);
    defineFunctionObject("STRUCTURED-NEURAL-NETWORK-REGRESSION", "(DEFUN STRUCTURED-NEURAL-NETWORK-REGRESSION ((CLASS-NAME SYMBOL) (SLOT-NAME SYMBOL) (CYCLES INTEGER)) :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :PUBLIC? TRUE)", ((cpp_function_code)(&structuredNeuralNetworkRegression)), ((cpp_function_code)(&structuredNeuralNetworkRegressionEvaluatorWrapper)));
    defineFunctionObject("GET-NN-NEAREST-NEIGHBORS", "(DEFUN (GET-NN-NEAREST-NEIGHBORS (LIST OF TRAINING-EXAMPLE)) ((PROBE TRAINING-EXAMPLE) (CASES (LIST OF TRAINING-EXAMPLE)) (K INTEGER)))", ((cpp_function_code)(&getNnNearestNeighbors)), NULL);
    defineFunctionObject("SWAP-IN-NEW-NETWORKS", "(DEFUN SWAP-IN-NEW-NETWORKS ((OLD-NETS (LIST OF PROPOSITION-NEURAL-NETWORK)) (NEW-NETS (LIST OF PROPOSITION-NEURAL-NETWORK))) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&swapInNewNetworks)), NULL);
    defineFunctionObject("SWAP-IN-NETWORK-FILE", "(DEFUN SWAP-IN-NETWORK-FILE ((FILE STRING)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&swapInNetworkFile)), ((cpp_function_code)(&swapInNetworkFileEvaluatorWrapper)));
    defineFunctionObject("LOAD-NEURAL-NETWORK-FILE", "(DEFUN (LOAD-NEURAL-NETWORK-FILE (LIST OF PROPOSITION-NEURAL-NETWORK)) ((FILE STRING)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&loadNeuralNetworkFile)), ((cpp_function_code)(&loadNeuralNetworkFileEvaluatorWrapper)));
    defineFunctionObject("SAVE-ALL-NEURAL-NETWORKS", "(DEFUN SAVE-ALL-NEURAL-NETWORKS ((FILE STRING)) :DOCUMENTATION \"Save all neural networks to `file' (if `file' is non-NULL).\nIf networks are saved periodically (see `set-save-network-cycle') this file\nname will be used to perform periodic saves.\" :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&saveAllNeuralNetworks)), ((cpp_function_code)(&saveAllNeuralNetworksEvaluatorWrapper)));
    defineFunctionObject("SAVE-NEURAL-NETWORK", "(DEFUN SAVE-NEURAL-NETWORK ((NET PROPOSITION-NEURAL-NETWORK) (FILE STRING)) :COMMAND? TRUE :PUBLIC? TRUE)", ((cpp_function_code)(&saveNeuralNetwork)), ((cpp_function_code)(&saveNeuralNetworkEvaluatorWrapper)));
    defineFunctionObject("PRINT-NEURAL-NETWORK", "(DEFUN PRINT-NEURAL-NETWORK ((NET PROPOSITION-NEURAL-NETWORK) (STREAM OUTPUT-STREAM)))", ((cpp_function_code)(&printNeuralNetwork)), NULL);
    defineFunctionObject("CREATE-HIDDEN-SIGNATURE", "(DEFUN (CREATE-HIDDEN-SIGNATURE WEIGHT-VECTOR) ((CONS-QUERY CONS)))", ((cpp_function_code)(&createHiddenSignature)), NULL);
    defineFunctionObject("INITIALIZE-2_D_ARRAY", "(DEFUN INITIALIZE-2_D_ARRAY ((SELF 2_D_ARRAY)))", ((cpp_function_code)(&initialize2_D_array)), NULL);
    defineMethodObject("(DEFMETHOD (2_D_ELEMENT (LIKE (ANY-VALUE SELF))) ((ARRAY 2_D_ARRAY) (ROW INTEGER) (COLUMN INTEGER)) :DOCUMENTATION \"Return the element of `array' at position [`row', `column'].\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (NTH (THE-ARRAY ARRAY) (+ (* ROW (NOF-COLUMNS ARRAY)) COLUMN))))", wrapMethodCode(((cpp_method_code)(&two_D_array::two_D_element))), NULL);
    defineMethodObject("(DEFMETHOD (2_D_ELEMENT-SETTER (LIKE (ANY-VALUE SELF))) ((ARRAY 2_D_ARRAY) (VALUE OBJECT) (ROW INTEGER) (COLUMN INTEGER)) :DOCUMENTATION \"Set the element of `array' at position [`row', `column']\nto `value' and return the result.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (SETF (NTH (THE-ARRAY ARRAY) (+ (* ROW (NOF-COLUMNS ARRAY)) COLUMN)) VALUE)))", wrapMethodCode(((cpp_method_code)(&two_D_array::two_D_elementSetter))), NULL);
    defineFunctionObject("CREATE-2_D_ARRAY", "(DEFUN (CREATE-2_D_ARRAY 2_D_ARRAY) ((NOF-ROWS INTEGER) (NOF-COLUMNS INTEGER) |&REST| (VALUES OBJECT)) :DOCUMENTATION \"Create a two-dimensional array with `nof-rows' rows and\n`nof-columns' columns, and initialize it in row-major-order from `values'.\nMissing values will be padded with NULL, extraneous values will be ignored.\" :PUBLIC? TRUE)", ((cpp_function_code)(&create2_D_array)), NULL);
    defineMethodObject("(DEFMETHOD FILL-ARRAY ((SELF 2_D_ARRAY) |&REST| (VALUES OBJECT)) :DOCUMENTATION \"Fill the two-dimensional array `self' in row-major-order\nfrom `values'.  Missing values will retain their old values, extraneous values\nwill be ignored.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&two_D_array::fillArray))), NULL);
    defineMethodObject("(DEFMETHOD PRINT-ARRAY ((SELF 2_D_ARRAY) (STREAM NATIVE-OUTPUT-STREAM)) :DOCUMENTATION \"Print the array `self' to `stream'.\")", wrapMethodCode(((cpp_method_code)(&two_D_array::printArray))), NULL);
  }
}

void startupNeuralNetwork() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupNeuralNetwork1();
    }
    if (currentStartupTimePhaseP(4)) {
      oNEURAL_NETWORK_TRAINING_METHODo = KWD_NEURAL_NETWORK_BACKPROP;
      oSAVE_NETWORK_FILEo = NULL;
      oSHRINK_FACTORo = oMAX_MOVEMENTo / (1.0 + oMAX_MOVEMENTo);
      oMASTER_NEURAL_NETWORK_LISTo = newList();
      oACTIVATED_NETWORKSo = newList();
      oPARTIAL_SUPPORT_CACHEo = newList();
    }
    if (currentStartupTimePhaseP(5)) {
      helpStartupNeuralNetwork2();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupNeuralNetwork3();
      defineFunctionObject("INITIALIZE-FLOAT-VECTOR", "(DEFUN INITIALIZE-FLOAT-VECTOR ((SELF FLOAT-VECTOR)))", ((cpp_function_code)(&initializeFloatVector)), NULL);
      defineFunctionObject("CREATE-FLOAT-VECTOR", "(DEFUN (CREATE-FLOAT-VECTOR FLOAT-VECTOR) (|&REST| (VALUES FLOAT)) :DOCUMENTATION \"Return a vector containing 'values', in order.\" :PUBLIC? TRUE)", ((cpp_function_code)(&createFloatVector)), NULL);
      defineMethodObject("(DEFMETHOD PRINT-VECTOR ((SELF FLOAT-VECTOR) (STREAM NATIVE-OUTPUT-STREAM)))", wrapMethodCode(((cpp_method_code)(&FloatVector::printVector))), NULL);
      defineMethodObject("(DEFMETHOD (EMPTY? BOOLEAN) ((SELF FLOAT-VECTOR)) :DOCUMENTATION \"Return TRUE if 'self' has length 0.\" :GLOBALLY-INLINE? TRUE (RETURN (EQL? (ARRAY-SIZE SELF) 0)))", wrapMethodCode(((cpp_method_code)(&FloatVector::emptyP))), NULL);
      defineMethodObject("(DEFMETHOD (NON-EMPTY? BOOLEAN) ((SELF FLOAT-VECTOR)) :DOCUMENTATION \"Return TRUE if 'self' has length > 0.\" :GLOBALLY-INLINE? TRUE (RETURN (> (ARRAY-SIZE SELF) 0)))", wrapMethodCode(((cpp_method_code)(&FloatVector::nonEmptyP))), NULL);
      defineMethodObject("(DEFMETHOD (NTH FLOAT) ((SELF FLOAT-VECTOR) (POSITION INTEGER)) :GLOBALLY-INLINE? TRUE (RETURN (SAFE-CAST (NTH (THE-ARRAY SELF) POSITION) FLOAT-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&FloatVector::nth))), NULL);
      defineMethodObject("(DEFMETHOD (NTH-SETTER FLOAT) ((SELF FLOAT-VECTOR) (VALUE FLOAT) (POSITION INTEGER)) :GLOBALLY-INLINE? TRUE (RETURN (SETF (WRAPPER-VALUE (SAFE-CAST (NTH (THE-ARRAY SELF) POSITION) FLOAT-WRAPPER)) VALUE)))", wrapMethodCode(((cpp_method_code)(&FloatVector::nthSetter))), NULL);
      defineMethodObject("(DEFMETHOD (LENGTH INTEGER) ((SELF FLOAT-VECTOR)) :GLOBALLY-INLINE? TRUE (RETURN (ARRAY-SIZE SELF)))", wrapMethodCode(((cpp_method_code)(&FloatVector::length))), NULL);
      defineMethodObject("(DEFMETHOD (MEMBER? BOOLEAN) ((SELF FLOAT-VECTOR) (OBJECT FLOAT)))", wrapMethodCode(((cpp_method_code)(&FloatVector::memberP))), NULL);
      defineFunctionObject("INITIALIZE-2_D_FLOAT-ARRAY", "(DEFUN INITIALIZE-2_D_FLOAT-ARRAY ((SELF 2_D_FLOAT-ARRAY)))", ((cpp_function_code)(&initialize2_D_floatArray)), NULL);
      defineMethodObject("(DEFMETHOD (2_D_ELEMENT FLOAT) ((ARRAY 2_D_FLOAT-ARRAY) (ROW INTEGER) (COLUMN INTEGER)) :DOCUMENTATION \"Return the element of `array' at position [`row', `column'].\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (SAFE-CAST (NTH (THE-ARRAY ARRAY) (+ (* ROW (NOF-COLUMNS ARRAY)) COLUMN)) FLOAT-WRAPPER)))", wrapMethodCode(((cpp_method_code)(&two_D_floatArray::two_D_element))), NULL);
      defineMethodObject("(DEFMETHOD (2_D_ELEMENT-SETTER (LIKE (ANY-VALUE SELF))) ((ARRAY 2_D_FLOAT-ARRAY) (VALUE FLOAT) (ROW INTEGER) (COLUMN INTEGER)) :DOCUMENTATION \"Set the element of `array' at position [`row', `column']\nto `value' and return the result.\" :GLOBALLY-INLINE? TRUE :PUBLIC? TRUE (RETURN (SETF (WRAPPER-VALUE (SAFE-CAST (NTH (THE-ARRAY ARRAY) (+ (* ROW (NOF-COLUMNS ARRAY)) COLUMN)) FLOAT-WRAPPER)) VALUE)))", wrapMethodCode(((cpp_method_code)(&two_D_floatArray::two_D_elementSetter))), NULL);
      defineFunctionObject("CREATE-2_D_FLOAT-ARRAY", "(DEFUN (CREATE-2_D_FLOAT-ARRAY 2_D_FLOAT-ARRAY) ((NOF-ROWS INTEGER) (NOF-COLUMNS INTEGER) |&REST| (VALUES FLOAT)) :DOCUMENTATION \"Create a two-dimensional array with `nof-rows' rows and\n`nof-columns' columns, and initialize it in row-major-order from `values'.\nMissing values will be padded with NULL, extraneous values will be ignored.\" :PUBLIC? TRUE)", ((cpp_function_code)(&create2_D_floatArray)), NULL);
      defineMethodObject("(DEFMETHOD FILL-ARRAY ((SELF 2_D_FLOAT-ARRAY) |&REST| (VALUES FLOAT)) :DOCUMENTATION \"Fill the two-dimensional array `self' in row-major-order\nfrom `values'.  Missing values will retain their old values, extraneous values\nwill be ignored.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&two_D_floatArray::fillArray))), NULL);
      defineMethodObject("(DEFMETHOD PRINT-ARRAY ((SELF 2_D_FLOAT-ARRAY) (STREAM NATIVE-OUTPUT-STREAM)) :DOCUMENTATION \"Print the array `self' to `stream'.\")", wrapMethodCode(((cpp_method_code)(&two_D_floatArray::printArray))), NULL);
      defineFunctionObject("STARTUP-NEURAL-NETWORK", "(DEFUN STARTUP-NEURAL-NETWORK () :PUBLIC? TRUE)", ((cpp_function_code)(&startupNeuralNetwork)), NULL);
      { MethodSlot* function = lookupFunction(SYM_NEURAL_NETWORK_LOGIC_STARTUP_NEURAL_NETWORK);

        setDynamicSlotValue(function->dynamicSlots, SYM_NEURAL_NETWORK_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupNeuralNetwork"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFGLOBAL *NEURAL-NETWORK-TRAINING-METHOD* KEYWORD :BACKPROP)", &oNEURAL_NETWORK_TRAINING_METHODo);
      defineGlobalVariableObject("(DEFGLOBAL *LEARNING-RATE* FLOAT 0.1)", &oLEARNING_RATEo);
      defineGlobalVariableObject("(DEFGLOBAL *MOMENTUM-TERM* FLOAT 0.9)", &oMOMENTUM_TERMo);
      defineGlobalVariableObject("(DEFGLOBAL *WEIGHT-RANGE* FLOAT 0.05)", &oWEIGHT_RANGEo);
      defineGlobalVariableObject("(DEFGLOBAL *ERROR-CUTOFF* FLOAT 0.0)", &oERROR_CUTOFFo);
      defineGlobalVariableObject("(DEFGLOBAL *ERROR-PRINT-CYCLE* INTEGER 25)", &oERROR_PRINT_CYCLEo);
      defineGlobalVariableObject("(DEFGLOBAL *SAVE-NETWORK-CYCLE* INTEGER 10000)", &oSAVE_NETWORK_CYCLEo);
      defineGlobalVariableObject("(DEFGLOBAL *SAVE-NETWORK-FILE* STRING NULL)", &oSAVE_NETWORK_FILEo);
      defineGlobalVariableObject("(DEFGLOBAL *TRACE-NEURAL-NETWORK-TRAINING* BOOLEAN FALSE)", &oTRACE_NEURAL_NETWORK_TRAININGo);
      defineGlobalVariableObject("(DEFGLOBAL *TRAIN-CACHED-NETWORKS?* BOOLEAN TRUE)", &oTRAIN_CACHED_NETWORKSpo);
      defineGlobalVariableObject("(DEFGLOBAL *MAX-MOVEMENT* FLOAT 1.75)", &oMAX_MOVEMENTo);
      defineGlobalVariableObject("(DEFGLOBAL *MODE-SWITCH* FLOAT 0.0)", &oMODE_SWITCHo);
      defineGlobalVariableObject("(DEFGLOBAL *SHRINK-FACTOR* FLOAT (/ *MAX-MOVEMENT* (+ 1.0 *MAX-MOVEMENT*)))", &oSHRINK_FACTORo);
      defineGlobalVariableObject("(DEFGLOBAL *WEIGHT-DECAY* FLOAT -1.0e-4)", &oWEIGHT_DECAYo);
      defineGlobalVariableObject("(DEFGLOBAL *SIGMOID-PRIME-OFFSET* FLOAT 0.1)", &oSIGMOID_PRIME_OFFSETo);
      defineGlobalVariableObject("(DEFGLOBAL *MASTER-NEURAL-NETWORK-LIST* (LIST OF PROPOSITION-NEURAL-NETWORK) (NEW LIST))", &oMASTER_NEURAL_NETWORK_LISTo);
      defineGlobalVariableObject("(DEFGLOBAL *ACTIVATED-NETWORKS* (LIST OF PROPOSITION-NEURAL-NETWORK) (NEW LIST))", &oACTIVATED_NETWORKSo);
      defineGlobalVariableObject("(DEFGLOBAL *SAVED-NET* PROPOSITION-NEURAL-NETWORK NULL)", &oSAVED_NETo);
      defineGlobalVariableObject("(DEFGLOBAL *PARTIAL-SUPPORT-CACHE* (LIST OF INTEGER-WRAPPER) (NEW LIST))", &oPARTIAL_SUPPORT_CACHEo);
      defineGlobalVariableObject("(DEFGLOBAL *LEARNING-CURVE* (VECTOR OF FLOAT-WRAPPER) NULL)", &oLEARNING_CURVEo);
    }
  }
}

Keyword* KWD_NEURAL_NETWORK_BACKPROP = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_WEIGHT_VECTOR = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_2_D_WEIGHT_ARRAY = NULL;

Surrogate* SGT_NEURAL_NETWORK_LOGIC_PROPOSITION_NEURAL_NETWORK = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_PROPOSITION = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_INPUT = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_HIDDEN = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_OUTPUT = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_INPUT_ERROR = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_HIDDEN_ERROR = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_IH = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_IH_DELTA = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_HO = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_HO_DELTA = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_IH_SLOPE = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_IH_PREV_SLOPE = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_HO_SLOPE = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_HO_PREV_SLOPE = NULL;

Keyword* KWD_NEURAL_NETWORK_AND = NULL;

Keyword* KWD_NEURAL_NETWORK_OR = NULL;

Keyword* KWD_NEURAL_NETWORK_QUICKPROP = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE = NULL;

Keyword* KWD_NEURAL_NETWORK_BACKPROPAGATION = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_NEURAL_NET = NULL;

Keyword* KWD_NEURAL_NETWORK_MAX = NULL;

Keyword* KWD_NEURAL_NETWORK_NOISY_OR = NULL;

Surrogate* SGT_NEURAL_NETWORK_STELLA_CONS = NULL;

Surrogate* SGT_NEURAL_NETWORK_LOGIC_PROPOSITION = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_DEFNETWORK = NULL;

Keyword* KWD_NEURAL_NETWORK_MATCH_MODE = NULL;

Keyword* KWD_NEURAL_NETWORK_NN = NULL;

Keyword* KWD_NEURAL_NETWORK_MAXIMIZE_SCOREp = NULL;

Surrogate* SGT_NEURAL_NETWORK_LOGIC_MULTI_DIMENSIONAL_ARRAY = NULL;

Surrogate* SGT_NEURAL_NETWORK_LOGIC_2_D_ARRAY = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_NOF_ROWS = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_NOF_COLUMNS = NULL;

Surrogate* SGT_NEURAL_NETWORK_LOGIC_FLOAT_VECTOR = NULL;

Symbol* SYM_NEURAL_NETWORK_STELLA_ARRAY_SIZE = NULL;

Surrogate* SGT_NEURAL_NETWORK_LOGIC_2_D_FLOAT_ARRAY = NULL;

Symbol* SYM_NEURAL_NETWORK_LOGIC_STARTUP_NEURAL_NETWORK = NULL;

Symbol* SYM_NEURAL_NETWORK_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
