#include <future.h>

syscall future_free(future* f)
{
	intmask mask = disable();	
	int returnval=freemem(f,sizeof(future));
	restore(mask);
	return returnval;
}
