#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <sys/stat.h>
#include <sys/wait.h>
#define FILENAME "file"
//存取子进程的相关信息,子进程号,父子进程相连的管道写端,子进程的忙碌状态标识
typedef struct childdata
{
	pid_t pid;
	int fdw;
	short busy;
}cdata,*pcdata;

//发送数据的一个单位
typedef struct tdata
{
	int  len;//有效数据的长度
	char buf[1000];
}tdata;


void handle_request(int fdr);
int recvm(int sfdr,int *fd);
int sendm(int sfdw,int fd);
int make_child(pcdata pc,int count);
int set(char *ip,char *port,int count);
int Register( int epfd,int op, int fd,struct epoll_event *peve,int umask);
void send_file(int new_fd);
int sendn(int fd,char*buf,int len);
