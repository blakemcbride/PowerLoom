#!/usr/bin/env python-pli

############################# BEGIN LICENSE BLOCK ############################
#                                                                            #
# Version: MPL 1.1/GPL 2.0/LGPL 2.1                                          #
#                                                                            #
# The contents of this file are subject to the Mozilla Public License        #
# Version 1.1 (the "License"); you may not use this file except in           #
# compliance with the License. You may obtain a copy of the License at       #
# http://www.mozilla.org/MPL/                                                #
#                                                                            #
# Software distributed under the License is distributed on an "AS IS" basis, #
# WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License   #
# for the specific language governing rights and limitations under the       #
# License.                                                                   #
#                                                                            #
# The Original Code is the PowerLoom KR&R System.                            #
#                                                                            #
# The Initial Developer of the Original Code is                              #
# UNIVERSITY OF SOUTHERN CALIFORNIA, INFORMATION SCIENCES INSTITUTE          #
# 4676 Admiralty Way, Marina Del Rey, California 90292, U.S.A.               #
#                                                                            #
# Portions created by the Initial Developer are Copyright (C) 2015-2021      #
# the Initial Developer. All Rights Reserved.                                #
#                                                                            #
# Contributor(s):                                                            #
#                                                                            #
# Alternatively, the contents of this file may be used under the terms of    #
# either the GNU General Public License Version 2 or later (the "GPL"), or   #
# the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),   #
# in which case the provisions of the GPL or the LGPL are applicable instead #
# of those above. If you wish to allow use of your version of this file only #
# under the terms of either the GPL or the LGPL, and not to allow others to  #
# use your version of this file under the terms of the MPL, indicate your    #
# decision by deleting the provisions above and replace them with the notice #
# and other provisions required by the GPL or the LGPL. If you do not delete #
# the provisions above, a recipient may use your version of this file under  #
# the terms of any one of the MPL, the GPL or the LGPL.                      #
#                                                                            #
############################# END LICENSE BLOCK ##############################

# Assorted utilities collected from various places
# TO DO: replace them at those various places.

from __future__ import print_function, division, absolute_import

import sys
PY2 = sys.version_info[0] == 2
PY3 = sys.version_info[0] >= 3
if PY3:
    unicode = str
    basestring = (bytes, unicode)
    long = int

import os
import re
import zipfile
import types


def listify(x):
    """Coerce 'x' into a list.  There is no Python builtin that does this."""
    return [] if x is None else list(x) if hasattr(x, "__iter__") and not isinstance(x, basestring) else [x]


### Unicode:

def coerceToBytes(text, encoding='UTF-8'):
    if isinstance(text, bytes):
        return text
    elif isinstance(text, unicode):
        return text.encode(encoding)
    else:
        return str(text)

def coerceToUnicode(text, encoding='UTF-8'):
    if isinstance(text, unicode):
        return text
    elif isinstance(text, bytes):
        return text.decode(encoding)
    else:
        return unicode(text)

def unicodeToByteOffset(offset, text):
    # Encode `offset' into `text' as a byte offset into a UTF8 encoding of `text'.
    # If `text' is not a Unicode string, simply return `offset'.
    # This is a bit wasteful but will do for now.
    if isinstance(text, unicode):
        return len(text[0:offset].encode('utf8'))
    else:
        return offset

def byteToUnicodeOffset(offset, text):
    # Encode byte `offset' into `text' as a Unicode offset into a UTF8 decoding of `text'.
    # If `text' is not a byte string, simply return `offset'.
    # This is a bit wasteful but will do for now.
    if isinstance(text, str):
        return len(text[0:offset].decode('utf8'))
    else:
        return offset

def robustCoerceToUnicode(text):
    """Coerce byte string `text' to UTF8-encoded Unicode, but do not break if there is a decoding error.
       In that case, simply report the error and try to fix the problem by moving inwards from both directions."""
    slack = 0
    end = len(text)
    while slack <= int(end / 2):
        try:
            # if necessary, move inwards from end:
            return coerceToUnicode(text[0:end-slack])
        except Exception as e:
            if slack == 0:
                print('ERROR: robustCoerceToUnicode ' + str(e) + ', attempting to fix the problem')
                #import pdb
                #pdb.set_trace()
        try:
            # if necessary, move inwards from start:
            return coerceToUnicode(text[0+slack:end])
        except:
            pass
        try:
            # if necessary, move inwards from start and end:
            return coerceToUnicode(text[0+slack:end-slack])
        except:
            pass
        slack += 1
    # we failed:
    return "UTF8 DECODING ERROR"

