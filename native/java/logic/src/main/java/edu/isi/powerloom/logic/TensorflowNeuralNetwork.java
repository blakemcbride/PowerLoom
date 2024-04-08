//  -*- Mode: Java -*-
//
// TensorflowNeuralNetwork.java

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

/** Neural network that is implemented by callbacks to TensorFlow.
 * @author Stella Java Translator
 */
public class TensorflowNeuralNetwork extends VectorNeuralNetwork {
    public Proposition proposition;
    public LongIntegerWrapper model;

  public static TensorflowNeuralNetwork newTensorflowNeuralNetwork() {
    { TensorflowNeuralNetwork self = null;

      self = new TensorflowNeuralNetwork();
      self.nVectorArgumentInputs = -1;
      self.nVectorArgumentSpecs = -1;
      self.nVectorArguments = -1;
      self.model = null;
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
    { TensorflowNeuralNetwork self = this;

      edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_NEURAL_NETWORKdUPDATE_NETWORK_WEIGHTS.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {self, new Double(error)});
    }
  }

  /** Given a properly forward activated network <code>self</code> for the current set of inputs,
   * and a training <code>error</code> between the current output and the goal value, backpropagate the error and
   * update <code>self</code>s vector of input errors.  Reads output, hidden activations and weights and updates
   * hidden errors and input errors.
   * @param error
   */
  public void backwardPropagateError(double error) {
    { TensorflowNeuralNetwork self = this;

      edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_NEURAL_NETWORKdBACKWARD_PROPAGATE_ERROR.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {self, new Double(error)});
    }
  }

  /** Activates the current inputs of the network <code>self</code> to compute its output.
   * Sets <code>self</code>s <code>output</code> slot and returns the computed value.  Reads input activations and
   * weights and updates hidden and output activations.
   * @return double
   */
  public double forwardPropagateInputs() {
    { TensorflowNeuralNetwork self = this;

      return (((Double)(edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_NEURAL_NETWORKdFORWARD_PROPAGATE_INPUTS.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {self}))).doubleValue());
    }
  }

  /** Set the current vector inputs of the network <code>self</code> to the vectors described by <code>vectorspecs</code>.
   * Each vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs
   * are translated into actual numeric vectors such as embeddings is specific to the particular neural network type.
   * @param vectorspecs
   */
  public void setVectorInputValues(Stella_Object vectorspecs) {
    { TensorflowNeuralNetwork self = this;

      edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_NEURAL_NETWORKdSET_VECTOR_INPUT_VALUES.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {self, vectorspecs.consify()});
    }
  }

  /** Generate a single argument spec for <code>arg</code> that can be used for <code>setVectorInputValues</code>.
   * <code>arg</code> can either be a proposition or justification.
   * @param arg
   * @return Stella_Object
   */
  public Stella_Object getVectorArgumentSpec(Stella_Object arg) {
    { TensorflowNeuralNetwork self = this;

      { Stella_Object spec = super.getVectorArgumentSpec(arg);
        Cons evalargs = Stella.NIL;

        if (Stella_Object.safePrimaryType(spec) == Logic.SGT_STELLA_CONS) {
          { Cons spec000 = ((Cons)(spec));

            { Stella_Object elt = null;
              Cons iter000 = spec000;
              Cons collect000 = null;

              for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
                elt = iter000.value;
                if (Stella_Object.longIntegerP(elt) ||
                    Stella_Object.stringP(elt)) {
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
    { TensorflowNeuralNetwork self = this;

      edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_NEURAL_NETWORKdSET_INPUT_VALUES.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {self, values.consify()});
    }
  }

  /** Return the 0-based <code>n</code>-th proposition input error of <code>self</code> (ignores bias unit).
   * @param n
   * @return double
   */
  public double nthInputError(int n) {
    { TensorflowNeuralNetwork self = this;

      return (((Double)(edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_NEURAL_NETWORKdNTH_INPUT_ERROR.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {self, new Integer(n)}))).doubleValue());
    }
  }

  /** Return the 0-based <code>n</code>-th proposition input of <code>self</code> (ignores bias unit).
   * @param n
   * @return double
   */
  public double nthInput(int n) {
    { TensorflowNeuralNetwork self = this;

      return (((Double)(edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_NEURAL_NETWORKdNTH_INPUT.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {self, new Integer(n)}))).doubleValue());
    }
  }

  /** Return the number of input values expected by <code>self</code> (ignores bias unit).
   * @return int
   */
  public int numberOfInputs() {
    { TensorflowNeuralNetwork self = this;

      return (((Integer)(edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_NEURAL_NETWORKdNUMBER_OF_INPUTS.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {self}))).intValue());
    }
  }

  /** Build a neural network for the proposition <code>prop</code>.  This builds a two-layer
   * perceptron network whose input nodes are activated by the truth of <code>prop</code>s arguments and whose
   * output node computes the truth of <code>prop</code>.
   * @param prop
   */
  public void buildPropositionNetwork(Proposition prop) {
    { TensorflowNeuralNetwork self = this;

      edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_NEURAL_NETWORKdBUILD_PROPOSITION_NETWORK.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {self, prop});
      self.linkNeuralNetwork(prop);
    }
  }

  /** Initialize the weights of the neural network <code>self</code> - eiher randomly or from a saved state.
   */
  public void initializeNetworkWeights() {
    { TensorflowNeuralNetwork self = this;

      edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_NEURAL_NETWORKdINITIALIZE_NETWORK_WEIGHTS.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {self});
    }
  }

  /** Randomize the weights of the neural network <code>self</code>.
   */
  public void randomizeNetworkWeights() {
    { TensorflowNeuralNetwork self = this;

      edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_NEURAL_NETWORKdRANDOMIZE_NETWORK_WEIGHTS.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {self});
    }
  }

  /** Allocates array space for a neural network with given number of input, hidden and output units.
   * @param numIn
   * @param numHidden
   * @param numOut
   */
  public void allocateNetworkArrays(int numIn, int numHidden, int numOut) {
    { TensorflowNeuralNetwork self = this;

      edu.isi.stella.javalib.Native.funcall(((FunctionCodeWrapper)(Logic.SYM_LOGIC_TENSORFLOW_NEURAL_NETWORKdALLOCATE_NETWORK_ARRAYS.symbolValueAndPlist.value)).wrapperValue, null, new java.lang.Object [] {self, new Integer(numIn), new Integer(numHidden), new Integer(numOut)});
    }
  }

  /** Return trun if <code>self</code> has been deleted.
   * @return boolean
   */
  public boolean deletedP() {
    { TensorflowNeuralNetwork self = this;

      return (Stella_Object.eqlToLongIntegerP(self.model, Stella.MOST_NEGATIVE_LONG_INTEGER));
    }
  }

  /** Unlink the network <code>self</code> from its associated proposition and mark it as deleted.
   */
  public void deleteNeuralNetwork() {
    { TensorflowNeuralNetwork self = this;

      self.unlinkNeuralNetwork();
      self.model = Stella.wrapLongInteger(Stella.MOST_NEGATIVE_LONG_INTEGER);
    }
  }

  /** Return the proposition linked to <code>self</code>.
   * @return Proposition
   */
  public Proposition getNeuralNetworkProposition() {
    { TensorflowNeuralNetwork self = this;

      return (self.proposition);
    }
  }

  /** Unlink the network <code>self</code> from its associated proposition.
   */
  public void unlinkNeuralNetwork() {
    { TensorflowNeuralNetwork self = this;

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
    { TensorflowNeuralNetwork self = this;

      self.proposition = prop;
      KeyValueList.setDynamicSlotValue(prop.dynamicSlots, Logic.SYM_LOGIC_NEURAL_NET, self, null);
    }
  }

  public static Stella_Object accessTensorflowNeuralNetworkSlotValue(TensorflowNeuralNetwork self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Logic.SYM_LOGIC_PROPOSITION) {
      if (setvalueP) {
        self.proposition = ((Proposition)(value));
      }
      else {
        value = self.proposition;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_MODEL) {
      if (setvalueP) {
        self.model = ((LongIntegerWrapper)(value));
      }
      else {
        value = self.model;
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
    { TensorflowNeuralNetwork self = this;

      return (Logic.SGT_LOGIC_TENSORFLOW_NEURAL_NETWORK);
    }
  }

}

