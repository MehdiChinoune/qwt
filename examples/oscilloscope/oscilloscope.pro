######################################################################
# Qwt Examples - Copyright (C) 2002 Uwe Rathmann
# This file may be used under the terms of the 3-clause BSD License
######################################################################

include( $${PWD}/../examples.pri )

TARGET   = oscilloscope

HEADERS = \
    signaldata.h \
    plot.h \
    knob.h \
    wheelbox.h \
    samplingthread.h \
    curvedata.h \
    mainwindow.h 

SOURCES = \
    signaldata.cpp \
    plot.cpp \
    knob.cpp \
    wheelbox.cpp \
    samplingthread.cpp \
    curvedata.cpp \
    mainwindow.cpp \
    main.cpp
