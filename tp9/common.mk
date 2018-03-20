################################################################################
# Description: Common Makefile instructions                                    #
#                                                                              #
# Authors: Jean-Raphael Matte, Maximilien Bianchi,                             #
#          Thomas Dufour & William Chartrand                                   #
# Inspired by: Simon Barrette & Jerome Collin                                  #
# Version: 1.0                                                                 #
################################################################################

# This Makefile contains all lines that are included in both library building
# and project building Makefiles. As such, it is simply included as is in both
# Makefiles

# Microcontroller name
# ex: 'at90s8515')
MCU=atmega324pa

# Frequency of the main clock
FREQ=8000000

# Optimization level
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s


# End of configuration



# Variables

# Compiler
CC=avr-gcc

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


# Definition of all object files

# These functions allow discrimination of .c and .cpp files
# C files
CFILES=$(filter %.c, $(PRJSRC))
# C++ files
CPPFILES=$(filter %.cpp, $(PRJSRC))

# List of all object files to be created
OBJDEPS=$(CFILES:.c=.o) $(CPPFILES:.cpp=.o)


# make rules

# 'make v' toggles the verbose setting by writing to verbose.makesetting
v:
ifeq ($(VERBOSE), true)
	@echo "VERBOSE=false" > verbose.makesetting
	@echo "Verbose turned off"
else
	@echo "VERBOSE=true" > verbose.makesetting
	@echo "Verbose turned on"
endif

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
