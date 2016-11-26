#include <stdio.h>
#include <stdlib.h>

int main( int argc,char* argv[ ])
{
	 if( argc!=3)
	 {
		  printf( "error args!\n" );
		  exit(-1);
	 }
	 return atoi( argv[ 1])+atoi( argv[ 2]);
}
