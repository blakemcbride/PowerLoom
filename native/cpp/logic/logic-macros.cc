//  -*- Mode: C++ -*-

// logic-macros.cc

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

#include "logic/logic-system.hh"

namespace logic {
  using namespace stella;

DEFINE_STELLA_SPECIAL(oSUPPRESSNONLOGICOBJECTWARNINGpo, boolean , true);

Object* signalParsingError(Cons* message) {
  { Symbol* streamvar = localGensym("STREAM");

    message = formatMessageArguments(message, false);
    return (listO(5, SYM_LOGIC_MACROS_STELLA_LET, cons(cons(streamvar, cons(listO(3, SYM_LOGIC_MACROS_STELLA_NEW, SYM_LOGIC_MACROS_STELLA_OUTPUT_STRING_STREAM, NIL), NIL)), NIL), listO(5, SYM_LOGIC_MACROS_STELLA_SPECIAL, cons(listO(3, SYM_LOGIC_MACROS_STELLA_oPRINTREADABLYpo, SYM_LOGIC_MACROS_STELLA_TRUE, NIL), NIL), listO(3, SYM_LOGIC_MACROS_STELLA_PRINT_STREAM, streamvar, cons(wrapString("PARSING ERROR: "), message->concatenate(listO(3, wrapString("."), SYM_LOGIC_MACROS_STELLA_EOL, NIL), 0))), listO(3, SYM_LOGIC_MACROS_LOGIC_HELP_SIGNAL_PROPOSITION_ERROR, streamvar, cons(KWD_LOGIC_MACROS_ERROR, NIL)), NIL), listO(3, SYM_LOGIC_MACROS_STELLA_SIGNAL_EXCEPTION, listO(5, SYM_LOGIC_MACROS_STELLA_NEW, SYM_LOGIC_MACROS_LOGIC_PARSING_ERROR, KWD_LOGIC_MACROS_MESSAGE, listO(3, SYM_LOGIC_MACROS_STELLA_THE_STRING, streamvar, NIL), NIL), NIL), NIL));
  }
}

Object* signalPropositionError(Cons* message) {
  { Symbol* streamvar = localGensym("STREAM");

    message = formatMessageArguments(message, false);
    return (listO(5, SYM_LOGIC_MACROS_STELLA_LET, cons(cons(streamvar, cons(listO(3, SYM_LOGIC_MACROS_STELLA_NEW, SYM_LOGIC_MACROS_STELLA_OUTPUT_STRING_STREAM, NIL), NIL)), NIL), listO(5, SYM_LOGIC_MACROS_STELLA_SPECIAL, cons(listO(3, SYM_LOGIC_MACROS_STELLA_oPRINTREADABLYpo, SYM_LOGIC_MACROS_STELLA_TRUE, NIL), NIL), listO(3, SYM_LOGIC_MACROS_STELLA_PRINT_STREAM, streamvar, cons(wrapString("ERROR: "), message->concatenate(listO(3, wrapString("."), SYM_LOGIC_MACROS_STELLA_EOL, NIL), 0))), listO(3, SYM_LOGIC_MACROS_LOGIC_HELP_SIGNAL_PROPOSITION_ERROR, streamvar, cons(KWD_LOGIC_MACROS_ERROR, NIL)), NIL), listO(3, SYM_LOGIC_MACROS_STELLA_SIGNAL_EXCEPTION, listO(5, SYM_LOGIC_MACROS_STELLA_NEW, SYM_LOGIC_MACROS_LOGIC_PROPOSITION_ERROR, KWD_LOGIC_MACROS_MESSAGE, listO(3, SYM_LOGIC_MACROS_STELLA_THE_STRING, streamvar, NIL), NIL), NIL), NIL));
  }
}

Object* signalPropositionWarning(Cons* message) {
  return (listO(5, SYM_LOGIC_MACROS_STELLA_SPECIAL, cons(listO(3, SYM_LOGIC_MACROS_STELLA_oPRINTREADABLYpo, SYM_LOGIC_MACROS_STELLA_TRUE, NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_PRINT_STREAM, SYM_LOGIC_MACROS_STELLA_STANDARD_WARNING, wrapString("WARNING: "), message->concatenate(cons(SYM_LOGIC_MACROS_STELLA_EOL, NIL), 0)), listO(4, SYM_LOGIC_MACROS_LOGIC_HELP_SIGNAL_PROPOSITION_ERROR, SYM_LOGIC_MACROS_STELLA_STANDARD_WARNING, KWD_LOGIC_MACROS_WARNING, NIL), NIL));
}

Object* defDisplayGlobals(Symbol* displayfunctionname, Cons* globalvariablenames) {
  { Cons* printclauses = NIL;

    { Symbol* g = NULL;
      Cons* iter000 = globalvariablenames->reverse();

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        g = ((Symbol*)(iter000->value));
        printclauses = append(cons(wrapString(g->symbolName), listO(3, wrapString(" =  "), g, cons(SYM_LOGIC_MACROS_STELLA_EOL, NIL))), printclauses);
      }
    }
    return (listO(6, SYM_LOGIC_MACROS_STELLA_DEFUN, cons(displayfunctionname, cons(SYM_LOGIC_MACROS_STELLA_STRING, NIL)), NIL, listO(3, SYM_LOGIC_MACROS_STELLA_PRINT, SYM_LOGIC_MACROS_STELLA_EOL, printclauses->concatenate(cons(SYM_LOGIC_MACROS_STELLA_EOL, NIL), 0)), listO(3, SYM_LOGIC_MACROS_STELLA_RETURN, wrapString(""), NIL), NIL));
  }
}

Object* moveInPlace() {
  return (listO(7, SYM_LOGIC_MACROS_STELLA_PROGN, listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_TRUTH_VALUE, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), SYM_LOGIC_MACROS_STELLA_NULL, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_JUSTIFICATION, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), SYM_LOGIC_MACROS_STELLA_NULL, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_WHEN, listO(3, SYM_LOGIC_MACROS_STELLA_DEFINEDp, listO(3, SYM_LOGIC_MACROS_LOGIC_PARTIAL_MATCH_FRAME, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), NIL), listO(3, SYM_LOGIC_MACROS_LOGIC_CLEAR_FRAME_PARTIAL_TRUTH, listO(3, SYM_LOGIC_MACROS_LOGIC_PARTIAL_MATCH_FRAME, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_LOGIC_LASTMOVE, KWD_LOGIC_MACROS_DOWN, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_COND, listO(3, SYM_LOGIC_MACROS_LOGIC_CHECKFORMOVEOUTp, listO(9, SYM_LOGIC_MACROS_STELLA_LET, listO(4, listO(3, SYM_LOGIC_MACROS_LOGIC_PARENT, listO(3, SYM_LOGIC_MACROS_LOGIC_UP, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), NIL), listO(3, SYM_LOGIC_MACROS_LOGIC_STARTTICKS, listO(3, SYM_LOGIC_MACROS_LOGIC_STARTING_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), NIL), listO(3, SYM_LOGIC_MACROS_LOGIC_AVAILABLETICKS, listO(5, SYM_LOGIC_MACROS_STELLA__, listO(3, SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_PARENT, NIL), listO(4, SYM_LOGIC_MACROS_STELLA__, SYM_LOGIC_MACROS_LOGIC_CLOCKTICKS, SYM_LOGIC_MACROS_LOGIC_STARTTICKS, NIL), wrapInteger(1), NIL), NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_PARENT, NIL), SYM_LOGIC_MACROS_LOGIC_AVAILABLETICKS, NIL), listO(3, SYM_LOGIC_MACROS_STELLA___, SYM_LOGIC_MACROS_LOGIC_AVAILABLETICKS, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), SYM_LOGIC_MACROS_LOGIC_AVAILABLETICKS, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_CURRENT_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_QUERY, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_ii, SYM_LOGIC_MACROS_LOGIC_CLOCKTICKS, NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_STARTING_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), SYM_LOGIC_MACROS_LOGIC_CLOCKTICKS, NIL), listO(7, SYM_LOGIC_MACROS_STELLA_WHEN, listO(4, SYM_LOGIC_MACROS_STELLA_le, SYM_LOGIC_MACROS_LOGIC_AVAILABLETICKS, wrapInteger(0), NIL), listO(3, SYM_LOGIC_MACROS_LOGIC_POP_FRAMES_UP_TO, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_MV_SETQ, listO(3, SYM_LOGIC_MACROS_LOGIC_FRAME, SYM_LOGIC_MACROS_STELLA_DEPTH, NIL), listO(4, SYM_LOGIC_MACROS_LOGIC_HANDLE_TIMEOUT, SYM_LOGIC_MACROS_LOGIC_FRAME, SYM_LOGIC_MACROS_STELLA_DEPTH, NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_LOGIC_LASTMOVE, KWD_LOGIC_MACROS_UP_FAIL, NIL), listO(4, SYM_LOGIC_MACROS_STELLA___, listO(3, SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_1i, listO(4, SYM_LOGIC_MACROS_STELLA__, SYM_LOGIC_MACROS_LOGIC_CLOCKTICKS, SYM_LOGIC_MACROS_LOGIC_STARTTICKS, NIL), NIL), NIL), NIL), NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_OTHERWISE, listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_CURRENT_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_QUERY, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_ii, SYM_LOGIC_MACROS_LOGIC_CLOCKTICKS, NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_STARTING_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), SYM_LOGIC_MACROS_LOGIC_CLOCKTICKS, NIL), NIL), NIL), NIL));
}