def robustByteToUnicodeOffset(offset, docText):
    """Coerce byte `offset' into `docText' into a UTF8-encoded Unicode offset, but do not break if there is a decoding error.
       In that case, simply report the error and try to fix the problem by moving inwards or outwards from the given `offset'."""
    slack = 0
    maxSlack = 5
    while slack <= maxSlack:
        try:
            # if necessary, move outwards from end:
            return byteToUnicodeOffset(offset+slack, docText)
        except Exception as e:
            if slack == 0:
                print('ERROR: robustByteToUnicodeOffset(' + str(offset) + ') ' + str(e) + ', attempting to fix the problem')
                #import pdb
                #pdb.set_trace()
        try:
            # if necessary, move inwards from end:
            return byteToUnicodeOffset(offset-slack, docText)
        except:
            pass
        slack += 1
    # we failed:
    return offset


### Files:

def findFileInPath(file, path, error=False):
    for path in listify(path):
        # guard against None elements:
        path = path or ''
        for dir in path.split(os.pathsep):
            dirFile = os.path.join(dir, file)
            if os.path.exists(dirFile):
                return dirFile
    if error:
        raise Exception('Cannot find file in path: ' + file + ', ' + path)
    else:
        return None

def addFlexWrite(file, encoding='UTF-8'):
    """For PY3 only, add a flexible write method to the file-like object 'file'
    that can handle both bytes and strings relative to 'encoding'.  Only add a
    write method if 'file' currently has one, and only do this for the specific
    'file' instance.  Return the (modified) 'file' object.
    """
    if PY3 and hasattr(file, 'write'):
        canWriteBytes = True
        try:
            file.write(b'')
        except:
            canWriteBytes = False
        canWriteText = True
        try:
            file.write('')
        except:
            canWriteText = False
        realWrite = file.write
        def flexWrite(data):
            if isinstance(data, str):
                if not canWriteText:
                    data = data.encode(encoding)
            elif isinstance(data, bytes):
                if not canWriteBytes:
                    data = data.decode(encoding)
            return realWrite(data)
        file.write = flexWrite
    return file
    
def smartOpen(file, mode='r', encoding='UTF-8'):
    """Version of `open' that is smart about gzip compression and already open file-like objects.
    IMPORTANT: This does not do anything special about character encodings, hence those have to
    be handled by the caller after reading arrays of bytes.  For PY3 this adds a flexible write
    method to output streams that can handle both bytes and strings based on 'encoding'.
    """
    if isinstance(file, basestring) and file.endswith('.gz'):
        import gzip
        # for PY2 force binary/bytes mode, but for PY3 obey the given 'mode':
        if mode.find('b') < 0 and PY2:
            mode += 'b'
        stream = gzip.open(file, mode)
    elif mode.find('r') >= 0 and hasattr(file, 'read'):
        stream = file
    elif (mode.find('w') >= 0 or mode.find('a') >= 0) and hasattr(file, 'write'):
        stream = file
    else:
        stream = open(file, mode)
    return addFlexWrite(stream, encoding=encoding)


### Output Files:

def getOutputFile(file, outFile=None, ext='.out', create=True):
    """Generate an output file based on input `file'.  If `outFile' is None, create it in `file's
    directory appending extension `ext' to it.  If `outFile' is a directory, create the output file
    there and create the directory if necessary if `create' is True.  Otherwise, use `outFile' as
    the name of the output file.
    """
    if outFile is None:
        outFile = os.path.dirname(file)
        if outFile == '':
            outFile = os.curdir
    if os.path.isdir(outFile) or os.path.basename(outFile) == '':
        # outFile is an existing directory or a possibly new directory path:
        if not os.path.exists(outFile) and create:
            os.makedirs(outFile, 0o755)
        outFile = os.path.join(outFile, os.path.basename(file) + ext)
    return outFile

def outputFileIsNewer(sourceFile, outFile=None):
    """Return True if `outFile' is not None, exists and is newer than `sourceFile'."""
    return outFile is not None and os.path.exists(outFile) and (os.path.getmtime(sourceFile) < os.path.getmtime(outFile))


### XSV Files:

def splitXsvLine(line, sep='\t'):
    tup = line.split(sep)
    # split off any trailing newline on last field - unfortunately, this copies the string:
    tup[-1] = tup[-1].rstrip('\r\n')
    return tup

class XsvFileLines(object):
    """
    Class that supports iteration over the lines of a tab/comma/char-separated file (or file-like object).
    Each returned tuple is a list of byte strings (as returned by read()), character set decoding
    needs to be handled by the caller if necessary.
    OBSOLETE: use csv.csvreader instead
    """
    # Maybe this should go into a utils package or something.
    def __init__(self, file, sep='\t'):
        self.fileIter = file
        if not hasattr(file, "__iter__") or isinstance(file, basestring):
            self.fileIter = open(file, 'r')
        self.separator = sep

    def __iter__(self):
        return self

    def __next__(self):
        return splitXsvLine(next(self.fileIter), self.separator)

    if PY2:
        next = __next__

    def close(self):
        self.fileIter.close()
        
    def __enter__(self):
        return self

    def __exit__(self, *_exc):
        self.close()

