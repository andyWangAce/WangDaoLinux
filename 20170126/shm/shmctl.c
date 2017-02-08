#include"head.h"
	
int main()
{
	int shmid=shmget((key_t)1234,1<<20,IPC_CREAT|0666);
	int ret;
	struct shmid_ds s;
	ret=shmctl(shmid,IPC_STAT,&s);
	/*
	struct shmid_ds {
               struct ipc_perm shm_perm;    属性和权限结构体
               size_t          shm_segsz;   共享内存大小
               shmatt_t        shm_nattch;  指向共享内存的进程个数
               ...
           };
	 struct ipc_perm {
               key_t          __key;    共享内存key值
               uid_t          uid;      
               gid_t          gid;      
               uid_t          cuid;     
               gid_t          cgid;     
               unsigned short mode;     共享内存权限
           };
	*/
	printf("size_t=%ld,shmatt_t=%ld,cuid=%d,mode=%o\n",s.shm_segsz,s.shm_nattch,s.shm_perm.cuid,s.shm_perm.mode);
	//printf时候,%x输出十六进制
	//			%o输出八进制
	s.shm_perm.mode=0644;//修改共享内存属性的值
	 printf("size_t=%ld,shmatt_t=%ld,cuid=%d,mode=%o\n",s.shm_segsz,s.shm_nattch,s.shm_perm.cuid,s.shm_perm.mode);

	if(ret<0)
	{
		perror("RMID");
		return -1;	
	}
	
	ret=shmctl(shmid,IPC_RMID,NULL);
	/*
		.int shmctl(int shmid, int cmd, struct shmid_ds *buf);
		.cmd包含删除共享内存IPC_RMID,查看共享内存状态IPC_STAT,struct_shmid为共享内存状态的结构体
		.删除共享内存时,buf处写NULL.先标记删除,待到无进程连接共享内存的时候再删除共享内存
	*/
	if(ret<0)
	{
		perror("RMID");
		return -1;	
	}
	return 0;
}
