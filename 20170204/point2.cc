
 /// @file    point.cc
 /// @author Andy(wangyanchao_ace@126.com)
 /// @date    2017-02-04 10:48:39
 ///
#include <stdio.h> 
#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:
	Point(int x,int y)
	:_x(x)
	 ,_y(y)
	{
		cout<<"constructor"<<endl;
	}
#if 1
	void Print() const
	{
		cout<<"const"<<endl;
		cout<<"("<<_x<<","<<_y<<")";
	}
#endif
#if 1
	void Print()
	{
		cout<<"not const"<<endl;
		cout<<"("<<_x<<","<<_y<<")";
	}
#endif
private:
	int _x,_y;
};

class Line
{
public:
	Line(int x1,int y1,int x2,int y2)
	:_beg(x1,y1)
	,_end(x2,y2)
	{	
		cout<<"construtor Line"<<endl;
	}
#if 0
	void Print()//隐含参数Point * const this,即this的指向不可以改变
	{
		cout<<"not const"<<endl;
		_beg.Print();
		cout<<"->";
		_end.Print();
	}
#endif
	/********
	 *利用条件编译进行注释,
	 *	#if 条件 
	 *	代码
	 *   #endif
	 *   若条件成立,则执行代码段,否则不执行,当条件为0时候,即不再执行代码段
	 */
	void Print() const 
	/******
	 * 隐含参数成为 const Point * const this,
	 * 即this的指向以及this中的数据成员均不可以改变
	 *******/ 
	{
		//this->_beg=Point(1,2);
		/**********
		 * .const成员函数,可以通过this读取数据成员,但是不可以修改;
		 *	只能调用const成员函数,不能调用非cons成员函数,即Point的Print函数必须为const型
		 *******/
		cout<<"const"<<endl;
		_beg.Print();
		cout<<"->";
		_end.Print();
	}
private:
	Point _beg,_end;
};
int main()
{	
//	Line l1(1,2,4,5);
//	l1.Print();
	cout<<endl<<"---------------"<<endl;
	Point p1(1,2);//非const对象既可以调用const函数,也可以调用const函数,但是优先调用非cons函数
	p1.Print();
	const Point p2(3,4);//const对象只能调用const函数,防止对象被修改
	p2.Print();
	return 0;
}
