/*****************************************************************************
 * Qwt Polar Examples - Copyright (C) 2008   Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <qmainwindow.h>

class Plot;
class SettingsEditor;
class QwtPolarPanner;
class QwtPolarMagnifier;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = NULL );

private Q_SLOTS:
    void enableZoomMode( bool on );
    void printDocument();
    void exportDocument();

private:
    Plot *d_plot;
    QwtPolarPanner *d_panner;
    QwtPolarMagnifier *d_zoomer;
    SettingsEditor *d_settingsEditor;
};

#endif
