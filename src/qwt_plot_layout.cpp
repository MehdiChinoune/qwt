/******************************************************************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "qwt_plot_layout.h"
#include "qwt_text.h"
#include "qwt_text_label.h"
#include "qwt_scale_widget.h"
#include "qwt_abstract_legend.h"
#include "qwt_math.h"

namespace
{
    class LayoutData
    {
      public:
        struct LegendData
        {
            void init( const QwtAbstractLegend* legend )
            {
                if ( legend )
                {
                    frameWidth = legend->frameWidth();
                    hScrollExtent = legend->scrollExtent( Qt::Horizontal );
                    vScrollExtent = legend->scrollExtent( Qt::Vertical );

                    hint = legend->sizeHint();
                }
            }

            QSize legendHint( const QwtAbstractLegend* legend, const QRectF& rect ) const
            {
                const int w = qMin( hint.width(), qwtFloor( rect.width() ) );

                int h = legend->heightForWidth( w );
                if ( h <= 0 )
                    h = hint.height();

                return QSize( w, h );
            }

            int frameWidth;
            int hScrollExtent;
            int vScrollExtent;
            QSize hint;
        };

        struct LabelData
        {
            void init( const QwtTextLabel* label )
            {
                frameWidth = 0;
                text = QwtText();

                if ( label )
                {
                    text = label->text();
                    if ( !( text.testPaintAttribute( QwtText::PaintUsingTextFont ) ) )
                        text.setFont( label->font() );

                    frameWidth = label->frameWidth();
                }
            }

            QwtText text;
            int frameWidth;
        };

        struct ScaleData
        {
            bool isVisible;
            const QwtScaleWidget* scaleWidget;
            QFont scaleFont;
            int start;
            int end;
            int baseLineOffset;
            double tickOffset;
            int dimWithoutTitle;
        };

        struct CanvasData
        {
            int contentsMargins[ QwtAxis::AxisCount ];
        };

      public:
        enum Label
        {
            Title,
            Footer,

            NumLabels
        };

        void init( const QwtPlot*, const QRectF& rect );

        inline ScaleData& axisData( QwtAxisId axisId )
        {
            return scaleData[ axisId ];
        }

        inline const ScaleData& axisData( QwtAxisId axisId ) const
        {
            return scaleData[ axisId ];
        }

        LegendData legendData;
        LabelData labelData[ NumLabels ];
        ScaleData scaleData[ QwtAxis::AxisCount ];
        CanvasData canvasData;
    };

    /*
       Extract all layout relevant data from the plot components
     */
    void LayoutData::init( const QwtPlot* plot, const QRectF& rect )
    {
        if ( plot->legend() )
        {
            legendData.init( plot->legend() );
            legendData.hint = legendData.legendHint( plot->legend(), rect );
        }

        labelData[ Title ].init( plot->titleLabel() );
        labelData[ Footer ].init( plot->footerLabel() );

        for ( int axisPos = 0; axisPos < QwtAxis::AxisCount; axisPos++ )
        {
            {
                const QwtAxisId axisId( axisPos );

                ScaleData& scaleData = axisData( axisId );

                if ( plot->isAxisVisible( axisId ) )
                {
                    const QwtScaleWidget* scaleWidget = plot->axisWidget( axisId );

                    scaleData.isVisible = true;

                    scaleData.scaleWidget = scaleWidget;

                    scaleData.scaleFont = scaleWidget->font();

                    scaleData.start = scaleWidget->startBorderDist();
                    scaleData.end = scaleWidget->endBorderDist();

                    scaleData.baseLineOffset = scaleWidget->margin();
                    scaleData.tickOffset = scaleWidget->margin();

                    if ( scaleWidget->scaleDraw()->hasComponent(
                        QwtAbstractScaleDraw::Ticks ) )
                    {
                        scaleData.tickOffset +=
                            scaleWidget->scaleDraw()->maxTickLength();
                    }

                    scaleData.dimWithoutTitle = scaleWidget->dimForLength(
                        QWIDGETSIZE_MAX, scaleData.scaleFont );

                    if ( !scaleWidget->title().isEmpty() )
                    {
                        scaleData.dimWithoutTitle -=
                            scaleWidget->titleHeightForWidth( QWIDGETSIZE_MAX );
                    }
                }
                else
                {
                    scaleData.isVisible = false;
                    scaleData.start = 0;
                    scaleData.end = 0;
                    scaleData.baseLineOffset = 0;
                    scaleData.tickOffset = 0.0;
                    scaleData.dimWithoutTitle = 0;
                }
            }
        }

        // canvas

        const QMargins m = plot->canvas()->contentsMargins();

        canvasData.contentsMargins[ QwtAxis::YLeft ] = m.left();
        canvasData.contentsMargins[ QwtAxis::XTop ] = m.top();
        canvasData.contentsMargins[ QwtAxis::YRight ] = m.right();
        canvasData.contentsMargins[ QwtAxis::XBottom ] = m.bottom();
    }
}

namespace
{
    class LayoutEngine
    {
      public:
        LayoutEngine()
            : m_legendPos( QwtPlot::BottomLegend )
            , m_legendRatio( 1.0 )
            , m_spacing( 5 )
        {
        }

        QRectF layoutLegend( QwtPlotLayout::Options,
            const LayoutData::LegendData&, const QRectF& ) const;

        QRectF alignLegend( const QSize& legendHint,
            const QRectF& canvasRect, const QRectF& legendRect ) const;

        void alignScales( QwtPlotLayout::Options,
            const LayoutData&, QRectF& canvasRect,
            QRectF scaleRect[QwtAxis::AxisCount] ) const;

