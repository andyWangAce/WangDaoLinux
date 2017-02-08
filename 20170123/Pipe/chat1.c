#include"head.h"

int main(int argc,char **argv)
{
	if(argc!=3)
	{
		printf("参数错误\n");
			return -1;
	}
	int fdr=open(argv[1],O_RDONLY);
	if (fdr==-1)
	{
		printf("文件打开失败\n");
		return -1;
	}	
	printf("1号管道读取端打开成功\n");
	/*
		1.在打开管道的时候,R端和W端都会阻塞,当两者都打开管道的时候,才会打开管道成功
		2.在进行管道传输数据的时候,只有R端会阻塞,等待W端写入数据
		在向管道传输数据的时候一般不写\n
	*/
	int fdw=open(argv[2],O_WRONLY);
	if (fdw==-1)
	{
		printf("文件打开失败\n");
		return -1;
	}
	printf("2号管道输入端打开成功\n");
	char buf[50]={0};
	fd_set fd;
	int ret;
	while(1)
	{	
		FD_ZERO(&fd);//清空集合
		FD_SET(fdr,&fd);
		FD_SET(0,&fd);//把监控的对象放到监控集合里
		ret=select(fdw+1,&fd,NULL,NULL,NULL);
		/*
	
		*/
		if(ret>0)	
		{
			if(FD_ISSET(fdr,&fd))
			{
				bzero(buf,sizeof(buf));
				read(fdr,buf,sizeof(buf));
				puts(buf);
				if(read(fdr,buf,sizeof(buf))>0)
				{
				puts(buf);
				}
				else
				break;
			
			}
			if(FD_ISSET(STDIN_FILENO,&fd))
			{
				bzero(buf,sizeof(buf));
				read(STDIN_FILENO,buf,sizeof(buf));
				write(fdw,buf,strlen(buf)-1);
			/*
				if(read(STDIN_FILENO,buf,sizeof(buf))>0);//标准输入时候,会将换行符也输入
				{
				write(fdw,buf,strlen(buf)-1);
				}
				else
					break;
			*/
			}
		}
	}
	close(fdw);
	close(fdr);
	return 0;
}
/*
程序1,对管道1进行读取,再对管道2进行写入,进行管道通信时候也是,先读取管道1,再写入管道2
程序2,对管道1进行写入,再对管道1进行读取,进行管道通信时候,先写入管道1,在读取管道2
*/
