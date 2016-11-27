#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( )
{

	pid_t pgid,pid1,pid2;
	printf( "mypid is %d\n" ,getpid( ));
	pgid=getpgid( 0);//获取当前进程的组ID;
	printf( "mysid is %d\n" ,getsid( 0));
	printf( "the pgid is %d\n" ,pgid);


	pid1=fork();
	int status;
	int ret;
	if( 0==pid1)
	{
		printf( "i am child1,i have start,mypid is %d,mypgid is %d,mysid is%d\n",getpid( ),getpgid( 0),getsid( 0));
		sleep(10);
		exit(1);
	}else{
		if(!( pid2=fork()))
		{
			printf( "i am child2,i have start,mypid is %d,mypgid is %d,mysid is %d\n",getpid( ),getpgid( 0),getsid( 0));
			sleep(5);
			exit(2);
		}else{
			printf( "i am father,i have start,mypid is %d,mysid is %d\n",getpid(),getsid( 0));
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
