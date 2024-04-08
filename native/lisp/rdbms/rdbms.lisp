;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; rdbms.lisp

#|
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
|#

(CL:IN-PACKAGE "STELLA")

;;; Auxiliary variables:

(CL:DEFVAR SYM-RDBMS-RDBMS-DEFUNTABLE NULL)
(CL:DEFVAR KWD-RDBMS-COMMON-LISP NULL)
(CL:DEFVAR KWD-RDBMS-FUNCTION NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-RELATION-TABLE NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-RELATION-DATABASE NULL)
(CL:DEFVAR SYM-RDBMS-PL-KERNEL-KB-RELATION-SPECIALIST NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-DBTABLE-SPECIALIST NULL)
(CL:DEFVAR KWD-RDBMS-AXIOMS NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-DEFTABLE NULL)
(CL:DEFVAR SGT-RDBMS-STELLA-CONS NULL)
(CL:DEFVAR KWD-RDBMS-ERROR NULL)
(CL:DEFVAR KWD-RDBMS-NAME NULL)
(CL:DEFVAR KWD-RDBMS-VARIABLE NULL)
(CL:DEFVAR KWD-RDBMS-TYPE NULL)
(CL:DEFVAR KWD-RDBMS-MODULE-NAME NULL)
(CL:DEFVAR KWD-RDBMS-MODULE-REFERENCE NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-RELATION-COLUMN-NAME NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-RELATION-COLUMN-MODULE-NAME NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-RELATION-COLUMN-MODULE-REFERENCE NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-DEFDB NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-DATABASE NULL)
(CL:DEFVAR KWD-RDBMS-CONNECTION-STRING NULL)
(CL:DEFVAR SGT-RDBMS-STELLA-STRING NULL)
(CL:DEFVAR KWD-RDBMS-JDBC-CONNECTION-STRING NULL)
(CL:DEFVAR KWD-RDBMS-ODBC-CONNECTION-STRING NULL)
(CL:DEFVAR KWD-RDBMS-DSN NULL)
(CL:DEFVAR KWD-RDBMS-DB NULL)
(CL:DEFVAR KWD-RDBMS-HOST NULL)
(CL:DEFVAR KWD-RDBMS-PORT NULL)
(CL:DEFVAR SGT-RDBMS-STELLA-INTEGER NULL)
(CL:DEFVAR KWD-RDBMS-USER NULL)
(CL:DEFVAR KWD-RDBMS-PASSWORD NULL)
(CL:DEFVAR KWD-RDBMS-MODULE NULL)
(CL:DEFVAR SGT-RDBMS-STELLA-MODULE NULL)
(CL:DEFVAR KWD-RDBMS-CONFIGURATION NULL)
(CL:DEFVAR SGT-RDBMS-STELLA-CONFIGURATION-TABLE NULL)
(CL:DEFVAR KWD-RDBMS-DB-NAME NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-ASSERT-RDBMS-CONNECTION-INFO NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-DEFQUERY NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-QUERY-SPECIALIST NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-CONNECTION-WRAPPER NULL)
(CL:DEFVAR SYM-RDBMS-STELLA-WRAPPER-VALUE NULL)
(CL:DEFVAR SGT-RDBMS-LOGIC-LOGIC-OBJECT NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-PROTOCOL NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-SERVER-TYPE NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-HOST NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-PORT NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-USER NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-PASSWORD NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-DB-NAME NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-ODBC-CONNECTION-STRING NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-CONNECTION-STRING NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-DSN NULL)
(CL:DEFVAR KWD-RDBMS-PROTOCOL NULL)
(CL:DEFVAR KWD-RDBMS-SERVER-TYPE NULL)
(CL:DEFVAR KWD-RDBMS-EXTENSIONAL-ASSERTION NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-DB-CONNECTION NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-RELATION-DATABASE NULL)
(CL:DEFVAR SYM-RDBMS-LOGIC-?X NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-RELATION-TABLE-INFO NULL)
(CL:DEFVAR SYM-RDBMS-STELLA-RELATION NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-DBMS-NAME NULL)
(CL:DEFVAR SYM-RDBMS-STELLA-TABLE-NAME NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-TABLE-ALIAS NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-COLUMN-LIST NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-COLUMN-VECTOR NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-COLUMN-INDEX NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-ADJUNCT NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-RELATION-COLUMN-INFO NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-TABLE-INFO NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-COLUMN-NAME NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-COLUMN-VARIABLE NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-COLUMN-TYPE NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-COLUMN-DB-TYPE NULL)
(CL:DEFVAR SYM-RDBMS-STELLA-MODULE-NAME NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-MODULE-REFERENCE NULL)
(CL:DEFVAR SYM-RDBMS-STELLA-MODULE NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-MODULE-LOCAL? NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-MODULE-REFERENCE-COLUMN NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-COERCION-FUNCTION NULL)
(CL:DEFVAR KWD-RDBMS-UNKNOWN NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-RELATION-TABLE NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-F-GET-RELATION-TABLE-INFO-MEMO-TABLE-000 NULL)
(CL:DEFVAR KWD-RDBMS-STRING-CONSTANT NULL)
(CL:DEFVAR SGT-RDBMS-STELLA-NUMBER NULL)
(CL:DEFVAR SGT-RDBMS-STELLA-BOOLEAN NULL)
(CL:DEFVAR KWD-RDBMS-MYSQL NULL)
(CL:DEFVAR SGT-RDBMS-STELLA-STRING-WRAPPER NULL)
(CL:DEFVAR SYM-RDBMS-STELLA-ITERATOR NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-DATABASE NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-F-ALLOCATE-DBTABLE-SPECIALIST-ITERATOR-MEMO-TABLE-000 NULL)
(CL:DEFVAR KWD-RDBMS-FAILURE NULL)
(CL:DEFVAR KWD-RDBMS-DB-LOOKUP NULL)
(CL:DEFVAR KWD-RDBMS-CONTINUING-SUCCESS NULL)
(CL:DEFVAR KWD-RDBMS-FINAL-SUCCESS NULL)
(CL:DEFVAR KWD-RDBMS-TECHNICAL NULL)
(CL:DEFVAR KWD-RDBMS-LAY NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-?REL NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-?EV NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-?DB NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-?ARGS NULL)
(CL:DEFVAR SYM-RDBMS-STELLA-AND NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-QUERY-PATTERN NULL)
(CL:DEFVAR SYM-RDBMS-STELLA-EXISTS NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-?DB-TYPE NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-SUPPORTS-DB-TYPE NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-INSTANCE-OF NULL)
(CL:DEFVAR KWD-RDBMS-DONT-OPTIMIZE? NULL)
(CL:DEFVAR KWD-RDBMS-HOW-MANY NULL)
(CL:DEFVAR KWD-RDBMS-ALL NULL)
(CL:DEFVAR KWD-RDBMS-INFERENCE-LEVEL NULL)
(CL:DEFVAR KWD-RDBMS-ASSERTION NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-F-GET-QUERY-PATTERN-EVALUATORS-QUERY-000 NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-F-GET-QUERY-PATTERN-EVALUATORS-MEMO-TABLE-000 NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-F-GET-QUERY-PATTERN-EVALUATORS-QUERY-001 NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-F-SQL-JOIN-MEMO-TABLE-000 NULL)
(CL:DEFVAR KWD-RDBMS-VALUE NULL)
(CL:DEFVAR KWD-RDBMS-WHITE-SPACE NULL)
(CL:DEFVAR KWD-RDBMS-SET NULL)
(CL:DEFVAR KWD-RDBMS-NONE NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-F-SQL-QUERY-MEMO-TABLE-000 NULL)
(CL:DEFVAR KWD-RDBMS-TERMINAL-FAILURE NULL)
(CL:DEFVAR SGT-RDBMS-RDBMS-SQL-DATABASE NULL)
(CL:DEFVAR KWD-RDBMS-EXTERNAL-DB-UPDATE NULL)
(CL:DEFVAR SGT-RDBMS-LOGIC-NAMED-DESCRIPTION NULL)
(CL:DEFVAR SGT-RDBMS-STELLA-TRUE NULL)
(CL:DEFVAR SGT-RDBMS-STELLA-FALSE NULL)
(CL:DEFVAR SGT-RDBMS-STELLA-THING NULL)
(CL:DEFVAR KWD-RDBMS-CLIP NULL)
(CL:DEFVAR KWD-RDBMS-ASSERT NULL)
(CL:DEFVAR KWD-RDBMS-RETRACT NULL)
(CL:DEFVAR KWD-RDBMS-ASSERT-TRUE NULL)
(CL:DEFVAR KWD-RDBMS-PRESUME-TRUE NULL)
(CL:DEFVAR KWD-RDBMS-RETRACT-TRUE NULL)
(CL:DEFVAR KWD-RDBMS-RETRACT-FALSE NULL)
(CL:DEFVAR KWD-RDBMS-ASSERT-FALSE NULL)
(CL:DEFVAR KWD-RDBMS-PRESUME-FALSE NULL)
(CL:DEFVAR KWD-RDBMS-CONCEIVE NULL)
(CL:DEFVAR SYM-RDBMS-RDBMS-STARTUP-RDBMS NULL)
(CL:DEFVAR SYM-RDBMS-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM
 (CL:SPECIAL *STARTUP-TIME-PHASE* *CLIPPINGENABLED?* NULL-CHARACTER
  *CHARACTER-TYPE-TABLE* *QUERYITERATOR* *RECORD-JUSTIFICATIONS?*
  TRUE-TRUTH-VALUE *REVERSEPOLARITY?* *MEMOIZATION-ENABLED?*
  MEMOIZED-NULL-VALUE TRUE-WRAPPER FALSE-WRAPPER *CONTEXT* *MODULE* EOL
  NULL-INTEGER NIL STANDARD-ERROR))

;;; (DEFUN (DEFUNTABLE LOGIC-OBJECT) ...)

(CL:DEFUN %DEFUNTABLE (ARGS)
  "Define (or redefine) a database table and map it to a function
The accepted syntax is:
	 
 (defuntable <relconst> <dbconst> <tablename> (<columndecl>+)
    [<keyword-option>*]).

<columndecl>'s specify the names (and optionally types) of the columns
of the database table.  They have the same form as a PowerLoom <vardecl>, but
column names can be specified with or without question marks.  If there
is a question mark it will be stripped to determine the column name, otherwise
a question mark will be added to generate the relation variable.  The optional
type specifies the domain of that argument and controls any necessary coercion.
The name of each column HAS TO MATCH one of the columns of <tablename>, however,
the order is irrelevant and arbitrary projections can be defined by only
specifying some subset of <tablename>'s columns.

See `deffunction' for legal keyword options.
"
  (CL:HANDLER-CASE (CL:RETURN-FROM %DEFUNTABLE (CALL-DEFUNTABLE ARGS))
   (LOGIC-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     (EXCEPTION-MESSAGE E))
    NULL)))

(CL:DEFUN DEFUNTABLE-EVALUATOR-WRAPPER (ARGUMENTS)
  (%DEFUNTABLE ARGUMENTS))

(CL:DEFMACRO DEFUNTABLE (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Define (or redefine) a database table and map it to a function
The accepted syntax is:
	 
 (defuntable <relconst> <dbconst> <tablename> (<columndecl>+)
    [<keyword-option>*]).

<columndecl>'s specify the names (and optionally types) of the columns
of the database table.  They have the same form as a PowerLoom <vardecl>, but
column names can be specified with or without question marks.  If there
is a question mark it will be stripped to determine the column name, otherwise
a question mark will be added to generate the relation variable.  The optional
type specifies the domain of that argument and controls any necessary coercion.
The name of each column HAS TO MATCH one of the columns of <tablename>, however,
the order is irrelevant and arbitrary projections can be defined by only
specifying some subset of <tablename>'s columns.

See `deffunction' for legal keyword options.
"
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/RDBMS/DEFUNTABLE|)) (CL:MACRO-FUNCTION (CL:QUOTE DEFUNTABLE)))

;;; (DEFUN (CALL-DEFUNTABLE NAMED-DESCRIPTION) ...)

(CL:DEFUN CALL-DEFUNTABLE (ARGUMENTS)
  "Callable version of the `deftable' command (which see).
Expects the same arguments as `deftable' but supplied as a list."
  (CL:LET*
   ((RELCONST (%%VALUE ARGUMENTS))
    (DBCONST (%%VALUE (%%REST ARGUMENTS)))
    (TABLENAME (%%VALUE (%%REST (%%REST ARGUMENTS))))
    (COLUMNSPECS (FOURTH ARGUMENTS))
    (DBAXIOMS
     (LIST*
      (LIST* SYM-RDBMS-RDBMS-RELATION-TABLE RELCONST
       (CONS TABLENAME NIL))
      (LIST* SYM-RDBMS-RDBMS-RELATION-DATABASE RELCONST
       (CONS DBCONST NIL))
      (LIST* SYM-RDBMS-PL-KERNEL-KB-RELATION-SPECIALIST RELCONST
       (CONS SYM-RDBMS-RDBMS-DBTABLE-SPECIALIST NIL))
      NIL)))
   (CL:LET* ((RELATIONARGS NULL) (COLUMNAXIOMS NULL))
    (CL:MULTIPLE-VALUE-SETQ (RELATIONARGS COLUMNAXIOMS)
     (PARSE-COLUMN-SPECS RELCONST COLUMNSPECS))
    (FOURTH-SETTER ARGUMENTS RELATIONARGS)
    (CONCATENATE DBAXIOMS COLUMNAXIOMS))
   (CALL-DEFFUNCTION
    (CONS RELCONST
     (CONCATENATE (%%REST (%%REST (%%REST ARGUMENTS)))
      (LIST* KWD-RDBMS-AXIOMS DBAXIOMS NIL))))))

;;; (DEFUN (DEFTABLE LOGIC-OBJECT) ...)

(CL:DEFUN %DEFTABLE (ARGS)
  "Define (or redefine) a database table and map it to a relation.
The accepted syntax is:
	 
 (deftable <relconst> <dbconst> <tablename> (<columndecl>+)
    [<keyword-option>*]).
	
<columndecl>'s specify the names (and optionally types) of the columns
of the database table.  They have the same form as a PowerLoom <vardecl>, but
column names can be specified with or without question marks.  If there
is a question mark it will be stripped to determine the column name, otherwise
a question mark will be added to generate the relation variable.  The optional
type specifies the domain of that argument and controls any necessary coercion.
The name of each column HAS TO MATCH one of the columns of <tablename>, however,
the order is irrelevant and arbitrary projections can be defined by only
specifying some subset of <tablename>'s columns.

See `defrelation' for legal keyword options.
"
  (CL:HANDLER-CASE (CL:RETURN-FROM %DEFTABLE (CALL-DEFTABLE ARGS))
   (LOGIC-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     (EXCEPTION-MESSAGE E))
    NULL)))

(CL:DEFUN DEFTABLE-EVALUATOR-WRAPPER (ARGUMENTS)
  (%DEFTABLE ARGUMENTS))

(CL:DEFMACRO DEFTABLE (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Define (or redefine) a database table and map it to a relation.
The accepted syntax is:
	 
 (deftable <relconst> <dbconst> <tablename> (<columndecl>+)
    [<keyword-option>*]).
	
<columndecl>'s specify the names (and optionally types) of the columns
of the database table.  They have the same form as a PowerLoom <vardecl>, but
column names can be specified with or without question marks.  If there
is a question mark it will be stripped to determine the column name, otherwise
a question mark will be added to generate the relation variable.  The optional
type specifies the domain of that argument and controls any necessary coercion.
The name of each column HAS TO MATCH one of the columns of <tablename>, however,
the order is irrelevant and arbitrary projections can be defined by only
specifying some subset of <tablename>'s columns.

See `defrelation' for legal keyword options.
"
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/RDBMS/DEFTABLE|)) (CL:MACRO-FUNCTION (CL:QUOTE DEFTABLE)))

;;; (DEFUN (CALL-DEFTABLE NAMED-DESCRIPTION) ...)

(CL:DEFUN CALL-DEFTABLE (ARGUMENTS)
  "Callable version of the `deftable' command (which see).
Expects the same arguments as `deftable' but supplied as a list."
  (CL:LET*
   ((RELCONST (%%VALUE ARGUMENTS))
    (DBCONST (%%VALUE (%%REST ARGUMENTS)))
    (TABLENAME (%%VALUE (%%REST (%%REST ARGUMENTS))))
    (COLUMNSPECS (FOURTH ARGUMENTS))
    (DBAXIOMS
     (LIST*
      (LIST* SYM-RDBMS-RDBMS-RELATION-TABLE RELCONST
       (CONS TABLENAME NIL))
      (LIST* SYM-RDBMS-RDBMS-RELATION-DATABASE RELCONST
       (CONS DBCONST NIL))
      (LIST* SYM-RDBMS-PL-KERNEL-KB-RELATION-SPECIALIST RELCONST
       (CONS SYM-RDBMS-RDBMS-DBTABLE-SPECIALIST NIL))
      NIL)))
   (CL:LET* ((RELATIONARGS NULL) (COLUMNAXIOMS NULL))
    (CL:MULTIPLE-VALUE-SETQ (RELATIONARGS COLUMNAXIOMS)
     (PARSE-COLUMN-SPECS RELCONST COLUMNSPECS))
    (FOURTH-SETTER ARGUMENTS RELATIONARGS)
    (CONCATENATE DBAXIOMS COLUMNAXIOMS))
   (CALL-DEFRELATION
    (CONS RELCONST
     (CONCATENATE (%%REST (%%REST (%%REST ARGUMENTS)))
      (LIST* KWD-RDBMS-AXIOMS DBAXIOMS NIL))))))

;;; (DEFUN (PARSE-ONE-COLUMN-SPEC PROPERTY-LIST) ...)

(CL:DEFUN PARSE-ONE-COLUMN-SPEC (COLUMNSPEC)
  (CL:LET*
   ((PARSEDCOLUMN (NEW-PROPERTY-LIST)) (VAR NULL) (NAME NULL)
    (OPTIONS NIL) (OPTIONSPLIST NULL) (TYPE NULL))
   (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE COLUMNSPEC)))
    (CL:COND
     ((CL:EQ TEST-VALUE-000 SGT-RDBMS-STELLA-CONS)
      (CL:PROGN (CL:SETQ NAME (%%VALUE COLUMNSPEC))
       (CL:IF
        (CL:AND (CL:NOT (CL:EQ (%%VALUE (%%REST COLUMNSPEC)) NULL))
         (CL:NOT (KEYWORD? (%%VALUE (%%REST COLUMNSPEC)))))
        (CL:PROGN (CL:SETQ TYPE (%%VALUE (%%REST COLUMNSPEC)))
         (CL:SETQ OPTIONS (%%REST (%%REST COLUMNSPEC))))
        (CL:SETQ OPTIONS (%%REST COLUMNSPEC)))))
     ((SUBTYPE-OF-SYMBOL? TEST-VALUE-000)
      (CL:PROGN (CL:SETQ NAME COLUMNSPEC)))
     (CL:T
      (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
       (CL:LET* ((*PRINTREADABLY?* CL:T))
        (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
        (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
         "PARSING ERROR: Illegal table column specification: `"
         COLUMNSPEC "'." EOL)
        (HELP-SIGNAL-PROPOSITION-ERROR STREAM-000 KWD-RDBMS-ERROR))
       (CL:ERROR
        (NEW-PARSING-ERROR (THE-STRING-READER STREAM-000)))))))
   (CL:WHEN (CL:NOT (CL:AND (CL:NOT (CL:EQ NAME NULL)) (SYMBOL? NAME)))
    (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
     (CL:LET* ((*PRINTREADABLY?* CL:T))
      (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001)
       "PARSING ERROR: Illegal table column name: `" NAME "'." EOL)
      (HELP-SIGNAL-PROPOSITION-ERROR STREAM-001 KWD-RDBMS-ERROR))
     (CL:ERROR (NEW-PARSING-ERROR (THE-STRING-READER STREAM-001)))))
   (CL:WHEN (CL:NOT (CL:OR (CL:EQ TYPE NULL) (SYMBOL? TYPE)))
    (CL:LET* ((STREAM-002 (NEW-OUTPUT-STRING-STREAM)))
     (CL:LET* ((*PRINTREADABLY?* CL:T))
      (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-002)
       "PARSING ERROR: Illegal table column type: `" TYPE "'." EOL)
      (HELP-SIGNAL-PROPOSITION-ERROR STREAM-002 KWD-RDBMS-ERROR))
     (CL:ERROR (NEW-PARSING-ERROR (THE-STRING-READER STREAM-002)))))
   (CL:LET* ((ARGLIST-000 NIL))
    (CL:LET* ((ARG-000 NULL) (ITER-000 OPTIONS) (COLLECT-000 NULL))
     (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
      (CL:SETQ ARG-000 (%%VALUE ITER-000))
      (CL:IF (CL:EQ COLLECT-000 NULL)
       (CL:PROGN (CL:SETQ COLLECT-000 (CONS ARG-000 NIL))
        (CL:IF (CL:EQ ARGLIST-000 NIL)
         (CL:SETQ ARGLIST-000 COLLECT-000)
         (ADD-CONS-TO-END-OF-CONS-LIST ARGLIST-000 COLLECT-000)))
       (CL:PROGN (CL:SETF (%%REST COLLECT-000) (CONS ARG-000 NIL))
        (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
      (CL:SETQ ITER-000 (%%REST ITER-000))))
    (CL:SETQ OPTIONSPLIST
     (VET-OPTIONS ARGLIST-000
      (GET-QUOTED-TREE "((:MODULE-NAME :MODULE-REFERENCE) \"/RDBMS\")"
       "/RDBMS"))))
   (CL:SETQ VAR NAME)
   (CL:COND
    ((QUESTION-MARK-SYMBOL? NAME)
     (CL:SETQ NAME
      (WRAP-STRING (SUBSEQUENCE (%SYMBOL-NAME VAR) 1 NULL-INTEGER))))
    (CL:T (CL:SETQ NAME (WRAP-STRING (%SYMBOL-NAME VAR)))
     (CL:SETQ VAR
      (INTERN-DERIVED-SYMBOL VAR
       (CONCATENATE "?" (%WRAPPER-VALUE NAME))))))
   (INSERT-AT PARSEDCOLUMN KWD-RDBMS-NAME NAME)
   (INSERT-AT PARSEDCOLUMN KWD-RDBMS-VARIABLE VAR)
   (CL:WHEN (CL:NOT (CL:EQ TYPE NULL))
    (INSERT-AT PARSEDCOLUMN KWD-RDBMS-TYPE TYPE))
   (CL:LET*
    ((KEY NULL) (VAL NULL) (ITER-001 (%THE-PLIST OPTIONSPLIST)))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
     (CL:SETQ KEY (%%VALUE ITER-001))
     (CL:SETQ VAL (%%VALUE (%%REST ITER-001)))
     (INSERT-AT PARSEDCOLUMN KEY VAL)
     (CL:SETQ ITER-001 (%%REST (%%REST ITER-001)))))
   PARSEDCOLUMN))

;;; (DEFUN (PARSE-COLUMN-SPECS CONS CONS) ...)

(CL:DEFUN PARSE-COLUMN-SPECS (RELCONST COLUMNSPECS)
  (CL:WHEN (CL:NOT (CONS? COLUMNSPECS))
   (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
    (CL:LET* ((*PRINTREADABLY?* CL:T))
     (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
      "PARSING ERROR: Illegal variable/column specifications: `"
      COLUMNSPECS "'." EOL)
     (HELP-SIGNAL-PROPOSITION-ERROR STREAM-000 KWD-RDBMS-ERROR))
    (CL:ERROR (NEW-PARSING-ERROR (THE-STRING-READER STREAM-000)))))
  (CL:LET* ((RELATIONARGS NIL) (AXIOMS NIL))
   (CL:LET*
    ((COLUMNSPEC NULL) (ITER-000 COLUMNSPECS) (I NULL-INTEGER)
     (ITER-001 1))
    (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-001))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ COLUMNSPEC (%%VALUE ITER-000)) (CL:SETQ I ITER-001)
     (CL:LET*
      ((COLUMNINFO (PARSE-ONE-COLUMN-SPEC COLUMNSPEC))
       (TYPE (LOOKUP COLUMNINFO KWD-RDBMS-TYPE))
       (NAME (LOOKUP COLUMNINFO KWD-RDBMS-NAME))
       (VAR (LOOKUP COLUMNINFO KWD-RDBMS-VARIABLE))
       (MODULENAME (LOOKUP COLUMNINFO KWD-RDBMS-MODULE-NAME))
       (MODULEREFERENCE
        (LOOKUP COLUMNINFO KWD-RDBMS-MODULE-REFERENCE)))
      (CL:IF (CL:NOT (CL:EQ TYPE NULL))
       (CL:SETQ RELATIONARGS (CONS (CONS-LIST VAR TYPE) RELATIONARGS))
       (CL:SETQ RELATIONARGS (CONS VAR RELATIONARGS)))
      (CL:WHEN (CL:NOT (CL:EQ NAME NULL))
       (CL:SETQ AXIOMS
        (CONS
         (LIST* SYM-RDBMS-RDBMS-RELATION-COLUMN-NAME RELCONST
          (CONS (WRAP-INTEGER I) (CONS NAME NIL)))
         AXIOMS)))
      (CL:WHEN (CL:NOT (CL:EQ MODULENAME NULL))
       (CL:SETQ AXIOMS
        (CONS
         (LIST* SYM-RDBMS-RDBMS-RELATION-COLUMN-MODULE-NAME RELCONST
          (CONS (WRAP-INTEGER I) (CONS MODULENAME NIL)))
         AXIOMS)))
      (CL:WHEN (CL:NOT (CL:EQ MODULEREFERENCE NULL))
       (CL:SETQ AXIOMS
        (CONS
         (LIST* SYM-RDBMS-RDBMS-RELATION-COLUMN-MODULE-REFERENCE
          RELCONST (CONS (WRAP-INTEGER I) (CONS MODULEREFERENCE NIL)))
         AXIOMS))))
     (CL:SETQ ITER-000 (%%REST ITER-000))
     (CL:SETQ ITER-001 (CL:1+ ITER-001))))
   (CL:VALUES (REVERSE RELATIONARGS) (REVERSE AXIOMS))))

;;; (DEFUN (DEFDB LOGIC-OBJECT) ...)

(CL:DEFUN %DEFDB (ARGS)
  "Define (or redefine) a database instance.  The accepted syntax is:
	 
 (defdb <dbconst>
    [:protocol <protocol string>]
    [:server-type <server type string>]
    [:dsn <ODBC data-source name string>]
    [:odbc-connection-string <ODBC connection string>]
    [:jdbc-connection-string <JDBC connection string>]
    [:connection-string <connection string>] ;; deprecated
    [:host <server host string>]
    [:port <server host port>]
    [:user <user name string>]
    [:password <password string>]
    [:db-name <database name string>]
    [<keyword-option>*])
	
Connection information can be asserted explicitly later or be done
programmatically, as long as it is done before the first time a
connection attempt is made (e.g., during a query).  This information
is passed to `SDBC/connect' (which see for more documentation on
ways to specify a connection).  For example, for ODBC a :DSN, an
:ODBC-CONNECTION-STRING or an appropriate combination of :HOST,
:PORT, :USER, :PASSWORD AND :DB-NAME can be used.  For JDBC a
:JDBC-CONNECTION-STRING or combination of :HOST, :PORT, etc. can
be used.  See `defobject' for additional legal keyword options.
"
  (CL:HANDLER-CASE (CL:RETURN-FROM %DEFDB (CALL-DEFDB ARGS))
   (LOGIC-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     (EXCEPTION-MESSAGE E))
    NULL)))

(CL:DEFUN DEFDB-EVALUATOR-WRAPPER (ARGUMENTS)
  (%DEFDB ARGUMENTS))

