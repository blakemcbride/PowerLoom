//  -*- Mode: C++ -*-

// unit-defs.cc

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
| Portions created by the Initial Developer are Copyright (C) 2001-2023      |
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

#include "utilities/utilities-system.hh"

namespace stella_utilities {
  using namespace stella;

void initializeUnitDefinitions() {
  // Measure conversion factors.  The ultimate source for the
  // conversions are the following publications.  NIST was normally followed
  // unless a more precise value was found in MfM.
  // 
  // Sources:
  // [NIST]
  //   Guide for the Use of the International System of Units (SI)
  //   U.S. Department of Commerce
  //   National Institute of Standards and Technology (NIST)
  //   NIST Special Publication 811, 1995 Edition
  //   http://physics.nist.gov/Document/sp811.pdf
  // 
  // [MfM]
  //   Richard A. Young and Thomas J. Glover
  //   Measure for Measure
  //   1996.  ISBN 1-889796-00-X
  //   (Blue Willow, Inc.; Littleton, Colorado, USA)
  //   http://www.bluewillow.com/
  // 
  { Measure* m = NULL;

    m = defineBaseMeasure("Mass", "kg");
    m->addUnit("g", 0.001, "kg");
    m->addUnit("mg", 0.001, "g");
    m->addUnit("ug", 1.0e-6, "g");
    m->addUnit("ng", 1.0e-9, "g");
    m->addUnit("pg", 1.0e-12, "g");
    m->addUnit("d", 1.7e-24, "g");
    m->addUnit("dalton", 1.0, "d");
    m->addUnit("kd", 1000.0, "d");
    m->addUnit("lbs", 0.45359237, "kg");
    m->addUnit("oz", 0.0625, "lbs");
    m->addUnit("gr", 1.4285714285714287e-4, "lbs");
    m->addUnit("lb", 1.0, "lbs");
    m->addUnit("mton", 1000000.0, "g");
    m->addUnit("tonne", 1000000.0, "g");
    m->addUnit("ton", 2000.0, "lbs");
    m->addUnit("longton", 2240.0, "lbs");
    m->addUnit("stone", 14.0, "lbs");
    m->addUnit("hwt", 100.0, "lbs");
    m->addUnit("slug", 14594.14842519685, "g");
    m->addUnit("carat", 0.2, "g");
    m = defineBaseMeasure("Distance", "m");
    m->addUnit("nm", 1.0e-9, "m");
    m->addUnit("um", 1.0e-6, "m");
    m->addUnit("mm", 0.001, "m");
    m->addUnit("cm", 0.01, "m");
    m->addUnit("dm", 0.1, "m");
    m->addUnit("km", 1000.0, "m");
    m->addUnit("angstrom", 1.0e-10, "m");
    m->addUnit("ang", 1.0, "angstrom");
    m->addUnit("in", 0.0254, "m");
    m->addUnit("ft", 12.0, "in");
    m->addUnit("yd", 3.0, "ft");
    m->addUnit("mile", 5280.0, "ft");
    m->addUnit("miles", 1.0, "mile");
    m->addUnit("mi", 1.0, "mile");
    m->addUnit("NM", 1852.0, "m");
    m->addUnit("nautmi", 1852.0, "m");
    m->addUnit("fathom", 6.0, "ft");
    m->addUnit("furlong", 220.0, "yd");
    m->addUnit("hand", 4.0, "in");
    m->addUnit("hh", 1.0, "hand");
    m->addUnit("pica", 0.16666666666666666, "in");
    m->addUnit("point", 0.013888888888888888, "in");
    m->addUnit("pt", 1.0, "point");
    m->addUnit("AU", 1.4959787066000003e+11, "m");
    m->addUnit("lightyear", 9.460528177426822e+15, "m");
    m->addUnit("LY", 1.0, "lightyear");
    m->addUnit("parsec", 3.085678e+16, "m");
    m = defineDerivedMeasure("Area", "m2", "m2");
    m->addUnit("sqyd", 1.0, "yd2");
    m->addUnit("sqft", 1.0, "ft2");
    m->addUnit("sqin", 1.0, "in2");
    m->addUnit("sqkm", 1.0, "km2");
    m->addUnit("sqmile", 1.0, "mile2");
    m->addUnit("hectare", 10000.0, "m2");
    m->addUnit("ha", 1.0, "hectare");
    m->addUnit("are", 100.0, "m2");
    m->addUnit("a", 1.0, "are");
    m->addUnit("acre", 4840.0, "yd2");
    m = defineDerivedMeasure("Volume", "m3", "m3");
    m->addUnit("liter", 0.001, "m3");
    m->addUnit("l", 1.0, "liter");
    m->addUnit("L", 1.0, "liter");
    m->addUnit("ml", 0.001, "liter");
    m->addUnit("ul", 1.0e-6, "liter");
    m->addUnit("nl", 1.0e-9, "liter");
    m->addUnit("pl", 1.0e-12, "liter");
    m->addUnit("cc", 1.0, "ml");
    m->addUnit("cl", 0.01, "liter");
    m->addUnit("dl", 0.1, "liter");
    m->addUnit("Hl", 100.0, "liter");
    m->addUnit("cuft", 1.0, "ft3");
    m->addUnit("cuyd", 1.0, "yd3");
    m->addUnit("acrefeet", 1.0, "acre.ft");
    m->addUnit("gallon", 231.0, "in3");
    m->addUnit("pint", 0.125, "gallon");
    m->addUnit("quart", 0.25, "gallon");
    m->addUnit("gal", 1.0, "gallon");
    m->addUnit("qt", 1.0, "quart");
    m->addUnit("floz", 0.0625, "pint");
    m->addUnit("barrel", 42.0, "gal");
    m->addUnit("cup", 0.5, "pint");
    m->addUnit("tbl", 0.0625, "cup");
    m->addUnit("tsp", 0.3333333333333333, "tbl");
    m->addUnit("bbl", 1.0, "barrel");
    m->addUnit("Mbbl", 1000000.0, "barrel");
    m->addUnit("Bbbl", 1.0e+9, "barrel");
    m->addUnit("BRT", 100.0, "ft3");
    m = defineBaseMeasure("Time", "s");
    m->addUnit("fs", 1.0e-15, "s");
    m->addUnit("ps", 1.0e-12, "s");
    m->addUnit("ns", 1.0e-9, "s");
    m->addUnit("us", 1.0e-6, "s");
    m->addUnit("ms", 0.001, "s");
    m->addUnit("min", 60.0, "s");
    m->addUnit("h", 60.0, "min");
    m->addUnit("day", 24.0, "h");
    m->addUnit("hr", 1.0, "h");
    m->addUnit("week", 7.0, "day");
    m->addUnit("fortnight", 14.0, "day");
    m->addUnit("year", 365.24219, "day");
    m->addUnit("decade", 10.0, "year");
    m->addUnit("century", 100.0, "year");
    m->addUnit("yr", 1.0, "year");
    m->addUnit("years", 1.0, "year");
    m->addUnit("days", 1.0, "day");
    m->addUnit("weeks", 1.0, "week");
    m->addUnit("month", 0.08333333333333333, "year");
    m->addUnit("months", 1.0, "month");
    m = defineDerivedMeasure("Velocity", "m/s", "m/s");
    m->addUnit("mph", 1.0, "mi/h");
    m->addUnit("kts", 1.0, "NM/h");
    m->addUnit("knots", 1.0, "kts");
    m->addUnit("c", 2.99792458e+8, "m/s");
    m = defineDerivedMeasure("Acceleration", "m/s2", "m/s2");
    m->addUnit("G", 9.80665, "m/s2");
    m = defineBaseMeasure("Amount-Of-Substance", "mole");
    m->addUnit("mol", 1.0, "mole");
    m->addUnit("mmol", 0.001, "mole");
    m->addUnit("umol", 1.0e-6, "mole");
    m->addUnit("kmol", 1000.0, "mole");
    m->addUnit("kilomole", 1.0, "kmol");
    m->addUnit("millimole", 1.0, "mmol");
    m->addUnit("micromole", 1.0, "umol");
    m->addUnit("molecule", 1.660540186674939e-24, "mol");
    m->addUnit("particle", 1.0, "molecule");
    m->addUnit("atom", 1.0, "molecule");
    m->addUnit("ion", 1.0, "molecule");
    m = defineDerivedMeasure("Molality", "mol/kg", "mol/kg");
    m->addUnit("molal", 1.0, "mol/kg");
    m = defineDerivedMeasure("Concentration-Of-Substance", "mol/m3", "mol/m3");
    m->addUnit("M", 1.0, "mol/l");
    m->addUnit("molar", 1.0, "M");
    m->addUnit("mM", 0.001, "M");
    m->addUnit("uM", 0.001, "mM");
    m->addUnit("nM", 0.001, "uM");
    m = defineDerivedMeasure("Molar-Mass", "kg/mol", "kg/mol");
    m = defineDerivedMeasure("Force", "N", "kg.m/s2");
    m->addUnit("kN", 1000.0, "N");
    m->addUnit("kgf", 1.0, "kg.G");
    m->addUnit("lbf", 1.0, "lb.G");
    m->addUnit("dyne", 1.0e-5, "N");
    m = defineDerivedMeasure("Pressure", "Pa", "kg/s2m");
    m->addUnit("N/m2", 1.0, "Pa");
    m->addUnit("hPa", 100.0, "Pa");
    m->addUnit("kPa", 1000.0, "Pa");
    m->addUnit("atm", 101325.0, "Pa");
    m->addUnit("inHg", 0.03342, "atm");
    m->addUnit("torr", 133.32236842105263, "Pa");
    m->addUnit("mmHg", 1.0, "torr");
    m->addUnit("psi", 6895301.7, "g/s2m");
    m->addUnit("bar", 100000.0, "Pa");
    m->addUnit("mbar", 0.001, "bar");
    m = defineDerivedMeasure("Density", "kg/m3", "kg/m3");
    m->addUnit("ppm", 1.0, "mg/l");
    m->addUnit("ppb", 1.0, "ug/l");
    m->addUnit("ppt", 1.0, "ng/l");
    m->addUnit("ppq", 1.0, "pg/l");
    m = defineDerivedMeasure("Power", "W", "m2kg/s3");
    m->addUnit("hp", 550.0, "ft.lbf/s");
    m->addUnit("shp", 1.0, "hp");
    m->addUnit("mW", 0.001, "W");
    m->addUnit("kW", 1000.0, "W");
    m->addUnit("MW", 1000000.0, "W");
    m->addUnit("GW", 1.0e+9, "W");
    m = defineDerivedMeasure("Work-Or-Torque", "J", "m2kg/s2");
    m->addUnit("erg", 1.0, "dyne.cm");
    m->addUnit("kJ", 1000.0, "J");
    m->addUnit("MJ", 1000000.0, "J");
    m->addUnit("GJ", 1.0e+9, "J");
    m->addUnit("BTU", 1055.05585262, "J");
    m->addUnit("cal", 4.1868, "J");
    m->addUnit("kcal", 1000.0, "cal");
    m->addUnit("therm", 1.0550559e+8, "J");
    m->addUnit("kWh", 1.0, "kW.h");
    m->addUnit("kiloton", 4.184e+12, "J");
    m->addUnit("Megaton", 1000.0, "kiloton");
    m = defineBaseMeasure("Electric-Current", "A");
    m->addUnit("mA", 0.001, "A");
    m = defineDerivedMeasure("Electric-Charge", "C", "s.A");
    m->addUnit("pC", 1.0e-12, "C");
    m = defineDerivedMeasure("Electric-Potential", "V", "m2kg/s3A");
    m->addUnit("mV", 0.001, "V");
    m->addUnit("kV", 1000.0, "V");
    m->addUnit("MV", 1000.0, "kV");
    m = defineDerivedMeasure("Electric-Resistance", "ohm", "m2kg/s3A2");
    m->addUnit("kohm", 1000.0, "ohm");
    m->addUnit("Mohm", 1000000.0, "ohm");
    m = defineDerivedMeasure("Electric-Conductance", "mho", "ohm-1");
    m->addUnit("S", 1.0, "mho");
    m->addUnit("mmho", 1.0e-6, "mho");
    m->addUnit("umho", 1.0e-9, "mho");
    m = defineDerivedMeasure("Capacitance", "F", "A2s4/m2kg");
    m->addUnit("mF", 0.001, "F");
    m->addUnit("uF", 1.0e-6, "F");
    m->addUnit("pF", 1.0e-6, "uF");
    m = defineDerivedMeasure("Inductance", "H", "m2kg/A2s2");
    m = defineDerivedMeasure("Magnetic-Flux", "Wb", "m2kg/s2A");
    m = defineDerivedMeasure("Magnetic-Flux-Density", "T", "kg/s2A");
    m = defineBaseMeasure("Luminous-Intensity", "Cd");
    m->addUnit("lumen", 1.0, "Cd");
    m->addUnit("lm", 1.0, "Cd");
    m = defineDerivedMeasure("Illuminance", "lux", "Cd/m2");
    m->addUnit("lx", 1.0, "lux");
    m = defineBaseMeasure("Temperature", "K");
    m->addUnit("oK", 1.0, "K");
    m->addUnit("Kelvin", 1.0, "K");
    m->addUnit("oC", 1.0, "K");
    m->addUnit("oF", 0.5555555555555556, "K");
    m->addUnit("Rankine", 1.0, "oF");
    m = defineBaseMeasure("Data", "bit");
    m->addUnit("byte", 8.0, "bit");
    m->addUnit("B", 1.0, "byte");
    m->addUnit("Kibit", 1024.0, "bit");
    m->addUnit("kibit", 1.0, "Kibit");
    m->addUnit("Mibit", 1024.0, "kibit");
    m->addUnit("Gibit", 1024.0, "Mibit");
    m->addUnit("KiB", 1024.0, "byte");
    m->addUnit("kiB", 1.0, "KiB");
    m->addUnit("MiB", 1024.0, "KiB");
    m->addUnit("GiB", 1024.0, "MiB");
    m->addUnit("TiB", 1024.0, "GiB");
    m->addUnit("PiB", 1024.0, "TiB");
    m->addUnit("kbit", 1000.0, "bit");
    m->addUnit("Mbit", 1000.0, "kbit");
    m->addUnit("Gbit", 1000.0, "Mbit");
    m->addUnit("kB", 1000.0, "byte");
    m->addUnit("MB", 1000.0, "kB");
    m->addUnit("GB", 1000.0, "MB");
    m->addUnit("TB", 1000.0, "GB");
    m->addUnit("PB", 1000.0, "TB");
    m = defineDimensionlessMeasure();
    m->addUnit("%", 0.01, "");
    m->addUnit("%%", 0.001, "");
    m->addUnit("rad", 1.0, "");
    m->addUnit("radian", 1.0, "rad");
    m->addUnit("deg", 0.017453292519943295, "rad");
    m->addUnit("minute", 0.016666666666666666, "deg");
    m->addUnit("sec", 0.016666666666666666, "minute");
    m->addUnit("arcmin", 1.0, "minute");
    m->addUnit("arcsec", 1.0, "sec");
    m->addUnit("degree", 1.0, "deg");
    m->addUnit("mil", 0.05625, "deg");
    m->addUnit("sr", 1.0, "");
    m->addUnit("steradian", 1.0, "sr");
    m = defineDerivedMeasure("Frequency", "Hz", "s-1");
    m->addUnit("kHz", 1000.0, "Hz");
    m->addUnit("MHz", 1000000.0, "Hz");
    m->addUnit("GHz", 1.0e+9, "Hz");
    m->addUnit("Bq", 1.0, "Hz");
    m->addUnit("Ci", 3.7e+10, "Bq");
    m->addUnit("mCi", 0.001, "Ci");
    m->addUnit("pCi", 1.0e-9, "Ci");
    m->addUnit("rps", 360.0, "deg/s");
    m->addUnit("rpm", 0.016666666666666666, "rps");
  }
}

void startupUnitDefs() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/UTILITIES", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SYM_UNIT_DEFS_UTILITIES_STARTUP_UNIT_DEFS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-UNIT-DEFS", NULL, 0)));
      SYM_UNIT_DEFS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("INITIALIZE-UNIT-DEFINITIONS", "(DEFUN INITIALIZE-UNIT-DEFINITIONS () :DOCUMENTATION \"Measure conversion factors.  The ultimate source for the\nconversions are the following publications.  NIST was normally followed\nunless a more precise value was found in MfM.\n\nSources:\n[NIST]\n  Guide for the Use of the International System of Units (SI)\n  U.S. Department of Commerce\n  National Institute of Standards and Technology (NIST)\n  NIST Special Publication 811, 1995 Edition\n  http://physics.nist.gov/Document/sp811.pdf\n\n[MfM]\n  Richard A. Young and Thomas J. Glover\n  Measure for Measure\n  1996.  ISBN 1-889796-00-X\n  (Blue Willow, Inc.; Littleton, Colorado, USA)\n  http://www.bluewillow.com/\n\")", ((cpp_function_code)(&initializeUnitDefinitions)), NULL);
      defineFunctionObject("STARTUP-UNIT-DEFS", "(DEFUN STARTUP-UNIT-DEFS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupUnitDefs)), NULL);
      { MethodSlot* function = lookupFunction(SYM_UNIT_DEFS_UTILITIES_STARTUP_UNIT_DEFS);

        setDynamicSlotValue(function->dynamicSlots, SYM_UNIT_DEFS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupUnitDefs"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("UTILITIES")))));
    }
  }
}

Symbol* SYM_UNIT_DEFS_UTILITIES_STARTUP_UNIT_DEFS = NULL;

Symbol* SYM_UNIT_DEFS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella_utilities
