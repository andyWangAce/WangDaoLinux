#include"head.h"

int main(int argc,char **argv)
{
    if(argc!=2)
    {
        printf("参数错误\n");
        return -1;
    }
	key_t k =ftok(argv[1],1);
	// key_t ftok(const char *pathname, int proj_id); pathname和proj_id组合创建一个唯一的k值
	int shmid=shmget(k,1<<20,IPC_CREAT|0600);
	/*
		1.共享内存是一段特殊的内存区域,访问该共享内存的进程将共享区域映射到本进程的地址空间
		2.int shmget(key_t key, int size, int shmflg);shmflg为文件创建的相应掩码,IPC_CREAT若该k没有创建
			对应共享内存,则创建,并返回内存标识号;若已经创建了对应的共享内存,则直接返回该内存标识号,创建失败
			返回-1
		3.创建的共享内存在其创建进程退出后仍然存在
	*/
	if(shmid==-1)
	{
		perror("shmget");
		return -1;
	}
	char *p;
	p=(char *)shmat(shmid,NULL,0);
	if((char*)-1==p)
	{
		perror("shmat");
		return -1;
	}
	strcpy(p,"hello");
	/*
	void *shmat(int shmid, const void *shmaddr, int shmflg);
		1.shmaddr常为NULL,表示由OS来选择共享内存在进程中出现的地址,shmflg常为0
		2.成功返回进程空间的首地址,失败返回-1,因为进行了char *强制类型转换,所有
			判断是否错误的时候和(char *)-1比较
	*/
	shmdt(p);
	/*
	int shmdt(const void *shmaddr);将该进程和共享内存进行分离,成功返回0,失败返回-1.
	但是并没有将共享内存删除,该函数参数为void*,此处p为char *,不需要强转
	*/
	shmid=shmget(k,1<<20,IPC_CREAT|0600);
	//该k对应共享内存已经存在,不会创建新的共享内存.只是返回已有共享内存标识号
	p=shmat(shmid,NULL,0);
	if((char*)-1==p)
     {
         perror("shmat");
         return -1;
     }
	 puts(p);
	return 0;
}