(CL:DEFMACRO DEFDB (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Define (or redefine) a database instance.  The accepted syntax is:
	 
 (defdb <dbconst>
    [:protocol <protocol string>]
    [:server-type <server type string>]
    [:dsn <ODBC data-source name string>]
    [:odbc-connection-string <ODBC connection string>]
    [:jdbc-connection-string <JDBC connection string>]
    [:connection-string <connection string>] ;; deprecated
    [:host <server host string>]
    [:port <server host port>]
    [:user <user name string>]
    [:password <password string>]
    [:db-name <database name string>]
    [<keyword-option>*])
	
Connection information can be asserted explicitly later or be done
programmatically, as long as it is done before the first time a
connection attempt is made (e.g., during a query).  This information
is passed to `SDBC/connect' (which see for more documentation on
ways to specify a connection).  For example, for ODBC a :DSN, an
:ODBC-CONNECTION-STRING or an appropriate combination of :HOST,
:PORT, :USER, :PASSWORD AND :DB-NAME can be used.  For JDBC a
:JDBC-CONNECTION-STRING or combination of :HOST, :PORT, etc. can
be used.  See `defobject' for additional legal keyword options.
"
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/RDBMS/DEFDB|)) (CL:MACRO-FUNCTION (CL:QUOTE DEFDB)))

;;; (DEFUN (CALL-DEFDB LOGIC-OBJECT) ...)

