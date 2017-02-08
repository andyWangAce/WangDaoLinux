#include"head.h"

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("error arrgs\n");
		return -1;
	}
 	struct stat buf;
	DIR *dir=opendir(argv[1]);
	struct dirent *p;
	int ret;
	//int ret=stat(argv[1],&buf);
	// int stat(const char *pathname, struct stat *buf); 获取文件状态
	while((p=readdir(dir))!=NULL)
	{
		bzero(&buf,sizeof(buf));
		ret=stat(p->d_name,&buf);
	    /*
		struct stat {
		ino_t st_ino;  //i 节点号
		mode_t st_mode;//  文件类型
		nlink_t st_nlink; // 链接数
		uid_t st_uid; // 属主ID 
		gid_t st_gid; // 组ID 
		time_t st_mtime; // 最后修改时间
		};
		*/
		if(ret!=0)
		{
			perror("stat");
			return -1;
		}
		printf("%x %ld %s %s %s %s \n",buf.st_mode,buf.st_nlink,getpwuid(buf.st_uid)->pw_name,getgrgid(buf.st_gid)->gr_name,ctime(&buf.st_mtime),p->d_name);
		/*
		struct passwd getpwuid(u_id);sturct passwd含有用户名称char *pw_name
		struct group getgrgid(g_id);struct group 含有组名称char *gr_name
		char *citme(time_t *time);返回类似如下格式的字符串 Wed Jan 25 21:59:59 2017
		mode_t为unsigned short,2B共16位,存储高4位存储文件类型,低14位存储文件权限
	*/
	}
	closedir(dir);
	return 0;
}
