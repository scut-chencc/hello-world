#include"head.h"
void handle_request(int sockfd)
{
	MSG send_msg;
	memset(&send_msg, 0, sizeof(MSG));
	strcpy(send_msg.msg_buf, FILE_NAME);
	send_msg.msg_len = strlen(send_msg.msg_buf);
	printf("send len is %d\n",send_msg.msg_len);
	send_n(sockfd, (char*)&send_msg, 4 + send_msg.msg_len);
	printf("I have send the filename\n");
	int fd_file = open(FILE_NAME, O_RDONLY);
	if(fd_file == -1)
	{
		perror("open");
		exit(-1);
	}
	char buf[32];
	int readn ;
	while(memset(&send_msg, 0, sizeof(MSG)), (send_msg.msg_len = read(fd_file, send_msg.msg_buf, sizeof(send_msg.msg_buf))) > 0)
	{
		send_n(sockfd,(char*)&send_msg, 4 + send_msg.msg_len);
		//sleep(3);
	}
	int flag=0;
	send(sockfd,&flag, 4,0);//客户端判断结束
	//send_n(sockfd,(char*)&send_msg, 4 + send_msg.msg_len);//客户端判断结束
	sleep(rand()%5 + 1);
	close(fd_file);
	close(sockfd);
	printf("handle_request is over\n");
}
 
