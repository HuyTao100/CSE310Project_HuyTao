#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "util.h"
#include "heap.h"
#pragma warning(disable:4996)

int main()
{
    HEAP* heap;
    heap = NULL;
    char c;
    FILE* ifile;
    ElementT element;
    int i, v, n, f;
    while (1) {
        c = nextCommand(&n, &f);
        switch (c) {
        case 's':
        case 'S': exit(0);

        case 'c':
        case 'C':
            heap = Initialize(n);
            break;

        case 'r':
        case 'R':
            int aNum;
            ifile = fopen("HEAPinput.txt", "r");
            if (!ifile) {
                printf("Error: cannot open file for reading\n");
                break;
            }
            fscanf(ifile, "%d", &n);
            if (heap == NULL || heap->capacity < n) {
                printf("Error: heap overflow\n");
                break;
            }
            heap->size = 0;
            for (int i = 1; i <= n; i++) {
                fscanf(ifile, "%d", &aNum);
                element = (ElementT)malloc(sizeof(ELEMENT)); //Dynamic memory Allocation
                element->key = aNum;
                heap->H[i] = element;
                heap->size++;
            }
            v = buildMinHeap(heap);
            if (f == 1)
            {
                printf("Number of Heapify calls: %d\n", v);
            }
            break;

        case 'p':
        case 'P':
            if (heap == NULL) {
                printf("Error: cannot print\n");
                break;
            }
            else {
                printHeap(heap);
                break;
            }

        case 'w':
        case 'W':
            if (heap == NULL) {
                printf("Error: cannot write\n");
                break;
            }
            writeHeap(heap);
            break;

        case 'i':
        case 'I':
            if (heap == NULL || heap->size == heap->capacity) {
                printf("Error: heap is NULL or full\n");
                break;
            }
            element = (ElementT)malloc(sizeof(ELEMENT)); //Dynamic Memory Allocations
            element->key = n;
            insert(heap, element);
            break;

        case 'd':
        case 'D':
            if (heap == NULL || heap->size == 0)
            {
                printf("Error: heap is NULL or empty\n");
                break;
            }
            v = extractMin(heap);
            if (f == 1)
            {
                printf("Number of Heapify calls: %d\n", v);
            }
            break;

        case 'K':
            decreaseKey(heap, n, f);
            break;
        default: break;
        }
    }exit(0);
}