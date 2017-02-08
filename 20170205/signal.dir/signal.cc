 ///
 /// @file    signal.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-05 16:38:47
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

void sig(int num)//捕捉到信号时候的行为
{
	cout<<"before,the signal num:"<<num<<endl;
	sleep(2);
	cout<<"after,the signal num"<<num<<endl;
}
int main()
{
	 signal(SIGINT,sig);
	 /*
	  *signa()函数创建的信号处理行为有如下特点:若正在发生系统调用的时候,接收到相应信号,进行处理相应的
	  *的行为,处理行为函数执行完毕后,再返回被打断的系统调用
	  */ 
	 char buf[20]={0};
	 read(STDIN_FILENO,buf,sizeof(buf));
	 cout<<buf;
	 return 0;
}
