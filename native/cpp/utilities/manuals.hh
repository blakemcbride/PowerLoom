//  -*- Mode: C++ -*-

// manuals.hh

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
| Portions created by the Initial Developer are Copyright (C) 2001-2023      |
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



namespace stella_utilities {
  using namespace stella;

// Global declarations:
extern List* oTEXINFO_STYLE_FEATURESo;
extern const char* oTEXINFO_WORD_DELIMITERSo;
extern DECLARE_STELLA_SPECIAL(oMANUAL_OUTPUT_LANGUAGEo, Keyword* );
extern HashTable* oDOCUMENTED_OBJECTS_REGISTRYo;
extern DECLARE_STELLA_SPECIAL(oMANUAL_OUTPUT_STREAMo, OutputStream* );
extern const char* oMANUAL_TEMPLATE_COMMAND_PREFIXo;

// Function signatures:
boolean texinfoSpecialCharacterP(char ch);
const char* texinfoEscapeString(const char* string);
const char* yieldTexinfoTypeSpec(Object* typeSpec);
const char* yieldTexinfoBareName(Object* name);
const char* yieldTexinfoParameterName(const char* name);
const char* yieldTexinfoConstant(Symbol* name);
const char* texinfoGetParagraphCommand(const char* string, int start);
void texinfoDescribeDocumentationString(Object* object, const char* documentation, OutputStream* stream, List* parameters);
void texinfoDescribeVariable(GlobalVariable* variable, OutputStream* stream);
void texinfoDescribeClass(Class* clasS, OutputStream* stream);
void texinfoDescribeSlot(StorageSlot* slot, OutputStream* stream);
List* texinfoGetRealMethodParameterNames(MethodSlot* method);
List* texinfoGetRealMethodParametersAndTypes(MethodSlot* method, List*& _Return1, List*& _Return2);
void texinfoDescribeMethod(MethodSlot* method, OutputStream* stream);
void texinfoDescribeTypeDeclaration(const char* parameter, StandardObject* type, const char* modifier, OutputStream* stream);
void texinfoDescribeUnimplementedObject(Object* specification, OutputStream* stream);
void registerDocumentedObject(Object* object);
boolean alreadyDocumentedObjectP(Object* object);
void clearDocumentedObjectsRegistry();
Object* lookupObjectFromSpecification(Object* specification);
boolean texinfoObjectL(Object* object1, Object* object2);
void manualDescribeUncategorizedObjects(Module* module, OutputStream* stream);
void manualDescribeObject(Object* object, Object* specification, OutputStream* stream);
void generateManual(Cons* manualSpec);
void generateManualFromTemplate(const char* templatefile, const char* outputfile);
const char* manualExpandTemplateCommands(const char* line);
void texinfoInsertDoc(Object* spec);
void texinfoInsertPreamble();
void helpStartupManuals1();
void startupManuals();

// Auxiliary global declarations:
extern Surrogate* SGT_MANUALS_STELLA_CONS;
extern Surrogate* SGT_MANUALS_STELLA_TYPE_SPEC;
extern Symbol* SYM_MANUALS_STELLA_VARIABLE_TYPE_SPECIFIER;
extern Symbol* SYM_MANUALS_STELLA_DOCUMENTATION;
extern Symbol* SYM_MANUALS_STELLA_SLOT_TYPE_SPECIFIER;
extern Symbol* SYM_MANUALS_STELLA_aREST;
extern Symbol* SYM_MANUALS_STELLA_aBODY;
extern Symbol* SYM_MANUALS_STELLA_METHOD_MACROp;
extern Symbol* SYM_MANUALS_STELLA_METHOD_COMMANDp;
extern Symbol* SYM_MANUALS_STELLA_METHOD_VARIABLE_ARGUMENTSp;
extern Symbol* SYM_MANUALS_STELLA_METHOD_BODY_ARGUMENTp;
extern Keyword* KWD_MANUALS_INFIX_PARAMETER_LISTS;
extern Keyword* KWD_MANUALS_TEXINFO;
extern Surrogate* SGT_MANUALS_STELLA_SLOT;
extern Surrogate* SGT_MANUALS_STELLA_GLOBAL_VARIABLE;
extern Surrogate* SGT_MANUALS_STELLA_MODULE;
extern Symbol* SYM_MANUALS_UTILITIES_MANUAL_DESCRIBE_OBJECT;
extern Symbol* SYM_MANUALS_UTILITIES_STARTUP_MANUALS;
extern Symbol* SYM_MANUALS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella_utilities
