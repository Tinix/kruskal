#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "edge.h"

/* Edge abstract data type */

struct _edge_t {
    vertex_t left;
    vertex_t right;
    unsigned int weight;
    bool is_primary;
};

edge_t edge_create(vertex_t left, vertex_t right, unsigned int weight) {
    edge_t edge = calloc(1, sizeof(struct _edge_t));
    assert(edge != NULL);
    edge->left = left;
    edge->right = right;
    edge->weight = weight;
    edge->is_primary = false;
    return (edge);
}

edge_t edge_destroy(edge_t edge) {
    assert(edge != NULL);
    edge->left = vertex_destroy(edge->left);
    edge->right = vertex_destroy(edge->right);
    free(edge);
    return (NULL);
}

edge_t edge_copy(edge_t edge) {
    assert(edge != NULL);
    vertex_t left = vertex_copy(edge->left), right = vertex_copy(edge->right);
    edge_t copy = edge_create(left, right, edge->weight);
    copy = edge_set_primary(copy, edge->is_primary);
    return (copy);
}

vertex_t edge_left_vertex(edge_t edge) {
    assert(edge != NULL);
    return (edge->left);
}

vertex_t edge_right_vertex(edge_t edge) {
    assert(edge != NULL);
    return (edge->right);
}

unsigned int edge_weight(edge_t edge) {
    assert(edge != NULL);
    return (edge->weight);
}

bool edge_lt(edge_t edge, edge_t other) {
    assert(edge != NULL);
    assert(other != NULL);
    return (edge_weight(edge) < edge_weight(other));
}

bool edge_lte(edge_t edge, edge_t other) {
    assert(edge != NULL);
    assert(other != NULL);
    return (edge_weight(edge) <= edge_weight(other));
}

bool edge_is_primary(edge_t edge) {
    assert(edge != NULL);
    return (edge->is_primary);
}

edge_t edge_set_primary(edge_t edge, bool is_primary) {
    assert(edge != NULL);
    edge->is_primary = is_primary;
    return (edge);
}

void edge_dump(edge_t edge, FILE * fd) {
    assert(edge != NULL);
    assert(fd != NULL);
    fprintf(fd, "[%u --%u-- %u]",
            vertex_label(edge_left_vertex(edge)),
            edge_weight(edge), vertex_label(edge_right_vertex(edge)));
}
