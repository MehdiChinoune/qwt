/*****************************************************************************
* Qwt Polar Examples - Copyright (C) 2008   Uwe Rathmann
* This file may be used under the terms of the 3-clause BSD License
*****************************************************************************/

#include "MainWindow.h"
#include "Plot.h"
#include "SettingsEditor.h"
#include "Pixmaps.h"

#include <QwtPolarPanner>
#include <QwtPolarMagnifier>
#include <QwtPolarRenderer>

#include <QToolBar>
#include <QToolButton>
#include <QPrinter>
#include <QPrintDialog>
#include <QLayout>

MainWindow::MainWindow( QWidget* parent )
    : QMainWindow( parent )
{
    QWidget* w = new QWidget( this );

    m_plot = new Plot( w );

    m_panner = new QwtPolarPanner( m_plot->canvas() );
    m_panner->setEnabled( false );

    m_zoomer = new QwtPolarMagnifier( m_plot->canvas() );
    m_zoomer->setEnabled( false );

    m_settingsEditor = new SettingsEditor( w );

    m_settingsEditor->showSettings( m_plot->settings() );
    connect( m_settingsEditor, SIGNAL(edited(const PlotSettings&)),
        m_plot, SLOT(applySettings(const PlotSettings&)) );

    QHBoxLayout* layout = new QHBoxLayout( w );
    layout->addWidget( m_settingsEditor, 0 );
    layout->addWidget( m_plot, 10 );

    setCentralWidget( w );

    QToolBar* toolBar = new QToolBar( this );

    QToolButton* btnZoom = new QToolButton( toolBar );

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
    connect( btnZoom, SIGNAL(toggled(bool)), SLOT(enableZoomMode(bool)) );

    QToolButton* btnPrint = new QToolButton( toolBar );
    btnPrint->setText( "Print" );
    btnPrint->setIcon( QPixmap( print_xpm ) );
    btnPrint->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnPrint );
    connect( btnPrint, SIGNAL(clicked()), SLOT(printDocument()) );

    QToolButton* btnExport = new QToolButton( toolBar );
    btnExport->setText( "Export" );
    btnExport->setIcon( QPixmap( print_xpm ) );
    btnExport->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
    toolBar->addWidget( btnExport );

    connect( btnExport, SIGNAL(clicked()), SLOT(exportDocument()) );

    addToolBar( toolBar );
}

void MainWindow::printDocument()
{
    QPrinter printer( QPrinter::HighResolution );

    QString docName = m_plot->title().text();
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
        renderer.renderTo( m_plot, printer );
    }
}

void MainWindow::exportDocument()
{
    QString fileName = "polarplot.pdf";

    QwtPolarRenderer renderer;
    renderer.exportTo( m_plot, "polarplot.pdf" );
}

void MainWindow::enableZoomMode( bool on )
{
    m_panner->setEnabled( on );
    m_zoomer->setEnabled( on );
}

#include "moc_MainWindow.cpp"