(CL:DEFUN CALL-DEFDB (ARGUMENTS)
  "Callable version of of the `defdb' command (which see).
Expects the same arguments as `defdb' but supplied as a list."
  (CL:LET*
   ((DEFINITION
     (CONS SYM-RDBMS-RDBMS-DEFDB (CONCATENATE ARGUMENTS NIL)))
    (DBNAME NULL) (DBAXIOMS NIL) (RELATIONOPTIONS NIL))
   (CL:LET* ((*TERMSOURCEBEINGPARSED* (STRINGIFY DEFINITION)))
    (CL:DECLARE (CL:SPECIAL *TERMSOURCEBEINGPARSED*))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING *TERMSOURCEBEINGPARSED*))
    (CL:SETQ ARGUMENTS (NORMALIZE-DEFOBJECT-ARGUMENTS ARGUMENTS))
    (CL:SETQ DBNAME (%%VALUE ARGUMENTS))
    (CL:MULTIPLE-VALUE-SETQ (DBAXIOMS RELATIONOPTIONS)
     (EXTRACT-RDBMS-OPTIONS DBNAME (%%REST ARGUMENTS)))
    (CL:SETQ DBAXIOMS
     (CONS (LIST* SYM-RDBMS-RDBMS-DATABASE DBNAME NIL) DBAXIOMS))
    (CL:SETF (%%REST ARGUMENTS)
     (CONCATENATE RELATIONOPTIONS
      (LIST* KWD-RDBMS-AXIOMS DBAXIOMS NIL)))
    (CALL-DEFOBJECT ARGUMENTS))))

;;; (DEFUN (EXTRACT-RDBMS-OPTIONS CONS CONS) ...)

(CL:DEFUN EXTRACT-RDBMS-OPTIONS (SELFNAME OPTIONS)
  (CL:LET* ((SELF-000 (NEW-PROPERTY-LIST)))
   (CL:SETF (%THE-PLIST SELF-000) OPTIONS)
   (CL:LET*
    ((SOURCEOPTIONS SELF-000)
     (RDBMSMODULE (GET-STELLA-MODULE "RDBMS" CL:T)) (RELATIONREF NULL)
     (RELATION NULL) (AXIOMS NIL) (OTHEROPTIONS NIL))
    (CL:LET*
     ((KEY NULL) (VALUE NULL) (ITER-000 (%THE-PLIST SOURCEOPTIONS)))
     (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
      (CL:SETQ KEY (%%VALUE ITER-000))
      (CL:SETQ VALUE (%%VALUE (%%REST ITER-000)))
      (CL:TAGBODY
       (CL:WHEN (KEYWORD? KEY)
        (CL:SETQ RELATIONREF
         (LOOKUP-SURROGATE-IN-MODULE (%SYMBOL-NAME KEY) RDBMSMODULE
          CL:T))
        (CL:WHEN (CL:NOT (CL:EQ RELATIONREF NULL))
         (CL:SETQ RELATION (GET-DESCRIPTION RELATIONREF))
         (CL:WHEN (CL:NOT (CL:EQ RELATION NULL))
          (CL:COND
           ((CONS? VALUE)
            (CL:SETQ AXIOMS
             (CONS
              (CONS (DESCRIPTION-NAME RELATION) (CONS SELFNAME VALUE))
              AXIOMS)))
           (CL:T
            (CL:LET* ((*MODULE* RDBMSMODULE) (*CONTEXT* *MODULE*))
             (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
             (CL:SETQ AXIOMS
              (CONS (HELP-DEFINE-KEYWORD-AXIOMS SELFNAME KEY VALUE)
               AXIOMS)))))
          (CL:GO :CONTINUE))))
       (CL:SETQ OTHEROPTIONS (CONS KEY OTHEROPTIONS))
       (CL:SETQ OTHEROPTIONS (CONS VALUE OTHEROPTIONS)) :CONTINUE)
      (CL:SETQ ITER-000 (%%REST (%%REST ITER-000)))))
    (CL:VALUES (REVERSE AXIOMS) (REVERSE OTHEROPTIONS)))))

;;; (DEFUN ASSERT-RDBMS-CONNECTION-INFO ...)

(CL:DEFUN %ASSERT-RDBMS-CONNECTION-INFO (DB-INSTANCE-NAME OPTIONS)
  "Assert DB connectivity information about the DB instance `db-instance-name' (for
example, \"edb\") according to `options'.  Looks up `db-instance-name' in the module
specified by the :module option (defaults to current module) and retracts any
preexisting connection information.  New assertions are also made in that module.
Default values are taken from the configuration table specified by :configuration.

Understands the following options, with default values specified by the configuration
key in parentheses:
   :connection-string (\"DBConnection\"),
   :jdbc-connection-string (\"JDBCString\"),
   :odbc-connection-string (\"ODBCString\"),
   :dsn (\"DSN\"),
   :db (\"DBName\"),
   :host (\"DBHost\"),
   :port (\"DBPort\"),
   :user (\"DBUser\"),
   :password (\"DBPassword\"),
   :module,
   :configuration."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING DB-INSTANCE-NAME))
  #+MCL
  (CL:CHECK-TYPE DB-INSTANCE-NAME CL:SIMPLE-STRING)
  (CL:LET*
   ((THEOPTIONS
     (PARSE-LOGIC-COMMAND-OPTIONS OPTIONS
      (LIST* KWD-RDBMS-CONNECTION-STRING SGT-RDBMS-STELLA-STRING
       KWD-RDBMS-JDBC-CONNECTION-STRING SGT-RDBMS-STELLA-STRING
       KWD-RDBMS-ODBC-CONNECTION-STRING SGT-RDBMS-STELLA-STRING
       KWD-RDBMS-DSN SGT-RDBMS-STELLA-STRING KWD-RDBMS-DB
       SGT-RDBMS-STELLA-STRING KWD-RDBMS-HOST SGT-RDBMS-STELLA-STRING
       KWD-RDBMS-PORT SGT-RDBMS-STELLA-INTEGER KWD-RDBMS-USER
       SGT-RDBMS-STELLA-STRING KWD-RDBMS-PASSWORD
       SGT-RDBMS-STELLA-STRING KWD-RDBMS-MODULE SGT-RDBMS-STELLA-MODULE
       KWD-RDBMS-CONFIGURATION SGT-RDBMS-STELLA-CONFIGURATION-TABLE
       NIL)
      CL:T CL:NIL))
    (CONFIG (LOOKUP THEOPTIONS KWD-RDBMS-CONFIGURATION))
    (CON-STRING
     (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-RDBMS-CONNECTION-STRING
      (LOOKUP-CONFIGURATION-PROPERTY "DBConnection" NULL CONFIG)))
    (JDBC-CON-STRING
     (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-RDBMS-CONNECTION-STRING
      (LOOKUP-CONFIGURATION-PROPERTY "JDBCString" NULL CONFIG)))
    (ODBC-CON-STRING
     (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-RDBMS-CONNECTION-STRING
      (LOOKUP-CONFIGURATION-PROPERTY "ODBCString" NULL CONFIG)))
    (DSN
     (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-RDBMS-DSN
      (LOOKUP-CONFIGURATION-PROPERTY "DSN" NULL CONFIG)))
    (DB-NAME
     (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-RDBMS-DB-NAME
      (LOOKUP-CONFIGURATION-PROPERTY "DBName" NULL CONFIG)))
    (HOST
     (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-RDBMS-HOST
      (LOOKUP-CONFIGURATION-PROPERTY "DBHost" NULL CONFIG)))
    (PORT
     (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-RDBMS-PORT
      (LOOKUP-CONFIGURATION-PROPERTY "DBPort" NULL CONFIG)))
    (USER
     (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-RDBMS-USER
      (LOOKUP-CONFIGURATION-PROPERTY "DBUser" NULL CONFIG)))
    (PASSWORD
     (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-RDBMS-PASSWORD
      (LOOKUP-CONFIGURATION-PROPERTY "DBPassword" NULL CONFIG)))
    (MODULE (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-RDBMS-MODULE *MODULE*))
    (MODULE-NAME (%MODULE-FULL-NAME MODULE))
    (DB-OBJECT (PLI::S-GET-OBJECT DB-INSTANCE-NAME MODULE-NAME NULL))
    (ASSERTION-TEMPLATE
     (INSTANTIATE-STRING-TEMPLATE
      (CONCATENATE "(AND"
       (CL:IF
        (CL:AND (CL:NOT (CL:EQ JDBC-CON-STRING NULL))
         (CL:NOT (STRING-EQL? (%WRAPPER-VALUE JDBC-CON-STRING) "")))
        "(RDBMS/JDBC-CONNECTION-STRING #$DB \"#$JDBCCON\")" "")
       (CL:IF
        (CL:AND (CL:NOT (CL:EQ ODBC-CON-STRING NULL))
         (CL:NOT (STRING-EQL? (%WRAPPER-VALUE ODBC-CON-STRING) "")))
        "(RDBMS/ODBC-CONNECTION-STRING #$DB \"#$ODBCCON\")" "")
       (CL:IF
        (CL:AND (CL:NOT (CL:EQ DSN NULL))
         (CL:NOT (STRING-EQL? (%WRAPPER-VALUE DSN) "")))
        "(RDBMS/DSN #$DB \"#$DSN\")" "")
       (CL:IF
        (CL:AND (CL:NOT (CL:EQ DB-NAME NULL))
         (CL:NOT (STRING-EQL? (%WRAPPER-VALUE DB-NAME) "")))
        "(RDBMS/DB-NAME #$DB \"#$NAME\")" "")
       (CL:IF
        (CL:AND (CL:NOT (CL:EQ HOST NULL))
         (CL:NOT (STRING-EQL? (%WRAPPER-VALUE HOST) "")))
        "(RDBMS/HOST #$DB \"#$HOST\")" "")
       (CL:IF (CL:NOT (CL:EQ PORT NULL)) "(RDBMS/PORT #$DB #$PORT)" "")
       (CL:IF
        (CL:AND (CL:NOT (CL:EQ USER NULL))
         (CL:NOT (STRING-EQL? (%WRAPPER-VALUE USER) "")))
        "(RDBMS/USER #$DB \"#$USER\")" "")
       (CL:IF
        (CL:AND (CL:NOT (CL:EQ PASSWORD NULL))
         (CL:NOT (STRING-EQL? (%WRAPPER-VALUE PASSWORD) "")))
        "(RDBMS/PASSWORD #$DB \"#$PWD\")" "")
       ")")
      "#$DB" DB-INSTANCE-NAME "#$DSN" (%WRAPPER-VALUE DSN) "#$NAME"
      (CL:IF (CL:NOT (CL:EQ DB-NAME NULL)) (%WRAPPER-VALUE DB-NAME) "")
      "#$HOST"
      (CL:IF (CL:NOT (CL:EQ HOST NULL)) (%WRAPPER-VALUE HOST) "")
      "#$PORT"
      (CL:IF (CL:NOT (CL:EQ PORT NULL))
       (INTEGER-TO-STRING (CL:TRUNCATE (%WRAPPER-VALUE PORT))) "")
      "#$USER"
      (CL:IF (CL:NOT (CL:EQ USER NULL)) (%WRAPPER-VALUE USER) "")
      "#$PWD"
      (CL:IF (CL:NOT (CL:EQ PASSWORD NULL)) (%WRAPPER-VALUE PASSWORD)
       "")
      "#$JDBCCON"
      (CL:IF (CL:NOT (CL:EQ JDBC-CON-STRING NULL))
       (%WRAPPER-VALUE JDBC-CON-STRING) "")
      "#$ODBCCON"
      (CL:IF (CL:NOT (CL:EQ ODBC-CON-STRING NULL))
       (%WRAPPER-VALUE ODBC-CON-STRING) ""))))
   (CL:DECLARE
    (CL:TYPE CL:SIMPLE-STRING MODULE-NAME ASSERTION-TEMPLATE))
   (CL:WHEN (CL:NOT (CL:EQ DB-OBJECT NULL))
    (PLI::S-EVALUATE
     (INSTANTIATE-STRING-TEMPLATE
      "(PROGN (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/DSN #$DB ?dsn)))
                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/DB-NAME #$DB ?db)))
                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/HOST #$DB ?host)))
                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/PORT #$DB ?port)))
                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/USER #$DB ?user)))
                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/PASSWORD #$DB ?pwd)))
                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/CONNECTION-STRING #$DB ?con)))
                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/ODBC-CONNECTION-STRING #$DB ?con)))
                  (RETRACT-FROM-QUERY (RETRIEVE ALL (RDBMS/JDBC-CONNECTION-STRING #$DB ?con))))"
      "#$DB" DB-INSTANCE-NAME)
     MODULE-NAME NULL))
   (CL:WHEN (CL:NOT (CL:EQ CON-STRING NULL))
    (PLI::S-ASSERT-PROPOSITION
     (INSTANTIATE-STRING-TEMPLATE
      "(RDBMS/#$PROTOCOL-CONNECTION-STRING #$DB \"#$CON\")"
      "#$PROTOCOL"
      (CL:IF (ODBC-CONNECTION-STRING? (%WRAPPER-VALUE CON-STRING))
       "ODBC" "JDBC")
      "#$DB" DB-INSTANCE-NAME "#$CON" (%WRAPPER-VALUE CON-STRING))
     MODULE-NAME NULL))
   (CL:WHEN (CL:NOT (STRING-EQL? ASSERTION-TEMPLATE "(AND)"))
    (PLI::S-ASSERT-PROPOSITION ASSERTION-TEMPLATE MODULE-NAME NULL))))

(CL:DEFUN ASSERT-RDBMS-CONNECTION-INFO-EVALUATOR-WRAPPER (ARGUMENTS)
  (%ASSERT-RDBMS-CONNECTION-INFO (%WRAPPER-VALUE (%%VALUE ARGUMENTS))
   (%%REST ARGUMENTS)))

(CL:DEFMACRO ASSERT-RDBMS-CONNECTION-INFO (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Assert DB connectivity information about the DB instance `db-instance-name' (for
example, \"edb\") according to `options'.  Looks up `db-instance-name' in the module
specified by the :module option (defaults to current module) and retracts any
preexisting connection information.  New assertions are also made in that module.
Default values are taken from the configuration table specified by :configuration.

Understands the following options, with default values specified by the configuration
key in parentheses:
   :connection-string (\"DBConnection\"),
   :jdbc-connection-string (\"JDBCString\"),
   :odbc-connection-string (\"ODBCString\"),
   :dsn (\"DSN\"),
   :db (\"DBName\"),
   :host (\"DBHost\"),
   :port (\"DBPort\"),
   :user (\"DBUser\"),
   :password (\"DBPassword\"),
   :module,
   :configuration."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/RDBMS/ASSERT-RDBMS-CONNECTION-INFO|)) (CL:MACRO-FUNCTION (CL:QUOTE ASSERT-RDBMS-CONNECTION-INFO)))

;;; (DEFUN (DEFQUERY LOGIC-OBJECT) ...)

(CL:DEFUN %DEFQUERY (ARGS)
  "Define (or redefine) an (external) query and map it to a relation.
The accepted syntax is:
	 
 (defquery <relconst> (<vardecl>+)
    {:query-pattern (<query-evaluator> <dbconst> <arguments-string>)}*
    [<keyword-option>*]).
	
<query-evaluator> has to be a `Computed-Procedure' that takes the following
three arguments: the <relconst> query proposition, the database object <dbconst>
and the arguments string.  It needs to return an iterator that generates CONS
tuples whose elements will be bound in sequence to <relconst>'s arguments.

See `defrelation' for other legal keyword options.
"
  (CL:HANDLER-CASE (CL:RETURN-FROM %DEFQUERY (CALL-DEFQUERY ARGS))
   (LOGIC-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     (EXCEPTION-MESSAGE E))
    NULL)))

(CL:DEFUN DEFQUERY-EVALUATOR-WRAPPER (ARGUMENTS)
  (%DEFQUERY ARGUMENTS))

(CL:DEFMACRO DEFQUERY (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Define (or redefine) an (external) query and map it to a relation.
The accepted syntax is:
	 
 (defquery <relconst> (<vardecl>+)
    {:query-pattern (<query-evaluator> <dbconst> <arguments-string>)}*
    [<keyword-option>*]).
	
<query-evaluator> has to be a `Computed-Procedure' that takes the following
three arguments: the <relconst> query proposition, the database object <dbconst>
and the arguments string.  It needs to return an iterator that generates CONS
tuples whose elements will be bound in sequence to <relconst>'s arguments.

See `defrelation' for other legal keyword options.
"
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/RDBMS/DEFQUERY|)) (CL:MACRO-FUNCTION (CL:QUOTE DEFQUERY)))

;;; (DEFUN (CALL-DEFQUERY NAMED-DESCRIPTION) ...)

(CL:DEFUN CALL-DEFQUERY (ARGUMENTS)
  "Callable version of the `defquery' command (which see).
Expects the same arguments as `deftable' but supplied as a list."
  (CL:LET*
   ((DEFINITION
     (CONS SYM-RDBMS-RDBMS-DEFQUERY (CONCATENATE ARGUMENTS NIL)))
    (RELATIONNAME NULL) (QUERYAXIOMS NIL) (RELATIONOPTIONS NIL))
   (CL:LET* ((*TERMSOURCEBEINGPARSED* (STRINGIFY DEFINITION)))
    (CL:DECLARE (CL:SPECIAL *TERMSOURCEBEINGPARSED*))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING *TERMSOURCEBEINGPARSED*))
    (CL:SETQ ARGUMENTS (NORMALIZE-DEFRELATION-ARGUMENTS ARGUMENTS))
    (CL:SETQ RELATIONNAME (%%VALUE ARGUMENTS))
    (CL:MULTIPLE-VALUE-SETQ (QUERYAXIOMS RELATIONOPTIONS)
     (EXTRACT-RDBMS-OPTIONS RELATIONNAME (%%REST (%%REST ARGUMENTS))))
    (CL:SETQ QUERYAXIOMS
     (CONS
      (LIST* SYM-RDBMS-PL-KERNEL-KB-RELATION-SPECIALIST RELATIONNAME
       (CONS SYM-RDBMS-RDBMS-QUERY-SPECIALIST NIL))
      QUERYAXIOMS))
    (CL:LET* ((RELATIONARGS NULL) (COLUMNAXIOMS NULL))
     (CL:MULTIPLE-VALUE-SETQ (RELATIONARGS COLUMNAXIOMS)
      (PARSE-COLUMN-SPECS RELATIONNAME (%%VALUE (%%REST ARGUMENTS))))
     (SECOND-SETTER ARGUMENTS RELATIONARGS)
     (CONCATENATE QUERYAXIOMS COLUMNAXIOMS))
    (CL:SETF (%%REST (%%REST ARGUMENTS))
     (CONCATENATE RELATIONOPTIONS
      (LIST* KWD-RDBMS-AXIOMS QUERYAXIOMS NIL)))
    (CALL-DEFRELATION ARGUMENTS))))

;;; (DEFCLASS CONNECTION-WRAPPER ...)

(CL:DEFCLASS CONNECTION-WRAPPER (LOGIC-THING)
  ((WRAPPER-VALUE :ALLOCATION :INSTANCE :ACCESSOR %WRAPPER-VALUE)))

(CL:DEFUN NEW-CONNECTION-WRAPPER ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE CONNECTION-WRAPPER)))
   (CL:SETF (%DYNAMIC-SLOTS SELF) (NEW-KEY-VALUE-LIST))
   (CL:SETF (%SURROGATE-VALUE-INVERSE SELF) NULL)
   (CL:SETF (%WRAPPER-VALUE SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF CONNECTION-WRAPPER))
  SGT-RDBMS-RDBMS-CONNECTION-WRAPPER)

(CL:DEFUN ACCESS-CONNECTION-WRAPPER-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME SYM-RDBMS-STELLA-WRAPPER-VALUE)
    (CL:IF SETVALUE? (CL:SETF (%WRAPPER-VALUE SELF) VALUE)
     (CL:SETQ VALUE (%WRAPPER-VALUE SELF))))
   (CL:T
    (CL:IF SETVALUE?
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS SELF) SLOTNAME VALUE NULL)
     (CL:SETQ VALUE (LOOKUP (%DYNAMIC-SLOTS SELF) SLOTNAME)))))
  VALUE)

;;; (DEFUN (NORMALIZE-CONNECTION-ARGUMENT STRING-WRAPPER) ...)

(CL:DEFUN NORMALIZE-CONNECTION-ARGUMENT (ARG)
  (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE ARG)))
   (CL:COND
    ((SUBTYPE-OF-STRING? TEST-VALUE-000)
     (CL:PROGN (CL:IF (NULL-WRAPPER? ARG) NULL ARG)))
    ((SUBTYPE-OF-INTEGER? TEST-VALUE-000)
     (CL:PROGN
      (CL:IF (NULL-WRAPPER? ARG) NULL
       (WRAP-STRING
        (INTEGER-TO-STRING (CL:TRUNCATE (%WRAPPER-VALUE ARG)))))))
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-RDBMS-LOGIC-LOGIC-OBJECT)
     (CL:PROGN (WRAP-STRING (PLI::GET-NAME ARG))))
    (CL:T NULL))))

;;; (DEFUN (CONNECT-TO-DATABASE /SDBC/CONNECTION) ...)

(CL:DEFUN CONNECT-TO-DATABASE (DATABASE)
  (CL:LET*
   ((PROTOCOL (ACCESS-BINARY-VALUE DATABASE SGT-RDBMS-RDBMS-PROTOCOL))
    (SERVERTYPE
     (ACCESS-BINARY-VALUE DATABASE SGT-RDBMS-RDBMS-SERVER-TYPE))
    (HOST (ACCESS-BINARY-VALUE DATABASE SGT-RDBMS-RDBMS-HOST))
    (PORT (ACCESS-BINARY-VALUE DATABASE SGT-RDBMS-RDBMS-PORT))
    (USER (ACCESS-BINARY-VALUE DATABASE SGT-RDBMS-RDBMS-USER))
    (PASSWORD (ACCESS-BINARY-VALUE DATABASE SGT-RDBMS-RDBMS-PASSWORD))
    (DBNAME (ACCESS-BINARY-VALUE DATABASE SGT-RDBMS-RDBMS-DB-NAME)))
   (CL:LET*
    ((TEMP-000
      (ACCESS-BINARY-VALUE DATABASE
       SGT-RDBMS-RDBMS-ODBC-CONNECTION-STRING)))
    (CL:LET*
     ((CONNECTIONSTRING
       (CL:IF (CL:NOT (CL:EQ TEMP-000 NULL)) TEMP-000
        (ACCESS-BINARY-VALUE DATABASE
         SGT-RDBMS-RDBMS-CONNECTION-STRING)))
      (DSN (ACCESS-BINARY-VALUE DATABASE SGT-RDBMS-RDBMS-DSN))
      (CONNECTION NULL) (CONNECTIONWRAPPER (NEW-CONNECTION-WRAPPER)))
     (CL:SETQ CONNECTION
      (%CONNECT
       (CONS-LIST KWD-RDBMS-PROTOCOL
        (NORMALIZE-CONNECTION-ARGUMENT PROTOCOL) KWD-RDBMS-SERVER-TYPE
        (NORMALIZE-CONNECTION-ARGUMENT SERVERTYPE) KWD-RDBMS-DSN
        (NORMALIZE-CONNECTION-ARGUMENT DSN) KWD-RDBMS-DB-NAME
        (NORMALIZE-CONNECTION-ARGUMENT DBNAME) KWD-RDBMS-USER
        (NORMALIZE-CONNECTION-ARGUMENT USER) KWD-RDBMS-PASSWORD
        (NORMALIZE-CONNECTION-ARGUMENT PASSWORD) KWD-RDBMS-HOST
        (NORMALIZE-CONNECTION-ARGUMENT HOST) KWD-RDBMS-PORT
        (NORMALIZE-CONNECTION-ARGUMENT PORT)
        KWD-RDBMS-CONNECTION-STRING
        (NORMALIZE-CONNECTION-ARGUMENT CONNECTIONSTRING))))
     (CL:SETF (%WRAPPER-VALUE CONNECTIONWRAPPER) CONNECTION)
     (CL:LET*
      ((*MODULE* (%BASE-MODULE *CONTEXT*)) (*CONTEXT* *MODULE*))
      (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
      (CL:LET*
       ((*INVISIBLEASSERTION?* CL:T)
        (*EVALUATIONMODE* KWD-RDBMS-EXTENSIONAL-ASSERTION))
       (CL:DECLARE (CL:SPECIAL *INVISIBLEASSERTION?* *EVALUATIONMODE*))
       (PLI::ASSERT-NARY-PROPOSITION
        (CONS (GET-RELATION SGT-RDBMS-RDBMS-DB-CONNECTION)
         (CONS DATABASE (CONS CONNECTIONWRAPPER NIL)))
        NULL NULL)))
     CONNECTION))))

;;; (DEFUN DISCONNECT-FROM-DATABASE ...)

(CL:DEFUN DISCONNECT-FROM-DATABASE (DATABASE)
  (CL:LET*
   ((CONNECTION
     (ACCESS-BINARY-VALUE DATABASE SGT-RDBMS-RDBMS-DB-CONNECTION)))
   (CL:COND
    ((SUBTYPE-OF? (SAFE-PRIMARY-TYPE CONNECTION)
      SGT-RDBMS-RDBMS-CONNECTION-WRAPPER)
     (CL:PROGN
      (CL:WHEN (CL:NOT (CL:EQ (%WRAPPER-VALUE CONNECTION) NULL))
       (%DISCONNECT (%WRAPPER-VALUE CONNECTION)))
      (CL:LET*
       ((*MODULE* (%BASE-MODULE *CONTEXT*)) (*CONTEXT* *MODULE*))
       (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
       (PLI::RETRACT-NARY-PROPOSITION
        (CONS (GET-RELATION SGT-RDBMS-RDBMS-DB-CONNECTION)
         (CONS DATABASE (CONS CONNECTION NIL)))
        NULL NULL))))
    (CL:T))))

;;; (DEFUN (GET-CONNECTION-FROM-DATABASE /SDBC/CONNECTION) ...)

(CL:DEFUN GET-CONNECTION-FROM-DATABASE (DATABASE)
  (CL:LET*
   ((CONNECTION
     (ACCESS-BINARY-VALUE DATABASE SGT-RDBMS-RDBMS-DB-CONNECTION)))
   (CL:COND
    ((SUBTYPE-OF? (SAFE-PRIMARY-TYPE CONNECTION)
      SGT-RDBMS-RDBMS-CONNECTION-WRAPPER)
     (CL:PROGN (%WRAPPER-VALUE CONNECTION)))
    (CL:T (CONNECT-TO-DATABASE DATABASE)))))

;;; (DEFUN (GET-CONNECTION-FROM-PREDICATE /SDBC/CONNECTION) ...)

(CL:DEFUN GET-CONNECTION-FROM-PREDICATE (RELATIONREF)
  (CL:LET*
   ((DATABASE
     (ACCESS-BINARY-VALUE (GET-DESCRIPTION RELATIONREF)
      SGT-RDBMS-RDBMS-RELATION-DATABASE))
    (CONNECTION (GET-CONNECTION-FROM-DATABASE DATABASE)))
   CONNECTION))

;;; (DEFUN (ALLOCATE-RESULT-SET-ITERATOR (ITERATOR OF CONS)) ...)

(CL:DEFUN ALLOCATE-RESULT-SET-ITERATOR (CONNECTION RELATION SQLSTATEMENT)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SQLSTATEMENT))
  #+MCL
  (CL:CHECK-TYPE SQLSTATEMENT CL:SIMPLE-STRING)
  (CL:LET* ((SELF-000 (NEW-ALL-PURPOSE-ITERATOR)))
   (CL:SETF (%ITERATOR-NESTED-ITERATOR SELF-000)
    (GET-RESULT-SET CONNECTION SQLSTATEMENT))
   (CL:SETF (%ITERATOR-OBJECT SELF-000) RELATION)
   (CL:SETF (%ITERATOR-SECOND-OBJECT SELF-000)
    (GET-RELATION-TABLE-INFO RELATION))
   (CL:SETF (%ITERATOR-NEXT-CODE SELF-000)
    (CL:FUNCTION RESULT-SET-ITERATOR-NEXT?))
   (CL:LET* ((VALUE-000 SELF-000)) VALUE-000)))

;;; (DEFUN (RESULT-SET-ITERATOR-NEXT? BOOLEAN) ...)

(CL:DEFUN RESULT-SET-ITERATOR-NEXT? (SELF)
  (CL:LET*
   ((RESULTSET (%ITERATOR-NESTED-ITERATOR SELF))
    (TABLEINFO (%ITERATOR-SECOND-OBJECT SELF)))
   (CL:COND
    ((NEXT? RESULTSET)
     (CL:SETF (%VALUE SELF)
      (COERCE-VALUES (%VALUE RESULTSET) TABLEINFO))
     CL:T)
    (CL:T CL:NIL))))

;;; (DEFUN (GET-TABLE-RELATION NAMED-DESCRIPTION) ...)

(CL:DEFUN GET-TABLE-RELATION (TABLE-NAME MODULE)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TABLE-NAME))
  #+MCL
  (CL:CHECK-TYPE TABLE-NAME CL:SIMPLE-STRING)
  (CL:LET*
   ((ITER
     (PLI::RETRIEVE
      (LIST* (WRAP-INTEGER 1)
       (LIST* SYM-RDBMS-RDBMS-RELATION-TABLE SYM-RDBMS-LOGIC-?X
        (WRAP-STRING TABLE-NAME) NIL)
       NIL)
      MODULE NULL)))
   (CL:IF (NEXT? ITER) (%VALUE ITER) NULL)))

;;; (DEFUN (GET-TABLE-COLUMN-INDEX INTEGER) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T CL:SIMPLE-STRING CL:T) CL:FIXNUM)
  GET-TABLE-COLUMN-INDEX))
(CL:DEFUN GET-TABLE-COLUMN-INDEX (TABLE-RELATION COLUMN-NAME MODULE)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING COLUMN-NAME))
  #+MCL
  (CL:CHECK-TYPE COLUMN-NAME CL:SIMPLE-STRING)
  (CL:LET*
   ((ITER
     (PLI::RETRIEVE
      (LIST* (WRAP-INTEGER 1)
       (LIST* SYM-RDBMS-RDBMS-RELATION-COLUMN-NAME TABLE-RELATION
        (LIST* SYM-RDBMS-LOGIC-?X (WRAP-STRING COLUMN-NAME) NIL))
       NIL)
      MODULE NULL)))
   (CL:IF (NEXT? ITER) (%WRAPPER-VALUE (%VALUE ITER)) -1)))

;;; (DEFUN (GET-TABLE-COLUMN-MODULE-NAME STRING-WRAPPER) ...)

(CL:DEFUN GET-TABLE-COLUMN-MODULE-NAME (TABLERELATION COLUMNINDEX)
  (CL:DECLARE (CL:TYPE CL:FIXNUM COLUMNINDEX))
  #+MCL
  (CL:CHECK-TYPE COLUMNINDEX CL:FIXNUM)
  (POP
   (PLI::RETRIEVE
    (LIST* (WRAP-INTEGER 1)
     (LIST* SYM-RDBMS-RDBMS-RELATION-COLUMN-MODULE-NAME TABLERELATION
      (CONS (WRAP-INTEGER COLUMNINDEX) (CONS SYM-RDBMS-LOGIC-?X NIL)))
     NIL)
    NULL NULL)))

;;; (DEFUN (GET-TABLE-COLUMN-MODULE-REFERENCE STRING-WRAPPER) ...)

(CL:DEFUN GET-TABLE-COLUMN-MODULE-REFERENCE (TABLERELATION COLUMNINDEX)
  (CL:DECLARE (CL:TYPE CL:FIXNUM COLUMNINDEX))
  #+MCL
  (CL:CHECK-TYPE COLUMNINDEX CL:FIXNUM)
  (POP
   (PLI::RETRIEVE
    (LIST* (WRAP-INTEGER 1)
     (LIST* SYM-RDBMS-RDBMS-RELATION-COLUMN-MODULE-REFERENCE
      TABLERELATION
      (CONS (WRAP-INTEGER COLUMNINDEX) (CONS SYM-RDBMS-LOGIC-?X NIL)))
     NIL)
    NULL NULL)))

;;; (DEFUN (GET-TABLE-COLUMN-NAME STRING-WRAPPER) ...)

(CL:DEFUN GET-TABLE-COLUMN-NAME (TABLERELATION COLUMNINDEX)
  (CL:DECLARE (CL:TYPE CL:FIXNUM COLUMNINDEX))
  #+MCL
  (CL:CHECK-TYPE COLUMNINDEX CL:FIXNUM)
  (POP
   (PLI::RETRIEVE
    (LIST* (WRAP-INTEGER 1)
     (LIST* SYM-RDBMS-RDBMS-RELATION-COLUMN-NAME TABLERELATION
      (CONS (WRAP-INTEGER COLUMNINDEX) (CONS SYM-RDBMS-LOGIC-?X NIL)))
     NIL)
    NULL NULL)))

;;; (DEFUN (GET-TABLE-COLUMN-NAMES (CONS OF STRING-WRAPPER)) ...)

(CL:DEFUN GET-TABLE-COLUMN-NAMES (TABLERELATION)
  (CL:LET* ((VALUE-000 NIL))
   (CL:LET*
    ((COLUMN NULL)
     (ITER-000 (%COLUMN-LIST (GET-RELATION-TABLE-INFO TABLERELATION)))
     (COLLECT-000 NULL))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ COLUMN (%%VALUE ITER-000))
     (CL:IF (CL:EQ COLLECT-000 NULL)
      (CL:PROGN
       (CL:SETQ COLLECT-000
        (CONS (WRAP-STRING (%COLUMN-NAME COLUMN)) NIL))
       (CL:IF (CL:EQ VALUE-000 NIL) (CL:SETQ VALUE-000 COLLECT-000)
        (ADD-CONS-TO-END-OF-CONS-LIST VALUE-000 COLLECT-000)))
      (CL:PROGN
       (CL:SETF (%%REST COLLECT-000)
        (CONS (WRAP-STRING (%COLUMN-NAME COLUMN)) NIL))
       (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   (CL:LET* ((NAMES VALUE-000))
    (CL:IF (MEMBER? NAMES NULL) NULL NAMES))))

;;; (DEFCLASS RELATION-TABLE-INFO ...)

(CL:DEFCLASS RELATION-TABLE-INFO (STANDARD-OBJECT)
  ((RELATION :ALLOCATION :INSTANCE :ACCESSOR %RELATION)
   (DATABASE :ALLOCATION :INSTANCE :ACCESSOR %DATABASE)
   (DBMS-NAME :ALLOCATION :INSTANCE :ACCESSOR %DBMS-NAME)
   (TABLE-NAME :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %TABLE-NAME)
   (TABLE-ALIAS :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %TABLE-ALIAS)
   (COLUMN-LIST :ALLOCATION :INSTANCE :ACCESSOR %COLUMN-LIST)
   (COLUMN-VECTOR :ALLOCATION :INSTANCE :ACCESSOR %COLUMN-VECTOR)
   (COLUMN-INDEX :ALLOCATION :INSTANCE :ACCESSOR %COLUMN-INDEX)
   (ADJUNCT :ALLOCATION :INSTANCE :ACCESSOR %ADJUNCT))
  (:DOCUMENTATION
   "Data structure that associates a PowerLoom relation representing
a database table or query with various information about its columns, value coercion, etc."))

(CL:DEFUN NEW-RELATION-TABLE-INFO ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE RELATION-TABLE-INFO)))
   (CL:SETF (%ADJUNCT SELF) NULL) (CL:SETF (%COLUMN-INDEX SELF) NULL)
   (CL:SETF (%COLUMN-VECTOR SELF) NULL)
   (CL:SETF (%COLUMN-LIST SELF) NULL)
   (CL:SETF (%TABLE-ALIAS SELF) "_T")
   (CL:SETF (%TABLE-NAME SELF) STELLA::NULL-STRING)
   (CL:SETF (%DBMS-NAME SELF) NULL) (CL:SETF (%DATABASE SELF) NULL)
   (CL:SETF (%RELATION SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF RELATION-TABLE-INFO))
  SGT-RDBMS-RDBMS-RELATION-TABLE-INFO)

(CL:DEFUN ACCESS-RELATION-TABLE-INFO-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME SYM-RDBMS-STELLA-RELATION)
    (CL:IF SETVALUE? (CL:SETF (%RELATION SELF) VALUE)
     (CL:SETQ VALUE (%RELATION SELF))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-DATABASE)
    (CL:IF SETVALUE? (CL:SETF (%DATABASE SELF) VALUE)
     (CL:SETQ VALUE (%DATABASE SELF))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-DBMS-NAME)
    (CL:IF SETVALUE? (CL:SETF (%DBMS-NAME SELF) VALUE)
     (CL:SETQ VALUE (%DBMS-NAME SELF))))
   ((CL:EQ SLOTNAME SYM-RDBMS-STELLA-TABLE-NAME)
    (CL:IF SETVALUE?
     (CL:SETF (%TABLE-NAME SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%TABLE-NAME SELF)))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-TABLE-ALIAS)
    (CL:IF SETVALUE?
     (CL:SETF (%TABLE-ALIAS SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%TABLE-ALIAS SELF)))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-COLUMN-LIST)
    (CL:IF SETVALUE? (CL:SETF (%COLUMN-LIST SELF) VALUE)
     (CL:SETQ VALUE (%COLUMN-LIST SELF))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-COLUMN-VECTOR)
    (CL:IF SETVALUE? (CL:SETF (%COLUMN-VECTOR SELF) VALUE)
     (CL:SETQ VALUE (%COLUMN-VECTOR SELF))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-COLUMN-INDEX)
    (CL:IF SETVALUE? (CL:SETF (%COLUMN-INDEX SELF) VALUE)
     (CL:SETQ VALUE (%COLUMN-INDEX SELF))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-ADJUNCT)
    (CL:IF SETVALUE? (CL:SETF (%ADJUNCT SELF) VALUE)
     (CL:SETQ VALUE (%ADJUNCT SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFCLASS RELATION-COLUMN-INFO ...)

(CL:DEFCLASS RELATION-COLUMN-INFO (STANDARD-OBJECT)
  ((TABLE-INFO :ALLOCATION :INSTANCE :ACCESSOR %TABLE-INFO)
   (COLUMN-NAME :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %COLUMN-NAME)
   (COLUMN-VARIABLE :ALLOCATION :INSTANCE :ACCESSOR %COLUMN-VARIABLE)
   (COLUMN-INDEX :TYPE CL:FIXNUM :INITFORM NULL-INTEGER :ALLOCATION
    :INSTANCE :ACCESSOR %COLUMN-INDEX)
   (COLUMN-TYPE :ALLOCATION :INSTANCE :ACCESSOR %COLUMN-TYPE)
   (COLUMN-DB-TYPE :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %COLUMN-DB-TYPE)
   (MODULE-NAME :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %MODULE-NAME)
   (MODULE-REFERENCE :TYPE CL:SIMPLE-STRING :INITFORM
    STELLA::NULL-STRING :ALLOCATION :INSTANCE :ACCESSOR
    %MODULE-REFERENCE)
   (MODULE :ALLOCATION :INSTANCE :ACCESSOR %MODULE)
   (MODULE-LOCAL? :ALLOCATION :INSTANCE :ACCESSOR %MODULE-LOCAL?)
   (MODULE-REFERENCE-COLUMN :ALLOCATION :INSTANCE :ACCESSOR
    %MODULE-REFERENCE-COLUMN)
   (COERCION-FUNCTION :ALLOCATION :INSTANCE :ACCESSOR
    %COERCION-FUNCTION)))

(CL:DEFUN NEW-RELATION-COLUMN-INFO ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE RELATION-COLUMN-INFO)))
   (CL:SETF (%COERCION-FUNCTION SELF) NULL)
   (CL:SETF (%MODULE-REFERENCE-COLUMN SELF) NULL)
   (CL:SETF (%MODULE-LOCAL? SELF) CL:NIL) (CL:SETF (%MODULE SELF) NULL)
   (CL:SETF (%MODULE-REFERENCE SELF) STELLA::NULL-STRING)
   (CL:SETF (%MODULE-NAME SELF) STELLA::NULL-STRING)
   (CL:SETF (%COLUMN-DB-TYPE SELF) STELLA::NULL-STRING)
   (CL:SETF (%COLUMN-TYPE SELF) NULL)
   (CL:SETF (%COLUMN-INDEX SELF) NULL-INTEGER)
   (CL:SETF (%COLUMN-VARIABLE SELF) NULL)
   (CL:SETF (%COLUMN-NAME SELF) STELLA::NULL-STRING)
   (CL:SETF (%TABLE-INFO SELF) NULL) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF RELATION-COLUMN-INFO))
  SGT-RDBMS-RDBMS-RELATION-COLUMN-INFO)

(CL:DEFUN ACCESS-RELATION-COLUMN-INFO-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-TABLE-INFO)
    (CL:IF SETVALUE? (CL:SETF (%TABLE-INFO SELF) VALUE)
     (CL:SETQ VALUE (%TABLE-INFO SELF))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-COLUMN-NAME)
    (CL:IF SETVALUE?
     (CL:SETF (%COLUMN-NAME SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%COLUMN-NAME SELF)))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-COLUMN-VARIABLE)
    (CL:IF SETVALUE? (CL:SETF (%COLUMN-VARIABLE SELF) VALUE)
     (CL:SETQ VALUE (%COLUMN-VARIABLE SELF))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-COLUMN-INDEX)
    (CL:IF SETVALUE?
     (CL:SETF (%COLUMN-INDEX SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-INTEGER (%COLUMN-INDEX SELF)))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-COLUMN-TYPE)
    (CL:IF SETVALUE? (CL:SETF (%COLUMN-TYPE SELF) VALUE)
     (CL:SETQ VALUE (%COLUMN-TYPE SELF))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-COLUMN-DB-TYPE)
    (CL:IF SETVALUE?
     (CL:SETF (%COLUMN-DB-TYPE SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%COLUMN-DB-TYPE SELF)))))
   ((CL:EQ SLOTNAME SYM-RDBMS-STELLA-MODULE-NAME)
    (CL:IF SETVALUE?
     (CL:SETF (%MODULE-NAME SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%MODULE-NAME SELF)))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-MODULE-REFERENCE)
    (CL:IF SETVALUE?
     (CL:SETF (%MODULE-REFERENCE SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%MODULE-REFERENCE SELF)))))
   ((CL:EQ SLOTNAME SYM-RDBMS-STELLA-MODULE)
    (CL:IF SETVALUE? (CL:SETF (%MODULE SELF) VALUE)
     (CL:SETQ VALUE (%MODULE SELF))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-MODULE-LOCAL?)
    (CL:IF SETVALUE?
     (CL:SETF (%MODULE-LOCAL? SELF)
      (COERCE-WRAPPED-BOOLEAN-TO-BOOLEAN VALUE))
     (CL:SETQ VALUE
      (CL:IF (%MODULE-LOCAL? SELF) TRUE-WRAPPER FALSE-WRAPPER))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-MODULE-REFERENCE-COLUMN)
    (CL:IF SETVALUE? (CL:SETF (%MODULE-REFERENCE-COLUMN SELF) VALUE)
     (CL:SETQ VALUE (%MODULE-REFERENCE-COLUMN SELF))))
   ((CL:EQ SLOTNAME SYM-RDBMS-RDBMS-COERCION-FUNCTION)
    (CL:IF SETVALUE?
     (CL:SETF (%COERCION-FUNCTION SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-FUNCTION-CODE (%COERCION-FUNCTION SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFUN (CREATE-RELATION-TABLE-INFO RELATION-TABLE-INFO) ...)

(CL:DEFUN CREATE-RELATION-TABLE-INFO (RELATION)
  (CL:LET* ((SELF-000 (NEW-RELATION-TABLE-INFO)))
   (CL:SETF (%RELATION SELF-000) RELATION)
   (CL:LET*
    ((TABLEINFO SELF-000) (COLUMNINFO NULL)
     (ARITY (LENGTH (%IO-VARIABLES RELATION))) (COLUMNS NIL)
     (DEFAULTMODULE (%BASE-MODULE *CONTEXT*)))
    (CL:DECLARE (CL:TYPE CL:FIXNUM ARITY))
    (CL:SETF (%DATABASE TABLEINFO)
     (ACCESS-BINARY-VALUE RELATION SGT-RDBMS-RDBMS-RELATION-DATABASE))
    (CL:SETF (%DBMS-NAME TABLEINFO)
     (CL:IF (CL:NOT (CL:EQ (%DATABASE TABLEINFO) NULL))
      (GET-DBMS-NAME
       (GET-CONNECTION-FROM-DATABASE (%DATABASE TABLEINFO)))
      KWD-RDBMS-UNKNOWN))
    (CL:SETF (%TABLE-NAME TABLEINFO)
     (UNWRAP-STRING
      (ACCESS-BINARY-VALUE RELATION SGT-RDBMS-RDBMS-RELATION-TABLE)))
    (CL:SETF (%COLUMN-INDEX TABLEINFO) (NEW-KEY-VALUE-MAP))
    (CL:LET*
     ((I NULL-INTEGER) (ITER-000 1) (UPPER-BOUND-000 ARITY)
      (UNBOUNDED?-000 (CL:= UPPER-BOUND-000 NULL-INTEGER)) (VAR NULL)
      (ITER-001 (%THE-CONS-LIST (%IO-VARIABLE-NAMES RELATION)))
      (COLLECT-000 NULL))
     (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-000 UPPER-BOUND-000))
     (CL:LOOP WHILE
      (CL:AND (CL:OR UNBOUNDED?-000 (CL:<= ITER-000 UPPER-BOUND-000))
       (CL:NOT (CL:EQ ITER-001 NIL)))
      DO (CL:SETQ I ITER-000) (CL:SETQ VAR (%%VALUE ITER-001))
      (CL:LET* ((SELF-002 (NEW-RELATION-COLUMN-INFO)))
       (CL:SETF (%TABLE-INFO SELF-002) TABLEINFO)
       (CL:SETQ COLUMNINFO SELF-002))
      (CL:SETF (%COLUMN-NAME COLUMNINFO)
       (UNWRAP-STRING (GET-TABLE-COLUMN-NAME RELATION I)))
      (CL:SETF (%COLUMN-VARIABLE COLUMNINFO) VAR)
      (CL:SETF (%COLUMN-INDEX COLUMNINFO) (CL:1- I))
      (CL:SETF (%COLUMN-TYPE COLUMNINFO)
       (PLI::GET-NTH-DOMAIN RELATION (CL:1- I)))
      (CL:SETF (%MODULE-NAME COLUMNINFO)
       (UNWRAP-STRING (GET-TABLE-COLUMN-MODULE-NAME RELATION I)))
      (CL:SETF (%MODULE-REFERENCE COLUMNINFO)
       (UNWRAP-STRING (GET-TABLE-COLUMN-MODULE-REFERENCE RELATION I)))
      (INSERT-AT (%COLUMN-INDEX TABLEINFO)
       (WRAP-STRING (%COLUMN-NAME COLUMNINFO)) COLUMNINFO)
      (INSERT-AT (%COLUMN-INDEX TABLEINFO) VAR COLUMNINFO)
      (INSERT-AT (%COLUMN-INDEX TABLEINFO)
       (WRAP-STRING (%SYMBOL-NAME VAR)) COLUMNINFO)
      (CL:IF (CL:EQ COLLECT-000 NULL)
       (CL:PROGN (CL:SETQ COLLECT-000 (CONS COLUMNINFO NIL))
        (CL:IF (CL:EQ COLUMNS NIL) (CL:SETQ COLUMNS COLLECT-000)
         (ADD-CONS-TO-END-OF-CONS-LIST COLUMNS COLLECT-000)))
       (CL:PROGN (CL:SETF (%%REST COLLECT-000) (CONS COLUMNINFO NIL))
        (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
      (CL:SETQ ITER-000 (CL:1+ ITER-000))
      (CL:SETQ ITER-001 (%%REST ITER-001))))
    (CL:SETF (%COLUMN-LIST TABLEINFO) COLUMNS)
    (CL:SETF (%COLUMN-VECTOR TABLEINFO) (CONS-TO-VECTOR COLUMNS))
    (CL:LET* ((COLUMN NULL) (ITER-002 (%COLUMN-LIST TABLEINFO)))
     (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-002 NIL)) DO
      (CL:SETQ COLUMN (%%VALUE ITER-002))
      (CL:COND
       ((CL:NOT (CL:EQ (%MODULE-NAME COLUMN) STELLA::NULL-STRING))
        (CL:SETF (%MODULE-LOCAL? COLUMN) CL:T)
        (CL:SETF (%MODULE COLUMN)
         (GET-STELLA-MODULE (%MODULE-NAME COLUMN) CL:NIL))
        (CL:WHEN (CL:EQ (%MODULE COLUMN) NULL)
         (CL:WARN
          "RDBMS: Column module `~A' for column `~A' on relation `~A' is not defined; ignoring it..."
          (%MODULE-NAME COLUMN) (%COLUMN-NAME COLUMN) RELATION)
         (CL:SETF (%MODULE COLUMN) DEFAULTMODULE)))
       ((CL:NOT (CL:EQ (%MODULE-REFERENCE COLUMN) STELLA::NULL-STRING))
        (CL:SETF (%MODULE-LOCAL? COLUMN) CL:T)
        (CL:SETF (%MODULE-REFERENCE-COLUMN COLUMN)
         (LOOKUP (%COLUMN-INDEX TABLEINFO)
          (WRAP-STRING (%MODULE-REFERENCE COLUMN)))))
       (CL:T (CL:SETF (%MODULE COLUMN) DEFAULTMODULE)))
      (CL:SETQ ITER-002 (%%REST ITER-002))))
    TABLEINFO)))

;;; (DEFUN (GET-MODULE-USING-REFERENCE MODULE) ...)

(CL:DEFUN GET-MODULE-USING-REFERENCE (COLUMN VALUES)
  (CL:LET*
   ((REFCOLUMINDEX (%COLUMN-INDEX (%MODULE-REFERENCE-COLUMN COLUMN)))
    (MODULENAME (NTH VALUES REFCOLUMINDEX))
    (MODULE
     (CL:IF (CL:NOT (CL:EQ MODULENAME NULL))
      (GET-STELLA-MODULE (%WRAPPER-VALUE MODULENAME) CL:NIL) NULL)))
   (CL:DECLARE (CL:TYPE CL:FIXNUM REFCOLUMINDEX))
   (CL:WHEN (CL:EQ MODULE NULL)
    (CL:WARN
     "RDBMS: Column module `~A' defined by reference for column `~A' on relation `~A' is not defined; ignoring it..."
     MODULENAME (%COLUMN-NAME COLUMN) (%RELATION (%TABLE-INFO COLUMN)))
    (CL:SETQ MODULE (%BASE-MODULE *CONTEXT*)))
   MODULE))

;;; (DEFUN (GET-RELATION-TABLE-INFO RELATION-TABLE-INFO) ...)

(CL:DEFUN GET-RELATION-TABLE-INFO (TABLERELATION)
  (CL:LET*
   ((MEMO-TABLE-000 NULL) (MEMOIZED-ENTRY-000 NULL)
    (MEMOIZED-VALUE-000 NULL))
   (CL:WHEN *MEMOIZATION-ENABLED?*
    (CL:SETQ MEMO-TABLE-000
     (%SURROGATE-VALUE
      SGT-RDBMS-RDBMS-F-GET-RELATION-TABLE-INFO-MEMO-TABLE-000))
    (CL:WHEN (CL:EQ MEMO-TABLE-000 NULL)
     (INITIALIZE-MEMOIZATION-TABLE
      SGT-RDBMS-RDBMS-F-GET-RELATION-TABLE-INFO-MEMO-TABLE-000
      "(:MAX-VALUES 100 :TIMESTAMPS (:META-KB-UPDATE))")
     (CL:SETQ MEMO-TABLE-000
      (%SURROGATE-VALUE
       SGT-RDBMS-RDBMS-F-GET-RELATION-TABLE-INFO-MEMO-TABLE-000)))
    (CL:SETQ MEMOIZED-ENTRY-000
     (LOOKUP-MRU-MEMOIZED-VALUE MEMO-TABLE-000 TABLERELATION *CONTEXT*
      MEMOIZED-NULL-VALUE NULL -1))
    (CL:SETQ MEMOIZED-VALUE-000 (%%VALUE MEMOIZED-ENTRY-000)))
   (CL:COND
    ((CL:NOT (CL:EQ MEMOIZED-VALUE-000 NULL))
     (CL:WHEN (CL:EQ MEMOIZED-VALUE-000 MEMOIZED-NULL-VALUE)
      (CL:SETQ MEMOIZED-VALUE-000 NULL)))
    (CL:T
     (CL:SETQ MEMOIZED-VALUE-000
      (CREATE-RELATION-TABLE-INFO TABLERELATION))
     (CL:WHEN *MEMOIZATION-ENABLED?*
      (CL:SETF (%%VALUE MEMOIZED-ENTRY-000)
       (CL:IF (CL:EQ MEMOIZED-VALUE-000 NULL) MEMOIZED-NULL-VALUE
        MEMOIZED-VALUE-000)))))
   (CL:LET* ((VALUE-000 MEMOIZED-VALUE-000)) VALUE-000)))

;;; (DEFUN (COLLECTION-VALUED-CONSTRAINT? BOOLEAN) ...)

(CL:DEFUN COLLECTION-VALUED-CONSTRAINT? (ARGUMENT)
  (CL:AND (CL:NOT (CL:EQ ARGUMENT NULL))
   (CL:OR (ENUMERATED-LIST? ARGUMENT) (ENUMERATED-SET? ARGUMENT))))

;;; (DEFUN (COLLECTION-VALUED-CONSTRAINT-ELEMENTS CONS) ...)

(CL:DEFUN COLLECTION-VALUED-CONSTRAINT-ELEMENTS (ARGUMENT)
  (CONSIFY (ASSERTED-COLLECTION-MEMBERS ARGUMENT CL:T)))

;;; (DEFUN PRINT-SQL-VALUE ...)

(CL:DEFUN PRINT-SQL-VALUE (STREAM VALUE COLUMN)
  (CL:LET*
   ((TARGET-TYPE (%COLUMN-TYPE COLUMN))
    (BASE-STRING (COERCE-POWERLOOM-OBJECT-TO-STRING VALUE TARGET-TYPE))
    (QUOTE-CHAR
     (SQL-QUOTE-CHARACTER (%DBMS-NAME (%TABLE-INFO COLUMN))
      KWD-RDBMS-STRING-CONSTANT)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING BASE-STRING))
   (CL:COND
    ((CL:EQ TARGET-TYPE (GET-DESCRIPTION SGT-RDBMS-STELLA-STRING))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM) QUOTE-CHAR
      (SQL-ESCAPE-STRING BASE-STRING QUOTE-CHAR) QUOTE-CHAR))
    ((CL:OR
      (SUBRELATION-OF? TARGET-TYPE
       (GET-DESCRIPTION SGT-RDBMS-STELLA-NUMBER))
      (SUBRELATION-OF? TARGET-TYPE
       (GET-DESCRIPTION SGT-RDBMS-STELLA-BOOLEAN)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM) BASE-STRING))
    (CL:T
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM) QUOTE-CHAR
      (SQL-ESCAPE-STRING BASE-STRING QUOTE-CHAR) QUOTE-CHAR)))))

;;; (DEFUN PRINT-COLUMN-CONSTRAINT ...)

(CL:DEFUN PRINT-COLUMN-CONSTRAINT (SQL COLUMN VALUE CASESENSITIVE?)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING VALUE))
  #+MCL
  (CL:CHECK-TYPE VALUE CL:SIMPLE-STRING)
  (CL:LET*
   ((TABLEINFO (%TABLE-INFO COLUMN))
    (TABLEALIAS (%TABLE-ALIAS TABLEINFO))
    (COLUMNNAME (%COLUMN-NAME COLUMN)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TABLEALIAS COLUMNNAME))
   (CL:WHEN (CL:NOT (CL:EQ TABLEALIAS STELLA::NULL-STRING))
    (CL:SETQ COLUMNNAME (CONCATENATE TABLEALIAS "." COLUMNNAME)))
   (%%PRINT-STREAM (%NATIVE-STREAM SQL) COLUMNNAME "=")
   (PRINT-SQL-VALUE SQL (WRAP-STRING VALUE) COLUMN)
   (CL:WHEN CASESENSITIVE?
    (CL:COND
     ((CL:EQ (%DBMS-NAME TABLEINFO) KWD-RDBMS-MYSQL)
      (%%PRINT-STREAM (%NATIVE-STREAM SQL) " AND " COLUMNNAME
       " LIKE BINARY ")
      (PRINT-SQL-VALUE SQL (WRAP-STRING VALUE) COLUMN))
     (CL:T)))))

;;; (DEFUN PRINT-ARGUMENT-CONSTRAINT ...)

(CL:DEFUN PRINT-ARGUMENT-CONSTRAINT (SQL ARGUMENT COLUMN)
  (CL:LET*
   ((COLUMNTYPE (%COLUMN-TYPE COLUMN))
    (ARGNAME (OBJECT-SURROGATE ARGUMENT))
    (ARGMODULE
     (CL:IF (CL:NOT (CL:EQ ARGNAME NULL)) (%HOME-CONTEXT ARGNAME)
      NULL))
    (MODULEREFCOLUMN (%MODULE-REFERENCE-COLUMN COLUMN))
    (CASESENSITIVE?
     (CL:OR
      (CL:AND (CL:NOT (CL:EQ ARGMODULE NULL))
       (%CASE-SENSITIVE? ARGMODULE))
      (ISA? ARGUMENT SGT-RDBMS-STELLA-STRING-WRAPPER))))
   (CL:COND
    ((COLLECTION-VALUED-CONSTRAINT? ARGUMENT)
     (%%PRINT-STREAM (%NATIVE-STREAM SQL) "(")
     (CL:LET*
      ((SUBARG NULL)
       (ITER-000 (COLLECTION-VALUED-CONSTRAINT-ELEMENTS ARGUMENT))
       (SI NULL-INTEGER) (ITER-001 1))
      (CL:DECLARE (CL:TYPE CL:FIXNUM SI ITER-001))
      (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
       (CL:SETQ SUBARG (%%VALUE ITER-000)) (CL:SETQ SI ITER-001)
       (CL:WHEN (CL:> SI 1)
        (%%PRINT-STREAM (%NATIVE-STREAM SQL) " OR "))
       (PRINT-COLUMN-CONSTRAINT SQL COLUMN
        (COERCE-POWERLOOM-OBJECT-TO-STRING SUBARG COLUMNTYPE)
        CASESENSITIVE?)
       (CL:SETQ ITER-000 (%%REST ITER-000))
       (CL:SETQ ITER-001 (CL:1+ ITER-001))))
     (%%PRINT-STREAM (%NATIVE-STREAM SQL) ")"))
    (CL:T
     (PRINT-COLUMN-CONSTRAINT SQL COLUMN
      (COERCE-POWERLOOM-OBJECT-TO-STRING ARGUMENT COLUMNTYPE)
      CASESENSITIVE?)))
   (CL:WHEN
    (CL:AND (CL:NOT (CL:EQ MODULEREFCOLUMN NULL))
     (CL:NOT (CL:EQ ARGMODULE NULL)))
    (%%PRINT-STREAM (%NATIVE-STREAM SQL) " AND ")
    (PRINT-COLUMN-CONSTRAINT SQL MODULEREFCOLUMN
     (%MODULE-NAME ARGMODULE) CL:NIL))))

;;; (DEFUN PRINT-SQL-COLUMN-LIST ...)

(CL:DEFUN PRINT-SQL-COLUMN-LIST (STREAM TABLE-INFO)
  (CL:LET* ((FIRST? CL:T) (ALIAS (%TABLE-ALIAS TABLE-INFO)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING ALIAS))
   (CL:LET* ((COLUMN NULL) (ITER-000 (%COLUMN-LIST TABLE-INFO)))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ COLUMN (%%VALUE ITER-000))
     (CL:IF FIRST? (CL:SETQ FIRST? CL:NIL)
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM) ", "))
     (CL:IF (CL:NOT (CL:EQ ALIAS STELLA::NULL-STRING))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM) ALIAS "."
       (%COLUMN-NAME COLUMN))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM) (%COLUMN-NAME COLUMN)))
     (CL:SETQ ITER-000 (%%REST ITER-000))))))

;;; (DEFUN PRINT-SQL-CONSTRAINT-LIST ...)

(CL:DEFUN PRINT-SQL-CONSTRAINT-LIST (STREAM TABLE-INFO ARGUMENTS)
  (CL:LET* ((FIRST? CL:T))
   (CL:LET*
    ((COLUMN NULL) (ITER-000 (%COLUMN-LIST TABLE-INFO)) (ARG NULL)
     (VECTOR-000 ARGUMENTS) (INDEX-000 0)
     (LENGTH-000 (LENGTH VECTOR-000)))
    (CL:DECLARE (CL:TYPE CL:FIXNUM INDEX-000 LENGTH-000))
    (CL:LOOP WHILE
     (CL:AND (CL:NOT (CL:EQ ITER-000 NIL)) (CL:< INDEX-000 LENGTH-000))
     DO (CL:SETQ COLUMN (%%VALUE ITER-000))
     (CL:SETQ ARG
      (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY VECTOR-000))
       INDEX-000))
     (CL:SETQ ARG (SAFE-ARGUMENT-BOUND-TO ARG))
     (CL:WHEN (CL:AND (CL:NOT (CL:EQ ARG NULL)) (CL:NOT (SKOLEM? ARG)))
      (CL:IF FIRST?
       (CL:PROGN (CL:SETQ FIRST? CL:NIL)
        (%%PRINT-STREAM (%NATIVE-STREAM STREAM) " WHERE "))
       (%%PRINT-STREAM (%NATIVE-STREAM STREAM) " AND "))
      (PRINT-ARGUMENT-CONSTRAINT STREAM ARG COLUMN))
     (CL:SETQ ITER-000 (%%REST ITER-000))
     (CL:SETQ INDEX-000 (CL:1+ INDEX-000))))))

;;; (DEFUN (CREATE-SQL-FROM-PROPOSITION STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T) CL:SIMPLE-STRING)
  CREATE-SQL-FROM-PROPOSITION))
(CL:DEFUN CREATE-SQL-FROM-PROPOSITION (PROPOSITION)
  (CL:LET*
   ((RELATION (GET-DESCRIPTION (%OPERATOR PROPOSITION)))
    (TABLEINFO (GET-RELATION-TABLE-INFO RELATION))
    (TABLEALIAS (%TABLE-ALIAS TABLEINFO))
    (ARGUMENTS (%ARGUMENTS PROPOSITION))
    (SQL (NEW-OUTPUT-STRING-STREAM)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TABLEALIAS))
   (%%PRINT-STREAM (%NATIVE-STREAM SQL) "SELECT DISTINCT ")
   (PRINT-SQL-COLUMN-LIST SQL TABLEINFO)
   (%%PRINT-STREAM (%NATIVE-STREAM SQL) " FROM "
    (%TABLE-NAME TABLEINFO))
   (CL:WHEN (CL:NOT (CL:EQ TABLEALIAS STELLA::NULL-STRING))
    (%%PRINT-STREAM (%NATIVE-STREAM SQL) " " TABLEALIAS))
   (PRINT-SQL-CONSTRAINT-LIST SQL TABLEINFO ARGUMENTS)
   (THE-STRING-READER SQL)))

;;; (DEFUN (ALLOCATE-DBTABLE-SPECIALIST-ITERATOR (ITERATOR OF CONS)) ...)

(CL:DEFUN ALLOCATE-DBTABLE-SPECIALIST-ITERATOR (FRAME)
  (CL:WHEN
   (CL:EQ
    (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FRAME)
     SYM-RDBMS-STELLA-ITERATOR NULL)
    NULL)
   (CL:LET*
    ((PROPOSITION (%PROPOSITION FRAME))
     (RELATIONREF (%OPERATOR PROPOSITION))
     (RELATION (GET-DESCRIPTION RELATIONREF)))
    (CHECK-FOR-EXTERNAL-DB-UPDATES PROPOSITION
     (ACCESS-BINARY-VALUE RELATION SGT-RDBMS-RDBMS-DATABASE))
    (CL:LET*
     ((MEMO-TABLE-000 NULL) (MEMOIZED-ENTRY-000 NULL)
      (MEMOIZED-VALUE-000 NULL))
     (CL:WHEN *MEMOIZATION-ENABLED?*
      (CL:SETQ MEMO-TABLE-000
       (%SURROGATE-VALUE
        SGT-RDBMS-RDBMS-F-ALLOCATE-DBTABLE-SPECIALIST-ITERATOR-MEMO-TABLE-000))
      (CL:WHEN (CL:EQ MEMO-TABLE-000 NULL)
       (INITIALIZE-MEMOIZATION-TABLE
        SGT-RDBMS-RDBMS-F-ALLOCATE-DBTABLE-SPECIALIST-ITERATOR-MEMO-TABLE-000
        "(:MAX-VALUES 1000 :TIMESTAMPS (:META-KB-UPDATE :EXTERNAL-DB-UPDATE))")
       (CL:SETQ MEMO-TABLE-000
        (%SURROGATE-VALUE
         SGT-RDBMS-RDBMS-F-ALLOCATE-DBTABLE-SPECIALIST-ITERATOR-MEMO-TABLE-000)))
      (CL:SETQ MEMOIZED-ENTRY-000
       (LOOKUP-MRU-MEMOIZED-VALUE MEMO-TABLE-000
        (GET-QUERY-PATTERN-MEMOIZATION-KEY PROPOSITION) *CONTEXT*
        (CL:IF *REVERSEPOLARITY?* TRUE-WRAPPER FALSE-WRAPPER)
        MEMOIZED-NULL-VALUE 6))
      (CL:SETQ MEMOIZED-VALUE-000 (%%VALUE MEMOIZED-ENTRY-000)))
     (CL:COND
      ((CL:NOT (CL:EQ MEMOIZED-VALUE-000 NULL))
       (CL:WHEN (CL:EQ MEMOIZED-VALUE-000 MEMOIZED-NULL-VALUE)
        (CL:SETQ MEMOIZED-VALUE-000 NULL)))
      (CL:T
       (CL:SETQ MEMOIZED-VALUE-000
        (NEW-MEMOIZABLE-ITERATOR
         (ALLOCATE-RESULT-SET-ITERATOR
          (GET-CONNECTION-FROM-PREDICATE RELATIONREF) RELATION
          (CREATE-SQL-FROM-PROPOSITION PROPOSITION))))
       (CL:WHEN *MEMOIZATION-ENABLED?*
        (CL:SETF (%%VALUE MEMOIZED-ENTRY-000)
         (CL:IF (CL:EQ MEMOIZED-VALUE-000 NULL) MEMOIZED-NULL-VALUE
          MEMOIZED-VALUE-000)))))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FRAME)
      SYM-RDBMS-STELLA-ITERATOR
      (CLONE-MEMOIZED-ITERATOR MEMOIZED-VALUE-000) NULL))))
  (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FRAME) SYM-RDBMS-STELLA-ITERATOR
   NULL))

;;; (DEFUN (RETRIEVE-NEXT-DB-QUERY-SOLUTION KEYWORD) ...)

(CL:DEFUN RETRIEVE-NEXT-DB-QUERY-SOLUTION (FRAME LASTMOVE)
  (CL:LET*
   ((ARGUMENTS (%ARGUMENTS (%PROPOSITION FRAME)))
    (ITERATOR
     (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FRAME)
      SYM-RDBMS-STELLA-ITERATOR NULL)))
   (CL:SETQ LASTMOVE LASTMOVE)
   (CL:WHEN (CL:EQ ITERATOR NULL)
    (CL:RETURN-FROM RETRIEVE-NEXT-DB-QUERY-SOLUTION KWD-RDBMS-FAILURE))
   (CL:WHEN (%FIRST-ITERATION? ITERATOR)
    (CL:WHEN (CL:NOT (NEXT? ITERATOR))
     (CL:RETURN-FROM RETRIEVE-NEXT-DB-QUERY-SOLUTION
      KWD-RDBMS-FAILURE))
    (CL:SETF (%FIRST-ITERATION? ITERATOR) CL:NIL))
   (CL:LOOP
    (CL:LET* ((NONULLS? CL:T) (RESULT NIL) (BINDING NULL))
     (CL:LET*
      ((COL NULL) (ITER-000 (%VALUE ITERATOR)) (ARG NULL)
       (VECTOR-000 ARGUMENTS) (INDEX-000 0)
       (LENGTH-000 (LENGTH VECTOR-000)) (COLLECT-000 NULL))
      (CL:DECLARE (CL:TYPE CL:FIXNUM INDEX-000 LENGTH-000))
      (CL:LOOP WHILE
       (CL:AND (CL:NOT (CL:EQ ITER-000 NIL))
        (CL:< INDEX-000 LENGTH-000))
       DO (CL:SETQ COL (%%VALUE ITER-000))
       (CL:SETQ ARG
        (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY VECTOR-000))
         INDEX-000))
       (CL:SETQ BINDING (ARGUMENT-BOUND-TO ARG))
       (CL:COND ((CL:EQ COL NULL) (CL:SETQ NONULLS? CL:NIL))
        ((CL:AND (CL:NOT (CL:EQ BINDING NULL))
          (CL:NOT (SKOLEM? BINDING)))
         (CL:SETQ COL BINDING)))
       (CL:IF (CL:EQ COLLECT-000 NULL)
        (CL:PROGN (CL:SETQ COLLECT-000 (CONS COL NIL))
         (CL:IF (CL:EQ RESULT NIL) (CL:SETQ RESULT COLLECT-000)
          (ADD-CONS-TO-END-OF-CONS-LIST RESULT COLLECT-000)))
        (CL:PROGN (CL:SETF (%%REST COLLECT-000) (CONS COL NIL))
         (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
       (CL:SETQ ITER-000 (%%REST ITER-000))
       (CL:SETQ INDEX-000 (CL:1+ INDEX-000))))
     (CL:WHEN
      (CL:OR
       (CL:AND (CL:NOT (CL:EQ *QUERYITERATOR* NULL))
        (CL:NOT
         (CL:EQ (%PARTIAL-MATCH-STRATEGY *QUERYITERATOR*) NULL)))
       NONULLS?)
      (CL:WHEN (BIND-VECTOR-OF-ARGUMENTS-TO-VALUES? ARGUMENTS RESULT)
       (CL:RETURN)))
     (CL:WHEN (CL:NOT (NEXT? ITERATOR))
      (CL:RETURN-FROM RETRIEVE-NEXT-DB-QUERY-SOLUTION
       KWD-RDBMS-FAILURE))))
   (CL:WHEN *RECORD-JUSTIFICATIONS?*
    (CL:LET* ((SELF-000 (NEW-PRIMITIVE-STRATEGY)))
     (CL:SETF (%STRATEGY SELF-000) KWD-RDBMS-DB-LOOKUP)
     (CL:SETF (%ANTECEDENTS SELF-000) NIL)
     (RECORD-GOAL-JUSTIFICATION FRAME SELF-000)))
   (CL:IF (NEXT? ITERATOR) KWD-RDBMS-CONTINUING-SUCCESS
    (CL:PROGN (SET-FRAME-TRUTH-VALUE FRAME TRUE-TRUTH-VALUE)
     KWD-RDBMS-FINAL-SUCCESS))))

;;; (DEFUN (DBTABLE-SPECIALIST KEYWORD) ...)

(CL:DEFUN DBTABLE-SPECIALIST (FRAME LASTMOVE)
  (CL:WHEN
   (CL:EQ
    (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FRAME)
     SYM-RDBMS-STELLA-ITERATOR NULL)
    NULL)
   (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FRAME)
    SYM-RDBMS-STELLA-ITERATOR
    (ALLOCATE-DBTABLE-SPECIALIST-ITERATOR FRAME) NULL))
  (RETRIEVE-NEXT-DB-QUERY-SOLUTION FRAME LASTMOVE))

;;; (DEFUN (GET-QUERY-PATTERN-EVALUATORS (CONS OF CONS)) ...)

(CL:DEFUN GET-QUERY-PATTERN-EVALUATORS (RELATIONREF)
  (CL:LET* ((EVALUATORFORMS NIL))
   (CL:LET*
    ((MEMO-TABLE-000 NULL) (MEMOIZED-ENTRY-000 NULL)
     (MEMOIZED-VALUE-000 NULL))
    (CL:WHEN *MEMOIZATION-ENABLED?*
     (CL:SETQ MEMO-TABLE-000
      (%SURROGATE-VALUE
       SGT-RDBMS-RDBMS-F-GET-QUERY-PATTERN-EVALUATORS-MEMO-TABLE-000))
     (CL:WHEN (CL:EQ MEMO-TABLE-000 NULL)
      (INITIALIZE-MEMOIZATION-TABLE
       SGT-RDBMS-RDBMS-F-GET-QUERY-PATTERN-EVALUATORS-MEMO-TABLE-000
       "(:MAX-VALUES 100 :TIMESTAMPS (:META-KB-UPDATE))")
      (CL:SETQ MEMO-TABLE-000
       (%SURROGATE-VALUE
        SGT-RDBMS-RDBMS-F-GET-QUERY-PATTERN-EVALUATORS-MEMO-TABLE-000)))
     (CL:SETQ MEMOIZED-ENTRY-000
      (LOOKUP-MRU-MEMOIZED-VALUE MEMO-TABLE-000 RELATIONREF *CONTEXT*
       MEMOIZED-NULL-VALUE NULL -1))
     (CL:SETQ MEMOIZED-VALUE-000 (%%VALUE MEMOIZED-ENTRY-000)))
    (CL:COND
     ((CL:NOT (CL:EQ MEMOIZED-VALUE-000 NULL))
      (CL:WHEN (CL:EQ MEMOIZED-VALUE-000 MEMOIZED-NULL-VALUE)
       (CL:SETQ MEMOIZED-VALUE-000 NULL)))
     (CL:T
      (CL:SETQ MEMOIZED-VALUE-000
       (APPLY-CACHED-RETRIEVE
        (LIST* SYM-RDBMS-RDBMS-?REL SYM-RDBMS-RDBMS-?EV
         SYM-RDBMS-RDBMS-?DB SYM-RDBMS-RDBMS-?ARGS NIL)
        (LIST* SYM-RDBMS-STELLA-AND
         (LIST* SYM-RDBMS-RDBMS-QUERY-PATTERN SYM-RDBMS-RDBMS-?REL
          SYM-RDBMS-RDBMS-?EV SYM-RDBMS-RDBMS-?DB SYM-RDBMS-RDBMS-?ARGS
          NIL)
         (LIST* SYM-RDBMS-STELLA-EXISTS
          (CONS SYM-RDBMS-RDBMS-?DB-TYPE NIL)
          (LIST* SYM-RDBMS-RDBMS-SUPPORTS-DB-TYPE SYM-RDBMS-RDBMS-?EV
           SYM-RDBMS-RDBMS-?DB-TYPE NIL)
          (LIST* SYM-RDBMS-RDBMS-INSTANCE-OF SYM-RDBMS-RDBMS-?DB
           SYM-RDBMS-RDBMS-?DB-TYPE NIL)
          NIL)
         NIL)
        (CONS-LIST RELATIONREF NULL NULL NULL)
        (CONS-LIST KWD-RDBMS-DONT-OPTIMIZE? TRUE-WRAPPER
         KWD-RDBMS-HOW-MANY KWD-RDBMS-ALL KWD-RDBMS-INFERENCE-LEVEL
         KWD-RDBMS-ASSERTION)
        SYM-RDBMS-RDBMS-F-GET-QUERY-PATTERN-EVALUATORS-QUERY-001))
      (CL:WHEN *MEMOIZATION-ENABLED?*
       (CL:SETF (%%VALUE MEMOIZED-ENTRY-000)
        (CL:IF (CL:EQ MEMOIZED-VALUE-000 NULL) MEMOIZED-NULL-VALUE
         MEMOIZED-VALUE-000)))))
    (CL:LET* ((PATTERNS MEMOIZED-VALUE-000))
     (CL:LET* ((TRIPLE NULL) (ITER-000 PATTERNS))
      (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
       (CL:SETQ TRIPLE (%%VALUE ITER-000))
       (CL:LET*
        ((CODE (FUNCTION-CODE-FROM-PROCEDURE (%%VALUE TRIPLE))))
        (CL:WHEN (CL:NOT (CL:EQ CODE NULL))
         (CL:SETQ EVALUATORFORMS
          (CONS
           (CONS-LIST (WRAP-FUNCTION-CODE CODE)
            (%%VALUE (%%REST TRIPLE))
            (%%VALUE (%%REST (%%REST TRIPLE))))
           EVALUATORFORMS))))
       (CL:SETQ ITER-000 (%%REST ITER-000))))
     (REVERSE EVALUATORFORMS)))))

;;; (DEFUN (NORMALIZE-SQL-JOIN-ARGUMENTS CONS CONS) ...)

(CL:DEFUN NORMALIZE-SQL-JOIN-ARGUMENTS (TABLEINFO ARGUMENTS)
  (CL:WHEN (CL:NOT (CL:EQ (%ADJUNCT TABLEINFO) NULL))
   (CL:RETURN-FROM NORMALIZE-SQL-JOIN-ARGUMENTS
    (CL:VALUES (%%VALUE (%ADJUNCT TABLEINFO))
     (%%VALUE (%%REST (%ADJUNCT TABLEINFO))))))
  (CL:WHEN (CL:NOT (STRING? ARGUMENTS))
   (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
    (CL:LET* ((*PRINTREADABLY?* CL:T))
     (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
      "PARSING ERROR: SQL-join: illegal pattern arguments: `" ARGUMENTS
      "'." EOL)
     (HELP-SIGNAL-PROPOSITION-ERROR STREAM-000 KWD-RDBMS-ERROR))
    (CL:ERROR (NEW-PARSING-ERROR (THE-STRING-READER STREAM-000)))))
  (CL:LET*
   ((ARGS (READ-S-EXPRESSION-FROM-STRING (%WRAPPER-VALUE ARGUMENTS)))
    (TABLES NIL) (JOINARGS NIL))
   (CL:COND
    ((CL:EQ (SAFE-PRIMARY-TYPE ARGS) SGT-RDBMS-STELLA-CONS)
     (CL:PROGN
      (CL:LET* ((TEST-VALUE-000 CL:NIL))
       (CL:SETQ TEST-VALUE-000 (>= (LENGTH ARGS) 2))
       (CL:WHEN TEST-VALUE-000
        (CL:SETQ TEST-VALUE-000 (<= (LENGTH ARGS) 3))
        (CL:WHEN TEST-VALUE-000
         (CL:LET* ((ALWAYS?-000 CL:T))
          (CL:LET* ((ARG NULL) (ITER-000 ARGS))
           (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
            (CL:SETQ ARG (%%VALUE ITER-000))
            (CL:WHEN (CL:NOT (CONS? ARG)) (CL:SETQ ALWAYS?-000 CL:NIL)
             (CL:RETURN))
            (CL:SETQ ITER-000 (%%REST ITER-000))))
          (CL:SETQ TEST-VALUE-000 ALWAYS?-000))))
       (CL:WHEN (CL:NOT TEST-VALUE-000)
        (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
         (CL:LET* ((*PRINTREADABLY?* CL:T))
          (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
          (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001)
           "PARSING ERROR: SQL-join: illegal pattern arguments: `"
           ARGUMENTS "'." EOL)
          (HELP-SIGNAL-PROPOSITION-ERROR STREAM-001 KWD-RDBMS-ERROR))
         (CL:ERROR
          (NEW-PARSING-ERROR (THE-STRING-READER STREAM-001))))))
      (CL:COND
       ((CL:= (LENGTH ARGS) 3)
        (CL:LET*
         ((OUTARG NULL) (ITER-001 (%%VALUE ARGS)) (COLUMN NULL)
          (ITER-002 (%COLUMN-LIST TABLEINFO)))
         (CL:LOOP WHILE
          (CL:AND (CL:NOT (CL:EQ ITER-001 NIL))
           (CL:NOT (CL:EQ ITER-002 NIL)))
          DO (CL:SETQ OUTARG (%%VALUE ITER-001))
          (CL:SETQ COLUMN (%%VALUE ITER-002))
          (CL:SETF (%COLUMN-NAME COLUMN) (COERCE-TO-STRING OUTARG))
          (INSERT-AT (%COLUMN-INDEX TABLEINFO)
           (WRAP-STRING (%COLUMN-NAME COLUMN)) COLUMN)
          (CL:SETQ ITER-001 (%%REST ITER-001))
          (CL:SETQ ITER-002 (%%REST ITER-002))))
        (CL:SETQ ARGS (%%REST ARGS)))
       (CL:T
        (CL:LET* ((COLUMN NULL) (ITER-003 (%COLUMN-LIST TABLEINFO)))
         (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-003 NIL)) DO
          (CL:SETQ COLUMN (%%VALUE ITER-003))
          (CL:WHEN (CL:EQ (%COLUMN-NAME COLUMN) STELLA::NULL-STRING)
           (CL:LET* ((STREAM-002 (NEW-OUTPUT-STRING-STREAM)))
            (CL:LET* ((*PRINTREADABLY?* CL:T))
             (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
             (%%PRINT-STREAM (%NATIVE-STREAM STREAM-002)
              "PARSING ERROR: SQL-join: missing output argument/column specifications for: `"
              (%RELATION (%TABLE-INFO COLUMN)) "'." EOL)
             (HELP-SIGNAL-PROPOSITION-ERROR STREAM-002
              KWD-RDBMS-ERROR))
            (CL:ERROR
             (NEW-PARSING-ERROR (THE-STRING-READER STREAM-002)))))
          (CL:SETQ ITER-003 (%%REST ITER-003))))))
      (CL:LET*
       ((TABLE NULL) (ITER-004 (%%VALUE ARGS)) (COLLECT-000 NULL))
       (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-004 NIL)) DO
        (CL:SETQ TABLE (%%VALUE ITER-004))
        (CL:IF (CL:EQ COLLECT-000 NULL)
         (CL:PROGN
          (CL:SETQ COLLECT-000
           (CONS
            (CL:IF (CONS? TABLE)
             (CONS (WRAP-STRING (COERCE-TO-STRING (%%VALUE TABLE)))
              (CONS
               (WRAP-STRING
                (COERCE-TO-STRING (%%VALUE (%%REST TABLE))))
               NIL))
             (WRAP-STRING (COERCE-TO-STRING TABLE)))
            NIL))
          (CL:IF (CL:EQ TABLES NIL) (CL:SETQ TABLES COLLECT-000)
           (ADD-CONS-TO-END-OF-CONS-LIST TABLES COLLECT-000)))
         (CL:PROGN
          (CL:SETF (%%REST COLLECT-000)
           (CONS
            (CL:IF (CONS? TABLE)
             (CONS (WRAP-STRING (COERCE-TO-STRING (%%VALUE TABLE)))
              (CONS
               (WRAP-STRING
                (COERCE-TO-STRING (%%VALUE (%%REST TABLE))))
               NIL))
             (WRAP-STRING (COERCE-TO-STRING TABLE)))
            NIL))
          (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
        (CL:SETQ ITER-004 (%%REST ITER-004))))
      (CL:LET*
       ((PAIR NULL) (ITER-005 (%%VALUE (%%REST ARGS)))
        (COLLECT-001 NULL))
       (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-005 NIL)) DO
        (CL:SETQ PAIR (%%VALUE ITER-005))
        (CL:WHEN (CL:NOT (CONS? PAIR))
         (CL:LET* ((STREAM-003 (NEW-OUTPUT-STRING-STREAM)))
          (CL:LET* ((*PRINTREADABLY?* CL:T))
           (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
           (%%PRINT-STREAM (%NATIVE-STREAM STREAM-003)
            "PARSING ERROR: SQL-join: illegal pattern arguments: `"
            ARGUMENTS "'." EOL)
           (HELP-SIGNAL-PROPOSITION-ERROR STREAM-003 KWD-RDBMS-ERROR))
          (CL:ERROR
           (NEW-PARSING-ERROR (THE-STRING-READER STREAM-003)))))
        (CL:SETQ PAIR
         (CONS-LIST (WRAP-STRING (COERCE-TO-STRING (%%VALUE PAIR)))
          (WRAP-STRING (COERCE-TO-STRING (%%VALUE (%%REST PAIR))))))
        (CL:IF (CL:EQ COLLECT-001 NULL)
         (CL:PROGN (CL:SETQ COLLECT-001 (CONS PAIR NIL))
          (CL:IF (CL:EQ JOINARGS NIL) (CL:SETQ JOINARGS COLLECT-001)
           (ADD-CONS-TO-END-OF-CONS-LIST JOINARGS COLLECT-001)))
         (CL:PROGN (CL:SETF (%%REST COLLECT-001) (CONS PAIR NIL))
          (CL:SETQ COLLECT-001 (%%REST COLLECT-001))))
        (CL:SETQ ITER-005 (%%REST ITER-005))))))
    (CL:T
     (CL:LET* ((STREAM-004 (NEW-OUTPUT-STRING-STREAM)))
      (CL:LET* ((*PRINTREADABLY?* CL:T))
       (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
       (%%PRINT-STREAM (%NATIVE-STREAM STREAM-004)
        "PARSING ERROR: SQL-join: illegal pattern arguments: `"
        ARGUMENTS "'." EOL)
       (HELP-SIGNAL-PROPOSITION-ERROR STREAM-004 KWD-RDBMS-ERROR))
      (CL:ERROR (NEW-PARSING-ERROR (THE-STRING-READER STREAM-004))))))
   (CL:SETF (%ADJUNCT TABLEINFO) (CONS-LIST TABLES JOINARGS))
   (CL:VALUES TABLES JOINARGS)))

;;; (DEFUN (HELP-MEMOIZE-SQL-JOIN (ITERATOR OF CONS)) ...)

(CL:DEFUN HELP-MEMOIZE-SQL-JOIN (PROPOSITION DATABASE ARGUMENTS)
  (CL:LET*
   ((RELATION (GET-DESCRIPTION (%OPERATOR PROPOSITION)))
    (TABLEINFO (GET-RELATION-TABLE-INFO RELATION)) (TABLES NIL)
    (JOINARGS NIL) (SQL (NEW-OUTPUT-STRING-STREAM)))
   (CL:MULTIPLE-VALUE-SETQ (TABLES JOINARGS)
    (NORMALIZE-SQL-JOIN-ARGUMENTS TABLEINFO ARGUMENTS))
   (%%PRINT-STREAM (%NATIVE-STREAM SQL) "SELECT DISTINCT ")
   (CL:LET*
    ((COLUMN NULL) (ITER-000 (%COLUMN-LIST TABLEINFO)) (I NULL-INTEGER)
     (ITER-001 1))
    (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-001))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ COLUMN (%%VALUE ITER-000)) (CL:SETQ I ITER-001)
     (CL:WHEN (CL:> I 1) (%%PRINT-STREAM (%NATIVE-STREAM SQL) ", "))
     (%%PRINT-STREAM (%NATIVE-STREAM SQL) (%COLUMN-NAME COLUMN))
     (CL:SETQ ITER-000 (%%REST ITER-000))
     (CL:SETQ ITER-001 (CL:1+ ITER-001))))
   (%%PRINT-STREAM (%NATIVE-STREAM SQL) " FROM ")
   (CL:LET*
    ((TABLE NULL) (ITER-002 TABLES) (I NULL-INTEGER) (ITER-003 1))
    (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-003))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-002 NIL)) DO
     (CL:SETQ TABLE (%%VALUE ITER-002)) (CL:SETQ I ITER-003)
     (CL:WHEN (CL:> I 1) (%%PRINT-STREAM (%NATIVE-STREAM SQL) ", "))
     (CL:IF (CONS? TABLE)
      (%%PRINT-STREAM (%NATIVE-STREAM SQL)
       (UNWRAP-STRING (%%VALUE TABLE)) " "
       (UNWRAP-STRING (%%VALUE (%%REST TABLE))))
      (%%PRINT-STREAM (%NATIVE-STREAM SQL) (UNWRAP-STRING TABLE)))
     (CL:SETQ ITER-002 (%%REST ITER-002))
     (CL:SETQ ITER-003 (CL:1+ ITER-003))))
   (%%PRINT-STREAM (%NATIVE-STREAM SQL) " WHERE ")
   (CL:LET*
    ((PAIR NULL) (ITER-004 JOINARGS) (I NULL-INTEGER) (ITER-005 1))
    (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-005))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-004 NIL)) DO
     (CL:SETQ PAIR (%%VALUE ITER-004)) (CL:SETQ I ITER-005)
     (CL:WHEN (CL:> I 1) (%%PRINT-STREAM (%NATIVE-STREAM SQL) " AND "))
     (%%PRINT-STREAM (%NATIVE-STREAM SQL)
      (UNWRAP-STRING (%%VALUE PAIR)) "="
      (UNWRAP-STRING (%%VALUE (%%REST PAIR))))
     (CL:SETQ ITER-004 (%%REST ITER-004))
     (CL:SETQ ITER-005 (CL:1+ ITER-005))))
   (CL:LET*
    ((ARG NULL) (VECTOR-000 (%ARGUMENTS PROPOSITION)) (INDEX-000 0)
     (LENGTH-000 (LENGTH VECTOR-000)) (COLUMN NULL)
     (ITER-006 (%COLUMN-LIST TABLEINFO)))
    (CL:DECLARE (CL:TYPE CL:FIXNUM INDEX-000 LENGTH-000))
    (CL:LOOP WHILE
     (CL:AND (CL:< INDEX-000 LENGTH-000) (CL:NOT (CL:EQ ITER-006 NIL)))
     DO
     (CL:SETQ ARG
      (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY VECTOR-000))
       INDEX-000))
     (CL:SETQ COLUMN (%%VALUE ITER-006))
     (CL:SETQ ARG (SAFE-ARGUMENT-BOUND-TO ARG))
     (CL:WHEN (CL:NOT (CL:EQ ARG NULL))
      (%%PRINT-STREAM (%NATIVE-STREAM SQL) " AND ")
      (PRINT-ARGUMENT-CONSTRAINT SQL ARG COLUMN))
     (CL:SETQ INDEX-000 (CL:1+ INDEX-000))
     (CL:SETQ ITER-006 (%%REST ITER-006))))
   (ALLOCATE-RESULT-SET-ITERATOR
    (GET-CONNECTION-FROM-DATABASE DATABASE) RELATION
    (THE-STRING-READER SQL))))

;;; (DEFUN (SQL-JOIN (ITERATOR OF CONS)) ...)

(CL:DEFUN SQL-JOIN (PROPOSITION DATABASE ARGUMENTS)
  (CHECK-FOR-EXTERNAL-DB-UPDATES PROPOSITION DATABASE)
  (CL:LET*
   ((MEMO-TABLE-000 NULL) (MEMOIZED-ENTRY-000 NULL)
    (MEMOIZED-VALUE-000 NULL))
   (CL:WHEN *MEMOIZATION-ENABLED?*
    (CL:SETQ MEMO-TABLE-000
     (%SURROGATE-VALUE SGT-RDBMS-RDBMS-F-SQL-JOIN-MEMO-TABLE-000))
    (CL:WHEN (CL:EQ MEMO-TABLE-000 NULL)
     (INITIALIZE-MEMOIZATION-TABLE
      SGT-RDBMS-RDBMS-F-SQL-JOIN-MEMO-TABLE-000
      "(:MAX-VALUES 100 :TIMESTAMPS (:META-KB-UPDATE :EXTERNAL-DB-UPDATE))")
     (CL:SETQ MEMO-TABLE-000
      (%SURROGATE-VALUE SGT-RDBMS-RDBMS-F-SQL-JOIN-MEMO-TABLE-000)))
    (CL:SETQ MEMOIZED-ENTRY-000
     (LOOKUP-MRU-MEMOIZED-VALUE MEMO-TABLE-000
      (GET-QUERY-PATTERN-MEMOIZATION-KEY PROPOSITION) *CONTEXT*
      (CL:IF *REVERSEPOLARITY?* TRUE-WRAPPER FALSE-WRAPPER)
      MEMOIZED-NULL-VALUE 6))
    (CL:SETQ MEMOIZED-VALUE-000 (%%VALUE MEMOIZED-ENTRY-000)))
   (CL:COND
    ((CL:NOT (CL:EQ MEMOIZED-VALUE-000 NULL))
     (CL:WHEN (CL:EQ MEMOIZED-VALUE-000 MEMOIZED-NULL-VALUE)
      (CL:SETQ MEMOIZED-VALUE-000 NULL)))
    (CL:T
     (CL:SETQ MEMOIZED-VALUE-000
      (NEW-MEMOIZABLE-ITERATOR
       (HELP-MEMOIZE-SQL-JOIN PROPOSITION DATABASE ARGUMENTS)))
     (CL:WHEN *MEMOIZATION-ENABLED?*
      (CL:SETF (%%VALUE MEMOIZED-ENTRY-000)
       (CL:IF (CL:EQ MEMOIZED-VALUE-000 NULL) MEMOIZED-NULL-VALUE
        MEMOIZED-VALUE-000)))))
   (CL:LET* ((VALUE-000 (CLONE-MEMOIZED-ITERATOR MEMOIZED-VALUE-000)))
    VALUE-000)))

;;; (DEFUN COLLECT-VARIABLE-BINDING ...)

(CL:DEFUN COLLECT-VARIABLE-BINDING (NAME TYPE BINDING BINDINGS)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING NAME))
  #+MCL
  (CL:CHECK-TYPE NAME CL:SIMPLE-STRING)
  (CL:WHEN (CL:NOT (CL:EQ BINDING NULL))
   (CL:WHEN (CL:NOT (CL:EQ TYPE NULL))
    (CL:SETQ TYPE (GET-DESCRIPTION TYPE)))
   (CL:COND
    ((COLLECTION-VALUED-CONSTRAINT? BINDING)
     (CL:LET* ((ARGS NIL))
      (CL:LET*
       ((ELT NULL)
        (ITER-000 (COLLECTION-VALUED-CONSTRAINT-ELEMENTS BINDING))
        (COLLECT-000 NULL))
       (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
        (CL:SETQ ELT (%%VALUE ITER-000))
        (CL:IF (CL:EQ COLLECT-000 NULL)
         (CL:PROGN
          (CL:SETQ COLLECT-000
           (CONS
            (WRAP-STRING (COERCE-POWERLOOM-OBJECT-TO-STRING ELT TYPE))
            NIL))
          (CL:IF (CL:EQ ARGS NIL) (CL:SETQ ARGS COLLECT-000)
           (ADD-CONS-TO-END-OF-CONS-LIST ARGS COLLECT-000)))
         (CL:PROGN
          (CL:SETF (%%REST COLLECT-000)
           (CONS
            (WRAP-STRING (COERCE-POWERLOOM-OBJECT-TO-STRING ELT TYPE))
            NIL))
          (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
        (CL:SETQ ITER-000 (%%REST ITER-000))))
      (CL:SETQ BINDING ARGS)))
    (CL:T
     (CL:SETQ BINDING
      (WRAP-STRING (COERCE-POWERLOOM-OBJECT-TO-STRING BINDING TYPE))))))
  (INSERT-AT BINDINGS (WRAP-STRING NAME) BINDING))

;;; (DEFUN (CREATE-SQL-QUERY-FROM-PROPOSITION STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T CL:T CL:T) CL:SIMPLE-STRING)
  CREATE-SQL-QUERY-FROM-PROPOSITION))
(CL:DEFUN CREATE-SQL-QUERY-FROM-PROPOSITION (PROPOSITION DATABASE ARGUMENTS)
  (CL:SETQ DATABASE DATABASE)
  (CL:LET*
   ((RELATION (GET-DESCRIPTION (%OPERATOR PROPOSITION)))
    (TEMPLATE (%WRAPPER-VALUE ARGUMENTS))
    (BINDINGS (NEW-KEY-VALUE-LIST)) (SQL STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEMPLATE SQL))
   (CL:LET*
    ((VAR NULL)
     (ITER-000 (%THE-CONS-LIST (%IO-VARIABLE-NAMES RELATION)))
     (ARG NULL) (VECTOR-000 (%ARGUMENTS PROPOSITION)) (INDEX-000 0)
     (LENGTH-000 (LENGTH VECTOR-000)) (I NULL-INTEGER) (ITER-001 1))
    (CL:DECLARE (CL:TYPE CL:FIXNUM INDEX-000 LENGTH-000 I ITER-001))
    (CL:LOOP WHILE
     (CL:AND (CL:NOT (CL:EQ ITER-000 NIL)) (CL:< INDEX-000 LENGTH-000))
     DO (CL:SETQ VAR (%%VALUE ITER-000))
     (CL:SETQ ARG
      (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY VECTOR-000))
       INDEX-000))
     (CL:SETQ I ITER-001)
     (COLLECT-VARIABLE-BINDING (%SYMBOL-NAME VAR)
      (PLI::GET-NTH-DOMAIN RELATION I) (SAFE-ARGUMENT-BOUND-TO ARG)
      BINDINGS)
     (CL:SETQ ITER-000 (%%REST ITER-000))
     (CL:SETQ INDEX-000 (CL:1+ INDEX-000))
     (CL:SETQ ITER-001 (CL:1+ ITER-001))))
   (CL:SETQ SQL (INSTANTIATE-SQL-CMD-TEMPLATE TEMPLATE BINDINGS))
   (CL:SETQ SQL (SQL-QUERY-INSTANTIATE-CONSTRAINTS SQL BINDINGS)) SQL))

;;; (DEFUN (HELP-MEMOIZE-SQL-QUERY (ITERATOR OF CONS)) ...)

(CL:DEFUN HELP-MEMOIZE-SQL-QUERY (PROPOSITION DATABASE ARGUMENTS)
  (ALLOCATE-RESULT-SET-ITERATOR (GET-CONNECTION-FROM-DATABASE DATABASE)
   (GET-DESCRIPTION (%OPERATOR PROPOSITION))
   (CREATE-SQL-QUERY-FROM-PROPOSITION PROPOSITION DATABASE ARGUMENTS)))

;;; (DEFUN (SQL-QUERY-INSTANTIATE-CONSTRAINTS STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:SIMPLE-STRING CL:T) CL:SIMPLE-STRING)
  SQL-QUERY-INSTANTIATE-CONSTRAINTS))
