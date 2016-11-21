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
	 if( argc!=3)
	 {
		  printf( " error args\n" );
		  return -1;
	 }
	 int fdw;
	 fdw=open( argv[ 1],O_WRONLY);
	 if( -1==fdw)
	 {
		  perror( " open1" );
		  return -1;
	 }
	 int fdr;
	 fdr=open( argv[ 2],O_RDONLY);
	 if( -1==fdr)
	 {
		  perror( " open2" );
		  return -1;
	 }

	 printf( "fdw=%d,fdr=%d\n" ,fdw,fdr);
	 char buf[ 128];
	 int ret;
	 while(bzero( buf,sizeof( buf)),(ret=read(STDIN_FILENO,buf,sizeof( buf) ))>0){
		 // write( fdw,buf,ret-1);//这样不用打印换行符
		 write( fdw,buf,ret);//打印了最后的换行符
		 bzero( buf,sizeof( buf));
		if((ret=read(fdr,buf,sizeof( buf)) )>0)
		{
			 printf( "%s\n" ,buf);
			 if( !strcmp( buf,"bye"))
				 break;
		}
	 }
	 return 0;
}
