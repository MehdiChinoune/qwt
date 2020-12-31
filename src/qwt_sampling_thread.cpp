/******************************************************************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "qwt_sampling_thread.h"
#include "qwt_system_clock.h"

class QwtSamplingThread::PrivateData
{
public:
    QwtSystemClock clock;

    double interval;
    bool isStopped;
};


//! Constructor
QwtSamplingThread::QwtSamplingThread( QObject *parent ):
    QThread( parent )
{
    m_data = new PrivateData;
    m_data->interval = 1000; // 1 second
    m_data->isStopped = true;
}

//! Destructor
QwtSamplingThread::~QwtSamplingThread()
{
    delete m_data;
}

/*!
   Change the interval (in ms), when sample() is called.
   The default interval is 1000.0 ( = 1s )

   \param interval Interval
   \sa interval()
*/
void QwtSamplingThread::setInterval( double interval )
{
    if ( interval < 0.0 )
        interval = 0.0;

    m_data->interval = interval;
}

/*!
   \return Interval (in ms), between 2 calls of sample()
   \sa setInterval()
*/
double QwtSamplingThread::interval() const
{
    return m_data->interval;
}

/*!
   \return Time (in ms) since the thread was started
   \sa QThread::start(), run()
*/
double QwtSamplingThread::elapsed() const
{
    if ( m_data->isStopped )
        return 0.0;

    return m_data->clock.elapsed();
}

/*!
   Terminate the collecting thread
   \sa QThread::start(), run()
*/
void QwtSamplingThread::stop()
{
    m_data->isStopped = true;
}

/*!
   Loop collecting samples started from QThread::start()
   \sa stop()
*/
void QwtSamplingThread::run()
{
    m_data->clock.start();
    m_data->isStopped = false;

    while ( !m_data->isStopped )
    {
        const double elapsed = m_data->clock.elapsed();
        sample( elapsed / 1000.0 );

        if ( m_data->interval > 0.0 )
        {
            const double msecs =
                m_data->interval - ( m_data->clock.elapsed() - elapsed );

            if ( msecs > 0.0 )
                usleep( qRound( 1000.0 * msecs ) );
        }
    }
}

#if QWT_MOC_INCLUDE
#include "moc_qwt_sampling_thread.cpp"
#endif
