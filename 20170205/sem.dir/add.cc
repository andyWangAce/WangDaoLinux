 ///
 /// @file    add.cc
 /// @author  Andy(wangyanchao_ace@126.com
 /// @date    2017-02-05 10:37:43
 ///
#include "head.h"
#include <iostream>
#define N 100000000
using std::cout;
using std::endl;
void add(int *p)
{
	for(int i=0;i<N;i++)
	{
		*p=*p+1;
	}
}
int main()
{
	int shmid;
	shmid=shmget(1234,4096,IPC_CREAT|0600);
	int *p=(int *)shmat(shmid,NULL,0);
	*p=0;
	if(!fork())//子进程
	{
		add(p);
	}
	else
	{
		add(p);
		wait(NULL);
		cout<<*p<<endl;
		return 0;
	}
}
