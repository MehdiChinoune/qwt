/******************************************************************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "qwt_plot_vectorfield.h"
#include "qwt_vectorfield_symbol.h"
#include "qwt_scale_map.h"
#include "qwt_color_map.h"
#include "qwt_painter.h"
#include "qwt_text.h"
#include "qwt_graphic.h"
#include "qwt_math.h"

#include <qpainter.h>
#include <qpainterpath.h>
#include <qdebug.h>
#include <cstdlib>

#define DEBUG_RENDER 0

#if DEBUG_RENDER
#include <qelapsedtimer.h>
#endif


static inline double qwtVector2Radians( double vx, double vy )
{
    if ( vx == 0.0 )
        return ( vy >= 0 ) ? M_PI_2 : 3 * M_PI_2;

    return std::atan2( vy, vx );
}

static inline double qwtVector2Magnitude( double vx, double vy )
{
    return sqrt( vx * vx + vy * vy );
}

static QwtInterval qwtMagnitudeRange(
    const QwtSeriesData< QwtVectorFieldSample >* series )
{
    if ( series->size() == 0 )
        return QwtInterval( 0, 1 );

    const QwtVectorFieldSample s0 = series->sample( 0 );

    double min = s0.vx * s0.vx + s0.vy * s0.vy;
    double max = min;

    for ( uint i = 1; i < series->size(); i++ )
    {
        const QwtVectorFieldSample s = series->sample( i );
        const double l = s.vx * s.vx + s.vy * s.vy;

        if ( l < min )
            min = l;

        if ( l > max )
            max = l;
    }

    min = std::sqrt( min );
    max = std::sqrt( max );

    if ( max == min )
        max += 1.0;

    return QwtInterval( min, max );
}

static inline QTransform qwtSymbolTransformation(
    const QTransform& oldTransform, double x, double y,
    double vx, double vy, double magnitude )
{
    QTransform transform = oldTransform;

    if ( !transform.isIdentity() )
    {
        transform.translate( x, y );

        const double radians = qwtVector2Radians( vx, vy );
        transform.rotateRadians( radians );
    }
    else
    {
        /*
            When starting with no transformation ( f.e on screen )
            the matrix can be found without having to use
            trigonometric functions
         */

        qreal sin, cos;
        if ( magnitude == 0.0 )
        {
            // something
            sin = 1.0;
            cos = 0.0;
        }
        else
        {
            sin = vy / magnitude;
            cos = vx / magnitude;
        }

        transform.setMatrix( cos, sin, 0.0, -sin, cos, 0.0, x, y, 1.0 );
    }

    return transform;
}

namespace
{
    class FilterMatrix
    {
      public:
        class Entry
        {
          public:
            inline void addSample( double sx, double sy,
                double svx, double svy )
            {
                x += sx;
                y += sy;

                vx += svx;
                vy += svy;

                count++;
            }

            quint32 count;

            // screen positions -> float is good enough
            float x;
            float y;
            float vx;
            float vy;
        };

        FilterMatrix( const QRectF& dataRect,
            const QRectF& canvasRect, const QSizeF& cellSize )
        {
            d_dx = cellSize.width();
            d_dy = cellSize.height();

            d_x0 = dataRect.x();
            if ( d_x0 < canvasRect.x() )
                d_x0 += int( ( canvasRect.x() - d_x0 ) / d_dx ) * d_dx;

            d_y0 = dataRect.y();
            if ( d_y0 < canvasRect.y() )
                d_y0 += int( ( canvasRect.y() - d_y0 ) / d_dy ) * d_dy;

            d_numColumns = canvasRect.width() / d_dx + 1;
            d_numRows = canvasRect.height() / d_dy + 1;

#if 1
            /*
                limit column and row count to a maximum of 1000000,
                so that memory usage is not an issue
             */
            if ( d_numColumns > 1000 )
            {
                d_dx = canvasRect.width() / 1000;
                d_numColumns = canvasRect.width() / d_dx + 1;
            }

            if ( d_numRows > 1000 )
            {
                d_dy = canvasRect.height() / 1000;
                d_numRows = canvasRect.height() / d_dx + 1;
            }
#endif

            d_x1 = d_x0 + d_numColumns * d_dx;
            d_y1 = d_y0 + d_numRows * d_dy;

            d_entries = ( Entry* )::calloc( d_numRows * d_numColumns, sizeof( Entry ) );
            if ( d_entries == NULL )
            {
                qWarning() << "QwtPlotVectorField: raster for filtering too fine - running out of memory";
            }
        }

