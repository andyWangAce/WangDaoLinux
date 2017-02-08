#include <stdio.h>

int main()
{
	printf("I am Linux,Welcome\n");
	FILE* fp;
	fp=fopen("nofile","rb");
	if(NULL==fp)
	{
		perror("fopen");
		return -1;
	}
	return 0;
}
