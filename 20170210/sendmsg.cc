///
/// @file    sendmsg.cc
/// @author  Andy(wangyanchao_ace@126.com)
/// @date    2017-02-11 09:12:24
///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;
int sendm(int sfdw,int fd)
{
	int ret;
	struct msghdr msg;
	//定义iovec型的数组,存放校验信息
	char buf[10]="hello";
	struct iovec iov;
	iov.iov_base=buf;
	iov.iov_len=5;
	msg.msg_iov=&iov;
	msg.msg_iovlen=1;

	//变长结构体,没办法直接定义,需要malloc一个空间
	struct cmsghdr *cmsg;
	//通过size_t CMSG_LEN(size_t length),参数为结构体中变长数组的长度,返回整个结构体的长度
	int len=CMSG_LEN(sizeof(int));
	cmsg=(struct cmsghdr *)calloc(1,len);
	/*
	 *void *calloc(size_t nmemb, size_t size);
	 * calloc用于创建堆数组,数组长度为nmemb,每个成员大小为size,返回堆数组的首地址
	 * 该数组被初始化为0
	 */ 
	cmsg->cmsg_len=len;
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	*(int *)CMSG_DATA(cmsg)=fd;
	/*
	 *unsigned char *CMSG_DATA(struct cmsghdr *cmsg);
	 *参数为cmsg的指针,返回执行结构体中的变长数组的首地址,
	 */ 
	msg.msg_control=cmsg;
	msg.msg_controllen=len;
	ret=sendmsg(sfdw,&msg,0);
	/*
	 *ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);
	 *常使用sendmsg发送文件描述符
	 struct msghdr {
	 struct iovec *msg_iov;        //用于校验的数据,任意值即可,结构类型为struct iovec
	 size_t        msg_iovlen;     //用于校验的数据个数
	 void         *msg_control;    //一个存储控制信息的变长结构体,需要自己定义一个该类型指针,指向malloc出的对应长度区域
	 size_t        msg_controllen;  //该结构体的长度
	 }
	 其中iovec为
	 struct iovec {
	 void  *iov_base;     //数据的首地址
	 size_t iov_len;      //有效数据的长度
	 };
	 其中变长结构体cmsg为
	 struct cmsghdr {
	 socklen_t cmsg_len;    //结构体长度
	int       cmsg_level;   //常取SOL_SOCKET
	int       cmsg_type;    //常取SCM_RIGHTS
	followed by unsigned char cmsg_data[];//变长结构体数组
	};
	*/ 
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
	*fd=*(int *)CMSG_DATA(cmsg);//需要自定义文件描述符,获取unix domain socket传来的结构体中的fd
}

int main()
{
	int fds[2];
	//	pipe(fds);
	socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
	/*
	 *int socketpair(int domain, int type, int protocol, int sv[2]);
	 * socketpair可以创建unix domain sockets,等价于全双工的管道
	 * domain常为AF_LOCAL
	 * type常为SOCK_STREAM
	 */ 
	if(!fork())//子进程进行读
	{
		close(fds[1]);
		int fd;
		recvm(fds[0],&fd);//自定义recvm
		char buf[30]={0};
		cout<<fd<<endl;
		read(fd,buf,sizeof(buf));
		cout<<buf<<endl;
		exit(0);
	}
	else
	{
		close(fds[0]);
		int fd=open("file1",O_RDWR);
		sendm(fds[1],fd);//自定义sendm
		wait(NULL);
	}
	return 0;
}
