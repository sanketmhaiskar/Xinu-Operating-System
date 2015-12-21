
#include <ctype.h>
#include <future.h>
#include <stdlib.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_hello - prints the welcome message
 *------------------------------------------------------------------------
 */
#define BUFFSIZE 1024
shellcmd xsh_networkfutures(int nargs, char *args[]) {


	if (nargs <2 || nargs > 2) 
	{
		printf("Usage: networkfutures <Message>");
		printf("Description:\n");
		printf("\tSends a message \n");		
		return 0;
	}
	
	future *f_exclusive;	
	f_exclusive = future_alloc(FUTURE_EXCLUSIVE);

	udp_init();
	kprintf("\nUDP table initialized !!");
	int32 slot =0;
	uint32 target_ip;
	dot2ip("192.168.1.100",&target_ip);
	slot=udp_register(target_ip,5555,5555);
	kprintf("\nSlot obtained for consumer : %d",slot);
	resume( create(network_cons, 1024, 20, "fcons1", 3, f_exclusive,slot,args[1]) );
  	resume( create(network_prod, 1024, 20, "fprod1", 3, f_exclusive,slot) );
		
	return 0;
	
}