(CL:DEFUN SQL-QUERY-INSTANTIATE-CONSTRAINTS (SQL BINDINGS)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SQL))
  #+MCL
  (CL:CHECK-TYPE SQL CL:SIMPLE-STRING)
  (CL:LET*
   ((START 0) (END (CL:THE CL:FIXNUM (CL:LENGTH SQL)))
    (VARIABLE STELLA::NULL-STRING) (VALUE NULL) (VARSTART 0) (VAREND 0)
    (COLSTART 0) (CONSTRAINT KWD-RDBMS-VALUE) (QUOTES "'`\"")
    (QUOTE NULL-CHARACTER) (RESULT NIL) (TRUECONDITION "1=1")
    (FALSECONDITION "0=1"))
   (CL:DECLARE (CL:TYPE CL:FIXNUM START END VARSTART VAREND COLSTART)
    (CL:TYPE CL:SIMPLE-STRING VARIABLE QUOTES TRUECONDITION
     FALSECONDITION))
   (CL:LOOP
    (CL:TAGBODY (CL:SETQ VARSTART (POSITION SQL #\? VAREND))
     (CL:WHEN (CL:= VARSTART NULL-INTEGER)
      (CL:COND
       ((CL:EQ RESULT NIL)
        (CL:RETURN-FROM SQL-QUERY-INSTANTIATE-CONSTRAINTS SQL))
       (CL:T
        (CL:SETQ RESULT
         (CONS (WRAP-STRING (SUBSEQUENCE SQL START NULL-INTEGER))
          RESULT))
        (CL:RETURN))))
     (CL:SETQ VARIABLE STELLA::NULL-STRING)
     (CL:LET*
      ((VAR NULL) (VAL NULL) (ITER-000 (%THE-KV-LIST BINDINGS)))
      (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NULL)) DO
       (CL:SETQ VAR (%KEY ITER-000)) (CL:SETQ VAL (%VALUE ITER-000))
       (CL:WHEN (STARTS-WITH? SQL (%WRAPPER-VALUE VAR) VARSTART)
        (CL:SETQ VARIABLE (%WRAPPER-VALUE VAR)) (CL:SETQ VALUE VAL)
        (CL:SETQ VAREND
         (CL:+ VARSTART (CL:THE CL:FIXNUM (CL:LENGTH VARIABLE))))
        (CL:WHEN
         (CL:OR (CL:= VAREND END)
          (CL:EQ
           (CL:AREF *CHARACTER-TYPE-TABLE*
            (CL:THE CL:FIXNUM
             (CL:CHAR-CODE
              (CL:LET ((SELF SQL) (POSITION VAREND))
               (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
                (CL:TYPE CL:FIXNUM POSITION))
               (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
                (CL:THE CL:FIXNUM POSITION))))))
           KWD-RDBMS-WHITE-SPACE)
          (MEMBER? QUOTES
           (CL:LET ((SELF SQL) (POSITION VAREND))
            (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
             (CL:TYPE CL:FIXNUM POSITION))
            (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
             (CL:THE CL:FIXNUM POSITION)))))
         (CL:RETURN)))
       (CL:SETQ ITER-000 (%REST ITER-000))))
     (CL:WHEN (CL:EQ VARIABLE STELLA::NULL-STRING)
      (CL:SETQ VAREND (CL:1+ VARSTART)) (CL:GO :CONTINUE))
     (CL:SETQ QUOTE NULL-CHARACTER)
     (CL:COND
      ((CL:EQL
        (CL:LET ((SELF SQL) (POSITION (MAX (CL:1- VARSTART) 0)))
         (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
          (CL:TYPE CL:FIXNUM POSITION))
         (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
          (CL:THE CL:FIXNUM POSITION)))
        #\=)
       (CL:SETQ COLSTART (CL:- VARSTART 2))
       (CL:SETQ CONSTRAINT KWD-RDBMS-VALUE))
      ((CL:AND
        (CL:EQL
         (CL:LET ((SELF SQL) (POSITION (MAX (CL:- VARSTART 2) 0)))
          (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
           (CL:TYPE CL:FIXNUM POSITION))
          (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
           (CL:THE CL:FIXNUM POSITION)))
         #\=)
        (MEMBER? QUOTES
         (CL:LET ((SELF SQL) (POSITION (CL:1- VARSTART)))
          (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
           (CL:TYPE CL:FIXNUM POSITION))
          (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
           (CL:THE CL:FIXNUM POSITION)))))
       (CL:SETQ COLSTART (CL:- VARSTART 3))
       (CL:SETQ CONSTRAINT KWD-RDBMS-VALUE)
       (CL:SETQ QUOTE
        (CL:LET ((SELF SQL) (POSITION (CL:1- VARSTART)))
         (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
          (CL:TYPE CL:FIXNUM POSITION))
         (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
          (CL:THE CL:FIXNUM POSITION)))))
      ((CL:OR (STARTS-WITH? SQL " IN " (MAX (CL:- VARSTART 4) 0))
        (STARTS-WITH? SQL " in " (MAX (CL:- VARSTART 4) 0)))
       (CL:SETQ COLSTART (CL:- VARSTART 5))
       (CL:SETQ CONSTRAINT KWD-RDBMS-SET))
      ((CL:AND
        (CL:OR (STARTS-WITH? SQL " IN " (MAX (CL:- VARSTART 5) 0))
         (STARTS-WITH? SQL " in " (MAX (CL:- VARSTART 5) 0)))
        (MEMBER? QUOTES
         (CL:LET ((SELF SQL) (POSITION (CL:1- VARSTART)))
          (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
           (CL:TYPE CL:FIXNUM POSITION))
          (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
           (CL:THE CL:FIXNUM POSITION)))))
       (CL:SETQ COLSTART (CL:- VARSTART 6))
       (CL:SETQ CONSTRAINT KWD-RDBMS-SET)
       (CL:SETQ QUOTE
        (CL:LET ((SELF SQL) (POSITION (CL:1- VARSTART)))
         (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
          (CL:TYPE CL:FIXNUM POSITION))
         (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
          (CL:THE CL:FIXNUM POSITION)))))
      (CL:T (CL:SETQ CONSTRAINT KWD-RDBMS-NONE) (CL:GO :CONTINUE)))
     (CL:WHEN
      (CL:AND (CL:EQ CONSTRAINT KWD-RDBMS-VALUE) (CONS? VALUE)
       (CL:NOT (CL:EQ VALUE NIL)))
      (CL:SETQ CONSTRAINT KWD-RDBMS-SET)
      (CL:SETQ RESULT
       (CONS (WRAP-STRING (SUBSEQUENCE SQL START (CL:1+ COLSTART)))
        RESULT))
      (CL:SETQ RESULT (CONS (WRAP-STRING " IN ") RESULT))
      (CL:SETQ START
       (CL:IF (DEFINED? QUOTE) (CL:1- VARSTART) VARSTART)))
     (CL:COND
      ((CL:OR (CL:EQ VALUE NULL) (CL:EQ VALUE NIL))
       (CL:LOOP
        (CL:COND ((CL:<= COLSTART 0) (CL:SETQ COLSTART 0) (CL:RETURN))
         ((CL:EQ
           (CL:AREF *CHARACTER-TYPE-TABLE*
            (CL:THE CL:FIXNUM
             (CL:CHAR-CODE
              (CL:LET ((SELF SQL) (POSITION COLSTART))
               (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
                (CL:TYPE CL:FIXNUM POSITION))
               (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
                (CL:THE CL:FIXNUM POSITION))))))
           KWD-RDBMS-WHITE-SPACE)
          (CL:SETQ COLSTART (CL:1+ COLSTART)) (CL:RETURN))
         (CL:T (CL:SETQ COLSTART (CL:1- COLSTART)))))
       (CL:WHEN (DEFINED? QUOTE) (CL:SETQ VAREND (CL:1+ VAREND)))
       (CL:SETQ RESULT
        (CONS (WRAP-STRING (SUBSEQUENCE SQL START COLSTART)) RESULT))
       (CL:SETQ RESULT
        (CONS
         (CL:IF (CL:EQ VALUE NIL) (WRAP-STRING FALSECONDITION)
          (WRAP-STRING TRUECONDITION))
         RESULT)))
      ((CL:EQ CONSTRAINT KWD-RDBMS-SET)
       (CL:WHEN (DEFINED? QUOTE) (CL:SETQ VARSTART (CL:1- VARSTART))
        (CL:SETQ VAREND (CL:1+ VAREND)))
       (CL:LET* ((SET (NEW-OUTPUT-STRING-STREAM)))
        (%%PRINT-STREAM (%NATIVE-STREAM SET) "(")
        (CL:LET*
         ((ELT NULL) (ITER-001 (CONSIFY VALUE)) (I NULL-INTEGER)
          (ITER-002 1))
         (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-002))
         (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
          (CL:SETQ ELT (%%VALUE ITER-001)) (CL:SETQ I ITER-002)
          (%%PRINT-STREAM (%NATIVE-STREAM SET)
           (CL:IF (CL:> I 1) "," ""))
          (CL:IF (DEFINED? QUOTE)
           (%%PRINT-STREAM (%NATIVE-STREAM SET) QUOTE
            (SQL-ESCAPE-STRING (%WRAPPER-VALUE ELT) QUOTE) QUOTE)
           (%%PRINT-STREAM (%NATIVE-STREAM SET) (UNWRAP-STRING ELT)))
          (CL:SETQ ITER-001 (%%REST ITER-001))
          (CL:SETQ ITER-002 (CL:1+ ITER-002))))
        (%%PRINT-STREAM (%NATIVE-STREAM SET) ")")
        (CL:SETQ RESULT
         (CONS (WRAP-STRING (SUBSEQUENCE SQL START VARSTART)) RESULT))
        (CL:SETQ RESULT
         (CONS (WRAP-STRING (THE-STRING-READER SET)) RESULT))))
      (CL:T
       (CL:SETQ RESULT
        (CONS (WRAP-STRING (SUBSEQUENCE SQL START VARSTART)) RESULT))
       (CL:SETQ RESULT
        (CONS
         (CL:IF (DEFINED? QUOTE)
          (WRAP-STRING
           (SQL-ESCAPE-STRING (%WRAPPER-VALUE VALUE) QUOTE))
          VALUE)
         RESULT))))
     (CL:SETQ START VAREND) :CONTINUE))
   (CL:LET* ((RES (NEW-OUTPUT-STRING-STREAM)))
    (CL:LET* ((PIECE NULL) (ITER-003 (REVERSE RESULT)))
     (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-003 NIL)) DO
      (CL:SETQ PIECE (%%VALUE ITER-003))
      (%%PRINT-STREAM (%NATIVE-STREAM RES) (UNWRAP-STRING PIECE))
      (CL:SETQ ITER-003 (%%REST ITER-003))))
    (THE-STRING-READER RES))))

