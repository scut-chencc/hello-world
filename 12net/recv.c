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
		if((nread==read(fd,buf,nleft)<0)
		{
			if(errno==FINTR)
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
		int ret=recv(sockfd,buf,len,MSG_PEEK);//窥探数据，不从套接口缓冲区删除
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

void do_service(int conn)
{
	char recvbuf[1024];
	while(1)
	{
		memset(recvbuf,0,sizeof(recvbuf));
		int ret=readline(conn,recvbuf,1024);
		if(ret==-1)
			ERR_EXIT("readline");
			
				
