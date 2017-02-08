 ///
 /// @file    cond.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-08 10:40:01
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

struct data
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
};

void * pthread(void *p1)
{
	data *p=(data *)p1;
	cout<<"I am child,I will wait in a line"<<endl;
	pthread_mutex_lock(&p->mutex);
	pthread_cond_wait(&p->cond,&p->mutex);
	pthread_mutex_unlock(&p->mutex);
	cout<<"I am child,I am free"<<endl;
}
int main()
{
	data d1;
	pthread_mutex_init(&d1.mutex,NULL);
	pthread_cond_init(&d1.cond,NULL);
	pthread_t pthid[5];
	for(int i=0;i<5;i++)
	{
	pthread_create(&pthid[i],NULL,pthread,&d1);
	}
	sleep(1);
	cout<<"I am parent,I will wake the child up"<<endl;
	pthread_cond_broadcast(&d1.cond);
	/*****
	 *int pthread_cond_broadcast(pthread_cond_t *cond);
	 *将处于条件变量阻塞队列的所有线程唤醒
	 */ 
	cout<<"I am parent,waking is over"<<endl;
	for(int i=0;i<5;i++)
	{
	pthread_join(pthid[i],NULL);
	}
	return 0;
}
