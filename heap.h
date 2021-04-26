#ifndef heap_H
#define heap_H

typedef struct TAG_ELEMENT{
    int vertex;
	float key;
}ELEMENT;

typedef ELEMENT *pELEMENT;

typedef struct TAG_HEAP
{
	int capacity; /* max size of the heap */
	int size;	  /* current size of the heap */
	pELEMENT* H;  /* pointer to pointers to elements */
}HEAP;

HEAP* Initialize(int n);
void heapFree(HEAP *heap);
pELEMENT extractMin(HEAP* heap);
int decreaseKey(HEAP* heap, int pos, float newKey, int flag);
int minHeapify(HEAP* heap, int i);
void MovingUp(HEAP *heap, int pos);
int heapInsert(HEAP *heap, pELEMENT);

#endif