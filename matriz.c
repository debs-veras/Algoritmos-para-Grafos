//Arquivo de implementações

#include <stdio.h>
#include "matriz.h"
#include <stdlib.h>
#include <time.h>


//-----------------Funções básicas--------------------
static int **MATRIXint( int r, int c, int val) { 
   int **m = malloc ( r * sizeof (int *) ); 
   for ( vertex i = 0; i < r; ++i) 
      m[i] = malloc ( c * sizeof (int) ); 
   for ( vertex i = 0; i < r; ++i) 
      for ( vertex j = 0; j < c; ++j) 
         m[i][j] = val; 
   return m; 
}

Graph GRAPHinit( int V) {
   Graph G = malloc ( sizeof *G);
   G->V = V; 
   G->A = 0; 
   G->adj = MATRIXint( V, V, 0);
   return G; 
}

void GRAPHinsertArc( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 0) {
      G->adj[v][w] = 1; 
      G->A++; 
   } 
}

void GRAPHremoveArc( Graph G, vertex v, vertex w) { 
   if (G->adj[v][w] == 1) {
      G->adj[v][w] = 0; 
      G->A--; 
   } 
} 

void GRAPHshow( Graph G) { 
   for ( vertex v = 0; v < G->V; ++v) { 
      printf ( "%2d:" , v); 
      for ( vertex w = 0; w < G->V; ++w) 
         if (G->adj[v][w] == 1) 
            printf ( " %2d" , w); 
         printf ( "\n" ); 
      } 
}

//-----------------Grafos Aleatórios--------------------
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
   for (vertex v = 0; v < G->V; ++v) topo[v] = -1;
   int cnt = 0;
   while (cnt < G->V) {
      for (vertex v = 0; v < G->V; ++v) 
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
