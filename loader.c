#include "globals.h"
#include "eragiketak.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
void *loader(void *hari_param){
int zenb, lag;
int bar=0;
struct PCB P;//Prozesua sortzeko
mm_t mm; //mm sortzeko
char ira[20];
FILE *file = fopen(fileno, "f");
while(1){
	zenb = rand() % 1000;
	if(zenb==0){
		P.pid = bar;//Prozesuaren zenbakia
		P.denb = rand() % 500;//Prozesuak behar duen denbora exekutatzeko
		P.lehen = rand() % 100;//Prozesuak daukan lehentasuna
		
		fscanf(file, "%s %x", ira, &mm.code);
    		if (strncmp(ira, ".text",5)){
			fprintf(stderr, "[ERR] .text missing");
			exit(-1);
    		}
    		
    		fscanf(file, "%s %x", ira, &mm.data);
    			if (strncmp(ira, ".data",5)){
			fprintf(stderr, "[ERR] .data missing");
			exit(-1);
    		}
    		
    		mem_fisikoa[mem_p] = mem_addr;
    		mm.pgb = mem_p; //process page index
    		mem_p++;
    		P.pc = mem_addr; //first command address
    		
    		while (fscanf(file, "%8x", &lag) != EOF){
			mem_fisikoa[mem_addr] = lag;
			mem_addr += 4;
			P.size++;
    		}
    		fclose(file);
    		
    		P.mem_man=mm;
    		P.size *=4;
    		memset(P.ir, 0, 20*sizeof(int));
    		
		if(Betea(PQ)==0){
			pthread_mutex_lock(&proz);
			SartuIlaran(PQ, &P);//PCB-ak ilaran sartu
			pthread_mutex_unlock(&proz);
            		ListaImprimatu(PQ);
			bar++;
		}else{
		}//Array-a betea badago itxaron.
	}
}

}
