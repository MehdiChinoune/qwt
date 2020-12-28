/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef INCREMENTAL_PLOT_H
#define INCREMENTAL_PLOT_H

#include <qwt_plot.h>

class QwtPlotCurve;
class QwtPlotDirectPainter;

class IncrementalPlot : public QwtPlot
{
    Q_OBJECT

public:
    IncrementalPlot( QWidget *parent = NULL );
    virtual ~IncrementalPlot();

    void appendPoint( const QPointF & );
    void clearPoints();

public Q_SLOTS:
    void showSymbols( bool );

private:
    QwtPlotCurve *d_curve;
    QwtPlotDirectPainter *d_directPainter;
};

#endif