        void layoutDimensions( QwtPlotLayout::Options, 
            const LayoutData&, const QRectF&, int& dimTitle,
            int& dimFooter, int dimAxis[QwtAxis::AxisCount] ) const;

        inline void setSpacing( unsigned int spacing ) { m_spacing = spacing; }
        inline unsigned int spacing() const { return m_spacing; }

        inline void setAlignCanvas( int axisPos, bool on ) { m_alignCanvas[ axisPos ] = on; }
        inline bool alignCanvas( int axisPos ) const { return m_alignCanvas[ axisPos ]; }

        inline void setCanvasMargin( int axisPos, int margin ) { m_canvasMargin[ axisPos ] = margin; }
        inline int canvasMargin( int axisPos ) const { return m_canvasMargin[ axisPos ]; }

        inline void setLegendPos( QwtPlot::LegendPosition pos ) { m_legendPos = pos; }
        inline QwtPlot::LegendPosition legendPos() const { return m_legendPos; }

        inline void setLegendRatio( double ratio ) { m_legendRatio = ratio; }
        inline double legendRatio() const { return m_legendRatio; }

      private:
        QwtPlot::LegendPosition m_legendPos;
        double m_legendRatio;

        unsigned int m_canvasMargin[QwtAxis::AxisCount];
        bool m_alignCanvas[QwtAxis::AxisCount];

        unsigned int m_spacing;
    };
}

QRectF LayoutEngine::layoutLegend( QwtPlotLayout::Options options,
    const LayoutData::LegendData& legendData, const QRectF& rect ) const
{
    const QSize legendHint( legendData.hint );

    int dim;
    if ( m_legendPos == QwtPlot::LeftLegend
        || m_legendPos == QwtPlot::RightLegend )
    {
        // We don't allow vertical legends to take more than
        // half of the available space.

        dim = qMin( legendHint.width(), int( rect.width() * m_legendRatio ) );

        if ( !( options & QwtPlotLayout::IgnoreScrollbars ) )
        {
            if ( legendHint.height() > rect.height() )
            {
                // The legend will need additional
                // space for the vertical scrollbar.

                dim += legendData.hScrollExtent;
            }
        }
    }
    else
    {
        dim = qMin( legendHint.height(), int( rect.height() * m_legendRatio ) );
        dim = qMax( dim, legendData.vScrollExtent );
    }

    QRectF legendRect = rect;
    switch ( m_legendPos )
    {
        case QwtPlot::LeftLegend:
        {
            legendRect.setWidth( dim );
            break;
        }
        case QwtPlot::RightLegend:
        {
            legendRect.setX( rect.right() - dim );
            legendRect.setWidth( dim );
            break;
        }
        case QwtPlot::TopLegend:
        {
            legendRect.setHeight( dim );
            break;
        }
        case QwtPlot::BottomLegend:
        {
            legendRect.setY( rect.bottom() - dim );
            legendRect.setHeight( dim );
            break;
        }
    }

    return legendRect;
}

QRectF LayoutEngine::alignLegend( const QSize& legendHint,
    const QRectF& canvasRect, const QRectF& legendRect ) const
{
    QRectF alignedRect = legendRect;

    if ( m_legendPos == QwtPlot::BottomLegend
        || m_legendPos == QwtPlot::TopLegend )
    {
        if ( legendHint.width() < canvasRect.width() )
        {
            alignedRect.setX( canvasRect.x() );
            alignedRect.setWidth( canvasRect.width() );
        }
    }
    else
    {
        if ( legendHint.height() < canvasRect.height() )
        {
            alignedRect.setY( canvasRect.y() );
            alignedRect.setHeight( canvasRect.height() );
        }
    }

    return alignedRect;
}

