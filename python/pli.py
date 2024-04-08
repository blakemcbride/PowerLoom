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

# Backwards compatible import wrapper for the Python interface v1 to PowerLoom PLI

# OBSOLETE: this version is now replaced by ploompi.py which is more general
#           and uses stellapi.py instead of the obsolete plic.py.

import sys

if sys.modules.get('ploompi') is not None:
    # v2 is already loaded, but somebody is importing expecting v1 names:
    from ploompi import *
    # provide some v2->v1 mappings:
    pli_tree_to_cons_tree = spi.pythonToStellaTree
    dwim_pli_tree_to_logic_tree = dwimTreeToLogicTree
    def_constant = defConstant
    lookup_constant = lookupConstant
    get_constant = lookupConstant
    delete_constant = deleteConstant
    parse_command = parseCommand
else:
    # load v1:
    from ploompi_v1 import *
    # prevent later v2 import to step on v1 symbols:
    sys.modules['ploompi'] = sys.modules[__name__]
    # possibly provide some v1->v2 mappings here, but this should really not be happening:
    pass
