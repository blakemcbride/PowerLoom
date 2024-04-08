//  -*- Mode: Java -*-
//
// XmlObjects.java

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

public class XmlObjects {
  /** Property list associating module names (namespace prefixes) with namespace uris.
   */
  public static PropertyList $NAMESPACE_PREFIX_URI_TABLE$ = null;

  /** Property list associating namespace uris with module names.
   */
  public static PropertyList $NAMESPACE_URI_PREFIX_TABLE$ = null;

  /** List of Namespaces which should not be output during xml generation.  
   *    Should be used in conjuction with *SUPRESS-NAMESPACES?*
   */
  public static Cons $INVISIBLE_NAMESPACES_ON_OUTPUT$ = null;

  public static Keyword KWD_INVISIBLE_ON_OUTPUTp = null;

  public static Symbol SYM_STELLA_PUSHQ = null;

  public static Symbol SYM_XML_OBJECTS_$INVISIBLE_NAMESPACES_ON_OUTPUT$ = null;

  public static Symbol SYM_STELLA_STARTUP_TIME_PROGN = null;

  public static Symbol SYM_STELLA_INSERT_AT = null;

  public static Symbol SYM_XML_OBJECTS_$NAMESPACE_PREFIX_URI_TABLE$ = null;

  public static Symbol SYM_XML_OBJECTS_$NAMESPACE_URI_PREFIX_TABLE$ = null;

  public static Symbol SYM_XML_OBJECTS_textContent = null;

  public static Symbol SYM_XML_OBJECTS_cdataContent = null;

  public static Symbol SYM_XML_OBJECTS_STARTUP_XML_OBJECT = null;

  /** If TRUE, don't output namespace declarations and prefixes
   */
  public final static StellaSpecialVariable $SUPRESS_NAMESPACESp$ = new StellaSpecialVariable();

  public static Surrogate SGT_STELLA_CONS = null;

  public static Surrogate SGT_XML_OBJECTS_XMLObject = null;

  public static Surrogate SGT_XML_OBJECTS_ID_PARENT_STRUCT = null;

  public static Symbol SYM_XML_OBJECTS_id = null;

  public static Symbol SYM_XML_OBJECTS_parents = null;

  public static PropertyList $NODE_PARENTS_TABLE$ = null;

  public static HashTable $NODE_ID_PARENTS_TABLE$ = null;

  public static int $CURRENT_ID$ = 0;

  public static Surrogate SGT_STELLA_XML_ELEMENT = null;

  /** Default module for the creation of XMLObject instances when converting
   * from XML to the object representation.  Used unless there is a more
   * specific namespace-mapping defined.
   */
  public final static StellaSpecialVariable $DEFAULT_XML_OBJECT_MODULE$ = new StellaSpecialVariable();

  public static Surrogate SGT_STELLA_STRING = null;

  public static Surrogate SGT_STELLA_LIST = null;

  public static Symbol SYM_XML_OBJECTS_ENCODING_SCHEME = null;

  public static Keyword KWD_BASE64 = null;

  public static Keyword KWD_PLAIN = null;

  public static String $BASE64_ENCODING_TABLE$ = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

  public static int[] $BASE64_DECODING_TABLE$ = null;

  public static Surrogate SGT_XML_OBJECTS_A = null;

  public static Symbol SYM_XML_OBJECTS_b = null;

  public static Symbol SYM_XML_OBJECTS_c = null;

  public static Surrogate SGT_XML_OBJECTS_B = null;

  public static Symbol SYM_XML_OBJECTS_d = null;

  public static Surrogate SGT_XML_OBJECTS_C = null;

  public static Symbol SYM_XML_OBJECTS_e = null;

  public static Surrogate SGT_XML_OBJECTS_D = null;

  public static Symbol SYM_XML_OBJECTS_f = null;

  public static Surrogate SGT_XML_OBJECTS_E = null;

  public static Surrogate SGT_XML_OBJECTS_F = null;

