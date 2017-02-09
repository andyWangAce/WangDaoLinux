 ///
 /// @file    real.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-08 20:12:48
 ///
#include "head.h"
#include <iostream>
using std::cout;
using std::endl;

void sig(int signum )
{
	time_t t;
	time(&t);
	cout<<ctime(&t);
}

int main()
{
	signal(SIGPROF,sig);
	kill(0,SIGPROF);
	struct itimerval t;
	bzero(&t,sizeof(t));//在为t赋初值的时候要清零
	t.it_value.tv_sec=3;
	t.it_interval.tv_sec=2;
	setitimer(ITIMER_PROF,&t,NULL);
	sleep(5);
	while(1);
	return 0;
}
