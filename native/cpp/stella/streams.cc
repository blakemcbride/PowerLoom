//  -*- Mode: C++ -*-

// streams.cc

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

#include "stella/stella-system.hh"

namespace stella {

// Generates a newline character when passed to a stream.
Symbol* EOL = NULL;

// A string constant containing the character sequence
// necessary to generate a newline.
const char* EOL_STRING = "\n";

// For STELLA we always assume an 8-bit transparent mapping from bytes to STRING characters
// such as ISO-8859-1 (ISO-LATIN-1), since that's what C++ natively supports.  For Java and some Lisps, we have
// to do some extra work to enforce this encoding when creating streams.  This is just a first iteration towards
// this handling this, for example, in Lisp we'd also have to configure compile and load streams to properly encode
// string constants that contain non-ASCII characters.
void* STELLA_CHARSET = NULL;

// Denotes the standard input stream for the host language.
InputStream* STANDARD_INPUT = NULL;

OutputStream* makeEarlyOutputStream(std::ostream* nativestream) {
  gcInitialize();
  { OutputStream* stream = newOutputStream();

    stream->nativeStream = nativestream;
    *nativestream << std::setprecision(16);
    return (stream);
  }
}

// Denotes the standard output stream for the host language.
OutputStream* STANDARD_OUTPUT = makeEarlyOutputStream(&std::cout);

// Denotes the standard warning stream for the host language.
OutputStream* STANDARD_WARNING = makeEarlyOutputStream(&std::cerr);

// Denotes the standard error stream for the host language.
OutputStream* STANDARD_ERROR = makeEarlyOutputStream(&std::cerr);

// If `true' all passes of a translation will always be performed
// regardless of whether any errors were encountered.  Otherwise, translation
// ends with the first pass that encountered an error.
DEFINE_STELLA_SPECIAL(oIGNORETRANSLATIONERRORSpo, boolean , true);

// Holds a string containing the single quote character.
StringWrapper* SINGLE_QUOTE_STRING = NULL;

// Holds a string containing the single backquote character.
StringWrapper* SINGLE_BQUOTE_STRING = NULL;

Cons* formatMessageArguments(Cons* messageargumentstree, boolean trailingeolP) {
  { Cons* augmentedarguments = NIL;

    { Object* item = NULL;
      Cons* iter000 = messageargumentstree;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        item = iter000->value;
        if (stringP(item) ||
            (item == EOL)) {
          augmentedarguments = cons(item, augmentedarguments);
        }
        else {
          augmentedarguments = cons(SINGLE_BQUOTE_STRING, augmentedarguments);
          augmentedarguments = cons(item, augmentedarguments);
          augmentedarguments = cons(SINGLE_QUOTE_STRING, augmentedarguments);
        }
      }
    }
    if (trailingeolP) {
      augmentedarguments = cons(EOL, augmentedarguments);
    }
    return (augmentedarguments->reverse());
  }
}

Object* print(Cons* body) {
  // Print arguments to the standard output stream.
  return (listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, SYM_STREAMS_STELLA_STANDARD_OUTPUT, body->concatenate(NIL, 0)));
}

Object* printSpaces(Cons* body) {
  // (print-spaces [stream] N) prints N spaces onto stream.  If
  // no stream form is provided, then STANDARD-OUTPUT will be used.
  if (body->rest == NIL) {
    return (listO(8, SYM_STREAMS_STELLA_FOREACH, SYM_STREAMS_STELLA_I, SYM_STREAMS_STELLA_IN, listO(4, SYM_STREAMS_STELLA_INTERVAL, wrapInteger(1), body->value, NIL), SYM_STREAMS_STELLA_DO, listO(3, SYM_STREAMS_STELLA_IGNORE, SYM_STREAMS_STELLA_I, NIL), listO(4, SYM_STREAMS_STELLA_PRINT_STREAM, SYM_STREAMS_STELLA_STANDARD_OUTPUT, wrapString(" "), NIL), NIL));
  }
  else {
    return (listO(8, SYM_STREAMS_STELLA_FOREACH, SYM_STREAMS_STELLA_I, SYM_STREAMS_STELLA_IN, listO(4, SYM_STREAMS_STELLA_INTERVAL, wrapInteger(1), body->rest->value, NIL), SYM_STREAMS_STELLA_DO, listO(3, SYM_STREAMS_STELLA_IGNORE, SYM_STREAMS_STELLA_I, NIL), listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, body->value, cons(wrapString(" "), NIL)), NIL));
  }
}

Object* inform(Cons* body) {
  // Print informative message, placing non-string arguments in quotes,
  // and terminating with a newline.
  body = formatMessageArguments(body, true);
  return (listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, SYM_STREAMS_STELLA_STANDARD_OUTPUT, body->concatenate(NIL, 0)));
}

Object* warn(Cons* body) {
  // Signal warning message, placing non-string arguments in quotes.
  body = formatMessageArguments(body, false);
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_STREAMS_COMMON_LISP) {
    return (listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, KWD_STREAMS_WARN, body->concatenate(NIL, 0)));
  }
  else {
    return (listO(4, SYM_STREAMS_STELLA_PRINT_STREAM, SYM_STREAMS_STELLA_STANDARD_WARNING, wrapString("Warning: "), body->concatenate(cons(SYM_STREAMS_STELLA_EOL, NIL), 0)));
  }
}

Object* signal(Symbol* type, Cons* body) {
  // Signal error message, placing non-string arguments in quotes.
  if (type == SYM_STREAMS_STELLA_NULL) {
    type = SYM_STREAMS_STELLA_STELLA_EXCEPTION;
  }
  if ((body->length() == 1) &&
      isaP(body->value, SGT_STREAMS_STELLA_STRING_WRAPPER)) {
    return (listO(3, SYM_STREAMS_STELLA_SIGNAL_EXCEPTION, listO(3, SYM_STREAMS_STELLA_NEW, type, listO(3, KWD_STREAMS_MESSAGE, body->value, NIL)), NIL));
  }
  else {
    { Symbol* streamvar = localGensym("STREAM");

      return (listO(5, SYM_STREAMS_STELLA_LET, cons(cons(streamvar, cons(listO(3, SYM_STREAMS_STELLA_NEW, SYM_STREAMS_STELLA_OUTPUT_STRING_STREAM, NIL), NIL)), NIL), listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, streamvar, formatMessageArguments(body, false)->concatenate(NIL, 0)), listO(3, SYM_STREAMS_STELLA_SIGNAL_EXCEPTION, listO(3, SYM_STREAMS_STELLA_NEW, type, listO(3, KWD_STREAMS_MESSAGE, listO(3, SYM_STREAMS_STELLA_THE_STRING, streamvar, NIL), NIL)), NIL), NIL));
    }
  }
}

Object* error(Cons* body) {
  // Signal error message, placing non-string arguments in quotes.
  return (listO(3, SYM_STREAMS_STELLA_SIGNAL, SYM_STREAMS_STELLA_STELLA_EXCEPTION, body->concatenate(NIL, 0)));
}

Object* continuableError(Cons* body) {
  // Signal error message, placing non-string arguments in quotes.
  body = formatMessageArguments(body, false);
  if (oTRANSLATOROUTPUTLANGUAGEo == KWD_STREAMS_JAVA) {
    if ((body->length() == 1) &&
        isaP(body->value, SGT_STREAMS_STELLA_STRING_WRAPPER)) {
      return (listO(4, SYM_STREAMS_STELLA_LET, cons(listO(3, SYM_STREAMS_STELLA_ERROR_MESSAGE_, wrapString(((StringWrapper*)(body->value))->wrapperValue), NIL), NIL), listO(4, SYM_STREAMS_STELLA_VERBATIM, KWD_STREAMS_JAVA, wrapString("Native.continuableError(error_message_)"), NIL), NIL));
    }
    else {
      { Symbol* streamvar = localGensym("STREAM");

        return (listO(5, SYM_STREAMS_STELLA_LET, cons(cons(streamvar, cons(listO(3, SYM_STREAMS_STELLA_NEW, SYM_STREAMS_STELLA_OUTPUT_STRING_STREAM, NIL), NIL)), NIL), listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, streamvar, formatMessageArguments(body, false)->concatenate(NIL, 0)), listO(4, SYM_STREAMS_STELLA_LET, cons(listO(3, SYM_STREAMS_STELLA_ERROR_MESSAGE_, listO(3, SYM_STREAMS_STELLA_THE_STRING, streamvar, NIL), NIL), NIL), listO(4, SYM_STREAMS_STELLA_VERBATIM, KWD_STREAMS_JAVA, wrapString("Native.continuableError(error_message_)"), NIL), NIL), NIL));
      }
    }
  }
  else {
    return (listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, KWD_STREAMS_CONTINUABLE_ERROR, body->concatenate(NIL, 0)));
  }
}

Object* signalReadError(Cons* body) {
  // Specialized version of `signal' that throws a READ-EXCEPTION.
  return (listO(3, SYM_STREAMS_STELLA_SIGNAL, SYM_STREAMS_STELLA_READ_EXCEPTION, body->concatenate(NIL, 0)));
}

void ensureFileExists(const char* filename, const char* context) {
  // Ensures that `filename' exists.  If not, an exception of
  // type `NO-SUCH-FILE-EXCEPTION' is thrown with `context' supplying
  // context for the error message.
  if (!(probeFileP(filename))) {
    { NoSuchFileException* self000 = newNoSuchFileException(stringConcatenate(context, ": file ", 2, filename, " does not exist"));

      self000->filename = filename;
      { NoSuchFileException* ex = self000;

        throw *ex;
      }
    }
  }
}

void ensureFileDoesNotExist(const char* filename, const char* context) {
  // Ensures that `filename' does not exist.  If it does,
  // an exception of type `FILE-ALREADY-EXISTS-EXCEPTION' is thrown
  // with `context' supplying context for the error message.
  if (probeFileP(filename)) {
    { FileAlreadyExistsException* self000 = newFileAlreadyExistsException(stringConcatenate(context, ": file ", 2, filename, " already exists"));

      self000->filename = filename;
      { FileAlreadyExistsException* ex = self000;

        throw *ex;
      }
    }
  }
}

Cons* formatWalkMessageArguments(Cons* messageargumentstree) {
  { ConsIterator* it = messageargumentstree->allocateIterator();

    for (; it->nextP(); ) {
      { Object* item = it->value;

        if (subtypeOfSymbolP(safePrimaryType(item))) {
          { Object* item000 = item;
            Symbol* item = ((Symbol*)(item000));

            if (!(item == EOL)) {
              it->valueSetter(listO(3, SYM_STREAMS_STELLA_DE_UGLIFY_PARSE_TREE, item, NIL));
            }
          }
        }
        else {
        }
      }
    }
  }
  return (messageargumentstree);
}

Object* walkError(Cons* body) {
  { Cons* messagearguments = formatMessageArguments(formatWalkMessageArguments(body), false);

    return (listO(5, SYM_STREAMS_STELLA_SPECIAL, cons(listO(3, SYM_STREAMS_STELLA_oPRINTREADABLYpo, SYM_STREAMS_STELLA_TRUE, NIL), NIL), cons(SYM_STREAMS_STELLA_SIGNAL_TRANSLATION_ERROR, NIL), listO(5, SYM_STREAMS_STELLA_UNLESS, cons(SYM_STREAMS_STELLA_SUPPRESS_WARNINGSp, NIL), listO(4, SYM_STREAMS_STELLA_PRINT_ERROR_CONTEXT, wrapString(">> ERROR: "), SYM_STREAMS_STELLA_STANDARD_ERROR, NIL), listO(5, SYM_STREAMS_STELLA_PRINT_STREAM, SYM_STREAMS_STELLA_STANDARD_ERROR, SYM_STREAMS_STELLA_EOL, wrapString(" "), messagearguments->concatenate(listO(3, wrapString("."), SYM_STREAMS_STELLA_EOL, NIL), 0)), NIL), NIL));
  }
}

Object* walkInform(Cons* body) {
  { Cons* messagearguments = formatMessageArguments(formatWalkMessageArguments(body), false);

    return (listO(5, SYM_STREAMS_STELLA_SPECIAL, cons(listO(3, SYM_STREAMS_STELLA_oPRINTREADABLYpo, SYM_STREAMS_STELLA_TRUE, NIL), NIL), cons(SYM_STREAMS_STELLA_SIGNAL_TRANSLATION_NOTE, NIL), listO(5, SYM_STREAMS_STELLA_UNLESS, cons(SYM_STREAMS_STELLA_SUPPRESS_WARNINGSp, NIL), listO(4, SYM_STREAMS_STELLA_PRINT_ERROR_CONTEXT, wrapString(">> NOTE: "), SYM_STREAMS_STELLA_STANDARD_OUTPUT, NIL), listO(5, SYM_STREAMS_STELLA_PRINT_STREAM, SYM_STREAMS_STELLA_STANDARD_OUTPUT, SYM_STREAMS_STELLA_EOL, wrapString(" "), messagearguments->concatenate(listO(3, wrapString("."), SYM_STREAMS_STELLA_EOL, NIL), 0)), NIL), NIL));
  }
}

Object* walkWarn(Cons* body) {
  { Cons* messagearguments = formatMessageArguments(formatWalkMessageArguments(body), false);

    return (listO(5, SYM_STREAMS_STELLA_SPECIAL, cons(listO(3, SYM_STREAMS_STELLA_oPRINTREADABLYpo, SYM_STREAMS_STELLA_TRUE, NIL), NIL), cons(SYM_STREAMS_STELLA_SIGNAL_TRANSLATION_WARNING, NIL), listO(5, SYM_STREAMS_STELLA_UNLESS, cons(SYM_STREAMS_STELLA_SUPPRESS_WARNINGSp, NIL), listO(4, SYM_STREAMS_STELLA_PRINT_ERROR_CONTEXT, wrapString(">> WARNING: "), SYM_STREAMS_STELLA_STANDARD_WARNING, NIL), listO(5, SYM_STREAMS_STELLA_PRINT_STREAM, SYM_STREAMS_STELLA_STANDARD_WARNING, SYM_STREAMS_STELLA_EOL, wrapString(" "), messagearguments->concatenate(listO(3, wrapString("."), SYM_STREAMS_STELLA_EOL, NIL), 0)), NIL), NIL));
  }
}

Object* safety(IntegerWrapper* level, Object* test, Cons* body) {
  // Signal warning message, placing non-string arguments in quotes.
  if (level->wrapperValue > oSAFETYo) {
    return (NULL);
  }
  body = formatMessageArguments(body, false);
  return (listO(4, SYM_STREAMS_STELLA_WHEN, listO(3, SYM_STREAMS_STELLA_NOT, test, NIL), listO(4, SYM_STREAMS_STELLA_PRINT_STREAM, KWD_STREAMS_ERROR, wrapString("Safety violation: "), body->concatenate(NIL, 0)), NIL));
}

Object* evaluationError(Cons* body) {
  { Symbol* streamvar = localGensym("STREAM");

    return (listO(8, SYM_STREAMS_STELLA_LET, cons(cons(streamvar, cons(listO(3, SYM_STREAMS_STELLA_NEW, SYM_STREAMS_STELLA_OUTPUT_STRING_STREAM, NIL), NIL)), NIL), listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, streamvar, listO(3, wrapString("While evaluating '"), SYM_STREAMS_STELLA_oEVALUATIONTREEo, NIL)), listO(4, SYM_STREAMS_STELLA_WHEN, listO(3, SYM_STREAMS_STELLA_DEFINEDp, SYM_STREAMS_STELLA_oEVALUATIONPARENTTREEo, NIL), listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, streamvar, listO(4, SYM_STREAMS_STELLA_EOL, wrapString("' inside '"), SYM_STREAMS_STELLA_oEVALUATIONPARENTTREEo, NIL)), NIL), listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, streamvar, listO(3, wrapString("':"), SYM_STREAMS_STELLA_EOL, NIL)), listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, streamvar, formatMessageArguments(body, false)->concatenate(NIL, 0)), listO(3, SYM_STREAMS_STELLA_SIGNAL_EXCEPTION, listO(5, SYM_STREAMS_STELLA_NEW, SYM_STREAMS_STELLA_EVALUATION_EXCEPTION, KWD_STREAMS_MESSAGE, listO(3, SYM_STREAMS_STELLA_THE_STRING, streamvar, NIL), NIL), NIL), NIL));
  }
}

