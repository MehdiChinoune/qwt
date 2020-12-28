/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <qmainwindow.h>

class Canvas;
class QPainterPath;

class MainWindow: public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow();

private Q_SLOTS:
    void loadSVG();

private:
    void loadSVG( const QString & );
    void loadPath( const QPainterPath & );

    Canvas *d_canvas[2];
};

#endif
