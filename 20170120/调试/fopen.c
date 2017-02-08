#include<stdio.h>

int main(int argc ,char **argv)
{
	if(argc==1)
	{
		printf("只有一个参数\n");
		return -1;
	}
	printf("第一个参数:%s\n",argv[0]);
	printf("第二个参数:%s\n",argv[1]);
	FILE *fp=fopen(argv[1],"rb+");
	if(NULL==fp)
	{
		perror("fopen");	
		return -1;
	}
	printf("success\n");
	return 0;
}
