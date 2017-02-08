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
	/*****
	 *	time_t time(time_t *tloc);//传入参数为time_t类型的变量,将其修改为自从1970-01-01以来的秒数
	 */
	cout<<ctime(&t);
	/*******
	 *char *ctime(const time_t *timep);返回年月日等形式的日期字符串
	 */ 
}
int main()
{
	signal(SIGALRM,sig);	
	kill(0,SIGALRM);
	struct itimerval value;
	memset(&value,0,sizeof(value));
	value.it_value.tv_sec=1;
	value.it_interval.tv_sec=2;
	setitimer(ITIMER_REAL,&value,NULL);
	/*******
    	*.每个进程可以使用3个计时器
     	*  真实计时器ITIMER_REAL:程序从开始执行到程序结束的实际时间,到时会给自己发送信号SIGALRM
    	*  虚拟计时器ITIMER_VIRTUAL:程序在用户态运行的时间,到时会给自己发送信号SIGVTALRM
    	*  实用计时器ITIMER_PROF:程序在用户态和内核态运行的时间和,到时会给自己发送信号SIGPROF
    	*/ 
	while(1);
	return 0;
}


