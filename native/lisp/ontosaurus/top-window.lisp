;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; top-window.lisp

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

(CL:DEFVAR SYM-TOP-WINDOW-STELLA-CODE-ONLY? NULL)
(CL:DEFVAR SYM-TOP-WINDOW-STELLA-NAMESPACE? NULL)
(CL:DEFVAR KWD-TOP-WINDOW-CONTEXT NULL)
(CL:DEFVAR KWD-TOP-WINDOW-CONCEPT NULL)
(CL:DEFVAR KWD-TOP-WINDOW-RELATION NULL)
(CL:DEFVAR KWD-TOP-WINDOW-INSTANCE NULL)
(CL:DEFVAR KWD-TOP-WINDOW-GET NULL)
(CL:DEFVAR KWD-TOP-WINDOW-CONTENT-TYPE NULL)
(CL:DEFVAR KWD-TOP-WINDOW-HTML NULL)
(CL:DEFVAR KWD-TOP-WINDOW-DOCUMENTATION NULL)
(CL:DEFVAR SYM-TOP-WINDOW-ONTOSAURUS-STARTUP-TOP-WINDOW NULL)
(CL:DEFVAR SYM-TOP-WINDOW-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM
 (CL:SPECIAL *STARTUP-TIME-PHASE* *MODULE* *ERROR-BACKGROUND-COLOR* EOL
  *CONTROL-BACKGROUND-COLOR* NIL FALSE-WRAPPER))

;;; (DEFGLOBAL *POWERLOOM-REFERENCE-MANUAL-URL* ...)

(CL:DEFVAR *POWERLOOM-REFERENCE-MANUAL-URL* "http://www.isi.edu/isd/LOOM/PowerLoom/documentation/manual/manual_frame.html")
(CL:DECLAIM (CL:TYPE CL:SIMPLE-STRING *POWERLOOM-REFERENCE-MANUAL-URL*))

;;; (DEFUN (SAVING-ALLOWED? BOOLEAN) ...)

(CL:DEFUN SAVING-ALLOWED? ()
  CL:NIL)

;;; (DEFUN (LOADING-ALLOWED? BOOLEAN) ...)

(CL:DEFUN LOADING-ALLOWED? ()
  CL:NIL)

;;; (DEFUN (EDITTING-ALLOWED? BOOLEAN) ...)

(CL:DEFUN EDITTING-ALLOWED? ()
  CL:NIL)

;;; (DEFUN (EDITTING-POSSIBLE? BOOLEAN) ...)

(CL:DEFUN EDITTING-POSSIBLE? ()
  CL:NIL)

;;; (DEFUN (CURRENT-EDIT-LOCK? BOOLEAN) ...)

(CL:DEFUN CURRENT-EDIT-LOCK? ()
  CL:NIL)

;;; (DEFUN (SORTED-CONTEXTS (CONS OF STRING-WRAPPER)) ...)

(CL:DEFUN SORTED-CONTEXTS ()
  (CL:LET* ((CONTEXTNAMES NIL))
   (CL:LET* ((M NULL) (ITER-000 (ALL-MODULES)))
    (CL:LOOP WHILE (NEXT? ITER-000) DO (CL:SETQ M (%VALUE ITER-000))
     (CL:WHEN
      (CL:AND
       (CL:NOT
        (%WRAPPER-VALUE
         (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS M)
          SYM-TOP-WINDOW-STELLA-CODE-ONLY? FALSE-WRAPPER)))
       (CL:NOT
        (%WRAPPER-VALUE
         (DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS M)
          SYM-TOP-WINDOW-STELLA-NAMESPACE? FALSE-WRAPPER))))
      (CL:SETQ CONTEXTNAMES
       (CONS (WRAP-STRING (NAME M)) CONTEXTNAMES)))))
   (SORT CONTEXTNAMES (CL:FUNCTION WRAPPED-STRING-LESS-THAN?))))

;;; (DEFUN SERVE-CONTROL-PANEL-INTERNAL ...)

