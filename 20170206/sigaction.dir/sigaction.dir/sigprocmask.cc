 ///
 /// @file    sigaction.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-06 10:39:32
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

void sig(int signum)
{
	cout<<endl<<signum<<"is coming"<<endl;
}
int main(void)
{
	signal(SIGINT,sig);
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);//将SIGINT添加到set集合
	int ret;
	ret=sigprocmask(SIG_BLOCK,&set,NULL);
	/******
	 *.int sigprocmask(int how, const sigset_t *set, sigset_t *oldset);
	 *.sigprocmask是全程阻塞信号即未在处理信号或在处理信号时均可以阻塞指定信号,
	 * 然而函数sigaction利用sa_mask只是在处理一个信号时候对其他信号阻塞
	 *.how分为3中:
	 *	SIG_BLOCK  将set集合中的信号添加到本进程现有的阻塞信号          +
	 *	SIG_UNBLOCK 将本进程现有的阻塞信号集合中移除set集合中包含的信号 -
	 *	SIG_SETMASK 将本进程现有的阻塞信号集合重置为set集合             =
	 *.一般这样使用该函数:
	 *     屏蔽;
	 *     关键代码;
	 *     屏蔽;
	 */ 
	if(-1==ret)
	{
		perror("sigprocmask");
		return -1;
	}
	cout<<"working begin"<<endl;
	sleep(3);
	cout<<"working end"<<endl;
	ret=sigprocmask(SIG_UNBLOCK,&set,NULL);
	 return 0;
}
