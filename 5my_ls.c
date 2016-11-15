#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
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
		  ret=sprintf( buf,"%s/%s" ,argv[ 1],dir_info->d_name);
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
	show_permit( file_stat.st_mode,per);
	ptime=ctime( &file_stat.st_mtime);
	time_make( ptime);
	printf( " %10s %d %5s %5s %ld %s %s\n" ,per,file_stat.st_nlink,(getpwuid( file_stat.st_uid))->pw_name,( getgrgid( file_stat.st_gid))->gr_name,file_stat.st_size,ptime+4,dir_info->d_name) ;
}
return 0;
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
	 else if( S_ISLNK( filemode))
	 {
		  buf[ 0]='-';
	 }
	 if( filemode & S_IRUSR)
	 {
		  buf[ 1]='r';
	 }else{
		  buf[ 1]='-';
	 }
	 
	 if( filemode & S_IWUSR)
	 {
		  buf[ 2]='w';
	 }else{
		  buf[ 2]='-';
	 }
	 if( filemode & S_IXUSR)
	 {
		  buf[ 3]='x';
	 }else{
		  buf[ 3]='-';
	 }
	 if( filemode & S_IRGRP)
	 {
		  buf[ 4]='r';
	 }else{
		  buf[ 4]='-';
	 }
	 if( filemode & S_IWGRP)
	 {
		  buf[ 5]='w';
	 }else{
		  buf[ 5]='-';
	 }
	 if( filemode & S_IXGRP)
	 {
		  buf[ 6]='x';
	 }else{
		  buf[ 6]='-';
	 }
	 if( filemode & S_IROTH)
	 {
		  buf[ 7]='r';
	 }else{
		  buf[ 7]='-';
	 }
	 if( filemode & S_IWOTH)
	 {
		  buf[ 8]='w';
	 }else{
		  buf[ 8]='-';
	 }
	 if( filemode & S_IXOTH)
	 {
		  buf[ 9]='x';
	 }else{
		  buf[ 9]='-';
	 }
	 memcpy( res,buf,11);
}
void time_make( char* ptime)
{
	 char* p;
	 p=ptime+strlen( ptime)-1;
	 while( ( *p)!=':')
	 {
		  p--;
	 }
	 *p='\0';
}