  public static Symbol SYM_XML_OBJECTS_STARTUP_MARSHALLER = null;

  public static Stella_Object DEFNAMESPACE(Cons body) {
    { Stella_Object namespaceURI = body.value;
      String namespaceName = ((Module)(Stella.$MODULE$.get())).moduleName;
      Cons bodyWithHeader = Cons.cons(null, body);

      { PropertyList SELF_000 = PropertyList.newPropertyList();

        SELF_000.thePlist = Cons.extractOptions(bodyWithHeader, null);
        { PropertyList options = SELF_000;
          Symbol invisibleP = ((Symbol)(options.lookup(XmlObjects.KWD_INVISIBLE_ON_OUTPUTp)));
          Cons invisibleForm = (((invisibleP != null) &&
              Stella.stringEqualP(invisibleP.symbolName, "TRUE")) ? Cons.cons(Cons.list$(Cons.cons(XmlObjects.SYM_STELLA_PUSHQ, Cons.cons(XmlObjects.SYM_XML_OBJECTS_$INVISIBLE_NAMESPACES_ON_OUTPUT$, Cons.cons(StringWrapper.wrapString(namespaceName), Cons.cons(Stella.NIL, Stella.NIL))))), Stella.NIL) : Stella.NIL);

          return (Cons.list$(Cons.cons(XmlObjects.SYM_STELLA_STARTUP_TIME_PROGN, Cons.cons(Cons.list$(Cons.cons(XmlObjects.SYM_STELLA_INSERT_AT, Cons.cons(XmlObjects.SYM_XML_OBJECTS_$NAMESPACE_PREFIX_URI_TABLE$, Cons.cons(StringWrapper.wrapString(namespaceName), Cons.cons(Cons.cons(namespaceURI, Stella.NIL), Stella.NIL))))), Cons.cons(Cons.list$(Cons.cons(XmlObjects.SYM_STELLA_INSERT_AT, Cons.cons(XmlObjects.SYM_XML_OBJECTS_$NAMESPACE_URI_PREFIX_TABLE$, Cons.cons(namespaceURI, Cons.cons(Cons.cons(StringWrapper.wrapString(namespaceName), Stella.NIL), Stella.NIL))))), Cons.cons(invisibleForm.concatenate(Stella.NIL, Stella.NIL), Stella.NIL))))));
        }
      }
    }
  }

  public static StringWrapper GET_NAMESPACE_URI(String namespacePrefix) {
    { Stella_Object uri = XmlObjects.$NAMESPACE_PREFIX_URI_TABLE$.lookup(StringWrapper.wrapString(namespacePrefix));

      if (uri != null) {
        return (((StringWrapper)(uri)));
      }
      else {
        return (null);
      }
    }
  }

  public static XmlAttribute MAKE_NAMESPACE_ATTRIBUTE(String namespaceName) {
    { XmlGlobalAttribute SELF_000 = XmlGlobalAttribute.newXmlGlobalAttribute();

      SELF_000.surfaceForm = "xmlns:" + namespaceName;
      SELF_000.name = namespaceName;
      SELF_000.namespaceName = "xmlns";
      { XmlGlobalAttribute VALUE_000 = SELF_000;

        return (VALUE_000);
      }
    }
  }

  public static String GET_VALUE_NAMESPACE_PREFIX(String valueString) {
    { int colonPos = Native.stringSearch(valueString, ":", 0);

      if (colonPos != Stella.NULL_INTEGER) {
        return (Native.string_subsequence(valueString, 0, colonPos));
      }
      return (null);
    }
  }

  /** Convert XML into an object.
   * @param xmlString
   * @return XMLObject
   */
  public static XMLObject FROM_XML_STRING(String xmlString) {
    return (XmlObjects.FROM_XML(XmlObjects.PARSE_XML(xmlString, true)));
  }

