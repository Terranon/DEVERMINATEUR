################################################################################
# Description: Makefile for a set of bytecode instructions                     #
#                                                                              #
# Authors: Jean-Raphael Matte                                                  #
# Version: 1.0                                                                 #
################################################################################

# Name of the project
# (use a single word, ex: "myproject")
PROJECTNAME=instructions

# Source file
# Use the .txt suffix for text files
# ex: 'tp1.txt':
PRJSRC=$(wildcard *.txt)

# Assembler
ASS=progmem

# Programmer
PRG=serieViaUSB

# Command to remove files
REMOVE=rm -f

# Flags sent to the assembler
ASSFLAGS=-v

# Flags sent to the programmer
PRGFLAGS=-e

# Main target
TRG=$(PROJECTNAME).bin

.PHONY: all program clean help

all: $(TRG)

$(TRG): $(PRJSRC)
	$(ASS) $(ASSFLAGS) -o $@ $^

program: $(TRG)
	$(PRG) $(PRGFLAGS) -f $<

clean:
	$(REMOVE) $(TRG)

help:
	@echo "make : assemble the .txt in the current directory"
	@echo "make program : write the EEPROM according to the assembled file"
	@echo "make clean : clean remove the assembled file"