void LayoutEngine::layoutDimensions( QwtPlotLayout::Options options, 
    const LayoutData& layoutData, const QRectF& rect, int& dimTitle,
    int& dimFooter, int dimAxis[QwtAxis::AxisCount] ) const
{
    using namespace QwtAxis;

    dimTitle = dimFooter = 0;
    for ( int axis = 0; axis < AxisCount; axis++ )
        dimAxis[axis] = 0;

    int backboneOffset[AxisCount];
    for ( int axisPos = 0; axisPos < AxisCount; axisPos++ )
    {
        backboneOffset[axisPos] = 0;
        if ( !( options & QwtPlotLayout::IgnoreFrames ) )
            backboneOffset[axisPos] += layoutData.canvasData.contentsMargins[axisPos];

        if ( !m_alignCanvas[axisPos] )
            backboneOffset[axisPos] += m_canvasMargin[axisPos];
    }

    bool done = false;
    while ( !done )
    {
        done = true;

        // the size for the 4 axis depend on each other. Expanding
        // the height of a horizontal axis will shrink the height
        // for the vertical axis, shrinking the height of a vertical
        // axis will result in a line break what will expand the
        // width and results in shrinking the width of a horizontal
        // axis what might result in a line break of a horizontal
        // axis ... . So we loop as long until no size changes.

        const LayoutData::LabelData& titleData =
            layoutData.labelData[ LayoutData::Title ];

        if ( !( ( options & QwtPlotLayout::IgnoreTitle ) || titleData.text.isEmpty() ) )
        {
            double w = rect.width();

            if ( layoutData.scaleData[YLeft].isVisible
                != layoutData.scaleData[YRight].isVisible )
            {
                // center to the canvas
                w -= dimAxis[YLeft] + dimAxis[YRight];
            }

            int d = qwtCeil( titleData.text.heightForWidth( w ) );
            if ( !( options & QwtPlotLayout::IgnoreFrames ) )
                d += 2 * titleData.frameWidth;

            if ( d > dimTitle )
            {
                dimTitle = d;
                done = false;
            }
        }

        const LayoutData::LabelData& footerData =
            layoutData.labelData[ LayoutData::Footer ];

        if ( !( ( options & QwtPlotLayout::IgnoreFooter ) || footerData.text.isEmpty() ) )
        {
            double w = rect.width();

            if ( layoutData.scaleData[YLeft].isVisible
                != layoutData.scaleData[YRight].isVisible )
            {
                // center to the canvas
                w -= dimAxis[YLeft] + dimAxis[YRight];
            }

            int d = qwtCeil( footerData.text.heightForWidth( w ) );
            if ( !( options & QwtPlotLayout::IgnoreFrames ) )
                d += 2 * footerData.frameWidth;

            if ( d > dimFooter )
            {
                dimFooter = d;
                done = false;
            }
        }

        for ( int axisPos = 0; axisPos < AxisCount; axisPos++ )
        {
            {
                const QwtAxisId axisId( axisPos );

                const LayoutData::ScaleData& scaleData = layoutData.axisData( axisId );

                if ( scaleData.isVisible )
                {
                    double length;
                    if ( isXAxis( axisPos ) )
                    {
                        length = rect.width() - dimAxis[YLeft] - dimAxis[YRight];
                        length -= scaleData.start + scaleData.end;

                        if ( dimAxis[YRight] > 0 )
                            length -= 1;

                        length += qMin( dimAxis[YLeft],
                            scaleData.start - backboneOffset[YLeft] );
                        length += qMin( dimAxis[YRight],
                            scaleData.end - backboneOffset[YRight] );
                    }
                    else // y axis
                    {
                        length = rect.height() - dimAxis[XTop] - dimAxis[XBottom];
                        length -= scaleData.start + scaleData.end;
                        length -= 1;

                        if ( dimAxis[XBottom] <= 0 )
                            length -= 1;

                        if ( dimAxis[XTop] <= 0 )
                            length -= 1;

                        /*
                           The tick labels of the y axes are always left/right from the
                           backbone/ticks of the x axes - but we have to take care,
                           that the labels don't overlap.
                         */
                        if ( dimAxis[XBottom] > 0 )
                        {
                            length += qMin(
                                layoutData.scaleData[XBottom].tickOffset,
                                double( scaleData.start - backboneOffset[XBottom] ) );
                        }

                        if ( dimAxis[XTop] > 0 )
                        {
                            length += qMin(
                                layoutData.scaleData[XTop].tickOffset,
                                double( scaleData.end - backboneOffset[XTop] ) );
                        }

                        if ( dimTitle > 0 )
                            length -= dimTitle + m_spacing;
                    }

                    int d = scaleData.dimWithoutTitle;
                    if ( !scaleData.scaleWidget->title().isEmpty() )
                    {
                        d += scaleData.scaleWidget->titleHeightForWidth( qwtFloor( length ) );
                    }


                    if ( d > dimAxis[axisId] )
                    {
                        dimAxis[axisId] = d;
                        done = false;
                    }
                }
            }
        }
    }
}