  /** Convert XML into an object.
   * @param in
   * @return XMLObject
   */
  public static XMLObject FROM_XML_STREAM(InputStream in) {
    return (XmlObjects.FROM_XML(XmlObjects.PARSE_XML_FROM_STREAM(in, true)));
  }

  public static XMLObject FROM_XML(Cons expr) {
    { StringWrapper elementName = XmlObjects.GET_ELEMENT_NAME_FROM_EXPR(expr);
      StringWrapper elementNamespaceName = XmlObjects.GET_ELEMENT_NAMESPACE_PREFIX_FROM_EXPR(expr);
      StringWrapper elementNamespaceURI = XmlObjects.GET_ELEMENT_NAMESPACE_URI_FROM_EXPR(expr);
      Cons attributeExpressions = ((Cons)(expr.rest.value));
      Cons elementExpressions = expr.rest.rest;
      Stella_Object theObject = XmlObjects.MAKE_XML_OBJECT(elementName.wrapperValue, elementNamespaceName.wrapperValue, elementNamespaceURI.wrapperValue);

      XMLObject.SET_ATTRIBUTES(((XMLObject)(theObject)), attributeExpressions);
      XMLObject.SET_ELEMENTS(((XMLObject)(theObject)), elementExpressions);
      XMLObject.SET_COLLECTIONS(((XMLObject)(theObject)), elementExpressions);
      return (((XMLObject)(theObject)));
    }
  }

  public static boolean SLOT_REPRESENTS_TAGP(Slot slot, XmlObject tag, boolean useTypeP, boolean useParametricTypeP) {
    { String name = tag.name;

      if (Stella.stringEqlP(name, slot.slotName.symbolName)) {
        return (true);
      }
      if (useTypeP ||
          useParametricTypeP) {
        { Surrogate slotType = null;
          StandardObject slotParametricType = null;

          { Object [] caller_MV_returnarray = new Object[1];

            slotType = XmlObjects.SLOT_BASE_AND_PARAMETER_TYPE(slot, caller_MV_returnarray);
            slotParametricType = ((StandardObject)(caller_MV_returnarray[0]));
          }
          if (useTypeP &&
              Stella.stringEqlP(name, slotType.symbolName)) {
            return (true);
          }
          if (useParametricTypeP &&
              Stella.stringEqlP(name, ((GeneralizedSymbol)(slotParametricType)).symbolName)) {
            return (true);
          }
        }
      }
      return (false);
    }
  }

  public static void RESET_MULTIREF_TABLES() {
    XmlObjects.$NODE_PARENTS_TABLE$ = PropertyList.newPropertyList();
    XmlObjects.$NODE_ID_PARENTS_TABLE$ = HashTable.newHashTable();
    XmlObjects.$CURRENT_ID$ = 0;
  }

  public static int GET_NEXT_ID() {
    { int currentID = XmlObjects.$CURRENT_ID$;

      XmlObjects.$CURRENT_ID$ = XmlObjects.$CURRENT_ID$ + 1;
      return (currentID);
    }
  }

  public static void CREATE_NODE_ID_PARENT_TABLE() {
    { XMLObject node = null;
      List parents = null;
      Cons ITER_000 = XmlObjects.$NODE_PARENTS_TABLE$.thePlist;

      for (;!(ITER_000 == Stella.NIL); ITER_000 = ITER_000.rest.rest) {
        node = ((XMLObject)(ITER_000.value));
        parents = ((List)(ITER_000.rest.value));
        {
          Stella.STANDARD_OUTPUT.nativeStream.println("node = " + node + ", parents = " + parents);
          if (parents.length() > 1) {
            { XMLObject parent = null;
              Cons ITER_001 = parents.theConsList;

              for (;!(ITER_001 == Stella.NIL); ITER_001 = ITER_001.rest) {
                parent = ((XMLObject)(ITER_001.value));
                XMLObject.INSERT_NODE_ID_PARENTS_TABLE(node, parent);
              }
            }
          }
        }
      }
    }
  }

