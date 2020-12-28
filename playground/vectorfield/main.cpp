/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include <qwt_plot.h>
#include <qwt_samples.h>
#include <qwt_plot_vectorfield.h>
#include <qwt_vectorfield_symbol.h>
#include <qwt_plot_grid.h>
#include <qwt_legend.h>
#include <qwt_color_map.h>

#include <qapplication.h>
#include <qpen.h>

class VectorField: public QwtPlotVectorField
{
public:
    VectorField():
        QwtPlotVectorField( "Vector Field" )
    {
        setRenderHint( QwtPlotItem::RenderAntialiased, true );
        setLegendIconSize( QSize( 20, 10 ) );

        setMagnitudeScaleFactor( 1.0 );

#if 0
        // test solid arrow
        setSymbol( new QwtVectorFieldArrow() );
        setPen( Qt::NoPen );
        setBrush( Qt::black );
        setMagnitudeScaleFactor( 2 );
#endif

#if 1
        // test color map
        QwtLinearColorMap *cm = new QwtLinearColorMap();
        cm->setColorInterval( Qt::yellow, Qt::blue );
        cm->addColorStop( 0.5, Qt::red );
        setColorMap( cm );
        setMagnitudeMode( MagnitudeAsColor, true );
#endif

#if 1
        setIndicatorOrigin( QwtPlotVectorField::OriginHead );
#else
        setIndicatorOrigin( QwtPlotVectorField::OriginTail );
#endif

#if 0
        setRasterSize( QSizeF( 20, 20 ) );
#endif
        setSamples( samples() );
    }

private:
    QVector<QwtVectorFieldSample> samples() const
    {
        const int dim = 10;

        QVector<QwtVectorFieldSample> samples;

        for ( int x = -dim; x < dim; x++ )
        {
            for ( int y = -dim; y < dim; y++ )
            {
                samples += QwtVectorFieldSample( x, y, y, -x );
            }
        }

        return samples;
    }
};

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    QwtPlot plot;
    plot.setTitle( "Vector Field" );
    plot.setCanvasBackground( Qt::white );

    plot.insertLegend( new QwtLegend() );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->attach( &plot );

    VectorField *fieldItem = new VectorField();
    fieldItem->attach( &plot );

    const QRectF r = fieldItem->boundingRect();

#if 1
    plot.setAxisScale( QwtPlot::xBottom, r.left() - 1.0, r.right() + 1.0 );
#else
    plot.setAxisScale( QwtPlot::xBottom, r.right() + 1.0, r.left() - 1.0 );
#endif

#if 1
    plot.setAxisScale( QwtPlot::yLeft, r.top() - 1.0, r.bottom() + 1.0 );
#else
    plot.setAxisScale( QwtPlot::yLeft, r.bottom() + 1.0, r.top() - 1.0 );
#endif

    plot.resize( 600, 400 );
    plot.show();

    return a.exec();
}
