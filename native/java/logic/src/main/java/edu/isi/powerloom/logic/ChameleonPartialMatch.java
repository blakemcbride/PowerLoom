//  -*- Mode: Java -*-
//
// ChameleonPartialMatch.java

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

/** Variant of :BASIC partial match strategy to support CHAMELEON queries.
 * @author Stella Java Translator
 */
public class ChameleonPartialMatch extends IncrementalPartialMatch {
    /** Holds justifications for OR arguments and alternative rules.
     */
    public Cons argumentJustifications;
    /** Holds argument propositions in the order they are associated with scores
     */
    public Cons argumentPropositions;

  public static ChameleonPartialMatch newChameleonPartialMatch(Keyword kind, ControlFrame controlFrame) {
    { ChameleonPartialMatch self = null;

      self = new ChameleonPartialMatch();
      self.kind = kind;
      self.controlFrame = controlFrame;
      self.successP = false;
      self.unboundVars = Stella.NIL;
      self.argumentWeights = Stella.NIL;
      self.argumentScores = Stella.NIL;
      self.dynamicCutoff = Stella.NULL_FLOAT;
      self.matchScore = Stella.NULL_FLOAT;
      self.maximumScore = 0.0;
      self.totalWeight = Stella.NULL_FLOAT;
      self.accumulatedWeight = 0.0;
      self.accumulatedScore = 0.0;
      self.child = null;
      self.parent = null;
      self.argumentPropositions = Stella.NIL;
      self.argumentJustifications = Stella.NIL;
      IncrementalPartialMatch.initializeIncrementalPartialMatch(self);
      return (self);
    }
  }

  public double computePartialTruth(QueryIterator query) {
    { ChameleonPartialMatch self = this;

      { ControlFrame baseframe = query.baseControlFrame;
        PartialMatchFrame partialmatchframe = query.partialMatchStrategy;
        FloatWrapper minimumscore = ((FloatWrapper)(query.options.lookup(Logic.KWD_MINIMUM_SCORE)));
        boolean maximizescoreP = !Stella_Object.eqlP(query.options.lookup(Logic.KWD_MAXIMIZE_SCOREp), Stella.FALSE_WRAPPER);
        Stella_Object recordjustificationsP = Logic.lookupDeferredQueryOption(query, Logic.KWD_RECORD_JUSTIFICATIONSp, Logic.SGT_STELLA_BOOLEAN);
        double epsilon = 0.001;
        NormalInferenceLevel initialinferencelevel = Logic.currentInferenceLevel();
        double latestscore = 0.0;
        double bestscore = 0.0;
        Justification bestproof = null;

        if (partialmatchframe == null) {
          partialmatchframe = self;
          query.partialMatchStrategy = self;
        }
        partialmatchframe.dynamicCutoff = ((minimumscore != null) ? minimumscore.wrapperValue : epsilon);
        { Object old$Queryiterator$000 = Logic.$QUERYITERATOR$.get();
          Object old$GenerateAllProofsP$000 = Logic.$GENERATE_ALL_PROOFSp$.get();
          Object old$RecordJustificationsP$000 = Logic.$RECORD_JUSTIFICATIONSp$.get();
          Object old$Inferencelevel$000 = Logic.$INFERENCELEVEL$.get();
          Object old$ReversepolarityP$000 = Logic.$REVERSEPOLARITYp$.get();

          try {
            Native.setSpecial(Logic.$QUERYITERATOR$, query);
            Native.setBooleanSpecial(Logic.$GENERATE_ALL_PROOFSp$, true);
            Native.setBooleanSpecial(Logic.$RECORD_JUSTIFICATIONSp$, ((Boolean)(Logic.$RECORD_JUSTIFICATIONSp$.get())).booleanValue());
            Native.setSpecial(Logic.$INFERENCELEVEL$, initialinferencelevel);
            Native.setBooleanSpecial(Logic.$REVERSEPOLARITYp$, false);
            if (Stella_Object.eqlP(recordjustificationsP, Stella.TRUE_WRAPPER)) {
              Native.setBooleanSpecial(Logic.$RECORD_JUSTIFICATIONSp$, true);
            }
            Logic.$RULE_COMBINATION$ = Logic.KWD_NOISY_OR;
            loop000 : for (;;) {
              if (!(query.nextP())) {
                if (query.solutions.length() == 0) {
                  bestscore = partialmatchframe.matchScore;
                }
                break loop000;
              }
              if (partialmatchframe.cutoffPartialMatchP(false)) {
                break loop000;
              }
              latestscore = partialmatchframe.matchScore;
              if (latestscore > bestscore) {
                bestscore = latestscore;
                bestproof = ((Justification)(KeyValueList.dynamicSlotValue(baseframe.dynamicSlots, Logic.SYM_LOGIC_JUSTIFICATION, null)));
                partialmatchframe.dynamicCutoff = bestscore + epsilon;
              }
              if (!maximizescoreP) {
                break loop000;
              }
              Native.setSpecial(Logic.$INFERENCELEVEL$, initialinferencelevel);
            }
            KeyValueList.setDynamicSlotValue(baseframe.dynamicSlots, Logic.SYM_LOGIC_JUSTIFICATION, bestproof, null);
            partialmatchframe.matchScore = bestscore;
            return (bestscore);

          } finally {
            Logic.$REVERSEPOLARITYp$.set(old$ReversepolarityP$000);
            Logic.$INFERENCELEVEL$.set(old$Inferencelevel$000);
            Logic.$RECORD_JUSTIFICATIONSp$.set(old$RecordJustificationsP$000);
            Logic.$GENERATE_ALL_PROOFSp$.set(old$GenerateAllProofsP$000);
            Logic.$QUERYITERATOR$.set(old$Queryiterator$000);
          }
        }
      }
    }
  }

