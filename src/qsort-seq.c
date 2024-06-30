#include"../MMIO/mmio.h"
#include"../data/vec_0001_001.h"

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
// Post: The partial vector [l,r) is sorted by recursive quicksort
void quicksort(int arr[], int len) {

    if(len<=1)
        return;

    int m = split(arr, len-1, 1, arr[len-1]);
    swap(&arr[m],&arr[len-1]);
    quicksort(&arr[0], m    );
    quicksort(&arr[m], len-m);

}

//////////// MAIN ////////////

int main() {

    print_MSR('S');
    quicksort(VEC, VSZ);
    print_MSR('E');

    for(int i = 0; i < VSZ-1; ++i) {
        if(VEC[i] > VEC[i+1]) {
            print_MSG('F');
            return -1;
        }
    }

    print_MSG('P');

}