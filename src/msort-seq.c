#include"../MMIO/mmio.h"
#include"../data/vec_0001_001.h"

int SCR[VSZ] = {1};

//////////// HEADERS ////////////

void merge(int vec[], int scr[], int l, int m, int r);
void mergesort(int vec[], int scr[], int l, int r);

//////////// MERGESORT ////////////

// Pre : The partial vectors [l,m) and [m,r) are sorted
// Post: The partial vector [l,r) is sorted by merging
void merge(int vec[], int scr[], int l, int m, int r) {

    int size = r-l;
    int p    = l;
    int q    = m;

    for (int i = 0; i < size; ++i) {
        if(p >= m)
            scr[l+i] = vec[q];
        else if(q >= r)
            scr[l+i] = vec[p];
        else if(vec[p] <= vec[q])
            {scr[l+i] = vec[p]; ++p;}
        else
            {scr[l+i] = vec[q]; ++q;}
    }

    for (int i = 0; i < size; ++i)
        vec[l+i] = scr[l+i];

}

// Pre : -
// Post: The partial vector [l,r) is sorted by sequential mergesort
void mergesort(int vec[], int scr[], int l, int r) {

    if(r-l<=1)
        return;
    int m = (l+r)/2;

    mergesort(vec,scr,l,m);
    mergesort(vec,scr,m,r);
    merge(vec,scr,l,m,r);

}

//////////// MAIN ////////////

int main() {

    print_MSR('S');
    mergesort(VEC,SCR,0,VSZ);
    print_MSR('E');

    for(int i = 0; i < VSZ-1; ++i) {
        if(VEC[i] > VEC[i+1]) {
            print_MSG('F');
            return -1;
        }
    }

    print_MSG('P');

}