Object* moveDown() {
  return (listO(8, SYM_LOGIC_MACROS_STELLA_LET, listO(3, listO(3, SYM_LOGIC_MACROS_LOGIC_UPFRAME, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), listO(3, SYM_LOGIC_MACROS_LOGIC_DOWNFRAME, listO(3, SYM_LOGIC_MACROS_LOGIC_DOWN, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_STELLA_DEPTH, listO(3, SYM_LOGIC_MACROS_STELLA_1i, SYM_LOGIC_MACROS_STELLA_DEPTH, NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_CURRENT_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_QUERY, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_ii, SYM_LOGIC_MACROS_LOGIC_CLOCKTICKS, NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_COND, listO(9, listO(3, SYM_LOGIC_MACROS_STELLA_DEFINEDp, SYM_LOGIC_MACROS_LOGIC_DOWNFRAME, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_LOGIC_FRAME, SYM_LOGIC_MACROS_LOGIC_DOWNFRAME, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_STARTING_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), SYM_LOGIC_MACROS_LOGIC_CLOCKTICKS, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_WHEN, listO(4, SYM_LOGIC_MACROS_STELLA_AND, SYM_LOGIC_MACROS_LOGIC_CHECKFORMOVEOUTp, listO(3, SYM_LOGIC_MACROS_STELLA_NULLp, listO(3, SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_1_, listO(3, SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_UPFRAME, NIL), NIL), NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_TRUTH_VALUE, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), SYM_LOGIC_MACROS_STELLA_NULL, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_JUSTIFICATION, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), SYM_LOGIC_MACROS_STELLA_NULL, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_WHEN, listO(3, SYM_LOGIC_MACROS_STELLA_DEFINEDp, listO(3, SYM_LOGIC_MACROS_LOGIC_PARTIAL_MATCH_FRAME, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), NIL), listO(3, SYM_LOGIC_MACROS_LOGIC_CLEAR_FRAME_PARTIAL_TRUTH, listO(3, SYM_LOGIC_MACROS_LOGIC_PARTIAL_MATCH_FRAME, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_LOGIC_LASTMOVE, KWD_LOGIC_MACROS_DOWN, NIL), NIL), listO(3, SYM_LOGIC_MACROS_STELLA_OTHERWISE, listO(8, SYM_LOGIC_MACROS_STELLA_LET, cons(listO(3, SYM_LOGIC_MACROS_LOGIC_PROPOSITION, listO(3, SYM_LOGIC_MACROS_LOGIC_ARGUMENT_BOUND_TO, listO(4, SYM_LOGIC_MACROS_STELLA_NTH, listO(3, SYM_LOGIC_MACROS_STELLA_ARGUMENTS, listO(3, SYM_LOGIC_MACROS_LOGIC_PROPOSITION, SYM_LOGIC_MACROS_LOGIC_UPFRAME, NIL), NIL), listO(3, SYM_LOGIC_MACROS_LOGIC_ARGUMENT_CURSOR, SYM_LOGIC_MACROS_LOGIC_UPFRAME, NIL), NIL), NIL), NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_LOGIC_DOWNFRAME, listO(4, SYM_LOGIC_MACROS_LOGIC_CREATE_DOWN_FRAME, SYM_LOGIC_MACROS_LOGIC_UPFRAME, SYM_LOGIC_MACROS_LOGIC_PROPOSITION, NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_LOGIC_FRAME, SYM_LOGIC_MACROS_LOGIC_DOWNFRAME, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_STARTING_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), SYM_LOGIC_MACROS_LOGIC_CLOCKTICKS, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_WHEN, SYM_LOGIC_MACROS_LOGIC_CHECKFORMOVEOUTp, listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_1_, listO(3, SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_UPFRAME, NIL), NIL), NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_LOGIC_LASTMOVE, KWD_LOGIC_MACROS_DOWN, NIL), NIL), NIL), NIL), listO(6, SYM_LOGIC_MACROS_STELLA_WHEN, listO(4, SYM_LOGIC_MACROS_STELLA_AND, listO(4, SYM_LOGIC_MACROS_STELLA_g, SYM_LOGIC_MACROS_STELLA_DEPTH, listO(3, SYM_LOGIC_MACROS_LOGIC_CURRENT_DEPTH_CUTOFF, SYM_LOGIC_MACROS_LOGIC_QUERY, NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_EQLp, listO(3, SYM_LOGIC_MACROS_STELLA_STATE, SYM_LOGIC_MACROS_LOGIC_UPFRAME, NIL), KWD_LOGIC_MACROS_PATTERN, NIL), NIL), listO(3, SYM_LOGIC_MACROS_LOGIC_POP_FRAMES_UP_TO, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_MV_SETQ, listO(3, SYM_LOGIC_MACROS_LOGIC_FRAME, SYM_LOGIC_MACROS_STELLA_DEPTH, NIL), listO(4, SYM_LOGIC_MACROS_LOGIC_HANDLE_DEPTH_VIOLATION, SYM_LOGIC_MACROS_LOGIC_FRAME, SYM_LOGIC_MACROS_STELLA_DEPTH, NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_LOGIC_LASTMOVE, KWD_LOGIC_MACROS_UP_FAIL, NIL), NIL), listO(5, SYM_LOGIC_MACROS_STELLA_WHEN, SYM_LOGIC_MACROS_LOGIC_CHECKFORMOVEOUTp, listO(6, SYM_LOGIC_MACROS_STELLA_WHEN, listO(4, SYM_LOGIC_MACROS_STELLA_AND, listO(4, SYM_LOGIC_MACROS_STELLA_le, listO(3, SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), wrapInteger(0), NIL), listO(3, SYM_LOGIC_MACROS_STELLA_NOT, listO(4, SYM_LOGIC_MACROS_STELLA_EQLp, SYM_LOGIC_MACROS_LOGIC_LASTMOVE, KWD_LOGIC_MACROS_UP_FAIL, NIL), NIL), NIL), listO(3, SYM_LOGIC_MACROS_LOGIC_POP_FRAMES_UP_TO, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_MV_SETQ, listO(3, SYM_LOGIC_MACROS_LOGIC_FRAME, SYM_LOGIC_MACROS_STELLA_DEPTH, NIL), listO(4, SYM_LOGIC_MACROS_LOGIC_HANDLE_TIMEOUT, SYM_LOGIC_MACROS_LOGIC_FRAME, SYM_LOGIC_MACROS_STELLA_DEPTH, NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_LOGIC_LASTMOVE, KWD_LOGIC_MACROS_UP_FAIL, NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_WHEN, listO(4, SYM_LOGIC_MACROS_STELLA_EQLp, SYM_LOGIC_MACROS_LOGIC_LASTMOVE, KWD_LOGIC_MACROS_UP_FAIL, NIL), listO(4, SYM_LOGIC_MACROS_STELLA___, listO(3, SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_1i, listO(4, SYM_LOGIC_MACROS_STELLA__, SYM_LOGIC_MACROS_LOGIC_CLOCKTICKS, listO(3, SYM_LOGIC_MACROS_LOGIC_STARTING_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_DOWNFRAME, NIL), NIL), NIL), NIL), NIL), NIL), NIL));
}

Object* moveUp(Symbol* successP, Symbol* keepframeP) {
  { Keyword* lastmove = NULL;

    if (successP == SYM_LOGIC_MACROS_STELLA_TRUE) {
      lastmove = KWD_LOGIC_MACROS_UP_TRUE;
    }
    else if (successP == SYM_LOGIC_MACROS_LOGIC_FAIL) {
      lastmove = KWD_LOGIC_MACROS_UP_FAIL;
      successP = SYM_LOGIC_MACROS_STELLA_FALSE;
    }
    else {
      { OutputStringStream* stream000 = newOutputStringStream();

        *(stream000->nativeStream) << "`" << successP << "'" << " is not a valid case option";
        throw *newStellaException(stream000->theStringReader());
      }
    }
    return (listO(8, SYM_LOGIC_MACROS_STELLA_LET, cons(listO(3, SYM_LOGIC_MACROS_LOGIC_PARENT, listO(3, SYM_LOGIC_MACROS_LOGIC_UP, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), NIL), NIL), listO(5, SYM_LOGIC_MACROS_STELLA_WHEN, listO(3, SYM_LOGIC_MACROS_STELLA_DEFINEDp, SYM_LOGIC_MACROS_LOGIC_PARENT, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_STELLA_RESULT, SYM_LOGIC_MACROS_LOGIC_PARENT, NIL), SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), listO(5, SYM_LOGIC_MACROS_STELLA_IF, cons(SYM_LOGIC_MACROS_LOGIC_CACHE_QUERY_RESULTSp, NIL), listO(4, SYM_LOGIC_MACROS_LOGIC_CACHE_GOAL, SYM_LOGIC_MACROS_LOGIC_FRAME, successP, cons(((keepframeP == SYM_LOGIC_MACROS_LOGIC_KEEP_FRAME) ? SYM_LOGIC_MACROS_STELLA_TRUE : SYM_LOGIC_MACROS_STELLA_FALSE), cons(SYM_LOGIC_MACROS_LOGIC_CLOCKTICKS, NIL))), listO(4, SYM_LOGIC_MACROS_LOGIC_UPDATE_GOAL_CACHE, SYM_LOGIC_MACROS_LOGIC_FRAME, successP, NIL), NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_STELLA_DEPTH, listO(3, SYM_LOGIC_MACROS_STELLA_1_, SYM_LOGIC_MACROS_STELLA_DEPTH, NIL), NIL), listO(5, SYM_LOGIC_MACROS_STELLA_WHEN, SYM_LOGIC_MACROS_LOGIC_CHECKFORMOVEOUTp, listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), SYM_LOGIC_MACROS_STELLA_NULL, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_WHEN, listO(3, SYM_LOGIC_MACROS_STELLA_DEFINEDp, SYM_LOGIC_MACROS_LOGIC_PARENT, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETF, listO(3, SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_PARENT, NIL), listO(5, SYM_LOGIC_MACROS_STELLA__, listO(3, SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_PARENT, NIL), listO(4, SYM_LOGIC_MACROS_STELLA__, SYM_LOGIC_MACROS_LOGIC_CLOCKTICKS, listO(3, SYM_LOGIC_MACROS_LOGIC_STARTING_CLOCK_TICKS, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), NIL), wrapInteger(1), NIL), NIL), NIL), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_LOGIC_FRAME, SYM_LOGIC_MACROS_LOGIC_PARENT, NIL), listO(5, SYM_LOGIC_MACROS_STELLA_WHEN, listO(3, SYM_LOGIC_MACROS_STELLA_NULLp, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_LOGIC_SUCCESSp, successP, NIL), cons(SYM_LOGIC_MACROS_STELLA_BREAK, NIL), NIL), (((keepframeP == SYM_LOGIC_MACROS_LOGIC_KEEP_FRAME) ? NIL : cons(listO(3, SYM_LOGIC_MACROS_LOGIC_POP_DOWN_FRAME, SYM_LOGIC_MACROS_LOGIC_FRAME, NIL), NIL)))->concatenate(listO(3, listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_LOGIC_LASTMOVE, lastmove, NIL), SYM_LOGIC_MACROS_LOGIC_LASTMOVE, NIL), 0)));
  }
}

Object* applyRetrieve(Cons* body) {
  // Execute a query composed of io-variables `variables'
  // and body `queryBody'.  Before executing, bind variables to `inputBindings'
  // (in sequence). If one variable is left unbound, returns a cons list of
  // bindings of that variable.  If two or more are unbound, returns
  // a cons list of cons lists of bindings.  Setting the option :singletons?
  // to FALSE always returns a list of lists.  Example call:
  //   `(apply-retrieve variables queryBody inputBindings)'
  { Symbol* gensymname = methodGensym("QUERY");

    return (listO(7, SYM_LOGIC_MACROS_LOGIC_APPLY_CACHED_RETRIEVE, listO(3, SYM_LOGIC_MACROS_STELLA_BQUOTE, body->value, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_BQUOTE, body->rest->value, NIL), cons(SYM_LOGIC_MACROS_STELLA_CONS_LIST, ((Cons*)(body->rest->rest->value))->concatenate(NIL, 0)), cons(SYM_LOGIC_MACROS_STELLA_CONS_LIST, body->nthRest(3)->concatenate(NIL, 0)), listO(3, SYM_LOGIC_MACROS_STELLA_QUOTE, gensymname, NIL), NIL));
  }
}

Object* applyAsk(Cons* body) {
  // Execute a yes/no query composed of input-variables
  // `inputVariables' and body `queryBody'.  Before executing, bind variables
  // to `inputBindings' (in sequence).
  //   `(apply-ask inputVariables queryBody inputBindings)'
  { Symbol* gensymname = methodGensym("QUERY");

    return (listO(7, SYM_LOGIC_MACROS_LOGIC_APPLY_CACHED_ASK, listO(3, SYM_LOGIC_MACROS_STELLA_BQUOTE, body->value, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_BQUOTE, body->rest->value, NIL), cons(SYM_LOGIC_MACROS_STELLA_CONS_LIST, ((Cons*)(body->rest->rest->value))->concatenate(NIL, 0)), cons(SYM_LOGIC_MACROS_STELLA_CONS_LIST, body->nthRest(3)->concatenate(NIL, 0)), listO(3, SYM_LOGIC_MACROS_STELLA_QUOTE, gensymname, NIL), NIL));
  }
}

Object* withinMetaCache(Cons* body) {
  // Execute `body' within the meta cache of the current module.
  // Set appropriate special variables.
  return (listO(3, SYM_LOGIC_MACROS_STELLA_SPECIAL, cons(listO(3, SYM_LOGIC_MACROS_STELLA_oCONTEXTo, listO(4, SYM_LOGIC_MACROS_LOGIC_GET_INFERENCE_CACHE, SYM_LOGIC_MACROS_STELLA_oMODULEo, KWD_LOGIC_MACROS_META, NIL), NIL), NIL), body->concatenate(NIL, 0)));
}

Object* withinClassificationSession(Keyword* descriptionorinstance, Cons* body) {
  // Used during classification.  Execute `body' within the indicated
  // classification session and inference world.
  return (listO(3, SYM_LOGIC_MACROS_STELLA_SPECIAL, listO(3, listO(3, SYM_LOGIC_MACROS_LOGIC_oCLASSIFICATIONSESSIONo, listO(3, SYM_LOGIC_MACROS_LOGIC_GET_CLASSIFICATION_SESSION, descriptionorinstance, NIL), NIL), listO(3, SYM_LOGIC_MACROS_STELLA_oCONTEXTo, listO(3, SYM_LOGIC_MACROS_LOGIC_CLASSIFICATION_WORLD, SYM_LOGIC_MACROS_LOGIC_oCLASSIFICATIONSESSIONo, NIL), NIL), NIL), body->concatenate(NIL, 0)));
}

Object* defineComputedConstraint(Symbol* name, Cons* varList, Cons* constraintTest, Cons* positionComputations) {
  // Defines `name' to be a constraint computation which uses
  // `constraint-test' to determine if a fully bound set of variables
  // satisfies the constraint.  The forms in `position-computations'
  // are used to compute the value for each of the positions. All such
  // computations must set the variable `value' to be the result
  // computed for the missing position.  Setting `value' to `null' for
  // any such computation means that that particular argument cannot
  // be computed from the others.  The input variables in `var-list'
  // will be bound to the N arguments to the constraint.
  //   The generated function will return a Stella Object and take as 
  // inputs the values of the N arguments to the constraint.  A value
  // of `null' means that the value is not available.  If all
  // arguments are not `null', then the return value will be a Stella
  // wrapped boolean indicating whether the constraint is satisified
  // or not.
  //   If more than one input value is `null', then this constraint
  // code will not be called.
  { Cons* valuecomputationcode = NIL;
    Symbol* valuesymbol = internSymbol("VALUE");

    { Object* computation = NULL;
      Cons* iter000 = positionComputations;
      int i = NULL_INTEGER;
      int iter001 = 0;
      Cons* collect000 = NULL;

      for  (; !(iter000 == NIL); 
            iter000 = iter000->rest,
            iter001 = iter001 + 1) {
        computation = iter000->value;
        i = iter001;
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(cons(wrapInteger(i), cons(computation, NIL)), NIL);
            if (valuecomputationcode == NIL) {
              valuecomputationcode = collect000;
            }
            else {
              addConsToEndOfConsList(valuecomputationcode, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(cons(wrapInteger(i), cons(computation, NIL)), NIL);
            collect000 = collect000->rest;
          }
        }
      }
    }
    return (listO(5, SYM_LOGIC_MACROS_STELLA_DEFUN, cons(name, cons(SYM_LOGIC_MACROS_STELLA_OBJECT, NIL)), cons(listO(3, SYM_LOGIC_MACROS_LOGIC_MISSING_ARGUMENT, SYM_LOGIC_MACROS_STELLA_INTEGER_WRAPPER, NIL), varList->concatenate(NIL, 0)), listO(5, SYM_LOGIC_MACROS_STELLA_LET, cons(cons(valuesymbol, listO(3, SYM_LOGIC_MACROS_STELLA_OBJECT, SYM_LOGIC_MACROS_STELLA_NULL, NIL)), NIL), listO(4, SYM_LOGIC_MACROS_STELLA_CASE, listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_LOGIC_MISSING_ARGUMENT, NIL), listO(3, wrapInteger(-1), constraintTest, NIL), valuecomputationcode->concatenate(cons(listO(3, SYM_LOGIC_MACROS_STELLA_OTHERWISE, SYM_LOGIC_MACROS_STELLA_NULL, NIL), NIL), 0)), listO(3, SYM_LOGIC_MACROS_STELLA_RETURN, valuesymbol, NIL), NIL), NIL));
  }
}

Object* defineArithmeticTestOnWrappers(Symbol* name, Symbol* testName) {
  // Defines `name' as an arithmetic comparision operation using the
  // test `test-name'.  It will take two wrapped number parameters and
  // return a `boolean'.  The code will use the appropriate test for
  // the specific subtype of wrapped number actually passed in.
  return (listO(7, SYM_LOGIC_MACROS_STELLA_DEFUN, cons(name, cons(SYM_LOGIC_MACROS_STELLA_BOOLEAN, NIL)), listO(3, listO(3, SYM_LOGIC_MACROS_STELLA_X, SYM_LOGIC_MACROS_STELLA_NUMBER_WRAPPER, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_Y, SYM_LOGIC_MACROS_STELLA_NUMBER_WRAPPER, NIL), NIL), KWD_LOGIC_MACROS_PUBLICp, SYM_LOGIC_MACROS_STELLA_TRUE, listO(5, SYM_LOGIC_MACROS_STELLA_TYPECASE, SYM_LOGIC_MACROS_STELLA_X, listO(3, SYM_LOGIC_MACROS_STELLA_INTEGER_WRAPPER, listO(5, SYM_LOGIC_MACROS_STELLA_TYPECASE, SYM_LOGIC_MACROS_STELLA_Y, listO(3, SYM_LOGIC_MACROS_STELLA_INTEGER_WRAPPER, listO(3, SYM_LOGIC_MACROS_STELLA_RETURN, cons(testName, listO(3, listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_STELLA_X, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_STELLA_Y, NIL), NIL)), NIL), NIL), listO(3, SYM_LOGIC_MACROS_STELLA_FLOAT_WRAPPER, listO(3, SYM_LOGIC_MACROS_STELLA_RETURN, cons(testName, listO(3, listO(4, SYM_LOGIC_MACROS_STELLA_CAST, listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_STELLA_X, NIL), SYM_LOGIC_MACROS_STELLA_FLOAT, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_STELLA_Y, NIL), NIL)), NIL), NIL), NIL), NIL), listO(3, SYM_LOGIC_MACROS_STELLA_FLOAT_WRAPPER, listO(5, SYM_LOGIC_MACROS_STELLA_TYPECASE, SYM_LOGIC_MACROS_STELLA_Y, listO(3, SYM_LOGIC_MACROS_STELLA_INTEGER_WRAPPER, listO(3, SYM_LOGIC_MACROS_STELLA_RETURN, cons(testName, listO(3, listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_STELLA_X, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_CAST, listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_STELLA_Y, NIL), SYM_LOGIC_MACROS_STELLA_FLOAT, NIL), NIL)), NIL), NIL), listO(3, SYM_LOGIC_MACROS_STELLA_FLOAT_WRAPPER, listO(3, SYM_LOGIC_MACROS_STELLA_RETURN, cons(testName, listO(3, listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_STELLA_X, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_STELLA_Y, NIL), NIL)), NIL), NIL), NIL), NIL), NIL), NIL));
}

