#include <stdio.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main( int argc,char* argv[ ])
{
	 if( argc!=2)
	 {
		  printf( "error args\n" );
		  return -1;
	 }
	 int fd;
	 fd=open( argv[ 1],O_RDWR);
	 if( -1==fd)
	 {
		  perror( "open" );
		  return -1;
	 }
	 char* p;//文件映射入内存的起始位置；
	 p=mmap( NULL,10,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	 if( ( void*)p==( void*)-1)
	 {
		  perror( "mmap" );
		  return -1;
	 }
	 *p='h'; 
	 int ret;
	 ret=munmap(p,10);
	 if( ret<0)
	 {
		  perror( "munmap" );
		  return -1;
	 }
	 close( fd);
	 return 0;
}
