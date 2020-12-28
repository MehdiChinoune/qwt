/*****************************************************************************
 * Qwt Widget Library
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <qwt_global.h>
#include <qwidget.h>

class MainWindow : public QWidget
{
public:
    MainWindow();

protected:
    virtual void resizeEvent( QResizeEvent * ) QWT_OVERRIDE;

private:
    void updateGradient();
};

#endif
