#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main( )
{
	 printf( "i have started\n" );
	 printf( "i will exit" );//如果加就\n可以正常打印；
	 _exit( 0);
}
