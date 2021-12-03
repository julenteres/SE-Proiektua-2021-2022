#ifndef __GLOBALS_H
#define __GLOBALS_H

#include <pthread.h>
extern pthread_mutex_t tick_zenb;
extern pthread_cond_t cond;
extern pthread_cond_t cond2;
extern pthread_mutex_t proz;

extern int time_quantum;
int core;

struct PCB{//Prozesu bakoitzaren datu egitura
    int pid;
    int denb;
    int lehen;
};
struct hariaren_parametroak{
	struct PCB haria_id;
    	int denbora;
	int maiztasuna;
};
typedef struct{
	struct PCB *process_queue;
	int luzera;//Ilararen luzera
	int erab;//Ilaran erabiliak dauden kopurua
	int *okup;//Ilarako leku hori okupatua dagoen edo ez jakiteko(okupatua=1 ez okupatua=-1)
}Process_Queue;
extern Process_Queue *PQ;
extern Process_Queue *coreak;
void *Clock(void *hari_param);
void *Timer(void *hari_param);
void *Process_Generator(void *hari_param);
void *Secheduler_Dispatcher(void *hari_param);
void *Prozesadore(void *hari_param);
#endif
