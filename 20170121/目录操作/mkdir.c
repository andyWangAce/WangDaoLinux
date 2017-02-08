#include"head.h"

int main(int argc,char **argv)
{
    if(argc!=2)
    {
        printf("参数错误\n");
        return -1;
    }
//	int ret=mkdir(argv[1],0777);
	int ret=rmdir(argv[1]);
	if(-1==ret)
    {
        perror("rmdir");
        return -1;
    }
	return 0;
}	
