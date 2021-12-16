#include "globals.h"
#include "eragiketak.h"
#include <stdio.h> 
void *Secheduler_Dispatcher(void *hari_param){
	struct PCB P;//Sartuko den prozesua
	int zenb;
	while(1){
		if(Hutsa(PQ)){
		}else{
			pthread_mutex_lock(&proz);
			if(!Hutsa(PQ)){
				P=Lehentasuna(PQ);
				zenb= Libre(coreak);
				SartuIlaran(&coreak[zenb], &P);
                	//ListaImprimatu(PQ);
                    //ListaImprimatu(coreak);
                	
			}
			pthread_mutex_unlock(&proz);
		}	
	}
}
