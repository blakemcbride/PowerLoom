//  -*- Mode: Java -*-
//
// _StartupShell.java

/*
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
*/

package edu.isi.ontosaurus;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.powerloom.logic.*;
import edu.isi.stella.*;

public class _StartupShell {
  public static void startupShell() {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/ONTOSAURUS", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          OntosaurusUtil.SGT_ONTOSAURUS_THREAD = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("THREAD", null, 1)));
          OntosaurusUtil.SYM_ONTOSAURUS_RUN_FUNCTION = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("RUN-FUNCTION", null, 0)));
          OntosaurusUtil.SYM_ONTOSAURUS_RUN_ARGUMENTS = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("RUN-ARGUMENTS", null, 0)));
          OntosaurusUtil.SGT_ONTOSAURUS_SHELL_PROCESS = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("SHELL-PROCESS", null, 1)));
          OntosaurusUtil.SYM_STELLA_DIRECTORY = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("DIRECTORY", Stella.getStellaModule("/STELLA", true), 0)));
          OntosaurusUtil.SYM_STELLA_INPUT_STREAM = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("INPUT-STREAM", Stella.getStellaModule("/STELLA", true), 0)));
          OntosaurusUtil.SYM_ONTOSAURUS_NATIVE_STDIN = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("NATIVE-STDIN", null, 0)));
          OntosaurusUtil.SYM_STELLA_OUTPUT_STREAM = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("OUTPUT-STREAM", Stella.getStellaModule("/STELLA", true), 0)));
          OntosaurusUtil.SYM_ONTOSAURUS_NATIVE_STDOUT = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("NATIVE-STDOUT", null, 0)));
          OntosaurusUtil.SYM_ONTOSAURUS_ERROR_STREAM = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("ERROR-STREAM", null, 0)));
          OntosaurusUtil.SYM_ONTOSAURUS_NATIVE_STDERR = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("NATIVE-STDERR", null, 0)));
          OntosaurusUtil.SYM_ONTOSAURUS_EXIT_STATUS = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("EXIT-STATUS", null, 0)));
          OntosaurusUtil.KWD_BLOCK = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("BLOCK", null, 2)));
          OntosaurusUtil.KWD_DIRECTORY = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("DIRECTORY", null, 2)));
          OntosaurusUtil.SGT_STELLA_STRING = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("STRING", Stella.getStellaModule("/STELLA", true), 1)));
          OntosaurusUtil.KWD_IGNORE_ERRORSp = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("IGNORE-ERRORS?", null, 2)));
          OntosaurusUtil.SGT_STELLA_BOOLEAN = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("BOOLEAN", Stella.getStellaModule("/STELLA", true), 1)));
          OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_SHELL = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-SHELL", null, 0)));
        }
        if (Stella.currentStartupTimePhaseP(4)) {
          OntosaurusUtil.$BLOCK_SHELL_COMMANDp$.setDefaultValue(new Boolean(false));
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          Stella.defineClassFromStringifiedSource("NATIVE-THREAD", "(DEFCLASS NATIVE-THREAD () :CL-NATIVE-TYPE \"#+allegro MP:PROCESS #-allegro CL:T\" :JAVA-NATIVE-TYPE \"java.lang.Thread\")");
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("THREAD", "(DEFCLASS THREAD (STANDARD-OBJECT) :SLOTS ((NATIVE-THREAD :TYPE NATIVE-THREAD) (RUN-FUNCTION :TYPE FUNCTION-CODE :REQUIRED? TRUE) (RUN-ARGUMENTS :TYPE VECTOR :REQUIRED? TRUE)) :INITIALIZER INITIALIZE-THREAD)");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.ontosaurus.Thread", "newThread", new java.lang.Class [] {Native.find_java_class("java.lang.reflect.Method"), Native.find_java_class("edu.isi.stella.Vector")});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.ontosaurus.Thread", "accessThreadSlotValue", new java.lang.Class [] {Native.find_java_class("edu.isi.ontosaurus.Thread"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          Stella.defineClassFromStringifiedSource("NATIVE-SHELL-PROCESS", "(DEFCLASS NATIVE-SHELL-PROCESS () :CL-NATIVE-TYPE \"INTEGER\" :JAVA-NATIVE-TYPE \"java.lang.Process\")");
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("SHELL-PROCESS", "(DEFCLASS SHELL-PROCESS (STANDARD-OBJECT) :SLOTS ((COMMAND :TYPE (ARRAY () OF STRING)) (DIRECTORY :TYPE STRING :INITIALLY \".\") (NATIVE-PROCESS :TYPE NATIVE-SHELL-PROCESS) (INPUT-STREAM :TYPE INPUT-STREAM) (NATIVE-STDIN :TYPE OUTPUT-STREAM) (OUTPUT-STREAM :TYPE OUTPUT-STREAM) (NATIVE-STDOUT :TYPE INPUT-STREAM) (ERROR-STREAM :TYPE OUTPUT-STREAM) (NATIVE-STDERR :TYPE INPUT-STREAM) (EXIT-STATUS :TYPE INTEGER :INITIALLY NULL)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.ontosaurus.ShellProcess", "newShellProcess", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.ontosaurus.ShellProcess", "accessShellProcessSlotValue", new java.lang.Class [] {Native.find_java_class("edu.isi.ontosaurus.ShellProcess"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineMethodObject("(DEFMETHOD INITIALIZE-THREAD ((SELF THREAD)))", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.Thread", "initializeThread", new java.lang.Class [] {})), null);
          Stella.defineFunctionObject("CL-INITIALIZE-THREAD", "(DEFUN CL-INITIALIZE-THREAD ((SELF THREAD)))", Native.find_java_method("edu.isi.ontosaurus.Thread", "clInitializeThread", new java.lang.Class [] {Native.find_java_class("edu.isi.ontosaurus.Thread")}), null);
          Stella.defineFunctionObject("JAVA-INITIALIZE-THREAD", "(DEFUN JAVA-INITIALIZE-THREAD ((SELF THREAD)))", Native.find_java_method("edu.isi.ontosaurus.Thread", "javaInitializeThread", new java.lang.Class [] {Native.find_java_class("edu.isi.ontosaurus.Thread")}), null);
          Stella.defineMethodObject("(DEFMETHOD START-THREAD ((SELF THREAD)) :DOCUMENTATION \"Start execution of `self's run-function.\" :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.Thread", "startThread", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD STOP-THREAD ((SELF THREAD)) :DOCUMENTATION \"Stop execution of `self's run-function.\" :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.Thread", "stopThread", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD KILL-THREAD ((SELF THREAD)) :DOCUMENTATION \"Stop `self' and then destroy the associated thread object.\" :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.Thread", "killThread", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD WAIT-FOR-COMPLETION ((SELF THREAD)) :DOCUMENTATION \"Suspend the current thread until `self' has completed execution.\" :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.Thread", "waitForCompletion", new java.lang.Class [] {})), null);
          Stella.defineFunctionObject("PARSE-SHELL-COMMAND", "(DEFUN (PARSE-SHELL-COMMAND (ARRAY () OF STRING)) ((COMMAND OBJECT)))", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "parseShellCommand", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object")}), null);
          Stella.defineMethodObject("(DEFMETHOD START-PROCESS ((SELF SHELL-PROCESS)) :DOCUMENTATION \"Start execution of `self's `command'.\")", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.ShellProcess", "startProcess", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD WAIT-FOR-COMPLETION ((SELF SHELL-PROCESS)) :DOCUMENTATION \"Suspend the current thread until `self' has completed execution.\" :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.ShellProcess", "waitForCompletion", new java.lang.Class [] {})), null);
          Stella.defineMethodObject("(DEFMETHOD DESTROY-PROCESS ((SELF SHELL-PROCESS)) :DOCUMENTATION \"Stop `self' and then destroy the associated process object.\nIn Lisp, this doesn't yet actually kill the shell process, it just waits for its\ncompletion.  Conceivably, we could execute a `kill' command to achieve that.\" :PUBLIC? TRUE)", MethodCodeWrapper.wrapMethodCode(Native.find_java_method("edu.isi.ontosaurus.ShellProcess", "destroyProcess", new java.lang.Class [] {})), null);
          Stella.defineFunctionObject("EXECUTE-SHELL-COMMAND", "(DEFUN (EXECUTE-SHELL-COMMAND INTEGER) ((COMMAND OBJECT) (DIRECTORY STRING) (INPUT INPUT-STREAM) (OUTPUT OUTPUT-STREAM) (ERROR OUTPUT-STREAM)) :DOCUMENTATION \"Run `command' in a shell and return its exit status.  If `directory' is\nnon-NULL, run it in that directory; if `input' is defined, feed `command's standard input\nfrom that stream; if `output' and/or `error' are defined, copy `commands' standard output/\nerror to those streams.  It is the responsibility of the caller to close the supplied\nstreams (if any) and do any shell error handling based on exit status or error output.\" :PUBLIC? TRUE)", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "executeShellCommand", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("java.lang.String"), Native.find_java_class("edu.isi.stella.InputStream"), Native.find_java_class("edu.isi.stella.OutputStream"), Native.find_java_class("edu.isi.stella.OutputStream")}), null);
          Stella.defineFunctionObject("SHELL-COMMAND", "(DEFUN (SHELL-COMMAND STRING-WRAPPER) ((COMMAND OBJECT) |&REST| (OPTIONS OBJECT)) :DOCUMENTATION \"User-level command interface to `execute-shell-command' (which see).\nRuns `command' and returns its output (if any) as a string.  If the shell created\na non-zero exit status or generated any error output, an exception will be raised\n- unless :ignore-errors? is true (which is the default).\nIf `command' was a string, split it at spaces to determine its arguments (this is\nnot sophisticated and does not handle quoting correctly).  For more complex commands,\nsupply them as a list of strings representing the program and its arguments.  If any\nshell-level operations such as redirection are needed, use the `sh -c cmd' idiom.\nIf :input is supplied as a non-null string, feed it to `command's standard input.\nIf :directory is given, execute `command' in that directory.\" :COMMAND? TRUE :PUBLIC? TRUE)", Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "shellCommand", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.Cons")}), Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "shellCommandEvaluatorWrapper", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Cons")}));
          Stella.defineFunctionObject("STARTUP-SHELL", "(DEFUN STARTUP-SHELL () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.ontosaurus._StartupShell", "startupShell", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(OntosaurusUtil.SYM_ONTOSAURUS_STARTUP_SHELL);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, OntosaurusUtil.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupShell"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("ONTOSAURUS")))));
          Stella.defineGlobalVariableObject("(DEFSPECIAL *BLOCK-SHELL-COMMAND?* BOOLEAN FALSE :DOCUMENTATION \"Allow disabling of `shell-command' in remote execution contexts\nfor security purposes.\")", null);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

}
