;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; logic-in.lisp

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

(CL:DEFVAR KWD-LOGIC-IN-TRACE-SUBGOALS NULL)
(CL:DEFVAR KWD-LOGIC-IN-TRACE-SOLUTIONS NULL)
(CL:DEFVAR KWD-LOGIC-IN-TRACE-CLASSIFIER NULL)
(CL:DEFVAR KWD-LOGIC-IN-ITERATIVE-DEEPENING NULL)
(CL:DEFVAR KWD-LOGIC-IN-JUSTIFICATIONS NULL)
(CL:DEFVAR KWD-LOGIC-IN-JUST-IN-TIME-INFERENCE NULL)
(CL:DEFVAR KWD-LOGIC-IN-EMIT-THINKING-DOTS NULL)
(CL:DEFVAR KWD-LOGIC-IN-GOAL-TREE NULL)
(CL:DEFVAR KWD-LOGIC-IN-CLASSIFIER-INFERENCES NULL)
(CL:DEFVAR KWD-LOGIC-IN-CLOSED-WORLD NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-SET-FEATURE NULL)
(CL:DEFVAR KWD-LOGIC-IN-COMMON-LISP NULL)
(CL:DEFVAR KWD-LOGIC-IN-FUNCTION NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-UNSET-FEATURE NULL)
(CL:DEFVAR KWD-LOGIC-IN-REALISTIC NULL)
(CL:DEFVAR KWD-LOGIC-IN-BYE NULL)
(CL:DEFVAR KWD-LOGIC-IN-EXIT NULL)
(CL:DEFVAR KWD-LOGIC-IN-HALT NULL)
(CL:DEFVAR KWD-LOGIC-IN-QUIT NULL)
(CL:DEFVAR KWD-LOGIC-IN-STOP NULL)
(CL:DEFVAR KWD-LOGIC-IN-DEFINE NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-DEFMODULE NULL)
(CL:DEFVAR SGT-LOGIC-IN-STELLA-CONS NULL)
(CL:DEFVAR KWD-LOGIC-IN-FINALIZE NULL)
(CL:DEFVAR KWD-LOGIC-IN-OPTIONS NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-LOAD NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-CLEAR-MODULE NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-DEFCLASS NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-DEFSLOT NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-DEFUN NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-DEFMETHOD NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-DEFCONCEPT NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-DEFFUNCTION NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-DEFRELATION NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-DEFOBJECT NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-DEFINSTANCE NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-DESTROY NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-IN-DIALECT NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-CC NULL)
(CL:DEFVAR KWD-LOGIC-IN-IMMEDIATE NULL)
(CL:DEFVAR KWD-LOGIC-IN-ALWAYS NULL)
(CL:DEFVAR KWD-LOGIC-IN-DEFERRED NULL)
(CL:DEFVAR KWD-LOGIC-IN-CHECK-DUPLICATES? NULL)
(CL:DEFVAR SGT-LOGIC-IN-STELLA-BOOLEAN NULL)
(CL:DEFVAR KWD-LOGIC-IN-MODULE NULL)
(CL:DEFVAR SGT-LOGIC-IN-STELLA-MODULE NULL)
(CL:DEFVAR KWD-LOGIC-IN-ASSERTION-MODULE NULL)
(CL:DEFVAR SGT-LOGIC-IN-STELLA-IDENTITY NULL)
(CL:DEFVAR KWD-LOGIC-IN-LOW NULL)
(CL:DEFVAR KWD-LOGIC-IN-MEDIUM NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-LOAD-DIRECTORY NULL)
(CL:DEFVAR KWD-LOGIC-IN-WHITE-SPACE NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-DEMO NULL)
(CL:DEFVAR KWD-LOGIC-IN-LEVEL NULL)
(CL:DEFVAR KWD-LOGIC-IN-NONE NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-TIME-COMMAND NULL)
(CL:DEFVAR KWD-LOGIC-IN-PORT NULL)
(CL:DEFVAR SGT-LOGIC-IN-STELLA-INTEGER NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-START-ONTOSAURUS NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-START-POWERLOOM-SERVER NULL)
(CL:DEFVAR KWD-LOGIC-IN-HOST NULL)
(CL:DEFVAR SGT-LOGIC-IN-STELLA-STRING NULL)
(CL:DEFVAR KWD-LOGIC-IN-DEBUG-LEVEL NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-START-POWERLOOM-GUI NULL)
(CL:DEFVAR KWD-LOGIC-IN-ERROR NULL)
(CL:DEFVAR KWD-LOGIC-IN-WARNING NULL)
(CL:DEFVAR SGT-LOGIC-IN-LOGIC-NAMED-DESCRIPTION NULL)
(CL:DEFVAR SGT-LOGIC-IN-LOGIC-PROPOSITION NULL)
(CL:DEFVAR SGT-LOGIC-IN-LOGIC-DESCRIPTION NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-MODULE-LOGIC-DIALECT NULL)
(CL:DEFVAR KWD-LOGIC-IN-KIF NULL)
(CL:DEFVAR SGT-LOGIC-IN-STELLA-RELATION NULL)
(CL:DEFVAR SGT-LOGIC-IN-LOGIC-LOGIC-OBJECT NULL)
(CL:DEFVAR KWD-LOGIC-IN-DEFINITION NULL)
(CL:DEFVAR KWD-LOGIC-IN-REDEFINITION NULL)
(CL:DEFVAR KWD-LOGIC-IN-PROPER-DEFINITION NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-OBJECT-AXIOMS NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-PROPOSITION-AXIOMS NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-SLOT-OPTION-KEYWORD NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-AND NULL)
(CL:DEFVAR SGT-LOGIC-IN-STELLA-THING NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-FORALL NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-NOT NULL)
(CL:DEFVAR KWD-LOGIC-IN-ASSERT-TRUE NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-BAD? NULL)
(CL:DEFVAR SYM-LOGIC-IN-PL-KERNEL-KB-NTH-DOMAIN NULL)
(CL:DEFVAR SYM-LOGIC-IN-PL-KERNEL-KB-DOMAIN NULL)
(CL:DEFVAR SYM-LOGIC-IN-PL-KERNEL-KB-RANGE NULL)
(CL:DEFVAR KWD-LOGIC-IN--> NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-?SELF NULL)
(CL:DEFVAR KWD-LOGIC-IN-=> NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-DEFPROPOSITION NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-DEFRULE NULL)
(CL:DEFVAR KWD-LOGIC-IN-CONCEIVE NULL)
(CL:DEFVAR KWD-LOGIC-IN-FORALL NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-SATELLITE-PROPOSITIONS NULL)
(CL:DEFVAR KWD-LOGIC-IN-CONFIDENCE-LEVEL NULL)
(CL:DEFVAR KWD-LOGIC-IN-DEFAULT NULL)
(CL:DEFVAR KWD-LOGIC-IN-PRESUME-TRUE NULL)
(CL:DEFVAR KWD-LOGIC-IN-FORWARD? NULL)
(CL:DEFVAR KWD-LOGIC-IN-FORWARD-ONLY? NULL)
(CL:DEFVAR KWD-LOGIC-IN-BACKWARD? NULL)
(CL:DEFVAR KWD-LOGIC-IN-BACKWARD-ONLY? NULL)
(CL:DEFVAR KWD-LOGIC-IN-WEIGHT NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-ABOUT NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-IN-MODULE NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-LIST-MODULES NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-METHOD-COMMAND? NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-DOCUMENTATION NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-HELP NULL)
(CL:DEFVAR SYM-LOGIC-IN-LOGIC-STARTUP-LOGIC-IN NULL)
(CL:DEFVAR SYM-LOGIC-IN-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM
 (CL:SPECIAL *STARTUP-TIME-PHASE* NULL-STRING-WRAPPER *WARNIFREDEFINE?*
  *STELLA-VERSION-STRING* *POWERLOOM-VERSION-STRING*
  *SKOLEM-ID-COUNTER* FALSE-WRAPPER *CHARACTER-UPCASE-TABLE*
  NULL-CHARACTER *CHARACTER-TYPE-TABLE* NULL-INTEGER *LOGIC-DIALECT*
  TRUE-WRAPPER *CURRENTFILENAME* *TRANSLATIONUNITS* *POWERLOOM-LOCK*
  *TRANSLATIONPHASE* STANDARD-INPUT *CONTEXT* *MODULE* NIL
  STANDARD-ERROR *ITERATIVE-DEEPENING-MODE?* *RECORD-JUSTIFICATIONS?*
  *JUST-IN-TIME-FORWARD-INFERENCE?* *EMIT-THINKING-DOTS?*
  STANDARD-OUTPUT EOL))

;;; (DEFGLOBAL *AVAILABLE-POWERLOOM-FEATURES* ...)

(CL:DEFVAR *AVAILABLE-POWERLOOM-FEATURES* NULL
  "List of PowerLoom environment features.")

;;; (DEFGLOBAL *CURRENT-POWERLOOM-FEATURES* ...)

(CL:DEFVAR *CURRENT-POWERLOOM-FEATURES* NULL
  "List of currently enabled PowerLoom environment features.")

;;; (DEFGLOBAL *DEFAULT-POWERLOOM-FEATURES* ...)

(CL:DEFVAR *DEFAULT-POWERLOOM-FEATURES* NULL
  "List of PowerLoom environment features enabled upon call to
'reset-features'.")

;;; (DEFUN PRINT-FEATURES ...)

(CL:DEFUN PRINT-FEATURES ()
  "Print the currently enabled and available PowerLoom environment features."
  (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
   "Currently enabled PowerLoom features:" EOL "   "
   *CURRENT-POWERLOOM-FEATURES* EOL EOL "Available PowerLoom features:"
   EOL "   " *AVAILABLE-POWERLOOM-FEATURES* EOL))

;;; (DEFUN (LIST-FEATURES LIST) ...)

(CL:DEFUN LIST-FEATURES ()
  "Return a list containing two lists, a list of currently enabled PowerLoom
features, and a list of all available PowerLoom features."
  (LIST *CURRENT-POWERLOOM-FEATURES* *AVAILABLE-POWERLOOM-FEATURES*))

;;; (DEFUN SET-POWERLOOM-FEATURE ...)

(CL:DEFUN SET-POWERLOOM-FEATURE (FEATURE)
  "Enable the PowerLoom environment feature `feature'."
  (CL:WHEN (CL:NOT (MEMBER? *CURRENT-POWERLOOM-FEATURES* FEATURE))
   (CL:COND
    ((CL:EQ FEATURE KWD-LOGIC-IN-TRACE-SUBGOALS) (CLEAR-CACHES)
     (%ADD-TRACE (CONS-LIST KWD-LOGIC-IN-GOAL-TREE)))
    ((CL:EQ FEATURE KWD-LOGIC-IN-TRACE-SOLUTIONS) (CLEAR-CACHES)
     (%ADD-TRACE (CONS-LIST KWD-LOGIC-IN-TRACE-SOLUTIONS)))
    ((CL:EQ FEATURE KWD-LOGIC-IN-TRACE-CLASSIFIER) (CLEAR-CACHES)
     (%ADD-TRACE (CONS-LIST KWD-LOGIC-IN-CLASSIFIER-INFERENCES)))
    ((CL:EQ FEATURE KWD-LOGIC-IN-CLOSED-WORLD))
    ((CL:EQ FEATURE KWD-LOGIC-IN-ITERATIVE-DEEPENING)
     (CL:SETQ *ITERATIVE-DEEPENING-MODE?* CL:T))
    ((CL:EQ FEATURE KWD-LOGIC-IN-JUSTIFICATIONS)
     (CL:SETQ *RECORD-JUSTIFICATIONS?* CL:T))
    ((CL:EQ FEATURE KWD-LOGIC-IN-JUST-IN-TIME-INFERENCE)
     (CL:SETQ *JUST-IN-TIME-FORWARD-INFERENCE?* CL:T))
    ((CL:EQ FEATURE KWD-LOGIC-IN-EMIT-THINKING-DOTS)
     (CL:SETQ *EMIT-THINKING-DOTS?* CL:T))
    (CL:T
     (CL:WARN "No such PowerLoom environment feature: `~A'" FEATURE)
     (PRINT-FEATURES) (CL:RETURN-FROM SET-POWERLOOM-FEATURE)))
   (INSERT *CURRENT-POWERLOOM-FEATURES* FEATURE)))

;;; (DEFUN (SET-FEATURE (LIST OF KEYWORD)) ...)

(CL:DEFUN %SET-FEATURE (FEATURES)
  "Enable the PowerLoom environment feature(s) named by `features'.
Return the list of enabled features.  Calling `set-feature' without any
arguments can be used to display the currently enabled features.
The following features are supported:

`just-in-time-inference': Enables interleaving of forward chaining inference
within backward chaining queries.

`iterative-deepening': Tells the query processor to use iterative deepening
instead of a depth-first search to find answers.  This is less efficient
but necessary for some kinds of highly recursive queries.

`trace-subgoals': Enables the generation of subgoaling trace information during
backchaining inference.

`trace-solutions': Prints newly found solutions during retrieval right when they
are generated as opposed to when the query terminates.

`trace-classifier': Tells the classifier to describe the inferences it draws.

`justifications': Enables the generation of justifications during inference,
which is a prerequiste for the generation of explanations with `(why)'.

`emit-thinking-dots': Tells PowerLoom to annotate its inference progress by
outputting characters indicating the completion of individual reasoning steps.

By default, the features `emit-thinking-dots' and `just-in-time-inference'
are enabled, and the others are disabled.
"
  (CL:HANDLER-CASE
   (CL:LET* ((FEATURENAME NULL) (ITER-000 FEATURES))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ FEATURENAME (%%VALUE ITER-000))
     (SET-POWERLOOM-FEATURE
      (KEYWORDIFY (COERCE-TO-STRING FEATURENAME)))
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   (LOGIC-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     (EXCEPTION-MESSAGE E))))
  *CURRENT-POWERLOOM-FEATURES*)

(CL:DEFUN SET-FEATURE-EVALUATOR-WRAPPER (ARGUMENTS)
  (%SET-FEATURE ARGUMENTS))

(CL:DEFMACRO SET-FEATURE (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Enable the PowerLoom environment feature(s) named by `features'.
Return the list of enabled features.  Calling `set-feature' without any
arguments can be used to display the currently enabled features.
The following features are supported:

`just-in-time-inference': Enables interleaving of forward chaining inference
within backward chaining queries.

`iterative-deepening': Tells the query processor to use iterative deepening
instead of a depth-first search to find answers.  This is less efficient
but necessary for some kinds of highly recursive queries.

`trace-subgoals': Enables the generation of subgoaling trace information during
backchaining inference.

`trace-solutions': Prints newly found solutions during retrieval right when they
are generated as opposed to when the query terminates.

`trace-classifier': Tells the classifier to describe the inferences it draws.

`justifications': Enables the generation of justifications during inference,
which is a prerequiste for the generation of explanations with `(why)'.

`emit-thinking-dots': Tells PowerLoom to annotate its inference progress by
outputting characters indicating the completion of individual reasoning steps.

By default, the features `emit-thinking-dots' and `just-in-time-inference'
are enabled, and the others are disabled.
"
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/SET-FEATURE|)) (CL:MACRO-FUNCTION (CL:QUOTE SET-FEATURE)))

;;; (DEFUN UNSET-POWERLOOM-FEATURE ...)

(CL:DEFUN UNSET-POWERLOOM-FEATURE (FEATURE)
  "Disable the PowerLoom environment feature `feature'."
  (CL:IF (MEMBER? *CURRENT-POWERLOOM-FEATURES* FEATURE)
   (CL:COND
    ((CL:EQ FEATURE KWD-LOGIC-IN-TRACE-SUBGOALS)
     (%DROP-TRACE (CONS-LIST KWD-LOGIC-IN-GOAL-TREE)))
    ((CL:EQ FEATURE KWD-LOGIC-IN-TRACE-SOLUTIONS)
     (%DROP-TRACE (CONS-LIST KWD-LOGIC-IN-TRACE-SOLUTIONS)))
    ((CL:EQ FEATURE KWD-LOGIC-IN-TRACE-CLASSIFIER)
     (%DROP-TRACE (CONS-LIST KWD-LOGIC-IN-CLASSIFIER-INFERENCES)))
    ((CL:EQ FEATURE KWD-LOGIC-IN-CLOSED-WORLD))
    ((CL:EQ FEATURE KWD-LOGIC-IN-ITERATIVE-DEEPENING)
     (CL:SETQ *ITERATIVE-DEEPENING-MODE?* CL:NIL))
    ((CL:EQ FEATURE KWD-LOGIC-IN-JUSTIFICATIONS)
     (CL:SETQ *RECORD-JUSTIFICATIONS?* CL:NIL))
    ((CL:EQ FEATURE KWD-LOGIC-IN-JUST-IN-TIME-INFERENCE)
     (CL:SETQ *JUST-IN-TIME-FORWARD-INFERENCE?* CL:NIL))
    ((CL:EQ FEATURE KWD-LOGIC-IN-EMIT-THINKING-DOTS)
     (CL:SETQ *EMIT-THINKING-DOTS?* CL:NIL))
    (CL:T
     (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" FEATURE
       "' is not a valid case option")
      (CL:ERROR
       (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
   (CL:WHEN (CL:NOT (MEMBER? *AVAILABLE-POWERLOOM-FEATURES* FEATURE))
    (CL:WARN "No such PowerLoom environment feature: `~A'" FEATURE)
    (PRINT-FEATURES)))
  (REMOVE *CURRENT-POWERLOOM-FEATURES* FEATURE))

;;; (DEFUN (UNSET-FEATURE (LIST OF KEYWORD)) ...)

(CL:DEFUN %UNSET-FEATURE (FEATURES)
  "Disable the PowerLoom environment feature(s) named by `features'.
Return the list of enabled features.  Calling `unset-feature' without any
arguments can be used to display the currently enabled features.
See `set-feature' for a description of supported features."
  (CL:HANDLER-CASE
   (CL:LET* ((FEATURENAME NULL) (ITER-000 FEATURES))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ FEATURENAME (%%VALUE ITER-000))
     (UNSET-POWERLOOM-FEATURE
      (KEYWORDIFY (COERCE-TO-STRING FEATURENAME)))
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   (LOGIC-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     (EXCEPTION-MESSAGE E))))
  *CURRENT-POWERLOOM-FEATURES*)

(CL:DEFUN UNSET-FEATURE-EVALUATOR-WRAPPER (ARGUMENTS)
  (%UNSET-FEATURE ARGUMENTS))

(CL:DEFMACRO UNSET-FEATURE (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Disable the PowerLoom environment feature(s) named by `features'.
Return the list of enabled features.  Calling `unset-feature' without any
arguments can be used to display the currently enabled features.
See `set-feature' for a description of supported features."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/UNSET-FEATURE|)) (CL:MACRO-FUNCTION (CL:QUOTE UNSET-FEATURE)))

;;; (DEFUN (RESET-FEATURES (LIST OF KEYWORD)) ...)

(CL:DEFUN RESET-FEATURES ()
  "Reset the PowerLoom environment features to their default settings."
  (CL:LET*
   ((F NULL)
    (ITER-000 (%THE-CONS-LIST (COPY *CURRENT-POWERLOOM-FEATURES*))))
   (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
    (CL:SETQ F (%%VALUE ITER-000))
    (CL:WHEN (CL:NOT (MEMBER? *DEFAULT-POWERLOOM-FEATURES* F))
     (UNSET-POWERLOOM-FEATURE F))
    (CL:SETQ ITER-000 (%%REST ITER-000))))
  (CL:LET*
   ((F NULL) (ITER-001 (%THE-CONS-LIST *DEFAULT-POWERLOOM-FEATURES*)))
   (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
    (CL:SETQ F (%%VALUE ITER-001))
    (CL:WHEN (CL:NOT (MEMBER? *CURRENT-POWERLOOM-FEATURES* F))
     (SET-POWERLOOM-FEATURE F))
    (CL:SETQ ITER-001 (%%REST ITER-001))))
  *CURRENT-POWERLOOM-FEATURES*)

;;; (DEFUN (ENABLED-POWERLOOM-FEATURE? BOOLEAN) ...)

(CL:DEFUN ENABLED-POWERLOOM-FEATURE? (FEATURE)
  "Return true if the STELLA `feature' is currently enabled."
  (MEMB? *CURRENT-POWERLOOM-FEATURES* FEATURE))

;;; (DEFUN (DISABLED-POWERLOOM-FEATURE? BOOLEAN) ...)

(CL:DEFUN DISABLED-POWERLOOM-FEATURE? (FEATURE)
  "Return true if the STELLA `feature' is currently disabled."
  (CL:NOT (MEMB? *CURRENT-POWERLOOM-FEATURES* FEATURE)))

;;; (DEFUN (PARSE-LOGIC-COMMAND-OPTIONS PROPERTY-LIST) ...)

(CL:DEFUN PARSE-LOGIC-COMMAND-OPTIONS (OPTIONS |LEGALOPTIONS&TYPES| COERCIONERROR? ALLOWOTHERKEYS?)
  "This is simply a wrapper to `parse-options' (which see).
We keep this alias in case we ever want to add any logic-specific extensions."
  (PARSE-OPTIONS OPTIONS |LEGALOPTIONS&TYPES| COERCIONERROR?
   ALLOWOTHERKEYS?))

;;; (DEFGLOBAL *LOGIC-PROMPT* ...)

(CL:DEFVAR *LOGIC-PROMPT* "|= "
  "The prompt used by the PowerLoom listener.")
(CL:DECLAIM (CL:TYPE CL:SIMPLE-STRING *LOGIC-PROMPT*))

;;; (DEFSPECIAL *PROMPT-SHOW-MODULE?* ...)

(CL:DEFVAR *PROMPT-SHOW-MODULE?* CL:T
  "Flag to control whether the logic prompt shows the module name.")

;;; (DEFUN PRINT-LOGIC-PROMPT ...)

(CL:DEFUN PRINT-LOGIC-PROMPT ()
  (CL:WHEN *PROMPT-SHOW-MODULE?*
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
    (%MODULE-NAME *MODULE*) " "))
  (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) *LOGIC-PROMPT*))

;;; (DEFGLOBAL *LOGIC-COMMAND-RESULT-INDENT* ...)

(CL:DEFVAR *LOGIC-COMMAND-RESULT-INDENT* "")
(CL:DECLAIM (CL:TYPE CL:SIMPLE-STRING *LOGIC-COMMAND-RESULT-INDENT*))

;;; (DEFUN PRINT-LOGIC-COMMAND-RESULT ...)

(CL:DEFUN PRINT-LOGIC-COMMAND-RESULT (RESULT)
  (CL:LET* ((TEMP-000 (LOOKUP-CONSTRAINT-PROPAGATION-WORLD *CONTEXT*)))
   (CL:LET*
    ((PRINTCONTEXT
      (CL:IF (CL:NOT (CL:EQ TEMP-000 NULL)) TEMP-000 *CONTEXT*)))
    (CL:LET*
     ((*PRINTMODE* KWD-LOGIC-IN-REALISTIC)
      (*PRETTYPRINTLOGICALFORMS?* CL:T) (*CONTEXT* PRINTCONTEXT))
     (CL:DECLARE
      (CL:SPECIAL *PRINTMODE* *PRETTYPRINTLOGICALFORMS?* *CONTEXT*))
     (CL:WHEN (CL:NOT (CL:EQ RESULT NULL))
      (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
       *LOGIC-COMMAND-RESULT-INDENT* RESULT EOL))))))

;;; (DEFSPECIAL *CONFIRM-INTERACTIVE-EXIT?* ...)

(CL:DEFVAR *CONFIRM-INTERACTIVE-EXIT?* FALSE
  "If TRUE exiting from the logic-command loop (or PowerLoom
listener) will be protected by a confirmation dialog.  This is mainly useful
for C++ and Java where exiting the listener will also exit the program.")

;;; (DEFUN (LOGIC-COMMAND-LOOP-EXIT? BOOLEAN BOOLEAN) ...)

(CL:DEFUN LOGIC-COMMAND-LOOP-EXIT? (COMMAND)
  (CL:LET* ((EXIT? CL:NIL))
   (CL:LET* ((TEST-VALUE-001 (SAFE-PRIMARY-TYPE COMMAND)))
    (CL:COND
     ((SUBTYPE-OF-KEYWORD? TEST-VALUE-001)
      (CL:PROGN
       (CL:COND
        ((CL:OR (CL:EQ COMMAND KWD-LOGIC-IN-BYE)
          (CL:EQ COMMAND KWD-LOGIC-IN-EXIT)
          (CL:EQ COMMAND KWD-LOGIC-IN-HALT)
          (CL:EQ COMMAND KWD-LOGIC-IN-QUIT)
          (CL:EQ COMMAND KWD-LOGIC-IN-STOP))
         (CL:SETQ EXIT? CL:T))
        (CL:T))))
     ((SUBTYPE-OF-SYMBOL? TEST-VALUE-001)
      (CL:PROGN
       (CL:LET* ((TEST-VALUE-000 (%SYMBOL-NAME COMMAND)))
        (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEST-VALUE-000))
        (CL:COND
         ((CL:OR (STRING-EQL? TEST-VALUE-000 "BYE")
           (STRING-EQL? TEST-VALUE-000 "EXIT")
           (STRING-EQL? TEST-VALUE-000 "HALT")
           (STRING-EQL? TEST-VALUE-000 "QUIT")
           (STRING-EQL? TEST-VALUE-000 "STOP")
           (STRING-EQL? TEST-VALUE-000 "bye")
           (STRING-EQL? TEST-VALUE-000 "exit")
           (STRING-EQL? TEST-VALUE-000 "halt")
           (STRING-EQL? TEST-VALUE-000 "quit")
           (STRING-EQL? TEST-VALUE-000 "stop"))
          (CL:SETQ EXIT? CL:T))
         (CL:T)))))
     (CL:T)))
   (CL:WHEN (CL:AND EXIT? *CONFIRM-INTERACTIVE-EXIT?*)
    (CL:SETQ EXIT? (YES-OR-NO? "Really exit? (yes or no) "))
    (CL:WHEN EXIT?
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL))
    (CL:RETURN-FROM LOGIC-COMMAND-LOOP-EXIT? (CL:VALUES EXIT? CL:T)))
   (CL:VALUES EXIT? EXIT?)))

;;; (DEFUN LOGIC-COMMAND-LOOP ...)

(CL:DEFUN LOGIC-COMMAND-LOOP (MODULE)
  (CL:LET*
   ((COMMAND NULL) (RESULT NULL) (EOF? CL:NIL) (EXIT? CL:NIL)
    (EXITCOMMAND? CL:NIL))
   (CL:LET*
    ((*MODULE* (CL:IF (CL:NOT (CL:EQ MODULE NULL)) MODULE *MODULE*))
     (*CONTEXT* *MODULE*))
    (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
    (CLEAR-INPUT STANDARD-INPUT)
    (CL:LOOP
     (CL:TAGBODY
      (CL:HANDLER-CASE
       (CL:PROGN (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL)
        (PRINT-LOGIC-PROMPT)
        (CL:MULTIPLE-VALUE-SETQ (COMMAND EOF?)
         (READ-S-EXPRESSION STANDARD-INPUT))
        (CL:WHEN EOF?
         (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
          "End of File encountered.  Exiting." EOL)
         (CL:RETURN))
        (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL)
        (CL:MULTIPLE-VALUE-SETQ (EXIT? EXITCOMMAND?)
         (LOGIC-COMMAND-LOOP-EXIT? COMMAND))
        (CL:WHEN EXIT? (CL:RETURN))
        (CL:WHEN EXITCOMMAND? (CL:GO :CONTINUE))
        (CL:SETQ RESULT (EVALUATE-LOGIC-COMMAND COMMAND CL:NIL))
        (PRINT-LOGIC-COMMAND-RESULT RESULT))
       (LOGIC-EXCEPTION (LE)
        (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR) ">> Error: "
         (EXCEPTION-MESSAGE LE)))
       (STELLA-EXCEPTION (E)
        (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
         ">> Internal Error: " (EXCEPTION-MESSAGE E))
        (PRINT-EXCEPTION-CONTEXT E STANDARD-ERROR)))
      :CONTINUE)))))

;;; (DEFUN (EVALUATE-LOGIC-COMMAND OBJECT) ...)

(CL:DEFUN EVALUATE-LOGIC-COMMAND (COMMAND FINALIZE?)
  (CL:LET*
   ((*TRANSLATIONERRORS* 0) (*TRANSLATIONWARNINGS* 0)
    (*IGNORETRANSLATIONERRORS?* CL:NIL) (*TRANSLATIONUNITS* NULL)
    (*TRANSLATIONPHASE* KWD-LOGIC-IN-DEFINE) (*EVALUATIONTREE* NULL))
   (CL:DECLARE
    (CL:SPECIAL *TRANSLATIONERRORS* *TRANSLATIONWARNINGS*
     *IGNORETRANSLATIONERRORS?* *TRANSLATIONUNITS* *TRANSLATIONPHASE*
     *EVALUATIONTREE*))
   (CL:DECLARE
    (CL:TYPE CL:FIXNUM *TRANSLATIONERRORS* *TRANSLATIONWARNINGS*))
   (CL:LET*
    ((OPERATOR NULL) (OPERATORNAME STELLA::NULL-STRING) (RESULT NULL))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING OPERATORNAME))
    (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE COMMAND)))
     (CL:COND
      ((CL:EQ TEST-VALUE-000 SGT-LOGIC-IN-STELLA-CONS)
       (CL:PROGN (CL:SETQ OPERATOR (%%VALUE COMMAND))
        (CL:COND
         ((SUBTYPE-OF-SYMBOL? (SAFE-PRIMARY-TYPE OPERATOR))
          (CL:PROGN (CL:SETQ OPERATORNAME (%SYMBOL-NAME OPERATOR))
           (CL:WHEN (STRING-EQUAL? OPERATORNAME "DEFMODULE")
            (CL:SETQ OPERATOR SYM-LOGIC-IN-STELLA-DEFMODULE)
            (CL:SETF (%%VALUE COMMAND) OPERATOR))
           (CL:COND
            ((STRING-EQUAL? OPERATORNAME "IN-MODULE")
             (HANDLE-IN-MODULE-TREE COMMAND CL:NIL CL:NIL))
            ((STRING-EQUAL? OPERATORNAME "IN-PACKAGE"))
            ((DECLARATION-TREE? COMMAND)
             (CL:SETQ *TRANSLATIONUNITS* (LIST))
             (WALK-TOP-LEVEL-TREE COMMAND CL:NIL)
             (CL:CASE (LENGTH (REVERSE *TRANSLATIONUNITS*))
              (0
               (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
                (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
                 "Translation failed: `" COMMAND "'")
                (CL:ERROR
                 (NEW-EVALUATION-EXCEPTION
                  (THE-STRING-READER STREAM-000)))))
              (1
               (CL:SETQ RESULT
                (%THE-OBJECT (FIRST *TRANSLATIONUNITS*))))
              (CL:OTHERWISE
               (CL:LET* ((RESULTS NIL))
                (CL:LET*
                 ((UNIT NULL)
                  (ITER-000 (%THE-CONS-LIST *TRANSLATIONUNITS*))
                  (COLLECT-000 NULL))
                 (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
                  (CL:SETQ UNIT (%%VALUE ITER-000))
                  (CL:IF (CL:EQ COLLECT-000 NULL)
                   (CL:PROGN
                    (CL:SETQ COLLECT-000 (CONS (%THE-OBJECT UNIT) NIL))
                    (CL:IF (CL:EQ RESULTS NIL)
                     (CL:SETQ RESULTS COLLECT-000)
                     (ADD-CONS-TO-END-OF-CONS-LIST RESULTS
                      COLLECT-000)))
                   (CL:PROGN
                    (CL:SETF (%%REST COLLECT-000)
                     (CONS (%THE-OBJECT UNIT) NIL))
                    (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
                  (CL:SETQ ITER-000 (%%REST ITER-000))))
                (CL:SETQ RESULT RESULTS)))))
            (CL:T
             (WITH-PROCESS-LOCK *POWERLOOM-LOCK*
              (CL:SETQ RESULT (%EVALUATE COMMAND)))))))
         (CL:T
          (WITH-PROCESS-LOCK *POWERLOOM-LOCK*
           (CL:SETQ RESULT (%EVALUATE COMMAND)))))))
      ((SUBTYPE-OF-KEYWORD? TEST-VALUE-000)
       (CL:PROGN (CL:SETQ RESULT COMMAND)))
      ((SUBTYPE-OF-SURROGATE? TEST-VALUE-000)
       (CL:PROGN (CL:SETQ RESULT COMMAND)))
      (CL:T
       (WITH-PROCESS-LOCK *POWERLOOM-LOCK*
        (CL:SETQ RESULT (%EVALUATE COMMAND))))))
    (CL:WHEN (CL:AND (CL:NOT (TRANSLATION-ERRORS?)) FINALIZE?)
     (CL:SETQ *TRANSLATIONPHASE* KWD-LOGIC-IN-FINALIZE)
     (FINALIZE-OBJECTS))
    RESULT)))

;;; (DEFGLOBAL *POWERLOOM-KB-FILE-EXTENSIONS* ...)

