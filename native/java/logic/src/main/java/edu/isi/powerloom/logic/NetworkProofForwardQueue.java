//  -*- Mode: Java -*-
//
// NetworkProofForwardQueue.java

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

public class NetworkProofForwardQueue extends NetworkProofQueue {
  public static NetworkProofForwardQueue newNetworkProofForwardQueue() {
    { NetworkProofForwardQueue self = null;

      self = new NetworkProofForwardQueue();
      self.nQueued = 0;
      self.minBatchSize = Native.floor(Logic.$NEURAL_NETWORK_BATCH_SIZE$ * 0.8);
      self.activeNetworks = HashSet.newHashSet();
      self.prerequisites = KeyValueMap.newKeyValueMap();
      self.dependents = KeyValueMap.newKeyValueMap();
      return (self);
    }
  }

  public void executeNetworkOperation(NeuralNetwork net, boolean forceP) {
    { NetworkProofForwardQueue queue = this;

      { int batchsize = net.currentBatchSize();

        if ((batchsize > 0) &&
            (forceP ||
             (batchsize >= queue.minBatchSize))) {
          { double output = 0.0;
            Justification proof = null;
            VectorSequence scoredproofs = VectorSequence.newVectorSequence(batchsize);

            net.batchForwardPropagateInputs();
            { int i = Stella.NULL_INTEGER;
              int iter000 = 0;
              int upperBound000 = batchsize - 1;

              for (;iter000 <= upperBound000; iter000 = iter000 + 1) {
                i = iter000;
                output = net.nthBatchOutput(i);
                proof = ((Justification)(net.nthBatchKey(i)));
                proof.matchScore = output;
                scoredproofs.insert(proof);
              }
            }
            queue.nQueued = queue.nQueued - batchsize;
            net.clearBatchArrays();
            { Justification proof000 = null;
              VectorSequence vector000 = scoredproofs;
              int index000 = 0;
              int length000 = vector000.sequenceLength;

              for (;index000 < length000; index000 = index000 + 1) {
                proof000 = ((Justification)((vector000.theArray)[index000]));
                { Justification dep = null;
                  Cons iter001 = queue.getDependents(proof000);

                  for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
                    dep = ((Justification)(iter001.value));
                    queue.notifyOfCompletion(dep, proof000);
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  public void queueNetworkOperation(Justification proof) {
    { NetworkProofForwardQueue queue = this;

      { double score = 0.0;

        { Keyword testValue000 = proof.inferenceRule;

          if (testValue000 == Logic.KWD_PRIMITIVE_STRATEGY) {
            throw ((StellaException)(StellaException.newStellaException("INTERNAL ERROR: unexpected justification type in batch forward computation").fillInStackTrace()));
          }
          else if ((testValue000 == Logic.KWD_AND_INTRODUCTION) ||
              (testValue000 == Logic.KWD_OR_INTRODUCTION)) {
            { NeuralNetwork net = Justification.getJustificationNeuralNetwork(proof);
              Vector inputs = Vector.newVector(net.numberOfInputs());
              Vector vectorargs = (net.hasVectorArgumentsP() ? Vector.newVector(net.numberOfVectorArguments(null)) : ((Vector)(null)));
              int index = -1;

              { Justification ant = null;
                Cons iter000 = proof.antecedents;

                for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
                  ant = ((Justification)(iter000.value));
                  index = net.truthValueArgumentIndex(ant.proposition);
                  if (index >= 0) {
                    score = ant.matchScore;
                    (inputs.theArray)[index] = (FloatWrapper.wrapFloat(score));
                  }
                  if (vectorargs != null) {
                    index = net.vectorArgumentIndex(ant.proposition);
                    if (index >= 0) {
                      (vectorargs.theArray)[index] = (net.getVectorArgumentSpec(ant));
                    }
                  }
                }
              }
              queue.queueInputValues(net, proof, inputs, vectorargs);
            }
          }
          else if (testValue000 == Logic.KWD_MULTIPLE_PROOFS) {
            { Cons value000 = Stella.NIL;

              { Justification ant = null;
                Cons iter001 = proof.antecedents;
                Cons collect000 = null;

                for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
                  ant = ((Justification)(iter001.value));
                  if (collect000 == null) {
                    {
                      collect000 = Cons.cons(FloatWrapper.wrapFloat(ant.matchScore), Stella.NIL);
                      if (value000 == Stella.NIL) {
                        value000 = collect000;
                      }
                      else {
                        Cons.addConsToEndOfConsList(value000, collect000);
                      }
                    }
                  }
                  else {
                    {
                      collect000.rest = Cons.cons(FloatWrapper.wrapFloat(ant.matchScore), Stella.NIL);
                      collect000 = collect000.rest;
                    }
                  }
                }
              }
              score = Logic.combineMultipleMatchScores(value000);
            }
            proof.matchScore = score;
            { Justification dep = null;
              Cons iter002 = queue.getDependents(proof);

              for (;!(iter002 == Stella.NIL); iter002 = iter002.rest) {
                dep = ((Justification)(iter002.value));
                queue.notifyOfCompletion(dep, proof);
              }
            }
          }
          else if ((testValue000 == Logic.KWD_DISPROOF) ||
              (testValue000 == Logic.KWD_GOAL_COMPLEMENT)) {
            score = Logic.invertChameleonMatchScore(((Justification)(proof.antecedents.value)).matchScore);
            proof.matchScore = score;
            { Justification dep = null;
              Cons iter003 = queue.getDependents(proof);

              for (;!(iter003 == Stella.NIL); iter003 = iter003.rest) {
                dep = ((Justification)(iter003.value));
                queue.notifyOfCompletion(dep, proof);
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
      }
    }
  }

  /** Compute the same partial match score as the call to <code>computePartialTruth</code>
   * that generated <code>proof</code> (which is assumed to have been compacted with a call to
   * <code>compactPartialProofToNetworkProof</code>.  The score will only be identical of course, if
   * the various networks and their weights have not yet been updated during learning.
   * @param proof
   */
  public void batchProcessCachedNetworkProof(Justification proof) {
    { NetworkProofForwardQueue queue = this;

      { Keyword testValue000 = proof.inferenceRule;

        if (testValue000 == Logic.KWD_PRIMITIVE_STRATEGY) {
          { Justification dep = null;
            Cons iter000 = queue.getDependents(proof);

            for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
              dep = ((Justification)(iter000.value));
              queue.notifyOfCompletion(dep, proof);
            }
          }
        }
        else if ((testValue000 == Logic.KWD_AND_INTRODUCTION) ||
            (testValue000 == Logic.KWD_OR_INTRODUCTION)) {
          { NeuralNetwork net = Justification.getJustificationNeuralNetwork(proof);

            { Justification ant = null;
              Cons iter001 = proof.antecedents;

              for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
                ant = ((Justification)(iter001.value));
                if (!net.ignoredValueArgumentP(ant.proposition)) {
                  queue.addDependent(ant, proof);
                }
              }
            }
            { Justification ant = null;
              Cons iter002 = proof.antecedents;

              for (;!(iter002 == Stella.NIL); iter002 = iter002.rest) {
                ant = ((Justification)(iter002.value));
                if (!net.ignoredValueArgumentP(ant.proposition)) {
                  queue.batchProcessCachedNetworkProof(ant);
                }
              }
            }
          }
        }
        else if ((testValue000 == Logic.KWD_MULTIPLE_PROOFS) ||
            ((testValue000 == Logic.KWD_DISPROOF) ||
             (testValue000 == Logic.KWD_GOAL_COMPLEMENT))) {
          { Justification ant = null;
            Cons iter003 = proof.antecedents;

            for (;!(iter003 == Stella.NIL); iter003 = iter003.rest) {
              ant = ((Justification)(iter003.value));
              queue.addDependent(ant, proof);
            }
          }
          { Justification ant = null;
            Cons iter004 = proof.antecedents;

            for (;!(iter004 == Stella.NIL); iter004 = iter004.rest) {
              ant = ((Justification)(iter004.value));
              queue.batchProcessCachedNetworkProof(ant);
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
    }
  }

  public Surrogate primaryType() {
    { NetworkProofForwardQueue self = this;

      return (Logic.SGT_LOGIC_NETWORK_PROOF_FORWARD_QUEUE);
    }
  }

}