        ~FilterMatrix()
        {
            if ( d_entries )
                std::free( d_entries );
        }

        inline int numColumns() const
        {
            return d_numColumns;
        }

        inline int numRows() const
        {
            return d_numRows;
        }

        inline void addSample( double x, double y,
            double u, double v )
        {
            if ( x >= d_x0 && x < d_x1
                && y >= d_y0 && y < d_y1 )
            {
                Entry& entry = d_entries[ indexOf( x, y ) ];
                entry.addSample( x, y, u, v );
            }
        }

        const FilterMatrix::Entry* entries() const
        {
            return d_entries;
        }

      private:
        inline int indexOf( qreal x, qreal y ) const
        {
            const int col = ( x - d_x0 ) / d_dx;
            const int row = ( y - d_y0 ) / d_dy;

            return row * d_numColumns + col;
        }

        qreal d_x0, d_x1, d_y0, d_y1, d_dx, d_dy;
        int d_numColumns;
        int d_numRows;

        Entry* d_entries;
    };
}

class QwtPlotVectorField::PrivateData
{
  public:
    PrivateData()
        : pen( Qt::black )
        , brush( Qt::black )
        , indicatorOrigin( QwtPlotVectorField::OriginHead )
        , magnitudeScaleFactor( 1.0 )
        , rasterSize( 20, 20 )
        , magnitudeModes( MagnitudeAsLength )
    {
        colorMap = NULL;
        symbol = new QwtVectorFieldThinArrow();
    }

    ~PrivateData()
    {
        delete colorMap;
        delete symbol;
    }

    QPen pen;
    QBrush brush;

    IndicatorOrigin indicatorOrigin;
    QwtVectorFieldSymbol* symbol;
    QwtColorMap* colorMap;

    /*
        Stores the range of magnitudes to be used for the color map.
        If invalid (min=max or negative values), the range is determined
        from the data samples themselves.
     */
    QwtInterval magnitudeRange;
    QwtInterval boundingMagnitudeRange;

    qreal magnitudeScaleFactor;
    QSizeF rasterSize;

    PaintAttributes paintAttributes;
    MagnitudeModes magnitudeModes;
};

/*!
   Constructor
   \param title Title of the curve
 */
QwtPlotVectorField::QwtPlotVectorField( const QwtText& title )
    : QwtPlotSeriesItem( title )
{
    init();
}

/*!
   Constructor
   \param title Title of the curve
 */
QwtPlotVectorField::QwtPlotVectorField( const QString& title )
    : QwtPlotSeriesItem( QwtText( title ) )
{
    init();
}

//! Destructor
QwtPlotVectorField::~QwtPlotVectorField()
{
    delete m_data;
}

/*!
   \brief Initialize data members
 */
void QwtPlotVectorField::init()
{
    setItemAttribute( QwtPlotItem::Legend );
    setItemAttribute( QwtPlotItem::AutoScale );

    m_data = new PrivateData;
    setData( new QwtVectorFieldData() );

    setZ( 20.0 );
}

void QwtPlotVectorField::setPen( const QPen& pen )
{
    if ( m_data->pen != pen )
    {
        m_data->pen = pen;

        itemChanged();
        legendChanged();
    }
}

QPen QwtPlotVectorField::pen() const
{
    return m_data->pen;
}

void QwtPlotVectorField::setBrush( const QBrush& brush )
{
    if ( m_data->brush != brush )
    {
        m_data->brush = brush;

        itemChanged();
        legendChanged();
    }
}

QBrush QwtPlotVectorField::brush() const
{
    return m_data->brush;
}

void QwtPlotVectorField::setIndicatorOrigin( IndicatorOrigin origin )
{
    m_data->indicatorOrigin = origin;
    if ( m_data->indicatorOrigin != origin )
    {
        m_data->indicatorOrigin = origin;
        itemChanged();
    }
}

QwtPlotVectorField::IndicatorOrigin QwtPlotVectorField::indicatorOrigin() const
{
    return m_data->indicatorOrigin;
}

void QwtPlotVectorField::setMagnitudeScaleFactor( double factor )
{
    if ( factor != m_data->magnitudeScaleFactor )
    {
        m_data->magnitudeScaleFactor = factor;
        itemChanged();
    }
}

double QwtPlotVectorField::magnitudeScaleFactor() const
{
    return m_data->magnitudeScaleFactor;
}

