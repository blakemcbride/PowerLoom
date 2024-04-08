//  -*- Mode: Java -*-
//
// XMLObject.java

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

/** The Root of all XMLObjects
 * @author Stella Java Translator
 */
public abstract class XMLObject extends StandardObject {
    public String textContent;
    public String cdataContent;

  public static void SET_COLLECTION_SLOT_VALUE(XMLObject renamed_Object, StorageSlot slot, Stella_Object value) {
    { List valueList = ((List)(XMLObject.GET_OBJECT_SLOT_VALUE(renamed_Object, slot)));

      if (valueList == null) {
        valueList = List.newList();
        XMLObject.SET_OBJECT_SLOT_VALUE(renamed_Object, slot, valueList);
      }
      valueList.insertLast(value);
    }
  }

  public static void SET_OBJECT_SLOT_VALUE(XMLObject renamed_Object, StorageSlot slot, Stella_Object value) {
    StandardObject.writeSlotValue(renamed_Object, slot, XmlObjects.DECODE_SLOT_VALUE(slot, value));
  }

  public static Stella_Object GET_OBJECT_SLOT_VALUE(XMLObject renamed_Object, StorageSlot slot) {
    return (XmlObjects.ENCODE_SLOT_VALUE(slot, StandardObject.readSlotValue(renamed_Object, slot)));
  }

  public static String GET_ELEMENT_NAME_FROM_OBJECT(XMLObject renamed_Object) {
    { String className = renamed_Object.primaryType().symbolName;

      return (className);
    }
  }

  public static void HELP_SIMULATE_MULTIREF_OUTPUT(XMLObject node, XMLObject parent, int indent) {
    { String nodeName = XMLObject.GET_ELEMENT_NAME_FROM_OBJECT(node);
      Cons children = XMLObject.GET_CHILDREN(node);

      { int i = Stella.NULL_INTEGER;
        int ITER_000 = 1;
        int UPPER_BOUND_000 = indent;
        boolean UNBOUNDEDP_000 = UPPER_BOUND_000 == Stella.NULL_INTEGER;

        for (;UNBOUNDEDP_000 ||
                  (ITER_000 <= UPPER_BOUND_000); ITER_000 = ITER_000 + 1) {
          i = ITER_000;
          i = i;
          Stella.STANDARD_OUTPUT.nativeStream.print(" ");
        }
      }
      Stella.STANDARD_OUTPUT.nativeStream.print(nodeName);
      if (XMLObject.FIRST_PARENT_FOR_MULTIREF_NODEP(node, parent)) {
        Stella.STANDARD_OUTPUT.nativeStream.print(" id=" + XMLObject.GET_NODE_ID(node));
      }
      else if (XMLObject.NTH_PARENT_FOR_MULTIREF_NODEP(node, parent)) {
        Stella.STANDARD_OUTPUT.nativeStream.print(" href=" + XMLObject.GET_NODE_ID(node));
      }
      Stella.STANDARD_OUTPUT.nativeStream.println();
      { XMLObject child = null;
        Cons ITER_001 = children;

        for (;!(ITER_001 == Stella.NIL); ITER_001 = ITER_001.rest) {
          child = ((XMLObject)(ITER_001.value));
          XMLObject.HELP_SIMULATE_MULTIREF_OUTPUT(child, node, indent + 2);
        }
      }
    }
  }

  public static int GET_NODE_ID(XMLObject node) {
    { IdParentStruct idParentsStruct = ((IdParentStruct)(XmlObjects.$NODE_ID_PARENTS_TABLE$.lookup(node)));

      return (idParentsStruct.id);
    }
  }

  public static boolean NTH_PARENT_FOR_MULTIREF_NODEP(XMLObject node, XMLObject parent) {
    { IdParentStruct idParentsStruct = ((IdParentStruct)(XmlObjects.$NODE_ID_PARENTS_TABLE$.lookup(node)));

      return ((idParentsStruct != null) &&
          (!(((XMLObject)(idParentsStruct.parents.first())) == parent)));
    }
  }

  public static boolean FIRST_PARENT_FOR_MULTIREF_NODEP(XMLObject node, XMLObject parent) {
    { IdParentStruct idParentsStruct = ((IdParentStruct)(XmlObjects.$NODE_ID_PARENTS_TABLE$.lookup(node)));

      return ((idParentsStruct != null) &&
          (((XMLObject)(idParentsStruct.parents.first())) == parent));
    }
  }

