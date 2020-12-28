/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <qwt_global.h>
#include <qmainwindow.h>

class Plot;
class Panel;
class QLabel;
class Settings;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget *parent = NULL );
    virtual bool eventFilter( QObject *, QEvent * ) QWT_OVERRIDE;

private Q_SLOTS:
    void applySettings( const Settings & );

private:
    Plot *d_plot;
    Panel *d_panel;
    QLabel *d_frameCount;
};

#endif
