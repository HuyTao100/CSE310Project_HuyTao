#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"
#include "graph.h"

HEAP* Initialize(int n) 
{
    HEAP* myHeap = (HEAP*)malloc(sizeof(HEAP)); //dynamic memory allocation
    if (myHeap != NULL)
    {
        myHeap->capacity = n;
        myHeap->size = 0;
        myHeap->H = (ElementT*)malloc((n + 1) * sizeof(ElementT)); //dynamic memory allocation
    }
    return myHeap;
}

 extractMin(HEAP* heap, int flag)
{
    ElementT minimum;
    if (heap == NULL || heap->size < 1)
    {
        printf("Error: heap is NULL or empty\n");
    }
    else
    {
        minimum = heap->H[1];
        heap->H[1] = heap->H[heap->size];
        heap->size--;
        minHeapify(heap, 1);
    }
    return minimum->vertex;
}

int decreaseKey(HEAP* heap, int pos, float newKey, int flag)
{
    if (heap == NULL)
    {
        printf("Error: invalid call to DecreaseKey\n");
    }
    else
    {
        if (flag == 1)
				printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", pos, heap->H[pos]->key, newKey);
        if (pos < 1 || pos > heap->size || newKey >= heap->H[pos]->key)
        {
            printf("Error: invalid call to DecreaseKey\n");
            return 1;
        }
            heap->H[pos]->key = newKey;
            MovingUp(heap, pos);
            return 0;
    }

}
void insert(HEAP *heap, ELEMENT *element)
{
    if (heap == NULL || heap->size == heap->capacity)
    {
        printf("Error: heap is NULL or full\n");
    }
    heap->size++;
    int i = heap->size;
    while (i > 1 && heap->H[i/2]->key > element->key)
    {
        heap->H[i] = heap->H[i/2];
        i = i/2;
    }
    heap->H[i] = element;
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

int buildMinHeap(HEAP* heap)
{
    int calls = 0;
    int length = (heap->size) / 2;
    for (int i = length; i >= 1; i--)
    {
        calls += minHeapify(heap, i);
    }
    return calls;
}