  public static void SIMULATE_MULTIREF_OUTPUT(XMLObject node) {
    XMLObject.HELP_SIMULATE_MULTIREF_OUTPUT(node, null, 0);
  }

  public static void HELP_POPULATE_NODE_PARENTS_TABLE(XMLObject node, XMLObject parent) {
    { Cons children = XMLObject.GET_CHILDREN(node);
      boolean firstVisitP = XMLObject.INSERT_NODE_PARENTS_TABLE(node, parent);

      if (firstVisitP) {
        { XMLObject child = null;
          Cons ITER_000 = children;

          for (;!(ITER_000 == Stella.NIL); ITER_000 = ITER_000.rest) {
            child = ((XMLObject)(ITER_000.value));
            XMLObject.HELP_POPULATE_NODE_PARENTS_TABLE(child, node);
          }
        }
      }
    }
  }

  public static void POPULATE_NODE_PARENTS_TABLE(XMLObject node) {
    XMLObject.HELP_POPULATE_NODE_PARENTS_TABLE(node, null);
  }

  public static Cons GET_CHILDREN(XMLObject node) {
    { Cons result = Stella.NIL;

      { Slot slot = null;
        Cons ITER_000 = XMLObject.GET_MAPPED_SLOTS(node).theConsList;

        for (;!(ITER_000 == Stella.NIL); ITER_000 = ITER_000.rest) {
          slot = ((Slot)(ITER_000.value));
          if (XmlObjects.ELEMENT_SLOTP(slot) &&
              (!XMLObject.SLOT_VALUE_IS_NULLP(node, slot))) {
            result = Cons.cons(XMLObject.GET_OBJECT_SLOT_VALUE(node, ((StorageSlot)(slot))), result);
          }
        }
      }
      return (result);
    }
  }

  public static void INSERT_NODE_ID_PARENTS_TABLE(XMLObject node, XMLObject parent) {
    { IdParentStruct idParentStruct = ((IdParentStruct)(XmlObjects.$NODE_ID_PARENTS_TABLE$.lookup(node)));
      List parents = null;

      if (idParentStruct == null) {
        {
          idParentStruct = IdParentStruct.NEW_ID_PARENT_STRUCT();
          parents = List.newList();
          idParentStruct.id = XmlObjects.GET_NEXT_ID();
          idParentStruct.parents = parents;
          XmlObjects.$NODE_ID_PARENTS_TABLE$.insertAt(node, idParentStruct);
        }
      }
      else {
        parents = idParentStruct.parents;
      }
      parents.insert(parent);
    }
  }

  public static boolean INSERT_NODE_PARENTS_TABLE(XMLObject node, XMLObject parent) {
    if (parent == null) {
      return (true);
    }
    { List parents = ((List)(XmlObjects.$NODE_PARENTS_TABLE$.lookup(node)));
      boolean result = false;

      if (parents == null) {
        result = true;
        parents = List.newList();
        XmlObjects.$NODE_PARENTS_TABLE$.insertAt(node, parents);
      }
      parents.insert(parent);
      return (result);
    }
  }

  public static StorageSlot LOOKUP_CONTENT_SLOT(XMLObject renamed_Object) {
    return (((StorageSlot)(Stella_Class.lookupSlot(renamed_Object.primaryClass(), XmlObjects.SYM_XML_OBJECTS_textContent))));
  }

  public static StorageSlot LOOKUP_COLLECTION_SLOT(XMLObject renamed_Object, Cons elementExpr) {
    { XmlElement tag = ((XmlElement)(elementExpr.value));

      { Slot slot = null;
        Cons ITER_000 = XMLObject.GET_MAPPED_SLOTS(renamed_Object).theConsList;

        for (;!(ITER_000 == Stella.NIL); ITER_000 = ITER_000.rest) {
          slot = ((Slot)(ITER_000.value));
          if (XmlObjects.COLLECTION_SLOTP(slot) &&
              XmlObjects.SLOT_REPRESENTS_TAGP(slot, tag, false, true)) {
            return (((StorageSlot)(slot)));
          }
        }
      }
      return (null);
    }
  }

