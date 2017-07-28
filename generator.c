#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define max(X, Y) (((X) > (Y)) ? (X) : (Y))
#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

#define MAX_VERTEX 200
#define MAX_EDGES 100

int main(int argc, char *argv[]) {
    int seed, n_vertex, n_edges, floor, roof, weight, l, r;
    int *nodes, *graph;

    seed = 0;
    if (argc == 2) {
        for (int i = 0; argv[1][i] != '\0'; i++) {
            seed *= 10;
            seed += argv[1][i] - '0';
        }
    }
    srand(seed);

    assert(MAX_VERTEX > 1);
    n_vertex = rand() % (MAX_VERTEX - 1) + 2;

    floor = n_vertex / 2 + n_vertex % 2;
    roof = min(MAX_EDGES, (n_vertex * (n_vertex - 1)) / 2);
    n_edges = rand() % (roof - floor + 1) + floor;

    nodes = calloc(n_vertex, sizeof(int));
    graph = calloc(n_vertex * n_vertex, sizeof(int));

    /* Not necessary using calloc 
       for (int i = 0; i < n_vertex; i++) {
       nodes[i] = 0;
       for (int j = 0; j < n_vertex; j++) {
       graph[i * n_vertex + j] = 0;
       }
       } */

    /* Make sure every node is connected */
    for (int i = 0; i < floor; i++) {
        while (1) {
            l = rand() % n_vertex;
            r = rand() % n_vertex;

            if (l != r && nodes[l] == 0
                && (i + n_vertex % 2 == floor || nodes[r] == 0)) {
                graph[l * n_vertex + r] = 1 + rand() % 50;
                nodes[l]++;
                nodes[r]++;
                break;
            }
        }
    }

    /* Create random edges */
    for (int i = floor; i < n_edges; i++) {
        while (1) {
            l = rand() % n_vertex;
            r = rand() % n_vertex;

            if (l != r) {
                if (graph[r * n_vertex + l] == 0
                    && graph[l * n_vertex + r] == 0) {
                    graph[l * n_vertex + r] = 1 + rand() % 50;
                    break;
                }
            }
        }
    }

    /* Dump graph */
    printf("# %d %d\n\n", n_vertex, n_edges);
    printf("graph G {\n");

    for (int i = 0; i < n_vertex; i++) {
        for (int j = i + 1; j < n_vertex; j++) {
            weight = max(graph[i * n_vertex + j], graph[j * n_vertex + i]);
            if (weight > 0) {
                printf("\t%u -- %u [label=%u];\n", i, j, weight);
            }
        }
    }

    printf("}");

    free(nodes);
    free(graph);
    return 0;
}
