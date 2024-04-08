//  -*- Mode: C++ -*-

// timepoint-kb.cc

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
 | Portions created by the Initial Developer are Copyright (C) 1997-2023      |
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

#include "logic/extensions/powerloom-extensions-system.hh"

namespace timepoint {
  using namespace stella_utilities;
  using namespace stella;
  using namespace logic;

void startupTimepointKb() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/TIMEPOINT-SUPPORT", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT", getStellaModule("/TIMEPOINT-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_DAY_OF_WEEK = ((Symbol*)(internRigidSymbolWrtModule("DAY-OF-WEEK", getStellaModule("/TIMEPOINT-KB", true), 0)));
      KWD_TIMEPOINT_KB_CLOSED = ((Keyword*)(internRigidSymbolWrtModule("CLOSED", NULL, 2)));
      SYM_TIMEPOINT_KB_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", getStellaModule("/STELLA", true), 0)));
      KWD_TIMEPOINT_KB_AXIOMS = ((Keyword*)(internRigidSymbolWrtModule("AXIOMS", NULL, 2)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_OF = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-OF", getStellaModule("/TIMEPOINT-KB", true), 0)));
      KWD_TIMEPOINT_KB__g = ((Keyword*)(internRigidSymbolWrtModule("->", NULL, 2)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_pTP = ((Symbol*)(internRigidSymbolWrtModule("?TP", NULL, 0)));
      KWD_TIMEPOINT_KB_DOCUMENTATION = ((Keyword*)(internRigidSymbolWrtModule("DOCUMENTATION", NULL, 2)));
      KWD_TIMEPOINT_KB_COMPUTED = ((Keyword*)(internRigidSymbolWrtModule("COMPUTED", NULL, 2)));
      KWD_TIMEPOINT_KB_RELATION_CONSTRAINT = ((Keyword*)(internRigidSymbolWrtModule("RELATION-CONSTRAINT", NULL, 2)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_OF_CONSTRAINT = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-OF-CONSTRAINT", NULL, 0)));
      KWD_TIMEPOINT_KB_RELATION_SPECIALIST = ((Keyword*)(internRigidSymbolWrtModule("RELATION-SPECIALIST", NULL, 2)));
      SYM_TIMEPOINT_KB_PL_KERNEL_KB_CONSTRAINT_SPECIALIST = ((Symbol*)(internRigidSymbolWrtModule("CONSTRAINT-SPECIALIST", getStellaModule("/PL-KERNEL-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_DURATION_OF = ((Symbol*)(internRigidSymbolWrtModule("DURATION-OF", getStellaModule("/TIMEPOINT-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_DURATION_OF_CONSTRAINT = ((Symbol*)(internRigidSymbolWrtModule("DURATION-OF-CONSTRAINT", NULL, 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIME_ = ((Symbol*)(internRigidSymbolWrtModule("TIME-", getStellaModule("/TIMEPOINT-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIME_MINUS_CONSTRAINT = ((Symbol*)(internRigidSymbolWrtModule("TIME-MINUS-CONSTRAINT", NULL, 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEi = ((Symbol*)(internRigidSymbolWrtModule("TIME+", getStellaModule("/TIMEPOINT-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIME_PLUS_CONSTRAINT = ((Symbol*)(internRigidSymbolWrtModule("TIME-PLUS-CONSTRAINT", NULL, 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_OFo = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-OF*", getStellaModule("/TIMEPOINT-KB", true), 0)));
      KWD_TIMEPOINT_KB_RELATION_EVALUATOR = ((Keyword*)(internRigidSymbolWrtModule("RELATION-EVALUATOR", NULL, 2)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_OFo_EVALUATOR = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-OF*-EVALUATOR", NULL, 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_OFo_SPECIALIST = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-OF*-SPECIALIST", NULL, 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_YEAR = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-YEAR", getStellaModule("/TIMEPOINT-KB", true), 0)));
      KWD_TIMEPOINT_KB_RELATION_COMPUTATION = ((Keyword*)(internRigidSymbolWrtModule("RELATION-COMPUTATION", NULL, 2)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_YEAR_COMPUTATION = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-YEAR-COMPUTATION", NULL, 0)));
      SYM_TIMEPOINT_KB_PL_KERNEL_KB_COMPUTATION_SPECIALIST = ((Symbol*)(internRigidSymbolWrtModule("COMPUTATION-SPECIALIST", getStellaModule("/PL-KERNEL-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_MONTH = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-MONTH", getStellaModule("/TIMEPOINT-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_MONTH_COMPUTATION = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-MONTH-COMPUTATION", NULL, 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_DAY = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-DAY", getStellaModule("/TIMEPOINT-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_DAY_COMPUTATION = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-DAY-COMPUTATION", NULL, 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_DAY_OF_WEEK = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-DAY-OF-WEEK", getStellaModule("/TIMEPOINT-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_DAY_OF_WEEK_COMPUTATION = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-DAY-OF-WEEK-COMPUTATION", NULL, 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_HOUR = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-HOUR", getStellaModule("/TIMEPOINT-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_HOUR_COMPUTATION = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-HOUR-COMPUTATION", NULL, 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_MINUTE = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-MINUTE", getStellaModule("/TIMEPOINT-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_MINUTE_COMPUTATION = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-MINUTE-COMPUTATION", NULL, 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_SECOND = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-SECOND", getStellaModule("/TIMEPOINT-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_SECOND_COMPUTATION = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-SECOND-COMPUTATION", NULL, 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_DATE = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-DATE", getStellaModule("/TIMEPOINT-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_DATE_COMPUTATION = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-DATE-COMPUTATION", NULL, 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_TIME = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-TIME", getStellaModule("/TIMEPOINT-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_TIME_COMPUTATION = ((Symbol*)(internRigidSymbolWrtModule("TIMEPOINT-TIME-COMPUTATION", NULL, 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_FORMAT_TIMEPOINT = ((Symbol*)(internRigidSymbolWrtModule("FORMAT-TIMEPOINT", getStellaModule("/TIMEPOINT-KB", true), 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_FORMAT_TIMEPOINT_COMPUTATION = ((Symbol*)(internRigidSymbolWrtModule("FORMAT-TIMEPOINT-COMPUTATION", NULL, 0)));
      SYM_TIMEPOINT_KB_TIMEPOINT_KB_CURRENT_TIME = ((Symbol*)(internRigidSymbolWrtModule("CURRENT-TIME", getStellaModule("/TIMEPOINT-KB", true), 0)));
      KWD_TIMEPOINT_KB_lle = ((Keyword*)(internRigidSymbolWrtModule("<<=", NULL, 2)));
      SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_STARTUP_TIMEPOINT_KB = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-TIMEPOINT-KB", NULL, 0)));
      SYM_TIMEPOINT_KB_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("STARTUP-TIMEPOINT-KB", "(DEFUN STARTUP-TIMEPOINT-KB () :PUBLIC? TRUE)", ((cpp_function_code)(&startupTimepointKb)), NULL);
      { MethodSlot* function = lookupFunction(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_STARTUP_TIMEPOINT_KB);

        setDynamicSlotValue(function->dynamicSlots, SYM_TIMEPOINT_KB_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupTimepointKb"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("TIMEPOINT-SUPPORT")))));
      { 
        BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("PL-KERNEL-KB", true));
        BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
        defconcept(consList(1, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT)))));
        defconcept(consList(6, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_DAY_OF_WEEK))), ((Cons*)(copyConsTree(NIL))), KWD_TIMEPOINT_KB_CLOSED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_AXIOMS, ((Cons*)(copyConsTree(getQuotedTree("((AND (/TIMEPOINT-KB/DAY-OF-WEEK /TIMEPOINT-KB/SUNDAY) (/TIMEPOINT-KB/DAY-OF-WEEK /TIMEPOINT-KB/SATURDAY) (/TIMEPOINT-KB/DAY-OF-WEEK /TIMEPOINT-KB/FRIDAY) (/TIMEPOINT-KB/DAY-OF-WEEK /TIMEPOINT-KB/THURSDAY) (/TIMEPOINT-KB/DAY-OF-WEEK /TIMEPOINT-KB/WEDNESDAY) (/TIMEPOINT-KB/DAY-OF-WEEK /TIMEPOINT-KB/TUESDAY) (/TIMEPOINT-KB/DAY-OF-WEEK /TIMEPOINT-KB/MONDAY)) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT"))))));
        deffunction(consList(12, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_OF))), ((Cons*)(copyConsTree(getQuotedTree("(((?X STRING)) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB__g, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_pTP))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Connects a STRING representation ?x of a time point to the actual\ninternal representation which is a date/time quantity wrapper representing a time\npoint.  Dates and times can be specified in a large number of different formats\nspecified by the STELLA variable `*date-time-patterns*' (defined in\nstella/date-time.ste) which see.  Examples can also be found in the demo file\ntimepoints.ste.")))), KWD_TIMEPOINT_KB_COMPUTED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_RELATION_CONSTRAINT, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_OF_CONSTRAINT))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_PL_KERNEL_KB_CONSTRAINT_SPECIALIST)))));
        deffunction(consList(12, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_DURATION_OF))), ((Cons*)(copyConsTree(getQuotedTree("(((?X STRING)) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB__g, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_pTP))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Connects a STRING representation ?x of a time duration to the\nactual internal representation which is a date/time quantity wrapper representing\na duration or relative date.  The syntax for time duration strings is\n`{plus|minus} N days[; M ms]' where N and M are integer values for days and\nmilliseconds.")))), KWD_TIMEPOINT_KB_COMPUTED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_RELATION_CONSTRAINT, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_DURATION_OF_CONSTRAINT))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_PL_KERNEL_KB_CONSTRAINT_SPECIALIST)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIME_))), ((Cons*)(copyConsTree(getQuotedTree("((?T1 ?T2 ?T3) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Subtract ?t2 from ?t1 resulting in ?t3.  If both ?t1 and\n?t2 are time points, ?t3 will be a duration.  If both are durations, ?t3\nwill be a duration.  If ?t1 is a time point and ?t2 a duration, ?t3 will be\na time point.  All other combinations will lead to failure.  Note that this\nis a computed constraint which can generate any argument from the other two,\nwhich means it can also do addition.")))), KWD_TIMEPOINT_KB_COMPUTED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_RELATION_CONSTRAINT, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIME_MINUS_CONSTRAINT))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_PL_KERNEL_KB_CONSTRAINT_SPECIALIST)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEi))), ((Cons*)(copyConsTree(getQuotedTree("((?T1 ?T2 ?T3) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Add ?t2 to ?t1 resulting in ?t3.  If both ?t1 and ?t2\nare durations, ?t3 will be a duration.  If one of them is a duration and\nthe other is a time point, ?t3 will be a time point.  All other combinations\nwill lead to failure.  Note that this is a computed constraint which can\ngenerate any argument from the other two, which means it can also do subtraction.")))), KWD_TIMEPOINT_KB_COMPUTED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_RELATION_CONSTRAINT, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIME_PLUS_CONSTRAINT))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_PL_KERNEL_KB_CONSTRAINT_SPECIALIST)))));
        deffunction(consList(8, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_OFo))), ((Cons*)(copyConsTree(getQuotedTree("(((?YEAR INTEGER) (?MONTH INTEGER) (?DAY INTEGER) (?HOUR INTEGER) (?MINUTE INTEGER) (?SECOND NUMBER) ?ZONE ?TIMEPOINT) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Maps time components into a timepoint or vice versa.\nVariables ?year, ?month, ?day, ?hour and ?minute are integers.\nVariable ?second is a number, either integer or float with resolution 0.001.\nVariable ?zone is the time zone.  It is represented as a floating point offset\nfrom UTC in hours.  As an input value common strings (used in the United States)\nare also recognized, for example `PST, `EDT', `UTC', `GMT', `local' etc.\nVariable ?timepoint is the internal timepoint representation.  Either all\nof ?year to ?zone must be given to define a ?timepoint, or a ?timepoint\nmust be given to generate all its individual components.  If a ?timepoint\nand a ?zone are given, the individual components are generated relative to\nthat time zone.")))), KWD_TIMEPOINT_KB_RELATION_EVALUATOR, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_OFo_EVALUATOR))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_OFo_SPECIALIST)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_YEAR))), ((Cons*)(copyConsTree(getQuotedTree("((?TP ?ZONE (?YEAR INTEGER)) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The year component of ?tp evaluated in time zone ?zone.\nVariable ?zone is represented as a floating point offset from UTC in hours.\nAs a ?zone input value common strings are also recognized (see timepoint-of*).")))), KWD_TIMEPOINT_KB_COMPUTED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_RELATION_COMPUTATION, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_YEAR_COMPUTATION))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_PL_KERNEL_KB_COMPUTATION_SPECIALIST)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_MONTH))), ((Cons*)(copyConsTree(getQuotedTree("((?TP ?ZONE (?MONTH INTEGER)) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The month component of ?tp evaluated in time zone ?zone.\nVariable ?zone is represented as a floating point offset from UTC in hours.\nAs a ?zone input value common strings are also recognized (see timepoint-of*).")))), KWD_TIMEPOINT_KB_COMPUTED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_RELATION_COMPUTATION, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_MONTH_COMPUTATION))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_PL_KERNEL_KB_COMPUTATION_SPECIALIST)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_DAY))), ((Cons*)(copyConsTree(getQuotedTree("((?TP ?ZONE (?DAY INTEGER)) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The day component of ?tp evaluated in time zone ?zone.\nVariable ?zone is represented as a floating point offset from UTC in hours.\nAs a ?zone input value common strings are also recognized (see timepoint-of*).")))), KWD_TIMEPOINT_KB_COMPUTED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_RELATION_COMPUTATION, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_DAY_COMPUTATION))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_PL_KERNEL_KB_COMPUTATION_SPECIALIST)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_DAY_OF_WEEK))), ((Cons*)(copyConsTree(getQuotedTree("((?TP ?ZONE (?DOW /TIMEPOINT-KB/DAY-OF-WEEK)) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The day-of-week component of ?tp evaluated in time zone ?zone.\nVariable ?zone is represented as a floating point offset from UTC in hours.\nAs a ?zone input value common strings are also recognized (see timepoint-of*).")))), KWD_TIMEPOINT_KB_COMPUTED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_RELATION_COMPUTATION, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_DAY_OF_WEEK_COMPUTATION))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_PL_KERNEL_KB_COMPUTATION_SPECIALIST)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_HOUR))), ((Cons*)(copyConsTree(getQuotedTree("((?TP ?ZONE (?HOUR INTEGER)) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The hour component of ?tp evaluated in time zone ?zone.\nVariable ?zone is represented as a floating point offset from UTC in hours.\nAs a ?zone input value common strings are also recognized (see timepoint-of*).")))), KWD_TIMEPOINT_KB_COMPUTED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_RELATION_COMPUTATION, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_HOUR_COMPUTATION))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_PL_KERNEL_KB_COMPUTATION_SPECIALIST)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_MINUTE))), ((Cons*)(copyConsTree(getQuotedTree("((?TP ?ZONE (?MINUTE INTEGER)) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The minute component of ?tp evaluated in time zone ?zone.\nVariable ?zone is represented as a floating point offset from UTC in hours.\nAs a ?zone input value common strings are also recognized (see timepoint-of*).")))), KWD_TIMEPOINT_KB_COMPUTED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_RELATION_COMPUTATION, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_MINUTE_COMPUTATION))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_PL_KERNEL_KB_COMPUTATION_SPECIALIST)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_SECOND))), ((Cons*)(copyConsTree(getQuotedTree("((?TP ?ZONE (?SECOND NUMBER)) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The second component of ?tp evaluated in time zone ?zone.\nVariable ?zone is represented as a floating point offset from UTC in hours.\nAs a ?zone input value common strings are also recognized (see timepoint-of*).")))), KWD_TIMEPOINT_KB_COMPUTED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_RELATION_COMPUTATION, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_SECOND_COMPUTATION))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_PL_KERNEL_KB_COMPUTATION_SPECIALIST)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_DATE))), ((Cons*)(copyConsTree(getQuotedTree("((?TP ?ZONE (?DATE STRING)) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The date component of ?tp evaluated in time zone ?zone.\nVariable ?zone is represented as a floating point offset from UTC in hours.\nAs a ?zone input value common strings are also recognized (see timepoint-of*).")))), KWD_TIMEPOINT_KB_COMPUTED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_RELATION_COMPUTATION, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_DATE_COMPUTATION))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_PL_KERNEL_KB_COMPUTATION_SPECIALIST)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_TIME))), ((Cons*)(copyConsTree(getQuotedTree("((?TP ?ZONE (?TIME STRING)) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("The time component of ?tp evaluated in time zone ?zone.\nVariable ?zone is represented as a floating point offset from UTC in hours.\nAs a ?zone input value common strings are also recognized (see timepoint-of*).")))), KWD_TIMEPOINT_KB_COMPUTED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_RELATION_COMPUTATION, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_TIME_COMPUTATION))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_PL_KERNEL_KB_COMPUTATION_SPECIALIST)))));
        deffunction(consList(10, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_FORMAT_TIMEPOINT))), ((Cons*)(copyConsTree(getQuotedTree("((?TP ?ZONE (?CONTROL STRING) (?FORMATTED STRING)) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Format ?tp relative to ?zone according to the format ?control string whose\nsyntax supports most directives of the Unix `date' command (see also the STELLA function\n`format-date').  Variable ?zone is represented as a floating point offset from UTC in hours.\nAs a ?zone input value common strings are also recognized (see timepoint-of*).")))), KWD_TIMEPOINT_KB_COMPUTED, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_STELLA_TRUE))), KWD_TIMEPOINT_KB_RELATION_COMPUTATION, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_FORMAT_TIMEPOINT_COMPUTATION))), KWD_TIMEPOINT_KB_RELATION_SPECIALIST, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_PL_KERNEL_KB_COMPUTATION_SPECIALIST)))));
        defrelation(consList(6, ((Symbol*)(copyConsTree(SYM_TIMEPOINT_KB_TIMEPOINT_KB_CURRENT_TIME))), ((Cons*)(copyConsTree(getQuotedTree("((?TP) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT")))), KWD_TIMEPOINT_KB_DOCUMENTATION, ((StringWrapper*)(copyConsTree(wrapString("Convenience relation to access the current time ?tp.  Every time this is evaluated\nin a query with an unbound ?tp variable, this will bind ?tp to the newly measured current time.  This\nrelation shields some of the idiosyncrasies of a changing time value in a logic system where the same\nfunction should never evaluate to different values based on the same input arguments.  Do never use this\nfunction in an assertion!  Instead, retrieve the current time via a query and pipe the resulting value\ninto an assertion via `assert-from-query'.  For example:\n    (assert-from-query (retrieve (current-time ?now)) :pattern (kappa (?now) (mytimeof t1 ?now)))")))), KWD_TIMEPOINT_KB_lle, ((Cons*)(copyConsTree(getQuotedTree("((EXISTS ?SPEC (AND (MEMBER-OF ?SPEC (LISTOF \"now\")) (/TIMEPOINT-KB/TIMEPOINT-OF ?SPEC ?TP))) \"/TIMEPOINT-SUPPORT\")", "/TIMEPOINT-SUPPORT"))))));
        processDefinitions();
      }
    }
  }
}

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_DAY_OF_WEEK = NULL;