Cons* formatStringMessageArguments(Cons* messagearguments, boolean trailingeolP) {
  { Cons* formattedarguments = formatMessageArguments(messagearguments, trailingeolP);

    { ConsIterator* it = formattedarguments->allocateIterator();

      for (; it->nextP(); ) {
        { Surrogate* testValue000 = safePrimaryType(it->value);

          if (subtypeOfStringP(testValue000)) {
          }
          else if (subtypeOfP(testValue000, SGT_STREAMS_STELLA_LITERAL_WRAPPER)) {
            it->valueSetter(wrapString(stringify(it->value)));
          }
          else {
            if (it->value == SYM_STREAMS_STELLA_EOL) {
              it->valueSetter(wrapString(EOL_STRING));
            }
            else {
              it->valueSetter(listO(3, SYM_STREAMS_STELLA_STRINGIFY, it->value, NIL));
            }
          }
        }
      }
    }
    return (formattedarguments);
  }
}

Object* messageToString(Cons* body) {
  { Cons* messagearguments = formatStringMessageArguments(body, false);
    Symbol* messagevar = localGensym("MESSAGE");

    return (listO(5, SYM_STREAMS_STELLA_VRLET, cons(cons(messagevar, listO(3, SYM_STREAMS_STELLA_STRING, SYM_STREAMS_STELLA_NULL, NIL)), NIL), listO(4, SYM_STREAMS_STELLA_SPECIAL, cons(listO(3, SYM_STREAMS_STELLA_oPRINTREADABLYpo, SYM_STREAMS_STELLA_TRUE, NIL), NIL), listO(3, SYM_STREAMS_STELLA_SETQ, messagevar, cons(cons(SYM_STREAMS_STELLA_CONCATENATE, messagearguments->concatenate(NIL, 0)), NIL)), NIL), messagevar, NIL));
  }
}

boolean terminateOutputStreamP(OutputStream* self) {
  { std::ostream* nativeStream = self->nativeStream;

    if (!(nativeStream == NULL)) {
      delete nativeStream;
    }
    self->nativeStream = NULL;
    self->state = KWD_STREAMS_CLOSED;
    return (true);
  }
}

boolean terminateInputStreamP(InputStream* self) {
  { std::istream* nativeStream = self->nativeStream;

    if (!(nativeStream == NULL)) {
      delete nativeStream;
    }
    self->nativeStream = NULL;
    self->state = KWD_STREAMS_CLOSED;
    return (true);
  }
}

// List of file streams that are currently open.
List* oOPEN_FILE_STREAMSo = NULL;

OutputFileStream* openOutputFile(const char* filename, int options, ...) {
  // Open file `fileName' for output and return the resulting output stream.
  // By default the file will be created or overwritten if it already exists.
  // If `:IF-EXISTS' (or `:IF-EXISTS-ACTION') is one of the `options' its value
  // specifies what to do in case the file already exists.  If the value is
  // `:SUPERSEDE' the pre-existing file will be overwritten.  If the value is
  // `:APPEND' the preexisting file will be appended to (if the file did not
  // yet exist the file will simply be created).  If the value is `:ERROR' then
  // an error will be signaled.  If it is `:ABORT' or `:PROBE' the opening operation
  // will be aborted and NULL will be returned.
  // 
  // If `:IF-NOT-EXISTS' (or `:IF-NOT-EXISTS-ACTION') is one of the `options' its
  // value specifies what to do in case the file does not already exist.  If the
  // value is `:CREATE', the file will simply be created.  If the value is
  // `:CREATE-PATH' the file will be created plus any non-existing directories
  // in the directory path of `fileName' will also be created.  If the value is
  // `:ERROR' then an error will be signaled.  If it is `:ABORT' or `:PROBE' the
  // opening operation will be aborted and NULL will be returned.
  { OutputFileStream* stream = newOutputFileStream(NULL);

    { Cons* arglist000 = NIL;

      { va_list iter000;
        int iter000Count = options;
        Keyword* arg000 = NULL;
        Cons* collect000 = NULL;

        va_start(iter000, options);
                for  (; (iter000Count--) > 0; ) {
          arg000 = va_arg(iter000, Keyword*);
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(arg000, NIL);
              if (arglist000 == NIL) {
                arglist000 = collect000;
              }
              else {
                addConsToEndOfConsList(arglist000, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(arg000, NIL);
              collect000 = collect000->rest;
            }
          }
        }
        va_end(iter000);
      }
      { PropertyList* theoptions = vetOptions(arglist000, listO(5, KWD_STREAMS_IF_EXISTS, KWD_STREAMS_IF_EXISTS_ACTION, KWD_STREAMS_IF_NOT_EXISTS, KWD_STREAMS_IF_NOT_EXISTS_ACTION, NIL));

        { Object* temp000 = theoptions->lookup(KWD_STREAMS_IF_EXISTS);

          { Keyword* chooseValue000 = NULL;

            if (((boolean)(temp000))) {
              chooseValue000 = ((Keyword*)(temp000));
            }
            else {
              { Object* temp001 = theoptions->lookup(KWD_STREAMS_IF_EXISTS_ACTION);

                chooseValue000 = (((boolean)(temp001)) ? ((Keyword*)(temp001)) : KWD_STREAMS_SUPERSEDE);
              }
            }
            stream->ifExistsAction = chooseValue000;
          }
        }
        { Object* temp002 = theoptions->lookup(KWD_STREAMS_IF_NOT_EXISTS);

          { Keyword* chooseValue001 = NULL;

            if (((boolean)(temp002))) {
              chooseValue001 = ((Keyword*)(temp002));
            }
            else {
              { Object* temp003 = theoptions->lookup(KWD_STREAMS_IF_NOT_EXISTS_ACTION);

                chooseValue001 = (((boolean)(temp003)) ? ((Keyword*)(temp003)) : KWD_STREAMS_CREATE);
              }
            }
            stream->ifNotExistsAction = chooseValue001;
          }
        }
        stream->filename = filename;
        initializeFileOutputStream(stream);
        if (stream->nativeStream == NULL) {
          closeStream(stream);
          stream = NULL;
        }
        return (stream);
      }
    }
  }
}

void initializeFileOutputStream(OutputFileStream* self) {
  if (!(self->filename != NULL)) {
    return;
  }
  { const char* filename = translateLogicalPathname(self->filename);
    boolean append = false;

    { Keyword* testValue000 = self->ifNotExistsAction;

      if (testValue000 == KWD_STREAMS_CREATE) {
      }
      else if (testValue000 == KWD_STREAMS_CREATE_PATH) {
        ensureDirectoriesExist(filename);
      }
      else if ((testValue000 == KWD_STREAMS_ABORT) ||
          (testValue000 == KWD_STREAMS_PROBE)) {
        if (!(probeFileP(filename))) {
          return;
        }
      }
      else if (testValue000 == KWD_STREAMS_ERROR) {
        ensureFileExists(filename, "initialize-file-output-stream");
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "initialize-file-output-stream: illegal :if-not-exists action: " << "`" << self->ifNotExistsAction << "'";
          throw *newBadArgumentException(stream000->theStringReader());
        }
      }
    }
    { Keyword* testValue001 = self->ifExistsAction;

      if (testValue001 == KWD_STREAMS_SUPERSEDE) {
      }
      else if (testValue001 == KWD_STREAMS_APPEND) {
        append = true;
      }
      else if ((testValue001 == KWD_STREAMS_ABORT) ||
          (testValue001 == KWD_STREAMS_PROBE)) {
        if (probeFileP(filename)) {
          return;
        }
      }
      else if (testValue001 == KWD_STREAMS_ERROR) {
        ensureFileDoesNotExist(filename, "initialize-file-output-stream");
      }
      else {
        { OutputStringStream* stream001 = newOutputStringStream();

          *(stream001->nativeStream) << "initialize-file-output-stream: illegal :if-exists action: " << "`" << self->ifExistsAction << "'";
          throw *newBadArgumentException(stream001->theStringReader());
        }
      }
    }
    self->nativeStream = (new std::ofstream(filename, append ? std::ios::app : std::ios::out));
    if (!*(self->nativeStream)) {
      { OutputStringStream* stream002 = newOutputStringStream();

        *(stream002->nativeStream) << "initialize-file-output-stream: Could not open " << "`" << self << "'";
        throw *newInputOutputException(stream002->theStringReader());
      }
    }
    *(self->nativeStream) << std::setprecision(16);
    self->state = KWD_STREAMS_OPEN;
    oOPEN_FILE_STREAMSo->push(self);
  }
}

boolean terminateFileOutputStreamP(OutputFileStream* self) {
  { std::ostream* nativeStream = self->nativeStream;

    if (!(nativeStream == NULL)) {
      delete nativeStream;
    }
    self->nativeStream = NULL;
    self->state = KWD_STREAMS_CLOSED;
    oOPEN_FILE_STREAMSo->remove(self);
    return (true);
  }
}

InputFileStream* openInputFile(const char* filename, int options, ...) {
  // Open file `fileName' for input and return the resulting input stream.
  // By default signal an error if the file does not exist.  The only legal
  // option so far is `:IF-NOT-EXISTS' (or `:IF-NOT-EXISTS-ACTION') which
  // specifies what to do in case the file does not exist.  If its value is
  // `:ERROR' then an error will be signaled.  If it is `:ABORT' or `:PROBE'
  // the opening operation will be aborted and NULL will be returned.
  { InputFileStream* stream = newInputFileStream(NULL);

    { Cons* arglist000 = NIL;

      { va_list iter000;
        int iter000Count = options;
        Keyword* arg000 = NULL;
        Cons* collect000 = NULL;

        va_start(iter000, options);
                for  (; (iter000Count--) > 0; ) {
          arg000 = va_arg(iter000, Keyword*);
          if (!((boolean)(collect000))) {
            {
              collect000 = cons(arg000, NIL);
              if (arglist000 == NIL) {
                arglist000 = collect000;
              }
              else {
                addConsToEndOfConsList(arglist000, collect000);
              }
            }
          }
          else {
            {
              collect000->rest = cons(arg000, NIL);
              collect000 = collect000->rest;
            }
          }
        }
        va_end(iter000);
      }
      { PropertyList* theoptions = vetOptions(arglist000, listO(3, KWD_STREAMS_IF_NOT_EXISTS, KWD_STREAMS_IF_NOT_EXISTS_ACTION, NIL));

        { Object* temp000 = theoptions->lookup(KWD_STREAMS_IF_NOT_EXISTS);

          { Keyword* chooseValue000 = NULL;

            if (((boolean)(temp000))) {
              chooseValue000 = ((Keyword*)(temp000));
            }
            else {
              { Object* temp001 = theoptions->lookup(KWD_STREAMS_IF_NOT_EXISTS_ACTION);

                chooseValue000 = (((boolean)(temp001)) ? ((Keyword*)(temp001)) : KWD_STREAMS_ERROR);
              }
            }
            stream->ifNotExistsAction = chooseValue000;
          }
        }
        stream->filename = filename;
        initializeFileInputStream(stream);
        if (stream->nativeStream == NULL) {
          closeStream(stream);
          stream = NULL;
        }
        return (stream);
      }
    }
  }
}

void initializeFileInputStream(InputFileStream* self) {
  if (!(self->filename != NULL)) {
    return;
  }
  { const char* filename = translateLogicalPathname(self->filename);

    { Keyword* testValue000 = self->ifNotExistsAction;

      if ((testValue000 == KWD_STREAMS_ABORT) ||
          (testValue000 == KWD_STREAMS_PROBE)) {
        if (!(probeFileP(filename))) {
          return;
        }
      }
      else if (testValue000 == KWD_STREAMS_ERROR) {
        ensureFileExists(filename, "initialize-file-input-stream");
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "initialize-file-input-stream: illegal :if-not-exists action: " << "`" << self->ifNotExistsAction << "'";
          throw *newBadArgumentException(stream000->theStringReader());
        }
      }
    }
    self->nativeStream = (new std::ifstream(filename));
    if (!*(self->nativeStream)) {
      { OutputStringStream* stream001 = newOutputStringStream();

        *(stream001->nativeStream) << "initialize-file-input-stream: Could not open " << "`" << self << "'";
        throw *newInputOutputException(stream001->theStringReader());
      }
    }
    self->state = KWD_STREAMS_OPEN;
    oOPEN_FILE_STREAMSo->push(self);
  }
}

boolean terminateFileInputStreamP(InputFileStream* self) {
  { std::istream* nativeStream = self->nativeStream;

    if (!(nativeStream == NULL)) {
      delete nativeStream;
    }
    self->nativeStream = NULL;
    self->state = KWD_STREAMS_CLOSED;
    oOPEN_FILE_STREAMSo->remove(self);
    return (true);
  }
}

void initializeStringOutputStream(OutputStringStream* self) {
  self->nativeStream = (new (GC) std::ostringstream());
  *(self->nativeStream) << std::setprecision(16);
}

boolean terminateStringOutputStreamP(OutputStringStream* self) {
  self->nativeStream = NULL;
  self->state = KWD_STREAMS_CLOSED;
  return (true);
}

const char* OutputStringStream::theStringReader() {
  { OutputStringStream* self = this;

    { std::ostream* nativeStream = self->nativeStream;
      const char* string = NULL;

      string = ostringstream_to_c_string((std::ostringstream*)nativeStream);
      if (string == NULL) {
        string = "";
      }
      return (string);
    }
  }
}

void initializeStringInputStream(InputStringStream* self) {
  { const char* string = self->theString;

    self->nativeStream = (new (GC) std::istringstream(string));
  }
}

boolean terminateStringInputStreamP(InputStringStream* self) {
  self->nativeStream = NULL;
  self->state = KWD_STREAMS_CLOSED;
  return (true);
}

