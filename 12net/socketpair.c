#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <fcntl.h>

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <strings.h>
#include <signal.h>
#include <sys/time.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/time.h>

#define ERR_EXIT(m) \
	do\
	{\
		perror(m);\
		exit(EXIT_FAILURE);\
	}while (0);


		
int main()
{
	int sockfds[2];
	if(socketpair(PF_UNIX,SOCK_STREAM,0,sockfds)<0)
		ERR_EXIT("socketpair");
	pid_t pid;
	pid=fork();
	if(pid==-1)
		ERR_EXIT("fork");
	if(pid>0)
	{
		int val=0;
		close(sockfds[1]);
		while(1)
		{
			++val;
			printf("sending data:%d\n",val);
			write(sockfds[0],&val,sizeof(val));
			read(sockfds[0],&val,sizeof(val));
			printf("data recv:%d\n",val);
			sleep(1);
		}
		
	}
	else if(pid==0)
	{
		int val;
		close(sockfds[0]);
		while(1)
		{
			read(sockfds[1],&val,sizeof(val));
			++val;
			write(sockfds[1],&val,sizeof(val));
		}
	}
	return 0;
}
	