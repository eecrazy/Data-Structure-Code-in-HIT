#include "matrix.h"
#include <math.h>
#include <fstream.h>
#include <malloc.h>

const unsigned char Z_RADIANS = 0;
const unsigned char Z_DEGREES = 1;
const unsigned char Z_COMMA   = 0;	// (x, y)
const unsigned char Z_LETTER  = 1;	// x + iy
const double M_PI  = 1.1415926;	
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
///////////////////////////////////////////////
/////////////////////////////////////////////////
///////////////////////////////////////////////
unsigned char complex::zArgMode   = Z_RADIANS;
unsigned char complex::zPrintMode = Z_COMMA;
unsigned char complex::zLetter    = 'i';

/* -------------------------------------------------------------------- */

double arg(const complex& z)		// argument (angle)
{
  if(z.re == 0 && z.im == 0)		// this is actually a domain error
    return 0;
  if(complex::zArgMode == Z_RADIANS)
    return atan2(z.im, z.re);
  return atan2(z.im, z.re)/M_PI*180;
}

complex ptor(double mag, double angle)  // polar-to-rectangular
{
  if(complex::zArgMode == Z_RADIANS)
    return complex(mag*cos(angle), mag*sin(angle));
  return complex(mag*cos(angle/180*M_PI), mag*sin(angle/180*M_PI));
}

complex rtop(double x, double y)	// rectangular-to-polar
{
  if(x == 0 && y == 0)			// this is actually a domain error
    return Z0;
  if(complex::zArgMode == Z_RADIANS)
    return complex(sqrt(x*x + y*y), atan2(y, x));
  return complex(sqrt(x*x + y*y), atan2(y, x)*180/M_PI);
}

complex& complex::topolar(void)
{
  double re_tmp = re;

  if(re != 0 || im != 0)		// z = (0,0) is a domain error
  {
    re = sqrt(re*re + im*im);
    im = atan2(im, re_tmp);
  }

  if(complex::zArgMode == Z_DEGREES)
    im *= (180/M_PI);

  return *this;
}

complex& complex::torect(void)
{
  double re_tmp = re;

  re = re_tmp*cos(im);
  im = re_tmp*sin(im);

  return *this;
}

/* ----- Operators ---------------------------------------------------- */

complex operator/(const complex& z1, const complex& z2)
{
  if(z2 == Z0)
    return complex(Zinf);		// z2 = Z0 is an error!

  double denom = z2.re*z2.re + z2.im*z2.im;
  double re = (z1.re*z2.re + z1.im*z2.im)/denom;
  double im = (z2.re*z1.im - z2.im*z1.re)/denom;
  return complex(re, im);
}

complex operator/(const double x, const complex& z)
{
  if(z == Z0)
    return complex(Zinf);		// z = Z0 is an error!

  double denom = z.re*z.re + z.im*z.im;
  return complex(x*z.re/denom, -z.im*x/denom);
}

/* ----- Math functions ----------------------------------------------- */

double abs(const complex& z)
{
  return sqrt(z.re*z.re + z.im*z.im);
}

complex sqrt(const complex& z)
{
  return ptor(sqrt(abs(z)), arg(z)/2);
}

complex pow(const complex& base, const double exponent)
{
  if(base != Z0 && exponent == 0.0)
    return complex(1,0);

  if (base == Z0 && exponent > 0)
    return Z0;

  // base == Z0 && exponent == 0 is undefined!

  return ptor(pow(abs(base), exponent), exponent*arg(base));
}

complex pow(const double base, const complex& exponent)
{
  if(base != 0.0 && exponent == Z0)
    return complex(1,0);

  if (base == 0 && re(exponent) > 0)
    return complex(0,0);

  // base == 0 && re(exponent) == 0 is undefined!

  if(base > 0.0)
    return exp(exponent * log(fabs(base)));

  return exp(exponent * complex(log(fabs(base)), M_PI));
}

complex pow(const complex& base, const complex& exponent)
{
  if(base != Z0 && exponent == Z0)
    return complex(1,0);

  if(base == Z0 && re(exponent) > 0)
    return complex(0,0);

  // base == Z0 && re(exponent) == 0 is undefined!

  return exp(exponent * log(base));
}

/* ----- Trig functions ----------------------------------------------- */

complex exp(const complex& z)
{
  double mag = exp(z.re);
  return complex(mag*cos(z.im), mag*sin(z.im));
}

complex log(const complex& z)
{
  return complex(log(mag(z)), atan2(z.im, z.re));
}
/*
complex log10(const complex& z)
{
  return log(z) * M_LOG10E;
}
*/
complex sin(const complex& z)
{
  return (exp(Zi*z) - exp(-Zi*z))/(2*Zi);
}

complex cos(const complex& z)
{
  return (exp(Zi*z) + exp(-Zi*z))/2;
}

complex tan(const complex& z)
{
  return sin(z)/cos(z);
}

complex asin(const complex& z)
{
  return -Zi*log(Zi*z+sqrt(1-z*z));
}

complex acos(const complex& z)
{
  return -Zi*log(z+Zi*sqrt(1-z*z));
}

complex atan(const complex& z)
{
  return -0.5*Zi * log((1+Zi*z)/(1-Zi*z));
}

complex sinh(const complex& z)
{
  return (exp(z) - exp(-z))/2;
}

complex cosh(const complex& z)
{
  return (exp(z) + exp(-z))/2;
}

complex tanh(const complex& z)
{
  return sinh(z)/cosh(z);
}

/* ----- Stream I/O --------------------------------------------------- */

