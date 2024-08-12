#ifndef PQ_H
#define PQ_H

#include <stdbool.h>
#include "item.h"

typedef struct pq PQ;

PQ* PQ_init(int maxN); // cria uma min PQ com capacidade maxN
void PQ_insert(PQ* pq, Item v);   // Insere Item na PQ. A maior prioridade é a do Item com menor campo 'value'
Item PQ_delmin(PQ* pq);       // Remove Item com menor campo 'value' da PQ
void PQ_decrease_key(PQ* pq, int id, double value); // Muda a prioridade do nó com identificador 'id' para 'value'
Item PQ_min(PQ* pq);          // Retorna Item com menor campo 'value' da PQ
bool PQ_empty(PQ* pq);        // Retorna True se a PQ não tem elementos
int  PQ_size(PQ* pq);         // Número de elementos na PQ
void PQ_finish(PQ* pq);       // Libera memória

int PQ_contains(PQ* pq, int id);

#endif
