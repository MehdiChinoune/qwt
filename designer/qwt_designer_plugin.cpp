/******************************************************************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#if defined( _MSC_VER ) /* MSVC Compiler */
#pragma warning ( disable : 4786 )
#endif

#include <qglobal.h>
#include <qaction.h>
#include <QtPlugin>
#include <QDesignerFormEditorInterface>
#include <QDesignerFormWindowInterface>
#include <QDesignerFormWindowCursorInterface>
#include <QExtensionManager>
#include <QErrorMessage>

#include "qwt_designer_plugin.h"

#ifndef NO_QWT_PLOT
#include "qwt_designer_plotdialog.h"
#include "qwt_plot.h"
#include "qwt_plot_canvas.h"
#include "qwt_scale_widget.h"
#endif

#ifndef NO_QWT_WIDGETS
#include "qwt_counter.h"
#include "qwt_wheel.h"
#include "qwt_thermo.h"
#include "qwt_knob.h"
#include "qwt_slider.h"
#include "qwt_dial.h"
#include "qwt_dial_needle.h"
#include "qwt_analog_clock.h"
#include "qwt_compass.h"
#endif

#include "qwt_text_label.h"

using namespace QwtDesignerPlugin;

CustomWidgetInterface::CustomWidgetInterface( QObject* parent )
    : QObject( parent )
    , m_isInitialized( false )
{
}

bool CustomWidgetInterface::isContainer() const
{
    return false;
}

bool CustomWidgetInterface::isInitialized() const
{
    return m_isInitialized;
}

QIcon CustomWidgetInterface::icon() const
{
    return m_icon;
}

QString CustomWidgetInterface::codeTemplate() const
{
    return m_codeTemplate;
}

QString CustomWidgetInterface::domXml() const
{
    return m_domXml;
}

QString CustomWidgetInterface::group() const
{
    return "Qwt Widgets";
}

QString CustomWidgetInterface::includeFile() const
{
    return m_include;
}

QString CustomWidgetInterface::name() const
{
    return m_name;
}

QString CustomWidgetInterface::toolTip() const
{
    return m_toolTip;
}

QString CustomWidgetInterface::whatsThis() const
{
    return m_whatsThis;
}

void CustomWidgetInterface::initialize(
    QDesignerFormEditorInterface* formEditor )
{
    if ( m_isInitialized )
        return;

    QExtensionManager* manager = formEditor->extensionManager();
    if ( manager )
    {
        manager->registerExtensions( new TaskMenuFactory( manager ),
            Q_TYPEID( QDesignerTaskMenuExtension ) );
    }

    m_isInitialized = true;
}

#ifndef NO_QWT_PLOT

