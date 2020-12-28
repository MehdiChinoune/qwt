/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef CANVAS_H
#define CANVAS_H

#include <qwt_global.h>
#include <qwidget.h>

class QSvgRenderer;
class QwtGraphic;

class Canvas: public QWidget
{
public:
    enum Mode
    {
        Svg,
        VectorGraphic
    };

    Canvas( Mode, QWidget *parent = NULL );
    virtual ~Canvas();

    void setSvg( const QByteArray & );

protected:
    virtual void paintEvent( QPaintEvent * ) QWT_OVERRIDE;

private:
    void render( QPainter *, const QRect & ) const;

    const Mode d_mode;
    union
    {
        QSvgRenderer *d_renderer;
        QwtGraphic *d_graphic;
    };
};

#endif
