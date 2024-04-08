//  -*- Mode: C++ -*-

// xml.cc

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
| Portions created by the Initial Developer are Copyright (C) 1996-2023      |
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

#include "stella/stella-system.hh"

namespace stella {

const char* oXML_URNo = "http://www.w3.org/XML/1998/namespaces";

const char* oHTML_V4_0_URNo = "http://www.w3.org/TR/REC-html40";

XmlObject* newXmlObject() {
  { XmlObject* self = NULL;

    self = new XmlObject();
    self->surfaceForm = NULL;
    self->name = NULL;
    return (self);
  }
}

Surrogate* XmlObject::primaryType() {
  { XmlObject* self = this;

    return (SGT_XML_STELLA_XML_OBJECT);
  }
}

Object* accessXmlObjectSlotValue(XmlObject* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_XML_STELLA_NAME) {
    if (setvalueP) {
      self->name = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->name);
    }
  }
  else if (slotname == SYM_XML_STELLA_SURFACE_FORM) {
    if (setvalueP) {
      self->surfaceForm = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->surfaceForm);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

XmlElement* newXmlElement() {
  { XmlElement* self = NULL;

    self = new XmlElement();
    self->surfaceForm = NULL;
    self->name = NULL;
    self->elementDictionary = NULL;
    self->namespaceUri = NULL;
    self->namespaceName = NULL;
    return (self);
  }
}

Surrogate* XmlElement::primaryType() {
  { XmlElement* self = this;

    return (SGT_XML_STELLA_XML_ELEMENT);
  }
}

Object* accessXmlElementSlotValue(XmlElement* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_XML_STELLA_NAMESPACE_NAME) {
    if (setvalueP) {
      self->namespaceName = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->namespaceName);
    }
  }
  else if (slotname == SYM_XML_STELLA_NAMESPACE_URI) {
    if (setvalueP) {
      self->namespaceUri = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->namespaceUri);
    }
  }
  else if (slotname == SYM_XML_STELLA_ELEMENT_DICTIONARY) {
    if (setvalueP) {
      self->elementDictionary = ((KeyValueList*)(value));
    }
    else {
      value = self->elementDictionary;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

void XmlElement::printObject(std::ostream* stream) {
  { XmlElement* self = this;

    *(stream) << "<" << self->surfaceForm << ">";
  }
}

void XmlAttribute::printObject(std::ostream* stream) {
  { XmlAttribute* self = this;

    *(stream) << "<" << self->surfaceForm << ">";
  }
}

XmlLocalAttribute* newXmlLocalAttribute() {
  { XmlLocalAttribute* self = NULL;

    self = new XmlLocalAttribute();
    self->surfaceForm = NULL;
    self->name = NULL;
    self->parentElement = NULL;
    return (self);
  }
}

Surrogate* XmlLocalAttribute::primaryType() {
  { XmlLocalAttribute* self = this;

    return (SGT_XML_STELLA_XML_LOCAL_ATTRIBUTE);
  }
}

Object* accessXmlLocalAttributeSlotValue(XmlLocalAttribute* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_XML_STELLA_PARENT_ELEMENT) {
    if (setvalueP) {
      self->parentElement = ((XmlElement*)(value));
    }
    else {
      value = self->parentElement;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

XmlGlobalAttribute* newXmlGlobalAttribute() {
  { XmlGlobalAttribute* self = NULL;

    self = new XmlGlobalAttribute();
    self->surfaceForm = NULL;
    self->name = NULL;
    self->namespaceUri = NULL;
    self->namespaceName = NULL;
    return (self);
  }
}

Surrogate* XmlGlobalAttribute::primaryType() {
  { XmlGlobalAttribute* self = this;

    return (SGT_XML_STELLA_XML_GLOBAL_ATTRIBUTE);
  }
}

Object* accessXmlGlobalAttributeSlotValue(XmlGlobalAttribute* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_XML_STELLA_NAMESPACE_NAME) {
    if (setvalueP) {
      self->namespaceName = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->namespaceName);
    }
  }
  else if (slotname == SYM_XML_STELLA_NAMESPACE_URI) {
    if (setvalueP) {
      self->namespaceUri = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->namespaceUri);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

XmlProcessingInstruction* newXmlProcessingInstruction() {
  { XmlProcessingInstruction* self = NULL;

    self = new XmlProcessingInstruction();
    self->surfaceForm = NULL;
    self->name = NULL;
    self->data = NULL;
    return (self);
  }
}

Surrogate* XmlProcessingInstruction::primaryType() {
  { XmlProcessingInstruction* self = this;

    return (SGT_XML_STELLA_XML_PROCESSING_INSTRUCTION);
  }
}

Object* accessXmlProcessingInstructionSlotValue(XmlProcessingInstruction* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_XML_STELLA_DATA) {
    if (setvalueP) {
      self->data = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->data);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

void XmlProcessingInstruction::printObject(std::ostream* stream) {
  { XmlProcessingInstruction* self = this;

    if (self->data == NULL) {
      *(stream) << "<?" << self->surfaceForm << ">";
    }
    else {
      *(stream) << "<?" << self->surfaceForm << " " << self->data << ">";
    }
  }
}

XmlDeclaration* newXmlDeclaration() {
  { XmlDeclaration* self = NULL;

    self = new XmlDeclaration();
    self->surfaceForm = NULL;
    self->name = NULL;
    self->data = NULL;
    return (self);
  }
}

Surrogate* XmlDeclaration::primaryType() {
  { XmlDeclaration* self = this;

    return (SGT_XML_STELLA_XML_DECLARATION);
  }
}

Object* accessXmlDeclarationSlotValue(XmlDeclaration* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_XML_STELLA_DATA) {
    if (setvalueP) {
      self->data = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->data);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

void XmlDeclaration::printObject(std::ostream* stream) {
  { XmlDeclaration* self = this;

    if (self->data == NULL) {
      *(stream) << "<!" << self->surfaceForm << ">";
    }
    else {
      *(stream) << "<!" << self->surfaceForm << " " << self->data << ">";
    }
  }
}

XmlDoctypeDeclaration* newXmlDoctypeDeclaration() {
  { XmlDoctypeDeclaration* self = NULL;

    self = new XmlDoctypeDeclaration();
    self->surfaceForm = NULL;
    self->name = NULL;
    self->data = NULL;
    return (self);
  }
}

Surrogate* XmlDoctypeDeclaration::primaryType() {
  { XmlDoctypeDeclaration* self = this;

    return (SGT_XML_STELLA_XML_DOCTYPE_DECLARATION);
  }
}

void XmlDoctypeDeclaration::printObject(std::ostream* stream) {
  { XmlDoctypeDeclaration* self = this;

    if (self->data == NULL) {
      *(stream) << "<!" << self->surfaceForm << ">";
    }
    else {
      *(stream) << "<!" << self->surfaceForm << " ...>";
    }
  }
}

XmlSpecial* newXmlSpecial() {
  { XmlSpecial* self = NULL;

    self = new XmlSpecial();
    self->surfaceForm = NULL;
    self->name = NULL;
    self->data = NULL;
    return (self);
  }
}

Surrogate* XmlSpecial::primaryType() {
  { XmlSpecial* self = this;

    return (SGT_XML_STELLA_XML_SPECIAL);
  }
}

Object* accessXmlSpecialSlotValue(XmlSpecial* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_XML_STELLA_DATA) {
    if (setvalueP) {
      self->data = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->data);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

void XmlSpecial::printObject(std::ostream* stream) {
  { XmlSpecial* self = this;

    *(stream) << "<!" << self->surfaceForm << ">";
  }
}

XmlComment* newXmlComment() {
  { XmlComment* self = NULL;

    self = new XmlComment();
    self->surfaceForm = NULL;
    self->name = NULL;
    return (self);
  }
}

Surrogate* XmlComment::primaryType() {
  { XmlComment* self = this;

    return (SGT_XML_STELLA_XML_COMMENT);
  }
}

void XmlComment::printObject(std::ostream* stream) {
  { XmlComment* self = this;

    if (self->surfaceForm == NULL) {
      *(stream) << "<!-- -->";
    }
    else {
      *(stream) << "<!-- " << strlen((self->surfaceForm)) << " chars -->";
    }
  }
}

XmlDoctype* newXmlDoctype() {
  { XmlDoctype* self = NULL;

    self = new XmlDoctype();
    self->parameterEntityTable = newKeyValueList();
    self->entityTable = newKeyValueList();
    self->name = NULL;
    return (self);
  }
}

Surrogate* XmlDoctype::primaryType() {
  { XmlDoctype* self = this;

    return (SGT_XML_STELLA_XML_DOCTYPE);
  }
}

Object* accessXmlDoctypeSlotValue(XmlDoctype* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_XML_STELLA_NAME) {
    if (setvalueP) {
      self->name = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->name);
    }
  }
  else if (slotname == SYM_XML_STELLA_ENTITY_TABLE) {
    if (setvalueP) {
      self->entityTable = ((KeyValueList*)(value));
    }
    else {
      value = self->entityTable;
    }
  }
  else if (slotname == SYM_XML_STELLA_PARAMETER_ENTITY_TABLE) {
    if (setvalueP) {
      self->parameterEntityTable = ((KeyValueList*)(value));
    }
    else {
      value = self->parameterEntityTable;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

void XmlDoctype::printObject(std::ostream* stream) {
  { XmlDoctype* self = this;

    *(stream) << "<!DOCTYPE " << self->name << ">";
  }
}

// Hash Table for interning XML elements that don't appear in any namespace.
StringHashTable* oXML_ELEMENT_NULL_NAMESPACE_TABLEo = NULL;

// Hash Table mapping URI's (for namespaces) to a Hash Table
// for interning XML elements.
StringHashTable* oXML_ELEMENT_HASH_TABLEo = NULL;

// Hash Table mapping URI's (for namespaces) to a Hash Table
// for interning XML global attributes.
StringHashTable* oXML_GLOBAL_ATTRIBUTE_HASH_TABLEo = NULL;

void resetXmlHashTables() {
  // Resets Hashtables used for interning XML elements and global
  // attribute objects.  This will allow garbage collection of no-longer used
  // objects, but will also mean that newly parsed xml elements and global attributes
  // will not be eq? to already existing ones with the same name.
  oXML_ELEMENT_NULL_NAMESPACE_TABLEo = newStringHashTable();
  oXML_ELEMENT_HASH_TABLEo = newStringHashTable();
  oXML_GLOBAL_ATTRIBUTE_HASH_TABLEo = newStringHashTable();
}

KvCons* makeNamespaceTable() {
  return (kvCons(wrapString("xml"), wrapString(oXML_URNo), NULL));
}

Cons* makeXmlCdataForm(const char* theData) {
  { XmlSpecial* self000 = newXmlSpecial();

    self000->name = "CDATA";
    self000->surfaceForm = "CDATA";
    { XmlSpecial* tag = self000;

      return (cons(tag, cons(cons(wrapString(theData), NIL), NIL)));
    }
  }
}

XmlAttribute* makeXmlnsAttribute(const char* name) {
  { int colonPosition = stringPosition(name, ':', 0);

    if (colonPosition == NULL_INTEGER) {
      { XmlGlobalAttribute* self000 = newXmlGlobalAttribute();

        self000->name = "";
        self000->namespaceName = "xmlns";
        self000->surfaceForm = name;
        { XmlGlobalAttribute* value000 = self000;

          return (value000);
        }
      }
    }
    else {
      { XmlGlobalAttribute* self001 = newXmlGlobalAttribute();

        self001->name = stringSubsequence(name, colonPosition + 1, NULL_INTEGER);
        self001->namespaceName = "xmlns";
        self001->surfaceForm = name;
        { XmlGlobalAttribute* value001 = self001;

          return (value001);
        }
      }
    }
  }
}

XmlElement* makeXmlElementInternal(const char* name, const char* namespaceName, const char* namespacE, const char* surfaceForm) {
  { StringHashTable* nsHashTable = NULL;
    XmlElement* element = NULL;

    if (namespacE != NULL) {
      nsHashTable = ((StringHashTable*)(oXML_ELEMENT_HASH_TABLEo->lookup(namespacE)));
      if (!((boolean)(nsHashTable))) {
        nsHashTable = newStringHashTable();
        oXML_ELEMENT_HASH_TABLEo->insertAt(namespacE, nsHashTable);
      }
    }
    else {
      nsHashTable = oXML_ELEMENT_NULL_NAMESPACE_TABLEo;
    }
    element = ((XmlElement*)(nsHashTable->lookup(name)));
    if (!((boolean)(element))) {
      { XmlElement* self001 = newXmlElement();

        self001->name = name;
        self001->namespaceName = namespaceName;
        self001->namespaceUri = namespacE;
        self001->surfaceForm = surfaceForm;
        self001->elementDictionary = newKeyValueList();
        element = self001;
      }
      nsHashTable->insertAt(name, element);
    }
    return (element);
  }
}

XmlElement* makeXmlElement(const char* name, const char* namespaceName, const char* namespacE) {
  // Creates and interns an XML element object `name' using `namespace-name'
  // to refer to  `namespace'.  If `namespace' is `null', then the element will
  // be interned in the null namespace.   `namespace' must otherwise be a URI.
  if ((namespaceName == NULL) ||
      stringEqlP(namespaceName, "")) {
    return (makeXmlElementInternal(name, "", namespacE, name));
  }
  else {
    return (makeXmlElementInternal(name, namespaceName, namespacE, stringConcatenate(namespaceName, ":", 1, name)));
  }
}

XmlElement* makeXmlElementRespectingNamespace(const char* name, KvCons* namespaceTable) {
  { int colonPosition = stringPosition(name, ':', 0);
    const char* nsPart = "";
    const char* rawName = "";
    const char* namespaceUri = NULL;

    if (colonPosition == NULL_INTEGER) {
      rawName = name;
    }
    else {
      {
        nsPart = stringSubsequence(name, 0, colonPosition);
        rawName = stringSubsequence(name, colonPosition + 1, NULL_INTEGER);
      }
    }
    namespaceUri = unwrapString(((StringWrapper*)(namespaceTable->lookup(wrapString(nsPart)))));
    if ((namespaceUri == NULL) &&
        (!stringEqlP(nsPart, ""))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Undefined Namespace for Element: " << "`" << nsPart << "'";
        throw *newBadArgumentException(stream000->theStringReader());
      }
    }
    return (makeXmlElementInternal(rawName, nsPart, namespaceUri, name));
  }
}

XmlGlobalAttribute* makeXmlGlobalAttributeInternal(const char* name, const char* namespaceName, const char* namespaceUri, const char* surfaceForm) {
  if ((namespaceUri == NULL) ||
      ((namespaceName == NULL) ||
       (stringEqlP(namespaceUri, "") ||
        stringEqlP(namespaceName, "")))) {
    throw *newBadArgumentException("namespace-name and namespace must be specified");
  }
  { StringHashTable* nsHashTable = ((StringHashTable*)(oXML_GLOBAL_ATTRIBUTE_HASH_TABLEo->lookup(namespaceUri)));
    XmlAttribute* attribute = NULL;

    if (!((boolean)(nsHashTable))) {
      nsHashTable = newStringHashTable();
      oXML_GLOBAL_ATTRIBUTE_HASH_TABLEo->insertAt(namespaceUri, nsHashTable);
    }
    attribute = ((XmlAttribute*)(nsHashTable->lookup(name)));
    if (!((boolean)(attribute))) {
      { XmlGlobalAttribute* self002 = newXmlGlobalAttribute();

        self002->name = name;
        self002->namespaceName = namespaceName;
        self002->namespaceUri = namespaceUri;
        self002->surfaceForm = surfaceForm;
        attribute = self002;
      }
      nsHashTable->insertAt(name, attribute);
    }
    return (((XmlGlobalAttribute*)(attribute)));
  }
}

XmlGlobalAttribute* makeXmlGlobalAttribute(const char* name, const char* namespaceName, const char* namespacE) {
  // Creates and interns an XML global attribute object with `name' using 
  // `namespace-name' to refer to  `namespace'.  `namespace'must be a URI.
  return (makeXmlGlobalAttributeInternal(name, namespaceName, namespacE, stringConcatenate(name, ":", 1, namespaceName)));
}

XmlGlobalAttribute* makeXmlGlobalAttributeRespectingNamespace(const char* name, const char* namespaceName, const char* surfaceForm, KvCons* namespaceTable) {
  { StringWrapper* namespaceUri = ((StringWrapper*)(namespaceTable->lookup(wrapString(namespaceName))));

    if (!((boolean)(namespaceUri))) {
      throw *newBadArgumentException("Undefined Namespace for Attribute!");
    }
    return (makeXmlGlobalAttributeInternal(name, namespaceName, namespaceUri->wrapperValue, surfaceForm));
  }
}

XmlLocalAttribute* makeXmlLocalAttribute(const char* name, XmlElement* element) {
  // Make an XML-LOCAL-ATTRIBUTE named `name' associated with `element'
  { KeyValueList* dictionary = element->elementDictionary;
    XmlAttribute* attribute = ((XmlAttribute*)(dictionary->lookup(wrapString(name))));

    if (!((boolean)(attribute))) {
      { XmlLocalAttribute* self000 = newXmlLocalAttribute();

        self000->name = name;
        self000->parentElement = element;
        self000->surfaceForm = name;
        attribute = self000;
      }
      element->elementDictionary->insertAt(wrapString(name), attribute);
    }
    return (((XmlLocalAttribute*)(attribute)));
  }
}

XmlAttribute* makeXmlAttributeRespectingNamespace(const char* name, XmlElement* element, KvCons* namespaceTable) {
  { int colonPosition = stringPosition(name, ':', 0);

    if (colonPosition == NULL_INTEGER) {
      return (makeXmlLocalAttribute(name, element));
    }
    else {
      return (makeXmlGlobalAttributeRespectingNamespace(stringSubsequence(name, colonPosition + 1, NULL_INTEGER), stringSubsequence(name, 0, colonPosition), name, namespaceTable));
    }
  }
}

boolean xmlnsAttributeP(Object* attribute) {
  return (isaP(attribute, SGT_XML_STELLA_XML_GLOBAL_ATTRIBUTE) &&
      stringEqlP("xmlns", ((XmlGlobalAttribute*)(attribute))->namespaceName));
}

boolean xmlnsAttributeNameP(const char* name) {
  { int colonPosition = stringPosition(name, ':', 0);

    if (colonPosition == NULL_INTEGER) {
      return (stringEqlP(name, "xmlns"));
    }
    else {
      return (stringEqlP(stringSubsequence(name, 0, colonPosition), "xmlns"));
    }
  }
}

const char* extractXmlnsName(const char* keyname) {
  { int colonPosition = stringPosition(keyname, ':', 0);

    if (colonPosition == NULL_INTEGER) {
      return ("");
    }
    else {
      return (stringSubsequence(keyname, colonPosition + 1, NULL_INTEGER));
    }
  }
}

KeyValueList* oXML_BASE_ENTITY_TABLEo = NULL;

void addXmlReference(const char* name, const char* substitution, KeyValueList* table) {
  table->insertAt(wrapString(name), wrapString(substitution));
}

KeyValueList* makeXmlEntityTable() {
  { KeyValueList* table = newKeyValueList();

    addXmlReference("lt", "&#60;", table);
    addXmlReference("gt", "&#62;", table);
    addXmlReference("amp", "&#38;", table);
    addXmlReference("apos", "&#39;", table);
    addXmlReference("quot", "&#34;", table);
    addXmlReference("nbsp", "&#160;", table);
    return (table);
  }
}

const char* decodeXmlCharRef(const char* digits) {
  { int n = 0;
    int end = strlen(digits) - 2;

    if (digits[2] == 'x') {
      { int i = NULL_INTEGER;
        int iter000 = 3;
        int upperBound000 = end;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter000 <= upperBound000); 
              iter000 = iter000 + 1) {
          i = iter000;
          n = (n * 16) + hexCharacterValue(digits[i]);
        }
      }
    }
    else {
      { int i = NULL_INTEGER;
        int iter001 = 2;
        int upperBound001 = end;
        boolean unboundedP001 = upperBound001 == NULL_INTEGER;

        for  (; unboundedP001 ||
                  (iter001 <= upperBound001); 
              iter001 = iter001 + 1) {
          i = iter001;
          n = (n * 10) + digitValue(digits[i]);
        }
      }
    }
    return (makeString(1, (char) n));
  }
}

boolean internalDtdDefinitionP(const char* definition) {
  return ((definition[0] == '[') &&
      (definition[(strlen(definition) - 1)] == ']'));
}

InputStream* getDoctypeDefinition(Cons* doctype) {
  { const char* definition = ((StringWrapper*)(((Cons*)(doctype->rest->value))->rest->value))->wrapperValue;

    if (internalDtdDefinitionP(definition)) {
      return (newInputStringStream(stringSubsequence(definition, 1, strlen(definition) - 2)));
    }
    else {
      return (NULL);
    }
  }
}

boolean externalIdHeadP(Object* attribute) {
  // Checks to see if this `attribute' is the literal marking either
  // a PUBLIC or SYSTEM literal for an XML Elternal ID.  (See 4.2.2)
  return (isaP(attribute, SGT_XML_STELLA_STRING_WRAPPER) &&
      (stringEqlP(((StringWrapper*)(attribute))->wrapperValue, "SYSTEM") ||
       stringEqlP(((StringWrapper*)(attribute))->wrapperValue, "PUBLIC")));
}

const char* decodeXmlEntityRef(XmlDoctype* doctype, const char* name, boolean peReferenceAllowedP) {
  { StringWrapper* value = NULL;

    if (((boolean)(doctype))) {
      value = ((StringWrapper*)(doctype->entityTable->lookup(wrapString(name))));
    }
    if (!((boolean)(value))) {
      value = ((StringWrapper*)(oXML_BASE_ENTITY_TABLEo->lookup(wrapString(name))));
    }
    if (!((boolean)(value))) {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "Couldn't find entity reference for " << "`" << name << "'";
        throw *newBadArgumentException(stream000->theStringReader());
      }
    }
    else {
      return (decodeXmlString(doctype, value->wrapperValue, peReferenceAllowedP));
    }
  }
}

const char* decodeXmlParameterEntityRef(XmlDoctype* doctype, const char* name, boolean peReferenceAllowedP) {
  if (!(peReferenceAllowedP)) {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "Illegal XML Parameter Entity Reference: " << "`" << name << "'";
      throw *newBadArgumentException(stream000->theStringReader());
    }
  }
  if (!((boolean)(doctype))) {
    { OutputStringStream* stream001 = newOutputStringStream();

      *(stream001->nativeStream) << "Parameter Entity References need a Doctype object: " << "`" << name << "'";
      throw *newBadArgumentException(stream001->theStringReader());
    }
  }
  { const char* value = ((StringWrapper*)(doctype->entityTable->lookup(wrapString(name))))->wrapperValue;

    if (value != NULL) {
      return (decodeXmlString(doctype, value, peReferenceAllowedP));
    }
    else {
      { OutputStringStream* stream002 = newOutputStringStream();

        *(stream002->nativeStream) << "No Parameter Entity found to match " << "`" << name << "'";
        throw *newBadArgumentException(stream002->theStringReader());
      }
    }
  }
}

const char* decodeXmlReference(XmlDoctype* doctype, const char* reference, boolean peReferenceAllowedP) {
  if (reference[0] == '&') {
    if (reference[1] == '#') {
      return (decodeXmlCharRef(reference));
    }
    else {
      return (decodeXmlEntityRef(doctype, stringSubsequence(reference, 1, strlen(reference) - 1), peReferenceAllowedP));
    }
  }
  else {
    return (decodeXmlParameterEntityRef(doctype, stringSubsequence(reference, 1, strlen(reference) - 1), peReferenceAllowedP));
  }
}

int findReferenceStart(const char* input, int start, int end) {
  if (end == NULL_INTEGER) {
    end = strlen(input) - 1;
  }
  { int i = NULL_INTEGER;
    int iter000 = start;
    int upperBound000 = end;
    boolean unboundedP000 = upperBound000 == NULL_INTEGER;

    for  (; unboundedP000 ||
              (iter000 <= upperBound000); 
          iter000 = iter000 + 1) {
      i = iter000;
      if ((input[i] == '&') ||
          (input[i] == '%')) {
        return (i);
      }
    }
  }
  return (NULL_INTEGER);
}

const char* decodeXmlString(XmlDoctype* doctype, const char* input, boolean peReferenceAllowedP) {
  { int inputEnd = (peReferenceAllowedP ? (strlen(input) - 1) : ((int)(NULL_INTEGER)));
    int referenceStart = (peReferenceAllowedP ? findReferenceStart(input, 0, inputEnd) : stringPosition(input, '&', 0));
    const char* substitution = NULL;

    if (referenceStart == NULL_INTEGER) {
      return (input);
    }
    else {
      { OutputStringStream* buffer = newOutputStringStream();
        int referenceEnd = 0;

        if (!(peReferenceAllowedP)) {
          inputEnd = strlen(input) - 1;
        }
        while (referenceStart != NULL_INTEGER) {
          *(buffer->nativeStream) << stringSubsequence(input, referenceEnd, referenceStart);
          referenceEnd = stringPosition(input, ';', referenceStart);
          if (!(referenceEnd != NULL_INTEGER)) {
            std::cerr << "Safety violation: " << "Unterminated XML reference";
          }
          referenceEnd = referenceEnd + 1;
          substitution = decodeXmlReference(doctype, stringSubsequence(input, referenceStart, referenceEnd), peReferenceAllowedP);
          if (substitution == NULL) {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "Unrecognized entity reference: " << "`" << stringSubsequence(input, referenceStart, referenceEnd) << "'";
              throw *newBadArgumentException(stream000->theStringReader());
            }
          }
          else {
            *(buffer->nativeStream) << substitution;
          }
          referenceStart = (peReferenceAllowedP ? findReferenceStart(input, referenceEnd, inputEnd) : stringPosition(input, '&', referenceEnd));
        }
        if (!(referenceEnd == inputEnd)) {
          *(buffer->nativeStream) << stringSubsequence(input, referenceEnd, NULL_INTEGER);
        }
        return (buffer->theStringReader());
      }
    }
  }
}

const char* normalizeAttributeValue(XmlDoctype* doctype, const char* input, boolean peReferenceAllowedP) {
  return (decodeXmlString(doctype, input, peReferenceAllowedP));
}

XmlDoctype* processDoctype(Cons* doctypeDeclaration) {
  // Takes an S-Expression representing a doctype and processes into
  // a DOCTYPE object.
  if (((boolean)(doctypeDeclaration)) &&
      ((!(doctypeDeclaration == NIL)) &&
       (isaP(doctypeDeclaration->value, SGT_XML_STELLA_XML_DECLARATION) &&
        stringEqlP("DOCTYPE", ((XmlDeclaration*)(doctypeDeclaration->value))->name)))) {
    { XmlDoctype* doctype = newXmlDoctype();
      InputStream* definitionStream = NULL;
      XmlExpressionIterator* iterator = NULL;

      try {
        doctype->name = ((StringWrapper*)(((Cons*)(doctypeDeclaration->rest->value))->value))->wrapperValue;
        definitionStream = getDoctypeDefinition(doctypeDeclaration);
        if (((boolean)(definitionStream))) {
          { XmlExpressionIterator* self001 = newXmlExpressionIterator();

            self001->theStream = definitionStream;
            self001->doctypeIteratorP = true;
            self001->doctype = doctype;
            iterator = self001;
          }
          { Object* declaration = NULL;
            XmlExpressionIterator* iter000 = iterator;

            for (; iter000->nextP(); ) {
              declaration = iter000->value;
              if (isaP(((Cons*)(declaration))->value, SGT_XML_STELLA_XML_DECLARATION) &&
                  stringEqlP("ENTITY", ((XmlDeclaration*)(((Cons*)(declaration))->value))->name)) {
                { Cons* attributes = ((Cons*)(((Cons*)(declaration))->rest->value));

                  if (stringEqlP("%", ((StringWrapper*)(attributes->value))->wrapperValue)) {
                    if ((attributes->length() > 3) &&
                        externalIdHeadP(attributes->rest->rest->value)) {
                      { OutputStringStream* stream000 = newOutputStringStream();

                        *(stream000->nativeStream) << "Can't handle external entity definitions: " << "`" << declaration << "'";
                        throw *newStellaException(stream000->theStringReader());
                      }
                    }
                    else {
                      addXmlReference(((StringWrapper*)(attributes->rest->value))->wrapperValue, ((StringWrapper*)(attributes->rest->rest->value))->wrapperValue, doctype->parameterEntityTable);
                    }
                  }
                  else {
                    if ((attributes->length() > 2) &&
                        externalIdHeadP(attributes->rest->value)) {
                      { OutputStringStream* stream001 = newOutputStringStream();

                        *(stream001->nativeStream) << "Can't handle external entity definitions: " << "`" << declaration << "'";
                        throw *newStellaException(stream001->theStringReader());
                      }
                    }
                    else {
                      addXmlReference(((StringWrapper*)(attributes->value))->wrapperValue, ((StringWrapper*)(attributes->rest->value))->wrapperValue, doctype->entityTable);
                    }
                  }
                }
              }
            }
          }
        }
        if (((boolean)(definitionStream))) {
          definitionStream->free();
        }
      }
catch (...) {
        throw;
      }
      return (doctype);
    }
  }
  else {
    return (NULL);
  }
}

Cons* oXML_TOKENIZER_TABLE_DEFINITIONo = NULL;

TokenizerTable* oXML_TOKENIZER_TABLEo = NULL;

// If true, all whitespace between tags (newlines, trailing WP, etc.)
// will be preserved.  This is a kludge to allow us to read certain `illegal' XML files
// where this whitespace is significant but not appropriately encoded.
DEFINE_STELLA_SPECIAL(oXML_PRESERVE_ALL_WHITESPACEpo, boolean , false);

TokenizerTable* oXML_WHITESPACE_PRESERVING_TOKENIZER_TABLEo = NULL;

TokenizerTable* getXmlWhitespacePreservingTokenizerTable() {
  if (!((boolean)(oXML_WHITESPACE_PRESERVING_TOKENIZER_TABLEo))) {
    { Cons* tokenizerdefinition = ((Cons*)(copyConsTree(oXML_TOKENIZER_TABLE_DEFINITIONo)));

      tokenizerdefinition->secondSetter(listO(10, KWD_XML_SKIP_WHITESPACE, SYM_XML_STELLA_x, wrapString("<"), KWD_XML_OPEN_TAG, KWD_XML_EOF, KWD_XML_EOF, SYM_XML_STELLA_o, KWD_XML_OTHERWISE, KWD_XML_CONTENT, NIL));
      oXML_WHITESPACE_PRESERVING_TOKENIZER_TABLEo = parseTokenizerDefinition(tokenizerdefinition);
    }
  }
  return (oXML_WHITESPACE_PRESERVING_TOKENIZER_TABLEo);
}

TokenizerTable* getXmlTokenizerTable() {
  if (oXML_PRESERVE_ALL_WHITESPACEpo) {
    return (getXmlWhitespacePreservingTokenizerTable());
  }
  else {
    return (oXML_TOKENIZER_TABLEo);
  }
}

TokenizerToken* tokenizeXmlExpression(InputStream* stream, TokenizerToken* tokenlist, const char* regiontagname, boolean skiptoregionP, boolean& _Return1) {
  { int parenbalance = 0;
    const char* starttag = NULL;
    const char* currenttag = NULL;
    boolean regiontagfoundP = (regiontagname == NULL) ||
        (!skiptoregionP);
    boolean endoffileP = true;
    Keyword* tokentype = NULL;
    const char* tokencontent = NULL;
    TokenizerToken* tokencursor = tokenlist;

    if (!((boolean)(tokenlist))) {
      tokenlist = newTokenizerToken();
      tokencursor = tokenlist;
    }
    { TokenizerTable* tok_table_ = getXmlTokenizerTable();
      const char* tok_transitions_ = tok_table_->transitions;
      Object** tok_statenames_ = tok_table_->stateNames->theArray;
      int tok_tokenstart_ = -1;
      boolean tok_endoftokensP_ = false;
      InputStream* tok_inputstream_ = stream;
      OutputStream* tok_echostream_ = tok_inputstream_->echoStream;
      TokenizerStreamState* tok_streamstate_ = ((!((boolean)(tok_inputstream_->tokenizerState))) ? (tok_inputstream_->tokenizerState = newTokenizerStreamState()) : tok_inputstream_->tokenizerState);
      char* tok_buffer_ = tok_streamstate_->buffer;
      int tok_size_ = tok_streamstate_->bufferSize;
      int tok_state_ = tok_streamstate_->getSavedState(tok_table_);
      int tok_nextstate_ = tok_state_;
      int tok_cursor_ = tok_streamstate_->cursor;
      int tok_end_ = tok_streamstate_->end;
      int tok_checkpoint_ = ((tok_cursor_ <= tok_end_) ? tok_end_ : tok_size_);

      {
        tok_statenames_ = tok_statenames_;
        tok_endoftokensP_ = tok_endoftokensP_;
      }
      for (;;) {
        {
          tok_tokenstart_ = -1;
          for (;;) {
            if (tok_cursor_ == tok_checkpoint_) {
              if (tok_cursor_ == tok_end_) {
                tok_streamstate_->cursor = tok_cursor_;
                tok_endoftokensP_ = readIntoTokenizerBuffer(tok_inputstream_, tok_streamstate_, tok_tokenstart_);
                tok_buffer_ = tok_streamstate_->buffer;
                tok_size_ = tok_streamstate_->bufferSize;
                tok_cursor_ = integerMod(tok_streamstate_->cursor, tok_size_);
                tok_end_ = tok_streamstate_->end;
                if (tok_endoftokensP_) {
                  tok_checkpoint_ = tok_cursor_;
                  if (tok_nextstate_ == -1) {
                  }
                  else if (coerceWrappedBooleanToBoolean(((BooleanWrapper*)((tok_table_->legalEofStates->theArray)[tok_state_])))) {
                    tok_nextstate_ = -1;
                    if (!(tok_tokenstart_ == -1)) {
                      tok_endoftokensP_ = false;
                    }
                  }
                  else {
                    tok_endoftokensP_ = false;
                    tok_state_ = 0;
                    tok_nextstate_ = -1;
                  }
                  break;
                }
                if (tok_cursor_ >= tok_end_) {
                  tok_checkpoint_ = tok_size_;
                }
                else {
                  tok_checkpoint_ = tok_end_;
                }
              }
              else {
                tok_checkpoint_ = tok_end_;
                tok_cursor_ = 0;
              }
            }
            tok_nextstate_ = (int)(unsigned char) (tok_buffer_[tok_cursor_]);
            tok_nextstate_ = (int)(unsigned char) (tok_transitions_[((((tok_state_ << 8)) | tok_nextstate_))]);
            if ((tok_nextstate_ & 128) == 0) {
              tok_state_ = tok_nextstate_;
              tok_cursor_ = tok_cursor_ + 1;
            }
            else if (tok_tokenstart_ == -1) {
              if ((tok_nextstate_ & 64) == 0) {
                tok_tokenstart_ = tok_cursor_;
              }
              tok_state_ = (tok_nextstate_ & 63);
              tok_cursor_ = tok_cursor_ + 1;
            }
            else {
              break;
            }
            if (((boolean)(tok_echostream_))) {
              *(tok_echostream_->nativeStream) << tok_buffer_[(tok_cursor_ - 1)];
            }
          }
        }
        if (tok_endoftokensP_) {
          endoffileP = true;
          if (parenbalance == 0) {
            break;
          }
          if (((boolean)(tok_streamstate_))) {
            tok_streamstate_->cursor = tok_cursor_;
            tok_streamstate_->table = tok_table_;
            tok_streamstate_->state = tok_state_;
          }
          throw *newReadException("XML Expression ended prematurely");
        }
        endoffileP = false;
        tokentype = ((Keyword*)(((GeneralizedSymbol*)(tok_statenames_[tok_state_]))));
        if (regiontagfoundP) {
        }
        else if ((tokentype == KWD_XML_START_TAG) &&
            stringEqlP(getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false), regiontagname)) {
          regiontagfoundP = true;
        }
        else {
          continue;
        }
        if ((tokentype == KWD_XML_START_TAG) ||
            ((tokentype == KWD_XML_START_PI_TAG) ||
             ((tokentype == KWD_XML_START_DECLARATION_TAG) ||
              (tokentype == KWD_XML_START_SPECIAL_TAG)))) {
          tokencontent = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false);
          currenttag = tokencontent;
          if (starttag == NULL) {
            starttag = tokencontent;
          }
          if (stringEqlP(tokencontent, starttag)) {
            parenbalance = parenbalance + 1;
          }
        }
        else if (tokentype == KWD_XML_START_TAG_END) {
          tokencontent = ">";
          if ((regiontagname != NULL) &&
              skiptoregionP) {
            parenbalance = parenbalance - 1;
          }
          currenttag = NULL;
        }
        else if ((tokentype == KWD_XML_END_TAG) ||
            ((tokentype == KWD_XML_EMPTY_TAG_END) ||
             (tokentype == KWD_XML_DATA_TAG_END))) {
          if (tokentype == KWD_XML_END_TAG) {
            tokencontent = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false);
            currenttag = tokencontent;
          }
          else {
            tokencontent = ">";
          }
          if (stringEqlP(currenttag, starttag) ||
              ((regiontagname != NULL) &&
               ((!skiptoregionP) &&
                stringEqlP(currenttag, regiontagname)))) {
            parenbalance = parenbalance - 1;
          }
          currenttag = NULL;
        }
        else if (tokentype == KWD_XML_ATTRIBUTE_NAME) {
          tokencontent = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false);
        }
        else if ((tokentype == KWD_XML_QUOTED_ATTRIBUTE_VALUE) ||
            (tokentype == KWD_XML_QUOTED_DECLARATION_TAG_DATA)) {
          tokencontent = getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 1, tok_cursor_ + -1, tok_size_, false);
          tokentype = KWD_XML_ATTRIBUTE_VALUE;
        }
        else if (tokentype == KWD_XML_UNQUOTED_ATTRIBUTE_VALUE) {
          tokencontent = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false);
          tokentype = KWD_XML_ATTRIBUTE_VALUE;
        }
        else if (tokentype == KWD_XML_PI_TAG_DATA) {
          tokencontent = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_ + -1, tok_size_, false);
        }
        else if ((tokentype == KWD_XML_DECLARATION_TAG_DATA) ||
            (tokentype == KWD_XML_DECLARATION_TAG_MARKUP_DATA)) {
          tokencontent = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false);
        }
        else if (tokentype == KWD_XML_SPECIAL_TAG_DATA) {
          tokencontent = getTokenTextInternal(tok_buffer_, tok_tokenstart_ + 1, tok_cursor_ + -2, tok_size_, false);
        }
        else if (tokentype == KWD_XML_CONTENT) {
          tokencontent = getTokenTextInternal(tok_buffer_, tok_tokenstart_, tok_cursor_, tok_size_, false);
          if (!(oXML_PRESERVE_ALL_WHITESPACEpo)) {
            { int cursor = strlen(tokencontent);

              { int i = NULL_INTEGER;
                int iter000 = 0;

                for (; true; iter000 = iter000 + 1) {
                  i = iter000;
                  if (!(oCHARACTER_TYPE_TABLEo[(int)(unsigned char) (tokencontent[(cursor = cursor - 1)])] == KWD_XML_WHITE_SPACE)) {
                    if (i > 0) {
                      i = 0 - i;
                      tokencontent = getTokenTextInternal(tok_buffer_, tok_tokenstart_, ((i < 0) ? (tok_cursor_ + i) : (tok_tokenstart_ + i)), tok_size_, false);
                    }
                    break;
                  }
                }
              }
            }
          }
        }
        else if (tokentype == KWD_XML_ERROR) {
          if (((boolean)(tok_streamstate_))) {
            tok_streamstate_->cursor = tok_cursor_;
            tok_streamstate_->table = tok_table_;
            tok_streamstate_->state = tok_state_;
          }
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "Illegal XML syntax: " << "`" << tokencontent << "'";
            throw *newReadException(stream000->theStringReader());
          }
        }
        else {
          if (((boolean)(tok_streamstate_))) {
            tok_streamstate_->cursor = tok_cursor_;
            tok_streamstate_->table = tok_table_;
            tok_streamstate_->state = tok_state_;
          }
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "Illegal XML syntax: " << "`" << tokencontent << "'" << " in state " << "`" << tokentype << "'";
            throw *newReadException(stream001->theStringReader());
          }
        }
        tokencursor->type = tokentype;
        tokencursor->content = tokencontent;
        if (!((boolean)(tokencursor->next))) {
          tokencursor->next = newTokenizerToken();
        }
        tokencursor = tokencursor->next;
        if (parenbalance == 0) {
          break;
        }
        if (parenbalance < 0) {
          if ((regiontagname != NULL) &&
              ((!skiptoregionP) &&
               (stringEqlP(tokenlist->content, regiontagname) &&
                (tokenlist->next == tokencursor)))) {
            tokenlist = NULL;
            break;
          }
          else {
            if (((boolean)(tok_streamstate_))) {
              tok_streamstate_->cursor = tok_cursor_;
              tok_streamstate_->table = tok_table_;
              tok_streamstate_->state = tok_state_;
            }
            { OutputStringStream* stream002 = newOutputStringStream();

              *(stream002->nativeStream) << "Unmatched end tag encountered: " << "`" << tokencontent << "'";
              throw *newReadException(stream002->theStringReader());
            }
          }
        }
      }
      tokencursor->type = NULL;
      if (((boolean)(tok_streamstate_))) {
        tok_streamstate_->cursor = tok_cursor_;
        tok_streamstate_->table = tok_table_;
        tok_streamstate_->state = tok_state_;
      }
      if (endoffileP) {
        _Return1 = true;
        return (NULL);
      }
      else {
        _Return1 = false;
        return (tokenlist);
      }
    }
  }
}

