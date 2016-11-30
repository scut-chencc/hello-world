#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct shm_data
{
	 int val;
	 int show;//0没有读取；1已经读取；
	 int lock;//1有人正在操作；0没有正在操作；
}shm_dt,*pshm;

void lock( int*);
void unlock( int*);

int main( )
{
	 int shm_id;
	 shm_id =shmget( ( key_t)1234,4096,0600|IPC_CREAT);
	 if( -1==shm_id)
	 {
		  perror( "shmget" );
		  exit( -1);
	 }
	 void* shmp;
	 shmp=shmat( shm_id,NULL,0);
	 if( shmp==(void*) -1)
	 {
		  perror( "shmat" );
		  exit( -1);
	 }
	 pshm pdata;
	 pdata=( pshm)shmp;
	 int i=0;
	 while( i<10){
		lock( &pdata->lock);
		printf( "r:the val is %d\n" ,pdata->val);
		pdata->val=0;
		pdata->show=1;
		printf( "i have read the val %d\n" ,i);
		unlock(&pdata->lock );
		sleep( 1);
		i++;
	 } 
	 int ret=shmdt( shmp);
	 if( -1==ret)
	 {
		  perror( "shmdt" );
		  exit( -1);
	 }
	 return 0;
}

void lock(int* l)
{
	 while( *l==1)
	 {
		  sleep( 1);
	 }
	 *l=1;
}
void unlock(int* l)
{
	 *l=0;
}
