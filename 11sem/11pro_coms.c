#include <sys/types.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int shm_id;
int *shmp;
int sem_id;
void init( );
int main( ){
	init( );
	if(!fork( ))
	{
		struct sembuf sem_pc[ 2];
		while( 1)
		{

			sem_pc[ 0].sem_num=0;
			sem_pc[ 0].sem_op=-1;
			sem_pc[ 0].sem_flg=SEM_UNDO;
			sem_pc[ 1].sem_num=1;
			sem_pc[ 1].sem_op=1;
			sem_pc[ 1].sem_flg=SEM_UNDO;
			int ret=semop( sem_id,sem_pc,1) ;
			if( -1==ret)
			{
				perror( "semop" );
				exit( -1);
			}

			( *shmp)--;
			printf( "--------------I am customer,my pro num is %d\n" ,*shmp);
			ret=semop( sem_id,&sem_pc[ 1],1);
			if( -1==ret)
			{
				perror( "semop" );
			}
			sleep( 2) ;

		}
	}
	else{
		 
		struct sembuf sem_pc[ 2];
		while( 1)
		{

			sem_pc[ 0].sem_num=0;
			sem_pc[ 0].sem_op=1;
			sem_pc[ 0].sem_flg=SEM_UNDO;
			sem_pc[ 1].sem_num=1;
			sem_pc[ 1].sem_op=-1;
			sem_pc[ 1].sem_flg=SEM_UNDO;
			int ret=semop( sem_id,sem_pc,1) ;
			if( -1==ret)
			{
				perror( "semop" );
				exit( -1);
			}

			( *shmp)++;
			printf( "--------------I am product,my pro num is %d\n" ,*shmp);
			ret=semop( sem_id,&sem_pc[ 1],1);
			if( -1==ret)
			{
				perror( "semop" );
			}
			sleep( 1) ;

		}
	}
    return 0;
}

void init( )
{
	shm_id=shmget( ( key_t)1234,20,0600|IPC_CREAT);
	if( -1==shm_id)
	{
		perror( "shmget" );
		exit( -1);
	}
	shmp=( int*)shmat( shm_id,NULL,0);
	if( ( int*)-1==shmp)
	{
		perror( "shmat" ) ;
		exit( -1);
	}
	*shmp=0;
	sem_id=semget( ( key_t)1234,2,0600|IPC_CREAT);
	if( -1==sem_id)
	{
		perror( "semget" );
		exit( -1);
	}
	unsigned short array[ 2];
	array[ 0]=0;
	array[ 1] =10;
	int ret=semctl( sem_id,0,SETALL,array);
	if( -1==ret)
	{
		perror( "semctl1" );
		exit( -1);
	}
}
