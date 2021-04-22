#ifndef heap_H_
#define heap_H_
#pragma warning(disable:4996)

typedef struct TAG_VERTEX {
    int distance;
    VERTEX* previous;
}VERTEX;

typedef VERTEX* VertexT;

typedef struct TAG_HEAP {
    int capacity;
    int size;
    VertexT** H;
}HEAP;

HEAP* Initialize(int n);
void printHeap(HEAP* A);
void writeHeap(HEAP* A);
int extractMin(HEAP* heap);
void decreaseKey(HEAP* heap, int i, int key);
int minHeapify(HEAP* heap, int i);
int buildMinHeap(HEAP* heap);

#endif