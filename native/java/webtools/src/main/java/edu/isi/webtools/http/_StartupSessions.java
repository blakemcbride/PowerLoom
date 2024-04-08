//  -*- Mode: Java -*-
//
// _StartupSessions.java

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

public class _StartupSessions {
  public static void startupSessions() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/HTTP", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          Http.SGT_HTTP_SESSION = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("SESSION", null, 1)));
          Http.SYM_STELLA_NAME = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("NAME", Stella.getStellaModule("/STELLA", true), 0)));
          Http.SYM_HTTP_TIMEOUT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("TIMEOUT", null, 0)));
          Http.SYM_HTTP_TIMESTAMP = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("TIMESTAMP", null, 0)));
          Http.SYM_HTTP_OBJECTS = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("OBJECTS", null, 0)));
          Http.SYM_HTTP_STARTUP_SESSIONS = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-SESSIONS", null, 0)));
        }
        if (Stella.currentStartupTimePhaseP(4)) {
          Http.$SESSION_TABLE$ = KeyValueMap.newKeyValueMap();
          Http.$SESSIONS_LOCK$ = Stella.makeProcessLock();
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("SESSION", "(DEFCLASS SESSION (DICTIONARY) :DOCUMENTATION \"Object storing the state associated with a single session.\nAll session-related information is stored in a table indexed on string keys.\" :PARAMETERS ((ANY-KEY :TYPE STRING-WRAPPER) (ANY-VALUE :TYPE OBJECT)) :SLOTS ((NAME :TYPE STRING :INITIALLY NULL :PUBLIC? TRUE :DOCUMENTATION \"UUID uniquely identifying this session.\") (TIMEOUT :TYPE TIME-DURATION :INITIALLY NULL :DOCUMENTATION \"Timeout duration of session; NULL means no timeout.\") (TIMESTAMP :TYPE CALENDAR-DATE :INITIALLY (MAKE-CURRENT-DATE-TIME) :DOCUMENTATION \"Time this object was last accessed.\") (OBJECTS :TYPE (KEY-VALUE-MAP OF STRING-WRAPPER OBJECT) :DOCUMENTATION \"Table of session-related objects indexed on string keys.\" :INITIALLY (NEW KEY-VALUE-MAP))))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.http.Session", "newSession", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.http.Session", "accessSessionSlotValue", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.Session"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("CLEANUP-SESSION-TABLE", "(DEFUN CLEANUP-SESSION-TABLE ())", Native.find_java_method("edu.isi.webtools.http.Http", "cleanupSessionTable", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("LOOKUP-SESSION", "(DEFUN (LOOKUP-SESSION SESSION) ((NAME STRING) (ERRORIFTIMEOUT? BOOLEAN)) :DOCUMENTATION \"Retrieve an existing session object with `name' if it exists, NULL otherwise.\nIf a session was found but has timed out, raise an error if `errorIfTimeout?' is true,\notherwise, return the timed-out session.  Bumps the timestamp on existing sessions that\nhaven't yet timed out.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "lookupSession", new java.lang.Class [] {Native.find_java_class("java.lang.String"), java.lang.Boolean.TYPE}), null);
          Stella.defineFunctionObject("CREATE-SESSION", "(DEFUN (CREATE-SESSION SESSION) ((NAME STRING) (TIMEOUT INTEGER)) :DOCUMENTATION \"Create a new session object with `name' (replacing any existing\nsessions with the same name).  If `name' is NULL, generate a random UUID for it.\nTimeout after `timeout' seconds or never in case the value is <= 0 or undefined.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "createSession", new java.lang.Class [] {Native.find_java_class("java.lang.String"), java.lang.Integer.TYPE}), null);
          Stella.defineFunctionObject("GET-SESSION", "(DEFUN (GET-SESSION SESSION) ((NAME STRING) (ERRORIFTIMEOUT? BOOLEAN) (TIMEOUT INTEGER)) :DOCUMENTATION \"Retrieve an existing session object with `name' if it exists or create a new one.\nIf `name' is NULL, generate a random UUID for it.  If an existing object was found but has timed\nout, raise an error if `errorIfTimeout?' is true.  If a new object is created, initialize its\ntimeout field with `timeout' seconds (0 or undefined means no timeout).\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.Http", "getSession", new java.lang.Class [] {Native.find_java_class("java.lang.String"), java.lang.Boolean.TYPE, java.lang.Integer.TYPE}), null);
          Stella.defineMethodObject("(DEFMETHOD (TIMED-OUT? BOOLEAN) ((SESSION SESSION)) :DOCUMENTATION \"Return TRUE if `session' has timed out.\" :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.Session", "timedOutP", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD REFRESH ((SESSION SESSION)) :DOCUMENTATION \"Bump the timestamp of `session'.\" :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.Session", "refresh", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD (LOOKUP OBJECT) ((SESSION SESSION) (KEY STRING-WRAPPER)) :DOCUMENTATION \"Retrieve a value from a `session' based on `key'.\" :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.Session", "lookup", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StringWrapper")})), null);
          Stella.defineMethodObject("(DEFMETHOD INSERT-AT ((SESSION SESSION) (KEY STRING-WRAPPER) (VALUE OBJECT)) :DOCUMENTATION \"Associate `key' with `value' on `session'.\" :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.Session", "insertAt", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StringWrapper"), Native.find_java_class("edu.isi.stella.Stella_Object")})), null);
          Stella.defineFunctionObject("STARTUP-SESSIONS", "(DEFUN STARTUP-SESSIONS () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http._StartupSessions", "startupSessions", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(Http.SYM_HTTP_STARTUP_SESSIONS);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, Http.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupSessions"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("HTTP")))));
          Stella.defineGlobalVariableObject("(DEFGLOBAL *SESSION-TABLE* (KEY-VALUE-MAP OF STRING-WRAPPER SESSION) (NEW KEY-VALUE-MAP) :DOCUMENTATION \"System-wide session table; each session is indexed on a\nglobally unique session name.\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *SESSIONS-LOCK* PROCESS-LOCK-OBJECT (MAKE-PROCESS-LOCK))", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *SESSION-TABLE-CLEANUP-COUNTER* INTEGER 0)", null);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
