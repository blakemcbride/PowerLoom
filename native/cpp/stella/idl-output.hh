//  -*- Mode: C++ -*-

// idl-output.hh

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

// Global declarations:
extern DECLARE_STELLA_SPECIAL(oIDL_INDENT_CHARSo, int );

// Function signatures:
void idlOutputParseTree(Cons* constree);
void idlOutputStatement(Object* statement);
void idlIndent();
void idlBumpIndent();
void idlUnbumpIndent();
void idlOutputTypedef(Cons* typedeF);
void idlOutputEnumerands(Cons* enumerands);
void idlOutputEnum(Cons* enuM);
void idlOutputTypeExpression(Cons* typeexpression);
void stringIdlOutputLiteral(const char* string);
void idlOutputAtomicExpression(Object* atom);
void idlOutputComment(StringWrapper* tree);
void idlOutputIdentifier(StringWrapper* identifier);
void idlOutputDerivedClasses(Cons* classList);
void idlOutputTemplateParameters(Cons* parameters);
boolean idlOutputTemplateClassesP();
void idlOutputInterface(Cons* classdef);
void idlOutputStruct(Cons* classdef);
void idlOutputOneFormalParameter(Cons* parameter);
void idlOutputFormalParameters(Cons* parameters);
void idlOutputFunctionSignature(Cons* function);
void idlOutputDeclarations(Cons* declarations);
void idlOutputSignature(Cons* signature, boolean outputmethodclassP);
void idlOutputSignatures(Cons* signatures);
void startupIdlOutput();

// Auxiliary global declarations:
extern Surrogate* SGT_IDL_OUTPUT_STELLA_CONS;
extern Symbol* SYM_IDL_OUTPUT_STELLA_IDL_COMMENT;
extern Symbol* SYM_IDL_OUTPUT_STELLA_IDL_TYPEDEF;
extern Symbol* SYM_IDL_OUTPUT_STELLA_IDL_ENUM;
extern Symbol* SYM_IDL_OUTPUT_STELLA_IDL_INTERFACE;
extern Symbol* SYM_IDL_OUTPUT_STELLA_IDL_STRUCT;
extern Symbol* SYM_IDL_OUTPUT_STELLA_IDL_DECLARATIONS;
extern Symbol* SYM_IDL_OUTPUT_STELLA_IDL_IDENT;
extern Symbol* SYM_IDL_OUTPUT_STELLA_IDL_TYPE;
extern Symbol* SYM_IDL_OUTPUT_STELLA_IDL_SIGNATURES;
extern Symbol* SYM_IDL_OUTPUT_STELLA_IDL_VAR_ARGS;
extern Symbol* SYM_IDL_OUTPUT_STELLA_STARTUP_IDL_OUTPUT;
extern Symbol* SYM_IDL_OUTPUT_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
