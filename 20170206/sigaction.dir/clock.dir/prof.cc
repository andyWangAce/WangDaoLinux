 ///
 /// @file    real.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-06 23:13:21
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

void sig(int signum)
{
	time_t t;
	time(&t);
	cout<<ctime(&t);

}
int main()
{
	signal(SIGPROF,sig);
	kill(0,SIGPROF);
	struct itimerval value;
	memset(&value,0,sizeof(value));
	value.it_value.tv_sec=2;
	value.it_interval.tv_sec=3;
	setitimer(ITIMER_PROF,&value,NULL);
	//实用计时器ITIMER_PROF,记录程序在用户态和内核态运行的时间和,到时会给自己发送信号SIGPROF
//	sleep(5);
	char buf[20]={0};
//	read(STDIN_FILENO,buf,sizeof(buf));//若设置read,则系统一直处于阻塞状态,没在运行,所以计时器无法计时
//	kill(0,SIGPROF);
	while(1);
	return 0;
}


