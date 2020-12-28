/*****************************************************************************
 * Qwt Examples
 * Copyright (C) 1997   Josef Wilgen
 * Copyright (C) 2002   Uwe Rathmann
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the Qwt License, Version 1.0
 *****************************************************************************/

#ifndef COMPLEX_NUMBER_H
#define COMPLEX_NUMBER_H

class ComplexNumber
{
public:
    ComplexNumber() ;
    ComplexNumber( double r, double i = 0.0 );

    double real() const;
    double imag() const;

    friend ComplexNumber operator*(
        const ComplexNumber &, const ComplexNumber & );

    friend ComplexNumber operator+(
        const ComplexNumber &, const ComplexNumber & );

    friend ComplexNumber operator-(
        const ComplexNumber &, const ComplexNumber & );
    friend ComplexNumber operator/(
        const ComplexNumber &, const ComplexNumber & );

private:
    double d_real;
    double d_imag;
};

inline ComplexNumber::ComplexNumber():
    d_real( 0.0 ),
    d_imag( -0.0 )
{
}

inline ComplexNumber::ComplexNumber( double re, double im ):
    d_real( re ),
    d_imag( im )
{
}

inline double ComplexNumber::real() const
{
    return d_real;
}

inline double ComplexNumber::imag() const
{
    return d_imag;
}

inline ComplexNumber operator+(
    const ComplexNumber &x1, const ComplexNumber &x2 )
{
    return ComplexNumber( x1.d_real + x2.d_real, x1.d_imag + x2.d_imag );
}

inline ComplexNumber operator-(
    const ComplexNumber &x1, const ComplexNumber &x2 )
{
    return ComplexNumber( x1.d_real - x2.d_real, x1.d_imag - x2.d_imag );
}

inline ComplexNumber operator*(
    const ComplexNumber &x1, const ComplexNumber &x2 )
{
    return ComplexNumber( x1.d_real * x2.d_real - x1.d_imag * x2.d_imag,
        x1.d_real * x2.d_imag + x2.d_real * x1.d_imag );
}

inline ComplexNumber operator/(
    const ComplexNumber &x1, const ComplexNumber &x2 )
{
    double denom = x2.d_real * x2.d_real + x2.d_imag * x2.d_imag;

    return ComplexNumber(
               ( x1.d_real * x2.d_real + x1.d_imag * x2.d_imag ) / denom,
               ( x1.d_imag * x2.d_real - x2.d_imag * x1.d_real ) / denom
           );
}

#endif
