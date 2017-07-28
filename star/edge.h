#ifndef EDGE_H
#define EDGE_H

#include <stdio.h>
#include "vertex.h"

/* Edge abstract data type */

typedef struct _edge_t *edge_t;

edge_t edge_create(vertex_t left, vertex_t right, unsigned int weight);
/*
 * Return a newly created edge.
 *
 * 'edge_destroy' has to be called on the resulting edge when is no
 * longer used.
 *
 * PRE: both 'left' and 'right' must not be NULL.
 *
 * POST: the result is not NULL and 'left' and 'right' are the result vertices.
 * Also, edge_weight(result) is 'weight'.
 */

edge_t edge_destroy(edge_t edge);
/*
 * Free the resources allocated for 'edge'.
 *
 * PRE: 'edge' must not be NULL.
 *
 * POST: the result is NULL.
 */

edge_t edge_copy(edge_t edge);
/*
 * Return a newly created edge which is an exact copy of the given 'edge'.
 *
 * 'edge_destroy' has to be called on the resulting vertex when is no
 * longer used.
 *
 * PRE: 'edge' must not be NULL.
 *
 * POST: the result is not NULL and the left and right vertices are equal to
 * the vertices from 'edge', and so is its weight.
 */

vertex_t edge_left_vertex(edge_t edge);
/*
 * Return the left vertex of 'edge'.
 *
 * PRE: 'edge' must not be NULL.
 *
 * POST: the result is not NULL.
 */

vertex_t edge_right_vertex(edge_t edge);
/*
 * Return the right vertex of 'edge'.
 *
 * PRE: 'edge' must not be NULL.
 *
 * POST: the result is not NULL.
 */

unsigned int edge_weight(edge_t edge);
/*
 * Return the weight of 'edge'.
 *
 * PRE: 'edge' must not be NULL.
 */

bool edge_lt(edge_t edge, edge_t other);
/*
 * Return whether the given 'edge' is strictly less than 'other'.
 *
 * PRE: both 'edge' and 'other' must not be NULL.
 */

bool edge_lte(edge_t edge, edge_t other);
/*
 * Return whether the given 'edge' is less or equal than 'other'.
 *
 * PRE: both 'edge' and 'other' must not be NULL.
 */

bool edge_is_primary(edge_t edge);
/*
 * Return true if the edge is a primary edge.
 *
 * PRE: 'edge' must not be NULL.
 */

edge_t edge_set_primary(edge_t edge, bool is_primary);
/*
 * Return the edge updated.
 *
 * PRE: 'edge' must not be NULL.
 */

void edge_dump(edge_t edge, FILE * fd);
/*
 * Dump the given 'edge' to the given file descriptor 'fd'.
 *
 * PRE: 'edge' must not be NULL, and 'fd' must be a valid file descriptor.
 */

#endif
