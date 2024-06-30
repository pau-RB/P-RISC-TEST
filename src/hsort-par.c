#include"../API/api.h"
#include"../MMIO/mmio.h"
#include"../data/vec_0001_001.h"

#define FRAME_SIZE 128
#define STACK_SIZE 1024

char child_stack[STACK_SIZE]={1};
char child_frame[FRAME_SIZE]={1};

//////////// HEADERS ////////////

inline void swap(int* a, int* b);
void heapify(int vec[], int len, int node);

void heapify2L(int vec[], int len, int node);
void heapify2R(int vec[], int len, int node);

void heapsort2();

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

//////////// PARALLEL ////////////

// Pre : vec contains a complete binary tree and the subtrees
//       hanging from node and the left child of node are heaps
//
//              (?)
//              / \
//            (?)  H
//            / \
//           H   H
//
// Post: node is the root of a heap (merge the three heaps)
void heapify2L(int vec[], int len, int node) {

    int node_l  = 2*node+1;
    int node_r  = 2*node+2;
    int node_ll = 2*node_l+1;
    int node_lr = 2*node_l+2;

    int max = node;
    if (node_l < len && vec[node_l] > vec[max])
        max = node_l;
    if (node_r < len && vec[node_r] > vec[max])
        max = node_r;
    if (node_ll < len && vec[node_ll] > vec[max])
        max = node_ll;
    if (node_lr < len && vec[node_lr] > vec[max])
        max = node_lr;

    if (max != node)
        swap(&vec[node], &vec[max]);

    if(max == node)
        heapify(vec, len, node_l);
    else if (max == node_l)
        heapify(vec, len, node_l);
    else if(max == node_r)
        {
            fork3((int)vec, len, node_l, &heapify, child_frame, child_stack+STACK_SIZE);
            heapify(vec, len, node_r);
            wait(child_frame);
        }
    else if(max == node_ll)
        heapify2L(vec, len, node_l);
    else if(max == node_lr)
        heapify2R(vec, len, node_l);

}

// Pre : vec contains a complete binary tree and the subtrees
//       hanging from node and the right child of node are heaps
//
//              (?)
//              / \
//             H  (?)
//                / \
//               H   H
//
// Post: node is the root of a heap (merge the three heaps)
void heapify2R(int vec[], int len, int node) {

    int node_l  = 2*node+1;
    int node_r  = 2*node+2;
    int node_rl = 2*node_r+1;
    int node_rr = 2*node_r+2;

    int max = node;
    if (node_l < len && vec[node_l] > vec[max])
        max = node_l;
    if (node_r < len && vec[node_r] > vec[max])
        max = node_r;
    if (node_rl < len && vec[node_rl] > vec[max])
        max = node_rl;
    if (node_rr < len && vec[node_rr] > vec[max])
        max = node_rr;

    if (max != node)
        swap(&vec[node], &vec[max]);

    if(max == node)
        heapify(vec, len, node_r);
    else if (max == node_l)
        {
            fork3((int)vec, len, node_l, &heapify, child_frame, child_stack+STACK_SIZE);
            heapify(vec, len, node_r);
            wait(child_frame);
        }
    else if(max == node_r)
        heapify(vec, len, node_r);
    else if(max == node_rl)
        heapify2L(vec, len, node_r);
    else if(max == node_rr)
        heapify2R(vec, len, node_r);

}

//////////// TOP LEVEL ////////////

// Pre : vec contains a set of numbers
// Post: vec is sorted by parallel heapsort
void heapsort2(int vec[], int len) {

    for(int i = len/2-1; i >= 0; --i)
        heapify(vec, len, i);

    for (int i = len-1; i >= 2; i-=2) {
        if(vec[1]>vec[2]) {
            swap(&vec[0], &vec[i]);
            swap(&vec[1], &vec[i-1]);
            heapify2L(vec, i-1, 0);
        } else {
            swap(&vec[0], &vec[i]);
            swap(&vec[2], &vec[i-1]);
            heapify2R(vec, i-1, 0);
        }  
    }

    if(vec[0]>vec[1])
        swap(&vec[0], &vec[1]);

}

//////////// MAIN ////////////

int main() {

    print_MSR('S');
    heapsort2(VEC, VSZ);
    print_MSR('E');

    for(int i = 0; i < VSZ-1; ++i) {
        if(VEC[i] > VEC[i+1]) {
            print_MSG('F');
            return -1;
        }
    }

    print_MSG('P');

}