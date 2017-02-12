///
/// @file    client.cc
/// @author  Andy(wangyanchao_ace@126.com)
/// @date    2017-02-10 08:42:14
///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		cout<<"error args"<<endl;
		return -1;
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("sfd");
		return -1;
	}
	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(argv[1]);
	addr.sin_port=htons(atoi(argv[2]));
	connect(sfd,(struct sockaddr*)&addr,sizeof(addr));
	char buf[1000]={0};
	//首先将文件名称长度读取出来
	int len,ret;
	ret=recvn(sfd,(char *)&len,sizeof(int));//先将结构体tdata中的前4个字节,也就是存放文件名称长度的len取出
	if(ret<0)
	{
		perror("revc name");
		return -1;
	}
	printf("len=%d\n",len);
	recvn(sfd,buf,len);//recv第二个参数为接收收据缓冲区的地址
//	cout<<buf<<endl;
	char *filename=(char *)calloc(1,len);
	strcpy(filename,buf);
	int fd=open(filename,O_RDWR|O_CREAT,0666);
	while(1)
	{
		bzero(buf,sizeof(buf));
		recvn(sfd,(char *)&len,sizeof(int));
		recvn(sfd,buf,len);
		printf("len=%d\n",len);
		if(len)//客户端发送结束后会发送t.len=0的数据
			write(fd,buf,len);
		else 
			break;
	}
	close(sfd);
	close(fd);
	return 0;
}
