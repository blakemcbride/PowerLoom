;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; powerloom.lisp

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

(CL:DEFVAR KWD-POWERLOOM-RELEASE NULL)
(CL:DEFVAR KWD-POWERLOOM-LOG-LEVELS NULL)
(CL:DEFVAR KWD-POWERLOOM-LEVEL NULL)
(CL:DEFVAR KWD-POWERLOOM-DEVELOPMENT NULL)
(CL:DEFVAR KWD-POWERLOOM-MEDIUM NULL)
(CL:DEFVAR KWD-POWERLOOM-LOW NULL)
(CL:DEFVAR KWD-POWERLOOM-PREFIX NULL)
(CL:DEFVAR KWD-POWERLOOM-MAX-WIDTH NULL)
(CL:DEFVAR SYM-POWERLOOM-LOGIC-STARTUP-POWERLOOM NULL)
(CL:DEFVAR SYM-POWERLOOM-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM
 (CL:SPECIAL *STARTUP-TIME-PHASE* *MODULE* STANDARD-ERROR
  STANDARD-OUTPUT EOL NIL))

;;; (DEFGLOBAL *POWERLOOM-MAJOR-VERSION-NUMBER* ...)

(CL:DEFVAR *POWERLOOM-MAJOR-VERSION-NUMBER* 5)
(CL:DECLAIM (CL:TYPE CL:FIXNUM *POWERLOOM-MAJOR-VERSION-NUMBER*))

;;; (DEFGLOBAL *POWERLOOM-MINOR-VERSION-NUMBER* ...)

(CL:DEFVAR *POWERLOOM-MINOR-VERSION-NUMBER* 0)
(CL:DECLAIM (CL:TYPE CL:FIXNUM *POWERLOOM-MINOR-VERSION-NUMBER*))

;;; (DEFGLOBAL *POWERLOOM-RELEASE-STATE* ...)

(CL:DEFVAR *POWERLOOM-RELEASE-STATE* "")
(CL:DECLAIM (CL:TYPE CL:SIMPLE-STRING *POWERLOOM-RELEASE-STATE*))

;;; (DEFGLOBAL *POWERLOOM-PATCH-LEVEL* ...)

(CL:DEFVAR *POWERLOOM-PATCH-LEVEL* 0)
(CL:DECLAIM (CL:TYPE CL:FIXNUM *POWERLOOM-PATCH-LEVEL*))

;;; (DEFGLOBAL *POWERLOOM-VERSION-STRING* ...)

(CL:DEFVAR *POWERLOOM-VERSION-STRING* STELLA::NULL-STRING)
(CL:DECLAIM (CL:TYPE CL:SIMPLE-STRING *POWERLOOM-VERSION-STRING*))

;;; (DEFGLOBAL *POWERLOOM-EXECUTION-MODE* ...)

(CL:DEFVAR *POWERLOOM-EXECUTION-MODE* NULL
  "Either :development, :debugging or :release (so far) which controls
whether certain internal error and warning messages are surfaced to the user.")

;;; (DEFUN PL-LOG ...)

(CL:DEFUN PL-LOG (LOGLEVEL CL:&REST MESSAGE)
  (CL:LET* ((ARGLIST-000 NIL))
   (CL:LET* ((ARG-000 NULL) (ITER-000 MESSAGE) (COLLECT-000 NULL))
    (CL:LOOP WHILE ITER-000 DO (CL:SETQ ARG-000 (CL:POP ITER-000))
     (CL:IF (CL:EQ COLLECT-000 NULL)
      (CL:PROGN (CL:SETQ COLLECT-000 (CONS ARG-000 NIL))
       (CL:IF (CL:EQ ARGLIST-000 NIL) (CL:SETQ ARGLIST-000 COLLECT-000)
        (ADD-CONS-TO-END-OF-CONS-LIST ARGLIST-000 COLLECT-000)))
      (CL:PROGN (CL:SETF (%%REST COLLECT-000) (CONS ARG-000 NIL))
       (CL:SETQ COLLECT-000 (%%REST COLLECT-000))))))
   (LOG-MESSAGE "PowerLoom" LOGLEVEL ARGLIST-000)))

;;; (DEFUN (POWERLOOM-INFORMATION STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION () CL:SIMPLE-STRING) POWERLOOM-INFORMATION))
(CL:DEFUN POWERLOOM-INFORMATION ()
  "Returns information about the current PowerLoom implementation.
Useful when reporting problems."
  (CL:LET* ((SS (NEW-OUTPUT-STRING-STREAM)))
   (%%PRINT-STREAM (%NATIVE-STREAM SS) *POWERLOOM-VERSION-STRING* EOL
    (STELLA-INFORMATION))
   (THE-STRING-READER SS)))

