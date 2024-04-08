//  -*- Mode: Java -*-
//
// runAgentAndWaitForResponse.java

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

package edu.isi.webtools.examples.fetch;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.stella.*;

public class runAgentAndWaitForResponse extends XMLObject {
    public edu.isi.webtools.examples.fetchcontent.arg0 arg0;
    public edu.isi.webtools.examples.fetchcontent.arg1 arg1;
    public edu.isi.webtools.examples.fetchcontent.arg2 arg2;

  public static runAgentAndWaitForResponse new_runAgentAndWaitForResponse() {
    { runAgentAndWaitForResponse self = null;

      self = new runAgentAndWaitForResponse();
      self.cdataContent = null;
      self.textContent = null;
      self.arg2 = null;
      self.arg1 = null;
      self.arg0 = null;
      return (self);
    }
  }

  public static Stella_Object access_runAgentAndWaitForResponse_Slot_Value(runAgentAndWaitForResponse self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Fetch.SYM_FETCH_arg0) {
      if (setvalueP) {
        self.arg0 = ((edu.isi.webtools.examples.fetchcontent.arg0)(value));
      }
      else {
        value = self.arg0;
      }
    }
    else if (slotname == Fetch.SYM_FETCH_arg1) {
      if (setvalueP) {
        self.arg1 = ((edu.isi.webtools.examples.fetchcontent.arg1)(value));
      }
      else {
        value = self.arg1;
      }
    }
    else if (slotname == Fetch.SYM_FETCH_arg2) {
      if (setvalueP) {
        self.arg2 = ((edu.isi.webtools.examples.fetchcontent.arg2)(value));
      }
      else {
        value = self.arg2;
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
    { runAgentAndWaitForResponse self = this;

      return (Fetch.SGT_FETCH_runAgentAndWaitForResponse);
    }
  }

}