  public static StorageSlot LOOKUP_ATTRIBUTE_SLOT(XMLObject renamed_Object, XmlAttribute attribute) {
    { Slot slot = null;
      Cons ITER_000 = XMLObject.GET_MAPPED_SLOTS(renamed_Object).theConsList;

      for (;!(ITER_000 == Stella.NIL); ITER_000 = ITER_000.rest) {
        slot = ((Slot)(ITER_000.value));
        if (XmlObjects.ATTRIBUTE_SLOTP(slot) &&
            XmlObjects.SLOT_REPRESENTS_TAGP(slot, attribute, false, false)) {
          return (((StorageSlot)(slot)));
        }
      }
    }
    return (null);
  }

  public static StorageSlot LOOKUP_ELEMENT_SLOT(XMLObject renamed_Object, Cons elementExpr) {
    { XmlElement tag = ((XmlElement)(elementExpr.value));
      Cons general_slots = Stella.NIL;

      { Slot slot = null;
        Cons ITER_000 = XMLObject.GET_MAPPED_SLOTS(renamed_Object).theConsList;

        for (;!(ITER_000 == Stella.NIL); ITER_000 = ITER_000.rest) {
          slot = ((Slot)(ITER_000.value));
          if (XmlObjects.ELEMENT_SLOTP(slot)) {
            if (XmlObjects.SLOT_REPRESENTS_TAGP(slot, tag, true, false)) {
              return (((StorageSlot)(slot)));
            }
            else if (slot.typeSpecifier() == XmlObjects.SGT_XML_OBJECTS_XMLObject) {
              general_slots = Cons.cons(slot, general_slots);
            }
            else {
            }
          }
        }
      }
      if (general_slots == Stella.NIL) {
        return (null);
      }
      else if (general_slots.rest == Stella.NIL) {
        return (((StorageSlot)(general_slots.value)));
      }
      else {
        return (null);
      }
    }
  }

  public static List GET_MAPPED_SLOTS(XMLObject renamed_Object) {
    return (((Stella_Class)(renamed_Object.primaryType().surrogateValue)).classLocalSlots);
  }

  public static void SET_COLLECTIONS(XMLObject renamed_Object, Cons elementExprs) {
    { Stella_Object expr = null;
      Cons ITER_000 = elementExprs;

      for (;!(ITER_000 == Stella.NIL); ITER_000 = ITER_000.rest) {
        expr = ITER_000.value;
        if (Surrogate.subtypeOfStringP(Stella_Object.safePrimaryType(expr))) {
          { StringWrapper expr_000 = ((StringWrapper)(expr));

          }
        }
        else {
          { StorageSlot matchingSlot = XMLObject.LOOKUP_COLLECTION_SLOT(renamed_Object, ((Cons)(expr)));

            if (!(matchingSlot == null)) {
              { XMLObject value = XmlObjects.FROM_XML(((Cons)(expr)));

                XMLObject.SET_COLLECTION_SLOT_VALUE(renamed_Object, matchingSlot, value);
              }
            }
          }
        }
      }
    }
  }

  public static void SET_ATTRIBUTES(XMLObject renamed_Object, Cons attributeExprs) {
    { PropertyList SELF_000 = PropertyList.newPropertyList();

      SELF_000.thePlist = attributeExprs;
      { PropertyList plist = SELF_000;

        { Stella_Object attribute = null;
          Stella_Object value = null;
          Cons ITER_000 = plist.thePlist;

          for (;!(ITER_000 == Stella.NIL); ITER_000 = ITER_000.rest.rest) {
            attribute = ITER_000.value;
            value = ITER_000.rest.value;
            { StorageSlot matchingSlot = XMLObject.LOOKUP_ATTRIBUTE_SLOT(renamed_Object, ((XmlAttribute)(attribute)));

              if (!(matchingSlot == null)) {
                XMLObject.SET_OBJECT_SLOT_VALUE(renamed_Object, matchingSlot, value);
              }
            }
          }
        }
      }
    }
  }

