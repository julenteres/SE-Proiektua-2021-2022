#include "globals.h"
void *Clock(void *hari_param){//Erlojua sortzeko
    int done;
    int tenp_kop=8;
	while(1){
		pthread_mutex_lock(&tick_zenb);
        while(done<tenp_kop){
            pthread_cond_wait(&cond, &tick_zenb);
            done=0;
            cond_broadcast(&cond2);
        }
		pthread_mutex_unlock(&tick_zenb);
	}
}