Keyword* KWD_TIMEPOINT_KB_CLOSED = NULL;

Symbol* SYM_TIMEPOINT_KB_STELLA_TRUE = NULL;

Keyword* KWD_TIMEPOINT_KB_AXIOMS = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_OF = NULL;

Keyword* KWD_TIMEPOINT_KB__g = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_pTP = NULL;

Keyword* KWD_TIMEPOINT_KB_DOCUMENTATION = NULL;

Keyword* KWD_TIMEPOINT_KB_COMPUTED = NULL;

Keyword* KWD_TIMEPOINT_KB_RELATION_CONSTRAINT = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_OF_CONSTRAINT = NULL;

Keyword* KWD_TIMEPOINT_KB_RELATION_SPECIALIST = NULL;

Symbol* SYM_TIMEPOINT_KB_PL_KERNEL_KB_CONSTRAINT_SPECIALIST = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_DURATION_OF = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_DURATION_OF_CONSTRAINT = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIME_ = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIME_MINUS_CONSTRAINT = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEi = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIME_PLUS_CONSTRAINT = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_OFo = NULL;

Keyword* KWD_TIMEPOINT_KB_RELATION_EVALUATOR = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_OFo_EVALUATOR = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_OFo_SPECIALIST = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_YEAR = NULL;

Keyword* KWD_TIMEPOINT_KB_RELATION_COMPUTATION = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_YEAR_COMPUTATION = NULL;

Symbol* SYM_TIMEPOINT_KB_PL_KERNEL_KB_COMPUTATION_SPECIALIST = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_MONTH = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_MONTH_COMPUTATION = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_DAY = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_DAY_COMPUTATION = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_DAY_OF_WEEK = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_DAY_OF_WEEK_COMPUTATION = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_HOUR = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_HOUR_COMPUTATION = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_MINUTE = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_MINUTE_COMPUTATION = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_SECOND = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_SECOND_COMPUTATION = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_DATE = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_DATE_COMPUTATION = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_TIME = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_TIME_COMPUTATION = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_FORMAT_TIMEPOINT = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_FORMAT_TIMEPOINT_COMPUTATION = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_CURRENT_TIME = NULL;

Keyword* KWD_TIMEPOINT_KB_lle = NULL;

Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_STARTUP_TIMEPOINT_KB = NULL;

Symbol* SYM_TIMEPOINT_KB_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace timepoint
