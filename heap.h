#ifndef heap_H_
#define heap_H_
#include "graph.h"
#pragma warning(disable:4996)

typedef struct TAG_ELEMENT
{
	float key;
	int vertex;
} ELEMENT;

typedef ELEMENT* ElementT;

typedef struct TAG_HEAP
{
	int capacity; /* max size of the heap */
	int size;	  /* current size of the heap */
	ElementT* H;  /* pointer to pointers to elements */
} HEAP;

HEAP* Initialize(int n);
VERTEX* extractMin(HEAP* heap, int flag);
HEAP* decreaseKey(HEAP* heap, int id, float value, int flag)
int minHeapify(HEAP* heap, int i);
int buildMinHeap(HEAP* heap);
int getVertexIndex(HEAP* heap, int id);

#endif