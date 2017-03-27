#include"factory.h"
#define FILE_NAME "downloadserver"
void send_n(int sockfd, char*p, int len);
void handle_request(int sockfd);
void* con_handle(void* arg);
int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		printf("EXE IP PORT ! \n");
		exit(1);
	}//传递IP和端口号
	factory_t my_factory ;//定义线程池结构体
	factory_init(&my_factory, con_handle, NULL, 10, 0, 100);//初始化my_factory,线程入口函数，定义线程数目，队列长度
	factory_start(&my_factory);//线程启动
	printf("factory start ! \n");
	//socket
	int fd_listen ;
	if((fd_listen = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("socket !");
		exit(1);
	}//初始化tcp的socket
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
	}//给fd_listen绑定IP地址和端口号
	//listen
	if(-1 == listen(fd_listen, 10))
	{
		perror("listen");
		close(fd_listen);
		exit(1);
	}//监听对应的端口号
	//accept
	while(1)
	{
		printf("accepting...! \n");
		struct sockaddr_in client_addr ;
		socklen_t len = sizeof(client_addr);
		pnode_t pnew = (pnode_t)calloc(1, sizeof(node_t));//分配一个队列元素空间，拿到指向空间的指针
		pnew ->nd_sockfd = accept(fd_listen,(struct sockaddr*)&client_addr, &len );
		printf("client: %s:%d connected ! \n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		//	handle_request(fd_client);
		pthread_mutex_lock(&my_factory.ft_que.que_mutex);
		factory_que_set(&my_factory.ft_que, pnew);
		pthread_mutex_unlock(&my_factory.ft_que.que_mutex);//先加锁，往队列内放置元素，元素里包含client_fd,并解锁
		pthread_cond_signal(&my_factory.ft_visit_cond);//通知对应等待的子线程，元素已经放好，可以获取
		//		close(fd_client);


	}	
	//close
	close(fd_listen);
	return 0 ;
}
void handle_request(int sockfd)
{
	MSG send_msg;
	memset(&send_msg, 0, sizeof(MSG));
	strcpy(send_msg.msg_buf, FILE_NAME);
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
	//send_n(sockfd,(char*)&send_msg, 4 + send_msg.msg_len);
	int flag=0;
	send(sockfd,&flag, 4,0);
	sleep(rand()%5 + 1);
	close(fd_file);
	close(sockfd);
}
void send_n(int sockfd, char*p, int len)
{
	int send_sum, send_ret ;
	send_sum = 0;
	while(send_sum < len)
	{
		send_ret = send(sockfd, p + send_sum, len - send_sum, 0);
		send_sum += send_ret ;
	}
}
void* con_handle(void* arg)
{
	pfactory_t pf = (pfactory_t)arg ;//拿到我们factory
	pque_t pq = &pf ->ft_que ;//拿到我们的队列描述结构体指针
	pnode_t ptask ;//实际存储我们的client fd的结构体指针
	while(1)
	{
		pthread_mutex_lock(&pq ->que_mutex);//加锁
		while(factory_que_empty(pq))
		{
			pthread_cond_wait(&pf ->ft_visit_cond, &pq ->que_mutex);
		}//判断pq队列是否为空，为空时就wait
		factory_que_get(pq, &ptask);//拿到队列第一个元素，ptask指向它，并删除该元素
		pthread_mutex_unlock(&pq ->que_mutex);//释放锁，其他线程可以访问队列

		handle_request(ptask ->nd_sockfd);//给对应连接的客户端发送文件

		close(ptask ->nd_sockfd);//关闭客户端连接

		free(ptask);//释放队列元素所占的空间
	}
}


