#include"head.h"

int main()
{
	printf("ready");
	//exit(0);//exit(返回值)在返回的时候,会清空I/O缓存区,会将标准输出缓存区的内容输出到屏幕上,再关闭进程
	_exit(1);//_exit()不刷新I/O缓存区,直接将进程关闭
	/*
	main函数中的return x;等价 exit(x);
	子进程使用exit(x);
	*/
}
