//  -*- Mode: Java -*-
//
// BufferedString.java

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
| The Original Code is the STELLA Programming Language.                      |
|                                                                            |
| The Initial Developer of the Original Code is                              |
| UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          |
| 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               |
|                                                                            |
| Portions created by the Initial Developer are Copyright (C) 1996-2023      |
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

package edu.isi.stella;

import edu.isi.stella.javalib.*;

public class BufferedString extends StandardObject {
    public StringBuffer buffer;
    public int bufferSize;
    public int fillPointer;

  public static BufferedString newBufferedString() {
    { BufferedString self = null;

      self = new BufferedString();
      self.fillPointer = 0;
      self.bufferSize = 16;
      self.buffer = Stella.makeRawMutableString(16);
      return (self);
    }
  }

  /** Return a substring of <code>string</code> beginning at position <code>start</code>
   * and ending up to but not including position <code>end</code>, counting from zero.  An
   * <code>end</code> value of NULL stands for the rest of the string.
   * @param start
   * @param end
   * @return String
   */
  public String subsequence(int start, int end) {
    { BufferedString self = this;

      if (end == Stella.NULL_INTEGER) {
        end = self.fillPointer;
      }
      return (Native.mutableString_subsequence(self.buffer, start, end));
    }
  }

  /** Return a substring of <code>string</code> beginning at position <code>start</code>
   * and ending up to but not including position <code>end</code>, counting from zero.  An
   * <code>end</code> value of NULL stands for the rest of the string.
   * @return String
   */
  public String theString() {
    { BufferedString self = this;

      return (Native.mutableString_subsequence(self.buffer, 0, self.fillPointer));
    }
  }

  /** Clear <code>self</code> by setting its active length to zero.
   */
  public void clear() {
    { BufferedString self = this;

      self.fillPointer = 0;
    }
  }

  public BufferedString copy() {
    { BufferedString self = this;

      { BufferedString self000 = BufferedString.newBufferedString();

        self000.bufferSize = self.bufferSize;
        self000.fillPointer = self.fillPointer;
        { BufferedString copy = self000;

          copy.buffer = new StringBuffer((Native.mutableString_subsequence(self.buffer, 0, Stella.NULL_INTEGER)));
          return (copy);
        }
      }
    }
  }

  public char pop() {
    { BufferedString self = this;

      { int bufcursor = self.fillPointer;

        if (bufcursor > 0) {
          bufcursor = bufcursor - 1;
          self.fillPointer = bufcursor;
          return ((self.buffer).charAt(bufcursor));
        }
        else {
          return (Stella.NULL_CHARACTER);
        }
      }
    }
  }

  /** Append <code>renamed_Char</code> to the END of the string <code>self</code>.  
   * Resize the buffer if necessary.
   * @param renamed_Char
   */
  public void appendCharacter(char renamed_Char) {
    { BufferedString self = this;

      { int bufsize = self.bufferSize;
        int bufcursor = self.fillPointer;
        StringBuffer buffer = self.buffer;

        if (bufcursor >= bufsize) {
          buffer = self.resizeBuffer(Stella.integer_max(bufsize, 1) * 2);
        }
        edu.isi.stella.javalib.Native.mutableString_nthSetter(buffer, renamed_Char, bufcursor);
        self.fillPointer = bufcursor + 1;
      }
    }
  }

  /** Append <code>value</code> to the END of the string <code>self</code>.  
   * Resize the buffer if necessary.
   * @param value
   */
  public void appendString(String value) {
    { BufferedString self = this;

      { int vallength = value.length();
        int valcursor = 0;
        int bufsize = self.bufferSize;
        int bufcursor = self.fillPointer;
        StringBuffer buffer = self.buffer;

        if ((bufcursor + vallength) > bufsize) {
          buffer = self.resizeBuffer(Stella.integer_max(bufsize * 2, bufcursor + vallength));
        }
        while (valcursor < vallength) {
          edu.isi.stella.javalib.Native.mutableString_nthSetter(buffer, (value.charAt(valcursor)), bufcursor);
          valcursor = valcursor + 1;
          bufcursor = bufcursor + 1;
        }
        self.fillPointer = bufcursor;
      }
    }
  }

  public char lastSetter(char value) {
    { BufferedString self = this;

      return (edu.isi.stella.javalib.Native.mutableString_nthSetter((self.buffer), value, (self.fillPointer - 1)));
    }
  }

  /** Return the last character in <code>self</code>.
   * @return char
   */
  public char last() {
    { BufferedString self = this;

      return ((self.buffer).charAt((self.fillPointer - 1)));
    }
  }

  /** Set the character in <code>self</code> at <code>position</code> to <code>ch</code>.
   * @param ch
   * @param position
   * @return char
   */
  public char nthSetter(char ch, int position) {
    { BufferedString self = this;

      return (edu.isi.stella.javalib.Native.mutableString_nthSetter((self.buffer), ch, position));
    }
  }

