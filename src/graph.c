#include "../include/graph.h"
#include "../include/edge.h"
#include "../include/PQ.h"

#include <stdlib.h>
#include <stdio.h>

struct node {
    Edge* adj; // Adjacency list
};

struct graph{
    Node** nodes;
    int node_amt;
    int edge_amt;
    
    int* client_id;
    int* server_id;
    int* monitor_id;

    int client_amt;
    int server_amt;
    int monitor_amt;
};

// Funcoes relacionadas aos nodes
Node* node_init() {
    Node* n = (Node*) calloc(1, sizeof(Node));
    n->adj = NULL;
    return n;
}

void node_add_edge(Node* n, int target, double weight) {
    Edge* e = edge_init(target, weight);

    edge_set_next(e, n->adj);
    n->adj = e;
}

Edge* node_get_adj(Node* n) {
    return n->adj;
}

void node_destroy(Node* n) {
    if (n == NULL) return;

    edge_destroy(n->adj);
    free(n);
}

// Funcoes relacionadas ao grafo

Graph* graph_init(int node_amt, int edge_amt, int client_amt, int server_amt, int monitor_amt) {
    
    Graph* g = (Graph*) calloc(1, sizeof(Graph));
    g->nodes = (Node**) calloc(node_amt, sizeof(Node*));
    g->node_amt = node_amt;
    g->edge_amt = edge_amt;

    g->client_id = (int*) calloc(client_amt, sizeof(int));
    g->server_id = (int*) calloc(server_amt, sizeof(int));
    g->monitor_id = (int*) calloc(monitor_amt, sizeof(int));

    g->client_amt = client_amt;
    g->server_amt = server_amt;
    g->monitor_amt = monitor_amt;

    for (int i = 0; i < node_amt; i++) {
        g->nodes[i] = node_init();
    }

    return g;
}

void graph_add_edge(Graph* g, int source, int target, double weight) {
    node_add_edge(g->nodes[source], target, weight);
}

void graph_destroy(Graph* g) {
    for (int i = 0; i < g->node_amt; i++) {
        node_destroy(g->nodes[i]);
    }

    free(g->nodes);
    free(g->client_id);
    free(g->server_id);
    free(g->monitor_id);
    free(g);
}

Graph* graph_read_file(FILE* f) {
    int node_amt, edge_amt, client_amt, server_amt, monitor_amt;
    
    fscanf(f, "%d %d", &node_amt, &edge_amt);
    fscanf(f, "%d %d %d", &server_amt, &client_amt, &monitor_amt);

    Graph* g = graph_init(node_amt, edge_amt, client_amt, server_amt, monitor_amt);

    for (int i = 0; i < server_amt; i++) {
        fscanf(f, "%d", &g->server_id[i]);
    }

    for (int i = 0; i < client_amt; i++) {
        fscanf(f, "%d", &g->client_id[i]);
    }

    for (int i = 0; i < monitor_amt; i++) {
        fscanf(f, "%d", &g->monitor_id[i]);
    }

    int src, target;
    double weight;

    for (int i = 0; i < edge_amt; i++) {
        fscanf(f, "%d %d %lf", &src, &target, &weight);
        graph_add_edge(g, src, target, weight);
    }

    return g;
};

Node** graph_get_nodes(Graph* g) {
    return g->nodes;
}

int graph_get_node_amt(Graph* g) {
    return g->node_amt;
}

int graph_get_edge_amt(Graph* g) {
    return g->edge_amt;
}

int* graph_get_client_id(Graph* g) {
    return g->client_id;
}

int* graph_get_server_id(Graph* g) {
    return g->server_id;
}

int* graph_get_monitor_id(Graph* g) {
    return g->monitor_id;
}

int graph_get_client_amt(Graph* g) {
    return g->client_amt;
}

int graph_get_server_amt(Graph* g) {
    return g->server_amt;
}

int graph_get_monitor_amt(Graph* g) {
    return g->monitor_amt;
}