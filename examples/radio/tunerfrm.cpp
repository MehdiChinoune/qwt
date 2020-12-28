/******************************************************************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "tunerfrm.h"

#include <qwt_wheel.h>
#include <qwt_slider.h>
#include <qwt_thermo.h>
#include <qwt_math.h>

#include <qlayout.h>
#include <qlabel.h>

class TuningThermo: public QWidget
{
public:
    TuningThermo( QWidget *parent ):
        QWidget( parent )
    {
        d_thermo = new QwtThermo( this );
        d_thermo->setOrientation( Qt::Horizontal );
        d_thermo->setScalePosition( QwtThermo::NoScale );
        d_thermo->setScale( 0.0, 1.0 );
        d_thermo->setFillBrush( Qt::green );

        QLabel *label = new QLabel( "Tuning", this );
        label->setAlignment( Qt::AlignCenter );

        QVBoxLayout *layout = new QVBoxLayout( this );
        layout->setContentsMargins( QMargins() );
        layout->addWidget( d_thermo );
        layout->addWidget( label );

        setFixedWidth( 3 * label->sizeHint().width() );
    }

    void setValue( double value )
    {
        d_thermo->setValue( value );
    }

private:
    QwtThermo *d_thermo;
};

TunerFrame::TunerFrame( QWidget *parent ):
    QFrame( parent )
{
    const double freqMin = 87.5;
    const double freqMax = 108;

    d_sliderFrequency = new QwtSlider( this );
    d_sliderFrequency->setOrientation( Qt::Horizontal );
    d_sliderFrequency->setScalePosition( QwtSlider::TrailingScale );
    d_sliderFrequency->setScale( freqMin, freqMax );
    d_sliderFrequency->setTotalSteps(
        qRound( ( freqMax - freqMin ) / 0.01 ) );
    d_sliderFrequency->setSingleSteps( 1 );
    d_sliderFrequency->setPageSteps( 10 );
    d_sliderFrequency->setScaleMaxMinor( 5 );
    d_sliderFrequency->setScaleMaxMajor( 12 );
    d_sliderFrequency->setHandleSize( QSize( 80, 20 ) );
    d_sliderFrequency->setBorderWidth( 1 );

    d_thermoTune = new TuningThermo( this );

    d_wheelFrequency = new QwtWheel( this );
    d_wheelFrequency->setMass( 0.5 );
    d_wheelFrequency->setRange( 87.5, 108 );
    d_wheelFrequency->setSingleStep( 0.01 );
    d_wheelFrequency->setPageStepCount( 10 );
    d_wheelFrequency->setTotalAngle( 3600.0 );
    d_wheelFrequency->setFixedHeight( 30 );


    connect( d_wheelFrequency, SIGNAL( valueChanged( double ) ), SLOT( adjustFreq( double ) ) );
    connect( d_sliderFrequency, SIGNAL( valueChanged( double ) ), SLOT( adjustFreq( double ) ) );

    QVBoxLayout *mainLayout = new QVBoxLayout( this );
    mainLayout->setContentsMargins( 10, 10, 10, 10 );
    mainLayout->setSpacing( 5 );
    mainLayout->addWidget( d_sliderFrequency );

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->setContentsMargins( QMargins() );
    hLayout->addWidget( d_thermoTune, 0 );
    hLayout->addStretch( 5 );
    hLayout->addWidget( d_wheelFrequency, 2 );

    mainLayout->addLayout( hLayout );
}

void TunerFrame::adjustFreq( double frq )
{
    const double factor = 13.0 / ( 108 - 87.5 );

    const double x = ( frq - 87.5 ) * factor;
    const double field = qwtSqr( std::sin( x ) * std::cos( 4.0 * x ) );

    d_thermoTune->setValue( field );

    if ( d_sliderFrequency->value() != frq )
        d_sliderFrequency->setValue( frq );
    if ( d_wheelFrequency->value() != frq )
        d_wheelFrequency->setValue( frq );

    Q_EMIT fieldChanged( field );
}

void TunerFrame::setFreq( double frq )
{
    d_wheelFrequency->setValue( frq );
}

#include "moc_tunerfrm.cpp"
