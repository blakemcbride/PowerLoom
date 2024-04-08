//  -*- Mode: Java -*-
//
// PartialMatchFrame.java

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

/** Abstract class acting as placeholder for system and
 * user-defined partial match implementations.
 * @author Stella Java Translator
 */
public abstract class PartialMatchFrame extends StandardObject {
    public Keyword kind;
    public ControlFrame controlFrame;
    public PartialMatchFrame parent;
    public PartialMatchFrame child;
    public double matchScore;
    public double dynamicCutoff;
    public Cons argumentScores;
    public Cons argumentWeights;
    public Cons unboundVars;
    public boolean successP;

  public double computePartialTruth(QueryIterator query) {
    { PartialMatchFrame self = this;

      query = query;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("Don't know how to compute partial truth for `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public QueryIterator retrievePartialSolutions(QueryIterator query) {
    { PartialMatchFrame self = this;

      query = query;
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("Don't know how to retrieve partial solutions for `" + self + "'");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public void initializePartialMatchStrategy(QueryIterator query) {
    { PartialMatchFrame self = this;

      { FloatWrapper minimumscore = ((FloatWrapper)(query.options.lookup(Logic.KWD_MINIMUM_SCORE)));
        double epsilon = 0.001;

        query.partialMatchStrategy = self;
        self.dynamicCutoff = ((minimumscore != null) ? minimumscore.wrapperValue : epsilon);
        KeyValueList.setDynamicSlotValue(query.dynamicSlots, Logic.SYM_LOGIC_LATEST_POSITIVE_SCORE, FloatWrapper.wrapFloat(0.0), Stella.NULL_FLOAT_WRAPPER);
      }
    }
  }

  public boolean earlyPartialMatchOrSuccessP() {
    { PartialMatchFrame self = this;

      return (false);
    }
  }

  public boolean earlyPartialMatchAndFailureP() {
    { PartialMatchFrame self = this;

      return (false);
    }
  }

  public void popPartialMatchScore() {
    { PartialMatchFrame self = this;

    }
  }

  public void recordPartialMatchScore(double score, double weight) {
    { PartialMatchFrame self = this;

      {
        score = score;
        weight = weight;
      }
    }
  }

  public void setBasePartialMatchTruth(Proposition prop, Keyword truth) {
    { PartialMatchFrame self = this;

      prop = prop;
      if (truth == Logic.KWD_TRUE) {
        KeyValueList.setDynamicSlotValue(((QueryIterator)(Logic.$QUERYITERATOR$.get())).dynamicSlots, Logic.SYM_LOGIC_LATEST_POSITIVE_SCORE, FloatWrapper.wrapFloat(1.0), Stella.NULL_FLOAT_WRAPPER);
      }
      else if (truth == Logic.KWD_FAIL) {
        KeyValueList.setDynamicSlotValue(((QueryIterator)(Logic.$QUERYITERATOR$.get())).dynamicSlots, Logic.SYM_LOGIC_LATEST_POSITIVE_SCORE, FloatWrapper.wrapFloat(0.0), Stella.NULL_FLOAT_WRAPPER);
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("`" + truth + "' is not a valid case option");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  public Keyword continuePartialAntecedentsProof(Keyword lastmove) {
    { PartialMatchFrame self = this;

      return (ControlFrame.continueAntecedentsProof(self.controlFrame, lastmove));
    }
  }

  public Keyword continuePartialStrategiesProofs(Keyword lastmove) {
    { PartialMatchFrame self = this;

      return (ControlFrame.oldInterpretGoalScores(self.controlFrame, lastmove));
    }
  }

  public double computeGoalScore() {
    { PartialMatchFrame self = this;

      return (Stella.NULL_FLOAT);
    }
  }

  public Keyword continuePartialFailProof(Keyword lastmove) {
    { PartialMatchFrame self = this;

      lastmove = ControlFrame.oldInterpretFailScore(self.controlFrame, lastmove);
      return (ControlFrame.continueFailProof(self.controlFrame, lastmove));
    }
  }

  public Keyword continuePartialNotProof(Keyword lastmove) {
    { PartialMatchFrame self = this;

      return (ControlFrame.continueNotProof(self.controlFrame, lastmove));
    }
  }

  public double computeNotScore() {
    { PartialMatchFrame self = this;

      return (Stella.NULL_FLOAT);
    }
  }

  public Keyword continuePartialOrProof(Keyword lastmove) {
    { PartialMatchFrame self = this;

      lastmove = ControlFrame.oldInterpretOrScores(self.controlFrame, lastmove);
      return (ControlFrame.continueOrProof(self.controlFrame, lastmove));
    }
  }

  public double computeOrScore() {
    { PartialMatchFrame self = this;

      return (Stella.NULL_FLOAT);
    }
  }

  public Keyword continuePartialAndProof(ControlFrame frame, Keyword lastmove) {
    { PartialMatchFrame self = this;

      lastmove = ControlFrame.oldInterpretAndScores(frame, lastmove);
      return (ControlFrame.continueAndProof(frame, lastmove));
    }
  }

  public double computeAndScore() {
    { PartialMatchFrame self = this;

      return (Stella.NULL_FLOAT);
    }
  }

  public boolean allowUnboundVariablesP() {
    { PartialMatchFrame self = this;

      return (false);
    }
  }

  public void setJustificationPartialTruth(Justification justification) {
    { PartialMatchFrame self = this;

      justification.matchScore = self.matchScore;
    }
  }

  public void setCachePartialTruth(AtomicGoalCache cache) {
    { PartialMatchFrame self = this;

      cache.matchScore = self.matchScore;
    }
  }

  public void traceFramePartialTruth(Keyword lastmove, OutputStream stream) {
    { PartialMatchFrame self = this;

      { double weight = self.propositionWeight(self.controlFrame.proposition);

        if (lastmove == Logic.KWD_DOWN) {
          { double cutoff = self.computeDynamicCutoff();

            if (cutoff != Stella.NULL_FLOAT) {
              stream.nativeStream.print("cutoff=" + cutoff);
            }
          }
        }
        else if ((lastmove == Logic.KWD_UP_TRUE) ||
            (lastmove == Logic.KWD_UP_FAIL)) {
          { double score = self.matchScore;

            stream.nativeStream.print("score=" + score);
            if ((weight != Stella.NULL_FLOAT) &&
                (!(weight == 1.0))) {
              stream.nativeStream.print(" weight=" + weight);
            }
          }
        }
        else {
        }
      }
    }
  }

  public void propagateFramePartialTruth(ControlFrame target) {
    { PartialMatchFrame source = this;

      { PartialMatchFrame targetpmf = target.partialMatchFrame;
        boolean flippolarityP = !(source.controlFrame.reversePolarityP == target.reversePolarityP);

        if (targetpmf == null) {
          if (flippolarityP) {
            targetpmf = ((PartialMatchFrame)(Surrogate.createObject(source.primaryType(), Cons.cons(Logic.KWD_CONTROL_FRAME, Cons.cons(target, Cons.cons(Logic.KWD_KIND, Cons.cons(target.state, Stella.NIL)))))));
            targetpmf.parent = source.parent;
            targetpmf.child = source;
          }
          else {
            targetpmf = source;
          }
          target.partialMatchFrame = targetpmf;
        }
        targetpmf.matchScore = source.matchScore;
        if (flippolarityP &&
            ((!TruthValue.unknownTruthValueP(source.controlFrame.truthValue)) ||
             (!(source.matchScore == source.truthValueScore(Logic.UNKNOWN_TRUTH_VALUE))))) {
          targetpmf.matchScore = source.invertMatchScore(source.matchScore);
        }
        KeyValueList.setDynamicSlotValue(((QueryIterator)(Logic.$QUERYITERATOR$.get())).dynamicSlots, Logic.SYM_LOGIC_LATEST_POSITIVE_SCORE, FloatWrapper.wrapFloat(targetpmf.matchScore), Stella.NULL_FLOAT_WRAPPER);
      }
    }
  }

  public void setFramePartialTruth(TruthValue truthvalue, double score, boolean ignorepolarityP) {
    { PartialMatchFrame self = this;

      { boolean flippolarityP = self.controlFrame.reversePolarityP &&
            (!ignorepolarityP);

        if ((score == Stella.NULL_FLOAT) &&
            (truthvalue != null)) {
          score = self.truthValueScore(truthvalue);
        }
        if (flippolarityP) {
          score = self.invertMatchScore(score);
        }
        self.matchScore = score;
        KeyValueList.setDynamicSlotValue(((QueryIterator)(Logic.$QUERYITERATOR$.get())).dynamicSlots, Logic.SYM_LOGIC_LATEST_POSITIVE_SCORE, FloatWrapper.wrapFloat(score), Stella.NULL_FLOAT_WRAPPER);
      }
    }
  }

  public boolean definedFramePartialTruthP() {
    { PartialMatchFrame self = this;

      return (self.matchScore != Stella.NULL_FLOAT);
    }
  }

  public void clearFramePartialTruth() {
    { PartialMatchFrame self = this;

      self.matchScore = Stella.NULL_FLOAT;
    }
  }

  public double computeAssertionScore(Proposition proposition, TruthValue truthvalue) {
    { PartialMatchFrame self = this;

      if (truthvalue == null) {
        truthvalue = ((TruthValue)(Stella_Object.accessInContext(proposition.truthValue, proposition.homeContext, false)));
      }
      if (!(truthvalue != null)) {
        System.err.print("Safety violation: INTERNAL ERROR: missing truth value for assertion");
      }
      { FloatWrapper score = ((FloatWrapper)(Stella_Object.accessInContext(KeyValueList.dynamicSlotValue(proposition.dynamicSlots, Logic.SYM_LOGIC_SCORE, null), proposition.homeContext, false)));
        double weight = self.propositionWeight(proposition);

        if (score == null) {
          score = FloatWrapper.wrapFloat(self.truthValueScore(truthvalue));
        }
        else if ((truthvalue == Logic.FALSE_TRUTH_VALUE) ||
            (truthvalue == Logic.DEFAULT_FALSE_TRUTH_VALUE)) {
          score = FloatWrapper.wrapFloat(self.invertMatchScore(score.wrapperValue));
        }
        return (score.wrapperValue * weight);
      }
    }
  }

  public double propositionWeight(Proposition proposition) {
    { PartialMatchFrame self = this;

      if (proposition != null) {
        { double weight = ((FloatWrapper)(KeyValueList.dynamicSlotValue(proposition.dynamicSlots, Logic.SYM_LOGIC_WEIGHT, Stella.NULL_FLOAT_WRAPPER))).wrapperValue;

          if (weight == Stella.NULL_FLOAT) {
            return (1.0);
          }
          else {
            return (weight);
          }
        }
      }
      else {
        return (1.0);
      }
    }
  }

  public double invertMatchScore(double score) {
    { PartialMatchFrame self = this;

      return (1.0 - score);
    }
  }

  public double truthValueScore(TruthValue truthvalue) {
    { PartialMatchFrame self = this;

      return (((truthvalue == Logic.TRUE_TRUTH_VALUE) ? 1.0 : 0.0));
    }
  }

  public boolean cutoffPartialMatchP(boolean traceP) {
    { PartialMatchFrame self = this;

      { double score = self.matchScore;
        double cutoff = self.dynamicCutoff;
        boolean cutoffP = false;

        if ((score == Stella.NULL_FLOAT) ||
            ((cutoff == Stella.NULL_FLOAT) ||
             (cutoff == 0.0))) {
          cutoffP = false;
        }
        else if (cutoff < 0.0) {
          cutoffP = score > cutoff;
        }
        else {
          cutoffP = score < cutoff;
        }
        if (cutoffP &&
            traceP) {
          Stella.STANDARD_OUTPUT.nativeStream.println("*** Cutting off search, cutoff=" + cutoff);
        }
        return (cutoffP);
      }
    }
  }

  public void setDynamicCutoff() {
    { PartialMatchFrame self = this;

      { double cutoff = self.computeDynamicCutoff();

        if (cutoff != Stella.NULL_FLOAT) {
          if ((cutoff < -100) ||
              (cutoff > 100)) {
            Stella.STANDARD_WARNING.nativeStream.println("Warning: *** fishy dynamic cutoff=`" + cutoff + "' computed, resetting to 0.0");
            cutoff = 0.0;
          }
          self.dynamicCutoff = cutoff;
        }
      }
    }
  }

  public double computeDynamicCutoff() {
    { PartialMatchFrame self = this;

      return (Stella.NULL_FLOAT);
    }
  }

  public PartialMatchFrame createPartialMatchFrame(ControlFrame frame, Keyword kind) {
    { PartialMatchFrame self = this;

      {
        frame = frame;
        kind = kind;
      }
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        {
          stream000.nativeStream.println("Missing concrete method named 'create-partial-match-frame' on the");
          stream000.nativeStream.print("   class `" + self.primaryType() + "'");
        }
;
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
  }

  public static void linkToParentPartialMatchFrame(PartialMatchFrame self) {
    { ControlFrame controlframe = self.controlFrame.up;

      while ((controlframe != null) &&
          (controlframe.partialMatchFrame == null)) {
        controlframe = controlframe.up;
      }
      if (controlframe != null) {
        self.parent = controlframe.partialMatchFrame;
        controlframe.partialMatchFrame.child = self;
      }
    }
  }

  public static Stella_Object accessPartialMatchFrameSlotValue(PartialMatchFrame self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Logic.SYM_LOGIC_KIND) {
      if (setvalueP) {
        self.kind = ((Keyword)(value));
      }
      else {
        value = self.kind;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_CONTROL_FRAME) {
      if (setvalueP) {
        self.controlFrame = ((ControlFrame)(value));
      }
      else {
        value = self.controlFrame;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_PARENT) {
      if (setvalueP) {
        self.parent = ((PartialMatchFrame)(value));
      }
      else {
        value = self.parent;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_CHILD) {
      if (setvalueP) {
        self.child = ((PartialMatchFrame)(value));
      }
      else {
        value = self.child;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_MATCH_SCORE) {
      if (setvalueP) {
        self.matchScore = ((FloatWrapper)(value)).wrapperValue;
      }
      else {
        value = FloatWrapper.wrapFloat(self.matchScore);
      }
    }
    else if (slotname == Logic.SYM_LOGIC_POSITIVE_SCORE) {
      if (setvalueP) {
        self.matchScore = ((FloatWrapper)(value)).wrapperValue;
      }
      else {
        value = FloatWrapper.wrapFloat(self.matchScore);
      }
    }
    else if (slotname == Logic.SYM_LOGIC_DYNAMIC_CUTOFF) {
      if (setvalueP) {
        self.dynamicCutoff = ((FloatWrapper)(value)).wrapperValue;
      }
      else {
        value = FloatWrapper.wrapFloat(self.dynamicCutoff);
      }
    }
    else if (slotname == Logic.SYM_LOGIC_ARGUMENT_SCORES) {
      if (setvalueP) {
        self.argumentScores = ((Cons)(value));
      }
      else {
        value = self.argumentScores;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_ARGUMENT_WEIGHTS) {
      if (setvalueP) {
        self.argumentWeights = ((Cons)(value));
      }
      else {
        value = self.argumentWeights;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_UNBOUND_VARS) {
      if (setvalueP) {
        self.unboundVars = ((Cons)(value));
      }
      else {
        value = self.unboundVars;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_SUCCESSp) {
      if (setvalueP) {
        self.successP = BooleanWrapper.coerceWrappedBooleanToBoolean(((BooleanWrapper)(value)));
      }
      else {
        value = (self.successP ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER);
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

}

