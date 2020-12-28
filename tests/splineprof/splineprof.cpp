#include <qwt_spline_pleasing.h>
#include <qwt_spline_local.h>
#include <qwt_spline_cubic.h>
#include <qwt_spline_parametrization.h>

#include <qelapsedtimer.h>

#include <qpolygon.h>
#include <qline.h>
#include <qdebug.h>

static void testSpline( const char *name, QwtSplineInterpolating *spline,
	int type, const QPolygonF &points )
{
	spline->setParametrization( type );

	QElapsedTimer timer;
	timer.start();

	const QVector<QLineF> lines = spline->bezierControlLines( points );

	qDebug() << name << ":" << timer.elapsed();
}

static void testSplines( int paramType, const QPolygonF &points )
{
#if 0
	QwtSplinePleasing splinePleasing;
	testSpline( "Pleasing", &splinePleasing, paramType, points );
#endif

#if 1
	QwtSplineLocal splineCardinal( QwtSplineLocal::Cardinal );
	testSpline( "Cardinal", &splineCardinal, paramType, points );
#endif

#if 1
	QwtSplineLocal splinePC( QwtSplineLocal::PChip );
	testSpline( "PChip", &splinePC, paramType, points );
#endif

#if 1
	QwtSplineLocal splineAkima( QwtSplineLocal::Akima );
	testSpline( "Akima", &splineAkima, paramType, points );
#endif

#if 1
	QwtSplineLocal splinePB( QwtSplineLocal::ParabolicBlending );
	testSpline( "Parabolic Blending", &splinePB, paramType, points );
#endif

#if 1
	QwtSplineCubic splineC2;
	testSpline( "Cubic", &splineC2, paramType, points );
#endif
}

int main()
{
	QPolygonF points;

	for ( int i = 0; i < 10e6; i++ )
		points += QPointF( i, std::sin( i ) );

#if 1
	qDebug() << "=== X";
	testSplines( QwtSplineParametrization::ParameterX, points );
#endif

#if 1
	qDebug() << "=== Y";
	testSplines( QwtSplineParametrization::ParameterY, points );
#endif

#if 1
	qDebug() << "=== Uniform";
	testSplines( QwtSplineParametrization::ParameterUniform, points );
#endif

#if 1
	qDebug() << "=== Manhattan";
	testSplines( QwtSplineParametrization::ParameterManhattan, points );
#endif

#if 1
	qDebug() << "=== Chordal";
	testSplines( QwtSplineParametrization::ParameterChordal, points );
#endif

#if 1
	qDebug() << "=== Centripetral";
	testSplines( QwtSplineParametrization::ParameterCentripetal, points );
#endif

	return 0;
}
