#ifndef graph_H
#define graph_H

typedef struct TAG_EDGE {
	int vertex_u;
	int vertex_v;
	int weight;
	TAG_EDGE *next;
}EDGE;

typedef EDGE* pEDGE;

typedef struct TAG_VERTEX {
	int color;
	int vertex;
	int pos;
	int pi;
	float key;
}VERTEX;
typedef VERTEX *pVERTEX;

typedef struct TAG_PATH{
	int vertex;
	TAG_PATH *next;
}PATH;
typedef PATH *pPATH;

void dijkstra(int n, pEDGE *A, int s, int t, int flag);
void printPath(int n, int source, int destination, int s, int t);
#endif
