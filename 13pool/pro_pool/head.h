#ifndef __HEAD_H__
#define __HEAD_H__
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/socket.h>
#include"my_msg.h"
#include<sys/select.h>
#include<sys/time.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#define FILE_NAME "main.c"
typedef struct child_tag
{
	int ch_fd ;
	pid_t ch_pid ;
	int ch_busy ;
}child_t, *pchild_t;
void send_fd(int sockfd, int fd);
void recv_fd(int sockfd, int* fd);
void send_n(int sockfd, char*p, int len);
int recv_n(int sockfd, char* p, int len);
void handle_request(int sockfd);
void make_child(pchild_t childs, int nchild);
#endif