void closeStream(Stream* self) {
  // Close the stream `self'.
  { Surrogate* testValue000 = safePrimaryType(self);

    if (subtypeOfP(testValue000, SGT_STREAMS_STELLA_INPUT_FILE_STREAM)) {
      { Stream* self000 = self;
        InputFileStream* self = ((InputFileStream*)(self000));

        terminateFileInputStreamP(self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_STREAMS_STELLA_OUTPUT_FILE_STREAM)) {
      { Stream* self001 = self;
        OutputFileStream* self = ((OutputFileStream*)(self001));

        terminateFileOutputStreamP(self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_STREAMS_STELLA_INPUT_STRING_STREAM)) {
      { Stream* self002 = self;
        InputStringStream* self = ((InputStringStream*)(self002));

        terminateStringInputStreamP(self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_STREAMS_STELLA_OUTPUT_STRING_STREAM)) {
      { Stream* self003 = self;
        OutputStringStream* self = ((OutputStringStream*)(self003));

        terminateStringOutputStreamP(self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_STREAMS_STELLA_INPUT_STREAM)) {
      { Stream* self004 = self;
        InputStream* self = ((InputStream*)(self004));

        terminateInputStreamP(self);
      }
    }
    else if (subtypeOfP(testValue000, SGT_STREAMS_STELLA_OUTPUT_STREAM)) {
      { Stream* self005 = self;
        OutputStream* self = ((OutputStream*)(self005));

        terminateOutputStreamP(self);
      }
    }
    else {
    }
  }
}

void clearInput(InputStream* self) {
  // Clear all buffered raw and tokenized input of `self'.
  { std::istream* nativeStream = self->nativeStream;

    char buffer[1024];
       nativeStream->clear();
       while (nativeStream->readsome(buffer, 1024) > 0) {};
    self->tokenizerState = NULL;
  }
}

void flushOutput(OutputStream* self) {
  // Flush all buffered output of `self'.
  { std::ostream* nativeStream = self->nativeStream;

    flush(*nativeStream);
  }
}

void closeAllFiles() {
  // Close all currently open file streams.  Use for emergencies or for cleanup.
  { List* openstreams = oOPEN_FILE_STREAMSo->copy();

    { Stream* stream = NULL;
      Cons* iter000 = openstreams->theConsList;

      for (; !(iter000 == NIL); iter000 = iter000->rest) {
        stream = ((Stream*)(iter000->value));
        closeStream(stream);
      }
    }
    openstreams->free();
  }
}

InputStream* openNetworkStream(const char* host, int port, OutputStream*& _Return1) {
  // Open a TCP/IP network stream to `host' at `port' and return the result
  // as an input/output stream pair.
  { std::istream* in = NULL;
    std::ostream* out = NULL;

    throw *newStellaException("Network streams not yet implemented for this target language");
    { InputStream* self001 = newInputStream();

      self001->nativeStream = in;
      self001->state = KWD_STREAMS_OPEN;
      self001->bufferingScheme = KWD_STREAMS_BLOCK;
      { InputStream* value000 = self001;

        { OutputStream* self002 = newOutputStream();

          self002->nativeStream = out;
          self002->state = KWD_STREAMS_OPEN;
          { OutputStream* value001 = self002;

            _Return1 = value001;
            return (value000);
          }
        }
      }
    }
  }
}

Object* withInputFile(Cons* binding, Cons* body) {
  // Sets up an unwind-protected form which opens a file for
  // input and closes it afterwards.  The stream for reading is bound to the
  // variable provided in the macro form.
  // Syntax is `(WITH-INPUT-FILE (var filename options*) body+)' where `options'
  // can be any that are legal for `open-input-file' (which see).
  { Symbol* var = ((Symbol*)(binding->value));

    return (listO(4, SYM_STREAMS_STELLA_LET, cons(cons(var, listO(3, SYM_STREAMS_STELLA_FILE_INPUT_STREAM, SYM_STREAMS_STELLA_NULL, NIL)), NIL), listO(4, SYM_STREAMS_STELLA_UNWIND_PROTECT, listO(3, SYM_STREAMS_STELLA_PROGN, listO(3, SYM_STREAMS_STELLA_SETQ, var, cons(listO(3, SYM_STREAMS_STELLA_OPEN_INPUT_FILE, binding->rest->value, binding->rest->rest->concatenate(NIL, 0)), NIL)), body->concatenate(NIL, 0)), listO(4, SYM_STREAMS_STELLA_WHEN, listO(3, SYM_STREAMS_STELLA_DEFINEDp, var, NIL), listO(3, SYM_STREAMS_STELLA_FREE, var, NIL), NIL), NIL), NIL));
  }
}

Object* withOutputFile(Cons* binding, Cons* body) {
  // Sets up an unwind-protected form which opens a file for
  // output and closes it afterwards.  The stream for writing is bound to the
  // variable provided in the macro form.
  // Syntax is `(WITH-OUTPUT-FILE (var filename options*) body+)' where `options'
  // can be any that are legal for `open-output-file' (which see).
  { Symbol* var = ((Symbol*)(binding->value));

    return (listO(4, SYM_STREAMS_STELLA_LET, cons(cons(var, listO(3, SYM_STREAMS_STELLA_FILE_OUTPUT_STREAM, SYM_STREAMS_STELLA_NULL, NIL)), NIL), listO(4, SYM_STREAMS_STELLA_UNWIND_PROTECT, listO(3, SYM_STREAMS_STELLA_PROGN, listO(3, SYM_STREAMS_STELLA_SETQ, var, cons(listO(3, SYM_STREAMS_STELLA_OPEN_OUTPUT_FILE, binding->rest->value, binding->rest->rest->concatenate(NIL, 0)), NIL)), body->concatenate(NIL, 0)), listO(4, SYM_STREAMS_STELLA_WHEN, listO(3, SYM_STREAMS_STELLA_DEFINEDp, var, NIL), listO(3, SYM_STREAMS_STELLA_FREE, var, NIL), NIL), NIL), NIL));
  }
}

Object* withNetworkStream(Cons* binding, Cons* body) {
  // Sets up an unwind-protected form which opens a network
  // socket stream to a host and port for input and output and closes it afterwards.
  // Separate variables as provided in the call are bound to the input and output
  // streams. Syntax is (WITH-NETWORK-STREAM (varIn varOut hostname port) body+)
  { Symbol* varIn = ((Symbol*)(binding->value));
    Symbol* varOut = ((Symbol*)(binding->rest->value));

    return (listO(4, SYM_STREAMS_STELLA_LET, listO(3, cons(varIn, listO(3, SYM_STREAMS_STELLA_INPUT_STREAM, SYM_STREAMS_STELLA_NULL, NIL)), cons(varOut, listO(3, SYM_STREAMS_STELLA_OUTPUT_STREAM, SYM_STREAMS_STELLA_NULL, NIL)), NIL), listO(5, SYM_STREAMS_STELLA_UNWIND_PROTECT, listO(3, SYM_STREAMS_STELLA_PROGN, listO(4, SYM_STREAMS_STELLA_MV_SETQ, cons(varIn, cons(varOut, NIL)), listO(3, SYM_STREAMS_STELLA_OPEN_NETWORK_STREAM, binding->rest->rest->value, cons(binding->fourth(), NIL)), NIL), body->concatenate(NIL, 0)), listO(4, SYM_STREAMS_STELLA_WHEN, listO(3, SYM_STREAMS_STELLA_DEFINEDp, varIn, NIL), listO(3, SYM_STREAMS_STELLA_FREE, varIn, NIL), NIL), listO(4, SYM_STREAMS_STELLA_WHEN, listO(3, SYM_STREAMS_STELLA_DEFINEDp, varOut, NIL), listO(3, SYM_STREAMS_STELLA_FREE, varOut, NIL), NIL), NIL), NIL));
  }
}

long long int nativeFileInputStreamPosition(std::istream* nstream) {
  nstream->clear(std::ios::goodbit);
  return (nstream->tellg());
}

long long int nativeFileInputStreamPositionSetter(std::istream* nstream, long long int newpos) {
  nstream->clear(std::ios::goodbit);nstream->seekg(newpos);
  return (newpos);
}

long long int InputFileStream::streamPosition() {
  // Return the current position of the file input cursor in `self'.
  { InputFileStream* self = this;

    { long long int position = nativeFileInputStreamPosition(self->nativeStream);
      TokenizerStreamState* state = self->tokenizerState;

      if (((boolean)(state))) {
        position = position - state->bufferedInputLength();
      }
      return (position);
    }
  }
}

long long int InputFileStream::streamPositionSetter(long long int newpos) {
  // Set the current position of the file input cursor in `self' to `newpos'.
  // If `self' has any tokenizer state associated with it, this will also reset
  // to the start state of the tokenizer table; otherwise, behavior would be
  // unpredictable unless the character class of the new position is exactly the
  // same as the one following the most recent token.
  { InputFileStream* self = this;

    { std::istream* nstream = self->nativeStream;
      TokenizerStreamState* state = self->tokenizerState;

      if (((boolean)(state))) {
        { long long int fileposition = nativeFileInputStreamPosition(nstream);
          long long int offset = fileposition - newpos;
          int buffered = 0;

          if (offset > 0) {
            buffered = state->bufferedInputLength();
            if (offset <= buffered) {
              state->cursor = ((int)(longIntegerMod(state->cursor + (buffered - offset), ((long long int)(state->bufferSize)))));
              state->reset();
              return (newpos);
            }
          }
          state->clear();
          state->reset();
        }
      }
      nativeFileInputStreamPositionSetter(nstream, newpos);
      return (newpos);
    }
  }
}

long long int nativeFileOutputStreamPosition(std::ostream* nstream) {
  return (nstream->tellp());
}

long long int nativeFileOutputStreamPositionSetter(std::ostream* nstream, long long int newpos) {
  nstream->seekp(newpos);
  return (newpos);
}

long long int OutputFileStream::streamPosition() {
  // Return the current position of the file input cursor in `self'.
  { OutputFileStream* self = this;

    return ((self->nativeStream)->tellp());
  }
}

long long int OutputFileStream::streamPositionSetter(long long int newpos) {
  // Set the current position of the file input cursor in `self' to `newpos'.
  { OutputFileStream* self = this;

    nativeFileOutputStreamPositionSetter(self->nativeStream, newpos);
    return (newpos);
  }
}

const char* oHTML_QUOTED_CHARACTERSo = "><&\"";

Cons* expandMarkupTagFunction(Cons* tagAndStream, Cons* body, boolean xmlP) {
  { Object* tag = tagAndStream->value;
    Symbol* tagvar = NULL;
    const char* tagvalue = NULL;
    Object* stream = tagAndStream->rest->value;
    Object* eolargument = tagAndStream->rest->rest->value;
    boolean eolP = ((boolean)(eolargument)) &&
        coerceWrappedBooleanToBoolean(coerceToBoolean(eolargument));

    if (body == NIL) {
      { Surrogate* testValue000 = safePrimaryType(tag);

        if (subtypeOfStringP(testValue000)) {
          { Object* tag000 = tag;
            StringWrapper* tag = ((StringWrapper*)(tag000));

            if (eolP) {
              return (listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, cons(wrapString(stringConcatenate("<", tag->wrapperValue, 1, (xmlP ? "/>" : ">"))), cons(SYM_STREAMS_STELLA_EOL, NIL))));
            }
            else {
              return (listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, cons(wrapString(stringConcatenate("<", tag->wrapperValue, 1, (xmlP ? "/>" : ">"))), NIL)));
            }
          }
        }
        else if (subtypeOfP(testValue000, SGT_STREAMS_STELLA_OBJECT)) {
          { Object* tag001 = tag;
            Object* tag = tag001;

            if (eolP) {
              return (listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, listO(3, wrapString("<"), tag, cons((xmlP ? wrapString("/>") : wrapString(">")), cons(SYM_STREAMS_STELLA_EOL, NIL)))));
            }
            else {
              return (listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, listO(3, wrapString("<"), tag, cons((xmlP ? wrapString("/>") : wrapString(">")), NIL))));
            }
          }
        }
        else {
          { OutputStringStream* stream000 = newOutputStringStream();

            *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
            throw *newStellaException(stream000->theStringReader());
          }
        }
      }
    }
    else {
      { Surrogate* testValue001 = safePrimaryType(tag);

        if (subtypeOfStringP(testValue001)) {
          { Object* tag002 = tag;
            StringWrapper* tag = ((StringWrapper*)(tag002));

            tagvalue = tag->wrapperValue;
            if (eolP) {
              return (listO(3, SYM_STREAMS_STELLA_PROGN, listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, cons(wrapString(stringConcatenate("<", tagvalue, 1, ">")), NIL)), body->concatenate(cons(listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, cons(wrapString(stringConcatenate("</", stringSubsequence(tagvalue, 0, stringPosition(tagvalue, ' ', 0)), 1, ">")), cons(SYM_STREAMS_STELLA_EOL, NIL))), NIL), 0)));
            }
            else {
              return (listO(3, SYM_STREAMS_STELLA_PROGN, listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, cons(wrapString(stringConcatenate("<", tagvalue, 1, ">")), NIL)), body->concatenate(cons(listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, cons(wrapString(stringConcatenate("</", stringSubsequence(tagvalue, 0, stringPosition(tagvalue, ' ', 0)), 1, ">")), NIL)), NIL), 0)));
            }
          }
        }
        else if (subtypeOfSymbolP(testValue001)) {
          { Object* tag003 = tag;
            Symbol* tag = ((Symbol*)(tag003));

            if (eolP) {
              return (listO(3, SYM_STREAMS_STELLA_PROGN, listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, listO(3, wrapString("<"), tag, cons(wrapString(">"), NIL))), body->concatenate(cons(listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, listO(5, wrapString("</"), listO(3, SYM_STREAMS_STELLA_SUBSEQUENCE, tag, listO(3, wrapInteger(0), listO(3, SYM_STREAMS_STELLA_POSITION, tag, listO(3, wrapCharacter(' '), wrapInteger(0), NIL)), NIL)), wrapString(">"), SYM_STREAMS_STELLA_EOL, NIL)), NIL), 0)));
            }
            else {
              return (listO(3, SYM_STREAMS_STELLA_PROGN, listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, listO(3, wrapString("<"), tag, cons(wrapString(">"), NIL))), body->concatenate(cons(listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, listO(4, wrapString("</"), listO(3, SYM_STREAMS_STELLA_SUBSEQUENCE, tag, listO(3, wrapInteger(0), listO(3, SYM_STREAMS_STELLA_POSITION, tag, listO(3, wrapCharacter(' '), wrapInteger(0), NIL)), NIL)), wrapString(">"), NIL)), NIL), 0)));
            }
          }
        }
        else if (subtypeOfP(testValue001, SGT_STREAMS_STELLA_OBJECT)) {
          { Object* tag004 = tag;
            Object* tag = tag004;

            tagvar = gensym("TAG");
            if (eolP) {
              return (listO(4, SYM_STREAMS_STELLA_LET, cons(cons(tagvar, listO(3, SYM_STREAMS_STELLA_STRING, tag, NIL)), NIL), listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, listO(3, wrapString("<"), tagvar, cons(wrapString(">"), NIL))), body->concatenate(cons(listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, listO(5, wrapString("</"), listO(3, SYM_STREAMS_STELLA_SUBSEQUENCE, tagvar, listO(3, wrapInteger(0), listO(3, SYM_STREAMS_STELLA_POSITION, tagvar, listO(3, wrapCharacter(' '), wrapInteger(0), NIL)), NIL)), wrapString(">"), SYM_STREAMS_STELLA_EOL, NIL)), NIL), 0)));
            }
            else {
              return (listO(4, SYM_STREAMS_STELLA_LET, cons(cons(tagvar, listO(3, SYM_STREAMS_STELLA_STRING, tag, NIL)), NIL), listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, listO(3, wrapString("<"), tagvar, cons(wrapString(">"), NIL))), body->concatenate(cons(listO(3, SYM_STREAMS_STELLA_PRINT_STREAM, stream, listO(4, wrapString("</"), listO(3, SYM_STREAMS_STELLA_SUBSEQUENCE, tagvar, listO(3, wrapInteger(0), listO(3, SYM_STREAMS_STELLA_POSITION, tagvar, listO(3, wrapCharacter(' '), wrapInteger(0), NIL)), NIL)), wrapString(">"), NIL)), NIL), 0)));
            }
          }
        }
        else {
          { OutputStringStream* stream001 = newOutputStringStream();

            *(stream001->nativeStream) << "`" << testValue001 << "'" << " is not a valid case option";
            throw *newStellaException(stream001->theStringReader());
          }
        }
      }
    }
  }
}

Object* withHtmlTag(Cons* tagAndStream, Cons* body) {
  return (expandMarkupTagFunction(tagAndStream, body, false));
}

Object* withXmlTag(Cons* tagAndStream, Cons* body) {
  return (expandMarkupTagFunction(tagAndStream, body, true));
}

boolean htmlCharacterNeedsQuotingP(char ch) {
  return (stringMemberP(oHTML_QUOTED_CHARACTERSo, ch));
}

void writeHtmlCharacterQuotingSpecialCharacters(std::ostream* stream, char ch) {
  switch (ch) {
    case '>': 
      *(stream) << "&gt;";
      break;
    case '<': 
      *(stream) << "&lt;";
      break;
    case '&': 
      *(stream) << "&amp;";
      break;
    case '"': 
      *(stream) << "&quot;";
      break;
    case '\n': 
    case '\r': 
      *(stream) << "&#" << (int)(unsigned char) ch << ";";
      break;
    default:
      *(stream) << ch;
      break;
  }
  return;
}

void writeHtmlQuotingSpecialCharacters(std::ostream* stream, const char* input) {
  { char ch = NULL_CHARACTER;
    const char* vector000 = input;
    int index000 = 0;
    int length000 = strlen(vector000);

    for  (; index000 < length000; 
          index000 = index000 + 1) {
      ch = vector000[index000];
      writeHtmlCharacterQuotingSpecialCharacters(stream, ch);
    }
  }
  return;
}

void writeHtmlEscapingUrlSpecialCharacters(std::ostream* stream, const char* input) {
  // Writes a string and replaces unallowed URL characters according to RFC 2396
  // with %-format URL escape sequences.
  { char ch = NULL_CHARACTER;
    const char* vector000 = input;
    int index000 = 0;
    int length000 = strlen(vector000);

    for  (; index000 < length000; 
          index000 = index000 + 1) {
      ch = vector000[index000];
      if ((oCHARACTER_TYPE_TABLEo[(int)(unsigned char) ch] == KWD_STREAMS_LETTER) ||
          (oCHARACTER_TYPE_TABLEo[(int)(unsigned char) ch] == KWD_STREAMS_DIGIT)) {
        *(stream) << ch;
      }
      else {
        switch (ch) {
          case '-': 
          case '_': 
          case '.': 
          case '~': 
            *(stream) << ch;
            break;
          default:
            { int code = (int)(unsigned char) ch;

              if (code < 16) {
                *(stream) << "%0" << integerToHexString(((long long int)(code)));
              }
              else {
                *(stream) << "%" << integerToHexString(((long long int)(code)));
              }
            }
            break;
        }
      }
    }
  }
  return;
}

