#include <sys/types.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>

int main( ){
	 int sem_id;
	 sem_id=semget(( key_t)1234,1,0600|IPC_CREAT);
	 if( -1==sem_id)
	 {
		  perror( "semget" );
		  exit( -1);
	 }
	 int val=2;
	 int ret=semctl( sem_id,0,SETVAL,val);
	 if( -1==ret)
	 {
		  perror( "semctl1" );
		  exit( -1);
	 }
	 unsigned short array[ 1]={0};
	 ret=semctl( sem_id,0,GETVAL,&array[ 0]);
	 if( -1==ret)
	 {
		  perror( "semctl2" );
		  exit( -1);
	 }
	 printf( "the sem[ 0] value is %u\n" ,ret);
     ret=semctl( sem_id,0,IPC_RMID);
	 if( -1==ret)
     {
		  perror( "semctl3" );
		  exit( -1);
	 }
	 return 0;

}
