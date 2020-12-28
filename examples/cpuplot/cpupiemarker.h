/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef CPU_PIE_MARKER_H
#define CPU_PIE_MARKER_H

#include <qwt_plot_item.h>

class CpuPieMarker: public QwtPlotItem
{
public:
    CpuPieMarker();

    virtual int rtti() const QWT_OVERRIDE;

    virtual void draw( QPainter *,
        const QwtScaleMap &, const QwtScaleMap &,
        const QRectF & ) const QWT_OVERRIDE;
};

#endif
