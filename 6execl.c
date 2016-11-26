#include <stdio.h>
#include <unistd.h>

int main()
{
	 execl( "./add" ,"add" ,"1" ,"2" ,NULL);
	 printf( "i am the main process\n" );//这句话被子进程覆盖，并没有执行；
	 return 0;
}
