######################################################################
# Qwt Examples - Copyright (C) 2002 Uwe Rathmann
# This file may be used under the terms of the 3-clause BSD License
######################################################################

include( $${PWD}/../examples.pri )

TARGET       = stockchart

HEADERS = \
    legend.h \
    griditem.h \
    plot.h \
    quotefactory.h

SOURCES = \
    legend.cpp \
    griditem.cpp \
    quotefactory.cpp \
    plot.cpp \
    main.cpp
