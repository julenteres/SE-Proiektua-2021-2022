#ifndef __GLOBALS_H
#define __GLOBALS_H

#include <pthread.h>
extern pthread_mutex_t tick_zenb;
extern pthread_cond_t cond;
extern pthread_cond_t cond2;
extern pthread_mutex_t proz;

extern int time_quantum;
extern int tamaina;
extern int bar;
int core;

typedef struct mm{
	int pgb; //Orri taularen helbide fisikoa
	int code; //Kodearen helbide birtuala
	int data; //Datuen helbide birtuala
}mm_t;

struct PCB{//Prozesu bakoitzaren datu egitura
    int pid;
    int denb;
    int lehen;
    int ir[20];
    int pc; //execution address
    struct mm mem_man;
    int size;
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

struct CPU{
    struct core *coreak;
    int core_kop; 
};

struct core{
    struct hari *hariak;
    int hari_kop;
    int ir[20];
    int pc; //execution address
    int ptbr;
};

struct hari{
    int id;
    int kopurua;
};

struct free_spaces{
    int addr;
    int size;
};

extern Process_Queue *PQ;
extern Process_Queue *coreak;
extern int* mem_fisikoa;
extern volatile int freespace;
extern volatile int mem_addr;
extern volatile int mem_p; //page addr
extern struct free_spaces *mem_free;
extern volatile int free_count;

void *Clock(void *hari_param);
void *Timer(void *hari_param);
void *loader(void *hari_param);
void *Secheduler_Dispatcher(void *hari_param);
void *Prozesadore(void *hari_param);

#define LD 7
#define ST 7
#define ADD 5
#define EXIT 3

#define MEM_SIZE 4194304 //2²²

#endif
