//  -*- Mode: Java -*-
//
// PLProposition.java

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
 | Portions created by the Initial Developer are Copyright (C) 2002-2023      |
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

package edu.isi.powerloom.server.gui;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;
import edu.isi.powerloom.logic.*;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.webtools.soap.*;
import edu.isi.powerloom.server.*;

public class PLProposition extends XMLObject {
    public String PropositionName;
    public String IsStrict;
    public String IsAsserted;
    public String IsRule;

  public static PLProposition new_PLProposition() {
    { PLProposition self = null;

      self = new PLProposition();
      self.cdataContent = null;
      self.textContent = null;
      self.IsRule = null;
      self.IsAsserted = null;
      self.IsStrict = null;
      self.PropositionName = null;
      return (self);
    }
  }

  /** Return TRUE if <code>x</code> and <code>y</code> represent the same Propositions
   * @param y
   * @return boolean
   */
  public boolean objectEqlP(Stella_Object y) {
    { PLProposition x = this;

      if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(y), GuiServer.SGT_GUI_SERVER_PLProposition)) {
        { PLProposition y000 = ((PLProposition)(y));

          if (Stella.stringEqlP(x.PropositionName, y000.PropositionName)) {
            return (true);
          }
        }
      }
      else {
      }
      return (false);
    }
  }

  public static Stella_Object access_PLProposition_Slot_Value(PLProposition self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == GuiServer.SYM_GUI_SERVER_PropositionName) {
      if (setvalueP) {
        self.PropositionName = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.PropositionName);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_IsStrict) {
      if (setvalueP) {
        self.IsStrict = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.IsStrict);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_IsAsserted) {
      if (setvalueP) {
        self.IsAsserted = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.IsAsserted);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_IsRule) {
      if (setvalueP) {
        self.IsRule = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.IsRule);
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
    { PLProposition self = this;

      return (GuiServer.SGT_GUI_SERVER_PLProposition);
    }
  }

}

