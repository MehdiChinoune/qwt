/*****************************************************************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef TUNER_FRAME_H
#define TUNER_FRAME_H

#include <qframe.h>

class QwtWheel;
class QwtSlider;
class TuningThermo;

class TunerFrame : public QFrame
{
    Q_OBJECT
public:
    TunerFrame( QWidget *p );

Q_SIGNALS:
    void fieldChanged( double f );

public Q_SLOTS:
    void setFreq( double frq );

private Q_SLOTS:
    void adjustFreq( double frq );

private:
    QwtWheel *d_wheelFrequency;
    TuningThermo *d_thermoTune;
    QwtSlider *d_sliderFrequency;
};

#endif
