#include"head.h"

int main()
{
	if(fork()==0)
	{
		pid_t pid,pgid,sid;
		printf("I am child,pid=%d,pgid=%d,sid=%d\n",getpid(),getpgid(0),getsid(0));
		/*
  		 pid getpid(pid)返回指定进程的组ID,若返回当前进程,则pid写0
		 pid getsid(pid)返回指定进程的会话ID,若返回当前进程的会话ID,则参数为0
		int setpgid(pid_t pid,pid_t pgid),函数将进程号为pid的进程单独设置为新的进程组的组长,其组ID为该进程的进程ID,成功返回0
		pid_t setsid(),将该进程设置为新的会话组组长以及进程组组长,会话组ID以及进程组ID均为该进程的进程ID
		*/
		setpgid(0,0);
		printf("I am child,pid=%d,pgid=%d,sid=%d\n",getpid(),getpgid(0),getsid(0));
		setsid();
		printf("I am child,pid=%d,pgid=%d,sid=%d\n",getpid(),getpgid(0),getsid(0));
		exit(0);
	}else
	{
		pid_t pid,pgid,sid;
		printf("I am parent,pid=%d,pgid=%d,sid=%d\n",getpid(),getpgid(0),getsid(0));
		wait(NULL);
		return 0;
	}
}

