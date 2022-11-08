#include <stdio.h>
#include "lista.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

//-----------------Funções Básicas--------------------
static link NEWnode( vertex w, link next) {
   link a = malloc( sizeof (struct node));
   a->w = w;
   a->next = next;
   return a;
}


Graph GRAPHinit( int V) {
   Graph G = malloc( sizeof *G);
   G->V = V;
   G->A = 0;
   G->adj = malloc( V * sizeof (link));
   for (vertex v = 0; v < V; ++v)
      G->adj[v] = NULL;
   return G;
}


void GRAPHinsertArc( Graph G, vertex v, vertex w) {
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (a->w == w) 
         return;
      G->adj[v] = NEWnode( w, G->adj[v]);
      G->A++;
}

//Exercício para criação desta função
void GRAPHremoveArc (Graph G, vertex v, vertex w) {
  link p, q = NULL;
    for (p = G->adj[v]; p != NULL; p = p->next) {
      if (p->w == w) {
        if (q == NULL)
          G->adj[v] = p->next;
        else
          q->next = p->next;
        p = NULL;
        free(p);
        return;
      }
      q = p;
    }
}


void GRAPHshow( Graph G) {
   vertex v;
   for (v = 0; v < G->V; ++v) {
      printf("%d: ", v);
      for (link a = G->adj[v]; a != NULL; a = a->next)
         printf("%2d ", a->w);
      printf("\n");
   }
}

//---------------Grafos Aleatórios e por Arquivo---------------------
//RAND_MAX = 2147483647
Graph GRAPHrand (int V, int A) {
   
   Graph G = GRAPHinit (V);
   
   srand(time(NULL));
   while (G->A < A) {
      vertex v = rand() % V;
      vertex w = rand() % V;
      if (v != w)
      GRAPHinsertArc (G, v, w);
   }
   return G;
}

Graph READdataIn(){
   Graph G;
   vertex v, w, V, A;

   scanf("%d", &V);
   G = GRAPHinit(V);

   scanf("%d", &A);
   for (int i = 0; i < A; ++i){
      scanf("%d-%d", &v, &w);
      GRAPHinsertArc(G, v, w);
   }

   return G;
}

//-----------------Numeração Topológica--------------------
bool isTopoNumbering( Graph G, int topo[]) {
   for (vertex v = 0; v < G->V; ++v)
      for (link a = G->adj[v]; a != NULL; a = a->next)
         if (topo[v] >= topo[a->w])
            return false;
   return true;
}

int topo[1000];

bool topol( Graph G) { 
   // implementação muito ineficiente...
   for (vertex v = 0; v < G->V; ++v) 
    topo[v] = -1;
   int cnt = 0;
   vertex v;
   while (cnt < G->V) {
      for (v = 0; v < G->V; ++v) 
         if (GRAPHindeg( G, v) == 0 && topo[v] == -1)
            break;
      if (v >= G->V) return false;
      // v é fonte
      topo[v] = cnt++;
      for (link a = G->adj[v]; a != NULL; a = a->next)
         GRAPHremoveArc( G, v, a->w);
   }
   return true;
}

void SHOWtopo(Graph G){
   printf("topo: [ ");
   for (vertex v = 0; v < G->V; v++){
      printf("%d ", topo[v]);
   }
   printf("]\n");
}

//-----------------EF1--------------------


int GRAPHindeg (Graph G, vertex v){
  int indeg = 0;
  
  for (vertex q = 0; q < G->V; ++q)
    for (link a = G->adj[q]; a != NULL; a = a->next)
      if(a->w == v)
        indeg++;
      
  return indeg;
}

int GRAPHoutdeg (Graph G, vertex v){
  int outdeg = 0;
  
  for (link a = G->adj[v]; a != NULL; a = a->next)
    outdeg++;

  return outdeg;
}

void IsSink(Graph G){
  vertex v;
  vertex isSink[G->V];

  for (int i = 0; i < G->V; ++i)
    isSink[i] = -1;
   
  for (v = 0; v < G->V; ++v){
    if (G->adj[v] != NULL){
        isSink[v] = 0;
    }
    for (vertex q = 0; (q < G->V) && (isSink[v] == -1); ++q){
      for (link a = G->adj[q]; a != NULL; a = a->next)
        if(a->w == v){
          isSink[v] = 1;
          break;
        }
    }
  }

  printf("\nSink: ");
  for(int i = 0; i < G->V; ++i)
    if (isSink[i] == 1)
       printf("%d ", i); 
}

void IsSource(Graph G){
  vertex v;
  vertex isSource[G->V];

  for (int i = 0; i < G->V; ++i)
    isSource[i] = 1;
   
  for (v = 0; v < G->V; ++v){
    if (G->adj[v] == NULL){
        isSource[v] = 0;
      }
    for (vertex q = 0; (q < G->V) && (isSource[v] == 1); ++q){
      for (link a = G->adj[q]; a != NULL; a = a->next)
        if(a->w == v){
          isSource[v] = 0;
          break;
        }
    }
  }

  printf("\nSource: ");
  for(int i = 0; i < G->V; ++i)
    if (isSource[i] == 1)
       printf("%d ", i); 
}

