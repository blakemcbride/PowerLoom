;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; shell.lisp

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
 | Portions created by the Initial Developer are Copyright (C) 2000-2023      |
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

(CL:DEFVAR SGT-SHELL-ONTOSAURUS-THREAD NULL)
(CL:DEFVAR SYM-SHELL-ONTOSAURUS-RUN-FUNCTION NULL)
(CL:DEFVAR SYM-SHELL-ONTOSAURUS-RUN-ARGUMENTS NULL)
(CL:DEFVAR SGT-SHELL-ONTOSAURUS-SHELL-PROCESS NULL)
(CL:DEFVAR SYM-SHELL-STELLA-DIRECTORY NULL)
(CL:DEFVAR SYM-SHELL-STELLA-INPUT-STREAM NULL)
(CL:DEFVAR SYM-SHELL-ONTOSAURUS-NATIVE-STDIN NULL)
(CL:DEFVAR SYM-SHELL-STELLA-OUTPUT-STREAM NULL)
(CL:DEFVAR SYM-SHELL-ONTOSAURUS-NATIVE-STDOUT NULL)
(CL:DEFVAR SYM-SHELL-ONTOSAURUS-ERROR-STREAM NULL)
(CL:DEFVAR SYM-SHELL-ONTOSAURUS-NATIVE-STDERR NULL)
(CL:DEFVAR SYM-SHELL-ONTOSAURUS-EXIT-STATUS NULL)
(CL:DEFVAR SGT-SHELL-STELLA-CONS NULL)
(CL:DEFVAR KWD-SHELL-BLOCK NULL)
(CL:DEFVAR KWD-SHELL-DIRECTORY NULL)
(CL:DEFVAR SGT-SHELL-STELLA-STRING NULL)
(CL:DEFVAR KWD-SHELL-INPUT NULL)
(CL:DEFVAR KWD-SHELL-IGNORE-ERRORS? NULL)
(CL:DEFVAR SGT-SHELL-STELLA-BOOLEAN NULL)
(CL:DEFVAR SYM-SHELL-ONTOSAURUS-SHELL-COMMAND NULL)
(CL:DEFVAR KWD-SHELL-COMMON-LISP NULL)
(CL:DEFVAR KWD-SHELL-FUNCTION NULL)
(CL:DEFVAR SYM-SHELL-ONTOSAURUS-STARTUP-SHELL NULL)
(CL:DEFVAR SYM-SHELL-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM
 (CL:SPECIAL *STARTUP-TIME-PHASE* *MODULE* TRUE-WRAPPER STANDARD-OUTPUT
  NULL-INTEGER NIL))

;;; (DEFCLASS THREAD ...)

(CL:DEFCLASS THREAD (STANDARD-OBJECT)
  ((NATIVE-THREAD :ALLOCATION :INSTANCE :ACCESSOR %NATIVE-THREAD)
   (RUN-FUNCTION :ALLOCATION :INSTANCE :ACCESSOR %RUN-FUNCTION)
   (RUN-ARGUMENTS :ALLOCATION :INSTANCE :ACCESSOR %RUN-ARGUMENTS)))

(CL:DEFUN NEW-THREAD (RUN-FUNCTION RUN-ARGUMENTS)
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE THREAD)))
   (CL:SETF (%RUN-FUNCTION SELF) RUN-FUNCTION)
   (CL:SETF (%RUN-ARGUMENTS SELF) RUN-ARGUMENTS)
   (CL:SETF (%NATIVE-THREAD SELF) NULL) (INITIALIZE-THREAD SELF) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF THREAD))
  SGT-SHELL-ONTOSAURUS-THREAD)

(CL:DEFUN ACCESS-THREAD-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME SYM-SHELL-ONTOSAURUS-RUN-FUNCTION)
    (CL:IF SETVALUE?
     (CL:SETF (%RUN-FUNCTION SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-FUNCTION-CODE (%RUN-FUNCTION SELF)))))
   ((CL:EQ SLOTNAME SYM-SHELL-ONTOSAURUS-RUN-ARGUMENTS)
    (CL:IF SETVALUE? (CL:SETF (%RUN-ARGUMENTS SELF) VALUE)
     (CL:SETQ VALUE (%RUN-ARGUMENTS SELF))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFMETHOD INITIALIZE-THREAD ...)

(CL:DEFMETHOD INITIALIZE-THREAD ((SELF THREAD))
  (CL:WHEN (CL:EQ (%RUN-FUNCTION SELF) NULL)
   (CL:ERROR
    (NEW-STELLA-EXCEPTION
     "initialize-thread: run-function not defined")))
  (CL-INITIALIZE-THREAD SELF))

;;; (DEFUN CL-INITIALIZE-THREAD ...)

(CL:DEFUN CL-INITIALIZE-THREAD (SELF)
  (CL:LET*
   ((NAME (YIELD-UNIQUE-GENSYM-NAME "STELLA-THREAD" NULL))
    (THREAD #+allegro (mp:make-process :name name) #-allegro NULL)
    (FUNCTION (%RUN-FUNCTION SELF)) (ARGUMENTS NIL))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING NAME))
   (CL:WHEN (NULL? THREAD)
    (CL:ERROR
     (NEW-STELLA-EXCEPTION
      "initialize-thread: threads not yet supported in this Lisp dialect")))
   (CL:SETF (%NATIVE-THREAD SELF) THREAD)
   (CL:WHEN (CL:NOT (CL:EQ (%RUN-ARGUMENTS SELF) NULL))
    (CL:SETQ ARGUMENTS (CONSIFY (%RUN-ARGUMENTS SELF))))
   #+allegro (cl:apply #'mp:process-preset thread function arguments)))

;;; (DEFUN JAVA-INITIALIZE-THREAD ...)

(CL:DEFUN JAVA-INITIALIZE-THREAD (SELF)
  (CL:LET*
   ((NAME (YIELD-UNIQUE-GENSYM-NAME "STELLA-THREAD" NULL))
    (THREAD NULL) (FUNCTION (%RUN-FUNCTION SELF)))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING NAME))
   (CL:LET* ((TEMP-000 (%RUN-ARGUMENTS SELF)))
    (CL:LET*
     ((ARGUMENTS
       (CL:IF (CL:NOT (CL:EQ TEMP-000 NULL)) TEMP-000 (VECTOR)))
      (NATARGS (%THE-ARRAY ARGUMENTS)))
     (CL:DECLARE (CL:TYPE CL:SIMPLE-VECTOR NATARGS))
     (CL:SETF (%NATIVE-THREAD SELF) THREAD)))))