  public static void SET_ELEMENTS(XMLObject renamed_Object, Cons elementExprs) {
    { Stella_Object expr = null;
      Cons ITER_000 = elementExprs;

      for (;!(ITER_000 == Stella.NIL); ITER_000 = ITER_000.rest) {
        expr = ITER_000.value;
        if (Surrogate.subtypeOfStringP(Stella_Object.safePrimaryType(expr))) {
          { StringWrapper expr_000 = ((StringWrapper)(expr));

            XMLObject.SET_OBJECT_SLOT_VALUE(renamed_Object, XMLObject.LOOKUP_CONTENT_SLOT(renamed_Object), expr_000);
          }
        }
        else {
          if (Stella_Object.isaP(expr, XmlObjects.SGT_STELLA_CONS) &&
              Stella_Object.xmlCdataP(((Cons)(expr)).value)) {
            renamed_Object.cdataContent = StringWrapper.unwrapString(((StringWrapper)(((Cons)(((Cons)(expr)).rest.value)).value)));
          }
          else {
            { StorageSlot matchingSlot = XMLObject.LOOKUP_ELEMENT_SLOT(renamed_Object, ((Cons)(expr)));

              if (!(matchingSlot == null)) {
                { XMLObject value = XmlObjects.FROM_XML(((Cons)(expr)));

                  XMLObject.SET_OBJECT_SLOT_VALUE(renamed_Object, matchingSlot, value);
                }
              }
            }
          }
        }
      }
    }
  }

  public static Cons MAKE_COLLECTION(XMLObject parentObject, Slot slot, Cons namespaceStack) {
    { List elements = ((List)(XMLObject.GET_OBJECT_SLOT_VALUE(parentObject, ((StorageSlot)(slot)))));
      Cons result = Stella.NIL;

      { XMLObject element = null;
        Cons ITER_000 = elements.theConsList;
        Cons COLLECT_000 = null;

        for (;!(ITER_000 == Stella.NIL); ITER_000 = ITER_000.rest) {
          element = ((XMLObject)(ITER_000.value));
          if (COLLECT_000 == null) {
            {
              COLLECT_000 = Cons.cons(element.TO_XML(namespaceStack), Stella.NIL);
              if (result == Stella.NIL) {
                result = COLLECT_000;
              }
              else {
                Cons.addConsToEndOfConsList(result, COLLECT_000);
              }
            }
          }
          else {
            {
              COLLECT_000.rest = Cons.cons(element.TO_XML(namespaceStack), Stella.NIL);
              COLLECT_000 = COLLECT_000.rest;
            }
          }
        }
      }
      return (result);
    }
  }

  public static Cons MAKE_ELEMENT(XMLObject parentObject, Slot slot, Cons namespaceStack) {
    return (((XMLObject)(XMLObject.GET_OBJECT_SLOT_VALUE(parentObject, ((StorageSlot)(slot))))).TO_XML(namespaceStack));
  }

  public static Cons MAKE_REVERSED_ATTRIBUTE(XMLObject parentObject, StorageSlot slot) {
    { Symbol attributeName = slot.slotName;
      String namespacePrefix = ((Module)(attributeName.homeContext)).moduleName;
      Stella_Object attributeValue = XMLObject.GET_OBJECT_SLOT_VALUE(parentObject, slot);
      StringWrapper namespaceURI = XmlObjects.GET_NAMESPACE_URI(namespacePrefix);

      { XmlAttribute CHOOSE_VALUE_000 = null;

        if ((namespaceURI == null) ||
            (((Boolean)(XmlObjects.$SUPRESS_NAMESPACESp$.get())).booleanValue() &&
             XmlObjects.$INVISIBLE_NAMESPACES_ON_OUTPUT$.memberP(StringWrapper.wrapString(namespacePrefix)))) {
          { XmlLocalAttribute SELF_000 = XmlLocalAttribute.newXmlLocalAttribute();

            SELF_000.name = attributeName.symbolName;
            SELF_000.surfaceForm = attributeName.symbolName;
            CHOOSE_VALUE_000 = SELF_000;
          }
        }
        else {
          { XmlGlobalAttribute SELF_001 = XmlGlobalAttribute.newXmlGlobalAttribute();

            SELF_001.name = attributeName.symbolName;
            SELF_001.surfaceForm = namespacePrefix + ":" + attributeName.symbolName;
            SELF_001.namespaceName = namespacePrefix;
            SELF_001.namespaceUri = namespaceURI.wrapperValue;
            CHOOSE_VALUE_000 = SELF_001;
          }
        }
        { XmlAttribute attribute = CHOOSE_VALUE_000;

          return (Cons.cons(attributeValue, Cons.cons(attribute, Stella.NIL)));
        }
      }
    }
  }

