
#include <xinu.h>
#include <stdio.h>
#include <stdlib.h>

/*------------------------------------------------------------------------
 * xsh_hello - prints the welcome message
 *------------------------------------------------------------------------
 */
#define BUFFSIZE 1024
shellcmd xsh_udpcs(int nargs, char *args[]) {

	/* Output info for '--help' argument */
	if (nargs <1 || nargs > 1) 
	{
		printf("Usage: udptest <REMOTE IP> <REMOTE PORT> <LOCAL PORT> <Message>");
		printf("Description:\n");
		printf("\tSends a UDP packet to a specific IP and PORT\n");		
		return 0;
	}
	
	udp_init();
	kprintf("\nUDP table initialized !!");
	int32 slot =0;
	uint32 server;
	dot2ip("192.168.1.100",&server);
	slot=udp_register(server,8888,8888);
	kprintf("\nSlot obtained : %d",slot);
	udp_send(slot,args[1],strlen(args[1]));
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
