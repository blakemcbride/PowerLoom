//  -*- Mode: Java -*-
//
// PLConcept.java

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

public class PLConcept extends XMLObject {
    public String ConceptName;
    public String Module;
    public String SourceString;
    public List PLConcept;
    public List PLSurrogate;

  public static PLConcept new_PLConcept() {
    { PLConcept self = null;

      self = new PLConcept();
      self.cdataContent = null;
      self.textContent = null;
      self.PLSurrogate = null;
      self.PLConcept = null;
      self.SourceString = null;
      self.Module = null;
      self.ConceptName = null;
      return (self);
    }
  }

  public static void memberTest(PLConcept concept) {
    { List conceptlist = List.newList();
      PLConcept newconc = edu.isi.powerloom.server.gui.PLConcept.new_PLConcept();

      newconc.ConceptName = concept.ConceptName;
      conceptlist.insert(concept);
      Stella.STANDARD_OUTPUT.nativeStream.println("IDENTICAL MEMBER: " + conceptlist.memberP(concept));
      Stella.STANDARD_OUTPUT.nativeStream.println("NONIDENTICAL MEMBER: " + conceptlist.memberP(newconc));
    }
  }

  public static boolean PLConceptL(PLConcept inst1, PLConcept inst2) {
    return (Stella.stringL(inst1.ConceptName, inst2.ConceptName));
  }

  /** Return TRUE if <code>x</code> and <code>y</code> represent the same Concept
   * @param y
   * @return boolean
   */
  public boolean objectEqlP(Stella_Object y) {
    { PLConcept x = this;

      if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(y), GuiServer.SGT_GUI_SERVER_PLConcept)) {
        { PLConcept y000 = ((PLConcept)(y));

          if (Stella.stringEqlP(x.ConceptName, y000.ConceptName)) {
            return (true);
          }
        }
      }
      else {
      }
      return (false);
    }
  }

  public static Stella_Object access_PLConcept_Slot_Value(PLConcept self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == GuiServer.SYM_GUI_SERVER_ConceptName) {
      if (setvalueP) {
        self.ConceptName = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.ConceptName);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_Module) {
      if (setvalueP) {
        self.Module = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.Module);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_SourceString) {
      if (setvalueP) {
        self.SourceString = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.SourceString);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_PLConcept) {
      if (setvalueP) {
        self.PLConcept = ((List)(value));
      }
      else {
        value = self.PLConcept;
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_PLSurrogate) {
      if (setvalueP) {
        self.PLSurrogate = ((List)(value));
      }
      else {
        value = self.PLSurrogate;
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
    { PLConcept self = this;

      return (GuiServer.SGT_GUI_SERVER_PLConcept);
    }
  }

}

