#include "globals.h"
#include <pthread.h>
#include <stdio.h>
void *Timer(void *hari_param){
    struct hariaren_parametroak *param;  
    int time_quantum=0;
    int tick;
    int done=0;
    param = (struct hariaren_parametroak *)hari_param;// Hariaren parametroak
    int maiztasuna = param -> maiztasuna;//Parametrotatik maiztasuna hartu
    pthread_mutex_lock(&tick_zenb);
    while(1){
        done++;
        if(tick==maiztasuna){   
            tick++;
            time_quantum++; //Quantuma handitzen joan  
        }
        pthread_cond_signal(&cond);
        pthread_cond_wait(&cond2, &tick_zenb);
    }
}
