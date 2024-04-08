//  -*- Mode: C++ -*-

// neural-network.hh

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
class NeuralNetwork : public StandardObject {
public:
  virtual void batchUpdateNetworkWeights();
  virtual void batchBackwardPropagateError();
  virtual oneDFloatArray* batchForwardPropagateInputs();
  virtual double nthBatchOutput(int n);
  virtual double nthKthBatchInputError(int n, int k);
  virtual Object* nthBatchKey(int n);
  virtual void pushTargetValue(double value);
  virtual void pushVectorInputValues(Object* vectorspecs);
  virtual void pushInputValues(Object* key, Object* values);
  virtual boolean batchIsFullP();
  virtual int currentBatchSize();
  virtual void clearBatchArrays();
  virtual void updateNetworkWeights(double error);
  virtual void backwardPropagateError(double error);
  virtual double forwardPropagateInputs();
  virtual Object* getVectorArgumentSpec(Object* arg);
  virtual void setVectorInputValues(Object* vectorspecs);
  virtual void setInputValues(Object* values);
  virtual double nthInputError(int n);
  virtual double nthInput(int n);
  virtual int numberOfInputs();
  virtual void buildPropositionNetwork(Proposition* prop);
  virtual void randomizeNetworkWeights();
  virtual void allocateNetworkArrays(int numIn, int numHidden, int numOut);
  virtual boolean deletedP();
  virtual void deleteNeuralNetwork();
  virtual void unlinkNeuralNetwork();
  virtual void linkNeuralNetwork(Proposition* prop);
  virtual int vectorArgumentIndex(Proposition* arg);
  virtual int numberOfVectorArguments(Proposition* prop);
  virtual boolean hasVectorArgumentsP();
  virtual boolean vectorArgumentP(Proposition* arg);
  virtual int numberOfIgnoredValueArguments(Proposition* prop);
  virtual boolean ignoredValueArgumentP(Proposition* arg);
  virtual int truthValueArgumentIndex(Proposition* arg);
  virtual int numberOfTruthValueArguments(Proposition* prop);
  virtual boolean truthValueArgumentP(Proposition* arg);
  virtual Proposition* getNeuralNetworkProposition();
};

class PropositionNeuralNetwork : public NeuralNetwork {
public:
  Proposition* proposition;
  Vector* input;
  Vector* hidden;
  double output;
  Vector* inputError;
  Vector* hiddenError;
  two_D_array* ih;
  two_D_array* ihDelta;
  Vector* ho;
  Vector* hoDelta;
  two_D_array* ihSlope;
  two_D_array* ihPrevSlope;
  Vector* hoSlope;
  Vector* hoPrevSlope;
public:
  virtual Surrogate* primaryType();
  virtual void updateNetworkWeights(double error);
  virtual void backwardPropagateError(double error);
  virtual double forwardPropagateInputs();
  virtual void setInputValues(Object* values);
  virtual double nthInputError(int n);
  virtual double nthInput(int n);
  virtual int numberOfInputs();
  virtual void buildPropositionNetwork(Proposition* prop);
  virtual void randomizeNetworkWeights();
  virtual void allocateNetworkArrays(int numIn, int numHidden, int numOut);
  virtual boolean deletedP();
  virtual void deleteNeuralNetwork();
  virtual Proposition* getNeuralNetworkProposition();
  virtual void unlinkNeuralNetwork();
  virtual void linkNeuralNetwork(Proposition* prop);
};

class MultiDimensionalArray : public AbstractCollection {
public:
  virtual Surrogate* primaryType();
};

class two_D_array : public MultiDimensionalArray {
// Two-dimensional arrays with elements of type OBJECT.
public:
  int nofRows;
  int nofColumns;
  Object** theArray;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
  virtual void printArray(std::ostream* stream);
  virtual void fillArray(int values, ...);
  virtual Object* two_D_elementSetter(Object* value, int row, int column);
  virtual Object* two_D_element(int row, int column);
};

class FloatVector : public AbstractCollection {
public:
  int arraySize;
  Object** theArray;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
  virtual boolean memberP(double object);
  virtual int length();
  virtual double nthSetter(double value, int position);
  virtual double nth(int position);
  virtual boolean nonEmptyP();
  virtual boolean emptyP();
  virtual void printVector(std::ostream* stream);
};

class two_D_floatArray : public MultiDimensionalArray {
// Two-dimensional arrays with elements of type FLOAT.
public:
  int nofRows;
  int nofColumns;
  Object** theArray;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
  virtual void printArray(std::ostream* stream);
  virtual void fillArray(int values, ...);
  virtual double two_D_elementSetter(double value, int row, int column);
  virtual double two_D_element(int row, int column);
};