  public static StringWrapper GET_ATTRIBUTE_VALUE_NAMESPACE_NAME(XMLObject parentObject, StorageSlot slot) {
    { String attributeValue = StringWrapper.unwrapString(((StringWrapper)(XMLObject.GET_OBJECT_SLOT_VALUE(parentObject, slot))));

      if (attributeValue != null) {
        { String valueNamespaceName = XmlObjects.GET_VALUE_NAMESPACE_PREFIX(attributeValue);

          if ((valueNamespaceName != null) &&
              (XmlObjects.$NAMESPACE_PREFIX_URI_TABLE$.lookup(StringWrapper.wrapString(valueNamespaceName)) != null)) {
            return (StringWrapper.wrapString(valueNamespaceName));
          }
        }
      }
      return (null);
    }
  }

  public static XmlElement MAKE_ELEMENT_TAG(XMLObject renamed_Object) {
    { String tagType = XMLObject.GET_ELEMENT_NAME_FROM_OBJECT(renamed_Object);
      String namespacePrefix = XMLObject.GET_NAMESPACE_PREFIX(renamed_Object);
      StringWrapper namespaceURI = XmlObjects.GET_NAMESPACE_URI(namespacePrefix);

      if ((namespaceURI == null) ||
          (((Boolean)(XmlObjects.$SUPRESS_NAMESPACESp$.get())).booleanValue() &&
           XmlObjects.$INVISIBLE_NAMESPACES_ON_OUTPUT$.memberP(StringWrapper.wrapString(namespacePrefix)))) {
        { XmlElement SELF_000 = XmlElement.newXmlElement();

          SELF_000.name = tagType;
          SELF_000.surfaceForm = tagType;
          { XmlElement VALUE_000 = SELF_000;

            return (VALUE_000);
          }
        }
      }
      else {
        { XmlElement SELF_001 = XmlElement.newXmlElement();

          SELF_001.name = tagType;
          SELF_001.surfaceForm = namespacePrefix + ":" + tagType;
          SELF_001.namespaceName = namespacePrefix;
          SELF_001.namespaceUri = namespaceURI.wrapperValue;
          { XmlElement VALUE_001 = SELF_001;

            return (VALUE_001);
          }
        }
      }
    }
  }

  public static Cons MAKE_CONTENT_EXPRESSION(XMLObject renamed_Object) {
    { Cons result = Stella.NIL;
      String content = renamed_Object.textContent;
      String cdata = renamed_Object.cdataContent;

      if (content != null) {
        result = Cons.cons(StringWrapper.wrapString(content), result);
      }
      if (cdata != null) {
        result = Cons.cons(Stella.makeXmlCdataForm(cdata), result);
      }
      return (result);
    }
  }

  public static String GET_NAMESPACE_PREFIX(XMLObject renamed_Object) {
    { Stella_Class theClass = ((Stella_Class)(renamed_Object.primaryType().surrogateValue));
      Module module = theClass.homeModule();

      return (module.moduleName);
    }
  }

