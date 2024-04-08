//  -*- Mode: C++ -*-

// machine-learning.hh

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
class TrainingExample : public StandardObject {
// A single example of a proposition paired with the score
//   that should be returned and the module it should be evaluated in.
public:
  Cons* query;
  Symbol* concept;
  Symbol* name;
  double score;
  Module* module;
  List* inputFeatures;
  Vector* input;
  Cons* facts;
  Vector* nnHidden;
  Object* output;
  double temp;
  Object* cachedSolution;
  int timestamp;
public:
  virtual Surrogate* primaryType();
};


// Global declarations:
extern List* oTRAINING_EXAMPLESo;
extern List* oTESTING_EXAMPLESo;
extern boolean oCLOSED_WORLD_TRAINING_EXAMPLESo;
extern int oMAX_STRUCTURE_DEPTHo;
extern boolean oDROP_FUNCTION_VALUESpo;
extern List* oTABOO_OPERATORSo;

// Function signatures:
TrainingExample* newTrainingExample();
Object* accessTrainingExampleSlotValue(TrainingExample* self, Symbol* slotname, Object* value, boolean setvalueP);
void setClosedWorldTrainingExamples(boolean b);
void setClosedWorldTrainingExamplesEvaluatorWrapper(Cons* arguments);
void printTrainingExample(TrainingExample* example);
void addTrainingExample(Cons* form, double score);
void addTrainingExampleEvaluatorWrapper(Cons* arguments);
void addTrainingExampleInModule(Cons* form, double score, Symbol* module);
void addTrainingExampleInModuleEvaluatorWrapper(Cons* arguments);
void addTestingExample(Cons* form, double score);
void addTestingExampleEvaluatorWrapper(Cons* arguments);
void clearTrainingExamples();
void shuffleList(List* cards);
void shuffleVector(Vector* cards);
void saveTrainingExamples();
int createPropositionalTrainingExamples(List* examples, OutputFileStream* nameFile, OutputFileStream* dataFile);
void fillInExampleOutputs(List* examples, Symbol* slotName);
void detectNoiseInTrainingExamples(List* examples);
List* getClassificationRelations(Cons* consQuery);
Vector* createInputSignature(Cons* consQuery);
void generateClassificationRule(Vector* instances, Symbol* conceptName, Symbol* className, boolean buildRuleP);
void buildClassificationRule(Symbol* kind, Symbol* className);
int oldGenerateClassificationTrainingExamples(Vector* instances, Surrogate* concept);
void testDomainTheory(Symbol* relationName, Symbol* className);
double testTheoryOverExamples(List* examples);
int generateTrainingExamples(Vector* instances, Surrogate* concept);
int generateClassificationTrainingExamples(Vector* instances, Surrogate* concept, boolean createSignatureP);
void generateRegressionRuleWoSlot(Vector* cases, Symbol* slotName, Symbol* className, boolean reallyBuildRule);
int generateRegressionTrainingExamples(Vector* instances, Surrogate* slot);
double approximate(Symbol* instName, Symbol* slotName);
FloatWrapper* approximateEvaluatorWrapper(Cons* arguments);
double generateSlotApproximation(Symbol* instName, Surrogate* slot);
boolean floatFunctionP(Surrogate* relation);
void setStructureDepth(int d);
void setStructureDepthEvaluatorWrapper(Cons* arguments);
void addTabooOperators(Symbol* s);
List* getAssertionStructure(Symbol* inst, int depth);
List* helpGetAssertionStructure(Symbol* inst, int depth);
void collectFactsInExamples(List* examples);
Cons* oldRecursiveBuildAntecedent(Symbol* inst, int depth);
Object* getArgumentBinding(Object* arg);
Object* consifyArgument(Object* arg);
Cons* propositionToCons(Proposition* prop);
void thingifyUntypedInstances();
void helpStartupMachineLearning1();
void startupMachineLearning();

