#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "util.h"
#include "heap.h"
#include "graph.h"
using namespace std;

int main(int argc, char *argv[])
{
	graph(argc, argv);
	FILE *ifile;
	int n, m, u;

	fscanf(ifile, "%d %d", &n, &m);
	int command, arg1, arg2, arg3, source;
	bool isComputed = false;
	HEAP *Q = NULL;
	HEAP* S = NULL;
	while (1)
	{
		command = nextCommand(&arg1, &arg2, &arg3);
		switch (command)
		{
		case 1: //find <source> <destination> <flag>
		{
			cout << "Query: find " << arg1 << " " << arg2 << " " << arg3 << "\n";
			if ((arg1 < 1 || arg1 > n) || arg2 == arg1 || (arg3 != 1 && arg3 != 0))
			{
				cout << "Error: invalid find query\n";
				break;
			}
			source = arg1;
			Q = Initialize(n, arg1);
			while (Q != NULL)
			{
				u = extractMin(Q, arg3);
			}
			isComputed = true;
			break;
		}
		case 2: //write path <s> <d>
		{
			cout << "Query: write path " << arg1 << " " << arg2 << "\n";
			if (isComputed == false)
			{
				cout << "Error: no path computation done\n";
				break;
			}
			if (arg1 != source || (arg2 < 1 || arg2 > n))
			{
				cout << "Error: invalid source destination pair\n";
				break;
			}

			Vertex v = findVertex(graph, arg2);
			int *paths = (int *)malloc(n * sizeof(int)); //dynamic memory allocation
			int count = 0;
			while (v != NULL && v->V->id != arg1)
			{
				paths[count] = v->V->id;
				count++;
				v = findVertex(graph, v->parent->id);
			}

			Vertex d = findVertex(graph, arg2);
			float weight = d->distance;

			if (weight == INT8_MAX && Q->size != 0)
			{
				printf("No %d-%d path has been computed.\n", arg1, arg2);
				break;
			}
			else if (v == NULL)
			{
				printf("No %d-%d path exists.\n", arg1, arg2);
				break;
			}
			paths[count] = v->V->id;
			count++;

			if (getVertexIndex(Q, arg2) != 0)
				cout << "Path not known to be shortest: <";
			else
				cout << "Shortest path: <";
			for (int i = count - 1; i > 0; i--)
			{
				cout << paths[i] << ", ";
			}
			cout << paths[0] << ">\n";
			printf("The path weight is: %12.4f\n", weight);
			break;
		}
		case 3: //stop
		{
			cout << "Query: stop\n";
			//free all dynamically allocated memory
			free(graph);
			free(Q);
			exit(0);
		}
		default:
			break;
		}
	}
	exit(0);
}