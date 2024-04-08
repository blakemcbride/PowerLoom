//  -*- Mode: Java -*-
//
// VectorNeuralNetwork.java

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

/** Neural network that supports vector input arguments.
 * @author Stella Java Translator
 */
public class VectorNeuralNetwork extends NeuralNetwork {
    public int nVectorArguments;
    public int nVectorArgumentSpecs;
    public int nVectorArgumentInputs;

  public static VectorNeuralNetwork newVectorNeuralNetwork() {
    { VectorNeuralNetwork self = null;

      self = new VectorNeuralNetwork();
      self.nVectorArgumentInputs = -1;
      self.nVectorArgumentSpecs = -1;
      self.nVectorArguments = -1;
      return (self);
    }
  }

  /** Generate a single argument spec for <code>arg</code> that can be used for <code>setVectorInputValues</code>.
   * <code>arg</code> can either be a proposition or justification.
   * @param arg
   * @return Stella_Object
   */
  public Stella_Object getVectorArgumentSpec(Stella_Object arg) {
    { VectorNeuralNetwork self = this;

      { Surrogate testValue000 = Stella_Object.safePrimaryType(arg);

        if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_JUSTIFICATION)) {
          { Justification arg000 = ((Justification)(arg));

            { Object old$Currentjustification$000 = Logic.$CURRENTJUSTIFICATION$.get();

              try {
                Native.setSpecial(Logic.$CURRENTJUSTIFICATION$, arg000);
                return (Proposition.generateProposition(arg000.proposition));

              } finally {
                Logic.$CURRENTJUSTIFICATION$.set(old$Currentjustification$000);
              }
            }
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, Logic.SGT_LOGIC_PROPOSITION)) {
          { Proposition arg000 = ((Proposition)(arg));

            return (Proposition.generateProposition(arg000));
          }
        }
        else {
          { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

            stream000.nativeStream.print("`" + testValue000 + "' is not a valid case option");
            throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
          }
        }
      }
    }
  }

  /** Set the current vector inputs of the network <code>self</code> to the vectors described by <code>vectorspecs</code>.
   * Each vector spec describes a vector-generating proposition that produces one or more vectors.  How those specs
   * are translated into actual numeric vectors such as embeddings is specific to the particular neural network type.
   * @param vectorspecs
   */
  public void setVectorInputValues(Stella_Object vectorspecs) {
    { VectorNeuralNetwork self = this;

      vectorspecs = vectorspecs;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("set-vector-input-values: Not defined on `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  /** Return the total number of input positions to store all elements of all vector
   * arguments of <code>prop</code>.  <code>prop</code> can be NULL in which case the linked proposition will be used.
   * @param prop
   * @return int
   */
  public int numberOfVectorArgumentInputs(Proposition prop) {
    { VectorNeuralNetwork self = this;

      { int ninps = self.nVectorArgumentInputs;

        if (ninps < 0) {
          if (prop == null) {
            prop = self.getNeuralNetworkProposition();
          }
          ninps = 0;
          { Stella_Object arg = null;
            Vector vector000 = prop.arguments;
            int index000 = 0;
            int length000 = vector000.length();

            for (;index000 < length000; index000 = index000 + 1) {
              arg = (vector000.theArray)[index000];
              if (self.vectorArgumentP(((Proposition)(arg)))) {
                { Stella_Object rel = ((Surrogate)(((Proposition)(arg)).operator)).surrogateValue;
                  Stella_Object arity = Logic.accessBinaryValue(rel, Logic.SGT_CHAMELEON_VECTOR_ARITY);
                  Stella_Object dims = Logic.accessBinaryValue(rel, Logic.SGT_CHAMELEON_VECTOR_DIMENSIONS);

                  if (!(Stella_Object.integerP(arity) &&
                      Stella_Object.integerP(dims))) {
                    { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

                      stream000.nativeStream.print("number-of-vector-argument-inputs: Missing or incorrect arity/dimension specifications for `" + rel + "'");
                      throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
                    }
                  }
                  ninps = ((int)(ninps + (((NumberWrapper)(arity)).numberWrapperToFloat() * ((NumberWrapper)(dims)).numberWrapperToFloat())));
                }
              }
            }
          }
          self.nVectorArgumentInputs = ninps;
        }
        return (ninps);
      }
    }
  }

  /** Return the total number of argument specs generated by vector arguments of <code>prop</code>.
   * This is only different than <code>numberOfVectorArguments</code> if at least one of <code>prop</code>s vector argument
   * relations has arity &gt; 1.  <code>prop</code> can be NULL in which case the linked proposition will be used.
   * @param prop
   * @return int
   */
  public int numberOfVectorArgumentSpecs(Proposition prop) {
    { VectorNeuralNetwork self = this;

      { int ninps = self.nVectorArgumentSpecs;

        if (ninps < 0) {
          if (prop == null) {
            prop = self.getNeuralNetworkProposition();
          }
          ninps = 0;
          { Stella_Object arg = null;
            Vector vector000 = prop.arguments;
            int index000 = 0;
            int length000 = vector000.length();

            for (;index000 < length000; index000 = index000 + 1) {
              arg = (vector000.theArray)[index000];
              if (self.vectorArgumentP(((Proposition)(arg)))) {
                { Stella_Object rel = ((Surrogate)(((Proposition)(arg)).operator)).surrogateValue;
                  Stella_Object arity = Logic.accessBinaryValue(rel, Logic.SGT_CHAMELEON_VECTOR_ARITY);

                  if (!(Stella_Object.integerP(arity))) {
                    { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

                      stream000.nativeStream.print("number-of-vector-argument-specs: Missing or incorrect arity specifications for `" + rel + "'");
                      throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
                    }
                  }
                  ninps = ((int)(ninps + ((NumberWrapper)(arity)).numberWrapperToFloat()));
                }
              }
            }
          }
          self.nVectorArgumentSpecs = ninps;
        }
        return (ninps);
      }
    }
  }

  /** Return the 0-based input position of vector argument <code>arg</code>.  Ignores bias unit which
   * is a network-implementation-specific detail.  If <code>arg</code> is not a vector argument, returns -1.
   * @param arg
   * @return int
   */
  public int vectorArgumentIndex(Proposition arg) {
    { VectorNeuralNetwork self = this;

      { MemoizationTable memoTable000 = null;
        Cons memoizedEntry000 = null;
        Stella_Object memoizedValue000 = null;

        if (Stella.$MEMOIZATION_ENABLEDp$) {
          memoTable000 = ((MemoizationTable)(Logic.SGT_LOGIC_M_VECTOR_NEURAL_NETWORKdVECTOR_ARGUMENT_INDEX_MEMO_TABLE_000.surrogateValue));
          if (memoTable000 == null) {
            Surrogate.initializeMemoizationTable(Logic.SGT_LOGIC_M_VECTOR_NEURAL_NETWORKdVECTOR_ARGUMENT_INDEX_MEMO_TABLE_000, "(:MAX-VALUES 1000 :TIMESTAMPS (:KB-UPDATE))");
            memoTable000 = ((MemoizationTable)(Logic.SGT_LOGIC_M_VECTOR_NEURAL_NETWORKdVECTOR_ARGUMENT_INDEX_MEMO_TABLE_000.surrogateValue));
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
          memoizedValue000 = IntegerWrapper.wrapInteger(NeuralNetwork.helpComputeArgumentIndex(self, arg, Logic.KWD_VECTOR));
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

  /** Return the number of arguments of <code>prop</code> that yield one or more vectors
   * for <code>self</code>s inputs.  <code>prop</code> can be NULL in which case the linked proposition will be used.
   * @param prop
   * @return int
   */
  public int numberOfVectorArguments(Proposition prop) {
    { VectorNeuralNetwork self = this;

      { int nargs = self.nVectorArguments;

        if (nargs < 0) {
          if (prop == null) {
            prop = self.getNeuralNetworkProposition();
          }
          nargs = 0;
          { Stella_Object arg = null;
            Vector vector000 = prop.arguments;
            int index000 = 0;
            int length000 = vector000.length();

            for (;index000 < length000; index000 = index000 + 1) {
              arg = (vector000.theArray)[index000];
              if (self.vectorArgumentP(((Proposition)(arg)))) {
                nargs = nargs + 1;
              }
            }
          }
          self.nVectorArguments = nargs;
        }
        return (nargs);
      }
    }
  }

  /** Return TRUE if <code>self</code> has at least one vector input argument.
   * @return boolean
   */
  public boolean hasVectorArgumentsP() {
    { VectorNeuralNetwork self = this;

      { int nargs = self.nVectorArguments;

        if (nargs < 0) {
          nargs = self.numberOfVectorArguments(null);
        }
        return (nargs > 0);
      }
    }
  }

  /** Return TRUE if <code>arg</code> yields one or more vectors for <code>self</code>s inputs.
   * @param arg
   * @return boolean
   */
  public boolean vectorArgumentP(Proposition arg) {
    { VectorNeuralNetwork self = this;

      { Stella_Object argrel = ((Surrogate)(arg.operator)).surrogateValue;

        return ((argrel != null) &&
            Logic.testPropertyP(argrel, Logic.SGT_CHAMELEON_VECTOR_RELATION));
      }
    }
  }

  public static Stella_Object accessVectorNeuralNetworkSlotValue(VectorNeuralNetwork self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Logic.SYM_LOGIC_N_VECTOR_ARGUMENTS) {
      if (setvalueP) {
        self.nVectorArguments = ((IntegerWrapper)(value)).wrapperValue;
      }
      else {
        value = IntegerWrapper.wrapInteger(self.nVectorArguments);
      }
    }
    else if (slotname == Logic.SYM_LOGIC_N_VECTOR_ARGUMENT_SPECS) {
      if (setvalueP) {
        self.nVectorArgumentSpecs = ((IntegerWrapper)(value)).wrapperValue;
      }
      else {
        value = IntegerWrapper.wrapInteger(self.nVectorArgumentSpecs);
      }
    }
    else if (slotname == Logic.SYM_LOGIC_N_VECTOR_ARGUMENT_INPUTS) {
      if (setvalueP) {
        self.nVectorArgumentInputs = ((IntegerWrapper)(value)).wrapperValue;
      }
      else {
        value = IntegerWrapper.wrapInteger(self.nVectorArgumentInputs);
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
    { VectorNeuralNetwork self = this;

      return (Logic.SGT_LOGIC_VECTOR_NEURAL_NETWORK);
    }
  }

}

