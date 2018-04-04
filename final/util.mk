################################################################################
# Description: Utilities and mnemonics                                         #
#                                                                              #
# Authors: Jean-Raphael Matte, Maximilien Bianchi,                             #
#          Thomas Dufour & William Chartrand                                   #
# Inspired by: Simon Barrette & Jerome Collin                                  #
# Version: 2.0                                                                 #
################################################################################

# Special characters
null :=
space := $(null) $(null)
colon := :

# Console utilities

# Escape character
xesc := \e

# Control Sequence Introducer
xCSI := $(xesc)[

# Select Graphic Rendition
xSGR := m

# Console color character constants
xcNull := $(xCSI)0$(xSGR)
xcBlack := $(xCSI)30$(xSGR)
xcRed := $(xCSI)1;31$(xSGR)
xcGreen := $(xCSI)1;32$(xSGR)
xcYellow := $(xCSI)1;33$(xSGR)
xcBlue := $(xCSI)1;34$(xSGR)
xcMagenta := $(xCSI)1;35$(xSGR)
xcCyan := $(xCSI)1;36$(xSGR)
xcWhite := $(xCSI)1;37$(xSGR)

# Colored [VERBOSE] string
xmVrb := $(xcCyan)[VERBOSE]$(xcNull)

# Colored [COMMAND] string
xmCmd := $(xcBlue)[COMMAND]$(xcNull)