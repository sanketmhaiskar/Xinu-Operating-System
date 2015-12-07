#include <future.h>
sid32 queue_lock;

syscall future_set(future *f, int *value)
{
	queue_lock =semcreate(1);	
	if(f->state ==FUTURE_VALID && f->flag==FUTURE_EXCLUSIVE)
	{
		return SYSERR;
	}	
	if((f->state == FUTURE_WAITING || f->state == FUTURE_EMPTY) && f->flag==FUTURE_EXCLUSIVE)
	{
		f->state = FUTURE_VALID;
		f->value=(int)*value;	
		return OK;
	}
	
	if(f->flag == FUTURE_QUEUE) 
	{
			pid32 tpid;
                        //GET EMPTY
			if(isQempty(&(f->get_head),&(f->get_tail)))
			{
				f->value=(int)*value;
				tpid=enQ(f->set_queue, getpid(), &(f->set_head), &(f->set_tail));
                        	suspend(getpid()); // BOTH EMPTY
				return OK;
			}
			else
			{
				f->value=(int)*value;
				tpid=deQ(f->get_queue, &(f->get_head), &(f->get_tail));
                        	resume(tpid);
				return OK;
			}
			
	}
	if(f->flag == FUTURE_SHARED )
	{
		if(f->state == FUTURE_VALID)
		{			
			return SYSERR;
		}	
		if(f->state == FUTURE_EMPTY)
		{
			f->value=(int)*value;	
			f->state = FUTURE_VALID;
		
		while(!isQempty(&(f->get_head),&(f->get_tail)))
		{
			pid32 tpid;			
			f->value=(int)*value;
			tpid=deQ(f->get_queue, &(f->get_head), &(f->get_tail));
                        resume(tpid);
		}
		}
		return OK;

	}
		
	
return SYSERR;
}
