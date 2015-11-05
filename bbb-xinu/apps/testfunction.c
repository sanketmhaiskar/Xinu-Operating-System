#include <xinu.h>
#include <ass6.h>

void testfunction(int n)
{
	if(n>0)
	{
		testfunction(n-1);
	}
}
