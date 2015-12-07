#include <prodcons.h>

 void producer(int count)
 {
      	int32 i;
	
	for( i=1 ; n<count ; i++ )
	{
		wait(consumed);		
		n=i;
		printf("\nProduced  : %d", n);
		signal(produced);
	}	
	semdelete(produced);
 }

