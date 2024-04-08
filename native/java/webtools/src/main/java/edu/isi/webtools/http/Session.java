//  -*- Mode: Java -*-
//
// Session.java

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

package edu.isi.webtools.http;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;

/** Object storing the state associated with a single session.
 * All session-related information is stored in a table indexed on string keys.
 * @author Stella Java Translator
 */
public class Session extends Dictionary {
    /** UUID uniquely identifying this session.
     */
    public String name;
    /** Timeout duration of session; NULL means no timeout.
     */
    public TimeDuration timeout;
    /** Time this object was last accessed.
     */
    public CalendarDate timestamp;
    /** Table of session-related objects indexed on string keys.
     */
    public KeyValueMap objects;

  public static Session newSession() {
    { Session self = null;

      self = new Session();
      self.objects = KeyValueMap.newKeyValueMap();
      self.timestamp = CalendarDate.makeCurrentDateTime();
      self.timeout = null;
      self.name = null;
      return (self);
    }
  }

  /** Associate <code>key</code> with <code>value</code> on <code>session</code>.
   * @param key
   * @param value
   */
  public void insertAt(StringWrapper key, Stella_Object value) {
    { Session session = this;

      session.objects.insertAt(key, value);
    }
  }

  /** Retrieve a value from a <code>session</code> based on <code>key</code>.
   * @param key
   * @return Stella_Object
   */
  public Stella_Object lookup(StringWrapper key) {
    { Session session = this;

      return (session.objects.lookup(key));
    }
  }

  /** Bump the timestamp of <code>session</code>.
   */
  public void refresh() {
    { Session session = this;

      { TimeDuration timeout = session.timeout;

        if (timeout != null) {
          session.timestamp = CalendarDate.makeCurrentDateTime();
        }
      }
    }
  }

  /** Return TRUE if <code>session</code> has timed out.
   * @return boolean
   */
  public boolean timedOutP() {
    { Session session = this;

      { TimeDuration timeout = session.timeout;
        CalendarDate timestamp = session.timestamp;

        if (timeout == null) {
          return (false);
        }
        else {
          return (DateTimeObject.timeSubtract(CalendarDate.makeCurrentDateTime(), timestamp).greaterP(timeout));
        }
      }
    }
  }

  public static Stella_Object accessSessionSlotValue(Session self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Http.SYM_STELLA_NAME) {
      if (setvalueP) {
        self.name = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.name);
      }
    }
    else if (slotname == Http.SYM_HTTP_TIMEOUT) {
      if (setvalueP) {
        self.timeout = ((TimeDuration)(value));
      }
      else {
        value = self.timeout;
      }
    }
    else if (slotname == Http.SYM_HTTP_TIMESTAMP) {
      if (setvalueP) {
        self.timestamp = ((CalendarDate)(value));
      }
      else {
        value = self.timestamp;
      }
    }
    else if (slotname == Http.SYM_HTTP_OBJECTS) {
      if (setvalueP) {
        self.objects = ((KeyValueMap)(value));
      }
      else {
        value = self.objects;
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
    { Session self = this;

      return (Http.SGT_HTTP_SESSION);
    }
  }

}

