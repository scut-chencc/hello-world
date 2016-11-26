#include <stdio.h>
#include <unistd.h>
#include <errno.h>
 
int main()
{
	char* p[3]={"add" ,"1" ,"2"};//字符型指针数组；
	//char* p[4]={"add" ,"1" ,"2","NULL"};//字符型指针数组；
	 //execv( "./add" ,"add" ,"1" ,"2" ,NULL);
	int ret;
	ret=execv( "./add" ,p);
	if( -1==ret) 
	{
		 printf("errno is %d\n" ,errno );
	}
	printf( "i am the main process\n" );//这句话被子进程覆盖，并没有执行；
	 return 0;
}
