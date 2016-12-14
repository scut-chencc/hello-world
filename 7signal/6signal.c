#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void handle( int sig)
{
	 printf( "the sig num is %d\n" ,sig);
	 sleep( 10);
	 printf( "the sig again is %d\n" ,sig);
}
int main( )
{
	 
	 signal( SIGINT,handle);//2
	 signal( SIGQUIT,handle);//3
	 sleep( 2);//当被打断后，就不能接着执行了；
	 return 0;
}
