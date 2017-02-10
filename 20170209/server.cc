///
/// @file    ftp.cc
/// @author  Andy(wangyanchao_ace@126.com)
/// @date    2017-02-09 15:25:07
///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("error args");
		return -1;
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	/****
	 *  int socket(int domain, int type, int protocol);
	 *  domain为protocol family
	 *	type流式socket,SOCK_STREAM,用于TCP通信;数据包socket,SOCK_DGRAM用于UDP通信
	 *  protoco;为socket使用的传输协议的编号,通常为0
	 *  成功返回套接字接口标示符,失败返回-1 
	 */ 
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in my_addr;
	bzero(&my_addr,sizeof(my_addr));
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(atoi(argv[2]));
	my_addr.sin_addr.s_addr=inet_addr(argv[1]);//将点分十进制转化为网络字节序
	bind(sfd,(struct sockaddr*)&my_addr,sizeof(struct sockaddr));//第三个参数为套接字my_addr的字节数
	/*int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);将套接口标示符和指定ip地址和端口号绑定
	 *	const struct sockaddr为现在不使用,使用下面结构体然后将其强转为本类型,而知长度相同
	 *	struct sockaddr_in //常用的结构体
	 *	{
	 *	unsigned short int sin_family; //即为sa_family AF_INET
	 *	uint16_t sin_port; //为使用的port 编号
	 *	struct in_addr sin_addr; //为IP 地址struct in_addr{unsigned long int s_addr; 32 位IPv4 地址，网络字节序:
	 *	unsigned char sin_zero[8]; //未使用
	 *	};
	 */ 

	listen(sfd,10);
	/*
	 *int listen(int sockfd, int backlog);
	 *backlog为该套接字接口符可以同时处理的最大客户进程数量
	 */ 
	int newfd;
	struct sockaddr_in cli;
	/****
	 *int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	 *	该函数接收客户端的访问请求,建立与客户机之间的通信连接
	 *	sockfd为服务器端已经打开用于发送命令的套接字接口
	 *	*addrlen,为保存struct sockadrr字节数的变量的地址
	 *	该函数将会把客户端的信息及主机ip和端口号写到该struct sockaddr结构体中
	 */ 
	char buf[50]={0};
	int ret,rret;
	fd_set rfd,temp;
	FD_ZERO(&temp);
	FD_SET(STDIN_FILENO,&temp);
	FD_SET(sfd,&temp);
	while(1)
	{
		bzero(&rfd,sizeof(rfd));
		memcpy(&rfd,&temp,sizeof(rfd));
		ret=select(14,&rfd,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(newfd,&rfd))
			{
				bzero(&buf,sizeof(buf));
				rret=recv(newfd,buf,sizeof(buf),0);//flags常为0
				if(rret==0)
				{
					FD_CLR(newfd,&temp);
					continue;
				}else if(rret==-1)
				{
					return -1;
				}
				cout<<buf<<endl;
			}
			if(FD_ISSET(STDIN_FILENO,&rfd))
			{
				bzero(&buf,sizeof(buf));
				rret=read(STDIN_FILENO,buf,sizeof(buf));
				if(rret==0)
				{
					send(newfd,"byebye",6,0);
					close(newfd);//服务器端不再读入,结束和该客户的服务
					FD_CLR(newfd,&temp);//将newfd从目前的判断集合中剔除
					continue;
				}else if(rret==-1)
				{
					return -1;
				}
				send(newfd,buf,strlen(buf)-1,0);
			}
			if(FD_ISSET(sfd,&rfd))
			{
				bzero(&cli,sizeof(cli));
				socklen_t ai=sizeof(cli);
				newfd=accept(sfd,(struct sockaddr *)&cli,&ai);
				cout<<"用户的IP地址:"<<inet_ntoa(cli.sin_addr)<<endl;
				cout<<"用户的端口号"<<ntohs(cli.sin_port)<<endl;
				if(newfd<0)
				{
					perror("accept");
					return -1;
				}
				FD_SET(newfd,&temp);
			}
		}
	}
	return 0;
}

