//  -*- Mode: C++ -*-

// api-support.hh

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
 | The Original Code is the PowerLoom KR&R System.                            |
 |                                                                            |
 | The Initial Developer of the Original Code is                              |
 | UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
 | 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
 |                                                                            |
 | Portions created by the Initial Developer are Copyright (C) 1997-2023      |
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
 +----------------------------- END LICENSE BLOCK ----------------------------+
*/




namespace logic {
  using namespace stella;

// Function signatures:
boolean classNamesNextP(AllPurposeIterator* self);
boolean allPropositionsNextP(AllPurposeIterator* self);
Iterator* allPropositions(Module* module, boolean localP);
boolean filterInconsistentPropositionP(Object* self, AllPurposeIterator* iterator);
Iterator* allInconsistentPropositions(Module* module, boolean localP);
boolean locallyModifiedPropositionP(Proposition* proposition, Module* module);
boolean filterLocallyModifiedPropositionP(Object* self, AllPurposeIterator* iterator);
Iterator* allLocallyModifiedPropositions(Module* module);
boolean visibleTermP(LogicObject* term, Context* context, boolean localP);
Iterator* allUnnamedTerms(Module* module, boolean localP);
boolean namedTermP(Object* term, AllPurposeIterator* iter);
Iterator* allNamedTerms(Module* module, boolean localP);
Iterator* allTerms(Module* module, boolean localP);
boolean filterInstanceP(LogicObject* self, AllPurposeIterator* iterator);
Iterator* allNamedInstances(Module* module, boolean localP);
Iterator* allInstances(Module* module, boolean localP);
LogicObject* stringToLogicObject(const char* string);
void startupApiSupport();

// Auxiliary global declarations:
extern Surrogate* SGT_API_SUPPORT_LOGIC_TRUTH_VALUE;
extern Surrogate* SGT_API_SUPPORT_LOGIC_LOGIC_OBJECT;
extern Surrogate* SGT_API_SUPPORT_LOGIC_PATTERN_VARIABLE;
extern Surrogate* SGT_API_SUPPORT_LOGIC_SKOLEM;
extern Surrogate* SGT_API_SUPPORT_LOGIC_NAMED_DESCRIPTION;
extern Surrogate* SGT_API_SUPPORT_LOGIC_DESCRIPTION;
extern Surrogate* SGT_API_SUPPORT_STELLA_THING;
extern Symbol* SYM_API_SUPPORT_LOGIC_STARTUP_API_SUPPORT;
extern Symbol* SYM_API_SUPPORT_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace logic
