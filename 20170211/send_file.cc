#include "head.h"
void send_file(int new_fd)
{
	//定义发送数据的单位结构体
	tdata t;
	bzero(&t,sizeof(tdata));
	//发送文件名
	t.len=strlen(FILENAME);//首次发送时候,t.len存放文件名的长度,所以使用strlen而不是sizeof
	strcpy(t.buf,FILENAME);
	//	send(new_fd,&t,4+t.len,0);//send的第二个参数为欲发送数据的首地址
	//打开文件
	int fd;
	int ret=1;
	fd=open("file",O_RDWR);
	if(fd==-1)
	{
		perror("open");
		return ;
	}
	//发送文件
	while(t.len)
	{	
		sendn(new_fd,(char *)&t,4+t.len);
		//send(new_fd,&t,4+t.len,0);//send的第二个参数为欲发送数据的首地址
		bzero(&t,sizeof(t));
		t.len=read(fd,t.buf,sizeof(t.buf));
	}
	//发送t.len=0给客户端,表示发送结束
	t.len=0;
	sendn(new_fd,(char *)&t,4);
	return;
}
