#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
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
	
struct packet
{
	int len;
	char buf[1024];
};

ssize_t readn(int fd,void* buf,size_t count)
{
	size_t nleft=count;
	ssize_t nread;
	char* bufp=(char*)buf;
	while(nleft>0)
	{
		if((nread==read(fd,buf,nleft)<0))
		{
			if(errno==EINTR)
				continue;
			return -1;
		}
		else if(nread==0)//读完了
			return  count-nleft;
		bufp+=nread;
		nleft-=nread;
	}
}

ssize_t writen(int fd,const void* buf,size_t count)
{
	size_t nleft=count;
	ssize_t nwritten;
	char* bufp=(char*)buf;
	while(nleft>0)
	{
		if((nwritten=write(fd,bufp,nleft))<0)
		{
			if(errno==EINTR)
				continue;
			return -1;
		}
		else if(nwritten==0)
		{
			continue;
		}
		bufp+=nwritten;
		nleft-=nwritten;
	}
}

ssize_t recv_peek(int sockfd,void* buf,size_t len)
{
	while(1)
	{
		int ret=recv(sockfd,buf,len,MSG_PEEK);//窥探数据，不从 套接口缓冲区删除
		if(ret==-1&& errno==EINTR)
			continue;
		return ret;
	}
}

ssize_t readline(int sockfd,void* buf,size_t maxline)
{
	int ret;
	int nread;
	char* bufp=buf;
	int nleft=maxline;
	while(1)
	{
		ret=recv_peek(sockfd,bufp,nleft);
		if(ret<0)
			return ret;
		else if(ret==0)
			return ret;
		nread=ret;
		int i;
		for(i=0;i<nread;i++)
		{
			if(bufp[i]=='\n')
			{
				ret=readn(sockfd,bufp,i+1);
				if(ret!=i+1)
					exit(EXIT_FAILURE);
				return ret;
			}
		}
		if(nread>nleft)
		 exit(EXIT_FAILURE);
		nleft-=nread;
		ret=readn(sockfd,bufp,nread);
		if(ret!=nread)
			exit(EXIT_FAILURE);
		bufp+=nread;
	}
	return -1;
}


int main(void)
{
	int sock;
	if((sock=socket(PF_INET,SOCK_STREAM,IPPROTO_TCP))<0)
		ERR_EXIT("socket");
	struct sockaddr_in servaddr;
	struct sockaddr_in server_addr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(5188);
	servaddr.sin_addr.s_addr=inet_addr("192.168.44.149");
	if(connect(sock,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
		ERR_EXIT("connect");
	char sendbuf[1024]={0};
	char recvbuf[1024]={0};
	while(fgets(sendbuf,sizeof(sendbuf),stdin)!=NULL)//接收数据到发送缓冲区
	{
		write(sock,sendbuf,strlen(sendbuf));//对方通过\n区分消息的边界的
		int ret=readline(sock,recvbuf,sizeof(recvbuf));
		if(ret==-1)
			ERR_EXIT("readline");
		if(ret==0)
		{
			printf("client close\n");
			break;
		}
		fputs(recvbuf,stdout);
		memset(sendbuf,0,sizeof(sendbuf));
		memset(recvbuf,0,sizeof(recvbuf));	
	}
	close(sock);
	return 0;
}
		
