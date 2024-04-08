//  -*- Mode: Java -*-
//
// _StartupFetchDemoContent.java

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

package edu.isi.webtools.examples.fetchcontent;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.stella.*;

public class _StartupFetchDemoContent {
  public static void STARTUP_FETCH_DEMO_CONTENT() {
    { Object OLD_$MODULE$_000 = Stella.$MODULE$.get();
      Object OLD_$CONTEXT$_000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/STELLA/XML-OBJECTS/FETCH-CONTENT", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          FetchContent.SGT_FETCH_CONTENT_arg0 = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("arg0", null, 1)));
          FetchContent.SGT_FETCH_CONTENT_arg1 = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("arg1", null, 1)));
          FetchContent.SYM_FETCH_CONTENT_item = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("item", null, 0)));
          FetchContent.SGT_FETCH_CONTENT_item = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("item", null, 1)));
          FetchContent.SYM_FETCH_CONTENT_key = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("key", null, 0)));
          FetchContent.SYM_FETCH_CONTENT_val = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("val", null, 0)));
          FetchContent.SGT_FETCH_CONTENT_key = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("key", null, 1)));
          FetchContent.SGT_FETCH_CONTENT_value = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("value", null, 1)));
          FetchContent.SGT_FETCH_CONTENT_arg2 = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("arg2", null, 1)));
          FetchContent.SYM_FETCH_CONTENT_STARTUP_FETCH_DEMO_CONTENT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-FETCH-DEMO-CONTENT", null, 0)));
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("arg0", "(DEFCLASS arg0 (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:string\")))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.fetchcontent.arg0", "new_arg0", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.fetchcontent.arg0", "access_arg0_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.fetchcontent.arg0"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("arg1", "(DEFCLASS arg1 (XMLObject) :PUBLIC-SLOTS ((item :TYPE item)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.fetchcontent.arg1", "new_arg1", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.fetchcontent.arg1", "access_arg1_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.fetchcontent.arg1"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("item", "(DEFCLASS item (XMLObject) :PUBLIC-SLOTS ((key :TYPE key) (val :TYPE value)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.fetchcontent.item", "new_item", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.fetchcontent.item", "access_item_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.fetchcontent.item"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("key", "(DEFCLASS key (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:string\")))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.fetchcontent.key", "new_key", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.fetchcontent.key", "access_key_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.fetchcontent.key"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("value", "(DEFCLASS value (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:string\")))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.fetchcontent.value", "new_value", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.fetchcontent.value", "access_value_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.fetchcontent.value"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("arg2", "(DEFCLASS arg2 (XMLObject))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.fetchcontent.arg2", "new_arg2", new java.lang.Class [] {});
          }
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("STARTUP-FETCH-DEMO-CONTENT", "(DEFUN STARTUP-FETCH-DEMO-CONTENT () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.examples.fetchcontent._StartupFetchDemoContent", "STARTUP_FETCH_DEMO_CONTENT", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(FetchContent.SYM_FETCH_CONTENT_STARTUP_FETCH_DEMO_CONTENT);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, edu.isi.webtools.examples.sample.Sample.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupFetchDemoContent"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("FETCH-CONTENT")))));
          XmlObjects.$NAMESPACE_PREFIX_URI_TABLE$.insertAt(StringWrapper.wrapString("FETCH-CONTENT"), StringWrapper.wrapString("urn:fetchDemoContent"));
          XmlObjects.$NAMESPACE_URI_PREFIX_TABLE$.insertAt(StringWrapper.wrapString("urn:fetchDemoContent"), StringWrapper.wrapString("FETCH-CONTENT"));
          XmlObjects.$INVISIBLE_NAMESPACES_ON_OUTPUT$ = Cons.cons(StringWrapper.wrapString("FETCH-CONTENT"), XmlObjects.$INVISIBLE_NAMESPACES_ON_OUTPUT$);
        }

      } finally {
        Stella.$CONTEXT$.set(OLD_$CONTEXT$_000);
        Stella.$MODULE$.set(OLD_$MODULE$_000);
      }
    }
  }

}
