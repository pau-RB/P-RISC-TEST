#ifndef FIXEDPOINT_H
#define FIXEDPOINT_H

#define BASE 8192

//////////// DEFINE TYPES ////////////

typedef int fixed;

typedef struct {
	fixed re;
	fixed im;
} complex;

// int to fixed
inline fixed itof (int a)
	{ return a*BASE; }

// fixed to int
inline int ftoi (fixed a)
	{ return a/BASE; }

// int to complex
inline complex itoc(int r, int i)
	{ complex res = {r*BASE,i*BASE}; return res; }

// fixed to complex
inline complex ftoc(fixed r, fixed i)
	{ complex res = {r,i}; return res; }

//////////// DEFINE FIXED OPERATORS ////////////

// fixed add
inline fixed fadd (fixed a, fixed b) 
	{ return a+b; }

// fixed sub
inline fixed fsub (fixed a, fixed b) 
	{ return a-b; }

// fixed mul
inline fixed fmul (fixed a, fixed b) 
	{ return a*b/BASE; }

// fixed div
inline fixed fdiv (fixed a, fixed b) 
	{ return a/b*BASE; }

//////////// DEFINE COMPLEX-FIXED OPERATORS ////////////

// square of mod of complex
inline fixed cmsq(complex a)
	{ return (a.re*a.re+a.im*a.im)/BASE; }

// complex times fixed
inline complex cfmul (complex a, fixed b)
	{ complex res = {fmul(a.re,b), fmul(a.im,b)}; return res; }

// complex div fixed
inline complex cfdiv (complex a, fixed b)
	{ complex res = {fdiv(a.re,b), fdiv(a.im,b)}; return res; }

//////////// DEFINE COMPLEX OPERATORS ////////////

// complex add
inline complex cadd(complex a, complex b)
	{ return ftoc(a.re+b.re,a.im+b.im); }

// complex sub
inline complex csub(complex a, complex b)
	{ return ftoc(a.re-b.re,a.im-b.im); }

// complex mul
inline complex cmul(complex a, complex b)
	{ return ftoc((a.re*b.re-a.im*b.im)/BASE,(a.re*b.im+a.im*b.re)/BASE); }

// inverse of complex
inline complex cinv(complex a)
	{ complex res = {a.re/cmsq(a)*BASE,-a.im/cmsq(a)*BASE}; return res; }

// complex div
inline complex cdiv(complex a, complex b)
	{ return cmul(a,cinv(b)); }

#endif