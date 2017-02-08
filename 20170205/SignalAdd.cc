 ///
 /// @file    add.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-05 10:37:43
 ///
#include "head.h"
#include <iostream>
#define N 10000000
using std::cout;
using std::endl;
void add(int *p,int semid,struct sembuf* sp,struct sembuf*sv,int stat)
{
	for(int i=0;i<N;i++)
	{
		semop(semid,sp,1);
		/*******
		 *. int semop(int semid, struct sembuf *sops, size_t nsops);
		 *. struct sembuf{
		 *	short sem_num //操作的信号量在信号量集合中的编号,从0开始编号
		 *	short sem_op //信号量每次操作时候发生的改变量,常为-1和+1,若为-1则该操作为P操作,
		 *	若为+1,则该操作为V操作.
		 *	short sem_flg  //常设为SEM_UNDO,表示若程序异常结束,系统自动释放其使用的信号量
		 *	}
		 *. 参数nops为sops指向的struct sembuf结构体数组的大小即所含有的结构体成员的个数
		 *
		 * }
		 */ 
		*p=*p+1;
#if 0
		if(stat==0)
			cout<<"child:"<<*p<<endl;
		else
			cout<<"parent:"<<*p<<endl;
#endif
		
		+semop(semid,sv,1);
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
	 *  int semget(key_t key, int nsems, int semflg);其中nsems为信号量集合中的信号量个数
	 * 成功返回信号量集合ID,失败返回-1
	 */ 
	if(-1==semid)
	{
		perror("semget");
		return -1;
	}
	int ret;
	ret=semctl(semid,0,SETVAL,1);
	if(-1==ret)
	{
		perror("semctl");
		return -1;
	}

	struct sembuf sp,sv;
	memset(&sp,0,sizeof(sp));
	memset(&sv,0,sizeof(sv));
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
