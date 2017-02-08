#include"head.h"

int main(int argc,int *arg[])
{
	if(argc==1)
	{
		printf("只有一个参数\n");
		return -1;	
	}	
	FILE *fp=fopen(argv[1],"rb+");
	if(NULL==fp)
	{
		perror("fopen");
		return -1;
	}
	printf("success\n");
	return 1;
}

