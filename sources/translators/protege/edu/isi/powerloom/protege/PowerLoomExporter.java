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
| The Original Code is the Protege PowerLoom Exporter.                       |
|                                                                            |
| The Initial Developer of the Original Code is                              |
| UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
| 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
|                                                                            |
| Portions created by the Initial Developer are Copyright (C) 2005-2007      |
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
*/

// $Id$

package edu.isi.powerloom.protege;

import java.io.*;
import java.util.*;
import javax.swing.JFileChooser;
import javax.swing.JCheckBox;
import edu.stanford.smi.protege.model.*;
import edu.stanford.smi.protege.plugin.*;
import edu.stanford.smi.protege.util.*;

/** Class to export Protege projects into PowerLoom format.
 *
 * @author USC/ISI Loom Group
 * @version $Revision$
 */
public class PowerLoomExporter implements ExportPlugin {

  protected static final String EXTENSION = ".plm";
  protected static final String PROTEGE_MODULE_NAME = "PROTEGE-SYSTEM";
  protected static boolean IGNORE_SYSTEM_CLASSES = true;
  protected HashSet<Frame> registry = new HashSet<Frame>(); // NOT THREADSAFE!!
  protected boolean doNativeTranslation = true;

  public String getName() {
    return "PowerLoom File";
  }

  public void handleExportRequest(Project project) {
    String name = project.getName();
    String proposedName = new File(name + EXTENSION).getPath();
    File file = null;
    JFileChooser chooser = ComponentFactory.createFileChooser(proposedName, EXTENSION);
    JCheckBox nativeBox = new JCheckBox("Native", doNativeTranslation);
    nativeBox.setToolTipText("Just native PowerLoom or with Prot\u00e9g\u00e9 additions.");
    chooser.setAccessory(nativeBox);
    if (chooser.showSaveDialog(null) == JFileChooser.APPROVE_OPTION) {
      doNativeTranslation = nativeBox.isSelected();
      file = chooser.getSelectedFile();
      if (file != null) {
	saveToFile(project, file, doNativeTranslation);
      }
    }
  }

  public void dispose() {
    // do nothing
  }
    
  public void saveToFile (Project project, File file, boolean nativeOnly) {
      PrintWriter writer = FileUtilities.createPrintWriter(file, false);
      writeOntology(project.getKnowledgeBase(), writer, nativeOnly);
      writer.close();
    }

  // Heavily inspired or stolen from ExportFlora.java by Michael Sintek.

  // Issues:
  // - union classes
  // - Protege roots where to stop
  // - module information 
  // - more specially mapped slots such as :DOCUMENTATION
  // - slot facets


  void initializeRegistry () {
    registry.clear();
  }

  void registerFrame (Frame frame) {
    // Insert `frame' into the registry (e.g., to mark that it was already translated).
    registry.add(frame);
  }

  boolean isRegisteredFrame (Frame frame) {
    // Return true if `frame' was already registered.
    return registry.contains(frame);
  }

  boolean isIgnoredFrame (Frame frame) {
    // Return true if `frame' does not need to be translated
    //    or has already been translated.
    // Currently, we ignore all system classes and slots.
    return (frame.isIncluded() ||
	    isRegisteredFrame(frame) ||
	    (IGNORE_SYSTEM_CLASSES && frame.isSystem()) ||
	    (frame instanceof Facet));
  }

  boolean isTopOfClassHierarchy (String name) {
    // Return true if `name' names the top of the class hierarchy
    // and thus would provide no useful restriction.
    return (name.equals("THING") ||
	    name.equals("|:THING|"));
  }