Cons* processAttributeList(Cons* reverseattributelist, XmlElement* element, KvCons* namespaceTable) {
  if (reverseattributelist == NIL) {
    return (NIL);
  }
  { Cons* attributelist = NIL;
    Cons* conscell = NULL;
    const char* attributename = NULL;

    while (!(reverseattributelist == NIL)) {
      conscell = new Cons();
      conscell->value = reverseattributelist->value;
      reverseattributelist = reverseattributelist->rest;
      conscell->rest = attributelist;
      attributelist = conscell;
      if (reverseattributelist == NIL) {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "Malformed attribute list in XML element " << "`" << element << "'";
          throw *newBadArgumentException(stream000->theStringReader());
        }
      }
      attributename = ((TokenizerToken*)(reverseattributelist->value))->content;
      reverseattributelist = reverseattributelist->rest;
      conscell = new Cons();
      if (xmlnsAttributeNameP(attributename)) {
        conscell->value = makeXmlnsAttribute(attributename);
      }
      else {
        conscell->value = makeXmlAttributeRespectingNamespace(attributename, element, namespaceTable);
      }
      conscell->rest = attributelist;
      attributelist = conscell;
    }
    return (attributelist);
  }
}

Object* xmlTokenListToSExpression(TokenizerToken* tokenlist, XmlDoctype* doctype, boolean doctypeDefinitionP) {
  // Convert the XML `tokenList' (using `doctype' for guidance) into a
  // representative s-expression and return the result.    The `doctype' argument is
  // currently only used for expansion of entity references.  It can be 'null'.  The
  // flag `doctype-definition?' should be true only when processing the DTD definition
  // of a DOCTYPE tag, since it enables substitution of parameter entity values.
  // 
  // Every XML tag is represented as a cons-list starting with the tag as its header,
  // followed by a possibly empty list of keyword value pairs representing tag attributes,
  // followed by a possibly empty list of content expressions which might themselves
  // be XML expressions.  For example, the expression
  // 
  //     <a a1=v1 a2='v2'> foo <b a3=v3/> bar </a>
  // 
  // becomes
  // 
  //    (<a> (<a1> "v1" <a2> "v2") "foo" (<b> (<a3> "v3")) "bar")
  // 
  // when represented as an s-expression.  The tag names are subtypes of XML-OBJECT
  // such as XML-ELEMENT, XML-LOCAL-ATTRIBUTE, XML-GLOBAL-ATTRIBUTE, etc.
  // ?, ! and [ prefixed tags are encoded as their own subtypes of XML-OBJECT, namely
  // XML-PROCESSING-INSTRUCTION, XML-DECLARATION, XML-SPECIAL, XML-COMMENT, etc.
  // CDATA is an XML-SPECIAL tag with a name of CDATA.
  // 
  // The name is available using class accessors.
  { Cons* parsedtree = NULL;
    Cons* parsedtreestack = NIL;
    Object* parsedtoken = NULL;
    const char* tagname = NULL;
    XmlElement* element = NULL;
    const char* xmlnsName = NULL;
    int colonPosition = 0;
    Cons* attributelist = NIL;
    Cons* conscell = NULL;
    Keyword* tokentype = NULL;
    KvCons* namespaceTable = makeNamespaceTable();
    Cons* nsStack = NIL;

    for (;;) {
      tokentype = tokenlist->type;
      if (tokentype == KWD_XML_START_TAG) {
        if (((boolean)(parsedtree))) {
          parsedtreestack = cons(parsedtree, parsedtreestack);
        }
        nsStack = cons(namespaceTable, nsStack);
        parsedtree = NIL;
        tagname = tokenlist->content;
        tokenlist = tokenlist->next;
        continue;
      }
      else if ((tokentype == KWD_XML_START_PI_TAG) ||
          ((tokentype == KWD_XML_START_DECLARATION_TAG) ||
           (tokentype == KWD_XML_START_SPECIAL_TAG))) {
        if (((boolean)(parsedtree))) {
          parsedtreestack = cons(parsedtree, parsedtreestack);
        }
        parsedtree = NIL;
        tagname = NULL;
        if (tokentype == KWD_XML_START_PI_TAG) {
          { XmlProcessingInstruction* self000 = newXmlProcessingInstruction();

            self000->name = tokenlist->content;
            self000->surfaceForm = tokenlist->content;
            parsedtoken = self000;
          }
        }
        else if (tokentype == KWD_XML_START_DECLARATION_TAG) {
          { XmlDeclaration* self001 = newXmlDeclaration();

            self001->name = tokenlist->content;
            self001->surfaceForm = tokenlist->content;
            parsedtoken = self001;
          }
        }
        else if (tokentype == KWD_XML_START_SPECIAL_TAG) {
          { XmlSpecial* self002 = newXmlSpecial();

            self002->name = tokenlist->content;
            self002->surfaceForm = tokenlist->content;
            parsedtoken = self002;
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << tokentype << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
      else if (tokentype == KWD_XML_START_TAG_END) {
        if (tagname != NULL) {
          {
            element = makeXmlElementRespectingNamespace(tagname, namespaceTable);
            conscell = new Cons();
            conscell->value = element;
            conscell->rest = parsedtree;
            parsedtree = conscell;
            parsedtoken = processAttributeList(attributelist, element, namespaceTable);
          }
        }
        else {
          parsedtoken = ((attributelist == NIL) ? NIL : attributelist->reverse());
        }
        attributelist = NIL;
      }
      else if ((tokentype == KWD_XML_EMPTY_TAG_END) ||
          (tokentype == KWD_XML_DATA_TAG_END)) {
        if (tagname != NULL) {
          {
            element = makeXmlElementRespectingNamespace(tagname, namespaceTable);
            conscell = new Cons();
            conscell->value = element;
            conscell->rest = parsedtree;
            parsedtree = conscell;
            parsedtoken = processAttributeList(attributelist, element, namespaceTable);
          }
        }
        else {
          parsedtoken = ((attributelist == NIL) ? NIL : attributelist->reverse());
        }
        conscell = new Cons();
        conscell->value = parsedtoken;
        conscell->rest = parsedtree;
        parsedtree = conscell;
        attributelist = NIL;
        tagname = NULL;
        if (parsedtreestack == NIL) {
          parsedtree = parsedtree->reverse();
          break;
        }
        else {
          if (tokentype == KWD_XML_EMPTY_TAG_END) {
            namespaceTable = ((KvCons*)(nsStack->value));
            nsStack = nsStack->rest;
          }
          { Cons* parenttree = parsedtreestack;

            parsedtreestack = parsedtreestack->rest;
            parenttree->rest = ((Cons*)(parenttree->value));
            parenttree->firstSetter(parsedtree->reverse());
            parsedtree = parenttree;
            tokenlist = tokenlist->next;
            continue;
          }
        }
      }
      else if (tokentype == KWD_XML_END_TAG) {
        if (parsedtreestack == NIL) {
          parsedtree = parsedtree->reverse();
          break;
        }
        else {
          namespaceTable = ((KvCons*)(nsStack->value));
          nsStack = nsStack->rest;
          { Cons* parenttree = parsedtreestack;

            parsedtreestack = parsedtreestack->rest;
            parenttree->rest = ((Cons*)(parenttree->value));
            parenttree->firstSetter(parsedtree->reverse());
            parsedtree = parenttree;
            tokenlist = tokenlist->next;
            continue;
          }
        }
      }
      else if (tokentype == KWD_XML_CONTENT) {
        parsedtoken = new StringWrapper();
        ((StringWrapper*)(parsedtoken))->wrapperValue = decodeXmlString(doctype, tokenlist->content, doctypeDefinitionP);
      }
      else if (tokentype == KWD_XML_ATTRIBUTE_NAME) {
        conscell = new Cons();
        conscell->value = tokenlist;
        conscell->rest = attributelist;
        attributelist = conscell;
        if (xmlnsAttributeNameP(tokenlist->content)) {
          xmlnsName = decodeXmlString(doctype, tokenlist->content, doctypeDefinitionP);
          tokenlist = tokenlist->next;
          if (!(tokenlist->type == KWD_XML_ATTRIBUTE_VALUE)) {
            { OutputStringStream* stream001 = newOutputStringStream();

              *(stream001->nativeStream) << "Illegal XMLNS syntax, namespace value is " << "`" << tokenlist->content << "'" << " of type " << "`" << tokenlist->type << "'";
              throw *newReadException(stream001->theStringReader());
            }
          }
          colonPosition = stringPosition(xmlnsName, ':', 0);
          { const char* namespaceValue = normalizeAttributeValue(doctype, tokenlist->content, doctypeDefinitionP);

            if (colonPosition != NULL_INTEGER) {
              namespaceTable = kvCons(wrapString(stringSubsequence(xmlnsName, colonPosition + 1, NULL_INTEGER)), wrapString(namespaceValue), namespaceTable);
            }
            else if (stringEqlP(namespaceValue, "")) {
              namespaceTable = kvCons(wrapString(""), NULL, namespaceTable);
            }
            else {
              namespaceTable = kvCons(wrapString(""), wrapString(namespaceValue), namespaceTable);
            }
            parsedtoken = new StringWrapper();
            ((StringWrapper*)(parsedtoken))->wrapperValue = namespaceValue;
            conscell = new Cons();
            conscell->value = parsedtoken;
            conscell->rest = attributelist;
            attributelist = conscell;
          }
        }
        tokenlist = tokenlist->next;
        continue;
      }
      else if ((tokentype == KWD_XML_ATTRIBUTE_VALUE) ||
          (tokentype == KWD_XML_DECLARATION_TAG_DATA)) {
        parsedtoken = new StringWrapper();
        ((StringWrapper*)(parsedtoken))->wrapperValue = normalizeAttributeValue(doctype, tokenlist->content, doctypeDefinitionP);
        conscell = new Cons();
        conscell->value = parsedtoken;
        conscell->rest = attributelist;
        attributelist = conscell;
        tokenlist = tokenlist->next;
        continue;
      }
      else if ((tokentype == KWD_XML_PI_TAG_DATA) ||
          ((tokentype == KWD_XML_SPECIAL_TAG_DATA) ||
           (tokentype == KWD_XML_DECLARATION_TAG_MARKUP_DATA))) {
        parsedtoken = new StringWrapper();
        ((StringWrapper*)(parsedtoken))->wrapperValue = tokenlist->content;
        conscell = new Cons();
        conscell->value = parsedtoken;
        conscell->rest = attributelist;
        attributelist = conscell;
        tokenlist = tokenlist->next;
        continue;
      }
      else {
        { OutputStringStream* stream002 = newOutputStringStream();

          *(stream002->nativeStream) << "Illegal XML syntax: " << "`" << tokenlist->content << "'" << " of type " << "`" << tokentype << "'";
          throw *newReadException(stream002->theStringReader());
        }
      }
      if (((boolean)(parsedtree))) {
        conscell = new Cons();
        conscell->value = parsedtoken;
        conscell->rest = parsedtree;
        parsedtree = conscell;
        tokenlist = tokenlist->next;
      }
      else {
        break;
      }
    }
    if (!((boolean)(parsedtree))) {
      return (parsedtoken);
    }
    else {
      return (parsedtree);
    }
  }
}

Object* readXmlExpression(InputStream* stream, Object* startTag, boolean& _Return1) {
  // Read one balanced XML expression from `stream' and return
  // its s-expression representation (see `xml-token-list-to-s-expression').  If
  // `startTagName' is non-`null', skip all tags until a start tag matching `start-tag'
  // is encountered.  XML namespaces are ignored for outside of the start tag.
  // Use s-expression representation to specify `start-tag', e.g., '(KIF (:version "1.0"))'.
  // The tag can be an XML element object, a symbol, a string or a cons.  If the tag is a cons
  // the first element can also be (name namespace) pair.
  // 
  // Return `true' as the second value on EOF.
  // 
  // CHANGE WARNING:  It is anticipated that this function will change to
  //  a) Properly take XML namespaces into account and
  //  b) require XML element objects instead of strings as the second argument.
  // This change will not be backwards-compatible.
  { XmlExpressionIterator* iter = xmlExpressions(stream, startTag);
    Object* result = NULL;
    boolean eofP = false;

    if (iter->nextP()) {
      result = iter->value;
    }
    else {
      eofP = true;
    }
    if ((stream == STANDARD_INPUT) ||
        ((boolean)(stream->echoStream))) {
      eatNextCharacterIfWhitespace(stream);
    }
    _Return1 = eofP;
    return (result);
  }
}

Cons* readXmlExpressions(const char* filename) {
  // Read all of the top-level XML expressions from `filename' and
  // return them in a list.
  { InputFileStream* in = NULL;

    try {
      in = openInputFile(filename, 0);
      { Cons* value000 = NIL;

        { Object* item = NULL;
          XmlExpressionIterator* iter000 = xmlExpressions(in, NULL);
          Cons* collect000 = NULL;

          for  (; iter000->nextP(); ) {
            item = iter000->value;
            if (!((boolean)(collect000))) {
              {
                collect000 = cons(item, NIL);
                if (value000 == NIL) {
                  value000 = collect000;
                }
                else {
                  addConsToEndOfConsList(value000, collect000);
                }
              }
            }
            else {
              {
                collect000->rest = cons(item, NIL);
                collect000 = collect000->rest;
              }
            }
          }
        }
        { Cons* value001 = value000;

          return (value001);
        }
      }
    }
catch (...) {
      if (((boolean)(in))) {
        in->free();
      }
      throw;
    }
    if (((boolean)(in))) {
      in->free();
    }
  }
}

XmlExpressionIterator* newXmlExpressionIterator() {
  { XmlExpressionIterator* self = NULL;

    self = new XmlExpressionIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->theStream = NULL;
    self->doctypeIteratorP = false;
    self->doctype = NULL;
    self->regionMatchFunction = ((cpp_function_code)(&xmlRegionMatchesP));
    self->regionTag = NULL;
    return (self);
  }
}

void XmlExpressionIterator::free() {
  { XmlExpressionIterator* self = this;

    if (terminateStreamIteratorP(self)) {
      unmake(self);
    }
  }
}

Surrogate* XmlExpressionIterator::primaryType() {
  { XmlExpressionIterator* self = this;

    return (SGT_XML_STELLA_XML_EXPRESSION_ITERATOR);
  }
}

Object* accessXmlExpressionIteratorSlotValue(XmlExpressionIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_XML_STELLA_REGION_TAG) {
    if (setvalueP) {
      self->regionTag = ((Cons*)(value));
    }
    else {
      value = self->regionTag;
    }
  }
  else if (slotname == SYM_XML_STELLA_REGION_MATCH_FUNCTION) {
    if (setvalueP) {
      self->regionMatchFunction = ((FunctionCodeWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapFunctionCode(self->regionMatchFunction);
    }
  }
  else if (slotname == SYM_XML_STELLA_DOCTYPE) {
    if (setvalueP) {
      self->doctype = ((XmlDoctype*)(value));
    }
    else {
      value = self->doctype;
    }
  }
  else if (slotname == SYM_XML_STELLA_DOCTYPE_ITERATORp) {
    if (setvalueP) {
      self->doctypeIteratorP = coerceWrappedBooleanToBoolean(((BooleanWrapper*)(value)));
    }
    else {
      value = (self->doctypeIteratorP ? TRUE_WRAPPER : FALSE_WRAPPER);
    }
  }
  else if (slotname == SYM_XML_STELLA_VALUE) {
    if (setvalueP) {
      self->value = value;
    }
    else {
      value = self->value;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

boolean XmlExpressionIterator::nextP() {
  { XmlExpressionIterator* self = this;

    { InputStream* stream = self->theStream;
      boolean firstiterationP = self->firstIterationP;
      TokenizerToken* tokenlist = (firstiterationP ? ((TokenizerToken*)(NULL)) : stream->tokenizerState->tokenList);
      Cons* regiontag = self->regionTag;
      const char* regiontagname = (((boolean)(regiontag)) ? ((XmlElement*)(regiontag->value))->name : ((const char*)(NULL)));
      boolean skiptoregionP = false;
      boolean eofP = false;

      if (firstiterationP) {
        self->firstIterationP = false;
        if (((boolean)(regiontag))) {
          skiptoregionP = true;
        }
      }
      for (;;) {
        tokenlist = tokenizeXmlExpression(stream, tokenlist, regiontagname, skiptoregionP, eofP);
        if (eofP) {
          if (((boolean)(regiontag)) &&
              (!skiptoregionP)) {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "EOF encountered before the end of the current " << "`" << regiontagname << "'" << " region";
              throw *newReadException(stream000->theStringReader());
            }
          }
          self->value = NULL;
          closeStream(stream);
          self->theStream = NULL;
          return (false);
        }
        if (!((boolean)(tokenlist))) {
          skiptoregionP = true;
          tokenlist = stream->tokenizerState->tokenList;
          continue;
        }
        if (firstiterationP) {
          stream->tokenizerState->tokenList = tokenlist;
          firstiterationP = false;
        }
        if (skiptoregionP &&
            ((boolean)(regiontag))) {
          { TokenizerToken* lasttoken = tokenlist;
            boolean emptytagP = false;

            while (((boolean)(lasttoken->next->type))) {
              lasttoken = lasttoken->next;
            }
            if (lasttoken->type == KWD_XML_EMPTY_TAG_END) {
              emptytagP = true;
            }
            else {
              lasttoken->type = KWD_XML_EMPTY_TAG_END;
            }
            if (!((boolean  (*) (Cons*, Object*))self->regionMatchFunction)(self->regionTag, xmlTokenListToSExpression(tokenlist, self->doctype, self->doctypeIteratorP))) {
              skiptoregionP = true;
              continue;
            }
            skiptoregionP = false;
            if (emptytagP) {
              regiontag = NULL;
              regiontagname = NULL;
              self->regionTag = NULL;
            }
            continue;
          }
        }
        else {
          { Object* xmlExpression = xmlTokenListToSExpression(tokenlist, self->doctype, self->doctypeIteratorP);

            self->value = xmlExpression;
            if ((isaP(xmlExpression, SGT_XML_STELLA_CONS) &&
                isaP(((Cons*)(xmlExpression))->value, SGT_XML_STELLA_XML_DECLARATION)) &&
                stringEqlP(((XmlDeclaration*)(((Cons*)(xmlExpression))->value))->name, "DOCTYPE")) {
              if (((boolean)(self->doctype))) {
                *(STANDARD_WARNING->nativeStream) << "Warning: " << "Found a DOCTYPE declaration in an XML-EXPRESSION-ITERATOR that already has a doctype!" << std::endl;
              }
              self->doctype = processDoctype(((Cons*)(xmlExpression)));
            }
          }
          return (true);
        }
      }
    }
  }
}

Cons* XmlExpressionIterator::consify() {
  { XmlExpressionIterator* iter = this;

    { Cons* value000 = NIL;

      { Object* item = NULL;
        XmlExpressionIterator* iter000 = iter;
        Cons* collect000 = NULL;

        for  (; iter000->nextP(); ) {
          item = iter000->value;
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(item, NIL);
              if (value000 == NIL) {
                value000 = collect000;
              }
              else {
                addConsToEndOfConsList(value000, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(item, NIL);
              collect000 = collect000->rest;
            }
          }
        }
      }
      { Cons* value001 = value000;

        return (value001);
      }
    }
  }
}

boolean xmlRegionMatchesP(Cons* regionspec, Cons* regiontag) {
  if (eqlP(regionspec->value, regiontag->value)) {
    { PropertyList* specattributes = NULL;
      PropertyList* tagattributes = NULL;
      Cons* specattributesource = ((Cons*)(regionspec->rest->value));

      if (((boolean)(specattributesource)) &&
          (!(specattributesource == NIL))) {
        { PropertyList* self000 = newPropertyList();

          self000->thePlist = ((Cons*)(regionspec->rest->value));
          specattributes = self000;
        }
      }
      else {
        return (true);
      }
      { PropertyList* self001 = newPropertyList();

        self001->thePlist = ((Cons*)(regiontag->rest->value));
        tagattributes = self001;
      }
      { Object* key = NULL;
        Object* value = NULL;
        Cons* iter000 = specattributes->thePlist;

        for  (; !(iter000 == NIL); 
              iter000 = iter000->rest->rest) {
          key = iter000->value;
          value = iter000->rest->value;
          if (!eqlP(tagattributes->lookup(key), value)) {
            return (false);
          }
        }
      }
      return (true);
    }
  }
  else {
    return (false);
  }
}

XmlElement* coerceToXmlElement(Object* regiontag) {
  { Surrogate* testValue000 = safePrimaryType(regiontag);

    if (subtypeOfSymbolP(testValue000)) {
      { Object* regiontag000 = regiontag;
        Symbol* regiontag = ((Symbol*)(regiontag000));

        return (makeXmlElement(regiontag->symbolName, "", NULL));
      }
    }
    else if (subtypeOfP(testValue000, SGT_XML_STELLA_XML_ELEMENT)) {
      { Object* regiontag001 = regiontag;
        XmlElement* regiontag = ((XmlElement*)(regiontag001));

        return (regiontag);
      }
    }
    else if (subtypeOfStringP(testValue000)) {
      { Object* regiontag002 = regiontag;
        StringWrapper* regiontag = ((StringWrapper*)(regiontag002));

        return (makeXmlElement(regiontag->wrapperValue, "", NULL));
      }
    }
    else if (testValue000 == SGT_XML_STELLA_CONS) {
      { Object* regiontag003 = regiontag;
        Cons* regiontag = ((Cons*)(regiontag003));

        if (regiontag->rest == NIL) {
          return (coerceToXmlElement(regiontag->value));
        }
        else {
          { Object* name = regiontag->value;
            StringWrapper* namespacE = ((StringWrapper*)(regiontag->rest->value));

            { Surrogate* testValue001 = safePrimaryType(name);

              if (subtypeOfSymbolP(testValue001)) {
                { Object* name000 = name;
                  Symbol* name = ((Symbol*)(name000));

                  return (makeXmlElement(name->symbolName, "", namespacE->wrapperValue));
                }
              }
              else if (subtypeOfP(testValue001, SGT_XML_STELLA_XML_ELEMENT)) {
                { Object* name001 = name;
                  XmlElement* name = ((XmlElement*)(name001));

                  return (name);
                }
              }
              else if (subtypeOfStringP(testValue001)) {
                { Object* name002 = name;
                  StringWrapper* name = ((StringWrapper*)(name002));

                  return (makeXmlElement(name->wrapperValue, "", namespacE->wrapperValue));
                }
              }
              else {
                { OutputStringStream* stream000 = newOutputStringStream();

                  *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                  throw *newStellaException(stream000->theStringReader());
                }
              }
            }
          }
        }
      }
    }
    else {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
        throw *newStellaException(stream001->theStringReader());
      }
    }
  }
}

XmlExpressionIterator* xmlExpressions(InputStream* stream, Object* regiontag) {
  // Return an XML-expression-iterator (which see) reading from
  // `stream'.  `regionTag' can be used to define delimited regions from which
  // expressions should be considered. Use s-expression representation to specify
  // `regionTag', e.g., '(KIF (:version "1.0"))'.  The tag can be an XML element
  // object, a symbol, a string or a cons.  If the tag is a cons the first element
  // can also be (name namespace) pair.
  { XmlExpressionIterator* self000 = newXmlExpressionIterator();

    self000->theStream = stream;
    { XmlExpressionIterator* iterator = self000;

      if (((boolean)(regiontag))) {
        if (safePrimaryType(regiontag) == SGT_XML_STELLA_CONS) {
          { Object* regiontag000 = regiontag;
            Cons* regiontag = ((Cons*)(regiontag000));

            if (regiontag == NIL) {
            }
            else if (!((boolean)(regiontag->rest))) {
              iterator->regionTag = cons(coerceToXmlElement(regiontag->value), cons(NIL, NIL));
            }
            else if (!((boolean)(regiontag->rest->rest))) {
              iterator->regionTag = cons(coerceToXmlElement(regiontag->value), cons(regiontag->rest->value, NIL));
            }
            else {
              iterator->regionTag = cons(coerceToXmlElement(regiontag->value), cons(regiontag->rest, NIL));
            }
          }
        }
        else {
          iterator->regionTag = cons(coerceToXmlElement(regiontag), cons(NIL, NIL));
        }
      }
      return (iterator);
    }
  }
}

boolean xmlCdataP(Object* item) {
  // Return `true' if `item' is an XML CDATA tag object
  if (subtypeOfP(safePrimaryType(item), SGT_XML_STELLA_XML_SPECIAL)) {
    { Object* item000 = item;
      XmlSpecial* item = ((XmlSpecial*)(item000));

      return (stringEqlP(item->name, "CDATA"));
    }
  }
  else {
    return (false);
  }
}

boolean xmlElementP(Object* item) {
  // Return `true' if `item' is an XML element object
  return (isaP(item, SGT_XML_STELLA_XML_ELEMENT));
}

boolean xmlAttributeP(Object* item) {
  // Return `true' if `item' is an XML attribute object
  return (isaP(item, SGT_XML_STELLA_XML_ATTRIBUTE));
}

boolean xmlGlobalAttributeP(Object* item) {
  // Return `true' if `item' is an XML attribute object
  return (isaP(item, SGT_XML_STELLA_XML_GLOBAL_ATTRIBUTE));
}

boolean xmlLocalAttributeP(Object* item) {
  // Return `true' if `item' is an XML attribute object
  return (isaP(item, SGT_XML_STELLA_XML_LOCAL_ATTRIBUTE));
}

boolean xmlBaseAttributeP(Object* item) {
  // Return `true' if `item' is an XML attribute object
  return (isaP(item, SGT_XML_STELLA_XML_GLOBAL_ATTRIBUTE) &&
      (stringEqlP("base", ((XmlGlobalAttribute*)(item))->name) &&
       stringEqlP(oXML_URNo, ((XmlGlobalAttribute*)(item))->namespaceUri)));
}

boolean xmlDeclarationP(Object* item) {
  // Return `true' if `item' is an XML declaration object
  return (isaP(item, SGT_XML_STELLA_XML_DECLARATION));
}

boolean xmlProcessingInstructionP(Object* item) {
  // Return `true' if `item' is an XML processing instruction object
  return (isaP(item, SGT_XML_STELLA_XML_PROCESSING_INSTRUCTION));
}

boolean xmlElementFormP(Object* form) {
  // Return `true' if `form' is a CONS headed by an XML ELEMENT tag
  return (isaP(form, SGT_XML_STELLA_CONS) &&
      isaP(((Cons*)(form))->value, SGT_XML_STELLA_XML_ELEMENT));
}

boolean xmlProcessingInstructionFormP(Object* form) {
  // Return `true' if `form' is a CONS headed by an XML PROCESSING INSTRUCTION tag
  return (isaP(form, SGT_XML_STELLA_CONS) &&
      isaP(((Cons*)(form))->value, SGT_XML_STELLA_XML_PROCESSING_INSTRUCTION));
}

boolean xmlDeclarationFormP(Object* form) {
  // Return `true' if `form' is a CONS headed by an XML DECLARATION tag
  return (isaP(form, SGT_XML_STELLA_CONS) &&
      isaP(((Cons*)(form))->value, SGT_XML_STELLA_XML_DECLARATION));
}

boolean xmlDoctypeFormP(Object* form) {
  // Return `true' if `form' is a CONS headed by a DOCTYPE tag
  return ((isaP(form, SGT_XML_STELLA_CONS) &&
      isaP(((Cons*)(form))->value, SGT_XML_STELLA_XML_DECLARATION)) &&
      stringEqlP(((XmlDeclaration*)(((Cons*)(form))->value))->name, "DOCTYPE"));
}

boolean xmlCdataFormP(Object* form) {
  // Return `true' if `form' is a CONS headed by a CDATA tag
  return (isaP(form, SGT_XML_STELLA_CONS) &&
      xmlCdataP(((Cons*)(form))->value));
}

XmlElement* getXmlTag(Cons* expression) {
  // Return the XML tag object of an XML `expression'.
  return (((XmlElement*)(expression->value)));
}

Cons* getXmlAttributes(Cons* expression) {
  // Return the list of attributes of an XML `expression' (may be empty).
  return (((Cons*)(expression->rest->value)));
}

const char* getXmlBaseAttributeValue(Cons* expression) {
  // Return the last base url attribute in the attribute list of this
  // element if it exists.  Otherwise NULL.
  { Cons* attributeList = ((Cons*)(expression->rest->value));
    XmlAttribute* attribute = NULL;
    const char* value = NULL;
    const char* baseAttributeValue = NULL;

    while (!(attributeList == NIL)) {
      { Object* head000 = attributeList->value;

        attributeList = attributeList->rest;
        attribute = ((XmlAttribute*)(head000));
      }
      { Object* head001 = attributeList->value;

        attributeList = attributeList->rest;
        value = ((StringWrapper*)(head001))->wrapperValue;
      }
      if (isaP(attribute, SGT_XML_STELLA_XML_GLOBAL_ATTRIBUTE) &&
          (stringEqlP("base", ((XmlGlobalAttribute*)(attribute))->name) &&
           stringEqlP(oXML_URNo, ((XmlGlobalAttribute*)(attribute))->namespaceUri))) {
        baseAttributeValue = value;
      }
    }
    return (baseAttributeValue);
  }
}

Cons* getXmlContent(Cons* expression) {
  // Return the list of content elements of an XML `expression' (may be empty).
  return (expression->rest->rest);
}

const char* getXmlCdataContent(Cons* form) {
  // Return the CDATA content of a CDATA `form'.  Does NOT make sure that `form'
  // actually is a CDATA form, so bad things can happen if it is given wrong input.
  return (unwrapString(((StringWrapper*)(((Cons*)(form->rest->value))->value))));
}

boolean XmlElement::xmlElementMatchP(const char* name, const char* namespacE) {
  // Returns `true' if `tag' is an XML element with the name `name'
  // in namespace `namespace'.  Note that `namespace' is the full URI, not an abbreviation.
  // Also, `namespace' may be `null', in which case `tag' must not have a namespace
  // associated with it.
  { XmlElement* tag = this;

    return (stringEqlP(tag->name, name) &&
        stringEqlP(tag->namespaceUri, namespacE));
  }
}

boolean XmlAttribute::xmlAttributeMatchP(const char* name, const char* namespacE) {
  // Return `true' if `attribute' is an XML attribute with name `name'
  // in namespace `namespace'.  Note that `namespace' is the full URI, not an
  // abbreviation.  Also, `namespace' may be `null', in which case `attribute'
  // must not have a namespace associated with it.
  { XmlAttribute* attribute = this;

    {
      name = name;
      namespacE = namespacE;
    }
    return (false);
  }
}

boolean XmlGlobalAttribute::xmlAttributeMatchP(const char* name, const char* namespacE) {
  // Return `true' if `attribute' is a global  XML attribute with name `name'
  // in namespace `namespace'.  Note that `namespace' is the full URI, not an
  // abbreviation.  Also, `namespace' may be `null', in which case `attribute'
  // must not have a namespace associated with it.
  { XmlGlobalAttribute* attribute = this;

    return (stringEqlP(attribute->name, name) &&
        stringEqlP(attribute->namespaceUri, namespacE));
  }
}

boolean XmlLocalAttribute::xmlAttributeMatchP(const char* name, const char* namespacE) {
  // Return `true' if `attribute' is a local XML attribute with name `name'.
  // Note that `namespace' must be `null' and that the `attribute's parent element
  // element is not considered by the match.  To take the parent element into
  // account use `xml-local-attribute-match?'.
  { XmlLocalAttribute* attribute = this;

    return ((namespacE == NULL) &&
        stringEqlP(attribute->name, name));
  }
}

boolean xmlGlobalAttributeMatchP(XmlGlobalAttribute* attribute, const char* name, const char* namespacE) {
  return (stringEqlP(attribute->name, name) &&
      stringEqlP(attribute->namespaceUri, namespacE));
}

boolean xmlLocalAttributeMatchP(XmlLocalAttribute* attribute, const char* name, const char* elementName, const char* elementNamespace) {
  // Return true if `attribute' is a local attribute with `name' and whose
  // parent element matches `element-name' and `element-namespace'.
  return (stringEqlP(attribute->name, name) &&
      (stringEqlP(attribute->parentElement->name, elementName) &&
       stringEqlP(attribute->parentElement->namespaceUri, elementNamespace)));
}

const char* xmlLookupAttribute(Cons* attributes, const char* name, const char* namespacE) {
  // Find the XML attribute in `attributes' with `name' and `namespace' and
  // return its value.  Note that it is assumed that all `attributes' come from
  // the same known tag, hence, the parent elements of any local attributes are
  // not considered by the lookup.
  while (!(attributes == NIL)) {
    if (((XmlAttribute*)(attributes->value))->xmlAttributeMatchP(name, namespacE)) {
      return (unwrapString(((StringWrapper*)(attributes->rest->value))));
    }
    attributes = attributes->rest->rest;
  }
  return (NULL);
}

Cons* expandXmlTagCase(Symbol* item, Cons* clauses) {
  { Cons* outputClauses = NIL;
    Object* key = NULL;

    { Cons* clause = NULL;
      Cons* iter000 = clauses;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        clause = ((Cons*)(iter000->value));
        key = clause->value;
        { Surrogate* testValue000 = safePrimaryType(key);

          if (testValue000 == SGT_XML_STELLA_CONS) {
            { Object* key000 = key;
              Cons* key = ((Cons*)(key000));

              if (key->rest == NIL) {
                outputClauses = cons(cons(listO(3, SYM_XML_STELLA_XML_ELEMENT_MATCHp, item, cons(key->value, cons(SYM_XML_STELLA_NULL, NIL))), clause->rest->concatenate(NIL, 0)), outputClauses);
              }
              else if (key->rest->value == KWD_XML_ANY) {
                outputClauses = cons(cons(listO(4, SYM_XML_STELLA_STRING_EQLp, listO(3, SYM_XML_STELLA_NAME, item, NIL), key->value, NIL), clause->rest->concatenate(NIL, 0)), outputClauses);
              }
              else {
                outputClauses = cons(cons(listO(3, SYM_XML_STELLA_XML_ELEMENT_MATCHp, item, cons(key->value, cons(key->rest->value, NIL))), clause->rest->concatenate(NIL, 0)), outputClauses);
              }
            }
          }
          else if (subtypeOfSymbolP(testValue000)) {
            { Object* key001 = key;
              Symbol* key = ((Symbol*)(key001));

              if (key == SYM_XML_STELLA_OTHERWISE) {
                outputClauses = cons(clause, outputClauses);
              }
              else {
                outputClauses = cons(cons(listO(3, SYM_XML_STELLA_XML_ELEMENT_MATCHp, item, cons(wrapString(key->symbolName), cons(SYM_XML_STELLA_NULL, NIL))), clause->rest->concatenate(NIL, 0)), outputClauses);
              }
            }
          }
          else if (subtypeOfStringP(testValue000)) {
            { Object* key002 = key;
              StringWrapper* key = ((StringWrapper*)(key002));

              outputClauses = cons(cons(listO(3, SYM_XML_STELLA_XML_ELEMENT_MATCHp, item, cons(key, cons(SYM_XML_STELLA_NULL, NIL))), clause->rest->concatenate(NIL, 0)), outputClauses);
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
      }
    }
    return (cons(SYM_XML_STELLA_COND, outputClauses->reverse()->concatenate(NIL, 0)));
  }
}

Object* xmlTagCase(Object* item, Cons* clauses) {
  // A case form for matching `item' against XML element tags.  Each
  // element of `clauses' should be a clause with the form
  //   ("tagname" ...)     or
  //   (("tagname" "namespace-uri") ...)
  // The clause heads can optionally be symbols instead of strings.  The key forms the
  // parameters to the method `xml-element-match?', with a missing namespace argument
  // passed as NULL.
  // 
  // The namespace argument will be evaluated, so one can use bound variables in
  // place of a fixed string.   As a special case, if the namespace argument is
  // :ANY, then the test will be done for a match on the tag name alone.
  if (isaP(item, SGT_XML_STELLA_SYMBOL)) {
    return (expandXmlTagCase(((Symbol*)(item)), clauses));
  }
  else {
    { Symbol* var = localGensym("ITEM");

      return (listO(4, SYM_XML_STELLA_LET, cons(cons(var, listO(3, SYM_XML_STELLA_XML_ELEMENT, item, NIL)), NIL), expandXmlTagCase(var, clauses), NIL));
    }
  }
}

void printXmlNonElementAttributes(OutputStream* stream, Cons* attributes) {
  { boolean lastWasAttributeP = false;

    { Object* item = NULL;
      Cons* iter000 = attributes;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        item = iter000->value;
        { Surrogate* testValue000 = safePrimaryType(item);

          if (subtypeOfP(testValue000, SGT_XML_STELLA_XML_ATTRIBUTE)) {
            { Object* item000 = item;
              XmlAttribute* item = ((XmlAttribute*)(item000));

              *(stream->nativeStream) << " " << item->surfaceForm;
              lastWasAttributeP = true;
            }
          }
          else if (subtypeOfStringP(testValue000)) {
            { Object* item001 = item;
              StringWrapper* item = ((StringWrapper*)(item001));

              if (lastWasAttributeP) {
                *(stream->nativeStream) << "=";
              }
              else {
                *(stream->nativeStream) << " ";
              }
              *(stream->nativeStream) << item->wrapperValue;
              lastWasAttributeP = false;
            }
          }
          else {
            { OutputStringStream* stream000 = newOutputStringStream();

              *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
              throw *newStellaException(stream000->theStringReader());
            }
          }
        }
      }
    }
  }
}

void printXmlElementAttributes(OutputStream* stream, Cons* attributes) {
  { Object* item = NULL;
    Cons* iter000 = attributes;

    for (; !(iter000 == NIL); iter000 = iter000->rest) {
      item = iter000->value;
      { Surrogate* testValue000 = safePrimaryType(item);

        if (subtypeOfP(testValue000, SGT_XML_STELLA_XML_ATTRIBUTE)) {
          { Object* item000 = item;
            XmlAttribute* item = ((XmlAttribute*)(item000));

            *(stream->nativeStream) << " " << item->surfaceForm << "=";
          }
        }
        else if (subtypeOfStringP(testValue000)) {
          { Object* item001 = item;
            StringWrapper* item = ((StringWrapper*)(item001));

            *(stream->nativeStream) << "\"";
            { boolean foundP000 = false;

              { char ch = NULL_CHARACTER;
                const char* vector000 = item->wrapperValue;
                int index000 = 0;
                int length000 = strlen(vector000);

                for  (; index000 < length000; 
                      index000 = index000 + 1) {
                  ch = vector000[index000];
                  if (htmlCharacterNeedsQuotingP(ch)) {
                    foundP000 = true;
                    break;
                  }
                }
              }
              if (foundP000) {
                writeHtmlQuotingSpecialCharacters(stream->nativeStream, item->wrapperValue);
              }
              else {
                *(stream->nativeStream) << item->wrapperValue;
              }
            }
            *(stream->nativeStream) << "\"";
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
  }
}

void printXmlExpression(OutputStream* stream, Cons* xmlExpression, int indent) {
  // Prints `xml-expression' on `stream'.  Indentation begins with the
  // value of `indent'.  If this is the `null' integer, no indentation is
  // performed.  Otherwise it should normally be specified as 0 (zero) for
  // top-level calls.
  // 
  // It is assumed that the `xml-expression' is a well-formed CONS-list
  // representation of an XML  form.  It expects a form like that form
  // returned by `read-XML-expression'.
  // 
  // Also handles a list of xml forms such as that returned by `XML-expressions'.
  // In that case, each of the forms is indented by `indent' spaces.
  if (isaP(xmlExpression->value, SGT_XML_STELLA_CONS)) {
    { Object* exp = NULL;
      Cons* iter000 = xmlExpression;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        exp = iter000->value;
        printXmlExpression(stream, ((Cons*)(exp)), indent);
      }
    }
    return;
  }
  { XmlObject* tag = ((XmlObject*)(xmlExpression->value));
    Cons* attributes = ((Cons*)(xmlExpression->rest->value));
    const char* tagname = tag->surfaceForm;
    boolean previousItemWasStringP = false;
    boolean inContentFieldP = false;

    if (indent != NULL_INTEGER) {
      { int i = NULL_INTEGER;
        int iter001 = 1;
        int upperBound000 = indent;
        boolean unboundedP000 = upperBound000 == NULL_INTEGER;

        for  (; unboundedP000 ||
                  (iter001 <= upperBound000); 
              iter001 = iter001 + 1) {
          i = iter001;
          i = i;
          *(stream->nativeStream) << " ";
        }
      }
    }
    { Surrogate* testValue000 = safePrimaryType(tag);

      if (subtypeOfP(testValue000, SGT_XML_STELLA_XML_PROCESSING_INSTRUCTION)) {
        { XmlObject* tag000 = tag;
          XmlProcessingInstruction* tag = ((XmlProcessingInstruction*)(tag000));

          *(stream->nativeStream) << "<?" << tagname;
          printXmlNonElementAttributes(stream, attributes);
          *(stream->nativeStream) << "?>" << std::endl;
        }
      }
      else if (subtypeOfP(testValue000, SGT_XML_STELLA_XML_DECLARATION)) {
        { XmlObject* tag001 = tag;
          XmlDeclaration* tag = ((XmlDeclaration*)(tag001));

          *(stream->nativeStream) << "<!" << tagname;
          printXmlNonElementAttributes(stream, attributes);
          *(stream->nativeStream) << ">" << std::endl;
        }
      }
      else if (subtypeOfP(testValue000, SGT_XML_STELLA_XML_SPECIAL)) {
        { XmlObject* tag002 = tag;
          XmlSpecial* tag = ((XmlSpecial*)(tag002));

          *(stream->nativeStream) << "<![" << tagname << "[";
          if (stringEqlP(tagname, "CDATA")) {
            *(stream->nativeStream) << unwrapString(((StringWrapper*)(attributes->value)));
          }
          else {
            printXmlNonElementAttributes(stream, attributes);
          }
          *(stream->nativeStream) << "]]>";
        }
      }
      else if (subtypeOfP(testValue000, SGT_XML_STELLA_XML_ELEMENT)) {
        { XmlObject* tag003 = tag;
          XmlElement* tag = ((XmlElement*)(tag003));

          if (xmlExpression->rest == NIL) {
            *(stream->nativeStream) << "<" << tagname << "/>" << std::endl;
          }
          else {
            *(stream->nativeStream) << "<" << tagname;
            printXmlElementAttributes(stream, ((Cons*)(xmlExpression->rest->value)));
            previousItemWasStringP = false;
            if (indent != NULL_INTEGER) {
              indent = indent + 2;
            }
            { Object* item = NULL;
              Cons* iter002 = xmlExpression->rest->rest;

              for (; !(iter002 == NIL); iter002 = iter002->rest) {
                item = iter002->value;
                { Surrogate* testValue001 = safePrimaryType(item);

                  if (testValue001 == SGT_XML_STELLA_CONS) {
                    { Object* item000 = item;
                      Cons* item = ((Cons*)(item000));

                      if (xmlCdataP(item->value)) {
                        {
                          if (!(inContentFieldP)) {
                            *(stream->nativeStream) << ">";
                            inContentFieldP = true;
                          }
                          printXmlExpression(stream, item, 0);
                          previousItemWasStringP = true;
                        }
                      }
                      else {
                        {
                          if (!(inContentFieldP)) {
                            *(stream->nativeStream) << ">" << std::endl;
                            inContentFieldP = true;
                          }
                          printXmlExpression(stream, item, indent);
                          previousItemWasStringP = false;
                        }
                      }
                    }
                  }
                  else if (subtypeOfStringP(testValue001)) {
                    { Object* item001 = item;
                      StringWrapper* item = ((StringWrapper*)(item001));

                      if (!(inContentFieldP)) {
                        *(stream->nativeStream) << ">";
                        inContentFieldP = true;
                      }
                      if (previousItemWasStringP) {
                        *(stream->nativeStream) << " ";
                      }
                      { boolean foundP000 = false;

                        { char ch = NULL_CHARACTER;
                          const char* vector000 = item->wrapperValue;
                          int index000 = 0;
                          int length000 = strlen(vector000);

                          for  (; index000 < length000; 
                                index000 = index000 + 1) {
                            ch = vector000[index000];
                            if (htmlCharacterNeedsQuotingP(ch)) {
                              foundP000 = true;
                              break;
                            }
                          }
                        }
                        if (foundP000) {
                          writeHtmlQuotingSpecialCharacters(stream->nativeStream, item->wrapperValue);
                        }
                        else {
                          *(stream->nativeStream) << item->wrapperValue;
                        }
                      }
                      previousItemWasStringP = true;
                    }
                  }
                  else {
                    { OutputStringStream* stream000 = newOutputStringStream();

                      *(stream000->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
                      throw *newStellaException(stream000->theStringReader());
                    }
                  }
                }
              }
            }
            if (inContentFieldP) {
              {
                if (indent != NULL_INTEGER) {
                  indent = indent - 2;
                  if (!(previousItemWasStringP)) {
                    { int i = NULL_INTEGER;
                      int iter003 = 1;
                      int upperBound001 = indent;
                      boolean unboundedP001 = upperBound001 == NULL_INTEGER;

                      for  (; unboundedP001 ||
                                (iter003 <= upperBound001); 
                            iter003 = iter003 + 1) {
                        i = iter003;
                        i = i;
                        *(stream->nativeStream) << " ";
                      }
                    }
                  }
                }
                *(stream->nativeStream) << "</" << tagname << ">";
                if ((indent != NULL_INTEGER) &&
                    (indent > 0)) {
                  *(stream->nativeStream) << std::endl;
                }
              }
            }
            else {
              *(stream->nativeStream) << "/>" << std::endl;
            }
          }
        }
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream001->theStringReader());
        }
      }
    }
  }
}

void helpStartupXml1() {
  {
    SGT_XML_STELLA_XML_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("XML-OBJECT", NULL, 1)));
    SYM_XML_STELLA_NAME = ((Symbol*)(internRigidSymbolWrtModule("NAME", NULL, 0)));
    SYM_XML_STELLA_SURFACE_FORM = ((Symbol*)(internRigidSymbolWrtModule("SURFACE-FORM", NULL, 0)));
    SGT_XML_STELLA_XML_ELEMENT = ((Surrogate*)(internRigidSymbolWrtModule("XML-ELEMENT", NULL, 1)));
    SYM_XML_STELLA_NAMESPACE_NAME = ((Symbol*)(internRigidSymbolWrtModule("NAMESPACE-NAME", NULL, 0)));
    SYM_XML_STELLA_NAMESPACE_URI = ((Symbol*)(internRigidSymbolWrtModule("NAMESPACE-URI", NULL, 0)));
    SYM_XML_STELLA_ELEMENT_DICTIONARY = ((Symbol*)(internRigidSymbolWrtModule("ELEMENT-DICTIONARY", NULL, 0)));
    SGT_XML_STELLA_XML_LOCAL_ATTRIBUTE = ((Surrogate*)(internRigidSymbolWrtModule("XML-LOCAL-ATTRIBUTE", NULL, 1)));
    SYM_XML_STELLA_PARENT_ELEMENT = ((Symbol*)(internRigidSymbolWrtModule("PARENT-ELEMENT", NULL, 0)));
    SGT_XML_STELLA_XML_GLOBAL_ATTRIBUTE = ((Surrogate*)(internRigidSymbolWrtModule("XML-GLOBAL-ATTRIBUTE", NULL, 1)));
    SGT_XML_STELLA_XML_PROCESSING_INSTRUCTION = ((Surrogate*)(internRigidSymbolWrtModule("XML-PROCESSING-INSTRUCTION", NULL, 1)));
    SYM_XML_STELLA_DATA = ((Symbol*)(internRigidSymbolWrtModule("DATA", NULL, 0)));
    SGT_XML_STELLA_XML_DECLARATION = ((Surrogate*)(internRigidSymbolWrtModule("XML-DECLARATION", NULL, 1)));
    SGT_XML_STELLA_XML_DOCTYPE_DECLARATION = ((Surrogate*)(internRigidSymbolWrtModule("XML-DOCTYPE-DECLARATION", NULL, 1)));
    SGT_XML_STELLA_XML_SPECIAL = ((Surrogate*)(internRigidSymbolWrtModule("XML-SPECIAL", NULL, 1)));
    SGT_XML_STELLA_XML_COMMENT = ((Surrogate*)(internRigidSymbolWrtModule("XML-COMMENT", NULL, 1)));
    SGT_XML_STELLA_XML_DOCTYPE = ((Surrogate*)(internRigidSymbolWrtModule("XML-DOCTYPE", NULL, 1)));
    SYM_XML_STELLA_ENTITY_TABLE = ((Symbol*)(internRigidSymbolWrtModule("ENTITY-TABLE", NULL, 0)));
    SYM_XML_STELLA_PARAMETER_ENTITY_TABLE = ((Symbol*)(internRigidSymbolWrtModule("PARAMETER-ENTITY-TABLE", NULL, 0)));
    SGT_XML_STELLA_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("STRING-WRAPPER", NULL, 1)));
    KWD_XML_START = ((Keyword*)(internRigidSymbolWrtModule("START", NULL, 2)));
    KWD_XML_INCLUDE = ((Keyword*)(internRigidSymbolWrtModule("INCLUDE", NULL, 2)));
    KWD_XML_SKIP_WHITESPACE = ((Keyword*)(internRigidSymbolWrtModule("SKIP-WHITESPACE", NULL, 2)));
    SYM_XML_STELLA_x = ((Symbol*)(internRigidSymbolWrtModule("!", NULL, 0)));
    KWD_XML_OPEN_TAG = ((Keyword*)(internRigidSymbolWrtModule("OPEN-TAG", NULL, 2)));
    KWD_XML_EOF = ((Keyword*)(internRigidSymbolWrtModule("EOF", NULL, 2)));
    SYM_XML_STELLA_o = ((Symbol*)(internRigidSymbolWrtModule("*", NULL, 0)));
    KWD_XML_OTHERWISE = ((Keyword*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 2)));
    KWD_XML_CONTENT = ((Keyword*)(internRigidSymbolWrtModule("CONTENT", NULL, 2)));
    KWD_XML_START_TAG_END = ((Keyword*)(internRigidSymbolWrtModule("START-TAG-END", NULL, 2)));
    KWD_XML_OPEN_END_TAG = ((Keyword*)(internRigidSymbolWrtModule("OPEN-END-TAG", NULL, 2)));
    KWD_XML_OPEN_PI_TAG = ((Keyword*)(internRigidSymbolWrtModule("OPEN-PI-TAG", NULL, 2)));
    KWD_XML_OPEN_DECLARATION_TAG = ((Keyword*)(internRigidSymbolWrtModule("OPEN-DECLARATION-TAG", NULL, 2)));
    KWD_XML_START_TAG = ((Keyword*)(internRigidSymbolWrtModule("START-TAG", NULL, 2)));
    KWD_XML_OPEN_EMPTY_TAG_END = ((Keyword*)(internRigidSymbolWrtModule("OPEN-EMPTY-TAG-END", NULL, 2)));
    KWD_XML_SKIP_TO_ATTRIBUTE_NAME = ((Keyword*)(internRigidSymbolWrtModule("SKIP-TO-ATTRIBUTE-NAME", NULL, 2)));
    KWD_XML_ANY = ((Keyword*)(internRigidSymbolWrtModule("ANY", NULL, 2)));
    KWD_XML_START_PI_TAG = ((Keyword*)(internRigidSymbolWrtModule("START-PI-TAG", NULL, 2)));
    KWD_XML_OPEN_PI_TAG_END = ((Keyword*)(internRigidSymbolWrtModule("OPEN-PI-TAG-END", NULL, 2)));
    KWD_XML_PI_TAG_DATA = ((Keyword*)(internRigidSymbolWrtModule("PI-TAG-DATA", NULL, 2)));
    KWD_XML_PI_TAG_DATA_OR_END = ((Keyword*)(internRigidSymbolWrtModule("PI-TAG-DATA-OR-END", NULL, 2)));
    KWD_XML_EMPTY_TAG_END = ((Keyword*)(internRigidSymbolWrtModule("EMPTY-TAG-END", NULL, 2)));
    KWD_XML_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    KWD_XML_END_TAG_END = ((Keyword*)(internRigidSymbolWrtModule("END-TAG-END", NULL, 2)));
    KWD_XML_END_TAG = ((Keyword*)(internRigidSymbolWrtModule("END-TAG", NULL, 2)));
    KWD_XML_ATTRIBUTE_NAME = ((Keyword*)(internRigidSymbolWrtModule("ATTRIBUTE-NAME", NULL, 2)));
    KWD_XML_SKIP_TO_ATTRIBUTE_VALUE = ((Keyword*)(internRigidSymbolWrtModule("SKIP-TO-ATTRIBUTE-VALUE", NULL, 2)));
    KWD_XML_SINGLE_QUOTED_ATTRIBUTE_VALUE = ((Keyword*)(internRigidSymbolWrtModule("SINGLE-QUOTED-ATTRIBUTE-VALUE", NULL, 2)));
    KWD_XML_DOUBLE_QUOTED_ATTRIBUTE_VALUE = ((Keyword*)(internRigidSymbolWrtModule("DOUBLE-QUOTED-ATTRIBUTE-VALUE", NULL, 2)));
    KWD_XML_UNQUOTED_ATTRIBUTE_VALUE = ((Keyword*)(internRigidSymbolWrtModule("UNQUOTED-ATTRIBUTE-VALUE", NULL, 2)));
    KWD_XML_QUOTED_ATTRIBUTE_VALUE = ((Keyword*)(internRigidSymbolWrtModule("QUOTED-ATTRIBUTE-VALUE", NULL, 2)));
    KWD_XML_START_TAG_OR_COMMENT = ((Keyword*)(internRigidSymbolWrtModule("START-TAG-OR-COMMENT", NULL, 2)));
    KWD_XML_OPEN_SPECIAL_TAG = ((Keyword*)(internRigidSymbolWrtModule("OPEN-SPECIAL-TAG", NULL, 2)));
    KWD_XML_START_DECLARATION_TAG = ((Keyword*)(internRigidSymbolWrtModule("START-DECLARATION-TAG", NULL, 2)));
    KWD_XML_DECLARATION_WHITESPACE = ((Keyword*)(internRigidSymbolWrtModule("DECLARATION-WHITESPACE", NULL, 2)));
    KWD_XML_DECLARATION_TAG_MARKUP_DATA_START = ((Keyword*)(internRigidSymbolWrtModule("DECLARATION-TAG-MARKUP-DATA-START", NULL, 2)));
    KWD_XML_SINGLE_QUOTED_DECLARATION_TAG_DATA = ((Keyword*)(internRigidSymbolWrtModule("SINGLE-QUOTED-DECLARATION-TAG-DATA", NULL, 2)));
    KWD_XML_DOUBLE_QUOTED_DECLARATION_TAG_DATA = ((Keyword*)(internRigidSymbolWrtModule("DOUBLE-QUOTED-DECLARATION-TAG-DATA", NULL, 2)));
    KWD_XML_DECLARATION_TAG_DATA = ((Keyword*)(internRigidSymbolWrtModule("DECLARATION-TAG-DATA", NULL, 2)));
    KWD_XML_QUOTED_DECLARATION_TAG_DATA = ((Keyword*)(internRigidSymbolWrtModule("QUOTED-DECLARATION-TAG-DATA", NULL, 2)));
  }
}

void helpStartupXml2() {
  {
    KWD_XML_DECLARATION_TAG_MARKUP_DATA = ((Keyword*)(internRigidSymbolWrtModule("DECLARATION-TAG-MARKUP-DATA", NULL, 2)));
    KWD_XML_START_SPECIAL_TAG = ((Keyword*)(internRigidSymbolWrtModule("START-SPECIAL-TAG", NULL, 2)));
    KWD_XML_SPECIAL_TAG_DATA = ((Keyword*)(internRigidSymbolWrtModule("SPECIAL-TAG-DATA", NULL, 2)));
    KWD_XML_SPECIAL_TAG_DATA_OR_END = ((Keyword*)(internRigidSymbolWrtModule("SPECIAL-TAG-DATA-OR-END", NULL, 2)));
    KWD_XML_SPECIAL_TAG_DATA_OR_END2 = ((Keyword*)(internRigidSymbolWrtModule("SPECIAL-TAG-DATA-OR-END2", NULL, 2)));
    KWD_XML_DATA_TAG_END = ((Keyword*)(internRigidSymbolWrtModule("DATA-TAG-END", NULL, 2)));
    KWD_XML_COMMENT_BODY = ((Keyword*)(internRigidSymbolWrtModule("COMMENT-BODY", NULL, 2)));
    KWD_XML_END_COMMENT_OR_COMMENT = ((Keyword*)(internRigidSymbolWrtModule("END-COMMENT-OR-COMMENT", NULL, 2)));
    KWD_XML_END_COMMENT_OR_COMMENT2 = ((Keyword*)(internRigidSymbolWrtModule("END-COMMENT-OR-COMMENT2", NULL, 2)));
    KWD_XML_COMMENT = ((Keyword*)(internRigidSymbolWrtModule("COMMENT", NULL, 2)));
    KWD_XML_ATTRIBUTE_VALUE = ((Keyword*)(internRigidSymbolWrtModule("ATTRIBUTE-VALUE", NULL, 2)));
    KWD_XML_WHITE_SPACE = ((Keyword*)(internRigidSymbolWrtModule("WHITE-SPACE", NULL, 2)));
    SGT_XML_STELLA_XML_EXPRESSION_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("XML-EXPRESSION-ITERATOR", NULL, 1)));
    SYM_XML_STELLA_REGION_TAG = ((Symbol*)(internRigidSymbolWrtModule("REGION-TAG", NULL, 0)));
    SYM_XML_STELLA_REGION_MATCH_FUNCTION = ((Symbol*)(internRigidSymbolWrtModule("REGION-MATCH-FUNCTION", NULL, 0)));
    SYM_XML_STELLA_DOCTYPE = ((Symbol*)(internRigidSymbolWrtModule("DOCTYPE", NULL, 0)));
    SYM_XML_STELLA_DOCTYPE_ITERATORp = ((Symbol*)(internRigidSymbolWrtModule("DOCTYPE-ITERATOR?", NULL, 0)));
    SYM_XML_STELLA_VALUE = ((Symbol*)(internRigidSymbolWrtModule("VALUE", NULL, 0)));
    SGT_XML_STELLA_CONS = ((Surrogate*)(internRigidSymbolWrtModule("CONS", NULL, 1)));
    SGT_XML_STELLA_XML_ATTRIBUTE = ((Surrogate*)(internRigidSymbolWrtModule("XML-ATTRIBUTE", NULL, 1)));
    SYM_XML_STELLA_XML_ELEMENT_MATCHp = ((Symbol*)(internRigidSymbolWrtModule("XML-ELEMENT-MATCH?", NULL, 0)));
    SYM_XML_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    SYM_XML_STELLA_STRING_EQLp = ((Symbol*)(internRigidSymbolWrtModule("STRING-EQL?", NULL, 0)));
    SYM_XML_STELLA_OTHERWISE = ((Symbol*)(internRigidSymbolWrtModule("OTHERWISE", NULL, 0)));
    SYM_XML_STELLA_COND = ((Symbol*)(internRigidSymbolWrtModule("COND", NULL, 0)));
    SGT_XML_STELLA_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("SYMBOL", NULL, 1)));
    SYM_XML_STELLA_LET = ((Symbol*)(internRigidSymbolWrtModule("LET", NULL, 0)));
    SYM_XML_STELLA_XML_ELEMENT = ((Symbol*)(internRigidSymbolWrtModule("XML-ELEMENT", NULL, 0)));
    SYM_XML_STELLA_STARTUP_XML = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-XML", NULL, 0)));
    SYM_XML_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupXml3() {
  {
    { Class* clasS = defineClassFromStringifiedSource("XML-OBJECT", "(DEFCLASS XML-OBJECT (STANDARD-OBJECT) :PUBLIC-SLOTS ((NAME :TYPE STRING) (SURFACE-FORM :TYPE STRING)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newXmlObject));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessXmlObjectSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("XML-ELEMENT", "(DEFCLASS XML-ELEMENT (XML-OBJECT) :PUBLIC-SLOTS ((NAMESPACE-NAME :TYPE STRING) (NAMESPACE-URI :TYPE STRING) (ELEMENT-DICTIONARY :TYPE (KEY-VALUE-LIST OF STRING-WRAPPER XML-ATTRIBUTE))) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"<\" (SURFACE-FORM SELF) \">\"))");

      clasS->classConstructorCode = ((cpp_function_code)(&newXmlElement));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessXmlElementSlotValue));
    }
    defineClassFromStringifiedSource("XML-ATTRIBUTE", "(DEFCLASS XML-ATTRIBUTE (XML-OBJECT) :ABSTRACT? TRUE :PUBLIC-SLOTS ((NAME :TYPE STRING) (SURFACE-FORM :TYPE STRING)) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"<\" (SURFACE-FORM SELF) \">\"))");
    { Class* clasS = defineClassFromStringifiedSource("XML-LOCAL-ATTRIBUTE", "(DEFCLASS XML-LOCAL-ATTRIBUTE (XML-ATTRIBUTE) :PUBLIC-SLOTS ((PARENT-ELEMENT :TYPE XML-ELEMENT)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newXmlLocalAttribute));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessXmlLocalAttributeSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("XML-GLOBAL-ATTRIBUTE", "(DEFCLASS XML-GLOBAL-ATTRIBUTE (XML-ATTRIBUTE) :PUBLIC-SLOTS ((NAMESPACE-NAME :TYPE STRING) (NAMESPACE-URI :TYPE STRING)))");

      clasS->classConstructorCode = ((cpp_function_code)(&newXmlGlobalAttribute));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessXmlGlobalAttributeSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("XML-PROCESSING-INSTRUCTION", "(DEFCLASS XML-PROCESSING-INSTRUCTION (XML-OBJECT) :PUBLIC-SLOTS ((DATA :TYPE STRING)) :PRINT-FORM (IF (NULL? (DATA SELF)) (PRINT-NATIVE-STREAM STREAM \"<?\" (SURFACE-FORM SELF) \">\") (PRINT-NATIVE-STREAM STREAM \"<?\" (SURFACE-FORM SELF) \" \" (DATA SELF) \">\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newXmlProcessingInstruction));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessXmlProcessingInstructionSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("XML-DECLARATION", "(DEFCLASS XML-DECLARATION (XML-OBJECT) :PUBLIC-SLOTS ((DATA :TYPE STRING)) :PRINT-FORM (IF (NULL? (DATA SELF)) (PRINT-NATIVE-STREAM STREAM \"<!\" (SURFACE-FORM SELF) \">\") (PRINT-NATIVE-STREAM STREAM \"<!\" (SURFACE-FORM SELF) \" \" (DATA SELF) \">\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newXmlDeclaration));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessXmlDeclarationSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("XML-DOCTYPE-DECLARATION", "(DEFCLASS XML-DOCTYPE-DECLARATION (XML-DECLARATION) :PRINT-FORM (IF (NULL? (DATA SELF)) (PRINT-NATIVE-STREAM STREAM \"<!\" (SURFACE-FORM SELF) \">\") (PRINT-NATIVE-STREAM STREAM \"<!\" (SURFACE-FORM SELF) \" ...>\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newXmlDoctypeDeclaration));
    }
    { Class* clasS = defineClassFromStringifiedSource("XML-SPECIAL", "(DEFCLASS XML-SPECIAL (XML-OBJECT) :PUBLIC-SLOTS ((DATA :TYPE STRING)) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"<!\" (SURFACE-FORM SELF) \">\"))");

      clasS->classConstructorCode = ((cpp_function_code)(&newXmlSpecial));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessXmlSpecialSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("XML-COMMENT", "(DEFCLASS XML-COMMENT (XML-OBJECT) :PRINT-FORM (IF (NULL? (SURFACE-FORM SELF)) (PRINT-NATIVE-STREAM STREAM \"<!-- -->\") (PRINT-NATIVE-STREAM STREAM \"<!-- \" (LENGTH (SURFACE-FORM SELF)) \" chars -->\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newXmlComment));
    }
    { Class* clasS = defineClassFromStringifiedSource("XML-DOCTYPE", "(DEFCLASS XML-DOCTYPE (STANDARD-OBJECT) :PUBLIC-SLOTS ((NAME :TYPE STRING) (ENTITY-TABLE :TYPE (KEY-VALUE-LIST OF STRING-WRAPPER STRING-WRAPPER) :INITIALLY (NEW KEY-VALUE-LIST)) (PARAMETER-ENTITY-TABLE :TYPE (KEY-VALUE-LIST OF STRING-WRAPPER STRING-WRAPPER) :INITIALLY (NEW KEY-VALUE-LIST))) :PRINT-FORM (PRINT-NATIVE-STREAM STREAM \"<!DOCTYPE \" (NAME SELF) \">\"))");

      clasS->classConstructorCode = ((cpp_function_code)(&newXmlDoctype));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessXmlDoctypeSlotValue));
    }
    { Class* clasS = defineClassFromStringifiedSource("XML-EXPRESSION-ITERATOR", "(DEFCLASS XML-EXPRESSION-ITERATOR (STREAM-ITERATOR) :DOCUMENTATION \"Iterator that yields XML expressions from an input stream.\nIf the value of `region-tag' is non-`null', only XML expressions enclosed within\nmatching region tags will be returned (there can be multiple such regions).\nWhat is a match is determined by `region-match-function'.  Usually, region tags\nwill/should be at the top level, but this is not necessarily so and also not\nenforced by the iterator.\" :PARAMETERS ((ANY-VALUE :TYPE OBJECT)) :PUBLIC? TRUE :SLOTS ((REGION-TAG :TYPE CONS) (REGION-MATCH-FUNCTION :TYPE FUNCTION-CODE :INITIALLY (THE-CODE :FUNCTION XML-REGION-MATCHES?)) (DOCTYPE :TYPE XML-DOCTYPE) (DOCTYPE-ITERATOR? :TYPE BOOLEAN :INITIALLY FALSE :DOCUMENTATION \"Set to `true' when iterating over a DTD definition.\")))");

      clasS->classConstructorCode = ((cpp_function_code)(&newXmlExpressionIterator));
      clasS->classSlotAccessorCode = ((cpp_function_code)(&accessXmlExpressionIteratorSlotValue));
    }
  }
}

void helpStartupXml4() {
  {
    defineFunctionObject("RESET-XML-HASH-TABLES", "(DEFUN RESET-XML-HASH-TABLES () :PUBLIC? TRUE :DOCUMENTATION \"Resets Hashtables used for interning XML elements and global\nattribute objects.  This will allow garbage collection of no-longer used\nobjects, but will also mean that newly parsed xml elements and global attributes\nwill not be eq? to already existing ones with the same name.\")", ((cpp_function_code)(&resetXmlHashTables)), NULL);
    defineFunctionObject("MAKE-NAMESPACE-TABLE", "(DEFUN (MAKE-NAMESPACE-TABLE (KV-CONS OF STRING-WRAPPER STRING-WRAPPER)) ())", ((cpp_function_code)(&makeNamespaceTable)), NULL);
    defineFunctionObject("MAKE-XML-CDATA-FORM", "(DEFUN (MAKE-XML-CDATA-FORM CONS) ((THE-DATA STRING)))", ((cpp_function_code)(&makeXmlCdataForm)), NULL);
    defineFunctionObject("MAKE-XMLNS-ATTRIBUTE", "(DEFUN (MAKE-XMLNS-ATTRIBUTE XML-ATTRIBUTE) ((NAME STRING)))", ((cpp_function_code)(&makeXmlnsAttribute)), NULL);
    defineFunctionObject("MAKE-XML-ELEMENT-INTERNAL", "(DEFUN (MAKE-XML-ELEMENT-INTERNAL XML-ELEMENT) ((NAME STRING) (NAMESPACE-NAME STRING) (NAMESPACE STRING) (SURFACE-FORM STRING)))", ((cpp_function_code)(&makeXmlElementInternal)), NULL);
    defineFunctionObject("MAKE-XML-ELEMENT", "(DEFUN (MAKE-XML-ELEMENT XML-ELEMENT) ((NAME STRING) (NAMESPACE-NAME STRING) (NAMESPACE STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Creates and interns an XML element object `name' using `namespace-name'\nto refer to  `namespace'.  If `namespace' is `null', then the element will\nbe interned in the null namespace.   `namespace' must otherwise be a URI.\")", ((cpp_function_code)(&makeXmlElement)), NULL);
    defineFunctionObject("MAKE-XML-ELEMENT-RESPECTING-NAMESPACE", "(DEFUN (MAKE-XML-ELEMENT-RESPECTING-NAMESPACE XML-ELEMENT) ((NAME STRING) (NAMESPACE-TABLE (KV-CONS OF STRING-WRAPPER STRING-WRAPPER))))", ((cpp_function_code)(&makeXmlElementRespectingNamespace)), NULL);
    defineFunctionObject("MAKE-XML-GLOBAL-ATTRIBUTE-INTERNAL", "(DEFUN (MAKE-XML-GLOBAL-ATTRIBUTE-INTERNAL XML-GLOBAL-ATTRIBUTE) ((NAME STRING) (NAMESPACE-NAME STRING) (NAMESPACE-URI STRING) (SURFACE-FORM STRING)))", ((cpp_function_code)(&makeXmlGlobalAttributeInternal)), NULL);
    defineFunctionObject("MAKE-XML-GLOBAL-ATTRIBUTE", "(DEFUN (MAKE-XML-GLOBAL-ATTRIBUTE XML-GLOBAL-ATTRIBUTE) ((NAME STRING) (NAMESPACE-NAME STRING) (NAMESPACE STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Creates and interns an XML global attribute object with `name' using \n`namespace-name' to refer to  `namespace'.  `namespace'must be a URI.\")", ((cpp_function_code)(&makeXmlGlobalAttribute)), NULL);
    defineFunctionObject("MAKE-XML-GLOBAL-ATTRIBUTE-RESPECTING-NAMESPACE", "(DEFUN (MAKE-XML-GLOBAL-ATTRIBUTE-RESPECTING-NAMESPACE XML-GLOBAL-ATTRIBUTE) ((NAME STRING) (NAMESPACE-NAME STRING) (SURFACE-FORM STRING) (NAMESPACE-TABLE (KV-CONS OF STRING-WRAPPER STRING-WRAPPER))))", ((cpp_function_code)(&makeXmlGlobalAttributeRespectingNamespace)), NULL);
    defineFunctionObject("MAKE-XML-LOCAL-ATTRIBUTE", "(DEFUN (MAKE-XML-LOCAL-ATTRIBUTE XML-LOCAL-ATTRIBUTE) ((NAME STRING) (ELEMENT XML-ELEMENT)) :PUBLIC? TRUE :DOCUMENTATION \"Make an XML-LOCAL-ATTRIBUTE named `name' associated with `element'\")", ((cpp_function_code)(&makeXmlLocalAttribute)), NULL);
    defineFunctionObject("MAKE-XML-ATTRIBUTE-RESPECTING-NAMESPACE", "(DEFUN (MAKE-XML-ATTRIBUTE-RESPECTING-NAMESPACE XML-ATTRIBUTE) ((NAME STRING) (ELEMENT XML-ELEMENT) (NAMESPACE-TABLE (KV-CONS OF STRING-WRAPPER STRING-WRAPPER))))", ((cpp_function_code)(&makeXmlAttributeRespectingNamespace)), NULL);
    defineFunctionObject("XMLNS-ATTRIBUTE?", "(DEFUN (XMLNS-ATTRIBUTE? BOOLEAN) ((ATTRIBUTE OBJECT)))", ((cpp_function_code)(&xmlnsAttributeP)), NULL);
    defineFunctionObject("XMLNS-ATTRIBUTE-NAME?", "(DEFUN (XMLNS-ATTRIBUTE-NAME? BOOLEAN) ((NAME STRING)))", ((cpp_function_code)(&xmlnsAttributeNameP)), NULL);
    defineFunctionObject("EXTRACT-XMLNS-NAME", "(DEFUN (EXTRACT-XMLNS-NAME STRING) ((KEYNAME STRING)))", ((cpp_function_code)(&extractXmlnsName)), NULL);
    defineFunctionObject("ADD-XML-REFERENCE", "(DEFUN ADD-XML-REFERENCE ((NAME STRING) (SUBSTITUTION STRING) (TABLE (KEY-VALUE-LIST OF STRING-WRAPPER STRING-WRAPPER))) :GLOBALLY-INLINE? TRUE (INSERT-AT TABLE NAME SUBSTITUTION))", ((cpp_function_code)(&addXmlReference)), NULL);
    defineFunctionObject("MAKE-XML-ENTITY-TABLE", "(DEFUN (MAKE-XML-ENTITY-TABLE (KEY-VALUE-LIST OF STRING-WRAPPER STRING-WRAPPER)) ())", ((cpp_function_code)(&makeXmlEntityTable)), NULL);
    defineFunctionObject("DECODE-XML-CHAR-REF", "(DEFUN (DECODE-XML-CHAR-REF STRING) ((DIGITS STRING)))", ((cpp_function_code)(&decodeXmlCharRef)), NULL);
    defineFunctionObject("INTERNAL-DTD-DEFINITION?", "(DEFUN (INTERNAL-DTD-DEFINITION? BOOLEAN) ((DEFINITION STRING)) :PUBLIC? FALSE)", ((cpp_function_code)(&internalDtdDefinitionP)), NULL);
    defineFunctionObject("GET-DOCTYPE-DEFINITION", "(DEFUN (GET-DOCTYPE-DEFINITION INPUT-STREAM) ((DOCTYPE CONS)) :PUBLIC? FALSE)", ((cpp_function_code)(&getDoctypeDefinition)), NULL);
    defineFunctionObject("EXTERNAL-ID-HEAD?", "(DEFUN (EXTERNAL-ID-HEAD? BOOLEAN) ((ATTRIBUTE OBJECT)) :PUBLIC? FALSE :DOCUMENTATION \"Checks to see if this `attribute' is the literal marking either\na PUBLIC or SYSTEM literal for an XML Elternal ID.  (See 4.2.2)\")", ((cpp_function_code)(&externalIdHeadP)), NULL);
    defineFunctionObject("DECODE-XML-ENTITY-REF", "(DEFUN (DECODE-XML-ENTITY-REF STRING) ((DOCTYPE XML-DOCTYPE) (NAME STRING) (PE-REFERENCE-ALLOWED? BOOLEAN)))", ((cpp_function_code)(&decodeXmlEntityRef)), NULL);
    defineFunctionObject("DECODE-XML-PARAMETER-ENTITY-REF", "(DEFUN (DECODE-XML-PARAMETER-ENTITY-REF STRING) ((DOCTYPE XML-DOCTYPE) (NAME STRING) (PE-REFERENCE-ALLOWED? BOOLEAN)))", ((cpp_function_code)(&decodeXmlParameterEntityRef)), NULL);
    defineFunctionObject("DECODE-XML-REFERENCE", "(DEFUN (DECODE-XML-REFERENCE STRING) ((DOCTYPE XML-DOCTYPE) (REFERENCE STRING) (PE-REFERENCE-ALLOWED? BOOLEAN)))", ((cpp_function_code)(&decodeXmlReference)), NULL);
    defineFunctionObject("FIND-REFERENCE-START", "(DEFUN (FIND-REFERENCE-START INTEGER) ((INPUT STRING) (START INTEGER) (END INTEGER)))", ((cpp_function_code)(&findReferenceStart)), NULL);
    defineFunctionObject("DECODE-XML-STRING", "(DEFUN (DECODE-XML-STRING STRING) ((DOCTYPE XML-DOCTYPE) (INPUT STRING) (PE-REFERENCE-ALLOWED? BOOLEAN)))", ((cpp_function_code)(&decodeXmlString)), NULL);
    defineFunctionObject("NORMALIZE-ATTRIBUTE-VALUE", "(DEFUN (NORMALIZE-ATTRIBUTE-VALUE STRING) ((DOCTYPE XML-DOCTYPE) (INPUT STRING) (PE-REFERENCE-ALLOWED? BOOLEAN)))", ((cpp_function_code)(&normalizeAttributeValue)), NULL);
    defineFunctionObject("PROCESS-DOCTYPE", "(DEFUN (PROCESS-DOCTYPE XML-DOCTYPE) ((DOCTYPE-DECLARATION CONS)) :PUBLIC? TRUE :DOCUMENTATION \"Takes an S-Expression representing a doctype and processes into\na DOCTYPE object.\")", ((cpp_function_code)(&processDoctype)), NULL);
    defineFunctionObject("GET-XML-WHITESPACE-PRESERVING-TOKENIZER-TABLE", "(DEFUN (GET-XML-WHITESPACE-PRESERVING-TOKENIZER-TABLE TOKENIZER-TABLE) ())", ((cpp_function_code)(&getXmlWhitespacePreservingTokenizerTable)), NULL);
    defineFunctionObject("GET-XML-TOKENIZER-TABLE", "(DEFUN (GET-XML-TOKENIZER-TABLE TOKENIZER-TABLE) ())", ((cpp_function_code)(&getXmlTokenizerTable)), NULL);
    defineFunctionObject("TOKENIZE-XML-EXPRESSION", "(DEFUN (TOKENIZE-XML-EXPRESSION TOKENIZER-TOKEN BOOLEAN) ((STREAM INPUT-STREAM) (TOKENLIST TOKENIZER-TOKEN) (REGIONTAGNAME STRING) (SKIPTOREGION? BOOLEAN)))", ((cpp_function_code)(&tokenizeXmlExpression)), NULL);
    defineFunctionObject("PROCESS-ATTRIBUTE-LIST", "(DEFUN (PROCESS-ATTRIBUTE-LIST CONS) ((REVERSEATTRIBUTELIST CONS) (ELEMENT XML-ELEMENT) (NAMESPACE-TABLE (KV-CONS OF STRING-WRAPPER STRING-WRAPPER))))", ((cpp_function_code)(&processAttributeList)), NULL);
    defineFunctionObject("XML-TOKEN-LIST-TO-S-EXPRESSION", "(DEFUN (XML-TOKEN-LIST-TO-S-EXPRESSION OBJECT) ((TOKENLIST TOKENIZER-TOKEN) (DOCTYPE XML-DOCTYPE) (DOCTYPE-DEFINITION? BOOLEAN)) :DOCUMENTATION \"Convert the XML `tokenList' (using `doctype' for guidance) into a\nrepresentative s-expression and return the result.    The `doctype' argument is\ncurrently only used for expansion of entity references.  It can be 'null'.  The\nflag `doctype-definition?' should be true only when processing the DTD definition\nof a DOCTYPE tag, since it enables substitution of parameter entity values.\n\nEvery XML tag is represented as a cons-list starting with the tag as its header,\nfollowed by a possibly empty list of keyword value pairs representing tag attributes,\nfollowed by a possibly empty list of content expressions which might themselves\nbe XML expressions.  For example, the expression\n\n    <a a1=v1 a2='v2'> foo <b a3=v3/> bar </a>\n\nbecomes\n\n   (<a> (<a1> \\\"v1\\\" <a2> \\\"v2\\\") \\\"foo\\\" (<b> (<a3> \\\"v3\\\")) \\\"bar\\\")\n\nwhen represented as an s-expre" "ssion.  The tag names are subtypes of XML-OBJECT\nsuch as XML-ELEMENT, XML-LOCAL-ATTRIBUTE, XML-GLOBAL-ATTRIBUTE, etc.\n?, ! and [ prefixed tags are encoded as their own subtypes of XML-OBJECT, namely\nXML-PROCESSING-INSTRUCTION, XML-DECLARATION, XML-SPECIAL, XML-COMMENT, etc.\nCDATA is an XML-SPECIAL tag with a name of CDATA.\n\nThe name is available using class accessors.\" :PUBLIC? TRUE)", ((cpp_function_code)(&xmlTokenListToSExpression)), NULL);
    defineFunctionObject("READ-XML-EXPRESSION", "(DEFUN (READ-XML-EXPRESSION OBJECT BOOLEAN) ((STREAM INPUT-STREAM) (START-TAG OBJECT)) :DOCUMENTATION \"Read one balanced XML expression from `stream' and return\nits s-expression representation (see `xml-token-list-to-s-expression').  If\n`startTagName' is non-`null', skip all tags until a start tag matching `start-tag'\nis encountered.  XML namespaces are ignored for outside of the start tag.\nUse s-expression representation to specify `start-tag', e.g., '(KIF (:version \\\"1.0\\\"))'.\nThe tag can be an XML element object, a symbol, a string or a cons.  If the tag is a cons\nthe first element can also be (name namespace) pair.\n\nReturn `true' as the second value on EOF.\n\nCHANGE WARNING:  It is anticipated that this function will change to\n a) Properly take XML namespaces into account and\n b) require XML element objects instead of strings as the second argument.\nThis change will not be backwards-compatible.\" :PUBLIC? TRUE)", ((cpp_function_code)(&readXmlExpression)), NULL);
    defineFunctionObject("READ-XML-EXPRESSIONS", "(DEFUN (READ-XML-EXPRESSIONS CONS) ((FILENAME STRING)) :DOCUMENTATION \"Read all of the top-level XML expressions from `filename' and\nreturn them in a list.\")", ((cpp_function_code)(&readXmlExpressions)), NULL);
    defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF XML-EXPRESSION-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&XmlExpressionIterator::nextP))), NULL);
    defineMethodObject("(DEFMETHOD (CONSIFY CONS) ((ITER XML-EXPRESSION-ITERATOR)))", wrapMethodCode(((cpp_method_code)(&XmlExpressionIterator::consify))), NULL);
    defineFunctionObject("XML-REGION-MATCHES?", "(DEFUN (XML-REGION-MATCHES? BOOLEAN) ((REGIONSPEC CONS) (REGIONTAG CONS)))", ((cpp_function_code)(&xmlRegionMatchesP)), NULL);
    defineFunctionObject("COERCE-TO-XML-ELEMENT", "(DEFUN (COERCE-TO-XML-ELEMENT XML-ELEMENT) ((REGIONTAG OBJECT)))", ((cpp_function_code)(&coerceToXmlElement)), NULL);
    defineFunctionObject("XML-EXPRESSIONS", "(DEFUN (XML-EXPRESSIONS XML-EXPRESSION-ITERATOR) ((STREAM INPUT-STREAM) (REGIONTAG OBJECT)) :DOCUMENTATION \"Return an XML-expression-iterator (which see) reading from\n`stream'.  `regionTag' can be used to define delimited regions from which\nexpressions should be considered. Use s-expression representation to specify\n`regionTag', e.g., '(KIF (:version \\\"1.0\\\"))'.  The tag can be an XML element\nobject, a symbol, a string or a cons.  If the tag is a cons the first element\ncan also be (name namespace) pair.\" :PUBLIC? TRUE)", ((cpp_function_code)(&xmlExpressions)), NULL);
    defineFunctionObject("XML-CDATA?", "(DEFUN (XML-CDATA? BOOLEAN) ((ITEM OBJECT)) :PUBLIC? TRUE :DOCUMENTATION \"Return `true' if `item' is an XML CDATA tag object\")", ((cpp_function_code)(&xmlCdataP)), NULL);
    defineFunctionObject("XML-ELEMENT?", "(DEFUN (XML-ELEMENT? BOOLEAN) ((ITEM OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return `true' if `item' is an XML element object\" (RETURN (ISA? ITEM @XML-ELEMENT)))", ((cpp_function_code)(&xmlElementP)), NULL);
    defineFunctionObject("XML-ATTRIBUTE?", "(DEFUN (XML-ATTRIBUTE? BOOLEAN) ((ITEM OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return `true' if `item' is an XML attribute object\" (RETURN (ISA? ITEM @XML-ATTRIBUTE)))", ((cpp_function_code)(&xmlAttributeP)), NULL);
    defineFunctionObject("XML-GLOBAL-ATTRIBUTE?", "(DEFUN (XML-GLOBAL-ATTRIBUTE? BOOLEAN) ((ITEM OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return `true' if `item' is an XML attribute object\" (RETURN (ISA? ITEM @XML-GLOBAL-ATTRIBUTE)))", ((cpp_function_code)(&xmlGlobalAttributeP)), NULL);
    defineFunctionObject("XML-LOCAL-ATTRIBUTE?", "(DEFUN (XML-LOCAL-ATTRIBUTE? BOOLEAN) ((ITEM OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return `true' if `item' is an XML attribute object\" (RETURN (ISA? ITEM @XML-LOCAL-ATTRIBUTE)))", ((cpp_function_code)(&xmlLocalAttributeP)), NULL);
    defineFunctionObject("XML-BASE-ATTRIBUTE?", "(DEFUN (XML-BASE-ATTRIBUTE? BOOLEAN) ((ITEM OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return `true' if `item' is an XML attribute object\" (RETURN (AND (XML-GLOBAL-ATTRIBUTE? ITEM) (STRING-EQL? \"base\" (NAME (CAST ITEM XML-GLOBAL-ATTRIBUTE))) (STRING-EQL? *XML-URN* (NAMESPACE-URI (CAST ITEM XML-GLOBAL-ATTRIBUTE))))))", ((cpp_function_code)(&xmlBaseAttributeP)), NULL);
    defineFunctionObject("XML-DECLARATION?", "(DEFUN (XML-DECLARATION? BOOLEAN) ((ITEM OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return `true' if `item' is an XML declaration object\" (RETURN (ISA? ITEM @XML-DECLARATION)))", ((cpp_function_code)(&xmlDeclarationP)), NULL);
    defineFunctionObject("XML-PROCESSING-INSTRUCTION?", "(DEFUN (XML-PROCESSING-INSTRUCTION? BOOLEAN) ((ITEM OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return `true' if `item' is an XML processing instruction object\" (RETURN (ISA? ITEM @XML-PROCESSING-INSTRUCTION)))", ((cpp_function_code)(&xmlProcessingInstructionP)), NULL);
    defineFunctionObject("XML-ELEMENT-FORM?", "(DEFUN (XML-ELEMENT-FORM? BOOLEAN) ((FORM OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return `true' if `form' is a CONS headed by an XML ELEMENT tag\" (RETURN (AND (ISA? FORM @CONS) (XML-ELEMENT? (FIRST (CAST FORM CONS))))))", ((cpp_function_code)(&xmlElementFormP)), NULL);
    defineFunctionObject("XML-PROCESSING-INSTRUCTION-FORM?", "(DEFUN (XML-PROCESSING-INSTRUCTION-FORM? BOOLEAN) ((FORM OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return `true' if `form' is a CONS headed by an XML PROCESSING INSTRUCTION tag\" (RETURN (AND (ISA? FORM @CONS) (XML-PROCESSING-INSTRUCTION? (FIRST (CAST FORM CONS))))))", ((cpp_function_code)(&xmlProcessingInstructionFormP)), NULL);
    defineFunctionObject("XML-DECLARATION-FORM?", "(DEFUN (XML-DECLARATION-FORM? BOOLEAN) ((FORM OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return `true' if `form' is a CONS headed by an XML DECLARATION tag\" (RETURN (AND (ISA? FORM @CONS) (XML-DECLARATION? (FIRST (CAST FORM CONS))))))", ((cpp_function_code)(&xmlDeclarationFormP)), NULL);
    defineFunctionObject("XML-DOCTYPE-FORM?", "(DEFUN (XML-DOCTYPE-FORM? BOOLEAN) ((FORM OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return `true' if `form' is a CONS headed by a DOCTYPE tag\" (RETURN (AND (XML-DECLARATION-FORM? FORM) (STRING-EQL? (NAME (CAST (FIRST (CAST FORM CONS)) XML-DECLARATION)) \"DOCTYPE\"))))", ((cpp_function_code)(&xmlDoctypeFormP)), NULL);
    defineFunctionObject("XML-CDATA-FORM?", "(DEFUN (XML-CDATA-FORM? BOOLEAN) ((FORM OBJECT)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return `true' if `form' is a CONS headed by a CDATA tag\" (RETURN (AND (ISA? FORM @CONS) (XML-CDATA? (FIRST (CAST FORM CONS))))))", ((cpp_function_code)(&xmlCdataFormP)), NULL);
    defineFunctionObject("GET-XML-TAG", "(DEFUN (GET-XML-TAG XML-ELEMENT) ((EXPRESSION CONS)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the XML tag object of an XML `expression'.\" (RETURN (FIRST EXPRESSION)))", ((cpp_function_code)(&getXmlTag)), NULL);
    defineFunctionObject("GET-XML-ATTRIBUTES", "(DEFUN (GET-XML-ATTRIBUTES CONS) ((EXPRESSION CONS)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the list of attributes of an XML `expression' (may be empty).\" (RETURN (SECOND EXPRESSION)))", ((cpp_function_code)(&getXmlAttributes)), NULL);
    defineFunctionObject("GET-XML-BASE-ATTRIBUTE-VALUE", "(DEFUN (GET-XML-BASE-ATTRIBUTE-VALUE STRING) ((EXPRESSION CONS)) :PUBLIC? TRUE :DOCUMENTATION \"Return the last base url attribute in the attribute list of this\nelement if it exists.  Otherwise NULL.\")", ((cpp_function_code)(&getXmlBaseAttributeValue)), NULL);
    defineFunctionObject("GET-XML-CONTENT", "(DEFUN (GET-XML-CONTENT CONS) ((EXPRESSION CONS)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the list of content elements of an XML `expression' (may be empty).\" (RETURN (REST (REST EXPRESSION))))", ((cpp_function_code)(&getXmlContent)), NULL);
    defineFunctionObject("GET-XML-CDATA-CONTENT", "(DEFUN (GET-XML-CDATA-CONTENT STRING) ((FORM CONS)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return the CDATA content of a CDATA `form'.  Does NOT make sure that `form'\nactually is a CDATA form, so bad things can happen if it is given wrong input.\" (RETURN (UNWRAP-STRING (FIRST (CAST (SECOND FORM) CONS)))))", ((cpp_function_code)(&getXmlCdataContent)), NULL);
    defineMethodObject("(DEFMETHOD (XML-ELEMENT-MATCH? BOOLEAN) ((TAG XML-ELEMENT) (NAME STRING) (NAMESPACE STRING)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Returns `true' if `tag' is an XML element with the name `name'\nin namespace `namespace'.  Note that `namespace' is the full URI, not an abbreviation.\nAlso, `namespace' may be `null', in which case `tag' must not have a namespace\nassociated with it.\" (RETURN (AND (EQL? (NAME TAG) NAME) (EQL? (NAMESPACE-URI TAG) NAMESPACE))))", wrapMethodCode(((cpp_method_code)(&XmlElement::xmlElementMatchP))), NULL);
    defineMethodObject("(DEFMETHOD (XML-ATTRIBUTE-MATCH? BOOLEAN) ((ATTRIBUTE XML-ATTRIBUTE) (NAME STRING) (NAMESPACE STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return `true' if `attribute' is an XML attribute with name `name'\nin namespace `namespace'.  Note that `namespace' is the full URI, not an\nabbreviation.  Also, `namespace' may be `null', in which case `attribute'\nmust not have a namespace associated with it.\")", wrapMethodCode(((cpp_method_code)(&XmlAttribute::xmlAttributeMatchP))), NULL);
  }
}

void startupXml() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupXml1();
      helpStartupXml2();
    }
    if (currentStartupTimePhaseP(4)) {
      oXML_ELEMENT_NULL_NAMESPACE_TABLEo = newStringHashTable();
      oXML_ELEMENT_HASH_TABLEo = newStringHashTable();
      oXML_GLOBAL_ATTRIBUTE_HASH_TABLEo = newStringHashTable();
      oXML_BASE_ENTITY_TABLEo = makeXmlEntityTable();
      oXML_TOKENIZER_TABLE_DEFINITIONo = listO(45, listO(4, KWD_XML_START, KWD_XML_INCLUDE, KWD_XML_SKIP_WHITESPACE, NIL), listO(13, KWD_XML_SKIP_WHITESPACE, SYM_XML_STELLA_x, listO(5, wrapCharacter(' '), wrapCharacter('\t'), wrapCharacter('\n'), wrapCharacter('\r'), NIL), KWD_XML_SKIP_WHITESPACE, SYM_XML_STELLA_x, wrapString("<"), KWD_XML_OPEN_TAG, KWD_XML_EOF, KWD_XML_EOF, SYM_XML_STELLA_o, KWD_XML_OTHERWISE, KWD_XML_CONTENT, NIL), listO(9, KWD_XML_CONTENT, SYM_XML_STELLA_x, wrapString("<"), KWD_XML_OPEN_TAG, KWD_XML_EOF, KWD_XML_EOF, KWD_XML_OTHERWISE, KWD_XML_CONTENT, NIL), listO(17, KWD_XML_OPEN_TAG, SYM_XML_STELLA_o, wrapString(">"), KWD_XML_START_TAG_END, SYM_XML_STELLA_x, wrapString("/"), KWD_XML_OPEN_END_TAG, wrapString("?"), KWD_XML_OPEN_PI_TAG, wrapString("!"), KWD_XML_OPEN_DECLARATION_TAG, listO(5, wrapCharacter(' '), wrapCharacter('\t'), wrapCharacter('\n'), wrapCharacter('\r'), NIL), KWD_XML_OPEN_TAG, SYM_XML_STELLA_o, KWD_XML_OTHERWISE, KWD_XML_START_TAG, NIL), listO(13, KWD_XML_START_TAG, SYM_XML_STELLA_o, wrapString(">"), KWD_XML_START_TAG_END, SYM_XML_STELLA_x, wrapString("/"), KWD_XML_OPEN_EMPTY_TAG_END, SYM_XML_STELLA_x, listO(5, wrapCharacter(' '), wrapCharacter('\t'), wrapCharacter('\n'), wrapCharacter('\r'), NIL), KWD_XML_SKIP_TO_ATTRIBUTE_NAME, KWD_XML_OTHERWISE, KWD_XML_START_TAG, NIL), listO(5, KWD_XML_OPEN_PI_TAG, SYM_XML_STELLA_o, KWD_XML_ANY, KWD_XML_START_PI_TAG, NIL), listO(10, KWD_XML_START_PI_TAG, SYM_XML_STELLA_x, wrapString("?"), KWD_XML_OPEN_PI_TAG_END, SYM_XML_STELLA_o, listO(5, wrapCharacter(' '), wrapCharacter('\t'), wrapCharacter('\n'), wrapCharacter('\r'), NIL), KWD_XML_PI_TAG_DATA, KWD_XML_OTHERWISE, KWD_XML_START_PI_TAG, NIL), listO(6, KWD_XML_PI_TAG_DATA, wrapString("?"), listO(3, KWD_XML_PI_TAG_DATA_OR_END, KWD_XML_PI_TAG_DATA, NIL), KWD_XML_OTHERWISE, KWD_XML_PI_TAG_DATA, NIL), listO(7, KWD_XML_PI_TAG_DATA_OR_END, SYM_XML_STELLA_o, wrapString(">"), KWD_XML_EMPTY_TAG_END, KWD_XML_OTHERWISE, KWD_XML_PI_TAG_DATA, NIL), listO(7, KWD_XML_OPEN_PI_TAG_END, SYM_XML_STELLA_o, wrapString(">"), KWD_XML_EMPTY_TAG_END, KWD_XML_OTHERWISE, KWD_XML_ERROR, NIL), listO(8, KWD_XML_OPEN_END_TAG, SYM_XML_STELLA_x, wrapString(">"), KWD_XML_END_TAG_END, SYM_XML_STELLA_o, KWD_XML_OTHERWISE, KWD_XML_END_TAG, NIL), listO(7, KWD_XML_END_TAG, SYM_XML_STELLA_x, wrapString(">"), KWD_XML_END_TAG_END, KWD_XML_OTHERWISE, KWD_XML_END_TAG, NIL), listO(14, KWD_XML_SKIP_TO_ATTRIBUTE_NAME, SYM_XML_STELLA_o, wrapString(">"), KWD_XML_START_TAG_END, SYM_XML_STELLA_x, wrapString("/"), KWD_XML_OPEN_EMPTY_TAG_END, SYM_XML_STELLA_x, listO(5, wrapCharacter(' '), wrapCharacter('\t'), wrapCharacter('\n'), wrapCharacter('\r'), NIL), KWD_XML_SKIP_TO_ATTRIBUTE_NAME, SYM_XML_STELLA_o, KWD_XML_OTHERWISE, KWD_XML_ATTRIBUTE_NAME, NIL), listO(13, KWD_XML_ATTRIBUTE_NAME, SYM_XML_STELLA_o, wrapString(">"), KWD_XML_START_TAG_END, SYM_XML_STELLA_x, wrapString("/"), KWD_XML_OPEN_EMPTY_TAG_END, SYM_XML_STELLA_x, listO(6, wrapCharacter('='), wrapCharacter(' '), wrapCharacter('\t'), wrapCharacter('\n'), wrapCharacter('\r'), NIL), KWD_XML_SKIP_TO_ATTRIBUTE_VALUE, KWD_XML_OTHERWISE, KWD_XML_ATTRIBUTE_NAME, NIL), listO(19, KWD_XML_SKIP_TO_ATTRIBUTE_VALUE, SYM_XML_STELLA_o, wrapString(">"), KWD_XML_START_TAG_END, SYM_XML_STELLA_x, wrapString("/"), KWD_XML_OPEN_EMPTY_TAG_END, listO(6, wrapCharacter('='), wrapCharacter(' '), wrapCharacter('\t'), wrapCharacter('\n'), wrapCharacter('\r'), NIL), KWD_XML_SKIP_TO_ATTRIBUTE_VALUE, SYM_XML_STELLA_o, wrapString("'"), KWD_XML_SINGLE_QUOTED_ATTRIBUTE_VALUE, SYM_XML_STELLA_o, wrapString("\""), KWD_XML_DOUBLE_QUOTED_ATTRIBUTE_VALUE, SYM_XML_STELLA_o, KWD_XML_OTHERWISE, KWD_XML_UNQUOTED_ATTRIBUTE_VALUE, NIL), listO(6, KWD_XML_SINGLE_QUOTED_ATTRIBUTE_VALUE, wrapString("'"), KWD_XML_QUOTED_ATTRIBUTE_VALUE, KWD_XML_OTHERWISE, KWD_XML_SINGLE_QUOTED_ATTRIBUTE_VALUE, NIL), listO(6, KWD_XML_DOUBLE_QUOTED_ATTRIBUTE_VALUE, wrapString("\""), KWD_XML_QUOTED_ATTRIBUTE_VALUE, KWD_XML_OTHERWISE, KWD_XML_DOUBLE_QUOTED_ATTRIBUTE_VALUE, NIL), listO(4, KWD_XML_QUOTED_ATTRIBUTE_VALUE, KWD_XML_INCLUDE, KWD_XML_SKIP_TO_ATTRIBUTE_NAME, NIL), listO(13, KWD_XML_UNQUOTED_ATTRIBUTE_VALUE, SYM_XML_STELLA_o, wrapString(">"), KWD_XML_START_TAG_END, SYM_XML_STELLA_x, wrapString("/"), KWD_XML_OPEN_EMPTY_TAG_END, SYM_XML_STELLA_x, listO(5, wrapCharacter(' '), wrapCharacter('\t'), wrapCharacter('\n'), wrapCharacter('\r'), NIL), KWD_XML_SKIP_TO_ATTRIBUTE_NAME, KWD_XML_OTHERWISE, KWD_XML_UNQUOTED_ATTRIBUTE_VALUE, NIL), listO(9, KWD_XML_OPEN_DECLARATION_TAG, wrapString("-"), KWD_XML_START_TAG_OR_COMMENT, wrapString("["), KWD_XML_OPEN_SPECIAL_TAG, SYM_XML_STELLA_o, KWD_XML_OTHERWISE, KWD_XML_START_DECLARATION_TAG, NIL), listO(10, KWD_XML_START_DECLARATION_TAG, SYM_XML_STELLA_o, wrapString(">"), KWD_XML_EMPTY_TAG_END, SYM_XML_STELLA_x, listO(5, wrapCharacter(' '), wrapCharacter('\t'), wrapCharacter('\n'), wrapCharacter('\r'), NIL), KWD_XML_DECLARATION_WHITESPACE, KWD_XML_OTHERWISE, KWD_XML_START_DECLARATION_TAG, NIL), listO(20, KWD_XML_DECLARATION_WHITESPACE, SYM_XML_STELLA_x, listO(5, wrapCharacter(' '), wrapCharacter('\t'), wrapCharacter('\n'), wrapCharacter('\r'), NIL), KWD_XML_DECLARATION_WHITESPACE, SYM_XML_STELLA_o, wrapString(">"), KWD_XML_EMPTY_TAG_END, SYM_XML_STELLA_o, wrapString("["), KWD_XML_DECLARATION_TAG_MARKUP_DATA_START, SYM_XML_STELLA_o, wrapString("'"), KWD_XML_SINGLE_QUOTED_DECLARATION_TAG_DATA, SYM_XML_STELLA_o, wrapString("\""), KWD_XML_DOUBLE_QUOTED_DECLARATION_TAG_DATA, SYM_XML_STELLA_o, KWD_XML_OTHERWISE, KWD_XML_DECLARATION_TAG_DATA, NIL), listO(17, KWD_XML_DECLARATION_TAG_DATA, SYM_XML_STELLA_x, listO(5, wrapCharacter(' '), wrapCharacter('\t'), wrapCharacter('\n'), wrapCharacter('\r'), NIL), KWD_XML_DECLARATION_WHITESPACE, SYM_XML_STELLA_o, wrapString(">"), KWD_XML_EMPTY_TAG_END, SYM_XML_STELLA_o, wrapString("["), KWD_XML_DECLARATION_TAG_MARKUP_DATA_START, wrapString("'"), KWD_XML_SINGLE_QUOTED_DECLARATION_TAG_DATA, wrapString("\""), KWD_XML_DOUBLE_QUOTED_DECLARATION_TAG_DATA, KWD_XML_OTHERWISE, KWD_XML_DECLARATION_TAG_DATA, NIL), listO(6, KWD_XML_SINGLE_QUOTED_DECLARATION_TAG_DATA, wrapString("'"), KWD_XML_QUOTED_DECLARATION_TAG_DATA, KWD_XML_OTHERWISE, KWD_XML_SINGLE_QUOTED_DECLARATION_TAG_DATA, NIL), listO(6, KWD_XML_DOUBLE_QUOTED_DECLARATION_TAG_DATA, wrapString("\""), KWD_XML_QUOTED_DECLARATION_TAG_DATA, KWD_XML_OTHERWISE, KWD_XML_DOUBLE_QUOTED_DECLARATION_TAG_DATA, NIL), listO(4, KWD_XML_QUOTED_DECLARATION_TAG_DATA, KWD_XML_INCLUDE, KWD_XML_DECLARATION_WHITESPACE, NIL), listO(6, KWD_XML_DECLARATION_TAG_MARKUP_DATA_START, wrapString("]"), KWD_XML_DECLARATION_TAG_MARKUP_DATA, KWD_XML_OTHERWISE, KWD_XML_DECLARATION_TAG_MARKUP_DATA_START, NIL), listO(7, KWD_XML_DECLARATION_TAG_MARKUP_DATA, SYM_XML_STELLA_o, wrapString(">"), KWD_XML_EMPTY_TAG_END, KWD_XML_OTHERWISE, KWD_XML_ERROR, NIL), listO(5, KWD_XML_OPEN_SPECIAL_TAG, SYM_XML_STELLA_o, KWD_XML_ANY, KWD_XML_START_SPECIAL_TAG, NIL), listO(7, KWD_XML_START_SPECIAL_TAG, SYM_XML_STELLA_o, wrapString("["), KWD_XML_SPECIAL_TAG_DATA, KWD_XML_OTHERWISE, KWD_XML_START_SPECIAL_TAG, NIL), listO(6, KWD_XML_SPECIAL_TAG_DATA, wrapString("]"), KWD_XML_SPECIAL_TAG_DATA_OR_END, KWD_XML_OTHERWISE, KWD_XML_SPECIAL_TAG_DATA, NIL), listO(6, KWD_XML_SPECIAL_TAG_DATA_OR_END, wrapString("]"), listO(3, KWD_XML_SPECIAL_TAG_DATA_OR_END2, KWD_XML_SPECIAL_TAG_DATA, NIL), KWD_XML_OTHERWISE, KWD_XML_SPECIAL_TAG_DATA, NIL), listO(7, KWD_XML_SPECIAL_TAG_DATA_OR_END2, SYM_XML_STELLA_o, wrapString(">"), KWD_XML_DATA_TAG_END, KWD_XML_OTHERWISE, KWD_XML_SPECIAL_TAG_DATA, NIL), listO(7, KWD_XML_START_TAG_OR_COMMENT, wrapString("-"), KWD_XML_COMMENT_BODY, SYM_XML_STELLA_o, KWD_XML_OTHERWISE, KWD_XML_START_TAG, NIL), listO(6, KWD_XML_COMMENT_BODY, wrapString("-"), KWD_XML_END_COMMENT_OR_COMMENT, KWD_XML_OTHERWISE, KWD_XML_COMMENT_BODY, NIL), listO(6, KWD_XML_END_COMMENT_OR_COMMENT, wrapString("-"), KWD_XML_END_COMMENT_OR_COMMENT2, KWD_XML_OTHERWISE, KWD_XML_COMMENT_BODY, NIL), listO(6, KWD_XML_END_COMMENT_OR_COMMENT2, wrapString(">"), KWD_XML_COMMENT, KWD_XML_OTHERWISE, KWD_XML_ERROR, NIL), listO(4, KWD_XML_COMMENT, KWD_XML_INCLUDE, KWD_XML_START, NIL), listO(4, KWD_XML_START_TAG_END, KWD_XML_INCLUDE, KWD_XML_START, NIL), listO(4, KWD_XML_DATA_TAG_END, KWD_XML_INCLUDE, KWD_XML_START, NIL), listO(4, KWD_XML_END_TAG_END, KWD_XML_INCLUDE, KWD_XML_START, NIL), listO(7, KWD_XML_OPEN_EMPTY_TAG_END, SYM_XML_STELLA_o, wrapString(">"), KWD_XML_EMPTY_TAG_END, KWD_XML_OTHERWISE, KWD_XML_ERROR, NIL), listO(4, KWD_XML_EMPTY_TAG_END, KWD_XML_INCLUDE, KWD_XML_START, NIL), listO(4, KWD_XML_ERROR, KWD_XML_INCLUDE, KWD_XML_START, NIL), NIL);
    }
    if (currentStartupTimePhaseP(5)) {
      helpStartupXml3();
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupXml4();
      defineMethodObject("(DEFMETHOD (XML-ATTRIBUTE-MATCH? BOOLEAN) ((ATTRIBUTE XML-GLOBAL-ATTRIBUTE) (NAME STRING) (NAMESPACE STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return `true' if `attribute' is a global  XML attribute with name `name'\nin namespace `namespace'.  Note that `namespace' is the full URI, not an\nabbreviation.  Also, `namespace' may be `null', in which case `attribute'\nmust not have a namespace associated with it.\")", wrapMethodCode(((cpp_method_code)(&XmlGlobalAttribute::xmlAttributeMatchP))), NULL);
      defineMethodObject("(DEFMETHOD (XML-ATTRIBUTE-MATCH? BOOLEAN) ((ATTRIBUTE XML-LOCAL-ATTRIBUTE) (NAME STRING) (NAMESPACE STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Return `true' if `attribute' is a local XML attribute with name `name'.\nNote that `namespace' must be `null' and that the `attribute's parent element\nelement is not considered by the match.  To take the parent element into\naccount use `xml-local-attribute-match?'.\")", wrapMethodCode(((cpp_method_code)(&XmlLocalAttribute::xmlAttributeMatchP))), NULL);
      defineFunctionObject("XML-GLOBAL-ATTRIBUTE-MATCH?", "(DEFUN (XML-GLOBAL-ATTRIBUTE-MATCH? BOOLEAN) ((ATTRIBUTE XML-GLOBAL-ATTRIBUTE) (NAME STRING) (NAMESPACE STRING)) :GLOBALLY-INLINE? TRUE (RETURN (AND (STRING-EQL? (NAME ATTRIBUTE) NAME) (EQL? (NAMESPACE-URI ATTRIBUTE) NAMESPACE))))", ((cpp_function_code)(&xmlGlobalAttributeMatchP)), NULL);
      defineFunctionObject("XML-LOCAL-ATTRIBUTE-MATCH?", "(DEFUN (XML-LOCAL-ATTRIBUTE-MATCH? BOOLEAN) ((ATTRIBUTE XML-LOCAL-ATTRIBUTE) (NAME STRING) (ELEMENT-NAME STRING) (ELEMENT-NAMESPACE STRING)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE :DOCUMENTATION \"Return true if `attribute' is a local attribute with `name' and whose\nparent element matches `element-name' and `element-namespace'.\" (RETURN (AND (STRING-EQL? (NAME ATTRIBUTE) NAME) (XML-ELEMENT-MATCH? (PARENT-ELEMENT ATTRIBUTE) ELEMENT-NAME ELEMENT-NAMESPACE))))", ((cpp_function_code)(&xmlLocalAttributeMatchP)), NULL);
      defineFunctionObject("XML-LOOKUP-ATTRIBUTE", "(DEFUN (XML-LOOKUP-ATTRIBUTE STRING) ((ATTRIBUTES CONS) (NAME STRING) (NAMESPACE STRING)) :DOCUMENTATION \"Find the XML attribute in `attributes' with `name' and `namespace' and\nreturn its value.  Note that it is assumed that all `attributes' come from\nthe same known tag, hence, the parent elements of any local attributes are\nnot considered by the lookup.\" :PUBLIC? TRUE)", ((cpp_function_code)(&xmlLookupAttribute)), NULL);
      defineFunctionObject("EXPAND-XML-TAG-CASE", "(DEFUN (EXPAND-XML-TAG-CASE CONS) ((ITEM SYMBOL) (CLAUSES (CONS OF CONS))))", ((cpp_function_code)(&expandXmlTagCase)), NULL);
      defineFunctionObject("XML-TAG-CASE", "(DEFUN XML-TAG-CASE ((ITEM OBJECT) |&BODY| (CLAUSES CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE :DOCUMENTATION \"A case form for matching `item' against XML element tags.  Each\nelement of `clauses' should be a clause with the form\n  (\\\"tagname\\\" ...)     or\n  ((\\\"tagname\\\" \\\"namespace-uri\\\") ...)\nThe clause heads can optionally be symbols instead of strings.  The key forms the\nparameters to the method `xml-element-match?', with a missing namespace argument\npassed as NULL.\n\nThe namespace argument will be evaluated, so one can use bound variables in\nplace of a fixed string.   As a special case, if the namespace argument is\n:ANY, then the test will be done for a match on the tag name alone.\")", ((cpp_function_code)(&xmlTagCase)), NULL);
      defineFunctionObject("PRINT-XML-NON-ELEMENT-ATTRIBUTES", "(DEFUN PRINT-XML-NON-ELEMENT-ATTRIBUTES ((STREAM OUTPUT-STREAM) (ATTRIBUTES CONS)))", ((cpp_function_code)(&printXmlNonElementAttributes)), NULL);
      defineFunctionObject("PRINT-XML-ELEMENT-ATTRIBUTES", "(DEFUN PRINT-XML-ELEMENT-ATTRIBUTES ((STREAM OUTPUT-STREAM) (ATTRIBUTES CONS)))", ((cpp_function_code)(&printXmlElementAttributes)), NULL);
      defineFunctionObject("PRINT-XML-EXPRESSION", "(DEFUN PRINT-XML-EXPRESSION ((STREAM OUTPUT-STREAM) (XML-EXPRESSION CONS) (INDENT INTEGER)) :DOCUMENTATION \"Prints `xml-expression' on `stream'.  Indentation begins with the\nvalue of `indent'.  If this is the `null' integer, no indentation is\nperformed.  Otherwise it should normally be specified as 0 (zero) for\ntop-level calls.\n\nIt is assumed that the `xml-expression' is a well-formed CONS-list\nrepresentation of an XML  form.  It expects a form like that form\nreturned by `read-XML-expression'.\n\nAlso handles a list of xml forms such as that returned by `XML-expressions'.\nIn that case, each of the forms is indented by `indent' spaces.\" :PUBLIC? TRUE)", ((cpp_function_code)(&printXmlExpression)), NULL);
      defineFunctionObject("STARTUP-XML", "(DEFUN STARTUP-XML () :PUBLIC? TRUE)", ((cpp_function_code)(&startupXml)), NULL);
      { MethodSlot* function = lookupFunction(SYM_XML_STELLA_STARTUP_XML);

        setDynamicSlotValue(function->dynamicSlots, SYM_XML_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupXml"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFCONSTANT *XML-URN* STRING \"http://www.w3.org/XML/1998/namespaces\")", &oXML_URNo);
      defineGlobalVariableObject("(DEFCONSTANT *HTML-V4-0-URN* STRING \"http://www.w3.org/TR/REC-html40\")", &oHTML_V4_0_URNo);
      defineGlobalVariableObject("(DEFGLOBAL *XML-ELEMENT-NULL-NAMESPACE-TABLE* (STRING-HASH-TABLE OF STRING XML-ELEMENT) (NEW (STRING-HASH-TABLE OF STRING XML-ELEMENT)) :DOCUMENTATION \"Hash Table for interning XML elements that don't appear in any namespace.\")", &oXML_ELEMENT_NULL_NAMESPACE_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *XML-ELEMENT-HASH-TABLE* (STRING-HASH-TABLE OF STRING (STRING-HASH-TABLE OF STRING XML-ELEMENT)) (NEW (STRING-HASH-TABLE OF STRING (STRING-HASH-TABLE OF STRING XML-ELEMENT))) :DOCUMENTATION \"Hash Table mapping URI's (for namespaces) to a Hash Table\nfor interning XML elements.\")", &oXML_ELEMENT_HASH_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *XML-GLOBAL-ATTRIBUTE-HASH-TABLE* (STRING-HASH-TABLE OF STRING (STRING-HASH-TABLE OF STRING XML-ATTRIBUTE)) (NEW (STRING-HASH-TABLE OF STRING (STRING-HASH-TABLE OF STRING XML-ATTRIBUTE))) :DOCUMENTATION \"Hash Table mapping URI's (for namespaces) to a Hash Table\nfor interning XML global attributes.\")", &oXML_GLOBAL_ATTRIBUTE_HASH_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *XML-BASE-ENTITY-TABLE* (KEY-VALUE-LIST OF STRING-WRAPPER STRING-WRAPPER) (MAKE-XML-ENTITY-TABLE))", &oXML_BASE_ENTITY_TABLEo);
      defineGlobalVariableObject("(DEFGLOBAL *XML-TOKENIZER-TABLE-DEFINITION* CONS (BQUOTE ((:START :INCLUDE :SKIP-WHITESPACE) (:SKIP-WHITESPACE ! (#\\  #\\Tab #\\Linefeed #\\Return) :SKIP-WHITESPACE ! \"<\" :OPEN-TAG :EOF :EOF * :OTHERWISE :CONTENT) (:CONTENT ! \"<\" :OPEN-TAG :EOF :EOF :OTHERWISE :CONTENT) (:OPEN-TAG * \">\" :START-TAG-END ! \"/\" :OPEN-END-TAG \"?\" :OPEN-PI-TAG \"!\" :OPEN-DECLARATION-TAG (#\\  #\\Tab #\\Linefeed #\\Return) :OPEN-TAG * :OTHERWISE :START-TAG) (:START-TAG * \">\" :START-TAG-END ! \"/\" :OPEN-EMPTY-TAG-END ! (#\\  #\\Tab #\\Linefeed #\\Return) :SKIP-TO-ATTRIBUTE-NAME :OTHERWISE :START-TAG) (:OPEN-PI-TAG * :ANY :START-PI-TAG) (:START-PI-TAG ! \"?\" :OPEN-PI-TAG-END * (#\\  #\\Tab #\\Linefeed #\\Return) :PI-TAG-DATA :OTHERWISE :START-PI-TAG) (:PI-TAG-DATA \"?\" (:PI-TAG-DATA-OR-END :PI-TAG-DATA) :OTHERWISE :PI-TAG-DATA) (:PI-TAG-DATA-OR-END * \">\" :EMPTY-TAG-END :OTHERWISE :PI-TAG-DATA) (:OPEN-PI-TAG-END * \">\" :EMPTY-TAG-END :OTHERWISE :ERROR) (:OPEN-END-TAG ! \">\" :END-TAG-END * :OTHERWISE :END-TAG) (:EN" "D-TAG ! \">\" :END-TAG-END :OTHERWISE :END-TAG) (:SKIP-TO-ATTRIBUTE-NAME * \">\" :START-TAG-END ! \"/\" :OPEN-EMPTY-TAG-END ! (#\\  #\\Tab #\\Linefeed #\\Return) :SKIP-TO-ATTRIBUTE-NAME * :OTHERWISE :ATTRIBUTE-NAME) (:ATTRIBUTE-NAME * \">\" :START-TAG-END ! \"/\" :OPEN-EMPTY-TAG-END ! (#\\= #\\  #\\Tab #\\Linefeed #\\Return) :SKIP-TO-ATTRIBUTE-VALUE :OTHERWISE :ATTRIBUTE-NAME) (:SKIP-TO-ATTRIBUTE-VALUE * \">\" :START-TAG-END ! \"/\" :OPEN-EMPTY-TAG-END (#\\= #\\  #\\Tab #\\Linefeed #\\Return) :SKIP-TO-ATTRIBUTE-VALUE * \"'\" :SINGLE-QUOTED-ATTRIBUTE-VALUE * \"\\\"\" :DOUBLE-QUOTED-ATTRIBUTE-VALUE * :OTHERWISE :UNQUOTED-ATTRIBUTE-VALUE) (:SINGLE-QUOTED-ATTRIBUTE-VALUE \"'\" :QUOTED-ATTRIBUTE-VALUE :OTHERWISE :SINGLE-QUOTED-ATTRIBUTE-VALUE) (:DOUBLE-QUOTED-ATTRIBUTE-VALUE \"\\\"\" :QUOTED-ATTRIBUTE-VALUE :OTHERWISE :DOUBLE-QUOTED-ATTRIBUTE-VALUE) (:QUOTED-ATTRIBUTE-VALUE :INCLUDE :SKIP-TO-ATTRIBUTE-NAME) (:UNQUOTED-ATTRIBUTE-VALUE * \">\" :START-TAG-END ! \"/\" :OPEN-EMPTY-TAG-END ! (#\\  #\\Tab #\\Linefeed #\\" "Return) :SKIP-TO-ATTRIBUTE-NAME :OTHERWISE :UNQUOTED-ATTRIBUTE-VALUE) (:OPEN-DECLARATION-TAG \"-\" :START-TAG-OR-COMMENT \"[\" :OPEN-SPECIAL-TAG * :OTHERWISE :START-DECLARATION-TAG) (:START-DECLARATION-TAG * \">\" :EMPTY-TAG-END ! (#\\  #\\Tab #\\Linefeed #\\Return) :DECLARATION-WHITESPACE :OTHERWISE :START-DECLARATION-TAG) (:DECLARATION-WHITESPACE ! (#\\  #\\Tab #\\Linefeed #\\Return) :DECLARATION-WHITESPACE * \">\" :EMPTY-TAG-END * \"[\" :DECLARATION-TAG-MARKUP-DATA-START * \"'\" :SINGLE-QUOTED-DECLARATION-TAG-DATA * \"\\\"\" :DOUBLE-QUOTED-DECLARATION-TAG-DATA * :OTHERWISE :DECLARATION-TAG-DATA) (:DECLARATION-TAG-DATA ! (#\\  #\\Tab #\\Linefeed #\\Return) :DECLARATION-WHITESPACE * \">\" :EMPTY-TAG-END * \"[\" :DECLARATION-TAG-MARKUP-DATA-START \"'\" :SINGLE-QUOTED-DECLARATION-TAG-DATA \"\\\"\" :DOUBLE-QUOTED-DECLARATION-TAG-DATA :OTHERWISE :DECLARATION-TAG-DATA) (:SINGLE-QUOTED-DECLARATION-TAG-DATA \"'\" :QUOTED-DECLARATION-TAG-DATA :OTHERWISE :SINGLE-QUOTED-DECLARATION-TAG-DATA) (:DOUBLE-QUOTED-DECLARATI" "ON-TAG-DATA \"\\\"\" :QUOTED-DECLARATION-TAG-DATA :OTHERWISE :DOUBLE-QUOTED-DECLARATION-TAG-DATA) (:QUOTED-DECLARATION-TAG-DATA :INCLUDE :DECLARATION-WHITESPACE) (:DECLARATION-TAG-MARKUP-DATA-START \"]\" :DECLARATION-TAG-MARKUP-DATA :OTHERWISE :DECLARATION-TAG-MARKUP-DATA-START) (:DECLARATION-TAG-MARKUP-DATA * \">\" :EMPTY-TAG-END :OTHERWISE :ERROR) (:OPEN-SPECIAL-TAG * :ANY :START-SPECIAL-TAG) (:START-SPECIAL-TAG * \"[\" :SPECIAL-TAG-DATA :OTHERWISE :START-SPECIAL-TAG) (:SPECIAL-TAG-DATA \"]\" :SPECIAL-TAG-DATA-OR-END :OTHERWISE :SPECIAL-TAG-DATA) (:SPECIAL-TAG-DATA-OR-END \"]\" (:SPECIAL-TAG-DATA-OR-END2 :SPECIAL-TAG-DATA) :OTHERWISE :SPECIAL-TAG-DATA) (:SPECIAL-TAG-DATA-OR-END2 * \">\" :DATA-TAG-END :OTHERWISE :SPECIAL-TAG-DATA) (:START-TAG-OR-COMMENT \"-\" :COMMENT-BODY * :OTHERWISE :START-TAG) (:COMMENT-BODY \"-\" :END-COMMENT-OR-COMMENT :OTHERWISE :COMMENT-BODY) (:END-COMMENT-OR-COMMENT \"-\" :END-COMMENT-OR-COMMENT2 :OTHERWISE :COMMENT-BODY) (:END-COMMENT-OR-COMMENT2 \">\" :COMMENT :OTHERWISE :ERROR) " "(:COMMENT :INCLUDE :START) (:START-TAG-END :INCLUDE :START) (:DATA-TAG-END :INCLUDE :START) (:END-TAG-END :INCLUDE :START) (:OPEN-EMPTY-TAG-END * \">\" :EMPTY-TAG-END :OTHERWISE :ERROR) (:EMPTY-TAG-END :INCLUDE :START) (:ERROR :INCLUDE :START))))", &oXML_TOKENIZER_TABLE_DEFINITIONo);
      defineGlobalVariableObject("(DEFGLOBAL *XML-TOKENIZER-TABLE* TOKENIZER-TABLE NULL)", &oXML_TOKENIZER_TABLEo);
      oXML_TOKENIZER_TABLEo = parseTokenizerDefinition(oXML_TOKENIZER_TABLE_DEFINITIONo);
      defineGlobalVariableObject("(DEFSPECIAL *XML-PRESERVE-ALL-WHITESPACE?* BOOLEAN FALSE :DOCUMENTATION \"If true, all whitespace between tags (newlines, trailing WP, etc.)\nwill be preserved.  This is a kludge to allow us to read certain `illegal' XML files\nwhere this whitespace is significant but not appropriately encoded.\")", &oXML_PRESERVE_ALL_WHITESPACEpo);
      defineGlobalVariableObject("(DEFGLOBAL *XML-WHITESPACE-PRESERVING-TOKENIZER-TABLE* TOKENIZER-TABLE NULL)", &oXML_WHITESPACE_PRESERVING_TOKENIZER_TABLEo);
    }
  }
}

Surrogate* SGT_XML_STELLA_XML_OBJECT = NULL;

Symbol* SYM_XML_STELLA_NAME = NULL;

Symbol* SYM_XML_STELLA_SURFACE_FORM = NULL;

Surrogate* SGT_XML_STELLA_XML_ELEMENT = NULL;

Symbol* SYM_XML_STELLA_NAMESPACE_NAME = NULL;

Symbol* SYM_XML_STELLA_NAMESPACE_URI = NULL;

Symbol* SYM_XML_STELLA_ELEMENT_DICTIONARY = NULL;

Surrogate* SGT_XML_STELLA_XML_LOCAL_ATTRIBUTE = NULL;

Symbol* SYM_XML_STELLA_PARENT_ELEMENT = NULL;

Surrogate* SGT_XML_STELLA_XML_GLOBAL_ATTRIBUTE = NULL;

Surrogate* SGT_XML_STELLA_XML_PROCESSING_INSTRUCTION = NULL;

Symbol* SYM_XML_STELLA_DATA = NULL;

Surrogate* SGT_XML_STELLA_XML_DECLARATION = NULL;

Surrogate* SGT_XML_STELLA_XML_DOCTYPE_DECLARATION = NULL;

Surrogate* SGT_XML_STELLA_XML_SPECIAL = NULL;

Surrogate* SGT_XML_STELLA_XML_COMMENT = NULL;

Surrogate* SGT_XML_STELLA_XML_DOCTYPE = NULL;

Symbol* SYM_XML_STELLA_ENTITY_TABLE = NULL;

Symbol* SYM_XML_STELLA_PARAMETER_ENTITY_TABLE = NULL;

Surrogate* SGT_XML_STELLA_STRING_WRAPPER = NULL;

Keyword* KWD_XML_START = NULL;

Keyword* KWD_XML_INCLUDE = NULL;

Keyword* KWD_XML_SKIP_WHITESPACE = NULL;

Symbol* SYM_XML_STELLA_x = NULL;

Keyword* KWD_XML_OPEN_TAG = NULL;

Keyword* KWD_XML_EOF = NULL;

Symbol* SYM_XML_STELLA_o = NULL;

Keyword* KWD_XML_OTHERWISE = NULL;

Keyword* KWD_XML_CONTENT = NULL;

Keyword* KWD_XML_START_TAG_END = NULL;

Keyword* KWD_XML_OPEN_END_TAG = NULL;

Keyword* KWD_XML_OPEN_PI_TAG = NULL;

Keyword* KWD_XML_OPEN_DECLARATION_TAG = NULL;

Keyword* KWD_XML_START_TAG = NULL;

Keyword* KWD_XML_OPEN_EMPTY_TAG_END = NULL;

Keyword* KWD_XML_SKIP_TO_ATTRIBUTE_NAME = NULL;

Keyword* KWD_XML_ANY = NULL;

Keyword* KWD_XML_START_PI_TAG = NULL;

Keyword* KWD_XML_OPEN_PI_TAG_END = NULL;

Keyword* KWD_XML_PI_TAG_DATA = NULL;

Keyword* KWD_XML_PI_TAG_DATA_OR_END = NULL;

Keyword* KWD_XML_EMPTY_TAG_END = NULL;

Keyword* KWD_XML_ERROR = NULL;

Keyword* KWD_XML_END_TAG_END = NULL;

Keyword* KWD_XML_END_TAG = NULL;

Keyword* KWD_XML_ATTRIBUTE_NAME = NULL;

Keyword* KWD_XML_SKIP_TO_ATTRIBUTE_VALUE = NULL;

Keyword* KWD_XML_SINGLE_QUOTED_ATTRIBUTE_VALUE = NULL;

Keyword* KWD_XML_DOUBLE_QUOTED_ATTRIBUTE_VALUE = NULL;

Keyword* KWD_XML_UNQUOTED_ATTRIBUTE_VALUE = NULL;

Keyword* KWD_XML_QUOTED_ATTRIBUTE_VALUE = NULL;

Keyword* KWD_XML_START_TAG_OR_COMMENT = NULL;

Keyword* KWD_XML_OPEN_SPECIAL_TAG = NULL;

Keyword* KWD_XML_START_DECLARATION_TAG = NULL;

Keyword* KWD_XML_DECLARATION_WHITESPACE = NULL;

Keyword* KWD_XML_DECLARATION_TAG_MARKUP_DATA_START = NULL;

Keyword* KWD_XML_SINGLE_QUOTED_DECLARATION_TAG_DATA = NULL;

Keyword* KWD_XML_DOUBLE_QUOTED_DECLARATION_TAG_DATA = NULL;

Keyword* KWD_XML_DECLARATION_TAG_DATA = NULL;

Keyword* KWD_XML_QUOTED_DECLARATION_TAG_DATA = NULL;

Keyword* KWD_XML_DECLARATION_TAG_MARKUP_DATA = NULL;

Keyword* KWD_XML_START_SPECIAL_TAG = NULL;

Keyword* KWD_XML_SPECIAL_TAG_DATA = NULL;

Keyword* KWD_XML_SPECIAL_TAG_DATA_OR_END = NULL;

Keyword* KWD_XML_SPECIAL_TAG_DATA_OR_END2 = NULL;

Keyword* KWD_XML_DATA_TAG_END = NULL;

Keyword* KWD_XML_COMMENT_BODY = NULL;

Keyword* KWD_XML_END_COMMENT_OR_COMMENT = NULL;

Keyword* KWD_XML_END_COMMENT_OR_COMMENT2 = NULL;

Keyword* KWD_XML_COMMENT = NULL;

Keyword* KWD_XML_ATTRIBUTE_VALUE = NULL;

Keyword* KWD_XML_WHITE_SPACE = NULL;

Surrogate* SGT_XML_STELLA_XML_EXPRESSION_ITERATOR = NULL;

Symbol* SYM_XML_STELLA_REGION_TAG = NULL;

Symbol* SYM_XML_STELLA_REGION_MATCH_FUNCTION = NULL;

Symbol* SYM_XML_STELLA_DOCTYPE = NULL;

Symbol* SYM_XML_STELLA_DOCTYPE_ITERATORp = NULL;

Symbol* SYM_XML_STELLA_VALUE = NULL;

Surrogate* SGT_XML_STELLA_CONS = NULL;

Surrogate* SGT_XML_STELLA_XML_ATTRIBUTE = NULL;

Symbol* SYM_XML_STELLA_XML_ELEMENT_MATCHp = NULL;

Symbol* SYM_XML_STELLA_NULL = NULL;

Symbol* SYM_XML_STELLA_STRING_EQLp = NULL;

Symbol* SYM_XML_STELLA_OTHERWISE = NULL;

Symbol* SYM_XML_STELLA_COND = NULL;

Surrogate* SGT_XML_STELLA_SYMBOL = NULL;

Symbol* SYM_XML_STELLA_LET = NULL;

Symbol* SYM_XML_STELLA_XML_ELEMENT = NULL;

Symbol* SYM_XML_STELLA_STARTUP_XML = NULL;

Symbol* SYM_XML_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
