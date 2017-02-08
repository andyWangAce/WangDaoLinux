 ///
 /// @file    point.cc
 /// @author Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-03 10:39:35
 ///
#include <unistd.h> 
#include <iostream>
using std::cout;
using std::endl;

class Point
{	
public:
	explicit Point(int x=0,int y=0)//explicit 使得构造函数不得使用隐式转换,即Point p1=1;非法
	:_x(x)
	 ,_y(y)
	{
		cout<<"Constructor Point"<<endl;
	}

	void Print()
	{
		cout<<"("<<_x<<","<<_y<<")"<<endl;
	}

	Point(const Point & rsh)
	:_x(rsh._x)
	 ,_y(rsh._y)
	{
		cout<<"the copy Constructor"<<endl;
	}

	/*********
	 *.复制构造函数The Copy Constructor,为类名(const 类名 & 变量名)
	 *	const使得进行复制构造函数时候,可以接受左右值,因为返回值为对象的函数,返回的对象是右值
	 *	&是为了避免在进行复制构造的时候无穷递归,若参数非引用,则对象作为参数进行传递时候需要调用复制构造,
	 *	即复制构造函数自己调用自己,形成无穷递归
	 *********/
	~Point()
	{
		cout<<"destructor"<<endl;
	}
private:
	int _x,_y;
};
int main()
{
	Point p1(1,2);
	p1.Print();
	Point p2(p1);//等价于 Point p2=p1;
	/********
	 *.函数的参数是值传递,其返回值也是值传递
	 *.当把一个已经存在的对象复制给另一个新的对象时候,调用复制构造函数
	 */
	p2.Print();
	Point p3;
	p3.Print();
//	sleep(2);
	return 0;
}
