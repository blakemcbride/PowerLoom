//  -*- Mode: Java -*-
//
// PLQuery.java

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

public class PLQuery extends XMLObject {
    public String IsAsk;
    public String QueryName;
    public String Query;
    public String Module;
    public String InferenceLevel;
    public String Timeout;
    public String Moveout;
    public String MatchMode;
    public String NumResults;
    public String MinScore;
    public String MaxUnknowns;
    public String MaximizeScore;
    public String DontOptimize;

  public static PLQuery new_PLQuery() {
    { PLQuery self = null;

      self = new PLQuery();
      self.cdataContent = null;
      self.textContent = null;
      self.DontOptimize = null;
      self.MaximizeScore = null;
      self.MaxUnknowns = null;
      self.MinScore = null;
      self.NumResults = null;
      self.MatchMode = null;
      self.Moveout = null;
      self.Timeout = null;
      self.InferenceLevel = null;
      self.Module = null;
      self.Query = null;
      self.QueryName = null;
      self.IsAsk = null;
      return (self);
    }
  }

  public static boolean isQueryPartialP(PLQuery plquery) {
    return ((plquery.MatchMode != null) &&
        (!Stella.stringEqlP(plquery.MatchMode, "STRICT")));
  }

  public static String createFollowupQueryString(PLQuery plquery) {
    { String result = "";
      String querybody = null;
      String commandclause = null;

      commandclause = "/LOGIC/RETRIEVE ";
      querybody = plquery.NumResults + "";
      result = "(" + commandclause + querybody + ")";
      return (result);
    }
  }

  public static String createQueryString(PLQuery plquery) {
    { String result = "";
      String querybody = null;
      String howmanyclause = "";
      String inferencelevelclause = "";
      String minscoreclause = "";
      String maxunknownsclause = "";
      String matchmodeclause = "";
      String timeoutclause = "";
      String commandclause = "";
      String moveoutclause = "";
      String maximizescoreclause = "";
      String dontoptimizeclause = "";

      if ((plquery.NumResults != null) &&
          (((plquery.NumResults).length() > 0) &&
           (!Stella.stringEqlP(plquery.NumResults, "ALL")))) {
        howmanyclause = " :HOW-MANY " + plquery.NumResults;
      }
      if ((plquery.Timeout != null) &&
          ((plquery.Timeout).length() > 0)) {
        timeoutclause = " :TIMEOUT " + plquery.Timeout;
      }
      if ((plquery.Moveout != null) &&
          ((plquery.Moveout).length() > 0)) {
        moveoutclause = " :MOVEOUT " + plquery.Moveout;
      }
      if ((plquery.MinScore != null) &&
          ((plquery.MinScore).length() > 0)) {
        minscoreclause = " :MINIMUM-SCORE " + plquery.MinScore;
      }
      if ((plquery.MaximizeScore != null) &&
          ((plquery.MaximizeScore).length() > 0)) {
        maximizescoreclause = " :MAXIMIZE-SCORE? " + plquery.MaximizeScore;
      }
      if ((plquery.DontOptimize != null) &&
          ((plquery.DontOptimize).length() > 0)) {
        dontoptimizeclause = " :DONT-OPTIMIZE? " + plquery.DontOptimize;
      }
      if ((plquery.MaxUnknowns != null) &&
          ((plquery.MaxUnknowns).length() > 0)) {
        maxunknownsclause = " :MAXIMUM-UNKNOWNS " + plquery.MaxUnknowns;
      }
      if ((plquery.MatchMode != null) &&
          ((plquery.MatchMode).length() > 0)) {
        matchmodeclause = " :MATCH-MODE :" + plquery.MatchMode;
      }
      if ((plquery.InferenceLevel != null) &&
          ((plquery.InferenceLevel).length() > 0)) {
        inferencelevelclause = " :INFERENCE-LEVEL :" + plquery.InferenceLevel;
      }
      if ((plquery.IsAsk != null) &&
          Stella.stringEqlP(plquery.IsAsk, "TRUE")) {
        commandclause = "/LOGIC/ASK ";
      }
      else {
        commandclause = "/LOGIC/RETRIEVE ";
      }
      querybody = plquery.NumResults + " " + plquery.Query;
      result = "(" + commandclause + querybody + howmanyclause + timeoutclause + moveoutclause + minscoreclause + maximizescoreclause + dontoptimizeclause + maxunknownsclause + matchmodeclause + inferencelevelclause + ")";
      return (result);
    }
  }

