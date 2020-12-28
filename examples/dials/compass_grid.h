/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef COMPASS_GRID
#define COMPASS_GRID

#include <qframe.h>

class QwtCompass;

class CompassGrid: public QFrame
{
public:
    CompassGrid( QWidget *parent = NULL );

private:
    QwtCompass *createCompass( int pos );
};

#endif
