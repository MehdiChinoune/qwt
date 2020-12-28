/*****************************************************************************
 * Qwt Polar Examples - Copyright (C) 2008   Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef PLOT_WINDOW_H
#define PLOT_WINDOW_H

#include <qwidget.h>

class Plot;
class QwtScaleWidget;

class PlotWindow: public QWidget
{
public:
    PlotWindow( QWidget * = NULL );

    Plot *plot() { return d_plot; }

private:
    Plot *d_plot;
    QwtScaleWidget *d_colorScale;
};

#endif
