//  -*- Mode: Java -*-
//
// AssertedCollectionMembersIterator.java

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

/** Iterator reimplementation of <code>assertedCollectionMembers</code>.
 * Generates asserted members of a collection as well as the supporting propositions
 * with their truth values and justifications (if applicable).
 * @author Stella Java Translator
 */
public class AssertedCollectionMembersIterator extends Iterator {
    public Stella_Object collection;
    public boolean specializeP;
    public Keyword kind;
    public Iterator baseIterator;
    public Iterator nestedBaseIterator;
    public Proposition proposition;
    public int observedCardinality;

  public static AssertedCollectionMembersIterator newAssertedCollectionMembersIterator() {
    { AssertedCollectionMembersIterator self = null;

      self = new AssertedCollectionMembersIterator();
      self.firstIterationP = true;
      self.value = null;
      self.observedCardinality = 0;
      self.proposition = null;
      self.nestedBaseIterator = null;
      self.baseIterator = null;
      self.kind = null;
      self.specializeP = false;
      self.collection = null;
      return (self);
    }
  }

  public boolean nextP() {
    { AssertedCollectionMembersIterator self = this;

      return (AssertedCollectionMembersIterator.allAssertedCollectionMembersDnextP(self));
    }
  }

  public static boolean allAssertedCollectionMembersDnextP(AssertedCollectionMembersIterator self) {
    { Iterator baseiterator = self.baseIterator;

      { Keyword testValue000 = self.kind;

        if (testValue000 == Logic.KWD_COLLECTION) {
          if (baseiterator.nextP()) {
            self.proposition = Logic.TRUE_PROPOSITION;
            self.value = baseiterator.value;
            return (true);
          }
        }
        else if (testValue000 == Logic.KWD_NAMED_DESCRIPTION) {
          if (baseiterator.nextP()) {
            self.proposition = ((Proposition)(baseiterator.value));
            self.value = (self.proposition.arguments.theArray)[0];
            if (self.specializeP) {
              self.observedCardinality = self.observedCardinality + 1;
            }
            return (true);
          }
        }
        else if (testValue000 == Logic.KWD_ENUMERATION) {
          { Iterator nestedbaseiterator = self.nestedBaseIterator;

            loop000 : for (;;) {
              if (nestedbaseiterator.nextP()) {
                if (!Stella_Object.eqlP(nestedbaseiterator.value, (self.proposition.arguments.theArray)[(self.proposition.arguments.length() - 1)])) {
                  self.value = nestedbaseiterator.value;
                  return (true);
                }
              }
              else if (baseiterator.nextP()) {
                self.proposition = ((Proposition)(baseiterator.value));
                nestedbaseiterator = ((Iterator)(self.proposition.arguments.allocateIterator()));
                self.nestedBaseIterator = nestedbaseiterator;
              }
              else {
                break loop000;
              }
            }
          }
        }
        else if (testValue000 == Logic.KWD_SKOLEM) {
          { Stella_Object collection = self.collection;
            boolean directP = !self.specializeP;

            { Proposition p = null;
              Iterator iter000 = ((Iterator)(baseiterator));

              while (iter000.nextP()) {
                p = ((Proposition)(iter000.value));
                if ((directP &&
                    Stella_Object.eqlP(Logic.valueOf((p.arguments.theArray)[1]), Logic.valueOf(collection))) ||
                    ((!directP) &&
                     LogicObject.collectionImpliesCollectionP(((LogicObject)(Logic.valueOf((p.arguments.theArray)[1]))), ((LogicObject)(Logic.valueOf(collection)))))) {
                  self.proposition = p;
                  self.value = (p.arguments.theArray)[0];
                  return (true);
                }
              }
            }
          }
        }
        else if ((testValue000 == Logic.KWD_DESCRIPTION) ||
            ((testValue000 == Logic.KWD_LOGIC_OBJECT) ||
             (testValue000 == Logic.KWD_UNDEFINED))) {
        }
        else {
          { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

            stream000.nativeStream.print("`" + testValue000 + "' is not a valid case option");
            throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
          }
        }
      }
      if ((self.kind == Logic.KWD_NAMED_DESCRIPTION) &&
          self.specializeP) {
        { MemoizationTable memoTable000 = null;
          Cons memoizedEntry000 = null;
          Stella_Object memoizedValue000 = null;

          if (Stella.$MEMOIZATION_ENABLEDp$) {
            memoTable000 = ((MemoizationTable)(Logic.SGT_LOGIC_F_ALL_ASSERTED_COLLECTION_MEMBERSdNEXTp_MEMO_TABLE_000.surrogateValue));
            if (memoTable000 == null) {
              Surrogate.initializeMemoizationTable(Logic.SGT_LOGIC_F_ALL_ASSERTED_COLLECTION_MEMBERSdNEXTp_MEMO_TABLE_000, "(:MAX-VALUES 100)");
              memoTable000 = ((MemoizationTable)(Logic.SGT_LOGIC_F_ALL_ASSERTED_COLLECTION_MEMBERSdNEXTp_MEMO_TABLE_000.surrogateValue));
            }
            memoizedEntry000 = MruMemoizationTable.lookupMruMemoizedValue(((MruMemoizationTable)(memoTable000)), self.collection, ((Module)(Stella.$MODULE$.get())), IntegerWrapper.wrapInteger(self.observedCardinality), Stella.MEMOIZED_NULL_VALUE, 2);
            memoizedValue000 = memoizedEntry000.value;
          }
          if (memoizedValue000 != null) {
            if (memoizedValue000 == Stella.MEMOIZED_NULL_VALUE) {
              memoizedValue000 = null;
            }
          }
          else {
            memoizedValue000 = self;
            if (Stella.$MEMOIZATION_ENABLEDp$) {
              memoizedEntry000.value = ((memoizedValue000 == null) ? Stella.MEMOIZED_NULL_VALUE : memoizedValue000);
            }
          }
          { AssertedCollectionMembersIterator memoizedvalue = ((AssertedCollectionMembersIterator)(memoizedValue000));

            if (memoizedvalue == self) {
              NamedDescription.updateObservedCardinality(((NamedDescription)(self.collection)), self.observedCardinality);
            }
          }
        }
      }
      self.value = null;
      return (false);
    }
  }

