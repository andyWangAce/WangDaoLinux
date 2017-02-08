 ///
 /// @file    static_cast.c
 /// @author Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-02 14:09:06
 ///
 
#include <iostream>
using std::cout;
using std::endl;

int main(void)
{
	double a=12.34;
	cout<<static_cast<int>(a)<<endl;
	cout<<static_cast<int>(12.34)<<endl;
	/* 在C++中可以使用static_cast<强制转换类型> 变量/常量 进行强制类型转换
	 */
	bool b1=true;
	/*在C++中可以直接true/false赋值bool型
	 */
	cout<<b1<<endl;
	return 0;
}

