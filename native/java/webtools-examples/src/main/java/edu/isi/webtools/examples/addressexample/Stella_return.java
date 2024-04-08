//  -*- Mode: Java -*-
//
// Stella_return.java

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
| The Original Code is the STELLA Programming Language.                      |
|                                                                            |
| The Initial Developer of the Original Code is                              |
| UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
| 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
|                                                                            |
| Portions created by the Initial Developer are Copyright (C) 2003-2023      |
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
+---------------------------- END LICENSE BLOCK -----------------------------+
*/

package edu.isi.webtools.examples.addressexample;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.stella.*;

public class Stella_return extends XMLObject {
    public streetNum streetNum;
    public streetName streetName;
    public city city;
    public state state;
    public zip zip;
    public phoneNumber phone;
    public String type;

  public static Stella_return new_return() {
    { Stella_return self = null;

      self = new Stella_return();
      self.cdataContent = null;
      self.textContent = null;
      self.type = "ADDRESS-DEMO:address";
      self.phone = null;
      self.zip = null;
      self.state = null;
      self.city = null;
      self.streetName = null;
      self.streetNum = null;
      return (self);
    }
  }

  public static Stella_Object access_return_Slot_Value(Stella_return self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == AddressExample.SYM_ADDRESS_EXAMPLE_streetNum) {
      if (setvalueP) {
        self.streetNum = ((streetNum)(value));
      }
      else {
        value = self.streetNum;
      }
    }
    else if (slotname == AddressExample.SYM_ADDRESS_EXAMPLE_streetName) {
      if (setvalueP) {
        self.streetName = ((streetName)(value));
      }
      else {
        value = self.streetName;
      }
    }
    else if (slotname == AddressExample.SYM_ADDRESS_EXAMPLE_city) {
      if (setvalueP) {
        self.city = ((city)(value));
      }
      else {
        value = self.city;
      }
    }
    else if (slotname == AddressExample.SYM_ADDRESS_EXAMPLE_state) {
      if (setvalueP) {
        self.state = ((state)(value));
      }
      else {
        value = self.state;
      }
    }
    else if (slotname == AddressExample.SYM_ADDRESS_EXAMPLE_zip) {
      if (setvalueP) {
        self.zip = ((zip)(value));
      }
      else {
        value = self.zip;
      }
    }
    else if (slotname == AddressExample.SYM_ADDRESS_EXAMPLE_phone) {
      if (setvalueP) {
        self.phone = ((phoneNumber)(value));
      }
      else {
        value = self.phone;
      }
    }
    else if (slotname == AddressExample.SYM_XSI_type) {
      if (setvalueP) {
        self.type = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.type);
      }
    }
    else {
      { OutputStringStream STREAM_000 = OutputStringStream.newOutputStringStream();

        STREAM_000.nativeStream.print("`" + slotname + "' is not a valid case option");
        throw ((StellaException)(StellaException.newStellaException(STREAM_000.theStringReader()).fillInStackTrace()));
      }
    }
    return (value);
  }

  public Surrogate primaryType() {
    { Stella_return self = this;

      return (AddressExample.SGT_ADDRESS_EXAMPLE_return);
    }
  }

}

