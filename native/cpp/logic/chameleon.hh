//  -*- Mode: C++ -*-

// chameleon.hh

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
class ChameleonPartialMatch : public IncrementalPartialMatch {
// Variant of :BASIC partial match strategy to support CHAMELEON queries.
public:
  // Holds justifications for OR arguments and alternative rules.
  Cons* argumentJustifications;
  // Holds argument propositions in the order they are associated with scores
  Cons* argumentPropositions;
public:
  virtual Surrogate* primaryType();
  virtual double computePartialTruth(QueryIterator* query);
  virtual Keyword* continuePartialAntecedentsProof(Keyword* lastmove);
  virtual Keyword* continuePartialStrategiesProofs(Keyword* lastmove);
  virtual double computeGoalScore();
  virtual Keyword* continuePartialFailProof(Keyword* lastmove);
  virtual Keyword* continuePartialNotProof(Keyword* lastmove);
  virtual double computeNotScore();
  virtual Keyword* continuePartialOrProof(Keyword* lastmove);
  virtual double computeOrScore();
  virtual Keyword* continuePartialAndProof(ControlFrame* frame, Keyword* lastmove);
  virtual double computeAndScore();
  virtual boolean allowUnboundVariablesP();
  virtual void popOrPartialMatchScore();
  virtual void pushOrPartialMatchScore(double score, double weight);
  virtual void popAndPartialMatchScore();
  virtual void pushAndPartialMatchScore(double score, double weight);
  virtual double propositionWeight(Proposition* proposition);
  virtual double invertMatchScore(double score);
  virtual double truthValueScore(TruthValue* truthvalue);
  virtual boolean cutoffPartialMatchP(boolean traceP);
  virtual double computeDynamicCutoff();
  virtual PartialMatchFrame* createPartialMatchFrame(ControlFrame* frame, Keyword* kind);
};

class ChameleonNeuralNetwork : public NeuralNetwork {
// Stream-lined neural network structure that doesn't require float wrapping.
public:
  Proposition* proposition;
  oneDFloatArray* input;
  oneDFloatArray* hidden;
  double output;
  twoDFloatArray* ih;
  oneDFloatArray* ho;
  oneDFloatArray* inputError;
  oneDFloatArray* hiddenError;
  double outputError;
  twoDFloatArray* ihDelta;
  oneDFloatArray* hoDelta;
public:
  virtual Surrogate* primaryType();
  virtual void updateNetworkWeights(double error);
  virtual void backwardPropagateError(double error);
  virtual double forwardPropagateInputs();
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
  virtual Proposition* getNeuralNetworkProposition();
  virtual void unlinkNeuralNetwork();
  virtual void linkNeuralNetwork(Proposition* prop);
};

class VectorNeuralNetwork : public NeuralNetwork {
// Neural network that supports vector input arguments.
public:
  int nVectorArguments;
  int nVectorArgumentSpecs;
  int nVectorArgumentInputs;
public:
  virtual Surrogate* primaryType();
  virtual Object* getVectorArgumentSpec(Object* arg);
  virtual void setVectorInputValues(Object* vectorspecs);
  virtual int numberOfVectorArgumentInputs(Proposition* prop);
  virtual int numberOfVectorArgumentSpecs(Proposition* prop);
  virtual int vectorArgumentIndex(Proposition* arg);
  virtual int numberOfVectorArguments(Proposition* prop);
  virtual boolean hasVectorArgumentsP();
  virtual boolean vectorArgumentP(Proposition* arg);
};

class TensorflowNeuralNetwork : public VectorNeuralNetwork {
// Neural network that is implemented by callbacks to TensorFlow.
public:
  Proposition* proposition;
  LongIntegerWrapper* model;
public:
  virtual Surrogate* primaryType();
  virtual void updateNetworkWeights(double error);
  virtual void backwardPropagateError(double error);
  virtual double forwardPropagateInputs();
  virtual void setVectorInputValues(Object* vectorspecs);
  virtual Object* getVectorArgumentSpec(Object* arg);
  virtual void setInputValues(Object* values);
  virtual double nthInputError(int n);
  virtual double nthInput(int n);
  virtual int numberOfInputs();
  virtual void buildPropositionNetwork(Proposition* prop);
  virtual void initializeNetworkWeights();
  virtual void randomizeNetworkWeights();
  virtual void allocateNetworkArrays(int numIn, int numHidden, int numOut);
  virtual boolean deletedP();
  virtual void deleteNeuralNetwork();
  virtual Proposition* getNeuralNetworkProposition();
  virtual void unlinkNeuralNetwork();
  virtual void linkNeuralNetwork(Proposition* prop);
};

