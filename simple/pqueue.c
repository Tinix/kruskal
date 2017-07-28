#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "edge.h"
#include "pqueue.h"

/* Min-PriorityQueue */

struct _pqueue_t {
    elem_t *elems;
    unsigned int max_size;
    unsigned int size;
};

/* Auxiliary Functions */

unsigned int left(unsigned int i) {
    return (2 * i);
}

unsigned int right(unsigned int i) {
    return (2 * i + 1);
}

unsigned int parent(unsigned int i) {
    return (i / 2);
}

bool has_child(pqueue_t pq, unsigned int i) {
    /* PRE */
    assert(1 <= i && i <= pq->size);

    return (left(i) <= pq->size);
}

bool has_parent(unsigned int i) {
    /* PRE */
    assert(1 <= i);

    return (i != 1);
}

unsigned int min_child(pqueue_t pq, unsigned int i) {
    /* PRE */
    assert(1 <= i && i <= pq->size);
    assert(has_child(pq, i));

    unsigned int j;

    if (right(i) <= pq->size && elem_lte(pq->elems[right(i)],
                                         pq->elems[left(i)])) {
        j = right(i);
    } else {
        j = left(i);
    }

    return (j);
}

void swap(pqueue_t pq, unsigned int i, unsigned int j) {
    elem_t temporal;

    temporal = pq->elems[i];
    pq->elems[i] = pq->elems[j];
    pq->elems[j] = temporal;
}

void lift(pqueue_t pq, unsigned int i) {
    /* PRE */
    assert(1 <= i && i <= pq->size && has_parent(i));

    swap(pq, i, parent(i));
}

bool must_lift(pqueue_t pq, unsigned int i) {
    /* PRE */
    assert(1 <= i && i <= pq->size && has_parent(i));

    return (elem_lt(pq->elems[i], pq->elems[parent(i)]));
}

void heap_float(pqueue_t pq) {
    unsigned int index;

    index = pq->size;
    while (has_parent(index) && must_lift(pq, index)) {
        lift(pq, index);
        index = parent(index);
    }
    assert(pq->elems[0] == NULL);
}

void sink(pqueue_t pq) {
    unsigned int index;

    index = 1;
    while (has_child(pq, index) && must_lift(pq, min_child(pq, index))) {
        index = min_child(pq, index);
        lift(pq, index);
    }
}

/* TAD's functions */

pqueue_t pqueue_empty(unsigned int max_size) {
    pqueue_t pq = NULL;

    pq = calloc(1, sizeof(struct _pqueue_t));
    assert(pq != NULL);
    pq->elems = calloc(max_size + 1, sizeof(elem_t));
    assert(pq->elems != NULL);
    pq->max_size = max_size;

    return (pq);
}

bool pqueue_is_full(pqueue_t pq) {
    /* PRE */
    assert(pq != NULL);

    return (pq->size == pq->max_size);
}

bool pqueue_is_empty(pqueue_t pq) {
    /* PRE */
    assert(pq != NULL);

    return (pq->size == 0);
}

elem_t pqueue_fst(pqueue_t pq) {
    /* PRE */
    assert(pq != NULL);
    assert(!pqueue_is_empty(pq));

    return (pq->elems[1]);
}

unsigned int pqueue_size(pqueue_t pq) {
    /* PRE */
    assert(pq != NULL);

    return (pq->size);
}

void pqueue_enqueue(pqueue_t pq, elem_t elem) {
    /* PRE */
    assert(pq != NULL);
    assert(!pqueue_is_full(pq));

    pq->size += 1;
    pq->elems[pq->size] = elem;
    heap_float(pq);
}

void pqueue_dequeue(pqueue_t pq) {
    /* PRE */
    assert(pq != NULL);
    assert(!pqueue_is_empty(pq));

    pq->elems[1] = elem_destroy(pq->elems[1]);
    pq->size -= 1;
    if (pq->size > 0) {
        pq->elems[1] = pq->elems[pq->size + 1];
        pq->elems[pq->size + 1] = NULL;
        sink(pq);
    }
}

pqueue_t pqueue_destroy(pqueue_t pq) {
    /* PRE */
    assert(pq != NULL);

    for (unsigned int i = 1; i <= pq->size; i++) {
        pq->elems[i] = elem_destroy(pq->elems[i]);
    }
    free(pq->elems);
    free(pq);

    return (NULL);
}
