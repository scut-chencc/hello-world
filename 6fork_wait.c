#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( )
{
	 pid_t pid;
	 pid=fork();
	 int status;
	 if( 0==pid)
	 {
		 printf( "i am child,i have start\n");
		  sleep(10);
		  exit( 3);
	 }else{
		 printf( "i am father,i have start\n");
		pid=wait( &status);
		printf( "the wait pid is %d,the exit status is %x\n",pid,status);
		sleep( 10);
		exit( 0);
	 }
}
