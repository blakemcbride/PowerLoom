;;; -*- Mode: Lisp; Package: STELLA; Syntax: COMMON-LISP; Base: 10 -*-

;;; unit-defs.lisp

#|
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
|#

(CL:IN-PACKAGE "STELLA")

;;; Auxiliary variables:

(CL:DEFVAR SYM-UNIT-DEFS-UTILITIES-STARTUP-UNIT-DEFS NULL)
(CL:DEFVAR SYM-UNIT-DEFS-STELLA-METHOD-STARTUP-CLASSNAME NULL)

;;; Forward declarations:

(CL:DECLAIM (CL:SPECIAL *STARTUP-TIME-PHASE* *MODULE*))

;;; (DEFUN INITIALIZE-UNIT-DEFINITIONS ...)

(CL:DEFUN INITIALIZE-UNIT-DEFINITIONS ()
  "Measure conversion factors.  The ultimate source for the
conversions are the following publications.  NIST was normally followed
unless a more precise value was found in MfM.

Sources:
[NIST]
  Guide for the Use of the International System of Units (SI)
  U.S. Department of Commerce
  National Institute of Standards and Technology (NIST)
  NIST Special Publication 811, 1995 Edition
  http://physics.nist.gov/Document/sp811.pdf

[MfM]
  Richard A. Young and Thomas J. Glover
  Measure for Measure
  1996.  ISBN 1-889796-00-X
  (Blue Willow, Inc.; Littleton, Colorado, USA)
  http://www.bluewillow.com/
"
  (CL:LET* ((M NULL)) (CL:SETQ M (DEFINE-BASE-MEASURE "Mass" "kg"))
   (ADD-UNIT M "g" 0.001d0 "kg") (ADD-UNIT M "mg" 0.001d0 "g")
   (ADD-UNIT M "ug" 1.0d-6 "g") (ADD-UNIT M "ng" 1.0d-9 "g")
   (ADD-UNIT M "pg" 1.0d-12 "g") (ADD-UNIT M "d" 1.7d-24 "g")
   (ADD-UNIT M "dalton" 1.0d0 "d") (ADD-UNIT M "kd" 1000.0d0 "d")
   (ADD-UNIT M "lbs" 0.45359237d0 "kg")
   (ADD-UNIT M "oz" 0.0625d0 "lbs")
   (ADD-UNIT M "gr" 1.4285714285714287d-4 "lbs")
   (ADD-UNIT M "lb" 1.0d0 "lbs") (ADD-UNIT M "mton" 1000000.0d0 "g")
   (ADD-UNIT M "tonne" 1000000.0d0 "g")
   (ADD-UNIT M "ton" 2000.0d0 "lbs")
   (ADD-UNIT M "longton" 2240.0d0 "lbs")
   (ADD-UNIT M "stone" 14.0d0 "lbs") (ADD-UNIT M "hwt" 100.0d0 "lbs")
   (ADD-UNIT M "slug" 14594.14842519685d0 "g")
   (ADD-UNIT M "carat" 0.2d0 "g")
   (CL:SETQ M (DEFINE-BASE-MEASURE "Distance" "m"))
   (ADD-UNIT M "nm" 1.0d-9 "m") (ADD-UNIT M "um" 1.0d-6 "m")
   (ADD-UNIT M "mm" 0.001d0 "m") (ADD-UNIT M "cm" 0.01d0 "m")
   (ADD-UNIT M "dm" 0.1d0 "m") (ADD-UNIT M "km" 1000.0d0 "m")
   (ADD-UNIT M "angstrom" 1.0d-10 "m")
   (ADD-UNIT M "ang" 1.0d0 "angstrom") (ADD-UNIT M "in" 0.0254d0 "m")
   (ADD-UNIT M "ft" 12.0d0 "in") (ADD-UNIT M "yd" 3.0d0 "ft")
   (ADD-UNIT M "mile" 5280.0d0 "ft") (ADD-UNIT M "miles" 1.0d0 "mile")
   (ADD-UNIT M "mi" 1.0d0 "mile") (ADD-UNIT M "NM" 1852.0d0 "m")
   (ADD-UNIT M "nautmi" 1852.0d0 "m") (ADD-UNIT M "fathom" 6.0d0 "ft")
   (ADD-UNIT M "furlong" 220.0d0 "yd") (ADD-UNIT M "hand" 4.0d0 "in")
   (ADD-UNIT M "hh" 1.0d0 "hand")
   (ADD-UNIT M "pica" 0.16666666666666666d0 "in")
   (ADD-UNIT M "point" 0.013888888888888888d0 "in")
   (ADD-UNIT M "pt" 1.0d0 "point")
   (ADD-UNIT M "AU" 1.4959787066000003d+11 "m")
   (ADD-UNIT M "lightyear" 9.460528177426822d+15 "m")
   (ADD-UNIT M "LY" 1.0d0 "lightyear")
   (ADD-UNIT M "parsec" 3.085678d+16 "m")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Area" "m2" "m2"))
   (ADD-UNIT M "sqyd" 1.0d0 "yd2") (ADD-UNIT M "sqft" 1.0d0 "ft2")
   (ADD-UNIT M "sqin" 1.0d0 "in2") (ADD-UNIT M "sqkm" 1.0d0 "km2")
   (ADD-UNIT M "sqmile" 1.0d0 "mile2")
   (ADD-UNIT M "hectare" 10000.0d0 "m2")
   (ADD-UNIT M "ha" 1.0d0 "hectare") (ADD-UNIT M "are" 100.0d0 "m2")
   (ADD-UNIT M "a" 1.0d0 "are") (ADD-UNIT M "acre" 4840.0d0 "yd2")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Volume" "m3" "m3"))
   (ADD-UNIT M "liter" 0.001d0 "m3") (ADD-UNIT M "l" 1.0d0 "liter")
   (ADD-UNIT M "L" 1.0d0 "liter") (ADD-UNIT M "ml" 0.001d0 "liter")
   (ADD-UNIT M "ul" 1.0d-6 "liter") (ADD-UNIT M "nl" 1.0d-9 "liter")
   (ADD-UNIT M "pl" 1.0d-12 "liter") (ADD-UNIT M "cc" 1.0d0 "ml")
   (ADD-UNIT M "cl" 0.01d0 "liter") (ADD-UNIT M "dl" 0.1d0 "liter")
   (ADD-UNIT M "Hl" 100.0d0 "liter") (ADD-UNIT M "cuft" 1.0d0 "ft3")
   (ADD-UNIT M "cuyd" 1.0d0 "yd3")
   (ADD-UNIT M "acrefeet" 1.0d0 "acre.ft")
   (ADD-UNIT M "gallon" 231.0d0 "in3")
   (ADD-UNIT M "pint" 0.125d0 "gallon")
   (ADD-UNIT M "quart" 0.25d0 "gallon")
   (ADD-UNIT M "gal" 1.0d0 "gallon") (ADD-UNIT M "qt" 1.0d0 "quart")
   (ADD-UNIT M "floz" 0.0625d0 "pint")
   (ADD-UNIT M "barrel" 42.0d0 "gal") (ADD-UNIT M "cup" 0.5d0 "pint")
   (ADD-UNIT M "tbl" 0.0625d0 "cup")
   (ADD-UNIT M "tsp" 0.3333333333333333d0 "tbl")
   (ADD-UNIT M "bbl" 1.0d0 "barrel")
   (ADD-UNIT M "Mbbl" 1000000.0d0 "barrel")
   (ADD-UNIT M "Bbbl" 1.0d+9 "barrel") (ADD-UNIT M "BRT" 100.0d0 "ft3")
   (CL:SETQ M (DEFINE-BASE-MEASURE "Time" "s"))
   (ADD-UNIT M "fs" 1.0d-15 "s") (ADD-UNIT M "ps" 1.0d-12 "s")
   (ADD-UNIT M "ns" 1.0d-9 "s") (ADD-UNIT M "us" 1.0d-6 "s")
   (ADD-UNIT M "ms" 0.001d0 "s") (ADD-UNIT M "min" 60.0d0 "s")
   (ADD-UNIT M "h" 60.0d0 "min") (ADD-UNIT M "day" 24.0d0 "h")
   (ADD-UNIT M "hr" 1.0d0 "h") (ADD-UNIT M "week" 7.0d0 "day")
   (ADD-UNIT M "fortnight" 14.0d0 "day")
   (ADD-UNIT M "year" 365.24219d0 "day")
   (ADD-UNIT M "decade" 10.0d0 "year")
   (ADD-UNIT M "century" 100.0d0 "year") (ADD-UNIT M "yr" 1.0d0 "year")
   (ADD-UNIT M "years" 1.0d0 "year") (ADD-UNIT M "days" 1.0d0 "day")
   (ADD-UNIT M "weeks" 1.0d0 "week")
   (ADD-UNIT M "month" 0.08333333333333333d0 "year")
   (ADD-UNIT M "months" 1.0d0 "month")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Velocity" "m/s" "m/s"))
   (ADD-UNIT M "mph" 1.0d0 "mi/h") (ADD-UNIT M "kts" 1.0d0 "NM/h")
   (ADD-UNIT M "knots" 1.0d0 "kts")
   (ADD-UNIT M "c" 2.99792458d+8 "m/s")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Acceleration" "m/s2" "m/s2"))
   (ADD-UNIT M "G" 9.80665d0 "m/s2")
   (CL:SETQ M (DEFINE-BASE-MEASURE "Amount-Of-Substance" "mole"))
   (ADD-UNIT M "mol" 1.0d0 "mole") (ADD-UNIT M "mmol" 0.001d0 "mole")
   (ADD-UNIT M "umol" 1.0d-6 "mole")
   (ADD-UNIT M "kmol" 1000.0d0 "mole")
   (ADD-UNIT M "kilomole" 1.0d0 "kmol")
   (ADD-UNIT M "millimole" 1.0d0 "mmol")
   (ADD-UNIT M "micromole" 1.0d0 "umol")
   (ADD-UNIT M "molecule" 1.660540186674939d-24 "mol")
   (ADD-UNIT M "particle" 1.0d0 "molecule")
   (ADD-UNIT M "atom" 1.0d0 "molecule")
   (ADD-UNIT M "ion" 1.0d0 "molecule")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Molality" "mol/kg" "mol/kg"))
   (ADD-UNIT M "molal" 1.0d0 "mol/kg")
   (CL:SETQ M
    (DEFINE-DERIVED-MEASURE "Concentration-Of-Substance" "mol/m3"
     "mol/m3"))
   (ADD-UNIT M "M" 1.0d0 "mol/l") (ADD-UNIT M "molar" 1.0d0 "M")
   (ADD-UNIT M "mM" 0.001d0 "M") (ADD-UNIT M "uM" 0.001d0 "mM")
   (ADD-UNIT M "nM" 0.001d0 "uM")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Molar-Mass" "kg/mol" "kg/mol"))
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Force" "N" "kg.m/s2"))
   (ADD-UNIT M "kN" 1000.0d0 "N") (ADD-UNIT M "kgf" 1.0d0 "kg.G")
   (ADD-UNIT M "lbf" 1.0d0 "lb.G") (ADD-UNIT M "dyne" 1.0d-5 "N")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Pressure" "Pa" "kg/s2m"))
   (ADD-UNIT M "N/m2" 1.0d0 "Pa") (ADD-UNIT M "hPa" 100.0d0 "Pa")
   (ADD-UNIT M "kPa" 1000.0d0 "Pa") (ADD-UNIT M "atm" 101325.0d0 "Pa")
   (ADD-UNIT M "inHg" 0.03342d0 "atm")
   (ADD-UNIT M "torr" 133.32236842105263d0 "Pa")
   (ADD-UNIT M "mmHg" 1.0d0 "torr")
   (ADD-UNIT M "psi" 6895301.7d0 "g/s2m")
   (ADD-UNIT M "bar" 100000.0d0 "Pa") (ADD-UNIT M "mbar" 0.001d0 "bar")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Density" "kg/m3" "kg/m3"))
   (ADD-UNIT M "ppm" 1.0d0 "mg/l") (ADD-UNIT M "ppb" 1.0d0 "ug/l")
   (ADD-UNIT M "ppt" 1.0d0 "ng/l") (ADD-UNIT M "ppq" 1.0d0 "pg/l")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Power" "W" "m2kg/s3"))
   (ADD-UNIT M "hp" 550.0d0 "ft.lbf/s") (ADD-UNIT M "shp" 1.0d0 "hp")
   (ADD-UNIT M "mW" 0.001d0 "W") (ADD-UNIT M "kW" 1000.0d0 "W")
   (ADD-UNIT M "MW" 1000000.0d0 "W") (ADD-UNIT M "GW" 1.0d+9 "W")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Work-Or-Torque" "J" "m2kg/s2"))
   (ADD-UNIT M "erg" 1.0d0 "dyne.cm") (ADD-UNIT M "kJ" 1000.0d0 "J")
   (ADD-UNIT M "MJ" 1000000.0d0 "J") (ADD-UNIT M "GJ" 1.0d+9 "J")
   (ADD-UNIT M "BTU" 1055.05585262d0 "J")
   (ADD-UNIT M "cal" 4.1868d0 "J") (ADD-UNIT M "kcal" 1000.0d0 "cal")
   (ADD-UNIT M "therm" 1.0550559d+8 "J")
   (ADD-UNIT M "kWh" 1.0d0 "kW.h") (ADD-UNIT M "kiloton" 4.184d+12 "J")
   (ADD-UNIT M "Megaton" 1000.0d0 "kiloton")
   (CL:SETQ M (DEFINE-BASE-MEASURE "Electric-Current" "A"))
   (ADD-UNIT M "mA" 0.001d0 "A")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Electric-Charge" "C" "s.A"))
   (ADD-UNIT M "pC" 1.0d-12 "C")
   (CL:SETQ M
    (DEFINE-DERIVED-MEASURE "Electric-Potential" "V" "m2kg/s3A"))
   (ADD-UNIT M "mV" 0.001d0 "V") (ADD-UNIT M "kV" 1000.0d0 "V")
   (ADD-UNIT M "MV" 1000.0d0 "kV")
   (CL:SETQ M
    (DEFINE-DERIVED-MEASURE "Electric-Resistance" "ohm" "m2kg/s3A2"))
   (ADD-UNIT M "kohm" 1000.0d0 "ohm")
   (ADD-UNIT M "Mohm" 1000000.0d0 "ohm")
   (CL:SETQ M
    (DEFINE-DERIVED-MEASURE "Electric-Conductance" "mho" "ohm-1"))
   (ADD-UNIT M "S" 1.0d0 "mho") (ADD-UNIT M "mmho" 1.0d-6 "mho")
   (ADD-UNIT M "umho" 1.0d-9 "mho")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Capacitance" "F" "A2s4/m2kg"))
   (ADD-UNIT M "mF" 0.001d0 "F") (ADD-UNIT M "uF" 1.0d-6 "F")
   (ADD-UNIT M "pF" 1.0d-6 "uF")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Inductance" "H" "m2kg/A2s2"))
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Magnetic-Flux" "Wb" "m2kg/s2A"))
   (CL:SETQ M
    (DEFINE-DERIVED-MEASURE "Magnetic-Flux-Density" "T" "kg/s2A"))
   (CL:SETQ M (DEFINE-BASE-MEASURE "Luminous-Intensity" "Cd"))
   (ADD-UNIT M "lumen" 1.0d0 "Cd") (ADD-UNIT M "lm" 1.0d0 "Cd")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Illuminance" "lux" "Cd/m2"))
   (ADD-UNIT M "lx" 1.0d0 "lux")
   (CL:SETQ M (DEFINE-BASE-MEASURE "Temperature" "K"))
   (ADD-UNIT M "oK" 1.0d0 "K") (ADD-UNIT M "Kelvin" 1.0d0 "K")
   (ADD-UNIT M "oC" 1.0d0 "K")
   (ADD-UNIT M "oF" 0.5555555555555556d0 "K")
   (ADD-UNIT M "Rankine" 1.0d0 "oF")
   (CL:SETQ M (DEFINE-BASE-MEASURE "Data" "bit"))
   (ADD-UNIT M "byte" 8.0d0 "bit") (ADD-UNIT M "B" 1.0d0 "byte")
   (ADD-UNIT M "Kibit" 1024.0d0 "bit")
   (ADD-UNIT M "kibit" 1.0d0 "Kibit")
   (ADD-UNIT M "Mibit" 1024.0d0 "kibit")
   (ADD-UNIT M "Gibit" 1024.0d0 "Mibit")
   (ADD-UNIT M "KiB" 1024.0d0 "byte") (ADD-UNIT M "kiB" 1.0d0 "KiB")
   (ADD-UNIT M "MiB" 1024.0d0 "KiB") (ADD-UNIT M "GiB" 1024.0d0 "MiB")
   (ADD-UNIT M "TiB" 1024.0d0 "GiB") (ADD-UNIT M "PiB" 1024.0d0 "TiB")
   (ADD-UNIT M "kbit" 1000.0d0 "bit")
   (ADD-UNIT M "Mbit" 1000.0d0 "kbit")
   (ADD-UNIT M "Gbit" 1000.0d0 "Mbit")
   (ADD-UNIT M "kB" 1000.0d0 "byte") (ADD-UNIT M "MB" 1000.0d0 "kB")
   (ADD-UNIT M "GB" 1000.0d0 "MB") (ADD-UNIT M "TB" 1000.0d0 "GB")
   (ADD-UNIT M "PB" 1000.0d0 "TB")
   (CL:SETQ M (DEFINE-DIMENSIONLESS-MEASURE))
   (ADD-UNIT M "%" 0.01d0 "") (ADD-UNIT M "%%" 0.001d0 "")
   (ADD-UNIT M "rad" 1.0d0 "") (ADD-UNIT M "radian" 1.0d0 "rad")
   (ADD-UNIT M "deg" 0.017453292519943295d0 "rad")
   (ADD-UNIT M "minute" 0.016666666666666666d0 "deg")
   (ADD-UNIT M "sec" 0.016666666666666666d0 "minute")
   (ADD-UNIT M "arcmin" 1.0d0 "minute")
   (ADD-UNIT M "arcsec" 1.0d0 "sec") (ADD-UNIT M "degree" 1.0d0 "deg")
   (ADD-UNIT M "mil" 0.05625d0 "deg") (ADD-UNIT M "sr" 1.0d0 "")
   (ADD-UNIT M "steradian" 1.0d0 "sr")
   (CL:SETQ M (DEFINE-DERIVED-MEASURE "Frequency" "Hz" "s-1"))
   (ADD-UNIT M "kHz" 1000.0d0 "Hz") (ADD-UNIT M "MHz" 1000000.0d0 "Hz")
   (ADD-UNIT M "GHz" 1.0d+9 "Hz") (ADD-UNIT M "Bq" 1.0d0 "Hz")
   (ADD-UNIT M "Ci" 3.7d+10 "Bq") (ADD-UNIT M "mCi" 0.001d0 "Ci")
   (ADD-UNIT M "pCi" 1.0d-9 "Ci") (ADD-UNIT M "rps" 360.0d0 "deg/s")
   (ADD-UNIT M "rpm" 0.016666666666666666d0 "rps")))

