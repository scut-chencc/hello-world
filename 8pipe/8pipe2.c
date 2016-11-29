#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main( )
{
	 int fd_wr[2];//父进程写；
	 int fd_rw[2];
	 pipe(fd_wr);
	 pipe( fd_rw);
	 if( !fork())
	 {
		  close(fd_wr[1]);
		  close( fd_rw[ 0]);
		  write( fd_rw[ 1],"i am child,i am fine" ,21);
		  char buf[ 32];
		  memset( buf,0,sizeof( buf));
		  read( fd_wr[ 0],buf,sizeof( buf));
		  printf("i am child:receive:%s\n" , buf);
		  close( fd_wr[ 0]);
		  close( fd_rw[ 1]);
		  exit( 0);
	 }else{
		  close( fd_wr[0]);
		  close( fd_rw[ 1]);
		  write(fd_wr[ 1],"hello,how are you" ,18);//还有结束符；
		  char buf[ 32];
		  memset ( buf,0,sizeof( buf));
		  read( fd_rw[ 0],buf,sizeof( buf));
		  printf( "i am parent:receive %s\n" ,buf); 
		  wait( NULL);
		  close( fd_wr[1]);
		  close( fd_rw[ 0]);
		  return 0;
	 }
}