  public static Surrogate SLOT_BASE_AND_PARAMETER_TYPE(Slot slot, Object [] MV_returnarray) {
    { StandardObject typeSpec = slot.typeSpecifier();

      { Surrogate TEST_VALUE_000 = Stella_Object.safePrimaryType(typeSpec);

        if (Surrogate.subtypeOfSurrogateP(TEST_VALUE_000)) {
          { Surrogate typeSpec_000 = ((Surrogate)(typeSpec));

            { Surrogate _return_temp = typeSpec_000;

              MV_returnarray[0] = null;
              return (_return_temp);
            }
          }
        }
        else if (Surrogate.subtypeOfParametricTypeSpecifierP(TEST_VALUE_000)) {
          { ParametricTypeSpecifier typeSpec_000 = ((ParametricTypeSpecifier)(typeSpec));

            { Surrogate _return_temp = typeSpec_000.specifierBaseType;

              MV_returnarray[0] = ((StandardObject)(typeSpec_000.specifierParameterTypes.first()));
              return (_return_temp);
            }
          }
        }
        else {
          { Surrogate _return_temp = slot.type();

            MV_returnarray[0] = null;
            return (_return_temp);
          }
        }
      }
    }
  }

  public static Cons PARSE_XML_FROM_STREAM(InputStream in, boolean skipFrontmatterP) {
    { Stella_Object item = null;
      XmlExpressionIterator ITER_000 = InputStream.xmlExpressions(in, null);

      while (ITER_000.nextP()) {
        item = ITER_000.value;
        if ((!skipFrontmatterP) ||
            ((Stella_Object.isaP(item, XmlObjects.SGT_STELLA_CONS) &&
            Stella_Object.isaP(((Cons)(item)).value, XmlObjects.SGT_STELLA_XML_ELEMENT)) ||
             (Stella_Object.isaP(item, XmlObjects.SGT_STELLA_CONS) &&
              Stella_Object.xmlCdataP(((Cons)(item)).value)))) {
          return (((Cons)(item)));
        }
      }
    }
    return (Stella.NIL);
  }

  public static Cons PARSE_XML(String string, boolean skipFrontmatterP) {
    return (XmlObjects.PARSE_XML_FROM_STREAM(InputStringStream.newInputStringStream(string), skipFrontmatterP));
  }

  public static Slot FIND_SLOT(String name, List slots, boolean useParametricTypeP, boolean useTypeP) {
    if (useTypeP &&
        ((slots.length() == 1) &&
         (XmlObjects.SLOT_BASE_AND_PARAMETER_TYPE(((Slot)(slots.first())), new Object[1]) == XmlObjects.SGT_XML_OBJECTS_XMLObject))) {
      return (((Slot)(slots.first())));
    }
    { Slot result = null;

      { Slot slot = null;
        Cons ITER_000 = slots.theConsList;

        LOOP_000 : for (;!(ITER_000 == Stella.NIL); ITER_000 = ITER_000.rest) {
          slot = ((Slot)(ITER_000.value));
          { Surrogate slotType = null;
            StandardObject slotParametricType = null;

            { Object [] caller_MV_returnarray = new Object[1];

              slotType = XmlObjects.SLOT_BASE_AND_PARAMETER_TYPE(slot, caller_MV_returnarray);
              slotParametricType = ((StandardObject)(caller_MV_returnarray[0]));
            }
            if ((useTypeP &&
                Stella.stringEqlP(name, slotType.symbolName)) ||
                ((useParametricTypeP &&
                Stella.stringEqlP(name, ((GeneralizedSymbol)(slotParametricType)).symbolName)) ||
                 Stella.stringEqlP(name, slot.slotName.symbolName))) {
              result = slot;
              break LOOP_000;
            }
          }
        }
      }
      return (result);
    }
  }

  public static StringWrapper GET_ELEMENT_NAME_FROM_EXPR(Cons expression) {
    return (StringWrapper.wrapString(((XmlElement)(expression.value)).name));
  }

