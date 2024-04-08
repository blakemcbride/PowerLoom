//  -*- Mode: Java -*-
//
// _StartupXmlObject.java

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

package edu.isi.webtools.objects.xml_objects;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;

public class _StartupXmlObject {
  public static void STARTUP_XML_OBJECT() {
    { Object OLD_$MODULE$_000 = Stella.$MODULE$.get();
      Object OLD_$CONTEXT$_000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/STELLA/XML-OBJECTS", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          XmlObjects.KWD_INVISIBLE_ON_OUTPUTp = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("INVISIBLE-ON-OUTPUT?", null, 2)));
          XmlObjects.SYM_STELLA_PUSHQ = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("PUSHQ", Stella.getStellaModule("/STELLA", true), 0)));
          XmlObjects.SYM_XML_OBJECTS_$INVISIBLE_NAMESPACES_ON_OUTPUT$ = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("*INVISIBLE-NAMESPACES-ON-OUTPUT*", null, 0)));
          XmlObjects.SYM_STELLA_STARTUP_TIME_PROGN = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-TIME-PROGN", Stella.getStellaModule("/STELLA", true), 0)));
          XmlObjects.SYM_STELLA_INSERT_AT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("INSERT-AT", Stella.getStellaModule("/STELLA", true), 0)));
          XmlObjects.SYM_XML_OBJECTS_$NAMESPACE_PREFIX_URI_TABLE$ = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("*NAMESPACE-PREFIX-URI-TABLE*", null, 0)));
          XmlObjects.SYM_XML_OBJECTS_$NAMESPACE_URI_PREFIX_TABLE$ = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("*NAMESPACE-URI-PREFIX-TABLE*", null, 0)));
          XmlObjects.SYM_XML_OBJECTS_textContent = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("textContent", null, 0)));
          XmlObjects.SYM_XML_OBJECTS_cdataContent = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("cdataContent", null, 0)));
          XmlObjects.SYM_XML_OBJECTS_STARTUP_XML_OBJECT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-XML-OBJECT", null, 0)));
        }
        if (Stella.currentStartupTimePhaseP(4)) {
          XmlObjects.$NAMESPACE_PREFIX_URI_TABLE$ = PropertyList.newPropertyList();
          XmlObjects.$NAMESPACE_URI_PREFIX_TABLE$ = PropertyList.newPropertyList();
          XmlObjects.$INVISIBLE_NAMESPACES_ON_OUTPUT$ = Stella.NIL;
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          Cons.defineExternalSlotFromParseTree(Stella.getQuotedTree("((DEFSLOT STORAGE-SLOT ENCODING-SCHEME :TYPE KEYWORD :OPTION-KEYWORD :ENCODING-SCHEME :DOCUMENTATION \"Specify an encoding scheme used to encode the value\nof a slot.  The currently understood values are :PLAIN (or NULL) and :BASE64\") \"/STELLA/XML-OBJECTS\")", "/STELLA/XML-OBJECTS"));
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("XMLObject", "(DEFCLASS XMLObject (STANDARD-OBJECT) :DOCUMENTATION \"The Root of all XMLObjects\" :ABSTRACT? TRUE :PUBLIC-SLOTS ((textContent :TYPE STRING) (cdataContent :TYPE STRING)) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM (TO-XML-STRING SELF)))");

            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "access_XMLObject_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("DEFNAMESPACE", "(DEFUN DEFNAMESPACE (|&BODY| (body CONS)) :TYPE OBJECT :MACRO? TRUE)", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "DEFNAMESPACE", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
          Stella.defineExternalSlotFromStringifiedSource("(DEFSLOT STORAGE-SLOT ENCODING-SCHEME :TYPE KEYWORD :OPTION-KEYWORD :ENCODING-SCHEME :DOCUMENTATION \"Specify an encoding scheme used to encode the value\nof a slot.  The currently understood values are :PLAIN (or NULL) and :BASE64\" :ALLOCATION :DYNAMIC)");
          Stella.defineMethodObject("(DEFMETHOD (GET-CONTENT STRING) ((OBJ XMLObject)) :PUBLIC? TRUE :DOCUMENTATION \"Returns the textContent or cdataContent slot, whichever has\na value.  If both are present, only the textContent slot is returned.\")", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "GET_CONTENT", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD SET-CONTENT ((OBJ XMLObject) (CONTENT STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Sets either the textContent or cdataContent slot, depending on\nwhether `CONTENT' needs to be encoded as CDATA or not.\")", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "SET_CONTENT", new java.lang.Class [] {Native.find_java_class("java.lang.String")})), null);
          Stella.defineFunctionObject("STARTUP-XML-OBJECT", "(DEFUN STARTUP-XML-OBJECT () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.objects.xml_objects._StartupXmlObject", "STARTUP_XML_OBJECT", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(XmlObjects.SYM_XML_OBJECTS_STARTUP_XML_OBJECT);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, edu.isi.webtools.http.Http.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupXmlObject"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("XML-OBJECTS")))));
          Stella.defineGlobalVariableObject("(DEFGLOBAL *NAMESPACE-PREFIX-URI-TABLE* PROPERTY-LIST (NEW PROPERTY-LIST) :DOCUMENTATION \"Property list associating module names (namespace prefixes) with namespace uris.\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *NAMESPACE-URI-PREFIX-TABLE* PROPERTY-LIST (NEW PROPERTY-LIST) :DOCUMENTATION \"Property list associating namespace uris with module names.\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *INVISIBLE-NAMESPACES-ON-OUTPUT* CONS NIL :DOCUMENTATION \"List of Namespaces which should not be output during xml generation.  \n   Should be used in conjuction with *SUPRESS-NAMESPACES?*\")", null);
        }

      } finally {
        Stella.$CONTEXT$.set(OLD_$CONTEXT$_000);
        Stella.$MODULE$.set(OLD_$MODULE$_000);
      }
    }
  }

}
