#!/usr/bin/env python

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

### Various utilities to run FB tools queries directly from PowerLoom

from __future__ import print_function, division, absolute_import

import sys
PY2 = sys.version_info[0] == 2
PY3 = sys.version_info[0] >= 3
if PY3:
    unicode = str
    basestring = (bytes, unicode)
    long = int

import stellapi as spi
import ploompi as pli

# we want all fbtools fns available here, so we only have to import once:
from fbtools import *


textDocumentsModule = 'TEXT-DOCUMENTS'
textDataModule = 'TEXT-DATA'

freebaseIndex = None

def getFreebaseIndex():
    """Access or create the currently configured Freebase index object.
       Use configure() to change configuration options."""
    global freebaseIndex
    if freebaseIndex is None:
        freebaseIndex = FreebaseIndex(config=getConfigFile())
    return freebaseIndex

def clearFreebaseIndex():
    """Clear currently loaded index for potential reload from different config."""
    global freebaseIndex
    freebaseIndex = None

def disableFreebaseIndex():
    """Disable use of Freebase which will make specialists quietly fail."""
    global freebaseIndex
    freebaseIndex = '__DISABLED__'

def enableFreebaseIndex():
    """Enable use of Freebase by specialists."""
    clearFreebaseIndex()


@pli.specialist(relation='freebase-search', module=textDocumentsModule, create=True, arity=4, defer=True)
def freebaseSearchSpecialist(frame, lastMove):
    """Specialist for the PowerLoom `freebase-search(?query ?maxhits ?doc ?score)' relation
       which provides a PowerLoom API for fbtools.FreebaseIndex.search() method.  Uses the
       default field configured with the "LUCENE_DEFAULT_FIELD" configuration property.
    """
    iterator = pli.getFrameIterator(frame)
    if iterator is None:
        # first time around:
        fbi = getFreebaseIndex()
        if not isinstance(fbi, FreebaseIndex):
            return pli.TERMINAL_FAILURE
        # at least the first two arguments need to be bound:
        if pli.isFrameBindingPattern(frame, 'BB'):
            query = pli.getNthFrameBinding(frame, 0)
            maxHits = pli.getNthFrameBinding(frame, 1)
            if isinstance(query, pli.StringWrapper) and isinstance(maxHits, pli.NumberWrapper):
                query = str(query)
                maxHits = int(maxHits)
                try:
                    hits = fbi.search(query, maxHits=maxHits)
                except:
                    return pli.TERMINAL_FAILURE
                iterator = pli.consToPlIterator(spi.pythonToStellaTree(hits))
                pli.setFrameIterator(frame, iterator)
    if iterator is None:
        return pli.TERMINAL_FAILURE
    # generate solutions:
    bindingState = pli.getFrameBindingState(frame)
    for hit in iterator:
        hit = list(hit)
        docid = pli.createIntegerWrapper(int(hit[0]))
        score = pli.createFloatWrapper(float(hit[1]))
        if pli.setNthFrameBinding(frame, 2, docid) and pli.setNthFrameBinding(frame, 3, score):
            return pli.CONTINUING_SUCCESS
        else:
            pli.setFrameBindingState(frame, bindingState)
    return pli.TERMINAL_FAILURE

@pli.specialist(relation='freebase-field-value', module=textDocumentsModule, create=True, arity=3, defer=True)
def freebaseFieldValueSpecialist(frame, lastMove):
    """Specialist for the PowerLoom `freebase-field-value(?docspec ?field ?value)' relation which
       provides a PowerLoom API for fbtools.FreebaseIndex.getFieldValues()/getDocumentFields() methods.
       At least the document spec needs to be bound.  If the field name is also bound, only its values
       will be retrieved; otherwise, all defined fields and values will be retrieved.
    """
    iterator = pli.getFrameIterator(frame)
    if iterator is None:
        # first time around:
        fbi = getFreebaseIndex()
        if not isinstance(fbi, FreebaseIndex):
            return pli.TERMINAL_FAILURE
        values = None
        if pli.isFrameBindingPattern(frame, 'BB'):
            # both document ID and field name are bound:
            docid = pli.getNthFrameBinding(frame, 0)
            field = pli.getNthFrameBinding(frame, 1)
            if isinstance(docid, pli.NumberWrapper):
                docid = int(docid)
            else:
                docid = str(docid)
            field = str(field)
            try:
                values = fbi.getFieldValues(docid, field)
            except:
                return pli.TERMINAL_FAILURE
            if values is not None:
                values = {field: values}
        elif pli.isFrameBindingPattern(frame, 'B_'):
            # only document ID field is bound:
            docid = pli.getNthFrameBinding(frame, 0)
            if isinstance(docid, pli.NumberWrapper):
                docid = int(docid)
            else:
                docid = str(docid)
            try:
                values = fbi.getDocumentFields(docid, maxValues=sys.maxsize)
            except:
                return pli.TERMINAL_FAILURE
        if values is None:
            return pli.TERMINAL_FAILURE
        tuples = []
        for (field, vals) in values.items():
            if isinstance(vals, list):
                for val in vals:
                    tuples.append([field, val])
            else:
                tuples.append([field, vals])
        iterator = pli.consToPlIterator(spi.pythonToStellaTree(tuples))
        pli.setFrameIterator(frame, iterator)
    # generate solutions:
    bindingState = pli.getFrameBindingState(frame)
    for hit in iterator:
        hit = list(hit)
        field = pli.createStringWrapper(str(hit[0]))
        value = pli.createStringWrapper(str(hit[1]))
        if pli.setNthFrameBinding(frame, 1, field) and pli.setNthFrameBinding(frame, 2, value):
            return pli.CONTINUING_SUCCESS
        else:
            pli.setFrameBindingState(frame, bindingState)
    return pli.TERMINAL_FAILURE


# If possible, execute PowerLoom definitions in the current environment, otherwise this has to be called again later:
pli.processDeferredCommands()
