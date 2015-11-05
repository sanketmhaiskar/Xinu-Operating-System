#include <xinu.h>
#include <ass6.h>

void testfunction(int n)
{
	//pid32 pid =getpid();
	if(n>0)
	{

		//struct procent *prptr = &proctab[pid];
		testfunction(n-1);
	}
	/*else
	{
	signal(var1);
	wait(var2);
	}*/
//return getpid();
}
