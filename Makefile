# Top-level Makefile for the PowerLoom system

# OBSOLETE: adapt this for latest version of PowerLoom or remove.

# This is the distribution Makefile for PowerLoom.  It can be used to
# compile and build both the Common-Lisp and the C++ version of
# PowerLoom.  If necessary, edit the Common-Lisp and/or C/C++ compiler
# settings below to reflect your environment and preferences.  Then type
#
# 	make		to build PowerLoom with Lisp and C++
#	make lisp	to build the Lisp version only
#	make c++	to build the C++ version only
#	make clean	to remove non-essential binary files
#	make extraclean	to remove all binary, executable, and backup files
#
# If you are only interested in either the Common-Lisp or the C++
# version of PowerLoom but not both, you can remove the unneeded
# source files to save disk space.  Type
#
#	make kill-lisp-sources  to remove all Common-Lisp source files
#	make kill-c++-sources   to remove all C++ source files
#
# The compiled Common-Lisp version of PowerLoom can be loaded by
# loading the file `load-powerloom.lisp' into your Lisp environment.
# The compiled C++ version of PowerLoom can be run by executing
# `bin/powerloom'.  Currently, there is no `make install' support to
# install PowerLoom outside its source tree.  After building PowerLoom
# you can type `make clean' to remove all non-essential binary files
# yet preserving your Lisp binaries and C++ executables necessary to
# run PowerLoom.

#
# Common-Lisp settings (edit to reflect your environment):
#

LISP = acl # name of your Common-Lisp executable

#
# C/C++ Compiler settings (edit to reflect your environment):
#

# GNU gcc/g++ settings:
CXX    = g++
CC     = gcc
CFLAGS = -w -g -O2

# Sparcworks settings:
#CXX    = CC
#CC     = cc
#CFLAGS = -w -fast

######################################################################
#                NO CUSTOMIZATION BEYOND THIS POINT                  #
######################################################################

all: lisp c++

.PHONY: lisp c++

#
# Lisp installation:
#

lisp: compile

.PHONY: edit-root-directory compile

translations.lisp.in:
	cp -p translations.lisp translations.lisp.in

edit-root-directory: translations.lisp.in
	rm -f translations.lisp
	sed -e "/(defvar \*powerloom-root-directory\*/s?\".*\"?\"`pwd`/\"?" \
	    translations.lisp.in > translations.lisp

compile: edit-root-directory
	echo '(load "load-powerloom.lisp")' | $(LISP)

#
# C++ installation:
#

c++:
	cd logic; \
	$(MAKE) $(MFLAGS) PWD=`pwd` CC=$(CC) CXX=$(CXX) CFLAGS="$(CFLAGS)"

#
# Cleaning up
#

.PHONY: clean extraclean kill-lisp-sources kill-c++-sources

kill-lisp-sources:
	find ./ -name '*.lisp' -exec /bin/rm -rf {} \;

kill-c++-sources:
	/bin/rm -rf stella/cpp-lib/
	find ./ -name '*.hh' -exec /bin/rm -rf {} \;
	find ./ -name '*.cc' -exec /bin/rm -rf {} \;

clean:
	cd logic; $(MAKE) $(MFLAGS) PWD=`pwd` clean

extraclean: clean
	cd bin; find ./ ! -type d -exec /bin/rm -rf {} \;
	/bin/rm -f *~ \#* .#*
	cd logic; $(MAKE) $(MFLAGS) PWD=`pwd` extraclean