class ChameleonBatchNeuralNetwork : public ChameleonNeuralNetwork {
// Chameleon neural network that supports batch operations via emulation.
public:
  // Each element is a set of values that may be legally passed to `set-input-values'.
  VectorSequence* inputBatch;
  // Each element is a key to identify a specific set of input values.
  VectorSequence* keyBatch;
  // Each element is a target output value for the respective set of input values.
  VectorSequence* targetBatch;
  oneDFloatArray* outputBatch;
  // Copies of `input-error' but without the bias unit, thus shifted by 1.
  VectorSequence* inputErrorBatch;
public:
  virtual Surrogate* primaryType();
  virtual void batchUpdateNetworkWeights();
  virtual void batchBackwardPropagateError();
  virtual oneDFloatArray* copyInputError();
  virtual oneDFloatArray* batchForwardPropagateInputs();
  virtual double nthBatchOutput(int n);
  virtual double nthKthBatchInputError(int n, int k);
  virtual Object* nthBatchKey(int n);
  virtual void pushTargetValue(double value);
  virtual void pushInputValues(Object* key, Object* values);
  virtual boolean batchIsFullP();
  virtual int currentBatchSize();
  virtual void clearBatchArrays();
  virtual void allocateNetworkArrays(int numIn, int numHidden, int numOut);
};

class twoDLongArray : public AbstractDimensionalArray {
// 2-dimensional array with long integer values.
public:
  int dim2;
  int dim1;
  long long int* theArray;
public:
  virtual Surrogate* primaryType();
  virtual long long int* theArrayReader();
  virtual void initializeDimensionalArray();
  virtual void initializeArray(long long int initialvalue);
  virtual long long int oneDAref(int i);
  virtual long long int oneDArefSetter(long long int value, int i);
  virtual int oneDArefAddress(int i);
  virtual int length();
  virtual long long int twoDAref(int i, int j);
  virtual long long int twoDArefSetter(long long int value, int i, int j);
  virtual int twoDArefAddress(int i, int j);
};

class TensorflowBatchNeuralNetwork : public TensorflowNeuralNetwork {
// Tensorflow neural network that supports batch operations.  We implement input and result
// batches as 1-D and 2-D float arrays to enable fast back-and-forth copying in a single shot instead of having
// multiple method calls.  For this reason, we maintain the input and target sequences manually.
public:
  // Cleared by Python/Tensorflow side, used to avoid unnecessary copying.
  boolean inputModifiedP;
  // Each row is a set of inputs for the input units of the network, including the bias.
  twoDFloatArray* inputBatch;
  int inputBatchLength;
  // Each element is a key to identify a specific set of input values.
  VectorSequence* keyBatch;
  // Each row is a set of vector argument specs for the inputs of the network.
  twoDLongArray* vectorBatch;
  int vectorBatchLength;
  // Each element is a target output value for the respective set of input values.
  oneDFloatArray* targetBatch;
  int targetBatchLength;
  oneDFloatArray* outputBatch;
  // Each row is a set of errors the respective inputs including the bias.
  twoDFloatArray* inputErrorBatch;
public:
  virtual Surrogate* primaryType();
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
  virtual double forwardPropagateInputs();
  virtual void setVectorInputValues(Object* vectorspecs);
  virtual Object* getVectorArgumentSpec(Object* arg);
  virtual void setInputValues(Object* values);
  virtual double nthInputError(int n);
  virtual double nthInput(int n);
  virtual int numberOfInputs();
  virtual void buildPropositionNetwork(Proposition* prop);
  virtual void allocateNetworkArrays(int numIn, int numHidden, int numOut);
  virtual void printNetworkArrays();
};

