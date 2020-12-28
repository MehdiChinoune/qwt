/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef RANDOM_PLOT_H
#define RANDOM_PLOT_H

#include "incrementalplot.h"
#include <qelapsedtimer.h>

class QTimer;

class RandomPlot: public IncrementalPlot
{
    Q_OBJECT

public:
    RandomPlot( QWidget *parent );

    virtual QSize sizeHint() const QWT_OVERRIDE;

Q_SIGNALS:
    void running( bool );
    void elapsed( int ms );

public Q_SLOTS:
    void clear();
    void stop();
    void append( int timeout, int count );

private Q_SLOTS:
    void appendPoint();

private:
    void initCurve();

    QTimer *d_timer;
    int d_timerCount;

    QElapsedTimer d_timeStamp;
};

#endif
