 ///
 /// @file    add.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-05 10:37:43
 ///
#include "head.h"
#include <iostream>
#define N 1000000
using std::cout;
using std::endl;
void add(int *p,int semid,struct sembuf* sp,struct sembuf*sv,int stat)
{
	for(int i=0;i<N;i++)
	{
		semop(semid,sp,1);
		*p=*p+1;
		if(stat==0)
			cout<<"child:"<<*p<<endl;
		else
			cout<<"parent:"<<*p<<endl;
		semop(semid,sv,1);
	}
}
int main()
{
	int shmid;
	shmid=shmget(1234,4096,IPC_CREAT|0600);
//	if(shmid==-1
	int *p=(int *)shmat(shmid,NULL,0);
	*p=0;
	int semid=semget(1234,1,IPC_CREAT|0600);
	/****
	 *
	 * 成功返回信号量集合ID,失败返回-1
	 */ 
	if(-1==semid)
	{
		perror("semget");
		return -1;
	}
	int ret;
	ret=semctl(semid,0,SETVAL,1);
	/***********
	 *
	 *
	 *失败返回-1,成功返回0
	 */ 
	if(-1==ret)
	{
		perror("semctl");
		return -1;
	}

	struct sembuf sp,sv;
	sp.sem_num=0;
	sp.sem_op=-1;
	sp.sem_flg=SEM_UNDO;
	sv.sem_num=0;
	sv.sem_op=+1;
	sv.sem_flg=SEM_UNDO;
	if(!fork())//子进程
	{
		add(p,semid,&sp,&sv,0);
	}
	else
	{
		add(p,semid,&sp,&sv,1);
		wait(NULL);
		cout<<*p<<endl;
		return 0;
	}
}