(CL:DEFVAR *POWERLOOM-KB-FILE-EXTENSIONS* NULL
  "If the extension of a KB file is unspecified in a
`load' or `demo' command, try to find it with one of these extensions.")

;;; (DEFSPECIAL *ASSERTION-MODULE* ...)

(CL:DEFVAR *ASSERTION-MODULE* NULL
  "If non-NULL, definition axioms and assertions will be evaluated
in this module instead of the IN-MODULE of a file, which allows us to separate
vocabulary definitions and their definitional constraints.")

;;; (DEFUN LOAD ...)

(CL:DEFUN %LOAD (FILE OPTIONS)
  "Read logic commands from `file' and evaluate them.
By default, this will check for each asserted proposition whether an
equivalent proposition already exists and, if so, not assert the
duplicate.  These duplicate checks are somewhat expensive though and
can be skipped by setting the option :check-duplicates? to false.
This can save time when loading large KBs where it is known that no
duplicate assertions exist in a file.

Also, by setting the :module option, the module in which the file
contents will be loaded will be set.  This will only affect files
that do NOT have an `in-module' declaration as part of the file.
If this is not set, and no `in-module' declaration is in the file,
the file will be loaded into the current module.

The option :assertion-module can be used to have assertions and
definitional axioms be asserted in a different module than the
top-level module where definitions are evaluated.  This is useful
in some cases where vocabulary definitions and their associated
axioms and assertions need to be separate for inference or efficiency
reasons.  The assertion module can be given as a name in case it is
defined in the loaded file.  Obviously, it needs to be a child of the
top-level module where vocabulary definitions are created.

Loading is done in two passes: in the first pass all definitional
commands such as `defmodule', `defconcept', etc. are evaluated but not
yet finalized, that is, their definitional axioms are parsed but not
yet asserted.  In the second pass all definitional commands are finalized
and then all commands in the file are executed in order (which will be
no-ops for the definitions already processed).  This scheme tries to
maintain some order independence for the commands in the file, since
relation definitions need to be performed before they can be used in
assertions.  At any point `process-definitions' can be called to finalize
all unfinalized definitions queued up so far.  Future versions might also
support a :one-pass? option for added efficiency."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING FILE))
  #+MCL
  (CL:CHECK-TYPE FILE CL:SIMPLE-STRING)
  (CL:LET*
   ((TEMP-000
     (%FIND-FILE-IN-LOAD-PATH FILE *POWERLOOM-KB-FILE-EXTENSIONS*)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEMP-000))
   (CL:SETQ FILE
    (CL:IF (CL:NOT (CL:EQ TEMP-000 STELLA::NULL-STRING)) TEMP-000
     FILE)))
  (ENSURE-FILE-EXISTS FILE "load")
  (CL:LET*
   ((TOPLEVELINVOCATION?
     (CL:EQ *CURRENTFILENAME* STELLA::NULL-STRING)))
   (CL:LET*
    ((*CURRENTLOADFILE* FILE)
     (*CURRENTFILENAME* (FILE-BASE-NAME FILE)))
    (CL:DECLARE (CL:SPECIAL *CURRENTLOADFILE* *CURRENTFILENAME*))
    (CL:DECLARE
     (CL:TYPE CL:SIMPLE-STRING *CURRENTLOADFILE* *CURRENTFILENAME*))
    (CL:LET* ((INPUTSTREAM NULL))
     (CL:UNWIND-PROTECT
      (CL:PROGN (CL:SETQ INPUTSTREAM (OPEN-INPUT-FILE FILE))
       (LOAD-STREAM INPUTSTREAM KWD-LOGIC-IN-OPTIONS OPTIONS))
      (CL:WHEN (CL:NOT (CL:EQ INPUTSTREAM NULL)) (FREE INPUTSTREAM)))))
   (CL:WHEN TOPLEVELINVOCATION? (SWEEP-TRANSIENTS))))

(CL:DEFUN LOAD-EVALUATOR-WRAPPER (ARGUMENTS)
  (%LOAD (%WRAPPER-VALUE (%%VALUE ARGUMENTS)) (%%REST ARGUMENTS)))

(CL:DEFMACRO LOAD (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Read logic commands from `file' and evaluate them.
By default, this will check for each asserted proposition whether an
equivalent proposition already exists and, if so, not assert the
duplicate.  These duplicate checks are somewhat expensive though and
can be skipped by setting the option :check-duplicates? to false.
This can save time when loading large KBs where it is known that no
duplicate assertions exist in a file.

Also, by setting the :module option, the module in which the file
contents will be loaded will be set.  This will only affect files
that do NOT have an `in-module' declaration as part of the file.
If this is not set, and no `in-module' declaration is in the file,
the file will be loaded into the current module.

The option :assertion-module can be used to have assertions and
definitional axioms be asserted in a different module than the
top-level module where definitions are evaluated.  This is useful
in some cases where vocabulary definitions and their associated
axioms and assertions need to be separate for inference or efficiency
reasons.  The assertion module can be given as a name in case it is
defined in the loaded file.  Obviously, it needs to be a child of the
top-level module where vocabulary definitions are created.

Loading is done in two passes: in the first pass all definitional
commands such as `defmodule', `defconcept', etc. are evaluated but not
yet finalized, that is, their definitional axioms are parsed but not
yet asserted.  In the second pass all definitional commands are finalized
and then all commands in the file are executed in order (which will be
no-ops for the definitions already processed).  This scheme tries to
maintain some order independence for the commands in the file, since
relation definitions need to be performed before they can be used in
assertions.  At any point `process-definitions' can be called to finalize
all unfinalized definitions queued up so far.  Future versions might also
support a :one-pass? option for added efficiency."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/STELLA/LOAD|)) (CL:MACRO-FUNCTION (CL:QUOTE LOAD)))

;;; (DEFUN (DEFINITION-NAME? BOOLEAN) ...)

(CL:DEFUN DEFINITION-NAME? (NAME)
  (CL:LET* ((NAME-STRING (%SYMBOL-NAME NAME)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING NAME-STRING))
   (CL:AND (CL:> (CL:THE CL:FIXNUM (CL:LENGTH NAME-STRING)) 2)
    (CL:EQL
     (CL:LET ((SELF NAME-STRING) (POSITION 0))
      (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
       (CL:TYPE CL:FIXNUM POSITION))
      (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
       (CL:THE CL:FIXNUM POSITION)))
     #\D)
    (CL:EQL
     (CL:LET ((SELF NAME-STRING) (POSITION 1))
      (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
       (CL:TYPE CL:FIXNUM POSITION))
      (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
       (CL:THE CL:FIXNUM POSITION)))
     #\E)
    (CL:EQL
     (CL:LET ((SELF NAME-STRING) (POSITION 2))
      (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
       (CL:TYPE CL:FIXNUM POSITION))
      (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
       (CL:THE CL:FIXNUM POSITION)))
     #\F))))

;;; (DEFUN (LOAD-COMMAND-EVAL-PHASE KEYWORD) ...)

(CL:DEFUN LOAD-COMMAND-EVAL-PHASE (TREE)
  "Analyze a command `tree' in a load file and determine when it should be processed."
  (CL:COND
   ((CL:EQ (SAFE-PRIMARY-TYPE TREE) SGT-LOGIC-IN-STELLA-CONS)
    (CL:PROGN
     (CL:LET* ((OPERATOR (%%VALUE TREE)))
      (CL:COND
       ((SUBTYPE-OF-SYMBOL? (SAFE-PRIMARY-TYPE OPERATOR))
        (CL:PROGN
         (CL:COND
          ((CL:OR (CL:EQ OPERATOR SYM-LOGIC-IN-STELLA-DEFMODULE)
            (CL:EQ OPERATOR SYM-LOGIC-IN-STELLA-CLEAR-MODULE)
            (CL:EQ OPERATOR SYM-LOGIC-IN-STELLA-DEFCLASS)
            (CL:EQ OPERATOR SYM-LOGIC-IN-STELLA-DEFSLOT)
            (CL:EQ OPERATOR SYM-LOGIC-IN-STELLA-DEFUN)
            (CL:EQ OPERATOR SYM-LOGIC-IN-STELLA-DEFMETHOD)
            (CL:EQ OPERATOR SYM-LOGIC-IN-LOGIC-DEFCONCEPT)
            (CL:EQ OPERATOR SYM-LOGIC-IN-LOGIC-DEFFUNCTION)
            (CL:EQ OPERATOR SYM-LOGIC-IN-LOGIC-DEFRELATION)
            (CL:EQ OPERATOR SYM-LOGIC-IN-LOGIC-DEFOBJECT)
            (CL:EQ OPERATOR SYM-LOGIC-IN-LOGIC-DEFINSTANCE)
            (CL:EQ OPERATOR SYM-LOGIC-IN-LOGIC-DESTROY))
           (CL:RETURN-FROM LOAD-COMMAND-EVAL-PHASE
            KWD-LOGIC-IN-IMMEDIATE))
          ((CL:OR (CL:EQ OPERATOR SYM-LOGIC-IN-LOGIC-IN-DIALECT)
            (CL:EQ OPERATOR SYM-LOGIC-IN-STELLA-CC))
           (CL:RETURN-FROM LOAD-COMMAND-EVAL-PHASE
            KWD-LOGIC-IN-ALWAYS))
          (CL:T
           (CL:WHEN
            (CL:AND (CL:NOT (DEFINITION-NAME? OPERATOR))
             (CL:NOT (CL:EQ (LOOKUP-COMMAND OPERATOR) NULL)))
            (CL:RETURN-FROM LOAD-COMMAND-EVAL-PHASE
             KWD-LOGIC-IN-DEFERRED))))))
       (CL:T)))))
   (CL:T))
  KWD-LOGIC-IN-IMMEDIATE)

;;; (DEFUN LOAD-STREAM ...)

(CL:DEFUN LOAD-STREAM (STREAM CL:&REST OPTIONS)
  "Read logic commands from `stream' and evaluate them.
Does the actual work for `load' (which see for a description of options)."
  (CL:LET* ((ARGLIST-000 NIL))
   (CL:LET* ((ARG-000 NULL) (ITER-000 OPTIONS) (COLLECT-000 NULL))
    (CL:LOOP WHILE ITER-000 DO (CL:SETQ ARG-000 (CL:POP ITER-000))
     (CL:IF (CL:EQ COLLECT-000 NULL)
      (CL:PROGN (CL:SETQ COLLECT-000 (CONS ARG-000 NIL))
       (CL:IF (CL:EQ ARGLIST-000 NIL) (CL:SETQ ARGLIST-000 COLLECT-000)
        (ADD-CONS-TO-END-OF-CONS-LIST ARGLIST-000 COLLECT-000)))
      (CL:PROGN (CL:SETF (%%REST COLLECT-000) (CONS ARG-000 NIL))
       (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))))
   (CL:LET*
    ((THEOPTIONS
      (PARSE-LOGIC-COMMAND-OPTIONS ARGLIST-000
       (LIST* KWD-LOGIC-IN-CHECK-DUPLICATES?
        SGT-LOGIC-IN-STELLA-BOOLEAN KWD-LOGIC-IN-MODULE
        SGT-LOGIC-IN-STELLA-MODULE KWD-LOGIC-IN-ASSERTION-MODULE
        SGT-LOGIC-IN-STELLA-IDENTITY NIL)
       CL:T CL:NIL))
     (CURRENTDIALECT *LOGIC-DIALECT*)
     (LOADMODULE
      (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-LOGIC-IN-MODULE *MODULE*))
     (SKIPCOMMAND? CL:NIL)
     (SEENINMODULE? (CL:NOT (CL:EQ LOADMODULE NULL))) (COMMANDS NIL))
    (CL:LET*
     ((*DONT-CHECK-FOR-DUPLICATE-PROPOSITIONS?*
       (CL:NOT
        (COERCE-WRAPPED-BOOLEAN-TO-BOOLEAN
         (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-LOGIC-IN-CHECK-DUPLICATES?
          TRUE-WRAPPER))))
      (*ASSERTION-MODULE* NULL) (*LOGIC-DIALECT* CURRENTDIALECT)
      (*TRANSLATIONERRORS* 0) (*TRANSLATIONWARNINGS* 0)
      (*TRANSLATIONNOTES* 0))
     (CL:DECLARE
      (CL:SPECIAL *DONT-CHECK-FOR-DUPLICATE-PROPOSITIONS?*
       *ASSERTION-MODULE* *LOGIC-DIALECT* *TRANSLATIONERRORS*
       *TRANSLATIONWARNINGS* *TRANSLATIONNOTES*))
     (CL:DECLARE
      (CL:TYPE CL:FIXNUM *TRANSLATIONERRORS* *TRANSLATIONWARNINGS*
       *TRANSLATIONNOTES*))
     (CL:LET* ((*MODULE* LOADMODULE) (*CONTEXT* *MODULE*))
      (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
      (CL:LET* ((TREE NULL) (ITER-001 (S-EXPRESSIONS STREAM)))
       (CL:LOOP WHILE (NEXT? ITER-001) DO
        (CL:SETQ TREE (%VALUE ITER-001))
        (CL:TAGBODY
         (CL:WHEN (CONS? TREE)
          (CL:MULTIPLE-VALUE-SETQ (SKIPCOMMAND? SEENINMODULE?)
           (HANDLE-IN-MODULE-TREE TREE SEENINMODULE? CL:NIL))
          (CL:WHEN SKIPCOMMAND? (CL:GO :CONTINUE)))
         (CL:LET* ((TEST-VALUE-000 (LOAD-COMMAND-EVAL-PHASE TREE)))
          (CL:COND
           ((CL:EQ TEST-VALUE-000 KWD-LOGIC-IN-IMMEDIATE)
            (EVALUATE-LOGIC-COMMAND TREE CL:NIL))
           ((CL:EQ TEST-VALUE-000 KWD-LOGIC-IN-ALWAYS)
            (EVALUATE-LOGIC-COMMAND TREE CL:NIL)
            (CL:SETQ COMMANDS (CONS TREE COMMANDS)))
           ((CL:EQ TEST-VALUE-000 KWD-LOGIC-IN-DEFERRED)
            (CL:SETQ COMMANDS (CONS TREE COMMANDS)))
           (CL:T
            (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
             (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`"
              TEST-VALUE-000 "' is not a valid case option")
             (CL:ERROR
              (NEW-STELLA-EXCEPTION
               (THE-STRING-READER STREAM-000)))))))
         :CONTINUE)))
      (CL:WHEN
       (CL:NOT
        (CL:EQ (LOOKUP THEOPTIONS KWD-LOGIC-IN-ASSERTION-MODULE) NULL))
       (CL:SETQ *ASSERTION-MODULE*
        (COERCE-TO-MODULE
         (LOOKUP THEOPTIONS KWD-LOGIC-IN-ASSERTION-MODULE) CL:T))
       (CL:SETQ *MODULE* *ASSERTION-MODULE*)
       (CL:SETQ *CONTEXT* *ASSERTION-MODULE*))
      (CL:LET* ((*TRANSLATIONPHASE* KWD-LOGIC-IN-FINALIZE))
       (CL:DECLARE (CL:SPECIAL *TRANSLATIONPHASE*)) (FINALIZE-OBJECTS))
      (CL:LET* ((TREE NULL) (ITER-002 (REVERSE COMMANDS)))
       (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-002 NIL)) DO
        (CL:SETQ TREE (%%VALUE ITER-002))
        (CL:WHEN (CL:NOT (CL:EQ *ASSERTION-MODULE* NULL))
         (CL:SETQ *MODULE* *ASSERTION-MODULE*)
         (CL:SETQ *CONTEXT* *ASSERTION-MODULE*))
        (EVALUATE-LOGIC-COMMAND TREE CL:T)
        (CL:SETQ ITER-002 (%%REST ITER-002)))))
     (CL:WHEN (CL:NOT (IGNORE-TRANSLATION-ERRORS?))
      (SUMMARIZE-TRANSLATION-ERRORS))))))

;;; (DEFUN LOAD-STREAM-IN-MODULE ...)

(CL:DEFUN LOAD-STREAM-IN-MODULE (STREAM MODULE)
  "Read logic commands from `stream' and evaluate them in `module'.
This is a backwards-compatibility wrapper.  Note that `module' will not override
any `in-module' declarations in `stream'."
  (LOAD-STREAM STREAM KWD-LOGIC-IN-MODULE MODULE))

;;; (DEFUN LOAD-DIRECTORY ...)

(CL:DEFUN %LOAD-DIRECTORY (DIRECTORY)
  "Load all PowerLoom files (*.plm) in `directory' in alphabetic sort order."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING DIRECTORY))
  #+MCL
  (CL:CHECK-TYPE DIRECTORY CL:SIMPLE-STRING)
  (PL-LOG KWD-LOGIC-IN-LOW
   (WRAP-STRING "Loading PowerLoom files from directory ")
   (WRAP-STRING DIRECTORY) (WRAP-STRING "..."))
  (BUMP-LOG-INDENT)
  (CL:SETQ DIRECTORY (FILE-NAME-AS-DIRECTORY DIRECTORY))
  (CL:LET* ((FILE NULL) (ITER-000 (%LIST-DIRECTORY-FILES DIRECTORY)))
   (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
    (CL:SETQ FILE (%%VALUE ITER-000))
    (CL:LET* ((FOUND?-000 CL:NIL))
     (CL:LET* ((EXT NULL) (ITER-001 *POWERLOOM-KB-FILE-EXTENSIONS*))
      (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
       (CL:SETQ EXT (%%VALUE ITER-001))
       (CL:WHEN
        (ENDS-WITH? (%WRAPPER-VALUE FILE) (%WRAPPER-VALUE EXT)
         NULL-INTEGER)
        (CL:SETQ FOUND?-000 CL:T) (CL:RETURN))
       (CL:SETQ ITER-001 (%%REST ITER-001))))
     (CL:WHEN FOUND?-000
      (PL-LOG KWD-LOGIC-IN-MEDIUM (WRAP-STRING "Loading file ") FILE)
      (%LOAD (CONCATENATE DIRECTORY (%WRAPPER-VALUE FILE)) NIL)))
    (CL:SETQ ITER-000 (%%REST ITER-000))))
  (UNBUMP-LOG-INDENT)
  (PROCESS-DEFINITIONS))

(CL:DEFUN LOAD-DIRECTORY-EVALUATOR-WRAPPER (ARGUMENTS)
  (%LOAD-DIRECTORY (%WRAPPER-VALUE (%%VALUE ARGUMENTS))))

(CL:DEFMACRO LOAD-DIRECTORY (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Load all PowerLoom files (*.plm) in `directory' in alphabetic sort order."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/LOAD-DIRECTORY|)) (CL:MACRO-FUNCTION (CL:QUOTE LOAD-DIRECTORY)))

;;; (DEFUN LOAD-CMD-LINE-FILES ...)

(CL:DEFUN LOAD-CMD-LINE-FILES ()
  "Loads all PowerLoom files specified on the command line.
If directories are listed, all PowerLoom files in those directories are loaded.
Since when this is called we might still have unprocessed command line args,
this only looks at files which are to the right of the last argument that
starts with a `-' character."
  (CL:LET*
   ((UNPROCESSEDARGS (UNPROCESSED-COMMAND-LINE-ARGUMENTS))
    (FILE STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING FILE))
   (CL:WHEN (CL:NOT (CL:EQ UNPROCESSEDARGS NULL))
    (CL:SETQ UNPROCESSEDARGS
     (REVERSE (COPY-CONS-LIST (UNPROCESSED-COMMAND-LINE-ARGUMENTS))))
    (CL:LET*
     ((ARG NULL) (ITER-000 UNPROCESSEDARGS) (I NULL-INTEGER)
      (ITER-001 0))
     (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-001))
     (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
      (CL:SETQ ARG (%%VALUE ITER-000)) (CL:SETQ I ITER-001)
      (CL:WHEN (STARTS-WITH? (%WRAPPER-VALUE ARG) "-" NULL-INTEGER)
       (CL:IF (CL:= I 0) (CL:SETQ UNPROCESSEDARGS NIL)
        (NTH-REST-SETTER UNPROCESSEDARGS NIL I))
       (CL:RETURN))
      (CL:SETQ ITER-000 (%%REST ITER-000))
      (CL:SETQ ITER-001 (CL:1+ ITER-001))))
    (PL-LOG KWD-LOGIC-IN-LOW
     (WRAP-STRING "Loading command line PowerLoom files..."))
    (BUMP-LOG-INDENT)
    (CL:LET* ((ARG NULL) (ITER-002 (REVERSE UNPROCESSEDARGS)))
     (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-002 NIL)) DO
      (CL:SETQ ARG (%%VALUE ITER-002))
      (CL:LET* ((FOUND?-000 CL:NIL))
       (CL:LET* ((EXT NULL) (ITER-003 *POWERLOOM-KB-FILE-EXTENSIONS*))
        (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-003 NIL)) DO
         (CL:SETQ EXT (%%VALUE ITER-003))
         (CL:WHEN
          (ENDS-WITH? (%WRAPPER-VALUE ARG) (%WRAPPER-VALUE EXT)
           NULL-INTEGER)
          (CL:SETQ FOUND?-000 CL:T) (CL:RETURN))
         (CL:SETQ ITER-003 (%%REST ITER-003))))
       (CL:IF FOUND?-000
        (CL:PROGN
         (CL:LET*
          ((TEMP-000
            (%FIND-FILE-IN-LOAD-PATH (%WRAPPER-VALUE ARG) NULL)))
          (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEMP-000))
          (CL:SETQ FILE
           (CL:IF (CL:NOT (CL:EQ TEMP-000 STELLA::NULL-STRING))
            TEMP-000 (%WRAPPER-VALUE ARG))))
         (PL-LOG KWD-LOGIC-IN-MEDIUM (WRAP-STRING "Loading file ")
          (WRAP-STRING FILE))
         (%LOAD FILE NIL))
        (CL:WHEN
         (PROBE-FILE? (FILE-NAME-AS-DIRECTORY (%WRAPPER-VALUE ARG)))
         (%LOAD-DIRECTORY (%WRAPPER-VALUE ARG)))))
      (CL:SETQ ITER-002 (%%REST ITER-002))))
    (UNBUMP-LOG-INDENT))))

;;; (DEFSPECIAL *DEMO-LEVEL* ...)

(CL:DEFVAR *DEMO-LEVEL* 0)
(CL:DECLAIM (CL:TYPE CL:FIXNUM *DEMO-LEVEL*))

;;; (DEFUN PRINT-DEMO-PROMPT ...)

(CL:DEFUN PRINT-DEMO-PROMPT ()
  (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) *LOGIC-PROMPT*))

;;; (DEFUN (DEMO-SKIP-TO-COMMAND BOOLEAN) ...)

(CL:DEFUN DEMO-SKIP-TO-COMMAND (STREAM)
  (CL:LET*
   ((CH NULL-CHARACTER) (EOF? CL:NIL) (ECHO? CL:NIL)
    (ECHOSTREAM (%ECHO-STREAM STREAM)))
   (CL:LOOP (CL:SETF (%ECHO-STREAM STREAM) NULL)
    (CL:MULTIPLE-VALUE-SETQ (CH EOF?) (READ-CHARACTER STREAM))
    (CL:WHEN EOF? (CL:RETURN-FROM DEMO-SKIP-TO-COMMAND CL:T))
    (CL:WHEN ECHO? (CL:SETF (%ECHO-STREAM STREAM) ECHOSTREAM))
    (CL:COND
     ((CL:EQ
       (CL:AREF *CHARACTER-TYPE-TABLE*
        (CL:THE CL:FIXNUM (CL:CHAR-CODE CH)))
       KWD-LOGIC-IN-WHITE-SPACE)
      (CL:WHEN ECHO? (%%PRINT-STREAM (%NATIVE-STREAM ECHOSTREAM) CH)))
     ((CL:EQL CH #\;) (CL:SETQ ECHO? CL:T)
      (CL:SETF (%ECHO-STREAM STREAM) ECHOSTREAM)
      (%%PRINT-STREAM (%NATIVE-STREAM ECHOSTREAM) CH)
      (CL:SETQ EOF?
       (CL:EQ (NATIVE-READ-LINE STREAM) STELLA::NULL-STRING))
      (CL:WHEN EOF? (CL:RETURN-FROM DEMO-SKIP-TO-COMMAND CL:T)))
     (CL:T (CL:SETF (%ECHO-STREAM STREAM) ECHOSTREAM)
      (UNREAD-CHARACTER CH STREAM) (CL:RETURN))))
   CL:NIL))

;;; (DEFUN (DEMO-PAUSE? BOOLEAN BOOLEAN) ...)

(CL:DEFUN DEMO-PAUSE? (PAUSE?)
  (CL:LET* ((EXIT? CL:NIL) (INPUT STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING INPUT))
   (CL:COND
    (PAUSE?
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
      "------ pause ------")
     (CL:SETQ INPUT (READ-LINE STANDARD-INPUT))
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL)
     (CL:WHEN (CL:> (CL:THE CL:FIXNUM (CL:LENGTH INPUT)) 0)
      (CL:CASE
       (CL:LET
        ((SELF *CHARACTER-UPCASE-TABLE*)
         (POSITION
          (CL:THE CL:FIXNUM
           (CL:CHAR-CODE
            (CL:LET ((SELF INPUT) (POSITION 0))
             (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
              (CL:TYPE CL:FIXNUM POSITION))
             (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
              (CL:THE CL:FIXNUM POSITION)))))))
        (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING SELF)
         (CL:TYPE CL:FIXNUM POSITION))
        (CL:SCHAR (CL:THE CL:SIMPLE-STRING SELF)
         (CL:THE CL:FIXNUM POSITION)))
       (#\C (CL:SETQ PAUSE? CL:NIL))
       (#\Q
        (CL:WHEN (Y-OR-N? "Really exit demo? (y or n) ")
         (CL:SETQ PAUSE? CL:NIL) (CL:SETQ EXIT? CL:T)))
       ((#\H #\?)
        (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
         "Type `c' to continue without pausing," EOL
         "     `q' to quit from this demo," EOL
         "     `?' or `h' to get this message," EOL
         "     or any other key to continue." EOL)
        (CL:RETURN-FROM DEMO-PAUSE? (DEMO-PAUSE? PAUSE?)))
       (CL:OTHERWISE))))
    (CL:T (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL)))
   (CL:VALUES PAUSE? EXIT?)))

;;; (DEFUN DEMO-FILE ...)

(CL:DEFUN DEMO-FILE (FILE PAUSE?)
  (CL:LET*
   ((TEMP-000
     (%FIND-FILE-IN-LOAD-PATH FILE *POWERLOOM-KB-FILE-EXTENSIONS*)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEMP-000))
   (CL:SETQ FILE
    (CL:IF (CL:NOT (CL:EQ TEMP-000 STELLA::NULL-STRING)) TEMP-000
     FILE)))
  (ENSURE-FILE-EXISTS FILE "demo-file")
  (CL:LET*
   ((CURRENTLEVEL *DEMO-LEVEL*) (COMMAND NULL) (RESULT NULL)
    (EXIT? CL:NIL))
   (CL:DECLARE (CL:TYPE CL:FIXNUM CURRENTLEVEL))
   (CL:LET* ((INPUTSTREAM NULL))
    (CL:UNWIND-PROTECT
     (CL:PROGN (CL:SETQ INPUTSTREAM (OPEN-INPUT-FILE FILE))
      (CL:LET*
       ((*CONFIRM-INTERACTIVE-EXIT?* CL:NIL)
        (*DEMO-LEVEL* (CL:1+ CURRENTLEVEL)))
       (CL:DECLARE
        (CL:SPECIAL *CONFIRM-INTERACTIVE-EXIT?* *DEMO-LEVEL*))
       (CL:DECLARE (CL:TYPE CL:FIXNUM *DEMO-LEVEL*))
       (CL:SETF (%ECHO-STREAM INPUTSTREAM) STANDARD-OUTPUT)
       (CL:LET* ((*MODULE* *MODULE*) (*CONTEXT* *MODULE*))
        (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
        (CL:WHEN PAUSE?
         (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
          "Now reading from `" FILE "'." EOL
          "Type `?' at the pause prompt for a list of available commands."
          EOL))
        (CL:LOOP
         (CL:HANDLER-CASE
          (CL:PROGN
           (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL)
           (CL:SETQ EXIT? (DEMO-SKIP-TO-COMMAND INPUTSTREAM))
           (PRINT-DEMO-PROMPT)
           (CL:WHEN (CL:NOT EXIT?)
            (CL:MULTIPLE-VALUE-SETQ (COMMAND EXIT?)
             (READ-S-EXPRESSION INPUTSTREAM)))
           (CL:WHEN (CL:OR EXIT? (LOGIC-COMMAND-LOOP-EXIT? COMMAND))
            (CL:RETURN))
           (CL:MULTIPLE-VALUE-SETQ (PAUSE? EXIT?) (DEMO-PAUSE? PAUSE?))
           (CL:WHEN EXIT? (CL:RETURN))
           (CL:SETQ RESULT (EVALUATE-LOGIC-COMMAND COMMAND CL:NIL))
           (PRINT-LOGIC-COMMAND-RESULT RESULT))
          (EVALUATION-EXCEPTION (E)
           (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR) ">> Error: "
            (EXCEPTION-MESSAGE E)))))
        (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL EOL
         *LOGIC-COMMAND-RESULT-INDENT* "Finished demo `" FILE "'."
         EOL))))
     (CL:WHEN (CL:NOT (CL:EQ INPUTSTREAM NULL)) (FREE INPUTSTREAM))))))

;;; (DEFGLOBAL *DEMO-FILES* ...)

(CL:DEFVAR *DEMO-FILES* NULL
  "List of example demo files.
Each entry is a `(<file> <description>)' pair.")

;;; (DEFUN (DEMO-ENTRY-FILE STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T) CL:SIMPLE-STRING) DEMO-ENTRY-FILE))
(CL:DEFUN DEMO-ENTRY-FILE (DEMOENTRY)
  (CL:LET* ((DEMOBASEFILE (%WRAPPER-VALUE (%%VALUE DEMOENTRY))))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING DEMOBASEFILE))
   (CL:LET*
    ((TEMP-000
      (%FIND-FILE-IN-LOAD-PATH DEMOBASEFILE
       *POWERLOOM-KB-FILE-EXTENSIONS*)))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TEMP-000))
    (CL:LET*
     ((VALUE-000
       (CL:IF (CL:NOT (CL:EQ TEMP-000 STELLA::NULL-STRING)) TEMP-000
        DEMOBASEFILE)))
     (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING VALUE-000)) VALUE-000))))

;;; (DEFUN (DEMO-ENTRY-DESCRIPTION STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T) CL:SIMPLE-STRING)
  DEMO-ENTRY-DESCRIPTION))
(CL:DEFUN DEMO-ENTRY-DESCRIPTION (DEMOENTRY)
  (CL:IF (CL:NOT (CL:EQ (%%VALUE (%%REST DEMOENTRY)) NULL))
   (%WRAPPER-VALUE (%%VALUE (%%REST DEMOENTRY)))
   (%WRAPPER-VALUE (%%VALUE DEMOENTRY))))

;;; (DEFUN (DEMO-ENTRY-TEST-SUITE? BOOLEAN) ...)

(CL:DEFUN DEMO-ENTRY-TEST-SUITE? (DEMOENTRY)
  (CL:AND (STRING? (%%VALUE (%%REST (%%REST DEMOENTRY))))
   (STRING-EQL? (%WRAPPER-VALUE (%%VALUE (%%REST (%%REST DEMOENTRY))))
    "test-suite")))

;;; (DEFUN (SELECT-EXAMPLE-DEMO STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:FIXNUM) CL:SIMPLE-STRING)
  SELECT-EXAMPLE-DEMO))
(CL:DEFUN SELECT-EXAMPLE-DEMO (INDEX)
  (CL:DECLARE (CL:TYPE CL:FIXNUM INDEX))
  #+MCL
  (CL:CHECK-TYPE INDEX CL:FIXNUM)
  (CL:LET* ((ENTRY (NTH *DEMO-FILES* (CL:1- INDEX))))
   (CL:IF (CL:NOT (CL:EQ ENTRY NULL)) (DEMO-ENTRY-FILE ENTRY)
    STELLA::NULL-STRING)))

;;; (DEFUN (SELECT-EXAMPLE-DEMO-FROM-MENU STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION () CL:SIMPLE-STRING)
  SELECT-EXAMPLE-DEMO-FROM-MENU))
(CL:DEFUN SELECT-EXAMPLE-DEMO-FROM-MENU ()
  (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "Choose a demo:" EOL)
  (CL:LET*
   ((ENTRY NULL) (ITER-000 *DEMO-FILES*) (I NULL-INTEGER) (ITER-001 1))
   (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-001))
   (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
    (CL:SETQ ENTRY (%%VALUE ITER-000)) (CL:SETQ I ITER-001)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "       " I ".  ")
    (CL:WHEN (CL:< I 10)
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) " "))
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     (DEMO-ENTRY-DESCRIPTION ENTRY) EOL)
    (CL:SETQ ITER-000 (%%REST ITER-000))
    (CL:SETQ ITER-001 (CL:1+ ITER-001))))
  (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
   "       Q.   Quit demoing" EOL)
  (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "Your choice: ")
  (CL:LET*
   ((SELECTION (READ-S-EXPRESSION STANDARD-INPUT))
    (FILE STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING FILE))
   (CL:COND
    ((SUBTYPE-OF-INTEGER? (SAFE-PRIMARY-TYPE SELECTION))
     (CL:PROGN
      (CL:SETQ FILE (SELECT-EXAMPLE-DEMO (%WRAPPER-VALUE SELECTION)))
      (CL:WHEN (CL:NOT (CL:EQ FILE STELLA::NULL-STRING))
       (CL:RETURN-FROM SELECT-EXAMPLE-DEMO-FROM-MENU FILE))))
    (CL:T
     (CL:WHEN (STRING-EQUAL? (STRINGIFY SELECTION) "Q")
      (CL:RETURN-FROM SELECT-EXAMPLE-DEMO-FROM-MENU
       STELLA::NULL-STRING))))
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
    ">> ERROR: Illegal choice `" SELECTION
    "'; enter a number between 1 and " (LENGTH *DEMO-FILES*) "!" EOL
    EOL)
   (SELECT-EXAMPLE-DEMO-FROM-MENU)))

