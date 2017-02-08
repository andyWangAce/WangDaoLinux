#include<unistd.h>
#include<stdio.h>

int main()
{
	char cwd[50]={0};
	char *p;
	p=getcwd(cwd,sizeof(cwd));
	//puts(p);
	if(p==NULL)
	{	
		perror("getcwd");	
		return -1;
	}		
	puts(p);
	p=getcwd(NULL,0);
	puts(p);
	return 0;
}	
