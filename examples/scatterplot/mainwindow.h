/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H 1

#include <qmainwindow.h>

class Plot;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();

private:
    void setSamples( int samples );

private:
    Plot *d_plot;
};

#endif
