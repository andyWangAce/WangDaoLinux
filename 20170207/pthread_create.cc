
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
//	pthread_exit((void *)1);
	/******
	 *void pthread_exit(void *retval);
	 *主动结束线程,返回值为retval,返回值可以被pthread_join捕捉到
	 */ 
	return (void *)1;
}

int main()
{
	pthread_t pthid;
	for(int i=0;i<2;i++)//for循环产生两个线程
	{
		int ret=pthread_create(&pthid,NULL,pthread,(void *)i);//将变量i的值强转为void *
		if(ret!=0)
		{
			cout<<"error num is"<<ret;
		}
		cout<<pthid;

		//接收整型数据
		//法一:定义一级指针,将其地址传给pthread_join
		int *pret;
		pthread_join(pthid,(void**)pret);//可以将一级指针强转为二级指针,两者都为4B,存放地址
		/*
		 *.int pthread_join(pthread_t thread, void **retval);
		 * thread为线程号,第二个参数去得到线程的返回值,无论线程return还是pthread_exit退出都可以接收
		 * 因为线程函数的返回值是void *,即一级指针,
		 * 为了得到其值,在main线程中,定义一个一级指针,将其强转为为二级指针,欺骗编译器,在pthread_join
		 * 函数内部对二级指针取值*,并赋值,实质是main线程中的一级指针取值,并赋值,所以main线程中,将一级指针
		 * 取值*,输出即可
		 */ 
	//	printf("%ld\n",(long int )(*pret));
		printf("%d\n",*pret);
		//法二:定义二级指针,不常用
#if 0
		int **ppret;
		pthread_join(pthid,(void**)ppret);
		cout<<(long int)(*ppret)<<endl;
#endif		
	}
	return 0;
}