;;; (DEFUN DEMO-EXAMPLE-DEMOS ...)

(CL:DEFUN DEMO-EXAMPLE-DEMOS ()
  (CL:LET* ((FILE STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING FILE))
   (CL:LOOP (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL)
    (CL:SETQ FILE (SELECT-EXAMPLE-DEMO-FROM-MENU))
    (CL:WHEN (CL:EQ FILE STELLA::NULL-STRING)
     (CL:RETURN-FROM DEMO-EXAMPLE-DEMOS))
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL)
    (DEMO-FILE FILE CL:T))))

;;; (DEFUN DEMO ...)

(CL:DEFUN %DEMO (FILEANDPAUSE)
  "Read logic commands from a file, echo them verbatimly to standard output,
and evaluate them just as if they had been typed in interactively.
When called with no arguments, present a menu of example demos, otherwise,
use the first argument as the name of the file to demo.
Pause for user confirmation after each expression has been read but
before it is evaluated.  Pausing can be turned off by suppling FALSE
as the optional second argument, or by typing `c' at the pause prompt.
Typing `?' at the pause prompt prints a list of available commands."
  (CL:LET*
   ((THEFILEANDPAUSE FILEANDPAUSE) (FILESPEC (%%VALUE THEFILEANDPAUSE))
    (PAUSE?
     (CL:NOT (EQL? (%%VALUE (%%REST THEFILEANDPAUSE)) FALSE-WRAPPER)))
    (FILE STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING FILE))
   (CL:WHEN (INTEGER? FILESPEC)
    (CL:SETQ FILE (SELECT-EXAMPLE-DEMO (%WRAPPER-VALUE FILESPEC)))
    (CL:IF (CL:NOT (CL:EQ FILE STELLA::NULL-STRING))
     (CL:SETQ FILESPEC (WRAP-STRING FILE)) (CL:SETQ FILESPEC NULL)))
   (CL:IF (CL:EQ FILESPEC NULL) (DEMO-EXAMPLE-DEMOS)
    (CL:COND
     ((SUBTYPE-OF-STRING? (SAFE-PRIMARY-TYPE FILESPEC))
      (CL:PROGN (DEMO-FILE (%WRAPPER-VALUE FILESPEC) PAUSE?)))
     (CL:T
      (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
       ">> ERROR: Illegal file specification: " FILESPEC))))))

(CL:DEFUN DEMO-EVALUATOR-WRAPPER (ARGUMENTS)
  (%DEMO ARGUMENTS))

(CL:DEFMACRO DEMO (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Read logic commands from a file, echo them verbatimly to standard output,
and evaluate them just as if they had been typed in interactively.
When called with no arguments, present a menu of example demos, otherwise,
use the first argument as the name of the file to demo.
Pause for user confirmation after each expression has been read but
before it is evaluated.  Pausing can be turned off by suppling FALSE
as the optional second argument, or by typing `c' at the pause prompt.
Typing `?' at the pause prompt prints a list of available commands."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/DEMO|)) (CL:MACRO-FUNCTION (CL:QUOTE DEMO)))

;;; (DEFUN TEST-LOGIC-FILE ...)

(CL:DEFUN TEST-LOGIC-FILE (FILE)
  (ENSURE-FILE-EXISTS FILE "test-logic-file")
  (CL:LET*
   ((CURRENTLEVEL *DEMO-LEVEL*) (COMMAND NULL) (RESULT NULL)
    (EXIT? CL:NIL) (INPUTSTREAM (NEW-INPUT-FILE-STREAM FILE))
    (FILEBASENAME (FILE-NAME-WITHOUT-DIRECTORY FILE)))
   (CL:DECLARE (CL:TYPE CL:FIXNUM CURRENTLEVEL))
   (CL:LET*
    ((*CONFIRM-INTERACTIVE-EXIT?* CL:NIL)
     (*DEMO-LEVEL* (CL:1+ CURRENTLEVEL)) (*PRINTREADABLY?* CL:T)
     (*PRINTPRETTY?* CL:NIL))
    (CL:DECLARE
     (CL:SPECIAL *CONFIRM-INTERACTIVE-EXIT?* *DEMO-LEVEL*
      *PRINTREADABLY?* *PRINTPRETTY?*))
    (CL:DECLARE (CL:TYPE CL:FIXNUM *DEMO-LEVEL*))
    (CL:LET* ((*MODULE* *MODULE*) (*CONTEXT* *MODULE*))
     (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL
      "Now testing file `" FILEBASENAME "':" EOL)
     (CL:LOOP
      (CL:HANDLER-CASE
       (CL:PROGN (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL)
        (PRINT-DEMO-PROMPT)
        (CL:WHEN (CL:NOT EXIT?)
         (CL:MULTIPLE-VALUE-SETQ (COMMAND EXIT?)
          (READ-S-EXPRESSION INPUTSTREAM)))
        (CL:WHEN (CL:OR EXIT? (LOGIC-COMMAND-LOOP-EXIT? COMMAND))
         (CL:RETURN))
        (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) COMMAND EOL
         EOL)
        (CL:SETQ RESULT (EVALUATE-LOGIC-COMMAND COMMAND CL:NIL))
        (PRINT-LOGIC-COMMAND-RESULT RESULT))
       (EVALUATION-EXCEPTION (E)
        (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR) ">> Error: "
         (EXCEPTION-MESSAGE E)))))
     (FREE INPUTSTREAM)
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL EOL
      *LOGIC-COMMAND-RESULT-INDENT* "Finished testing file `"
      FILEBASENAME "'." EOL)))))

;;; (DEFUN (GET-FORMATTED-DATE-AND-TIME STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION () CL:SIMPLE-STRING)
  GET-FORMATTED-DATE-AND-TIME))
(CL:DEFUN GET-FORMATTED-DATE-AND-TIME ()
  (CALENDAR-DATE-TO-STRING (MAKE-CURRENT-DATE-TIME)
   (GET-LOCAL-TIME-ZONE) CL:NIL CL:T))

;;; (DEFUN RUN-POWERLOOM-TESTS ...)

(CL:DEFUN RUN-POWERLOOM-TESTS ()
  "Run the PowerLoom test suite.  Currently this simply runs all demos and
echos commands and their results to standard output.  The output can then
be diffed with previously validated runs to find deviations."
  (CL:LET*
   ((PLUSER (GET-STELLA-MODULE "PL-USER" CL:T))
    (START-TIME (MAKE-CURRENT-DATE-TIME)) (FINISH-TIME NULL)
    (LOGLEVEL
     (LOOKUP-LOGGING-PARAMETER "PowerLoom" KWD-LOGIC-IN-LEVEL
      KWD-LOGIC-IN-LOW)))
   (%SET-LOGGING-PARAMETERS "PowerLoom"
    (CONS-LIST KWD-LOGIC-IN-LEVEL KWD-LOGIC-IN-NONE))
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
    "RUNNING POWERLOOM TEST SUITE" EOL "============================"
    EOL EOL)
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
    "STELLA version:    " *STELLA-VERSION-STRING* EOL
    "PowerLoom version: " *POWERLOOM-VERSION-STRING* EOL
    "Start time:        "
    (CALENDAR-DATE-TO-STRING START-TIME (GET-LOCAL-TIME-ZONE) CL:NIL
     CL:T)
    EOL EOL)
   (CLEAR-CONTEXT PLUSER)
   (CL:LET*
    ((CHILD NULL)
     (ITER-000 (%THE-CONS-LIST (COPY (%CHILD-CONTEXTS PLUSER)))))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ CHILD (%%VALUE ITER-000)) (DESTROY-CONTEXT CHILD)
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   (CL:SETQ *SKOLEM-ID-COUNTER* 0)
   (CL:LET* ((ENTRY NULL) (ITER-001 *DEMO-FILES*))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
     (CL:SETQ ENTRY (%%VALUE ITER-001))
     (CL:WHEN (DEMO-ENTRY-TEST-SUITE? ENTRY)
      (TEST-LOGIC-FILE (DEMO-ENTRY-FILE ENTRY)))
     (CL:SETQ ITER-001 (%%REST ITER-001))))
   (CL:SETQ FINISH-TIME (MAKE-CURRENT-DATE-TIME))
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL
    "FINISHED RUNNING POWERLOOM TEST SUITE" EOL
    "=====================================" EOL "Finish time:   "
    (CALENDAR-DATE-TO-STRING FINISH-TIME (GET-LOCAL-TIME-ZONE) CL:NIL
     CL:T)
    EOL "Elapsed time:  "
    (TIME-DURATION-TO-STRING (TIME-SUBTRACT FINISH-TIME START-TIME))
    EOL EOL)
   (%SET-LOGGING-PARAMETERS "PowerLoom"
    (CONS-LIST KWD-LOGIC-IN-LEVEL LOGLEVEL))))

;;; (DEFUN (TIME-COMMAND OBJECT) ...)

(CL:DEFUN %TIME-COMMAND (COMMAND)
  "Execute `command', measure and report its CPU and elapsed time
needed for its execution, and then return its result."
  (CL:LET*
   ((STARTTIME (MAKE-CURRENT-DATE-TIME)) (STARTCPU (GET-TICKTOCK))
    (RESULT (%EVALUATE COMMAND)) (ENDCPU (GET-TICKTOCK))
    (ELAPSEDTIME (TIME-SUBTRACT (MAKE-CURRENT-DATE-TIME) STARTTIME)))
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "CPU Time:     "
    (TICKTOCK-DIFFERENCE STARTCPU ENDCPU) " secs" EOL)
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "Elapsed Time: ")
   (CL:WHEN (CL:> (%DAYS ELAPSEDTIME) 0)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
     (%DAYS ELAPSEDTIME) " days, "))
   (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
    (ROUND (CL:/ (%MILLIS ELAPSEDTIME) 1000.0d0)) " secs" EOL)
   RESULT))

(CL:DEFMACRO TIME-COMMAND (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Execute `command', measure and report its CPU and elapsed time
needed for its execution, and then return its result."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/TIME-COMMAND|)) (CL:MACRO-FUNCTION (CL:QUOTE TIME-COMMAND)))

;;; (DEFUN (GET-HTTP-SERVER-SYSTEM STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION () CL:SIMPLE-STRING) GET-HTTP-SERVER-SYSTEM))
(CL:DEFUN GET-HTTP-SERVER-SYSTEM ()
  "webtools")

;;; (DEFUN START-ONTOSAURUS ...)

(CL:DEFUN %START-ONTOSAURUS (OPTIONS)
  "Start the PowerLoom HTTP server at :port (defaults to 9090).  Loads
the required support systems in Lisp and Java if necessary (C++ is not yet supported)."
  (CL:LET*
   ((THEOPTIONS
     (PARSE-LOGIC-COMMAND-OPTIONS OPTIONS
      (LIST* KWD-LOGIC-IN-PORT SGT-LOGIC-IN-STELLA-INTEGER NIL) CL:T
      CL:NIL))
    (PORT
     (%WRAPPER-VALUE
      (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-LOGIC-IN-PORT
       (WRAP-INTEGER 0))))
    (ADDRESS STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:FIXNUM PORT)
    (CL:TYPE CL:SIMPLE-STRING ADDRESS))
   (AUTOLOAD "ONTOSAURUS/CONTROL-PANEL-HANDLER" "ontosaurus" NULL CL:T)
   (CL:SETQ ADDRESS
    (CL:FUNCALL
     (AUTOLOAD "HTTP/START-HTTP-SERVER" (GET-HTTP-SERVER-SYSTEM) NULL
      CL:T)
     PORT))
   (PL-LOG KWD-LOGIC-IN-LOW
    (WRAP-STRING "Started Ontosaurus, point your browser to `")
    (WRAP-STRING ADDRESS) (WRAP-STRING "ploom/ontosaurus/'"))))

(CL:DEFUN START-ONTOSAURUS-EVALUATOR-WRAPPER (ARGUMENTS)
  (%START-ONTOSAURUS ARGUMENTS))

(CL:DEFMACRO START-ONTOSAURUS (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Start the PowerLoom HTTP server at :port (defaults to 9090).  Loads
the required support systems in Lisp and Java if necessary (C++ is not yet supported)."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/START-ONTOSAURUS|)) (CL:MACRO-FUNCTION (CL:QUOTE START-ONTOSAURUS)))

;;; (DEFUN STOP-ONTOSAURUS ...)

(CL:DEFUN STOP-ONTOSAURUS ()
  "Stop the PowerLoom HTTP server and free up any bound ports.
This is a no-op if no server is running or the server is not supported."
  (CL:FUNCALL
   (AUTOLOAD "HTTP/STOP-HTTP-SERVER" (GET-HTTP-SERVER-SYSTEM) NULL
    CL:T)))

;;; (DEFUN START-POWERLOOM-SERVER ...)

(CL:DEFUN %START-POWERLOOM-SERVER (OPTIONS)
  "Start the PowerLoom HTTP server at :port (defaults to 9090).  Loads
the required support systems in Lisp and Java if necessary (C++ is not yet supported)."
  (CL:LET*
   ((THEOPTIONS
     (PARSE-LOGIC-COMMAND-OPTIONS OPTIONS
      (LIST* KWD-LOGIC-IN-PORT SGT-LOGIC-IN-STELLA-INTEGER NIL) CL:T
      CL:NIL))
    (PORT
     (%WRAPPER-VALUE
      (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-LOGIC-IN-PORT
       (WRAP-INTEGER 0))))
    (ADDRESS STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:FIXNUM PORT)
    (CL:TYPE CL:SIMPLE-STRING ADDRESS))
   (AUTOLOAD "GUI-SERVER/GUI-REQUEST-HANDLER" "powerloom-server" NULL
    CL:T)
   (CL:SETQ ADDRESS
    (CL:FUNCALL
     (AUTOLOAD "HTTP/START-HTTP-SERVER" (GET-HTTP-SERVER-SYSTEM) NULL
      CL:T)
     PORT))
   (PL-LOG KWD-LOGIC-IN-LOW
    (WRAP-STRING "Started PowerLoom server at `") (WRAP-STRING ADDRESS)
    (WRAP-STRING "ploom/soap-rpc/...'"))))

(CL:DEFUN START-POWERLOOM-SERVER-EVALUATOR-WRAPPER (ARGUMENTS)
  (%START-POWERLOOM-SERVER ARGUMENTS))

(CL:DEFMACRO START-POWERLOOM-SERVER (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Start the PowerLoom HTTP server at :port (defaults to 9090).  Loads
the required support systems in Lisp and Java if necessary (C++ is not yet supported)."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/START-POWERLOOM-SERVER|)) (CL:MACRO-FUNCTION (CL:QUOTE START-POWERLOOM-SERVER)))

;;; (DEFUN STOP-POWERLOOM-SERVER ...)

(CL:DEFUN STOP-POWERLOOM-SERVER ()
  "Stop the PowerLoom HTTP server and free up any bound ports.
This is a no-op if no server is running or the server is not supported."
  (CL:FUNCALL
   (AUTOLOAD "HTTP/STOP-HTTP-SERVER" (GET-HTTP-SERVER-SYSTEM) NULL
    CL:T)))

;;; (DEFUN START-POWERLOOM-GUI ...)

(CL:DEFUN %START-POWERLOOM-GUI (OPTIONS)
  "Start the PowerLoom server at :port (defaults to 9090) and launches
the GUI which will communicate with the server at that port.  If :host is specified,
the GUI will try to communicate with a server at `host:port' instead of the local
embedded server (note, you can always point the GUI manually to a different server
from its `Connect to Server' menu item).  Loads the required support systems if necessary.
Embedded calls to the GUI are currently only supported in Java; however, when the GUI is
run in standalone mode, it can communicate with any PowerLoom installation that supports
an HTTP server (currently Lisp and Java)."
  (CL:LET*
   ((THEOPTIONS
     (PARSE-LOGIC-COMMAND-OPTIONS OPTIONS
      (LIST* KWD-LOGIC-IN-HOST SGT-LOGIC-IN-STELLA-STRING
       KWD-LOGIC-IN-PORT SGT-LOGIC-IN-STELLA-INTEGER
       KWD-LOGIC-IN-DEBUG-LEVEL SGT-LOGIC-IN-STELLA-INTEGER NIL)
      CL:T CL:NIL))
    (HOST
     (%WRAPPER-VALUE
      (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-LOGIC-IN-HOST
       (WRAP-STRING "localhost"))))
    (PORT
     (%WRAPPER-VALUE
      (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-LOGIC-IN-PORT
       (WRAP-INTEGER 9090))))
    (DEBUGLEVEL
     (%WRAPPER-VALUE
      (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-LOGIC-IN-DEBUG-LEVEL
       (WRAP-INTEGER 1))))
    (GUICLASS "edu.isi.powerloom.gui.components.PowerloomApp")
    (GUIFN NULL) (GUIFNARGS (CL:MAKE-ARRAY 6)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING HOST GUICLASS)
    (CL:TYPE CL:FIXNUM PORT DEBUGLEVEL)
    (CL:TYPE CL:SIMPLE-VECTOR GUIFNARGS))
   (CL:PROGN
    (CL:PROGN (CL:SETQ HOST HOST) (CL:SETQ PORT PORT)
     (CL:SETQ DEBUGLEVEL DEBUGLEVEL) (CL:SETQ GUICLASS GUICLASS)
     (CL:SETQ GUIFN GUIFN) (CL:SETQ GUIFNARGS GUIFNARGS))
    (CL:ERROR
     (NEW-LOGIC-EXCEPTION
      "PowerLoom GUI only available in Java version of PowerLoom")))))

(CL:DEFUN START-POWERLOOM-GUI-EVALUATOR-WRAPPER (ARGUMENTS)
  (%START-POWERLOOM-GUI ARGUMENTS))

(CL:DEFMACRO START-POWERLOOM-GUI (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Start the PowerLoom server at :port (defaults to 9090) and launches
the GUI which will communicate with the server at that port.  If :host is specified,
the GUI will try to communicate with a server at `host:port' instead of the local
embedded server (note, you can always point the GUI manually to a different server
from its `Connect to Server' menu item).  Loads the required support systems if necessary.
Embedded calls to the GUI are currently only supported in Java; however, when the GUI is
run in standalone mode, it can communicate with any PowerLoom installation that supports
an HTTP server (currently Lisp and Java)."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/START-POWERLOOM-GUI|)) (CL:MACRO-FUNCTION (CL:QUOTE START-POWERLOOM-GUI)))

;;; (DEFUN STOP-POWERLOOM-GUI ...)

(CL:DEFUN STOP-POWERLOOM-GUI ()
  "Closes the PowerLoom GUI application if it is currently visible.
This is a no-op if the GUI is not running or if it is not supported."
  (CL:LET*
   ((GUICLASS "edu.isi.powerloom.gui.components.PowerloomApp")
    (EXITFN NULL))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING GUICLASS))
   (CL:SETQ GUICLASS GUICLASS)
   (CL:WHEN (CL:NOT (CL:EQ EXITFN NULL)) (CL:FUNCALL EXITFN))))

;;; (DEFUN POWERLOOM-GUI-EXIT-HOOK ...)

(CL:DEFUN POWERLOOM-GUI-EXIT-HOOK (IGNORE)
  "Exit hook to stop the PowerLoom GUI if it is running."
  (CL:SETQ IGNORE IGNORE)
  (CL:HANDLER-CASE (STOP-POWERLOOM-GUI) (CL:CONDITION ())))

;;; (DEFSPECIAL *TERMSOURCEBEINGPARSED* ...)

(CL:DEFVAR *TERMSOURCEBEINGPARSED* STELLA::NULL-STRING
  "Points to the source of the relation being parsed.")
(CL:DECLAIM (CL:TYPE CL:SIMPLE-STRING *TERMSOURCEBEINGPARSED*))

;;; (DEFSPECIAL *DESCRIPTIONUNDERCONSTRUCTION* ...)

(CL:DEFVAR *DESCRIPTIONUNDERCONSTRUCTION* NULL
  "Pofints to a description or its parse tree which
is the input to the description being constructed.")

;;; (DEFSPECIAL *TERMUNDERCONSTRUCTION* ...)

(CL:DEFVAR *TERMUNDERCONSTRUCTION* NULL
  "Points to the parse tree which is the input to the
proposition being constructed.")

;;; (DEFGLOBAL *EXPRESSION-SIZE-CUTOFF* ...)

(CL:DEFVAR *EXPRESSION-SIZE-CUTOFF* 300
  "Limit on how big an s-expression we will print within
an error message.")
(CL:DECLAIM (CL:TYPE CL:FIXNUM *EXPRESSION-SIZE-CUTOFF*))

;;; (DEFUN PRINT-FORMULA-CONTAINING-ERROR ...)

(CL:DEFUN PRINT-FORMULA-CONTAINING-ERROR (SELF STREAM)
  (CL:LET*
   ((TEMP (NEW-OUTPUT-STRING-STREAM))
    (EXPRESSIONSTRING STELLA::NULL-STRING))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING EXPRESSIONSTRING))
   (%%PRINT-STREAM (%NATIVE-STREAM TEMP) SELF)
   (CL:SETQ EXPRESSIONSTRING (THE-STRING-READER TEMP))
   (CL:WHEN
    (CL:> (CL:THE CL:FIXNUM (CL:LENGTH EXPRESSIONSTRING))
     *EXPRESSION-SIZE-CUTOFF*)
    (CL:SETQ EXPRESSIONSTRING
     (CONCATENATE
      (SUBSEQUENCE EXPRESSIONSTRING 0 *EXPRESSION-SIZE-CUTOFF*)
      " ......)")))
   (%%PRINT-STREAM (%NATIVE-STREAM STREAM) EXPRESSIONSTRING)))

;;; (DEFUN HELP-SIGNAL-PROPOSITION-ERROR ...)

(CL:DEFUN HELP-SIGNAL-PROPOSITION-ERROR (STREAM WARNINGORERROR)
  (CL:LET*
   ((BESTOUTPUTOBJECT *TERMUNDERCONSTRUCTION*)
    (TYPENAME
     (CL:IF (CL:NOT (CL:EQ BESTOUTPUTOBJECT NULL)) "proposition"
      "relation")))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TYPENAME))
   (CL:WHEN (CL:EQ BESTOUTPUTOBJECT NULL)
    (CL:SETQ BESTOUTPUTOBJECT *DESCRIPTIONUNDERCONSTRUCTION*))
   (CL:WHEN
    (CL:AND (CL:EQ BESTOUTPUTOBJECT NULL)
     (CL:NOT (CL:EQ *TERMSOURCEBEINGPARSED* STELLA::NULL-STRING)))
    (CL:SETQ BESTOUTPUTOBJECT (WRAP-STRING *TERMSOURCEBEINGPARSED*)))
   (CL:WHEN (CL:NOT (CL:EQ BESTOUTPUTOBJECT NULL))
    (%%PRINT-STREAM (%NATIVE-STREAM STREAM) "   ")
    (CL:COND
     ((CL:EQ WARNINGORERROR KWD-LOGIC-IN-ERROR)
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM) "Error"))
     ((CL:EQ WARNINGORERROR KWD-LOGIC-IN-WARNING)
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM) "Warning"))
     (CL:T
      (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
       (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" WARNINGORERROR
        "' is not a valid case option")
       (CL:ERROR
        (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
    (%%PRINT-STREAM (%NATIVE-STREAM STREAM)
     " occurred while parsing the " TYPENAME ": ")
    (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE BESTOUTPUTOBJECT)))
     (CL:COND
      ((SUBTYPE-OF? TEST-VALUE-000
        SGT-LOGIC-IN-LOGIC-NAMED-DESCRIPTION)
       (CL:PROGN
        (%%PRINT-STREAM (%NATIVE-STREAM STREAM)
         (RELATION-NAME BESTOUTPUTOBJECT) EOL)
        (CL:RETURN-FROM HELP-SIGNAL-PROPOSITION-ERROR)))
      ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-PROPOSITION)
       (CL:PROGN (%%PRINT-STREAM (%NATIVE-STREAM STREAM) EOL "   ")
        (PRINT-FORMULA-CONTAINING-ERROR *TERMUNDERCONSTRUCTION*
         STREAM)))
      ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-DESCRIPTION)
       (CL:PROGN (%%PRINT-STREAM (%NATIVE-STREAM STREAM) EOL "   ")
        (PRINT-FORMULA-CONTAINING-ERROR *TERMUNDERCONSTRUCTION*
         STREAM)))
      ((CL:EQ TEST-VALUE-000 SGT-LOGIC-IN-STELLA-CONS)
       (CL:PROGN (%%PRINT-STREAM (%NATIVE-STREAM STREAM) EOL "   ")
        (PRINT-FORMULA-CONTAINING-ERROR *TERMUNDERCONSTRUCTION*
         STREAM)))
      ((SUBTYPE-OF-STRING? TEST-VALUE-000)
       (CL:PROGN (%%PRINT-STREAM (%NATIVE-STREAM STREAM) EOL)
        (CL:LET*
         ((SEXPRESSION
           (READ-S-EXPRESSION-FROM-STRING
            (%WRAPPER-VALUE BESTOUTPUTOBJECT))))
         (PRINT-FORMULA-CONTAINING-ERROR SEXPRESSION STREAM))))
      (CL:T)))
    (%%PRINT-STREAM (%NATIVE-STREAM STREAM) EOL))))

;;; (DEFUN (LOGIC-DIALECT KEYWORD) ...)

(CL:DEFUN LOGIC-DIALECT (SELF)
  (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE SELF)))
   (CL:COND
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-STELLA-RELATION)
     (CL:PROGN (LOGIC-DIALECT (HOME-MODULE SELF))))
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-STELLA-MODULE)
     (CL:PROGN
      (CL:LET*
       ((DIALECT
         (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS SELF)
          SYM-LOGIC-IN-LOGIC-MODULE-LOGIC-DIALECT NULL)))
       (CL:IF (CL:NOT (CL:EQ DIALECT NULL)) DIALECT
        KWD-LOGIC-IN-KIF))))
    (CL:T
     (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" TEST-VALUE-000
       "' is not a valid case option")
      (CL:ERROR
       (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))))

;;; (DEFUN (LOOKUP-LOGIC-OBJECT-SURROGATE SURROGATE) ...)

(CL:DEFUN LOOKUP-LOGIC-OBJECT-SURROGATE (NAME DEFINITIONMODULE)
  (CL:SETQ DEFINITIONMODULE
   (CL:IF (CL:NOT (CL:EQ DEFINITIONMODULE NULL)) DEFINITIONMODULE
    *MODULE*))
  (CL:IF
   (EXPLICITLY-QUALIFIED-LOGIC-OBJECT-NAME? NAME DEFINITIONMODULE)
   (LOOKUP-SURROGATE-IN-MODULE (%SYMBOL-NAME NAME) (%HOME-CONTEXT NAME)
    CL:T)
   (LOOKUP-SURROGATE (%SYMBOL-NAME NAME))))

;;; (DEFUN (INTERN-LOGIC-OBJECT-SURROGATE SURROGATE) ...)

(CL:DEFUN INTERN-LOGIC-OBJECT-SURROGATE (NAME)
  (CL:WHEN (CL:NOT (CLEARABLE? *MODULE*))
   (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
    (CL:LET* ((*PRINTREADABLY?* CL:T))
     (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
      "ERROR: Can't define the term `" NAME
      "' in the unclearable module `" (%MODULE-FULL-NAME *MODULE*) "'."
      EOL)
     (HELP-SIGNAL-PROPOSITION-ERROR STREAM-000 KWD-LOGIC-IN-ERROR))
    (CL:ERROR (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-000)))))
  (CL:LET*
   ((OLDSURROGATE (LOOKUP-LOGIC-OBJECT-SURROGATE NAME *MODULE*))
    (OLDVALUE
     (CL:IF (CL:NOT (CL:EQ OLDSURROGATE NULL))
      (%SURROGATE-VALUE OLDSURROGATE) NULL))
    (OLDMODULE
     (CL:IF (CL:NOT (CL:EQ OLDVALUE NULL)) (HOME-MODULE OLDVALUE)
      NULL)))
   (CL:WHEN
    (CL:AND (CL:NOT (CL:EQ OLDVALUE NULL))
     (CL:NOT (CL:EQ OLDMODULE *MODULE*)))
    (CL:WHEN *WARNIFREDEFINE?*
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "Defining `" NAME
      "' would cause a term with the same name" EOL "   of type `"
      (NAME-OBJECT-METACLASS OLDVALUE) "' in module `"
      (%MODULE-FULL-NAME OLDMODULE) "' to be shadowed." EOL)
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
      "CAUTION: Automatic shadowing can be dangerous, because forward "
      EOL
      "   references to a shadowed object may be bound to the now shadowed "
      EOL "   object.  Suggestion: Explicitly shadow the name using"
      EOL "   DEFMODULE's `:shadow' option." EOL)
     (CL:WHEN (CL:NOT (YES-OR-NO? "Do it anyway? "))
      (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
       (CL:LET* ((*PRINTREADABLY?* CL:T))
        (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
        (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001)
         "ERROR: Couldn't shadow name `" NAME "' in `"
         (%MODULE-FULL-NAME *MODULE*) "'." EOL)
        (HELP-SIGNAL-PROPOSITION-ERROR STREAM-001 KWD-LOGIC-IN-ERROR))
       (CL:ERROR
        (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-001)))))))
   (CL:IF (EXPLICITLY-QUALIFIED-LOGIC-OBJECT-NAME? NAME *MODULE*)
    (CL:LET* ((*MODULE* (%HOME-CONTEXT NAME)) (*CONTEXT* *MODULE*))
     (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
     (SHADOW-SURROGATE (%SYMBOL-NAME NAME)))
    (SHADOW-SURROGATE (%SYMBOL-NAME NAME)))))

;;; (DEFUN (NAME-OBJECT-METACLASS STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION (CL:T) CL:SIMPLE-STRING) NAME-OBJECT-METACLASS))
(CL:DEFUN NAME-OBJECT-METACLASS (SELF)
  (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE SELF)))
   (CL:COND
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-DESCRIPTION)
     (CL:PROGN
      (CL:COND ((CLASS? SELF) "concept") ((FUNCTION? SELF) "function")
       (CL:T "relation"))))
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-LOGIC-OBJECT)
     (CL:PROGN "logic object"))
    (CL:T (STRING-DOWNCASE (%SYMBOL-NAME (PRIMARY-TYPE SELF)))))))

;;; (DEFUN (LOGIC-OBJECT-DEFINITION-TYPE KEYWORD) ...)

(CL:DEFUN LOGIC-OBJECT-DEFINITION-TYPE (NAME OLDOBJECT NEWOBJECT)
  (CL:WHEN (CL:EQ OLDOBJECT NULL)
   (CL:RETURN-FROM LOGIC-OBJECT-DEFINITION-TYPE
    KWD-LOGIC-IN-DEFINITION))
  (CL:LET*
   ((OLDKIND (NAME-OBJECT-METACLASS OLDOBJECT))
    (NEWKIND (NAME-OBJECT-METACLASS NEWOBJECT)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING OLDKIND NEWKIND))
   (CL:LET* ((TEST-VALUE-001 (SAFE-PRIMARY-TYPE OLDOBJECT)))
    (CL:COND
     ((SUBTYPE-OF? TEST-VALUE-001 SGT-LOGIC-IN-LOGIC-NAMED-DESCRIPTION)
      (CL:PROGN
       (CL:WHEN (CL:NOT (STRING-EQL? OLDKIND NEWKIND))
        (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
         (CL:LET* ((*PRINTREADABLY?* CL:T))
          (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
          (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
           "ERROR: Can't redefine `" OLDKIND "' `" NAME "' with a `"
           NEWKIND "'." EOL
           "   Explicitly destroy the old object first before you redefine it."
           EOL)
          (HELP-SIGNAL-PROPOSITION-ERROR STREAM-000
           KWD-LOGIC-IN-ERROR))
         (CL:ERROR
          (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-000)))))
       (CL:WHEN
        (CL:NOT
         (CL:OR (CL:= (ARITY OLDOBJECT) (ARITY NEWOBJECT))
          (CL:AND
           (CL:NOT
            (CL:EQ (STRINGIFIED-SOURCE NEWOBJECT) STELLA::NULL-STRING))
           (CL:NOT
            (CL:=
             (STRING-SEARCH (STRINGIFIED-SOURCE NEWOBJECT)
              "VARIABLE-ARITY" 0)
             NULL-INTEGER)))))
        (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
         (CL:LET* ((*PRINTREADABLY?* CL:T))
          (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
          (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001)
           "ERROR: Can't redefine `" OLDKIND "' `" NAME
           "' with a different arity." EOL
           "   Explicitly destroy the old object first before you redefine it."
           EOL)
          (HELP-SIGNAL-PROPOSITION-ERROR STREAM-001
           KWD-LOGIC-IN-ERROR))
         (CL:ERROR
          (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-001)))))
       (CL:RETURN-FROM LOGIC-OBJECT-DEFINITION-TYPE
        KWD-LOGIC-IN-REDEFINITION)))
     ((SUBTYPE-OF? TEST-VALUE-001 SGT-LOGIC-IN-LOGIC-LOGIC-OBJECT)
      (CL:PROGN
       (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE NEWOBJECT)))
        (CL:COND
         ((SUBTYPE-OF? TEST-VALUE-000
           SGT-LOGIC-IN-LOGIC-NAMED-DESCRIPTION)
          (CL:PROGN
           (CL:RETURN-FROM LOGIC-OBJECT-DEFINITION-TYPE
            KWD-LOGIC-IN-PROPER-DEFINITION)))
         ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-LOGIC-OBJECT)
          (CL:PROGN
           (CL:RETURN-FROM LOGIC-OBJECT-DEFINITION-TYPE
            KWD-LOGIC-IN-REDEFINITION)))
         (CL:T)))))
     (CL:T
      (CL:WHEN
       (CL:EQ (PRIMARY-TYPE OLDOBJECT) (PRIMARY-TYPE NEWOBJECT))
       (CL:RETURN-FROM LOGIC-OBJECT-DEFINITION-TYPE
        KWD-LOGIC-IN-REDEFINITION)))))
   (CL:LET* ((STREAM-002 (NEW-OUTPUT-STRING-STREAM)))
    (CL:LET* ((*PRINTREADABLY?* CL:T))
     (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-002)
      "ERROR: Can't redefine `" OLDKIND "' `" NAME "' with a `" NEWKIND
      "'." EOL
      "   Explicitly destroy the old object first before you redefine it."
      EOL)
     (HELP-SIGNAL-PROPOSITION-ERROR STREAM-002 KWD-LOGIC-IN-ERROR))
    (CL:ERROR (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-002))))))

