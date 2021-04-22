#include <stdio.h>
#include "util.h"
#pragma warning(disable:4996)

int nextCommand(int* n, int* f)
{
    char c;
    while (1) {
        scanf("%c", &c);
        if (c == ' ' || c == '\t' || c == '\n') {
            continue;
        }
        if (c == 'S' || c == 's') {
            break;
        }
        if (c == 'C' || c == 'c') {
            scanf("%d", n);
            break;
        }
        if (c == 'R' || c == 'r') {
            scanf("%d", f);
            break;
        }
        if (c == 'P' || c == 'p') {
            break;
        }
        if (c == 'W' || c == 'w') {
            break;
        }
        if (c == 'I' || c == 'i') {
            scanf("%d", n);
            break;
        }
        if (c == 'D' || c == 'd') {
            scanf("%d", f);
            break;
        }
        if (c == 'K' || c == 'k') {
            scanf("%d", n);
            scanf("%d", f);
            break;
        }
    }
    return c;
}