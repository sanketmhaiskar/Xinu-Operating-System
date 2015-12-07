#include <future.h>
#include <stdlib.h>
#include <string.h>
int TEST;

uint network_cons(future *fut,int32 slot,char *str) {

  int i, status;
  intmask mask;
  mask = disable();
  kprintf("\nString sent for length calculation :%s:%d\n",str,strlen(str));
  restore(mask);
  udp_send(slot,str,strlen(str));
  status = future_get(fut, &i);
  if (status < 1) {
    kprintf("future_get failed\n");
    return 1;
  }
  mask = disable();
  kprintf("\nLength of the String is : %d\n", i);
  restore(mask);
return OK;
}


uint network_prod(future *fut,int32 slot) {

  int j,status;
  /*j = (int)fut;
  for (i=0; i<1000; i++) {
    j += i;
  }*/

//j=5;
//j=TEST++;
  char tempbuff[1024];
  int32 msglen = udp_recv(slot,tempbuff,1024,15000);
	if(msglen == -1)
	{
		printf("TimeOut!!\n");	
		return 1;	
	}
	else
	{
		printf("Message Received :%s\n",tempbuff);	
	
       		j= atoi(tempbuff);
  		status = future_set(fut, &j);
  		intmask mask;
  		mask=disable();
  		if (status < 1) {
  			kprintf("future_set failed\n");
  			restore(mask);
    			return 1;
  		}
  		restore(mask);
  		return OK;
	}
}
	
