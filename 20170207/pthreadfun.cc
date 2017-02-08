
/// @file    thread.cc
/// @author  Andy(wangyanchao_ace@126.com)
/// @date    2017-02-07 10:33:36
///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;
#define N 10000000
pthread_mutex_t lock;//将互斥锁定义为全局变量

void * pthread(void *p)
{
	//int *pi=(int *)p;
	for(int i=0;i<N;i++)
	{
		pthread_mutex_lock(&lock);
		*(int *)p=*(int*)p+1;
		pthread_mutex_unlock(&lock);
	}

	return NULL;
}

int main()
{
	pthread_t pthid;
	pthread_mutex_init(&lock,NULL);
	/***
	 * 初始化互斥锁
	 *int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
	 *第一个参数为互斥锁的地址,第二个参数为互斥锁的属性,普通锁为NULL
	 */ 
	int *p=new int;//不同的线程共享堆空间
	int ret=pthread_create(&pthid,NULL,pthread,p);
	if(ret!=0)
	{
		cout<<"error num is"<<ret<<endl;
	}
	for(int i=0;i<N;i++)
	{
		// pthread_mutex_lock(&lock); //若某线程连续上两次锁则会进入死锁状态
		pthread_mutex_lock(&lock);//上锁,int pthread_mutex_lock(pthread_mutex_t *mutex);
		pthread_mutex_trylock(&lock);//尝试上锁,若可以上锁则上锁;若不可以上锁,则不阻塞,继续执行下面代码
		*p=*p+1;
		pthread_mutex_unlock(&lock);//解锁,int pthread_mutex_unlock(pthread_mutex_t *mutex);
	}
	pthread_join(pthid,NULL);
	cout<<*p<<endl;
	return 0;
}
