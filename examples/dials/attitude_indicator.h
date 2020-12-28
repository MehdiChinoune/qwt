/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef ATTITUDE_INDICATOR_H
#define ATTITUDE_INDICATOR_H

#include <qwt_dial.h>
#include <qwt_dial_needle.h>

class AttitudeIndicatorNeedle: public QwtDialNeedle
{
public:
    AttitudeIndicatorNeedle( const QColor & );

protected:
    virtual void drawNeedle( QPainter *,
        double length, QPalette::ColorGroup ) const QWT_OVERRIDE;
};

class AttitudeIndicator: public QwtDial
{
    Q_OBJECT

public:
    AttitudeIndicator( QWidget *parent = NULL );

    double angle() const { return value(); }
    double gradient() const { return d_gradient; }

public Q_SLOTS:
    void setGradient( double );
    void setAngle( double angle ) { setValue( angle ); }

protected:
    virtual void keyPressEvent( QKeyEvent * ) QWT_OVERRIDE;

    virtual void drawScale( QPainter *,
        const QPointF &center, double radius ) const QWT_OVERRIDE;

    virtual void drawScaleContents( QPainter *painter,
        const QPointF &center, double radius ) const QWT_OVERRIDE;

private:
    double d_gradient;
};

#endif
