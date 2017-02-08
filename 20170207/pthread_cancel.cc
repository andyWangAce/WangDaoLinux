 ///
 /// @file    pthread_cancel.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-07 20:31:26
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

void * pthread (void *p)
{
	cout<<"pthread is coming"<<endl;
	sleep(10);
	return NULL;
}
int main()
{
	pthread_t pth;
	pthread_create(&pth,NULL,pthread,NULL);
	sleep(1);
	pthread_cancel(pth);
	/*****
	 *int pthread_cancel(pthread_t thread);
	 *杀死线程号为thread的线程
	 */ 
	int *pi;
	pthread_join(pth,(void **)pi);
	cout<<*pi<<endl;
	return 0;
}


