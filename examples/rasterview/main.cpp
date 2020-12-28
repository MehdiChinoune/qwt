/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "plot.h"

#include <qapplication.h>
#include <qmainwindow.h>
#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qcombobox.h>
#include <qlabel.h>

class MainWindow: public QMainWindow
{
public:
    MainWindow( QWidget * = NULL );
};

MainWindow::MainWindow( QWidget *parent ):
    QMainWindow( parent )
{
    Plot *plot = new Plot( this );
    setCentralWidget( plot );

    QToolBar *toolBar = new QToolBar( this );

    QComboBox *rasterBox = new QComboBox( toolBar );
    rasterBox->addItem( "Wikipedia" );

    toolBar->addWidget( new QLabel( "Data ", toolBar ) );
    toolBar->addWidget( rasterBox );
    toolBar->addSeparator();

    QComboBox *modeBox = new QComboBox( toolBar );
    modeBox->addItem( "Nearest Neighbour" );
    modeBox->addItem( "Bilinear Interpolation" );
    modeBox->addItem( "Bicubic Interpolation" );

    toolBar->addWidget( new QLabel( "Resampling ", toolBar ) );
    toolBar->addWidget( modeBox );

    toolBar->addSeparator();

    QToolButton *btnExport = new QToolButton( toolBar );
    btnExport->setText( "Export" );
    btnExport->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnExport );

    addToolBar( toolBar );

    connect( modeBox, SIGNAL( activated( int ) ), plot, SLOT( setResampleMode( int ) ) );
    connect( btnExport, SIGNAL( clicked() ), plot, SLOT( exportPlot() ) );
}

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    MainWindow mainWindow;
    mainWindow.resize( 600, 400 );
    mainWindow.show();

    return a.exec();
}
