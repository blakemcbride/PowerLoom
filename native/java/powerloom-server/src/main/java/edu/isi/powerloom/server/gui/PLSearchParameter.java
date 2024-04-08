//  -*- Mode: Java -*-
//
// PLSearchParameter.java

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

public class PLSearchParameter extends XMLObject {
    public String ModuleName;
    public String SearchString;
    public String SearchConcept;
    public String SearchRelation;
    public String SearchInstance;
    public String CaseSensitive;

  public static PLSearchParameter new_PLSearchParameter() {
    { PLSearchParameter self = null;

      self = new PLSearchParameter();
      self.cdataContent = null;
      self.textContent = null;
      self.CaseSensitive = null;
      self.SearchInstance = null;
      self.SearchRelation = null;
      self.SearchConcept = null;
      self.SearchString = null;
      self.ModuleName = null;
      return (self);
    }
  }

  public static PLSearchResult serverSearch(PLSearchParameter searchparameter) {
    { String modulename = searchparameter.ModuleName;
      String searchstring = searchparameter.SearchString;
      String searchconceptP = searchparameter.SearchConcept;
      String searchrelationP = searchparameter.SearchRelation;
      String searchinstanceP = searchparameter.SearchInstance;
      String casesensitiveP = searchparameter.CaseSensitive;
      PLSearchResult result = PLSearchResult.new_PLSearchResult();
      List searchresults = List.newList();

      if (Stella.stringEqlP(modulename, "ALL")) {
        searchresults = GuiServer.searchAllModules(searchstring, searchinstanceP, searchconceptP, searchrelationP, casesensitiveP);
      }
      else {
        searchresults = GuiServer.searchModule(modulename, searchstring, searchinstanceP, searchconceptP, searchrelationP, casesensitiveP);
      }
      result.PLSearchResultItem = searchresults;
      return (result);
    }
  }

  public static Stella_Object access_PLSearchParameter_Slot_Value(PLSearchParameter self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == GuiServer.SYM_GUI_SERVER_ModuleName) {
      if (setvalueP) {
        self.ModuleName = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.ModuleName);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_SearchString) {
      if (setvalueP) {
        self.SearchString = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.SearchString);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_SearchConcept) {
      if (setvalueP) {
        self.SearchConcept = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.SearchConcept);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_SearchRelation) {
      if (setvalueP) {
        self.SearchRelation = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.SearchRelation);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_SearchInstance) {
      if (setvalueP) {
        self.SearchInstance = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.SearchInstance);
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
    else {
      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

        stream000.nativeStream.print("`" + slotname + "' is not a valid case option");
        throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
      }
    }
    return (value);
  }

  public Surrogate primaryType() {
    { PLSearchParameter self = this;

      return (GuiServer.SGT_GUI_SERVER_PLSearchParameter);
    }
  }

}

