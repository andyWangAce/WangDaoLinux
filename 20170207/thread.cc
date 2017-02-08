 
 /// @file    thread.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-07 10:33:36
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

/****
 *.同一个进程中的各个线程共享进程的堆区域,代码,数据,文件描述符,信号.各个线程拥有自己的栈空间,
 *	线程之间切换较快,但是一个线程崩溃,会将所有的线程搞崩溃,不利于资源的管理和保护
 *.类似进程的    创建fork(),          退出exit(),        等待wait()
 * 线程有对应的  创建pthread_create(),退出pthread_exit() 等待pthread_join()
 *.main函数即为main线程,进行相应的线程资源回收
 */ 
void * pthread(void *p)
{
	cout<<"pthread "<<( long int )p<<endl;//将void *强转为long int 
//	cout<<"pthread "<<*(int *)p<<endl;
}

int main()
{
	pthread_t pthid;
	int i=10;
	int ret=pthread_create(&pthid,NULL,pthread,(void *)2);//传常量
//	int ret=pthread_create(&pthid,NULL,pthread,&i);
	/******
	 *.int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
	 * void *(*start_routine) (void *), void *arg);
	 * thread是传出参数,获得pthread_t类型的线程号
	 * pthread_attr_t为该线程的运行属性
	 * start_routine为创建线程的函数指针
	 * arg为传递给第三个参数即创建线程函数的参数,传递int型常量时候,将其转化为void *,在函数内部
	 * 将其(long int)p转化
	 *
	 */ 
	if(ret!=0)
	{
		cout<<"error num is"<<ret<<endl;
	}
	sleep(1);
	cout<<pthid<<endl;
	return 0;
}
