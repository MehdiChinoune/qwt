/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "mainwindow.h"
#include "plot.h"
#include "panel.h"

#include <qstatusbar.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qcoreevent.h>
#include <qelapsedtimer.h>

MainWindow::MainWindow( QWidget *parent ):
    QMainWindow( parent )
{
    QWidget *w = new QWidget( this );

    d_panel = new Panel( w );

    d_plot = new Plot( w );

    QHBoxLayout *hLayout = new QHBoxLayout( w );
    hLayout->addWidget( d_panel );
    hLayout->addWidget( d_plot, 10 );

    setCentralWidget( w );

    d_frameCount = new QLabel( this );
    statusBar()->addWidget( d_frameCount, 10 );

    applySettings( d_panel->settings() );

    connect( d_panel, SIGNAL( settingsChanged( const Settings & ) ),
        this, SLOT( applySettings( const Settings & ) ) );
}

bool MainWindow::eventFilter( QObject *object, QEvent *event )
{
    if ( object == d_plot->canvas() && event->type() == QEvent::Paint )
    {
        static int counter;
        static QElapsedTimer timeStamp;

        if ( !timeStamp.isValid() )
        {
            timeStamp.start();
            counter = 0;
        }
        else
        {
            counter++;

            const double elapsed = timeStamp.elapsed() / 1000.0;
            if ( elapsed >= 1 )
            {
                QString fps;
                fps.setNum( qRound( counter / elapsed ) );
                fps += " Fps";

                d_frameCount->setText( fps );

                counter = 0;
                timeStamp.start();
            }
        }
    }

    return QMainWindow::eventFilter( object, event );
}

void MainWindow::applySettings( const Settings &settings )
{
    d_plot->setSettings( settings );

    // the canvas might have been recreated
    d_plot->canvas()->removeEventFilter( this );
    d_plot->canvas()->installEventFilter( this );
}

#include "moc_mainwindow.cpp"
