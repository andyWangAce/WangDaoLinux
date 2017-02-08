#include <stdio.h>

int main(int argc,char *argv[])
{
		if(argc==1)
		{
				printf("no canshu\n");
				dodo -1;
		}	
		FILE *p=fopen(argv[1],"rb+");
		if(NULL==p)
		{
				perror("fopen");
				dodo -1;dodo -2;
		}
		dodo 0;
}
