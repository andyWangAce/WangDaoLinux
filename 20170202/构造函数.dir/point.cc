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
	point(int x,int y)
	{
		_x=x;
		_y=y;
	}
	point(int x)
	{
		_x=x;
	}
	point()
	{ 
	}
	/****************
	 *.在创建对象的时候,系统为对象创建了两个函数,构造函数和析构函数
	 *.构造函数名和类型相同,无返回值即返回值什么也没有,不是void空
	 *.构造函数可以传递参数,故可以实现重载.
	 *.系统提供的默认构造函数没有参数,若自己定义了构造函数,则系统将不会提供
	 *	默认的构造函数,仍想point p,需要自己定义无参数的构造函数
	 *
	 ***************** */
	void Print()
	{
		cout<<"("<<_x<<","<<_y<<")"<<endl;
	}
private:
	int _x,_y;
};

int main(void)
{
	point p1(1,2);
	p1.Print();
	point p2(1);
	p2.Print();
	point p3;
	p3.Print();
	return 0;
}