// Global declarations:
extern Keyword* oNEURAL_NETWORK_TRAINING_METHODo;
extern double oLEARNING_RATEo;
extern double oMOMENTUM_TERMo;
extern double oWEIGHT_RANGEo;
extern double oERROR_CUTOFFo;
extern int oERROR_PRINT_CYCLEo;
extern int oSAVE_NETWORK_CYCLEo;
extern const char* oSAVE_NETWORK_FILEo;
extern boolean oTRACE_NEURAL_NETWORK_TRAININGo;
extern boolean oTRAIN_CACHED_NETWORKSpo;
extern double oMAX_MOVEMENTo;
extern double oMODE_SWITCHo;
extern double oSHRINK_FACTORo;
extern double oWEIGHT_DECAYo;
extern double oSIGMOID_PRIME_OFFSETo;
extern List* oMASTER_NEURAL_NETWORK_LISTo;
extern List* oACTIVATED_NETWORKSo;
extern PropositionNeuralNetwork* oSAVED_NETo;
extern List* oPARTIAL_SUPPORT_CACHEo;
extern Vector* oLEARNING_CURVEo;

// Function signatures:
PropositionNeuralNetwork* newPropositionNeuralNetwork();
Object* accessPropositionNeuralNetworkSlotValue(PropositionNeuralNetwork* self, Symbol* slotname, Object* value, boolean setvalueP);
void setTraceNeuralNetworkTraining(boolean b);
void setTraceNeuralNetworkTrainingEvaluatorWrapper(Cons* arguments);
void setSaveNetworkCycle(int i);
void setSaveNetworkCycleEvaluatorWrapper(Cons* arguments);
void setErrorCutoff(double f);
void setErrorCutoffEvaluatorWrapper(Cons* arguments);
void setTrainCachedNeuralNetworks(boolean b);
void setTrainCachedNeuralNetworksEvaluatorWrapper(Cons* arguments);
void setLearningRate(double rate);
void setLearningRateEvaluatorWrapper(Cons* arguments);
void setMomentumTerm(double m);
void setMomentumTermEvaluatorWrapper(Cons* arguments);
void setWeightRange(double w);
void setWeightRangeEvaluatorWrapper(Cons* arguments);
void setNeuralNetworkTrainingMethod(Keyword* m);
void setErrorPrintCycle(int i);
void setErrorPrintCycleEvaluatorWrapper(Cons* arguments);
void deleteAllNeuralNetworks();
void checkMasterNetworkList();
void clearAllNeuralNetworks();
void clearAllSlopes();
void clearSlopes(PropositionNeuralNetwork* net);
void randomizeNeuralNetwork(PropositionNeuralNetwork* net);
PropositionNeuralNetwork* createNeuralNetwork(Proposition* prop);
Proposition* gnp(Symbol* name);
PropositionNeuralNetwork* defnetwork(Cons* args);
PropositionNeuralNetwork* defnetworkEvaluatorWrapper(Cons* arguments);
PropositionNeuralNetwork* defineNeuralNetworkFromParseTree(Cons* tree);
PropositionNeuralNetwork* allocateNeuralNetwork(int numIn, int numHidden);
double activatePropositionalNeuralNetwork(PropositionNeuralNetwork* net);
const char* makeNetInputString(Vector* input);
void trainNeuralNetwork(int cycles, int numTraining);
void trainNeuralNetworkEvaluatorWrapper(Cons* arguments);
void trainUncachedNeuralNetworks(int cycles, int numTraining);
void backpropagateError(Proposition* prop, double error);
void quickpropagateError(Proposition* prop, double error);
double computeError(double training, double output);
double computeDelta(double slope, double prevSlope, double prevDelta);
double computeQpDelta(double slope, double prevSlope, double prevDelta);
void modifyWeights();
double testOverTrainingExamples();
FloatWrapper* testOverTrainingExamplesEvaluatorWrapper(Cons* arguments);
double trainAndTestNeuralNetwork(int cycles, int numTraining, int numTesting);
FloatWrapper* trainAndTestNeuralNetworkEvaluatorWrapper(Cons* arguments);
double testNeuralNetwork();
FloatWrapper* testNeuralNetworkEvaluatorWrapper(Cons* arguments);
double multipleNetworkTrainingRuns(int runs, int cycles, int numTraining);
FloatWrapper* multipleNetworkTrainingRunsEvaluatorWrapper(Cons* arguments);
void trainCachedNeuralNetworks(int cycles, int numTraining);
void cachedBackpropagateError(Cons* tree, double error);
void cachedQuickpropagateError(Cons* tree, double error);
Cons* createCachedNetwork(Cons* consQuery);
Object* buildNetworkTree(Proposition* prop, Cons* propList);
double activateCachedNetwork(Cons* tree);
double randomWeight(double n);
double randomFloat(double n);
Vector* consToVector(Cons* form);
Vector* createVector(int values, ...);
void zeroVector(Vector* v);
void structuredNeuralNetworkRegression(Symbol* className, Symbol* slotName, int cycles);
void structuredNeuralNetworkRegressionEvaluatorWrapper(Cons* arguments);
List* getNnNearestNeighbors(TrainingExample* probe, List* cases, int k);
void swapInNewNetworks(List* oldNets, List* newNets);
void swapInNetworkFile(const char* file);
void swapInNetworkFileEvaluatorWrapper(Cons* arguments);
List* loadNeuralNetworkFile(const char* file);
List* loadNeuralNetworkFileEvaluatorWrapper(Cons* arguments);
void saveAllNeuralNetworks(const char* file);
void saveAllNeuralNetworksEvaluatorWrapper(Cons* arguments);
void saveNeuralNetwork(PropositionNeuralNetwork* net, const char* file);
void saveNeuralNetworkEvaluatorWrapper(Cons* arguments);
void printNeuralNetwork(PropositionNeuralNetwork* net, OutputStream* stream);
Vector* createHiddenSignature(Cons* consQuery);
MultiDimensionalArray* newMultiDimensionalArray();
two_D_array* new2_D_array(int nofRows, int nofColumns);
Object* access2_D_arraySlotValue(two_D_array* self, Symbol* slotname, Object* value, boolean setvalueP);
void initialize2_D_array(two_D_array* self);
two_D_array* create2_D_array(int nofRows, int nofColumns, int values, ...);
FloatVector* newFloatVector(int arraySize);
Object* accessFloatVectorSlotValue(FloatVector* self, Symbol* slotname, Object* value, boolean setvalueP);
void initializeFloatVector(FloatVector* self);
FloatVector* createFloatVector(int values, ...);
two_D_floatArray* new2_D_floatArray(int nofRows, int nofColumns);
Object* access2_D_floatArraySlotValue(two_D_floatArray* self, Symbol* slotname, Object* value, boolean setvalueP);
void initialize2_D_floatArray(two_D_floatArray* self);
two_D_floatArray* create2_D_floatArray(int nofRows, int nofColumns, int values, ...);
void helpStartupNeuralNetwork1();
void helpStartupNeuralNetwork2();
void helpStartupNeuralNetwork3();
void startupNeuralNetwork();

