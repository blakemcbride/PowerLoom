//  -*- Mode: Java -*-
//
// Tomcat.java

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
 | Portions created by the Initial Developer are Copyright (C) 2003-2023      |
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

package edu.isi.webtools.http.tomcat;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.stella.*;
import edu.isi.webtools.http.*;

public class Tomcat {
  public static Surrogate SGT_TOMCAT_HTTP_SERVER_TOMCAT = null;

  public static Keyword KWD_OK = null;

  public static Surrogate SGT_TOMCAT_HTTP_EXCHANGE_TOMCAT = null;

  public static Symbol SYM_TOMCAT_RESPONSE_CODE = null;

  public static Symbol SYM_TOMCAT_HANDLER_OPTIONS = null;

  public static Keyword KWD_BLOCK = null;

  public static Surrogate SGT_STELLA_PROPERTY_LIST = null;

  public static Keyword KWD_PATH = null;

  public static Keyword KWD_HANDLER_TYPE = null;

  public static Keyword KWD_ERROR = null;

  public static Keyword KWD_HANDLER = null;

  public static Keyword KWD_FILE = null;

  public static Keyword KWD_DIRECTORY = null;

  public static Keyword KWD_CONTENT_TYPE = null;

  public static Keyword KWD_HTML = null;

  public static Symbol SYM_TOMCAT_STARTUP_HTTP_SERVER_IMPL = null;

  public static Symbol SYM_STELLA_METHOD_STARTUP_CLASSNAME = null;

  public static Symbol SYM_TOMCAT_STARTUP_WEBTOOLS_TOMCAT_SYSTEM = null;

}
