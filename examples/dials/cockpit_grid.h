/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef COCKPIT_GRID
#define COCKPIT_GRID

#include <qframe.h>
#include <qpalette.h>

class QwtDial;
class QwtAnalogClock;
class SpeedoMeter;
class AttitudeIndicator;

class CockpitGrid: public QFrame
{
    Q_OBJECT

public:
    CockpitGrid( QWidget *parent = NULL );

private Q_SLOTS:
    void changeSpeed();
    void changeGradient();
    void changeAngle();

private:
    QPalette colorTheme( const QColor & ) const;
    QwtDial *createDial( int pos );

    QwtAnalogClock *d_clock;
    SpeedoMeter *d_speedo;
    AttitudeIndicator *d_ai;
};

#endif
