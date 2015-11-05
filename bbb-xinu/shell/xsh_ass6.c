#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <ass6.h>

void ass6_problem1();
void ass6_problem2_getstk();
void ass6_problem2_getmem();
void ass6_problem3();

shellcmd xsh_ass6(int nargs, char *args[]) {
if(nargs!=2)
  {
       	kprintf("Incorrect number of arguments !!\n");
	return 1;
  }
  else
  {
	char *temp = args[1];
	if(strlen(temp)>1)
	{
		kprintf("Invalid Argument format!!\n");
		return 1;
	}	
	if(atoi(args[1])==1)
	{
		ass6_problem1();
	}else if(atoi(args[1])==2)
	{
		ass6_problem2_getstk();
	}else if(atoi(args[1])==3)
	{
		ass6_problem2_getmem();
	}else if(atoi(args[1])==4)
	{
		ass6_problem3();
	}
	else
	{
		kprintf("Invalid Argument!! Arguments should be an option from 1-4.\n");
		return 1;
	}
  }
  return 0;
}

void ass6_problem1()
{
	MEMFREE_FLAG= FALSE;
	printf("Problem 1: Display Free blocks\n");
	int i=0;
	struct memblk *freeptr;
	intmask mask = disable();
	freeptr = &memlist;
	kprintf("Total Free Memory Available: %u\n",freeptr->mlength);
	freeptr=freeptr->mnext;	
	while(freeptr!=NULL)
	{
		kprintf("Size of Block %d : %u \n",++i,freeptr->mlength);
		kprintf("Address of Block : %u \n",freeptr);
		freeptr=freeptr->mnext;	
	}
	restore(mask);		
}

void ass6_problem2_getstk()
{
	MEMFREE_FLAG =TRUE;	
	kprintf("\nProblem 2 : Stack Memory allocated!\n");
	mygetstk(204);
	getstk(204);
	return;
}

void ass6_problem2_getmem()
{
	MEMFREE_FLAG = TRUE;	
	kprintf("\nProblem 2 : Heap Memory allocated!\n");
	mygetmem(204);
	getmem(204);
	return;
}


void ass6_problem3()
{
	pid32 pid = mycreate(testfunction, 1024, 10,"testfunction",1,5);
	kprintf("\nProblem 3: Test Function for checking the maximum allocated memory \nTest Process created with pid : %d\n",pid);
	resume(pid);
	
}


