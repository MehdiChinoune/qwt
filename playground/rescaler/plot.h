/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef PLOT_H
#define PLOT_H

#include <qwt_plot.h>

class RectItem;
class QwtInterval;

class Plot: public QwtPlot
{
    Q_OBJECT

public:
    Plot( QWidget *parent, const QwtInterval & );
    virtual void updateLayout() QWT_OVERRIDE;

    void setRectOfInterest( const QRectF & );

Q_SIGNALS:
    void resized( double xRatio, double yRatio );

private:
    RectItem *d_rectOfInterest;
};

#endif
