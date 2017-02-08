#include"head.h"

int main(int argc,char **argv)
{
    if(argc!=2)
    {
        printf("error args\n");
        return -1;
    }
	int fd1=open(argv[1],O_RDWR|O_CREAT,0666);
	if(-1==fd1)
	{
		perror("open");
		return -1;
	}
//	int fd2=fd1;//文件描述符进行赋值的时候无作用
	int fd2=dup(fd1); 
	/*
	 int dup(int oldfd);进行文件描述符复制,返回当前文件描述符中最小且未使用的数字
	*/
	close(fd1);//采用引用计数,当计数为0时候才关闭文件
	char buf[20]={0};
	int ret=read(fd2,buf,sizeof(buf));
	printf("errno=%d\n",errno);//查看errno,需要引用头文件 #include <errno.h>
	printf("%s\n",buf);
	return 0;
	//vim在编辑文件的时候,会在文件结尾自动加回车\n
}
