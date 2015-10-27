#include <xinu.h>
#include <stdio.h>

/*------------------------------------------------------------------------
 * xsh_reset - reset the machine 
 *------------------------------------------------------------------------
 */
shellcmd xsh_reset(int nargs, char *args[])
{

    
 	 volatile uint32 *prm_rstctrl =(volatile uint32 *) 0x44E00F00; 
	//getting the address of the resgister 

	*prm_rstctrl =0x01; // Generate a warm software reset (Setting the LSB to 1)

    return 0;
}
