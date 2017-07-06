//创建进程池
#include"head.h"
static void child_main(int fd) ;
void make_child(pchild_t childs, int nchild)
{
	int index = 0 ;
	while(nchild > 0)
	{
		int fds[2] ;
		if(-1 == socketpair(AF_LOCAL, SOCK_STREAM, 0, fds))//为了后面传递文件描述符
		{
			perror("socketpair");
			exit(1);
		}
		pid_t pid = fork() ;
		if(pid == 0)// 0
		{
			close(fds[1]);
			child_main(fds[0]);//把父进程的文件描述符传给子进程开的管道
			exit(1);
		}
		close(fds[0]);
		childs[index].ch_pid = pid ;
		childs[index].ch_fd = fds[1];//监听子进程的fds[ 0]传来的信息：双向的；
		childs[index].ch_busy = 0 ;
		index ++ ;
		nchild -- ;
	}	
}
static void child_main(int fd)
{
	int fd_client ;
	int flag = 1 ;
	while(1)
	{
		recv_fd(fd, &fd_client);//等着接收信息；fd_client保存传来的文件描述符
		handle_request(fd_client);
		write(fd, &flag, sizeof(flag));//告诉父进程已经干完活
	}
}

