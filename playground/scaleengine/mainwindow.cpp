/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#include "mainwindow.h"
#include "plot.h"
#include "transformplot.h"

#include <qwt_transform.h>
#include <qwt_math.h>

#include <qsplitter.h>

class TransformPos: public QwtTransform
{
public:
    TransformPos( double pos, double range, double factor ):
        d_position( pos ),
        d_range( range ),
        d_factor( factor ),
        d_powRange( std::pow( d_range, d_factor ) )
    {
    }

    virtual double transform( double value ) const QWT_OVERRIDE
    {
        const double v1 = d_position - d_range;
        const double v2 = v1 + 2 * d_range;

        if ( value <= v1 )
        {
            return value;
        }

        if ( value >= v2 )
        {
            return v1 + 2 * d_powRange + value - v2;
        }

        double v;

        if ( value <= d_position )
        {
            v = v1 + std::pow( value - v1, d_factor );
        }
        else
        {
            v = v1 + 2 * d_powRange - std::pow( v2 - value, d_factor );
        }

        return v;
    }

    virtual double invTransform( double value ) const  QWT_OVERRIDE
    {
        const double v1 = d_position - d_range;
        const double v2 = v1 + 2 * d_powRange;

        if ( value < v1 )
        {
            return value;
        }

        if ( value >= v2 )
        {
            return value + 2 * ( d_range - d_powRange );
        }

        double v;
        if ( value <= v1 + d_powRange )
        {
            v = v1 + std::pow( value - v1, 1.0 / d_factor );
        }
        else
        {
            v = d_position + d_range - std::pow( v2 - value, 1.0 / d_factor );
        }

        return v;
    }

    virtual QwtTransform *copy() const QWT_OVERRIDE
    {
        return new TransformPos( d_position, d_range, d_factor );
    }

private:
    const double d_position;
    const double d_range;
    const double d_factor;
    const double d_powRange;
};

MainWindow::MainWindow( QWidget *parent ):
    QMainWindow( parent )
{
    QSplitter *splitter = new QSplitter( Qt::Vertical );

    d_transformPlot = new TransformPlot( splitter );

    d_transformPlot->insertTransformation( "Square Root",
        QColor( "DarkSlateGray" ), new QwtPowerTransform( 0.5 ) );
    d_transformPlot->insertTransformation( "Linear",
        QColor( "Peru" ), new QwtNullTransform() );
    d_transformPlot->insertTransformation( "Cubic",
        QColor( "OliveDrab" ), new QwtPowerTransform( 3.0 ) );
    d_transformPlot->insertTransformation( "Power 10",
        QColor( "Indigo" ), new QwtPowerTransform( 10.0 ) );
    d_transformPlot->insertTransformation( "Log",
        QColor( "SteelBlue" ), new QwtLogTransform() );
    d_transformPlot->insertTransformation( "At 400",
        QColor( "Crimson" ), new TransformPos( 400.0, 100.0, 1.4 ) );

    const QwtPlotItemList curves =
        d_transformPlot->itemList( QwtPlotItem::Rtti_PlotCurve );
    if ( !curves.isEmpty() )
        d_transformPlot->setLegendChecked( curves[ 2 ] );

    d_plot = new Plot( splitter );
    d_plot->setTransformation( new QwtPowerTransform( 3.0 ) );

    setCentralWidget( splitter );

    connect( d_transformPlot, SIGNAL( selected( QwtTransform * ) ),
        d_plot, SLOT( setTransformation( QwtTransform * ) ) );
}

#include "moc_mainwindow.cpp"