  public static StringWrapper GET_ELEMENT_NAMESPACE_PREFIX_FROM_EXPR(Cons expression) {
    { StringWrapper lookupResult = ((StringWrapper)(XmlObjects.$NAMESPACE_URI_PREFIX_TABLE$.lookup(XmlObjects.GET_ELEMENT_NAMESPACE_URI_FROM_EXPR(expression))));

      return (((lookupResult != null) ? lookupResult : Stella.NULL_STRING_WRAPPER));
    }
  }

  public static StringWrapper GET_ELEMENT_NAMESPACE_URI_FROM_EXPR(Cons expression) {
    return (StringWrapper.wrapString(((XmlElement)(expression.value)).namespaceUri));
  }

  public static String STRINGIFY_XML(Cons expression) {
    { OutputStringStream ss = OutputStringStream.newOutputStringStream();

      OutputStream.printXmlExpression(ss, expression, 0);
      return (ss.theStringReader());
    }
  }

  public static Module LOOKUP_OBJECT_CREATION_MODULE(String namespacePrefix) {
    { Module creationModule = null;

      if ((namespacePrefix != null) &&
          (!Stella.stringEqlP(namespacePrefix, ""))) {
        creationModule = ((Module)(Stella.getStellaContext(namespacePrefix, false)));
      }
      if (creationModule == null) {
        if (((Module)(XmlObjects.$DEFAULT_XML_OBJECT_MODULE$.get())) != null) {
          creationModule = ((Module)(XmlObjects.$DEFAULT_XML_OBJECT_MODULE$.get()));
        }
        else {
          creationModule = ((Module)(Stella.$MODULE$.get()));
        }
      }
      return (creationModule);
    }
  }

  public static Stella_Object MAKE_XML_OBJECT(String className, String namespacePrefix, String namespaceURI) {
    namespaceURI = namespaceURI;
    { Surrogate theType = Surrogate.lookupSurrogateInModule(className, XmlObjects.LOOKUP_OBJECT_CREATION_MODULE(namespacePrefix), true);

      if (theType == null) {
        { OutputStringStream STREAM_000 = OutputStringStream.newOutputStringStream();

          STREAM_000.nativeStream.print("Couldn't find a class for `" + className + "' in target module `" + XmlObjects.LOOKUP_OBJECT_CREATION_MODULE(namespacePrefix) + "'");
          throw ((NoSuchObjectException)(NoSuchObjectException.newNoSuchObjectException(STREAM_000.theStringReader()).fillInStackTrace()));
        }
      }
      { Stella_Class theClass = ((Stella_Class)(theType.surrogateValue));
        java.lang.reflect.Method theConstructor = theClass.classConstructorCode;

        return (Stella.apply(theConstructor, Stella.NIL));
      }
    }
  }

  public static boolean ATTRIBUTE_SLOTP(Slot slot) {
    { Surrogate stringType = XmlObjects.SGT_STELLA_STRING;
      Surrogate slotType = slot.type();

      return ((!(slot.slotName == XmlObjects.SYM_XML_OBJECTS_textContent)) &&
          Surrogate.subtypeOfP(slotType, stringType));
    }
  }

  public static boolean ELEMENT_SLOTP(Slot slot) {
    { Surrogate rootXMLType = XmlObjects.SGT_XML_OBJECTS_XMLObject;
      Surrogate slotType = slot.type();

      return (Surrogate.subtypeOfP(slotType, rootXMLType));
    }
  }

  public static boolean COLLECTION_SLOTP(Slot slot) {
    { Surrogate listType = XmlObjects.SGT_STELLA_LIST;
      Surrogate slotType = slot.type();

      return (Surrogate.subtypeOfP(slotType, listType));
    }
  }

