#include"head.h"
void handle_request(int sockfd)
{
	MSG send_msg;
	memset(&send_msg, 0, sizeof(MSG));
	strcpy(send_msg.msg_buf, FILE_NAME);//得到文件名
	send_msg.msg_len = strlen(send_msg.msg_buf);
	send_n(sockfd, (char*)&send_msg, 4 + send_msg.msg_len);
	int fd_file = open(FILE_NAME, O_RDONLY);
	char buf[32];
	int readn ;
	while(memset(&send_msg, 0, sizeof(MSG)), (send_msg.msg_len = read(fd_file, send_msg.msg_buf, sizeof(send_msg.msg_buf))) > 0)
	{
		send_n(sockfd,(char*)&send_msg, 4 + send_msg.msg_len);
		//		sleep(1);
	}
	send_n(sockfd,(char*)&send_msg, 4 + send_msg.msg_len);
	sleep(rand()%5 + 1);
	close(fd_file);
	close(sockfd);
}
 
