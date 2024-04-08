//  -*- Mode: Java -*-
//
// OntosaurusUtil.java

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

public class OntosaurusUtil {
  public static Symbol SYM_ONTOSAURUS_STARTUP_HTML_MACROS = null;

  public static Symbol SYM_STELLA_METHOD_STARTUP_CLASSNAME = null;

  public static String $ERROR_BACKGROUND_COLOR$ = "FF9999";

  public static String $STANDARD_BACKGROUND_COLOR$ = "99CCFF";

  public static String $MODULE_BACKGROUND_COLOR$ = "9999CC";

  public static String $CONTROL_BACKGROUND_COLOR$ = "6699CC";

  public static String $ANSWER_BACKGROUND_COLOR$ = "99FFFF";

  public static String $FORM_BACKGROUND_COLOR$ = "6699CC";

  /** Tag used for prefix part of HREF generation in
   * <code>htmlWrite3PartHrefInDetail</code>.
   */
  public static String $HREF_PREFIX_TAG$ = "FONT COLOR='#666666' SIZE=-1";

  /** Tag used for suffix part of HREF generation in
   * <code>htmlWrite3PartHrefInDetail</code>.
   */
  public static String $HREF_SUFFIX_TAG$ = "FONT COLOR='#666666' SIZE=-1";

  public static Surrogate SGT_LOGIC_LOGIC_OBJECT = null;

  public static Surrogate SGT_STELLA_MODULE = null;

  public static String $POWERLOOM_COPYRIGHT_TRAILER$ = null;

  public static Symbol SYM_ONTOSAURUS_STARTUP_HTML_UTILITIES = null;

  /** Stores reusable key-value list for use by
   * 'print-descriptions-as-kif-rule'.
   */
  public static KeyValueMap REUSABLE_SKOLEM_MAPPING_TABLE = null;

  /** A function that takes two arguments, a Stella Object
   * and a NATIVE-(?) OUTPUT-STREAM, and writes a representation of that
   * object on that stream.  This will only be called on <code>atomic</code> Stella
   * objects -- compound objects like Conses, Propositions, etc. are handled
   * by the outer code.
   */
  public final static StellaSpecialVariable $PPRINT_ATOMIC_OBJECT_RENDERER$ = new StellaSpecialVariable();

  /** A function that takes two arguments, a Stella Proposition
   * and a NATIVE-(?) OUTPUT-STREAM, and writes something that precedes the
   * normal printed representation of a proposition.   This will only be called 
   * on <code>PROPOSITION</code> objects.
   */
  public final static StellaSpecialVariable $PPRINT_BEFORE_PROPOSITION_FUNCTION$ = new StellaSpecialVariable();

  /** A function that takes two arguments, a Stella Proposition
   * and a NATIVE-(?) OUTPUT-STREAM, and writes something that precedes the
   * normal printed representation of a proposition.   This will only be called 
   * on <code>PROPOSITION</code> objects.
   */
  public final static StellaSpecialVariable $PPRINT_AFTER_PROPOSITION_FUNCTION$ = new StellaSpecialVariable();

  /** A function that takes two arguments, a Stella Definition
   * and a NATIVE-(?) OUTPUT-STREAM, and writes something that precedes the
   * normal printed representation of a definition.   This will only be called 
   * on <code>DEFINITION</code> objects.
   */
  public final static StellaSpecialVariable $PPRINT_BEFORE_DEFINITION_FUNCTION$ = new StellaSpecialVariable();

  /** A function that takes two arguments, a Stella Definition
   * and a NATIVE-(?) OUTPUT-STREAM, and writes something that precedes the
   * normal printed representation of a definition.   This will only be called 
   * on <code>DEFINITION</code> objects.
   */
  public final static StellaSpecialVariable $PPRINT_AFTER_DEFINITION_FUNCTION$ = new StellaSpecialVariable();

  public final static StellaSpecialVariable $PPRINT_INDENT$ = new StellaSpecialVariable();

  public static Surrogate SGT_STELLA_LITERAL_WRAPPER = null;

  public static Surrogate SGT_LOGIC_PATTERN_VARIABLE = null;

  public static Surrogate SGT_LOGIC_SKOLEM = null;

  public static Surrogate SGT_LOGIC_LOGIC_THING = null;

  public static Surrogate SGT_STELLA_THING = null;

  public static Surrogate SGT_STELLA_MUTABLE_STRING_WRAPPER = null;

  public static Surrogate SGT_LOGIC_NAMED_DESCRIPTION = null;

  public static Surrogate SGT_LOGIC_PROPOSITION = null;

  public static Surrogate SGT_LOGIC_DESCRIPTION = null;

  public static Surrogate SGT_STELLA_COLLECTION = null;

  public static Surrogate SGT_STELLA_CONS = null;

  public static boolean $DOWNCASE_STANDARD_KIF_OPERATORSp$ = true;

  public static Surrogate SGT_PL_KERNEL_KB_AND = null;

  public static Surrogate SGT_PL_KERNEL_KB_OR = null;

  public static Surrogate SGT_PL_KERNEL_KB_NOT = null;

  public static Surrogate SGT_PL_KERNEL_KB_FAIL = null;

  public static Surrogate SGT_PL_KERNEL_KB_FORALL = null;

  public static Surrogate SGT_PL_KERNEL_KB_EXISTS = null;

  public static Surrogate SGT_PL_KERNEL_KB_KAPPA = null;

  public static Surrogate SGT_PL_KERNEL_KB_SUBSET_OF = null;

  public static Surrogate SGT_PL_KERNEL_KB_SETOF = null;

  public static Surrogate SGT_PL_KERNEL_KB_LISTOF = null;

  public static Surrogate SGT_PL_KERNEL_KB_BAGOF = null;

  public static Surrogate SGT_STELLA_TRUE = null;

  public static Surrogate SGT_STELLA_FALSE = null;

  public static Surrogate SGT_PL_KERNEL_KB_EQUIVALENT = null;

  public static Keyword KWD_PREDICATE = null;

  public static Keyword KWD_ISA = null;

  public static Keyword KWD_FUNCTION = null;

  public static Keyword KWD_AND = null;

  public static Keyword KWD_OR = null;

  public static Keyword KWD_NOT = null;

  public static Keyword KWD_EQUIVALENT = null;

  public static Keyword KWD_FAIL = null;

  public static Keyword KWD_CONSTANT = null;

  public static Keyword KWD_EXISTS = null;

  public static Symbol SYM_LOGIC_IO_VARIABLES = null;

  public static Keyword KWD_FORALL = null;

  public static Keyword KWD_IMPLIES = null;

  public static Symbol SYM_LOGIC_COMPLEMENT_DESCRIPTION = null;

  public static Symbol SYM_LOGIC_FORWARD_ONLYp = null;

  public static Surrogate SGT_STELLA_SYMBOL = null;

  public static Keyword KWD_KIF = null;

  public static Keyword KWD_KIF_ONTOSAURUS = null;

  public static Symbol SYM_ONTOSAURUS_STARTUP_NEW_PPRINT = null;

  public static Surrogate SGT_STELLA_GENERALIZED_SYMBOL = null;

  /** The action parameter for URL printing
   */
  public final static StellaSpecialVariable $ONTOSAURUS_URL_ACTION$ = new StellaSpecialVariable();

  public static Symbol SYM_ONTOSAURUS_STARTUP_HTML_PPRINT = null;

  public static Symbol SYM_ONTOSAURUS_STARTUP_CONTROL_PANEL_SCRIPT = null;

  public static Keyword KWD_CONCEPT = null;

  public static Keyword KWD_RELATION = null;

  public static Keyword KWD_CONTEXT = null;

  public static Keyword KWD_INSTANCE = null;

  public static Keyword KWD_QUERY = null;

  public static Keyword KWD_OBJECT = null;

  public static Keyword KWD_PREORDER = null;

  public static LogicObject $IMAGE_URL_RELATION$ = null;

  public static LogicObject $DOCUMENTATION_RELATION$ = null;

  public static Symbol SYM_STELLA_CODE_ONLYp = null;

  public static Symbol SYM_STELLA_NAMESPACEp = null;

  public static Keyword KWD_MODULE = null;

  public static Keyword KWD_EXACT = null;

  public static Keyword KWD_CASE_INSENSITIVE = null;

  public static Keyword KWD_SUBSTRING = null;

  public static Keyword KWD_WILDCARD = null;

  public static Keyword KWD_REGEX = null;

  public static Symbol SYM_ONTOSAURUS_PPRINT_ATOMIC_OBJECT_FOR_HTML = null;

  public static Keyword KWD_BAD_REQUEST = null;

  public static Keyword KWD_CONTENT_TYPE = null;

  public static Keyword KWD_HTML = null;

  public static Keyword KWD_DOCUMENTATION = null;

  public static Symbol SYM_ONTOSAURUS_STARTUP_HTML_DESCRIBE_OBJECT = null;

  public static String $POWERLOOM_REFERENCE_MANUAL_URL$ = "http://www.isi.edu/isd/LOOM/PowerLoom/documentation/manual/manual_frame.html";

  public static Keyword KWD_GET = null;

  public static Symbol SYM_ONTOSAURUS_STARTUP_TOP_WINDOW = null;

  /** A list of preset queries to make entry easier.  Format is
   * (&quot;Title&quot; &quot;ModuleName&quot; &quot;QueryBody&quot;) 
   */
  public final static StellaSpecialVariable $PRESET_QUERIES$ = new StellaSpecialVariable();

  public static String $GENERAL_QUERY_FORM_TEMPLATE$ = null;

  public static Keyword KWD_SORT_BY = null;

  public static Keyword KWD_VALUES = null;

  public static Keyword KWD_TIMEOUT = null;

  public static Symbol SYM_LOGIC_ALL = null;

  public static Symbol SYM_STELLA_EXISTS = null;

  public static Symbol SYM_LOGIC_JUSTIFICATION = null;

  public static Keyword KWD_LAY = null;

  public static Keyword KWD_POST = null;

  public static Keyword KWD_INTERNAL_ERROR = null;

  public static Symbol SYM_ONTOSAURUS_STARTUP_GENERAL_QUERY = null;

  /** If true, show binary relations between domain and range concepts as edges.
   */
  public static boolean $VIZ_SHOW_RELATIONSp$ = false;

  /** If true, show binary relations as attributes (2nd box in a concept label).
   */
  public static boolean $VIZ_SHOW_ATTRIBUTESp$ = false;

  /** If true, show defining rules (3rd box in a concept label).
   */
  public static boolean $VIZ_SHOW_RULESp$ = false;

  /** If true, put everything under artificial TOP node.
   */
  public static boolean $VIZ_ADD_TOPp$ = false;

  public static String $VIZ_NODE_COLOR$ = "yellow";

  public static String $VIZ_RELATION_COLOR$ = "blue";

  public static String $VIZ_RELATION_STYLE$ = "dashed";

  public static int $VIZ_FONT_SIZE$ = 7;

  public static Surrogate SGT_ONTOSAURUS_VIZ_INFO = null;

  public static Symbol SYM_STELLA_STREAM = null;

  public static Symbol SYM_ONTOSAURUS_ALLOWED_OBJECTS = null;

  public static Symbol SYM_ONTOSAURUS_SHOW_RELATIONSp = null;

  public static Symbol SYM_ONTOSAURUS_SHOW_ATTRIBUTESp = null;

  public static Symbol SYM_ONTOSAURUS_SHOW_RULESp = null;

  public static Symbol SYM_ONTOSAURUS_ADD_TOPp = null;

  public static Symbol SYM_ONTOSAURUS_NODE_COLOR = null;

  public static Symbol SYM_ONTOSAURUS_RELATION_COLOR = null;

  public static Symbol SYM_ONTOSAURUS_RELATION_STYLE = null;

  public static Symbol SYM_ONTOSAURUS_FONT_SIZE = null;

  public static String VIZ_TOP = "top";

  public static String VIZ_UNKNOWN = "unknown";

  public static Symbol SYM_LOGIC_pRELATION = null;

  public static Symbol SYM_ONTOSAURUS_pDOMAIN = null;

  public static Symbol SYM_STELLA_AND = null;

  public static Symbol SYM_PL_KERNEL_KB_NTH_DOMAIN = null;

  public static Symbol SYM_ONTOSAURUS_BINARY_RELATION = null;

  public static Keyword KWD_SINGLETONSp = null;

  public static Keyword KWD_INFERENCE_LEVEL = null;

  public static Keyword KWD_SHALLOW = null;

  public static Symbol SYM_ONTOSAURUS_M_VIZ_INFOdVIZ_GET_BINARY_RELATIONS_OF_QUERY_000 = null;

  public static Surrogate SGT_ONTOSAURUS_M_VIZ_INFOdVIZ_GET_BINARY_RELATIONS_OF_MEMO_TABLE_000 = null;

  public static Symbol SYM_ONTOSAURUS_M_VIZ_INFOdVIZ_GET_BINARY_RELATIONS_OF_QUERY_001 = null;

  /** Set of PowerLoom logic modules that shouldn't be visualized.
   * By default this is empty but it could be used to customize the visualizer.
   */
  public static List $VIZ_EXCLUDED_MODULES$ = null;

  public static Surrogate SGT_PL_KERNEL_KB_CONCEPT = null;

  public static Keyword KWD_MEDIUM = null;

  public static String $VIZ_DOT_PROGRAM$ = "dot";

  /** If true, visualization requests are enabled.
   */
  public static boolean $VIZ_SERVER_ENABLEDp$ = true;

  /** If true, visualization images will be linked with a
   * clickable image map.
   */
  public static boolean $VIZ_SERVER_IMAGE_MAPS_ENABLEDp$ = true;

  public static Surrogate SGT_ONTOSAURUS_F_VIZ_SERVER_EXPORT_OBJECT_MEMO_TABLE_000 = null;

  public static Keyword KWD_NOT_IMPLEMENTED = null;

  public static Keyword KWD_IMAGE_GIF = null;

  public static Keyword KWD_INPUT = null;

  public static Symbol SYM_ONTOSAURUS_STARTUP_VISUALIZE = null;

  public static Surrogate SGT_ONTOSAURUS_THREAD = null;

  public static Symbol SYM_ONTOSAURUS_RUN_FUNCTION = null;

  public static Symbol SYM_ONTOSAURUS_RUN_ARGUMENTS = null;

  public static Surrogate SGT_ONTOSAURUS_SHELL_PROCESS = null;

  public static Symbol SYM_STELLA_DIRECTORY = null;

  public static Symbol SYM_STELLA_INPUT_STREAM = null;

  public static Symbol SYM_ONTOSAURUS_NATIVE_STDIN = null;

  public static Symbol SYM_STELLA_OUTPUT_STREAM = null;

  public static Symbol SYM_ONTOSAURUS_NATIVE_STDOUT = null;

  public static Symbol SYM_ONTOSAURUS_ERROR_STREAM = null;

  public static Symbol SYM_ONTOSAURUS_NATIVE_STDERR = null;

  public static Symbol SYM_ONTOSAURUS_EXIT_STATUS = null;

  public static Keyword KWD_BLOCK = null;

  /** Allow disabling of <code>shellCommand</code> in remote execution contexts
   * for security purposes.
   */
  public final static StellaSpecialVariable $BLOCK_SHELL_COMMANDp$ = new StellaSpecialVariable();

  public static Keyword KWD_DIRECTORY = null;

  public static Surrogate SGT_STELLA_STRING = null;

  public static Keyword KWD_IGNORE_ERRORSp = null;

  public static Surrogate SGT_STELLA_BOOLEAN = null;

  public static Symbol SYM_ONTOSAURUS_STARTUP_SHELL = null;

  public static Symbol SYM_ONTOSAURUS_STARTUP_ONTOSAURUS_SYSTEM = null;

  public static String makeHtmlBodyTag(String backgroundcolor) {
    if (backgroundcolor == null) {
      backgroundcolor = OntosaurusUtil.$STANDARD_BACKGROUND_COLOR$;
    }
    return ("BODY BGCOLOR='" + backgroundcolor + "'");
  }

  public static void htmlLineBreak(edu.isi.stella.javalib.NativeOutputStream stream) {
    stream.println("<BR>");
  }

