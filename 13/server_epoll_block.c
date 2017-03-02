#include "func.h" 
#include <sys/epoll.h>
#define NUM 10
int main(int argc,char* argv[ ])
{
	if(argc!=3)
	{
		printf("error args\n" );
		return -1;
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if( -1==sfd)
	{
		perror("socket" );
		return -1;
	}
	struct sockaddr_in server_addr;
	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(atoi(argv[2]));
	server_addr.sin_addr.s_addr=inet_addr(argv[ 1]);
	int ret=bind(sfd,(struct sockaddr*)&server_addr,sizeof(struct sockaddr));
	if( -1==ret)
	{
		perror( " bind" );
		close( sfd);
		return -1;
	}
	ret=listen(sfd,NUM);
	if( -1==ret)
	{
		perror( " listen" );
		close( sfd);
		return -1;
	}
	struct sockaddr_in client_addr;
	bzero(&client_addr,sizeof(client_addr));
	int lenth =sizeof(client_addr);
	int epfd=epoll_create( 1);
	struct epoll_event ev,events[ 11];
	ev.data.fd=sfd;
	ev.events=EPOLLIN;
	ret=epoll_ctl( epfd,EPOLL_CTL_ADD,sfd,&ev);
	if( ret==-1)
	{
		perror( "epoll_ctl" );
		exit( -1);
	}
	//char buf[512];
	char buf[ 5];
	while( 1)
	{
		int eventnum;
		eventnum=epoll_wait(epfd,events,11,-1);//select一直在等；
		int i;
		for(i=0;i<eventnum;i++)
		{

			if(events[ i].data.fd==sfd)
			{

				int newfd=accept( sfd,( struct sockaddr*)&client_addr,&lenth);//连接成功后卡在这里，等下一个连接；
				if( newfd==-1)
				{
					 perror( "accept" );
					 close( sfd);
					 exit( -1);
				}
				printf("connect success,client ip=%s,client port=%d\n" ,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
				printf("the new fd is %d\n" ,newfd);
				ev.data.fd=newfd;
				ev.events=EPOLLIN;
				ret=epoll_ctl(epfd,EPOLL_CTL_ADD,newfd,&ev);
				if( ret==-1)
				{
					 perror( "epoll_ctl_newfd" );
					 exit( -1);
				}
			} 
			else
			{

				bzero( buf,sizeof( buf));
				printf( "i will recv\n" );
				ret=recv(events[ i].data.fd,buf,sizeof( buf),0);
				if( ret==0)//代表关闭
				{
					ev.data.fd=events[ i].data.fd;
					 epoll_ctl(epfd,EPOLL_CTL_DEL,events[ i].data.fd,&ev);
					 printf("%d client disconnect\n",ev.data.fd );

				}
				else if( ret==-1)//yichang;
				{
					 perror( "recv" );
					 close( sfd);
					 exit( -1);
				}
				printf( "from %d client :%s\n" ,events[ i].data.fd,buf);
				if( ret>0)
				{
					printf( "%s\n" ,buf);
				}
			}
		    //else if( FD_ISSET( 0,&rdset))
			//{
			//	bzero( buf,sizeof( buf));
			//	read(0,buf,sizeof( buf));
			//	ret=send( newfd,buf,strlen(buf)-1,0);//去掉read到的换行；
			//	if( -1==ret)
			//	{
			//		perror("send" );
			//		close( newfd);
			//		close( sfd);
			//		return -1;
			//	}
			//} 
		} 
	}
	return 0;
}
