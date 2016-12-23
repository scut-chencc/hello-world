#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void cleanup(void* p)
{
	free( p);
	p=NULL;
	printf("the memory is free\n" );
}
void* pthread_func(void* p1)
{
	 char* p=( char*)malloc(10);
	 pthread_cleanup_push(cleanup,p);
	 sleep(10);
	 pthread_exit( NULL);//就在这里退出了，下面只是为了成对出现，和0或1没关系；
	 pthread_cleanup_pop( 0);//如果为0,执行到该位置，就是弹出函数不执行清理函数；
}
int main( )
{
	pthread_t pthid;
	 pthread_create(&pthid,NULL,pthread_func,NULL );
	 int ret;
	 //ret=pthread_cancel(pthid);//cancle要在join之前，否则就没意义；看不出睡眠的效果；
	 //if( 0!=ret)
	 //{
	 //     printf("pthread_cancle ret is %d\n",ret );
	 //     return -1;
	 //}
	 ret=pthread_join(pthid,NULL);//等待子线程退出；
	 if( 0!=ret)
	 {
		  printf("pthread_join ret is %d\n" ,ret);
		  return -1;
	 }
	 return 0;
}