class NetworkProofQueue : public StandardObject {
public:
  // Map from computation prerequisites to their dependents.
  KeyValueMap* dependents;
  // Map from dependents to their computation prerequisites.
  KeyValueMap* prerequisites;
  HashSet* activeNetworks;
  int minBatchSize;
  int nQueued;
public:
  virtual Surrogate* primaryType();
  virtual void executeAll();
  virtual void queueInputValues(NeuralNetwork* net, Justification* proof, Object* inputs, Object* vectorspecs);
  virtual void notifyOfCompletion(Justification* proof, Justification* prerequisite);
  virtual void executeNetworkOperation(NeuralNetwork* net, boolean forceP);
  virtual void queueNetworkOperation(Justification* proof);
  virtual void batchProcessCachedNetworkProof(Justification* proof);
  virtual boolean hasPrerequisiteP(Justification* dependent, Justification* prerequisite);
  virtual Cons* getPrerequisites(Justification* dependent);
  virtual boolean hasDependentP(Justification* prerequisite, Justification* dependent);
  virtual Cons* getDependents(Justification* prerequisite);
  virtual void removeDependent(Justification* prerequisite, Justification* dependent);
  virtual void addDependent(Justification* prerequisite, Justification* dependent);
};

class NetworkProofForwardQueue : public NetworkProofQueue {
public:
  virtual Surrogate* primaryType();
  virtual void executeNetworkOperation(NeuralNetwork* net, boolean forceP);
  virtual void queueNetworkOperation(Justification* proof);
  virtual void batchProcessCachedNetworkProof(Justification* proof);
};

class NetworkProofBackwardQueue : public NetworkProofQueue {
public:
  virtual Surrogate* primaryType();
  virtual void executeNetworkOperation(NeuralNetwork* net, boolean forceP);
  virtual void queueNetworkOperation(Justification* proof);
  virtual void batchProcessCachedNetworkProof(Justification* proof);
};

class NetworkProofUpdateQueue : public NetworkProofQueue {
public:
  virtual Surrogate* primaryType();
  virtual void executeNetworkOperation(NeuralNetwork* net, boolean forceP);
  virtual void queueNetworkOperation(Justification* proof);
  virtual void batchProcessCachedNetworkProof(Justification* proof);
};

class ScoredQueryProofAdjunct : public ProofAdjunct {
public:
  PartialMatchFrame* partialMatchStrategy;
  ControlFrame* downFrame;
public:
  virtual Surrogate* primaryType();
};


// Global declarations:
extern Module* oCHAMELEON_MODULEo;
extern double oCHAMELEON_DEFAULT_DEFAULT_SCOREo;
extern KeyValueMap* oALL_NEURAL_NETWORKSo;
extern Keyword* oCHAMELEON_NEURAL_NETWORK_IMPLEMENTATIONo;
extern double oCHAMELEON_DEFAULT_INPUT_VALUEo;
extern FloatWrapper* oWRAPPED_CHAMELEON_DEFAULT_INPUT_VALUEo;
extern int oNEURAL_NETWORK_BATCH_SIZEo;
extern int oBATCH_OPERATION_COUNTo;
extern int oBATCH_TOTAL_COUNTo;