void LayoutEngine::alignScales( QwtPlotLayout::Options options,
    const LayoutData& layoutData, QRectF& canvasRect,
    QRectF scaleRect[QwtAxis::AxisCount] ) const
{
    using namespace QwtAxis;

    int backboneOffset[AxisCount];
    for ( int axisPos = 0; axisPos < AxisCount; axisPos++ )
    {
        backboneOffset[axisPos] = 0;

        if ( !m_alignCanvas[axisPos] )
        {
            backboneOffset[axisPos] += m_canvasMargin[axisPos];
        }

        if ( !( options & QwtPlotLayout::IgnoreFrames ) )
        {
            backboneOffset[axisPos] +=
                layoutData.canvasData.contentsMargins[axisPos];
        }
    }

    for ( int axis = 0; axis < AxisCount; axis++ )
    {
        if ( !scaleRect[axis].isValid() )
            continue;

        const int startDist = layoutData.scaleData[axis].start;
        const int endDist = layoutData.scaleData[axis].end;

        QRectF& axisRect = scaleRect[axis];

        if ( isXAxis( axis ) )
        {
            const QRectF& leftScaleRect = scaleRect[YLeft];
            const int leftOffset = backboneOffset[YLeft] - startDist;

            if ( leftScaleRect.isValid() )
            {
                const double dx = leftOffset + leftScaleRect.width();
                if ( m_alignCanvas[YLeft] && dx < 0.0 )
                {
                    /*
                       The axis needs more space than the width
                       of the left scale.
                     */
                    const double cLeft = canvasRect.left(); // qreal -> double
                    canvasRect.setLeft( qwtMaxF( cLeft, axisRect.left() - dx ) );
                }
                else
                {
                    const double minLeft = leftScaleRect.left();
                    const double left = axisRect.left() + leftOffset;
                    axisRect.setLeft( qwtMaxF( left, minLeft ) );
                }
            }
            else
            {
                if ( m_alignCanvas[YLeft] && leftOffset < 0 )
                {
                    canvasRect.setLeft( qwtMaxF( canvasRect.left(),
                        axisRect.left() - leftOffset ) );
                }
                else
                {
                    if ( leftOffset > 0 )
                        axisRect.setLeft( axisRect.left() + leftOffset );
                }
            }

            const QRectF& rightScaleRect = scaleRect[YRight];
            const int rightOffset = backboneOffset[YRight] - endDist + 1;

            if ( rightScaleRect.isValid() )
            {
                const double dx = rightOffset + rightScaleRect.width();
                if ( m_alignCanvas[YRight] && dx < 0 )
                {
                    /*
                       The axis needs more space than the width
                       of the right scale.
                     */
                    const double cRight = canvasRect.right(); // qreal -> double
                    canvasRect.setRight( qwtMinF( cRight, axisRect.right() + dx ) );
                }

                const double maxRight = rightScaleRect.right();
                const double right = axisRect.right() - rightOffset;
                axisRect.setRight( qwtMinF( right, maxRight ) );
            }
            else
            {
                if ( m_alignCanvas[YRight] && rightOffset < 0 )
                {
                    canvasRect.setRight( qwtMinF( canvasRect.right(),
                        axisRect.right() + rightOffset ) );
                }
                else
                {
                    if ( rightOffset > 0 )
                        axisRect.setRight( axisRect.right() - rightOffset );
                }
            }
        }
        else // YLeft, YRight
        {
            const QRectF& bottomScaleRect = scaleRect[XBottom];
            const int bottomOffset = backboneOffset[XBottom] - endDist + 1;

            if ( bottomScaleRect.isValid() )
            {
                const double dy = bottomOffset + bottomScaleRect.height();
                if ( m_alignCanvas[XBottom] && dy < 0 )
                {
                    /*
                       The axis needs more space than the height
                       of the bottom scale.
                     */
                    const double cBottom = canvasRect.bottom(); // qreal -> double
                    canvasRect.setBottom( qwtMinF( cBottom, axisRect.bottom() + dy ) );
                }
                else
                {
                    const double maxBottom = bottomScaleRect.top() +
                        layoutData.scaleData[XBottom].tickOffset;
                    const double bottom = axisRect.bottom() - bottomOffset;
                    axisRect.setBottom( qwtMinF( bottom, maxBottom ) );
                }
            }
            else
            {
                if ( m_alignCanvas[XBottom] && bottomOffset < 0 )
                {
                    canvasRect.setBottom( qwtMinF( canvasRect.bottom(),
                        axisRect.bottom() + bottomOffset ) );
                }
                else
                {
                    if ( bottomOffset > 0 )
                        axisRect.setBottom( axisRect.bottom() - bottomOffset );
                }
            }

            const QRectF& topScaleRect = scaleRect[XTop];
            const int topOffset = backboneOffset[XTop] - startDist;

            if ( topScaleRect.isValid() )
            {
                const double dy = topOffset + topScaleRect.height();
                if ( m_alignCanvas[XTop] && dy < 0 )
                {
                    /*
                       The axis needs more space than the height
                       of the top scale.
                     */
                    const double cTop = canvasRect.top(); // qreal -> double
                    canvasRect.setTop( qwtMaxF( cTop, axisRect.top() - dy ) );
                }
                else
                {
                    const double minTop = topScaleRect.bottom() -
                        layoutData.scaleData[XTop].tickOffset;

                    const double top = axisRect.top() + topOffset;
                    axisRect.setTop( qwtMaxF( top, minTop ) );
                }
            }
            else
            {
                if ( m_alignCanvas[XTop] && topOffset < 0 )
                {
                    canvasRect.setTop( qwtMaxF( canvasRect.top(),
                        axisRect.top() - topOffset ) );
                }
                else
                {
                    if ( topOffset > 0 )
                        axisRect.setTop( axisRect.top() + topOffset );
                }
            }
        }
    }

    /*
       The canvas has been aligned to the scale with largest
       border distances. Now we have to realign the other scale.
     */

    for ( int axis = 0; axis < AxisCount; axis++ )
    {
        {
            QRectF& sRect = scaleRect[axis];

            if ( !sRect.isValid() )
                continue;

            if ( isXAxis( axis ) )
            {
                if ( m_alignCanvas[YLeft] )
                {
                    double y = canvasRect.left() - layoutData.scaleData[axis].start;
                    if ( !( options & QwtPlotLayout::IgnoreFrames ) )
                        y += layoutData.canvasData.contentsMargins[YLeft];

                    sRect.setLeft( y );
                }

                if ( m_alignCanvas[YRight] )
                {
                    double y = canvasRect.right() - 1 + layoutData.scaleData[axis].end;
                    if ( !( options & QwtPlotLayout::IgnoreFrames ) )
                        y -= layoutData.canvasData.contentsMargins[YRight];

                    sRect.setRight( y );
                }

                if ( m_alignCanvas[axis] )
                {
                    if ( axis == XTop )
                        sRect.setBottom( canvasRect.top() );
                    else
                        sRect.setTop( canvasRect.bottom() );
                }
            }
            else
            {
                if ( m_alignCanvas[XTop] )
                {
                    double x = canvasRect.top() - layoutData.scaleData[axis].start;
                    if ( !( options & QwtPlotLayout::IgnoreFrames ) )
                        x += layoutData.canvasData.contentsMargins[XTop];

                    sRect.setTop( x );
                }

                if ( m_alignCanvas[XBottom] )
                {
                    double x = canvasRect.bottom() - 1 + layoutData.scaleData[axis].end;
                    if ( !( options & QwtPlotLayout::IgnoreFrames ) )
                        x -= layoutData.canvasData.contentsMargins[XBottom];

                    sRect.setBottom( x );
                }

                if ( m_alignCanvas[axis] )
                {
                    if ( axis == YLeft )
                        sRect.setRight( canvasRect.left() );
                    else
                        sRect.setLeft( canvasRect.right() );
                }
            }
        }
    }
}

