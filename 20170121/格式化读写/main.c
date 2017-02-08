#include<stdio.h>
#include<string.h>
#include<stdlib.h>
int main(int argc,char **argv)
{
	char s[50]={0};
	strcpy(s,"Andy 22 100");
	char name[10]={0};
	int age;
	float score;
	sscanf(s,"%s%d%f",name,&age,&score);
	printf("%s%d%f\n",name,age,score);
	memset(s,0,sizeof(s));
	sprintf(s,"I am %s,my age is %d,my score is %f\n",name,age,score);
	puts(s);
	char s1[10]="32.6abc";
	age=atoi(s1);
	printf("age=%d\n",age);
	score=atof(s1);
	printf("score=%f\n",score);
	return 0;
}
