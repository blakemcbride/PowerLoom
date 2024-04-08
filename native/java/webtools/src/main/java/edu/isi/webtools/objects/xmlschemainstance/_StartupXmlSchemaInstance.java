//  -*- Mode: Java -*-
//
// _StartupXmlSchemaInstance.java

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

package edu.isi.webtools.objects.xmlschemainstance;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.stella.*;

public class _StartupXmlSchemaInstance {
  public static void STARTUP_XML_SCHEMA_INSTANCE() {
    { Object OLD_$MODULE$_000 = Stella.$MODULE$.get();
      Object OLD_$CONTEXT$_000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/STELLA/XML-OBJECTS/XSI", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          Xsi.SYM_XSI_STARTUP_XML_SCHEMA_INSTANCE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-XML-SCHEMA-INSTANCE", null, 0)));
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("STARTUP-XML-SCHEMA-INSTANCE", "(DEFUN STARTUP-XML-SCHEMA-INSTANCE () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.objects.xmlschemainstance._StartupXmlSchemaInstance", "STARTUP_XML_SCHEMA_INSTANCE", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(Xsi.SYM_XSI_STARTUP_XML_SCHEMA_INSTANCE);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, edu.isi.webtools.http.Http.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupXmlSchemaInstance"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("XSI")))));
          XmlObjects.$NAMESPACE_PREFIX_URI_TABLE$.insertAt(StringWrapper.wrapString("XSI"), StringWrapper.wrapString("http://www.w3.org/2001/XMLSchema-instance"));
          XmlObjects.$NAMESPACE_URI_PREFIX_TABLE$.insertAt(StringWrapper.wrapString("http://www.w3.org/2001/XMLSchema-instance"), StringWrapper.wrapString("XSI"));
        }

      } finally {
        Stella.$CONTEXT$.set(OLD_$CONTEXT$_000);
        Stella.$MODULE$.set(OLD_$MODULE$_000);
      }
    }
  }

}