  public Keyword continuePartialAntecedentsProof(Keyword lastmove) {
    { ChameleonPartialMatch self = this;

      { ControlFrame frame = self.controlFrame;
        Proposition goal = ControlFrame.extractSubgoalOfFrame(frame);
        double score = Stella.NULL_FLOAT;
        Keyword result = null;

        if (lastmove == Logic.KWD_DOWN) {
          self.setDynamicCutoff();
        }
        else if ((lastmove == Logic.KWD_UP_TRUE) ||
            (lastmove == Logic.KWD_UP_FAIL)) {
          { ControlFrame goalframe = frame.result;

            score = goalframe.partialMatchFrame.matchScore;
            self.pushOrPartialMatchScore(score, self.propositionWeight(((Proposition)(KeyValueList.dynamicSlotValue(frame.dynamicSlots, Logic.SYM_LOGIC_ANTECEDENTS_RULE, null)))));
            score = self.computeGoalScore();
            self.setFramePartialTruth(null, score, false);
            if (((Boolean)(Logic.$RECORD_JUSTIFICATIONSp$.get())).booleanValue() &&
                (((Justification)(KeyValueList.dynamicSlotValue(goalframe.dynamicSlots, Logic.SYM_LOGIC_JUSTIFICATION, null))) != null)) {
              ControlFrame.recordModusPonensJustification(frame, Logic.KWD_UP_TRUE);
              self.argumentJustifications = Cons.cons(((Justification)(KeyValueList.dynamicSlotValue(frame.dynamicSlots, Logic.SYM_LOGIC_JUSTIFICATION, null))), self.argumentJustifications);
            }
            if ((!Proposition.allArgumentsBoundP(goal)) ||
                self.cutoffPartialMatchP(Stella_Object.traceKeywordP(Logic.KWD_GOAL_TREE))) {
              self.popOrPartialMatchScore();
              if (((Boolean)(Logic.$RECORD_JUSTIFICATIONSp$.get())).booleanValue()) {
                self.argumentJustifications = self.argumentJustifications.rest;
              }
              self.setFramePartialTruth(Logic.UNKNOWN_TRUTH_VALUE, 0.0, true);
              lastmove = Logic.KWD_UP_FAIL;
            }
            else if ((!ControlFrame.hasMoreAntecedentsP(frame)) &&
                (Proposition.allArgumentsBoundP(goal) &&
                 (self.argumentJustifications.length() > 0))) {
              lastmove = Logic.KWD_UP_TRUE;
            }
            else {
              lastmove = Logic.KWD_UP_FAIL;
            }
          }
        }
        else {
          { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

            stream000.nativeStream.print("`" + lastmove + "' is not a valid case option");
            throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
          }
        }
        frame.down = null;
        result = ControlFrame.continueAntecedentsProof(frame, lastmove);
        if (lastmove == Logic.KWD_UP_TRUE) {
          if (frame.truthValue == null) {
            frame.truthValue = Logic.UNKNOWN_TRUTH_VALUE;
          }
          switch (self.argumentJustifications.length()) {
            case 0: 
            break;
            case 1: 
              KeyValueList.setDynamicSlotValue(frame.dynamicSlots, Logic.SYM_LOGIC_JUSTIFICATION, ((Justification)(self.argumentJustifications.value)), null);
            break;
            default:
              { Justification self003 = Justification.newJustification();

                self003.inferenceRule = Logic.KWD_MULTIPLE_PROOFS;
                self003.antecedents = self.argumentJustifications.reverse();
                ControlFrame.recordGoalJustification(frame, self003);
              }
            break;
          }
        }
        return (result);
      }
    }
  }

