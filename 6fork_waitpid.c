#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( )
{
	pid_t pid1,pid2;
	pid1=fork();
	int status;
	int ret;
	if( 0==pid1)
	{
		printf( "i am child1,i have start,mypid is %d\n",getpid( ));
		sleep(10);
		exit(1);
	}else{
		if(!( pid2=fork()))
		{
			printf( "i am child2,i have start,mypid is %d\n",getpid( ));
			sleep(5);
			exit(2);
		}else{
			printf( "i am father,i have start\n");
			ret=waitpid(pid1, &status,0);
			//ret=waitpid(pid1, &status,WNOHANG);
			printf( "the return of waitpid1 is %d,the exit status of child1 is %x\n",ret,status);
			ret=waitpid(pid2, &status,0);
			//ret=waitpid(pid2, &status,WNOHANG);
			printf( "the return of waitpid2 is %d,the exit status of child2 is %x\n",ret,status);
			sleep( 10);
			exit( 0);
		}
	} 
}
