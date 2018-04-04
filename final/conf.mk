################################################################################
# Description: System wide configurations                                      #
#                                                                              #
# Authors: Jean-Raphael Matte, Maximilien Bianchi,                             #
#          Thomas Dufour & William Chartrand                                   #
# Inspired by: Simon Barrette & Jerome Collin                                  #
# Version: 2.0                                                                 #
################################################################################

# This Makefile contains all lines that are included in both library building
# and project building Makefiles. As such, it is simply included as is in both
# Makefiles

# Microcontroller name
# ex: 'at90s8515')
mcu := atmega324pa

# Frequency of the main clock
freq := 8000000

# Optimization level
# Use s (size opt), 1, 2, 3 ou 0 (off)
optLevel := s