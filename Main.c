#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include "eragiketak.h"
#include "globals.h"
#include "clock.h"
#include "timer.h"
#include "loader.h"
#include "scheduler-dispatcher.h"
#include "prozesadore.h"

Process_Queue *PQ;
Process_Queue *coreak;

pthread_mutex_t tick_zenb;
pthread_mutex_t proz;
pthread_cond_t cond;
pthread_cond_t cond2;

void sortu_hariak(int maiztasuna, int core){//Hariak sortzeko

    int i, err;
    pthread_t *hariak;
    pthread_t *cor;
    struct hariaren_parametroak *h_p;
    struct hariaren_parametroak *c_p;
    int hari_kop=5;

    hariak = malloc(hari_kop * sizeof(pthread_t));
    h_p = malloc(hari_kop * sizeof(struct hariaren_parametroak));
    cor = malloc(hari_kop * sizeof(pthread_t));
    c_p = malloc(hari_kop * sizeof(struct hariaren_parametroak));

    i=0;
    
    for(int k=0; k<core; k++){
    	c_p[k].haria_id.pid= k;
    }
    
    for(int j=0; j<hari_kop; j++){
    	h_p[j].maiztasuna = j;
    	h_p[j].haria_id.pid = j;
    }   
    
    err = pthread_create(&hariak[i], NULL, Clock, (void *)&h_p[i]);
    if(err > 0){
    fprintf(stderr, "Errore bat gertatu da hariak sortzean.\n");
    exit(1);
    }
    i++;
    
     
    err = pthread_create(&hariak[i], NULL, Timer, (void *)&h_p[i]);
    if(err > 0){
    fprintf(stderr, "Errore bat gertatu da hariak sortzean.\n");
    exit(1);
    }
    i++; 
   
    err = pthread_create(&hariak[i], NULL, loader, (void *)&h_p[i]);
    if(err > 0){
    fprintf(stderr, "Errore bat gertatu da hariak sortzean.\n");
    exit(1);
    }
    i++;

    err = pthread_create(&hariak[i], NULL, Secheduler_Dispatcher, (void *)&h_p[i]);
    if(err > 0){
    fprintf(stderr, "Errore bat gertatu da hariak sortzean.\n");
    exit(1);
    }
    i++;
    
    for(int j=0; j< core; j++){
	    err = pthread_create(&cor[j], NULL, Prozesadore, (void *)&c_p[i]);
	    if(err > 0){
	    fprintf(stderr, "Errore bat gertatu da hariak sortzean.\n");
	    exit(1);
	    }
    }
   
    for(i = 0; i < hari_kop; i++){ // Ume guztiak amaitu arte 
        pthread_join(hariak[i], NULL);
    }
    for(i = 0; i < core; i++){ // Ume guztiak amaitu arte 
        pthread_join(cor[i], NULL);
    }
    free(hariak);
    free(h_p);
    free(cor);
    free(c_p);
}

int main(int argc, char *argv[]){
    char *c;
    char *h;
    char *m;
    int maiztasuna;
    int prozesu;
    int core_kopuru;
    int hari_kopuru;
    int tamaina=100;
    //int hariak;
    int core;

    if(argc!=3){
	printf("Erabilpena: Erabili nahi duzun maiztasuna, coreak sartu.\n");
	exit(1);
    }
    maiztasuna = strtol(argv[1], &m, 10);//kanpotik sartu dugun maiztasuna lortzeko
    //hariak = strtol(argv[2], &h, 10);//sortuko ditugun prozesu ilara kopurua 
    core_kopuru = strtol(argv[2], &c, 10);//sortuko ditugun core kopurua
    hari_kopuru = strtol(argv[2], &c, 10);//Coreek edukiko dituen hariak
    
    //Memoria hasieratu
    mem_fisikoa = malloc(MEM_SIZE*sizeof(int));
    mem_addr = 1000;
    mem_p = 0;
    freespace = MEM_SIZE - mem_addr;
    mem_free = malloc(MEM_SIZE*sizeof(struct free_spaces));
    mem_free[0].addr = mem_addr;
    mem_free[0].size = freespace;
    free_count = 1;
    
    //mutexa sortu
    pthread_mutex_init(&tick_zenb, NULL);
    pthread_mutex_init(&proz, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_cond_init(&cond2, NULL);
 
    PQ=malloc(sizeof(Process_Queue));//Prozesu ilarak
  
    //coreak=malloc(core *sizeof(Process_Queue));//Coreak
    Sistema_hasieratu(core_kopuru, hari_kopuru);
    Hasieratu(PQ, tamaina);

    //for(int i=0; i<core; i++){//zenbat core erabili
    	//Hasieratu(&coreak[i], 100);
    //}
     //hariask sortu     
    sortu_hariak(maiztasuna, core_kopuru);
    //mutexak kentzeko
    pthread_mutex_destroy(&tick_zenb);
    pthread_mutex_destroy(&proz);
}