PlotInterface::PlotInterface( QObject* parent )
    : CustomWidgetInterface( parent )
{
    m_name = "QwtPlot";
    m_include = "qwt_plot.h";
    m_icon = QPixmap( ":/pixmaps/qwtplot.png" );
    m_domXml =
        "<widget class=\"QwtPlot\" name=\"qwtPlot\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>400</width>\n"
        "   <height>200</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget* PlotInterface::createWidget( QWidget* parent )
{
    return new QwtPlot( parent );
}


PlotCanvasInterface::PlotCanvasInterface( QObject* parent )
    : CustomWidgetInterface( parent )
{
    m_name = "QwtPlotCanvas";
    m_include = "qwt_plot_canvas.h";
    m_icon = QPixmap( ":/pixmaps/qwtplot.png" );
    m_domXml =
        "<widget class=\"QwtPlotCanvas\" name=\"qwtPlotCanvas\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>400</width>\n"
        "   <height>200</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget* PlotCanvasInterface::createWidget( QWidget* parent )
{
    return new QwtPlotCanvas( parent );
}

#endif

#ifndef NO_QWT_POLAR

PolarPlotInterface::PolarPlotInterface( QObject* parent )
    : CustomWidgetInterface( parent )
{
    m_name = "QwtPolarPlot";
    m_include = "qwt_polar_plot.h";
    m_icon = QPixmap( ":/pixmaps/qwt_polar_plot.png" );
    m_domXml =
        "<widget class=\"QwtPolarPlot\" name=\"qwtPolarPlot\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>400</width>\n"
        "   <height>400</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget* PlotCanvasInterface::createWidget( QWidget* parent )
{
    return new QwtPolarPlot( parent );
}

#endif

#ifndef NO_QWT_WIDGETS

AnalogClockInterface::AnalogClockInterface( QObject* parent )
    : CustomWidgetInterface( parent )
{
    m_name = "QwtAnalogClock";
    m_include = "qwt_analog_clock.h";
    m_icon = QPixmap( ":/pixmaps/qwtanalogclock.png" );
    m_domXml =
        "<widget class=\"QwtAnalogClock\" name=\"AnalogClock\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>200</width>\n"
        "   <height>200</height>\n"
        "  </rect>\n"
        " </property>\n"
        " <property name=\"lineWidth\">\n"
        "  <number>4</number>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget* AnalogClockInterface::createWidget( QWidget* parent )
{
    return new QwtAnalogClock( parent );
}

#endif

#ifndef NO_QWT_WIDGETS

CompassInterface::CompassInterface( QObject* parent )
    : CustomWidgetInterface( parent )
{
    m_name = "QwtCompass";
    m_include = "qwt_compass.h";
    m_icon = QPixmap( ":/pixmaps/qwtcompass.png" );
    m_domXml =
        "<widget class=\"QwtCompass\" name=\"Compass\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>200</width>\n"
        "   <height>200</height>\n"
        "  </rect>\n"
        " </property>\n"
        " <property name=\"lineWidth\">\n"
        "  <number>4</number>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget* CompassInterface::createWidget( QWidget* parent )
{
    QwtCompass* compass = new QwtCompass( parent );
    compass->setNeedle( new QwtCompassMagnetNeedle(
        QwtCompassMagnetNeedle::TriangleStyle,
        compass->palette().color( QPalette::Mid ),
        compass->palette().color( QPalette::Dark ) ) );

    return compass;
}

#endif

#ifndef NO_QWT_WIDGETS

CounterInterface::CounterInterface( QObject* parent )
    : CustomWidgetInterface( parent )
{
    m_name = "QwtCounter";
    m_include = "qwt_counter.h";
    m_icon = QPixmap( ":/pixmaps/qwtcounter.png" );
    m_domXml =
        "<widget class=\"QwtCounter\" name=\"Counter\">\n"
        "</widget>\n";
}

QWidget* CounterInterface::createWidget( QWidget* parent )
{
    return new QwtCounter( parent );
}

#endif

#ifndef NO_QWT_WIDGETS

DialInterface::DialInterface( QObject* parent )
    : CustomWidgetInterface( parent )
{
    m_name = "QwtDial";
    m_include = "qwt_dial.h";
    m_icon = QPixmap( ":/pixmaps/qwtdial.png" );
    m_domXml =
        "<widget class=\"QwtDial\" name=\"Dial\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>200</width>\n"
        "   <height>200</height>\n"
        "  </rect>\n"
        " </property>\n"
        " <property name=\"lineWidth\">\n"
        "  <number>4</number>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget* DialInterface::createWidget( QWidget* parent )
{
    QwtDial* dial = new QwtDial( parent );
    dial->setNeedle( new QwtDialSimpleNeedle(
        QwtDialSimpleNeedle::Arrow, true,
        dial->palette().color( QPalette::Dark ),
        dial->palette().color( QPalette::Mid ) ) );

    return dial;
}

#endif

#ifndef NO_QWT_WIDGETS

KnobInterface::KnobInterface( QObject* parent )
    : CustomWidgetInterface( parent )
{
    m_name = "QwtKnob";
    m_include = "qwt_knob.h";
    m_icon = QPixmap( ":/pixmaps/qwtknob.png" );
    m_domXml =
        "<widget class=\"QwtKnob\" name=\"Knob\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>150</width>\n"
        "   <height>150</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget* KnobInterface::createWidget( QWidget* parent )
{
    return new QwtKnob( parent );
}

#endif

#ifndef NO_QWT_PLOT

ScaleWidgetInterface::ScaleWidgetInterface( QObject* parent )
    : CustomWidgetInterface( parent )
{
    m_name = "QwtScaleWidget";
    m_include = "qwt_scale_widget.h";
    m_icon = QPixmap( ":/pixmaps/qwtscale.png" );
    m_domXml =
        "<widget class=\"QwtScaleWidget\" name=\"ScaleWidget\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>60</width>\n"
        "   <height>250</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget* ScaleWidgetInterface::createWidget( QWidget* parent )
{
    return new QwtScaleWidget( QwtScaleDraw::LeftScale, parent );
}

#endif

#ifndef NO_QWT_WIDGETS

SliderInterface::SliderInterface( QObject* parent )
    : CustomWidgetInterface( parent )
{
    m_name = "QwtSlider";
    m_include = "qwt_slider.h";
    m_icon = QPixmap( ":/pixmaps/qwtslider.png" );
    m_domXml =
        "<widget class=\"QwtSlider\" name=\"Slider\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>60</width>\n"
        "   <height>250</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget* SliderInterface::createWidget( QWidget* parent )
{
    return new QwtSlider( parent );
}

#endif

TextLabelInterface::TextLabelInterface( QObject* parent )
    : CustomWidgetInterface( parent )
{
    m_name = "QwtTextLabel";
    m_include = "qwt_text_label.h";

    m_icon = QPixmap( ":/pixmaps/qwtwidget.png" );
    m_domXml =
        "<widget class=\"QwtTextLabel\" name=\"TextLabel\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>100</width>\n"
        "   <height>20</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget* TextLabelInterface::createWidget( QWidget* parent )
{
    return new QwtTextLabel( QwtText( "Label" ), parent );
}

#ifndef NO_QWT_WIDGETS

ThermoInterface::ThermoInterface( QObject* parent )
    : CustomWidgetInterface( parent )
{
    m_name = "QwtThermo";
    m_include = "qwt_thermo.h";
    m_icon = QPixmap( ":/pixmaps/qwtthermo.png" );
    m_domXml =
        "<widget class=\"QwtThermo\" name=\"Thermo\">\n"
        " <property name=\"geometry\">\n"
        "  <rect>\n"
        "   <x>0</x>\n"
        "   <y>0</y>\n"
        "   <width>60</width>\n"
        "   <height>250</height>\n"
        "  </rect>\n"
        " </property>\n"
        "</widget>\n";
}

QWidget* ThermoInterface::createWidget( QWidget* parent )
{
    return new QwtThermo( parent );
}

#endif

#ifndef NO_QWT_WIDGETS

WheelInterface::WheelInterface( QObject* parent )
    : CustomWidgetInterface( parent )
{
    m_name = "QwtWheel";
    m_include = "qwt_wheel.h";
    m_icon = QPixmap( ":/pixmaps/qwtwheel.png" );
    m_domXml =
        "<widget class=\"QwtWheel\" name=\"Wheel\">\n"
        "</widget>\n";
}

QWidget* WheelInterface::createWidget( QWidget* parent )
{
    return new QwtWheel( parent );
}

#endif

CustomWidgetCollectionInterface::CustomWidgetCollectionInterface( QObject* parent )
    : QObject( parent )
{
#ifndef NO_QWT_PLOT
    m_plugins.append( new PlotInterface( this ) );

#if 0
    // better not: the designer crashes TODO ..
    m_plugins.append( new PlotCanvasInterface( this ) );
#endif

    m_plugins.append( new ScaleWidgetInterface( this ) );
#endif

#ifndef NO_QWT_WIDGETS
    m_plugins.append( new AnalogClockInterface( this ) );
    m_plugins.append( new CompassInterface( this ) );
    m_plugins.append( new CounterInterface( this ) );
    m_plugins.append( new DialInterface( this ) );
    m_plugins.append( new KnobInterface( this ) );
    m_plugins.append( new SliderInterface( this ) );
    m_plugins.append( new ThermoInterface( this ) );
    m_plugins.append( new WheelInterface( this ) );
#endif

    m_plugins.append( new TextLabelInterface( this ) );
}

QList< QDesignerCustomWidgetInterface* >
CustomWidgetCollectionInterface::customWidgets( void ) const
{
    return m_plugins;
}

TaskMenuFactory::TaskMenuFactory( QExtensionManager* parent )
    : QExtensionFactory( parent )
{
}

QObject* TaskMenuFactory::createExtension(
    QObject* object, const QString& iid, QObject* parent ) const
{
    if ( iid == Q_TYPEID( QDesignerTaskMenuExtension ) )
    {
#ifndef NO_QWT_PLOT
        if ( QwtPlot* plot = qobject_cast< QwtPlot* >( object ) )
            return new TaskMenuExtension( plot, parent );
#endif
#ifndef NO_QWT_WIDGETS
        if ( QwtDial* dial = qobject_cast< QwtDial* >( object ) )
            return new TaskMenuExtension( dial, parent );
#endif
    }

    return QExtensionFactory::createExtension( object, iid, parent );
}


TaskMenuExtension::TaskMenuExtension( QWidget* widget, QObject* parent )
    : QObject( parent )
    , m_widget( widget )
{
    m_editAction = new QAction( tr( "Edit Qwt Attributes ..." ), this );
    connect( m_editAction, SIGNAL(triggered()),
        this, SLOT(editProperties()) );
}

QList< QAction* > TaskMenuExtension::taskActions() const
{
    QList< QAction* > list;
    list.append( m_editAction );
    return list;
}

QAction* TaskMenuExtension::preferredEditAction() const
{
    return m_editAction;
}

void TaskMenuExtension::editProperties()
{
    const QVariant v = m_widget->property( "propertiesDocument" );
    if ( !v.canConvert< QString >() )
        return;

#ifndef NO_QWT_PLOT
    const QString properties = v.value< QString >();

    if ( qobject_cast< QwtPlot* >( m_widget ) )
    {
        PlotDialog dialog( properties );
        connect( &dialog, SIGNAL(edited(const QString&)),
            SLOT(applyProperties(const QString&)) );
        ( void )dialog.exec();
        return;
    }
#endif

    static QErrorMessage* errorMessage = NULL;
    if ( errorMessage == NULL )
        errorMessage = new QErrorMessage();
    errorMessage->showMessage( "Not implemented yet." );
}

void TaskMenuExtension::applyProperties( const QString& properties )
{
    QDesignerFormWindowInterface* formWindow =
        QDesignerFormWindowInterface::findFormWindow( m_widget );
    if ( formWindow && formWindow->cursor() )
        formWindow->cursor()->setProperty( "propertiesDocument", properties );
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2( QwtDesignerPlugin, CustomWidgetCollectionInterface )
#endif

#if QWT_MOC_INCLUDE
#include "moc_qwt_designer_plugin.cpp"
#endif
