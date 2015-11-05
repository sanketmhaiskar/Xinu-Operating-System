#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <ass6.h>

sid32 var1,var2;
shellcmd xsh_getfreeblocks(int nargs, char *args[]) {
if(nargs >2)
  {
       	printf("Too many arguments !!\n");
  }
  else
  {
	var1 = semcreate(0);
	var2 = semcreate(0);
	printf("Assignment 1\n");
	int i=0;
	struct memblk *freeptr;
	intmask mask = disable();
	freeptr = &memlist;
	while(freeptr!=NULL)
	{
		printf("Block %d : %u \n",++i,freeptr->mlength);
		freeptr=freeptr->mnext;	
	}
	restore(mask);
	pid32 pid = mycreate(testfunction, 1024, 10,"testfunction",1,5);
	struct procent *prptr = &proctab[pid];
	uint32 *tempptr;
	tempptr = (uint32 *)(prptr->prstkptr);
	uint32 temp = prptr->prstklen;
	uint32 *maxptr;
	maxptr = (uint32 *)(prptr->prstkbase) - temp;

	temp=0;
	kprintf("%d:%d:%d",maxptr,tempptr,temp);
	while(maxptr < tempptr)
	{
		*tempptr=(uint32)(-65534);
		tempptr--;
		temp++;
	}
	kprintf("%d:%d:%d",maxptr,tempptr,temp);
	kprintf("\nInitial Stack Size for pid %d : %d\n",pid,(prptr->prstkbase - prptr->prstkptr));

	resume(pid);
	wait(var1);

	mask = disable();
	temp=-1;
	tempptr = (uint32 *)(prptr->prstkbase);
	while(*tempptr!=(uint32)(-65534))
	{
		tempptr--;		
		temp++;
	}
	kprintf("Maximum Memory Used (in Bytes) :%d\n",temp*sizeof(uint32 *));
	kprintf("Final Stack Size for pid %d : %d\n",pid,(prptr->prstkbase - prptr->prstkptr));
	restore(mask);
	signal(var2);
	//mykill(pid);
	//sleep(5);
	//kprintf("Final Stack Size for pid %d : %d\n",pid,(prptr->prstkbase - prptr->prstkptr));
  }
  return 0;
}



