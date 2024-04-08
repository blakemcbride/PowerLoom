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
| Portions created by the Initial Developer are Copyright (C) 2005-2006      |
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
import edu.stanford.smi.protege.model.*;
import edu.stanford.smi.protege.util.*;

/**
 * Various utilities to support Protege/PowerLoom translation.
 */

public class Util {

  public static Reader getReader(String filename) {
    Reader reader = null;
    if (filename != null) {
      try {
	reader = new BufferedReader(new InputStreamReader(new FileInputStream(new File(filename))), 8096);
      } catch (IOException e) {
	// should we do something here?
      }
    }
    return reader;
  }

  public static Writer getWriter(String filename) {
    Writer writer = null;
    if (filename != null) {
      try {
	writer = new BufferedWriter(new OutputStreamWriter(new FileOutputStream(new File(filename))), 8096);
      } catch (IOException e) {
	// should we do something here?
      }
    }
    return writer;
  }

  public static String getPowerLoomName(Frame frame, boolean nativeOnly) {
    // Return the PowerLoom name to use for the Protege object `frame'
    //    (could be a class, slot or instance).
    // If `nativeOnly', then translate system names to native PowerLoom
    //    names.
    String name = frame.getName();
    String module = "";
    //if (name.charAt(0) == ':')
    //    name = name.substring(1);
    //if (frame.isSystem())
    //    module = getProtegeSystemModule() + "/";
    //return module + nameToPowerLoomName(name);
	
    // Handle internal Protege to PowerLoom mappings:
    if (nativeOnly) {
      if (name.equals(":STANDARD-CLASS") ||
	  name.equals(":CLASS") ||
	  name.equals(":META-CLASS")) {
	return "CONCEPT";
      } else if (name.equals(":STANDARD-SLOT") ||
		 name.equals(":SLOT") ||
		 name.equals(":RELATION") ||
		 name.equals(":DIRECTED-BINARY-RELATION")) {
	return "BINARY-RELATION";
      } else if (name.equals(":SYSTEM-CLASS") ||
		 name.equals(":FACET") ||
		 name.equals(":STANDARD-FACET") ||
		 name.equals(":CONSTRAINT") ||
		 name.equals(":PAL-CONSTRAINT") ||
		 name.equals(":ANNOTATION") ||
		 name.equals(":INSTANCE-ANNOTATION")) {
	return "THING";
      }
    }

    return nameToPowerLoomName(name);
  }

  public static String nameToPowerLoomName (String name) {
    // Translate the Protege name `name' into a PowerLoom symbol with
    // appropriate quoting, escaping, case preservation, etc.
    // this is too simplistic but should do for now:
    return "|" + name + "|";
  }

  static String valueToPowerLoomObject (ValueType valueType, Object value, boolean nativeOnly) {
    // Translate `value' into an appropriate PowerLoom object.
    // Currently ignores `valueType'.
    // If a Frame, then respect `nativeOnly' in name translation.
    if (value == null)
      return "NULL";
    else if (value instanceof Frame)  // Cls, Slot or Instance
      return getPowerLoomName((Frame)value, nativeOnly);
    else if (value instanceof Number) // float, integer
      return value.toString();
    else if (value instanceof String) 
      return "\"" + escapeString(value.toString()) + "\"";
    else // BOOLEAN, SYMBOL
      // not sure whether this does the right thing for symbols:
      return value.toString();
  }

  static String escapeString (String str) {
    // Escape any special charactes in `str' and return the result.
    if ((str.indexOf('"') == -1) &&
	(str.indexOf('\\') == -1))
      return str;
    else {
      int length = str.length();
      StringBuffer buffer = new StringBuffer();
      char ch;
      for (int i = 0; i < length; i++) {
	ch = str.charAt(i);
	switch (ch) {
	case '"': buffer.append("\\\"");
	  break;
	case '\\': buffer.append("\\\\");
	  break;
	default:
	  buffer.append(ch);
	}
      }
      return buffer.toString();
    }
  }

  public static String getProtegeSystemModule () {
    // Return the name of the PowerLoom module used to define various
    // Protege system classes such as THING, DIRECTED-BINARY-RELATION, etc.
    return "PROTEGE-SYSTEM";
  }

  public static String getPowerLoomFileHeader () {
    return ";;; -*- Mode: Lisp; Syntax: Common-Lisp; Package: STELLA; Base: 10. -*-"
      + "\n\n(IN-PACKAGE \"STELLA\")";
  }

  public static void printCollection(Writer stream, Collection coll, String separator) {
    for (Iterator i = coll.iterator(); i.hasNext(); ) {
      Util.print(stream, i.next().toString());
      if (i.hasNext()) Util.print(stream, separator);
    }
  }

  public static void printPowerLoomCollection(Writer stream, Collection coll, 
					      String separator, boolean nativeOnly) {
    for (Iterator i = coll.iterator(); i.hasNext(); ) {
      Util.print(stream, valueToPowerLoomObject(ValueType.ANY, i.next(), nativeOnly));
      if (i.hasNext()) {
	Util.print(stream, separator);
      }
    }
  }

  public static void print(Writer stream, String text) {
    // write `text' onto `stream' ignoring any exceptions.
    try {
      stream.write(text);
    }
    // ignore `write' excpetions, should we care?
    catch (IOException e) {}
  }

  public static void println(Writer stream, String text) {
    // write `text' and a terminating newline onto `stream' ignoring any exceptions.
    try {
      stream.write(text);
      stream.write("\n");
    }
    // ignore `write' excpetions, should we care?
    catch (IOException e) {}
  }
}
