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
volatile int mem_p; 
struct free_spaces *mem_free;

//Memorian dagoen toki librea bilatzeko
int bilatu_tokia_memorian(int size){
    int i;
    int addr = -1;

    for (i=0; i<free_count; i++){
	if (mem_free[i].size >= size){
	    addr = mem_free[i].addr;
	    
	    if (mem_free[i].size > size){
		mem_free[i].addr += size;
		mem_free[i].size -= size;//memoria libreari kendu erabili behar duzuna
	    }
	}
    }
    return addr;
}


void *loader(void *hari_param){
int zenb;
int bar=0;
int i=0;
int p_size=0;
char line[16];
FILE *elf;
struct PCB P;//Prozesua sortzeko
mm_t mm; //mm sortzeko
char ira[20];
char file[23];
unsigned char   op, reg1, reg2, reg3;
unsigned int v_address, bin, bal;
while(1){
	zenb = rand() % 1000;
	if(zenb==0){
		
		sprintf(file, "Fitxategiak/prog%03d.elf",i);//programa desberdinak lortzeko prog000.elf prog001.elf
    		elf=fopen(file, "r");//fitxategia ireki
    		if(elf=NULL){
    			fprintf(stderr, "[ERR] Ezin da fitxategia ireki");
    			exit(-1);
    		}
		while(fgets(line, sizeof(line), elf) != NULL){//linea bat irakurtzeko
    			p_size++;//Zenbat 
    		}
    		mem_addr=bilatu_tokia_memorian(p_size);//memorian tokia bilatzeko
    		if(mem_addr != -1){
			freespace-=p_size;//Memorian dagoen toki librea eguneratu
			fscanf(elf, "%s %x", ira, &mm.code);//.code irakurtzeko
    			if (strncmp(ira, ".text",5)){//kopia egiteko
				fprintf(stderr, "[ERR] .text ez da aurkitzem");
				op = (bin >> 28) & 0x0F;
        			reg1 = (bin >> 24) & 0x0F; 
        			reg2 = (bin >> 20) & 0x0F; 
        			reg3 = (bin >> 16) & 0x0F;
        			v_address = bin & 0x00FFFFFF;
        			switch(op){
        				case 0://ld
        					printf("0x%06X: [%08X] ld r%d,0x%06X\n", mem_addr, bin, reg1, v_address);
        					break;
        				case 1://st
        					printf("0x%06X: [%08X] st r%d,0x%06X\n", mem_addr, bin, reg1, v_address);
        					break;
        				case 2://add
        					printf("0x%06X: [%08X] add r%d, r%d, r%d\n", mem_addr, bin, reg1, reg2, reg3);
        					break;
        				case 3: // sub
            				case 4: // mul
            				case 5: // div
            				case 6: // and
            				case 7: // or
            				case 8: // xor
        				case 9:  // mov
            				case 10: // cmp
            				case 11: // b
            				case 12: // beq
            				case 13: // bgt
            				case 14: // blt
            				case 15://exit
        					printf("0x%06X: [%08X] exit", mem_addr, bin);
        					break;
        			}
        			mem_addr=mem_addr+4;
				exit(-1);
    			}
    		
    			fscanf(elf, "%s %x", ira, &mm.data);//.data irakurtzeko
    			if (strncmp(ira, ".data",5)){//kopia egiteko
				fprintf(stderr, "[ERR] .data ez da aurkitzen");
				printf("0x%06X: [%08X] %d\n", mem_addr, bin, bal);
				mem_addr=mem_addr+4;
				exit(-1);
    			}
    			//mm-ren hasieraketa
    			mem_fisikoa[mem_p] = mem_addr;
    			mm.pgb = mem_p; //Orri taularen helbidea
    			mem_p++;
    			P.pc = mem_addr; //Lehenengo komandoaren helbidea
    		
    			while (fscanf(elf, "%8x", &bin) != EOF){//memorian fitxategia kargatzeko
				mem_fisikoa[mem_addr] = bin;
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
    			memset(P.ir, 0, 20*sizeof(int));//Ir erregistroan kopia egiteko
    		
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
