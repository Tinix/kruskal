#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "graph.h"
#include "pqueue.h"
#include "union_find.h"


graph_t kruskal(graph_t graph) {
/* Computes a MST of the given graph.
 *
 * This function returns a copy of the input graph in which
 * only the edges of the MST are marked as primary. The
 * remaining edges are marked as secondary. 
 *
 * The input graph does not change. 
 * 
*/
    graph_t mst;
    union_find_t uf;
    pqueue_t pq;
    edge_t *edges;
    edge_t e;
    unsigned int left, right, n, m;

    /* Inicialización */
    n = graph_vertices_count(graph);
    m = graph_edges_count(graph);
    mst = graph_empty(n);
    uf = union_find_create(n);
    pq = pqueue_empty(m);

    /* Llenar `pq` */
    edges = graph_edges(graph);
    for (unsigned int j = 0; j < m; j++) {
        pqueue_enqueue(pq, edges[j]);
    }
    /* Ahora las aristas están en `pq` */
    free(edges);
    edges = NULL;


    /* Principal */
    while (!pqueue_is_empty(pq) && union_find_count(uf) > 1) {
        e = edge_copy(pqueue_fst(pq));
        left = vertex_label(edge_left_vertex(e));
        right = vertex_label(edge_right_vertex(e));
        left = union_find_find(uf, left);
        right = union_find_find(uf, right);
        if (!union_find_connected(uf, left, right)) {
            e = edge_set_primary(e, true);
            union_find_union(uf, left, right);
        } else {
            e = edge_set_primary(e, false);
        }
        mst = graph_add_edge(mst, e);
        pqueue_dequeue(pq);
    }

    /* Agregar aristas restantes como secundarias */
    while (!pqueue_is_empty(pq)) {
        e = edge_copy(pqueue_fst(pq));
        e = edge_set_primary(e, false);
        mst = graph_add_edge(mst, e);
        pqueue_dequeue(pq);
    }

    /* Destroy */
    uf = union_find_destroy(uf);
    pq = pqueue_destroy(pq);

    return (mst);
}

unsigned int mst_total_weight(graph_t mst) {
/* Returns the sum of the weights of all the primary
 * edges of the given graph.
 */
    unsigned int sum, m;
    edge_t *edges;

    edges = graph_edges(mst);
    sum = 0;
    m = graph_edges_count(mst);
    for (unsigned int i = 0; i < m; i++) {
        if (edge_is_primary(edges[i])) {
            sum += edge_weight(edges[i]);
        }
        edges[i] = edge_destroy(edges[i]);
    }
    free(edges);

    return (sum);
}

bool graph_has_cycle(graph_t g) {
    bool has_secondary_edge;
    edge_t *edges;
    unsigned int i, m;

    edges = graph_edges(g);
    has_secondary_edge = false;
    i = 0;
    m = graph_edges_count(g);
    while (!has_secondary_edge && i < m) {
        has_secondary_edge = !edge_is_primary(edges[i]);
        edges[i] = edge_destroy(edges[i]);
        i += 1;
    }
    while (i < m) {
        edges[i] = edge_destroy(edges[i]);
        i += 1;
    }
    free(edges);

    return (has_secondary_edge);
}

unsigned int graph_connected_components(graph_t g) {
    unsigned int classes_count = 0, n, m, left, right;
    union_find_t uf;
    edge_t *edges;

    n = graph_vertices_count(g);
    m = graph_edges_count(g);
    uf = union_find_create(n);

    edges = graph_edges(g);
    for (unsigned int i = 0; i < m; i++) {
        left = vertex_label(edge_left_vertex(edges[i]));
        right = vertex_label(edge_right_vertex(edges[i]));
        left = union_find_find(uf, left);
        right = union_find_find(uf, right);
        if (!union_find_connected(uf, left, right)) {
            union_find_union(uf, left, right);
        }
        edges[i] = edge_destroy(edges[i]);
    }
    free(edges);
    classes_count = union_find_count(uf);
    uf = union_find_destroy(uf);

    return (classes_count);
}

#ifndef TEST                    /* keep this line above main function */

int main(void) {
    /* read graph from stdin */
    graph_t graph = graph_from_file(stdin);
    assert(graph != NULL);
    /* run kruskal */
    graph_t mst = kruskal(graph);
    /* dump graph */
    graph_dump(mst, stdout);
    /* dump total weight */
    printf("\n# MST : %u\n", mst_total_weight(mst));
    /* dump whether has a cycle */
    if (graph_has_cycle(mst)) {
        printf("# Has a cycle: YES\n");
    } else {
        printf("# Has a cycle: NO\n");
    }
    /* dump total connected components */
    printf("# Connected components: %u\n", graph_connected_components(mst));
    /* destroy both graphs */
    graph = graph_destroy(graph);
    mst = graph_destroy(mst);
}

#endif                          /* keep this line below main function */
