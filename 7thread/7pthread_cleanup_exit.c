#include <stdio.h>
#include <pthread.h>

void cleanup(void* p)
{
	 printf("the p is %d\n" ,( int)p);
}
void* pthread_func(void* p)
{
	 pthread_cleanup_push(cleanup,( void*)1);
	 pthread_cleanup_push(cleanup,( void*)2);
	 sleep(5);
	 pthread_exit( NULL);//就在这里退出了，下面只是为了成对出现，和0或1没关系；
	 pthread_cleanup_pop( 0);//如果为0,执行到该位置，就是弹出函数不执行清理函数；
	 pthread_cleanup_pop( 0);
}
int main( )
{
	pthread_t pthid;
	 pthread_create(&pthid,NULL,pthread_func,NULL );
	 int ret=pthread_join(pthid,NULL);//等待子线程退出；
	 if( 0!=ret)
	 {
		  printf("ret is %d\n" ,ret);
		  return -1;
	 }
	 return 0;
}
