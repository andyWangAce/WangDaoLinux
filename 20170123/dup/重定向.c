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
  	int fd2=open("2.txt",O_RDWR);
	int fd3;
//	fd3=dup2(fd1,5);
	fd3=dup2(fd1,fd2);
	/*
	. int dup2(int oldfd, int newfd);返回值为newfd
    .dup2,可以复制到指定的文件描述符,newfd可以问0-1023的整数,也可以是已经
	  打开的文件描述符,此时需要关闭原来的文件,再复制为新的文件描述符
	*/
	char buf[20]={0};
	read(fd3,buf,sizeof(buf));
	printf("fd3=%d,%s",fd3,buf);
	return 0;
}
		
