#include"head.h"

int  main()
{
	pid_t pid=fork();
	if(pid==0)
	{
		printf("I am child\n");
		char *p=NULL;
		*p=2;
		sleep(5);
		exit(0);
	}
	else
	{
		int status;//pid_t wait(int *status).status存放子进程的退出状态
		printf("I am parent,and I am waiting to clean the child\n");
		wait(&status);
		if(WIFEXITED(status))
		/*
		   int	WIFEXITED(status),如果子进程正常结束,该函数返回非0值,
			若非正常结束,例如内中断,返回0
		*/
		{//正常结束时
			printf("child return :%d\n",WEXITSTATUS(status));
		/*
			int WEXITSTATUS(status);当正常结束时候,该函数可以得到子进程的返回值
		*/		
		}else
		{
			printf("process is crashing\n");
		}		
		/*
			pid_t waitpid(pid_t pid,int *status,int options).若options为WNOHANG,时候主进程在等待的过程
			不睡觉,继续往下走
		*/
	return 0;
	}
}
	
