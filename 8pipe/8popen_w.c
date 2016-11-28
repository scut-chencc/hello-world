#include <stdio.h>
#include <string.h>

int main( )
{
	 FILE* fp=popen("./8add" ,"w");
	 char buf[ 128];
	 memset( buf,0,sizeof( buf));
     buf[ 0]='1';
	 buf[ 1]=' ';
	 buf[ 2]='2';
	 buf[ 3]='\n';
	 fwrite( buf,sizeof( char),4,fp);
	 fclose( fp);
	 return 0;
}
