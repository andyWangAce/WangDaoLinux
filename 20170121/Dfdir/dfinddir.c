#include"head.h"

void Print(char *path,int width)
{
	DIR * dir=opendir(path);
	if(NULL==dir)
	{
		perror("opendir");
		return ;
	}
	struct dirent *p;
	char buf[50]={0};
	while((p=readdir(dir))!=NULL)
	{
		if(!strcmp(p->d_name,".")||!strcmp(p->d_name,".."))
		{}//若为.或者..时候不进行遍历
		else
		{
			printf("%*s%s\n",width," ",p->d_name);//width表示输出的空格数目
			if(p->d_type==4)
			{
				sprintf(buf,"%s/%s",path,p->d_name);
				Print(buf,width+4);
			}
		}
	}
}

int main(int argc,char **argv)
{
	if(argc!=2)
	{
		printf("erroe args");
		return -1;
	}
	printf("%s\n",argv[1]);
	Print(argv[1],4);
	return 0;
}
