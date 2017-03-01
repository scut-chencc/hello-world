#include <stdio.h>
#include <stdlib.h>

int main( int argc,char* argv[ ])
{
	 if( argc!=4)
	 {
		  printf( "error args!\n" );
		  exit(-1);
	 }
	 return atoi( argv[ 1])+atoi( argv[ 2]);
}