// === PrivateData

class QwtPlotLayout::PrivateData
{
  public:
    QRectF titleRect;
    QRectF footerRect;
    QRectF legendRect;
    QRectF scaleRects[QwtAxis::AxisCount];
    QRectF canvasRect;

    LayoutEngine engine;
    LayoutData layoutData;
};

/*!
   \brief Constructor
 */

QwtPlotLayout::QwtPlotLayout()
{
    m_data = new PrivateData;

    setLegendPosition( QwtPlot::BottomLegend );
    setCanvasMargin( 4 );
    setAlignCanvasToScales( false );

    invalidate();
}

//! Destructor
QwtPlotLayout::~QwtPlotLayout()
{
    delete m_data;
}

/*!
   Change a margin of the canvas. The margin is the space
   above/below the scale ticks. A negative margin will
   be set to -1, excluding the borders of the scales.

   \param margin New margin
   \param axisPos One of QwtAxis::Position. Specifies where the position of the margin.
              -1 means margin at all borders.
   \sa canvasMargin()

   \warning The margin will have no effect when alignCanvasToScale() is true
 */

void QwtPlotLayout::setCanvasMargin( int margin, int axisPos )
{
    if ( margin < -1 )
        margin = -1;

    LayoutEngine& engine = m_data->engine;

    if ( axisPos == -1 )
    {
        for ( axisPos = 0; axisPos < QwtAxis::AxisCount; axisPos++ )
            engine.setCanvasMargin( axisPos, margin );
    }
    else if ( QwtAxis::isValid( axisPos ) )
    {
        engine.setCanvasMargin( axisPos, margin );
    }
}

/*!
    \param axisPos Axis position
    \return Margin around the scale tick borders
    \sa setCanvasMargin()
 */
int QwtPlotLayout::canvasMargin( int axisPos ) const
{
    if ( !QwtAxis::isValid( axisPos ) )
        return 0;

    return m_data->engine.canvasMargin( axisPos );
}

/*!
   \brief Set the align-canvas-to-axis-scales flag for all axes

   \param on True/False
   \sa setAlignCanvasToScale(), alignCanvasToScale()
 */
void QwtPlotLayout::setAlignCanvasToScales( bool on )
{
    for ( int axisPos = 0; axisPos < QwtAxis::AxisCount; axisPos++ )
        m_data->engine.setAlignCanvas( axisPos, on );
}

/*!
   Change the align-canvas-to-axis-scales setting. The canvas may:

   - extend beyond the axis scale ends to maximize its size,
   - align with the axis scale ends to control its size.

   The axisId parameter is somehow confusing as it identifies a border
   of the plot and not the axes, that are aligned. F.e when QwtAxis::YLeft
   is set, the left end of the the x-axes ( QwtAxis::XTop, QwtAxis::XBottom )
   is aligned.

   \param axisId Axis index
   \param on New align-canvas-to-axis-scales setting

   \sa setCanvasMargin(), alignCanvasToScale(), setAlignCanvasToScales()
   \warning In case of on == true canvasMargin() will have no effect
 */
void QwtPlotLayout::setAlignCanvasToScale( int axisPos, bool on )
{
    if ( QwtAxis::isValid( axisPos ) )
        m_data->engine.setAlignCanvas( axisPos, on );
}

/*!
   Return the align-canvas-to-axis-scales setting. The canvas may:
   - extend beyond the axis scale ends to maximize its size
   - align with the axis scale ends to control its size.

   \param axisPos Axis position
   \return align-canvas-to-axis-scales setting
   \sa setAlignCanvasToScale(), setAlignCanvasToScale(), setCanvasMargin()
 */
bool QwtPlotLayout::alignCanvasToScale( int axisPos ) const
{
    if ( !QwtAxis::isValid( axisPos ) )
        return false;

    return m_data->engine.alignCanvas( axisPos );
}

/*!
   Change the spacing of the plot. The spacing is the distance
   between the plot components.

   \param spacing New spacing
   \sa setCanvasMargin(), spacing()
 */
void QwtPlotLayout::setSpacing( int spacing )
{
    m_data->engine.setSpacing( qMax( 0, spacing ) );
}

/*!
   \return Spacing
   \sa margin(), setSpacing()
 */
int QwtPlotLayout::spacing() const
{
    return m_data->engine.spacing();
}

/*!
   \brief Specify the position of the legend
   \param pos The legend's position.
   \param ratio Ratio between legend and the bounding rectangle
               of title, footer, canvas and axes. The legend will be shrunk
               if it would need more space than the given ratio.
               The ratio is limited to ]0.0 .. 1.0]. In case of <= 0.0
               it will be reset to the default ratio.
               The default vertical/horizontal ratio is 0.33/0.5.

   \sa QwtPlot::setLegendPosition()
 */

void QwtPlotLayout::setLegendPosition( QwtPlot::LegendPosition pos, double ratio )
{
    if ( ratio > 1.0 )
        ratio = 1.0;

    LayoutEngine& engine = m_data->engine;

    switch ( pos )
    {
        case QwtPlot::TopLegend:
        case QwtPlot::BottomLegend:
        {
            if ( ratio <= 0.0 )
                ratio = 0.33;

            engine.setLegendRatio( ratio );
            engine.setLegendPos( pos );

            break;
        }
        case QwtPlot::LeftLegend:
        case QwtPlot::RightLegend:
        {
            if ( ratio <= 0.0 )
                ratio = 0.5;

            engine.setLegendRatio( ratio );
            engine.setLegendPos( pos );

            break;
        }
        default:
            break;
    }
}

