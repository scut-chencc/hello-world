#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
void show_permit( mode_t filemode,char* res);
void time_make( char* ptime);
int main( int argc,char* argv[ ])
{
	 if( argc!=2)
	 {
		  printf( " error args\n" );
		  exit( -1);
	 }
	 DIR* dp;
	 dp=opendir( argv[ 1]);
	 if( NULL==dp)
	 {
		  perror( " opendir" );
		  exit( -1);
	 }
	 struct dirent* dir_info;
	 char buf[ 128];
	 int ret;
	 struct stat file_stat;
	 char* ptime;
	 while( ( dir_info=readdir( dp))!=NULL)
	 {
		  memset( buf,0,sizeof( buf));
		  ret=sprintf( buf," %s/%s" ,argv[ 1],dir_name);
		  if( ret<0)
		  {
			   perror( " sprintf" );
			   exit( -1);
		  }
		  ret=stat( buf,&file_stat);
		  if( ret<0)
		  {
			   perror( " stat" );
			   exit( -1);
		  }
		  char per[ 11];

	 }
	show_permit( file_stat.st_mode,per);
}
void show_permit( mode_t filemode,char* res)
{
	 char buf[ 11];
	 memset( buf,0,sizeof( buf));
	 if( S_ISREG( filemode))
	 {
		  buf[ 0]='-';
	 }else if( S_ISDIR( filemode))
	 {  
		buf[ 0]='d';
	 }
}