// Auxiliary global declarations:
extern Surrogate* SGT_MACHINE_LEARNING_LOGIC_TRAINING_EXAMPLE;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_QUERY;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_CONCEPT;
extern Symbol* SYM_MACHINE_LEARNING_STELLA_NAME;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_SCORE;
extern Symbol* SYM_MACHINE_LEARNING_STELLA_MODULE;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_INPUT_FEATURES;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_INPUT;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_FACTS;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_NN_HIDDEN;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_OUTPUT;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_TEMP;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_CACHED_SOLUTION;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_TIMESTAMP;
extern Keyword* KWD_MACHINE_LEARNING_MATCH_MODE;
extern Keyword* KWD_MACHINE_LEARNING_BASIC;
extern Keyword* KWD_MACHINE_LEARNING_MAXIMIZE_SCOREp;
extern Symbol* SYM_MACHINE_LEARNING_STELLA_TRUE;
extern Keyword* KWD_MACHINE_LEARNING_MOVEOUT;
extern Keyword* KWD_MACHINE_LEARNING_RETRACT_TRUE;
extern Keyword* KWD_MACHINE_LEARNING_ASSERT_TRUE;
extern Keyword* KWD_MACHINE_LEARNING_RETRACT_FALSE;
extern Keyword* KWD_MACHINE_LEARNING_ASSERT_FALSE;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_DEFRELATION;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_pP;
extern Symbol* SYM_MACHINE_LEARNING_STELLA_THING;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_DEFRULE;
extern Symbol* SYM_MACHINE_LEARNING_STELLA_FORALL;
extern Symbol* SYM_MACHINE_LEARNING_STELLA_eg;
extern Symbol* SYM_MACHINE_LEARNING_STELLA_AND;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_pY;
extern Symbol* SYM_MACHINE_LEARNING_STELLA_NOT;
extern Surrogate* SGT_MACHINE_LEARNING_STELLA_FLOAT;
extern Keyword* KWD_MACHINE_LEARNING_ISA;
extern Keyword* KWD_MACHINE_LEARNING_FUNCTION;
extern Surrogate* SGT_MACHINE_LEARNING_STELLA_NUMBER_WRAPPER;
extern Symbol* SYM_MACHINE_LEARNING_STELLA_ge;
extern Symbol* SYM_MACHINE_LEARNING_STELLA_el;
extern Symbol* SYM_MACHINE_LEARNING_STELLA_e;
extern Surrogate* SGT_MACHINE_LEARNING_STELLA_SYMBOL;
extern Surrogate* SGT_MACHINE_LEARNING_LOGIC_DESCRIPTION;
extern Surrogate* SGT_MACHINE_LEARNING_LOGIC_SKOLEM;
extern Surrogate* SGT_MACHINE_LEARNING_LOGIC_LOGIC_OBJECT;
extern Surrogate* SGT_MACHINE_LEARNING_LOGIC_PROPOSITION;
extern Surrogate* SGT_MACHINE_LEARNING_LOGIC_PATTERN_VARIABLE;
extern Surrogate* SGT_MACHINE_LEARNING_LOGIC_NAMED_DESCRIPTION;
extern Keyword* KWD_MACHINE_LEARNING_IN;
extern Keyword* KWD_MACHINE_LEARNING_PREDICATE;
extern Keyword* KWD_MACHINE_LEARNING_EQUIVALENT;
extern Keyword* KWD_MACHINE_LEARNING_FORALL;
extern Keyword* KWD_MACHINE_LEARNING_EXISTS;
extern Symbol* SYM_MACHINE_LEARNING_STELLA_OR;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_IO_VARIABLES;
extern Surrogate* SGT_MACHINE_LEARNING_STELLA_THING;
extern Symbol* SYM_MACHINE_LEARNING_LOGIC_STARTUP_MACHINE_LEARNING;
extern Symbol* SYM_MACHINE_LEARNING_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
