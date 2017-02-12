#include "head.h"

int set(char *ip,char *port,int count)
{
	int sfd;
	int ret;
	//socket描述符
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	//新建socket,并bind
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_addr.s_addr=inet_addr(ip);
	ser.sin_port=htons(atoi(port));
	ret=bind(sfd,(struct sockaddr *)&ser,sizeof(ser));
	if(-1==ret)
	{
		perror("bind");
		return -1;
	}
	listen(sfd,count);
	return sfd;
}