int hexCharacterValue(char c) {
  // Convert the base-16 hex character `c' into a base-10 number.
  { int code = (int)(unsigned char) c;

    if (code < 65) {
      return (code - 48);
    }
    else if (code < 97) {
      return (code - 55);
    }
    else {
      return (code - 87);
    }
  }
}

const char* unescapeUrlString(const char* input) {
  // Takes a string and replaces %-format URL escape sequences with their real
  // character equivalent according to RFC 2396.
  if (stringPosition(input, '%', 0) == NULL_INTEGER) {
    return (input);
  }
  else {
    { char* result = makeRawMutableString(strlen(input));
      int iOut = 0;
      int iIn = 0;
      char charSave = NULL_CHARACTER;
      int charValue = 0;
      int escapeValue = 0;
      int iMax = strlen(input);

      while (iIn < iMax) {
        if (input[iIn] == '%') {
          {
            iIn = iIn + 1;
            if (iIn < iMax) {
              {
                charSave = input[iIn];
                charValue = hexCharacterValue(charSave);
                iIn = iIn + 1;
                if ((charValue != NULL_INTEGER) &&
                    (iIn < iMax)) {
                  {
                    escapeValue = 16 * charValue;
                    charValue = hexCharacterValue(input[iIn]);
                    if (charValue != NULL_INTEGER) {
                      {
                        result[iOut] = ((char) (escapeValue + charValue));
                      }
                    }
                    else {
                      {
                        result[iOut] = '%';
                        result[(iOut = iOut + 1)] = charSave;
                        result[(iOut = iOut + 1)] = (input[iIn]);
                      }
                    }
                  }
                }
                else {
                  {
                    result[iOut] = '%';
                    result[(iOut = iOut + 1)] = charSave;
                  }
                }
                iOut = iOut + 1;
                iIn = iIn + 1;
              }
            }
            else {
              {
                result[iOut] = '%';
                iOut = iOut + 1;
              }
            }
          }
        }
        else {
          {
            result[iOut] = (input[iIn]);
            iOut = iOut + 1;
            iIn = iIn + 1;
          }
        }
      }
      return (mutableStringSubsequence(result, 0, iOut));
    }
  }
}

KeyValueList* oHTML_ESCAPE_TABLEo = NULL;

const char* unescapeHtmlString(const char* input) {
  // Replaces HTML escape sequences such as &amp; with their
  // associated characters.
  { int incursor = 0;
    int outcursor = 0;
    int escapestart = stringPosition(input, '&', incursor);
    int escapeend = -1;
    int inputlength = -1;
    char* output = NULL;
    CharacterWrapper* character = NULL;

    for (;;) {
      if (escapestart == NULL_INTEGER) {
        if (output == NULL) {
          return (input);
        }
        else {
          break;
        }
      }
      escapeend = stringPosition(input, ';', escapestart);
      if (escapeend == NULL_INTEGER) {
        if (output == NULL) {
          return (input);
        }
        else {
          break;
        }
      }
      character = ((CharacterWrapper*)(oHTML_ESCAPE_TABLEo->lookup(wrapString(stringSubsequence(input, escapestart + 1, escapeend)))));
      if (!((boolean)(character))) {
        escapestart = stringPosition(input, '&', escapeend);
        continue;
      }
      if (output == NULL) {
        inputlength = strlen(input);
        output = makeRawMutableString(inputlength);
      }
      while (incursor < escapestart) {
        output[outcursor] = (input[incursor]);
        incursor = incursor + 1;
        outcursor = outcursor + 1;
      }
      output[outcursor] = (character->wrapperValue);
      outcursor = outcursor + 1;
      incursor = escapeend + 1;
      escapestart = stringPosition(input, '&', escapeend);
    }
    while (incursor < inputlength) {
      output[outcursor] = (input[incursor]);
      incursor = incursor + 1;
      outcursor = outcursor + 1;
    }
    return (stringSubsequence(output, 0, outcursor));
  }
}

