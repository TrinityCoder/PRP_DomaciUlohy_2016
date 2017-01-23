#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "graph.h"

#define INITIAL_GRAPH_CAPACITY 100   // Defaultni velikost pole m_edges noveho grafu.

graph_t* allocate_graph() {
     graph_t* g = malloc(sizeof(graph_t));
     g->m_edges = malloc(sizeof(edge_t) * INITIAL_GRAPH_CAPACITY);
     g->m_capacity = INITIAL_GRAPH_CAPACITY;
     g->m_size = 0;
     return g;
}

void free_graph(graph_t **graph) {
     if(graph != NULL && *graph != NULL) {
          free((*graph)->m_edges);
          free(*graph);
          *graph = NULL;
     }
}

void auto_close(FILE** f) { fclose(*f); }
#define auto_closed __attribute__ ((__cleanup__(auto_close)))

#define IS_GRAPH_FULL(g) ((g)->m_capacity == (g)->m_size ? true : false)
#define RESIZE_GRAPH(g)                                                            \
          do {                                                                     \
               g->m_capacity *= 2;                                                 \
               g->m_edges = realloc(g->m_edges, g->m_capacity * sizeof(edge_t));   \
          } while(0);
#define RESIZE_IF_NEEDED(g) do { if(IS_GRAPH_FULL(g)) { RESIZE_GRAPH(g); } } while(0)

#define CURR_EDGE_X(g, pos) (g->m_edges[pos].m_x)
#define CURR_EDGE_Y(g, pos) (g->m_edges[pos].m_y)
#define CURR_EDGE_COST(g, pos) (g->m_edges[pos].m_cost)

void load_txt(const char *fname, graph_t *graph) {
     FILE* f auto_closed = fopen(fname, "r");
     while(1) {
          RESIZE_IF_NEEDED(graph);
          if(fscanf(f, "%d %d %d", &CURR_EDGE_X(graph, graph->m_size),
                               &CURR_EDGE_Y(graph, graph->m_size),
                               &CURR_EDGE_COST(graph, graph->m_size)) != 3) {
               break;  // Konec souboru.
          }
          graph->m_size += 1;
     }
}

void load_bin(const char *fname, graph_t *graph) {
     FILE* f auto_closed = fopen(fname, "rb");
     while(1) {
          RESIZE_IF_NEEDED(graph);
          // V nasledujicim volani fce fread() si muzeme dovolit vzit
          // zacatek promenne m_x a zapsat jednim volanim na toto misto v pameti
          // 3 integery za sebe - umoznuje nam to __attribute__((__packed__))
          // u definice struktury edge_t.
          if(fread(&CURR_EDGE_X(graph, graph->m_size), sizeof(int), 3, f) != 3)
               break;
          graph->m_size += 1;
     }
}

void save_txt(const graph_t * const graph, const char *fname) {
     FILE* f auto_closed = fopen(fname, "w+");
     for(int i = 0; i < graph->m_size; ++i) {
          fprintf(f, "%d %d %d\n", CURR_EDGE_X(graph, i),
                                   CURR_EDGE_Y(graph, i),
                                   CURR_EDGE_COST(graph, i));
     }
}

void save_bin(const graph_t * const graph, const char *fname) {
     FILE* f auto_closed = fopen(fname, "wb+");
     for(int i = 0; i < graph->m_size; ++i) {
          // Zde u funkce fwrite() si dovolime to same, co u funkce fread()
          // (viz funkce load_bin() vyse).
          fwrite(&CURR_EDGE_X(graph, i), sizeof(int), 3, f);
     }
}

#undef auto_closed
#undef IS_GRAPH_FULL
#undef RESIZE_GRAPH
#undef RESIZE_IF_NEEDED
#undef CURR_EDGE_X
#undef CURR_EDGE_Y
#undef CURR_EDGE_COST
