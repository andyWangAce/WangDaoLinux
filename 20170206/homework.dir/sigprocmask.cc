 ///
 /// @file    sigprocmask.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-08 20:00:47
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;


int main()
{
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigprocmask(SIG_BLOCK,&set,NULL);
	sleep(5);
	sigset_t set1;
	sigemptyset(&set1);
	sigpending(&set1);
	if(sigismember(&set1,SIGINT))
	{
		cout<<endl<<"SIGINT is pending"<<endl;
	}
	else
	{
		cout<<"SIGITN is not pending"<<endl;
	}
	sigprocmask(SIG_UNBLOCK,&set,NULL);
	return 0;
}
