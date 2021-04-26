#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"
#include "graph.h"

extern pVERTEX *V;

HEAP* Initialize(int n) 
{
    HEAP* myHeap = (HEAP*)malloc(sizeof(HEAP)); //dynamic memory allocation
    if (myHeap != NULL)
    {
        myHeap->capacity = n;
        myHeap->size = 0;
        myHeap->H = (pELEMENT*)calloc(n + 1, sizeof(pELEMENT)); //dynamic memory allocation
    }
    return myHeap;
}

void heapFree(HEAP *heap)
{
    free(heap->H);
    free(heap);
}

pELEMENT extractMin(HEAP* heap)
{
    pELEMENT minimum, last;
    if (heap == NULL || heap->size < 1)
    {
        printf("Error: heap is NULL or empty\n");
        return NULL;
    }
        minimum = heap->H[1];
        last = heap->H[heap->size--];
        heap->H[1] = last;
        V[heap->H[1]->vertex]->pos = 1;    
        minHeapify(heap, 1);
        V[minimum->vertex]->pos = 0;
        return minimum;
}

int decreaseKey(HEAP* heap, int pos, float newKey, int flag)
{
    if (heap == NULL)
    {
        printf("Error: invalid call to DecreaseKey\n");
    }
    else
    {
        if (pos < 1 || pos > heap->size || newKey >= heap->H[pos]->key)
        {
            printf("Error: invalid call to DecreaseKey\n");
            return 1;
        }
        if (flag == 1)
        {
				printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", pos, heap->H[pos]->key, newKey);
        }
            heap->H[pos]->key = newKey;
            MovingUp(heap, pos);
            return 0;
        
    }
    return 1;
}
int heapInsert(HEAP *heap, pELEMENT element)
{
    if (heap->size >= heap->capacity)
    {
        printf("Error in heapInsert: Heap full...\n");
        return 1;
    }
    heap->size++;
    heap->H[heap->size] = element;
    V[heap->H[heap->size]->vertex]->pos = heap->size;

    MovingUp(heap, heap->size);

    return 0;
}

int minHeapify(HEAP* heap, int i) {
    int smallest, l, r;
    l = i * 2;
    r = (i * 2) + 1;
    int calls = 1;
    if (l <= heap->size && heap->H[l]->key < heap->H[i]->key)
    {
        smallest = l;
    }
    else
    {
        smallest = i;
    }
    if (r <= heap->size && heap->H[r]->key < heap->H[smallest]->key)
    {
        smallest = r;
    }
    if (smallest != i)
    {
        int temp = heap->H[i]->key;
        heap->H[i]->key = heap->H[smallest]->key;
        heap->H[smallest]->key = temp;
        calls += minHeapify(heap, smallest);
    }
    return calls;
}

void MovingUp(HEAP *heap, int pos)
{
    pELEMENT temp;
    int parent;

    parent = pos/2;
    if (pos > 1 && heap->H[pos]->key < heap->H[parent]->key)
    {
        temp = heap->H[pos];
        heap->H[pos] = heap->H[parent];
        heap->H[parent] = temp;
        V[heap->H[pos]->vertex]->pos = pos;
        V[heap->H[parent]->vertex]->pos = parent;
        MovingUp(heap, parent);
    }
}

