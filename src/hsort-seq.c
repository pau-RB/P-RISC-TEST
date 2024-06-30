#include"../MMIO/mmio.h"
#include"../data/vec_0001_001.h"

//////////// HEADERS ////////////

inline void swap(int* a, int* b);
void heapify(int vec[], int len, int node);

void heapsort();

//////////// SEQUENTIAL ////////////

// Pre :
// Post: swap
inline void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
}

// Pre : vec contains a complete binary tree and the subtrees
//       hanging from node are heaps
// Post: node is the root of a heap (merge both heaps)
void heapify(int vec[], int len, int node) {

    int max = node;

    int node_l = 2*node+1;
    int node_r = 2*node+2;

    if (node_l < len && vec[node_l] > vec[max])
        max = node_l;

    if (node_r < len && vec[node_r] > vec[max])
        max = node_r;

    if (max != node) {
        swap(&vec[node], &vec[max]);
        heapify(vec, len, max);
    }

}

//////////// TOP LEVEL ////////////

// Pre : vec contains a set of numbers
// Post: vec is sorted by standard heapsort
void heapsort(int vec[], int len) {

    for(int i = len/2-1; i >= 0; --i)
        heapify(vec, len, i);

    for (int i = len-1; i >= 0; --i) {
        swap(&vec[0], &vec[i]);
        heapify(vec, i, 0);
    }

}

//////////// MAIN ////////////

int main() {

    print_MSR('S');
    heapsort(VEC, VSZ);
    print_MSR('E');

    for(int i = 0; i < VSZ-1; ++i) {
        if(VEC[i] > VEC[i+1]) {
            print_MSG('F');
            return -1;
        }
    }

    print_MSG('P');

}