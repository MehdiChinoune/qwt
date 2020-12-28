/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef CIRCULAR_BUFFER_H
#define CIRCULAR_BUFFER_H

#include <qwt_series_data.h>
#include <qvector.h>

class CircularBuffer: public QwtSeriesData<QPointF>
{
public:
    CircularBuffer( double interval = 10.0, size_t numPoints = 1000 );
    void fill( double interval, size_t numPoints );

    void setReferenceTime( double );
    double referenceTime() const;

    virtual size_t size() const QWT_OVERRIDE;
    virtual QPointF sample( size_t index ) const QWT_OVERRIDE;

    virtual QRectF boundingRect() const QWT_OVERRIDE;

    void setFunction( double( *y )( double ) );

private:
    double ( *d_y )( double );

    double d_referenceTime;
    double d_interval;
    QVector<double> d_values;

    double d_step;
    int d_startIndex;
    double d_offset;
};

#endif
