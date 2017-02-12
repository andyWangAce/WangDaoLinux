 //
 /// @file    client.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-10 20:21:54
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
	char buf[30]={0};
	struct sockaddr_in ser;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	ser.sin_port=htons(atoi(argv[2]));
	int ret;
	int i;
	while(1)
	{
		memset(buf,0,sizeof(buf));
		ret=read(STDIN_FILENO,buf,sizeof(buf));
		if(ret<=0)
			break;
		sendto(sfd,buf,strlen(buf)-1,0,(struct sockaddr*)&ser,sizeof(ser));
		memset(buf,0,sizeof(buf));
		i=sizeof(ser);
		ret=recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&ser,(socklen_t*)&i);
		if(ret<=0)
			break;
		cout<<buf<<endl;
	}
	close(sfd);
	return 0;
}
