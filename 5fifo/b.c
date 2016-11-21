#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
int main( int argc,char* argv[ ])
{
	 if( argc!=2)
	 {
		  printf( " error args\n" );
		  return -1;
	 }
	 int fdw;
	 fdw=open( argv[ 1],O_WRONLY);
	 if( -1==fdw)
	 {
		  perror( " open" );
		  return -1;
	 }
	 printf( " the fdw is %d\n" ,fdw);
	 char buf[ 128];
	 int ret;
	 while(bzero( buf,sizeof( buf)),(ret=read(STDIN_FILENO,buf,sizeof( buf) ))>0){
		 // write( fdw,buf,ret-1);//这样不用打印换行符
		 write( fdw,buf,ret);//打印了最后的换行符
	 }
	 return 0;
}
