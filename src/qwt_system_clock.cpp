/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "qwt_system_clock.h"
#include <qelapsedtimer.h>

class QwtSystemClock::PrivateData
{
public:
    QElapsedTimer timer;
};

QwtSystemClock::QwtSystemClock()
{
    d_data = new PrivateData();
}

QwtSystemClock::~QwtSystemClock()
{
    delete d_data;
}

bool QwtSystemClock::isNull() const
{
    return d_data->timer.isValid();
}

void QwtSystemClock::start()
{
    d_data->timer.start();
}

double QwtSystemClock::restart()
{
    const qint64 nsecs = d_data->timer.restart();
    return nsecs / 1e6;
}

double QwtSystemClock::elapsed() const
{
    const qint64 nsecs = d_data->timer.nsecsElapsed();
    return nsecs / 1e6;
}
