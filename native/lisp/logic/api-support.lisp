;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; api-support.lisp

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

(CL:DEFVAR SGT-API-SUPPORT-LOGIC-TRUTH-VALUE NULL)
(CL:DEFVAR SGT-API-SUPPORT-LOGIC-LOGIC-OBJECT NULL)
(CL:DEFVAR SGT-API-SUPPORT-LOGIC-PATTERN-VARIABLE NULL)
(CL:DEFVAR SGT-API-SUPPORT-LOGIC-SKOLEM NULL)
(CL:DEFVAR SGT-API-SUPPORT-LOGIC-NAMED-DESCRIPTION NULL)
(CL:DEFVAR SGT-API-SUPPORT-LOGIC-DESCRIPTION NULL)
(CL:DEFVAR SGT-API-SUPPORT-STELLA-THING NULL)
(CL:DEFVAR SYM-API-SUPPORT-LOGIC-STARTUP-API-SUPPORT NULL)
(CL:DEFVAR SYM-API-SUPPORT-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM (CL:SPECIAL *STARTUP-TIME-PHASE* NIL *CONTEXT* *MODULE*))

;;; (DEFUN (CLASS-NAMES-NEXT? BOOLEAN) ...)

(CL:DEFUN CLASS-NAMES-NEXT? (SELF)
  (CL:WHEN (%FIRST-ITERATION? SELF)
   (CL:SETF (%FIRST-ITERATION? SELF) CL:NIL)
   (CL:SETF (%VALUE SELF) (%CLASS-TYPE (%ITERATOR-OBJECT SELF)))
   (CL:RETURN-FROM CLASS-NAMES-NEXT? CL:T))
  (CL:LET* ((NEXT? (NEXT? (%ITERATOR-NESTED-ITERATOR SELF))))
   (CL:WHEN NEXT?
    (CL:SETF (%VALUE SELF) (%VALUE (%ITERATOR-NESTED-ITERATOR SELF))))
   NEXT?))

;;; (DEFUN (ALL-PROPOSITIONS-NEXT? BOOLEAN) ...)

(CL:DEFUN ALL-PROPOSITIONS-NEXT? (SELF)
  (CL:LOOP
   (CL:LET* ((ITERATOR (%ITERATOR-NESTED-ITERATOR SELF)) (MODULE NULL))
    (CL:WHEN (NEXT? ITERATOR) (CL:SETF (%VALUE SELF) (%VALUE ITERATOR))
     (CL:RETURN-FROM ALL-PROPOSITIONS-NEXT? CL:T))
    (CL:SETQ MODULE (POP (%ITERATOR-OBJECT SELF)))
    (CL:WHEN (CL:EQ MODULE NULL) (CL:SETF (%VALUE SELF) NULL)
     (CL:RETURN-FROM ALL-PROPOSITIONS-NEXT? CL:NIL))
    (CL:SETF (%ITERATOR-NESTED-ITERATOR SELF)
     (ALLOCATE-ITERATOR (LOCALLY-CONCEIVED-PROPOSITIONS MODULE))))))

;;; (DEFUN (ALL-PROPOSITIONS (ITERATOR OF PROPOSITION)) ...)

(CL:DEFUN ALL-PROPOSITIONS (MODULE LOCAL?)
  "Iterate over all conceived propositions visible from `module'.
Only propositions that haven't been deleted will be considered.
If `local?', only return propositions conceived locally in `module'."
  (CL:LET* ((SELF-000 (NEW-ALL-PURPOSE-ITERATOR)))
   (CL:SETF (%ITERATOR-OBJECT SELF-000)
    (CL:IF LOCAL? (LIST)
     (LISTIFY
      (REVERSE (COPY-CONS-LIST (%%REST (VISIBLE-MODULES MODULE)))))))
   (CL:SETF (%ITERATOR-NESTED-ITERATOR SELF-000)
    (ALLOCATE-ITERATOR (LOCALLY-CONCEIVED-PROPOSITIONS MODULE)))
   (CL:SETF (%ITERATOR-NEXT-CODE SELF-000)
    (CL:FUNCTION ALL-PROPOSITIONS-NEXT?))
   (CL:LET* ((VALUE-000 SELF-000)) VALUE-000)))

