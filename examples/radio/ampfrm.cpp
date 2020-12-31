/******************************************************************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "ampfrm.h"

#include <qwt_knob.h>
#include <qwt_thermo.h>
#include <qwt_round_scale_draw.h>
#include <qwt_math.h>

#include <qlayout.h>
#include <qlabel.h>
#include <qevent.h>
#include <qmath.h>

class Knob: public QWidget
{
public:
    Knob( const QString &title, double min, double max, QWidget *parent ):
        QWidget( parent )
    {
        m_knob = new QwtKnob( this );
        m_knob->setScale( min, max );
        m_knob->setTotalSteps( 0 ); // disable
        m_knob->setScaleMaxMajor( 10 );

        m_knob->setKnobStyle( QwtKnob::Raised );
        m_knob->setKnobWidth( 50 );
        m_knob->setBorderWidth( 2 );
        m_knob->setMarkerStyle( QwtKnob::Notch );
        m_knob->setMarkerSize( 8 );

        m_knob->scaleDraw()->setTickLength( QwtScaleDiv::MinorTick, 4 );
        m_knob->scaleDraw()->setTickLength( QwtScaleDiv::MediumTick, 4 );
        m_knob->scaleDraw()->setTickLength( QwtScaleDiv::MajorTick, 6 );

        m_label = new QLabel( title, this );
        m_label->setAlignment( Qt::AlignTop | Qt::AlignHCenter );

        setSizePolicy( QSizePolicy::MinimumExpanding,
            QSizePolicy::MinimumExpanding );
    }

    virtual QSize sizeHint() const QWT_OVERRIDE
    {
        QSize sz1 = m_knob->sizeHint();
        QSize sz2 = m_label->sizeHint();

        const int w = qMax( sz1.width(), sz2.width() );
        const int h = sz1.height() + sz2.height();

        int off = qCeil( m_knob->scaleDraw()->extent( m_knob->font() ) );
        off -= 10; // spacing

        return QSize( w, h - off );
    }

    void setValue( double value )
    {
        m_knob->setValue( value );
    }

    double value() const
    {
        return m_knob->value();
    }

protected:
    virtual void resizeEvent( QResizeEvent *event ) QWT_OVERRIDE
    {
        const QSize sz = event->size();

        int h = m_label->sizeHint().height();

        m_label->setGeometry( 0, sz.height() - h, sz.width(), h );

        h = m_knob->sizeHint().height();
        int off = qCeil( m_knob->scaleDraw()->extent( m_knob->font() ) );
        off -= 10; // spacing

        m_knob->setGeometry( 0, m_label->pos().y() - h + off,
            sz.width(), h );
    }

private:
    QwtKnob *m_knob;
    QLabel *m_label;
};

class Thermo: public QWidget
{
public:
    Thermo( const QString &title, QWidget *parent ):
        QWidget( parent )
    {
        m_thermo = new QwtThermo( this );
        m_thermo->setPipeWidth( 6 );
        m_thermo->setScale( -40, 10 );
        m_thermo->setFillBrush( Qt::green );
        m_thermo->setAlarmBrush( Qt::red );
        m_thermo->setAlarmLevel( 0.0 );
        m_thermo->setAlarmEnabled( true );

        QLabel *label = new QLabel( title, this );
        label->setAlignment( Qt::AlignTop | Qt::AlignLeft );

        QVBoxLayout *layout = new QVBoxLayout( this );
        layout->setContentsMargins( QMargins() );
        layout->setSpacing( 0 );
        layout->addWidget( m_thermo, 10 );
        layout->addWidget( label );
    }

    void setValue( double value )
    {
        m_thermo->setValue( value );
    }

private:
    QwtThermo *m_thermo;
};

AmpFrame::AmpFrame( QWidget *p ):
    QFrame( p )
{
    m_knbVolume = new Knob( "Volume", 0.0, 10.0, this );
    m_knbBalance = new Knob( "Balance", -10.0, 10.0, this );
    m_knbTreble = new Knob( "Treble", -10.0, 10.0, this );
    m_knbBass = new Knob( "Bass", -10.0, 10.0, this );

    m_thmLeft = new Thermo( "Left [dB]", this );
    m_thmRight = new Thermo( "Right [dB]", this );

    QHBoxLayout *layout = new QHBoxLayout( this );
    layout->setSpacing( 0 );
    layout->setContentsMargins( 10, 10, 10, 10 );
    layout->addWidget( m_knbVolume );
    layout->addWidget( m_knbBalance);
    layout->addWidget( m_knbTreble);
    layout->addWidget( m_knbBass );
    layout->addSpacing( 20 );
    layout->addStretch( 10 );
    layout->addWidget( m_thmLeft );
    layout->addSpacing( 10 );
    layout->addWidget( m_thmRight );

    m_knbVolume->setValue( 7.0 );
    ( void )startTimer( 50 );
}

void AmpFrame::timerEvent( QTimerEvent * )
{
    static double phs = 0;

    //
    //  This amplifier generates its own input signal...
    //

    const double sig_bass = ( 1.0 + 0.1 * m_knbBass->value() )
        * std::sin( 13.0 * phs );
    const double sig_mim_l = std::sin( 17.0 * phs );
    const double sig_mim_r = std::cos( 17.5 * phs );
    const double sig_trbl_l = 0.5 * ( 1.0 + 0.1 * m_knbTreble->value() )
        * std::sin( 35.0 * phs );
    const double sig_trbl_r = 0.5 * ( 1.0 + 0.1 * m_knbTreble->value() )
        * std::sin( 34.0 * phs );

    double sig_l = 0.05 * m_master * m_knbVolume->value()
        * qwtSqr( sig_bass + sig_mim_l + sig_trbl_l );
    double sig_r = 0.05 * m_master * m_knbVolume->value()
        * qwtSqr( sig_bass + sig_mim_r + sig_trbl_r );

    double balance = 0.1 * m_knbBalance->value();
    if ( balance > 0 )
        sig_l *= ( 1.0 - balance );
    else
        sig_r *= ( 1.0 + balance );

    if ( sig_l > 0.01 )
        sig_l = 20.0 * log10( sig_l );
    else
        sig_l = -40.0;

    if ( sig_r > 0.01 )
        sig_r = 20.0 * log10( sig_r );
    else
        sig_r = - 40.0;

    m_thmLeft->setValue( sig_l );
    m_thmRight->setValue( sig_r );

    phs += M_PI / 100;
    if ( phs > M_PI )
        phs = 0;
}

void AmpFrame::setMaster( double v )
{
    m_master = v;
}

#include "moc_ampfrm.cpp"
