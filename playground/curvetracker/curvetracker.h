/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef CURVE_TRACKER_H
#define CURVE_TRACKER_H

#include <qwt_plot_picker.h>

class QwtPlotCurve;
class QLineF;

class CurveTracker: public QwtPlotPicker
{
public:
    CurveTracker( QWidget * );

protected:
    virtual QwtText trackerTextF( const QPointF & ) const QWT_OVERRIDE;
    virtual QRect trackerRect( const QFont & ) const QWT_OVERRIDE;

private:
    QString curveInfoAt( const QwtPlotCurve *, const QPointF & ) const;
    QLineF curveLineAt( const QwtPlotCurve *, double x ) const;
};

#endif
