/* -------------------------------------------------------------------- */
/* Z++ Version 1.10               complex.h       Last revised 10/10/92 */
/*                                                                      */
/* Complex number class for Turbo C++/Borland C++.                      */
/* Copyright 1992 by Carl W. Moreland                                   */
/* -------------------------------------------------------------------- */

#ifndef COMPLEXdotH
#define COMPLEXdotH

#include <math.h>
#include <iostream.h>

const unsigned char Z_RADIANS = 0;
const unsigned char Z_DEGREES = 1;
const unsigned char Z_COMMA   = 0;	// (x, y)
const unsigned char Z_LETTER  = 1;	// x + iy

class complex
{
public:
  double re, im;

private:
  static unsigned char zArgMode;
  static unsigned char zPrintMode;
  static unsigned char zLetter;

public:
  complex(void): re(0), im(0) {}
  complex(const double real, const double imag=0): re(real), im(imag) {}
  complex(const complex& z): re(z.re), im(z.im) {}

  friend double    re(const complex& z) {	// real part
    return z.re;
  }
  friend double    im(const complex& z) {	// imaginary part
    return z.im;
  }
  friend double  real(const complex& z) {	// real part
    return z.re;
  }
  friend double  imag(const complex& z) {	// imaginary part
    return z.im;
  }
  friend double   mag(const complex& z) {	// magnitude |z|
    return sqrt(z.re*z.re + z.im*z.im);
  }
  friend double   arg(const complex& z);	// argument
  friend double   ang(const complex& z) {	// angle
    return arg(z);
  }
  friend double    ph(const complex& z) {	// phase
    return arg(z);
  }
  friend complex conj(const complex& z) {	// complex conjugate
    return complex(z.re, -z.im);
  }
  friend double  norm(const complex& z) {	// norm
    return z.re*z.re + z.im*z.im;
  }

  friend complex rtop(double x,   double y=0);
  friend complex ptor(double mag, double angle=0);
  complex& topolar(void);
  complex& torect(void);

  void operator = (const complex& z) {		// z1 = z2
    re = z.re;
    im = z.im;
  }
  complex& operator += (const complex& z) {	// z1 += z2
    re += z.re;
    im += z.im;
    return *this;
  }
  complex& operator -= (const complex& z) {	// z1 -= z2
    re -= z.re;
    im -= z.im;
    return *this;
  }
  complex& operator *= (const complex& z) {	// z1 *= z2
    *this = *this * z;
    return *this;
  }
  complex& operator /= (const complex& z) {	// z1 /= z2
    *this = *this / z;
    return *this;
  }
  complex operator + (void) const {		// +z1
    return *this;
  }
  complex operator - (void) const {		// -z1
    return complex(-re, -im);
  }

  friend complex operator + (const complex& z1, const complex& z2) {
    return complex(z1.re + z2.re, z1.im + z2.im);
  }
  friend complex operator + (const complex& z, const double x) {
    return complex(z.re+x, z.im);
  }
  friend complex operator + (const double x, const complex& z) {
    return complex(z.re+x, z.im);
  }
  friend complex operator - (const complex& z1, const complex& z2) {
    return complex(z1.re - z2.re, z1.im - z2.im);
  }
  friend complex operator - (const complex&, const double);
  friend complex operator - (const double x, const complex& z) {
    return complex(x-z.re, -z.im);
  }
  friend complex operator * (const complex& z1, const complex& z2) {
    double re = z1.re*z2.re - z1.im*z2.im;
    double im = z1.re*z2.im + z1.im*z2.re;
    return complex(re, im);
  }
  friend complex operator * (const complex& z, const double x) {
    return complex(z.re*x, z.im*x);
  }
  friend complex operator * (const double x, const complex& z) {
    return complex(z.re*x, z.im*x);
  }
  friend complex operator / (const complex&, const complex&);
  friend complex operator / (const complex& z, const double x) {
    return complex(z.re/x, z.im/x);
  }
  friend complex operator / (const double, const complex&);
  friend complex operator ^ (const complex& z1, const complex& z2) {
    return pow(z1, z2);
  }

  friend int operator == (const complex& z1, const complex& z2) {
    return (z1.re == z2.re) && (z1.im == z2.im);
  }
  friend int operator != (const complex& z1, const complex& z2) {
    return (z1.re != z2.re) || (z1.im != z2.im);
  }

  friend double   abs(const complex& z);
  friend complex sqrt(const complex& z);
  friend complex pow(const complex& base, const complex& exp);
  friend complex pow(const complex& base, const double   exp);
  friend complex pow(const double   base, const complex& exp);

  friend complex   exp(const complex& z);
  friend complex   log(const complex& z);
  friend complex    ln(const complex& z);
  friend complex log10(const complex& z);

  friend complex  cos(const complex& z);
  friend complex  sin(const complex& z);
  friend complex  tan(const complex& z);

  friend complex asin(const complex& z);
  friend complex acos(const complex& z);
  friend complex atan(const complex& z);

  friend complex sinh(const complex& z);
  friend complex cosh(const complex& z);
  friend complex tanh(const complex& z);

  void SetArgMode(unsigned char mode) const {
    if(mode == Z_RADIANS || mode == Z_DEGREES)
      zArgMode = mode;
  }
  void SetPrintMode(unsigned char mode) const {
    if(mode == Z_COMMA || mode == Z_LETTER)
      zPrintMode = mode;
  }
  void SetLetter(unsigned char letter) const {
    zLetter = letter;
  }

  friend ostream& operator<<(ostream&, const complex&);
  friend istream& operator>>(istream&, const complex&);
};

static const complex Z0(0, 0);		// complex number 0
static const complex Z1(1, 0);		// complex number 1
static const complex Zi(0, 1);		// complex number i
static const complex Zinf(HUGE_VAL, HUGE_VAL); // complex number infinity
static const complex Complex;

/* -------------------------------------------------------------------- */
/* Here is the same class with the name capitalized. If you prefer this */
/* simply remove the comment delimiters below and comment out the 5     */
/* static globals above.                                                */
/* -------------------------------------------------------------------- */
/*
class Complex: public complex
{
public:
  Complex(void): re(0), im(0) {}
  Complex(const double real, const double imag=0): re(real), im(imag) {}
  Complex(const complex& z): re(z.re), im(z.im) {}
};

static const Complex Z0(0, 0);		// complex number 0
static const Complex Z1(1, 0);		// complex number 1
static const Complex Zi(0, 1);		// complex number i
static const Complex Zinf(HUGE_VAL, HUGE_VAL); // complex number infinity
static const Complex complex;
*/

#endif
