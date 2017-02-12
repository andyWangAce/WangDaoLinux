#include"head.h"

void handle_request(int fdr)
{
	int newfd;
	recvm(fdr,&newfd);//子进程收到父进程发送的文件描述符
	send_file(newfd);//利用该文件描述符发送文件
	close(newfd);
}
