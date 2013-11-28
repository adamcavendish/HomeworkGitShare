#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
void  func( )
{  printf("This is func\n");  }
main( )
{ int i , j ;
  signal(SIGUSR1,func);
  while (i=fork( )== -1) ;
  if (i == 0)
{ sleep(5);
      signal(SIGUSR1,func);
printf("This is the first child\n");
  sleep(5);
  exit(0);
}
   while ( j = fork( ) == -1 ) ;
   if ( j ==0)
	{ sleep(3);
printf("This is the second child\n");
kill(i , SIGUSR1);
sleep(3);
exit(0);
	}
   printf("This is the parent\n");
	kill(j , SIGUSR1);
wait( );
kill( i , SIGUSR1);
wait( );
exit(0);
}
