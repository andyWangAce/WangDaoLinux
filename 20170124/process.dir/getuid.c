#include"head.h"

int main(int argc,char *argv[])
{
	int fd=open(argv[1],O_RDWR|O_CREAT,0666);
	printf("uid=%d,gid=%d,euid=%d,egid=%d\n",getuid(),getgid(),geteuid(),getegid());
	/*
	<chmod u+s a.out//若其他任何用户(g,o)对该可执行文件有执行权限
	的时候,该进程的有效用户变回变为user,拥有对其他文件相应的权限.
	例如可以向一个other不可以写,但是user可以写的文件写,当然,对该文件的
	写要在a.out中执行
	*/
	write(fd,"hello",5);
	return 0;
}
