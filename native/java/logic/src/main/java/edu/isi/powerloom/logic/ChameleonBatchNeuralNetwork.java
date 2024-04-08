//  -*- Mode: Java -*-
//
// ChameleonBatchNeuralNetwork.java

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

/** Chameleon neural network that supports batch operations via emulation.
 * @author Stella Java Translator
 */
public class ChameleonBatchNeuralNetwork extends ChameleonNeuralNetwork {
    /** Each element is a set of values that may be legally passed to <code>setInputValues</code>.
     */
    public VectorSequence inputBatch;
    /** Each element is a key to identify a specific set of input values.
     */
    public VectorSequence keyBatch;
    /** Each element is a target output value for the respective set of input values.
     */
    public VectorSequence targetBatch;
    public oneDFloatArray outputBatch;
    /** Copies of <code>inputError</code> but without the bias unit, thus shifted by 1.
     */
    public VectorSequence inputErrorBatch;

  public static ChameleonBatchNeuralNetwork newChameleonBatchNeuralNetwork() {
    { ChameleonBatchNeuralNetwork self = null;

      self = new ChameleonBatchNeuralNetwork();
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
      self.inputErrorBatch = null;
      self.outputBatch = null;
      self.targetBatch = null;
      self.keyBatch = null;
      self.inputBatch = null;
      return (self);
    }
  }

  public void batchUpdateNetworkWeights() {
    { ChameleonBatchNeuralNetwork self = this;

      { edu.isi.stella.Stella_Object[] targets = self.targetBatch.theArray;
        double output = 0.0;
        double error = 0.0;

        { Stella_Object input = null;
          VectorSequence vector000 = self.inputBatch;
          int index000 = 0;
          int length000 = vector000.sequenceLength;
          int i = Stella.NULL_INTEGER;
          int iter000 = 0;

          for (;index000 < length000; index000 = index000 + 1, iter000 = iter000 + 1) {
            input = (vector000.theArray)[index000];
            i = iter000;
            self.setInputValues(input);
            output = self.forwardPropagateInputs();
            error = ((FloatWrapper)(targets[i])).wrapperValue - output;
            self.backwardPropagateError(error);
            self.updateNetworkWeights(error);
          }
        }
      }
    }
  }

  public void batchBackwardPropagateError() {
    { ChameleonBatchNeuralNetwork self = this;

      { edu.isi.stella.Stella_Object[] targets = self.targetBatch.theArray;
        VectorSequence errors = self.inputErrorBatch;
        double output = 0.0;
        double error = 0.0;

        errors.clear();
        { Stella_Object input = null;
          VectorSequence vector000 = self.inputBatch;
          int index000 = 0;
          int length000 = vector000.sequenceLength;
          int i = Stella.NULL_INTEGER;
          int iter000 = 0;

          for (;index000 < length000; index000 = index000 + 1, iter000 = iter000 + 1) {
            input = (vector000.theArray)[index000];
            i = iter000;
            self.setInputValues(input);
            output = self.forwardPropagateInputs();
            error = ((FloatWrapper)(targets[i])).wrapperValue - output;
            self.backwardPropagateError(error);
            errors.insert(self.copyInputError());
          }
        }
      }
    }
  }

  public oneDFloatArray copyInputError() {
    { ChameleonBatchNeuralNetwork self = this;

      { oneDFloatArray inputerror = self.inputError;
        oneDFloatArray copyerror = oneDFloatArray.new1DFloatArray(inputerror.dim1);

        Logic.copyFloatValuesToBuffer(inputerror, copyerror.theArray, 0, inputerror.dim1);
        return (copyerror);
      }
    }
  }

  public oneDFloatArray batchForwardPropagateInputs() {
    { ChameleonBatchNeuralNetwork self = this;

      { double[] outputs = self.outputBatch.theArray;

        { Stella_Object input = null;
          VectorSequence vector000 = self.inputBatch;
          int index000 = 0;
          int length000 = vector000.sequenceLength;
          int i = Stella.NULL_INTEGER;
          int iter000 = 0;

          for (;index000 < length000; index000 = index000 + 1, iter000 = iter000 + 1) {
            input = (vector000.theArray)[index000];
            i = iter000;
            self.setInputValues(input);
            outputs[i] = self.forwardPropagateInputs();
          }
        }
        return (self.outputBatch);
      }
    }
  }

  public double nthBatchOutput(int n) {
    { ChameleonBatchNeuralNetwork self = this;

      return (self.outputBatch.theArray[n]);
    }
  }

  public double nthKthBatchInputError(int n, int k) {
    { ChameleonBatchNeuralNetwork self = this;

      return (((oneDFloatArray)((self.inputErrorBatch.theArray)[n])).theArray[k + 1]);
    }
  }

  public Stella_Object nthBatchKey(int n) {
    { ChameleonBatchNeuralNetwork self = this;

      return ((self.keyBatch.theArray)[n]);
    }
  }

  public void pushTargetValue(double value) {
    { ChameleonBatchNeuralNetwork self = this;

      self.targetBatch.insert(FloatWrapper.wrapFloat(value));
    }
  }

  public void pushInputValues(Stella_Object key, Stella_Object values) {
    { ChameleonBatchNeuralNetwork self = this;

      self.keyBatch.insert(key);
      self.inputBatch.insert(values);
    }
  }

  public boolean batchIsFullP() {
    { ChameleonBatchNeuralNetwork self = this;

      return (self.inputBatch.sequenceLength >= self.outputBatch.length());
    }
  }

  public int currentBatchSize() {
    { ChameleonBatchNeuralNetwork self = this;

      return (self.inputBatch.sequenceLength);
    }
  }

  public void clearBatchArrays() {
    { ChameleonBatchNeuralNetwork self = this;

      self.inputBatch.clear();
      self.keyBatch.clear();
      self.targetBatch.clear();
      self.inputErrorBatch.clear();
    }
  }

  public void allocateNetworkArrays(int numIn, int numHidden, int numOut) {
    { ChameleonBatchNeuralNetwork self = this;

      super.allocateNetworkArrays(numIn, numHidden, numOut);
      self.inputBatch = VectorSequence.newVectorSequence(Logic.$NEURAL_NETWORK_BATCH_SIZE$);
      self.keyBatch = VectorSequence.newVectorSequence(Logic.$NEURAL_NETWORK_BATCH_SIZE$);
      self.outputBatch = oneDFloatArray.new1DFloatArray(Logic.$NEURAL_NETWORK_BATCH_SIZE$);
      self.targetBatch = VectorSequence.newVectorSequence(Logic.$NEURAL_NETWORK_BATCH_SIZE$);
      self.inputErrorBatch = VectorSequence.newVectorSequence(Logic.$NEURAL_NETWORK_BATCH_SIZE$);
    }
  }

  public static Stella_Object accessChameleonBatchNeuralNetworkSlotValue(ChameleonBatchNeuralNetwork self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Logic.SYM_LOGIC_INPUT_BATCH) {
      if (setvalueP) {
        self.inputBatch = ((VectorSequence)(value));
      }
      else {
        value = self.inputBatch;
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
    else if (slotname == Logic.SYM_LOGIC_TARGET_BATCH) {
      if (setvalueP) {
        self.targetBatch = ((VectorSequence)(value));
      }
      else {
        value = self.targetBatch;
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
        self.inputErrorBatch = ((VectorSequence)(value));
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
    { ChameleonBatchNeuralNetwork self = this;

      return (Logic.SGT_LOGIC_CHAMELEON_BATCH_NEURAL_NETWORK);
    }
  }

}

