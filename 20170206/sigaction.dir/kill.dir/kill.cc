 ///
 /// @file    kill.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-06 22:33:54
 ///
#include "head.h"
#include <iostream>
using std::cout;
using std::endl;

int main(int argc,char *argv[])
{
	pid_t pid;
	int sig;
	pid=atoi(argv[1]);
	sig=atoi(argv[2]);
	int ret;
	ret=kill(pid,sig);
	/*****
	 *.int kill(pid_t pid, int sig);
	 *pid>0  将信号发送为pid进程
	 *pid==0 将信号发送给与本进程同一进程组的所有进程
	 *pid==-1 将该信号发送给系统里现存的所有进程
	 *pid<0但是不等于-1 将该信号发送给进程组ID为|pid|的进程组中的所有进程
	 */ 
	if(ret==-1)
	{
		perror("kill");
		return -1;
	}
	return 0;
}
