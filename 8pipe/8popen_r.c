#include <stdio.h>
#include <string.h>
int main( )
{
	 FILE* fp=popen( "ls -l" ,"r" );
	 char buf[ 128];
	 while( memset( buf,0,sizeof( buf)),fgets(buf,sizeof( buf) ,fp))
	 {
		 buf[ strlen( buf)-1]='\0';
		  puts(buf );
	 }
	 pclose( fp);
	 return 0;
}
