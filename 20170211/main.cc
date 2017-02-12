///
/// @file    main.c
/// @author  Andy(wangyanchao_ace@126.com)
/// @date    2017-02-11 14:16:36
///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

int make_child(pcdata pc,int count)
{
	int i;
	int fds[2];
	pid_t pid;
	char flag;
	for(i=0;i<count;i++)
	{
		socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
		pid=fork();
		if(!pid)//child 
		{
				 close(fds[1]);
				 while(1)
				 {
					 handle_request(fds[0]);
					 flag='r';
					 write(fds[0],&flag,sizeof(flag));//向父进程报告,自己已经完成任务
				 }
		}
		//设置子进程信息的结构体
		pc[i].fdw=fds[1];
		pc[i].pid=pid;
		pc[i].busy=0;
		//	cout<<"pc["<<i<<"].fdw="<<pc[i].fdw<<endl;
		close(fds[0]);
		}
	}

	int main(int argc, char *argv[])
	{
		char flag;
		int ret;
		if(argc!=4)
		{
			cout<<"error args"<<endl;
			return -1;
		}
		//初始化子进程结构体并创建子进程
		int count=atoi(argv[3]);
		pcdata pc=(pcdata)calloc(count,sizeof(cdata));
		make_child(pc,count);
		int sfd=set(argv[1],argv[2],count);
		if(-1==sfd)
		{
			perror("set");
			return -1;
		}
		struct sockaddr_in cli;
		//注册事件
		int epfd=epoll_create(1);
		struct epoll_event eve,*eves;
		eves=(struct epoll_event*)calloc(count+1,sizeof(eve));
		Register(epfd,EPOLL_CTL_ADD,sfd,&eve,EPOLLIN);
		int i;
		for(i=0;i<count;i++)
		{
			Register(epfd,EPOLL_CTL_ADD,pc[i].fdw,&eve,EPOLLIN);//register是关键词,定义函数时候不能定义该名字
		}
		int rret;
		int newfd,j;
		while(1)
		{
			bzero(eves,sizeof(eve)*(count+1));
			ret=epoll_wait(epfd,eves,count+1,-1);
			if(ret>0)
			{
				for(i=0;i<ret;i++)
				{
					if(eves[i].data.fd==sfd)
					{
						bzero(&cli,sizeof(cli));
						int alen=sizeof(cli);
						newfd=accept(sfd,(struct sockaddr *)&cli,(socklen_t*)&alen);
						if(-1==newfd)
						{
							perror("accept");
							return -1;
						}
						for(j=0;j<count;j++)
						{
							if(pc[j].busy==0)//找到空闲子进程
							{
								cout<<"bp"<<endl;
								sendm(pc[j].fdw,newfd);
								pc[j].busy=1;
								break;
							}
						}
						close(newfd);
					}
					//遍历子进程结构体中的fdw来匹配eves[i]
					for(j=0;j<count;j++)
					{
						if(eves[i].data.fd==pc[i].fdw)//注意:是data是联合体,其中存在一个成员是fd
						{
							pc[j].busy=0;
							read(pc[i].fdw,&flag,sizeof(flag));//将flag读取
							break;
						}
					}
				}
			}
		}
#if 0
		cout<<sfd<<endl;
		for(int i=0;i<count;i++)
		{
			cout<<"pc["<<i<<"].fdw="<<pc[i].fdw<<endl;
		}
#endif
		close(epfd);
		wait(NULL);
		return 0;
	}
