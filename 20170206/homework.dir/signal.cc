 ///
 /// @file    signal.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-08 16:57:14
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

void sig(int signum)
{
	cout<<endl<<signum<<"is coming"<<endl;
	sleep(2);
	cout<<signum<<"is finishing"<<endl;
}
int main()
{
	signal(SIGINT,sig);
	signal(SIGQUIT,sig);
	while(1);
	return 0;
}