;;; (DEFUN (SQL-QUERY (ITERATOR OF CONS)) ...)

(CL:DEFUN SQL-QUERY (PROPOSITION DATABASE ARGUMENTS)
  (CHECK-FOR-EXTERNAL-DB-UPDATES PROPOSITION DATABASE)
  (CL:LET*
   ((MEMO-TABLE-000 NULL) (MEMOIZED-ENTRY-000 NULL)
    (MEMOIZED-VALUE-000 NULL))
   (CL:WHEN *MEMOIZATION-ENABLED?*
    (CL:SETQ MEMO-TABLE-000
     (%SURROGATE-VALUE SGT-RDBMS-RDBMS-F-SQL-QUERY-MEMO-TABLE-000))
    (CL:WHEN (CL:EQ MEMO-TABLE-000 NULL)
     (INITIALIZE-MEMOIZATION-TABLE
      SGT-RDBMS-RDBMS-F-SQL-QUERY-MEMO-TABLE-000
      "(:MAX-VALUES 100 :TIMESTAMPS (:META-KB-UPDATE :EXTERNAL-DB-UPDATE))")
     (CL:SETQ MEMO-TABLE-000
      (%SURROGATE-VALUE SGT-RDBMS-RDBMS-F-SQL-QUERY-MEMO-TABLE-000)))
    (CL:SETQ MEMOIZED-ENTRY-000
     (LOOKUP-MRU-MEMOIZED-VALUE MEMO-TABLE-000
      (GET-QUERY-PATTERN-MEMOIZATION-KEY PROPOSITION) *CONTEXT*
      (CL:IF *REVERSEPOLARITY?* TRUE-WRAPPER FALSE-WRAPPER)
      MEMOIZED-NULL-VALUE 6))
    (CL:SETQ MEMOIZED-VALUE-000 (%%VALUE MEMOIZED-ENTRY-000)))
   (CL:COND
    ((CL:NOT (CL:EQ MEMOIZED-VALUE-000 NULL))
     (CL:WHEN (CL:EQ MEMOIZED-VALUE-000 MEMOIZED-NULL-VALUE)
      (CL:SETQ MEMOIZED-VALUE-000 NULL)))
    (CL:T
     (CL:SETQ MEMOIZED-VALUE-000
      (NEW-MEMOIZABLE-ITERATOR
       (HELP-MEMOIZE-SQL-QUERY PROPOSITION DATABASE ARGUMENTS)))
     (CL:WHEN *MEMOIZATION-ENABLED?*
      (CL:SETF (%%VALUE MEMOIZED-ENTRY-000)
       (CL:IF (CL:EQ MEMOIZED-VALUE-000 NULL) MEMOIZED-NULL-VALUE
        MEMOIZED-VALUE-000)))))
   (CL:LET* ((VALUE-000 (CLONE-MEMOIZED-ITERATOR MEMOIZED-VALUE-000)))
    VALUE-000)))