/*!
   \brief Specify the position of the legend
   \param pos The legend's position. Valid values are
      \c QwtPlot::LeftLegend, \c QwtPlot::RightLegend,
      \c QwtPlot::TopLegend, \c QwtPlot::BottomLegend.

   \sa QwtPlot::setLegendPosition()
 */
void QwtPlotLayout::setLegendPosition( QwtPlot::LegendPosition pos )
{
    setLegendPosition( pos, 0.0 );
}

/*!
   \return Position of the legend
   \sa setLegendPosition(), QwtPlot::setLegendPosition(),
      QwtPlot::legendPosition()
 */
QwtPlot::LegendPosition QwtPlotLayout::legendPosition() const
{
    return m_data->engine.legendPos();
}

/*!
   Specify the relative size of the legend in the plot
   \param ratio Ratio between legend and the bounding rectangle
               of title, footer, canvas and axes. The legend will be shrunk
               if it would need more space than the given ratio.
               The ratio is limited to ]0.0 .. 1.0]. In case of <= 0.0
               it will be reset to the default ratio.
               The default vertical/horizontal ratio is 0.33/0.5.
 */
void QwtPlotLayout::setLegendRatio( double ratio )
{
    setLegendPosition( legendPosition(), ratio );
}

/*!
   \return The relative size of the legend in the plot.
   \sa setLegendPosition()
 */
double QwtPlotLayout::legendRatio() const
{
    return m_data->engine.legendRatio();
}

/*!
   \brief Set the geometry for the title

   This method is intended to be used from derived layouts
   overloading activate()

   \sa titleRect(), activate()
 */
void QwtPlotLayout::setTitleRect( const QRectF& rect )
{
    m_data->titleRect = rect;
}

/*!
   \return Geometry for the title
   \sa activate(), invalidate()
 */
QRectF QwtPlotLayout::titleRect() const
{
    return m_data->titleRect;
}

/*!
   \brief Set the geometry for the footer

   This method is intended to be used from derived layouts
   overloading activate()

   \sa footerRect(), activate()
 */
void QwtPlotLayout::setFooterRect( const QRectF& rect )
{
    m_data->footerRect = rect;
}

/*!
   \return Geometry for the footer
   \sa activate(), invalidate()
 */
QRectF QwtPlotLayout::footerRect() const
{
    return m_data->footerRect;
}

/*!
   \brief Set the geometry for the legend

   This method is intended to be used from derived layouts
   overloading activate()

   \param rect Rectangle for the legend

   \sa legendRect(), activate()
 */
void QwtPlotLayout::setLegendRect( const QRectF& rect )
{
    m_data->legendRect = rect;
}

/*!
   \return Geometry for the legend
   \sa activate(), invalidate()
 */
QRectF QwtPlotLayout::legendRect() const
{
    return m_data->legendRect;
}

/*!
   \brief Set the geometry for an axis

   This method is intended to be used from derived layouts
   overloading activate()

   \param axisId Axis
   \param rect Rectangle for the scale

   \sa scaleRect(), activate()
 */
void QwtPlotLayout::setScaleRect( QwtAxisId axisId, const QRectF& rect )
{
    if ( QwtAxis::isValid( axisId ) )
        m_data->scaleRects[axisId] = rect;
}

/*!
   \param axisId Axis
   \return Geometry for the scale
   \sa activate(), invalidate()
 */
QRectF QwtPlotLayout::scaleRect( QwtAxisId axisId ) const
{
    if ( QwtAxis::isValid( axisId ) )
        return m_data->scaleRects[axisId];

    return QRectF();
}

/*!
   \brief Set the geometry for the canvas

   This method is intended to be used from derived layouts
   overloading activate()

   \sa canvasRect(), activate()
 */
void QwtPlotLayout::setCanvasRect( const QRectF& rect )
{
    m_data->canvasRect = rect;
}

/*!
   \return Geometry for the canvas
   \sa activate(), invalidate()
 */
QRectF QwtPlotLayout::canvasRect() const
{
    return m_data->canvasRect;
}

/*!
   Invalidate the geometry of all components.
   \sa activate()
 */
void QwtPlotLayout::invalidate()
{
    m_data->titleRect = m_data->footerRect =
        m_data->legendRect = m_data->canvasRect = QRectF();

    for ( int axisPos = 0; axisPos < QwtAxis::AxisCount; axisPos++ )
        m_data->scaleRects[axisPos] = QRect();
}

/*!
   \return Minimum size hint
   \param plot Plot widget

   \sa QwtPlot::minimumSizeHint()
 */
