#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main( int argc,char* argv[ ])
{
	 if( argc!=2)
	 {
		  printf( "error args\n" );
		  exit( -1);
	 }
	 int ret=mkfifo( argv[ 1],0666);
	 if( -1==ret)
	 {
		  perror( "mkfifo" );
		  exit( -1);
	 }
	 return 0;
}
