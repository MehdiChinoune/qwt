######################################################################
# Qwt Examples - Copyright (C) 2002 Uwe Rathmann
# This file may be used under the terms of the 3-clause BSD License
######################################################################

include( $${PWD}/../examples.pri )

TARGET       = dials

HEADERS = \
    attitude_indicator.h \
    speedo_meter.h \
    cockpit_grid.h \
    compass_grid.h

SOURCES = \
    attitude_indicator.cpp \
    speedo_meter.cpp \
    cockpit_grid.cpp \
    compass_grid.cpp \
    dials.cpp

