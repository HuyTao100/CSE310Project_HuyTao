#ifndef heap_H_
#define heap_H_
#include "graph.h"
#pragma warning(disable:4996)

typedef struct TAG_HEAP {
    int capacity;
    int size;
    VERTEX** H;
}HEAP;

HEAP* Initialize(int n, int s);
int extractMin(HEAP* heap, int flag);
void decreaseKey(HEAP* heap, int i, float value, int key);
int minHeapify(HEAP* heap, int i);
int buildMinHeap(HEAP* heap);
int getVertexIndex(HEAP* heap, int id);

#endif