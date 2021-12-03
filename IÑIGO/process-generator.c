#include "globals.h"
#include "eragiketak.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
void *Process_Generator(void *hari_param){
int zenb;
struct PCB P;//Prozesua sortzeko
int i=0; //Prozesuak zenbatzeko
while(1){
	zenb = rand() % 1000;
	if(zenb==0){
		P.pid = i;//Prozesuaren zenbakia
		P.denb = rand() % 500;//Prozesuak behar duen denbora exekutatzeko
		P.lehen = rand() % 100;//Prozesuak daukan lehentasuna
		if(Betea(PQ)==0){
			pthread_mutex_lock(&proz);
			SartuIlaran(PQ, P);//PCB-ak ilaran sartu
			pthread_mutex_unlock(&proz);
			i++;
		}else{
		}//Array-a betea badago itxaron.
	}
}

}
