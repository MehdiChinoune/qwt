/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef TV_PLOT_H
#define TV_PLOT_H

#include <qwt_plot.h>

class TVPlot: public QwtPlot
{
    Q_OBJECT

public:
    TVPlot( QWidget * = NULL );

public Q_SLOTS:
    void setMode( int );
    void exportPlot();

private:
    void populate();

private Q_SLOTS:
    void showItem( const QVariant &, bool on );
};

#endif
