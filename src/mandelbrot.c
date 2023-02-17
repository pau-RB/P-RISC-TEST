#define ST_MAX 64
#define ST_STACK_SIZE 128

#include"../API/api.h"
#include"../MMIO/mmio.h"

#define BASE 8192
#define STEP 512
#define MAXITER 100
#define INFTY 4*BASE

typedef struct {
	int r;
	int i;
} Complex;

inline int fromint(int a)
	{ return BASE*a; }

inline Complex com(int r, int i)
	{ Complex res = {r,i}; return res; }

inline Complex add(Complex a, Complex b)
	{return com(a.r+b.r,a.i+b.i);}

inline Complex sub(Complex a, Complex b)
	{return com(a.r-b.r,a.i-b.i);}

inline Complex mul(Complex a, Complex b)
	{return com((a.r*b.r-a.i*b.i)/BASE,(a.r*b.i+a.i*b.r)/BASE);}

inline int modsq(Complex a)
	{return (a.r*a.r+a.i*a.i)/BASE;}

int inside(int r, int i) {
	Complex c = {r,i};
	Complex z = {0,0};
	for(int i = 0; i < MAXITER; ++i)
		if(modsq(z) > INFTY)
			return 0;
		else
			z = add(mul(z,z),c);
	return 1;
}

int mandelbrot(int l, int r, int b, int t) {
	int total = 0;
	for (int i = l; i < r; i+=STEP)
    	for (int j = b; j < t; j+=STEP)
    		total += inside(i,j);
    return total;
}

int mandelbrotN (int l, int r, int b, int t) {
	int sum (int a, int b) {return a+b;};
	return reduce2D(l,r,STEP,b,t,STEP,&inside,&sum);
}

int main() {

	print_MSR('S');
	int par = mandelbrotN(fromint(-2),fromint(1),fromint(-1),fromint(1));
    print_MSR('E');

	int seq = mandelbrot(fromint(-2),fromint(1),fromint(-1),fromint(1));

    if(par == seq)
    	print_MSG('P');
    else
    	print_MSG('F');

}