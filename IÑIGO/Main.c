#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>
#include "eragiketak.h"
#include "globals.h"
#include "clock.h"
#include "timer.h"
#include "process-generator.h"
#include "scheduler-dispatcher.h"
#include "prozesadore.h"

Process_Queue *PQ;
Process_Queue *coreak;

pthread_cond_t cond;
pthread_cond_t cond2;

pthread_mutex_t tick_zenb;
pthread_mutex_t proz;

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
    
    for(int j=0; j<hari_kop-1; j++){
    	h_p[j].maiztasuna = j;
    	h_p[j].haria_id.pid = j;
    }   
    
    err = pthread_create(&hariak[i], NULL, Clock, (void *)&h_p[i]);
    if(err > 0){
    fprintf(stderr, "Errore bat gertatu da hariak sortzean.\n");
    exit(1);
    }
    i++;
    
    for(int j=0; j<8; j++){  
        err = pthread_create(&hariak[i], NULL, Timer, (void *)&h_p[i]);
        if(err > 0){
        fprintf(stderr, "Errore bat gertatu da hariak sortzean.\n");
        exit(1);
        }
        j++;
    }
    i++; 
   
    err = pthread_create(&hariak[i], NULL, Process_Generator, (void *)&h_p[i]);
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
    int core;

    if(argc!=4){
	printf("Erabilpena: Erabili nahi duzun maiztasuna, hariak eta coreak sartu.\n");
	exit(1);
    }
    maiztasuna = strtol(argv[1], &m, 10);//kanpotik sartu dugun maiztasuna lortzeko
    //prozesu = strtol(argv[2], &h, 10);//sortuko ditugun prozesu ilara kopurua 
    core = strtol(argv[3], &c, 10);//sortuko ditugun core kopurua
    //mutexa sortu
    pthread_mutex_init(&tick_zenb, NULL);
    pthread_mutex_init(&proz, NULL);
    pthread_cond_init(&cond, NULL);
    pthread_cond_init(&cond2, NULL);
 
    PQ=malloc(core *sizeof(Process_Queue));//Prozesu ilarak
    coreak=malloc(core *sizeof(Process_Queue));//Coreak
/*    for(int i=0; i<prozesu; i++){//zenbat hari sortu
    	Hasieratu(&PQ[i], 100);
    }*/
    for(int i=0; i<core; i++){//zenbat core erabili
    	Hasieratu(&coreak[i], 100);
    }
     //hariask sortu     
    sortu_hariak(maiztasuna, core);
    //mutexak kentzeko
    pthread_mutex_destroy(&tick_zenb);
    pthread_mutex_destroy(&proz);
}
