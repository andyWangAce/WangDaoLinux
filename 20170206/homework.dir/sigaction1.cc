///
/// @file    sigaction1.cc
/// @author  Andy(wangyanchao_ace@126.com)
/// @date    2017-02-08 19:31:38
///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

void sig(int signum,siginfo_t *,void *)
{
	cout<<signum<<" is coming"<<endl;
	sleep(2);
	sigset_t set;
	sigemptyset(&set);
	sigpending(&set);
	if(sigismember(&set,SIGQUIT))
{
cout<<"SIGQUIT is pending."<<endl;
}
else
{
cout<<"SIGQUIT is not pending."<<endl;
}
}
int main()
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_flags=SA_SIGINFO;
	sigset_t set;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGQUIT);
	act.sa_sigaction=sig;
	sigaction(SIGINT,&act,NULL);
	while(1);
	return 0;
}
