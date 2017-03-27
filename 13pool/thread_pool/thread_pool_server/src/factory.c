#include"factory.h"

void factory_init(pfactory_t pf,\
		pfunc_t pfun_con, pfunc_t pfun_pro,\
		int con_cnt, int pro_cnt,\
		int que_capacity)
{
	factory_que_init(&(pf ->ft_que), que_capacity );//初始化我们的队列描述结构体
	pthread_cond_init(&(pf ->ft_visit_cond ), NULL);//初始化线程池条件变量
//	pthread_cond_init(&( pf ->ft_pro_cond ), NULL);
	pf  ->ft_con_func = pfun_con;//给子线程赋入口函数
	pf  ->ft_pro_func = pfun_pro;

	pf ->ft_pro_cnt = pro_cnt ;//子线程数目
	pf ->ft_con_cnt = con_cnt ;
	
	pf ->ft_arr_pro = (pthread_t*)calloc(pro_cnt, sizeof(pthread_t));//为子线程的thread_id 申请空间
	pf ->ft_arr_con = (pthread_t*)calloc(con_cnt, sizeof(pthread_t));

	pf ->ft_flag = 0 ;//判断线程池是否已经启动，0是未启动，1是已启动
	
}
void factory_start(pfactory_t pf)// factory_start(pf); factory_start(pf)
{
	if(pf ->ft_flag == 1)
	{
		return ;
	}
	int cnt ;
	pf ->ft_flag = 1 ;
	
	for(cnt = 0; cnt < pf ->ft_pro_cnt; cnt ++)
	{
		pthread_create(pf ->ft_arr_pro + cnt, NULL, pf ->ft_pro_func, (void*)pf );
	}
	//循环启动子线程
	
	for(cnt = 0; cnt < pf ->ft_con_cnt; cnt ++)
	{
		pthread_create(pf ->ft_arr_con + cnt, NULL, pf ->ft_con_func, (void*)pf );
	}

}
void factory_stop(pfactory_t pf)
{
	if(pf ->ft_flag == 0)
	{
		return ;
	}
	pf ->ft_flag = 0 ;
	int cnt ;
	for(cnt = 0; cnt < pf ->ft_pro_cnt; cnt ++)
	{
		pthread_join( (pf ->ft_arr_pro)[cnt], NULL );
	}

	for(cnt = 0; cnt < pf ->ft_con_cnt; cnt ++)
	{
		pthread_join( (pf ->ft_arr_con)[cnt], NULL );
	}
	//回收子线程的资源
}
void factory_destroy(pfactory_t pf)
{
	factory_que_destroy( &pf ->ft_que);
	pthread_cond_destroy(&(pf ->ft_visit_cond));
//	pthread_cond_destroy(&(pf ->ft_con_cond));
	free(pf ->ft_arr_pro);
	free(pf ->ft_arr_con);
	//回收我们的factroy资源
}

