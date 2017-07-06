#ifndef __FACTORY_H__
#define __FACTORY_H__
#include"head.h"
#include"work_que.h"
typedef void* (*pfunc_t)(void*)  ;
typedef struct tag
{
	que_t ft_que;
	pthread_cond_t ft_visit_cond;//线程池条件变量，控制线程同步
	//pthread_cond_t ft_con_cond;
	pfunc_t ft_con_func;
	pfunc_t ft_pro_func;
	int ft_pro_cnt ;
	int ft_con_cnt ;
	pthread_t* ft_arr_con;
:x
	int ft_flag ;

}factory_t, *pfactory_t ;//描述线程池结构体
void factory_init(pfactory_t pf,\
		pfunc_t pfun_con, pfunc_t pfun_pro,\
		int con_cnt, int pro_cnt,\

		int que_capacity);
void factory_start(pfactory_t pf);
void factory_stop(pfactory_t pf);
void factory_destroy(pfactory_t pf);
#endif
