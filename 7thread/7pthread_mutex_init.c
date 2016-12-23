#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int main( )
{
	 int ret;
	 pthread_mutex_t mutex;
	 ret=pthread_mutex_init(&mutex,NULL);
     if( 0!=ret)
	 {
		  printf("pthread_mutex_init ret is %d\n" ,ret);
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
