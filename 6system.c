#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main( )
{
	 printf( "mypid is %d\n" ,getpid());
	 int ret;
	 ret=system( "./add 1 2" );
	 printf( "ret is %d\n" ,ret>>8);
	 return 0;
}
