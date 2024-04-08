//  -*- Mode: Java -*-
//
// ShellProcess.java

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

public class ShellProcess extends StandardObject {
    public String[] command;
    public String directory;
    public java.lang.Process nativeProcess;
    public InputStream inputStream;
    public OutputStream nativeStdin;
    public OutputStream outputStream;
    public InputStream nativeStdout;
    public OutputStream errorStream;
    public InputStream nativeStderr;
    public int exitStatus;

  public static ShellProcess newShellProcess() {
    { ShellProcess self = null;

      self = new ShellProcess();
      self.exitStatus = Stella.NULL_INTEGER;
      self.nativeStderr = null;
      self.errorStream = null;
      self.nativeStdout = null;
      self.outputStream = null;
      self.nativeStdin = null;
      self.inputStream = null;
      self.nativeProcess = null;
      self.directory = ".";
      self.command = null;
      return (self);
    }
  }

  /** Stop <code>self</code> and then destroy the associated process object.
   * In Lisp, this doesn't yet actually kill the shell process, it just waits for its
   * completion.  Conceivably, we could execute a <code>kill</code> command to achieve that.
   */
  public void destroyProcess() {
    { ShellProcess self = this;

      { java.lang.Process process = self.nativeProcess;

        process.destroy();
        if (self.nativeStdin != null) {
          OutputStream.terminateOutputStreamP(self.nativeStdin);
        }
        if (self.nativeStdout != null) {
          InputStream.terminateInputStreamP(self.nativeStdout);
          self.nativeStdout.tokenizerState = null;
        }
        if (self.nativeStderr != null) {
          InputStream.terminateInputStreamP(self.nativeStderr);
          self.nativeStderr.tokenizerState = null;
        }
        self.nativeProcess = null;
      }
    }
  }

  /** Suspend the current thread until <code>self</code> has completed execution.
   */
  public void waitForCompletion() {
    { ShellProcess self = this;

      { java.lang.Process process = self.nativeProcess;
        int exit = Stella.NULL_INTEGER;

        try {
          exit = process.waitFor();
        } catch (InterruptedException e) {
          Native.rethrowAsStellaException(e, StellaException.class, "waitForCompletion: ", true);
        }
;
        self.exitStatus = exit;
      }
    }
  }

  /** Start execution of <code>self</code>s <code>command</code>.
   */
  public void startProcess() {
    { ShellProcess self = this;

      { java.lang.Process process = null;
        String[] command = self.command;
        String directory = self.directory;
        InputStream input = self.inputStream;
        OutputStream output = self.outputStream;
        OutputStream error = self.errorStream;
        edu.isi.stella.javalib.NativeOutputStream stdin = null;
        edu.isi.stella.javalib.NativeInputStream stdout = null;
        edu.isi.stella.javalib.NativeInputStream stderr = null;

        try {
         process = Runtime.getRuntime().exec(command, null, new java.io.File(directory));
         if (input != null)
            stdin = edu.isi.stella.javalib.NativeOutputStream.create(process.getOutputStream());
         if (output != null)
            stdout = edu.isi.stella.javalib.NativeInputStream.create
                        (new edu.isi.stella.javalib.FlushableBufferedInputStream(process.getInputStream()));
         if (error != null)
            stderr = edu.isi.stella.javalib.NativeInputStream.create
                        (new edu.isi.stella.javalib.FlushableBufferedInputStream(process.getErrorStream()));
       }
       catch (java.io.IOException e) {
          Native.rethrowAsStellaException(e, InputOutputException.class, "ShellProcess.startProcess: ", true);
       }
;
        if (process == null) {
          throw ((StellaException)(StellaException.newStellaException("shell-process.start-process: not yet implemented").fillInStackTrace()));
        }
        self.nativeProcess = process;
        if (stdin != null) {
          { OutputStream self001 = OutputStream.newOutputStream();

            self001.nativeStream = stdin;
            self.nativeStdin = self001;
          }
        }
        if (stdout != null) {
          { InputStream self002 = InputStream.newInputStream();

            self002.nativeStream = stdout;
            self002.bufferingScheme = OntosaurusUtil.KWD_BLOCK;
            self.nativeStdout = self002;
          }
        }
        if (stderr != null) {
          { InputStream self003 = InputStream.newInputStream();

            self003.nativeStream = stderr;
            self003.bufferingScheme = OntosaurusUtil.KWD_BLOCK;
            self.nativeStderr = self003;
          }
        }
      }
    }
  }

  public static Stella_Object accessShellProcessSlotValue(ShellProcess self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == OntosaurusUtil.SYM_STELLA_DIRECTORY) {
      if (setvalueP) {
        self.directory = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.directory);
      }
    }
    else if (slotname == OntosaurusUtil.SYM_STELLA_INPUT_STREAM) {
      if (setvalueP) {
        self.inputStream = ((InputStream)(value));
      }
      else {
        value = self.inputStream;
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_NATIVE_STDIN) {
      if (setvalueP) {
        self.nativeStdin = ((OutputStream)(value));
      }
      else {
        value = self.nativeStdin;
      }
    }
    else if (slotname == OntosaurusUtil.SYM_STELLA_OUTPUT_STREAM) {
      if (setvalueP) {
        self.outputStream = ((OutputStream)(value));
      }
      else {
        value = self.outputStream;
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_NATIVE_STDOUT) {
      if (setvalueP) {
        self.nativeStdout = ((InputStream)(value));
      }
      else {
        value = self.nativeStdout;
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_ERROR_STREAM) {
      if (setvalueP) {
        self.errorStream = ((OutputStream)(value));
      }
      else {
        value = self.errorStream;
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_NATIVE_STDERR) {
      if (setvalueP) {
        self.nativeStderr = ((InputStream)(value));
      }
      else {
        value = self.nativeStderr;
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_EXIT_STATUS) {
      if (setvalueP) {
        self.exitStatus = ((IntegerWrapper)(value)).wrapperValue;
      }
      else {
        value = IntegerWrapper.wrapInteger(self.exitStatus);
      }
    }
    else {
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("`" + slotname + "' is not a valid case option");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
    return (value);
  }

  public Surrogate primaryType() {
    { ShellProcess self = this;

      return (OntosaurusUtil.SGT_ONTOSAURUS_SHELL_PROCESS);
    }
  }

}

