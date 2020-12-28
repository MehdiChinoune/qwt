/*****************************************************************************
 * Qwt Examples
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>
#include <qelapsedtimer.h>

class Curve;

class Plot: public QwtPlot
{
public:
    Plot( QWidget * = NULL);

protected:
    virtual void timerEvent( QTimerEvent * ) QWT_OVERRIDE;

private:
    void updateCurves();

    enum { CurveCount = 4 };
    Curve *d_curves[CurveCount];

    QElapsedTimer d_timer;
};

#endif
