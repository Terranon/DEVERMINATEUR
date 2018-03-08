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

# Microcontroller name
# ex: 'at90s8515')
MCU=atmega324pa

# Frequency of the main clock
FREQ=8000000

# Name of you project
# (use a single word, ex: "myproject")
PROJECTNAME=lib-deverminateur

# Source files
# Use the .cpp suffix for c++ files
# List all source file to compile, separated by a whitespace,
# or use '$(wildcard *.cpp)' to include all .cpp files in the current directory
# ex: 'tp1.c tp2.cpp':
PRJSRC=Adc.cpp Motor.cpp PhotoCell.cpp Timer.cpp

# Additional inclusions (ex: -I/path/to/mydir)
INC=

# Libraries to link (ex: -lmylib)
LIBS=

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


HEXFORMAT=ihex


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
LDFLAGS=-Wl,-Map,$(TRG).map \
	-mmcu=$(MCU)

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


# make commands 

# Phony Targets
.PHONY: all install clean

# 'make all' compiles the project
all: $(TRG)

# Linking
$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) -lm $(LIBS)

# -lm : link the math library
# $(LIBS) : should be specified as a list of -l'mylib' flags, where 
#           'mylib' is replaced with the name of a library (ex: -lmylib)

# Object files
# C file -> object file
%.o: %.c
	$(CC) $(CFLAGS) -c $<
# C++ file -> object file
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

# Header dependencies
# Includes the make commands contained .d files generated during compilation
-include *.d

# creation of hex files from elf files
%.hex: %.out
	$(OBJCOPY) -j .text -j .data -O $(HEXFORMAT) $< $@

# make install allows compilation of the project and installation on the chip
install: $(HEXROMTRG)
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID) \
		-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)

# make clean removes all files created by compilation
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d

# EOF
