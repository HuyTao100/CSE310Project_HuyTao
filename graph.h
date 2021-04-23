#ifndef graph_H_
#define graph_H_
#include "heap.h"

typedef struct TAG_EDGE {
	int edge_ID;
	int vertex_u;
	int weight;
	TAG_EDGE *next;
}EDGE;

typedef EDGE* pEDGE;

typedef struct TAG_VERTEX {
	int pos;
	int pi;
	float distance;
}VERTEX;

EDGE** graph(int argc, char* argv[]);
VERTEX** createVertexArray(EDGE** G, int n);
HEAP* initializeSingleSource(HEAP* Q, int vertex);
int getWeight(int u, int v);
HEAP* relax(HEAP* Q, int u, int v, float value, int flag);
HEAP* DijkstraSP(int n, int s, float value, int flag);
VERTEX* findVertex(int i);
VERTEX* getVertex(int i);
HEAP* MovingUp(HEAP* heap, int pos);

#endif