  public Keyword continuePartialStrategiesProofs(Keyword lastmove) {
    { ChameleonPartialMatch self = this;

      { ControlFrame frame = self.controlFrame;
        Keyword result = super.continuePartialStrategiesProofs(lastmove);

        if ((result == Logic.KWD_FAILURE) &&
            ((!((frame.truthValue == Logic.UNKNOWN_TRUTH_VALUE) ||
            (frame.truthValue == null))) &&
             (!(frame.reversePolarityP == ((frame.truthValue == Logic.FALSE_TRUTH_VALUE) ||
             (frame.truthValue == Logic.DEFAULT_FALSE_TRUTH_VALUE)))))) {
          if (Logic.KWD_OTHER == Logic.KWD_VARIANT1) {
            ControlFrame.setFrameTruthValue(frame, Logic.UNKNOWN_TRUTH_VALUE);
            if (!((self.matchScore == 0.0) ||
                (self.matchScore == 1.0))) {
              result = Logic.KWD_FINAL_SUCCESS;
            }
            if (((Boolean)(Logic.$RECORD_JUSTIFICATIONSp$.get())).booleanValue() &&
                ((result == Logic.KWD_FINAL_SUCCESS) &&
                 (((Justification)(KeyValueList.dynamicSlotValue(frame.dynamicSlots, Logic.SYM_LOGIC_JUSTIFICATION, null))) == null))) {
              ControlFrame.recordPrimitiveJustification(frame, Logic.KWD_UP_TRUE);
            }
          }
          else if (Logic.KWD_OTHER == Logic.KWD_VARIANT2) {
            ControlFrame.setFrameTruthValue(frame, Logic.UNKNOWN_TRUTH_VALUE);
            self.setFramePartialTruth(Logic.UNKNOWN_TRUTH_VALUE, Stella.NULL_FLOAT, true);
          }
          else {
          }
        }
        return (result);
      }
    }
  }

  public double computeGoalScore() {
    { ChameleonPartialMatch self = this;

      return (super.computeGoalScore());
    }
  }

  public Keyword continuePartialFailProof(Keyword lastmove) {
    { ChameleonPartialMatch self = this;

      return (super.continuePartialFailProof(lastmove));
    }
  }

  public Keyword continuePartialNotProof(Keyword lastmove) {
    { ChameleonPartialMatch self = this;

      return (super.continuePartialNotProof(lastmove));
    }
  }

  public double computeNotScore() {
    { ChameleonPartialMatch self = this;

      return (0.0);
    }
  }

