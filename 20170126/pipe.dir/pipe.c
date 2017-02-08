#include"head.h"

int main()
{
	int fds[2];//fds存放读写文件描述符
	pipe(fds);
	/*
		fds[0],R端
		fds[1],W端
	*/
	printf("fds[0]=%d,fds[1]=%d\n",fds[0],fds[1]);
	if(!fork())//子进程
	{
		close(fds[1]);//关闭W端	
		char buf[20]={0};
		int ret=read(fds[0],buf,sizeof(buf));
		/*ssize_t read(int fd, void *buf, size_t count);
		ssize_t write(int fd, const void *buf, size_t count);
		read和write函数出错返回-1,读取完毕返回0,其他情况返回读写的个数,read和write会将自己字符串中的0读取与
		写入
		*/
		if(ret<0)
		{
			perror("read");
			return -1;	
		}
		printf("clen=%d\n",strlen(buf));
		printf("cret=%d\n",ret);
		puts(buf);
		close(fds[0]);
		sleep(1);
		exit(0);
	}
	else
	{//父进程
		close(fds[0]);//关闭读端
		char buf[]="hello world";
		int ret=write(fds[1],buf,sizeof(buf));
		printf("flen=%d\n",strlen(buf));
		printf("fret=%d\n",ret);
		wait(NULL);
		close(fds[1]);
//		return 0;
		exit(0);
	}
	/*	
	1.无名管道的特点:
		.只能在父子或者兄弟之间进行通信
		.半双工(因为管道就是半双工)
		.是一种特殊的文件,只可以存在内存中,可以对其使用read和write
	2. int pipe(int pipefd[2]);,pipe函数创建无名管道,pipefd[0]为管道的R端,
		pipefd[1]位管道的W端
	3.父进程创建无名管道,父进程创建子进程,则父子均有无名管道的R,W权限,故
		父子各自关闭不同的管道权限,保留相异的管道权限,来实现进程通信
	4.应该先关闭写端
	
	*/
}
