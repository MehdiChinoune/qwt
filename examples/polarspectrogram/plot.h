/*****************************************************************************
 * Qwt Polar Examples - Copyright (C) 2008   Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef PLOT_H
#define PLOT_H

#include <qwt_polar_plot.h>

class QwtPolarGrid;
class QwtPolarSpectrogram;

class Plot: public QwtPolarPlot
{
    Q_OBJECT

public:
    Plot( QWidget * = NULL );
    QwtPolarSpectrogram *spectrogram();

public Q_SLOTS:
    void exportDocument();
    void showGrid( bool );
    void rotate();
    void mirror();

private:
    QwtPolarGrid *d_grid;
    QwtPolarSpectrogram *d_spectrogram;
};

#endif