QSize QwtPlotLayout::minimumSizeHint( const QwtPlot* plot ) const
{
    using namespace QwtAxis;

    class ScaleData
    {
      public:
        ScaleData()
        {
            w = h = minLeft = minRight = tickOffset = 0;
        }

        int w;
        int h;
        int minLeft;
        int minRight;
        int tickOffset;
    } scaleData[AxisCount];

    int canvasBorder[AxisCount];

    const int fw = plot->canvas()->contentsMargins().left();

    int axis;
    for ( axis = 0; axis < AxisCount; axis++ )
    {
        if ( plot->isAxisVisible( axis ) )
        {
            const QwtScaleWidget* scl = plot->axisWidget( axis );
            ScaleData& sd = scaleData[axis];

            const QSize hint = scl->minimumSizeHint();
            sd.w = hint.width();
            sd.h = hint.height();
            scl->getBorderDistHint( sd.minLeft, sd.minRight );
            sd.tickOffset = scl->margin();
            if ( scl->scaleDraw()->hasComponent( QwtAbstractScaleDraw::Ticks ) )
                sd.tickOffset += qwtCeil( scl->scaleDraw()->maxTickLength() );
        }

        canvasBorder[axis] = fw + m_data->engine.canvasMargin( axis ) + 1;
    }

    for ( axis = 0; axis < AxisCount; axis++ )
    {
        ScaleData& sd = scaleData[axis];
        if ( sd.w && isXAxis( axis ) )
        {
            if ( ( sd.minLeft > canvasBorder[YLeft] ) && scaleData[YLeft].w )
            {
                int shiftLeft = sd.minLeft - canvasBorder[YLeft];
                if ( shiftLeft > scaleData[YLeft].w )
                    shiftLeft = scaleData[YLeft].w;

                sd.w -= shiftLeft;
            }

            if ( ( sd.minRight > canvasBorder[YRight] ) && scaleData[YRight].w )
            {
                int shiftRight = sd.minRight - canvasBorder[YRight];
                if ( shiftRight > scaleData[YRight].w )
                    shiftRight = scaleData[YRight].w;

                sd.w -= shiftRight;
            }
        }

        if ( sd.h && ( isYAxis( axis ) ) )
        {
            if ( ( sd.minLeft > canvasBorder[XBottom] ) && scaleData[XBottom].h )
            {
                int shiftBottom = sd.minLeft - canvasBorder[XBottom];
                if ( shiftBottom > scaleData[XBottom].tickOffset )
                    shiftBottom = scaleData[XBottom].tickOffset;

                sd.h -= shiftBottom;
            }

            if ( ( sd.minLeft > canvasBorder[XTop] ) && scaleData[XTop].h )
            {
                int shiftTop = sd.minRight - canvasBorder[XTop];
                if ( shiftTop > scaleData[XTop].tickOffset )
                    shiftTop = scaleData[XTop].tickOffset;

                sd.h -= shiftTop;
            }
        }
    }

    const QWidget* canvas = plot->canvas();

    const QMargins m = canvas->contentsMargins();

    const QSize minCanvasSize = canvas->minimumSize();

    int w = scaleData[YLeft].w + scaleData[YRight].w;
    int cw = qMax( scaleData[XBottom].w, scaleData[XTop].w )
        + m.left() + 1 + m.right() + 1;
    w += qMax( cw, minCanvasSize.width() );

    int h = scaleData[XBottom].h + scaleData[XTop].h;
    int ch = qMax( scaleData[YLeft].h, scaleData[YRight].h )
        + m.top() + 1 + m.bottom() + 1;
    h += qMax( ch, minCanvasSize.height() );

    const QwtTextLabel* labels[2];
    labels[0] = plot->titleLabel();
    labels[1] = plot->footerLabel();

    for ( int i = 0; i < 2; i++ )
    {
        const QwtTextLabel* label = labels[i];
        if ( label && !label->text().isEmpty() )
        {
            // we center on the plot canvas.
            const bool centerOnCanvas = !( plot->isAxisVisible( YLeft )
                && plot->isAxisVisible( YRight ) );

            int labelW = w;
            if ( centerOnCanvas )
            {
                labelW -= scaleData[YLeft].w + scaleData[YRight].w;
            }

            int labelH = label->heightForWidth( labelW );
            if ( labelH > labelW ) // Compensate for a long title
            {
                w = labelW = labelH;
                if ( centerOnCanvas )
                    w += scaleData[YLeft].w + scaleData[YRight].w;

                labelH = label->heightForWidth( labelW );
            }
            h += labelH + spacing();
        }
    }

    // Compute the legend contribution

    const QwtAbstractLegend* legend = plot->legend();
    if ( legend && !legend->isEmpty() )
    {
        const LayoutEngine& engine = m_data->engine;

        if ( engine.legendPos() == QwtPlot::LeftLegend
            || engine.legendPos() == QwtPlot::RightLegend )
        {
            int legendW = legend->sizeHint().width();
            int legendH = legend->heightForWidth( legendW );

            if ( legend->frameWidth() > 0 )
                w += spacing();

            if ( legendH > h )
                legendW += legend->scrollExtent( Qt::Horizontal );

            if ( engine.legendRatio() < 1.0 )
                legendW = qMin( legendW, int( w / ( 1.0 - engine.legendRatio() ) ) );

            w += legendW + spacing();
        }
        else
        {
            int legendW = qMin( legend->sizeHint().width(), w );
            int legendH = legend->heightForWidth( legendW );

            if ( legend->frameWidth() > 0 )
                h += spacing();

            if ( engine.legendRatio() < 1.0 )
                legendH = qMin( legendH, int( h / ( 1.0 - engine.legendRatio() ) ) );

            h += legendH + spacing();
        }
    }

    return QSize( w, h );
}

/*!
   \brief Recalculate the geometry of all components.

   \param plot Plot to be layout
   \param plotRect Rectangle where to place the components
   \param options Layout options

   \sa invalidate(), titleRect(), footerRect()
      legendRect(), scaleRect(), canvasRect()
 */
