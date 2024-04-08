#!/bin/python

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
# Portions created by the Initial Developer are Copyright (C) 1997-2019      #
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
############################## END LICENSE BLOCK #############################

# Utilities to generate high-level API function signatures for pli.py v1

# OBSOLETE: replaced by ploompi.py which does not need these signatures.
#           pli.h is now part of sources/logic to support pli access via C.

# How to generate:
# - evaluate the buffer which will print all the PLI signatures
# - postedit where necessary


from __future__ import print_function
import re
import os.path
import sys
import plic

# This assumes that `pli.h' resides in the same directory as `plic.py':
pli_c_header_file = os.path.join(os.path.dirname(sys.modules['plic'].__file__), 'pli.h')


def capi_type_to_pli_type(typ):
    if typ == 'void':
        return None
    if typ == 'char*':
        return 'str'
    elif typ == 'int':
        return 'int'
    elif typ == 'boolean':
        return 'bool'
    elif typ == 'pli_Object*':
        return 'StellaObject'
    elif typ[0:4] == 'pli_':
        return typ[4:].replace('*', '')
    return typ

def capi_sig_to_pli_definition(sig):
    cApiSig = re.split('[ ,()]+', sig)
    returnType = capi_type_to_pli_type(cApiSig[0])
    cApiFun = cApiSig[1]
    pliFun = cApiFun[4:]
    print('#', sig)
    print('def ', pliFun, '(', sep='', end='')
    argit=iter(cApiSig[2:-1])
    first=True
    for ctyp, carg in zip(argit, argit):
        if carg == 'module' or carg == 'environment':
            carg += '=None'
        if not first:
            carg = ', ' + carg
        print(carg, end='')
        first = False
    print('):')

    argit=iter(cApiSig[2:-1])
    for ctyp, carg in zip(argit, argit):
        print('    ', carg, ' = pli_to_stella_object_of_type(', carg, ', ', capi_type_to_pli_type(ctyp), ')', sep='')

    print('    ', end='')
    if returnType != None:
        print('return stella_to_pli_object(', end='')
    print('plic.', cApiFun, '(', sep='', end='')
    argit=iter(cApiSig[2:-1])
    first=True
    for ctyp, carg in zip(argit, argit):
        if not first:
            carg = ', ' + carg
        print(carg, end='')
        first = False
    print(')', end='')
    if returnType != None:
        print(')', end='')
    print('\n')

# We simply load the content of `pli.h' and process each function signature:
with open(pli_c_header_file, 'r') as f:
    for line in f.read().splitlines():
        if line[0:1].isalpha() and not line.startswith("typedef"):
            capi_sig_to_pli_definition(line)
