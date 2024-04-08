//  -*- Mode: Java -*-
//
// nameToLookup.java

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
+---------------------------- END LICENSE BLOCK -----------------------------+
*/

package edu.isi.webtools.examples.addressexample;

import edu.isi.stella.javalib.Native;
import edu.isi.stella.javalib.StellaSpecialVariable;
import edu.isi.webtools.objects.xml_objects.*;
import edu.isi.stella.*;

public class nameToLookup extends XMLObject {
    public String type;

  public static nameToLookup new_nameToLookup() {
    { nameToLookup self = null;

      self = new nameToLookup();
      self.cdataContent = null;
      self.textContent = null;
      self.type = null;
      return (self);
    }
  }

  public static getAddressFromNameResponse getAddressFromName(nameToLookup name) {
    { String theName = name.textContent;

      { areaCode SELF_000 = areaCode.new_areaCode();

        SELF_000.textContent = "789";
        { areaCode areaCode = SELF_000;

          { exchange SELF_001 = exchange.new_exchange();

            SELF_001.textContent = "654";
            { exchange exchange = SELF_001;

              { number SELF_002 = number.new_number();

                SELF_002.textContent = "3210";
                { number number = SELF_002;

                  { phoneNumber SELF_003 = phoneNumber.new_phoneNumber();

                    SELF_003.areaCode = areaCode;
                    SELF_003.exchange = exchange;
                    SELF_003.number = number;
                    { phoneNumber phone = SELF_003;

                      { streetNum SELF_004 = streetNum.new_streetNum();

                        SELF_004.textContent = "919";
                        { streetNum streetNum = SELF_004;

                          { streetName SELF_005 = streetName.new_streetName();

                            SELF_005.textContent = "Street for " + theName;
                            { streetName streetName = SELF_005;

                              { city SELF_006 = city.new_city();

                                SELF_006.textContent = "Sunnytown";
                                { city city = SELF_006;

                                  { state SELF_007 = state.new_state();

                                    SELF_007.textContent = "UT";
                                    { state state = SELF_007;

                                      { zip SELF_008 = zip.new_zip();

                                        SELF_008.textContent = "43434";
                                        { zip zip = SELF_008;

                                          { Stella_return SELF_009 = Stella_return.new_return();

                                            SELF_009.streetNum = streetNum;
                                            SELF_009.streetName = streetName;
                                            SELF_009.city = city;
                                            SELF_009.state = state;
                                            SELF_009.zip = zip;
                                            SELF_009.phone = phone;
                                            { Stella_return renamed_Return = SELF_009;

                                              { getAddressFromNameResponse SELF_010 = getAddressFromNameResponse.new_getAddressFromNameResponse();

                                                SELF_010.renamed_Return = renamed_Return;
                                                { getAddressFromNameResponse result = SELF_010;

                                                  return (result);
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }

  public static Stella_Object access_nameToLookup_Slot_Value(nameToLookup self, Symbol slotname, Stella_Object value, boolean setvalueP) {
    if (slotname == AddressExample.SYM_XSI_type) {
      if (setvalueP) {
        self.type = ((StringWrapper)(value)).wrapperValue;
      }
      else {
        value = StringWrapper.wrapString(self.type);
      }
    }
    else {
      { OutputStringStream STREAM_000 = OutputStringStream.newOutputStringStream();

        STREAM_000.nativeStream.print("`" + slotname + "' is not a valid case option");
        throw ((StellaException)(StellaException.newStellaException(STREAM_000.theStringReader()).fillInStackTrace()));
      }
    }
    return (value);
  }

  public Surrogate primaryType() {
    { nameToLookup self = this;

      return (AddressExample.SGT_ADDRESS_EXAMPLE_nameToLookup);
    }
  }

}