;;; (DEFUN (FILTER-INCONSISTENT-PROPOSITION? BOOLEAN) ...)

(CL:DEFUN FILTER-INCONSISTENT-PROPOSITION? (SELF ITERATOR)
  (CL:LET* ((MODULE (%ITERATOR-OBJECT ITERATOR)))
   (CL:LET* ((*CONTEXT* NULL) (*MODULE* NULL))
    (CL:DECLARE (CL:SPECIAL *CONTEXT* *MODULE*))
    (CL:LET* ((TEMP-000 (BEST-INFERENCE-CACHE MODULE)))
     (CL:SETQ *CONTEXT*
      (CL:IF (CL:NOT (CL:EQ TEMP-000 NULL)) TEMP-000 MODULE)))
    (CL:SETQ *MODULE* (%BASE-MODULE *CONTEXT*)) (INCONSISTENT? SELF))))

;;; (DEFUN (ALL-INCONSISTENT-PROPOSITIONS (ITERATOR OF PROPOSITION)) ...)

(CL:DEFUN ALL-INCONSISTENT-PROPOSITIONS (MODULE LOCAL?)
  "Iterate over all conceived propositions visible from `module'
that have an inconsistent truth value.  If `local?', only return
inconsistent propositions conceived locally in `module'."
  (CL:LET*
   ((PROPOSITIONS-ITERATOR (ALL-PROPOSITIONS MODULE LOCAL?))
    (ITERATOR (NEW-ALL-PURPOSE-ITERATOR)))
   (CL:SETF (%ITERATOR-OBJECT ITERATOR) MODULE)
   (CL:SETF (%FIRST-ITERATION? ITERATOR) CL:T)
   (CL:SETF (%ITERATOR-NESTED-ITERATOR ITERATOR) PROPOSITIONS-ITERATOR)
   (CL:SETF (%ITERATOR-NEXT-CODE ITERATOR)
    (CL:FUNCTION FILTERED-NESTED-ITERATOR-NEXT?))
   (CL:SETF (%ITERATOR-FILTER-CODE ITERATOR)
    (CL:FUNCTION FILTER-INCONSISTENT-PROPOSITION?))
   ITERATOR))

;;; (DEFUN (LOCALLY-MODIFIED-PROPOSITION? BOOLEAN) ...)

