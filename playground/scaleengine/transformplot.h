/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef TRANSFORM_PLOT_H
#define TRANSFORM_PLOT_H

#include <qwt_plot.h>

class QwtTransform;

class TransformPlot: public QwtPlot
{
    Q_OBJECT

public:
    TransformPlot( QWidget *parent = NULL );
    void insertTransformation( const QString &,
        const QColor &, QwtTransform * );

    void setLegendChecked( QwtPlotItem * );

Q_SIGNALS:
    void selected( QwtTransform * );

private Q_SLOTS:
    void legendChecked( const QVariant &, bool on );

private:
};

#endif
