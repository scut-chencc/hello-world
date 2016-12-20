#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>

void handle( int signum)
{
	 printf( "I received the %d signal\n" ,signum);
	 exit( 0);
}

int main( )
{
	 signal(SIGINT,handle);
	 kill(0,SIGINT);
	 printf("I should not be here\n" );
	 return 0;
}
