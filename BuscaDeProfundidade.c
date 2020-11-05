#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define vertex int
pthread_t threads[2];


static int cnt;
int pre[100];

struct grafo {
   int V; 
   int A; 
   int **adj; 
};
typedef struct grafo *Grafo;

typedef struct node *link;
struct node { 
   vertex w; 
   link next; 
};

static link NEWnode( vertex w, link next) { 
   link a = malloc( sizeof (struct node));
   a->w = w; 
   a->next = next;     
   return a;                         
}

Grafo criaGrafo( int V) { 
   Grafo G = malloc( sizeof *G);
   G->V = V; 
   G->A = 0;
   G->adj = malloc( V * sizeof (link));
   for (vertex v = 0; v < V; ++v) 
      G->adj[v] = NULL;
   return G;
}

void inserirGrafo( Grafo G, vertex v, vertex w) { 
   for (link a = G->adj[v]; a != NULL; a = a->next) 
      if (a->w == w) return;
   G->adj[v] = NEWnode( w, G->adj[v]);
   G->A++;
}

void DFS( Grafo G, vertex v) 
{ 
   pre[v] = cnt++; 
   for (link a = G->adj[v]; a != NULL; a = a->next) {
      vertex w = a->w;
      if (pre[w] == -1)
         DFS( G, w); 
   }
}

void *grafoDFS( Grafo G) 
{ 
   cnt = 0;
   for (vertex v = 0; v < G->V; ++v) 
      pre[v] = -1;
   for (vertex v = 0; v < G->V; ++v)
      if (pre[v] == -1) 
         DFS( G, v);
}

int main(){
    Grafo grafo1 = criaGrafo(4);
    inserirGrafo(grafo1,0,1);
    inserirGrafo(grafo1,0,2);
    inserirGrafo(grafo1,1,2);
    inserirGrafo(grafo1,3,4);
    inserirGrafo(grafo1,4,2);

   for(int i=0; i<2; i++) {
      pthread_create(&(threads[i]), NULL, grafoDFS(grafo1), NULL);
   }
    return 0;
}