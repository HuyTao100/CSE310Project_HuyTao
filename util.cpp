#include <stdio.h>
#include <string.h>
#include "util.h"
#include "heap.h"
#include <iostream>
#pragma warning(disable:4996)

int nextCommand(int* n, int* f, int *o)
{
    char c[1000];
    int command;
    while (1) {
        scanf("%s", c);
        if (strcmp(c, "find") == 0)
        {
            scanf("%d %d %d", n, f, o);
            command = 1;
            break;
        }
        if (strcmp(c, "write") == 0)
        {
            scanf("%s", c);
            if (strcmp(c, "path") == 0)
            {
                scanf("%d %d %d", n, f, o);
                command = 2;
                break;
            }
        }

        if (strcmp(c, "stop") == 0)
        {
            command = 3;
            break;
        }

        printf("Warning in nextCommand invalid input \n");
        break;
    }
    return command;
}