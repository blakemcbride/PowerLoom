//  -*- Mode: Java -*-
//
// GuiServer.java

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

public class GuiServer {
  public static Surrogate SGT_GUI_SERVER_PLString = null;

  public static Symbol SYM_GUI_SERVER_Value = null;

  public static Surrogate SGT_GUI_SERVER_PLSurrogate = null;

  public static Symbol SYM_LOGIC_ID = null;

  public static Surrogate SGT_GUI_SERVER_ServerException = null;

  public static Symbol SYM_GUI_SERVER_Type = null;

  public static Symbol SYM_GUI_SERVER_Message = null;

  public static Surrogate SGT_GUI_SERVER_PLModuleContainer = null;

  public static Symbol SYM_GUI_SERVER_PLModule = null;

  public static Surrogate SGT_GUI_SERVER_PLModule = null;

  public static Symbol SYM_GUI_SERVER_ModuleName = null;

  public static Symbol SYM_GUI_SERVER_SourceString = null;

  public static Symbol SYM_GUI_SERVER_CppPackage = null;

  public static Symbol SYM_GUI_SERVER_LispPackage = null;

  public static Symbol SYM_GUI_SERVER_JavaPackage = null;

  public static Symbol SYM_GUI_SERVER_JavaCatchallClass = null;

  public static Symbol SYM_GUI_SERVER_Documentation = null;

  public static Symbol SYM_GUI_SERVER_API = null;

  public static Symbol SYM_GUI_SERVER_CaseSensitive = null;

  public static Symbol SYM_GUI_SERVER_PLSurrogate = null;

  public static Surrogate SGT_GUI_SERVER_PLConcept = null;

  public static Symbol SYM_GUI_SERVER_ConceptName = null;

  public static Symbol SYM_GUI_SERVER_Module = null;

  public static Symbol SYM_GUI_SERVER_PLConcept = null;

  public static Surrogate SGT_GUI_SERVER_PLConceptContainer = null;

  public static Surrogate SGT_GUI_SERVER_PLRelation = null;

  public static Symbol SYM_GUI_SERVER_RelationName = null;

  public static Symbol SYM_GUI_SERVER_IsFunction = null;

  public static Symbol SYM_GUI_SERVER_IsClosed = null;

  public static Symbol SYM_GUI_SERVER_PLRelation = null;

  public static Surrogate SGT_GUI_SERVER_PLRelationContainer = null;

  public static Surrogate SGT_GUI_SERVER_PLInstance = null;

  public static Symbol SYM_GUI_SERVER_InstanceName = null;

  public static Surrogate SGT_GUI_SERVER_PLInstanceContainer = null;

  public static Symbol SYM_GUI_SERVER_PLInstance = null;

  public static Surrogate SGT_GUI_SERVER_PLProposition = null;

  public static Symbol SYM_GUI_SERVER_PropositionName = null;

  public static Symbol SYM_GUI_SERVER_IsStrict = null;

  public static Symbol SYM_GUI_SERVER_IsAsserted = null;

  public static Symbol SYM_GUI_SERVER_IsRule = null;

  public static Surrogate SGT_GUI_SERVER_PLPropositionContainer = null;

  public static Symbol SYM_GUI_SERVER_PLProposition = null;

  public static Surrogate SGT_GUI_SERVER_PLRule = null;

  public static Symbol SYM_GUI_SERVER_RuleName = null;

  public static Surrogate SGT_GUI_SERVER_PLVariable = null;

  public static Symbol SYM_GUI_SERVER_VariableName = null;

  public static Symbol SYM_GUI_SERVER_VariableType = null;

  public static Surrogate SGT_GUI_SERVER_PLVariableList = null;

  public static Symbol SYM_GUI_SERVER_PLVariable = null;

  public static Surrogate SGT_GUI_SERVER_PLModuleFileList = null;

  public static Symbol SYM_GUI_SERVER_PLModuleFile = null;

  public static Surrogate SGT_GUI_SERVER_PLModuleFile = null;

  public static Symbol SYM_GUI_SERVER_KBName = null;

  public static Symbol SYM_GUI_SERVER_KBDescription = null;

  public static Symbol SYM_GUI_SERVER_FileName = null;

  public static Surrogate SGT_GUI_SERVER_PLFile = null;

  public static Symbol SYM_GUI_SERVER_PLFileContent = null;

  public static Surrogate SGT_GUI_SERVER_PLFileContent = null;

  public static Surrogate SGT_GUI_SERVER_PLDirectory = null;

  public static Symbol SYM_GUI_SERVER_DirectoryName = null;

  public static Surrogate SGT_GUI_SERVER_PLDirectoryContents = null;

  public static Symbol SYM_GUI_SERVER_PLDirectory = null;

  public static Symbol SYM_GUI_SERVER_PLFile = null;

  public static Surrogate SGT_GUI_SERVER_PLSurrogateCollection = null;

  public static Surrogate SGT_GUI_SERVER_PLObjectUnion = null;

  public static Symbol SYM_GUI_SERVER_LiteralValue = null;

  public static Surrogate SGT_GUI_SERVER_PLTuple = null;

  public static Symbol SYM_GUI_SERVER_PLObjectUnion = null;

  public static Surrogate SGT_GUI_SERVER_PLQuery = null;

  public static Symbol SYM_GUI_SERVER_IsAsk = null;

  public static Symbol SYM_GUI_SERVER_QueryName = null;

  public static Symbol SYM_GUI_SERVER_Query = null;

  public static Symbol SYM_GUI_SERVER_InferenceLevel = null;

  public static Symbol SYM_GUI_SERVER_Timeout = null;

  public static Symbol SYM_GUI_SERVER_Moveout = null;

  public static Symbol SYM_GUI_SERVER_MatchMode = null;

  public static Symbol SYM_GUI_SERVER_NumResults = null;

  public static Symbol SYM_GUI_SERVER_MinScore = null;

  public static Symbol SYM_GUI_SERVER_MaxUnknowns = null;

  public static Symbol SYM_GUI_SERVER_MaximizeScore = null;

  public static Symbol SYM_GUI_SERVER_DontOptimize = null;

  public static Surrogate SGT_GUI_SERVER_PLQueryResult = null;

  public static Symbol SYM_GUI_SERVER_PLTuple = null;

  public static Surrogate SGT_GUI_SERVER_PLSearchParameter = null;

  public static Symbol SYM_GUI_SERVER_SearchString = null;

  public static Symbol SYM_GUI_SERVER_SearchConcept = null;

  public static Symbol SYM_GUI_SERVER_SearchRelation = null;

  public static Symbol SYM_GUI_SERVER_SearchInstance = null;

  public static Surrogate SGT_GUI_SERVER_PLSearchResult = null;

  public static Symbol SYM_GUI_SERVER_PLSearchResultItem = null;

  public static Surrogate SGT_GUI_SERVER_PLSearchResultItem = null;

  public static Surrogate SGT_GUI_SERVER_PLServerInfo = null;

  public static Symbol SYM_GUI_SERVER_AllowRemoteFileBrowsing = null;

  public static Symbol SYM_GUI_SERVER_STARTUP_XML_OBJECTS = null;

  public static Symbol SYM_STELLA_METHOD_STARTUP_CLASSNAME = null;

  public static boolean $ALLOW_REMOTE_FILEBROWSING$ = false;

  public static String $SERVER_LOG_FILE$ = "PL:logs;powerloom-server.log";

  public static Keyword KWD_LOG_LEVELS = null;

  public static Keyword KWD_LEVEL = null;

  public static Keyword KWD_DEVELOPMENT = null;

  public static Keyword KWD_HIGH = null;

  public static Keyword KWD_LOW = null;

  public static Keyword KWD_PREFIX = null;

  public static Keyword KWD_MAX_WIDTH = null;

  public static Keyword KWD_STREAM = null;

  public static int $QUERY_SESSION_TIMEOUT$ = 86400;

  public static Surrogate SGT_LOGIC_LOGIC_OBJECT = null;

  public static Surrogate SGT_STELLA_CONS = null;

  public static Surrogate SGT_LOGIC_TRUTH_VALUE = null;

  public static Surrogate SGT_LOGIC_NAMED_DESCRIPTION = null;

  public static Surrogate SGT_LOGIC_SKOLEM = null;

  public static Symbol SYM_STELLA_CODE_ONLYp = null;

  public static Symbol SYM_STELLA_JAVA_FLOTSAM_CLASS = null;

  public static Symbol SYM_STELLA_APIp = null;

  public static Surrogate SGT_STELLA_LITERAL = null;

  public static Keyword KWD_FORALL = null;

  public static Keyword KWD_EXISTS = null;

  public static Keyword KWD_IMPLIES = null;

  public static Symbol SYM_LOGIC_MASTER_PROPOSITION = null;

  public static Symbol SYM_STELLA_ASK = null;

  public static Keyword KWD_ORIGINAL = null;

  public static String $KB_FILENAME_INDEX$ = "PL:kbs;kbs.ste";

  public static String $KB_DIRECTORY$ = "PL:kbs;";

  public static Symbol SYM_GUI_SERVER_WILD = null;

  public static String $DEFAULT_KB_DIRECTORY$ = "/nfs/topaz/melz/";

  /** Hash Table for used for dispatching server API methods.
   */
  public static StringHashTable $SERVER_DISPATCH_TABLE$ = null;

  public static Symbol SYM_GUI_SERVER_STARTUP_GUI_SERVER_API = null;

  public static Module $GUI_SERVER_MODULE$ = null;

  public static String $SOAP_RESULT_PREFIX$ = "<?xml version='1.0' encoding='UTF-8'?><env:Envelope xmlns:env='http://schemas.xmlsoap.org/soap/envelope/' xmlns:xsd='http://www.w3.org/2001/XMLSchema' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:enc='http://schemas.xmlsoap.org/soap/encoding/' xmlns:ns0='http://hello.org/wsdl' env:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'><env:Body><response><result><![CDATA[";

  public static String $SOAP_EXCEPTION_PREFIX$ = "<?xml version='1.0' encoding='UTF-8'?><env:Envelope xmlns:env='http://schemas.xmlsoap.org/soap/envelope/' xmlns:xsd='http://www.w3.org/2001/XMLSchema' xmlns:xsi='http://www.w3.org/2001/XMLSchema-instance' xmlns:enc='http://schemas.xmlsoap.org/soap/encoding/' xmlns:ns0='http://hello.org/wsdl' env:encodingStyle='http://schemas.xmlsoap.org/soap/encoding/'><env:Body><response><exception><![CDATA[";

  public static String $SOAP_RESULT_SUFFIX$ = "]]></result></response></env:Body></env:Envelope>";

  public static String $SOAP_EXCEPTION_SUFFIX$ = "]]></exception></response></env:Body></env:Envelope>";

  public static Keyword KWD_CONTENT_TYPE = null;

  public static Keyword KWD_XML = null;

  public static Keyword KWD_DOCUMENTATION = null;

  public static Symbol SYM_GUI_SERVER_STARTUP_GUI_SERVER = null;

  public static Keyword KWD_KIF = null;

  public static Surrogate SGT_LOGIC_PROPOSITION = null;

  public static Keyword KWD_ISA = null;

  public static Keyword KWD_FUNCTION = null;

  public static Keyword KWD_PREDICATE = null;

  public static Keyword KWD_NOT = null;

  public static Keyword KWD_EQUIVALENT = null;

  public static Surrogate SGT_STELLA_LITERAL_WRAPPER = null;

  public static Surrogate SGT_LOGIC_PATTERN_VARIABLE = null;

  public static Surrogate SGT_STELLA_GENERALIZED_SYMBOL = null;

  public static Surrogate SGT_STELLA_MODULE = null;

  public static Surrogate SGT_STELLA_THING = null;

  /** The action parameter for URL printing
   */
  public final static StellaSpecialVariable $PLGUI_URL_ACTION$ = new StellaSpecialVariable();

  public static Keyword KWD_JAVA_GUI_HTML = null;

  public static Keyword KWD_HTML = null;

  public static Keyword KWD_LAY = null;

  public static Keyword KWD_KIF_ONTOSAURUS = null;

  public static Keyword KWD_BRIEF = null;

  public static String $PLGUI_EXPLANATION_TRACE_FILE$ = null;

  public static Symbol SYM_GUI_SERVER_STARTUP_EXPLANATIONS = null;

  public static void serverLog(Keyword loglevel, Cons message) {
    Stella.logMessage("PL-Server", loglevel, message);
  }

  public static String plObjectToGuiName(Stella_Object x) {
    { Module homemodule = x.homeModule();
      Surrogate surrogate = Logic.objectSurrogate(x);

      if ((surrogate == null) &&
          Stella_Object.surrogateP(x)) {
        surrogate = ((Surrogate)(x));
      }
      if (surrogate != null) {
        if (!(homemodule == ((Module)(surrogate.homeContext)))) {
          return (((Module)(surrogate.homeContext)).moduleName + "/" + surrogate.symbolName);
        }
        else {
          return (surrogate.symbolName);
        }
      }
      else {
        return (edu.isi.powerloom.PLI.objectToString(x));
      }
    }
  }

  public static String guiNameToPlName(String name) {
    if (Stella.qualifiedStellaNameP(name)) {
      { String barename = null;
        String module = null;
        Keyword type = null;

        { Object [] caller_MV_returnarray = new Object[2];

          barename = Stella.parseStellaName(name, false, caller_MV_returnarray);
          module = ((String)(((StringWrapper)(caller_MV_returnarray[0])).wrapperValue));
          type = ((Keyword)(caller_MV_returnarray[1]));
        }
        type = type;
        if (barename.charAt(0) == '|') {
          return (module + "/" + barename + "");
        }
        else {
          return (module + "/|" + barename + "|");
        }
      }
    }
    else {
      if (name.charAt(0) == '|') {
        return (name);
      }
      else {
        return ("|" + name + "|");
      }
    }
  }

  /** Get all the loaded modules, structured, hierarchically
   * @return PLModuleContainer
   */
  public static PLModuleContainer serverGetModules() {
    { Module rootmodule = Stella.$ROOT_MODULE$;

      return (GuiServer.getModules(rootmodule));
    }
  }

