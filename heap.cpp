#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "heap.h"

HEAP* Initialize(int n) {
    HEAP* heap = (HEAP*)calloc(1, sizeof(HEAP)); // Dynamic memory allocation
    if (heap != NULL)
    {
        heap->capacity = n;
        heap->size = 1;
        heap->H = (ElementT*)calloc(n + 1, sizeof(ElementT)); // Dynamic memory allocation
    }
    return heap;
}

void printHeap(HEAP* heap) {
    printf("capacity=%d, size=%d\n", heap->capacity, heap->size);
    if (heap->size > 0)
    {
        for (int i = 1; i <= heap->size - 1; i++)
        {
            printf("%d, ", heap->H[i]->key);
        }
        printf("%d\n", heap->H[heap->size]->key);
    }
}

void writeHeap(HEAP* heap)
{
    FILE* afile;
    afile = fopen("HEAPoutput.txt", "w");
    if (!afile) {
        printf("Error: cannot write\n");
        return;
    }
    else {
        fprintf(afile, "%d\n", heap->size);
        for (int i = 1; i <= heap->size; i++) {
            fprintf(afile, "%d\n", heap->H[i]->key);
        }
    }
    fclose(afile);
}

void insert(HEAP* heap, ELEMENT* element)
{
    if (heap == NULL || heap->size == heap->capacity)
    {
        printf("Error: heap is NULL or full\n");
    }
    heap->size++;
    int i = heap->size;
    while (i > 1 && heap->H[i / 2]->key > element->key)
    {
        heap->H[i] = heap->H[i / 2];
        i = i / 2;
    }
    heap->H[i] = element;
}

int extractMin(HEAP* heap)
{
    int minimum;
    int calls;
    if (heap->size < 1)
    {
        printf("Error: heap is EMPTY\n");
    }
    else
    {
        minimum = heap->H[1]->key;
        heap->H[1] = heap->H[heap->size];
        heap->size--;
        calls = minHeapify(heap, 1);
        printf("Deleted key: %d\n", minimum);
    }
    return calls;
}

void decreaseKey(HEAP* heap, int i, int key)
{
    if (heap == NULL || i < 1 || i > heap->size || key >= heap->H[i]->key)
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
