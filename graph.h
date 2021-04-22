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
	int distance;
	VERTEX* previous;
}VERTEX;

void graph(int argc, char* argv[]);
VERTEX** initializeSingleSource(EDGE*** someArrays, int vertex);
int getWeight(int u, int v);
VERTEX** relax(int u, int v);

#endif