  public static String getHtmlObjectType(Stella_Object renamed_Object) {
    { String objecttype = null;

      { Surrogate testValue000 = Stella_Object.safePrimaryType(renamed_Object);

        if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
          { LogicObject object000 = ((LogicObject)(renamed_Object));

            if (Logic.classP(object000)) {
              objecttype = "concept";
            }
            else if (Logic.relationP(object000)) {
              objecttype = "relation";
            }
            else {
              objecttype = "object";
            }
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_STELLA_MODULE)) {
          { Module object000 = ((Module)(renamed_Object));

            objecttype = "context";
          }
        }
        else {
        }
      }
      return (objecttype);
    }
  }

  public static String getHtmlObjectLookupModule(Stella_Object renamed_Object) {
    { Module lookupmodule = renamed_Object.homeModule();

      if ((((Module)(Stella.$MODULE$.get())) != null) &&
          Context.visibleFromP(lookupmodule, ((Module)(Stella.$MODULE$.get())))) {
        lookupmodule = ((Module)(Stella.$MODULE$.get()));
      }
      return (lookupmodule.name());
    }
  }

  public static String getHtmlObjectHandle(Stella_Object renamed_Object) {
    { Symbol name = Logic.objectName(renamed_Object);

      if (name != null) {
        return (name.visibleName(true));
      }
      else if (Logic.functionOutputSkolemP(renamed_Object)) {
        return (Native.stringify(Logic.generateTerm(renamed_Object)));
      }
      else {
        return (Native.stringify(renamed_Object));
      }
    }
  }

  public static String getHtmlObjectTitle(Stella_Object renamed_Object) {
    { Symbol name = Logic.objectName(renamed_Object);

      if (name != null) {
        return (name.localPrintName(false));
      }
      else if (Logic.functionOutputSkolemP(renamed_Object)) {
        return (Native.stringify(Logic.generateTerm(renamed_Object)));
      }
      else {
        return (Native.stringify(renamed_Object));
      }
    }
  }

  public static String getHtmlObjectTitlePrefix(Stella_Object renamed_Object) {
    { Symbol name = Logic.objectName(renamed_Object);

      if (((name != null) &&
          (!(name == Symbol.lookupSymbolInModule(name.symbolName, ((Module)(Stella.$MODULE$.get())), false)))) ||
          ((name == null) &&
           (!Context.visibleFromP(renamed_Object.homeModule(), ((Module)(Stella.$MODULE$.get())))))) {
        return (renamed_Object.homeModule().moduleFullName + Stella.MODULE_SEPARATOR_STRING);
      }
      else {
        return ("");
      }
    }
  }

  public static void htmlWriteUrlInDetail(edu.isi.stella.javalib.NativeOutputStream stream, String action, String objecttype, String contextname, String objectname) {
    stream.print("/ploom/ontosaurus/do-action?" + action + "+" + objecttype + "+");
    Stella.writeHtmlEscapingUrlSpecialCharacters(stream, contextname);
    stream.print("+");
    Stella.writeHtmlEscapingUrlSpecialCharacters(stream, objectname);
  }

  public static void htmlWrite3PartHrefInDetail(edu.isi.stella.javalib.NativeOutputStream stream, String target, String action, String objectType, String contextName, String objectName, String objectTitlePrefix, String objectTitle, String objectTitleSuffix, boolean rawtitleP) {
    stream.print("<A ");
    if (target != null) {
      stream.print("TARGET='" + target + "' ");
    }
    stream.print("HREF='");
    OntosaurusUtil.htmlWriteUrlInDetail(stream, action, objectType, contextName, objectName);
    stream.print("'>");
    if (rawtitleP) {
      stream.print(objectTitlePrefix + objectTitle + objectTitleSuffix);
    }
    else {
      {
        if ((objectTitlePrefix != null) &&
            (!Stella.stringEqlP(objectTitlePrefix, ""))) {
          {
            stream.print("<" + OntosaurusUtil.$HREF_PREFIX_TAG$ + ">");
            Stella.writeHtmlQuotingSpecialCharacters(stream, objectTitlePrefix);
            stream.print("</" + Native.string_subsequence(OntosaurusUtil.$HREF_PREFIX_TAG$, 0, Native.string_position(OntosaurusUtil.$HREF_PREFIX_TAG$, ' ', 0)) + ">");
          }
        }
        Stella.writeHtmlQuotingSpecialCharacters(stream, objectTitle);
        if ((objectTitleSuffix != null) &&
            (!Stella.stringEqlP(objectTitleSuffix, ""))) {
          {
            stream.print("<" + OntosaurusUtil.$HREF_SUFFIX_TAG$ + ">");
            Stella.writeHtmlQuotingSpecialCharacters(stream, objectTitleSuffix);
            stream.print("</" + Native.string_subsequence(OntosaurusUtil.$HREF_SUFFIX_TAG$, 0, Native.string_position(OntosaurusUtil.$HREF_SUFFIX_TAG$, ' ', 0)) + ">");
          }
        }
      }
    }
    stream.print("</A>");
    return;
  }

  public static void htmlWriteHrefInDetail(edu.isi.stella.javalib.NativeOutputStream stream, String target, String action, String objecttype, String contextname, String objectname, String objecttitle, boolean rawtitleP) {
    OntosaurusUtil.htmlWrite3PartHrefInDetail(stream, target, action, objecttype, contextname, objectname, "", objecttitle, "", rawtitleP);
  }

  public static void htmlWriteHref(edu.isi.stella.javalib.NativeOutputStream stream, String action, String objecttype, StandardObject renamed_Object) {
    { Surrogate testValue000 = Stella_Object.safePrimaryType(renamed_Object);

      if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
        { LogicObject object000 = ((LogicObject)(renamed_Object));

          OntosaurusUtil.htmlWrite3PartHrefInDetail(stream, null, action, objecttype, OntosaurusUtil.getHtmlObjectLookupModule(object000), OntosaurusUtil.getHtmlObjectHandle(object000), OntosaurusUtil.getHtmlObjectTitlePrefix(object000), OntosaurusUtil.getHtmlObjectTitle(object000), "", false);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_STELLA_MODULE)) {
        { Module object000 = ((Module)(renamed_Object));

          OntosaurusUtil.htmlWriteHrefInDetail(stream, null, action, objecttype, object000.name(), object000.name(), object000.name(), false);
        }
      }
      else {
        Stella.STANDARD_OUTPUT.nativeStream.print(Stella.STANDARD_ERROR + "Don't know how to write HREF for object" + renamed_Object);
        stream.print(renamed_Object);
      }
    }
    return;
  }

  public static void htmlWriteUrl(edu.isi.stella.javalib.NativeOutputStream stream, String action, StandardObject renamed_Object) {
    { Surrogate testValue000 = Stella_Object.safePrimaryType(renamed_Object);

      if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
        { LogicObject object000 = ((LogicObject)(renamed_Object));

          OntosaurusUtil.htmlWriteUrlInDetail(stream, action, OntosaurusUtil.getHtmlObjectType(object000), OntosaurusUtil.getHtmlObjectLookupModule(object000), OntosaurusUtil.getHtmlObjectHandle(object000));
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_STELLA_MODULE)) {
        { Module object000 = ((Module)(renamed_Object));

          OntosaurusUtil.htmlWriteUrlInDetail(stream, action, OntosaurusUtil.getHtmlObjectType(object000), OntosaurusUtil.getHtmlObjectLookupModule(object000), OntosaurusUtil.getHtmlObjectHandle(object000));
        }
      }
      else {
        Stella.STANDARD_ERROR.nativeStream.println("Don't know how to write URL for object " + renamed_Object);
      }
    }
  }

  public static void htmlWriteJavascript(edu.isi.stella.javalib.NativeOutputStream stream, String js) {
    {
      stream.println("<SCRIPT LANGUAGE=\"JAVASCRIPT\"><!-- Hide from old browsers");
      stream.println(js);
      stream.println("// end hiding from old browsers -->");
      stream.println("</SCRIPT>");
    }
;
    return;
  }

  public static void htmlWriteHeaderWithTable(edu.isi.stella.javalib.NativeOutputStream stream, String title, String head) {
    {
      stream.print("<TABLE WIDTH='100%'>");
      stream.println();
      {
        stream.print("<TR>");
        {
          stream.print("<TD ALIGN='LEFT'>");
          {
            stream.print("<B>");
            Stella.writeHtmlQuotingSpecialCharacters(stream, title);
            stream.print("</B>");
          }
          stream.println("</TD>");
        }
        {
          stream.print("<TD ALIGN='RIGHT'>");
          {
            stream.print("<FONT SIZE=3 COLOR='#663333'>");
            Stella.writeHtmlQuotingSpecialCharacters(stream, head);
            stream.print("</FONT>");
          }
          stream.print("</TD>");
        }
        stream.println("</TR>");
      }
      stream.println("</TABLE>");
    }
    return;
  }

  public static void writeBookmarkIcon(LogicObject instance, edu.isi.stella.javalib.NativeOutputStream stream) {
    OntosaurusUtil.htmlWriteHrefInDetail(stream, "bookmark", "bookmark", "object", instance.homeModule().name(), Logic.objectName(instance).visibleName(true), "<IMG SRC='/ploom/icons/bookmark.gif' ALT='&lt;mark&gt;' BORDER='0' WIDTH='14' HEIGHT='15' />&nbsp;Bookmark</A>", true);
  }

  public static void htmlEmitImage(edu.isi.stella.javalib.NativeOutputStream stream, String imageurl, String alternatetext, int width, int height, String alignment, int border) {
    stream.print("<IMG SRC='" + imageurl + "'");
    if (alternatetext != null) {
      stream.print(" ALT='" + alternatetext + "'");
    }
    if (width != Stella.NULL_INTEGER) {
      stream.print(" WIDTH=" + width);
    }
    if (height != Stella.NULL_INTEGER) {
      stream.print(" HEIGHT=" + height);
    }
    if (alignment != null) {
      stream.print(" ALIGN='" + alignment + "'");
    }
    if (border != Stella.NULL_INTEGER) {
      stream.print(" BORDER='" + border + "'/>");
    }
    else {
      stream.print(" BORDER='0'/>");
    }
    return;
  }

  public static void htmlDisplayStringInParagraphs(String s, edu.isi.stella.javalib.NativeOutputStream stream) {
    { int start = 0;
      int pos = 0;

      while (pos != Stella.NULL_INTEGER) {
        pos = Native.stringSearch(s, "\n\n", start);
        {
          stream.print("<P>");
          Stella.writeHtmlQuotingSpecialCharacters(stream, Native.string_subsequence(s, start, pos));
          stream.println("</P>");
        }
        if (!(pos == Stella.NULL_INTEGER)) {
          start = pos + 2;
        }
      }
    }
  }

  public static void writePowerloomTrailer(edu.isi.stella.javalib.NativeOutputStream stream) {
    stream.print(OntosaurusUtil.$POWERLOOM_COPYRIGHT_TRAILER$);
  }

  public static void pprintNewline(edu.isi.stella.javalib.NativeOutputStream stream) {
    stream.println();
    { int i = Stella.NULL_INTEGER;
      int iter000 = 1;
      int upperBound000 = ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue();
      boolean unboundedP000 = upperBound000 == Stella.NULL_INTEGER;

      for (;unboundedP000 ||
                (iter000 <= upperBound000); iter000 = iter000 + 1) {
        i = iter000;
        i = i;
        stream.print(" ");
      }
    }
  }

  public static void pprintAtomicObject(Stella_Object self, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (!(self == null)) {
      { Surrogate testValue000 = Stella_Object.safePrimaryType(self);

        if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_STELLA_LITERAL_WRAPPER)) {
          { LiteralWrapper self000 = ((LiteralWrapper)(self));

            OntosaurusUtil.pprintLiteralWrapper(self000, stream);
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_PATTERN_VARIABLE)) {
          { PatternVariable self000 = ((PatternVariable)(self));

            if ((((KeyValueMap)(Logic.$SKOLEMNAMEMAPPINGTABLE$.get())) != null) &&
                (((Skolem)(((KeyValueMap)(Logic.$SKOLEMNAMEMAPPINGTABLE$.get())).lookup(self000))) != null)) {
              stream.print(PatternVariable.generateNameOfVariable(((PatternVariable)(((Skolem)(((KeyValueMap)(Logic.$SKOLEMNAMEMAPPINGTABLE$.get())).lookup(self000)))))));
            }
            else if ((((Justification)(Logic.$CURRENTJUSTIFICATION$.get())) != null) &&
                (Logic.justificationArgumentBoundTo(self000, null) != null)) {
              OntosaurusUtil.pprintObject(Logic.justificationArgumentBoundTo(self000, null), stream);
            }
            else {
              stream.print(PatternVariable.generateNameOfVariable(self000));
            }
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_SKOLEM)) {
          { Skolem self000 = ((Skolem)(self));

            if (Logic.nativeValueOf(self000) != null) {
              OntosaurusUtil.pprintAtomicObject(Logic.nativeValueOf(self000), stream);
            }
            else if (Logic.innermostOf(self000) != null) {
              stream.print(Native.stringDowncase(Skolem.getSkolemPrintName(self000)));
              if (!(Logic.innermostOf(self000) == self000)) {
                stream.print(Logic.VALUE_OF_SEPARATOR);
                OntosaurusUtil.pprintObject(Logic.innermostOf(self000), stream);
              }
              else if (self000.definingProposition != null) {
                stream.print(Logic.VALUE_OF_SEPARATOR);
                OntosaurusUtil.pprintFunctionTerm(self000.definingProposition, stream);
              }
              else {
              }
            }
            else {
              stream.print(Skolem.generateSkolem(self000));
            }
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
          { LogicObject self000 = ((LogicObject)(self));

            if (self000.surrogateValueInverse != null) {
              stream.print(Surrogate.surrogateToSymbol(self000.surrogateValueInverse));
            }
            else {
              stream.print("Unamed_Object");
            }
          }
        }
        else if (Surrogate.subtypeOfSurrogateP(testValue000)) {
          { Surrogate self000 = ((Surrogate)(self));

            stream.print(OntosaurusUtil.operatorToString(self000));
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_LOGIC_THING)) {
          { LogicThing self000 = ((LogicThing)(self));

            if (Logic.generateTerm(self000) != null) {
              OntosaurusUtil.pprintObject(Logic.generateTerm(self000), stream);
            }
            else if (self000.surrogateValueInverse != null) {
              stream.print(self000.surrogateValueInverse);
            }
            else {
              stream.print(self000);
            }
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_STELLA_THING)) {
          { Thing self000 = ((Thing)(self));

            if (self000.surrogateValueInverse != null) {
              stream.print(self000.surrogateValueInverse);
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

  public static void pprintLiteralWrapper(LiteralWrapper self, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Surrogate testValue000 = Stella_Object.safePrimaryType(self);

      if (Surrogate.subtypeOfBooleanP(testValue000)) {
        { BooleanWrapper self000 = ((BooleanWrapper)(self));

          stream.print(self000.wrapperValue);
        }
      }
      else if (Surrogate.subtypeOfIntegerP(testValue000)) {
        { IntegerWrapper self000 = ((IntegerWrapper)(self));

          stream.print(self000.wrapperValue);
        }
      }
      else if (Surrogate.subtypeOfFloatP(testValue000)) {
        { FloatWrapper self000 = ((FloatWrapper)(self));

          stream.print(self000.wrapperValue);
        }
      }
      else if (Surrogate.subtypeOfCharacterP(testValue000)) {
        { CharacterWrapper self000 = ((CharacterWrapper)(self));

          stream.print(self000.wrapperValue);
        }
      }
      else if (Surrogate.subtypeOfStringP(testValue000)) {
        { StringWrapper self000 = ((StringWrapper)(self));

          if (((Boolean)(Stella.$PRINTREADABLYp$.get())).booleanValue()) {
            stream.print("\"" + self000.wrapperValue + "\"");
          }
          else {
            stream.print(self000.wrapperValue);
          }
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_STELLA_MUTABLE_STRING_WRAPPER)) {
        { MutableStringWrapper self000 = ((MutableStringWrapper)(self));

          if (((Boolean)(Stella.$PRINTREADABLYp$.get())).booleanValue()) {
            stream.print("\"" + self000.wrapperValue + "\"");
          }
          else {
            stream.print(self000.wrapperValue);
          }
        }
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("`" + testValue000 + "' is not a valid case option");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  public static boolean pprintAsAtomicObjectP(Stella_Object self) {
    { Surrogate testValue000 = Stella_Object.safePrimaryType(self);

      if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_NAMED_DESCRIPTION)) {
        { NamedDescription self000 = ((NamedDescription)(self));

          return (true);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_PROPOSITION)) {
        { Proposition self000 = ((Proposition)(self));

          return (false);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_DESCRIPTION)) {
        { Description self000 = ((Description)(self));

          return (false);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_STELLA_COLLECTION)) {
        { Collection self000 = ((Collection)(self));

          return (false);
        }
      }
      else if (testValue000 == OntosaurusUtil.SGT_STELLA_CONS) {
        { Cons self000 = ((Cons)(self));

          return (false);
        }
      }
      else {
        return (true);
      }
    }
  }

  public static void pprintCompositeObject(Stella_Object self, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Surrogate testValue000 = Stella_Object.safePrimaryType(self);

      if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_PROPOSITION)) {
        { Proposition self000 = ((Proposition)(self));

          OntosaurusUtil.pprintProposition(self000, stream);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_DESCRIPTION)) {
        { Description self000 = ((Description)(self));

          OntosaurusUtil.pprintDescription(self000, stream);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_STELLA_COLLECTION)) {
        { Collection self000 = ((Collection)(self));

          OntosaurusUtil.pprintStellaCollection(self000, stream);
        }
      }
      else if (testValue000 == OntosaurusUtil.SGT_STELLA_CONS) {
        { Cons self000 = ((Cons)(self));

          OntosaurusUtil.pprintStellaCons(self000, stream);
        }
      }
      else {
        Stella.STANDARD_WARNING.nativeStream.println("Warning: UNKNOWN composite object: `" + self + "'");
      }
    }
  }

  public static void pprintObject(Stella_Object self, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (self == null) {
    }
    else if (!OntosaurusUtil.pprintAsAtomicObjectP(self)) {
      OntosaurusUtil.pprintCompositeObject(self, stream);
    }
    else if (((java.lang.reflect.Method)(OntosaurusUtil.$PPRINT_ATOMIC_OBJECT_RENDERER$.get())) != null) {
      edu.isi.stella.javalib.Native.funcall(((java.lang.reflect.Method)(OntosaurusUtil.$PPRINT_ATOMIC_OBJECT_RENDERER$.get())), null, new java.lang.Object [] {self, stream});
    }
    else {
      OntosaurusUtil.pprintAtomicObject(self, stream);
    }
  }

  public static void pprintArguments(Vector arguments, boolean separatelinesP, boolean omitlastargumentP, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (arguments == null) {
      return;
    }
    { Iterator argumentsiterator = (omitlastargumentP ? arguments.butLast() : ((Iterator)(arguments.allocateIterator())));
      int visibleargcount = Logic.visibleArgumentsCount(arguments);
      int argindex = 0;

      if (omitlastargumentP &&
          Logic.visibleArgumentP(arguments.last())) {
        visibleargcount = visibleargcount - 1;
      }
      { Stella_Object arg = null;
        Iterator iter000 = argumentsiterator;

        while (iter000.nextP()) {
          arg = iter000.value;
          if (Logic.visibleArgumentP(arg) ||
              (visibleargcount == 0)) {
            argindex = argindex + 1;
            if (argindex > 1) {
              if (separatelinesP) {
                OntosaurusUtil.pprintNewline(stream);
              }
              else {
                stream.print(" ");
              }
            }
            OntosaurusUtil.pprintObject(arg, stream);
          }
        }
      }
    }
  }

  public static boolean shortTermP(Stella_Object arg) {
    { Surrogate testValue000 = Stella_Object.safePrimaryType(arg);

      if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_STELLA_LITERAL_WRAPPER)) {
        { LiteralWrapper arg000 = ((LiteralWrapper)(arg));

          { Surrogate testValue001 = Stella_Object.safePrimaryType(arg000);

            if (Surrogate.subtypeOfStringP(testValue001)) {
              { StringWrapper arg001 = ((StringWrapper)(arg000));

                return ((arg001.wrapperValue).length() < 9);
              }
            }
            else if (Surrogate.subtypeOfP(testValue001, OntosaurusUtil.SGT_STELLA_MUTABLE_STRING_WRAPPER)) {
              { MutableStringWrapper arg001 = ((MutableStringWrapper)(arg000));

                return ((arg001.wrapperValue).length() < 9);
              }
            }
            else {
              return (true);
            }
          }
        }
      }
      else if (Surrogate.subtypeOfSymbolP(testValue000)) {
        { Symbol arg000 = ((Symbol)(arg));

          return ((arg000.symbolName).length() < 9);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_PATTERN_VARIABLE)) {
        { PatternVariable arg000 = ((PatternVariable)(arg));

          return ((arg000.skolemName.symbolName).length() < 9);
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
        { LogicObject arg000 = ((LogicObject)(arg));

          { Symbol name = Logic.objectName(arg000);

            if (name != null) {
              return ((name.symbolName).length() < 9);
            }
            else {
              return (false);
            }
          }
        }
      }
      else {
        return (false);
      }
    }
  }

  public static String operatorToString(Stella_Object operator) {
    if (operator == null) {
      return ("NULL");
    }
    { Surrogate testValue000 = Stella_Object.safePrimaryType(operator);

      if (Surrogate.subtypeOfSurrogateP(testValue000)) {
        { Surrogate operator000 = ((Surrogate)(operator));

          { String printname = Logic.stringifiedSurrogate(operator000);

            if ((operator000 == OntosaurusUtil.SGT_PL_KERNEL_KB_AND) ||
                ((operator000 == OntosaurusUtil.SGT_PL_KERNEL_KB_OR) ||
                 ((operator000 == OntosaurusUtil.SGT_PL_KERNEL_KB_NOT) ||
                  ((operator000 == OntosaurusUtil.SGT_PL_KERNEL_KB_FAIL) ||
                   ((operator000 == OntosaurusUtil.SGT_PL_KERNEL_KB_FORALL) ||
                    ((operator000 == OntosaurusUtil.SGT_PL_KERNEL_KB_EXISTS) ||
                     ((operator000 == OntosaurusUtil.SGT_PL_KERNEL_KB_KAPPA) ||
                      ((operator000 == OntosaurusUtil.SGT_PL_KERNEL_KB_SUBSET_OF) ||
                       ((operator000 == OntosaurusUtil.SGT_PL_KERNEL_KB_SETOF) ||
                        ((operator000 == OntosaurusUtil.SGT_PL_KERNEL_KB_LISTOF) ||
                         ((operator000 == OntosaurusUtil.SGT_PL_KERNEL_KB_BAGOF) ||
                          ((operator000 == OntosaurusUtil.SGT_STELLA_TRUE) ||
                           (operator000 == OntosaurusUtil.SGT_STELLA_FALSE))))))))))))) {
              if (OntosaurusUtil.$DOWNCASE_STANDARD_KIF_OPERATORSp$) {
                printname = Native.stringDowncase(printname);
              }
            }
            else if (operator000 == OntosaurusUtil.SGT_PL_KERNEL_KB_EQUIVALENT) {
              printname = "=";
            }
            else {
            }
            return (printname);
          }
        }
      }
      else if (Surrogate.subtypeOfSymbolP(testValue000)) {
        { Symbol operator000 = ((Symbol)(operator));

          return (Logic.maybeDowncase(operator000.symbolName));
        }
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("`" + testValue000 + "' is not a valid case option");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  public static void pprintOperatorWithArguments(String operatorname, Vector arguments, boolean separatelinesP, boolean omitlastargumentP, edu.isi.stella.javalib.NativeOutputStream stream) {
    { int operatorindent = operatorname.length() + 2;

      stream.print("(" + operatorname + " ");
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + operatorindent);
      OntosaurusUtil.pprintArguments(arguments, separatelinesP, omitlastargumentP, stream);
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - operatorindent);
      stream.print(")");
    }
  }

  public static void pprintRelationProposition(Proposition self, edu.isi.stella.javalib.NativeOutputStream stream) {
    { int nargs = self.arguments.length();

      stream.print("(");
      OntosaurusUtil.pprintObject(self.operator, stream);
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 3);
      { boolean testValue000 = false;

        if (nargs >= 4) {
          testValue000 = true;
        }
        else {
          {
            testValue000 = nargs == 3;
            if (testValue000) {
              { boolean alwaysP000 = true;

                { Stella_Object arg = null;
                  Vector vector000 = self.arguments;
                  int index000 = 0;
                  int length000 = vector000.length();

                  loop000 : for (;index000 < length000; index000 = index000 + 1) {
                    arg = (vector000.theArray)[index000];
                    if (!(!OntosaurusUtil.shortTermP(arg))) {
                      alwaysP000 = false;
                      break loop000;
                    }
                  }
                }
                testValue000 = alwaysP000;
              }
            }
          }
        }
        if (testValue000) {
          { Stella_Object arg = null;
            Vector vector001 = self.arguments;
            int index001 = 0;
            int length001 = vector001.length();

            for (;index001 < length001; index001 = index001 + 1) {
              arg = (vector001.theArray)[index001];
              OntosaurusUtil.pprintNewline(stream);
              OntosaurusUtil.pprintObject(arg, stream);
            }
          }
        }
        else {
          { Stella_Object arg = null;
            Vector vector002 = self.arguments;
            int index002 = 0;
            int length002 = vector002.length();

            for (;index002 < length002; index002 = index002 + 1) {
              arg = (vector002.theArray)[index002];
              if (OntosaurusUtil.pprintAsAtomicObjectP(arg)) {
                stream.print(" ");
              }
              else {
                OntosaurusUtil.pprintNewline(stream);
              }
              OntosaurusUtil.pprintObject(arg, stream);
            }
          }
        }
      }
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 3);
      stream.print(")");
    }
  }

  public static void pprintFunctionTerm(Proposition self, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Stella_Object skolem = (self.arguments.theArray)[(self.arguments.length() - 1)];

      OntosaurusUtil.htmlWriteHrefInDetail(stream, null, "show", OntosaurusUtil.getHtmlObjectType(skolem), OntosaurusUtil.getHtmlObjectLookupModule(skolem), OntosaurusUtil.getHtmlObjectHandle(skolem), "(", true);
    }
    OntosaurusUtil.pprintObject(self.operator, stream);
    { boolean testValue000 = false;

      if (self.arguments.length() >= 5) {
        testValue000 = true;
      }
      else {
        {
          testValue000 = self.arguments.length() == 4;
          if (testValue000) {
            { boolean alwaysP000 = true;

              { Stella_Object arg = null;
                Vector vector000 = self.arguments;
                int index000 = 0;
                int length000 = vector000.length();

                loop000 : for (;index000 < length000; index000 = index000 + 1) {
                  arg = (vector000.theArray)[index000];
                  if (!(!OntosaurusUtil.shortTermP(arg))) {
                    alwaysP000 = false;
                    break loop000;
                  }
                }
              }
              testValue000 = alwaysP000;
            }
          }
        }
      }
      if (testValue000) {
        { int indent = (self.operator.symbolName).length() + 2;
          boolean firstP = true;

          Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + indent);
          { Stella_Object arg = null;
            Iterator iter000 = self.arguments.butLast();

            while (iter000.nextP()) {
              arg = iter000.value;
              if (firstP) {
                {
                  stream.print(" ");
                  firstP = false;
                }
              }
              else {
                OntosaurusUtil.pprintNewline(stream);
              }
              OntosaurusUtil.pprintObject(arg, stream);
            }
          }
          Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - indent);
        }
      }
      else {
        { Stella_Object arg = null;
          Iterator iter001 = self.arguments.butLast();

          while (iter001.nextP()) {
            arg = iter001.value;
            stream.print(" ");
            OntosaurusUtil.pprintObject(arg, stream);
          }
        }
      }
    }
    stream.print(")");
  }

  public static void pprintFunctionProposition(Proposition self, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Stella_Object lastarg = self.arguments.last();

      stream.print("(= ");
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 3);
      OntosaurusUtil.pprintFunctionTerm(self, stream);
      if (OntosaurusUtil.pprintAsAtomicObjectP(lastarg)) {
        stream.print(" ");
      }
      else {
        OntosaurusUtil.pprintNewline(stream);
      }
      OntosaurusUtil.pprintObject(lastarg, stream);
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 3);
      stream.print(")");
    }
  }

  public static void pprintProposition(Proposition self, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (((java.lang.reflect.Method)(OntosaurusUtil.$PPRINT_BEFORE_PROPOSITION_FUNCTION$.get())) != null) {
      edu.isi.stella.javalib.Native.funcall(((java.lang.reflect.Method)(OntosaurusUtil.$PPRINT_BEFORE_PROPOSITION_FUNCTION$.get())), null, new java.lang.Object [] {self, stream});
    }
    { Keyword testValue000 = self.kind;

      if ((testValue000 == OntosaurusUtil.KWD_PREDICATE) ||
          (testValue000 == OntosaurusUtil.KWD_ISA)) {
        OntosaurusUtil.pprintRelationProposition(self, stream);
      }
      else if (testValue000 == OntosaurusUtil.KWD_FUNCTION) {
        if (((Boolean)(Logic.$PRINTFUNCTIONSASRELATIONSp$.get())).booleanValue()) {
          OntosaurusUtil.pprintRelationProposition(self, stream);
        }
        else {
          OntosaurusUtil.pprintFunctionProposition(self, stream);
        }
      }
      else if (testValue000 == OntosaurusUtil.KWD_AND) {
        stream.print("(");
        OntosaurusUtil.pprintObject(self.operator, stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 5);
        stream.print(" ");
        OntosaurusUtil.pprintArguments(self.arguments, true, false, stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 5);
        stream.print(")");
      }
      else if (testValue000 == OntosaurusUtil.KWD_OR) {
        stream.print("(");
        OntosaurusUtil.pprintObject(self.operator, stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 4);
        stream.print(" ");
        OntosaurusUtil.pprintArguments(self.arguments, true, false, stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 4);
        stream.print(")");
      }
      else if (testValue000 == OntosaurusUtil.KWD_NOT) {
        stream.print("(");
        OntosaurusUtil.pprintObject(self.operator, stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 5);
        stream.print(" ");
        OntosaurusUtil.pprintObject((self.arguments.theArray)[0], stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 5);
        stream.print(")");
      }
      else if (testValue000 == OntosaurusUtil.KWD_EQUIVALENT) {
        stream.print("(=");
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 3);
        stream.print(" ");
        OntosaurusUtil.pprintArguments(self.arguments, false, false, stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 3);
        stream.print(")");
      }
      else if (testValue000 == OntosaurusUtil.KWD_FAIL) {
        stream.print("(");
        OntosaurusUtil.pprintObject(self.operator, stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 6);
        stream.print(" ");
        OntosaurusUtil.pprintProposition(((Proposition)((self.arguments.theArray)[0])), stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 6);
        stream.print(")");
      }
      else if (testValue000 == OntosaurusUtil.KWD_CONSTANT) {
        OntosaurusUtil.pprintObject(Proposition.generateOperator(self), stream);
      }
      else if (testValue000 == OntosaurusUtil.KWD_EXISTS) {
        stream.print("(");
        OntosaurusUtil.pprintObject(self.operator, stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 8);
        stream.print(" ");
        OntosaurusUtil.pprintQuantifiedVariables(((Vector)(KeyValueList.dynamicSlotValue(self.dynamicSlots, OntosaurusUtil.SYM_LOGIC_IO_VARIABLES, null))), false, stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 5);
        OntosaurusUtil.pprintNewline(stream);
        OntosaurusUtil.pprintProposition(((Proposition)((self.arguments.theArray)[0])), stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 3);
        stream.print(")");
      }
      else if (testValue000 == OntosaurusUtil.KWD_FORALL) {
        stream.print("(");
        OntosaurusUtil.pprintObject(self.operator, stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 8);
        stream.print(" ");
        OntosaurusUtil.pprintQuantifiedVariables(((Vector)(KeyValueList.dynamicSlotValue(self.dynamicSlots, OntosaurusUtil.SYM_LOGIC_IO_VARIABLES, null))), false, stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 5);
        OntosaurusUtil.pprintNewline(stream);
        stream.print("(=> ");
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 4);
        OntosaurusUtil.pprintProposition(((Proposition)((self.arguments.theArray)[0])), stream);
        OntosaurusUtil.pprintNewline(stream);
        OntosaurusUtil.pprintProposition(((Proposition)((self.arguments.theArray)[1])), stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 7);
        stream.print(")");
      }
      else if (testValue000 == OntosaurusUtil.KWD_IMPLIES) {
        OntosaurusUtil.pprintImpliesProposition(self, stream);
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("`" + testValue000 + "' is not a valid case option");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
    }
    if (((java.lang.reflect.Method)(OntosaurusUtil.$PPRINT_AFTER_PROPOSITION_FUNCTION$.get())) != null) {
      edu.isi.stella.javalib.Native.funcall(((java.lang.reflect.Method)(OntosaurusUtil.$PPRINT_AFTER_PROPOSITION_FUNCTION$.get())), null, new java.lang.Object [] {self, stream});
    }
  }

  public static void pprintQuantifiedVariables(Vector variables, boolean includetypesP, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (variables == null) {
      return;
    }
    stream.print("(");
    Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 1);
    { Skolem vbl = null;
      Vector vector000 = variables;
      int index000 = 0;
      int length000 = vector000.length();
      int i = Stella.NULL_INTEGER;
      int iter000 = 1;

      for (;index000 < length000; index000 = index000 + 1, iter000 = iter000 + 1) {
        vbl = ((Skolem)((vector000.theArray)[index000]));
        i = iter000;
        if (includetypesP) {
          stream.print("(");
        }
        { Surrogate testValue000 = Stella_Object.safePrimaryType(vbl);

          if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_PATTERN_VARIABLE)) {
            { PatternVariable vbl000 = ((PatternVariable)(vbl));

              OntosaurusUtil.pprintObject(vbl000, stream);
            }
          }
          else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_SKOLEM)) {
            { Skolem vbl000 = ((Skolem)(vbl));

              OntosaurusUtil.pprintObject(vbl000, stream);
            }
          }
          else {
            { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

              stream000.nativeStream.print("`" + testValue000 + "' is not a valid case option");
              throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
            }
          }
        }
        if (includetypesP) {
          OntosaurusUtil.pprintObject(Logic.logicalType(vbl), stream);
          stream.print(")");
        }
        if (i < variables.length()) {
          if (includetypesP) {
            OntosaurusUtil.pprintNewline(stream);
          }
          else {
            stream.print(" ");
          }
        }
      }
    }
    Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 1);
    stream.print(")");
  }

  public static void pprintNamedDescription(NamedDescription self, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (((java.lang.reflect.Method)(OntosaurusUtil.$PPRINT_ATOMIC_OBJECT_RENDERER$.get())) != null) {
      edu.isi.stella.javalib.Native.funcall(((java.lang.reflect.Method)(OntosaurusUtil.$PPRINT_ATOMIC_OBJECT_RENDERER$.get())), null, new java.lang.Object [] {self, stream});
    }
    else {
      OntosaurusUtil.pprintAtomicObject(self, stream);
    }
  }

  public static void pprintDescription(Description self, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (Description.namedDescriptionP(self)) {
      OntosaurusUtil.pprintNamedDescription(((NamedDescription)(self)), stream);
    }
    else if (((Description)(KeyValueList.dynamicSlotValue(self.dynamicSlots, OntosaurusUtil.SYM_LOGIC_COMPLEMENT_DESCRIPTION, null))) != null) {
      stream.print("(" + OntosaurusUtil.operatorToString(OntosaurusUtil.SGT_PL_KERNEL_KB_NOT) + " ");
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 5);
      OntosaurusUtil.pprintObject(((Description)(KeyValueList.dynamicSlotValue(self.dynamicSlots, OntosaurusUtil.SYM_LOGIC_COMPLEMENT_DESCRIPTION, null))), stream);
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 5);
      stream.print(")");
    }
    else {
      stream.print("(" + OntosaurusUtil.operatorToString(OntosaurusUtil.SGT_PL_KERNEL_KB_KAPPA) + " ");
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 7);
      OntosaurusUtil.pprintObject(self.ioVariables, stream);
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 4);
      OntosaurusUtil.pprintObject(self.proposition, stream);
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 3);
      stream.print(")");
    }
  }

  public static void pprintDescriptionBody(Description description, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (description.proposition == null) {
      stream.print("(");
      OntosaurusUtil.pprintObject(description.surrogateValueInverse, stream);
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 3);
      if (((KeyValueMap)(Logic.$SKOLEMNAMEMAPPINGTABLE$.get())) != null) {
        { PatternVariable var = null;
          Vector vector000 = ((NamedDescription)(description)).ioVariables;
          int index000 = 0;
          int length000 = vector000.length();

          for (;index000 < length000; index000 = index000 + 1) {
            var = ((PatternVariable)((vector000.theArray)[index000]));
            stream.print(" ");
            if (((Skolem)(((KeyValueMap)(Logic.$SKOLEMNAMEMAPPINGTABLE$.get())).lookup(var))) != null) {
              OntosaurusUtil.pprintObject(((Skolem)(((KeyValueMap)(Logic.$SKOLEMNAMEMAPPINGTABLE$.get())).lookup(var))), stream);
            }
            else {
              OntosaurusUtil.pprintObject(var, stream);
            }
          }
        }
      }
      else {
        { Symbol name = null;
          Cons iter000 = ((NamedDescription)(description)).ioVariableNames.theConsList;

          for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
            name = ((Symbol)(iter000.value));
            stream.print(" ");
            OntosaurusUtil.pprintObject(name, stream);
          }
        }
      }
      stream.print(")");
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 3);
    }
    else {
      OntosaurusUtil.pprintProposition(description.proposition, stream);
    }
  }

  public static void pprintNamedDescriptionsAsRule(NamedDescription head, NamedDescription tail, String operatorprefix, edu.isi.stella.javalib.NativeOutputStream stream) {
    { int operatorindent = operatorprefix.length() + 2;
      Cons variables = Stella.NIL;

      { Symbol v = null;
        Cons iter000 = Logic.SYSTEM_DEFINED_ARGUMENT_NAMES;
        IntegerIntervalIterator i = Stella.interval(1, head.arity());
        Cons collect000 = null;

        for (;(!(iter000 == Stella.NIL)) &&
                  i.nextP(); iter000 = iter000.rest) {
          v = ((Symbol)(iter000.value));
          if (collect000 == null) {
            {
              collect000 = Cons.cons(v, Stella.NIL);
              if (variables == Stella.NIL) {
                variables = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(variables, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(v, Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 3);
      stream.print("(" + OntosaurusUtil.operatorToString(OntosaurusUtil.SGT_PL_KERNEL_KB_FORALL) + " (");
      OntosaurusUtil.pprintObject(variables.value, stream);
      { Stella_Object v = null;
        Cons iter001 = variables.rest;

        for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
          v = iter001.value;
          stream.print(" ");
          OntosaurusUtil.pprintObject(v, stream);
        }
      }
      stream.print(")");
      OntosaurusUtil.pprintNewline(stream);
      stream.print("(" + operatorprefix + " (");
      OntosaurusUtil.pprintObject(head, stream);
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + operatorindent);
      { Stella_Object v = null;
        Cons iter002 = variables;

        for (;!(iter002 == Stella.NIL); iter002 = iter002.rest) {
          v = iter002.value;
          stream.print(" ");
          OntosaurusUtil.pprintObject(v, stream);
        }
      }
      stream.print(")");
      OntosaurusUtil.pprintNewline(stream);
      stream.print("(");
      OntosaurusUtil.pprintObject(tail, stream);
      { Stella_Object v = null;
        Cons iter003 = variables;

        for (;!(iter003 == Stella.NIL); iter003 = iter003.rest) {
          v = iter003.value;
          stream.print(" ");
          OntosaurusUtil.pprintObject(v, stream);
        }
      }
      stream.print("))");
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - operatorindent);
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 3);
    }
  }

  public static void helpPprintDescriptionsAsRule(Description desc, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Vector existentials = Logic.copyConsListToVariablesVector(Description.topLevelExistentialVariables(desc));
      boolean existentialvariablesP = existentials.nonEmptyP();

      if (existentialvariablesP) {
        stream.print("(" + OntosaurusUtil.operatorToString(OntosaurusUtil.SGT_PL_KERNEL_KB_EXISTS) + " ");
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 8);
        OntosaurusUtil.pprintQuantifiedVariables(existentials, false, stream);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 5);
        OntosaurusUtil.pprintNewline(stream);
      }
      OntosaurusUtil.pprintDescriptionBody(desc, stream);
      if (existentialvariablesP) {
        stream.print(")");
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 3);
      }
    }
  }

  public static void pprintDescriptionsAsRule(Description head, Description tail, Proposition rule, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Vector headvariables = null;
      Vector tailvariables = null;
      boolean forwardruleP = ((BooleanWrapper)(KeyValueList.dynamicSlotValue(rule.dynamicSlots, OntosaurusUtil.SYM_LOGIC_FORWARD_ONLYp, Stella.FALSE_WRAPPER))).wrapperValue;
      String operatorprefix = Proposition.chooseImplicationOperator(rule, forwardruleP).symbolName;
      int operatorindent = operatorprefix.length() + 2;

      if (head.deletedP() ||
          tail.deletedP()) {
        { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();

          try {
            Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, false);
            OntosaurusUtil.pprintObject(StringWrapper.wrapString("(=> <DeLeTeD ArGuMeNt(S)>)"), stream);

          } finally {
            Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
          }
        }
        return;
      }
      if (forwardruleP) {
        { Description temp = head;

          head = tail;
          tail = temp;
        }
      }
      if ((tail.proposition == null) &&
          (head.proposition == null)) {
        OntosaurusUtil.pprintNamedDescriptionsAsRule(((NamedDescription)(head)), ((NamedDescription)(tail)), operatorprefix, stream);
        return;
      }
      headvariables = head.ioVariables;
      tailvariables = tail.ioVariables;
      if (tail.proposition == null) {
        tailvariables = headvariables;
      }
      else if (head.proposition == null) {
        headvariables = tailvariables;
      }
      OntosaurusUtil.REUSABLE_SKOLEM_MAPPING_TABLE.clear();
      { PatternVariable tailvbl = null;
        Vector vector000 = tailvariables;
        int index000 = 0;
        int length000 = vector000.length();
        PatternVariable headvbl = null;
        Vector vector001 = headvariables;
        int index001 = 0;
        int length001 = vector001.length();

        for (;(index000 < length000) &&
                  (index001 < length001); index000 = index000 + 1, index001 = index001 + 1) {
          tailvbl = ((PatternVariable)((vector000.theArray)[index000]));
          headvbl = ((PatternVariable)((vector001.theArray)[index001]));
          OntosaurusUtil.REUSABLE_SKOLEM_MAPPING_TABLE.insertAt(headvbl, tailvbl);
        }
      }
      stream.print("(" + OntosaurusUtil.operatorToString(OntosaurusUtil.SGT_PL_KERNEL_KB_FORALL) + " ");
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 8);
      OntosaurusUtil.pprintQuantifiedVariables(tailvariables, false, stream);
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 5);
      OntosaurusUtil.pprintNewline(stream);
      stream.print("(");
      { Object old$PrintreadablyP$001 = Stella.$PRINTREADABLYp$.get();

        try {
          Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, false);
          OntosaurusUtil.pprintObject(StringWrapper.wrapString(operatorprefix), stream);

        } finally {
          Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$001);
        }
      }
      stream.print(" ");
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + operatorindent);
      { Object old$Skolemnamemappingtable$000 = Logic.$SKOLEMNAMEMAPPINGTABLE$.get();

        try {
          Native.setSpecial(Logic.$SKOLEMNAMEMAPPINGTABLE$, OntosaurusUtil.REUSABLE_SKOLEM_MAPPING_TABLE);
          OntosaurusUtil.helpPprintDescriptionsAsRule(head, stream);

        } finally {
          Logic.$SKOLEMNAMEMAPPINGTABLE$.set(old$Skolemnamemappingtable$000);
        }
      }
      OntosaurusUtil.REUSABLE_SKOLEM_MAPPING_TABLE.clear();
      OntosaurusUtil.pprintNewline(stream);
      OntosaurusUtil.helpPprintDescriptionsAsRule(tail, stream);
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - operatorindent);
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 3);
      stream.print("))");
    }
  }

  public static void pprintImpliesProposition(Proposition self, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Stella_Object tailarg = (self.arguments.theArray)[0];
      Stella_Object headarg = (self.arguments.theArray)[1];

      if (Stella_Object.isaP(headarg, OntosaurusUtil.SGT_LOGIC_DESCRIPTION) &&
          Stella_Object.isaP(tailarg, OntosaurusUtil.SGT_LOGIC_DESCRIPTION)) {
        OntosaurusUtil.pprintDescriptionsAsRule(((Description)(headarg)), ((Description)(tailarg)), self, stream);
      }
      else {
        OntosaurusUtil.pprintOperatorWithArguments(OntosaurusUtil.operatorToString(OntosaurusUtil.SGT_PL_KERNEL_KB_SUBSET_OF), self.arguments, false, false, stream);
      }
    }
  }

  public static void pprintStellaCollection(Collection self, edu.isi.stella.javalib.NativeOutputStream stream) {
    { boolean setP = self.noDuplicatesP();
      boolean firstP = true;

      if (setP) {
        {
          stream.print("(" + OntosaurusUtil.operatorToString(OntosaurusUtil.SGT_PL_KERNEL_KB_SETOF));
          Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 7);
        }
      }
      else {
        {
          stream.print("(" + OntosaurusUtil.operatorToString(OntosaurusUtil.SGT_PL_KERNEL_KB_LISTOF));
          Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 8);
        }
      }
      switch (self.length()) {
        case 0: 
        break;
        case 1: 
          { Stella_Object m = null;
            Iterator iter000 = ((Iterator)(self.allocateIterator()));

            while (iter000.nextP()) {
              m = iter000.value;
              OntosaurusUtil.pprintObject(m, stream);
            }
          }
        break;
        case 2: 
        case 3: 
          { Stella_Object m = null;
            Iterator iter001 = ((Iterator)(self.allocateIterator()));

            while (iter001.nextP()) {
              m = iter001.value;
              stream.print(" ");
              OntosaurusUtil.pprintObject(m, stream);
            }
          }
        break;
        default:
          { Stella_Object m = null;
            Iterator iter002 = ((Iterator)(self.allocateIterator()));

            while (iter002.nextP()) {
              m = iter002.value;
              if (firstP) {
                {
                  stream.print(" ");
                  firstP = false;
                }
              }
              else {
                OntosaurusUtil.pprintNewline(stream);
              }
              OntosaurusUtil.pprintObject(m, stream);
            }
          }
        break;
      }
      stream.print(")");
      if (setP) {
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 7);
      }
      else {
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 8);
      }
    }
  }

  public static void pprintStellaCons(Cons self, edu.isi.stella.javalib.NativeOutputStream stream) {
    stream.print("(");
    Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 1);
    switch (self.length()) {
      case 0: 
      break;
      case 1: 
        OntosaurusUtil.pprintObject(self.value, stream);
      break;
      case 2: 
        OntosaurusUtil.pprintObject(self.value, stream);
        stream.print(" ");
        OntosaurusUtil.pprintObject(self.rest.value, stream);
      break;
      case 3: 
        OntosaurusUtil.pprintObject(self.value, stream);
        stream.print(" ");
        OntosaurusUtil.pprintObject(self.rest.value, stream);
        stream.print(" ");
        OntosaurusUtil.pprintObject(self.rest.rest.value, stream);
      break;
      case 4: 
      case 5: 
        OntosaurusUtil.pprintObject(self.value, stream);
        { Stella_Object obj = null;
          Cons iter000 = self.rest;

          for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
            obj = iter000.value;
            if (((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() > 2) {
              OntosaurusUtil.pprintNewline(stream);
            }
            else {
              stream.print(" ");
            }
            OntosaurusUtil.pprintObject(obj, stream);
          }
        }
      break;
      default:
        OntosaurusUtil.pprintObject(self.value, stream);
        { Stella_Object obj = null;
          Cons iter001 = self.rest;

          for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
            obj = iter001.value;
            OntosaurusUtil.pprintNewline(stream);
            OntosaurusUtil.pprintObject(obj, stream);
          }
        }
      break;
    }
    stream.print(")");
    Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 1);
  }

  public static void pprintDefinition(Cons self, boolean hasvariablesP, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (((java.lang.reflect.Method)(OntosaurusUtil.$PPRINT_BEFORE_DEFINITION_FUNCTION$.get())) != null) {
      edu.isi.stella.javalib.Native.funcall(((java.lang.reflect.Method)(OntosaurusUtil.$PPRINT_BEFORE_DEFINITION_FUNCTION$.get())), null, new java.lang.Object [] {self, stream});
    }
    stream.print("(");
    OntosaurusUtil.pprintObject(self.value, stream);
    stream.print(" ");
    if (Stella_Object.isaP(self.rest.value, OntosaurusUtil.SGT_STELLA_SYMBOL)) {
      OntosaurusUtil.pprintAtomicObject(self.rest.value, stream);
    }
    else {
      OntosaurusUtil.pprintObject(self.rest.value, stream);
    }
    if (!hasvariablesP) {
      self = self.rest.rest;
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 3);
    }
    else if (((Cons)(self.rest.rest.value)).length() > 5) {
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 10);
      OntosaurusUtil.pprintNewline(stream);
      OntosaurusUtil.pprintObject(self.rest.rest.value, stream);
      self = self.rest.rest.rest;
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 7);
    }
    else {
      stream.print(" ");
      OntosaurusUtil.pprintObject(self.rest.rest.value, stream);
      self = self.rest.rest.rest;
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 3);
    }
    while (!(self == Stella.NIL)) {
      OntosaurusUtil.pprintNewline(stream);
      OntosaurusUtil.pprintObject(self.value, stream);
      stream.print(" ");
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() + 8);
      OntosaurusUtil.pprintObject(self.rest.value, stream);
      Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 8);
      self = self.rest.rest;
    }
    Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, ((Integer)(OntosaurusUtil.$PPRINT_INDENT$.get())).intValue() - 3);
    stream.print(")");
    if (((java.lang.reflect.Method)(OntosaurusUtil.$PPRINT_AFTER_DEFINITION_FUNCTION$.get())) != null) {
      edu.isi.stella.javalib.Native.funcall(((java.lang.reflect.Method)(OntosaurusUtil.$PPRINT_AFTER_DEFINITION_FUNCTION$.get())), null, new java.lang.Object [] {self, stream});
    }
  }

  public static void pprintOntosaurusObject(Stella_Object self, OutputStream stream) {
    { Object old$LogicDialect$000 = Logic.$LOGIC_DIALECT$.get();
      Object old$PprintAtomicObjectRenderer$000 = OntosaurusUtil.$PPRINT_ATOMIC_OBJECT_RENDERER$.get();

      try {
        Native.setSpecial(Logic.$LOGIC_DIALECT$, OntosaurusUtil.KWD_KIF);
        Native.setSpecial(OntosaurusUtil.$PPRINT_ATOMIC_OBJECT_RENDERER$, Native.find_java_method("edu.isi.ontosaurus.OntosaurusUtil", "pprintAtomicObjectForHtml", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.javalib.NativeOutputStream")}));
        if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(self), OntosaurusUtil.SGT_LOGIC_PROPOSITION)) {
          { Proposition self000 = ((Proposition)(self));

            { Keyword testValue000 = self000.kind;

              if ((testValue000 == OntosaurusUtil.KWD_ISA) ||
                  ((testValue000 == OntosaurusUtil.KWD_FUNCTION) ||
                   ((testValue000 == OntosaurusUtil.KWD_PREDICATE) ||
                    ((testValue000 == OntosaurusUtil.KWD_NOT) ||
                     ((testValue000 == OntosaurusUtil.KWD_EQUIVALENT) ||
                      (testValue000 == OntosaurusUtil.KWD_FAIL)))))) {
              }
              else {
                {
                  stream.nativeStream.print("<PRE>");
                  OntosaurusUtil.pprintObject(self000, stream.nativeStream);
                  stream.nativeStream.println("</PRE>");
                }
                return;
              }
            }
          }
        }
        else {
        }
        OntosaurusUtil.pprintObject(self, stream.nativeStream);

      } finally {
        OntosaurusUtil.$PPRINT_ATOMIC_OBJECT_RENDERER$.set(old$PprintAtomicObjectRenderer$000);
        Logic.$LOGIC_DIALECT$.set(old$LogicDialect$000);
      }
    }
  }

  public static void pprintAtomicObjectForHtmlDefinition(Stella_Object self, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (!(self == null)) {
      if (Surrogate.subtypeOfSymbolP(Stella_Object.safePrimaryType(self))) {
        { Symbol self000 = ((Symbol)(self));

          { Stella_Object renamed_Object = Logic.getInstance(self000);

            if (renamed_Object != null) {
              OntosaurusUtil.pprintAtomicObjectForHtml(renamed_Object, stream);
            }
            else {
              OntosaurusUtil.pprintAtomicObjectForHtml(self000, stream);
            }
          }
        }
      }
      else {
        OntosaurusUtil.pprintAtomicObjectForHtml(self, stream);
      }
    }
  }

  public static void pprintAtomicObjectForHtml(Stella_Object self, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (!(self == null)) {
      { Surrogate testValue000 = Stella_Object.safePrimaryType(self);

        if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_STELLA_LITERAL_WRAPPER)) {
          { LiteralWrapper self000 = ((LiteralWrapper)(self));

            OntosaurusUtil.pprintLiteralWrapperForHtml(self000, stream);
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_PATTERN_VARIABLE)) {
          { PatternVariable self000 = ((PatternVariable)(self));

            OntosaurusUtil.pprintAtomicObject(self000, stream);
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_SKOLEM)) {
          { Skolem self000 = ((Skolem)(self));

            if (Logic.nativeValueOf(self000) != null) {
              OntosaurusUtil.pprintAtomicObjectForHtml(Logic.nativeValueOf(self000), stream);
            }
            else if (Logic.innermostOf(self000) != null) {
              if (Logic.innermostOf(self000) == self000) {
                if (self000.definingProposition != null) {
                  OntosaurusUtil.pprintFunctionTerm(self000.definingProposition, stream);
                }
                else {
                  {
                    stream.print("<FONT COLOR='#666666'>");
                    stream.print(Native.stringDowncase(Skolem.getSkolemPrintName(self000)));
                    stream.print("</FONT>");
                  }
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
                  OntosaurusUtil.pprintObject(Logic.innermostOf(self000), stream);
                }
              }
            }
            else {
              stream.print(Skolem.generateSkolem(self000));
            }
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
          { LogicObject self000 = ((LogicObject)(self));

            if (self000.surrogateValueInverse != null) {
              OntosaurusUtil.printOntosaurusUrl(self000, stream);
            }
            else {
              stream.print("Unamed_Object");
            }
          }
        }
        else if (Surrogate.subtypeOfSurrogateP(testValue000)) {
          { Surrogate self000 = ((Surrogate)(self));

            if (self000.surrogateValue != null) {
              OntosaurusUtil.pprintObject(self000.surrogateValue, stream);
            }
            else {
              stream.print(OntosaurusUtil.operatorToString(self000));
            }
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_STELLA_GENERALIZED_SYMBOL)) {
          { GeneralizedSymbol self000 = ((GeneralizedSymbol)(self));

            Stella.writeHtmlQuotingSpecialCharacters(stream, self000.symbolName);
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_STELLA_MODULE)) {
          { Module self000 = ((Module)(self));

            OntosaurusUtil.htmlWriteHref(stream, ((String)(OntosaurusUtil.$ONTOSAURUS_URL_ACTION$.get())), "context", self000);
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_LOGIC_THING)) {
          { LogicThing self000 = ((LogicThing)(self));

            try {
              OntosaurusUtil.pprintObject(Logic.generateTerm(self000), stream);
            } catch (TermGenerationException e000) {
              stream.print(self000);
            }
          }
        }
        else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_STELLA_THING)) {
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

  public static void pprintLiteralWrapperForHtml(LiteralWrapper self, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Surrogate testValue000 = Stella_Object.safePrimaryType(self);

      if (Surrogate.subtypeOfBooleanP(testValue000)) {
        { BooleanWrapper self000 = ((BooleanWrapper)(self));

          stream.print(self000.wrapperValue);
        }
      }
      else if (Surrogate.subtypeOfIntegerP(testValue000)) {
        { IntegerWrapper self000 = ((IntegerWrapper)(self));

          stream.print(self000.wrapperValue);
        }
      }
      else if (Surrogate.subtypeOfFloatP(testValue000)) {
        { FloatWrapper self000 = ((FloatWrapper)(self));

          stream.print(self000.wrapperValue);
        }
      }
      else if (Surrogate.subtypeOfCharacterP(testValue000)) {
        { CharacterWrapper self000 = ((CharacterWrapper)(self));

          Stella.writeHtmlCharacterQuotingSpecialCharacters(stream, self000.wrapperValue);
        }
      }
      else if (Surrogate.subtypeOfStringP(testValue000)) {
        { StringWrapper self000 = ((StringWrapper)(self));

          if (((Boolean)(Stella.$PRINTREADABLYp$.get())).booleanValue()) {
            stream.print("\"");
          }
          Stella.writeHtmlQuotingSpecialCharacters(stream, self000.wrapperValue);
          if (((Boolean)(Stella.$PRINTREADABLYp$.get())).booleanValue()) {
            stream.print("\"");
          }
        }
      }
      else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_STELLA_MUTABLE_STRING_WRAPPER)) {
        { MutableStringWrapper self000 = ((MutableStringWrapper)(self));

          if (((Boolean)(Stella.$PRINTREADABLYp$.get())).booleanValue()) {
            stream.print("\"");
          }
          Stella.writeHtmlQuotingSpecialCharacters(stream, (self000.wrapperValue).toString());
          if (((Boolean)(Stella.$PRINTREADABLYp$.get())).booleanValue()) {
            stream.print("\"");
          }
        }
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("`" + testValue000 + "' is not a valid case option");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
    }
  }

  public static String logicObjectDisplayType(LogicObject obj) {
    if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(obj), OntosaurusUtil.SGT_LOGIC_DESCRIPTION)) {
      { Description obj000 = ((Description)(obj));

        return ("relation");
      }
    }
    else {
      return ("object");
    }
  }

  /** Prints a URL following PowerLoom Ontosaurus conventions.
   * @param theObject
   * @param nativestream
   */
  public static void printOntosaurusUrl(LogicObject theObject, edu.isi.stella.javalib.NativeOutputStream nativestream) {
    OntosaurusUtil.htmlWriteHref(nativestream, ((String)(OntosaurusUtil.$ONTOSAURUS_URL_ACTION$.get())), OntosaurusUtil.logicObjectDisplayType(theObject), theObject);
  }

  public static void writeControlPanelScript(edu.isi.stella.javalib.NativeOutputStream stream) {
    {
      stream.println("<SCRIPT LANGUAGE='JavaScript'>");
      stream.println("<!-- Hide from non-javascript browsers");
      stream.println();
      stream.println("// Copyright 2000 University of Southern California");
      stream.println("// All rights reserved.");
      stream.println();
      stream.println("function putRight(newLoc) {parent.frames[2].document.location.href = newLoc;};");
      stream.println();
      stream.println("function putLeft(newLoc) {parent.frames[1].document.location.href = newLoc;};");
      stream.println("// var URLpath = self.document.location.href.substring(0, self.document.location.href.lastIndexOf('/') + 1);");
      stream.println();
      stream.println("function myescape (str) {");
      stream.println("  // Needed because the built-in escape doesn't escape the '+' character.");
      stream.println("  var i = str.indexOf('+');");
      stream.println("  var newstr = '';");
      stream.println("  if (i == -1) {return str;}");
      stream.println("  else {");
      stream.println("    newstr += str.substring(0,str.indexOf('+')) + '%2B';");
      stream.println("    if (i+1 < str.length)");
      stream.println("      {newstr +=  myescape(str.substring(i+1,str.length))};");
      stream.println("    return newstr;");
      stream.println("  };");
      stream.println("}");
      stream.println();
      stream.println("function lispify (str, caseflag) {");
      stream.println("  if (caseflag) {var sym = myescape(escape(str.toUpperCase()));} ");
      stream.println("  else {var sym = myescape(escape(str));};");
      stream.println("  return sym;");
      stream.println("};");
      stream.println();
      stream.println("function loadTopContextURL() {");
      stream.println("  var form = window.document.navform;");
      stream.println("  var sel = form.elements[0].options[form.elements[0].selectedIndex].text;");
      stream.println("  var URLpath = window.document.location.href.substring(0, window.document.location.href.lastIndexOf('/') + 1");
      stream.println("					       );");
      stream.println("  return URLpath + \"do-action?show+context+\" + sel + \"+NIL\";");
      stream.println("}");
      stream.println();
      stream.println("function loadURL(windowName, url, form) {");
      stream.println("  var sel = form.elements[0].options[form.elements[0].selectedIndex].text;");
      stream.println("  var typ = form.objecttype.options[form.objecttype.selectedIndex].value;");
      stream.println("  var URLpath = self.document.location.href.substring(0, self.document.location.href.lastIndexOf('/') + 1);");
      stream.println();
      stream.println();
      stream.println("  if (url == \"show\") {");
      stream.println("    if (form.matchtype.options[form.matchtype.selectedIndex].value==\"caseInsensitive\") {url = \"findinsensitive\"}");
      stream.println("    else if (form.matchtype.options[form.matchtype.selectedIndex].value==\"substring\") {url = \"findsubstring\"};");
      stream.println("  } else if (url == \"edit\") {");
      stream.println("    if (form.matchtype.options[form.matchtype.selectedIndex].value==\"caseInsensitive\") {url = \"editinsensitive\"}");
      stream.println("    else if (form.matchtype.options[form.matchtype.selectedIndex].value==\"substring\") {url = \"editsubstring\"};");
      stream.println("  };");
      stream.println();
      stream.println("  if (form.find.value == \"?\") {");
      stream.println("     // window.open (URLpath + \"help/regexp.html\", \"toc\")");
      stream.println("        parent.frames[\"toc\"].document.location.href = URLpath + \"help/regexp.html\"");
      stream.println("  }");
      stream.println("  else if (url == \"new\") {");
      stream.println("    if (typ == \"instance\") {");
      stream.println("     parent.frames[windowName].document.location.href = URLpath + \"do-action?new+instance+\" + sel + \"+NIL\"}");
      stream.println();
      stream.println("       else {");
      stream.println("     parent.frames[windowName].document.location.href = URLpath + \"do-action?new+\" + typ + \"+\" + sel + \"+NIL\"");
      stream.println("}");
      stream.println("  }");
      stream.println("  else if (form.find.value.length > 0) {");
      stream.println("        url = \"do-action?\" + url +\"+\" + typ + \"+\";");
      stream.println("     parent.frames[windowName].document.location.href = URLpath + url + sel + \"+\" + lispify(form.find.value, false)");
      stream.println("  } else {");
      stream.println("   alert(\"No input provided. You need to enter name to look up.\");");
      stream.println("  };");
      stream.println("};");
      stream.println();
      stream.println("function loadContextURL(windowName, action, form) {");
      stream.println("  var sel = form.elements[0].options[form.elements[0].selectedIndex].text;");
      stream.println("  var URLpath = self.document.location.href.substring(0, self.document.location.href.lastIndexOf('/') + 1);");
      stream.println("  parent.frames[windowName].document.location.href = URLpath + \"do-action?\" + action + \"+context+\" + sel + \"+NIL\";");
      stream.println("};");
      stream.println();
      stream.println("function loadNewContextURL(windowName, lispPackage, form) {");
      stream.println("  var sel = form.elements[0].options[form.elements[0].selectedIndex].text;");
      stream.println("  var URLpath = self.document.location.href.substring(0, self.document.location.href.lastIndexOf('/') + 1);");
      stream.println("  parent.frames[windowName].document.location.href = URLpath + \"do-action?new+context+BUILT-IN-THEORY+\" + lispPackage;");
      stream.println("};");
      stream.println();
      stream.println("function loadVanillaURL(windowName, action, form) {");
      stream.println("  var URLpath = self.document.location.href.substring(0, self.document.location.href.lastIndexOf('/') + 1);");
      stream.println("  window.open(URLpath + action, windowName).focus();");
      stream.println("};");
      stream.println();
      stream.println("function loadFrameVanillaURL(windowName, action, form) {");
      stream.println("  var URLpath = self.document.location.href.substring(0, self.document.location.href.lastIndexOf('/') + 1);");
      stream.println("  // window.open(URLpath + action, windowName).focus();");
      stream.println("  parent.frames[windowName].document.location.href = URLpath + action;");
      stream.println("};");
      stream.println();
      stream.println("function formTest(form) {");
      stream.println("  loadURL('content', 'show', form);");
      stream.println("  return false;");
      stream.println("};");
      stream.println();
      stream.println("function setConInfo(con, theory) {");
      stream.println("  var Form = self.document.navform;");
      stream.println("  var Selection = Form.context;");
      stream.println("  var tempResult = \"\";");
      stream.println("  for (var i = 0; i < Selection.options.length; i++) {");
      stream.println("    if (Selection.options[i].text == theory) {");
      stream.println("      Selection.options[i].selected = true;");
      stream.println("    } else {");
      stream.println("      Selection.options[i].selected = false;");
      stream.println("    };");
      stream.println("  };");
      stream.println("  Form.find.value = con;");
      stream.println("};");
      stream.println();
      stream.println("// End hiding from old browsers -->");
      stream.println("</SCRIPT>");
    }
;
  }

  public static String lookupTerm(Keyword term, boolean capitalizedP, boolean pluralP) {
    if (pluralP &&
        capitalizedP) {
      if (term == OntosaurusUtil.KWD_CONCEPT) {
        return ("Concepts");
      }
      else if (term == OntosaurusUtil.KWD_RELATION) {
        return ("Relations");
      }
      else if (term == OntosaurusUtil.KWD_CONTEXT) {
        return ("Modules");
      }
      else if (term == OntosaurusUtil.KWD_INSTANCE) {
        return ("Instances");
      }
      else if (term == OntosaurusUtil.KWD_QUERY) {
        return ("Queries");
      }
      else if (term == OntosaurusUtil.KWD_OBJECT) {
        return ("Objects");
      }
      else {
        return (Native.stringCapitalize(term.symbolName) + "s");
      }
    }
    else if (capitalizedP) {
      if (term == OntosaurusUtil.KWD_CONCEPT) {
        return ("Concept");
      }
      else if (term == OntosaurusUtil.KWD_RELATION) {
        return ("Relation");
      }
      else if (term == OntosaurusUtil.KWD_CONTEXT) {
        return ("Module");
      }
      else if (term == OntosaurusUtil.KWD_INSTANCE) {
        return ("Instance");
      }
      else if (term == OntosaurusUtil.KWD_QUERY) {
        return ("Query");
      }
      else if (term == OntosaurusUtil.KWD_OBJECT) {
        return ("Object");
      }
      else {
        return (Native.stringCapitalize(term.symbolName));
      }
    }
    else if (pluralP) {
      if (term == OntosaurusUtil.KWD_CONCEPT) {
        return ("concepts");
      }
      else if (term == OntosaurusUtil.KWD_RELATION) {
        return ("relations");
      }
      else if (term == OntosaurusUtil.KWD_CONTEXT) {
        return ("modules");
      }
      else if (term == OntosaurusUtil.KWD_INSTANCE) {
        return ("instances");
      }
      else if (term == OntosaurusUtil.KWD_QUERY) {
        return ("queries");
      }
      else if (term == OntosaurusUtil.KWD_OBJECT) {
        return ("objects");
      }
      else {
        return (Native.stringDowncase(term.symbolName) + "s");
      }
    }
    else {
      if (term == OntosaurusUtil.KWD_CONCEPT) {
        return ("concept");
      }
      else if (term == OntosaurusUtil.KWD_RELATION) {
        return ("relation");
      }
      else if (term == OntosaurusUtil.KWD_CONTEXT) {
        return ("module");
      }
      else if (term == OntosaurusUtil.KWD_INSTANCE) {
        return ("instance");
      }
      else if (term == OntosaurusUtil.KWD_QUERY) {
        return ("query");
      }
      else if (term == OntosaurusUtil.KWD_OBJECT) {
        return ("object");
      }
      else {
        return (Native.stringDowncase(term.symbolName));
      }
    }
  }

  public static String safeObjectNameString(LogicObject instance) {
    { Surrogate surrogate = instance.surrogateValueInverse;

      if (surrogate != null) {
        return (surrogate.symbolName);
      }
      else {
        return (null);
      }
    }
  }

  public static void htmlDescribeLocation(LogicObject self, edu.isi.stella.javalib.NativeOutputStream stream) {
    {
      stream.print("<PRE>");
      stream.print(OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_CONTEXT, true, false) + ": ");
      if ((self != null) &&
          Stella_Object.isaP(self.homeModule(), OntosaurusUtil.SGT_STELLA_MODULE)) {
        OntosaurusUtil.htmlWriteHref(stream, "show", "context", self.homeModule());
      }
      else {
        stream.print(Stella.cc(Stella.NIL));
      }
      stream.println();
      if ((self != null) &&
          ((Logic.objectName(self) != null) &&
           (!(Logic.objectName(self).homeModule() == self.homeModule())))) {
        stream.print("Namespace: ");
        OntosaurusUtil.htmlWriteHref(stream, "show", "context", Logic.objectName(self).homeModule());
        stream.println();
      }
      stream.println("</PRE>");
    }
    return;
  }

  public static void htmlWriteContextViewOption(edu.isi.stella.javalib.NativeOutputStream stream, String objectname, Module ctx) {
    stream.print("<option VALUE=\"do-action?show+object+");
    Stella.writeHtmlEscapingUrlSpecialCharacters(stream, ctx.name());
    stream.print("+");
    Stella.writeHtmlEscapingUrlSpecialCharacters(stream, objectname);
    stream.print("\"");
    if (ctx == ((Module)(Stella.$MODULE$.get()))) {
      stream.print(" SELECTED");
    }
    stream.print(">");
    Stella.writeHtmlQuotingSpecialCharacters(stream, ctx.name());
    stream.println("</OPTION>");
    return;
  }

  public static void htmlDescribeContextView(LogicObject self, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Module homec = self.homeModule();
      String objectname = OntosaurusUtil.getHtmlObjectHandle(self);
      AllPurposeIterator contextlist = Context.allSubcontexts(homec, OntosaurusUtil.KWD_PREORDER);

      if (!(OntosaurusUtil.childModules(homec) == Stella.NIL)) {
        OntosaurusUtil.htmlWriteJavascript(stream, "\nfunction jumpLink (opt) {\n  var URLpath = self.location.href.substring(0 , self.location.href.lastIndexOf('/') + 1);\n  self.location.href=URLpath + opt.options[opt.selectedIndex].value;\n};\n");
        {
          stream.print("<FORM Name='CFORM'>");
          stream.print("Seen from: ");
          {
            stream.print("<SELECT NAME='context' onchange='jumpLink(this);'>");
            stream.println();
            OntosaurusUtil.htmlWriteContextViewOption(stream, objectname, homec);
            { Context c = null;
              AllPurposeIterator iter000 = contextlist;

              while (iter000.nextP()) {
                c = ((Context)(iter000.value));
                if (Stella_Object.isaP(c, OntosaurusUtil.SGT_STELLA_MODULE)) {
                  OntosaurusUtil.htmlWriteContextViewOption(stream, objectname, ((Module)(c)));
                }
              }
            }
            stream.print("</SELECT>");
          }
          stream.println("</FORM>");
        }
      }
    }
    return;
  }

  public static void htmlDisplayImages(StandardObject self, edu.isi.stella.javalib.NativeOutputStream stream) {
    { boolean firstP = true;
      edu.isi.powerloom.PlIterator images = edu.isi.powerloom.PLI.getInferredBinaryPropositionValues(OntosaurusUtil.$IMAGE_URL_RELATION$, self, null, null);

      if (!(images.emptyP())) {
        stream.println();
        {
          stream.print("<P>");
          { Stella_Object i = null;
            edu.isi.powerloom.PlIterator iter000 = images;

            while (iter000.nextP()) {
              i = iter000.value;
              if (firstP) {
                OntosaurusUtil.htmlLineBreak(stream);
              }
              else {
                stream.print(" ");
              }
              OntosaurusUtil.htmlEmitImage(stream, ((StringWrapper)(i)).wrapperValue, "", Stella.NULL_INTEGER, Stella.NULL_INTEGER, "BOTTOM", 0);
            }
          }
          stream.print("</P>");
        }
      }
    }
    return;
  }

  public static void htmlDisplayDocumentation(StandardObject self, edu.isi.stella.javalib.NativeOutputStream stream) {
    { edu.isi.powerloom.PlIterator docstrings = edu.isi.powerloom.PLI.getInferredBinaryPropositionValues(OntosaurusUtil.$DOCUMENTATION_RELATION$, self, null, null);

      if (docstrings != null) {
        {
          stream.print("<FONT COLOR='#007700'>");
          {
            stream.print("<DL>");
            { Stella_Object doc = null;
              edu.isi.powerloom.PlIterator iter000 = docstrings;

              while (iter000.nextP()) {
                doc = iter000.value;
                if ((doc != null) &&
                    (((StringWrapper)(doc)).wrapperValue != null)) {
                  {
                    stream.print("<DT>");
                    OntosaurusUtil.htmlDisplayStringInParagraphs(((StringWrapper)(doc)).wrapperValue, stream);
                    stream.print("</DT>");
                  }
                }
              }
            }
            stream.print("</DL>");
          }
          stream.println("</FONT>");
        }
      }
      stream.println("<HR SIZE=2>");
    }
  }

  public static void htmlDisplaySynonyms(Stella_Object self, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Cons synonyms = Logic.getSynonyms(self);

      if (!(synonyms == Stella.NIL)) {
        {
          stream.print("<P>");
          {
            stream.print("<B>");
            stream.print("Synonyms: ");
            stream.print("</B>");
          }
          Stella.writeHtmlEscapingUrlSpecialCharacters(stream, Logic.objectStringName(((LogicObject)(synonyms.value))));
          { LogicObject syn = null;
            Cons iter000 = synonyms.rest;

            for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
              syn = ((LogicObject)(iter000.value));
              stream.print(", ");
              Stella.writeHtmlEscapingUrlSpecialCharacters(stream, Logic.objectStringName(syn));
            }
          }
          stream.println("</P>");
        }
      }
    }
  }

  public static void htmlDescribeEquivalents(String title, String head, NamedDescription relation, edu.isi.stella.javalib.NativeOutputStream stream, boolean ruleP) {
    { Cons equivalents = Cons.copyConsList(NamedDescription.allEquivalentRelations(relation, true));

      if (!(equivalents.rest == Stella.NIL)) {
        equivalents = equivalents.remove(relation).sort(Native.find_java_method("edu.isi.powerloom.logic.LogicObject", "objectNameLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.powerloom.logic.LogicObject")}));
        OntosaurusUtil.htmlWriteHeaderWithTable(stream, title, head);
        OntosaurusUtil.htmlWriteHref(stream, "show", "concept", ((NamedDescription)(equivalents.value)));
        { NamedDescription c = null;
          Cons iter000 = equivalents.rest;

          for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
            c = ((NamedDescription)(iter000.value));
            stream.print(", ");
            OntosaurusUtil.htmlWriteHref(stream, "show", "concept", c);
          }
        }
        if (ruleP) {
          stream.println("<HR SIZE=2>");
        }
      }
      return;
    }
  }

  public static void htmlDescribeOneSubLevel(NamedDescription renamed_Object, int depth, int cutoff, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Cons directsubs = edu.isi.powerloom.PLI.getDirectSubrelations(renamed_Object, null, null).consify();

      if (directsubs == Stella.NIL) {
        return;
      }
      directsubs = directsubs.sort(Native.find_java_method("edu.isi.powerloom.logic.LogicObject", "objectNameLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.powerloom.logic.LogicObject")}));
      {
        stream.print("<DL STYLE=' margin-top: 0; margin-bottom:0'>");
        { Stella_Object sub = null;
          Cons iter000 = directsubs;

          for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
            sub = iter000.value;
            {
              stream.print("<DT STYLE='margin-top: 0'>");
              OntosaurusUtil.htmlWriteHref(stream, "show", "concept", ((StandardObject)(sub)));
              if ((depth >= cutoff) &&
                  (!edu.isi.powerloom.PLI.getDirectSubrelations(((LogicObject)(sub)), null, null).emptyP())) {
                stream.print("    +...");
              }
              stream.println("</DT>");
            }
            if (!(depth >= cutoff)) {
              {
                stream.print("<DD>");
                OntosaurusUtil.htmlDescribeOneSubLevel(((NamedDescription)(sub)), depth + 1, cutoff, stream);
                stream.println("</DD>");
              }
            }
          }
        }
        stream.println("</DL>");
      }
      return;
    }
  }

  public static void htmlDescribeSubs(String title, String head, NamedDescription relation, edu.isi.stella.javalib.NativeOutputStream stream, boolean ruleP) {
    { int heuristicdepth = 4;
      int sublength = edu.isi.powerloom.PLI.getDirectSubrelations(relation, null, null).length();

      if (sublength > 30) {
        heuristicdepth = heuristicdepth - 1;
      }
      OntosaurusUtil.htmlWriteHeaderWithTable(stream, title, head);
      if (sublength == 0) {
        {
          stream.print("<I>");
          stream.print("None");
          stream.println("</I>");
        }
      }
      else {
        OntosaurusUtil.htmlDescribeOneSubLevel(relation, 0, heuristicdepth, stream);
      }
      if (ruleP) {
        stream.println("<HR SIZE=2>");
      }
      return;
    }
  }

  public static void htmlDescribeOneSuperLevel(Cons directsupers, HashTable alreadyoutput, edu.isi.stella.javalib.NativeOutputStream stream) {
    { boolean alreadyoutputP = false;

      if (directsupers == Stella.NIL) {
        return;
      }
      directsupers = Cons.copyConsList(directsupers).sort(Native.find_java_method("edu.isi.powerloom.logic.LogicObject", "objectNameLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.powerloom.logic.LogicObject")}));
      {
        stream.print("<DL STYLE=' margin-top: 0; margin-bottom:0'>");
        { NamedDescription renamed_Super = null;
          Cons iter000 = directsupers;

          for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
            renamed_Super = ((NamedDescription)(iter000.value));
            alreadyoutputP = alreadyoutput.lookup(renamed_Super) != null;
            {
              stream.print("<DT STYLE='margin-top: 0'>");
              OntosaurusUtil.htmlWriteHref(stream, "show", "concept", renamed_Super);
              if (alreadyoutputP) {
                stream.print("...");
              }
              stream.println("</DT>");
            }
            if (!(alreadyoutputP)) {
              alreadyoutput.insertAt(renamed_Super, Stella.TRUE_WRAPPER);
              {
                stream.print("<DD>");
                OntosaurusUtil.htmlDescribeOneSuperLevel(edu.isi.powerloom.PLI.getDirectSuperrelations(renamed_Super, null, null).consify(), alreadyoutput, stream);
                stream.println("</DD>");
              }
            }
          }
        }
        stream.println("</DL>");
      }
      return;
    }
  }

  public static void htmlDescribeSupers(String title, String head, NamedDescription relation, edu.isi.stella.javalib.NativeOutputStream stream, boolean ruleP) {
    { HashTable alreadyoutput = HashTable.newHashTable();
      Cons directsupers = edu.isi.powerloom.PLI.getDirectSuperrelations(relation, null, null).consify();

      OntosaurusUtil.htmlWriteHeaderWithTable(stream, title, head);
      if (directsupers == Stella.NIL) {
        {
          stream.print("<I>");
          stream.print("None");
          stream.println("</I>");
        }
      }
      else {
        OntosaurusUtil.htmlDescribeOneSuperLevel(directsupers, alreadyoutput, stream);
      }
      if (ruleP) {
        stream.println("<HR SIZE=2>");
      }
      return;
    }
  }

  public static void htmlDescribeTypes(String title, String head, LogicObject relation, edu.isi.stella.javalib.NativeOutputStream stream, boolean ruleP) {
    { HashTable alreadyoutput = HashTable.newHashTable();
      Cons types = edu.isi.powerloom.PLI.getDirectTypes(relation, null, null).consify();

      OntosaurusUtil.htmlWriteHeaderWithTable(stream, title, head);
      if (types == Stella.NIL) {
        {
          stream.print("<I>");
          stream.print("None");
          stream.println("</I>");
        }
      }
      else {
        OntosaurusUtil.htmlDescribeOneSuperLevel(types, alreadyoutput, stream);
      }
      if (ruleP) {
        stream.println("<HR SIZE=2>");
      }
      return;
    }
  }

  public static void htmlDescribeOneParentWithSiblings(NamedDescription parent, NamedDescription child, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Cons directsubs = edu.isi.powerloom.PLI.getDirectSubrelations(parent, null, null).consify();

      directsubs = directsubs.sort(Native.find_java_method("edu.isi.powerloom.logic.LogicObject", "objectNameLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.powerloom.logic.LogicObject")}));
      {
        stream.print("<DT>");
        stream.print("Common parent: ");
        OntosaurusUtil.htmlWriteHref(stream, "show", "concept", parent);
        stream.println("</DT>");
      }
      { Stella_Object sub = null;
        Cons iter000 = directsubs;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          sub = iter000.value;
          if (!(sub == child)) {
            {
              stream.print("<DD>");
              OntosaurusUtil.htmlWriteHref(stream, "show", "concept", ((StandardObject)(sub)));
              stream.println("</DD>");
            }
          }
        }
      }
      return;
    }
  }

  public static boolean hasChildOtherThanP(NamedDescription parent, NamedDescription child) {
    { LogicObject c = null;
      edu.isi.powerloom.PlIterator iter000 = edu.isi.powerloom.PLI.getDirectSubrelations(parent, null, null);

      while (iter000.nextP()) {
        c = ((LogicObject)(iter000.value));
        if (!(c == child)) {
          return (true);
        }
      }
    }
    return (false);
  }

  public static void htmlDescribeSiblings(String title, String head, NamedDescription relation, edu.isi.stella.javalib.NativeOutputStream stream, boolean ruleP) {
    { Cons parentsofsibs = Stella.NIL;

      { LogicObject p = null;
        edu.isi.powerloom.PlIterator iter000 = edu.isi.powerloom.PLI.getDirectSuperrelations(relation, null, null);
        Cons collect000 = null;

        while (iter000.nextP()) {
          p = ((LogicObject)(iter000.value));
          if (OntosaurusUtil.hasChildOtherThanP(((NamedDescription)(p)), relation)) {
            if (collect000 == null) {
              {
                collect000 = Cons.cons(p, Stella.NIL);
                if (parentsofsibs == Stella.NIL) {
                  parentsofsibs = collect000;
                }
                else {
                  Cons.addConsToEndOfConsList(parentsofsibs, collect000);
                }
              }
            }
            else {
              {
                collect000.rest = Cons.cons(p, Stella.NIL);
                collect000 = collect000.rest;
              }
            }
          }
        }
      }
      parentsofsibs = parentsofsibs.sort(Native.find_java_method("edu.isi.powerloom.logic.LogicObject", "objectNameLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.powerloom.logic.LogicObject")}));
      OntosaurusUtil.htmlWriteHeaderWithTable(stream, title, head);
      if (parentsofsibs == Stella.NIL) {
        {
          stream.print("<I>");
          stream.print("None");
          stream.println("</I>");
        }
      }
      else {
        {
          stream.print("<DL>");
          { NamedDescription p = null;
            Cons iter001 = parentsofsibs;

            for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
              p = ((NamedDescription)(iter001.value));
              OntosaurusUtil.htmlDescribeOneParentWithSiblings(p, relation, stream);
            }
          }
          stream.println("</DL>");
        }
      }
      if (ruleP) {
        stream.println("<HR SIZE=2>");
      }
      return;
    }
  }

  public static void htmlDescribeRules(String title, String head, LogicObject relation, edu.isi.stella.javalib.NativeOutputStream stream, boolean ruleP) {
    { Cons rules = edu.isi.powerloom.PLI.getRules(relation, null, null).consify();
      boolean ruleWrittenP = false;

      OntosaurusUtil.htmlWriteHeaderWithTable(stream, title, head);
      {
        stream.print("<PRE>");
        rules = rules.sort(Native.find_java_method("edu.isi.powerloom.logic.Proposition", "propositionLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Proposition"), Native.find_java_class("edu.isi.powerloom.logic.Proposition")}));
        { Proposition rule = null;
          Cons iter000 = rules;

          for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
            rule = ((Proposition)(iter000.value));
            if ((!rule.deletedP()) &&
                ((((Boolean)(Logic.$REVERSEPOLARITYp$.get())).booleanValue() ? Proposition.falseP(rule) : (Proposition.trueP(rule) ||
                Proposition.functionWithDefinedValueP(rule))))) {
              if (!(Proposition.simpleSubrelationPropositionP(rule))) {
                OntosaurusUtil.pprintObject(rule, stream);
                {
                  stream.println("");
                  stream.println();
                }
;
                ruleWrittenP = true;
              }
            }
          }
        }
        stream.println("</PRE>");
      }
      if (!(ruleWrittenP)) {
        {
          stream.print("<I>");
          stream.print("None");
          stream.println("</I>");
        }
      }
      if (ruleP) {
        stream.println("<HR SIZE=2>");
      }
      return;
    }
  }

  public static void htmlDescribeFacts(String title, String head, LogicObject relation, edu.isi.stella.javalib.NativeOutputStream stream, boolean filterRulesP, boolean ruleP) {
    { Cons facts = edu.isi.powerloom.PLI.getPropositionsOf(relation, null, null).consify();
      boolean factWrittenP = false;

      OntosaurusUtil.htmlWriteHeaderWithTable(stream, title, head);
      {
        stream.print("<PRE>");
        facts = facts.sort(Native.find_java_method("edu.isi.powerloom.logic.Proposition", "propositionLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Proposition"), Native.find_java_class("edu.isi.powerloom.logic.Proposition")}));
        { Proposition fact = null;
          Cons iter000 = facts;

          for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
            fact = ((Proposition)(iter000.value));
            if ((!fact.deletedP()) &&
                ((((Boolean)(Logic.$REVERSEPOLARITYp$.get())).booleanValue() ? Proposition.falseP(fact) : (Proposition.trueP(fact) ||
                Proposition.functionWithDefinedValueP(fact))))) {
              if (!(Logic.classP(fact.operator))) {
                if (!(fact.kind == OntosaurusUtil.KWD_EQUIVALENT)) {
                  if (!(filterRulesP &&
                      (fact.kind == OntosaurusUtil.KWD_IMPLIES))) {
                    factWrittenP = true;
                    OntosaurusUtil.pprintObject(fact, stream);
                    {
                      stream.println("");
                      stream.println();
                    }
;
                  }
                }
              }
            }
          }
        }
        stream.println("</PRE>");
      }
      if (!(factWrittenP)) {
        {
          stream.print("<I>");
          stream.print("None");
          stream.println("</I>");
        }
      }
      if (ruleP) {
        stream.println("<HR SIZE=2>");
      }
      return;
    }
  }

  public static void htmlDescribeInstances(String title, String head, NamedDescription relation, edu.isi.stella.javalib.NativeOutputStream stream, boolean ruleP) {
    { Cons instances = edu.isi.powerloom.PLI.getConceptInstances(relation, null, null).consify();
      Cons assertedinstances = Logic.ASSERTION_INFERENCE.levellizedAllClassInstances(relation.surrogateValueInverse);
      Cons directinstances = edu.isi.powerloom.PLI.getDirectConceptInstances(relation, null, null).consify();
      int nInstances = instances.length();

      OntosaurusUtil.htmlWriteHeaderWithTable(stream, title, head);
      if (instances == Stella.NIL) {
        {
          stream.print("<I>");
          stream.print("None");
          stream.println("</I>");
        }
      }
      else {
        {
          stream.print(nInstances + (((nInstances == 1) ? " instance; " : " instances; ")) + directinstances.length() + " direct (");
          OntosaurusUtil.htmlEmitImage(stream, "icons/small-circ-filled.gif", "x", 11, 11, "BOTTOM", 0);
          stream.println(")");
          {
            stream.print("<DL>");
            instances = instances.sort(Native.find_java_method("edu.isi.powerloom.logic.Logic", "logicFormLessP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.Stella_Object")}));
            { Stella_Object instance = null;
              Cons iter000 = instances;

              for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
                instance = iter000.value;
                {
                  stream.print("<DT>");
                  OntosaurusUtil.htmlEmitImage(stream, (directinstances.memberP(instance) ? "icons/small-circ-filled.gif" : "icons/small-circ-open.gif"), (directinstances.memberP(instance) ? "x" : "o"), 11, 11, "BOTTOM", 0);
                  stream.print("&nbsp;");
                  if (assertedinstances.memberP(instance)) {
                    OntosaurusUtil.pprintObject(instance, stream);
                  }
                  else {
                    {
                      stream.print("<I>");
                      OntosaurusUtil.pprintObject(instance, stream);
                      stream.print("</I>");
                    }
                  }
                  stream.println("</DT>");
                }
              }
            }
            stream.println("</DL>");
          }
        }
      }
      if (ruleP) {
        stream.println("<HR SIZE=2>");
      }
      return;
    }
  }

  public static void htmlDescribeTuples(String title, String head, NamedDescription relation, edu.isi.stella.javalib.NativeOutputStream stream, boolean ruleP) {
    { Cons tuples = edu.isi.powerloom.PLI.getRelationExtension(relation, null, null).consify();

      OntosaurusUtil.htmlWriteHeaderWithTable(stream, title, head);
      if (tuples == Stella.NIL) {
        {
          stream.print("<I>");
          stream.print("None");
          stream.println("</I>");
        }
      }
      else {
        {
          stream.print("<PRE>");
          tuples = tuples.sort(Native.find_java_method("edu.isi.powerloom.logic.Proposition", "propositionLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.Proposition"), Native.find_java_class("edu.isi.powerloom.logic.Proposition")}));
          { Proposition tuple = null;
            Cons iter000 = tuples;

            for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
              tuple = ((Proposition)(iter000.value));
              OntosaurusUtil.pprintObject(tuple, stream);
              {
                stream.println("");
                stream.println();
              }
;
            }
          }
          stream.println("</PRE>");
        }
      }
      if (ruleP) {
        stream.println("<HR SIZE=2>");
      }
      return;
    }
  }

  public static void htmlDescribeNamedDescription(NamedDescription concept, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (!(concept != null)) {
      return;
    }
    { String namestring = Logic.objectNameString(concept);
      String descriptionterm = OntosaurusUtil.lookupTerm((Logic.classP(concept) ? OntosaurusUtil.KWD_CONCEPT : OntosaurusUtil.KWD_RELATION), false, true);

      synchronized (Logic.$POWERLOOM_LOCK$) {
        { Object old$Context$000 = Stella.$CONTEXT$.get();
          Object old$Module$000 = Stella.$MODULE$.get();

          try {
            Native.setSpecial(Stella.$CONTEXT$, Logic.getQueryContext());
            Native.setSpecial(Stella.$MODULE$, ((Context)(Stella.$CONTEXT$.get())).baseModule);
            Logic.elaborateInstance(concept);

          } finally {
            Stella.$MODULE$.set(old$Module$000);
            Stella.$CONTEXT$.set(old$Context$000);
          }
        }
      }
      OntosaurusUtil.htmlDescribeLocation(concept, stream);
      OntosaurusUtil.htmlDescribeContextView(concept, stream);
      OntosaurusUtil.htmlDisplaySynonyms(concept, stream);
      OntosaurusUtil.htmlDisplayImages(concept, stream);
      OntosaurusUtil.htmlDisplayDocumentation(concept, stream);
      OntosaurusUtil.htmlDescribeEquivalents(Native.stringConcatenate("Equivalent ", descriptionterm), namestring, concept, stream, true);
      if (OntosaurusUtil.vizServerAvailableP()) {
        OntosaurusUtil.htmlWriteHrefInDetail(stream, "Graph", "graph", "relation", ((Module)(Stella.$MODULE$.get())).name(), Logic.objectName(concept).visibleName(true), "Graph " + namestring, false);
        stream.println("<HR SIZE=2>");
      }
      OntosaurusUtil.htmlDescribeTypes("Types", namestring, concept, stream, true);
      OntosaurusUtil.htmlDescribeSubs(Native.stringConcatenate("Sub", descriptionterm), namestring, concept, stream, true);
      OntosaurusUtil.htmlDescribeSupers(Native.stringConcatenate("Super", descriptionterm), namestring, concept, stream, true);
      OntosaurusUtil.htmlDescribeSiblings("Siblings", namestring, concept, stream, true);
      OntosaurusUtil.htmlDescribeFacts("Facts", namestring, concept, stream, true, true);
      OntosaurusUtil.htmlDescribeRules("Rules", namestring, concept, stream, true);
      { Object old$Context$001 = Stella.$CONTEXT$.get();
        Object old$Module$001 = Stella.$MODULE$.get();

        try {
          Native.setSpecial(Stella.$CONTEXT$, Logic.getQueryContext());
          Native.setSpecial(Stella.$MODULE$, ((Context)(Stella.$CONTEXT$.get())).baseModule);
          if (edu.isi.powerloom.PLI.getArity(concept) == 1) {
            OntosaurusUtil.htmlDescribeInstances("Instances", namestring, concept, stream, true);
          }
          else {
            OntosaurusUtil.htmlDescribeTuples("Tuples", namestring, concept, stream, true);
          }

        } finally {
          Stella.$MODULE$.set(old$Module$001);
          Stella.$CONTEXT$.set(old$Context$001);
        }
      }
      return;
    }
  }

  public static void htmlDescribeInstance(LogicObject instance, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (!(instance != null)) {
      return;
    }
    { String namestring = OntosaurusUtil.getHtmlObjectHandle(instance);

      synchronized (Logic.$POWERLOOM_LOCK$) {
        { Object old$Context$000 = Stella.$CONTEXT$.get();
          Object old$Module$000 = Stella.$MODULE$.get();

          try {
            Native.setSpecial(Stella.$CONTEXT$, Logic.getQueryContext());
            Native.setSpecial(Stella.$MODULE$, ((Context)(Stella.$CONTEXT$.get())).baseModule);
            Logic.elaborateInstance(instance);

          } finally {
            Stella.$MODULE$.set(old$Module$000);
            Stella.$CONTEXT$.set(old$Context$000);
          }
        }
      }
      OntosaurusUtil.htmlDescribeLocation(instance, stream);
      OntosaurusUtil.htmlDescribeContextView(instance, stream);
      OntosaurusUtil.htmlDisplaySynonyms(instance, stream);
      OntosaurusUtil.htmlDisplayImages(instance, stream);
      OntosaurusUtil.htmlDisplayDocumentation(instance, stream);
      OntosaurusUtil.htmlDescribeTypes("Types", namestring, instance, stream, true);
      { Object old$Context$001 = Stella.$CONTEXT$.get();
        Object old$Module$001 = Stella.$MODULE$.get();

        try {
          Native.setSpecial(Stella.$CONTEXT$, Logic.getQueryContext());
          Native.setSpecial(Stella.$MODULE$, ((Context)(Stella.$CONTEXT$.get())).baseModule);
          OntosaurusUtil.htmlDescribeFacts("Facts", namestring, instance, stream, false, true);

        } finally {
          Stella.$MODULE$.set(old$Module$001);
          Stella.$CONTEXT$.set(old$Context$001);
        }
      }
      return;
    }
  }

  public static Cons childModules(Module module) {
    { Cons directsubmodules = Stella.NIL;

      { Context child = null;
        Cons iter000 = module.childContexts.theConsList;
        Cons collect000 = null;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          child = ((Context)(iter000.value));
          if (Stella_Object.isaP(child, OntosaurusUtil.SGT_STELLA_MODULE)) {
            if (collect000 == null) {
              {
                collect000 = Cons.cons(child, Stella.NIL);
                if (directsubmodules == Stella.NIL) {
                  directsubmodules = collect000;
                }
                else {
                  Cons.addConsToEndOfConsList(directsubmodules, collect000);
                }
              }
            }
            else {
              {
                collect000.rest = Cons.cons(child, Stella.NIL);
                collect000 = collect000.rest;
              }
            }
          }
        }
      }
      return (directsubmodules);
    }
  }

  public static void htmlDescribeOneModuleSubLevel(Module module, int depth, int cutoff, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Cons directsubmodules = OntosaurusUtil.childModules(module);

      if (directsubmodules == Stella.NIL) {
        return;
      }
      directsubmodules = directsubmodules.sort(Native.find_java_method("edu.isi.powerloom.logic.Logic", "moduleNameLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Context"), Native.find_java_class("edu.isi.stella.Context")}));
      {
        stream.print("<DL STYLE=' margin-top: 0; margin-bottom:0'>");
        { Module sub = null;
          Cons iter000 = directsubmodules;

          for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
            sub = ((Module)(iter000.value));
            {
              stream.print("<DT STYLE='margin-top: 0'>");
              OntosaurusUtil.htmlWriteHref(stream, "show", "context", sub);
              if ((depth >= cutoff) &&
                  (!(OntosaurusUtil.childModules(sub) == Stella.NIL))) {
                stream.print("    +...");
              }
              stream.println("</DT>");
            }
            if (!(depth >= cutoff)) {
              {
                stream.print("<DD>");
                OntosaurusUtil.htmlDescribeOneModuleSubLevel(sub, depth + 1, cutoff, stream);
                stream.println("</DD>");
              }
            }
          }
        }
        stream.println("</DL>");
      }
      return;
    }
  }

  public static void htmlDescribeModuleSubs(String title, String head, Module module, edu.isi.stella.javalib.NativeOutputStream stream, boolean ruleP) {
    { int heuristicdepth = 4;
      int sublength = OntosaurusUtil.childModules(module).length();

      if (sublength > 30) {
        heuristicdepth = heuristicdepth - 1;
      }
      OntosaurusUtil.htmlWriteHeaderWithTable(stream, title, head);
      if (sublength == 0) {
        {
          stream.print("<I>");
          stream.print("None");
          stream.println("</I>");
        }
      }
      else {
        OntosaurusUtil.htmlDescribeOneModuleSubLevel(module, 0, heuristicdepth, stream);
      }
      if (ruleP) {
        stream.println("<HR SIZE=2>");
      }
      return;
    }
  }

  public static void htmlDescribeOneModuleSuperLevel(Module module, HashTable alreadyoutput, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Cons parents = Cons.copyConsList(module.parentModules.theConsList).sort(Native.find_java_method("edu.isi.powerloom.logic.Logic", "moduleNameLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Context"), Native.find_java_class("edu.isi.stella.Context")}));
      boolean alreadyoutputP = false;

      if (parents == Stella.NIL) {
        return;
      }
      {
        stream.print("<DL STYLE=' margin-top: 0; margin-bottom:0'>");
        { Module parent = null;
          Cons iter000 = parents;

          for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
            parent = ((Module)(iter000.value));
            alreadyoutputP = alreadyoutput.lookup(parent) != null;
            {
              stream.print("<DT STYLE='margin-top: 0'>");
              OntosaurusUtil.htmlWriteHref(stream, "show", "context", parent);
              if (alreadyoutputP) {
                stream.print("...");
              }
              stream.println("</DT>");
            }
            if (!(alreadyoutputP)) {
              alreadyoutput.insertAt(parent, Stella.TRUE_WRAPPER);
              {
                stream.print("<DD>");
                OntosaurusUtil.htmlDescribeOneModuleSuperLevel(parent, alreadyoutput, stream);
                stream.println("</DD>");
              }
            }
          }
        }
        stream.println("</DL>");
      }
    }
    return;
  }

  public static void htmlDescribeModuleSupers(String title, String head, Module module, edu.isi.stella.javalib.NativeOutputStream stream, boolean ruleP) {
    { HashTable alreadyoutput = HashTable.newHashTable();

      OntosaurusUtil.htmlWriteHeaderWithTable(stream, title, head);
      if (module.parentModule() == null) {
        {
          stream.print("<I>");
          stream.print("None");
          stream.println("</I>");
        }
      }
      else {
        OntosaurusUtil.htmlDescribeOneModuleSuperLevel(module, alreadyoutput, stream);
      }
      if (ruleP) {
        stream.println("<HR SIZE=2>");
      }
      return;
    }
  }

  public static void htmlDisplayModuleStats(String title, String head, Module module, edu.isi.stella.javalib.NativeOutputStream stream, boolean ruleP) {
    { int nconcepts = 0;
      int nrelations = 0;
      int ninstances = 0;
      List allclasses = List.newList();
      List toplevelclasses = List.newList();
      boolean addP = false;

      { Stella_Object renamed_Object = null;
        Iterator iter000 = Logic.allNamedTerms(module, true);

        while (iter000.nextP()) {
          renamed_Object = iter000.value;
          if (Stella_Object.isaP(renamed_Object, OntosaurusUtil.SGT_LOGIC_NAMED_DESCRIPTION)) {
            if (Logic.classP(renamed_Object)) {
              nconcepts = nconcepts + 1;
              allclasses.push(((LogicObject)(renamed_Object)));
            }
            else if (Logic.relationP(renamed_Object)) {
              nrelations = nrelations + 1;
            }
            else {
              ninstances = ninstances + 1;
            }
          }
          else if (Stella_Object.stellaClassP(renamed_Object)) {
            nconcepts = nconcepts + 1;
          }
          else {
            ninstances = ninstances + 1;
          }
        }
      }
      { LogicObject renamed_Class = null;
        Cons iter001 = allclasses.theConsList;

        for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
          renamed_Class = ((LogicObject)(iter001.value));
          addP = true;
          { NamedDescription parent = null;
            Cons iter002 = NamedDescription.allDirectSuperrelations(((NamedDescription)(renamed_Class)), true);

            loop002 : for (;!(iter002 == Stella.NIL); iter002 = iter002.rest) {
              parent = ((NamedDescription)(iter002.value));
              if (allclasses.memberP(parent)) {
                addP = false;
                break loop002;
              }
            }
          }
          if (addP) {
            toplevelclasses.push(renamed_Class);
          }
        }
      }
      OntosaurusUtil.htmlWriteHeaderWithTable(stream, title, head);
      stream.print(nconcepts + " " + OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_CONCEPT, false, !(nconcepts == 1)) + "; " + nrelations + " " + OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_RELATION, false, !(nrelations == 1)) + "; " + ninstances + " " + OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_INSTANCE, false, !(ninstances == 1)) + ";  TOTAL of objects = " + (nconcepts + nrelations + ninstances));
      {
        stream.print("<P>");
        {
          stream.print("<B>");
          stream.print("Top Level Classes:");
          stream.print("</B>");
        }
        stream.println("<BR>");
        if (toplevelclasses.emptyP()) {
          {
            stream.print("<I>");
            stream.print("None");
            stream.println("</I>");
          }
        }
        else {
          {
            stream.print("<DL>");
            toplevelclasses = toplevelclasses.sort(Native.find_java_method("edu.isi.powerloom.logic.LogicObject", "objectNameLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.powerloom.logic.LogicObject"), Native.find_java_class("edu.isi.powerloom.logic.LogicObject")}));
            { LogicObject renamed_Class = null;
              Cons iter003 = toplevelclasses.theConsList;

              for (;!(iter003 == Stella.NIL); iter003 = iter003.rest) {
                renamed_Class = ((LogicObject)(iter003.value));
                {
                  stream.print("<DT STYLE='margin-top: 0'>");
                  OntosaurusUtil.htmlWriteHref(stream, "show", "concept", renamed_Class);
                  stream.println("</DT>");
                }
              }
            }
            stream.print("</DL>");
          }
        }
        stream.println("</P>");
      }
      if (ruleP) {
        stream.println("<HR SIZE=2>");
      }
      return;
    }
  }

  public static void htmlDescribeModule(Module module, edu.isi.stella.javalib.NativeOutputStream stream) {
    if (!(module != null)) {
      return;
    }
    { String namestring = module.name();

      if (OntosaurusUtil.vizServerAvailableP() &&
          ((!((BooleanWrapper)(KeyValueList.dynamicSlotValue(module.dynamicSlots, OntosaurusUtil.SYM_STELLA_CODE_ONLYp, Stella.FALSE_WRAPPER))).wrapperValue) &&
           (!((BooleanWrapper)(KeyValueList.dynamicSlotValue(module.dynamicSlots, OntosaurusUtil.SYM_STELLA_NAMESPACEp, Stella.FALSE_WRAPPER))).wrapperValue))) {
        OntosaurusUtil.htmlWriteHrefInDetail(stream, "Graph", "graph", "context", module.name(), module.name(), "Graph " + module.name(), false);
      }
      OntosaurusUtil.htmlDisplayImages(module, stream);
      OntosaurusUtil.htmlDisplayDocumentation(module, stream);
      OntosaurusUtil.htmlDescribeModuleSubs("Child Modules", namestring, module, stream, true);
      OntosaurusUtil.htmlDescribeModuleSupers("Parent Modules", namestring, module, stream, true);
      OntosaurusUtil.htmlDisplayModuleStats("Contents", namestring, module, stream, true);
      return;
    }
  }

  public static void htmlUnknownModuleResponse(Keyword itemtype, String itemname, String modulename, edu.isi.stella.javalib.NativeOutputStream stream) {
    {
      stream.print("<HTML>");
      {
        stream.print("<HEAD>");
        {
          stream.print("<TITLE>");
          stream.print(OntosaurusUtil.lookupTerm(itemtype, true, false) + " ");
          Stella.writeHtmlQuotingSpecialCharacters(stream, itemname);
          stream.println("</TITLE>");
        }
        stream.println("</HEAD>");
      }
      { String tag001 = "BODY BGCOLOR='#" + OntosaurusUtil.$ERROR_BACKGROUND_COLOR$ + "'";

        stream.print("<" + tag001 + ">");
        {
          stream.print("<H1>");
          stream.print(OntosaurusUtil.lookupTerm(itemtype, true, false) + " ");
          Stella.writeHtmlQuotingSpecialCharacters(stream, itemname);
          stream.println("</H1>");
        }
        stream.println("<HR SIZE=4>");
        {
          stream.print("<STRONG>");
          stream.print("SORRY: Unknown " + OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_CONTEXT, false, false) + " `");
          Stella.writeHtmlQuotingSpecialCharacters(stream, modulename);
          stream.print("'.");
          OntosaurusUtil.htmlLineBreak(stream);
          stream.println("<HR SIZE=2>");
          OntosaurusUtil.writePowerloomTrailer(stream);
          stream.println("</STRONG>");
        }
        stream.println("</" + Native.string_subsequence(tag001, 0, Native.string_position(tag001, ' ', 0)) + ">");
      }
      stream.println("</HTML>");
    }
  }

  public static void htmlUnknownObjectResponse(Keyword itemtype, String itemname, edu.isi.stella.javalib.NativeOutputStream stream) {
    {
      stream.print("<HTML>");
      {
        stream.print("<HEAD>");
        {
          stream.print("<TITLE>");
          stream.print(OntosaurusUtil.lookupTerm(itemtype, true, false) + " ");
          Stella.writeHtmlQuotingSpecialCharacters(stream, itemname);
          stream.print("</TITLE>");
        }
        stream.println();
        stream.print("</HEAD>");
      }
      stream.println();
      { String tag002 = "BODY BGCOLOR='#" + OntosaurusUtil.$ERROR_BACKGROUND_COLOR$ + "'";

        stream.print("<" + tag002 + ">");
        {
          stream.print("<H1>");
          stream.print(OntosaurusUtil.lookupTerm(itemtype, true, false) + " ");
          Stella.writeHtmlQuotingSpecialCharacters(stream, itemname);
          stream.println("</H1>");
        }
        stream.println("<HR SIZE=4>");
        {
          stream.print("<STRONG>");
          stream.print("SORRY: Unknown " + OntosaurusUtil.lookupTerm(itemtype, false, false) + " `" + itemname + "' in " + OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_CONTEXT, false, false) + " ");
          Stella.writeHtmlQuotingSpecialCharacters(stream, ((Module)(Stella.$MODULE$.get())).name());
          stream.print(".");
          stream.print("</STRONG>");
        }
        OntosaurusUtil.htmlLineBreak(stream);
        stream.println("<HR SIZE=2>");
        OntosaurusUtil.writePowerloomTrailer(stream);
        stream.println("</" + Native.string_subsequence(tag002, 0, Native.string_position(tag002, ' ', 0)) + ">");
      }
      stream.print("</HTML>");
    }
  }

  public static void htmlWriteRelationResponsePage(NamedDescription relation, edu.isi.stella.javalib.NativeOutputStream stream) {
    { String objectname = OntosaurusUtil.getHtmlObjectHandle(relation);

      {
        stream.print("<HTML>");
        {
          stream.print("<HEAD>");
          stream.println("<BASE TARGET='content'>");
          {
            stream.print("<TITLE>");
            stream.print(OntosaurusUtil.lookupTerm((Logic.classP(relation) ? OntosaurusUtil.KWD_CONCEPT : OntosaurusUtil.KWD_RELATION), true, false) + " ");
            Stella.writeHtmlQuotingSpecialCharacters(stream, objectname);
            stream.println("</TITLE>");
          }
          stream.println("</HEAD>");
        }
        { String tag003 = "BODY BGCOLOR='#" + OntosaurusUtil.$STANDARD_BACKGROUND_COLOR$ + "'";

          stream.print("<" + tag003 + ">");
          {
            stream.print("<H1>");
            stream.print(OntosaurusUtil.lookupTerm((Logic.classP(relation) ? OntosaurusUtil.KWD_CONCEPT : OntosaurusUtil.KWD_RELATION), true, false) + " ");
            Stella.writeHtmlQuotingSpecialCharacters(stream, objectname);
            stream.println("</H1>");
          }
          stream.println("<HR SIZE=4>");
          OntosaurusUtil.htmlDescribeNamedDescription(relation, stream);
          OntosaurusUtil.writePowerloomTrailer(stream);
          stream.println("</" + Native.string_subsequence(tag003, 0, Native.string_position(tag003, ' ', 0)) + ">");
        }
        stream.println("</HTML>");
      }
    }
  }

  public static void htmlWriteInstanceResponsePage(LogicObject instance, edu.isi.stella.javalib.NativeOutputStream stream) {
    { String objectname = OntosaurusUtil.getHtmlObjectHandle(instance);

      {
        stream.print("<HTML>");
        {
          stream.print("<HEAD>");
          stream.println("<BASE TARGET='content'>");
          {
            stream.print("<TITLE>");
            stream.print(OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_INSTANCE, true, false) + " ");
            Stella.writeHtmlQuotingSpecialCharacters(stream, objectname);
            stream.println("</TITLE>");
          }
          stream.println("</HEAD>");
        }
        { String tag004 = "BODY BGCOLOR='#" + OntosaurusUtil.$STANDARD_BACKGROUND_COLOR$ + "'";

          stream.print("<" + tag004 + ">");
          {
            stream.print("<H1>");
            stream.print(OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_INSTANCE, true, false) + " ");
            Stella.writeHtmlQuotingSpecialCharacters(stream, objectname);
            stream.println("</H1>");
          }
          stream.println("<HR SIZE=4>");
          OntosaurusUtil.htmlDescribeInstance(instance, stream);
          OntosaurusUtil.writePowerloomTrailer(stream);
          stream.println("</" + Native.string_subsequence(tag004, 0, Native.string_position(tag004, ' ', 0)) + ">");
        }
        stream.println("</HTML>");
      }
    }
  }

  public static void htmlWriteObjectResponsePageInternal(Stella_Object renamed_Object, edu.isi.stella.javalib.NativeOutputStream stream) {
    { String objectname = OntosaurusUtil.getHtmlObjectHandle(renamed_Object);

      if (objectname == null) {
        objectname = Native.stringify(renamed_Object);
      }
      {
        stream.print("<HTML>");
        {
          stream.print("<HEAD>");
          stream.println("<BASE TARGET='content'>");
          {
            stream.print("<TITLE>");
            stream.print(OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_OBJECT, true, false) + " ");
            Stella.writeHtmlQuotingSpecialCharacters(stream, objectname);
            stream.println("</TITLE>");
          }
          stream.println("</HEAD>");
        }
        { String tag005 = "BODY BGCOLOR='#" + OntosaurusUtil.$STANDARD_BACKGROUND_COLOR$ + "'";

          stream.print("<" + tag005 + ">");
          {
            stream.print("<H1>");
            stream.print(OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_OBJECT, true, false) + " ");
            Stella.writeHtmlQuotingSpecialCharacters(stream, objectname);
            stream.println("</H1>");
          }
          stream.println("<HR SIZE=4>");
          Stella.writeHtmlQuotingSpecialCharacters(stream, objectname);
          stream.println("<BR>");
          stream.println("<HR SIZE=2>");
          OntosaurusUtil.writePowerloomTrailer(stream);
          stream.println("</" + Native.string_subsequence(tag005, 0, Native.string_position(tag005, ' ', 0)) + ">");
        }
        stream.println("</HTML>");
      }
    }
  }

  public static void htmlWriteModuleResponsePageInternal(Module module, edu.isi.stella.javalib.NativeOutputStream stream) {
    { String modulename = module.name();

      {
        stream.print("<HTML>");
        {
          stream.print("<HEAD>");
          stream.println("<BASE TARGET='content'>");
          {
            stream.print("<TITLE>");
            stream.print(OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_MODULE, true, false) + " ");
            Stella.writeHtmlQuotingSpecialCharacters(stream, modulename);
            stream.println("</TITLE>");
          }
          stream.println("</HEAD>");
        }
        { String tag006 = "BODY BGCOLOR='#" + OntosaurusUtil.$MODULE_BACKGROUND_COLOR$ + "'";

          stream.print("<" + tag006 + ">");
          {
            stream.print("<H1>");
            stream.print(OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_CONTEXT, true, false) + " ");
            Stella.writeHtmlQuotingSpecialCharacters(stream, modulename);
            stream.println("</H1>");
          }
          stream.println("<HR SIZE=4>");
          OntosaurusUtil.htmlDescribeModule(module, stream);
          OntosaurusUtil.writePowerloomTrailer(stream);
          stream.println("</" + Native.string_subsequence(tag006, 0, Native.string_position(tag006, ' ', 0)) + ">");
        }
        stream.println("</HTML>");
      }
    }
  }

  public static void htmlWriteModuleResponsePage(String modulename, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Module module = Stella.getStellaModule(modulename, false);

      if (module == null) {
        OntosaurusUtil.htmlUnknownObjectResponse(OntosaurusUtil.KWD_CONTEXT, modulename, stream);
      }
      else {
        { Object old$Module$000 = Stella.$MODULE$.get();
          Object old$Context$000 = Stella.$CONTEXT$.get();

          try {
            Native.setSpecial(Stella.$MODULE$, module);
            Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
            OntosaurusUtil.htmlWriteModuleResponsePageInternal(module, stream);

          } finally {
            Stella.$CONTEXT$.set(old$Context$000);
            Stella.$MODULE$.set(old$Module$000);
          }
        }
      }
    }
  }

  public static void htmlWriteObjectResponsePage(String modulename, String objectname, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Module module = Stella.getStellaModule(modulename, false);

      if (module == null) {
        OntosaurusUtil.htmlUnknownModuleResponse(OntosaurusUtil.KWD_RELATION, objectname, modulename, stream);
        return;
      }
      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { Stella_Object instance = (Stella.startsWithP(objectname, "(", 0) ? Logic.coerceToInstance(Stella.readSExpressionFromString(objectname), null) : edu.isi.powerloom.PLI.getObject(objectname, null, null));

            if (instance != null) {
              { Surrogate testValue000 = Stella_Object.safePrimaryType(instance);

                if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_NAMED_DESCRIPTION)) {
                  { NamedDescription instance000 = ((NamedDescription)(instance));

                    OntosaurusUtil.htmlWriteRelationResponsePage(instance000, stream);
                  }
                }
                else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
                  { LogicObject instance000 = ((LogicObject)(instance));

                    OntosaurusUtil.htmlWriteInstanceResponsePage(instance000, stream);
                  }
                }
                else {
                  OntosaurusUtil.htmlWriteObjectResponsePageInternal(instance, stream);
                }
              }
            }
            else {
              OntosaurusUtil.htmlUnknownObjectResponse(OntosaurusUtil.KWD_OBJECT, objectname, stream);
            }
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  public static List findCandidateObjects(String objectname, String objecttype, Keyword matchtype) {
    { String barename = null;
      String modulename = null;
      Keyword kind = null;
      List results = List.newList();
      Symbol candidateobjectname = null;
      Module objectmodule = null;
      String upcasedobjectname = null;
      Iterator candidateterms = null;

      kind = kind;
      try {
        { Object [] caller_MV_returnarray = new Object[2];

          barename = Stella.parseStellaName(objectname, false, caller_MV_returnarray);
          modulename = ((String)(((StringWrapper)(caller_MV_returnarray[0])).wrapperValue));
          kind = ((Keyword)(caller_MV_returnarray[1]));
        }
      } catch (ReadException e000) {
        barename = objectname;
      }
      upcasedobjectname = Native.stringUpcase(barename);
      candidateterms = Logic.allNamedTerms(((Module)(((Context)(Stella.$CONTEXT$.get())))), false);
      if (modulename != null) {
        objectmodule = Stella.getStellaModule(modulename, true);
      }
      if (matchtype == OntosaurusUtil.KWD_EXACT) {
        { Stella_Object obj = null;
          Iterator iter000 = candidateterms;

          loop000 : while (iter000.nextP()) {
            obj = iter000.value;
            if (Stella_Object.isaP(obj, OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
              candidateobjectname = Logic.objectName(obj);
              if (candidateobjectname != null) {
                if (Stella.stringEqlP(candidateobjectname.symbolName, barename) &&
                    ((objectmodule == null) ||
                     (candidateobjectname.homeModule() == objectmodule))) {
                  results.push(((LogicObject)(obj)));
                  continue loop000;
                }
              }
              { LogicObject syn = null;
                Cons iter001 = Logic.getSynonyms(obj);

                loop001 : for (;!(iter001 == Stella.NIL); iter001 = iter001.rest) {
                  syn = ((LogicObject)(iter001.value));
                  candidateobjectname = Logic.objectName(syn);
                  if (candidateobjectname != null) {
                    if (Stella.stringEqlP(candidateobjectname.symbolName, barename) &&
                        ((objectmodule == null) ||
                         (candidateobjectname.homeModule() == objectmodule))) {
                      results.push(syn);
                      break loop001;
                    }
                  }
                }
              }
            }
          }
        }
      }
      else if (matchtype == OntosaurusUtil.KWD_CASE_INSENSITIVE) {
        { Stella_Object obj = null;
          Iterator iter002 = candidateterms;

          loop002 : while (iter002.nextP()) {
            obj = iter002.value;
            if (Stella_Object.isaP(obj, OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
              candidateobjectname = Logic.objectName(obj);
              if (candidateobjectname != null) {
                if (Stella.stringEqualP(candidateobjectname.symbolName, barename) &&
                    ((objectmodule == null) ||
                     (candidateobjectname.homeModule() == objectmodule))) {
                  results.push(((LogicObject)(obj)));
                  continue loop002;
                }
              }
              { LogicObject syn = null;
                Cons iter003 = Logic.getSynonyms(obj);

                loop003 : for (;!(iter003 == Stella.NIL); iter003 = iter003.rest) {
                  syn = ((LogicObject)(iter003.value));
                  candidateobjectname = Logic.objectName(syn);
                  if (candidateobjectname != null) {
                    if (Stella.stringEqualP(candidateobjectname.symbolName, barename) &&
                        ((objectmodule == null) ||
                         (candidateobjectname.homeModule() == objectmodule))) {
                      results.push(syn);
                      break loop003;
                    }
                  }
                }
              }
            }
          }
        }
      }
      else if (matchtype == OntosaurusUtil.KWD_SUBSTRING) {
        { Stella_Object obj = null;
          Iterator iter004 = candidateterms;

          loop004 : while (iter004.nextP()) {
            obj = iter004.value;
            if (Stella_Object.isaP(obj, OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
              candidateobjectname = Logic.objectName(obj);
              if (candidateobjectname != null) {
                if ((Native.stringSearch(Native.stringUpcase(candidateobjectname.symbolName), upcasedobjectname, 0) != Stella.NULL_INTEGER) &&
                    ((objectmodule == null) ||
                     (candidateobjectname.homeModule() == objectmodule))) {
                  results.push(((LogicObject)(obj)));
                  continue loop004;
                }
              }
              { LogicObject syn = null;
                Cons iter005 = Logic.getSynonyms(obj);

                loop005 : for (;!(iter005 == Stella.NIL); iter005 = iter005.rest) {
                  syn = ((LogicObject)(iter005.value));
                  candidateobjectname = Logic.objectName(syn);
                  if (candidateobjectname != null) {
                    if ((Native.stringSearch(Native.stringUpcase(candidateobjectname.symbolName), upcasedobjectname, 0) != Stella.NULL_INTEGER) &&
                        ((objectmodule == null) ||
                         (candidateobjectname.homeModule() == objectmodule))) {
                      results.push(syn);
                      break loop005;
                    }
                  }
                }
              }
            }
          }
        }
      }
      else if (matchtype == OntosaurusUtil.KWD_WILDCARD) {
        throw ((StellaException)(StellaException.newStellaException(":WILDCARD matching not implemented yet").fillInStackTrace()));
      }
      else if (matchtype == OntosaurusUtil.KWD_REGEX) {
        throw ((StellaException)(StellaException.newStellaException(":REGEX matching not implemented yet").fillInStackTrace()));
      }
      else {
        { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

          stream000.nativeStream.print("`" + matchtype + "' is not a valid case option");
          throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
        }
      }
      results.removeDuplicates();
      results.sort(Native.find_java_method("edu.isi.powerloom.logic.Logic", "logicFormLessP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.Stella_Object"), Native.find_java_class("edu.isi.stella.Stella_Object")}));
      return (results);
    }
  }

  public static LogicObject resolveSynonyms(LogicObject obj) {
    { Surrogate surrogate = obj.surrogateValueInverse;

      if ((surrogate != null) &&
          Logic.synonymSurrogateP(surrogate)) {
        return (((LogicObject)(surrogate.surrogateValue)));
      }
      else {
        return (obj);
      }
    }
  }

  public static void htmlWriteFindObjectResponsePage(String modulename, String objectname, String objecttype, Keyword matchtype, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Module module = Stella.getStellaModule(modulename, false);

      if (module == null) {
        OntosaurusUtil.htmlUnknownModuleResponse(OntosaurusUtil.KWD_RELATION, objectname, modulename, stream);
        return;
      }
      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, module);
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          { List candidateobjects = OntosaurusUtil.findCandidateObjects(objectname, objecttype, matchtype);

            switch (candidateobjects.length()) {
              case 0: 
                OntosaurusUtil.htmlUnknownObjectResponse((Stella.stringEqlP(objecttype, "instance") ? OntosaurusUtil.KWD_OBJECT : OntosaurusUtil.KWD_RELATION), objectname, stream);
              break;
              case 1: 
                { Surrogate testValue000 = Stella_Object.safePrimaryType(((LogicObject)(candidateobjects.first())));

                  if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_NAMED_DESCRIPTION)) {
                    OntosaurusUtil.htmlWriteRelationResponsePage(((NamedDescription)(OntosaurusUtil.resolveSynonyms(((LogicObject)(candidateobjects.first()))))), stream);
                  }
                  else if (Surrogate.subtypeOfP(testValue000, OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
                    OntosaurusUtil.htmlWriteInstanceResponsePage(OntosaurusUtil.resolveSynonyms(((LogicObject)(candidateobjects.first()))), stream);
                  }
                  else {
                    throw ((StellaException)(StellaException.newStellaException("Can't handle object in html-write-find-object-response-page").fillInStackTrace()));
                  }
                }
              break;
              default:
                OntosaurusUtil.htmlWriteMultipleChoicePage(objectname, candidateobjects, stream);
              break;
            }
          }

        } finally {
          Stella.$CONTEXT$.set(old$Context$000);
          Stella.$MODULE$.set(old$Module$000);
        }
      }
    }
  }

  public static void htmlWriteMultipleChoicePage(String searchstring, List candidateobjects, edu.isi.stella.javalib.NativeOutputStream stream) {
    {
      stream.print("<HTML>");
      {
        stream.print("<HEAD>");
        stream.println("<BASE TARGET='content'>");
        {
          stream.print("<TITLE>");
          Stella.writeHtmlQuotingSpecialCharacters(stream, searchstring);
          stream.println("</TITLE>");
        }
        stream.println("</HEAD>");
      }
      { String tag007 = "BODY BGCOLOR='#" + OntosaurusUtil.$STANDARD_BACKGROUND_COLOR$ + "'";

        stream.print("<" + tag007 + ">");
        {
          stream.print("<H1>");
          stream.print("Matches for &quot;");
          {
            stream.print("<FONT COLOR='#990033'>");
            Stella.writeHtmlQuotingSpecialCharacters(stream, searchstring);
            stream.print("</FONT>");
          }
          stream.print("&quot;");
          stream.println("</H1>");
        }
        stream.println("<HR SIZE=4>");
        { LogicObject obj = null;
          Cons iter000 = candidateobjects.theConsList;

          for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
            obj = ((LogicObject)(iter000.value));
            if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(obj), OntosaurusUtil.SGT_LOGIC_DESCRIPTION)) {
              { Description obj000 = ((Description)(obj));

                if (Logic.classP(obj000)) {
                  stream.print("Concept ");
                }
                else {
                  stream.print("Relation ");
                }
                OntosaurusUtil.pprintObject(obj000, stream);
              }
            }
            else {
              stream.print("Object ");
              OntosaurusUtil.pprintObject(obj, stream);
            }
            OntosaurusUtil.htmlLineBreak(stream);
          }
        }
        stream.println("<HR SIZE=2>");
        OntosaurusUtil.writePowerloomTrailer(stream);
        stream.println("</" + Native.string_subsequence(tag007, 0, Native.string_position(tag007, ' ', 0)) + ">");
      }
      stream.println("</HTML>");
    }
  }

  public static void htmlPowerloomResponse(String action, String objecttype, String modulename, String objectname, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Object old$PprintAtomicObjectRenderer$000 = OntosaurusUtil.$PPRINT_ATOMIC_OBJECT_RENDERER$.get();
      Object old$PprintIndent$000 = OntosaurusUtil.$PPRINT_INDENT$.get();
      Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();

      try {
        Native.setSpecial(OntosaurusUtil.$PPRINT_ATOMIC_OBJECT_RENDERER$, Symbol.lookupFunction(OntosaurusUtil.SYM_ONTOSAURUS_PPRINT_ATOMIC_OBJECT_FOR_HTML).functionCode);
        Native.setIntSpecial(OntosaurusUtil.$PPRINT_INDENT$, 0);
        Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
        if (Stella.stringEqlP(objecttype, "object") ||
            (Stella.stringEqlP(objecttype, "concept") ||
             (Stella.stringEqlP(objecttype, "relation") ||
              Stella.stringEqlP(objecttype, "instance")))) {
          if (Stella.stringEqlP(action, "show")) {
            { Object old$OntosaurusUrlAction$000 = OntosaurusUtil.$ONTOSAURUS_URL_ACTION$.get();

              try {
                Native.setSpecial(OntosaurusUtil.$ONTOSAURUS_URL_ACTION$, "show");
                OntosaurusUtil.htmlWriteObjectResponsePage(modulename, objectname, stream);

              } finally {
                OntosaurusUtil.$ONTOSAURUS_URL_ACTION$.set(old$OntosaurusUrlAction$000);
              }
            }
            return;
          }
          else if (Stella.stringEqlP(action, "find") ||
              Stella.stringEqlP(action, "findsubstring")) {
            { Object old$OntosaurusUrlAction$001 = OntosaurusUtil.$ONTOSAURUS_URL_ACTION$.get();

              try {
                Native.setSpecial(OntosaurusUtil.$ONTOSAURUS_URL_ACTION$, "show");
                OntosaurusUtil.htmlWriteFindObjectResponsePage(modulename, objectname, objecttype, OntosaurusUtil.KWD_SUBSTRING, stream);

              } finally {
                OntosaurusUtil.$ONTOSAURUS_URL_ACTION$.set(old$OntosaurusUrlAction$001);
              }
            }
            return;
          }
          else if (Stella.stringEqlP(action, "findexact")) {
            { Object old$OntosaurusUrlAction$002 = OntosaurusUtil.$ONTOSAURUS_URL_ACTION$.get();

              try {
                Native.setSpecial(OntosaurusUtil.$ONTOSAURUS_URL_ACTION$, "show");
                OntosaurusUtil.htmlWriteFindObjectResponsePage(modulename, objectname, objecttype, OntosaurusUtil.KWD_EXACT, stream);

              } finally {
                OntosaurusUtil.$ONTOSAURUS_URL_ACTION$.set(old$OntosaurusUrlAction$002);
              }
            }
            return;
          }
          else if (Stella.stringEqlP(action, "findinsensitive")) {
            { Object old$OntosaurusUrlAction$003 = OntosaurusUtil.$ONTOSAURUS_URL_ACTION$.get();

              try {
                Native.setSpecial(OntosaurusUtil.$ONTOSAURUS_URL_ACTION$, "show");
                OntosaurusUtil.htmlWriteFindObjectResponsePage(modulename, objectname, objecttype, OntosaurusUtil.KWD_CASE_INSENSITIVE, stream);

              } finally {
                OntosaurusUtil.$ONTOSAURUS_URL_ACTION$.set(old$OntosaurusUrlAction$003);
              }
            }
            return;
          }
        }
        else if (Stella.stringEqlP(objecttype, "context") &&
            Stella.stringEqlP(action, "show")) {
          OntosaurusUtil.htmlWriteModuleResponsePage(modulename, stream);
          return;
        }
        else if (Stella.stringEqlP(objecttype, "query")) {
          if (Stella.stringEqlP(action, "explain")) {
            OntosaurusUtil.htmlWriteExplanationResponsePage(modulename, objectname, stream);
            return;
          }
        }

      } finally {
        Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
        OntosaurusUtil.$PPRINT_INDENT$.set(old$PprintIndent$000);
        OntosaurusUtil.$PPRINT_ATOMIC_OBJECT_RENDERER$.set(old$PprintAtomicObjectRenderer$000);
      }
    }
    {
      stream.print("<FONT COLOR='#BB0000'>");
      {
        stream.print("<B>");
        stream.print("ERROR: Unrecognized action-type pair: '" + action + "' '" + objecttype + "'.");
        stream.print("</B>");
      }
      stream.println("</FONT>");
    }
    return;
  }

  public static void doActionHandler(edu.isi.webtools.http.HttpExchange xchg) {
    { Cons keys = edu.isi.webtools.http.Http.parseAndDecodeUrlArguments(edu.isi.webtools.http.HttpExchange.getRequestUriQuery(xchg), '+');
      StringWrapper action = ((StringWrapper)(keys.value));
      StringWrapper objecttype = ((StringWrapper)(keys.rest.value));
      StringWrapper modulename = ((StringWrapper)(keys.rest.rest.value));
      StringWrapper objectname = ((StringWrapper)(keys.fourth()));
      edu.isi.stella.javalib.NativeOutputStream stream = edu.isi.webtools.http.HttpExchange.getReplyStream(xchg);

      try {
        if (keys.length() >= 4) {
          if (Stella.startsWithP(action.wrapperValue, "graph", 0)) {
            OntosaurusUtil.vizServerHandler(xchg);
          }
          else {
            OntosaurusUtil.htmlPowerloomResponse(action.wrapperValue, objecttype.wrapperValue, modulename.wrapperValue, objectname.wrapperValue, stream);
          }
        }
        else {
          edu.isi.webtools.http.HttpExchange.setResponseCode(xchg, OntosaurusUtil.KWD_BAD_REQUEST);
          { String tag008 = OntosaurusUtil.makeHtmlBodyTag(OntosaurusUtil.$ERROR_BACKGROUND_COLOR$);

            stream.print("<" + tag008 + ">");
            stream.println("ERROR: expected four parameters, only received " + keys.length());
            stream.println("<BR><OL>");
            { StringWrapper key = null;
              Cons iter000 = keys;

              for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
                key = ((StringWrapper)(iter000.value));
                stream.println("<LI>" + key + "</LI>");
              }
            }
            stream.println("</OL>");
            stream.println("</" + Native.string_subsequence(tag008, 0, Native.string_position(tag008, ' ', 0)) + ">");
          }
        }
      } catch (java.lang.Exception e) {
        edu.isi.webtools.http.HttpExchange.generateErrorResponse(xchg, OntosaurusUtil.KWD_BAD_REQUEST, Stella.exceptionMessage(e));
      }
    }
  }

  public static boolean savingAllowedP() {
    return (false);
  }

  public static boolean loadingAllowedP() {
    return (false);
  }

  public static boolean edittingAllowedP() {
    return (false);
  }

  public static boolean edittingPossibleP() {
    return (false);
  }

  public static boolean currentEditLockP() {
    return (false);
  }

  public static Cons sortedContexts() {
    { Cons contextnames = Stella.NIL;

      { Module m = null;
        Iterator iter000 = Stella.allModules();

        while (iter000.nextP()) {
          m = ((Module)(iter000.value));
          if ((!((BooleanWrapper)(KeyValueList.dynamicSlotValue(m.dynamicSlots, OntosaurusUtil.SYM_STELLA_CODE_ONLYp, Stella.FALSE_WRAPPER))).wrapperValue) &&
              (!((BooleanWrapper)(KeyValueList.dynamicSlotValue(m.dynamicSlots, OntosaurusUtil.SYM_STELLA_NAMESPACEp, Stella.FALSE_WRAPPER))).wrapperValue)) {
            contextnames = Cons.cons(StringWrapper.wrapString(m.name()), contextnames);
          }
        }
      }
      return (contextnames.sort(Native.find_java_method("edu.isi.stella.StringWrapper", "wrappedStringLessThanP", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.StringWrapper"), Native.find_java_class("edu.isi.stella.StringWrapper")})));
    }
  }

  public static void serveControlPanelInternal(edu.isi.stella.javalib.NativeOutputStream stream) {
    {
      stream.print("<HTML>");
      {
        stream.print("<HEAD>");
        {
          stream.print("<TITLE>");
          stream.print("PowerLoom Browser Control Panel");
          stream.println("</TITLE>");
        }
        OntosaurusUtil.writeControlPanelScript(stream);
        stream.println("</HEAD>");
      }
      { String tag009 = "BODY BGCOLOR='#" + OntosaurusUtil.$CONTROL_BACKGROUND_COLOR$ + "'";

        stream.print("<" + tag009 + ">");
        OntosaurusUtil.writeTopSection(stream);
        OntosaurusUtil.writeTheorySection(stream);
        OntosaurusUtil.writeBottomSection(stream);
        stream.println("</" + Native.string_subsequence(tag009, 0, Native.string_position(tag009, ' ', 0)) + ">");
      }
      stream.println("</HTML>");
    }
    return;
  }

  public static void writeTheorySection(edu.isi.stella.javalib.NativeOutputStream stream) {
    stream.print("<b>" + OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_CONTEXT, true, false) + ":</b>&nbsp;");
    stream.println("<SELECT NAME=\"theory\" onChange='document.cookie=\"theory=\" + this[this.selectedIndex].value + \";\";'>");
    { StringWrapper c = null;
      Cons iter000 = OntosaurusUtil.sortedContexts();

      for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
        c = ((StringWrapper)(iter000.value));
        stream.println("<option VALUE='" + c.wrapperValue + "'>" + c.wrapperValue + "</option>");
      }
    }
    stream.println("</SELECT>");
    return;
  }

  public static void writeTopSection(edu.isi.stella.javalib.NativeOutputStream stream) {
    {
      stream.println("<FORM NAME=\"navform\" TARGET=\"content\" METHOD=\"POST\" onSubmit=\"return formTest(this)\">");
      stream.println("<TABLE BORDER>");
      stream.println("<TR>");
      stream.println("<TD ALIGN=center COLSPAN=1 ROWSPAN=1>");
      stream.println("<A HREF=\"help/intro.html\" TARGET=\"content\" onMouseOver=\"window.status='Shows directions for using this browser'; return true\">");
      stream.println("<IMG SRC=\"/ploom/icons/button-34-help.gif\" BORDER=0 WIDTH=12 HEIGHT=14></a></TD>");
      stream.println("<TD COLSPAN=1 ROWSPAN=1 VALIGN=TOP>");
    }
;
    return;
  }

  public static void writeBottomSection(edu.isi.stella.javalib.NativeOutputStream stream) {
    stream.print("<input TYPE=button  NAME=\"show\" VALUE=\"Show\" onClick=\"loadContextURL('content', 'show', this.form)\">\n");
    if (OntosaurusUtil.savingAllowedP()) {
      stream.print("<input TYPE=button  NAME=\"save\" VALUE=\"Save...\" onClick=\"loadContextURL('content', 'save',this.form)\">\n");
    }
    if (OntosaurusUtil.loadingAllowedP()) {
      stream.print("<input TYPE=button  NAME= \"load\" VALUE=\"Load...\" \n       onClick=\"loadContextURL('content', 'load', this.form)\">\n");
    }
    if (OntosaurusUtil.edittingAllowedP()) {
      stream.print("<input TYPE=button  NAME=\"newctxt\" VALUE=\"New...\" onClick=\"loadNewContextURL('toc', 'COMMON-LISP-USER', this.form)\">\n");
    }
    {
      stream.println();
      stream.print("</TD>");
    }
;
    stream.println("<TD ROWSPAN=1 ALIGN=CENTER>");
    stream.println("<INPUT TYPE=\"button\" NAME=\"swap\" VALUE=\"Hold Window\" \n  onClick=\"putLeft(parent.frames[2].document.location.href)\" onMouseOver=\"window.status='Moves the content window into the reference window.'; return true\">");
    stream.println("</TD>");
    if (OntosaurusUtil.edittingPossibleP()) {
      {
        stream.print("<TD ALIGN=LEFT ROWSPAN=2");
        if (OntosaurusUtil.edittingAllowedP()) {
          stream.print(" BGCOLOR='#FFCCCC'");
        }
        else if (OntosaurusUtil.currentEditLockP()) {
          stream.print(" BGCOLOR='#FFFFCC'");
        }
        {
          stream.println(">");
          stream.print("<INPUT TYPE=\"radio\" NAME=\"LOCK\" VALUE=\"0\" onClick=\"location.pathname='/loom/edit-unlock.html'\"");
        }
;
        if (!(OntosaurusUtil.edittingAllowedP())) {
          stream.print(" CHECKED");
        }
        {
          stream.println(">Browse&nbsp;only<BR>");
          stream.print("<INPUT TYPE=\"radio\" NAME=\"LOCK\" VALUE=\"1\" onClick=\"location.pathname='/loom/edit-lock.html'\"");
        }
;
        if (OntosaurusUtil.edittingAllowedP()) {
          stream.print(" CHECKED");
        }
        stream.print(">Make&nbsp;Changes<BR>&nbsp;&nbsp;(Others&nbsp;blocked)\n</TD></TR>");
      }
    }
    else {
      {
        stream.println("<TD ALIGN=CENTER ROWSPAN=2 VALIGN=CENTER>");
        stream.println("<A HREF=\"http://www.isi.edu/isd/LOOM/PowerLoom/\" TARGET=\"manual\" onMouseOver=\"window.status='Goes to the PowerLoom Home Page'; return true\"><img src=\"/ploom/icons/powerloom-logo-small.gif\" BORDER=0 WIDTH=40 HEIGHT=38></A>");
        stream.println("</TD>");
        stream.println("</TR>");
      }
;
    }
    {
      stream.println("<TR><TD ALIGN=CENTER ROWSPAN=1>");
      stream.println("<A HREF='" + OntosaurusUtil.$POWERLOOM_REFERENCE_MANUAL_URL$ + "' TARGET=\"manual\" onMouseOver=\"window.status='PowerLoom Reference Manual' ; return true\">");
      stream.println("<IMG SRC=\"/ploom/icons/book-small.gif\" BORDER=0 WIDTH=21 HEIGHT=11></a></TD>");
      stream.println("<TD ALIGN=JUSTIFY ROWSPAN=1 COLSPAN=2>");
    }
;
    {
      stream.println("");
      stream.println();
      stream.println("<SELECT NAME=\"objecttype\">");
      stream.println("<option VALUE=\"object\" SELECTED>any</option>");
      stream.println("<option VALUE=\"concept\">" + OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_CONCEPT, false, false) + "</option>");
      stream.println("<option VALUE=\"relation\">" + OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_RELATION, false, false) + "</option>");
      stream.println("<option VALUE=\"instance\">" + OntosaurusUtil.lookupTerm(OntosaurusUtil.KWD_INSTANCE, false, false) + "</option>");
      stream.println("</SELECT>");
    }