;;; (DEFMETHOD START-THREAD ...)

(CL:DEFMETHOD START-THREAD ((SELF THREAD))
  "Start execution of `self's run-function."
  (CL:LET* ((THREAD (%NATIVE-THREAD SELF)))
   #+allegro (mp:process-enable thread)))

;;; (DEFMETHOD STOP-THREAD ...)

(CL:DEFMETHOD STOP-THREAD ((SELF THREAD))
  "Stop execution of `self's run-function."
  (CL:LET* ((THREAD (%NATIVE-THREAD SELF)))
   #+allegro (mp:process-disable thread)))

;;; (DEFMETHOD KILL-THREAD ...)

(CL:DEFMETHOD KILL-THREAD ((SELF THREAD))
  "Stop `self' and then destroy the associated thread object."
  (CL:LET* ((THREAD (%NATIVE-THREAD SELF))) (STOP-THREAD SELF)
   #+allegro (mp:process-kill thread)
   (CL:SETF (%NATIVE-THREAD SELF) NULL)))

;;; (DEFMETHOD WAIT-FOR-COMPLETION ...)

(CL:DEFMETHOD WAIT-FOR-COMPLETION ((SELF THREAD))
  "Suspend the current thread until `self' has completed execution."
  (CL:LET* ((THREAD (%NATIVE-THREAD SELF)))
   #+allegro (mp:process-wait "wait" #'(cl:lambda (thread) (CL:not (mp:process-active-p thread))) thread)))

;;; (DEFCLASS SHELL-PROCESS ...)

(CL:DEFCLASS SHELL-PROCESS (STANDARD-OBJECT)
  ((COMMAND :ALLOCATION :INSTANCE :ACCESSOR %COMMAND)
   (DIRECTORY :TYPE CL:SIMPLE-STRING :INITFORM STELLA::NULL-STRING
    :ALLOCATION :INSTANCE :ACCESSOR %DIRECTORY)
   (NATIVE-PROCESS :ALLOCATION :INSTANCE :ACCESSOR %NATIVE-PROCESS)
   (INPUT-STREAM :ALLOCATION :INSTANCE :ACCESSOR %INPUT-STREAM)
   (NATIVE-STDIN :ALLOCATION :INSTANCE :ACCESSOR %NATIVE-STDIN)
   (OUTPUT-STREAM :ALLOCATION :INSTANCE :ACCESSOR %OUTPUT-STREAM)
   (NATIVE-STDOUT :ALLOCATION :INSTANCE :ACCESSOR %NATIVE-STDOUT)
   (ERROR-STREAM :ALLOCATION :INSTANCE :ACCESSOR %ERROR-STREAM)
   (NATIVE-STDERR :ALLOCATION :INSTANCE :ACCESSOR %NATIVE-STDERR)
   (EXIT-STATUS :TYPE CL:FIXNUM :INITFORM NULL-INTEGER :ALLOCATION
    :INSTANCE :ACCESSOR %EXIT-STATUS)))

(CL:DEFUN NEW-SHELL-PROCESS ()
  (CL:LET* ((SELF NULL))
   (CL:SETQ SELF (CL:MAKE-INSTANCE (CL:QUOTE SHELL-PROCESS)))
   (CL:SETF (%EXIT-STATUS SELF) NULL-INTEGER)
   (CL:SETF (%NATIVE-STDERR SELF) NULL)
   (CL:SETF (%ERROR-STREAM SELF) NULL)
   (CL:SETF (%NATIVE-STDOUT SELF) NULL)
   (CL:SETF (%OUTPUT-STREAM SELF) NULL)
   (CL:SETF (%NATIVE-STDIN SELF) NULL)
   (CL:SETF (%INPUT-STREAM SELF) NULL)
   (CL:SETF (%NATIVE-PROCESS SELF) NULL)
   (CL:SETF (%DIRECTORY SELF) ".")
   (CL:SETF (%COMMAND SELF) STELLA::NULL-1D-ARRAY) SELF))

(CL:DEFMETHOD PRIMARY-TYPE ((SELF SHELL-PROCESS))
  SGT-SHELL-ONTOSAURUS-SHELL-PROCESS)

(CL:DEFUN ACCESS-SHELL-PROCESS-SLOT-VALUE (SELF SLOTNAME VALUE SETVALUE?)
  (CL:COND
   ((CL:EQ SLOTNAME SYM-SHELL-STELLA-DIRECTORY)
    (CL:IF SETVALUE? (CL:SETF (%DIRECTORY SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-STRING (%DIRECTORY SELF)))))
   ((CL:EQ SLOTNAME SYM-SHELL-STELLA-INPUT-STREAM)
    (CL:IF SETVALUE? (CL:SETF (%INPUT-STREAM SELF) VALUE)
     (CL:SETQ VALUE (%INPUT-STREAM SELF))))
   ((CL:EQ SLOTNAME SYM-SHELL-ONTOSAURUS-NATIVE-STDIN)
    (CL:IF SETVALUE? (CL:SETF (%NATIVE-STDIN SELF) VALUE)
     (CL:SETQ VALUE (%NATIVE-STDIN SELF))))
   ((CL:EQ SLOTNAME SYM-SHELL-STELLA-OUTPUT-STREAM)
    (CL:IF SETVALUE? (CL:SETF (%OUTPUT-STREAM SELF) VALUE)
     (CL:SETQ VALUE (%OUTPUT-STREAM SELF))))
   ((CL:EQ SLOTNAME SYM-SHELL-ONTOSAURUS-NATIVE-STDOUT)
    (CL:IF SETVALUE? (CL:SETF (%NATIVE-STDOUT SELF) VALUE)
     (CL:SETQ VALUE (%NATIVE-STDOUT SELF))))
   ((CL:EQ SLOTNAME SYM-SHELL-ONTOSAURUS-ERROR-STREAM)
    (CL:IF SETVALUE? (CL:SETF (%ERROR-STREAM SELF) VALUE)
     (CL:SETQ VALUE (%ERROR-STREAM SELF))))
   ((CL:EQ SLOTNAME SYM-SHELL-ONTOSAURUS-NATIVE-STDERR)
    (CL:IF SETVALUE? (CL:SETF (%NATIVE-STDERR SELF) VALUE)
     (CL:SETQ VALUE (%NATIVE-STDERR SELF))))
   ((CL:EQ SLOTNAME SYM-SHELL-ONTOSAURUS-EXIT-STATUS)
    (CL:IF SETVALUE?
     (CL:SETF (%EXIT-STATUS SELF) (%WRAPPER-VALUE VALUE))
     (CL:SETQ VALUE (WRAP-INTEGER (%EXIT-STATUS SELF)))))
   (CL:T
    (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "`" SLOTNAME
      "' is not a valid case option")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
  VALUE)

;;; (DEFUN (PARSE-SHELL-COMMAND (ARRAY () OF STRING)) ...)

(CL:DEFUN PARSE-SHELL-COMMAND (COMMAND)
  (CL:LET* ((PARSEDCOMMAND NIL) (RESULT STELLA::NULL-1D-ARRAY))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-VECTOR RESULT))
   (CL:LET* ((TEST-VALUE-000 (SAFE-PRIMARY-TYPE COMMAND)))
    (CL:COND
     ((CL:EQ TEST-VALUE-000 SGT-SHELL-STELLA-CONS)
      (CL:PROGN (CL:SETQ PARSEDCOMMAND COMMAND)))
     ((SUBTYPE-OF-STRING? TEST-VALUE-000)
      (CL:PROGN
       (CL:SETQ PARSEDCOMMAND
        (SPLIT-STRING (%WRAPPER-VALUE COMMAND) #\ ))))
     (CL:T
      (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
       (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000)
        "parse-shell-command: illegal shell command format: `" COMMAND
        "'")
       (CL:ERROR
        (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000)))))))
   (CL:WHEN #+allegro CL:t #-allegro CL:nil
    (CL:SETQ PARSEDCOMMAND
     (CONS (%%VALUE PARSEDCOMMAND) PARSEDCOMMAND)))
   (CL:SETQ RESULT (CL:MAKE-ARRAY (LENGTH PARSEDCOMMAND)))
   (CL:LET*
    ((ELT NULL) (ITER-000 PARSEDCOMMAND) (I NULL-INTEGER) (ITER-001 0))
    (CL:DECLARE (CL:TYPE CL:FIXNUM I ITER-001))
    (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
     (CL:SETQ ELT (%%VALUE ITER-000)) (CL:SETQ I ITER-001)
     (CL:SETF (CL:AREF RESULT I) (%WRAPPER-VALUE ELT))
     (CL:SETQ ITER-000 (%%REST ITER-000))
     (CL:SETQ ITER-001 (CL:1+ ITER-001))))
   RESULT))

;;; (DEFMETHOD START-PROCESS ...)

(CL:DEFMETHOD START-PROCESS ((SELF SHELL-PROCESS))
  "Start execution of `self's `command'."
  (CL:LET*
   ((PROCESS NULL) (COMMAND (%COMMAND SELF))
    (DIRECTORY (%DIRECTORY SELF)) (INPUT (%INPUT-STREAM SELF))
    (OUTPUT (%OUTPUT-STREAM SELF)) (ERROR (%ERROR-STREAM SELF))
    (STDIN NULL) (STDOUT NULL) (STDERR NULL))
   (CL:DECLARE (CL:TYPE CL:SIMPLE-VECTOR COMMAND)
    (CL:TYPE CL:SIMPLE-STRING DIRECTORY))
   #+allegro
       (CL:progn
         (CL:setq stdin (CL:if (defined? input) :stream CL:nil))
         (CL:setq stdout (CL:if (defined? output) :stream CL:nil))
         (CL:setq stderr (CL:if (defined? error) :stream CL:nil))
         (CL:multiple-value-setq (stdin stdout stderr process)
            (excl:run-shell-command command :input stdin :output stdout :error-output stderr :separate-streams CL:t
                                    :directory directory :wait CL:nil))
         (CL:when stdin
            (CL:ignore-errors (CL:setf (CL:stream-external-format stdin) STELLA-CHARSET)))
         (CL:when stdout
            (CL:ignore-errors (CL:setf (CL:stream-external-format stdout) STELLA-CHARSET)))
         (CL:when stderr
            (CL:ignore-errors (CL:setf (CL:stream-external-format stderr) STELLA-CHARSET)))
         (CL:setq stdin (CL:or stdin NULL))
         (CL:setq stdout (CL:or stdout NULL))
         (CL:setq stderr (CL:or stderr NULL)))
   (CL:WHEN (NULL? PROCESS)
    (CL:ERROR
     (NEW-STELLA-EXCEPTION
      "shell-process.start-process: not yet implemented")))
   (CL:SETF (%NATIVE-PROCESS SELF) PROCESS)
   (CL:WHEN (DEFINED? STDIN)
    (CL:LET* ((SELF-001 (NEW-OUTPUT-STREAM)))
     (CL:SETF (%NATIVE-STREAM SELF-001) STDIN)
     (CL:SETF (%NATIVE-STDIN SELF) SELF-001)))
   (CL:WHEN (DEFINED? STDOUT)
    (CL:LET* ((SELF-002 (NEW-INPUT-STREAM)))
     (CL:SETF (%NATIVE-STREAM SELF-002) STDOUT)
     (CL:SETF (%BUFFERING-SCHEME SELF-002) KWD-SHELL-BLOCK)
     (CL:SETF (%NATIVE-STDOUT SELF) SELF-002)))
   (CL:WHEN (DEFINED? STDERR)
    (CL:LET* ((SELF-003 (NEW-INPUT-STREAM)))
     (CL:SETF (%NATIVE-STREAM SELF-003) STDERR)
     (CL:SETF (%BUFFERING-SCHEME SELF-003) KWD-SHELL-BLOCK)
     (CL:SETF (%NATIVE-STDERR SELF) SELF-003)))))

;;; (DEFMETHOD WAIT-FOR-COMPLETION ...)

(CL:DEFMETHOD WAIT-FOR-COMPLETION ((SELF SHELL-PROCESS))
  "Suspend the current thread until `self' has completed execution."
  (CL:LET* ((PROCESS (%NATIVE-PROCESS SELF)) (EXIT NULL-INTEGER))
   (CL:DECLARE (CL:TYPE CL:FIXNUM EXIT))
   #+allegro (CL:setq exit (sys:reap-os-subprocess :pid process :wait CL:t))
   (CL:SETF (%EXIT-STATUS SELF) EXIT)))

;;; (DEFMETHOD DESTROY-PROCESS ...)

(CL:DEFMETHOD DESTROY-PROCESS ((SELF SHELL-PROCESS))
  "Stop `self' and then destroy the associated process object.
In Lisp, this doesn't yet actually kill the shell process, it just waits for its
completion.  Conceivably, we could execute a `kill' command to achieve that."
  (CL:LET* ((PROCESS (%NATIVE-PROCESS SELF)))
   #+allegro (sys:reap-os-subprocess :pid process :wait CL:t)
   (CL:WHEN (CL:NOT (CL:EQ (%NATIVE-STDIN SELF) NULL))
    (TERMINATE-OUTPUT-STREAM? (%NATIVE-STDIN SELF)))
   (CL:WHEN (CL:NOT (CL:EQ (%NATIVE-STDOUT SELF) NULL))
    (TERMINATE-INPUT-STREAM? (%NATIVE-STDOUT SELF))
    (CL:SETF (%TOKENIZER-STATE (%NATIVE-STDOUT SELF)) NULL))
   (CL:WHEN (CL:NOT (CL:EQ (%NATIVE-STDERR SELF) NULL))
    (TERMINATE-INPUT-STREAM? (%NATIVE-STDERR SELF))
    (CL:SETF (%TOKENIZER-STATE (%NATIVE-STDERR SELF)) NULL))
   (CL:SETF (%NATIVE-PROCESS SELF) NULL)))

;;; (DEFUN (EXECUTE-SHELL-COMMAND INTEGER) ...)

(CL:DECLAIM
 (CL:FTYPE
  (CL:FUNCTION (CL:T CL:SIMPLE-STRING CL:T CL:T CL:T) CL:FIXNUM)
  EXECUTE-SHELL-COMMAND))
(CL:DEFUN EXECUTE-SHELL-COMMAND (COMMAND DIRECTORY INPUT OUTPUT ERROR)
  "Run `command' in a shell and return its exit status.  If `directory' is
non-NULL, run it in that directory; if `input' is defined, feed `command's standard input
from that stream; if `output' and/or `error' are defined, copy `commands' standard output/
error to those streams.  It is the responsibility of the caller to close the supplied
streams (if any) and do any shell error handling based on exit status or error output."
  (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING DIRECTORY))
  #+MCL
  (CL:CHECK-TYPE DIRECTORY CL:SIMPLE-STRING)
  (CL:LET* ((SELF-000 (NEW-SHELL-PROCESS)))
   (CL:SETF (%COMMAND SELF-000) (PARSE-SHELL-COMMAND COMMAND))
   (CL:SETF (%DIRECTORY SELF-000)
    (CL:IF (CL:NOT (CL:EQ DIRECTORY STELLA::NULL-STRING)) DIRECTORY
     "."))
   (CL:SETF (%INPUT-STREAM SELF-000) INPUT)
   (CL:SETF (%OUTPUT-STREAM SELF-000) OUTPUT)
   (CL:SETF (%ERROR-STREAM SELF-000) ERROR)
   (CL:LET* ((PROCESS SELF-000)) (START-PROCESS PROCESS)
    (CL:LET*
     ((OUTPUTTHREAD
       (CL:IF (CL:NOT (CL:EQ OUTPUT NULL))
        (NEW-THREAD (CL:FUNCTION COPY-STREAM-TO-STREAM)
         (VECTOR (%NATIVE-STDOUT PROCESS) (%OUTPUT-STREAM PROCESS)))
        NULL))
      (ERRORTHREAD
       (CL:IF (CL:NOT (CL:EQ ERROR NULL))
        (NEW-THREAD (CL:FUNCTION COPY-STREAM-TO-STREAM)
         (VECTOR (%NATIVE-STDERR PROCESS) (%ERROR-STREAM PROCESS)))
        NULL)))
     (CL:WHEN (CL:NOT (CL:EQ OUTPUTTHREAD NULL))
      (START-THREAD OUTPUTTHREAD))
     (CL:WHEN (CL:NOT (CL:EQ ERRORTHREAD NULL))
      (START-THREAD ERRORTHREAD))
     (CL:WHEN (CL:NOT (CL:EQ INPUT NULL))
      (COPY-STREAM-TO-STREAM INPUT (%NATIVE-STDIN PROCESS))
      (CLOSE-STREAM (%NATIVE-STDIN PROCESS)))
     (CL:WHEN (CL:NOT (CL:EQ OUTPUTTHREAD NULL))
      (WAIT-FOR-COMPLETION OUTPUTTHREAD))
     (CL:WHEN (CL:NOT (CL:EQ ERRORTHREAD NULL))
      (WAIT-FOR-COMPLETION ERRORTHREAD))
     (WAIT-FOR-COMPLETION PROCESS) (DESTROY-PROCESS PROCESS)
     (%EXIT-STATUS PROCESS)))))

;;; (DEFSPECIAL *BLOCK-SHELL-COMMAND?* ...)

(CL:DEFVAR *BLOCK-SHELL-COMMAND?* CL:NIL
  "Allow disabling of `shell-command' in remote execution contexts
for security purposes.")

;;; (DEFUN (SHELL-COMMAND STRING-WRAPPER) ...)

(CL:DEFUN %SHELL-COMMAND (COMMAND OPTIONS)
  "User-level command interface to `execute-shell-command' (which see).
Runs `command' and returns its output (if any) as a string.  If the shell created
a non-zero exit status or generated any error output, an exception will be raised
- unless :ignore-errors? is true (which is the default).
If `command' was a string, split it at spaces to determine its arguments (this is
not sophisticated and does not handle quoting correctly).  For more complex commands,
supply them as a list of strings representing the program and its arguments.  If any
shell-level operations such as redirection are needed, use the `sh -c cmd' idiom.
If :input is supplied as a non-null string, feed it to `command's standard input.
If :directory is given, execute `command' in that directory."
  (CL:WHEN *BLOCK-SHELL-COMMAND?*
   (CL:ERROR
    (NEW-STELLA-EXCEPTION
     "Execution of `shell-command' is blocked in this context")))
  (CL:LET*
   ((THEOPTIONS
     (PARSE-LOGIC-COMMAND-OPTIONS OPTIONS
      (LIST* KWD-SHELL-DIRECTORY SGT-SHELL-STELLA-STRING
       KWD-SHELL-INPUT SGT-SHELL-STELLA-STRING KWD-SHELL-IGNORE-ERRORS?
       SGT-SHELL-STELLA-BOOLEAN NIL)
      CL:T CL:NIL))
    (DIRECTORY (UNWRAP-STRING (LOOKUP THEOPTIONS KWD-SHELL-DIRECTORY)))
    (INPUTSTRING (UNWRAP-STRING (LOOKUP THEOPTIONS KWD-SHELL-INPUT)))
    (EXIT 0) (OUTPUT STELLA::NULL-STRING) (ERROR STELLA::NULL-STRING)
    (IGNOREERRORS?
     (LOOKUP-WITH-DEFAULT THEOPTIONS KWD-SHELL-IGNORE-ERRORS?
      TRUE-WRAPPER)))
   (CL:DECLARE
    (CL:TYPE CL:SIMPLE-STRING DIRECTORY INPUTSTRING OUTPUT ERROR)
    (CL:TYPE CL:FIXNUM EXIT))
   (CL:WHEN (CL:NOT (CL:EQ DIRECTORY STELLA::NULL-STRING))
    (CL:SETQ DIRECTORY (TRANSLATE-LOGICAL-PATHNAME DIRECTORY)))
   (CL:LET*
    ((INPUTSTREAM
      (CL:IF (CL:NOT (BLANK-STRING? INPUTSTRING))
       (NEW-INPUT-STRING-STREAM INPUTSTRING) NULL))
     (OUTPUTSTREAM (NEW-OUTPUT-STRING-STREAM))
     (ERRORSTREAM (NEW-OUTPUT-STRING-STREAM)))
    (CL:SETQ EXIT
     (EXECUTE-SHELL-COMMAND COMMAND DIRECTORY INPUTSTREAM OUTPUTSTREAM
      ERRORSTREAM))
    (CL:SETQ OUTPUT (THE-STRING-READER OUTPUTSTREAM))
    (CL:SETQ ERROR (THE-STRING-READER ERRORSTREAM))
    (CL:WHEN (CL:NOT (CL:EQ INPUTSTREAM NULL))
     (CLOSE-STREAM INPUTSTREAM))
    (CLOSE-STREAM OUTPUTSTREAM) (CLOSE-STREAM ERRORSTREAM))
   (CL:WHEN (CL:NOT (BLANK-STRING? ERROR))
    (CL:IF (COERCE-WRAPPED-BOOLEAN-TO-BOOLEAN IGNOREERRORS?)
     (%%PRINT-STREAM (%NATIVE-STREAM STANDARD-OUTPUT) ERROR)
     (CL:LET* ((STREAM-000 (NEW-OUTPUT-STRING-STREAM)))
      (%%PRINT-STREAM (%NATIVE-STREAM STREAM-000) "shell-command: `"
       ERROR "'")
      (CL:ERROR
       (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-000))))))
   (CL:WHEN
    (CL:AND (CL:NOT (CL:= EXIT 0))
     (CL:NOT (COERCE-WRAPPED-BOOLEAN-TO-BOOLEAN IGNOREERRORS?)))
    (CL:LET* ((STREAM-001 (NEW-OUTPUT-STRING-STREAM)))
     (%%PRINT-STREAM (%NATIVE-STREAM STREAM-001)
      "shell-command: non-zero exit status=`" EXIT "'")
     (CL:ERROR (NEW-STELLA-EXCEPTION (THE-STRING-READER STREAM-001)))))
   (CL:IF (BLANK-STRING? OUTPUT) NULL (WRAP-STRING OUTPUT))))

(CL:DEFUN SHELL-COMMAND-EVALUATOR-WRAPPER (ARGUMENTS)
  (%SHELL-COMMAND (%%VALUE ARGUMENTS) (%%REST ARGUMENTS)))

(CL:DEFMACRO SHELL-COMMAND (CL:&WHOLE EXPRESSION CL:&REST IGNORE)
  "User-level command interface to `execute-shell-command' (which see).
Runs `command' and returns its output (if any) as a string.  If the shell created
a non-zero exit status or generated any error output, an exception will be raised
- unless :ignore-errors? is true (which is the default).
If `command' was a string, split it at spaces to determine its arguments (this is
not sophisticated and does not handle quoting correctly).  For more complex commands,
supply them as a list of strings representing the program and its arguments.  If any
shell-level operations such as redirection are needed, use the `sh -c cmd' idiom.
If :input is supplied as a non-null string, feed it to `command's standard input.
If :directory is given, execute `command' in that directory."
  (CL:DECLARE (CL:IGNORE IGNORE))
  (CL:LET ((*IGNORETRANSLATIONERRORS?* FALSE))
   (CL-INCREMENTALLY-TRANSLATE EXPRESSION)))

(CL:SETF (CL:MACRO-FUNCTION (CL:QUOTE |/ONTOSAURUS/SHELL-COMMAND|)) (CL:MACRO-FUNCTION (CL:QUOTE SHELL-COMMAND)))

(CL:DEFUN STARTUP-SHELL ()
  (CL:LET*
   ((*MODULE*
     (GET-STELLA-MODULE "/ONTOSAURUS" (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
    (CL:SETQ SGT-SHELL-ONTOSAURUS-THREAD
     (INTERN-RIGID-SYMBOL-WRT-MODULE "THREAD" NULL 1))
    (CL:SETQ SYM-SHELL-ONTOSAURUS-RUN-FUNCTION
     (INTERN-RIGID-SYMBOL-WRT-MODULE "RUN-FUNCTION" NULL 0))
    (CL:SETQ SYM-SHELL-ONTOSAURUS-RUN-ARGUMENTS
     (INTERN-RIGID-SYMBOL-WRT-MODULE "RUN-ARGUMENTS" NULL 0))
    (CL:SETQ SGT-SHELL-ONTOSAURUS-SHELL-PROCESS
     (INTERN-RIGID-SYMBOL-WRT-MODULE "SHELL-PROCESS" NULL 1))
    (CL:SETQ SYM-SHELL-STELLA-DIRECTORY
     (INTERN-RIGID-SYMBOL-WRT-MODULE "DIRECTORY"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0))
    (CL:SETQ SYM-SHELL-STELLA-INPUT-STREAM
     (INTERN-RIGID-SYMBOL-WRT-MODULE "INPUT-STREAM"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0))
    (CL:SETQ SYM-SHELL-ONTOSAURUS-NATIVE-STDIN
     (INTERN-RIGID-SYMBOL-WRT-MODULE "NATIVE-STDIN" NULL 0))
    (CL:SETQ SYM-SHELL-STELLA-OUTPUT-STREAM
     (INTERN-RIGID-SYMBOL-WRT-MODULE "OUTPUT-STREAM"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0))
    (CL:SETQ SYM-SHELL-ONTOSAURUS-NATIVE-STDOUT
     (INTERN-RIGID-SYMBOL-WRT-MODULE "NATIVE-STDOUT" NULL 0))
    (CL:SETQ SYM-SHELL-ONTOSAURUS-ERROR-STREAM
     (INTERN-RIGID-SYMBOL-WRT-MODULE "ERROR-STREAM" NULL 0))
    (CL:SETQ SYM-SHELL-ONTOSAURUS-NATIVE-STDERR
     (INTERN-RIGID-SYMBOL-WRT-MODULE "NATIVE-STDERR" NULL 0))
    (CL:SETQ SYM-SHELL-ONTOSAURUS-EXIT-STATUS
     (INTERN-RIGID-SYMBOL-WRT-MODULE "EXIT-STATUS" NULL 0))
    (CL:SETQ SGT-SHELL-STELLA-CONS
     (INTERN-RIGID-SYMBOL-WRT-MODULE "CONS"
      (GET-STELLA-MODULE "/STELLA" CL:T) 1))
    (CL:SETQ KWD-SHELL-BLOCK
     (INTERN-RIGID-SYMBOL-WRT-MODULE "BLOCK" NULL 2))
    (CL:SETQ KWD-SHELL-DIRECTORY
     (INTERN-RIGID-SYMBOL-WRT-MODULE "DIRECTORY" NULL 2))
    (CL:SETQ SGT-SHELL-STELLA-STRING
     (INTERN-RIGID-SYMBOL-WRT-MODULE "STRING"
      (GET-STELLA-MODULE "/STELLA" CL:T) 1))
    (CL:SETQ KWD-SHELL-INPUT
     (INTERN-RIGID-SYMBOL-WRT-MODULE "INPUT" NULL 2))
    (CL:SETQ KWD-SHELL-IGNORE-ERRORS?
     (INTERN-RIGID-SYMBOL-WRT-MODULE "IGNORE-ERRORS?" NULL 2))
    (CL:SETQ SGT-SHELL-STELLA-BOOLEAN
     (INTERN-RIGID-SYMBOL-WRT-MODULE "BOOLEAN"
      (GET-STELLA-MODULE "/STELLA" CL:T) 1))
    (CL:SETQ SYM-SHELL-ONTOSAURUS-SHELL-COMMAND
     (INTERN-RIGID-SYMBOL-WRT-MODULE "SHELL-COMMAND" NULL 0))
    (CL:SETQ KWD-SHELL-COMMON-LISP
     (INTERN-RIGID-SYMBOL-WRT-MODULE "COMMON-LISP" NULL 2))
    (CL:SETQ KWD-SHELL-FUNCTION
     (INTERN-RIGID-SYMBOL-WRT-MODULE "FUNCTION" NULL 2))
    (CL:SETQ SYM-SHELL-ONTOSAURUS-STARTUP-SHELL
     (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-SHELL" NULL 0))
    (CL:SETQ SYM-SHELL-STELLA-METHOD-STARTUP-CLASSNAME
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 5)
    (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "NATIVE-THREAD"
     "(DEFCLASS NATIVE-THREAD () :CL-NATIVE-TYPE \"#+allegro MP:PROCESS #-allegro CL:T\" :JAVA-NATIVE-TYPE \"java.lang.Thread\")")
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "THREAD"
        "(DEFCLASS THREAD (STANDARD-OBJECT) :SLOTS ((NATIVE-THREAD :TYPE NATIVE-THREAD) (RUN-FUNCTION :TYPE FUNCTION-CODE :REQUIRED? TRUE) (RUN-ARGUMENTS :TYPE VECTOR :REQUIRED? TRUE)) :INITIALIZER INITIALIZE-THREAD)")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS) (CL:FUNCTION NEW-THREAD))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION ACCESS-THREAD-SLOT-VALUE)))
    (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "NATIVE-SHELL-PROCESS"
     "(DEFCLASS NATIVE-SHELL-PROCESS () :CL-NATIVE-TYPE \"INTEGER\" :JAVA-NATIVE-TYPE \"java.lang.Process\")")
    (CL:LET*
     ((CLASS
       (DEFINE-CLASS-FROM-STRINGIFIED-SOURCE "SHELL-PROCESS"
        "(DEFCLASS SHELL-PROCESS (STANDARD-OBJECT) :SLOTS ((COMMAND :TYPE (ARRAY () OF STRING)) (DIRECTORY :TYPE STRING :INITIALLY \".\") (NATIVE-PROCESS :TYPE NATIVE-SHELL-PROCESS) (INPUT-STREAM :TYPE INPUT-STREAM) (NATIVE-STDIN :TYPE OUTPUT-STREAM) (OUTPUT-STREAM :TYPE OUTPUT-STREAM) (NATIVE-STDOUT :TYPE INPUT-STREAM) (ERROR-STREAM :TYPE OUTPUT-STREAM) (NATIVE-STDERR :TYPE INPUT-STREAM) (EXIT-STATUS :TYPE INTEGER :INITIALLY NULL)))")))
     (CL:SETF (%CLASS-CONSTRUCTOR-CODE CLASS)
      (CL:FUNCTION NEW-SHELL-PROCESS))
     (CL:SETF (%CLASS-SLOT-ACCESSOR-CODE CLASS)
      (CL:FUNCTION ACCESS-SHELL-PROCESS-SLOT-VALUE))))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
    (DEFINE-METHOD-OBJECT
     "(DEFMETHOD INITIALIZE-THREAD ((SELF THREAD)))"
     (WRAP-METHOD-CODE (CL:FUNCTION INITIALIZE-THREAD)) NULL)
    (DEFINE-FUNCTION-OBJECT "CL-INITIALIZE-THREAD"
     "(DEFUN CL-INITIALIZE-THREAD ((SELF THREAD)))"
     (CL:FUNCTION CL-INITIALIZE-THREAD) NULL)
    (DEFINE-FUNCTION-OBJECT "JAVA-INITIALIZE-THREAD"
     "(DEFUN JAVA-INITIALIZE-THREAD ((SELF THREAD)))"
     (CL:FUNCTION JAVA-INITIALIZE-THREAD) NULL)
    (DEFINE-METHOD-OBJECT
     "(DEFMETHOD START-THREAD ((SELF THREAD)) :DOCUMENTATION \"Start execution of `self's run-function.\" :PUBLIC? TRUE)"
     (WRAP-METHOD-CODE (CL:FUNCTION START-THREAD)) NULL)
    (DEFINE-METHOD-OBJECT
     "(DEFMETHOD STOP-THREAD ((SELF THREAD)) :DOCUMENTATION \"Stop execution of `self's run-function.\" :PUBLIC? TRUE)"
     (WRAP-METHOD-CODE (CL:FUNCTION STOP-THREAD)) NULL)
    (DEFINE-METHOD-OBJECT
     "(DEFMETHOD KILL-THREAD ((SELF THREAD)) :DOCUMENTATION \"Stop `self' and then destroy the associated thread object.\" :PUBLIC? TRUE)"
     (WRAP-METHOD-CODE (CL:FUNCTION KILL-THREAD)) NULL)
    (DEFINE-METHOD-OBJECT
     "(DEFMETHOD WAIT-FOR-COMPLETION ((SELF THREAD)) :DOCUMENTATION \"Suspend the current thread until `self' has completed execution.\" :PUBLIC? TRUE)"
     (WRAP-METHOD-CODE (CL:FUNCTION WAIT-FOR-COMPLETION)) NULL)
    (DEFINE-FUNCTION-OBJECT "PARSE-SHELL-COMMAND"
     "(DEFUN (PARSE-SHELL-COMMAND (ARRAY () OF STRING)) ((COMMAND OBJECT)))"
     (CL:FUNCTION PARSE-SHELL-COMMAND) NULL)
    (DEFINE-METHOD-OBJECT
     "(DEFMETHOD START-PROCESS ((SELF SHELL-PROCESS)) :DOCUMENTATION \"Start execution of `self's `command'.\")"
     (WRAP-METHOD-CODE (CL:FUNCTION START-PROCESS)) NULL)
    (DEFINE-METHOD-OBJECT
     "(DEFMETHOD WAIT-FOR-COMPLETION ((SELF SHELL-PROCESS)) :DOCUMENTATION \"Suspend the current thread until `self' has completed execution.\" :PUBLIC? TRUE)"
     (WRAP-METHOD-CODE (CL:FUNCTION WAIT-FOR-COMPLETION)) NULL)
    (DEFINE-METHOD-OBJECT
     "(DEFMETHOD DESTROY-PROCESS ((SELF SHELL-PROCESS)) :DOCUMENTATION \"Stop `self' and then destroy the associated process object.
In Lisp, this doesn't yet actually kill the shell process, it just waits for its
completion.  Conceivably, we could execute a `kill' command to achieve that.\" :PUBLIC? TRUE)"
     (WRAP-METHOD-CODE (CL:FUNCTION DESTROY-PROCESS)) NULL)
    (DEFINE-FUNCTION-OBJECT "EXECUTE-SHELL-COMMAND"
     "(DEFUN (EXECUTE-SHELL-COMMAND INTEGER) ((COMMAND OBJECT) (DIRECTORY STRING) (INPUT INPUT-STREAM) (OUTPUT OUTPUT-STREAM) (ERROR OUTPUT-STREAM)) :DOCUMENTATION \"Run `command' in a shell and return its exit status.  If `directory' is
non-NULL, run it in that directory; if `input' is defined, feed `command's standard input
from that stream; if `output' and/or `error' are defined, copy `commands' standard output/
error to those streams.  It is the responsibility of the caller to close the supplied
streams (if any) and do any shell error handling based on exit status or error output.\" :PUBLIC? TRUE)"
     (CL:FUNCTION EXECUTE-SHELL-COMMAND) NULL)
    (DEFINE-FUNCTION-OBJECT "SHELL-COMMAND"
     "(DEFUN (SHELL-COMMAND STRING-WRAPPER) ((COMMAND OBJECT) |&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"User-level command interface to `execute-shell-command' (which see).
Runs `command' and returns its output (if any) as a string.  If the shell created
a non-zero exit status or generated any error output, an exception will be raised
- unless :ignore-errors? is true (which is the default).
If `command' was a string, split it at spaces to determine its arguments (this is
not sophisticated and does not handle quoting correctly).  For more complex commands,
supply them as a list of strings representing the program and its arguments.  If any
shell-level operations such as redirection are needed, use the `sh -c cmd' idiom.
If :input is supplied as a non-null string, feed it to `command's standard input.
If :directory is given, execute `command' in that directory.\" :COMMAND? TRUE :PUBLIC? TRUE)"
     (CL:FUNCTION %SHELL-COMMAND)
     (CL:FUNCTION SHELL-COMMAND-EVALUATOR-WRAPPER))
    (DEFINE-FUNCTION-OBJECT "STARTUP-SHELL"
     "(DEFUN STARTUP-SHELL () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-SHELL) NULL)
    (CL:LET*
     ((FUNCTION (LOOKUP-FUNCTION SYM-SHELL-ONTOSAURUS-STARTUP-SHELL)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-SHELL-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupShell") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "ONTOSAURUS")))
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFSPECIAL *BLOCK-SHELL-COMMAND?* BOOLEAN FALSE :DOCUMENTATION \"Allow disabling of `shell-command' in remote execution contexts
for security purposes.\")" NULL)
    (REGISTER-NATIVE-NAME SYM-SHELL-ONTOSAURUS-SHELL-COMMAND
     KWD-SHELL-COMMON-LISP KWD-SHELL-FUNCTION))))
