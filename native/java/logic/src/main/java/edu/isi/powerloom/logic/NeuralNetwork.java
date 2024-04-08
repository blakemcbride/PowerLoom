//  -*- Mode: Java -*-
//
// NeuralNetwork.java

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

package edu.isi.powerloom.logic;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;

public abstract class NeuralNetwork extends StandardObject {
  /** Run weight updates for the current input and target batches.
   */
  public void batchUpdateNetworkWeights() {
    { NeuralNetwork self = this;

      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("batch-update-network-weights: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Run backward propagation on the current input and target batch and store back-propagated
   * errors in the input error batch.
   */
  public void batchBackwardPropagateError() {
    { NeuralNetwork self = this;

      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("batch-backward-propagate-error: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Run forward propagation on the current input batch and store outputs in the output batch.
   * @return oneDFloatArray
   */
  public oneDFloatArray batchForwardPropagateInputs() {
    { NeuralNetwork self = this;

      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("batch-forward-propagate-inputs: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Return the output value for the <code>n</code>-th set of inputs in the input batch.
   * @param n
   * @return double
   */
  public double nthBatchOutput(int n) {
    { NeuralNetwork self = this;

      n = n;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("nth-batch-output: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Return error of the <code>k</code>-th input in the <code>n</code>-th set of inputs in the input batch.
   * <code>k</code> ignores the bias unit.
   * @param n
   * @param k
   * @return double
   */
  public double nthKthBatchInputError(int n, int k) {
    { NeuralNetwork self = this;

      {
        n = n;
        k = k;
      }
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("nth-kth-batch-input-error: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Return the key associated with the <code>n</code>-th set of inputs in the input batch.
   * @param n
   * @return Stella_Object
   */
  public Stella_Object nthBatchKey(int n) {
    { NeuralNetwork self = this;

      n = n;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("nth-batch-key: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Push a target <code>value</code> onto the target batch array which is assumed to correspond to the input
   * values at the same respective position in the batch.  Inputs and targets are associated by position in the batch,
   * they can be pushed independently, as long as they are fully synchronized when processing of the batch starts.
   * @param value
   */
  public void pushTargetValue(double value) {
    { NeuralNetwork self = this;

      value = value;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("push-target-value: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Push <code>vectorspecs</code> onto the vector argument batch array which is assumed to correspond to the input
   * values at the same respective position in the batch.  Truth-valued and vector-valued inputs are associated by position
   * in the batch, they can be pushed independently, as long as they are fully synchronized when processing of the batch starts.
   * If <code>self</code> has no vector-valued argument, the associated batch array can be left undefined.
   * @param vectorspecs
   */
  public void pushVectorInputValues(Stella_Object vectorspecs) {
    { NeuralNetwork self = this;

      vectorspecs = vectorspecs;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("push-vector-input-values: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Push input <code>values</code> onto the input batch array and associate them with <code>key</code> (which can be NULL).
   * Associating a key lets us easily map inputs/outputs to some processing object of interest (e.g., a justification).
   * @param key
   * @param values
   */
  public void pushInputValues(Stella_Object key, Stella_Object values) {
    { NeuralNetwork self = this;

      {
        key = key;
        values = values;
      }
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("push-input-values: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Return true if input batch arrays have been filled to capacity.
   * @return boolean
   */
  public boolean batchIsFullP() {
    { NeuralNetwork self = this;

      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("batch-is-full?: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Return the number of currently batched inputs.
   * @return int
   */
  public int currentBatchSize() {
    { NeuralNetwork self = this;

      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("current-batch-size: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Clear all currently batched inputs (with keys) and associated target values.
   */
  public void clearBatchArrays() {
    { NeuralNetwork self = this;

      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("clear-batch-arrays: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Given a properly forward activated and backpropagated network <code>self</code> for the current
   * inputs and training <code>error</code>, update the network's weights according to current gradients, learning rate
   * and momentum terms to reduce the error for the given inputs.  Reads output, hidden and input activations,
   * hidden error, weights and weight deltas, and updates weights and weight deltas.
   * @param error
   */
  public void updateNetworkWeights(double error) {
    { NeuralNetwork self = this;

      error = error;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("update-network-weights: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Given a properly forward activated network <code>self</code> for the current set of inputs,
   * and a training <code>error</code> between the current output and the goal value, backpropagate the error and
   * update <code>self</code>s vector of input errors.  Reads output, hidden activations and weights and updates
   * hidden errors and input errors.
   * @param error
   */
  public void backwardPropagateError(double error) {
    { NeuralNetwork self = this;

      error = error;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("backward-propagate-error: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Activates the current inputs of the network <code>self</code> to compute its output.
   * Sets <code>self</code>s <code>output</code> slot and returns the computed value.  Reads input activations and
   * weights and updates hidden and output activations.
   * @return double
   */
  public double forwardPropagateInputs() {
    { NeuralNetwork self = this;

      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("forward-propagate-inputs: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Generate a single argument spec for <code>arg</code> that can be used for <code>setVectorInputValues</code>.
   * <code>arg</code> can either be a proposition or justification.
   * @param arg
   * @return Stella_Object
   */
  public Stella_Object getVectorArgumentSpec(Stella_Object arg) {
    { NeuralNetwork self = this;

      arg = arg;
      return (null);
    }
  }

  /** Set the current vector inputs of the network <code>self</code> to the vectors described by <code>vectorspecs</code>.
   * Each vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs
   * are translated into actual numeric vectors such as embeddings is specific to the particular neural network type.
   * @param vectorspecs
   */
  public void setVectorInputValues(Stella_Object vectorspecs) {
    { NeuralNetwork self = this;

      vectorspecs = vectorspecs;
    }
  }

  /** Set the current truth-value inputs of the network <code>self</code> to float <code>values</code> in sequence.
   * Missing inputs will be set to 0.0, extra values will be ignored.
   * @param values
   */
  public void setInputValues(Stella_Object values) {
    { NeuralNetwork self = this;

      values = values;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("set-input-values: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Return the 0-based <code>n</code>-th proposition input error of <code>self</code> (ignores bias unit).
   * @param n
   * @return double
   */
  public double nthInputError(int n) {
    { NeuralNetwork self = this;

      n = n;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("nth-input-error: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Return the 0-based <code>n</code>-th proposition input of <code>self</code> (ignores bias unit).
   * @param n
   * @return double
   */
  public double nthInput(int n) {
    { NeuralNetwork self = this;

      n = n;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("nth-input: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Return the 0-based input position of vector argument <code>arg</code>.  Ignores bias unit which
   * is a network-implementation-specific detail.  If <code>arg</code> is not a vector argument, returns -1.
   * @param arg
   * @return int
   */
  public int vectorArgumentIndex(Proposition arg) {
    { NeuralNetwork self = this;

      arg = arg;
      return (-1);
    }
  }

  /** Return the number of arguments of <code>prop</code> that yield one or more vectors
   * for <code>self</code>s inputs.  <code>prop</code> can be NULL in which case the linked proposition will be used.
   * @param prop
   * @return int
   */
  public int numberOfVectorArguments(Proposition prop) {
    { NeuralNetwork self = this;

      prop = prop;
      return (0);
    }
  }

  /** Return TRUE if <code>self</code> has at least one vector input argument.
   * @return boolean
   */
  public boolean hasVectorArgumentsP() {
    { NeuralNetwork self = this;

      return (false);
    }
  }

  /** Return TRUE if <code>arg</code> yields one or more vectors for <code>self</code>s inputs.
   * @param arg
   * @return boolean
   */
  public boolean vectorArgumentP(Proposition arg) {
    { NeuralNetwork self = this;

      arg = arg;
      return (false);
    }
  }

  /** Return the number of arguments of <code>prop</code> whose partial truth value will be ignored
   * for <code>self</code>s inputs.  This top-level method only looks at <code>prop</code> and ignores <code>self</code>.
   * @param prop
   * @return int
   */
  public int numberOfIgnoredValueArguments(Proposition prop) {
    { NeuralNetwork self = this;

      { int nignored = 0;

        { Stella_Object arg = null;
          Vector vector000 = prop.arguments;
          int index000 = 0;
          int length000 = vector000.length();

          for (;index000 < length000; index000 = index000 + 1) {
            arg = (vector000.theArray)[index000];
            if (self.ignoredValueArgumentP(((Proposition)(arg)))) {
              nignored = nignored + 1;
            }
          }
        }
        return (nignored);
      }
    }
  }

  /** Return TRUE if the partial truth value of <code>arg</code> will be ignored for <code>self</code>s inputs.
   * This top-level method only looks at <code>arg</code> and ignores <code>self</code>.
   * @param arg
   * @return boolean
   */
  public boolean ignoredValueArgumentP(Proposition arg) {
    { NeuralNetwork self = this;

      { Stella_Object argrel = ((Surrogate)(arg.operator)).surrogateValue;

        return ((argrel != null) &&
            (Logic.testPropertyP(argrel, Logic.SGT_CHAMELEON_IGNORED_VALUE_RELATION) ||
             (Logic.testPropertyP(argrel, Logic.SGT_CHAMELEON_VECTOR_RELATION) &&
              (!Logic.testPropertyP(argrel, Logic.SGT_CHAMELEON_TRUTH_VALUE_RELATION)))));
      }
    }
  }

  /** Return the 0-based input position of truth value argument <code>arg</code>.  Ignores bias unit which
   * is a network-implementation-specific detail.  Generates indices in the order expected by <code>setInputValues</code>.
   * If <code>arg</code> is not a truth value argument, returns -1.
   * @param arg
   * @return int
   */
  public int truthValueArgumentIndex(Proposition arg) {
    { NeuralNetwork self = this;

      { MemoizationTable memoTable000 = null;
        Cons memoizedEntry000 = null;
        Stella_Object memoizedValue000 = null;

        if (Stella.$MEMOIZATION_ENABLEDp$) {
          memoTable000 = ((MemoizationTable)(Logic.SGT_LOGIC_M_NEURAL_NETWORKdTRUTH_VALUE_ARGUMENT_INDEX_MEMO_TABLE_000.surrogateValue));
          if (memoTable000 == null) {
            Surrogate.initializeMemoizationTable(Logic.SGT_LOGIC_M_NEURAL_NETWORKdTRUTH_VALUE_ARGUMENT_INDEX_MEMO_TABLE_000, "(:MAX-VALUES 1000 :TIMESTAMPS (:KB-UPDATE))");
            memoTable000 = ((MemoizationTable)(Logic.SGT_LOGIC_M_NEURAL_NETWORKdTRUTH_VALUE_ARGUMENT_INDEX_MEMO_TABLE_000.surrogateValue));
          }
          memoizedEntry000 = MruMemoizationTable.lookupMruMemoizedValue(((MruMemoizationTable)(memoTable000)), self, arg, Stella.MEMOIZED_NULL_VALUE, null, -1);
          memoizedValue000 = memoizedEntry000.value;
        }
        if (memoizedValue000 != null) {
          if (memoizedValue000 == Stella.MEMOIZED_NULL_VALUE) {
            memoizedValue000 = null;
          }
        }
        else {
          memoizedValue000 = IntegerWrapper.wrapInteger(NeuralNetwork.helpComputeArgumentIndex(self, arg, Logic.KWD_TRUTH_VALUE));
          if (Stella.$MEMOIZATION_ENABLEDp$) {
            memoizedEntry000.value = ((memoizedValue000 == null) ? Stella.MEMOIZED_NULL_VALUE : memoizedValue000);
          }
        }
        { IntegerWrapper value000 = ((IntegerWrapper)(memoizedValue000));

          return (value000.wrapperValue);
        }
      }
    }
  }

  /** Return the number of arguments of <code>prop</code> whose partial truth value will be considered
   * for <code>self</code>s inputs.  This top-level method only looks at <code>prop</code> and ignores <code>self</code>.
   * @param prop
   * @return int
   */
  public int numberOfTruthValueArguments(Proposition prop) {
    { NeuralNetwork self = this;

      { int ntruth = 0;

        { Stella_Object arg = null;
          Vector vector000 = prop.arguments;
          int index000 = 0;
          int length000 = vector000.length();

          for (;index000 < length000; index000 = index000 + 1) {
            arg = (vector000.theArray)[index000];
            if (self.truthValueArgumentP(((Proposition)(arg)))) {
              ntruth = ntruth + 1;
            }
          }
        }
        return (ntruth);
      }
    }
  }

  /** Return TRUE if the partial truth value of <code>arg</code> will be considered for <code>self</code>s inputs.
   * This top-level method only looks at <code>arg</code> and ignores <code>self</code>.
   * @param arg
   * @return boolean
   */
  public boolean truthValueArgumentP(Proposition arg) {
    { NeuralNetwork self = this;

      { Stella_Object argrel = ((Surrogate)(arg.operator)).surrogateValue;

        return ((argrel != null) &&
            (Logic.testPropertyP(argrel, Logic.SGT_CHAMELEON_TRUTH_VALUE_RELATION) ||
             (!(Logic.testPropertyP(argrel, Logic.SGT_CHAMELEON_IGNORED_VALUE_RELATION) ||
            (Logic.testPropertyP(argrel, Logic.SGT_CHAMELEON_VECTOR_RELATION) &&
             (!Logic.testPropertyP(argrel, Logic.SGT_CHAMELEON_TRUTH_VALUE_RELATION)))))));
      }
    }
  }

  /** Memoizable helper function for <code>truthValueArgumentIndex</code> and friends.
   * @param self
   * @param arg
   * @param kind
   * @return int
   */
  public static int helpComputeArgumentIndex(NeuralNetwork self, Proposition arg, Keyword kind) {
    { Proposition proposition = self.getNeuralNetworkProposition();
      int pos = -1;
      boolean matchP = false;
      KeyValueMap mapping = null;

      if ((arg.kind == Logic.KWD_NOT) ||
          (arg.kind == Logic.KWD_FAIL)) {
        arg = ((Proposition)((arg.arguments.theArray)[0]));
      }
      { Stella_Object proparg = null;
        Vector vector000 = proposition.arguments;
        int index000 = 0;
        int length000 = vector000.length();

        for (;index000 < length000; index000 = index000 + 1) {
          proparg = (vector000.theArray)[index000];
          if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(proparg), Logic.SGT_LOGIC_PROPOSITION)) {
            { Proposition proparg000 = ((Proposition)(proparg));

              if ((proparg000.kind == Logic.KWD_NOT) ||
                  (proparg000.kind == Logic.KWD_FAIL)) {
                proparg000 = ((Proposition)((proparg000.arguments.theArray)[0]));
              }
              if (((kind == Logic.KWD_TRUTH_VALUE) &&
                  self.truthValueArgumentP(proparg000)) ||
                  (((kind == Logic.KWD_IGNORED_VALUE) &&
                  self.ignoredValueArgumentP(proparg000)) ||
                   ((kind == Logic.KWD_VECTOR) &&
                    self.vectorArgumentP(proparg000)))) {
                pos = pos + 1;
                matchP = true;
              }
              else {
                matchP = false;
              }
              if (proparg000 == arg) {
                return ((matchP ? pos : -1));
              }
              else if (proparg000.operator == arg.operator) {
                { Object old$UnifyPropositionsP$000 = Logic.$UNIFY_PROPOSITIONSp$.get();
                  Object old$Queryiterator$000 = Logic.$QUERYITERATOR$.get();

                  try {
                    Native.setBooleanSpecial(Logic.$UNIFY_PROPOSITIONSp$, true);
                    Native.setSpecial(Logic.$QUERYITERATOR$, null);
                    if (mapping == null) {
                      mapping = KeyValueMap.newKeyValueMap();
                    }
                    else {
                      mapping.clear();
                    }
                    if (Proposition.equivalentPropositionsP(proparg000, arg, mapping)) {
                      return ((matchP ? pos : -1));
                    }

                  } finally {
                    Logic.$QUERYITERATOR$.set(old$Queryiterator$000);
                    Logic.$UNIFY_PROPOSITIONSp$.set(old$UnifyPropositionsP$000);
                  }
                }
              }
            }
          }
          else {
          }
        }
      }
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("INTERNAL ERROR: failed to map neural net input argument: `" + arg + "'`" + proposition + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Return the number of input values expected by <code>self</code> (ignores bias unit).
   * @return int
   */
  public int numberOfInputs() {
    { NeuralNetwork self = this;

      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("number-of-inputs: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Build a neural network for the proposition <code>prop</code> and link them.  This builds
   * a two-layer perceptron network whose input nodes are activated by the truth of <code>prop</code>s arguments
   * and whose output node computes the truth of <code>prop</code>.
   * @param prop
   */
  public void buildPropositionNetwork(Proposition prop) {
    { NeuralNetwork self = this;

      prop = prop;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("build-proposition-network: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Randomize the weights of the neural network <code>self</code>.
   */
  public void randomizeNetworkWeights() {
    { NeuralNetwork self = this;

      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("randomize-network-weights: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Allocates array space for a neural network with given number of input, hidden and output units.
   * @param numIn
   * @param numHidden
   * @param numOut
   */
  public void allocateNetworkArrays(int numIn, int numHidden, int numOut) {
    { NeuralNetwork self = this;

      {
        numIn = numIn;
        numHidden = numHidden;
        numOut = numOut;
      }
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("allocate-arrays: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Return trun if <code>self</code> has been deleted.
   * @return boolean
   */
  public boolean deletedP() {
    { NeuralNetwork self = this;

      return (false);
    }
  }

  /** Unlink the network <code>self</code> from its associated proposition and mark it as deleted.
   */
  public void deleteNeuralNetwork() {
    { NeuralNetwork self = this;

      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("delete-neural-network: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Return the proposition linked to <code>self</code>.
   * @return Proposition
   */
  public Proposition getNeuralNetworkProposition() {
    { NeuralNetwork self = this;

      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("get-proposition: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Unlink the network <code>self</code> from its associated proposition.
   */
  public void unlinkNeuralNetwork() {
    { NeuralNetwork self = this;

      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("unlink-neural-network: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Link the network <code>self</code> to its associated proposition <code>prop</code>.
   * @param prop
   */
  public void linkNeuralNetwork(Proposition prop) {
    { NeuralNetwork self = this;

      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("link-neural-network: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Unregister the network <code>self</code> on the global networks list.
   * @param self
   */
  public static void unregisterNeuralNetwork(NeuralNetwork self) {
    { IntegerWrapper hashcode = IntegerWrapper.wrapInteger(Proposition.propositionHashIndex(self.getNeuralNetworkProposition(), null, true));
      Cons bucket = ((Cons)(Logic.$ALL_NEURAL_NETWORKS$.lookup(hashcode)));

      if (bucket == null) {
      }
      else if (bucket.rest == Stella.NIL) {
        Logic.$ALL_NEURAL_NETWORKS$.removeAt(hashcode);
      }
      else {
        bucket.remove(self);
      }
    }
  }

  /** Register the network <code>self</code> on the global networks list (assumes <code>self</code> has been linked).
   * @param self
   */
  public static void registerNeuralNetwork(NeuralNetwork self) {
    { IntegerWrapper hashcode = IntegerWrapper.wrapInteger(Proposition.propositionHashIndex(self.getNeuralNetworkProposition(), null, true));
      Cons bucket = ((Cons)(Logic.$ALL_NEURAL_NETWORKS$.lookup(hashcode)));

      if (bucket == null) {
        Logic.$ALL_NEURAL_NETWORKS$.insertAt(hashcode, Cons.cons(self, Stella.NIL));
      }
      else {
        bucket.rest = Cons.cons(((NeuralNetwork)(bucket.value)), bucket.rest);
        bucket.firstSetter(self);
      }
    }
  }

}