  public static PLModuleFileList serverGetLoadableKbs() {
    { Cons filedescriptions = GuiServer.loadIndexFile();
      PLModuleFileList result = PLModuleFileList.new_PLModuleFileList();
      List plfiles = List.newList();

      { Cons desc = null;
        Cons iter000 = filedescriptions;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          desc = ((Cons)(iter000.value));
          plfiles.insert(GuiServer.makePlFile(desc));
        }
      }
      result.PLModuleFile = plfiles;
      return (result);
    }
  }

  /** Return a data structure describing the characteristics and capabilities of this server instance.
   * @return PLServerInfo
   */
  public static PLServerInfo serverGetInfo() {
    { PLServerInfo result = PLServerInfo.new_PLServerInfo();

      if (GuiServer.$ALLOW_REMOTE_FILEBROWSING$) {
        result.AllowRemoteFileBrowsing = "TRUE";
      }
      else {
        result.AllowRemoteFileBrowsing = "FALSE";
      }
      return (result);
    }
  }

  public static String extractModuleNameFromStream(InputStream stream) {
    { Stella_Object tree = null;
      SExpressionIterator iter000 = InputStream.sExpressions(stream);
      int i = Stella.NULL_INTEGER;
      int iter001 = 1;
      int upperBound000 = 20;

      for (;iter000.nextP() &&
                (iter001 <= upperBound000); iter001 = iter001 + 1) {
        tree = iter000.value;
        i = iter001;
        i = i;
        if (Stella_Object.safePrimaryType(tree) == GuiServer.SGT_STELLA_CONS) {
          { Cons tree000 = ((Cons)(tree));

            { Stella_Object operator = tree000.value;
              String modulename = null;

              if (Surrogate.subtypeOfSymbolP(Stella_Object.safePrimaryType(operator))) {
                { Symbol operator000 = ((Symbol)(operator));

                  if (Stella.stringEqlP((((Module)(Stella.$MODULE$.get())).caseSensitiveP ? Native.stringUpcase(operator000.symbolName) : operator000.symbolName), "IN-MODULE")) {
                    modulename = Stella_Object.coerceToModuleName(tree000.rest.value, false);
                    if (modulename == null) {
                      { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

                        stream000.nativeStream.print("Illegal IN-MODULE declaration: `" + tree000 + "'");
                        throw ((ReadException)(ReadException.newReadException(stream000.theStringReader()).fillInStackTrace()));
                      }
                    }
                    else {
                      return (modulename);
                    }
                  }
                  else {
                  }
                }
              }
              else {
              }
            }
          }
        }
        else {
        }
      }
    }
    return ("**NOTFOUND**");
  }

  public static String extractModuleNameFromFile(String filename) {
    { String modulename = null;

      { InputFileStream in = null;

        try {
          in = Stella.openInputFile(filename, Stella.NIL);
          modulename = GuiServer.extractModuleNameFromStream(in);

        } finally {
          if (in != null) {
            in.free();
          }
        }
      }
      return (modulename);
    }
  }

  public static PLTuple makePlTupleFromProposition(Proposition proposition) {
    { Vector arguments = proposition.arguments;
      List plobjectunions = List.newList();
      PLTuple result = PLTuple.new_PLTuple();

      { Stella_Object argument = null;
        Vector vector000 = arguments;
        int index000 = 0;
        int length000 = vector000.length();
        Cons collect000 = null;

        for (;index000 < length000; index000 = index000 + 1) {
          argument = (vector000.theArray)[index000];
          if (collect000 == null) {
            {
              collect000 = Cons.cons(GuiServer.makePlObjectUnion(argument), Stella.NIL);
              if (plobjectunions.theConsList == Stella.NIL) {
                plobjectunions.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(plobjectunions.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(GuiServer.makePlObjectUnion(argument), Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      result.PLObjectUnion = plobjectunions;
      return (result);
    }
  }

  public static PLTuple makePlTuple(Cons tuple) {
    { PLTuple result = PLTuple.new_PLTuple();
      List plobjectunions = List.newList();

      { Stella_Object renamed_Object = null;
        Cons iter000 = tuple;
        Cons collect000 = null;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          renamed_Object = iter000.value;
          if (collect000 == null) {
            {
              collect000 = Cons.cons(GuiServer.makePlObjectUnion(renamed_Object), Stella.NIL);
              if (plobjectunions.theConsList == Stella.NIL) {
                plobjectunions.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(plobjectunions.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(GuiServer.makePlObjectUnion(renamed_Object), Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      result.PLObjectUnion = plobjectunions;
      return (result);
    }
  }

  public static PLObjectUnion makePlObjectUnion(Stella_Object renamed_Object) {
    { PLObjectUnion result = PLObjectUnion.new_PLObjectUnion();

      result.LiteralValue = "";
      result.Type = "";
      if (renamed_Object == null) {
        result.LiteralValue = "";
        result.Type = "STRING";
        return (result);
      }
      if (Logic.skolemP(renamed_Object) &&
          (((Stella_Object)(Stella_Object.accessInContext(((Skolem)(renamed_Object)).variableValue, ((Skolem)(renamed_Object)).homeContext, false))) != null)) {
        renamed_Object = ((Stella_Object)(Stella_Object.accessInContext(((Skolem)(renamed_Object)).variableValue, ((Skolem)(renamed_Object)).homeContext, false)));
      }
      { Surrogate testValue000 = Stella_Object.safePrimaryType(renamed_Object);

        if (Surrogate.subtypeOfIntegerP(testValue000)) {
          { IntegerWrapper object000 = ((IntegerWrapper)(renamed_Object));

            result.LiteralValue = Native.stringify(IntegerWrapper.wrapInteger(object000.wrapperValue));
            result.Type = "INTEGER";
          }
        }
        else if (Surrogate.subtypeOfFloatP(testValue000)) {
          { FloatWrapper object000 = ((FloatWrapper)(renamed_Object));

            result.LiteralValue = Native.stringify(FloatWrapper.wrapFloat(object000.wrapperValue));
            result.Type = "FLOAT";
          }
        }
        else if (Surrogate.subtypeOfStringP(testValue000)) {
          { StringWrapper object000 = ((StringWrapper)(renamed_Object));

            result.LiteralValue = object000.wrapperValue;
            result.Type = "STRING";
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, GuiServer.SGT_LOGIC_TRUTH_VALUE)) {
          { TruthValue object000 = ((TruthValue)(renamed_Object));

            result.LiteralValue = GuiServer.getTruthValueString(object000);
            result.Type = "TRUTH-VALUE";
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, GuiServer.SGT_LOGIC_NAMED_DESCRIPTION)) {
          { NamedDescription object000 = ((NamedDescription)(renamed_Object));

            result.PLSurrogate = GuiServer.makeLogicSurrogate(object000);
            if (Logic.classP(object000)) {
              result.Type = "CONCEPT";
            }
            else {
              result.Type = "RELATION";
            }
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, GuiServer.SGT_LOGIC_SKOLEM)) {
          { Skolem object000 = ((Skolem)(renamed_Object));

            result.PLSurrogate = GuiServer.makeLogicSurrogate(object000);
            result.Type = "INSTANCE";
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, GuiServer.SGT_LOGIC_LOGIC_OBJECT)) {
          { LogicObject object000 = ((LogicObject)(renamed_Object));

            result.PLSurrogate = GuiServer.makeLogicSurrogate(object000);
            result.Type = "INSTANCE";
          }
        }
        else {
          Stella.STANDARD_OUTPUT.nativeStream.println("This object has unknown type: " + renamed_Object + " (type = )");
          if (renamed_Object == null) {
            Stella.STANDARD_OUTPUT.nativeStream.println("make-pl-object-union: object is NOT defined");
          }
          else {
            result = GuiServer.makePlObjectUnion(StringWrapper.wrapString(Native.stringify(renamed_Object)));
          }
        }
      }
      return (result);
    }
  }

  public static PLModuleContainer getModules(Module module) {
    { List allmodules = GuiServer.collectAllModules(module, List.newList());
      PLModuleContainer result = GuiServer.createModuleContainer(allmodules);

      return (result);
    }
  }

  public static boolean codeModuleP(Module module) {
    return (((BooleanWrapper)(KeyValueList.dynamicSlotValue(module.dynamicSlots, GuiServer.SYM_STELLA_CODE_ONLYp, Stella.FALSE_WRAPPER))).wrapperValue ||
        (Stella.stringEqlP(module.moduleName, "IDL-THEORY") ||
         Stella.stringEqlP(module.moduleName, "IDL-USER-THEORY")));
  }

  public static List collectAllModules(Module module, List collectedmodules) {
    { Module child = null;
      edu.isi.powerloom.PlIterator iter000 = edu.isi.powerloom.PLI.getChildModules(module);

      while (iter000.nextP()) {
        child = ((Module)(iter000.value));
        if (!GuiServer.codeModuleP(child)) {
          GuiServer.collectAllModules(child, collectedmodules);
        }
      }
    }
    collectedmodules.insert(module);
    return (collectedmodules);
  }

  public static PLModuleContainer createModuleContainer(List collectedmodules) {
    { PLModuleContainer container = PLModuleContainer.new_PLModuleContainer();
      List plmodules = List.newList();

      { Module module = null;
        Cons iter000 = collectedmodules.theConsList;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          module = ((Module)(iter000.value));
          { PLModule plmodule = PLModule.new_PLModule();
            edu.isi.powerloom.PlIterator childmoduleiter = edu.isi.powerloom.PLI.getChildModules(module);
            List surrogatechildren = List.newList();

            plmodule.ModuleName = module.moduleName;
            if (module.moduleCppPackage() == null) {
              plmodule.CppPackage = "";
            }
            else {
              plmodule.CppPackage = module.moduleCppPackage();
            }
            if (module.moduleLispPackage() == null) {
              plmodule.LispPackage = "";
            }
            else {
              plmodule.LispPackage = module.moduleLispPackage();
            }
            if (module.javaPackage() == null) {
              plmodule.JavaPackage = "";
            }
            else {
              plmodule.JavaPackage = module.javaPackage();
            }
            if (((StringWrapper)(KeyValueList.dynamicSlotValue(module.dynamicSlots, GuiServer.SYM_STELLA_JAVA_FLOTSAM_CLASS, Stella.NULL_STRING_WRAPPER))).wrapperValue == null) {
              plmodule.JavaCatchallClass = "";
            }
            else {
              plmodule.JavaCatchallClass = ((StringWrapper)(KeyValueList.dynamicSlotValue(module.dynamicSlots, GuiServer.SYM_STELLA_JAVA_FLOTSAM_CLASS, Stella.NULL_STRING_WRAPPER))).wrapperValue;
            }
            if (module.documentation == null) {
              plmodule.Documentation = "";
            }
            else {
              plmodule.Documentation = GuiServer.xmlifyString(module.documentation);
            }
            if (module.caseSensitiveP) {
              plmodule.CaseSensitive = "TRUE";
            }
            else {
              plmodule.CaseSensitive = "FALSE";
            }
            if (((BooleanWrapper)(KeyValueList.dynamicSlotValue(module.dynamicSlots, GuiServer.SYM_STELLA_APIp, Stella.FALSE_WRAPPER))).wrapperValue) {
              plmodule.api = "TRUE";
            }
            else {
              plmodule.api = "FALSE";
            }
            plmodule.SourceString = GuiServer.replaceChokableCharsWithEntities(GuiServer.getStringifiedModule(module));
            { Module child = null;
              edu.isi.powerloom.PlIterator iter001 = childmoduleiter;
              Cons collect000 = null;

              while (iter001.nextP()) {
                child = ((Module)(iter001.value));
                if (!GuiServer.codeModuleP(child)) {
                  if (collect000 == null) {
                    {
                      collect000 = Cons.cons(GuiServer.makeModuleSurrogate(child), Stella.NIL);
                      if (surrogatechildren.theConsList == Stella.NIL) {
                        surrogatechildren.theConsList = collect000;
                      }
                      else {
                        Cons.addConsToEndOfConsList(surrogatechildren.theConsList, collect000);
                      }
                    }
                  }
                  else {
                    {
                      collect000.rest = Cons.cons(GuiServer.makeModuleSurrogate(child), Stella.NIL);
                      collect000 = collect000.rest;
                    }
                  }
                }
              }
            }
            plmodule.PLSurrogate = surrogatechildren;
            plmodules.insert(plmodule);
          }
        }
      }
      container.PLModule = plmodules;
      return (container);
    }
  }

  public static List getStellaLiteralConcepts() {
    { List collectedconcepts = List.newList();
      NamedDescription topconcept = Logic.getDescription(GuiServer.SGT_STELLA_LITERAL.surrogateValue);
      Module module = edu.isi.powerloom.PLI.getModule("PL-KERNEL-KB", null);

      GuiServer.getStellaLiteralConceptsHelper(module, topconcept, collectedconcepts);
      return (collectedconcepts);
    }
  }

  public static void getStellaLiteralConceptsHelper(Module module, NamedDescription concept, List collectedconcepts) {
    { LogicObject child = null;
      edu.isi.powerloom.PlIterator iter000 = edu.isi.powerloom.PLI.getDirectSubrelations(concept, module, null);

      while (iter000.nextP()) {
        child = ((LogicObject)(iter000.value));
        GuiServer.getStellaLiteralConceptsHelper(module, ((NamedDescription)(child)), collectedconcepts);
      }
    }
    collectedconcepts.insert(concept);
  }

  public static PLConceptContainer getConcepts(Module module) {
    { List allconcepts = GuiServer.getAllConcepts(module, true);
      PLConceptContainer result = null;

      if (module == edu.isi.powerloom.PLI.getModule("PL-KERNEL-KB", null)) {
        allconcepts.concatenate(GuiServer.getStellaLiteralConcepts(), Stella.NIL);
      }
      result = GuiServer.createConceptContainer(allconcepts, module, true);
      return (result);
    }
  }

  public static PLConceptContainer getConceptsWithPrefix(Module module, String prefix) {
    { List allconcepts = GuiServer.getAllConceptsWithPrefix(module, false, prefix);
      PLConceptContainer result = null;

      result = GuiServer.createConceptContainer(allconcepts, module, false);
      return (result);
    }
  }

  public static PLConceptContainer createConceptContainer(List collectedconcepts, Module module, boolean includechildrenP) {
    { PLConceptContainer container = PLConceptContainer.new_PLConceptContainer();
      List plconcepts = List.newList();

      { Description concept = null;
        Cons iter000 = collectedconcepts.theConsList;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          concept = ((Description)(iter000.value));
          { PLConcept plconcept = PLConcept.new_PLConcept();
            edu.isi.powerloom.PlIterator childconceptiter = edu.isi.powerloom.PLI.getDirectSubrelations(concept, module, null);
            List surrogatechildren = List.newList();

            plconcept.ConceptName = GuiServer.xmlifyString(GuiServer.plObjectToGuiName(concept));
            plconcept.Module = concept.homeModule().moduleFullName;
            plconcept.SourceString = "";
            if (includechildrenP) {
              { LogicObject child = null;
                edu.isi.powerloom.PlIterator iter001 = childconceptiter;
                Cons collect000 = null;

                while (iter001.nextP()) {
                  child = ((LogicObject)(iter001.value));
                  if (Logic.classP(child) &&
                      (!BooleanWrapper.coerceWrappedBooleanToBoolean((child.deletedP() ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER)))) {
                    if (collect000 == null) {
                      {
                        collect000 = Cons.cons(GuiServer.makeLogicSurrogate(child), Stella.NIL);
                        if (surrogatechildren.theConsList == Stella.NIL) {
                          surrogatechildren.theConsList = collect000;
                        }
                        else {
                          Cons.addConsToEndOfConsList(surrogatechildren.theConsList, collect000);
                        }
                      }
                    }
                    else {
                      {
                        collect000.rest = Cons.cons(GuiServer.makeLogicSurrogate(child), Stella.NIL);
                        collect000 = collect000.rest;
                      }
                    }
                  }
                }
              }
            }
            surrogatechildren = surrogatechildren.sort(Native.find_java_method("edu.isi.powerloom.server.gui.PLSurrogate", "PLSurrogateL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate"), Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate")}));
            plconcept.PLSurrogate = surrogatechildren;
            plconcepts.insert(plconcept);
          }
        }
      }
      plconcepts = plconcepts.sort(Native.find_java_method("edu.isi.powerloom.server.gui.PLConcept", "PLConceptL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLConcept"), Native.find_java_class("edu.isi.powerloom.server.gui.PLConcept")}));
      container.PLConcept = plconcepts;
      return (container);
    }
  }

  public static PLRelationContainer getRelations(Module module) {
    { List allrelations = GuiServer.getAllRelations(module);
      PLRelationContainer result = GuiServer.createRelationContainer(allrelations, module, true);

      return (result);
    }
  }

  public static PLRelationContainer getRelationsWithPrefix(Module module, String prefix) {
    { List allrelations = GuiServer.getAllRelationsWithPrefix(module, false, prefix);
      PLRelationContainer result = null;

      result = GuiServer.createRelationContainer(allrelations, module, false);
      return (result);
    }
  }

  public static PLRelationContainer createRelationContainer(List collectedrelations, Module module, boolean includechildrenP) {
    { PLRelationContainer container = PLRelationContainer.new_PLRelationContainer();
      List plrelations = List.newList();

      { Description relation = null;
        Cons iter000 = collectedrelations.theConsList;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          relation = ((Description)(iter000.value));
          { PLRelation plrelation = PLRelation.new_PLRelation();
            edu.isi.powerloom.PlIterator childrelationiter = edu.isi.powerloom.PLI.getDirectSubrelations(relation, module, null);
            List surrogatechildren = List.newList();

            if (Logic.functionP(relation)) {
              plrelation.IsFunction = "TRUE";
            }
            else {
              plrelation.IsFunction = "FALSE";
            }
            if (Logic.closedTermP(relation)) {
              plrelation.IsClosed = "TRUE";
            }
            else {
              plrelation.IsClosed = "FALSE";
            }
            plrelation.RelationName = GuiServer.xmlifyString(GuiServer.plObjectToGuiName(relation));
            plrelation.Module = relation.homeModule().moduleFullName;
            plrelation.SourceString = "";
            if (includechildrenP) {
              { LogicObject child = null;
                edu.isi.powerloom.PlIterator iter001 = childrelationiter;
                Cons collect000 = null;

                while (iter001.nextP()) {
                  child = ((LogicObject)(iter001.value));
                  if ((!Logic.classP(child)) &&
                      (!BooleanWrapper.coerceWrappedBooleanToBoolean((child.deletedP() ? Stella.TRUE_WRAPPER : Stella.FALSE_WRAPPER)))) {
                    if (collect000 == null) {
                      {
                        collect000 = Cons.cons(GuiServer.makeLogicSurrogate(child), Stella.NIL);
                        if (surrogatechildren.theConsList == Stella.NIL) {
                          surrogatechildren.theConsList = collect000;
                        }
                        else {
                          Cons.addConsToEndOfConsList(surrogatechildren.theConsList, collect000);
                        }
                      }
                    }
                    else {
                      {
                        collect000.rest = Cons.cons(GuiServer.makeLogicSurrogate(child), Stella.NIL);
                        collect000 = collect000.rest;
                      }
                    }
                  }
                }
              }
            }
            surrogatechildren = surrogatechildren.sort(Native.find_java_method("edu.isi.powerloom.server.gui.PLSurrogate", "PLSurrogateL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate"), Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate")}));
            plrelation.PLSurrogate = surrogatechildren;
            plrelations.insert(plrelation);
          }
        }
      }
      plrelations = plrelations.sort(Native.find_java_method("edu.isi.powerloom.server.gui.PLRelation", "PLRelationL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLRelation"), Native.find_java_class("edu.isi.powerloom.server.gui.PLRelation")}));
      container.PLRelation = plrelations;
      return (container);
    }
  }

  public static PLSurrogateCollection createModuleCollection(List modules) {
    { List surrogatechildren = List.newList();
      PLSurrogateCollection plsurrogatecollection = PLSurrogateCollection.new_PLSurrogateCollection();

      { Module module = null;
        Cons iter000 = modules.theConsList;
        Cons collect000 = null;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          module = ((Module)(iter000.value));
          if (collect000 == null) {
            {
              collect000 = Cons.cons(GuiServer.makeModuleSurrogate(module), Stella.NIL);
              if (surrogatechildren.theConsList == Stella.NIL) {
                surrogatechildren.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(surrogatechildren.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(GuiServer.makeModuleSurrogate(module), Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      surrogatechildren = surrogatechildren.sort(Native.find_java_method("edu.isi.powerloom.server.gui.PLSurrogate", "PLSurrogateL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate"), Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate")}));
      plsurrogatecollection.PLSurrogate = surrogatechildren;
      return (plsurrogatecollection);
    }
  }

  public static PLSurrogateCollection createSurrogateCollection(List surrogates) {
    { List surrogatechildren = List.newList();
      PLSurrogateCollection plsurrogatecollection = PLSurrogateCollection.new_PLSurrogateCollection();

      { Surrogate surrogate = null;
        Cons iter000 = surrogates.theConsList;
        Cons collect000 = null;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          surrogate = ((Surrogate)(iter000.value));
          if (collect000 == null) {
            {
              collect000 = Cons.cons(GuiServer.makeSurrogateSurrogate(surrogate), Stella.NIL);
              if (surrogatechildren.theConsList == Stella.NIL) {
                surrogatechildren.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(surrogatechildren.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(GuiServer.makeSurrogateSurrogate(surrogate), Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      surrogatechildren = surrogatechildren.sort(Native.find_java_method("edu.isi.powerloom.server.gui.PLSurrogate", "PLSurrogateL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate"), Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate")}));
      plsurrogatecollection.PLSurrogate = surrogatechildren;
      return (plsurrogatecollection);
    }
  }

  public static PLSurrogateCollection createSurrogateCollectionForLogicObject(List relations) {
    { List surrogatechildren = List.newList();
      PLSurrogateCollection plsurrogatecollection = PLSurrogateCollection.new_PLSurrogateCollection();

      { LogicObject relation = null;
        Cons iter000 = relations.theConsList;
        Cons collect000 = null;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          relation = ((LogicObject)(iter000.value));
          if (collect000 == null) {
            {
              collect000 = Cons.cons(GuiServer.makeLogicSurrogate(relation), Stella.NIL);
              if (surrogatechildren.theConsList == Stella.NIL) {
                surrogatechildren.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(surrogatechildren.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(GuiServer.makeLogicSurrogate(relation), Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      surrogatechildren = surrogatechildren.sort(Native.find_java_method("edu.isi.powerloom.server.gui.PLSurrogate", "PLSurrogateL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate"), Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate")}));
      plsurrogatecollection.PLSurrogate = surrogatechildren;
      return (plsurrogatecollection);
    }
  }

  public static PLSurrogateCollection createSuperrelationsContainer(LogicObject relation, Module module) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, module);
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        { edu.isi.powerloom.PlIterator parentrelationiter = edu.isi.powerloom.PLI.getDirectSuperrelations(relation, module, null);
          List surrogatechildren = List.newList();
          PLSurrogateCollection plsurrogatecollection = PLSurrogateCollection.new_PLSurrogateCollection();

          { LogicObject parent = null;
            edu.isi.powerloom.PlIterator iter000 = parentrelationiter;
            Cons collect000 = null;

            while (iter000.nextP()) {
              parent = ((LogicObject)(iter000.value));
              if (collect000 == null) {
                {
                  collect000 = Cons.cons(GuiServer.makeLogicSurrogate(parent), Stella.NIL);
                  if (surrogatechildren.theConsList == Stella.NIL) {
                    surrogatechildren.theConsList = collect000;
                  }
                  else {
                    Cons.addConsToEndOfConsList(surrogatechildren.theConsList, collect000);
                  }
                }
              }
              else {
                {
                  collect000.rest = Cons.cons(GuiServer.makeLogicSurrogate(parent), Stella.NIL);
                  collect000 = collect000.rest;
                }
              }
            }
          }
          surrogatechildren = surrogatechildren.sort(Native.find_java_method("edu.isi.powerloom.server.gui.PLSurrogate", "PLSurrogateL", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate"), Native.find_java_class("edu.isi.powerloom.server.gui.PLSurrogate")}));
          plsurrogatecollection.PLSurrogate = surrogatechildren;
          return (plsurrogatecollection);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  public static PLVariableList createVariablesList(LogicObject relation) {
    { List variables = List.newList();
      PLVariableList plvariablelist = PLVariableList.new_PLVariableList();

      if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(relation), GuiServer.SGT_LOGIC_NAMED_DESCRIPTION)) {
        { NamedDescription relation000 = ((NamedDescription)(relation));

          { Symbol variablename = null;
            Cons iter000 = relation000.ioVariableNames.theConsList;
            Surrogate variabletype = null;
            Cons iter001 = relation000.ioVariableTypes.theConsList;
            Cons collect000 = null;

            for (;(!(iter000 == Stella.NIL)) &&
                      (!(iter001 == Stella.NIL)); iter000 = iter000.rest, iter001 = iter001.rest) {
              variablename = ((Symbol)(iter000.value));
              variabletype = ((Surrogate)(iter001.value));
              if (collect000 == null) {
                {
                  collect000 = Cons.cons(GuiServer.makePlVariable(variablename.symbolName, variabletype), Stella.NIL);
                  if (variables.theConsList == Stella.NIL) {
                    variables.theConsList = collect000;
                  }
                  else {
                    Cons.addConsToEndOfConsList(variables.theConsList, collect000);
                  }
                }
              }
              else {
                {
                  collect000.rest = Cons.cons(GuiServer.makePlVariable(variablename.symbolName, variabletype), Stella.NIL);
                  collect000 = collect000.rest;
                }
              }
            }
          }
        }
      }
      else {
      }
      plvariablelist.PLVariable = variables;
      return (plvariablelist);
    }
  }

  public static PLVariable makePlVariable(String variablename, Surrogate variabletype) {
    { PLVariable result = PLVariable.new_PLVariable();
      PLString plvariablename = PLString.new_PLString();
      PLSurrogate plvariabletype = PLSurrogate.new_PLSurrogate();

      plvariablename.Value = variablename;
      plvariabletype.id = variabletype.symbolName;
      result.VariableName = plvariablename;
      result.VariableType = plvariabletype;
      return (result);
    }
  }

  public static PLRelation makePlRelation(LogicObject relation, String modulename) {
    modulename = modulename;
    { PLRelation xmlrelation = PLRelation.new_PLRelation();

      xmlrelation.Module = relation.homeModule().moduleFullName;
      if (Logic.functionP(relation)) {
        xmlrelation.IsFunction = "TRUE";
      }
      else {
        xmlrelation.IsFunction = "FALSE";
      }
      if (Logic.closedTermP(relation)) {
        xmlrelation.IsClosed = "TRUE";
      }
      else {
        xmlrelation.IsClosed = "FALSE";
      }
      xmlrelation.SourceString = "";
      xmlrelation.RelationName = GuiServer.xmlifyString(GuiServer.plObjectToGuiName(relation));
      return (xmlrelation);
    }
  }

  public static PLConcept makePlConcept(LogicObject concept) {
    { PLConcept xmlconcept = PLConcept.new_PLConcept();

      xmlconcept.Module = concept.homeModule().moduleFullName;
      xmlconcept.SourceString = "";
      xmlconcept.ConceptName = GuiServer.xmlifyString(GuiServer.plObjectToGuiName(concept));
      return (xmlconcept);
    }
  }

  public static List makePlRelations(List relations, String modulename) {
    { List result = List.newList();

      { Description relation = null;
        Cons iter000 = relations.theConsList;
        Cons collect000 = null;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          relation = ((Description)(iter000.value));
          if (collect000 == null) {
            {
              collect000 = Cons.cons(GuiServer.makePlRelation(relation, modulename), Stella.NIL);
              if (result.theConsList == Stella.NIL) {
                result.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(result.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(GuiServer.makePlRelation(relation, modulename), Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      return (result);
    }
  }

  public static PLSurrogate makeModuleSurrogate(Module module) {
    { PLSurrogate result = PLSurrogate.new_PLSurrogate();

      result.id = module.moduleName;
      return (result);
    }
  }

  public static PLSurrogate makeSurrogateSurrogate(Surrogate surrogate) {
    { PLSurrogate result = PLSurrogate.new_PLSurrogate();

      result.id = GuiServer.xmlifyString(GuiServer.plObjectToGuiName(surrogate));
      return (result);
    }
  }

  public static PLSurrogate makeLogicSurrogate(LogicObject obj) {
    { PLSurrogate result = PLSurrogate.new_PLSurrogate();

      if (Logic.skolemP(obj)) {
        { OutputStringStream resultstream = OutputStringStream.newOutputStringStream();
          edu.isi.stella.javalib.NativeOutputStream nativestream = resultstream.nativeStream;
          String printname = null;

          { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();
            Object old$PrintprettyP$000 = Stella.$PRINTPRETTYp$.get();

            try {
              Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
              Native.setBooleanSpecial(Stella.$PRINTPRETTYp$, true);
              printname = GuiServer.xmlifyString(resultstream.theStringReader());

            } finally {
              Stella.$PRINTPRETTYp$.set(old$PrintprettyP$000);
              Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
            }
          }
          result.id = printname;
          return (result);
        }
      }
      result.id = GuiServer.xmlifyString(GuiServer.plObjectToGuiName(obj));
      return (result);
    }
  }

  public static List getAllRelations(Module module) {
    { Iterator iter = Logic.allNamedDescriptions(module, true);
      List result = List.newList();

      { NamedDescription description = null;
        Iterator iter000 = iter;
        Cons collect000 = null;

        while (iter000.nextP()) {
          description = ((NamedDescription)(iter000.value));
          if (!Logic.classP(description)) {
            if (collect000 == null) {
              {
                collect000 = Cons.cons(description, Stella.NIL);
                if (result.theConsList == Stella.NIL) {
                  result.theConsList = collect000;
                }
                else {
                  Cons.addConsToEndOfConsList(result.theConsList, collect000);
                }
              }
            }
            else {
              {
                collect000.rest = Cons.cons(description, Stella.NIL);
                collect000 = collect000.rest;
              }
            }
          }
        }
      }
      return (result);
    }
  }

  public static List getAllRelationsWithPrefix(Module module, boolean localP, String prefix) {
    { Iterator iter = Logic.allNamedDescriptions(module, localP);
      List result = List.newList();
      String downcasedprefix = Native.stringDowncase(prefix);

      { NamedDescription description = null;
        Iterator iter000 = iter;
        Cons collect000 = null;

        while (iter000.nextP()) {
          description = ((NamedDescription)(iter000.value));
          if ((!Logic.classP(description)) &&
              ((prefix != null) &&
               Stella.startsWithP(GuiServer.getLogicObjectName(description, "FALSE"), downcasedprefix, 0))) {
            if (collect000 == null) {
              {
                collect000 = Cons.cons(description, Stella.NIL);
                if (result.theConsList == Stella.NIL) {
                  result.theConsList = collect000;
                }
                else {
                  Cons.addConsToEndOfConsList(result.theConsList, collect000);
                }
              }
            }
            else {
              {
                collect000.rest = Cons.cons(description, Stella.NIL);
                collect000 = collect000.rest;
              }
            }
          }
        }
      }
      return (result);
    }
  }

  public static List getAllConcepts(Module module, boolean localP) {
    { Iterator iter = Logic.allNamedDescriptions(module, localP);
      List result = List.newList();

      { NamedDescription description = null;
        Iterator iter000 = iter;
        Cons collect000 = null;

        while (iter000.nextP()) {
          description = ((NamedDescription)(iter000.value));
          if (Logic.classP(description)) {
            if (collect000 == null) {
              {
                collect000 = Cons.cons(description, Stella.NIL);
                if (result.theConsList == Stella.NIL) {
                  result.theConsList = collect000;
                }
                else {
                  Cons.addConsToEndOfConsList(result.theConsList, collect000);
                }
              }
            }
            else {
              {
                collect000.rest = Cons.cons(description, Stella.NIL);
                collect000 = collect000.rest;
              }
            }
          }
        }
      }
      return (result);
    }
  }

  public static List getAllConceptsWithPrefix(Module module, boolean localP, String prefix) {
    { Iterator iter = Logic.allNamedDescriptions(module, localP);
      List result = List.newList();
      String downcasedprefix = Native.stringDowncase(prefix);

      { NamedDescription description = null;
        Iterator iter000 = iter;
        Cons collect000 = null;

        while (iter000.nextP()) {
          description = ((NamedDescription)(iter000.value));
          if (Logic.classP(description) &&
              ((prefix != null) &&
               Stella.startsWithP(GuiServer.getLogicObjectName(description, "FALSE"), downcasedprefix, 0))) {
            if (collect000 == null) {
              {
                collect000 = Cons.cons(description, Stella.NIL);
                if (result.theConsList == Stella.NIL) {
                  result.theConsList = collect000;
                }
                else {
                  Cons.addConsToEndOfConsList(result.theConsList, collect000);
                }
              }
            }
            else {
              {
                collect000.rest = Cons.cons(description, Stella.NIL);
                collect000 = collect000.rest;
              }
            }
          }
        }
      }
      return (result);
    }
  }

  public static List getSubconcepts(Description concept, Module module) {
    { edu.isi.powerloom.PlIterator iter = edu.isi.powerloom.PLI.getDirectSubrelations(concept, module, null);
      List result = List.newList();

      { LogicObject sub = null;
        edu.isi.powerloom.PlIterator iter000 = iter;
        Cons collect000 = null;

        while (iter000.nextP()) {
          sub = ((LogicObject)(iter000.value));
          if (collect000 == null) {
            {
              collect000 = Cons.cons(sub, Stella.NIL);
              if (result.theConsList == Stella.NIL) {
                result.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(result.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(sub, Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      return (result);
    }
  }

  public static List getSubrelations(Description relation, Module module) {
    { edu.isi.powerloom.PlIterator iter = edu.isi.powerloom.PLI.getDirectSubrelations(relation, module, null);
      List result = List.newList();

      { LogicObject sub = null;
        edu.isi.powerloom.PlIterator iter000 = iter;
        Cons collect000 = null;

        while (iter000.nextP()) {
          sub = ((LogicObject)(iter000.value));
          if (collect000 == null) {
            {
              collect000 = Cons.cons(sub, Stella.NIL);
              if (result.theConsList == Stella.NIL) {
                result.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(result.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(sub, Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      return (result);
    }
  }

  public static List getSuperconcepts(Description concept, Module module) {
    { edu.isi.powerloom.PlIterator iter = edu.isi.powerloom.PLI.getDirectSuperrelations(concept, module, null);
      List result = List.newList();

      { LogicObject renamed_Super = null;
        edu.isi.powerloom.PlIterator iter000 = iter;
        Cons collect000 = null;

        while (iter000.nextP()) {
          renamed_Super = ((LogicObject)(iter000.value));
          if (collect000 == null) {
            {
              collect000 = Cons.cons(renamed_Super, Stella.NIL);
              if (result.theConsList == Stella.NIL) {
                result.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(result.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(renamed_Super, Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      return (result);
    }
  }

  public static List getSuperrelations(Description relation, Module module) {
    { edu.isi.powerloom.PlIterator iter = edu.isi.powerloom.PLI.getDirectSuperrelations(relation, module, null);
      List result = List.newList();

      { LogicObject renamed_Super = null;
        edu.isi.powerloom.PlIterator iter000 = iter;
        Cons collect000 = null;

        while (iter000.nextP()) {
          renamed_Super = ((LogicObject)(iter000.value));
          if (collect000 == null) {
            {
              collect000 = Cons.cons(renamed_Super, Stella.NIL);
              if (result.theConsList == Stella.NIL) {
                result.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(result.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(renamed_Super, Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      return (result);
    }
  }

  public static PLInstance makePlInstance(LogicObject instance) {
    { PLInstance xmlinstance = PLInstance.new_PLInstance();

      xmlinstance.InstanceName = GuiServer.xmlifyString(GuiServer.plObjectToGuiName(instance));
      if (instance.homeModule() != null) {
        xmlinstance.Module = instance.homeModule().moduleFullName;
      }
      else {
        xmlinstance.Module = "";
      }
      xmlinstance.SourceString = "(DEFOBJECT " + xmlinstance.InstanceName + ")";
      return (xmlinstance);
    }
  }

  public static List makePlInstances(List instances, boolean skipuninternedinstancesP) {
    { List result = List.newList();

      { LogicObject instance = null;
        Cons iter000 = instances.theConsList;
        Cons collect000 = null;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          instance = ((LogicObject)(iter000.value));
          if ((!skipuninternedinstancesP) ||
              (instance.homeModule() != null)) {
            if (collect000 == null) {
              {
                collect000 = Cons.cons(GuiServer.makePlInstance(instance), Stella.NIL);
                if (result.theConsList == Stella.NIL) {
                  result.theConsList = collect000;
                }
                else {
                  Cons.addConsToEndOfConsList(result.theConsList, collect000);
                }
              }
            }
            else {
              {
                collect000.rest = Cons.cons(GuiServer.makePlInstance(instance), Stella.NIL);
                collect000 = collect000.rest;
              }
            }
          }
        }
      }
      return (result);
    }
  }

  public static PLProposition makePlProposition(Proposition proposition, Module module, boolean isrule) {
    { PLProposition xmlproposition = PLProposition.new_PLProposition();

      xmlproposition.PropositionName = GuiServer.getPropositionString(proposition, module);
      if (Proposition.assertedAsTrueP(proposition)) {
        xmlproposition.IsAsserted = "TRUE";
      }
      else {
        xmlproposition.IsAsserted = "FALSE";
      }
      { Object old$Context$000 = Stella.$CONTEXT$.get();
        Object old$Module$000 = Stella.$MODULE$.get();

        try {
          Native.setSpecial(Stella.$CONTEXT$, Logic.getQueryContext());
          Native.setSpecial(Stella.$MODULE$, ((Context)(Stella.$CONTEXT$.get())).baseModule);
          if (edu.isi.powerloom.PLI.isStrict(Proposition.propositionTruthValue(proposition))) {
            xmlproposition.IsStrict = "TRUE";
          }
          else {
            xmlproposition.IsStrict = "FALSE";
          }

        } finally {
          Stella.$MODULE$.set(old$Module$000);
          Stella.$CONTEXT$.set(old$Context$000);
        }
      }
      if (isrule) {
        xmlproposition.IsRule = "TRUE";
      }
      else {
        xmlproposition.IsRule = "FALSE";
      }
      return (xmlproposition);
    }
  }

  public static List makePlPropositions(List propositions, Module module, boolean isrule) {
    { List result = List.newList();

      { Proposition proposition = null;
        Cons iter000 = propositions.theConsList;
        Cons collect000 = null;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          proposition = ((Proposition)(iter000.value));
          if (collect000 == null) {
            {
              collect000 = Cons.cons(GuiServer.makePlProposition(proposition, module, isrule), Stella.NIL);
              if (result.theConsList == Stella.NIL) {
                result.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(result.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(GuiServer.makePlProposition(proposition, module, isrule), Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      return (result);
    }
  }

  public static PLString getDocumentationForObject(String modulename, String objectname) {
    { PLString result = PLString.new_PLString();
      String docstring = "";

      { Stella_Object doc = null;
        edu.isi.powerloom.PlIterator iter000 = edu.isi.powerloom.PLI.sGetInferredBinaryPropositionValues("DOCUMENTATION", GuiServer.guiNameToPlName(objectname), modulename, null);
        int i = Stella.NULL_INTEGER;
        int iter001 = 1;

        for (;iter000.nextP(); iter001 = iter001 + 1) {
          doc = iter000.value;
          i = iter001;
          if (Stella_Object.stringP(doc)) {
            docstring = docstring + (((i == 1) ? "" : Stella.EOL_STRING)) + ((StringWrapper)(doc)).wrapperValue;
          }
        }
      }
      result.Value = GuiServer.xmlifyFormattedString(docstring);
      return (result);
    }
  }

  public static List getDirectRelationsForConcept(Module module, LogicObject concept) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, module);
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        { Module module000 = edu.isi.powerloom.PLI.getHomeModule(concept);
          List allrelations = GuiServer.getAllRelations(module000);
          List result = List.newList();

          { Description relation = null;
            Cons iter000 = allrelations.theConsList;
            Cons collect000 = null;

            for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
              relation = ((Description)(iter000.value));
              if (concept == edu.isi.powerloom.PLI.getDomain(relation)) {
                if (collect000 == null) {
                  {
                    collect000 = Cons.cons(relation, Stella.NIL);
                    if (result.theConsList == Stella.NIL) {
                      result.theConsList = collect000;
                    }
                    else {
                      Cons.addConsToEndOfConsList(result.theConsList, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000.rest = Cons.cons(relation, Stella.NIL);
                    collect000 = collect000.rest;
                  }
                }
              }
            }
          }
          return (result);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  public static List getInheritedRelationsForConcept(Module module, LogicObject concept) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, module);
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        { Module module000 = edu.isi.powerloom.PLI.getHomeModule(concept);
          List allrelations = GuiServer.getAllRelations(module000);
          List result = List.newList();

          { Description relation = null;
            Cons iter000 = allrelations.theConsList;
            Cons collect000 = null;

            for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
              relation = ((Description)(iter000.value));
              if (edu.isi.powerloom.PLI.isSubrelation(concept, edu.isi.powerloom.PLI.getDomain(relation), module000, edu.isi.powerloom.PLI.TAXONOMIC_ENV)) {
                if (collect000 == null) {
                  {
                    collect000 = Cons.cons(relation, Stella.NIL);
                    if (result.theConsList == Stella.NIL) {
                      result.theConsList = collect000;
                    }
                    else {
                      Cons.addConsToEndOfConsList(result.theConsList, collect000);
                    }
                  }
                }
                else {
                  {
                    collect000.rest = Cons.cons(relation, Stella.NIL);
                    collect000 = collect000.rest;
                  }
                }
              }
            }
          }
          return (result);
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  /** Get all the propositions for a given instance
   * @param modulename
   * @param instancename
   * @param relationP
   * @return List
   */
  public static List getPropositionsForObject(String modulename, String instancename, boolean relationP) {
    relationP = relationP;
    { edu.isi.powerloom.PlIterator iter = edu.isi.powerloom.PLI.sGetPropositionsOf(GuiServer.guiNameToPlName(instancename), modulename, null);
      List propositions = List.newList();

      { Proposition prop = null;
        edu.isi.powerloom.PlIterator iter000 = iter;
        Cons collect000 = null;

        while (iter000.nextP()) {
          prop = ((Proposition)(iter000.value));
          if (!GuiServer.rulePropositionP(prop)) {
            if (collect000 == null) {
              {
                collect000 = Cons.cons(prop, Stella.NIL);
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
                collect000.rest = Cons.cons(prop, Stella.NIL);
                collect000 = collect000.rest;
              }
            }
          }
        }
      }
      return (propositions.sort(Native.find_java_method("edu.isi.powerloom.logic.Proposition", "propositionLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Proposition"), Native.find_java_class("edu.isi.powerloom.logic.Proposition")})));
    }
  }

  /** Get all the rules for a given logic object
   * @param modulename
   * @param instancename
   * @return List
   */
  public static List getRulesForRelation(String modulename, String instancename) {
    { edu.isi.powerloom.PlIterator iter = edu.isi.powerloom.PLI.sGetRules(GuiServer.guiNameToPlName(instancename), modulename, null);
      List rules = List.newList();

      { Proposition rule = null;
        edu.isi.powerloom.PlIterator iter000 = iter;
        Cons collect000 = null;

        while (iter000.nextP()) {
          rule = ((Proposition)(iter000.value));
          if (collect000 == null) {
            {
              collect000 = Cons.cons(rule, Stella.NIL);
              if (rules.theConsList == Stella.NIL) {
                rules.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(rules.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(rule, Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      return (rules.sort(Native.find_java_method("edu.isi.powerloom.logic.Proposition", "propositionLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Proposition"), Native.find_java_class("edu.isi.powerloom.logic.Proposition")})));
    }
  }

  public static boolean rulePropositionP(Proposition proposition) {
    { Keyword testValue000 = proposition.kind;

      if ((testValue000 == GuiServer.KWD_FORALL) ||
          ((testValue000 == GuiServer.KWD_EXISTS) ||
           (testValue000 == GuiServer.KWD_IMPLIES))) {
        return (true);
      }
      else {
        return (false);
      }
    }
  }

  public static boolean subrelationRuleP(Proposition rule) {
    return ((rule.kind == GuiServer.KWD_IMPLIES) &&
        (Stella_Object.isaP((rule.arguments.theArray)[0], GuiServer.SGT_LOGIC_NAMED_DESCRIPTION) &&
         Stella_Object.isaP((rule.arguments.theArray)[1], GuiServer.SGT_LOGIC_NAMED_DESCRIPTION)));
  }

  /** Get all the relevant rules for a given logic object.
   * @param modulename
   * @param relationname
   * @return List
   */
  public static List getRelevantRulesForRelation(String modulename, String relationname) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename, null);
      LogicObject relation = edu.isi.powerloom.PLI.sGetRelation(GuiServer.guiNameToPlName(relationname), modulename, null);
      List rules = List.newList();

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { Object old$Context$001 = Stella.$CONTEXT$.get();
            Object old$Module$001 = Stella.$MODULE$.get();

            try {
              Native.setSpecial(Stella.$CONTEXT$, Logic.getQueryContext());
              Native.setSpecial(Stella.$MODULE$, ((Context)(Stella.$CONTEXT$.get())).baseModule);
              { Proposition rule = null;
                Cons iter000 = Logic.callGetRules(relation);
                Cons collect000 = null;

                for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
                  rule = ((Proposition)(iter000.value));
                  if (Proposition.trueP(rule) &&
                      (!GuiServer.subrelationRuleP(rule))) {
                    if (collect000 == null) {
                      {
                        { Proposition temp000 = ((Proposition)(KeyValueList.dynamicSlotValue(rule.dynamicSlots, GuiServer.SYM_LOGIC_MASTER_PROPOSITION, null)));

                          collect000 = Cons.cons(((temp000 != null) ? temp000 : rule), Stella.NIL);
                        }
                        if (rules.theConsList == Stella.NIL) {
                          rules.theConsList = collect000;
                        }
                        else {
                          Cons.addConsToEndOfConsList(rules.theConsList, collect000);
                        }
                      }
                    }
                    else {
                      {
                        { Proposition temp001 = ((Proposition)(KeyValueList.dynamicSlotValue(rule.dynamicSlots, GuiServer.SYM_LOGIC_MASTER_PROPOSITION, null)));

                          collect000.rest = Cons.cons(((temp001 != null) ? temp001 : rule), Stella.NIL);
                        }
                        collect000 = collect000.rest;
                      }
                    }
                  }
                }
              }
              rules.removeDuplicates();
              return (rules.sort(Native.find_java_method("edu.isi.powerloom.logic.Proposition", "propositionLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Proposition"), Native.find_java_class("edu.isi.powerloom.logic.Proposition")})));

            } finally {
              Stella.$MODULE$.set(old$Module$001);
              Stella.$CONTEXT$.set(old$Context$001);
            }
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  public static List getPropositionsForInstanceAndRelation(String modulename, String instancename, String relationname) {
    { String expressionstring = "(" + GuiServer.guiNameToPlName(relationname) + " " + GuiServer.guiNameToPlName(instancename);
      Description relation = ((Description)(edu.isi.powerloom.PLI.sGetRelation(GuiServer.guiNameToPlName(relationname), modulename, null)));
      int arity = relation.arity();
      List result = List.newList();

      { int i = Stella.NULL_INTEGER;
        int iter000 = 2;
        int upperBound000 = arity;
        boolean unboundedP000 = upperBound000 == Stella.NULL_INTEGER;

        for (;unboundedP000 ||
                  (iter000 <= upperBound000); iter000 = iter000 + 1) {
          i = iter000;
          i = i;
          expressionstring = expressionstring + " NULL";
        }
      }
      expressionstring = expressionstring + ")";
      { Proposition prop = null;
        edu.isi.powerloom.PlIterator iter001 = edu.isi.powerloom.PLI.sGetPropositions(expressionstring, modulename, null);
        Cons collect000 = null;

        while (iter001.nextP()) {
          prop = ((Proposition)(iter001.value));
          if (collect000 == null) {
            {
              collect000 = Cons.cons(prop, Stella.NIL);
              if (result.theConsList == Stella.NIL) {
                result.theConsList = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(result.theConsList, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(prop, Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      return (result.sort(Native.find_java_method("edu.isi.powerloom.logic.Proposition", "propositionLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Proposition"), Native.find_java_class("edu.isi.powerloom.logic.Proposition")})));
    }
  }

  public static String evaluateLogicCommandInModule(String command, String modulename, boolean finalizeP) {
    { Module module = Stella.getStellaModule(modulename, false);
      Stella_Object result = null;

      if (module == null) {
        module = ((Module)(Stella.$MODULE$.get()));
      }
      try {
        { Object old$Module$000 = Stella.$MODULE$.get();
          Object old$Context$000 = Stella.$CONTEXT$.get();

          try {
            Native.setSpecial(Stella.$MODULE$, module);
            Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
            Logic.$LAZY_SATELLITE_RULESp$ = false;
            result = Logic.evaluateLogicCommand(InputStream.readSExpression(InputStringStream.newInputStringStream(command), new Object[1]), finalizeP);
            if (result == null) {
              return ("");
            }
            else if (Stella_Object.stringP(result)) {
              return (((StringWrapper)(result)).wrapperValue);
            }
            else {
              { OutputStringStream resultstream = OutputStringStream.newOutputStringStream();
                edu.isi.stella.javalib.NativeOutputStream nativestream = resultstream.nativeStream;

                { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();
                  Object old$PrintprettyP$000 = Stella.$PRINTPRETTYp$.get();

                  try {
                    Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
                    Native.setBooleanSpecial(Stella.$PRINTPRETTYp$, true);
                    if (result != null) {
                      resultstream.nativeStream.print(result);
                    }

                  } finally {
                    Stella.$PRINTPRETTYp$.set(old$PrintprettyP$000);
                    Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
                  }
                }
                return (resultstream.theStringReader());
              }
            }

          } finally {
            Stella.$CONTEXT$.set(old$Context$000);
            Stella.$MODULE$.set(old$Module$000);
          }
        }
      } catch (java.lang.Exception e) {
        throw ((java.lang.RuntimeException)(((java.lang.RuntimeException)(e)).fillInStackTrace()));
      }
    }
  }

  public static Cons evaluateQueryCommandInModule(edu.isi.webtools.http.Session session, String query, String modulename, boolean continuationqueryP, boolean partialqueryP) {
    { Module module = Stella.getStellaModule(modulename, false);
      Cons querytree = Stella.NIL;
      QueryIterator queryiterator = null;
      Cons tuple = Stella.NIL;
      Cons result = Stella.NIL;

      if (module == null) {
        module = ((Module)(Stella.$MODULE$.get()));
      }
      try {
        { Object old$Module$000 = Stella.$MODULE$.get();
          Object old$Context$000 = Stella.$CONTEXT$.get();

          try {
            Native.setSpecial(Stella.$MODULE$, module);
            Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
            querytree = ((Cons)(Stella.readSExpressionFromString(query)));
            if (querytree.value == GuiServer.SYM_STELLA_ASK) {
              {
                queryiterator = Logic.createAskQuery(querytree.rest);
                session.insertAt(StringWrapper.wrapString("QueryIterator"), queryiterator);
                if (partialqueryP) {
                  result = Cons.cons(FloatWrapper.wrapFloat(Logic.callAskPartial(queryiterator)), Stella.NIL);
                }
                else {
                  result = Cons.cons(Logic.callAsk(queryiterator), Stella.NIL);
                }
                return (Cons.cons(result, Stella.NIL));
              }
            }
            else {
              {
                if (continuationqueryP) {
                  Logic.$MOST_RECENT_QUERY$ = ((QueryIterator)(session.lookup(StringWrapper.wrapString("QueryIterator"))));
                }
                else {
                  Logic.$MOST_RECENT_QUERY$ = null;
                }
                queryiterator = Logic.createRetrieveQuery(querytree.rest);
                session.insertAt(StringWrapper.wrapString("QueryIterator"), queryiterator);
                if (partialqueryP) {
                  Logic.callRetrievePartial(queryiterator);
                }
                else {
                  Logic.callRetrieve(queryiterator);
                }
                { QuerySolution solution = null;
                  DictionaryIterator iter000 = ((DictionaryIterator)(queryiterator.solutions.allocateIterator()));
                  Cons collect000 = null;

                  while (iter000.nextP()) {
                    solution = ((QuerySolution)(iter000.value));
                    tuple = solution.bindings.consify();
                    if (partialqueryP) {
                      tuple.concatenate(Cons.cons(FloatWrapper.wrapFloat(solution.matchScore), Stella.NIL), Stella.NIL);
                    }
                    if (collect000 == null) {
                      {
                        collect000 = Cons.cons(tuple, Stella.NIL);
                        if (result == Stella.NIL) {
                          result = collect000;
                        }
                        else {
                          Cons.addConsToEndOfConsList(result, collect000);
                        }
                      }
                    }
                    else {
                      {
                        collect000.rest = Cons.cons(tuple, Stella.NIL);
                        collect000 = collect000.rest;
                      }
                    }
                  }
                }
                return (result);
              }
            }

          } finally {
            Stella.$CONTEXT$.set(old$Context$000);
            Stella.$MODULE$.set(old$Module$000);
          }
        }
      } catch (java.lang.Exception e) {
        throw ((java.lang.RuntimeException)(((java.lang.RuntimeException)(e)).fillInStackTrace()));
      }
    }
  }

  public static String getPropositionString(Proposition prop, Module module) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, module);
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        { OutputStringStream ss = OutputStringStream.newOutputStringStream();

          { Object old$Printmode$000 = Logic.$PRINTMODE$.get();
            Object old$Printlogicalformstream$000 = Logic.$PRINTLOGICALFORMSTREAM$.get();
            Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();

            try {
              Native.setSpecial(Logic.$PRINTMODE$, GuiServer.KWD_ORIGINAL);
              Native.setSpecial(Logic.$PRINTLOGICALFORMSTREAM$, ss);
              Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
              Logic.prettyPrintLogicalForm(prop, ss);

            } finally {
              Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
              Logic.$PRINTLOGICALFORMSTREAM$.set(old$Printlogicalformstream$000);
              Logic.$PRINTMODE$.set(old$Printmode$000);
            }
          }
          return (GuiServer.xmlifyFormattedString(ss.theStringReader()));
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  public static String getTruthValueString(TruthValue tv) {
    { OutputStringStream ss = OutputStringStream.newOutputStringStream();

      TruthValue.printTruthValue(tv, ss);
      return (ss.theStringReader());
    }
  }

  public static String xmlifyString(String instring) {
    return (GuiServer.compactWhitespace(GuiServer.stripNewlines(instring)));
  }

  public static String xmlifyFormattedString(String instring) {
    return (instring);
  }

  public static String getStringifiedModule(Module module) {
    { String modulename = module.moduleName;
      List parents = module.parentModules;
      List uses = module.uses;
      String documentation = module.documentation;
      String parentstrings = "";
      String usesstrings = "";
      String result = null;

      { Module parent = null;
        Cons iter000 = parents.theConsList;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          parent = ((Module)(iter000.value));
          parentstrings = parentstrings + " " + parent.moduleFullName;
        }
      }
      { Module use = null;
        Cons iter001 = uses.theConsList;

        for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
          use = ((Module)(iter001.value));
          usesstrings = usesstrings + " " + use.moduleName;
        }
      }
      result = "(defmodule " + modulename + " :includes (" + parentstrings + ") :uses (" + usesstrings + ") ";
      if (documentation != null) {
        result = result + ":documentation \"" + documentation + "\"";
      }
      result = result + ")";
      return (result);
    }
  }

  public static String replaceChokableCharsWithEntities(String instring) {
    { OutputStringStream ss = OutputStringStream.newOutputStringStream();

      GuiServer.writeHtmlQuotingChokableCharacters(ss.nativeStream, instring);
      return (ss.theStringReader());
    }
  }

  public static void writeHtmlCharacterQuotingChokableCharacters(edu.isi.stella.javalib.NativeOutputStream stream, char ch) {
    if (((int) ch == 10) ||
        ((int) ch > 127)) {
      stream.print("&#" + (int) ch + ";");
    }
    else {
      Stella.writeHtmlCharacterQuotingSpecialCharacters(stream, ch);
    }
  }

  public static void writeHtmlQuotingChokableCharacters(edu.isi.stella.javalib.NativeOutputStream stream, String input) {
    { char ch = Stella.NULL_CHARACTER;
      String vector000 = input;
      int index000 = 0;
      int length000 = vector000.length();

      for (;index000 < length000; index000 = index000 + 1) {
        ch = vector000.charAt(index000);
        GuiServer.writeHtmlCharacterQuotingChokableCharacters(stream, ch);
      }
    }
    return;
  }

  public static String compactWhitespace(String instring) {
    { int count = 0;
      int length = instring.length();
      int cursor = 0;
      int newcursor = 0;
      StringBuffer result = null;

      if (length == 0) {
        return ("");
      }
      loop000 : for (;;) {
        if ((cursor > 0) &&
            (Stella.stringEqlP(Native.makeString(1, instring.charAt(cursor)), " ") &&
             Stella.stringEqlP(Native.makeString(1, instring.charAt((cursor - 1))), " "))) {
          count = count + 1;
        }
        if (cursor == (length - 1)) {
          break loop000;
        }
        cursor = cursor + 1;
      }
      result = Stella.makeRawMutableString(length - count);
      cursor = 0;
      loop001 : for (;;) {
        if (!((cursor > 0) &&
            (Stella.stringEqlP(Native.makeString(1, instring.charAt(cursor)), " ") &&
             Stella.stringEqlP(Native.makeString(1, instring.charAt((cursor - 1))), " ")))) {
          edu.isi.stella.javalib.Native.mutableString_nthSetter(result, (instring.charAt(cursor)), newcursor);
          newcursor = newcursor + 1;
        }
        if (cursor == (length - 1)) {
          break loop001;
        }
        cursor = cursor + 1;
      }
      return (result.toString());
    }
  }

  public static String stripNewlines(String instring) {
    return (Stella.replaceSubstrings(instring, " ", Native.makeString(1, '\n')));
  }

  public static String stripModule(String instring, Module module) {
    { String modname = module.moduleFullName + "/";

      return (Stella.replaceSubstrings(instring, "", modname));
    }
  }

  public static String replaceDoubleQuotesWithSingleQuotes(String instring) {
    return (Stella.replaceSubstrings(instring, "'", "\""));
  }

  public static Cons loadIndexFile() {
    Stella.STANDARD_OUTPUT.nativeStream.println("Loading index " + GuiServer.$KB_FILENAME_INDEX$ + "...");
    { InputFileStream instream = InputFileStream.newInputFileStream(GuiServer.$KB_FILENAME_INDEX$);
      SExpressionIterator streamiter = InputStream.sExpressions(instream);

      { Stella_Object sexp = null;
        SExpressionIterator iter000 = streamiter;

        while (iter000.nextP()) {
          sexp = iter000.value;
          return (((Cons)(sexp)));
        }
      }
      return (Stella.NIL);
    }
  }

  public static void saveIndexFile(Cons index) {
    Stella.STANDARD_OUTPUT.nativeStream.println("Saving index " + GuiServer.$KB_FILENAME_INDEX$ + "...");
    { OutputFileStream outstream = OutputFileStream.newOutputFileStream(GuiServer.$KB_FILENAME_INDEX$);

      outstream.nativeStream.println("(");
      { Cons tuple = null;
        Cons iter000 = index;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          tuple = ((Cons)(iter000.value));
          outstream.nativeStream.println("  (\"" + ((StringWrapper)(tuple.value)).wrapperValue + "\" \"" + ((StringWrapper)(tuple.rest.value)).wrapperValue + "\" \"" + ((StringWrapper)(tuple.rest.rest.value)).wrapperValue + "\" \"" + ((StringWrapper)(tuple.fourth())).wrapperValue + "\")");
        }
      }
      outstream.nativeStream.println(")");
      Stream.closeStream(outstream);
    }
  }

  public static PLModuleFile makePlFile(Cons filedescription) {
    { StringWrapper kb = ((StringWrapper)(filedescription.value));
      StringWrapper modulename = ((StringWrapper)(filedescription.rest.value));
      StringWrapper filename = ((StringWrapper)(filedescription.rest.rest.value));
      StringWrapper description = ((StringWrapper)(filedescription.fourth()));
      PLModuleFile plfile = PLModuleFile.new_PLModuleFile();

      plfile.ModuleName = modulename.wrapperValue;
      plfile.FileName = filename.wrapperValue;
      plfile.KBName = kb.wrapperValue;
      plfile.KBDescription = description.wrapperValue;
      return (plfile);
    }
  }

  public static Cons parseMatchString(String matchstring, String casesensitiveP) {
    { Cons result = Stella.NIL;
      int wildcardpos = 0;
      int cursor = 0;
      String wildcard = "*";
      String fragment = null;

      while ((wildcardpos = Native.stringSearch(matchstring, wildcard, cursor)) != Stella.NULL_INTEGER) {
        if (wildcardpos > cursor) {
          fragment = Native.string_subsequence(matchstring, cursor, wildcardpos);
          if (Stella.stringEqlP(casesensitiveP, "FALSE")) {
            fragment = Native.stringDowncase(fragment);
          }
          result = Cons.cons(StringWrapper.wrapString(fragment), result);
        }
        result = Cons.cons(GuiServer.SYM_GUI_SERVER_WILD, result);
        cursor = wildcardpos + 1;
      }
      if (cursor < matchstring.length()) {
        fragment = Native.string_subsequence(matchstring, cursor, matchstring.length());
        result = Cons.cons(StringWrapper.wrapString(fragment), result);
      }
      return (result.reverse());
    }
  }

  public static boolean searchStringMatchP(String inputstring, Cons matchlist) {
    if (matchlist == Stella.NIL) {
      if (inputstring.length() == 0) {
        return (true);
      }
      else {
        return (false);
      }
    }
    if (Stella_Object.symbolP(matchlist.value)) {
      { StringWrapper firstnonwild = GuiServer.getFirstNonWild(matchlist);
        int matchpos = 0;
        String restofinput = null;

        if (firstnonwild == null) {
          return (true);
        }
        if ((matchpos = Native.stringSearch(inputstring, firstnonwild.wrapperValue, 0)) != Stella.NULL_INTEGER) {
          restofinput = Native.string_subsequence(inputstring, matchpos + (firstnonwild.wrapperValue).length(), inputstring.length());
          return (GuiServer.searchStringMatchP(restofinput, GuiServer.getRestAfterFirstNonWild(matchlist)));
        }
        return (false);
      }
    }
    else {
      { StringWrapper fragment = ((StringWrapper)(matchlist.value));

        if ((fragment.wrapperValue).length() > inputstring.length()) {
          return (false);
        }
        else {
          { String inputstart = Native.string_subsequence(inputstring, 0, (fragment.wrapperValue).length());
            String restofinput = Native.string_subsequence(inputstring, (fragment.wrapperValue).length(), inputstring.length());

            return (Stella.stringEqlP(fragment.wrapperValue, inputstart) &&
                GuiServer.searchStringMatchP(restofinput, matchlist.rest));
          }
        }
      }
    }
  }

  public static StringWrapper getFirstNonWild(Cons matchlist) {
    { Stella_Object candidate = null;
      Cons iter000 = matchlist;

      for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
        candidate = iter000.value;
        if (Stella_Object.stringP(candidate)) {
          return (((StringWrapper)(candidate)));
        }
      }
    }
    return (null);
  }

  public static Cons getRestAfterFirstNonWild(Cons matchlist) {
    while (matchlist != null) {
      if (Stella_Object.stringP(matchlist.value)) {
        return (matchlist.rest);
      }
      matchlist = matchlist.rest;
    }
    return (null);
  }

  public static List searchLogicObjects(String modulename, List objects, Cons matchlist, String casesensitiveP) {
    { List result = List.newList();

      { LogicObject renamed_Object = null;
        Cons iter000 = objects.theConsList;
        Cons collect000 = null;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          renamed_Object = ((LogicObject)(iter000.value));
          if (GuiServer.searchStringMatchP(GuiServer.getLogicObjectName(renamed_Object, casesensitiveP), matchlist)) {
            if (collect000 == null) {
              {
                collect000 = Cons.cons(GuiServer.makeSearchResultItem(modulename, renamed_Object), Stella.NIL);
                if (result.theConsList == Stella.NIL) {
                  result.theConsList = collect000;
                }
                else {
                  Cons.addConsToEndOfConsList(result.theConsList, collect000);
                }
              }
            }
            else {
              {
                collect000.rest = Cons.cons(GuiServer.makeSearchResultItem(modulename, renamed_Object), Stella.NIL);
                collect000 = collect000.rest;
              }
            }
          }
        }
      }
      return (result);
    }
  }

  public static String getLogicObjectName(LogicObject renamed_Object, String casesensitiveP) {
    { String name = Logic.objectNameString(renamed_Object);

      if (Stella.stringEqlP(casesensitiveP, "TRUE")) {
        return (name);
      }
      else {
        return (Native.stringDowncase(name));
      }
    }
  }

  public static List searchConcepts(String modulename, Cons matchlist, String casesensitiveP) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename, null);

      return (GuiServer.searchLogicObjects(modulename, GuiServer.getAllConcepts(module, true), matchlist, casesensitiveP));
    }
  }

  public static List searchRelations(String modulename, Cons matchlist, String casesensitiveP) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename, null);

      return (GuiServer.searchLogicObjects(modulename, GuiServer.getAllRelations(module), matchlist, casesensitiveP));
    }
  }

  public static List searchInstances(String modulename, Cons matchlist, String casesensitiveP) {
    { Module module = edu.isi.powerloom.PLI.getModule(modulename, null);
      Iterator allinstances = Logic.allInstances(module, true);
      List nonskoleminstances = List.newList();

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
      return (GuiServer.searchLogicObjects(modulename, nonskoleminstances, matchlist, casesensitiveP));
    }
  }

  public static List searchAllModules(String searchstring, String searchinstanceP, String searchconceptP, String searchrelationP, String casesensitiveP) {
    { Module rootmodule = Stella.$ROOT_MODULE$;
      List allmodules = GuiServer.collectAllModules(rootmodule, List.newList());
      List result = List.newList();

      { Module module = null;
        Cons iter000 = allmodules.theConsList;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          module = ((Module)(iter000.value));
          result.concatenate(GuiServer.searchModule(module.moduleName, searchstring, searchinstanceP, searchconceptP, searchrelationP, casesensitiveP), Stella.NIL);
        }
      }
      return (result);
    }
  }

  public static List searchModule(String modulename, String searchstring, String searchinstanceP, String searchconceptP, String searchrelationP, String casesensitiveP) {
    { List conceptresults = List.newList();
      List relationresults = List.newList();
      List instanceresults = List.newList();
      Cons matchlist = GuiServer.parseMatchString(searchstring, casesensitiveP);
      List result = List.newList();
      Module module = edu.isi.powerloom.PLI.getModule(modulename, null);

      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          if (Stella.stringEqlP(searchinstanceP, "TRUE")) {
            instanceresults = GuiServer.searchInstances(modulename, matchlist, casesensitiveP);
          }
          if (Stella.stringEqlP(searchrelationP, "TRUE")) {
            relationresults = GuiServer.searchRelations(modulename, matchlist, casesensitiveP);
          }
          if (Stella.stringEqlP(searchconceptP, "TRUE")) {
            conceptresults = GuiServer.searchConcepts(modulename, matchlist, casesensitiveP);
          }
          result = conceptresults.concatenate(instanceresults, Cons.cons(relationresults, Stella.NIL));
          return (result);

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  public static PLSearchResultItem makeSearchResultItem(String modulename, LogicObject renamed_Object) {
    { PLObjectUnion union = GuiServer.makePlObjectUnion(renamed_Object);
      PLSearchResultItem result = PLSearchResultItem.new_PLSearchResultItem();

      result.ModuleName = modulename;
      result.PLObjectUnion = union;
      return (result);
    }
  }

  public static List getDirectoryListing(String currentdirectory) {
    { List filesindir = List.newList();
      List dirsindir = List.newList();
      List result = List.newList();

      result.insert(dirsindir);
      result.insert(filesindir);
      return (result);
    }
  }

  public static Stella_Object dispatchCall(String functionname, Cons args) {
    { FunctionCodeWrapper code = ((FunctionCodeWrapper)(GuiServer.$SERVER_DISPATCH_TABLE$.lookup(functionname)));

      if (code == null) {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("Couldn't find function `" + functionname + "' for dispatch.");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
      else {
        return (Stella.apply(code.wrapperValue, args));
      }
    }
  }

  public static void initializeDispatchTable() {
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-MODULES", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "serverGetModules", new java.lang.Class [] {})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-CONCEPTS-FOR-MODULE", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetConceptsForModule", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-INSTANCES-FOR-MODULE", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetInstancesForModule", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-RELATIONS-FOR-MODULE", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetRelationsForModule", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-DIRECT-INSTANCES-FOR-CONCEPT", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetDirectInstancesForConcept", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-INSTANCES-FOR-CONCEPT", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetInstancesForConcept", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-PROPOSITIONS-FOR-MODULE", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetPropositionsForModule", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-RELATIONS-FOR-CONCEPT", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetRelationsForConcept", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-INHERITED-RELATIONS-FOR-CONCEPT", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetInheritedRelationsForConcept", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-DOCUMENTATION-FOR-CONCEPT", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetDocumentationForConcept", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-SOURCE-FOR-CONCEPT", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetSourceForConcept", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-DOCUMENTATION-FOR-RELATION", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetDocumentationForRelation", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-DOCUMENTATION-FOR-INSTANCE", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetDocumentationForInstance", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-SUPERCONCEPTS-FOR-CONCEPT", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetSuperconceptsForConcept", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-SUPERRELATIONS-FOR-RELATION", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetSuperrelationsForRelation", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-INCLUDES-FOR-MODULE", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetIncludesForModule", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-USES-FOR-MODULE", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetUsesForModule", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-SHADOWED-SURROGATES-FOR-MODULE", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetShadowedSurrogatesForModule", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-VARIABLES-FOR-RELATION", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetVariablesForRelation", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-PROPOSITIONS-FOR-INSTANCE", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetPropositionsForInstance", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-TYPES-FOR-INSTANCE", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetTypesForInstance", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-PROPOSITIONS-FOR-CONCEPT", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetPropositionsForConcept", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-PROPOSITIONS-FOR-RELATION", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetPropositionsForRelation", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-RULES-FOR-CONCEPT", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetRulesForConcept", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-RULES-FOR-RELATION", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetRulesForRelation", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-PROPOSITIONS-FOR-INSTANCE-AND-RELATION", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetPropositionsForInstanceAndRelation", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-EVALUATE-LOGIC-COMMAND", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverEvaluateLogicCommand", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-LOADABLE-KBS", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "serverGetLoadableKbs", new java.lang.Class [] {})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-LOAD-KB", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverLoadKb", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-LOAD-KB2", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLFile", "serverLoadKb2", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLFile")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-SAVE-KB", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverSaveKb", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-SAVE-KB2", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverSaveKb2", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-CLEAR-KB", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLModule", "serverClearKb", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLModule")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-QUERY", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLQuery", "serverQuery", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLQuery"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-SEARCH", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLSearchParameter", "serverSearch", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLSearchParameter")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-DIRECTORY-LISTING", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetDirectoryListing", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-DEFAULT-DIRECTORY-LISTING", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetDefaultDirectoryListing", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-EXTENSION-FOR-RELATION", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetExtensionForRelation", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-RELATION", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetRelation", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-CONCEPT", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetConcept", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-INSTANCE", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetInstance", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-CONCEPT-COMPLETIONS", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetConceptCompletions", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-RELATION-COMPLETIONS", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetRelationCompletions", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-INSTANCE-COMPLETIONS", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverGetInstanceCompletions", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-DESTROY-OBJECT", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLString", "serverDestroyObject", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLString"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-EXPLANATION-FOR-QUERY", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.PLQuery", "serverGetExplanationForQuery", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.server.gui.PLQuery"), Native.find_java_class("edu.isi.powerloom.server.gui.PLString")})));
    GuiServer.$SERVER_DISPATCH_TABLE$.insertAt("SERVER-GET-INFO", FunctionCodeWrapper.wrapFunctionCode(Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "serverGetInfo", new java.lang.Class [] {})));
  }

  public static PLConceptContainer testServerGetConceptsForModule() {
    { PLString plstring = PLString.new_PLString();

      plstring.Value = "EELD";
      return (PLString.serverGetConceptsForModule(plstring));
    }
  }

  public static PLInstanceContainer testServerGetInstancesForModule() {
    { PLString plstring = PLString.new_PLString();

      plstring.Value = "LOGIC";
      return (PLString.serverGetInstancesForModule(plstring));
    }
  }

  public static PLRelationContainer testServerGetRelationsForModule() {
    { PLString plstring = PLString.new_PLString();

      plstring.Value = "PL-KERNEL-KB";
      return (PLString.serverGetRelationsForModule(plstring));
    }
  }

  public static PLInstanceContainer testServerGetDirectInstancesForConcept() {
    { PLString module = PLString.new_PLString();
      PLString concept = PLString.new_PLString();

      module.Value = "AIRCRAFT-KB";
      concept.Value = "AIRCRAFT";
      return (PLString.serverGetDirectInstancesForConcept(module, concept));
    }
  }

  public static PLInstanceContainer testServerGetInstancesForConcept() {
    { PLString module = PLString.new_PLString();
      PLString concept = PLString.new_PLString();

      module.Value = "AIRCRAFT-KB";
      concept.Value = "AIRCRAFT";
      return (PLString.serverGetInstancesForConcept(module, concept));
    }
  }

  public static PLPropositionContainer testServerGetPropositionsForModule() {
    { PLString plstring = PLString.new_PLString();

      plstring.Value = "AIRCRAFT-KB";
      return (PLString.serverGetPropositionsForModule(plstring));
    }
  }

  public static PLPropositionContainer testServerGetPropositionsForInstance() {
    { PLString modstring = PLString.new_PLString();
      PLString instancestring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      instancestring.Value = "F-117";
      return (PLString.serverGetPropositionsForInstance(modstring, instancestring));
    }
  }

  public static PLSurrogateCollection testServerGetTypesForInstance() {
    { PLString modstring = PLString.new_PLString();
      PLString instancestring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      instancestring.Value = "A-10";
      return (PLString.serverGetTypesForInstance(modstring, instancestring));
    }
  }

  public static PLString testServerGetDocumentationForInstance() {
    { PLString modstring = PLString.new_PLString();
      PLString instancestring = PLString.new_PLString();

      modstring.Value = "EELD";
      instancestring.Value = "Action_105";
      return (PLString.serverGetDocumentationForInstance(modstring, instancestring));
    }
  }

  public static PLRelationContainer testServerGetRelationsForConcept() {
    { PLString modstring = PLString.new_PLString();
      PLString instancestring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      instancestring.Value = "ENGINE";
      return (PLString.serverGetRelationsForConcept(modstring, instancestring));
    }
  }

  public static PLRelationContainer testServerGetInheritedRelationsForConcept() {
    { PLString modstring = PLString.new_PLString();
      PLString instancestring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      instancestring.Value = "AIRCRAFT";
      return (PLString.serverGetInheritedRelationsForConcept(modstring, instancestring));
    }
  }

  public static PLString testServerGetDocumentationForConcept() {
    { PLString modstring = PLString.new_PLString();
      PLString conceptstring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      conceptstring.Value = "JFC9";
      return (PLString.serverGetDocumentationForConcept(modstring, conceptstring));
    }
  }

  public static PLString testServerGetSourceForConcept() {
    { PLString modstring = PLString.new_PLString();
      PLString conceptstring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      conceptstring.Value = "AIR-ORGANIZATION";
      return (PLString.serverGetSourceForConcept(modstring, conceptstring));
    }
  }

  public static PLString testServerGetDocumentationForRelation() {
    { PLString modstring = PLString.new_PLString();
      PLString relationstring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      relationstring.Value = "ORDNANCE";
      return (PLString.serverGetDocumentationForRelation(modstring, relationstring));
    }
  }

  public static PLSurrogateCollection testServerGetSuperconceptsForConcept() {
    { PLString modstring = PLString.new_PLString();
      PLString conceptstring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      conceptstring.Value = "AIR-ORGANIZATION";
      return (PLString.serverGetSuperconceptsForConcept(modstring, conceptstring));
    }
  }

  public static PLSurrogateCollection testServerGetSuperrelationsForRelation() {
    { PLString modstring = PLString.new_PLString();
      PLString relationstring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      relationstring.Value = "AG-ORDNANCE";
      return (PLString.serverGetSuperrelationsForRelation(modstring, relationstring));
    }
  }

  public static PLSurrogateCollection testServerGetIncludesForModule() {
    { PLString modstring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      return (PLString.serverGetIncludesForModule(modstring));
    }
  }

  public static PLSurrogateCollection testServerGetShadowedSurrogatesForModule() {
    { PLString modstring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      return (PLString.serverGetShadowedSurrogatesForModule(modstring));
    }
  }

  public static PLSurrogateCollection testServerGetUsesForModule() {
    { PLString modstring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      return (PLString.serverGetUsesForModule(modstring));
    }
  }

  public static PLVariableList testServerGetVariablesForRelation() {
    { PLString modstring = PLString.new_PLString();
      PLString relationstring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      relationstring.Value = "STORES";
      return (PLString.serverGetVariablesForRelation(modstring, relationstring));
    }
  }

  public static PLPropositionContainer testServerGetPropositionsForConcept() {
    { PLString modstring = PLString.new_PLString();
      PLString instancestring = PLString.new_PLString();

      modstring.Value = "SUBMOD1";
      instancestring.Value = "WIDTH-RELATION";
      return (PLString.serverGetPropositionsForConcept(modstring, instancestring));
    }
  }

  public static PLPropositionContainer testServerGetRulesForConcept() {
    { PLString modstring = PLString.new_PLString();
      PLString instancestring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      instancestring.Value = "WIDTH-RELATION";
      return (PLString.serverGetRulesForConcept(modstring, instancestring));
    }
  }

  public static PLPropositionContainer testServerGetPropositionsForRelation() {
    { PLString modstring = PLString.new_PLString();
      PLString instancestring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      instancestring.Value = "ABCD";
      return (PLString.serverGetPropositionsForRelation(modstring, instancestring));
    }
  }

  public static PLPropositionContainer testServerGetRulesForRelation() {
    { PLString modstring = PLString.new_PLString();
      PLString instancestring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      instancestring.Value = "SMART-BOMB";
      return (PLString.serverGetRulesForRelation(modstring, instancestring));
    }
  }

  public static PLPropositionContainer testServerGetPropositionsForInstanceAndRelation() {
    { PLString modstring = PLString.new_PLString();
      PLString relationstring = PLString.new_PLString();
      PLString instancestring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      relationstring.Value = "FLEET-SIZE";
      instancestring.Value = "USAF";
      return (PLString.serverGetPropositionsForInstanceAndRelation(modstring, instancestring, relationstring));
    }
  }

  public static PLString testServerEvaluateLogicCommand(String command) {
    { PLString modstring = PLString.new_PLString();
      PLString commandstring = PLString.new_PLString();

      modstring.Value = "AIRCRAFT-KB";
      commandstring.Value = command;
      return (PLString.serverEvaluateLogicCommand(modstring, commandstring));
    }
  }

  public static PLString testServerLoadKb() {
    { PLString kbstring = PLString.new_PLString();

      kbstring.Value = "aircraft-kb";
      return (PLString.serverLoadKb(kbstring));
    }
  }

  public static void testServerClearKb() {
    { PLModule mod = PLModule.new_PLModule();

      mod.ModuleName = "AIRCRAFT-KB";
      PLModule.serverClearKb(mod);
    }
  }

  public static PLString testServerSaveKb() {
    { PLString kbstring = PLString.new_PLString();
      PLString modstring = PLString.new_PLString();
      PLString descstring = PLString.new_PLString();

      kbstring.Value = "aircraft-kb10";
      modstring.Value = "AIRCRAFT-KB";
      descstring.Value = "groovy new desc for aircraft-kb10";
      return (PLString.serverSaveKb(modstring, kbstring, descstring));
    }
  }

  public static PLFile testServerSaveKb2() {
    { PLString filestring = PLString.new_PLString();
      PLString modstring = PLString.new_PLString();

      filestring.Value = "/nfs/topaz/melz/cvscheckout/powerloom/sources/logic/demos/aircraft.ploom";
      modstring.Value = "AIRCRAFT-KB";
      return (PLString.serverSaveKb2(modstring, filestring));
    }
  }

  public static PLQuery makePlQuery() {
    { PLQuery plquery = PLQuery.new_PLQuery();

      plquery.Query = "(HAPPY ?X)";
      plquery.NumResults = "ALL";
      plquery.Module = "SUBMOD1";
      plquery.IsAsk = "FALSE";
      plquery.QueryName = "";
      plquery.InferenceLevel = "";
      plquery.Timeout = "";
      plquery.Moveout = "";
      plquery.MatchMode = "PARTIAL";
      plquery.MinScore = "";
      plquery.MaxUnknowns = "";
      plquery.MaximizeScore = "";
      plquery.DontOptimize = "";
      return (plquery);
    }
  }

  public static PLQueryResult testServerQuery() {
    { PLQueryResult result = null;
      PLString continuequeryP = PLString.new_PLString();
      PLQuery plquery = GuiServer.makePlQuery();

      continuequeryP.Value = "FALSE";
      Stella.STANDARD_OUTPUT.nativeStream.println("result1 is: " + PLQuery.serverQuery(plquery, continuequeryP));
      return (result);
    }
  }

  public static PLSearchResult testServerSearch1() {
    { PLSearchParameter searchparameter = PLSearchParameter.new_PLSearchParameter();

      searchparameter.ModuleName = "AIRCRAFT-KB";
      searchparameter.SearchString = "*pod*";
      searchparameter.SearchConcept = "TRUE";
      searchparameter.SearchRelation = "FALSE";
      searchparameter.SearchInstance = "FALSE";
      searchparameter.CaseSensitive = "FALSE";
      return (PLSearchParameter.serverSearch(searchparameter));
    }
  }

  public static PLDirectoryContents testServerGetDefaultDirectoryListing() {
    { PLString extension = PLString.new_PLString();

      extension.Value = "*.edu";
      return (PLString.serverGetDefaultDirectoryListing(extension));
    }
  }

  public static PLQueryResult testServerGetExtensionForRelation() {
    { PLString mod = PLString.new_PLString();
      PLString relation = PLString.new_PLString();

      mod.Value = "AIRCRAFT-KB";
      relation.Value = "cost";
      return (PLString.serverGetExtensionForRelation(mod, relation));
    }
  }

  public static PLRelationContainer testServerGetRelation() {
    { PLString mod = PLString.new_PLString();
      PLString relation = PLString.new_PLString();

      mod.Value = "AIRCRAFT-KB";
      relation.Value = "DUPLICATE-FREE";
      return (PLString.serverGetRelation(mod, relation));
    }
  }

  public static PLConceptContainer testServerGetConcept() {
    { PLString mod = PLString.new_PLString();
      PLString concept = PLString.new_PLString();

      mod.Value = "AIRCRAFT-KB";
      concept.Value = "DUPLICATE-FREE";
      return (PLString.serverGetConcept(mod, concept));
    }
  }

  public static PLInstanceContainer testServerGetInstance() {
    { PLString mod = PLString.new_PLString();
      PLString instance = PLString.new_PLString();

      mod.Value = "AIRCRAFT-KB";
      instance.Value = "A-10";
      return (PLString.serverGetInstance(mod, instance));
    }
  }

  public static PLConceptContainer testServerGetConceptCompletions() {
    { PLString mod = PLString.new_PLString();
      PLString prefix = PLString.new_PLString();

      mod.Value = "AIRCRAFT-KB";
      prefix.Value = "CO";
      return (PLString.serverGetConceptCompletions(mod, prefix));
    }
  }

  public static PLRelationContainer testServerGetRelationCompletions() {
    { PLString mod = PLString.new_PLString();
      PLString prefix = PLString.new_PLString();

      mod.Value = "AIRCRAFT-KB";
      prefix.Value = "CO";
      return (PLString.serverGetRelationCompletions(mod, prefix));
    }
  }

  public static PLInstanceContainer testServerGetInstanceCompletions() {
    { PLString mod = PLString.new_PLString();
      PLString prefix = PLString.new_PLString();

      mod.Value = "AIRCRAFT-KB";
      prefix.Value = "A";
      return (PLString.serverGetInstanceCompletions(mod, prefix));
    }
  }

  public static PLString testServerDestroyObject() {
    { PLString mod = PLString.new_PLString();
      PLString renamed_Object = PLString.new_PLString();

      mod.Value = "AIRCRAFT-KB";
      renamed_Object.Value = "SWING-WING";
      return (PLString.serverDestroyObject(mod, renamed_Object));
    }
  }

  public static PLString testServerGetExplanationForQuery() {
    { PLQuery plquery = GuiServer.makePlQuery();
      PLString resultnum = PLString.new_PLString();

      resultnum.Value = "4";
      return (PLQuery.serverGetExplanationForQuery(plquery, resultnum));
    }
  }

  public static PLServerInfo testServerGetInfo() {
    { PLServerInfo result = GuiServer.serverGetInfo();

      return (result);
    }
  }

  public static String serverProcessSoapRequest(String requestbody) {
    { String exception = null;
      String realresult = "";
      String soapresult = null;

      GuiServer.serverLog(GuiServer.KWD_HIGH, Cons.cons(StringWrapper.wrapString("Request: "), Cons.cons(StringWrapper.wrapString(requestbody), Stella.NIL)));
      try {
        { Cons soaptree = GuiServer.serverParseXmlDocumentString(requestbody);
          Stella_Object soapbodycontents = GuiServer.serverExtractSoapBodyContents(soaptree);

          realresult = GuiServer.serverInvokePowerloomMethod(((Cons)(soapbodycontents)));
        }
      } catch (LogicException e) {
        exception = GuiServer.serverMarshalException("PowerLoom Error", e);
      } catch (StellaException e) {
        exception = GuiServer.serverMarshalException("STELLA Error", e);
      } catch (java.lang.Exception e) {
        exception = GuiServer.serverMarshalException("Internal Error", e);
      }
      soapresult = GuiServer.serverGenerateSoapResponse(realresult, exception);
      GuiServer.serverLog(GuiServer.KWD_HIGH, Cons.cons(StringWrapper.wrapString("Response: "), Cons.cons(StringWrapper.wrapString(soapresult), Stella.NIL)));
      return (soapresult);
    }
  }

  public static String serverMarshalException(String type, java.lang.Exception exception) {
    { String message = Stella.exceptionMessage(exception);
      ServerException serverexception = ServerException.new_ServerException();
      String xmlstring = null;

      serverexception.Message = message;
      serverexception.Type = type;
      xmlstring = serverexception.TO_XML_STRING();
      return (xmlstring);
    }
  }

  public static String serverGenerateSoapResponse(String response, String exception) {
    if (exception != null) {
      return (GuiServer.$SOAP_EXCEPTION_PREFIX$ + exception + GuiServer.$SOAP_EXCEPTION_SUFFIX$);
    }
    else {
      return (GuiServer.$SOAP_RESULT_PREFIX$ + response + GuiServer.$SOAP_RESULT_SUFFIX$);
    }
  }

  public static Cons serverParseXmlDocumentString(String request) {
    { Cons value000 = Stella.NIL;

      { Stella_Object item = null;
        XmlExpressionIterator iter000 = InputStream.xmlExpressions(InputStringStream.newInputStringStream(request), null);
        Cons collect000 = null;

        while (iter000.nextP()) {
          item = iter000.value;
          if (collect000 == null) {
            {
              collect000 = Cons.cons(item, Stella.NIL);
              if (value000 == Stella.NIL) {
                value000 = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(value000, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(item, Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      { Cons value001 = value000;

        return (value001);
      }
    }
  }

  public static Stella_Object serverExtractSoapBodyContents(Cons parsetree) {
    { Cons body = ((Cons)(((Cons)(parsetree.value)).rest.rest.value));
      Stella_Object bodycontents = body.rest.rest.value;

      return (bodycontents);
    }
  }

  public static String serverExtractMethodName(Cons bodycontents) {
    return (((XmlObject)(bodycontents.value)).name);
  }

  public static Cons serverExtractArguments(Cons bodycontents) {
    { Object old$DefaultXmlObjectModule$000 = XmlObjects.$DEFAULT_XML_OBJECT_MODULE$.get();

      try {
        Native.setSpecial(XmlObjects.$DEFAULT_XML_OBJECT_MODULE$, GuiServer.$GUI_SERVER_MODULE$);
        { Cons rawargs = ((Cons)(bodycontents.rest.rest));
          Cons result = Stella.NIL;

          { Cons arg = null;
            Cons iter000 = rawargs;
            Cons collect000 = null;

            for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
              arg = ((Cons)(iter000.value));
              if (collect000 == null) {
                {
                  collect000 = Cons.cons(XmlObjects.FROM_XML_STRING(((StringWrapper)(arg.rest.rest.value)).wrapperValue), Stella.NIL);
                  if (result == Stella.NIL) {
                    result = collect000;
                  }
                  else {
                    Cons.addConsToEndOfConsList(result, collect000);
                  }
                }
              }
              else {
                {
                  collect000.rest = Cons.cons(XmlObjects.FROM_XML_STRING(((StringWrapper)(arg.rest.rest.value)).wrapperValue), Stella.NIL);
                  collect000 = collect000.rest;
                }
              }
            }
          }
          return (result);
        }

      } finally {
        XmlObjects.$DEFAULT_XML_OBJECT_MODULE$.set(old$DefaultXmlObjectModule$000);
      }
    }
  }

  public static String serverInvokePowerloomMethod(Cons bodycontents) {
    { String methodname = GuiServer.serverExtractMethodName(bodycontents);
      Cons arguments = GuiServer.serverExtractArguments(bodycontents);
      XMLObject result = ((XMLObject)(GuiServer.dispatchCall(methodname, arguments)));
      String marshaledresult = result.TO_XML_STRING();

      return (marshaledresult);
    }
  }

  public static void guiRequestHandler(edu.isi.webtools.http.HttpExchange xchg) {
    { String request = edu.isi.webtools.http.HttpExchange.getRequestBody(xchg);
      String response = GuiServer.serverProcessSoapRequest(request);

      edu.isi.webtools.http.HttpExchange.getReplyStream(xchg).print(response);
    }
  }

  public static void plguiHtmlPprintObject(Stella_Object self, OutputStream stream) {
    { Object old$LogicDialect$000 = Logic.$LOGIC_DIALECT$.get();
      Object old$PprintAtomicObjectRenderer$000 = edu.isi.ontosaurus.OntosaurusUtil.$PPRINT_ATOMIC_OBJECT_RENDERER$.get();

      try {
        Native.setSpecial(Logic.$LOGIC_DIALECT$, GuiServer.KWD_KIF);
        Native.setSpecial(edu.isi.ontosaurus.OntosaurusUtil.$PPRINT_ATOMIC_OBJECT_RENDERER$, Native.find_java_method("edu.isi.powerloom.server.gui.GuiServer", "plguiHtmlPprintAtomicObject", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}));
        if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(self), GuiServer.SGT_LOGIC_PROPOSITION)) {
          { Proposition self000 = ((Proposition)(self));

            { Keyword testValue000 = self000.kind;

              if ((testValue000 == GuiServer.KWD_ISA) ||
                  ((testValue000 == GuiServer.KWD_FUNCTION) ||
                   ((testValue000 == GuiServer.KWD_PREDICATE) ||
                    ((testValue000 == GuiServer.KWD_NOT) ||
                     (testValue000 == GuiServer.KWD_EQUIVALENT))))) {
              }
              else {
                {
                  stream.nativeStream.print("<PRE>");
                  edu.isi.ontosaurus.OntosaurusUtil.pprintObject(self000, stream.nativeStream);
                  stream.nativeStream.println("</PRE>");
                }
                return;
              }
            }
          }
        }
        else {
        }
        edu.isi.ontosaurus.OntosaurusUtil.pprintObject(self, stream.nativeStream);

      } finally {
        edu.isi.ontosaurus.OntosaurusUtil.$PPRINT_ATOMIC_OBJECT_RENDERER$.set(old$PprintAtomicObjectRenderer$000);
        Logic.$LOGIC_DIALECT$.set(old$LogicDialect$000);
      }
    }
  }

  public static void plguiHtmlPprintAtomicObject(Stella_Object self, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (!(self == null)) {
      { Surrogate testValue000 = Stella_Object.safePrimaryType(self);

        if (Surrogate.subtypeOfP(testValue000, GuiServer.SGT_STELLA_LITERAL_WRAPPER)) {
          { LiteralWrapper self000 = ((LiteralWrapper)(self));

            edu.isi.ontosaurus.OntosaurusUtil.pprintLiteralWrapperForHtml(self000, stream);
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, GuiServer.SGT_LOGIC_PATTERN_VARIABLE)) {
          { PatternVariable self000 = ((PatternVariable)(self));

            edu.isi.ontosaurus.OntosaurusUtil.pprintAtomicObject(self000, stream);
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, GuiServer.SGT_LOGIC_SKOLEM)) {
          { Skolem self000 = ((Skolem)(self));

            if (Logic.nativeValueOf(self000) != null) {
              edu.isi.ontosaurus.OntosaurusUtil.pprintAtomicObject(Logic.nativeValueOf(self000), stream);
            }
            else if (Logic.innermostOf(self000) != null) {
              if (Logic.innermostOf(self000) == self000) {
                {
                  stream.print("<FONT COLOR='#666666'>");
                  stream.print(Native.stringDowncase(Skolem.getSkolemPrintName(self000)));
                  stream.print("</FONT>");
                }
              }
              else {
                {
                  {
                    stream.print("<FONT COLOR='#996633'>");
                    stream.print(Native.stringDowncase(Skolem.getSkolemPrintName(self000)));
                    stream.print(Logic.VALUE_OF_SEPARATOR);
                    stream.print("</FONT>");
                  }
                  edu.isi.ontosaurus.OntosaurusUtil.pprintObject(Logic.innermostOf(self000), stream);
                }
              }
            }
            else {
              stream.print(Skolem.generateSkolem(self000));
            }
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, GuiServer.SGT_LOGIC_LOGIC_OBJECT)) {
          { LogicObject self000 = ((LogicObject)(self));

            if (self000.surrogateValueInverse != null) {
              GuiServer.printPlguiUrl(self000, stream);
            }
            else {
              stream.print("Unamed_Object");
            }
          }
        }
        else if (Surrogate.subtypeOfSurrogateP(testValue000)) {
          { Surrogate self000 = ((Surrogate)(self));

            if (self000.surrogateValue != null) {
              edu.isi.ontosaurus.OntosaurusUtil.pprintObject(self000.surrogateValue, stream);
            }
            else {
              stream.print(Surrogate.surrogateToSymbol(self000));
            }
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, GuiServer.SGT_STELLA_GENERALIZED_SYMBOL)) {
          { GeneralizedSymbol self000 = ((GeneralizedSymbol)(self));

            Stella.writeHtmlQuotingSpecialCharacters(stream, self000.symbolName);
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, GuiServer.SGT_STELLA_MODULE)) {
          { Module self000 = ((Module)(self));

            GuiServer.plguiWriteUrl(stream, ((String)(GuiServer.$PLGUI_URL_ACTION$.get())), "context", self000);
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, GuiServer.SGT_STELLA_THING)) {
          { Thing self000 = ((Thing)(self));

            if (self000.surrogateValueInverse != null) {
              stream.print(self000.surrogateValueInverse.symbolName);
            }
            else {
              stream.print(self000);
            }
          }
        }
        else {
          stream.print(self);
        }
      }
    }
  }

  /** Prints a URL following PowerLoom Plgui conventions.
   * @param theObject
   * @param nativestream
   */
  public static void printPlguiUrl(LogicObject theObject, edu.isi.stella.javalib.NativeOutputStream nativestream) {
    GuiServer.plguiWriteUrl(nativestream, ((String)(GuiServer.$PLGUI_URL_ACTION$.get())), edu.isi.ontosaurus.OntosaurusUtil.logicObjectDisplayType(theObject), theObject);
  }

  public static void plguiWriteUrlInDetail(edu.isi.stella.javalib.NativeOutputStream stream, String target, String action, String objecttype, String contextname, String objectname, String objecttitle, boolean rawtitleP) {
    action = action;
    stream.print("<A ");
    if (target != null) {
      stream.print("TARGET='" + target + "' ");
    }
    stream.print("HREF='plgui:navigateTo?type=" + Native.stringUpcase(objecttype) + "&id=");
    Stella.writeHtmlEscapingUrlSpecialCharacters(stream, objectname);
    stream.print("&module=");
    Stella.writeHtmlEscapingUrlSpecialCharacters(stream, contextname);
    stream.print("'>");
    if (rawtitleP) {
      stream.print(objecttitle);
    }
    else {
      Stella.writeHtmlQuotingSpecialCharacters(stream, objecttitle);
    }
    stream.print("</A>");
    return;
  }

  public static void plguiWriteUrl(edu.isi.stella.javalib.NativeOutputStream stream, String action, String objecttype, StandardObject renamed_Object) {
    { Surrogate testValue000 = Stella_Object.safePrimaryType(renamed_Object);

      if (Surrogate.subtypeOfP(testValue000, GuiServer.SGT_LOGIC_LOGIC_OBJECT)) {
        { LogicObject object000 = ((LogicObject)(renamed_Object));

          { Module writemodule = object000.homeModule();

            GuiServer.plguiWriteUrlInDetail(stream, null, action, objecttype, writemodule.name(), Logic.objectStringName(object000), Logic.objectStringName(object000), false);
          }
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, GuiServer.SGT_STELLA_MODULE)) {
        { Module object000 = ((Module)(renamed_Object));

          GuiServer.plguiWriteUrlInDetail(stream, null, action, objecttype, object000.name(), object000.name(), object000.name(), false);
        }
      }
      else {
        Stella.STANDARD_OUTPUT.nativeStream.print(Stella.STANDARD_ERROR + "Don't know how to write URL for object" + renamed_Object);
        stream.print(renamed_Object);
      }
    }
    return;
  }

  public static void printJustificationToHtmlFile(Justification justification, String file) {
    { Object old$ExplanationFormat$000 = Logic.$EXPLANATION_FORMAT$.get();
      Object old$ExplanationAudience$000 = Logic.$EXPLANATION_AUDIENCE$.get();
      Object old$LogicDialect$000 = Logic.$LOGIC_DIALECT$.get();
      Object old$MostRecentExplanationMapping$000 = Logic.$MOST_RECENT_EXPLANATION_MAPPING$.get();

      try {
        Native.setSpecial(Logic.$EXPLANATION_FORMAT$, GuiServer.KWD_HTML);
        Native.setSpecial(Logic.$EXPLANATION_AUDIENCE$, GuiServer.KWD_LAY);
        Native.setSpecial(Logic.$LOGIC_DIALECT$, GuiServer.KWD_KIF_ONTOSAURUS);
        Native.setSpecial(Logic.$MOST_RECENT_EXPLANATION_MAPPING$, KeyValueList.newKeyValueList());
        if (((FunctionCodeWrapper)(Logic.$LOGIC_DIALECT_PRINT_FUNCTIONS$.lookup(((Keyword)(Logic.$LOGIC_DIALECT$.get()))))) == null) {
          Native.setSpecial(Logic.$LOGIC_DIALECT$, GuiServer.KWD_KIF);
        }
        { ExplanationInfo info = Justification.registerJustification(Justification.visibleJustification(justification), ((KeyValueList)(Logic.$MOST_RECENT_EXPLANATION_MAPPING$.get())));

          info.label = "1";
          info.depth = 1;
        }
        { OutputFileStream stream = null;

          try {
            stream = Stella.openOutputFile(file, Stella.NIL);
            {
              stream.nativeStream.println();
              stream.nativeStream.println("Explanation #1 score=" + justification.matchScore + ":");
              stream.nativeStream.println();
            }
;
            Justification.printWhynotJustification(Justification.visibleJustification(justification), stream, Stella.NULL_INTEGER, GuiServer.KWD_BRIEF, false);

          } finally {
            if (stream != null) {
              stream.free();
            }
          }
        }

      } finally {
        Logic.$MOST_RECENT_EXPLANATION_MAPPING$.set(old$MostRecentExplanationMapping$000);
        Logic.$LOGIC_DIALECT$.set(old$LogicDialect$000);
        Logic.$EXPLANATION_AUDIENCE$.set(old$ExplanationAudience$000);
        Logic.$EXPLANATION_FORMAT$.set(old$ExplanationFormat$000);
      }
    }
  }

  public static String getJustificationString(Justification justification) {
    { Object old$ExplanationFormat$000 = Logic.$EXPLANATION_FORMAT$.get();
      Object old$ExplanationAudience$000 = Logic.$EXPLANATION_AUDIENCE$.get();
      Object old$LogicDialect$000 = Logic.$LOGIC_DIALECT$.get();
      Object old$MostRecentExplanationMapping$000 = Logic.$MOST_RECENT_EXPLANATION_MAPPING$.get();

      try {
        Native.setSpecial(Logic.$EXPLANATION_FORMAT$, GuiServer.KWD_HTML);
        Native.setSpecial(Logic.$EXPLANATION_AUDIENCE$, GuiServer.KWD_LAY);
        Native.setSpecial(Logic.$LOGIC_DIALECT$, GuiServer.KWD_JAVA_GUI_HTML);
        Native.setSpecial(Logic.$MOST_RECENT_EXPLANATION_MAPPING$, KeyValueList.newKeyValueList());
        { OutputStringStream stringstream = OutputStringStream.newOutputStringStream();
          ExplanationInfo info = Justification.registerJustification(Justification.visibleJustification(justification), ((KeyValueList)(Logic.$MOST_RECENT_EXPLANATION_MAPPING$.get())));

          info.label = "1";
          info.depth = 1;
          {
            stringstream.nativeStream.println();
            stringstream.nativeStream.print("Explanation #1");
          }
;
          if (justification.matchScore != Stella.NULL_FLOAT) {
            stringstream.nativeStream.print(" score=" + justification.matchScore);
          }
          {
            stringstream.nativeStream.println(":");
            stringstream.nativeStream.println();
          }
;
          Justification.printWhynotJustification(Justification.visibleJustification(justification), stringstream, Stella.NULL_INTEGER, GuiServer.KWD_BRIEF, false);
          { String result = stringstream.theStringReader();

            if (GuiServer.$PLGUI_EXPLANATION_TRACE_FILE$ != null) {
              { OutputFileStream out = null;

                try {
                  out = Stella.openOutputFile(GuiServer.$PLGUI_EXPLANATION_TRACE_FILE$, Stella.NIL);
                  out.nativeStream.println(result);

                } finally {
                  if (out != null) {
                    out.free();
                  }
                }
              }
            }
            return (result);
          }
        }

      } finally {
        Logic.$MOST_RECENT_EXPLANATION_MAPPING$.set(old$MostRecentExplanationMapping$000);
        Logic.$LOGIC_DIALECT$.set(old$LogicDialect$000);
        Logic.$EXPLANATION_AUDIENCE$.set(old$ExplanationAudience$000);
        Logic.$EXPLANATION_FORMAT$.set(old$ExplanationFormat$000);
      }
    }
  }

}
