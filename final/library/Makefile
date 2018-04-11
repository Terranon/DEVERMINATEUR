################################################################################
# Description: Makefile for the library lib-deverminateur                      #
#                                                                              #
# Authors: Jean-Raphael Matte, Maximilien Bianchi,                             #
#          Thomas Dufour & William Chartrand                                   #
# Inspired by: Simon Barrette & Jerome Collin                                  #
# Version: 2.0                                                                 #
################################################################################

# This Makefile allows the compilation of libraries developped for Atmel AVR
# microcontrollers, under Linux or Unix, using the AVR-GCC tool.
# This Makefile supports C++

# Configuration {

# Name of you project
# (use a single word, ex: "myproject")
projectName := deverminateur

# Source files
# List all source file to compile, separated by a whitespace,
# or use '$(notdir $(wildcard src/*.cpp))' to include all .cpp files
# in the src directory
# ex: 'tp1.c tp2.cpp':
srcFiles := Adc.cpp Button.cpp Interpreter.cpp Motor.cpp Sensor.cpp Timer.cpp

# Directories where make will look for prerequisites and targets
# Each must be separated by a colon (ex: dir1:dir2:../otherdir)
VPATH := src

# System wide configurations
include ../conf.mk

# } End of configuration



# Variables {

# Utilities and mnemonics
include ../util.mk

verboseSettingFile := verbose.makesetting

# Include settings
-include $(verboseSettingFile)

# List of all object files to be created and linked
objFiles := $(srcFiles:.cpp=.o)

# List of .d dependecy files that will be generated
depFiles := $(srcFiles:.cpp=.d)

# Archiver
AR := ar

# Compiler
CC := avr-gcc

# Options for the compiling stage
CXXFLAGS := \
	-I . \
	-D F_CPU=$(freq)UL \
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
# -fno-exceptions : disable try-catch blocks
# -Wall : Turn on some optional warnings

# Options for the archiving stage
ARFLAGS := rcs
# r : Insert the files into the archive (with replacement). This operation
#     differs from q in that any previously existing members are deleted if
#     their names match those being added.
# c : Create the archive
# s : Write an object-file index into the archive, or update an existing one,
#     even if no other change is made to the archive.

# Command to remove files
remove := rm -f

# Targets

# Output of the archiving stage
arTarget := lib$(projectName).a

# } End of variables



# make rules {

# Phony Targets

# 'make all' compiles the library
.PHONY: all
all: $(arTarget)

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
-include $(depFiles)

# Compiling
define ccRecipe =
$(CC) -c $(CXXFLAGS) -o $@ $<
endef
# -c : Stop after compilation stage, do not link.
# -o $< : Specifies the output file.
%.o: %.cpp %.d
ifeq ($(verbose), true)
	@echo -e "$(xmVrb) Compiling $< into $@ ..."
	@echo -e "$(xmCmd) $(ccRecipe)"
	@$(ccRecipe)
	@echo -e "$(xmVrb) Done"
else
	@$(ccRecipe)
endif

# Archiving
define arRecipe =
$(AR) $(ARFLAGS) $@ $^
endef
$(arTarget): $(objFiles)
ifeq ($(verbose), true)
	@echo -e "$(xmVrb) Archiving $^ in library $@ ..."
	@echo -e "$(xmCmd) $(arRecipe)"
	@$(arRecipe)
	@echo -e "$(xmVrb) Done"
else
	@$(arRecipe)
endif

# make clean leaves only the archive file
define cleanRecipe =
$(remove) $(objFiles) $(depFiles)
endef
.PHONY: clean
clean:
ifeq ($(verbose), true)
	@echo -e "$(xmVrb) Removing intermediate files ..."
	@echo -e "$(xmCmd) $(cleanRecipe)"
	@$(cleanRecipe)
	@echo -e "$(xmVrb) Done"
else
	@$(cleanRecipe)
endif

# mrproper removes all files created during compilation
define mrproperRecipe =
$(remove) $(arTarget)
endef
.PHONY: mrproper
mrproper: clean
ifeq ($(verbose), true)
	@echo -e "$(xmVrb) Removing $(arTarget) ..."
	@echo -e "$(xmCmd) $(mrproperRecipe)"
	@$(mrproperRecipe)
	@echo -e "$(xmVrb) Done"
else
	@$(mrproperRecipe)
endif

# } end of make rules

# EOF
