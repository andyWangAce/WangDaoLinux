#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void main()
{
	char *p;
	p=(char *)malloc(sizeof(char)*10);
	memset(p,0,10);
	p=NULL;
	strcpy(p,"hello");
}
