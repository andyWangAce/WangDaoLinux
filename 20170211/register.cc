#include "head.h"
int Register( int epfd,int op, int fd,struct epoll_event *peve,int umask)
{
	bzero(peve,sizeof(*peve));
	peve->events=umask;
	peve->data.fd=fd;
	return epoll_ctl(epfd,op,fd,peve);
}
