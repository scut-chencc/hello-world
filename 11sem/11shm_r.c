#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/sem.h>

typedef struct shm_data
{
	 int val;
	 int show;//0：没人读取；1：已经读取；
	 int lock;//0：没人操作1：有人操作；
}shm_dt,*pshm;

int main( )
{
	 int shm_id;
	 shm_id=shmget( ( key_t)1234,4096,0600|IPC_CREAT);
	 if( -1==shm_id)
	 {
		  perror( "shmget" );
		  exit( -1);
	 }
	 void *shmp;
	 shmp=shmat( shm_id,NULL,0);
	 if(( char*)-1==( char*)shmp)
	 {
		  perror("shmat" );
		  exit( -1);
	 }
	 int sem_id=semget( ( key_t)1234,1,0600|IPC_CREAT);
	 if( -1==sem_id)
	 {
		  perror( "semget" );
		  exit( -1);
	 }
	 int ret=semctl( sem_id,0,SETVAL,1);//只设置一次就可以了；
	 if( -1==ret)
	 {
		  perror(" semctl" );
		  exit(-1);
	 }
	 struct sembuf sem1;
	 sem1.sem_num=0;
	 sem1.sem_op=-1;
	 sem1.sem_flg=SEM_UNDO;
	 struct sembuf sem2;
	 sem2.sem_num=0;
	 sem2.sem_op=1;
	 sem2.sem_flg=SEM_UNDO;
	  
	 pshm pdata;
	 pdata=( pshm)shmp;
	 int i=0;
	 for( ;i<10000000;i++)
	 {
		  semop( sem_id,&sem1,1);
		  pdata->val=pdata->val+1;
		  semop( sem_id,&sem2,1);
	 }
	 printf( "the val is %d\n" ,pdata->val);
	 ret=shmdt(shmp);
	 if( -1==ret)
	 {
		  perror( "shmdt" );
		  exit( -1);
	 }
	 ret=semctl( sem_id,0,IPC_RMID);//因为要在另一个操作完之后才能删除信号量；
	 if( -1==ret)
	 {
	      perror( "shm_r:semctl1" );
	      exit( -1);
	 }
	 return 0;
}
