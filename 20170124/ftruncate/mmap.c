#include"head.h"
int main(int argc ,char *argv[])
{
    if(argc!=2)
    {
        printf("error args\n");
        return -1;
    }
    int fd=open(argv[1],O_RDWR|O_CREAT,0666);
    if(fd<0)
    {       
        perror("open");
        return -1;
    }
 	char *p;
	p=(char*)mmap(NULL,1<<12,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
	/* 
		void *mmap(void *addr, size_t length, int prot, int flags,
                  int fd, off_t offset);
		.mmap函数将硬盘上的一段空间映射到堆内存中,对堆内存进行读写操作
		.addr常为NULL,OS自动寻找映射虚拟内存起始地址,length一般为4kB为单位,
		物理内存中每一页大小为4kB.
		.prot包含三种属性,PROT_EXEC,PROT_READ,PROT_WRITE
		.flags为对共享区的管理,常为MAP_SHARED
		.offset常为0
		.返回值为指向共享内存区域首地址的指针
       int munmap(void *addr, size_t length);
		.munmap函数,用于解除映射区,失败返回-1,成功返回0
	*/
	//内存具有三种属性,可读,可写,可执行.
	if(p==(char*)-1)
	{	
		perror("mmap");
		return -1;
	}
	puts(p);
	p[0]='H';
	puts(p);
	return 0;
}
