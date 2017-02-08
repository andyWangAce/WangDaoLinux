#include"head.h"

void main()
{
	pid_t pid=fork();
	if(pid==0)
	{
		printf("I am child\n");
		exit(0);
	}
	else
	{
		while(1);//如果子进程先结束,父进程尚在运行,子进程的相应资源未被回收,子进程会变成僵尸zombie状态,过多zombie会影响系统性能
	}
}