;;; (DEFUN BIND-LOGIC-OBJECT-TO-SURROGATE ...)

(CL:DEFUN BIND-LOGIC-OBJECT-TO-SURROGATE (NAME OBJECT)
  (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE OBJECT)))
   (CL:COND
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-LOGIC-OBJECT)
     (CL:PROGN))
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-PROPOSITION)
     (CL:PROGN))
    (CL:T
     (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
       "INTERNAL ERROR: Can't yet define logic objects of type `"
       (PRIMARY-TYPE OBJECT) "'")
      (CL:ERROR
       (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000)))))))
  (CL:LET*
   ((NAMESURROGATE (INTERN-LOGIC-OBJECT-SURROGATE NAME))
    (OBJECTSURROGATE (OBJECT-SURROGATE OBJECT))
    (OLDOBJECT (%SURROGATE-VALUE NAMESURROGATE)) (DEFINITIONTYPE NULL))
   (CL:WHEN
    (CL:AND (CL:NOT (CL:EQ OLDOBJECT NULL)) (DELETED? OLDOBJECT))
    (CL:SETQ OLDOBJECT NULL)
    (CL:SETF (%SURROGATE-VALUE NAMESURROGATE) NULL))
   (CL:WHEN
    (CL:AND *WARNIFREDEFINE?* (CL:NOT (CL:EQ OBJECTSURROGATE NULL))
     (CL:NOT (CL:EQ OBJECTSURROGATE NAMESURROGATE)))
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "The `"
     (NAME-OBJECT-METACLASS OBJECT) "' now named `" NAME
     "' used to be named `"
     (INTERN-SYMBOL-IN-MODULE (%SYMBOL-NAME OBJECTSURROGATE)
      (%HOME-CONTEXT OBJECTSURROGATE) CL:NIL)
     "'." EOL "    Unlinking it from its old name." EOL)
    (CL:SETF (%SURROGATE-VALUE OBJECTSURROGATE) NULL))
   (OBJECT-SURROGATE-SETTER OBJECT NAMESURROGATE)
   (CL:SETQ DEFINITIONTYPE
    (LOGIC-OBJECT-DEFINITION-TYPE NAME OLDOBJECT OBJECT))
   (CL:SETF (%SURROGATE-VALUE NAMESURROGATE) OBJECT)
   (CL:WHEN
    (CL:AND (CL:NOT (CL:EQ OLDOBJECT NULL))
     (CL:NOT (EQL? OLDOBJECT OBJECT)))
    (OBJECT-SURROGATE-SETTER OLDOBJECT NULL))
   (CL:COND ((CL:EQ DEFINITIONTYPE KWD-LOGIC-IN-DEFINITION))
    ((CL:EQ DEFINITIONTYPE KWD-LOGIC-IN-PROPER-DEFINITION)
     (TRANSFER-PROPOSITIONS-AND-BACKLINKS OLDOBJECT OBJECT)
     (CL:LET* ((TEST-VALUE-001 (SAFE-PRIMARY-TYPE OLDOBJECT)))
      (CL:COND
       ((SUBTYPE-OF? TEST-VALUE-001 SGT-LOGIC-IN-LOGIC-LOGIC-OBJECT)
        (CL:PROGN (DELETED?-SETTER OLDOBJECT CL:T)))
       ((SUBTYPE-OF? TEST-VALUE-001 SGT-LOGIC-IN-LOGIC-PROPOSITION)
        (CL:PROGN (DELETED?-SETTER OLDOBJECT CL:T)))
       (CL:T
        (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
         (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001) "`" TEST-VALUE-001
          "' is not a valid case option")
         (CL:ERROR
          (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-001))))))))
    ((CL:EQ DEFINITIONTYPE KWD-LOGIC-IN-REDEFINITION)
     (REDEFINE-LOGIC-OBJECT NAME OLDOBJECT OBJECT))
    (CL:T
     (CL:LET* ((STREAM-002 (NEW-OUTPUT-STRING-STREAM)))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-002) "`" DEFINITIONTYPE
       "' is not a valid case option")
      (CL:ERROR
       (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-002))))))))

;;; (DEFUN REDEFINE-LOGIC-OBJECT ...)

(CL:DEFUN REDEFINE-LOGIC-OBJECT (NAME OLDOBJECT NEWOBJECT)
  (CL:LET*
   ((ORIGINATEDPROPS
     (REMOVE-DELETED-MEMBERS (ORIGINATED-PROPOSITIONS OLDOBJECT)))
    (EXCEPTPROPS (COPY ORIGINATEDPROPS)))
   (CL:LET* ((PROP NULL) (ITER-000 (%THE-CONS-LIST ORIGINATEDPROPS)))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ PROP (%%VALUE ITER-000))
     (CL:LET*
      ((SATELLITE NULL)
       (ITER-001 (%THE-CONS-LIST (SATELLITE-PROPOSITIONS PROP))))
      (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
       (CL:SETQ SATELLITE (%%VALUE ITER-001))
       (INSERT-NEW EXCEPTPROPS SATELLITE)
       (CL:SETQ ITER-001 (%%REST ITER-001))))
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   (CL:WHEN
    (CL:AND *WARNIFREDEFINE?*
     (CL:NOT
      (STRING-EQL? (STRINGIFIED-SOURCE OLDOBJECT)
       (STRINGIFIED-SOURCE NEWOBJECT))))
    (PL-LOG KWD-LOGIC-IN-LOW (WRAP-STRING "Redefining the ")
     (WRAP-STRING (NAME-OBJECT-METACLASS OLDOBJECT))
     (WRAP-STRING " named ") NAME))
   (TRANSFER-SYNONYMS OLDOBJECT NEWOBJECT)
   (TRANSFER-PROPOSITIONS-EXCEPT-FOR OLDOBJECT NEWOBJECT EXCEPTPROPS)
   (CL:WHEN (ISA? OLDOBJECT SGT-LOGIC-IN-LOGIC-NAMED-DESCRIPTION)
    (TRANSFER-DESCRIPTION-EXTENSION OLDOBJECT NEWOBJECT))
   (CL:LET* ((PROP NULL) (ITER-002 (%THE-CONS-LIST ORIGINATEDPROPS)))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-002 NIL)) DO
     (CL:SETQ PROP (%%VALUE ITER-002)) (DESTROY-PROPOSITION PROP)
     (CL:SETQ ITER-002 (%%REST ITER-002))))
   (CL:WHEN (CL:NOT (EQL? OLDOBJECT NEWOBJECT))
    (DESTROY-OBJECT OLDOBJECT))))

;;; (DEFGLOBAL *HANDLE-EXPLICITLY-QUALIFIED-LOGIC-OBJECTS?* ...)

(CL:DEFVAR *HANDLE-EXPLICITLY-QUALIFIED-LOGIC-OBJECTS?* CL:T)

;;; (DEFUN (EXPLICITLY-QUALIFIED-LOGIC-OBJECT-NAME? BOOLEAN) ...)

(CL:DEFUN EXPLICITLY-QUALIFIED-LOGIC-OBJECT-NAME? (OBJECTNAME DEFINITIONMODULE)
  (CL:WHEN *HANDLE-EXPLICITLY-QUALIFIED-LOGIC-OBJECTS?*
   (CL:SETQ DEFINITIONMODULE
    (CL:IF (CL:NOT (CL:EQ DEFINITIONMODULE NULL)) DEFINITIONMODULE
     *MODULE*))
   (CL:RETURN-FROM EXPLICITLY-QUALIFIED-LOGIC-OBJECT-NAME?
    (CL:NOT
     (VISIBLE-FROM? (%HOME-CONTEXT OBJECTNAME) DEFINITIONMODULE))))
  CL:NIL)

;;; (DEFUN (COERCE-TO-BOUND-OR-LOCAL-SURROGATE SURROGATE) ...)

(CL:DEFUN COERCE-TO-BOUND-OR-LOCAL-SURROGATE (SELF)
  (CL:LET* ((SURROGATE NULL))
   (CL:WHEN (EXPLICITLY-QUALIFIED-LOGIC-OBJECT-NAME? SELF *MODULE*)
    (CL:LET* ((*MODULE* (%HOME-CONTEXT SELF)) (*CONTEXT* *MODULE*))
     (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
     (CL:RETURN-FROM COERCE-TO-BOUND-OR-LOCAL-SURROGATE
      (COERCE-TO-BOUND-OR-LOCAL-SURROGATE SELF))))
   (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE SELF)))
    (CL:COND
     ((SUBTYPE-OF-SURROGATE? TEST-VALUE-000)
      (CL:PROGN (CL:SETQ SURROGATE SELF)))
     ((SUBTYPE-OF-SYMBOL? TEST-VALUE-000)
      (CL:PROGN
       (CL:SETQ SURROGATE
        (LOOKUP-SURROGATE-IN-MODULE (%SYMBOL-NAME SELF)
         (%HOME-CONTEXT SELF) CL:NIL))
       (CL:WHEN
        (CL:AND (CL:EQ SURROGATE NULL)
         (CL:NOT (CL:EQ (%HOME-CONTEXT SELF) *MODULE*)))
        (CL:SETQ SURROGATE
         (LOOKUP-SURROGATE-IN-MODULE (%SYMBOL-NAME SELF) *MODULE*
          CL:NIL)))))
     (CL:T
      (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
       (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" TEST-VALUE-000
        "' is not a valid case option")
       (CL:ERROR
        (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000)))))))
   (CL:WHEN
    (CL:AND (CL:NOT (CL:EQ SURROGATE NULL))
     (CL:NOT (CL:EQ (%SURROGATE-VALUE SURROGATE) NULL)))
    (CL:RETURN-FROM COERCE-TO-BOUND-OR-LOCAL-SURROGATE SURROGATE))
   (SHADOW-SURROGATE (%SYMBOL-NAME SELF))))

;;; (DEFUN (AXIOMS CONS) ...)

(CL:DEFUN AXIOMS (SELF)
  (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE SELF)))
   (CL:COND
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-LOGIC-OBJECT)
     (CL:PROGN
      (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS SELF)
       SYM-LOGIC-IN-LOGIC-OBJECT-AXIOMS NULL)))
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-PROPOSITION)
     (CL:PROGN
      (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS SELF)
       SYM-LOGIC-IN-LOGIC-PROPOSITION-AXIOMS NULL)))
    (CL:T
     (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" TEST-VALUE-000
       "' is not a valid case option")
      (CL:ERROR
       (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))))

;;; (DEFUN (AXIOMS-SETTER OBJECT) ...)

(CL:DEFUN AXIOMS-SETTER (SELF AXIOMS)
  (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE SELF)))
   (CL:COND
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-LOGIC-OBJECT)
     (CL:PROGN
      (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS SELF)
       SYM-LOGIC-IN-LOGIC-OBJECT-AXIOMS AXIOMS NULL)))
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-PROPOSITION)
     (CL:PROGN
      (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS SELF)
       SYM-LOGIC-IN-LOGIC-PROPOSITION-AXIOMS AXIOMS NULL)))
    (CL:T
     (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" TEST-VALUE-000
       "' is not a valid case option")
      (CL:ERROR
       (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000)))))))
  AXIOMS)

;;; (DEFUN DEFINITION-AXIOMS-HANDLER ...)

(CL:DEFUN DEFINITION-AXIOMS-HANDLER (SELF SLOT THEAXIOMS)
  (CL:SETQ SLOT SLOT)
  (CL:WHEN (STRING? THEAXIOMS)
   (CL:SETQ THEAXIOMS
    (UNSTRINGIFY-IN-MODULE (%WRAPPER-VALUE THEAXIOMS)
     (HOME-MODULE SELF))))
  (AXIOMS-SETTER SELF (COMBINE-AXIOM-LISTS (AXIOMS SELF) THEAXIOMS)))

;;; (DEFUN DEFINITION-HALF-RULE-HANDLER ...)

(CL:DEFUN DEFINITION-HALF-RULE-HANDLER (SELF SLOT BODY)
  (CL:LET*
   ((KEYWORD
     (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS SLOT)
      SYM-LOGIC-IN-STELLA-SLOT-OPTION-KEYWORD NULL))
    (ARROW
     (INTERN-SYMBOL-IN-MODULE (%SYMBOL-NAME KEYWORD)
      (GET-STELLA-MODULE "PL-KERNEL-KB" CL:T) CL:NIL))
    (NEWRULE NULL))
   (CL:WHEN (CL:EQ BODY NULL)
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (CL:LET* ((*PRINTREADABLY?* CL:T))
      (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
       "ERROR: Missing value for arrow keyword." EOL)
      (HELP-SIGNAL-PROPOSITION-ERROR STREAM-000 KWD-LOGIC-IN-ERROR))
     (CL:ERROR
      (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-000)))))
   (CL:WHEN (STRING? BODY)
    (CL:SETQ BODY
     (UNSTRINGIFY-IN-MODULE (%WRAPPER-VALUE BODY) (HOME-MODULE SELF))))
   (CL:SETQ NEWRULE (COMPLETE-RULE-DEFINITION SELF BODY ARROW))
   (AXIOMS-SETTER SELF (COMBINE-AXIOM-LISTS (AXIOMS SELF) NEWRULE))))

;;; (DEFUN (COMBINE-AXIOM-LISTS CONS) ...)

(CL:DEFUN COMBINE-AXIOM-LISTS (OLDAXIOMS NEWAXIOMS)
  (CL:WHEN (CL:EQ OLDAXIOMS NULL) (CL:SETQ OLDAXIOMS NIL))
  (CL:WHEN (CL:EQ NEWAXIOMS NULL) (CL:SETQ NEWAXIOMS NIL))
  (CL:LET* ((NORMALIZEDNEWAXIOMS NIL))
   (CL:COND
    ((CL:EQ (SAFE-PRIMARY-TYPE NEWAXIOMS) SGT-LOGIC-IN-STELLA-CONS)
     (CL:PROGN
      (CL:LET* ((ALWAYS?-000 CL:T))
       (CL:LET* ((ELT NULL) (ITER-000 NEWAXIOMS))
        (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
         (CL:SETQ ELT (%%VALUE ITER-000))
         (CL:WHEN (CL:NOT (CONS? ELT)) (CL:SETQ ALWAYS?-000 CL:NIL)
          (CL:RETURN))
         (CL:SETQ ITER-000 (%%REST ITER-000))))
       (CL:IF ALWAYS?-000
        (CL:PROGN (CL:SETQ NORMALIZEDNEWAXIOMS NEWAXIOMS))
        (CL:IF (CL:EQ (%%VALUE NEWAXIOMS) SYM-LOGIC-IN-STELLA-AND)
         (CL:PROGN (CL:SETQ NORMALIZEDNEWAXIOMS (%%REST NEWAXIOMS)))
         (CL:PROGN
          (CL:SETQ NORMALIZEDNEWAXIOMS (CONS NEWAXIOMS NIL))))))))
    (CL:T (CL:SETQ NORMALIZEDNEWAXIOMS (CONS NEWAXIOMS NIL))))
   (CONCATENATE OLDAXIOMS NORMALIZEDNEWAXIOMS)))

;;; (DEFUN (YIELD-RELATION-PARAMETERS-TREE CONS) ...)

(CL:DEFUN YIELD-RELATION-PARAMETERS-TREE (SELF DROPFUNCTIONPARAMETER? TYPED?)
  (CL:LET* ((PARAMETERLIST NIL) (PARAMETER NULL))
   (CL:LET*
    ((PNAME NULL) (ITER-000 (%THE-CONS-LIST (%IO-VARIABLE-NAMES SELF)))
     (PTYPE NULL)
     (ITER-001 (%THE-CONS-LIST (%IO-VARIABLE-TYPES SELF))))
    (CL:LOOP WHILE
     (CL:AND (CL:NOT (CL:EQ ITER-000 NIL))
      (CL:NOT (CL:EQ ITER-001 NIL)))
     DO (CL:SETQ PNAME (%%VALUE ITER-000))
     (CL:SETQ PTYPE (%%VALUE ITER-001)) (CL:SETQ PARAMETER PNAME)
     (CL:WHEN
      (CL:AND TYPED? (CL:NOT (CL:EQ PTYPE SGT-LOGIC-IN-STELLA-THING)))
      (CL:SETQ PARAMETER
       (CONS PARAMETER
        (CONS
         (INTERN-SYMBOL-IN-MODULE (%SYMBOL-NAME PTYPE)
          (%HOME-CONTEXT PTYPE) CL:T)
         NIL))))
     (CL:SETQ PARAMETERLIST (CONS PARAMETER PARAMETERLIST))
     (CL:SETQ ITER-000 (%%REST ITER-000))
     (CL:SETQ ITER-001 (%%REST ITER-001))))
   (CL:WHEN
    (CL:AND DROPFUNCTIONPARAMETER? (FUNCTION-DESCRIPTION? SELF))
    (CL:SETQ PARAMETERLIST (%%REST PARAMETERLIST)))
   (REVERSE PARAMETERLIST)))

;;; (DEFUN (COMPLETE-RULE-DEFINITION OBJECT) ...)

(CL:DEFUN COMPLETE-RULE-DEFINITION (SELF BODY ARROW)
  (CL:LET*
   ((PARAMETERS (YIELD-RELATION-PARAMETERS-TREE SELF CL:NIL CL:NIL)))
   (LIST* SYM-LOGIC-IN-STELLA-FORALL PARAMETERS
    (CONS
     (CONS ARROW
      (LIST*
       (CONS (DESCRIPTION-NAME SELF) (CONCATENATE PARAMETERS NIL))
       (WRAP-KIF-WITH-FORALL BODY PARAMETERS) NIL))
     NIL))))

;;; (DEFUN DEFINITION-KEYWORD-AXIOMS-HANDLER ...)

(CL:DEFUN DEFINITION-KEYWORD-AXIOMS-HANDLER (SELF SELFNAME KEY VALUE)
  (AXIOMS-SETTER SELF
   (COMBINE-AXIOM-LISTS (AXIOMS SELF)
    (HELP-DEFINE-KEYWORD-AXIOMS SELFNAME KEY VALUE))))

;;; (DEFUN (HELP-DEFINE-KEYWORD-AXIOMS CONS) ...)

(CL:DEFUN HELP-DEFINE-KEYWORD-AXIOMS (SELFNAME KEY VALUE)
  (CL:LET*
   ((AXIOMS NIL) (RELATIONNAME (INTERN-SYMBOL (%SYMBOL-NAME KEY))))
   (CL:COND
    ((CL:AND (SYMBOL? VALUE)
      (STRING-EQUAL? (%SYMBOL-NAME VALUE) "TRUE"))
     (CL:SETQ AXIOMS (CONS RELATIONNAME (CONS SELFNAME NIL))))
    ((CL:AND (SYMBOL? VALUE)
      (STRING-EQUAL? (%SYMBOL-NAME VALUE) "FALSE"))
     (CL:SETQ AXIOMS
      (LIST* SYM-LOGIC-IN-STELLA-NOT
       (CONS RELATIONNAME (CONS SELFNAME NIL)) NIL)))
    ((CL:AND (CONS? VALUE)
      (CL:NOT
       (MEMB?
        (GET-QUOTED-TREE "((SETOFALL KAPPA SETOF LISTOF) \"/LOGIC\")"
         "/LOGIC")
        (%%VALUE VALUE))))
     (CL:LET* ((VALUES VALUE) (SELFARG NULL))
      (CL:LET* ((VAL NULL) (ITER-000 VALUES))
       (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
        (CL:SETQ VAL (%%VALUE ITER-000))
        (CL:WHEN
         (CL:AND (SYMBOL? VAL)
          (STRING-EQUAL? (%SYMBOL-NAME VAL) "?SELF"))
         (CL:SETQ SELFARG VAL) (CL:RETURN))
        (CL:SETQ ITER-000 (%%REST ITER-000))))
      (CL:COND
       ((CL:NOT (CL:EQ SELFARG NULL))
        (CL:SETQ AXIOMS
         (CONS RELATIONNAME
          (SUBSTITUTE (COPY-CONS-LIST VALUES) SELFNAME SELFARG))))
       (CL:T
        (CL:LET* ((VAL NULL) (ITER-001 VALUES) (COLLECT-000 NULL))
         (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
          (CL:SETQ VAL (%%VALUE ITER-001))
          (CL:IF (CL:EQ COLLECT-000 NULL)
           (CL:PROGN
            (CL:SETQ COLLECT-000
             (CONS (CONS RELATIONNAME (CONS SELFNAME (CONS VAL NIL)))
              NIL))
            (CL:IF (CL:EQ AXIOMS NIL) (CL:SETQ AXIOMS COLLECT-000)
             (ADD-CONS-TO-END-OF-CONS-LIST AXIOMS COLLECT-000)))
           (CL:PROGN
            (CL:SETF (%%REST COLLECT-000)
             (CONS (CONS RELATIONNAME (CONS SELFNAME (CONS VAL NIL)))
              NIL))
            (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))
          (CL:SETQ ITER-001 (%%REST ITER-001))))))))
    (CL:T
     (CL:SETQ AXIOMS
      (CONS RELATIONNAME (CONS SELFNAME (CONS VALUE NIL))))))
   AXIOMS))

;;; (DEFUN ASSERT-KEYWORD-AXIOM ...)

(CL:DEFUN ASSERT-KEYWORD-AXIOM (SELF SELFNAME KEY VALUE)
  (CL:LET*
   ((AXIOM NULL)
    (ITER-000
     (COMBINE-AXIOM-LISTS NIL
      (HELP-DEFINE-KEYWORD-AXIOMS SELFNAME KEY VALUE))))
   (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
    (CL:SETQ AXIOM (%%VALUE ITER-000))
    (CL:LET*
     ((PROPS (UPDATE-PROPOSITION AXIOM KWD-LOGIC-IN-ASSERT-TRUE)))
     (CL:WHEN (CL:NOT (CL:EQ PROPS NULL))
      (CL:LET* ((P NULL) (ITER-001 PROPS))
       (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
        (CL:SETQ P (%%VALUE ITER-001))
        (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE SELF)))
         (CL:COND
          ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-LOGIC-OBJECT)
           (CL:PROGN (LINK-ORIGINATED-PROPOSITION SELF P)))
          ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-PROPOSITION)
           (CL:PROGN (LINK-ORIGINATED-PROPOSITION SELF P)))
          (CL:T)))
        (CL:SETQ ITER-001 (%%REST ITER-001))))))
    (CL:SETQ ITER-000 (%%REST ITER-000)))))

;;; (DEFGLOBAL *UNFINALIZED-OBJECTS* ...)

(CL:DEFVAR *UNFINALIZED-OBJECTS* NULL
  "List of objects whose definitions and/or associated
axioms and constraints are not yet processed.")

;;; (DEFSPECIAL *FINALIZEOBJECTSIMMEDIATELY?* ...)

(CL:DEFVAR *FINALIZEOBJECTSIMMEDIATELY?* CL:NIL)

;;; (DEFUN REGISTER-UNFINALIZED-OBJECT ...)

(CL:DEFUN REGISTER-UNFINALIZED-OBJECT (OBJECT)
  (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE OBJECT)))
   (CL:COND
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-LOGIC-OBJECT)
     (CL:PROGN (PUSH *UNFINALIZED-OBJECTS* OBJECT)))
    ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-PROPOSITION)
     (CL:PROGN (PUSH *UNFINALIZED-OBJECTS* OBJECT)))
    (CL:T
     (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
       "INTERNAL ERROR: can't register objects of type `"
       (PRIMARY-TYPE OBJECT) "' for finalization")
      (CL:ERROR
       (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000)))))))
  (CL:WHEN *FINALIZEOBJECTSIMMEDIATELY?* (FINALIZE-OBJECTS)))

;;; (DEFUN CLEANUP-UNFINALIZED-OBJECTS ...)

(CL:DEFUN CLEANUP-UNFINALIZED-OBJECTS ()
  (REMOVE-DELETED-MEMBERS *UNFINALIZED-OBJECTS*))

;;; (DEFUN LINK-ORIGINATED-PROPOSITION ...)

(CL:DEFUN LINK-ORIGINATED-PROPOSITION (OBJECT PROPOSITION)
  (CL:LET* ((PROPOSITIONS (ORIGINATED-PROPOSITIONS OBJECT)))
   (CL:WHEN (NULL-LIST? PROPOSITIONS) (CL:SETQ PROPOSITIONS (NEW-LIST))
    (ORIGINATED-PROPOSITIONS-SETTER OBJECT PROPOSITIONS))
   (PUSH PROPOSITIONS PROPOSITION)))

;;; (DEFUN (HELP-FINALIZE-OBJECT-AXIOMS (CONS OF PROPOSITION)) ...)

(CL:DEFUN HELP-FINALIZE-OBJECT-AXIOMS (THEAXIOMS)
  (CL:IF (CL:EQ THEAXIOMS NULL) NIL
   (CL:LET* ((PROPOSITIONS NIL) (RESULT NULL))
    (CL:LET* ((AXIOM NULL) (ITER-000 THEAXIOMS))
     (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
      (CL:SETQ AXIOM (%%VALUE ITER-000))
      (CL:SETQ RESULT
       (UPDATE-PROPOSITION AXIOM KWD-LOGIC-IN-ASSERT-TRUE))
      (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE RESULT)))
       (CL:COND
        ((CL:EQ TEST-VALUE-000 SGT-LOGIC-IN-STELLA-CONS)
         (CL:PROGN
          (CL:LET* ((R NULL) (ITER-001 RESULT))
           (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
            (CL:SETQ R (%%VALUE ITER-001))
            (CL:SETQ PROPOSITIONS (CONS R PROPOSITIONS))
            (CL:SETQ ITER-001 (%%REST ITER-001))))))
        ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-PROPOSITION)
         (CL:PROGN (CL:SETQ PROPOSITIONS (CONS RESULT PROPOSITIONS))))
        (CL:T (CL:RETURN-FROM HELP-FINALIZE-OBJECT-AXIOMS NIL))))
      (CL:SETQ ITER-000 (%%REST ITER-000))))
    (REVERSE PROPOSITIONS))))

;;; (DEFUN FINALIZE-OBJECT-AXIOMS ...)

(CL:DEFUN FINALIZE-OBJECT-AXIOMS (SELF)
  (CL:LET*
   ((*TERMSOURCEBEINGPARSED* STELLA::NULL-STRING)
    (*LOGIC-DIALECT* KWD-LOGIC-IN-KIF))
   (CL:DECLARE (CL:SPECIAL *TERMSOURCEBEINGPARSED* *LOGIC-DIALECT*))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING *TERMSOURCEBEINGPARSED*))
   (CL:LET*
    ((*MODULE*
      (CL:IF (CL:NOT (CL:EQ *ASSERTION-MODULE* NULL))
       *ASSERTION-MODULE* (HOME-MODULE SELF)))
     (*CONTEXT* *MODULE*))
    (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
    (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE SELF)))
     (CL:COND
      ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-LOGIC-OBJECT)
       (CL:PROGN
        (CL:SETQ *TERMSOURCEBEINGPARSED* (STRINGIFIED-SOURCE SELF))
        (CL:WHEN (CL:EQ (AXIOMS SELF) NULL)
         (CL:RETURN-FROM FINALIZE-OBJECT-AXIOMS))
        (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS SELF)
         SYM-LOGIC-IN-STELLA-BAD? TRUE-WRAPPER NULL)
        (CL:LET*
         ((THEAXIOMS (HELP-FINALIZE-OBJECT-AXIOMS (AXIOMS SELF))))
         (CL:IF (CL:EQ THEAXIOMS NIL)
          (CL:RETURN-FROM FINALIZE-OBJECT-AXIOMS)
          (CL:LET* ((P NULL) (ITER-000 THEAXIOMS))
           (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
            (CL:SETQ P (%%VALUE ITER-000))
            (LINK-ORIGINATED-PROPOSITION SELF P)
            (CL:SETQ ITER-000 (%%REST ITER-000))))))
        (AXIOMS-SETTER SELF NULL)
        (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS SELF)
         SYM-LOGIC-IN-STELLA-BAD? NULL NULL)))
      ((SUBTYPE-OF? TEST-VALUE-000 SGT-LOGIC-IN-LOGIC-PROPOSITION)
       (CL:PROGN
        (CL:SETQ *TERMSOURCEBEINGPARSED* (STRINGIFIED-SOURCE SELF))
        (CL:WHEN (CL:EQ (AXIOMS SELF) NULL)
         (CL:RETURN-FROM FINALIZE-OBJECT-AXIOMS))
        (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS SELF)
         SYM-LOGIC-IN-STELLA-BAD? TRUE-WRAPPER NULL)
        (CL:LET*
         ((THEAXIOMS (HELP-FINALIZE-OBJECT-AXIOMS (AXIOMS SELF))))
         (CL:IF (CL:EQ THEAXIOMS NIL)
          (CL:RETURN-FROM FINALIZE-OBJECT-AXIOMS)
          (CL:LET* ((P NULL) (ITER-001 THEAXIOMS))
           (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
            (CL:SETQ P (%%VALUE ITER-001))
            (LINK-ORIGINATED-PROPOSITION SELF P)
            (CL:SETQ ITER-001 (%%REST ITER-001))))))
        (AXIOMS-SETTER SELF NULL)
        (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS SELF)
         SYM-LOGIC-IN-STELLA-BAD? NULL NULL)))
      (CL:T
       (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
        (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" TEST-VALUE-000
         "' is not a valid case option")
        (CL:ERROR
         (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))))))

;;; (DEFUN CHECK-DESCRIPTION-ARGUMENT-TYPES ...)

(CL:DEFUN CHECK-DESCRIPTION-ARGUMENT-TYPES (SELF)
  (CL:LET* ((*MODULE* (HOME-MODULE SELF)) (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:LET*
    ((TYPE NULL) (ITER-000 (%THE-CONS-LIST (%IO-VARIABLE-TYPES SELF))))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ TYPE (%%VALUE ITER-000))
     (CL:LET* ((CLASS (GET-DESCRIPTION TYPE)))
      (CL:WHEN (CL:EQ CLASS NULL)
       (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
        (CL:LET* ((*PRINTREADABLY?* CL:T))
         (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
         (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
          "ERROR: Undefined class `" (%SYMBOL-NAME TYPE)
          "' appears as argument type" EOL
          "   in the definition of relation `" (DESCRIPTION-NAME SELF)
          "'." EOL "." EOL)
         (HELP-SIGNAL-PROPOSITION-ERROR STREAM-000 KWD-LOGIC-IN-ERROR))
        (CL:ERROR
         (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-000)))))
      (CL:WHEN (CL:NOT (CLASS-DESCRIPTION? CLASS))
       (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "Non-class `"
        (%SYMBOL-NAME TYPE) "' appears as argument type" EOL
        "in the definition of relation `" (DESCRIPTION-NAME SELF) "'."
        EOL EOL)))
     (CL:SETQ ITER-000 (%%REST ITER-000))))))

;;; (DEFUN FINALIZE-OBJECT ...)

(CL:DEFUN FINALIZE-OBJECT (SELF)
  (CL:WHEN (CL:OR (DELETED? SELF) (FINALIZED-OBJECT? SELF))
   (CL:RETURN-FROM FINALIZE-OBJECT))
  (CL:HANDLER-CASE
   (CL:LET* ((TEST-VALUE-001 (SAFE-PRIMARY-TYPE SELF)))
    (CL:COND
     ((SUBTYPE-OF? TEST-VALUE-001 SGT-LOGIC-IN-LOGIC-NAMED-DESCRIPTION)
      (CL:PROGN
       (CL:LET* ((TEST-VALUE-000 CL:NIL))
        (CL:IF (COERCE-WRAPPED-BOOLEAN-TO-BOOLEAN (BAD? SELF))
         (CL:SETQ TEST-VALUE-000 CL:T)
         (CL:LET* ((FOUND?-000 CL:NIL))
          (CL:LET*
           ((TYPE NULL)
            (ITER-000 (%THE-CONS-LIST (%IO-VARIABLE-TYPES SELF))))
           (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
            (CL:SETQ TYPE (%%VALUE ITER-000))
            (CL:WHEN (CL:= (%SYMBOL-ID TYPE) -1)
             (CL:SETQ FOUND?-000 CL:T) (CL:RETURN))
            (CL:SETQ ITER-000 (%%REST ITER-000))))
          (CL:SETQ TEST-VALUE-000 FOUND?-000)))
        (CL:WHEN TEST-VALUE-000 (CL:RETURN-FROM FINALIZE-OBJECT)))
       (FINALIZE-OBJECT-AXIOMS SELF)
       (CHECK-DESCRIPTION-ARGUMENT-TYPES SELF)))
     ((SUBTYPE-OF? TEST-VALUE-001 SGT-LOGIC-IN-LOGIC-LOGIC-OBJECT)
      (CL:PROGN
       (CL:WHEN (COERCE-WRAPPED-BOOLEAN-TO-BOOLEAN (BAD? SELF))
        (CL:RETURN-FROM FINALIZE-OBJECT))
       (FINALIZE-OBJECT-AXIOMS SELF)))
     ((SUBTYPE-OF? TEST-VALUE-001 SGT-LOGIC-IN-LOGIC-PROPOSITION)
      (CL:PROGN
       (CL:WHEN (COERCE-WRAPPED-BOOLEAN-TO-BOOLEAN (BAD? SELF))
        (CL:RETURN-FROM FINALIZE-OBJECT))
       (FINALIZE-OBJECT-AXIOMS SELF)))
     (CL:T)))
   (LOGIC-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     (EXCEPTION-MESSAGE E)))))

