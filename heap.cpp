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

int extractMin(HEAP* heap, int flag)
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
    if (flag == 1)
        printf("Delete vertex %d, key=%12.4f\n", minimum->vertex, minimum->key);
    return minimum->vertex;
}

HEAP* decreaseKey(HEAP* heap, int pos, int newKey, int flag)
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
        }
        else
        {
            heap->H[pos]->key = newKey;
            int parent = pos / 2;
            if (pos > 1 && heap->H[pos]->key < heap->H[parent]->key)
            {
                heap = MovingUp(heap, pos);
            }
            while(parent > 1 && heap->H[pos]->key < heap->H[parent]->key)
            {
                parent = parent / 2;
                heap = MovingUp(heap, parent);
            }
            if (flag == 1)
                printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", pos, heap->H[pos]->key, newKey);
        }
    }
    return heap;

}

int getVertexIndex(HEAP* heap, int id)
{
    if (heap != NULL)
    {
        for (int i = 1; i < heap->size + 1; i++)
        {
            if (heap->H[i]->vertex_ID == id)
            {
                return i;
            }
        }
    }
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

