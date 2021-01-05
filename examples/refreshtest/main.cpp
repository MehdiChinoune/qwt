/*****************************************************************************
* Qwt Examples - Copyright (C) 2002 Uwe Rathmann
* This file may be used under the terms of the 3-clause BSD License
*****************************************************************************/

#include "MainWindow.h"
#include <QApplication>

#ifndef QWT_NO_OPENGL
#if QT_VERSION < 0x050000
#define USE_OPENGL 1
#endif
#endif

#if USE_OPENGL
#include <qgl.h>
#endif

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    MainWindow window;
    window.resize( 600, 400 );
    window.show();

    return app.exec();
}
