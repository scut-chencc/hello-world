#ifndef __MSG_H__
#define __MSG_H__
#define MAX_SIZE 1024//为了内存对齐，提高cpu效率
typedef struct msg_tag
{
	int msg_len ;
	char msg_buf[MAX_SIZE - sizeof(int)];
}MSG, *pMSG;
#endif
