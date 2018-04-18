################################################################################
# Description: Makefile configurations for an executable project               #
#                                                                              #
# Authors: Jean-Raphael Matte, Maximilien Bianchi,                             #
#          Thomas Dufour & William Chartrand                                   #
# Inspired by: Simon Barrette & Jerome Collin                                  #
# Version: 2.0                                                                 #
################################################################################

# Configurations {

# Name of you project
# (use a single word, ex: "myproject")
projectName := guccibot

# Source files
# List all .cpp source file to compile, separated by a whitespace,
# or use '$(notdir $(wildcard src/*.cpp))' to include all .cpp files
# in the src directory
srcFiles := guccibot.cpp

# Directories of included libraries
# The paths cannot contain whitespace characters
# (ex: /path/to/mydir ../other/dir)
libDirs := ../../library

# Names of the libraries to link, without the lib/.a prefix/suffix
# (ex: mylib otherlib)
libNames := deverminateur

# Directories where make will look for prerequisites and targets
# Each must be separated by a colon (ex: dir1:dir2:../otherdir)
VPATH := src

# } End of configurations

# The rest of the makefile
include ../common.mk

# EOF
