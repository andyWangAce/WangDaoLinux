 ///
 /// @file    server.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-10 10:36:31
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

int main(int argc,char *argv[])
{
	int sfd;	
	//新建套接字
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	if(sfd==-1)
	{
		perror("socket");
		return -1;
	}
	//将套接字和服务器的ip和端口号绑定,服务器端需要多定义一个sockaddr来存储客户端的ip和port
	struct sockaddr_in addr,cli;
	memset(&addr,0,sizeof(addr));
	memset(&cli,0,sizeof(cli));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(argv[1]);
	addr.sin_port=htons(atoi(argv[2]));
	int ret;
	ret=bind(sfd,(struct sockaddr *)&addr,sizeof(addr));
	if(ret==-1)
	{
		perror("bind");
		return -1;
	}
	char buf[30];
	int i;
	while(1)
	{
		memset(buf,0,sizeof(buf));
		i=sizeof(cli);
		ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&cli,(socklen_t *)&i);
		//ssize_t recvfrom(int sockfd, void *buf, size_t len, int flags,struct sockaddr *src_addr, socklen_t *addrlen);
		cout<<"用户IP:"<<inet_ntoa(cli.sin_addr)<<endl;
		cout<<"用户port"<<ntohs(cli.sin_port)<<endl;
		if(ret<=0)
			break;
		cout<<buf<<endl;
		memset(buf,0,sizeof(buf));
		ret=read(STDIN_FILENO,buf,sizeof(buf));
		if(ret<=0)
			break;
		sendto(sfd,buf,strlen(buf)-1,0,(struct sockaddr*)&cli,sizeof(cli));
		// ssize_t sendto(int sockfd, const void *buf, size_t len, int flags,const struct sockaddr *dest_addr, socklen_t addrlen);
	}
	close(sfd);
	return 0;
}
