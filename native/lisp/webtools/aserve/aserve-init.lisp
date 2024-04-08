;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; aserve-init.lisp

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
 | Portions created by the Initial Developer are Copyright (C) 2003-2023      |
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

(CL:DEFVAR SYM-ASERVE-INIT-STELLA-STARTUP-ASERVE-INIT NULL)
(CL:DEFVAR SYM-ASERVE-INIT-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM (CL:SPECIAL *STELLA-MODULE* *MODULE*))

;;; (VERBATIM :COMMON-LISP ...)


;;; Convenience for Allegro, since it should be loadable via require.
;;; Other lisps will need to either have loaded it beforehand or else
;;; define a function of no arguments called LOAD-ASERVE visible in the
;;; CL-USER package that will load the Aserve code.

#+:EXCL(CL:eval-when (:compile-toplevel :load-toplevel :execute)
         (CL:require :ASERVE))
#-:EXCL(CL:eval-when (:compile-toplevel :load-toplevel :execute)
         (CL:unless (CL:find-package :net.aserve)
           (CL:let ((loader-function-symbol (CL:find-symbol "LOAD-ASERVE" "CL-USER")))
             (CL:if (CL:and loader-function-symbol (CL:fboundp loader-function-symbol))
               (CL:funcall loader-function-symbol)
               (CL:cerror "Continue trying to load file.  Requires ASERVE to have been loaded."
                       "Oops.  Looks like the required ASERVE system has not been loaded yet.")))))


(CL:DEFUN STARTUP-ASERVE-INIT ()
  (CL:LET* ((*MODULE* *STELLA-MODULE*) (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
    (CL:SETQ SYM-ASERVE-INIT-STELLA-STARTUP-ASERVE-INIT
     (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-ASERVE-INIT" NULL 0))
    (CL:SETQ SYM-ASERVE-INIT-STELLA-METHOD-STARTUP-CLASSNAME
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME" NULL
      0)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
    (DEFINE-FUNCTION-OBJECT "STARTUP-ASERVE-INIT"
     "(DEFUN STARTUP-ASERVE-INIT () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-ASERVE-INIT) NULL)
    (CL:LET*
     ((FUNCTION
       (LOOKUP-FUNCTION SYM-ASERVE-INIT-STELLA-STARTUP-ASERVE-INIT)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-ASERVE-INIT-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupAserveInit") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "STELLA"))))))
