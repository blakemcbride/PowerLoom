//  -*- Mode: Java -*-
//
// TensorflowBatchNeuralNetwork.java

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

/** Tensorflow neural network that supports batch operations.  We implement input and result
 * batches as 1-D and 2-D float arrays to enable fast back-and-forth copying in a single shot instead of having
 * multiple method calls.  For this reason, we maintain the input and target sequences manually.
 * @author Stella Java Translator
 */
public class TensorflowBatchNeuralNetwork extends TensorflowNeuralNetwork {
    /** Cleared by Python/Tensorflow side, used to avoid unnecessary copying.
     */
    public boolean inputModifiedP;
    /** Each row is a set of inputs for the input units of the network, including the bias.
     */
    public twoDFloatArray inputBatch;
    public int inputBatchLength;
    /** Each element is a key to identify a specific set of input values.
     */
    public VectorSequence keyBatch;
    /** Each row is a set of vector argument specs for the inputs of the network.
     */
    public twoDLongArray vectorBatch;
    public int vectorBatchLength;
    /** Each element is a target output value for the respective set of input values.
     */
    public oneDFloatArray targetBatch;
    public int targetBatchLength;
    public oneDFloatArray outputBatch;
    /** Each row is a set of errors the respective inputs including the bias.
     */
    public twoDFloatArray inputErrorBatch;

  public static TensorflowBatchNeuralNetwork newTensorflowBatchNeuralNetwork() {
    { TensorflowBatchNeuralNetwork self = null;

      self = new TensorflowBatchNeuralNetwork();
      self.nVectorArgumentInputs = -1;
      self.nVectorArgumentSpecs = -1;
      self.nVectorArguments = -1;
      self.model = null;
      self.proposition = null;
      self.inputErrorBatch = null;
      self.outputBatch = null;
      self.targetBatchLength = 0;
      self.targetBatch = null;
      self.vectorBatchLength = 0;
      self.vectorBatch = null;
      self.keyBatch = null;
      self.inputBatchLength = 0;
      self.inputBatch = null;
      self.inputModifiedP = true;
      return (self);
    }
  }