(CL:DEFUN LOCALLY-MODIFIED-PROPOSITION? (PROPOSITION MODULE)
  "Return true if proposition's truth-value has been locally modified in
`module' (initialized, asserted, retracted).  This will always succeed for locally conceived
propositions regardless of whether their truth value is defined or not."
  (CL:LET* ((TRUTHVALUE (%TRUTH-VALUE PROPOSITION)))
   (CL:COND
    ((CL:OR (CL:EQ TRUTHVALUE NULL)
      (ISA? TRUTHVALUE SGT-API-SUPPORT-LOGIC-TRUTH-VALUE))
     (CL:RETURN-FROM LOCALLY-MODIFIED-PROPOSITION?
      (CL:EQ (HOME-MODULE PROPOSITION) MODULE)))
    (CL:T
     (CL:LET*
      ((CTXT NULL) (TV NULL) (ITER-000 (%THE-KV-LIST TRUTHVALUE)))
      (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NULL)) DO
       (CL:SETQ CTXT (%KEY ITER-000)) (CL:SETQ TV (%VALUE ITER-000))
       (CL:SETQ TV TV)
       (CL:WHEN (CL:EQ CTXT MODULE)
        (CL:RETURN-FROM LOCALLY-MODIFIED-PROPOSITION? CL:T))
       (CL:SETQ ITER-000 (%REST ITER-000))))))
   CL:NIL))

;;; (DEFUN (FILTER-LOCALLY-MODIFIED-PROPOSITION? BOOLEAN) ...)

(CL:DEFUN FILTER-LOCALLY-MODIFIED-PROPOSITION? (SELF ITERATOR)
  (LOCALLY-MODIFIED-PROPOSITION? SELF (%ITERATOR-OBJECT ITERATOR)))

;;; (DEFUN (ALL-LOCALLY-MODIFIED-PROPOSITIONS (ITERATOR OF PROPOSITION)) ...)

(CL:DEFUN ALL-LOCALLY-MODIFIED-PROPOSITIONS (MODULE)
  "Iterate over all conceived propositions visible from `module' that had their
truth value locally modified (initialized, asserted, retracted).  Note, that this
will always include all locally conceived propositions."
  (CL:LET*
   ((PROPOSITIONS-ITERATOR (ALL-PROPOSITIONS MODULE CL:NIL))
    (ITERATOR (NEW-ALL-PURPOSE-ITERATOR)))
   (CL:SETF (%ITERATOR-OBJECT ITERATOR) MODULE)
   (CL:SETF (%FIRST-ITERATION? ITERATOR) CL:T)
   (CL:SETF (%ITERATOR-NESTED-ITERATOR ITERATOR) PROPOSITIONS-ITERATOR)
   (CL:SETF (%ITERATOR-NEXT-CODE ITERATOR)
    (CL:FUNCTION FILTERED-NESTED-ITERATOR-NEXT?))
   (CL:SETF (%ITERATOR-FILTER-CODE ITERATOR)
    (CL:FUNCTION FILTER-LOCALLY-MODIFIED-PROPOSITION?))
   ITERATOR))

;;; (DEFUN (VISIBLE-TERM? BOOLEAN) ...)

(CL:DEFUN VISIBLE-TERM? (TERM CONTEXT LOCAL?)
  (CL:IF LOCAL? (CL:EQ (%HOME-CONTEXT TERM) CONTEXT)
   (VISIBLE-FROM? (%HOME-CONTEXT TERM) CONTEXT)))

;;; (DEFUN (ALL-UNNAMED-TERMS ITERATOR) ...)

