#include "globals.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
//Prozesuen hasieraketak egiteko
void Hasieratu(Process_Queue *PQ, int tamaina){
	PQ->erab=0;
	PQ->luzera=tamaina;
	PQ->process_queue= malloc(tamaina * sizeof(struct PCB));	
	PQ->okup= malloc(tamaina * sizeof(int));
	int i;
	for(i=0; i<tamaina; i++){
		PQ-> okup[i]=-1;
	}
}

void Sistema_hasieratu(int corea, int haria){
    struct CPU *cpuak = malloc(sizeof(struct CPU));
    cpuak->core_kop = corea;
    for(int i=0; i<cpuak->core_kop; i++){
        cpuak->coreak[i] = malloc(sizeof(struct core));
        cpuak->coreak[i].hari_kop = haria;
        for(int j=0; j<cpuak->coreak[i].hari_kop; j++){
            cpuak->coreak[i].hariak[j] =malloc(sizeof(struct hari));
            cpuak->coreak[i].hariak[j].id=j;
            cpuak->coreak[i].hariak[j].kopurua= haria;
        }
    }
}

//Ilaran prozesuak sartzeko
void SartuIlaran(Process_Queue *PQ, struct PCB *pr){
	int i;
	for(i=0; i<PQ->luzera; i++){
		if(PQ->okup[i]==-1){
			PQ->erab++;
			memcpy(&(PQ->process_queue[i]), pr, sizeof(struct PCB));
			PQ->okup[i]=1;
			break;
		}else{
		}
	}
}

//Ilara betea dagoen jakiteko
int Betea(Process_Queue *PQ){
	if(PQ->luzera==PQ->erab){
		return 1;
	}
	return 0;
}

//Ilara hutsa dagoen jakiteko
int Hutsa(Process_Queue *PQ){
	if(PQ->erab==0){
		return 1;
	}
	return 0;
}

//Ilarako prozesuen artean lehentasun handienekoa lortzeko
struct PCB Lehentasuna(Process_Queue* PQ){
	struct PCB handiena;
	int bet=-1;
	int zein;
	for(int i=0; i<=PQ->luzera; i++){
		if(bet==-1 && PQ->okup[i]!=-1){
			bet=0;
			handiena=PQ->process_queue[i];
			zein=i;
		}else{
			if(PQ->okup[i]!=-1){
				if(handiena.lehen<PQ->process_queue[i].lehen){
					handiena=PQ->process_queue[i];
					zein=i;
				}
			}
		}
	}
	PQ->okup[zein]=-1;
	PQ->erab--;
	return handiena;
}
//Ilarak impìmatzeko
void ListaImprimatu(Process_Queue *PQ){
	int i;
    int tamaina=100;
    printf( "**********");
	for(i=0; i<=tamaina; i++){
		printf( "%d.", PQ->process_queue[i].pid);
	}
    printf( "**********\n");
}

//Core-ilaren libreena lortzeko
int Libre (Process_Queue *coreak){
	Process_Queue *libre;
	int i;
	int zenb=0;
	for(i=0; i<core; i++){
		if(coreak[i].erab <libre->erab){
			zenb=i;
		}
	}
	return zenb;
}	

