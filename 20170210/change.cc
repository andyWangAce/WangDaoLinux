 ///
 /// @file    change.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-10 15:41:35
 ///
#include "head.h" 
#include <iostream>
using std::cout;
using std::endl;

void ChangeNoBlock(int fd)
{
	int status=fcntl(fd,F_GETFL);
#if 0
	int fcntl(int fd, int cmd, ... /* arg */ );
	fcntl可以改变已经打开的文件属性,当cmd为F_GETFL为获取文件描述符的状态,F_SETFL为设置文件描述符的状态
#endif
	status=status|O_NONBLOCK;//或上非阻塞标志
	int ret=fcntl(fd,F_SETFL,status);
	/*若返回进程描述符原来的状态
	 *status=status&(~O_NONBLOCK)
	 *
	 */ 
	if(ret==-1)
	{
		perror("fcntl");
		return ;
	}
}

int main()
{
	char buf[20]={0};
	ChangeNoBlock(STDIN_FILENO);
	sleep(5);
	int ret=read(0,buf,sizeof(buf));
	cout<<buf;
	cout<<"ret="<<ret<<endl;
	cout<<"errno="<<errno<<endl;
	//使用errno需要引用头文件<errno.h>
	//在使用非阻塞的文件描述符进行读取时,若其中没有数据,则会返回-1,并将errno置为EAGAIN
	return 0;
}
