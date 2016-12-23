#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#define NUM 10000000
pthread_mutex_t mutex;
int sum=0;

void* p_func(void* p)
{
	 int i;
	 pthread_mutex_lock(&mutex);
	 pthread_mutex_lock(&mutex);
	 printf("i am child,i have lock\n" );
	 pthread_mutex_unlock(&mutex);
	 pthread_mutex_unlock(&mutex);
	 pthread_exit(NULL);
}
int main( )
{
	 int ret;
	 pthread_mutexattr_t attr;
	 int i;
	 i=PTHREAD_MUTEX_RECURSIVE_NP;
	 memcpy(&attr,&i,4);
	 //attr.__mutexkind=PTHREAD_MUTEX_RECURSIVE_NP;

	 //ret=pthread_mutex_init(&mutex,NULL);
	 ret=pthread_mutex_init(&mutex,&attr);
     if( 0!=ret)
	 {
		  printf("pthread_mutex_init ret is %d\n" ,ret);
		  return -1;
	 }

	 pthread_t pthid;
	 pthread_create(&pthid,NULL,p_func,NULL);
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