// Auxiliary global declarations:
extern Keyword* KWD_NEURAL_NETWORK_BACKPROP;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_WEIGHT_VECTOR;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_2_D_WEIGHT_ARRAY;
extern Surrogate* SGT_NEURAL_NETWORK_LOGIC_PROPOSITION_NEURAL_NETWORK;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_PROPOSITION;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_INPUT;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_HIDDEN;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_OUTPUT;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_INPUT_ERROR;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_HIDDEN_ERROR;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_IH;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_IH_DELTA;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_HO;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_HO_DELTA;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_IH_SLOPE;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_IH_PREV_SLOPE;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_HO_SLOPE;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_HO_PREV_SLOPE;
extern Keyword* KWD_NEURAL_NETWORK_AND;
extern Keyword* KWD_NEURAL_NETWORK_OR;
extern Keyword* KWD_NEURAL_NETWORK_QUICKPROP;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_MATCH_SCORE;
extern Keyword* KWD_NEURAL_NETWORK_BACKPROPAGATION;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_NEURAL_NET;
extern Keyword* KWD_NEURAL_NETWORK_MAX;
extern Keyword* KWD_NEURAL_NETWORK_NOISY_OR;
extern Surrogate* SGT_NEURAL_NETWORK_STELLA_CONS;
extern Surrogate* SGT_NEURAL_NETWORK_LOGIC_PROPOSITION;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_DEFNETWORK;
extern Keyword* KWD_NEURAL_NETWORK_MATCH_MODE;
extern Keyword* KWD_NEURAL_NETWORK_NN;
extern Keyword* KWD_NEURAL_NETWORK_MAXIMIZE_SCOREp;
extern Surrogate* SGT_NEURAL_NETWORK_LOGIC_MULTI_DIMENSIONAL_ARRAY;
extern Surrogate* SGT_NEURAL_NETWORK_LOGIC_2_D_ARRAY;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_NOF_ROWS;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_NOF_COLUMNS;
extern Surrogate* SGT_NEURAL_NETWORK_LOGIC_FLOAT_VECTOR;
extern Symbol* SYM_NEURAL_NETWORK_STELLA_ARRAY_SIZE;
extern Surrogate* SGT_NEURAL_NETWORK_LOGIC_2_D_FLOAT_ARRAY;
extern Symbol* SYM_NEURAL_NETWORK_LOGIC_STARTUP_NEURAL_NETWORK;
extern Symbol* SYM_NEURAL_NETWORK_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
