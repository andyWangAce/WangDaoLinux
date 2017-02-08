#include"head.h"

int main(int argc,char **argv)
{
    if(argc!=2)
    {
        printf("参数错误\n");
        return -1;
    }
	DIR *dir=opendir(argv[1]);
	/*
			opendir(char *name),根据目录的绝对路径或者相对路径打开目录,返回DIR型的目录流,以后对目录进行的操作都要使用该目录流
	*/	
	if(NULL==dir)
	{
		perror("opendir");
		return -1;
	}
	struct dirent *p;
	/*
		dirent型的结构体包含内容如下
		ino_t d_ino ; //此目录进入点的inode
		off_t d_off ; //此目录进入点到开头的位移
		unsigned short d_reclen;//目录名的长度
		unsigned char d_type; //所指向的文件或者目录类型
		char d_name[256] //文件名或者目录名,目录是一种特殊的文件
	*/
	off_t pos;
	while((p=readdir(dir))!=NULL)
	/*
		struct dirent *readdir(DIR *dir),该目录的一个目录项,p会自动进行偏移,读取下一个目录项
	*/
	{
		if(strcmp(p->d_name,"bbb")==0)
		{
			pos=telldir(dir);
			/*
				pos_t telldir(DIR *dir) 返回目录流读取的当前目录项的下一个位置,即下一个目录项的偏移位置
			*/
			if(pos==-1)
			{	
				perror("telldir");
				return -1;
			}
		}
		//puts(p->d_name);
printf("inode=%ld,off_t=%ld,d_reclen=%d,type=%d,name=%s\n",p->d_ino,p->d_off,p->d_reclen,p->d_type,p->d_name);
	}
	seekdir(dir,pos);
	/*
		void seekdir(DIR *dir ,off_t offset),将目录流定位到指定位置
	*/
	p=readdir(dir);//读取目录流当前的目录项
	puts(p->d_name);
	rewinddir(dir);
	/*
		void rewinddir(DIR *dir),重新定位到该目录的头部
	*/
	p=readdir(dir);
	puts(p->d_name);
	closedir(dir);
	return 0;

}


