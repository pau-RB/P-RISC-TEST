#include "./MMIO/mmio.h"
#include "./data/mat_0032_001.h"

int C[MSZ][MSZ] = {1};
int D[MSZ][MSZ] = {1};

void mxm(int*A,int*B,int*C);

int main() {

  C[0][0] = 0;
  D[0][0] = 0;

  print_MSR('S');
  mxm((int*)A,(int*)B,(int*)C);
  print_MSR('E');

  for (int i = 0; i < MSZ; ++i)
    for (int j = 0; j < MSZ; ++j)
      for (int k = 0; k < MSZ; ++k)
        D[i][j]+=A[i][k]*B[k][j];

  for (int i = 0; i < MSZ; ++i)
    for (int j = 0; j < MSZ; ++j)
      if(C[i][j]!=D[i][j]) {
        print_MSG('F');
        print_HEX(i);
        print_HEX(j);
        print_HEX(C[i][j]);
        print_HEX(D[i][j]);
        return 1;
      }

  print_MSG('P');

  return 0;
}