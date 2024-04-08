//  -*- Mode: Java -*-
//
// _StartupHttpServerImpl.java

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
 | Portions created by the Initial Developer are Copyright (C) 2009-2023      |
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

package edu.isi.webtools.http.sun;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;
import edu.isi.webtools.http.*;

public class _StartupHttpServerImpl {
  public static void startupHttpServerImpl() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/HTTP/SUN", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          Sun.SGT_SUN_HTTP_SERVER_SUN = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("HTTP-SERVER-SUN", null, 1)));
          Sun.SYM_SUN_CURRENT_SERVER_PORT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("CURRENT-SERVER-PORT", null, 0)));
          Sun.KWD_OK = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("OK", null, 2)));
          Sun.SGT_SUN_HTTP_EXCHANGE_SUN = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("HTTP-EXCHANGE-SUN", null, 1)));
          Sun.SYM_SUN_RESPONSE_CODE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("RESPONSE-CODE", null, 0)));
          Sun.SYM_SUN_HANDLER_OPTIONS = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("HANDLER-OPTIONS", null, 0)));
          Sun.KWD_BLOCK = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("BLOCK", null, 2)));
          Sun.KWD_CONTENT_TYPE = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("CONTENT-TYPE", null, 2)));
          Sun.KWD_HTML = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("HTML", null, 2)));
          Sun.SYM_SUN_STARTUP_HTTP_SERVER_IMPL = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-HTTP-SERVER-IMPL", null, 0)));
          Sun.SYM_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", Stella.getStellaModule("/STELLA", true), 0)));
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          Stella.defineClassFromStringifiedSource("NATIVE-HTTP-SERVER", "(DEFCLASS NATIVE-HTTP-SERVER () :JAVA-NATIVE-TYPE \"com.sun.net.httpserver.HttpServer\")");
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("HTTP-SERVER-SUN", "(DEFCLASS HTTP-SERVER-SUN (HTTP-SERVER) :PUBLIC? TRUE :SLOTS ((CURRENT-SERVER :TYPE NATIVE-HTTP-SERVER) (CURRENT-SERVER-PORT :TYPE INTEGER)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "newHttpServerSun", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "accessHttpServerSunSlotValue", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.sun.HttpServerSun"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          Stella.defineClassFromStringifiedSource("NATIVE-HTTP-EXCHANGE", "(DEFCLASS NATIVE-HTTP-EXCHANGE () :JAVA-NATIVE-TYPE \"com.sun.net.httpserver.HttpExchange\")");
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("HTTP-EXCHANGE-SUN", "(DEFCLASS HTTP-EXCHANGE-SUN (HTTP-EXCHANGE) :SLOTS ((NATIVE-EXCHANGE :TYPE NATIVE-HTTP-EXCHANGE) (RESPONSE-CODE :TYPE INTEGER :INITIALLY (GET-HTTP-RESPONSE-CODE :OK NULL)) (REPLY-STREAM :TYPE NATIVE-OUTPUT-STREAM) (HANDLER-OPTIONS :TYPE PROPERTY-LIST)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.http.sun.HttpExchangeSun", "newHttpExchangeSun", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.http.sun.HttpExchangeSun", "accessHttpExchangeSunSlotValue", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.sun.HttpExchangeSun"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineMethodObject("(DEFMETHOD (START-HTTP-SERVER-IMPL STRING) ((SERVER HTTP-SERVER-SUN) (PORT INTEGER)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "startHttpServerImpl", new java.lang.Class [] {java.lang.Integer.TYPE})), null);
          Stella.defineMethodObject("(DEFMETHOD STOP-HTTP-SERVER-IMPL ((SERVER HTTP-SERVER-SUN)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "stopHttpServerImpl", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-HEADER-VALUE-IMPL STRING) ((SERVER HTTP-SERVER-SUN) (XCHG HTTP-EXCHANGE) (KEY KEYWORD)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "getHeaderValueImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange"), Native.find_java_class("edu.isi.stella.Keyword")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REPLY-HEADER-VALUE-IMPL STRING) ((SERVER HTTP-SERVER-SUN) (XCHG HTTP-EXCHANGE) (KEY KEYWORD)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "getReplyHeaderValueImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange"), Native.find_java_class("edu.isi.stella.Keyword")})), null);
          Stella.defineMethodObject("(DEFMETHOD SET-REPLY-HEADER-VALUE-IMPL ((SERVER HTTP-SERVER-SUN) (XCHG HTTP-EXCHANGE) (KEY KEYWORD) (VALUE STRING)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "setReplyHeaderValueImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange"), Native.find_java_class("edu.isi.stella.Keyword"), Native.find_java_class("java.lang.String")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-URI-IMPL STRING) ((SERVER HTTP-SERVER-SUN) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "getRequestUriImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-URI-QUERY-IMPL STRING) ((SERVER HTTP-SERVER-SUN) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "getRequestUriQueryImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-URI-PATH-IMPL STRING) ((SERVER HTTP-SERVER-SUN) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "getRequestUriPathImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-METHOD-IMPL KEYWORD) ((SERVER HTTP-SERVER-SUN) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "getRequestMethodImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-PROTOCOL-IMPL STRING) ((SERVER HTTP-SERVER-SUN) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "getRequestProtocolImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-BODY-IMPL STRING) ((SERVER HTTP-SERVER-SUN) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "getRequestBodyImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-LOCAL-ADDRESS-IMPL STRING) ((SERVER HTTP-SERVER-SUN) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "getRequestLocalAddressImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REQUEST-REMOTE-ADDRESS-IMPL STRING) ((SERVER HTTP-SERVER-SUN) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "getRequestRemoteAddressImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-REPLY-STREAM-IMPL NATIVE-OUTPUT-STREAM) ((SERVER HTTP-SERVER-SUN) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "getReplyStreamImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineMethodObject("(DEFMETHOD SET-RESPONSE-CODE-IMPL ((SERVER HTTP-SERVER-SUN) (XCHG HTTP-EXCHANGE) (CODE KEYWORD)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "setResponseCodeImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange"), Native.find_java_class("edu.isi.stella.Keyword")})), null);
          Stella.defineMethodObject("(DEFMETHOD PUBLISH-FILE-IMPL ((SERVER HTTP-SERVER-SUN) (PATH STRING) (FILE STRING) (OPTIONS PROPERTY-LIST)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "publishFileImpl", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.PropertyList")})), null);
          Stella.defineMethodObject("(DEFMETHOD PUBLISH-DIRECTORY-IMPL ((SERVER HTTP-SERVER-SUN) (PATH STRING) (DIRECTORY STRING) (OPTIONS PROPERTY-LIST)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "publishDirectoryImpl", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.PropertyList")})), null);
          Stella.defineMethodObject("(DEFMETHOD PUBLISH-HANDLER-IMPL ((SERVER HTTP-SERVER-SUN) (PATH STRING) (HANDLER FUNCTION-CODE) (OPTIONS PROPERTY-LIST)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "publishHandlerImpl", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.reflect.Method"), Native.find_java_class("edu.isi.stella.PropertyList")})), null);
          Stella.defineMethodObject("(DEFMETHOD (GET-HANDLER-OPTIONS-IMPL PROPERTY-LIST) ((SERVER HTTP-SERVER-SUN) (XCHG HTTP-EXCHANGE)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.http.sun.HttpServerSun", "getHandlerOptionsImpl", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.http.HttpExchange")})), null);
          Stella.defineFunctionObject("STARTUP-HTTP-SERVER-IMPL", "(DEFUN STARTUP-HTTP-SERVER-IMPL () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.http.sun._StartupHttpServerImpl", "startupHttpServerImpl", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(Sun.SYM_SUN_STARTUP_HTTP_SERVER_IMPL);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, Sun.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupHttpServerImpl"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("HTTP/SUN")))));
          if ((Http.$HTTP_SERVER_IMPLEMENTATION$ != null) &&
              (!Stella_Object.isaP(Http.$HTTP_SERVER_IMPLEMENTATION$, Sun.SGT_SUN_HTTP_SERVER_SUN))) {
            throw ((StellaException)(StellaException.newStellaException("Conflicting HTTP server implementation already loaded").fillInStackTrace()));
          }
          else {
            Http.$HTTP_SERVER_IMPLEMENTATION$ = HttpServerSun.newHttpServerSun();
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
