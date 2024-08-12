#include "../include/edge.h"
#include "../include/item.h"
#include <stdlib.h>
#include <stdio.h>

struct edge {
    Edge* next;
    Item path;
};

Edge* edge_init(int target, double weight) {
    Edge* e = (Edge*) calloc(1, sizeof(Edge));

    id(e->path) = target;
    value(e->path) = weight;
    e->next = NULL;

    return e;
}

Edge* edge_get_next(Edge* e) {
    return e->next;
}

int edge_get_target(Edge* e) {
    return id(e->path);
}

double edge_get_weight(Edge* e) {
    return value(e->path);
}

void edge_set_next(Edge* e, Edge* next) {
    e->next = next;
}

void edge_destroy(Edge* e) {
    if (e == NULL) return;

    edge_destroy(e->next);
    free(e);
}