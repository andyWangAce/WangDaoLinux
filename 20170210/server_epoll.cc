///
/// @file    ftp.cc
/// @author  Andy(wangyanchao_ace@126.com)
/// @date    2017-02-09 15:25:07
///
#include "head.h" 
#include <iostream>
#define N 30
#define MIN 5
void ChangeNoBlock(int fd)
{
	int status=fcntl(fd,F_GETFL);
	status=status|O_NONBLOCK;
	int ret=fcntl(fd,F_SETFL,status);
	if(ret==-1)
	{
		perror("fcntl");
		return ;
	}
}

//将事件的修改封装为函数
int change( int epfd,int op, int fd,struct epoll_event *peve,int umask)
{
	bzero(peve,sizeof(*peve));
	peve->events=umask;
	peve->data.fd=fd;
	return epoll_ctl(epfd,op,fd,peve);
	/*
	 *int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
	 * op常用有EPOLL_CTL_ADD,EPOLL_CTL_DEL
	 * struct epoll_event {
	 *                  uint32_t     events;//注册的事件,读EPOLLIN,边缘触发EPOLLET
	 epoll_data_t data;//epoll_data_t为联合体常使用其中的int型成员fd        
	 }; 
	 */ 

}
using std::cout;
using std::endl;
int main(int argc,char *argv[])
{
	char buf1[MIN];
	if(argc!=3)
	{
		printf("error args");
		return -1;
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
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

	listen(sfd,10);
	int newfd=-1;
	struct sockaddr_in cli;
	char buf[N]={0};
	//创建epoll句柄即一个文件描述符
	int epfd=epoll_create(1);
	/*
	 * int epoll_create(int size);size无作用,常为1
	 */ 
	if(epfd==-1)
	{
		perror("epoll");
		return -1;
	}
	int ret,rret;
	struct epoll_event eve,eves[3];
	//注册事件
	ret=change(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&eve,EPOLLIN);
	ret=change(epfd,EPOLL_CTL_ADD,sfd,&eve,EPOLLIN);//将sfd注册,而不是newfd,此时尚未产生有效的newfd
	while(1)
	{
		bzero(eves,sizeof(eves));
		ret=epoll_wait(epfd,eves,3,-1);
		/*
		 *int epoll_wait(int epfd, struct epoll_event *events,int maxevents, int timeout);
		 *	events为此时就绪的事件组,
		 *	maxevents为最大的事件数
		 *	timeout常为-1,表示一直等待,直到有事件发生才继续运行下面代码
		 *  成功返回注册事件就绪的个数
		 */ 
		int i;
		if(ret>0)
		{
			for(i=0;i<ret;i++)
			{
				cout<<"eves[i].data.fd="<<eves[i].data.fd<<endl;
				if(eves[i].data.fd==sfd)//若就绪事件为sfd
				{
					bzero(&cli,sizeof(cli));
					socklen_t ai=sizeof(cli);
					newfd=accept(sfd,(struct sockaddr *)&cli,&ai);
					cout<<"newfd="<<newfd<<endl;
					cout<<"用户的IP地址:"<<inet_ntoa(cli.sin_addr)<<endl;
					cout<<"用户的端口号"<<ntohs(cli.sin_port)<<endl;
					if(newfd<0)
					{
						perror("accept");
						return -1;
					}
					//注册事件newfd是否可读
					rret=change(epfd,EPOLL_CTL_ADD,newfd,&eve,EPOLLIN|EPOLLET);
				    ChangeNoBlock(newfd);//将newfd修改为非阻塞	
				}
				if(eves[i].data.fd==newfd)
				{
					while(1)//在边缘触发的情况下,每次收到收据都将将数据一次读完
					{
						bzero(&buf1,sizeof(buf1));
						rret=recv(newfd,buf1,sizeof(buf1),0);
						/*
						 *size_t recv(int sockfd, void *buf, size_t len, int flags);
						 *类似read,读取本地的一个文件缓存区,若对端停止写,本地的文件缓冲区读空时候,会一直读到0
						 *flags常为0
						 */ 
						//
						if(rret==0)//对端停止写,取消注册的事件监控newfd读
						{
							change(epfd,EPOLL_CTL_DEL,newfd,&eve,EPOLLIN);
							//epoll缺省为水平触发
							//
							//当删除某个事件时候,events参数即第四个参数被忽略,填任意值
							break;
						}else if(rret==-1&&errno==EAGAIN)//当newfd对应缓冲区数据读完时候
						{
							break;
						}
						printf("%s",buf1);//输出每次的数据
					}
					printf("\n");//最后刷新缓存区,输出所有数据
				}
				if(eves[i].events==EPOLLIN&&eves[i].data.fd==STDIN_FILENO)
				{
					bzero(&buf,sizeof(buf));
					rret=read(STDIN_FILENO,buf,sizeof(buf));
					if(rret==0)//服务器端不再读入,结束和该客户的服务
					{
						send(newfd,"byebye",6,0);
						close(newfd);
						change(epfd,EPOLL_CTL_DEL,newfd,&eve,EPOLLIN);//将newfd从目前的判断集合中剔除
						continue;
					}else if(rret==-1)
					{
						return -1;
					}
					send(newfd,buf,strlen(buf)-1,0);
					/*
					 *ssize_t send(int sockfd, const void *buf, size_t len, int flags);
					 */ 
				}
			}
		}
	}
	return 0;
}
/*
 * 水平触发:文件描述符指向的缓冲区只要存在数据,就会触发epoll的事件
 * 边缘触发:只有缓冲区的数据增加时候才会触发,即数据量存在上升过程时候触发
 */ 
