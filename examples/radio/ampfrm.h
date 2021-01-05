/*****************************************************************************
* Qwt Widget Library
* Copyright (C) 1997   Josef Wilgen
* Copyright (C) 2002   Uwe Rathmann
*
* This library is free software; you can redistribute it and/or
* modify it under the terms of the Qwt License, Version 1.0
*****************************************************************************/

#pragma once

#include <QwtGlobal>
#include <QFrame>

class Knob;
class Thermo;

class AmpFrame : public QFrame
{
    Q_OBJECT
  public:
    AmpFrame( QWidget* );

  public Q_SLOTS:
    void setMaster( double v );

  protected:
    virtual void timerEvent( QTimerEvent* ) QWT_OVERRIDE;

  private:
    Knob* m_knbVolume;
    Knob* m_knbBalance;
    Knob* m_knbTreble;
    Knob* m_knbBass;
    Thermo* m_thmLeft;
    Thermo* m_thmRight;
    double m_master;
};
