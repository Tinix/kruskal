#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "helpers.h"

#define GRAPH_NAME_TOKEN "graph"
#define MAX_EDGE_COUNT 100


static inline char *_non_empty_line(FILE * fd) {
    assert(fd != NULL);
    char *line = readline(fd);
    while (strlen(line) == 0) {
        free(line);
        line = readline(fd);
    }
    return (line);
}


/* Graph abstract data type */

struct _graph_t {
    edge_t *edges;
    unsigned int vertices_count;
    unsigned int edges_count;
};

graph_t graph_empty(unsigned int num_vertices) {
    graph_t graph = calloc(1, sizeof(struct _graph_t));
    assert(graph != NULL);

    graph->vertices_count = num_vertices;
    graph->edges_count = 0;
    graph->edges = calloc(MAX_EDGE_COUNT, sizeof(edge_t));
    assert(graph->edges != NULL);

    return (graph);
}

graph_t graph_destroy(graph_t graph) {
    assert(graph != NULL);

    for (unsigned int i = 0; i < graph->edges_count; i++) {
        graph->edges[i] = edge_destroy(graph->edges[i]);
    }
    free(graph->edges);
    free(graph);
    return (NULL);
}

graph_t graph_add_edge(graph_t graph, edge_t edge) {
    /* PRE: edge not in graph */
    /* PRE: 0 < left/right vertices labels <= vertices_count */
    assert(graph != NULL);
    assert(edge != NULL);

    unsigned int next = graph->edges_count;
    graph->edges[next] = edge;
    graph->edges_count++;

    return (graph);
}

graph_t graph_from_file(FILE * fd) {
    assert(fd != NULL);
    int scan_result = 0;
    char *line = NULL, *token = NULL;
    unsigned int vertices_count = 0, edges_count = 0;
    graph_t graph = NULL;

    /* first line should contain vertices/edges counts */
    line = _non_empty_line(fd);
    scan_result = sscanf(line, "# %u %u\n", &vertices_count, &edges_count);
    free(line);
    if (scan_result != 2) {
        exit(EXIT_FAILURE);
    }

    /* next line should be graph definition */
    line = _non_empty_line(fd);
    token = strtok(line, " ");
    if (token != NULL && strcmp(token, GRAPH_NAME_TOKEN) == 0) {
        /* name: read until space or opening brace */
        token = strtok(NULL, " {");
    }
    free(line);

    edge_t *edges = calloc(edges_count, sizeof(edge_t));
    assert(edges != NULL);

    /* next edges_count lines should be edges */
    for (unsigned int i = 0; i < edges_count; i++) {
        label_t left = 0, right = 0;
        unsigned int weight = 0;

        line = _non_empty_line(fd);
        scan_result = sscanf(line, " %u -- %u [label=%u]",
                             &left, &right, &weight);
        if (scan_result != 3) {
            printf("Could not read the graph file.\n");
            exit(EXIT_FAILURE);
        }

        if (vertices_count <= left || vertices_count <= right) {
            printf("Wrong vertex id, should be 0 <= id < vertices_count.\n");
            exit(EXIT_FAILURE);
        }

        vertex_t left_vertex = vertex_create(left);
        vertex_t right_vertex = vertex_create(right);
        edge_t new_edge = edge_create(left_vertex, right_vertex, weight);
        edges[i] = new_edge;
        free(line);
    }

    graph = calloc(1, sizeof(struct _graph_t));
    assert(graph != NULL);

    graph->vertices_count = vertices_count;
    graph->edges_count = edges_count;
    graph->edges = edges;

    return (graph);
}

unsigned int graph_vertices_count(graph_t graph) {
    assert(graph != NULL);
    return (graph->vertices_count);
}

unsigned int graph_edges_count(graph_t graph) {
    assert(graph != NULL);
    return (graph->edges_count);
}

edge_t *graph_edges(graph_t graph) {
    assert(graph != NULL);
    unsigned int num_edges = graph_edges_count(graph);
    edge_t *edges = calloc(num_edges, sizeof(edge_t));
    assert(edges != NULL);

    for (unsigned int i = 0; i < num_edges; i++) {
        edge_t edge = graph->edges[i];
        edge_t new_edge = edge_copy(edge);
        edges[i] = new_edge;
    }
    return (edges);
}

void graph_dump(graph_t graph, FILE * fd) {
    assert(graph != NULL);
    assert(fd != NULL);

    unsigned int v_count = graph_vertices_count(graph);
    unsigned int e_count = graph_edges_count(graph);

    /* write counts */
    fprintf(fd, "# %u %u\n\n", v_count, e_count);

    /* open graph */
    fprintf(fd, "graph G {\n");
    /* free(name); */

    /* write edges */
    edge_t *edges = graph_edges(graph);
    for (unsigned int i = 0; i < e_count; i++) {
        label_t left = 0, right = 0;
        unsigned int weight = 0;

        edge_t edge = edges[i];
        left = vertex_label(edge_left_vertex(edge));
        right = vertex_label(edge_right_vertex(edge));
        weight = edge_weight(edge);

        if (edge_is_primary(edge)) {
            fprintf(fd, "\t%u -- %u [label=%u, color=red, style=bold];\n",
                    left, right, weight);
        } else {
            fprintf(fd, "\t%u -- %u [label=%u];\n", left, right, weight);
        }
        edges[i] = edge_destroy(edge);
    }
    free(edges);

    /* close graph */
    fprintf(fd, "}\n");
}
