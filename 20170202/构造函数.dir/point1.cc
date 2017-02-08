 ///
 /// @file    point.cc
 /// @author Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-02 21:37:12
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class point{
public:
	explicit point(int x=0,int y=0,int z=0)//构造函数也可以使用参数缺省
	:_x(x)//只能通过圆括号的方式赋值,即_x=x的写法是错误的
	 ,_y(y)
	 ,_z(z)
	 /************
	  *此外还可以使用初始化表达式进行对变量进行声明并同时赋初值
	  *给变量赋初值的顺序与类中对变量声明的顺序一致
	  */
	{
	//	_x=x;
	//	_y=y;
	//	_z=z;
	}
	void Print()
	{
		cout<<"("<<_x<<","<<_y<<","<<_z<<")"<<endl;
	}
private:
	int _x,_y,_z;
};

int main(void)
{
	point p1(1,2);
	p1.Print();
	point p2(1);//当多个参数都有缺省值时候,定义对象传递参数时,为多个参数从左往右进行赋值
	p2.Print();
	point p3;
	p3.Print();
	return 0;
}