;
    {
      stream.println();
      stream.println("<INPUT NAME=\"find\" SIZE=30 >");
      stream.println();
      stream.println("<input TYPE=submit  NAME=\"dofind\" VALUE=\"Find\" onClick=\"loadURL('content', 'show', this.form)\">");
    }
;
    if (OntosaurusUtil.edittingAllowedP()) {
      stream.print("<input TYPE=button  NAME= \"edit\" VALUE=\"Edit\" \n       onClick=\"loadURL('content', 'edit', this.form)\">\n<input TYPE=button  NAME=\"new\" VALUE=\"New...\" \n       onClick=\"loadURL('content', 'new',this.form)\">\n");
    }
    {
      stream.println("  <img src=\"/ploom/icons/eighth-inch-space.gif\" ALT=\" \" WIDTH=9 HEIGHT=2>");
      stream.println("Match&nbsp;<SELECT NAME=\"matchtype\">");
      stream.println("<option VALUE=\"exact\">Exactly</option>");
      stream.println("<option VALUE=\"caseInsensitive\">Case Insensitive</option>");
      stream.println("<option VALUE=\"substring\" SELECTED>Substring</option>");
      stream.println("</SELECT>");
    }
;
    stream.print("\n</TD></TR></TABLE>\n</FORM>");
    stream.println("<SCRIPT LANGUAGE='JavaScript'>");
    stream.println("var cookieValue = document.cookie.substring(document.cookie.indexOf('theory=')+7,document.cookie.length);");
    stream.println("if (cookieValue.indexOf(';') != -1) {");
    stream.println("cookieValue = cookieValue.substring(0,cookieValue.indexOf(';'));");
    stream.println("}");
    stream.println("for (var i = 0; i < document.navform.theory.length; i++) {");
    stream.println("   if (document.navform.theory[i].value==cookieValue) {");
    stream.println("     document.navform.theory.selectedIndex = i; }");
    {
      stream.println("}</SCRIPT>");
      stream.println();
    }
