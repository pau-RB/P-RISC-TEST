#define ST_MAX  16
#define SEG_SZ  256

#include"../API/api.h"
#include"../MMIO/mmio.h"
#include"../API/fixedpoint.h"
#include"../data/bivec_0010_001.h"

int Z[VSZ] = {1};

int saxpi() {
	for (int i = 0; i < VSZ-SEG_SZ; ++i)
		Z[i] = fadd(VECX[i],fmul(itof(73),VECY[i]));
}

int main() {

	Z[0] = 0;

	int saxpiSZ(int I) {
		for (int i = I; i < I+SEG_SZ; ++i)
			Z[i] = fadd(VECX[i],fmul(itof(73),VECY[i]));
	}

	// Parallel SAXPI
	block1D(0,VSZ-SEG_SZ,SEG_SZ,&saxpiSZ);
	print_MSR('E');
	print_CTR('E');

	// Check SAXPI
	for (int i = 0; i < VSZ-SEG_SZ; ++i)
		if(Z[i] != fadd(VECX[i],fmul(itof(73),VECY[i]))) {
			print_MSG('F');
			print_HEX(i);
			return 1;
		}

	print_MSG('P');

	return 0;

}
