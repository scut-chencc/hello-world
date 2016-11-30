#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdlib.h>

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
	 return 0;
}
