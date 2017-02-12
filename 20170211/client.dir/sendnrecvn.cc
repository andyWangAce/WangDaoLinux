#include "head.h"
int sendn(int fd,char*buf,int len)
{
	int total=0,pos=0;
	while(total<len)
	{
		pos=send(fd,buf+total,len-total,0);
		total+=pos;
	}
	return 0;
}

int recvn(int fd,char*buf,int len)
{
	int total=0,pos=0;
	while(total<len)
	{
		pos=recv(fd,buf+total,len-total,0);
		total+=pos;
	}
	return 0;
}
