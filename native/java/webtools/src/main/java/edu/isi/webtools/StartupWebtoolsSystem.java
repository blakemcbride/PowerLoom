//  -*- Mode: Java -*-
//
// StartupWebtoolsSystem.java

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

package edu.isi.webtools;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;
import edu.isi.webtools.objects.soap_env.*;
import edu.isi.webtools.http.*;
import edu.isi.webtools.soap.*;

public class StartupWebtoolsSystem {
  public static void startupWebtoolsSystem() {
    synchronized (Stella.$BOOTSTRAP_LOCK$) {
      if (Stella.currentStartupTimePhaseP(0)) {
        if (!(Stella.systemStartedUpP("stella", "/STELLA"))) {
          StartupStellaSystem.startupStellaSystem();
        }
      }
      if (Stella.currentStartupTimePhaseP(1)) {
        Module.defineModuleFromStringifiedSource("/STELLA/XML-OBJECTS", "(:LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"xml_objects\" :JAVA-PACKAGE \"edu.isi.webtools.objects.xml_objects\" :CASE-SENSITIVE? TRUE :INCLUDES (\"STELLA\") :CODE-ONLY? TRUE)");
        Module.defineModuleFromStringifiedSource("/STELLA/XML-OBJECTS/SOAP-ENV", "(:LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"soap_env\" :JAVA-PACKAGE \"edu.isi.webtools.objects.soap_env\" :CASE-SENSITIVE? TRUE :INCLUDES (\"XML-OBJECTS\") :NAMESPACE? TRUE :CODE-ONLY? TRUE)");
        Module.defineModuleFromStringifiedSource("/STELLA/XML-OBJECTS/XSD", "(:LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"xmlschema\" :JAVA-PACKAGE \"edu.isi.webtools.objects.xmlschema\" :CASE-SENSITIVE? TRUE :INCLUDES (\"XML-OBJECTS\") :NAMESPACE? TRUE)");
        Module.defineModuleFromStringifiedSource("/STELLA/XML-OBJECTS/XSI", "(:LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"xmlschemainstance\" :JAVA-PACKAGE \"edu.isi.webtools.objects.xmlschemainstance\" :CASE-SENSITIVE? TRUE :INCLUDES (\"XML-OBJECTS\") :NAMESPACE? TRUE)");
        Module.defineModuleFromStringifiedSource("/STELLA/XML-OBJECTS/APACHE-SOAP", "(:LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"apachesoap\" :JAVA-PACKAGE \"edu.isi.webtools.objects.apachesoap\" :CASE-SENSITIVE? TRUE :INCLUDES (\"XML-OBJECTS\") :NAMESPACE? TRUE)");
        Module.defineModuleFromStringifiedSource("/HTTP", "(:USES (\"STELLA\") :LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"http\" :JAVA-PACKAGE \"edu.isi.webtools.http\" :CODE-ONLY? TRUE)");
        Module.defineModuleFromStringifiedSource("/SOAP", "(:USES (\"STELLA\" \"SOAP-ENV\" \"HTTP\") :LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"http\" :JAVA-PACKAGE \"edu.isi.webtools.soap\" :CODE-ONLY? TRUE)");
        Module.defineModuleFromStringifiedSource("/HTTP/WEBTOOLS", "(:INCLUDES (\"HTTP\" \"SOAP\") :LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"webtools\" :JAVA-PACKAGE \"edu.isi.webtools\" :CODE-ONLY? TRUE)");
      }
      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/HTTP/WEBTOOLS", Stella.$STARTUP_TIME_PHASE$ > 1));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          if (Stella.currentStartupTimePhaseP(2)) {
            Webtools.SYM_WEBTOOLS_STARTUP_WEBTOOLS_SYSTEM = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-WEBTOOLS-SYSTEM", null, 0)));
          }
          if (Stella.currentStartupTimePhaseP(6)) {
            Stella.finalizeClasses();
          }
          if (Stella.currentStartupTimePhaseP(7)) {
            Stella.defineFunctionObject("STARTUP-WEBTOOLS-SYSTEM", "(DEFUN STARTUP-WEBTOOLS-SYSTEM () :PUBLIC? TRUE :C-CALLABLE? TRUE :C-NAMESPACE-PREFIX \"stella_\")", Native.find_java_method("edu.isi.webtools.StartupWebtoolsSystem", "startupWebtoolsSystem", new java.lang.Class [] {}), null);
            { MethodSlot function = Symbol.lookupFunction(Webtools.SYM_WEBTOOLS_STARTUP_WEBTOOLS_SYSTEM);

              KeyValueList.setDynamicSlotValue(function.dynamicSlots, edu.isi.webtools.http.Http.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("StartupWebtoolsSystem"), Stella.NULL_STRING_WRAPPER);
            }
          }
          if (Stella.currentStartupTimePhaseP(8)) {
            Stella.finalizeSlots();
            Stella.cleanupUnfinalizedClasses();
          }
          if (Stella.currentStartupTimePhaseP(9)) {
            Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("/HTTP/WEBTOOLS")))));
            { int phase = Stella.NULL_INTEGER;
              int iter006 = 0;
              int upperBound007 = 9;

              for (;iter006 <= upperBound007; iter006 = iter006 + 1) {
                phase = iter006;
                Stella.$STARTUP_TIME_PHASE$ = phase;
                _StartupHttpClient.startupHttpClient();
                _StartupHttpServer.startupHttpServer();
                _StartupSessions.startupSessions();
                edu.isi.webtools.objects.xml_objects._StartupXmlObject.STARTUP_XML_OBJECT();
                edu.isi.webtools.objects.xmlschema._StartupXmlSchema.STARTUP_XML_SCHEMA();
                edu.isi.webtools.objects.xmlschemainstance._StartupXmlSchemaInstance.STARTUP_XML_SCHEMA_INSTANCE();
                edu.isi.webtools.objects.apachesoap._StartupApacheSoap.STARTUP_APACHE_SOAP();
                _StartupSoapEnv.STARTUP_SOAP_ENV();
                edu.isi.webtools.objects.xml_objects._StartupMarshaller.STARTUP_MARSHALLER();
                _StartupSoap.startupSoap();
              }
            }
            Stella.$STARTUP_TIME_PHASE$ = 999;
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

}
