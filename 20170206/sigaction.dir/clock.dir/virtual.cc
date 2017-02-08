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
	signal(SIGVTALRM,sig);
	kill(0,SIGVTALRM);
	struct itimerval value;
	memset(&value,0,sizeof(value));
	value.it_value.tv_sec=2;
	value.it_interval.tv_sec=3;
	setitimer(ITIMER_VIRTUAL,&value,NULL);
	/*
	虚拟计时器ITIMER_VIRTUAL:记录程序在用户态运行的时间,到时会给自己发送信号SIGVTALRM
	*/
	char buf[20]={0};
	sleep(5);
//	read(STDIN_FILENO,buf,sizeof(buf));
	while(1);
	return 0;
}


