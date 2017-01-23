#ifndef __GRAPH_H__
#define __GRAPH_H__

typedef struct __attribute__((__packed__)) _edge_t {
     int m_x;        // Vychozi vrchol hrany.
     int m_y;        // Konecny vrchol hrany.
     int m_cost;     // Cena hrany.
} edge_t;

typedef struct {
   edge_t* m_edges;  // Pole hran grafu.
   int m_size;       // Pocet hran grafu (<==> pocet prvku v m_edges).
   int m_capacity;   // Kolik objektu typu edge_t pojme celkem m_edges.
} graph_t;

/* Allocate a new graph and return a reference to it. */
graph_t* allocate_graph();
/* Free all allocated memory and set reference to the graph to NULL. */
void free_graph(graph_t **graph);

/* Load a graph from the text file. */
void load_txt(const char *fname, graph_t *graph);
/* Load a graph from the binary file. */
void load_bin(const char *fname, graph_t *graph);

/* Save the graph to the text file. */
void save_txt(const graph_t * const graph, const char *fname);
/* Save the graph to the binary file. */
void save_bin(const graph_t * const graph, const char *fname);

#endif // __GRAPH_H__
