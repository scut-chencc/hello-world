#ifndef __WORK_QUE__
#define __WORK_QUE__
#include"head.h"
typedef struct tag_node
{
	int nd_sockfd ;
	struct tag_node* nd_next ;
}node_t, *pnode_t;//元素结构体，存储实际client fd
typedef struct tag_que
{
	pnode_t que_head, que_tail;
	int que_capacity;
	int que_size;

	pthread_mutex_t que_mutex ;
}que_t, *pque_t;//描述队列的结构体
void factory_que_init(pque_t pq, int capacity);
void factory_que_set(pque_t pq, pnode_t pnew);
void factory_que_get(pque_t pq, pnode_t* p);
void factory_que_destroy(pque_t pq);
int factory_que_full(pque_t pq);
int factory_que_empty(pque_t pq);
#endif