;;; (DEFUN (ALLOCATE-QUERY-SPECIALIST-ITERATOR (ITERATOR OF CONS)) ...)

(CL:DEFUN ALLOCATE-QUERY-SPECIALIST-ITERATOR (FRAME)
  (CL:WHEN
   (CL:EQ
    (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FRAME)
     SYM-RDBMS-STELLA-ITERATOR NULL)
    NULL)
   (CL:LET*
    ((ITERATOR NULL) (ITERATOR2 NULL)
     (PROPOSITION (%PROPOSITION FRAME))
     (RELATIONREF (%OPERATOR PROPOSITION)))
    (CL:LET*
     ((TRIPLE NULL)
      (ITER-000 (GET-QUERY-PATTERN-EVALUATORS RELATIONREF)))
     (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
      (CL:SETQ TRIPLE (%%VALUE ITER-000))
      (CL:COND
       ((CL:EQ ITERATOR NULL)
        (CL:SETQ ITERATOR
         (CL:FUNCALL (%WRAPPER-VALUE (%%VALUE TRIPLE)) PROPOSITION
          (%%VALUE (%%REST TRIPLE))
          (%%VALUE (%%REST (%%REST TRIPLE))))))
       (CL:T
        (CL:SETQ ITERATOR2
         (CL:FUNCALL (%WRAPPER-VALUE (%%VALUE TRIPLE)) PROPOSITION
          (%%VALUE (%%REST TRIPLE))
          (%%VALUE (%%REST (%%REST TRIPLE)))))
        (CL:WHEN (CL:NOT (CL:EQ ITERATOR2 NULL))
         (CL:SETQ ITERATOR (CONCATENATE ITERATOR ITERATOR2)))))
      (CL:SETQ ITER-000 (%%REST ITER-000))))
    (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FRAME)
     SYM-RDBMS-STELLA-ITERATOR ITERATOR NULL)))
  (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FRAME) SYM-RDBMS-STELLA-ITERATOR
   NULL))

;;; (DEFUN (QUERY-SPECIALIST KEYWORD) ...)

(CL:DEFUN QUERY-SPECIALIST (FRAME LASTMOVE)
  (CL:WHEN
   (CL:EQ
    (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FRAME)
     SYM-RDBMS-STELLA-ITERATOR NULL)
    NULL)
   (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FRAME)
    SYM-RDBMS-STELLA-ITERATOR
    (ALLOCATE-QUERY-SPECIALIST-ITERATOR FRAME) NULL))
  (RETRIEVE-NEXT-DB-QUERY-SOLUTION FRAME LASTMOVE))

;;; (DEFUN (COLLECT-QUERY-DATABASE-SPECIALIST-BINDINGS (KEY-VALUE-LIST OF STRING-WRAPPER OBJECT)) ...)

(CL:DEFUN COLLECT-QUERY-DATABASE-SPECIALIST-BINDINGS (FRAME FIRSTARGINDEX)
  (CL:DECLARE (CL:TYPE CL:FIXNUM FIRSTARGINDEX))
  #+MCL
  (CL:CHECK-TYPE FIRSTARGINDEX CL:FIXNUM)
  (CL:LET*
   ((ARGUMENTS (%ARGUMENTS (%PROPOSITION FRAME)))
    (BINDINGS (NEW-KEY-VALUE-LIST)))
   (CL:LET*
    ((ARG NULL) (VECTOR-000 ARGUMENTS) (INDEX-000 0)
     (LENGTH-000 (LENGTH VECTOR-000)) (I NULL-INTEGER) (ITER-000 0))
    (CL:DECLARE (CL:TYPE CL:FIXNUM INDEX-000 LENGTH-000 I ITER-000))
    (CL:LOOP WHILE (CL:< INDEX-000 LENGTH-000) DO
     (CL:SETQ ARG
      (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY VECTOR-000))
       INDEX-000))
     (CL:SETQ I ITER-000)
     (CL:WHEN (CL:AND (CL:>= I FIRSTARGINDEX) (VARIABLE? ARG))
      (COLLECT-VARIABLE-BINDING (%SYMBOL-NAME (%SKOLEM-NAME ARG))
       (LOGICAL-TYPE ARG) (ARGUMENT-BOUND-TO ARG) BINDINGS))
     (CL:SETQ INDEX-000 (CL:1+ INDEX-000))
     (CL:SETQ ITER-000 (CL:1+ ITER-000))))
   BINDINGS))

;;; (DEFUN (BIND-NEXT-DATABASE-TUPLE-TO-ARGUMENTS KEYWORD) ...)

(CL:DEFUN BIND-NEXT-DATABASE-TUPLE-TO-ARGUMENTS (FRAME FIRSTARGINDEX)
  (CL:DECLARE (CL:TYPE CL:FIXNUM FIRSTARGINDEX))
  #+MCL
  (CL:CHECK-TYPE FIRSTARGINDEX CL:FIXNUM)
  (CL:LET*
   ((ARGUMENTS (%ARGUMENTS (%PROPOSITION FRAME)))
    (NOFOUTPUTS (CL:- (LENGTH ARGUMENTS) FIRSTARGINDEX))
    (ITERATOR
     (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FRAME)
      SYM-RDBMS-STELLA-ITERATOR NULL))
    (PATTERNRECORD (%CURRENT-PATTERN-RECORD *QUERYITERATOR*))
    (UBSTACKOFFSET (%TOP-UNBINDING-STACK-OFFSET PATTERNRECORD))
    (CHECKEDUNBOUNDOUTPUTS? CL:NIL))
   (CL:DECLARE (CL:TYPE CL:FIXNUM NOFOUTPUTS UBSTACKOFFSET))
   (CL:LOOP WHILE (NEXT? ITERATOR) DO
    (CL:LET* ((ALWAYS?-000 CL:T))
     (CL:LET*
      ((OUTPUT NULL) (ITER-000 (%VALUE ITERATOR)) (I NULL-INTEGER)
       (ITER-001 FIRSTARGINDEX)
       (UPPER-BOUND-000 (CL:1- (LENGTH ARGUMENTS))))
      (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-001 UPPER-BOUND-000))
      (CL:LOOP WHILE
       (CL:AND (CL:NOT (CL:EQ ITER-000 NIL))
        (CL:<= ITER-001 UPPER-BOUND-000))
       DO (CL:SETQ OUTPUT (%%VALUE ITER-000)) (CL:SETQ I ITER-001)
       (CL:WHEN
        (CL:NOT
         (COLLECTION-VALUED-CONSTRAINT?
          (ARGUMENT-BOUND-TO
           (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY ARGUMENTS))
            I))))
        (CL:WHEN
         (CL:NOT
          (BIND-ARGUMENT-TO-VALUE?
           (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY ARGUMENTS)) I)
           (COERCE-STRING-TO-POWERLOOM-OBJECT (UNWRAP-STRING OUTPUT)
            (GET-DESCRIPTION
             (LOGICAL-TYPE
              (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY ARGUMENTS))
               I)))
            *MODULE* CL:NIL)
           CL:T))
         (CL:SETQ ALWAYS?-000 CL:NIL) (CL:RETURN)))
       (CL:SETQ ITER-000 (%%REST ITER-000))
       (CL:SETQ ITER-001 (CL:1+ ITER-001))))
     (CL:WHEN ALWAYS?-000
      (CL:WHEN
       (CL:AND (CL:NOT CHECKEDUNBOUNDOUTPUTS?)
        (CL:< (LENGTH (%VALUE ITERATOR)) NOFOUTPUTS))
       (CL:LET*
        ((I NULL-INTEGER)
         (ITER-002 (CL:+ (LENGTH (%VALUE ITERATOR)) FIRSTARGINDEX))
         (UPPER-BOUND-001 (CL:1- (LENGTH ARGUMENTS))))
        (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-002 UPPER-BOUND-001))
        (CL:LOOP WHILE (CL:<= ITER-002 UPPER-BOUND-001) DO
         (CL:SETQ I ITER-002)
         (CL:WHEN
          (CL:EQ
           (ARGUMENT-BOUND-TO
            (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY ARGUMENTS))
             I))
           NULL)
          (CL:RETURN-FROM BIND-NEXT-DATABASE-TUPLE-TO-ARGUMENTS
           KWD-RDBMS-TERMINAL-FAILURE))
         (CL:SETQ ITER-002 (CL:1+ ITER-002)))))
      (CL:SETQ CHECKEDUNBOUNDOUTPUTS? CL:T)
      (CL:RETURN-FROM BIND-NEXT-DATABASE-TUPLE-TO-ARGUMENTS
       KWD-RDBMS-CONTINUING-SUCCESS)))
    (UNBIND-VARIABLES-BEGINNING-AT PATTERNRECORD
     (CL:1+ UBSTACKOFFSET)))
   KWD-RDBMS-TERMINAL-FAILURE))

;;; (DEFUN (QUERY-SQL-DATABASE-SPECIALIST KEYWORD) ...)

(CL:DEFUN QUERY-SQL-DATABASE-SPECIALIST (FRAME LASTMOVE)
  (CL:SETQ LASTMOVE LASTMOVE)
  (CL:LET*
   ((ARGUMENTS (%ARGUMENTS (%PROPOSITION FRAME)))
    (DATABASE
     (ARGUMENT-BOUND-TO
      (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY ARGUMENTS)) 0)))
    (QUERY
     (ARGUMENT-BOUND-TO
      (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY ARGUMENTS)) 1))))
   (CL:WHEN
    (CL:OR (CL:EQ DATABASE NULL) (CL:NOT (STRING? QUERY))
     (CL:NOT (TEST-ISA? DATABASE SGT-RDBMS-RDBMS-SQL-DATABASE)))
    (CL:RETURN-FROM QUERY-SQL-DATABASE-SPECIALIST
     KWD-RDBMS-TERMINAL-FAILURE))
   (CL:WHEN
    (CL:EQ
     (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FRAME)
      SYM-RDBMS-STELLA-ITERATOR NULL)
     NULL)
    (CL:LET*
     ((BINDINGS (COLLECT-QUERY-DATABASE-SPECIALIST-BINDINGS FRAME 2)))
     (CL:SETQ QUERY
      (WRAP-STRING
       (INSTANTIATE-SQL-CMD-TEMPLATE (%WRAPPER-VALUE QUERY) BINDINGS)))
     (CL:SETQ QUERY
      (WRAP-STRING
       (SQL-QUERY-INSTANTIATE-CONSTRAINTS (%WRAPPER-VALUE QUERY)
        BINDINGS)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FRAME)
      SYM-RDBMS-STELLA-ITERATOR
      (GET-RESULT-SET (GET-CONNECTION-FROM-DATABASE DATABASE)
       (%WRAPPER-VALUE QUERY))
      NULL)))
   (BIND-NEXT-DATABASE-TUPLE-TO-ARGUMENTS FRAME 2)))

;;; (DEFUN (QUERY-DATABASE-SPECIALIST KEYWORD) ...)

(CL:DEFUN QUERY-DATABASE-SPECIALIST (FRAME LASTMOVE)
  (CL:LET*
   ((PROPOSITION (%PROPOSITION FRAME))
    (ARGUMENTS (%ARGUMENTS PROPOSITION))
    (DATABASE
     (ARGUMENT-BOUND-TO
      (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY ARGUMENTS)) 0)))
    (QUERY
     (ARGUMENT-BOUND-TO
      (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY ARGUMENTS)) 1))))
   (CL:WHEN (CL:OR (CL:EQ DATABASE NULL) (CL:NOT (STRING? QUERY)))
    (CL:RETURN-FROM QUERY-DATABASE-SPECIALIST
     KWD-RDBMS-TERMINAL-FAILURE))
   (CL:IF (TEST-ISA? DATABASE SGT-RDBMS-RDBMS-SQL-DATABASE)
    (QUERY-SQL-DATABASE-SPECIALIST FRAME LASTMOVE) KWD-RDBMS-FAILURE)))

;;; (DEFUN DB-UPDATE-DEMON ...)

(CL:DEFUN DB-UPDATE-DEMON (DBPROPOSITION)
  (CL:LET*
   ((DB
     (CL:AREF
      (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY (%ARGUMENTS DBPROPOSITION)))
      0)))
   (DISCONNECT-FROM-DATABASE DB)
   (BUMP-MEMOIZATION-TIMESTAMP KWD-RDBMS-EXTERNAL-DB-UPDATE)))

;;; (DEFUN CHECK-FOR-EXTERNAL-DB-UPDATES ...)

(CL:DEFUN CHECK-FOR-EXTERNAL-DB-UPDATES (PROPOSITION DATABASE)
  (CL:PROGN (CL:SETQ PROPOSITION PROPOSITION)
   (CL:SETQ DATABASE DATABASE)))

;;; (DEFUN (GET-QUERY-PATTERN-MEMOIZATION-KEY OBJECT) ...)

(CL:DEFUN GET-QUERY-PATTERN-MEMOIZATION-KEY (PROPOSITION)
  (CL:LET*
   ((RELATIONREF (%OPERATOR PROPOSITION))
    (IOVARS (%IO-VARIABLES (GET-DESCRIPTION RELATIONREF)))
    (UNBOUNDVARS (LIST)) (KEY (NEW-OUTPUT-STRING-STREAM)))
   (PRINT-LOGICAL-FORM RELATIONREF KEY)
   (CL:LET*
    ((ARG NULL) (VECTOR-000 (%ARGUMENTS PROPOSITION)) (INDEX-000 0)
     (LENGTH-000 (LENGTH VECTOR-000)))
    (CL:DECLARE (CL:TYPE CL:FIXNUM INDEX-000 LENGTH-000))
    (CL:LOOP WHILE (CL:< INDEX-000 LENGTH-000) DO
     (CL:SETQ ARG
      (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY VECTOR-000))
       INDEX-000))
     (%%PRINT-STREAM (%NATIVE-STREAM KEY) " ")
     (CL:COND
      ((CL:AND (VARIABLE? ARG)
        (CL:EQ (SAFE-ARGUMENT-BOUND-TO ARG) NULL))
       (CL:WHEN (CL:NOT (MEMBER? UNBOUNDVARS ARG))
        (INSERT-LAST UNBOUNDVARS ARG))
       (PRINT-LOGICAL-FORM
        (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY IOVARS))
         (CL:THE CL:FIXNUM (POSITION UNBOUNDVARS ARG 0)))
        KEY))
      (CL:T (PRINT-LOGICAL-FORM (SAFE-ARGUMENT-BOUND-TO ARG) KEY)))
     (CL:SETQ INDEX-000 (CL:1+ INDEX-000))))
   (WRAP-STRING (THE-STRING-READER KEY))))

;;; (DEFUN (COERCE-VALUES (CONS OF OBJECT)) ...)

(CL:DEFUN COERCE-VALUES (VALUES TABLE)
  (CL:LET* ((RESULT NIL) (MODULE NULL) (LOCAL? CL:NIL))
   (CL:LET*
    ((VALUE NULL) (ITER-000 VALUES) (COLUMN NULL)
     (ITER-001 (%COLUMN-LIST TABLE)) (COLLECT-000 NULL))
    (CL:LOOP WHILE
     (CL:AND (CL:NOT (CL:EQ ITER-000 NIL))
      (CL:NOT (CL:EQ ITER-001 NIL)))
     DO (CL:SETQ VALUE (%%VALUE ITER-000))
     (CL:SETQ COLUMN (%%VALUE ITER-001))
     (CL:SETQ MODULE (%MODULE COLUMN))
     (CL:SETQ LOCAL? (%MODULE-LOCAL? COLUMN))
     (CL:WHEN (CL:EQ MODULE NULL)
      (CL:SETQ MODULE (GET-MODULE-USING-REFERENCE COLUMN VALUES)))
     (CL:IF (CL:EQ COLLECT-000 NULL)
      (CL:PROGN
       (CL:SETQ COLLECT-000
        (CONS
         (COERCE-STRING-TO-POWERLOOM-OBJECT (UNWRAP-STRING VALUE)
          (%COLUMN-TYPE COLUMN) MODULE LOCAL?)
         NIL))
       (CL:IF (CL:EQ RESULT NIL) (CL:SETQ RESULT COLLECT-000)
        (ADD-CONS-TO-END-OF-CONS-LIST RESULT COLLECT-000)))
      (CL:PROGN
       (CL:SETF (%%REST COLLECT-000)
        (CONS
         (COERCE-STRING-TO-POWERLOOM-OBJECT (UNWRAP-STRING VALUE)
          (%COLUMN-TYPE COLUMN) MODULE LOCAL?)
         NIL))
       (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
     (CL:SETQ ITER-000 (%%REST ITER-000))
     (CL:SETQ ITER-001 (%%REST ITER-001))))
   RESULT))

;;; (DEFUN (COERCE-STRING-TO-POWERLOOM-OBJECT OBJECT) ...)

(CL:DEFUN COERCE-STRING-TO-POWERLOOM-OBJECT (VALUE TYPE MODULE LOCAL?)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING VALUE))
  #+MCL
  (CL:CHECK-TYPE VALUE CL:SIMPLE-STRING)
  (CL:WHEN (CL:EQ VALUE STELLA::NULL-STRING)
   (CL:RETURN-FROM COERCE-STRING-TO-POWERLOOM-OBJECT NULL))
  (CL:LET*
   ((TYPESURROGATE (OBJECT-SURROGATE TYPE))
    (TYPENAME (%SYMBOL-NAME TYPESURROGATE)) (RESULT NULL))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TYPENAME))
   (CL:COND
    ((CL:EQ TYPESURROGATE SGT-RDBMS-STELLA-STRING)
     (CL:SETQ RESULT (WRAP-STRING VALUE)))
    ((STRING-EQL? TYPENAME "KEYWORD")
     (CL:SETQ RESULT (INTERN-KEYWORD VALUE)))
    ((STRING-EQL? TYPENAME "SEXP")
     (CL:SETQ RESULT (READ-S-EXPRESSION-FROM-STRING VALUE)))
    ((ISA? (%SURROGATE-VALUE TYPESURROGATE)
      SGT-RDBMS-LOGIC-NAMED-DESCRIPTION)
     (CL:SETQ RESULT
      (FIND-OR-CREATE-INSTANCE VALUE TYPE MODULE LOCAL?))
     (CL:LET* ((*MODULE* MODULE) (*CONTEXT* *MODULE*))
      (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
      (ASSERT-ISA-PROPOSITION RESULT TYPESURROGATE)))
    ((SUBTYPE-OF? TYPESURROGATE SGT-RDBMS-STELLA-BOOLEAN)
     (CL:SETQ RESULT
      (CL:IF (STRING-EQL? VALUE "1")
       (%SURROGATE-VALUE SGT-RDBMS-STELLA-TRUE)
       (%SURROGATE-VALUE SGT-RDBMS-STELLA-FALSE))))
    ((SUBTYPE-OF? TYPESURROGATE SGT-RDBMS-STELLA-INTEGER)
     (CL:SETQ RESULT (WRAP-INTEGER (NUMBER-STRING-TO-INTEGER VALUE))))
    ((SUBTYPE-OF? TYPESURROGATE SGT-RDBMS-STELLA-NUMBER)
     (CL:SETQ RESULT (WRAP-FLOAT (STRING-TO-FLOAT VALUE))))
    ((SUBTYPE-OF? TYPESURROGATE SGT-RDBMS-STELLA-THING)
     (CL:SETQ RESULT
      (FIND-OR-CREATE-INSTANCE VALUE TYPE MODULE LOCAL?)))
    (CL:T
     (CL:WARN
      "RDBMS: Don't yet know how to coerce string \"`~A'\" to type `~A'"
      VALUE TYPENAME)))
   RESULT))

;;; (DEFUN (NUMBER-STRING-TO-INTEGER INTEGER) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:SIMPLE-STRING) CL:FIXNUM)
  NUMBER-STRING-TO-INTEGER))
(CL:DEFUN NUMBER-STRING-TO-INTEGER (X)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING X))
  #+MCL
  (CL:CHECK-TYPE X CL:SIMPLE-STRING)
  (CL:HANDLER-CASE
   (CL:RETURN-FROM NUMBER-STRING-TO-INTEGER
    (CL:TRUNCATE (STRING-TO-INTEGER X)))
   (CL:CONDITION () (CL:TRUNCATE (STRING-TO-FLOAT X)))))

;;; (DEFUN (COERCE-POWERLOOM-OBJECT-TO-STRING STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T CL:T) CL:SIMPLE-STRING)
  COERCE-POWERLOOM-OBJECT-TO-STRING))
(CL:DEFUN COERCE-POWERLOOM-OBJECT-TO-STRING (OBJECT TYPE)
  (CL:SETQ TYPE TYPE)
  (CL:LET* ((*PRINTREADABLY?* CL:T))
   (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
   (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE OBJECT)))
    (CL:COND
     ((SUBTYPE-OF-STRING? TEST-VALUE-000)
      (CL:PROGN (%WRAPPER-VALUE OBJECT)))
     ((SUBTYPE-OF? TEST-VALUE-000 SGT-RDBMS-LOGIC-LOGIC-OBJECT)
      (CL:PROGN (%SYMBOL-NAME (%SURROGATE-VALUE-INVERSE OBJECT))))
     (CL:T (STRINGIFY OBJECT))))))

;;; (DEFUN (FIND-OR-CREATE-INSTANCE OBJECT) ...)

(CL:DEFUN FIND-OR-CREATE-INSTANCE (NAME TYPE MODULE LOCAL?)
  "Find an existing instance with `name' in `module' or create one with `type'
if it does not yet exist.  If `local?' do not look into any inherited modules."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING NAME))
  #+MCL
  (CL:CHECK-TYPE NAME CL:SIMPLE-STRING)
  (CL:LET*
   ((INSTANCEREF (LOOKUP-SURROGATE-IN-MODULE NAME MODULE LOCAL?))
    (VALUE
     (CL:IF (CL:NOT (CL:EQ INSTANCEREF NULL))
      (%SURROGATE-VALUE INSTANCEREF) NULL))
    (TYPEREF NULL))
   (CL:COND
    ((CL:NOT (CL:EQ VALUE NULL))
     (CL:IF (STELLA-CLASS? VALUE)
      (CL:RETURN-FROM FIND-OR-CREATE-INSTANCE
       (CLASS.GET-DESCRIPTION VALUE))
      (CL:RETURN-FROM FIND-OR-CREATE-INSTANCE VALUE)))
    ((CL:EQ INSTANCEREF NULL)
     (CL:WHEN
      (CL:NOT
       (CL:EQL
        (CL:LET ((SELF NAME) (POSITION 0))
         (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
          (CL:TYPE CL:FIXNUM POSITION))
         (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
          (CL:THE CL:FIXNUM POSITION)))
        #\())
      (CL:SETQ INSTANCEREF
       (INTERN-SURROGATE-IN-MODULE NAME MODULE LOCAL?)))))
   (CL:SETQ TYPEREF (OBJECT-SURROGATE TYPE))
   (CL:WHEN (CL:EQ TYPEREF SGT-RDBMS-STELLA-THING)
    (CL:SETQ TYPEREF NULL))
   (CL:LET* ((*MODULE* MODULE) (*CONTEXT* *MODULE*))
    (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
    (CL:IF (CL:NOT (CL:EQ INSTANCEREF NULL))
     (CREATE-LOGIC-INSTANCE INSTANCEREF TYPEREF)
     (CL:LET*
      ((SKOLEM (EVALUATE-TERM (READ-S-EXPRESSION-FROM-STRING NAME))))
      (ASSERT-ISA-PROPOSITION SKOLEM TYPEREF) SKOLEM)))))

;;; (DEFUN (CREATE-SQL-ASSERTION-FROM-PROPOSITION STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T CL:T) CL:SIMPLE-STRING)
  CREATE-SQL-ASSERTION-FROM-PROPOSITION))
(CL:DEFUN CREATE-SQL-ASSERTION-FROM-PROPOSITION (PROPOSITION MODE)
  (CL:LET*
   ((RELATION-REF (GET-PROPOSITION-BASE-OPERATOR PROPOSITION))
    (RELATION (GET-DESCRIPTION RELATION-REF))
    (ISFUNCTION? (FUNCTION? RELATION-REF))
    (TABLE-INFO (GET-RELATION-TABLE-INFO RELATION))
    (TABLE-ALIAS (%TABLE-ALIAS TABLE-INFO)) (SKOLEM-TERM NULL)
    (FUNCTION-VALUE NULL) (ARGUMENTS NULL)
    (SQL (NEW-OUTPUT-STRING-STREAM)) (FIRST? CL:T))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TABLE-ALIAS))
   (CL:SETF (%TABLE-ALIAS TABLE-INFO) STELLA::NULL-STRING)
   (CL:IF ISFUNCTION?
    (CL:PROGN
     (CL:MULTIPLE-VALUE-SETQ (SKOLEM-TERM FUNCTION-VALUE)
      (GET-SKOLEM-AND-VALUE-TERMS PROPOSITION))
     (CL:LET*
      ((ARGS (%ARGUMENTS (%DEFINING-PROPOSITION SKOLEM-TERM)))
       (ARGS-LENGTH (LENGTH ARGS)))
      (CL:DECLARE (CL:TYPE CL:FIXNUM ARGS-LENGTH))
      (CL:SETQ ARGUMENTS
       (NEW-VECTOR
        (CL:IF (CL:EQ MODE KWD-RDBMS-CLIP) (CL:1- ARGS-LENGTH)
         ARGS-LENGTH)))
      (CL:LET*
       ((I NULL-INTEGER) (ITER-000 0)
        (UPPER-BOUND-000 (CL:- ARGS-LENGTH 2)))
       (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-000 UPPER-BOUND-000))
       (CL:LOOP WHILE (CL:<= ITER-000 UPPER-BOUND-000) DO
        (CL:SETQ I ITER-000)
        (CL:LET
         ((SELF (%THE-ARRAY ARGUMENTS))
          (VALUE
           (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY ARGS)) I))
          (POSITION I))
         (CL:DECLARE (CL:TYPE CL:SIMPLE-VECTOR SELF)
          (CL:TYPE CL:FIXNUM POSITION))
         (CL:SETF (CL:AREF SELF POSITION) VALUE))
        (CL:SETQ ITER-000 (CL:1+ ITER-000))))
      (CL:WHEN (CL:NOT (CL:EQ MODE KWD-RDBMS-CLIP))
       (CL:LET
        ((SELF (%THE-ARRAY ARGUMENTS)) (VALUE FUNCTION-VALUE)
         (POSITION (CL:1- ARGS-LENGTH)))
        (CL:DECLARE (CL:TYPE CL:SIMPLE-VECTOR SELF)
         (CL:TYPE CL:FIXNUM POSITION))
        (CL:SETF (CL:AREF SELF POSITION) VALUE)))))
    (CL:SETQ ARGUMENTS (%ARGUMENTS PROPOSITION)))
   (CL:COND
    ((CL:EQ MODE KWD-RDBMS-ASSERT)
     (%%PRINT-STREAM (%NATIVE-STREAM SQL) "INSERT INTO "
      (%TABLE-NAME TABLE-INFO))
     (%%PRINT-STREAM (%NATIVE-STREAM SQL) " (")
     (PRINT-SQL-COLUMN-LIST SQL TABLE-INFO)
     (%%PRINT-STREAM (%NATIVE-STREAM SQL) ") VALUES (")
     (CL:LET*
      ((COLUMN NULL) (ITER-001 (%COLUMN-LIST TABLE-INFO)) (ARG NULL)
       (VECTOR-000 ARGUMENTS) (INDEX-000 0)
       (LENGTH-000 (LENGTH VECTOR-000)))
      (CL:DECLARE (CL:TYPE CL:FIXNUM INDEX-000 LENGTH-000))
      (CL:LOOP WHILE
       (CL:AND (CL:NOT (CL:EQ ITER-001 NIL))
        (CL:< INDEX-000 LENGTH-000))
       DO (CL:SETQ COLUMN (%%VALUE ITER-001))
       (CL:SETQ ARG
        (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY VECTOR-000))
         INDEX-000))
       (CL:COND
        ((CL:OR (CL:EQ ARG NULL) (SKOLEM? ARG))
         (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
          (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
           "Can't assert non-ground items to table from `" PROPOSITION
           "'")
          (CL:ERROR
           (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000)))))
        (FIRST? (CL:SETQ FIRST? CL:NIL))
        (CL:T (%%PRINT-STREAM (%NATIVE-STREAM SQL) ", ")))
       (PRINT-SQL-VALUE SQL ARG COLUMN)
       (CL:SETQ ITER-001 (%%REST ITER-001))
       (CL:SETQ INDEX-000 (CL:1+ INDEX-000))))
     (%%PRINT-STREAM (%NATIVE-STREAM SQL) ")"))
    ((CL:OR (CL:EQ MODE KWD-RDBMS-RETRACT) (CL:EQ MODE KWD-RDBMS-CLIP))
     (%%PRINT-STREAM (%NATIVE-STREAM SQL) "DELETE FROM "
      (%TABLE-NAME TABLE-INFO) " ")
     (PRINT-SQL-CONSTRAINT-LIST SQL TABLE-INFO ARGUMENTS))
    (CL:T
     (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001) "`" MODE
       "' is not a valid case option")
      (CL:ERROR
       (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-001))))))
   (CL:SETF (%TABLE-ALIAS TABLE-INFO) TABLE-ALIAS)
   (BUMP-MEMOIZATION-TIMESTAMP KWD-RDBMS-EXTERNAL-DB-UPDATE)
   (THE-STRING-READER SQL)))

