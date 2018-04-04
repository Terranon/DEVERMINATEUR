################################################################################
# Description: Makefile for a set of bytecode instructions                     #
#                                                                              #
# Authors: Jean-Raphael Matte                                                  #
# Version: 1.0                                                                 #
################################################################################

# Assembler
ASS=progmem

# Programmer
PRG=serieViaUSB

# Command to remove files
REMOVE=rm -f

# Command to output the binary file
OD=od -v -t x1

# Flags sent to the assembler
ASSFLAGS=-v

# Flags sent to the programmer
PRGFLAGS=-h -e

# Main target
TRG=$(PROJECTNAME).bin

.PHONY: all program see clean help

all: $(TRG)

$(TRG): $(PRJSRC)
	$(ASS) $(ASSFLAGS) -o $@ $^

program: $(TRG)
	$(PRG) $(PRGFLAGS) -f $<

see :
	$(OD) $(TRG)

clean:
	$(REMOVE) $(TRG)

help:
	@echo "make : assemble the .txt in the current directory"
	@echo "make program : write the EEPROM according to the assembled file"
	@echo "make clean : clean remove the assembled file"
	@echo "make see : output the assembled file"