ostream& operator<<(ostream& s, const complex& z)
{
  char sign[] = "   ";

  if(complex::zPrintMode == Z_COMMA)
    return s << "(" << z.re << ", " << z.im << ")";

  if(z.im == 0 || z.im/fabs(z.im) == 1)
    sign[1] = '+';
  else
    sign[1] = '-';
  return s << z.re << sign << complex::zLetter << fabs(z.im);

}

istream& operator>>(istream& s, const complex& z)
{
  char ch;

  s >> ch;
  if(ch == '(')
  {
    s >> z.re >> ch;
    if(ch == ',')
      s >> z.im >> ch;
    if(ch != ')')
      s.clear(ios::badbit | s.rdstate());
  }
  else
  {
    s.putback(ch);
    s >> z.re;
  }

  return s;
}
///////////////////////////////////////
////////////////////fft
void Fft(complex CA[],int n,int k,complex CB[],int l,int il)
{
    int it,m,is,i,j,nv,l0;
    double p,q,s,vr,vi,poddr,poddi;
	double *pr,*pi,*fr,*fi;
	pr=(double*)malloc(n*sizeof(double));
    pi=(double*)malloc(n*sizeof(double));
	fr=(double*)malloc(n*sizeof(double));
	fi=(double*)malloc(n*sizeof(double));
	for(i=0;i<n;i++)
	{
		pr[i]=CA[i].re;
		pi[i]=CA[i].im;
	}
    for (it=0; it<=n-1; it++)
      { m=it; is=0;
        for (i=0; i<=k-1; i++)
          { j=m/2; is=2*is+(m-2*j); m=j;}
        fr[it]=pr[is]; fi[it]=pi[is];
      }
    pr[0]=1.0; pi[0]=0.0;
    p=6.283185306/(1.0*n);
    pr[1]=cos(p); pi[1]=-sin(p);
    if (l!=0) pi[1]=-pi[1];
    for (i=2; i<=n-1; i++)
      { p=pr[i-1]*pr[1]; q=pi[i-1]*pi[1];
        s=(pr[i-1]+pi[i-1])*(pr[1]+pi[1]);
        pr[i]=p-q; pi[i]=s-p-q;
      }
    for (it=0; it<=n-2; it=it+2)
      { vr=fr[it]; vi=fi[it];
        fr[it]=vr+fr[it+1]; fi[it]=vi+fi[it+1];
        fr[it+1]=vr-fr[it+1]; fi[it+1]=vi-fi[it+1];
      }
    m=n/2; nv=2;
    for (l0=k-2; l0>=0; l0--)
      { m=m/2; nv=2*nv;
        for (it=0; it<=(m-1)*nv; it=it+nv)
          for (j=0; j<=(nv/2)-1; j++)
            { p=pr[m*j]*fr[it+j+nv/2];
              q=pi[m*j]*fi[it+j+nv/2];
              s=pr[m*j]+pi[m*j];
              s=s*(fr[it+j+nv/2]+fi[it+j+nv/2]);
              poddr=p-q; poddi=s-p-q;
              fr[it+j+nv/2]=fr[it+j]-poddr;
              fi[it+j+nv/2]=fi[it+j]-poddi;
              fr[it+j]=fr[it+j]+poddr;
              fi[it+j]=fi[it+j]+poddi;
            }
      }
    if (l!=0)
      for (i=0; i<=n-1; i++)
        { fr[i]=fr[i]/(1.0*n);
          fi[i]=fi[i]/(1.0*n);
        }
    if (il!=0)
      for (i=0; i<=n-1; i++)
        { pr[i]=sqrt(fr[i]*fr[i]+fi[i]*fi[i]);
          if (fabs(fr[i])<0.000001*fabs(fi[i]))
            { if ((fi[i]*fr[i])>0) pi[i]=90.0;
              else pi[i]=-90.0;
            }
          else
            pi[i]=atan(fi[i]/fr[i])*360.0/6.283185306;
        }
	for(i=0;i<n;i++)
	{
		CA[i].re=pr[i];
		CA[i].im=pi[i];
	}
    
	  for(i=0;i<n;i++)
	  {
		  CB[i].re=fr[i];
		  CB[i].im=fi[i];
	  }
    return;
  }
/////////////////////////////////////
void  main()
{
    complex a,b;
	a.re=2;
	a.im=3;
	b=a;
	b=exp(a);
	cout<<b;
	int n=64,i,j;
	double deltaT=0.1,R;
	ifstream ifile("d:\\work\\tj.fft");
	ofstream ofile("d:\\work\\tj.out");
	/*for(i=0;i<n;i++)
       ofile<<exp(-i*deltaT)<<endl;
	
	complex q;
	double L;
	int j;
	for(L=0;L<n;L++)
	{
		ifile.seekg(ios::beg);
		q=0;
		for(j=0;j<n;j++)
		{
			ifile>>R;
			q+=R*exp(-2*M_PI*L*Zi*L*j/n);
		}
		q*=deltaT;
		ofile<<q<<endl;
	}
	CMatrix<int> A;
	A.Ones(3);
	cout<<A;
    CMatrix<complex> B;
	B.Ones(3);
	cout<<B;
*/
	complex CA[64];
	complex p[64],f[64];
    for(i=0;i<64;i++)
	{
		ifile>>p[i];
	}
	Fft(p,64,6,f,1,1);
	for(i=0;i<=15;i++)
	{
		for(j=0;j<=3;j++)
			ofile<<f[4*i+j]<<"    ";
		ofile<<endl;
	}
	ofile<<endl<<endl<<endl;

for(i=0;i<=15;i++)
	{
		for(j=0;j<=3;j++)
			ofile<<p[4*i+j]<<"    ";
		ofile<<endl;
	}



	return ;
};





