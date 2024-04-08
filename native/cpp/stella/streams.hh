//  -*- Mode: C++ -*-

// streams.hh

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


namespace stella {

// Class definitions:
class StreamIterator : public AbstractIterator {
// Iterator that yields tokens from an input stream.
public:
  InputStream* theStream;
};

class SExpressionIterator : public StreamIterator {
// Iterator that yields s-expressions from an input stream.
public:
  // The current value of this iterator
  Object* value;
public:
  virtual void free();
  virtual boolean nextP();
  virtual Surrogate* primaryType();
};

class LineIterator : public StreamIterator {
// Iterator that yields lines with any line terminator sequence from an input stream.
public:
  // The current value of this iterator
  const char* value;
public:
  virtual void free();
  virtual boolean nextP();
  virtual Surrogate* primaryType();
};

class NativeLineIterator : public StreamIterator {
// Iterator that yields lines from an input stream.
public:
  // The current value of this iterator
  const char* value;
public:
  virtual void free();
  virtual boolean nextP();
  virtual Surrogate* primaryType();
};

class CharacterIterator : public StreamIterator {
// Iterator that yields characters from an input stream.
public:
  // The current value of this iterator
  char value;
public:
  virtual void free();
  virtual boolean nextP();
  virtual Surrogate* primaryType();
};


// Global declarations:
extern Symbol* EOL;
extern const char* EOL_STRING;
extern void* STELLA_CHARSET;
extern InputStream* STANDARD_INPUT;
extern OutputStream* STANDARD_OUTPUT;
extern OutputStream* STANDARD_WARNING;
extern OutputStream* STANDARD_ERROR;
extern DECLARE_STELLA_SPECIAL(oIGNORETRANSLATIONERRORSpo, boolean );
extern StringWrapper* SINGLE_QUOTE_STRING;
extern StringWrapper* SINGLE_BQUOTE_STRING;
extern List* oOPEN_FILE_STREAMSo;
extern const char* oHTML_QUOTED_CHARACTERSo;
extern KeyValueList* oHTML_ESCAPE_TABLEo;
extern KeyValueList* oLOGGING_REGISTRYo;
extern double oLOGGING_LOCAL_TIME_ZONEo;
extern int oLOG_INDENT_LEVELo;

// Function signatures:
OutputStream* makeEarlyOutputStream(std::ostream* nativestream);
Cons* formatMessageArguments(Cons* messageargumentstree, boolean trailingeolP);
Object* print(Cons* body);
Object* printSpaces(Cons* body);
Object* inform(Cons* body);
Object* warn(Cons* body);
Object* signal(Symbol* type, Cons* body);
Object* error(Cons* body);
Object* continuableError(Cons* body);
Object* signalReadError(Cons* body);
void ensureFileExists(const char* filename, const char* context);
void ensureFileDoesNotExist(const char* filename, const char* context);
Cons* formatWalkMessageArguments(Cons* messageargumentstree);
Object* walkError(Cons* body);
Object* walkInform(Cons* body);
Object* walkWarn(Cons* body);
Object* safety(IntegerWrapper* level, Object* test, Cons* body);
Object* evaluationError(Cons* body);
Cons* formatStringMessageArguments(Cons* messagearguments, boolean trailingeolP);
Object* messageToString(Cons* body);
boolean terminateOutputStreamP(OutputStream* self);
boolean terminateInputStreamP(InputStream* self);
OutputFileStream* openOutputFile(const char* filename, int options, ...);
void initializeFileOutputStream(OutputFileStream* self);
boolean terminateFileOutputStreamP(OutputFileStream* self);
InputFileStream* openInputFile(const char* filename, int options, ...);
void initializeFileInputStream(InputFileStream* self);
boolean terminateFileInputStreamP(InputFileStream* self);
void initializeStringOutputStream(OutputStringStream* self);
boolean terminateStringOutputStreamP(OutputStringStream* self);
void initializeStringInputStream(InputStringStream* self);
boolean terminateStringInputStreamP(InputStringStream* self);
void closeStream(Stream* self);
void clearInput(InputStream* self);
void flushOutput(OutputStream* self);
void closeAllFiles();
InputStream* openNetworkStream(const char* host, int port, OutputStream*& _Return1);
Object* withInputFile(Cons* binding, Cons* body);
Object* withOutputFile(Cons* binding, Cons* body);
Object* withNetworkStream(Cons* binding, Cons* body);
long long int nativeFileInputStreamPosition(std::istream* nstream);
long long int nativeFileInputStreamPositionSetter(std::istream* nstream, long long int newpos);
long long int nativeFileOutputStreamPosition(std::ostream* nstream);
long long int nativeFileOutputStreamPositionSetter(std::ostream* nstream, long long int newpos);
Cons* expandMarkupTagFunction(Cons* tagAndStream, Cons* body, boolean xmlP);
Object* withHtmlTag(Cons* tagAndStream, Cons* body);
Object* withXmlTag(Cons* tagAndStream, Cons* body);
boolean htmlCharacterNeedsQuotingP(char ch);
void writeHtmlCharacterQuotingSpecialCharacters(std::ostream* stream, char ch);
void writeHtmlQuotingSpecialCharacters(std::ostream* stream, const char* input);
void writeHtmlEscapingUrlSpecialCharacters(std::ostream* stream, const char* input);
int hexCharacterValue(char c);
const char* unescapeUrlString(const char* input);
const char* unescapeHtmlString(const char* input);
Object* accessStreamIteratorSlotValue(StreamIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
SExpressionIterator* newSExpressionIterator();
Object* accessSExpressionIteratorSlotValue(SExpressionIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
LineIterator* newLineIterator();
Object* accessLineIteratorSlotValue(LineIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
NativeLineIterator* newNativeLineIterator();
Object* accessNativeLineIteratorSlotValue(NativeLineIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
CharacterIterator* newCharacterIterator();
Object* accessCharacterIteratorSlotValue(CharacterIterator* self, Symbol* slotname, Object* value, boolean setvalueP);
boolean terminateStreamIteratorP(StreamIterator* self);
SExpressionIterator* sExpressions(InputStream* stream);
NativeLineIterator* nativeLines(InputStream* stream);
LineIterator* lines(InputStream* stream);
CharacterIterator* characters(InputStream* stream);
Object* lookupLoggingParameter(const char* module, Keyword* parameter, Object* defaulT);
void setLoggingParameters(const char* module, Cons* paramsAvalues);
void setLoggingParametersEvaluatorWrapper(Cons* arguments);
void setLogLevel(const char* module, Object* level);
void setLogLevelEvaluatorWrapper(Cons* arguments);
boolean logLevelLE(Object* level, const char* module);
void bumpLogIndent();
void unbumpLogIndent();
OutputStream* getLogStream(const char* module);
void logMessage(const char* module, Object* loglevel, Cons* message);
void logmsg(const char* module, Object* loglevel, int message, ...);
void helpStartupStreams1();
void helpStartupStreams2();
void helpStartupStreams3();
void helpStartupStreams4();
void startupStreams();

// Auxiliary global declarations:
extern Symbol* SYM_STREAMS_STELLA_EOL;
extern Symbol* SYM_STREAMS_STELLA_PRINT_STREAM;
extern Symbol* SYM_STREAMS_STELLA_STANDARD_OUTPUT;
extern Symbol* SYM_STREAMS_STELLA_FOREACH;
extern Symbol* SYM_STREAMS_STELLA_I;
extern Symbol* SYM_STREAMS_STELLA_IN;
extern Symbol* SYM_STREAMS_STELLA_INTERVAL;
extern Symbol* SYM_STREAMS_STELLA_DO;
extern Symbol* SYM_STREAMS_STELLA_IGNORE;
extern Keyword* KWD_STREAMS_COMMON_LISP;
extern Keyword* KWD_STREAMS_WARN;
extern Symbol* SYM_STREAMS_STELLA_STANDARD_WARNING;
extern Symbol* SYM_STREAMS_STELLA_NULL;
extern Symbol* SYM_STREAMS_STELLA_STELLA_EXCEPTION;
extern Surrogate* SGT_STREAMS_STELLA_STRING_WRAPPER;
extern Symbol* SYM_STREAMS_STELLA_SIGNAL_EXCEPTION;
extern Symbol* SYM_STREAMS_STELLA_NEW;
extern Keyword* KWD_STREAMS_MESSAGE;
extern Symbol* SYM_STREAMS_STELLA_LET;
extern Symbol* SYM_STREAMS_STELLA_OUTPUT_STRING_STREAM;
extern Symbol* SYM_STREAMS_STELLA_THE_STRING;
extern Symbol* SYM_STREAMS_STELLA_SIGNAL;
extern Keyword* KWD_STREAMS_JAVA;
extern Symbol* SYM_STREAMS_STELLA_ERROR_MESSAGE_;
extern Symbol* SYM_STREAMS_STELLA_VERBATIM;
extern Keyword* KWD_STREAMS_CONTINUABLE_ERROR;
extern Symbol* SYM_STREAMS_STELLA_READ_EXCEPTION;
extern Symbol* SYM_STREAMS_STELLA_DE_UGLIFY_PARSE_TREE;
extern Symbol* SYM_STREAMS_STELLA_SPECIAL;
extern Symbol* SYM_STREAMS_STELLA_oPRINTREADABLYpo;
extern Symbol* SYM_STREAMS_STELLA_TRUE;
extern Symbol* SYM_STREAMS_STELLA_SIGNAL_TRANSLATION_ERROR;
extern Symbol* SYM_STREAMS_STELLA_UNLESS;
extern Symbol* SYM_STREAMS_STELLA_SUPPRESS_WARNINGSp;
extern Symbol* SYM_STREAMS_STELLA_PRINT_ERROR_CONTEXT;
extern Symbol* SYM_STREAMS_STELLA_STANDARD_ERROR;
extern Symbol* SYM_STREAMS_STELLA_SIGNAL_TRANSLATION_NOTE;
extern Symbol* SYM_STREAMS_STELLA_SIGNAL_TRANSLATION_WARNING;
extern Symbol* SYM_STREAMS_STELLA_WHEN;
extern Symbol* SYM_STREAMS_STELLA_NOT;
extern Keyword* KWD_STREAMS_ERROR;
extern Symbol* SYM_STREAMS_STELLA_oEVALUATIONTREEo;
extern Symbol* SYM_STREAMS_STELLA_DEFINEDp;
extern Symbol* SYM_STREAMS_STELLA_oEVALUATIONPARENTTREEo;
extern Symbol* SYM_STREAMS_STELLA_EVALUATION_EXCEPTION;
extern Surrogate* SGT_STREAMS_STELLA_LITERAL_WRAPPER;
extern Symbol* SYM_STREAMS_STELLA_STRINGIFY;
extern Symbol* SYM_STREAMS_STELLA_VRLET;
extern Symbol* SYM_STREAMS_STELLA_STRING;
extern Symbol* SYM_STREAMS_STELLA_SETQ;
extern Symbol* SYM_STREAMS_STELLA_CONCATENATE;
extern Keyword* KWD_STREAMS_CLOSED;
extern Keyword* KWD_STREAMS_IF_EXISTS;
extern Keyword* KWD_STREAMS_IF_EXISTS_ACTION;
extern Keyword* KWD_STREAMS_IF_NOT_EXISTS;
extern Keyword* KWD_STREAMS_IF_NOT_EXISTS_ACTION;
extern Keyword* KWD_STREAMS_SUPERSEDE;
extern Keyword* KWD_STREAMS_CREATE;
extern Keyword* KWD_STREAMS_CREATE_PATH;
extern Keyword* KWD_STREAMS_ABORT;
extern Keyword* KWD_STREAMS_PROBE;
extern Keyword* KWD_STREAMS_APPEND;
extern Keyword* KWD_STREAMS_OPEN;
extern Surrogate* SGT_STREAMS_STELLA_INPUT_FILE_STREAM;
extern Surrogate* SGT_STREAMS_STELLA_OUTPUT_FILE_STREAM;
extern Surrogate* SGT_STREAMS_STELLA_INPUT_STRING_STREAM;
extern Surrogate* SGT_STREAMS_STELLA_OUTPUT_STRING_STREAM;
extern Surrogate* SGT_STREAMS_STELLA_INPUT_STREAM;
extern Surrogate* SGT_STREAMS_STELLA_OUTPUT_STREAM;
extern Keyword* KWD_STREAMS_BLOCK;
extern Symbol* SYM_STREAMS_STELLA_FILE_INPUT_STREAM;
extern Symbol* SYM_STREAMS_STELLA_UNWIND_PROTECT;
extern Symbol* SYM_STREAMS_STELLA_PROGN;
extern Symbol* SYM_STREAMS_STELLA_OPEN_INPUT_FILE;
extern Symbol* SYM_STREAMS_STELLA_FREE;
extern Symbol* SYM_STREAMS_STELLA_FILE_OUTPUT_STREAM;
extern Symbol* SYM_STREAMS_STELLA_OPEN_OUTPUT_FILE;
extern Symbol* SYM_STREAMS_STELLA_INPUT_STREAM;
extern Symbol* SYM_STREAMS_STELLA_OUTPUT_STREAM;
extern Symbol* SYM_STREAMS_STELLA_MV_SETQ;
extern Symbol* SYM_STREAMS_STELLA_OPEN_NETWORK_STREAM;
extern Surrogate* SGT_STREAMS_STELLA_OBJECT;
extern Symbol* SYM_STREAMS_STELLA_SUBSEQUENCE;
extern Symbol* SYM_STREAMS_STELLA_POSITION;
extern Keyword* KWD_STREAMS_LETTER;
extern Keyword* KWD_STREAMS_DIGIT;
extern Symbol* SYM_STREAMS_STELLA_THE_STREAM;
extern Surrogate* SGT_STREAMS_STELLA_S_EXPRESSION_ITERATOR;
extern Symbol* SYM_STREAMS_STELLA_VALUE;
extern Surrogate* SGT_STREAMS_STELLA_LINE_ITERATOR;
extern Surrogate* SGT_STREAMS_STELLA_NATIVE_LINE_ITERATOR;
extern Surrogate* SGT_STREAMS_STELLA_CHARACTER_ITERATOR;
extern Keyword* KWD_STREAMS_LEVEL;
extern Keyword* KWD_STREAMS_LOG_LEVELS;
extern Keyword* KWD_STREAMS_STREAM;
extern Keyword* KWD_STREAMS_PREFIX;
extern Keyword* KWD_STREAMS_MAX_WIDTH;
extern Surrogate* SGT_STREAMS_STELLA_GENERALIZED_SYMBOL;
extern Surrogate* SGT_STREAMS_STELLA_FILE_OUTPUT_STREAM;
extern Symbol* SYM_STREAMS_STELLA_STARTUP_STREAMS;
extern Symbol* SYM_STREAMS_STELLA_METHOD_STARTUP_CLASSNAME;


} // end of namespace stella
