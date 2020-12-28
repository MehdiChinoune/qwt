######################################################################
# Qwt Examples - Copyright (C) 2002 Uwe Rathmann
# This file may be used under the terms of the 3-clause BSD License
######################################################################

include( $${PWD}/../playground.pri )

greaterThan(QT_MAJOR_VERSION, 4) { 
    !qtHaveModule(svg) {
        error("Qt has been built without SVG support !")
    }   
}

TARGET   = graphicscale
QT      += svg

HEADERS = \
    canvas.h \
    mainwindow.h

SOURCES = \
    canvas.cpp \
    mainwindow.cpp \
    main.cpp

