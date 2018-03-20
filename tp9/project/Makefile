################################################################################
# Description: Makefile for an executable project                              #
#                                                                              #
# Authors: Jean-Raphael Matte, Maximilien Bianchi,                             #
#          Thomas Dufour & William Chartrand                                   #
# Inspired by: Simon Barrette & Jerome Collin                                  #
# Version: 1.0                                                                 #
################################################################################

# This Makefile allows the compilation of projects developped for Atmel AVR
# microcontrollers, under Linux or Unix, using the AVR-GCC tool.
# This Makefile supports C and C++

# Name of you project
# (use a single word, ex: "myproject")
PROJECTNAME=project

# Source files
# Use the .cpp suffix for c++ files
# List all source file to compile, separated by a whitespace,
# or use '$(wildcard *.cpp)' to include all .cpp files in the current directory
# ex: 'tp1.c tp2.cpp':
PRJSRC=project.cpp

# Additional inclusions (ex: -I/path/to/mydir)
INC=-I../library

# Additional directories where the linker should look for libraries
LDINC=$(patsubst -I%,-L%,$(INC))

# Libraries to link (ex: -lmylib)
LIBS=-ldeverminateur

# Programmer ID - Do not change 
# Complete list of Programmer IDs available with AVRdude
AVRDUDE_PROGRAMMERID=usbasp


# End of configuration



# Variables

# Object copy command
OBJCOPY=avr-objcopy

# AVRdude command
AVRDUDE=avrdude

# Format (bfdname) for the .hex file
HEXFORMAT=ihex

# Linker to link libraries
LDFLAGS=$(LDINC) \
	-Wl,-Map,$(TRG).map \
	-mmcu=$(MCU)

# $(LDINC) : Should be specified as a list of '-L/path/to/my/dir' corresponding 
# to other directories to include
# -Wl,-Map,$(TRG).map : give -Map $(TRG).map as options to the linker
# -mmcu=$(MCU) : Specify ATMEL AVR MCU type


# Targets

# Default target names
TRG=$(PROJECTNAME).out
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex


# make rules

# Phony Targets
.PHONY: all install clean v

# 'make all' compiles the project
all: $(TRG)

# Common lines
include ../Makefile.common

# Linking
$(TRG): $(OBJDEPS)
ifeq ($(VERBOSE), true)
	@echo -e "$(SVERB) Linking $(OBJDEPS) in project $(TRG) ..."
	@echo -e -n "$(SCOMM) "
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) -lm $(LIBS)
	@echo -e "$(SVERB) Done"
else
	@$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) -lm $(LIBS)
endif

# -lm : link the math library
# $(LIBS) : should be specified as a list of -l'mylib' flags, where 
#           'mylib' is replaced with the name of a library (ex: -lmylib)

# creation of hex files from elf files
%.hex: %.out
ifeq ($(VERBOSE), true)
	@echo -e "$(SVERB) Converting $< to $@ ..."
	@echo -e -n "$(SCOMM) "
	$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@
	@echo -e "$(SVERB) Done"
else
	@$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@
endif

# make install allows compilation of the project and installation on the chip
install: $(HEXROMTRG)
ifeq ($(VERBOSE), true)
	@echo -e "$(SVERB) Flashing $(HEXROMTRG) onto $(MCU) ..."
	@echo -e -n "$(SCOMM) "
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) \
		-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)
	@echo -e "$(SVERB) Done"
else
	@$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) \
		-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)
endif

# make clean removes all files created by compilation
clean:
ifeq ($(VERBOSE), true)
	@echo -e "$(SVERB) Removing all compilation files ..."
	@echo -e -n "$(SCOMM) "
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d
	@echo -e "$(SVERB) Done"
else
	@$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d
endif

# EOF
