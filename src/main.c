#include <stdio.h>
#include <stdlib.h>
#include "../include/util.h"
#include "../include/graph.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (input == NULL) {
        printf("Error opening input file\n");
        return 1;
    }

    Graph* g = graph_read_file(input);

    int server_amt = graph_get_server_amt(g);
    int client_amt = graph_get_client_amt(g);
    int monitor_amt = graph_get_monitor_amt(g);

    double* sm_dist = (double*) calloc(server_amt*monitor_amt, sizeof(double));
    double* sc_dist = (double*) calloc(server_amt*client_amt, sizeof(double));
    double* cm_dist = (double*) calloc(client_amt*monitor_amt, sizeof(double));
    double* cs_dist = (double*) calloc(client_amt*server_amt, sizeof(double));
    double* ms_dist = (double*) calloc(monitor_amt*server_amt, sizeof(double));
    double* mc_dist = (double*) calloc(monitor_amt*client_amt, sizeof(double));

    handle_dijkstra(g, sm_dist, sc_dist, cm_dist, cs_dist, ms_dist, mc_dist);

    Ratio* ratios = calculate_ratios(g, sm_dist, sc_dist, cm_dist, cs_dist, ms_dist, mc_dist); 
    qsort(ratios, server_amt*client_amt, sizeof(Ratio), ratio_cmp);

    graph_destroy(g);

    free(sm_dist);
    free(sc_dist);
    free(cm_dist);
    free(cs_dist);
    free(ms_dist);
    free(mc_dist);

    fclose(input);

    FILE* output = fopen(argv[2], "w");
    if (output == NULL) {
        printf("Error opening output file\n");
        return 1;
    }

    for (int i = 0; i < server_amt*client_amt; i++) {
        fprintf(output, "%d %d %.16lf\n", ratios[i].server_id, ratios[i].client_id, ratios[i].ratio);
    }

    fclose(output);
    free(ratios);
}
