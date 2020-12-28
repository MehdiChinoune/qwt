/*****************************************************************************
 * Qwt Examples - Copyright (C) 2002 Uwe Rathmann
 * This file may be used under the terms of the 3-clause BSD License
 *****************************************************************************/

#ifndef CPU_STAT_H
#define CPU_STAT_H

#include <qdatetime.h>

class CpuStat
{
public:
    CpuStat();
    void statistic( double &user, double &system );
    QTime upTime() const;

    enum Value
    {
        User,
        Nice,
        System,
        Idle,

        NValues
    };

private:
    void lookUp( double[NValues] ) const;
    double procValues[NValues];
};

#endif
