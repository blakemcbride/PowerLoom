;;; -*- Mode: Lisp; Package: CL-USER; Syntax: COMMON-LISP; Base: 10 -*-

;;;;;;;;;;;;;;;;;;;;;;;;;;;; BEGIN LICENSE BLOCK ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;                                                                            ;
; Version: MPL 1.1/GPL 2.0/LGPL 2.1                                          ;
;                                                                            ;
; The contents of this file are subject to the Mozilla Public License        ;
; Version 1.1 (the "License"); you may not use this file except in           ;
; compliance with the License. You may obtain a copy of the License at       ;
; http://www.mozilla.org/MPL/                                                ;
;                                                                            ;
; Software distributed under the License is distributed on an "AS IS" basis, ;
; WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License   ;
; for the specific language governing rights and limitations under the       ;
; License.                                                                   ;
;                                                                            ;
; The Original Code is the PowerLoom KR&R System.                            ;
;                                                                            ;
; The Initial Developer of the Original Code is                              ;
; UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          ;
; 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               ;
;                                                                            ;
; Portions created by the Initial Developer are Copyright (C) 1997-2019      ;
; the Initial Developer. All Rights Reserved.                                ;
;                                                                            ;
; Contributor(s):                                                            ;
;                                                                            ;
; Alternatively, the contents of this file may be used under the terms of    ;
; either the GNU General Public License Version 2 or later (the "GPL"), or   ;
; the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),   ;
; in which case the provisions of the GPL or the LGPL are applicable instead ;
; of those above. If you wish to allow use of your version of this file only ;
; under the terms of either the GPL or the LGPL, and not to allow others to  ;
; use your version of this file under the terms of the MPL, indicate your    ;
; decision by deleting the provisions above and replace them with the notice ;
; and other provisions required by the GPL or the LGPL. If you do not delete ;
; the provisions above, a recipient may use your version of this file under  ;
; the terms of any one of the MPL, the GPL or the LGPL.                      ;
;                                                                            ;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;; END LICENSE BLOCK ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;


;;; Load PowerLoom.

(in-package "CL-USER")


;;; Bootstrap STELLA:

;; Set this to t to use structs instead of CLOS objects as the implementation
;; of STELLA classes.  Structs are significantly faster but can cause problems
;; when classes are redefined.  Use for production versions only.
(defvar *load-cl-struct-stella?* t)

;; In CMUCL and derivatives, use low optimization levels to more
;; easily uncover issues due to imprecise type declarations (or too
;; agressive CMUCL type inference); however, to achieve reasonable
;; speed, we need speed=3; also turn down verbosity levels so we can
;; actually see what's going on during compilation:
#+(or cmu sbcl)
(progn (setq *stella-compiler-optimization*
         '(optimize (speed 3) (safety 1) (space 1) (debug 1)))
       (setq *compile-verbose* nil
             *compile-print* nil
             *gc-verbose* nil))

;; Work around a compiler bug that surfaces with safety=1 in ACL 8.1:
#+allegro-v8.1
(setq *stella-compiler-optimization*
  '(optimize (speed 3) (safety 2) (space 0) (debug 1)))

(load (merge-pathnames (make-pathname :directory (append (pathname-directory *load-pathname*) '("native" "lisp" "stella")))
                       (make-pathname :name "load-stella" :type (if *load-cl-struct-stella?* "slisp" "lisp"))))

;; needed to make Allegro Emacs FI interface behave sanely with STELLA:
#+allegro (tpl:setq-default cl-user::*redefinition-warnings* nil)


;;; Retranslate STELLA:

;; To generate and install an updated version of STELLA for use with PowerLoom, do this:
#|
(cl:load ".../stella/load-stella")
(translate-system "stella" :common-lisp :root-native-directory ".../powerloom/native/")
|#


;;; Load PowerLoom systems:

(defvar *powerloom-root-directory* (namestring (make-pathname :directory (pathname-directory *load-truename*))))
(defvar *powerloom-binary-directory* (stella::concatenate "PL:native;lisp;bin;" *stella-binary-subdirectory* ";"))

(stella::define-logical-host-property "PL" :root-directory #.*powerloom-root-directory*)


;; Set this to t to load various optional extension systems such as RDBMS support.
;; Alternatively, you can load systems individually via `stella::make-system'.
(defvar *load-all-extensions?* nil)

(unless (stella::system-loaded? "logic")
  (stella::make-system "powerloom" :common-lisp
                       :root-native-directory "PL:native;"
                       :root-binary-directory #.*powerloom-binary-directory*))

;; do this to generate a full C++ translation after loading PowerLoom:
;(translate-system "powerloom" :cpp :force-translation? true :recursive? true :production-settings? true :root-native-directory "PL:native;")

(when *load-all-extensions?*
  (stella::load-all-extension-systems))

(defun powerloom ()
  (stella::powerloom))

(format t "~&PowerLoom ~a loaded.~%~
           Type `(powerloom)' to get started.~%~
           Type `(in-package \"STELLA\")' to run PowerLoom commands directly from the Lisp prompt."
	(stella::get-system-version-string (stella::get-system-definition "powerloom" cl:t)))

(stella::in-module "PL-USER")
