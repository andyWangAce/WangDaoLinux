#include"head.h"

int main(int argc,char **argv)
{
	if(argc!=2)
	{
		printf("参数错误\n");
		return -1;
	}
	printf("cwd:%s\n",getcwd(NULL,0));
	int ret=chdir(argv[1]);
	if(ret==-1)
	{
		perror("chdir");
		return -1;
	}
	printf("cwd:%s\n",getcwd(NULL,0));
	return 0;
}
