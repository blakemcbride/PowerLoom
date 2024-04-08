//  -*- Mode: Java -*-
//
// ChameleonNeuralNetwork.java

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

/** Stream-lined neural network structure that doesn't require float wrapping.
 * @author Stella Java Translator
 */
public class ChameleonNeuralNetwork extends NeuralNetwork {
    public Proposition proposition;
    public oneDFloatArray input;
    public oneDFloatArray hidden;
    public double output;
    public twoDFloatArray ih;
    public oneDFloatArray ho;
    public oneDFloatArray inputError;
    public oneDFloatArray hiddenError;
    public double outputError;
    public twoDFloatArray ihDelta;
    public oneDFloatArray hoDelta;

  public static ChameleonNeuralNetwork newChameleonNeuralNetwork() {
    { ChameleonNeuralNetwork self = null;

      self = new ChameleonNeuralNetwork();
      self.hoDelta = null;
      self.ihDelta = null;
      self.outputError = Stella.NULL_FLOAT;
      self.hiddenError = null;
      self.inputError = null;
      self.ho = null;
      self.ih = null;
      self.output = Stella.NULL_FLOAT;
      self.hidden = null;
      self.input = null;
      self.proposition = null;
      return (self);
    }
  }

  /** Given a properly forward activated and backpropagated network <code>self</code> for the current
   * inputs and training <code>error</code>, update the network's weights according to current gradients, learning rate
   * and momentum terms to reduce the error for the given inputs.  Reads output, hidden and input activations,
   * hidden error, weights and weight deltas, and updates weights and weight deltas.
   * @param error
   */
  public void updateNetworkWeights(double error) {
    { ChameleonNeuralNetwork self = this;

      { oneDFloatArray input = self.input;
        int lastInput = input.dim1 - 1;
        double[] inputArray = input.theArray;
        twoDFloatArray ih = self.ih;
        twoDFloatArray ihDelta = self.ihDelta;
        oneDFloatArray hidden = self.hidden;
        int lastHidden = hidden.dim1 - 1;
        double[] hiddenArray = hidden.theArray;
        oneDFloatArray hiddenError = self.hiddenError;
        double[] hiddenErrorArray = hiddenError.theArray;
        oneDFloatArray ho = self.ho;
        double[] hoArray = ho.theArray;
        oneDFloatArray hoDelta = self.hoDelta;
        double[] hoDeltaArray = hoDelta.theArray;
        double output = self.output;
        double delta = 0.0;

        error = error * output * (1.0 - output);
        { int h = Stella.NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = lastHidden;
          boolean unboundedP000 = upperBound000 == Stella.NULL_INTEGER;

          for (;unboundedP000 ||
                    (iter000 <= upperBound000); iter000 = iter000 + 1) {
            h = iter000;
            delta = (Logic.$MOMENTUM_TERM$ * hoDeltaArray[h]) + (Logic.$LEARNING_RATE$ * error * hiddenArray[h]);
            hoArray[h] = hoArray[h] + delta;
            hoDeltaArray[h] = delta;
            { int i = Stella.NULL_INTEGER;
              int iter001 = 0;
              int upperBound001 = lastInput;
              boolean unboundedP001 = upperBound001 == Stella.NULL_INTEGER;

              for (;unboundedP001 ||
                        (iter001 <= upperBound001); iter001 = iter001 + 1) {
                i = iter001;
                delta = (Logic.$MOMENTUM_TERM$ * ihDelta.theArray[(i * ihDelta.dim2) + h]) + (Logic.$LEARNING_RATE$ * hiddenErrorArray[h] * inputArray[i]);
                ih.theArray[(i * ih.dim2) + h] = ih.theArray[(i * ih.dim2) + h] + delta;
                ihDelta.theArray[(i * ihDelta.dim2) + h] = delta;
              }
            }
          }
        }
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
    { ChameleonNeuralNetwork self = this;

      { int lastInput = self.input.dim1 - 1;
        oneDFloatArray inputError = self.inputError;
        double[] inputErrorArray = inputError.theArray;
        twoDFloatArray ih = self.ih;
        oneDFloatArray hidden = self.hidden;
        double[] hiddenArray = hidden.theArray;
        int lastHidden = hidden.dim1 - 1;
        oneDFloatArray hiddenError = self.hiddenError;
        double[] hiddenErrorArray = hiddenError.theArray;
        oneDFloatArray ho = self.ho;
        double[] hoArray = ho.theArray;
        double output = self.output;

        error = error * output * (1.0 - output);
        { int h = Stella.NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = lastHidden;
          boolean unboundedP000 = upperBound000 == Stella.NULL_INTEGER;

          for (;unboundedP000 ||
                    (iter000 <= upperBound000); iter000 = iter000 + 1) {
            h = iter000;
            hiddenErrorArray[h] = error * hoArray[h];
            hiddenErrorArray[h] = hiddenErrorArray[h] * hiddenArray[h] * (1.0 - hiddenArray[h]);
          }
        }
        { int i = Stella.NULL_INTEGER;
          int iter001 = 0;
          int upperBound001 = lastInput;
          boolean unboundedP001 = upperBound001 == Stella.NULL_INTEGER;

          for (;unboundedP001 ||
                    (iter001 <= upperBound001); iter001 = iter001 + 1) {
            i = iter001;
            inputErrorArray[i] = 0.0;
            { int h = Stella.NULL_INTEGER;
              int iter002 = 0;
              int upperBound002 = lastHidden;
              boolean unboundedP002 = upperBound002 == Stella.NULL_INTEGER;

              for (;unboundedP002 ||
                        (iter002 <= upperBound002); iter002 = iter002 + 1) {
                h = iter002;
                inputErrorArray[i] = inputErrorArray[i] + (hiddenErrorArray[h] * ih.theArray[(i * ih.dim2) + h]);
              }
            }
          }
        }
      }
    }
  }

  /** Activates the current inputs of the network <code>self</code> to compute its output.
   * Sets <code>self</code>s <code>output</code> slot and returns the computed value.  Reads input activations and
   * weights and updates hidden and output activations.
   * @return double
   */
  public double forwardPropagateInputs() {
    { ChameleonNeuralNetwork self = this;

      { oneDFloatArray input = self.input;
        oneDFloatArray hidden = self.hidden;
        int numIn = input.dim1;
        int numHidden = hidden.dim1;
        double[] inputArray = input.theArray;
        double[] hiddenArray = hidden.theArray;
        twoDFloatArray ih = self.ih;
        oneDFloatArray ho = self.ho;
        double[] hoArray = ho.theArray;
        double score = 0.0;
        double sum = 0.0;

        inputArray[0] = 1.0;
        { int i = Stella.NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = numHidden - 1;

          for (;iter000 <= upperBound000; iter000 = iter000 + 1) {
            i = iter000;
            sum = 0.0;
            { int j = Stella.NULL_INTEGER;
              int iter001 = 0;
              int upperBound001 = numIn - 1;

              for (;iter001 <= upperBound001; iter001 = iter001 + 1) {
                j = iter001;
                sum = sum + (inputArray[j] * ih.theArray[(j * ih.dim2) + i]);
              }
            }
            hiddenArray[i] = 1.0 / (1.0 + Math.exp((0 - sum)));
            score = score + (hiddenArray[i] * hoArray[i]);
          }
        }
        self.output = 1.0 / (1.0 + Math.exp((0 - score)));
        return (self.output);
      }
    }
  }

  /** Set the current vector inputs of the network <code>self</code> to the vectors described by <code>vectorspecs</code>.
   * Each vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs
   * are translated into actual numeric vectors such as embeddings is specific to the particular neural network type.
   * @param vectorspecs
   */
  public void setVectorInputValues(Stella_Object vectorspecs) {
    { ChameleonNeuralNetwork self = this;

      vectorspecs = vectorspecs;
      if (!(Stella_Object.isaP(self, Logic.SGT_LOGIC_VECTOR_NEURAL_NETWORK))) {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("set-vector-input-values: Not defined on `" + self + "'");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  /** Set the current truth-value inputs of the network <code>self</code> to float <code>values</code> in sequence.
   * Missing inputs will be set to 0.0, extra values will be ignored.
   * @param values
   */
  public void setInputValues(Stella_Object values) {
    { ChameleonNeuralNetwork self = this;

      { oneDFloatArray input = self.input;
        double[] inputarray = input.theArray;

        inputarray[0] = 1.0;
        Logic.copyFloatValuesToBuffer(values, inputarray, 1, input.dim1);
      }
    }
  }

  /** Return the 0-based <code>n</code>-th proposition input error of <code>self</code> (ignores bias unit).
   * @param n
   * @return double
   */
  public double nthInputError(int n) {
    { ChameleonNeuralNetwork self = this;

      return (self.inputError.theArray[n + 1]);
    }
  }

  /** Return the 0-based <code>n</code>-th proposition input of <code>self</code> (ignores bias unit).
   * @param n
   * @return double
   */
  public double nthInput(int n) {
    { ChameleonNeuralNetwork self = this;

      return (self.input.theArray[n + 1]);
    }
  }

  /** Return the number of input values expected by <code>self</code> (ignores bias unit).
   * @return int
   */
  public int numberOfInputs() {
    { ChameleonNeuralNetwork self = this;

      return (self.input.dim1 - 1);
    }
  }

  /** Build a neural network for the proposition <code>prop</code>.  This builds a two-layer
   * perceptron network whose input nodes are activated by the truth of <code>prop</code>s arguments and whose
   * output node computes the truth of <code>prop</code>.
   * @param prop
   */
  public void buildPropositionNetwork(Proposition prop) {
    { ChameleonNeuralNetwork self = this;

      { int numIn = (prop.arguments.length() - self.numberOfIgnoredValueArguments(prop)) + 1;
        int numHidden = Stella.integer_min(numIn + 0, 20);

        if (numIn > 100) {
          numHidden = Native.floor(numIn / 10.0) + 10;
        }
        self.allocateNetworkArrays(numIn, numHidden, 1);
        { Keyword testValue000 = prop.kind;

          if ((testValue000 == Logic.KWD_AND) ||
              (testValue000 == Logic.KWD_OR)) {
            self.randomizeNetworkWeights();
          }
          else {
            self.randomizeNetworkWeights();
          }
        }
        self.linkNeuralNetwork(prop);
      }
    }
  }

  /** Randomize the weights of the neural network <code>self</code>.
   */
  public void randomizeNetworkWeights() {
    { ChameleonNeuralNetwork self = this;

      { int numIn = self.input.dim1;
        int numHidden = self.hidden.dim1;
        double[] hoDeltaArray = self.hoDelta.theArray;
        twoDFloatArray ihDelta = self.ihDelta;
        twoDFloatArray ih = self.ih;
        double[] hoArray = self.ho.theArray;

        { int h = Stella.NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = numHidden - 1;

          for (;iter000 <= upperBound000; iter000 = iter000 + 1) {
            h = iter000;
            hoDeltaArray[h] = 0.0;
            { int i = Stella.NULL_INTEGER;
              int iter001 = 0;
              int upperBound001 = numIn - 1;

              for (;iter001 <= upperBound001; iter001 = iter001 + 1) {
                i = iter001;
                ihDelta.theArray[(i * ihDelta.dim2) + h] = 0.0;
              }
            }
          }
        }
        { int i = Stella.NULL_INTEGER;
          int iter002 = 0;
          int upperBound002 = numHidden - 1;

          for (;iter002 <= upperBound002; iter002 = iter002 + 1) {
            i = iter002;
            { int j = Stella.NULL_INTEGER;
              int iter003 = 0;
              int upperBound003 = numIn - 1;

              for (;iter003 <= upperBound003; iter003 = iter003 + 1) {
                j = iter003;
                ih.theArray[(j * ih.dim2) + i] = Logic.randomWeight(Logic.$WEIGHT_RANGE$);
              }
            }
            hoArray[i] = Logic.randomWeight(Logic.$WEIGHT_RANGE$);
          }
        }
      }
    }
  }

  /** Allocates array space for a neural network with given number of input, hidden and output units.
   * @param numIn
   * @param numHidden
   * @param numOut
   */
  public void allocateNetworkArrays(int numIn, int numHidden, int numOut) {
    { ChameleonNeuralNetwork self = this;

      numOut = numOut;
      self.input = oneDFloatArray.new1DFloatArray(numIn);
      self.hidden = oneDFloatArray.new1DFloatArray(numHidden);
      self.ih = twoDFloatArray.new2DFloatArray(numHidden, numIn);
      self.ihDelta = twoDFloatArray.new2DFloatArray(numHidden, numIn);
      self.inputError = oneDFloatArray.new1DFloatArray(numIn);
      self.hiddenError = oneDFloatArray.new1DFloatArray(numHidden);
      self.ho = oneDFloatArray.new1DFloatArray(numHidden);
      self.hoDelta = oneDFloatArray.new1DFloatArray(numHidden);
    }
  }

  /** Return trun if <code>self</code> has been deleted.
   * @return boolean
   */
  public boolean deletedP() {
    { ChameleonNeuralNetwork self = this;

      return (self.output == Stella.MOST_NEGATIVE_FLOAT);
    }
  }

  /** Unlink the network <code>self</code> from its associated proposition and mark it as deleted.
   */
  public void deleteNeuralNetwork() {
    { ChameleonNeuralNetwork self = this;

      self.unlinkNeuralNetwork();
      self.output = Stella.MOST_NEGATIVE_FLOAT;
    }
  }

  /** Return the proposition linked to <code>self</code>.
   * @return Proposition
   */
  public Proposition getNeuralNetworkProposition() {
    { ChameleonNeuralNetwork self = this;

      return (self.proposition);
    }
  }

  /** Unlink the network <code>self</code> from its associated proposition.
   */
  public void unlinkNeuralNetwork() {
    { ChameleonNeuralNetwork self = this;

      { Proposition prop = self.proposition;

        self.proposition = null;
        if (prop != null) {
          KeyValueList.setDynamicSlotValue(prop.dynamicSlots, Logic.SYM_LOGIC_NEURAL_NET, null, null);
        }
      }
    }
  }

  /** Link the network <code>self</code> to its associated proposition <code>prop</code>.
   * @param prop
   */
  public void linkNeuralNetwork(Proposition prop) {
    { ChameleonNeuralNetwork self = this;

      self.proposition = prop;
      KeyValueList.setDynamicSlotValue(prop.dynamicSlots, Logic.SYM_LOGIC_NEURAL_NET, self, null);
    }
  }

  public static Stella_Object accessChameleonNeuralNetworkSlotValue(ChameleonNeuralNetwork self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Logic.SYM_LOGIC_PROPOSITION) {
      if (setvalueP) {
        self.proposition = ((Proposition)(value));
      }
      else {
        value = self.proposition;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_INPUT) {
      if (setvalueP) {
        self.input = ((oneDFloatArray)(value));
      }
      else {
        value = self.input;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_HIDDEN) {
      if (setvalueP) {
        self.hidden = ((oneDFloatArray)(value));
      }
      else {
        value = self.hidden;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_OUTPUT) {
      if (setvalueP) {
        self.output = ((FloatWrapper)(value)).wrapperValue;
      }
      else {
        value = FloatWrapper.wrapFloat(self.output);
      }
    }
    else if (slotname == Logic.SYM_LOGIC_IH) {
      if (setvalueP) {
        self.ih = ((twoDFloatArray)(value));
      }
      else {
        value = self.ih;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_HO) {
      if (setvalueP) {
        self.ho = ((oneDFloatArray)(value));
      }
      else {
        value = self.ho;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_INPUT_ERROR) {
      if (setvalueP) {
        self.inputError = ((oneDFloatArray)(value));
      }
      else {
        value = self.inputError;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_HIDDEN_ERROR) {
      if (setvalueP) {
        self.hiddenError = ((oneDFloatArray)(value));
      }
      else {
        value = self.hiddenError;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_OUTPUT_ERROR) {
      if (setvalueP) {
        self.outputError = ((FloatWrapper)(value)).wrapperValue;
      }
      else {
        value = FloatWrapper.wrapFloat(self.outputError);
      }
    }
    else if (slotname == Logic.SYM_LOGIC_IH_DELTA) {
      if (setvalueP) {
        self.ihDelta = ((twoDFloatArray)(value));
      }
      else {
        value = self.ihDelta;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_HO_DELTA) {
      if (setvalueP) {
        self.hoDelta = ((oneDFloatArray)(value));
      }
      else {
        value = self.hoDelta;
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
    { ChameleonNeuralNetwork self = this;

      return (Logic.SGT_LOGIC_CHAMELEON_NEURAL_NETWORK);
    }
  }

}

