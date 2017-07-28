#ifndef VERTEX_H
#define VERTEX_H

/* Vertex abstract data type */

typedef struct _vertex_t *vertex_t;
typedef unsigned int label_t;

vertex_t vertex_create(label_t label);
/*
 * Return a newly created vertex with identifier 'label'.
 *
 * 'vertex_destroy' has to be called on the resulting vertex when is no
 * longer used.
 *
 * POST: the result is not NULL and vertex_label(result) is 'label'.
 */

vertex_t vertex_destroy(vertex_t vertex);
/*
 * Free the resources allocated for 'vertex'.
 *
 * PRE: 'vertex' must not be NULL.
 *
 * POST: the result is NULL.
 */

vertex_t vertex_copy(vertex_t vertex);
/*
 * Return a newly created vertex which is an exact copy of the given 'vertex'.
 *
 * 'vertex_destroy' has to be called on the resulting vertex when is no
 * longer used.
 *
 * PRE: 'vertex' must not be NULL.
 *
 * POST: the result is not NULL and vertex_label(result) is 'label'.
 * POST: the result is not NULL and the label of the result is equal to
 * the label from 'vertex'.
 */

label_t vertex_label(vertex_t vertex);
/*
 * Return the label for 'vertex'.
 *
 * PRE: 'vertex' must not be NULL.
 */

#endif