  public Keyword continuePartialOrProof(Keyword lastmove) {
    { ChameleonPartialMatch self = this;

      { ControlFrame frame = self.controlFrame;
        Proposition orproposition = frame.proposition;
        int argcursor = frame.argumentCursor;
        Keyword result = null;

        if (lastmove == Logic.KWD_DOWN) {
          { int i = Stella.NULL_INTEGER;
            int iter000 = argcursor;
            int upperBound000 = self.argumentScores.length() - 1;

            for (;iter000 <= upperBound000; iter000 = iter000 + 1) {
              i = iter000;
              i = i;
              self.popOrPartialMatchScore();
              if (((Boolean)(Logic.$RECORD_JUSTIFICATIONSp$.get())).booleanValue()) {
                self.argumentJustifications = self.argumentJustifications.rest;
              }
            }
          }
          self.setDynamicCutoff();
        }
        else if ((lastmove == Logic.KWD_UP_TRUE) ||
            (lastmove == Logic.KWD_UP_FAIL)) {
          { boolean sucessP = lastmove == Logic.KWD_UP_TRUE;
            ControlFrame result000 = frame.result;
            Vector disjuncts = orproposition.arguments;
            Proposition disjunct = ((Proposition)((disjuncts.theArray)[argcursor]));
            double score = result000.partialMatchFrame.matchScore;

            self.pushOrPartialMatchScore(score, self.propositionWeight(disjunct));
            score = self.computeOrScore();
            self.setFramePartialTruth(null, score, false);
            if (((Boolean)(Logic.$RECORD_JUSTIFICATIONSp$.get())).booleanValue()) {
              self.argumentJustifications = Cons.cons(((Justification)(KeyValueList.dynamicSlotValue(result000.dynamicSlots, Logic.SYM_LOGIC_JUSTIFICATION, null))), self.argumentJustifications);
            }
            if ((!Proposition.allArgumentsBoundP(disjunct)) ||
                self.cutoffPartialMatchP(Stella_Object.traceKeywordP(Logic.KWD_GOAL_TREE))) {
              self.popOrPartialMatchScore();
              if (((Boolean)(Logic.$RECORD_JUSTIFICATIONSp$.get())).booleanValue()) {
                self.argumentJustifications = self.argumentJustifications.rest;
              }
              self.setFramePartialTruth(Logic.UNKNOWN_TRUTH_VALUE, 0.0, true);
              lastmove = Logic.KWD_UP_FAIL;
            }
            else if (sucessP &&
                ((argcursor == (disjuncts.length() - 1)) &&
                 Proposition.allArgumentsBoundP(disjunct))) {
              lastmove = Logic.KWD_UP_TRUE;
            }
            else {
              lastmove = Logic.KWD_UP_FAIL;
            }
          }
        }
        else {
          { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

            stream000.nativeStream.print("`" + lastmove + "' is not a valid case option");
            throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
          }
        }
        frame.down = null;
        result = ControlFrame.continueOrProof(frame, lastmove);
        if (self.argumentJustifications.length() >= 2) {
          { Justification self003 = Justification.newJustification();

            self003.inferenceRule = Logic.KWD_OR_INTRODUCTION;
            self003.antecedents = self.argumentJustifications.reverse();
            ControlFrame.recordGoalJustification(frame, self003);
          }
        }
        return (result);
      }
    }
  }

  public double computeOrScore() {
    { ChameleonPartialMatch self = this;

      return (self.computeAndScore());
    }
  }

  public Keyword continuePartialAndProof(ControlFrame frame, Keyword lastmove) {
    { ChameleonPartialMatch self = this;

      if ((lastmove == Logic.KWD_UP_TRUE) ||
          (lastmove == Logic.KWD_UP_FAIL)) {
        if (TruthValue.falseTruthValueP(frame.result.truthValue) &&
            TruthValue.strictTruthValueP(frame.result.truthValue)) {
          frame.result.truthValue = Logic.UNKNOWN_TRUTH_VALUE;
        }
      }
      else {
      }
      return (super.continuePartialAndProof(frame, lastmove));
    }
  }

  public double computeAndScore() {
    { ChameleonPartialMatch self = this;

      { NeuralNetwork net = Proposition.getPropositionNeuralNetwork(self.controlFrame.proposition, true);
        Vector inputs = Vector.newVector(net.numberOfInputs());
        Vector vectorargs = (net.hasVectorArgumentsP() ? Vector.newVector(net.numberOfVectorArguments(null)) : ((Vector)(null)));
        int index = -1;

        { Proposition arg = null;
          Cons iter000 = self.argumentPropositions;
          FloatWrapper score = null;
          Cons iter001 = self.argumentScores;

          for (;(!(iter000 == Stella.NIL)) &&
                    (!(iter001 == Stella.NIL)); iter000 = iter000.rest, iter001 = iter001.rest) {
            arg = ((Proposition)(iter000.value));
            score = ((FloatWrapper)(iter001.value));
            index = net.truthValueArgumentIndex(arg);
            if (index >= 0) {
              (inputs.theArray)[index] = score;
            }
            if (vectorargs != null) {
              index = net.vectorArgumentIndex(arg);
              if (index >= 0) {
                (vectorargs.theArray)[index] = (net.getVectorArgumentSpec(arg));
              }
            }
          }
        }
        net.setInputValues(inputs);
        if (vectorargs != null) {
          net.setVectorInputValues(vectorargs);
        }
        return (net.forwardPropagateInputs());
      }
    }
  }