(CL:DEFUN POWERLOOM-INFORMATION-EVALUATOR-WRAPPER (ARGUMENTS)
  (CL:SETQ ARGUMENTS ARGUMENTS)
  (CL:LET* ((RESULT (POWERLOOM-INFORMATION)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING RESULT))
   (CL:IF (CL:NOT (CL:EQ RESULT STELLA::NULL-STRING))
    (WRAP-STRING RESULT) NULL)))

;;; (DEFUN (POWERLOOM-COPYRIGHT-HEADER STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION () CL:SIMPLE-STRING)
  POWERLOOM-COPYRIGHT-HEADER))
(CL:DEFUN POWERLOOM-COPYRIGHT-HEADER ()
  (CL:LET*
   ((LOGICSYSTEM (GET-SYSTEM-DEFINITION "logic" CL:NIL))
    (SUBSTITUTION-LIST (NEW-KEY-VALUE-LIST)))
   (FILL-IN-DATE-SUBSTITUTION SUBSTITUTION-LIST)
   (CL:IF (CL:NOT (CL:EQ LOGICSYSTEM NULL))
    (SUBSTITUTE-TEMPLATE-VARIABLES-IN-STRING (%BANNER LOGICSYSTEM)
     SUBSTITUTION-LIST)
    "---------------------------- BEGIN LICENSE BLOCK ---------------------------+
 |                                                                            |
 | Version: MPL 1.1/GPL 2.0/LGPL 2.1                                          |
 |                                                                            |
 | The contents of this file are subject to the Mozilla Public License        |
 | Version 1.1 (the \"License\"); you may not use this file except in           |
 | compliance with the License. You may obtain a copy of the License at       |
 | http://www.mozilla.org/MPL/                                                |
 |                                                                            |
 | Software distributed under the License is distributed on an \"AS IS\" basis, |
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
 | Portions created by the Initial Developer are Copyright (C) 1997-2010      |
 | the Initial Developer. All Rights Reserved.                                |
 |                                                                            |
 | Contributor(s):                                                            |
 |                                                                            |
 | Alternatively, the contents of this file may be used under the terms of    |
 | either the GNU General Public License Version 2 or later (the \"GPL\"), or   |
 | the GNU Lesser General Public License Version 2.1 or later (the \"LGPL\"),   |
 | in which case the provisions of the GPL or the LGPL are applicable instead |
 | of those above. If you wish to allow use of your version of this file only |
 | under the terms of either the GPL or the LGPL, and not to allow others to  |
 | use your version of this file under the terms of the MPL, indicate your    |
 | decision by deleting the provisions above and replace them with the notice |
 | and other provisions required by the GPL or the LGPL. If you do not delete |
 | the provisions above, a recipient may use your version of this file under  |
 | the terms of any one of the MPL, the GPL or the LGPL.                      |
 |                                                                            |
 +----------------------------- END LICENSE BLOCK ----------------------------")))

;;; (DEFUN COPYRIGHT ...)

(CL:DEFUN COPYRIGHT ()
  "Print detailed PowerLoom copyright information."
  (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) " +"
   (POWERLOOM-COPYRIGHT-HEADER) "+" EOL))

;;; (DEFUN (COPYRIGHT-YEARS STRING) ...)

(CL:DECLAIM
 (CL:FTYPE (CL:FUNCTION () CL:SIMPLE-STRING) COPYRIGHT-YEARS))
(CL:DEFUN COPYRIGHT-YEARS ()
  (CL:LET*
   ((COPYRIGHT (POWERLOOM-COPYRIGHT-HEADER))
    (START (STRING-SEARCH COPYRIGHT "1997" 0))
    (END (STRING-SEARCH COPYRIGHT "  " START)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING COPYRIGHT)
    (CL:TYPE CL:FIXNUM START END))
   (SUBSEQUENCE COPYRIGHT START END)))

;;; (DEFGLOBAL *POWERLOOM-LOCK* ...)

(CL:DEFVAR *POWERLOOM-LOCK* NULL
  "Lock object for synchronizing safe multi-process access to PowerLoom")

;;; (DEFUN POWERLOOM ...)

(CL:DEFUN POWERLOOM ()
  "Run the PowerLoom listener.  Read logic commands from the
standard input, evaluate them, and print their results.  Exit if the user
entered `bye', `exit', `halt', `quit', or `stop'."
  (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) EOL
   "    Welcome to " *POWERLOOM-VERSION-STRING* EOL EOL
   "Copyright (C) USC Information Sciences Institute, "
   (COPYRIGHT-YEARS) "." EOL
   "PowerLoom is a trademark of the University of Southern California."
   EOL "PowerLoom comes with ABSOLUTELY NO WARRANTY!" EOL
   "Type `(copyright)' for detailed copyright information." EOL
   "Type `(help)' for a list of available commands." EOL
   "Type `(demo)' for a list of example applications." EOL
   "Type `bye', `exit', `halt', `quit', or `stop', to exit." EOL EOL)
  (CL:HANDLER-CASE
   (CL:PROGN (LOGIC-COMMAND-LOOP NULL)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) "Bye." EOL EOL))
   (CL:CONDITION (E)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     "Caught native non-STELLA exception " E " at top level." EOL)
    (PRINT-EXCEPTION-CONTEXT E STANDARD-ERROR)
    (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-ERROR)
     "Exiting PowerLoom." EOL EOL))))

