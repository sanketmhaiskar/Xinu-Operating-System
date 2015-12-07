#include <ctype.h>
#include <future.h>
#include<stdlib.h>

int n;
sid32 produced,consumed;
shellcmd xsh_prodcons(int nargs, char *args[]) 
{
	n=0;
	int count =2000;
	if(nargs==2)
 	 {
				
		if (nargs == 2 && strncmp(args[1], "--help", 7) == 0) {
			kprintf("USAGE : prodcons <Positive Number > | Number argument is optional\n");
			return 0;
		}
		else if(nargs == 2 && strncmp(args[1], "-f", 3) == 0) 
		{

			future *f_exclusive, *f_shared, *f_queue;
   			f_exclusive = future_alloc(FUTURE_EXCLUSIVE);
 			f_shared = future_alloc(FUTURE_SHARED);
			f_queue = future_alloc(FUTURE_QUEUE);
			
			
			resume( create(future_cons, 1024, 20, "fcons1", 1, f_exclusive) );
  			resume( create(future_prod, 1024, 20, "fprod1", 1, f_exclusive) );

  			resume( create(future_cons, 1024, 20, "fcons2", 1, f_shared) );
  			resume( create(future_cons, 1024, 20, "fcons3", 1, f_shared) );
  			resume( create(future_cons, 1024, 20, "fcons4", 1, f_shared) ); 
  			resume( create(future_cons, 1024, 20, "fcons5", 1, f_shared) );
  			resume( create(future_prod, 1024, 20, "fprod2", 1, f_shared) );

  		
			resume( create(future_cons, 1024, 20, "fcons6", 1, f_queue) );
  			resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
  			resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
			resume( create(future_cons, 1024, 20, "fcons7", 1, f_queue) );
			resume( create(future_prod, 1024, 20, "fprod3", 1, f_queue) );
			resume( create(future_prod, 1024, 20, "fprod4", 1, f_queue) );
			resume( create(future_prod, 1024, 20, "fprod5", 1, f_queue) );
			resume( create(future_prod, 1024, 20, "fprod6", 1, f_queue) );
  
			future_free(f_exclusive);
			future_free(f_shared);
			future_free(f_queue);

			return 0;
		}
		else
		{
			int i=0;				
			char *str = args[1];	
			str[strlen(str)]='\0';
			while(i<strlen(str))
			{
				if(!isdigit(str[i]))
				{
					kprintf("Invalid Argument type !! Try '%s --help' for more information\n",args[0]);
					return 1;
				}
				i++;
			}
			count = atoi(str);
			if(count==0)
			{
				kprintf("Please enter a non-zero positive number\n");
				return 1;
			}
       		}
		
  	}
  	else if(nargs >2)
  	{
       		kprintf("Too many arguments !!\n USAGE : prodcons <Positive Number> | Number argument is optional\n");
		return 1;
  	}
	

	consumed=semcreate(1);
	produced=semcreate(0);	
	resume(create(producer, 1024, 20, "producer", 1, count));	
	resume(create(consumer, 1024, 20, "consumer", 1, count));
 	return 0;

}
