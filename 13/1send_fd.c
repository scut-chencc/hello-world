#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( )
{
	 int pfd[2];
	 pipe(pfd) ;
	 if( !fork( ))
	 {
		  int fd;
		  close( pfd[ 1]);
		  int ret=read(pfd[ 0],&fd,4);
		  if( -1==ret)
		  {
			   perror( "read" );
			   exit( -1);
		  }
		  printf( " i am child,the fd is %d\n" ,fd);
		  char buf[ 10]={0};
		  ret=read(fd,buf,sizeof( buf));
		  if( -1==ret)
		  {
			   perror( "readfd" );
			   exit( -1);
		  }
		  printf(" buf is %s\n" ,buf);
		  exit( 0);
	 }else{
		  int ret;
		  close( pfd[ 0]);
		  int fd=open("test" ,O_RDWR);
		  if( -1==fd)
		  {
			   perror( "open" );
			   exit( -1);
		  }
		  printf(" the fd is %d\n" ,fd);
		  write( pfd[ 1],&fd,4);
		  char buf[ 10]={0};
		  ret=read(fd,buf,sizeof( buf));
		  if( -1==ret)
		  {
			   perror( "read2" );
			   exit( -1);
		  }
		  printf("parent buf is %s\n" ,buf);
		  wait(NULL);
		  return 0;
	 }
}
