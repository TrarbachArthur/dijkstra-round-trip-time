#ifndef RATIO_H
#define RATIO_H

#include "graph.h"

#include <stdlib.h>
#include <stdio.h>

typedef struct ratio {
    int server_id;
    int client_id;
    double ratio;
} Ratio;

int ratio_cmp(const void* a, const void* b);

void handle_dijkstra(Graph* g, double* sm_dist, double* sc_dist, double* cm_dist, double* cs_dist, double* ms_dist, double* mc_dist);

Ratio* calculate_ratios(Graph* g, double* sm_dist, double* sc_dist, double* cm_dist, double* cs_dist, double* ms_dist, double* mc_dist);

#endif