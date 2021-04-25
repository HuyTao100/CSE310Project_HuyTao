#ifndef graph_H
#define graph_H

typedef struct TAG_EDGE {
	int edge_ID;
	int vertex_u;
	int vertex_v;
	int weight;
	TAG_EDGE *next;
}EDGE;

typedef EDGE* pEDGE;

typedef struct TAG_VERTEX {
	int vertex;
	int pos;
	int pi;
	float key;
}VERTEX;
typedef VERTEX *pVERTEX;

void graph(FILE* afile, int vertices, int edges, char direction[]);
void createVertexArray(EDGE** Graph, int vertices);
HEAP* relax(HEAP* Queue, int u, int v, float weight, int flag);
HEAP* DijkstraSP(EDGE** Graph, int source, int destination, int vertices, int flag);
void MovingUp(HEAP* heap, int pos);

#endif
