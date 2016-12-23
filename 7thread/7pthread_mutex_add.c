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
	 for(i=0;i<NUM;i++)
	 {
		 pthread_mutex_lock(&mutex);
		  sum++;
		  pthread_mutex_unlock( &mutex);
	 }
	 printf("child the sum is %d\n" ,sum);
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
	 for(i=0;i<NUM;i++)
	 {
		  pthread_mutex_lock(&mutex);
		  sum++;
		  pthread_mutex_unlock(&mutex);
	 }
	 printf("father the sum is %d\n" ,sum);
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
