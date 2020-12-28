/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "compass_grid.h"
#include "cockpit_grid.h"

#include <qapplication.h>
#include <qtabwidget.h>

int main ( int argc, char **argv )
{
    QApplication a( argc, argv );

    QTabWidget tabWidget;
    tabWidget.addTab( new CompassGrid, "Compass" );
    tabWidget.addTab( new CockpitGrid, "Cockpit" );

    tabWidget.show();

    return a.exec();
}

