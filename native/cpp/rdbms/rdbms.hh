//  -*- Mode: C++ -*-

// rdbms.hh

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

// Class definitions:
class ConnectionWrapper : public LogicThing {
public:
  sdbc::Connection* wrapperValue;
public:
  virtual Surrogate* primaryType();
};

class RelationTableInfo : public StandardObject {
// Data structure that associates a PowerLoom relation representing
// a database table or query with various information about its columns, value coercion, etc.
public:
  NamedDescription* relation;
  Object* database;
  Keyword* dbmsName;
  const char* tableName;
  const char* tableAlias;
  Cons* columnList;
  Vector* columnVector;
  KeyValueMap* columnIndex;
  Object* adjunct;
public:
  virtual Surrogate* primaryType();
};

class RelationColumnInfo : public StandardObject {
public:
  RelationTableInfo* tableInfo;
  const char* columnName;
  Symbol* columnVariable;
  int columnIndex;
  NamedDescription* columnType;
  const char* columnDbType;
  const char* moduleName;
  const char* moduleReference;
  Module* module;
  boolean moduleLocalP;
  RelationColumnInfo* moduleReferenceColumn;
  cpp_function_code coercionFunction;
public:
  virtual Surrogate* primaryType();
};



// Function signatures:
LogicObject* defuntable(Cons* args);
LogicObject* defuntableEvaluatorWrapper(Cons* arguments);
NamedDescription* callDefuntable(Cons* arguments);
LogicObject* deftable(Cons* args);
LogicObject* deftableEvaluatorWrapper(Cons* arguments);
NamedDescription* callDeftable(Cons* arguments);
PropertyList* parseOneColumnSpec(Object* columnspec);
Cons* parseColumnSpecs(Object* relconst, Object* columnspecs, Cons*& _Return1);
LogicObject* defdb(Cons* args);
LogicObject* defdbEvaluatorWrapper(Cons* arguments);
LogicObject* callDefdb(Cons* arguments);
Cons* extractRdbmsOptions(Symbol* selfname, Cons* options, Cons*& _Return1);
void assertRdbmsConnectionInfo(const char* dbInstanceName, Cons* options);
void assertRdbmsConnectionInfoEvaluatorWrapper(Cons* arguments);
LogicObject* defquery(Cons* args);
LogicObject* defqueryEvaluatorWrapper(Cons* arguments);
NamedDescription* callDefquery(Cons* arguments);
ConnectionWrapper* newConnectionWrapper();
Object* accessConnectionWrapperSlotValue(ConnectionWrapper* self, Symbol* slotname, Object* value, boolean setvalueP);
StringWrapper* normalizeConnectionArgument(Object* arg);
sdbc::Connection* connectToDatabase(LogicObject* database);
void disconnectFromDatabase(LogicObject* database);
sdbc::Connection* getConnectionFromDatabase(LogicObject* database);
sdbc::Connection* getConnectionFromPredicate(Surrogate* relationref);
Iterator* allocateResultSetIterator(sdbc::Connection* connection, LogicObject* relation, const char* sqlstatement);
boolean resultSetIteratorNextP(AllPurposeIterator* self);
NamedDescription* getTableRelation(const char* tableName, Module* module);
int getTableColumnIndex(NamedDescription* tableRelation, const char* columnName, Module* module);
StringWrapper* getTableColumnModuleName(NamedDescription* tablerelation, int columnindex);
StringWrapper* getTableColumnModuleReference(NamedDescription* tablerelation, int columnindex);
StringWrapper* getTableColumnName(NamedDescription* tablerelation, int columnindex);
Cons* getTableColumnNames(NamedDescription* tablerelation);
RelationTableInfo* newRelationTableInfo();
Object* accessRelationTableInfoSlotValue(RelationTableInfo* self, Symbol* slotname, Object* value, boolean setvalueP);
RelationColumnInfo* newRelationColumnInfo();
Object* accessRelationColumnInfoSlotValue(RelationColumnInfo* self, Symbol* slotname, Object* value, boolean setvalueP);
RelationTableInfo* createRelationTableInfo(NamedDescription* relation);
Module* getModuleUsingReference(RelationColumnInfo* column, Cons* values);
RelationTableInfo* getRelationTableInfo(NamedDescription* tablerelation);
boolean collectionValuedConstraintP(Object* argument);
Cons* collectionValuedConstraintElements(Object* argument);
void printSqlValue(OutputStream* stream, Object* value, RelationColumnInfo* column);
void printColumnConstraint(OutputStream* sql, RelationColumnInfo* column, const char* value, boolean casesensitiveP);
void printArgumentConstraint(OutputStream* sql, Object* argument, RelationColumnInfo* column);
void printSqlColumnList(OutputStream* stream, RelationTableInfo* tableInfo);
void printSqlConstraintList(OutputStream* stream, RelationTableInfo* tableInfo, Vector* arguments);
const char* createSqlFromProposition(Proposition* proposition);
Iterator* allocateDbtableSpecialistIterator(ControlFrame* frame);
Keyword* retrieveNextDbQuerySolution(ControlFrame* frame, Keyword* lastmove);
Keyword* dbtableSpecialist(ControlFrame* frame, Keyword* lastmove);
Cons* getQueryPatternEvaluators(Surrogate* relationref);
Cons* normalizeSqlJoinArguments(RelationTableInfo* tableinfo, Object* arguments, Cons*& _Return1);
Iterator* helpMemoizeSqlJoin(Proposition* proposition, LogicObject* database, Object* arguments);
Iterator* sqlJoin(Proposition* proposition, LogicObject* database, Object* arguments);
void collectVariableBinding(const char* name, Object* type, Object* binding, KeyValueList* bindings);
const char* createSqlQueryFromProposition(Proposition* proposition, LogicObject* database, Object* arguments);
Iterator* helpMemoizeSqlQuery(Proposition* proposition, LogicObject* database, Object* arguments);
const char* sqlQueryInstantiateConstraints(const char* sql, KeyValueList* bindings);
Iterator* sqlQuery(Proposition* proposition, LogicObject* database, Object* arguments);
Iterator* allocateQuerySpecialistIterator(ControlFrame* frame);
Keyword* querySpecialist(ControlFrame* frame, Keyword* lastmove);
KeyValueList* collectQueryDatabaseSpecialistBindings(ControlFrame* frame, int firstargindex);
Keyword* bindNextDatabaseTupleToArguments(ControlFrame* frame, int firstargindex);
Keyword* querySqlDatabaseSpecialist(ControlFrame* frame, Keyword* lastmove);
Keyword* queryDatabaseSpecialist(ControlFrame* frame, Keyword* lastmove);
void dbUpdateDemon(Proposition* dbproposition);
void checkForExternalDbUpdates(Proposition* proposition, LogicObject* database);
Object* getQueryPatternMemoizationKey(Proposition* proposition);
Cons* coerceValues(Cons* values, RelationTableInfo* table);
Object* coerceStringToPowerloomObject(const char* value, NamedDescription* type, Module* module, boolean localP);
int numberStringToInteger(const char* x);
const char* coercePowerloomObjectToString(Object* object, NamedDescription* type);
Object* findOrCreateInstance(const char* name, NamedDescription* type, Module* module, boolean localP);
const char* createSqlAssertionFromProposition(Proposition* proposition, Keyword* mode);
void dbRelationGoesTrue(Proposition* proposition);
void dbRelationGoesUnknown(Proposition* proposition);
void dbRelationGoesFalse(Proposition* proposition);
void dbRelationUpdateDemon(Proposition* proposition, Keyword* updateMode);
void helpStartupRdbms1();
void helpStartupRdbms2();
void helpStartupRdbms3();
void helpStartupRdbms4();
void startupRdbms();

