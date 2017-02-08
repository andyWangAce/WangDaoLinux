#include"head.h"

int main(int argc ,char *argv[])
{
	 if(argc!=2)
    {
        printf("error args\n");
        return -1;
    }
	int fd=open(argv[1],O_RDWR|O_CREAT,0666);
	if(fd<0)
	{	
		perror("open");
		return -1;
	}
	ftruncate(fd,1<<10);
	/*
	  int ftruncate(int fd, off_t length);
	  	该函数用于改变文件的大小,当length大于文件原有的长度的时候,使文件变大
		当length小于文件原有的长度时候,会将大于length的部分截断
	*/
	return 0;
}
