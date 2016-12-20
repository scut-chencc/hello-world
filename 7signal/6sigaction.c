#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int sigtimes=0;
void sa_sigact( int signum,siginfo_t *siginfo,void* pReserved)
{
	sigtimes++;
	 printf( "I have received the sig %d,the times is %d\n" ,signum,sigtimes);
	 printf( "the send pid is %d\n" ,siginfo->si_pid);
	 printf( "the send pid is %d\n" ,siginfo->si_uid);
	 sleep( 3);
	 printf( "-----I have received the sig %d,after sleep,the times is %d\n" ,signum,sigtimes);
}
int main( )
{
	 struct sigaction act;
	 act.sa_sigaction=sa_sigact;
	 act.sa_flags=SA_SIGINFO|SA_RESTART;
	 int ret=sigaction( SIGQUIT,&act,NULL);
	 if( -1==ret)
	 {
		  perror( "sigaction" );
		  exit( -1);
	 }
	 ret=sigaction( SIGINT,&act,NULL);
	 if( -1==ret)
	 {
		  perror( "sigaction" );
		  exit( -1);
	 }
	 char buf[ 128];
	 ret=read(STDIN_FILENO,buf,sizeof( buf));
	 if( -1==ret)
	 {
		  perror( "read" );
		  exit( -1);
	 }
	 printf("the buf is %s\n" ,buf);
	 sleep(3);
	 return 0;
}
