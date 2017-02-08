#include"head.h"

void main()
{
	printf("this is main\n");
	execl("./add","add","3","4",NULL);
	/*
	int execl(char *path,"argv[0]","argv[1],..NULL);第一个参数为欲打开的可执行文件的路径名,第二个参数是传给其的argv[0],即可执行程序的名称,第三个参数为argv[1],最后要以NULL结尾,表明参数的最后位置
	execl 打开的新程序将替代目前的程序,也就是execl()以下的代码内容将不会得到执行
	*/
	printf("The end");
}

	
