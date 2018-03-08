################################################################################
# Description: Makefile for the library lib-deverminateur                      #
#                                                                              #
# Authors: Jean-Raphael Matte, Maximilien Bianchi,                             #
#          Thomas Dufour & William Chartrand                                   #
# Inspired by: Simon Barrette & Jerome Collin                                  #
# Version: 1.0                                                                 #
################################################################################

# This Makefile allows the compilation of libraries developped for Atmel AVR
# microcontrollers, under Linux or Unix, using the AVR-GCC tool.
# This Makefile supports C and C++

# Name of you project
# (use a single word, ex: "myproject")
PROJECTNAME=deverminateur

# Source files
# Use the .cpp suffix for c++ files
# List all source file to compile, separated by a whitespace,
# or use '$(wildcard *.cpp)' to include all .cpp files in the current directory
# ex: 'tp1.c tp2.cpp':
PRJSRC=Adc.cpp Motor.cpp Timer.cpp Led.cpp

# Additional inclusions (ex: -I/path/to/mydir)
INC=


# End of configuration



# Variables

# Archiver
AR=ar

# Options for the archiver

AROPTIONS=rcs

# r : Insert the files into the archive (with replacement). This operation
#     differs from q in that any previously existing members are deleted if
#     their names match those being added.
# c : Create the archive
# s : Write an object-file index into the archive, or update an existing one,
#     even if no other change is made to the archive.

# Targets

# Default target names
TRG=lib$(PROJECTNAME).a


# make rules 

# Phony Targets
.PHONY: all clean v mrproper

# 'make all' compiles the library
all: $(TRG)

# Common lines
include ../Makefile.common

# Archiving
$(TRG): $(OBJDEPS)
ifeq ($(VERBOSE), true)
	@echo -e "$(SVERB) Linking $(OBJDEPS) in project $(TRG) ..."
	@echo -e -n "$(SCOMM) "
	$(AR) $(AROPTIONS) $(TRG) $(OBJDEPS)
	@echo -e "$(SVERB) Done"
else
	@$(AR) $(AROPTIONS)v $(TRG) $(OBJDEPS)
endif

# -lm : link the math library
# $(LIBS) : should be specified as a list of -l'mylib' flags, where 
#           'mylib' is replaced with the name of a library (ex: -lmylib)

# make clean leaves only the archive file
clean:
ifeq ($(VERBOSE), true)
	@echo -e "$(SVERB) Removing compilation files ..."
	@echo -e -n "$(SCOMM) "
	$(REMOVE) $(OBJDEPS) *.d
	@echo -e "$(SVERB) Done"
else
	@$(REMOVE) $(OBJDEPS) *.d
endif

# mrproper removes all files created during compilation
mrproper: clean
ifeq ($(VERBOSE), true)
	@echo -e "$(SVERB) Removing $(TRG) ..."
	@echo -e -n "$(SCOMM) "
	$(REMOVE) $(TRG)
	@echo -e "$(SVERB) Done"
else
	@$(REMOVE) $(TRG)
endif

# EOF
