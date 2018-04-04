################################################################################
# Description: Makefile for an executable project                              #
#                                                                              #
# Authors: Jean-Raphael Matte, Maximilien Bianchi,                             #
#          Thomas Dufour & William Chartrand                                   #
# Inspired by: Simon Barrette & Jerome Collin                                  #
# Version: 2.0                                                                 #
################################################################################

# This Makefile allows the compilation and installation of projects developped 
# for Atmel AVR microcontrollers, under Linux or Unix, using the AVR-GCC tool.
# This Makefile supports C++

# Configurations {

# System wide configurations
include ../../conf.mk

# } End of configurations



# Variables {

# Utilities and mnemonics
include ../../util.mk

verboseSettingFile := verbose.makesetting

# Include settings
-include $(verboseSettingFile)

# List of all object files to be created and linked
objFiles := $(srcFiles:.cpp=.o)

# List of .d dependecy files that will be generated
depFiles := $(srcFiles:.cpp=.d)

# Actual library file
libFile := $(libDirs)/lib$(libNames).a

# Output of the linking stage
ldTarget := $(projectName).out

# Link map file
ldMapFile := $(ldTarget).map

# hex file to be installed
hexRomTarget := $(projectName).hex

# This file sometimes shows up for unknown reasons
eeHexFile := $(projectName).ee.hex

# Directories in which the compiler will look for header files
ccIncludeOps := $(addsuffix /src,$(addprefix -I,$(libDirs)))

# Directories in which the linker will look for libraries
ldIncludeOps := $(addprefix -L,$(libDirs))

# Libraries to link, formatted as options for the linker
ldLibOps := $(addprefix -l,$(libNames))

# Object copy command
objCopy := avr-objcopy

# AVR programmer
avrProg := avrdude

# AVRDudeProgrammer ID
# Complete list of Programmer IDs available with AVRdude
avrDudeProgID := usbasp

# Object format for the .hex file
# The command to list valid target values is 'objdump -i'
hexFormat := ihex
# ihex : Intel HEX

# Compiler
CC := avr-gcc

# Options for the compiling stage
CXXFLAGS := \
	-I . \
	-D F_CPU=$(freq)UL \
	$(ccIncludeOps) \
	-g \
	-mmcu=$(mcu) \
	-O$(optLevel) \
	-fpack-struct \
	-fshort-enums \
	-funsigned-bitfields \
	-funsigned-char \
	-fno-exceptions \
	-Wall
# -I . : Add the current directory (.) to the list of directories to be searched
#        for header files.
# -D F_CPU=$(freq)UL : Define F_CPU at the frequency specified in freq
# $(ccIncludeOps) : Should be specified as a list of '-I/path/to/my/dir' 
#                   corresponding to other directories to include
# -g : generate debug information to be used by GDB debugger.
# -mmcu=$(mcu) : Specify ATMEL AVR mcu type
# -O$(optLevel) : Set optimizaton level
# -fpack-struct : Pack all structure members together without holes
# -fshort-enums : Allocate to an "enum" type only as many bytes as it needs for 
#                 the declared range of possible values.  Specifically, the 
#                 "enum" type will be equivalent to the smallest integer type 
#                 which has enough room.
# -funsigned-bitfields : bit-fields are unsigned by default
# -funsigned-char : chars are unsigned by default
# -fno-exceptions : Disable try-catch blocks
# -Wall : Turn on some optional warnings

# Options for the linking stage
LDFLAGS := \
	$(ldIncludeOps) \
	-Wl,-Map,$(ldMapFile) \
	-mmcu=$(mcu)
# $(ldIncludeOps) : Should be specified as a list of '-L/path/to/my/dir' options
#                   corresponding to other directories to include
# -Wl,-Map,$(ldMapFile) : give '-Map $(ldMapFile)' as options to the linker, 
#                         which makes it print a link map to the file
#                         $(ldMapFile)
# -mmcu=$(mcu) : Specify the Atmel AVR mcu type

# Command to call make
MAKE := make

# Command to remove files
remove := rm -f

# } End of variables



# make rules {

# 'make all' compiles the project
.PHONY: all
all: $(ldTarget)

# 'make v' toggles the verbose setting by writing to $(verboseSettingFile)
.PHONY: v
v: $(verboseSettingFile)
	@sed -i -e 's/true/oldtrue/g' $(verboseSettingFile)
	@sed -i -e 's/false/true/g' $(verboseSettingFile)
	@sed -i -e 's/oldtrue/false/g' $(verboseSettingFile)
	@cat $(verboseSettingFile)

# Rule for generating the $(verboseSettingFile), if it is not found
$(verboseSettingFile):
	@echo "verbose := true" > $(verboseSettingFile)

