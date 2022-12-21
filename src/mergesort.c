#include"../API/api.h"
#include"../MMIO/mmio.h"
#include"../data/vec01.h"

#define MS_THD  3
#define FRAME_SIZE 128
#define STACK_SIZE 1024

#define VSZ 2000

int SCR[VSZ] = {1};

char child_stack[MS_THD][STACK_SIZE]={1};
char child_frame[MS_THD][FRAME_SIZE]={1};

//////////// HEADERS ////////////

void merge(int vec[], int scr[], int l, int m, int r);
void mergesort(int vec[], int scr[], int l, int r);
void mergesortN(int vec[], int scr[], int id, int l, int r);

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

// Pre : Child stack and frames are interpreted as a complete
//       binary tree and the subtree hanging from id is available
// Post: The partial vector [l,r) is sorted by parallel mergesort
void mergesortN(int vec[], int scr[], int id, int l, int r) {

    if(r-l<=1)
        return;

    int m = (l+r)/2;

    int child_l = 2*id+1;
    int child_r = 2*id+2;
    int frame   = id;

    if(frame < MS_THD)
        fork5((int)vec,(int)scr,child_l,l,m,(void*)mergesortN,child_frame[frame],child_stack[frame]+STACK_SIZE);
    else
        mergesortN(vec,scr,child_l,l,m);

    mergesortN(vec,scr,child_r,m,r);

    if(frame < MS_THD)
        wait(child_frame[frame]);

    merge(vec,scr,l,m,r);

}

//////////// MAIN ////////////

int main() {

    printLSR('S');
    mergesortN(VEC,SCR,0,0,VSZ);
    printLSR('E');

    for(int i = 0; i < VSZ-1; ++i) {
        if(VEC[i] > VEC[i+1]) {
            putchar('F');
            return -1;
        }
    }

    putchar('P');

}