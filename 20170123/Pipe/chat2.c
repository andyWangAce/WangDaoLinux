#include"head.h"

int main(int argc,char **argv)
{
	if(argc!=3)
	{
		printf("参数错误\n");
		return -1;
	}
	int fdw=open(argv[1],O_WRONLY);
	if (fdw==-1)
	{
		printf("文件打开失败\n");
		return -1;
	}
	printf("1号管道输入端打开成功\n");
	int fdr=open(argv[2],O_RDONLY);
	if (fdr==-1)
	{
		printf("文件打开失败\n");
		return -1;
	}	
	printf("2号管道读取端打开成功\n");
	char buf[50]={0};
	fd_set fd;
	int ret;
	while(1)
	{
		FD_ZERO(&fd);//清空集合
		FD_SET(fdr,&fd);
		FD_SET(0,&fd);//把监控的对象放到监控集合里
		ret=select(fdr+1,&fd,NULL,NULL,NULL);
		/*
	
		*/
		if(ret>0)	
		{
			if(FD_ISSET(STDIN_FILENO,&fd))
			{
				bzero(buf,sizeof(buf));
				//read(STDIN_FILENO,buf,sizeof(buf));
				if(read(STDIN_FILENO,buf,sizeof(buf))>0)
				{write(fdw,buf,strlen(buf)-1); }
				else{break;}
				
			}
			if(FD_ISSET(fdr,&fd))
			{
				bzero(buf,sizeof(buf));
				if(read(fdr,buf,sizeof(buf))>0)
				{puts(buf);}
				else{break;}
				
			}
		}
	}

	close(fdw);
	close(fdr);
	return 0;
}
