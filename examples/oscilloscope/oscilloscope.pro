######################################################################
# Qwt Examples - Copyright (C) 2002 Uwe Rathmann
# This file may be used under the terms of the 3-clause BSD License
######################################################################

include( $${PWD}/../examples.pri )

TARGET   = oscilloscope

HEADERS = \
    SignalData.h \
    Plot.h \
    Knob.h \
    WheelBox.h \
    SamplingThread.h \
    CurveData.h \
    MainWindow.h 

SOURCES = \
    SignalData.cpp \
    Plot.cpp \
    Knob.cpp \
    WheelBox.cpp \
    SamplingThread.cpp \
    CurveData.cpp \
    MainWindow.cpp \
    main.cpp
