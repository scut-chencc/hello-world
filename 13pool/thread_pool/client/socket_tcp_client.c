#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include "head.h"
int main(int argc,char* argv[])
{
	if(argc!=3)
	{
		printf("error args!\n");
		exit(-1);
	}
	int sfd =socket(AF_INET,SOCK_STREAM,0);//客户端初始化socket
	if(sfd==-1)
	{
		perror("socket");
		exit(-1);
	}
	struct sockaddr_in server_addr;
	memset(&server_addr,0,sizeof(struct sockaddr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port = htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	int ret;
	ret=connect(sfd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr));
	if(ret==-1)
	{
		perror("connect");
		close(sfd);
		exit(-1);
	}
	printf("connect server success\n");
	MSG recv_msg;
	memset(&recv_msg, 0, sizeof(MSG));
	int recv_num;
	char buf[1024]={0};
	recv(sfd, &recv_num,sizeof(int),0);
	recv(sfd,buf,recv_num,0);	
	printf("filename is %s\n",buf);
	
	int fd_file = open(buf,O_RDWR|O_CREAT,0644);
	if(fd_file == -1)
	{
		perror("open");
	}
 	while(1)
	{
		recv(sfd, &recv_num,sizeof(int),0);
		if(recv_num == 0)
			break;
		recv(sfd,buf,recv_num,0);
		write(fd_file,buf,recv_num);
	}	
	printf("recv success\n");
	close(fd_file);
	close(sfd);
}
	
