//  -*- Mode: Java -*-
//
// VizInfo.java

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

/** Encapsulates all the options and local state information needed to
 * visualize a set of concepts as a graph.
 * @author Stella Java Translator
 */
public class VizInfo extends StandardObject {
    public OutputStream stream;
    public HashSet allowedObjects;
    public boolean showRelationsP;
    public boolean showAttributesP;
    public boolean showRulesP;
    public boolean addTopP;
    public String nodeColor;
    public String relationColor;
    public String relationStyle;
    public int fontSize;

  public static VizInfo newVizInfo() {
    { VizInfo self = null;

      self = new VizInfo();
      self.fontSize = OntosaurusUtil.$VIZ_FONT_SIZE$;
      self.relationStyle = OntosaurusUtil.$VIZ_RELATION_STYLE$;
      self.relationColor = OntosaurusUtil.$VIZ_RELATION_COLOR$;
      self.nodeColor = OntosaurusUtil.$VIZ_NODE_COLOR$;
      self.addTopP = OntosaurusUtil.$VIZ_ADD_TOPp$;
      self.showRulesP = OntosaurusUtil.$VIZ_SHOW_RULESp$;
      self.showAttributesP = OntosaurusUtil.$VIZ_SHOW_ATTRIBUTESp$;
      self.showRelationsP = OntosaurusUtil.$VIZ_SHOW_RELATIONSp$;
      self.allowedObjects = null;
      self.stream = null;
      return (self);
    }
  }

  public void vizExportTrailer() {
    { VizInfo self = this;

      self.vizExportDotTrailer();
    }
  }

  public void vizExportHeader() {
    { VizInfo self = this;

      self.vizExportDotHeader();
    }
  }

