
#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------------------------------
 * xsh_hello - prints the welcome message
 *------------------------------------------------------------------------
 */
#define BUFFSIZE 1024
shellcmd xsh_udptest(int nargs, char *args[]) {

	/* Output info for '--help' argument */
	if (nargs <5 || nargs > 5) 
	{
		printf("Usage: udptest <REMOTE IP> <REMOTE PORT> <LOCAL PORT> <Message>");
		printf("Description:\n");
		printf("\tSends a UDP packet to a specific IP and PORT\n");		
		return 0;
	}
	
	udp_init();
	kprintf("\nUDP table initialized !!");
	int32 slot =0;
	uint32 target_ip;
	dot2ip(args[1],&target_ip);
	slot=udp_register(target_ip,atoi(args[2]),atoi(args[3]));
	kprintf("\nSlot obtained : %d",slot);
	udp_send(slot,args[4],strlen(args[4]));
	kprintf("\nMessage sent \n");
	char tempbuff[BUFFSIZE];
	int32 msglen = udp_recv(slot,tempbuff,BUFFSIZE,15000);
	if(msglen == -1)
	{
		printf("TimeOut!!\n");		
	}
	else
	{
		printf("Message Received :%s\n",tempbuff);	
	}
	return 0;
}
