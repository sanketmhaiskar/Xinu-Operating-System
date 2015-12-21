#include <future.h>
#include <stdlib.h>
#include <string.h>
int TEST;

uint network_cons(future *fut,int32 slot,char *str) {

  int i, status;
  intmask mask;
  mask = disable();
  kprintf("\nString sent for length calculation !!\n");
  restore(mask);
  udp_send(slot,str,strlen(str));
  status = future_get(fut, &i);
  if (status < 1) {
    kprintf("\nFuture_get failed !!\n");
    return 1;
  }
  mask = disable();
  kprintf("\nLength of the String is : %d\n", i);
  restore(mask);
  future_free(fut);
return OK;
}


uint network_prod(future *fut,int32 slot) {

  	int j,status;  
  	char tempbuff[1024];
  	int32 msglen = udp_recv(slot,tempbuff,1024,15000);
	intmask mask;
	mask=disable();
	if(msglen <0)
	{
		printf("\nTimeOut!!\n");	
		return 1;	
	}
	else
	{	
		printf("\nMessage Received :%s\n",tempbuff);	
       		j= atoi(tempbuff);
  		status = future_set(fut, &j);
  		
  		if (status < 1) {
  			kprintf("\nFuture_set failed !!\n");
  			restore(mask);
			future_free(fut);
    			return 1;
  		}
  		restore(mask);
  		return OK;
	}
}
	
