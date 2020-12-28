######################################################################
# Qwt Examples - Copyright (C) 2002 Uwe Rathmann
# This file may be used under the terms of the 3-clause BSD License
######################################################################

include( $${PWD}/../examples.pri )

TARGET       = refreshtest

HEADERS = \
    settings.h \
    circularbuffer.h \
    panel.h \
    plot.h \
    mainwindow.h

SOURCES = \
    circularbuffer.cpp \
    panel.cpp \
    plot.cpp \
    mainwindow.cpp \
    main.cpp

