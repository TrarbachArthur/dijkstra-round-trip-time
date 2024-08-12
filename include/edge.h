#ifndef EDGE_H
#define EDGE_H

typedef struct edge Edge;

Edge* edge_init(int target, double weight);

Edge* edge_get_next(Edge* e);
int edge_get_target(Edge* e);
double edge_get_weight(Edge* e);

void edge_set_next(Edge* e, Edge* next);

void edge_destroy(Edge* e);

#endif