// Function signatures:
void ensureChameleonOntology();
Module* getChameleonModule();
boolean chameleonVectorRelationP(Object* x);
boolean chameleonIgnoredValueRelationP(Object* x);
boolean chameleonTruthValueRelationP(Object* x);
boolean chameleonPrimitiveValueRelationP(Object* x);
ChameleonPartialMatch* newChameleonPartialMatch(Keyword* kind, ControlFrame* controlFrame);
Object* accessChameleonPartialMatchSlotValue(ChameleonPartialMatch* self, Symbol* slotname, Object* value, boolean setvalueP);
boolean chameleonPartialMatchModeP();
double invertChameleonMatchScore(double score);
void registerNeuralNetwork(NeuralNetwork* self);
void unregisterNeuralNetwork(NeuralNetwork* self);
NeuralNetwork* lookupPropositionNeuralNetwork(Proposition* prop);
void deleteNeuralNetworks();
void randomizeNeuralNetworks();
void createAndLinkNeuralNetwork(Proposition* prop);
NeuralNetwork* getPropositionNeuralNetwork(Proposition* prop, boolean errorP);
NeuralNetwork* getJustificationNeuralNetwork(Justification* just);
int helpComputeArgumentIndex(NeuralNetwork* self, Proposition* arg, Keyword* kind);
ChameleonNeuralNetwork* newChameleonNeuralNetwork();
Object* accessChameleonNeuralNetworkSlotValue(ChameleonNeuralNetwork* self, Symbol* slotname, Object* value, boolean setvalueP);
void copyFloatValuesToBuffer(Object* values, double* buffer, int start, int end);
VectorNeuralNetwork* newVectorNeuralNetwork();
Object* accessVectorNeuralNetworkSlotValue(VectorNeuralNetwork* self, Symbol* slotname, Object* value, boolean setvalueP);
TensorflowNeuralNetwork* newTensorflowNeuralNetwork();
Object* accessTensorflowNeuralNetworkSlotValue(TensorflowNeuralNetwork* self, Symbol* slotname, Object* value, boolean setvalueP);
void registerTensorflowCallback(const char* name, cpp_function_code code);
cpp_function_code getTensorflowCallback(Symbol* name);
boolean tensorflowBackendAvailableP();
Justification* getCachedNetworkProof(TrainingExample* example);
Justification* compactPartialProofToNetworkProof(Justification* proof);
double combineMultipleMatchScores(Cons* scores);
double forwardPropagateCachedNetworkProof(Justification* proof);
double forwardPropagateCachedNetworkFromJustification(Justification* just);
void backwardPropagateCachedNetworkProof(Justification* proof, double error);
void backwardPropagateCachedNetworkMultiProof(Justification* proof, double error);
ChameleonBatchNeuralNetwork* newChameleonBatchNeuralNetwork();
Object* accessChameleonBatchNeuralNetworkSlotValue(ChameleonBatchNeuralNetwork* self, Symbol* slotname, Object* value, boolean setvalueP);
twoDLongArray* new2DLongArray(int dim2, int dim1);
TensorflowBatchNeuralNetwork* newTensorflowBatchNeuralNetwork();
Object* accessTensorflowBatchNeuralNetworkSlotValue(TensorflowBatchNeuralNetwork* self, Symbol* slotname, Object* value, boolean setvalueP);
NetworkProofQueue* newNetworkProofQueue();
Object* accessNetworkProofQueueSlotValue(NetworkProofQueue* self, Symbol* slotname, Object* value, boolean setvalueP);
NetworkProofForwardQueue* newNetworkProofForwardQueue();
NetworkProofBackwardQueue* newNetworkProofBackwardQueue();
NetworkProofUpdateQueue* newNetworkProofUpdateQueue();
void addNetworkProofDependencyLink(KeyValueMap* table, Justification* subject, Justification* object);
void removeNetworkProofDependencyLink(KeyValueMap* table, Justification* subject, Justification* object);
List* retrieveTrainingExamples(Cons* options);
List* retrieveTrainingExamplesEvaluatorWrapper(Cons* arguments);
Vector* selectTrainingExamples(Cons* options);
Vector* selectTrainingExamplesEvaluatorWrapper(Cons* arguments);
PropertyList* normalizeChameleonTrainingOptions(Object* options);
void trainChameleonNeuralNetworks(Cons* options);
void trainChameleonNeuralNetworksEvaluatorWrapper(Cons* arguments);
ScoredQueryProofAdjunct* newScoredQueryProofAdjunct();
Object* accessScoredQueryProofAdjunctSlotValue(ScoredQueryProofAdjunct* self, Symbol* slotname, Object* value, boolean setvalueP);
Keyword* scoredQuerySpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* matchScoreSpecialist(ControlFrame* frame, Keyword* lastmove);
void helpStartupChameleon1();
void helpStartupChameleon2();
void helpStartupChameleon3();
void helpStartupChameleon4();
void helpStartupChameleon5();
void helpStartupChameleon6();
void helpStartupChameleon7();
void startupChameleon();

