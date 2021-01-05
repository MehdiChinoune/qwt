/*****************************************************************************
* Qwt Examples - Copyright (C) 2002 Uwe Rathmann
* This file may be used under the terms of the 3-clause BSD License
*****************************************************************************/

#include "Plot.h"

#include <QApplication>
#include <QMainWindow>
#include <QComboBox>
#include <QToolBar>
#include <QToolButton>

namespace
{
    class MainWindow : public QMainWindow
    {
      public:
        MainWindow( QWidget* parent = NULL )
            : QMainWindow( parent )
        {
            d_plot = new Plot( this );
            setCentralWidget( d_plot );

            QToolBar* toolBar = new QToolBar( this );

            QComboBox* typeBox = new QComboBox( toolBar );
            typeBox->addItem( "Bars" );
            typeBox->addItem( "Tube" );
            typeBox->setCurrentIndex( 1 );
            typeBox->setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );

            QToolButton* btnExport = new QToolButton( toolBar );
            btnExport->setText( "Export" );
            btnExport->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
            connect( btnExport, SIGNAL(clicked()), d_plot, SLOT(exportPlot()) );

            toolBar->addWidget( typeBox );
            toolBar->addWidget( btnExport );
            addToolBar( toolBar );

            d_plot->setMode( typeBox->currentIndex() );
            connect( typeBox, SIGNAL(currentIndexChanged(int)),
                d_plot, SLOT(setMode(int)) );
        }

      private:
        Plot* d_plot;
    };
}

int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    MainWindow window;
    window.setObjectName( "MainWindow" );
    window.resize( 600, 400 );
    window.show();

    return app.exec();
}
