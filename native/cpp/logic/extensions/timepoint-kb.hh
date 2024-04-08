//  -*- Mode: C++ -*-

// timepoint-kb.hh

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




namespace timepoint {
  using namespace stella_utilities;
  using namespace stella;
  using namespace logic;

// Function signatures:
void startupTimepointKb();

// Auxiliary global declarations:
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_DAY_OF_WEEK;
extern Keyword* KWD_TIMEPOINT_KB_CLOSED;
extern Symbol* SYM_TIMEPOINT_KB_STELLA_TRUE;
extern Keyword* KWD_TIMEPOINT_KB_AXIOMS;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_OF;
extern Keyword* KWD_TIMEPOINT_KB__g;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_pTP;
extern Keyword* KWD_TIMEPOINT_KB_DOCUMENTATION;
extern Keyword* KWD_TIMEPOINT_KB_COMPUTED;
extern Keyword* KWD_TIMEPOINT_KB_RELATION_CONSTRAINT;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_OF_CONSTRAINT;
extern Keyword* KWD_TIMEPOINT_KB_RELATION_SPECIALIST;
extern Symbol* SYM_TIMEPOINT_KB_PL_KERNEL_KB_CONSTRAINT_SPECIALIST;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_DURATION_OF;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_DURATION_OF_CONSTRAINT;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIME_;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIME_MINUS_CONSTRAINT;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEi;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIME_PLUS_CONSTRAINT;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_OFo;
extern Keyword* KWD_TIMEPOINT_KB_RELATION_EVALUATOR;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_OFo_EVALUATOR;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_OFo_SPECIALIST;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_YEAR;
extern Keyword* KWD_TIMEPOINT_KB_RELATION_COMPUTATION;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_YEAR_COMPUTATION;
extern Symbol* SYM_TIMEPOINT_KB_PL_KERNEL_KB_COMPUTATION_SPECIALIST;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_MONTH;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_MONTH_COMPUTATION;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_DAY;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_DAY_COMPUTATION;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_DAY_OF_WEEK;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_DAY_OF_WEEK_COMPUTATION;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_HOUR;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_HOUR_COMPUTATION;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_MINUTE;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_MINUTE_COMPUTATION;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_SECOND;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_SECOND_COMPUTATION;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_DATE;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_DATE_COMPUTATION;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_TIMEPOINT_TIME;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_TIMEPOINT_TIME_COMPUTATION;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_FORMAT_TIMEPOINT;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_FORMAT_TIMEPOINT_COMPUTATION;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_KB_CURRENT_TIME;
extern Keyword* KWD_TIMEPOINT_KB_lle;
extern Symbol* SYM_TIMEPOINT_KB_TIMEPOINT_SUPPORT_STARTUP_TIMEPOINT_KB;
extern Symbol* SYM_TIMEPOINT_KB_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace timepoint