void QwtPlotVectorField::setRasterSize( const QSizeF& size )
{
    if ( size != m_data->rasterSize )
    {
        m_data->rasterSize = size;
        itemChanged();
    }
}

QSizeF QwtPlotVectorField::rasterSize() const
{
    return m_data->rasterSize;
}

/*!
   Specify an attribute how to draw the curve

   \param attribute Paint attribute
   \param on On/Off
   \sa testPaintAttribute()
 */
void QwtPlotVectorField::setPaintAttribute(
    PaintAttribute attribute, bool on )
{
    PaintAttributes attributes = m_data->paintAttributes;

    if ( on )
        attributes |= attribute;
    else
        attributes &= ~attribute;

    if ( m_data->paintAttributes != attributes )
    {
        m_data->paintAttributes = attributes;
        itemChanged();
    }
}

/*!
    \return True, when attribute is enabled
    \sa PaintAttribute, setPaintAttribute()
 */
bool QwtPlotVectorField::testPaintAttribute(
    PaintAttribute attribute ) const
{
    return ( m_data->paintAttributes & attribute );
}

//! \return QwtPlotItem::Rtti_PlotField
int QwtPlotVectorField::rtti() const
{
    return QwtPlotItem::Rtti_PlotVectorField;
}

void QwtPlotVectorField::setMagnitudeMode( MagnitudeMode mode, bool on )
{
    if ( on == testMagnitudeMode( mode ) )
        return;

    if ( on )
        m_data->magnitudeModes |= mode;
    else
        m_data->magnitudeModes &= ~mode;

    itemChanged();
}

bool QwtPlotVectorField::testMagnitudeMode( MagnitudeMode mode ) const
{
    return m_data->magnitudeModes & mode;
}

void QwtPlotVectorField::setMagnitudeModes( MagnitudeModes modes )
{
    if ( m_data->magnitudeModes != modes )
    {
        m_data->magnitudeModes = modes;
        itemChanged();
    }
}

/*!
    Sets a new arrow symbol (implementation of arrow drawing code).
    Ownership is transferred to QwtPlotVectorField.
 */
void QwtPlotVectorField::setSymbol( QwtVectorFieldSymbol* symbol )
{
    if ( m_data->symbol == symbol )
        return;

    delete m_data->symbol;
    m_data->symbol = symbol;

    itemChanged();
    legendChanged();
}

const QwtVectorFieldSymbol* QwtPlotVectorField::symbol() const
{
    return m_data->symbol;
}

QwtPlotVectorField::MagnitudeModes QwtPlotVectorField::magnitudeModes() const
{
    return m_data->magnitudeModes;
}

/*!
   Initialize data with an array of samples.
   \param samples Vector of points
 */
void QwtPlotVectorField::setSamples( const QVector< QwtVectorFieldSample >& samples )
{
    setData( new QwtVectorFieldData( samples ) );
}

/*!
   Assign a series of samples

   setSamples() is just a wrapper for setData() without any additional
   value - beside that it is easier to find for the developer.

   \param data Data
   \warning The item takes ownership of the data object, deleting
           it when its not used anymore.
 */
void QwtPlotVectorField::setSamples( QwtVectorFieldData* data )
{
    setData( data );
}

/*!
   Change the color map

   Often it is useful to display the mapping between intensities and
   colors as an additional plot axis, showing a color bar.

   \param colorMap Color Map

   \sa colorMap(), QwtScaleWidget::setColorBarEnabled(),
      QwtScaleWidget::setColorMap()
 */
void QwtPlotVectorField::setColorMap( QwtColorMap* colorMap )
{
    if ( colorMap == NULL )
        return;

    if ( colorMap != m_data->colorMap )
    {
        delete m_data->colorMap;
        m_data->colorMap = colorMap;
    }

    legendChanged();
    itemChanged();
}

/*!
   \return Color Map used for mapping the intensity values to colors
   \sa setColorMap()
 */
const QwtColorMap* QwtPlotVectorField::colorMap() const
{
    return m_data->colorMap;
}

/*!
   Sets the min/max magnitudes to be used for color map lookups.
   If invalid (min=max=0 or negative values), the range is determined from
   the current range of magnitudes in the vector samples.
 */
void QwtPlotVectorField::setMagnitudeRange( const QwtInterval& magnitudeRange )
{
    m_data->magnitudeRange = magnitudeRange;
}

