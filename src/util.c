#include "../include/util.h"
#include "../include/graph.h"
#include "../include/PQ.h"
#include "../include/edge.h"

#include <stdio.h>
#include <stdlib.h>
#include <float.h>

int ratio_cmp(const void* a, const void* b) {
    Ratio* ra = (Ratio*) a;
    Ratio* rb = (Ratio*) b;

    if (ra->ratio < rb->ratio) return -1;
    if (ra->ratio > rb->ratio) return 1;
    return 0;
}

double* dijkstra(Graph* g, int src) {
    double* dist = (double*) calloc(graph_get_node_amt(g), sizeof(double));
    Item i;

    for (int i = 0; i < graph_get_node_amt(g); i++) {
        dist[i] = DBL_MAX;
    }

    dist[src] = 0;

    PQ* pq = PQ_init(graph_get_edge_amt(g));
    id(i) = src;
    value(i) = dist[src];
    PQ_insert(pq, i);

    Node** nodes = graph_get_nodes(g);

    while(!PQ_empty(pq)) {
        i = PQ_delmin(pq);
        int v = id(i);
        Node* n = nodes[v];

        for (Edge* e = node_get_adj(n); e != NULL; e = edge_get_next(e)) {
            int w = edge_get_target(e);
            double weight = edge_get_weight(e);

            if(dist[w] > dist[v] + weight) {
                dist[w] = dist[v] + weight;
                id(i) = w;
                value(i) = dist[w];

                if (PQ_contains(pq, w)) {
                    PQ_decrease_key(pq, w, dist[w]);
                }
                else {
                    PQ_insert(pq, i);
                }
            }
        }
    }

    PQ_finish(pq);

    return dist;
}

void handle_dijkstra(Graph* g, double* sm_dist, double* sc_dist, double* cm_dist, double* cs_dist, double* ms_dist, double* mc_dist) {
    Node** nodes = graph_get_nodes(g);
    int node_amt = graph_get_node_amt(g);
    
    int server_amt = graph_get_server_amt(g);
    int client_amt = graph_get_client_amt(g);
    int monitor_amt = graph_get_monitor_amt(g);

    int* server_id = graph_get_server_id(g);
    int* client_id = graph_get_client_id(g);
    int* monitor_id = graph_get_monitor_id(g);

    double* dist;

    // Calculate and store all relevant distances with servers as source

    for(int i = 0; i < server_amt; i++) {
        dist = dijkstra(g, server_id[i]);

        for (int j = 0; j < monitor_amt; j++) {
            sm_dist[i*monitor_amt + j] = dist[monitor_id[j]];
        }

        for(int j = 0; j < client_amt; j++) {
            sc_dist[i*client_amt + j] = dist[client_id[j]];
        }

        free(dist);
    }
    
    // Calculate and store all relevant distances with clients as source

    for(int i = 0; i < client_amt; i++) {
        dist = dijkstra(g, client_id[i]);

        for(int j = 0; j < monitor_amt; j++) {
            cm_dist[i*monitor_amt + j] = dist[monitor_id[j]];
        }

        for (int j = 0; j < server_amt; j++) {
            cs_dist[i*server_amt + j] = dist[server_id[j]];
        }

        free(dist);
    }

    // Calculate and store all relevant distances with monitors as source

    for(int i = 0; i < monitor_amt; i++) {
        dist = dijkstra(g, monitor_id[i]);

        for(int j = 0; j < server_amt; j++) {
            ms_dist[i*server_amt + j] = dist[server_id[j]];
        }

        for(int j = 0; j < client_amt; j++) {
            mc_dist[i*client_amt + j] = dist[client_id[j]];
        }

        free(dist);
    }
}

Ratio* calculate_ratios(Graph* g, double* sm_dist, double* sc_dist, double* cm_dist, double* cs_dist, double* ms_dist, double* mc_dist) {
    int server_amt = graph_get_server_amt(g);
    int client_amt = graph_get_client_amt(g);
    int monitor_amt = graph_get_monitor_amt(g);

    int* server_id = graph_get_server_id(g);
    int* client_id = graph_get_client_id(g);
    int* monitor_id = graph_get_monitor_id(g);

    Ratio* ratios = (Ratio*) calloc(server_amt*client_amt, sizeof(Ratio));

    double rtt, real_rtt; // RTT and RTT*
    double min_real_rtt;

    for (int i = 0; i < server_amt; i++) {
        for (int j = 0; j < client_amt; j++) {
            min_real_rtt = DBL_MAX;

            rtt = sc_dist[i*client_amt + j] + cs_dist[j*server_amt + i]; // S->C + C->S

            for (int k = 0; k < monitor_amt; k++) {
                real_rtt = sm_dist[i*monitor_amt + k] + mc_dist[k*client_amt + j]; // S->M + M->C
                real_rtt += cm_dist[j*monitor_amt + k] + ms_dist[k*server_amt + i]; // C->M + M->S

                if (real_rtt < min_real_rtt) {
                    min_real_rtt = real_rtt;
                }
            }

            Ratio ratio;
            ratio.server_id = server_id[i];
            ratio.client_id = client_id[j];
            ratio.ratio = min_real_rtt / rtt;

            ratios[i*client_amt + j] = ratio;
        }
    }

    return ratios;
}