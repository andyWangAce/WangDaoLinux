 ///
 /// @file    alarm.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-06 22:50:07
 ///
#include "head.h"
#include <iostream>
using std::cout;
using std::endl;

void sig(int signum)
{
	cout<<"SIGALRM"<<endl;
}
int main()
{	
	signal(SIGALRM,sig);
	alarm(2);
	/****
	 * unsigned int alarm(unsigned int seconds);表示seconds秒后,进程自身自动产生一个SIGALARM信号
	 */ 
	sleep(10);
	/*****
	 *int pause(void);
	 * 将自身挂起,直到有信号发生才返回
	 */ 
	return 0;
}