def readXsvFile(file, sep='\t'):
    # OBSOLETE: use csv.csvreader instead
    with XsvFileLines(file, sep) as xsv:
        return [tup for tup in xsv]

def writeXsvFile(tuples, file, sep='\t'):
    # OBSOLETE: use csv.csvwriter instead
    sep = coerceToBytes(sep, 'UTF-8')
    with open(file, 'wb') as out:
        for tup in tuples:
            out.write(sep.join([coerceToBytes(x, 'UTF-8') for x in tup]))
            out.write(b'\n')


### ZIP files:

class ZipFileMembers(object):
    """
    Class that supports iteration over the members of a zip archive.
    Members can be selected via a regular expression, the default selects all.
    Name and info of the current member can be accessed via the fileName and fileInfo fields.
    """
    # This should go into a ziputils package.
    def __init__(self, file, selector='^.*$'):
        self.zipFile = file
        self.selector = re.compile(selector)
        self.archive = zipfile.ZipFile(self.zipFile, 'r')
        # ZipFile doesn't support iteration member-by-member, so we have to get the full list:
        self.infoList = self.archive.infolist()
        self.infoCursor = 0
        self.fileInfo = None
        self.fileObject = None
        self.fileName = None
        self.value = None

    def __len__(self):
        return len(self.infoList)

    def __iter__(self):
        return self

    def __next__(self):
        nInfos = len(self.infoList)
        while self.infoCursor < nInfos:
            self.fileInfo = self.infoList[self.infoCursor]
            self.fileName = self.fileInfo.filename
            self.infoCursor += 1
            m = self.selector.match(self.fileName)
            if m and m.start() == 0 and m.end() == len(self.fileName):
                if self.fileObject:
                    # close previous object before we open the new one:
                    self.fileObject.close()
                self.fileObject = self.archive.open(self.fileInfo, 'r')
                return self.fileObject
        raise StopIteration()

    if PY2:
        next = __next__

    def close(self):
        if self.fileObject:
            self.fileObject.close()
        self.archive.close()
        
    def __enter__(self):
        return self

    def __exit__(self, *_exc):
        self.close()

class ZipFileLines(ZipFileMembers):
    """
    Class that supports iteration over the lines of the members of a zip archive.
    Each line retains the terminating newline, just like iteration over file objects.
    Members can be selected via a regular expression, the default selects all.
    Name and info of the current member can be accessed via the fileName and fileInfo fields.
    Each returned line is a string of bytes (as returned by read()), character set decoding
    needs to be handled by the caller if necessary.
    """
    # This should go into a ziputils package.
    def __init__(self, file, selector='^.*$'):
        super(ZipFileLines, self).__init__(file, selector)
        self.fileIter = None

    def __next__(self):
        while True:
            try:
                if self.fileIter is None:
                    raise StopIteration()
                return next(self.fileIter)
            except StopIteration:
                super(ZipFileLines, self).__next__()
                self.fileIter = iter(self.fileObject)

    if PY2:
        next = __next__


### Common text normalizations:

whiteSpaceRegex = re.compile('\\s+')
newlineRegex = re.compile('[\n\r]')
formattingRegex = re.compile('[\b\f\n\r\t\v]')
punctuationRegex = re.compile('[^ \\t\n\\r\\f\\va-zA-Z0-9]')
prefixSuffixRegex = re.compile('^the |^a |^mr |^mrs |^dr |^prof ')

def normalizeWhiteSpace(text):
    return re.sub(whiteSpaceRegex, ' ', text)

def normalizeNewlines(text):
    return re.sub(newlineRegex, ' ', text)

def normalizeFormatting(text):
    return re.sub(formattingRegex, ' ', text)

def normalizeNameCase(name):
    return name.lower()

def normalizeNameWhiteSpace(name):
    name = normalizeNameCase(name)
    return normalizeWhiteSpace(name)

def normalizeNamePunctuation(name):
    name = re.sub(punctuationRegex, '', name)
    return normalizeNameWhiteSpace(name)

def normalizeNamePrefixSuffix(name):
    name = normalizeNamePunctuation(name)
    return re.sub(prefixSuffixRegex, '', name)


### Memoization

def clearAllLruCaches(verbose=True):
    # Utility to clear any LRU caches of all currently loaded function.
    for mod in list(sys.modules.values()):
        if mod is None:
            continue
        for name in dir(mod):
            # shield against module import errors, etc.:
            try:
                obj = getattr(mod, name, None)
            except:
                pass
            if isinstance(obj, types.FunctionType):
                if hasattr(obj, 'cache_clear'):
                    if verbose:
                        print("clearing LRU cache of", mod.__name__ + '.' + obj.__name__)
                    obj.cache_clear()
