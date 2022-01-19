#include "globals.h"
#include "eragiketak.h"
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// ALDAGAI GLOBALAK //
int* mem_fisikoa;
volatile int freespace;
volatile int mem_addr;
volatile int mem_p; //page addr
struct free_spaces *mem_free;
volatile int free_count;

int bilatu_tokia_memorian(int size){
    int i;
    int addr = -1;

    for (i=0; i<free_count; i++){
	if (mem_free[i].size >= size){
	    addr = mem_free[i].addr;
	    
	    // update the free space incase it was bigger
	    if (mem_free[i].size > size){
		mem_free[i].addr += size;
		mem_free[i].size -= size;
	    }
	}
    }
    return addr; // -1 => error
}


void *loader(void *hari_param){
int zenb, lag;
int bar=0;
int i=0;
int p_size=0;
char line[16];
FILE *elf;
struct PCB P;//Prozesua sortzeko
mm_t mm; //mm sortzeko
char ira[20];
char file[23];
while(1){
	zenb = rand() % 1000;
	if(zenb==0){
		
		sprintf(file, "prog%d.elf",i);
    		elf=fopen(file, "r");//fitxategia ireki
    		if(elf=NULL){
    			fprintf(stderr, "[ERR] Ezin da fitxategia ireki");
    			exit(-1);
    		}
		while(fgets(line, sizeof(line), elf) != NULL){//linea bat irakurtzeko
    		p_size++;
    		}
    		p_size=(p_size-2)*4;
    		mem_addr=bilatu_tokia_memorian(p_size);//memoria bilatzeko
    		if(mem_addr != -1){
			freespace-=p_size;
			fscanf(elf, "%s %x", ira, &mm.code);
    			if (strncmp(ira, ".text",5)){
				fprintf(stderr, "[ERR] .text missing");
				exit(-1);
    			}
    		
    			fscanf(elf, "%s %x", ira, &mm.data);
    				if (strncmp(ira, ".data",5)){
				fprintf(stderr, "[ERR] .data missing");
				exit(-1);
    			}
    		
    			mem_fisikoa[mem_p] = mem_addr;
    			mm.pgb = mem_p; //Orri taularen helbidea
    			mem_p++;
    			P.pc = mem_addr; //Lehenengo komandoaren helbidea
    		
    			while (fscanf(elf, "%8x", &lag) != EOF){
				mem_fisikoa[mem_addr] = lag;
				mem_addr += 4;
				P.size++;
    			}
    			fclose(elf);
    		
    			//PROZESUAREN HASIERAKETA
    			P.pid = bar;//Prozesuaren zenbakia
			P.denb = rand() % 500;//Prozesuak behar duen denbora exekutatzeko
			P.lehen = rand() % 100;//Prozesuak daukan lehentasuna
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
		i=(i+1)%50;
		p_size=0;
		}
	}
}

}