;;; (DEFUN (FINALIZED-OBJECT? BOOLEAN) ...)

(CL:DEFUN FINALIZED-OBJECT? (SELF)
  (CL:EQ (AXIOMS SELF) NULL))

;;; (DEFUN (OBJECTS-ARE-FINALIZED? BOOLEAN) ...)

(CL:DEFUN OBJECTS-ARE-FINALIZED? ()
  (CL:EQ (%THE-CONS-LIST *UNFINALIZED-OBJECTS*) NIL))

;;; (DEFSPECIAL *INHIBITOBJECTFINALIZATION?* ...)

(CL:DEFVAR *INHIBITOBJECTFINALIZATION?* CL:NIL
  "Used to prevent finalization from triggering in the
middle of 'delicate' computations.  Also used to prevent recursive
invocation of 'finalize-objects'.")

;;; (DEFUN FINALIZE-OBJECTS ...)

(CL:DEFUN FINALIZE-OBJECTS ()
  "Finalize all currently unfinalized objects.
The user-level entry point for this is `(process-definitions)'."
  (CL:WHEN
   (CL:OR *INHIBITOBJECTFINALIZATION?*
    (CL:EQ (%THE-CONS-LIST *UNFINALIZED-OBJECTS*) NIL)
    (CL:NOT (WORLD-STATE? *CONTEXT*)))
   (CL:RETURN-FROM FINALIZE-OBJECTS))
  (CL:LET*
   ((*INHIBITOBJECTFINALIZATION?* CL:T)
    (*TERMSOURCEBEINGPARSED* STELLA::NULL-STRING)
    (*DESCRIPTIONUNDERCONSTRUCTION* NULL)
    (*TERMUNDERCONSTRUCTION* NULL))
   (CL:DECLARE
    (CL:SPECIAL *INHIBITOBJECTFINALIZATION?* *TERMSOURCEBEINGPARSED*
     *DESCRIPTIONUNDERCONSTRUCTION* *TERMUNDERCONSTRUCTION*))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING *TERMSOURCEBEINGPARSED*))
   (FINALIZE-CLASSES-AND-SLOTS)
   (CL:LET*
    ((OBJECT NULL)
     (ITER-000 (%THE-CONS-LIST (REVERSE *UNFINALIZED-OBJECTS*))))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ OBJECT (%%VALUE ITER-000)) (FINALIZE-OBJECT OBJECT)
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   (CLEAR *UNFINALIZED-OBJECTS*)))

;;; (DEFUN (HELP-DEFINE-RELATION-FROM-PARSE-TREE NAMED-DESCRIPTION) ...)

(CL:DEFUN HELP-DEFINE-RELATION-FROM-PARSE-TREE (TREE STRINGIFIEDSOURCE)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING STRINGIFIEDSOURCE))
  #+MCL
  (CL:CHECK-TYPE STRINGIFIEDSOURCE CL:SIMPLE-STRING)
  (CL:LET*
   ((OPERATOR (%%VALUE TREE)) (NAME (%%VALUE (%%REST TREE)))
    (PARAMETERS (%%VALUE (%%REST (%%REST TREE))))
    (OPTIONS (NTH-REST TREE 3))
    (CLASS? (CL:EQ OPERATOR SYM-LOGIC-IN-LOGIC-DEFCONCEPT))
    (FUNCTION? (CL:EQ OPERATOR SYM-LOGIC-IN-LOGIC-DEFFUNCTION))
    (DESCRIPTION NULL))
   (CL:SETQ DESCRIPTION
    (GET-IDENTICAL-RELATION NAME STRINGIFIEDSOURCE))
   (CL:WHEN (CL:NOT (CL:EQ DESCRIPTION NULL))
    (CL:RETURN-FROM HELP-DEFINE-RELATION-FROM-PARSE-TREE DESCRIPTION))
   (CL:LET*
    ((PARAMETERNAMES NULL) (PARAMETERTYPES NULL)
     (VARIABLEARITY? CL:NIL))
    (CL:MULTIPLE-VALUE-SETQ
     (PARAMETERNAMES PARAMETERTYPES VARIABLEARITY?)
     (PARSE-RELATION-PARAMETERS-TREE PARAMETERS))
    (CL:SETQ DESCRIPTION
     (CREATE-PRIMITIVE-DESCRIPTION PARAMETERNAMES PARAMETERTYPES
      VARIABLEARITY? CLASS? FUNCTION? *MODULE*))
    (CL:SETQ *DESCRIPTIONUNDERCONSTRUCTION* DESCRIPTION)
    (STRINGIFIED-SOURCE-SETTER DESCRIPTION STRINGIFIEDSOURCE)
    (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS DESCRIPTION)
     SYM-LOGIC-IN-STELLA-BAD? TRUE-WRAPPER NULL)
    (BIND-LOGIC-OBJECT-TO-SURROGATE NAME DESCRIPTION)
    (ENSURE-DESCRIPTION-BODY DESCRIPTION)
    (PROCESS-DEFINITION-OPTIONS DESCRIPTION OPTIONS)
    (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS DESCRIPTION)
     SYM-LOGIC-IN-STELLA-BAD? NULL NULL)
    (REGISTER-UNFINALIZED-OBJECT DESCRIPTION) DESCRIPTION)))

;;; (DEFUN (PARSE-RELATION-PARAMETERS-TREE (LIST OF SYMBOL) (LIST OF TYPE) BOOLEAN) ...)

(CL:DEFUN PARSE-RELATION-PARAMETERS-TREE (PARAMETERS)
  (CL:WHEN (CL:EQ PARAMETERS NULL)
   (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
    (CL:LET* ((*PRINTREADABLY?* CL:T))
     (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
      "ERROR: Missing concept or relation parameters." EOL)
     (HELP-SIGNAL-PROPOSITION-ERROR STREAM-000 KWD-LOGIC-IN-ERROR))
    (CL:ERROR (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-000)))))
  (CL:LET*
   ((NAME NULL) (TYPE NULL) (PARAMETERNAMES (NEW-LIST))
    (PARAMETERTYPES (NEW-LIST)) (VARIABLEARITY? CL:NIL))
   (CL:LET* ((P NULL) (ITER-000 PARAMETERS))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ P (%%VALUE ITER-000))
     (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE P)))
      (CL:COND
       ((CL:EQ TEST-VALUE-000 SGT-LOGIC-IN-STELLA-CONS)
        (CL:PROGN
         (CL:WHEN
          (CL:NOT
           (CL:AND (CL:= (LENGTH P) 2) (SYMBOL? (%%VALUE P))
            (SYMBOL? (%%VALUE (%%REST P)))))
          (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
           (CL:LET* ((*PRINTREADABLY?* CL:T))
            (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
            (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001)
             "ERROR: Illegal parameter: `" P "'." EOL)
            (HELP-SIGNAL-PROPOSITION-ERROR STREAM-001
             KWD-LOGIC-IN-ERROR))
           (CL:ERROR
            (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-001)))))
         (CL:SETQ NAME (%%VALUE P))
         (CL:WHEN (CL:NOT (QUESTION-MARK-SYMBOL? NAME))
          (CL:LET* ((STREAM-002 (NEW-OUTPUT-STRING-STREAM)))
           (CL:LET* ((*PRINTREADABLY?* CL:T))
            (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
            (%%PRINT-STREAM (%NATIVE-STREAM STREAM-002)
             "ERROR: Expected a question mark variable: `" NAME "'."
             EOL)
            (HELP-SIGNAL-PROPOSITION-ERROR STREAM-002
             KWD-LOGIC-IN-ERROR))
           (CL:ERROR
            (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-002)))))
         (CL:SETQ TYPE (%%VALUE (%%REST P)))))
       ((SUBTYPE-OF-SYMBOL? TEST-VALUE-000)
        (CL:PROGN (CL:SETQ NAME P)
         (CL:WHEN (CL:NOT (QUESTION-MARK-SYMBOL? NAME))
          (CL:LET* ((STREAM-003 (NEW-OUTPUT-STRING-STREAM)))
           (CL:LET* ((*PRINTREADABLY?* CL:T))
            (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
            (%%PRINT-STREAM (%NATIVE-STREAM STREAM-003)
             "ERROR: Expected a question mark variable: `" NAME "'."
             EOL)
            (HELP-SIGNAL-PROPOSITION-ERROR STREAM-003
             KWD-LOGIC-IN-ERROR))
           (CL:ERROR
            (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-003)))))
         (CL:SETQ TYPE SGT-LOGIC-IN-STELLA-THING)))
       (CL:T
        (CL:LET* ((STREAM-004 (NEW-OUTPUT-STRING-STREAM)))
         (CL:LET* ((*PRINTREADABLY?* CL:T))
          (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
          (%%PRINT-STREAM (%NATIVE-STREAM STREAM-004)
           "ERROR: Illegal parameter: `" P "'." EOL)
          (HELP-SIGNAL-PROPOSITION-ERROR STREAM-004
           KWD-LOGIC-IN-ERROR))
         (CL:ERROR
          (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-004)))))))
     (CL:WHEN (SEQUENCE-VARIABLE-SYMBOL? NAME)
      (CL:SETQ VARIABLEARITY? CL:T))
     (CL:WHEN (MEMBER? PARAMETERNAMES NAME)
      (CL:LET* ((STREAM-005 (NEW-OUTPUT-STRING-STREAM)))
       (CL:LET* ((*PRINTREADABLY?* CL:T))
        (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
        (%%PRINT-STREAM (%NATIVE-STREAM STREAM-005)
         "ERROR: Duplicate relation parameter name: `" NAME "'." EOL)
        (HELP-SIGNAL-PROPOSITION-ERROR STREAM-005 KWD-LOGIC-IN-ERROR))
       (CL:ERROR
        (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-005)))))
     (PUSH PARAMETERNAMES NAME)
     (PUSH PARAMETERTYPES (COERCE-TO-BOUND-OR-LOCAL-SURROGATE TYPE))
     (CL:WHEN VARIABLEARITY? (CL:RETURN))
     (CL:SETQ ITER-000 (%%REST ITER-000))))
   (CL:WHEN (CL:EQ PARAMETERTYPES NULL)
    (CL:LET* ((STREAM-006 (NEW-OUTPUT-STRING-STREAM)))
     (CL:LET* ((*PRINTREADABLY?* CL:T))
      (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-006)
       "ERROR: Missing relation parameter list." EOL)
      (HELP-SIGNAL-PROPOSITION-ERROR STREAM-006 KWD-LOGIC-IN-ERROR))
     (CL:ERROR
      (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-006)))))
   (CL:WHEN (EMPTY? PARAMETERTYPES)
    (CL:LET* ((STREAM-007 (NEW-OUTPUT-STRING-STREAM)))
     (CL:LET* ((*PRINTREADABLY?* CL:T))
      (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-007)
       "ERROR: Empty relation parameter list." EOL)
      (HELP-SIGNAL-PROPOSITION-ERROR STREAM-007 KWD-LOGIC-IN-ERROR))
     (CL:ERROR
      (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-007)))))
   (CL:VALUES (REVERSE PARAMETERNAMES) (REVERSE PARAMETERTYPES)
    VARIABLEARITY?)))

;;; (DEFUN (GET-IDENTICAL-RELATION NAMED-DESCRIPTION) ...)

(CL:DEFUN GET-IDENTICAL-RELATION (NAME STRINGIFIEDSOURCE)
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING STRINGIFIEDSOURCE))
  #+MCL
  (CL:CHECK-TYPE STRINGIFIEDSOURCE CL:SIMPLE-STRING)
  (CL:LET*
   ((SURROGATE (LOOKUP-LOGIC-OBJECT-SURROGATE NAME *MODULE*))
    (SURROGATEVALUE
     (CL:IF (CL:NOT (CL:EQ SURROGATE NULL))
      (%SURROGATE-VALUE SURROGATE) NULL))
    (DESCRIPTION NULL))
   (CL:WHEN
    (CL:AND (CL:NOT (CL:EQ SURROGATEVALUE NULL))
     (ISA? SURROGATEVALUE SGT-LOGIC-IN-LOGIC-NAMED-DESCRIPTION))
    (CL:SETQ DESCRIPTION SURROGATEVALUE))
   (CL:WHEN (CL:NOT (CL:EQ DESCRIPTION NULL))
    (CL:WHEN
     (CL:AND
      (CL:NOT (COERCE-WRAPPED-BOOLEAN-TO-BOOLEAN (BAD? DESCRIPTION)))
      (STRING-EQL? (STRINGIFIED-SOURCE DESCRIPTION) STRINGIFIEDSOURCE))
     (CL:RETURN-FROM GET-IDENTICAL-RELATION DESCRIPTION)))
   NULL))

;;; (DEFMETHOD PROCESS-DEFINITION-OPTIONS ...)

(CL:DEFMETHOD PROCESS-DEFINITION-OPTIONS ((SELF NAMED-DESCRIPTION) OPTIONS)
  (CL:LET*
   ((KEY NULL) (VALUE NULL)
    (ITER-000 (%THE-PLIST (VET-OPTIONS OPTIONS NULL))))
   (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
    (CL:SETQ KEY (%%VALUE ITER-000))
    (CL:SETQ VALUE (%%VALUE (%%REST ITER-000)))
    (CL:WHEN (CL:NOT (RUN-OPTION-HANDLER? SELF KEY VALUE))
     (DEFINITION-KEYWORD-AXIOMS-HANDLER SELF (DESCRIPTION-NAME SELF)
      KEY VALUE))
    (CL:SETQ ITER-000 (%%REST (%%REST ITER-000)))))
  (CL:WHEN (CL:NOT (CLASS? SELF))
   (CL:LET*
    ((NAME (DESCRIPTION-NAME SELF)) (IOVARIABLES (%IO-VARIABLES SELF))
     (IOVARIABLETYPES (%IO-VARIABLE-TYPES SELF))
     (THEAXIOMS (AXIOMS SELF)) (TYPEDARGUMENTS NIL) (OPERATOR NULL)
     (FIRSTARG NULL) (ARGUMENTTYPEAXIOMS NIL))
    (CL:WHEN
     (CL:AND (CL:NOT (CL:EQ THEAXIOMS NULL))
      (MEMB? IOVARIABLETYPES SGT-LOGIC-IN-STELLA-THING))
     (CL:LET* ((AXIOM NULL) (ITER-001 THEAXIOMS))
      (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
       (CL:SETQ AXIOM (%%VALUE ITER-001))
       (CL:COND
        ((CL:EQ (SAFE-PRIMARY-TYPE AXIOM) SGT-LOGIC-IN-STELLA-CONS)
         (CL:PROGN (CL:SETQ OPERATOR (%%VALUE AXIOM))
          (CL:SETQ FIRSTARG (%%VALUE (%%REST AXIOM)))
          (CL:COND
           ((CL:AND
             (CL:EQ OPERATOR SYM-LOGIC-IN-PL-KERNEL-KB-NTH-DOMAIN)
             (CL:EQ FIRSTARG NAME)
             (INTEGER? (%%VALUE (%%REST (%%REST AXIOM)))))
            (CL:SETQ TYPEDARGUMENTS
             (CONS
              (CL:AREF
               (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY IOVARIABLES))
               (CL:THE CL:FIXNUM
                (%WRAPPER-VALUE (%%VALUE (%%REST (%%REST AXIOM))))))
              TYPEDARGUMENTS)))
           ((CL:AND (CL:EQ OPERATOR SYM-LOGIC-IN-PL-KERNEL-KB-DOMAIN)
             (CL:EQ FIRSTARG NAME))
            (CL:SETQ TYPEDARGUMENTS
             (CONS
              (CL:AREF
               (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY IOVARIABLES)) 0)
              TYPEDARGUMENTS)))
           ((CL:AND (CL:EQ OPERATOR SYM-LOGIC-IN-PL-KERNEL-KB-RANGE)
             (CL:EQ FIRSTARG NAME))
            (CL:SETQ TYPEDARGUMENTS
             (CONS (LAST IOVARIABLES) TYPEDARGUMENTS))))))
        (CL:T))
       (CL:SETQ ITER-001 (%%REST ITER-001)))))
    (CL:LET*
     ((TYPE NULL) (ITER-002 (%THE-CONS-LIST IOVARIABLETYPES))
      (VAR NULL) (VECTOR-000 IOVARIABLES) (INDEX-000 0)
      (LENGTH-000 (LENGTH VECTOR-000)) (I NULL-INTEGER) (ITER-003 0)
      (COLLECT-000 NULL))
     (CL:DECLARE (CL:TYPE CL:FIXNUM INDEX-000 LENGTH-000 I ITER-003))
     (CL:LOOP WHILE
      (CL:AND (CL:NOT (CL:EQ ITER-002 NIL))
       (CL:< INDEX-000 LENGTH-000))
      DO (CL:SETQ TYPE (%%VALUE ITER-002))
      (CL:SETQ VAR
       (CL:AREF (CL:THE CL:SIMPLE-VECTOR (%THE-ARRAY VECTOR-000))
        INDEX-000))
      (CL:SETQ I ITER-003)
      (CL:WHEN
       (CL:AND (CL:NOT (CL:EQ TYPE NULL))
        (CL:OR (CL:NOT (CL:EQ TYPE SGT-LOGIC-IN-STELLA-THING))
         (CL:NOT (MEMB? TYPEDARGUMENTS VAR))))
       (CL:IF (CL:EQ COLLECT-000 NULL)
        (CL:PROGN
         (CL:SETQ COLLECT-000
          (CONS
           (LIST* SYM-LOGIC-IN-PL-KERNEL-KB-NTH-DOMAIN NAME
            (CONS (WRAP-INTEGER I)
             (CONS
              (INTERN-SYMBOL-IN-MODULE (%SYMBOL-NAME TYPE)
               (%HOME-CONTEXT TYPE) CL:NIL)
              NIL)))
           NIL))
         (CL:IF (CL:EQ ARGUMENTTYPEAXIOMS NIL)
          (CL:SETQ ARGUMENTTYPEAXIOMS COLLECT-000)
          (ADD-CONS-TO-END-OF-CONS-LIST ARGUMENTTYPEAXIOMS
           COLLECT-000)))
        (CL:PROGN
         (CL:SETF (%%REST COLLECT-000)
          (CONS
           (LIST* SYM-LOGIC-IN-PL-KERNEL-KB-NTH-DOMAIN NAME
            (CONS (WRAP-INTEGER I)
             (CONS
              (INTERN-SYMBOL-IN-MODULE (%SYMBOL-NAME TYPE)
               (%HOME-CONTEXT TYPE) CL:NIL)
              NIL)))
           NIL))
         (CL:SETQ COLLECT-000 (%%REST COLLECT-000)))))
      (CL:SETQ ITER-002 (%%REST ITER-002))
      (CL:SETQ INDEX-000 (CL:1+ INDEX-000))
      (CL:SETQ ITER-003 (CL:1+ ITER-003))))
    (CL:WHEN (CL:NOT (CL:EQ ARGUMENTTYPEAXIOMS NIL))
     (AXIOMS-SETTER SELF
      (COMBINE-AXIOM-LISTS ARGUMENTTYPEAXIOMS THEAXIOMS))))))

;;; (DEFUN (DEFFUNCTION NAMED-DESCRIPTION) ...)

(CL:DEFUN %DEFFUNCTION (ARGS)
  "Define (or redefine) a logic function.  The accepted syntax is:
	 
 (deffunction <funconst> (<vardecl>+) [:-> <vardecl>]
    [:documentation <string>]
    [:<= <sentence>] | [:=> <sentence>] |
    [:<<= <sentence>] | [:=>> <sentence>] | 
    [:<=> <sentence>] | [:<=>> <sentence>] |
    [:<<=> <sentence>] | [:<<=>> <sentence>] |
    [:axioms {<sentence> | (<sentence>+)}]
    [<keyword-option>*])
	
Function parameters can be typed or untyped.  If the `:->' option is
supplied, it specifies the output variable of the function.  Otherwise,
the last variable in the parameter list is used as the output variable.
See `defrelation' for a description of `<keyword-option>'s.
"
  (CL:HANDLER-CASE
   (CL:RETURN-FROM %DEFFUNCTION (CALL-DEFFUNCTION ARGS))
   (LOGIC-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     (EXCEPTION-MESSAGE E))
    NULL)))

(CL:DEFUN DEFFUNCTION-EVALUATOR-WRAPPER (ARGUMENTS)
  (%DEFFUNCTION ARGUMENTS))

(CL:DEFMACRO DEFFUNCTION (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Define (or redefine) a logic function.  The accepted syntax is:
	 
 (deffunction <funconst> (<vardecl>+) [:-> <vardecl>]
    [:documentation <string>]
    [:<= <sentence>] | [:=> <sentence>] |
    [:<<= <sentence>] | [:=>> <sentence>] | 
    [:<=> <sentence>] | [:<=>> <sentence>] |
    [:<<=> <sentence>] | [:<<=>> <sentence>] |
    [:axioms {<sentence> | (<sentence>+)}]
    [<keyword-option>*])
	
Function parameters can be typed or untyped.  If the `:->' option is
supplied, it specifies the output variable of the function.  Otherwise,
the last variable in the parameter list is used as the output variable.
See `defrelation' for a description of `<keyword-option>'s.
"
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/DEFFUNCTION|)) (CL:MACRO-FUNCTION (CL:QUOTE DEFFUNCTION)))

;;; (DEFUN (CALL-DEFFUNCTION NAMED-DESCRIPTION) ...)

(CL:DEFUN CALL-DEFFUNCTION (ARGUMENTS)
  "Callable version of the `deffunction' command (which see).
Expects the same arguments as `deffunction' but supplied as a list."
  (CL:LET*
   ((DEFINITION
     (CONS SYM-LOGIC-IN-LOGIC-DEFFUNCTION
      (CONCATENATE ARGUMENTS NIL))))
   (CL:LET*
    ((*TERMSOURCEBEINGPARSED* (STRINGIFY DEFINITION))
     (*DESCRIPTIONUNDERCONSTRUCTION* NULL))
    (CL:DECLARE
     (CL:SPECIAL *TERMSOURCEBEINGPARSED*
      *DESCRIPTIONUNDERCONSTRUCTION*))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING *TERMSOURCEBEINGPARSED*))
    (CL:SETF (%%REST DEFINITION)
     (NORMALIZE-DEFFUNCTION-ARGUMENTS ARGUMENTS))
    (INTERN-LOGIC-OBJECT-SURROGATE (%%VALUE (%%REST DEFINITION)))
    (HELP-DEFINE-RELATION-FROM-PARSE-TREE DEFINITION
     *TERMSOURCEBEINGPARSED*))))

;;; (DEFUN (NORMALIZE-DEFFUNCTION-ARGUMENTS CONS) ...)

(CL:DEFUN NORMALIZE-DEFFUNCTION-ARGUMENTS (ARGUMENTS)
  (CL:LET*
   ((NAME (%%VALUE ARGUMENTS))
    (PARAMETERS (%%VALUE (%%REST ARGUMENTS)))
    (OPTIONS (%%REST (%%REST ARGUMENTS))))
   (CL:WHEN (CL:NOT (SYMBOL? NAME))
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (CL:LET* ((*PRINTREADABLY?* CL:T))
      (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
       "ERROR: Illegal function name where symbol expected: `" NAME
       "'." EOL)
      (HELP-SIGNAL-PROPOSITION-ERROR STREAM-000 KWD-LOGIC-IN-ERROR))
     (CL:ERROR
      (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-000)))))
   (CL:COND
    ((CL:EQ (SAFE-PRIMARY-TYPE PARAMETERS) SGT-LOGIC-IN-STELLA-CONS)
     (CL:PROGN
      (CL:LOOP WHILE (CL:NOT (CL:EQ OPTIONS NIL)) DO
       (CL:WHEN
        (CL:AND (CL:EQ (%%VALUE OPTIONS) KWD-LOGIC-IN-->)
         (CL:NOT (CL:EQ (%%VALUE (%%REST OPTIONS)) NULL)))
        (CL:SETQ PARAMETERS
         (CONCATENATE PARAMETERS
          (CONS (%%VALUE (%%REST OPTIONS)) NIL)))
        (SECOND-SETTER ARGUMENTS PARAMETERS)
        (FIRST-SETTER OPTIONS NULL) (SECOND-SETTER OPTIONS NULL)
        (CL:SETQ OPTIONS (REMOVE (%%REST (%%REST ARGUMENTS)) NULL))
        (CL:SETF (%%REST (%%REST ARGUMENTS)) OPTIONS) (CL:RETURN))
       (CL:SETQ OPTIONS (%%REST (%%REST OPTIONS))))
      (CL:WHEN (CL:EQ PARAMETERS NIL)
       (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
        (CL:LET* ((*PRINTREADABLY?* CL:T))
         (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
         (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001)
          "ERROR: Cannot have 0-arity functions." EOL)
         (HELP-SIGNAL-PROPOSITION-ERROR STREAM-001 KWD-LOGIC-IN-ERROR))
        (CL:ERROR
         (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-001)))))))
    (CL:T
     (CL:LET* ((STREAM-002 (NEW-OUTPUT-STRING-STREAM)))
      (CL:LET* ((*PRINTREADABLY?* CL:T))
       (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
       (%%PRINT-STREAM (%NATIVE-STREAM STREAM-002)
        "ERROR: Illegal parameter list: `" PARAMETERS "'." EOL)
       (HELP-SIGNAL-PROPOSITION-ERROR STREAM-002 KWD-LOGIC-IN-ERROR))
      (CL:ERROR
       (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-002))))))
   ARGUMENTS))

;;; (DEFUN (DEFRELATION NAMED-DESCRIPTION) ...)

(CL:DEFUN %DEFRELATION (ARGS)
  "Define (or redefine) a logic relation.  The accepted syntax is:
	 
 (defrelation <relconst> (<vardecl>+)
    [:documentation <string>]
    [:<= <sentence>] | [:=> <sentence>] |
    [:<<= <sentence>] | [:=>> <sentence>] | 
    [:<=> <sentence>] | [:<=>> <sentence>] |
    [:<<=> <sentence>] | [:<<=>> <sentence>] |
    [:axioms {<sentence> | (<sentence>+)}]
    [<keyword-option>*])
	
Relation parameters can be typed or untyped.
`<keyword-option>' represents a keyword followed by a value that states an
assertion about `<relconst>'.  For example, including the option `:foo bar'
states that the proposition `(foo <relconst> bar)' is true.  `:foo (bar fum)'
states that both `(foo <relconst> bar)' and `(foo <relconst> fum)' are true.
`:foo true' states that `(foo <relconst>)' is true, `:foo false' states that
`(not (foo <relconst>))' is true.
"
  (CL:HANDLER-CASE
   (CL:RETURN-FROM %DEFRELATION (CALL-DEFRELATION ARGS))
   (LOGIC-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     (EXCEPTION-MESSAGE E))
    NULL)))

(CL:DEFUN DEFRELATION-EVALUATOR-WRAPPER (ARGUMENTS)
  (%DEFRELATION ARGUMENTS))

(CL:DEFMACRO DEFRELATION (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Define (or redefine) a logic relation.  The accepted syntax is:
	 
 (defrelation <relconst> (<vardecl>+)
    [:documentation <string>]
    [:<= <sentence>] | [:=> <sentence>] |
    [:<<= <sentence>] | [:=>> <sentence>] | 
    [:<=> <sentence>] | [:<=>> <sentence>] |
    [:<<=> <sentence>] | [:<<=>> <sentence>] |
    [:axioms {<sentence> | (<sentence>+)}]
    [<keyword-option>*])
	
Relation parameters can be typed or untyped.
`<keyword-option>' represents a keyword followed by a value that states an
assertion about `<relconst>'.  For example, including the option `:foo bar'
states that the proposition `(foo <relconst> bar)' is true.  `:foo (bar fum)'
states that both `(foo <relconst> bar)' and `(foo <relconst> fum)' are true.
`:foo true' states that `(foo <relconst>)' is true, `:foo false' states that
`(not (foo <relconst>))' is true.
"
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/DEFRELATION|)) (CL:MACRO-FUNCTION (CL:QUOTE DEFRELATION)))

;;; (DEFUN (CALL-DEFRELATION NAMED-DESCRIPTION) ...)

(CL:DEFUN CALL-DEFRELATION (ARGUMENTS)
  "Callable version of the `defrelation' command (which see).
Expects the same arguments as `defrelation' but supplied as a list."
  (CL:LET*
   ((DEFINITION
     (CONS SYM-LOGIC-IN-LOGIC-DEFRELATION
      (CONCATENATE ARGUMENTS NIL))))
   (CL:LET*
    ((*TERMSOURCEBEINGPARSED* (STRINGIFY DEFINITION))
     (*DESCRIPTIONUNDERCONSTRUCTION* NULL))
    (CL:DECLARE
     (CL:SPECIAL *TERMSOURCEBEINGPARSED*
      *DESCRIPTIONUNDERCONSTRUCTION*))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING *TERMSOURCEBEINGPARSED*))
    (CL:SETF (%%REST DEFINITION)
     (NORMALIZE-DEFRELATION-ARGUMENTS ARGUMENTS))
    (INTERN-LOGIC-OBJECT-SURROGATE (%%VALUE (%%REST DEFINITION)))
    (HELP-DEFINE-RELATION-FROM-PARSE-TREE DEFINITION
     *TERMSOURCEBEINGPARSED*))))

;;; (DEFUN (NORMALIZE-DEFRELATION-ARGUMENTS CONS) ...)

(CL:DEFUN NORMALIZE-DEFRELATION-ARGUMENTS (ARGUMENTS)
  (CL:LET*
   ((NAME (%%VALUE ARGUMENTS))
    (PARAMETERS (%%VALUE (%%REST ARGUMENTS)))
    (OPTIONS (%%REST (%%REST ARGUMENTS))))
   (CL:WHEN (CL:NOT (SYMBOL? NAME))
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (CL:LET* ((*PRINTREADABLY?* CL:T))
      (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
       "ERROR: Illegal relation name where symbol expected: `" NAME
       "'." EOL)
      (HELP-SIGNAL-PROPOSITION-ERROR STREAM-000 KWD-LOGIC-IN-ERROR))
     (CL:ERROR
      (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-000)))))
   (CL:WHEN (CL:NOT (CONS? PARAMETERS))
    (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
     (CL:LET* ((*PRINTREADABLY?* CL:T))
      (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001)
       "ERROR: Illegal parameter list: `" PARAMETERS "'." EOL)
      (HELP-SIGNAL-PROPOSITION-ERROR STREAM-001 KWD-LOGIC-IN-ERROR))
     (CL:ERROR
      (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-001)))))
   (CL:WHEN (CL:EQ PARAMETERS NIL)
    (CL:LET* ((STREAM-002 (NEW-OUTPUT-STRING-STREAM)))
     (CL:LET* ((*PRINTREADABLY?* CL:T))
      (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-002)
       "ERROR: Cannot have 0-arity relations." EOL)
      (HELP-SIGNAL-PROPOSITION-ERROR STREAM-002 KWD-LOGIC-IN-ERROR))
     (CL:ERROR
      (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-002)))))
   (CL:WHEN (MEMBER? OPTIONS KWD-LOGIC-IN-->)
    (CL:LET* ((STREAM-003 (NEW-OUTPUT-STRING-STREAM)))
     (CL:LET* ((*PRINTREADABLY?* CL:T))
      (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-003)
       "ERROR: 'defrelation' does not allow a return value (':->') clause."
       EOL)
      (HELP-SIGNAL-PROPOSITION-ERROR STREAM-003 KWD-LOGIC-IN-ERROR))
     (CL:ERROR
      (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-003)))))
   ARGUMENTS))

;;; (DEFUN (DEFCONCEPT NAMED-DESCRIPTION) ...)

(CL:DEFUN %DEFCONCEPT (ARGS)
  "Define (or redefine) a concept.  The accepted syntax is:
	 
 (defconcept <conceptconst> [(<var> <parent>*)]
    [:documentation <string>]
    [:<= <sentence>] | [:=> <sentence>] |
    [:<<= <sentence>] | [:=>> <sentence>] | 
    [:<=> <sentence>] | [:<=>> <sentence>] | [:<<=> <sentence>] |
    [:<<=>> <sentence>] |
    [:axioms {<sentence> | (<sentence>+)}] |
    <keyword-option>*)
	
Declaration of a concept variable `<var>' is optional, unless any
implication (arrow) options are supplied that need to reference it.  A
possibly empty list of concept names following `<var>' is taken as the list
of parents of `<conceptconst>'.  Alternatively, parents can be specified
via the `:=>' option.  If no parents are specified, the parent of
`<conceptconst>' is taken to be THING.  `<keyword-option>' represents a
keyword followed by a value that states an assertion about `<conceptconst>'.
See `defrelation' for a description of `<keyword-option>'s.
"
  (CL:HANDLER-CASE (CL:RETURN-FROM %DEFCONCEPT (CALL-DEFCONCEPT ARGS))
   (LOGIC-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     (EXCEPTION-MESSAGE E))
    NULL)))

(CL:DEFUN DEFCONCEPT-EVALUATOR-WRAPPER (ARGUMENTS)
  (%DEFCONCEPT ARGUMENTS))

