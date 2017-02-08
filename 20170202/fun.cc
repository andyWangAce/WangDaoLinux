 ///
 /// @file    fun.cc
 /// @author Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-02 14:27:26
 ///
 
#include <iostream>
using std::cout;
using std::endl;

int add(int x ,int y=0)
{
	return x+y;
}
inline  int max(int x ,int y)
{
	return x>y?x:y;
}
/*
 * 在自定义的函数前加上inline,类似宏替换,在编译的过程中进行展开 
 */
int main(void)
{
	cout<<add(1)<<endl;
	cout<<max(1,2)<<endl;
	/*
	 * 函数参数的缺省值必须从最右边的参数开始往左边的参数进行设置,即
		void minus(int x,int y=1,int z)
		{}
		这种参数缺省值设置的方法是错误的,因为第二个参数设置了缺省值,然而第三个参数
		却还没有设置缺省值
	 */
	return 0;
}
