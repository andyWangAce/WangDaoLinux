#include"head.h"

int main(int argc,char **argv)
{
	pid_t p1,p2;
	p1=getpid();//获取进程id
	p2=getppid();//获取父进程id
	printf("pid=%d,ppid=%d\n",p1,p2);
	while(1);
	/*
	.ps -elf 查看所有打开的进程,
	若进程处于运行状态,标识为R;
	若进程处于睡眠状态,标识为S;
	若进程处于僵尸状态,标识为Z;
	若进程处于挂起状态,标识为T;
	*/
	return 0;
}
