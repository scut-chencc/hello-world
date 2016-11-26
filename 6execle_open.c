#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main( )
{
	 int fd;
	 char buf[ 128];
	 char* buf2;
	 buf2=getcwd( buf,128);
	 printf("getcwd is %s,the return of getcwd is %s\n" ,buf,buf2);
	 fd=open( "logfile" ,O_RDONLY|O_CREAT,0666);
	 if( fd<0)
	 {
		  perror("open" );
		  return -1;
	 }
	 return 0;
}
