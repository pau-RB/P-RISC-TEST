#include"../API/api.h"
#include"../MMIO/mmio.h"
#include"../data/vec_0001_001.h"

#define QS_THD  31
#define SS_THD  7
#define FRAME_SIZE 128
#define STACK_SIZE 8192

char child_stack[((QS_THD>SS_THD)?(QS_THD):(SS_THD))][STACK_SIZE]={1};
char child_frame[((QS_THD>SS_THD)?(QS_THD):(SS_THD))][FRAME_SIZE]={1};

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

// Pre :
// Post: swap
inline void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Pre :
// Post: Splits arr in elements lte and gt than pivot returns first gt
int split(int arr[], int len, int s, int pivot) {

    int i = 0;
    for(int j = 0; j < len; j+=s)
        if(arr[j] <= pivot)
            {swap(&arr[i],&arr[j]); i+=s;}
    return i;

}

// Pre :
// Post: Splits arr in elements lt and geq than pivot returns first geq
int splitN(int id, int arr[], int len, int s, int pivot) {

    if(id < SS_THD && s < len)
    {
        int child_l = 2*id+1;
        int child_r = 2*id+2;
                 fork5 (child_l, (int) &arr[0], len  , 2*s, pivot, (void*)splitN, child_frame[id], child_stack[id]+STACK_SIZE); 	 
        int m1 = splitN(child_r,       &arr[s], len-s, 2*s, pivot);
        int m2 = wait(child_frame[id]);
        return split(&arr[MIN(m1,m2)], MIN(MAX(m1,m2),len)-MIN(m1,m2), s, pivot) + MIN(m1,m2);
    }
    else
        return split(arr, len, s, pivot);

}

// Pre :
// Post: The partial vector [l,r) is sorted by recursive quicksort
void quicksort(int arr[], int len) {

    if(len<=1)
        return;

    int m = split(arr, len-1, 1, arr[len-1]);
    swap(&arr[m],&arr[len-1]);
    quicksort(&arr[0], m    );
    quicksort(&arr[m], len-m);

}

// Pre : Child stack and frames are interpreted as a complete
//       binary tree and the subtree hanging from id is available
// Post: The partial vector [l,r) is sorted by double parallel quicksort
void quicksortN(int id, int arr[], int len) {

    if(len<=1)
        return;

    if(id < QS_THD)
    {
        int m = splitN(id, arr, len-1, 1, arr[len-1]);
        int child_l = 2*id+1;
        int child_r = 2*id+2;
        fork3     (child_l, (int) &arr[0], m    , (void*)quicksortN, child_frame[id], child_stack[id]+STACK_SIZE);
        quicksortN(child_r,       &arr[m], len-m);
        wait(child_frame[id]);
    }
    else
        quicksort(arr,len);

}

//////////// MAIN ////////////

int main() {

    print_MSR('S');
    quicksortN(0,VEC, VSZ);
    print_MSR('E');

    for(int i = 0; i < VSZ-1; ++i) {
        if(VEC[i] > VEC[i+1]) {
            print_MSG('F');
            return -1;
        }
    }

    print_MSG('P');

}