  public static Stella_Object DECODE_SLOT_VALUE(StorageSlot slot, Stella_Object value) {
    { Keyword encoding = ((Keyword)(KeyValueList.dynamicSlotValue(slot.dynamicSlots, XmlObjects.SYM_XML_OBJECTS_ENCODING_SCHEME, null)));

      if (encoding != null) {
        if (encoding == XmlObjects.KWD_BASE64) {
          if (Stella_Object.stringP(value)) {
            value = StringWrapper.wrapString(XmlObjects.BASE64_DECODE_STRING(((StringWrapper)(value)).wrapperValue));
          }
          else {
            { OutputStringStream STREAM_000 = OutputStringStream.newOutputStringStream();

              STREAM_000.nativeStream.print("Don't know how to base64-decode this object: `" + value + "'");
              throw ((StellaException)(StellaException.newStellaException(STREAM_000.theStringReader()).fillInStackTrace()));
            }
          }
        }
        else if (encoding == XmlObjects.KWD_PLAIN) {
        }
        else {
          { OutputStringStream STREAM_001 = OutputStringStream.newOutputStringStream();

            STREAM_001.nativeStream.print("Unknown encoding scheme: `" + encoding + "'");
            throw ((StellaException)(StellaException.newStellaException(STREAM_001.theStringReader()).fillInStackTrace()));
          }
        }
      }
      return (value);
    }
  }

  public static Stella_Object ENCODE_SLOT_VALUE(StorageSlot slot, Stella_Object value) {
    { Keyword encoding = ((Keyword)(KeyValueList.dynamicSlotValue(slot.dynamicSlots, XmlObjects.SYM_XML_OBJECTS_ENCODING_SCHEME, null)));

      if (encoding != null) {
        if (encoding == XmlObjects.KWD_BASE64) {
          if (Stella_Object.stringP(value)) {
            value = StringWrapper.wrapString(XmlObjects.BASE64_ENCODE_STRING(((StringWrapper)(value)).wrapperValue));
          }
          else {
            { OutputStringStream STREAM_000 = OutputStringStream.newOutputStringStream();

              STREAM_000.nativeStream.print("Don't know how to base64-encode this object: `" + value + "'");
              throw ((StellaException)(StellaException.newStellaException(STREAM_000.theStringReader()).fillInStackTrace()));
            }
          }
        }
        else if (encoding == XmlObjects.KWD_PLAIN) {
        }
        else {
          { OutputStringStream STREAM_001 = OutputStringStream.newOutputStringStream();

            STREAM_001.nativeStream.print("unknown encoding scheme: `" + encoding + "'");
            throw ((StellaException)(StellaException.newStellaException(STREAM_001.theStringReader()).fillInStackTrace()));
          }
        }
      }
      return (value);
    }
  }

  public static int[] INITIALIZE_BASE64_DECODING_TABLE() {
    { int[] buffer = new int[256];

      { int i = Stella.NULL_INTEGER;
        int ITER_000 = 0;
        int UPPER_BOUND_000 = 255;

        for (;ITER_000 <= UPPER_BOUND_000; ITER_000 = ITER_000 + 1) {
          i = ITER_000;
          buffer[i] = -1;
        }
      }
      { char ch = Stella.NULL_CHARACTER;
        String VECTOR_000 = XmlObjects.$BASE64_ENCODING_TABLE$;
        int INDEX_000 = 0;
        int LENGTH_000 = VECTOR_000.length();
        int code = Stella.NULL_INTEGER;
        int ITER_001 = 0;
        int UPPER_BOUND_001 = 63;

        for (;(INDEX_000 < LENGTH_000) &&
                  (ITER_001 <= UPPER_BOUND_001); INDEX_000 = INDEX_000 + 1, ITER_001 = ITER_001 + 1) {
          ch = VECTOR_000.charAt(INDEX_000);
          code = ITER_001;
          buffer[(int) ch] = code;
        }
      }
      return (buffer);
    }
  }

