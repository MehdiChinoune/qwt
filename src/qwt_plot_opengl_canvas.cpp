/******************************************************************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "qwt_plot_opengl_canvas.h"
#include "qwt_plot.h"
#include "qwt_painter.h"

#include <qpainter.h>
#include <qpainterpath.h>
#include <qcoreevent.h>
#include <qopenglframebufferobject.h>
#include <qopenglpaintdevice.h>

class QwtPlotOpenGLCanvas::PrivateData
{
  public:
    PrivateData()
        : isPolished( false )
        , fboDirty( true )
        , fbo( NULL )
    {
    }

    ~PrivateData()
    {
        delete fbo;
    }

    int numSamples;

    bool isPolished;
    bool fboDirty;
    QOpenGLFramebufferObject* fbo;
};


/*!
   \brief Constructor

   \param plot Parent plot widget
   \sa QwtPlot::setCanvas()
 */
QwtPlotOpenGLCanvas::QwtPlotOpenGLCanvas( QwtPlot* plot )
    : QOpenGLWidget( plot )
    , QwtPlotAbstractGLCanvas( this )
{
    QSurfaceFormat fmt = format();
    fmt.setSamples( 4 );

    init( fmt );
}

QwtPlotOpenGLCanvas::QwtPlotOpenGLCanvas(
        const QSurfaceFormat& format, QwtPlot* plot )
    : QOpenGLWidget( plot )
    , QwtPlotAbstractGLCanvas( this )
{
    init( format );
}

void QwtPlotOpenGLCanvas::init( const QSurfaceFormat& format )
{
    m_data = new PrivateData;
    m_data->numSamples = format.samples();

    setFormat( format );

#if 1
    setAttribute( Qt::WA_OpaquePaintEvent, true );
#endif
}

//! Destructor
QwtPlotOpenGLCanvas::~QwtPlotOpenGLCanvas()
{
    delete m_data;
}

/*!
   Paint event

   \param event Paint event
   \sa QwtPlot::drawCanvas()
 */
void QwtPlotOpenGLCanvas::paintEvent( QPaintEvent* event )
{
    if ( m_data->isPolished )
        QOpenGLWidget::paintEvent( event );
}

/*!
   Qt event handler for QEvent::PolishRequest and QEvent::StyleChange
   \param event Qt Event
   \return See QGLWidget::event()
 */
bool QwtPlotOpenGLCanvas::event( QEvent* event )
{
    const bool ok = QOpenGLWidget::event( event );

    if ( event->type() == QEvent::PolishRequest )
    {
        // In opposite to non OpenGL widgets receive pointless
        // early repaints. As we always have a QEvent::PolishRequest
        // followed by QEvent::Paint, we can ignore all thos repaints.

        m_data->isPolished = true;
    }

    if ( event->type() == QEvent::PolishRequest ||
        event->type() == QEvent::StyleChange )
    {
        // assuming, that we always have a styled background
        // when we have a style sheet

        setAttribute( Qt::WA_StyledBackground,
            testAttribute( Qt::WA_StyleSheet ) );
    }

    return ok;
}

void QwtPlotOpenGLCanvas::replot()
{
    QwtPlotAbstractGLCanvas::replot();
}

void QwtPlotOpenGLCanvas::invalidateBackingStore()
{
    m_data->fboDirty = true;
}

void QwtPlotOpenGLCanvas::clearBackingStore()
{
    delete m_data->fbo;
    m_data->fbo = NULL;
}

QPainterPath QwtPlotOpenGLCanvas::borderPath( const QRect& rect ) const
{
    return borderPath2( rect );
}

void QwtPlotOpenGLCanvas::initializeGL()
{
}

void QwtPlotOpenGLCanvas::paintGL()
{
    const bool hasFocusIndicator =
        hasFocus() && focusIndicator() == CanvasFocusIndicator;

    QPainter painter;

    if ( testPaintAttribute( QwtPlotOpenGLCanvas::BackingStore ) &&
        QOpenGLFramebufferObject::hasOpenGLFramebufferBlit() )
    {
        const qreal pixelRatio = QwtPainter::devicePixelRatio( NULL );
        const QSize fboSize = size() * pixelRatio;

        if ( hasFocusIndicator )
            painter.begin( this );

        /*
           QOpenGLWidget has its own internal FBO, that is used to restore
           its content without having to repaint. This works fine when f.e
           a rubberband is moving on top, but there are still situations,
           where we can repaint without an potentially expensive replot:

               - when having the focus the top level window gets activated/deactivated
               - ???
         */

        if ( m_data->fbo )
        {
            if ( m_data->fbo->size() != fboSize )
            {
                delete m_data->fbo;
                m_data->fbo = NULL;
            }
        }

        if ( m_data->fbo == NULL )
        {
            QOpenGLFramebufferObjectFormat fboFormat;
            fboFormat.setSamples( m_data->numSamples );
            fboFormat.setAttachment( QOpenGLFramebufferObject::CombinedDepthStencil );

            m_data->fbo = new QOpenGLFramebufferObject( fboSize, fboFormat );
            m_data->fboDirty = true;
        }

        if ( m_data->fboDirty )
        {
            m_data->fbo->bind();

            QOpenGLPaintDevice pd( fboSize );

            QPainter fboPainter( &pd );
            fboPainter.scale( pixelRatio, pixelRatio );
            draw( &fboPainter);
            fboPainter.end();

            m_data->fboDirty = false;
        }

        QOpenGLFramebufferObject::blitFramebuffer( NULL, m_data->fbo );
    }
    else
    {
        painter.begin( this );
        draw( &painter );
    }

    if ( hasFocusIndicator )
        drawFocusIndicator( &painter );
}

void QwtPlotOpenGLCanvas::resizeGL( int, int )
{
    // nothing to do
}

#if QWT_MOC_INCLUDE
#include "moc_qwt_plot_opengl_canvas.cpp"
#endif