  public boolean allowUnboundVariablesP() {
    { ChameleonPartialMatch self = this;

      return (false);
    }
  }

  public void popOrPartialMatchScore() {
    { ChameleonPartialMatch self = this;

      super.popOrPartialMatchScore();
    }
  }

  public void pushOrPartialMatchScore(double score, double weight) {
    { ChameleonPartialMatch self = this;

      super.pushOrPartialMatchScore(score, weight);
    }
  }

  public void popAndPartialMatchScore() {
    { ChameleonPartialMatch self = this;

      super.popAndPartialMatchScore();
      self.argumentPropositions = self.argumentPropositions.rest;
    }
  }

  public void pushAndPartialMatchScore(double score, double weight) {
    { ChameleonPartialMatch self = this;

      { Proposition argprop = self.controlFrame.result.proposition;

        super.pushAndPartialMatchScore(score, weight);
        self.argumentPropositions = Cons.cons(argprop, self.argumentPropositions);
      }
    }
  }

  public double propositionWeight(Proposition proposition) {
    { ChameleonPartialMatch self = this;

      return (super.propositionWeight(proposition));
    }
  }

  public double invertMatchScore(double score) {
    { ChameleonPartialMatch self = this;

      return (Logic.invertChameleonMatchScore(score));
    }
  }

  public double truthValueScore(TruthValue truthvalue) {
    { ChameleonPartialMatch self = this;

      { double score = truthvalue.matchScore;

        if (score < 0.0) {
          score = score + 1.0;
        }
        return (score);
      }
    }
  }

  public boolean cutoffPartialMatchP(boolean traceP) {
    { ChameleonPartialMatch self = this;

      return (super.cutoffPartialMatchP(traceP));
    }
  }

  public double computeDynamicCutoff() {
    { ChameleonPartialMatch self = this;

      if (((IncrementalPartialMatch)(self.parent)) != null) {
        { Keyword testValue000 = self.kind;

          if (testValue000 == Logic.KWD_ATOMIC_GOAL) {
            return (((IncrementalPartialMatch)(self.parent)).dynamicCutoff);
          }
          else if ((testValue000 == Logic.KWD_AND) ||
              (testValue000 == Logic.KWD_OR)) {
          }
          else {
          }
        }
      }
      return (0.0);
    }
  }

  public PartialMatchFrame createPartialMatchFrame(ControlFrame frame, Keyword kind) {
    { ChameleonPartialMatch self = this;

      { ChameleonPartialMatch pmf = ChameleonPartialMatch.newChameleonPartialMatch(kind, frame);
        Proposition prop = frame.proposition;

        if ((kind == Logic.KWD_AND) ||
            (kind == Logic.KWD_OR)) {
          if (Proposition.getPropositionNeuralNetwork(prop, false) == null) {
            Proposition.createAndLinkNeuralNetwork(prop);
          }
        }
        else {
        }
        PartialMatchFrame.linkToParentPartialMatchFrame(pmf);
        return (pmf);
      }
    }
  }

  public static Stella_Object accessChameleonPartialMatchSlotValue(ChameleonPartialMatch self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Logic.SYM_LOGIC_ARGUMENT_JUSTIFICATIONS) {
      if (setvalueP) {
        self.argumentJustifications = ((Cons)(value));
      }
      else {
        value = self.argumentJustifications;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_ARGUMENT_PROPOSITIONS) {
      if (setvalueP) {
        self.argumentPropositions = ((Cons)(value));
      }
      else {
        value = self.argumentPropositions;
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
    { ChameleonPartialMatch self = this;

      return (Logic.SGT_LOGIC_CHAMELEON_PARTIAL_MATCH);
    }
  }

}