Object* accessStreamIteratorSlotValue(StreamIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_STREAMS_STELLA_THE_STREAM) {
    if (setvalueP) {
      self->theStream = ((InputStream*)(value));
    }
    else {
      value = self->theStream;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

SExpressionIterator* newSExpressionIterator() {
  { SExpressionIterator* self = NULL;

    self = new SExpressionIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->theStream = NULL;
    return (self);
  }
}

void SExpressionIterator::free() {
  { SExpressionIterator* self = this;

    if (terminateStreamIteratorP(self)) {
      unmake(self);
    }
  }
}

Surrogate* SExpressionIterator::primaryType() {
  { SExpressionIterator* self = this;

    return (SGT_STREAMS_STELLA_S_EXPRESSION_ITERATOR);
  }
}

Object* accessSExpressionIteratorSlotValue(SExpressionIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_STREAMS_STELLA_VALUE) {
    if (setvalueP) {
      self->value = value;
    }
    else {
      value = self->value;
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

LineIterator* newLineIterator() {
  { LineIterator* self = NULL;

    self = new LineIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->theStream = NULL;
    return (self);
  }
}

void LineIterator::free() {
  { LineIterator* self = this;

    if (terminateStreamIteratorP(self)) {
      unmake(self);
    }
  }
}

Surrogate* LineIterator::primaryType() {
  { LineIterator* self = this;

    return (SGT_STREAMS_STELLA_LINE_ITERATOR);
  }
}

Object* accessLineIteratorSlotValue(LineIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_STREAMS_STELLA_VALUE) {
    if (setvalueP) {
      self->value = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->value);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

NativeLineIterator* newNativeLineIterator() {
  { NativeLineIterator* self = NULL;

    self = new NativeLineIterator();
    self->firstIterationP = true;
    self->value = NULL;
    self->theStream = NULL;
    return (self);
  }
}

void NativeLineIterator::free() {
  { NativeLineIterator* self = this;

    if (terminateStreamIteratorP(self)) {
      unmake(self);
    }
  }
}

Surrogate* NativeLineIterator::primaryType() {
  { NativeLineIterator* self = this;

    return (SGT_STREAMS_STELLA_NATIVE_LINE_ITERATOR);
  }
}

Object* accessNativeLineIteratorSlotValue(NativeLineIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_STREAMS_STELLA_VALUE) {
    if (setvalueP) {
      self->value = ((StringWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapString(self->value);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

CharacterIterator* newCharacterIterator() {
  { CharacterIterator* self = NULL;

    self = new CharacterIterator();
    self->firstIterationP = true;
    self->value = NULL_CHARACTER;
    self->theStream = NULL;
    return (self);
  }
}

void CharacterIterator::free() {
  { CharacterIterator* self = this;

    if (terminateStreamIteratorP(self)) {
      unmake(self);
    }
  }
}

Surrogate* CharacterIterator::primaryType() {
  { CharacterIterator* self = this;

    return (SGT_STREAMS_STELLA_CHARACTER_ITERATOR);
  }
}

Object* accessCharacterIteratorSlotValue(CharacterIterator* self, Symbol* slotname, Object* value, boolean setvalueP) {
  if (slotname == SYM_STREAMS_STELLA_VALUE) {
    if (setvalueP) {
      self->value = ((CharacterWrapper*)(value))->wrapperValue;
    }
    else {
      value = wrapCharacter(self->value);
    }
  }
  else {
    { OutputStringStream* stream000 = newOutputStringStream();

      *(stream000->nativeStream) << "`" << slotname << "'" << " is not a valid case option";
      throw *newStellaException(stream000->theStringReader());
    }
  }
  return (value);
}

boolean terminateStreamIteratorP(StreamIterator* self) {
  if (((boolean)(self->theStream))) {
    self->theStream->free();
  }
  return (true);
}

SExpressionIterator* sExpressions(InputStream* stream) {
  { SExpressionIterator* self000 = newSExpressionIterator();

    self000->theStream = stream;
    { SExpressionIterator* value000 = self000;

      return (value000);
    }
  }
}

boolean SExpressionIterator::nextP() {
  { SExpressionIterator* self = this;

    self->firstIterationP = false;
    { Object* object = NULL;
      boolean eofP = false;

      object = readSExpression(self->theStream, eofP);
      if (eofP) {
        closeStream(self->theStream);
        return (false);
      }
      else {
        self->value = object;
        return (true);
      }
    }
  }
}

NativeLineIterator* nativeLines(InputStream* stream) {
  { NativeLineIterator* self000 = newNativeLineIterator();

    self000->theStream = stream;
    { NativeLineIterator* value000 = self000;

      return (value000);
    }
  }
}

boolean NativeLineIterator::nextP() {
  { NativeLineIterator* self = this;

    { const char* line = nativeReadLine(self->theStream);

      self->firstIterationP = false;
      self->value = line;
      if (line == NULL) {
        closeStream(self->theStream);
        return (false);
      }
      else {
        return (true);
      }
    }
  }
}

LineIterator* lines(InputStream* stream) {
  { LineIterator* self000 = newLineIterator();

    self000->theStream = stream;
    { LineIterator* value000 = self000;

      return (value000);
    }
  }
}

boolean LineIterator::nextP() {
  { LineIterator* self = this;

    { const char* line = readLine(self->theStream);

      self->firstIterationP = false;
      self->value = line;
      if (line == NULL) {
        closeStream(self->theStream);
        return (false);
      }
      else {
        return (true);
      }
    }
  }
}

CharacterIterator* characters(InputStream* stream) {
  { CharacterIterator* self000 = newCharacterIterator();

    self000->theStream = stream;
    { CharacterIterator* value000 = self000;

      return (value000);
    }
  }
}

boolean CharacterIterator::nextP() {
  { CharacterIterator* self = this;

    self->firstIterationP = false;
    { char chaR = NULL_CHARACTER;
      boolean eofP = false;

      chaR = readCharacter(self->theStream, eofP);
      if (eofP) {
        self->value = NULL_CHARACTER;
        closeStream(self->theStream);
        return (false);
      }
      else {
        self->value = chaR;
        return (true);
      }
    }
  }
}

KeyValueList* oLOGGING_REGISTRYo = NULL;

double oLOGGING_LOCAL_TIME_ZONEo = NULL_FLOAT;

Object* lookupLoggingParameter(const char* module, Keyword* parameter, Object* defaulT) {
  // Lookup logging `parameter' for `module'.  Use `default' if no
  // value is defined.
  { Object* value = NULL;

    { StringWrapper* mod = NULL;
      PropertyList* props = NULL;
      KvCons* iter000 = oLOGGING_REGISTRYo->theKvList;

      for  (; ((boolean)(iter000)); 
            iter000 = iter000->rest) {
        mod = ((StringWrapper*)(iter000->key));
        props = ((PropertyList*)(iter000->value));
        if (stringEqualP(module, mod->wrapperValue)) {
          { Object* temp000 = props->lookup(parameter);

            value = (((boolean)(temp000)) ? temp000 : defaulT);
          }
          break;
        }
      }
    }
    return (value);
  }
}

void setLoggingParameters(const char* module, Cons* paramsAvalues) {
  // Set logging parameters for `module'.  The supported parameters are:
  //   :LOG-LEVELS - a cons list of legal levels in ascending log level order;
  //                 for example, (:NONE :LOW :MEDIUM :HIGH) or (0 1 2 3).
  //   :LEVEL      - the current log level for `module'
  //   :STREAM     - the stream or file to log to (defaults to STANDARD-OUTPUT)
  //   :PREFIX     - the prefix to use to identify the module (defaults to `module')
  //   :MAX-WIDTH  - logging output lines will be kept to approximately this width
  //                 (defaults to 10000, minimum width of about 30 is used to
  //                 print line header information).
  { PropertyList* options = vetOptions(paramsAvalues, getQuotedTree("((:LOG-LEVELS :LEVEL :STREAM :PREFIX :MAX-WIDTH) \"/STELLA\")", "/STELLA"));
    PropertyList* loginfo = NULL;

    { StringWrapper* mod = NULL;
      PropertyList* props = NULL;
      KvCons* iter000 = oLOGGING_REGISTRYo->theKvList;

      for  (; ((boolean)(iter000)); 
            iter000 = iter000->rest) {
        mod = ((StringWrapper*)(iter000->key));
        props = ((PropertyList*)(iter000->value));
        if (stringEqualP(module, mod->wrapperValue)) {
          loginfo = props;
        }
      }
    }
    if (!((boolean)(loginfo))) {
      loginfo = newPropertyList();
      oLOGGING_REGISTRYo->insertAt(wrapString(module), loginfo);
    }
    { Object* key = NULL;
      Object* value = NULL;
      Cons* iter001 = options->thePlist;

      for  (; !(iter001 == NIL); 
            iter001 = iter001->rest->rest) {
        key = iter001->value;
        value = iter001->rest->value;
        loginfo->insertAt(key, value);
      }
    }
  }
}

void setLoggingParametersEvaluatorWrapper(Cons* arguments) {
  setLoggingParameters(((StringWrapper*)(arguments->value))->wrapperValue, arguments->rest);
}

void setLogLevel(const char* module, Object* level) {
  // Set the log-level for `module' to `level'.  This is a
  // convenience function for this common operation.
  setLoggingParameters(module, consList(2, KWD_STREAMS_LEVEL, level));
}

void setLogLevelEvaluatorWrapper(Cons* arguments) {
  setLogLevel(((StringWrapper*)(arguments->value))->wrapperValue, arguments->rest->value);
}

boolean logLevelLE(Object* level, const char* module) {
  // Return TRUE if `level' is lower than or equal to the current
  // log level of `module'.  Return FALSE if any of them are undefined.
  { Cons* loglevels = ((Cons*)(lookupLoggingParameter(module, KWD_STREAMS_LOG_LEVELS, NIL)));
    Object* modulelevel = lookupLoggingParameter(module, KWD_STREAMS_LEVEL, NULL);
    int pos1 = loglevels->position(level, 0);
    int pos2 = loglevels->position(modulelevel, 0);

    return ((pos1 != NULL_INTEGER) &&
        ((pos2 != NULL_INTEGER) &&
         (pos1 <= pos2)));
  }
}

// The number of spaces to print before the content of a log message.
int oLOG_INDENT_LEVELo = 0;

void bumpLogIndent() {
  // Increase the indentation level for subsequent log messages.
  oLOG_INDENT_LEVELo = oLOG_INDENT_LEVELo + 2;
}

void unbumpLogIndent() {
  // Decrease the indentation level for subsequent log messages.
  oLOG_INDENT_LEVELo = oLOG_INDENT_LEVELo - 2;
}

OutputStream* getLogStream(const char* module) {
  // Return a valid log stream for `module'.
  { Object* streamspec = lookupLoggingParameter(module, KWD_STREAMS_STREAM, STANDARD_OUTPUT);

    { Surrogate* testValue000 = safePrimaryType(streamspec);

      if (subtypeOfStringP(testValue000)) {
        { Object* streamspec000 = streamspec;
          StringWrapper* streamspec = ((StringWrapper*)(streamspec000));

          return (openOutputFile(streamspec->wrapperValue, 4, KWD_STREAMS_IF_EXISTS, KWD_STREAMS_APPEND, KWD_STREAMS_IF_NOT_EXISTS, KWD_STREAMS_CREATE));
        }
      }
      else if (subtypeOfP(testValue000, SGT_STREAMS_STELLA_OUTPUT_STREAM)) {
        { Object* streamspec001 = streamspec;
          OutputStream* streamspec = ((OutputStream*)(streamspec001));

          return (streamspec);
        }
      }
      else {
        { OutputStringStream* stream000 = newOutputStringStream();

          *(stream000->nativeStream) << "`" << testValue000 << "'" << " is not a valid case option";
          throw *newStellaException(stream000->theStringReader());
        }
      }
    }
  }
}

void logMessage(const char* module, Object* loglevel, Cons* message) {
  // Log all elements of `message' to `module's log stream if
  // `logLevel' is the same or lower than the `module's log level.  Interprets `EOL'
  // or :EOL to print a line terminator.
  if (logLevelLE(loglevel, module)) {
    { OutputStream* log = getLogStream(module);
      const char* moduleprefix = ((StringWrapper*)(lookupLoggingParameter(module, KWD_STREAMS_PREFIX, wrapString(module))))->wrapperValue;
      int maxroom = ((IntegerWrapper*)(lookupLoggingParameter(module, KWD_STREAMS_MAX_WIDTH, wrapInteger(10000))))->wrapperValue;
      int room = maxroom;
      const char* eltstring = NULL;

      try {
        *(log->nativeStream) << "[" << makeCurrentDateTime()->calendarDateToString(oLOGGING_LOCAL_TIME_ZONEo, false, false) << ((stringEqlP(moduleprefix, "") ? "" : " ")) << moduleprefix << "] ";
        { int i = NULL_INTEGER;
          int iter000 = 1;
          int upperBound000 = oLOG_INDENT_LEVELo;
          boolean unboundedP000 = upperBound000 == NULL_INTEGER;

          for  (; unboundedP000 ||
                    (iter000 <= upperBound000); 
                iter000 = iter000 + 1) {
            i = iter000;
            i = i;
            *(log->nativeStream) << " ";
          }
        }
        room = room - (27 + strlen(moduleprefix) + oLOG_INDENT_LEVELo);
        { 
          BIND_STELLA_SPECIAL(oPRINTREADABLYpo, boolean, true);
          { Object* elt = NULL;
            Cons* iter001 = message;

            for (; !(iter001 == NIL); iter001 = iter001->rest) {
              elt = iter001->value;
              { Surrogate* testValue000 = safePrimaryType(elt);

                if (subtypeOfStringP(testValue000)) {
                  { Object* elt000 = elt;
                    StringWrapper* elt = ((StringWrapper*)(elt000));

                    eltstring = elt->wrapperValue;
                  }
                }
                else if (subtypeOfP(testValue000, SGT_STREAMS_STELLA_GENERALIZED_SYMBOL)) {
                  { Object* elt001 = elt;
                    GeneralizedSymbol* elt = ((GeneralizedSymbol*)(elt001));

                    if (stringEqlP(elt->symbolName, "EOL")) {
                      *(log->nativeStream) << std::endl;
                      room = maxroom;
                      continue;
                    }
                    else {
                      eltstring = stringify(elt);
                    }
                  }
                }
                else {
                  eltstring = stringify(elt);
                }
              }
              if (room < strlen(eltstring)) {
                *(log->nativeStream) << stringSubsequence(eltstring, 0, room) << "...";
              }
              else {
                *(log->nativeStream) << eltstring;
              }
            }
          }
        }
        *(log->nativeStream) << std::endl;
        flushOutput(log);
      }
catch (...) {
        throw;
      }
      if (isaP(log, SGT_STREAMS_STELLA_FILE_OUTPUT_STREAM)) {
        closeStream(log);
      }
    }
  }
}

void logmsg(const char* module, Object* loglevel, int message, ...) {
  // Log all elements of `message' to `module's log stream if
  // `logLevel' is the same or lower than the `module's log level.  Interprets `EOL'
  // or :EOL to print a line terminator.
  { Cons* arglist000 = NIL;

    { va_list iter000;
      int iter000Count = message;
      Object* arg000 = NULL;
      Cons* collect000 = NULL;

      va_start(iter000, message);
            for  (; (iter000Count--) > 0; ) {
        arg000 = va_arg(iter000, Object*);
        if (!((boolean)(collect000))) {
          {
            collect000 = cons(arg000, NIL);
            if (arglist000 == NIL) {
              arglist000 = collect000;
            }
            else {
              addConsToEndOfConsList(arglist000, collect000);
            }
          }
        }
        else {
          {
            collect000->rest = cons(arg000, NIL);
            collect000 = collect000->rest;
          }
        }
      }
      va_end(iter000);
    }
    logMessage(module, loglevel, arglist000);
  }
}

void helpStartupStreams1() {
  {
    SYM_STREAMS_STELLA_EOL = ((Symbol*)(internRigidSymbolWrtModule("EOL", NULL, 0)));
    SYM_STREAMS_STELLA_PRINT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("PRINT-STREAM", NULL, 0)));
    SYM_STREAMS_STELLA_STANDARD_OUTPUT = ((Symbol*)(internRigidSymbolWrtModule("STANDARD-OUTPUT", NULL, 0)));
    SYM_STREAMS_STELLA_FOREACH = ((Symbol*)(internRigidSymbolWrtModule("FOREACH", NULL, 0)));
    SYM_STREAMS_STELLA_I = ((Symbol*)(internRigidSymbolWrtModule("I", NULL, 0)));
    SYM_STREAMS_STELLA_IN = ((Symbol*)(internRigidSymbolWrtModule("IN", NULL, 0)));
    SYM_STREAMS_STELLA_INTERVAL = ((Symbol*)(internRigidSymbolWrtModule("INTERVAL", NULL, 0)));
    SYM_STREAMS_STELLA_DO = ((Symbol*)(internRigidSymbolWrtModule("DO", NULL, 0)));
    SYM_STREAMS_STELLA_IGNORE = ((Symbol*)(internRigidSymbolWrtModule("IGNORE", NULL, 0)));
    KWD_STREAMS_COMMON_LISP = ((Keyword*)(internRigidSymbolWrtModule("COMMON-LISP", NULL, 2)));
    KWD_STREAMS_WARN = ((Keyword*)(internRigidSymbolWrtModule("WARN", NULL, 2)));
    SYM_STREAMS_STELLA_STANDARD_WARNING = ((Symbol*)(internRigidSymbolWrtModule("STANDARD-WARNING", NULL, 0)));
    SYM_STREAMS_STELLA_NULL = ((Symbol*)(internRigidSymbolWrtModule("NULL", NULL, 0)));
    SYM_STREAMS_STELLA_STELLA_EXCEPTION = ((Symbol*)(internRigidSymbolWrtModule("STELLA-EXCEPTION", NULL, 0)));
    SGT_STREAMS_STELLA_STRING_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("STRING-WRAPPER", NULL, 1)));
    SYM_STREAMS_STELLA_SIGNAL_EXCEPTION = ((Symbol*)(internRigidSymbolWrtModule("SIGNAL-EXCEPTION", NULL, 0)));
    SYM_STREAMS_STELLA_NEW = ((Symbol*)(internRigidSymbolWrtModule("NEW", NULL, 0)));
    KWD_STREAMS_MESSAGE = ((Keyword*)(internRigidSymbolWrtModule("MESSAGE", NULL, 2)));
    SYM_STREAMS_STELLA_LET = ((Symbol*)(internRigidSymbolWrtModule("LET", NULL, 0)));
    SYM_STREAMS_STELLA_OUTPUT_STRING_STREAM = ((Symbol*)(internRigidSymbolWrtModule("OUTPUT-STRING-STREAM", NULL, 0)));
    SYM_STREAMS_STELLA_THE_STRING = ((Symbol*)(internRigidSymbolWrtModule("THE-STRING", NULL, 0)));
    SYM_STREAMS_STELLA_SIGNAL = ((Symbol*)(internRigidSymbolWrtModule("SIGNAL", NULL, 0)));
    KWD_STREAMS_JAVA = ((Keyword*)(internRigidSymbolWrtModule("JAVA", NULL, 2)));
    SYM_STREAMS_STELLA_ERROR_MESSAGE_ = ((Symbol*)(internRigidSymbolWrtModule("ERROR_MESSAGE_", NULL, 0)));
    SYM_STREAMS_STELLA_VERBATIM = ((Symbol*)(internRigidSymbolWrtModule("VERBATIM", NULL, 0)));
    KWD_STREAMS_CONTINUABLE_ERROR = ((Keyword*)(internRigidSymbolWrtModule("CONTINUABLE-ERROR", NULL, 2)));
    SYM_STREAMS_STELLA_READ_EXCEPTION = ((Symbol*)(internRigidSymbolWrtModule("READ-EXCEPTION", NULL, 0)));
    SYM_STREAMS_STELLA_DE_UGLIFY_PARSE_TREE = ((Symbol*)(internRigidSymbolWrtModule("DE-UGLIFY-PARSE-TREE", NULL, 0)));
    SYM_STREAMS_STELLA_SPECIAL = ((Symbol*)(internRigidSymbolWrtModule("SPECIAL", NULL, 0)));
    SYM_STREAMS_STELLA_oPRINTREADABLYpo = ((Symbol*)(internRigidSymbolWrtModule("*PRINTREADABLY?*", NULL, 0)));
    SYM_STREAMS_STELLA_TRUE = ((Symbol*)(internRigidSymbolWrtModule("TRUE", NULL, 0)));
    SYM_STREAMS_STELLA_SIGNAL_TRANSLATION_ERROR = ((Symbol*)(internRigidSymbolWrtModule("SIGNAL-TRANSLATION-ERROR", NULL, 0)));
    SYM_STREAMS_STELLA_UNLESS = ((Symbol*)(internRigidSymbolWrtModule("UNLESS", NULL, 0)));
    SYM_STREAMS_STELLA_SUPPRESS_WARNINGSp = ((Symbol*)(internRigidSymbolWrtModule("SUPPRESS-WARNINGS?", NULL, 0)));
    SYM_STREAMS_STELLA_PRINT_ERROR_CONTEXT = ((Symbol*)(internRigidSymbolWrtModule("PRINT-ERROR-CONTEXT", NULL, 0)));
    SYM_STREAMS_STELLA_STANDARD_ERROR = ((Symbol*)(internRigidSymbolWrtModule("STANDARD-ERROR", NULL, 0)));
    SYM_STREAMS_STELLA_SIGNAL_TRANSLATION_NOTE = ((Symbol*)(internRigidSymbolWrtModule("SIGNAL-TRANSLATION-NOTE", NULL, 0)));
    SYM_STREAMS_STELLA_SIGNAL_TRANSLATION_WARNING = ((Symbol*)(internRigidSymbolWrtModule("SIGNAL-TRANSLATION-WARNING", NULL, 0)));
    SYM_STREAMS_STELLA_WHEN = ((Symbol*)(internRigidSymbolWrtModule("WHEN", NULL, 0)));
    SYM_STREAMS_STELLA_NOT = ((Symbol*)(internRigidSymbolWrtModule("NOT", NULL, 0)));
    KWD_STREAMS_ERROR = ((Keyword*)(internRigidSymbolWrtModule("ERROR", NULL, 2)));
    SYM_STREAMS_STELLA_oEVALUATIONTREEo = ((Symbol*)(internRigidSymbolWrtModule("*EVALUATIONTREE*", NULL, 0)));
    SYM_STREAMS_STELLA_DEFINEDp = ((Symbol*)(internRigidSymbolWrtModule("DEFINED?", NULL, 0)));
    SYM_STREAMS_STELLA_oEVALUATIONPARENTTREEo = ((Symbol*)(internRigidSymbolWrtModule("*EVALUATIONPARENTTREE*", NULL, 0)));
    SYM_STREAMS_STELLA_EVALUATION_EXCEPTION = ((Symbol*)(internRigidSymbolWrtModule("EVALUATION-EXCEPTION", NULL, 0)));
    SGT_STREAMS_STELLA_LITERAL_WRAPPER = ((Surrogate*)(internRigidSymbolWrtModule("LITERAL-WRAPPER", NULL, 1)));
    SYM_STREAMS_STELLA_STRINGIFY = ((Symbol*)(internRigidSymbolWrtModule("STRINGIFY", NULL, 0)));
    SYM_STREAMS_STELLA_VRLET = ((Symbol*)(internRigidSymbolWrtModule("VRLET", NULL, 0)));
    SYM_STREAMS_STELLA_STRING = ((Symbol*)(internRigidSymbolWrtModule("STRING", NULL, 0)));
    SYM_STREAMS_STELLA_SETQ = ((Symbol*)(internRigidSymbolWrtModule("SETQ", NULL, 0)));
    SYM_STREAMS_STELLA_CONCATENATE = ((Symbol*)(internRigidSymbolWrtModule("CONCATENATE", NULL, 0)));
    KWD_STREAMS_CLOSED = ((Keyword*)(internRigidSymbolWrtModule("CLOSED", NULL, 2)));
    KWD_STREAMS_IF_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("IF-EXISTS", NULL, 2)));
    KWD_STREAMS_IF_EXISTS_ACTION = ((Keyword*)(internRigidSymbolWrtModule("IF-EXISTS-ACTION", NULL, 2)));
    KWD_STREAMS_IF_NOT_EXISTS = ((Keyword*)(internRigidSymbolWrtModule("IF-NOT-EXISTS", NULL, 2)));
    KWD_STREAMS_IF_NOT_EXISTS_ACTION = ((Keyword*)(internRigidSymbolWrtModule("IF-NOT-EXISTS-ACTION", NULL, 2)));
    KWD_STREAMS_SUPERSEDE = ((Keyword*)(internRigidSymbolWrtModule("SUPERSEDE", NULL, 2)));
    KWD_STREAMS_CREATE = ((Keyword*)(internRigidSymbolWrtModule("CREATE", NULL, 2)));
    KWD_STREAMS_CREATE_PATH = ((Keyword*)(internRigidSymbolWrtModule("CREATE-PATH", NULL, 2)));
    KWD_STREAMS_ABORT = ((Keyword*)(internRigidSymbolWrtModule("ABORT", NULL, 2)));
  }
}

void helpStartupStreams2() {
  {
    KWD_STREAMS_PROBE = ((Keyword*)(internRigidSymbolWrtModule("PROBE", NULL, 2)));
    KWD_STREAMS_APPEND = ((Keyword*)(internRigidSymbolWrtModule("APPEND", NULL, 2)));
    KWD_STREAMS_OPEN = ((Keyword*)(internRigidSymbolWrtModule("OPEN", NULL, 2)));
    SGT_STREAMS_STELLA_INPUT_FILE_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("INPUT-FILE-STREAM", NULL, 1)));
    SGT_STREAMS_STELLA_OUTPUT_FILE_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("OUTPUT-FILE-STREAM", NULL, 1)));
    SGT_STREAMS_STELLA_INPUT_STRING_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("INPUT-STRING-STREAM", NULL, 1)));
    SGT_STREAMS_STELLA_OUTPUT_STRING_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("OUTPUT-STRING-STREAM", NULL, 1)));
    SGT_STREAMS_STELLA_INPUT_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("INPUT-STREAM", NULL, 1)));
    SGT_STREAMS_STELLA_OUTPUT_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("OUTPUT-STREAM", NULL, 1)));
    KWD_STREAMS_BLOCK = ((Keyword*)(internRigidSymbolWrtModule("BLOCK", NULL, 2)));
    SYM_STREAMS_STELLA_FILE_INPUT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("FILE-INPUT-STREAM", NULL, 0)));
    SYM_STREAMS_STELLA_UNWIND_PROTECT = ((Symbol*)(internRigidSymbolWrtModule("UNWIND-PROTECT", NULL, 0)));
    SYM_STREAMS_STELLA_PROGN = ((Symbol*)(internRigidSymbolWrtModule("PROGN", NULL, 0)));
    SYM_STREAMS_STELLA_OPEN_INPUT_FILE = ((Symbol*)(internRigidSymbolWrtModule("OPEN-INPUT-FILE", NULL, 0)));
    SYM_STREAMS_STELLA_FREE = ((Symbol*)(internRigidSymbolWrtModule("FREE", NULL, 0)));
    SYM_STREAMS_STELLA_FILE_OUTPUT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("FILE-OUTPUT-STREAM", NULL, 0)));
    SYM_STREAMS_STELLA_OPEN_OUTPUT_FILE = ((Symbol*)(internRigidSymbolWrtModule("OPEN-OUTPUT-FILE", NULL, 0)));
    SYM_STREAMS_STELLA_INPUT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("INPUT-STREAM", NULL, 0)));
    SYM_STREAMS_STELLA_OUTPUT_STREAM = ((Symbol*)(internRigidSymbolWrtModule("OUTPUT-STREAM", NULL, 0)));
    SYM_STREAMS_STELLA_MV_SETQ = ((Symbol*)(internRigidSymbolWrtModule("MV-SETQ", NULL, 0)));
    SYM_STREAMS_STELLA_OPEN_NETWORK_STREAM = ((Symbol*)(internRigidSymbolWrtModule("OPEN-NETWORK-STREAM", NULL, 0)));
    SGT_STREAMS_STELLA_OBJECT = ((Surrogate*)(internRigidSymbolWrtModule("OBJECT", NULL, 1)));
    SYM_STREAMS_STELLA_SUBSEQUENCE = ((Symbol*)(internRigidSymbolWrtModule("SUBSEQUENCE", NULL, 0)));
    SYM_STREAMS_STELLA_POSITION = ((Symbol*)(internRigidSymbolWrtModule("POSITION", NULL, 0)));
    KWD_STREAMS_LETTER = ((Keyword*)(internRigidSymbolWrtModule("LETTER", NULL, 2)));
    KWD_STREAMS_DIGIT = ((Keyword*)(internRigidSymbolWrtModule("DIGIT", NULL, 2)));
    SYM_STREAMS_STELLA_THE_STREAM = ((Symbol*)(internRigidSymbolWrtModule("THE-STREAM", NULL, 0)));
    SGT_STREAMS_STELLA_S_EXPRESSION_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("S-EXPRESSION-ITERATOR", NULL, 1)));
    SYM_STREAMS_STELLA_VALUE = ((Symbol*)(internRigidSymbolWrtModule("VALUE", NULL, 0)));
    SGT_STREAMS_STELLA_LINE_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("LINE-ITERATOR", NULL, 1)));
    SGT_STREAMS_STELLA_NATIVE_LINE_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("NATIVE-LINE-ITERATOR", NULL, 1)));
    SGT_STREAMS_STELLA_CHARACTER_ITERATOR = ((Surrogate*)(internRigidSymbolWrtModule("CHARACTER-ITERATOR", NULL, 1)));
    KWD_STREAMS_LEVEL = ((Keyword*)(internRigidSymbolWrtModule("LEVEL", NULL, 2)));
    KWD_STREAMS_LOG_LEVELS = ((Keyword*)(internRigidSymbolWrtModule("LOG-LEVELS", NULL, 2)));
    KWD_STREAMS_STREAM = ((Keyword*)(internRigidSymbolWrtModule("STREAM", NULL, 2)));
    KWD_STREAMS_PREFIX = ((Keyword*)(internRigidSymbolWrtModule("PREFIX", NULL, 2)));
    KWD_STREAMS_MAX_WIDTH = ((Keyword*)(internRigidSymbolWrtModule("MAX-WIDTH", NULL, 2)));
    SGT_STREAMS_STELLA_GENERALIZED_SYMBOL = ((Surrogate*)(internRigidSymbolWrtModule("GENERALIZED-SYMBOL", NULL, 1)));
    SGT_STREAMS_STELLA_FILE_OUTPUT_STREAM = ((Surrogate*)(internRigidSymbolWrtModule("FILE-OUTPUT-STREAM", NULL, 1)));
    SYM_STREAMS_STELLA_STARTUP_STREAMS = ((Symbol*)(internRigidSymbolWrtModule("STARTUP-STREAMS", NULL, 0)));
    SYM_STREAMS_STELLA_METHOD_STARTUP_CLASSNAME = ((Symbol*)(internRigidSymbolWrtModule("METHOD-STARTUP-CLASSNAME", NULL, 0)));
  }
}

