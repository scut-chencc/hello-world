#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
int main( int argc,char* argv[ ])
{
	 printf( "the O_RDONLY is %x\n" ,O_RDONLY); 
	 printf( "the O_WRONLY is %x\n" ,O_WRONLY); 
	 printf( "the O_NONBLOCK is %x\n" ,O_NONBLOCK); 
	 int fds_status=fcntl(STDIN_FILENO,F_GETFL);
	 fds_status=fds_status | O_NONBLOCK;
	 printf("the STDIN_FILENO status is %x\n" ,fds_status);
	 int ret=fcntl(STDIN_FILENO,F_SETFL,fds_status);
	 printf("the fcntl return  value is %x\n" ,ret) ;
	 char buf[ 512]={0};
	 ret=read( STDIN_FILENO,buf,512);
	 printf( " i have read %d bytes\n" ,ret);
	 printf( " errno is %d \n" ,errno);
	 return 0;
}
