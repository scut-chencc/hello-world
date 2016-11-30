#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

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
	 //int ret=shmctl(shm_id,IPC_RMID,NULL);
	 struct shmid_ds shm_ds_info;
	 int ret=shmctl( shm_id,IPC_STAT,&shm_ds_info);
	 if( -1==ret)
	 {
		  perror( "shmctl" );
		  exit( -1);
	 }
	 printf( "mypid is %d\n" ,getpid( ));
	 printf( "the shm_perm.key is %x\n" ,shm_ds_info.shm_perm.__key);
	 printf( "the shm_perm.uid is %d\n" ,shm_ds_info.shm_perm.uid);
	 printf( "the shm_perm.gid is %d\n" ,shm_ds_info.shm_perm.gid);
	 printf( "the shm_perm.cuid is %d\n" ,shm_ds_info.shm_perm.cuid);
	 printf( "the shm_perm.cgid is %d\n" ,shm_ds_info.shm_perm.cgid);
	 printf( "the shm_perm.mode is %x\n" ,shm_ds_info.shm_perm.mode);
	 printf( "the shm_perm.__seq is %u\n" ,shm_ds_info.shm_perm.__seq);
	 printf( "the size is %d\n" ,shm_ds_info.shm_segsz);
	 printf( "the la_time is %s\n" ,ctime(&shm_ds_info.shm_atime) ) ;
	 printf( "the ld_time is %s\n" ,ctime(&shm_ds_info.shm_dtime) ) ;
	 printf( "the lc_time is %s\n" ,ctime(&shm_ds_info.shm_ctime) ) ;
	 printf( "the create pid is %d\n" ,shm_ds_info.shm_cpid);
	 printf( "the last pid is %d\n" ,shm_ds_info.shm_lpid);
	 printf( "the attach num is %ld\n" ,shm_ds_info.shm_nattch);
	 
	 shmdt( shmp);
	 return 0;
}
