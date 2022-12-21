#include"../API/api.h"
#include"../MMIO/mmio.h"
#include"../data/vec01.h"

#define MAX_THD 8
#define QS_THD  7
#define FRAME_SIZE 128
#define STACK_SIZE 8192

#define VSZ 2000

char child_stack[MAX_THD][STACK_SIZE]={1};
char child_frame[MAX_THD][FRAME_SIZE]={1};

//////////// HEADERS ////////////

inline void swap(int* a, int* b);
inline int min(int a, int b);
inline int max(int a, int b);
int split(int vec[], int l, int r, int s, int pivot);
void quicksort(int vec[], int l, int r);
void quicksortN(int vec[], int id, int l, int r);

//////////// SEQUENTIAL ////////////

// Pre :
// Post: swap
inline void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Pre :
// Post: min
inline int min(int a, int b) {
    if(a < b)
        return a;
    else
        return b;
}

// Pre :
// Post: max
inline int max(int a, int b) {
    if(a > b)
        return a;
    else
        return b;
}

// Pre :
// Post: Splits vec in elements lt and geq than pivot returns first geq
int split(int vec[], int l, int r, int s, int pivot) {

    int i = l;
    for(int j = l; j < r; j+=s)
        if(vec[j] < pivot)
            {swap(&vec[i],&vec[j]); i+=s;}

    return i;

}

//////////// TOP LEVEL ////////////

// Pre :
// Post: The partial vector [l,r) is sorted by recursive quicksort
void quicksort(int vec[], int l, int r) {

    if(r-l<=1)
        return;

    int m = split(vec, l, r-1, 1, vec[r-1]);

    swap(&vec[m],&vec[r-1]);

    quicksort(vec, l, m);
    quicksort(vec, m+1, r);

}

// Pre : Child stack and frames are interpreted as a complete
//       binary tree and the subtree hanging from id is available
// Post: The partial vector [l,r) is sorted by double parallel quicksort
void quicksortN(int vec[], int id, int l, int r) {

    if(r-l<=1)
        return;

    int child_l = 2*id+1;
    int child_r = 2*id+2;

    int pivot = vec[r-1];
    int m1,m2;

    // Partial split (parallel)
    if(child_l < QS_THD)
        fork5((int)vec, l, r-1, 2, pivot, (void*)split,child_frame[child_l],child_stack[child_l]+STACK_SIZE);
    else
        m1 = split(vec, l, r-1, 2, pivot);

    if(child_r < QS_THD)
        fork5((int)vec, l+1, r-1, 2, pivot, (void*)split,child_frame[child_r],child_stack[child_r]+STACK_SIZE);
    else
        m2 = split(vec, l+1, r-1, 2, pivot);

    if(child_l < QS_THD)
        m1 = wait(child_frame[child_l]);

    if(child_r < QS_THD)
        m2 = wait(child_frame[child_r]);

    // Merge split (sequential)
    int m = split(vec, min(m1,m2), max(m1,m2), 1, pivot);
    swap(&vec[m],&vec[r-1]);

    // Recursive sort (parallel)

    if(child_l < QS_THD)
        fork4((int)vec, child_l, l, m, (void*)quicksortN,child_frame[child_l],child_stack[child_l]+STACK_SIZE);
    else
        quicksort(vec, l, m);

    if(child_r < QS_THD)
        fork4((int)vec, child_r, m+1, r, (void*)quicksortN,child_frame[child_r],child_stack[child_r]+STACK_SIZE);
    else
        quicksort(vec, m+1, r);

    if(child_l < QS_THD)
        wait(child_frame[child_l]);

    if(child_r < QS_THD)
        wait(child_frame[child_r]);

}

//////////// MAIN ////////////

int main() {

    printLSR('S');
    quicksortN(VEC, 0, 0, VSZ);
    printLSR('E');

    for(int i = 0; i < VSZ-1; ++i) {
        if(VEC[i] > VEC[i+1]) {
            putchar('F');
            return -1;
        }
    }

    putchar('P');

}