#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main( )
{
	 sigset_t sset;
	 sigemptyset( &sset);
	 sigaddset( &sset,SIGINT);
	 //int ret=sigprocmask( SIG_BLOCK,&sset,NULL);
	 int ret=sigprocmask( SIG_SETMASK,&sset,NULL);
	 if( -1==ret)
	 {
		  perror( "sigprocmask" );
		  exit( -1);
	 }
	 printf( " I am here\n" );
	 sleep( 5);//在这当中发信号才被挂起，才会被检测到；
	 printf( "after sleep\n" );
	 sigset_t sset1;
	 sigemptyset( &sset1);
	 ret=sigpending(&sset1);
	 if( -1==ret)
	 {
		  perror( "sigpending" );
		  exit( -1);
	 }
	 ret=sigismember(&sset1,SIGINT);
	 if( 1==ret)
	 {
		  printf( "SIGINT is a member of sset1\n" );
	 }
	 //ret=sigprocmask( SIG_UNBLOCK,&sset,NULL);
	 //if( -1==ret)
	 //{
	 //     perror( "sigprocmask2" );
	 //     exit( -1);
	 //}
	 
	 while( 1);
	 return 0;
}