(CL:DEFUN ALL-UNNAMED-TERMS (MODULE LOCAL?)
  "Iterate over all unnamed terms visible from `module'.  A term can be
an instance (or individual) as well as a description.  Only terms that
haven't been deleted will be considered.  If `local?', only return
terms created locally in `module'."
  (CL:LET* ((TERMS NIL) (TERMSWITHDUPLICATES NIL) (TERM NULL))
   (CL:LET*
    ((PROPOSITION NULL) (ITER-000 (ALL-PROPOSITIONS MODULE LOCAL?)))
    (CL:LOOP WHILE (NEXT? ITER-000) DO
     (CL:SETQ PROPOSITION (%VALUE ITER-000))
     (CL:LET*
      ((ARG NULL) (VECTOR-000 (%ARGUMENTS PROPOSITION)) (INDEX-000 0)
       (LENGTH-000 (LENGTH VECTOR-000)))
      (CL:DECLARE (CL:TYPE CL:FIXNUM INDEX-000 LENGTH-000))
      (CL:LOOP WHILE (CL:< INDEX-000 LENGTH-000) DO
       (CL:SETQ ARG
        (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY VECTOR-000))
         INDEX-000))
       (CL:TAGBODY
        (CL:WHEN
         (CL:AND (CL:NOT (CL:EQ ARG NULL))
          (ISA? ARG SGT-API-SUPPORT-LOGIC-LOGIC-OBJECT)
          (CL:NOT (DELETED? ARG)))
         (CL:SETQ TERM ARG)
         (CL:WHEN
          (CL:OR (CL:NOT (VISIBLE-TERM? TERM MODULE LOCAL?))
           (CL:NOT (CL:EQ (%SURROGATE-VALUE-INVERSE TERM) NULL)))
          (CL:GO :CONTINUE))
         (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE TERM)))
          (CL:COND
           ((SUBTYPE-OF? TEST-VALUE-000
             SGT-API-SUPPORT-LOGIC-PATTERN-VARIABLE)
            (CL:PROGN))
           ((SUBTYPE-OF? TEST-VALUE-000 SGT-API-SUPPORT-LOGIC-SKOLEM)
            (CL:PROGN
             (CL:IF (CL:NOT (CL:EQ (%DEFINING-PROPOSITION TERM) NULL))
              (CL:WHEN (CL:EQ (%DEFINING-PROPOSITION TERM) PROPOSITION)
               (CL:SETQ TERMS (CONS TERM TERMS)))
              (CL:SETQ TERMSWITHDUPLICATES
               (CONS TERM TERMSWITHDUPLICATES)))))
           (CL:T
            (CL:SETQ TERMSWITHDUPLICATES
             (CONS TERM TERMSWITHDUPLICATES))))))
        :CONTINUE)
       (CL:SETQ INDEX-000 (CL:1+ INDEX-000))))))
   (ALLOCATE-ITERATOR
    (CONCATENATE TERMS (REMOVE-DUPLICATES TERMSWITHDUPLICATES)))))

;;; (DEFUN (NAMED-TERM? BOOLEAN) ...)

(CL:DEFUN NAMED-TERM? (TERM ITER)
  (CL:SETQ ITER ITER)
  (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE TERM)))
   (CL:COND
    ((SUBTYPE-OF? TEST-VALUE-000
      SGT-API-SUPPORT-LOGIC-NAMED-DESCRIPTION)
     (CL:PROGN (CL:NOT (DELETED? TERM))))
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-API-SUPPORT-LOGIC-DESCRIPTION)
     (CL:PROGN CL:NIL))
    ((SUBTYPE-OF? TEST-VALUE-000
      SGT-API-SUPPORT-LOGIC-PATTERN-VARIABLE)
     (CL:PROGN CL:NIL))
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-API-SUPPORT-LOGIC-LOGIC-OBJECT)
     (CL:PROGN (CL:NOT (DELETED? TERM))))
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-API-SUPPORT-STELLA-THING)
     (CL:PROGN (CL:NOT (DELETED? TERM))))
    (CL:T CL:NIL))))

;;; (DEFUN (ALL-NAMED-TERMS (ITERATOR OF OBJECT)) ...)

(CL:DEFUN ALL-NAMED-TERMS (MODULE LOCAL?)
  "Iterate over all named terms visible from `module'.  A term can be an
instance (or individual) as well as a description.  Only terms that
haven't been deleted will be considered.  If `local?', only return 
terms created locally in `module'."
  (CL:IF LOCAL?
   (CL:LET* ((SELF-000 (NEW-ALL-PURPOSE-ITERATOR)))
    (CL:SETF (%ITERATOR-NESTED-ITERATOR SELF-000)
     (ALLOCATE-ITERATOR (LOCALLY-CONCEIVED-INSTANCES MODULE)))
    (CL:SETF (%ITERATOR-NEXT-CODE SELF-000)
     (CL:FUNCTION FILTERED-NESTED-ITERATOR-NEXT?))
    (CL:SETF (%ITERATOR-FILTER-CODE SELF-000)
     (CL:FUNCTION NAMED-TERM?))
    (CL:LET* ((VALUE-000 SELF-000)) VALUE-000))
   (CL:LET*
    ((ITERATOR1 (ALL-NAMED-TERMS MODULE CL:T)) (ITERATORLIST NIL))
    (CL:LET*
     ((SUPER NULL) (ITER-000 (%ALL-SUPER-CONTEXTS MODULE))
      (COLLECT-000 NULL))
     (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
      (CL:SETQ SUPER (%%VALUE ITER-000))
      (CL:IF (CL:EQ COLLECT-000 NULL)
       (CL:PROGN
        (CL:SETQ COLLECT-000 (CONS (ALL-NAMED-TERMS SUPER CL:T) NIL))
        (CL:IF (CL:EQ ITERATORLIST NIL)
         (CL:SETQ ITERATORLIST COLLECT-000)
         (ADD-CONS-TO-END-OF-CONS-LIST ITERATORLIST COLLECT-000)))
       (CL:PROGN
        (CL:SETF (%%REST COLLECT-000)
         (CONS (ALL-NAMED-TERMS SUPER CL:T) NIL))
        (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
      (CL:SETQ ITER-000 (%%REST ITER-000))))
    (CL:IF (CL:EQ ITERATORLIST NIL) ITERATOR1
     (CL:LET* ((SELF-001 (NEW-ALL-PURPOSE-ITERATOR)))
      (CL:SETF (%ITERATOR-NESTED-ITERATOR SELF-001) ITERATOR1)
      (CL:SETF (%ITERATOR-CONS-LIST SELF-001) ITERATORLIST)
      (CL:SETF (%ITERATOR-NEXT-CODE SELF-001)
       (CL:FUNCTION FILTERED-CONCATENATED-ITERATOR-NEXT?))
      (CL:LET* ((VALUE-001 SELF-001)) VALUE-001))))))

;;; (DEFUN (ALL-TERMS (ITERATOR OF OBJECT)) ...)

(CL:DEFUN ALL-TERMS (MODULE LOCAL?)
  "Return a list of all terms visible from `module'.  A term can be an
instance (or individual) as well as a description.  Only terms that
haven't been deleted will be considered.  If `local?', only return 
terms created locally in `module'."
  (CL:IF LOCAL?
   (CL:PROGN
    (REMOVE-DELETED-MEMBERS (LOCALLY-CONCEIVED-INSTANCES MODULE))
    (ALLOCATE-ITERATOR (LOCALLY-CONCEIVED-INSTANCES MODULE)))
   (CONCATENATE (ALL-NAMED-TERMS MODULE CL:NIL)
    (ALL-UNNAMED-TERMS MODULE CL:NIL))))

;;; (DEFUN (FILTER-INSTANCE? BOOLEAN) ...)

(CL:DEFUN FILTER-INSTANCE? (SELF ITERATOR)
  (CL:SETQ ITERATOR ITERATOR)
  (CL:NOT (ISA? SELF SGT-API-SUPPORT-LOGIC-DESCRIPTION)))

;;; (DEFUN (ALL-NAMED-INSTANCES (ITERATOR OF LOGIC-OBJECT)) ...)

(CL:DEFUN ALL-NAMED-INSTANCES (MODULE LOCAL?)
  "Iterate over all named instances (or individuals) visible from `module'.
Only instances that haven't been deleted will be considered.  If `local?',
only return instances created locally in `module'."
  (CL:LET* ((SELF-000 (NEW-ALL-PURPOSE-ITERATOR)))
   (CL:SETF (%ITERATOR-NESTED-ITERATOR SELF-000)
    (ALL-NAMED-TERMS MODULE LOCAL?))
   (CL:SETF (%ITERATOR-NEXT-CODE SELF-000)
    (CL:FUNCTION FILTERED-NESTED-ITERATOR-NEXT?))
   (CL:SETF (%ITERATOR-FILTER-CODE SELF-000)
    (CL:FUNCTION FILTER-INSTANCE?))
   (CL:LET* ((VALUE-000 SELF-000)) VALUE-000)))

;;; (DEFUN (ALL-INSTANCES (ITERATOR OF LOGIC-OBJECT)) ...)

(CL:DEFUN ALL-INSTANCES (MODULE LOCAL?)
  "Iterate over all instances (or individuals) visible from `module'.
Only instances that haven't been deleted will be considered.  If `local?',
only return instances created locally in `module'."
  (CL:LET*
   ((ITERATOR (ALL-TERMS MODULE LOCAL?)) (ALLPURPOSEITERATOR NULL))
   (CL:IF LOCAL?
    (CL:LET* ((SELF-000 (NEW-ALL-PURPOSE-ITERATOR)))
     (CL:SETF (%ITERATOR-NESTED-ITERATOR SELF-000) ITERATOR)
     (CL:SETF (%ITERATOR-NEXT-CODE SELF-000)
      (CL:FUNCTION FILTERED-NESTED-ITERATOR-NEXT?))
     (CL:SETQ ALLPURPOSEITERATOR SELF-000))
    (CL:SETQ ALLPURPOSEITERATOR ITERATOR))
   (CL:SETF (%ITERATOR-FILTER-CODE ALLPURPOSEITERATOR)
    (CL:FUNCTION FILTER-INSTANCE?))
   ALLPURPOSEITERATOR))

;;; (DEFUN (STRING-TO-LOGIC-OBJECT LOGIC-OBJECT) ...)

(CL:DEFUN STRING-TO-LOGIC-OBJECT (STRING)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING STRING))
  #+MCL
  (CL:CHECK-TYPE STRING CL:SIMPLE-STRING)
  (CL:LET* ((SGT NULL) (ITER-000 (ALL-SURROGATES NULL CL:NIL)))
   (CL:LOOP WHILE (NEXT? ITER-000) DO (CL:SETQ SGT (%VALUE ITER-000))
    (CL:WHEN
     (CL:AND (STRING-EQL? (%SYMBOL-NAME SGT) STRING)
      (CL:NOT (CL:EQ (%SURROGATE-VALUE SGT) NULL))
      (ISA? (%SURROGATE-VALUE SGT) SGT-API-SUPPORT-LOGIC-LOGIC-OBJECT))
     (CL:RETURN-FROM STRING-TO-LOGIC-OBJECT (%SURROGATE-VALUE SGT)))))
  NULL)

(CL:DEFUN STARTUP-API-SUPPORT ()
  (CL:LET*
   ((*MODULE* (GET-STELLA-MODULE "/LOGIC" (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
    (CL:SETQ SGT-API-SUPPORT-LOGIC-TRUTH-VALUE
     (INTERN-RIGID-SYMBOL-WRT-MODULE "TRUTH-VALUE" NULL 1))
    (CL:SETQ SGT-API-SUPPORT-LOGIC-LOGIC-OBJECT
     (INTERN-RIGID-SYMBOL-WRT-MODULE "LOGIC-OBJECT" NULL 1))
    (CL:SETQ SGT-API-SUPPORT-LOGIC-PATTERN-VARIABLE
     (INTERN-RIGID-SYMBOL-WRT-MODULE "PATTERN-VARIABLE" NULL 1))
    (CL:SETQ SGT-API-SUPPORT-LOGIC-SKOLEM
     (INTERN-RIGID-SYMBOL-WRT-MODULE "SKOLEM" NULL 1))
    (CL:SETQ SGT-API-SUPPORT-LOGIC-NAMED-DESCRIPTION
     (INTERN-RIGID-SYMBOL-WRT-MODULE "NAMED-DESCRIPTION" NULL 1))
    (CL:SETQ SGT-API-SUPPORT-LOGIC-DESCRIPTION
     (INTERN-RIGID-SYMBOL-WRT-MODULE "DESCRIPTION" NULL 1))
    (CL:SETQ SGT-API-SUPPORT-STELLA-THING
     (INTERN-RIGID-SYMBOL-WRT-MODULE "THING"
      (GET-STELLA-MODULE "/STELLA" CL:T) 1))
    (CL:SETQ SYM-API-SUPPORT-LOGIC-STARTUP-API-SUPPORT
     (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-API-SUPPORT" NULL 0))
    (CL:SETQ SYM-API-SUPPORT-STELLA-METHOD-STARTUP-CLASSNAME
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
    (DEFINE-FUNCTION-OBJECT "CLASS-NAMES-NEXT?"
     "(DEFUN (CLASS-NAMES-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))"
     (CL:FUNCTION CLASS-NAMES-NEXT?) NULL)
    (DEFINE-FUNCTION-OBJECT "ALL-PROPOSITIONS-NEXT?"
     "(DEFUN (ALL-PROPOSITIONS-NEXT? BOOLEAN) ((SELF ALL-PURPOSE-ITERATOR)))"
     (CL:FUNCTION ALL-PROPOSITIONS-NEXT?) NULL)
    (DEFINE-FUNCTION-OBJECT "ALL-PROPOSITIONS"
     "(DEFUN (ALL-PROPOSITIONS (ITERATOR OF PROPOSITION)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all conceived propositions visible from `module'.
Only propositions that haven't been deleted will be considered.
If `local?', only return propositions conceived locally in `module'.\" :PUBLIC? TRUE)"
     (CL:FUNCTION ALL-PROPOSITIONS) NULL)
    (DEFINE-FUNCTION-OBJECT "FILTER-INCONSISTENT-PROPOSITION?"
     "(DEFUN (FILTER-INCONSISTENT-PROPOSITION? BOOLEAN) ((SELF OBJECT) (ITERATOR ALL-PURPOSE-ITERATOR)))"
     (CL:FUNCTION FILTER-INCONSISTENT-PROPOSITION?) NULL)
    (DEFINE-FUNCTION-OBJECT "ALL-INCONSISTENT-PROPOSITIONS"
     "(DEFUN (ALL-INCONSISTENT-PROPOSITIONS (ITERATOR OF PROPOSITION)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all conceived propositions visible from `module'
that have an inconsistent truth value.  If `local?', only return
inconsistent propositions conceived locally in `module'.\" :PUBLIC? TRUE)"
     (CL:FUNCTION ALL-INCONSISTENT-PROPOSITIONS) NULL)
    (DEFINE-FUNCTION-OBJECT "LOCALLY-MODIFIED-PROPOSITION?"
     "(DEFUN (LOCALLY-MODIFIED-PROPOSITION? BOOLEAN) ((PROPOSITION PROPOSITION) (MODULE MODULE)) :DOCUMENTATION \"Return true if proposition's truth-value has been locally modified in
`module' (initialized, asserted, retracted).  This will always succeed for locally conceived
propositions regardless of whether their truth value is defined or not.\" :PUBLIC? TRUE)"
     (CL:FUNCTION LOCALLY-MODIFIED-PROPOSITION?) NULL)
    (DEFINE-FUNCTION-OBJECT "FILTER-LOCALLY-MODIFIED-PROPOSITION?"
     "(DEFUN (FILTER-LOCALLY-MODIFIED-PROPOSITION? BOOLEAN) ((SELF OBJECT) (ITERATOR ALL-PURPOSE-ITERATOR)))"
     (CL:FUNCTION FILTER-LOCALLY-MODIFIED-PROPOSITION?) NULL)
    (DEFINE-FUNCTION-OBJECT "ALL-LOCALLY-MODIFIED-PROPOSITIONS"
     "(DEFUN (ALL-LOCALLY-MODIFIED-PROPOSITIONS (ITERATOR OF PROPOSITION)) ((MODULE MODULE)) :DOCUMENTATION \"Iterate over all conceived propositions visible from `module' that had their
truth value locally modified (initialized, asserted, retracted).  Note, that this
will always include all locally conceived propositions.\" :PUBLIC? TRUE)"
     (CL:FUNCTION ALL-LOCALLY-MODIFIED-PROPOSITIONS) NULL)
    (DEFINE-FUNCTION-OBJECT "VISIBLE-TERM?"
     "(DEFUN (VISIBLE-TERM? BOOLEAN) ((TERM LOGIC-OBJECT) (CONTEXT CONTEXT) (LOCAL? BOOLEAN)))"
     (CL:FUNCTION VISIBLE-TERM?) NULL)
    (DEFINE-FUNCTION-OBJECT "ALL-UNNAMED-TERMS"
     "(DEFUN (ALL-UNNAMED-TERMS ITERATOR) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all unnamed terms visible from `module'.  A term can be
an instance (or individual) as well as a description.  Only terms that
haven't been deleted will be considered.  If `local?', only return
terms created locally in `module'.\" :PUBLIC? TRUE)"
     (CL:FUNCTION ALL-UNNAMED-TERMS) NULL)
    (DEFINE-FUNCTION-OBJECT "NAMED-TERM?"
     "(DEFUN (NAMED-TERM? BOOLEAN) ((TERM OBJECT) (ITER ALL-PURPOSE-ITERATOR)))"
     (CL:FUNCTION NAMED-TERM?) NULL)
    (DEFINE-FUNCTION-OBJECT "ALL-NAMED-TERMS"
     "(DEFUN (ALL-NAMED-TERMS (ITERATOR OF OBJECT)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all named terms visible from `module'.  A term can be an
instance (or individual) as well as a description.  Only terms that
haven't been deleted will be considered.  If `local?', only return 
terms created locally in `module'.\" :PUBLIC? TRUE)"
     (CL:FUNCTION ALL-NAMED-TERMS) NULL)
    (DEFINE-FUNCTION-OBJECT "ALL-TERMS"
     "(DEFUN (ALL-TERMS (ITERATOR OF OBJECT)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Return a list of all terms visible from `module'.  A term can be an
instance (or individual) as well as a description.  Only terms that
haven't been deleted will be considered.  If `local?', only return 
terms created locally in `module'.\" :PUBLIC? TRUE)"
     (CL:FUNCTION ALL-TERMS) NULL)
    (DEFINE-FUNCTION-OBJECT "FILTER-INSTANCE?"
     "(DEFUN (FILTER-INSTANCE? BOOLEAN) ((SELF LOGIC-OBJECT) (ITERATOR ALL-PURPOSE-ITERATOR)))"
     (CL:FUNCTION FILTER-INSTANCE?) NULL)
    (DEFINE-FUNCTION-OBJECT "ALL-NAMED-INSTANCES"
     "(DEFUN (ALL-NAMED-INSTANCES (ITERATOR OF LOGIC-OBJECT)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all named instances (or individuals) visible from `module'.
Only instances that haven't been deleted will be considered.  If `local?',
only return instances created locally in `module'.\" :PUBLIC? TRUE)"
     (CL:FUNCTION ALL-NAMED-INSTANCES) NULL)
    (DEFINE-FUNCTION-OBJECT "ALL-INSTANCES"
     "(DEFUN (ALL-INSTANCES (ITERATOR OF LOGIC-OBJECT)) ((MODULE MODULE) (LOCAL? BOOLEAN)) :DOCUMENTATION \"Iterate over all instances (or individuals) visible from `module'.
Only instances that haven't been deleted will be considered.  If `local?',
only return instances created locally in `module'.\" :PUBLIC? TRUE)"
     (CL:FUNCTION ALL-INSTANCES) NULL)
    (DEFINE-FUNCTION-OBJECT "STRING-TO-LOGIC-OBJECT"
     "(DEFUN (STRING-TO-LOGIC-OBJECT LOGIC-OBJECT) ((STRING STRING)))"
     (CL:FUNCTION STRING-TO-LOGIC-OBJECT) NULL)
    (DEFINE-FUNCTION-OBJECT "STARTUP-API-SUPPORT"
     "(DEFUN STARTUP-API-SUPPORT () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-API-SUPPORT) NULL)
    (CL:LET*
     ((FUNCTION
       (LOOKUP-FUNCTION SYM-API-SUPPORT-LOGIC-STARTUP-API-SUPPORT)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-API-SUPPORT-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupApiSupport") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "LOGIC")))
    (INSERT-AT *STRING-TO-OBJECT-FUNCTIONS*
     SGT-API-SUPPORT-LOGIC-LOGIC-OBJECT
     (WRAP-FUNCTION-CODE (CL:FUNCTION STRING-TO-LOGIC-OBJECT))))))