// Auxiliary global declarations:
extern Symbol* SYM_RDBMS_RDBMS_DEFUNTABLE;
extern Symbol* SYM_RDBMS_RDBMS_RELATION_TABLE;
extern Symbol* SYM_RDBMS_RDBMS_RELATION_DATABASE;
extern Symbol* SYM_RDBMS_PL_KERNEL_KB_RELATION_SPECIALIST;
extern Symbol* SYM_RDBMS_RDBMS_DBTABLE_SPECIALIST;
extern Keyword* KWD_RDBMS_AXIOMS;
extern Symbol* SYM_RDBMS_RDBMS_DEFTABLE;
extern Surrogate* SGT_RDBMS_STELLA_CONS;
extern Keyword* KWD_RDBMS_ERROR;
extern Keyword* KWD_RDBMS_NAME;
extern Keyword* KWD_RDBMS_VARIABLE;
extern Keyword* KWD_RDBMS_TYPE;
extern Keyword* KWD_RDBMS_MODULE_NAME;
extern Keyword* KWD_RDBMS_MODULE_REFERENCE;
extern Symbol* SYM_RDBMS_RDBMS_RELATION_COLUMN_NAME;
extern Symbol* SYM_RDBMS_RDBMS_RELATION_COLUMN_MODULE_NAME;
extern Symbol* SYM_RDBMS_RDBMS_RELATION_COLUMN_MODULE_REFERENCE;
extern Symbol* SYM_RDBMS_RDBMS_DEFDB;
extern Symbol* SYM_RDBMS_RDBMS_DATABASE;
extern Keyword* KWD_RDBMS_CONNECTION_STRING;
extern Surrogate* SGT_RDBMS_STELLA_STRING;
extern Keyword* KWD_RDBMS_JDBC_CONNECTION_STRING;
extern Keyword* KWD_RDBMS_ODBC_CONNECTION_STRING;
extern Keyword* KWD_RDBMS_DSN;
extern Keyword* KWD_RDBMS_DB;
extern Keyword* KWD_RDBMS_HOST;
extern Keyword* KWD_RDBMS_PORT;
extern Surrogate* SGT_RDBMS_STELLA_INTEGER;
extern Keyword* KWD_RDBMS_USER;
extern Keyword* KWD_RDBMS_PASSWORD;
extern Keyword* KWD_RDBMS_MODULE;
extern Surrogate* SGT_RDBMS_STELLA_MODULE;
extern Keyword* KWD_RDBMS_CONFIGURATION;
extern Surrogate* SGT_RDBMS_STELLA_CONFIGURATION_TABLE;
extern Keyword* KWD_RDBMS_DB_NAME;
extern Symbol* SYM_RDBMS_RDBMS_DEFQUERY;
extern Symbol* SYM_RDBMS_RDBMS_QUERY_SPECIALIST;
extern Surrogate* SGT_RDBMS_RDBMS_CONNECTION_WRAPPER;
extern Symbol* SYM_RDBMS_STELLA_WRAPPER_VALUE;
extern Surrogate* SGT_RDBMS_LOGIC_LOGIC_OBJECT;
extern Surrogate* SGT_RDBMS_RDBMS_PROTOCOL;
extern Surrogate* SGT_RDBMS_RDBMS_SERVER_TYPE;
extern Surrogate* SGT_RDBMS_RDBMS_HOST;
extern Surrogate* SGT_RDBMS_RDBMS_PORT;
extern Surrogate* SGT_RDBMS_RDBMS_USER;
extern Surrogate* SGT_RDBMS_RDBMS_PASSWORD;
extern Surrogate* SGT_RDBMS_RDBMS_DB_NAME;
extern Surrogate* SGT_RDBMS_RDBMS_ODBC_CONNECTION_STRING;
extern Surrogate* SGT_RDBMS_RDBMS_CONNECTION_STRING;
extern Surrogate* SGT_RDBMS_RDBMS_DSN;
extern Keyword* KWD_RDBMS_PROTOCOL;
extern Keyword* KWD_RDBMS_SERVER_TYPE;
extern Keyword* KWD_RDBMS_EXTENSIONAL_ASSERTION;
extern Surrogate* SGT_RDBMS_RDBMS_DB_CONNECTION;
extern Surrogate* SGT_RDBMS_RDBMS_RELATION_DATABASE;
extern Symbol* SYM_RDBMS_LOGIC_pX;
extern Surrogate* SGT_RDBMS_RDBMS_RELATION_TABLE_INFO;
extern Symbol* SYM_RDBMS_STELLA_RELATION;
extern Symbol* SYM_RDBMS_RDBMS_DBMS_NAME;
extern Symbol* SYM_RDBMS_STELLA_TABLE_NAME;
extern Symbol* SYM_RDBMS_RDBMS_TABLE_ALIAS;
extern Symbol* SYM_RDBMS_RDBMS_COLUMN_LIST;
extern Symbol* SYM_RDBMS_RDBMS_COLUMN_VECTOR;
extern Symbol* SYM_RDBMS_RDBMS_COLUMN_INDEX;
extern Symbol* SYM_RDBMS_RDBMS_ADJUNCT;
extern Surrogate* SGT_RDBMS_RDBMS_RELATION_COLUMN_INFO;
extern Symbol* SYM_RDBMS_RDBMS_TABLE_INFO;
extern Symbol* SYM_RDBMS_RDBMS_COLUMN_NAME;
extern Symbol* SYM_RDBMS_RDBMS_COLUMN_VARIABLE;
extern Symbol* SYM_RDBMS_RDBMS_COLUMN_TYPE;
extern Symbol* SYM_RDBMS_RDBMS_COLUMN_DB_TYPE;
extern Symbol* SYM_RDBMS_STELLA_MODULE_NAME;
extern Symbol* SYM_RDBMS_RDBMS_MODULE_REFERENCE;
extern Symbol* SYM_RDBMS_STELLA_MODULE;
extern Symbol* SYM_RDBMS_RDBMS_MODULE_LOCALp;
extern Symbol* SYM_RDBMS_RDBMS_MODULE_REFERENCE_COLUMN;
extern Symbol* SYM_RDBMS_RDBMS_COERCION_FUNCTION;
extern Keyword* KWD_RDBMS_UNKNOWN;
extern Surrogate* SGT_RDBMS_RDBMS_RELATION_TABLE;
extern Surrogate* SGT_RDBMS_RDBMS_F_GET_RELATION_TABLE_INFO_MEMO_TABLE_000;
extern Keyword* KWD_RDBMS_STRING_CONSTANT;
extern Surrogate* SGT_RDBMS_STELLA_NUMBER;
extern Surrogate* SGT_RDBMS_STELLA_BOOLEAN;
extern Keyword* KWD_RDBMS_MYSQL;
extern Surrogate* SGT_RDBMS_STELLA_STRING_WRAPPER;
extern Symbol* SYM_RDBMS_STELLA_ITERATOR;
extern Surrogate* SGT_RDBMS_RDBMS_DATABASE;
extern Surrogate* SGT_RDBMS_RDBMS_F_ALLOCATE_DBTABLE_SPECIALIST_ITERATOR_MEMO_TABLE_000;
extern Keyword* KWD_RDBMS_FAILURE;
extern Keyword* KWD_RDBMS_DB_LOOKUP;
extern Keyword* KWD_RDBMS_CONTINUING_SUCCESS;
extern Keyword* KWD_RDBMS_FINAL_SUCCESS;
extern Keyword* KWD_RDBMS_TECHNICAL;
extern Keyword* KWD_RDBMS_LAY;
extern Symbol* SYM_RDBMS_RDBMS_pREL;
extern Symbol* SYM_RDBMS_RDBMS_pEV;
extern Symbol* SYM_RDBMS_RDBMS_pDB;
extern Symbol* SYM_RDBMS_RDBMS_pARGS;
extern Symbol* SYM_RDBMS_STELLA_AND;
extern Symbol* SYM_RDBMS_RDBMS_QUERY_PATTERN;
extern Symbol* SYM_RDBMS_STELLA_EXISTS;
extern Symbol* SYM_RDBMS_RDBMS_pDB_TYPE;
extern Symbol* SYM_RDBMS_RDBMS_SUPPORTS_DB_TYPE;
extern Symbol* SYM_RDBMS_RDBMS_INSTANCE_OF;
extern Keyword* KWD_RDBMS_DONT_OPTIMIZEp;
extern Keyword* KWD_RDBMS_HOW_MANY;
extern Keyword* KWD_RDBMS_ALL;
extern Keyword* KWD_RDBMS_INFERENCE_LEVEL;
extern Keyword* KWD_RDBMS_ASSERTION;
extern Symbol* SYM_RDBMS_RDBMS_F_GET_QUERY_PATTERN_EVALUATORS_QUERY_000;
extern Surrogate* SGT_RDBMS_RDBMS_F_GET_QUERY_PATTERN_EVALUATORS_MEMO_TABLE_000;
extern Symbol* SYM_RDBMS_RDBMS_F_GET_QUERY_PATTERN_EVALUATORS_QUERY_001;
extern Surrogate* SGT_RDBMS_RDBMS_F_SQL_JOIN_MEMO_TABLE_000;
extern Keyword* KWD_RDBMS_VALUE;
extern Keyword* KWD_RDBMS_WHITE_SPACE;
extern Keyword* KWD_RDBMS_SET;
extern Keyword* KWD_RDBMS_NONE;
extern Surrogate* SGT_RDBMS_RDBMS_F_SQL_QUERY_MEMO_TABLE_000;
extern Keyword* KWD_RDBMS_TERMINAL_FAILURE;
extern Surrogate* SGT_RDBMS_RDBMS_SQL_DATABASE;
extern Keyword* KWD_RDBMS_EXTERNAL_DB_UPDATE;
extern Surrogate* SGT_RDBMS_LOGIC_NAMED_DESCRIPTION;
extern Surrogate* SGT_RDBMS_STELLA_TRUE;
extern Surrogate* SGT_RDBMS_STELLA_FALSE;
extern Surrogate* SGT_RDBMS_STELLA_THING;
extern Keyword* KWD_RDBMS_CLIP;
extern Keyword* KWD_RDBMS_ASSERT;
extern Keyword* KWD_RDBMS_RETRACT;
extern Keyword* KWD_RDBMS_ASSERT_TRUE;
extern Keyword* KWD_RDBMS_PRESUME_TRUE;
extern Keyword* KWD_RDBMS_RETRACT_TRUE;
extern Keyword* KWD_RDBMS_RETRACT_FALSE;
extern Keyword* KWD_RDBMS_ASSERT_FALSE;
extern Keyword* KWD_RDBMS_PRESUME_FALSE;
extern Keyword* KWD_RDBMS_CONCEIVE;
extern Symbol* SYM_RDBMS_RDBMS_STARTUP_RDBMS;
extern Symbol* SYM_RDBMS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace rdbms
