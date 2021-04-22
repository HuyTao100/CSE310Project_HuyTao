#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <regex>
#include "graph.h"

using namespace std;

int vertices, edges;
EDGE*** arrays;
VERTEX** vertexArray;
VERTEX** priorityQueue;
int numInQueue = 0;

 void graph(int argc, char* argv[])
{
	const char* graph = argv[1];
	const char* direction = argv[2];

	if (strcmp(direction, "directed") != 0 && strcmp(direction, "undirected") != 0)
		throw invalid_argument("graph direction invalid or not specified\n");

	FILE* afile = fopen(graph, "r");
	if (!afile)
		throw invalid_argument("cannot open file for reading or file does not exist\n");

	fscanf(afile, "%d, %d", &vertices, &edges);
	EDGE*** someArray = new EDGE * *[vertices]; 
	VERTEX** someVertexArray = new VERTEX * [vertices];
	arrays = someArray;

	for (int i = 0; i < vertices; i++)
	{
		EDGE **array = new EDGE*[vertices];
		arrays[i] = array;
	}

	int edgeID, vertexU, vertexV;
	float weight;

	for (int i = 0; i < edges; i++)
	{
		int flag = 0;
		int flag2 = 0;
		fscanf(afile, "%d %d %d %f", &edgeID, &vertexU, &vertexV, &weight);
		EDGE* edge = (EDGE*)malloc(sizeof(EDGE));
		edge->edge_ID = edgeID;
		edge->vertex_u = vertexU;
		edge->vertex_v = vertexV;
		edge->weight = weight;
		if (strcmp(direction, "directed"))
		{
			EDGE**arrayToInsert = arrays[vertexU];
			for (int j = 0; j < vertices; j++)
			{
				if (arrayToInsert[j] == NULL && flag == 0)
				{
					arrayToInsert[j] = edge;
					flag = 1;
				}
				flag = 0;
			}
			arrays[vertexU] = arrayToInsert;
		}
		if (strcmp(direction, "undirected"))
		{
			EDGE** arrayToInsert = arrays[vertexU];
			EDGE** arrayToInsert2 = arrays[vertexV];
			for (int j = 0; j < vertices; j++)
			{
				if (arrayToInsert[j] == NULL && flag == 0)
				{
					arrayToInsert[j] = edge;
					flag = 1;
				}

				if (arrayToInsert2[j] == NULL && flag2 == 0)
				{
					edge->vertex_v = vertexU;
					edge->vertex_u = vertexV;
					arrayToInsert2[j] = edge;
					flag2 = 1;
				}
				arrays[vertexU] = arrayToInsert;
				arrays[vertexV] = arrayToInsert2;
				flag = 0;
				flag2 = 0;
			}
		}
		
	}

}

 VERTEX** initializeSingleSource(int vertex)
 {
	 for (int i = 0; i < vertices; i++)
	 {
		 VERTEX* someVertex = new VERTEX();
		 someVertex->vertex_ID = i;
		 someVertex->distance = INFINITY;
		 someVertex->previous = NULL;
		 vertexArray[i] = someVertex;
		 vertexArray[vertex]->distance = 0;
	 }
	 priorityQueue[numInQueue] = vertexArray[vertex];
	 numInQueue = numInQueue + 1;

	 return priorityQueue;
 }

 int getWeight(int u, int v)
 {
	 for (int i = 0; i < vertices; i++)
	 {
		 EDGE** searchVertex = arrays[i];
		 for (int j = 0; j < vertices; j++)
		 {
			 if (searchVertex[j] == NULL)
			 {
				 break;
			 }
			 if (searchVertex[j]->vertex_u == u && searchVertex[j]->vertex_v == v)
			 {
				 return searchVertex[j]->weight;
			 }

		 }
	 }
 }

 VERTEX** relax(int u, int v)
 {
	 if (vertexArray[v]->distance == INFINITY)
	 {
		 vertexArray[v]->distance = vertexArray[u]->distance + getWeight(u, v);
		 vertexArray[v]->previous = vertexArray[u];
		 priorityQueue[numInQueue] = vertexArray[v];
		 numInQueue = numInQueue + 1;
		 return priorityQueue;
	 }
	 else if (vertexArray[v]->distance > vertexArray[u]->distance + getWeight(u, v))
	 {
		 vertexArray[v]->distance = vertexArray[u]->distance + getWeight(u, v);
		 vertexArray[v]->previous = vertexArray[u];
		 return priorityQueue;
	 }
 }