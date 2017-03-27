#include"head.h"
int main(int argc, char* argv[])//ip port nchild
{
	if(argc != 4)
	{
		printf("EXE IP PORT NCHILD ! \n");
		exit(1);
	}
	int nchild = atoi(argv[3]);
	int index ;
	pchild_t parr = (pchild_t)calloc(nchild, sizeof(child_t));
	make_child(parr, nchild);
	//socket
	int fd_listen ;
	if((fd_listen = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket !");
		exit(1);
	}
	//bind
	struct sockaddr_in server_addr ;
	memset(&server_addr, 0, sizeof(server_addr));
	server_addr.sin_family = AF_INET ;
	server_addr.sin_port = htons( atoi(argv[2]) ) ;
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	if(-1 == bind(fd_listen,(const struct sockaddr*)&server_addr, sizeof(server_addr)))
	{
		perror("bind");
		close(fd_listen);
		exit(1);
	}
	//listen
	if(-1 == listen(fd_listen, 10))
	{
		perror("listen");
		close(fd_listen);
		exit(1);
	}

	int ret,i;	
	int epfd=epoll_create(1);
	struct epoll_event ev,events[20];
	ev.data.fd = fd_listen;
	ev.events = EPOLLIN;

	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd_listen,&ev);
	if(ret == -1)
	{
		perror("epoll");
		exit(-1);
	}
	for(index = 0; index < nchild; index ++)
	{
		ev.data.fd = parr[index].ch_fd;
		ev.events = EPOLLIN;	
		epoll_ctl(epfd,EPOLL_CTL_ADD,parr[index].ch_fd,&ev);
		if(ret == -1)
		{
			perror("epoll");
			exit(-1);
		}
	}//放入所有的fds[1]，用于服务器父子进程通信的

	while(1)
	{
		int eventnum;
		eventnum=epoll_wait(epfd,events,20,-1);
		for(i=0;i<eventnum;i++)
		{
			if(events[i].data.fd == fd_listen)//给子进程分配任务
			{
				int fd_client = accept(fd_listen, NULL, NULL);
				for(index = 0; index < nchild; index ++)
				{
					if(parr[index].ch_busy == 0)
					{
						break ;
					}
				}
				if(index == nchild)
				{
					continue ;
				}
				send_fd(parr[index].ch_fd, fd_client);
				printf("send success\n");
				parr[index].ch_busy = 1;
			}
			//把子进程标识为非忙碌
			for(index = 0; index < nchild; index ++)
			{
				if(events[i].data.fd == parr[index].ch_fd)
				{
					parr[index].ch_busy = 0 ;
				}
			}
		}

	}	
	//close
	close(fd_listen);
	return 0 ;
}
