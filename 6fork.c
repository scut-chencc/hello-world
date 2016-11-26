#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc,char* argv[ ] )
{
	if( argc!=2)
	{
		 printf( "error args!\n" );
		 exit( 0);
	}
	int fd=open( argv[ 1],O_RDWR);
	 pid_t pid;
	 pid=fork( );
	if(pid==0)
	{ 
		printf( "this is child,pid is %d,fork return value is %d\n" ,getpid( ),pid);
		char buf[ 128];
		read( fd,buf,5);//子进程继承父进程打开的文件描述符；
		buf[ 5]='\0';
		printf( "the buf is %s\n" ,buf);
		exit(0);
	}else{
		printf( "this is parent,pid is %d,fork return value is %d\n" ,getpid(),pid);
	}
	return 0;
}
