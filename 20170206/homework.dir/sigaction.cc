 ///
 /// @file    sigaction.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-08 17:12:25
 ///
#include "head.h"
#include <iostream>
using std::cout;
using std::endl;

void sig(int signum,siginfo_t *p1,void *p)
{
	cout<<endl<<signum<<"is coming"<<endl;
	sleep(1);
	cout<<endl<<signum<<"is finishing"<<endl;
}

int main()
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_sigaction=sig;
	act.sa_flags=SA_SIGINFO|SA_NODEFER;
	sigaction(SIGINT,&act,NULL);
	while(1);
	return 0;
}
