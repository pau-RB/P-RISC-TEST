#define SEG_SZ  256

#include"../MMIO/mmio.h"
#include"../API/fixedpoint.h"
#include"../data/bivec_0010_001.h"

int Z[VSZ] = {1};

int saxpy() {
	for (int i = 0; i < VSZ-SEG_SZ; ++i)
		Z[i] = fadd(VECX[i],fmul(itof(73),VECY[i]));
}

int main() {

	Z[0] = 0;

	// Parallel SAXPY
	print_MSR('S');
	saxpy();
	print_MSR('E');

	// Check SAXPY
	for (int i = 0; i < VSZ-SEG_SZ; ++i)
		if(Z[i] != fadd(VECX[i],fmul(itof(73),VECY[i]))) {
			print_MSG('F');
			print_HEX(i);
			return 1;
		}

	print_MSG('P');

	return 0;

}
