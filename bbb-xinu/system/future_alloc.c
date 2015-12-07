#include <future.h>

future* future_alloc(int future_flag)
{
	future *f=(future*)getmem(sizeof(future));
    	if ((int)f==SYSERR)
	{
  	      return NULL; 
        }
    f->state=FUTURE_EMPTY;
    f->flag=future_flag;

   if(future_flag == FUTURE_QUEUE || future_flag == FUTURE_SHARED)
   {
    int i;
    for(i=0; i<myQSIZE; i++)	
    {
    	f->set_queue[i] = -1; 
	f->get_queue[i] = -1; 
    }
	f->set_head = -1;
	f->set_tail = -1;
	f->get_head = -1;
	f->get_tail = -1;	
   }

return f;
	
}
