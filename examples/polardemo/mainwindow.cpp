/*****************************************************************************
 * Qwt Polar Examples - Copyright (C) 2008   Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "mainwindow.h"
#include "plot.h"
#include "settingseditor.h"
#include "pixmaps.h"

#include <qwt_polar_panner.h>
#include <qwt_polar_magnifier.h>
#include <qwt_polar_renderer.h>

#include <qtoolbar.h>
#include <qtoolbutton.h>
#include <qprinter.h>
#include <qprintdialog.h>
#include <qlayout.h>

MainWindow::MainWindow( QWidget *parent ):
    QMainWindow( parent )
{
    QWidget *w = new QWidget( this );

    d_plot = new Plot( w );

    d_panner = new QwtPolarPanner( d_plot->canvas() );
    d_panner->setEnabled( false );

    d_zoomer = new QwtPolarMagnifier( d_plot->canvas() );
    d_zoomer->setEnabled( false );

    d_settingsEditor = new SettingsEditor( w );

    d_settingsEditor->showSettings( d_plot->settings() );
    connect( d_settingsEditor, SIGNAL( edited( const PlotSettings & ) ),
        d_plot, SLOT( applySettings( const PlotSettings & ) ) );

    QHBoxLayout *layout = new QHBoxLayout( w );
    layout->addWidget( d_settingsEditor, 0 );
    layout->addWidget( d_plot, 10 );

    setCentralWidget( w );

    QToolBar *toolBar = new QToolBar( this );

    QToolButton *btnZoom = new QToolButton( toolBar );

    const QString zoomHelp =
        "Use the wheel to zoom in/out.\n"
        "When the plot is zoomed in,\n"
        "use the left mouse button to move it.";

    btnZoom->setText( "Zoom" );
    btnZoom->setIcon( QPixmap( zoom_xpm ) );
    btnZoom->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    btnZoom->setToolTip( zoomHelp );
    btnZoom->setCheckable( true );
    toolBar->addWidget( btnZoom );
    connect( btnZoom, SIGNAL( toggled( bool ) ), SLOT( enableZoomMode( bool ) ) );

    QToolButton *btnPrint = new QToolButton( toolBar );
    btnPrint->setText( "Print" );
    btnPrint->setIcon( QPixmap( print_xpm ) );
    btnPrint->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnPrint );
    connect( btnPrint, SIGNAL( clicked() ), SLOT( printDocument() ) );

    QToolButton *btnExport = new QToolButton( toolBar );
    btnExport->setText( "Export" );
    btnExport->setIcon( QPixmap( print_xpm ) );
    btnExport->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnExport );

    connect( btnExport, SIGNAL( clicked() ), SLOT( exportDocument() ) );

    addToolBar( toolBar );
}

void MainWindow::printDocument()
{
    QPrinter printer( QPrinter::HighResolution );

    QString docName = d_plot->title().text();
    if ( !docName.isEmpty() )
    {
        docName.replace ( "\n", " -- " );
        printer.setDocName ( docName );
    }

    printer.setCreator( "polar plot demo example" );
#if QT_VERSION >= 0x050300
    printer.setPageOrientation( QPageLayout::Landscape );
#else
    printer.setOrientation( QPrinter::Landscape );
#endif

    QPrintDialog dialog( &printer );
    if ( dialog.exec() )
    {
        QwtPolarRenderer renderer;
        renderer.renderTo( d_plot, printer );
    }
}

void MainWindow::exportDocument()
{
    QString fileName = "polarplot.pdf";

    QwtPolarRenderer renderer;
    renderer.exportTo( d_plot, "polarplot.pdf" );
}

void MainWindow::enableZoomMode( bool on )
{
    d_panner->setEnabled( on );
    d_zoomer->setEnabled( on );
}

#include "moc_mainwindow.cpp"
