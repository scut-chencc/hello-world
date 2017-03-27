#include"head.h"
struct cmsghdr* send_fd(int sockfd, int fd)
{
	struct msghdr my_msg ;
	struct iovec bufs[2];
	struct cmsghdr* pcmsg ;
	int cmsglen = CMSG_LEN(sizeof(int));
	int val = 1024 ;
	char buf[]  = "hello world !" ;
	memset(&my_msg, 0, sizeof(my_msg));
	my_msg.msg_name = NULL ;
	my_msg.msg_namelen = 0 ;
	bufs[0].iov_base = &val ;
	bufs[0].iov_len = sizeof(val);
	bufs[1].iov_base = buf ;
	bufs[1].iov_len = strlen(buf);
	
	my_msg.msg_iov = bufs ;
	my_msg.msg_iovlen = 2 ;
	my_msg.msg_flags = 0 ;

	pcmsg = (struct cmsghdr*) calloc(1, cmsglen);
	pcmsg ->cmsg_len = cmsglen ;
	pcmsg ->cmsg_level = SOL_SOCKET ;
	pcmsg ->cmsg_type = SCM_RIGHTS ;
	*(int*)CMSG_DATA(pcmsg) = fd ;

	my_msg.msg_control = pcmsg ;
	my_msg.msg_controllen = cmsglen;

	sendmsg(sockfd, &my_msg, 0);
	return pcmsg;
}
struct cmsghdr* recv_fd(int sockfd, int* fd)
{
	struct msghdr my_msg ;
	struct iovec bufs[2];
	struct cmsghdr* pcmsg ;
	int cmsglen = CMSG_LEN(sizeof(int));
	int val = 0 ;
	char buf[32]  = "" ;
	memset(&my_msg, 0, sizeof(my_msg));
	my_msg.msg_name = NULL ;
	my_msg.msg_namelen = 0 ;
	bufs[0].iov_base = &val ;
	bufs[0].iov_len = sizeof(val);
	bufs[1].iov_base = buf ;
	bufs[1].iov_len = 31;
	
	my_msg.msg_iov = bufs ;
	my_msg.msg_iovlen = 2 ;
	my_msg.msg_flags = 0 ;
	printf("sizeof is %d\n",sizeof(struct cmsghdr));
	pcmsg = (struct cmsghdr*) calloc(1, cmsglen);

	my_msg.msg_control = pcmsg ;
	my_msg.msg_controllen = cmsglen;

	recvmsg(sockfd, &my_msg, 0);
	
	*fd = *(int*)CMSG_DATA(pcmsg);
	return pcmsg;	
}
