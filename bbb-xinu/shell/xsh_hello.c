
#include <xinu.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

shellcmd xsh_hello(int nargs, char *args[]) {
  if(nargs==2)
  {
	int i=0;
	while(i<strlen(args[1]))
	{
		if(isalpha(args[1][i])==0)
		{
			printf("Invalid Type of argument.Argument must be a string. USAGE : hello <String>\n");
			return 1;
		} 
		i++;
	}   	
	printf("Hello %s , Welcome to the world of Xinu!!\n",args[1]);
  }
  else if(nargs >2)
  {
       	printf("Too many arguments !!\n USAGE : hello <Name> eg: Hello Sanket \n");
  }
  else
  {
	printf("Too Few arguments !!\n USAGE : hello <Name> eg: Hello Sanket \n ");	
  }
  return 0;
}
