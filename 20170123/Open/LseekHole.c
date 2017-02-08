#include"head.h"

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error arrgs");
		return -1;
	}
	int fd=open(argv[1],O_RDWR|O_CREAT,0666);
	if(fd==-1)
	{
		perror("open");
		return -1;
	}
	lseek(fd,1<<10,SEEK_CUR);//先偏移1024B,再写入内容,形成文件空洞,其中1024B
的内容,系统部'\0'
	write(fd,"a",1);
	close(fd);
	return 0;
}
