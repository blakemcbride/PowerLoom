;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; startup-system.lisp

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
| The Original Code is the STELLA Programming Language.                      |
|                                                                            |
| The Initial Developer of the Original Code is                              |
| UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
| 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
|                                                                            |
| Portions created by the Initial Developer are Copyright (C) 2001-2023      |
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
|#

(CL:IN-PACKAGE "STELLA")

;;; Auxiliary variables:

(CL:DEFVAR SYM-STARTUP-SYSTEM-UTILITIES-STARTUP-UTILITIES-SYSTEM NULL)
(CL:DEFVAR SYM-STARTUP-SYSTEM-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM (CL:SPECIAL *BOOTSTRAP-LOCK* *STARTUP-TIME-PHASE* *MODULE*))

(CL:DEFUN STARTUP-UTILITIES-SYSTEM ()
  (WITH-PROCESS-LOCK *BOOTSTRAP-LOCK*
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 0)
    (CL:WHEN (CL:NOT (SYSTEM-STARTED-UP? "stella" "/STELLA"))
     (STARTUP-STELLA-SYSTEM)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 1)
    (DEFINE-MODULE-FROM-STRINGIFIED-SOURCE "/UTILITIES"
     "(:LISP-PACKAGE \"STELLA\" :JAVA-PACKAGE \"edu.isi.stella.utilities\" :USES (\"STELLA\") :NICKNAME \"UTIL\" :CODE-ONLY? TRUE)"))
   (CL:LET*
    ((*MODULE*
      (GET-STELLA-MODULE "/UTILITIES" (> *STARTUP-TIME-PHASE* 1)))
     (*CONTEXT* *MODULE*))
    (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
    (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
     (CL:SETQ SYM-STARTUP-SYSTEM-UTILITIES-STARTUP-UTILITIES-SYSTEM
      (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-UTILITIES-SYSTEM" NULL
       0))
     (CL:SETQ SYM-STARTUP-SYSTEM-STELLA-METHOD-STARTUP-CLASSNAME
      (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
       (GET-STELLA-MODULE "/STELLA" CL:T) 0)))
    (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
    (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
     (DEFINE-FUNCTION-OBJECT "STARTUP-UTILITIES-SYSTEM"
      "(DEFUN STARTUP-UTILITIES-SYSTEM () :PUBLIC? TRUE :C-CALLABLE? TRUE :C-NAMESPACE-PREFIX \"stella_\")"
      (CL:FUNCTION STARTUP-UTILITIES-SYSTEM) NULL)
     (CL:LET*
      ((FUNCTION
        (LOOKUP-FUNCTION
         SYM-STARTUP-SYSTEM-UTILITIES-STARTUP-UTILITIES-SYSTEM)))
      (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
       SYM-STARTUP-SYSTEM-STELLA-METHOD-STARTUP-CLASSNAME
       (WRAP-STRING "StartupUtilitiesSystem") NULL-STRING-WRAPPER)))
    (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
     (CLEANUP-UNFINALIZED-CLASSES))
    (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
     (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "/UTILITIES")))
     (CL:LET* ((PHASE NULL-INTEGER) (ITER-006 0) (UPPER-BOUND-007 9))
      (CL:DECLARE (CL:TYPE CL:FIXNUM PHASE ITER-006 UPPER-BOUND-007))
      (CL:LOOP WHILE (CL:<= ITER-006 UPPER-BOUND-007) DO
       (CL:SETQ PHASE ITER-006) (CL:SETQ *STARTUP-TIME-PHASE* PHASE)
       (STARTUP-MANUALS) (STARTUP-UNITS) (STARTUP-UNIT-DEFS)
       (CL:SETQ ITER-006 (CL:1+ ITER-006))))
     (CL:SETQ *STARTUP-TIME-PHASE* 999)))))
