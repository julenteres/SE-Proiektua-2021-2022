#include "globals.h"
#include "eragiketak.h"
void *Prozesadore(void *hari_param){
	struct PCB PT;
	struct hariaren_parametroak *param;
	param = (struct hariaren_parametroak *)hari_param;
	int i;
	int x;
	int time_quantum;

	while(1){
		 if(time_quantum ==100){
		        pthread_mutex_lock(&proz);
		        time_quantum=0;
		        x = Libre(coreak);
		        //Lehentasun handiena daukan corea lortu eta memoria fisikoan jarri.
			PT=Lehentasuna(&coreak[x]);
			if(PT.denb > 100){
				PT.denb=PT.denb- 100;
				if(PT.lehen - 5 < 0){
					PT.lehen=0;
				}else{	
					PT.lehen=PT.lehen - 5;
				}
				SartuIlaran(&coreak[x], PT);
			}
                pthread_mutex_unlock(&proz);  
            	}
	    
	}
}
