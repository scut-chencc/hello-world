#include "func.h" 

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
	 char buf[ 128];
	 bzero( buf,sizeof( buf));
	 read( 0,buf,sizeof( buf));
	 //strcpy(buf,"how are you" );
	 ret=send(sfd,buf,strlen(buf)-1,0);
	 if( -1==ret)
	 {
		  perror( "send" );
		  close(sfd);
		  return -1;
	 }
	 bzero( buf,sizeof( buf));
	 ret=recv(sfd,buf,sizeof( buf),0);
	 if( ret>0)
	 {
		  printf("I am client,the message is %s\n" ,buf);
	 }
	 close(sfd);
	 return 0;
	 return 0;
}