  public void vizExportModule(Module module) {
    { VizInfo self = this;

      Logic.plLog(OntosaurusUtil.KWD_MEDIUM, Cons.cons(StringWrapper.wrapString("powerloom-viz: exporting module: "), Cons.cons(module, Stella.NIL)));
      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          self.vizExportConcepts(module);

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  public void vizExportConcepts(Module module) {
    { VizInfo self = this;

      { Stella_Object concept = null;
        edu.isi.powerloom.PlIterator iter000 = edu.isi.powerloom.PLI.getConceptInstances(((LogicObject)(Logic.getInstance(OntosaurusUtil.SGT_PL_KERNEL_KB_CONCEPT))), module, null);

        while (iter000.nextP()) {
          concept = iter000.value;
          if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(concept), OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
            { LogicObject concept000 = ((LogicObject)(concept));

              if ((concept000.homeModule() == module) &&
                  self.vizAllowedObjectP(concept000)) {
                self.vizExportConcept(concept000, module);
              }
            }
          }
          else {
            { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

              stream000.nativeStream.print("viz-export-concepts: concept not handled: `" + concept + "'");
              throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
            }
          }
        }
      }
    }
  }

  public void vizExportConceptTree(LogicObject concept, Module module) {
    { VizInfo self = this;

      self.nodeColor = "palegreen";
      self.vizExportConcept(concept, module);
      self.nodeColor = "yellow";
      self.vizAllowObject(concept);
      { LogicObject renamed_Super = null;
        edu.isi.powerloom.PlIterator iter000 = edu.isi.powerloom.PLI.getProperSuperrelations(concept, module, null);

        while (iter000.nextP()) {
          renamed_Super = ((LogicObject)(iter000.value));
          self.vizAllowObject(renamed_Super);
        }
      }
      { LogicObject sub = null;
        edu.isi.powerloom.PlIterator iter001 = edu.isi.powerloom.PLI.getProperSubrelations(concept, module, null);

        while (iter001.nextP()) {
          sub = ((LogicObject)(iter001.value));
          self.vizAllowObject(sub);
        }
      }
      { LogicObject renamed_Super = null;
        edu.isi.powerloom.PlIterator iter002 = edu.isi.powerloom.PLI.getProperSuperrelations(concept, module, null);

        while (iter002.nextP()) {
          renamed_Super = ((LogicObject)(iter002.value));
          if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(renamed_Super), OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
            { LogicObject super000 = ((LogicObject)(renamed_Super));

              self.vizExportConcept(super000, module);
            }
          }
          else {
            { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

              stream000.nativeStream.print("viz-export-concept-tree: concept not handled: `" + renamed_Super + "'");
              throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
            }
          }
        }
      }
      { LogicObject sub = null;
        edu.isi.powerloom.PlIterator iter003 = edu.isi.powerloom.PLI.getProperSubrelations(concept, module, null);

        while (iter003.nextP()) {
          sub = ((LogicObject)(iter003.value));
          if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(sub), OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
            { LogicObject sub000 = ((LogicObject)(sub));

              self.vizExportConcept(sub000, module);
            }
          }
          else {
            { OutputStringStream stream001 = OutputStringStream.newOutputStringStream();

              stream001.nativeStream.print("viz-export-concept-tree: concept not handled: `" + sub + "'");
              throw ((StellaException)(StellaException.newStellaException(stream001.theStringReader()).fillInStackTrace()));
            }
          }
        }
      }
    }
  }

  public void vizExportConcept(LogicObject concept, Module module) {
    { VizInfo self = this;

      self.vizExportConceptToDot(concept, module);
    }
  }

  public void vizExportDotTrailer() {
    { VizInfo self = this;

      self.stream.nativeStream.println("}");
    }
  }

  public void vizExportDotHeader() {
    { VizInfo self = this;

      { OutputStream stream = self.stream;

        stream.nativeStream.println("digraph Ontology {");
        stream.nativeStream.println("  node [fontname = Arial, fontsize=" + self.fontSize + ", shape=box, style=filled, fillcolor=" + self.nodeColor + ", height=0.2];");
        stream.nativeStream.println("  edge [fontname = Arial, fontsize=" + self.fontSize + "];");
      }
    }
  }

  public void vizExportConceptToDot(LogicObject concept, Module module) {
    { VizInfo self = this;

      self.vizConceptToDotNode(concept, module);
      self.vizConceptLinksToDotEdges(concept, module);
    }
  }

  public void vizConceptLinksToDotEdges(LogicObject concept, Module module) {
    { VizInfo self = this;

      { OutputStream stream = self.stream;
        int count = 0;

        { LogicObject renamed_Super = null;
          edu.isi.powerloom.PlIterator iter000 = edu.isi.powerloom.PLI.getDirectSuperrelations(concept, module, null);

          while (iter000.nextP()) {
            renamed_Super = ((LogicObject)(iter000.value));
            if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(renamed_Super), OntosaurusUtil.SGT_LOGIC_NAMED_DESCRIPTION)) {
              { NamedDescription super000 = ((NamedDescription)(renamed_Super));

                if (self.vizAllowedObjectP(super000)) {
                  stream.nativeStream.println("  \"" + OntosaurusUtil.vizDotObjectName(super000) + "\" -> \"" + OntosaurusUtil.vizDotObjectName(concept) + "\" [dir=back]");
                  count = count + 1;
                }
                else {
                  stream.nativeStream.print("  \"" + OntosaurusUtil.vizDotObjectName(super000) + "\" [shape=box, style=filled, fillcolor=grey,URL=\"" + self.vizGenerateOntosaurusHandle(super000) + "\"]");
                  stream.nativeStream.println("  \"" + OntosaurusUtil.vizDotObjectName(super000) + "\" -> \"" + OntosaurusUtil.vizDotObjectName(concept) + "\" [dir=back]");
                  count = count + 1;
                }
              }
            }
            else {
              { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

                stream000.nativeStream.print("viz-concept-links-to-dot-edges: unhandled super concept: `" + renamed_Super + "'");
                throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
              }
            }
          }
        }
        if ((count == 0) &&
            self.addTopP) {
          stream.nativeStream.println("  \"" + OntosaurusUtil.VIZ_TOP + "\" -> \"" + OntosaurusUtil.vizDotObjectName(concept) + "\" [dir=back]");
        }
        if (self.showRelationsP) {
          { LogicObject range = null;
            String relcolor = self.relationColor;
            String relstyle = self.relationStyle;

            { Object old$Module$000 = Stella.$MODULE$.get();
              Object old$Context$000 = Stella.$CONTEXT$.get();

              try {
                Native.setSpecial(Stella.$MODULE$, module);
                Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
                { LogicObject relation = null;
                  Cons iter001 = self.vizGetBinaryRelationsOf(concept);

                  for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
                    relation = ((LogicObject)(iter001.value));
                    range = edu.isi.powerloom.PLI.getRange(relation);
                    if (self.vizAllowedObjectP(relation)) {
                      stream.nativeStream.println("  \"" + OntosaurusUtil.vizDotObjectName(concept) + "\" -> \"" + OntosaurusUtil.vizDotObjectName(range) + "\" [label=\"" + OntosaurusUtil.vizDotObjectName(relation) + "\", color=" + relcolor + ", style=" + relstyle + "]");
                    }
                  }
                }

              } finally {
                Stella.$CONTEXT$.set(old$Context$000);
                Stella.$MODULE$.set(old$Module$000);
              }
            }
          }
        }
      }
    }
  }

  public void vizAddConceptRulesToDotNode(LogicObject concept, Module module) {
    { VizInfo self = this;

      { OutputStream stream = self.stream;
        boolean firstP = true;

        { Object old$Module$000 = Stella.$MODULE$.get();
          Object old$Context$000 = Stella.$CONTEXT$.get();

          try {
            Native.setSpecial(Stella.$MODULE$, module);
            Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
            { Object old$PrettyprintlogicalformsP$000 = Logic.$PRETTYPRINTLOGICALFORMSp$.get();

              try {
                Native.setBooleanSpecial(Logic.$PRETTYPRINTLOGICALFORMSp$, true);
                { Proposition rule = null;
                  edu.isi.powerloom.PlIterator iter000 = edu.isi.powerloom.PLI.getRules(concept, module, null);

                  while (iter000.nextP()) {
                    rule = ((Proposition)(iter000.value));
                    if (!Proposition.simpleSubrelationPropositionP(rule)) {
                      if (!(firstP)) {
                        stream.nativeStream.print("\\l");
                      }
                      firstP = false;
                      stream.nativeStream.print(OntosaurusUtil.vizDotString(Native.stringify(rule)));
                    }
                  }
                }

              } finally {
                Logic.$PRETTYPRINTLOGICALFORMSp$.set(old$PrettyprintlogicalformsP$000);
              }
            }

          } finally {
            Stella.$CONTEXT$.set(old$Context$000);
            Stella.$MODULE$.set(old$Module$000);
          }
        }
      }
    }
  }

  public void vizAddConceptAttributesToDotNode(LogicObject concept, Module module) {
    { VizInfo self = this;

      { OutputStream stream = self.stream;
        LogicObject range = null;

        { Object old$Module$000 = Stella.$MODULE$.get();
          Object old$Context$000 = Stella.$CONTEXT$.get();

          try {
            Native.setSpecial(Stella.$MODULE$, module);
            Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
            { LogicObject relation = null;
              Cons iter000 = self.vizGetBinaryRelationsOf(concept);

              for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
                relation = ((LogicObject)(iter000.value));
                range = edu.isi.powerloom.PLI.getRange(relation);
                stream.nativeStream.print(OntosaurusUtil.vizDotObjectName(relation) + ": " + OntosaurusUtil.vizDotObjectName(range) + "\\l");
              }
            }

          } finally {
            Stella.$CONTEXT$.set(old$Context$000);
            Stella.$MODULE$.set(old$Module$000);
          }
        }
      }
    }
  }

  public void vizConceptToDotNode(LogicObject concept, Module module) {
    { VizInfo self = this;

      { OutputStream stream = self.stream;
        String conceptname = OntosaurusUtil.vizDotObjectName(concept);
        String conceptcolor = self.nodeColor;
        String concepturl = self.vizGenerateOntosaurusHandle(concept);

        if (self.showAttributesP ||
            self.showRulesP) {
          stream.nativeStream.print("  \"" + conceptname + "\" [shape=record, style=filled, fillcolor=" + conceptcolor + ", URL=\"");
          stream.nativeStream.print(concepturl);
          stream.nativeStream.print("\", label=\"{" + conceptname + "|");
          if (self.showAttributesP) {
            self.vizAddConceptAttributesToDotNode(concept, module);
          }
          if (self.showRulesP) {
            if (self.showAttributesP) {
              stream.nativeStream.print("|");
            }
            self.vizAddConceptRulesToDotNode(concept, module);
          }
          stream.nativeStream.println("}\"]");
        }
        else {
          stream.nativeStream.print("  \"" + conceptname + "\" [shape=box, style=filled, fillcolor=" + conceptcolor + ", URL=\"" + concepturl + "\"]");
        }
      }
    }
  }

  public void vizExcludeObject(Stella_Object renamed_Object) {
    { VizInfo self = this;

      { HashSet allowedobjects = self.allowedObjects;

        if (allowedobjects == null) {
          allowedobjects = HashSet.newHashSet();
          self.allowedObjects = allowedobjects;
        }
        allowedobjects.remove(renamed_Object);
      }
    }
  }

  public void vizAllowObject(Stella_Object renamed_Object) {
    { VizInfo self = this;

      { HashSet allowedobjects = self.allowedObjects;

        if (allowedobjects == null) {
          allowedobjects = HashSet.newHashSet();
          self.allowedObjects = allowedobjects;
        }
        allowedobjects.insert(renamed_Object);
      }
    }
  }

  public boolean vizAllowedObjectP(Stella_Object renamed_Object) {
    { VizInfo self = this;

      return (((self.allowedObjects == null) ? (!self.vizExcludedModuleP(renamed_Object.homeModule())) : self.allowedObjects.memberP(renamed_Object)));
    }
  }

  public boolean vizExcludedModuleP(Module module) {
    { VizInfo self = this;

      return (OntosaurusUtil.$VIZ_EXCLUDED_MODULES$.memberP(module) ||
          (!Logic.logicModuleP(module)));
    }
  }

  public Cons vizGetBinaryRelationsOf(LogicObject concept) {
    { VizInfo self = this;

      { MemoizationTable memoTable000 = null;
        Cons memoizedEntry000 = null;
        Stella_Object memoizedValue000 = null;

        if (Stella.$MEMOIZATION_ENABLEDp$) {
          memoTable000 = ((MemoizationTable)(OntosaurusUtil.SGT_ONTOSAURUS_M_VIZ_INFOdVIZ_GET_BINARY_RELATIONS_OF_MEMO_TABLE_000.surrogateValue));
          if (memoTable000 == null) {
            Surrogate.initializeMemoizationTable(OntosaurusUtil.SGT_ONTOSAURUS_M_VIZ_INFOdVIZ_GET_BINARY_RELATIONS_OF_MEMO_TABLE_000, "(:MAX-VALUES 1000 :TIMESTAMPS (:META-KB-UPDATE))");
            memoTable000 = ((MemoizationTable)(OntosaurusUtil.SGT_ONTOSAURUS_M_VIZ_INFOdVIZ_GET_BINARY_RELATIONS_OF_MEMO_TABLE_000.surrogateValue));
          }
          memoizedEntry000 = MruMemoizationTable.lookupMruMemoizedValue(((MruMemoizationTable)(memoTable000)), concept, ((Context)(Stella.$CONTEXT$.get())), Stella.MEMOIZED_NULL_VALUE, null, -1);
          memoizedValue000 = memoizedEntry000.value;
        }
        if (memoizedValue000 != null) {
          if (memoizedValue000 == Stella.MEMOIZED_NULL_VALUE) {
            memoizedValue000 = null;
          }
        }
        else {
          memoizedValue000 = Logic.applyCachedRetrieve(Cons.list$(Cons.cons(OntosaurusUtil.SYM_LOGIC_pRELATION, Cons.cons(OntosaurusUtil.SYM_ONTOSAURUS_pDOMAIN, Cons.cons(Stella.NIL, Stella.NIL)))), Cons.list$(Cons.cons(OntosaurusUtil.SYM_STELLA_AND, Cons.cons(Cons.list$(Cons.cons(OntosaurusUtil.SYM_PL_KERNEL_KB_NTH_DOMAIN, Cons.cons(OntosaurusUtil.SYM_LOGIC_pRELATION, Cons.cons(IntegerWrapper.wrapInteger(0), Cons.cons(OntosaurusUtil.SYM_ONTOSAURUS_pDOMAIN, Cons.cons(Stella.NIL, Stella.NIL)))))), Cons.cons(Cons.list$(Cons.cons(OntosaurusUtil.SYM_ONTOSAURUS_BINARY_RELATION, Cons.cons(OntosaurusUtil.SYM_LOGIC_pRELATION, Cons.cons(Stella.NIL, Stella.NIL)))), Cons.cons(Stella.NIL, Stella.NIL))))), Cons.consList(Cons.cons(null, Cons.cons(concept, Stella.NIL))), Cons.consList(Cons.cons(OntosaurusUtil.KWD_SINGLETONSp, Cons.cons(Stella.TRUE_WRAPPER, Cons.cons(OntosaurusUtil.KWD_INFERENCE_LEVEL, Cons.cons(OntosaurusUtil.KWD_SHALLOW, Stella.NIL))))), OntosaurusUtil.SYM_ONTOSAURUS_M_VIZ_INFOdVIZ_GET_BINARY_RELATIONS_OF_QUERY_001, new Object[2]);
          if (Stella.$MEMOIZATION_ENABLEDp$) {
            memoizedEntry000.value = ((memoizedValue000 == null) ? Stella.MEMOIZED_NULL_VALUE : memoizedValue000);
          }
        }
        { Cons value000 = ((Cons)(memoizedValue000));

          return (value000);
        }
      }
    }
  }

  public String vizGenerateOntosaurusHandle(StandardObject renamed_Object) {
    { VizInfo self = this;

      { OutputStringStream url = OutputStringStream.newOutputStringStream();

        OntosaurusUtil.htmlWriteUrl(url.nativeStream, "show", renamed_Object);
        return (url.theStringReader());
      }
    }
  }

  public static Stella_Object accessVizInfoSlotValue(VizInfo self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == OntosaurusUtil.SYM_STELLA_STREAM) {
      if (setvalueP) {
        self.stream = ((OutputStream)(value));
      }
      else {
        value = self.stream;
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_ALLOWED_OBJECTS) {
      if (setvalueP) {
        self.allowedObjects = ((HashSet)(value));
      }
      else {
        value = self.allowedObjects;
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_SHOW_RELATIONSp) {
      if (setvalueP) {
        self.showRelationsP = BooleanWrapper.coerceWrappedBooleanToBoolean(((BooleanWrapper)(value)));
      }
      else {
        value = (self.showRelationsP ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER);
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_SHOW_ATTRIBUTESp) {
      if (setvalueP) {
        self.showAttributesP = BooleanWrapper.coerceWrappedBooleanToBoolean(((BooleanWrapper)(value)));
      }
      else {
        value = (self.showAttributesP ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER);
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_SHOW_RULESp) {
      if (setvalueP) {
        self.showRulesP = BooleanWrapper.coerceWrappedBooleanToBoolean(((BooleanWrapper)(value)));
      }
      else {
        value = (self.showRulesP ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER);
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_ADD_TOPp) {
      if (setvalueP) {
        self.addTopP = BooleanWrapper.coerceWrappedBooleanToBoolean(((BooleanWrapper)(value)));
      }
      else {
        value = (self.addTopP ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER);
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_NODE_COLOR) {
      if (setvalueP) {
        self.nodeColor = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.nodeColor);
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_RELATION_COLOR) {
      if (setvalueP) {
        self.relationColor = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.relationColor);
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_RELATION_STYLE) {
      if (setvalueP) {
        self.relationStyle = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.relationStyle);
      }
    }
    else if (slotname == OntosaurusUtil.SYM_ONTOSAURUS_FONT_SIZE) {
      if (setvalueP) {
        self.fontSize = ((IntegerWrapper)(value)).wrapperValue;
      }
      else {
        value = IntegerWrapper.wrapInteger(self.fontSize);
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
    { VizInfo self = this;

      return (OntosaurusUtil.SGT_ONTOSAURUS_VIZ_INFO);
    }
  }

}

