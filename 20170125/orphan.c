#include"head.h"

void main()
{
	pid_t pid;
	pid=fork();
	if(pid==0)//返回子进程
	{
		printf("I am child\n");
		sleep(3);
		while(1);//父进程结束时候,子进程尚未结束的时候,子进程会变成孤儿进程,其父进程变成了1号进程
	}
	else
	{
		printf("I am parent\n");
	}
}
