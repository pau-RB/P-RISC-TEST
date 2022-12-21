#include"../API/api.h"
#include"../MMIO/mmio.h"

#define MAX_THD 32
#define FRAME_SIZE 128
#define STACK_SIZE 128

#define BASE 8192
#define STEP 512
#define MAXITER 100
#define INFTY 4*BASE

char child_stack[MAX_THD][STACK_SIZE]={1};
char child_frame[MAX_THD][FRAME_SIZE]={1};
int busy[MAX_THD]={1};

typedef struct {
	int r;
	int i;
} Complex;

inline int fromint(int a) {
	return BASE*a;
}

inline Complex com(int r, int i) {
	Complex res = {r,i};
	return res;
}

inline Complex add(Complex a, Complex b)
	{return com(a.r+b.r,a.i+b.i);}

inline Complex sub(Complex a, Complex b)
	{return com(a.r-b.r,a.i-b.i);}

inline Complex mul(Complex a, Complex b)
	{return com((a.r*b.r-a.i*b.i)/BASE,(a.r*b.i+a.i*b.r)/BASE);}

inline int modsq(Complex a)
	{return (a.r*a.r+a.i*a.i)/BASE;}

int inside(Complex c) {
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
	for (int i = b; i < t; i+=STEP)
    	for (int j = l; j < r; j+=STEP)
    		total += inside(com(j,i));
    return total;
}

int mandelbrot4(int l, int r, int b, int t) {

	int total = 0;

	int h = l+(r-l)*9/16;
	int v = b+(t-b)*8/16;

	fork4(l,h,b,v,(void*)mandelbrot,child_frame[0],child_stack[0]+STACK_SIZE);
	fork4(l,h,v,t,(void*)mandelbrot,child_frame[1],child_stack[1]+STACK_SIZE);
	fork4(h,r,b,v,(void*)mandelbrot,child_frame[2],child_stack[2]+STACK_SIZE);
	fork4(h,r,v,t,(void*)mandelbrot,child_frame[3],child_stack[3]+STACK_SIZE);

	total+=wait(child_frame[0]);
    total+=wait(child_frame[1]);
    total+=wait(child_frame[2]);
    total+=wait(child_frame[3]);

    return total;

}

int mandelbrotN(int l, int r, int b, int t) {

	int thd   = 0;
	int total = 0;

	for(thd = 0; thd < MAX_THD; ++thd)
    	busy[thd] = 0;
	
	thd = 0;
	for (int i = b; i < t; i+=STEP) {
    	for (int j = l; j < r; j+=STEP) {
    		if(busy[thd])
    			{total += wait(child_frame[thd]); busy[thd] = 0;}
    		fork2(j,i,(void*)inside,child_frame[thd],child_stack[thd]+STACK_SIZE); busy[thd] = 1;
    		thd = (thd+1)%MAX_THD;
    	}
    }

    for(thd = 0; thd < MAX_THD; ++thd)
    	if(busy[thd])
	    	total += wait(child_frame[thd]);

    return total;
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
