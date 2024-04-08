//  -*- Mode: C++ -*-

// ontology.hh

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
void startupOntology();

// Auxiliary global declarations:
extern Symbol* SYM_ONTOLOGY_RDBMS_DATABASE;
extern Keyword* KWD_ONTOLOGY_DOCUMENTATION;
extern Symbol* SYM_ONTOLOGY_RDBMS_SQL_DATABASE;
extern Symbol* SYM_ONTOLOGY_RDBMS_PROTOCOL;
extern Keyword* KWD_ONTOLOGY__g;
extern Keyword* KWD_ONTOLOGY_GOES_TRUE_DEMON;
extern Symbol* SYM_ONTOLOGY_RDBMS_DB_UPDATE_DEMON;
extern Keyword* KWD_ONTOLOGY_GOES_UNKNOWN_DEMON;
extern Symbol* SYM_ONTOLOGY_RDBMS_SERVER_TYPE;
extern Symbol* SYM_ONTOLOGY_RDBMS_DSN;
extern Symbol* SYM_ONTOLOGY_RDBMS_CONNECTION_STRING;
extern Symbol* SYM_ONTOLOGY_RDBMS_ODBC_CONNECTION_STRING;
extern Symbol* SYM_ONTOLOGY_RDBMS_JDBC_CONNECTION_STRING;
extern Symbol* SYM_ONTOLOGY_RDBMS_HOST;
extern Symbol* SYM_ONTOLOGY_RDBMS_PORT;
extern Symbol* SYM_ONTOLOGY_RDBMS_USER;
extern Symbol* SYM_ONTOLOGY_RDBMS_PASSWORD;
extern Symbol* SYM_ONTOLOGY_RDBMS_DB_NAME;
extern Symbol* SYM_ONTOLOGY_RDBMS_DB_CONNECTION;
extern Symbol* SYM_ONTOLOGY_RDBMS_pCONN;
extern Keyword* KWD_ONTOLOGY_AXIOMS;
extern Symbol* SYM_ONTOLOGY_RDBMS_RELATION_TABLE;
extern Symbol* SYM_ONTOLOGY_RDBMS_RELATION_DATABASE;
extern Symbol* SYM_ONTOLOGY_RDBMS_RELATION_COLUMN_NAME;
extern Symbol* SYM_ONTOLOGY_RDBMS_RELATION_COLUMN_MODULE_NAME;
extern Symbol* SYM_ONTOLOGY_RDBMS_RELATION_COLUMN_MODULE_REFERENCE;
extern Symbol* SYM_ONTOLOGY_RDBMS_QUERY_EVALUATOR;
extern Symbol* SYM_ONTOLOGY_RDBMS_SUPPORTS_DB_TYPE;
extern Keyword* KWD_ONTOLOGY_CLOSED;
extern Symbol* SYM_ONTOLOGY_STELLA_TRUE;
extern Symbol* SYM_ONTOLOGY_RDBMS_QUERY_PATTERN;
extern Symbol* SYM_ONTOLOGY_RDBMS_QUERY_SQL_DATABASE;
extern Keyword* KWD_ONTOLOGY_VARIABLE_ARITY;
extern Keyword* KWD_ONTOLOGY_RELATION_SPECIALIST;
extern Symbol* SYM_ONTOLOGY_RDBMS_QUERY_SQL_DATABASE_SPECIALIST;
extern Symbol* SYM_ONTOLOGY_RDBMS_QUERY_DATABASE;
extern Symbol* SYM_ONTOLOGY_RDBMS_QUERY_DATABASE_SPECIALIST;
extern Symbol* SYM_ONTOLOGY_RDBMS_FETCH_EDB_DATABASE;
extern Symbol* SYM_ONTOLOGY_RDBMS_TASK_ID;
extern Symbol* SYM_ONTOLOGY_RDBMS_SUBTASK_ID;
extern Symbol* SYM_ONTOLOGY_RDBMS_FETCH_QUERY;
extern Symbol* SYM_ONTOLOGY_RDBMS_FETCH_QUERY_TYPE_1;
extern Symbol* SYM_ONTOLOGY_RDBMS_FETCH_QUERY_TYPE_2;
extern Symbol* SYM_ONTOLOGY_RDBMS_QUERY_TABLE_NAME;
extern Symbol* SYM_ONTOLOGY_RDBMS_QUERY_PARAMETER_NAME;
extern Symbol* SYM_ONTOLOGY_RDBMS_STARTUP_ONTOLOGY;
extern Symbol* SYM_ONTOLOGY_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace rdbms
