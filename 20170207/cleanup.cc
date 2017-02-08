 ///
 /// @file    cleanup.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-07 15:31:43
 ///
 
#include "head.h"
#include <iostream>
using std::cout;
using std::endl;

void clean(void *p)
{
	cout<<"I am cleaning :"<<(long int)p<<endl;
}
void * thread(void *p)
{
	pthread_cleanup_push(clean,(void *)1);
	/***
	 *.线程终止清理设置函数成对出现,pthread_cleanup_push设置资源清理行为函数,
	 *	pthread_cleanup_push与pthread_cleanup_push之间的代码段的终止动作都将得到执行
	 *.void pthread_cleanup_push(void (*routine)(void *),void *arg);
	 *routine函数为资源清理行为函数,arg为传给其的参数
	 *
	 *
	 */
	cout<<"thread is working"<<endl;
	//pthread_exit(NULL);
	pthread_cleanup_pop(1);
	cout<<"cleaning is over"<<endl;
	return NULL;
	/*****
	 * .void pthread_cleanup_pop(int execute);
	 *  execute参数为非0值时,线程函数执行到pthread_cleanup_pop处,将清理行为函数栈退栈一个清理行为函数并执行,
	 *  执行完毕后,继续执行线程执行函数
	 * .此外线程函数在主动pthread_exit()或者被pthread_cancel()干掉的时候会执行线程清理函数,若没有执行这两个函数
	 * ,且return退出,pthread_cleanup_pop(0); 则不会执行线程清理函数
	 * 即以下这种情况
	 *pthread_cleanup_pop(0);
	 *cout<<"cleaning is over"<<endl;
	 *return NULL;
	 */ 
}
int main()
{
	pthread_t pth;
	pthread_create(&pth,NULL,thread,NULL);
	pthread_join(pth,NULL);
	return 0;
}