  void exportCls (Writer writer, Cls cls, boolean nativeOnly) {
    // Output a PowerLoom definition of the Protege class `cls'.
    // To do:  Handle template slot restrictions
    //  -- cls.getTemplateSlotValueType(slot)
    //  -- cls.getTemplateSlotAllowedClses(slot)
    //  -- cardinality restrictions, etc.

    Collection<Cls> superClasses = (Collection<Cls>) cls.getDirectSuperclasses();
        
    if (isIgnoredFrame(cls))
      // we are not interested in system classes:
      return;
    else
      registerFrame(cls);
        
    // Generate concept definition:
    Util.print(writer, "(DEFCONCEPT " + Util.getPowerLoomName(cls, nativeOnly) + " (?self");
    for (Cls superClass: new TreeSet<Cls>(superClasses)) {
      if (! (nativeOnly && superClass.isSystem())) {
	String superName = Util.getPowerLoomName(superClass, nativeOnly);
	if (! isTopOfClassHierarchy(superName))
	  Util.print(writer, " " + superName);
      }
    }
    Util.print(writer, ")");  // close superclass list

    // Output template slot restrictions on the class:
    // Collection templateSlots = cls.getDirectTemplateSlots();
    for (Slot templateSlot: new TreeSet<Slot>((Collection<Slot>) cls.getTemplateSlots())) {
      if (cls.hasDirectTemplateSlot(templateSlot) ||
	  cls.hasDirectlyOverriddenTemplateSlot(templateSlot)) {
	if (!nativeOnly)
	  Util.print(writer, "\n   :|:DIRECT-TEMPLATE-SLOTS| " + Util.getPowerLoomName(templateSlot, nativeOnly));
	exportTemplateSlotRestriction(writer, cls, templateSlot, "?self", nativeOnly);
      }
    }
    
    // Output any own slot values defined on the class:
    for (Slot slot: new TreeSet<Slot>((Collection<Slot>) cls.getOwnSlots())) {
      exportOwnSlotValueAsKeywordAxiom(writer, cls, slot, nativeOnly);
    }

    Util.print(writer, ")\n\n");  // close definition
  }

  String getRelationDomain (Slot slot, boolean nativeOnly) {
    // Return the domain to use for the PowerLoom relation representing `slot'.
    // If `slot' has a single domain, translate it and return it as a string;
    //    otherwise, use THING since we haven't yet decided on how to deal
    //    with UNION domains.

    Collection domains = slot.getDirectDomain();
    if (domains.size() == 1)
      return Util.getPowerLoomName((Frame)domains.iterator().next(), nativeOnly);
    else
      return "THING";
  }

  
  String getTypeTranslation (ValueType valueType, Collection allowedClses,
				    Collection allowedParents, boolean nativeOnly) {
    // Return the type to use in PowerLoom for the Protege valueType given.
    // If `slot' has a single allowedCls, translate it and return it as
    //    a string;
    //  otherwise, return THING since we haven't yet decided on how to deal
    //    with UNION domains.

    if (valueType == ValueType.ANY)
      return "THING";
    else if (valueType == ValueType.CLS)
      return "CONCEPT"; // allowed parents must be translated as a separate rule
    else if (valueType == ValueType.INSTANCE) {
      if (allowedClses.isEmpty())
	return "THING";
      else
	if (allowedClses.size() == 1)
	  return Util.getPowerLoomName((Cls)allowedClses.iterator().next(), nativeOnly);
	else
	  return "THING"; // union class constraint has to go elsewhere
    }
    else if (valueType == ValueType.INTEGER)
      return "INTEGER";
    else if (valueType == ValueType.FLOAT)
      return "NUMBER";
    else if (valueType == ValueType.STRING)
      return "STRING";
    else if (valueType == ValueType.SYMBOL)
      return "STRING";
    else if (valueType == ValueType.BOOLEAN)
      return "|:BOOLEAN|"; // shouldn't happen
    else {
      System.out.println("Warning: unknown value type " + valueType);
      return "THING";
    }
  }

  String getRelationRange (Slot slot, boolean nativeOnly) {
    return getTypeTranslation(slot.getValueType(),
			      slot.getAllowedClses(), 
			      slot.getAllowedParents(),
			      nativeOnly);
  }

