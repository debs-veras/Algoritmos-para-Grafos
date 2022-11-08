#include <stdbool.h>
#define vertex int

typedef struct graph *Graph;
typedef struct node *link;

struct node{
	vertex w;
	link next;
};

struct graph{
	int V;
	int A;
	link *adj;
};

static link NEWnode(vertex w, link next);

Graph GRAPHinit(int V);
void GRAPHinsertArc(Graph G, vertex v, vertex w);
void GRAPHshow(Graph G);
Graph GRAPHrand(int V, int A);
void GRAPHremoveArc(Graph G, vertex v, vertex w);
bool isTopoNumbering(Graph G, int topo[]);
bool topol(Graph G);
void SHOWtopo();
Graph READdataIn();

int GRAPHindeg(Graph G, vertex v);
int GRAPHoutdeg(Graph G, vertex v);
void IsSink(Graph G);
void IsSource(Graph G);
void UGRAPHdegrees(Graph G);
bool GRAPHisUndirected(Graph G);

static void reachR(Graph G, vertex v);
bool GRAPHreach(Graph G, vertex s, vertex t);

static void dfsR_rastro(Graph G, vertex v);
static void dfsR3(Graph G, vertex v);
void GRAPHdfs3(Graph G);
void ClassificaArcos(Graph G);
void IMPRIME_pre_post(Graph G);