;
    return;
  }

  public static void serveControlPanelNeedsJavascript(edu.isi.stella.javalib.NativeOutputStream stream) {
    {
      stream.print("<HTML>");
      stream.println();
      {
        stream.print("<HEAD>");
        stream.println();
        {
          stream.print("<TITLE>");
          stream.print("Loom Browser No Javascript");
          stream.println("</TITLE>");
        }
        stream.println("</HEAD>");
      }
      { String tag010 = "BODY BGCOLOR='#" + OntosaurusUtil.$ERROR_BACKGROUND_COLOR$ + "'";

        stream.print("<" + tag010 + ">");
        {
          stream.print("<B>");
          {
            stream.print("<FONT SIZE=6>");
            stream.println("I'm sorry, but a Javascript enabled browser is needed to use this site.");
            stream.println("</FONT>");
          }
          {
            stream.print("<P>");
            {
              stream.print("<FONT SIZE=4>");
              stream.print("If your browser supports Javascript, then you may need to go into the options section and turn on Javascript.  Then reload this location.");
              stream.print("</FONT>");
            }
            stream.println("</P>");
          }
          stream.println("</B>");
        }
        stream.println("</" + Native.string_subsequence(tag010, 0, Native.string_position(tag010, ' ', 0)) + ">");
      }
      stream.println("</HTML>");
    }
  }

  public static void controlPanelHandler(edu.isi.webtools.http.HttpExchange xchg) {
    { edu.isi.stella.javalib.NativeOutputStream stream = edu.isi.webtools.http.HttpExchange.getReplyStream(xchg);

      if (edu.isi.webtools.http.HttpExchange.getRequestMethod(xchg) == OntosaurusUtil.KWD_GET) {
        OntosaurusUtil.serveControlPanelInternal(stream);
      }
      else {
        OntosaurusUtil.serveControlPanelNeedsJavascript(stream);
      }
    }
  }

  public static void htmlWriteQueryFormPage(edu.isi.stella.javalib.NativeOutputStream stream) {
    { OutputStream self000 = OutputStream.newOutputStream();

      self000.nativeStream = stream;
      OntosaurusUtil.htmlWriteQueryFormPageFromTemplate(self000, InputStringStream.newInputStringStream(OntosaurusUtil.$GENERAL_QUERY_FORM_TEMPLATE$));
    }
  }

  public static String yieldPresetQueriesScript(Cons queries) {
    if (queries == Stella.NIL) {
      return ("");
    }
    { int nqueries = queries.length();
      OutputStringStream script = OutputStringStream.newOutputStringStream();

      script.nativeStream.print("<SCRIPT LANGUAGE='JavaScript'>\n	      \nfunction makeArray (size) {\n  this.length = size;\n  return this;\n}\n\nvar queryModuleList = new makeArray(");
      script.nativeStream.print(nqueries + ");\nvar querySourceList = new makeArray(");
      {
        script.nativeStream.println(nqueries + ");");
        script.nativeStream.println();
      }
;
      { Cons entry = null;
        Cons iter000 = queries;
        int j = Stella.NULL_INTEGER;
        int iter001 = 1;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest, iter001 = iter001 + 1) {
          entry = ((Cons)(iter000.value));
          j = iter001;
          script.nativeStream.println("queryModuleList[" + j + "] = '" + ((StringWrapper)(entry.rest.value)).wrapperValue + "';");
          script.nativeStream.println("querySourceList[" + j + "] = '" + Stella.replaceSubstrings(Stella.replaceSubstrings(Stella.replaceSubstrings(Stella.replaceSubstrings(((StringWrapper)(entry.rest.rest.value)).wrapperValue, "\\\\", "\\"), "\\\"", Native.makeString(1, '"')), "\\n", Native.makeString(1, '\n')), "\\n", Native.makeString(1, '\r')) + "';");
        }
      }
      {
        script.nativeStream.println();
        script.nativeStream.println("function setSourceAndModule (index) {\n  if (index > 0) {\n    document.QUERY.QUERYSOURCE.value = querySourceList[index];\n    for (var i = 0; i < document.QUERY.MODULE.length; i++) {\n       if (document.QUERY.MODULE[i].value==queryModuleList[index]) {\n           document.QUERY.MODULE.selectedIndex = i; }\n    }\n  } else {\n  document.QUERY.QUERYSOURCE.value = '';\n  }\n}\n</SCRIPT>");
        script.nativeStream.println();
      }
;
      return (script.theStringReader());
    }
  }

  public static String yieldChoiceMenuString(Cons items, String selectoptions) {
    { OutputStringStream menu = OutputStringStream.newOutputStringStream();
      String optionitem = null;
      String menuitem = null;

      menu.nativeStream.println("<SELECT " + selectoptions + ">");
      { Stella_Object item = null;
        Cons iter000 = items;
        int i = Stella.NULL_INTEGER;
        int iter001 = 1;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest, iter001 = iter001 + 1) {
          item = iter000.value;
          i = iter001;
          { Surrogate testValue000 = Stella_Object.safePrimaryType(item);

            if (Surrogate.subtypeOfStringP(testValue000)) {
              { StringWrapper item000 = ((StringWrapper)(item));

                optionitem = item000.wrapperValue;
                menuitem = item000.wrapperValue;
              }
            }
            else if (testValue000 == OntosaurusUtil.SGT_STELLA_CONS) {
              { Cons item000 = ((Cons)(item));

                optionitem = ((StringWrapper)(item000.value)).wrapperValue;
                menuitem = ((StringWrapper)(item000.rest.value)).wrapperValue;
              }
            }
            else {
              { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

                stream000.nativeStream.print("`" + testValue000 + "' is not a valid case option");
                throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
              }
            }
          }
          menu.nativeStream.println("<OPTION VALUE='" + optionitem + "'" + (((i == 1) ? " SELECTED" : "")) + ">" + menuitem + "</OPTION>");
        }
      }
      menu.nativeStream.println("</SELECT>");
      return (menu.theStringReader());
    }
  }

  public static String yieldModuleMenuString(Cons modules) {
    if (modules == Stella.NIL) {
      return ("");
    }
    return (OntosaurusUtil.yieldChoiceMenuString(modules, "NAME='MODULE' onChange='document.cookie=\"theory=\" + this[this.selectedIndex].value + \";\";'"));
  }

  public static String yieldQueryMenuString(Cons queries) {
    if (queries == Stella.NIL) {
      return ("");
    }
    { Cons queryitems = Stella.NIL;

      { Cons entry = null;
        Cons iter000 = queries;
        Cons collect000 = null;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest) {
          entry = ((Cons)(iter000.value));
          if (collect000 == null) {
            {
              collect000 = Cons.cons(((StringWrapper)(entry.value)), Stella.NIL);
              if (queryitems == Stella.NIL) {
                queryitems = collect000;
              }
              else {
                Cons.addConsToEndOfConsList(queryitems, collect000);
              }
            }
          }
          else {
            {
              collect000.rest = Cons.cons(((StringWrapper)(entry.value)), Stella.NIL);
              collect000 = collect000.rest;
            }
          }
        }
      }
      queryitems = Cons.cons(Stella.getQuotedTree("((\"None\" \"----\") \"/ONTOSAURUS\")", "/ONTOSAURUS"), queryitems);
      return (OntosaurusUtil.yieldChoiceMenuString(queryitems, "NAME='QLIST' onChange='setSourceAndModule(this.selectedIndex)'"));
    }
  }

  public static String yieldNofAnswersMenuString(Cons nofanswers) {
    if (nofanswers == Stella.NIL) {
      return ("");
    }
    return (OntosaurusUtil.yieldChoiceMenuString(nofanswers, "NAME='NANSWERS'"));
  }

  public static String yieldTimeoutsMenuString(Cons timeouts) {
    if (timeouts == Stella.NIL) {
      return ("");
    }
    return (OntosaurusUtil.yieldChoiceMenuString(timeouts, "NAME='TIMEOUT'"));
  }

  public static void htmlWriteQueryFormPageFromTemplate(OutputStream stream, InputStream templatestream) {
    { KeyValueList variables = KeyValueList.newKeyValueList();
      String formheader = "<FORM NAME='QUERY' METHOD='POST' ACTION='do-query' ENCTYPE='application/www-url-form-encoded'>";

      variables.insertAt(StringWrapper.wrapString("MODULE-MENU"), StringWrapper.wrapString(OntosaurusUtil.yieldModuleMenuString(OntosaurusUtil.sortedContexts())));
      formheader = formheader + Stella.EOL_STRING + OntosaurusUtil.yieldPresetQueriesScript(((Cons)(OntosaurusUtil.$PRESET_QUERIES$.get())));
      variables.insertAt(StringWrapper.wrapString("QUERY-MENU"), StringWrapper.wrapString(OntosaurusUtil.yieldQueryMenuString(((Cons)(OntosaurusUtil.$PRESET_QUERIES$.get())))));
      variables.insertAt(StringWrapper.wrapString("NOF-ANSWERS-MENU"), StringWrapper.wrapString(OntosaurusUtil.yieldNofAnswersMenuString(Stella.getQuotedTree("((\"All\" \"1\" \"2\" \"5\" \"10\" \"20\" \"50\" \"100\") \"/ONTOSAURUS\")", "/ONTOSAURUS"))));
      variables.insertAt(StringWrapper.wrapString("TIMEOUTS-MENU"), StringWrapper.wrapString(OntosaurusUtil.yieldTimeoutsMenuString(Stella.getQuotedTree("((\"None\" \"1.0\" \"2.0\" \"5.0\" \"10.0\" \"30.0\" \"60.0\" \"120.0\") \"/ONTOSAURUS\")", "/ONTOSAURUS"))));
      variables.insertAt(StringWrapper.wrapString("QUERY-INPUT-AREA"), StringWrapper.wrapString("<TEXTAREA NAME='QUERYSOURCE' ROWS='4' COLS='80'></TEXTAREA>"));
      variables.insertAt(StringWrapper.wrapString("SUBMIT-BUTTON"), StringWrapper.wrapString("<INPUT TYPE='SUBMIT' VALUE='Submit'>"));
      variables.insertAt(StringWrapper.wrapString("RESET-BUTTON"), StringWrapper.wrapString("<INPUT TYPE='RESET' VALUE='Clear'>"));
      variables.insertAt(StringWrapper.wrapString("FORM-TRAILER"), StringWrapper.wrapString("</FORM>"));
      formheader = formheader + Stella.EOL_STRING + "<SCRIPT LANGUAGE='JavaScript'>\nvar cookieValue = document.cookie.substring(document.cookie.indexOf('qmodule=')+8,document.cookie.length);\nif (cookieValue.indexOf(';') != -1) {\ncookieValue = cookieValue.substring(0,cookieValue.indexOf(';'));\n}\nfor (var i = 0; i < document.QUERY.MODULE.length; i++) {\n   if (document.QUERY.MODULE[i].value==cookieValue) {\n     document.QUERY.MODULE.selectedIndex = i; }\n}</SCRIPT>";
      variables.insertAt(StringWrapper.wrapString("FORM-HEADER"), StringWrapper.wrapString(formheader));
      InputStream.substituteTemplateVariablesToStream(templatestream, stream, variables);
    }
  }

  public static void htmlExecuteQuery(KeyValueList querydata, edu.isi.stella.javalib.NativeOutputStream stream) {
    { String modulename = ((StringWrapper)(querydata.lookup(StringWrapper.wrapString("MODULE")))).wrapperValue;
      Module module = Logic.getModule(StringWrapper.wrapString(modulename));
      StringWrapper nvalueentry = ((StringWrapper)(querydata.lookup(StringWrapper.wrapString("NANSWERS"))));
      Stella_Object nvalueobject = ((nvalueentry != null) ? Stella.readSExpressionFromString(nvalueentry.wrapperValue) : ((Stella_Object)(null)));
      int nvalues = (Stella_Object.integerP(nvalueobject) ? ((IntegerWrapper)(nvalueobject)).wrapperValue : Stella.NULL_INTEGER);
      StringWrapper timeoutentry = ((StringWrapper)(querydata.lookup(StringWrapper.wrapString("TIMEOUT"))));
      Stella_Object timeoutobject = ((timeoutentry != null) ? Stella.readSExpressionFromString(timeoutentry.wrapperValue) : ((Stella_Object)(null)));
      double timeout = (Stella_Object.floatP(timeoutobject) ? ((FloatWrapper)(timeoutobject)).wrapperValue : Stella.NULL_FLOAT);
      Cons query = Stella.NIL;
      Cons options = Cons.list$(Cons.cons(OntosaurusUtil.KWD_SORT_BY, Cons.cons(OntosaurusUtil.KWD_VALUES, Cons.cons(Stella.NIL, Stella.NIL))));
      List variables = List.newList();

      if (module != null) {
        { Object old$Module$000 = Stella.$MODULE$.get();
          Object old$Context$000 = Stella.$CONTEXT$.get();

          try {
            Native.setSpecial(Stella.$MODULE$, module);
            Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
            query = ((Cons)(Stella.readSExpressionFromString(((StringWrapper)(querydata.lookup(StringWrapper.wrapString("QUERYSOURCE")))).wrapperValue)));
            Logic.collectUndeclaredVariables(query, Stella.NIL, variables);
            if (timeout != Stella.NULL_FLOAT) {
              options = options.concatenate(Cons.list$(Cons.cons(OntosaurusUtil.KWD_TIMEOUT, Cons.cons(FloatWrapper.wrapFloat(timeout), Cons.cons(Stella.NIL, Stella.NIL)))), Stella.NIL);
            }
            if (variables.emptyP()) {
              OntosaurusUtil.htmlExecuteAskQuery(query, options, module, stream);
            }
            else {
              OntosaurusUtil.htmlExecuteRetrieveQuery(nvalues, variables.theConsList, query, options, module, stream);
            }
            OntosaurusUtil.htmlLineBreak(stream);
            stream.println("<HR SIZE=2>");
            OntosaurusUtil.writePowerloomTrailer(stream);

          } finally {
            Stella.$CONTEXT$.set(old$Context$000);
            Stella.$MODULE$.set(old$Module$000);
          }
        }
      }
      else {
        OntosaurusUtil.htmlUnknownModuleResponse(OntosaurusUtil.KWD_QUERY, "", modulename, stream);
      }
    }
  }

  public static void htmlExecuteAskQuery(Cons query, Cons options, Module mod, edu.isi.stella.javalib.NativeOutputStream stream) {
    { TruthValue answer = edu.isi.powerloom.PLI.ask(Cons.cons(query, options), mod, null);

      if ((answer == Logic.TRUE_TRUTH_VALUE) ||
          (answer == Logic.DEFAULT_TRUE_TRUTH_VALUE)) {
        {
          stream.print("<FONT COLOR='#33FF66'>");
          stream.print("TRUE");
          stream.println("</FONT>");
        }
      }
      else if ((answer == Logic.FALSE_TRUTH_VALUE) ||
          (answer == Logic.DEFAULT_FALSE_TRUTH_VALUE)) {
        {
          stream.print("<FONT COLOR='#FF6633'>");
          stream.print("FALSE");
          stream.println("</FONT>");
        }
      }
      else {
        {
          stream.print("<FONT COLOR='#888888'>");
          stream.print("UNKNOWN");
          stream.println("</FONT>");
        }
      }
    }
  }

  public static void htmlExecuteRetrieveQuery(int nvalues, Cons variables, Cons query, Cons options, Module mod, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();

      try {
        Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
        { QueryIterator queryiterator = null;
          Cons solutions = Stella.NIL;

          { Object old$Module$000 = Stella.$MODULE$.get();
            Object old$Context$000 = Stella.$CONTEXT$.get();

            try {
              Native.setSpecial(Stella.$MODULE$, ((mod != null) ? mod : ((Module)(Stella.$MODULE$.get()))));
              Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
              synchronized (Logic.$POWERLOOM_LOCK$) {
                queryiterator = Logic.callRetrieve(Cons.cons(((nvalues > 0) ? ((Stella_Object)(IntegerWrapper.wrapInteger(nvalues))) : ((Stella_Object)(OntosaurusUtil.SYM_LOGIC_ALL))), Cons.cons(variables, Cons.cons(query, options.concatenate(Stella.NIL, Stella.NIL)))));
              }

            } finally {
              Stella.$CONTEXT$.set(old$Context$000);
              Stella.$MODULE$.set(old$Module$000);
            }
          }
          solutions = queryiterator.consifyCurrentSolutions();
          {
            stream.print("<HTML>");
            {
              stream.print("<HEAD>");
              stream.println("<BASE TARGET='content'>");
              {
                stream.print("<TITLE>");
                stream.print("Answer Page");
                stream.println("</TITLE>");
              }
              stream.println("</HEAD>");
            }
            { String tag011 = OntosaurusUtil.makeHtmlBodyTag(OntosaurusUtil.$ANSWER_BACKGROUND_COLOR$);

              stream.print("<" + tag011 + ">");
              if (queryiterator.timeoutP) {
                stream.println("The query timed out.<BR>");
              }
              if (solutions == Stella.NIL) {
                {
                  stream.print("<FONT COLOR='#CC3366'>");
                  {
                    stream.print("<I>");
                    stream.print("No Solutions");
                    stream.print("</I>");
                  }
                  stream.println("</FONT>");
                }
              }
              else {
                { Cons soln = null;
                  Cons iter000 = solutions;
                  int answercounter = Stella.NULL_INTEGER;
                  int iter001 = 1;

                  for (;!(iter000 == Stella.NIL); iter000 = iter000.rest, iter001 = iter001 + 1) {
                    soln = ((Cons)(iter000.value));
                    answercounter = iter001;
                    {
                      stream.print("<DL>");
                      {
                        stream.print("<DT>");
                        {
                          stream.print("<FONT COLOR='#999999'>");
                          stream.println("Solution " + answercounter + ":");
                          OntosaurusUtil.writeExplanationIcon(queryiterator, soln, stream);
                          stream.print("</FONT>");
                        }
                        stream.println("</DT>");
                      }
                      { Stella_Object binding = null;
                        Cons iter002 = soln;
                        Stella_Object var = null;
                        Cons iter003 = variables;

                        for (;(!(iter002 == Stella.NIL)) &&
                                  (!(iter003 == Stella.NIL)); iter002 = iter002.rest, iter003 = iter003.rest) {
                          binding = iter002.value;
                          var = iter003.value;
                          {
                            stream.print("<DD>");
                            stream.print(var + " = ");
                            if (Surrogate.subtypeOfP(Stella_Object.safePrimaryType(binding), OntosaurusUtil.SGT_LOGIC_LOGIC_OBJECT)) {
                              { LogicObject binding000 = ((LogicObject)(binding));

                                OntosaurusUtil.htmlWriteHref(stream, "show", "concept", binding000);
                              }
                            }
                            else {
                              stream.print(binding);
                            }
                            stream.println("</DD>");
                          }
                        }
                      }
                      stream.println("</DL>");
                    }
                  }
                }
              }
              stream.println("</" + Native.string_subsequence(tag011, 0, Native.string_position(tag011, ' ', 0)) + ">");
            }
            stream.println("</HTML>");
          }
        }

      } finally {
        Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
      }
    }
  }

  public static void writeExplanationIcon(QueryIterator query, Cons bindings, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Module module = query.queryContext.baseModule;
      Description description = query.baseControlFrame.patternRecord.description;
      Vector existsvars = description.internalVariables;
      Stella_Object proposition = null;
      KeyValueMap mapping = KeyValueMap.newKeyValueMap();

      { Stella_Object binding = null;
        Cons iter000 = bindings;
        PatternVariable var = null;
        Vector vector000 = description.ioVariables;
        int index000 = 0;
        int length000 = vector000.length();

        for (;(!(iter000 == Stella.NIL)) &&
                  (index000 < length000); iter000 = iter000.rest, index000 = index000 + 1) {
          binding = iter000.value;
          var = ((PatternVariable)((vector000.theArray)[index000]));
          mapping.insertAt(var, binding);
        }
      }
      { PatternVariable var = null;
        Vector vector001 = existsvars;
        int index001 = 0;
        int length001 = vector001.length();

        for (;index001 < length001; index001 = index001 + 1) {
          var = ((PatternVariable)((vector001.theArray)[index001]));
          mapping.insertAt(var, var);
        }
      }
      proposition = Proposition.generateProposition(Proposition.copyProposition(description.proposition, mapping));
      if (existsvars.nonEmptyP()) {
        proposition = Cons.list$(Cons.cons(OntosaurusUtil.SYM_STELLA_EXISTS, Cons.cons(Logic.generateVariables(existsvars, false), Cons.cons(Cons.cons(proposition, Stella.NIL), Stella.NIL))));
      }
      OntosaurusUtil.htmlWriteHrefInDetail(stream, null, "explain", "query", module.name(), Native.stringify(proposition), "<IMG SRC='/ploom/icons/button-question.gif' ALT='Explain result' BORDER='0' WIDTH='14' HEIGHT='15' /></A>", true);
    }
  }

  public static void htmlWriteExplanationResponsePage(String modulename, String query, edu.isi.stella.javalib.NativeOutputStream stream) {
    { Module module = Stella.getStellaModule(modulename, false);

      if (module == null) {
        OntosaurusUtil.htmlUnknownModuleResponse(OntosaurusUtil.KWD_RELATION, query, modulename, stream);
        return;
      }
      { Object old$Module$000 = Stella.$MODULE$.get();
        Object old$Context$000 = Stella.$CONTEXT$.get();

        try {
          Native.setSpecial(Stella.$MODULE$, ((module != null) ? module : ((Module)(Stella.$MODULE$.get()))));
          Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
          synchronized (Logic.$POWERLOOM_LOCK$) {
            { Object old$RecordJustificationsP$000 = Logic.$RECORD_JUSTIFICATIONSp$.get();

              try {
                Native.setBooleanSpecial(Logic.$RECORD_JUSTIFICATIONSp$, true);
                { QueryIterator queryiterator = Logic.createAskQuery(Cons.cons(Stella.readSExpressionFromString(query), Stella.NIL));
                  OutputStringStream explanation = OutputStringStream.newOutputStringStream();
                  Justification justification = null;

                  Logic.callAsk(queryiterator);
                  justification = ((Justification)(KeyValueList.dynamicSlotValue(queryiterator.baseControlFrame.dynamicSlots, OntosaurusUtil.SYM_LOGIC_JUSTIFICATION, null)));
                  { Object old$ExplanationFormat$000 = Logic.$EXPLANATION_FORMAT$.get();
                    Object old$ExplanationAudience$000 = Logic.$EXPLANATION_AUDIENCE$.get();
                    Object old$LogicDialect$000 = Logic.$LOGIC_DIALECT$.get();

                    try {
                      Native.setSpecial(Logic.$EXPLANATION_FORMAT$, OntosaurusUtil.KWD_HTML);
                      Native.setSpecial(Logic.$EXPLANATION_AUDIENCE$, OntosaurusUtil.KWD_LAY);
                      Native.setSpecial(Logic.$LOGIC_DIALECT$, OntosaurusUtil.KWD_KIF_ONTOSAURUS);
                      Justification.printExplanation(justification, explanation, null, 4, ((Keyword)(Logic.$EXPLANATION_AUDIENCE$.get())));

                    } finally {
                      Logic.$LOGIC_DIALECT$.set(old$LogicDialect$000);
                      Logic.$EXPLANATION_AUDIENCE$.set(old$ExplanationAudience$000);
                      Logic.$EXPLANATION_FORMAT$.set(old$ExplanationFormat$000);
                    }
                  }
                  { String tag012 = OntosaurusUtil.makeHtmlBodyTag("FFFFFF");

                    stream.print("<" + tag012 + ">");
                    stream.println(explanation.theStringReader());
                    stream.println("</" + Native.string_subsequence(tag012, 0, Native.string_position(tag012, ' ', 0)) + ">");
                  }
                }

              } finally {
                Logic.$RECORD_JUSTIFICATIONSp$.set(old$RecordJustificationsP$000);
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

  public static void ploomQueryHandler(edu.isi.webtools.http.HttpExchange xchg) {
    { edu.isi.stella.javalib.NativeOutputStream stream = edu.isi.webtools.http.HttpExchange.getReplyStream(xchg);
      Keyword method = edu.isi.webtools.http.HttpExchange.getRequestMethod(xchg);

      if (method == OntosaurusUtil.KWD_GET) {
        OntosaurusUtil.htmlWriteQueryFormPage(stream);
      }
      else if (method == OntosaurusUtil.KWD_POST) {
        try {
          { String body = edu.isi.webtools.http.HttpExchange.getRequestBody(xchg);
            KeyValueList values = edu.isi.webtools.http.Http.parseAndDecodeFormValues(body);

            OntosaurusUtil.htmlExecuteQuery(values, stream);
          }
        } catch (LogicException e) {
          edu.isi.webtools.http.HttpExchange.generateErrorResponse(xchg, OntosaurusUtil.KWD_BAD_REQUEST, Stella.exceptionMessage(e));
        } catch (java.lang.Exception e) {
          edu.isi.webtools.http.HttpExchange.generateErrorResponse(xchg, OntosaurusUtil.KWD_INTERNAL_ERROR, Stella.exceptionMessage(e));
        }
      }
      else {
        { String message000 = null;

          { Object old$PrintreadablyP$000 = Stella.$PRINTREADABLYp$.get();

            try {
              Native.setBooleanSpecial(Stella.$PRINTREADABLYp$, true);
              message000 = "Unhandled request method: " + "`" + Native.stringify(method) + "'";

            } finally {
              Stella.$PRINTREADABLYp$.set(old$PrintreadablyP$000);
            }
          }
          edu.isi.webtools.http.HttpExchange.generateErrorResponse(xchg, OntosaurusUtil.KWD_BAD_REQUEST, message000);
        }
      }
    }
  }

  public static String vizGetObjectName(Stella_Object renamed_Object) {
    if (renamed_Object == null) {
      return (OntosaurusUtil.VIZ_UNKNOWN);
    }
    { String name = Logic.objectNameString(renamed_Object);

      if (name == null) {
        name = Native.stringify(renamed_Object);
      }
      return (name);
    }
  }

  public static String vizDotString(String name) {
    { StringBuffer buffer = Stella.makeRawMutableString(name.length() * 2);
      int i = -1;
      boolean solP = false;

      { char renamed_Char = Stella.NULL_CHARACTER;
        String vector000 = name;
        int index000 = 0;
        int length000 = vector000.length();

        for (;index000 < length000; index000 = index000 + 1) {
          renamed_Char = vector000.charAt(index000);
          switch (renamed_Char) {
            case ' ': 
              if (solP) {
                edu.isi.stella.javalib.Native.mutableString_nthSetter(buffer, '.', (i = i + 1));
              }
              else {
                edu.isi.stella.javalib.Native.mutableString_nthSetter(buffer, renamed_Char, (i = i + 1));
              }
            break;
            case '\n': 
            case '\r': 
              edu.isi.stella.javalib.Native.mutableString_nthSetter(buffer, '\\', (i = i + 1));
              edu.isi.stella.javalib.Native.mutableString_nthSetter(buffer, 'l', (i = i + 1));
              solP = true;
            break;
            case '"': 
            case '{': 
            case '}': 
            case '|': 
            case '<': 
            case '>': 
            case '\\': 
              edu.isi.stella.javalib.Native.mutableString_nthSetter(buffer, '\\', (i = i + 1));
              edu.isi.stella.javalib.Native.mutableString_nthSetter(buffer, renamed_Char, (i = i + 1));
              solP = false;
            break;
            default:
              edu.isi.stella.javalib.Native.mutableString_nthSetter(buffer, renamed_Char, (i = i + 1));
              solP = false;
            break;
          }
        }
      }
      return (Native.mutableString_subsequence(buffer, 0, i + 1));
    }
  }

  public static String vizDotObjectName(Stella_Object renamed_Object) {
    return (OntosaurusUtil.vizDotString(OntosaurusUtil.vizGetObjectName(renamed_Object)));
  }

  public static void vizExportModuleToFile(Module module, String file) {
    { OutputFileStream out = null;

      try {
        out = Stella.openOutputFile(file, Stella.NIL);
        { Object old$Module$000 = Stella.$MODULE$.get();
          Object old$Context$000 = Stella.$CONTEXT$.get();

          try {
            Native.setSpecial(Stella.$MODULE$, module);
            Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
            { VizInfo self000 = VizInfo.newVizInfo();

              self000.showRelationsP = true;
              self000.stream = out;
              { VizInfo info = self000;

                info.vizExportHeader();
                info.vizExportModule(module);
                info.vizExportTrailer();
              }
            }

          } finally {
            Stella.$CONTEXT$.set(old$Context$000);
            Stella.$MODULE$.set(old$Module$000);
          }
        }

      } finally {
        if (out != null) {
          out.free();
        }
      }
    }
  }

  public static void vizExportConceptToFile(LogicObject concept, Module module, String file) {
    { OutputFileStream out = null;

      try {
        out = Stella.openOutputFile(file, Stella.NIL);
        { Object old$Module$000 = Stella.$MODULE$.get();
          Object old$Context$000 = Stella.$CONTEXT$.get();

          try {
            Native.setSpecial(Stella.$MODULE$, module);
            Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
            { VizInfo self000 = VizInfo.newVizInfo();

              self000.showRelationsP = true;
              self000.showAttributesP = true;
              self000.showRulesP = true;
              self000.stream = out;
              { VizInfo info = self000;

                info.vizExportHeader();
                info.vizExportConceptTree(concept, module);
                info.vizExportTrailer();
              }
            }

          } finally {
            Stella.$CONTEXT$.set(old$Context$000);
            Stella.$MODULE$.set(old$Module$000);
          }
        }

      } finally {
        if (out != null) {
          out.free();
        }
      }
    }
  }

  public static boolean vizServerAvailableP() {
    return (OntosaurusUtil.$VIZ_SERVER_ENABLEDp$);
  }

  public static void vizServerExportModule(Module module, OutputStream out) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, module);
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        { VizInfo self000 = VizInfo.newVizInfo();

          self000.showRelationsP = true;
          self000.stream = out;
          { VizInfo info = self000;

            info.vizExportHeader();
            info.vizExportModule(module);
            info.vizExportTrailer();
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  public static void vizServerExportConcept(LogicObject concept, Module module, OutputStream out) {
    { Object old$Module$000 = Stella.$MODULE$.get();
      Object old$Context$000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, module);
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        { VizInfo self000 = VizInfo.newVizInfo();

          self000.showRelationsP = true;
          self000.stream = out;
          { VizInfo info = self000;

            info.vizExportHeader();
            info.vizExportConceptTree(concept, module);
            info.vizExportTrailer();
          }
        }

      } finally {
        Stella.$CONTEXT$.set(old$Context$000);
        Stella.$MODULE$.set(old$Module$000);
      }
    }
  }

  public static String vizServerExportObject(Stella_Object renamed_Object, Module module) {
    { MemoizationTable memoTable000 = null;
      Cons memoizedEntry000 = null;
      Stella_Object memoizedValue000 = null;

      if (Stella.$MEMOIZATION_ENABLEDp$) {
        memoTable000 = ((MemoizationTable)(OntosaurusUtil.SGT_ONTOSAURUS_F_VIZ_SERVER_EXPORT_OBJECT_MEMO_TABLE_000.surrogateValue));
        if (memoTable000 == null) {
          Surrogate.initializeMemoizationTable(OntosaurusUtil.SGT_ONTOSAURUS_F_VIZ_SERVER_EXPORT_OBJECT_MEMO_TABLE_000, "(:MAX-VALUES 20 :TIMESTAMPS (:META-KB-UPDATE))");
          memoTable000 = ((MemoizationTable)(OntosaurusUtil.SGT_ONTOSAURUS_F_VIZ_SERVER_EXPORT_OBJECT_MEMO_TABLE_000.surrogateValue));
        }
        memoizedEntry000 = MruMemoizationTable.lookupMruMemoizedValue(((MruMemoizationTable)(memoTable000)), renamed_Object, module, Stella.MEMOIZED_NULL_VALUE, null, 2);
        memoizedValue000 = memoizedEntry000.value;
      }
      if (memoizedValue000 != null) {
        if (memoizedValue000 == Stella.MEMOIZED_NULL_VALUE) {
          memoizedValue000 = null;
        }
      }
      else {
        memoizedValue000 = StringWrapper.wrapString(OntosaurusUtil.helpVizServerExportObject(renamed_Object, module));
        if (Stella.$MEMOIZATION_ENABLEDp$) {
          memoizedEntry000.value = ((memoizedValue000 == null) ? Stella.MEMOIZED_NULL_VALUE : memoizedValue000);
        }
      }
      { StringWrapper value000 = ((StringWrapper)(memoizedValue000));

        return (value000.wrapperValue);
      }
    }
  }

  public static String helpVizServerExportObject(Stella_Object renamed_Object, Module module) {
    { OutputStringStream dotout = OutputStringStream.newOutputStringStream();

      if (Stella_Object.isaP(renamed_Object, OntosaurusUtil.SGT_STELLA_MODULE)) {
        OntosaurusUtil.vizServerExportModule(((Module)(renamed_Object)), dotout);
      }
      else {
        OntosaurusUtil.vizServerExportConcept(((LogicObject)(renamed_Object)), module, dotout);
      }
      return (dotout.theStringReader());
    }
  }

  public static void vizServerHandler(edu.isi.webtools.http.HttpExchange xchg) {
    if (!(OntosaurusUtil.vizServerAvailableP())) {
      edu.isi.webtools.http.HttpExchange.generateErrorResponse(xchg, OntosaurusUtil.KWD_NOT_IMPLEMENTED, "Graphing not supported, program `" + OntosaurusUtil.$VIZ_DOT_PROGRAM$ + "' not found");
      return;
    }
    { Cons keys = edu.isi.webtools.http.Http.parseAndDecodeUrlArguments(edu.isi.webtools.http.HttpExchange.getRequestUriQuery(xchg), '+');

      if (keys.length() < 4) {
        OntosaurusUtil.doActionHandler(xchg);
      }
      { StringWrapper action = ((StringWrapper)(keys.value));
        StringWrapper objecttype = ((StringWrapper)(keys.rest.value));
        StringWrapper modulename = ((StringWrapper)(keys.rest.rest.value));
        StringWrapper objectname = ((StringWrapper)(keys.fourth()));
        edu.isi.stella.javalib.NativeOutputStream stream = edu.isi.webtools.http.HttpExchange.getReplyStream(xchg);
        Module module = edu.isi.powerloom.PLI.getModule(modulename.wrapperValue, null);
        Stella_Object visualizedobject = null;
        boolean generatemapP = OntosaurusUtil.$VIZ_SERVER_IMAGE_MAPS_ENABLEDp$ &&
            Stella_Object.eqlToStringP(action, "graph");

        if (module == null) {
          OntosaurusUtil.htmlUnknownObjectResponse(OntosaurusUtil.KWD_CONTEXT, modulename.wrapperValue, stream);
          return;
        }
        { String testValue000 = objecttype.wrapperValue;

          if (Stella.stringEqlP(testValue000, "context")) {
            visualizedobject = module;
          }
          else if (Stella.stringEqlP(testValue000, "relation") ||
              Stella.stringEqlP(testValue000, "concept")) {
            visualizedobject = edu.isi.powerloom.PLI.getRelation(objectname.wrapperValue, module, null);
          }
          else {
            edu.isi.webtools.http.HttpExchange.generateErrorResponse(xchg, OntosaurusUtil.KWD_BAD_REQUEST, "Malformed URL, graph of type `" + objecttype.wrapperValue + "' is not supported.");
            return;
          }
        }
        if (visualizedobject == null) {
          OntosaurusUtil.htmlUnknownObjectResponse(((module == null) ? OntosaurusUtil.KWD_CONTEXT : OntosaurusUtil.KWD_RELATION), ((module == null) ? modulename.wrapperValue : objectname.wrapperValue), stream);
          return;
        }
        if (generatemapP) {
          OntosaurusUtil.vizServerServeImagePlusMap(xchg, visualizedobject, module);
        }
        else {
          OntosaurusUtil.vizServerServeImage(xchg, visualizedobject, module);
        }
      }
    }
  }

  public static void vizServerServeImage(edu.isi.webtools.http.HttpExchange xchg, Stella_Object renamed_Object, Module module) {
    { edu.isi.stella.javalib.NativeOutputStream stream = edu.isi.webtools.http.HttpExchange.getReplyStream(xchg);
      String dotcommands = OntosaurusUtil.vizServerExportObject(renamed_Object, module);
      int dotexit = 0;

      if (Stella.blankStringP(dotcommands)) {
        edu.isi.webtools.http.HttpExchange.generateErrorResponse(xchg, OntosaurusUtil.KWD_BAD_REQUEST, "Nothing to graph");
        return;
      }
      edu.isi.webtools.http.HttpExchange.setReplyHeaderValue(xchg, OntosaurusUtil.KWD_CONTENT_TYPE, edu.isi.webtools.http.Http.getHttpMimeType(OntosaurusUtil.KWD_IMAGE_GIF, null));
      { OutputStream self001 = OutputStream.newOutputStream();

        self001.nativeStream = stream;
        dotexit = OntosaurusUtil.executeShellCommand(Cons.cons(StringWrapper.wrapString(OntosaurusUtil.$VIZ_DOT_PROGRAM$), Cons.cons(StringWrapper.wrapString("-Tgif"), Stella.NIL)), ".", InputStringStream.newInputStringStream(dotcommands), self001, null);
      }
      if (!(dotexit == 0)) {
        edu.isi.webtools.http.HttpExchange.generateErrorResponse(xchg, OntosaurusUtil.KWD_INTERNAL_ERROR, "Problem running `dot'");
        return;
      }
    }
  }

  public static void vizServerServeImagePlusMap(edu.isi.webtools.http.HttpExchange xchg, Stella_Object renamed_Object, Module module) {
    { String uri = Stella.unescapeUrlString(edu.isi.webtools.http.HttpExchange.getRequestUri(xchg));
      edu.isi.stella.javalib.NativeOutputStream stream = edu.isi.webtools.http.HttpExchange.getReplyStream(xchg);
      String dotcommands = OntosaurusUtil.vizServerExportObject(renamed_Object, module);
      String imagemap = null;

      if (Stella.blankStringP(dotcommands)) {
        edu.isi.webtools.http.HttpExchange.generateErrorResponse(xchg, OntosaurusUtil.KWD_BAD_REQUEST, "Nothing to graph");
        return;
      }
      try {
        imagemap = OntosaurusUtil.shellCommand(Cons.cons(StringWrapper.wrapString(OntosaurusUtil.$VIZ_DOT_PROGRAM$), Cons.cons(StringWrapper.wrapString("-Tcmap"), Stella.NIL)), Cons.cons(OntosaurusUtil.KWD_INPUT, Cons.cons(StringWrapper.wrapString(dotcommands), Stella.NIL))).wrapperValue;
      } catch (StellaException e) {
        edu.isi.webtools.http.HttpExchange.generateErrorResponse(xchg, OntosaurusUtil.KWD_INTERNAL_ERROR, Stella.exceptionMessage(e));
        return;
      }
      edu.isi.webtools.http.HttpExchange.setReplyHeaderValue(xchg, OntosaurusUtil.KWD_CONTENT_TYPE, edu.isi.webtools.http.Http.getHttpMimeType(OntosaurusUtil.KWD_HTML, null));
      {
        stream.print("<HTML>");
        {
          stream.print("<HEAD>");
          stream.println("<TITLE>PowerLoom Graph</TITLE>");
          stream.println("<BASE TARGET='content'>");
          stream.println("</HEAD>");
        }
        {
          stream.print("<BODY>");
          {
            stream.print("<MAP NAME='ontomap'>");
            stream.print(imagemap);
            stream.println("</MAP>");
          }
          stream.println("<IMG SRC='" + Stella.replaceSubstrings(uri, "/do-action?graph-bare+", "/do-action?graph+") + "' border='1' usemap='#ontomap'>");
          stream.println("</BODY>");
        }
        stream.println("</HTML>");
      }
    }
  }

  public static String[] parseShellCommand(Stella_Object command) {
    { Cons parsedcommand = Stella.NIL;
      String[] result = null;

      { Surrogate testValue000 = Stella_Object.safePrimaryType(command);

        if (testValue000 == OntosaurusUtil.SGT_STELLA_CONS) {
          { Cons command000 = ((Cons)(command));

            parsedcommand = command000;
          }
        }
        else if (Surrogate.subtypeOfStringP(testValue000)) {
          { StringWrapper command000 = ((StringWrapper)(command));

            parsedcommand = Stella.splitString(command000.wrapperValue, ' ');
          }
        }
        else {
          { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

            stream000.nativeStream.print("parse-shell-command: illegal shell command format: `" + command + "'");
            throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
          }
        }
      }
      if (false) {
        parsedcommand = Cons.cons(((StringWrapper)(parsedcommand.value)), parsedcommand);
      }
      result = new String[parsedcommand.length()];
      { StringWrapper elt = null;
        Cons iter000 = parsedcommand;
        int i = Stella.NULL_INTEGER;
        int iter001 = 0;

        for (;!(iter000 == Stella.NIL); iter000 = iter000.rest, iter001 = iter001 + 1) {
          elt = ((StringWrapper)(iter000.value));
          i = iter001;
          result[i] = elt.wrapperValue;
        }
      }
      return (result);
    }
  }

  /** Run <code>command</code> in a shell and return its exit status.  If <code>directory</code> is
   * non-NULL, run it in that directory; if <code>input</code> is defined, feed <code>command</code>s standard input
   * from that stream; if <code>output</code> and/or <code>error</code> are defined, copy <code>commands</code> standard output/
   * error to those streams.  It is the responsibility of the caller to close the supplied
   * streams (if any) and do any shell error handling based on exit status or error output.
   * @param command
   * @param directory
   * @param input
   * @param output
   * @param error
   * @return int
   */
  public static int executeShellCommand(Stella_Object command, String directory, InputStream input, OutputStream output, OutputStream error) {
    { ShellProcess self000 = ShellProcess.newShellProcess();

      self000.command = OntosaurusUtil.parseShellCommand(command);
      self000.directory = ((directory != null) ? directory : ".");
      self000.inputStream = input;
      self000.outputStream = output;
      self000.errorStream = error;
      { ShellProcess process = self000;

        process.startProcess();
        { Thread outputthread = ((output != null) ? Thread.newThread(Native.find_java_method("edu.isi.stella.InputStream", "copyStreamToStream", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.InputStream"), Native.find_java_class("edu.isi.stella.OutputStream")}), Stella.vector(Cons.cons(process.nativeStdout, Cons.cons(process.outputStream, Stella.NIL)))) : ((Thread)(null)));
          Thread errorthread = ((error != null) ? Thread.newThread(Native.find_java_method("edu.isi.stella.InputStream", "copyStreamToStream", new java.lang.Class [] {Native.find_java_class("edu.isi.stella.InputStream"), Native.find_java_class("edu.isi.stella.OutputStream")}), Stella.vector(Cons.cons(process.nativeStderr, Cons.cons(process.errorStream, Stella.NIL)))) : ((Thread)(null)));

          if (outputthread != null) {
            outputthread.startThread();
          }
          if (errorthread != null) {
            errorthread.startThread();
          }
          if (input != null) {
            InputStream.copyStreamToStream(input, process.nativeStdin);
            Stream.closeStream(process.nativeStdin);
          }
          if (outputthread != null) {
            outputthread.waitForCompletion();
          }
          if (errorthread != null) {
            errorthread.waitForCompletion();
          }
          process.waitForCompletion();
          process.destroyProcess();
          return (process.exitStatus);
        }
      }
    }
  }

  /** User-level command interface to <code>executeShellCommand</code> (which see).
   * Runs <code>command</code> and returns its output (if any) as a string.  If the shell created
   * a non-zero exit status or generated any error output, an exception will be raised
   * - unless :ignore-errors? is true (which is the default).
   * If <code>command</code> was a string, split it at spaces to determine its arguments (this is
   * not sophisticated and does not handle quoting correctly).  For more complex commands,
   * supply them as a list of strings representing the program and its arguments.  If any
   * shell-level operations such as redirection are needed, use the <code>shCCmd</code> idiom.
   * If :input is supplied as a non-null string, feed it to <code>command</code>s standard input.
   * If :directory is given, execute <code>command</code> in that directory.
   * @param command
   * @param options
   * @return StringWrapper
   */
  public static StringWrapper shellCommand(Stella_Object command, Cons options) {
    if (((Boolean)(OntosaurusUtil.$BLOCK_SHELL_COMMANDp$.get())).booleanValue()) {
      throw ((StellaException)(StellaException.newStellaException("Execution of `shell-command' is blocked in this context").fillInStackTrace()));
    }
    { PropertyList theoptions = Logic.parseLogicCommandOptions(options, Cons.list$(Cons.cons(OntosaurusUtil.KWD_DIRECTORY, Cons.cons(OntosaurusUtil.SGT_STELLA_STRING, Cons.cons(OntosaurusUtil.KWD_INPUT, Cons.cons(OntosaurusUtil.SGT_STELLA_STRING, Cons.cons(OntosaurusUtil.KWD_IGNORE_ERRORSp, Cons.cons(OntosaurusUtil.SGT_STELLA_BOOLEAN, Cons.cons(Stella.NIL, Stella.NIL)))))))), true, false);
      String directory = StringWrapper.unwrapString(((StringWrapper)(theoptions.lookup(OntosaurusUtil.KWD_DIRECTORY))));
      String inputstring = StringWrapper.unwrapString(((StringWrapper)(theoptions.lookup(OntosaurusUtil.KWD_INPUT))));
      int exit = 0;
      String output = null;
      String error = null;
      Stella_Object ignoreerrorsP = theoptions.lookupWithDefault(OntosaurusUtil.KWD_IGNORE_ERRORSp, Stella.TRUE_WRAPPER);

      if (directory != null) {
        directory = Stella.translateLogicalPathname(directory);
      }
      { InputStringStream inputstream = ((!Stella.blankStringP(inputstring)) ? InputStringStream.newInputStringStream(inputstring) : ((InputStringStream)(null)));
        OutputStringStream outputstream = OutputStringStream.newOutputStringStream();
        OutputStringStream errorstream = OutputStringStream.newOutputStringStream();

        exit = OntosaurusUtil.executeShellCommand(command, directory, inputstream, outputstream, errorstream);
        output = outputstream.theStringReader();
        error = errorstream.theStringReader();
        if (inputstream != null) {
          Stream.closeStream(inputstream);
        }
        Stream.closeStream(outputstream);
        Stream.closeStream(errorstream);
      }
      if (!Stella.blankStringP(error)) {
        if (BooleanWrapper.coerceWrappedBooleanToBoolean(((BooleanWrapper)(ignoreerrorsP)))) {
          Stella.STANDARD_OUTPUT.nativeStream.print(error);
        }
        else {
          { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

            stream000.nativeStream.print("shell-command: `" + error + "'");
            throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
          }
        }
      }
      if ((!(exit == 0)) &&
          (!BooleanWrapper.coerceWrappedBooleanToBoolean(((BooleanWrapper)(ignoreerrorsP))))) {
        { OutputStringStream stream001 = OutputStringStream.newOutputStringStream();

          stream001.nativeStream.print("shell-command: non-zero exit status=`" + exit + "'");
          throw ((StellaException)(StellaException.newStellaException(stream001.theStringReader()).fillInStackTrace()));
        }
      }
      if (Stella.blankStringP(output)) {
        return (null);
      }
      else {
        return (StringWrapper.wrapString(output));
      }
    }
  }

  public static StringWrapper shellCommandEvaluatorWrapper(Cons arguments) {
    return (OntosaurusUtil.shellCommand(arguments.value, arguments.rest));
  }

}
