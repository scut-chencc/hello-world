#include <sys/uio.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	 int fd=open("test" ,O_RDWR);
	 char buf1[10]="hello" ;
	 char buf2[ 10]="world" ;
	 struct iovec iov[ 2];
	 iov[ 0].iov_base=buf1;
	 iov[ 0] .iov_len=5;
	 iov[ 1].iov_base=buf2;
	 iov[ 1].iov_len=5;
	 int ret=writev(fd,iov,2);
	 if( -1==ret)
	 {
		  perror("writev" );
		  exit(-1) ;
	 } 
	 lseek(fd,0,SEEK_SET);
	 char bufr1[ 10]={0};
	 char bufr2[ 10]={0};
	 struct iovec iovr[2];

}