Object* defineArithmeticOperationOnWrappers(Symbol* name, Symbol* operationName) {
  // Defines `name' as an arithmetic comparision operation using the
  // test `test-name'.  It will take two wrapped number parameters and
  // return a wrapped number.  The code will use the appropriate test
  // for the specific subtype of wrapped number actually passed in,
  // and return the appropriate subtype of wrapped number based on the
  // normal arithmetic contagion rules.
  //   
  // For example, if both input parameters are wrapped integers then
  // the output will be a wrapped integer.  If the inputs are a
  // wrapped integer and a wrapped float then the output will be a
  // wrapped float, etc.
  return (listO(7, SYM_LOGIC_MACROS_STELLA_DEFUN, cons(name, cons(SYM_LOGIC_MACROS_STELLA_NUMBER_WRAPPER, NIL)), listO(3, listO(3, SYM_LOGIC_MACROS_STELLA_X, SYM_LOGIC_MACROS_STELLA_NUMBER_WRAPPER, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_Y, SYM_LOGIC_MACROS_STELLA_NUMBER_WRAPPER, NIL), NIL), KWD_LOGIC_MACROS_PUBLICp, SYM_LOGIC_MACROS_STELLA_TRUE, listO(5, SYM_LOGIC_MACROS_STELLA_LET, cons(listO(4, SYM_LOGIC_MACROS_LOGIC_FLOATRESULT, SYM_LOGIC_MACROS_STELLA_FLOAT, SYM_LOGIC_MACROS_STELLA_NULL, NIL), NIL), listO(5, SYM_LOGIC_MACROS_STELLA_TYPECASE, SYM_LOGIC_MACROS_STELLA_X, listO(3, SYM_LOGIC_MACROS_STELLA_INTEGER_WRAPPER, listO(5, SYM_LOGIC_MACROS_STELLA_TYPECASE, SYM_LOGIC_MACROS_STELLA_Y, listO(3, SYM_LOGIC_MACROS_STELLA_INTEGER_WRAPPER, listO(3, SYM_LOGIC_MACROS_STELLA_RETURN, listO(3, SYM_LOGIC_MACROS_STELLA_WRAP_LITERAL, listO(4, SYM_LOGIC_MACROS_STELLA_SAFE_CAST, cons(operationName, listO(3, listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_STELLA_X, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_STELLA_Y, NIL), NIL)), SYM_LOGIC_MACROS_STELLA_INTEGER, NIL), NIL), NIL), NIL), listO(3, SYM_LOGIC_MACROS_STELLA_FLOAT_WRAPPER, listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_LOGIC_FLOATRESULT, cons(operationName, listO(3, listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_STELLA_X, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_STELLA_Y, NIL), NIL)), NIL), NIL), NIL), NIL), listO(3, SYM_LOGIC_MACROS_STELLA_FLOAT_WRAPPER, listO(4, SYM_LOGIC_MACROS_STELLA_TYPECASE, SYM_LOGIC_MACROS_STELLA_Y, listO(3, listO(3, SYM_LOGIC_MACROS_STELLA_INTEGER_WRAPPER, SYM_LOGIC_MACROS_STELLA_FLOAT_WRAPPER, NIL), listO(4, SYM_LOGIC_MACROS_STELLA_SETQ, SYM_LOGIC_MACROS_LOGIC_FLOATRESULT, cons(operationName, listO(3, listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_STELLA_X, NIL), listO(3, SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE, SYM_LOGIC_MACROS_STELLA_Y, NIL), NIL)), NIL), NIL), NIL), NIL), NIL), listO(3, SYM_LOGIC_MACROS_STELLA_RETURN, listO(3, SYM_LOGIC_MACROS_STELLA_WRAP_LITERAL, SYM_LOGIC_MACROS_LOGIC_FLOATRESULT, NIL), NIL), NIL), NIL));
}

