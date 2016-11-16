#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
typedef struct student
{
	 int num;
	 char name[ 16];
}std_t;
int main( int argc,char* argv[ ])
{
	 if( argc!=2)
	 {
		  printf( " error args!\n" );
		  exit( -1);
	 }
	 int fd;
	 //fd=open( argv[ 1],O_RDWR|O_APPEND);
	 //fd=open( argv[ 1],O_RDWR|O_CREAT,0666);
	 fd=open( argv[ 1],O_RDWR|O_TRUNC,0666);
	 if( -1==fd)
	 {
		  perror(" open"  );
		  exit( -1);
	 }
	 printf( " open success ,fd is %d\n" ,fd);
	 int ret;
	 std_t std[ 2];
	 memset( std,0,sizeof( std));
	 //write
	 std[0].num=9001;
	 strcpy( std[0].name,"zhangsan") ;
	 std[1].num=9002;
	 strcpy( std[1].name,"lisi");
	 ret=write( fd,&std[0],40);
	 if( -1==ret)
	 {
	      perror( " write" );
	      exit( -1);
	 }
	 //lseek to head of file for read
	 ret=lseek( fd,0,SEEK_SET);
	 if( -1==ret)
	 {
		  perror( " seek" );
		  exit( -1);
	 }
	 //read
	 memset( std,0,sizeof( std));
	 ret=read( fd,&std[ 0],40);
	 if( -1==ret)
	 {
		  perror( " read" );
		  exit( -1);
	 }
	 int i;
	 for(i=0;i<2;i++)
	 {
		  printf( " the num is %d,the name is %s\n" ,std[ i].num,std[ i].name);
	 }
	 ret=close( fd);
	 if( -1==ret)
	 {
		  perror( " close" );
		  exit( -1);
	 }
	 printf( " close success!\n" );
	 return 0;
}
