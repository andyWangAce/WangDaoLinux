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
};//结构体定义最后要加分号

void * pthread(void *p1)
{
	data *p=(data *)p1;
	cout<<"I am child,I will wait in a line"<<endl;
	pthread_mutex_lock(&p->mutex);
	pthread_cond_wait(&p->cond,&p->mutex);
	pthread_mutex_unlock(&p->mutex);
	/********
	 *使用条件变量的过程:
	 *1.互斥锁加锁
	 *2.条件变量等待即int pthread_cond_wait(pthread_cond_t *restrict cond,pthread_mutex_t *restrict mutex);
	 *	此时该线程处于sleep状态,等待被唤醒 
	 * 3.互斥锁解锁
	 * 其中pthread_cond_wait所进行的操作为
	 *			1.将该线程添加到条件变量的阻塞队列上
	 *			2.unlock互斥锁
	 *			若该线程收到signal或者broadcast的信号则
	 *			1.将该线程唤醒
	 *			2.lock互斥锁
	 *	所以若多个线程执行该线程函数的时候,线程是阻塞在pthread_cond_wait的条件队列上,而不是互斥锁上
	 */ 
	cout<<"I am child,I am free"<<endl;
}
int main()
{
	data d1;
	pthread_mutex_init(&d1.mutex,NULL);
	pthread_cond_init(&d1.cond,NULL);
	/************
	 * int pthread_cond_init(pthread_cond_t *restrict cond,const pthread_condattr_t *restrict attr);
	 * 第一个参数cond为条件变量,第二个参数attr为条件变量的相关属性,该函数用于条件变量初始化
	 ********/ 
	pthread_t pthid;
	pthread_create(&pthid,NULL,pthread,&d1);
	sleep(1);
	cout<<"I am parent,I will wake the child up"<<endl;
	pthread_cond_signal(&d1.cond);
	/*
	 *int pthread_cond_signal(pthread_cond_t *cond);将条件变量阻塞队列上的队首线程唤醒
	 */ 
	cout<<"I am parent,waking is over"<<endl;
	pthread_join(pthid,NULL);
	return 0;
}
