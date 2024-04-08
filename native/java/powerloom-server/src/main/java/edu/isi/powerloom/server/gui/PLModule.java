//  -*- Mode: Java -*-
//
// PLModule.java

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
 | Portions created by the Initial Developer are Copyright (C) 2002-2023      |
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

package edu.isi.powerloom.server.gui;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;
import edu.isi.powerloom.logic.*;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.webtools.soap.*;
import edu.isi.powerloom.server.*;

public class PLModule extends XMLObject {
    public String ModuleName;
    public String SourceString;
    public String CppPackage;
    public String LispPackage;
    public String JavaPackage;
    public String JavaCatchallClass;
    public String Documentation;
    public String api;
    public String CaseSensitive;
    public List PLModule;
    public List PLSurrogate;

  public static PLModule new_PLModule() {
    { PLModule self = null;

      self = new PLModule();
      self.cdataContent = null;
      self.textContent = null;
      self.PLSurrogate = null;
      self.PLModule = null;
      self.CaseSensitive = null;
      self.api = null;
      self.Documentation = null;
      self.JavaCatchallClass = null;
      self.JavaPackage = null;
      self.LispPackage = null;
      self.CppPackage = null;
      self.SourceString = null;
      self.ModuleName = null;
      return (self);
    }
  }

  public static PLString serverClearKb(PLModule module) {
    { String modname = module.ModuleName;
      PLString result = PLString.new_PLString();

      edu.isi.powerloom.PLI.sClearModule(modname, null);
      result.Value = "OK";
      return (result);
    }
  }

  public static boolean PLModuleL(PLModule inst1, PLModule inst2) {
    return (Stella.stringL(inst1.ModuleName, inst2.ModuleName));
  }

  public static Stella_Object access_PLModule_Slot_Value(PLModule self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == GuiServer.SYM_GUI_SERVER_ModuleName) {
      if (setvalueP) {
        self.ModuleName = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.ModuleName);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_SourceString) {
      if (setvalueP) {
        self.SourceString = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.SourceString);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_CppPackage) {
      if (setvalueP) {
        self.CppPackage = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.CppPackage);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_LispPackage) {
      if (setvalueP) {
        self.LispPackage = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.LispPackage);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_JavaPackage) {
      if (setvalueP) {
        self.JavaPackage = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.JavaPackage);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_JavaCatchallClass) {
      if (setvalueP) {
        self.JavaCatchallClass = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.JavaCatchallClass);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_Documentation) {
      if (setvalueP) {
        self.Documentation = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.Documentation);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_API) {
      if (setvalueP) {
        self.api = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.api);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_CaseSensitive) {
      if (setvalueP) {
        self.CaseSensitive = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.CaseSensitive);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_PLModule) {
      if (setvalueP) {
        self.PLModule = ((List)(value));
      }
      else {
        value = self.PLModule;
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_PLSurrogate) {
      if (setvalueP) {
        self.PLSurrogate = ((List)(value));
      }
      else {
        value = self.PLSurrogate;
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
    { PLModule self = this;

      return (GuiServer.SGT_GUI_SERVER_PLModule);
    }
  }

}