Object* withLogicEnvironment(Object* moduleform, Object* environment, Cons* body) {
  // Execute `body' within the module resulting from `moduleForm'.
  // `*module*' or NULL are acceptable `moduleForm's.  It will locally rebind 
  // `*module*' and `*context*' and shield the outer bindings from changes.
  return (listO(3, SYM_LOGIC_MACROS_STELLA_SPECIAL, listO(3, listO(3, SYM_LOGIC_MACROS_STELLA_oMODULEo, listO(3, SYM_LOGIC_MACROS_STELLA_FIRST_DEFINED, moduleform, cons(SYM_LOGIC_MACROS_STELLA_oMODULEo, NIL)), NIL), listO(3, SYM_LOGIC_MACROS_STELLA_oCONTEXTo, SYM_LOGIC_MACROS_STELLA_oMODULEo, NIL), NIL), (((symbolP(environment) &&
      (!(environment == SYM_LOGIC_MACROS_STELLA_NULL))) ? cons(listO(3, SYM_LOGIC_MACROS_STELLA_IGNORE, environment, NIL), NIL) : NIL))->concatenate(cons(listO(3, SYM_LOGIC_MACROS_STELLA_WITH_PROCESS_LOCK, SYM_LOGIC_MACROS_LOGIC_oPOWERLOOM_LOCKo, body->concatenate(NIL, 0)), NIL), 0)));
}

