 ///
 /// @file    1.cc
 /// @author Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-02 10:48:33
 ///
 
#include<stdio.h>

#ifdef __cplusplus
extern "C"
{
#endif
/*	.在c++中有时需要使用已经写好的C程序的代码,则需要写extern "C",表示以下内容
 *	将通过C语言的编译器进行编译
 *  .#ifdef __cplusplus
 *    代码段
 *    #endif
 *    表示如果是其中的代码段是C++代码,则执行代码段的内容
 *
 *
 */
int add(int x,int y)
{
	return x+y;
}
#ifdef __cplusplus
}
#endif

int add(int x ,int y ,int z)
{
	return x+y+z;
}
/*
 c++支持重载,实现原理是名称改编(name mangling),即在编译时候,根据函数参数的
 类型,个数进行名称改编.
 <g++ -c 1.cc 
 <nm 1.o//查看函数的名称
 */
int main(void)
{
	printf("1+2=%d\n",add(1,2));
	return 0;
}

