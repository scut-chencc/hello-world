#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#define NUM 10000000
pthread_mutex_t mutex;
int sum=0;

void* p_func(void* p)
{
	 int i;
	 pthread_mutex_lock(&mutex);
	 printf("i am child,i have lock\n" );
	 while( 1);
	 pthread_mutex_unlock(&mutex);
	 pthread_exit(NULL);
}
int main( )
{
	 int ret;
	 ret=pthread_mutex_init(&mutex,NULL);
     if( 0!=ret)
	 {
		  printf("pthread_mutex_init ret is %d\n" ,ret);
		  return -1;
	 }

	 pthread_t pthid;
	 pthread_create(&pthid,NULL,p_func,NULL);
	 int i;
	 sleep( 1);
	 ret=pthread_mutex_trylock(&mutex);
	 printf("pthread_mutex_trylock return ret is %d\n" ,ret) ;//EBESY IS 16;
	 ret=pthread_join(pthid, NULL);
	 if( 0!=ret)
	 {
		  printf("pthread_join ret is %d\n" ,ret);
		  return -1;
	 }
	 ret=pthread_mutex_destroy(&mutex);
	 if( 0!=ret)
	 {
		  printf("pthread_mutex_destroy ret is %d\n" ,ret);
		  return -1;
	 }
	 return 0;
}
