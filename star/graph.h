#ifndef _GRAPH_H
#define _GRAPH_H

#include <stdbool.h>
#include "edge.h"

/* Graph abstract data type */

typedef struct _graph_t *graph_t;

graph_t graph_empty(unsigned int num_vertices);
/*
 * Return a newly created graph that will hold up to 'num_vertices',
 * numerated from 0 to 'num_vertices' - 1
 *
 * 'graph_destroy' has to be called on the resulting graph when is no
 * longer used.
 *
 */

graph_t graph_destroy(graph_t graph);
/*
 * Free the resources allocated for 'graph'.
 *
 * PRE: 'graph' must not be NULL.
 *
 * POST: the result is NULL.
 */

graph_t graph_add_edge(graph_t graph, edge_t edge);
/*
 * Add 'edge' to the given 'graph'.
 *
 * PRE: both 'graph' and 'edge' must not be NULL.
 *
 * POST: the result is not NULL and is the same as 'graph' but with the new
 * 'edge' added to the edges list.
 */

graph_t graph_from_file(FILE * fd);
/*
 * Return a newly created graph that will be filled with the data in
 * the file descriptor 'fd'.
 *
 * The file format must be as follows:
 *
 * # <num vertices> <num edges>
 * graph <graph name> {
 *     <if of vertex from> -- <id of vertex to> [label=<edge weigth>];
 *     <if of vertex from> -- <id of vertex to> [label=<edge weigth>];
 *     <if of vertex from> -- <id of vertex to> [label=<edge weigth>];
 *     <if of vertex from> -- <id of vertex to> [label=<edge weigth>];
 *     ...
 *     <if of vertex from> -- <id of vertex to> [label=<edge weigth>];
 * }
 *
 * PRE: 'fd' must be a valid file descriptor.
 *
 * POST: the result is not NULL and is a graph that has as many vertices and
 * as many edges as the amount indicated in the input file. Also, the resulting
 * graph's name is the same as the one given in the file descripted by 'fd'.
 */

unsigned int graph_vertices_count(graph_t graph);
/*
 * Return the amount of vertices in the given 'graph'.
 *
 * PRE: 'graph' must be not NULL.
 */

unsigned int graph_edges_count(graph_t graph);
/*
 * Return the amount of edges in the given 'graph'.
 *
 * PRE: 'graph' must be not NULL.
 */

edge_t *graph_edges(graph_t graph);
/*
 * Return an array with a COPY of the edges of the given 'graph'.
 *
 * PRE: 'graph' must be not NULL.
 *
 * POST: the result is not NULL and will hold as many edges as
 * 'graph_edges_count(graph)'. The caller must call free on it when done
 * using it.
 */

void graph_dump(graph_t graph, FILE * fd);
/*
 * Dump the given 'graph' to the file descriptor 'fd'.
 *
 * The file format is the same as the one required in read_graph_from_file.
 *
 * PRE: 'graph' must not be NULL and 'fd' must be a valid file descriptor.
 */

#endif
