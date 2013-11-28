#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
void func()
{
printf("A signal has been received\n");
}
main()
{
int  i ;
signal(18,func);
printf("Processing signal function has been set\n");
i = fork(  );
if (i == 0)
  { printf("Child process is now executing!\n");
kill(getppid( ),18);
sleep(10);
printf("child finished\n");
	 exit(0);
	}

sleep(10);
printf("This is the parent\n");
kill(i,18);
wait( );
printf("parent finished\n");
exit(0);
}
