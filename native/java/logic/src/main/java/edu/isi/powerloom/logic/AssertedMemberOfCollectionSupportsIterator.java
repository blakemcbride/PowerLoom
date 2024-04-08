//  -*- Mode: Java -*-
//
// AssertedMemberOfCollectionSupportsIterator.java

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

/** Iterator reimplementation of <code>memberOfCollectionP</code>.
 * Generates proposition supports that prove that the bound self.member is or is not
 * an asserted member of the specified collection (handles reverse polarity).
 * @author Stella Java Translator
 */
public class AssertedMemberOfCollectionSupportsIterator extends AssertedCollectionMembersIterator {
    public Stella_Object member;

  public static AssertedMemberOfCollectionSupportsIterator newAssertedMemberOfCollectionSupportsIterator() {
    { AssertedMemberOfCollectionSupportsIterator self = null;

      self = new AssertedMemberOfCollectionSupportsIterator();
      self.firstIterationP = true;
      self.value = null;
      self.observedCardinality = 0;
      self.proposition = null;
      self.nestedBaseIterator = null;
      self.baseIterator = null;
      self.kind = null;
      self.specializeP = false;
      self.collection = null;
      self.member = null;
      return (self);
    }
  }

  public boolean nextP() {
    { AssertedMemberOfCollectionSupportsIterator self = this;

      return (AssertedMemberOfCollectionSupportsIterator.allAssertedMemberOfCollectionSupportsDnextP(self));
    }
  }

  public static boolean allAssertedMemberOfCollectionSupportsDnextP(AssertedMemberOfCollectionSupportsIterator self) {
    { Stella_Object member = self.member;
      Iterator baseiterator = self.baseIterator;

      { Keyword testValue000 = self.kind;

        if (testValue000 == Logic.KWD_COLLECTION) {
          if (baseiterator.nextP()) {
            self.proposition = Logic.TRUE_PROPOSITION;
            self.value = member;
            return (true);
          }
        }
        else if (testValue000 == Logic.KWD_NAMED_DESCRIPTION) {
          if (baseiterator.nextP()) {
            self.proposition = ((Proposition)(baseiterator.value));
            self.value = member;
            return (true);
          }
        }
        else if (testValue000 == Logic.KWD_ENUMERATION) {
          { Iterator nestedbaseiterator = self.nestedBaseIterator;

            loop000 : for (;;) {
              { Stella_Object arg = null;
                Iterator iter000 = nestedbaseiterator;

                while (iter000.nextP()) {
                  arg = iter000.value;
                  if (Stella_Object.eqlP(Logic.valueOf(arg), member) &&
                      (!Stella_Object.eqlP(arg, (self.proposition.arguments.theArray)[(self.proposition.arguments.length() - 1)]))) {
                    self.value = member;
                    if (((Boolean)(Logic.$REVERSEPOLARITYp$.get())).booleanValue()) {
                      self.value = null;
                      return (false);
                    }
                    else {
                      self.value = member;
                      return (true);
                    }
                  }
                }
              }
              if (baseiterator.nextP()) {
                self.proposition = ((Proposition)(baseiterator.value));
                nestedbaseiterator = ((Iterator)(self.proposition.arguments.allocateIterator()));
                self.nestedBaseIterator = nestedbaseiterator;
              }
              else {
                break loop000;
              }
            }
            if (((Boolean)(Logic.$REVERSEPOLARITYp$.get())).booleanValue() &&
                (self.value == null)) {
              self.value = member;
              return (true);
            }
          }
        }
        else if (testValue000 == Logic.KWD_SKOLEM) {
          { Stella_Object collection = self.collection;
            LogicObject subcollection = null;

            { Proposition p = null;
              Iterator iter001 = ((Iterator)(baseiterator));

              while (iter001.nextP()) {
                p = ((Proposition)(iter001.value));
                subcollection = ((LogicObject)(Logic.valueOf((p.arguments.theArray)[1])));
                if ((((Boolean)(Logic.$REVERSEPOLARITYp$.get())).booleanValue() ? LogicObject.collectionImpliesCollectionP(((LogicObject)(collection)), subcollection) : LogicObject.collectionImpliesCollectionP(subcollection, ((LogicObject)(collection))))) {
                  self.proposition = p;
                  self.value = member;
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
      return (false);
    }
  }

  public static Stella_Object accessAssertedMemberOfCollectionSupportsIteratorSlotValue(AssertedMemberOfCollectionSupportsIterator self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Logic.SYM_LOGIC_MEMBER) {
      if (setvalueP) {
        self.member = value;
      }
      else {
        value = self.member;
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
    { AssertedMemberOfCollectionSupportsIterator self = this;

      return (Logic.SGT_LOGIC_ASSERTED_MEMBER_OF_COLLECTION_SUPPORTS_ITERATOR);
    }
  }

}

