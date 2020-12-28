/* -*- mode: C++ ; c-file-style: "stroustrup" -*- *****************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef QWT_SYSTEM_CLOCK_H
#define QWT_SYSTEM_CLOCK_H

#include "qwt_global.h"

/*!
  \brief QwtSystemClock provides high resolution clock time functions.

  Precision and time intervals are multiples of milliseconds (ms).

  ( QwtSystemClock is obsolete since Qt 4.8 as QElapsedTimer offers the same
    precision )
*/

class QWT_EXPORT QwtSystemClock
{
public:
    QwtSystemClock();
    virtual ~QwtSystemClock();

    bool isNull() const;

    void start();
    double restart();
    double elapsed() const;

private:
    Q_DISABLE_COPY(QwtSystemClock)

    class PrivateData;
    PrivateData *d_data;
};

#endif
