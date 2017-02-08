 ///
 /// @file    pthread_cancel.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-07 20:31:26
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

void clean(void *p)
{
	cout<<"I will clean"<<endl;
	delete p;
	cout<<"cleaning is over"<<endl;
}

void * pthread (void *p)
{
	int *pi=new int;
	pthread_cleanup_push(clean,pi);
	sleep(3);
	pthread_cleanup_pop(1);
	return NULL;
}
int main()
{
	pthread_t pth;
	pthread_create(&pth,NULL,pthread,NULL);
	sleep(1);
	pthread_cancel(pth);
	pthread_join(pth,NULL);
	return 0;
}


