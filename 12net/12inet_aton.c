#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

int main(int argc,char* argv[] )
{
	 if( 2!=argc)
	 {
		  printf(" error args\n" );
		  return -1;
	 }
	 struct in_addr addr;
	 int ret;
	 ret=inet_aton(argv[ 1],&addr);//将点分十进制转换为网络二进制；
	 if( 1!=ret)
	 {
		  perror("inet_aton" );
		  return -1;
	 }
	 printf("the s_addr is %x\n" ,addr.s_addr);
	 printf("string is %s\n" ,inet_ntoa(addr));
	 printf("the s_addr2 is %x\n" ,inet_addr( argv[1]));
	 return 0;
}