(CL:DEFUN SERVE-CONTROL-PANEL-INTERNAL (STREAM)
  (CL:PROGN (%%PRINT-STREAM STREAM "<HTML>")
   (CL:PROGN (%%PRINT-STREAM STREAM "<HEAD>")
    (CL:PROGN (%%PRINT-STREAM STREAM "<TITLE>")
     (%%PRINT-STREAM STREAM "PowerLoom Browser Control Panel")
     (%%PRINT-STREAM STREAM "</TITLE>" EOL))
    (WRITE-CONTROL-PANEL-SCRIPT STREAM)
    (%%PRINT-STREAM STREAM "</HEAD>" EOL))
   (CL:LET*
    ((TAG-009
      (CONCATENATE "BODY BGCOLOR='#" *CONTROL-BACKGROUND-COLOR* "'")))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TAG-009))
    (%%PRINT-STREAM STREAM "<" TAG-009 ">") (WRITE-TOP-SECTION STREAM)
    (WRITE-THEORY-SECTION STREAM) (WRITE-BOTTOM-SECTION STREAM)
    (%%PRINT-STREAM STREAM "</"
     (SUBSEQUENCE TAG-009 0 (POSITION TAG-009 #\  0)) ">" EOL))
   (%%PRINT-STREAM STREAM "</HTML>" EOL))
  NULL)

;;; (DEFUN WRITE-THEORY-SECTION ...)

(CL:DEFUN WRITE-THEORY-SECTION (STREAM)
  (%%PRINT-STREAM STREAM "<b>"
   (LOOKUP-TERM KWD-TOP-WINDOW-CONTEXT CL:T CL:NIL) ":</b>&nbsp;")
  (%%PRINT-STREAM STREAM
   "<SELECT NAME=\"theory\" onChange='document.cookie=\"theory=\" + this[this.selectedIndex].value + \";\";'>"
   EOL)
  (CL:LET* ((C NULL) (ITER-000 (SORTED-CONTEXTS)))
   (CL:LOOP WHILE (CL:NOT (CL:EQ ITER-000 NIL)) DO
    (CL:SETQ C (%%VALUE ITER-000))
    (%%PRINT-STREAM STREAM "<option VALUE='" (%WRAPPER-VALUE C) "'>"
     (%WRAPPER-VALUE C) "</option>" EOL)
    (CL:SETQ ITER-000 (%%REST ITER-000))))
  (%%PRINT-STREAM STREAM "</SELECT>" EOL)
  NULL)

;;; (DEFUN WRITE-TOP-SECTION ...)

(CL:DEFUN WRITE-TOP-SECTION (STREAM)
  (%%PRINT-STREAM STREAM
   "<FORM NAME=\"navform\" TARGET=\"content\" METHOD=\"POST\" onSubmit=\"return formTest(this)\">"
   EOL "<TABLE BORDER>" EOL "<TR>" EOL
   "<TD ALIGN=center COLSPAN=1 ROWSPAN=1>" EOL
   "<A HREF=\"help/intro.html\" TARGET=\"content\" onMouseOver=\"window.status='Shows directions for using this browser'; return true\">"
   EOL
   "<IMG SRC=\"/ploom/icons/button-34-help.gif\" BORDER=0 WIDTH=12 HEIGHT=14></a></TD>"
   EOL "<TD COLSPAN=1 ROWSPAN=1 VALIGN=TOP>" EOL)
  NULL)

;;; (DEFUN WRITE-BOTTOM-SECTION ...)

(CL:DEFUN WRITE-BOTTOM-SECTION (STREAM)
  (%%PRINT-STREAM STREAM
   "<input TYPE=button  NAME=\"show\" VALUE=\"Show\" onClick=\"loadContextURL('content', 'show', this.form)\">
")
  (CL:WHEN (SAVING-ALLOWED?)
   (%%PRINT-STREAM STREAM
    "<input TYPE=button  NAME=\"save\" VALUE=\"Save...\" onClick=\"loadContextURL('content', 'save',this.form)\">
"))
  (CL:WHEN (LOADING-ALLOWED?)
   (%%PRINT-STREAM STREAM
    "<input TYPE=button  NAME= \"load\" VALUE=\"Load...\" 
       onClick=\"loadContextURL('content', 'load', this.form)\">
"))
  (CL:WHEN (EDITTING-ALLOWED?)
   (%%PRINT-STREAM STREAM
    "<input TYPE=button  NAME=\"newctxt\" VALUE=\"New...\" onClick=\"loadNewContextURL('toc', 'COMMON-LISP-USER', this.form)\">
"))
  (%%PRINT-STREAM STREAM EOL "</TD>")
  (%%PRINT-STREAM STREAM "<TD ROWSPAN=1 ALIGN=CENTER>" EOL)
  (%%PRINT-STREAM STREAM
   "<INPUT TYPE=\"button\" NAME=\"swap\" VALUE=\"Hold Window\" 
  onClick=\"putLeft(parent.frames[2].document.location.href)\" onMouseOver=\"window.status='Moves the content window into the reference window.'; return true\">"
   EOL)
  (%%PRINT-STREAM STREAM "</TD>" EOL)
  (CL:IF (EDITTING-POSSIBLE?)
   (CL:PROGN (%%PRINT-STREAM STREAM "<TD ALIGN=LEFT ROWSPAN=2")
    (CL:COND
     ((EDITTING-ALLOWED?) (%%PRINT-STREAM STREAM " BGCOLOR='#FFCCCC'"))
     ((CURRENT-EDIT-LOCK?)
      (%%PRINT-STREAM STREAM " BGCOLOR='#FFFFCC'")))
    (%%PRINT-STREAM STREAM ">" EOL
     "<INPUT TYPE=\"radio\" NAME=\"LOCK\" VALUE=\"0\" onClick=\"location.pathname='/loom/edit-unlock.html'\"")
    (CL:WHEN (CL:NOT (EDITTING-ALLOWED?))
     (%%PRINT-STREAM STREAM " CHECKED"))
    (%%PRINT-STREAM STREAM ">Browse&nbsp;only<BR>" EOL
     "<INPUT TYPE=\"radio\" NAME=\"LOCK\" VALUE=\"1\" onClick=\"location.pathname='/loom/edit-lock.html'\"")
    (CL:WHEN (EDITTING-ALLOWED?) (%%PRINT-STREAM STREAM " CHECKED"))
    (%%PRINT-STREAM STREAM
     ">Make&nbsp;Changes<BR>&nbsp;&nbsp;(Others&nbsp;blocked)
</TD></TR>"))
   (%%PRINT-STREAM STREAM "<TD ALIGN=CENTER ROWSPAN=2 VALIGN=CENTER>"
    EOL
    "<A HREF=\"http://www.isi.edu/isd/LOOM/PowerLoom/\" TARGET=\"manual\" onMouseOver=\"window.status='Goes to the PowerLoom Home Page'; return true\"><img src=\"/ploom/icons/powerloom-logo-small.gif\" BORDER=0 WIDTH=40 HEIGHT=38></A>"
    EOL "</TD>" EOL "</TR>" EOL))
  (%%PRINT-STREAM STREAM "<TR><TD ALIGN=CENTER ROWSPAN=1>" EOL
   "<A HREF='" *POWERLOOM-REFERENCE-MANUAL-URL*
   "' TARGET=\"manual\" onMouseOver=\"window.status='PowerLoom Reference Manual' ; return true\">"
   EOL
   "<IMG SRC=\"/ploom/icons/book-small.gif\" BORDER=0 WIDTH=21 HEIGHT=11></a></TD>"
   EOL "<TD ALIGN=JUSTIFY ROWSPAN=1 COLSPAN=2>" EOL)
  (%%PRINT-STREAM STREAM EOL EOL "<SELECT NAME=\"objecttype\">" EOL
   "<option VALUE=\"object\" SELECTED>any</option>" EOL
   "<option VALUE=\"concept\">"
   (LOOKUP-TERM KWD-TOP-WINDOW-CONCEPT CL:NIL CL:NIL) "</option>" EOL
   "<option VALUE=\"relation\">"
   (LOOKUP-TERM KWD-TOP-WINDOW-RELATION CL:NIL CL:NIL) "</option>" EOL
   "<option VALUE=\"instance\">"
   (LOOKUP-TERM KWD-TOP-WINDOW-INSTANCE CL:NIL CL:NIL) "</option>" EOL
   "</SELECT>" EOL)
  (%%PRINT-STREAM STREAM EOL "<INPUT NAME=\"find\" SIZE=30 >" EOL EOL
   "<input TYPE=submit  NAME=\"dofind\" VALUE=\"Find\" onClick=\"loadURL('content', 'show', this.form)\">"
   EOL)
  (CL:WHEN (EDITTING-ALLOWED?)
   (%%PRINT-STREAM STREAM
    "<input TYPE=button  NAME= \"edit\" VALUE=\"Edit\" 
       onClick=\"loadURL('content', 'edit', this.form)\">
<input TYPE=button  NAME=\"new\" VALUE=\"New...\" 
       onClick=\"loadURL('content', 'new',this.form)\">
"))
  (%%PRINT-STREAM STREAM
   "  <img src=\"/ploom/icons/eighth-inch-space.gif\" ALT=\" \" WIDTH=9 HEIGHT=2>"
   EOL "Match&nbsp;<SELECT NAME=\"matchtype\">" EOL
   "<option VALUE=\"exact\">Exactly</option>" EOL
   "<option VALUE=\"caseInsensitive\">Case Insensitive</option>" EOL
   "<option VALUE=\"substring\" SELECTED>Substring</option>" EOL
   "</SELECT>" EOL)
  (%%PRINT-STREAM STREAM "
</TD></TR></TABLE>
</FORM>")
  (%%PRINT-STREAM STREAM "<SCRIPT LANGUAGE='JavaScript'>" EOL)
  (%%PRINT-STREAM STREAM
   "var cookieValue = document.cookie.substring(document.cookie.indexOf('theory=')+7,document.cookie.length);"
   EOL)
  (%%PRINT-STREAM STREAM "if (cookieValue.indexOf(';') != -1) {" EOL)
  (%%PRINT-STREAM STREAM
   "cookieValue = cookieValue.substring(0,cookieValue.indexOf(';'));"
   EOL)
  (%%PRINT-STREAM STREAM "}" EOL)
  (%%PRINT-STREAM STREAM
   "for (var i = 0; i < document.navform.theory.length; i++) {" EOL)
  (%%PRINT-STREAM STREAM
   "   if (document.navform.theory[i].value==cookieValue) {" EOL)
  (%%PRINT-STREAM STREAM
   "     document.navform.theory.selectedIndex = i; }" EOL)
  (%%PRINT-STREAM STREAM "}</SCRIPT>" EOL EOL)
  NULL)

;;; (DEFUN SERVE-CONTROL-PANEL-NEEDS-JAVASCRIPT ...)

(CL:DEFUN SERVE-CONTROL-PANEL-NEEDS-JAVASCRIPT (STREAM)
  (CL:PROGN (%%PRINT-STREAM STREAM "<HTML>")
   (%%PRINT-STREAM STREAM EOL)
   (CL:PROGN (%%PRINT-STREAM STREAM "<HEAD>")
    (%%PRINT-STREAM STREAM EOL)
    (CL:PROGN (%%PRINT-STREAM STREAM "<TITLE>")
     (%%PRINT-STREAM STREAM "Loom Browser No Javascript")
     (%%PRINT-STREAM STREAM "</TITLE>" EOL))
    (%%PRINT-STREAM STREAM "</HEAD>" EOL))
   (CL:LET*
    ((TAG-010
      (CONCATENATE "BODY BGCOLOR='#" *ERROR-BACKGROUND-COLOR* "'")))
    (CL:DECLARE (CL:TYPE CL:SIMPLE-STRING TAG-010))
    (%%PRINT-STREAM STREAM "<" TAG-010 ">")
    (CL:PROGN (%%PRINT-STREAM STREAM "<B>")
     (CL:PROGN (%%PRINT-STREAM STREAM "<FONT SIZE=6>")
      (%%PRINT-STREAM STREAM
       "I'm sorry, but a Javascript enabled browser is needed to use this site."
       EOL)
      (%%PRINT-STREAM STREAM "</FONT>" EOL))
     (CL:PROGN (%%PRINT-STREAM STREAM "<P>")
      (CL:PROGN (%%PRINT-STREAM STREAM "<FONT SIZE=4>")
       (%%PRINT-STREAM STREAM
        "If your browser supports Javascript, then you may need to go into the options section and turn on Javascript.  Then reload this location.")
       (%%PRINT-STREAM STREAM "</FONT>"))
      (%%PRINT-STREAM STREAM "</P>" EOL))
     (%%PRINT-STREAM STREAM "</B>" EOL))
    (%%PRINT-STREAM STREAM "</"
     (SUBSEQUENCE TAG-010 0 (POSITION TAG-010 #\  0)) ">" EOL))
   (%%PRINT-STREAM STREAM "</HTML>" EOL)))

;;; (DEFUN CONTROL-PANEL-HANDLER ...)

(CL:DEFUN CONTROL-PANEL-HANDLER (XCHG)
  (CL:LET* ((STREAM (GET-REPLY-STREAM XCHG)))
   (CL:COND
    ((CL:EQ (GET-REQUEST-METHOD XCHG) KWD-TOP-WINDOW-GET)
     (SERVE-CONTROL-PANEL-INTERNAL STREAM))
    (CL:T (SERVE-CONTROL-PANEL-NEEDS-JAVASCRIPT STREAM)))))

(CL:DEFUN STARTUP-TOP-WINDOW ()
  (CL:LET*
   ((*MODULE*
     (GET-STELLA-MODULE "/ONTOSAURUS" (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
    (CL:SETQ SYM-TOP-WINDOW-STELLA-CODE-ONLY?
     (INTERN-RIGID-SYMBOL-WRT-MODULE "CODE-ONLY?"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0))
    (CL:SETQ SYM-TOP-WINDOW-STELLA-NAMESPACE?
     (INTERN-RIGID-SYMBOL-WRT-MODULE "NAMESPACE?"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0))
    (CL:SETQ KWD-TOP-WINDOW-CONTEXT
     (INTERN-RIGID-SYMBOL-WRT-MODULE "CONTEXT" NULL 2))
    (CL:SETQ KWD-TOP-WINDOW-CONCEPT
     (INTERN-RIGID-SYMBOL-WRT-MODULE "CONCEPT" NULL 2))
    (CL:SETQ KWD-TOP-WINDOW-RELATION
     (INTERN-RIGID-SYMBOL-WRT-MODULE "RELATION" NULL 2))
    (CL:SETQ KWD-TOP-WINDOW-INSTANCE
     (INTERN-RIGID-SYMBOL-WRT-MODULE "INSTANCE" NULL 2))
    (CL:SETQ KWD-TOP-WINDOW-GET
     (INTERN-RIGID-SYMBOL-WRT-MODULE "GET" NULL 2))
    (CL:SETQ KWD-TOP-WINDOW-CONTENT-TYPE
     (INTERN-RIGID-SYMBOL-WRT-MODULE "CONTENT-TYPE" NULL 2))
    (CL:SETQ KWD-TOP-WINDOW-HTML
     (INTERN-RIGID-SYMBOL-WRT-MODULE "HTML" NULL 2))
    (CL:SETQ KWD-TOP-WINDOW-DOCUMENTATION
     (INTERN-RIGID-SYMBOL-WRT-MODULE "DOCUMENTATION" NULL 2))
    (CL:SETQ SYM-TOP-WINDOW-ONTOSAURUS-STARTUP-TOP-WINDOW
     (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-TOP-WINDOW" NULL 0))
    (CL:SETQ SYM-TOP-WINDOW-STELLA-METHOD-STARTUP-CLASSNAME
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
    (DEFINE-FUNCTION-OBJECT "SAVING-ALLOWED?"
     "(DEFUN (SAVING-ALLOWED? BOOLEAN) ())"
     (CL:FUNCTION SAVING-ALLOWED?) NULL)
    (DEFINE-FUNCTION-OBJECT "LOADING-ALLOWED?"
     "(DEFUN (LOADING-ALLOWED? BOOLEAN) ())"
     (CL:FUNCTION LOADING-ALLOWED?) NULL)
    (DEFINE-FUNCTION-OBJECT "EDITTING-ALLOWED?"
     "(DEFUN (EDITTING-ALLOWED? BOOLEAN) ())"
     (CL:FUNCTION EDITTING-ALLOWED?) NULL)
    (DEFINE-FUNCTION-OBJECT "EDITTING-POSSIBLE?"
     "(DEFUN (EDITTING-POSSIBLE? BOOLEAN) ())"
     (CL:FUNCTION EDITTING-POSSIBLE?) NULL)
    (DEFINE-FUNCTION-OBJECT "CURRENT-EDIT-LOCK?"
     "(DEFUN (CURRENT-EDIT-LOCK? BOOLEAN) ())"
     (CL:FUNCTION CURRENT-EDIT-LOCK?) NULL)
    (DEFINE-FUNCTION-OBJECT "SORTED-CONTEXTS"
     "(DEFUN (SORTED-CONTEXTS (CONS OF STRING-WRAPPER)) ())"
     (CL:FUNCTION SORTED-CONTEXTS) NULL)
    (DEFINE-FUNCTION-OBJECT "SERVE-CONTROL-PANEL-INTERNAL"
     "(DEFUN SERVE-CONTROL-PANEL-INTERNAL ((STREAM NATIVE-OUTPUT-STREAM)))"
     (CL:FUNCTION SERVE-CONTROL-PANEL-INTERNAL) NULL)
    (DEFINE-FUNCTION-OBJECT "WRITE-THEORY-SECTION"
     "(DEFUN WRITE-THEORY-SECTION ((STREAM NATIVE-OUTPUT-STREAM)))"
     (CL:FUNCTION WRITE-THEORY-SECTION) NULL)
    (DEFINE-FUNCTION-OBJECT "WRITE-TOP-SECTION"
     "(DEFUN WRITE-TOP-SECTION ((STREAM NATIVE-OUTPUT-STREAM)))"
     (CL:FUNCTION WRITE-TOP-SECTION) NULL)
    (DEFINE-FUNCTION-OBJECT "WRITE-BOTTOM-SECTION"
     "(DEFUN WRITE-BOTTOM-SECTION ((STREAM NATIVE-OUTPUT-STREAM)))"
     (CL:FUNCTION WRITE-BOTTOM-SECTION) NULL)
    (DEFINE-FUNCTION-OBJECT "SERVE-CONTROL-PANEL-NEEDS-JAVASCRIPT"
     "(DEFUN SERVE-CONTROL-PANEL-NEEDS-JAVASCRIPT ((STREAM NATIVE-OUTPUT-STREAM)))"
     (CL:FUNCTION SERVE-CONTROL-PANEL-NEEDS-JAVASCRIPT) NULL)
    (DEFINE-FUNCTION-OBJECT "CONTROL-PANEL-HANDLER"
     "(DEFUN CONTROL-PANEL-HANDLER ((XCHG /HTTP/HTTP-EXCHANGE)))"
     (CL:FUNCTION CONTROL-PANEL-HANDLER) NULL)
    (DEFINE-FUNCTION-OBJECT "STARTUP-TOP-WINDOW"
     "(DEFUN STARTUP-TOP-WINDOW () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-TOP-WINDOW) NULL)
    (CL:LET*
     ((FUNCTION
       (LOOKUP-FUNCTION SYM-TOP-WINDOW-ONTOSAURUS-STARTUP-TOP-WINDOW)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-TOP-WINDOW-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupTopWindow") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "ONTOSAURUS")))
    (DEFINE-GLOBAL-VARIABLE-OBJECT
     "(DEFGLOBAL *POWERLOOM-REFERENCE-MANUAL-URL* STRING \"http://www.isi.edu/isd/LOOM/PowerLoom/documentation/manual/manual_frame.html\")"
     NULL)
    (PUBLISH-HANDLER "/ploom/ontosaurus/top-window.html"
     (CL:FUNCTION CONTROL-PANEL-HANDLER) KWD-TOP-WINDOW-CONTENT-TYPE
     (WRAP-STRING (GET-HTTP-MIME-TYPE KWD-TOP-WINDOW-HTML NULL))
     KWD-TOP-WINDOW-DOCUMENTATION
     (WRAP-STRING "Ontosaurus control-panel handler.")))))
