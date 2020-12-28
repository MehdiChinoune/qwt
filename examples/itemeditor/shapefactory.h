/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef SHAPE_FACTORY_H
#define SHAPE_FACTORY_H

class QPainterPath;
class QPointF;
class QSizeF;

namespace ShapeFactory
{
    enum Shape
    {
        Rect,
        Triangle,
        Ellipse,
        Ring,
        Star,
        Hexagon
    };

    QPainterPath path( Shape, const QPointF &, const QSizeF & );
}

#endif
