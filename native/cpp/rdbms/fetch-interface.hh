//  -*- Mode: C++ -*-

// fetch-interface.hh

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




namespace rdbms {
  using namespace stella;
  using namespace logic;

// Function signatures:
Object* runFetchQuery(const char* host, int port, const char* queryId, const char* taskId, const char* subtaskId, const char* database, const char* parameters);
const char* normalizeFetchQueryArguments(Proposition* proposition, Object* arguments, Cons*& _Return1, PropertyList*& _Return2);
Iterator* helpMemoizeFetchEdbQuery(Proposition* proposition, LogicObject* database, Object* arguments);
Iterator* fetchEdbQuery(Proposition* proposition, LogicObject* database, Object* arguments);
Cons* parseFetchXmlAnswer(Cons* xmlanswer, NamedDescription* relation, Cons* outputcolumns);
Cons* parseOneFetchXmlObject(Cons* object, NamedDescription* relation, Cons* outputcolumns);
void startFetchEdbGateway(int port);
void evaluateFetchQuery(KeyValueList* keys, std::ostream* out);
Cons* buildOneTableAssertion(NamedDescription* tableRelation, Cons* tuple, Module* dbModule);
Cons* generateTableAssertions(const char* tableName, Cons* xmlAnswer, Module* module, Module* dbModule);
const char* lookupStringValue(NamedDescription* relation, LogicObject* instance, Module* mod);
Cons* fetchQueryAssertions(const char* host, int port, LogicObject* fetchQuery, const char* taskId, const char* subtaskId, const char* database, const char* parameterValue, Module* targetModule, Module* dbModule);
void startupFetchInterface();

// Auxiliary global declarations:
extern Surrogate* SGT_FETCH_INTERFACE_RDBMS_RUN_FETCH_QUERY;
extern Surrogate* SGT_FETCH_INTERFACE_STELLA_CONS;
extern Surrogate* SGT_FETCH_INTERFACE_STELLA_XML_ELEMENT;
extern Keyword* KWD_FETCH_INTERFACE_ERROR;
extern Surrogate* SGT_FETCH_INTERFACE_RDBMS_HOST;
extern Surrogate* SGT_FETCH_INTERFACE_RDBMS_PORT;
extern Surrogate* SGT_FETCH_INTERFACE_RDBMS_TASK_ID;
extern Surrogate* SGT_FETCH_INTERFACE_RDBMS_SUBTASK_ID;
extern Surrogate* SGT_FETCH_INTERFACE_RDBMS_DB_NAME;
extern Surrogate* SGT_FETCH_INTERFACE_RDBMS_F_FETCH_EDB_QUERY_MEMO_TABLE_000;
extern Surrogate* SGT_FETCH_INTERFACE_LOGIC_QUERY_ITERATOR;
extern Symbol* SYM_FETCH_INTERFACE_LOGIC_pX;
extern Symbol* SYM_FETCH_INTERFACE_RDBMS_STARTUP_FETCH_INTERFACE;
extern Symbol* SYM_FETCH_INTERFACE_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace rdbms
