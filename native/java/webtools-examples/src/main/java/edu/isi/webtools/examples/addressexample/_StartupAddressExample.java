//  -*- Mode: Java -*-
//
// _StartupAddressExample.java

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

public class _StartupAddressExample {
  static void HELP_STARTUP_ADDRESS_EXAMPLE1() {
    {
      AddressExample.SGT_ADDRESS_EXAMPLE_getAddressFromName = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("getAddressFromName", null, 1)));
      AddressExample.SYM_ADDRESS_EXAMPLE_nameElement = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("nameElement", null, 0)));
      AddressExample.SGT_ADDRESS_EXAMPLE_return = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("return", null, 1)));
      AddressExample.SYM_ADDRESS_EXAMPLE_streetNum = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("streetNum", null, 0)));
      AddressExample.SYM_ADDRESS_EXAMPLE_streetName = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("streetName", null, 0)));
      AddressExample.SYM_ADDRESS_EXAMPLE_city = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("city", null, 0)));
      AddressExample.SYM_ADDRESS_EXAMPLE_state = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("state", null, 0)));
      AddressExample.SYM_ADDRESS_EXAMPLE_zip = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("zip", null, 0)));
      AddressExample.SYM_ADDRESS_EXAMPLE_phone = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("phone", null, 0)));
      AddressExample.SYM_XSI_type = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("type", Stella.getStellaModule("/STELLA/XML-OBJECTS/XSI", true), 0)));
      AddressExample.SGT_ADDRESS_EXAMPLE_getAddressFromNameResponse = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("getAddressFromNameResponse", null, 1)));
      AddressExample.SYM_ADDRESS_EXAMPLE_return = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("return", null, 0)));
      AddressExample.SGT_ADDRESS_EXAMPLE_nameToLookup = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("nameToLookup", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_Address = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("Address", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_StreetNum = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("StreetNum", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_StreetName = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("StreetName", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_City = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("City", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_State = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("State", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_Zip = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("Zip", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_PhoneNumber = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("PhoneNumber", null, 1)));
      AddressExample.SYM_ADDRESS_EXAMPLE_areaCode = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("areaCode", null, 0)));
      AddressExample.SYM_ADDRESS_EXAMPLE_exchange = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("exchange", null, 0)));
      AddressExample.SYM_ADDRESS_EXAMPLE_number = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("number", null, 0)));
      AddressExample.SGT_ADDRESS_EXAMPLE_AreaCode = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("AreaCode", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_Exchange = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("Exchange", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_Number = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("Number", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_streetNum = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("streetNum", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_streetName = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("streetName", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_city = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("city", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_state = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("state", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_zip = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("zip", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_phoneNumber = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("phoneNumber", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_areaCode = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("areaCode", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_exchange = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("exchange", null, 1)));
      AddressExample.SGT_ADDRESS_EXAMPLE_number = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("number", null, 1)));
      AddressExample.KWD_METHOD = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("METHOD", null, 2)));
      AddressExample.KWD_POST = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("POST", null, 2)));
      AddressExample.KWD_CONTENT = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("CONTENT", null, 2)));
      AddressExample.KWD_HEADERS = ((Keyword)(GeneralizedSymbol.internRigidSymbolWrtModule("HEADERS", null, 2)));
      AddressExample.SGT_SOAP_ENV_Fault = ((Surrogate)(GeneralizedSymbol.internRigidSymbolWrtModule("Fault", Stella.getStellaModule("/STELLA/XML-OBJECTS/SOAP-ENV", true), 1)));
      AddressExample.SYM_ADDRESS_EXAMPLE_STARTUP_ADDRESS_EXAMPLE = ((Symbol)(GeneralizedSymbol.internRigidSymbolWrtModule("STARTUP-ADDRESS-EXAMPLE", null, 0)));
    }
  }

  public static void STARTUP_ADDRESS_EXAMPLE() {
    { Object OLD_$MODULE$_000 = Stella.$MODULE$.get();
      Object OLD_$CONTEXT$_000 = Stella.$CONTEXT$.get();

      try {
        Native.setSpecial(Stella.$MODULE$, Stella.getStellaModule("/STELLA/XML-OBJECTS/ADDRESS-EXAMPLE", Stella.$STARTUP_TIME_PHASE$ > 1));
        Native.setSpecial(Stella.$CONTEXT$, ((Module)(Stella.$MODULE$.get())));
        if (Stella.currentStartupTimePhaseP(2)) {
          _StartupAddressExample.HELP_STARTUP_ADDRESS_EXAMPLE1();
        }
        if (Stella.currentStartupTimePhaseP(5)) {
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("getAddressFromName", "(DEFCLASS getAddressFromName (XMLObject) :PUBLIC-SLOTS ((nameElement :TYPE nameToLookup)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.getAddressFromName", "new_getAddressFromName", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.getAddressFromName", "access_getAddressFromName_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.getAddressFromName"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("return", "(DEFCLASS return (XMLObject) :PUBLIC-SLOTS ((streetNum :TYPE streetNum) (streetName :TYPE streetName) (city :TYPE city) (state :TYPE state) (zip :TYPE zip) (phone :TYPE phoneNumber) (/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"ADDRESS-DEMO:address\")))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.Stella_return", "new_return", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.Stella_return", "access_return_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.Stella_return"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("getAddressFromNameResponse", "(DEFCLASS getAddressFromNameResponse (XMLObject) :PUBLIC-SLOTS ((return :TYPE /STELLA/XML-OBJECTS/ADDRESS-DEMO/return)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.getAddressFromNameResponse", "new_getAddressFromNameResponse", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.getAddressFromNameResponse", "access_getAddressFromNameResponse_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.getAddressFromNameResponse"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("nameToLookup", "(DEFCLASS nameToLookup (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.nameToLookup", "new_nameToLookup", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.nameToLookup", "access_nameToLookup_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.nameToLookup"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("Address", "(DEFCLASS Address (XMLObject) :PUBLIC-SLOTS ((streetNum :TYPE StreetNum) (streetName :TYPE StreetName) (city :TYPE City) (state :TYPE State) (zip :TYPE Zip) (phone :TYPE PhoneNumber)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.Address", "new_Address", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.Address", "access_Address_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.Address"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("StreetNum", "(DEFCLASS StreetNum (XMLObject))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.StreetNum", "new_StreetNum", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("StreetName", "(DEFCLASS StreetName (XMLObject))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.StreetName", "new_StreetName", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("City", "(DEFCLASS City (XMLObject))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.City", "new_City", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("State", "(DEFCLASS State (XMLObject))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.State", "new_State", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("Zip", "(DEFCLASS Zip (XMLObject))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.Zip", "new_Zip", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("PhoneNumber", "(DEFCLASS PhoneNumber (XMLObject) :PUBLIC-SLOTS ((areaCode :TYPE AreaCode) (exchange :TYPE Exchange) (number :TYPE Number)))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.PhoneNumber", "new_PhoneNumber", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.PhoneNumber", "access_PhoneNumber_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.PhoneNumber"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("AreaCode", "(DEFCLASS AreaCode (XMLObject))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.AreaCode", "new_AreaCode", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("Exchange", "(DEFCLASS Exchange (XMLObject))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.Exchange", "new_Exchange", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("Number", "(DEFCLASS Number (XMLObject))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.Number", "new_Number", new java.lang.Class [] {});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("streetNum", "(DEFCLASS streetNum (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:int\")))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.streetNum", "new_streetNum", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.streetNum", "access_streetNum_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.streetNum"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("streetName", "(DEFCLASS streetName (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:string\")))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.streetName", "new_streetName", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.streetName", "access_streetName_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.streetName"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("city", "(DEFCLASS city (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:string\")))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.city", "new_city", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.city", "access_city_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.city"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("state", "(DEFCLASS state (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:string\")))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.state", "new_state", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.state", "access_state_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.state"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("zip", "(DEFCLASS zip (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:int\")))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.zip", "new_zip", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.zip", "access_zip_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.zip"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("phoneNumber", "(DEFCLASS phoneNumber (XMLObject) :PUBLIC-SLOTS ((areaCode :TYPE areaCode) (exchange :TYPE exchange) (number :TYPE number) (/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"ADDRESS-DEMO:phone\")))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.phoneNumber", "new_phoneNumber", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.phoneNumber", "access_phoneNumber_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.phoneNumber"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("areaCode", "(DEFCLASS areaCode (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:int\")))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.areaCode", "new_areaCode", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.areaCode", "access_areaCode_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.areaCode"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("exchange", "(DEFCLASS exchange (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:string\")))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.exchange", "new_exchange", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.exchange", "access_exchange_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.exchange"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
          { Stella_Class renamed_Class = Stella.defineClassFromStringifiedSource("number", "(DEFCLASS number (XMLObject) :PUBLIC-SLOTS ((/STELLA/XML-OBJECTS/XSI/type :TYPE STRING :INITIALLY \"XSD:string\")))");

            renamed_Class.classConstructorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.number", "new_number", new java.lang.Class [] {});
            renamed_Class.classSlotAccessorCode = Native.find_java_method("edu.isi.webtools.examples.addressexample.number", "access_number_Slot_Value", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.number"), Native.find_java_class("edu.isi.stella.Symbol"), Native.find_java_class("edu.isi.stella.Stella_Object"), java.lang.Boolean.TYPE});
          }
        }
        if (Stella.currentStartupTimePhaseP(6)) {
          Stella.finalizeClasses();
        }
        if (Stella.currentStartupTimePhaseP(7)) {
          Stella.defineFunctionObject("getAddressFromName", "(DEFUN (getAddressFromName getAddressFromNameResponse) ((name nameToLookup)))", Native.find_java_method("edu.isi.webtools.examples.addressexample.nameToLookup", "getAddressFromName", new java.lang.Class [] {Native.find_java_class("edu.isi.webtools.examples.addressexample.nameToLookup")}), null);
          Stella.defineFunctionObject("MAKE-REQUEST-OBJECT1", "(DEFUN (MAKE-REQUEST-OBJECT1 getAddressFromName) ())", Native.find_java_method("edu.isi.webtools.examples.addressexample.AddressExample", "MAKE_REQUEST_OBJECT1", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("ADDRESS-TEST1", "(DEFUN ADDRESS-TEST1 ())", Native.find_java_method("edu.isi.webtools.examples.addressexample.AddressExample", "ADDRESS_TEST1", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("ADDRESS-TEST2", "(DEFUN ADDRESS-TEST2 ())", Native.find_java_method("edu.isi.webtools.examples.addressexample.AddressExample", "ADDRESS_TEST2", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("GET-APACHE-RESPONSE1", "(DEFUN GET-APACHE-RESPONSE1 ())", Native.find_java_method("edu.isi.webtools.examples.addressexample.AddressExample", "GET_APACHE_RESPONSE1", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("GET-APACHE-RESPONSE2", "(DEFUN GET-APACHE-RESPONSE2 ())", Native.find_java_method("edu.isi.webtools.examples.addressexample.AddressExample", "GET_APACHE_RESPONSE2", new java.lang.Class [] {}), null);
          Stella.defineFunctionObject("STARTUP-ADDRESS-EXAMPLE", "(DEFUN STARTUP-ADDRESS-EXAMPLE () :PUBLIC? TRUE)", Native.find_java_method("edu.isi.webtools.examples.addressexample._StartupAddressExample", "STARTUP_ADDRESS_EXAMPLE", new java.lang.Class [] {}), null);
          { MethodSlot function = Symbol.lookupFunction(AddressExample.SYM_ADDRESS_EXAMPLE_STARTUP_ADDRESS_EXAMPLE);

            KeyValueList.setDynamicSlotValue(function.dynamicSlots, edu.isi.webtools.examples.sample.Sample.SYM_STELLA_METHOD_STARTUP_CLASSNAME, StringWrapper.wrapString("_StartupAddressExample"), Stella.NULL_STRING_WRAPPER);
          }
        }
        if (Stella.currentStartupTimePhaseP(8)) {
          Stella.finalizeSlots();
          Stella.cleanupUnfinalizedClasses();
        }
        if (Stella.currentStartupTimePhaseP(9)) {
          Stella_Object.inModule(((StringWrapper)(Stella_Object.copyConsTree(StringWrapper.wrapString("ADDRESS-EXAMPLE")))));
          XmlObjects.$NAMESPACE_PREFIX_URI_TABLE$.insertAt(StringWrapper.wrapString("ADDRESS-EXAMPLE"), StringWrapper.wrapString("urn:AddressFetcher"));
          XmlObjects.$NAMESPACE_URI_PREFIX_TABLE$.insertAt(StringWrapper.wrapString("urn:AddressFetcher"), StringWrapper.wrapString("ADDRESS-EXAMPLE"));
          XmlObjects.$INVISIBLE_NAMESPACES_ON_OUTPUT$ = Cons.cons(StringWrapper.wrapString("ADDRESS-EXAMPLE"), XmlObjects.$INVISIBLE_NAMESPACES_ON_OUTPUT$);
          Stella.defineGlobalVariableObject("(DEFGLOBAL *ADDRESS-REQUEST* STRING \"<?xml version='1.0' encoding='UTF-8'?>\n<SOAP-ENV:Envelope xmlns:SOAP-ENV=\\\"http://schemas.xmlsoap.org/soap/envelope/\\\" xmlns:xsi=\\\"http://www.w3.org/2001/XMLSchema-instance\\\" xmlns:xsd=\\\"http://www.w3.org/2001/XMLSchema\\\">\n<SOAP-ENV:Body>\n<ns1:getAddressFromName xmlns:ns1=\\\"urn:AddressFetcher\\\" SOAP-ENV:encodingStyle=\\\"http://schemas.xmlsoap.org/soap/encoding/\\\">\n<ns1:nameToLookup xsi:type=\\\"xsd:string\\\">John B. Good</ns1:nameToLookup>\n</ns1:getAddressFromName>\n</SOAP-ENV:Body>\n</SOAP-ENV:Envelope>\n\")", null);
        }

      } finally {
        Stella.$CONTEXT$.set(OLD_$CONTEXT$_000);
        Stella.$MODULE$.set(OLD_$MODULE$_000);
      }
    }
  }

}