boolean oCYC_KLUDGES_ENABLEDpo = false;

Object* whenCycKludgesEnabled(Cons* body) {
  return (listO(3, SYM_LOGIC_MACROS_STELLA_WHEN, SYM_LOGIC_MACROS_LOGIC_oCYC_KLUDGES_ENABLEDpo, body->concatenate(NIL, 0)));
}

boolean oDATA_FINDER_KLUDGES_ENABLEDpo = false;

Object* whenDataFinderKludgesEnabled(Cons* body) {
  return (listO(3, SYM_LOGIC_MACROS_STELLA_WHEN, SYM_LOGIC_MACROS_LOGIC_oDATA_FINDER_KLUDGES_ENABLEDpo, body->concatenate(NIL, 0)));
}

void helpStartupLogicMacros1() {
  {
    { Module* stellamodule = oSTELLA_MODULEo;
      Module* logicmodule = getStellaModule("LOGIC", true);
      Module* plkernelmodule = getStellaModule("PL-KERNEL", true);

      internSurrogateInModule("PROPOSITION.IF", stellamodule, true);
      internSurrogateInModule("=", stellamodule, true);
      importSymbol(lookupSymbolInModule("=", stellamodule, true), plkernelmodule);
      importSurrogate(lookupSurrogateInModule("=", stellamodule, true), plkernelmodule);
      { Object* name = NULL;
        Cons* iter000 = getQuotedTree("((\"LISTOF\" \"SETOF\") \"/LOGIC\")", "/LOGIC");

        for (; !(iter000 == NIL); iter000 = iter000->rest) {
          name = iter000->value;
          { StringWrapper* sname = ((StringWrapper*)(name));
            Symbol* plkernelsym = internSymbolInModule(sname->wrapperValue, plkernelmodule, true);
            Surrogate* plkernelsgt = internSurrogateInModule(sname->wrapperValue, plkernelmodule, true);

            importSymbol(plkernelsym, logicmodule);
            importSurrogate(plkernelsgt, logicmodule);
          }
        }
      }
    }
    SYM_LOGIC_MACROS_STELLA_LET = ((Symbol*)(internRigidSymbolWrtModule("LET", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_NEW = ((Symbol*)(internRigidSymbolWrtModule("NEW", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_OUTPUT_STRING_STREAM = ((Symbol*)(internRigidSymbolWrtModule("OUTPUT-STRING-STREAM", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_SPECIAL = ((Symbol*)(internRigidSymbolWrtModule("SPECIAL", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_oPRINTREADABLYpo = ((Symbol*)(internRigidSymbolWrtModule("*PRINTREADABLY?*", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_PRINT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("PRINT-STREAM", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_EOL = ((Symbol*)(internRigidSymbolWrtModule("EOL", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_HELP_SIGNAL_PROPOSITION_ERROR = ((Symbol*)(internRigidSymbolWrtModule("HELP-SIGNAL-PROPOSITION-ERROR", NULL, 0)));
    KWD_LOGIC_MACROS_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    SYM_LOGIC_MACROS_STELLA_SIGNAL_EXCEPTION = ((Symbol*)(internRigidSymbolWrtModule("SIGNAL-EXCEPTION", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_PARSING_ERROR = ((Symbol*)(internRigidSymbolWrtModule("PARSING-ERROR", NULL, 0)));
    KWD_LOGIC_MACROS_MESSAGE = ((Keyword*)(internRigidSymbolWrtModule("MESSAGE", NULL, 2)));
    SYM_LOGIC_MACROS_STELLA_THE_STRING = ((Symbol*)(internRigidSymbolWrtModule("THE-STRING", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_PROPOSITION_ERROR = ((Symbol*)(internRigidSymbolWrtModule("PROPOSITION-ERROR", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_STANDARD_WARNING = ((Symbol*)(internRigidSymbolWrtModule("STANDARD-WARNING", getStellaModule("/STELLA", true), 0)));
    KWD_LOGIC_MACROS_WARNING = ((Keyword*)(internRigidSymbolWrtModule("WARNING", NULL, 2)));
    SYM_LOGIC_MACROS_STELLA_DEFUN = ((Symbol*)(internRigidSymbolWrtModule("DEFUN", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_STRING = ((Symbol*)(internRigidSymbolWrtModule("STRING", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_PRINT = ((Symbol*)(internRigidSymbolWrtModule("PRINT", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_RETURN = ((Symbol*)(internRigidSymbolWrtModule("RETURN", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("PROGN", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_SETF = ((Symbol*)(internRigidSymbolWrtModule("SETF", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_TRUTH_VALUE = ((Symbol*)(internRigidSymbolWrtModule("TRUTH-VALUE", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_FRAME = ((Symbol*)(internRigidSymbolWrtModule("FRAME", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_JUSTIFICATION = ((Symbol*)(internRigidSymbolWrtModule("JUSTIFICATION", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_WHEN = ((Symbol*)(internRigidSymbolWrtModule("WHEN", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_DEFINEDp = ((Symbol*)(internRigidSymbolWrtModule("DEFINED?", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_PARTIAL_MATCH_FRAME = ((Symbol*)(internRigidSymbolWrtModule("PARTIAL-MATCH-FRAME", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_CLEAR_FRAME_PARTIAL_TRUTH = ((Symbol*)(internRigidSymbolWrtModule("CLEAR-FRAME-PARTIAL-TRUTH", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_LASTMOVE = ((Symbol*)(internRigidSymbolWrtModule("LASTMOVE", NULL, 0)));
    KWD_LOGIC_MACROS_DOWN = ((Keyword*)(internRigidSymbolWrtModule("DOWN", NULL, 2)));
    SYM_LOGIC_MACROS_STELLA_COND = ((Symbol*)(internRigidSymbolWrtModule("COND", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_CHECKFORMOVEOUTp = ((Symbol*)(internRigidSymbolWrtModule("CHECKFORMOVEOUT?", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_PARENT = ((Symbol*)(internRigidSymbolWrtModule("PARENT", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_UP = ((Symbol*)(internRigidSymbolWrtModule("UP", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_STARTTICKS = ((Symbol*)(internRigidSymbolWrtModule("STARTTICKS", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_STARTING_CLOCK_TICKS = ((Symbol*)(internRigidSymbolWrtModule("STARTING-CLOCK-TICKS", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_AVAILABLETICKS = ((Symbol*)(internRigidSymbolWrtModule("AVAILABLETICKS", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA__ = ((Symbol*)(internRigidSymbolWrtModule("-", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS = ((Symbol*)(internRigidSymbolWrtModule("ALLOTTED-CLOCK-TICKS", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_CLOCKTICKS = ((Symbol*)(internRigidSymbolWrtModule("CLOCKTICKS", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA___ = ((Symbol*)(internRigidSymbolWrtModule("--", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_CURRENT_CLOCK_TICKS = ((Symbol*)(internRigidSymbolWrtModule("CURRENT-CLOCK-TICKS", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_QUERY = ((Symbol*)(internRigidSymbolWrtModule("QUERY", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_ii = ((Symbol*)(internRigidSymbolWrtModule("++", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_le = ((Symbol*)(internRigidSymbolWrtModule("<=", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_POP_FRAMES_UP_TO = ((Symbol*)(internRigidSymbolWrtModule("POP-FRAMES-UP-TO", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_MV_SETQ = ((Symbol*)(internRigidSymbolWrtModule("MV-SETQ", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_DEPTH = ((Symbol*)(internRigidSymbolWrtModule("DEPTH", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_HANDLE_TIMEOUT = ((Symbol*)(internRigidSymbolWrtModule("HANDLE-TIMEOUT", NULL, 0)));
    KWD_LOGIC_MACROS_UP_FAIL = ((Keyword*)(internRigidSymbolWrtModule("UP-FAIL", NULL, 2)));
    SYM_LOGIC_MACROS_STELLA_1i = ((Symbol*)(internRigidSymbolWrtModule("1+", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_OTHERWISE = ((Symbol*)(internRigidSymbolWrtModule("OTHERWISE", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_UPFRAME = ((Symbol*)(internRigidSymbolWrtModule("UPFRAME", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_DOWNFRAME = ((Symbol*)(internRigidSymbolWrtModule("DOWNFRAME", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_DOWN = ((Symbol*)(internRigidSymbolWrtModule("DOWN", NULL, 0)));
  }
}

void helpStartupLogicMacros2() {
  {
    SYM_LOGIC_MACROS_STELLA_AND = ((Symbol*)(internRigidSymbolWrtModule("AND", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_NULLp = ((Symbol*)(internRigidSymbolWrtModule("NULL?", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_1_ = ((Symbol*)(internRigidSymbolWrtModule("1-", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_PROPOSITION = ((Symbol*)(internRigidSymbolWrtModule("PROPOSITION", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_ARGUMENT_BOUND_TO = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENT-BOUND-TO", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_NTH = ((Symbol*)(internRigidSymbolWrtModule("NTH", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_ARGUMENTS = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENTS", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_ARGUMENT_CURSOR = ((Symbol*)(internRigidSymbolWrtModule("ARGUMENT-CURSOR", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_CREATE_DOWN_FRAME = ((Symbol*)(internRigidSymbolWrtModule("CREATE-DOWN-FRAME", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_g = ((Symbol*)(internRigidSymbolWrtModule(">", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_CURRENT_DEPTH_CUTOFF = ((Symbol*)(internRigidSymbolWrtModule("CURRENT-DEPTH-CUTOFF", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_EQLp = ((Symbol*)(internRigidSymbolWrtModule("EQL?", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_STATE = ((Symbol*)(internRigidSymbolWrtModule("STATE", getStellaModule("/STELLA", true), 0)));
    KWD_LOGIC_MACROS_PATTERN = ((Keyword*)(internRigidSymbolWrtModule("PATTERN", NULL, 2)));
    SYM_LOGIC_MACROS_LOGIC_HANDLE_DEPTH_VIOLATION = ((Symbol*)(internRigidSymbolWrtModule("HANDLE-DEPTH-VIOLATION", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_FAIL = ((Symbol*)(internRigidSymbolWrtModule("FAIL", NULL, 0)));
    KWD_LOGIC_MACROS_UP_TRUE = ((Keyword*)(internRigidSymbolWrtModule("UP-TRUE", NULL, 2)));
    SYM_LOGIC_MACROS_STELLA_FALSE = ((Symbol*)(internRigidSymbolWrtModule("FALSE", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_RESULT = ((Symbol*)(internRigidSymbolWrtModule("RESULT", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_IF = ((Symbol*)(internRigidSymbolWrtModule("IF", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_CACHE_QUERY_RESULTSp = ((Symbol*)(internRigidSymbolWrtModule("CACHE-QUERY-RESULTS?", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_CACHE_GOAL = ((Symbol*)(internRigidSymbolWrtModule("CACHE-GOAL", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_UPDATE_GOAL_CACHE = ((Symbol*)(internRigidSymbolWrtModule("UPDATE-GOAL-CACHE", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_SUCCESSp = ((Symbol*)(internRigidSymbolWrtModule("SUCCESS?", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_BREAK = ((Symbol*)(internRigidSymbolWrtModule("BREAK", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_KEEP_FRAME = ((Symbol*)(internRigidSymbolWrtModule("KEEP-FRAME", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_POP_DOWN_FRAME = ((Symbol*)(internRigidSymbolWrtModule("POP-DOWN-FRAME", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_APPLY_CACHED_RETRIEVE = ((Symbol*)(internRigidSymbolWrtModule("APPLY-CACHED-RETRIEVE", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_BQUOTE = ((Symbol*)(internRigidSymbolWrtModule("BQUOTE", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_CONS_LIST = ((Symbol*)(internRigidSymbolWrtModule("CONS-LIST", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_QUOTE = ((Symbol*)(internRigidSymbolWrtModule("QUOTE", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_APPLY_CACHED_ASK = ((Symbol*)(internRigidSymbolWrtModule("APPLY-CACHED-ASK", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_oCONTEXTo = ((Symbol*)(internRigidSymbolWrtModule("*CONTEXT*", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_GET_INFERENCE_CACHE = ((Symbol*)(internRigidSymbolWrtModule("GET-INFERENCE-CACHE", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_oMODULEo = ((Symbol*)(internRigidSymbolWrtModule("*MODULE*", getStellaModule("/STELLA", true), 0)));
    KWD_LOGIC_MACROS_META = ((Keyword*)(internRigidSymbolWrtModule("META", NULL, 2)));
    SYM_LOGIC_MACROS_LOGIC_oCLASSIFICATIONSESSIONo = ((Symbol*)(internRigidSymbolWrtModule("*CLASSIFICATIONSESSION*", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_GET_CLASSIFICATION_SESSION = ((Symbol*)(internRigidSymbolWrtModule("GET-CLASSIFICATION-SESSION", NULL, 0)));
    SYM_LOGIC_MACROS_LOGIC_CLASSIFICATION_WORLD = ((Symbol*)(internRigidSymbolWrtModule("CLASSIFICATION-WORLD", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_OBJECT = ((Symbol*)(internRigidSymbolWrtModule("OBJECT", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_MISSING_ARGUMENT = ((Symbol*)(internRigidSymbolWrtModule("MISSING-ARGUMENT", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_INTEGER_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("INTEGER-WRAPPER", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_CASE = ((Symbol*)(internRigidSymbolWrtModule("CASE", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE = ((Symbol*)(internRigidSymbolWrtModule("WRAPPER-VALUE", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_BOOLEAN = ((Symbol*)(internRigidSymbolWrtModule("BOOLEAN", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_X = ((Symbol*)(internRigidSymbolWrtModule("X", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_NUMBER_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("NUMBER-WRAPPER", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_Y = ((Symbol*)(internRigidSymbolWrtModule("Y", getStellaModule("/STELLA", true), 0)));
    KWD_LOGIC_MACROS_PUBLICp = ((Keyword*)(internRigidSymbolWrtModule("PUBLIC?", NULL, 2)));
    SYM_LOGIC_MACROS_STELLA_TYPECASE = ((Symbol*)(internRigidSymbolWrtModule("TYPECASE", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_FLOAT_WRAPPER = ((Symbol*)(internRigidSymbolWrtModule("FLOAT-WRAPPER", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_CAST = ((Symbol*)(internRigidSymbolWrtModule("CAST", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_FLOAT = ((Symbol*)(internRigidSymbolWrtModule("FLOAT", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_LOGIC_FLOATRESULT = ((Symbol*)(internRigidSymbolWrtModule("FLOATRESULT", NULL, 0)));
    SYM_LOGIC_MACROS_STELLA_WRAP_LITERAL = ((Symbol*)(internRigidSymbolWrtModule("WRAP-LITERAL", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_SAFE_CAST = ((Symbol*)(internRigidSymbolWrtModule("SAFE-CAST", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_INTEGER = ((Symbol*)(internRigidSymbolWrtModule("INTEGER", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_FIRST_DEFINED = ((Symbol*)(internRigidSymbolWrtModule("FIRST-DEFINED", getStellaModule("/STELLA", true), 0)));
    SYM_LOGIC_MACROS_STELLA_WITH_PROCESS_LOCK = ((Symbol*)(internRigidSymbolWrtModule("WITH-PROCESS-LOCK", getStellaModule("/STELLA", true), 0)));
  }
}

void startupLogicMacros() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, getStellaModule("/LOGIC", oSTARTUP_TIME_PHASEo > 1));
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupLogicMacros1();
      helpStartupLogicMacros2();
      SYM_LOGIC_MACROS_LOGIC_oPOWERLOOM_LOCKo = ((Symbol*)(internRigidSymbolWrtModule("*POWERLOOM-LOCK*", NULL, 0)));
      SYM_LOGIC_MACROS_STELLA_IGNORE = ((Symbol*)(internRigidSymbolWrtModule("IGNORE", getStellaModule("/STELLA", true), 0)));
      SYM_LOGIC_MACROS_LOGIC_oCYC_KLUDGES_ENABLEDpo = ((Symbol*)(internRigidSymbolWrtModule("*CYC-KLUDGES-ENABLED?*", NULL, 0)));
      SYM_LOGIC_MACROS_LOGIC_oDATA_FINDER_KLUDGES_ENABLEDpo = ((Symbol*)(internRigidSymbolWrtModule("*DATA-FINDER-KLUDGES-ENABLED?*", NULL, 0)));
      SYM_LOGIC_MACROS_LOGIC_STARTUP_LOGIC_MACROS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-LOGIC-MACROS", NULL, 0)));
      SYM_LOGIC_MACROS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", getStellaModule("/STELLA", true), 0)));
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      defineFunctionObject("SIGNAL-PARSING-ERROR", "(DEFUN SIGNAL-PARSING-ERROR (|&BODY| (MESSAGE CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&signalParsingError)), NULL);
      defineFunctionObject("SIGNAL-PROPOSITION-ERROR", "(DEFUN SIGNAL-PROPOSITION-ERROR (|&BODY| (MESSAGE CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&signalPropositionError)), NULL);
      defineFunctionObject("SIGNAL-PROPOSITION-WARNING", "(DEFUN SIGNAL-PROPOSITION-WARNING (|&BODY| (MESSAGE CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&signalPropositionWarning)), NULL);
      defineFunctionObject("DEF-DISPLAY-GLOBALS", "(DEFUN DEF-DISPLAY-GLOBALS ((DISPLAYFUNCTIONNAME SYMBOL) (GLOBALVARIABLENAMES (CONS OF SYMBOL))) :TYPE OBJECT :MACRO? TRUE :LISP-MACRO? TRUE)", ((cpp_function_code)(&defDisplayGlobals)), NULL);
      defineFunctionObject("MOVE-IN-PLACE", "(DEFUN MOVE-IN-PLACE () :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&moveInPlace)), NULL);
      defineFunctionObject("MOVE-DOWN", "(DEFUN MOVE-DOWN () :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&moveDown)), NULL);
      defineFunctionObject("MOVE-UP", "(DEFUN MOVE-UP ((SUCCESS? SYMBOL) (KEEPFRAME? SYMBOL)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&moveUp)), NULL);
      defineFunctionObject("APPLY-RETRIEVE", "(DEFUN APPLY-RETRIEVE (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Execute a query composed of io-variables `variables'\nand body `queryBody'.  Before executing, bind variables to `inputBindings'\n(in sequence). If one variable is left unbound, returns a cons list of\nbindings of that variable.  If two or more are unbound, returns\na cons list of cons lists of bindings.  Setting the option :singletons?\nto FALSE always returns a list of lists.  Example call:\n  `(apply-retrieve variables queryBody inputBindings)'\")", ((cpp_function_code)(&applyRetrieve)), NULL);
      defineFunctionObject("APPLY-ASK", "(DEFUN APPLY-ASK (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Execute a yes/no query composed of input-variables\n`inputVariables' and body `queryBody'.  Before executing, bind variables\nto `inputBindings' (in sequence).\n  `(apply-ask inputVariables queryBody inputBindings)'\")", ((cpp_function_code)(&applyAsk)), NULL);
      defineFunctionObject("WITHIN-META-CACHE", "(DEFUN WITHIN-META-CACHE (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Execute `body' within the meta cache of the current module.\nSet appropriate special variables.\")", ((cpp_function_code)(&withinMetaCache)), NULL);
      defineFunctionObject("WITHIN-CLASSIFICATION-SESSION", "(DEFUN WITHIN-CLASSIFICATION-SESSION ((DESCRIPTIONORINSTANCE KEYWORD) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Used during classification.  Execute `body' within the indicated\nclassification session and inference world.\")", ((cpp_function_code)(&withinClassificationSession)), NULL);
      defineFunctionObject("DEFINE-COMPUTED-CONSTRAINT", "(DEFUN DEFINE-COMPUTED-CONSTRAINT ((NAME SYMBOL) (VAR-LIST CONS) (CONSTRAINT-TEST CONS) |&BODY| (POSITION-COMPUTATIONS CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Defines `name' to be a constraint computation which uses\n`constraint-test' to determine if a fully bound set of variables\nsatisfies the constraint.  The forms in `position-computations'\nare used to compute the value for each of the positions. All such\ncomputations must set the variable `value' to be the result\ncomputed for the missing position.  Setting `value' to `null' for\nany such computation means that that particular argument cannot\nbe computed from the others.  The input variables in `var-list'\nwill be bound to the N arguments to the constraint.\n  The generated function will return a Stella Object and take as \ninputs the values of the N arguments to the constraint.  A value\nof `null' means that the value is not available.  If all\narguments are not `null', then the return value will be a Stella\nwrapped boolean " "indicating whether the constraint is satisified\nor not.\n  If more than one input value is `null', then this constraint\ncode will not be called.\")", ((cpp_function_code)(&defineComputedConstraint)), NULL);
      defineFunctionObject("DEFINE-ARITHMETIC-TEST-ON-WRAPPERS", "(DEFUN DEFINE-ARITHMETIC-TEST-ON-WRAPPERS ((NAME SYMBOL) (TEST-NAME SYMBOL)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Defines `name' as an arithmetic comparision operation using the\ntest `test-name'.  It will take two wrapped number parameters and\nreturn a `boolean'.  The code will use the appropriate test for\nthe specific subtype of wrapped number actually passed in.\")", ((cpp_function_code)(&defineArithmeticTestOnWrappers)), NULL);
      defineFunctionObject("DEFINE-ARITHMETIC-OPERATION-ON-WRAPPERS", "(DEFUN DEFINE-ARITHMETIC-OPERATION-ON-WRAPPERS ((NAME SYMBOL) (OPERATION-NAME SYMBOL)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Defines `name' as an arithmetic comparision operation using the\ntest `test-name'.  It will take two wrapped number parameters and\nreturn a wrapped number.  The code will use the appropriate test\nfor the specific subtype of wrapped number actually passed in,\nand return the appropriate subtype of wrapped number based on the\nnormal arithmetic contagion rules.\n  \nFor example, if both input parameters are wrapped integers then\nthe output will be a wrapped integer.  If the inputs are a\nwrapped integer and a wrapped float then the output will be a\nwrapped float, etc.\")", ((cpp_function_code)(&defineArithmeticOperationOnWrappers)), NULL);
      defineFunctionObject("WITH-LOGIC-ENVIRONMENT", "(DEFUN WITH-LOGIC-ENVIRONMENT ((MODULEFORM OBJECT) (ENVIRONMENT OBJECT) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :DOCUMENTATION \"Execute `body' within the module resulting from `moduleForm'.\n`*module*' or NULL are acceptable `moduleForm's.  It will locally rebind \n`*module*' and `*context*' and shield the outer bindings from changes.\" :PUBLIC? TRUE)", ((cpp_function_code)(&withLogicEnvironment)), NULL);
      defineFunctionObject("WHEN-CYC-KLUDGES-ENABLED", "(DEFUN WHEN-CYC-KLUDGES-ENABLED (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&whenCycKludgesEnabled)), NULL);
      defineFunctionObject("WHEN-DATA-FINDER-KLUDGES-ENABLED", "(DEFUN WHEN-DATA-FINDER-KLUDGES-ENABLED (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&whenDataFinderKludgesEnabled)), NULL);
      defineFunctionObject("STARTUP-LOGIC-MACROS", "(DEFUN STARTUP-LOGIC-MACROS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupLogicMacros)), NULL);
      { MethodSlot* function = lookupFunction(SYM_LOGIC_MACROS_LOGIC_STARTUP_LOGIC_MACROS);

        setDynamicSlotValue(function->dynamicSlots, SYM_LOGIC_MACROS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupLogicMacros"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("LOGIC")))));
      defineGlobalVariableObject("(DEFSPECIAL *SUPPRESSNONLOGICOBJECTWARNING?* BOOLEAN TRUE)", &oSUPPRESSNONLOGICOBJECTWARNINGpo);
      defineGlobalVariableObject("(DEFGLOBAL *CYC-KLUDGES-ENABLED?* BOOLEAN FALSE)", &oCYC_KLUDGES_ENABLEDpo);
      defineGlobalVariableObject("(DEFGLOBAL *DATA-FINDER-KLUDGES-ENABLED?* BOOLEAN FALSE)", &oDATA_FINDER_KLUDGES_ENABLEDpo);
    }
  }
}

Symbol* SYM_LOGIC_MACROS_STELLA_LET = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_NEW = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_OUTPUT_STRING_STREAM = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_SPECIAL = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_oPRINTREADABLYpo = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_TRUE = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_PRINT_STREAM = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_EOL = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_HELP_SIGNAL_PROPOSITION_ERROR = NULL;

Keyword* KWD_LOGIC_MACROS_ERROR = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_SIGNAL_EXCEPTION = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_PARSING_ERROR = NULL;

Keyword* KWD_LOGIC_MACROS_MESSAGE = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_THE_STRING = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_PROPOSITION_ERROR = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_STANDARD_WARNING = NULL;

Keyword* KWD_LOGIC_MACROS_WARNING = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_DEFUN = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_STRING = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_PRINT = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_RETURN = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_PROGN = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_SETF = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_TRUTH_VALUE = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_FRAME = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_NULL = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_JUSTIFICATION = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_WHEN = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_DEFINEDp = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_PARTIAL_MATCH_FRAME = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_CLEAR_FRAME_PARTIAL_TRUTH = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_SETQ = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_LASTMOVE = NULL;

Keyword* KWD_LOGIC_MACROS_DOWN = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_COND = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_CHECKFORMOVEOUTp = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_PARENT = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_UP = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_STARTTICKS = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_STARTING_CLOCK_TICKS = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_AVAILABLETICKS = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA__ = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_ALLOTTED_CLOCK_TICKS = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_CLOCKTICKS = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA___ = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_CURRENT_CLOCK_TICKS = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_QUERY = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_ii = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_le = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_POP_FRAMES_UP_TO = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_MV_SETQ = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_DEPTH = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_HANDLE_TIMEOUT = NULL;

Keyword* KWD_LOGIC_MACROS_UP_FAIL = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_1i = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_OTHERWISE = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_UPFRAME = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_DOWNFRAME = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_DOWN = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_AND = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_NULLp = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_1_ = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_PROPOSITION = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_ARGUMENT_BOUND_TO = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_NTH = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_ARGUMENTS = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_ARGUMENT_CURSOR = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_CREATE_DOWN_FRAME = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_g = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_CURRENT_DEPTH_CUTOFF = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_EQLp = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_STATE = NULL;

Keyword* KWD_LOGIC_MACROS_PATTERN = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_HANDLE_DEPTH_VIOLATION = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_NOT = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_FAIL = NULL;

Keyword* KWD_LOGIC_MACROS_UP_TRUE = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_FALSE = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_RESULT = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_IF = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_CACHE_QUERY_RESULTSp = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_CACHE_GOAL = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_UPDATE_GOAL_CACHE = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_SUCCESSp = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_BREAK = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_KEEP_FRAME = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_POP_DOWN_FRAME = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_APPLY_CACHED_RETRIEVE = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_BQUOTE = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_CONS_LIST = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_QUOTE = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_APPLY_CACHED_ASK = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_oCONTEXTo = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_GET_INFERENCE_CACHE = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_oMODULEo = NULL;

Keyword* KWD_LOGIC_MACROS_META = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_oCLASSIFICATIONSESSIONo = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_GET_CLASSIFICATION_SESSION = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_CLASSIFICATION_WORLD = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_OBJECT = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_MISSING_ARGUMENT = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_INTEGER_WRAPPER = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_CASE = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_WRAPPER_VALUE = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_BOOLEAN = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_X = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_NUMBER_WRAPPER = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_Y = NULL;

Keyword* KWD_LOGIC_MACROS_PUBLICp = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_TYPECASE = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_FLOAT_WRAPPER = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_CAST = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_FLOAT = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_FLOATRESULT = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_WRAP_LITERAL = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_SAFE_CAST = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_INTEGER = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_FIRST_DEFINED = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_WITH_PROCESS_LOCK = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_oPOWERLOOM_LOCKo = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_IGNORE = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_oCYC_KLUDGES_ENABLEDpo = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_oDATA_FINDER_KLUDGES_ENABLEDpo = NULL;

Symbol* SYM_LOGIC_MACROS_LOGIC_STARTUP_LOGIC_MACROS = NULL;

Symbol* SYM_LOGIC_MACROS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace logic
