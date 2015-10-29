#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

shellcmd xsh_getfreeblocks(int nargs, char *args[]) {
if(nargs >2)
  {
       	printf("Too many arguments !!\n USAGE : hello <Name> eg: Hello Sanket \n");
  }
  else
  {
	int i=0;
	struct memblk *freeptr;
	freeptr = &memlist;
	while(freeptr!=NULL)
	{
		printf("Block %d : %d \n",++i,(uint32)freeptr->mlength);
		freeptr=freeptr->mnext;	
	}
  }
  return 0;
}
