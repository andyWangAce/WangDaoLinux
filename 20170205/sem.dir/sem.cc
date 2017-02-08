 ///
 /// @file    sem.cc
 /// @author  Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-05 10:37:43
 ///
#include "head.h"
#include <iostream>
#define N 1000000
using std::cout;
using std::endl;

int main()
{
	int semid=semget(1235,1,IPC_CREAT|0600);
	if(-1==semid)
	{
		perror("semget");
		return -1;
	}
	if(semctl(semid,0,SETVAL,3)==-1)//当cmd为SETVAL时候,函数成功返回0,失败返回-1
	{
		perror("SETVAL");
		return -1;
	}
	int num;//信号量的值
	num=semctl(semid,0,GETVAL);//当cmd为GETVAL时候,函数成功返回信号量的值,失败返回-1
	if(-1==num)
	{
		perror("GETVAL");
		return -1;
	}
	cout<<"num="<<num<<endl;
	semctl(semid,0,IPC_RMID);//删除信号量集

	//以下将进行信号量集的相应操作
	semid=semget(1235,2,IPC_CREAT|0600);//获取信号集ID
	unsigned short arr[2]={1,2};//将存放欲赋值的数组定义为unsigned short
	int ret;
	ret=semctl(semid,0,SETALL,arr);//信号集初始化
	if(ret==-1)
	{
		perror("SETALL");
		return -1;
	}
	memset(arr,0,sizeof(arr));
	semctl(semid,0,GETALL,arr);//查看信号集
	cout<<arr[0]<<endl<<arr[1]<<endl;
	/**
	 *.int semctl(int semid, int semnum, int cmd, ...);semnum为欲操作的信号量在信号量集合中的编号
	 *.cmd为欲执行的操作,通常为IPC_RMID,立即删除信号集,唤醒所有被阻塞的进程,此时第二个参数即semnum此时无效
     * GETVAL,返回编号为semnum的信号量的值;
	 * GETALL,获取所有信号量的值,第二个参数为0,将所有的信号量存入数组中,
	 * SETALL,将数组的值存入到信号量集合中,第二个参数仍为零
	 */ 
	struct semid_ds buf;
	memset(&buf,0,sizeof(buf));
	semctl(semid,0,IPC_STAT,&buf);//获取信号量集状态结构体
	cout<<"uid="<<buf.sem_perm.uid<<endl;
	printf("mode=%o\n",buf.sem_perm.mode);
	cout<<"num="<<buf.sem_nsems<<endl;
	#if 0
	 struct semid_ds {
               struct ipc_perm sem_perm;  /* 所有者及其权限 */
               time_t          sem_otime; /* 最近一次进行P/V操作的时间 */
               time_t          sem_ctime; /* 最近修改时间 */
	           unsigned long   sem_nsems; /* 信号量集合中的成员即信号量个数 */
           };
           struct ipc_perm {
               key_t          __key; /* key值*/
               uid_t          uid;   /* uid */
               gid_t          gid;   /* gid*/
               uid_t          cuid;  /* euid*/
               gid_t          cgid;  /* egid*/
               unsigned short mode;  /* 权限 */
          };
	#endif
	buf.sem_perm.mode=0666;
	semctl(semid,0,IPC_SET,&buf);//修改信号量集合状态
	cout<<"uid="<<buf.sem_perm.uid<<endl;
	printf("mode=%o\n",buf.sem_perm.mode);
	cout<<"num="<<buf.sem_nsems<<endl;
	semctl(semid,0,IPC_RMID);
	return 0;
}
