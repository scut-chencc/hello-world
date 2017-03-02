#include "func.h" 
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//疑问：为什么^c退出，会不断给客户端发空信息呢？因为客户端的fd_isset( newfd,&rdset会一直成立)
int main( int argc,char* argv[ ])
{
	if( argc!=3)
	{
		printf(" error args\n" );
		return -1;
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket" );
		return -1;
	}
	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	client_addr.sin_family=AF_INET;
	client_addr.sin_port=htons(atoi(argv[ 2]));
	client_addr.sin_addr.s_addr=inet_addr(argv[ 1]);
	int ret;
	ret=connect(sfd,( struct sockaddr*)&client_addr,sizeof( struct sockaddr));
	if( -1==ret)
	{
		perror("connect" );
		close( sfd);
		return -1;
	}
	printf("connect server success\n" );
	//char buf[ 128];
	fd_set rdset;
	/*
	   while( 1)
	   {
	   FD_ZERO( &rdset);
	   FD_SET( 0,&rdset);
	   FD_SET( sfd,&rdset);
	   ret=select(sfd+1,&rdset,NULL,NULL,NULL);
	   if( ret>0)
	   {
	   if(FD_ISSET(0,&rdset))
	   {
	   bzero( buf,sizeof( buf));
	   read( 0,buf,sizeof( buf));
	   ret=send(sfd,buf,strlen( buf)-1,0);//-1是去掉输入的回车；
	   if( -1==ret)
	   {
	   perror("send" );
	   close( sfd);
	   return -1;
	   }
	   printf( "i have send\n" );
	   }
	   if( FD_ISSET(sfd,&rdset))
	   {

	   bzero( buf,sizeof( buf));
	   ret=recv(sfd,buf,sizeof( buf),0);
	   if( ret>0)
	   {
	   printf("I am client,the message is %s\n" ,buf);
	   }
	   }
	   }
	   }
	   */
	char buf[ 4096]={0};
	int file_fd=open("12server_tcp_select.c" ,O_RDWR);
	ret=read(file_fd,buf,2048);
	if(ret==-1)
	{
		 perror( "read" );
		 exit( -1);
	}
	ret=send(sfd,buf,ret+1,0);//-1是去掉输入的回车；
	if( -1==ret)
	{
		perror("send" );
		close( sfd);
		return -1;
	}
	printf( "i have send\n" );
	while( 1);
	close(sfd);
	return 0;
}
