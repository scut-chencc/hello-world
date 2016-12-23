#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* p=NULL;
void cleanmalloc(void* arg)
{
	 printf( "i am %d clean func\n" ,( int)arg);
	 free(p);
	 p=NULL;
}
void* thread( void* arg)
{
	pthread_cleanup_push( cleanmalloc,( void*)1);
	
	int* i;
	i=( int*)arg;
	 printf( "the arg is %d\n",*i );
	 //sleep(10);
	 //while( 1);
	 printf("the *p is %d\n" ,*((int*)p));
	 //pthread_cleanup_pop(0);//把函数弹出来但不执行；
	 pthread_cleanup_pop(0);
	 int exitval=4;
	 pthread_exit((void*)exitval);
}
int main( )
{
	 pthread_t pthid1;
	 pthread_t pthid2;
	 int i=3;
	 p=(int*)malloc(4);
	 *(int*)p=6;
	 int ret=pthread_create(&pthid1,NULL,thread,&i);
	 if( 0==ret)
	 {
		  printf("the thread %ld create success\n",pthid1);
	 }
	 int exitval=0;
	 ret=pthread_cancel(pthid1);//一般工作中用不到；
	 //cancel之后资源清理了，但是退出值不正常了；
	 if( ret!=0)
	 {
		  perror("pthread_cancel" );
		  exit( -1);
	 }
	 ret=pthread_join(pthid1,(void**)&exitval);
	 if(ret!=0)
	 {
		  perror("pthread_join");
		  exit(-1);
	 }
	 printf("the exitval is %d\n" ,exitval);
	 printf( "the p value is %x\n" ,p);
	 while(1);
	 return 0;
}
