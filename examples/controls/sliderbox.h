/*****************************************************************************
 * Qwt Examples
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef SLIDER_BOX_H
#define SLIDER_BOX_H

#include <qwidget.h>

class QLabel;
class QwtSlider;

class SliderBox: public QWidget
{
    Q_OBJECT
public:
    SliderBox( int sliderType, QWidget *parent = NULL );

private Q_SLOTS:
    void setNum( double v );

private:
    QwtSlider *createSlider( int sliderType ) const;

    QwtSlider *d_slider;
    QLabel *d_label;
};

#endif
