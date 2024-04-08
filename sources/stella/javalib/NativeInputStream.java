// -*- Mode: Java -*-

/*--------------------------- BEGIN LICENSE BLOCK ---------------------------+
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
| The Original Code is the STELLA Programming Language.                      |
|                                                                            |
| The Initial Developer of the Original Code is                              |
| UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
| 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
|                                                                            |
| Portions created by the Initial Developer are Copyright (C) 1996-2019      |
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
+---------------------------- END LICENSE BLOCK ----------------------------*/

// Version: $Id$

// PushbackInputStream that uses the ISO-8859-1 encoding for byte-to-char transparency.


package edu.isi.stella.javalib;

import edu.isi.stella.InputOutputException;
import java.io.*;

// TO DO:
// - clean up the reader/writer mess (see Native.java log and NativeOutputStream
//   for more on that story).  In general this is in better shape than on the output
//   side but still not perfect
// - figure out how using (buffered) readers interacts with position inquiry and setting
// - this doesn't have to extend from `PushbackInputStream' anymore since we are going
//   through the mark/reset mechanism, it can extend from BufferedInputStream for example.

public class NativeInputStream extends PushbackInputStream {

    public BufferedReader reader;

    public NativeInputStream (InputStream in) {
        // Create a NativeInputStream for `in'.
        super(in);
    }

    public static NativeInputStream create (InputStream in) {
        // Static convenience constructor that mirrors what we need for NativeOutputStream.
        return new NativeInputStream(in);
    }

    public BufferedReader getReader () {
        // Access the ISO-8859-1 charset reader for this stream or created if it doesn't yet exist.
        if (reader == null)
            reader =  new BufferedReader(new InputStreamReader(this, edu.isi.stella.Stella.STELLA_CHARSET));
        return reader;
    }

    public void setReader (BufferedReader rdr) {
        // Set the reader for this stream.
        reader = rdr;
    }

    public void clear () {
        // Clear any buffered input from the reader and/or stream (there doesn't seem to be
        // any analogue to `flush' for input streams).
        try {
            if (reader != null) {
                BufferedReader rdr = reader;
                reader = null;
                while (rdr.ready()) {
                    rdr.read();
                }
                reader = rdr;
            }
            else
                read(new byte[available()]);
        }
        catch (IOException e) {
            throw (InputOutputException)InputOutputException.newInputOutputException("NativeInputStream.clear: " + e.getMessage()).fillInStackTrace();
        }
    }
}