  public static PLString serverGetExplanationForQuery(PLQuery query, PLString resultnumber) {
    { edu.isi.webtools.http.Session session = PLQuery.getQuerySession(query, true);
      Stella_Object queryiterator = session.lookup(StringWrapper.wrapString("QueryIterator"));
      long solutionindex = Native.stringToInteger(resultnumber.Value) - 1;
      List justifications = null;
      String explanation = "No explanation available.";
      PLString result = PLString.new_PLString();
      String modulename = query.Module;
      Module module = edu.isi.powerloom.PLI.getModule(modulename, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          justifications = QueryIterator.getQueryJustifications(((QueryIterator)(queryiterator)), ((int)(solutionindex)), Stella.NULL_INTEGER, true);
          if (justifications.length() > 0) {
            explanation = GuiServer.getJustificationString(((Justification)(justifications.first())));
          }
          result.Value = explanation;
          return (result);

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  public static PLQueryResult serverQuery(PLQuery plquery, PLString continuequeryP) {
    { boolean continueP = Stella.stringEqlP(continuequeryP.Value, "TRUE");
      edu.isi.webtools.http.Session session = PLQuery.getQuerySession(plquery, continueP);
      PLQueryResult result = PLQueryResult.new_PLQueryResult();
      List pltuples = List.newList();
      String query = null;
      String modulename = plquery.Module;
      Cons queryresult = null;
      Module module = edu.isi.powerloom.PLI.getModule(modulename, null);

      if (continueP) {
        query = PLQuery.createFollowupQueryString(plquery);
      }
      else {
        query = PLQuery.createQueryString(plquery);
      }
      queryresult = GuiServer.evaluateQueryCommandInModule(session, query, modulename, continueP, PLQuery.isQueryPartialP(plquery));
      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { Stella_Object tuple = null;
            Cons iter000 = queryresult;
            Cons collect000 = null;

            for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
              tuple = iter000.value;
              if (collect000 == null) {
                {
                  collect000 = Cons.cons(GuiServer.makePlTuple(((Cons)(tuple))), Stella.NIL);
                  if (pltuples.theConsList == Stella.NIL) {
                    pltuples.theConsList = collect000;
                  }
                  else {
                    Cons.addConsToEndOfConsList(pltuples.theConsList, collect000);
                  }
                }
              }
              else {
                {
                  collect000.rest = Cons.cons(GuiServer.makePlTuple(((Cons)(tuple))), Stella.NIL);
                  collect000 = collect000.rest;
                }
              }
            }
          }
          result.PLTuple = pltuples;
          return (result);

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  public static edu.isi.webtools.http.Session getQuerySession(PLQuery query, boolean errorP) {
    { String sessionname = query.QueryName;
      edu.isi.webtools.http.Session session = edu.isi.webtools.http.Http.lookupSession(sessionname, false);

      if ((session == null) ||
          session.timedOutP()) {
        if (errorP) {
          throw ((StellaException)(StellaException.newStellaException("Query session expired").fillInStackTrace()));
        }
        else {
          session = edu.isi.webtools.http.Http.createSession(sessionname, GuiServer.$QUERY_SESSION_TIMEOUT$);
        }
      }
      return (session);
    }
  }

  public static Stella_Object access_PLQuery_Slot_Value(PLQuery self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == GuiServer.SYM_GUI_SERVER_IsAsk) {
      if (setvalueP) {
        self.IsAsk = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.IsAsk);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_QueryName) {
      if (setvalueP) {
        self.QueryName = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.QueryName);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_Query) {
      if (setvalueP) {
        self.Query = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.Query);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_Module) {
      if (setvalueP) {
        self.Module = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.Module);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_InferenceLevel) {
      if (setvalueP) {
        self.InferenceLevel = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.InferenceLevel);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_Timeout) {
      if (setvalueP) {
        self.Timeout = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.Timeout);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_Moveout) {
      if (setvalueP) {
        self.Moveout = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.Moveout);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_MatchMode) {
      if (setvalueP) {
        self.MatchMode = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.MatchMode);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_NumResults) {
      if (setvalueP) {
        self.NumResults = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.NumResults);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_MinScore) {
      if (setvalueP) {
        self.MinScore = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.MinScore);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_MaxUnknowns) {
      if (setvalueP) {
        self.MaxUnknowns = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.MaxUnknowns);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_MaximizeScore) {
      if (setvalueP) {
        self.MaximizeScore = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.MaximizeScore);
      }
    }
    else if (slotname == GuiServer.SYM_GUI_SERVER_DontOptimize) {
      if (setvalueP) {
        self.DontOptimize = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.DontOptimize);
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
    { PLQuery self = this;

      return (GuiServer.SGT_GUI_SERVER_PLQuery);
    }
  }

}

