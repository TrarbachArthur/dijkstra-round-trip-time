#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include "edge.h"

typedef struct node Node;
typedef struct graph Graph;

// Node

Node* node_init();

void node_add_edge(Node* n, int target, double weight);

int node_get_id(Node* n);
void node_add_edge(Node* n, int target, double weight);
Edge* node_get_adj(Node* n);
void node_destroy(Node* n);

// Graph

Graph* graph_init(int node_amt, int edge_amt, int client_amt, int server_amt, int monitor_amt);

void graph_add_edge(Graph* g, int source, int target, double weight);

void graph_destroy(Graph* g);

Graph* graph_read_file(FILE* f);

Node** graph_get_nodes(Graph* g);
int graph_get_node_amt(Graph* g);
int graph_get_edge_amt(Graph* g);
int* graph_get_client_id(Graph* g);
int* graph_get_server_id(Graph* g);
int* graph_get_monitor_id(Graph* g);
int graph_get_client_amt(Graph* g);
int graph_get_server_amt(Graph* g);
int graph_get_monitor_amt(Graph* g);

#endif