  String getTemplateRelationRange (Slot slot, Cls cls, boolean nativeOnly) {
    return getTypeTranslation(cls.getTemplateSlotValueType(slot),
			      cls.getTemplateSlotAllowedClses(slot), 
			      cls.getTemplateSlotAllowedParents(slot),
			      nativeOnly);

  }

  void exportSlot (Writer writer, Slot slot, boolean nativeOnly) {
    // Issues to handle:
    // - UNION domains & ranges
    if (isIgnoredFrame(slot))
      return;
    else
      registerFrame(slot);

    boolean isUnaryRelation = (slot.getValueType() == ValueType.BOOLEAN);
    boolean isRelation = isUnaryRelation || slot.getAllowsMultipleValues();
    String relationDomain = getRelationDomain(slot, nativeOnly);
    String relationRange = null;
    String firstVariable = (isTopOfClassHierarchy(relationDomain) ? 
			    "?self" :
			    "(?self " + relationDomain + ")");
    String secondVariable = "";

    if (! isUnaryRelation) {
      relationRange = getRelationRange(slot, nativeOnly);
      secondVariable = (isTopOfClassHierarchy(relationRange) ? 
			" ?value" :
			" (?value " + relationRange + ")");
    }
    Util.println(writer,
		 (isRelation ? "(DEFRELATION " : "(DEFFUNCTION ")
		 + Util.getPowerLoomName(slot, nativeOnly) 
		 + " (" + firstVariable + secondVariable + ")");

    // Handle any superslots:
    for (Iterator superSlotsIterator = slot.getDirectSuperslots().iterator();
	 superSlotsIterator.hasNext();) {
      Slot superSlot = (Slot)superSlotsIterator.next();
      if (! (nativeOnly && superSlot.isSystem())) {
	Util.println(writer,
		     "   :=> (" + Util.getPowerLoomName(superSlot, nativeOnly)
		     + " ?self" 
		     + (isUnaryRelation ? ")" : " ?value)")
		     );
      }
    }


    // Output any own slot values defined on the slot:
    for (Slot ownSlot: new TreeSet<Slot>((Collection<Slot>) slot.getOwnSlots())) {
      exportOwnSlotValueAsKeywordAxiom(writer, slot, ownSlot, nativeOnly);
    }
    Util.print(writer, ")\n\n");  // close definition
  }

  boolean isTranslatedSystemSlot (Slot slot) {
    // Return true if the slot is a system slot that we translate.
    // System slots we need to care about - there might be more:
    String name = slot.getName();
    return (name.equals(":CREATION-TIMESTAMP")
	    || name.equals(":CREATOR")
	    || name.equals(":DIRECT-DOMAIN")
	    || name.equals(":DIRECT-SUPERSLOTS")
	    || name.equals(":DIRECT-SUBSLOTS")
	    || name.equals(":DIRECT-TYPE")
	    || name.equals(":DOCUMENTATION")
	    || name.equals(":ROLE")
	    || name.equals(":SLOT-INVERSE")
	    || name.equals(":SLOT-MINIMUM-CARDINALITY")
	    || name.equals(":SLOT-MAXIMUM-CARDINALITY")
	    || name.equals(":SLOT-NUMERIC-MINIMUM")
	    || name.equals(":SLOT-NUMERIC-MAXIMUM")
	    || name.equals(":SLOT-VALUE-TYPE"));
      }

  boolean isMappedSlot (Slot slot) {
    // Return true if `slot' and its values are mapped onto an
    //    appropriate PowerLoom idiom.
    String name = slot.getName();
    return (name.equals(":DIRECT-TYPE")
	    || name.equals(":DOCUMENTATION")
	    || name.equals(":SLOT-INVERSE")
	    // These not yet:
	    // || name.equals(":SLOT-MINIMUM-CARDINALITY")
	    // || name.equals(":SLOT-MAXIMUM-CARDINALITY")
	    // || name.equals(":SLOT-NUMERIC-MINIMUM")
	    // || name.equals(":SLOT-NUMERIC-MAXIMUM")
	    // || name.equals(":SLOT-VALUE-TYPE")
	    );
  }
  boolean isIgnoredSlot (Slot slot, boolean nativeOnly) {
    // Return true if slot values for `slot' do not need to be output.
    if (nativeOnly) {
      return (slot.isSystem() && (! isMappedSlot(slot)));
    } else {
      return (slot.isSystem() && (! isTranslatedSystemSlot(slot)));
    }
  }

