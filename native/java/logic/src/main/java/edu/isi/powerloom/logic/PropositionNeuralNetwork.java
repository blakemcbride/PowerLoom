//  -*- Mode: Java -*-
//
// PropositionNeuralNetwork.java

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

public class PropositionNeuralNetwork extends NeuralNetwork {
    public Proposition proposition;
    public Vector input;
    public Vector hidden;
    public double output;
    public Vector inputError;
    public Vector hiddenError;
    public two_D_array ih;
    public two_D_array ihDelta;
    public Vector ho;
    public Vector hoDelta;
    public two_D_array ihSlope;
    public two_D_array ihPrevSlope;
    public Vector hoSlope;
    public Vector hoPrevSlope;

  public static PropositionNeuralNetwork newPropositionNeuralNetwork() {
    { PropositionNeuralNetwork self = null;

      self = new PropositionNeuralNetwork();
      self.hoPrevSlope = null;
      self.hoSlope = null;
      self.ihPrevSlope = null;
      self.ihSlope = null;
      self.hoDelta = null;
      self.ho = null;
      self.ihDelta = null;
      self.ih = null;
      self.hiddenError = null;
      self.inputError = null;
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
    { PropositionNeuralNetwork self = this;

      { Vector input = self.input;
        int lastInput = input.length() - 1;
        two_D_array ih = self.ih;
        two_D_array ihDelta = self.ihDelta;
        Vector hidden = self.hidden;
        int lastHidden = hidden.length() - 1;
        Vector hiddenError = self.hiddenError;
        Vector ho = self.ho;
        Vector hoDelta = self.hoDelta;
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
            delta = (Logic.$MOMENTUM_TERM$ * ((FloatWrapper)((hoDelta.theArray)[h])).wrapperValue) + (Logic.$LEARNING_RATE$ * error * ((FloatWrapper)((hidden.theArray)[h])).wrapperValue);
            (ho.theArray)[h] = (FloatWrapper.wrapFloat(((FloatWrapper)((ho.theArray)[h])).wrapperValue + delta));
            (hoDelta.theArray)[h] = (FloatWrapper.wrapFloat(delta));
            { int i = Stella.NULL_INTEGER;
              int iter001 = 0;
              int upperBound001 = lastInput;
              boolean unboundedP001 = upperBound001 == Stella.NULL_INTEGER;

              for (;unboundedP001 ||
                        (iter001 <= upperBound001); iter001 = iter001 + 1) {
                i = iter001;
                delta = (Logic.$MOMENTUM_TERM$ * ((FloatWrapper)((ihDelta.theArray)[((i * ihDelta.nofColumns) + h)])).wrapperValue) + (Logic.$LEARNING_RATE$ * ((FloatWrapper)((hiddenError.theArray)[h])).wrapperValue * ((FloatWrapper)((input.theArray)[i])).wrapperValue);
                (ih.theArray)[((i * ih.nofColumns) + h)] = (FloatWrapper.wrapFloat(((FloatWrapper)((ih.theArray)[((i * ih.nofColumns) + h)])).wrapperValue + delta));
                (ihDelta.theArray)[((i * ihDelta.nofColumns) + h)] = (FloatWrapper.wrapFloat(delta));
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
    { PropositionNeuralNetwork self = this;

      { int lastInput = self.input.length() - 1;
        Vector inputError = self.inputError;
        two_D_array ih = self.ih;
        Vector hidden = self.hidden;
        int lastHidden = hidden.length() - 1;
        Vector hiddenError = self.hiddenError;
        Vector ho = self.ho;
        double output = self.output;

        error = error * output * (1.0 - output);
        { int h = Stella.NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = lastHidden;
          boolean unboundedP000 = upperBound000 == Stella.NULL_INTEGER;

          for (;unboundedP000 ||
                    (iter000 <= upperBound000); iter000 = iter000 + 1) {
            h = iter000;
            (hiddenError.theArray)[h] = (FloatWrapper.wrapFloat(error * ((FloatWrapper)((ho.theArray)[h])).wrapperValue));
            (hiddenError.theArray)[h] = (FloatWrapper.wrapFloat(((FloatWrapper)((hiddenError.theArray)[h])).wrapperValue * ((FloatWrapper)((hidden.theArray)[h])).wrapperValue * (1.0 - ((FloatWrapper)((hidden.theArray)[h])).wrapperValue)));
          }
        }
        { int i = Stella.NULL_INTEGER;
          int iter001 = 0;
          int upperBound001 = lastInput;
          boolean unboundedP001 = upperBound001 == Stella.NULL_INTEGER;

          for (;unboundedP001 ||
                    (iter001 <= upperBound001); iter001 = iter001 + 1) {
            i = iter001;
            (inputError.theArray)[i] = (FloatWrapper.wrapFloat(0.0));
            { int h = Stella.NULL_INTEGER;
              int iter002 = 0;
              int upperBound002 = lastHidden;
              boolean unboundedP002 = upperBound002 == Stella.NULL_INTEGER;

              for (;unboundedP002 ||
                        (iter002 <= upperBound002); iter002 = iter002 + 1) {
                h = iter002;
                (inputError.theArray)[i] = (FloatWrapper.wrapFloat(((FloatWrapper)((inputError.theArray)[i])).wrapperValue + (((FloatWrapper)((hiddenError.theArray)[h])).wrapperValue * ((FloatWrapper)((ih.theArray)[((i * ih.nofColumns) + h)])).wrapperValue)));
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
    { PropositionNeuralNetwork self = this;

      { Vector input = self.input;
        Vector hidden = self.hidden;
        int numIn = input.length();
        int numHidden = hidden.length();
        two_D_array ih = self.ih;
        Vector ho = self.ho;
        double score = 0.0;
        double sum = 0.0;

        (input.theArray)[0] = (FloatWrapper.wrapFloat(1.0));
        { int i = Stella.NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = numHidden - 1;

          for (;iter000 <= upperBound000; iter000 = iter000 + 1) {
            i = iter000;
            { int j = Stella.NULL_INTEGER;
              int iter001 = 0;
              int upperBound001 = numIn - 1;

              for (;iter001 <= upperBound001; iter001 = iter001 + 1) {
                j = iter001;
                sum = sum + (((FloatWrapper)((input.theArray)[j])).wrapperValue * ((FloatWrapper)((ih.theArray)[((j * ih.nofColumns) + i)])).wrapperValue);
              }
            }
            (hidden.theArray)[i] = (FloatWrapper.wrapFloat(1.0 / (1.0 + Math.exp((0 - sum)))));
            score = score + (((FloatWrapper)((hidden.theArray)[i])).wrapperValue * ((FloatWrapper)((ho.theArray)[i])).wrapperValue);
          }
        }
        self.output = 1.0 / (1.0 + Math.exp((0 - score)));
        return (self.output);
      }
    }
  }

  /** Set the current truth-value inputs of the network <code>self</code> to float <code>values</code> in sequence.
   * Missing inputs will be set to 0.0, extra values will be ignored.
   * @param values
   */
  public void setInputValues(Stella_Object values) {
    { PropositionNeuralNetwork self = this;

      { Vector input = self.input;
        int numIn = input.length();
        int cursor = 1;

        (input.theArray)[0] = (FloatWrapper.wrapFloat(1.0));
        { Surrogate testValue000 = Stella_Object.safePrimaryType(values);

          if (testValue000 == Logic.SGT_STELLA_CONS) {
            { Cons values000 = ((Cons)(values));

              { Stella_Object val = null;
                Cons iter000 = values000;

                for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
                  val = iter000.value;
                  if (cursor < numIn) {
                    if (val == null) {
                      val = Logic.$WRAPPED_CHAMELEON_DEFAULT_INPUT_VALUE$;
                    }
                    (input.theArray)[cursor] = (((FloatWrapper)(val)));
                    cursor = cursor + 1;
                  }
                }
              }
            }
          }
          else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_STELLA_LIST)) {
            { List values000 = ((List)(values));

              { Stella_Object val = null;
                Cons iter001 = values000.theConsList;

                for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
                  val = iter001.value;
                  if (cursor < numIn) {
                    if (val == null) {
                      val = Logic.$WRAPPED_CHAMELEON_DEFAULT_INPUT_VALUE$;
                    }
                    (input.theArray)[cursor] = (((FloatWrapper)(val)));
                    cursor = cursor + 1;
                  }
                }
              }
            }
          }
          else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_STELLA_VECTOR)) {
            { Vector values000 = ((Vector)(values));

              { Stella_Object val = null;
                Vector vector000 = values000;
                int index000 = 0;
                int length000 = vector000.length();

                for (;index000 < length000; index000 = index000 + 1) {
                  val = (vector000.theArray)[index000];
                  if (cursor < numIn) {
                    if (val == null) {
                      val = Logic.$WRAPPED_CHAMELEON_DEFAULT_INPUT_VALUE$;
                    }
                    (input.theArray)[cursor] = (((FloatWrapper)(val)));
                    cursor = cursor + 1;
                  }
                }
              }
            }
          }
          else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_STELLA_SEQUENCE)) {
            { Sequence values000 = ((Sequence)(values));

              { Stella_Object val = null;
                Iterator iter002 = ((Iterator)(values000.allocateIterator()));

                while (iter002.nextP()) {
                  val = iter002.value;
                  if (cursor < numIn) {
                    if (val == null) {
                      val = Logic.$WRAPPED_CHAMELEON_DEFAULT_INPUT_VALUE$;
                    }
                    (input.theArray)[cursor] = (((FloatWrapper)(val)));
                    cursor = cursor + 1;
                  }
                }
              }
            }
          }
          else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_STELLA_ITERATOR)) {
            { Iterator values000 = ((Iterator)(values));

              { Stella_Object val = null;
                Iterator iter003 = values000;

                while (iter003.nextP()) {
                  val = iter003.value;
                  if (cursor < numIn) {
                    if (val == null) {
                      val = Logic.$WRAPPED_CHAMELEON_DEFAULT_INPUT_VALUE$;
                    }
                    (input.theArray)[cursor] = (((FloatWrapper)(val)));
                    cursor = cursor + 1;
                  }
                }
              }
            }
          }
          else {
            { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

              stream000.nativeStream.print("`" + testValue000 + "' is not a valid case option");
              throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
            }
          }
        }
        while (cursor < numIn) {
          (input.theArray)[cursor] = (FloatWrapper.wrapFloat(0.0));
          cursor = cursor + 1;
        }
      }
    }
  }

  /** Return the 0-based <code>n</code>-th proposition input error of <code>self</code> (ignores bias unit).
   * @param n
   * @return double
   */
  public double nthInputError(int n) {
    { PropositionNeuralNetwork self = this;

      return (((FloatWrapper)((self.inputError.theArray)[(n + 1)])).wrapperValue);
    }
  }

  /** Return the 0-based <code>n</code>-th proposition input of <code>self</code> (ignores bias unit).
   * @param n
   * @return double
   */
  public double nthInput(int n) {
    { PropositionNeuralNetwork self = this;

      return (((FloatWrapper)((self.input.theArray)[(n + 1)])).wrapperValue);
    }
  }

  /** Return the number of input values expected by <code>self</code> (ignores bias unit).
   * @return int
   */
  public int numberOfInputs() {
    { PropositionNeuralNetwork self = this;

      return (self.input.length() - 1);
    }
  }

  /** Build a neural network for the proposition <code>prop</code>.  This builds a two-layer
   * perceptron network whose input nodes are activated by the truth of <code>prop</code>s arguments and whose
   * output node computes the truth of <code>prop</code>.
   * @param prop
   */
  public void buildPropositionNetwork(Proposition prop) {
    { PropositionNeuralNetwork self = this;

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
    { PropositionNeuralNetwork self = this;

      { int numIn = self.input.length();
        int numHidden = self.hidden.length();

        { int h = Stella.NULL_INTEGER;
          int iter000 = 0;
          int upperBound000 = numHidden - 1;

          for (;iter000 <= upperBound000; iter000 = iter000 + 1) {
            h = iter000;
            (self.hoDelta.theArray)[h] = (FloatWrapper.wrapFloat(0.0));
            { int i = Stella.NULL_INTEGER;
              int iter001 = 0;
              int upperBound001 = numIn - 1;

              for (;iter001 <= upperBound001; iter001 = iter001 + 1) {
                i = iter001;
                (self.ihDelta.theArray)[((i * self.ihDelta.nofColumns) + h)] = (FloatWrapper.wrapFloat(0.0));
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
                (self.ih.theArray)[((j * self.ih.nofColumns) + i)] = (FloatWrapper.wrapFloat(Logic.randomWeight(Logic.$WEIGHT_RANGE$)));
              }
            }
            (self.ho.theArray)[i] = (FloatWrapper.wrapFloat(Logic.randomWeight(Logic.$WEIGHT_RANGE$)));
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
    { PropositionNeuralNetwork self = this;

      numOut = numOut;
      self.input = Vector.newVector(numIn);
      self.hidden = Vector.newVector(numHidden);
      self.ih = two_D_array.new2_D_array(numIn, numHidden);
      self.ihDelta = two_D_array.new2_D_array(numIn, numHidden);
      self.inputError = Vector.newVector(numIn);
      self.hiddenError = Vector.newVector(numHidden);
      self.ho = Vector.newVector(numHidden);
      self.hoDelta = Vector.newVector(numHidden);
      if (Logic.$NEURAL_NETWORK_TRAINING_METHOD$ == Logic.KWD_QUICKPROP) {
        self.ihSlope = two_D_array.new2_D_array(numIn, numHidden);
        self.ihPrevSlope = two_D_array.new2_D_array(numIn, numHidden);
        self.hoSlope = Vector.newVector(numHidden);
        self.hoPrevSlope = Vector.newVector(numHidden);
      }
    }
  }

  /** Return trun if <code>self</code> has been deleted.
   * @return boolean
   */
  public boolean deletedP() {
    { PropositionNeuralNetwork self = this;

      return (self.output == Stella.MOST_NEGATIVE_FLOAT);
    }
  }

  /** Unlink the network <code>self</code> from its associated proposition and mark it as deleted.
   */
  public void deleteNeuralNetwork() {
    { PropositionNeuralNetwork self = this;

      self.unlinkNeuralNetwork();
      self.output = Stella.MOST_NEGATIVE_FLOAT;
    }
  }

  /** Return the proposition linked to <code>self</code>.
   * @return Proposition
   */
  public Proposition getNeuralNetworkProposition() {
    { PropositionNeuralNetwork self = this;

      return (self.proposition);
    }
  }

  /** Unlink the network <code>self</code> from its associated proposition.
   */
  public void unlinkNeuralNetwork() {
    { PropositionNeuralNetwork self = this;

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
    { PropositionNeuralNetwork self = this;

      self.proposition = prop;
      KeyValueList.setDynamicSlotValue(prop.dynamicSlots, Logic.SYM_LOGIC_NEURAL_NET, self, null);
    }
  }

  public static void printNeuralNetwork(PropositionNeuralNetwork net, OutputStream stream) {
    stream.nativeStream.println("defnetwork ");
    Proposition.printProposition(net.proposition, stream, false);
    stream.nativeStream.println();
    stream.nativeStream.println(net.input.length() + " " + net.hidden.length());
    { int i = Stella.NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = net.input.length() - 1;

      for (;iter000 <= upperBound000; iter000 = iter000 + 1) {
        i = iter000;
        { int j = Stella.NULL_INTEGER;
          int iter001 = 0;
          int upperBound001 = net.hidden.length() - 1;

          for (;iter001 <= upperBound001; iter001 = iter001 + 1) {
            j = iter001;
            { double value = ((FloatWrapper)((net.ih.theArray)[((i * net.ih.nofColumns) + j)])).wrapperValue;

              stream.nativeStream.print(" " + value);
            }
          }
        }
      }
    }
    stream.nativeStream.println();
    { FloatWrapper num = null;
      Vector vector000 = net.ho;
      int index000 = 0;
      int length000 = vector000.length();

      for (;index000 < length000; index000 = index000 + 1) {
        num = ((FloatWrapper)((vector000.theArray)[index000]));
        { double value = num.wrapperValue;

          stream.nativeStream.print(" " + value);
        }
      }
    }
    stream.nativeStream.println();
  }

  public static void saveNeuralNetwork(PropositionNeuralNetwork net, String file) {
    { OutputFileStream fptr = OutputFileStream.newOutputFileStream(file);

      PropositionNeuralNetwork.printNeuralNetwork(net, fptr);
      fptr.free();
    }
  }

  public static double activatePropositionalNeuralNetwork(PropositionNeuralNetwork net) {
    { int numIn = net.input.length();
      int numHidden = net.hidden.length();
      Vector arguments = net.proposition.arguments;
      int stop = numIn - 1;
      Vector input = net.input;
      Vector hidden = net.hidden;
      two_D_array ih = net.ih;
      Vector ho = net.ho;
      double score = 0.0;
      double sum = 0.0;

      Logic.$ACTIVATED_NETWORKS$.push(net);
      (net.input.theArray)[0] = (FloatWrapper.wrapFloat(1.0));
      { int i = Stella.NULL_INTEGER;
        int iter000 = 1;
        int upperBound000 = stop;
        boolean unboundedP000 = upperBound000 == Stella.NULL_INTEGER;

        for (;unboundedP000 ||
                  (iter000 <= upperBound000); iter000 = iter000 + 1) {
          i = iter000;
          if (((FloatWrapper)(KeyValueList.dynamicSlotValue(((Proposition)((arguments.theArray)[(i - 1)])).dynamicSlots, Logic.SYM_LOGIC_MATCH_SCORE, Stella.NULL_FLOAT_WRAPPER))).wrapperValue != Stella.NULL_FLOAT) {
            (input.theArray)[i] = (FloatWrapper.wrapFloat(((FloatWrapper)(KeyValueList.dynamicSlotValue(((Proposition)((arguments.theArray)[(i - 1)])).dynamicSlots, Logic.SYM_LOGIC_MATCH_SCORE, Stella.NULL_FLOAT_WRAPPER))).wrapperValue));
          }
          else {
            (input.theArray)[i] = (FloatWrapper.wrapFloat(0.0));
          }
        }
      }
      { int i = Stella.NULL_INTEGER;
        int iter001 = 0;
        int upperBound001 = numHidden - 1;

        for (;iter001 <= upperBound001; iter001 = iter001 + 1) {
          i = iter001;
          { int j = Stella.NULL_INTEGER;
            int iter002 = 0;
            int upperBound002 = stop;
            boolean unboundedP001 = upperBound002 == Stella.NULL_INTEGER;

            for (;unboundedP001 ||
                      (iter002 <= upperBound002); iter002 = iter002 + 1) {
              j = iter002;
              sum = sum + (((FloatWrapper)((input.theArray)[j])).wrapperValue * ((FloatWrapper)((ih.theArray)[((j * ih.nofColumns) + i)])).wrapperValue);
            }
          }
          (hidden.theArray)[i] = (FloatWrapper.wrapFloat(1.0 / (1.0 + Math.exp((0 - sum)))));
          score = score + (((FloatWrapper)((hidden.theArray)[i])).wrapperValue * ((FloatWrapper)((ho.theArray)[i])).wrapperValue);
        }
      }
      if ((1.0 + Math.exp((0 - score))) == 0.0) {
        Stella.STANDARD_OUTPUT.nativeStream.println("Sum is " + score);
      }
      net.output = 1.0 / (1.0 + Math.exp((0 - score)));
      KeyValueList.setDynamicSlotValue(net.proposition.dynamicSlots, Logic.SYM_LOGIC_MATCH_SCORE, FloatWrapper.wrapFloat(net.output), Stella.NULL_FLOAT_WRAPPER);
      return (net.output);
    }
  }

  public static void randomizeNeuralNetwork(PropositionNeuralNetwork net) {
    { int numIn = net.input.length();
      int numHidden = net.hidden.length();

      { int h = Stella.NULL_INTEGER;
        int iter000 = 0;
        int upperBound000 = numHidden - 1;

        for (;iter000 <= upperBound000; iter000 = iter000 + 1) {
          h = iter000;
          (net.hoDelta.theArray)[h] = (FloatWrapper.wrapFloat(0.0));
          { int i = Stella.NULL_INTEGER;
            int iter001 = 0;
            int upperBound001 = numIn - 1;

            for (;iter001 <= upperBound001; iter001 = iter001 + 1) {
              i = iter001;
              (net.ihDelta.theArray)[((i * net.ihDelta.nofColumns) + h)] = (FloatWrapper.wrapFloat(0.0));
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
              (net.ih.theArray)[((j * net.ih.nofColumns) + i)] = (FloatWrapper.wrapFloat(Logic.randomWeight(Logic.$WEIGHT_RANGE$)));
            }
          }
          (net.ho.theArray)[i] = (FloatWrapper.wrapFloat(Logic.randomWeight(Logic.$WEIGHT_RANGE$)));
        }
      }
    }
  }

  public static void clearSlopes(PropositionNeuralNetwork net) {
    { int h = Stella.NULL_INTEGER;
      int iter000 = 0;
      int upperBound000 = net.hidden.length() - 1;

      for (;iter000 <= upperBound000; iter000 = iter000 + 1) {
        h = iter000;
        { int i = Stella.NULL_INTEGER;
          int iter001 = 0;
          int upperBound001 = net.input.length() - 1;

          for (;iter001 <= upperBound001; iter001 = iter001 + 1) {
            i = iter001;
            (net.ihPrevSlope.theArray)[((i * net.ihPrevSlope.nofColumns) + h)] = (((FloatWrapper)((net.ihSlope.theArray)[((i * net.ihSlope.nofColumns) + h)])));
            (net.ihSlope.theArray)[((i * net.ihSlope.nofColumns) + h)] = (FloatWrapper.wrapFloat(((FloatWrapper)((net.ih.theArray)[((i * net.ih.nofColumns) + h)])).wrapperValue * Logic.$WEIGHT_DECAY$));
          }
        }
        (net.hoPrevSlope.theArray)[h] = (((FloatWrapper)((net.hoSlope.theArray)[h])));
        (net.hoSlope.theArray)[h] = (FloatWrapper.wrapFloat(((FloatWrapper)((net.ho.theArray)[h])).wrapperValue * Logic.$WEIGHT_DECAY$));
      }
    }
  }

  public static Stella_Object accessPropositionNeuralNetworkSlotValue(PropositionNeuralNetwork self, Symbol slotname, Stella_Object value, boolean setvalueP) {
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
        self.input = ((Vector)(value));
      }
      else {
        value = self.input;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_HIDDEN) {
      if (setvalueP) {
        self.hidden = ((Vector)(value));
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
    else if (slotname == Logic.SYM_LOGIC_INPUT_ERROR) {
      if (setvalueP) {
        self.inputError = ((Vector)(value));
      }
      else {
        value = self.inputError;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_HIDDEN_ERROR) {
      if (setvalueP) {
        self.hiddenError = ((Vector)(value));
      }
      else {
        value = self.hiddenError;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_IH) {
      if (setvalueP) {
        self.ih = ((two_D_array)(value));
      }
      else {
        value = self.ih;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_IH_DELTA) {
      if (setvalueP) {
        self.ihDelta = ((two_D_array)(value));
      }
      else {
        value = self.ihDelta;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_HO) {
      if (setvalueP) {
        self.ho = ((Vector)(value));
      }
      else {
        value = self.ho;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_HO_DELTA) {
      if (setvalueP) {
        self.hoDelta = ((Vector)(value));
      }
      else {
        value = self.hoDelta;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_IH_SLOPE) {
      if (setvalueP) {
        self.ihSlope = ((two_D_array)(value));
      }
      else {
        value = self.ihSlope;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_IH_PREV_SLOPE) {
      if (setvalueP) {
        self.ihPrevSlope = ((two_D_array)(value));
      }
      else {
        value = self.ihPrevSlope;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_HO_SLOPE) {
      if (setvalueP) {
        self.hoSlope = ((Vector)(value));
      }
      else {
        value = self.hoSlope;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_HO_PREV_SLOPE) {
      if (setvalueP) {
        self.hoPrevSlope = ((Vector)(value));
      }
      else {
        value = self.hoPrevSlope;
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
    { PropositionNeuralNetwork self = this;

      return (Logic.SGT_LOGIC_PROPOSITION_NEURAL_NETWORK);
    }
  }

}

