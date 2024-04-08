//  -*- Mode: Java -*-
//
// PLString.java

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

public class PLString extends XMLObject {
    public String Value;

  public static PLString new_PLString() {
    { PLString self = null;

      self = new PLString();
      self.cdataContent = null;
      self.textContent = null;
      self.Value = null;
      return (self);
    }
  }

  /** Return the files and directories in the directory designated by '*DEFAULT-KB-DIRECTORY*'.
   * @param extensionfilter
   * @return PLDirectoryContents
   */
  public static PLDirectoryContents serverGetDefaultDirectoryListing(PLString extensionfilter) {
    { PLString dir = PLString.new_PLString();

      dir.Value = GuiServer.$DEFAULT_KB_DIRECTORY$;
      return (PLString.serverGetDirectoryListing(dir, extensionfilter));
    }
  }

  /** Return the files and directories in 'currentDirectory'.
   * @param currentdirectory
   * @param extensionfilter
   * @return PLDirectoryContents
   */
  public static PLDirectoryContents serverGetDirectoryListing(PLString currentdirectory, PLString extensionfilter) {
    { List directorylisting = GuiServer.getDirectoryListing(currentdirectory.Value);
      PLDirectoryContents pldirectorylisting = PLDirectoryContents.new_PLDirectoryContents();
      List plfiles = List.newList();
      List pldirectories = List.newList();
      Cons matchlist = GuiServer.parseMatchString(extensionfilter.Value, "FALSE");

      pldirectorylisting.DirectoryName = currentdirectory.Value;
      { Stella_Object filename = null;
        Cons iter000 = ((List)(directorylisting.first())).theConsList;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          filename = iter000.value;
          if (GuiServer.searchStringMatchP(((StringWrapper)(filename)).wrapperValue, matchlist)) {
            { PLFile plfile = PLFile.new_PLFile();

              plfile.FileName = ((StringWrapper)(filename)).wrapperValue;
              plfiles.insert(plfile);
            }
          }
        }
      }
      { Stella_Object dirname = null;
        Cons iter001 = ((List)(directorylisting.second())).theConsList;

        for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
          dirname = iter001.value;
          { PLDirectory pldirectory = PLDirectory.new_PLDirectory();

            pldirectory.DirectoryName = ((StringWrapper)(dirname)).wrapperValue;
            pldirectories.insert(pldirectory);
          }
        }
      }
      pldirectorylisting.PLFile = plfiles;
      pldirectorylisting.PLDirectory = pldirectories;
      return (pldirectorylisting);
    }
  }

  public static PLInstanceContainer serverGetInstance(PLString modulename, PLString instancename) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { PLInstanceContainer result = PLInstanceContainer.new_PLInstanceContainer();
            Stella_Object instance = edu.isi.powerloom.PLI.sGetObject(GuiServer.guiNameToPlName(instancename.Value), modulename.Value, null);
            List xmlinstances = List.newList();

            if (Stella_Object.isaP(instance, GuiServer.SGT_LOGIC_LOGIC_OBJECT) &&
                (instance != null)) {
              xmlinstances.insert(GuiServer.makePlInstance(((LogicObject)(instance))));
            }
            result.PLInstance = xmlinstances;
            return (result);
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  public static PLConceptContainer serverGetConcept(PLString modulename, PLString conceptname) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { PLConceptContainer result = PLConceptContainer.new_PLConceptContainer();
            LogicObject concept = edu.isi.powerloom.PLI.sGetConcept(GuiServer.guiNameToPlName(conceptname.Value), modulename.Value, null);
            List xmlconcepts = List.newList();

            if (concept != null) {
              xmlconcepts.insert(GuiServer.makePlConcept(concept));
            }
            result.PLConcept = xmlconcepts;
            return (result);
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  public static PLRelationContainer serverGetRelation(PLString modulename, PLString relationname) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { PLRelationContainer result = PLRelationContainer.new_PLRelationContainer();
            LogicObject relation = edu.isi.powerloom.PLI.sGetRelation(GuiServer.guiNameToPlName(relationname.Value), modulename.Value, null);
            List xmlrelations = List.newList();

            if (relation != null) {
              xmlrelations.insert(GuiServer.makePlRelation(relation, modulename.Value));
            }
            result.PLRelation = xmlrelations;
            return (result);
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Destroy an object
   * @param modulename
   * @param objectname
   * @return PLString
   */
  public static PLString serverDestroyObject(PLString modulename, PLString objectname) {
    { String modulestring = modulename.Value;
      Module module = edu.isi.powerloom.PLI.getModule(modulestring, null);
      String objectstring = objectname.Value;
      PLString result = PLString.new_PLString();

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          edu.isi.powerloom.PLI.sDestroyObject(objectstring, modulestring, null);
          result.Value = "OK";
          return (result);

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Get the extension for a relation
   * @param modulename
   * @param relationname
   * @return PLQueryResult
   */
  public static PLQueryResult serverGetExtensionForRelation(PLString modulename, PLString relationname) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { PLQueryResult result = PLQueryResult.new_PLQueryResult();
            List pltuples = List.newList();
            edu.isi.powerloom.PlIterator extension = edu.isi.powerloom.PLI.sGetRelationExtension(GuiServer.guiNameToPlName(relationname.Value), modulename.Value, null);

            { Proposition proposition = null;
              edu.isi.powerloom.PlIterator iter000 = extension;
              Cons collect000 = null;

              while (iter000.nextP()) {
                proposition = ((Proposition)(iter000.value));
                if (collect000 == null) {
                  {
                    collect000 = Cons.cons(GuiServer.makePlTupleFromProposition(proposition), Stella.NIL);
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
                    collect000.rest = Cons.cons(GuiServer.makePlTupleFromProposition(proposition), Stella.NIL);
                    collect000 = collect000.rest;
                  }
                }
              }
            }
            result.PLTuple = pltuples;
            return (result);
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  public static PLFile serverSaveKb2(PLString plmodulename, PLString plfilename) {
    { String modulename = plmodulename.Value;
      Module module = edu.isi.powerloom.PLI.getModule(modulename, null);
      String filename = plfilename.Value;
      OutputStringStream stream = OutputStringStream.newOutputStringStream();
      PLFile result = PLFile.new_PLFile();

      Stella.STANDARD_OUTPUT.nativeStream.println("Saving KB: " + modulename + " to " + filename);
      Logic.doSaveModule(module, stream);
      result.FileName = filename;
      { PLFileContent self002 = PLFileContent.new_PLFileContent();

        self002.textContent = stream.theStringReader();
        result.PLFileContent = self002;
      }
      return (result);
    }
  }

  public static PLString serverSaveKb(PLString plmodulename, PLString plkbname, PLString pldescription) {
    { String kbname = plkbname.Value;
      String modulename = plmodulename.Value;
      Module module = edu.isi.powerloom.PLI.getModule(modulename, null);
      String description = pldescription.Value;
      Cons rawfileindex = GuiServer.loadIndexFile();
      PLModuleFileList fileindex = GuiServer.serverGetLoadableKbs();
      String filename = PLModuleFileList.findFilenameForKb(fileindex, kbname);
      PLString result = PLString.new_PLString();

      if (filename != null) {
        {
          Stella.STANDARD_OUTPUT.nativeStream.println("Saving KB: " + modulename + " to " + filename);
          { OutputFileStream stream = OutputFileStream.newOutputFileStream(filename);

            Logic.doSaveModule(module, stream);
            stream.free();
          }
        }
      }
      else {
        { String newfile = GuiServer.$KB_DIRECTORY$ + kbname + ".ploom";
          Cons newindex = Cons.cons(Cons.cons(StringWrapper.wrapString(kbname), Cons.cons(StringWrapper.wrapString(modulename), Cons.cons(StringWrapper.wrapString(newfile), Cons.cons(StringWrapper.wrapString(description), Stella.NIL)))), rawfileindex);

          GuiServer.saveIndexFile(newindex);
          Stella.STANDARD_OUTPUT.nativeStream.println("Saving new KB: " + modulename + " to " + newfile);
          { OutputFileStream stream = OutputFileStream.newOutputFileStream(newfile);

            Logic.doSaveModule(module, stream);
            stream.free();
          }
          Stella.STANDARD_OUTPUT.nativeStream.println("new index: " + newindex);
        }
      }
      result.Value = "OK";
      return (result);
    }
  }

  public static PLString serverLoadKb(PLString plkbname) {
    Stella.STANDARD_OUTPUT.nativeStream.println("in server-load-kb");
    { String kbname = plkbname.Value;
      PLModuleFileList fileindex = GuiServer.serverGetLoadableKbs();
      String filename = PLModuleFileList.findFilenameForKb(fileindex, kbname);
      PLString result = PLString.new_PLString();

      Stella.STANDARD_OUTPUT.nativeStream.println("kbName is:" + kbname);
      Stella.STANDARD_OUTPUT.nativeStream.println("fileName is:" + filename);
      if (filename != null) {
        {
          Stella.STANDARD_OUTPUT.nativeStream.println("Loading KB: " + filename);
          Logic.load(filename, Stella.NIL);
          result.Value = "OK";
        }
      }
      else {
        {
          Stella.STANDARD_OUTPUT.nativeStream.print("Error: couldn't find fileName for " + kbname);
          result.Value = "ERROR";
        }
      }
      return (result);
    }
  }

  /** Evaluate 'commandString' and return the result
   * @param modulename
   * @param commandstring
   * @return PLString
   */
  public static PLString serverEvaluateLogicCommand(PLString modulename, PLString commandstring) {
    { String command = commandstring.Value;
      String module = modulename.Value;
      String evalresult = null;
      PLString result = PLString.new_PLString();

      evalresult = GuiServer.evaluateLogicCommandInModule(command, module, true);
      result.Value = GuiServer.xmlifyString(evalresult);
      return (result);
    }
  }

  /** Get all the propositions for a given instance and relation
   * @param modulename
   * @param instancename
   * @param relationname
   * @return PLPropositionContainer
   */
  public static PLPropositionContainer serverGetPropositionsForInstanceAndRelation(PLString modulename, PLString instancename, PLString relationname) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { List propositions = GuiServer.getPropositionsForInstanceAndRelation(modulename.Value, instancename.Value, relationname.Value);
            List xmlinstances = List.newList();
            PLPropositionContainer result = PLPropositionContainer.new_PLPropositionContainer();

            xmlinstances = GuiServer.makePlPropositions(propositions, module, false);
            result.PLProposition = xmlinstances;
            return (result);
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Get all the rules for a given relation
   * @param modulename
   * @param instancename
   * @return PLPropositionContainer
   */
  public static PLPropositionContainer serverGetRulesForRelation(PLString modulename, PLString instancename) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { List propositions = GuiServer.getRelevantRulesForRelation(modulename.Value, instancename.Value);
            List xmlinstances = List.newList();
            PLPropositionContainer result = PLPropositionContainer.new_PLPropositionContainer();

            xmlinstances = GuiServer.makePlPropositions(propositions, module, true);
            result.PLProposition = xmlinstances;
            return (result);
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Get all the rules for a given concept
   * @param modulename
   * @param instancename
   * @return PLPropositionContainer
   */
  public static PLPropositionContainer serverGetRulesForConcept(PLString modulename, PLString instancename) {
    return (PLString.serverGetRulesForRelation(modulename, instancename));
  }

  /** Get all the propositions for a given relation
   * @param modulename
   * @param instancename
   * @return PLPropositionContainer
   */
  public static PLPropositionContainer serverGetPropositionsForRelation(PLString modulename, PLString instancename) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { List propositions = GuiServer.getPropositionsForObject(modulename.Value, instancename.Value, true);
            List xmlinstances = List.newList();
            PLPropositionContainer result = PLPropositionContainer.new_PLPropositionContainer();

            xmlinstances = GuiServer.makePlPropositions(propositions, module, false);
            result.PLProposition = xmlinstances;
            return (result);
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Get all the propositions for a given concept
   * @param modulename
   * @param instancename
   * @return PLPropositionContainer
   */
  public static PLPropositionContainer serverGetPropositionsForConcept(PLString modulename, PLString instancename) {
    return (PLString.serverGetPropositionsForRelation(modulename, instancename));
  }

  /** Get the documentation string for module+instance.
   * @param modulename
   * @param instancename
   * @return PLString
   */
  public static PLString serverGetDocumentationForInstance(PLString modulename, PLString instancename) {
    return (GuiServer.getDocumentationForObject(modulename.Value, instancename.Value));
  }

  /** Get all the types of an instance.
   * @param modulename
   * @param instancename
   * @return PLSurrogateCollection
   */
  public static PLSurrogateCollection serverGetTypesForInstance(PLString modulename, PLString instancename) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);
      Stella_Object instance = edu.isi.powerloom.PLI.sGetObject(GuiServer.guiNameToPlName(instancename.Value), modulename.Value, null);
      List types = edu.isi.powerloom.PLI.getDirectTypes(((LogicObject)(instance)), module, null).listify();

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          return (GuiServer.createSurrogateCollectionForLogicObject(types));

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Get all the propositions for a given instance
   * @param modulename
   * @param instancename
   * @return PLPropositionContainer
   */
  public static PLPropositionContainer serverGetPropositionsForInstance(PLString modulename, PLString instancename) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { List propositions = GuiServer.getPropositionsForObject(modulename.Value, instancename.Value, false);
            List xmlinstances = List.newList();
            PLPropositionContainer result = PLPropositionContainer.new_PLPropositionContainer();

            xmlinstances = GuiServer.makePlPropositions(propositions, module, false);
            result.PLProposition = xmlinstances;
            return (result);
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Get all the relations which have 'conceptName' as a subtype of their domain
   * @param modulename
   * @param conceptname
   * @return PLRelationContainer
   */
  public static PLRelationContainer serverGetInheritedRelationsForConcept(PLString modulename, PLString conceptname) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { LogicObject concept = edu.isi.powerloom.PLI.getConcept(conceptname.Value, module, null);
            List xmlinstances = List.newList();
            List relations = GuiServer.getInheritedRelationsForConcept(module, concept);
            PLRelationContainer container = PLRelationContainer.new_PLRelationContainer();

            xmlinstances = GuiServer.makePlRelations(relations, modulename.Value);
            container.PLRelation = xmlinstances;
            return (container);
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Get all the direct relations which have 'conceptName' as their domain
   * @param modulename
   * @param conceptname
   * @return PLRelationContainer
   */
  public static PLRelationContainer serverGetRelationsForConcept(PLString modulename, PLString conceptname) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { LogicObject concept = edu.isi.powerloom.PLI.getConcept(conceptname.Value, module, null);
            List xmlinstances = List.newList();
            List relations = GuiServer.getDirectRelationsForConcept(module, concept);
            PLRelationContainer container = PLRelationContainer.new_PLRelationContainer();

            xmlinstances = GuiServer.makePlRelations(relations, modulename.Value);
            container.PLRelation = xmlinstances;
            return (container);
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Get all the propositions for a given module
   * @param modulename
   * @return PLPropositionContainer
   */
  public static PLPropositionContainer serverGetPropositionsForModule(PLString modulename) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { edu.isi.powerloom.PlIterator iter = edu.isi.powerloom.PLI.getPropositionsInModule(module, null);
            List propositions = List.newList();
            PLPropositionContainer result = PLPropositionContainer.new_PLPropositionContainer();
            List xmlinstances = List.newList();

            { Proposition proposition = null;
              edu.isi.powerloom.PlIterator iter000 = iter;
              Cons collect000 = null;

              while (iter000.nextP()) {
                proposition = ((Proposition)(iter000.value));
                if (collect000 == null) {
                  {
                    collect000 = Cons.cons(proposition, Stella.NIL);
                    if (propositions.theConsList == Stella.NIL) {
                      propositions.theConsList = collect000;
                    }
                    else {
                      Cons.addConsToEndOfConsList(propositions.theConsList, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000.rest = Cons.cons(proposition, Stella.NIL);
                    collect000 = collect000.rest;
                  }
                }
              }
            }
            xmlinstances = GuiServer.makePlPropositions(propositions, module, false);
            result.PLProposition = xmlinstances;
            return (result);
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Get the superrelations for module+relation
   * @param modulename
   * @param relationname
   * @return PLVariableList
   */
  public static PLVariableList serverGetVariablesForRelation(PLString modulename, PLString relationname) {
    { LogicObject relation = edu.isi.powerloom.PLI.sGetRelation(GuiServer.guiNameToPlName(relationname.Value), modulename.Value, null);

      return (GuiServer.createVariablesList(relation));
    }
  }

  /** Get the uses for module
   * @param modulename
   * @return PLSurrogateCollection
   */
  public static PLSurrogateCollection serverGetShadowedSurrogatesForModule(PLString modulename) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      return (GuiServer.createSurrogateCollection(module.shadowedSurrogates()));
    }
  }

  /** Get the uses for module
   * @param modulename
   * @return PLSurrogateCollection
   */
  public static PLSurrogateCollection serverGetUsesForModule(PLString modulename) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      return (GuiServer.createModuleCollection(module.uses));
    }
  }

  /** Get the includes for module
   * @param modulename
   * @return PLSurrogateCollection
   */
  public static PLSurrogateCollection serverGetIncludesForModule(PLString modulename) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      return (GuiServer.createModuleCollection(edu.isi.powerloom.PLI.getParentModules(module).listify()));
    }
  }

  /** Get the superrelations for module+relation
   * @param modulename
   * @param relationname
   * @return PLSurrogateCollection
   */
  public static PLSurrogateCollection serverGetSuperrelationsForRelation(PLString modulename, PLString relationname) {
    { LogicObject relation = edu.isi.powerloom.PLI.sGetRelation(GuiServer.guiNameToPlName(relationname.Value), modulename.Value, null);
      Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      return (GuiServer.createSuperrelationsContainer(relation, module));
    }
  }

  /** Get the superconcepts for module+concept
   * @param modulename
   * @param conceptname
   * @return PLSurrogateCollection
   */
  public static PLSurrogateCollection serverGetSuperconceptsForConcept(PLString modulename, PLString conceptname) {
    { LogicObject concept = edu.isi.powerloom.PLI.sGetConcept(GuiServer.guiNameToPlName(conceptname.Value), modulename.Value, null);
      Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);

      return (GuiServer.createSuperrelationsContainer(concept, module));
    }
  }

  /** Get the documentation string for module+relation
   * @param modulename
   * @param relationname
   * @return PLString
   */
  public static PLString serverGetDocumentationForRelation(PLString modulename, PLString relationname) {
    return (GuiServer.getDocumentationForObject(modulename.Value, relationname.Value));
  }

  /** Get the source string for module+concept
   * @param modulename
   * @param conceptname
   * @return PLString
   */
  public static PLString serverGetSourceForConcept(PLString modulename, PLString conceptname) {
    { PLString result = PLString.new_PLString();
      String source = Logic.stringifiedSource(edu.isi.powerloom.PLI.sGetConcept(GuiServer.guiNameToPlName(conceptname.Value), modulename.Value, null));

      result.Value = GuiServer.xmlifyString(source);
      return (result);
    }
  }

  /** Get the documentation string for module+concept
   * @param modulename
   * @param conceptname
   * @return PLString
   */
  public static PLString serverGetDocumentationForConcept(PLString modulename, PLString conceptname) {
    return (GuiServer.getDocumentationForObject(modulename.Value, conceptname.Value));
  }

  /** Get all the instances for a given module+concept
   * @param modulename
   * @param conceptname
   * @return PLInstanceContainer
   */
  public static PLInstanceContainer serverGetDirectInstancesForConcept(PLString modulename, PLString conceptname) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);
      edu.isi.powerloom.PlIterator iter = edu.isi.powerloom.PLI.getDirectConceptInstances(edu.isi.powerloom.PLI.getConcept(conceptname.Value, module, null), module, null);
      List instances = List.newList();
      PLInstanceContainer result = PLInstanceContainer.new_PLInstanceContainer();
      List xmlinstances = List.newList();

      { Stella_Object instance = null;
        edu.isi.powerloom.PlIterator iter000 = iter;
        Cons collect000 = null;

        while (iter000.nextP()) {
          instance = iter000.value;
          if (collect000 == null) {
            {
              collect000 = Cons.cons(instance, Stella.NIL);
              if (instances.theConsList == Stella.NIL) {
                instances.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(instances.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(instance, Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      xmlinstances = GuiServer.makePlInstances(instances, true);
      xmlinstances = xmlinstances.sort(Native.find_java_method("edu.isi.powerloom.server.gui.PLInstance", "PLInstanceL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLInstance"), Native.find_java_class("edu.isi.powerloom.server.gui.PLInstance")}));
      result.PLInstance = xmlinstances;
      return (result);
    }
  }

  /** Get all the instances for a given module+concept
   * @param modulename
   * @param conceptname
   * @return PLInstanceContainer
   */
  public static PLInstanceContainer serverGetInstancesForConcept(PLString modulename, PLString conceptname) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename.Value, null);
      edu.isi.powerloom.PlIterator iter = edu.isi.powerloom.PLI.getConceptInstances(edu.isi.powerloom.PLI.getConcept(conceptname.Value, module, null), module, null);
      List instances = List.newList();
      PLInstanceContainer result = PLInstanceContainer.new_PLInstanceContainer();
      List xmlinstances = List.newList();

      { Stella_Object instance = null;
        edu.isi.powerloom.PlIterator iter000 = iter;
        Cons collect000 = null;

        while (iter000.nextP()) {
          instance = iter000.value;
          if (collect000 == null) {
            {
              collect000 = Cons.cons(instance, Stella.NIL);
              if (instances.theConsList == Stella.NIL) {
                instances.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(instances.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(instance, Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      xmlinstances = GuiServer.makePlInstances(instances, true);
      xmlinstances = xmlinstances.sort(Native.find_java_method("edu.isi.powerloom.server.gui.PLInstance", "PLInstanceL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLInstance"), Native.find_java_class("edu.isi.powerloom.server.gui.PLInstance")}));
      result.PLInstance = xmlinstances;
      return (result);
    }
  }

  /** Get all the relations in a module and included/used modules that begin with 'prefix'
   * @param plmodule
   * @param prefix
   * @return PLRelationContainer
   */
  public static PLRelationContainer serverGetRelationCompletions(PLString plmodule, PLString prefix) {
    { Module module = edu.isi.powerloom.PLI.getModule(plmodule.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          return (GuiServer.getRelationsWithPrefix(module, prefix.Value));

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Get all the relations in a module, structured hierarchically
   * @param plstring
   * @return PLRelationContainer
   */
  public static PLRelationContainer serverGetRelationsForModule(PLString plstring) {
    { Module module = edu.isi.powerloom.PLI.getModule(plstring.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          return (GuiServer.getRelations(module));

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Get all the instances begining with 'prefix' in all modules accessible from 'plModule'.
   * @param plmodule
   * @param prefix
   * @return PLInstanceContainer
   */
  public static PLInstanceContainer serverGetInstanceCompletions(PLString plmodule, PLString prefix) {
    { Module module = edu.isi.powerloom.PLI.getModule(plmodule.Value, null);
      Iterator allinstances = Logic.allInstances(module, false);
      List nonskoleminstances = List.newList();
      PLInstanceContainer result = PLInstanceContainer.new_PLInstanceContainer();
      List xmlinstances = List.newList();
      String downcasedprefix = Native.stringDowncase(prefix.Value);

      { LogicObject instance = null;
        Iterator iter000 = allinstances;
        Cons collect000 = null;

        while (iter000.nextP()) {
          instance = ((LogicObject)(iter000.value));
          if ((!Logic.skolemP(instance)) &&
              Stella.startsWithP(GuiServer.getLogicObjectName(instance, "FALSE"), downcasedprefix, 0)) {
            if (collect000 == null) {
              {
                collect000 = Cons.cons(instance, Stella.NIL);
                if (nonskoleminstances.theConsList == Stella.NIL) {
                  nonskoleminstances.theConsList = collect000;
                }
                else {
                  Cons.addConsToEndOfConsList(nonskoleminstances.theConsList, collect000);
                }
              }
            }
            else {
              {
                collect000.rest = Cons.cons(instance, Stella.NIL);
                collect000 = collect000.rest;
              }
            }
          }
        }
      }
      xmlinstances = GuiServer.makePlInstances(nonskoleminstances, true);
      xmlinstances = xmlinstances.sort(Native.find_java_method("edu.isi.powerloom.server.gui.PLInstance", "PLInstanceL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLInstance"), Native.find_java_class("edu.isi.powerloom.server.gui.PLInstance")}));
      result.PLInstance = xmlinstances;
      return (result);
    }
  }

  /** Get all the instances in a module, excluding skolems
   * @param plstring
   * @return PLInstanceContainer
   */
  public static PLInstanceContainer serverGetInstancesForModule(PLString plstring) {
    { Module module = edu.isi.powerloom.PLI.getModule(plstring.Value, null);
      Iterator allinstances = Logic.allInstances(module, true);
      List nonskoleminstances = List.newList();
      PLInstanceContainer result = PLInstanceContainer.new_PLInstanceContainer();
      List xmlinstances = List.newList();

      { LogicObject instance = null;
        Iterator iter000 = allinstances;
        Cons collect000 = null;

        while (iter000.nextP()) {
          instance = ((LogicObject)(iter000.value));
          if (!Logic.skolemP(instance)) {
            if (collect000 == null) {
              {
                collect000 = Cons.cons(instance, Stella.NIL);
                if (nonskoleminstances.theConsList == Stella.NIL) {
                  nonskoleminstances.theConsList = collect000;
                }
                else {
                  Cons.addConsToEndOfConsList(nonskoleminstances.theConsList, collect000);
                }
              }
            }
            else {
              {
                collect000.rest = Cons.cons(instance, Stella.NIL);
                collect000 = collect000.rest;
              }
            }
          }
        }
      }
      xmlinstances = GuiServer.makePlInstances(nonskoleminstances, true);
      xmlinstances = xmlinstances.sort(Native.find_java_method("edu.isi.powerloom.server.gui.PLInstance", "PLInstanceL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLInstance"), Native.find_java_class("edu.isi.powerloom.server.gui.PLInstance")}));
      result.PLInstance = xmlinstances;
      return (result);
    }
  }

  /** Get all the concepts in a module and included/used modules that begin with 'prefix'
   * @param plmodule
   * @param prefix
   * @return PLConceptContainer
   */
  public static PLConceptContainer serverGetConceptCompletions(PLString plmodule, PLString prefix) {
    { Module module = edu.isi.powerloom.PLI.getModule(plmodule.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          return (GuiServer.getConceptsWithPrefix(module, prefix.Value));

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  /** Get all the concepts in a module, structured hierarchically
   * @param plstring
   * @return PLConceptContainer
   */
  public static PLConceptContainer serverGetConceptsForModule(PLString plstring) {
    { Module module = edu.isi.powerloom.PLI.getModule(plstring.Value, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          return (GuiServer.getConcepts(module));

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  public static Stella_Object access_PLString_Slot_Value(PLString self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == GuiServer.SYM_GUI_SERVER_Value) {
      if (setvalueP) {
        self.Value = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.Value);
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
    { PLString self = this;

      return (GuiServer.SGT_GUI_SERVER_PLString);
    }
  }

}

