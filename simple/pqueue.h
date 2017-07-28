#ifndef PQUEUE_H
#define PQUEUE_H

#include <assert.h>
#include <stdbool.h>

#include "edge.h"

/* Min-PriorityQueue */

typedef struct _pqueue_t *pqueue_t;
typedef edge_t elem_t;

/* Use this constants to avoid using the type *edge_t* in the implementation */
#define elem_lt edge_lt
#define elem_lte edge_lte
#define elem_destroy edge_destroy


/* The element of higher priority is the minimum element inside the queue.
 * All the functions assume that the parameter 'pq' is not NULL  
 */

pqueue_t pqueue_empty(unsigned int max_size);
/* Returns an empty priority queue that will hold up to 'max_size' elements. */

bool pqueue_is_full(pqueue_t pq);
/* Returns true if the queue has 'max_size' elements, false otherwise. */

bool pqueue_is_empty(pqueue_t pq);
/* Returns true if the given queue has no elements, false otherwise. */

elem_t pqueue_fst(pqueue_t pq);
/* Returns the first element of the given queue. 
 * The result is the element with the highest priority 
 * (the minimum element inside 'pq').
 * Implementation note: The result should be a reference, not a copy.
 */

unsigned int pqueue_size(pqueue_t pq);
/* Returns how many elements are inside the given queue. */

void pqueue_enqueue(pqueue_t pq, elem_t elem);
/* Inserts a new element 'elem' in the queue.
 * Assumes 'pq' is not full.
 */

void pqueue_dequeue(pqueue_t pq);
/* Removes the first element in the queue.
 * Assumes 'pq' is not empty.
 */

pqueue_t pqueue_destroy(pqueue_t pq);
/* Destroys the queue and free all its memory resources 
 * Implementation note: The result should be NULL pointer.
 */

#endif
