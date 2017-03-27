/*************************************************************************
	> File Name: pool_child.c
	> Author: Comst
	> Mail:750145240@qq.com 
	> Created Time: Sat 22 Nov 2014 05:27:24 PM CST
 ************************************************************************/
#include"head.h"
static void child_main(int fd) ;
void make_child(pchild_t childs, int nchild)
{
	int index = 0 ;
	while(nchild > 0)
	{
		int fds[2] ;
		if(-1 == socketpair(AF_LOCAL, SOCK_STREAM, 0, fds))
		{
			perror("socketpair");
			exit(1);
		}
		pid_t pid = fork() ;
		if(pid == 0)// 0
		{
			close(fds[1]);
			child_main(fds[0]);
			exit(1);
		}
		close(fds[0]);
		childs[index].ch_pid = pid ;
		childs[index].ch_fd = fds[1];
		childs[index].ch_busy = 0 ;
		index ++ ;
		nchild -- ;
	}	
}
static void child_main(int fd) 
{
	int fd_client=0 ;
	int flag = 1 ;
	while(1)
	{
		printf("before recv ,fd_client is %d\n",fd_client);
		recv_fd(fd, &fd_client);
		printf("after recv ,fd_client is %d\n",fd_client);
		handle_request(fd_client);
		int ret;
		ret=write(fd, &flag, sizeof(flag));
		if(ret == -1)
		{
			perror("write");
		}
	}
}

