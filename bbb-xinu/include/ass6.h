
#include <stdbool.h>
#include <string.h>

#ifndef _ASS6_H_
#define _ASS6_H_
extern sid32 var1,var2;
extern bool MEMFREE_FLAG ;
extern void testfunction(int);
/* in file mycreate.c */

extern	pid32	mycreate(void *, uint32, pri16, char *, uint32, ...);

extern	char	*getstk(uint32);

#endif 
