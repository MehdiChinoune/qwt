/*****************************************************************************
 * Qwt Polar Examples - Copyright (C) 2008   Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "plotwindow.h"
#include "plot.h"

#include <qapplication.h>
#include <qmainwindow.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>

class MainWindow: public QMainWindow
{
public:
    MainWindow( QWidget * = NULL );

private:
    PlotWindow *d_plotWindow;
};

MainWindow::MainWindow( QWidget *parent ):
    QMainWindow( parent )
{
    d_plotWindow = new PlotWindow( this );
    setCentralWidget( d_plotWindow );

    QToolBar *toolBar = new QToolBar( this );

    QToolButton *btnExport = new QToolButton( toolBar );
    btnExport->setText( "Export" );
    btnExport->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnExport );

    QToolButton *btnGrid = new QToolButton( toolBar );
    btnGrid->setText( "Grid" );
    btnGrid->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    btnGrid->setCheckable( true );
    btnGrid->setChecked( true );
    toolBar->addWidget( btnGrid );

    QToolButton *btnRotate = new QToolButton( toolBar );
    btnRotate->setText( "Rotate" );
    btnRotate->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnRotate );
    addToolBar( toolBar );

    QToolButton *btnMirror = new QToolButton( toolBar );
    btnMirror->setText( "Mirror" );
    btnMirror->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnMirror );
    addToolBar( toolBar );

    connect( btnExport, SIGNAL( clicked() ),
        d_plotWindow->plot(), SLOT( exportDocument() ) );
    connect( btnGrid, SIGNAL( toggled( bool ) ),
        d_plotWindow->plot(), SLOT( showGrid( bool ) ) );
    connect( btnRotate, SIGNAL( clicked() ),
        d_plotWindow->plot(), SLOT( rotate() ) );
    connect( btnMirror, SIGNAL( clicked() ),
        d_plotWindow->plot(), SLOT( mirror() ) );
}

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    MainWindow mainWindow;
    mainWindow.resize( 700, 600 );
    mainWindow.show();

    return a.exec();
}
