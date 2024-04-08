//  -*- Mode: Java -*-
//
// Thread.java

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

public class Thread extends StandardObject {
    public java.lang.Thread nativeThread;
    public java.lang.reflect.Method runFunction;
    public Vector runArguments;

  public static Thread newThread(java.lang.reflect.Method runFunction, Vector runArguments) {
    { Thread self = null;

      self = new Thread();
      self.runFunction = runFunction;
      self.runArguments = runArguments;
      self.nativeThread = null;
      self.initializeThread();
      return (self);
    }
  }

  /** Suspend the current thread until <code>self</code> has completed execution.
   */
  public void waitForCompletion() {
    { Thread self = this;

      { java.lang.Thread thread = self.nativeThread;

        try {
         thread.join();
       } catch (InterruptedException e) {
         Native.rethrowAsStellaException(e, StellaException.class, "waitForCompletion: ", true);
       }
;
      }
    }
  }

  /** Stop <code>self</code> and then destroy the associated thread object.
   */
  public void killThread() {
    { Thread self = this;

      { java.lang.Thread thread = self.nativeThread;

        self.stopThread();
        thread.destroy();
        self.nativeThread = null;
      }
    }
  }

  /** Stop execution of <code>self</code>s run-function.
   */
  public void stopThread() {
    { Thread self = this;

      { java.lang.Thread thread = self.nativeThread;

        thread.stop();
      }
    }
  }

  /** Start execution of <code>self</code>s run-function.
   */
  public void startThread() {
    { Thread self = this;

      { java.lang.Thread thread = self.nativeThread;

        thread.start();
      }
    }
  }

  public static void javaInitializeThread(Thread self) {
    { String name = Stella.yieldUniqueGensymName("STELLA-THREAD", null);
      java.lang.Thread thread = null;
      java.lang.reflect.Method function = self.runFunction;

      { Vector temp000 = self.runArguments;

        { Vector arguments = ((temp000 != null) ? temp000 : Stella.vector(Stella.NIL));
          edu.isi.stella.Stella_Object[] natargs = arguments.theArray;

          final java.lang.reflect.Method fn = function;
            final java.lang.Object[] args = natargs;
            thread = new java.lang.Thread(name) {
               public void run() {
                 Native.funcall(fn, null, args);
               }
            }
;
          self.nativeThread = thread;
        }
      }
    }
  }

  public static void clInitializeThread(Thread self) {
    { String name = Stella.yieldUniqueGensymName("STELLA-THREAD", null);
      java.lang.Thread thread = null;
      java.lang.reflect.Method function = self.runFunction;
      Cons arguments = Stella.NIL;

      if (thread == null) {
        throw ((StellaException)(StellaException.newStellaException("initialize-thread: threads not yet supported in this Lisp dialect").fillInStackTrace()));
      }
      self.nativeThread = thread;
      if (self.runArguments != null) {
        arguments = self.runArguments.consify();
      }
    }
  }

  public void initializeThread() {
    { Thread self = this;

      if (self.runFunction == null) {
        throw ((StellaException)(StellaException.newStellaException("initialize-thread: run-function not defined").fillInStackTrace()));
      }
      Thread.javaInitializeThread(self);
    }
  }

  public static Stella_Object accessThreadSlotValue(Thread self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_RUN_FUNCTION) {
      if (setvalueP) {
        self.runFunction = ((FunctionCodeWrapper)(value)).wrapperValue;
      }
      else {
        value = FunctionCodeWrapper.wrapFunctionCode(self.runFunction);
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_RUN_ARGUMENTS) {
      if (setvalueP) {
        self.runArguments = ((Vector)(value));
      }
      else {
        value = self.runArguments;
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
    { Thread self = this;

      return (OntosaurusUtil.SGT_ONTOSAURUS_THREAD);
    }
  }

}

