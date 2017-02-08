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
	cout<<p->si_pid<<endl;
	cout<<p->si_uid<<endl;
	/*****
	 *sigingo_t{ 
	 *			pid_t  si_pid;//发送信号的进程ID
	 *			uid_t  si_uid;//发送进程的真实用户ID
	 *       }
	 */ 
}
int main(void)
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_sigaction=sig;
	act.sa_flags=SA_SIGINFO|SA_RESTART;
	int ret;
	 ret=sigaction(SIGINT,&act,NULL);
	 ret=sigaction(SIGQUIT,&act,NULL);
	if(-1==ret)
	{
		perror("sigaction");
		return -1;
	}
	sigemptyset(&act.sa_mask);
	char buf[20]={0};
	read(STDIN_FILENO,buf,sizeof(buf));
	cout<<buf;
	 return 0;
}
