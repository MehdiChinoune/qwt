/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>

class Settings;
class LegendItem;
class QwtLegend;

class Plot: public QwtPlot
{
    Q_OBJECT

public:
    Plot( QWidget *parent = NULL );
    virtual ~Plot();

public Q_SLOTS:
    void applySettings( const Settings & );

public:
    virtual void replot() QWT_OVERRIDE;

private:
    void insertCurve();

    QwtLegend *d_externalLegend;
    LegendItem *d_legendItem;
    bool d_isDirty;
};

#endif
