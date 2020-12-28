/*****************************************************************************
 * Qwt Examples
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "mainwindow.h"
#include <qapplication.h>

int main ( int argc, char **argv )
{
    QApplication a( argc, argv );

    MainWindow w;
    w.resize( 540, 400 );
    w.show();

    return a.exec();
}
