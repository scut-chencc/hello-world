#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
int main()
{
	extern char** environ;
	//printf("the first string in environ is %s\n" ,environ[ 0]);
	char* p;
	p=getenv("PWD");
	char* head="/home/ccc/hello-world/temp" ;
	printf("the pwd is %s\n" ,head);
	int ret;
	ret=mkdir(head,0777);
	if( -1==ret)
	{
		 perror("mkdir");
		 exit( -1);
	}
	ret=setenv("PWD" ,head,1);
	if( -1==ret)
	{
		 perror( "setenv" );
		 exit( -1);
	}
	execle( "./6execle_open" ,"6execle_open",NULL,environ);
    //execle是把后面的程序放入代码段，覆盖而已，还是原来的进程，所以要改变执行路径还需自己设置；
	//printf("the pwd is %s\n" ,getenv( "PWD" ));
	//execl( "./add" ,"add" ,"1" ,"2" ,NULL);
	printf( "i am the main process\n" );//如果子进程创建成功，这句话被子进程覆盖，并没有执行；
	return 0;
}
