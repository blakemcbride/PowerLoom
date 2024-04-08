//  -*- Mode: C++ -*-

// xml.hh

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


namespace stella {

// Class definitions:
class XmlObject : public StandardObject {
public:
  const char* name;
  const char* surfaceForm;
public:
  virtual Surrogate* primaryType();
};

class XmlElement : public XmlObject {
public:
  const char* namespaceName;
  const char* namespaceUri;
  KeyValueList* elementDictionary;
public:
  virtual void printObject(std::ostream* stream);
  virtual boolean xmlElementMatchP(const char* name, const char* namespacE);
  virtual Surrogate* primaryType();
};

class XmlAttribute : public XmlObject {
public:
  virtual void printObject(std::ostream* stream);
  virtual boolean xmlAttributeMatchP(const char* name, const char* namespacE);
};

class XmlLocalAttribute : public XmlAttribute {
public:
  XmlElement* parentElement;
public:
  virtual boolean xmlAttributeMatchP(const char* name, const char* namespacE);
  virtual Surrogate* primaryType();
};

class XmlGlobalAttribute : public XmlAttribute {
public:
  const char* namespaceName;
  const char* namespaceUri;
public:
  virtual boolean xmlAttributeMatchP(const char* name, const char* namespacE);
  virtual Surrogate* primaryType();
};

class XmlProcessingInstruction : public XmlObject {
public:
  const char* data;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
};

class XmlDeclaration : public XmlObject {
public:
  const char* data;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
};

class XmlDoctypeDeclaration : public XmlDeclaration {
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
};

class XmlSpecial : public XmlObject {
public:
  const char* data;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
};

class XmlComment : public XmlObject {
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
};

class XmlDoctype : public StandardObject {
public:
  const char* name;
  KeyValueList* entityTable;
  KeyValueList* parameterEntityTable;
public:
  virtual void printObject(std::ostream* stream);
  virtual Surrogate* primaryType();
};

class XmlExpressionIterator : public StreamIterator {
// Iterator that yields XML expressions from an input stream.
// If the value of `region-tag' is non-`null', only XML expressions enclosed within
// matching region tags will be returned (there can be multiple such regions).
// What is a match is determined by `region-match-function'.  Usually, region tags
// will/should be at the top level, but this is not necessarily so and also not
// enforced by the iterator.
public:
  Cons* regionTag;
  cpp_function_code regionMatchFunction;
  XmlDoctype* doctype;
  // Set to `true' when iterating over a DTD definition.
  boolean doctypeIteratorP;
  // The current value of this iterator
  Object* value;
public:
  virtual void free();
  virtual Cons* consify();
  virtual boolean nextP();
  virtual Surrogate* primaryType();
};


// Global declarations:
extern const char* oXML_URNo;
extern const char* oHTML_V4_0_URNo;
extern StringHashTable* oXML_ELEMENT_NULL_NAMESPACE_TABLEo;
extern StringHashTable* oXML_ELEMENT_HASH_TABLEo;
extern StringHashTable* oXML_GLOBAL_ATTRIBUTE_HASH_TABLEo;
extern KeyValueList* oXML_BASE_ENTITY_TABLEo;
extern Cons* oXML_TOKENIZER_TABLE_DEFINITIONo;
extern TokenizerTable* oXML_TOKENIZER_TABLEo;
extern DECLARE_STELLA_SPECIAL(oXML_PRESERVE_ALL_WHITESPACEpo, boolean );
extern TokenizerTable* oXML_WHITESPACE_PRESERVING_TOKENIZER_TABLEo;

// Function signatures:
XmlObject* newXmlObject();
Object* accessXmlObjectSlotValue(XmlObject* self, Symbol* slotname, Object* value, boolean setvalueP);
XmlElement* newXmlElement();
Object* accessXmlElementSlotValue(XmlElement* self, Symbol* slotname, Object* value, boolean setvalueP);
XmlLocalAttribute* newXmlLocalAttribute();
Object* accessXmlLocalAttributeSlotValue(XmlLocalAttribute* self, Symbol* slotname, Object* value, boolean setvalueP);
XmlGlobalAttribute* newXmlGlobalAttribute();
Object* accessXmlGlobalAttributeSlotValue(XmlGlobalAttribute* self, Symbol* slotname, Object* value, boolean setvalueP);
XmlProcessingInstruction* newXmlProcessingInstruction();
Object* accessXmlProcessingInstructionSlotValue(XmlProcessingInstruction* self, Symbol* slotname, Object* value, boolean setvalueP);
XmlDeclaration* newXmlDeclaration();
Object* accessXmlDeclarationSlotValue(XmlDeclaration* self, Symbol* slotname, Object* value, boolean setvalueP);
XmlDoctypeDeclaration* newXmlDoctypeDeclaration();
XmlSpecial* newXmlSpecial();
Object* accessXmlSpecialSlotValue(XmlSpecial* self, Symbol* slotname, Object* value, boolean setvalueP);
XmlComment* newXmlComment();
XmlDoctype* newXmlDoctype();
Object* accessXmlDoctypeSlotValue(XmlDoctype* self, Symbol* slotname, Object* value, boolean setvalueP);
void resetXmlHashTables();
KvCons* makeNamespaceTable();
Cons* makeXmlCdataForm(const char* theData);
XmlAttribute* makeXmlnsAttribute(const char* name);
XmlElement* makeXmlElementInternal(const char* name, const char* namespaceName, const char* namespacE, const char* surfaceForm);
XmlElement* makeXmlElement(const char* name, const char* namespaceName, const char* namespacE);
XmlElement* makeXmlElementRespectingNamespace(const char* name, KvCons* namespaceTable);
XmlGlobalAttribute* makeXmlGlobalAttributeInternal(const char* name, const char* namespaceName, const char* namespaceUri, const char* surfaceForm);
XmlGlobalAttribute* makeXmlGlobalAttribute(const char* name, const char* namespaceName, const char* namespacE);
XmlGlobalAttribute* makeXmlGlobalAttributeRespectingNamespace(const char* name, const char* namespaceName, const char* surfaceForm, KvCons* namespaceTable);
XmlLocalAttribute* makeXmlLocalAttribute(const char* name, XmlElement* element);
XmlAttribute* makeXmlAttributeRespectingNamespace(const char* name, XmlElement* element, KvCons* namespaceTable);
boolean xmlnsAttributeP(Object* attribute);
boolean xmlnsAttributeNameP(const char* name);
const char* extractXmlnsName(const char* keyname);
void addXmlReference(const char* name, const char* substitution, KeyValueList* table);
KeyValueList* makeXmlEntityTable();
const char* decodeXmlCharRef(const char* digits);
boolean internalDtdDefinitionP(const char* definition);
InputStream* getDoctypeDefinition(Cons* doctype);
boolean externalIdHeadP(Object* attribute);
const char* decodeXmlEntityRef(XmlDoctype* doctype, const char* name, boolean peReferenceAllowedP);
const char* decodeXmlParameterEntityRef(XmlDoctype* doctype, const char* name, boolean peReferenceAllowedP);
const char* decodeXmlReference(XmlDoctype* doctype, const char* reference, boolean peReferenceAllowedP);
int findReferenceStart(const char* input, int start, int end);
const char* decodeXmlString(XmlDoctype* doctype, const char* input, boolean peReferenceAllowedP);
const char* normalizeAttributeValue(XmlDoctype* doctype, const char* input, boolean peReferenceAllowedP);
XmlDoctype* processDoctype(Cons* doctypeDeclaration);
TokenizerTable* getXmlWhitespacePreservingTokenizerTable();
TokenizerTable* getXmlTokenizerTable();
TokenizerToken* tokenizeXmlExpression(InputStream* stream, TokenizerToken* tokenlist, const char* regiontagname, boolean skiptoregionP, boolean& _Return1);
Cons* processAttributeList(Cons* reverseattributelist, XmlElement* element, KvCons* namespaceTable);
Object* xmlTokenListToSExpression(TokenizerToken* tokenlist, XmlDoctype* doctype, boolean doctypeDefinitionP);
Object* readXmlExpression(InputStream* stream, Object* startTag, boolean& _Return1);
Cons* readXmlExpressions(const char* filename);
XmlExpressionIterator* newXmlExpressionIterator();
Object* accessXmlExpressionIteratorSlotValue(XmlExpressionIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
boolean xmlRegionMatchesP(Cons* regionspec, Cons* regiontag);
XmlElement* coerceToXmlElement(Object* regiontag);
XmlExpressionIterator* xmlExpressions(InputStream* stream, Object* regiontag);
boolean xmlCdataP(Object* item);
boolean xmlElementP(Object* item);
boolean xmlAttributeP(Object* item);
boolean xmlGlobalAttributeP(Object* item);
boolean xmlLocalAttributeP(Object* item);
boolean xmlBaseAttributeP(Object* item);
boolean xmlDeclarationP(Object* item);
boolean xmlProcessingInstructionP(Object* item);
boolean xmlElementFormP(Object* form);
boolean xmlProcessingInstructionFormP(Object* form);
boolean xmlDeclarationFormP(Object* form);
boolean xmlDoctypeFormP(Object* form);
boolean xmlCdataFormP(Object* form);
XmlElement* getXmlTag(Cons* expression);
Cons* getXmlAttributes(Cons* expression);
const char* getXmlBaseAttributeValue(Cons* expression);
Cons* getXmlContent(Cons* expression);
const char* getXmlCdataContent(Cons* form);
boolean xmlGlobalAttributeMatchP(XmlGlobalAttribute* attribute, const char* name, const char* namespacE);
boolean xmlLocalAttributeMatchP(XmlLocalAttribute* attribute, const char* name, const char* elementName, const char* elementNamespace);
const char* xmlLookupAttribute(Cons* attributes, const char* name, const char* namespacE);
Cons* expandXmlTagCase(Symbol* item, Cons* clauses);
Object* xmlTagCase(Object* item, Cons* clauses);
void printXmlNonElementAttributes(OutputStream* stream, Cons* attributes);
void printXmlElementAttributes(OutputStream* stream, Cons* attributes);
void printXmlExpression(OutputStream* stream, Cons* xmlExpression, int indent);
void helpStartupXml1();
void helpStartupXml2();
void helpStartupXml3();
void helpStartupXml4();
void startupXml();

// Auxiliary global declarations:
extern Surrogate* SGT_XML_STELLA_XML_OBJECT;
extern Symbol* SYM_XML_STELLA_NAME;
extern Symbol* SYM_XML_STELLA_SURFACE_FORM;
extern Surrogate* SGT_XML_STELLA_XML_ELEMENT;
extern Symbol* SYM_XML_STELLA_NAMESPACE_NAME;
extern Symbol* SYM_XML_STELLA_NAMESPACE_URI;
extern Symbol* SYM_XML_STELLA_ELEMENT_DICTIONARY;
extern Surrogate* SGT_XML_STELLA_XML_LOCAL_ATTRIBUTE;
extern Symbol* SYM_XML_STELLA_PARENT_ELEMENT;
extern Surrogate* SGT_XML_STELLA_XML_GLOBAL_ATTRIBUTE;
extern Surrogate* SGT_XML_STELLA_XML_PROCESSING_INSTRUCTION;
extern Symbol* SYM_XML_STELLA_DATA;
extern Surrogate* SGT_XML_STELLA_XML_DECLARATION;
extern Surrogate* SGT_XML_STELLA_XML_DOCTYPE_DECLARATION;
extern Surrogate* SGT_XML_STELLA_XML_SPECIAL;
extern Surrogate* SGT_XML_STELLA_XML_COMMENT;
extern Surrogate* SGT_XML_STELLA_XML_DOCTYPE;
extern Symbol* SYM_XML_STELLA_ENTITY_TABLE;
extern Symbol* SYM_XML_STELLA_PARAMETER_ENTITY_TABLE;
extern Surrogate* SGT_XML_STELLA_STRING_WRAPPER;
extern Keyword* KWD_XML_START;
extern Keyword* KWD_XML_INCLUDE;
extern Keyword* KWD_XML_SKIP_WHITESPACE;
extern Symbol* SYM_XML_STELLA_x;
extern Keyword* KWD_XML_OPEN_TAG;
extern Keyword* KWD_XML_EOF;
extern Symbol* SYM_XML_STELLA_o;
extern Keyword* KWD_XML_OTHERWISE;
extern Keyword* KWD_XML_CONTENT;
extern Keyword* KWD_XML_START_TAG_END;
extern Keyword* KWD_XML_OPEN_END_TAG;
extern Keyword* KWD_XML_OPEN_PI_TAG;
extern Keyword* KWD_XML_OPEN_DECLARATION_TAG;
extern Keyword* KWD_XML_START_TAG;
extern Keyword* KWD_XML_OPEN_EMPTY_TAG_END;
extern Keyword* KWD_XML_SKIP_TO_ATTRIBUTE_NAME;
extern Keyword* KWD_XML_ANY;
extern Keyword* KWD_XML_START_PI_TAG;
extern Keyword* KWD_XML_OPEN_PI_TAG_END;
extern Keyword* KWD_XML_PI_TAG_DATA;
extern Keyword* KWD_XML_PI_TAG_DATA_OR_END;
extern Keyword* KWD_XML_EMPTY_TAG_END;
extern Keyword* KWD_XML_ERROR;
extern Keyword* KWD_XML_END_TAG_END;
extern Keyword* KWD_XML_END_TAG;
extern Keyword* KWD_XML_ATTRIBUTE_NAME;
extern Keyword* KWD_XML_SKIP_TO_ATTRIBUTE_VALUE;
extern Keyword* KWD_XML_SINGLE_QUOTED_ATTRIBUTE_VALUE;
extern Keyword* KWD_XML_DOUBLE_QUOTED_ATTRIBUTE_VALUE;
extern Keyword* KWD_XML_UNQUOTED_ATTRIBUTE_VALUE;
extern Keyword* KWD_XML_QUOTED_ATTRIBUTE_VALUE;
extern Keyword* KWD_XML_START_TAG_OR_COMMENT;
extern Keyword* KWD_XML_OPEN_SPECIAL_TAG;
extern Keyword* KWD_XML_START_DECLARATION_TAG;
extern Keyword* KWD_XML_DECLARATION_WHITESPACE;
extern Keyword* KWD_XML_DECLARATION_TAG_MARKUP_DATA_START;
extern Keyword* KWD_XML_SINGLE_QUOTED_DECLARATION_TAG_DATA;
extern Keyword* KWD_XML_DOUBLE_QUOTED_DECLARATION_TAG_DATA;
extern Keyword* KWD_XML_DECLARATION_TAG_DATA;
extern Keyword* KWD_XML_QUOTED_DECLARATION_TAG_DATA;
extern Keyword* KWD_XML_DECLARATION_TAG_MARKUP_DATA;
extern Keyword* KWD_XML_START_SPECIAL_TAG;
extern Keyword* KWD_XML_SPECIAL_TAG_DATA;
extern Keyword* KWD_XML_SPECIAL_TAG_DATA_OR_END;
extern Keyword* KWD_XML_SPECIAL_TAG_DATA_OR_END2;
extern Keyword* KWD_XML_DATA_TAG_END;
extern Keyword* KWD_XML_COMMENT_BODY;
extern Keyword* KWD_XML_END_COMMENT_OR_COMMENT;
extern Keyword* KWD_XML_END_COMMENT_OR_COMMENT2;
extern Keyword* KWD_XML_COMMENT;
extern Keyword* KWD_XML_ATTRIBUTE_VALUE;
extern Keyword* KWD_XML_WHITE_SPACE;
extern Surrogate* SGT_XML_STELLA_XML_EXPRESSION_ITERATOR;
extern Symbol* SYM_XML_STELLA_REGION_TAG;
extern Symbol* SYM_XML_STELLA_REGION_MATCH_FUNCTION;
extern Symbol* SYM_XML_STELLA_DOCTYPE;
extern Symbol* SYM_XML_STELLA_DOCTYPE_ITERATORp;
extern Symbol* SYM_XML_STELLA_VALUE;
extern Surrogate* SGT_XML_STELLA_CONS;
extern Surrogate* SGT_XML_STELLA_XML_ATTRIBUTE;
extern Symbol* SYM_XML_STELLA_XML_ELEMENT_MATCHp;
extern Symbol* SYM_XML_STELLA_NULL;
extern Symbol* SYM_XML_STELLA_STRING_EQLp;
extern Symbol* SYM_XML_STELLA_OTHERWISE;
extern Symbol* SYM_XML_STELLA_COND;
extern Surrogate* SGT_XML_STELLA_SYMBOL;
extern Symbol* SYM_XML_STELLA_LET;
extern Symbol* SYM_XML_STELLA_XML_ELEMENT;
extern Symbol* SYM_XML_STELLA_STARTUP_XML;
extern Symbol* SYM_XML_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
