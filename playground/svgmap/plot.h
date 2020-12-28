/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>
#include <qrect.h>

class QwtPlotGraphicItem;

class Plot: public QwtPlot
{
    Q_OBJECT

public:
    Plot( QWidget * = NULL );

public Q_SLOTS:

#ifndef QT_NO_FILEDIALOG
    void loadSVG();
#endif

    void loadSVG( const QString & );

private:
    void rescale();

    QwtPlotGraphicItem *d_mapItem;
    const QRectF d_mapRect;
};

#endif