(CL:DEFMACRO DEFCONCEPT (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Define (or redefine) a concept.  The accepted syntax is:
	 
 (defconcept <conceptconst> [(<var> <parent>*)]
    [:documentation <string>]
    [:<= <sentence>] | [:=> <sentence>] |
    [:<<= <sentence>] | [:=>> <sentence>] | 
    [:<=> <sentence>] | [:<=>> <sentence>] | [:<<=> <sentence>] |
    [:<<=>> <sentence>] |
    [:axioms {<sentence> | (<sentence>+)}] |
    <keyword-option>*)
	
Declaration of a concept variable `<var>' is optional, unless any
implication (arrow) options are supplied that need to reference it.  A
possibly empty list of concept names following `<var>' is taken as the list
of parents of `<conceptconst>'.  Alternatively, parents can be specified
via the `:=>' option.  If no parents are specified, the parent of
`<conceptconst>' is taken to be THING.  `<keyword-option>' represents a
keyword followed by a value that states an assertion about `<conceptconst>'.
See `defrelation' for a description of `<keyword-option>'s.
"
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/DEFCONCEPT|)) (CL:MACRO-FUNCTION (CL:QUOTE DEFCONCEPT)))

;;; (DEFUN (CALL-DEFCONCEPT NAMED-DESCRIPTION) ...)

(CL:DEFUN CALL-DEFCONCEPT (ARGUMENTS)
  "Callable version of the `defconcept' command (which see).
Expects the same arguments as `defconcept' but supplied as a list."
  (CL:LET*
   ((DEFINITION
     (CONS SYM-LOGIC-IN-LOGIC-DEFCONCEPT (CONCATENATE ARGUMENTS NIL))))
   (CL:LET*
    ((*TERMSOURCEBEINGPARSED* (STRINGIFY DEFINITION))
     (*DESCRIPTIONUNDERCONSTRUCTION* NULL))
    (CL:DECLARE
     (CL:SPECIAL *TERMSOURCEBEINGPARSED*
      *DESCRIPTIONUNDERCONSTRUCTION*))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING *TERMSOURCEBEINGPARSED*))
    (CL:SETF (%%REST DEFINITION)
     (NORMALIZE-DEFCONCEPT-ARGUMENTS ARGUMENTS))
    (INTERN-LOGIC-OBJECT-SURROGATE (%%VALUE (%%REST DEFINITION)))
    (HELP-DEFINE-RELATION-FROM-PARSE-TREE DEFINITION
     *TERMSOURCEBEINGPARSED*))))

;;; (DEFUN (NORMALIZE-DEFCONCEPT-ARGUMENTS CONS) ...)

(CL:DEFUN NORMALIZE-DEFCONCEPT-ARGUMENTS (ARGUMENTS)
  (CL:LET*
   ((NAME (%%VALUE ARGUMENTS)) (PARAMETERS NULL)
    (SELFVARIABLE SYM-LOGIC-IN-LOGIC-?SELF) (SUPERS NIL)
    (IMPLIESRULES NIL))
   (CL:WHEN (CL:NOT (SYMBOL? NAME))
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (CL:LET* ((*PRINTREADABLY?* CL:T))
      (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
       "ERROR: Illegal concept name where symbol expected: `" NAME "'."
       EOL)
      (HELP-SIGNAL-PROPOSITION-ERROR STREAM-000 KWD-LOGIC-IN-ERROR))
     (CL:ERROR
      (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-000)))))
   (CL:WHEN (CONS? (%%VALUE (%%REST ARGUMENTS)))
    (CL:SETQ PARAMETERS (%%VALUE (%%REST ARGUMENTS))))
   (CL:COND
    ((CL:NOT (CL:EQ PARAMETERS NULL))
     (CL:WHEN (CONS? (%%VALUE PARAMETERS))
      (CL:SETQ PARAMETERS (%%VALUE PARAMETERS)))
     (CL:COND ((CL:EQ PARAMETERS NIL) (CL:SETQ SUPERS NIL))
      ((QUESTION-MARK-SYMBOL? (%%VALUE PARAMETERS))
       (CL:SETQ SELFVARIABLE (%%VALUE PARAMETERS))
       (CL:SETQ SUPERS (%%REST PARAMETERS)))
      ((SYMBOL? (%%VALUE PARAMETERS)) (CL:SETQ SUPERS PARAMETERS))
      (CL:T
       (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
        (CL:LET* ((*PRINTREADABLY?* CL:T))
         (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
         (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001)
          "ERROR: Illegal parameter list: `"
          (%%VALUE (%%REST ARGUMENTS)) "'." EOL)
         (HELP-SIGNAL-PROPOSITION-ERROR STREAM-001 KWD-LOGIC-IN-ERROR))
        (CL:ERROR
         (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-001))))))
     (CL:LET* ((SUPER NULL) (ITER-000 SUPERS))
      (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
       (CL:SETQ SUPER (%%VALUE ITER-000))
       (CL:SETQ IMPLIESRULES (CONS KWD-LOGIC-IN-=> IMPLIESRULES))
       (CL:SETQ IMPLIESRULES
        (CONS (CONS SUPER (CONS SELFVARIABLE NIL)) IMPLIESRULES))
       (CL:SETQ ITER-000 (%%REST ITER-000))))
     (CL:SETQ IMPLIESRULES (REVERSE IMPLIESRULES))
     (CL:SETF (%%REST ARGUMENTS)
      (CONS (CONS (CONS SELFVARIABLE (CONS NAME NIL)) NIL)
       (CONCATENATE IMPLIESRULES
        (CONCATENATE (%%REST (%%REST ARGUMENTS)) NIL)))))
    ((CL:EQ (%%REST ARGUMENTS) NIL)
     (CL:SETF (%%REST ARGUMENTS)
      (CONS (CONS (CONS SELFVARIABLE (CONS NAME NIL)) NIL) NIL)))
    ((KEYWORD? (%%VALUE (%%REST ARGUMENTS)))
     (CL:SETF (%%REST (%%REST ARGUMENTS))
      (CONS (%%VALUE (%%REST ARGUMENTS))
       (CONCATENATE (%%REST (%%REST ARGUMENTS)) NIL)))
     (SECOND-SETTER ARGUMENTS
      (CONS (CONS SELFVARIABLE (CONS NAME NIL)) NIL))))
   ARGUMENTS))

;;; (DEFUN (DEFINE-RELATION-FROM-PARSE-TREE NAMED-DESCRIPTION) ...)

(CL:DEFUN DEFINE-RELATION-FROM-PARSE-TREE (TREE)
  (CL:LET* ((TEST-VALUE-000 (%%VALUE TREE)))
   (CL:COND
    ((CL:EQ TEST-VALUE-000 SYM-LOGIC-IN-LOGIC-DEFCONCEPT)
     (CALL-DEFCONCEPT (%%REST TREE)))
    ((CL:EQ TEST-VALUE-000 SYM-LOGIC-IN-LOGIC-DEFRELATION)
     (CALL-DEFRELATION (%%REST TREE)))
    ((CL:EQ TEST-VALUE-000 SYM-LOGIC-IN-LOGIC-DEFFUNCTION)
     (CALL-DEFFUNCTION (%%REST TREE)))
    (CL:T
     (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" TEST-VALUE-000
       "' is not a valid case option")
      (CL:ERROR
       (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))))

;;; (DEFUN (DEFOBJECT LOGIC-OBJECT) ...)

(CL:DEFUN %DEFOBJECT (ARGS)
  "Define (or redefine) a logic instance.  The accepted syntax is:
	 
 (defobject <constant>
    [:documentation <string>]
    [<keyword-option>*])
	
`<keyword-option>' represents a keyword followed by a value
that states an assertion about <constant>.  See `defrelation' for a
description of `<keyword-option>'s.

`defobject' provides a sugar-coated way to assert a collection of facts
about a logic constant, but otherwise adds nothing in terms of functionality.
"
  (CL:HANDLER-CASE (CL:RETURN-FROM %DEFOBJECT (CALL-DEFOBJECT ARGS))
   (LOGIC-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     (EXCEPTION-MESSAGE E))
    NULL)))

(CL:DEFUN DEFOBJECT-EVALUATOR-WRAPPER (ARGUMENTS)
  (%DEFOBJECT ARGUMENTS))

(CL:DEFMACRO DEFOBJECT (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Define (or redefine) a logic instance.  The accepted syntax is:
	 
 (defobject <constant>
    [:documentation <string>]
    [<keyword-option>*])
	
`<keyword-option>' represents a keyword followed by a value
that states an assertion about <constant>.  See `defrelation' for a
description of `<keyword-option>'s.

`defobject' provides a sugar-coated way to assert a collection of facts
about a logic constant, but otherwise adds nothing in terms of functionality.
"
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/DEFOBJECT|)) (CL:MACRO-FUNCTION (CL:QUOTE DEFOBJECT)))

;;; (DEFUN (DEFINSTANCE LOGIC-OBJECT) ...)

(CL:DEFUN %DEFINSTANCE (ARGS)
  "Define (or redefine) a logic instance (`definstance' is an alias
for `defobject' which see)."
  (CL:HANDLER-CASE (CL:RETURN-FROM %DEFINSTANCE (CALL-DEFOBJECT ARGS))
   (LOGIC-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     (EXCEPTION-MESSAGE E))
    NULL)))

(CL:DEFUN DEFINSTANCE-EVALUATOR-WRAPPER (ARGUMENTS)
  (%DEFINSTANCE ARGUMENTS))

(CL:DEFMACRO DEFINSTANCE (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Define (or redefine) a logic instance (`definstance' is an alias
for `defobject' which see)."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/DEFINSTANCE|)) (CL:MACRO-FUNCTION (CL:QUOTE DEFINSTANCE)))

;;; (DEFUN (CALL-DEFOBJECT LOGIC-OBJECT) ...)

(CL:DEFUN CALL-DEFOBJECT (ARGUMENTS)
  "Callable version of the `defobject' command (which see).
Expects the same arguments as `defobject' but supplied as a list."
  (CL:LET*
   ((DEFINITION
     (CONS SYM-LOGIC-IN-LOGIC-DEFOBJECT (CONCATENATE ARGUMENTS NIL)))
    (NAME NULL) (OPTIONS NIL) (TERM NULL))
   (CL:LET* ((*TERMSOURCEBEINGPARSED* (STRINGIFY DEFINITION)))
    (CL:DECLARE (CL:SPECIAL *TERMSOURCEBEINGPARSED*))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING *TERMSOURCEBEINGPARSED*))
    (CL:SETQ ARGUMENTS (NORMALIZE-DEFOBJECT-ARGUMENTS ARGUMENTS))
    (CL:SETQ OPTIONS (%%REST ARGUMENTS))
    (CL:COND
     ((CONS? (%%VALUE ARGUMENTS))
      (CL:SETQ NAME (INTERN-SYMBOL (STRINGIFY (%%VALUE ARGUMENTS))))
      (CL:SETQ TERM (CONCEIVE-TERM (%%VALUE ARGUMENTS)))
      (CL:WHEN (CL:EQ TERM NULL)
       (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
        (CL:LET* ((*PRINTREADABLY?* CL:T))
         (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
         (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
          "ERROR: Illegal object name or term: `" NAME "'." EOL)
         (HELP-SIGNAL-PROPOSITION-ERROR STREAM-000 KWD-LOGIC-IN-ERROR))
        (CL:ERROR
         (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-000))))))
     (CL:T (CL:SETQ NAME (%%VALUE ARGUMENTS))
      (INTERN-LOGIC-OBJECT-SURROGATE NAME)
      (CL:SETQ TERM (CREATE-LOGIC-INSTANCE NULL NULL))))
    (CL:COND
     ((SUBTYPE-OF? (SAFE-PRIMARY-TYPE TERM)
       SGT-LOGIC-IN-LOGIC-LOGIC-OBJECT)
      (CL:PROGN
       (STRINGIFIED-SOURCE-SETTER TERM *TERMSOURCEBEINGPARSED*)
       (BIND-LOGIC-OBJECT-TO-SURROGATE NAME TERM)
       (PROCESS-DEFINITION-OPTIONS TERM OPTIONS)
       (REGISTER-UNFINALIZED-OBJECT TERM)))
     (CL:T (BIND-LOGIC-OBJECT-TO-SURROGATE NAME TERM)
      (CL:LET*
       ((*MODULE*
         (CL:IF (CL:NOT (CL:EQ *ASSERTION-MODULE* NULL))
          *ASSERTION-MODULE* *MODULE*))
        (*CONTEXT* *MODULE*))
       (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
       (CL:LET*
        ((KEY NULL) (VALUE NULL)
         (ITER-000 (%THE-PLIST (VET-OPTIONS OPTIONS NULL))))
        (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
         (CL:SETQ KEY (%%VALUE ITER-000))
         (CL:SETQ VALUE (%%VALUE (%%REST ITER-000)))
         (ASSERT-KEYWORD-AXIOM TERM NAME KEY VALUE)
         (CL:SETQ ITER-000 (%%REST (%%REST ITER-000))))))))
    TERM)))

;;; (DEFUN (NORMALIZE-DEFOBJECT-ARGUMENTS CONS) ...)

(CL:DEFUN NORMALIZE-DEFOBJECT-ARGUMENTS (ARGUMENTS)
  (CL:LET* ((NAME (%%VALUE ARGUMENTS)) (OPTIONS (%%REST ARGUMENTS)))
   (CL:WHEN (CL:NOT (CL:OR (SYMBOL? NAME) (CONS? NAME)))
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (CL:LET* ((*PRINTREADABLY?* CL:T))
      (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
       "ERROR: Illegal object name where symbol or function term expected: `"
       NAME "'." EOL)
      (HELP-SIGNAL-PROPOSITION-ERROR STREAM-000 KWD-LOGIC-IN-ERROR))
     (CL:ERROR
      (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-000)))))
   (CL:SETQ OPTIONS OPTIONS) ARGUMENTS))

;;; (DEFMETHOD PROCESS-DEFINITION-OPTIONS ...)

(CL:DEFMETHOD PROCESS-DEFINITION-OPTIONS ((SELF LOGIC-OBJECT) OPTIONS)
  (CL:LET*
   ((KEY NULL) (VALUE NULL)
    (ITER-000 (%THE-PLIST (VET-OPTIONS OPTIONS NULL))))
   (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
    (CL:SETQ KEY (%%VALUE ITER-000))
    (CL:SETQ VALUE (%%VALUE (%%REST ITER-000)))
    (CL:WHEN (CL:NOT (RUN-OPTION-HANDLER? SELF KEY VALUE))
     (DEFINITION-KEYWORD-AXIOMS-HANDLER SELF (OBJECT-NAME SELF) KEY
      VALUE))
    (CL:SETQ ITER-000 (%%REST (%%REST ITER-000))))))

;;; (DEFUN (DEFPROPOSITION PROPOSITION) ...)

(CL:DEFUN %DEFPROPOSITION (ARGS)
  "Define (or redefine) a named proposition.  The accepted syntax is:
	 
 (defproposition <name> <sentence>
    [:documentation <string>]
    [:forward-only? {true | false}]
    [:backward-only? {true | false}]
    [:dont-optimize? {true | false}]
    [:confidence-level {:strict | :default}]
    [<keyword-option>*])
	
<sentence> can be any sentence that is legal as a top-level assertion.
<name> can be a string or symbol and will be bound to the asserted
proposition represented by <sentence>.  After this definition every
occurrence of <name> will be replaced by the associated proposition.

The options :forward-only? and :backward-only? can be used to tell the
inference engine to only use the rule in forward or backward direction
(this can also be achieved by using the `<<=' or `=>>' implication
arrows).  :dont-optimize?  tells the inference engine to not rearrange
the order of clauses in the antecedent of a rule and instead evaluate
them in their original order.  :confidence-level can be used to mark a
proposition as default only.

`<keyword-option>' represents a keyword followed by a value
that states an assertion about the proposition <name>.  See `defrelation'
for a description of `<keyword-option>'s.
"
  (CL:HANDLER-CASE
   (CL:RETURN-FROM %DEFPROPOSITION (CALL-DEFPROPOSITION ARGS))
   (LOGIC-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     (EXCEPTION-MESSAGE E))
    NULL)))

(CL:DEFUN DEFPROPOSITION-EVALUATOR-WRAPPER (ARGUMENTS)
  (%DEFPROPOSITION ARGUMENTS))

(CL:DEFMACRO DEFPROPOSITION (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Define (or redefine) a named proposition.  The accepted syntax is:
	 
 (defproposition <name> <sentence>
    [:documentation <string>]
    [:forward-only? {true | false}]
    [:backward-only? {true | false}]
    [:dont-optimize? {true | false}]
    [:confidence-level {:strict | :default}]
    [<keyword-option>*])
	
<sentence> can be any sentence that is legal as a top-level assertion.
<name> can be a string or symbol and will be bound to the asserted
proposition represented by <sentence>.  After this definition every
occurrence of <name> will be replaced by the associated proposition.

The options :forward-only? and :backward-only? can be used to tell the
inference engine to only use the rule in forward or backward direction
(this can also be achieved by using the `<<=' or `=>>' implication
arrows).  :dont-optimize?  tells the inference engine to not rearrange
the order of clauses in the antecedent of a rule and instead evaluate
them in their original order.  :confidence-level can be used to mark a
proposition as default only.

`<keyword-option>' represents a keyword followed by a value
that states an assertion about the proposition <name>.  See `defrelation'
for a description of `<keyword-option>'s.
"
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/DEFPROPOSITION|)) (CL:MACRO-FUNCTION (CL:QUOTE DEFPROPOSITION)))

;;; (DEFUN (DEFRULE PROPOSITION) ...)

(CL:DEFUN %DEFRULE (ARGS)
  "Define (or redefine) a named rule (`defrule' is an alias
for `defproposition' which see)."
  (CL:HANDLER-CASE (CL:RETURN-FROM %DEFRULE (CALL-DEFPROPOSITION ARGS))
   (LOGIC-EXCEPTION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     (EXCEPTION-MESSAGE E))
    NULL)))

(CL:DEFUN DEFRULE-EVALUATOR-WRAPPER (ARGUMENTS)
  (%DEFRULE ARGUMENTS))

(CL:DEFMACRO DEFRULE (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Define (or redefine) a named rule (`defrule' is an alias
for `defproposition' which see)."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/DEFRULE|)) (CL:MACRO-FUNCTION (CL:QUOTE DEFRULE)))

;;; (DEFUN (CALL-DEFPROPOSITION PROPOSITION) ...)

(CL:DEFUN CALL-DEFPROPOSITION (ARGUMENTS)
  "Callable version of the `defproposition' command (which see).
Expects the same arguments as `defproposition' but supplied as a list."
  (CL:LET*
   ((DEFINITION
     (CONS SYM-LOGIC-IN-LOGIC-DEFPROPOSITION
      (CONCATENATE ARGUMENTS NIL)))
    (NAME NULL) (OPTIONS NIL) (CONCEPTION NULL) (PROPOSITION NULL)
    (OLDTRUTHVALUE NULL))
   (CL:LET* ((*TERMSOURCEBEINGPARSED* (STRINGIFY DEFINITION)))
    (CL:DECLARE (CL:SPECIAL *TERMSOURCEBEINGPARSED*))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING *TERMSOURCEBEINGPARSED*))
    (CL:SETQ ARGUMENTS (NORMALIZE-DEFPROPOSITION-ARGUMENTS ARGUMENTS))
    (CL:SETQ NAME (%%VALUE ARGUMENTS))
    (INTERN-LOGIC-OBJECT-SURROGATE NAME)
    (CL:SETQ CONCEPTION
     (SMART-UPDATE-PROPOSITION (%%VALUE (%%REST ARGUMENTS))
      KWD-LOGIC-IN-CONCEIVE))
    (CL:COND
     ((CL:EQ CONCEPTION NULL)
      (CL:RETURN-FROM CALL-DEFPROPOSITION NULL))
     ((CONS? CONCEPTION)
      (CL:SETQ PROPOSITION (CONJOIN-PROPOSITIONS CONCEPTION))
      (CL:SETQ PROPOSITION
       (FASTEN-DOWN-ONE-PROPOSITION PROPOSITION CL:NIL)))
     (CL:T (CL:SETQ PROPOSITION CONCEPTION)))
    (CL:SETQ OPTIONS (%%REST (%%REST ARGUMENTS)))
    (STRINGIFIED-SOURCE-SETTER PROPOSITION *TERMSOURCEBEINGPARSED*)
    (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS PROPOSITION)
     SYM-LOGIC-IN-STELLA-BAD? TRUE-WRAPPER NULL)
    (BIND-LOGIC-OBJECT-TO-SURROGATE NAME PROPOSITION)
    (PROCESS-DEFINITION-OPTIONS PROPOSITION OPTIONS)
    (CL:WHEN (CL:EQ (%KIND PROPOSITION) KWD-LOGIC-IN-FORALL)
     (CL:LET*
      ((SATELLITE NULL)
       (ITER-000
        (%THE-CONS-LIST (SATELLITE-PROPOSITIONS PROPOSITION))))
      (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
       (CL:SETQ SATELLITE (%%VALUE ITER-000))
       (DESTROY-PROPOSITION SATELLITE)
       (CL:SETQ ITER-000 (%%REST ITER-000))))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS PROPOSITION)
      SYM-LOGIC-IN-LOGIC-SATELLITE-PROPOSITIONS NULL NULL))
    (CL:SETQ OLDTRUTHVALUE
     (ACCESS-IN-CONTEXT (%TRUTH-VALUE PROPOSITION)
      (%HOME-CONTEXT PROPOSITION) CL:NIL))
    (CL:COND
     ((CL:EQ
       (LOOKUP-ANNOTATION PROPOSITION KWD-LOGIC-IN-CONFIDENCE-LEVEL)
       KWD-LOGIC-IN-DEFAULT)
      (REMOVE-ANNOTATION PROPOSITION KWD-LOGIC-IN-CONFIDENCE-LEVEL)
      (UPDATE-PROPOSITION-TRUTH-VALUE PROPOSITION
       KWD-LOGIC-IN-PRESUME-TRUE))
     (CL:T
      (UPDATE-PROPOSITION-TRUTH-VALUE PROPOSITION
       KWD-LOGIC-IN-ASSERT-TRUE)))
    (CL:WHEN
     (CL:EQ OLDTRUTHVALUE
      (ACCESS-IN-CONTEXT (%TRUTH-VALUE PROPOSITION)
       (%HOME-CONTEXT PROPOSITION) CL:NIL))
     (RUN-GOES-TRUE-DEMONS PROPOSITION))
    (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS PROPOSITION)
     SYM-LOGIC-IN-STELLA-BAD? NULL NULL)
    (REGISTER-UNFINALIZED-OBJECT PROPOSITION) PROPOSITION)))

;;; (DEFUN (NORMALIZE-DEFPROPOSITION-ARGUMENTS CONS) ...)

(CL:DEFUN NORMALIZE-DEFPROPOSITION-ARGUMENTS (ARGUMENTS)
  (CL:LET*
   ((NAME (%%VALUE ARGUMENTS))
    (PROPOSITION (%%VALUE (%%REST ARGUMENTS))) (OPTIONS NULL)
    (VALUE NULL) (ANNOTATIONS NIL))
   (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE (%%VALUE ARGUMENTS))))
    (CL:COND ((SUBTYPE-OF-SYMBOL? TEST-VALUE-000))
     ((SUBTYPE-OF-STRING? TEST-VALUE-000)
      (CL:SETQ NAME
       (INTERN-SYMBOL (%WRAPPER-VALUE (%%VALUE ARGUMENTS))))
      (FIRST-SETTER ARGUMENTS NAME))
     (CL:T
      (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
       (CL:LET* ((*PRINTREADABLY?* CL:T))
        (CL:DECLARE (CL:SPECIAL *PRINTREADABLY?*))
        (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
         "ERROR: Illegal proposition name where symbol or string expected: `"
         NAME "'." EOL)
        (HELP-SIGNAL-PROPOSITION-ERROR STREAM-000 KWD-LOGIC-IN-ERROR))
       (CL:ERROR
        (NEW-PROPOSITION-ERROR (THE-STRING-READER STREAM-000)))))))
   (CL:SETQ OPTIONS (VET-OPTIONS (%%REST (%%REST ARGUMENTS)) NULL))
   (CL:SETQ VALUE (LOOKUP OPTIONS KWD-LOGIC-IN-FORWARD?))
   (CL:WHEN (CL:NOT (CL:EQ VALUE NULL))
    (REMOVE-AT OPTIONS KWD-LOGIC-IN-FORWARD?)
    (INSERT-AT OPTIONS KWD-LOGIC-IN-FORWARD-ONLY? VALUE))
   (CL:SETQ VALUE (LOOKUP OPTIONS KWD-LOGIC-IN-BACKWARD?))
   (CL:WHEN (CL:NOT (CL:EQ VALUE NULL))
    (REMOVE-AT OPTIONS KWD-LOGIC-IN-BACKWARD?)
    (INSERT-AT OPTIONS KWD-LOGIC-IN-BACKWARD-ONLY? VALUE))
   (CL:SETQ VALUE (LOOKUP OPTIONS KWD-LOGIC-IN-CONFIDENCE-LEVEL))
   (CL:WHEN (CL:NOT (CL:EQ VALUE NULL))
    (CL:SETQ ANNOTATIONS
     (CONCATENATE ANNOTATIONS
      (LIST* KWD-LOGIC-IN-CONFIDENCE-LEVEL VALUE NIL)))
    (REMOVE-AT OPTIONS KWD-LOGIC-IN-CONFIDENCE-LEVEL))
   (CL:SETQ VALUE (LOOKUP OPTIONS KWD-LOGIC-IN-WEIGHT))
   (CL:WHEN (CL:NOT (CL:EQ VALUE NULL))
    (CL:SETQ ANNOTATIONS
     (CONCATENATE ANNOTATIONS (LIST* KWD-LOGIC-IN-WEIGHT VALUE NIL)))
    (REMOVE-AT OPTIONS KWD-LOGIC-IN-WEIGHT))
   (CL:WHEN (CL:NOT (CL:EQ ANNOTATIONS NIL))
    (SECOND-SETTER ARGUMENTS
     (LIST* SYM-LOGIC-IN-LOGIC-ABOUT PROPOSITION
      (CONCATENATE ANNOTATIONS NIL))))
   (CL:SETF (%%REST (%%REST ARGUMENTS)) (%THE-PLIST OPTIONS)) ARGUMENTS))

;;; (DEFMETHOD PROCESS-DEFINITION-OPTIONS ...)

(CL:DEFMETHOD PROCESS-DEFINITION-OPTIONS ((SELF PROPOSITION) OPTIONS)
  (AXIOMS-SETTER SELF NULL)
  (CL:LET*
   ((KEY NULL) (VALUE NULL)
    (ITER-000 (%THE-PLIST (VET-OPTIONS OPTIONS NULL))))
   (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
    (CL:SETQ KEY (%%VALUE ITER-000))
    (CL:SETQ VALUE (%%VALUE (%%REST ITER-000)))
    (CL:WHEN (CL:NOT (RUN-OPTION-HANDLER? SELF KEY VALUE))
     (DEFINITION-KEYWORD-AXIOMS-HANDLER SELF (OBJECT-NAME SELF) KEY
      VALUE))
    (CL:SETQ ITER-000 (%%REST (%%REST ITER-000))))))

;;; (DEFGLOBAL *LOGIC-RELEVANT-STELLA-COMMANDS* ...)

(CL:DEFVAR *LOGIC-RELEVANT-STELLA-COMMANDS* NULL)

;;; (DEFUN (COMMAND< BOOLEAN) ...)

(CL:DEFUN COMMAND< (COMMAND1 COMMAND2)
  (STRING-LESS? (VISIBLE-NAME (%SLOT-NAME COMMAND1) CL:NIL)
   (VISIBLE-NAME (%SLOT-NAME COMMAND2) CL:NIL)))

;;; (DEFUN (LIST-LOGIC-COMMANDS (LIST OF METHOD-SLOT)) ...)

(CL:DEFUN LIST-LOGIC-COMMANDS ()
  (CL:LET* ((COMMANDS (NEW-LIST)))
   (CL:LET*
    ((FUNCTION NULL)
     (ITER-000 (ALL-FUNCTIONS (GET-STELLA-MODULE "/LOGIC" CL:T) CL:T))
     (COLLECT-000 NULL))
    (CL:LOOP WHILE (NEXT? ITER-000) DO
     (CL:SETQ FUNCTION (%VALUE ITER-000))
     (CL:WHEN
      (CL:AND
       (%WRAPPER-VALUE
        (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
         SYM-LOGIC-IN-STELLA-METHOD-COMMAND? FALSE-WRAPPER))
       (PUBLIC? FUNCTION))
      (CL:IF (CL:EQ COLLECT-000 NULL)
       (CL:PROGN (CL:SETQ COLLECT-000 (CONS FUNCTION NIL))
        (CL:IF (CL:EQ (%THE-CONS-LIST COMMANDS) NIL)
         (CL:SETF (%THE-CONS-LIST COMMANDS) COLLECT-000)
         (ADD-CONS-TO-END-OF-CONS-LIST (%THE-CONS-LIST COMMANDS)
          COLLECT-000)))
       (CL:PROGN (CL:SETF (%%REST COLLECT-000) (CONS FUNCTION NIL))
        (CL:SETQ COLLECT-000 (%%REST COLLECT-000)))))))
   (CL:LET*
    ((STELLACOMMAND NULL) (ITER-001 *LOGIC-RELEVANT-STELLA-COMMANDS*)
     (COLLECT-001 NULL))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
     (CL:SETQ STELLACOMMAND (%%VALUE ITER-001))
     (CL:IF (CL:EQ COLLECT-001 NULL)
      (CL:PROGN
       (CL:SETQ COLLECT-001 (CONS (LOOKUP-COMMAND STELLACOMMAND) NIL))
       (CL:IF (CL:EQ (%THE-CONS-LIST COMMANDS) NIL)
        (CL:SETF (%THE-CONS-LIST COMMANDS) COLLECT-001)
        (ADD-CONS-TO-END-OF-CONS-LIST (%THE-CONS-LIST COMMANDS)
         COLLECT-001)))
      (CL:PROGN
       (CL:SETF (%%REST COLLECT-001)
        (CONS (LOOKUP-COMMAND STELLACOMMAND) NIL))
       (CL:SETQ COLLECT-001 (%%REST COLLECT-001))))
     (CL:SETQ ITER-001 (%%REST ITER-001))))
   (SORT COMMANDS (CL:FUNCTION COMMAND<))))

;;; (DEFUN HELP ...)

(CL:DEFUN %HELP (COMMANDS)
  "Describe specific commands, or print a list of available commands."
  (CL:LET* ((THECOMMANDS COMMANDS))
   (CL:COND
    ((CL:EQ THECOMMANDS NIL)
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
      "The following commands are available (type `(help <command>+)'"
      EOL "to get command-specific documentation):" EOL EOL)
     (CL:LET* ((ALLCOMMANDS (LIST-LOGIC-COMMANDS)))
      (CL:LET* ((COMMAND NULL) (ITER-000 (%THE-CONS-LIST ALLCOMMANDS)))
       (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
        (CL:SETQ COMMAND (%%VALUE ITER-000))
        (CL:WHEN
         (CL:NOT
          (CL:EQ
           (%WRAPPER-VALUE
            (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS COMMAND)
             SYM-LOGIC-IN-STELLA-DOCUMENTATION NULL-STRING-WRAPPER))
           STELLA::NULL-STRING))
         (PRINT-DOCUMENTATION COMMAND STANDARD-OUTPUT CL:T))
        (CL:SETQ ITER-000 (%%REST ITER-000))))
      (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL
       "Undocumented Commands:" EOL EOL)
      (CL:LET* ((COMMAND NULL) (ITER-001 (%THE-CONS-LIST ALLCOMMANDS)))
       (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-001 NIL)) DO
        (CL:SETQ COMMAND (%%VALUE ITER-001))
        (CL:WHEN
         (CL:EQ
          (%WRAPPER-VALUE
           (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS COMMAND)
            SYM-LOGIC-IN-STELLA-DOCUMENTATION NULL-STRING-WRAPPER))
          STELLA::NULL-STRING)
         (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
          (%SLOT-NAME COMMAND) ":" EOL))
        (CL:SETQ ITER-001 (%%REST ITER-001))))))
    (CL:T
     (CL:LET* ((COMMANDNAME NULL) (ITER-002 THECOMMANDS))
      (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-002 NIL)) DO
       (CL:SETQ COMMANDNAME (%%VALUE ITER-002))
       (CL:LET* ((COMMAND (LOOKUP-COMMAND COMMANDNAME)))
        (CL:IF (CL:NOT (CL:EQ COMMAND NULL))
         (PRINT-DOCUMENTATION COMMAND STANDARD-OUTPUT CL:NIL)
         (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT)
          "Undefined command: `" COMMANDNAME "'" EOL)))
       (CL:SETQ ITER-002 (%%REST ITER-002))))))))

(CL:DEFUN HELP-EVALUATOR-WRAPPER (ARGUMENTS)
  (%HELP ARGUMENTS))

(CL:DEFMACRO HELP (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "Describe specific commands, or print a list of available commands."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/LOGIC/HELP|)) (CL:MACRO-FUNCTION (CL:QUOTE HELP)))

