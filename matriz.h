//Arquivo de assinaturas

#define vertex int

struct graph {
	int V;
	int A;
	int **adj; 
};

typedef struct graph *Graph;

static int **MATRIXint( int r, int c, int val); 
Graph GRAPHinit( int V);
void GRAPHinsertArc( Graph G, vertex v, vertex w); 
void GRAPHremoveArc( Graph G, vertex v, vertex w);
void GRAPHshow( Graph G);
Graph GRAPHrand (int V, int A);
bool isTopoNumbering( Graph G, int topo[]);
bool topol( Graph G);
