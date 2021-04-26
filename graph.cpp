#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <regex>
#include "graph.h"
#include "heap.h"

using namespace std;
extern pVERTEX *V;

void printPath(int n, int source, int destination, int s, int t)
{
	PATH *pPATH;
	PATH *pNode;
	int u, v;

	if (V[t]->color == 0){
		if (destination < 1 || destination > n || t == destination){
			printf("No %d-%d path exists.\n", s, t);
			return;
		}else{
			printf("No %d-%d path has been computed.\n", s, t);
			return;
		}
	} else if (V[t]->color == 1){
		printf("Path not known to be shortest: <%d", s);
	} else if (V[t]->color == 2){
		printf("Shortest path: <%d", s);
	}

	pNode = (PATH *) malloc(sizeof(PATH));
	pNode->vertex = t;
	pNode->next = NULL;
	pPATH = pNode;
	v = pNode->vertex;
	while (V[v]->pi){
		u = V[v]->pi;
		pNode = (PATH *) malloc(sizeof(PATH));
		v = u;
		pNode->vertex = u;
		pPATH = pNode;
	}
	while (pPATH){
		pNode = pPATH;
		printf(", %d", pNode->vertex);
		pPATH = pPATH->next;
		free(pNode);
	}
	printf(">\n");
	printf("The path weight is: %12.4f\n", V[t]->key);
}

void dijkstra(int n, pEDGE *A, int s, int t, int flag)
{
	pEDGE edge;
	HEAP *heap;
	ELEMENT *element;

	int u, v;
	float w;

	int pos;

	for(int i = 1; i<=n; i++)
	{
		V[i]->color = 0;
		V[i]->pi = 0;
	}
	V[s]->key = 0;
	V[s]->color = 1;

	heap = Initialize(n);
	element = (pELEMENT) malloc(sizeof(ELEMENT));
	element->vertex = s;
	element->key = V[s]->key;
	heapInsert(heap, element);
	if (flag == 1){
		printf("Insert vertex %d, key=%12.4f\n", element->vertex, element->key);
	}
	
	while (heap->size != 0){
		element = extractMin(heap);
		if (flag == 1){
			printf("Delete vertex %d, key=%12.4f\n", element->vertex, element->key);
		}
		u = element->vertex;
		V[u]->color = 2;
		if (element->vertex == t){
			break;
		}
		free(element);

		edge = A[u];
		while(edge != NULL) {
			v = edge->vertex_v;
			w = edge->weight;
			if (V[v]->color == 0){
				V[v]->key = V[u]->key + w;
				V[v]->pi = u;
				V[v]->color = 1;
				pELEMENT velement = (pELEMENT) malloc(sizeof(ELEMENT));
				velement->vertex = v;
				velement->key = V[v]->key;
				heapInsert(heap, velement);
				if (flag == 1){
					printf("Insert vertex %d, key=%12.4f\n", velement->vertex, velement->key);
				}
			}
			else if(V[v]->key > V[u]->key + w)
			{
				V[v]->key = V[u]->key + w;
				V[v]->pi = u;
				pos = V[v]->pos;
				decreaseKey(heap, pos, V[v]->key, flag);
			}
			edge = edge->next;
		}
	}
}