  /** Base-64 encode <code>input</code> and return the result.
   * @param input
   * @return String
   */
  public static String BASE64_ENCODE_STRING(String input) {
    { int inputLength = input.length();
      int codeLength = Native.ceiling(inputLength / 3.0) * 4;
      int nofLines = Native.ceiling(codeLength / 76.0);
      int outputLength = codeLength + (nofLines * 2);
      StringBuffer output = Stella.makeRawMutableString(outputLength);
      String encodingTable = XmlObjects.$BASE64_ENCODING_TABLE$;
      int triple = 0;
      int inputCursor = 0;
      int outputCursor = 0;
      int eolPosition = 76;
      int nofPads = 0;

      LOOP_000 : for (;;) {
        if (inputCursor == inputLength) {
          break LOOP_000;
        }
        triple = (int) (input.charAt(inputCursor));
        inputCursor = inputCursor + 1;
        if (inputCursor == inputLength) {
          triple = (triple << 16);
        }
        else {
          triple = (((triple << 8)) | ((int) (input.charAt(inputCursor))));
          inputCursor = inputCursor + 1;
          if (inputCursor == inputLength) {
            triple = (triple << 8);
          }
          else {
            triple = (((triple << 8)) | ((int) (input.charAt(inputCursor))));
            inputCursor = inputCursor + 1;
          }
        }
        edu.isi.stella.javalib.Native.mutableString_nthSetter(output, (encodingTable.charAt(((triple >> 18)))), outputCursor);
        outputCursor = outputCursor + 1;
        edu.isi.stella.javalib.Native.mutableString_nthSetter(output, (encodingTable.charAt(((((triple >> 12)) & 63)))), outputCursor);
        outputCursor = outputCursor + 1;
        edu.isi.stella.javalib.Native.mutableString_nthSetter(output, (encodingTable.charAt(((((triple >> 6)) & 63)))), outputCursor);
        outputCursor = outputCursor + 1;
        edu.isi.stella.javalib.Native.mutableString_nthSetter(output, (encodingTable.charAt(((triple & 63)))), outputCursor);
        outputCursor = outputCursor + 1;
        if (outputCursor == eolPosition) {
          eolPosition = eolPosition + 78;
          edu.isi.stella.javalib.Native.mutableString_nthSetter(output, '\r', outputCursor);
          outputCursor = outputCursor + 1;
          edu.isi.stella.javalib.Native.mutableString_nthSetter(output, '\n', outputCursor);
          outputCursor = outputCursor + 1;
        }
      }
      switch ((inputLength % 3)) {
        case 0: 
          nofPads = 0;
        break;
        case 1: 
          nofPads = 2;
        break;
        case 2: 
          nofPads = 1;
        break;
        default:
          { OutputStringStream STREAM_000 = OutputStringStream.newOutputStringStream();

            STREAM_000.nativeStream.print("`" + (inputLength % 3) + "' is not a valid case option");
            throw ((StellaException)(StellaException.newStellaException(STREAM_000.theStringReader()).fillInStackTrace()));
          }
      }
      { int i = Stella.NULL_INTEGER;
        int ITER_000 = 1;
        int UPPER_BOUND_000 = nofPads;
        boolean UNBOUNDEDP_000 = UPPER_BOUND_000 == Stella.NULL_INTEGER;

        for (;UNBOUNDEDP_000 ||
                  (ITER_000 <= UPPER_BOUND_000); ITER_000 = ITER_000 + 1) {
          i = ITER_000;
          edu.isi.stella.javalib.Native.mutableString_nthSetter(output, '=', ((outputLength - i) - 2));
        }
      }
      if (outputLength >= 2) {
        edu.isi.stella.javalib.Native.mutableString_nthSetter(output, '\r', (outputLength - 2));
        edu.isi.stella.javalib.Native.mutableString_nthSetter(output, '\n', (outputLength - 1));
      }
      return (output.toString());
    }
  }

