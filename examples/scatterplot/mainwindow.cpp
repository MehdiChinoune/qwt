/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "mainwindow.h"
#include "plot.h"

#include <qwt_math.h>

static double randomValue()
{
    // a number between [ 0.0, 1.0 ]
    return ( qwtRand() % 100000 ) / 100000.0;
}

MainWindow::MainWindow()
{
    d_plot = new Plot( this );
    d_plot->setTitle( "Scatter Plot" );
    setCentralWidget( d_plot );

    // a million points
    setSamples( 100000 );
}

void MainWindow::setSamples( int numPoints )
{
    QPolygonF samples;

    for ( int i = 0; i < numPoints; i++ )
    {
        const double x = randomValue() * 24.0 + 1.0;
        const double y = std::log( 10.0 * ( x - 1.0 ) + 1.0 )
            * ( randomValue() * 0.5 + 0.9 );

        samples += QPointF( x, y );
    }

    d_plot->setSamples( samples );
}

#include "moc_mainwindow.cpp"
