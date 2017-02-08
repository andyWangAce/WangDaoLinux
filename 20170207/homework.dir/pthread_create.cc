
/// @file    thread.cc
/// @author  Andy(wangyanchao_ace@126.com)
/// @date    2017-02-07 10:33:36
///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;


void * pthread(void *p)
{
	cout<<"pthread argv="<<(long int)p<<endl;
	return (void *)2;
}

int main()
{
	pthread_t pthid;
	//创建子线程
	int ret=pthread_create(&pthid,NULL,pthread,(void *)1);//将变量i的值强转为void *
	if(ret!=0)
	{
		cout<<"error num is"<<ret;
	}
	//等待子线程
	int *pi;
	pthread_join(pthid,(void**)pi);
//	cout<<"return="<<*pi<<endl;
	printf("return=%d\n",*pi);
	return 0;
}
