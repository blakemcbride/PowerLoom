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
+---------------------------- END LICENSE BLOCK -----------------------------+
|#

(CL:IN-PACKAGE "STELLA")

;;; Auxiliary variables:

(CL:DEFVAR SYM-STARTUP-SYSTEM-WEBTOOLS-STARTUP-WEBTOOLS-SYSTEM NULL)
(CL:DEFVAR SYM-STARTUP-SYSTEM-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM (CL:SPECIAL *BOOTSTRAP-LOCK* *STARTUP-TIME-PHASE* *MODULE*))

(CL:DEFUN STARTUP-WEBTOOLS-SYSTEM ()
  (WITH-PROCESS-LOCK *BOOTSTRAP-LOCK*
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 0)
    (CL:WHEN (CL:NOT (SYSTEM-STARTED-UP? "stella" "/STELLA"))
     (STARTUP-STELLA-SYSTEM)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 1)
    (DEFINE-MODULE-FROM-STRINGIFIED-SOURCE "/STELLA/XML-OBJECTS"
     "(:LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"xml_objects\" :JAVA-PACKAGE \"edu.isi.webtools.objects.xml_objects\" :CASE-SENSITIVE? TRUE :INCLUDES (\"STELLA\") :CODE-ONLY? TRUE)")
    (DEFINE-MODULE-FROM-STRINGIFIED-SOURCE
     "/STELLA/XML-OBJECTS/SOAP-ENV"
     "(:LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"soap_env\" :JAVA-PACKAGE \"edu.isi.webtools.objects.soap_env\" :CASE-SENSITIVE? TRUE :INCLUDES (\"XML-OBJECTS\") :NAMESPACE? TRUE :CODE-ONLY? TRUE)")
    (DEFINE-MODULE-FROM-STRINGIFIED-SOURCE "/STELLA/XML-OBJECTS/XSD"
     "(:LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"xmlschema\" :JAVA-PACKAGE \"edu.isi.webtools.objects.xmlschema\" :CASE-SENSITIVE? TRUE :INCLUDES (\"XML-OBJECTS\") :NAMESPACE? TRUE)")
    (DEFINE-MODULE-FROM-STRINGIFIED-SOURCE "/STELLA/XML-OBJECTS/XSI"
     "(:LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"xmlschemainstance\" :JAVA-PACKAGE \"edu.isi.webtools.objects.xmlschemainstance\" :CASE-SENSITIVE? TRUE :INCLUDES (\"XML-OBJECTS\") :NAMESPACE? TRUE)")
    (DEFINE-MODULE-FROM-STRINGIFIED-SOURCE
     "/STELLA/XML-OBJECTS/APACHE-SOAP"
     "(:LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"apachesoap\" :JAVA-PACKAGE \"edu.isi.webtools.objects.apachesoap\" :CASE-SENSITIVE? TRUE :INCLUDES (\"XML-OBJECTS\") :NAMESPACE? TRUE)")
    (DEFINE-MODULE-FROM-STRINGIFIED-SOURCE "/HTTP"
     "(:USES (\"STELLA\") :LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"http\" :JAVA-PACKAGE \"edu.isi.webtools.http\" :CODE-ONLY? TRUE)")
    (DEFINE-MODULE-FROM-STRINGIFIED-SOURCE "/SOAP"
     "(:USES (\"STELLA\" \"SOAP-ENV\" \"HTTP\") :LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"http\" :JAVA-PACKAGE \"edu.isi.webtools.soap\" :CODE-ONLY? TRUE)")
    (DEFINE-MODULE-FROM-STRINGIFIED-SOURCE "/HTTP/WEBTOOLS"
     "(:INCLUDES (\"HTTP\" \"SOAP\") :LISP-PACKAGE \"STELLA\" :CPP-PACKAGE \"webtools\" :JAVA-PACKAGE \"edu.isi.webtools\" :CODE-ONLY? TRUE)"))
   (CL:LET*
    ((*MODULE*
      (GET-STELLA-MODULE "/HTTP/WEBTOOLS" (> *STARTUP-TIME-PHASE* 1)))
     (*CONTEXT* *MODULE*))
    (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
    (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
     (CL:SETQ SYM-STARTUP-SYSTEM-WEBTOOLS-STARTUP-WEBTOOLS-SYSTEM
      (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-WEBTOOLS-SYSTEM" NULL
       0))
     (CL:SETQ SYM-STARTUP-SYSTEM-STELLA-METHOD-STARTUP-CLASSNAME
      (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
       (GET-STELLA-MODULE "/STELLA" CL:T) 0)))
    (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
    (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
     (DEFINE-FUNCTION-OBJECT "STARTUP-WEBTOOLS-SYSTEM"
      "(DEFUN STARTUP-WEBTOOLS-SYSTEM () :PUBLIC? TRUE :C-CALLABLE? TRUE :C-NAMESPACE-PREFIX \"stella_\")"
      (CL:FUNCTION STARTUP-WEBTOOLS-SYSTEM) NULL)
     (CL:LET*
      ((FUNCTION
        (LOOKUP-FUNCTION
         SYM-STARTUP-SYSTEM-WEBTOOLS-STARTUP-WEBTOOLS-SYSTEM)))
      (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
       SYM-STARTUP-SYSTEM-STELLA-METHOD-STARTUP-CLASSNAME
       (WRAP-STRING "StartupWebtoolsSystem") NULL-STRING-WRAPPER)))
    (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
     (CLEANUP-UNFINALIZED-CLASSES))
    (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
     (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "/HTTP/WEBTOOLS")))
     (CL:LET* ((PHASE NULL-INTEGER) (ITER-006 0) (UPPER-BOUND-007 9))
      (CL:DECLARE (CL:TYPE CL:FIXNUM PHASE ITER-006 UPPER-BOUND-007))
      (CL:LOOP WHILE (CL:<= ITER-006 UPPER-BOUND-007) DO
       (CL:SETQ PHASE ITER-006) (CL:SETQ *STARTUP-TIME-PHASE* PHASE)
       (STARTUP-HTTP-CLIENT) (STARTUP-HTTP-SERVER) (STARTUP-SESSIONS)
       (STARTUP-XML-OBJECT) (STARTUP-XML-SCHEMA)
       (STARTUP-XML-SCHEMA-INSTANCE) (STARTUP-APACHE-SOAP)
       (STARTUP-SOAP-ENV) (STARTUP-MARSHALLER) (STARTUP-SOAP)
       (CL:SETQ ITER-006 (CL:1+ ITER-006))))
     (CL:SETQ *STARTUP-TIME-PHASE* 999)))))
