 ///
 /// @file    sigaction.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-06 10:39:32
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

void sig(int signum,siginfo_t *p,void *p1)
{
	cout<<endl<<"before num"<<signum<<endl;
	sleep(3);
	sigset_t set;
	sigemptyset(&set);//int sigemptyset(sigset_t *set)//清空信号集合
	sigpending(&set); //int sigpending(sigset *set),获得进程控制块当前的信号状态
	if(sigismember(&set,SIGQUIT))
	{
		cout<<"SIGQUIT is pending"<<endl;
	}
	else{
	cout<<"SIGQUIT is not pending"<<endl;
	}
	 //int sigismember(const sigset_t *set,int signum)//判断signum是否包含在set集合中,若在返回1,不在返回0
	cout<<"after num"<<signum<<endl;
}
int main(void)
{
	int ret;
	struct sigaction act;
	memset(&act,0,sizeof(act));
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGQUIT);//直接将SIGQUIT添加到act中的sa_mask 
	/*****
	 *sa_mask为中断屏蔽的信号集,此集合内的信号不会将正在执行的信号处理函数打断,但是相应的信号
	 *在sigset_t的1,不会被抹掉.然而SIG_IGN即忽略信号时,会将相应的sigset_t上的对应位置不断置0
	 *sa_mask是一个包含信号集合的sigset_t结构体,针对sigset_t有专门的处理函数
	 *int sigaddset(sigset_t *set,int signum)//往set中添加信号signum
	 */
	act.sa_sigaction=sig;
	act.sa_flags=SA_SIGINFO;
	 ret=sigaction(SIGINT,&act,NULL);
	 ret=sigaction(SIGQUIT,&act,NULL);
	if(-1==ret)
	{
		perror("sigaction");
		return -1;
	}
	while(1);
	return 0;
}
