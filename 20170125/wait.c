#include"head.h"

int  main()
{
	pid_t pid=fork();
	if(pid==0)
	{
		printf("I am child\n");
		sleep(5);
		exit(0);
	}
	else
	{
		printf("I am parent,and I am waiting to clean the child\n");
		wait(NULL);//父进程等待子进程结束然后进行回收子进程资源,在等待的过程中父进程处于睡觉sleep状态.
		printf("finish cleaning\n");
		sleep(5);
		return 0;
	}
}
	
