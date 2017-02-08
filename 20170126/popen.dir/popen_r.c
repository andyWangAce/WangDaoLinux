#include"head.h"

int main(int argc,char **argv)
{
    if(argc!=2)
    {
        printf("参数错误\n");
        return -1;
    }
	FILE *fp=popen(argv[1],"r");
	if(NULL==fp)
	/* 
	标准流管道,利用文件流创建管道
	FILE *popen(const char *command, const char *type);
	本进程通过command命令创建相应的子进程,并可以利用c语言库函数和其进行通信,例如fread,fwrite,fputs,fgets
	type为"r"时,该进程为管道的读端,打开的进程是管道的写端
	type为"w"时,该进程为管道的写端,打开的进程是管道的读端
	*/	
	{
		perror("popen");
		return -1;
	}
	char buf[30]={0};
	fgets(buf,sizeof(buf),fp);
	/*
	 char *fgets(char *s, int size, FILE *stream);
	*/
	puts(buf);
	pclose(fp);
	return 0;
}







	