/*!
   Computes length of the arrow in screen coordinate units based on
   its magnitude. Default implementation simply scales the vector
   using the magnitudeScaleFactor property.
   Re-implement this function to provide special handling for zero/non-zero
   magnitude arrows, or impose minimum/maximum arrow length limits.
   \return Length of arrow to be drawn in dependence of vector magnitude.
   \sa setMagnitudeScaleFactor
 */
double QwtPlotVectorField::arrowLength( double magnitude ) const
{
#if 0
    /*
       Normalize magnitude with respect to value range.
       Then, magnitudeScaleFactor is the number of pixels to draw (times the arrow tail width) for
       a vector of length equal to magnitudeRange.maxValue().
       The relative scaling ensures that change of data samples of very different magnitudes
       will always lead to a reasonable display on screen.
     */
    const QwtVectorFieldData* vectorData = dynamic_cast< const QwtVectorFieldData* >( data() );
    if (m_data->magnitudeRange.maxValue() > 0)
        magnitude /= m_data->magnitudeRange.maxValue();
#endif
    double l = magnitude * m_data->magnitudeScaleFactor;
    if ( m_data->paintAttributes & LimitLength )
    {
        // TODO : make 30 a parameter? or leave this to user code and remove LimitLength altogether?
        l = qMin(l, 50.0);
        // ensure non-zero arrows are always at least 3 pixels long
        if (l != 0)
            l = qMax(l, 3.0);
    }
    return l;
}

QRectF QwtPlotVectorField::boundingRect() const
{
#if 0
    /*
        The bounding rectangle of the samples comes from the origins
        only, but as we know the scaling factor for the magnitude
        ( qwtVector2Magnitude ) here, we could try to include it ?
     */
#endif

    return QwtPlotSeriesItem::boundingRect();
}

QwtGraphic QwtPlotVectorField::legendIcon(
    int index, const QSizeF& size ) const
{
    Q_UNUSED( index );

    QwtGraphic icon;
    icon.setDefaultSize( size );

    if ( size.isEmpty() )
        return icon;

    QPainter painter( &icon );
    painter.setRenderHint( QPainter::Antialiasing,
        testRenderHint( QwtPlotItem::RenderAntialiased ) );

    painter.translate( -size.width(), -0.5 * size.height() );

    painter.setPen( m_data->pen );
    painter.setBrush( m_data->brush );

    m_data->symbol->setLength( size.width() - 2 );
    m_data->symbol->paint( &painter );

    return icon;
}

/*!
   Draw a subset of the points

   \param painter Painter
   \param xMap Maps x-values into pixel coordinates.
   \param yMap Maps y-values into pixel coordinates.
   \param canvasRect Contents rectangle of the canvas
   \param from Index of the first sample to be painted
   \param to Index of the last sample to be painted. If to < 0 the
         series will be painted to its last sample.

   \sa drawDots()
 */
void QwtPlotVectorField::drawSeries( QPainter* painter,
    const QwtScaleMap& xMap, const QwtScaleMap& yMap,
    const QRectF& canvasRect, int from, int to ) const
{
    if ( !painter || dataSize() <= 0 )
        return;

    if ( to < 0 )
        to = dataSize() - 1;

    if ( from < 0 )
        from = 0;

    if ( from > to )
        return;

#if DEBUG_RENDER
    QElapsedTimer timer;
    timer.start();
#endif

    drawSymbols( painter, xMap, yMap, canvasRect, from, to );

#if DEBUG_RENDER
    qDebug() << timer.elapsed();
#endif
}

