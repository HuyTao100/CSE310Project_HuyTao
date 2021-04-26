#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include "util.h"
#include "heap.h"
#include "graph.h"
using namespace std;
pVERTEX *V;

int main(int argc, char *argv[])
{
	int n, m, directed_graph;
	int edge_id, u, v, source, destination, flag;
	float w;
	int v_fscanf;
	pEDGE *A;
	pEDGE node;
	FILE *ifile;
	ifile = fopen(argv[1], "r");
	if (!ifile)
		throw invalid_argument("cannot open file for reading or file does not exist\n");
	if (0 == strcmp(argv[2], "directed\0")){
		directed_graph = 1;
	}
	if (0 == strcmp(argv[2], "undirected\0")){
		directed_graph = 0;
	}
	v_fscanf = fscanf(ifile, "%d %d", &n, &m);
	A = (pEDGE *) calloc(n+1, sizeof(pEDGE));

	for (int i = 1; i <= m; i++){
		v_fscanf = fscanf(ifile, "%d %d %d %f", &edge_id, &u, &v, &w);
	

	node = (pEDGE) malloc (sizeof(EDGE));
	node->vertex_u = u;
	node->vertex_v = v;
	node->weight = w;
	node->next = A[u];
	A[u] = node;

	if(!directed_graph){
		node = (pEDGE) malloc(sizeof(EDGE));
		node->vertex_u = v;
		node->vertex_v = u;
		node->weight = w;
		node->next = A[v];
	
		}
	}
	fclose(ifile);

	source = 0;
	destination = 0;
	V = (pVERTEX *) calloc(n+1, sizeof(pVERTEX));
	for(int i = 1; i <= n; i++)
	{
		V[i] = (VERTEX*) malloc (sizeof(VERTEX));
		V[i]->vertex = i;
	}
	int command, arg1, arg2, arg3;
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
			}else{
				source = arg1;
				destination = arg2;
				flag = arg3;
				dijkstra(n, A, source, destination, flag);
			}
			break;
		}
		case 2: //write path <s> <d>
		{
			cout << "Query: write path " << arg1 << " " << arg2 << "\n";
			if (source == 0)
			{
				cout << "Error: no path computation done\n";
				break;
			}
			else if (arg1 != source || (arg2 < 1 || arg2 > n) || arg1 == arg2)
			{
				cout << "Error: invalid source destination pair\n";
				break;
			}
			else{
				printPath(n, source, destination, arg1, arg2);
			}
			break;
		}
		case 3: //stop
		{
			cout << "Query: stop\n";
			//free all dynamically allocated memory
			free(A);
			exit(0);
		}
		default:
			break;
		}
	}
}