#include <future.h>
sid32 queue_lock;
syscall future_get(future *f, int* value)
{	 
	queue_lock = semcreate(1);
	if(f->state ==FUTURE_EMPTY && f->flag == FUTURE_EXCLUSIVE)
	{
		f->state = FUTURE_WAITING;
		f->pid = getpid();
		while(true)
		{
			intmask mask=disable();							
			kprintf("");
			restore(mask);
			if(f->state==FUTURE_VALID)
			{
				intmask mask=disable();							
				*value=f->value;
				restore(mask);				
				return OK;	
			}
		}
		
	}
	if(f->state ==FUTURE_EMPTY && f->flag == FUTURE_QUEUE)
	{
		//Add it to the get queue
		intmask mask = disable();

		//SET EMPTY
		if(isQempty(&(f->set_head),&(f->set_tail)))
		{
			wait(queue_lock);			
			enQ(f->get_queue,getpid(),&(f->get_head),&(f->get_tail));
			signal(queue_lock);
			suspend(getpid());
			*value = f->value;	
		}
		else
		{
			pid32 tpid;
			wait(queue_lock);			
			tpid=deQ(f->set_queue, &(f->set_head), &(f->set_tail));
			signal(queue_lock);
                        resume(tpid);
			*value = f->value;	
			return OK;
		}

		restore(mask);
		return OK;
	}
	if(f->flag == FUTURE_SHARED)
	{
		if(f->state == FUTURE_EMPTY)
		{		
			intmask mask = disable();		//SET EMPTY
			enQ(f->get_queue,getpid(),&(f->get_head),&(f->get_tail));			
			suspend(getpid());
			*value = f->value;
			restore(mask);	
		return OK;
		}
		if(f->state == FUTURE_VALID)	
		{
			*value = f->value;
			return OK;
		}

	}
	
return SYSERR;
}