   boolean translateOwnSlotValueAsKeywordAxiom (Writer writer,
						      Frame instance,
						      Slot ownSlot,
						      boolean nativeOnly) {
    // Specially translates the slots listed in `isMappedSlot' and
    //    returns true if it did.
    String name = ownSlot.getName();
    int nofValues = instance.getOwnSlotValueCount(ownSlot);
    ValueType valueType = instance.getOwnSlotValueType(ownSlot);

    if (nofValues == 0)
      return true;

    Iterator values = instance.getOwnSlotValues(ownSlot).iterator();

    if (name.equals(":DIRECT-TYPE")) {
      while (values.hasNext()) {
	Object value = values.next();
	// Don't print system frames if nativeOnly
	if (! (nativeOnly && (value instanceof Frame) && ((Frame) value).isSystem()))
	  Util.print(writer, "\n  :"
		     + Util.valueToPowerLoomObject(valueType, value, nativeOnly)
		     + " TRUE");
      }
      return true;
    }

    ////// MORE TO COME.

    // Generate axiom for system slots that just need to be renamed:
    String keyword;

    if (name.equals(":DOCUMENTATION"))
      keyword = name;
    else if (name.equals(":SLOT-INVERSE"))
      keyword = ":INVERSE";
    else
      return false;

    Util.print(writer, "\n  " + keyword + " ");
    if (nofValues > 1) Util.print(writer, "(");
    while (values.hasNext()) {
      Util.print(writer, " " + Util.valueToPowerLoomObject(valueType, values.next(), nativeOnly));
    }
    if (nofValues > 1) Util.print(writer, ")");
    return true;
  }

