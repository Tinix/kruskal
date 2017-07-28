#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "union_find.h"


struct _union_find_t {
    int *classes;
    uint max_size;
    uint class_count;
};

union_find_t union_find_create(uint max_size) {
    union_find_t uf = NULL;

    uf = calloc(1, sizeof(struct _union_find_t));
    assert(uf != NULL);
    uf->classes = calloc(max_size, sizeof(uint));
    assert(uf->classes != NULL);
    for (uint i = 0; i < max_size; i++) {
        uf->classes[i] = -1;
    }
    uf->max_size = max_size;
    uf->class_count = max_size;

    return (uf);
}

/* Función auxiliar */
bool is_rep(union_find_t uf, uint elem) {
    return (uf->classes[elem] < 0);
}

uint union_find_find(union_find_t uf, uint elem) {
    /* PRE */
    assert(uf != NULL);
    assert(elem < uf->max_size);

    unsigned int result, j, k;

    j = elem;
    while (!is_rep(uf, j)) {
        j = uf->classes[j];
    }
    result = j;
    j = elem;
    while (!is_rep(uf, j)) {
        k = uf->classes[j];
        uf->classes[j] = result;
        j = k;
    }

    return (result);
}

void union_find_union(union_find_t uf, uint elem1, uint elem2) {
    /* PRE */
    assert(uf != NULL);
    assert(elem1 < uf->max_size && elem2 < uf->max_size);
    assert(is_rep(uf, elem1) && is_rep(uf, elem2));

    int size1, size2;

    if (elem1 != elem2) {
        size1 = uf->classes[elem1];
        size2 = uf->classes[elem2];
        if (size1 >= size2) {   // Si elem2 representa al conjunto MÁS GRANDE
            uf->classes[elem2] += size1;
            uf->classes[elem1] = elem2;
        } else {
            uf->classes[elem1] += size2;
            uf->classes[elem2] = elem1;
        }
        uf->class_count -= 1;
        assert(union_find_connected(uf, elem1, elem2));
    }
}

bool union_find_connected(union_find_t uf, uint elem1, uint elem2) {
    /* PRE */
    assert(uf != NULL);
    assert(elem1 < uf->max_size && elem2 < uf->max_size);

    return (union_find_find(uf, elem1) == union_find_find(uf, elem2));
}

uint union_find_count(union_find_t uf) {
    /* PRE */
    assert(uf != NULL);

    return (uf->class_count);
}

union_find_t union_find_destroy(union_find_t uf) {
    /* PRE */
    assert(uf != NULL);

    free(uf->classes);
    free(uf);

    return (NULL);
}