# Preprocessing
# Generate .d dependecy files using gcc preprocessing
define prepRecipe =
$(CC) -MM -MF $@ $(CXXFLAGS) $<
endef
# -MM : Instead of outputting the result of preprocessing, output a make rule 
#       describing the dependencies of the source file. Stop after the 
#       preprocessing stage.
# -MF $@ : Specifies a file to write the dependencies to.
%.d: %.cpp
ifeq ($(verbose), true)
	@echo -e "$(xmVrb) Preprocessing $<, outputting depedencies to $@ ..."
	@echo -e "$(xmCmd) $(prepRecipe)"
	@$(prepRecipe)
	@echo -e "$(xmVrb) Done"
else
	@$(prepRecipe)
endif

# Header dependencies
# Includes the make rules contained in .d files generated during preprocessing
include $(depFiles)

# Compiling
define ccRecipe =
$(CC) -c $(CXXFLAGS) -o $@ $<
endef
# -c : Stop after compilation stage, do not link.
# -o $@ : Specifies the output file.
%.o: %.cpp %.d
ifeq ($(verbose), true)
	@echo -e "$(xmVrb) Compiling $< into $@ ..."
	@echo -e "$(xmCmd) $(ccRecipe)"
	@$(ccRecipe)
	@echo -e "$(xmVrb) Done"
else
	@$(ccRecipe)
endif

# Linking
define ldRecipe =
$(CC) $(LDFLAGS) -o $@ $(objFiles) -lm $(ldLibOps)
endef
# -o $@ : Specifies the output file
# -lm : link the math library
# $(ldLibOps) : should be specified as a list of -l'mylib' flags, where 
#               'mylib' is the name of a library (ex: -lmylib)
$(ldTarget): $(objFiles)
ifeq ($(verbose), true)
	@echo -e "$(xmVrb) Linking $^ in project $@, outputting link map to \
		$@.map ..."
	@echo -e "$(xmCmd) $(ldRecipe)"
	@$(ldRecipe)
	@echo -e "$(xmVrb) Done"
else
	@$(ldRecipe)
endif

# The library will be recompiled at the linking stage
$(ldTarget): $(libFile)

# creation of hex files from elf files
define hexRecipe =
$(objCopy) -j .text -j .data -O $(hexFormat) $< $@
endef
# -j .text -j .data : Copy only the .text and .data sections from the input file
#                     to the output file
# -O $(hexFormat) : Write the output file using the object format $(hexFormat)
%.hex: %.out
ifeq ($(verbose), true)
	@echo -e "$(xmVrb) Converting $< to $@ ..."
	@echo -e "$(xmCmd) $(hexRecipe)"
	@$(hexRecipe)
	@echo -e "$(xmVrb) Done"
else
	@$(hexRecipe)
endif

# 'make install' allows compilation of the project and installation on the chip
define installRecipe =
$(avrProg) -c $(avrDudeProgID) -p $(mcu) -P -e \
	-U flash:w:$(hexRomTarget)
endef
# -c $(avrDudeProgID) : Specify the programmer to be used
# -p $(mcu) : Part number
# -P : Port
# -e : Causes a chip erase to be executed.
# -U flash:w:$(hexRomTarget) : Write $(hexRomTarget) to the flash memory
.PHONY: install
install: $(hexRomTarget)
ifeq ($(verbose), true)
	@echo -e "$(xmVrb) Flashing $(hexRomTarget) onto $(mcu) ..."
	@echo -e "$(xmCmd) $(installRecipe)"
	@$(installRecipe)
	@echo -e "$(xmVrb) Done"
else
	@$(installRecipe)
endif

# this rule allows the library to be recompiled
define libRecipe =
	$(MAKE) -B -C $(libDirs)
endef
$(libFile):
ifeq ($(verbose), true)
	@echo -e "$(xmVrb) Recompiling $@ ..."
	@echo -e "$(xmCmd) $(libRecipe)"
	@$(libRecipe)
	@echo -e "$(xmVrb) Done"
else
	@$(libRecipe)
endif

# make clean removes all files created by compilation
define cleanRecipe =
$(remove) $(ldTarget) $(ldMapFile) $(objFiles) $(eeHexFile) $(hexRomTarget) \
	$(depFiles)
endef
.PHONY: clean
clean:
ifeq ($(verbose), true)
	@echo -e "$(xmVrb) Removing all generated files ..."
	@echo -e "$(xmCmd) $(cleanRecipe)"
	@$(cleanRecipe)
	@echo -e "$(xmVrb) Done"
else
	@$(cleanRecipe)
endif

# } end of make rules

# EOF
