/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "attitude_indicator.h"
#include "speedo_meter.h"
#include "cockpit_grid.h"

#include <qwt_analog_clock.h>
#include <qwt_round_scale_draw.h>

#include <qlayout.h>
#include <qtimer.h>

CockpitGrid::CockpitGrid( QWidget *parent ):
    QFrame( parent )
{
    setAutoFillBackground( true );

    setPalette( colorTheme( QColor( Qt::darkGray ).darker( 150 ) ) );

    QGridLayout *layout = new QGridLayout( this );
    layout->setSpacing( 5 );
    layout->setContentsMargins( QMargins() );

    int i;
    for ( i = 0; i < 3; i++ )
    {
        QwtDial *dial = createDial( i );
        layout->addWidget( dial, 0, i );
    }

    for ( i = 0; i < layout->columnCount(); i++ )
        layout->setColumnStretch( i, 1 );
}

QwtDial *CockpitGrid::createDial( int pos )
{
    QwtDial *dial = NULL;
    switch( pos )
    {
        case 0:
        {
            m_clock = new QwtAnalogClock( this );
#if 0
            // disable minor ticks
            m_clock->scaleDraw()->setTickLength( QwtScaleDiv::MinorTick, 0 );
#endif

            const QColor knobColor = QColor( Qt::gray ).lighter( 130 );

            for ( int i = 0; i < QwtAnalogClock::NHands; i++ )
            {
                QColor handColor = QColor( Qt::gray ).lighter( 150 );
                int width = 8;

                if ( i == QwtAnalogClock::SecondHand )
                {
                    handColor = Qt::gray;
                    width = 5;
                }

                QwtDialSimpleNeedle *hand = new QwtDialSimpleNeedle(
                    QwtDialSimpleNeedle::Arrow, true, handColor, knobColor );
                hand->setWidth( width );

                m_clock->setHand( static_cast<QwtAnalogClock::Hand>( i ), hand );
            }

            QTimer *timer = new QTimer( m_clock );
            timer->connect( timer, SIGNAL( timeout() ),
                m_clock, SLOT( setCurrentTime() ) );
            timer->start( 1000 );

            dial = m_clock;
            break;
        }
        case 1:
        {
            m_speedo = new SpeedoMeter( this );
            m_speedo->setScaleStepSize( 20.0 );
            m_speedo->setScale( 0.0, 240.0 );
            m_speedo->scaleDraw()->setPenWidthF( 2 );

            QTimer *timer = new QTimer( m_speedo );
            timer->connect( timer, SIGNAL( timeout() ),
                this, SLOT( changeSpeed() ) );
            timer->start( 50 );

            dial = m_speedo;
            break;
        }
        case 2:
        {
            m_ai = new AttitudeIndicator( this );
            m_ai->scaleDraw()->setPenWidthF( 3 );

            QTimer *gradientTimer = new QTimer( m_ai );
            gradientTimer->connect( gradientTimer, SIGNAL( timeout() ),
                this, SLOT( changeGradient() ) );
            gradientTimer->start( 100 );

            QTimer *angleTimer = new QTimer( m_ai );
            angleTimer->connect( angleTimer, SIGNAL( timeout() ),
                this, SLOT( changeAngle() ) );
            angleTimer->start( 100 );

            dial = m_ai;
            break;
        }

    }

    if ( dial )
    {
        dial->setReadOnly( true );
        dial->setLineWidth( 4 );
        dial->setFrameShadow( QwtDial::Sunken );
    }
    return dial;
}

QPalette CockpitGrid::colorTheme( const QColor &base ) const
{
    QPalette palette;
    palette.setColor( QPalette::Base, base );
    palette.setColor( QPalette::Window, base.darker( 150 ) );
    palette.setColor( QPalette::Mid, base.darker( 110 ) );
    palette.setColor( QPalette::Light, base.lighter( 170 ) );
    palette.setColor( QPalette::Dark, base.darker( 170 ) );
    palette.setColor( QPalette::Text, base.darker( 200 ).lighter( 800 ) );
    palette.setColor( QPalette::WindowText, base.darker( 200 ) );

    return palette;
}

void CockpitGrid::changeSpeed()
{
    static double offset = 0.8;

    double speed = m_speedo->value();

    if ( ( speed < 7.0 && offset < 0.0 ) ||
        ( speed > 203.0 && offset > 0.0 ) )
    {
        offset = -offset;
    }

    static int counter = 0;
    switch( counter++ % 12 )
    {
        case 0:
        case 2:
        case 7:
        case 8:
            break;
        default:
            m_speedo->setValue( speed + offset );
    }
}

void CockpitGrid::changeAngle()
{
    static double offset = 0.05;

    double angle = m_ai->angle();
    if ( angle > 180.0 )
        angle -= 360.0;

    if ( ( angle < -5.0 && offset < 0.0 ) ||
        ( angle > 5.0 && offset > 0.0 ) )
    {
        offset = -offset;
    }

    m_ai->setAngle( angle + offset );
}

void CockpitGrid::changeGradient()
{
    static double offset = 0.005;

    double gradient = m_ai->gradient();

    if ( ( gradient < -0.05 && offset < 0.0 ) ||
        ( gradient > 0.05 && offset > 0.0 ) )
    {
        offset = -offset;
    }

    m_ai->setGradient( gradient + offset );
}

#include "moc_cockpit_grid.cpp"
