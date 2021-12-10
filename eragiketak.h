#ifndef __ERAGIKETAK__H
#define __ERAGIKETAK__H

#include "globals.h"

void Hasieratu(Process_Queue *PQ, int tamaina);
void SartuIlaran(Process_Queue *PQ, struct PCB pr);
int Betea(Process_Queue *PQ);
int Hutsa(Process_Queue *PQ);
struct PCB Lehentasuna(Process_Queue *PQ);
void ListaImprimatu(Process_Queue *PQ);
int Libre (Process_Queue *coreak);
#endif