(CL:DEFUN STARTUP-POWERLOOM ()
  (CL:LET*
   ((*MODULE* (GET-STELLA-MODULE "/LOGIC" (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
    (CL:SETQ KWD-POWERLOOM-RELEASE
     (INTERN-RIGID-SYMBOL-WRT-MODULE "RELEASE" NULL 2))
    (CL:SETQ KWD-POWERLOOM-LOG-LEVELS
     (INTERN-RIGID-SYMBOL-WRT-MODULE "LOG-LEVELS" NULL 2))
    (CL:SETQ KWD-POWERLOOM-LEVEL
     (INTERN-RIGID-SYMBOL-WRT-MODULE "LEVEL" NULL 2))
    (CL:SETQ KWD-POWERLOOM-DEVELOPMENT
     (INTERN-RIGID-SYMBOL-WRT-MODULE "DEVELOPMENT" NULL 2))
    (CL:SETQ KWD-POWERLOOM-MEDIUM
     (INTERN-RIGID-SYMBOL-WRT-MODULE "MEDIUM" NULL 2))
    (CL:SETQ KWD-POWERLOOM-LOW
     (INTERN-RIGID-SYMBOL-WRT-MODULE "LOW" NULL 2))
    (CL:SETQ KWD-POWERLOOM-PREFIX
     (INTERN-RIGID-SYMBOL-WRT-MODULE "PREFIX" NULL 2))
    (CL:SETQ KWD-POWERLOOM-MAX-WIDTH
     (INTERN-RIGID-SYMBOL-WRT-MODULE "MAX-WIDTH" NULL 2))
    (CL:SETQ SYM-POWERLOOM-LOGIC-STARTUP-POWERLOOM
     (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-POWERLOOM" NULL 0))
    (CL:SETQ SYM-POWERLOOM-STELLA-METHOD-STARTUP-CLASSNAME
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 4)
    (CL:SETQ *POWERLOOM-VERSION-STRING*
     (CONCATENATE "PowerLoom "
      (INTEGER-TO-STRING
       (CL:TRUNCATE *POWERLOOM-MAJOR-VERSION-NUMBER*))
      "."
      (INTEGER-TO-STRING
       (CL:TRUNCATE *POWERLOOM-MINOR-VERSION-NUMBER*))
      "." (INTEGER-TO-STRING (CL:TRUNCATE *POWERLOOM-PATCH-LEVEL*))
      *POWERLOOM-RELEASE-STATE*))
    (CL:SETQ *POWERLOOM-EXECUTION-MODE* KWD-POWERLOOM-RELEASE)
    (CL:SETQ *POWERLOOM-LOCK* (MAKE-PROCESS-LOCK)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
    (DEFINE-FUNCTION-OBJECT "PL-LOG"
     "(DEFUN PL-LOG ((LOGLEVEL KEYWORD) |&REST| (MESSAGE OBJECT)))"
     (CL:FUNCTION PL-LOG) NULL)
    (DEFINE-FUNCTION-OBJECT "POWERLOOM-INFORMATION"
     "(DEFUN (POWERLOOM-INFORMATION STRING) () :DOCUMENTATION \"Returns information about the current PowerLoom implementation.
Useful when reporting problems.\" :PUBLIC? TRUE :COMMAND? TRUE)"
     (CL:FUNCTION POWERLOOM-INFORMATION)
     (CL:FUNCTION POWERLOOM-INFORMATION-EVALUATOR-WRAPPER))
    (DEFINE-FUNCTION-OBJECT "POWERLOOM-COPYRIGHT-HEADER"
     "(DEFUN (POWERLOOM-COPYRIGHT-HEADER STRING) ())"
     (CL:FUNCTION POWERLOOM-COPYRIGHT-HEADER) NULL)
    (DEFINE-FUNCTION-OBJECT "COPYRIGHT"
     "(DEFUN COPYRIGHT () :COMMAND? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Print detailed PowerLoom copyright information.\")"
     (CL:FUNCTION COPYRIGHT) NULL)
    (DEFINE-FUNCTION-OBJECT "COPYRIGHT-YEARS"
     "(DEFUN (COPYRIGHT-YEARS STRING) ())"
     (CL:FUNCTION COPYRIGHT-YEARS) NULL)
    (DEFINE-FUNCTION-OBJECT "POWERLOOM"
     "(DEFUN POWERLOOM () :DOCUMENTATION \"Run the PowerLoom listener.  Read logic commands from the
standard input, evaluate them, and print their results.  Exit if the user
entered `bye', `exit', `halt', `quit', or `stop'.\" :PUBLIC? TRUE)"
     (CL:FUNCTION POWERLOOM) NULL)
    (DEFINE-FUNCTION-OBJECT "STARTUP-POWERLOOM"
     "(DEFUN STARTUP-POWERLOOM () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-POWERLOOM) NULL)
    (CL:LET*
     ((FUNCTION
       (LOOKUP-FUNCTION SYM-POWERLOOM-LOGIC-STARTUP-POWERLOOM)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-POWERLOOM-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupPowerloom") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "LOGIC")))
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *POWERLOOM-MAJOR-VERSION-NUMBER* INTEGER 5)" NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *POWERLOOM-MINOR-VERSION-NUMBER* INTEGER 0)" NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *POWERLOOM-RELEASE-STATE* STRING \"\")" NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *POWERLOOM-PATCH-LEVEL* INTEGER 0)" NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *POWERLOOM-VERSION-STRING* STRING (CONCATENATE \"PowerLoom \" (INTEGER-TO-STRING *POWERLOOM-MAJOR-VERSION-NUMBER*) \".\" (INTEGER-TO-STRING *POWERLOOM-MINOR-VERSION-NUMBER*) \".\" (INTEGER-TO-STRING *POWERLOOM-PATCH-LEVEL*) *POWERLOOM-RELEASE-STATE*))"
     NULL)
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *POWERLOOM-EXECUTION-MODE* KEYWORD :RELEASE :DOCUMENTATION \"Either :development, :debugging or :release (so far) which controls
whether certain internal error and warning messages are surfaced to the user.\" :DEMON-PROPERTY \"powerloom.executionMode\")"
     NULL)
    (%SET-LOGGING-PARAMETERS "PowerLoom"
     (CONS-LIST KWD-POWERLOOM-LOG-LEVELS
      (GET-QUOTED-TREE "((:NONE :LOW :MEDIUM :HIGH) \"/LOGIC\")"
       "/LOGIC")
      KWD-POWERLOOM-LEVEL
      (CL:IF
       (CL:EQ *POWERLOOM-EXECUTION-MODE* KWD-POWERLOOM-DEVELOPMENT)
       KWD-POWERLOOM-MEDIUM KWD-POWERLOOM-LOW)
      KWD-POWERLOOM-PREFIX (WRAP-STRING "PL") KWD-POWERLOOM-MAX-WIDTH
      (WRAP-INTEGER 250)))
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *POWERLOOM-LOCK* PROCESS-LOCK-OBJECT (MAKE-PROCESS-LOCK) :PUBLIC? TRUE :DOCUMENTATION \"Lock object for synchronizing safe multi-process access to PowerLoom\")"
     NULL))))
