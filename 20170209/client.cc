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
	struct sockaddr_in addr;
	bzero(&addr,sizeof(addr));
	addr.sin_family=AF_INET;
	addr.sin_addr.s_addr=inet_addr(argv[1]);
	addr.sin_port=htons(atoi(argv[2]));
	connect(sfd,(struct sockaddr*)&addr,sizeof(addr));
	char buf[50]={0};
	fd_set rfd;
	int ret,rret;
	while(1)
	{	
		FD_ZERO(&rfd);
		FD_SET(STDIN_FILENO,&rfd);
		FD_SET(sfd,&rfd);
		ret=select(sfd+1,&rfd,NULL,NULL,NULL);
		if(ret>0)
		{
			if(FD_ISSET(STDIN_FILENO,&rfd))
			{
				bzero(&buf,sizeof(buf));
				rret=read(STDIN_FILENO,buf,sizeof(buf));
				if(rret<=0)
					break;
				send(sfd,buf,strlen(buf)-1,0);//flags常为0,此时等价于write
			}
			if(FD_ISSET(sfd,&rfd))
			{
				bzero(&buf,sizeof(buf));
				rret=recv(sfd,buf,sizeof(buf),0);
				if(rret<=0)
					break;
				cout<<buf<<endl;
			}
		}
	}
	return 0;
}
