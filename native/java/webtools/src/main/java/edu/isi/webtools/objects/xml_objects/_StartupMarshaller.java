//  -*- Mode: Java -*-
//
// _StartupMarshaller.java

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

public class _StartupMarshaller {
  static void HELP_STARTUP_MARSHALLER1() {
    {
      XmlObjects.SGT_STELLA_CONS = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("CONS", Stella.getStellaModule("/STELLA", true), 1)));
      XmlObjects.SGT_XML_OBJECTS_XMLObject = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("XMLObject", null, 1)));
      XmlObjects.SGT_XML_OBJECTS_ID_PARENT_STRUCT = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("ID-PARENT-STRUCT", null, 1)));
      XmlObjects.SYM_XML_OBJECTS_id = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("id", null, 0)));
      XmlObjects.SYM_XML_OBJECTS_parents = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("parents", null, 0)));
      XmlObjects.SGT_STELLA_XML_ELEMENT = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("XML-ELEMENT", Stella.getStellaModule("/STELLA", true), 1)));
      XmlObjects.SGT_STELLA_STRING = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("STRING", Stella.getStellaModule("/STELLA", true), 1)));
      XmlObjects.SGT_STELLA_LIST = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("LIST", Stella.getStellaModule("/STELLA", true), 1)));
      XmlObjects.SYM_XML_OBJECTS_ENCODING_SCHEME = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("ENCODING-SCHEME", null, 0)));
      XmlObjects.KWD_BASE64 = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("BASE64", null, 2)));
      XmlObjects.KWD_PLAIN = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("PLAIN", null, 2)));
      XmlObjects.SGT_XML_OBJECTS_A = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("A", null, 1)));
      XmlObjects.SYM_XML_OBJECTS_b = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("b", null, 0)));
      XmlObjects.SYM_XML_OBJECTS_c = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("c", null, 0)));
      XmlObjects.SGT_XML_OBJECTS_B = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("B", null, 1)));
      XmlObjects.SYM_XML_OBJECTS_d = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("d", null, 0)));
      XmlObjects.SGT_XML_OBJECTS_C = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("C", null, 1)));
      XmlObjects.SYM_XML_OBJECTS_e = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("e", null, 0)));
      XmlObjects.SGT_XML_OBJECTS_D = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("D", null, 1)));
      XmlObjects.SYM_XML_OBJECTS_f = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("f", null, 0)));
      XmlObjects.SGT_XML_OBJECTS_E = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("E", null, 1)));
      XmlObjects.SGT_XML_OBJECTS_F = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("F", null, 1)));
      XmlObjects.SYM_XML_OBJECTS_STARTUP_MARSHALLER = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-MARSHALLER", null, 0)));
    }
  }

  static void HELP_STARTUP_MARSHALLER2() {
    {
      { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("ID-PARENT-STRUCT", "(DEFCLASS ID-PARENT-STRUCT (OBJECT) :PUBLIC-SLOTS ((id :TYPE INTEGER) (parents :TYPE (LIST OF XMLObject))))");

        renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.objects.xml_objects.IdParentStruct", "NEW_ID_PARENT_STRUCT", new java.lang.Class [] {});
        renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.objects.xml_objects.IdParentStruct", "ACCESS_ID_PARENT_STRUCT_SLOT_VALUE", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.IdParentStruct"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
      }
      { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("A", "(DEFCLASS A (XMLObject) :PUBLIC-SLOTS ((b :TYPE B) (c :TYPE C)))");

        renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.objects.xml_objects.A", "NEW_A", new java.lang.Class [] {});
        renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.objects.xml_objects.A", "ACCESS_A_SLOT_VALUE", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.A"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
      }
      { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("B", "(DEFCLASS B (XMLObject) :PUBLIC-SLOTS ((d :TYPE D)))");

        renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.objects.xml_objects.B", "NEW_B", new java.lang.Class [] {});
        renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.objects.xml_objects.B", "ACCESS_B_SLOT_VALUE", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.B"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
      }
      { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("C", "(DEFCLASS C (XMLObject) :PUBLIC-SLOTS ((d :TYPE D) (e :TYPE E)))");

        renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.objects.xml_objects.C", "NEW_C", new java.lang.Class [] {});
        renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.objects.xml_objects.C", "ACCESS_C_SLOT_VALUE", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.C"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
      }
      { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("D", "(DEFCLASS D (XMLObject) :PUBLIC-SLOTS ((f :TYPE F)))");

        renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.objects.xml_objects.D", "NEW_D", new java.lang.Class [] {});
        renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.objects.xml_objects.D", "ACCESS_D_SLOT_VALUE", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.D"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
      }
      { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("E", "(DEFCLASS E (XMLObject) :PUBLIC-SLOTS ((f :TYPE F)))");

        renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.objects.xml_objects.E", "NEW_E", new java.lang.Class [] {});
        renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.objects.xml_objects.E", "ACCESS_E_SLOT_VALUE", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.E"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
      }
      { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("F", "(DEFCLASS F (XMLObject))");

        renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.objects.xml_objects.F", "NEW_F", new java.lang.Class [] {});
      }
    }
  }

  static void HELP_STARTUP_MARSHALLER3() {
    {
      Stella.defineFunctionObject("SLOT-VALUE-IS-NULL?", "(DEFUN (SLOT-VALUE-IS-NULL? BOOLEAN) ((parentObject XMLObject) (slot SLOT)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "SLOT_VALUE_IS_NULLP", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.Slot")}), null);
      Stella.defineFunctionObject("SLOT-VALUE-IS-NULL-OR-EMPTY?", "(DEFUN (SLOT-VALUE-IS-NULL-OR-EMPTY? BOOLEAN) ((parentObject XMLObject) (slot SLOT)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "SLOT_VALUE_IS_NULL_OR_EMPTYP", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.Slot")}), null);
      Stella.defineMethodObject("(DEFMETHOD (TO-XML-STRING STRING) ((object XMLObject)) :PUBLIC? TRUE :DOCUMENTATION \"Convert `object' into it's XML Representation as a string\")", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "TO_XML_STRING", new java.lang.Class [] {})), null);
      Stella.defineMethodObject("(DEFMETHOD TO-XML-STREAM ((object XMLObject) (out OUTPUT-STREAM)) :PUBLIC? TRUE :DOCUMENTATION \"Write `object' in  it's XML Representation to `out'.\")", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "TO_XML_STREAM", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.OutputStream")})), null);
      Stella.defineMethodObject("(DEFMETHOD (TO-XML CONS) ((object XMLObject) (namespaceStack (CONS OF STRING-WRAPPER))))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "TO_XML", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")})), null);
      Stella.defineFunctionObject("GET-NAMESPACE-PREFIX", "(DEFUN (GET-NAMESPACE-PREFIX STRING) ((object XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "GET_NAMESPACE_PREFIX", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("GET-NAMESPACE-URI", "(DEFUN (GET-NAMESPACE-URI STRING-WRAPPER) ((namespacePrefix STRING)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "GET_NAMESPACE_URI", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
      Stella.defineFunctionObject("MAKE-CONTENT-EXPRESSION", "(DEFUN (MAKE-CONTENT-EXPRESSION CONS) ((object XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "MAKE_CONTENT_EXPRESSION", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("MAKE-ELEMENT-TAG", "(DEFUN (MAKE-ELEMENT-TAG XML-ELEMENT) ((object XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "MAKE_ELEMENT_TAG", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("MAKE-NAMESPACE-ATTRIBUTE", "(DEFUN (MAKE-NAMESPACE-ATTRIBUTE XML-ATTRIBUTE) ((namespaceName STRING)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "MAKE_NAMESPACE_ATTRIBUTE", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
      Stella.defineFunctionObject("GET-ATTRIBUTE-VALUE-NAMESPACE-NAME", "(DEFUN (GET-ATTRIBUTE-VALUE-NAMESPACE-NAME STRING-WRAPPER) ((parentObject XMLObject) (slot STORAGE-SLOT)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "GET_ATTRIBUTE_VALUE_NAMESPACE_NAME", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.StorageSlot")}), null);
      Stella.defineFunctionObject("GET-VALUE-NAMESPACE-PREFIX", "(DEFUN (GET-VALUE-NAMESPACE-PREFIX STRING) ((valueString STRING)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "GET_VALUE_NAMESPACE_PREFIX", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
      Stella.defineFunctionObject("MAKE-REVERSED-ATTRIBUTE", "(DEFUN (MAKE-REVERSED-ATTRIBUTE CONS) ((parentObject XMLObject) (slot STORAGE-SLOT)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "MAKE_REVERSED_ATTRIBUTE", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.StorageSlot")}), null);
      Stella.defineFunctionObject("MAKE-ELEMENT", "(DEFUN (MAKE-ELEMENT CONS) ((parentObject XMLObject) (slot SLOT) (namespaceStack CONS)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "MAKE_ELEMENT", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.Slot"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("MAKE-COLLECTION", "(DEFUN (MAKE-COLLECTION CONS) ((parentObject XMLObject) (slot SLOT) (namespaceStack CONS)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "MAKE_COLLECTION", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.Slot"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("FROM-XML-STRING", "(DEFUN (FROM-XML-STRING XMLObject) ((xmlString STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Convert XML into an object.\")", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "FROM_XML_STRING", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
      Stella.defineFunctionObject("FROM-XML-STREAM", "(DEFUN (FROM-XML-STREAM XMLObject) ((in INPUT-STREAM)) :PUBLIC? TRUE :DOCUMENTATION \"Convert XML into an object.\")", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "FROM_XML_STREAM", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.InputStream")}), null);
      Stella.defineFunctionObject("FROM-XML", "(DEFUN (FROM-XML XMLObject) ((expr CONS)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "FROM_XML", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("SET-ELEMENTS", "(DEFUN SET-ELEMENTS ((object XMLObject) (elementExprs CONS)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "SET_ELEMENTS", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("SET-ATTRIBUTES", "(DEFUN SET-ATTRIBUTES ((object XMLObject) (attributeExprs CONS)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "SET_ATTRIBUTES", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("SET-COLLECTIONS", "(DEFUN SET-COLLECTIONS ((object XMLObject) (elementExprs CONS)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "SET_COLLECTIONS", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("GET-MAPPED-SLOTS", "(DEFUN (GET-MAPPED-SLOTS (LIST OF SLOT)) ((object XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "GET_MAPPED_SLOTS", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("SLOT-REPRESENTS-TAG?", "(DEFUN (SLOT-REPRESENTS-TAG? BOOLEAN) ((slot SLOT) (tag XML-OBJECT) (useType? BOOLEAN) (useParametricType? BOOLEAN)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "SLOT_REPRESENTS_TAGP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Slot"), Native.find_java_class("edu.isi.stella.XmlObject"), java.lang.Boolean.TYPE, java.lang.Boolean.TYPE}), null);
      Stella.defineFunctionObject("LOOKUP-ELEMENT-SLOT", "(DEFUN (LOOKUP-ELEMENT-SLOT STORAGE-SLOT) ((object XMLObject) (elementExpr CONS)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "LOOKUP_ELEMENT_SLOT", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("LOOKUP-ATTRIBUTE-SLOT", "(DEFUN (LOOKUP-ATTRIBUTE-SLOT STORAGE-SLOT) ((object XMLObject) (attribute XML-ATTRIBUTE)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "LOOKUP_ATTRIBUTE_SLOT", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.XmlAttribute")}), null);
      Stella.defineFunctionObject("LOOKUP-COLLECTION-SLOT", "(DEFUN (LOOKUP-COLLECTION-SLOT STORAGE-SLOT) ((object XMLObject) (elementExpr CONS)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "LOOKUP_COLLECTION_SLOT", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("LOOKUP-CONTENT-SLOT", "(DEFUN (LOOKUP-CONTENT-SLOT STORAGE-SLOT) ((object XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "LOOKUP_CONTENT_SLOT", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("RESET-MULTIREF-TABLES", "(DEFUN RESET-MULTIREF-TABLES ())", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "RESET_MULTIREF_TABLES", new java.lang.Class [] {}), null);
      Stella.defineFunctionObject("GET-NEXT-ID", "(DEFUN (GET-NEXT-ID INTEGER) ())", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "GET_NEXT_ID", new java.lang.Class [] {}), null);
      Stella.defineFunctionObject("INSERT-NODE-PARENTS-TABLE", "(DEFUN (INSERT-NODE-PARENTS-TABLE BOOLEAN) ((node XMLObject) (parent XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "INSERT_NODE_PARENTS_TABLE", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("INSERT-NODE-ID-PARENTS-TABLE", "(DEFUN INSERT-NODE-ID-PARENTS-TABLE ((node XMLObject) (parent XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "INSERT_NODE_ID_PARENTS_TABLE", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("GET-CHILDREN", "(DEFUN (GET-CHILDREN (CONS OF XMLObject)) ((node XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "GET_CHILDREN", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("POPULATE-NODE-PARENTS-TABLE", "(DEFUN POPULATE-NODE-PARENTS-TABLE ((node XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "POPULATE_NODE_PARENTS_TABLE", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("HELP-POPULATE-NODE-PARENTS-TABLE", "(DEFUN HELP-POPULATE-NODE-PARENTS-TABLE ((node XMLObject) (parent XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "HELP_POPULATE_NODE_PARENTS_TABLE", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("CREATE-NODE-ID-PARENT-TABLE", "(DEFUN CREATE-NODE-ID-PARENT-TABLE ())", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "CREATE_NODE_ID_PARENT_TABLE", new java.lang.Class [] {}), null);
      Stella.defineFunctionObject("SIMULATE-MULTIREF-OUTPUT", "(DEFUN SIMULATE-MULTIREF-OUTPUT ((node XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "SIMULATE_MULTIREF_OUTPUT", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("FIRST-PARENT-FOR-MULTIREF-NODE?", "(DEFUN (FIRST-PARENT-FOR-MULTIREF-NODE? BOOLEAN) ((node XMLObject) (parent XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "FIRST_PARENT_FOR_MULTIREF_NODEP", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("NTH-PARENT-FOR-MULTIREF-NODE?", "(DEFUN (NTH-PARENT-FOR-MULTIREF-NODE? BOOLEAN) ((node XMLObject) (parent XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "NTH_PARENT_FOR_MULTIREF_NODEP", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("GET-NODE-ID", "(DEFUN (GET-NODE-ID INTEGER) ((node XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "GET_NODE_ID", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("HELP-SIMULATE-MULTIREF-OUTPUT", "(DEFUN HELP-SIMULATE-MULTIREF-OUTPUT ((node XMLObject) (parent XMLObject) (indent INTEGER)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "HELP_SIMULATE_MULTIREF_OUTPUT", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), java.lang.Integer.TYPE}), null);
      Stella.defineFunctionObject("SLOT-BASE-AND-PARAMETER-TYPE", "(DEFUN (SLOT-BASE-AND-PARAMETER-TYPE TYPE TYPE-SPEC) ((slot SLOT)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "SLOT_BASE_AND_PARAMETER_TYPE", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Slot"), Native.find_java_class("[Ljava.lang.Object;")}), null);
      Stella.defineFunctionObject("PARSE-XML-FROM-STREAM", "(DEFUN (PARSE-XML-FROM-STREAM CONS) ((in INPUT-STREAM) (skipFrontmatter? BOOLEAN)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "PARSE_XML_FROM_STREAM", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.InputStream"), java.lang.Boolean.TYPE}), null);
      Stella.defineFunctionObject("PARSE-XML", "(DEFUN (PARSE-XML CONS) ((string STRING) (skipFrontmatter? BOOLEAN)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "PARSE_XML", new java.lang.Class [] {Native.find_java_class("java.lang.String"), java.lang.Boolean.TYPE}), null);
      Stella.defineFunctionObject("FIND-SLOT", "(DEFUN (FIND-SLOT SLOT) ((name STRING) (slots (LIST OF SLOT)) (useParametricType? BOOLEAN) (useType? BOOLEAN)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "FIND_SLOT", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.List"), java.lang.Boolean.TYPE, java.lang.Boolean.TYPE}), null);
      Stella.defineFunctionObject("GET-ELEMENT-NAME-FROM-EXPR", "(DEFUN (GET-ELEMENT-NAME-FROM-EXPR STRING-WRAPPER) ((expression CONS)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "GET_ELEMENT_NAME_FROM_EXPR", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("GET-ELEMENT-NAMESPACE-PREFIX-FROM-EXPR", "(DEFUN (GET-ELEMENT-NAMESPACE-PREFIX-FROM-EXPR STRING-WRAPPER) ((expression CONS)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "GET_ELEMENT_NAMESPACE_PREFIX_FROM_EXPR", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("GET-ELEMENT-NAMESPACE-URI-FROM-EXPR", "(DEFUN (GET-ELEMENT-NAMESPACE-URI-FROM-EXPR STRING-WRAPPER) ((expression CONS)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "GET_ELEMENT_NAMESPACE_URI_FROM_EXPR", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("GET-ELEMENT-NAME-FROM-OBJECT", "(DEFUN (GET-ELEMENT-NAME-FROM-OBJECT STRING) ((object XMLObject)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "GET_ELEMENT_NAME_FROM_OBJECT", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject")}), null);
      Stella.defineFunctionObject("STRINGIFY-XML", "(DEFUN (STRINGIFY-XML STRING) ((expression CONS)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "STRINGIFY_XML", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}), null);
      Stella.defineFunctionObject("LOOKUP-OBJECT-CREATION-MODULE", "(DEFUN (LOOKUP-OBJECT-CREATION-MODULE MODULE) ((namespacePrefix STRING)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "LOOKUP_OBJECT_CREATION_MODULE", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
      Stella.defineFunctionObject("MAKE-XML-OBJECT", "(DEFUN (MAKE-XML-OBJECT OBJECT) ((className STRING) (namespacePrefix STRING) (namespaceURI STRING)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "MAKE_XML_OBJECT", new java.lang.Class [] {Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String"), Native.find_java_class("java.lang.String")}), null);
      Stella.defineFunctionObject("ATTRIBUTE-SLOT?", "(DEFUN (ATTRIBUTE-SLOT? BOOLEAN) ((slot SLOT)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "ATTRIBUTE_SLOTP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Slot")}), null);
      Stella.defineFunctionObject("ELEMENT-SLOT?", "(DEFUN (ELEMENT-SLOT? BOOLEAN) ((slot SLOT)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "ELEMENT_SLOTP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Slot")}), null);
      Stella.defineFunctionObject("COLLECTION-SLOT?", "(DEFUN (COLLECTION-SLOT? BOOLEAN) ((slot SLOT)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "COLLECTION_SLOTP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Slot")}), null);
      Stella.defineFunctionObject("GET-OBJECT-SLOT-VALUE", "(DEFUN (GET-OBJECT-SLOT-VALUE OBJECT) ((object XMLObject) (slot STORAGE-SLOT)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "GET_OBJECT_SLOT_VALUE", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.StorageSlot")}), null);
      Stella.defineFunctionObject("SET-OBJECT-SLOT-VALUE", "(DEFUN SET-OBJECT-SLOT-VALUE ((object XMLObject) (slot STORAGE-SLOT) (value OBJECT)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "SET_OBJECT_SLOT_VALUE", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.StorageSlot"), Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
      Stella.defineFunctionObject("SET-COLLECTION-SLOT-VALUE", "(DEFUN SET-COLLECTION-SLOT-VALUE ((object XMLObject) (slot STORAGE-SLOT) (value OBJECT)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XMLObject", "SET_COLLECTION_SLOT_VALUE", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.objects.xml_objects.XMLObject"), Native.find_java_class("edu.isi.stella.StorageSlot"), Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
      Stella.defineFunctionObject("DECODE-SLOT-VALUE", "(DEFUN (DECODE-SLOT-VALUE OBJECT) ((slot STORAGE-SLOT) (value OBJECT)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "DECODE_SLOT_VALUE", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StorageSlot"), Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
      Stella.defineFunctionObject("ENCODE-SLOT-VALUE", "(DEFUN (ENCODE-SLOT-VALUE OBJECT) ((slot STORAGE-SLOT) (value OBJECT)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "ENCODE_SLOT_VALUE", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StorageSlot"), Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
      Stella.defineFunctionObject("INITIALIZE-BASE64-DECODING-TABLE", "(DEFUN (INITIALIZE-BASE64-DECODING-TABLE (ARRAY () OF INTEGER)) ())", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "INITIALIZE_BASE64_DECODING_TABLE", new java.lang.Class [] {}), null);
    }
  }

  public static void STARTUP_MARSHALLER() {
    { Object OLD_$MODULE$_000 = Stella.$MODULE$.get();
      Object OLD_$CONTEXT$_000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/STELLA/XML-OBJECTS", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          _StartupMarshaller.HELP_STARTUP_MARSHALLER1();
        }
        if (Stella.currentStartupTimePhaseP(4)) {
          XmlObjects.$SUPRESS_NAMESPACESp$.setDefaultValue(new Boolean(false));
          XmlObjects.$NODE_PARENTS_TABLE$ = PropertyList.newPropertyList();
          XmlObjects.$NODE_ID_PARENTS_TABLE$ = HashTable.newHashTable();
          XmlObjects.$DEFAULT_XML_OBJECT_MODULE$.setDefaultValue(null);
          XmlObjects.$BASE64_DECODING_TABLE$ = XmlObjects.INITIALIZE_BASE64_DECODING_TABLE();
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          _StartupMarshaller.HELP_STARTUP_MARSHALLER2();
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          _StartupMarshaller.HELP_STARTUP_MARSHALLER3();
          Stella.defineFunctionObject("BASE64-ENCODE-STRING", "(DEFUN (BASE64-ENCODE-STRING STRING) ((input STRING)) :DOCUMENTATION \"Base-64 encode `input' and return the result.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "BASE64_ENCODE_STRING", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("BASE64-DECODE-STRING", "(DEFUN (BASE64-DECODE-STRING STRING) ((input STRING)) :DOCUMENTATION \"Base-64 decode `input' and return the result.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "BASE64_DECODE_STRING", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("READ-XML", "(DEFUN (READ-XML OBJECT) ((xmlString STRING)))", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "READ_XML", new java.lang.Class [] {Native.find_java_class("java.lang.String")}), null);
          Stella.defineFunctionObject("MULTIREF-TEST1", "(DEFUN MULTIREF-TEST1 ())", Native.find_java_method("edu.isi.webtools.objects.xml_objects.XmlObjects", "MULTIREF_TEST1", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("STARTUP-MARSHALLER", "(DEFUN STARTUP-MARSHALLER () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.objects.xml_objects._StartupMarshaller", "STARTUP_MARSHALLER", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(XmlObjects.SYM_XML_OBJECTS_STARTUP_MARSHALLER);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, edu.isi.webtools.http.Http.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupMarshaller"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("XML-OBJECTS")))));
          Stella.defineGlobalVariableObject("(DEFSPECIAL *SUPRESS-NAMESPACES?* BOOLEAN FALSE :DOCUMENTATION \"If TRUE, don't output namespace declarations and prefixes\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *NODE-PARENTS-TABLE* (PROPERTY-LIST OF XMLObject (LIST OF XMLObject)) (NEW PROPERTY-LIST))", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *NODE-ID-PARENTS-TABLE* (HASH-TABLE OF XMLObject ID-PARENT-STRUCT) (NEW HASH-TABLE))", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *CURRENT-ID* INTEGER 0)", null);
          Stella.defineGlobalVariableObject("(DEFSPECIAL *DEFAULT-XML-OBJECT-MODULE* MODULE NULL :PUBLIC? TRUE :DOCUMENTATION \"Default module for the creation of XMLObject instances when converting\nfrom XML to the object representation.  Used unless there is a more\nspecific namespace-mapping defined.\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *BASE64-ENCODING-TABLE* STRING \"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\")", null);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *BASE64-DECODING-TABLE* (ARRAY () OF INTEGER) (INITIALIZE-BASE64-DECODING-TABLE))", null);
        }

      } finally {
        Stella.$CONTEXT$.set(OLD_$CONTEXT$_000);
        Stella.$MODULE$.set(OLD_$MODULE$_000);
      }
    }
  }

}
