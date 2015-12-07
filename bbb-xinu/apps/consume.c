#include <prodcons.h>

 void consumer(int count)
 {
	//int32 i=0;

   	while(1)
	{	
		wait(produced);
		printf("\nConsumed : %d\n",n);
		if(n>=count)
		{
			break;
		}
		signal(consumed);
	}
	semdelete(consumed);
 }

