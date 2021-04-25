#ifndef heap_H
#define heap_H
#include "graph.h"
#pragma warning(disable:4996)

typedef VERTEX ELEMENT;
typedef VERTEX *pELEMENT;

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
	pELEMENT* H;  /* pointer to pointers to elements */
} HEAP;

HEAP* Initialize(int n);
int extractMin(HEAP* heap, int flag);
int decreaseKey(HEAP* heap, int pos, float newKey, int flag);
int minHeapify(HEAP* heap, int i);
int buildMinHeap(HEAP* heap);
void insert(HEAP *heap, ELEMENT *element);

#endif