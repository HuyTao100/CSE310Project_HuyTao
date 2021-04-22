#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"
#include "graph.h"

HEAP* Initialize(int n, int s) {
    HEAP* heap = (HEAP*)calloc(1, sizeof(HEAP)); // Dynamic memory allocation
    if (heap != NULL)
    {
        heap->capacity = n;
        heap->size = 1;
        heap->H = initializeSingleSource(s);
    }
    return heap;
}

int extractMin(HEAP* heap, int flag)
{
    VERTEX* minimum;
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
        printf("Delete vertex %d, key=%12.4f\n", minimum->vertex_ID, minimum->distance);
    return minimum->vertex_ID;
}

void decreaseKey(HEAP* heap, int id, float value, int flag)
{
    if (heap == NULL || id < 1 || id > heap->size || value >= heap->H[id]->distance)
    {
        printf("Error: invalid call to DecreaseKey\n");
    }
    else
    {
        heap->H[i]->key = key;
        while (i > 1 && heap->H[i / 2]->key > heap->H[i]->key)
        {
            int temp = heap->H[i]->key;
            heap->H[i]->key = heap->H[i / 2]->key;
            heap->H[i / 2]->key = temp;
            i = i / 2;
        }
    }

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