  public Cons TO_XML(Cons namespaceStack) {
    { XMLObject renamed_Object = this;

      { XmlElement objectTag = XMLObject.MAKE_ELEMENT_TAG(renamed_Object);
        List slots = XMLObject.GET_MAPPED_SLOTS(renamed_Object);
        String objectNamespace = XMLObject.GET_NAMESPACE_PREFIX(renamed_Object);
        Cons newNamespaceStack = namespaceStack;
        StringWrapper attributeNamespaceName = null;
        StringWrapper attributeValueNamespaceName = null;
        StringWrapper namespaceURI = null;
        Cons namespaceAttributes = Stella.NIL;
        Cons attributes = Stella.NIL;
        Cons elements = Stella.NIL;
        Cons collections = Stella.NIL;

        if (!(newNamespaceStack.memberP(StringWrapper.wrapString(objectNamespace)))) {
          newNamespaceStack = Cons.cons(StringWrapper.wrapString(objectNamespace), newNamespaceStack);
          namespaceURI = ((StringWrapper)(XmlObjects.$NAMESPACE_PREFIX_URI_TABLE$.lookup(StringWrapper.wrapString(objectNamespace))));
          if (namespaceURI != null) {
            namespaceAttributes = Cons.cons(XmlObjects.MAKE_NAMESPACE_ATTRIBUTE(objectNamespace), namespaceAttributes);
            namespaceAttributes = Cons.cons(namespaceURI, namespaceAttributes);
          }
        }
        { Slot slot = null;
          Cons ITER_000 = slots.theConsList;

          for (;!(ITER_000 == Stella.NIL); ITER_000 = ITER_000.rest) {
            slot = ((Slot)(ITER_000.value));
            if (XmlObjects.ATTRIBUTE_SLOTP(slot) &&
                (!XMLObject.SLOT_VALUE_IS_NULLP(renamed_Object, slot))) {
              attributes = Cons.append(XMLObject.MAKE_REVERSED_ATTRIBUTE(renamed_Object, ((StorageSlot)(slot))), attributes);
              attributeNamespaceName = StringWrapper.wrapString(((Module)(slot.slotName.homeContext)).moduleName);
              if (!(newNamespaceStack.memberP(attributeNamespaceName))) {
                newNamespaceStack = Cons.cons(attributeNamespaceName, newNamespaceStack);
                namespaceURI = ((StringWrapper)(XmlObjects.$NAMESPACE_PREFIX_URI_TABLE$.lookup(attributeNamespaceName)));
                if (namespaceURI != null) {
                  namespaceAttributes = Cons.cons(XmlObjects.MAKE_NAMESPACE_ATTRIBUTE(attributeNamespaceName.wrapperValue), namespaceAttributes);
                  namespaceAttributes = Cons.cons(namespaceURI, namespaceAttributes);
                }
              }
              attributeValueNamespaceName = XMLObject.GET_ATTRIBUTE_VALUE_NAMESPACE_NAME(renamed_Object, ((StorageSlot)(slot)));
              if (!((attributeValueNamespaceName == null) ||
                  newNamespaceStack.memberP(attributeValueNamespaceName))) {
                newNamespaceStack = Cons.cons(attributeValueNamespaceName, newNamespaceStack);
                namespaceURI = ((StringWrapper)(XmlObjects.$NAMESPACE_PREFIX_URI_TABLE$.lookup(attributeValueNamespaceName)));
                if (namespaceURI != null) {
                  namespaceAttributes = Cons.cons(XmlObjects.MAKE_NAMESPACE_ATTRIBUTE(attributeValueNamespaceName.wrapperValue), namespaceAttributes);
                  namespaceAttributes = Cons.cons(namespaceURI, namespaceAttributes);
                }
              }
            }
          }
        }
        { Slot slot = null;
          Cons ITER_001 = slots.theConsList;

          for (;!(ITER_001 == Stella.NIL); ITER_001 = ITER_001.rest) {
            slot = ((Slot)(ITER_001.value));
            if (XmlObjects.ELEMENT_SLOTP(slot)) {
              if (!(XMLObject.SLOT_VALUE_IS_NULLP(renamed_Object, slot))) {
                elements = Cons.cons(XMLObject.MAKE_ELEMENT(renamed_Object, slot, newNamespaceStack), elements);
              }
            }
            else if (XmlObjects.COLLECTION_SLOTP(slot)) {
              if (!(XMLObject.SLOT_VALUE_IS_NULL_OR_EMPTYP(renamed_Object, slot))) {
                collections = Cons.cons(XMLObject.MAKE_COLLECTION(renamed_Object, slot, newNamespaceStack), collections);
              }
            }
          }
        }
        return (Cons.cons(objectTag, Cons.cons(namespaceAttributes.reverse().concatenate(attributes.reverse().concatenate(Stella.NIL, Stella.NIL), Stella.NIL), elements.reverse().concatenate(collections.reverse().concatenate(XMLObject.MAKE_CONTENT_EXPRESSION(renamed_Object).concatenate(Stella.NIL, Stella.NIL), Stella.NIL), Stella.NIL))));
      }
    }
  }

  /** Write <code>renamed_Object</code> in  it's XML Representation to <code>out</code>.
   * @param out
   */
  public void TO_XML_STREAM(OutputStream out) {
    { XMLObject renamed_Object = this;

      OutputStream.printXmlExpression(out, renamed_Object.TO_XML(Stella.NIL), 0);
    }
  }

