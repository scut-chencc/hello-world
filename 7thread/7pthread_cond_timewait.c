#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <strings.h>
#include <sys/time.h>
pthread_cond_t cond;
pthread_mutex_t mutex;

void* p_func(void* p)
{
	 struct timespec ts;
	 struct timeval now;
	 bzero(&ts,sizeof( ts));
	 int ret;
	 gettimeofday(&now,NULL);
	 ts.tv_sec=now.tv_sec+5;
	 pthread_mutex_lock(&mutex);
	 printf(" i am child ,this is wait entrance\n" );
	 ret=pthread_cond_timedwait(&cond,&mutex,&ts);//超时等待，ret是110;
	 if(0!=ret)
	 {
		  printf("pthread_cond_timewait ret is %d\n" ,ret);
	 }
	 printf(" i am child thread,i am wake\n" );
	 pthread_mutex_unlock(&mutex);
	 pthread_exit( NULL);
}
int main( )
{
	 int ret;
	 ret=pthread_cond_init(&cond,NULL);
	 if( 0!=ret)
	 {
		  printf("pthread_cond_init ret is %d\n" ,ret);
		  return -1;
	 }
	 ret=pthread_mutex_init(&mutex,NULL);
	 if( 0!=ret)
	 {
		  printf("pthread_mutex_init ret is %d\n" ,ret);
		  return -1;
	 }
	 pthread_t thid;
	 pthread_create( &thid,NULL,p_func,NULL);
	 sleep( 1);
	 //pthread_cond_signal( &cond);//除非条件变量没有初始化，不然一般不会失败
	 ret=pthread_join(thid,NULL);
	 if( 0!=ret)
	 {
		  printf("pthread_join ret is %d\n" ,ret);
		  return -1;
	 }
	 ret=pthread_cond_destroy(&cond);
	 if( 0!=ret)
	 {
		  printf("pthread_cond_destroy ret is %d\n" ,ret);
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