(CL:DEFUN HELP-STARTUP-LOGIC-IN1 ()
  (CL:PROGN
   (CL:SETQ KWD-LOGIC-IN-TRACE-SUBGOALS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TRACE-SUBGOALS" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-TRACE-SOLUTIONS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TRACE-SOLUTIONS" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-TRACE-CLASSIFIER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TRACE-CLASSIFIER" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-ITERATIVE-DEEPENING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ITERATIVE-DEEPENING" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-JUSTIFICATIONS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "JUSTIFICATIONS" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-JUST-IN-TIME-INFERENCE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "JUST-IN-TIME-INFERENCE" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-EMIT-THINKING-DOTS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "EMIT-THINKING-DOTS" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-GOAL-TREE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "GOAL-TREE" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-CLASSIFIER-INFERENCES
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CLASSIFIER-INFERENCES" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-CLOSED-WORLD
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CLOSED-WORLD" NULL 2))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-SET-FEATURE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "SET-FEATURE" NULL 0))
   (CL:SETQ KWD-LOGIC-IN-COMMON-LISP
    (INTERN-RIGID-SYMBOL-WRT-MODULE "COMMON-LISP" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-FUNCTION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "FUNCTION" NULL 2))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-UNSET-FEATURE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "UNSET-FEATURE" NULL 0))
   (CL:SETQ KWD-LOGIC-IN-REALISTIC
    (INTERN-RIGID-SYMBOL-WRT-MODULE "REALISTIC" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-BYE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "BYE" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-EXIT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "EXIT" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-HALT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "HALT" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-QUIT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "QUIT" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-STOP
    (INTERN-RIGID-SYMBOL-WRT-MODULE "STOP" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-DEFINE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFINE" NULL 2))
   (CL:SETQ SYM-LOGIC-IN-STELLA-DEFMODULE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFMODULE"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SGT-LOGIC-IN-STELLA-CONS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONS"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ KWD-LOGIC-IN-FINALIZE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "FINALIZE" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-OPTIONS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "OPTIONS" NULL 2))
   (CL:SETQ SYM-LOGIC-IN-STELLA-LOAD
    (INTERN-RIGID-SYMBOL-WRT-MODULE "LOAD"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-STELLA-CLEAR-MODULE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CLEAR-MODULE"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-STELLA-DEFCLASS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFCLASS"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-STELLA-DEFSLOT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFSLOT"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-STELLA-DEFUN
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFUN"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-STELLA-DEFMETHOD
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFMETHOD"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-DEFCONCEPT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFCONCEPT" NULL 0))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-DEFFUNCTION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFFUNCTION" NULL 0))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-DEFRELATION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFRELATION" NULL 0))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-DEFOBJECT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFOBJECT" NULL 0))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-DEFINSTANCE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFINSTANCE" NULL 0))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-DESTROY
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DESTROY" NULL 0))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-IN-DIALECT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "IN-DIALECT" NULL 0))
   (CL:SETQ SYM-LOGIC-IN-STELLA-CC
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CC"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ KWD-LOGIC-IN-IMMEDIATE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "IMMEDIATE" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-ALWAYS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ALWAYS" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-DEFERRED
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFERRED" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-CHECK-DUPLICATES?
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CHECK-DUPLICATES?" NULL 2))
   (CL:SETQ SGT-LOGIC-IN-STELLA-BOOLEAN
    (INTERN-RIGID-SYMBOL-WRT-MODULE "BOOLEAN"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ KWD-LOGIC-IN-MODULE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MODULE" NULL 2))
   (CL:SETQ SGT-LOGIC-IN-STELLA-MODULE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MODULE"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ KWD-LOGIC-IN-ASSERTION-MODULE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ASSERTION-MODULE" NULL 2))
   (CL:SETQ SGT-LOGIC-IN-STELLA-IDENTITY
    (INTERN-RIGID-SYMBOL-WRT-MODULE "IDENTITY"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ KWD-LOGIC-IN-LOW
    (INTERN-RIGID-SYMBOL-WRT-MODULE "LOW" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-MEDIUM
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MEDIUM" NULL 2))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-LOAD-DIRECTORY
    (INTERN-RIGID-SYMBOL-WRT-MODULE "LOAD-DIRECTORY" NULL 0))
   (CL:SETQ KWD-LOGIC-IN-WHITE-SPACE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "WHITE-SPACE" NULL 2))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-DEMO
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEMO" NULL 0))
   (CL:SETQ KWD-LOGIC-IN-LEVEL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "LEVEL" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-NONE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "NONE" NULL 2))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-TIME-COMMAND
    (INTERN-RIGID-SYMBOL-WRT-MODULE "TIME-COMMAND" NULL 0))
   (CL:SETQ KWD-LOGIC-IN-PORT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PORT" NULL 2))
   (CL:SETQ SGT-LOGIC-IN-STELLA-INTEGER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "INTEGER"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-START-ONTOSAURUS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "START-ONTOSAURUS" NULL 0))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-START-POWERLOOM-SERVER
    (INTERN-RIGID-SYMBOL-WRT-MODULE "START-POWERLOOM-SERVER" NULL 0))))

(CL:DEFUN HELP-STARTUP-LOGIC-IN2 ()
  (CL:PROGN
   (CL:SETQ KWD-LOGIC-IN-HOST
    (INTERN-RIGID-SYMBOL-WRT-MODULE "HOST" NULL 2))
   (CL:SETQ SGT-LOGIC-IN-STELLA-STRING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "STRING"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ KWD-LOGIC-IN-DEBUG-LEVEL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEBUG-LEVEL" NULL 2))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-START-POWERLOOM-GUI
    (INTERN-RIGID-SYMBOL-WRT-MODULE "START-POWERLOOM-GUI" NULL 0))
   (CL:SETQ KWD-LOGIC-IN-ERROR
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ERROR" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-WARNING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "WARNING" NULL 2))
   (CL:SETQ SGT-LOGIC-IN-LOGIC-NAMED-DESCRIPTION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "NAMED-DESCRIPTION" NULL 1))
   (CL:SETQ SGT-LOGIC-IN-LOGIC-PROPOSITION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PROPOSITION" NULL 1))
   (CL:SETQ SGT-LOGIC-IN-LOGIC-DESCRIPTION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DESCRIPTION" NULL 1))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-MODULE-LOGIC-DIALECT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "MODULE-LOGIC-DIALECT" NULL 0))
   (CL:SETQ KWD-LOGIC-IN-KIF
    (INTERN-RIGID-SYMBOL-WRT-MODULE "KIF" NULL 2))
   (CL:SETQ SGT-LOGIC-IN-STELLA-RELATION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RELATION"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SGT-LOGIC-IN-LOGIC-LOGIC-OBJECT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "LOGIC-OBJECT" NULL 1))
   (CL:SETQ KWD-LOGIC-IN-DEFINITION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFINITION" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-REDEFINITION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "REDEFINITION" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-PROPER-DEFINITION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PROPER-DEFINITION" NULL 2))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-OBJECT-AXIOMS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "OBJECT-AXIOMS" NULL 0))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-PROPOSITION-AXIOMS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PROPOSITION-AXIOMS" NULL 0))
   (CL:SETQ SYM-LOGIC-IN-STELLA-SLOT-OPTION-KEYWORD
    (INTERN-RIGID-SYMBOL-WRT-MODULE "SLOT-OPTION-KEYWORD"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-STELLA-AND
    (INTERN-RIGID-SYMBOL-WRT-MODULE "AND"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SGT-LOGIC-IN-STELLA-THING
    (INTERN-RIGID-SYMBOL-WRT-MODULE "THING"
     (GET-STELLA-MODULE "/STELLA" CL:T) 1))
   (CL:SETQ SYM-LOGIC-IN-STELLA-FORALL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "FORALL"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-STELLA-NOT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "NOT"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ KWD-LOGIC-IN-ASSERT-TRUE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ASSERT-TRUE" NULL 2))
   (CL:SETQ SYM-LOGIC-IN-STELLA-BAD?
    (INTERN-RIGID-SYMBOL-WRT-MODULE "BAD?"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-PL-KERNEL-KB-NTH-DOMAIN
    (INTERN-RIGID-SYMBOL-WRT-MODULE "NTH-DOMAIN"
     (GET-STELLA-MODULE "/PL-KERNEL-KB" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-PL-KERNEL-KB-DOMAIN
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DOMAIN"
     (GET-STELLA-MODULE "/PL-KERNEL-KB" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-PL-KERNEL-KB-RANGE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "RANGE"
     (GET-STELLA-MODULE "/PL-KERNEL-KB" CL:T) 0))
   (CL:SETQ KWD-LOGIC-IN-->
    (INTERN-RIGID-SYMBOL-WRT-MODULE "->" NULL 2))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-?SELF
    (INTERN-RIGID-SYMBOL-WRT-MODULE "?SELF" NULL 0))
   (CL:SETQ KWD-LOGIC-IN-=>
    (INTERN-RIGID-SYMBOL-WRT-MODULE "=>" NULL 2))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-DEFPROPOSITION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFPROPOSITION" NULL 0))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-DEFRULE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFRULE" NULL 0))
   (CL:SETQ KWD-LOGIC-IN-CONCEIVE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONCEIVE" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-FORALL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "FORALL" NULL 2))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-SATELLITE-PROPOSITIONS
    (INTERN-RIGID-SYMBOL-WRT-MODULE "SATELLITE-PROPOSITIONS" NULL 0))
   (CL:SETQ KWD-LOGIC-IN-CONFIDENCE-LEVEL
    (INTERN-RIGID-SYMBOL-WRT-MODULE "CONFIDENCE-LEVEL" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-DEFAULT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DEFAULT" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-PRESUME-TRUE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "PRESUME-TRUE" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-FORWARD?
    (INTERN-RIGID-SYMBOL-WRT-MODULE "FORWARD?" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-FORWARD-ONLY?
    (INTERN-RIGID-SYMBOL-WRT-MODULE "FORWARD-ONLY?" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-BACKWARD?
    (INTERN-RIGID-SYMBOL-WRT-MODULE "BACKWARD?" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-BACKWARD-ONLY?
    (INTERN-RIGID-SYMBOL-WRT-MODULE "BACKWARD-ONLY?" NULL 2))
   (CL:SETQ KWD-LOGIC-IN-WEIGHT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "WEIGHT" NULL 2))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-ABOUT
    (INTERN-RIGID-SYMBOL-WRT-MODULE "ABOUT" NULL 0))
   (CL:SETQ SYM-LOGIC-IN-STELLA-IN-MODULE
    (INTERN-RIGID-SYMBOL-WRT-MODULE "IN-MODULE"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-STELLA-LIST-MODULES
    (INTERN-RIGID-SYMBOL-WRT-MODULE "LIST-MODULES"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-STELLA-METHOD-COMMAND?
    (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-COMMAND?"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-STELLA-DOCUMENTATION
    (INTERN-RIGID-SYMBOL-WRT-MODULE "DOCUMENTATION"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-HELP
    (INTERN-RIGID-SYMBOL-WRT-MODULE "HELP" NULL 0))
   (CL:SETQ SYM-LOGIC-IN-LOGIC-STARTUP-LOGIC-IN
    (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-LOGIC-IN" NULL 0))
   (CL:SETQ SYM-LOGIC-IN-STELLA-METHOD-STARTUP-CLASSNAME
    (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
     (GET-STELLA-MODULE "/STELLA" CL:T) 0))))

(CL:DEFUN HELP-STARTUP-LOGIC-IN3 ()
  (CL:PROGN
   (CL:SETQ *AVAILABLE-POWERLOOM-FEATURES*
    (LIST KWD-LOGIC-IN-TRACE-SUBGOALS KWD-LOGIC-IN-TRACE-SOLUTIONS
     KWD-LOGIC-IN-TRACE-CLASSIFIER KWD-LOGIC-IN-ITERATIVE-DEEPENING
     KWD-LOGIC-IN-JUSTIFICATIONS KWD-LOGIC-IN-JUST-IN-TIME-INFERENCE
     KWD-LOGIC-IN-EMIT-THINKING-DOTS))
   (CL:SETQ *CURRENT-POWERLOOM-FEATURES* (LIST))
   (CL:SETQ *DEFAULT-POWERLOOM-FEATURES*
    (LIST KWD-LOGIC-IN-JUST-IN-TIME-INFERENCE
     KWD-LOGIC-IN-EMIT-THINKING-DOTS))
   (RESET-FEATURES)
   (CL:SETQ *POWERLOOM-KB-FILE-EXTENSIONS*
    (GET-QUOTED-TREE "((\".plm\" \".ploom\") \"/LOGIC\")" "/LOGIC"))
   (CL:SETQ *DEMO-FILES*
    (LIST*
     (LIST* (WRAP-STRING "basics")
      (WRAP-STRING "Basic PowerLoom commands")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "classes")
      (WRAP-STRING "Primitive and defined classes")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "collections")
      (WRAP-STRING "Reasoning with collections")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "append")
      (WRAP-STRING "Prolog-style `append'") (WRAP-STRING "test-suite")
      NIL)
     (LIST* (WRAP-STRING "inequalities")
      (WRAP-STRING "Reasoning with inequalities")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "recursion")
      (WRAP-STRING "Reasoning with recursive rules")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "negation")
      (WRAP-STRING "Reasoning with negation")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "constraints")
      (WRAP-STRING "Constraint propagation") (WRAP-STRING "test-suite")
      NIL)
     (LIST* (WRAP-STRING "equations")
      (WRAP-STRING "Simple equational reasoning")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "subsumption")
      (WRAP-STRING "Simple subsumption reasoning")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "family")
      (WRAP-STRING "Subsumption reasoning within a family ontology")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "relation-hierarchy")
      (WRAP-STRING
       "Finding sub, super and equivalent concepts and relations")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "defaults")
      (WRAP-STRING "Default reasoning with Tweety and friends")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "defaults2")
      (WRAP-STRING "More default reasoning") (WRAP-STRING "test-suite")
      NIL)
     (LIST* (WRAP-STRING "definition-syntax")
      (WRAP-STRING
       "The whole scoop on relation definition, funny arrows, etc.")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "meta-relations")
      (WRAP-STRING "Using meta-properties and relations")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "partial-match")
      (WRAP-STRING "Reasoning with partial information")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "probability-learning")
      (WRAP-STRING "Learning to answer probabilistic queries")
      (WRAP-STRING "test-suite") NIL)
     (LIST* (WRAP-STRING "regression-demo")
      (WRAP-STRING "Learning to predict functions") NIL)
     (LIST* (WRAP-STRING "rule-induction-demo")
      (WRAP-STRING "Learning inference rules") NIL)
     (LIST* (WRAP-STRING "test-suite")
      (WRAP-STRING "PowerLoom test suite") (WRAP-STRING "test-suite")
      NIL)
     NIL))
   (CL:SETQ *TERMSOURCEBEINGPARSED* STELLA::NULL-STRING)
   (CL:SETQ *UNFINALIZED-OBJECTS* (LIST))
   (CL:SETQ *LOGIC-RELEVANT-STELLA-COMMANDS*
    (LIST* SYM-LOGIC-IN-STELLA-CC SYM-LOGIC-IN-STELLA-CLEAR-MODULE
     SYM-LOGIC-IN-STELLA-DEFMODULE SYM-LOGIC-IN-STELLA-IN-MODULE
     SYM-LOGIC-IN-STELLA-LIST-MODULES NIL))))

