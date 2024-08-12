#include <stdio.h>
#include <stdlib.h>
#include "../include/PQ.h"
#include "../include/item.h"

struct pq {
    Item* pq;
    int* map;
    int N;
};

static void swap(PQ* pq, int i, int j) {
    exch(pq->pq[i], pq->pq[j]);
    pq->map[id(pq->pq[i])] = i;
    pq->map[id(pq->pq[j])] = j;
}

void fix_up(PQ* pq, int k) {
    while (k > 1 && more(pq->pq[k/2], pq->pq[k])) {
        swap(pq, k, k/2);
        k = k/2;
    }
}

void fix_down(PQ* pq, int sz, int k){
  while (2*k <= sz) {
    int j = 2*k;
    if (j < sz && more(pq->pq[j], pq->pq[j+1])){
      j++;
    }
    if (!more(pq->pq[k], pq->pq[j])) {
      break;
    }
    swap(pq, k, j);
    k = j;
  }
}

PQ* PQ_init(int maxN) {
    PQ* pq = (PQ*) calloc(1, sizeof(PQ));
    pq->pq = (Item*) calloc((maxN+1), sizeof (Item));
    pq->map = (int*) calloc((maxN+1), sizeof (int));
    pq->N = 0;

    return pq;
}

void PQ_insert(PQ* pq, Item v) {
    pq->N++;
    pq->pq[pq->N] = v;
    pq->map[id(v)] = pq->N;
    fix_up(pq, pq->N);
}

Item PQ_delmin(PQ* pq) {
    Item min = pq->pq[1];
    swap(pq, 1, pq->N);
    pq->N--;
    fix_down(pq, pq->N, 1);
    return min;
}

Item PQ_min(PQ* pq) {
    return pq->pq[1];
}

void PQ_decrease_key(PQ* pq, int id, double value) {
    int i = pq->map[id];
    value(pq->pq[i]) = value;
    fix_up(pq, i);
}

bool PQ_empty(PQ* pq) {
    return pq->N == 0;
}

int  PQ_size(PQ* pq) {
    return pq->N;
}

void PQ_finish(PQ* pq) {
    free(pq->pq);
    free(pq->map);
    free(pq);
}

int PQ_contains(PQ* pq, int id) {
    return pq->map[id];
}