(CL:DEFUN STARTUP-UNIT-DEFS ()
  (CL:LET*
   ((*MODULE*
     (GET-STELLA-MODULE "/UTILITIES" (> *STARTUP-TIME-PHASE* 1)))
    (*CONTEXT* *MODULE*))
   (CL:DECLARE (CL:SPECIAL *MODULE* *CONTEXT*))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 2)
    (CL:SETQ SYM-UNIT-DEFS-UTILITIES-STARTUP-UNIT-DEFS
     (INTERN-RIGID-SYMBOL-WRT-MODULE "STARTUP-UNIT-DEFS" NULL 0))
    (CL:SETQ SYM-UNIT-DEFS-STELLA-METHOD-STARTUP-CLASSNAME
     (INTERN-RIGID-SYMBOL-WRT-MODULE "METHOD-STARTUP-CLASSNAME"
      (GET-STELLA-MODULE "/STELLA" CL:T) 0)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 6) (FINALIZE-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 7)
    (DEFINE-FUNCTION-OBJECT "INITIALIZE-UNIT-DEFINITIONS"
     "(DEFUN INITIALIZE-UNIT-DEFINITIONS () :DOCUMENTATION \"Measure conversion factors.  The ultimate source for the
conversions are the following publications.  NIST was normally followed
unless a more precise value was found in MfM.

Sources:
[NIST]
  Guide for the Use of the International System of Units (SI)
  U.S. Department of Commerce
  National Institute of Standards and Technology (NIST)
  NIST Special Publication 811, 1995 Edition
  http://physics.nist.gov/Document/sp811.pdf

[MfM]
  Richard A. Young and Thomas J. Glover
  Measure for Measure
  1996.  ISBN 1-889796-00-X
  (Blue Willow, Inc.; Littleton, Colorado, USA)
  http://www.bluewillow.com/
\")" (CL:FUNCTION INITIALIZE-UNIT-DEFINITIONS) NULL)
    (DEFINE-FUNCTION-OBJECT "STARTUP-UNIT-DEFS"
     "(DEFUN STARTUP-UNIT-DEFS () :PUBLIC? TRUE)"
     (CL:FUNCTION STARTUP-UNIT-DEFS) NULL)
    (CL:LET*
     ((FUNCTION
       (LOOKUP-FUNCTION SYM-UNIT-DEFS-UTILITIES-STARTUP-UNIT-DEFS)))
     (SET-DYNAMIC-SLOT-VALUE (%DYNAMIC-SLOTS FUNCTION)
      SYM-UNIT-DEFS-STELLA-METHOD-STARTUP-CLASSNAME
      (WRAP-STRING "_StartupUnitDefs") NULL-STRING-WRAPPER)))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 8) (FINALIZE-SLOTS)
    (CLEANUP-UNFINALIZED-CLASSES))
   (CL:WHEN (CURRENT-STARTUP-TIME-PHASE? 9)
    (%IN-MODULE (COPY-CONS-TREE (WRAP-STRING "UTILITIES"))))))
