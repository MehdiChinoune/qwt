/*****************************************************************************
* Qwt Examples - Copyright (C) 2002 Uwe Rathmann
* This file may be used under the terms of the 3-clause BSD License
*****************************************************************************/

#include "Plot.h"

#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QStatusBar>
#include <QToolButton>
#include <QComboBox>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>

namespace
{
    class MainWindow : public QMainWindow
    {
      public:
        MainWindow( QWidget* = NULL );
    };
}

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
{
    Plot* plot = new Plot( this );
    plot->setContentsMargins( 0, 5, 0, 10 );

    setCentralWidget( plot );

    QToolBar* toolBar = new QToolBar( this );

#ifndef QT_NO_PRINTER
    QToolButton* btnPrint = new QToolButton( toolBar );
    btnPrint->setText( "Print" );
    btnPrint->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnPrint );
    connect( btnPrint, SIGNAL(clicked()), plot, SLOT(printPlot()) );

    toolBar->addSeparator();
#endif

    toolBar->addWidget( new QLabel("Color Map " ) );

    QComboBox* mapBox = new QComboBox( toolBar );
    mapBox->addItem( "RGB" );
    mapBox->addItem( "Hue" );
    mapBox->addItem( "Saturation" );
    mapBox->addItem( "Value" );
    mapBox->addItem( "Sat.+Value" );
    mapBox->addItem( "Alpha" );
    mapBox->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
    toolBar->addWidget( mapBox );

    connect( mapBox, SIGNAL(currentIndexChanged(int)),
        plot, SLOT(setColorMap(int)) );

    toolBar->addWidget( new QLabel("Table " ) );

    QComboBox* colorTableBox = new QComboBox( toolBar );
    colorTableBox->addItem( "None" );
    colorTableBox->addItem( "256" );
    colorTableBox->addItem( "1024" );
    colorTableBox->addItem( "16384" );
    toolBar->addWidget( colorTableBox );

    connect( colorTableBox, SIGNAL(currentIndexChanged(int)),
        plot, SLOT(setColorTableSize(int)) );

    toolBar->addWidget( new QLabel( " Opacity " ) );
    QSlider* slider = new QSlider( Qt::Horizontal );
    slider->setRange( 0, 255 );
    slider->setValue( 255 );
    connect( slider, SIGNAL(valueChanged(int)), plot, SLOT(setAlpha(int)) );

    toolBar->addWidget( slider );
    toolBar->addWidget( new QLabel("   " ) );

    QCheckBox* btnSpectrogram = new QCheckBox( "Spectrogram", toolBar );
    toolBar->addWidget( btnSpectrogram );
    connect( btnSpectrogram, SIGNAL(toggled(bool)),
        plot, SLOT(showSpectrogram(bool)) );

    QCheckBox* btnContour = new QCheckBox( "Contour", toolBar );
    toolBar->addWidget( btnContour );
    connect( btnContour, SIGNAL(toggled(bool)),
        plot, SLOT(showContour(bool)) );

    addToolBar( toolBar );

    btnSpectrogram->setChecked( true );
    btnContour->setChecked( false );

    connect( plot, SIGNAL(rendered(const QString&)),
        statusBar(), SLOT(showMessage(const QString&)),
        Qt::QueuedConnection );
}

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );
    app.setStyle( "Windows" );

    MainWindow window;
    window.resize( 600, 400 );
    window.show();

    return app.exec();
}
