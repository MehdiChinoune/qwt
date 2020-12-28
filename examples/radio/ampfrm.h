/*****************************************************************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef AMP_FRAME_H
#define AMP_FRAME_H

#include <qwt_global.h>
#include <qframe.h>

class Knob;
class Thermo;

class AmpFrame : public QFrame
{
    Q_OBJECT
public:
    AmpFrame( QWidget * );

public Q_SLOTS:
    void setMaster( double v );

protected:
    virtual void timerEvent( QTimerEvent * ) QWT_OVERRIDE;

private:
    Knob *d_knbVolume;
    Knob *d_knbBalance;
    Knob *d_knbTreble;
    Knob *d_knbBass;
    Thermo *d_thmLeft;
    Thermo *d_thmRight;
    double d_master;
};

#endif