;;; (DEFUN DB-RELATION-GOES-TRUE ...)

(CL:DEFUN DB-RELATION-GOES-TRUE (PROPOSITION)
  (CL:LET*
   ((BASE-RELATION (GET-PROPOSITION-BASE-OPERATOR PROPOSITION))
    (CONNECTION (GET-CONNECTION-FROM-PREDICATE BASE-RELATION)))
   (CL:IF
    (CL:AND *CLIPPINGENABLED?*
     (FUNCTION? (GET-DESCRIPTION BASE-RELATION)))
    (%EXECUTE-SQL CONNECTION
     (WRAP-STRING
      (CREATE-SQL-ASSERTION-FROM-PROPOSITION PROPOSITION
       KWD-RDBMS-CLIP))
     NIL)
    (%EXECUTE-SQL CONNECTION
     (WRAP-STRING
      (CREATE-SQL-ASSERTION-FROM-PROPOSITION PROPOSITION
       KWD-RDBMS-RETRACT))
     NIL))
   (%EXECUTE-SQL CONNECTION
    (WRAP-STRING
     (CREATE-SQL-ASSERTION-FROM-PROPOSITION PROPOSITION
      KWD-RDBMS-ASSERT))
    NIL)))

;;; (DEFUN DB-RELATION-GOES-UNKNOWN ...)

(CL:DEFUN DB-RELATION-GOES-UNKNOWN (PROPOSITION)
  (CL:LET*
   ((CONNECTION
     (GET-CONNECTION-FROM-PREDICATE
      (GET-PROPOSITION-BASE-OPERATOR PROPOSITION))))
   (%EXECUTE-SQL CONNECTION
    (WRAP-STRING
     (CREATE-SQL-ASSERTION-FROM-PROPOSITION PROPOSITION
      KWD-RDBMS-RETRACT))
    NIL)))

;;; (DEFUN DB-RELATION-GOES-FALSE ...)

(CL:DEFUN DB-RELATION-GOES-FALSE (PROPOSITION)
  (CL:WARN
   "RDBMS: DB relations can't be made false.  Making `~A' unknown instead."
   PROPOSITION)
  (DB-RELATION-GOES-UNKNOWN PROPOSITION))

;;; (DEFUN DB-RELATION-UPDATE-DEMON ...)

(CL:DEFUN DB-RELATION-UPDATE-DEMON (PROPOSITION UPDATE-MODE)
  (CL:COND
   ((CL:OR (CL:EQ UPDATE-MODE KWD-RDBMS-ASSERT-TRUE)
     (CL:EQ UPDATE-MODE KWD-RDBMS-PRESUME-TRUE))
    (DB-RELATION-GOES-TRUE PROPOSITION)
    (DESTROY-REDUNDANT-PROPOSITION PROPOSITION))
   ((CL:EQ UPDATE-MODE KWD-RDBMS-RETRACT-TRUE)
    (DB-RELATION-GOES-UNKNOWN PROPOSITION)
    (DESTROY-REDUNDANT-PROPOSITION PROPOSITION))
   ((CL:EQ UPDATE-MODE KWD-RDBMS-RETRACT-FALSE)
    (CL:WARN "RDBMS: DB relations can't be false.")
    (DB-RELATION-GOES-UNKNOWN PROPOSITION)
    (DESTROY-REDUNDANT-PROPOSITION PROPOSITION))
   ((CL:OR (CL:EQ UPDATE-MODE KWD-RDBMS-ASSERT-FALSE)
     (CL:EQ UPDATE-MODE KWD-RDBMS-PRESUME-FALSE))
    (DB-RELATION-GOES-FALSE PROPOSITION)
    (DESTROY-REDUNDANT-PROPOSITION PROPOSITION))
   ((CL:EQ UPDATE-MODE KWD-RDBMS-CONCEIVE))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" UPDATE-MODE
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000)))))))