void QwtPlotVectorField::drawSymbols( QPainter* painter,
    const QwtScaleMap& xMap, const QwtScaleMap& yMap,
    const QRectF& canvasRect, int from, int to ) const
{
    const bool doAlign = QwtPainter::roundingAlignment( painter );
    const bool doClip = false;

    const bool isInvertingX = xMap.isInverting();
    const bool isInvertingY = yMap.isInverting();

    const QwtSeriesData< QwtVectorFieldSample >* series = data();

    if ( m_data->magnitudeModes & MagnitudeAsColor )
    {
        // user input error, can't draw without color map
        // TODO: Discuss! Without colormap, silently fall back to uniform colors?
        if ( m_data->colorMap == NULL)
            return;
    }
    else
    {
        painter->setPen( m_data->pen );
        painter->setBrush( m_data->brush );
    }

    if ( ( m_data->paintAttributes & FilterVectors ) && !m_data->rasterSize.isEmpty() )
    {
        const QRectF dataRect = QwtScaleMap::transform(
            xMap, yMap, boundingRect() );

        // TODO: Discuss. How to handle raster size when switching from screen to print size!
        //       DPI-aware adjustment of rastersize? Or make "rastersize in screen coordinate"
        //       or "rastersize in plotcoordinetes" a user option?
#if 1
        // define filter matrix based on screen/print coordinates
        FilterMatrix matrix( dataRect, canvasRect, m_data->rasterSize );
#else
        // define filter matrix based on real coordinates

        // get scale factor from real coordinates to screen coordinates
        double xScale = 1;
        if (xMap.sDist() != 0)
            xScale = xMap.pDist() / xMap.sDist();

        double yScale = 1;
        if (yMap.sDist() != 0)
            yScale = yMap.pDist() / yMap.sDist();

        QSizeF canvasRasterSize(xScale * m_data->rasterSize.width(), yScale * m_data->rasterSize.height() );
        FilterMatrix matrix( dataRect, canvasRect, canvasRasterSize );
#endif

        for ( int i = from; i <= to; i++ )
        {
            const QwtVectorFieldSample sample = series->sample( i );
            if ( !sample.isNull() )
            {
                matrix.addSample( xMap.transform( sample.x ),
                    yMap.transform( sample.y ), sample.vx, sample.vy );
            }
        }

        const int numEntries = matrix.numRows() * matrix.numColumns();
        const FilterMatrix::Entry* entries = matrix.entries();

        for ( int i = 0; i < numEntries; i++ )
        {
            const FilterMatrix::Entry& entry = entries[i];

            if ( entry.count == 0 )
                continue;

            double xi = entry.x / entry.count;
            double yi = entry.y / entry.count;

            if ( doAlign )
            {
                xi = qRound( xi );
                yi = qRound( yi );
            }

            const double vx = entry.vx / entry.count;
            const double vy = entry.vy / entry.count;

            drawSymbol( painter, xi, yi,
                isInvertingX ? -vx : vx, isInvertingY ? -vy : vy );
        }
    }
    else
    {
        for ( int i = from; i <= to; i++ )
        {
            const QwtVectorFieldSample sample = series->sample( i );

            // arrows with zero length are never drawn
            if ( sample.isNull() )
                continue;

            double xi = xMap.transform( sample.x );
            double yi = yMap.transform( sample.y );

            if ( doAlign )
            {
                xi = qRound( xi );
                yi = qRound( yi );
            }

            if ( doClip )
            {
                if ( !canvasRect.contains( xi, yi ) )
                    continue;
            }

            drawSymbol( painter, xi, yi,
                isInvertingX ? -sample.vx : sample.vx,
                isInvertingY ? -sample.vy : sample.vy );
        }
    }
}

void QwtPlotVectorField::drawSymbol( QPainter* painter,
    double x, double y, double vx, double vy ) const
{
    const double magnitude = qwtVector2Magnitude( vx, vy );

    const QTransform oldTransform = painter->transform();

    QTransform transform = qwtSymbolTransformation( oldTransform,
        x, y, vx, vy, magnitude );

    QwtVectorFieldSymbol* symbol = m_data->symbol;

    double length = 0.0;

    if ( m_data->magnitudeModes & MagnitudeAsLength )
    {
        length = arrowLength( magnitude );
    }

    symbol->setLength( length );

    if( m_data->indicatorOrigin == OriginTail )
    {
        const qreal dx = symbol->length();
        transform.translate( dx, 0.0 );
    }
    else if ( m_data->indicatorOrigin == OriginCenter )
    {
        const qreal dx = symbol->length();
        transform.translate( 0.5 * dx, 0.0 );
    }

    if ( m_data->magnitudeModes & MagnitudeAsColor )
    {
        // Determine color for arrow if colored by magnitude.

        QwtInterval range = m_data->magnitudeRange;

        if ( !range.isValid() )
        {
            if ( !m_data->boundingMagnitudeRange.isValid() )
                m_data->boundingMagnitudeRange = qwtMagnitudeRange( data() );

            range = m_data->boundingMagnitudeRange;
        }

        const QColor c = m_data->colorMap->rgb( range, magnitude );

#if 1
        painter->setBrush( c );
        painter->setPen( c );
#endif
    }

    painter->setWorldTransform( transform, false );
    symbol->paint( painter );
    painter->setWorldTransform( oldTransform, false );
}

void QwtPlotVectorField::dataChanged()
{
    m_data->boundingMagnitudeRange.invalidate();
    QwtPlotSeriesItem::dataChanged();
}
