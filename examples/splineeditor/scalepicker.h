/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef SCALE_PICKER_H
#define SCALE_PICKER_H

#include <qwt_global.h>

#include <qobject.h>
#include <qrect.h>

class QwtPlot;
class QwtScaleWidget;

class ScalePicker: public QObject
{
    Q_OBJECT
public:
    ScalePicker( QwtPlot *plot );

    virtual bool eventFilter( QObject *, QEvent * ) QWT_OVERRIDE;

Q_SIGNALS:
    void clicked( int axis, double value );

private:
    void mouseClicked( const QwtScaleWidget *, const QPoint & );
    QRect scaleRect( const QwtScaleWidget * ) const;
};

#endif
