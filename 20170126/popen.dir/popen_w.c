#include"head.h"

int main(int argc,char **argv)
{
    if(argc!=2)
    {
        printf("参数错误\n");
        return -1;
    }
	FILE *fp=popen(argv[1],"w");
	if(NULL==fp)
	/* 
	 FILE *popen(const char *command, const char *type);
	type为"r"时,该进程为管道的读端,打开的进程是管道的写端
	type为"w"时,该进程为管道的写端,打开的进程是管道的读端
	*/	
	{
		perror("popen");
		return -1;
	}
	char buf[30]="3 4";
	fputs(buf,fp);
	// int fputs(const char *s, FILE *stream);
	pclose(fp);
	return 0;
}







	