  /** Convert <code>renamed_Object</code> into it's XML Representation as a string
   * @return String
   */
  public String TO_XML_STRING() {
    { XMLObject renamed_Object = this;

      return (XmlObjects.STRINGIFY_XML(renamed_Object.TO_XML(Stella.NIL)));
    }
  }

  public static boolean SLOT_VALUE_IS_NULL_OR_EMPTYP(XMLObject parentObject, Slot slot) {
    { List value = ((List)(XMLObject.GET_OBJECT_SLOT_VALUE(parentObject, ((StorageSlot)(slot)))));

      return ((value == null) ||
          value.emptyP());
    }
  }

  public static boolean SLOT_VALUE_IS_NULLP(XMLObject parentObject, Slot slot) {
    { Stella_Object value = XMLObject.GET_OBJECT_SLOT_VALUE(parentObject, ((StorageSlot)(slot)));

      if (value == null) {
        return (true);
      }
      { Surrogate TEST_VALUE_000 = Stella_Object.safePrimaryType(value);

        if (Surrogate.subtypeOfIntegerP(TEST_VALUE_000)) {
          { IntegerWrapper value_000 = ((IntegerWrapper)(value));

            return (value_000.wrapperValue == Stella.NULL_INTEGER);
          }
        }
        else if (Surrogate.subtypeOfFloatP(TEST_VALUE_000)) {
          { FloatWrapper value_000 = ((FloatWrapper)(value));

            return (value_000.wrapperValue == Stella.NULL_FLOAT);
          }
        }
        else if (Surrogate.subtypeOfStringP(TEST_VALUE_000)) {
          { StringWrapper value_000 = ((StringWrapper)(value));

            return (value_000.wrapperValue == null);
          }
        }
        else if (Surrogate.subtypeOfCharacterP(TEST_VALUE_000)) {
          { CharacterWrapper value_000 = ((CharacterWrapper)(value));

            return (value_000.wrapperValue == Stella.NULL_CHARACTER);
          }
        }
        else {
          return (false);
        }
      }
    }
  }

  /** Sets either the textContent or cdataContent slot, depending on
   * whether <code>content</code> needs to be encoded as CDATA or not.
   * @param content
   */
  public void SET_CONTENT(String content) {
    { XMLObject OBJ = this;

      { boolean FOUNDP_000 = false;

        { char ch = Stella.NULL_CHARACTER;
          String VECTOR_000 = content;
          int INDEX_000 = 0;
          int LENGTH_000 = VECTOR_000.length();

          LOOP_000 : for (;INDEX_000 < LENGTH_000; INDEX_000 = INDEX_000 + 1) {
            ch = VECTOR_000.charAt(INDEX_000);
            if (Stella.htmlCharacterNeedsQuotingP(ch)) {
              FOUNDP_000 = true;
              break LOOP_000;
            }
          }
        }
        if (FOUNDP_000) {
          if (Native.stringSearch(content, "]]>", 0) != Stella.NULL_INTEGER) {
            { OutputStringStream s = OutputStringStream.newOutputStringStream();

              Stella.writeHtmlQuotingSpecialCharacters(s.nativeStream, content);
              OBJ.textContent = s.theStringReader();
            }
          }
          else {
            OBJ.cdataContent = content;
          }
        }
        else {
          OBJ.textContent = content;
        }
      }
    }
  }

  /** Returns the textContent or cdataContent slot, whichever has
   * a value.  If both are present, only the textContent slot is returned.
   * @return String
   */
  public String GET_CONTENT() {
    { XMLObject OBJ = this;

      if (OBJ.textContent != null) {
        return (OBJ.textContent);
      }
      else {
        return (OBJ.cdataContent);
      }
    }
  }

  public void printObject(edu.isi.stella.javalib.NativeOutputStream stream) {
    { XMLObject self = this;

      stream.print(self.TO_XML_STRING());
    }
  }

  public static Stella_Object access_XMLObject_Slot_Value(XMLObject self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == XmlObjects.SYM_XML_OBJECTS_textContent) {
      if (setvalueP) {
        self.textContent = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.textContent);
      }
    }
    else if (slotname == XmlObjects.SYM_XML_OBJECTS_cdataContent) {
      if (setvalueP) {
        self.cdataContent = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.cdataContent);
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

}