(CL:DEFUN HELP-STARTUP-LOGIC-IN4 ()
  (CL:PROGN
   (DEFINE-FUNCTION-OBJECT "PRINT-FEATURES"
    "(DEFUN PRINT-FEATURES () :COMMAND? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Print the currently enabled and available PowerLoom environment features.\")"
    (CL:FUNCTION PRINT-FEATURES) NULL)
   (DEFINE-FUNCTION-OBJECT "LIST-FEATURES"
    "(DEFUN (LIST-FEATURES LIST) () :COMMAND? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Return a list containing two lists, a list of currently enabled PowerLoom
features, and a list of all available PowerLoom features.\")"
    (CL:FUNCTION LIST-FEATURES) NULL)
   (DEFINE-FUNCTION-OBJECT "SET-POWERLOOM-FEATURE"
    "(DEFUN SET-POWERLOOM-FEATURE ((FEATURE KEYWORD)) :DOCUMENTATION \"Enable the PowerLoom environment feature `feature'.\")"
    (CL:FUNCTION SET-POWERLOOM-FEATURE) NULL)
   (DEFINE-FUNCTION-OBJECT "SET-FEATURE"
    "(DEFUN (SET-FEATURE (LIST OF KEYWORD)) (|&REST| (FEATURES NAME)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Enable the PowerLoom environment feature(s) named by `features'.
Return the list of enabled features.  Calling `set-feature' without any
arguments can be used to display the currently enabled features.
The following features are supported:

`just-in-time-inference': Enables interleaving of forward chaining inference
within backward chaining queries.

`iterative-deepening': Tells the query processor to use iterative deepening
instead of a depth-first search to find answers.  This is less efficient
but necessary for some kinds of highly recursive queries.

`trace-subgoals': Enables the generation of subgoaling trace information during
backchaining inference.

`trace-solutions': Prints newly found solutions during retrieval right when they
are generated as opposed to when the query terminates.

`trace-classifier': Tells the classifier to describe the inferences it draws.

`justifications': Enables the generation of justifications during inference,
which is a prerequiste for the generation of explanations with `(why)'.

`emit-thinking-dots': Tells PowerLoom to annotate its inference progress by
outputting characters indicating the completion of individual reasoning steps.

By default, the features `emit-thinking-dots' and `just-in-time-inference'
are enabled, and the others are disabled.
\")" (CL:FUNCTION %SET-FEATURE)
    (CL:FUNCTION SET-FEATURE-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "UNSET-POWERLOOM-FEATURE"
    "(DEFUN UNSET-POWERLOOM-FEATURE ((FEATURE KEYWORD)) :DOCUMENTATION \"Disable the PowerLoom environment feature `feature'.\")"
    (CL:FUNCTION UNSET-POWERLOOM-FEATURE) NULL)
   (DEFINE-FUNCTION-OBJECT "UNSET-FEATURE"
    "(DEFUN (UNSET-FEATURE (LIST OF KEYWORD)) (|&REST| (FEATURES NAME)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Disable the PowerLoom environment feature(s) named by `features'.
Return the list of enabled features.  Calling `unset-feature' without any
arguments can be used to display the currently enabled features.
See `set-feature' for a description of supported features.\")"
    (CL:FUNCTION %UNSET-FEATURE)
    (CL:FUNCTION UNSET-FEATURE-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "RESET-FEATURES"
    "(DEFUN (RESET-FEATURES (LIST OF KEYWORD)) () :COMMAND? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Reset the PowerLoom environment features to their default settings.\")"
    (CL:FUNCTION RESET-FEATURES) NULL)
   (DEFINE-FUNCTION-OBJECT "ENABLED-POWERLOOM-FEATURE?"
    "(DEFUN (ENABLED-POWERLOOM-FEATURE? BOOLEAN) ((FEATURE KEYWORD)) :DOCUMENTATION \"Return true if the STELLA `feature' is currently enabled.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (MEMB? *CURRENT-POWERLOOM-FEATURES* FEATURE)))"
    (CL:FUNCTION ENABLED-POWERLOOM-FEATURE?) NULL)
   (DEFINE-FUNCTION-OBJECT "DISABLED-POWERLOOM-FEATURE?"
    "(DEFUN (DISABLED-POWERLOOM-FEATURE? BOOLEAN) ((FEATURE KEYWORD)) :DOCUMENTATION \"Return true if the STELLA `feature' is currently disabled.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (RETURN (NOT (MEMB? *CURRENT-POWERLOOM-FEATURES* FEATURE))))"
    (CL:FUNCTION DISABLED-POWERLOOM-FEATURE?) NULL)
   (DEFINE-FUNCTION-OBJECT "PARSE-LOGIC-COMMAND-OPTIONS"
    "(DEFUN (PARSE-LOGIC-COMMAND-OPTIONS PROPERTY-LIST) ((OPTIONS OBJECT) (|LEGALOPTIONS&TYPES| CONS) (COERCIONERROR? BOOLEAN) (ALLOWOTHERKEYS? BOOLEAN)) :DOCUMENTATION \"This is simply a wrapper to `parse-options' (which see).
We keep this alias in case we ever want to add any logic-specific extensions.\" :PUBLIC? TRUE)"
    (CL:FUNCTION PARSE-LOGIC-COMMAND-OPTIONS) NULL)
   (DEFINE-FUNCTION-OBJECT "PRINT-LOGIC-PROMPT"
    "(DEFUN PRINT-LOGIC-PROMPT ())" (CL:FUNCTION PRINT-LOGIC-PROMPT)
    NULL)
   (DEFINE-FUNCTION-OBJECT "PRINT-LOGIC-COMMAND-RESULT"
    "(DEFUN PRINT-LOGIC-COMMAND-RESULT ((RESULT OBJECT)))"
    (CL:FUNCTION PRINT-LOGIC-COMMAND-RESULT) NULL)
   (DEFINE-FUNCTION-OBJECT "LOGIC-COMMAND-LOOP-EXIT?"
    "(DEFUN (LOGIC-COMMAND-LOOP-EXIT? BOOLEAN BOOLEAN) ((COMMAND OBJECT)))"
    (CL:FUNCTION LOGIC-COMMAND-LOOP-EXIT?) NULL)
   (DEFINE-FUNCTION-OBJECT "LOGIC-COMMAND-LOOP"
    "(DEFUN LOGIC-COMMAND-LOOP ((MODULE MODULE)))"
    (CL:FUNCTION LOGIC-COMMAND-LOOP) NULL)
   (DEFINE-FUNCTION-OBJECT "EVALUATE-LOGIC-COMMAND"
    "(DEFUN (EVALUATE-LOGIC-COMMAND OBJECT) ((COMMAND OBJECT) (FINALIZE? BOOLEAN)))"
    (CL:FUNCTION EVALUATE-LOGIC-COMMAND) NULL)
   (DEFINE-FUNCTION-OBJECT "LOAD"
    "(DEFUN LOAD ((FILE STRING) |&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Read logic commands from `file' and evaluate them.
By default, this will check for each asserted proposition whether an
equivalent proposition already exists and, if so, not assert the
duplicate.  These duplicate checks are somewhat expensive though and
can be skipped by setting the option :check-duplicates? to false.
This can save time when loading large KBs where it is known that no
duplicate assertions exist in a file.

Also, by setting the :module option, the module in which the file
contents will be loaded will be set.  This will only affect files
that do NOT have an `in-module' declaration as part of the file.
If this is not set, and no `in-module' declaration is in the file,
the file will be loaded into the current module.

The option :assertion-module can be used to have assertions and
definitional axioms be asserted in a different module than the
top-level module where definitions are evaluated.  This is useful
in some cases where vocabulary definitions and their associated
axioms and assertions need to be separate for inference or efficiency
reasons.  The assertion module can be given as a name in case it is
defined in the loaded file.  Obviously, it needs to be a child of the
top-level module where vocabulary definitions are created.

Loading is done in two passes: in the first pass all definitional
commands such as `defmodule', `defconcept', etc. are evaluated but not
yet finalized, that is, their definitional axioms are parsed but not
yet asserted.  In the second pass all definitional commands are finalized
and then all commands in the file are executed in order (which will be
no-ops for the definitions already processed).  This scheme tries to
maintain some order independence for the commands in the file, since
relation definitions need to be performed before they can be used in
assertions.  At any point `process-definitions' can be called to finalize
all unfinalized definitions queued up so far.  Future versions might also
support a :one-pass? option for added efficiency.\" :COMMAND? TRUE :PUBLIC? TRUE)"
    (CL:FUNCTION %LOAD) (CL:FUNCTION LOAD-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "DEFINITION-NAME?"
    "(DEFUN (DEFINITION-NAME? BOOLEAN) ((NAME SYMBOL)) :PUBLIC? FALSE)"
    (CL:FUNCTION DEFINITION-NAME?) NULL)
   (DEFINE-FUNCTION-OBJECT "LOAD-COMMAND-EVAL-PHASE"
    "(DEFUN (LOAD-COMMAND-EVAL-PHASE KEYWORD) ((TREE OBJECT)) :DOCUMENTATION \"Analyze a command `tree' in a load file and determine when it should be processed.\" :PUBLIC? TRUE)"
    (CL:FUNCTION LOAD-COMMAND-EVAL-PHASE) NULL)
   (DEFINE-FUNCTION-OBJECT "LOAD-STREAM"
    "(DEFUN LOAD-STREAM ((STREAM INPUT-STREAM) |&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Read logic commands from `stream' and evaluate them.
Does the actual work for `load' (which see for a description of options).\" :PUBLIC? TRUE)"
    (CL:FUNCTION LOAD-STREAM) NULL)
   (DEFINE-FUNCTION-OBJECT "LOAD-STREAM-IN-MODULE"
    "(DEFUN LOAD-STREAM-IN-MODULE ((STREAM INPUT-STREAM) (MODULE MODULE)) :DOCUMENTATION \"Read logic commands from `stream' and evaluate them in `module'.
This is a backwards-compatibility wrapper.  Note that `module' will not override
any `in-module' declarations in `stream'.\" :PUBLIC? TRUE)"
    (CL:FUNCTION LOAD-STREAM-IN-MODULE) NULL)
   (DEFINE-FUNCTION-OBJECT "LOAD-DIRECTORY"
    "(DEFUN LOAD-DIRECTORY ((DIRECTORY STRING)) :DOCUMENTATION \"Load all PowerLoom files (*.plm) in `directory' in alphabetic sort order.\" :PUBLIC? TRUE :COMMAND? TRUE)"
    (CL:FUNCTION %LOAD-DIRECTORY)
    (CL:FUNCTION LOAD-DIRECTORY-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "LOAD-CMD-LINE-FILES"
    "(DEFUN LOAD-CMD-LINE-FILES () :DOCUMENTATION \"Loads all PowerLoom files specified on the command line.
If directories are listed, all PowerLoom files in those directories are loaded.
Since when this is called we might still have unprocessed command line args,
this only looks at files which are to the right of the last argument that
starts with a `-' character.\" :PUBLIC? TRUE :COMMAND? TRUE)"
    (CL:FUNCTION LOAD-CMD-LINE-FILES) NULL)
   (DEFINE-FUNCTION-OBJECT "PRINT-DEMO-PROMPT"
    "(DEFUN PRINT-DEMO-PROMPT ())" (CL:FUNCTION PRINT-DEMO-PROMPT)
    NULL)
   (DEFINE-FUNCTION-OBJECT "DEMO-SKIP-TO-COMMAND"
    "(DEFUN (DEMO-SKIP-TO-COMMAND BOOLEAN) ((STREAM INPUT-STREAM)))"
    (CL:FUNCTION DEMO-SKIP-TO-COMMAND) NULL)
   (DEFINE-FUNCTION-OBJECT "DEMO-PAUSE?"
    "(DEFUN (DEMO-PAUSE? BOOLEAN BOOLEAN) ((PAUSE? BOOLEAN)))"
    (CL:FUNCTION DEMO-PAUSE?) NULL)
   (DEFINE-FUNCTION-OBJECT "DEMO-FILE"
    "(DEFUN DEMO-FILE ((FILE FILE-NAME) (PAUSE? BOOLEAN)))"
    (CL:FUNCTION DEMO-FILE) NULL)
   (DEFINE-FUNCTION-OBJECT "DEMO-ENTRY-FILE"
    "(DEFUN (DEMO-ENTRY-FILE STRING) ((DEMOENTRY (CONS OF STRING-WRAPPER))))"
    (CL:FUNCTION DEMO-ENTRY-FILE) NULL)
   (DEFINE-FUNCTION-OBJECT "DEMO-ENTRY-DESCRIPTION"
    "(DEFUN (DEMO-ENTRY-DESCRIPTION STRING) ((DEMOENTRY (CONS OF STRING-WRAPPER))))"
    (CL:FUNCTION DEMO-ENTRY-DESCRIPTION) NULL)
   (DEFINE-FUNCTION-OBJECT "DEMO-ENTRY-TEST-SUITE?"
    "(DEFUN (DEMO-ENTRY-TEST-SUITE? BOOLEAN) ((DEMOENTRY (CONS OF STRING-WRAPPER))))"
    (CL:FUNCTION DEMO-ENTRY-TEST-SUITE?) NULL)
   (DEFINE-FUNCTION-OBJECT "SELECT-EXAMPLE-DEMO"
    "(DEFUN (SELECT-EXAMPLE-DEMO STRING) ((INDEX INTEGER)))"
    (CL:FUNCTION SELECT-EXAMPLE-DEMO) NULL)
   (DEFINE-FUNCTION-OBJECT "SELECT-EXAMPLE-DEMO-FROM-MENU"
    "(DEFUN (SELECT-EXAMPLE-DEMO-FROM-MENU STRING) ())"
    (CL:FUNCTION SELECT-EXAMPLE-DEMO-FROM-MENU) NULL)
   (DEFINE-FUNCTION-OBJECT "DEMO-EXAMPLE-DEMOS"
    "(DEFUN DEMO-EXAMPLE-DEMOS ())" (CL:FUNCTION DEMO-EXAMPLE-DEMOS)
    NULL)
   (DEFINE-FUNCTION-OBJECT "DEMO"
    "(DEFUN DEMO (|&REST| (FILEANDPAUSE OBJECT)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? TRUE :DOCUMENTATION \"Read logic commands from a file, echo them verbatimly to standard output,
and evaluate them just as if they had been typed in interactively.
When called with no arguments, present a menu of example demos, otherwise,
use the first argument as the name of the file to demo.
Pause for user confirmation after each expression has been read but
before it is evaluated.  Pausing can be turned off by suppling FALSE
as the optional second argument, or by typing `c' at the pause prompt.
Typing `?' at the pause prompt prints a list of available commands.\")"
    (CL:FUNCTION %DEMO) (CL:FUNCTION DEMO-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "TEST-LOGIC-FILE"
    "(DEFUN TEST-LOGIC-FILE ((FILE FILE-NAME)))"
    (CL:FUNCTION TEST-LOGIC-FILE) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-FORMATTED-DATE-AND-TIME"
    "(DEFUN (GET-FORMATTED-DATE-AND-TIME STRING) ())"
    (CL:FUNCTION GET-FORMATTED-DATE-AND-TIME) NULL)
   (DEFINE-FUNCTION-OBJECT "RUN-POWERLOOM-TESTS"
    "(DEFUN RUN-POWERLOOM-TESTS () :COMMAND? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Run the PowerLoom test suite.  Currently this simply runs all demos and
echos commands and their results to standard output.  The output can then
be diffed with previously validated runs to find deviations.\")"
    (CL:FUNCTION RUN-POWERLOOM-TESTS) NULL)
   (DEFINE-FUNCTION-OBJECT "TIME-COMMAND"
    "(DEFUN (TIME-COMMAND OBJECT) ((COMMAND CONS)) :DOCUMENTATION \"Execute `command', measure and report its CPU and elapsed time
needed for its execution, and then return its result.\" :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE)"
    (CL:FUNCTION %TIME-COMMAND) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-HTTP-SERVER-SYSTEM"
    "(DEFUN (GET-HTTP-SERVER-SYSTEM STRING) ())"
    (CL:FUNCTION GET-HTTP-SERVER-SYSTEM) NULL)
   (DEFINE-FUNCTION-OBJECT "START-ONTOSAURUS"
    "(DEFUN START-ONTOSAURUS (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Start the PowerLoom HTTP server at :port (defaults to 9090).  Loads
the required support systems in Lisp and Java if necessary (C++ is not yet supported).\" :COMMAND? TRUE :PUBLIC? TRUE)"
    (CL:FUNCTION %START-ONTOSAURUS)
    (CL:FUNCTION START-ONTOSAURUS-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "STOP-ONTOSAURUS"
    "(DEFUN STOP-ONTOSAURUS () :DOCUMENTATION \"Stop the PowerLoom HTTP server and free up any bound ports.
This is a no-op if no server is running or the server is not supported.\" :COMMAND? TRUE :PUBLIC? TRUE)"
    (CL:FUNCTION STOP-ONTOSAURUS) NULL)
   (DEFINE-FUNCTION-OBJECT "START-POWERLOOM-SERVER"
    "(DEFUN START-POWERLOOM-SERVER (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Start the PowerLoom HTTP server at :port (defaults to 9090).  Loads
the required support systems in Lisp and Java if necessary (C++ is not yet supported).\" :COMMAND? TRUE :PUBLIC? TRUE)"
    (CL:FUNCTION %START-POWERLOOM-SERVER)
    (CL:FUNCTION START-POWERLOOM-SERVER-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "STOP-POWERLOOM-SERVER"
    "(DEFUN STOP-POWERLOOM-SERVER () :DOCUMENTATION \"Stop the PowerLoom HTTP server and free up any bound ports.
This is a no-op if no server is running or the server is not supported.\" :COMMAND? TRUE :PUBLIC? TRUE)"
    (CL:FUNCTION STOP-POWERLOOM-SERVER) NULL)
   (DEFINE-FUNCTION-OBJECT "START-POWERLOOM-GUI"
    "(DEFUN START-POWERLOOM-GUI (|&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"Start the PowerLoom server at :port (defaults to 9090) and launches
the GUI which will communicate with the server at that port.  If :host is specified,
the GUI will try to communicate with a server at `host:port' instead of the local
embedded server (note, you can always point the GUI manually to a different server
from its `Connect to Server' menu item).  Loads the required support systems if necessary.
Embedded calls to the GUI are currently only supported in Java; however, when the GUI is
run in standalone mode, it can communicate with any PowerLoom installation that supports
an HTTP server (currently Lisp and Java).\" :COMMAND? TRUE :PUBLIC? TRUE)"
    (CL:FUNCTION %START-POWERLOOM-GUI)
    (CL:FUNCTION START-POWERLOOM-GUI-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "STOP-POWERLOOM-GUI"
    "(DEFUN STOP-POWERLOOM-GUI () :DOCUMENTATION \"Closes the PowerLoom GUI application if it is currently visible.
This is a no-op if the GUI is not running or if it is not supported.\" :COMMAND? TRUE :PUBLIC? TRUE)"
    (CL:FUNCTION STOP-POWERLOOM-GUI) NULL)
   (DEFINE-FUNCTION-OBJECT "POWERLOOM-GUI-EXIT-HOOK"
    "(DEFUN POWERLOOM-GUI-EXIT-HOOK ((IGNORE OBJECT)) :DOCUMENTATION \"Exit hook to stop the PowerLoom GUI if it is running.\" :PUBLIC? TRUE)"
    (CL:FUNCTION POWERLOOM-GUI-EXIT-HOOK) NULL)
   (DEFINE-FUNCTION-OBJECT "PRINT-FORMULA-CONTAINING-ERROR"
    "(DEFUN PRINT-FORMULA-CONTAINING-ERROR ((SELF OBJECT) (STREAM OUTPUT-STREAM)))"
    (CL:FUNCTION PRINT-FORMULA-CONTAINING-ERROR) NULL)
   (DEFINE-FUNCTION-OBJECT "HELP-SIGNAL-PROPOSITION-ERROR"
    "(DEFUN HELP-SIGNAL-PROPOSITION-ERROR ((STREAM OUTPUT-STREAM) (WARNINGORERROR KEYWORD)))"
    (CL:FUNCTION HELP-SIGNAL-PROPOSITION-ERROR) NULL)
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION PERMUTATION-TABLE :TYPE (KEY-VALUE-LIST OF VECTOR SLOT) :OPTION-KEYWORD :PERMUTATION-TABLE :ALLOCATION :DYNAMIC)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT TABLE RELATION-PARAMETER-TYPE-SPECIFIERS :RENAMES TUPLE-DOMAINS)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT MODULE MODULE-LOGIC-DIALECT :TYPE KEYWORD :DEFAULT NULL :OPTION-KEYWORD :LOGIC-DIALECT :PUBLIC? TRUE :ALLOCATION :DYNAMIC)")
   (DEFINE-FUNCTION-OBJECT "LOGIC-DIALECT"
    "(DEFUN (LOGIC-DIALECT KEYWORD) ((SELF OBJECT)))"
    (CL:FUNCTION LOGIC-DIALECT) NULL)
   (DEFINE-FUNCTION-OBJECT "LOOKUP-LOGIC-OBJECT-SURROGATE"
    "(DEFUN (LOOKUP-LOGIC-OBJECT-SURROGATE SURROGATE) ((NAME SYMBOL) (DEFINITIONMODULE MODULE)))"
    (CL:FUNCTION LOOKUP-LOGIC-OBJECT-SURROGATE) NULL)
   (DEFINE-FUNCTION-OBJECT "INTERN-LOGIC-OBJECT-SURROGATE"
    "(DEFUN (INTERN-LOGIC-OBJECT-SURROGATE SURROGATE) ((NAME SYMBOL)))"
    (CL:FUNCTION INTERN-LOGIC-OBJECT-SURROGATE) NULL)
   (DEFINE-FUNCTION-OBJECT "NAME-OBJECT-METACLASS"
    "(DEFUN (NAME-OBJECT-METACLASS STRING) ((SELF OBJECT)))"
    (CL:FUNCTION NAME-OBJECT-METACLASS) NULL)
   (DEFINE-FUNCTION-OBJECT "LOGIC-OBJECT-DEFINITION-TYPE"
    "(DEFUN (LOGIC-OBJECT-DEFINITION-TYPE KEYWORD) ((NAME SYMBOL) (OLDOBJECT OBJECT) (NEWOBJECT OBJECT)))"
    (CL:FUNCTION LOGIC-OBJECT-DEFINITION-TYPE) NULL)
   (DEFINE-FUNCTION-OBJECT "BIND-LOGIC-OBJECT-TO-SURROGATE"
    "(DEFUN BIND-LOGIC-OBJECT-TO-SURROGATE ((NAME SYMBOL) (OBJECT OBJECT)))"
    (CL:FUNCTION BIND-LOGIC-OBJECT-TO-SURROGATE) NULL)
   (DEFINE-FUNCTION-OBJECT "REDEFINE-LOGIC-OBJECT"
    "(DEFUN REDEFINE-LOGIC-OBJECT ((NAME SYMBOL) (OLDOBJECT OBJECT) (NEWOBJECT OBJECT)))"
    (CL:FUNCTION REDEFINE-LOGIC-OBJECT) NULL)
   (DEFINE-FUNCTION-OBJECT "EXPLICITLY-QUALIFIED-LOGIC-OBJECT-NAME?"
    "(DEFUN (EXPLICITLY-QUALIFIED-LOGIC-OBJECT-NAME? BOOLEAN) ((OBJECTNAME GENERALIZED-SYMBOL) (DEFINITIONMODULE MODULE)))"
    (CL:FUNCTION EXPLICITLY-QUALIFIED-LOGIC-OBJECT-NAME?) NULL)
   (DEFINE-FUNCTION-OBJECT "COERCE-TO-BOUND-OR-LOCAL-SURROGATE"
    "(DEFUN (COERCE-TO-BOUND-OR-LOCAL-SURROGATE SURROGATE) ((SELF GENERALIZED-SYMBOL)))"
    (CL:FUNCTION COERCE-TO-BOUND-OR-LOCAL-SURROGATE) NULL)
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT LOGIC-OBJECT OBJECT-AXIOMS :TYPE CONS :DEFAULT NULL :READER AXIOMS :OPTION-KEYWORD :AXIOMS :OPTION-HANDLER DEFINITION-AXIOMS-HANDLER :ALLOCATION :DYNAMIC)")))

(CL:DEFUN HELP-STARTUP-LOGIC-IN5 ()
  (CL:PROGN
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT PROPOSITION PROPOSITION-AXIOMS :TYPE CONS :DEFAULT NULL :WRITER AXIOMS-SETTER :OPTION-KEYWORD :AXIOMS :OPTION-HANDLER DEFINITION-AXIOMS-HANDLER :ALLOCATION :DYNAMIC)")
   (DEFINE-FUNCTION-OBJECT "AXIOMS"
    "(DEFUN (AXIOMS CONS) ((SELF OBJECT)))" (CL:FUNCTION AXIOMS) NULL)
   (DEFINE-FUNCTION-OBJECT "AXIOMS-SETTER"
    "(DEFUN (AXIOMS-SETTER OBJECT) ((SELF OBJECT) (AXIOMS CONS)))"
    (CL:FUNCTION AXIOMS-SETTER) NULL)
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS1 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<= :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS2 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :=> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS3 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<<= :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS4 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :=>> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS5 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<=> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS6 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<=>> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS7 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<<=> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS8 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<<=>> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS9 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<~ :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS10 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :~> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS11 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<<~ :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS12 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :~>> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS13 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<~> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS14 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<~>> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS15 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<<~> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-EXTERNAL-SLOT-FROM-STRINGIFIED-SOURCE
    "(DEFSLOT NAMED-DESCRIPTION AXIOMS-ALIAS16 :RENAMES OBJECT-AXIOMS :OPTION-KEYWORD :<<~>> :OPTION-HANDLER DEFINITION-HALF-RULE-HANDLER)")
   (DEFINE-FUNCTION-OBJECT "DEFINITION-AXIOMS-HANDLER"
    "(DEFUN DEFINITION-AXIOMS-HANDLER ((SELF OBJECT) (SLOT STORAGE-SLOT) (THEAXIOMS OBJECT)))"
    (CL:FUNCTION DEFINITION-AXIOMS-HANDLER) NULL)
   (DEFINE-FUNCTION-OBJECT "DEFINITION-HALF-RULE-HANDLER"
    "(DEFUN DEFINITION-HALF-RULE-HANDLER ((SELF NAMED-DESCRIPTION) (SLOT STORAGE-SLOT) (BODY OBJECT)))"
    (CL:FUNCTION DEFINITION-HALF-RULE-HANDLER) NULL)
   (DEFINE-FUNCTION-OBJECT "COMBINE-AXIOM-LISTS"
    "(DEFUN (COMBINE-AXIOM-LISTS CONS) ((OLDAXIOMS CONS) (NEWAXIOMS OBJECT)))"
    (CL:FUNCTION COMBINE-AXIOM-LISTS) NULL)
   (DEFINE-FUNCTION-OBJECT "YIELD-RELATION-PARAMETERS-TREE"
    "(DEFUN (YIELD-RELATION-PARAMETERS-TREE CONS) ((SELF NAMED-DESCRIPTION) (DROPFUNCTIONPARAMETER? BOOLEAN) (TYPED? BOOLEAN)))"
    (CL:FUNCTION YIELD-RELATION-PARAMETERS-TREE) NULL)
   (DEFINE-FUNCTION-OBJECT "COMPLETE-RULE-DEFINITION"
    "(DEFUN (COMPLETE-RULE-DEFINITION OBJECT) ((SELF NAMED-DESCRIPTION) (BODY OBJECT) (ARROW SYMBOL)))"
    (CL:FUNCTION COMPLETE-RULE-DEFINITION) NULL)
   (DEFINE-FUNCTION-OBJECT "DEFINITION-KEYWORD-AXIOMS-HANDLER"
    "(DEFUN DEFINITION-KEYWORD-AXIOMS-HANDLER ((SELF OBJECT) (SELFNAME SYMBOL) (KEY KEYWORD) (VALUE OBJECT)))"
    (CL:FUNCTION DEFINITION-KEYWORD-AXIOMS-HANDLER) NULL)
   (DEFINE-FUNCTION-OBJECT "HELP-DEFINE-KEYWORD-AXIOMS"
    "(DEFUN (HELP-DEFINE-KEYWORD-AXIOMS CONS) ((SELFNAME SYMBOL) (KEY KEYWORD) (VALUE OBJECT)))"
    (CL:FUNCTION HELP-DEFINE-KEYWORD-AXIOMS) NULL)
   (DEFINE-FUNCTION-OBJECT "ASSERT-KEYWORD-AXIOM"
    "(DEFUN ASSERT-KEYWORD-AXIOM ((SELF OBJECT) (SELFNAME SYMBOL) (KEY KEYWORD) (VALUE OBJECT)))"
    (CL:FUNCTION ASSERT-KEYWORD-AXIOM) NULL)
   (DEFINE-FUNCTION-OBJECT "REGISTER-UNFINALIZED-OBJECT"
    "(DEFUN REGISTER-UNFINALIZED-OBJECT ((OBJECT OBJECT)))"
    (CL:FUNCTION REGISTER-UNFINALIZED-OBJECT) NULL)
   (DEFINE-FUNCTION-OBJECT "CLEANUP-UNFINALIZED-OBJECTS"
    "(DEFUN CLEANUP-UNFINALIZED-OBJECTS ())"
    (CL:FUNCTION CLEANUP-UNFINALIZED-OBJECTS) NULL)
   (DEFINE-FUNCTION-OBJECT "LINK-ORIGINATED-PROPOSITION"
    "(DEFUN LINK-ORIGINATED-PROPOSITION ((OBJECT OBJECT) (PROPOSITION PROPOSITION)))"
    (CL:FUNCTION LINK-ORIGINATED-PROPOSITION) NULL)
   (DEFINE-FUNCTION-OBJECT "HELP-FINALIZE-OBJECT-AXIOMS"
    "(DEFUN (HELP-FINALIZE-OBJECT-AXIOMS (CONS OF PROPOSITION)) ((THEAXIOMS CONS)))"
    (CL:FUNCTION HELP-FINALIZE-OBJECT-AXIOMS) NULL)
   (DEFINE-FUNCTION-OBJECT "FINALIZE-OBJECT-AXIOMS"
    "(DEFUN FINALIZE-OBJECT-AXIOMS ((SELF OBJECT)))"
    (CL:FUNCTION FINALIZE-OBJECT-AXIOMS) NULL)
   (DEFINE-FUNCTION-OBJECT "CHECK-DESCRIPTION-ARGUMENT-TYPES"
    "(DEFUN CHECK-DESCRIPTION-ARGUMENT-TYPES ((SELF NAMED-DESCRIPTION)))"
    (CL:FUNCTION CHECK-DESCRIPTION-ARGUMENT-TYPES) NULL)
   (DEFINE-FUNCTION-OBJECT "FINALIZE-OBJECT"
    "(DEFUN FINALIZE-OBJECT ((SELF OBJECT)))"
    (CL:FUNCTION FINALIZE-OBJECT) NULL)
   (DEFINE-FUNCTION-OBJECT "FINALIZED-OBJECT?"
    "(DEFUN (FINALIZED-OBJECT? BOOLEAN) ((SELF OBJECT)))"
    (CL:FUNCTION FINALIZED-OBJECT?) NULL)
   (DEFINE-FUNCTION-OBJECT "OBJECTS-ARE-FINALIZED?"
    "(DEFUN (OBJECTS-ARE-FINALIZED? BOOLEAN) () :GLOBALLY-INLINE? TRUE (RETURN (EMPTY? (THE-CONS-LIST *UNFINALIZED-OBJECTS*))))"
    (CL:FUNCTION OBJECTS-ARE-FINALIZED?) NULL)
   (DEFINE-FUNCTION-OBJECT "FINALIZE-OBJECTS"
    "(DEFUN FINALIZE-OBJECTS () :DOCUMENTATION \"Finalize all currently unfinalized objects.
The user-level entry point for this is `(process-definitions)'.\" :PUBLIC? TRUE)"
    (CL:FUNCTION FINALIZE-OBJECTS) NULL)
   (DEFINE-FUNCTION-OBJECT "HELP-DEFINE-RELATION-FROM-PARSE-TREE"
    "(DEFUN (HELP-DEFINE-RELATION-FROM-PARSE-TREE NAMED-DESCRIPTION) ((TREE CONS) (STRINGIFIEDSOURCE STRING)))"
    (CL:FUNCTION HELP-DEFINE-RELATION-FROM-PARSE-TREE) NULL)
   (DEFINE-FUNCTION-OBJECT "PARSE-RELATION-PARAMETERS-TREE"
    "(DEFUN (PARSE-RELATION-PARAMETERS-TREE (LIST OF SYMBOL) (LIST OF TYPE) BOOLEAN) ((PARAMETERS CONS)))"
    (CL:FUNCTION PARSE-RELATION-PARAMETERS-TREE) NULL)
   (DEFINE-FUNCTION-OBJECT "GET-IDENTICAL-RELATION"
    "(DEFUN (GET-IDENTICAL-RELATION NAMED-DESCRIPTION) ((NAME SYMBOL) (STRINGIFIEDSOURCE STRING)))"
    (CL:FUNCTION GET-IDENTICAL-RELATION) NULL)
   (DEFINE-METHOD-OBJECT
    "(DEFMETHOD PROCESS-DEFINITION-OPTIONS ((SELF NAMED-DESCRIPTION) (OPTIONS OBJECT)))"
    (WRAP-METHOD-CODE (CL:FUNCTION PROCESS-DEFINITION-OPTIONS)) NULL)
   (DEFINE-FUNCTION-OBJECT "DEFFUNCTION"
    "(DEFUN (DEFFUNCTION NAMED-DESCRIPTION) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a logic function.  The accepted syntax is:
	 
 (deffunction <funconst> (<vardecl>+) [:-> <vardecl>]
    [:documentation <string>]
    [:<= <sentence>] | [:=> <sentence>] |
    [:<<= <sentence>] | [:=>> <sentence>] | 
    [:<=> <sentence>] | [:<=>> <sentence>] |
    [:<<=> <sentence>] | [:<<=>> <sentence>] |
    [:axioms {<sentence> | (<sentence>+)}]
    [<keyword-option>*])
	
Function parameters can be typed or untyped.  If the `:->' option is
supplied, it specifies the output variable of the function.  Otherwise,
the last variable in the parameter list is used as the output variable.
See `defrelation' for a description of `<keyword-option>'s.
\")" (CL:FUNCTION %DEFFUNCTION)
    (CL:FUNCTION DEFFUNCTION-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "CALL-DEFFUNCTION"
    "(DEFUN (CALL-DEFFUNCTION NAMED-DESCRIPTION) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `deffunction' command (which see).
Expects the same arguments as `deffunction' but supplied as a list.\" :PUBLIC? TRUE)"
    (CL:FUNCTION CALL-DEFFUNCTION) NULL)
   (DEFINE-FUNCTION-OBJECT "NORMALIZE-DEFFUNCTION-ARGUMENTS"
    "(DEFUN (NORMALIZE-DEFFUNCTION-ARGUMENTS CONS) ((ARGUMENTS CONS)))"
    (CL:FUNCTION NORMALIZE-DEFFUNCTION-ARGUMENTS) NULL)
   (DEFINE-FUNCTION-OBJECT "DEFRELATION"
    "(DEFUN (DEFRELATION NAMED-DESCRIPTION) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a logic relation.  The accepted syntax is:
	 
 (defrelation <relconst> (<vardecl>+)
    [:documentation <string>]
    [:<= <sentence>] | [:=> <sentence>] |
    [:<<= <sentence>] | [:=>> <sentence>] | 
    [:<=> <sentence>] | [:<=>> <sentence>] |
    [:<<=> <sentence>] | [:<<=>> <sentence>] |
    [:axioms {<sentence> | (<sentence>+)}]
    [<keyword-option>*])
	
Relation parameters can be typed or untyped.
`<keyword-option>' represents a keyword followed by a value that states an
assertion about `<relconst>'.  For example, including the option `:foo bar'
states that the proposition `(foo <relconst> bar)' is true.  `:foo (bar fum)'
states that both `(foo <relconst> bar)' and `(foo <relconst> fum)' are true.
`:foo true' states that `(foo <relconst>)' is true, `:foo false' states that
`(not (foo <relconst>))' is true.
\")" (CL:FUNCTION %DEFRELATION)
    (CL:FUNCTION DEFRELATION-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "CALL-DEFRELATION"
    "(DEFUN (CALL-DEFRELATION NAMED-DESCRIPTION) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `defrelation' command (which see).
Expects the same arguments as `defrelation' but supplied as a list.\" :PUBLIC? TRUE)"
    (CL:FUNCTION CALL-DEFRELATION) NULL)
   (DEFINE-FUNCTION-OBJECT "NORMALIZE-DEFRELATION-ARGUMENTS"
    "(DEFUN (NORMALIZE-DEFRELATION-ARGUMENTS CONS) ((ARGUMENTS CONS)))"
    (CL:FUNCTION NORMALIZE-DEFRELATION-ARGUMENTS) NULL)
   (DEFINE-FUNCTION-OBJECT "DEFCONCEPT"
    "(DEFUN (DEFCONCEPT NAMED-DESCRIPTION) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a concept.  The accepted syntax is:
	 
 (defconcept <conceptconst> [(<var> <parent>*)]
    [:documentation <string>]
    [:<= <sentence>] | [:=> <sentence>] |
    [:<<= <sentence>] | [:=>> <sentence>] | 
    [:<=> <sentence>] | [:<=>> <sentence>] | [:<<=> <sentence>] |
    [:<<=>> <sentence>] |
    [:axioms {<sentence> | (<sentence>+)}] |
    <keyword-option>*)
	
Declaration of a concept variable `<var>' is optional, unless any
implication (arrow) options are supplied that need to reference it.  A
possibly empty list of concept names following `<var>' is taken as the list
of parents of `<conceptconst>'.  Alternatively, parents can be specified
via the `:=>' option.  If no parents are specified, the parent of
`<conceptconst>' is taken to be THING.  `<keyword-option>' represents a
keyword followed by a value that states an assertion about `<conceptconst>'.
See `defrelation' for a description of `<keyword-option>'s.
\")" (CL:FUNCTION %DEFCONCEPT)
    (CL:FUNCTION DEFCONCEPT-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "CALL-DEFCONCEPT"
    "(DEFUN (CALL-DEFCONCEPT NAMED-DESCRIPTION) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `defconcept' command (which see).
Expects the same arguments as `defconcept' but supplied as a list.\" :PUBLIC? TRUE)"
    (CL:FUNCTION CALL-DEFCONCEPT) NULL)
   (DEFINE-FUNCTION-OBJECT "NORMALIZE-DEFCONCEPT-ARGUMENTS"
    "(DEFUN (NORMALIZE-DEFCONCEPT-ARGUMENTS CONS) ((ARGUMENTS CONS)))"
    (CL:FUNCTION NORMALIZE-DEFCONCEPT-ARGUMENTS) NULL)
   (DEFINE-FUNCTION-OBJECT "DEFINE-RELATION-FROM-PARSE-TREE"
    "(DEFUN (DEFINE-RELATION-FROM-PARSE-TREE NAMED-DESCRIPTION) ((TREE CONS)))"
    (CL:FUNCTION DEFINE-RELATION-FROM-PARSE-TREE) NULL)
   (DEFINE-FUNCTION-OBJECT "DEFOBJECT"
    "(DEFUN (DEFOBJECT LOGIC-OBJECT) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a logic instance.  The accepted syntax is:
	 
 (defobject <constant>
    [:documentation <string>]
    [<keyword-option>*])
	
`<keyword-option>' represents a keyword followed by a value
that states an assertion about <constant>.  See `defrelation' for a
description of `<keyword-option>'s.

`defobject' provides a sugar-coated way to assert a collection of facts
about a logic constant, but otherwise adds nothing in terms of functionality.
\")" (CL:FUNCTION %DEFOBJECT)
    (CL:FUNCTION DEFOBJECT-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "DEFINSTANCE"
    "(DEFUN (DEFINSTANCE LOGIC-OBJECT) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a logic instance (`definstance' is an alias
for `defobject' which see).\")" (CL:FUNCTION %DEFINSTANCE)
    (CL:FUNCTION DEFINSTANCE-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "CALL-DEFOBJECT"
    "(DEFUN (CALL-DEFOBJECT LOGIC-OBJECT) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `defobject' command (which see).
Expects the same arguments as `defobject' but supplied as a list.\" :PUBLIC? TRUE)"
    (CL:FUNCTION CALL-DEFOBJECT) NULL)
   (DEFINE-FUNCTION-OBJECT "NORMALIZE-DEFOBJECT-ARGUMENTS"
    "(DEFUN (NORMALIZE-DEFOBJECT-ARGUMENTS CONS) ((ARGUMENTS CONS)))"
    (CL:FUNCTION NORMALIZE-DEFOBJECT-ARGUMENTS) NULL)
   (DEFINE-METHOD-OBJECT
    "(DEFMETHOD PROCESS-DEFINITION-OPTIONS ((SELF LOGIC-OBJECT) (OPTIONS OBJECT)))"
    (WRAP-METHOD-CODE (CL:FUNCTION PROCESS-DEFINITION-OPTIONS)) NULL)
   (DEFINE-FUNCTION-OBJECT "DEFPROPOSITION"
    "(DEFUN (DEFPROPOSITION PROPOSITION) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a named proposition.  The accepted syntax is:
	 
 (defproposition <name> <sentence>
    [:documentation <string>]
    [:forward-only? {true | false}]
    [:backward-only? {true | false}]
    [:dont-optimize? {true | false}]
    [:confidence-level {:strict | :default}]
    [<keyword-option>*])
	
<sentence> can be any sentence that is legal as a top-level assertion.
<name> can be a string or symbol and will be bound to the asserted
proposition represented by <sentence>.  After this definition every
occurrence of <name> will be replaced by the associated proposition.

The options :forward-only? and :backward-only? can be used to tell the
inference engine to only use the rule in forward or backward direction
(this can also be achieved by using the `<<=' or `=>>' implication
arrows).  :dont-optimize?  tells the inference engine to not rearrange
the order of clauses in the antecedent of a rule and instead evaluate
them in their original order.  :confidence-level can be used to mark a
proposition as default only.

`<keyword-option>' represents a keyword followed by a value
that states an assertion about the proposition <name>.  See `defrelation'
for a description of `<keyword-option>'s.
\")" (CL:FUNCTION %DEFPROPOSITION)
    (CL:FUNCTION DEFPROPOSITION-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "DEFRULE"
    "(DEFUN (DEFRULE PROPOSITION) (|&REST| (ARGS PARSE-TREE)) :PUBLIC? TRUE :COMMAND? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Define (or redefine) a named rule (`defrule' is an alias
for `defproposition' which see).\")" (CL:FUNCTION %DEFRULE)
    (CL:FUNCTION DEFRULE-EVALUATOR-WRAPPER))
   (DEFINE-FUNCTION-OBJECT "CALL-DEFPROPOSITION"
    "(DEFUN (CALL-DEFPROPOSITION PROPOSITION) ((ARGUMENTS CONS)) :DOCUMENTATION \"Callable version of the `defproposition' command (which see).
Expects the same arguments as `defproposition' but supplied as a list.\" :PUBLIC? TRUE)"
    (CL:FUNCTION CALL-DEFPROPOSITION) NULL)
   (DEFINE-FUNCTION-OBJECT "NORMALIZE-DEFPROPOSITION-ARGUMENTS"
    "(DEFUN (NORMALIZE-DEFPROPOSITION-ARGUMENTS CONS) ((ARGUMENTS CONS)))"
    (CL:FUNCTION NORMALIZE-DEFPROPOSITION-ARGUMENTS) NULL)))

(CL:DEFUN STARTUP-LOGIC-IN ()
  (CL:LET*
   ((*MODULE* (GET-STELLA-MODULE "/LOGIC" (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2) (HELP-STARTUP-LOGIC-IN1)
    (HELP-STARTUP-LOGIC-IN2))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 4) (HELP-STARTUP-LOGIC-IN3))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7) (HELP-STARTUP-LOGIC-IN4)
    (HELP-STARTUP-LOGIC-IN5)
    (DEFINE-METHOD-OBJECT
     "(DEFMETHOD PROCESS-DEFINITION-OPTIONS ((SELF PROPOSITION) (OPTIONS OBJECT)))"
     (WRAP-METHOD-CODE (CL:FUNCTION PROCESS-DEFINITION-OPTIONS)) NULL)
    (DEFINE-FUNCTION-OBJECT "COMMAND<"
     "(DEFUN (COMMAND< BOOLEAN) ((COMMAND1 METHOD-SLOT) (COMMAND2 METHOD-SLOT)))"
     (CL:FUNCTION COMMAND<) NULL)
    (DEFINE-FUNCTION-OBJECT "LIST-LOGIC-COMMANDS"
     "(DEFUN (LIST-LOGIC-COMMANDS (LIST OF METHOD-SLOT)) ())"
     (CL:FUNCTION LIST-LOGIC-COMMANDS) NULL)
    (DEFINE-FUNCTION-OBJECT "HELP"
     "(DEFUN HELP (|&REST| (COMMANDS SYMBOL)) :COMMAND? TRUE :PUBLIC? TRUE :EVALUATE-ARGUMENTS? FALSE :DOCUMENTATION \"Describe specific commands, or print a list of available commands.\")"
     (CL:FUNCTION %HELP) (CL:FUNCTION HELP-EVALUATOR-WRAPPER))
    (DEFINE-FUNCTION-OBJECT "STARTUP-LOGIC-IN"
     "(DEFUN STARTUP-LOGIC-IN () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-LOGIC-IN) NULL)
    (CL:LET*
     ((FUNCTION (LOOKUP-FUNCTION SYM-LOGIC-IN-LOGIC-STARTUP-LOGIC-IN)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-LOGIC-IN-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupLogicIn") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "LOGIC")))
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *AVAILABLE-POWERLOOM-FEATURES* (LIST OF KEYWORD) (LIST :TRACE-SUBGOALS :TRACE-SOLUTIONS :TRACE-CLASSIFIER :ITERATIVE-DEEPENING :JUSTIFICATIONS :JUST-IN-TIME-INFERENCE :EMIT-THINKING-DOTS) :DOCUMENTATION \"List of PowerLoom environment features.\")"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *CURRENT-POWERLOOM-FEATURES* (LIST OF KEYWORD) (LIST) :DOCUMENTATION \"List of currently enabled PowerLoom environment features.\")"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *DEFAULT-POWERLOOM-FEATURES* (LIST OF KEYWORD) (LIST :JUST-IN-TIME-INFERENCE :EMIT-THINKING-DOTS) :DOCUMENTATION \"List of PowerLoom environment features enabled upon call to
'reset-features'.\")" NULL)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-SET-FEATURE
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-UNSET-FEATURE
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *LOGIC-PROMPT* STRING \"|= \" :DOCUMENTATION \"The prompt used by the PowerLoom listener.\" :PUBLIC? TRUE)"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFSPECIAL *PROMPT-SHOW-MODULE?* BOOLEAN TRUE :DOCUMENTATION \"Flag to control whether the logic prompt shows the module name.\" :PUBLIC? TRUE)"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *LOGIC-COMMAND-RESULT-INDENT* STRING \"\")" NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFSPECIAL *CONFIRM-INTERACTIVE-EXIT?* BOOLEAN (VERBATIM :COMMON-LISP FALSE :OTHERWISE TRUE) :DOCUMENTATION \"If TRUE exiting from the logic-command loop (or PowerLoom
listener) will be protected by a confirmation dialog.  This is mainly useful
for C++ and Java where exiting the listener will also exit the program.\" :PUBLIC? TRUE :DEMON-PROPERTY \"powerloom.confirmInteractiveExit\")"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *POWERLOOM-KB-FILE-EXTENSIONS* CONS (QUOTE (\".plm\" \".ploom\")) :DOCUMENTATION \"If the extension of a KB file is unspecified in a
`load' or `demo' command, try to find it with one of these extensions.\" :PUBLIC? TRUE)"
     NULL)
    (%ADD-LOAD-PATH "PL:kbs;")
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFSPECIAL *ASSERTION-MODULE* MODULE NULL :DOCUMENTATION \"If non-NULL, definition axioms and assertions will be evaluated
in this module instead of the IN-MODULE of a file, which allows us to separate
vocabulary definitions and their definitional constraints.\")" NULL)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-STELLA-LOAD
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-LOAD-DIRECTORY
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFSPECIAL *DEMO-LEVEL* INTEGER 0)" NULL)
    (%ADD-LOAD-PATH "PL:sources;logic;demos;")
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *DEMO-FILES* (CONS OF (CONS OF STRING-WRAPPER)) (BQUOTE ((\"basics\" \"Basic PowerLoom commands\" \"test-suite\") (\"classes\" \"Primitive and defined classes\" \"test-suite\") (\"collections\" \"Reasoning with collections\" \"test-suite\") (\"append\" \"Prolog-style `append'\" \"test-suite\") (\"inequalities\" \"Reasoning with inequalities\" \"test-suite\") (\"recursion\" \"Reasoning with recursive rules\" \"test-suite\") (\"negation\" \"Reasoning with negation\" \"test-suite\") (\"constraints\" \"Constraint propagation\" \"test-suite\") (\"equations\" \"Simple equational reasoning\" \"test-suite\") (\"subsumption\" \"Simple subsumption reasoning\" \"test-suite\") (\"family\" \"Subsumption reasoning within a family ontology\" \"test-suite\") (\"relation-hierarchy\" \"Finding sub, super and equivalent concepts and relations\" \"test-suite\") (\"defaults\" \"Default reasoning with Tweety and friends\" \"test-suite\") (\"defaults2\" \"More default reasoning\" \"test-suite\") (\"definition-syntax\" \"The whole scoop on relation definition, funny arrows, etc.\" \"test-suite\") (\"meta-relations\" \"Using meta-properties and relations\" \"test-suite\") (\"partial-match\" \"Reasoning with partial information\" \"test-suite\") (\"probability-learning\" \"Learning to answer probabilistic queries\" \"test-suite\") (\"regression-demo\" \"Learning to predict functions\") (\"rule-induction-demo\" \"Learning inference rules\") (\"test-suite\" \"PowerLoom test suite\" \"test-suite\"))) :DOCUMENTATION \"List of example demo files.
Each entry is a `(<file> <description>)' pair.\")" NULL)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-DEMO
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-TIME-COMMAND
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-START-ONTOSAURUS
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-START-POWERLOOM-SERVER
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-START-POWERLOOM-GUI
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFSPECIAL *TERMSOURCEBEINGPARSED* STRING NULL :DOCUMENTATION \"Points to the source of the relation being parsed.\")"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFSPECIAL *DESCRIPTIONUNDERCONSTRUCTION* OBJECT NULL :DOCUMENTATION \"Pofints to a description or its parse tree which
is the input to the description being constructed.\")" NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFSPECIAL *TERMUNDERCONSTRUCTION* OBJECT NULL :DOCUMENTATION \"Points to the parse tree which is the input to the
proposition being constructed.\")" NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *EXPRESSION-SIZE-CUTOFF* INTEGER 300 :DOCUMENTATION \"Limit on how big an s-expression we will print within
an error message.\")" NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *HANDLE-EXPLICITLY-QUALIFIED-LOGIC-OBJECTS?* BOOLEAN TRUE)"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *UNFINALIZED-OBJECTS* LIST (LIST) :DOCUMENTATION \"List of objects whose definitions and/or associated
axioms and constraints are not yet processed.\")" NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFSPECIAL *FINALIZEOBJECTSIMMEDIATELY?* BOOLEAN FALSE)" NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFSPECIAL *INHIBITOBJECTFINALIZATION?* BOOLEAN FALSE :DOCUMENTATION \"Used to prevent finalization from triggering in the
middle of 'delicate' computations.  Also used to prevent recursive
invocation of 'finalize-objects'.\")" NULL)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-DEFFUNCTION
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-DEFRELATION
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-DEFCONCEPT
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-DEFOBJECT
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-DEFINSTANCE
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-DEFPROPOSITION
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-DEFRULE
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *LOGIC-RELEVANT-STELLA-COMMANDS* (CONS OF SYMBOL) (BQUOTE (CC CLEAR-MODULE DEFMODULE IN-MODULE LIST-MODULES)))"
     NULL)
    (REGISTER-NATIVE-NAME SYM-LOGIC-IN-LOGIC-HELP
     KWD-LOGIC-IN-COMMON-LISP KWD-LOGIC-IN-FUNCTION))))
