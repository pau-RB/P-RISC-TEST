#include"../API/api.h"
#include"../MMIO/mmio.h"
#include"../data/mat_0032_001.h"

#define MM_THD  16

int C[MSZ][MSZ] = {1};

int mmt16(int I, int J) {
	for (int i = I; i < I+16; ++i)
		for (int j = J; j < J+16; ++j)
			for (int k = 0; k < MSZ; ++k)
				C[i][j]+=A[i][k]*B[j][k];
}

int main() {

	C[0][0] = 0;

	// Parallel AxBt

	print_MSR('S');
	block2D(0,MSZ,16,0,MSZ,16,&mmt16);
	print_MSR('E');

	// Sequential AxBt

	for (int i = 0; i < MSZ; ++i)
		for (int j = 0; j < MSZ; ++j)
			for (int k = 0; k < MSZ; ++k)
				C[i][j]-=A[i][k]*B[j][k];

	// Check AxBt

	for (int i = 0; i < MSZ; ++i)
		for (int j = 0; j < MSZ; ++j)
			if(C[i][j]!=0) {
				print_MSG('F');
				print_HEX(i);
				print_HEX(j);
				print_HEX(C[i][j]);
				return 1;
			}

	print_MSG('P');

	return 0;

}