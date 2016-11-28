#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

void Deamon( )
{
	 if( fork( )!=0)
	 {
		  exit( 0);
	 }
	 setsid( );
	 chdir("/" );
	 umask( 0);
	 int i=0;
	 for( ;i<3;i++)
	 {
		  close( i);
	 }
}
int main( )
{
	 Deamon( );
	 while( 1)
	 {
		  sleep( 1);
	 }
	 return 0;
}
