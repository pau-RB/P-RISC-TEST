#include"../API/fixedpoint.h"
#include"../MMIO/mmio.h"

#define STEP 512
#define MAXITER 100
#define INFTY 4*BASE

int inside (fixed re, fixed im) {
	complex c = {re,im};
	complex z = {0,0};
	for(int i = 0; i < MAXITER; ++i)
		if(cmsq(z) > INFTY)
			return 0;
		else
			z = cadd(cmul(z,z),c);
	return 1;
}

int mandelbrot (int l, int r, int b, int t) {
	int total = 0;
	for (int i = l; i < r; i+=STEP)
		for (int j = b; j < t; j+=STEP)
			total += inside(i,j);
	return total;
}

int main() {

	print_MSR('S');
	int seq = mandelbrot(itof(-2),itof(1),itof(-1),itof(1));
	print_MSR('E');

	print_MSG('P');

	print_HEX(seq);

}