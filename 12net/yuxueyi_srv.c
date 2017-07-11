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
	
void echo_srv(int conn)
{
	char recvbuf[1024];
	int n;
	while(1)
	{
		memset(recvbuf,0,sizeof(recvbuf));
		n=read(conn,recvbuf,sizeof(recvbuf));
		if(n==-1)
		{
			if(n==EINTR)
				continue;
			ERR_EXIT("read");
		}
		else if(n==0)
		{
			printf("client close\n");//客户端关闭了
			break;
		}
		fputs(recvbuf,stdout);
		write(conn,recvbuf,strlen(recvbuf));
	}
	close(conn);
}

int main()
{
	int listenfd;
	if((listenfd=socket(PF_UNIX,SOCK_STREAM,0))<0)
		ERR_EXIT("socket");
	unlink("/tmp/test_socket");//删除sock文件
	struct sockaddr_un servaddr;
	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sun_family=AF_UNIX;
	strcpy(servaddr.sun_path,"/tmp/test_socket");//初始化地址：当前目录底下的test_socket
	if(bind(listenfd,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
		ERR_EXIT("bind");
	if(listen(listenfd,SOMAXCONN)<0)
		ERR_EXIT("listen");
	int conn;
	pid_t pid;
	while(1)
	{
		conn=accept(listenfd,NULL,NULL);//不关心对等方的地址和地址长度
		if(conn==-1)
		{
			if(conn==EINTR)
				continue;
			ERR_EXIT("accept");
		}
		pid=fork();
		if(pid==-1) 
			ERR_EXIT("fork");
		if(pid==0)
		{
			close(listenfd);//不需要处理监听的
			echo_srv(conn);//回射
			exit(EXIT_SUCCESS);
		}
		close(conn);//父进程不需要处理连接的
	}		
	return 0;
}