void UGRAPHdegrees(Graph G){
  vertex grau[G->V];

  for (int i = 0; i < G->V; ++i)
      grau[i] = 0;

  for (vertex v = 0; v < G->V; ++v)
    for (link a = G->adj[v]; a != NULL; a = a->next)
      grau[v]++;

  printf("\ngraus\n");
  for(int i = 0; i < G->V; ++i)
      printf("%d: %d\n", i, grau[i]); 
}

bool GRAPHisUndirected(Graph G){
  int cont, q;
  
  for (vertex v = 0; v < G->V; ++v){
    cont = 0;
    for (link a = G->adj[v]; a != NULL; a = a->next){
      q = a->w;
      for (link b = G->adj[q]; b != NULL; b = b->next)
        if (b->w == v)
          cont = 1;
      if (cont == 0)
        return false;
    }
  }
    
  return true;
}

//----------------Acessibilidade-------------------

/* Para simplificar, suporemos que nossos grafos têm no máximo 1000 vértices e 
trataremos o vetor visited[] como variável global. */
static int visited[1000];

/* A função GRAPHreach() recebe vértices s e t de um grafo G e decide se t está ao 
alcance de s ou não. */

static void reachR( Graph G, vertex v) { 
   visited[v] = 1;
   for (link a = G->adj[v]; a != NULL; a = a->next)
      if (visited[a->w] == 0)
         reachR( G, a->w);
}

bool GRAPHreach( Graph G, vertex s, vertex t) { 
   for (vertex v = 0; v < G->V; ++v)
      visited[v] = 0;
   reachR( G, s);
   if (visited[t] == 0) 
    return false;
   else 
    return true;
}


//--------------------------------------------

static char ident[100];
static int cnt;
int pre[1000];
vertex pa[1000];

void GRAPHdfs_rastro (Graph G) {
  vertex v;
  for (v = 0; v < G->V; ++v)
    pre[v] = -1;
  
  for (v = 0; v < G->V; ++v)
    if (pre[v] == -1) {
      pa[v] = v;
      printf("%d dfsR(G,%d)\n", v, v);
      dfsR_rastro (G, v);
  }
}

static void dfsR_rastro (Graph G, vertex v) {
  link a;
  pre[v] = cnt++;
  for (a = G->adj[v]; a != NULL; a = a->next) {
    vertex w = a->w;
    if (pre[w] == -1) {
      pa[w] = v;
      printf("%s%d-%d dfsR(G,%d) \n", ident, v, w, w);
      strcat(ident, ". ");
      dfsR_rastro (G, w);
    }
     else
       printf("%s%d-%d \n", ident, v, w);
  }
  printf("%s%d\n", ident, v);
  ident[strlen(ident) - 2] = '\0';
}

static int cntt, post[1000];

static void dfsR3( Graph G, vertex v) {
  pre[v] = cnt++;
  for (link a = G->adj[v]; a != NULL; a = a->next)
    if (pre[a->w] == -1) {
      pa[a->w] = v; // v é pai de a->w
      dfsR3( G, a->w);
    }
  post[v] = cntt++;
}

void GRAPHdfs3( Graph G) {
  cnt = cntt = 0;
  for (vertex v = 0; v < G->V; ++v)
    pre[v] = -1;
  for (vertex v = 0; v < G->V; ++v)
    if (pre[v] == -1) {
      pa[v] = v; // v é uma raiz
      dfsR3( G, v); // nova etapa
    }
}

void ClassificaArcos(Graph G){
  link a;
  vertex v, w;
  printf("Classificacao dos Arcos\n");
  for(v = 0; v < G->V; v++)
    for (a = G->adj[v]; a != NULL; a = a->next){
      w = a->w;
      //printf("\n%d-%d ", v, a->w);
      if (pre[v] < pre[w] && post[w] < post[v] && pa[w] == v)
        printf("%d-%d arborescencia\n", v, w);
      else if (pre[v] > pre[w] && post[v] < post[w])
        printf("%d-%d retorno\n", v, w);
      else if (pre[v] < pre[w] && post[v] > post[w])
        printf("%d-%d avanco\n", v, w);
      else if ((pre[w] < pre[v] && post[w] < post[v]) &&
              (pre[v] > pre[w] && post[v] > post[w]))
        printf("%d-%d cruzado\n", v, w);
  }
}


void IMPRIME_pre_post(Graph G){
  printf("      ");
  for (int i = 0; i < G->V ; ++i){
    printf("%d ", i);
  }
  printf("\n");

  printf("pre : ");
  for (int i = 0; i < G->V ; ++i){
    printf("%d ", pre[i]);
  }
  printf("\n");

  printf("post: ");
  for (int i = 0; i < G->V ; ++i){
    printf("%d ", post[i]);
  }
  printf("\n");

  printf("pa:   ");
  for (int i = 0; i < G->V ; ++i){
    printf("%d ", pa[i]);
  }
  printf("\n");
}
