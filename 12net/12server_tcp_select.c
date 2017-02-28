#include "func.h" 
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
	int newfd=-1;
	char buf[ 128];
	fd_set rdset;
	while( 1)
	{
		FD_ZERO( &rdset);
		FD_SET(0,&rdset);
		FD_SET( sfd,&rdset);
		if(newfd>0)
		{
			FD_SET( newfd,&rdset);
			printf( " i have set\n" );
		}
		ret=select(NUM+4,&rdset,NULL,NULL,NULL);//select一直在等；
		if( ret!=-1)
		{
			if( FD_ISSET(sfd,&rdset))
			{

				newfd=accept( sfd,( struct sockaddr*)&client_addr,&lenth);//连接成功后卡在这里，等下一个连接；
				if(-1==newfd)
				{
					perror("accept" );
					close( sfd);
					return -1;
				}
				printf("connect success,client ip=%s,client port=%d\n" ,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
			}
			else if(FD_ISSET(newfd,&rdset))
			{

				bzero( buf,sizeof( buf));
				printf( "i will recv\n" );
				ret=recv(newfd,buf,sizeof( buf),0);
				printf( "i have recv\n" );
				if( ret>0)
				{
					printf( "%s\n" ,buf);
				}
			}
			else if( FD_ISSET( 0,&rdset))
			{
				 bzero( buf,sizeof( buf));
				 read(0,buf,sizeof( buf));
				 ret=send( newfd,buf,strlen(buf)-1,0);//去掉read到的换行；
				 if( -1==ret)
				 {
					  perror("send" );
					  close( newfd);
					  close( sfd);
					  return -1;
				 }
			}
		}
	}
	return 0;
}
