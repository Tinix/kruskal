#include <assert.h>
#include <stdlib.h>

#include "vertex.h"


struct _vertex_t {
    label_t id;
};

vertex_t vertex_create(label_t label) {
    vertex_t vertex = calloc(1, sizeof(struct _vertex_t));
    assert(vertex != NULL);
    vertex->id = label;
    return (vertex);
}

vertex_t vertex_destroy(vertex_t vertex) {
    assert(vertex != NULL);
    free(vertex);
    return (NULL);
}

vertex_t vertex_copy(vertex_t vertex) {
    assert(vertex != NULL);
    vertex_t copy = vertex_create(vertex->id);
    return (copy);
}

label_t vertex_label(vertex_t vertex) {
    assert(vertex != NULL);
    return (vertex->id);
}
