#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <signal.h>

void handle(int signum)
{
	time_t timep;
	time( &timep);
	printf("now,the time is %d:%d:%d\n" ,gmtime(&timep)->tm_hour,gmtime( &timep)->tm_min,gmtime(&timep)->tm_sec) ;
}
int main( )
{
	signal( SIGPROF,handle);
	struct itimerval timespec;
	timespec.it_value.tv_sec=1;
	timespec.it_value.tv_usec=0;
	timespec.it_interval.tv_sec=0;
	timespec.it_interval.tv_usec=0;
	int ret=setitimer(ITIMER_PROF,&timespec,NULL);
	if( -1==ret)
	{
		 perror( "setitimer" );
		 exit( -1);
	}
	sleep(5);//会被alarm打断；
	printf( "i have sleep\n" );
	sleep( 5);
	while( 1);
	return 0;
}
