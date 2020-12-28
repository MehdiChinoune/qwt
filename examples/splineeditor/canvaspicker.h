/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef CANVAS_PICKER_H
#define CANVAS_PICKER_H

#include <qwt_global.h>
#include <qobject.h>

class QPoint;
class QwtPlot;
class QwtPlotCurve;

class CanvasPicker: public QObject
{
    Q_OBJECT
public:
    CanvasPicker( bool sortedX, QwtPlot *plot );
    virtual bool eventFilter( QObject *, QEvent * ) QWT_OVERRIDE;

private:
    void select( const QPoint & );
    void move( const QPoint & );
    void moveBy( int dx, int dy );
    void release();

    QwtPlot *plot();
    const QwtPlot *plot() const;

    QwtPlotCurve *d_selectedCurve;
    int d_selectedPoint;
    const bool d_sortedX;
};

#endif
