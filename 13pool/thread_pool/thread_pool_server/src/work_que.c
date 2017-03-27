#include "work_que.h"

void factory_que_init(pque_t pq, int capacity)
{	
	pq ->que_head = NULL ;
	pq ->que_tail = NULL ;

	pq ->que_capacity = capacity ;
	pq ->que_size = 0 ;
	pthread_mutex_init(&(pq ->que_mutex), NULL);//初始化队列及队列锁
	
}
void factory_que_set(pque_t pq, pnode_t pnew)
{
	if(pq ->que_head == NULL)
	{
		pq ->que_head = pnew ;
	}else 
	{
		pq ->que_tail ->nd_next = pnew ;
	}
	pq ->que_tail = pnew ;
	pq ->que_size++ ;//把队列元素添加到队列里边
}
void factory_que_get(pque_t pq, pnode_t* p)
{
	*p = pq ->que_head ;
	pq ->que_head = (*p) ->nd_next ;//*p ++
	pq ->que_size-- ;//队列头被取出,并删除队列头
	if(pq -> que_size == 0)
	{
		pq ->que_tail = pq ->que_head ;
	}

}
void factory_que_destroy(pque_t pq)
{
	pthread_mutex_destroy(&(pq ->que_mutex));
	pnode_t pcur;
	pcur = pq -> que_head ;
	while(pcur)
	{
		pq ->que_head = pcur ->nd_next ;
		free(pcur);
		pcur = pq ->que_head ;
	}
	pq ->que_head = NULL;
	pq ->que_tail = NULL;
	pq ->que_capacity = 0 ;
	pq ->que_size = 0 ;
	//销毁队列
	
}
int factory_que_full(pque_t pq)
{
	return 0 ; //(pq ->que_size == pq ->que_capacity) ;
}
int factory_que_empty(pque_t pq)//判断队列是否为空
{
	return (pq ->que_size == 0) ;
}

