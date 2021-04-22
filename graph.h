#ifndef graph_H_
#define graph_H_

typedef struct TAG_EDGE {
	int edge_ID;
	int vertex_u;
	int vertex_v;
	int weight;
	struct Edge* next;
}EDGE;

typedef struct TAG_VERTEX {
	int vertex_ID;
	int distance;
	VERTEX* previous;
}VERTEX;

void graph(int argc, char* argv[]);
HEAP* initializeSingleSource(HEAP* Q, int vertex);
int getWeight(int u, int v);
HEAP* relax(HEAP* Q, int u, int v, float value, int flag);
HEAP* DijkstraSP(int s, int value);

#endif