(CL:DEFUN HELP-STARTUP-RDBMS1 ()
  (CL:PROGN
   (CL:SETQ SYM-RDBMS-RDBMS-DEFUNTABLE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFUNTABLE" NULL 0))
   (CL:SETQ KWD-RDBMS-COMMON-LISP
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COMMON-LISP" NULL 2))
   (CL:SETQ KWD-RDBMS-FUNCTION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "FUNCTION" NULL 2))
   (CL:SETQ SYM-RDBMS-RDBMS-RELATION-TABLE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RELATION-TABLE" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-RELATION-DATABASE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RELATION-DATABASE" NULL 0))
   (CL:SETQ SYM-RDBMS-PL-KERNEL-KB-RELATION-SPECIALIST
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RELATION-SPECIALIST"
     (GET-STELLA-MODULE "/PL-KERNEL-KB" CL:T) 0))
   (CL:SETQ SYM-RDBMS-RDBMS-DBTABLE-SPECIALIST
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DBTABLE-SPECIALIST" NULL 0))
   (CL:SETQ KWD-RDBMS-AXIOMS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "AXIOMS" NULL 2))
   (CL:SETQ SYM-RDBMS-RDBMS-DEFTABLE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFTABLE" NULL 0))
   (CL:SETQ SGT-RDBMS-STELLA-CONS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONS"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ KWD-RDBMS-ERROR
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ERROR" NULL 2))
   (CL:SETQ KWD-RDBMS-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "NAME" NULL 2))
   (CL:SETQ KWD-RDBMS-VARIABLE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "VARIABLE" NULL 2))
   (CL:SETQ KWD-RDBMS-TYPE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TYPE" NULL 2))
   (CL:SETQ KWD-RDBMS-MODULE-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MODULE-NAME" NULL 2))
   (CL:SETQ KWD-RDBMS-MODULE-REFERENCE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MODULE-REFERENCE" NULL 2))
   (CL:SETQ SYM-RDBMS-RDBMS-RELATION-COLUMN-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RELATION-COLUMN-NAME" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-RELATION-COLUMN-MODULE-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RELATION-COLUMN-MODULE-NAME" NULL
     0))
   (CL:SETQ SYM-RDBMS-RDBMS-RELATION-COLUMN-MODULE-REFERENCE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RELATION-COLUMN-MODULE-REFERENCE"
     NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-DEFDB
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFDB" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-DATABASE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DATABASE" NULL 0))
   (CL:SETQ KWD-RDBMS-CONNECTION-STRING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONNECTION-STRING" NULL 2))
   (CL:SETQ SGT-RDBMS-STELLA-STRING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "STRING"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ KWD-RDBMS-JDBC-CONNECTION-STRING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "JDBC-CONNECTION-STRING" NULL 2))
   (CL:SETQ KWD-RDBMS-ODBC-CONNECTION-STRING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ODBC-CONNECTION-STRING" NULL 2))
   (CL:SETQ KWD-RDBMS-DSN
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DSN" NULL 2))
   (CL:SETQ KWD-RDBMS-DB (INTERN-RIGID-SYMBOL-WRT-MODULE "DB" NULL 2))
   (CL:SETQ KWD-RDBMS-HOST
    (INTERN-RIGID-SYMBOL-WRT-MODULE "HOST" NULL 2))
   (CL:SETQ KWD-RDBMS-PORT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PORT" NULL 2))
   (CL:SETQ SGT-RDBMS-STELLA-INTEGER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "INTEGER"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ KWD-RDBMS-USER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "USER" NULL 2))
   (CL:SETQ KWD-RDBMS-PASSWORD
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PASSWORD" NULL 2))
   (CL:SETQ KWD-RDBMS-MODULE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MODULE" NULL 2))
   (CL:SETQ SGT-RDBMS-STELLA-MODULE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MODULE"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ KWD-RDBMS-CONFIGURATION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONFIGURATION" NULL 2))
   (CL:SETQ SGT-RDBMS-STELLA-CONFIGURATION-TABLE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONFIGURATION-TABLE"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ KWD-RDBMS-DB-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DB-NAME" NULL 2))
   (CL:SETQ SYM-RDBMS-RDBMS-ASSERT-RDBMS-CONNECTION-INFO
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ASSERT-RDBMS-CONNECTION-INFO" NULL
     0))
   (CL:SETQ SYM-RDBMS-RDBMS-DEFQUERY
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFQUERY" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-QUERY-SPECIALIST
    (INTERN-RIGID-SYMBOL-WRT-MODULE "QUERY-SPECIALIST" NULL 0))
   (CL:SETQ SGT-RDBMS-RDBMS-CONNECTION-WRAPPER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONNECTION-WRAPPER" NULL 1))
   (CL:SETQ SYM-RDBMS-STELLA-WRAPPER-VALUE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "WRAPPER-VALUE"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SGT-RDBMS-LOGIC-LOGIC-OBJECT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "LOGIC-OBJECT"
     (GET-STELLA-MODULE "/LOGIC" CL:T) 1))
   (CL:SETQ SGT-RDBMS-RDBMS-PROTOCOL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PROTOCOL" NULL 1))
   (CL:SETQ SGT-RDBMS-RDBMS-SERVER-TYPE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "SERVER-TYPE" NULL 1))
   (CL:SETQ SGT-RDBMS-RDBMS-HOST
    (INTERN-RIGID-SYMBOL-WRT-MODULE "HOST" NULL 1))
   (CL:SETQ SGT-RDBMS-RDBMS-PORT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PORT" NULL 1))
   (CL:SETQ SGT-RDBMS-RDBMS-USER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "USER" NULL 1))
   (CL:SETQ SGT-RDBMS-RDBMS-PASSWORD
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PASSWORD" NULL 1))
   (CL:SETQ SGT-RDBMS-RDBMS-DB-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DB-NAME" NULL 1))
   (CL:SETQ SGT-RDBMS-RDBMS-ODBC-CONNECTION-STRING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ODBC-CONNECTION-STRING" NULL 1))
   (CL:SETQ SGT-RDBMS-RDBMS-CONNECTION-STRING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONNECTION-STRING" NULL 1))
   (CL:SETQ SGT-RDBMS-RDBMS-DSN
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DSN" NULL 1))
   (CL:SETQ KWD-RDBMS-PROTOCOL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PROTOCOL" NULL 2))
   (CL:SETQ KWD-RDBMS-SERVER-TYPE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "SERVER-TYPE" NULL 2))
   (CL:SETQ KWD-RDBMS-EXTENSIONAL-ASSERTION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "EXTENSIONAL-ASSERTION" NULL 2))
   (CL:SETQ SGT-RDBMS-RDBMS-DB-CONNECTION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DB-CONNECTION" NULL 1))
   (CL:SETQ SGT-RDBMS-RDBMS-RELATION-DATABASE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RELATION-DATABASE" NULL 1))
   (CL:SETQ SYM-RDBMS-LOGIC-?X
    (INTERN-RIGID-SYMBOL-WRT-MODULE "?X"
     (GET-STELLA-MODULE "/LOGIC" CL:T) 0))
   (CL:SETQ SGT-RDBMS-RDBMS-RELATION-TABLE-INFO
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RELATION-TABLE-INFO" NULL 1))))

(CL:DEFUN HELP-STARTUP-RDBMS2 ()
  (CL:PROGN
   (CL:SETQ SYM-RDBMS-STELLA-RELATION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RELATION"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-RDBMS-RDBMS-DBMS-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DBMS-NAME" NULL 0))
   (CL:SETQ SYM-RDBMS-STELLA-TABLE-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TABLE-NAME"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-RDBMS-RDBMS-TABLE-ALIAS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TABLE-ALIAS" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-COLUMN-LIST
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COLUMN-LIST" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-COLUMN-VECTOR
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COLUMN-VECTOR" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-COLUMN-INDEX
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COLUMN-INDEX" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-ADJUNCT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ADJUNCT" NULL 0))
   (CL:SETQ SGT-RDBMS-RDBMS-RELATION-COLUMN-INFO
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RELATION-COLUMN-INFO" NULL 1))
   (CL:SETQ SYM-RDBMS-RDBMS-TABLE-INFO
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TABLE-INFO" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-COLUMN-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COLUMN-NAME" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-COLUMN-VARIABLE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COLUMN-VARIABLE" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-COLUMN-TYPE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COLUMN-TYPE" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-COLUMN-DB-TYPE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COLUMN-DB-TYPE" NULL 0))
   (CL:SETQ SYM-RDBMS-STELLA-MODULE-NAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MODULE-NAME"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-RDBMS-RDBMS-MODULE-REFERENCE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MODULE-REFERENCE" NULL 0))
   (CL:SETQ SYM-RDBMS-STELLA-MODULE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MODULE"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-RDBMS-RDBMS-MODULE-LOCAL?
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MODULE-LOCAL?" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-MODULE-REFERENCE-COLUMN
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MODULE-REFERENCE-COLUMN" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-COERCION-FUNCTION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COERCION-FUNCTION" NULL 0))
   (CL:SETQ KWD-RDBMS-UNKNOWN
    (INTERN-RIGID-SYMBOL-WRT-MODULE "UNKNOWN" NULL 2))
   (CL:SETQ SGT-RDBMS-RDBMS-RELATION-TABLE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RELATION-TABLE" NULL 1))
   (CL:SETQ SGT-RDBMS-RDBMS-F-GET-RELATION-TABLE-INFO-MEMO-TABLE-000
    (INTERN-RIGID-SYMBOL-WRT-MODULE
     "F-GET-RELATION-TABLE-INFO-MEMO-TABLE-000" NULL 1))
   (CL:SETQ KWD-RDBMS-STRING-CONSTANT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "STRING-CONSTANT" NULL 2))
   (CL:SETQ SGT-RDBMS-STELLA-NUMBER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "NUMBER"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SGT-RDBMS-STELLA-BOOLEAN
    (INTERN-RIGID-SYMBOL-WRT-MODULE "BOOLEAN"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ KWD-RDBMS-MYSQL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MYSQL" NULL 2))
   (CL:SETQ SGT-RDBMS-STELLA-STRING-WRAPPER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "STRING-WRAPPER"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SYM-RDBMS-STELLA-ITERATOR
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ITERATOR"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SGT-RDBMS-RDBMS-DATABASE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DATABASE" NULL 1))
   (CL:SETQ
    SGT-RDBMS-RDBMS-F-ALLOCATE-DBTABLE-SPECIALIST-ITERATOR-MEMO-TABLE-000
    (INTERN-RIGID-SYMBOL-WRT-MODULE
     "F-ALLOCATE-DBTABLE-SPECIALIST-ITERATOR-MEMO-TABLE-000" NULL 1))
   (CL:SETQ KWD-RDBMS-FAILURE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "FAILURE" NULL 2))
   (CL:SETQ KWD-RDBMS-DB-LOOKUP
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DB-LOOKUP" NULL 2))
   (CL:SETQ KWD-RDBMS-CONTINUING-SUCCESS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONTINUING-SUCCESS" NULL 2))
   (CL:SETQ KWD-RDBMS-FINAL-SUCCESS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "FINAL-SUCCESS" NULL 2))
   (CL:SETQ KWD-RDBMS-TECHNICAL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TECHNICAL" NULL 2))
   (CL:SETQ KWD-RDBMS-LAY
    (INTERN-RIGID-SYMBOL-WRT-MODULE "LAY" NULL 2))
   (CL:SETQ SYM-RDBMS-RDBMS-?REL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "?REL" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-?EV
    (INTERN-RIGID-SYMBOL-WRT-MODULE "?EV" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-?DB
    (INTERN-RIGID-SYMBOL-WRT-MODULE "?DB" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-?ARGS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "?ARGS" NULL 0))
   (CL:SETQ SYM-RDBMS-STELLA-AND
    (INTERN-RIGID-SYMBOL-WRT-MODULE "AND"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-RDBMS-RDBMS-QUERY-PATTERN
    (INTERN-RIGID-SYMBOL-WRT-MODULE "QUERY-PATTERN" NULL 0))
   (CL:SETQ SYM-RDBMS-STELLA-EXISTS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "EXISTS"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-RDBMS-RDBMS-?DB-TYPE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "?DB-TYPE" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-SUPPORTS-DB-TYPE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "SUPPORTS-DB-TYPE" NULL 0))
   (CL:SETQ SYM-RDBMS-RDBMS-INSTANCE-OF
    (INTERN-RIGID-SYMBOL-WRT-MODULE "INSTANCE-OF" NULL 0))
   (CL:SETQ KWD-RDBMS-DONT-OPTIMIZE?
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DONT-OPTIMIZE?" NULL 2))
   (CL:SETQ KWD-RDBMS-HOW-MANY
    (INTERN-RIGID-SYMBOL-WRT-MODULE "HOW-MANY" NULL 2))
   (CL:SETQ KWD-RDBMS-ALL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ALL" NULL 2))
   (CL:SETQ KWD-RDBMS-INFERENCE-LEVEL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "INFERENCE-LEVEL" NULL 2))
   (CL:SETQ KWD-RDBMS-ASSERTION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ASSERTION" NULL 2))
   (CL:SETQ SYM-RDBMS-RDBMS-F-GET-QUERY-PATTERN-EVALUATORS-QUERY-000
    (INTERN-RIGID-SYMBOL-WRT-MODULE
     "F-GET-QUERY-PATTERN-EVALUATORS-QUERY-000" NULL 0))
   (CL:SETQ
    SGT-RDBMS-RDBMS-F-GET-QUERY-PATTERN-EVALUATORS-MEMO-TABLE-000
    (INTERN-RIGID-SYMBOL-WRT-MODULE
     "F-GET-QUERY-PATTERN-EVALUATORS-MEMO-TABLE-000" NULL 1))
   (CL:SETQ SYM-RDBMS-RDBMS-F-GET-QUERY-PATTERN-EVALUATORS-QUERY-001
    (INTERN-RIGID-SYMBOL-WRT-MODULE
     "F-GET-QUERY-PATTERN-EVALUATORS-QUERY-001" NULL 0))
   (CL:SETQ SGT-RDBMS-RDBMS-F-SQL-JOIN-MEMO-TABLE-000
    (INTERN-RIGID-SYMBOL-WRT-MODULE "F-SQL-JOIN-MEMO-TABLE-000" NULL
     1))
   (CL:SETQ KWD-RDBMS-VALUE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "VALUE" NULL 2))
   (CL:SETQ KWD-RDBMS-WHITE-SPACE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "WHITE-SPACE" NULL 2))
   (CL:SETQ KWD-RDBMS-SET
    (INTERN-RIGID-SYMBOL-WRT-MODULE "SET" NULL 2))
   (CL:SETQ KWD-RDBMS-NONE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "NONE" NULL 2))))

(CL:DEFUN HELP-STARTUP-RDBMS3 ()
  (CL:PROGN
   (CL:SETQ SGT-RDBMS-RDBMS-F-SQL-QUERY-MEMO-TABLE-000
    (INTERN-RIGID-SYMBOL-WRT-MODULE "F-SQL-QUERY-MEMO-TABLE-000" NULL
     1))
   (CL:SETQ KWD-RDBMS-TERMINAL-FAILURE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TERMINAL-FAILURE" NULL 2))
   (CL:SETQ SGT-RDBMS-RDBMS-SQL-DATABASE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "SQL-DATABASE" NULL 1))
   (CL:SETQ KWD-RDBMS-EXTERNAL-DB-UPDATE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "EXTERNAL-DB-UPDATE" NULL 2))
   (CL:SETQ SGT-RDBMS-LOGIC-NAMED-DESCRIPTION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "NAMED-DESCRIPTION"
     (GET-STELLA-MODULE "/LOGIC" CL:T) 1))
   (CL:SETQ SGT-RDBMS-STELLA-TRUE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TRUE"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SGT-RDBMS-STELLA-FALSE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "FALSE"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SGT-RDBMS-STELLA-THING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "THING"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ KWD-RDBMS-CLIP
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CLIP" NULL 2))
   (CL:SETQ KWD-RDBMS-ASSERT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ASSERT" NULL 2))
   (CL:SETQ KWD-RDBMS-RETRACT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RETRACT" NULL 2))
   (CL:SETQ KWD-RDBMS-ASSERT-TRUE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ASSERT-TRUE" NULL 2))
   (CL:SETQ KWD-RDBMS-PRESUME-TRUE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PRESUME-TRUE" NULL 2))
   (CL:SETQ KWD-RDBMS-RETRACT-TRUE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RETRACT-TRUE" NULL 2))
   (CL:SETQ KWD-RDBMS-RETRACT-FALSE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RETRACT-FALSE" NULL 2))
   (CL:SETQ KWD-RDBMS-ASSERT-FALSE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ASSERT-FALSE" NULL 2))
   (CL:SETQ KWD-RDBMS-PRESUME-FALSE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PRESUME-FALSE" NULL 2))
   (CL:SETQ KWD-RDBMS-CONCEIVE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONCEIVE" NULL 2))
   (CL:SETQ SYM-RDBMS-RDBMS-STARTUP-RDBMS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-RDBMS" NULL 0))
   (CL:SETQ SYM-RDBMS-STELLA-METHOD-STARTUP-CLASSNAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))))

(CL:DEFUN HELP-STARTUP-RDBMS4 ()
  (CL:PROGN
   (DEFINE-FUNCTION-OBJECT "DEFUNTABLE"
    "(DEFUN (DEFUNTABLE LOGIC-OBJECT) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a database table and map it to a function
The accepted syntax is:
	 
 (defuntable <relconst> <dbconst> <tablename> (<columndecl>+)
    [<keyword-option>*]).

<columndecl>'s specify the names (and optionally types) of the columns
of the database table.  They have the same form as a PowerLoom <vardecl>, but
column names can be specified with or without question marks.  If there
is a question mark it will be stripped to determine the column name, otherwise
a question mark will be added to generate the relation variable.  The optional
type specifies the domain of that argument and controls any necessary coercion.
The name of each column HAS TO MATCH one of the columns of <tablename>, however,
the order is irrelevant and arbitrary projections can be defined by only
specifying some subset of <tablename>'s columns.

See `deffunction' for legal keyword options.
\")" (CL:FUNCTION %DEFUNTABLE)
    (CL:FUNCTION DEFUNTABLE-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "CALL-DEFUNTABLE"
    "(DEFUN (CALL-DEFUNTABLE NAMED-DESCRIPTION) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `deftable' command (which see).
Expects the same arguments as `deftable' but supplied as a list.\" :PUBLIC? TRUE)"
    (CL:FUNCTION CALL-DEFUNTABLE) NULL)
   (DEFINE-FUNCTION-OBJECT "DEFTABLE"
    "(DEFUN (DEFTABLE LOGIC-OBJECT) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a database table and map it to a relation.
The accepted syntax is:
	 
 (deftable <relconst> <dbconst> <tablename> (<columndecl>+)
    [<keyword-option>*]).
	
<columndecl>'s specify the names (and optionally types) of the columns
of the database table.  They have the same form as a PowerLoom <vardecl>, but
column names can be specified with or without question marks.  If there
is a question mark it will be stripped to determine the column name, otherwise
a question mark will be added to generate the relation variable.  The optional
type specifies the domain of that argument and controls any necessary coercion.
The name of each column HAS TO MATCH one of the columns of <tablename>, however,
the order is irrelevant and arbitrary projections can be defined by only
specifying some subset of <tablename>'s columns.

See `defrelation' for legal keyword options.
\")" (CL:FUNCTION %DEFTABLE) (CL:FUNCTION DEFTABLE-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "CALL-DEFTABLE"
    "(DEFUN (CALL-DEFTABLE NAMED-DESCRIPTION) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `deftable' command (which see).
Expects the same arguments as `deftable' but supplied as a list.\" :PUBLIC? TRUE)"
    (CL:FUNCTION CALL-DEFTABLE) NULL)
   (DEFINE-FUNCTION-OBJECT "PARSE-ONE-COLUMN-SPEC"
    "(DEFUN (PARSE-ONE-COLUMN-SPEC PROPERTY-LIST) ((COLUMNSPEC OBJECT)))"
    (CL:FUNCTION PARSE-ONE-COLUMN-SPEC) NULL)
   (DEFINE-FUNCTION-OBJECT "PARSE-COLUMN-SPECS"
    "(DEFUN (PARSE-COLUMN-SPECS CONS CONS) ((RELCONST OBJECT) (COLUMNSPECS OBJECT)))"
    (CL:FUNCTION PARSE-COLUMN-SPECS) NULL)
   (DEFINE-FUNCTION-OBJECT "DEFDB"
    "(DEFUN (DEFDB LOGIC-OBJECT) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a database instance.  The accepted syntax is:
	 
 (defdb <dbconst>
    [:protocol <protocol string>]
    [:server-type <server type string>]
    [:dsn <ODBC data-source name string>]
    [:odbc-connection-string <ODBC connection string>]
    [:jdbc-connection-string <JDBC connection string>]
    [:connection-string <connection string>] ;; deprecated
    [:host <server host string>]
    [:port <server host port>]
    [:user <user name string>]
    [:password <password string>]
    [:db-name <database name string>]
    [<keyword-option>*])
	
Connection information can be asserted explicitly later or be done
programmatically, as long as it is done before the first time a
connection attempt is made (e.g., during a query).  This information
is passed to `SDBC/connect' (which see for more documentation on
ways to specify a connection).  For example, for ODBC a :DSN, an
:ODBC-CONNECTION-STRING or an appropriate combination of :HOST,
:PORT, :USER, :PASSWORD AND :DB-NAME can be used.  For JDBC a
:JDBC-CONNECTION-STRING or combination of :HOST, :PORT, etc. can
be used.  See `defobject' for additional legal keyword options.
\")" (CL:FUNCTION %DEFDB) (CL:FUNCTION DEFDB-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "CALL-DEFDB"
    "(DEFUN (CALL-DEFDB LOGIC-OBJECT) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of of the `defdb' command (which see).
Expects the same arguments as `defdb' but supplied as a list.\" :PUBLIC? TRUE)"
    (CL:FUNCTION CALL-DEFDB) NULL)
   (DEFINE-FUNCTION-OBJECT "EXTRACT-RDBMS-OPTIONS"
    "(DEFUN (EXTRACT-RDBMS-OPTIONS CONS CONS) ((SELFNAME SYMBOL) (OPTIONS CONS)))"
    (CL:FUNCTION EXTRACT-RDBMS-OPTIONS) NULL)
   (DEFINE-FUNCTION-OBJECT "ASSERT-RDBMS-CONNECTION-INFO"
    "(DEFUN ASSERT-RDBMS-CONNECTION-INFO ((DB-INSTANCE-NAME STRING) |&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Assert DB connectivity information about the DB instance `db-instance-name' (for
example, \\\"edb\\\") according to `options'.  Looks up `db-instance-name' in the module
specified by the :module option (defaults to current module) and retracts any
preexisting connection information.  New assertions are also made in that module.
Default values are taken from the configuration table specified by :configuration.

Understands the following options, with default values specified by the configuration
key in parentheses:
   :connection-string (\\\"DBConnection\\\"),
   :jdbc-connection-string (\\\"JDBCString\\\"),
   :odbc-connection-string (\\\"ODBCString\\\"),
   :dsn (\\\"DSN\\\"),
   :db (\\\"DBName\\\"),
   :host (\\\"DBHost\\\"),
   :port (\\\"DBPort\\\"),
   :user (\\\"DBUser\\\"),
   :password (\\\"DBPassword\\\"),
   :module,
   :configuration.\" :COMMAND? TRUE :PUBLIC? TRUE)"
    (CL:FUNCTION %ASSERT-RDBMS-CONNECTION-INFO)
    (CL:FUNCTION ASSERT-RDBMS-CONNECTION-INFO-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "DEFQUERY"
    "(DEFUN (DEFQUERY LOGIC-OBJECT) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) an (external) query and map it to a relation.
The accepted syntax is:
	 
 (defquery <relconst> (<vardecl>+)
    {:query-pattern (<query-evaluator> <dbconst> <arguments-string>)}*
    [<keyword-option>*]).
	
<query-evaluator> has to be a `Computed-Procedure' that takes the following
three arguments: the <relconst> query proposition, the database object <dbconst>
and the arguments string.  It needs to return an iterator that generates CONS
tuples whose elements will be bound in sequence to <relconst>'s arguments.

See `defrelation' for other legal keyword options.
\")" (CL:FUNCTION %DEFQUERY) (CL:FUNCTION DEFQUERY-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "CALL-DEFQUERY"
    "(DEFUN (CALL-DEFQUERY NAMED-DESCRIPTION) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `defquery' command (which see).
Expects the same arguments as `deftable' but supplied as a list.\" :PUBLIC? TRUE)"
    (CL:FUNCTION CALL-DEFQUERY) NULL)
   (DEFINE-FUNCTION-OBJECT "NORMALIZE-CONNECTION-ARGUMENT"
    "(DEFUN (NORMALIZE-CONNECTION-ARGUMENT STRING-WRAPPER) ((ARG OBJECT)))"
    (CL:FUNCTION NORMALIZE-CONNECTION-ARGUMENT) NULL)
   (DEFINE-FUNCTION-OBJECT "CONNECT-TO-DATABASE"
    "(DEFUN (CONNECT-TO-DATABASE /SDBC/CONNECTION) ((DATABASE LOGIC-OBJECT)))"
    (CL:FUNCTION CONNECT-TO-DATABASE) NULL)
   (DEFINE-FUNCTION-OBJECT "DISCONNECT-FROM-DATABASE"
    "(DEFUN DISCONNECT-FROM-DATABASE ((DATABASE LOGIC-OBJECT)))"
    (CL:FUNCTION DISCONNECT-FROM-DATABASE) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-CONNECTION-FROM-DATABASE"
    "(DEFUN (GET-CONNECTION-FROM-DATABASE /SDBC/CONNECTION) ((DATABASE LOGIC-OBJECT)))"
    (CL:FUNCTION GET-CONNECTION-FROM-DATABASE) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-CONNECTION-FROM-PREDICATE"
    "(DEFUN (GET-CONNECTION-FROM-PREDICATE /SDBC/CONNECTION) ((RELATIONREF SURROGATE)))"
    (CL:FUNCTION GET-CONNECTION-FROM-PREDICATE) NULL)
   (DEFINE-FUNCTION-OBJECT "ALLOCATE-RESULT-SET-ITERATOR"
    "(DEFUN (ALLOCATE-RESULT-SET-ITERATOR (ITERATOR OF CONS)) ((CONNECTION /SDBC/CONNECTION) (RELATION LOGIC-OBJECT) (SQLSTATEMENT STRING)))"
    (CL:FUNCTION ALLOCATE-RESULT-SET-ITERATOR) NULL)
   (DEFINE-FUNCTION-OBJECT "RESULT-SET-ITERATOR-NEXT?"
    "(DEFUN (RESULT-SET-ITERATOR-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))"
    (CL:FUNCTION RESULT-SET-ITERATOR-NEXT?) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-TABLE-RELATION"
    "(DEFUN (GET-TABLE-RELATION NAMED-DESCRIPTION) ((TABLE-NAME STRING) (MODULE MODULE)))"
    (CL:FUNCTION GET-TABLE-RELATION) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-TABLE-COLUMN-INDEX"
    "(DEFUN (GET-TABLE-COLUMN-INDEX INTEGER) ((TABLE-RELATION NAMED-DESCRIPTION) (COLUMN-NAME STRING) (MODULE MODULE)))"
    (CL:FUNCTION GET-TABLE-COLUMN-INDEX) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-TABLE-COLUMN-MODULE-NAME"
    "(DEFUN (GET-TABLE-COLUMN-MODULE-NAME STRING-WRAPPER) ((TABLERELATION NAMED-DESCRIPTION) (COLUMNINDEX INTEGER)))"
    (CL:FUNCTION GET-TABLE-COLUMN-MODULE-NAME) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-TABLE-COLUMN-MODULE-REFERENCE"
    "(DEFUN (GET-TABLE-COLUMN-MODULE-REFERENCE STRING-WRAPPER) ((TABLERELATION NAMED-DESCRIPTION) (COLUMNINDEX INTEGER)))"
    (CL:FUNCTION GET-TABLE-COLUMN-MODULE-REFERENCE) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-TABLE-COLUMN-NAME"
    "(DEFUN (GET-TABLE-COLUMN-NAME STRING-WRAPPER) ((TABLERELATION NAMED-DESCRIPTION) (COLUMNINDEX INTEGER)))"
    (CL:FUNCTION GET-TABLE-COLUMN-NAME) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-TABLE-COLUMN-NAMES"
    "(DEFUN (GET-TABLE-COLUMN-NAMES (CONS OF STRING-WRAPPER)) ((TABLERELATION NAMED-DESCRIPTION)))"
    (CL:FUNCTION GET-TABLE-COLUMN-NAMES) NULL)
   (DEFINE-FUNCTION-OBJECT "CREATE-RELATION-TABLE-INFO"
    "(DEFUN (CREATE-RELATION-TABLE-INFO RELATION-TABLE-INFO) ((RELATION NAMED-DESCRIPTION)))"
    (CL:FUNCTION CREATE-RELATION-TABLE-INFO) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-MODULE-USING-REFERENCE"
    "(DEFUN (GET-MODULE-USING-REFERENCE MODULE) ((COLUMN RELATION-COLUMN-INFO) (VALUES CONS)))"
    (CL:FUNCTION GET-MODULE-USING-REFERENCE) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-RELATION-TABLE-INFO"
    "(DEFUN (GET-RELATION-TABLE-INFO RELATION-TABLE-INFO) ((TABLERELATION NAMED-DESCRIPTION)))"
    (CL:FUNCTION GET-RELATION-TABLE-INFO) NULL)
   (DEFINE-FUNCTION-OBJECT "COLLECTION-VALUED-CONSTRAINT?"
    "(DEFUN (COLLECTION-VALUED-CONSTRAINT? BOOLEAN) ((ARGUMENT OBJECT)))"
    (CL:FUNCTION COLLECTION-VALUED-CONSTRAINT?) NULL)
   (DEFINE-FUNCTION-OBJECT "COLLECTION-VALUED-CONSTRAINT-ELEMENTS"
    "(DEFUN (COLLECTION-VALUED-CONSTRAINT-ELEMENTS CONS) ((ARGUMENT OBJECT)))"
    (CL:FUNCTION COLLECTION-VALUED-CONSTRAINT-ELEMENTS) NULL)
   (DEFINE-FUNCTION-OBJECT "PRINT-SQL-VALUE"
    "(DEFUN PRINT-SQL-VALUE ((STREAM OUTPUT-STREAM) (VALUE OBJECT) (COLUMN RELATION-COLUMN-INFO)))"
    (CL:FUNCTION PRINT-SQL-VALUE) NULL)
   (DEFINE-FUNCTION-OBJECT "PRINT-COLUMN-CONSTRAINT"
    "(DEFUN PRINT-COLUMN-CONSTRAINT ((SQL OUTPUT-STREAM) (COLUMN RELATION-COLUMN-INFO) (VALUE STRING) (CASESENSITIVE? BOOLEAN)))"
    (CL:FUNCTION PRINT-COLUMN-CONSTRAINT) NULL)
   (DEFINE-FUNCTION-OBJECT "PRINT-ARGUMENT-CONSTRAINT"
    "(DEFUN PRINT-ARGUMENT-CONSTRAINT ((SQL OUTPUT-STREAM) (ARGUMENT OBJECT) (COLUMN RELATION-COLUMN-INFO)))"
    (CL:FUNCTION PRINT-ARGUMENT-CONSTRAINT) NULL)
   (DEFINE-FUNCTION-OBJECT "PRINT-SQL-COLUMN-LIST"
    "(DEFUN PRINT-SQL-COLUMN-LIST ((STREAM OUTPUT-STREAM) (TABLE-INFO RELATION-TABLE-INFO)))"
    (CL:FUNCTION PRINT-SQL-COLUMN-LIST) NULL)
   (DEFINE-FUNCTION-OBJECT "PRINT-SQL-CONSTRAINT-LIST"
    "(DEFUN PRINT-SQL-CONSTRAINT-LIST ((STREAM OUTPUT-STREAM) (TABLE-INFO RELATION-TABLE-INFO) (ARGUMENTS VECTOR)))"
    (CL:FUNCTION PRINT-SQL-CONSTRAINT-LIST) NULL)
   (DEFINE-FUNCTION-OBJECT "CREATE-SQL-FROM-PROPOSITION"
    "(DEFUN (CREATE-SQL-FROM-PROPOSITION STRING) ((PROPOSITION PROPOSITION)))"
    (CL:FUNCTION CREATE-SQL-FROM-PROPOSITION) NULL)
   (DEFINE-FUNCTION-OBJECT "ALLOCATE-DBTABLE-SPECIALIST-ITERATOR"
    "(DEFUN (ALLOCATE-DBTABLE-SPECIALIST-ITERATOR (ITERATOR OF CONS)) ((FRAME CONTROL-FRAME)))"
    (CL:FUNCTION ALLOCATE-DBTABLE-SPECIALIST-ITERATOR) NULL)
   (DEFINE-FUNCTION-OBJECT "RETRIEVE-NEXT-DB-QUERY-SOLUTION"
    "(DEFUN (RETRIEVE-NEXT-DB-QUERY-SOLUTION KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))"
    (CL:FUNCTION RETRIEVE-NEXT-DB-QUERY-SOLUTION) NULL)
   (DEFINE-FUNCTION-OBJECT "DBTABLE-SPECIALIST"
    "(DEFUN (DBTABLE-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))"
    (CL:FUNCTION DBTABLE-SPECIALIST) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-QUERY-PATTERN-EVALUATORS"
    "(DEFUN (GET-QUERY-PATTERN-EVALUATORS (CONS OF CONS)) ((RELATIONREF SURROGATE)))"
    (CL:FUNCTION GET-QUERY-PATTERN-EVALUATORS) NULL)
   (DEFINE-FUNCTION-OBJECT "NORMALIZE-SQL-JOIN-ARGUMENTS"
    "(DEFUN (NORMALIZE-SQL-JOIN-ARGUMENTS CONS CONS) ((TABLEINFO RELATION-TABLE-INFO) (ARGUMENTS OBJECT)))"
    (CL:FUNCTION NORMALIZE-SQL-JOIN-ARGUMENTS) NULL)
   (DEFINE-FUNCTION-OBJECT "HELP-MEMOIZE-SQL-JOIN"
    "(DEFUN (HELP-MEMOIZE-SQL-JOIN (ITERATOR OF CONS)) ((PROPOSITION PROPOSITION) (DATABASE LOGIC-OBJECT) (ARGUMENTS OBJECT)))"
    (CL:FUNCTION HELP-MEMOIZE-SQL-JOIN) NULL)
   (DEFINE-FUNCTION-OBJECT "SQL-JOIN"
    "(DEFUN (SQL-JOIN (ITERATOR OF CONS)) ((PROPOSITION PROPOSITION) (DATABASE LOGIC-OBJECT) (ARGUMENTS OBJECT)))"
    (CL:FUNCTION SQL-JOIN) NULL)
   (DEFINE-FUNCTION-OBJECT "COLLECT-VARIABLE-BINDING"
    "(DEFUN COLLECT-VARIABLE-BINDING ((NAME STRING) (TYPE OBJECT) (BINDING OBJECT) (BINDINGS (KEY-VALUE-LIST OF STRING-WRAPPER OBJECT))))"
    (CL:FUNCTION COLLECT-VARIABLE-BINDING) NULL)
   (DEFINE-FUNCTION-OBJECT "CREATE-SQL-QUERY-FROM-PROPOSITION"
    "(DEFUN (CREATE-SQL-QUERY-FROM-PROPOSITION STRING) ((PROPOSITION PROPOSITION) (DATABASE LOGIC-OBJECT) (ARGUMENTS OBJECT)))"
    (CL:FUNCTION CREATE-SQL-QUERY-FROM-PROPOSITION) NULL)
   (DEFINE-FUNCTION-OBJECT "HELP-MEMOIZE-SQL-QUERY"
    "(DEFUN (HELP-MEMOIZE-SQL-QUERY (ITERATOR OF CONS)) ((PROPOSITION PROPOSITION) (DATABASE LOGIC-OBJECT) (ARGUMENTS OBJECT)))"
    (CL:FUNCTION HELP-MEMOIZE-SQL-QUERY) NULL)
   (DEFINE-FUNCTION-OBJECT "SQL-QUERY-INSTANTIATE-CONSTRAINTS"
    "(DEFUN (SQL-QUERY-INSTANTIATE-CONSTRAINTS STRING) ((SQL STRING) (BINDINGS (KEY-VALUE-LIST OF STRING-WRAPPER OBJECT))))"
    (CL:FUNCTION SQL-QUERY-INSTANTIATE-CONSTRAINTS) NULL)
   (DEFINE-FUNCTION-OBJECT "SQL-QUERY"
    "(DEFUN (SQL-QUERY (ITERATOR OF CONS)) ((PROPOSITION PROPOSITION) (DATABASE LOGIC-OBJECT) (ARGUMENTS OBJECT)))"
    (CL:FUNCTION SQL-QUERY) NULL)
   (DEFINE-FUNCTION-OBJECT "ALLOCATE-QUERY-SPECIALIST-ITERATOR"
    "(DEFUN (ALLOCATE-QUERY-SPECIALIST-ITERATOR (ITERATOR OF CONS)) ((FRAME CONTROL-FRAME)))"
    (CL:FUNCTION ALLOCATE-QUERY-SPECIALIST-ITERATOR) NULL)
   (DEFINE-FUNCTION-OBJECT "QUERY-SPECIALIST"
    "(DEFUN (QUERY-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))"
    (CL:FUNCTION QUERY-SPECIALIST) NULL)
   (DEFINE-FUNCTION-OBJECT "COLLECT-QUERY-DATABASE-SPECIALIST-BINDINGS"
    "(DEFUN (COLLECT-QUERY-DATABASE-SPECIALIST-BINDINGS (KEY-VALUE-LIST OF STRING-WRAPPER OBJECT)) ((FRAME CONTROL-FRAME) (FIRSTARGINDEX INTEGER)))"
    (CL:FUNCTION COLLECT-QUERY-DATABASE-SPECIALIST-BINDINGS) NULL)
   (DEFINE-FUNCTION-OBJECT "BIND-NEXT-DATABASE-TUPLE-TO-ARGUMENTS"
    "(DEFUN (BIND-NEXT-DATABASE-TUPLE-TO-ARGUMENTS KEYWORD) ((FRAME CONTROL-FRAME) (FIRSTARGINDEX INTEGER)))"
    (CL:FUNCTION BIND-NEXT-DATABASE-TUPLE-TO-ARGUMENTS) NULL)
   (DEFINE-FUNCTION-OBJECT "QUERY-SQL-DATABASE-SPECIALIST"
    "(DEFUN (QUERY-SQL-DATABASE-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))"
    (CL:FUNCTION QUERY-SQL-DATABASE-SPECIALIST) NULL)
   (DEFINE-FUNCTION-OBJECT "QUERY-DATABASE-SPECIALIST"
    "(DEFUN (QUERY-DATABASE-SPECIALIST KEYWORD) ((FRAME CONTROL-FRAME) (LASTMOVE KEYWORD)))"
    (CL:FUNCTION QUERY-DATABASE-SPECIALIST) NULL)
   (DEFINE-FUNCTION-OBJECT "DB-UPDATE-DEMON"
    "(DEFUN DB-UPDATE-DEMON ((DBPROPOSITION PROPOSITION)))"
    (CL:FUNCTION DB-UPDATE-DEMON) NULL)
   (DEFINE-FUNCTION-OBJECT "CHECK-FOR-EXTERNAL-DB-UPDATES"
    "(DEFUN CHECK-FOR-EXTERNAL-DB-UPDATES ((PROPOSITION PROPOSITION) (DATABASE LOGIC-OBJECT)))"
    (CL:FUNCTION CHECK-FOR-EXTERNAL-DB-UPDATES) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-QUERY-PATTERN-MEMOIZATION-KEY"
    "(DEFUN (GET-QUERY-PATTERN-MEMOIZATION-KEY OBJECT) ((PROPOSITION PROPOSITION)))"
    (CL:FUNCTION GET-QUERY-PATTERN-MEMOIZATION-KEY) NULL)
   (DEFINE-FUNCTION-OBJECT "COERCE-VALUES"
    "(DEFUN (COERCE-VALUES (CONS OF OBJECT)) ((VALUES (CONS OF STRING-WRAPPER)) (TABLE RELATION-TABLE-INFO)))"
    (CL:FUNCTION COERCE-VALUES) NULL)
   (DEFINE-FUNCTION-OBJECT "COERCE-STRING-TO-POWERLOOM-OBJECT"
    "(DEFUN (COERCE-STRING-TO-POWERLOOM-OBJECT OBJECT) ((VALUE STRING) (TYPE NAMED-DESCRIPTION) (MODULE MODULE) (LOCAL? BOOLEAN)))"
    (CL:FUNCTION COERCE-STRING-TO-POWERLOOM-OBJECT) NULL)
   (DEFINE-FUNCTION-OBJECT "NUMBER-STRING-TO-INTEGER"
    "(DEFUN (NUMBER-STRING-TO-INTEGER INTEGER) ((X STRING)))"
    (CL:FUNCTION NUMBER-STRING-TO-INTEGER) NULL)))

(CL:DEFUN STARTUP-RDBMS ()
  (CL:LET*
   ((*MODULE* (GET-STELLA-MODULE "/RDBMS" (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2) (HELP-STARTUP-RDBMS1)
    (HELP-STARTUP-RDBMS2) (HELP-STARTUP-RDBMS3))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 5)
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "CONNECTION-WRAPPER"
        "(DEFCLASS CONNECTION-WRAPPER (LOGIC-THING) :PUBLIC-SLOTS ((WRAPPER-VALUE :TYPE /SDBC/CONNECTION)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION NEW-CONNECTION-WRAPPER))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION ACCESS-CONNECTION-WRAPPER-SLOT-VALUE)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "RELATION-TABLE-INFO"
        "(DEFCLASS RELATION-TABLE-INFO (STANDARD-OBJECT) :DOCUMENTATION \"Data structure that associates a PowerLoom relation representing
a database table or query with various information about its columns, value coercion, etc.\" :PUBLIC-SLOTS ((RELATION :TYPE NAMED-DESCRIPTION) (DATABASE :TYPE OBJECT) (DBMS-NAME :TYPE KEYWORD) (TABLE-NAME :TYPE STRING) (TABLE-ALIAS :TYPE STRING :INITIALLY \"_T\") (COLUMN-LIST :TYPE (CONS OF RELATION-COLUMN-INFO)) (COLUMN-VECTOR :TYPE (VECTOR OF RELATION-COLUMN-INFO)) (COLUMN-INDEX :TYPE (KEY-VALUE-MAP OF OBJECT RELATION-COLUMN-INFO)) (ADJUNCT :TYPE OBJECT)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION NEW-RELATION-TABLE-INFO))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION ACCESS-RELATION-TABLE-INFO-SLOT-VALUE)))
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "RELATION-COLUMN-INFO"
        "(DEFCLASS RELATION-COLUMN-INFO (STANDARD-OBJECT) :PUBLIC-SLOTS ((TABLE-INFO :TYPE RELATION-TABLE-INFO) (COLUMN-NAME :TYPE STRING) (COLUMN-VARIABLE :TYPE SYMBOL) (COLUMN-INDEX :TYPE INTEGER) (COLUMN-TYPE :TYPE NAMED-DESCRIPTION) (COLUMN-DB-TYPE :TYPE STRING) (MODULE-NAME :TYPE STRING) (MODULE-REFERENCE :TYPE STRING) (MODULE :TYPE MODULE) (MODULE-LOCAL? :TYPE BOOLEAN) (MODULE-REFERENCE-COLUMN :TYPE RELATION-COLUMN-INFO) (COERCION-FUNCTION :TYPE FUNCTION-CODE)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION NEW-RELATION-COLUMN-INFO))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION ACCESS-RELATION-COLUMN-INFO-SLOT-VALUE))))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7) (HELP-STARTUP-RDBMS4)
    (DEFINE-FUNCTION-OBJECT "COERCE-POWERLOOM-OBJECT-TO-STRING"
     "(DEFUN (COERCE-POWERLOOM-OBJECT-TO-STRING STRING) ((OBJECT OBJECT) (TYPE NAMED-DESCRIPTION)))"
     (CL:FUNCTION COERCE-POWERLOOM-OBJECT-TO-STRING) NULL)
    (DEFINE-FUNCTION-OBJECT "FIND-OR-CREATE-INSTANCE"
     "(DEFUN (FIND-OR-CREATE-INSTANCE OBJECT) ((NAME STRING) (TYPE NAMED-DESCRIPTION) (MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Find an existing instance with `name' in `module' or create one with `type'
if it does not yet exist.  If `local?' do not look into any inherited modules.\" :PUBLIC? TRUE)"
     (CL:FUNCTION FIND-OR-CREATE-INSTANCE) NULL)
    (DEFINE-FUNCTION-OBJECT "CREATE-SQL-ASSERTION-FROM-PROPOSITION"
     "(DEFUN (CREATE-SQL-ASSERTION-FROM-PROPOSITION STRING) ((PROPOSITION PROPOSITION) (MODE KEYWORD)))"
     (CL:FUNCTION CREATE-SQL-ASSERTION-FROM-PROPOSITION) NULL)
    (DEFINE-FUNCTION-OBJECT "DB-RELATION-GOES-TRUE"
     "(DEFUN DB-RELATION-GOES-TRUE ((PROPOSITION PROPOSITION)))"
     (CL:FUNCTION DB-RELATION-GOES-TRUE) NULL)
    (DEFINE-FUNCTION-OBJECT "DB-RELATION-GOES-UNKNOWN"
     "(DEFUN DB-RELATION-GOES-UNKNOWN ((PROPOSITION PROPOSITION)))"
     (CL:FUNCTION DB-RELATION-GOES-UNKNOWN) NULL)
    (DEFINE-FUNCTION-OBJECT "DB-RELATION-GOES-FALSE"
     "(DEFUN DB-RELATION-GOES-FALSE ((PROPOSITION PROPOSITION)))"
     (CL:FUNCTION DB-RELATION-GOES-FALSE) NULL)
    (DEFINE-FUNCTION-OBJECT "DB-RELATION-UPDATE-DEMON"
     "(DEFUN DB-RELATION-UPDATE-DEMON ((PROPOSITION PROPOSITION) (UPDATE-MODE KEYWORD)))"
     (CL:FUNCTION DB-RELATION-UPDATE-DEMON) NULL)
    (DEFINE-FUNCTION-OBJECT "STARTUP-RDBMS"
     "(DEFUN STARTUP-RDBMS () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-RDBMS) NULL)
    (CL:LET*
     ((FUNCTION (LOOKUP-FUNCTION SYM-RDBMS-RDBMS-STARTUP-RDBMS)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-RDBMS-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupRdbms") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "RDBMS")))
    (REGISTER-NATIVE-NAME SYM-RDBMS-RDBMS-DEFUNTABLE
     KWD-RDBMS-COMMON-LISP KWD-RDBMS-FUNCTION)
    (SAFE-IMPORT-SYMBOL SYM-RDBMS-RDBMS-DEFUNTABLE
     (GET-STELLA-MODULE "PL-KERNEL" CL:T))
    (REGISTER-NATIVE-NAME SYM-RDBMS-RDBMS-DEFTABLE
     KWD-RDBMS-COMMON-LISP KWD-RDBMS-FUNCTION)
    (SAFE-IMPORT-SYMBOL SYM-RDBMS-RDBMS-DEFTABLE
     (GET-STELLA-MODULE "PL-KERNEL" CL:T))
    (REGISTER-NATIVE-NAME SYM-RDBMS-RDBMS-DEFDB KWD-RDBMS-COMMON-LISP
     KWD-RDBMS-FUNCTION)
    (SAFE-IMPORT-SYMBOL SYM-RDBMS-RDBMS-DEFDB
     (GET-STELLA-MODULE "PL-KERNEL" CL:T))
    (REGISTER-NATIVE-NAME SYM-RDBMS-RDBMS-ASSERT-RDBMS-CONNECTION-INFO
     KWD-RDBMS-COMMON-LISP KWD-RDBMS-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-RDBMS-RDBMS-DEFQUERY
     KWD-RDBMS-COMMON-LISP KWD-RDBMS-FUNCTION)
    (SAFE-IMPORT-SYMBOL SYM-RDBMS-RDBMS-DEFQUERY
     (GET-STELLA-MODULE "PL-KERNEL" CL:T))
    (DEFINE-EXPLANATION-PHRASE KWD-RDBMS-DB-LOOKUP KWD-RDBMS-TECHNICAL
     "by database lookup")
    (DEFINE-EXPLANATION-PHRASE KWD-RDBMS-DB-LOOKUP KWD-RDBMS-LAY
     "because it is stored in database"))))
