################################################################################
# Description: Makefile for an executable project                              #
#                                                                              #
# Authors: Jean-Raphael Matte, Maximilien Bianchi,                             #
#          Thomas Dufour & William Chartrand                                   #
# Inspired by: Simon Barrette & Jerome Collin                                  #
# Version: 1.0                                                                 #
################################################################################

# This Makefile allows the compilation of libraries developped for Atmel AVR
# microcontrollers, under Linux or Unix, using the AVR-GCC tool.
# This Makefile supports C and C++

# Microcontroller name
# ex: 'at90s8515')
MCU=atmega324pa

# Frequency of the main clock
FREQ=8000000

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

# Optimization level
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s

# Programmer ID - Do not change 
# Complete list of Programmer IDs available with AVRdude
AVRDUDE_PROGRAMMERID=usbasp


# End of configuration



# Variables

# Compiler
CC=avr-gcc

# Object copy command
OBJCOPY=avr-objcopy

# AVRdude command
AVRDUDE=avrdude

# Command to remove files
REMOVE=rm -f

# Console color character constants
NC=\e[1;0m
BLACK=\e[1;30m
RED=\e[1;31m
GREEN=\e[1;32m
YELLOW=\e[1;33m
BLUE=\e[1;34m
MAGENTA=\e[1;35m
CYAN=\e[1;36m
WHITE=\e[1;37m

# Colored [VERBOSE] string
SVERB=$(CYAN)[VERBOSE]$(NC)

# Colored [COMMAND] string
SCOMM=$(BLUE)[COMMAND]$(NC)

# Format (bfdname) for the .hex file
HEXFORMAT=ihex

# Additional settings
-include *.makesetting

# Compiler options

# Flags for the C compiler
CFLAGS= -I . \
	-D F_CPU=$(FREQ)UL \
	-MMD \
	$(INC) \
	-g \
	-mmcu=$(MCU) \
	-O$(OPTLEVEL) \
	-fpack-struct \
	-fshort-enums \
	-funsigned-bitfields \
	-funsigned-char \
	-Wall

# -I . : Add the current directory (.) to the list of directories to be searched 
#        for header files.
# -D F_CPU=$(FREQ)UL : Define F_CPU at the frequency specified in FREQ
# -MMD : Instead of outputting the result of preprocessing, output a make rule 
#        describing the dependencies of the source file. This file will have the 
#        same name as the source file, with a .d suffixe.
# $(INC) : Should be specified as a list of '-I/path/to/my/dir' corresponding to 
#          other directories to include
# -g : generate debug information to be used by GDB debugger.
# -mmcu=$(MCU) : Specify ATMEL AVR MCU type
# -O$(OPTLEVEL) : Set optimizaton level
# -fpack-struct : Pack all structure members together without holes
# -fshort-enums : Allocate to an "enum" type only as many bytes as it needs for 
#                 the declared range of possible values.  Specifically, the 
#                 "enum" type will be equivalent to the smallest integer type 
#                 which has enough room.
# -funsigned-bitfields : bit-fields are unsigned by default
# -funsigned-char : chars are unsigned by default
# -Wall : Turn on some optional warnings

# Flags for the C++ compiler 
CXXFLAGS=-fno-exceptions

# -fno-exceptions : disable try-catch blocks

# Linker to link libraries
LDFLAGS=$(LDINC) \
	-Wl,-Map,$(TRG).map \
	-mmcu=$(MCU)

# $(LDINC) : Should be specified as a list of '-L/path/to/my/dir' corresponding to 
#          other directories to include
# -Wl,-Map,$(TRG).map : give -Map $(TRG).map as options to the linker
# -mmcu=$(MCU) : Specify ATMEL AVR MCU type


# Targets

# Default target names
TRG=$(PROJECTNAME).out
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex


# Definition of all object files

# These functions allow discrimination of .c and .cpp files
# C files
CFILES=$(filter %.c, $(PRJSRC))
# C++ files
CPPFILES=$(filter %.cpp, $(PRJSRC))

# List of all object files to be created
OBJDEPS=$(CFILES:.c=.o) $(CPPFILES:.cpp=.o)

# Additional settings
-include *.makesetting

# make commands 

# Phony Targets
.PHONY: all install clean v

# 'make all' compiles the project
all: $(TRG)

# 'make v' toggles the verbose setting by writing to verbose.makesetting
v:
ifeq ($(VERBOSE), true)
	@echo "VERBOSE=false" > verbose.makesetting
	@echo "Verbose turned off"
else
	@echo "VERBOSE=true" > verbose.makesetting
	@echo "Verbose turned on"
endif

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

# Object files

# C file -> object file
%.o: %.c
ifeq ($(VERBOSE), true)
	@echo -e "$(SVERB) Compiling $@ ..."
	@echo -e -n "$(SCOMM) "
	$(CC) $(CFLAGS) -c $<
	@echo -e "$(SVERB) Done"
else
	@$(CC) $(CFLAGS) -c $<
endif
	
# C++ file -> object file
%.o: %.cpp
ifeq ($(VERBOSE), true)
	@echo -e "$(SVERB) Compiling $@ ..."
	@echo -e -n "$(SCOMM) "
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<
	@echo -e "$(SVERB) Done"
else
	@$(CC) $(CFLAGS) $(CXXFLAGS) -c $<
endif

# Header dependencies
# Includes the make commands contained .d files generated during compilation
-include *.d

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
