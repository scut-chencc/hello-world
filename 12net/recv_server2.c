#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>

#define ERR_EXIT(m) \
	do\
	{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while (0);
	
int main(void)
{
	int sock;
	if((sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
		ERR_EXIT("socket");
	struct sockaddr_in servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(5188);
	servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
		ERR_EXIT("connect");
	struct packet sendbuf;
	struct packet recvbuf;
	memset(&sendbuf,0,sizeof(sendbuf));
	memset(&recvbuf,0,sizeof(recvbuf));
	int n;
	while(fgets(sendbuf.buf,sizeof(sendbuf.buf),stdin)!=NULL)
	{
		n=strlen(sendbuf.buf);
		sendbuf.len=htonl(n);
		write(sock,&sendbuf,4+n);
		int ret=readn(sock,&recvbuf.len,4);
		if(ret==-1)
			ERR_EXIT("read");
			else if(ret<4)
			{
				printf("client close\n");
				break;
			}
			n=htohl(recvbuf.len);
			ret=readn(sock,recvbuf.buf,n);
			if(ret==-1)
			