  public void batchUpdateNetworkWeights() {
    { TensorflowBatchNeuralNetwork self = this;

      edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_UPDATE_NETWORK_WEIGHTS.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {});
    }
  }

  public void batchBackwardPropagateError() {
    { TensorflowBatchNeuralNetwork self = this;

      edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_BACKWARD_PROPAGATE_ERROR.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {});
    }
  }

  public oneDFloatArray batchForwardPropagateInputs() {
    { TensorflowBatchNeuralNetwork self = this;

      edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORKdBATCH_FORWARD_PROPAGATE_INPUTS.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {});
      return (self.outputBatch);
    }
  }

  public double nthBatchOutput(int n) {
    { TensorflowBatchNeuralNetwork self = this;

      return (self.outputBatch.theArray[n]);
    }
  }

  public double nthKthBatchInputError(int n, int k) {
    { TensorflowBatchNeuralNetwork self = this;

      return (self.inputErrorBatch.theArray[(n * self.inputErrorBatch.dim2) + k + 1]);
    }
  }

  public Stella_Object nthBatchKey(int n) {
    { TensorflowBatchNeuralNetwork self = this;

      return ((self.keyBatch.theArray)[n]);
    }
  }

  public void pushTargetValue(double value) {
    { TensorflowBatchNeuralNetwork self = this;

      { int cursor = self.targetBatchLength;

        self.targetBatch.theArray[cursor] = value;
        self.targetBatchLength = cursor + 1;
        self.inputModifiedP = true;
      }
    }
  }

  public void pushVectorInputValues(Stella_Object vectorspecs) {
    { TensorflowBatchNeuralNetwork self = this;

      if (self.vectorBatch != null) {
        { twoDLongArray vectorbatch = self.vectorBatch;
          long[] vectorarray = vectorbatch.theArray;
          int start = (self.vectorBatchLength * vectorbatch.dim2) + 0;
          int i = start;

          { Surrogate testValue000 = Stella_Object.safePrimaryType(vectorspecs);

            if (Surrogate.subtypeOfP(testValue000, Logic.SGT_STELLA_VECTOR)) {
              { Vector vectorspecs000 = ((Vector)(vectorspecs));

                { Stella_Object spec = null;
                  Vector vector000 = vectorspecs000;
                  int index000 = 0;
                  int length000 = vector000.length();

                  for (;index000 < length000; index000 = index000 + 1) {
                    spec = (vector000.theArray)[index000];
                    if (Stella_Object.safePrimaryType(spec) == Logic.SGT_STELLA_CONS) {
                      { Cons spec000 = ((Cons)(spec));

                        { Stella_Object elt = null;
                          Cons iter000 = spec000;

                          for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
                            elt = iter000.value;
                            if (Surrogate.subtypeOfLongIntegerP(Stella_Object.safePrimaryType(elt))) {
                              { LongIntegerWrapper elt000 = ((LongIntegerWrapper)(elt));

                                vectorarray[i] = elt000.wrapperValue;
                                i = i + 1;
                              }
                            }
                            else {
                              { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

                                stream000.nativeStream.print("push-vector-input-values: unexpected vector argument spec: `" + elt + "'");
                                throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
                              }
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
            else if (testValue000 == Logic.SGT_STELLA_CONS) {
              { Cons vectorspecs000 = ((Cons)(vectorspecs));

                { Stella_Object spec = null;
                  Cons iter001 = vectorspecs000;

                  for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
                    spec = iter001.value;
                    if (Stella_Object.safePrimaryType(spec) == Logic.SGT_STELLA_CONS) {
                      { Cons spec000 = ((Cons)(spec));

                        { Stella_Object elt = null;
                          Cons iter002 = spec000;

                          for (;!(iter002 == Stella.NIL); iter002 = iter002.rest) {
                            elt = iter002.value;
                            if (Surrogate.subtypeOfLongIntegerP(Stella_Object.safePrimaryType(elt))) {
                              { LongIntegerWrapper elt000 = ((LongIntegerWrapper)(elt));

                                vectorarray[i] = elt000.wrapperValue;
                                i = i + 1;
                              }
                            }
                            else {
                              { OutputStringStream stream001 = OutputStringStream.newOutputStringStream();

                                stream001.nativeStream.print("push-vector-input-values: unexpected vector argument spec: `" + elt + "'");
                                throw ((StellaException)(StellaException.newStellaException(stream001.theStringReader()).fillInStackTrace()));
                              }
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
            else {
              { OutputStringStream stream002 = OutputStringStream.newOutputStringStream();

                stream002.nativeStream.print("`" + testValue000 + "' is not a valid case option");
                throw ((StellaException)(StellaException.newStellaException(stream002.theStringReader()).fillInStackTrace()));
              }
            }
          }
          if (i > start) {
            self.vectorBatchLength = self.vectorBatchLength + 1;
            self.inputModifiedP = true;
          }
        }
      }
    }
  }

  public void pushInputValues(Stella_Object key, Stella_Object values) {
    { TensorflowBatchNeuralNetwork self = this;

      { twoDFloatArray inputbatch = self.inputBatch;
        double[] inputarray = inputbatch.theArray;
        int start = (self.inputBatchLength * inputbatch.dim2) + 0;

        inputarray[start] = 1.0;
        Logic.copyFloatValuesToBuffer(values, inputarray, start + 1, start + inputbatch.dim2);
        self.inputBatchLength = self.inputBatchLength + 1;
        self.keyBatch.insert(key);
        self.inputModifiedP = true;
      }
    }
  }

  public boolean batchIsFullP() {
    { TensorflowBatchNeuralNetwork self = this;

      return (self.inputBatchLength >= Logic.$NEURAL_NETWORK_BATCH_SIZE$);
    }
  }

  public int currentBatchSize() {
    { TensorflowBatchNeuralNetwork self = this;

      return (self.inputBatchLength);
    }
  }

  public void clearBatchArrays() {
    { TensorflowBatchNeuralNetwork self = this;

      self.inputBatchLength = 0;
      self.keyBatch.clear();
      self.vectorBatchLength = 0;
      self.targetBatchLength = 0;
      self.inputModifiedP = true;
    }
  }

  /** Activates the current inputs of the network <code>self</code> to compute its output.
   * Sets <code>self</code>s <code>output</code> slot and returns the computed value.  Reads input activations and
   * weights and updates hidden and output activations.
   * @return double
   */
  public double forwardPropagateInputs() {
    { TensorflowBatchNeuralNetwork self = this;

      return (super.forwardPropagateInputs());
    }
  }

  /** Set the current vector inputs of the network <code>self</code> to the vectors described by <code>vectorspecs</code>.
   * Each vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs
   * are translated into actual numeric vectors such as embeddings is specific to the particular neural network type.
   * @param vectorspecs
   */
  public void setVectorInputValues(Stella_Object vectorspecs) {
    { TensorflowBatchNeuralNetwork self = this;

      super.setVectorInputValues(vectorspecs);
    }
  }

  /** Generate a single argument spec for <code>arg</code> that can be used for <code>setVectorInputValues</code>.
   * <code>arg</code> can either be a proposition or justification.
   * @param arg
   * @return Stella_Object
   */
  public Stella_Object getVectorArgumentSpec(Stella_Object arg) {
    { TensorflowBatchNeuralNetwork self = this;

      { Stella_Object spec = super.getVectorArgumentSpec(arg);
        Cons evalargs = Stella.NIL;

        if (Stella_Object.safePrimaryType(spec) == Logic.SGT_STELLA_CONS) {
          { Cons spec000 = ((Cons)(spec));

            { Stella_Object elt = null;
              Cons iter000 = spec000;
              Cons collect000 = null;

              for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
                elt = iter000.value;
                if (Stella_Object.longIntegerP(elt)) {
                  if (collect000 == null) {
                    {
                      collect000 = Cons.cons(elt, Stella.NIL);
                      if (evalargs == Stella.NIL) {
                        evalargs = collect000;
                      }
                      else {
                        Cons.addConsToEndOfConsList(evalargs, collect000);
                      }
                    }
                  }
                  else {
                    {
                      collect000.rest = Cons.cons(elt, Stella.NIL);
                      collect000 = collect000.rest;
                    }
                  }
                }
              }
            }
          }
        }
        else {
        }
        if (!(evalargs == Stella.NIL)) {
          return (evalargs);
        }
        else {
          return (spec);
        }
      }
    }
  }

  /** Set the current truth-value inputs of the network <code>self</code> to float <code>values</code> in sequence.
   * Missing inputs will be set to 0.0, extra values will be ignored.
   * @param values
   */
  public void setInputValues(Stella_Object values) {
    { TensorflowBatchNeuralNetwork self = this;

      super.setInputValues(values);
    }
  }

  /** Return the 0-based <code>n</code>-th proposition input error of <code>self</code> (ignores bias unit).
   * @param n
   * @return double
   */
  public double nthInputError(int n) {
    { TensorflowBatchNeuralNetwork self = this;

      n = n;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("nth-input-error: not supported on: `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Return the 0-based <code>n</code>-th proposition input of <code>self</code> (ignores bias unit).
   * @param n
   * @return double
   */
  public double nthInput(int n) {
    { TensorflowBatchNeuralNetwork self = this;

      n = n;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("nth-input: not supported on: `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Return the number of input values expected by <code>self</code> (ignores bias unit).
   * @return int
   */
  public int numberOfInputs() {
    { TensorflowBatchNeuralNetwork self = this;

      return (self.inputBatch.dim2 - 1);
    }
  }

  /** Build a neural network for the proposition <code>prop</code>.  This builds a two-layer
   * perceptron network whose input nodes are activated by the truth of <code>prop</code>s arguments and whose
   * output node computes the truth of <code>prop</code>.
   * @param prop
   */
  public void buildPropositionNetwork(Proposition prop) {
    { TensorflowBatchNeuralNetwork self = this;

      { int numIn = self.numberOfTruthValueArguments(prop) + self.numberOfVectorArgumentInputs(prop) + 1;
        int numHidden = Stella.integer_min(numIn + 0, 20);

        if (numIn > 100) {
          numHidden = Native.floor(numIn / 10.0) + 10;
        }
        self.proposition = prop;
        self.allocateNetworkArrays(numIn, numHidden, 1);
        { Keyword testValue000 = prop.kind;

          if ((testValue000 == Logic.KWD_AND) ||
              (testValue000 == Logic.KWD_OR)) {
            self.initializeNetworkWeights();
          }
          else {
            self.initializeNetworkWeights();
          }
        }
        self.linkNeuralNetwork(prop);
      }
    }
  }

  public void allocateNetworkArrays(int numIn, int numHidden, int numOut) {
    { TensorflowBatchNeuralNetwork self = this;

      super.allocateNetworkArrays(numIn, numHidden, numOut);
      { int tvnumin = self.numberOfTruthValueArguments(self.proposition) + 1;

        self.inputBatch = twoDFloatArray.new2DFloatArray(tvnumin, Logic.$NEURAL_NETWORK_BATCH_SIZE$);
        self.keyBatch = VectorSequence.newVectorSequence(Logic.$NEURAL_NETWORK_BATCH_SIZE$);
        if (self.numberOfVectorArgumentSpecs(null) > 0) {
          self.vectorBatch = twoDLongArray.new2DLongArray(self.numberOfVectorArgumentSpecs(null), Logic.$NEURAL_NETWORK_BATCH_SIZE$);
        }
        self.targetBatch = oneDFloatArray.new1DFloatArray(Logic.$NEURAL_NETWORK_BATCH_SIZE$);
        self.outputBatch = oneDFloatArray.new1DFloatArray(Logic.$NEURAL_NETWORK_BATCH_SIZE$);
        self.inputErrorBatch = twoDFloatArray.new2DFloatArray(tvnumin, Logic.$NEURAL_NETWORK_BATCH_SIZE$);
        self.inputModifiedP = true;
      }
    }
  }

  public void printNetworkArrays() {
    { TensorflowBatchNeuralNetwork self = this;

      { int batchlength = self.inputBatchLength;

        Stella.STANDARD_OUTPUT.nativeStream.println("input batch (" + batchlength + "):");
        { int i = Stella.NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = batchlength - 1;

          for (;iter000 <= upperBound000; iter000 = iter000 + 1) {
            i = iter000;
            { int j = Stella.NULL_INTEGER;
              int iter001 = 0;
              int upperBound001 = self.inputBatch.dim2 - 1;

              for (;iter001 <= upperBound001; iter001 = iter001 + 1) {
                j = iter001;
                Stella.STANDARD_OUTPUT.nativeStream.print(self.inputBatch.theArray[(i * self.inputBatch.dim2) + j] + " ");
              }
            }
            Stella.STANDARD_OUTPUT.nativeStream.println();
          }
        }
        batchlength = self.targetBatchLength;
        Stella.STANDARD_OUTPUT.nativeStream.println("target batch (" + batchlength + "):");
        { int i = Stella.NULL_INTEGER;
          int iter002 = 0;
          int upperBound002 = batchlength - 1;

          for (;iter002 <= upperBound002; iter002 = iter002 + 1) {
            i = iter002;
            Stella.STANDARD_OUTPUT.nativeStream.print(self.targetBatch.theArray[i] + " ");
          }
        }
        Stella.STANDARD_OUTPUT.nativeStream.println();
        batchlength = self.inputBatchLength;
        Stella.STANDARD_OUTPUT.nativeStream.println("output batch (" + batchlength + "):");
        { int i = Stella.NULL_INTEGER;
          int iter003 = 0;
          int upperBound003 = batchlength - 1;

          for (;iter003 <= upperBound003; iter003 = iter003 + 1) {
            i = iter003;
            Stella.STANDARD_OUTPUT.nativeStream.print(self.outputBatch.theArray[i] + " ");
          }
        }
        Stella.STANDARD_OUTPUT.nativeStream.println();
        Stella.STANDARD_OUTPUT.nativeStream.println("input error batch (" + batchlength + "):");
        { int i = Stella.NULL_INTEGER;
          int iter004 = 0;
          int upperBound004 = batchlength - 1;

          for (;iter004 <= upperBound004; iter004 = iter004 + 1) {
            i = iter004;
            { int j = Stella.NULL_INTEGER;
              int iter005 = 0;
              int upperBound005 = self.inputErrorBatch.dim2 - 1;

              for (;iter005 <= upperBound005; iter005 = iter005 + 1) {
                j = iter005;
                Stella.STANDARD_OUTPUT.nativeStream.print(self.inputErrorBatch.theArray[(i * self.inputErrorBatch.dim2) + j] + " ");
              }
            }
            Stella.STANDARD_OUTPUT.nativeStream.println();
          }
        }
      }
    }
  }

  public static Stella_Object accessTensorflowBatchNeuralNetworkSlotValue(TensorflowBatchNeuralNetwork self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Logic.SYM_LOGIC_INPUT_MODIFIEDp) {
      if (setvalueP) {
        self.inputModifiedP = BooleanWrapper.coerceWrappedBooleanToBoolean(((BooleanWrapper)(value)));
      }
      else {
        value = (self.inputModifiedP ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER);
      }
    }
    else if (slotname == Logic.SYM_LOGIC_INPUT_BATCH) {
      if (setvalueP) {
        self.inputBatch = ((twoDFloatArray)(value));
      }
      else {
        value = self.inputBatch;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_INPUT_BATCH_LENGTH) {
      if (setvalueP) {
        self.inputBatchLength = ((IntegerWrapper)(value)).wrapperValue;
      }
      else {
        value = IntegerWrapper.wrapInteger(self.inputBatchLength);
      }
    }
    else if (slotname == Logic.SYM_LOGIC_KEY_BATCH) {
      if (setvalueP) {
        self.keyBatch = ((VectorSequence)(value));
      }
      else {
        value = self.keyBatch;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_VECTOR_BATCH) {
      if (setvalueP) {
        self.vectorBatch = ((twoDLongArray)(value));
      }
      else {
        value = self.vectorBatch;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_VECTOR_BATCH_LENGTH) {
      if (setvalueP) {
        self.vectorBatchLength = ((IntegerWrapper)(value)).wrapperValue;
      }
      else {
        value = IntegerWrapper.wrapInteger(self.vectorBatchLength);
      }
    }
    else if (slotname == Logic.SYM_LOGIC_TARGET_BATCH) {
      if (setvalueP) {
        self.targetBatch = ((oneDFloatArray)(value));
      }
      else {
        value = self.targetBatch;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_TARGET_BATCH_LENGTH) {
      if (setvalueP) {
        self.targetBatchLength = ((IntegerWrapper)(value)).wrapperValue;
      }
      else {
        value = IntegerWrapper.wrapInteger(self.targetBatchLength);
      }
    }
    else if (slotname == Logic.SYM_LOGIC_OUTPUT_BATCH) {
      if (setvalueP) {
        self.outputBatch = ((oneDFloatArray)(value));
      }
      else {
        value = self.outputBatch;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_INPUT_ERROR_BATCH) {
      if (setvalueP) {
        self.inputErrorBatch = ((twoDFloatArray)(value));
      }
      else {
        value = self.inputErrorBatch;
      }
    }
    else {
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("`" + slotname + "' is not a valid case option");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
    return (value);
  }

  public Surrogate primaryType() {
    { TensorflowBatchNeuralNetwork self = this;

      return (Logic.SGT_LOGIC_TENSORFLOW_BATCH_NEURAL_NETWORK);
    }
  }

}