  /** Return the character in <code>self</code> at <code>position</code>.
   * @param position
   * @return char
   */
  public char nth(int position) {
    { BufferedString self = this;

      return ((self.buffer).charAt(position));
    }
  }

  /** Return <code>true</code> if <code>self</code> has length &gt; 0.
   * @return boolean
   */
  public boolean nonEmptyP() {
    { BufferedString self = this;

      return (self.fillPointer > 0);
    }
  }

  /** Return <code>true</code> if <code>self</code> has length 0.
   * @return boolean
   */
  public boolean emptyP() {
    { BufferedString self = this;

      return (self.fillPointer == 0);
    }
  }

  /** Reset the length of <code>self</code> to <code>newlength</code>.  Fill in NULL characters if <code>newlength</code> 
   * is greater than the current length.  This is the safe way to reset the fill pointer.
   * @param newlength
   * @return int
   */
  public int lengthSetter(int newlength) {
    { BufferedString self = this;

      { int fp = self.fillPointer;

        if (newlength < 0) {
          { OutputStringStream stream000 = OutputStringStream.newOutputStringStream();

            stream000.nativeStream.print("Out-of-bounds: cannot set string buffer to negative length: `" + newlength + "'");
            throw ((StellaException)(StellaException.newStellaException(stream000.theStringReader()).fillInStackTrace()));
          }
        }
        else if (newlength < fp) {
          self.fillPointer = newlength;
        }
        else if (newlength > fp) {
          self.ensureFreeSpace(newlength - fp);
          { StringBuffer buf = self.buffer;

            while (fp < newlength) {
              edu.isi.stella.javalib.Native.mutableString_nthSetter(buf, Stella.NULL_CHARACTER, fp);
              fp = fp + 1;
            }
            self.fillPointer = newlength;
          }
        }
        return (newlength);
      }
    }
  }

  public int length() {
    { BufferedString self = this;

      return (self.fillPointer);
    }
  }

  /** Return the amount of free space in <code>self</code>.
   * @return int
   */
  public int freeSpace() {
    { BufferedString self = this;

      return (self.bufferSize - self.fillPointer);
    }
  }

  /** Ensure <code>self</code> is big enough to accommodate an additional item of <code>size</code>.
   * @param size
   * @return StringBuffer
   */
  public StringBuffer ensureFreeSpace(int size) {
    { BufferedString self = this;

      if ((self.fillPointer + size) > self.bufferSize) {
        return (self.resizeBuffer(Stella.integer_max(self.bufferSize * 2, self.fillPointer + size)));
      }
      else {
        return (self.buffer);
      }
    }
  }

  /** Change the size of <code>self</code> to <code>size</code>.  If <code>size</code> is smaller
   * than the current size of <code>self</code>, it's buffer will be truncated.
   * @param size
   * @return StringBuffer
   */
  public StringBuffer resizeBuffer(int size) {
    { BufferedString self = this;

      { int oldsize = self.bufferSize;
        StringBuffer oldbuffer = self.buffer;
        StringBuffer newbuffer = oldbuffer;

        if (oldsize == 0) {
          newbuffer = Stella.makeRawMutableString(size);
          self.buffer = newbuffer;
          self.bufferSize = size;
        }
        else if (size == oldsize) {
        }
        else {
          { int l = self.fillPointer;

            newbuffer = Stella.makeRawMutableString(size);
            self.buffer = newbuffer;
            self.bufferSize = size;
            if (size < l) {
              l = size;
              self.fillPointer = l;
            }
            while (l > 0) {
              l = l - 1;
              edu.isi.stella.javalib.Native.mutableString_nthSetter(newbuffer, (oldbuffer.charAt(l)), l);
            }
          }
        }
        return (newbuffer);
      }
    }
  }

  public static Stella_Object accessBufferedStringSlotValue(BufferedString self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == Stella.SYM_STELLA_BUFFER) {
      if (setvalueP) {
        self.buffer = ((MutableStringWrapper)(value)).wrapperValue;
      }
      else {
        value = MutableStringWrapper.wrapMutableString(self.buffer);
      }
    }
    else if (slotname == Stella.SYM_STELLA_BUFFER_SIZE) {
      if (setvalueP) {
        self.bufferSize = ((IntegerWrapper)(value)).wrapperValue;
      }
      else {
        value = IntegerWrapper.wrapInteger(self.bufferSize);
      }
    }
    else if (slotname == Stella.SYM_STELLA_FILL_POINTER) {
      if (setvalueP) {
        self.fillPointer = ((IntegerWrapper)(value)).wrapperValue;
      }
      else {
        value = IntegerWrapper.wrapInteger(self.fillPointer);
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
    { BufferedString self = this;

      return (Stella.SGT_STELLA_BUFFERED_STRING);
    }
  }

}

