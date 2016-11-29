#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main( )
{
	 int fd[2];
	 int ret;
	 ret=pipe(fd);
	 if(-1==ret )
	 {
		  perror("pipe");
		  exit( -1);
	 }
	 if( !fork())
	 {
		  close(fd[1]);
		  char buf[ 32];
		  memset( buf,0,sizeof( buf));
		  read( fd[ 0],buf,sizeof( buf));
		  puts( buf);//puts本身结尾输出换行符；
		  close( fd[ 0]);
		  exit( 0);
	 }else{
		  //close( fd[0]);
		  write(fd[ 1],"hello" ,6);//还有结束符；
		  char buf[ 32];
		  memset ( buf,0,sizeof( buf));
		  read( fd[ 0],buf,sizeof( buf));
		  printf( "parent puts %s\n" ,buf); 
		  wait( NULL);
		  close( fd[1]);
		  return 0;
	 }
}
