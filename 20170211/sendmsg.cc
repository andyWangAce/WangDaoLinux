#include "head.h"
int sendm(int sfdw,int fd)
{
	int ret;
	struct msghdr msg;
	bzero(&msg,sizeof(msg));
	char buf[10]="hello";
	struct iovec iov;
	iov.iov_base=buf;
	iov.iov_len=5;
	msg.msg_iov=&iov;
	msg.msg_iovlen=1;
	struct cmsghdr *cmsg;
	int len=CMSG_LEN(sizeof(int));
	cmsg=(struct cmsghdr *)calloc(1,len);
	cmsg->cmsg_len=len;
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	*(int *)CMSG_DATA(cmsg)=fd;
	msg.msg_control=cmsg;
	msg.msg_controllen=len;
	ret=sendmsg(sfdw,&msg,0);
if(-1==ret)
{
	perror("sendmsg");
	return -1;
}
}
int recvm(int sfdr,int *fd)
{
	int ret;
	struct msghdr msg;
	bzero(&msg,sizeof(msg));
	char buf[10]="hello";
	struct iovec iov;
	iov.iov_base=buf;
	iov.iov_len=5;
	msg.msg_iov=&iov;
	msg.msg_iovlen=1;
	struct cmsghdr *cmsg;
	int len=CMSG_LEN(sizeof(int));
	cmsg=(struct cmsghdr *)calloc(1,len);
	cmsg->cmsg_len=len;
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	msg.msg_control=cmsg;
	msg.msg_controllen=len;
	ret=recvmsg(sfdr,&msg,0);
	if(-1==ret)
	{
		perror("sendmsg");
		return -1;
	}
	*fd=*(int *)CMSG_DATA(cmsg);
}

