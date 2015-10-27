/* queue.c - enqueue, dequeue */

#include <xinu.h>
#include <myqueue.h>

//struct myQent myQtab[myQSIZE];	/* Table of process queues	*/

/*------------------------------------------------------------------------
 *  enqueue  -  Insert a process at the tail of a queue
 *------------------------------------------------------------------------
 */
pid32 enQ(pid32 Q[],pid32 pid, int *head, int *tail)
{		
	if(*head == -1 && *tail == -1)	{
		Q[0] = pid;
		*head = 0;
		*tail = 0;
		//return 0;
	}	
	
	if (*tail >-1 && *tail<(myQSIZE-1))	{
		(*tail)++;
		Q[*tail] = pid;
		//return 0;
	}
	
	return pid;
}

/*------------------------------------------------------------------------
 *  dequeue  -  Remove and return the first process on a list
 *------------------------------------------------------------------------
 */
pid32 deQ(pid32 Q[], int *head, int *tail)			/* ID of process removed	*/
{
	if(*head == -1 && *tail == -1)	{
		return SYSERR;
	}
	pid32 pid=Q[*head];
	if(*head >-1 && *tail > -1 && *head == *tail && *head < myQSIZE)	{
		pid=Q[*head];		
		Q[*tail] = -1;
		*head = -1;
		*tail = -1;
		return pid;
	}	
	
	if (*head >-1 && *head<myQSIZE)	{
		Q[*head] = -1;
		(*head)++;
		pid=Q[*head];		
	}
	return pid;
}

bool isQempty(int* head, int* tail)
{
	if(*head == -1 && *tail == -1)
	{
		return TRUE;
	}
	if(*tail-*head < 0)
	{
		*head=-1;	
		*tail=-1;
		return TRUE;
	}	
	return FALSE;
}