  void exportTemplateSlotRestriction (Writer writer,
					     Cls cls,
					     Slot templateSlot,
					     String clsVariable,
					     boolean nativeOnly) {
    // TO DO:  Handle additional non-standard Facets.

    if (isIgnoredSlot(templateSlot, nativeOnly))
      return;

    String slotName = Util.getPowerLoomName(templateSlot, nativeOnly);
    int minCardinality = cls.getTemplateSlotMinimumCardinality(templateSlot);
    int maxCardinality = cls.getTemplateSlotMaximumCardinality(templateSlot);
    Number minNumericValue = cls.getTemplateSlotMinimumValue(templateSlot);
    Number maxNumericValue = cls.getTemplateSlotMaximumValue(templateSlot);
    ValueType valueType = cls.getTemplateSlotValueType(templateSlot);
    String rangeType = getTemplateRelationRange(templateSlot, cls, nativeOnly);

    if (valueType == ValueType.BOOLEAN)  // Handled as unary relation.
      return;
    
    if (minCardinality > 0)
      Util.print(writer, 
		 "\n   :=> (RANGE-CARDINALITY-LOWER-BOUND "
		 + slotName + " " + clsVariable + " " + minCardinality + ")");
    if (maxCardinality >= 0)
      Util.print(writer,
		 "\n   :=> (RANGE-CARDINALITY-UPPER-BOUND "
		 + slotName + " " + clsVariable + " " + maxCardinality + ")");
    if (minNumericValue != null)
      Util.print(writer,
		 "\n   :=> (=> (" + slotName + " " + clsVariable + " ?X)" + 
		 " (>= ?X " + minNumericValue + "))");
    if (maxNumericValue != null)
      Util.print(writer,
		 "\n   :=> (=> (" + slotName + " " + clsVariable + " ?X)" + 
		 " (=< ?X " + maxNumericValue + "))");
    if (! isTopOfClassHierarchy(rangeType))
      Util.print(writer, 
		 "\n   :=> (RANGE-TYPE " + slotName + " " + clsVariable + " " + rangeType + ")");
    Collection allowedValues = cls.getTemplateSlotAllowedValues(templateSlot);
    if (! allowedValues.isEmpty()) {
      Util.print(writer,
		 "\n   :=> (RANGE-TYPE " + slotName + " " + clsVariable +
		 " (KAPPA (?X) (MEMBER-OF ?X (SETOF ");
      Util.printPowerLoomCollection(writer, allowedValues, " ", nativeOnly);
      Util.print(writer, "))))");
    }
    
    if (valueType == ValueType.INSTANCE) {
      if (!nativeOnly) {
	Collection allowedClses =  cls.getTemplateSlotAllowedClses(templateSlot);
	for (Iterator iter = allowedClses.iterator(); iter.hasNext(); ) {
	  Util.print(writer,
		     "\n   :=> (|:RANGE-ALLOWED-CLASSES| " + slotName
		     + " " + clsVariable
		     + " " + Util.getPowerLoomName((Frame) iter.next(), nativeOnly) + ")");
	}
      }
    } else if (valueType == ValueType.CLS) {
      if (!nativeOnly) {
	Collection allowedParents =  cls.getTemplateSlotAllowedParents(templateSlot);
	for (Iterator iter = allowedParents.iterator(); iter.hasNext(); ) {
	  Util.print(writer,
		     "\n   :=> (|:RANGE-ALLOWED-PARENTS| " + slotName
		     + " " + clsVariable
		     + " " + Util.getPowerLoomName((Frame) iter.next(), nativeOnly) + ")");
	}
      }
    }

    Collection values = cls.getTemplateSlotValues(templateSlot);
    for (Iterator iter = values.iterator(); iter.hasNext(); ) {
	Util.print(writer,
		   "\n   :=> (" + slotName + " " + clsVariable + " "
		   + Util.valueToPowerLoomObject(valueType, iter.next(), nativeOnly) +  ")");
      }
    Collection defaults = cls.getTemplateSlotDefaultValues(templateSlot);
    for (Iterator iter = defaults.iterator(); iter.hasNext(); ) {
	Util.print(writer,
		   "\n   :~> (" + slotName + " " + clsVariable + " "
		   + Util.valueToPowerLoomObject(valueType, iter.next(), nativeOnly) +  ")");
    }
  }

  void exportOwnSlotValueAsKeywordAxiom (Writer writer,
						Frame instance,
						Slot ownSlot,
						boolean nativeOnly) {

    if (isIgnoredSlot(ownSlot, nativeOnly))
      return;

    if (isMappedSlot(ownSlot)
	&& translateOwnSlotValueAsKeywordAxiom(writer, instance, ownSlot, nativeOnly))
      return;

    int nofValues = instance.getOwnSlotValueCount(ownSlot);
    ValueType valueType = instance.getOwnSlotValueType(ownSlot);

    if (nofValues == 0)
      return;

    Util.print(writer, "\n  :" + Util.getPowerLoomName(ownSlot, nativeOnly) + " ");
    if (nofValues > 1) Util.print(writer, "(");

    for (Iterator values = instance.getOwnSlotValues(ownSlot).iterator();
	 values.hasNext();)
      Util.print(writer, " " + Util.valueToPowerLoomObject(valueType, values.next(), nativeOnly));
    if (nofValues > 1) Util.print(writer, ")");
  }

  void exportInstance(Writer writer, Instance instance, boolean nativeOnly) {

    if (isIgnoredFrame(instance))
      return;
    else
      registerFrame(instance);

    Util.print(writer, "(DEFINSTANCE " + Util.getPowerLoomName(instance, nativeOnly));

    // Output any own slot values defined on the instance:
    for (Slot ownSlot: new TreeSet<Slot>((Collection<Slot>) instance.getOwnSlots())) {
      exportOwnSlotValueAsKeywordAxiom(writer, instance, ownSlot, nativeOnly);
    }
    Util.print(writer, ")\n\n");  // close definition
  }

