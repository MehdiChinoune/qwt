######################################################################
# Qwt Polar Examples - Copyright (C) 2008 Uwe Rathmann
# This file may be used under the terms of the 3-clause BSD License
######################################################################

include( $${PWD}/../examples.pri )

TARGET       = polardemo

HEADERS = \
	Pixmaps.h \
	MainWindow.h \
	Plot.h \
	SettingsEditor.h

SOURCES = \
	MainWindow.cpp \
	Plot.cpp \
	SettingsEditor.cpp \
	main.cpp