  /** Base-64 decode <code>input</code> and return the result.
   * @param input
   * @return String
   */
  public static String BASE64_DECODE_STRING(String input) {
    { int inputLength = input.length();
      int outputLength = (inputLength / 4) * 3;
      StringBuffer output = Stella.makeRawMutableString(outputLength);
      int[] decodingTable = XmlObjects.$BASE64_DECODING_TABLE$;
      int code = 0;
      int triple = 0;
      int nofPads = 0;
      int inputCursor = 0;
      int outputCursor = 0;

      LOOP_000 : for (;;) {
        LOOP_001 : for (;;) {
          if (inputCursor == inputLength) {
            break LOOP_001;
          }
          code = decodingTable[(int) (input.charAt(inputCursor))];
          inputCursor = inputCursor + 1;
          if (!(code == -1)) {
            break LOOP_001;
          }
        }
        if (inputCursor == inputLength) {
          break LOOP_000;
        }
        triple = code;
        triple = (((triple << 6)) | (decodingTable[(int) (input.charAt(inputCursor))]));
        inputCursor = inputCursor + 1;
        code = decodingTable[(int) (input.charAt(inputCursor))];
        inputCursor = inputCursor + 1;
        if (code == -1) {
          nofPads = 2;
          triple = (triple << 12);
        }
        else {
          triple = (((triple << 6)) | code);
          code = decodingTable[(int) (input.charAt(inputCursor))];
          inputCursor = inputCursor + 1;
          if (code == -1) {
            nofPads = 1;
            triple = (triple << 6);
          }
          else {
            triple = (((triple << 6)) | code);
          }
        }
        if (nofPads == 0) {
          edu.isi.stella.javalib.Native.mutableString_nthSetter(output, ((char) ((triple >> 16))), outputCursor);
          outputCursor = outputCursor + 1;
          edu.isi.stella.javalib.Native.mutableString_nthSetter(output, ((char) ((((triple >> 8)) & 255))), outputCursor);
          outputCursor = outputCursor + 1;
          edu.isi.stella.javalib.Native.mutableString_nthSetter(output, ((char) ((triple & 255))), outputCursor);
          outputCursor = outputCursor + 1;
        }
        else {
          edu.isi.stella.javalib.Native.mutableString_nthSetter(output, ((char) ((triple >> 16))), outputCursor);
          outputCursor = outputCursor + 1;
          if (nofPads == 1) {
            edu.isi.stella.javalib.Native.mutableString_nthSetter(output, ((char) ((((triple >> 8)) & 255))), outputCursor);
            outputCursor = outputCursor + 1;
          }
        }
      }
      if (outputCursor < outputLength) {
        return (Native.mutableString_subsequence(output, 0, outputCursor));
      }
      else {
        return (output.toString());
      }
    }
  }

  public static Stella_Object READ_XML(String xmlString) {
    { InputStringStream inputStream = InputStringStream.newInputStringStream(xmlString);

      return (InputStream.readXmlExpression(inputStream, null, new Object[1]));
    }
  }

  public static void MULTIREF_TEST1() {
    { F f = F.NEW_F();

      { E SELF_001 = E.NEW_E();

        SELF_001.f = f;
        { E e = SELF_001;

          { D SELF_002 = D.NEW_D();

            SELF_002.f = f;
            { D d = SELF_002;

              { C SELF_003 = C.NEW_C();

                SELF_003.d = d;
                SELF_003.e = e;
                { C c = SELF_003;

                  { B SELF_004 = B.NEW_B();

                    SELF_004.d = d;
                    { B b = SELF_004;

                      { A SELF_005 = A.NEW_A();

                        SELF_005.b = b;
                        SELF_005.c = c;
                        { A a = SELF_005;

                          XmlObjects.RESET_MULTIREF_TABLES();
                          XMLObject.POPULATE_NODE_PARENTS_TABLE(a);
                          XmlObjects.CREATE_NODE_ID_PARENT_TABLE();
                          XMLObject.SIMULATE_MULTIREF_OUTPUT(a);
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

}
