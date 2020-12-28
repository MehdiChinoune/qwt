/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef PLOT_H
#define PLOT_H

#include "shapefactory.h"
#include <qwt_plot.h>

class QColor;
class QSizeF;
class QPointF;
class Editor;

class Plot: public QwtPlot
{
    Q_OBJECT

public:
    Plot( QWidget *parent = NULL );

public Q_SLOTS:
    void exportPlot();
    void setMode( int );

private:
    void populate();

    void addShape( const QString &title,
        ShapeFactory::Shape, const QColor &,
        const QPointF &, const QSizeF & );

    Editor *d_editor;
};

#endif
