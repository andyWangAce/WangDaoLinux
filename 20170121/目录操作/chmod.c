#include <sys/stat.h>
#include<stdio.h>
int main(int argc,char **argv)
{
	if(1==argc)
	{
		printf("只有一个参数\n");
		return -1;
	}
	chmod(argv[1],0777);
	return 0;
}
