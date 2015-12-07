/* clkhandler.c - clkhandler */

#include <xinu.h>

/*-----------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *-----------------------------------------------------------------------
 */
void	clkhandler()
{

	static uint32 count1000 = 1000;	/* variable to count 1000ms */
	static uint32 reset_arp_count=0;
	struct	arpentry  *arptr;
	int32 i;	
	volatile struct am335x_timer1ms *csrptr = 0x44E31000;
					/* Pointer to timer CSR	    */

	/* If there is no interrupt, return */

	if((csrptr->tisr & AM335X_TIMER1MS_TISR_OVF_IT_FLAG) == 0) {
		return;
	}

	/* Acknowledge the interrupt */

	csrptr->tisr = AM335X_TIMER1MS_TISR_OVF_IT_FLAG;

	/* Decrement 1000ms counter */

	count1000--;

	/* After 1 sec, increment clktime */

	if(count1000 == 0) {
		clktime++;
		reset_arp_count++;
		count1000 = 1000;
	}
	/*Reset arp counter and clear arp cache .Checks every 30 seconds if there is a stale entry.*/
	if(reset_arp_count >=30)
	{
		reset_arp_count=0;
		for (i=0; i<ARP_SIZ; i++) {
		arptr = &arpcache[i];
		if(((clktime-arptr->arp_age)>300) && arptr->arstate != AR_FREE)
		{
			arptr->arstate = AR_FREE;
			arptr->arp_age = clktime;	
			kprintf("\nARP cache Entry %d deleted.\n",i+1);
		}
		}
	}
	/* check if sleep queue is empty */

	if(!isempty(sleepq)) {

		/* sleepq nonempty, decrement the key of */
		/* topmost process on sleepq		 */

		if((--queuetab[firstid(sleepq)].qkey) == 0) {

			wakeup();
		}
	}

	/* Decrement the preemption counter */
	/* Reschedule if necessary	    */

	if((--preempt) == 0) {
		preempt = QUANTUM;
		resched();
	}
}
