#include"../MMIO/mmio.h"
#include"../data/mat_0032_001.h"

int C[MSZ][MSZ] = {1};

int main() {

	C[0][0] = 0;

	// Parallel AxBt

	print_MSR('S');

	// Sequential AxBt

	for (int i = 0; i < MSZ; ++i)
		for (int j = 0; j < MSZ; ++j)
			for (int k = 0; k < MSZ; ++k)
				C[i][j]+=A[i][k]*B[j][k];

	print_MSR('E');

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