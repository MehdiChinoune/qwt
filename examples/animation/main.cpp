/*****************************************************************************
* Qwt Examples
* Copyright (C) 1997   Josef Wilgen
* Copyright (C) 2002   Uwe Rathmann
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the Qwt License, Version 1.0
*****************************************************************************/

#include "Plot.h"
#include <QApplication>

#ifndef QWT_NO_OPENGL
    #if QT_VERSION < 0x050000
        #include <qgl.h>
    #endif

    #if QT_VERSION >= 0x060000
        #include <QwtPlotOpenGLCanvas>
typedef QwtPlotOpenGLCanvas Canvas;
    #else
        #include <QwtPlotGLCanvas>
typedef QwtPlotGLCanvas Canvas;
    #endif
#else
typedef QwtPlotCanvas Canvas;
    #include <QwtPlotCanvas>
#endif

int main ( int argc, char** argv )
{
#ifndef QWT_NO_OPENGL
#if QT_VERSION < 0x050000
    // on my box QPaintEngine::OpenGL2 has serious problems, f.e:
    // the lines of a simple drawRect are wrong.

    QGL::setPreferredPaintEngine( QPaintEngine::OpenGL );
#endif
#endif

    QApplication a( argc, argv );

    Plot plot;

    Canvas* canvas = new Canvas();
    canvas->setPaintAttribute( Canvas::BackingStore, false );
    canvas->setFrameStyle( QFrame::NoFrame );

    plot.setCanvas( canvas );
    plot.setCanvasBackground( QColor( 30, 30, 50 ) );

    plot.resize( 400, 400 );
    plot.show();

    return a.exec();
}
