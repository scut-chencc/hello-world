#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM 2
int tickets=10;
pthread_mutex_t mutex;
pthread_cond_t cond;
void* s_func( void* p)
{
	 long i=(long)p;
	 while( 1)
	 {
		  pthread_mutex_lock( &mutex);
		  if(tickets>0)
		  {
			   printf("i am windows %ld,tickets is %d\n" ,i,tickets);
			   tickets--;
			   if( tickets==0)
			   {
				    pthread_cond_signal( &cond);
			   }
			   printf("i am windows %ld,sale a ticket,tickets is %d\n" ,i,tickets);
		  }else{
			   pthread_mutex_unlock(&mutex);
			   pthread_exit( NULL);//or break;
		  }
		  pthread_mutex_unlock(&mutex);
		  //sleep( 1);
	 }
}
void* set_func( void* p)
{
	//while( 1)//可以用cancel取消，不过注意wait退出解锁，不然后面卖票操作不了；
	//{
		pthread_mutex_lock(&mutex);
	 	if( tickets>0)
	 	{
	 	     pthread_cond_wait(&cond,&mutex);
	 	}
	 	tickets=10;
	 	pthread_mutex_unlock( &mutex);
	//} 
	 sleep( 1);
	 pthread_exit( NULL);
}
int main( )
{
	 pthread_mutex_init( &mutex,NULL);
	 pthread_cond_init( &cond,NULL);
	 pthread_t sale[NUM],setticket;
	 long i;
	 for(i=0;i<NUM;i++)
	 {
		pthread_create(&sale[i],NULL,s_func,( void*)i);
	 }
	 pthread_create( &setticket,NULL,set_func,NULL);
	 for(i=0;i<NUM;i++)
	 {
		pthread_join(sale[i],NULL);
	 }
	pthread_join( setticket,NULL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy( &cond);
	return 0;
}