void QwtPlotLayout::activate( const QwtPlot* plot,
    const QRectF& plotRect, Options options )
{
    invalidate();

    QRectF rect( plotRect );  // undistributed rest of the plot rect

    // We extract all layout relevant parameters from the widgets,
    // and save them to m_data->layoutData.

    m_data->layoutData.init( plot, rect );

    if ( !( options & IgnoreLegend )
        && plot->legend() && !plot->legend()->isEmpty() )
    {
        m_data->legendRect = m_data->engine.layoutLegend(
            options, m_data->layoutData.legendData, rect );

        // subtract m_data->legendRect from rect

        const QRegion region( rect.toRect() );
        rect = region.subtracted( m_data->legendRect.toRect() ).boundingRect();

        switch ( m_data->engine.legendPos() )
        {
            case QwtPlot::LeftLegend:
            {
                rect.setLeft( rect.left() + spacing() );
                break;
            }
            case QwtPlot::RightLegend:
            {
                rect.setRight( rect.right() - spacing() );
                break;
            }
            case QwtPlot::TopLegend:
            {
                rect.setTop( rect.top() + spacing() );
                break;
            }
            case QwtPlot::BottomLegend:
            {
                rect.setBottom( rect.bottom() - spacing() );
                break;
            }
        }
    }

    /*
     +---+-----------+---+
     |       Title       |
     +---+-----------+---+
     |   |   Axis    |   |
     +---+-----------+---+
     | A |           | A |
     | x |  Canvas   | x |
     | i |           | i |
     | s |           | s |
     +---+-----------+---+
     |   |   Axis    |   |
     +---+-----------+---+
     |      Footer       |
     +---+-----------+---+
     */

    // title, footer and axes include text labels. The height of each
    // label depends on its line breaks, that depend on the width
    // for the label. A line break in a horizontal text will reduce
    // the available width for vertical texts and vice versa.
    // layoutDimensions finds the height/width for title, footer and axes
    // including all line breaks.

    using namespace QwtAxis;

    int dimTitle, dimFooter, dimAxes[AxisCount];
    m_data->engine.layoutDimensions( options, m_data->layoutData,
        rect, dimTitle, dimFooter, dimAxes );

    if ( dimTitle > 0 )
    {
        m_data->titleRect.setRect(
            rect.left(), rect.top(), rect.width(), dimTitle );

        rect.setTop( m_data->titleRect.bottom() + spacing() );

        if ( m_data->layoutData.scaleData[YLeft].isVisible !=
            m_data->layoutData.scaleData[YRight].isVisible )
        {
            // if only one of the y axes is missing we align
            // the title centered to the canvas

            m_data->titleRect.setX( rect.left() + dimAxes[YLeft] );
            m_data->titleRect.setWidth( rect.width()
                - dimAxes[YLeft] - dimAxes[YRight] );
        }
    }

    if ( dimFooter > 0 )
    {
        m_data->footerRect.setRect(
            rect.left(), rect.bottom() - dimFooter, rect.width(), dimFooter );

        rect.setBottom( m_data->footerRect.top() - spacing() );

        if ( m_data->layoutData.scaleData[YLeft].isVisible !=
            m_data->layoutData.scaleData[YRight].isVisible )
        {
            // if only one of the y axes is missing we align
            // the footer centered to the canvas

            m_data->footerRect.setX( rect.left() + dimAxes[YLeft] );
            m_data->footerRect.setWidth( rect.width()
                - dimAxes[YLeft] - dimAxes[YRight] );
        }
    }

    m_data->canvasRect.setRect(
        rect.x() + dimAxes[YLeft],
        rect.y() + dimAxes[XTop],
        rect.width() - dimAxes[YRight] - dimAxes[YLeft],
        rect.height() - dimAxes[XBottom] - dimAxes[XTop] );

    for ( int axisPos = 0; axisPos < AxisCount; axisPos++ )
    {
        // set the rects for the axes

        {
            const QwtAxisId axis( axisPos );

            if ( dimAxes[axis] )
            {
                int dim = dimAxes[axis];
                QRectF& scaleRect = m_data->scaleRects[axis];

                scaleRect = m_data->canvasRect;
                switch ( axis )
                {
                    case YLeft:
                    {
                        scaleRect.setX( m_data->canvasRect.left() - dim );
                        scaleRect.setWidth( dim );
                        break;
                    }
                    case YRight:
                    {
                        scaleRect.setX( m_data->canvasRect.right() );
                        scaleRect.setWidth( dim );
                        break;
                    }
                    case XBottom:
                    {
                        scaleRect.setY( m_data->canvasRect.bottom() );
                        scaleRect.setHeight( dim );
                        break;
                    }
                    case XTop:
                    {
                        scaleRect.setY( m_data->canvasRect.top() - dim );
                        scaleRect.setHeight( dim );
                        break;
                    }
                }
                scaleRect = scaleRect.normalized();
            }
        }
    }

    // +---+-----------+---+
    // |  <-   Axis   ->   |
    // +-^-+-----------+-^-+
    // | | |           | | |
    // |   |           |   |
    // | A |           | A |
    // | x |  Canvas   | x |
    // | i |           | i |
    // | s |           | s |
    // |   |           |   |
    // | | |           | | |
    // +-V-+-----------+-V-+
    // |   <-  Axis   ->   |
    // +---+-----------+---+

    // The ticks of the axes - not the labels above - should
    // be aligned to the canvas. So we try to use the empty
    // corners to extend the axes, so that the label texts
    // left/right of the min/max ticks are moved into them.

    m_data->engine.alignScales( options, m_data->layoutData,
        m_data->canvasRect, m_data->scaleRects );

    if ( !m_data->legendRect.isEmpty() )
    {
        // We prefer to align the legend to the canvas - not to
        // the complete plot - if possible.

        m_data->legendRect = m_data->engine.alignLegend(
            m_data->layoutData.legendData.hint,
            m_data->canvasRect, m_data->legendRect );
    }
}