  public static Stella_Object accessAssertedCollectionMembersIteratorSlotValue(AssertedCollectionMembersIterator self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Logic.SYM_STELLA_COLLECTION) {
      if (setvalueP) {
        self.collection = value;
      }
      else {
        value = self.collection;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_SPECIALIZEp) {
      if (setvalueP) {
        self.specializeP = BooleanWrapper.coerceWrappedBooleanToBoolean(((BooleanWrapper)(value)));
      }
      else {
        value = (self.specializeP ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER);
      }
    }
    else if (slotname == Logic.SYM_LOGIC_KIND) {
      if (setvalueP) {
        self.kind = ((Keyword)(value));
      }
      else {
        value = self.kind;
      }
    }
    else if (slotname == Logic.SYM_STELLA_BASE_ITERATOR) {
      if (setvalueP) {
        self.baseIterator = ((Iterator)(value));
      }
      else {
        value = self.baseIterator;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_NESTED_BASE_ITERATOR) {
      if (setvalueP) {
        self.nestedBaseIterator = ((Iterator)(value));
      }
      else {
        value = self.nestedBaseIterator;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_PROPOSITION) {
      if (setvalueP) {
        self.proposition = ((Proposition)(value));
      }
      else {
        value = self.proposition;
      }
    }
    else if (slotname == Logic.SYM_LOGIC_OBSERVED_CARDINALITY) {
      if (setvalueP) {
        self.observedCardinality = ((IntegerWrapper)(value)).wrapperValue;
      }
      else {
        value = IntegerWrapper.wrapInteger(self.observedCardinality);
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
    { AssertedCollectionMembersIterator self = this;

      return (Logic.SGT_LOGIC_ASSERTED_COLLECTION_MEMBERS_ITERATOR);
    }
  }

}

