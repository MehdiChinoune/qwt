/******************************************************************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#include "MainWindow.h"
#include "TunerBox.h"
#include "AmplifierBox.h"

#include <QLayout>

MainWindow::MainWindow()
{
    TunerBox* tunerBox = new TunerBox( this );
    tunerBox->setFrameStyle( QFrame::Panel | QFrame::Raised );

    AmplifierBox* amplifierBox = new AmplifierBox( this );
    amplifierBox->setFrameStyle( QFrame::Panel | QFrame::Raised );

    QVBoxLayout* layout = new QVBoxLayout( this );
    layout->setContentsMargins( QMargins() );
    layout->setSpacing( 0 );
    layout->addWidget( tunerBox );
    layout->addWidget( amplifierBox );

    connect( tunerBox, SIGNAL(fieldChanged(double)),
        amplifierBox, SLOT(setMaster(double)) );

    tunerBox->setFreq( 90.0 );

    setPalette( QPalette( QColor( 192, 192, 192 ) ) );
    updateGradient();
}

void MainWindow::resizeEvent( QResizeEvent* )
{
    // Qt 4.7.1: QGradient::StretchToDeviceMode is buggy on X11
    updateGradient();
}

void MainWindow::updateGradient()
{
    QPalette pal = palette();

    const QColor buttonColor = pal.color( QPalette::Button );
    const QColor midLightColor = pal.color( QPalette::Midlight );

    QLinearGradient gradient( rect().topLeft(), rect().topRight() );
    gradient.setColorAt( 0.0, midLightColor );
    gradient.setColorAt( 0.7, buttonColor );
    gradient.setColorAt( 1.0, buttonColor );

    pal.setBrush( QPalette::Window, gradient );
    setPalette( pal );
}
