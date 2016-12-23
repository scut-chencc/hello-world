#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#define NUM 2
pthread_cond_t cond;
pthread_mutex_t mutex;

void* p_func(void* p)
{
	 pthread_mutex_lock(&mutex);
	 int ret;
	 int i=( int)p;
	 printf(" i am child %d,this is wait entrance\n",i );
	 ret=pthread_cond_wait(&cond,&mutex);
	 if(0!=ret)
	 {
		  printf("pthread_cond_wait ret is %d\n" ,ret);
	 }
	 printf(" i am child thread %d,i am wake\n",i);
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
	 pthread_t thid[NUM];
	 int i;
	 for(i=0;i<NUM;i++)
	 {
		pthread_create( &thid[i],NULL,p_func,( void*)i);
	 }
	 sleep( 1);
	 pthread_cond_broadcast(&cond);
	// pthread_mutex_lock(&mutex);//验证子线程wait后，解锁，睡觉；
	// printf("i am father thread,i can lock\n" );
	// pthread_mutex_unlock( &mutex);
	 //pthread_cond_signal( &cond);//除非条件变量没有初始化，不然一般不会失败
	 for(i=0;i<NUM;i++)
	 {
		ret=pthread_join(thid[i],NULL);
		if( 0!=ret)
	 	{
	 	     printf("pthread_join ret is %d\n" ,ret);
	 	     return -1;
	 	}
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
