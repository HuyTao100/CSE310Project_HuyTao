#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <regex>
#include "graph.h"
#include "heap.h"

using namespace std;
extern VERTEX *V;
EDGE* someArray[INT16_MAX];

void graph(FILE* afile, int vertices, int edges, char direction[])
{
	for (int i = 0; i < vertices; i++)
	{
		EDGE* nullEdge = (EDGE*)malloc(sizeof(EDGE));
		nullEdge->next = NULL;
		nullEdge->vertex_u = -1;
		nullEdge->weight = -1;
		someArray[i] = nullEdge;
	}

	int edgeID, vertexU, vertexV;
	float Weight;

	for (int i = 0; i < edges; i++)
	{
		fscanf(afile, "%d %d %d %f", &edgeID, &vertexU, &vertexV, &Weight);
		if (strcmp(direction, "directed"))
		{
			if (someArray[vertexU]->vertex_u == -1)
			{
				someArray[vertexU]->edge_ID = edgeID;
				someArray[vertexU]->vertex_u = vertexU;
				someArray[vertexU]->weight = Weight;
			}
			someArray[vertexU]->next = someArray[vertexV];
		}
		else if (strcmp(direction, "undirected"))
		{
			if (someArray[vertexU]->vertex_u == -1)
			{
				someArray[vertexU]->edge_ID = edgeID;
				someArray[vertexU]->vertex_u = vertexU;
				someArray[vertexU]->weight = Weight;
			}
			someArray[vertexU]->next = someArray[vertexV];
			someArray[vertexV]->next = someArray[someArray[vertexU]->vertex_u];
		}
	}
	printf("hello");
}

void printPath(int n, int source, int destination, int s, int t)
{
	PATH *pPATH;
	PATH *pNODE;
}

HEAP* initializeSingleSource(int vertices, int vertex)
 {
	 for (int i = 0; i < vertices; i++)
	 {
		 VertexArray[i]->distance = -1;
		 VertexArray[i]->pi = -1;
	 }
	 VertexArray[vertex]->distance = 0;
	 VertexArray[vertex]->pos = 0;
	 HEAP* newHeap = Initialize(vertices);
	 newHeap->H[0]->vertex = vertex;
	 newHeap->H[0]->key = 0;
	 return newHeap;
 }

HEAP* relax(HEAP* Queue, int u, int v, float weight, int flag)
 {
	 if (VertexArray[u]->distance == -1)
	 {
		 VertexArray[v]->distance = VertexArray[u]->distance + weight;
		 VertexArray[v]->pi = u;
		 Queue->size++;
		 VertexArray[v]->pos = Queue->size;
		 Queue->H[Queue->size]->key = VertexArray[v]->distance;
		 Queue->H[Queue->size]->vertex = VertexArray[v]->pos;
		 if (flag == 1)
		 {
			 printf("Insert vertex %d, from %12.4f\n", v, Queue->H[Queue->size]->key);
		 }
	 }


	 else if (VertexArray[v]->distance > VertexArray[u]->distance + weight)
	 {
		 VertexArray[v]->distance = VertexArray[u]->distance + weight;
		 VertexArray[u]->pi = u;
		 int pos = VertexArray[v]->pos;
		 decreaseKey(Queue, pos, VertexArray[v]->distance, flag);
	 }

	 return Queue;
 }

void MovingUp(HEAP* heap, int pos)
{
	int parent; ElementT temp;

	if (pos > 1 && heap->H[pos]->key < heap->H[parent]->key)
	{
		parent = pos / 2;
		temp = heap->H[pos];
		heap->H[pos] = heap->H[parent];
		VertexArray[heap->H[pos]->vertex]->pos = pos;
		VertexArray[heap->H[parent]->vertex]->pos = parent;
		MovingUp(heap, parent);
	}
}

int dijkstra(int n, pEDGE *A, int s, int t, int flag)
{
	pEDGE edge;
	HEAP *heap;
	ELEMENT *element;

	int u, v, i;
	float w;

	int pos;
	int count_Heapify;

	for(int i = 1; i<=n; i++)
	{
		V[i].pi = 0;
	}
	V[s].distance = 0;

	heap = Initialize(n);
	element = (ELEMENT *) malloc(sizeof(ELEMENT));
	element->vertex = s;
	element->key = 0;
	insert(heap, element);
	if (flag == 1){
		printf("Insert vertex %d, key=%12.4f\n", element->vertex, element->key);
	}
	
	while (heap->size){
		element = extractMin(heap, &flag, &count_Heapify);
	}
}
