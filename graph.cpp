#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <regex>
#include "graph.h"
#include "heap.h"

using namespace std;
VERTEX** VertexArray;

EDGE** graph(int argc, char* argv[])
{
	int vertices, edges;
	const char* graph = argv[1];
	const char* direction = argv[2];

	if (strcmp(direction, "directed") != 0 && strcmp(direction, "undirected") != 0)
		throw invalid_argument("graph direction invalid or not specified\n");

	FILE* afile = fopen(graph, "r");
	if (!afile)
		throw invalid_argument("cannot open file for reading or file does not exist\n");

	fscanf(afile, "%d, %d", &vertices, &edges);
	EDGE** someArray = new EDGE * [vertices];
	EDGE* nullEdge = new EDGE;
	nullEdge->next = NULL;
	nullEdge->vertex_u = -1;
	nullEdge->weight = -1;
	for (int i = 0; i < vertices; i++)
	{
		someArray[i] = nullEdge;
	}

	int edgeID, vertexU, vertexV;
	float weight;

	for (int i = 0; i < edges; i++)
	{
		fscanf(afile, "%d %d %d %f", &edgeID, &vertexU, &vertexV, &weight);
		EDGE* edge = (EDGE*)malloc(sizeof(EDGE));
		edge->edge_ID = edgeID;
		edge->vertex_u = vertexU;
		edge->next = NULL;
		edge->weight = weight;
		if (strcmp(direction, "directed"))
		{
			if (someArray[vertexU]->vertex_u == -1)
			{
				someArray[vertexU] = edge;
			}
			edge->next = someArray[vertexV];
		}
		else if (strcmp(direction, "undirected"))
		{
			if (someArray[vertexU]->vertex_u == -1)
			{
				someArray[vertexU] = edge;
			}
			edge->next = someArray[vertexV];
			someArray[vertexV]->next = someArray[edge->vertex_u];
		}
	}
	return someArray;
}

void createVertexArray(EDGE** Graph, int vertices)
{
	VERTEX** vertexArray = new VERTEX*[vertices];
	VERTEX* nullVertex = new VERTEX;
	nullVertex->pos = -1;
	for (int i = 0; i < vertices; i++)
	{
		vertexArray[i] = nullVertex;
	}

	VertexArray = vertexArray;
	delete vertexArray;
}

HEAP* initializeSingleSource(int vertices, int vertex)
 {
	 for (int i = 0; i < vertices; i++)
	 {
		 VertexArray[i]->distance = INFINITY;
		 VertexArray[i]->pi = NULL;
	 }
	 VertexArray[vertex]->distance = 0;
	 VertexArray[vertex]->pos = 0;
	 HEAP* newHeap = Initialize(vertices);
	 newHeap->H[0]->vertex = vertex;
	 newHeap->H[0]->key = 0;
	 return newHeap;
 }

HEAP* relax(HEAP* Queue, int u, int v, int weight, int flag)
 {
	 if (VertexArray[u]->distance == INFINITY)
	 {
		 VertexArray[v]->distance = VertexArray[u]->distance + weight;
		 VertexArray[v]->pi = u;
		 Queue->size++;
		 VertexArray[v]->pos = Queue->size;
		 Queue->H[Queue->size]->key = VertexArray[v]->distance;
		 Queue->H[Queue->size]->vertex = VertexArray[v]->pos;
		 if (flag == 1)
		 {
			 printf("Insert vertex %d, from %12.4f to %12.4f\n", v);
		 }
	 }


	 else if (VertexArray[v]->distance > VertexArray[u]->distance + weight)
	 {
		 VertexArray[v]->distance = VertexArray[u]->distance + weight;
		 VertexArray[u]->pi = u;
		 int pos = VertexArray[v]->pos;
		 Queue = decreaseKey(Queue, pos, VertexArray[v]->distance, flag);
	 }

	 return Queue;
 }

HEAP* MovingUp(HEAP* heap, int pos)
{
	int parent; ElementT temp;

	parent = pos / 2;
	temp = heap->H[pos];
	heap->H[pos] = heap->H[parent];
	VertexArray[heap->H[pos]->vertex]->pos = pos;
	VertexArray[heap->H[parent]->vertex]->pos = parent;
}

void DijkstraSP(EDGE**Graph, int source, int destination, int vertices, float value, int weight, int flag)
{
	createVertexArray(Graph, vertices);
	HEAP* priorityQueue = initializeSingleSource(vertices, source);
	while (priorityQueue != NULL)
	{
		u = extractMin(priorityQueue, flag);
		numInQueue = numInQueue--;
		for (int i = 0; i < vertices; i++)
		{
			EDGE** someArray = arrays[i];
			for (int j = 0; j < vertices; j++)
			{
				if (someArray[j]->vertex_u == u->vertex_ID)
				{
					relax(priorityQueue, u->vertex_ID, someArray[j]->vertex_v, value, flag);
				}

				if (someArray[j]->vertex_v == u->vertex_ID)
				{
					relax(priorityQueue, someArray[j]->vertex_v, u->vertex_ID, value, flag);
				}
			}
		}
		
	}
	return priorityQueue;
}

VERTEX* getVertex(int i)
{
	return vertexArray[i];
}

VERTEX* findVertex(int i)
{
	EDGE** someArray = arrays[i];
	if (someArray[i]->vertex_u == i)
	{
		return vertexArray[someArray[i]->vertex_u];
	}
}