  void exportOntology(Writer writer, KnowledgeBase kb, boolean nativeOnly) {
    initializeRegistry();
    for (Cls cls: new TreeSet<Cls>((Collection<Cls>) kb.getClses())) {
      exportCls(writer, cls, nativeOnly);
    }

    // here we still need to output slots.
    for (Slot slot: new TreeSet<Slot>((Collection<Slot>) kb.getSlots())) {
      exportSlot(writer, slot, nativeOnly);
    }
  }

  void exportInstances(Writer writer, KnowledgeBase kb, boolean nativeOnly) {
    initializeRegistry();
    for (Instance instance: new TreeSet<Instance>((Collection<Instance>) kb.getInstances())) {
      if (instance instanceof SimpleInstance) {
	exportInstance(writer, instance, nativeOnly);
      }
    }
  }

  String projectNameToModuleName(String projectName) {
    return projectName.toUpperCase() + "-MODULE";
  }

  String moduleNameFromProjectURI(java.net.URI projectURI) {
    // Assumes that the form of the URI is
    //    .../name.pprj  
    String path = projectURI.getPath();
    try {
      return projectNameToModuleName(path.substring(path.lastIndexOf('/') + 1,
						    path.lastIndexOf(".pprj")));
    } catch (IndexOutOfBoundsException e) {
      return path;
    }
  }

  void exportModuleDefinition(Writer writer, KnowledgeBase kb, boolean nativeOnly) {
    // Print a module definition for the exported files derived
    //    from the current project's name.
    String moduleName = projectNameToModuleName(kb.getProject().getName());
    Iterator includedProjects = kb.getProject().getDirectIncludedProjectURIs().iterator();

    Util.print(writer, "(DEFMODULE \"" + moduleName + "\"\n"
	       + "  :INCLUDES (");
    while (includedProjects.hasNext()) {
      Util.print(writer, 
		 "\"" + moduleNameFromProjectURI((java.net.URI) (includedProjects.next())) + "\" ");
    }
    if (!nativeOnly) Util.print(writer, "\"" + PROTEGE_MODULE_NAME + "\" ");
    Util.print(writer,
	       "\"PL-KERNEL\")\n"
	       + "  :CASE-SENSITIVE? TRUE)");
  }

  void writeInModule (Writer writer, KnowledgeBase kb) {
    // Print an in-module declaration for the exported files derived
    //    from the current project's name.
    String moduleName = projectNameToModuleName(kb.getProject().getName());
    Util.print(writer, "(IN-MODULE \"" + moduleName + "\")");
  }

  /**  Writes an ontology to an output stream.  This can be done including
   *  references to a Protege ontology or not.
   *
   * @param kb The Protege knowledge base to be written.
   * @param out The writer used to accept the translation.
   * @param nativeOnly A flag which tells whether reference to Protege concepts should be left out.
   */
  public void writeOntology(KnowledgeBase kb, PrintWriter out, boolean nativeOnly) {
    // Translate the ontology of `kb' to PowerLoom and write the
    // result to `fileName'.
    try {
      String kbName = kb.getName();

      Util.print(out, Util.getPowerLoomFileHeader());
      Util.print(out, "\n\n;;; Ontology definitions automatically generated from Protege KB '"
		 + kbName + "'\n\n");
            
      exportModuleDefinition(out, kb, nativeOnly);
      Util.print(out, "\n\n");
      writeInModule(out, kb);
      Util.print(out, "\n\n");

      // not yet sure what to do about these:
      //Vector unionClasses = new Vector(); // [ [c1,..,cn], .... ]

      out.flush();
      exportOntology(out, kb, nativeOnly);
      Util.print(out, "\n\n");
      out.flush();
      exportInstances(out, kb, nativeOnly);

      out.flush();
            
    } catch (Exception e) {
      Util.println(out, "*** ERROR *** " + e);
      e.printStackTrace(out);
      out.flush();
    }
  }

}
