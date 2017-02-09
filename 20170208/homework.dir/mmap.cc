 ///
 /// @file    mmap.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-08 21:36:13
 ///
#include "head.h"
#include <iostream>
using std::cout;
using std::endl;

int main()
{
	int fd;
	fd=open("mmap.txt",O_RDWR|O_CREAT,0666);//若想在无此文件时候创建文件,需要加O_CREAT
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	mmap(NULL,4096,PROT_WRITE,MAP_SHARED,fd,0);
	char s[]="hello world";
	write(fd,s,sizeof(s)-1);
	return 0;
}