// Auxiliary global declarations:
extern Surrogate* SGT_CHAMELEON_CHAMELEON_TRUTH_VALUE_RELATION;
extern Surrogate* SGT_CHAMELEON_CHAMELEON_VECTOR_RELATION;
extern Surrogate* SGT_CHAMELEON_CHAMELEON_IGNORED_VALUE_RELATION;
extern Surrogate* SGT_CHAMELEON_CHAMELEON_PRIMITIVE_VALUE_RELATION;
extern Surrogate* SGT_CHAMELEON_LOGIC_CHAMELEON_PARTIAL_MATCH;
extern Symbol* SYM_CHAMELEON_LOGIC_ARGUMENT_JUSTIFICATIONS;
extern Symbol* SYM_CHAMELEON_LOGIC_ARGUMENT_PROPOSITIONS;
extern Keyword* KWD_CHAMELEON_AND;
extern Keyword* KWD_CHAMELEON_OR;
extern Keyword* KWD_CHAMELEON_ATOMIC_GOAL;
extern Keyword* KWD_CHAMELEON_UP_TRUE;
extern Keyword* KWD_CHAMELEON_UP_FAIL;
extern Keyword* KWD_CHAMELEON_DOWN;
extern Symbol* SYM_CHAMELEON_LOGIC_JUSTIFICATION;
extern Keyword* KWD_CHAMELEON_GOAL_TREE;
extern Keyword* KWD_CHAMELEON_OR_INTRODUCTION;
extern Keyword* KWD_CHAMELEON_FAILURE;
extern Keyword* KWD_CHAMELEON_OTHER;
extern Keyword* KWD_CHAMELEON_VARIANT1;
extern Keyword* KWD_CHAMELEON_FINAL_SUCCESS;
extern Keyword* KWD_CHAMELEON_VARIANT2;
extern Symbol* SYM_CHAMELEON_LOGIC_ANTECEDENTS_RULE;
extern Keyword* KWD_CHAMELEON_MULTIPLE_PROOFS;
extern Keyword* KWD_CHAMELEON_TECHNICAL;
extern Keyword* KWD_CHAMELEON_LAY;
extern Keyword* KWD_CHAMELEON_MINIMUM_SCORE;
extern Keyword* KWD_CHAMELEON_MAXIMIZE_SCOREp;
extern Keyword* KWD_CHAMELEON_RECORD_JUSTIFICATIONSp;
extern Surrogate* SGT_CHAMELEON_STELLA_BOOLEAN;
extern Keyword* KWD_CHAMELEON_NOISY_OR;
extern Keyword* KWD_CHAMELEON_ORIGINAL;
extern Symbol* SYM_CHAMELEON_LOGIC_NEURAL_NET;
extern Keyword* KWD_CHAMELEON_PROPOSITION;
extern Keyword* KWD_CHAMELEON_CHAMELEON;
extern Keyword* KWD_CHAMELEON_CHAMELEON_BATCH;
extern Keyword* KWD_CHAMELEON_TENSORFLOW;
extern Keyword* KWD_CHAMELEON_TENSORFLOW_BATCH;
extern Keyword* KWD_CHAMELEON_NOT;
extern Keyword* KWD_CHAMELEON_FAIL;
extern Surrogate* SGT_CHAMELEON_LOGIC_PROPOSITION;
extern Keyword* KWD_CHAMELEON_TRUTH_VALUE;
extern Keyword* KWD_CHAMELEON_IGNORED_VALUE;
extern Keyword* KWD_CHAMELEON_VECTOR;
extern Surrogate* SGT_CHAMELEON_LOGIC_M_NEURAL_NETWORKdTRUTH_VALUE_ARGUMENT_INDEX_MEMO_TABLE_000;
extern Keyword* KWD_CHAMELEON_QUICKPROP;
extern Surrogate* SGT_CHAMELEON_STELLA_CONS;
extern Surrogate* SGT_CHAMELEON_STELLA_LIST;
extern Surrogate* SGT_CHAMELEON_STELLA_VECTOR;
extern Surrogate* SGT_CHAMELEON_STELLA_SEQUENCE;
extern Surrogate* SGT_CHAMELEON_STELLA_ITERATOR;
extern Surrogate* SGT_CHAMELEON_LOGIC_CHAMELEON_NEURAL_NETWORK;
extern Symbol* SYM_CHAMELEON_LOGIC_PROPOSITION;
extern Symbol* SYM_CHAMELEON_LOGIC_INPUT;
extern Symbol* SYM_CHAMELEON_LOGIC_HIDDEN;
extern Symbol* SYM_CHAMELEON_LOGIC_OUTPUT;
extern Symbol* SYM_CHAMELEON_LOGIC_IH;
extern Symbol* SYM_CHAMELEON_LOGIC_HO;
extern Symbol* SYM_CHAMELEON_LOGIC_INPUT_ERROR;
extern Symbol* SYM_CHAMELEON_LOGIC_HIDDEN_ERROR;
extern Symbol* SYM_CHAMELEON_LOGIC_OUTPUT_ERROR;
extern Symbol* SYM_CHAMELEON_LOGIC_IH_DELTA;
extern Symbol* SYM_CHAMELEON_LOGIC_HO_DELTA;
extern Surrogate* SGT_CHAMELEON_STELLA_FLOAT_ARRAY;
extern Surrogate* SGT_CHAMELEON_LOGIC_VECTOR_NEURAL_NETWORK;
extern Symbol* SYM_CHAMELEON_LOGIC_N_VECTOR_ARGUMENTS;
extern Symbol* SYM_CHAMELEON_LOGIC_N_VECTOR_ARGUMENT_SPECS;
extern Symbol* SYM_CHAMELEON_LOGIC_N_VECTOR_ARGUMENT_INPUTS;
extern Surrogate* SGT_CHAMELEON_LOGIC_M_VECTOR_NEURAL_NETWORKdVECTOR_ARGUMENT_INDEX_MEMO_TABLE_000;
extern Surrogate* SGT_CHAMELEON_CHAMELEON_VECTOR_ARITY;
extern Surrogate* SGT_CHAMELEON_CHAMELEON_VECTOR_DIMENSIONS;
extern Surrogate* SGT_CHAMELEON_LOGIC_JUSTIFICATION;
extern Surrogate* SGT_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORK;
extern Symbol* SYM_CHAMELEON_LOGIC_MODEL;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdBUILD_PROPOSITION_NETWORK;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdALLOCATE_NETWORK_ARRAYS;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdRANDOMIZE_NETWORK_WEIGHTS;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdINITIALIZE_NETWORK_WEIGHTS;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdNUMBER_OF_INPUTS;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdNTH_INPUT;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdNTH_INPUT_ERROR;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdSET_INPUT_VALUES;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdSET_VECTOR_INPUT_VALUES;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdFORWARD_PROPAGATE_INPUTS;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdBACKWARD_PROPAGATE_ERROR;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_NEURAL_NETWORKdUPDATE_NETWORK_WEIGHTS;
extern Keyword* KWD_CHAMELEON_MATCH_MODE;
extern Keyword* KWD_CHAMELEON_WARNING;
extern Keyword* KWD_CHAMELEON_PRIMITIVE_STRATEGY;
extern Keyword* KWD_CHAMELEON_GOAL_COMPLEMENT;
extern Keyword* KWD_CHAMELEON_AND_INTRODUCTION;
extern Keyword* KWD_CHAMELEON_DISPROOF;
extern Keyword* KWD_CHAMELEON_MODUS_PONENS;
extern Keyword* KWD_CHAMELEON_MODUS_TOLLENS;
extern Keyword* KWD_CHAMELEON_SUBSUMPTION_REASONING;
extern Keyword* KWD_CHAMELEON_FAIL_INTRODUCTION;
extern Keyword* KWD_CHAMELEON_MAX;
extern Surrogate* SGT_CHAMELEON_LOGIC_CHAMELEON_BATCH_NEURAL_NETWORK;
extern Symbol* SYM_CHAMELEON_LOGIC_INPUT_BATCH;
extern Symbol* SYM_CHAMELEON_LOGIC_KEY_BATCH;
extern Symbol* SYM_CHAMELEON_LOGIC_TARGET_BATCH;
extern Symbol* SYM_CHAMELEON_LOGIC_OUTPUT_BATCH;
extern Symbol* SYM_CHAMELEON_LOGIC_INPUT_ERROR_BATCH;
extern Surrogate* SGT_CHAMELEON_LOGIC_2D_LONG_ARRAY;
extern Surrogate* SGT_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORK;
extern Symbol* SYM_CHAMELEON_LOGIC_INPUT_MODIFIEDp;
extern Symbol* SYM_CHAMELEON_LOGIC_INPUT_BATCH_LENGTH;
extern Symbol* SYM_CHAMELEON_LOGIC_VECTOR_BATCH;
extern Symbol* SYM_CHAMELEON_LOGIC_VECTOR_BATCH_LENGTH;
extern Symbol* SYM_CHAMELEON_LOGIC_TARGET_BATCH_LENGTH;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_FORWARD_PROPAGATE_INPUTS;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_BACKWARD_PROPAGATE_ERROR;
extern Symbol* SYM_CHAMELEON_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_UPDATE_NETWORK_WEIGHTS;
extern Surrogate* SGT_CHAMELEON_LOGIC_NETWORK_PROOF_QUEUE;
extern Symbol* SYM_CHAMELEON_LOGIC_DEPENDENTS;
extern Symbol* SYM_CHAMELEON_LOGIC_PREREQUISITES;
extern Symbol* SYM_CHAMELEON_LOGIC_ACTIVE_NETWORKS;
extern Symbol* SYM_CHAMELEON_LOGIC_MIN_BATCH_SIZE;
extern Symbol* SYM_CHAMELEON_LOGIC_N_QUEUED;
extern Surrogate* SGT_CHAMELEON_LOGIC_NETWORK_PROOF_FORWARD_QUEUE;
extern Surrogate* SGT_CHAMELEON_LOGIC_NETWORK_PROOF_BACKWARD_QUEUE;
extern Surrogate* SGT_CHAMELEON_LOGIC_NETWORK_PROOF_UPDATE_QUEUE;
extern Keyword* KWD_CHAMELEON_MODULE;
extern Surrogate* SGT_CHAMELEON_STELLA_MODULE;
extern Keyword* KWD_CHAMELEON_LOCALp;
extern Keyword* KWD_CHAMELEON_N_TRAIN;
extern Surrogate* SGT_CHAMELEON_STELLA_INTEGER;
extern Symbol* SYM_CHAMELEON_CHAMELEON_TRAINING_EXAMPLE;
extern Symbol* SYM_CHAMELEON_LOGIC_pP;
extern Symbol* SYM_CHAMELEON_LOGIC_pS;
extern Keyword* KWD_CHAMELEON_SHUFFLEp;
extern Keyword* KWD_CHAMELEON_OPTIONS;
extern Keyword* KWD_CHAMELEON_EPOCHS;
extern Keyword* KWD_CHAMELEON_PRINT_CYCLE;
extern Keyword* KWD_CHAMELEON_ERROR_CUTOFF;
extern Surrogate* SGT_CHAMELEON_STELLA_FLOAT;
extern Keyword* KWD_CHAMELEON_BATCHp;
extern Keyword* KWD_CHAMELEON_EXAMPLES;
extern Surrogate* SGT_CHAMELEON_STELLA_OBJECT;
extern Surrogate* SGT_CHAMELEON_LOGIC_SCORED_QUERY_PROOF_ADJUNCT;
extern Symbol* SYM_CHAMELEON_LOGIC_PARTIAL_MATCH_STRATEGY;
extern Symbol* SYM_CHAMELEON_LOGIC_DOWN_FRAME;
extern Symbol* SYM_CHAMELEON_LOGIC_PROOF_ADJUNCT;
extern Keyword* KWD_CHAMELEON_TERMINAL_FAILURE;
extern Keyword* KWD_CHAMELEON_MOVE_DOWN;
extern Surrogate* SGT_CHAMELEON_STELLA_NUMBER_WRAPPER;
extern Keyword* KWD_CHAMELEON_SCORED_QUERY;
extern Keyword* KWD_CHAMELEON_CONTINUING_SUCCESS;
extern Keyword* KWD_CHAMELEON_MATCH_SCORE;
extern Symbol* SYM_CHAMELEON_LOGIC_STARTUP_CHAMELEON;
extern Symbol* SYM_CHAMELEON_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
