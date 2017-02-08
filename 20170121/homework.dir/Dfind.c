#include"head.h"

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("参数错误\n");
		return -1;
	}
	DIR *dir=opendir(argv[1]);
	if(dir==NULL)
	{
		perror("opendir");
		return -1;
	}
	struct dirent *p;
	int flag=0;
	while((p=readdir(dir))!=NULL)
	{
		if(strcmp(argv[2],p->d_name)==0)
		{
			printf("%s/%s\n",argv[1],argv[2]);
			flag=1;
		}	
	}
	if(0==flag)
	{printf("该目录下无此文件\n");}
	return 0;
}
