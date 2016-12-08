#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main( ){
	 int sem_id;
	 sem_id=semget(( key_t)1234,2,0600|IPC_CREAT);
	 if( -1==sem_id)
	 {
		  perror( "semget" );
		  exit( -1);
	 }
	 //int val=2;
	 //int ret=semctl( sem_id,0,SETVAL,val);
	 unsigned short array[ 2]={2,2};
	 int ret=semctl( sem_id,0,SETALL,array);
	 if( -1==ret)
	 {
		  perror( "semctl1" );
		  printf( "the errno id %d\n" ,errno);
		  exit( -1);
	 }
	 struct sembuf sem2[ 2];
	 sem2[ 0].sem_num=0;
	 sem2[ 0].sem_op=-1;
	 sem2[ 0].sem_flg=SEM_UNDO;
	 sem2[ 1].sem_num=1;
	 sem2[ 1].sem_op=1;
	 sem2[ 1].sem_flg=SEM_UNDO;
	 ret=semop( sem_id,sem2,2) ;
	 if( -1==ret)
	 {
		  perror( "semop" );
		  exit( -1);
	 }
	 unsigned short array_out[ 2];
	 ret=semctl( sem_id,0,GETALL,array_out);
	 if( -1==ret)
	 {
		  perror( "semctl2" );
		  exit( -1);
	 }
	 printf( "the sem[ 0] value is %d\n" ,array_out[ 0]);
	 printf( "the sem[ 1] value is %d\n" ,array_out[ 1]);
     ret=semctl( sem_id,0,IPC_RMID);
	 if( -1==ret)
     {
		  perror( "semctl3" );
		  exit( -1);
	 }
	 return 0;

}