void helpStartupStreams3() {
  {
    EOL = SYM_STREAMS_STELLA_EOL;
    { InputStream* self000 = newInputStream();

      self000->nativeStream = &std::cin;
      STANDARD_INPUT = self000;
    }
    SINGLE_QUOTE_STRING = wrapString("'");
    SINGLE_BQUOTE_STRING = wrapString("`");
    oOPEN_FILE_STREAMSo = newList();
    oHTML_ESCAPE_TABLEo = newKeyValueList();
    oLOGGING_REGISTRYo = newKeyValueList();
    oLOGGING_LOCAL_TIME_ZONEo = getLocalTimeZone();
  }
}

void helpStartupStreams4() {
  {
    defineFunctionObject("MAKE-EARLY-OUTPUT-STREAM", "(DEFUN (MAKE-EARLY-OUTPUT-STREAM OUTPUT-STREAM) ((NATIVESTREAM NATIVE-OUTPUT-STREAM)))", ((cpp_function_code)(&makeEarlyOutputStream)), NULL);
    defineFunctionObject("FORMAT-MESSAGE-ARGUMENTS", "(DEFUN (FORMAT-MESSAGE-ARGUMENTS CONS) ((MESSAGEARGUMENTSTREE CONS) (TRAILINGEOL? BOOLEAN)))", ((cpp_function_code)(&formatMessageArguments)), NULL);
    defineFunctionObject("PRINT", "(DEFUN PRINT (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Print arguments to the standard output stream.\")", ((cpp_function_code)(&print)), NULL);
    defineFunctionObject("PRINT-SPACES", "(DEFUN PRINT-SPACES (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE :DOCUMENTATION \"(print-spaces [stream] N) prints N spaces onto stream.  If\nno stream form is provided, then STANDARD-OUTPUT will be used.\")", ((cpp_function_code)(&printSpaces)), NULL);
    defineFunctionObject("INFORM", "(DEFUN INFORM (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Print informative message, placing non-string arguments in quotes,\nand terminating with a newline.\")", ((cpp_function_code)(&inform)), NULL);
    defineFunctionObject("WARN", "(DEFUN WARN (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Signal warning message, placing non-string arguments in quotes.\")", ((cpp_function_code)(&warn)), NULL);
    defineFunctionObject("SIGNAL", "(DEFUN SIGNAL ((TYPE SYMBOL) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Signal error message, placing non-string arguments in quotes.\")", ((cpp_function_code)(&signal)), NULL);
    defineFunctionObject("ERROR", "(DEFUN ERROR (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Signal error message, placing non-string arguments in quotes.\")", ((cpp_function_code)(&error)), NULL);
    defineFunctionObject("CONTINUABLE-ERROR", "(DEFUN CONTINUABLE-ERROR (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Signal error message, placing non-string arguments in quotes.\")", ((cpp_function_code)(&continuableError)), NULL);
    defineFunctionObject("SIGNAL-READ-ERROR", "(DEFUN SIGNAL-READ-ERROR (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Specialized version of `signal' that throws a READ-EXCEPTION.\")", ((cpp_function_code)(&signalReadError)), NULL);
    defineFunctionObject("ENSURE-FILE-EXISTS", "(DEFUN ENSURE-FILE-EXISTS ((FILENAME STRING) (CONTEXT STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Ensures that `filename' exists.  If not, an exception of\ntype `NO-SUCH-FILE-EXCEPTION' is thrown with `context' supplying\ncontext for the error message.\")", ((cpp_function_code)(&ensureFileExists)), NULL);
    defineFunctionObject("ENSURE-FILE-DOES-NOT-EXIST", "(DEFUN ENSURE-FILE-DOES-NOT-EXIST ((FILENAME STRING) (CONTEXT STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Ensures that `filename' does not exist.  If it does,\nan exception of type `FILE-ALREADY-EXISTS-EXCEPTION' is thrown\nwith `context' supplying context for the error message.\")", ((cpp_function_code)(&ensureFileDoesNotExist)), NULL);
    defineFunctionObject("FORMAT-WALK-MESSAGE-ARGUMENTS", "(DEFUN (FORMAT-WALK-MESSAGE-ARGUMENTS CONS) ((MESSAGEARGUMENTSTREE CONS)))", ((cpp_function_code)(&formatWalkMessageArguments)), NULL);
    defineFunctionObject("WALK-ERROR", "(DEFUN WALK-ERROR (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&walkError)), NULL);
    defineFunctionObject("WALK-INFORM", "(DEFUN WALK-INFORM (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&walkInform)), NULL);
    defineFunctionObject("WALK-WARN", "(DEFUN WALK-WARN (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&walkWarn)), NULL);
    defineFunctionObject("SAFETY", "(DEFUN SAFETY ((LEVEL INTEGER-WRAPPER) (TEST OBJECT) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Signal warning message, placing non-string arguments in quotes.\")", ((cpp_function_code)(&safety)), NULL);
    defineFunctionObject("EVALUATION-ERROR", "(DEFUN EVALUATION-ERROR (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&evaluationError)), NULL);
    defineFunctionObject("FORMAT-STRING-MESSAGE-ARGUMENTS", "(DEFUN (FORMAT-STRING-MESSAGE-ARGUMENTS CONS) ((MESSAGEARGUMENTS CONS) (TRAILINGEOL? BOOLEAN)))", ((cpp_function_code)(&formatStringMessageArguments)), NULL);
    defineFunctionObject("MESSAGE-TO-STRING", "(DEFUN MESSAGE-TO-STRING (|&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&messageToString)), NULL);
    defineFunctionObject("TERMINATE-OUTPUT-STREAM?", "(DEFUN (TERMINATE-OUTPUT-STREAM? BOOLEAN) ((SELF OUTPUT-STREAM)))", ((cpp_function_code)(&terminateOutputStreamP)), NULL);
    defineFunctionObject("TERMINATE-INPUT-STREAM?", "(DEFUN (TERMINATE-INPUT-STREAM? BOOLEAN) ((SELF INPUT-STREAM)))", ((cpp_function_code)(&terminateInputStreamP)), NULL);
    defineFunctionObject("OPEN-OUTPUT-FILE", "(DEFUN (OPEN-OUTPUT-FILE FILE-OUTPUT-STREAM) ((FILENAME STRING) |&REST| (OPTIONS KEYWORD)) :DOCUMENTATION \"Open file `fileName' for output and return the resulting output stream.\nBy default the file will be created or overwritten if it already exists.\nIf `:IF-EXISTS' (or `:IF-EXISTS-ACTION') is one of the `options' its value\nspecifies what to do in case the file already exists.  If the value is\n`:SUPERSEDE' the pre-existing file will be overwritten.  If the value is\n`:APPEND' the preexisting file will be appended to (if the file did not\nyet exist the file will simply be created).  If the value is `:ERROR' then\nan error will be signaled.  If it is `:ABORT' or `:PROBE' the opening operation\nwill be aborted and NULL will be returned.\n\nIf `:IF-NOT-EXISTS' (or `:IF-NOT-EXISTS-ACTION') is one of the `options' its\nvalue specifies what to do in case the file does not already exist.  If the\nvalue is `:CREATE', the file will simply be created.  If the value is\n`:CREATE-PATH' the file will be created plus" " any non-existing directories\nin the directory path of `fileName' will also be created.  If the value is\n`:ERROR' then an error will be signaled.  If it is `:ABORT' or `:PROBE' the\nopening operation will be aborted and NULL will be returned.\" :PUBLIC? TRUE)", ((cpp_function_code)(&openOutputFile)), NULL);
    defineFunctionObject("INITIALIZE-FILE-OUTPUT-STREAM", "(DEFUN INITIALIZE-FILE-OUTPUT-STREAM ((SELF FILE-OUTPUT-STREAM)))", ((cpp_function_code)(&initializeFileOutputStream)), NULL);
    defineFunctionObject("TERMINATE-FILE-OUTPUT-STREAM?", "(DEFUN (TERMINATE-FILE-OUTPUT-STREAM? BOOLEAN) ((SELF FILE-OUTPUT-STREAM)))", ((cpp_function_code)(&terminateFileOutputStreamP)), NULL);
    defineFunctionObject("OPEN-INPUT-FILE", "(DEFUN (OPEN-INPUT-FILE FILE-INPUT-STREAM) ((FILENAME STRING) |&REST| (OPTIONS KEYWORD)) :DOCUMENTATION \"Open file `fileName' for input and return the resulting input stream.\nBy default signal an error if the file does not exist.  The only legal\noption so far is `:IF-NOT-EXISTS' (or `:IF-NOT-EXISTS-ACTION') which\nspecifies what to do in case the file does not exist.  If its value is\n`:ERROR' then an error will be signaled.  If it is `:ABORT' or `:PROBE'\nthe opening operation will be aborted and NULL will be returned.\" :PUBLIC? TRUE)", ((cpp_function_code)(&openInputFile)), NULL);
    defineFunctionObject("INITIALIZE-FILE-INPUT-STREAM", "(DEFUN INITIALIZE-FILE-INPUT-STREAM ((SELF FILE-INPUT-STREAM)))", ((cpp_function_code)(&initializeFileInputStream)), NULL);
    defineFunctionObject("TERMINATE-FILE-INPUT-STREAM?", "(DEFUN (TERMINATE-FILE-INPUT-STREAM? BOOLEAN) ((SELF FILE-INPUT-STREAM)))", ((cpp_function_code)(&terminateFileInputStreamP)), NULL);
    defineFunctionObject("INITIALIZE-STRING-OUTPUT-STREAM", "(DEFUN INITIALIZE-STRING-OUTPUT-STREAM ((SELF OUTPUT-STRING-STREAM)))", ((cpp_function_code)(&initializeStringOutputStream)), NULL);
    defineFunctionObject("TERMINATE-STRING-OUTPUT-STREAM?", "(DEFUN (TERMINATE-STRING-OUTPUT-STREAM? BOOLEAN) ((SELF OUTPUT-STRING-STREAM)))", ((cpp_function_code)(&terminateStringOutputStreamP)), NULL);
    defineMethodObject("(DEFMETHOD (THE-STRING-READER STRING) ((SELF OUTPUT-STRING-STREAM)))", wrapMethodCode(((cpp_method_code)(&OutputStringStream::theStringReader))), NULL);
    defineFunctionObject("INITIALIZE-STRING-INPUT-STREAM", "(DEFUN INITIALIZE-STRING-INPUT-STREAM ((SELF INPUT-STRING-STREAM)))", ((cpp_function_code)(&initializeStringInputStream)), NULL);
    defineFunctionObject("TERMINATE-STRING-INPUT-STREAM?", "(DEFUN (TERMINATE-STRING-INPUT-STREAM? BOOLEAN) ((SELF INPUT-STRING-STREAM)))", ((cpp_function_code)(&terminateStringInputStreamP)), NULL);
    defineFunctionObject("CLOSE-STREAM", "(DEFUN CLOSE-STREAM ((SELF STREAM)) :DOCUMENTATION \"Close the stream `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&closeStream)), NULL);
    defineFunctionObject("CLEAR-INPUT", "(DEFUN CLEAR-INPUT ((SELF INPUT-STREAM)) :DOCUMENTATION \"Clear all buffered raw and tokenized input of `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&clearInput)), NULL);
    defineFunctionObject("FLUSH-OUTPUT", "(DEFUN FLUSH-OUTPUT ((SELF OUTPUT-STREAM)) :DOCUMENTATION \"Flush all buffered output of `self'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&flushOutput)), NULL);
    defineFunctionObject("CLOSE-ALL-FILES", "(DEFUN CLOSE-ALL-FILES () :DOCUMENTATION \"Close all currently open file streams.  Use for emergencies or for cleanup.\" :PUBLIC? TRUE)", ((cpp_function_code)(&closeAllFiles)), NULL);
    defineFunctionObject("OPEN-NETWORK-STREAM", "(DEFUN (OPEN-NETWORK-STREAM INPUT-STREAM OUTPUT-STREAM) ((HOST STRING) (PORT INTEGER)) :DOCUMENTATION \"Open a TCP/IP network stream to `host' at `port' and return the result\nas an input/output stream pair.\" :PUBLIC? TRUE)", ((cpp_function_code)(&openNetworkStream)), NULL);
    defineFunctionObject("WITH-INPUT-FILE", "(DEFUN WITH-INPUT-FILE ((BINDING CONS) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Sets up an unwind-protected form which opens a file for\ninput and closes it afterwards.  The stream for reading is bound to the\nvariable provided in the macro form.\nSyntax is `(WITH-INPUT-FILE (var filename options*) body+)' where `options'\ncan be any that are legal for `open-input-file' (which see).\")", ((cpp_function_code)(&withInputFile)), NULL);
    defineFunctionObject("WITH-OUTPUT-FILE", "(DEFUN WITH-OUTPUT-FILE ((BINDING CONS) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Sets up an unwind-protected form which opens a file for\noutput and closes it afterwards.  The stream for writing is bound to the\nvariable provided in the macro form.\nSyntax is `(WITH-OUTPUT-FILE (var filename options*) body+)' where `options'\ncan be any that are legal for `open-output-file' (which see).\")", ((cpp_function_code)(&withOutputFile)), NULL);
    defineFunctionObject("WITH-NETWORK-STREAM", "(DEFUN WITH-NETWORK-STREAM ((BINDING CONS) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE :PUBLIC? TRUE :DOCUMENTATION \"Sets up an unwind-protected form which opens a network\nsocket stream to a host and port for input and output and closes it afterwards.\nSeparate variables as provided in the call are bound to the input and output\nstreams. Syntax is (WITH-NETWORK-STREAM (varIn varOut hostname port) body+)\")", ((cpp_function_code)(&withNetworkStream)), NULL);
    defineFunctionObject("NATIVE-FILE-INPUT-STREAM-POSITION", "(DEFUN (NATIVE-FILE-INPUT-STREAM-POSITION LONG-INTEGER) ((NSTREAM NATIVE-INPUT-STREAM)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (VERBATIM :CPP \"nstream->clear(std::ios::goodbit)\" :OTHERWISE NULL) (RETURN (VERBATIM :COMMON-LISP \"(CL:file-position nstream)\" :CPP \"nstream->tellg()\" :JAVA \"((NativeFileInputStream)nstream).position()\")))", ((cpp_function_code)(&nativeFileInputStreamPosition)), NULL);
    defineFunctionObject("NATIVE-FILE-INPUT-STREAM-POSITION-SETTER", "(DEFUN (NATIVE-FILE-INPUT-STREAM-POSITION-SETTER LONG-INTEGER) ((NSTREAM NATIVE-INPUT-STREAM) (NEWPOS LONG-INTEGER)) :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (VERBATIM :COMMON-LISP \"(CL:file-position nstream newpos)\" :CPP \"nstream->clear(std::ios::goodbit);nstream->seekg(newpos)\" :JAVA \"((NativeFileInputStream)nstream).position(newpos)\") (RETURN NEWPOS))", ((cpp_function_code)(&nativeFileInputStreamPositionSetter)), NULL);
    defineMethodObject("(DEFMETHOD (STREAM-POSITION LONG-INTEGER) ((SELF FILE-INPUT-STREAM)) :DOCUMENTATION \"Return the current position of the file input cursor in `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&InputFileStream::streamPosition))), NULL);
    defineMethodObject("(DEFMETHOD (STREAM-POSITION-SETTER LONG-INTEGER) ((SELF FILE-INPUT-STREAM) (NEWPOS LONG-INTEGER)) :DOCUMENTATION \"Set the current position of the file input cursor in `self' to `newpos'.\nIf `self' has any tokenizer state associated with it, this will also reset\nto the start state of the tokenizer table; otherwise, behavior would be\nunpredictable unless the character class of the new position is exactly the\nsame as the one following the most recent token.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&InputFileStream::streamPositionSetter))), NULL);
    defineFunctionObject("NATIVE-FILE-OUTPUT-STREAM-POSITION", "(DEFUN (NATIVE-FILE-OUTPUT-STREAM-POSITION LONG-INTEGER) ((NSTREAM NATIVE-OUTPUT-STREAM)) :GLOBALLY-INLINE? TRUE (RETURN (VERBATIM :COMMON-LISP \"(CL:file-position nstream)\" :CPP \"nstream->tellp()\" :JAVA \"((NativeFileOutputStream)nstream).position()\")))", ((cpp_function_code)(&nativeFileOutputStreamPosition)), NULL);
    defineFunctionObject("NATIVE-FILE-OUTPUT-STREAM-POSITION-SETTER", "(DEFUN (NATIVE-FILE-OUTPUT-STREAM-POSITION-SETTER LONG-INTEGER) ((NSTREAM NATIVE-OUTPUT-STREAM) (NEWPOS LONG-INTEGER)) :GLOBALLY-INLINE? TRUE (VERBATIM :COMMON-LISP \"(CL:file-position nstream newpos)\" :CPP \"nstream->seekp(newpos)\" :JAVA \"((NativeFileOutputStream)nstream).position(newpos)\") (RETURN NEWPOS))", ((cpp_function_code)(&nativeFileOutputStreamPositionSetter)), NULL);
    defineMethodObject("(DEFMETHOD (STREAM-POSITION LONG-INTEGER) ((SELF FILE-OUTPUT-STREAM)) :DOCUMENTATION \"Return the current position of the file input cursor in `self'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&OutputFileStream::streamPosition))), NULL);
    defineMethodObject("(DEFMETHOD (STREAM-POSITION-SETTER LONG-INTEGER) ((SELF FILE-OUTPUT-STREAM) (NEWPOS LONG-INTEGER)) :DOCUMENTATION \"Set the current position of the file input cursor in `self' to `newpos'.\" :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&OutputFileStream::streamPositionSetter))), NULL);
    defineFunctionObject("EXPAND-MARKUP-TAG-FUNCTION", "(DEFUN (EXPAND-MARKUP-TAG-FUNCTION CONS) ((TAG-AND-STREAM CONS) (BODY CONS) (XML? BOOLEAN)))", ((cpp_function_code)(&expandMarkupTagFunction)), NULL);
    defineFunctionObject("WITH-HTML-TAG", "(DEFUN WITH-HTML-TAG ((TAG-AND-STREAM CONS) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&withHtmlTag)), NULL);
    defineFunctionObject("WITH-XML-TAG", "(DEFUN WITH-XML-TAG ((TAG-AND-STREAM CONS) |&BODY| (BODY CONS)) :TYPE OBJECT :MACRO? TRUE)", ((cpp_function_code)(&withXmlTag)), NULL);
    defineFunctionObject("HTML-CHARACTER-NEEDS-QUOTING?", "(DEFUN (HTML-CHARACTER-NEEDS-QUOTING? BOOLEAN) ((CH CHARACTER)))", ((cpp_function_code)(&htmlCharacterNeedsQuotingP)), NULL);
    defineFunctionObject("WRITE-HTML-CHARACTER-QUOTING-SPECIAL-CHARACTERS", "(DEFUN WRITE-HTML-CHARACTER-QUOTING-SPECIAL-CHARACTERS ((STREAM NATIVE-OUTPUT-STREAM) (CH CHARACTER)) :GLOBALLY-INLINE? TRUE (CASE CH (#\\> (PRINT-STREAM STREAM \"&gt;\")) (#\\< (PRINT-STREAM STREAM \"&lt;\")) (#\\& (PRINT-STREAM STREAM \"&amp;\")) (#\\\" (PRINT-STREAM STREAM \"&quot;\")) ((#\\Linefeed #\\Return) (PRINT-STREAM STREAM \"&#\" (CHARACTER-CODE CH) \";\")) (OTHERWISE (PRINT-STREAM STREAM CH))) (RETURN))", ((cpp_function_code)(&writeHtmlCharacterQuotingSpecialCharacters)), NULL);
    defineFunctionObject("WRITE-HTML-QUOTING-SPECIAL-CHARACTERS", "(DEFUN WRITE-HTML-QUOTING-SPECIAL-CHARACTERS ((STREAM NATIVE-OUTPUT-STREAM) (INPUT STRING)))", ((cpp_function_code)(&writeHtmlQuotingSpecialCharacters)), NULL);
    defineFunctionObject("WRITE-HTML-ESCAPING-URL-SPECIAL-CHARACTERS", "(DEFUN WRITE-HTML-ESCAPING-URL-SPECIAL-CHARACTERS ((STREAM NATIVE-OUTPUT-STREAM) (INPUT STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Writes a string and replaces unallowed URL characters according to RFC 2396\nwith %-format URL escape sequences.\")", ((cpp_function_code)(&writeHtmlEscapingUrlSpecialCharacters)), NULL);
    defineFunctionObject("HEX-CHARACTER-VALUE", "(DEFUN (HEX-CHARACTER-VALUE INTEGER) ((C CHARACTER)) :DOCUMENTATION \"Convert the base-16 hex character `c' into a base-10 number.\" :PUBLIC? TRUE :GLOBALLY-INLINE? TRUE (LET ((CODE (CHARACTER-CODE C))) (COND ((< CODE 65) (RETURN (- CODE 48))) ((< CODE 97) (RETURN (- CODE 55))) (OTHERWISE (RETURN (- CODE 87))))))", ((cpp_function_code)(&hexCharacterValue)), NULL);
    defineFunctionObject("UNESCAPE-URL-STRING", "(DEFUN (UNESCAPE-URL-STRING STRING) ((INPUT STRING)) :PUBLIC? TRUE :DOCUMENTATION \"Takes a string and replaces %-format URL escape sequences with their real\ncharacter equivalent according to RFC 2396.\")", ((cpp_function_code)(&unescapeUrlString)), NULL);
    defineFunctionObject("UNESCAPE-HTML-STRING", "(DEFUN (UNESCAPE-HTML-STRING STRING) ((INPUT STRING)) :DOCUMENTATION \"Replaces HTML escape sequences such as &amp; with their\nassociated characters.\" :PUBLIC? TRUE)", ((cpp_function_code)(&unescapeHtmlString)), NULL);
    defineFunctionObject("TERMINATE-STREAM-ITERATOR?", "(DEFUN (TERMINATE-STREAM-ITERATOR? BOOLEAN) ((SELF STREAM-ITERATOR)))", ((cpp_function_code)(&terminateStreamIteratorP)), NULL);
  }
}

void startupStreams() {
  { 
    BIND_STELLA_SPECIAL(oMODULEo, Module*, oSTELLA_MODULEo);
    BIND_STELLA_SPECIAL(oCONTEXTo, Context*, oMODULEo);
    if (currentStartupTimePhaseP(2)) {
      helpStartupStreams1();
      helpStartupStreams2();
    }
    if (currentStartupTimePhaseP(4)) {
      helpStartupStreams3();
    }
    if (currentStartupTimePhaseP(5)) {
      { Class* clasS = defineClassFromStringifiedSource("STREAM-ITERATOR", "(DEFCLASS STREAM-ITERATOR (ABSTRACT-ITERATOR) :PUBLIC? TRUE :ABSTRACT? TRUE :DOCUMENTATION \"Iterator that yields tokens from an input stream.\" :SLOTS ((THE-STREAM :TYPE INPUT-STREAM)) :TERMINATOR TERMINATE-STREAM-ITERATOR?)");

        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessStreamIteratorSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("S-EXPRESSION-ITERATOR", "(DEFCLASS S-EXPRESSION-ITERATOR (STREAM-ITERATOR) :PUBLIC? TRUE :DOCUMENTATION \"Iterator that yields s-expressions from an input stream.\" :PARAMETERS ((ANY-VALUE :TYPE OBJECT)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newSExpressionIterator));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessSExpressionIteratorSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("LINE-ITERATOR", "(DEFCLASS LINE-ITERATOR (STREAM-ITERATOR) :PUBLIC? TRUE :DOCUMENTATION \"Iterator that yields lines with any line terminator sequence from an input stream.\" :PARAMETERS ((ANY-VALUE :TYPE STRING)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newLineIterator));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessLineIteratorSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("NATIVE-LINE-ITERATOR", "(DEFCLASS NATIVE-LINE-ITERATOR (STREAM-ITERATOR) :PUBLIC? TRUE :DOCUMENTATION \"Iterator that yields lines from an input stream.\" :PARAMETERS ((ANY-VALUE :TYPE STRING)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newNativeLineIterator));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessNativeLineIteratorSlotValue));
      }
      { Class* clasS = defineClassFromStringifiedSource("CHARACTER-ITERATOR", "(DEFCLASS CHARACTER-ITERATOR (STREAM-ITERATOR) :PUBLIC? TRUE :DOCUMENTATION \"Iterator that yields characters from an input stream.\" :PARAMETERS ((ANY-VALUE :TYPE CHARACTER)))");

        clasS->classConstructorCode = ((cpp_function_code)(&newCharacterIterator));
        clasS->classSlotAccessorCode = ((cpp_function_code)(&accessCharacterIteratorSlotValue));
      }
    }
    if (currentStartupTimePhaseP(6)) {
      finalizeClasses();
    }
    if (currentStartupTimePhaseP(7)) {
      helpStartupStreams4();
      defineFunctionObject("S-EXPRESSIONS", "(DEFUN (S-EXPRESSIONS S-EXPRESSION-ITERATOR) ((STREAM INPUT-STREAM)) :PUBLIC? TRUE)", ((cpp_function_code)(&sExpressions)), NULL);
      defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF S-EXPRESSION-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&SExpressionIterator::nextP))), NULL);
      defineFunctionObject("NATIVE-LINES", "(DEFUN (NATIVE-LINES NATIVE-LINE-ITERATOR) ((STREAM INPUT-STREAM)) :PUBLIC? TRUE)", ((cpp_function_code)(&nativeLines)), NULL);
      defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF NATIVE-LINE-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&NativeLineIterator::nextP))), NULL);
      defineFunctionObject("LINES", "(DEFUN (LINES LINE-ITERATOR) ((STREAM INPUT-STREAM)) :PUBLIC? TRUE)", ((cpp_function_code)(&lines)), NULL);
      defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF LINE-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&LineIterator::nextP))), NULL);
      defineFunctionObject("CHARACTERS", "(DEFUN (CHARACTERS CHARACTER-ITERATOR) ((STREAM INPUT-STREAM)) :PUBLIC? TRUE)", ((cpp_function_code)(&characters)), NULL);
      defineMethodObject("(DEFMETHOD (NEXT? BOOLEAN) ((SELF CHARACTER-ITERATOR)) :PUBLIC? TRUE)", wrapMethodCode(((cpp_method_code)(&CharacterIterator::nextP))), NULL);
      defineFunctionObject("LOOKUP-LOGGING-PARAMETER", "(DEFUN (LOOKUP-LOGGING-PARAMETER OBJECT) ((MODULE STRING) (PARAMETER KEYWORD) (DEFAULT OBJECT)) :DOCUMENTATION \"Lookup logging `parameter' for `module'.  Use `default' if no\nvalue is defined.\" :PUBLIC? TRUE)", ((cpp_function_code)(&lookupLoggingParameter)), NULL);
      defineFunctionObject("SET-LOGGING-PARAMETERS", "(DEFUN SET-LOGGING-PARAMETERS ((MODULE STRING) |&REST| (|PARAMS&VALUES| OBJECT)) :DOCUMENTATION \"Set logging parameters for `module'.  The supported parameters are:\n  :LOG-LEVELS - a cons list of legal levels in ascending log level order;\n                for example, (:NONE :LOW :MEDIUM :HIGH) or (0 1 2 3).\n  :LEVEL      - the current log level for `module'\n  :STREAM     - the stream or file to log to (defaults to STANDARD-OUTPUT)\n  :PREFIX     - the prefix to use to identify the module (defaults to `module')\n  :MAX-WIDTH  - logging output lines will be kept to approximately this width\n                (defaults to 10000, minimum width of about 30 is used to\n                print line header information).\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&setLoggingParameters)), ((cpp_function_code)(&setLoggingParametersEvaluatorWrapper)));
      defineFunctionObject("SET-LOG-LEVEL", "(DEFUN SET-LOG-LEVEL ((MODULE STRING) (LEVEL OBJECT)) :DOCUMENTATION \"Set the log-level for `module' to `level'.  This is a\nconvenience function for this common operation.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&setLogLevel)), ((cpp_function_code)(&setLogLevelEvaluatorWrapper)));
      defineFunctionObject("LOG-LEVEL<=", "(DEFUN (LOG-LEVEL<= BOOLEAN) ((LEVEL OBJECT) (MODULE STRING)) :DOCUMENTATION \"Return TRUE if `level' is lower than or equal to the current\nlog level of `module'.  Return FALSE if any of them are undefined.\" :PUBLIC? TRUE)", ((cpp_function_code)(&logLevelLE)), NULL);
      defineFunctionObject("BUMP-LOG-INDENT", "(DEFUN BUMP-LOG-INDENT () :DOCUMENTATION \"Increase the indentation level for subsequent log messages.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&bumpLogIndent)), NULL);
      defineFunctionObject("UNBUMP-LOG-INDENT", "(DEFUN UNBUMP-LOG-INDENT () :DOCUMENTATION \"Decrease the indentation level for subsequent log messages.\" :PUBLIC? TRUE :COMMAND? TRUE)", ((cpp_function_code)(&unbumpLogIndent)), NULL);
      defineFunctionObject("GET-LOG-STREAM", "(DEFUN (GET-LOG-STREAM OUTPUT-STREAM) ((MODULE STRING)) :DOCUMENTATION \"Return a valid log stream for `module'.\" :PUBLIC? TRUE)", ((cpp_function_code)(&getLogStream)), NULL);
      defineFunctionObject("LOG-MESSAGE", "(DEFUN LOG-MESSAGE ((MODULE STRING) (LOGLEVEL OBJECT) (MESSAGE CONS)) :DOCUMENTATION \"Log all elements of `message' to `module's log stream if\n`logLevel' is the same or lower than the `module's log level.  Interprets `EOL'\nor :EOL to print a line terminator.\" :PUBLIC? TRUE)", ((cpp_function_code)(&logMessage)), NULL);
      defineFunctionObject("LOGMSG", "(DEFUN LOGMSG ((MODULE STRING) (LOGLEVEL OBJECT) |&REST| (MESSAGE OBJECT)) :DOCUMENTATION \"Log all elements of `message' to `module's log stream if\n`logLevel' is the same or lower than the `module's log level.  Interprets `EOL'\nor :EOL to print a line terminator.\" :PUBLIC? TRUE)", ((cpp_function_code)(&logmsg)), NULL);
      defineFunctionObject("STARTUP-STREAMS", "(DEFUN STARTUP-STREAMS () :PUBLIC? TRUE)", ((cpp_function_code)(&startupStreams)), NULL);
      { MethodSlot* function = lookupFunction(SYM_STREAMS_STELLA_STARTUP_STREAMS);

        setDynamicSlotValue(function->dynamicSlots, SYM_STREAMS_STELLA_METHOD_STARTUP_CLASSNAME, wrapString("_StartupStreams"), NULL_STRING_WRAPPER);
      }
    }
    if (currentStartupTimePhaseP(8)) {
      finalizeSlots();
      cleanupUnfinalizedClasses();
    }
    if (currentStartupTimePhaseP(9)) {
      inModule(((StringWrapper*)(copyConsTree(wrapString("/STELLA")))));
      defineGlobalVariableObject("(DEFGLOBAL EOL SYMBOL (QUOTE EOL) :DOCUMENTATION \"Generates a newline character when passed to a stream.\" :PUBLIC? TRUE)", &EOL);
      defineGlobalVariableObject("(DEFGLOBAL EOL-STRING STRING \"\n\" :DOCUMENTATION \"A string constant containing the character sequence\nnecessary to generate a newline.\" :PUBLIC? TRUE)", &EOL_STRING);
      defineGlobalVariableObject("(DEFGLOBAL STELLA-CHARSET NATIVE-CHARSET-ENCODING (VERBATIM :JAVA \"java.nio.charset.Charset.forName(\\\"ISO-8859-1\\\")\" :COMMON-LISP \"(CL:or #+allegro (CL:ignore-errors (excl::find-external-format :iso-8859-1))\n                                 #+cmu :iso-8859-1\n                                 :DEFAULT)\" :OTHERWISE NULL) :DOCUMENTATION \"For STELLA we always assume an 8-bit transparent mapping from bytes to STRING characters\nsuch as ISO-8859-1 (ISO-LATIN-1), since that's what C++ natively supports.  For Java and some Lisps, we have\nto do some extra work to enforce this encoding when creating streams.  This is just a first iteration towards\nthis handling this, for example, in Lisp we'd also have to configure compile and load streams to properly encode\nstring constants that contain non-ASCII characters.\" :PUBLIC? TRUE)", &STELLA_CHARSET);
      defineGlobalVariableObject("(DEFGLOBAL STANDARD-INPUT INPUT-STREAM NULL :DOCUMENTATION \"Denotes the standard input stream for the host language.\" :PUBLIC? TRUE)", &STANDARD_INPUT);
      defineGlobalVariableObject("(DEFGLOBAL STANDARD-OUTPUT OUTPUT-STREAM (VERBATIM :OTHERWISE (MAKE-EARLY-OUTPUT-STREAM (VERBATIM :COMMON-LISP CL:*STANDARD-OUTPUT* :CPP \"&std::cout\" :JAVA \"#$(STELLAROOT).javalib.NativeOutputStream.create(java.lang.System.out)\"))) :DOCUMENTATION \"Denotes the standard output stream for the host language.\" :PUBLIC? TRUE)", &STANDARD_OUTPUT);
      defineGlobalVariableObject("(DEFGLOBAL STANDARD-WARNING OUTPUT-STREAM (VERBATIM :OTHERWISE (MAKE-EARLY-OUTPUT-STREAM (VERBATIM :COMMON-LISP CL:*ERROR-OUTPUT* :CPP \"&std::cerr\" :JAVA \"#$(STELLAROOT).javalib.NativeOutputStream.create(java.lang.System.err)\"))) :DOCUMENTATION \"Denotes the standard warning stream for the host language.\" :PUBLIC? TRUE)", &STANDARD_WARNING);
      defineGlobalVariableObject("(DEFGLOBAL STANDARD-ERROR OUTPUT-STREAM (VERBATIM :OTHERWISE (MAKE-EARLY-OUTPUT-STREAM (VERBATIM :COMMON-LISP CL:*ERROR-OUTPUT* :CPP \"&std::cerr\" :JAVA \"#$(STELLAROOT).javalib.NativeOutputStream.create(java.lang.System.err)\"))) :DOCUMENTATION \"Denotes the standard error stream for the host language.\" :PUBLIC? TRUE)", &STANDARD_ERROR);
      defineGlobalVariableObject("(DEFSPECIAL *IGNORETRANSLATIONERRORS?* BOOLEAN TRUE :DOCUMENTATION \"If `true' all passes of a translation will always be performed\nregardless of whether any errors were encountered.  Otherwise, translation\nends with the first pass that encountered an error.\" :PUBLIC? TRUE)", &oIGNORETRANSLATIONERRORSpo);
      defineGlobalVariableObject("(DEFGLOBAL SINGLE-QUOTE-STRING STRING-WRAPPER (WRAP-LITERAL \"'\") :DOCUMENTATION \"Holds a string containing the single quote character.\")", &SINGLE_QUOTE_STRING);
      defineGlobalVariableObject("(DEFGLOBAL SINGLE-BQUOTE-STRING STRING-WRAPPER (WRAP-LITERAL \"`\") :DOCUMENTATION \"Holds a string containing the single backquote character.\")", &SINGLE_BQUOTE_STRING);
      defineGlobalVariableObject("(DEFGLOBAL *OPEN-FILE-STREAMS* (LIST OF STREAM) (NEW (LIST OF STREAM)) :DOCUMENTATION \"List of file streams that are currently open.\")", &oOPEN_FILE_STREAMSo);
      defineGlobalVariableObject("(DEFGLOBAL *HTML-QUOTED-CHARACTERS* STRING \"><&\\\"\")", &oHTML_QUOTED_CHARACTERSo);
      defineGlobalVariableObject("(DEFGLOBAL *HTML-ESCAPE-TABLE* KEY-VALUE-LIST (NEW KEY-VALUE-LIST))", &oHTML_ESCAPE_TABLEo);
      oHTML_ESCAPE_TABLEo->insertAt(wrapString("lt"), wrapCharacter('<'));
      oHTML_ESCAPE_TABLEo->insertAt(wrapString("gt"), wrapCharacter('>'));
      oHTML_ESCAPE_TABLEo->insertAt(wrapString("amp"), wrapCharacter('&'));
      oHTML_ESCAPE_TABLEo->insertAt(wrapString("quot"), wrapCharacter('"'));
      oHTML_ESCAPE_TABLEo->insertAt(wrapString("apos"), wrapCharacter('\''));
      oHTML_ESCAPE_TABLEo->insertAt(wrapString("nbsp"), wrapCharacter(' '));
      oHTML_ESCAPE_TABLEo->insertAt(wrapString("NBSP"), wrapCharacter(' '));
      defineGlobalVariableObject("(DEFGLOBAL *LOGGING-REGISTRY* (KEY-VALUE-LIST OF STRING-WRAPPER (PROPERTY-LIST OF KEYWORD OBJECT)) (NEW KEY-VALUE-LIST))", &oLOGGING_REGISTRYo);
      defineGlobalVariableObject("(DEFGLOBAL *LOGGING-LOCAL-TIME-ZONE* FLOAT (GET-LOCAL-TIME-ZONE))", &oLOGGING_LOCAL_TIME_ZONEo);
      defineGlobalVariableObject("(DEFGLOBAL *LOG-INDENT-LEVEL* INTEGER 0 :DOCUMENTATION \"The number of spaces to print before the content of a log message.\" :PUBLIC? TRUE)", &oLOG_INDENT_LEVELo);
    }
  }
}

Symbol* SYM_STREAMS_STELLA_EOL = NULL;

Symbol* SYM_STREAMS_STELLA_PRINT_STREAM = NULL;

Symbol* SYM_STREAMS_STELLA_STANDARD_OUTPUT = NULL;

Symbol* SYM_STREAMS_STELLA_FOREACH = NULL;

Symbol* SYM_STREAMS_STELLA_I = NULL;

Symbol* SYM_STREAMS_STELLA_IN = NULL;

Symbol* SYM_STREAMS_STELLA_INTERVAL = NULL;

Symbol* SYM_STREAMS_STELLA_DO = NULL;

Symbol* SYM_STREAMS_STELLA_IGNORE = NULL;

Keyword* KWD_STREAMS_COMMON_LISP = NULL;

Keyword* KWD_STREAMS_WARN = NULL;

Symbol* SYM_STREAMS_STELLA_STANDARD_WARNING = NULL;

Symbol* SYM_STREAMS_STELLA_NULL = NULL;

Symbol* SYM_STREAMS_STELLA_STELLA_EXCEPTION = NULL;

Surrogate* SGT_STREAMS_STELLA_STRING_WRAPPER = NULL;

Symbol* SYM_STREAMS_STELLA_SIGNAL_EXCEPTION = NULL;

Symbol* SYM_STREAMS_STELLA_NEW = NULL;

Keyword* KWD_STREAMS_MESSAGE = NULL;

Symbol* SYM_STREAMS_STELLA_LET = NULL;

Symbol* SYM_STREAMS_STELLA_OUTPUT_STRING_STREAM = NULL;

Symbol* SYM_STREAMS_STELLA_THE_STRING = NULL;

Symbol* SYM_STREAMS_STELLA_SIGNAL = NULL;

Keyword* KWD_STREAMS_JAVA = NULL;

Symbol* SYM_STREAMS_STELLA_ERROR_MESSAGE_ = NULL;

Symbol* SYM_STREAMS_STELLA_VERBATIM = NULL;

Keyword* KWD_STREAMS_CONTINUABLE_ERROR = NULL;

Symbol* SYM_STREAMS_STELLA_READ_EXCEPTION = NULL;

Symbol* SYM_STREAMS_STELLA_DE_UGLIFY_PARSE_TREE = NULL;

Symbol* SYM_STREAMS_STELLA_SPECIAL = NULL;

Symbol* SYM_STREAMS_STELLA_oPRINTREADABLYpo = NULL;

Symbol* SYM_STREAMS_STELLA_TRUE = NULL;

Symbol* SYM_STREAMS_STELLA_SIGNAL_TRANSLATION_ERROR = NULL;

Symbol* SYM_STREAMS_STELLA_UNLESS = NULL;

Symbol* SYM_STREAMS_STELLA_SUPPRESS_WARNINGSp = NULL;

Symbol* SYM_STREAMS_STELLA_PRINT_ERROR_CONTEXT = NULL;

Symbol* SYM_STREAMS_STELLA_STANDARD_ERROR = NULL;

Symbol* SYM_STREAMS_STELLA_SIGNAL_TRANSLATION_NOTE = NULL;

Symbol* SYM_STREAMS_STELLA_SIGNAL_TRANSLATION_WARNING = NULL;

Symbol* SYM_STREAMS_STELLA_WHEN = NULL;

Symbol* SYM_STREAMS_STELLA_NOT = NULL;

Keyword* KWD_STREAMS_ERROR = NULL;

Symbol* SYM_STREAMS_STELLA_oEVALUATIONTREEo = NULL;

Symbol* SYM_STREAMS_STELLA_DEFINEDp = NULL;

Symbol* SYM_STREAMS_STELLA_oEVALUATIONPARENTTREEo = NULL;

Symbol* SYM_STREAMS_STELLA_EVALUATION_EXCEPTION = NULL;

Surrogate* SGT_STREAMS_STELLA_LITERAL_WRAPPER = NULL;

Symbol* SYM_STREAMS_STELLA_STRINGIFY = NULL;

Symbol* SYM_STREAMS_STELLA_VRLET = NULL;

Symbol* SYM_STREAMS_STELLA_STRING = NULL;

Symbol* SYM_STREAMS_STELLA_SETQ = NULL;

Symbol* SYM_STREAMS_STELLA_CONCATENATE = NULL;

Keyword* KWD_STREAMS_CLOSED = NULL;

Keyword* KWD_STREAMS_IF_EXISTS = NULL;

Keyword* KWD_STREAMS_IF_EXISTS_ACTION = NULL;

Keyword* KWD_STREAMS_IF_NOT_EXISTS = NULL;

Keyword* KWD_STREAMS_IF_NOT_EXISTS_ACTION = NULL;

Keyword* KWD_STREAMS_SUPERSEDE = NULL;

Keyword* KWD_STREAMS_CREATE = NULL;

Keyword* KWD_STREAMS_CREATE_PATH = NULL;

Keyword* KWD_STREAMS_ABORT = NULL;

Keyword* KWD_STREAMS_PROBE = NULL;

Keyword* KWD_STREAMS_APPEND = NULL;

Keyword* KWD_STREAMS_OPEN = NULL;

Surrogate* SGT_STREAMS_STELLA_INPUT_FILE_STREAM = NULL;

Surrogate* SGT_STREAMS_STELLA_OUTPUT_FILE_STREAM = NULL;

Surrogate* SGT_STREAMS_STELLA_INPUT_STRING_STREAM = NULL;

Surrogate* SGT_STREAMS_STELLA_OUTPUT_STRING_STREAM = NULL;

Surrogate* SGT_STREAMS_STELLA_INPUT_STREAM = NULL;

Surrogate* SGT_STREAMS_STELLA_OUTPUT_STREAM = NULL;

Keyword* KWD_STREAMS_BLOCK = NULL;

Symbol* SYM_STREAMS_STELLA_FILE_INPUT_STREAM = NULL;

Symbol* SYM_STREAMS_STELLA_UNWIND_PROTECT = NULL;

Symbol* SYM_STREAMS_STELLA_PROGN = NULL;

Symbol* SYM_STREAMS_STELLA_OPEN_INPUT_FILE = NULL;

Symbol* SYM_STREAMS_STELLA_FREE = NULL;

Symbol* SYM_STREAMS_STELLA_FILE_OUTPUT_STREAM = NULL;

Symbol* SYM_STREAMS_STELLA_OPEN_OUTPUT_FILE = NULL;

Symbol* SYM_STREAMS_STELLA_INPUT_STREAM = NULL;

Symbol* SYM_STREAMS_STELLA_OUTPUT_STREAM = NULL;

Symbol* SYM_STREAMS_STELLA_MV_SETQ = NULL;

Symbol* SYM_STREAMS_STELLA_OPEN_NETWORK_STREAM = NULL;

Surrogate* SGT_STREAMS_STELLA_OBJECT = NULL;

Symbol* SYM_STREAMS_STELLA_SUBSEQUENCE = NULL;

Symbol* SYM_STREAMS_STELLA_POSITION = NULL;

Keyword* KWD_STREAMS_LETTER = NULL;

Keyword* KWD_STREAMS_DIGIT = NULL;

Symbol* SYM_STREAMS_STELLA_THE_STREAM = NULL;

Surrogate* SGT_STREAMS_STELLA_S_EXPRESSION_ITERATOR = NULL;

Symbol* SYM_STREAMS_STELLA_VALUE = NULL;

Surrogate* SGT_STREAMS_STELLA_LINE_ITERATOR = NULL;

Surrogate* SGT_STREAMS_STELLA_NATIVE_LINE_ITERATOR = NULL;

Surrogate* SGT_STREAMS_STELLA_CHARACTER_ITERATOR = NULL;

Keyword* KWD_STREAMS_LEVEL = NULL;

Keyword* KWD_STREAMS_LOG_LEVELS = NULL;

Keyword* KWD_STREAMS_STREAM = NULL;

Keyword* KWD_STREAMS_PREFIX = NULL;

Keyword* KWD_STREAMS_MAX_WIDTH = NULL;

Surrogate* SGT_STREAMS_STELLA_GENERALIZED_SYMBOL = NULL;

Surrogate* SGT_STREAMS_STELLA_FILE_OUTPUT_STREAM = NULL;

Symbol* SYM_STREAMS_STELLA_STARTUP_STREAMS = NULL;

Symbol* SYM_STREAMS_STELLA_METHOD_STARTUP_CLASSNAME = NULL;

} // end of namespace stella
