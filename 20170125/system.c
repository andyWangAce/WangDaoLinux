#include"head.h"

void main()
{
	printf("I am parent\n");
	system("ls -al");//创建一个子进程,且子进程和父进程间的关联较少
	printf("the end\n");
}
