//  -*- Mode: Java -*-
//
// NetworkProofQueue.java

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

public class NetworkProofQueue extends StandardObject {
    /** Map from computation prerequisites to their dependents.
     */
    public KeyValueMap dependents;
    /** Map from dependents to their computation prerequisites.
     */
    public KeyValueMap prerequisites;
    public HashSet activeNetworks;
    public int minBatchSize;
    public int nQueued;

  public static NetworkProofQueue newNetworkProofQueue() {
    { NetworkProofQueue self = null;

      self = new NetworkProofQueue();
      self.nQueued = 0;
      self.minBatchSize = Native.floor(Logic.$NEURAL_NETWORK_BATCH_SIZE$ * 0.8);
      self.activeNetworks = HashSet.newHashSet();
      self.prerequisites = KeyValueMap.newKeyValueMap();
      self.dependents = KeyValueMap.newKeyValueMap();
      return (self);
    }
  }

  /** Execute queued ops in <code>queue</code> until there is nothing more to do.
   */
  public void executeAll() {
    { NetworkProofQueue queue = this;

      { int lowwatermark = queue.activeNetworks.length() * queue.minBatchSize;

        while (queue.nQueued > 0) {
          { NeuralNetwork net = null;
            DictionaryIterator iter000 = ((DictionaryIterator)(queue.activeNetworks.allocateIterator()));

            while (iter000.nextP()) {
              net = ((NeuralNetwork)(iter000.value));
              queue.executeNetworkOperation(net, queue.nQueued <= lowwatermark);
            }
          }
        }
      }
    }
  }

  /** Queue <code>inputs</code> in <code>net</code>s input batch.  Execute the current batch if we are full.
   * @param net
   * @param proof
   * @param inputs
   * @param vectorspecs
   */
  public void queueInputValues(NeuralNetwork net, Justification proof, Stella_Object inputs, Stella_Object vectorspecs) {
    { NetworkProofQueue queue = this;

      queue.activeNetworks.insert(net);
      while (net.batchIsFullP()) {
        queue.executeNetworkOperation(net, true);
      }
      net.pushInputValues(proof, inputs);
      if (vectorspecs != null) {
        net.pushVectorInputValues(vectorspecs);
      }
      queue.nQueued = queue.nQueued + 1;
    }
  }

  /** Notify <code>proof</code> that one of its <code>prerequisite</code>s had its computation completed.
   * @param proof
   * @param prerequisite
   */
  public void notifyOfCompletion(Justification proof, Justification prerequisite) {
    { NetworkProofQueue queue = this;

      queue.removeDependent(prerequisite, proof);
      if (queue.getPrerequisites(proof) == Stella.NIL) {
        queue.queueNetworkOperation(proof);
      }
    }
  }

  public void executeNetworkOperation(NeuralNetwork net, boolean forceP) {
    { NetworkProofQueue queue = this;

      {
        net = net;
        forceP = forceP;
      }
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("execute-network-operation: not implemented on: `" + queue + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public void queueNetworkOperation(Justification proof) {
    { NetworkProofQueue queue = this;

      proof = proof;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("queue-network-operation: not implemented on: `" + queue + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public void batchProcessCachedNetworkProof(Justification proof) {
    { NetworkProofQueue queue = this;

      proof = proof;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("batch-process-cached-network-proof: not implemented on: `" + queue + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public boolean hasPrerequisiteP(Justification dependent, Justification prerequisite) {
    { NetworkProofQueue queue = this;

      return (queue.getPrerequisites(dependent).membP(prerequisite));
    }
  }

  public Cons getPrerequisites(Justification dependent) {
    { NetworkProofQueue queue = this;

      { Cons temp000 = ((Cons)(queue.prerequisites.lookup(dependent)));

        { Cons value000 = ((temp000 != null) ? temp000 : Stella.NIL);

          return (((Cons)(value000)));
        }
      }
    }
  }

  public boolean hasDependentP(Justification prerequisite, Justification dependent) {
    { NetworkProofQueue queue = this;

      return (queue.getDependents(prerequisite).membP(dependent));
    }
  }

  public Cons getDependents(Justification prerequisite) {
    { NetworkProofQueue queue = this;

      { Cons temp000 = ((Cons)(queue.dependents.lookup(prerequisite)));

        { Cons value000 = ((temp000 != null) ? temp000 : Stella.NIL);

          return (((Cons)(value000)));
        }
      }
    }
  }

  public void removeDependent(Justification prerequisite, Justification dependent) {
    { NetworkProofQueue queue = this;

      Logic.removeNetworkProofDependencyLink(queue.dependents, prerequisite, dependent);
      Logic.removeNetworkProofDependencyLink(queue.prerequisites, dependent, prerequisite);
    }
  }

  public void addDependent(Justification prerequisite, Justification dependent) {
    { NetworkProofQueue queue = this;

      Logic.addNetworkProofDependencyLink(queue.dependents, prerequisite, dependent);
      Logic.addNetworkProofDependencyLink(queue.prerequisites, dependent, prerequisite);
    }
  }

  public static Stella_Object accessNetworkProofQueueSlotValue(NetworkProofQueue self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Logic.SYM_LOGIC_DEPENDENTS) {
      if (setvalueP) {
        self.dependents = ((KeyValueMap)(value));
      }
      else {
        value = self.dependents;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_PREREQUISITES) {
      if (setvalueP) {
        self.prerequisites = ((KeyValueMap)(value));
      }
      else {
        value = self.prerequisites;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_ACTIVE_NETWORKS) {
      if (setvalueP) {
        self.activeNetworks = ((HashSet)(value));
      }
      else {
        value = self.activeNetworks;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_MIN_BATCH_SIZE) {
      if (setvalueP) {
        self.minBatchSize = ((IntegerWrapper)(value)).wrapperValue;
      }
      else {
        value = IntegerWrapper.wrapInteger(self.minBatchSize);
      }
    }
    else if (slotname == Logic.SYM_LOGIC_N_QUEUED) {
      if (setvalueP) {
        self.nQueued = ((IntegerWrapper)(value)).wrapperValue;
      }
      else {
        value = IntegerWrapper.wrapInteger(self.nQueued);
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
    { NetworkProofQueue self = this;

      return (Logic.SGT_LOGIC_NETWORK_PROOF_QUEUE);
    }
  }

}

