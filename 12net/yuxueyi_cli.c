#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <signal.h>
#include <sys/time.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>

#define ERR_EXIT(m) \
	do\
	{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while (0);

void echo_cli(int sock)
{
	char sendbuf[1024]={0};
	char recvbuf[1024]={0};
	
	while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL)
	{
		write(sock,sendbuf,strlen(sendbuf));
		read(sock,recvbuf,sizeof(recvbuf));
		fputs(recvbuf,stdout);
		memset(sendbuf,0,sizeof(sendbuf)); 
		memset(recvbuf,0,sizeof(recvbuf));
	}
}
		
int main()
{
	int sock;
	if((sock=socket(PF_UNIX,SOCK_STREAM,0))<0)
		ERR_EXIT("socket");
	struct sockaddr_un servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sun_family=AF_UNIX;
	strcpy(servaddr.sun_path,"/tmp/test_socket");
	if(connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
		ERR_EXIT("connect");
	echo_cli(sock);
	return 0;
}
	