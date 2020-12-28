/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "mainwindow.h"
#include <qapplication.h>

int main ( int argc, char **argv )
{
    QApplication a( argc, argv );
    a.setStyle( "Windows" );

    MainWindow w;
    w.resize( 700, 500 );
    w.show();

    return a.exec();
}
